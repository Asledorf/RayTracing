#pragma once
#include"Types.h"
#include"Image.h"
#include"Scene.h"
#include"Camera.h"



class Tracer
{
public:
	Tracer(int s, int d) : samples{ s }, depth{ d } {}

	//void Trace(Image& img, Scene& scene);
	void Trace(Image& img, Scene& scene, Camera& camera);
private:
	glm::vec3 m_origin{0,0,0};
	int samples{ 1 };
	int depth{ 1 };
};