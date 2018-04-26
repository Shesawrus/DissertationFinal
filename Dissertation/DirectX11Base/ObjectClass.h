#pragma once
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

struct ObjectType
{
	XMFLOAT3 position;
	XMFLOAT3 Velocity = XMFLOAT3(0.0, 0.0, 0.0);
	float Mass = 1;
	float height = 1;
	float width = 1;
	float depth = 1;
	XMFLOAT3 Rotation = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);
};