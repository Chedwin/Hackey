//*******************************//
//
// Name:			Effect.h
// Description:		Abstract class of an effect to be applied to a model, texture, etc.
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//

#ifndef EFFECT_H
#define EFFECT_H

#include "Macro.h"
#include "AbstractRenderer.h"

class Effect {
public:
	// Apply the effect to the model its attached to
	// It needs a reference to the renderer to create the effect
	virtual void ApplyEffect(AbstractRenderer &renderer) = 0;


	//Perform any operations necessary after the effect has been applied and the model rendered.
	virtual void PostEffect(AbstractRenderer &renderer) = 0;

	// Return the name of the material
	virtual STRING GetMaterialName() const = 0;
};

#endif