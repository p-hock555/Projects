using System;
using UnityEngine;
using UnityEngine.UI;

namespace Prototype
{
    public class DialogBox : MonoBehaviour
    {
        [SerializeField] private Text _captionText;
        [SerializeField] private Text _contentText;
        [SerializeField] private Button _okButton;
        private Action _onClose;

        public string Caption
        {
            get => _captionText.text;
            set => _captionText.text = value;
        }

        public string Content
        {
            get => _contentText.text;
            set => _contentText.text = value;
        }

        public static DialogBox Create(DialogBox prefab, string caption, string message, Transform parent = null)
        {
            var result = Instantiate(prefab, parent);
            result.Init(caption, message);
            return result;
        }

        private void Init(string caption, string message)
        {
            Caption = caption;
            Content = message;
            _okButton.onClick.AddListener(Close);
        }

        public void OnClose(Action action)
        {
            _onClose += action;
        }

        public void Close()
        {
            Destroy(gameObject);
            _onClose?.Invoke();
        }
    }
}
