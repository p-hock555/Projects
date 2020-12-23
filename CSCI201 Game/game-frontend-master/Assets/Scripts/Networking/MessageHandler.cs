using System;
using System.Collections.Concurrent;
using UnityEngine;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading;
using Google.Protobuf;
using Networking.MessageTypes;
using Protos;
using PlayerFinish = Protos.PlayerFinish;

namespace Networking
{
    public class MessageHandler : MonoBehaviour
    {
        private ConcurrentQueue<object> InMessageQueue { get; set; }
        private BlockingCollection<object> OutMessageQueue { get; set; }

        private NetworkManager _networkManager;

        private volatile bool _listening = false;
        private volatile bool _sending = false;

        public bool Connected => _listening;

        public MessageHandler Instance => GameObject.Find("message_handler")?.GetComponent<MessageHandler>();

        public static MessageHandler Create(EndPoint remoteEndPoint)
        {
            var result = new GameObject("message_handler")
                .AddComponent<MessageHandler>();
            result.Init(remoteEndPoint);
            DontDestroyOnLoad(result.gameObject);
            return result;
        }

        private void Init(EndPoint remoteEndPoint)
        {
            InMessageQueue = new ConcurrentQueue<object>();
            OutMessageQueue = new BlockingCollection<object>();
            _networkManager = new NetworkManager(remoteEndPoint);
        }

        public virtual void Connect()
        {
            try
            {
                _networkManager.SocketConnect();
                var listenTh = new Thread(Listener);
                var sendTh = new Thread(Sender);
                _listening = true;
                _sending = true;
                listenTh.Start();
                sendTh.Start();
            }
            catch (Exception)
            {
                // ignored
            }
        }

        public virtual void Disconnect()
        {
            _listening = false;
            _sending = false;
            OutMessageQueue.Add(null);
            _networkManager.Close();
        }

        public virtual void WriteMessage(object message)
        {
            OutMessageQueue.Add(message);
        }

        public virtual bool TryRemoveMessage(out object message)
        {
            return InMessageQueue.TryDequeue(out message);
        }

        private void Listener()
        {
            try
            {
                while (_listening)
                {
                    var msgType = (InMsgType) MessageType.Parser.ParseDelimitedFrom(_networkManager.Stream).Type;
                    QueueNextMessageAccordingToType(msgType);
                }
            }
            catch (Exception e)
            {
                Debug.LogError($"{e.Message}/n{e.StackTrace}");
                _listening = false;
            }
        }

        private void QueueNextMessageAccordingToType(InMsgType msgType)
        {
            switch (msgType)
            {
                case InMsgType.Login:
                {
                    var loginResponse = LoginResponse.Parser.ParseDelimitedFrom(_networkManager.Stream);
                    InMessageQueue.Enqueue(loginResponse);
                    break;
                }
                case InMsgType.Register:
                {
                    var registerResponse = RegisterResponse.Parser.ParseDelimitedFrom(_networkManager.Stream);
                    InMessageQueue.Enqueue(registerResponse);
                    break;
                }
                case InMsgType.GameInfo:
                {
                    var info = PlayerInfo.Parser.ParseDelimitedFrom(_networkManager.Stream);
                    InMessageQueue.Enqueue(info);
                    break;
                }
                case InMsgType.PlayerDisconnected:
                {
                    var player =
                        new PlayerDisconnected(PlayerID.Parser.ParseDelimitedFrom(_networkManager.Stream));
                    InMessageQueue.Enqueue(player);
                    break;
                }
                case InMsgType.PlayerRemoved:
                {
                    var removed = new PlayerRemoved(PlayerID.Parser.ParseDelimitedFrom(_networkManager.Stream));
                    InMessageQueue.Enqueue(removed);
                    break;
                }
                case InMsgType.PlayerDied:
                {
                    var player = new PlayerDied(PlayerID.Parser.ParseDelimitedFrom(_networkManager.Stream));
                    InMessageQueue.Enqueue(player);
                    break;
                }
                case InMsgType.LeaderboardInfo:
                {
                    var leaderboard = Leaderboard.Parser.ParseDelimitedFrom(_networkManager.Stream);
                    InMessageQueue.Enqueue(leaderboard);
                    break;
                }
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private void Sender()
        {
            while (_sending)
            {
                var msg = OutMessageQueue.Take();
                switch (msg)
                {
                    case null:
                        break;
                    case LoginRequest loginRequest:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.Login
                        }.WriteDelimitedTo(_networkManager.Stream);
                        loginRequest.AuthInfo.WriteDelimitedTo(_networkManager.Stream);

                        _networkManager.Stream.Flush();
                        break;
                    }
                    case RegisterRequest registerRequest:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.Register
                        }.WriteDelimitedTo(_networkManager.Stream);
                        registerRequest.AuthInfo.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                    case PlayerInfo playerInfo:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.PlayerInfo
                        }.WriteDelimitedTo(_networkManager.Stream);
                        playerInfo.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                    case PlayerFinish playerFinish:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.PlayerFinish
                        }.WriteDelimitedTo(_networkManager.Stream);
                        playerFinish.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                    case Died _:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.PlayerDied
                        }.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                    case PlayerRestart _:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.PlayerRestart
                        }.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                    case LeaderboardRequest _:
                    {
                        new MessageType
                        {
                            Type = (int) OutMsgType.LeaderboardRequest
                        }.WriteDelimitedTo(_networkManager.Stream);
                        break;
                    }
                }
            }
        }

        private void OnDestroy()
        {
            Disconnect();
        }
    }
}