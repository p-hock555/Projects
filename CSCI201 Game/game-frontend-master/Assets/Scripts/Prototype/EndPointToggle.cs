using Networking;
using System.Net;
using UnityEngine;
using UnityEngine.UI;

namespace Prototype
{
    [RequireComponent(typeof(Text))]
    public class EndPointToggle : MonoBehaviour
    {
        private static bool _isDebug = false;
        public static EndPoint EndPoint { get; private set; } = NetworkManager.awsEndPoint;

        private void Awake()
        {
            GetComponent<Text>().text = $"isDebug: {_isDebug}";
        }

        private void Update()
        {
            if (Input.GetKeyDown(KeyCode.F1))
            {
                Toggle();
                print("[INFO] Toggled debug endpoint");
            }
        }

        public void Toggle()
        {
            if (_isDebug)
            {
                _isDebug = false;
                EndPoint = NetworkManager.awsEndPoint;
            }
            else
            {
                _isDebug = true;
                EndPoint = NetworkManager.debugEndPoint;
            }
            GetComponent<Text>().text = $"isDebug: {_isDebug}";
        }
    }
}
