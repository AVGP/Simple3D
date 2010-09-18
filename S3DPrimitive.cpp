/**
* @file S3DPrimitive.cpp
* @brief Contains the code for S3DPrimitive.
*/
#include "S3DPrimitive.h"

//This is unused at the moment. But that doesn't mean, we're not going to use it
unsigned int S3DPrimitive::id_max = 1; 

/**
* @brief Returns if the primitive is filled or just wireframe.
*/
bool S3DPrimitive::getFillMode()
{
	return isFilled;
}

/**
* @brief Used to influence, if the primitive is filled or just wireframe.
* @param[in] fill True, to make the primitive filled, else false.
*/
void S3DPrimitive::setFillMode(bool fill)
{
	isFilled = fill;
}

/**
* @brief Returns the color of the primitive.
*/
unsigned long S3DPrimitive::getColor()
{
	return color;
}

/**
* @brief Sets the color of the primitive
* @param[in] c The color as unsigned long (as produced by RGB-macro), the primitive will get.
*/
void S3DPrimitive::setColor(unsigned long c)
{
	color = c;
}
