#include <queue>

#include "map.h"

int main() {
    Map map("../data/map1.txt");
    auto path = map.AStar({8, 3}, {9, 14});
    // map.data_[8][3] = map.data_[9][14] = LocationType::DESERT;
    for (auto &loc : path) {
        std::cout << loc.first << " " << loc.second << std::endl;
        // map.data_[loc.first][loc.second] = LocationType::STREAM;
    }
    // std::cout << std::endl;

    // std::cout << map << std::endl;
    return 0;
}