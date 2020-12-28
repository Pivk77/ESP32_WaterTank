#include "HX711.h"

class Sensor
{
private:
    HX711 pressure;
    long valueEmpty;
    long reading;
    long calibrated_min, calibrated_max;
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

    long calibrateMin()
    {
        calibrated_min = 0;
        for (int i = 0; i < 100; i++)
        {
            calibrated_min += pressure.read();
        }
        calibrated_min = calibrated_min / 100;
        Serial.println("CalibratedMin:" + calibrated_min);
        return calibrated_min;
    }
    long calibrateMax()
    {
        calibrated_max = 0;
        for (int i = 0; i < 100; i++)
        {
            calibrated_max += pressure.read();
        }
        calibrated_max = calibrated_max / 100;
        Serial.println("CalibratedMax:" + calibrated_max);
        return calibrated_max;
    }
    long raw()
    {
        return pressure.read() / 1000;
    }

    long height()
    {
        //do some magic here(mapped value)
        return mapf(raw(), calibrated_min, calibrated_max, 0, 150);
    }
    double volume()
    {
        return (height() * PI * 3600) / 1000000.0;
    }
};