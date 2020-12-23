using Prototype;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Laser : MonoBehaviour
{
    [SerializeField] private float _activateIntervals;
    [SerializeField] private float _activateOffset;
    [SerializeField] private float _activateDuration;
    [SerializeField] private float _maxBeamSize;
    [SerializeField] private AnimationCurve _activeBeamSizeCurve;
    [SerializeField] private Transform _laserSizeTransform;

    private void Start()
    {
        _activeBeamSizeCurve.preWrapMode = WrapMode.ClampForever;
        StartCoroutine(CrtAnimateLaser());
    }

    private IEnumerator CrtAnimateLaser()
    {
        _laserSizeTransform.gameObject.SetActive(false);
        yield return new WaitForSeconds(_activateOffset);
        while (true)
        {
            yield return StartCoroutine(CrtAnimateLaserActive());
            yield return new WaitForSeconds(_activateIntervals);
        }
    }

    private IEnumerator CrtAnimateLaserActive()
    {
        _laserSizeTransform.gameObject.SetActive(true);
        var time = 0.0f;
        var curveDuration = _activeBeamSizeCurve.GetDuration();
        while (time < _activateDuration)
        {
            var scale =  _laserSizeTransform.localScale;
            var normalizedTime = time / _activateDuration;
            scale.x = _activeBeamSizeCurve.EvaluateNormalized(normalizedTime) * _maxBeamSize;
            time += Time.deltaTime;
            _laserSizeTransform.localScale = scale;
            yield return new WaitForEndOfFrame();
        }
        _laserSizeTransform.gameObject.SetActive(false);
        yield break;
    }
}
