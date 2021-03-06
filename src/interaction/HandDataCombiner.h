#pragma once
#include "Leap.h"
#include "HandLocationRecognizer.h"
#include "HandActivationRecognizer.h"
#include "HandPoseRecognizer.h"
#include "HandRollRecognizer.h"
#include "ScrollRecognizer.h"
#include "SystemWipeRecognizer.h"
#include "TimeRecognizer.h"

struct HandData {
  SystemWipe systemWipe;
  HandLocation locationData;
  HandPose handPose;
  HandRoll rollData;
  HandPinch pinchData;
  HandGrab grabData;
  Scroll scroll;
  double timeVisible;
};

class HandDataCombiner {
public:
  HandDataCombiner();
  ~HandDataCombiner();
  
  void AutoFilter(const SystemWipe &systemWipe, const HandLocation& handLocation, const HandPose& handPose, const HandRoll& handRoll, const HandPinch& handPinch, const HandGrab& handGrab, const Scroll& handScroll, const HandTime& handTime, HandData& handData);
};