#include "stdafx.h"
#include "ThreadPool.h"

WorkQueue::WorkQueue()
	: m_condition(SDL_CreateCond())
	, m_lockQueue(SDL_CreateMutex())
{
}


// ADDING TASKS TO THE QUEUE
///////////////////////////////////////////////////////
void WorkQueue::addTask(std::function<void()> newTask)
{
	if (!finished)
	{
		SDL_LockMutex(m_lockQueue);		// Lock Task Queue
		m_tasks.push(newTask);			// Push new task
		SDL_CondSignal(m_condition);	// Restarts Threads waiting on m_condition
		SDL_UnlockMutex(m_lockQueue);	// Lock Task Queue
	}
}
// ADDING TASKS TO THE QUEUE
///////////////////////////////////////////////////////
std::function<void()> WorkQueue::nextTask()
{
	std::function<void()> nextJob = 0;
	SDL_LockMutex(m_lockQueue);							// Lock Task Queue
	if (finished && m_tasks.size() == 0)
	{
		nextJob = 0;
	}
	else
	{
		while (m_tasks.size() == 0)
		{
			SDL_CondWait(m_condition, m_lockQueue);		// Wait while theres no jobs
		}	
		nextJob = m_tasks.front();						
		m_tasks.pop();									// Pop job of the front of the queue
	}
	SDL_UnlockMutex(m_lockQueue);						// Unlock Task Queue
	return nextJob;
}
// FINISH
///////////////////////////////////////////////////////
void WorkQueue::finish()
{
	SDL_LockMutex(m_lockQueue);			// Lock Task Queue 
	finished = true;
	SDL_CondSignal(m_condition);		// Lock Task Queue 
	SDL_UnlockMutex(m_lockQueue);		// Lock Task Queue 

	SDL_DestroyMutex(m_lockQueue);		// Cleanup mutex
	SDL_DestroyCond(m_condition);		// Cleanup condition
}

bool WorkQueue::hasWork()
{
	return m_tasks.size() > 0;
}

// THREADED FUNCTION THAT TAKES WORKQUEUE DATA AS A PARAMETER
///////////////////////////////////////////////////////
int getWork(void * param)
{
	std::function<void()> moreWork;
	WorkQueue * workQueue = (WorkQueue*)param;
	while (moreWork = workQueue->nextTask())
	{
		moreWork();
	}
	return 0;
}
// THREADEDPOOL 
///////////////////////////////////////////////////////
ThreadPool::ThreadPool()
{
	int numOfCores = std::thread::hardware_concurrency() - 1;		// Gets num of cores on the machine
	for (int i = 0; i < numOfCores; i++)
	{ 
		// SDL_CreateThread(Function Called, Name of Thread, Pointer to the Data)
		m_threads.push_back(SDL_CreateThread(getWork, "RainbowJeremy", &workQueue));
	}
}
// THREADEDPOOL DESTRUCTOR
///////////////////////////////////////////////////////
ThreadPool::~ThreadPool()
{
	workQueue.finish();
	waitForCompletion();
	for (int i = 0; i < m_threads.size(); i++)
	{
		SDL_WaitThread(m_threads[i], NULL);
	}
}

void ThreadPool::addTask(std::function<void()> newTask)
{
	workQueue.addTask(newTask);
}

void ThreadPool::waitForCompletion()
{
	while (workQueue.hasWork()) 
	{
	}
}
