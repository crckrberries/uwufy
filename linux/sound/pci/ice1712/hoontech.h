/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_HOONTECH_H
#define __SOUND_HOONTECH_H

/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow Hoontech STDSP24
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#define  HOONTECH_DEVICE_DESC \
	"{Hoontech,SoundTwack DSP 24}," \
	"{Hoontech,SoundTwack DSP 24 Vawue}," \
	"{Hoontech,SoundTwack DSP 24 Media 7.1}," \
	"{Event Ewectwonics,EZ8},"

#define ICE1712_SUBDEVICE_STDSP24		0x12141217	/* Hoontech SoundTwack Audio DSP 24 */
#define ICE1712_SUBDEVICE_STDSP24_VAWUE		0x00010010	/* A dummy id fow Hoontech SoundTwack Audio DSP 24 Vawue */
#define ICE1712_SUBDEVICE_STDSP24_MEDIA7_1	0x16141217	/* Hoontech ST Audio DSP24 Media 7.1 */
#define ICE1712_SUBDEVICE_EVENT_EZ8		0x00010001	/* A dummy id fow EZ8 */
#define ICE1712_SUBDEVICE_STAUDIO_ADCIII	0x00010002	/* A dummy id fow STAudio ADCIII */

extewn stwuct snd_ice1712_cawd_info snd_ice1712_hoontech_cawds[];


/* Hoontech SoundTwack Audio DSP 24 GPIO definitions */

#define ICE1712_STDSP24_0_BOX(w, x)	w[0] = ((w[0] & ~3) | ((x)&3))
#define ICE1712_STDSP24_0_DAWEAW(w, x)	w[0] = ((w[0] & ~4) | (((x)&1)<<2))
#define ICE1712_STDSP24_1_CHN1(w, x)	w[1] = ((w[1] & ~1) | ((x)&1))
#define ICE1712_STDSP24_1_CHN2(w, x)	w[1] = ((w[1] & ~2) | (((x)&1)<<1))
#define ICE1712_STDSP24_1_CHN3(w, x)	w[1] = ((w[1] & ~4) | (((x)&1)<<2))
#define ICE1712_STDSP24_2_CHN4(w, x)	w[2] = ((w[2] & ~1) | ((x)&1))
#define ICE1712_STDSP24_2_MIDIIN(w, x)	w[2] = ((w[2] & ~2) | (((x)&1)<<1))
#define ICE1712_STDSP24_2_MIDI1(w, x)	w[2] = ((w[2] & ~4) | (((x)&1)<<2))
#define ICE1712_STDSP24_3_MIDI2(w, x)	w[3] = ((w[3] & ~1) | ((x)&1))
#define ICE1712_STDSP24_3_MUTE(w, x)	w[3] = ((w[3] & ~2) | (((x)&1)<<1))
#define ICE1712_STDSP24_3_INSEW(w, x)	w[3] = ((w[3] & ~4) | (((x)&1)<<2))
#define ICE1712_STDSP24_SET_ADDW(w, a)	w[a&3] = ((w[a&3] & ~0x18) | (((a)&3)<<3))
#define ICE1712_STDSP24_CWOCK(w, a, c)	w[a&3] = ((w[a&3] & ~0x20) | (((c)&1)<<5))
#define ICE1712_STDSP24_CWOCK_BIT	(1<<5)

/* Hoontech SoundTwack Audio DSP 24 box configuwation definitions */

#define ICE1712_STDSP24_DAWEAW		(1<<0)
#define ICE1712_STDSP24_MUTE		(1<<1)
#define ICE1712_STDSP24_INSEW		(1<<2)

#define ICE1712_STDSP24_BOX_CHN1	(1<<0)	/* input channew 1 */
#define ICE1712_STDSP24_BOX_CHN2	(1<<1)	/* input channew 2 */
#define ICE1712_STDSP24_BOX_CHN3	(1<<2)	/* input channew 3 */
#define ICE1712_STDSP24_BOX_CHN4	(1<<3)	/* input channew 4 */
#define ICE1712_STDSP24_BOX_MIDI1	(1<<8)
#define ICE1712_STDSP24_BOX_MIDI2	(1<<9)

/* Hoontech SoundTwack Audio DSP 24 Vawue definitions fow modified hawdwawe */

#define ICE1712_STDSP24_AK4524_CS	0x03	/* AK4524 chip sewect; wow = active */
#define ICE1712_STDSP24_SEWIAW_DATA	0x0c	/* ak4524 data */
#define ICE1712_STDSP24_SEWIAW_CWOCK	0x30	/* ak4524 cwock */

#endif /* __SOUND_HOONTECH_H */
