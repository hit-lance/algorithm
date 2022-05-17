#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum class LocationType { COMMON = 0, BLOCK, STREAM, DESERT };

// using Map = std::vector<std::vector<LocationType>>;
using Location = std::pair<size_t, size_t>;

class Map {
   public:
    Map(const std::string& path);
    friend std::ostream& operator<<(std::ostream& os, const Map& map);

   private:
    std::vector<std::vector<LocationType>> data_;
};