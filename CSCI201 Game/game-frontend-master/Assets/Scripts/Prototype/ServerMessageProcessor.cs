using Networking.MessageTypes;
using Protos;
using System.Collections.Generic;
using UnityEngine;

namespace Prototype
{
    public class ServerMessageProcessor : MonoBehaviour
    {
        [SerializeField] private RemotePlayer _playerPrefab;
        [SerializeField] private Dictionary<int, RemotePlayer> _remotePlayers = new Dictionary<int, RemotePlayer>();


        private void Update()
        {
            var messageHandler = MainSceneParameters.Find()?.MessageHandler;
            if (messageHandler != null)
            {
                const int MAX_MESSAGE_PER_FRAME = 10;
                var messageCount = 0;
                while (messageCount < MAX_MESSAGE_PER_FRAME)
                {
                    if (messageHandler.TryRemoveMessage(out var message))
                    {
                        ProcessMessage(message);
                        ++messageCount;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        private void ProcessMessage(object message)
        {
            switch (message)
            {
                case PlayerInfo playerInfo:
                    {
                        print($"Player Info: id = {playerInfo.Id}, x = {playerInfo.X}, y = {playerInfo.Y}");

                        SyncPlayerCoordinates(playerInfo);
                        break;
                    }
                case PlayerRemoved playerRemoved:
                    {
                        print($"Player removed: id = {playerRemoved.PlayerId.ID}");
                        RemovePlayer((int)playerRemoved.PlayerId.ID);
                        break;
                    }

                case PlayerDisconnected playerDisconnected:
                    {
                        print($"Player removed: id = {playerDisconnected.PlayerId.ID}");
                        RemovePlayer((int)playerDisconnected.PlayerId.ID);
                        break;
                    }
                default:
                    {
                        print($"[INFO] Unknown message type {message.GetType()}");
                        break;
                    }
            }
        }

        private void SyncPlayerCoordinates(PlayerInfo playerInfo)
        {
            var id = playerInfo.Id;
            var pos = new Vector2((float)playerInfo.X, (float)playerInfo.Y);

            RemotePlayer remotePlayerObject = null;
            if (!_remotePlayers.TryGetValue(id, out remotePlayerObject))
            {
                remotePlayerObject = RemotePlayer.Create(_playerPrefab, pos);
                _remotePlayers.Add(id, remotePlayerObject);
            }

            remotePlayerObject.AddPosition(pos);
        }

        private void RemovePlayer(int id)
        {
            print($"Player is removed with int id {id}");

            foreach (var pair in _remotePlayers)
            {
                print($"{pair.Key}, {pair.Value.name}");
            }

            if (_remotePlayers.ContainsKey(id))
            {
                var player = _remotePlayers[id];
                _remotePlayers.Remove(id);

                Destroy(player.gameObject);
            }
        }
    }
}
