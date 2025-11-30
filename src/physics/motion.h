#ifndef MOTION_H
#define MOTION_H
#pragma once

class Motion {
public:
  Motion();
  void update(double deltaTime);
  void setMaxVelocity(double maxVelocity);
  void setFriction(double friction);
  double getMaxVelocity() { return maxVelocity; };
  double getFriction() { return friction; };
  double position, velocity, acceleration;

private:
  double maxVelocity, friction;
};
#endif