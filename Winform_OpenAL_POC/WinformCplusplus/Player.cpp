#include "Player.h"
#include"Framework.h"

static ALuint g_source = 0;
static ALuint g_buffer = 0;
static float  g_duration = 0.0f;

int init() {
	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
		return 0;
	}
}

float GetDuration()
{
	return g_duration;
}

float GetPosition()
{
	ALfloat pos = 0.0f;
	alGetSourcef(g_source, AL_SEC_OFFSET, &pos);
	return pos;
}

void SetPosition(float seconds)
{
	alSourcef(g_source, AL_SEC_OFFSET, seconds);
}

int Play(const char * fileName)
{
	ALuint      uiBuffer;
	ALuint      uiSource;
	ALint       iState;
	
	// Generate an AL Buffer
	alGenBuffers(1, &g_buffer);

	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)fileName, g_buffer))
	{
		ALFWprintf("Failed to load %s\n", fileName);
	}

	ALint freq, channels, bits, size;
	alGetBufferi(g_buffer, AL_FREQUENCY, &freq);
	alGetBufferi(g_buffer, AL_CHANNELS, &channels);
	alGetBufferi(g_buffer, AL_BITS, &bits);
	alGetBufferi(g_buffer, AL_SIZE, &size);
	g_duration = (float)size / (channels * (bits / 8)) / freq;

	// Generate a Source to playback the Buffer
	alGenSources(1, &g_source);

	// Attach Source to Buffer
	alSourcei(g_source, AL_BUFFER, g_buffer);
	//pour boucler un son
	alSourcei(g_source, AL_LOOPING, 1);
	// Play Source
	alSourcePlay(g_source);

	/*
	do
	{
		Sleep(100);
		ALFWprintf(".");
		// Get Source State
		alGetSourcei(uiSource, AL_SOURCE_STATE, &iState);
	} while (iState == AL_PLAYING);
	*/

	// Clean up by deleting Source(s) and Buffer(s)
	/*
	alSourceStop(uiSource);
	alDeleteSources(1, &uiSource);
	alDeleteBuffers(1, &uiBuffer);

	ALFWShutdownOpenAL();

	ALFWShutdown();
	*/
	return 0;
}
