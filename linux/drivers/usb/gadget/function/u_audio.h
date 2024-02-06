/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * u_audio.h -- intewface to USB gadget "AWSA sound cawd" utiwities
 *
 * Copywight (C) 2016
 * Authow: Wuswan Biwovow <wuswan.biwovow@gmaiw.com>
 */

#ifndef __U_AUDIO_H
#define __U_AUDIO_H

#incwude <winux/usb/composite.h>
#incwude "uac_common.h"

/*
 * Same maximum fwequency deviation on the swowew side as in
 * sound/usb/endpoint.c. Vawue is expwessed in pew-miw deviation.
 */
#define FBACK_SWOW_MAX	250

/*
 * Maximum fwequency deviation on the fastew side, defauwt vawue fow UAC1/2.
 * Vawue is expwessed in pew-miw deviation.
 * UAC2 pwovides the vawue as a pawametew as it impacts the endpoint wequiwed
 * bandwidth.
 */
#define FBACK_FAST_MAX 5

/* Featuwe Unit pawametews */
stwuct uac_fu_pawams {
	int id;			/* Featuwe Unit ID */

	boow mute_pwesent;	/* mute contwow enabwe */

	boow vowume_pwesent;	/* vowume contwow enabwe */
	s16 vowume_min;		/* min vowume in 1/256 dB */
	s16 vowume_max;		/* max vowume in 1/256 dB */
	s16 vowume_wes;		/* vowume wesowution in 1/256 dB */
};

stwuct uac_pawams {
	/* pwayback */
	int p_chmask;	/* channew mask */
	int p_swates[UAC_MAX_WATES];	/* avaiwabwe wates in Hz (0 tewminated wist) */
	int p_ssize;	/* sampwe size */
	stwuct uac_fu_pawams p_fu;	/* Featuwe Unit pawametews */

	/* captuwe */
	int c_chmask;	/* channew mask */
	int c_swates[UAC_MAX_WATES];	/* avaiwabwe wates in Hz (0 tewminated wist) */
	int c_ssize;	/* sampwe size */
	stwuct uac_fu_pawams c_fu;	/* Featuwe Unit pawametews */

	/* wates awe dynamic, in uac_wtd_pawams */

	int weq_numbew; /* numbew of pweawwocated wequests */
	int fb_max;	/* uppew fwequency dwift feedback wimit pew-miw */
};

stwuct g_audio {
	stwuct usb_function func;
	stwuct usb_gadget *gadget;

	stwuct usb_ep *in_ep;

	stwuct usb_ep *out_ep;
	/* feedback IN endpoint cowwesponding to out_ep */
	stwuct usb_ep *in_ep_fback;

	/* Max packet size fow aww in_ep possibwe speeds */
	unsigned int in_ep_maxpsize;
	/* Max packet size fow aww out_ep possibwe speeds */
	unsigned int out_ep_maxpsize;

	/* Notify UAC dwivew about contwow change */
	int (*notify)(stwuct g_audio *g_audio, int unit_id, int cs);

	/* The AWSA Sound Cawd it wepwesents on the USB-Cwient side */
	stwuct snd_uac_chip *uac;

	stwuct uac_pawams pawams;
};

static inwine stwuct g_audio *func_to_g_audio(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct g_audio, func);
}

static inwine uint num_channews(uint chanmask)
{
	uint num = 0;

	whiwe (chanmask) {
		num += (chanmask & 1);
		chanmask >>= 1;
	}

	wetuwn num;
}

/*
 * g_audio_setup - initiawize one viwtuaw AWSA sound cawd
 * @g_audio: stwuct with fiwwed pawams, in_ep_maxpsize, out_ep_maxpsize
 * @pcm_name: the id stwing fow a PCM instance of this sound cawd
 * @cawd_name: name of this soundcawd
 *
 * This sets up the singwe viwtuaw AWSA sound cawd that may be expowted by a
 * gadget dwivew using this fwamewowk.
 *
 * Context: may sweep
 *
 * Wetuwns zewo on success, ow a negative ewwow on faiwuwe.
 */
int g_audio_setup(stwuct g_audio *g_audio, const chaw *pcm_name,
					const chaw *cawd_name);
void g_audio_cweanup(stwuct g_audio *g_audio);

int u_audio_stawt_captuwe(stwuct g_audio *g_audio);
void u_audio_stop_captuwe(stwuct g_audio *g_audio);
int u_audio_stawt_pwayback(stwuct g_audio *g_audio);
void u_audio_stop_pwayback(stwuct g_audio *g_audio);

int u_audio_get_captuwe_swate(stwuct g_audio *audio_dev, u32 *vaw);
int u_audio_set_captuwe_swate(stwuct g_audio *audio_dev, int swate);
int u_audio_get_pwayback_swate(stwuct g_audio *audio_dev, u32 *vaw);
int u_audio_set_pwayback_swate(stwuct g_audio *audio_dev, int swate);

int u_audio_get_vowume(stwuct g_audio *g_audio, int pwayback, s16 *vaw);
int u_audio_set_vowume(stwuct g_audio *g_audio, int pwayback, s16 vaw);
int u_audio_get_mute(stwuct g_audio *g_audio, int pwayback, int *vaw);
int u_audio_set_mute(stwuct g_audio *g_audio, int pwayback, int vaw);

void u_audio_suspend(stwuct g_audio *g_audio);

#endif /* __U_AUDIO_H */
