#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>

WorkQueue::WorkQueue()
	: m_condition(SDL_CreateCond())
	, m_lockQueue(SDL_CreateMutex())
{
}

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

std::function<void()> WorkQueue::nextTask()
{
	std::function<void()> nextJob = 0;
	SDL_LockMutex(m_lockQueue);
	if (finished && m_tasks.size() == 0)
	{
		nextJob = 0;
	}
	else
	{
		while (m_tasks.size() == 0)
		{
			SDL_CondWait(m_condition, m_lockQueue);
		}
		nextJob = m_tasks.front();
		m_tasks.pop();
	}
	SDL_UnlockMutex(m_lockQueue);
	return nextJob;
}

void WorkQueue::finish()
{
	SDL_LockMutex(m_lockQueue);
	finished = true;
	SDL_CondSignal(m_condition);
	SDL_UnlockMutex(m_lockQueue);

	SDL_DestroyMutex(m_lockQueue);
	SDL_DestroyCond(m_condition);
}

bool WorkQueue::hasWork()
{
	return m_tasks.size() > 0;
}


int getWork(void * param)
{
	std::function<void()> moreWork;
	WorkQueue * workQueue = (WorkQueue*)param;
	while (moreWork = workQueue->nextTask())
	{
		moreWork();
	}

	std::cout << "1" << std::endl;
	
	return 0;
}

ThreadPool::ThreadPool()
{
	int numOfCores = std::thread::hardware_concurrency() - 1;
	for (int i = 0; i < numOfCores; i++)
	{ 
		// SDL_CreateThread(Function Called, Name of Thread, Pointer to the Data)
		m_threads.push_back(SDL_CreateThread(getWork, "RainbowJeremy", &workQueue));
	}
}

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
