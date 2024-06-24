#include <glad/glad.h>
#include "FrogEngine.h"
using namespace FrogEngine;
#include <iostream>
#include <fstream>
#include <sstream>

std::map<const char*, Shader*> Shader::_shaders;

Shader* Shader::LoadShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath)
{
	_shaders[name] = new Shader(name, vertexShaderPath, fragmentShaderPath);
	return _shaders[name];
}

Shader* Shader::GetShader(const char* name)
{
	return _shaders[name];
}

Shader::Shader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath)
{
	name = name;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ��֤ifstream��������׳��쳣��
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// ���ļ�
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		// ��ȡ�ļ��Ļ������ݵ���������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();
		// ת����������string
		std::string vertexCode = vShaderStream.str();
		std::string fragmentCode = fShaderStream.str();

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//������ɫ������
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//����ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		//�����ɫ�������Ƿ����ɹ�
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR : VERTEX SHADER ("<< fragmentShaderPath <<") COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//Ƭ����ɫ������
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//����Ƭ����ɫ������
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		//�����ɫ�������Ƿ����ɹ�
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR : FRAGMENT SHADER (" << vertexShaderPath << ") COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//������ɫ������
		_shaderProgram = glCreateProgram();
		//��ɫ�����ӵ�������
		glAttachShader(_shaderProgram, vertexShader);
		glAttachShader(_shaderProgram, fragmentShader);
		//����
		glLinkProgram(_shaderProgram);
		//�����ɫ������״̬
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR : SHADER (" << name << ") COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		//���ӽ�����Shader����ɾ����
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR : SHADER FILE(" << vertexShaderPath << "," << fragmentShaderPath << ") NOT_SUCCESFULLY_READ\n" << std::endl;
	}
}

Shader::~Shader()
{

}

void Shader::Use()
{
	glUseProgram(_shaderProgram);
}

void Shader::SetBool(const char* valueName, bool value) const
{
	int valueLocation = glGetUniformLocation(_shaderProgram, valueName);
	glUniform1i(valueLocation, (int)value);
}

void Shader::SetInt(const char* valueName, int value) const
{
	int valueLocation = glGetUniformLocation(_shaderProgram, valueName);
	glUniform1i(valueLocation, value);
}

void Shader::SetFloat(const char* valueName, float value) const
{
	int valueLocation = glGetUniformLocation(_shaderProgram, valueName);
	glUniform1f(valueLocation, value);
}

void Shader::SetMat4(const char* valueName, Matrix4 value) const
{
	unsigned int valueLocation = glGetUniformLocation(_shaderProgram, valueName);
	glUniformMatrix4fv(valueLocation, 1, GL_FALSE, value.ValuePtr());
}

void Shader::SetVector3(const char* valueName, Vector3 value) const
{
	unsigned int valueLocation = glGetUniformLocation(_shaderProgram, valueName);
	glUniform3f(valueLocation, value.GetX(), value.GetY(), value.GetZ());
}