#include "map.h"

#include <algorithm>
#include <cmath>
#include <queue>
#include <set>

Map::Map(const std::vector<std::vector<LocationType>>& data) { data_ = data; }

std::vector<Location> Map::AStar(const Location& src, const Location& dst) const {
    std::vector<Location> path;
    size_t m = data_.size(), n = data_[0].size();

    std::vector<std::vector<double>> dist(m, std::vector<double>(n, std::numeric_limits<double>::max()));
    std::vector<std::vector<Location>> edge(m, std::vector<Location>(n));

    auto h = [](const Location& a, const Location& b) {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    };

    std::priority_queue<std::pair<double, Location>, std::vector<std::pair<double, Location>>,
                        std::greater<std::pair<double, Location>>>
        pq;
    std::set<Location> s;

    dist[src.first][src.second] = 0;
    pq.push({h(src, dst), src});

    while (!pq.empty()) {
        Location p = pq.top().second;
        if (p == dst) {
            Location t = dst;
            while (t != src) {
                path.push_back(t);
                t = edge[t.first][t.second];
            }
            path.push_back(src);
            break;
        }
        pq.pop();
        if (s.find(p) != s.end()) {
            continue;
        }
        s.insert(p);

        for (auto& dir : DIRACTIONS) {
            Location q{p.first + dir.first, p.second + dir.second};
            if (q.first < 0 || q.first >= m || q.second < 0 || q.second >= n ||
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
            if (dist[p.first][p.second] + weight < dist[q.first][q.second]) {
                dist[q.first][q.second] = dist[p.first][p.second] + weight;
                edge[q.first][q.second] = p;
                pq.push({dist[q.first][q.second] + h(q, dst), q});
            }
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::pair<std::vector<Location>, std::vector<Location>> Map::BiAStar(const Location& src, const Location& dst) const {
    std::vector<Location> path1, path2;
    size_t m = data_.size(), n = data_[0].size();

    std::vector<std::vector<double>> dist1(m, std::vector<double>(n, std::numeric_limits<double>::max()));
    std::vector<std::vector<double>> dist2(m, std::vector<double>(n, std::numeric_limits<double>::max()));
    std::vector<std::vector<Location>> edge1(m, std::vector<Location>(n));
    std::vector<std::vector<Location>> edge2(m, std::vector<Location>(n));

    auto h = [](const Location& a, const Location& b) {
        return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
    };

    std::priority_queue<std::pair<double, Location>, std::vector<std::pair<double, Location>>,
                        std::greater<std::pair<double, Location>>>
        pq1, pq2;
    std::set<Location> s1, s2;

    dist1[src.first][src.second] = 0;
    dist2[dst.first][dst.second] = 0;
    pq1.push({h(src, dst), src});
    pq2.push({h(src, dst), dst});

    while (!pq1.empty() && !pq2.empty()) {
        Location p1 = pq1.top().second, p2 = pq2.top().second;

        if (s1.find(p2) != s1.end() || s2.find(p1) != s2.end()) {
            Location p = (s1.find(p2) != s1.end()) ? p2 : p1, t;

            t = p;
            while (t != src) {
                path1.push_back(t);
                t = edge1[t.first][t.second];
            }
            path1.push_back(src);

            t = p;
            while (t != dst) {
                path2.push_back(t);
                t = edge2[t.first][t.second];
            }
            path2.push_back(dst);
            break;
        }

        if (s1.find(p1) != s1.end()) {
            pq1.pop();
            continue;
        }
        if (s2.find(p2) != s2.end()) {
            pq2.pop();
            continue;
        }
        pq1.pop();
        pq2.pop();
        s1.insert(p1);
        s2.insert(p2);

        for (auto& dir : DIRACTIONS) {
            Location q{p1.first + dir.first, p1.second + dir.second};
            if (q.first < 0 || q.first >= m || q.second < 0 || q.second >= n ||
                data_[q.first][q.second] == LocationType::OBSTACLE) {
                continue;
            }
            double weight = h(p1, q);
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
            if (dist1[p1.first][p1.second] + weight < dist1[q.first][q.second]) {
                dist1[q.first][q.second] = dist1[p1.first][p1.second] + weight;
                edge1[q.first][q.second] = p1;
                pq1.push({dist1[q.first][q.second] + h(q, dst), q});
            }
        }

        for (auto& dir : DIRACTIONS) {
            Location q{p2.first + dir.first, p2.second + dir.second};
            if (q.first < 0 || q.first >= m || q.second < 0 || q.second >= n ||
                data_[q.first][q.second] == LocationType::OBSTACLE) {
                continue;
            }
            double weight = h(p2, q);
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
            if (dist2[p2.first][p2.second] + weight < dist2[q.first][q.second]) {
                dist2[q.first][q.second] = dist2[p2.first][p2.second] + weight;
                edge2[q.first][q.second] = p2;
                pq2.push({dist2[q.first][q.second] + h(q, src), q});
            }
        }
    }
    std::reverse(path1.begin(), path1.end());
    std::reverse(path2.begin(), path2.end());
    return {path1, path2};
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