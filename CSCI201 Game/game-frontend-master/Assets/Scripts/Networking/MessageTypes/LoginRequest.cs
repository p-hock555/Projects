using Protos;

namespace Networking.MessageTypes
{
    public class LoginRequest
    {
        public LoginRequest(AuthRequest authInfo)
        {
            AuthInfo = authInfo;
        }

        public AuthRequest AuthInfo { get; }
    }
}