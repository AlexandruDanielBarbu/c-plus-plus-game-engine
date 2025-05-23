// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"

#define PI 3.141592

Camera game_camera;
GLuint vboId;
Shaders myShaders;

float angle = 0.0f;
float step = 0.1f;
float totalTime = 0.0f;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[6];

	// First Triangle
	// Set position of vertices
	verticesData[0].pos.x = -0.5f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x =  0.5f;  verticesData[1].pos.y =  0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x = -0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	// Set Color of vertices
	verticesData[0].color.x = 1.0f; verticesData[0].color.y = 0.0f; verticesData[0].color.z = 0.0f;	 // R
	verticesData[1].color.x = 0.0f; verticesData[1].color.y = 1.0f; verticesData[1].color.z = 0.0f;  // G
	verticesData[2].color.x = 0.0f; verticesData[2].color.y = 0.0f; verticesData[2].color.z = 1.0f;	 // B

	// First Triangle
	// Set position of vertices
	verticesData[3].pos.x =  0.5f;  verticesData[3].pos.y = -0.5f;  verticesData[3].pos.z =  0.0f;
	verticesData[4].pos.x =  0.5f;  verticesData[4].pos.y =  0.5f;  verticesData[4].pos.z =  0.0f;
	verticesData[5].pos.x = -0.5f;  verticesData[5].pos.y = -0.5f;  verticesData[5].pos.z =  0.0f;

	// Set Color of vertices
	verticesData[3].color.x = 1.0f; verticesData[3].color.y = 1.0f; verticesData[3].color.z = 0.0f;	 // Y
	verticesData[4].color.x = 0.0f; verticesData[4].color.y = 1.0f; verticesData[4].color.z = 0.0f;  // G
	verticesData[5].color.x = 0.0f; verticesData[5].color.y = 0.0f; verticesData[5].color.z = 1.0f;	 // B
	
	
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	Matrix mRotation;
	mRotation.SetRotationZ(angle);

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(Vector3));
	}

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (float*)mRotation.m);
	}

	Matrix modelMatrix;
	modelMatrix.SetRotationZ(angle);

	Matrix MVP = modelMatrix * game_camera.viewMatrix * game_camera.perspectiveMatrix;

	if (myShaders.modelViewPerspectiveUniform != -1)
	{
		glUniformMatrix4fv(myShaders.modelViewPerspectiveUniform, 1, GL_FALSE, &MVP.m[0][0]);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	// Update the timer with delta time
	totalTime += deltaTime;

	if (totalTime > Globals::frameTime) {
		// Reset the timer of the update loop
		totalTime -= Globals::frameTime;

		// Set camera deltaTime
		game_camera.setDeltaTime(Globals::frameTime);

		// Perform update operations here
		angle += step;
	
		if (angle >= 2 * PI)
			angle -= 2 * PI;
	}
}

#define MOVEMENT_STEP 10.0f
void Key ( ESContext *esContext, unsigned char key, bool bIsPressed) {
	printf("Key:\t%c\tpressed?\t%d\n", key, (int)bIsPressed);

	switch (key) {
	case 'w': case 'W':
		game_camera.moveOz(-MOVEMENT_STEP);
		break;

	case 's': case 'S':
		game_camera.moveOz(MOVEMENT_STEP);
		break;

	case 'd': case 'D':
		game_camera.moveOx(MOVEMENT_STEP);
		break;

	case 'a': case 'A':
		game_camera.moveOx(-MOVEMENT_STEP);
		break;

	case 'q': case 'Q':
		game_camera.moveOy(MOVEMENT_STEP);
		break;

	case 'e': case 'E':
		game_camera.moveOy(-MOVEMENT_STEP);
		break;

	case VK_UP:
		game_camera.rotateOx(MOVEMENT_STEP);
		break;

	case VK_DOWN:
		game_camera.rotateOx(-MOVEMENT_STEP);
		break;

	case VK_RIGHT:
		game_camera.rotateOy(-MOVEMENT_STEP);
		break;
	
	case VK_LEFT:
		game_camera.rotateOy(MOVEMENT_STEP);
		break;

	case 'c': case 'C':
		game_camera.rotateOz(-MOVEMENT_STEP);
		break;

	case 'z': case 'Z':
		game_camera.rotateOz(MOVEMENT_STEP);
		break;

	default:
		break;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

