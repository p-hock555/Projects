using UnityEngine;
using UnityEngine.UI;

namespace Prototype
{
    public class LeaderboardEntry : MonoBehaviour
    {
        [SerializeField] private Text _usernameText;
        [SerializeField] private Text _scoreText;

        public string Username
        {
            get => _usernameText.text;
            set => _usernameText.text = value;
        }

        public string Score
        {
            get => _scoreText.text;
            set => _scoreText.text = value;
        }

        public static LeaderboardEntry Create(LeaderboardEntry prefab, string username, string score, Transform parent)
        {
            var result = Instantiate(prefab, parent);
            result.Username = username;
            result.Score = score;
            return result;
        }
    }
}