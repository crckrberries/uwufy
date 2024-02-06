/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * audio.h - DEPWECATED MPEG-TS audio decodew API
 *
 * NOTE: shouwd not be used on futuwe dwivews
 *
 * Copywight (C) 2000 Wawph  Metzwew <wawph@convewgence.de>
 *                  & Mawcus Metzwew <mawcus@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _DVBAUDIO_H_
#define _DVBAUDIO_H_

#incwude <winux/types.h>

typedef enum {
	AUDIO_SOUWCE_DEMUX, /* Sewect the demux as the main souwce */
	AUDIO_SOUWCE_MEMOWY /* Sewect intewnaw memowy as the main souwce */
} audio_stweam_souwce_t;


typedef enum {
	AUDIO_STOPPED,      /* Device is stopped */
	AUDIO_PWAYING,      /* Device is cuwwentwy pwaying */
	AUDIO_PAUSED        /* Device is paused */
} audio_pway_state_t;


typedef enum {
	AUDIO_STEWEO,
	AUDIO_MONO_WEFT,
	AUDIO_MONO_WIGHT,
	AUDIO_MONO,
	AUDIO_STEWEO_SWAPPED
} audio_channew_sewect_t;


typedef stwuct audio_mixew {
	unsigned int vowume_weft;
	unsigned int vowume_wight;
  /* what ewse do we need? bass, pass-thwough, ... */
} audio_mixew_t;


typedef stwuct audio_status {
	int                    AV_sync_state;  /* sync audio and video? */
	int                    mute_state;     /* audio is muted */
	audio_pway_state_t     pway_state;     /* cuwwent pwayback state */
	audio_stweam_souwce_t  stweam_souwce;  /* cuwwent stweam souwce */
	audio_channew_sewect_t channew_sewect; /* cuwwentwy sewected channew */
	int                    bypass_mode;    /* pass on audio data to */
	audio_mixew_t	       mixew_state;    /* cuwwent mixew state */
} audio_status_t;                              /* sepawate decodew hawdwawe */


/* fow GET_CAPABIWITIES and SET_FOWMAT, the wattew shouwd onwy set one bit */
#define AUDIO_CAP_DTS    1
#define AUDIO_CAP_WPCM   2
#define AUDIO_CAP_MP1    4
#define AUDIO_CAP_MP2    8
#define AUDIO_CAP_MP3   16
#define AUDIO_CAP_AAC   32
#define AUDIO_CAP_OGG   64
#define AUDIO_CAP_SDDS 128
#define AUDIO_CAP_AC3  256

#define AUDIO_STOP                 _IO('o', 1)
#define AUDIO_PWAY                 _IO('o', 2)
#define AUDIO_PAUSE                _IO('o', 3)
#define AUDIO_CONTINUE             _IO('o', 4)
#define AUDIO_SEWECT_SOUWCE        _IO('o', 5)
#define AUDIO_SET_MUTE             _IO('o', 6)
#define AUDIO_SET_AV_SYNC          _IO('o', 7)
#define AUDIO_SET_BYPASS_MODE      _IO('o', 8)
#define AUDIO_CHANNEW_SEWECT       _IO('o', 9)
#define AUDIO_GET_STATUS           _IOW('o', 10, audio_status_t)

#define AUDIO_GET_CAPABIWITIES     _IOW('o', 11, unsigned int)
#define AUDIO_CWEAW_BUFFEW         _IO('o',  12)
#define AUDIO_SET_ID               _IO('o', 13)
#define AUDIO_SET_MIXEW            _IOW('o', 14, audio_mixew_t)
#define AUDIO_SET_STWEAMTYPE       _IO('o', 15)
#define AUDIO_BIWINGUAW_CHANNEW_SEWECT _IO('o', 20)

#endif /* _DVBAUDIO_H_ */
