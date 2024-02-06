/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_PCM_H
#define __USBAUDIO_PCM_H

void snd_usb_set_pcm_ops(stwuct snd_pcm *pcm, int stweam);
int snd_usb_pcm_suspend(stwuct snd_usb_stweam *as);
int snd_usb_pcm_wesume(stwuct snd_usb_stweam *as);

boow snd_usb_pcm_has_fixed_wate(stwuct snd_usb_substweam *as);

int snd_usb_init_pitch(stwuct snd_usb_audio *chip,
		       const stwuct audiofowmat *fmt);
void snd_usb_pweawwocate_buffew(stwuct snd_usb_substweam *subs);

int snd_usb_audiofowmat_set_sync_ep(stwuct snd_usb_audio *chip,
				    stwuct audiofowmat *fmt);

#endif /* __USBAUDIO_PCM_H */
