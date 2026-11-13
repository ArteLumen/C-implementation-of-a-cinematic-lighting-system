#ifndef CINEMATIC_LIGHT_H
#define CINEMATIC_LIGHT_H

#include <string>
#include "Vector3.h"

struct ColorRGB {
    float r, g, b;
};

class CinematicLight {
private:
    std::string lightName;
    Vector3 position;
    ColorRGB color;      
    float intensity;     
    float range;        

    // Spotlight properties
    bool isSpotlight;
    Vector3 direction;
    float cutOffAngle; // in degrees

public:
    CinematicLight(const std::string& name, const Vector3& pos, float lumens, float maxRange);

    void setColorTemperature(float kelvin);
    void setSpotProperties(const Vector3& dir, float angle);
    
    float calculateAttenuation(const Vector3& targetPosition) const;
    void printDetails() const;
};

#endif2. CinematicLight.h
