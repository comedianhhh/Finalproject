#include "EngineCore.h"
#include "EngineTime.h"

Time* Time::instance = nullptr;

void Time::Update()
{
	endTime = std::chrono::system_clock().now();
	deltaTime = endTime - beginTime;
	beginTime = endTime;
	totalTime += deltaTime;
	frameCount++;

	// Execute tasks that are scheduled to run
	while (!taskQueue.empty() && taskQueue.top().executeTime <= std::chrono::system_clock().now()) {
		taskQueue.top().taskFunction();
		taskQueue.pop();
	}
}

void Time::Initialize()
{
	beginTime = std::chrono::system_clock().now();
	endTime = std::chrono::system_clock().now();

	deltaTime = std::chrono::duration<float>(0);
	totalTime = std::chrono::duration<float>(0);
	frameCount = 0;
}
void Time::ScheduleTask(float delayInSeconds, std::function<void()> task) 
{
	ScheduledTask newTask;
	newTask.executeTime = std::chrono::system_clock().now() + std::chrono::milliseconds(static_cast<int>(delayInSeconds * 1000));
	newTask.taskFunction = task;
	taskQueue.push(newTask);
}