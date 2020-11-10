#pragma once
#include "Ray.h"
#include "Material.h"

//class Material;

class Geometry
{
public:
	Geometry() {}
	Geometry(Material* material) : m_material{ material } {}

	virtual bool Hit(const ray& r, float tMin , float tMax, raycastHit& hit) = 0;

	Material* material() { return m_material; }

protected:
	Material* m_material{ nullptr };
};