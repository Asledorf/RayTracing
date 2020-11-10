#include "Plane.h"

bool Plane::Hit(const ray& r, float tMin, float tMax, raycastHit& hit)
{
    float denominator = glm::dot(r.direction, m_normal);

    if (abs(denominator) < std::numeric_limits<float>::epsilon())
    {
        return false; // direction and plane parallel, no intersection
    }
    //Compute t by
    float t = glm::dot(m_center - r.origin, m_normal) / denominator;

    //If t is < then 0 then the ray is hitting the backside of the plane, return false
    if (t < 0)
    {
        return false;
    }

    //Check if t > tMinand t < tMax then set the hit struct and return true        
    if (t >= tMin && t <= tMax)
    {
        hit.t = t;
        hit.point = r.pointAt(t);
        hit.normal = m_normal;
        hit.material = m_material;
        return true;
    }

    return false;
}
