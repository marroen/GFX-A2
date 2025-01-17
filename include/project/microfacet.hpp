#pragma once
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // For matrix transformations
#include <glm/gtc/random.hpp> // For random number generation

#include "tracer.hpp"

class MicrofacetMaterial : public Material {
public:
  glm::vec3 albedo;
  float refractiveIndex;
  float roughness;

  MicrofacetMaterial(
    const glm::vec3& albedo,
    float refractiveIndex,
    float roughness
  ) :
  albedo(albedo),
  refractiveIndex(refractiveIndex),
  roughness(roughness) {}

  virtual bool scatter(
    const Ray& rayIn,
    const Intersection& hit,
    glm::vec3& attenuation,
    Ray& scattered
  ) const override {
    glm::vec3 reflected = glm::reflect(rayIn.direction, hit.normal);
    glm::vec3 refracted = glm::refract(rayIn.direction, hit.normal, 1.0f / refractiveIndex);

    // Mix between reflection and refraction based on roughness
    scattered = Ray(hit.position, glm::mix(reflected, refracted, roughness));
    attenuation = albedo;

    return true;
  }
};