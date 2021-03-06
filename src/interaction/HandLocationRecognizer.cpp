#include "stdafx.h"
#include "HandLocationRecognizer.h"
#include "HandPoseRecognizer.h"
#include "CoordinateUtility.h"
#include "InteractionConfigs.h"

HandLocationRecognizer::HandLocationRecognizer(void) :
isInitialized(false)
{}
HandLocationRecognizer::~HandLocationRecognizer(void) {}

void HandLocationRecognizer::AutoFilter(const Leap::Hand& hand, const HandPose& handPose, HandLocation& handLocation) {
  EigenTypes::Vector2 screenLocation;
  
  //We sometimes want to offset the palm position based on the direction the user is pointing
  EigenTypes::Vector3 offset(0.0,0.0,0.0);
  
  screenLocation = m_coordinateUtility->LeapToScreen(hand.palmPosition());

  for( auto finger : hand.fingers() ) {
    if ( finger.type() == Leap::Finger::TYPE_INDEX) {
      offset = finger.direction().toVector3<EigenTypes::Vector3>();
    }
  }
  
  offset *= loactionConfigs::INDEX_DIRECTION_OFFSET_DISTANCE;
  
  screenLocation += ProjectVector(2, offset);
  
  screenLocation.y() *= -1.0f;
  handLocation.x = static_cast<float>(screenLocation.x());
  handLocation.y = static_cast<float>(screenLocation.y());
  handLocation.mmX = static_cast<float>(hand.palmPosition().x);
  handLocation.mmY = static_cast<float>(hand.palmPosition().y * -1);
  
  if ( isInitialized ) {
    handLocation.dX = static_cast<float>(handLocation.x - lastPosition.x());
    handLocation.dY = static_cast<float>(handLocation.y - lastPosition.y());
    handLocation.dmmX = static_cast<float>(handLocation.mmX - lastLeapPosition.x());
    handLocation.dmmY = static_cast<float>(handLocation.mmY - lastLeapPosition.y());
  } else {
    handLocation.dX = 0.0f;
    handLocation.dY = 0.0f;
    handLocation.dmmX = 0.0f;
    handLocation.dmmY = 0.0f;
  }
  
  lastLeapPosition = handLocation.leapPosition();
  lastPosition = handLocation.screenPosition();
  isInitialized = true;
}