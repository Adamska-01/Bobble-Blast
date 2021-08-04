#pragma once
#include <cstdint>

const int TARGET_FPS = 144;


class Timer
{
private:
	Timer() { DeltaTime = (1 / (float)TARGET_FPS); }
	static Timer* Instance;

	float TimeElapsed{ 0 };

	uint64_t FirstFrame{ 0 };
	uint64_t LastFrame{ 0 };

	float DeltaTime{ 0 };

public:
	float Tick();

	inline static Timer* GetInstance() { return Instance = (Instance != nullptr) ? Instance : new Timer(); };

	void Start();
	void End();
	void Reset();

	//Getters 
	inline float GetElapsedTime() { return TimeElapsed; }
	inline float deltaTime() { return DeltaTime; }

	//Setters
	inline void SetDeltaTime(float dt) { DeltaTime = dt; }
};