#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class LocationType { COMMON = 0, OBSTACLE, STREAM, DESERT };

using Location = std::pair<size_t, size_t>;

class Map {
   public:
    Map(const std::string& path);

    std::vector<Location> AStar(const Location& src, const Location& dst);

    friend std::ostream& operator<<(std::ostream& os, const Map& map);

   private:
    std::vector<std::vector<LocationType>> data_;
};

static const std::vector<Location> DIRACTIONS = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
