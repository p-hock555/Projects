using System.Collections;
using Networking;
using Networking.MessageTypes;
using Protos;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.UIElements;
using Button = UnityEngine.UI.Button;

namespace Prototype
{
    public class LoginScreen : MonoBehaviour
    {
        [SerializeField] private InputField _usernameInput;
        [SerializeField] private InputField _passwordInput;
        [SerializeField] private Button _signInButton;
        [SerializeField] private Button _signUpButton;
        [SerializeField] private CanvasRenderer _errorPanel;
        [SerializeField] private Text _errorMsg;
        [SerializeField] private float _errorWaitTime;
        private bool _interactable = true;

        private void SetInteractable(bool interactibility)
        {
            _interactable = interactibility;
            _usernameInput.interactable = interactibility;
            _passwordInput.interactable = interactibility;
            _signInButton.interactable = interactibility;
            _signUpButton.interactable = interactibility;
        }

        public void HandleLoginBtnClicked()
        {
            Login();
        }

        public void HandleSignUpBtnClicked()
        {
            SceneManager.LoadScene("register");
        }

        public void HandlePlayAsGuestBtnClick()
        {
            print("[INFO] Playing as guest.");
            var fakeMessageHandler = FakeMessageHandler.Create();
            MainSceneParameters.Create(fakeMessageHandler, true).LoadScene();
        }

        private void Login()
        {
            var messageHandler = MessageHandler.Create(EndPointToggle.EndPoint);
            messageHandler.Connect();

            if (messageHandler.Connected)
            {
                var username = _usernameInput.text;
                var password = _passwordInput.text;
                var authRequest = new LoginRequest(new AuthRequest {Username = username, Password = password});
                messageHandler.WriteMessage(authRequest);
                StartCoroutine(CrtWaitForServerResponse(messageHandler));
            }
            else
            {
                print("[ERROR] Cannot connect to server.");
                _errorPanel.gameObject.SetActive(true);
                StartCoroutine(CrtDisableErrorAfterDelay());
            }
        }

        private IEnumerator CrtWaitForServerResponse(MessageHandler messageHandler)
        {
            SetInteractable(false);
            print("Waiting for login response...");
            var startTime = Time.time;
            object response = null;
            while (!messageHandler.TryRemoveMessage(out response) ||
                   !(response is LoginResponse))
            {
                yield return null;
                if (Time.time >= startTime + 5f)
                {
                    SetInteractable(true);
                    _errorMsg.text = "Login timeout.";
                    _errorPanel.gameObject.SetActive(true);
                    StartCoroutine(CrtDisableErrorAfterDelay());
                    yield break;
                }
            }

            var loginResponse = (LoginResponse) response;

            print($"Login response: {loginResponse.Success}");

            if (loginResponse.Success == 1)
            {
                Destroy(messageHandler.gameObject);
                _errorMsg.text = "Username and password does not match. Please try again.";
                _errorPanel.gameObject.SetActive(true);
                StartCoroutine(CrtDisableErrorAfterDelay());
                _passwordInput.text = "";
                _usernameInput.text = "";
            }
            else if (loginResponse.Success == 2)
            {
                Destroy(messageHandler.gameObject);
                _errorMsg.text = "User already logged in.";
                _errorPanel.gameObject.SetActive(true);
                StartCoroutine(CrtDisableErrorAfterDelay());
                _passwordInput.text = "";
                _usernameInput.text = "";
            }
            else
            {
                MainSceneParameters.Create(messageHandler).LoadScene();
            }

            SetInteractable(true);
        }

        private IEnumerator CrtDisableErrorAfterDelay()
        {
            yield return new WaitForSeconds(_errorWaitTime);
            _errorPanel.gameObject.SetActive(false);
            SetInteractable(true);
        }
    }
}