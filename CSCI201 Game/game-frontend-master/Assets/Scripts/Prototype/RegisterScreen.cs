using System.Collections;
using System.Collections.Generic;
using System.Text;
using Networking;
using Networking.MessageTypes;
using Protos;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Prototype
{
    public class RegisterScreen : MonoBehaviour
    {
        [SerializeField] private InputField _usernameField;
        [SerializeField] private InputField _passwordField;
        [SerializeField] private InputField _confirmPasswordField;
        [SerializeField] private Button _cancelBtn;
        [SerializeField] private Button _signUpBtn;
        [SerializeField] private DialogBox _dialogPrefab;
        [SerializeField] private Transform _dialogParent;

        private readonly Dictionary<int, string> _errorCodeMessageMap =
            new Dictionary<int, string>()
            {
                {1, "Username is already taken."},
                {2, "Username can only contain letters, numbers, and underscore."},
                {4, "Username must be 4 to 16 characters long."},
                {8, "Password must be 8 to 20 characters long."}
            };

        public void HandleSignUpButtonClick()
        {

            if (_passwordField.text.Equals(_confirmPasswordField.text))
            {
                Register();
            }
            else
            {
                DialogBox.Create(_dialogPrefab, "Error", "Password and confirm password must match.", _dialogParent)
                    .OnClose(() => SetInteractable(true));
            }
        }


        private void Register()
        {
            //MessageHandler.Connect();
            var messageHandler = MessageHandler.Create(EndPointToggle.EndPoint);
            messageHandler.Connect();

            if (messageHandler.Connected)
            {
                var username = _usernameField.text;
                var password = _passwordField.text;
                var authRequest = new RegisterRequest(new AuthRequest { Username = username, Password = password });
                messageHandler.WriteMessage(authRequest);
                SetInteractable(false);
                StartCoroutine(CrtWaitForServerResponse(messageHandler));
            }
            else
            {
                SetInteractable(false);
                DialogBox.Create(_dialogPrefab, "Error", "Cannot connect to the server.", _dialogParent)
                    .OnClose(() => SetInteractable(true));
            }
        }

        private IEnumerator CrtWaitForServerResponse(MessageHandler messageHandler)
        {
            print("Waiting for register response...");
            object response = null;
            var startTime = Time.time;
            while (!messageHandler.TryRemoveMessage(out response) ||
                   !(response is RegisterResponse))
            {
                yield return null;
                if (Time.time > startTime + 5f)
                {
                    DialogBox.Create(_dialogPrefab, "Error", "Connection timed out.", _dialogParent)
                        .OnClose(() => SetInteractable(true));
                    Destroy(messageHandler.gameObject);
                    yield break;
                }
            }

            var registerResponse = (RegisterResponse) response;
            print($"Register response: {registerResponse.StatusCode}");

            if (registerResponse.StatusCode == 0)
            {
                DialogBox.Create(_dialogPrefab, "Success", "You are successfully registered.", _dialogParent)
                    .OnClose(() => SceneManager.LoadScene("Login"));
            }
            else
            {
                var builder = new StringBuilder();
                foreach (var pair in _errorCodeMessageMap)
                {
                    var flag = pair.Key;
                    var msg = pair.Value;
                    if ((flag & registerResponse.StatusCode) > 0)
                    {
                        builder.AppendLine(msg);
                    }
                }

                DialogBox.Create(_dialogPrefab, "Error", builder.ToString(), _dialogParent)
                    .OnClose(() => SetInteractable(true));
            }
        }

        public void HandleBackBtnClicked()
        {
            SceneManager.LoadScene("Login");
        }


        private void SetInteractable(bool b)
        {
            _usernameField.interactable = b;
            _passwordField.interactable = b;
            _confirmPasswordField.interactable = b;
            _signUpBtn.interactable = b;
            _cancelBtn.interactable = b;
        }
    }
}