#include "HX711.h"

class Sensor
{
private:
    HX711 pressure;
    long valueEmpty;
    double calibrated_min, calibrated_max;
    //define calibration points here

    double mapf(double x, double in_min, double in_max, double out_min, double out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

public:
    Sensor(int PS_DOUT_PIN, int PS_SCK_PIN)
    {
        pressure.begin(PS_DOUT_PIN, PS_SCK_PIN);
    }

    bool calibrate()
    {
        //some magic here
        return false;
    }
    long raw()
    {
        return pressure.read() / 1000;
    }

    long height()
    {
        //do some magic here(mapped value)
        return mapf(raw(), 430, 1500, 0, 180);
    }
    long volume()
    {
        return (height() * PI * 3600) / 1000000;
    }
};