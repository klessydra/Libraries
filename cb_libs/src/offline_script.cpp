/*-------------------------------------------------------------------------------------------------------------
Script:      offline_script.cpp
Descrizione: Function that loads the offline dataset into the folder "Data/offline" and train the model 
			 in an offline manner. As described in the pdf, this is crucial to evaluate some important
			 figures such as the regret. In fact, due to the online nature of contextual bandits algorithm,
			 at each time instant, only the reward related to the chosen action will be known.
			 This means that it will be impossible to evaluate performances exactly and in a replicable way	     
Author:      Marco Angioli
Data:        09/02/2022
Version:     1.1
-------------------------------------------------------------------------------------------------------------*/
#include "offline_script.hpp"
Linear_UCB_Disjoint linucb_disjoint_policy_object(K,D,0.5);

void offline_mode()
{
	init();

	#if operation==1
		#if D == 4
    matrix<D,1>ct={{{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT}}}; 						                                                                  // FFT context with feature size = 4
    #elif D == 8 
    matrix<D,1>ct={{{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT},{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT}}}; 						                      // FFT context with feature size = 8
    #else
    matrix<D,1> ct={.value={{0},{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{0},{0},{0},{0},{0},{1<<SHIFT_AMOUNT}}}; 	// FFT context with feature size = 14
    #endif
	#else
		#if D == 4
    matrix<D,1>ct={.value={{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0}}};                                                               				// MATMUL 64x64 context with feature size = 4
    #elif D == 8
    matrix<D,1>ct={.value={{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0}}}; 	                  			// MATMUL 64x64 context with feature size = 4
    #else
    matrix<D,1> ct={.value={{0},{0},{1<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{0},{0},{0},{0},{0},{1<<SHIFT_AMOUNT},{1<<SHIFT_AMOUNT},{0}}}; 	// FFT with 14 feature size
    #endif
  #endif


	// Choice of best action through Disjoint Linear UCB algorithm
	int chosen_arm_index = linucb_disjoint_policy_object.select_arm(ct);

	// Initial Address print:
	if (Klessydra_get_coreID() == 0)
	{
		printf("i_addr: 0x%x\n",((unsigned)&linucb_disjoint_policy_object.linucb_arms[0] - 0x100000)/4);
		printf("\nChosen:%d\n",chosen_arm_index);
	}
		
}

void update(int chosen_arm_index, float rew)
{
	init();
 
	#if operation==1
		#if D == 4
    matrix<D,1>ct={{{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT}}}; 						                                                                  // FFT context with feature size = 4
    #elif D == 8 
    matrix<D,1>ct={{{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT},{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT}}}; 						                      // FFT context with feature size = 8
    #else
    matrix<D,1> ct={.value={{0},{1<<SHIFT_AMOUNT},{0},{0},{1<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{0},{0},{0},{0},{0},{1<<SHIFT_AMOUNT}}}; 	// FFT context with feature size = 14
    #endif
	#else
		#if D == 4
    matrix<D,1>ct={.value={{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0}}};                                                               				// MATMUL 64x64 context with feature size = 4
    #elif D == 8
    matrix<D,1>ct={.value={{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{2<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0}}}; 	                  			// MATMUL 64x64 context with feature size = 4
    #else
    matrix<D,1> ct={.value={{0},{0},{1<<SHIFT_AMOUNT},{0},{1<<SHIFT_AMOUNT},{0},{0},{0},{0},{0},{0},{1<<SHIFT_AMOUNT},{1<<SHIFT_AMOUNT},{0}}}; 	// FFT with 14 feature size
    #endif
  #endif


	// Update	
	linucb_disjoint_policy_object.linucb_arms[chosen_arm_index].reward_update(rew, ct);

	// Initial Address print:
	if (Klessydra_get_coreID() == 0)
		printf("i_addr: 0x%x\n",((unsigned)&linucb_disjoint_policy_object.linucb_arms[0] - 0x100000)/4);
}


