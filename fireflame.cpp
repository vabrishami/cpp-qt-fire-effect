#include "fireflame.h"

Fire::Fire(int _width, int _height)
{
    width = _width;
    height = _height;
    allocateArray();
}

Fire::~Fire()
{
    for (int i = 0; i < height; ++i) {
        delete[] fireArray[i];
    }
    delete[] fireArray;
}

void Fire::allocateArray()
{
    fireArray = new int*[height];
    for (int i = 0; i < height; i++) {
        fireArray[i] = new int[width];
        for (int j = 0; j < width; j++)
            fireArray[i][j] = 0;
    }
}

/* Randomly assigned lowest and highest intensity 
values to the last row of fire array*/
void Fire::startFire()
{
    for (int i = 0; i < width; i++)
        fireArray[height - 1][i] = rand() % coloGradientSize;
}

void Fire::setArray(int i, int j, int val)
{

    if (i >= 0 && i < height && j >= 0 && j < width)
        fireArray[i][j] = val;
}

int Fire::getArray(int i, int j)
{
    if (i >= 0 && i < height && j >= 0 && j < width)
        return fireArray[i][j];
    return 0;
}

void Fire::increaseDecay()
{
    decay += 0.01;
}

void Fire::decreaseDecay()
{
    if (decay > 4.0)
        decay -= 0.01;
}

void Fire::setWindDirection(WindDir _windDirection)
{
    windDirection = _windDirection;
}

int Fire::getWidth()
{
    return width;
}

int Fire::getHeight()
{
    return height;
}

/* This method compute the intensity index by averaging 
{(X, Y+1), (X+1, Y+1), (X-1, Y+1), (X, Y+2). Wind will 
remove even  (X+1, Y+1) or (X-1, Y+1) depending on the 
wind direction.*/
void Fire::updateFire()
{
    int height1, height2, width0, width1, widthM1;
    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            // Compute the index of the neighbors
            height1 = i + 1;
            height2 = (i + 2) % height;
            width0 = j;
            width1 = (j + 1) % width;
            widthM1 = (j - 1 + width) % width;

            fireArray[i][j] = fireArray[height1][width0] + fireArray[height2][width0];
            // If WEST just use (X+1, Y+1) as third value
            if (windDirection == WEST)
                fireArray[i][j] += fireArray[height1][width1];
            // If WEST just use (X-1, Y+1) as third value
            else if (windDirection == EAST)
                fireArray[i][j] += fireArray[height1][widthM1];
            else
                fireArray[i][j] += fireArray[height1][width1] + fireArray[height1][widthM1];
            // If wind, then divide by decay-1
            fireArray[i][j] /= (windDirection != NOWIND ? decay - 1 : decay);
        }
    }
}
