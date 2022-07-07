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
#include "offline_script_hybrid.hpp"
Linear_UCB_Hybrid linucb_hybrid_policy_object(KA,D,K,0.15);

void offline_mode_hr()
{
	init();                             // Initialization: load model parameters previously saved in valu5es.cpp
  
	linucb_hybrid_policy_object.init_arm();
 
	// Choice of best action through Hybrid Linear UCB algorithm
 	matrix<K,K> A_node_inv = LU_decomposition<K,K>(linucb_hybrid_policy_object.A_node);				          
 	matrix<K,1> beta_hat = mult<K,K,K,1>(A_node_inv,linucb_hybrid_policy_object.b_node); 			          
  	int chosen_arm_index = linucb_hybrid_policy_object.select_arm(ct,A_node_inv, beta_hat);

	// Final_print:
	if (Klessydra_get_coreID() == 0)
	{
		printf("i_addr: 0x%x\n",((unsigned)&linucb_hybrid_policy_object.linucb_arms[0] - 0x100000)/4);
		printf("\nChosen:%d\n",chosen_arm_index);
	}
}

void update_hr(int chosen_arm_index, float rew)
{
	init();                             // Initialization: load model parameters previously saved in values.cpp
	linucb_hybrid_policy_object.init_arm();

	// Model Update: 

	// 1) Update Phase 1:
	linucb_hybrid_policy_object.update_shared_features_matrices_phase1(linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].B,\
										     						                                 linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].A,\
								     								                                 linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].b);

	// 2) Z computation		
	matrix<K,1>data_z_array = reshape<K,AF,D>(mult<AF,1,1,D>(transpose<AF,1>(linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].arm_features),transpose<1,D>(ct)));

	// 3) Update of the expected rewards for each action:
	linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].reward_update(reward, ct, data_z_array);

	// 4) Update Phase 2:
	linucb_hybrid_policy_object.update_shared_features_matrices_phase2(data_z_array,reward,linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].B,\
                                               						                               linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].A,\
					                                                                               linucb_hybrid_policy_object.linucb_arms[chosen_arm_index].b);
	// Optimized_print:
	if (Klessydra_get_coreID() == 0)
		printf("i_addr: 0x%x\n",((unsigned)&linucb_hybrid_policy_object.linucb_arms[0] - 0x100000)/4);
}
