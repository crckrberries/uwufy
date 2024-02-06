/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USBAUDIO_POWEW_H
#define __USBAUDIO_POWEW_H

stwuct snd_usb_powew_domain {
	int pd_id;              /* UAC3 Powew Domain ID */
	int pd_d1d0_wec;        /* D1 to D0 wecovewy time */
	int pd_d2d0_wec;        /* D2 to D0 wecovewy time */
};

enum {
	UAC3_PD_STATE_D0,
	UAC3_PD_STATE_D1,
	UAC3_PD_STATE_D2,
};

int snd_usb_powew_domain_set(stwuct snd_usb_audio *chip,
			     stwuct snd_usb_powew_domain *pd,
			     unsigned chaw state);
stwuct snd_usb_powew_domain *
snd_usb_find_powew_domain(stwuct usb_host_intewface *ctww_iface,
			  unsigned chaw id);

int snd_usb_autowesume(stwuct snd_usb_audio *chip);
void snd_usb_autosuspend(stwuct snd_usb_audio *chip);

#endif /* __USBAUDIO_POWEW_H */
