#include "Tracer.h"
#include "Sphere.h"
#include "Scene.h"
#include "Math.h"

void Tracer::Trace(Image& img, Scene& scene, Camera& camera)
{
	float aspectRatio = img.width() / (float)img.height();
	for (size_t y = 0; y < img.height(); y++)
	{
		//height = 600
		for (size_t x = 0; x < img.width(); x++)
		{
			//width = 800
			glm::vec3 color{0,0,0};

			for (size_t i = 0; i < samples; i++)
			{
				glm::vec3 p;
				p.x =	((x + random_01()) / img.width());
				p.y = 1-((y + random_01()) / img.height());
				p.z = 0;

				glm::vec3 direction = glm::vec3{ glm::vec2{p} * 2.0f - 1.0f, -1 };
				direction.y /= aspectRatio;
				direction = glm::normalize(direction);


				glm::vec2 viewport = camera.ScreenToViewport({ x + random_01(), y + random_01() }); 
				viewport.y = 1 - (viewport.y);
				ray r = camera.ViewportToRay(viewport);
				//ray r(m_origin, direction);	

				raycastHit Hit;
				color += (scene.Trace(r, 0.001f, FLT_MAX, Hit));
			}
			color /= (float)samples;
			img.SetPoint({ x,y }, color);
		}
	}
}