#version 330

in vec2 UV;

out vec4 color;

uniform sampler2D myTexture;

uniform float alpha;

void main()
{
	vec3 tempColor = texture2D(myTexture,UV).rgb;
	
	color = vec4(tempColor.xyz,alpha);
}