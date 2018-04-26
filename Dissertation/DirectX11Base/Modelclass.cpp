////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
	m_Texture = 0;
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device, std::vector<VertexType> newVertices, std::vector<unsigned long> newIndices, ID3D11DeviceContext* deviceContext, char* textureFilename, int size, int count, void* instances)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBufferData(newVertices, newIndices);
	if (!result)
	{
		return false;
	}

	result = InitializeBuffers(device, size, count, instances);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	if (m_Texture == NULL)
	{
		return NULL;
	}
	else
	{
		return m_Texture->GetTexture();
	}
}

bool ModelClass::InitializeBuffers(ID3D11Device* device, int size, int count, void* instances)
{
	HRESULT result;

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Create the instance array.

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = size * count;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);

	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.


	return true;
}

bool ModelClass::InitializeBufferData(std::vector<VertexType> newVertices, std::vector<unsigned long> newIndices)
{
	HRESULT result;
	
	// Set the number of vertices in the vertex array.
	m_vertexCount = newVertices.size();

	// Set the number of indices in the index array.
	m_indexCount = newIndices.size();

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!vertices)
	{
		return false;
	}

	for each (VertexType newVertex in newVertices)
	{
		vertices[counter] = newVertex;
		counter++;
	}

	counter = 0;

	for each (unsigned long newIndex in newIndices)
	{
		indices[counter] = newIndex;
		counter++;
	}
}

void ModelClass::ShutdownBuffers()
{
	// Release the instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

//void ModelClass::RenderColor(ID3D11DeviceContext* deviceContext)
//{
//	unsigned int strides[2];
//	unsigned int offsets[2];
//	ID3D11Buffer* bufferPointers[2];
//
//
//	// Set the buffer strides.
//	strides[0] = sizeof(VertexType); 
//	strides[1] = sizeof(ParticleType);
//
//									  // Set the buffer offsets.
//	offsets[0] = 0;
//	offsets[1] = 0;
//
//	// Set the array of pointers to the vertex and instance buffers.
//	bufferPointers[0] = m_vertexBuffer;
//	bufferPointers[1] = m_instanceBuffer;
//
//	// Set the vertex buffer to active in the input assembler so it can be rendered.
//	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
//
//	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
//	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //<--- Replace to what ever topology you are using
//
//	return;
//}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	
	//unsigned int stride;
	//unsigned int offset;

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(ParticleType);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	//// Set the vertex buffer to active in the input assembler so it can be rendered.
	//deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

ID3D11Buffer* ModelClass::GetInstanceBuffer()
{
	return m_instanceBuffer;
}