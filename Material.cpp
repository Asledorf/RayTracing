#include "Material.h"
#include "Math.h"

bool Lambertian::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
	// compute the direction as done previously    
	glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
	glm::vec3 direction = glm::normalize(target - hit.point);

	// set scattered to a ray with hit.point as the origin and the direction   
	scattered = ray{hit.point, direction};

	// set attenuation to the albedo
	attenuation = m_albedo;

	return true;
}

bool Metal::Scatter(const ray& r, const raycastHit& hit, glm::vec3& attenuation, ray& scattered) const
{
	// compute reflected ray using reflect function in Math.h       
	// set scattered to reflected ray plus fuzziness of ray (random vector)      
	// set attenuation to the albedo 

	glm::vec3 reflected = reflect(glm::normalize(r.direction), hit.normal);
	scattered.origin = hit.point;
	scattered.direction = reflected + (randomInUnitSphere() * m_fuzz);
	attenuation = m_albedo;
	return true;
}
