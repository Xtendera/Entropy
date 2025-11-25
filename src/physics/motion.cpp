#include "motion.h"
#include <cmath>

Motion::Motion() : position{0}, velocity{0}, acceleration{0} {}

void Motion::update(double deltaTime) {
  position = position + velocity * deltaTime +
             0.5 * acceleration * std::pow(deltaTime, 2);
  velocity = velocity + acceleration * deltaTime;
}