#pragma once
#include <string>

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class ShaderUtil
{

private:
	//�� �� ID
	unsigned int mProgramId;
	//type & source �� ȡ shader �� �� ��
	unsigned int GetCompiledShader(unsigned int shader_type, const std::string& shader_source);

public:
	ShaderUtil() {}
	~ShaderUtil() {}

	// Load a vertex and a fragment shader from file
	// �� Ϊ �� �� �� �� Ƭ
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	// Use the program
	void Use();

	// Delete the program
	void Delete();



};
