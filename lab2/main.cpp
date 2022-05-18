#include "map.h"

int main() {
    Map map("../data/map1.txt");
    std::cout << map << std::endl;
    // auto path = map.AStar({8, 3}, {9, 14});
    // for (auto &loc : path) {
    //     std::cout << loc.first << loc.second << std::endl;
    // }
    return 0;
}