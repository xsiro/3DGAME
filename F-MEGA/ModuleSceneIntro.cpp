#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Race.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update


update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	//COMMENT LATER
	/*for (uint i = 0; i < Race_index; i++) {
		Race[i]->Render();
	}*/
	return UPDATE_CONTINUE;
}
//COMMENT LATER
//Cube ModuleSceneIntro::Walls(float posX, float posY, float posZ, int race)
//{
//	float mass = 100000;
//	float sizeX = 3;
//	float sizeY = 3;
//	float sizeZ = 3;
//	Race[Race_index] = new Cube(sizeX, sizeY, sizeZ);
//	Race[Race_index]->SetPos(posX, posY , posZ);
//	App->physics->AddBody(*Race[Race_index], mass);
//	if (race)
//	{ 
//		Race[Race_index]->color = Red;
//	}	
//	Race_index++;
//	return *Race[Race_index - 1];
//}

//THIS TOO
//bool ModuleSceneIntro::CreateRace(float list[], uint size, uint numRace) {
//	for (int i = 0; i < size; i += 3) {
//		float x = list[i] * 200;
//		float y = list[i + 1] * 200;
//		float z = list[i + 2] * 200 - 55;
//		Walls(x, y, z, numRace);
//	}
//
//	return true;
//}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

