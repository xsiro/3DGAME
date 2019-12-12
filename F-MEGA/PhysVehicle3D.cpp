#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	Cube aleron(info.aleron_size.x, info.aleron_size.y, info.aleron_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&aleron.transform);
	Cube paloaleron(info.paloaleron_size.x, info.paloaleron_size.y, info.paloaleron_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&paloaleron.transform);

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_aleron(info.aleron_offset.x, info.aleron_offset.y, info.aleron_offset.z);
	offset_aleron = offset_aleron.rotate(q.getAxis(), q.getAngle());
	btVector3 offset_paloaleron(info.paloaleron_offset.x, info.paloaleron_offset.y, info.paloaleron_offset.z);
	offset_paloaleron = offset_paloaleron.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	aleron.transform.M[12] += offset_aleron.getX();
	aleron.transform.M[13] += offset_aleron.getY();
	aleron.transform.M[14] += offset_aleron.getZ();

	paloaleron.transform.M[12] += offset_paloaleron.getX();
	paloaleron.transform.M[13] += offset_paloaleron.getY();
	paloaleron.transform.M[14] += offset_paloaleron.getZ();

	chassis.color = Red;
	aleron.color.Set(255, 128, 0);
	paloaleron.color = Red;


	chassis.Render();
	aleron.Render();
	paloaleron.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}