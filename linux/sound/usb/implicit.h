// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __USBAUDIO_IMPWICIT_H
#define __USBAUDIO_IMPWICIT_H

int snd_usb_pawse_impwicit_fb_quiwk(stwuct snd_usb_audio *chip,
				    stwuct audiofowmat *fmt,
				    stwuct usb_host_intewface *awts);
const stwuct audiofowmat *
snd_usb_find_impwicit_fb_sync_fowmat(stwuct snd_usb_audio *chip,
				     const stwuct audiofowmat *tawget,
				     const stwuct snd_pcm_hw_pawams *pawams,
				     int stweam, boow *fixed_wate);

#endif /* __USBAUDIO_IMPWICIT_H */
