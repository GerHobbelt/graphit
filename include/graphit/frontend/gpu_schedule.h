//
// Created by Ajay Brahmakshatriya 
//

#ifndef GRAPHIT_GPU_SCHEDULE
#define GRAPHIT_GPU_SCHEDULE

#include <assert.h>


namespace graphit {
namespace fir {
namespace gpu_schedule {


enum gpu_schedule_options {
	PUSH, 
	PULL, 
	FUSED, 
	UNFUSED_BITMAP,
	UNFUSED_BOOLMAP,
	ENABLED,
	DISABLED,
	TWC,
	TWCE,
	WM,
	CM,
	STRICT,
	EDGE_ONLY
};

class GPUSchedule {
	// Abstract class has no functions for now
};

class SimpleGPUSchedule: public GPUSchedule {

public:
	enum class direction_type {
		DIR_PUSH, 
		DIR_PULL
	};

	enum class frontier_creation_type {
		FRONTIER_FUSED, 
		UNFUSED_BITMAP,
		UNFUSED_BOOLMAP
	};

	enum class deduplication_type {
		DEDUP_ENABLED, 
		DEDUP_DISABLED
	};

	enum class load_balancing_type {
		TWC, 
		TWCE, 
		WM, 
		CM, 
		STRICT,
		EDGE_ONLY
	};

	enum class kernel_fusion_type {
		FUSION_ENABLED,
		FUSION_DISABLED
	};

private:
	direction_type direction;
	frontier_creation_type frontier_creation;
	deduplication_type deduplication;
	load_balancing_type load_balancing;
	kernel_fusion_type kernel_fusion;

public:	
	void configDirection(enum gpu_schedule_options o) {
		switch(o) {
			case PUSH:
				direction = direction_type::DIR_PUSH;
				break;
			case PULL:
				direction = direction_type::DIR_PULL;
				break;
			default:
				assert(false && "Invalid option for configDirection");
				break;
		}	
	}
	
	void configFrontierCreation(enum gpu_schedule_options o) {
		switch(o) {
			case FUSED:
				frontier_creation = frontier_creation_type::FRONTIER_FUSED;
				break;
			case UNFUSED_BITMAP:
				frontier_creation = frontier_creation_type::UNFUSED_BITMAP;
				break;
			case UNFUSED_BOOLMAP:
				frontier_creation = frontier_creation_type::UNFUSED_BOOLMAP;
				break;
			default:
				assert(false && "Invalid option for configFrontierCreation");	
				break;
		}
	}

	void configDeduplication(enum gpu_schedule_options o) {
		switch(o) {
			case ENABLED:
				deduplication = deduplication_type::DEDUP_ENABLED;
				break;
			case DISABLED:
				deduplication = deduplication_type::DEDUP_DISABLED;
				break;
			default:
				assert(false && "Invalid option for configDeduplication");
				break;
		}
	}

	void configLoadBalance(enum gpu_schedule_options o) {
		switch(o) {
			case TWC:
				load_balancing = load_balancing_type::TWC;
				break;
			case TWCE:
				load_balancing = load_balancing_type::TWCE;
				break;
			case WM:
				load_balancing = load_balancing_type::WM;
				break;
			case CM:
				load_balancing = load_balancing_type::CM;
				break;
			case STRICT:
				load_balancing = load_balancing_type::STRICT;
				break;
			case EDGE_ONLY:
				load_balancing = load_balancing_type::EDGE_ONLY;
				break;
			default:
				assert(false && "Invalid option for configLoadBalance");
				break;
		}
	}
	
	void configKernelFusion(enum gpu_schedule_options o) {
		switch(o) {
			case ENABLED:
				kernel_fusion = kernel_fusion_type::FUSION_ENABLED;
				break;
			case DISABLED:
				kernel_fusion = kernel_fusion_type::FUSION_DISABLED;
				break;
			default:
				assert(false && "Invalid option for configKernelFusion");
				break;
		}
		
	}
};

class HybridGPUSchedule: public GPUSchedule {
private:
	SimpleGPUSchedule s1;
	SimpleGPUSchedule s2;
	
	float threshold;
	// TODO: have separate alpha beta
public:	
	enum hybrid_criteria {
		INPUT_VERTEXSET_SIZE
	};
private:	
	hybrid_criteria _hybrid_criteria;
public:	
	HybridGPUSchedule (hybrid_criteria h, float t, SimpleGPUSchedule &_s1, SimpleGPUSchedule &_s2) {
		_hybrid_criteria = h;
		threshold = t;
		s1 = _s1;
		s2 = _s2;
	}
};


}
}
}

#endif
