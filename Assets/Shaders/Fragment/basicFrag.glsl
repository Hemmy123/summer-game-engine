#version 330 core

in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 colour;

void main(){
	colour = IN.colour;
}
