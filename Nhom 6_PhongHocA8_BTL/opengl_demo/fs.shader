#version 460

in vec3
	position_eye,
	normal_eye;

uniform mat4 view_mat_shader;

//in vec4 fragment_color;
out vec4 out_color;
uniform vec3 objectColor;

void main() {
	//-----------chỉ định các vị trí-------------
		// vị trí nguồn sáng trong thế giới
	vec3 light_position_world = vec3(0.0, 12.0, 0.0);
	// biến đổi vị trí nguồn sáng sang eye space
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

	// vị trí viewer
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);

	// chuẩn hóa normal_eye
	vec3 n_eye = normalize(normal_eye);

	// tính vector khoảng cách từ nguồn sáng đến mắt
	// hướng vector hướng từ vertex đến nguồn sáng
	// = vị trí Light - vị trí Vertex
	vec3 distance_to_light_eye = light_position_eye - position_eye;
	// chuẩn hóa vector khoảng cách từ nguồn sáng đến mắt
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

	// tính vector khoảng cách vị trí viewer và vertex
	// = vị trí viewer - vị trí vertex
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
	// chuẩn hóa	
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);

	// --------------cường độ ánh sáng khuếch tán-----------------------
		// tính cosin góc giữa vector hướng ánh sáng và vector pháp tuyến: l.n
	float dot_prod = dot(direction_to_light_eye, n_eye);
	// lấy giá trị >=0 để loại bỏ giá trị âm ứng với góc >90 độ
	dot_prod = max(dot_prod, 0.0);

	// cường độ ánh sáng đến
	// màu trắng mờ
	vec3 Ld = vec3(0.7, 0.7, 0.7);

	// hệ số phản xạ khuếch tán
	// màu cam
	vec3 Kd = vec3(1.0, 0.5, 0.0);

	// cường độ ánh sáng khuếch tán cuối cùng
	vec3 Id = Ld * Kd * dot_prod;

	// -----------------cường độ ánh sáng phản xạ-------------------		
	// blinn	
		// tính vector half way
	vec3 half_way_eye = surface_to_viewer_eye + direction_to_light_eye;
	// chuẩn hóa vector half way
	half_way_eye = normalize(half_way_eye);

	// tính cosin góc giữa vector half_way_eye và vector pháp tuyến: n.h
	float dot_prod_specular = dot(half_way_eye, n_eye);
	// lấy giá trị >=0 để loại bỏ giá trị âm ứng với góc >90 độ
	dot_prod_specular = max(dot_prod_specular, 0.0);

	// hệ số sáng bóng
	float specular_exponent = 100.0;
	// tính mũ với hệ số sáng bóng
	float specular_factor = pow(dot_prod_specular, specular_exponent);

	// ánh sáng phản xạ
	// màu trắng
	vec3 Ls = vec3(1.0, 1.0, 1.0);

	// hệ số phản xạ
	// phản xạ toàn phần, màu trắng
	vec3 Ks = vec3(1.0, 1.0, 1.0);

	// cường độ ánh sáng phản xạ cuối cùng
	vec3 Is = Ls * Ks * specular_factor;

	// --------------cường độ ánh sáng môi trường---------------
		// ánh sáng môi trường
		// màu xám
	vec3 La = vec3(0.8, 0.8, 0.8);

	// hệ số môi trường
	// phản chiếu hoàn toàn
	vec3 Ka = vec3(1.0, 1.0, 1.0);

	// cường độ ánh sáng môi trường cuối cùng
	vec3 Ia = La * Ka;

	// ------------mau cuoi cung------------
	//out_color = fragment_color;
	//out_color = vec4(Is + Id + Ia, 1.0);
	//out_color = vec4(Is + Id + Ia, 1.0) * fragment_color;
	out_color = vec4(Is + Id + Ia, 1.0) * vec4(objectColor, 1.0f);
	//out_color = vec4((Is + Id + Ia) * fragment_color.rgb, 1.0);
	//out_color = vec4(Id * fragment_color.rgb + Ia, 1.0);


}
