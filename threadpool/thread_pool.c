/**
 * thread_pool.c
 *
 */
#include "thread_pool.h"

BOOL thr_thread_create( thr_THREAD* handle, thr_THREAD_FUNC func, void *arg )
{
#if defined WIN32
	*handle = ( thr_THREAD )_beginthreadex( NULL, 0, func, arg, 0, NULL );
	if ( 0 == *handle )
	{
		return FALSE;
	}

#elif defined LINUX
	if ( handle == NULL )
	{
		return FALSE;
	}
	memset( handle, 0, sizeof( thr_THREAD ) );

	if ( pthread_create( handle, NULL, func, arg ) )
	{
		return FALSE;
	}

#elif defined VXWORKS

#define thr_THREAD_PRIORITY_INVXWORKS 10

	pthread_attr_t attr;
	struct sched_param schedparam;

	if ( handle == NULL )
	{
		return FALSE;
	}
	memset( handle, 0, sizeof( thr_THREAD ) );
	memset( &attr, 0, sizeof( attr ) );
	memset( &schedparam, 0, sizeof( schedparam ) );

	if ( pthread_attr_init( &attr ) )
	{
		return FALSE;
	}

	if ( pthread_attr_setstacksize( &attr, 512 * 1024 ) )
	{
		return FALSE;
	}

	if ( pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED ) )
	{
		return FALSE;
	}

	if ( pthread_attr_setschedpolicy( &attr, SCHED_FIFO ) )
	{
		return FALSE;
	}

	schedparam.sched_priority = thr_THREAD_PRIORITY_INVXWORKS;
	if ( pthread_attr_setschedparam( &attr, &schedparam ) )
	{
		return FALSE;
	}

	if ( pthread_create( handle, &attr, func, arg ) )
	{
		return FALSE;
	}

#endif

	return TRUE;
};

void thr_thread_join( thr_THREAD handle )
{
#if defined WIN32
	WaitForSingleObject( handle, INFINITE );
	CloseHandle( handle );

#elif defined LINUX
	pthread_join( handle, NULL );

#elif defined VXWORKS
	pthread_join( handle, NULL );
#endif
}

void thr_thread_exit()
{
#if defined WIN32
	_endthreadex( 0 );

#elif defined LINUX
	pthread_exit( NULL );

#elif defined VXWORKS
	pthread_exit( NULL );

#endif
}

int thr_thread_set_priority( thr_THREAD handle, int priority )
{
#if defined WIN32
	return -1;

#elif defined LINUX
	return -1;

#elif defined VXWORKS
	int policy = 0;
	struct sched_param schedparam;

	memset( &schedparam, 0, sizeof( schedparam ) );
	if ( pthread_getschedparam( handle, &policy, &schedparam ) )
	{
		return thr_THREAD_RET_SETPRI;
	}

	memset( &schedparam, 0, sizeof( schedparam ) );
	schedparam.sched_priority = priority;
	if ( pthread_setschedparam( handle, policy, &schedparam ) )
	{
		return thr_THREAD_RET_SETPRI;
	}

#endif

	return 0;
}

int thr_thread_reschedule()
{
#if defined WIN32

#elif defined LINUX

#elif defined VXWORKS
	if ( ERROR == taskDelay( 0 ) )
	{
		ERROR_PRINT( "taskDelay return error!" );
	}

#endif

	return 0;
}

int thr_mutex_init( thr_MUTEX* handle )
{
#if defined WIN32
	*handle = CreateMutex( 0, FALSE, 0 );
	if ( NULL == *handle )
	{
		return thr_MUTEX_RET_CREATEFAILED;
	}

#elif defined LINUX
	if ( pthread_mutex_init( handle, NULL ) )
	{
		return thr_MUTEX_RET_CREATEFAILED;
	}

#elif defined VXWORKS
	if ( handle == NULL )
	{
		return thr_MUTEX_RET_CREATEFAILED;
	}
	memset( handle, 0, sizeof( thr_MUTEX ) );

	if ( pthread_mutex_init( handle, NULL ) )
	{
		return thr_MUTEX_RET_CREATEFAILED;
	}

#endif

	return 0;
}

int thr_mutex_destroy( thr_MUTEX* handle )
{
#if defined WIN32
	if ( WaitForSingleObject( *handle, ( DWORD )0 ) == WAIT_TIMEOUT )
		return thr_MUTEX_RET_NOTOWNER;

	CloseHandle( *handle );
	*handle = 0;

#elif defined LINUX
	if ( pthread_mutex_destroy( handle ) == EBUSY )
		return thr_MUTEX_RET_NOTOWNER;

#elif defined VXWORKS
	if ( pthread_mutex_destroy( handle ) == EBUSY )
		return thr_MUTEX_RET_NOTOWNER;

#endif

	return 0;
}

int thr_mutex_lock( thr_MUTEX* handle )
{
#if defined WIN32
	if ( WaitForSingleObject( *handle, INFINITE ) == WAIT_FAILED )
	{
		return thr_MUTEX_RET_LOCKERROR;
	}

#elif defined LINUX
	if ( pthread_mutex_lock( handle ) )
	{
		return thr_MUTEX_RET_LOCKERROR;
	}

#elif defined VXWORKS
	if ( pthread_mutex_lock( handle ) )
	{
		return thr_MUTEX_RET_LOCKERROR;
	}

#endif

	return 0;
}

int thr_mutex_unlock( thr_MUTEX* handle )
{
#if defined WIN32
	if ( !ReleaseMutex( *handle ) )
	{
		return thr_MUTEX_RET_UNLOCKERROR;
	}

#elif defined LINUX
	if ( pthread_mutex_unlock( handle ) )
	{
		return thr_MUTEX_RET_UNLOCKERROR;
	}

#elif defined VXWORKS
	if ( pthread_mutex_unlock( handle ) )
	{
		return thr_MUTEX_RET_UNLOCKERROR;
	}

#endif

	return 0;
}

int thr_sem_init( thr_SEM* handle )
{
#if defined WIN32
	*handle = CreateSemaphore( NULL, 0, 65536, NULL );
	if ( NULL == *handle )
	{
		return thr_SEM_RET_CREATEFAILED;
	}

#elif defined LINUX
	if ( pthread_mutex_init( &( handle->mutex ), NULL ) )
	{
		return thr_SEM_RET_CREATEFAILED;
	}

	if ( pthread_cond_init( &( handle->cond ), NULL ) )
	{
		pthread_mutex_destroy( &( handle->mutex ) );
		return thr_SEM_RET_CREATEFAILED;
	}

	handle->count = 0;

#elif defined VXWORKS
	if ( handle == NULL )
	{
		return thr_SEM_RET_CREATEFAILED;
	}
	memset( handle, 0, sizeof( thr_SEM ) );

	if ( pthread_mutex_init( &( handle->mutex ), NULL ) )
	{
		return thr_SEM_RET_CREATEFAILED;
	}

	if ( pthread_cond_init( &( handle->cond ), NULL ) )
	{
		pthread_mutex_destroy( &( handle->mutex ) );
		return thr_SEM_RET_CREATEFAILED;
	}

	handle->count = 0;

#endif

	return 0;
}

void thr_sem_destroy( thr_SEM* handle )
{
#if defined WIN32
	CloseHandle( *handle );
	*handle = 0;

#elif defined LINUX
	pthread_mutex_destroy( &( handle->mutex ) );

	pthread_cond_destroy( &( handle->cond ) );

#elif defined VXWORKS
	pthread_mutex_destroy( &( handle->mutex ) );

	pthread_cond_destroy( &( handle->cond ) );

#endif
}


int thr_sem_post( thr_SEM* handle )
{
#if defined WIN32
	ReleaseSemaphore( *handle, 1, NULL );

#elif defined LINUX
	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_POSTERROR;

	handle->count++;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_POSTERROR;

	if ( pthread_cond_signal( &( handle->cond ) ) )
		return thr_SEM_RET_POSTERROR; 

#elif defined VXWORKS
	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_POSTERROR;

	handle->count++;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_POSTERROR;

	if ( pthread_cond_signal( &( handle->cond ) ) )
		return thr_SEM_RET_POSTERROR; 

#endif

	return 0;
}


int thr_sem_wait( thr_SEM* handle )
{
#if defined WIN32
	if ( WAIT_FAILED == WaitForSingleObject( *handle, INFINITE ) ) 
	{
		return thr_SEM_RET_WAITERROR;
	}

#elif defined LINUX
	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR;

	while ( handle->count <= 0 )
	{
		if ( pthread_cond_wait( &( handle->cond ), &( handle->mutex ) ) 
				&& ( errno != EINTR ) )
		{
			break;
		}
	}
	handle->count--;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR; 

#elif defined VXWORKS
	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR;

	while ( handle->count <= 0 )
	{
		if ( pthread_cond_wait( &( handle->cond ), &( handle->mutex ) ) 
				&& ( errno != EINTR ) )
		{
			break;
		}
	}
	handle->count--;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR; 

#endif

	return 0;
}

int thr_sem_timewait( thr_SEM* handle, UINT32 milliseconds )
{
#if defined WIN32
	DWORD dwRet;

	dwRet = WaitForSingleObject( *handle, milliseconds );
	if ( WAIT_FAILED == dwRet ) 
	{
		return thr_SEM_RET_WAITERROR;
	}

	if ( WAIT_TIMEOUT == dwRet )
	{
		return thr_SEM_RET_TIMEOUT;
	}

#elif defined LINUX
	int ret;
	struct timespec ts;
	UINT32 sec, millisec;

	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR;

	sec = milliseconds / 1000;
	millisec = milliseconds % 1000;
	clock_gettime( CLOCK_REALTIME, &ts );
	ts.tv_sec += sec;
	ts.tv_nsec += millisec * 1000000;

	while ( handle->count <= 0 )
	{
		ret = pthread_cond_timedwait( &( handle->cond ), &( handle->mutex ), &ts ); 
		if ( ret && ( errno != EINTR ) )
		{
			break;
		}
	}

	if ( ret )
	{
		if ( pthread_mutex_unlock( &( handle->mutex ) ) )
			return thr_SEM_RET_WAITERROR;

		if ( ret == ETIMEDOUT )
			return thr_SEM_RET_TIMEOUT;

		return thr_SEM_RET_WAITERROR;

	}

	handle->count--;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR; 

#elif defined VXWORKS
	int ret;
	struct timespec ts;
	UINT32 sec, millisec;

	if ( pthread_mutex_lock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR;

	sec = milliseconds / 1000;
	millisec = milliseconds % 1000;
	clock_gettime( CLOCK_REALTIME, &ts );
	ts.tv_sec += sec;
	ts.tv_nsec += millisec * 1000000;

	while ( handle->count <= 0 )
	{
		ret = pthread_cond_timedwait( &( handle->cond ), &( handle->mutex ), &ts ); 
		if ( ret && ( errno != EINTR ) )
		{
			break;
		}
	}

	if ( ret )
	{
		if ( pthread_mutex_unlock( &( handle->mutex ) ) )
			return thr_SEM_RET_WAITERROR;

		if ( ret == ETIMEDOUT )
			return thr_SEM_RET_TIMEOUT;

		return thr_SEM_RET_WAITERROR;

	}

	handle->count--;

	if ( pthread_mutex_unlock( &( handle->mutex ) ) )
		return thr_SEM_RET_WAITERROR; 

#endif

	return 0;
}



/******************************************************
 * FuncName    : thrdproc
 * Description : provide a framework to do the client side real actions
 *               it's blocked when no client arive.
 * Input       : void *arg, actually it's a pointer to struct thrdpool_t
 * Output      : no
 * Return      : void
 *****************************************************/
thr_THREAD_RET thr_THREAD_CALL thrdproc( void *arg ) 
{
	thrdpool_t *pthrdpool = ( thrdpool_t *)arg;
	clt_t *clts = pthrdpool->clttab.pclts;
	UINT32 idx=0;
	INT32 cltidx = -1;
	UINT32 hpri = 99999;
#if defined LINUX
	pthread_detach( pthread_self() );
	pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, NULL );
#endif
	for(;;) 
	{
		thr_sem_wait( &(pthrdpool->thread_sem) );

		idx=0;
		cltidx = -1;
		hpri = 99999;
		for( idx = 0; idx < pthrdpool->clttab.count; idx++ ) {
			if( clts[idx].state == WAITING ) {
				if( hpri >clts[idx].pri ) {
					hpri = clts[idx].pri;
					cltidx = idx;
				}
			}
		}
		thr_mutex_lock( &pthrdpool->thrdmutex );
		clts[cltidx].state = PROCESSING;
		pthrdpool->clttab.waitcount--;
		pthrdpool->clttab.proscount++;
		//runLog(pthrdpool->logfile,"clientidx=%d, cltid=%d, state=%d, pri=%ld, waitcount=%d \n", cltidx, clts[cltidx].cltid, clts[cltidx].state, clts[cltidx].pri, pthrdpool->clttab.waitcount);
		thr_mutex_unlock( &pthrdpool->thrdmutex );


		/* processing area */
		printf("do 1\n");
		( *clts[cltidx].thrdcall.thrdfunc)( clts[cltidx].thrdcall.arg );

		printf("do 2\n");
		if( clts[cltidx].thrdexit.thrdfunc != NULL )
			( *clts[cltidx].thrdexit.thrdfunc)( clts[cltidx].thrdexit.arg );
		//thr_sem_post( &(pthrdpool->thread_sem) );

		/* free this client resource */
		printf("do free\n");
		thr_mutex_lock( &pthrdpool->thrdmutex );
		clts[cltidx].state = IDLE;
		pthrdpool->clttab.proscount--;
		clts[cltidx].thrdcall.thrdfunc = NULL;
		clts[cltidx].thrdcall.arg = NULL;
		clts[cltidx].thrdexit.thrdfunc = NULL;
		clts[cltidx].thrdcall.arg = NULL;
		//runLog( pthrdpool->logfile, " the resource released,cltidx=%d, cltid=%d , pri=%ld, curthread is %ld \n", cltidx, clts[cltidx].cltid, clts[cltidx].pri, pthread_self() );
		thr_mutex_unlock( &pthrdpool->thrdmutex );
	}

	return NULL;
}

/******************************************************
 * FuncName    : createThrdPool
 * Description : To create a thread pool
 * Input       :
 *   @maxthrds : max thread count permit to create
 *   @maxclts  : max clients count permit to serve
 *   @plogfile : log file name
 * Output      : no
 * Return      : the pointer of thrdpool_t instance created here.
 *****************************************************/

thrdpool_t *thr_createThrdPool( int maxthrds, int maxclts, char *plogfile ) {
	int idx;
	thrdpool_t *pthrdpool;
	clt_t *clts;
	/* 
	 * create a thread pool and initialize it 
	 * according to the parameters specified by the caller
	 */
	if(( maxthrds <= 0 ) || ( maxclts <= 0 )) {
		runLog( plogfile, "smaller than zero is illegal for the paramter maxthrds or maxclts of function createThrdPool.\n" );
		printf(plogfile);
		return NULL;
	}
	pthrdpool = calloc( sizeof( thrdpool_t ), 1);
	pthrdpool->thrdtab.pthrds = calloc( sizeof( thr_THREAD ), maxthrds );
	pthrdpool->thrdtab.count = maxthrds;
	pthrdpool->clttab.pclts = calloc( sizeof( clt_t ), maxclts );
	clts = pthrdpool->clttab.pclts;
	pthrdpool->clttab.count = maxclts;
	if( plogfile == NULL )
		pthrdpool->logfile[0] = '\0';
	else
		strcpy( pthrdpool->logfile, plogfile );
	pthrdpool->clttab.waitcount = 0;
	pthrdpool->clttab.proscount = 0;
	pthrdpool->clttab.prino = 0;
	for( idx = 0; idx < maxclts; idx++ ) {
		clts[idx].state = IDLE;
		clts[idx].pri = 0;
		clts[idx].cltid = -1;
		clts[idx].thrdcall.thrdfunc = NULL;
		clts[idx].thrdcall.arg = NULL;
		clts[idx].thrdexit.thrdfunc = NULL;
		clts[idx].thrdcall.arg = NULL;
	}

	thr_mutex_init(&( pthrdpool->thrdmutex));


	thr_sem_init(&( pthrdpool->thread_sem));

	for( idx = 0; idx < maxthrds; idx++ ) 
	{
		thr_thread_create( &(pthrdpool->thrdtab.pthrds[idx]), thrdproc, (void *)pthrdpool );
	}

	return pthrdpool;
}

/******************************************************
 * FuncName    : destroyThrdPool
 * Description : free the resources the thread pool used
 * Input       : thrdpool_t *pthrdpool
 * Output      : no
 * Return      : void
 *****************************************************/

void thr_destroyThrdPool( thrdpool_t *pthrdpool ) {
	UINT32 idx;
	for( idx = 0; idx < pthrdpool->thrdtab.count; idx++) {
#ifdef	LINUX
		pthread_cancel( pthrdpool->thrdtab.pthrds[idx] );
#elif  defined WIN32
		TerminateThread( pthrdpool->thrdtab.pthrds[idx],1 );

#endif
	}

	/* maybe return error EPERM here, but it doesn't matter. */
	thr_mutex_unlock( &pthrdpool->thrdmutex );        
	free( pthrdpool->thrdtab.pthrds );
	free( pthrdpool->clttab.pclts );
	free( pthrdpool );
	pthrdpool = NULL;

}
#if 0
/******************************************************
 * FuncName    : thr_deletetask
 * Description : deletetask 
 * Input       : thr_rwlock_t * lock_ins
 * Output      : no
 * Return      : void
 *****************************************************/

int thr_deletetask(unsigned int cltid, thrdpool_t * pthrdpool)
{
	//thrdpool_t *pthrdpool = ( thrdpool_t *)arg;
	clt_t *clts = pthrdpool->clttab.pclts;
	UINT32 idx=0;
	INT32 cltidx = -1;
	thr_mutex_lock( &pthrdpool->thrdmutex );
	for( idx = 0; idx < pthrdpool->clttab.count; idx++ ) 
	{
		if(( clts[idx].state == WAITING) &&(clts[idx].cltid == cltid)) 
		{
			clts[idx].state = IDLE;
			pthrdpool->clttab.proscount--;
			clts[idx].thrdcall.thrdfunc = NULL;
			clts[idx].thrdcall.arg = NULL;
			clts[idx].thrdexit.thrdfunc = NULL;
			clts[idx].thrdcall.arg = NULL;
		}
	}
	thr_mutex_unlock( &pthrdpool->thrdmutex );

}
#endif
/******************************************************
 * FuncName    : addClt
 * Description : add a new client to the pool specified by the param pthrdpool
 * Input       :
 *   @pthrdpool: the thread pool to add the client to
 *   @cltid    : the identifier used by user to identify the client, 
 *               for example,it can be the connection descriptor returned by accept(..) call.
 *   @thrdcall : a struct include the real client function and it's arguments to perform by the thread
 *   @thrdexit : a struct include the real client function and it's arguments to perform when thrdcall finished.
 * Output      : no
 * Return      : 
 *   ETOOMANYCLTS : no place for the new client
 *   THRDPOOL_OK  : the client is successfully added into the thread pool
 *****************************************************/

int thr_addClt( thrdpool_t *pthrdpool, unsigned int cltid, thrdcall_t thrdcall, thrdcall_t thrdexit ) {
	ENTER_FUNC();
	UINT32 idx=0;
	INT32 idleidx = -1;
	clt_t *clts=NULL;
	thr_mutex_lock( &(pthrdpool->thrdmutex) );
	/* get first idle client item        */
	for( idx = 0; idx < pthrdpool->clttab.count; idx++ ) {
		if( pthrdpool->clttab.pclts[idx].state == IDLE ) {
			idleidx = idx;
			break;
		}
	}
	if( idleidx == -1 ) {        
		//runLog( pthrdpool->logfile, "too many clients for new client [%d].\n", cltid );
		//printf(pthrdpool->logfile);
		thr_mutex_unlock( &pthrdpool->thrdmutex );
		return ETOOMANYCLTS;
	}
	clts = pthrdpool->clttab.pclts;
	clts[idleidx].cltid = cltid;
	clts[idleidx].state = WAITING;
	clts[idleidx].thrdcall.thrdfunc = thrdcall.thrdfunc;
	clts[idleidx].thrdcall.arg = thrdcall.arg;
	clts[idleidx].thrdexit.thrdfunc = thrdexit.thrdfunc;
	clts[idleidx].thrdexit.arg = thrdexit.arg;
	pthrdpool->clttab.waitcount++;
	/* calculate the priority of the coming client */
	pthrdpool->clttab.prino++;
	clts[idleidx].pri = pthrdpool->clttab.prino;

	thr_sem_post( &(pthrdpool->thread_sem) );
	thr_mutex_unlock( &pthrdpool->thrdmutex );
	EXIT_FUNC();
	return THRDPOOL_OK;
}

