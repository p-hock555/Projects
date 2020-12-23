using Protos;

namespace Networking.MessageTypes
{
    public class PlayerDisconnected
    {
        public PlayerDisconnected(PlayerID playerId)
        {
            PlayerId = playerId;
        }

        public PlayerID PlayerId { get; }
    }
}