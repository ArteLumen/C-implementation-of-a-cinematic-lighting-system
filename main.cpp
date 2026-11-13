#include <iostream>
#include <vector>
#include "Vector3.h"
#include "CinematicLight.h"

int main() {
    std::vector<CinematicLight> sceneLights;

    // 1. Standard Point Light (Key Light)
    CinematicLight keyLight("Key Light (Tungsten)", {0.0f, 3.0f, -2.0f}, 1200.0f, 20.0f);
    keyLight.setColorTemperature(3200.0f);

    // 2. Spotlight (Overhead Stage Spotlight)
    CinematicLight spotLight("Stage Spotlight", {0.0f, 5.0f, 0.0f}, 2500.0f, 15.0f);
    spotLight.setColorTemperature(5600.0f);
    spotLight.setSpotProperties({0.0f, -1.0f, 0.0f}, 35.0f); // Pointing down, 35-degree cone

    sceneLights.push_back(keyLight);
    sceneLights.push_back(spotLight);

    Vector3 actorPosition = {0.0f, 0.0f, 0.0f};

    std::cout << "=== Advanced Cinematic Lighting Simulation ===\n\n";

    for (const auto& light : sceneLights) {
        light.printDetails();
        float receivedLight = light.calculateAttenuation(actorPosition);
        std::cout << "Received Light Intensity at Actor Position: " 
                  << receivedLight << " Lux\n\n";
    }

    return 0;
}
