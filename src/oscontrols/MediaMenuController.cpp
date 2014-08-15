#include "MediaMenuController.h"


MediaMenuController::MediaMenuController() :
m_fadeState(FADE_OUT),
m_mediaView(new MediaView(Vector3(300, 300, 0), 5.0f))
{
  m_controllingHand = Leap::Hand::invalid();
  std::cout << "init media menu controller children" << std::endl;
  m_rootNode->AddChild(m_mediaView);
}

void MediaMenuController::AutoFilter(const HandExistenceState &hes) {
  if(!m_controllingHand.isValid()) { // if there is a controlling hand
    //    std::cout << "no controlling hand" << std::endl;
    if(!hes.m_newHands.empty())
    {
      m_controllingHand = hes.m_newHands[0];
      m_fadeState = FADE_IN;
      std::cout << "set new controlling hand" << std::endl;
    }
  }
  else {
    //std::cout << "has controlling hand" << std::endl;
    if(!findHandInVector(hes.m_stableHands, m_controllingHand)) {
      m_fadeState = FADE_OUT;
      m_controllingHand = Leap::Hand::invalid();
      std::cout << "remove controlling hand" << std::endl;
    }
  }
  
  switch (m_fadeState) {
    case FADE_IN:
      m_mediaView->setOpacity(1.0f);
      break;
    case FADE_OUT:
      m_mediaView->setOpacity(0.0f);
      break;
    default:
      break;
      // woo
  }
}

bool MediaMenuController::findHandInVector(std::vector<Leap::Hand> vect, Leap::Hand goalHand) {
  bool retVal = false;
  for(Leap::Hand hand : vect) {
    if(hand.id() == goalHand.id()) {
      retVal = true;
    }
  }
  return retVal;
}



