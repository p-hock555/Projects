using JetBrains.Annotations;
using Networking;
using Protos;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.UI;

namespace Prototype
{
    public enum PlayerJumpState
    {
        Idle = 0,
        ShortJump = 1,
        LongJump = 2,
        Falling = 3,
        Wall = 4
    }

    public enum JumpDirection
    {
        Neutral = 0,
        Left = 1,
        Right = 2
    }

    public class ControlFlags
    {
        private bool _flag = false;
        public bool Read() => _flag;
        public void Set() => _flag = true;
        public void Clear() => _flag = false;
    }

    public class ConditionalFlags : ControlFlags
    {
        [NotNull] private readonly Func<bool> _condition;
        public ConditionalFlags([NotNull] Func<bool> condition)
        {
            _condition = condition;
        }

        public void Update()
        {
            if (_condition())
            {
                Set();
            }
        }
    }

    public class CharacterController : MonoBehaviour
    {
        [SerializeField] private float _jumpVerticalVelocity;
        [SerializeField] private float _jumpGravityMultiplier;
        [SerializeField] private float _fallGravityMultiplier;
        [SerializeField] private Transform _foot;
        [SerializeField] private Transform _rightHand;
        [SerializeField] private Transform _leftHand;
        [SerializeField] private float _horizontalVelocity;
        [SerializeField] private float _shortJumpHeight;
        [SerializeField] private float _longJumpHeight;
        [SerializeField] private float _longJumpTimeThreshold;
        [SerializeField] private float _playerBaseLineY;
        [SerializeField] private AnimationCurve _shortJumpVelocityField;
        [SerializeField] private Transform _checkPoint;
        [SerializeField] private List<Transform> _futureCheckPoints;
        [SerializeField] private GoalIndicator _goalIndicator;
        [SerializeField] private Text _timeDisplay;
        private float _startTime;
        private int _jumpCharge = 2;
        [SerializeField] private PlayerJumpState _jumpState = PlayerJumpState.Idle;
        private JumpDirection _jumpDirection = JumpDirection.Neutral;
        private float _durationThePlayerHoldsTheJumpKey;
        private float _previousAngularVelocity = 0.0f;
        private bool _jumpFlag = false;
        private bool _finihed = false;

        [SerializeField] private bool _isOnGround;

        private Rigidbody2D _rigidBody;

        private ConditionalFlags _jumpKeyDown;
        private ConditionalFlags _jumpKey;
        private ConditionalFlags _jumpKeyUp;
        private ConditionalFlags _leftArrow;
        private ConditionalFlags _rightArrow;


        private float inputRecordedTime = 0.0f;

        private IEnumerator CrtBroadcastPlayerPosition()
        {
            while (!_finihed)
            {
                yield return new WaitForSeconds(0.05f);

                if (!_finihed)
                {
                    MainSceneParameters.Find()?.MessageHandler.WriteMessage(
                        new PlayerInfo { Rotation = 0, X = transform.position.x, Y = transform.position.y });
                }
            }
        }

        private void Awake()
        {
            _rigidBody = GetComponent<Rigidbody2D>();
            _jumpKeyDown = new ConditionalFlags(() => Input.GetKeyDown(KeyCode.Space));
            _jumpKey = new ConditionalFlags(() => Input.GetKey(KeyCode.Space));
            _jumpKeyUp = new ConditionalFlags(() => Input.GetKeyUp(KeyCode.Space));
            _leftArrow = new ConditionalFlags(() => Input.GetKey(KeyCode.A));
            _rightArrow = new ConditionalFlags(() => Input.GetKey(KeyCode.D));
            _goalIndicator = GetComponent<GoalIndicator>();
            _startTime = Time.time;

            UpdateGoalIndicator();
            StartCoroutine(CrtBroadcastPlayerPosition());
        }

        private void SendBackToSpawn()
        {
            transform.position = _checkPoint.position;
            ClearKeyEventFlags();
            _jumpState = PlayerJumpState.Idle;
        }

        private void Update()
        {
            UpdateKeyEventFlags();
            UpdateTimeDisplay();

            if (Input.GetKeyDown(KeyCode.F2))
            {
                FinishGame(MainSceneParameters.Find().MessageHandler);
            }
        }

        private void UpdateTimeDisplay()
        {
            var timeElapsed = Time.time - _startTime;
            _timeDisplay.text = $"{timeElapsed:0.00}s";
        }

        private void UpdateKeyEventFlags()
        {
            _jumpKeyDown.Update();
            _jumpKey.Update();
            _jumpKeyUp.Update();
            _leftArrow.Update();
            _rightArrow.Update();

            inputRecordedTime = Time.time;
        }

        private void ClearKeyEventFlags()
        {
            _jumpKeyDown.Clear();
            _jumpKey.Clear();
            _jumpKeyUp.Clear();
            _leftArrow.Clear();
            _rightArrow.Clear();
        }

        private void FixedUpdate()
        {
            var updatedIsOnGround = CheckIfPlayerIsOnGround();
            UpdateGravityMultiplierAccordingToJumpState();

            switch (_jumpState)
            {
                case PlayerJumpState.Idle:
                    {
                        HandleIdleState();
                        break;
                    }
                case PlayerJumpState.ShortJump:
                    {
                        HandleShortJumpState();
                        break;
                    }
                case PlayerJumpState.LongJump:
                    {
                        HandleLongJumpState();
                        break;
                    }
                case PlayerJumpState.Wall:
                    {
                        _rigidBody.velocity = Vector2.zero;
                        _rigidBody.gravityScale = 0.0f;
                        TryTransitionToShortJump();
                        break;
                    }
                case PlayerJumpState.Falling:
                    {
                        if (!TryTransitionToShortJump())
                        {
                            if (CheckIfControlConflictWithJumpDirection())
                            {
                                _jumpState = PlayerJumpState.Idle;
                            }
                        }
                        break;
                    }
                default:
                    throw new ArgumentOutOfRangeException();
            }

            if (!_isOnGround && updatedIsOnGround)
            {
                _jumpCharge = 2;
            }
            else if (_isOnGround && !updatedIsOnGround && _jumpCharge == 2)
            {
                _jumpCharge -= 1;
            }

            ClearKeyEventFlags();
            _isOnGround = updatedIsOnGround;
        }

        private void HandleIdleState()
        {
            if (!TryTransitionToShortJump())
            {
                if (_leftArrow.Read())
                {
                    _rigidBody.velocity = SetHorizontalVelocity(_rigidBody.velocity, -_horizontalVelocity);
                }
                else if (_rightArrow.Read())
                {
                    _rigidBody.velocity = SetHorizontalVelocity(_rigidBody.velocity, _horizontalVelocity);
                }
                else
                {
                    _rigidBody.velocity = SetHorizontalVelocity(_rigidBody.velocity, 0.0f);
                }
            }
        }

        private void HandleShortJumpState()
        {
            if (CheckIfControlConflictWithJumpDirection())
            {
                _jumpState = PlayerJumpState.Idle;
            }
            else if (!TryTransitionToShortJump() && !TryTransitionToLongJump())
            {
                var verticalDistance =
                    Mathf.Max(0.0f, _playerBaseLineY + _shortJumpHeight - transform.position.y);
                var fraction = (_shortJumpHeight - verticalDistance) / _shortJumpHeight;
                var velocity = _shortJumpVelocityField.Evaluate(fraction) * _jumpVerticalVelocity;
                _rigidBody.velocity = SetVerticalVelocity(_rigidBody.velocity, velocity);

                

                SetAirVelocityWhenJumping();

                if (verticalDistance <= 0.6f)
                {
                    _jumpState = PlayerJumpState.Falling;
                }
                else if (_jumpKey.Read())
                {
                    _durationThePlayerHoldsTheJumpKey += Time.deltaTime;
                }
            }
        }

        private void HandleLongJumpState()
        {
            if (CheckIfControlConflictWithJumpDirection())
            {
                _jumpState = PlayerJumpState.Idle;
            }
            else if (!TryTransitionToShortJump())
            {
                float verticalDistance =
                    Mathf.Max(0.0f, _playerBaseLineY + _longJumpHeight - transform.position.y);
                float velocity = (verticalDistance / _longJumpHeight) * _jumpVerticalVelocity;

                _rigidBody.velocity = SetVerticalVelocity(_rigidBody.velocity, velocity);

                SetAirVelocityWhenJumping();

                if (verticalDistance <= 0.6f)
                {
                    _jumpState = PlayerJumpState.Falling;
                }
            }
        }

        private void SetAirVelocityWhenJumping()
        {
            if (_jumpDirection == JumpDirection.Left)
            {
                _rigidBody.velocity = SetHorizontalVelocity(_rigidBody.velocity, -_horizontalVelocity);
            }
            else if (_jumpDirection == JumpDirection.Right)
            {
                _rigidBody.velocity = SetHorizontalVelocity(_rigidBody.velocity, _horizontalVelocity);
            }
        }

        private bool TryTransitionToShortJump()
        {
            if (_jumpKeyDown.Read() && _jumpCharge > 0)
            {
                _jumpState = PlayerJumpState.ShortJump;

                if (_leftArrow.Read())
                {
                    _jumpDirection = JumpDirection.Left;
                }
                else if (_rightArrow.Read())
                {
                    _jumpDirection = JumpDirection.Right;
                }
                else
                {
                    _jumpDirection = JumpDirection.Neutral;
                }

                --_jumpCharge;
                _playerBaseLineY = transform.position.y;
                _durationThePlayerHoldsTheJumpKey = 0.0f;
                return true;
            }
            else
            {
                return false;
            }
        }

        private bool TryTransitionToLongJump()
        {
            if (_durationThePlayerHoldsTheJumpKey >= _longJumpTimeThreshold)
            {
                _jumpState = PlayerJumpState.LongJump;
                return true;
            }
            return false;
        }

        private bool WallAtRightHandSide()
        {
            return Physics2D
                .OverlapCircleAll(_rightHand.position, 0.05f)
                .Any(cld => cld.CompareTag("Wall"));
        }

        private bool WallAtLeftHandSide()
        {
            return Physics2D
                .OverlapCircleAll(_leftHand.position, 0.05f)
                .Any(cld => cld.CompareTag("Wall"));
        }

        private void HandlePlayerHitGround()
        {

        }

        private void UpdateGravityMultiplierAccordingToJumpState()
        {
            if (_jumpState == PlayerJumpState.Idle || _jumpState == PlayerJumpState.Falling)
            {
                _rigidBody.gravityScale = _fallGravityMultiplier;
            }
            else
            {
                _rigidBody.gravityScale = _jumpGravityMultiplier;
            }
        }

        private void HandlePlayerJumpInput()
        {
            if (Input.GetKeyDown(KeyCode.Space) && _jumpCharge > 0)
            {
                --_jumpCharge;
                _rigidBody.velocity = SetVerticalVelocity(_rigidBody.velocity, _jumpVerticalVelocity);
            }
        }

        private static Vector2 SetVerticalVelocity(Vector2 oldVelocity, float verticalVelocity)
        {
            oldVelocity.y = verticalVelocity;
            return oldVelocity;
        }

        private static Vector2 SetHorizontalVelocity(Vector2 oldVelocity, float horizontalVelocity)
        {
            oldVelocity.x = horizontalVelocity;
            return oldVelocity;
        }

        private bool CheckIfPlayerIsOnGround()
        {
            var allColliders = Physics2D.OverlapCircleAll(_foot.transform.position, 0.05f);
            return allColliders.Any(cld => !cld.CompareTag("Player"));
        }

        private bool CheckIfControlConflictWithJumpDirection()
        {
            switch (_jumpDirection)
            {
                case JumpDirection.Neutral:
                    return _leftArrow.Read() || _rightArrow.Read();
                case JumpDirection.Left:
                    return _rightArrow.Read();
                case JumpDirection.Right:
                    return _leftArrow.Read();
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private void OnCollisionEnter2D(Collision2D collision)
        {
            _jumpState = PlayerJumpState.Idle;

            if (collision.collider.CompareTag("Spikes"))
            {
                SendBackToSpawn();
            }
            else if (WallAtRightHandSide() || WallAtLeftHandSide())
            {
                _jumpState = PlayerJumpState.Wall;
                _jumpCharge = 2;
            }
        }

        private void OnTriggerEnter2D(Collider2D incomingCollider)
        {
            if (incomingCollider.CompareTag("Checkpoint"))
            {
                var checkpointTransform = incomingCollider.transform;
                if (checkpointTransform == _futureCheckPoints.FirstOrDefault())
                {
                    _checkPoint = _futureCheckPoints.FirstOrDefault();
                    _futureCheckPoints.RemoveAt(0);
                    UpdateGoalIndicator();
                }
            }
        }

        private void UpdateGoalIndicator()
        {
            if (_futureCheckPoints.Count == 0)
            {
                print("[INFO] Player has finished the level!");
                _finihed = true;
                var messageHandler = MainSceneParameters.Find()?.MessageHandler;

                if (messageHandler != null)
                {
                    FinishGame(messageHandler);
                }
            }
            else
            {
                _goalIndicator.SetGoal(_futureCheckPoints[0]);
            }
        }

        private void FinishGame(MessageHandler messageHandler)
        {
            if (messageHandler is null)
            {
                print("Message handler is null.");
            }
            var score = Time.time - _startTime;
            messageHandler.WriteMessage(new PlayerFinish() { Score = score });
            LeaderBoardSceneParameter.Create(messageHandler, MainSceneParameters.Find()?.IsGuest ?? true, score).LoadScene();
        }
    }
}
