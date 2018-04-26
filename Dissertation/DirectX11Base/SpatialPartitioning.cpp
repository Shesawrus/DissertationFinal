#include "SpatialPartitioning.h"

SpatialPartition::SpatialPartition()
{

}

SpatialPartition::~SpatialPartition()
{

}

void SpatialPartition::Initialize(XMFLOAT3 m_min, XMFLOAT3 m_max, float m_sectionSize)
{
	min = m_min;
	max = m_max;
	sectionSize = m_sectionSize;

	totalSections.x = (int)((max.x - min.x) / sectionSize) + 1;
	totalSections.y = (int)((max.y - min.y) / sectionSize) + 1;
	totalSections.z = (int)((max.z - min.z) / sectionSize) + 1;

	for (int a = 0; a < totalSections.x * totalSections.y * totalSections.z; a++)
	{
		spatialPartitionList.push_back(new SpatialSection);
	}
}

vector<ParticleType*> SpatialPartition::getObjectsWithinRange(XMFLOAT3 pos, float range)
{
	
	XMFLOAT3 rangeCheck;
	vector<ParticleType*> particlesWithinRange;

	for (int a = -range;a <= range + sectionSize;a += sectionSize)
	{
		for (int b = -range;b <= range + sectionSize;b += sectionSize)
		{
			for (int c = -range;c <= range + sectionSize;c += sectionSize)
			{
				XMFLOAT3 offset = XMFLOAT3(a,b,c);
				offset.x += pos.x;
				offset.y += pos.y;
				offset.z += pos.z;

				int index = calculateIndexPosition(offset);

				if (index >= 0 && index < spatialPartitionList.size())
				{
					SpatialSection currentSection = *spatialPartitionList[index];
					for (int d = 0;d < currentSection.spatialSectionList.size();d++)
					{
						distance = CalculateDistance(currentSection.spatialSectionList[d]->position, pos);
						if (distance < range)
						{
							if (!(checkVector(currentSection.spatialSectionList[d], particlesWithinRange)))
							{
								particlesWithinRange.push_back(currentSection.spatialSectionList[d]);
							}
						}
					}
				}
			}
		}
	}

	return particlesWithinRange;
}

bool SpatialPartition::checkVector(ParticleType* particle, vector<ParticleType*> tempVector)
{
	for (int a = 0; a < tempVector.size(); a++)
	{
		if (particle == tempVector[a])
		{
			return true;
		}
	}
	return false;
}

int SpatialPartition::calculateIndexPosition(XMFLOAT3 pos)
{
	XMFLOAT3 SpatialPos;

	if (pos.x > min.x && pos.y > min.y && pos.z > min.z)
	{
		if (pos.x < max.x && pos.y < max.y && pos.z < max.z)
		{
			SpatialPos.x = (int)((pos.x - min.x) / sectionSize);
			SpatialPos.y = (int)((pos.y - min.y) / sectionSize);
			SpatialPos.z = (int)((pos.z - min.z) / sectionSize);
			return (int)((SpatialPos.x * totalSections.y * totalSections.z) + (SpatialPos.y * totalSections.z) + SpatialPos.z);
		}
	}
	return -1;
}

void SpatialPartition::addToVector(ParticleType* particle)
{
	int index = calculateIndexPosition(particle->position);
	if (index >= 0 && index < spatialPartitionList.size())
	{
		spatialPartitionList[index]->spatialSectionList.push_back(particle);
	}
}

void SpatialPartition::removeFromVector(ParticleType* particle)
{
	int index = calculateIndexPosition(particle->position);

	if (index >= 0 && index < spatialPartitionList.size())
	{
		for (int a = 0;a < spatialPartitionList[index]->spatialSectionList.size();a++)
		{
			if (spatialPartitionList[index]->spatialSectionList[a] == particle)
			{
				spatialPartitionList[index]->spatialSectionList[a] = spatialPartitionList[index]->spatialSectionList.back();
				spatialPartitionList[index]->spatialSectionList.pop_back();
			}
		}
	}
} 

float SpatialPartition::CalculateDistance(XMFLOAT3 particleA, XMFLOAT3 particleB)
{
	XMVECTOR posA = XMLoadFloat3(&particleA);
	XMVECTOR posB = XMLoadFloat3(&particleB);

	float distance = 0;

	posA -= posB;

	posA = XMVector3Length(posA);
	XMStoreFloat(&distance, posA);

	return distance;
}