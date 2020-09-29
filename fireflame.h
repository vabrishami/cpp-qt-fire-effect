#ifndef FIRE_H
#define FIRE_H

#include "qglobal.h"

enum WindDir { NOWIND = 0,
    WEST = 1,
    EAST = -1 };
const int palleteSize = 256;

class Fire {
public:
    Fire(int _width, int _height);
    ~Fire();

    // Routine to randomized array bottom with fumes
    void startFire();
    // Main routine to propagate the fire
    void updateFire();
    // Set and return a value from fire array
    void setArray(int i, int j, int val);
    int getArray(int i, int j);
    // Adjust the height of the fire
    void increaseDecay();
    void decreaseDecay();
    // Set wind direction
    void setWindDirection(WindDir _windDirection);
    // Methods for getting height and width of the image
    int getWidth();
    int getHeight();

private:
    // 2D array to keep fire intensity indices
    int** fireArray;
    int width;
    int height;
    double decay = 4.02;
    WindDir windDirection = NOWIND;
    // Number of colors in the pallete
    int coloGradientSize = palleteSize - 6;
    // Method to allocate and initialize the fire array
    void allocateArray();
};
#endif

