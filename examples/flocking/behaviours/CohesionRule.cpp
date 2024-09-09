#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  for (size_t i = 0; i < neighborhood.size(); i++) 
  {
      if (neighborhood[i] != boid)
      {
          cohesionForce += neighborhood[i]->getPosition();
      }
  }
  if (neighborhood.size() > 0)
  {
        cohesionForce /= neighborhood.size();
        cohesionForce -= boid->getPosition();
        return cohesionForce.normalized();
  }

  return Vector2f::zero();
}