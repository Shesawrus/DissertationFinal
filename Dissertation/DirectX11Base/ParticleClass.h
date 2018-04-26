#pragma once

#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <d3d11.h>
#include <directxmath.h>


using namespace DirectX;


struct ParticleType
{
	XMFLOAT3 position = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT4 color = XMFLOAT4(0.0, 0.0, 0.0, 1.0);
	XMFLOAT3 Velocity = XMFLOAT3(0.0, 0.0, 0.0);
	float objectRadius = 1;
	float radationRadius = 5.5;
	float Mass = 1;
	float temperature = -5;
	bool isLiquid = false;
	XMFLOAT3 Rotation = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);
	int index = -1;
	float density = 0;
	double pressure;
	double targetDensity = 0.99798;
	XMFLOAT3 forces = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 direction;
};

#endif 