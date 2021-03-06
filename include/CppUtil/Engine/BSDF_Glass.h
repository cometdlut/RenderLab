#ifndef _ENGINE_MATERIAL_BSDF_GLASS_H_
#define _ENGINE_MATERIAL_BSDF_GLASS_H_

#include <CppUtil/Engine/BSDF.h>

namespace CppUtil {
	namespace Engine {
		class BSDF_Glass : public BSDF {
			ELE_SETUP(BSDF_Glass)
		public:
			BSDF_Glass(float ior = 1.f, const glm::vec3 & transmittance = glm::vec3(1), const glm::vec3 & reflectance = glm::vec3(1))
				: ior(ior), transmittance(transmittance), reflectance(reflectance) { }

			virtual glm::vec3 F(const glm::vec3 & wo, const glm::vec3 & wi, const glm::vec2 & texcoord) { return glm::vec3(0); }

			// probability density function
			virtual float PDF(const glm::vec3 & wo, const glm::vec3 & wi, const glm::vec2 & texcoord) { return 0; }

			// PD is probability density
			// return albedo
			// @arg0 in
			// @arg1 out
			// @arg2 out
			virtual glm::vec3 Sample_f(const glm::vec3 & wo, const glm::vec2 & texcoord, glm::vec3 & wi, float & pd);

			virtual bool IsDelta() const { return true; }

		public:
			float ior;
			glm::vec3 transmittance;
			glm::vec3 reflectance;
		};
	}
}

#endif//!_ENGINE_MATERIAL_BSDF_GLASS_H_
