#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////

//AntTweakBar
#include <AntTweakBar.h>

//Exporting
//#include <assimp\Importer.hpp>
//#include <assimp\scene.h>
//#include <assimp\postprocess.h>
#include <iostream>
#include <fstream>

//Base
#include <directxmath.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>   

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	//Tess
	struct TriangleIndices
	{
		int v1;
		int v2;
		int v3;

		TriangleIndices(int a, int b, int c)
		{
			v1 = a;
			v2 = b;
			v3 = c;
		}
		
	};
	//Tess

	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool Initialize(int, int, HWND);
	void Shutdown();
	void sendModel(ModelClass*);
	/*void CreateCube();*/
	void CreateSphere();
	/*void CreateRectangle();
	void CreatePlain();*/
	D3DClass* m_Direct3D;
	ModelClass* m_Model;
	std::vector<ModelClass*> m_objects;
	//Tess
	//int addVertex(XMFLOAT3 point);
	//int GetMiddlePoint(int p1, int p2);
	//Tess

	//Exporting
	void ExportModels();
	//Exporting

	bool Frame(CameraClass* mCamera);

	float height = 1;
	float width = 2;
	float depth = 4;

	XMFLOAT3 Rotation = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT3 origin = XMFLOAT3(0.0,0.0,0.0);

private:
	bool Render(CameraClass* mCamera);
	//Tess
	std::vector<TriangleIndices*> faces;
private:
	//Tess
	ModelClass::VertexType currentVertex;
	int index;
	std::map<INT64, int> middlePointIndexCache;
	//Tess
	TwBar *myBar;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
};

#endif