using Protos;

namespace Networking.MessageTypes
{
    public class PlayerDied
    {
        public PlayerDied(PlayerID playerId)
        {
            PlayerId = playerId;
        }

        public PlayerID PlayerId { get; }
    }
}