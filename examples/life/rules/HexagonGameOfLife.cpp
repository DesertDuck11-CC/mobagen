#include "HexagonGameOfLife.h"

void HexagonGameOfLife::Step(World& world) 
{
  for (size_t i = 0; i < world.SideSize(); i++) {
    for (size_t j = 0; j < world.SideSize(); j++) {
      Point2D point(i, j);

      int neighbours = CountNeighbors(world, point);

      if (world.Get(point) && neighbours < 2) {
        world.SetNext(point, false);  // Underpopulation
      } else if (world.Get(point) && neighbours == 2) {
        world.SetNext(point, true);  // Survives
      } else if (world.Get(point) && neighbours > 2) {
        world.SetNext(point, false);  // Overpopulation
      } else if (!world.Get(point) && neighbours == 2) {
        world.SetNext(point, true);  // Reproduction
      } else {
        world.SetNext(point, false);
      }
    }
  }
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) 
{
  int sum = 0;
 
  //Even
  if (point.y % 2 == 0) 
  {
    if (world.Get(point + point.RIGHT) && point.x < world.SideSize() - 1) {
      sum++;
    }
    if (world.Get(point + point.UP) && point.y > 0) {
      sum++;
    }
    if (world.Get(point + point.UP + point.LEFT) && point.y > 0 && point.x > 0) {
      sum++;
    }
    if (world.Get(point + point.LEFT) && point.x > 0) {
      sum++;
    }
    if (world.Get(point + point.DOWN + point.LEFT) && point.y < world.SideSize() - 1 && point.x > 0) {
      sum++;
    }
    if (world.Get(point + point.DOWN) && point.y < world.SideSize() - 1) {
      sum++;
    }
  }
  else  //Odd
  {
    if (world.Get(point + point.RIGHT) && point.x < world.SideSize() - 1) {
      sum++;
    }
    if (world.Get(point + point.UP + point.RIGHT) && point.y > 0 && point.x < world.SideSize() - 1) {
      sum++;
    }
    if (world.Get(point + point.UP) && point.y > 0) {
      sum++;
    }
    if (world.Get(point + point.LEFT) && point.x > 0) {
      sum++;
    }
    if (world.Get(point + point.DOWN) && point.y < world.SideSize() - 1) {
      sum++;
    }
    if (world.Get(point + point.DOWN + point.RIGHT) && point.y < world.SideSize() - 1 && point.x < world.SideSize() - 1) {
      sum++;
    }
  }

  return sum; 
}
