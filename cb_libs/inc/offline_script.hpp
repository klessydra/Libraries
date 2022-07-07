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
#ifndef _offline_script_hpp_
#define _offline_script_hpp_
#include "Disjoint_LinUCB.hpp"
#include "info.hpp"


extern Linear_UCB_Disjoint linucb_disjoint_policy_object;	// Disjoint algorithm

// Configuration choice:
void init();
//void offline_mode();

//Update:
//void update(int chosen_c,float rew);
#endif
