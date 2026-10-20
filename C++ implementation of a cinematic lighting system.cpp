#include <iostream>
#include <cmath>
#include <string>

struct Vector3 {
    float x, y, z;

};

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

public:

    CinematicLight(const std::string& name, const Vector3& pos, float lumens, float maxRange)
        : lightName(name), position(pos), intensity(lumens), range(maxRange) {
        color = {1.0f, 1.0f, 1.0f};
    }

    void setColorTemperature(float kelvin) {
        if (kelvin <= 3200.0f) {
          
            color = {1.0f, 0.72f, 0.42f}; 
          
        } else if (kelvin >= 6500.0f) {
          
            color = {0.8f, 0.9f, 1.0f};   
        } else {
            color = {1.0f, 0.95f, 0.88f}; 
        }
    }

    float calculateAttenuation(const Vector3& targetPosition) const {
        float dx = position.x - targetPosition.x;
        float dy = position.y - targetPosition.y;
        float dz = position.z - targetPosition.z;
        float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

        if (distance > range) {
            return 0.0f;
        }

        float attenuation = intensity / (1.0f + 0.09f * distance + 0.032f * (distance * distance));
        return attenuation;
    }

    void printDetails() const {
        std::cout << "--- Light Specs: " << lightName << " ---\n";
        std::cout << "Position    : (" << position.x << ", " << position.y << ", " << position.z << ")\n";
        std::cout << "Intensity   : " << intensity << " Lumens\n";
        std::cout << "RGB Color   : (" << color.r << ", " << color.g << ", " << color.b << ")\n";
        std::cout << "-------------------------------------------\n";
    }
};

int main() {
  
    Vector3 keyLightPos = {0.0f, 3.0f, -2.0f};
  
    CinematicLight keyLight("Key Light (Tungsten)", keyLightPos, 1200.0f, 20.0f);

    keyLight.setColorTemperature(3200.0f);
  
    keyLight.printDetails();

    Vector3 actorPosition = {0.0f, 0.0f, 0.0f};

    float receivedLight = keyLight.calculateAttenuation(actorPosition);

    std::cout << "Received Light Intensity at Actor Position: " 
              << receivedLight << " Lux\n";

    return 0;
}
