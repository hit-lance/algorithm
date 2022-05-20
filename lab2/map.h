#pragma once

#include <iostream>
#include <vector>

enum class LocationType { COMMON = 0, OBSTACLE, STREAM, DESERT };

using Location = std::pair<int, int>;

class Map {
   public:
    Map(const std::vector<std::vector<LocationType>>& data);

    std::vector<Location> AStar(const Location& src, const Location& dst) const;

    std::pair<std::vector<Location>, std::vector<Location>> BiAStar(const Location& src, const Location& dst) const;

    friend std::ostream& operator<<(std::ostream& os, const Map& map);

   private:
    std::vector<std::vector<LocationType>> data_;
};

static const std::vector<Location> DIRACTIONS = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
