using Networking;
using UnityEngine;

namespace Prototype
{
    public class FakeMessageHandler : MessageHandler
    {
        public static FakeMessageHandler Create()
        {
            var gm = new GameObject();
            DontDestroyOnLoad(gm);
            return gm.AddComponent<FakeMessageHandler>();
        }

        public override void Connect()
        {
        }

        public override void Disconnect()
        {
        }

        public override void WriteMessage(object message)
        {
        }

        public override bool TryRemoveMessage(out object message)
        {
            message = default;
            return false;
        }
    }
}