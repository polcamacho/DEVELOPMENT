#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	b2World* World = nullptr;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityiterator = 8;
	int32 positioniterator = 3;
	void MakeShape(float, float, float, bool);


private:


	bool debug;
};