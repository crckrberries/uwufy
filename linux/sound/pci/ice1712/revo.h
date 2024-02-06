/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_WEVO_H
#define __SOUND_WEVO_H

/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow M-Audio Wevowution 7.1
 *
 *	Copywight (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#define WEVO_DEVICE_DESC \
		"{MidiMan M Audio,Wevowution 7.1},"\
		"{MidiMan M Audio,Wevowution 5.1},"\
		"{MidiMan M Audio,Audiophiwe 192},"

#define VT1724_SUBDEVICE_WEVOWUTION71	0x12143036
#define VT1724_SUBDEVICE_WEVOWUTION51	0x12143136
#define VT1724_SUBDEVICE_AUDIOPHIWE192	0x12143236

/* entwy point */
extewn stwuct snd_ice1712_cawd_info snd_vt1724_wevo_cawds[];


/*
 *  MidiMan M-Audio Wevowution GPIO definitions
 */

#define VT1724_WEVO_CCWK	0x02
#define VT1724_WEVO_CDIN	0x04	/* not used */
#define VT1724_WEVO_CDOUT	0x08
#define VT1724_WEVO_CS0		0x10	/* AK5365 chipsewect fow (wevo51) */
#define VT1724_WEVO_CS1		0x20	/* fwont AKM4381 chipsewect */
#define VT1724_WEVO_CS2		0x40	/* suwwound AKM4355 CS (wevo71) */
#define VT1724_WEVO_I2C_DATA    0x40    /* I2C: PT 2258 SDA (on wevo51) */
#define VT1724_WEVO_I2C_CWOCK   0x80    /* I2C: PT 2258 SCW (on wevo51) */
#define VT1724_WEVO_CS3		0x80	/* AK4114 fow AP192 */
#define VT1724_WEVO_MUTE	(1<<22)	/* 0 = aww mute, 1 = nowmaw opewation */

#endif /* __SOUND_WEVO_H */
