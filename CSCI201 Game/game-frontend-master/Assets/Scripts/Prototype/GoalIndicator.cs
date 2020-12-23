using UnityEngine;

namespace Prototype
{
    public class GoalIndicator : MonoBehaviour
    {
        [SerializeField] private float _marginSize;
        [SerializeField] private Transform _goal;
        [SerializeField] private Transform _indicator;
        private Camera _camera;

        private void Awake()
        {
            _camera = Camera.main;
        }

        public void SetGoal(Transform goal)
        {
            _goal = goal;
        }

        private void Update()
        {
            if (_goal != null)
            {
                UpdateIndicator();
            }
        }

        private void UpdateIndicator()
        {
            if (_goal != null && _indicator != null)
            {
                _indicator.gameObject.SetActive(true);

                var topLeft = RectTopLeft();
                var topRight = RectTopRight();
                var bottomLeft = RectBottomLeft();
                var bottomRight = RectBottomRight();

                var topLine = new LineSegment(topLeft, topRight);
                var leftLine = new LineSegment(topLeft, bottomLeft);
                var bottomLine = new LineSegment(bottomLeft, bottomRight);
                var rightLine = new LineSegment(bottomRight, topRight);

                if (TryUpdateIndicatorIfIntersectsWithLine(topLine)) return;
                if (TryUpdateIndicatorIfIntersectsWithLine(leftLine)) return;
                if (TryUpdateIndicatorIfIntersectsWithLine(bottomLine)) return;
                if (TryUpdateIndicatorIfIntersectsWithLine(rightLine)) return;

                _indicator.gameObject.SetActive(false);
            }
        }

        private bool TryUpdateIndicatorIfIntersectsWithLine(LineSegment line)
        {
            var playerToGoal = new LineSegment(transform.position, _goal.position);
            if (LineSegment.Intersect(ref line, ref playerToGoal, out var point))
            {
                var playerPos = (Vector2) transform.position;
                var offset = (point - playerPos) * 0.9f;
                _indicator.transform.position = playerPos + offset;
                MakeIndicatorLooksAt(_goal.transform.position);
                return true;
            }
            else
            {
                return false;
            }
        }

        private void MakeIndicatorLooksAt(Vector2 target)
        {
            var indicatorToObj = target - (Vector2) _indicator.position;
            var angleDiff = Vector2.SignedAngle(_indicator.up, indicatorToObj);
            _indicator.Rotate(Vector3.forward, angleDiff);
        }

        private bool IsGoalOnScreen()
        {
            var bottomLeft = RectBottomLeft();
            var topRight = RectTopRight();
            var minX = bottomLeft.x;
            var minY = bottomLeft.y;
            var maxX = topRight.x;
            var maxY = topRight.y;
            Vector2 goalPos = _goal.position;
            return goalPos.x >= minX && goalPos.x <= maxX &&
                   goalPos.y >= minY && goalPos.y <= maxY;
        }

        private Vector2 RectBottomLeft()
        {
            return _camera.ScreenToWorldPoint(Vector2.zero);
        }

        private Vector2 RectTopRight()
        {
            float screenHeight = Screen.height;
            float screenWidth = Screen.width;
            return _camera.ScreenToWorldPoint(new Vector2(screenWidth, screenHeight));
        }

        private Vector2 RectTopLeft()
        {
            float screenHeight = Screen.height;
            return _camera.ScreenToWorldPoint(new Vector2(0, screenHeight));
        }
        private Vector2 RectBottomRight()
        {
            float screenWidth = Screen.width;
            return _camera.ScreenToWorldPoint(new Vector2(screenWidth, 0));
        }

    }
}
