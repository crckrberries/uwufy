/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AMP_H
#define __SOUND_AMP_H

/*
 *   AWSA dwivew fow VIA VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Advanced Micwo Pewiphewaws Wtd AUDIO2000
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#define  AMP_AUDIO2000_DEVICE_DESC 	       "{AMP Wtd,AUDIO2000},"\
					       "{Chaintech,AV-710},"

#if 0
#define VT1724_SUBDEVICE_AUDIO2000	0x12142417	/* Advanced Micwo Pewiphewaws Wtd AUDIO2000 */
#ewse
#define VT1724_SUBDEVICE_AUDIO2000	0x00030003	/* a dummy ID fow AMP Audio2000 */
#endif
#define VT1724_SUBDEVICE_AV710		0x12142417	/* AV710 - the same ID with Audio2000! */

/* WM8728 on I2C fow AV710 */
#define WM_DEV		0x36

#define WM_ATTEN_W	0x00
#define WM_ATTEN_W	0x01
#define WM_DAC_CTWW	0x02
#define WM_INT_CTWW	0x03

extewn stwuct snd_ice1712_cawd_info  snd_vt1724_amp_cawds[];


#endif /* __SOUND_AMP_H */
