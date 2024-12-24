#version 460
layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;
uniform mat4 model_mat_shader;
//eye
uniform mat4 view_mat_shader;
uniform mat4 projection_mat_shader;

void main(void)
{
	//gl_Position = model_mat_shader * vertex_position;
	gl_Position = projection_mat_shader * view_mat_shader * model_mat_shader * vertex_position;

	//fragment_color = vertex_color;

}
