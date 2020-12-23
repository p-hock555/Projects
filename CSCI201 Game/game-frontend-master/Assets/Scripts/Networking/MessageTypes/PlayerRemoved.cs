using Protos;

namespace Networking.MessageTypes
{
    public class PlayerRemoved
    {
        public PlayerRemoved(PlayerID playerId)
        {
            PlayerId = playerId;
        }

        public PlayerID PlayerId { get; }
    }
}