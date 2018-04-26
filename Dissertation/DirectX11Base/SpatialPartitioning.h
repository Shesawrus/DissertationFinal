#pragma once

#include "ParticleClass.h"
#include <vector>

using namespace std;

struct SpatialSection
{
	vector<ParticleType*> spatialSectionList;
};

class SpatialPartition
{
public:
	SpatialPartition();
	~SpatialPartition();
	void Initialize(XMFLOAT3, XMFLOAT3, float);
	vector<ParticleType*> getObjectsWithinRange(XMFLOAT3, float);
	bool checkVector(ParticleType*, vector<ParticleType*>);
	int calculateIndexPosition(XMFLOAT3);
	void addToVector(ParticleType*);
	void removeFromVector(ParticleType*);
	static float CalculateDistance(XMFLOAT3, XMFLOAT3);

private:
	vector<SpatialSection*> spatialPartitionList;
	XMFLOAT3 min;
	XMFLOAT3 max;
	XMFLOAT3 totalSections;
	float distance;
	float sectionSize;
};

