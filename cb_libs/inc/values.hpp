#if DISJOINT==1
	#include "Disjoint_LinUCB.hpp"
	#include "info.hpp" 
	extern Linear_UCB_Disjoint linucb_disjoint_policy_object;	// Disjoint algorithm
#else
	#include "Hybrid_LinUCB.hpp"
	#include "info.hpp" 
	extern Linear_UCB_Hybrid linucb_hybrid_policy_object;		// Hybrid algorithm
#endif
void init();
