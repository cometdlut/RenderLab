#ifndef _ENGINE_COMPONENT_GEOMETRY_H_
#define _ENGINE_COMPONENT_GEOMETRY_H_

#include <CppUtil/Engine/Component.h>

namespace CppUtil {
	namespace Engine {
		class Primitive;

		class Geometry : public Component {
			COMPONENT_SETUP(Geometry)
		public:
			Geometry(Basic::Ptr<SObj> sobj, Basic::Ptr<Primitive> primitive)
				: Component(sobj), primitive(primitive) { }

			Basic::Ptr<Primitive> GetPrimitive() { return primitive; }
			void SetPrimitive(Basic::Ptr<Primitive> primitive) { this->primitive = primitive; }
		private:
			Basic::Ptr<Primitive> primitive;
		};
	}
}

#endif//!_ENGINE_COMPONENT_GEOMETRY_H_