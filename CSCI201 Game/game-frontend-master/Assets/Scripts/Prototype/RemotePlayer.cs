using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

namespace Prototype
{
    public class RemotePlayer : MonoBehaviour
    {
        private const float FIXED_ANIMATION_STEP = 0.048f;
        private const float ANIMATE_THRESHOLD = 0.01f;
        private Queue<Vector2> _positions = new Queue<Vector2>();

        public static RemotePlayer Create(RemotePlayer prefab, Vector2 position)
        {
            var remotePlayer = Instantiate(prefab, position, Quaternion.identity);
            return remotePlayer;
        }

        private void Awake()
        {
            StartCoroutine(CrtAnimatePlayer());
        }

        public void AddPosition(Vector2 position)
        {
            if (_positions.Count == 0 || 
                Vector2.Distance(_positions.Peek(), position) > ANIMATE_THRESHOLD)
            _positions.Enqueue(position);
        }

        private IEnumerator CrtAnimatePlayer()
        {
            while (true)
            {
                yield return new WaitUntil(() => _positions.Count > 0);
                if (_positions.Count > 0)
                {
                    yield return StartCoroutine(CrtAnimateTowards(_positions.Dequeue()));
                }
            }
        }

        private IEnumerator CrtAnimateTowards(Vector2 position)
        {
            var startTime = Time.time;
            var endTime = startTime + FIXED_ANIMATION_STEP;
            var startPosition = transform.position;
            while (Time.time < endTime)
            {
                var delta = Time.time - startTime;
                var deltaNormalized = delta / (endTime - startTime);
                var currentPosition = Vector2.Lerp(startPosition, position, deltaNormalized);
                transform.position = currentPosition;
                yield return null;
            }
        }
        
    }
}
