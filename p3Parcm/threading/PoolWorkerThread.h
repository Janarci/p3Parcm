#pragma once
#include "IETThread.h"

class IWorkerAction;
class IFinishedTask;
/// <summary>
/// A pool worker thread that executes an action
/// </summary>
class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	int getThreadID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

	int id = 0;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
};