#pragma once


class Stats
{
private:
	int Score;
	int Lives;

public:
	inline Stats() {
		Score = 0;
		Lives = 3;
	}

	inline void Reset() {
		Score = 0;
		Lives = 3;
	}

	//Setters
	void AddScore(int value) { Score += value; }
	void AddLives(int value) { Lives += value; }

	//Getters
	int GetScore() { return Score; }
	int GetLives() { return Lives; }
};