#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
public:
    LineSensor();
    LineSensor(const int threshold, const int sensorPin);

    int getThreshold();
    void setThreshold(const int threshold);

    int getSensorPin();
    void setSensorPin(const int sensorPin);

    bool status() const;

private:
    int threshold;
    int sensorPin;
};

#endif // LINESENSOR_H
