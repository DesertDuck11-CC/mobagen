#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <vector>
#include <stack>
bool RecursiveBacktrackerExample::Step(World* w) {    
    
    if (!stack.empty()) 
    {
        Point2D current = stack.back();

        visited[current.x][current.y] = true;

        w->SetNodeColor(current, Color::Red);

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
                Random rand;
                target = neighbours[rand.Range(0, neighbours.size() - 1)];
            }

            if (target == stack.back().Right())
            {
                w->SetEast(stack.back(), false);
                w->SetWest(stack.back().Right(), false);
            }
            else if (target == stack.back().Up()) 
            {
                w->SetNorth(stack.back(), false);
                w->SetSouth(stack.back().Up(), false);
            }
            else if (target == stack.back().Down()) 
            {
                w->SetSouth(stack.back(), false);
                w->SetNorth(stack.back().Down(), false);
            } 
            else if (target == stack.back().Left()) 
            {
                w->SetWest(stack.back(), false);
                w->SetEast(stack.back().Left(), false);
            }

            stack.push_back(target);

            return true;
        }
        else
        {
            w->SetNodeColor(stack.back(), Color::Black);
            stack.pop_back();

            return true;
        }

    } 
    else 
    {
        stack.push_back(randomStartPoint(w));
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

    //Up
    if ((p.Up().x >= -sideOver2) && (p.Up().x <= sideOver2) && (p.Up().y <= sideOver2) && (p.Up().y >= -sideOver2))
    {
        if (!visited[p.Up().x][p.Up().y]) 
        {
            visitables.push_back(p.Up());
        }
    }

    //Right
    if ((p.Right().x >= -sideOver2) && (p.Right().x <= sideOver2) && (p.Right().y <= sideOver2) && (p.Right().y >= -sideOver2)) 
    {
        if (!visited[p.Right().x][p.Right().y]) 
        {
            visitables.push_back(p.Right());
        }
    }

    //Down
    if ((p.Down().x >= -sideOver2) && (p.Down().x <= sideOver2) && (p.Down().y <= sideOver2) && (p.Down().y >= -sideOver2)) 
    {
        if (!visited[p.Down().x][p.Down().y]) 
        {
            visitables.push_back(p.Down());
        }
    }

    //Left
    if ((p.Left().x >= -sideOver2) && (p.Left().x <= sideOver2) && (p.Left().y <= sideOver2) && (p.Left().y >= -sideOver2)) 
    {
        if (!visited[p.Left().x][p.Left().y]) 
        {
            visitables.push_back(p.Left());
        }
    }

    return visitables;
}
