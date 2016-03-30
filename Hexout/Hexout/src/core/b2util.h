#pragma once

#include "Box2D/Common/b2Math.h"
#include "vec2.h"

static const float c_scale = 32.0f;

inline b2Vec2 worldToBox2D(float x, float y)
{
	return b2Vec2(x / c_scale, y / c_scale);
}

inline b2Vec2 worldToBox2D(yam2d::vec2 vec)
{
	vec.x /= c_scale;
	vec.y /= c_scale;
	return b2Vec2(vec.x, vec.y);
}

inline float worldToBox2D(float f)
{
	return f / c_scale;
}

inline yam2d::vec2 box2DToWorld(float x, float y)
{
	return yam2d::vec2(x * c_scale, y * c_scale);
}

inline yam2d::vec2 box2DToWorld(b2Vec2 vec)
{
	vec.x *= c_scale;
	vec.y *= c_scale;
	return yam2d::vec2(vec.x, vec.y);
}

inline float box2DToWorld(float f)
{
	return f * c_scale;
}