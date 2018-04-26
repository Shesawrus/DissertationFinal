#include "PhysicsClass.h"

PhysicsClass::PhysicsClass()
{
	instances = new ParticleType[m_instanceCount];
	objectInstances = new ObjectType[m_objectCount];
	ParticleType currentParticle;
	partitionClass = new SpatialPartition;
	GridWidth = 0;
	GridHeight = 0;
	GridDepth = 0;
	GridPos = 0;

	partitionClass->Initialize(XMFLOAT3(150, -25, -50), XMFLOAT3(250, 100, 50), 15);

	objectInstances[0].position = XMFLOAT3(160, -20, -15);
	objectInstances[0].width = 300;
	objectInstances[0].height = 2;
	objectInstances[0].depth = 300;

	srand((unsigned)time(NULL));
	// Load the instance array with data.
	for (int a = 0; a < 6; a++)
	{
		GridDepth = a * 5;
		for (int b = 0; b < 6; b++)
		{
			GridHeight = b * 5;
			for (int c = 0; c < 6; c++)
			{
				GridWidth = c * 5;
				currentParticle = instances[GridPos];
				instances[GridPos].temperature = -2;
				instances[GridPos].density = currentParticle.Mass * ((4 / 3) * kPiD * pow(currentParticle.objectRadius, 3));
				instances[GridPos].position = XMFLOAT3(GridWidth + 200, GridHeight - 10, GridDepth);
				
				int index = partitionClass->calculateIndexPosition(instances[GridPos].position);
				if (index != instances[GridPos].index)
				{
					if (index != -1)
					{
						partitionClass->removeFromVector(&instances[GridPos]);
						instances[GridPos].index = index;
						partitionClass->addToVector(&instances[GridPos]);
					}
				}

				GridPos++;
			}
		}
	}



}

PhysicsClass::~PhysicsClass()
{

}

bool PhysicsClass::Initialize(GraphicsClass* m_graphics)
{
	currentTime = GetTickCount();

	XMFLOAT3 Rotation = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);

	float pitch = Rotation.x * 0.0174532925f;
	float yaw = Rotation.y * 0.0174532925f;
	float roll = Rotation.z * 0.0174532925f;

	auto t = (1.0 + sqrt(5.0)) / 2.0;

	ModelClass::VertexType currentVertex;
	std::vector<ModelClass::VertexType> vertexList;
	std::vector<unsigned long> indexList;

	//Directx 11 creating icosphere C++

	// Square 1.

	currentVertex.position = XMFLOAT3(origin.x - 1, origin.y + t, origin.z);
	currentVertex.color = XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f);
	currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + 1, origin.y + t, origin.z);
	currentVertex.color = XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f);
	currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x - 1, origin.y - t, origin.z);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + 1, origin.y - t, origin.z);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	// Square 2.

	currentVertex.position = XMFLOAT3(origin.x, origin.y - 1, origin.z + t);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + 1, origin.z + t);
	currentVertex.color = XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y - 1, origin.z - t);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + 1, origin.z - t);
	currentVertex.color = XMFLOAT4(0.8f, 0.8f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	// Square 3.

	currentVertex.position = XMFLOAT3(origin.x + t, origin.y, origin.z - 1);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + t, origin.y, origin.z + 1);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x - t, origin.y, origin.z - 1);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x - t, origin.y, origin.z + 1);
	currentVertex.color = XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f);
	vertexList.push_back(currentVertex);

	// 5 faces around point 0.

	indexList.push_back(0);
	indexList.push_back(5);
	indexList.push_back(11);

	indexList.push_back(0);
	indexList.push_back(1);
	indexList.push_back(5);

	indexList.push_back(0);
	indexList.push_back(7);
	indexList.push_back(1);

	indexList.push_back(0);
	indexList.push_back(10);
	indexList.push_back(7);

	indexList.push_back(0);
	indexList.push_back(11);
	indexList.push_back(10);

	//// 5 adjacent faces.

	indexList.push_back(1);
	indexList.push_back(9);
	indexList.push_back(5);

	indexList.push_back(5);
	indexList.push_back(4);
	indexList.push_back(11);

	indexList.push_back(11);
	indexList.push_back(2);
	indexList.push_back(10);

	indexList.push_back(10);
	indexList.push_back(6);
	indexList.push_back(7);

	indexList.push_back(7);
	indexList.push_back(8);
	indexList.push_back(1);

	//// 5 faces around point 3.

	indexList.push_back(3);
	indexList.push_back(4);
	indexList.push_back(9);

	indexList.push_back(3);
	indexList.push_back(2);
	indexList.push_back(4);

	indexList.push_back(3);
	indexList.push_back(6);
	indexList.push_back(2);

	indexList.push_back(3);
	indexList.push_back(8);
	indexList.push_back(6);

	indexList.push_back(3);
	indexList.push_back(9);
	indexList.push_back(8);

	////5 adjacent faces

	indexList.push_back(4);
	indexList.push_back(5);
	indexList.push_back(9);

	indexList.push_back(2);
	indexList.push_back(11);
	indexList.push_back(4);

	indexList.push_back(6);
	indexList.push_back(10);
	indexList.push_back(2);

	indexList.push_back(8);
	indexList.push_back(7);
	indexList.push_back(6);

	indexList.push_back(9);
	indexList.push_back(1);
	indexList.push_back(8);

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	for (auto it = vertexList.begin(); it != vertexList.end(); it++)
	{
		XMVECTOR tempPos = XMLoadFloat3(&it->position);
		tempPos = XMVector3TransformCoord(tempPos, rotationMatrix);
		XMStoreFloat3(&it->position, tempPos);
		it->position.x += origin.x;
		it->position.y += origin.y;
		it->position.z += origin.z;

	}

	m_model = new ModelClass();
	m_model->Initialize(m_graphics->m_Direct3D->GetDevice(), vertexList, indexList, m_graphics->m_Direct3D->GetDeviceContext(), "../Dissertation/stone01.tga", sizeof(ParticleType), m_instanceCount, instances);

	m_graphics->sendModel(m_model);

	CreateRectangle(m_graphics);

	

	return true;
}

void PhysicsClass::AlgorithmLoop(GraphicsClass* m_graphics)
{
	XMFLOAT3 velocity;
	int iceCounter = 0;
	deltaTime = GetTickCount() - currentTime;
	currentTime = GetTickCount();
	tempInstances = instances;

	vector<ParticleType*> withInRange;

	for (int a = 0; a < m_instanceCount; a++)
	{
		iceCounter = 0;
		velocity = XMFLOAT3(0.0, 0.0, 0.0);
		m_densityCounter = 0;
		neighbourList.clear();
		withInRange.clear();
		withInRange = partitionClass->getObjectsWithinRange(tempInstances[a].position, tempInstances[a].radationRadius);
		for (int b = 0; b < withInRange.size(); b++)
		{
			collisionHit = NULL;
			collisionHit = Intersect(tempInstances[a].position, withInRange[b]->position, tempInstances[a].objectRadius, withInRange[b]->objectRadius);
			/*if (collisionHit)
			{
				newVelocity = changeVelocity(tempInstances[a].Velocity, tempInstances[a].Mass, withInRange[b]->Velocity, withInRange[b]->Mass);
			}

			if (tempInstances[a].isLiquid != true && withInRange[b]->isLiquid != true)
			{
				velocity.x += withInRange[b]->Velocity.x;
				velocity.z += withInRange[b]->Velocity.z;
				iceCounter++;
			}*/

			CalculateDensity(tempInstances[a], *withInRange[b]);
		}

		accumulateForces(&tempInstances[a]);
		HeatTransfer(&tempInstances[a], deltaTime);

		if (tempInstances[a].isLiquid)
		{
			applyForce(&tempInstances[a]);
		}

		if (iceCounter != 0)
		{
			velocity.x /= iceCounter;
			velocity.z /= iceCounter;
		}

		for (int c = 0; c < m_objectCount; c++)
		{
			collisionHit = NULL;
			collisionHit = collisionWithObject(objectInstances[c].position, objectInstances[c].width, objectInstances[c].height, objectInstances[c].depth, tempInstances[a].position, tempInstances[a].objectRadius);
			if (collisionHit)
			{
				tempInstances[a].Velocity.y = 0.0;
				ResultOfObjectCollision();
			}
		}

	}

	pressureForces.clear();
	instances = tempInstances;
	Movement(m_graphics, 0);
	
}

bool PhysicsClass::Intersect(XMFLOAT3 sphere, XMFLOAT3 other, float sphereRadius, float otherRadius)
{
	distance = sqrt((sphere.x - other.x) * (sphere.x - other.x) + 
					(sphere.y - other.y) * (sphere.y - other.y) + 
					(sphere.z - other.z) * (sphere.z - other.z));

	if (distance < (sphereRadius + otherRadius))
	{
		return true;
	}
	else
	{
		return false;
	}
}

XMFLOAT3 PhysicsClass::changeVelocity(XMFLOAT3 sphereVelocity, float sphereMass, XMFLOAT3 otherVelocity, float otherMass)
{
	XMFLOAT3 changeInVelocity;

	changeInVelocity.x = (sphereVelocity.x * (sphereMass - otherMass) + (2 * otherMass * otherVelocity.x)) / (sphereMass + otherMass);
	changeInVelocity.y = (sphereVelocity.y * (sphereMass - otherMass) + (2 * otherMass * otherVelocity.y)) / (sphereMass + otherMass);
	changeInVelocity.z = (sphereVelocity.z * (sphereMass - otherMass) + (2 * otherMass * otherVelocity.z)) / (sphereMass + otherMass);

	if (changeInVelocity.x > 1)
	{
		changeInVelocity.x = 1;
	}

	if (changeInVelocity.x < -1)
	{
		changeInVelocity.x = -1;
	}

	if (changeInVelocity.y > 1)
	{
		changeInVelocity.y = 1;
	}

	if (changeInVelocity.y < -1)
	{
		changeInVelocity.y = -1;
	}

	if (changeInVelocity.z > 1)
	{
		changeInVelocity.z = 1;
	}

	if (changeInVelocity.z < -1)
	{
		changeInVelocity.z = -1;
	}
	return changeInVelocity;
}

//Fluid Dynamics

void PhysicsClass::accumulateForces(ParticleType* particleA)
{
	accumulateNonPressureForces(particleA);
	accumulatePressureForce(particleA);
	CalculateExternalForces(particleA);
}

void PhysicsClass::accumulateNonPressureForces(ParticleType* particleA)
{
	accumulateViscosityForce(particleA);
}

void PhysicsClass::accumulatePressureForce(ParticleType* particleA)
{
	XMFLOAT3 result;
	XMFLOAT3 dir;
	XMFLOAT3 kernalResult;
	double massSquared;
	double dist;

	for (int b = 0; b < neighbourList.size(); b++)
	{
		dist = partitionClass->CalculateDistance(particleA->position, neighbourList[b]->position);
		massSquared = sqrt(particleA->Mass + neighbourList[b]->Mass);
		CalculatePressure(particleA, neighbourList[b]);
		if (dist > 0.0)
		{
		result.x = (particleA->position.x - neighbourList[b]->position.x / distance);
		result.y = (particleA->position.y - neighbourList[b]->position.y / distance);
		result.z = (particleA->position.z - neighbourList[b]->position.z / distance);

		dir = result;

		kernalResult = gradientKernal(dist, particleA->radationRadius, dir);

		pressureForces.push_back(result);

		pressureForces[b].x -= massSquared * (particleA->pressure / (particleA->density * particleA->density) +
			neighbourList[b]->pressure / (neighbourList[b]->density *  neighbourList[b]->density)) * kernalResult.x;
		pressureForces[b].y -= massSquared * (particleA->pressure / (particleA->density * particleA->density) +
			neighbourList[b]->pressure / (neighbourList[b]->density *  neighbourList[b]->density)) * kernalResult.y;
		pressureForces[b].z -= massSquared * (particleA->pressure / (particleA->density * particleA->density) +
			neighbourList[b]->pressure / (neighbourList[b]->density *  neighbourList[b]->density)) * kernalResult.z;
		}
	}
}

void PhysicsClass::accumulateViscosityForce(ParticleType* particleA)
{
	double dist;
	double massSquared;
	double kernalResult;
	double result;

	XMFLOAT3 VelocityDifference;
	XMFLOAT3 changeInViscosity;

	for (int b = 0; b < neighbourList.size(); b++)
	{
		dist = partitionClass->CalculateDistance(particleA->position, neighbourList[b]->position);

		massSquared = sqrt(particleA->Mass + neighbourList[b]->Mass);

		result = viscosityCoefficient * massSquared;
		kernalResult = viscositySmoothingKernel(distance, particleA->radationRadius);

		VelocityDifference.x = neighbourList[b]->Velocity.x - particleA->Velocity.x;
		VelocityDifference.y = neighbourList[b]->Velocity.y - particleA->Velocity.y;
		VelocityDifference.z = neighbourList[b]->Velocity.z - particleA->Velocity.z;

		changeInViscosity.x = viscosityCoefficient * massSquared * VelocityDifference.x / neighbourList[b]->density * kernalResult;
		changeInViscosity.y = viscosityCoefficient * massSquared * VelocityDifference.y / neighbourList[b]->density * kernalResult;
		changeInViscosity.z = viscosityCoefficient * massSquared * VelocityDifference.z / neighbourList[b]->density * kernalResult;


		particleA->forces.x += changeInViscosity.x;
		particleA->forces.y += changeInViscosity.y;
		particleA->forces.z += changeInViscosity.z;
	}
}

void PhysicsClass::CalculateDensity(ParticleType particleA, ParticleType particleB)
{
	if (partitionClass->CalculateDistance(particleA.position, particleB.position) <= particleA.radationRadius)
	{
		m_densityCounter += particleB.density;
		neighbourList.push_back(&particleB);
	}
}

void PhysicsClass::CalculatePressure(ParticleType* particleA, ParticleType* particleB)
{
	double speedOfSound = 1481.0;
	double targetDensity = particleA->targetDensity;
	double eosScale = targetDensity * sqrt(1481.0) / eosExponent;

	particleA->pressure = CalculatePressureEOS(particleA, eosScale);
	particleB->pressure = CalculatePressureEOS(particleB, eosScale);

	if (particleA->pressure < 0)
	{
		particleA->pressure *= negativePressureScale;
	}

	if (particleB->pressure < 0)
	{
		particleB->pressure *= negativePressureScale;
	}

	CalculatePressureGradient(particleA, particleB);
}

double PhysicsClass::CalculatePressureEOS(ParticleType* particleA, double eosScale)
{
	double p = eosScale / eosExponent * (pow((particleA->density / targetDensity), eosExponent) - 1.0);

	return p;
}

double PhysicsClass::CalculatePressureGradient(ParticleType* particleA, ParticleType* particleB)
{
	double pressureA = particleA->pressure;
	double pressureB = particleB->pressure;

	return ((particleB->Mass * ((pressureA / particleA->density) + (pressureB / particleB->density))) *
		pressureSmoothingKernel(partitionClass->CalculateDistance(particleA->position, particleB->position), particleA->radationRadius));

}

void PhysicsClass::CalculateExternalForces(ParticleType* particleA)
{
	XMFLOAT3 force;

	force.x = particleA->Mass * gravityConst.x;
	force.y = particleA->Mass * gravityConst.y;
	force.z = particleA->Mass * gravityConst.z;

	particleA->forces.x = force.x;
	particleA->forces.y = force.y;
	particleA->forces.z = force.z;
}

void PhysicsClass::applyForce(ParticleType* particleA)
{
	particleA->Velocity.x += particleA->forces.x;
	particleA->Velocity.y += particleA->forces.y;
	particleA->Velocity.z += particleA->forces.z;
}

/*
void PhysicsClass::CalculateViscosity(ParticleType* particleA, ParticleType* particleB)
{
	double massSquared = sqrt(particleA->Mass + particleB->Mass);
	double result;
	double kernalResult;
	double distance = partitionClass->CalculateDistance(particleA->position, particleB->position);

	XMFLOAT3 VelocityDifference;
	XMFLOAT3 changeInViscosity;

	result = viscosityCoefficient * massSquared;
	kernalResult = viscositySmoothingKernel(distance, particleA->radationRadius);

	VelocityDifference.x = particleB->Velocity.x - particleA->Velocity.x;
	VelocityDifference.y = particleB->Velocity.y - particleA->Velocity.y;
	VelocityDifference.z = particleB->Velocity.z - particleA->Velocity.z;

	changeInViscosity.x = viscosityCoefficient * massSquared * VelocityDifference.x / particleB->density * kernalResult;
	changeInViscosity.y = viscosityCoefficient * massSquared * VelocityDifference.y / particleB->density * kernalResult;
	changeInViscosity.z = viscosityCoefficient * massSquared * VelocityDifference.z / particleB->density * kernalResult;


	particleA->forces.x += changeInViscosity.x;
	particleA->forces.y += changeInViscosity.y;
	particleA->forces.z += changeInViscosity.z;
}
*/

//Fluid Dynamics

//Kernals

double PhysicsClass::heatSmoothingKernel(float distance, float radius)
{
	double h = radius;
	double h2 = h * h;
	double h3 = h2 * h;

	if (distance*distance >= h2)
	{
		return 0.0;
	}
	else
	{
		float x = 1.0 - distance * distance / h2;
		return 315.0 / (64.0 * kPiD * h3) * x * x * x;
	}
}

double PhysicsClass::pressureSmoothingKernel(float distance, float radius)
{
	double h = radius;
	double h2 = h * h;
	double h3 = h2 * h;
	double h4 = h2 * h2;

	if (distance >= h)
	{
		return 0.0;
	}
	else
	{
		double x = 1.0 - distance / h;
		return -45.0 / (kPiD * h4) * x * x;
	}
}

double PhysicsClass::viscositySmoothingKernel(float distance, float radius)
{
	double h = radius;
	double h2 = h * h;
	double h3 = h2 * h;
	double h4 = h2 * h2;
	double h5 = h3 * h2;

	if (distance >= h)
	{
		return 0.0;
	}
	else
	{
		double x = 1.0 - distance / h;
		return 90.0 / (kPiD * h5) * x * x;
	}
}

double PhysicsClass::derivativeKernal(double distance, double radius)
{
	double h = radius;
	double h2 = h * h;
	double h4 = h2 * h2;

	if (distance >= h)
	{
		return 0.0;
	}
	else
	{
		double x = 1.0 - distance / h;

		return -45.0 / (kPiD * h4) * x * x;
	}

}

XMFLOAT3 PhysicsClass::gradientKernal(double distance, double radius, XMFLOAT3 directionToCenter)
{
	XMFLOAT3 result;
	double kernalResult = derivativeKernal(distance, radius);

	result.x = -kernalResult * directionToCenter.x;
	result.y = -kernalResult * directionToCenter.y;
	result.z = -kernalResult * directionToCenter.z;

	return result;
}

//Kernals

void PhysicsClass::HeatTransfer(ParticleType* particleA, double deltaTime)
{
	float currentHeatRate = 0;

	for (int b = 0; b < neighbourList.size(); b++)
	{
		currentHeatRate += particleA->Mass * ((particleA->temperature - neighbourList[b]->temperature) / particleA->density) *
			heatSmoothingKernel(partitionClass->CalculateDistance(particleA->position, neighbourList[b]->position), particleA->radationRadius);
	}
	
	if (neighbourList.size() < 7)
	{
		currentHeatRate += particleA->Mass * ((roomTemperature - particleA->temperature) / particleA->density) *
			heatSmoothingKernel(1, particleA->radationRadius);
	}

	if (particleA->temperature >= 0.01)
	{
		particleA->isLiquid = true;
	}
	else
	{
		particleA->isLiquid = false;
	}

	if (particleA->isLiquid == true)
	{ 
		heatTransferRate = currentHeatRate * waterHeatConstant;
	}
	else
	{
		heatTransferRate = currentHeatRate * iceHeatConstant;
	}

	heatTransferRate *= deltaTime / 1000;

	particleA->temperature += heatTransferRate;

}

/*
float PhysicsClass::Gravity(XMFLOAT3 sphereVelocity, float sphereMass)
{
	XMFLOAT3 newVelocity;

	newVelocity.y = (sphereVelocity.y + gravityConst.y * sphereMass)  * deltaTime / 1000;

	return newVelocity.y;
}
*/

bool PhysicsClass::collisionWithObject(XMFLOAT3 objectPosition, float width, float height, float depth, XMFLOAT3 spherePosition, float sphereRadius)
{
	float leftFace = objectPosition.x;
	float rightFace = objectPosition.x + width;
	float bottomFace = objectPosition.y - 6;
	float topFace = objectPosition.y - 7; 
	float farface = objectPosition.z;
	float nearFace = objectPosition.z + depth;

	float distanceSquared = sphereRadius * sphereRadius;

	if (spherePosition.x + sphereRadius> leftFace)
	{
		if (spherePosition.x - sphereRadius< rightFace)
		{
			if (spherePosition.y + sphereRadius > bottomFace)
			{
				if (spherePosition.y - sphereRadius  < topFace)
				{
					if (spherePosition.z + sphereRadius > farface)
					{
						if (spherePosition.z - sphereRadius < nearFace)
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void PhysicsClass::ResultOfObjectCollision()
{

}

float  PhysicsClass::squared(float Value)
{
	return Value * Value;
}

void PhysicsClass::Movement(GraphicsClass* m_Graphics, int instanceNumber)
{
	D3D11_MAPPED_SUBRESOURCE mappedInstance;
	ZeroMemory(&mappedInstance, sizeof(D3D11_MAPPED_SUBRESOURCE));

	for (int i = 0; i < m_instanceCount; i++)
	{
		instances[i].position.x += instances[i].Velocity.x;
		instances[i].position.y += instances[i].Velocity.y;
		instances[i].position.z += instances[i].Velocity.z;

		int index = partitionClass->calculateIndexPosition(instances[i].position);
		if (index != instances[i].index)
		{
			if (index != -1)
			{
				partitionClass->removeFromVector(&instances[i]);
				instances[i].index = index;
				partitionClass->addToVector(&instances[i]);
			}
		}
	}

	m_Graphics->m_Direct3D->GetDeviceContext()->Map(m_model->GetInstanceBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedInstance);

	memcpy(mappedInstance.pData, instances, sizeof(ParticleType)* m_instanceCount);

	m_Graphics->m_Direct3D->GetDeviceContext()->Unmap(m_model->GetInstanceBuffer(), 0);

}

void PhysicsClass::CreateRectangle(GraphicsClass* m_graphics)
{
	XMFLOAT3 Rotation = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 origin = XMFLOAT3(0, -5.0, 0.0);

	float pitch = Rotation.x * 0.0174532925f;
	float yaw = Rotation.y * 0.0174532925f;
	float roll = Rotation.z * 0.0174532925f;

	float height = 2;
	float width = 100;
	float depth = 100;

	ModelClass::VertexType currentVertex;
	std::vector<ModelClass::VertexType> vertexList;
	std::vector<unsigned long> indexList;

	//Face 1 -Front-

	currentVertex.position = XMFLOAT3(origin);// Bottom left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0,1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0,0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z); // Top left
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);  // Top right.
	//currentVertex.texture = XMFLOAT2(1, 1);
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z); // Bottom right.
	//currentVertex.texture = XMFLOAT2(1, 0);
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	vertexList.push_back(currentVertex);

	//Face 2 -Right-

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z);  // Bottom left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z + depth);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);   // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z + depth);   // Top right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z + depth);   // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	//Face 3 -Back-

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z + depth);// Bottom left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z + depth);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y, origin.z + depth);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z + depth); // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z + depth);  // Top right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y, origin.z + depth);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	//Face 4 -Left-

	currentVertex.position = XMFLOAT3(origin.x, origin.y, origin.z + depth);// Bottom left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z + depth);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z + depth);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z); // Top right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	//Face 5 -Top-

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z); // Bottom left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z + depth); // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x, origin.y + height, origin.z + depth);  // Top left.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z + depth);  // Top right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);  // Bottom right.
	currentVertex.color = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	//Face 6 -Bottom-

	currentVertex.position = XMFLOAT3(origin.x, origin.y, origin.z + depth);// Bottom left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin);// top left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 0);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z + depth);// Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin);// top left.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(0, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z);// top right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 1);
	vertexList.push_back(currentVertex);

	currentVertex.position = XMFLOAT3(origin.x + width, origin.y, origin.z + depth);// Bottom right.
	currentVertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	//currentVertex.texture = XMFLOAT2(1, 0);
	vertexList.push_back(currentVertex);

	// Load the index array with data.

							 //First face

	indexList.push_back(0);  // Bottom left.
	indexList.push_back(1);  // Top left.
	indexList.push_back(2);  // Bottom right.
	indexList.push_back(3);  // Top left.
	indexList.push_back(4);  // Top right.
	indexList.push_back(5);  // Bottom right.

							 //Second face

	indexList.push_back(6);  // Bottom left.
	indexList.push_back(7);  // Top left.
	indexList.push_back(8);  // Bottom right.
	indexList.push_back(9);  // Bottom left.
	indexList.push_back(10);  // Top left.
	indexList.push_back(11);  // Bottom right.

							  //Third face

	indexList.push_back(12);  // Bottom left.
	indexList.push_back(13);  // Top left.
	indexList.push_back(14);  // Bottom right.
	indexList.push_back(15);  // Top left.
	indexList.push_back(16);  // Top right.
	indexList.push_back(17);  // Bottom right.

							  //Fourth face

	indexList.push_back(18);  // Bottom left
	indexList.push_back(19);  // Top left	
	indexList.push_back(20);  // Bottom right
	indexList.push_back(21);  // Top left.
	indexList.push_back(22);  // Top right.
	indexList.push_back(23);  // Bottom right.

							  //Fifth face

	indexList.push_back(24);  // Bottom right
	indexList.push_back(25);  // Top right	
	indexList.push_back(26);  // Bottom left
	indexList.push_back(27);  // Top right.
	indexList.push_back(28);  // Top left.
	indexList.push_back(29);  // Bottom left.

							  //Sixth face

	indexList.push_back(30);  // Bottom left.
	indexList.push_back(31);  // top left.
	indexList.push_back(32);  // Bottom right.
	indexList.push_back(33);  // top left.
	indexList.push_back(34);  // top right.
	indexList.push_back(35);  // Bottom right.

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	for (auto it = vertexList.begin(); it != vertexList.end(); it++)
	{
		XMVECTOR tempPos = XMLoadFloat3(&it->position);
		tempPos = XMVector3TransformCoord(tempPos, rotationMatrix);
		XMStoreFloat3(&it->position, tempPos);
		it->position.x += origin.x;
		it->position.y += origin.y;
		it->position.z += origin.z;

	}

	ModelClass *newModel = new ModelClass();
	newModel->Initialize(m_graphics->m_Direct3D->GetDevice(), vertexList, indexList, m_graphics->m_Direct3D->GetDeviceContext(), "../Dissertation/stone01.tga", sizeof(ObjectType), 1, objectInstances);
	m_graphics->sendModel(newModel);
}

void PhysicsClass::Shutdown()
{
	delete[] instances;
	instances = 0;
}