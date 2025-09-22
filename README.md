FastDTW-x
=========

C++ porting of Stan Salvador's FastDTW

Usage:
iOS,use CocoaPods,add line in podfile:
pod 'FastDTW-x'
Other platform,Import all source files in Classes folder.

Sample code:

    #include "DTW.h"
    #include "FastDTW.h"
    #include "EuclideanDistance.h"
    #include <iostream>

    using namespace fastdtw;

    extern double *sample1;
    extern double *sample2;
    extern int sampleLength;
    
    void testDTW()
    {
        TimeSeries<double,1> tsI;
        for (int i = 0; i<sampleLength; ++i) {
            tsI.addLast(i, TimeSeriesPoint<double,1>(sample1+i));
        }
    
        TimeSeries<double,1> tsJ;
        for (int i = 0;i<sampleLength; ++i)
        {
            tsJ.addLast(i, TimeSeriesPoint<double,1>(sample2+i));
        }
    
        TimeWarpInfo<double> info =  STRI::getWarpInfoBetween(tsI,tsJ,EuclideanDistance());
        printf("Warp Distance by DTW:%lf\n",info.getDistance());
        info.getPath()->print(std::cout);
    }

    void testFastDTW()
    {
        TimeSeries<double,1> tsI;
        for (int i = 0; i<sampleLength; ++i) {
            tsI.addLast(i, TimeSeriesPoint<double,1>(sample1+i));
        }
    
        TimeSeries<double,1> tsJ;
        for (int i = 0;i<sampleLength; ++i)
        {
            tsJ.addLast(i, TimeSeriesPoint<double,1>(sample2+i));
        }
    
        TimeWarpInfo<double> info =  FAST::getWarpInfoBetween(tsI,tsJ,EuclideanDistance());
        printf("Warp Distance by DTW:%lf\n",info.getDistance());
        info.getPath()->print(std::cout);
    }

多维序列示例：

    std::vector<std::array<double, 2>> left{{{0.0, 1.0}, {1.0, 2.0}}};
    std::vector<std::array<double, 2>> right{{{0.0, 1.2}, {1.1, 2.1}}};

    TimeSeries<double, 2> fixedDim;
    for (std::size_t i = 0; i < left.size(); ++i) {
        fixedDim.addLast(static_cast<double>(i), TimeSeriesPoint<double, 2>(left[i].data()));
    }

    TimeSeries<double, 0> dynamicDim(2); // 运行时设定维度
    for (std::size_t i = 0; i < right.size(); ++i) {
        TimeSeriesPoint<double, 0> point(right[i].data(), 2);
        dynamicDim.addLast(static_cast<double>(i), point);
    }

    EuclideanDistance dist;
    double d = FAST::getWarpDistBetween(fixedDim, dynamicDim, dist);

