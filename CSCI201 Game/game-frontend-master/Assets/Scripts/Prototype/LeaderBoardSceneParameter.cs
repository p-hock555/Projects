using JetBrains.Annotations;
using Networking;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Prototype
{
    public class LeaderBoardSceneParameter : MonoBehaviour
    {
        public const string GAME_OBJECT_NAME = "LEADER_BOARD_SCENE_PARAMETER";
        public const string SCENE_NAME = "leaderboard";

        public MessageHandler MessageHandler { get; private set; }
        public bool IsGuest { get; private set; }
        public float Score { get; private set; }

        public static LeaderBoardSceneParameter Create(MessageHandler messageHandler, bool isGuest, float score)
        {
            var gm = new GameObject(GAME_OBJECT_NAME);
            var component = gm.AddComponent<LeaderBoardSceneParameter>();
            component.Init(messageHandler, isGuest, score);
            DontDestroyOnLoad(component.gameObject);
            SceneManager.sceneLoaded += component.HandleSceneLoaded;
            return component;
        }

        [CanBeNull]
        public static LeaderBoardSceneParameter Find()
        {
            return GameObject.Find(GAME_OBJECT_NAME)?.GetComponent<LeaderBoardSceneParameter>();
        }

        public void LoadScene()
        {
            SceneManager.LoadScene(SCENE_NAME);
        }

        public AsyncOperation LoadSceneAsync()
        {
            return SceneManager.LoadSceneAsync(SCENE_NAME);
        }

        private void HandleSceneLoaded(Scene scene, LoadSceneMode mode)
        {
            SceneManager.MoveGameObjectToScene(gameObject, scene);
            SceneManager.sceneLoaded -= HandleSceneLoaded;
        }

        private void Init(MessageHandler messageHandler, bool isGuest, float score)
        {
            print("[INFO] Game screen loaded.");
            this.MessageHandler = messageHandler;
            this.IsGuest = isGuest;
            this.Score = score;
        }
    }
}
