#pragma once
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For matrix transformations
#include <glm/gtc/random.hpp> // For random number generation

// General ray
struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;
  float tMin, tMax;

  Ray() = default;

  Ray(
    const glm::vec3& o,
    const glm::vec3& d,
    float tMin = 0.0001f,
    float tMax = FLT_MAX
  ) :
    origin(o),
    direction(glm::normalize(d)),
    tMin(tMin),
    tMax(tMax) {}
};

class Material;

// Intersection point
struct Intersection {
  glm::vec3 position; // Intersection
  glm::vec3 normal;   // @ Intersection
  float t;            // Distance scalar
  bool hit;           // Did it hit?
  Material* material; // @ Intersection
};

// BSDF
class Material {
public:
  // Ray deviation
  virtual bool scatter(
    const Ray& rayIn,
    const Intersection& hit,
    glm::vec3& attenuation,
    Ray& scattered
  ) const = 0;
};