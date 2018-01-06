// GuiTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



void initScene();
void initGraphics(int argc, char *argv[]);
void idle();
void drawScene();
void Display();
void Reshape(int width, int height);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMouseMotion(int x, int y);
void Keyboard(unsigned char k, int x, int y);
void Special(int k, int x, int y);
void Terminate(void);

#define GUI_FPS 60
int last_idle = 0;
#ifdef _DEBUG
int lastSec = last_idle;
#endif // _DEBUG
double fps = 1000/GUI_FPS;
int timesInSec = 0;

bool FPS()
{
	int now = glutGet(GLUT_ELAPSED_TIME);
#ifdef _DEBUG
	int eSec = now - lastSec;
	if( eSec >= 1000 )
	{
		std::system("cls");
		console_log("FPS %d\n", timesInSec);
		lastSec = now;
		timesInSec = 0;
	}
#endif // _DEBUG
	int e = now - last_idle;
	if( e >= fps )
	{
		last_idle = now;
		return true;
	}
	return false;
}

void hideConsole()
{
#ifdef _DEBUG
	return;
#endif // _DEBUG
	HWND consoleWnd = GetConsoleWindow();
	ShowWindow(consoleWnd, 0);
}

int main(int argc, char *argv[])
{
	hideConsole();

	// Initialize openGL, glut, glew
	initGraphics(argc, argv);

	// Set GLUT callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(PassiveMouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	initScene();

	atexit(Terminate);  // Called after glutMainLoop ends

	glutIdleFunc(idle);
	// Call the GLUT main loop
	glutMainLoop();

	return 0;
}



void initScene()
{

	/*//create, load, compile, attach vertex and fragment shader
	g_programID = initShader("..\\Shaders\\vertexShader.glsl", "..\\Shaders\\fragmentShader.glsl");
	if(!g_programID)
	{
		std::cout << "\nFatal Error in shader creation!\n\a\a\a";
		return;
	}*/
	
}

void initGraphics(int argc, char *argv[])
{
	// Initialize GLUT
	glutInit(&argc, argv);
//	glutInitContextVersion(3, 2);
//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	
	//glutInitContextVersion(2, 0); 
	//glutInitContextVersion(3, 1);
	
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //use a framebuffer with double buffering and RGBA format. Use a z-buffer
	
	glutInitWindowSize(800, 800);
	glutCreateWindow("GuiTest");
	glutCreateMenu(NULL);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glMatrixMode( GL_MODELVIEW );


	/*// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		assert(0);
		return;
	}
	else
	{
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	}*/
}

void idle()
{
	if( FPS() )
		glutPostRedisplay();
}

void drawScene()
{
	timesInSec++;

	/*if(g_programID == 0 || m_objects.size() < 1 )
	{
		return;
	}

	glUseProgram(g_programID);
/ *	if ( m_currObj != -1 )
		m_objects[m_currObj].CGProgram();
	else
		return;* /
//	g_programID = m_objects[m_currObj].g_programID;
	GLfloat mat_rotation[16];
	ConvertQuaternionToMatrix(g_quaternion, mat_rotation);
/ *
	GLuint mat_rotation_id = glGetUniformLocation(g_programID, "rotation");
	glUniformMatrix4fv(mat_rotation_id, 1, false, mat_rotation); //glUniformMatrix4fv assumes that the matrix is given in column major order. i.e, the first four elements in "mat" array corresponds to the first column of the matrix
* /
	GLfloat mat_translation[16];
//	createTranslationMatrix(0.0f, 0.0f, -5.0f, mat_translation);
	createTranslationMatrix(float(x_translate) / screen_w, float(y_translate) / screen_h, z_translate, mat_translation);
/ *	
	GLuint mat_translation_id = glGetUniformLocation(g_programID, "translation");
	glUniformMatrix4fv(mat_translation_id, 1, false, mat_translation);
* /
	GLfloat mat_projection[16];
	createPerspectiveProjectionMatrix(1.0f, 200.0f, 0.25f, 0.25f, mat_projection);
/ *
	GLuint mat_projection_id = glGetUniformLocation(g_programID, "projection");
	glUniformMatrix4fv(mat_projection_id, 1, false, mat_projection);
* /
	GLfloat scaleFix = m_objects[m_currObj].scaleFix;
	GLuint scale_id = glGetUniformLocation(g_programID, "scale");
	glUniform1f(scale_id, g_Scale*scaleFix );

	//this will invoke the rendering of the model.
	//GL_TRIANGLES means that each three consecutive vertices in the array are connected and treated as a single triangle.
	//this means that vertices in our meshes have to be duplicated. to avoid duplication and render triangles with additional indices information, one can use glDrawElements
//	glDrawArrays(GL_TRIANGLES, 0, 36);

//	createTranslationMatrix(0.9f, 0.0f, -5.0f, mat_translation);
//	glUniformMatrix4fv(mat_translation_id, 1, false, mat_translation);

/ *	glBindVertexArray(g_vertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, 36);* /

/ *	createTranslationMatrix(0.0f, 0.0f, -5.0f, mat_translation);

	glUniformMatrix4fv(mat_translation_id, 1, false, mat_translation);* /

//	glBindVertexArray(g_vertexArrayID2);
//	glDrawArrays(GL_TRIANGLES, 0, 36);

/ *	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , g_vertexBufferObjectID3 );
	glBindBuffer( GL_ARRAY_BUFFER , g_vertexArrayID );* /
//	glDrawElements( GL_LINE_STRIP, 6 , GL_UNSIGNED_SHORT , 0 );
	if ( m_currObj != -1 )
	{
		m_objects[m_currObj].obj_material.ka = ka;
		m_objects[m_currObj].obj_material.kd = kd;
		m_objects[m_currObj].obj_material.ks = ks;

		m_objects[m_currObj].translateMat.setMatrix( mat_translation );
		m_objects[m_currObj].rotMat.setMatrix( mat_rotation );
		m_objects[m_currObj].projectionMat.setMatrix( mat_projection );
		m_objects[m_currObj].calcMVP();

		GLfloat mat_MVP [16];
		m_objects[m_currObj].MVP.getMatrix( mat_MVP );
		GLuint mat_MVP_id = glGetUniformLocation(g_programID, "MVP");
		glUniformMatrix4fv(mat_MVP_id, 1, false, mat_MVP );

		l1.setOrientation( Vector4( dir[0] , dir[1], dir[2] ) );

		GLfloat ambient [3];
		ambient[0] = ( ( glob_light & 0xFF0000 ) >> 16 ) * m_objects[m_currObj].obj_material.ka ;
		ambient[1] = ( ( glob_light & 0x00FF00 ) >> 8 ) * m_objects[m_currObj].obj_material.ka  ;
		ambient[2] = ( ( glob_light & 0x0000FF )		) * m_objects[m_currObj].obj_material.ka ;
		GLuint ambient_id = glGetUniformLocation(g_programID, "vAmbient");
		glUniform3f(ambient_id, ambient[2] / 255 , ambient[1] / 255 , ambient[0] / 255 );

		GLfloat diffuse [3];
		diffuse[0] = ( ( l1.color & 0xFF0000 ) >> 16 ) * m_objects[m_currObj].obj_material.kd ;
		diffuse[1] = ( ( l1.color & 0x00FF00 ) >> 8 ) * m_objects[m_currObj].obj_material.kd  ;
		diffuse[2] = ( ( l1.color & 0x0000FF )		) * m_objects[m_currObj].obj_material.kd ;
		GLuint diffuse_id = glGetUniformLocation(g_programID, "vDiffuse");
		glUniform3f(diffuse_id, diffuse[2] / 255 , diffuse[1] / 255 , diffuse[0] / 255 );
		GLuint light1_dir_id = glGetUniformLocation(g_programID, "Light1Dir");
		GLuint light1_pos_id = glGetUniformLocation(g_programID, "Light1Pos");
		GLuint light1_type_id = glGetUniformLocation(g_programID, "directional1");
		glUniform4f(light1_dir_id, l1.getOrientation('x') , l1.getOrientation('y') , l1.getOrientation('z') , 1.0f  );
		glUniform4f(light1_pos_id, l1.pos[0] , l1.pos[1] , l1.pos[2] , 1.0f  );
	//	glUniform4f(light1_pos_id, 0.0f , 0.0f , 500.0f , 1.0f  );
		glUniform1i(light1_type_id , !l1.type );

		m_objects[m_currObj].drawBox = m_showBox;
		m_objects[m_currObj].drawNormals = m_showNormals;
		m_objects[m_currObj].CGDraw( !m_light );
	}*/
}



//callback function called by GLUT to render screen
void Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //set the background color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //init z-buffer and framebuffer

	drawScene();

	// Present frame buffer
	glutSwapBuffers();
}




// Callback function called by GLUT when window size changes
void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	// Send the new window size to AntTweakBar
	
	glutPostRedisplay();
}


void MouseButton(int button, int state, int x, int y)
{
	
	glutPostRedisplay();
}

void MouseMotion(int x, int y)
{
	glutPostRedisplay();
}

void PassiveMouseMotion(int x, int y)
{
}


void Keyboard(unsigned char k, int x, int y)
{
	glutPostRedisplay();
}

void fullScreenToggle()
{
	glutFullScreenToggle();
}

// Function called at exit
void Terminate(void)
{
	//to do: add code for releasing opengl data such as textures and buffers

}

void Special(int k, int x, int y)
{

}


/*


void Display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //set the background color to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //init z-buffer and framebuffer

	drawScene();

	// Present frame buffer
	glutSwapBuffers();
}

int _tmain(int argc, char* argv[])
{
	// Initialize openGL, glut, glew
//	initGraphics(argc, argv);
	// Initialize AntTweakBar

	// Set GLUT callbacks
// 	glutDisplayFunc(Display);
// 	glutReshapeFunc(Reshape);
// 	glutMouseFunc(MouseButton);
// 	glutMotionFunc(MouseMotion);
// 	glutPassiveMotionFunc(PassiveMouseMotion);
// 	glutKeyboardFunc(Keyboard);
// 	glutSpecialFunc(Special);


//	atexit(Terminate);  // Called after glutMainLoop ends


	HWND consoleWnd = GetConsoleWindow();
	ShowWindow(consoleWnd, 0);
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutDisplayFunc(Display);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Gui Test");

	glutMainLoop();
	return 0;
}

*/
