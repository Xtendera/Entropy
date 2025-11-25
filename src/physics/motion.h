#ifndef MOTION_H
#define MOTION_H
#pragma once

class Motion {
public:
  Motion();
  void update(double deltaTime);
  double position, velocity, acceleration;
};
#endif