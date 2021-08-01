#type Vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 v_TexCoord;

uniform mat4 viewProjection;
uniform mat4 model;

void main(){
	v_TexCoord = aTexCoord;
	gl_Position = viewProjection * model * vec4(aPos, 1.0);
}

#type Fragment
#version 330 core
out vec4 FragColor;
uniform vec3 u_Color;
uniform sampler2D tex;

in vec2 v_TexCoord;

void main(){
	FragColor = texture(tex, v_TexCoord);
	//FragColor = vec4(u_Color, 1.0);
	//FragColor = vec4(0.2, 0.3, 0.8, 1.0);
}