#pragma once
#include <thread>
#include <queue>
#include <SDL_mutex.h>
#include <SDL_thread.h>
#include <vector>
#include <functional>


static int getWork(void* param);

class WorkQueue {
public:
	WorkQueue();
	void addTask(std::function<void()> newTask);
	std::function<void()> nextTask();
	void finish();
	bool hasWork();
private:
	SDL_mutex* m_lockQueue;
	SDL_cond* m_condition;
	std::queue<std::function<void()>> m_tasks;
	bool finished;
};
class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void addTask(std::function<void()> newTask);
	void waitForCompletion();
private:
	std::vector<SDL_Thread*> m_threads;
	WorkQueue workQueue;
};