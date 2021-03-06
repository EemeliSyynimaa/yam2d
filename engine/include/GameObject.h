// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// http://code.google.com/p/yam2d/
//
// Copyright (c) 2013 Mikko Romppainen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Object.h>
#include <vec2.h>
#include <string>
#include <Entity.h>

namespace yam2d
{

class Layer;

/**
 * Class for GameObject. Game objects
 *
 * @see Scene, Layer
 * @ingroup yam2d
 * @author Mikko Romppainen (mikko@kajakbros.com)
 */
class GameObject : public Entity
{
public:
	GameObject(Entity* parent, const PropertySet& properties);
	GameObject(Entity* parent, int type = 0, const vec2& position = vec2(0.0f), const vec2& size = vec2(0.0f), const std::string& name = "");

	virtual ~GameObject();

	void setName( const std::string& name );
	void setPosition( const vec2& position );
	void setPosition( float x, float y ) { setPosition(vec2(x,y)); }
	void setRotation( float rotation );
	void setSize( float sizeX, float sizeY );
	void setSize( const vec2& size );

	const std::string& getName() const;
	const vec2& getPosition() const;
	float getRotation() const;
	const vec2& getSize() const;
	vec2 getSizeInTiles() const;
	
	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;
	
	bool isInside(const vec2& worldPosition) const;

	// Check collision between two game objects.
	//
	// collisionNormalLikeOverlap is optional "like normal vector". This means, that it is not normalized, but 
	// instead it describes components of overlapping axis relative to object size. Vector component 
	// which has bigger absolute value, can be used as a normal vector. Both, x and y values of the 
	// collisionNormalLikeOverlap are between 0 and 1. 0 means that the object are overlapping fully
	// (basically are in same location) and values closer to 1 means that the objects are not overlapping 
	// so much. Exact 1 means that objects are barely touching each other.
	bool collidesTo( GameObject* other, vec2* collisionNormalLikeOverlap = 0 );

	void setTileSize(const vec2& tileSize );

	//void setOffset( const vec2& offset ) { m_offset = offset; recalcExtens(); }
	//const vec2& getOffset() const { return m_offset; }
protected:

private:
	void recalcExtens();

	GameObject();
	GameObject(const GameObject&);
	GameObject& operator=(const GameObject&);
	
	std::string		m_name;
	vec2			m_position;
//	vec2			m_offset;
	vec2			m_topLeft;
	vec2			m_bottomRight;
	float			m_rotation;
	vec2			m_size;
	vec2			m_tileScale;
//	int				m_type;
};

class Updatable
{
public:
	virtual void update(float deltaTime) = 0;
};

}


#endif


