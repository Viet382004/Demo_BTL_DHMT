#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	//float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) /*+ sizeof(Vertices[1].rgba)*/;

int CurrentWidth = 800,
CurrentHeight = 800;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };


bool
translated = false,
rotated = false,
scaled = false;
// ------------------------------------------
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

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
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
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

//================================ HÌNH DUNG PHÒNG HỌC CHÍNH=====================================

mat4 model_phongchinh;

void TuongBen(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.9, 0.7, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SanNha(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.6, 0.5);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TranNha(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 0.93, 0.87);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongSau(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.6, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TuongTruoc(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.6, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void phongchinh(float x, float y, float z, int goc)
{
	model_phongchinh = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));

	
	// Phần tường trên cửa sổ
	TuongBen(15.0, 5.0, -25.0, 0.5, 4.0, 10.0); // Tường phía trên cửa sổ 1
	TuongBen(15.0, 5.0, -5.0, 0.5, 4.0, 10.0);  // Tường phía trên cửa sổ 2
	TuongBen(15.0, 5.0, 15.0, 0.5, 4.0, 10.0); // Tường phía trên cửa sổ 3

	// Phần tường dưới của cửa sổ 1
	TuongBen(15.0, -5.0, -25.0, 0.5, 4.0, 10.0); // Tường phía dưới cửa sổ 1
	TuongBen(15.0, -5.0, -5.0, 0.5, 4.0, 10.0);  // Tường phía dưới cửa sổ 2
	TuongBen(15.0, -5.0, 15.0, 0.5, 4.0, 10.0); // Tường phía dưới cửa sổ 3

	TuongBen(15.0, 0.0, -33.0, 0.5, 14.0, 6.0); // Giữa dau và cửa sổ 1
	TuongBen(15.0, 0.0, -15.0, 0.5, 14.0, 10.0); // Giữa cửa sổ 1 và cửa sổ 2
	TuongBen(15.0, 0.0, 5.0, 0.5, 14.0, 10.0);  // Giữa cửa sổ 2 và cửa sổ 3
	TuongBen(15.0, 0.0, 23.0, 0.5, 14.0, 6.0); // Giữa cửa sổ 3 và cuoi

	// Các tường bên phải 
	TuongBen(-15.0, 0.0, -5.0, 0.5, 14.0, 40); // Phần tường bên phải

	TuongBen(-15.0, 3.5, -27.5, 0.5, 7.0, 5.0); // Tường phía trên cửa 2
	TuongBen(-15.0, 3.5, 17.5, 0.5, 7.0, 5.0); // Tường phía trên cửa 1

	TuongBen(-15.0, 0.0, -33.0, 0.5, 14.0, 6.0);
	TuongBen(-15.0, 0.0, 23.0, 0.5, 14.0, 6.0); 

	//Tuong truoc
	TuongTruoc(2.3, -5, 25.1, 15.5, 4, 0.2);
	TuongTruoc(2.3, 7, 25.1, 15.5, 4, 0.2);
	TuongTruoc(-10, 0, 25.1, 11, 14, 0.2);
	TuongTruoc(12, 0, 25.1, 6, 14, 0.2);
	TuongTruoc(0, 0, 25.5, 30, 14.2, 0.2);


	TuongSau(0, 0, -35.1, 30, 14.2, 0.2);
	SanNha(0, -7.1, 0, 35, 0.2, 75.0);
	TranNha(0, 7.1, 0, 35, 0.2, 75.0);
}

//===========================CỬA RA VÀO=============================
mat4 model_cuaravao;
float goccua = 30;

void cuaphai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * translate(vec3(0,0,1)) * rotate_y(goccua) * translate(vec3(0, 0, -1.25)) * scale(vec3(0.2, 7, 2.5));
	mat4 model_base = model_cuaravao * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.7, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuatrai(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * translate(vec3(0, 0, 1)) * rotate_y(-goccua) * translate(vec3(0, 0, 1.25)) * scale(vec3(0.2, 7, 2.5));
	mat4 model_base = model_cuaravao * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.7, 0.7);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuaravao(float x, float y, float z, int goc)
{
	model_cuaravao = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.0, 1.0, 1.0));
	// cửa đầu
	cuaphai(-15.0, -3.5, 19);
	cuatrai(-15.0, -3.5, 14);

	// cửa cuối 
	cuaphai(-15.0, -3.5, -26);
	cuatrai(-15.0, -3.5, -31);
}

//=======================CỬA SỔ=========================
mat4 model_cuaso;
float rem = 0.0f;

void kinh(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuaso * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 0.5, 0.6);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void songcua(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_cuaso * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhtreorem(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.4, 0.4, 10.0));
	mat4 model_base = model_cuaso * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.6, 0.6, 0.6);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void remcua(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y - (rem/2.0), z)) * scale(vec3(0.2, 6.0 + rem, 10.0));
	mat4 model_base = model_cuaso * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void cuaso()
{
	kinh(15.0, 0.0, -25.0, 0.1, 6.0, 10.0); // Cửa sổ 1
	songcua(15.0, 0.0, -25.0, 0.2, 6.0, 0.3);
	thanhtreorem(14.55, 3.2, -25.0);
	remcua(14.5, 0.0, -25);

	kinh(15.0, 0.0, -5.0, 0.1, 6.0, 10.0); // Cửa sổ 2
	songcua(15.0, 0.0, -5.0, 0.2, 6.0, 0.3);
	thanhtreorem(14.55, 3.2, -5.0);
	remcua(14.5, 0.0, -5);

	kinh(15.0, 0.0, 15.0, 0.1, 6.0, 10.0); // Cửa sổ 3
	songcua(15.0, 0.0, 15.0, 0.2, 6.0, 0.3);
	thanhtreorem(14.55, 3.2, 15.0);
	remcua(14.5, 0.0, 15);
}


//===============================ĐIỀU HÒA=================================
mat4 model_dieuhoa;
float alp = 150;
int dir = 1;

void phantren(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(2.0, 2.0, 6.0));
	// TuongBen(15.0, 0.0, -15.0, 0.5, 14.0, 10.0);
	mat4 model_base = model_dieuhoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void phansau(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.1, 2.0, 6.0));
	// TuongBen(15.0, 0.0, -15.0, 0.5, 14.0, 10.0);
	mat4 model_base = model_dieuhoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.2, 0.2, 0.2);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void phanduoi(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * rotate_z(60) * scale(vec3(2.25, 2.25, 1.0));
	mat4 model_base = model_dieuhoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void canhdieuhoa(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * rotate_z(alp) * translate(vec3(1.0, 0.0, 0.0)) * scale(vec3(2.0, 0.2, 4.0));
	mat4 model_base = model_dieuhoa * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void dieuhoa()
{
	phantren(13.75, 6.0, -15.0);
	phanduoi(14.3, 5.4, -12.5);
	phanduoi(14.3, 5.4, -17.5);
	phansau(14.75, 5.0, -15.0);
	canhdieuhoa(14.75, 4.0, -15.0);  
}


//=========== Đồng Hồ ===========================================
mat4 model_clock, model_view_clock;
float rotation_angle = 0.0f;

void clock_face(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_clock * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 1.0, 1.0, 1.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void clock_border(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_clock * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void clock_hand(float x, float y, float z, float length, float width, float thickness, float angle)
{
	mat4 instance = identity_mat4();
	// Di chuyển kim đến tâm đồng hồ
	instance = translate(vec3(x, y, z)) *
		// Xoay kim
		rotate_y(angle) *
		// Di chuyển điểm gốc của kim xuống một nửa chiều dài để kim quay quanh đầu
		translate(vec3(0.0f, 0.0f, length / 2)) *
		// Scale kim theo kích thước mong muốn
		scale(vec3(width, thickness, length));

	mat4 model_base = model_clock * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void clock_center(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_clock * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void update_rotation()
{
	rotation_angle += 1.0f;
}

void clock(float x, float y, float z, float goc)
{
	model_clock = translate(vec3(x, y, z)) * scale(vec3(1, 1, 1)) * rotate_x(goc);

	// Kim phút quay nhanh hơn
	float minute_angle = rotation_angle;

	// Kim giờ quay chậm hơn
	float hour_angle = rotation_angle / 12.0f;

	// Vẽ viền đồng hồ
	clock_border(0.0, 0.0, 0.0, 2.2, 0.1, 2.2);

	// Vẽ mặt đồng hồ
	clock_face(0.0, 0.01, 0.0, 2.0, 0.1, 2.0);

	// Vẽ kim giờ (ngắn và dày)
	clock_hand(0.0, 0.02, 0.0, 0.8, 0.15, 0.1, hour_angle);

	// Vẽ kim phút (dài và mảnh)
	clock_hand(0.0, 0.03, 0.0, 1.0, 0.1, 0.1, minute_angle);

	// Vẽ tâm đồng hồ
	clock_center(0.0, 0.04, 0.0, 0.15, 0.1, 0.15);
}
//===============================QUẠT TRẦN==================================
mat4 model_quattran;
float qtqt[] = { 0, 0, 0 };
//bool check_qt = false;
int tocdo_qt = 2;

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
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 1.0, 1.2);
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
		glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 1.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void canhquat_quattran(float x, float y, float z, int goc)
{
	mat4 instance = identity_mat4();
	instance = rotate_y(goc) * translate(vec3(x, y, z)) * scale(vec3(2.5, 0.05, 0.5));
	mat4 model_base = model_quattran * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.0, 1.0, 1.0);
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
void nhieu_quattran()
{
	quattran(8.0, 6.75, 14.0, 0);
	quattran(8.0, 6.75, -8.0, 0);
	quattran(8.0, 6.75, -25.0, 0);
	quattran(-8.0, 6.75, 14.0, 0);
	quattran(-8.0, 6.75, -8.0, 0);
	quattran(-8.0, 6.75, -25.0, 0);
}

//=============================== SINH VIÊN ==================================
mat4 model_nguoi;
float ngng[] = { 0, 0, 0 };

void body(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.46, 0.71, 0.81);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void upper_leg(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
void lower_leg(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void upper_arm(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
void lower_arm(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void neck(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void head(float x, float y, float z, float x1, float y1, float z1, float r, float g, float b)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_nguoi * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Robot(float x, float y, float z, float goc)
{
	model_nguoi = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1.5, 1.5, 1.5));
	body(0, 0, 0, 1, 1.6, 0.4);
	neck(0, 0.9, 0, 0.25, 0.25, 0.25, 1, 0.8, 0.76);

	mat4 model_nguoi_bandau = model_nguoi;
	model_nguoi = model_nguoi_bandau * translate(vec3(0, 1.2, 0)) * rotate_z(ngng[0]) * translate(vec3(0, -1.2, 0));
	head(0, 1.3, 0, 0.6, 0.6, 0.4, 1, 0.8, 0.76);

	model_nguoi = model_nguoi_bandau * translate(vec3(0.3, -1.0, 0)) * rotate_x(ngng[1]) * translate(vec3(0.3, 1.0, 0));
	upper_leg(-0.3, -1.0, 0, 0.4, 0.4, 0.2, 0.46, 0.71, 0.81);
	upper_leg(-0.3, -1.6, 0, 0.2, 0.8, 0.16, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.3, -1.0, 0)) * rotate_x(-ngng[1]) * translate(vec3(0.3, 1.0, 0));
	upper_leg(-0.9, -1.0, 0, 0.4, 0.4, 0.2, 0.46, 0.71, 0.81);
	upper_leg(-0.9, -1.6, 0, 0.2, 0.8, 0.16, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.0, 0.6, 0)) * rotate_x(-ngng[1]) * translate(vec3(0.0, -0.6, 0));
	upper_arm(0.65, 0.6, 0, 0.3, 0.4, 0.16, 0.46, 0.71, 0.81);
	upper_arm(0.65, 0.1, 0, 0.2, 0.6, 0.14, 1, 0.8, 0.76);
	model_nguoi = model_nguoi_bandau * translate(vec3(0.0, 0.6, 0)) * rotate_x(ngng[1]) * translate(vec3(0.0, -0.6, 0));
	upper_arm(-0.65, 0.6, 0, 0.3, 0.4, 0.16, 0.46, 0.71, 0.81);
	upper_arm(-0.65, 0.1, 0, 0.2, 0.6, 0.14, 1, 0.8, 0.76);
}

void nhieu_nguoi()
{	
	//Sinh Vien
	Robot(0, -4, 0, 0);
	Robot(5, -4, 9, 0);
	Robot(10, -4, 9, 0);
	Robot(-5, -4, 9, 0);
	Robot(-10, -4, 9, 0);
	Robot(5, -4, 4, 0);
	Robot(10, -4, 4, 0);
	Robot(-5, -4, 4, 0);
	Robot(-10, -4, 4, 0);
	Robot(5, -4, -1, 0);
	Robot(10, -4, -1, 0);
	Robot(-5, -4, -1, 0);
	Robot(-10, -4, -1, 0);
	//Giang vien
	Robot(11, -2, 22, 180);
}


//============================ BÀN GHẾ SINH VIÊN ===============================
//=========== BÀN ==========

mat4 model_ban, model_view_ban;

void mat_ban(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.55, 0.35, 0.23);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ban(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ngan_ban(float x, float y, float z, float x1, float y1, float z1) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.55, 0.35, 0.23); // Màu khác để phân biệt
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanh_noi(float x, float y, float z, float x1, float y1, float z1) {
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ban * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.7, 0.7, 0.7); // Màu khác để dễ nhận biết
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ban(float x, float y, float z, int goc)
{
	model_ban = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(1, 1, 1));
	mat_ban(0.0, 0.0, 0.0, 2.0, 0.1, 5.0);
	chan_ban(0.8, -1.2, 2.0, 0.15, 2.4, 0.15);   // Chân trước bên phải
	chan_ban(0.8, -1.2, -2.0, 0.15, 2.4, 0.15);  // Chân sau bên phải
	chan_ban(-0.8, -1.2, 2.0, 0.15, 2.4, 0.15);  // Chân trước bên trái
	chan_ban(-0.8, -1.2, -2.0, 0.15, 2.4, 0.15); // Chân sau bên trái
	ngan_ban(0.0, -0.4, 0.0, 1.8, 0.1, 4.0); // Ngăn bàn
}
//=========== GHẾ ==========

mat4 model_ghe, model_view_ghe;
float gg[] = { 0, 0, 0 };

void mat_ghe(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.6, 0.4);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void chan_ghe(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_ghe * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.8, 0.8, 0.8);
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
	mat_ghe(0.0, 0.0, 0.0, 1.0, 0.1, 5.0);
	chan_ghe(0.3, -1.05, 2.0, 0.15, 2.0, 0.15);
	chan_ghe(0.3, -1.05, -2.0, 0.15, 2.0, 0.15);
	chan_ghe(-0.3, -1.05, 2.0, 0.15, 2.0, 0.15);
	chan_ghe(-0.3, -1.05, -2.0, 0.15, 2.0, 0.15);
}

void ban_ghe() {

	//===============Ban ben phia trai================
	//Ban 4
	ban(-5.25, -4.0, -4.0, 90);
	ghe(-5.25, -4.95, -6.5, -90);

	//Ban 4
	ban(-10.5, -4.0, -4.0, 90);
	ghe(-10.5, -4.95, -6.5, -90);

	//Ban 3
	ban(-5.25, -4.0, 1.0, 90);
	ghe(-5.25, -4.95, -1.5, -90);

	//Ban 3
	ban(-10.5, -4.0, 1.0, 90);
	ghe(-10.5, -4.95, -1.5, -90);

	//Ban 2
	ban(-5.25, -4.0, 6.0, 90);
	ghe(-5.25, -4.95, 3.5, -90);

	//Ban 2
	ban(-10.5, -4.0, 6.0, 90);
	ghe(-10.5, -4.95, 3.5, -90);

	//Ban 1
	ban(-5.25, -4.0, 11.0, 90);
	ghe(-5.25, -4.95, 8.5, -90);

	////Ban 1
	ban(-10.5, -4.0, 11, 90);
	ghe(-10.5, -4.95, 8.5, -90);

	//Ban 5
	ban(-5.25, -4.0, -9.0, 90);
	ghe(-5.25, -4.95, -11.5, -90);

	//Ban 5
	ban(-10.5, -4.0, -9.0, 90);
	ghe(-10.5, -4.95, -11.5, -90);

	//Ban 6
	ban(-5.25, -4.0, -14.0, 90);
	ghe(-5.25, -4.95, -16.5, -90);

	//Ban 6
	ban(-10.5, -4.0, -14.0, 90);
	ghe(-10.5, -4.95, -16.5, -90);

	//Ban 7
	ban(-5.25, -4.0, -19.0, 90);
	ghe(-5.25, -4.95, -21.5, -90);

	//Ban 7
	ban(-10.5, -4.0, -19.0, 90);
	ghe(-10.5, -4.95, -21.5, -90);

	//Ban 8
	ban(-5.25, -4.0, -24.0, 90);
	ghe(-5.25, -4.95, -26.5, -90);

	//Ban 8
	ban(-10.5, -4.0, -24.0, 90);
	ghe(-10.5, -4.95, -26.5, -90);

	//Ban 9
	ban(-5.25, -4.0, -29.0, 90);
	ghe(-5.25, -4.95, -31.5, -90);

	//Ban 9
	ban(-10.5, -4.0, -29.0, 90);
	ghe(-10.5, -4.95, -31.5, -90);


	//===============Ban ben phia phai================
	//Ban 4
	ban(5.25, -4.0, -4.0, 90);
	ghe(5.25, -4.95, -6.5, -90);

	//Ban 4
	ban(10.5, -4.0, -4.0, 90);
	ghe(10.5, -4.95, -6.5, -90);

	//Ban 3
	ban(5.25, -4.0, 1.0, 90);
	ghe(5.25, -4.95, -1.5, -90);

	//Ban 3
	ban(10.5, -4.0, 1.0, 90);
	ghe(10.5, -4.95, -1.5, -90);

	//Ban 2
	ban(5.25, -4.0, 6.0, 90);
	ghe(5.25, -4.95, 3.5, -90);

	//Ban 2
	ban(10.5, -4.0, 6.0, 90);
	ghe(10.5, -4.95, 3.5, -90);

	//Ban 1
	ban(5.25, -4.0, 11.0, 90);
	ghe(5.25, -4.95, 8.5, -90);

	////Ban 1
	ban(10.5, -4.0, 11, 90);
	ghe(10.5, -4.95, 8.5, -90);

	//Ban 5
	ban(5.25, -4.0, -9.0, 90);
	ghe(5.25, -4.95, -11.5, -90);

	//Ban 5
	ban(10.5, -4.0, -9.0, 90);
	ghe(10.5, -4.95, -11.5, -90);

	//Ban 6
	ban(5.25, -4.0, -14.0, 90);
	ghe(5.25, -4.95, -16.5, -90);

	//Ban 6
	ban(10.5, -4.0, -14.0, 90);
	ghe(10.5, -4.95, -16.5, -90);

	//Ban 7
	ban(5.25, -4.0, -19.0, 90);
	ghe(5.25, -4.95, -21.5, -90);

	//Ban 7
	ban(10.5, -4.0, -19.0, 90);
	ghe(10.5, -4.95, -21.5, -90);

	//Ban 8
	ban(5.25, -4.0, -24.0, 90);
	ghe(5.25, -4.95, -26.5, -90);

	//Ban 8
	ban(10.5, -4.0, -24.0, 90);
	ghe(10.5, -4.95, -26.5, -90);

	//Ban 9
	ban(5.25, -4.0, -29.0, 90);
	ghe(5.25, -4.95, -31.5, -90);

	//Ban 9
	ban(10.5, -4.0, -29.0, 90);
	ghe(10.5, -4.95, -31.5, -90);


}

//============================ BÀN GHẾ GIẢNG VIÊN  ===============================

mat4 model_bangv;
float tdtd[] = { 0, 0, 0 };
float dcbgv[] = { 0, 0, 0 };
void mattruoc() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0.42)) * scale(vec3(0.8, 0.4, 0.02));
	mat4 tudong = model_bangv * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void matphai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.39, 0, 0.21)) * scale(vec3(0.02, 0.4, 0.4));
	mat4 tudong = model_bangv * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void mattrai_tudong() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.39, 0, 0.21)) * scale(vec3(0.02, 0.4, 0.4));
	mat4 tudong = model_bangv * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.81, 0.91, 0.96);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void naptrai() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(0.2, 0.21, 0.01)) * rotate_x(tdtd[0]) * translate(vec3(0, 0, 0.2)) * scale(vec3(0.4, 0.02, 0.44));
	mat4 tudong = model_bangv * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.49, 0.62, 0.76);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void napphai() {
	mat4 instance = identity_mat4();
	instance = translate(vec3(-0.2, 0.21, 0.01)) * rotate_x(tdtd[1]) * translate(vec3(0, 0, 0.2)) * scale(vec3(0.4, 0.02, 0.44));
	mat4 tudong = model_bangv * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, tudong.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.49, 0.62, 0.76);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void banchogv(float x, float y, float z, int goc) {
	model_bangv = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(6.0, 6.0, 6.0));
	//THEM DI CHUYEN BAN =================================================================
	model_bangv = model_bangv * translate(vec3(dcbgv[0], dcbgv[1], dcbgv[3]));
	mattruoc();
	matphai_tudong();
	mattrai_tudong();
	naptrai();
	napphai();
}


//====================== CUỐN VỞ ===========================

mat4 model_cuonvo, model_view_cuonvo;
float cuonvo1[] = { 0.0,0.0,0.0 };

void trang1(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.7, 0.1, 1.0));
	mat4 model_base = model_cuonvo * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.624, 0.878, 0.894);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void trang2(float x, float y, float z)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(0.7, 0.1, 1.0));
	mat4 model_base = model_cuonvo * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.294, 0.702, 0.8);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}



void cuonvo(float x, float y, float z, float goc)
{
	model_cuonvo = translate(vec3(x, y, z)) * rotate_y(goc) * scale(vec3(0.8, 0.8, 0.8));
	trang1(0.0, -2.25, 0.0);
	model_cuonvo = model_cuonvo * translate(vec3(0.0, -2.25, 0.5)) * rotate_x(cuonvo1[0]) * translate(vec3(0.0, 2.25, -0.5));
	trang2(0.0, -2.25, 0.0);
}


void nhieu_cuonvo()
{

	cuonvo(-9.5, -2.1, 11.0, -90);
	cuonvo(9.5, -2.1, 11.0, -90);
	cuonvo(-4.5, -2.1, 11.0, -90);
	cuonvo(4.5, -2.1, 11.0, -90);
	cuonvo(-3.5, -2.1, 11.0, -90);
	cuonvo(3.5, -2.1, 11.0, -90);
	cuonvo(-3.5, -2.1, 6.0, -90);
	cuonvo(3.5, -2.1, 6.0, -90);
	cuonvo(-9.5, -2.1, 6.0, -90);
	cuonvo(9.5, -2.1, 6.0, -90);
	cuonvo(-3.5, -2.1, 1.0, -90);
	cuonvo(3.5, -2.1, 1.0, -90);
	cuonvo(-9.5, -2.1, 1.0, -90);
	cuonvo(9.5, -2.1, 1.0, -90);
}


//====================== BẢNG ĐEN ===========================

mat4 model_bangden;
float dcbden[3] = {0, 0, 0};
void nen(float x, float y, float z, float goc)
{
	mat4 instance = identity_mat4();
	// DI CHUYEN BANG DEN
	instance = translate(vec3(x, y, z)) * scale(vec3(13.5, 8.0, 0.1)) * translate(vec3(dcbden[0], dcbden[1], dcbden[2]));
	mat4 model_base = model_bangden * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.1f, 0.1f, 0.1f); // Màu đen cho nền
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void bangden()
{
	nen(2.3, 0.9, 25.1, 180);
}

//====================== BỤC GIẢNG ===========================

void bucgiang(float x, float y, float z, float x1, float y1, float z1)
{
	mat4 instance = identity_mat4();
	instance = translate(vec3(x, y, z)) * scale(vec3(x1, y1, z1));
	mat4 model_base = model_phongchinh * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_base.m);
	glUniform3f(glGetUniformLocation(ProgramId, "objectColor"), 0.75, 0.6, 0.0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void buc()
{
	bucgiang(3.5,-6.5,23.0,23.0,1.2,5.0);
	bucgiang(11.0, -6.5, 20.0, 8.0, 1.2, 4.0);
}





vec3	eye(0.0f, 0.0f, 20.0f),
at(0.0f, 0.0f, 0.0f),
up(0.0f, 1.0f, 0.0f);

float pitch = 0.0f;  // Xoay lên/xuống
float yaw = 0.0f;    // Xoay trái/phải

mat4 pitch_matrix = rotate_x(pitch);
mat4 yaw_matrix = rotate_y(yaw);
// Tạo ma trận quay tổng hợp
mat4 rotation_matrix = yaw_matrix * pitch_matrix;
vec3 up_direction = multiply_mat4_vec3(rotation_matrix, up);


void DisplayFunc(void)
{
	mat4 pitch_matrix = rotate_x(pitch);
	mat4 yaw_matrix = rotate_y(yaw);
	mat4 rotation_matrix = yaw_matrix * pitch_matrix;

	vec3 forward_direction = normalize(at - eye); // Hướng nhìn hiện tại
	vec3 rotated_forward = multiply_mat4_vec3(rotation_matrix, forward_direction);

	vec3 new_at = eye + rotated_forward; // Cập nhật điểm nhìn
	vec3 new_up = multiply_mat4_vec3(rotation_matrix, up); // Cập nhật hướng lên

	view_mat_cpp = lookat(eye, new_at, new_up);

	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//======= VIỆT =============
	phongchinh(0, 0, 0, 0);
	nhieu_quattran();
	nhieu_nguoi();
	nhieu_cuonvo();
	bangden();
	ban_ghe();
	buc();
	banchogv(10.5, -4.5, 21.0, 180);
	
	clock(0.0f, 2.0f, -35.02f, 90);
	
	cuaso();
	dieuhoa();

	cuaravao(0, 0, 0, 0);


	GLuint vertex_color_location = glGetUniformLocation(ProgramId, "vertex_color");
	glUniform4f(vertex_color_location, 0.0f, 0.0f, 1.0f, 1.0f);
	glUniform4f(vertex_color_location, 1.0f, 0.0f, 0.0f, 1.0f);


	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
void IdleFunc(void)
{
	// =================Quạt trần=============
	qtqt[0] += 10.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	qtqt[1] += 20.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	qtqt[2] += 90.0f;
	if (qtqt[0] > 360.0f) {
		qtqt[0] -= 360.0f;
	}

	// ==================ĐIỀU HÒA====================
	alp += dir * 0.1f;
	if (alp <= 165.0f) dir = 1;
	if (alp >= 190.0f) dir = -1;


	// ===================ĐỒNG HỒ=====================
	update_rotation();

	
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;

	case 'z':
		tocdo_qt += 1;
		if (tocdo_qt > 3) {
			tocdo_qt = 0;
		}
		glutPostRedisplay();
		break;


	case 'E':
		ngng[0] += 10;
		if (ngng[0] > 30) ngng[0] = 30;
		glutPostRedisplay();
		break;
	case 'R':
		ngng[0] -= 10;
		if (ngng[0] < -30) ngng[0] = -30;
		glutPostRedisplay();
		break;
	case 'T':
		ngng[1] += 5;
		if (ngng[1] > 30) ngng[1] = 30;
		glutPostRedisplay();
		break;
	case 'Y':
		ngng[1] -= 5;
		if (ngng[1] < -30) ngng[1] = -30;
		glutPostRedisplay();
		break;


	case 'P':
		gg[0] -= 0.1;
		if (gg[0] < -0.2) gg[0] = -0.2;
		glutPostRedisplay();
		break;
	case 'O':
		gg[0] += 0.1;
		if (gg[0] > 1) gg[0] = 1;
		glutPostRedisplay();
		break;


	case 'Q':
		cuonvo1[0] += 30;
		if (cuonvo1[0] > 180) cuonvo1[0] = 180;
		glutPostRedisplay();
		break;
	case 'W':
		cuonvo1[0] -= 30;
		if (cuonvo1[0] < 0) cuonvo1[0] = 0;
		glutPostRedisplay();
		break;


	case 'w':  // Di chuyển camera về phía trước
		eye.z -= 0.5f;
		at.z -= 0.5f;
		break;
	case 's':  // Di chuyển camera về phía sau
		eye.z += 0.5f;
		at.z += 0.5f;
		break;
	case 'd':  // Di chuyển camera sang trái
		eye.x -= 0.5f;
		at.x -= 0.5f;
		break;
	case 'a':  // Di chuyển camera sang phải
		eye.x += 0.5f;
		at.x += 0.5f;
		break;
	case 'q':  // Di chuyển camera lên trên
		eye.y += 0.5f;
		at.y += 0.5f;
		break;
	case 'e':  // Di chuyển camera xuống dưới
		eye.y -= 0.5f;
		at.y -= 0.5f;
		break;

	case 'j':  // Xoay camera sang trái (yaw - tăng)
		yaw -= 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;
	case 'l':  // Xoay camera sang phải (yaw - giảm)
		yaw += 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay

		break;
	case 'i':  // Xoay camera lên (pitch - tăng)
		pitch += 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;
	case 'k':  // Xoay camera xuống (pitch - giảm)
		pitch -= 2.0f; // Điều chỉnh giá trị này để thay đổi tốc độ quay
		break;
	
		
		//Di chuyen ban giang vien va bang
	case 'A':
		dcbgv[0] -= 0.1;
		dcbden[0] -= 0.1;
		glutPostRedisplay();
		break;
	case 'S':
		dcbgv[0] += 0.1;
		dcbden[0] += 0.1;
		glutPostRedisplay();
		break;
	case 'D':
		dcbgv[2] -= 0.1;
		dcbden[1] -= 0.1;
		glutPostRedisplay();
		break;
	case 'F':
		dcbgv[2] += 0.1;
		dcbden[1] += 0.1;
		glutPostRedisplay();
		break;


	// Đóng mở cửa
	case '[':
		goccua += 10.0f;
		if (goccua > 100) goccua = 100;
		glutPostRedisplay();
		break;
	case ']':
		goccua -= 10.0f;
		if (goccua < 0) goccua = 0;
		glutPostRedisplay();
		break;

	// Rèm
	case '<':
		rem += 1.0f;
		if (rem > 0) rem = 0;
		glutPostRedisplay();
		break;
	case '>':
		rem -= 1.0f;
		if (rem < -6) rem = -6;
		glutPostRedisplay();
		break;
	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Lớp học");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
