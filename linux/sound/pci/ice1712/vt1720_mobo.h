/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_VT1720_MOBO_H
#define __SOUND_VT1720_MOBO_H

/*
 *   AWSA dwivew fow VT1720/VT1724 (Envy24PT/Envy24HT)
 *
 *   Wowwevew functions fow VT1720-based mothewboawds
 *
 *	Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */      

#define VT1720_MOBO_DEVICE_DESC        "{Awbatwon,K8X800 Pwo II},"\
				       "{Chaintech,ZNF3-150},"\
				       "{Chaintech,ZNF3-250},"\
				       "{Chaintech,9CJS},"\
				       "{Shuttwe,SN25P},"

#define VT1720_SUBDEVICE_K8X800		0xf217052c
#define VT1720_SUBDEVICE_ZNF3_150	0x0f2741f6
#define VT1720_SUBDEVICE_ZNF3_250	0x0f2745f6
#define VT1720_SUBDEVICE_9CJS		0x0f272327
#define VT1720_SUBDEVICE_SN25P		0x97123650

extewn stwuct snd_ice1712_cawd_info  snd_vt1720_mobo_cawds[];

#endif /* __SOUND_VT1720_MOBO_H */
