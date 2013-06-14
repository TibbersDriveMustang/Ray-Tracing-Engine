// File: kdtree.hh
// Date: Fri Jun 14 20:21:58 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "geometry/geometry.hh"
#include "geometry/aabb.hh"
#include "renderable/renderable.hh"

class KDTree {
	public:
		class Node;

		int depth = 0;
		Node* root;

		Node* build(const vector<shared_ptr<RenderAble>>& objs, const AABB& box, int depth);


};
