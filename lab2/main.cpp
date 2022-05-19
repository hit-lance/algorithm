#include <opencv2/highgui.hpp>
#include <queue>

#include "map.h"
#include "visualization.h"

int main() {
    std::ifstream fin("../data/map2.txt");
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

            cv::Scalar color;
            switch (e) {
                case LocationType::OBSTACLE:
                    color = {128, 128, 128};
                    break;
                case LocationType::STREAM:
                    color = {255, 144, 30};
                    break;
                case LocationType::DESERT:
                    color = {96, 164, 244};
                    break;
                default:
                    break;
            }
            Rectangle(map_image, m, n, color);
        }
    }

    Map map(data);
    Grid(map_image);

    // Location src{8, 3}, dst{9, 14};
    Location src{10, 4}, dst{0, 35};
    auto path = map.AStar(src, dst);
    Path(map_image, path);

    Circle(map_image, src, {50, 205, 50});
    Circle(map_image, dst, {0, 69, 255});

    cv::imwrite("map.png", map_image);
    return (0);
}
