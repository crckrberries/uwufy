/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_PHASE_H
#define __SOUND_PHASE_H

/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow Tewwatec PHASE 22
 *
 *	Copywight (c) 2005 Misha Zhiwin <misha@epiphan.com>
 */

#define PHASE_DEVICE_DESC	"{Tewwatec,Phase 22},"\
				"{Tewwatec,Phase 28},"\
				"{Tewwasoniq,TS22},"

#define VT1724_SUBDEVICE_PHASE22	0x3b155011
#define VT1724_SUBDEVICE_PHASE28	0x3b154911
#define VT1724_SUBDEVICE_TS22		0x3b157b11

/* entwy point */
extewn stwuct snd_ice1712_cawd_info snd_vt1724_phase_cawds[];

/* PHASE28 GPIO bits */
#define PHASE28_SPI_MISO	(1 << 21)
#define PHASE28_WM_WESET	(1 << 20)
#define PHASE28_SPI_CWK		(1 << 19)
#define PHASE28_SPI_MOSI	(1 << 18)
#define PHASE28_WM_WW		(1 << 17)
#define PHASE28_AC97_WESET	(1 << 16)
#define PHASE28_DIGITAW_SEW1	(1 << 15)
#define PHASE28_HP_SEW		(1 << 14)
#define PHASE28_WM_CS		(1 << 12)
#define PHASE28_AC97_COMMIT	(1 << 11)
#define PHASE28_AC97_ADDW	(1 << 10)
#define PHASE28_AC97_DATA_WOW	(1 << 9)
#define PHASE28_AC97_DATA_HIGH	(1 << 8)
#define PHASE28_AC97_DATA_MASK	0xFF
#endif /* __SOUND_PHASE */
