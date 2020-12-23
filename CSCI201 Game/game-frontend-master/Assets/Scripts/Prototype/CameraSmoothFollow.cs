using UnityEngine;

namespace Prototype
{
    public class CameraSmoothFollow : MonoBehaviour
    {
        [SerializeField] private Rigidbody2D _playerRigidBody;
        [SerializeField] private Vector2 _cameraVelocity;
        [SerializeField] private float _maxCameraVelocity;
        [SerializeField] private float _cameraAcceleration;
        [SerializeField] private float _maxCameraOffset;
        [SerializeField] private float _velocityOffsetMultiplier;
        private Vector2 _target = Vector2.zero;

        private void Awake()
        {
        }

        private void FixedUpdate()
        {
            var offset = _velocityOffsetMultiplier * _playerRigidBody.velocity;
            offset = offset.normalized * Mathf.Min(offset.magnitude, _maxCameraOffset);
            _target = offset;
            if (Vector2.Distance(_target, transform.localPosition) >= 0.01f)
            {
                _cameraVelocity = (_target - (Vector2)transform.localPosition) * 0.1f;
                transform.localPosition += (Vector3)_cameraVelocity;
            }
        }
    }
}
