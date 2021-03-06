//
//  InteractionConfigs.h
//  Shortcuts
//
//  Created by Daniel Plemmons on 8/18/14.
//
//

#pragma once
#include "EigenTypes.h"

namespace config {
  const EigenTypes::Vector3 m_leapMin(-120.0f,290.0f,-30.0f);
  const EigenTypes::Vector3 m_leapMax(120.0f,450.0f,30.0f);
}

namespace mediaMenuConfigs {
  const float SCREEN_EDGE_BUFFER_DISTANCE = 380.0f;
}

namespace activationConfigs {
  // Pinch and Grab Constants
  const float MIN_GRAB_START = 0.7f;
  const float MIN_GRAB_CONTINUE = 0.6f;
  const float MIN_PINCH_START = 0.9f;
  const float MIN_PINCH_CONTINUE = 0.8f;
}

namespace loactionConfigs {
  // Hand Location Constants
  const float INDEX_DIRECTION_OFFSET_DISTANCE = 200.0f;
}

namespace pointingConfigs {
  const float MAX_BEND_FOR_START_POINTING = 1.6f;
  const float MAX_BEND_FOR_CONTINUE_POINTING = 1.8f;
  const float MAX_BEND_FOR_THUMB_START_POINTING = 0.35f;
  const float MAX_BEND_FOR_THUMB_CONTINUE_POINTING = 0.45f;
}

namespace poseConfigs {
  const float MIN_PALM_Y_FOR_START_UPSIDE_DOWN = 0.5f;
  const float MIN_PALM_Y_FOR_CONTINUE_UPSIDE_DOWN = 0.0f;
}

namespace transitionConfigs {
  const float MAX_HAND_DELTA_FOR_POSE_TRANSITION = 1.5f;
}

namespace scrollConfigs {
  const float MAX_SCROLL_SMOOTHING = 0.6f;
  const float MM_DELTA_FOR_MIN_SMOOTHING = 1.0f;
  const float MM_DELTA_FOR_MAX_SMOOTHING = 0.0f;

}
