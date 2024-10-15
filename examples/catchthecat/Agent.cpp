#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

using namespace std;

std::vector<Point2D> getVisitableNeighbours(World* w, const Point2D& current, const unordered_map<Point2D, bool>& visited);

int heuristics(int goal, Point2D neighbour);

bool operator<(const Point2D& lhs, const Point2D& rhs) {
  return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

bool operator>(const Point2D& lhs, const Point2D& rhs) {
  return (lhs.x > rhs.x) || (lhs.x == rhs.x && lhs.y > rhs.y);
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<std::pair<int, Point2D>, std::vector<std::pair<int, Point2D>>, std::greater<std::pair<int, Point2D>>> frontier;     // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  unordered_map<Point2D, int> costSoFar;

  // bootstrap state
  auto catPos = w->getCat();
  frontier.emplace(0, catPos);
  frontierSet.insert(catPos);
  costSoFar[catPos] = 0;
  visited[catPos] = true;

  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

      auto currentPair = frontier.top();
      Point2D current = currentPair.second;
      frontier.pop();
      frontierSet.erase(current);

      visited[current] = true;

      std::vector<Point2D> neighbours = getVisitableNeighbours(w, current, visited);



      if (w->catWinsOnSpace(current))
      {
          borderExit = current;
          break;
      }

      for (size_t i = 0; i < neighbours.size(); i++) 
      {
          int newCost = costSoFar[current] + 1;

          if (costSoFar.find(neighbours[i]) == costSoFar.end() || newCost < costSoFar[neighbours[i]])
          {
              costSoFar[neighbours[i]] = newCost + 1;
              int priority = newCost + heuristics(w->getWorldSideSize() / 2, neighbours[i]);
              frontier.emplace(priority, neighbours[i]);
              frontierSet.insert(neighbours[i]);
              cameFrom[neighbours[i]] = current;
          }
      }
  }

  std::vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) 
  {
      for (Point2D at = borderExit; at != catPos; at = cameFrom[at]) 
      {
          path.push_back(at);
          std::cout << at.x << " " << at.y << std::endl;
      }

      return path;
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> getVisitableNeighbours(World* w, const Point2D& current, const unordered_map<Point2D, bool>& visited) {
    std::vector<Point2D> neighbours, temp;
    
    temp = w->neighbors(current);

    for (size_t i = 0; i < temp.size(); i++) {
      Point2D neighbour = temp[i];
      if (w->isValidPosition(neighbour) && !w->getContent(neighbour) && visited.find(neighbour) == visited.end())
      {
        neighbours.push_back(neighbour);
      }
    }
    
    return neighbours;
}

int heuristics(int goal, Point2D neighbour)
{
  if (neighbour.y - neighbour.x <= 0 && neighbour.y + neighbour.x >= 0) {
    return goal - neighbour.x;
  }
  if (neighbour.x - neighbour.y < 0 && neighbour.x + neighbour.y > 0) {
    return goal - neighbour.y;
  }
  if (neighbour.x - neighbour.y <= 0 && neighbour.x + neighbour.y <= 0) {
    return goal - abs(neighbour.x);
  }
  if (neighbour.x - neighbour.y > 0 && neighbour.x + neighbour.y < 0) {
    return goal - abs(neighbour.y);
  }
  return goal;
}
