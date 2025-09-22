//
//  TimeSeriesPoint.h
//  FastDTW-x
//
//  Created by Melo Yao on 12/3/13.
//  Copyright (c) 2013 melo.yao. All rights reserved.
//

#ifndef __FastDTW_x__TimeSeriesPoint__
#define __FastDTW_x__TimeSeriesPoint__
#include "Foundation.h"
#include "FDAssert.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <vector>
FD_NS_START
using namespace std;

//Fixed dimension TimeSeriesPoint template
template <typename ValueType, JInt nDimension>
class MeasurementVector
{
    vector<ValueType> value;

    void assignFromPointer(const ValueType* meas)
    {
        copy(meas, meas + nDimension, value.begin());
    }

public:
    MeasurementVector():value(nDimension)
    {
    }

    explicit MeasurementVector(const ValueType* meas):value(nDimension)
    {
        assignFromPointer(meas);
    }

    explicit MeasurementVector(const vector<ValueType>& meas):value(nDimension)
    {
        setMeasurements(meas);
    }

    MeasurementVector(initializer_list<ValueType> meas):value(nDimension)
    {
        setMeasurements(meas);
    }

    void setMeasurements(const ValueType* meas, JInt nDim = nDimension)
    {
        FDASSERT0(nDim == nDimension, "ERROR:  cannot change dimensionality of a fixed-dimension measurement vector.");
        assignFromPointer(meas);
    }

    void setMeasurements(const vector<ValueType>& meas)
    {
        FDASSERT0(meas.size() == nDimension, "ERROR:  measurement vector supplied with incorrect dimensionality.");
        copy(meas.begin(), meas.end(), value.begin());
    }

    void setMeasurements(initializer_list<ValueType> meas)
    {
        FDASSERT0(meas.size() == nDimension, "ERROR:  measurement vector supplied with incorrect dimensionality.");
        copy(meas.begin(), meas.end(), value.begin());
    }

    void setDynamicMeasurements(const ValueType* meas, JInt nDim)
    {
        setMeasurements(meas, nDim);
    }

    JInt size() const
    {
        return static_cast<JInt>(value.size());
    }

    ValueType operator[](JInt index) const
    {
        return value[index];
    }

    ValueType& operator[](JInt index)
    {
        return value[index];
    }

    bool operator==(const MeasurementVector<ValueType,nDimension>& mv) const
    {
        return  value == mv.value;
    }

    bool operator<(const MeasurementVector<ValueType, nDimension>& mv) const
    {
        return value < mv.value;
    }

    void print(ostream& stream) const
    {
        stream<<"p(";
        for (JInt i = 0; i<value.size(); ++i) {
            stream << value[i] << ",";
        }
        stream <<")";
    }
};

//1 dimension TimeSeriesPoint specification
template <typename ValueType>
class MeasurementVector<ValueType, 1> {
    
    ValueType value;
    
public:
    MeasurementVector():value(0)
    {
    }

    explicit MeasurementVector(const ValueType* meas):value(*meas)
    {
    }

    explicit MeasurementVector(const vector<ValueType>& meas):value(0)
    {
        setMeasurements(meas);
    }

    MeasurementVector(initializer_list<ValueType> meas):value(0)
    {
        setMeasurements(meas);
    }

    void setMeasurements(const ValueType* meas, JInt nDim = 1)
    {
        FDASSERT0(nDim == 1, "ERROR:  cannot change dimensionality of a fixed-dimension measurement vector.");
        value = *meas;
    }

    void setMeasurements(const vector<ValueType>& meas)
    {
        FDASSERT0(meas.size() == 1, "ERROR:  measurement vector supplied with incorrect dimensionality.");
        value = meas[0];
    }

    void setMeasurements(initializer_list<ValueType> meas)
    {
        FDASSERT0(meas.size() == 1, "ERROR:  measurement vector supplied with incorrect dimensionality.");
        value = *meas.begin();
    }

    void setDynamicMeasurements(const ValueType* meas, JInt nDim)
    {
        setMeasurements(meas, nDim);
    }
    
    JInt size() const
    {
        return 1;
    }
    
    ValueType operator[](JInt index) const
    {
        return value;
    }

    
    ValueType& operator[](JInt index)
    {
        return value;
    }
    
    bool operator==(const MeasurementVector<ValueType,1>& mv) const
    {
        return  value == mv.value;
    }

    bool operator<(const MeasurementVector<ValueType, 1>& mv) const
    {
        return value < mv.value;
    }
    
    void print(ostream& stream) const
    {
        stream<<"p("<<value<<")";
    }
};


//Dynamic dimension TimeSeriesPoint specification
template <typename ValueType>
class MeasurementVector<ValueType, 0> {
    
    vector<ValueType> value;
    
public:
    MeasurementVector():value()
    {
    }

    explicit MeasurementVector(const ValueType* meas):value()
    {
    }

    explicit MeasurementVector(const vector<ValueType>& meas):value(meas)
    {
    }

    MeasurementVector(initializer_list<ValueType> meas):value(meas)
    {
    }

    void setMeasurements(const ValueType* meas, JInt nDim)
    {
        value.assign(meas, meas + nDim);
    }

    void setMeasurements(const vector<ValueType>& meas)
    {
        value = meas;
    }

    void setMeasurements(initializer_list<ValueType> meas)
    {
        value.assign(meas.begin(), meas.end());
    }

    void setDynamicMeasurements(const ValueType* meas, JInt nDim)
    {
        setMeasurements(meas, nDim);
    }

    JInt size() const
    {
        return static_cast<JInt>(value.size());
    }

    ValueType operator[](JInt index) const
    {
        return value[index];
    }

    ValueType& operator[](JInt index)
    {
        return value[index];
    }

    bool operator==(const MeasurementVector<ValueType,0>& mv) const
    {
        return  value == mv.value;
    }

    bool operator<(const MeasurementVector<ValueType, 0>& mv) const
    {
        return value < mv.value;
    }

    void print(ostream& stream) const
    {
        stream<<"p(";
        for (JInt i = 0; i<value.size(); ++i) {
            stream << value[i] << ",";
        }
        stream <<")";
    }
};

template <typename ValueType,JInt nDimension>
class TimeSeriesPoint {
    MeasurementVector<ValueType, nDimension> _measurements;

public:
    TimeSeriesPoint():_measurements()
    {
    }

    explicit TimeSeriesPoint(const ValueType* meas):_measurements()
    {
        if (nDimension == 0) {
            FDASSERT0(false, "ERROR:  dynamic TimeSeriesPoint construction requires explicit dimensionality.");
        }
        else {
            _measurements.setMeasurements(meas, nDimension);
        }
    }

    TimeSeriesPoint(const ValueType* meas, JInt nDim):_measurements()
    {
        _measurements.setMeasurements(meas, nDim);
    }

    explicit TimeSeriesPoint(const vector<ValueType>& meas):_measurements(meas)
    {
    }

    TimeSeriesPoint(initializer_list<ValueType> meas):_measurements(meas)
    {
    }

    ValueType get(JInt dimension) const
    {
        return _measurements[dimension];
    }

    void setMeasurements(const ValueType* meas, JInt nDim)
    {
        _measurements.setMeasurements(meas, nDim);
    }

    void setMeasurements(const vector<ValueType>& meas)
    {
        _measurements.setMeasurements(meas);
    }

    void setMeasurements(initializer_list<ValueType> meas)
    {
        _measurements.setMeasurements(meas);
    }

    void setDynamicMeasurements(const ValueType* meas, JInt nDim)
    {
        _measurements.setDynamicMeasurements(meas,nDim);
    }

    void set(JInt dimension,ValueType newValue)
    {
        _measurements[dimension] = newValue;
    }

    JInt size() const
    {
        return _measurements.size();
    }

    const MeasurementVector<ValueType, nDimension>* toArray() const
    {
        return &_measurements;
    }

    bool operator==(const TimeSeriesPoint& p) const
    {
        return _measurements == p._measurements;
    }

    bool operator<(TimeSeriesPoint& p)
    {
        return _measurements < p._measurements;
    }

    ~TimeSeriesPoint()
    {
    }

    void print(ostream& stream) const
    {
        _measurements.print(stream);
    }
};

FD_NS_END
#endif /* defined(__FastDTW_x__TimeSeriesPoint__) */
