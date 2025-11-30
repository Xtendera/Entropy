#ifndef MOTION_H
#define MOTION_H
#pragma once

class Motion {
public:
  Motion();
  void update(double deltaTime);
  void setMaxVelocity(double maxVelocity);
  double getMaxVelocity() { return maxVelocity; };
  double position, velocity, acceleration;

private:
  double maxVelocity;
};
#endif