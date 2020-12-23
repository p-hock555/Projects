using UnityEngine;

namespace Prototype
{
    public static class AnimationCurveExt
    {
        public static float GetDuration(this AnimationCurve curve)
        {
            var lastKey = curve[curve.length - 1];
            return lastKey.time;
        }

        public static float EvaluateNormalized(this AnimationCurve curve, float time)
        {
            var duration = curve.GetDuration();
            return curve.Evaluate(duration * time);
        }
    }
}
