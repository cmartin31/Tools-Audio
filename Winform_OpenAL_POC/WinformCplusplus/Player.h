
#pragma once

	int Play(const char * fileName);
	int init();

	float GetDuration();             
	float GetPosition();             
	void  SetPosition(float seconds);

	void Pause();
	void Resume();
	void SetVolume(float volume);
	bool IsPlaying();
	void Stop();
	bool IsFinished();
	bool IsLooping();
	void SetLooping(bool _setLoop);