#pragma once

#ifndef _TIME_H_
#define _TIME_H_

#include <chrono>
#include <queue>

class Time
{
	struct ScheduledTask {
		std::chrono::system_clock::time_point executeTime;
		std::function<void()> taskFunction;

		// This will make the priority queue a min-heap based on the executeTime
		bool operator<(const ScheduledTask& other) const {
			return executeTime > other.executeTime;
		}
	};
public:
	static Time& Instance()
	{
		if (instance == nullptr)
		{
			instance = new Time();
			instance->Initialize();
		}
		return *instance;
	}

	void Destroy()
	{
		if (instance == nullptr)
		{
			delete instance;
		}
	}

	void Update();

	float DeltaTime() { return deltaTime.count(); }
	float TotalTime() { return totalTime.count(); }
	unsigned int FrameCount() { return frameCount; }

	void ScheduleTask(float delayInSeconds, std::function<void()> task);

private:
	void Initialize();

private:
	unsigned int frameCount = 0;
	std::chrono::duration<float> deltaTime = std::chrono::duration<float>(0.0f);
	std::chrono::duration<float> totalTime = std::chrono::duration<float>(0.0f);
	std::chrono::time_point<std::chrono::system_clock> beginTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;
	std::priority_queue<ScheduledTask> taskQueue;
	static Time* instance;

private:
	inline explicit Time() = default;
	inline ~Time() = default;
	inline explicit Time(Time const&) = delete;
	inline Time& operator=(Time const&) = delete;
};

#endif