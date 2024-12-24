#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	 { 0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { -0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	 // v2-v3-v0
	  { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	  { 0.5f,	-0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },
	  { 0.5f,	 0.5f,	0.5f,	1.0f },//{ 1.0f,	0.0f,	0.0f,	1.0f } },

	  // v0-v3-v4 (right)
	   { 0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	   { 0.5f,	-0.5f,   0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	   { 0.5f,	-0.5f,  -0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
	   // v4-v5-v0
		{ 0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
		{ 0.5f,	 0.5f,	-0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },
		{ 0.5f,	 0.5f,   0.5f,	1.0f },//{ 0.0f,	1.0f,	0.0f,	1.0f } },

		// v0-v5-v6 (top)
		 { 0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		 { 0.5f,	0.5f,	-0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		 { -0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		 // v6-v1-v0
		  { -0.5f,	 0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		  { -0.5f,	0.5f,	0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		  { 0.5f,	0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },

		  // v1-v6-v7 (left)
		   { -0.5f,	 0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		   { -0.5f,	0.5f,	-0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		   { -0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
		   // v7-v2-v1
			{ -0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
			{ -0.5f,	-0.5f,	0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },
			{ -0.5f,	0.5f,	 0.5f,	1.0f },//{ 0.0f,	0.0f,	1.0f,	1.0f } },

			// v7-v4-v3 (bottom)
			 { -0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
			 { 0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
			 { 0.5f,	-0.5f,	 0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
			 // v3-v2-v7
			  { 0.5f,	 -0.5f,	 0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
			  { -0.5f,	-0.5f,	0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },
			  { -0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.1f,	0.2f,	0.3f,	1.0f } },

			  // v4-v7-v6 (back)
			  { 0.5f,	 -0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
			  { -0.5f,	-0.5f,	-0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
			  { -0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
			  // v6-v5-v4
			  { -0.5f,	 0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
			  { 0.5f,	0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } },
			  { 0.5f,	-0.5f,	 -0.5f,	1.0f },//{ 0.4f,	0.5f,	0.6f,	1.0f } }
};
const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 700,
CurrentHeight = 700;

<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
mat4 model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;
========
//mat4 model_mat_cpp,
//view_mat_cpp,
//projection_mat_cpp;
//
//int model_mat_location,
//view_mat_location,
//projection_mat_location;
//
//float Alpha = 0.0f;
//float Beta = 0.0f;
//
//float t[] = { 0.0f, 0.0f, 0.0f };
bool translated = false;

mat4 model_mat_cpp,
view_mat_cpp,
projection_mat_cpp,
model_ban, model_view_ban;
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

int model_mat_location,
view_mat_location,
projection_mat_location;

float Alpha = 0.0f;
float Beta = 0.0f;
<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp

========
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp
float t[] = { 0.0f, 0.0f, 0.0f };


bool 
translated = false;


GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
// -----------------------------Quạt trần----------------------------------------------	

mat4 model_quattran;
float qtqt[] = { 0, 0, 0 };
int tocdo_qt = 0;

void captreo_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.5, 0.5, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void thanhtreo_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.1, 1.0, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void nap_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(0.4, 0.2, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.81, 0.83);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void dongco_quattran(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	for (int i = 0; i <= 360; i += 1) {

		instance = translate(vec3(x, y, z)) * rotate_y(i) * scale(vec3(1.0, 0.2, 0.1));
		mat4 model_base = model_quattran * instance;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.96, 0.57, 0.55);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void canhquat_quattran(float x, float y, float z, int goc)
{
	mat4 instance = identity_mat4();
	instance = rotate_y(goc) * translate(vec3(x, y, z)) * scale(vec3(2.5, 0.05, 0.5));
	mat4 model_base = model_quattran * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void quattran(float x, float y, float z, int goc)
{
	model_quattran = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	captreo_quattran(0, 0, 0);
	thanhtreo_quattran(0.0, -0.75, 0.0);
	nap_quattran(0.0, -1.35, 0.0);

	mat4 model_quattran_bd = model_quattran;
	// Chỉnh tốc độ quay của quạt(max: 3 -> 1:min)
	switch (tocdo_qt)
	{
	case 0:
		model_quattran = model_quattran_bd;
		break;
	case 1:
		model_quattran = model_quattran_bd * rotate_y(qtqt[0]);
		break;
	case 2:
		model_quattran = model_quattran_bd * rotate_y(qtqt[1]);
		break;
	case 3:
		model_quattran = model_quattran_bd * rotate_y(qtqt[2]);
		break;
	default:
		break;
	}

	dongco_quattran(0.0, -1.55, 0.0);
	canhquat_quattran(1.25, -1.55, -0.0, 0);	// Cánh quạt 1
	canhquat_quattran(1.25, -1.55, -0.0, 120);	// Cánh quạt 2
	canhquat_quattran(1.25, -1.55, -0.0, 240);	// Cánh quạt 3
}

========
// ---------------------------------------------------------------------------	
void mat_ban(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.68, 0.5, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ban(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.68, 0.5, 0.37);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ban(float x, float y, float z, int goc)
{
	model_ban = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	mat_ban(0.0, 0.0, 0.0, 2.0, 0.1, 3.4);
	chan_ban(0.9, -1.2, 1.4, 0.15, 2.5, 0.15);
	chan_ban(0.9, -1.2, -1.4, 0.15, 2.5, 0.15);
	chan_ban(-0.9, -1.2, 1.4, 0.15, 2.5, 0.15);
	chan_ban(-0.9, -1.2, -1.4, 0.15, 2.5, 0.15);
}

//ghe
mat4 model_ghe, model_view_ghe;
float gg[] = { 0, 0, 0 };

void mat_ghe(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 0.82, 0.35);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ghe(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void tua_ghe(float x, float y, float z, float x1, float y1, float z1) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1, 0.82, 0.35);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ghe(float x, float y, float z, int goc)
{
	model_ghe = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	model_ghe = model_ghe * translate(vec3(gg[0], 0, 0));
	mat_ghe(0.0, 0.0, 0.0, 1.0, 0.1, 3.4);
	chan_ghe(0.5, -0.75, 1.5, 0.15, 1.5, 0.15);
	chan_ghe(0.5, -0.75, -1.5, 0.15, 1.5, 0.15);
	chan_ghe(-0.5, -0.75, 1.5, 0.15, 1.5, 0.15);
	chan_ghe(-0.5, -0.75, -1.5, 0.15, 1.5, 0.15);
	//tua_ghe(-0.675, 0.75, 0, 0.15, 1.5, 1.0);
}
void ban_ghe() {

	ban(-4, -4.55, -4.0, 90);
	ghe(-4.0, -4.55, -6.0, -90);
	//ghe(-3.25, -4.95, -6.5, -90);
	
}
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

// ---------------------------------------------------------------------------

void DisplayFunc(void)
{
	glEnable(GL_DEPTH_TEST);



//Nhìn từ dưới lên
vec3 eye(4.0f, 2.0f, -2.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);

//Nhìn từ bên hông vào 
//vec3 eye(4.0f, -1.0f, -2.0f),
//		at(0.0f, 0.0f, 0.0f),
//		up(0.0f, 1.0f, 0.0f);

//Nhìn từ trên xuông
//vec3 eye(4.0f, -3.0f, -2.0f),
//		at(0.0f, 0.0f, 0.0f),
//		up(0.0f, 1.0f, 0.0f);

<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
========
	vec3 eye(2.0f, 2.0f, 2.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	// Các tham số của phép chiếu perspective
	float
		znear = 1.0f,
		zfar = 100.0f,
		fov = 67.0f,
		aspect = (float)CurrentWidth / CurrentHeight;

	projection_mat_cpp = perspective(fov, aspect, zfar, znear);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);


	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);

<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
========

	//model_mat_cpp = rotate_x(-45)*rotate_y(45);



	//if (translated)
	//{
	//	//model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
	//	model_mat_cpp = model_mat_cpp * translate(vec3(Beta, 0.0, 0.0));
	//	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	//}
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(Beta, 0.0, 0.0));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
	quattran(0,0,0,0);
========
	ban_ghe();
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

	glutSwapBuffers();
}
// ---------------------------------------------------------------------------	
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	
void IdleFunc(void)
{
	// Cập nhật giá trị góc quay cho các phần tử trong mảng qtqt
	qtqt[0] += 10.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	qtqt[1] += 20.0f;
	if (qtqt[1] > 360.0f) {  // Sửa điều kiện để kiểm tra qtqt[1] thay vì qtqt[0]
		qtqt[1] -= 360.0f;
	}

	qtqt[2] += 90.0f;
	if (qtqt[2] > 360.0f) {  // Sửa điều kiện để kiểm tra qtqt[2] thay vì qtqt[0]
		qtqt[2] -= 360.0f;
	}

	glutPostRedisplay();  // Yêu cầu vẽ lại màn hình
}

// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
	case 27: // Phím ESC để thoát chương trình
		exit(EXIT_SUCCESS);
		break;

	case 'z': // Tăng tốc độ quay
		tocdo_qt += 1;
		if (tocdo_qt > 5) { // Giới hạn tốc độ quay tối đa
			tocdo_qt = 5;
		}
		glutPostRedisplay(); // Cập nhật lại màn hình
		break;

	case 'x': // Giảm tốc độ quay
		tocdo_qt -= 1;
		if (tocdo_qt < 0) { // Giới hạn tốc độ quay tối thiểu
			tocdo_qt = 0;
		}
		glutPostRedisplay(); // Cập nhật lại màn hình
		break;
========
	case 27:
		exit(EXIT_SUCCESS); break;
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp
	}
}

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
<<<<<<<< HEAD:QuatTran/opengl_demo/main.cpp
	glutCreateWindow("Quat tran");
========
	glutCreateWindow("Ban ghe");
>>>>>>>> 77fe4aa (DHMT):BanGhe/BanGhe/opengl_demo/main.cpp

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}

