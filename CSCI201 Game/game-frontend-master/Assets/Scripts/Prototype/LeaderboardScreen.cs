using Networking.MessageTypes;
using System.Collections;
using Networking;
using UnityEngine;
using Protos;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

namespace Prototype
{
    public class LeaderboardScreen : MonoBehaviour
    {
        [SerializeField] private Text _loadingText;
        [SerializeField] private Text _scoreDisplay;
        [SerializeField] private Transform _leaderboardParent;
        [SerializeField] private LeaderboardEntry _leaderboardEntryPrefab;

        private void Awake()
        {
            var parameters = LeaderBoardSceneParameter.Find();
            if (parameters != null)
            {
                _scoreDisplay.text = $"Your time: {parameters.Score:0.00}s";
                if (parameters.IsGuest)
                {
                    _loadingText.text = "Login to see the leaderboard.";
                }
                else
                {
                    var messageHandler = parameters.MessageHandler;
                    if (messageHandler != null)
                    {
                        messageHandler.WriteMessage(new LeaderboardRequest());
                        StartCoroutine(CrtWaitForLeaderboardResponse(messageHandler));
                    }
                }
            }
        }

        private IEnumerator CrtWaitForLeaderboardResponse(MessageHandler messageHandler)
        {
            while (messageHandler.Connected)
            {
                if (messageHandler.TryRemoveMessage(out var message))
                {
                    if (message is Leaderboard leaderboard)
                    {
                        UpdateLeaderboardDisplay(leaderboard);
                    }
                }
                yield return null;
            }
        }

        private void UpdateLeaderboardDisplay(Leaderboard leaderboard)
        {
            _loadingText.gameObject.SetActive(false);
            foreach (var entry in leaderboard.Scores)
            {
                LeaderboardEntry.Create(_leaderboardEntryPrefab, entry.Username, entry.Score.ToString(), _leaderboardParent);
            }
        }

        public void HandleExit()
        {
            Destroy(LeaderBoardSceneParameter.Find()?.MessageHandler);
            Destroy(LeaderBoardSceneParameter.Find()?.gameObject);
#if UNITY_EDITOR
            SceneManager.LoadScene("Login");
#else
            Application.Quit();
#endif
        }

        public void HandleRestart()
        {
            MainSceneParameters.Create
            (
                LeaderBoardSceneParameter.Find()?.MessageHandler,
                LeaderBoardSceneParameter.Find()?.IsGuest ?? true
            ).LoadScene();
        }
    }
}
