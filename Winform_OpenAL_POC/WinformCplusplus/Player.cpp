#include "Player.h"
#include "Framework.h"
#include"Ogg.h"


static ALuint g_source = 0;
static ALuint g_buffer = 0;
static float  g_duration = 0.0f;
static float g_volume = 1.0f;

int init() {
	// Initialize Framework
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		ALFWShutdown();
		return 0;
	}

	// Initialize OggVorbis libary
	InitVorbisFile();
	if (!g_bVorbisInit)
	{
		ALFWprintf("Failed to find OggVorbis DLLs (vorbisfile.dll, ogg.dll, or vorbis.dll)\n");
		ALFWShutdown();

		return 0;
	}
}

static bool IsOggFile(const char* fileName)
{
	const char* ext = strrchr(fileName, '.');
	return ext && _stricmp(ext, ".ogg") == 0;
}

static bool LoadOggToBuffer(const char* fileName, ALuint uiBuffer)
{
	if (!g_bVorbisInit)
		return false;

	FILE* pFile = fopen(fileName, "rb");
	if (!pFile)
		return false;

	ov_callbacks sCallbacks;
	sCallbacks.read_func = ov_read_func;
	sCallbacks.seek_func = ov_seek_func;
	sCallbacks.close_func = ov_close_func;
	sCallbacks.tell_func = ov_tell_func;

	OggVorbis_File sOggVorbisFile;
	if (fn_ov_open_callbacks(pFile, &sOggVorbisFile, NULL, 0, sCallbacks) != 0)
	{
		fclose(pFile);
		return false;
	}

	vorbis_info* psVorbisInfo = fn_ov_info(&sOggVorbisFile, -1);
	if (!psVorbisInfo)
	{
		fn_ov_clear(&sOggVorbisFile);
		return false;
	}

	unsigned long ulChannels = psVorbisInfo->channels;
	unsigned long ulFrequency = psVorbisInfo->rate;

	ALenum eFormat = 0;
	switch (ulChannels)
	{
	case 1: eFormat = AL_FORMAT_MONO16;   break;
	case 2: eFormat = AL_FORMAT_STEREO16; break;
	case 4: eFormat = alGetEnumValue("AL_FORMAT_QUAD16");  break;
	case 6: eFormat = alGetEnumValue("AL_FORMAT_51CHN16"); break;
	}
	if (eFormat == 0)
	{
		fn_ov_clear(&sOggVorbisFile);
		return false;
	}

	ogg_int64_t llTotalSamples = fn_ov_pcm_total(&sOggVorbisFile, -1);
	unsigned long ulBufferSize = (unsigned long)(llTotalSamples * ulChannels * 2);

	char* pData = (char*)malloc(ulBufferSize);
	if (!pData)
	{
		fn_ov_clear(&sOggVorbisFile);
		return false;
	}

	unsigned long ulBytesDone = DecodeOggVorbis(&sOggVorbisFile, pData, ulBufferSize, ulChannels);

	if (ulBytesDone > 0)
		alBufferData(uiBuffer, eFormat, pData, ulBytesDone, ulFrequency);

	free(pData);
	fn_ov_clear(&sOggVorbisFile);

	return ulBytesDone > 0;
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

void Pause()
{
	alSourcePause(g_source);
}

void Resume()
{
	alSourcePlay(g_source);
}

void SetVolume(float volume)  
{
	g_volume = volume;
	if (g_source != 0)
		alSourcef(g_source, AL_GAIN, g_volume);
}

bool IsPlaying()
{
	ALint etat = 0;
	alGetSourcei(g_source, AL_SOURCE_STATE, &etat);
	return etat == AL_PLAYING;
}

void Stop()
{
	Pause();
	g_duration = 0.f;
	SetPosition(g_duration);
}

int Play(const char* fileName)
{
	ALuint      uiBuffer;
	ALuint      uiSource;
	ALint       iState;

	// Generate an AL Buffer
	alGenBuffers(1, &g_buffer);

	bool isOgg = IsOggFile(fileName);

	if (isOgg)
	{
		if (!LoadOggToBuffer((char*)fileName, g_buffer))
		{
			ALFWprintf("Failed to load %s\n", fileName);
		}
	}
	else
	{
		if (!ALFWLoadWaveToBuffer((char*)fileName, g_buffer))
		{
			ALFWprintf("Failed to load %s\n", fileName);
		}
	}

	// Load Wave file into OpenAL Buffer


	ALint freq, channels, bits, size;
	alGetBufferi(g_buffer, AL_FREQUENCY, &freq);
	alGetBufferi(g_buffer, AL_CHANNELS, &channels);
	alGetBufferi(g_buffer, AL_BITS, &bits);
	alGetBufferi(g_buffer, AL_SIZE, &size);
	g_duration = (float)size / (channels * (bits / 8)) / freq;

	// Generate a Source to playback the Buffer
	alGenSources(1, &g_source);
	alSourcef(g_source, AL_GAIN, g_volume);

	// Attach Source to Buffer
	alSourcei(g_source, AL_BUFFER, g_buffer);
	//pour boucler un son
	alSourcei(g_source, AL_LOOPING, 1);


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

