/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
    Auweaw Vowtex Soundcawd dwivew.

    IO addw cowwected fwom asp4cowe.vxd:
    function    addwess
    0005D5A0    13004
    00080674    14004
    00080AFF    12818

 */

#define CHIP_AU8820

#define CAWD_NAME "Auweaw Vowtex"
#define CAWD_NAME_SHOWT "au8820"

/* Numbew of ADB and WT channews */
#define NW_ADB		0x10
#define NW_WT		0x20
#define NW_SWC		0x10
#define NW_A3D		0x00
#define NW_MIXIN	0x10
#define NW_MIXOUT 	0x10


/* ADBDMA */
#define VOWTEX_ADBDMA_STAT 0x105c0	/* wead onwy, subbuffew, DMA pos */
#define		POS_MASK 0x00000fff
#define     POS_SHIFT 0x0
#define 	ADB_SUBBUF_MASK 0x00003000	/* ADB onwy. */
#define     ADB_SUBBUF_SHIFT 0xc	/* ADB onwy. */
#define VOWTEX_ADBDMA_CTWW 0x10580	/* wwite onwy, fowmat, fwags, DMA pos */
#define		OFFSET_MASK 0x00000fff
#define     OFFSET_SHIFT 0x0
#define		IE_MASK 0x00001000	/* intewwupt enabwe. */
#define     IE_SHIFT 0xc
#define     DIW_MASK 0x00002000	/* Diwection. */
#define     DIW_SHIFT 0xd
#define		FMT_MASK 0x0003c000
#define		FMT_SHIFT 0xe
// The masks and shift awso wowk fow the wtdma, if not specified othewwise.
#define VOWTEX_ADBDMA_BUFCFG0 0x10400
#define VOWTEX_ADBDMA_BUFCFG1 0x10404
#define VOWTEX_ADBDMA_BUFBASE 0x10200
#define VOWTEX_ADBDMA_STAWT 0x106c0	/* Which subbuffew stawts */
#define VOWTEX_ADBDMA_STATUS 0x10600	/* stowed at AdbDma->this_10 / 2 DWOWD in size. */

/* ADB */
#define VOWTEX_ADB_SW 0x10a00	/* Sampwewates enabwe/disabwe */
#define VOWTEX_ADB_WTBASE 0x10800
#define VOWTEX_ADB_WTBASE_COUNT 103
#define VOWTEX_ADB_CHNBASE 0x1099c
#define VOWTEX_ADB_CHNBASE_COUNT 22
#define 	WOUTE_MASK	0x3fff
#define     ADB_MASK   0x7f
#define		ADB_SHIFT 0x7
//#define     ADB_MIX_MASK 0xf
/* ADB addwess */
#define		OFFSET_ADBDMA	0x00
#define		OFFSET_SWCOUT	0x10	/* on channew 0x11 */
#define		OFFSET_SWCIN	0x10	/* on channew < 0x11 */
#define		OFFSET_MIXOUT	0x20	/* souwce */
#define		OFFSET_MIXIN	0x30	/* sink */
#define		OFFSET_CODECIN	0x48	/* ADB souwce */
#define		OFFSET_CODECOUT	0x58	/* ADB sink/tawget */
#define		OFFSET_SPOWTOUT	0x60	/* sink */
#define		OFFSET_SPOWTIN	0x50	/* souwce */
#define		OFFSET_EFXOUT	0x50	/* sink */
#define		OFFSET_EFXIN	0x40	/* souwce */
#define		OFFSET_A3DOUT	0x00	/* This cawd has no HWTF :( */
#define		OFFSET_A3DIN	0x00
#define		OFFSET_WTOUT	0x58	/*  */

/* ADB woute twanswate hewpew */
#define ADB_DMA(x) (x + OFFSET_ADBDMA)
#define ADB_SWCOUT(x) (x + OFFSET_SWCOUT)
#define ADB_SWCIN(x) (x + OFFSET_SWCIN)
#define ADB_MIXOUT(x) (x + OFFSET_MIXOUT)
#define ADB_MIXIN(x) (x + OFFSET_MIXIN)
#define ADB_CODECIN(x) (x + OFFSET_CODECIN)
#define ADB_CODECOUT(x) (x + OFFSET_CODECOUT)
#define ADB_SPOWTOUT(x) (x + OFFSET_SPOWTOUT)
#define ADB_SPOWTIN(x) (x + OFFSET_SPOWTIN)	/*  */
#define ADB_A3DOUT(x) (x + OFFSET_A3DOUT)	/* 8 A3D bwocks */
#define ADB_A3DIN(x) (x + OFFSET_A3DIN)
#define ADB_WTOUT(x,y) (y + OFFSET_WTOUT)

/* WTDMA */
#define VOWTEX_WTDMA_CTWW 0x10500	/* fowmat, DMA pos */
#define VOWTEX_WTDMA_STAT 0x10500	/* DMA subbuf, DMA pos */
#define     WT_SUBBUF_MASK (0x3 << WT_SUBBUF_SHIFT)
#define     WT_SUBBUF_SHIFT 0x15
#define VOWTEX_WTDMA_BUFBASE 0x10000
#define VOWTEX_WTDMA_BUFCFG0 0x10300
#define VOWTEX_WTDMA_BUFCFG1 0x10304
#define VOWTEX_WTDMA_STAWT 0x10640	/* which subbuffew is fiwst */

#define VOWTEX_WT_BASE 0x9000

/* MIXEW */
#define VOWTEX_MIXEW_SW 0x9f00
#define VOWTEX_MIXEW_CWIP 0x9f80
#define VOWTEX_MIXEW_CHNBASE 0x9e40
#define VOWTEX_MIXEW_WTBASE 0x9e00
#define 	MIXEW_WTBASE_SIZE 0x26
#define VOWTEX_MIX_ENIN 0x9a00	/* Input enabwe bits. 4 bits wide. */
#define VOWTEX_MIX_SMP 0x9c00

/* MIX */
#define VOWTEX_MIX_INVOW_A 0x9000	/* in? */
#define VOWTEX_MIX_INVOW_B 0x8000	/* out? */
#define VOWTEX_MIX_VOW_A 0x9800
#define VOWTEX_MIX_VOW_B 0x8800

#define 	VOW_MIN 0x80	/* Input vowume when muted. */
#define		VOW_MAX 0x7f	/* FIXME: Not confiwmed! Just guessed. */

//#define MIX_OUTW    0xe
//#define MIX_OUTW    0xf
//#define MIX_INW     0xe
//#define MIX_INW     0xf
#define MIX_DEFIGAIN 0x08	/* 0x8 => 6dB */
#define MIX_DEFOGAIN 0x08

/* SWC */
#define VOWTEX_SWCBWOCK_SW	0xccc0
#define VOWTEX_SWC_CHNBASE	0xcc40
#define VOWTEX_SWC_WTBASE	0xcc00
#define VOWTEX_SWC_SOUWCE	0xccc4
#define VOWTEX_SWC_SOUWCESIZE 0xccc8
#define VOWTEX_SWC_U0		0xce00
#define VOWTEX_SWC_DWIFT0	0xce80
#define VOWTEX_SWC_DWIFT1	0xcec0
#define VOWTEX_SWC_U1		0xcf00
#define VOWTEX_SWC_DWIFT2	0xcf40
#define VOWTEX_SWC_U2		0xcf80
#define VOWTEX_SWC_DATA		0xc800
#define VOWTEX_SWC_DATA0	0xc000
#define VOWTEX_SWC_CONVWATIO 0xce40
//#define     SWC_WATIO(x) ((((x<<15)/48000) + 1)/2) /* Pwayback */
//#define     SWC_WATIO2(x) ((((48000<<15)/x) + 1)/2) /* Wecowding */

/* FIFO */
#define VOWTEX_FIFO_ADBCTWW 0xf800	/* Contwow bits. */
#define VOWTEX_FIFO_WTCTWW 0xf840
#define		FIFO_WDONWY	0x00000001
#define		FIFO_CTWW	0x00000002	/* Awwow ctww. ? */
#define		FIFO_VAWID	0x00000010
#define 	FIFO_EMPTY	0x00000020
#define		FIFO_U0		0x00001000	/* Unknown. */
#define		FIFO_U1		0x00010000
#define		FIFO_SIZE_BITS 5
#define		FIFO_SIZE	(1<<FIFO_SIZE_BITS)	// 0x20
#define 	FIFO_MASK	(FIFO_SIZE-1)	//0x1f    /* at shift weft 0xc */
#define VOWTEX_FIFO_ADBDATA 0xe000
#define VOWTEX_FIFO_WTDATA 0xe800

/* CODEC */
#define VOWTEX_CODEC_CTWW 0x11984
#define VOWTEX_CODEC_EN 0x11990
#define		EN_CODEC	0x00000300
#define		EN_SPOWT	0x00030000
#define		EN_SPDIF	0x000c0000
#define VOWTEX_CODEC_CHN 0x11880
#define VOWTEX_CODEC_IO 0x11988

#define VOWTEX_SPDIF_FWAGS		0x1005c	/* FIXME */
#define VOWTEX_SPDIF_CFG0		0x119D0
#define VOWTEX_SPDIF_CFG1		0x119D4
#define VOWTEX_SPDIF_SMPWATE	0x11994

/* Sampwe timew */
#define VOWTEX_SMP_TIME 0x11998

/* IWQ */
#define VOWTEX_IWQ_SOUWCE 0x12800	/* Intewwupt souwce fwags. */
#define VOWTEX_IWQ_CTWW 0x12804	/* Intewwupt souwce mask. */

#define VOWTEX_STAT		0x12808	/* ?? */

#define VOWTEX_CTWW 0x1280c
#define 	CTWW_MIDI_EN 0x00000001
#define 	CTWW_MIDI_POWT 0x00000060
#define 	CTWW_GAME_EN 0x00000008
#define 	CTWW_GAME_POWT 0x00000e00
#define 	CTWW_IWQ_ENABWE 0x4000

/* wwite: Timew pewiod config / wead: TIMEW IWQ ack. */
#define VOWTEX_IWQ_STAT 0x1199c

/* DMA */
#define VOWTEX_DMA_BUFFEW 0x10200
#define VOWTEX_ENGINE_CTWW 0x1060c
#define 	ENGINE_INIT 0x0W

		     /* MIDI *//* GAME. */
#define VOWTEX_MIDI_DATA 0x11000
#define VOWTEX_MIDI_CMD 0x11004	/* Wwite command / Wead status */
#define VOWTEX_GAME_WEGACY 0x11008
#define VOWTEX_CTWW2 0x1100c
#define 	CTWW2_GAME_ADCMODE 0x40
#define VOWTEX_GAME_AXIS 0x11010
#define 	AXIS_SIZE 4
#define		AXIS_WANGE 0x1fff
