using System.Net;
using System.Net.Sockets;
using Google.Protobuf;


namespace Networking
{
    public class NetworkManager
    {
        public static readonly EndPoint awsEndPoint = new IPEndPoint(IPAddress.Parse("100.26.168.26"), 3456);
        public static readonly EndPoint debugEndPoint = new IPEndPoint(IPAddress.Loopback, 3456);

        private readonly EndPoint RemoteEp;
        private Socket _socket;
        public NetworkManager(EndPoint remote)
        {
            RemoteEp = remote;
        }

        public bool Connected { get; private set; } = false;
        public NetworkStream Stream { get; private set; }
        
        public void SocketConnect()
        {
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _socket.Connect(RemoteEp);
            Stream = new NetworkStream(_socket);
            Connected = true;
        }

        public void Close()
        {
            _socket?.Dispose();
        }
    }
}