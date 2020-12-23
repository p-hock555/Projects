using Protos;

namespace Networking.MessageTypes
{
    public class RegisterRequest
    {
        public RegisterRequest(AuthRequest authInfo)
        {
            AuthInfo = authInfo;
        }

        public AuthRequest AuthInfo { get; }
    }
}