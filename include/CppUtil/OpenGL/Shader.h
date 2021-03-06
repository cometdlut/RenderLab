#ifndef _OPENGL_SHADER_SHADER_H_
#define _OPENGL_SHADER_SHADER_H_

typedef unsigned int uint;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace CppUtil {
	namespace OpenGL {
		class Shader {
		public:
			// constructor generates the shader on the fly
			Shader();
			Shader(const std::string &  vertexPath, const std::string & fragmentPath, const std::string & geometryPath = "");

			uint GetID() const;
			bool IsValid() const;

			// activate the shader
			bool Use() const;

			// utility uniform functions
			void SetBool(const std::string &name, bool value) const;
			void SetInt(const std::string &name, int value) const;
			void SetFloat(const std::string &name, float value) const;
			void SetFloats(const std::string &name, uint n, const float * values) const;
			void SetVec2f(const std::string &name, float value0, float value1) const;
			void SetVec2f(const std::string &name, const glm::vec2 & v) const;
			void SetVec3f(const std::string &name, float value0, float value1, float value2) const;
			void SetVec3f(const std::string &name, const glm::vec3 & v) const;
			void SetVec3fs(const std::string &name, uint n, const float * data) const;
			void SetVec4f(const std::string &name, float value0, float value1, float value2, float value3) const;
			void SetVec4f(const std::string &name, const glm::vec4 & v) const;
			void SetMat4f(const std::string &name, const float * matValue) const;
			void SetMat4f(const std::string &name, const glm::mat4 mat4) const;

			//------------
			void UniformBlockBind(const std::string &name, uint bindPoint) const;
		private:
			// utility function for checking shader compilation/linking errors.
			int CheckCompileErrors(uint shader, std::string type);
			//------------
			uint ID;
			bool valid;
		};
	}
}

#endif // !_OPENGL_SHADER_SHADER_H_
