#include "motion.h"
#include <algorithm>
#include <limits>

Motion::Motion()
    : position{0}, velocity{0}, acceleration{0},
      maxVelocity{std::numeric_limits<double>::max()} {}

void Motion::update(double deltaTime) {
  double newVel = velocity + acceleration * deltaTime;

  newVel = std::clamp(newVel, -maxVelocity, maxVelocity);
  position += (velocity + newVel) * 0.5 * deltaTime;
  velocity = newVel;
}

// Reason for the getter/setter functions is bcs maxVelocity needs to be
// positive/absolute
void Motion::setMaxVelocity(double maxVelocity) {
  this->maxVelocity = std::abs(maxVelocity);
}
