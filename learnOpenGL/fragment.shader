#version 450 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform  float alpha_percent;
void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), alpha_percent);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0f-TexCoord.x,TexCoord.y)), 0.3);
}