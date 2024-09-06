#pragma once

class Constant
{
public:
	Constant();
	~Constant() = default;

public:

	/* how many milisecond does this take each one of those need to take? well 16.6666 to execute should take 16.6 ms */
	const int FPS = 60;
	const int MILLISECOND_PER_FRAME = 1000 / FPS;

};
