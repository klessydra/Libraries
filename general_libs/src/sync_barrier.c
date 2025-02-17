#include"functions.h"
#include <stdio.h>

int key_barr = 0;

int barrier_completed[THREAD_POOL_SIZE]; 
int arrived_at_barrier[THREAD_POOL_SIZE];
int sync_barrier_register[THREAD_POOL_SIZE];
int key;  // key to be used for atomic operations
int *ptr_key;

void sync_barrier_reset()
{
	int my_hart;
	my_hart = Klessydra_get_coreID();
	sync_barrier_register[my_hart] = 0;
}

void sync_barrier_thread_registration()
{
	__asm__("csrw 0x300, 0x8;" ); // each thread enables it's own interrupt
	int my_hart;
	my_hart = Klessydra_get_coreID();
	arrived_at_barrier[my_hart] =  0;	
	sync_barrier_register[my_hart] = 1;
}


#if USE_KLESSYDRA_M == 0

void sync_barrier()
{	
    int my_hart, i;
	int *ptr_key = &key_barr;
    my_hart = Klessydra_get_coreID();
    
    if(sync_barrier_register[my_hart] == 1)  // checks if the thread entering was registered with the sync_barrier_thread_registration function
    {
    	klessydra_lock_acquire(ptr_key);   // the following routine must be done atomically	
	    barrier_completed[my_hart] = 1;    // this set to 1 to indicate that all threads arrived, if not it will be reset to zero as done below
	    arrived_at_barrier[my_hart] = 1;   // identifies the core that the current thread with the thread_id in "my_hart" has arrived
	    for (i=0;i<THREAD_POOL_SIZE; i++)  // 
		{
			if (arrived_at_barrier[i] == 0 && sync_barrier_register[i] == 1) 
			{
				barrier_completed[my_hart] = 0;  // reset to zero not all the threads have arrived at the barrier function
			}
		}
	    if (barrier_completed[my_hart] == 0)  // send the waiting threads to a WFI state
	    {
			klessydra_lock_release(ptr_key);  // release lock acquired previously allowing the other threads to execute the routine
			__asm__(
				"WFI;"
				://no output register
				://no input register
				://no clobbered register*/
				);
	    }
	    else 
	    {
			klessydra_lock_release(ptr_key);  // release lock acquired previously allowing the other threads to execute the routine
			for (i=0;i<THREAD_POOL_SIZE; i++)
			{
				arrived_at_barrier[i] = 0;
			}
			int irq_set = 0;
			for (i=0;i<THREAD_POOL_SIZE; i++)
			{
				if (my_hart != i  &&  sync_barrier_register[i] == 1) 
				{
					send_sw_irq(i);
				}
				sync_barrier_register[i]=0;  // The thread that enters this condition turns off all the registered threads
			}
			barrier_completed[my_hart] = 0;
	    }
    }
}

#endif


#if USE_KLESSYDRA_M == 1

void sync_barrier()
{
    int my_hart, i;
	int *ptr_key = &key_barr;
    my_hart = Klessydra_get_coreID();
    
    if(sync_barrier_register[my_hart] == 1)  // checks if the thread entering was registered with the sync_barrier_thread_registration function
    {
    	klessydra_lock_acquire(ptr_key);   // the following routine must be done atomically	
	    barrier_completed[my_hart] = 1;    // this set to 1 to indicate that all threads arrived, if not it will be reset to zero as done below
	    arrived_at_barrier[my_hart] = 1;   // identifies the core that the current thread with the thread_id in "my_hart" has arrived
	    for (i=0;i<THREAD_POOL_SIZE; i++)  // 
		{
			if (arrived_at_barrier[i] == 0 && sync_barrier_register[i] == 1) 
			{
				barrier_completed[my_hart] = 0;  // reset to zero not all the threads have arrived at the barrier function
			}
		}
	    if (barrier_completed[my_hart] == 0)  // send the waiting threads to a WFI state
	    {
			klessydra_lock_release(ptr_key);  // release lock acquired previously allowing the other threads to execute the routine
			__asm__(
				"WFI;"
				://no output register
				://no input register
				://no clobbered register*/
				);
	    }
	    else 
	    {
			klessydra_lock_release(ptr_key);  // release lock acquired previously allowing the other threads to execute the routine
			for (i=0;i<THREAD_POOL_SIZE; i++)
			{
				arrived_at_barrier[i] = 0;
			}
			int irq_set = 0;
			for (i=0;i<THREAD_POOL_SIZE; i++)
			{
				if (my_hart != i  &&  sync_barrier_register[i] == 1) 
				{
					irq_set = irq_set + (1 << i); // this will create a vector of bits where the index of every high bit represents the thread to wakeup 
				}
				sync_barrier_register[i]=0;  // The thread that enters this condition turns off all the registered threads
			}
			send_multi_sw_irq(irq_set);
			barrier_completed[my_hart] = 0;
	    }
    }
}

#endif
