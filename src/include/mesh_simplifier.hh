// File: mesh_simplifier.hh

// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once

#include <vector>
#include <unordered_set>
#include <queue>
#include "renderable/mesh.hh"
using std::vector;
using std::unordered_set;
using std::priority_queue;

class MeshSimplifier {
	private:
		Mesh& mesh;

		struct Vertex;

		struct Face {
			Vertex * vtx[3];
			Vec norm;

			Face(Vertex* a, Vertex* b, Vertex* c): vtx{a, b, c}
			{ norm = (c->pos - a->pos).cross((b->pos - a->pos)).get_normalized(); }

			// delete this face (containing u, v) when collapsing from u to v
			void delete_from(Vertex* u, Vertex* v);

			// change vertex u to v when collapsing from u to v
			void change_to(Vertex* u, Vertex* v);

#ifdef DEBUG
			inline bool contain(Vertex* v) const
			{ return (v == vtx[0]) + (v == vtx[1]) + (v == vtx[2]) == 1; }

			inline int count(Vertex* v) const
			{ return (v == vtx[0]) + (v == vtx[1]) + (v == vtx[2]); }
#endif
		};

		struct Vertex {
			Vec pos;
			int id = -1;
			bool erased = false;
			unordered_set<Vertex*> adj_vtx;
			unordered_set<Face*> adj_face;

			int cost_timestamp = 0;
			real_t cost;
			Vertex* candidate = nullptr;

			Vertex(Vec _pos, int _id = -1):pos(_pos), id(_id) {}

			inline void add_face(Face* f) {
				adj_face.insert(f);
				REP(k, 3) if (f->vtx[k] != this)
					adj_vtx.insert(f->vtx[k]);
			}

			// change adj_vtx, u to v
			void change_to(Vertex* u, Vertex* v);
		};

		struct Elem {
			// element type to use in the heap
			Vertex* v;
			int cost_timestamp;

			Elem(Vertex* _v) :
				v(_v), cost_timestamp(v->cost_timestamp) {}

			bool operator < (const Elem& r) const
			{ return v->cost > r.v->cost; }

			inline bool outofdate() const
			{ return cost_timestamp < v->cost_timestamp; }
		};

		vector<Vertex> vtxs;
		vector<Face> faces;
		int target_num;			// shrink to this number
		priority_queue<Elem> heap;

		real_t cost(Vertex*, Vertex*) const;

		void update_cost(Vertex*);

		int collapse(Vertex*, Vertex*);		// return the number of faces it simplified

		void do_simplify();

		void write_back();

	public:
		MeshSimplifier(Mesh& mesh, real_t _ratio);

		void simplify();
};
