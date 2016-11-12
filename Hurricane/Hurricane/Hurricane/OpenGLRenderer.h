//*******************************//
//
// Name:			OpenGLRenderer.h
// Description:		This renderer uses a SDL window w/ a GL Context to draw to the screen
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	Nov 04, 2016
//
//*******************************//

#pragma once

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include "Macro.h"
#include "Game.h"
#include "AbstractRenderer.h"
#include "Window.h"

#include "ShaderProgramManager.h"
#include "ImageManager.h"
//#include "HMath.h"

class OpenGLRenderer : public AbstractRenderer {
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void RenderPrimitive(PrimitiveType prim);
};

#endif