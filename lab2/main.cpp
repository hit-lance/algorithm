#include <opencv2/highgui.hpp>
#include <queue>

#include "map.h"
#include "visualization.h"

int main() {
    std::ifstream fin("../data/map1.txt");
    int m, n;
    fin >> m >> n;

    auto data = std::vector<std::vector<LocationType>>(m, std::vector<LocationType>(n));

    // initiate cv::Mat
    cv::Mat map_image = InitMat(m, n);

    for (const auto e : {LocationType::OBSTACLE, LocationType::STREAM, LocationType::DESERT}) {
        size_t t;
        fin >> t;
        for (int i = 0; i < t; ++i) {
            fin >> m >> n;
            data[m][n] = e;
            Rectangle(map_image, m, n, {128, 128, 128});
        }
    }

    Map map(data);
    Location src{8, 3}, dst{9, 14};
    auto path = map.AStar(src, dst);

    Grid(map_image);
    Path(map_image, path);
    Circle(map_image, src, {0, 255, 0});
    Circle(map_image, dst, {0, 0, 255});

    cv::imwrite("map.png", map_image);
    return (0);
}
