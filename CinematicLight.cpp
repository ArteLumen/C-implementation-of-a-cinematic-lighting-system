#include "CinematicLight.h"
#include <iostream>
#include <cmath>

CinematicLight::CinematicLight(const std::string& name, const Vector3& pos, float lumens, float maxRange)
    : lightName(name), position(pos), intensity(lumens), range(maxRange), isSpotlight(false), direction{0.0f, -1.0f, 0.0f}, cutOffAngle(45.0f) {
    color = {1.0f, 1.0f, 1.0f};
}

void CinematicLight::setColorTemperature(float kelvin) {
    if (kelvin <= 3200.0f) {
        color = {1.0f, 0.72f, 0.42f}; // Tungsten Warmth
    } else if (kelvin >= 6500.0f) {
        color = {0.8f, 0.9f, 1.0f};   // Daylight Coolness
    } else {
        color = {1.0f, 0.95f, 0.88f}; // Neutral
    }
}

void CinematicLight::setSpotProperties(const Vector3& dir, float angle) {
    isSpotlight = true;
    direction = dir.normalize();
    cutOffAngle = angle;
}

float CinematicLight::calculateAttenuation(const Vector3& targetPosition) const {
    float distance = position.distanceTo(targetPosition);

    // Early exit if out of range
    if (distance > range) {
        return 0.0f;
    }

    // Quadratic attenuation formula
    float attenuation = intensity / (1.0f + 0.09f * distance + 0.032f * (distance * distance));

    // If it's a spotlight, calculate cone restriction
    if (isSpotlight) {
        Vector3 lightToTarget = {
            targetPosition.x - position.x,
            targetPosition.y - position.y,
            targetPosition.z - position.z
        };
        lightToTarget = lightToTarget.normalize();

        float theta = direction.dot(lightToTarget);
        float cutOffCosine = std::cos(cutOffAngle * 3.14159265f / 180.0f);

        if (theta < cutOffCosine) {
            return 0.0f; // Outside the spotlight beam
        }
        
        attenuation *= theta; // Soften based on angle alignment
    }

    return attenuation;
}

void CinematicLight::printDetails() const {
    std::cout << "--- Light Specs: " << lightName << " ---\n";
    std::cout << "Position    : (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    std::cout << "Type        : " << (isSpotlight ? "Spotlight" : "Point Light") << "\n";
    std::cout << "Intensity   : " << intensity << " Lumens\n";
    std::cout << "RGB Color   : (" << color.r << ", " << color.g << ", " << color.b << ")\n";
    std::cout << "-------------------------------------------\n";
}
