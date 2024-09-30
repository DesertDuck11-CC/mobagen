#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <vector>
#include <stack>
bool RecursiveBacktrackerExample::Step(World* w) {
    
    stack.push_back(Point2D(0, 0));
    
    
    if (!stack.empty()) 
    {
        Point2D current = stack.front();

        visited[current.x][current.y] = true;

        std::vector<Point2D> neighbours = getVisitables(w, current);
        if (neighbours.size() > 0)
        {
            Point2D target;
            if (neighbours.size() == 1)
            {
                target = neighbours.front();
            }
            else
            {
                target = randomStartPoint(w);
            }
        }

    } 
    else 
    {
        stack.pop_back();
    }


    return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;

    return visitables;
}
