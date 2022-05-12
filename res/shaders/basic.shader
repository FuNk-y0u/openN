#shader vertex
#version 120

void main(void)
{
	gl_Position = ftransform();
}

#shader fragment
#version 120

uniform vec4 u_Color;

void main(void)
{
	gl_FragColor = u_Color;
}
