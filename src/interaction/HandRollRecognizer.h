#pragma once
#include "TimeRecognizer.h"
#include <Leap.h>
#include <Animation.h>

/// <summary>
/// Refers to a noise-filtered roll amount by the user
/// </summary>
struct HandRoll {
  // The amount of the roll, in radians
  float dTheta;
  float absoluteRoll;
};

/// <summary>
/// A simplified thresholded roll detector
/// </summary>
class HandRollRecognizer
{
public:
  HandRollRecognizer(void);
  ~HandRollRecognizer(void);

  void AutoFilter(const Leap::Hand& hand, const FrameTime& frameTime, HandRoll& dra);

private:
  // True if no packets have been received yet--used to guard against initialization spikes
  bool m_hasLast;

  Smoothed<float>m_deltaRoll;
  // Last measured hand roll amount, used to guard against wander
  float m_lastRoll;
};

