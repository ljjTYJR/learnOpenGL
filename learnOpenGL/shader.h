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
	//����ID
	unsigned int ID;

	//������ɫ��
	//�� �� �� ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//�������
	void use();
	//uniform ���ߺ���
	void setBool(const std::string &name, bool value) const;	//��ֵ������const�ĺ�׺��Ҫ��shader���ܹ��ı�����Ƿ���ֵ��const
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4& inputMat)const;
		//����������������ͨ��ģ�����������޸�

private:
	void checkCompileErroes(unsigned int shader, std::string type);
};
#endif // !SHADER_H
