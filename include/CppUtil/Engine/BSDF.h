#ifndef _ENGINE_MATERIAL_BSDF_H_
#define _ENGINE_MATERIAL_BSDF_H_

#include <CppUtil/Engine/MaterialBase.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace CppUtil {
	namespace Engine {
		class BSDF : public MaterialBase {
			ELE_SETUP(BSDF)
		public:
			virtual glm::vec3 F(const glm::vec3 & wo, const glm::vec3 & wi, const glm::vec2 & texcoord) = 0;

			// probability density function
			virtual float PDF(const glm::vec3 & wo, const glm::vec3 & wi, const glm::vec2 & texcoord) = 0;

			// PD is probability density
			// return albedo
			virtual glm::vec3 Sample_f(const glm::vec3 & wo, const glm::vec2 & texcoord, glm::vec3 & wi, float & PD) = 0;

			virtual glm::vec3 GetEmission() const { return glm::vec3(0); }

			virtual bool IsDelta() const = 0;

			virtual void ChangeNormal(const glm::vec2 & texcoord, const glm::vec3 & tangent, glm::vec3 & normal) const { return; };

		public:
			static glm::vec3 LocalReflect(const glm::vec3 & w) {
				return glm::vec3(-w.x, -w.y, w.z);
			}
			static bool LocalRefract(const glm::vec3& wo, glm::vec3& wi, float ior);

		protected:
			static glm::vec3 TangentSpaceNormalToWorld(const glm::vec3 & worldTangent, const glm::vec3 worldNormal, const glm::vec3 & tangentSpaceNormal);
		};
	}
}

#endif//!_ENGINE_MATERIAL_BSDF_H_
