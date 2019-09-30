#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG

#pragma comment(lib, "Box2D/libx86/Debug/Box2D.lib")

#endif // DEBUG
#ifndef _DEBUG

#pragma comment(lib, "Box2D/libx86/Release/Box2D.lib")

#endif // DEBUG


// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;

}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it

	b2Vec2 grav;
	grav.x = 0.0f;
	grav.y = 10.0f;

	World = new b2World(grav);


	// TODO 4: Create a a big static circle as "ground"
	
	MakeShape(200, 10, 10, false);
	
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)
	World->Step(timeStep, velocityiterator, positioniterator);
	return UPDATE_CONTINUE;
}

void ModulePhysics::MakeShape(float ratius, float x, float y, bool move=false) {

	b2BodyDef circleground;
	circleground.position.Set(x, y);

	if (move == true)
		circleground.type = b2_dynamicBody;

	b2CircleShape shape;
	shape.m_radius = PIXELS_TO_METERS(ratius);
	shape.m_type = b2Shape::e_circle;
	b2Body* body = World->CreateBody(&circleground);
	if (move == true)
	{
		b2FixtureDef frixtureDef;
		frixtureDef.shape = &shape;
		frixtureDef.density = 1.0f;
		frixtureDef.friction = 0.3f;
		body->CreateFixture(&frixtureDef);
	}
	else
		body->CreateFixture(&shape, 0.0f);
	b2BodyDef groundbox;
	groundbox.position.Set(50, 50);
	if (move == false)
		groundbox.type = b2_staticBody;
	b2PolygonShape shape2;
	shape2.m_type = b2Shape::e_polygon;
	b2Body* body2 = World->CreateBody(&groundbox);
	if (move == false)
	{
		b2FixtureDef frixtureDef2;
		frixtureDef2.shape = &shape2;
		frixtureDef2.density = 0.0f;
		body2->CreateFixture(&frixtureDef2);
	}
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == 1)
		MakeShape(50, PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()), true);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = World->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;
				case b2Shape::e_polygon:
				{
					b2PolygonShape* shape2 = (b2PolygonShape*)f->GetShape();
					b2Vec2 pos2 = f->GetBody()->GetPosition();
					SDL_Rect rect;
					App->renderer->DrawQuad(rect, 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete World;

	return true;
}
