# C-implementation-of-a-cinematic-lighting-system
# Cinematic Lighting Simulator (C++)

A lightweight, physics-based C++ simulation engine designed for virtual cinematography and lighting calculations. This project models real-world photometric behaviors—such as inverse-square light attenuation and Kelvin color temperature conversion—to help filmmakers, virtual production artists, and developers calculate precise lighting setups.

---

## Features

- **Physics-Based Attenuation:** Computes accurate light falloff over distance using quadratic approximation (Inverse-Square Law).
- **Kelvin Color Temperature Mapping:** Easily simulate and switch between cinematic light color balances (e.g., Warm Tungsten at $3200\text{K}$ vs. Cool Daylight at $5600\text{K}$).
- **Clean Code Architecture:** Modular object-oriented design using modern C++ standards.
- **Self-Documented Math:** Optimized for integration into custom rendering pipelines, game engine plugins, or hardware control scripts.

---

## Project Structure

```text
├── main.cpp          # Core implementation and execution examples
└── README.md         # Project documentation
