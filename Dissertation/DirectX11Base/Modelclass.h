////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <vector>
//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

#include "textureclass.h"
#include "ParticleClass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:

public:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 texture;
	};

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	bool Initialize(ID3D11Device*, std::vector<VertexType>, std::vector<unsigned long>, ID3D11DeviceContext* deviceContext, char* textureFilename, int size, int count, void* instances);
	//void Movement(ID3D11DeviceContext*,ID3D11Device*, int, XMFLOAT3);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	ID3D11Buffer* GetInstanceBuffer();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*, int size, int count, void* instances);
	bool InitializeBufferData(std::vector<VertexType>, std::vector<unsigned long>);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();
	//void RenderColor(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ID3D11Buffer* m_instanceBuffer;
	int counter = 0;
	VertexType* vertices;
	unsigned long* indices;

};

#endif