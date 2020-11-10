#include "Camera.h"
#include "Image.h"
Camera::Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float vfov, Image* image)
{


	//Save the pointer to the image
	m_image = image;
	//Calculate the aspect ratio. Make sure to cast one of the values to float or else it will do an int division
	float aspectRatio = image->width() / image->height();
	//Calculate the height from the vertical field of view(fov)ovfov is in degrees 
	//glm::radians converts to radians which is needed for tan function
	float theta = glm::radians(vfov); 
	float h = tan(theta * 0.5f);
	//Calculate the viewport widthand height
	float viewportHeight = h * 2.0f; float viewportWidth = aspectRatio * viewportHeight;
	//Calculate the forward, right, and up vectors
	m_forward = glm::normalize(eye - lookAt);
	m_right = glm::normalize(glm::cross(up, m_forward));
	m_up = glm::cross(m_forward, m_right);
	//Save the eye position
	m_eye = eye;
	//Calculate the horizontal and vertical dimensions of the viewport
	m_horizontal = viewportWidth * m_right;
	m_vertical = viewportHeight * m_up;
	//Calculate the bottom left position of the viewport
	m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward; 
}

//ScreenToViewport 
glm::vec2 Camera::ScreenToViewport(const glm::vec2& screen)
{
	//Create vec2 viewport variable
	glm::vec2 viewport;
	//Set viewport x to screen x / image width
	//cast image width to float
	//Set viewport y to screen y / image height
	//cast image height to float
	viewport.x = screen.x / (float)m_image->width();
	viewport.y = screen.y / (float)m_image->height();
	//return viewport
	return viewport;
}

//ViewportToRay 
ray Camera::ViewportToRay(const glm::vec2& viewport)
{
	//Create ray variable
	ray r;
	//Set ray origin to eye
	//Set ray direction to
	r.direction = m_lowerLeft + (viewport.x * m_horizontal) + (viewport.y * m_vertical) - m_eye;
	//return ray
	return r;
}

//Update Tracer
//Trace function will now take Camera as a parameter
	//void Trace(Image & image, Scene & scene, Camera & camera); 

//Trace function will now compute ray using the CameraoRemove old code that create ray with the following
	//glm::vec2 viewport = camera.ScreenToViewport({ x + random01(), y + random01() }); 
	//viewport.y = 1 - (viewport.y);
	//ray r = camera.ViewportToRay(viewport);
