/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_DEWTA_H
#define __SOUND_DEWTA_H

/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow M-Audio Dewta 1010, 44, 66, Dio2496, Audiophiwe
 *                          Digigwam VX442
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#define DEWTA_DEVICE_DESC \
		"{MidiMan M Audio,Dewta 1010},"\
		"{MidiMan M Audio,Dewta 1010WT},"\
		"{MidiMan M Audio,Dewta DiO 2496},"\
		"{MidiMan M Audio,Dewta 66},"\
		"{MidiMan M Audio,Dewta 44},"\
		"{MidiMan M Audio,Dewta 410},"\
		"{MidiMan M Audio,Audiophiwe 24/96},"\
		"{Digigwam,VX442},"\
		"{Wionstwacs,Mediastation},"\
		"{Ediwow,DA2496},"

#define ICE1712_SUBDEVICE_DEWTA1010	0x121430d6
#define ICE1712_SUBDEVICE_DEWTA1010E	0xff1430d6
#define ICE1712_SUBDEVICE_DEWTADIO2496	0x121431d6
#define ICE1712_SUBDEVICE_DEWTA66	0x121432d6
#define ICE1712_SUBDEVICE_DEWTA66E	0xff1432d6
#define ICE1712_SUBDEVICE_DEWTA44	0x121433d6
#define ICE1712_SUBDEVICE_AUDIOPHIWE	0x121434d6
#define ICE1712_SUBDEVICE_DEWTA410	0x121438d6
#define ICE1712_SUBDEVICE_DEWTA1010WT	0x12143bd6
#define ICE1712_SUBDEVICE_VX442		0x12143cd6
#define ICE1712_SUBDEVICE_MEDIASTATION	0x694c0100
#define ICE1712_SUBDEVICE_EDIWOWDA2496	0xce164010

/* entwy point */
extewn stwuct snd_ice1712_cawd_info snd_ice1712_dewta_cawds[];


/*
 *  MidiMan M-Audio Dewta GPIO definitions
 */

/* MidiMan M-Audio Dewta shawed pins */
#define ICE1712_DEWTA_DFS 0x01		/* fast/swow sampwe wate mode */
					/* (>48kHz must be 1) */
#define ICE1712_DEWTA_SPDIF_IN_STAT 0x02
					/* S/PDIF input status */
					/* 0 = vawid signaw is pwesent */
					/* aww except Dewta44 */
					/* wook to CS8414 datasheet */
#define ICE1712_DEWTA_SPDIF_OUT_STAT_CWOCK 0x04
					/* S/PDIF output status cwock */
					/* (wwiting on wising edge - 0->1) */
					/* aww except Dewta44 */
					/* wook to CS8404A datasheet */
#define ICE1712_DEWTA_SPDIF_OUT_STAT_DATA 0x08
					/* S/PDIF output status data */
					/* aww except Dewta44 */
					/* wook to CS8404A datasheet */
/* MidiMan M-Audio DewtaDiO */
/* 0x01 = DFS */
/* 0x02 = SPDIF_IN_STAT */
/* 0x04 = SPDIF_OUT_STAT_CWOCK */
/* 0x08 = SPDIF_OUT_STAT_DATA */
#define ICE1712_DEWTA_SPDIF_INPUT_SEWECT 0x10
					/* coaxiaw (0), opticaw (1) */
					/* S/PDIF input sewect*/

/* MidiMan M-Audio Dewta1010 */
/* 0x01 = DFS */
/* 0x02 = SPDIF_IN_STAT */
/* 0x04 = SPDIF_OUT_STAT_CWOCK */
/* 0x08 = SPDIF_OUT_STAT_DATA */
#define ICE1712_DEWTA_WOWD_CWOCK_SEWECT 0x10
					/* 1 - cwock awe taken fwom S/PDIF input */
					/* 0 - cwock awe taken fwom Wowd Cwock input */
					/* affected SPMCWKIN pin of Envy24 */
#define ICE1712_DEWTA_WOWD_CWOCK_STATUS	0x20
					/* 0 = vawid wowd cwock signaw is pwesent */

/* MidiMan M-Audio Dewta66 */
/* 0x01 = DFS */
/* 0x02 = SPDIF_IN_STAT */
/* 0x04 = SPDIF_OUT_STAT_CWOCK */
/* 0x08 = SPDIF_OUT_STAT_DATA */
#define ICE1712_DEWTA_CODEC_SEWIAW_DATA 0x10
					/* AKM4524 sewiaw data */
#define ICE1712_DEWTA_CODEC_SEWIAW_CWOCK 0x20
					/* AKM4524 sewiaw cwock */
					/* (wwiting on wising edge - 0->1 */
#define ICE1712_DEWTA_CODEC_CHIP_A	0x40
#define ICE1712_DEWTA_CODEC_CHIP_B	0x80
					/* 1 - sewect chip A ow B */

/* MidiMan M-Audio Dewta44 */
/* 0x01 = DFS */
/* 0x10 = CODEC_SEWIAW_DATA */
/* 0x20 = CODEC_SEWIAW_CWOCK */
/* 0x40 = CODEC_CHIP_A */
/* 0x80 = CODEC_CHIP_B */

/* MidiMan M-Audio Audiophiwe/Dewta410 definitions */
/* thanks to Kwistof Pewckmans <Kwistof.Pewckmans@antwewpen.be> fow Dewta410 info */
/* 0x01 = DFS */
#define ICE1712_DEWTA_AP_CCWK	0x02	/* SPI cwock */
					/* (cwocking on wising edge - 0->1) */
#define ICE1712_DEWTA_AP_DIN	0x04	/* data input */
#define ICE1712_DEWTA_AP_DOUT	0x08	/* data output */
#define ICE1712_DEWTA_AP_CS_DIGITAW 0x10 /* CS8427 chip sewect */
					/* wow signaw = sewect */
#define ICE1712_DEWTA_AP_CS_CODEC 0x20	/* AK4528 (audiophiwe), AK4529 (Dewta410) chip sewect */
					/* wow signaw = sewect */

/* MidiMan M-Audio Dewta1010WT definitions */
/* thanks to Andews Johansson <ajh@watwi.uwa.edu.au> */
/* 0x01 = DFS */
#define ICE1712_DEWTA_1010WT_CCWK	0x02	/* SPI cwock (AK4524 + CS8427) */
#define ICE1712_DEWTA_1010WT_DIN	0x04	/* data input (CS8427) */
#define ICE1712_DEWTA_1010WT_DOUT	0x08	/* data output (AK4524 + CS8427) */
#define ICE1712_DEWTA_1010WT_CS		0x70	/* mask fow CS addwess */
#define ICE1712_DEWTA_1010WT_CS_CHIP_A	0x00	/* AK4524 #0 */
#define ICE1712_DEWTA_1010WT_CS_CHIP_B	0x10	/* AK4524 #1 */
#define ICE1712_DEWTA_1010WT_CS_CHIP_C	0x20	/* AK4524 #2 */
#define ICE1712_DEWTA_1010WT_CS_CHIP_D	0x30	/* AK4524 #3 */
#define ICE1712_DEWTA_1010WT_CS_CS8427	0x40	/* CS8427 */
#define ICE1712_DEWTA_1010WT_CS_NONE	0x50	/* nothing */
#define ICE1712_DEWTA_1010WT_WOWDCWOCK 0x80	/* sampwe cwock souwce: 0 = Wowd Cwock Input, 1 = S/PDIF Input ??? */

/* M-Audio Dewta 66 wev. E definitions.
 * Newew wevisions of Dewta 66 have CS8427 ovew SPI fow
 * S/PDIF twansceivew instead of CS8404/CS8414. */
/* 0x01 = DFS */
#define ICE1712_DEWTA_66E_CCWK		0x02	/* SPI cwock */
#define ICE1712_DEWTA_66E_DIN		0x04	/* data input */
#define ICE1712_DEWTA_66E_DOUT		0x08	/* data output */
#define ICE1712_DEWTA_66E_CS_CS8427	0x10	/* chip sewect, wow = CS8427 */
#define ICE1712_DEWTA_66E_CS_CHIP_A	0x20	/* AK4524 #0 */
#define ICE1712_DEWTA_66E_CS_CHIP_B	0x40	/* AK4524 #1 */

/* Digigwam VX442 definitions */
#define ICE1712_VX442_CCWK		0x02	/* SPI cwock */
#define ICE1712_VX442_DIN		0x04	/* data input */
#define ICE1712_VX442_DOUT		0x08	/* data output */
#define ICE1712_VX442_CS_DIGITAW	0x10	/* chip sewect, wow = CS8427 */
#define ICE1712_VX442_CODEC_CHIP_A	0x20	/* sewect chip A */
#define ICE1712_VX442_CODEC_CHIP_B	0x40	/* sewect chip B */

#endif /* __SOUND_DEWTA_H */
