#pragma once

#include <iostream>
#include "GL/glew.h"	//this line have to be before freeglut
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLSLProgram.h"

#pragma comment (lib,"freeglut.lib")
#pragma comment (lib,"glew32.lib")

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace opengl
{
	//constants
	const float NCP = 0.1f;
	const float FCP = 150.0f;
	const float ANGLE = 75.f;
	
	//globals
	int m_iWindowId;
	const std::string sWindowTitle = "OGL Cube";		//name of the window
	unsigned int iWidthWindow = 800, iHeightWindow = 600;	//width & height of the viewport
	
	//variables
	glm::mat4x4 mProjMatrix, mModelMatrix, mViewMatrix;
	CGLSLProgram m_program;
	GLuint m_iIndexVAO;
	float m_fAngle;	//this variable is just for spinning the cube

	//cube definition
	const int iNVertices = 36;
	glm::vec4 vec_points[iNVertices];
	glm::vec4 vec_colors[iNVertices];
	glm::vec4 vec_positions[8] = {
    glm::vec4( -0.5f, -0.5f,  0.5f, 1.0f ),
    glm::vec4( -0.5f,  0.5f,  0.5f, 1.0f ),
    glm::vec4(  0.5f,  0.5f,  0.5f, 1.0f ),
    glm::vec4(  0.5f, -0.5f,  0.5f, 1.0f ),
    glm::vec4( -0.5f, -0.5f, -0.5f, 1.0f ),
    glm::vec4( -0.5f,  0.5f, -0.5f, 1.0f ),
    glm::vec4(  0.5f,  0.5f, -0.5f, 1.0f ),
    glm::vec4(  0.5f, -0.5f, -0.5f, 1.0f )};
	glm::vec4 colors[8] = {
			glm::vec4( 0.f, 0.f, 0.f, 1.f ),  // black
			glm::vec4( 1.f, 0.f, 0.f, 1.f ),  // red
			glm::vec4( 1.f, 1.f, 0.f, 1.f ),  // yellow
			glm::vec4( 0.f, 1.f, 0.f, 1.f ),  // green
			glm::vec4( 0.f, 0.f, 1.f, 1.f ),  // blue
			glm::vec4( 1.f, 0.f, 1.f, 1.f ),  // magenta
			glm::vec4( 0.5f, 0.5f, 0.5f, 0.5f ),  // grey
			glm::vec4( 0.f, 1.f, 1.f, 1.f )   // cyan
	};

	///
	/// A function to create two triangles based on the quad definition
	///
	/// @iIndex an integer to access into the vectors (color and points)
	/// @a definition of the 1st index into the </code>vec_position</code> variable
	/// @b definition of the 2nd index into the </code>vec_position</code> variable
	/// @c definition of the 3rd index into the </code>vec_position</code> variable
	/// @d definition of the 4th index into the </code>vec_position</code> variable
	void quad(int& iIndex, int a, int b, int c, int d )
	{
		vec_colors[iIndex] = colors[a]; vec_points[iIndex] = vec_positions[a]; iIndex++;
		vec_colors[iIndex] = colors[b]; vec_points[iIndex] = vec_positions[b]; iIndex++;
		vec_colors[iIndex] = colors[c]; vec_points[iIndex] = vec_positions[c]; iIndex++;
		vec_colors[iIndex] = colors[a]; vec_points[iIndex] = vec_positions[a]; iIndex++;
		vec_colors[iIndex] = colors[c]; vec_points[iIndex] = vec_positions[c]; iIndex++;
		vec_colors[iIndex] = colors[d]; vec_points[iIndex] = vec_positions[d]; iIndex++;
	}

	///
	/// Simple function to construct <code>iNVertices</code> vertexes over the definition of 6 faces of a cube
	///
	void colorcube()
	{
		int iIndex = 0;	
		quad(iIndex, 1, 0, 3, 2 );
		quad(iIndex, 2, 3, 7, 6 );
		quad(iIndex, 3, 0, 4, 7 );
		quad(iIndex, 6, 5, 1, 2 );
		quad(iIndex, 4, 5, 6, 7 );
		quad(iIndex, 5, 4, 0, 1 );
	}

	///
	/// Function to initialize OGL variables + shader's loading + VAO + VBO
	///
	void initialize()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		
		mModelMatrix = glm::mat4();
		mViewMatrix = glm::mat4();
		glewInit();	
		colorcube();

		m_program.loadShader("shaders/basic.vert", CGLSLProgram::VERTEX);
		m_program.loadShader("shaders/basic.geom", CGLSLProgram::GEOMETRY);
		m_program.loadShader("shaders/basic.frag", CGLSLProgram::FRAGMENT);
		m_program.create_link();
		m_program.enable();
			m_program.addAttribute("vVertex");
			m_program.addAttribute("vColor");
			m_program.addAttribute("vNormal");
			m_program.addUniform("mView");
			m_program.addUniform("mProjection");
			m_program.addUniform("mModel");
		m_program.disable();

		//VAO
		glGenVertexArrays(1, &m_iIndexVAO);
		glBindVertexArray(m_iIndexVAO);
		//VBO - create and initialize a buffer object
		GLuint iIdBuffer;
		glGenBuffers(1, &iIdBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, iIdBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec_points) +sizeof(vec_colors), NULL, GL_STATIC_DRAW );
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec_points), vec_points);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec_points), sizeof(vec_colors), vec_colors);
		
			glEnableVertexAttribArray(m_program.getLocation("vVertex"));
			glVertexAttribPointer(m_program.getLocation("vVertex"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //Vertex
			glEnableVertexAttribArray(m_program.getLocation("vColor"));
			glVertexAttribPointer(m_program.getLocation("vColor"), 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vec_points))); //Colors
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_fAngle = 0.f;
	}

	///
	/// The display OGL function
	///
	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.15f, 0.15f, 0.15f, 1.f);	//a grey color

		mViewMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,-1.5));	//a little bit 
		mModelMatrix = glm::rotate(glm::mat4(), m_fAngle, glm::vec3(0,1,0));

		m_program.enable();
			glUniformMatrix4fv(m_program.getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
			glUniformMatrix4fv(m_program.getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
			glUniformMatrix4fv(m_program.getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
			glBindVertexArray(m_iIndexVAO);
				glDrawArrays(GL_TRIANGLES, 0, iNVertices);
			glBindVertexArray(0);
		m_program.disable();

		glutSwapBuffers();
		if (++m_fAngle > 360.f) m_fAngle -= 360.f;	//for the spinning
	}

	///
	/// A simple calling to the display function
	///
	void idle()
	{
		glutPostRedisplay();
	}

	///
	/// The classical resized function in GLUT, including the perspective matrox construction
	///
	void reshape(int w, int h)
	{
		if(h == 0)h = 1;
		float fRatio = float(w) / float(h);
		opengl::iWidthWindow = w;
		opengl::iHeightWindow = h;
		glViewport(0, 0, w, h);
		float k = 90;
		opengl::mProjMatrix = glm::perspective(k, fRatio, opengl::NCP, opengl::FCP);
	}

	///
	/// This function can be used to delete or close instances previously created
	///
	void terminate()
	{
		std::cout << "the end" << std::endl;
		exit(0);
	}

	///
	///The classical keyboard manager GLUT function, ESC key to exit
	///
	void keyboard(unsigned char key, int x, int y)
	{
		if(key == 27)	//'ESC'
			opengl::terminate();
	}
};


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(opengl::iWidthWindow, opengl::iHeightWindow);
	glutInitContextFlags(GLUT_DEBUG);
	opengl::m_iWindowId = glutCreateWindow(opengl::sWindowTitle.c_str());
	opengl::initialize();
	glutDisplayFunc(opengl::display);
	glutIdleFunc(opengl::idle);
	glutReshapeFunc(opengl::reshape);
	glutKeyboardFunc(opengl::keyboard);
  glutCloseFunc(opengl::terminate);
	glutMainLoop();
	return 0;
}