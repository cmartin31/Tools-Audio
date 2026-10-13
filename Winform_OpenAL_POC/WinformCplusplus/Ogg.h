#pragma once
#include "Framework.h"
#include "vorbis\vorbisfile.h"


#define NUMBUFFERS              (4)
#define	SERVICE_UPDATE_PERIOD	(20)

#define	TEST_OGGVORBIS_FILE		"stereo.ogg"

// Ogg Vorbis

// Ogg Voribis DLL Handle
extern HINSTANCE g_hVorbisFileDLL;

// Functions
void InitVorbisFile();
void ShutdownVorbisFile();
unsigned long DecodeOggVorbis(OggVorbis_File* psOggVorbisFile, char* pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);
void Swap(short& s1, short& s2);

size_t ov_read_func(void* ptr, size_t size, size_t nmemb, void* datasource);
int ov_seek_func(void* datasource, ogg_int64_t offset, int whence);
int ov_close_func(void* datasource);
long ov_tell_func(void* datasource);

// Function pointers
typedef int (*LPOVCLEAR)(OggVorbis_File* vf);
typedef long (*LPOVREAD)(OggVorbis_File* vf, char* buffer, int length, int bigendianp, int word, int sgned, int* bitstream);
typedef ogg_int64_t(*LPOVPCMTOTAL)(OggVorbis_File* vf, int i);
typedef vorbis_info* (*LPOVINFO)(OggVorbis_File* vf, int link);
typedef vorbis_comment* (*LPOVCOMMENT)(OggVorbis_File* vf, int link);
typedef int (*LPOVOPENCALLBACKS)(void* datasource, OggVorbis_File* vf, char* initial, long ibytes, ov_callbacks callbacks);

// Variables
extern LPOVCLEAR			fn_ov_clear;
extern LPOVREAD				fn_ov_read;
extern LPOVPCMTOTAL			fn_ov_pcm_total;
extern LPOVINFO				fn_ov_info;
extern LPOVCOMMENT			fn_ov_comment;
extern LPOVOPENCALLBACKS	fn_ov_open_callbacks;

extern bool g_bVorbisInit;