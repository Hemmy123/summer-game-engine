#version 330 core


layout (location = 0)

in  vec3 position;
in  vec2 texCoord;
in  vec4 colour;

out Vertex	{
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(){
	gl_Position = vec4(position.x, position.y, position.z,1.0);
	
	OUT.texCoord	= texCoord;
	//OUT.colour		= colour;
	OUT.colour		= colour;
	
}

