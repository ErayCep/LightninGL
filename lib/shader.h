#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertex_path, const char* fragment_path) {
		std::string vertex_code, fragment_code;
		std::ifstream vertex_file, fragment_file;

		vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vertex_file.open(vertex_path);
			fragment_file.open(fragment_path);
			std::stringstream vertex_stream, fragment_stream;
			vertex_stream << vertex_file.rdbuf();
			fragment_stream << fragment_file.rdbuf();

			vertex_file.close();
			fragment_file.close();

			vertex_code = vertex_stream.str();
			fragment_code = fragment_stream.str();
		} catch (std::ifstream::failure& e) {
			std::cerr << "Unable to open" << std::endl;
		}

		const char* v_shader_code = vertex_code.c_str();
		const char* f_shader_code = fragment_code.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &v_shader_code, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &f_shader_code, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use() const {
		glUseProgram(ID);
	}

	void setBool(const std::string& name, bool value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), (float)value);
	}

	void setFloat(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec2(const std::string& name, glm::vec2 value) const {
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void setVec2(const std::string& name, float x, float y) const {
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}

	void setVec3(const std::string& name, glm::vec3 value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void setVec3(const std::string& name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setVec4(const std::string& name, glm::vec4 value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void setVec4(const std::string& name, float x, float y, float z, float w) const{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void setMat2(const std::string& name, glm::mat2 value) const {
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setMat3(const std::string& name, glm::mat3 value) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setMat4(const std::string& name, glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

private:
	void checkCompileErrors(GLuint shader, std::string type) {
		int success;
		char info_log[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type " << type << "\n" << info_log;
			}
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				std::cerr << "ERROR::PROGRAM_LINK_ERROR of type " << type << "\n" << info_log << std::endl;
			}
		}
	}
};


#endif
