#version 330 core
uniform vec3 u_color;
out vec4 FragColor;
in vec2 UV;
uniform sampler2D texture_diffuse;

void main()
{
	//FragColor = o_normal;
	//FragColor = vertexColor;
	FragColor = texture(texture_diffuse, UV);
	//FragColor = vec3(u_color);
}