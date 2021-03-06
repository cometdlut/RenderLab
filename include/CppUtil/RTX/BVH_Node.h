#ifndef _RTX_HITABLE_BVH_NODE_H_
#define _RTX_HITABLE_BVH_NODE_H_

#include <CppUtil/RTX/Hitable.h>
#include <vector>

namespace RTX {
	class BVH_Node : public Hitable{
		HITABLE_SETUP(BVH_Node)
	public:
		BVH_Node(CppUtil::Basic::CPtr<Material> material = NULL);
		BVH_Node(std::vector<Hitable::CPtr> & hitables, CppUtil::Basic::CPtr<Material> material = NULL);
		BVH_Node(const std::vector<Hitable::CPtr>::const_iterator begin, const std::vector<Hitable::CPtr>::const_iterator end, CppUtil::Basic::CPtr<Material> material = NULL);

		virtual HitRst RayIn(CppUtil::Basic::Ptr<Ray> & ray) const;
		virtual const AABB GetBoundingBox() const { return box; }
		const Hitable::CPtr GetLeft() const { return left; }
		const Hitable::CPtr GetRight() const { return right; }
	protected:
		void Build(const std::vector<Hitable::CPtr>::const_iterator begin, const std::vector<Hitable::CPtr>::const_iterator end);

		Hitable::CPtr left;
		Hitable::CPtr right;
		AABB box;
	};
}

#endif // !_RTX_HITABLE_BVH_NODE_H_
