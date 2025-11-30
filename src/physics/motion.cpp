#include "motion.h"
#include <algorithm>
#include <limits>

Motion::Motion()
    : position{0}, velocity{0}, acceleration{0},
      maxVelocity{std::numeric_limits<double>::max()}, friction{0} {}

void Motion::update(double deltaTime) {
  if (acceleration == 0.0 && friction > 0.0) {
    if (velocity > 0) {
      velocity -= friction * deltaTime;
      if (velocity < 0) velocity = 0;
    } else if (velocity < 0) {
      velocity += friction * deltaTime;
      if (velocity > 0) velocity = 0;
    }
  }

  double newVel = velocity + acceleration * deltaTime;

  newVel = std::clamp(newVel, -maxVelocity, maxVelocity);
  position += (velocity + newVel) * 0.5 * deltaTime;
  velocity = newVel;
}

void Motion::setMaxVelocity(double maxVelocity) {
  this->maxVelocity = std::abs(maxVelocity);
}

void Motion::setFriction(double friction) {
  this->friction = std::abs(friction);
}
