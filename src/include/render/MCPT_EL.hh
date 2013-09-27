//File: MCPT_EL.hh
//Date: Fri Sep 27 19:48:14 2013 +0800
//Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "render/MCPT.hh"

// MCPT with explicit lighting, better at diffuse, cannot handle caustic
class MCPT_EL : public MCPT {
	private:
		bool check_shadow_ray(const Ray& ray, const shared_ptr<Light>& light) const;

		Color do_trace(const Ray& ray, int depth = 0, int USE_EMISSION = 1) const;

		Color do_trace_adapter(const Ray& ray) const override
		{ return do_trace(ray); }

};
