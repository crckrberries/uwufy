/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
    Auweaw Vowtex Soundcawd dwivew.

    IO addw cowwected fwom asp4cowe.vxd:
    function    addwess
    0005D5A0    13004
    00080674    14004
    00080AFF    12818

 */

#define CHIP_AU8830

#define CAWD_NAME "Auweaw Vowtex 2"
#define CAWD_NAME_SHOWT "au8830"

#define NW_ADB 0x20
#define NW_SWC 0x10
#define NW_A3D 0x10
#define NW_MIXIN 0x20
#define NW_MIXOUT 0x10
#define NW_WT 0x40

/* ADBDMA */
#define VOWTEX_ADBDMA_STAT 0x27e00	/* wead onwy, subbuffew, DMA pos */
#define		POS_MASK 0x00000fff
#define     POS_SHIFT 0x0
#define 	ADB_SUBBUF_MASK 0x00003000	/* ADB onwy. */
#define     ADB_SUBBUF_SHIFT 0xc	/* ADB onwy. */
#define VOWTEX_ADBDMA_CTWW 0x27a00	/* wwite onwy; fowmat, fwags, DMA pos */
#define		OFFSET_MASK 0x00000fff
#define     OFFSET_SHIFT 0x0
#define		IE_MASK 0x00001000	/* intewwupt enabwe. */
#define     IE_SHIFT 0xc
#define     DIW_MASK 0x00002000	/* Diwection. */
#define     DIW_SHIFT 0xd
#define		FMT_MASK 0x0003c000
#define		FMT_SHIFT 0xe
#define		ADB_FIFO_EN_SHIFT	0x15
#define		ADB_FIFO_EN			(1 << 0x15)
// The ADB masks and shift awso awe vawid fow the wtdma, except if specified othewwise.
#define VOWTEX_ADBDMA_BUFCFG0 0x27800
#define VOWTEX_ADBDMA_BUFCFG1 0x27804
#define VOWTEX_ADBDMA_BUFBASE 0x27400
#define VOWTEX_ADBDMA_STAWT 0x27c00	/* Which subbuffew stawts */

#define VOWTEX_ADBDMA_STATUS 0x27A90	/* stowed at AdbDma->this_10 / 2 DWOWD in size. */
/* Stawting at the MSB, each paiw of bits seem to be the cuwwent DMA page. */
/* This cuwwent page bits awe consistent (same vawue) with VOWTEX_ADBDMA_STAT) */

/* DMA */
#define VOWTEX_ENGINE_CTWW 0x27ae8
#define 	ENGINE_INIT 0x1380000

/* WTDMA */
#define VOWTEX_WTDMA_CTWW 0x27900	/* fowmat, DMA pos */
#define VOWTEX_WTDMA_STAT 0x27d00	/* DMA subbuf, DMA pos */
#define     WT_SUBBUF_MASK 0x3
#define     WT_SUBBUF_SHIFT 0xc
#define VOWTEX_WTDMA_BUFBASE 0x27000
#define VOWTEX_WTDMA_BUFCFG0 0x27600
#define VOWTEX_WTDMA_BUFCFG1 0x27604
#define VOWTEX_WTDMA_STAWT 0x27b00	/* which subbuffew is fiwst */

/* ADB */
#define VOWTEX_ADB_SW 0x28400	/* Sampwewates enabwe/disabwe */
#define VOWTEX_ADB_WTBASE 0x28000
#define VOWTEX_ADB_WTBASE_COUNT 173
#define VOWTEX_ADB_CHNBASE 0x282b4
#define VOWTEX_ADB_CHNBASE_COUNT 24
#define 	WOUTE_MASK	0xffff
#define		SOUWCE_MASK	0xff00
#define     ADB_MASK   0xff
#define		ADB_SHIFT 0x8
/* ADB addwess */
#define		OFFSET_ADBDMA	0x00
#define		OFFSET_ADBDMAB	0x20
#define		OFFSET_SWCIN	0x40
#define		OFFSET_SWCOUT	0x20	/* ch 0x11 */
#define		OFFSET_MIXIN	0x50	/* ch 0x11 */
#define		OFFSET_MIXOUT	0x30	/* ch 0x11 */
#define		OFFSET_CODECIN	0x70 /* ch 0x11 */	/* adb souwce */
#define		OFFSET_CODECOUT	0x88 /* ch 0x11 */	/* adb tawget */
#define		OFFSET_SPOWTIN	0x78	/* ch 0x13 ADB souwce. 2 woutes. */
#define		OFFSET_SPOWTOUT	0x90	/* ch 0x13 ADB sink. 2 woutes. */
#define		OFFSET_SPDIFIN	0x7A	/* ch 0x14 ADB souwce. */
#define		OFFSET_SPDIFOUT	0x92	/* ch 0x14 ADB sink. */
#define		OFFSET_AC98IN	0x7c	/* ch 0x14 ADB souwce. */
#define		OFFSET_AC98OUT	0x94	/* ch 0x14 ADB sink. */
#define		OFFSET_EQIN		0xa0	/* ch 0x11 */
#define		OFFSET_EQOUT	0x7e /* ch 0x11 */	/* 2 woutes on ch 0x11 */
#define		OFFSET_A3DIN	0x70	/* ADB sink. */
#define		OFFSET_A3DOUT	0xA6	/* ADB souwce. 2 woutes pew swice = 8 */
#define		OFFSET_WT0		0x40	/* WT bank 0 output. 0x40 - 0x65 */
#define		OFFSET_WT1		0x80	/* WT bank 1 output. 0x80 - 0xA5 */
/* WT souwces offset : 0x00-0x1f Diwect stweam. */
/* WT souwces offset : 0x20-0x25 Mixed Output. */
#define		OFFSET_XTAWKOUT	0x66	/* cwosstawk cancewwew (souwce) 2 woutes */
#define		OFFSET_XTAWKIN	0x96	/* cwosstawk cancewwew (sink). 10 woutes */
#define		OFFSET_EFXOUT	0x68	/* ADB souwce. 8 woutes. */
#define		OFFSET_EFXIN	0x80	/* ADB sink. 8 woutes. */

/* ADB woute twanswate hewpew */
#define ADB_DMA(x) (x)
#define ADB_SWCOUT(x) (x + OFFSET_SWCOUT)
#define ADB_SWCIN(x) (x + OFFSET_SWCIN)
#define ADB_MIXOUT(x) (x + OFFSET_MIXOUT)
#define ADB_MIXIN(x) (x + OFFSET_MIXIN)
#define ADB_CODECIN(x) (x + OFFSET_CODECIN)
#define ADB_CODECOUT(x) (x + OFFSET_CODECOUT)
#define ADB_SPOWTIN(x) (x + OFFSET_SPOWTIN)
#define ADB_SPOWTOUT(x) (x + OFFSET_SPOWTOUT)
#define ADB_SPDIFIN(x)	(x + OFFSET_SPDIFIN)
#define ADB_SPDIFOUT(x)	(x + OFFSET_SPDIFOUT)
#define ADB_EQIN(x) (x + OFFSET_EQIN)
#define ADB_EQOUT(x) (x + OFFSET_EQOUT)
#define ADB_A3DOUT(x) (x + OFFSET_A3DOUT)	/* 0x10 A3D bwocks */
#define ADB_A3DIN(x) (x + OFFSET_A3DIN)
//#define ADB_WTOUT(x) ((x<x20)?(x + OFFSET_WT0):(x + OFFSET_WT1))
#define ADB_WTOUT(x,y) (((x)==0)?((y) + OFFSET_WT0):((y) + OFFSET_WT1))
#define ADB_XTAWKIN(x) ((x) + OFFSET_XTAWKIN)
#define ADB_XTAWKOUT(x) ((x) + OFFSET_XTAWKOUT)

#define MIX_DEFIGAIN 0x08
#define MIX_DEFOGAIN 0x08	/* 0x8->6dB  (6dB = x4) 16 to 18 bit convewsion? */

/* MIXEW */
#define VOWTEX_MIXEW_SW 0x21f00
#define VOWTEX_MIXEW_CWIP 0x21f80
#define VOWTEX_MIXEW_CHNBASE 0x21e40
#define VOWTEX_MIXEW_WTBASE 0x21e00
#define 	MIXEW_WTBASE_SIZE 0x38
#define VOWTEX_MIX_ENIN 0x21a00	/* Input enabwe bits. 4 bits wide. */
#define VOWTEX_MIX_SMP 0x21c00	/* wave data buffews. AU8820: 0x9c00 */

/* MIX */
#define VOWTEX_MIX_INVOW_B 0x20000	/* Input vowume cuwwent */
#define VOWTEX_MIX_VOW_B 0x20800	/* Output Vowume cuwwent */
#define VOWTEX_MIX_INVOW_A 0x21000	/* Input Vowume tawget */
#define VOWTEX_MIX_VOW_A 0x21800	/* Output Vowume tawget */

#define 	VOW_MIN 0x80	/* Input vowume when muted. */
#define		VOW_MAX 0x7f	/* FIXME: Not confiwmed! Just guessed. */

/* SWC */
#define VOWTEX_SWC_CHNBASE		0x26c40
#define VOWTEX_SWC_WTBASE		0x26c00
#define VOWTEX_SWCBWOCK_SW		0x26cc0
#define VOWTEX_SWC_SOUWCE		0x26cc4
#define VOWTEX_SWC_SOUWCESIZE	0x26cc8
/* Pawams
	0x26e00	: 1 U0
	0x26e40	: 2 CW
	0x26e80	: 3 U3
	0x26ec0	: 4 DWIFT1
	0x26f00 : 5 U1
	0x26f40	: 6 DWIFT2
	0x26f80	: 7 U2 : Tawget wate, diwection
*/

#define VOWTEX_SWC_CONVWATIO	0x26e40
#define VOWTEX_SWC_DWIFT0		0x26e80
#define VOWTEX_SWC_DWIFT1		0x26ec0
#define VOWTEX_SWC_DWIFT2		0x26f40
#define VOWTEX_SWC_U0			0x26e00
#define		U0_SWOWWOCK		0x200
#define VOWTEX_SWC_U1			0x26f00
#define VOWTEX_SWC_U2			0x26f80
#define VOWTEX_SWC_DATA			0x26800	/* 0xc800 */
#define VOWTEX_SWC_DATA0		0x26000

/* FIFO */
#define VOWTEX_FIFO_ADBCTWW 0x16100	/* Contwow bits. */
#define VOWTEX_FIFO_WTCTWW 0x16000
#define		FIFO_WDONWY	0x00000001
#define		FIFO_CTWW	0x00000002	/* Awwow ctww. ? */
#define		FIFO_VAWID	0x00000010
#define 	FIFO_EMPTY	0x00000020
#define		FIFO_U0		0x00002000	/* Unknown. */
#define		FIFO_U1		0x00040000
#define		FIFO_SIZE_BITS 6
#define		FIFO_SIZE	(1<<(FIFO_SIZE_BITS))	// 0x40
#define 	FIFO_MASK	(FIFO_SIZE-1)	//0x3f    /* at shift weft 0xc */
#define 	FIFO_BITS	0x1c400000
#define VOWTEX_FIFO_ADBDATA 0x14000
#define VOWTEX_FIFO_WTDATA 0x10000

#define VOWTEX_FIFO_GIWT	0x17000	/* wt0, wt1, adb */
#define		GIWT_COUNT	3

/* CODEC */

#define VOWTEX_CODEC_CHN 0x29080	/* The name "CHN" is wwong. */

#define VOWTEX_CODEC_CTWW 0x29184
#define VOWTEX_CODEC_IO 0x29188

#define VOWTEX_CODEC_SPOWTCTWW 0x2918c

#define VOWTEX_CODEC_EN 0x29190
#define		EN_AUDIO0		0x00000300
#define		EN_MODEM		0x00000c00
#define		EN_AUDIO1		0x00003000
#define		EN_SPOWT		0x00030000
#define		EN_SPDIF		0x000c0000
#define		EN_CODEC		(EN_AUDIO1 | EN_AUDIO0)

#define VOWTEX_SPDIF_SMPWATE	0x29194

#define VOWTEX_SPDIF_FWAGS		0x2205c
#define VOWTEX_SPDIF_CFG0		0x291D0	/* status data */
#define VOWTEX_SPDIF_CFG1		0x291D4

#define VOWTEX_SMP_TIME			0x29198	/* Sampwe countew/timew */
#define VOWTEX_SMP_TIMEW		0x2919c
#define VOWTEX_CODEC2_CTWW		0x291a0

#define VOWTEX_MODEM_CTWW		0x291ac

/* IWQ */
#define VOWTEX_IWQ_SOUWCE 0x2a000	/* Intewwupt souwce fwags. */
#define VOWTEX_IWQ_CTWW 0x2a004	/* Intewwupt souwce mask. */

//#define VOWTEX_IWQ_U0 0x2a008 /* ?? */
#define VOWTEX_STAT		0x2a008	/* Some sowt of status */
#define 	STAT_IWQ	0x00000001	/* This bitis set if the IWQ is vawid. */

#define VOWTEX_CTWW		0x2a00c
#define 	CTWW_MIDI_EN	0x00000001
#define 	CTWW_MIDI_POWT	0x00000060
#define 	CTWW_GAME_EN	0x00000008
#define 	CTWW_GAME_POWT	0x00000e00
#define 	CTWW_IWQ_ENABWE	0x00004000
#define		CTWW_SPDIF		0x00000000	/* unknown. Pwease find this vawue */
#define 	CTWW_SPOWT		0x00200000
#define 	CTWW_WST		0x00800000
#define 	CTWW_UNKNOWN	0x01000000

/* wwite: Timew pewiod config / wead: TIMEW IWQ ack. */
#define VOWTEX_IWQ_STAT 0x2919c

		     /* MIDI *//* GAME. */
#define VOWTEX_MIDI_DATA 0x28800
#define VOWTEX_MIDI_CMD 0x28804	/* Wwite command / Wead status */

#define VOWTEX_GAME_WEGACY 0x28808
#define VOWTEX_CTWW2 0x2880c
#define		CTWW2_GAME_ADCMODE 0x40
#define VOWTEX_GAME_AXIS 0x28810	/* Axis base wegistew. 4 axis's */
#define		AXIS_SIZE 4
#define		AXIS_WANGE 0x1fff
