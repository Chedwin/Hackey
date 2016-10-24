//*******************************//
//
// Name:			HMath.h
// Description:		A simple header that includes all the necessary GLM header files.
//					All credit goes to Silicon Graphics or whoever
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Oct 08, 2016
//
//*******************************//

#pragma once

#include "Macro.h"

#ifndef HMATH_H
#define HMATH_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

// LET'S MACRO DEFINE SOME GLM TERMS
#define VEC2 glm::vec2
#define VEC3 glm::vec3
#define VEC4 glm::vec4

#define MATRIX3 glm::mat3
#define MATRIX4 glm::mat4

#define QUATERNION glm::quat

#endif