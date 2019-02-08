#pragma once

#include "GameObject.h"

#include <glm/vec3.hpp>

namespace ge {

///
/// \brief The Light class represents a Light
///
class Light : public GameObject {
public:
    Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);

    void setAmbient(const glm::vec3 &ambient);
    void setDiffuse(const glm::vec3 &diffuse);
    void setSpecular(const glm::vec3 &specular);

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

inline void Light::setAmbient(const glm::vec3 &ambient) {this->ambient = ambient;}
inline void Light::setDiffuse(const glm::vec3 &diffuse) {this->diffuse = diffuse;}
inline void Light::setSpecular(const glm::vec3 &specular) {this->specular = specular;}

inline glm::vec3 Light::getAmbient() const {return this->ambient;}
inline glm::vec3 Light::getDiffuse() const {return this->diffuse;}
inline glm::vec3 Light::getSpecular() const {return this->specular;}

} // namespace ge
