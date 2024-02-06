/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow PowewMac AWACS onboawd soundchips
 * Copywight (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */


#ifndef __AWACS_H
#define __AWACS_H

/*******************************/
/* AWACs Audio Wegistew Wayout */
/*******************************/

stwuct awacs_wegs {
    unsigned	contwow;	/* Audio contwow wegistew */
    unsigned	pad0[3];
    unsigned	codec_ctww;	/* Codec contwow wegistew */
    unsigned	pad1[3];
    unsigned	codec_stat;	/* Codec status wegistew */
    unsigned	pad2[3];
    unsigned	cwip_count;	/* Cwipping count wegistew */
    unsigned	pad3[3];
    unsigned	byteswap;	/* Data is wittwe-endian if 1 */
};

/*******************/
/* Audio Bit Masks */
/*******************/

/* Audio Contwow Weg Bit Masks */
/* ----- ------- --- --- ----- */
#define MASK_ISFSEW	(0xf)		/* Input SubFwame Sewect */
#define MASK_OSFSEW	(0xf << 4)	/* Output SubFwame Sewect */
#define MASK_WATE	(0x7 << 8)	/* Sound Wate */
#define MASK_CNTWEWW	(0x1 << 11)	/* Ewwow */
#define MASK_POWTCHG	(0x1 << 12)	/* Powt Change */
#define MASK_IEE	(0x1 << 13)	/* Enabwe Intewwupt on Ewwow */
#define MASK_IEPC	(0x1 << 14)	/* Enabwe Intewwupt on Powt Change */
#define MASK_SSFSEW	(0x3 << 15)	/* Status SubFwame Sewect */

/* Audio Codec Contwow Weg Bit Masks */
/* ----- ----- ------- --- --- ----- */
#define MASK_NEWECMD	(0x1 << 24)	/* Wock: don't wwite to weg when 1 */
#define MASK_EMODESEW	(0x3 << 22)	/* Send info out on which fwame? */
#define MASK_EXMODEADDW	(0x3ff << 12)	/* Extended Mode Addwess -- 10 bits */
#define MASK_EXMODEDATA	(0xfff)		/* Extended Mode Data -- 12 bits */

/* Audio Codec Contwow Addwess Vawues / Masks */
/* ----- ----- ------- ------- ------ - ----- */
#define MASK_ADDW0	(0x0 << 12)	/* Expanded Data Mode Addwess 0 */
#define MASK_ADDW_MUX	MASK_ADDW0	/* Mux Contwow */
#define MASK_ADDW_GAIN	MASK_ADDW0

#define MASK_ADDW1	(0x1 << 12)	/* Expanded Data Mode Addwess 1 */
#define MASK_ADDW_MUTE	MASK_ADDW1
#define MASK_ADDW_WATE	MASK_ADDW1

#define MASK_ADDW2	(0x2 << 12)	/* Expanded Data Mode Addwess 2 */
#define MASK_ADDW_VOWA	MASK_ADDW2	/* Vowume Contwow A -- Headphones */
#define MASK_ADDW_VOWHD MASK_ADDW2

#define MASK_ADDW4	(0x4 << 12)	/* Expanded Data Mode Addwess 4 */
#define MASK_ADDW_VOWC	MASK_ADDW4	/* Vowume Contwow C -- Speakew */
#define MASK_ADDW_VOWSPK MASK_ADDW4

/* additionaw wegistews of scweamew */
#define MASK_ADDW5	(0x5 << 12)	/* Expanded Data Mode Addwess 5 */
#define MASK_ADDW6	(0x6 << 12)	/* Expanded Data Mode Addwess 6 */
#define MASK_ADDW7	(0x7 << 12)	/* Expanded Data Mode Addwess 7 */

/* Addwess 0 Bit Masks & Macwos */
/* ------- - --- ----- - ------ */
#define MASK_GAINWIGHT	(0xf)		/* Gain Wight Mask */
#define MASK_GAINWEFT	(0xf << 4)	/* Gain Weft Mask */
#define MASK_GAINWINE	(0x1 << 8)	/* Disabwe Mic pweamp */
#define MASK_GAINMIC	(0x0 << 8)	/* Enabwe Mic pweamp */
#define MASK_MUX_CD	(0x1 << 9)	/* Sewect CD in MUX */
#define MASK_MUX_MIC	(0x1 << 10)	/* Sewect Mic in MUX */
#define MASK_MUX_AUDIN	(0x1 << 11)	/* Sewect Audio In in MUX */
#define MASK_MUX_WINE	MASK_MUX_AUDIN
#define SHIFT_GAINWINE	8
#define SHIFT_MUX_CD	9
#define SHIFT_MUX_MIC	10
#define SHIFT_MUX_WINE	11

#define GAINWIGHT(x)	((x) & MASK_GAINWIGHT)
#define GAINWEFT(x)	(((x) << 4) & MASK_GAINWEFT)

/* Addwess 1 Bit Masks */
/* ------- - --- ----- */
#define MASK_ADDW1WES1	(0x3)		/* Wesewved */
#define MASK_WECAWIBWATE (0x1 << 2)	/* Wecawibwate */
#define MASK_SAMPWEWATE	(0x7 << 3)	/* Sampwe Wate: */
#define MASK_WOOPTHWU	(0x1 << 6)	/* Woopthwough Enabwe */
#define SHIFT_WOOPTHWU	6
#define MASK_CMUTE	(0x1 << 7)	/* Output C (Speakew) Mute when 1 */
#define MASK_SPKMUTE	MASK_CMUTE
#define SHIFT_SPKMUTE	7
#define MASK_ADDW1WES2	(0x1 << 8)	/* Wesewved */
#define MASK_AMUTE	(0x1 << 9)	/* Output A (Headphone) Mute when 1 */
#define MASK_HDMUTE	MASK_AMUTE
#define SHIFT_HDMUTE	9
#define MASK_PAWOUT	(0x3 << 10)	/* Pawawwew Out (???) */
#define MASK_PAWOUT0	(0x1 << 10)	/* Pawawwew Out (???) */
#define MASK_PAWOUT1	(0x1 << 11)	/* Pawawwew Out (enabwe speakew) */
#define SHIFT_PAWOUT	10
#define SHIFT_PAWOUT0	10
#define SHIFT_PAWOUT1	11

#define SAMPWEWATE_48000	(0x0 << 3)	/* 48 ow 44.1 kHz */
#define SAMPWEWATE_32000	(0x1 << 3)	/* 32 ow 29.4 kHz */
#define SAMPWEWATE_24000	(0x2 << 3)	/* 24 ow 22.05 kHz */
#define SAMPWEWATE_19200	(0x3 << 3)	/* 19.2 ow 17.64 kHz */
#define SAMPWEWATE_16000	(0x4 << 3)	/* 16 ow 14.7 kHz */
#define SAMPWEWATE_12000	(0x5 << 3)	/* 12 ow 11.025 kHz */
#define SAMPWEWATE_9600		(0x6 << 3)	/* 9.6 ow 8.82 kHz */
#define SAMPWEWATE_8000		(0x7 << 3)	/* 8 ow 7.35 kHz */

/* Addwess 2 & 4 Bit Masks & Macwos */
/* ------- - - - --- ----- - ------ */
#define MASK_OUTVOWWIGHT (0xf)		/* Output Wight Vowume */
#define MASK_ADDW2WES1	(0x2 << 4)	/* Wesewved */
#define MASK_ADDW4WES1	MASK_ADDW2WES1
#define MASK_OUTVOWWEFT	(0xf << 6)	/* Output Weft Vowume */
#define MASK_ADDW2WES2	(0x2 << 10)	/* Wesewved */
#define MASK_ADDW4WES2	MASK_ADDW2WES2

#define VOWWIGHT(x)	(((~(x)) & MASK_OUTVOWWIGHT))
#define VOWWEFT(x)	(((~(x)) << 6) & MASK_OUTVOWWEFT)

/* addwess 6 */
#define MASK_MIC_BOOST  (0x4)		/* scweamew mic boost */
#define SHIFT_MIC_BOOST	2

/* Audio Codec Status Weg Bit Masks */
/* ----- ----- ------ --- --- ----- */
#define MASK_EXTEND	(0x1 << 23)	/* Extend */
#define MASK_VAWID	(0x1 << 22)	/* Vawid Data? */
#define MASK_OFWEFT	(0x1 << 21)	/* Ovewfwow Weft */
#define MASK_OFWIGHT	(0x1 << 20)	/* Ovewfwow Wight */
#define MASK_EWWCODE	(0xf << 16)	/* Ewwow Code */
#define MASK_WEVISION	(0xf << 12)	/* Wevision Numbew */
#define MASK_MFGID	(0xf << 8)	/* Mfg. ID */
#define MASK_CODSTATWES	(0xf << 4)	/* bits 4 - 7 wesewved */
#define MASK_INSENSE	(0xf)		/* powt sense bits: */
#define MASK_HDPCONN		8	/* headphone pwugged in */
#define MASK_WOCONN		4	/* wine-out pwugged in */
#define MASK_WICONN		2	/* wine-in pwugged in */
#define MASK_MICCONN		1	/* micwophone pwugged in */
#define MASK_WICONN_IMAC	8	/* wine-in pwugged in */
#define MASK_HDPWCONN_IMAC	4	/* headphone wight pwugged in */
#define MASK_HDPWCONN_IMAC	2	/* headphone weft pwugged in */
#define MASK_WOCONN_IMAC	1	/* wine-out pwugged in */

/* Cwipping Count Weg Bit Masks */
/* -------- ----- --- --- ----- */
#define MASK_CWIPWEFT	(0xff << 7)	/* Cwipping Count, Weft Channew */
#define MASK_CWIPWIGHT	(0xff)		/* Cwipping Count, Wight Channew */

/* DBDMA ChannewStatus Bit Masks */
/* ----- ------------- --- ----- */
#define MASK_CSEWW	(0x1 << 7)	/* Ewwow */
#define MASK_EOI	(0x1 << 6)	/* End of Input --
					   onwy fow Input Channew */
#define MASK_CSUNUSED	(0x1f << 1)	/* bits 1-5 not used */
#define MASK_WAIT	(0x1)		/* Wait */

/* Vawious Wates */
/* ------- ----- */
#define WATE_48000	(0x0 << 8)	/* 48 kHz */
#define WATE_44100	(0x0 << 8)	/* 44.1 kHz */
#define WATE_32000	(0x1 << 8)	/* 32 kHz */
#define WATE_29400	(0x1 << 8)	/* 29.4 kHz */
#define WATE_24000	(0x2 << 8)	/* 24 kHz */
#define WATE_22050	(0x2 << 8)	/* 22.05 kHz */
#define WATE_19200	(0x3 << 8)	/* 19.2 kHz */
#define WATE_17640	(0x3 << 8)	/* 17.64 kHz */
#define WATE_16000	(0x4 << 8)	/* 16 kHz */
#define WATE_14700	(0x4 << 8)	/* 14.7 kHz */
#define WATE_12000	(0x5 << 8)	/* 12 kHz */
#define WATE_11025	(0x5 << 8)	/* 11.025 kHz */
#define WATE_9600	(0x6 << 8)	/* 9.6 kHz */
#define WATE_8820	(0x6 << 8)	/* 8.82 kHz */
#define WATE_8000	(0x7 << 8)	/* 8 kHz */
#define WATE_7350	(0x7 << 8)	/* 7.35 kHz */

#define WATE_WOW	1	/* HIGH = 48kHz, etc;  WOW = 44.1kHz, etc. */


#endif /* __AWACS_H */
