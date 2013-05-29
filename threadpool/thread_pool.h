/**
 * thread_pool.h
 *
 */

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include "platform_def.h"

#if defined WIN32

#define thr_THREAD HANDLE
#define thr_THREAD_RET unsigned
#define thr_THREAD_CALL __stdcall

#define thr_MUTEX HANDLE
#define thr_SEM HANDLE

#elif defined LINUX

#define thr_THREAD pthread_t
#define thr_THREAD_RET void*
#define thr_THREAD_CALL

#define thr_MUTEX pthread_mutex_t

typedef struct
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int count;
} thr_thread_sem_t;
#define thr_SEM thr_thread_sem_t

#elif defined VXWORKS

#define thr_THREAD pthread_t
#define thr_THREAD_RET void*
#define thr_THREAD_CALL

#define thr_MUTEX pthread_mutex_t

typedef struct
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int count;
} thr_thread_sem_t;
#define thr_SEM thr_thread_sem_t

#endif

typedef thr_THREAD_RET ( thr_THREAD_CALL *thr_THREAD_FUNC )( void *arg );

#define thr_THREAD_RET_SETPRI           -1

#define thr_MUTEX_RET_CREATEFAILED      -1
#define thr_MUTEX_RET_NOTOWNER          -2
#define thr_MUTEX_RET_LOCKERROR         -3
#define thr_MUTEX_RET_UNLOCKERROR       -4

#define thr_SEM_RET_CREATEFAILED        -1
#define thr_SEM_RET_POSTERROR           -2
#define thr_SEM_RET_WAITERROR           -3
#define thr_SEM_RET_TIMEOUT             -4

//////////////////////////////// threapool mode start /////////////////////////////
#define THRDPOOL_OK     0
#define ETOOMANYCLTS   -1

#define runLog sprintf
typedef struct {
	thr_THREAD *pthrds;
	UINT32 count;
} thrdtab_t;

typedef enum { IDLE, WAITING, PROCESSING } cltstate_t;
typedef void *(*thrdfunc_t)(void *);

typedef struct {
	thrdfunc_t thrdfunc;
	void *arg;
} thrdcall_t;

typedef struct {
	UINT32 cltid;
	cltstate_t state;     /* the current state of this client */
	thrdcall_t thrdcall;  /* the function excuted by thread defined by user */
	thrdcall_t thrdexit;  /* the function excuted by thread when process finishes */
	UINT32 pri;           /* priority */
} clt_t;

typedef struct {
	clt_t *pclts;
	UINT32 count;         /* the max count of clients permited */
	UINT32 waitcount;     /* the count of clients in WAITING state */
	UINT32 proscount;     /* the count of clients in PROCESSING state */
	UINT32 prino;         /* increasing number, used to set the coming client's priority */
} clttab_t;

typedef struct {
	thrdtab_t thrdtab;
	clttab_t clttab;
	thr_MUTEX thrdmutex;
	thr_SEM thread_sem;
	UINT8 logfile[256];   /* run log file name */
} thrdpool_t;

//////////////////////////////// threapool mode end  /////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

	/**
     * Function:		thr_thread_create
     * Description:    creates a thread
     * Input:    
     * handle		pointer to the handle of thread which will be created
     * func		pointer to the function to be executed by the thread
     * arg			pointer to a variable to be passed to the thread
     * Output:			        
     * Return:  
     * The thr_thread_create function returns TRUE if successful. 
     * Otherwise, it returns FALSE.
     * Others:         
	 */
	BOOL thr_thread_create( thr_THREAD* handle, thr_THREAD_FUNC func, void *arg );

	/**
     * Function:		thr_thread_join
     * Description:    waits the thread to terminate
     * Input:     
     * handle		the handle of thread which will be terminated
     * Output:			        
     * Return:         none
     * Others:         
     */
     void thr_thread_join( thr_THREAD handle );
      
	/**
     * Function:		thr_thread_exit
     * Description:    thread exit
     * Input:           
     * Output:			        
     * Return:         
     * Others:         
     */
     void thr_thread_exit( void );
      
    /**
     * Function:		thr_thread_set_priority
     * Description:    set a thread's priority
     * Input:           
     * Output:			        
     * Return:         
     * Others:         
     */
     int thr_thread_set_priority( thr_THREAD handle, int priority );
      
    /**
     * Function:		thr_thread_reschedule
     * Description:    
     * Input:           
     * Output:			        
     * Return:         
     * Others:         
     */
     int thr_thread_reschedule();
      
    /**
     * Function:		thr_mutex_init
     * Description:    initiates a mutex
     * Input:    
     * handle		pointer to the handle of mutex which will be created
     * Output:			        
     * Return: 
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_MUTEX_RET_CREATEFAILED. 
     * Others:         
     */
	int thr_mutex_init( thr_MUTEX* handle );

	/**
     * Function:		thr_mutex_destroy
     * Description:    destroys a mutex
     * Input:    
     * handle		pointer to the handle of mutex which will be destroyed           
     * Output:			        
     * Return:     
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_MUTEX_RET_NOTOWNER. 
     * Others:         
     */
	int thr_mutex_destroy( thr_MUTEX* handle );

	/**
     * Function:		thr_mutex_lock
     * Description:    locks a mutex
     * Input:  
     * handle		pointer to the handle of mutex which will be locked    
     * Output:			        
     * Return:   
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_MUTEX_RET_LOCKERROR. 
     * Others:         
     */
	int thr_mutex_lock( thr_MUTEX* handle );

	/**
     * Function:		thr_mutex_unlock
     * Description:    unlocks a mutex
     * Input:     
     * handle		pointer to the handle of mutex which will be unlocked    
     * Output:			        
     * Return:    
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_MUTEX_RET_UNLOCKERROR. 
     * Others:         
     */
	int thr_mutex_unlock( thr_MUTEX* handle );

	/**
     * Function:		thr_sem_init
     * Description:    initiates a semaphore
     * Calls:           
     * Called By:       
     * Table Accessed:  
     * Table Updated:   
     * Input:           
     * handle		pointer to the handle of semaphore which will be created    
     * Output:			        
     * Return:   
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_SEM_RET_CREATEFAILED. 
     * Others:         
     */
	int thr_sem_init( thr_SEM* handle );

	/**
     * Function:		thr_sem_destroy
     * Description:    destroys a semaphore
     * Input:       
     * handle		pointer to the handle of semaphore which will be destroyed    
     * netuint		
     * Output:			        
     * Return:			none
     * Others:         
     */
     void  thr_sem_destroy( thr_SEM* handle );

	/**
     * Function:		thr_sem_post
     * Description:    unlocks a semaphore
     * Input:   
     * handle		pointer to the handle of semaphore which will be unlocked  
     * Output:			        
     * Return:  
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_SEM_RET_POSTERROR. 
     * Others:         
     */
	int thr_sem_post( thr_SEM* handle );

	/**
     * Function:		thr_sem_wait
     * Description:    locks a semaphore
     * Input: 
     * handle		pointer to the handle of semaphore which will be locked  
     * miliseconds	time-out interval, in milliseconds
     * Output:			        
     * Return:    
     * if the function succeeds, the return value is zero.
     * if the function fails, the return value is thr_SEM_RET_WAITERROR. 
     * Others:         
	 */
	int thr_sem_timewait( thr_SEM* handle, UINT32 milliseconds );


	/**
	 * FuncName    : createThrdPool
	 * Description : To create a thread pool
	 * Input       :
	 *  @maxthrds  : max thread count permit to create
	 *  @maxclts   : max clients count permit to serve
	 *  @plogfile  : log file name
	 * Output      : no
	 * Return      : the pointer of thrdpool_t instance created here.
	 */
	thrdpool_t * thr_createThrdPool( int maxthrds, int maxclts, char *plogfile );

	/**
	 * FuncName    : thrdproc
	 * Description : 
	 *                        provide a framework to do the client side real actions
	 *                        it's blocked when no client arive.
	 *
	 * Input       : void *arg, actually it's a pointer to struct thrdpool_t
	 * Output      : no
	 * Return      : viod
	 */
	thr_THREAD_RET thr_THREAD_CALL thrdproc( void *arg ) ;

	/**
	 * FuncName    : destroyThrdPool
	 * Description : free the resources the thread pool used
	 * Input       : thrdpool_t *pthrdpool
	 * Output      : no
	 * Return      : void
	 */
	void thr_destroyThrdPool( thrdpool_t *pthrdpool ) ;

	/**
	 * FuncName    : addClt
	 * Description : add a new client to the pool specified by the param pthrdpool
	 * Input       :
	 *  @pthrdpool : the thread pool to add the client to
	 *  @cltid     : the identifier used by user to identify the client, 
	 *               for example,it can be the connection descriptor returned by accept(..) call.
	 *  @thrdcall  : a struct include the real client function and it's arguments to perform by the thread
	 *  @thrdexit  : a struct include the real client function and it's arguments to perform when thrdcall finished.
	 * Output      : no
	 * Return      : 
	 *  ETOOMANYCLTS : no place for the new client
	 *  THRDPOOL_OK  : the client is successfully added into the thread pool
	 */
	int thr_addClt( thrdpool_t *pthrdpool, unsigned int cltid, thrdcall_t thrdcall, thrdcall_t thrdexit );


	/**
	 * FuncName    : thr_deletetask
	 * Description : deletetask 
	 * Input       : 
	 * Output      : no
	 * Return      : void
	 */
	int thr_deletetask(unsigned int cltid, thrdpool_t * pthrdpool);

#ifdef __cplusplus
}
#endif

#endif
