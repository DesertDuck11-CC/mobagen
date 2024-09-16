#include "HexagonGameOfLife.h"

void HexagonGameOfLife::Step(World& world) 
{
  for (size_t i = 0; i < world.SideSize(); i++) {
    for (size_t j = 0; j < world.SideSize(); j++) {
      Point2D point(i, j);

      int neighbours = CountNeighbors(world, point);

      if (world.Get(point) && neighbours < 2) {
        world.SetNext(point, false);  // Underpopulation
      } else if (world.Get(point) && (neighbours == 2 || neighbours == 3)) {
        world.SetNext(point, true);  // Survives
      } else if (world.Get(point) && neighbours > 3) {
        world.SetNext(point, false);  // Overpopulation
      } else if (!world.Get(point) && neighbours == 3) {
        world.SetNext(point, true);  // Reproduction
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
    if (world.Get(point + point.RIGHT)) {
      sum++;
    }
    if (world.Get(point + point.UP)) {
      sum++;
    }
    if (world.Get(point + point.UP + point.LEFT)) {
      sum++;
    }
    if (world.Get(point + point.LEFT)) {
      sum++;
    }
    if (world.Get(point + point.DOWN + point.LEFT)) {
      sum++;
    }
    if (world.Get(point + point.DOWN)) {
      sum++;
    }
  }
  else  //Odd
  {
    if (world.Get(point + point.RIGHT)) {
      sum++;
    }
    if (world.Get(point + point.UP + point.RIGHT)) {
      sum++;
    }
    if (world.Get(point + point.UP)) {
      sum++;
    }
    if (world.Get(point + point.LEFT)) {
      sum++;
    }
    if (world.Get(point + point.DOWN)) {
      sum++;
    }
    if (world.Get(point + point.DOWN + point.RIGHT)) {
      sum++;
    }
  }

  return sum; 
}
