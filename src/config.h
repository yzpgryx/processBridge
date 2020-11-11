#ifndef __CONFIG_H__
#define __CONFIG_H__

/*
 * select one of the three ways to implement to process bridge.
 * only one of them should be enabled.
 */
#define USE_MESSAGE_QUEUE	// message queue
//#define USE_SEM_SHM		// semaphore + shared memory
//#define USE_SOCKET		// socket

#endif