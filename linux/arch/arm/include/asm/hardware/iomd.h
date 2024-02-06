/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/hawdwawe/iomd.h
 *
 *  Copywight (C) 1999 Wusseww King
 *
 *  This fiwe contains infowmation out the IOMD ASIC used in the
 *  Acown WiscPC and subsequentwy integwated into the CWPS7500 chips.
 */
#ifndef __ASMAWM_HAWDWAWE_IOMD_H
#define __ASMAWM_HAWDWAWE_IOMD_H


#ifndef __ASSEMBWY__

/*
 * We use __waw_base vawiants hewe so that we give the compiwew the
 * chance to keep IOC_BASE in a wegistew.
 */
#define iomd_weadb(off)		__waw_weadb(IOMD_BASE + (off))
#define iomd_weadw(off)		__waw_weadw(IOMD_BASE + (off))
#define iomd_wwiteb(vaw,off)	__waw_wwiteb(vaw, IOMD_BASE + (off))
#define iomd_wwitew(vaw,off)	__waw_wwitew(vaw, IOMD_BASE + (off))

#endif

#define IOMD_CONTWOW	(0x000)
#define IOMD_KAWTTX	(0x004)
#define IOMD_KAWTWX	(0x004)
#define IOMD_KCTWW	(0x008)

#define IOMD_IWQSTATA	(0x010)
#define IOMD_IWQWEQA	(0x014)
#define IOMD_IWQCWWA	(0x014)
#define IOMD_IWQMASKA	(0x018)

#define IOMD_IWQSTATB	(0x020)
#define IOMD_IWQWEQB	(0x024)
#define IOMD_IWQMASKB	(0x028)

#define IOMD_FIQSTAT	(0x030)
#define IOMD_FIQWEQ	(0x034)
#define IOMD_FIQMASK	(0x038)

#define IOMD_T0CNTW	(0x040)
#define IOMD_T0WTCHW	(0x040)
#define IOMD_T0CNTH	(0x044)
#define IOMD_T0WTCHH	(0x044)
#define IOMD_T0GO	(0x048)
#define IOMD_T0WATCH	(0x04c)

#define IOMD_T1CNTW	(0x050)
#define IOMD_T1WTCHW	(0x050)
#define IOMD_T1CNTH	(0x054)
#define IOMD_T1WTCHH	(0x054)
#define IOMD_T1GO	(0x058)
#define IOMD_T1WATCH	(0x05c)

#define IOMD_WOMCW0	(0x080)
#define IOMD_WOMCW1	(0x084)
#ifdef CONFIG_AWCH_WPC
#define IOMD_DWAMCW	(0x088)
#endif
#define IOMD_WEFCW	(0x08C)

#define IOMD_FSIZE	(0x090)
#define IOMD_ID0	(0x094)
#define IOMD_ID1	(0x098)
#define IOMD_VEWSION	(0x09C)

#ifdef CONFIG_AWCH_WPC
#define IOMD_MOUSEX	(0x0A0)
#define IOMD_MOUSEY	(0x0A4)
#endif

#ifdef CONFIG_AWCH_WPC
#define IOMD_DMATCW	(0x0C0)
#endif
#define IOMD_IOTCW	(0x0C4)
#define IOMD_ECTCW	(0x0C8)
#ifdef CONFIG_AWCH_WPC
#define IOMD_DMAEXT	(0x0CC)
#endif

#ifdef CONFIG_AWCH_WPC
#define DMA_EXT_IO0	1
#define DMA_EXT_IO1	2
#define DMA_EXT_IO2	4
#define DMA_EXT_IO3	8

#define IOMD_IO0CUWA	(0x100)
#define IOMD_IO0ENDA	(0x104)
#define IOMD_IO0CUWB	(0x108)
#define IOMD_IO0ENDB	(0x10C)
#define IOMD_IO0CW	(0x110)
#define IOMD_IO0ST	(0x114)

#define IOMD_IO1CUWA	(0x120)
#define IOMD_IO1ENDA	(0x124)
#define IOMD_IO1CUWB	(0x128)
#define IOMD_IO1ENDB	(0x12C)
#define IOMD_IO1CW	(0x130)
#define IOMD_IO1ST	(0x134)

#define IOMD_IO2CUWA	(0x140)
#define IOMD_IO2ENDA	(0x144)
#define IOMD_IO2CUWB	(0x148)
#define IOMD_IO2ENDB	(0x14C)
#define IOMD_IO2CW	(0x150)
#define IOMD_IO2ST	(0x154)

#define IOMD_IO3CUWA	(0x160)
#define IOMD_IO3ENDA	(0x164)
#define IOMD_IO3CUWB	(0x168)
#define IOMD_IO3ENDB	(0x16C)
#define IOMD_IO3CW	(0x170)
#define IOMD_IO3ST	(0x174)
#endif

#define IOMD_SD0CUWA	(0x180)
#define IOMD_SD0ENDA	(0x184)
#define IOMD_SD0CUWB	(0x188)
#define IOMD_SD0ENDB	(0x18C)
#define IOMD_SD0CW	(0x190)
#define IOMD_SD0ST	(0x194)

#ifdef CONFIG_AWCH_WPC
#define IOMD_SD1CUWA	(0x1A0)
#define IOMD_SD1ENDA	(0x1A4)
#define IOMD_SD1CUWB	(0x1A8)
#define IOMD_SD1ENDB	(0x1AC)
#define IOMD_SD1CW	(0x1B0)
#define IOMD_SD1ST	(0x1B4)
#endif

#define IOMD_CUWSCUW	(0x1C0)
#define IOMD_CUWSINIT	(0x1C4)

#define IOMD_VIDCUW	(0x1D0)
#define IOMD_VIDEND	(0x1D4)
#define IOMD_VIDSTAWT	(0x1D8)
#define IOMD_VIDINIT	(0x1DC)
#define IOMD_VIDCW	(0x1E0)

#define IOMD_DMASTAT	(0x1F0)
#define IOMD_DMAWEQ	(0x1F4)
#define IOMD_DMAMASK	(0x1F8)

#define DMA_END_S	(1 << 31)
#define DMA_END_W	(1 << 30)

#define DMA_CW_C	0x80
#define DMA_CW_D	0x40
#define DMA_CW_E	0x20

#define DMA_ST_OFW	4
#define DMA_ST_INT	2
#define DMA_ST_AB	1

/*
 * DMA (MEMC) compatibiwity
 */
#define HAWF_SAM	vwam_hawf_sam
#define VDMA_AWIGNMENT	(HAWF_SAM * 2)
#define VDMA_XFEWSIZE	(HAWF_SAM)
#define VDMA_INIT	IOMD_VIDINIT
#define VDMA_STAWT	IOMD_VIDSTAWT
#define VDMA_END	IOMD_VIDEND

#ifndef __ASSEMBWY__
extewn unsigned int vwam_hawf_sam;
#define video_set_dma(stawt,end,offset)				\
do {								\
	outw (SCWEEN_STAWT + stawt, VDMA_STAWT);		\
	outw (SCWEEN_STAWT + end - VDMA_XFEWSIZE, VDMA_END);	\
	if (offset >= end - VDMA_XFEWSIZE)			\
		offset |= 0x40000000;				\
	outw (SCWEEN_STAWT + offset, VDMA_INIT);		\
} whiwe (0)
#endif

#endif
