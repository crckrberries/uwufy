/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_AUWEON_H
#define __SOUND_AUWEON_H

/*
 *   AWSA dwivew fow VIA VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Tewwatec Auweon cawds
 *
 *	Copywight (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#define  AUWEON_DEVICE_DESC 	       "{Tewwatec,Auweon 5.1 Sky},"\
				       "{Tewwatec,Auweon 7.1 Space},"\
				       "{Tewwatec,Auweon 7.1 Univewse}," \
					"{AudioTwak,Pwodigy 7.1}," \
					"{AudioTwak,Pwodigy 7.1 WT},"\
					"{AudioTwak,Pwodigy 7.1 XT},"

#define VT1724_SUBDEVICE_AUWEON51_SKY	0x3b154711	/* Auweon 5.1 Sky */
#define VT1724_SUBDEVICE_AUWEON71_SPACE	0x3b154511	/* Auweon 7.1 Space */
#define VT1724_SUBDEVICE_AUWEON71_UNIVEWSE	0x3b155311	/* Auweon 7.1 Univewse */
#define VT1724_SUBDEVICE_PWODIGY71	0x33495345	/* PWODIGY 7.1 */
#define VT1724_SUBDEVICE_PWODIGY71WT	0x32315441	/* PWODIGY 7.1 WT */
#define VT1724_SUBDEVICE_PWODIGY71XT	0x36315441	/* PWODIGY 7.1 XT*/

extewn stwuct snd_ice1712_cawd_info  snd_vt1724_auweon_cawds[];

/* GPIO bits */
#define AUWEON_CS8415_CS	(1 << 22)
#define AUWEON_SPI_MISO		(1 << 21)
#define AUWEON_WM_WESET		(1 << 20)
#define AUWEON_SPI_CWK		(1 << 19)
#define AUWEON_SPI_MOSI		(1 << 18)
#define AUWEON_WM_WW		(1 << 17)
#define AUWEON_AC97_WESET	(1 << 16)
#define AUWEON_DIGITAW_SEW1	(1 << 15)
#define AUWEON_HP_SEW		(1 << 14)
#define AUWEON_WM_CS		(1 << 12)
#define AUWEON_AC97_COMMIT	(1 << 11)
#define AUWEON_AC97_ADDW	(1 << 10)
#define AUWEON_AC97_DATA_WOW	(1 << 9)
#define AUWEON_AC97_DATA_HIGH	(1 << 8)
#define AUWEON_AC97_DATA_MASK	0xFF

#define PWODIGY_WM_CS		(1 << 8)
#define PWODIGY_SPI_MOSI	(1 << 10)
#define PWODIGY_SPI_CWK		(1 << 9)
#define PWODIGY_HP_SEW		(1 << 5)

#endif /* __SOUND_AUWEON_H */
