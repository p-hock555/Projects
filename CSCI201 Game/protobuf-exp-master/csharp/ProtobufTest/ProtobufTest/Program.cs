using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using Google.Protobuf;

namespace ProtobufTest
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var remoteEp = new IPEndPoint(IPAddress.Loopback, 3456);

            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            AuthCredential cred = null;
            PlayerChange change = null;
            var status = new PlayerStatus
            {
                Name = "aaron",
                Rotation = 0,
                X = 1,
                Y = 2,
                Z = 3
            };

            
                socket.Connect(remoteEp);
                Console.WriteLine("Socket connected to {0}", socket.RemoteEndPoint);
                var stream = new NetworkStream(socket);
                cred = AuthCredential.Parser.ParseDelimitedFrom(stream);
                change = PlayerChange.Parser.ParseDelimitedFrom(stream);
            status.WriteDelimitedTo(stream);
            

            if (cred == null)
            {
                Console.WriteLine("null");
            }
            else
            {
                Console.WriteLine(cred.Password);
                Console.WriteLine(cred.Username);
            }

            if (change == null)
            {
                Console.WriteLine("null");
            }
            else
            {
                Console.WriteLine(change.Name);
                Console.WriteLine(change.EnterExit);

            }

            Console.ReadLine();
        }
    }
}