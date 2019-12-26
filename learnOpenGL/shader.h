#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"glm.hpp"
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{
public:
	//程序ID
	unsigned int ID;

	//构造着色器
	//构 造 函 数
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//激活程序
	void use();
	//uniform 工具函数
	void setBool(const std::string &name, bool value) const;	//常值函数，const的后缀主要是shader不能够改变而不是返回值是const
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4& inputMat)const;
		//上面三个函数可以通过模板类来进行修改

private:
	void checkCompileErroes(unsigned int shader, std::string type);
};
#endif // !SHADER_H
