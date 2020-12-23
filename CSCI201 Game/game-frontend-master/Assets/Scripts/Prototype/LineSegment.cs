using UnityEngine;

namespace Prototype
{
    public struct LineSegment
    {
        public Vector2 Start { get; }
        public Vector2 End { get; }

        public LineSegment(Vector2 start, Vector2 end)
        {
            Start = start;
            End = end;
        }

        private bool PointInRange(Vector2 point)
        {
            var toStart = Start - point;
            var toEnd = End - point;
            return Vector2.Dot(toStart, toEnd) <= 0;
        }

        /// <summary>
        /// Transform the line into form 'ax + by = k'.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <param name="k"></param>
        public void ToStandardForm(out float a, out float b, out float k)
        {
            var direction = Start - End;
            a = direction.y;
            b = -direction.x;
            k = a * Start.x + b * Start.y;
        }

        public static bool Intersect(ref LineSegment lhs, ref LineSegment rhs, out Vector2 position)
        {
            lhs.ToStandardForm(out var a, out var b, out var k1);
            rhs.ToStandardForm(out var c, out var d, out var k2);
            var det = a * d - b * c;
            if (Mathf.Abs(det) <= Mathf.Epsilon)
            {
                position = default;
                return false;
            }
            else
            {
                var detX = k1 * d - b * k2;
                var detY = a * k2 - k1 * c;
                var solution = new Vector2(detX / det, detY / det);
                if (lhs.PointInRange(solution) && rhs.PointInRange(solution))
                {
                    position = solution;
                    return true;
                }
                else
                {
                    position = default;
                    return false;
                }
            }
        }
    }
}
