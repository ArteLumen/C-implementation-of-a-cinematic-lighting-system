#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

struct Vector3 {
    float x, y, z;
};

struct ColorRGB {
    float r, g, b;
};

namespace {

const float kPi = 3.14159265358979323846f;
const float kMinDistance = 0.1f;   // Avoids division by zero very close to the light

float clampf(float value, float lo, float hi) {
    return std::max(lo, std::min(value, hi));
}

float distanceBetween(const Vector3& a, const Vector3& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Approximates the color of a blackbody radiator (e.g. tungsten, daylight)
// for a given color temperature. Returns RGB in the 0..1 range.
ColorRGB kelvinToRGB(float kelvin) {
    float t = clampf(kelvin, 1000.0f, 40000.0f) / 100.0f;
    float r, g, b;

    if (t <= 66.0f) {
        r = 255.0f;
        g = 99.4708025861f * std::log(t) - 161.1195681661f;
    } else {
        r = 329.698727446f * std::pow(t - 60.0f, -0.1332047592f);
        g = 288.1221695283f * std::pow(t - 60.0f, -0.0755148492f);
    }

    if (t >= 66.0f) {
        b = 255.0f;
    } else if (t <= 19.0f) {
        b = 0.0f;
    } else {
        b = 138.5177312231f * std::log(t - 10.0f) - 305.0447927307f;
    }

    ColorRGB color = {
        clampf(r, 0.0f, 255.0f) / 255.0f,
        clampf(g, 0.0f, 255.0f) / 255.0f,
        clampf(b, 0.0f, 255.0f) / 255.0f
    };
    return color;
}

// Smooth window that fades the light to exactly zero at 'range',
// so there is no visible cutoff edge. Result is in 0..1.
float rangeWindow(float distance, float range) {
    float ratio = distance / range;
    float ratio2 = ratio * ratio;
    float w = clampf(1.0f - ratio2 * ratio2, 0.0f, 1.0f);
    return w * w;
}

} // namespace

class CinematicLight {
private:
    std::string lightName;
    Vector3 position;
    ColorRGB color;
    float lumens;       // Total light output of the source (luminous flux)
    float range;        // Distance at which the light fades to zero (meters)
    float kelvin;

public:
    CinematicLight(const std::string& name, const Vector3& pos, float lumensOutput, float maxRange)
        : lightName(name),
          position(pos),
          color{1.0f, 1.0f, 1.0f},
          lumens(std::max(0.0f, lumensOutput)),
          range(std::max(maxRange, kMinDistance)),
          kelvin(6500.0f) {}

    // Getters
    const std::string& getName() const { return lightName; }
    const Vector3& getPosition() const { return position; }
    const ColorRGB& getColor() const { return color; }
    float getLumens() const { return lumens; }
    float getRange() const { return range; }

    // Smooth color temperature (1000K - 40000K), e.g. 3200K tungsten, 5600K daylight
    void setColorTemperature(float newKelvin) {
        kelvin = clampf(newKelvin, 1000.0f, 40000.0f);
        color = kelvinToRGB(kelvin);
    }

    // Illuminance in lux received at a point (assumes the surface faces the light).
    // Point light model: luminous intensity I = lumens / (4*pi) candela,
    // illuminance E = I / d^2 (inverse square law), faded smoothly to 0 at 'range'.
    float calculateIlluminance(const Vector3& target) const {
        float distance = std::max(distanceBetween(position, target), kMinDistance);
        if (distance >= range) {
            return 0.0f;
        }

        float candela = lumens / (4.0f * kPi);
        float lux = candela / (distance * distance);
        return lux * rangeWindow(distance, range);
    }

    // Colored light arriving at a point: light color scaled by illuminance (lux).
    ColorRGB calculateLightColor(const Vector3& target) const {
        float lux = calculateIlluminance(target);
        ColorRGB result = { color.r * lux, color.g * lux, color.b * lux };
        return result;
    }

    void printDetails() const {
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "--- Light Specs: " << lightName << " ---\n";
        std::cout << "Position    : (" << position.x << ", " << position.y << ", " << position.z << ")\n";
        std::cout << "Output      : " << lumens << " lumens\n";
        std::cout << "Range       : " << range << " m\n";
        std::cout << "Temperature : " << kelvin << " K\n";
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

    float lux = keyLight.calculateIlluminance(actorPosition);
    ColorRGB lit = keyLight.calculateLightColor(actorPosition);

    std::cout << "\nIlluminance at Actor Position: " << lux << " lux\n";
    std::cout << "Colored light at Actor        : (" << lit.r << ", " << lit.g << ", " << lit.b << ")\n";

    // Falloff demo: the light fades smoothly to zero at the range limit
    std::cout << "\nFalloff along a line from the light:\n";
    const float distances[] = {1.0f, 5.0f, 10.0f, 15.0f, 19.0f, 20.0f, 25.0f};
    for (float d : distances) {
        Vector3 target = {keyLightPos.x, keyLightPos.y, keyLightPos.z + d};
        std::cout << "  " << std::setw(5) << d << " m -> "
                  << keyLight.calculateIlluminance(target) << " lux\n";
    }

    return 0;
}
