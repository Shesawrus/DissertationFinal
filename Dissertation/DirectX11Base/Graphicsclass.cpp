////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Model = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

	bool result;

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;

	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	

	TwInit(TW_DIRECT3D11, m_Direct3D->GetDevice()); // for Direct3D 11
	TwWindowSize(800, 600);
	myBar = TwNewBar("Menu");

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the color shader object.", "Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::sendModel(ModelClass* m_ModelClass)
{
	m_objects.push_back(m_ModelClass);
}

void GraphicsClass::Shutdown()
{

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	return;
}


bool GraphicsClass::Frame(CameraClass* mCamera)
{
	bool result;

	// Render the graphics scene.
	result = Render(mCamera);
	if (!result)
	{
		return false;
	}
	return true;
}


bool GraphicsClass::Render(CameraClass* mCamera)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.5f, 1.0f);

	// Generate the view matrix based on the camera's position.
	mCamera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	mCamera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	

	for each(ModelClass* modelList in m_objects)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		modelList->Render(m_Direct3D->GetDeviceContext());
		// Render the model using the color shader.
		
		if (modelList->GetTexture() == NULL)
		{
			result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), modelList->GetIndexCount(), modelList->GetVertexCount(), 1000,worldMatrix, viewMatrix, projectionMatrix);
		}
		else
		{	
			// Render the model using the texture shader.
			result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), modelList->GetIndexCount(), 4, worldMatrix, viewMatrix, projectionMatrix, modelList->GetTexture());
		}
	}

	if (!result)
	{
		return false;
	}

	TwRefreshBar(myBar);
	TwDraw();
	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}
