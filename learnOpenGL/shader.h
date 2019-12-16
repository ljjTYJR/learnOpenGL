#pragma once
#include <string>

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class ShaderUtil
{

private:
	//程 序 ID
	unsigned int mProgramId;
	//type & source 获 取 shader 的 数 据
	unsigned int GetCompiledShader(unsigned int shader_type, const std::string& shader_source);

public:
	ShaderUtil() {}
	~ShaderUtil() {}

	// Load a vertex and a fragment shader from file
	// 分 为 顶 点 和 面 片
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	// Use the program
	void Use();

	// Delete the program
	void Delete();



};
