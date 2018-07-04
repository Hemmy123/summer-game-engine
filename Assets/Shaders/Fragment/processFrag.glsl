#version 150 core

uniform sampler2D 	screenTex;
uniform vec2 		pixelSize;
uniform int 		isVertical;
uniform float 	time;

in Vertex{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 colour;

const float weights[5] = float[]( 0.12, 0.22, 0.32, 0.22, 0.12);


void main(void ){

//	vec2 values[5];
//
//	if(isVertical == 1){
//		values = vec2[](
//			vec2(0.0, -pixelSize.y * 3),
//			vec2(0.0, -pixelSize.y * 2),
//			vec2(0.0, pixelSize.y),
//			vec2(0.0, pixelSize.y * 2),
//			vec2(0.0, pixelSize.y * 3));
//
//	}
//	else{
//		values = vec2[](
//			vec2(-pixelSize.x * 3,	0.0),
//			vec2(-pixelSize.x * 2,	0.0),
//			vec2(pixelSize.x,		0.0),
//			vec2(pixelSize.x * 2,	0.0),
//			vec2(pixelSize.x * 3,	0.0));
//	}
//
//	 for(int i = 0; i < 5 ; i++){
//
//
//	 	 vec4 tmp = texture(screenTex, IN.texCoord.xy + values[i]);
//
//	 	 colour += tmp * weights[i];
//
//	 }
	// colour = texture(screenTex, IN.texCoord.xy);
	colour = texture( screenTex, IN.texCoord + 0.005*vec2( sin(time+1024.0*IN.texCoord.x),cos(time+768.0*IN.texCoord.y)) );

	

}


