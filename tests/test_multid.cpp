#include "FastDTW-x/Classes/DTW.h"
#include "FastDTW-x/Classes/FastDTW.h"
#include "FastDTW-x/Classes/EuclideanDistance.h"
#include <array>
#include <iostream>
#include <vector>

int main() {
    using namespace fastdtw;
    std::vector<std::array<double, 2>> seriesA{{{0.0, 1.0}, {1.0, 2.0}, {2.0, 3.0}, {3.0, 4.5}}};
    std::vector<std::array<double, 2>> seriesB{{{0.0, 1.2}, {1.2, 2.1}, {2.0, 3.2}, {3.5, 4.8}}};

    TimeSeries<double, 2> fixedA;
    TimeSeries<double, 2> fixedB;
    for (std::size_t i = 0; i < seriesA.size(); ++i) {
        fixedA.addLast(static_cast<double>(i), TimeSeriesPoint<double, 2>(seriesA[i].data()));
        fixedB.addLast(static_cast<double>(i), TimeSeriesPoint<double, 2>(seriesB[i].data()));
    }

    TimeSeries<double, 0> dynamicA(2);
    TimeSeries<double, 0> dynamicB(2);
    for (std::size_t i = 0; i < seriesA.size(); ++i) {
        TimeSeriesPoint<double, 0> pointA(seriesA[i].data(), 2);
        TimeSeriesPoint<double, 0> pointB(seriesB[i].data(), 2);
        dynamicA.addLast(static_cast<double>(i), pointA);
        dynamicB.addLast(static_cast<double>(i), pointB);
    }

    EuclideanDistance distance;
    const double fastFixed = FAST::getWarpDistBetween(fixedA, fixedB, distance);
    const double fastDynamic = FAST::getWarpDistBetween(dynamicA, dynamicB, distance);
    const double exact = STRI::getWarpInfoBetween(fixedA, fixedB, distance).getDistance();

    std::cout << "fastdtw_distance=" << fastFixed << '\n';
    std::cout << "fastdtw_dynamic_distance=" << fastDynamic << '\n';
    std::cout << "dtw_distance=" << exact << '\n';

    return 0;
}
