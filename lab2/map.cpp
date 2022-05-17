#include "map.h"

Map::Map(const std::string& path) {
    std::ifstream fin(path);
    size_t m, n;
    fin >> m >> n;
    data_ = std::vector<std::vector<LocationType>>(m, std::vector<LocationType>(n));

    for (const auto e : {LocationType::BLOCK, LocationType::STREAM, LocationType::DESERT}) {
        size_t t;
        fin >> t;
        for (int i = 0; i < t; ++i) {
            fin >> m >> n;
            data_[m][n] = e;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Map& map) {
    for (auto& row : map.data_) {
        for (auto& loc : row) {
            std::cout << static_cast<int>(loc) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}