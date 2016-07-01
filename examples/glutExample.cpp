//Describimos un cubo
//*******************
//Se replican vértices para que cada cara 
//tenga una normal distinta.

//Número de vértices
const int cubeNVertex = 24; // 4 vértices x 6 caras
const int cubeNTriangleIndex = 12; // 2 triángulos por cara x  6 cara;


const unsigned int cubeTriangleIndex[] = {
	//Cara z = 1
	0,1,2,			1,3,2,
	//Cara z = -1
	4,6,5,			5,6,7,
	//Cara x = 1
	8,10,9,			9,10,11,
	//Cara x = -1
	12,13,14,		13,15,14,
	//Cara y = 1
	16,17,18,		17,19,18,
	//Cara y = -1
	20,22,21,		21,22,23,
};

//Posicíon de los vertices
const float cubeVertexPos[] = { 
	//Cara z = 1
	-1.0f,	-1.0f,	 1.0f, //0
	 1.0f,	-1.0f,	 1.0f, //1
	-1.0f,	 1.0f,	 1.0f, //2
	 1.0f,	 1.0f,	 1.0f, //3

	//Cara z = -1		   
	-1.0f,	-1.0f,	-1.0f, //4
	 1.0f,	-1.0f,	-1.0f, //5
	-1.0f,	 1.0f,	-1.0f, //6
	 1.0f,	 1.0f,	-1.0f, //7

	//Cara x = 1		   
	1.0f,	-1.0f,	-1.0f, //8
	1.0f,	-1.0f,	 1.0f, //9
	1.0f,	 1.0f,	-1.0f, //10
	1.0f,	 1.0f,	 1.0f, //11

	//Cara x = -1		   
	-1.0f,	-1.0f,	-1.0f, //12
	-1.0f,	-1.0f,	 1.0f, //13
	-1.0f,	 1.0f,	-1.0f, //14
	-1.0f,	 1.0f,	 1.0f, //15

	//Cara y = 1		   
	-1.0f,	 1.0f,	-1.0f, //16
	-1.0f,	 1.0f,	 1.0f, //17
	 1.0f,	 1.0f,	-1.0f, //18
	 1.0f,	 1.0f,	 1.0f, //19

	//Cara y = -1		   
	-1.0f,	-1.0f,	-1.0f, //20
	-1.0f,	-1.0f,	 1.0f, //21
	 1.0f,	-1.0f,	-1.0f, //22
	 1.0f,	-1.0f,	 1.0f  //23
 };


//Normal de los vertices
const float cubeVertexNormal[] = { 
	//Cara z = 1
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 

	//Cara z = -1		   
	0.0f,	0.0f,	-1.0f, 
	0.0f,	0.0f,	-1.0f, 
	0.0f,	0.0f,	-1.0f, 
	0.0f,	0.0f,	-1.0f, 

	//Cara x = 1		   
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 

	//Cara x = -1		   
	-1.0f,	0.0f,	 0.0f, 
	-1.0f,	0.0f,	 0.0f, 
	-1.0f,	0.0f,	 0.0f, 
	-1.0f,	0.0f,	 0.0f, 

	//Cara y = 1		   
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 

	//Cara y = -1		   
	0.0f,	-1.0f,	0.0f, 
	0.0f,	-1.0f,	0.0f, 
	0.0f,	-1.0f,	0.0f, 
	0.0f,	-1.0f,	0.0f  
 };


//Color de los vertices
const float cubeVertexColor[] = { 
	//Cara z = 1
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 
	0.0f,	0.0f,	 1.0f, 

	//Cara z = -1		   
	0.6f,	0.6f,	 1.0f, 
	0.6f,	0.6f,	 1.0f, 
	0.6f,	0.6f,	 1.0f, 
	0.6f,	0.6f,	 1.0f, 

	//Cara x = 1		   
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 
	1.0f,	0.0f,	 0.0f, 

	//Cara x = -1		   
	1.0f,	0.6f,	 0.6f, 
	1.0f,	0.6f,	 0.6f, 
	1.0f,	0.6f,	 0.6f, 
	1.0f,	0.6f,	 0.6f, 

	//Cara y = 1		   
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 
	0.0f,	1.0f,	0.0f, 

	//Cara y = -1		   
	0.6f,	1.0f,	0.6f, 
	0.6f,	1.0f,	0.6f, 
	0.6f,	1.0f,	0.6f, 
	0.6f,	1.0f,	0.6f  
 };

//Cood. de textura de los vertices
const float cubeVertexTexCoord[] = { 
	//Cara z = 1
	 0.0f, 0.0f,
	 1.0f, 0.0f,
	 0.0f, 1.0f,
	 1.0f, 1.0f,

	//Cara z = -1
	0.0f, 1.0f, 
	1.0f, 1.0f, 
	0.0f, 0.0f, 
	1.0f, 0.0f, 

	//Cara x = 1	
	0.0f,	1.0f,
	1.0f,	1.0f,
	0.0f,	0.0f,
	1.0f,	0.0f,

	//Cara x = -1
	0.0f,	0.0f,
	1.0f,	0.0f,
	0.0f,	1.0f,
	1.0f,	1.0f,

	//Cara y = 1	
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	//Cara y = -1
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
};

#include <reto/reto.h>
#include <glutExampleShaders.h>

using namespace reto;

#include <GL/glew.h>

#ifdef Darwin
  #define __gl_h_
  #define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GL/freeglut.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include <reto/Camera.h>
#include <reto/ShaderProgram.h>
Camera camera;
ShaderProgram prog;

//////////////////////////////////////////////////////////////
// Variables que nos dan acceso a Objetos OpenGL
//////////////////////////////////////////////////////////////

//VAO
unsigned int vao;
//VBOs que forman parte del objeto
unsigned int posVBO;
unsigned int colorVBO;
unsigned int normalVBO;
unsigned int texCoordVBO;
unsigned int triangleIndexVBO;

//////////////////////////////////////////////////////////////
// Funciones auxiliares
//////////////////////////////////////////////////////////////
//!!Por implementar

//Declaración de CB
void renderFunc();
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);

//Funciones de inicialización y destrucción
void initContext(int argc, char** argv);
void initOGL();
void initShader(const char *vname, const char *fname);
void initObj();
void destroy();

int main(int argc, char** argv)
{
	initContext(argc, argv);
	initOGL();
	initShader( RETO_EXAMPLE_SHADERS_V0_VERT,
              RETO_EXAMPLE_SHADERS_V0_FRAG );
	initObj();

	glutMainLoop(); //Escucha eventos y redirige
	destroy();

	return 0;
}
	
//////////////////////////////////////////
// Funciones auxiliares 
void initContext(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitContextVersion(3,3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GLUT example");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		exit (-1);
	}
	const GLubyte *oglVersion = glGetString(GL_VERSION);
	std::cout << "This system supports OpenGL Version: " << oglVersion << std::endl;

	glutReshapeFunc(resizeFunc);
	glutDisplayFunc(renderFunc);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(mouseFunc);
}

void initOGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	//Habilitamos el culling
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);

	/*
	proj = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);
	view = glm::mat4(1.0f);
	view[3].z = -6;
	*/
}

void destroy()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &posVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &texCoordVBO);

	glDeleteBuffers(1, &triangleIndexVBO);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);

}

void initShader(const char *vname, const char *fname)
{
	prog.load(vname, fname);
	///////////////////////////////
	// 			SAME CODE 
	///////////////////////////////
	// prog.loadVertexShader(vname);
	// prog.loadFragmentShader(fname);
	
	prog.create();
	prog.bindAttribute("inPos", 0);
	prog.bindAttribute("inColor", 1);
	prog.bindAttribute("inNormal", 2);
	prog.bindAttribute("inTexCoord", 3);
	prog.link();

	prog.addUniform("model");
	prog.addUniform("normal");
	prog.addUniform("View");
	prog.addUniform("ViewProj");

	std::cout << "---------------------------" << std::endl;

	std::cout << "model: " << prog["model"] << std::endl;
	std::cout << "normal: " << prog["normal"] << std::endl;
	std::cout << "View: " << prog["View"] << std::endl;
	std::cout << "ViewProj: " << prog["ViewProj"] << std::endl;

	prog.addAttribute("inPos");
	prog.addAttribute("inColor");
	prog.addAttribute("inNormal");
	prog.addAttribute("inTexCoord");

	std::cout << "---------------------------" << std::endl;

	std::cout << "inPos: " << prog("inPos") << std::endl;
	std::cout << "inColor: " << prog("inColor") << std::endl;
	std::cout << "inNormal: " << prog("inNormal") << std::endl;
	std::cout << "inTexCoord: " << prog("inTexCoord") << std::endl;
}

void initObj()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &posVBO);
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3, cubeVertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(prog("inPos"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(prog("inPos"));
	//std::cout << "Add inPos to VAO" << std::endl;

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO); //GL_ARRAY_BUFFERS para atributos
	glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3, cubeVertexColor, GL_STATIC_DRAW);
	glVertexAttribPointer(prog("inColor"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(prog("inColor"));
	//std::cout << "Add inColor to VAO" << std::endl;

	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 3, cubeVertexNormal, GL_STATIC_DRAW);
	glVertexAttribPointer(prog("inNormal"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(prog("inNormal"));
	//std::cout << "Add inNormal to VAO" << std::endl;

	glGenBuffers(1, &texCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, cubeNVertex*sizeof(float) * 2, cubeVertexTexCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(prog("inTexCoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(prog("inTexCoord"));
	//std::cout << "Add inTexCoord to VAO" << std::endl;

	glGenBuffers(1, &triangleIndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeNTriangleIndex*sizeof(unsigned int) * 3, cubeTriangleIndex, GL_STATIC_DRAW);

	//model = glm::mat4(1.0f);

}

void renderFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	prog.use();

	//Pintado del objeto!!!! 
	prog.sendUniform4m("View", camera.ViewMatrix( ));
	//prog.sendUniform4m("ViewProj", camera.ViewProjectionMatrix( ));
	auto vp = camera.ViewProjectionMatrix( );
	prog.sendUniform4m("ViewProj", vp);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, cubeNTriangleIndex*3,GL_UNSIGNED_INT, (void*)0);
	prog.unuse();

	glutSwapBuffers();

}

void resizeFunc(int width, int height){
	//Para ajustar el aspect ratio hay que usar la matriz projection.
	glViewport(0, 0, width, height);
}
void idleFunc(){

	//model = glm::mat4(1.0f);
	static float angle = 0.0f;
	angle = (angle > 3.141592f * 2.0f) ? 0 : angle + 0.01f;
	//model = glm::rotate(model, angle, glm::vec3(1.0f, 1.0f, 0.0f));
	glutPostRedisplay();
}
void keyboardFunc(unsigned char, int, int){}
void mouseFunc(int, int, int, int){}
