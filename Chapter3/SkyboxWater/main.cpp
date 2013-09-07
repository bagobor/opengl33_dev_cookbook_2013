

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "..\src\GLSLShader.h"
 
#include <SOIL.h>

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

#ifdef _DEBUG 
#pragma comment(lib, "glew_static_x86_d.lib")
#pragma comment(lib, "freeglut_static_x86_d.lib")
#pragma comment(lib, "SOIL_static_x86_d.lib")
#else
#pragma comment(lib, "glew_static_x86.lib")
#pragma comment(lib, "freeglut_static_x86.lib")
#pragma comment(lib, "SOIL_static_x86.lib")
#endif

using namespace std;

const int WIDTH  = 1280;
const int HEIGHT = 960; 

glm::mat4  P = glm::mat4(1);
glm::mat4 MV = glm::mat4(1);

int state = 0, oldX=0, oldY=0;
float rX=11, rY=64, dist = -7;
 
#include "../src/skybox.h"
CSkybox* skybox;
GLuint skyboxTextureID;

#include "../src/WaterSurface.h"
CWaterSurface* water;


const char* texture_names[6] = {"../../media/skybox/ocean/posx.png",
								"../../media/skybox/ocean/negx.png", 
								"../../media/skybox/ocean/posy.png",   
								"../../media/skybox/ocean/negy.png", 
								"../../media/skybox/ocean/posz.png",
								"../../media/skybox/ocean/negz.png"}; 
							 

 /*
const char* texture_names[6] = {"media/skybox/SaintLazarusChurch3/posx.jpg",
								"media/skybox/SaintLazarusChurch3/negx.jpg", 
								"media/skybox/SaintLazarusChurch3/posy.jpg",   
								"media/skybox/SaintLazarusChurch3/negy.jpg", 
								"media/skybox/SaintLazarusChurch3/posz.jpg",
								"media/skybox/SaintLazarusChurch3/negz.jpg"}; 
		*/					 
 /*
const char* texture_names[6] = {"media/skybox/Teide/posx.jpg",
								"media/skybox/Teide/negx.jpg", 
								"media/skybox/Teide/posy.jpg",   
								"media/skybox/Teide/negy.jpg", 
								"media/skybox/Teide/posz.jpg",
								"media/skybox/Teide/negz.jpg"};
*/							 
/*
const char* texture_names[6] = {"media/skybox/Tenerife/posx.jpg",
								"media/skybox/Tenerife/negx.jpg", 
								"media/skybox/Tenerife/posy.jpg",   
								"media/skybox/Tenerife/negy.jpg", 
								"media/skybox/Tenerife/posz.jpg",
								"media/skybox/Tenerife/negz.jpg"}; 
 */


void OnMouseDown(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN) 
	{
		oldX = x; 
		oldY = y;  
	}	

	if(button == GLUT_MIDDLE_BUTTON)
		state = 0;
	else
		state = 1; 
}

void OnMouseMove(int x, int y)
{
	if (state == 0)
		dist *= (1 + (y - oldY)/60.0f); 
	else
	{
		rY += (x - oldX)/5.0f; 
		rX += (y - oldY)/5.0f; 
	}  
	oldX = x; 
	oldY = y; 

	glutPostRedisplay(); 
}
void OnInit() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	GL_CHECK_ERRORS
	 
	//setup Skybox
	skybox = new CSkybox();

	GL_CHECK_ERRORS

	water = new CWaterSurface(1000,1000,1000,1000);
	
	//load skybox textures using SOIL 
	int texture_widths[6];
	int texture_heights[6];
	int channels[6];
	GLubyte* pData[6];
		
	cout<<"Loading skybox images: ..."<<endl;
	for(int i=0;i<6;i++) {
		cout<<"\tLoading: "<<texture_names[i]<<" ... ";
		pData[i] = SOIL_load_image(texture_names[i],	&texture_widths[i], &texture_heights[i], &channels[i], SOIL_LOAD_AUTO); 
		cout<<"done."<<endl;
	}
	
	GL_CHECK_ERRORS

	//setup OpenGL texture
    glGenTextures(1, &skyboxTextureID);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID); 
	
	GL_CHECK_ERRORS

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GL_CHECK_ERRORS

	GLint format = (channels[0]==4)?GL_RGBA:GL_RGB;
    //load the 6 images
	for(int i=0;i<6;i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, texture_widths[i], texture_heights[i], 0, format, GL_UNSIGNED_BYTE, pData[i]); 
		SOIL_free_image_data(pData[i]); 
	} 
	 
	GL_CHECK_ERRORS
	cout<<"Initialization successfull"<<endl;
}

void OnShutdown() {
	delete skybox;
	delete water;
	glDeleteTextures(1, &skyboxTextureID);
	cout<<"Shutdown successfull"<<endl;
}

void OnResize(int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	//setup the projection matrix
	P = glm::perspective(45.0f, (GLfloat)w/h, 0.1f, 1000.f);
}

void OnIdle() {
	glutPostRedisplay();
}

void OnRender() { 
	float time = glutGet(GLUT_ELAPSED_TIME)/1000.0f *0.1f;
	GL_CHECK_ERRORS
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glm::mat4 T		= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, dist));
	glm::mat4 Rx	= glm::rotate(glm::mat4(1),  rX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MV	= glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f)); 
	glm::mat4 S     = glm::scale(glm::mat4(1),glm::vec3(1000.0));
    glm::mat4 MVP	= P*MV*S;
	 
	skybox->Render( glm::value_ptr(MVP));  
	 
	MV = T*MV; 
	water->SetTime(time); 
	
	glm::vec3 eyePos;
	eyePos.x = -(MV[0][0] * MV[3][0] + MV[0][1] * MV[3][1] + MV[0][2] * MV[3][2]);
    eyePos.y = -(MV[1][0] * MV[3][0] + MV[1][1] * MV[3][1] + MV[1][2] * MV[3][2]);
    eyePos.z = -(MV[2][0] * MV[3][0] + MV[2][1] * MV[3][1] + MV[2][2] * MV[3][2]);
	water->SetEyePos(eyePos);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	water->Render(glm::value_ptr(P*MV));
	glDisable(GL_BLEND);
	glutSwapBuffers();


}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	
	glutInitContextVersion (3, 3);
	glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Skybox - OpenGL 3.3");
	glewExperimental = GL_TRUE;
	 
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		cerr<<"Error: "<<glewGetErrorString(err)<<endl;
	} else {
		if (GLEW_VERSION_3_3)
		{
			cout<<"Driver supports OpenGL 3.3\nDetails:"<<endl;
		}
	}
	err = glGetError(); //this is to ignore INVALID ENUM error 1282 
	GL_CHECK_ERRORS

	cout<<"\tUsing GLEW "<<glewGetString(GLEW_VERSION)<<endl;
	cout<<"\tVendor: "<<glGetString (GL_VENDOR)<<endl;
	cout<<"\tRenderer: "<<glGetString (GL_RENDERER)<<endl;
	cout<<"\tVersion: "<<glGetString (GL_VERSION)<<endl;
	cout<<"\tGLSL: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;

	GL_CHECK_ERRORS

	OnInit();
	glutCloseFunc(OnShutdown);

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize); 
	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutIdleFunc(OnIdle);
	glutMainLoop();	
}