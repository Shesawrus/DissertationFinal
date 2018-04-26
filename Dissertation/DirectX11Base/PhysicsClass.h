#pragma once

#include "Modelclass.h"
#include "Graphicsclass.h"
#include "ParticleClass.h"
#include "ObjectClass.h"
#include "SpatialPartitioning.h"

#include <vector>
#include <time.h>


class PhysicsClass
{


public:
	PhysicsClass();
	~PhysicsClass();
	void Shutdown();

	bool Intersect(XMFLOAT3, XMFLOAT3, float, float);
	bool collisionWithObject(XMFLOAT3, float, float, float, XMFLOAT3, float); //cube position, width, height, depth, sphere position, radius
	bool Initialize(GraphicsClass*);
	XMFLOAT3 changeVelocity(XMFLOAT3, float, XMFLOAT3, float);
	float Gravity(XMFLOAT3, float);
	float squared(float);
	void ResultOfObjectCollision();
	void AlgorithmLoop(GraphicsClass*);
	void Movement(GraphicsClass*, int);
	void CreateRectangle(GraphicsClass*);

	//Fluid Dynamics

	void accumulateForces(ParticleType*);
	void accumulateNonPressureForces(ParticleType*);
	void accumulatePressureForce(ParticleType*);
	void accumulateViscosityForce(ParticleType*);

	void CalculateDensity(ParticleType, ParticleType);
	void CalculatePressure(ParticleType*, ParticleType*);
	double CalculatePressureEOS(ParticleType*, double);
	double CalculatePressureGradient(ParticleType*, ParticleType*);

	void applyForce(ParticleType*);

	void CalculateViscosity(ParticleType*, ParticleType*);
	void CalculatePseudoViscosity();


	void CalculateExternalForces(ParticleType*);

	//Kernals

	double heatSmoothingKernel(float, float);
	double pressureSmoothingKernel(float, float);
	double viscositySmoothingKernel(float, float);
	double derivativeKernal(double, double);
	XMFLOAT3 gradientKernal(double, double, XMFLOAT3);

	void HeatTransfer(ParticleType*, double);
	

private:
	ModelClass* m_model;
	ParticleType* instances;
	ParticleType* tempInstances;
	ObjectType* objectInstances;
	SpatialPartition* partitionClass;
	vector<ParticleType*> neighbourList;
	vector<XMFLOAT3> pressureForces; 

	float h, h2, h3 = 0;
	float m_densityCounter;

	float heatTransferRate;
	float iceHeatConstant = 2.092;
	float waterHeatConstant = 0.603;

	double eosExponent = 1;
	float targetDensity = 0.997;
	int negativePressureScale = 0;
	double viscosityCoefficient = 1.0518;
	int pressureFieldCounter = 0;

	float roomTemperature = 21.0;

	int m_objectCount = 1;
	int m_instanceCount = 216;
	int particleACounter;
	int GridPos = 0;
	float GridWidth = 0;
	float GridHeight = 0;
	float GridDepth = 0;
	float distance;
	double kPiD = 3.14159265358979323846264338327950288;
	XMFLOAT3 newVelocity;
	float velocityChange;
	const XMFLOAT3 gravityConst = XMFLOAT3(0.0, -0.00981, 0.0);
	bool collisionHit;

	double deltaTime;
	DWORD currentTime;
	
};


