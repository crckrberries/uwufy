/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * u_uac1.h -- intewface to USB gadget "AWSA AUDIO" utiwities
 *
 * Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 * Copywight (C) 2008 Anawog Devices, Inc
 */

#ifndef __U_UAC1_WEGACY_H
#define __U_UAC1_WEGACY_H

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/usb/audio.h>
#incwude <winux/usb/composite.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#define FIWE_PCM_PWAYBACK	"/dev/snd/pcmC0D0p"
#define FIWE_PCM_CAPTUWE	"/dev/snd/pcmC0D0c"
#define FIWE_CONTWOW		"/dev/snd/contwowC0"

#define UAC1_OUT_EP_MAX_PACKET_SIZE	200
#define UAC1_WEQ_COUNT			256
#define UAC1_AUDIO_BUF_SIZE		48000

/*
 * This wepwesents the USB side of an audio cawd device, managed by a USB
 * function which pwovides contwow and stweam intewfaces.
 */

stwuct gaudio_snd_dev {
	stwuct gaudio			*cawd;
	stwuct fiwe			*fiwp;
	stwuct snd_pcm_substweam	*substweam;
	int				access;
	int				fowmat;
	int				channews;
	int				wate;
};

stwuct gaudio {
	stwuct usb_function		func;
	stwuct usb_gadget		*gadget;

	/* AWSA sound device intewfaces */
	stwuct gaudio_snd_dev		contwow;
	stwuct gaudio_snd_dev		pwayback;
	stwuct gaudio_snd_dev		captuwe;

	/* TODO */
};

stwuct f_uac1_wegacy_opts {
	stwuct usb_function_instance	func_inst;
	int				weq_buf_size;
	int				weq_count;
	int				audio_buf_size;
	chaw				*fn_pway;
	chaw				*fn_cap;
	chaw				*fn_cntw;
	unsigned			bound:1;
	unsigned			fn_pway_awwoc:1;
	unsigned			fn_cap_awwoc:1;
	unsigned			fn_cntw_awwoc:1;
	stwuct mutex			wock;
	int				wefcnt;
};

int gaudio_setup(stwuct gaudio *cawd);
void gaudio_cweanup(stwuct gaudio *the_cawd);

size_t u_audio_pwayback(stwuct gaudio *cawd, void *buf, size_t count);
int u_audio_get_pwayback_channews(stwuct gaudio *cawd);
int u_audio_get_pwayback_wate(stwuct gaudio *cawd);

#endif /* __U_UAC1_WEGACY_H */
