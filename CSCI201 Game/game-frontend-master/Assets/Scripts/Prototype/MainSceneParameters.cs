using JetBrains.Annotations;
using Networking;
using System;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Prototype
{
    public class MainSceneParameters : MonoBehaviour
    {
        public const string GAME_OBJECT_NAME = "MAIN_SCENE_PARAMETERS";
        public const string SCENE_NAME = "main";

        public MessageHandler MessageHandler { get; private set; }
        public bool IsGuest { get; set; }

        public static MainSceneParameters Create(MessageHandler messageHandler, bool isGuest = false)
        {
            var gm = new GameObject(GAME_OBJECT_NAME);
            var component = gm.AddComponent<MainSceneParameters>();
            component.IsGuest = isGuest;
            component.Init(messageHandler);
            DontDestroyOnLoad(component.gameObject);
            SceneManager.sceneLoaded += component.HandleSceneLoaded;
            return component;
        }

        [CanBeNull]
        public static MainSceneParameters Find()
        {
            return GameObject.Find(GAME_OBJECT_NAME)?.GetComponent<MainSceneParameters>();
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

        private void Init(MessageHandler messageHandler)
        {
            print("[INFO] Game screen loaded.");
            this.MessageHandler = messageHandler;
        }
    }
}
