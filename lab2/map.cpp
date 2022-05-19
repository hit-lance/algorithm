#include "map.h"

#include <limits>
#include <queue>
#include <set>
#include <algorithm>

Map::Map(const std::string& path) {
    std::ifstream fin(path);
    size_t m, n;
    fin >> m >> n;
    data_ = std::vector<std::vector<LocationType>>(m, std::vector<LocationType>(n));

    for (const auto e : {LocationType::OBSTACLE, LocationType::STREAM, LocationType::DESERT}) {
        size_t t;
        fin >> t;
        for (int i = 0; i < t; ++i) {
            fin >> m >> n;
            data_[m][n] = e;
        }
    }
}

std::vector<Location> Map::AStar(const Location& src, const Location& dst) {
    std::vector<Location> path;
    std::vector<std::vector<double>> dist_to(data_.size(),
                                             std::vector<double>(data_[0].size(), std::numeric_limits<double>::max()));
    std::vector<std::vector<Location>> edge_to(data_.size(), std::vector<Location>(data_[0].size()));

    auto h = [](const Location& a, const Location& b) {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    };

    std::priority_queue<std::pair<double, Location>, std::vector<std::pair<double, Location>>,
                        std::greater<std::pair<double, Location>>>
        pq;

    std::set<Location> s;

    dist_to[src.first][src.second] = 0;
    pq.push({h(src, dst), src});

    while (!pq.empty()) {
        Location p = pq.top().second;
        if (p == dst) {
            Location t = dst;
            while (t != src) {
                path.push_back(t);
                t = edge_to[t.first][t.second];
            }
            path.push_back(src);
        }
        pq.pop();
        if (s.find(p) != s.end()) {
            continue;
        }
        s.insert(p);

        for (auto& dir : DIRACTIONS) {
            Location q{p.first + dir.first, p.second + dir.second};
            if (q.first < 0 || q.first >= data_.size() || q.second < 0 || q.second >= data_[0].size() ||
                data_[q.first][q.second] == LocationType::OBSTACLE) {
                continue;
            }
            double weight = h(p, q);
            switch (data_[q.first][q.second]) {
                case LocationType::STREAM:
                    weight += 2;
                    break;
                case LocationType::DESERT:
                    weight += 4;
                    break;
                default:
                    break;
            }
            if (dist_to[p.first][p.second] + weight < dist_to[q.first][q.second]) {
                dist_to[q.first][q.second] = dist_to[p.first][p.second] + weight;
                edge_to[q.first][q.second] = p;
                pq.push({dist_to[q.first][q.second] + h(q, dst), q});
            }
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
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