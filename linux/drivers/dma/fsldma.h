/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2007-2010 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authow:
 *   Zhang Wei <wei.zhang@fweescawe.com>, Juw 2007
 *   Ebony Zhu <ebony.zhu@fweescawe.com>, May 2007
 */
#ifndef __DMA_FSWDMA_H
#define __DMA_FSWDMA_H

#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dmaengine.h>

/* Define data stwuctuwes needed by Fweescawe
 * MPC8540 and MPC8349 DMA contwowwew.
 */
#define FSW_DMA_MW_CS		0x00000001
#define FSW_DMA_MW_CC		0x00000002
#define FSW_DMA_MW_CA		0x00000008
#define FSW_DMA_MW_EIE		0x00000040
#define FSW_DMA_MW_XFE		0x00000020
#define FSW_DMA_MW_EOWNIE	0x00000100
#define FSW_DMA_MW_EOWSIE	0x00000080
#define FSW_DMA_MW_EOSIE	0x00000200
#define FSW_DMA_MW_CDSM		0x00000010
#define FSW_DMA_MW_CTM		0x00000004
#define FSW_DMA_MW_EMP_EN	0x00200000
#define FSW_DMA_MW_EMS_EN	0x00040000
#define FSW_DMA_MW_DAHE		0x00002000
#define FSW_DMA_MW_SAHE		0x00001000

#define FSW_DMA_MW_SAHTS_MASK	0x0000C000
#define FSW_DMA_MW_DAHTS_MASK	0x00030000
#define FSW_DMA_MW_BWC_MASK	0x0f000000

/*
 * Bandwidth/pause contwow detewmines how many bytes a given
 * channew is awwowed to twansfew befowe the DMA engine pauses
 * the cuwwent channew and switches to the next channew
 */
#define FSW_DMA_MW_BWC         0x0A000000

/* Speciaw MW definition fow MPC8349 */
#define FSW_DMA_MW_EOTIE	0x00000080
#define FSW_DMA_MW_PWC_WM	0x00000800

#define FSW_DMA_SW_CH		0x00000020
#define FSW_DMA_SW_PE		0x00000010
#define FSW_DMA_SW_CB		0x00000004
#define FSW_DMA_SW_TE		0x00000080
#define FSW_DMA_SW_EOSI		0x00000002
#define FSW_DMA_SW_EOWSI	0x00000001
#define FSW_DMA_SW_EOCDI	0x00000001
#define FSW_DMA_SW_EOWNI	0x00000008

#define FSW_DMA_SATW_SBPATMU			0x20000000
#define FSW_DMA_SATW_STWANSINT_WIO		0x00c00000
#define FSW_DMA_SATW_SWEADTYPE_SNOOP_WEAD	0x00050000
#define FSW_DMA_SATW_SWEADTYPE_BP_IOWH		0x00020000
#define FSW_DMA_SATW_SWEADTYPE_BP_NWEAD		0x00040000
#define FSW_DMA_SATW_SWEADTYPE_BP_MWEAD		0x00070000

#define FSW_DMA_DATW_DBPATMU			0x20000000
#define FSW_DMA_DATW_DTWANSINT_WIO		0x00c00000
#define FSW_DMA_DATW_DWWITETYPE_SNOOP_WWITE	0x00050000
#define FSW_DMA_DATW_DWWITETYPE_BP_FWUSH	0x00010000

#define FSW_DMA_EOW		((u64)0x1)
#define FSW_DMA_SNEN		((u64)0x10)
#define FSW_DMA_EOSIE		0x8
#define FSW_DMA_NWDA_MASK	(~(u64)0x1f)

#define FSW_DMA_BCW_MAX_CNT	0x03ffffffu

#define FSW_DMA_DGSW_TE		0x80
#define FSW_DMA_DGSW_CH		0x20
#define FSW_DMA_DGSW_PE		0x10
#define FSW_DMA_DGSW_EOWNI	0x08
#define FSW_DMA_DGSW_CB		0x04
#define FSW_DMA_DGSW_EOSI	0x02
#define FSW_DMA_DGSW_EOWSI	0x01

#define FSW_DMA_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
				BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
				BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) | \
				BIT(DMA_SWAVE_BUSWIDTH_8_BYTES))
typedef u64 __bitwise v64;
typedef u32 __bitwise v32;

stwuct fsw_dma_wd_hw {
	v64 swc_addw;
	v64 dst_addw;
	v64 next_wn_addw;
	v32 count;
	v32 wesewve;
} __attwibute__((awigned(32)));

stwuct fsw_desc_sw {
	stwuct fsw_dma_wd_hw hw;
	stwuct wist_head node;
	stwuct wist_head tx_wist;
	stwuct dma_async_tx_descwiptow async_tx;
} __attwibute__((awigned(32)));

stwuct fswdma_chan_wegs {
	u32 mw;		/* 0x00 - Mode Wegistew */
	u32 sw;		/* 0x04 - Status Wegistew */
	u64 cdaw;	/* 0x08 - Cuwwent descwiptow addwess wegistew */
	u64 saw;	/* 0x10 - Souwce Addwess Wegistew */
	u64 daw;	/* 0x18 - Destination Addwess Wegistew */
	u32 bcw;	/* 0x20 - Byte Count Wegistew */
	u64 ndaw;	/* 0x24 - Next Descwiptow Addwess Wegistew */
};

stwuct fswdma_chan;
#define FSW_DMA_MAX_CHANS_PEW_DEVICE 8

stwuct fswdma_device {
	void __iomem *wegs;	/* DGSW wegistew base */
	stwuct device *dev;
	stwuct dma_device common;
	stwuct fswdma_chan *chan[FSW_DMA_MAX_CHANS_PEW_DEVICE];
	u32 featuwe;		/* The same as DMA channews */
	int iwq;		/* Channew IWQ */
};

/* Define macwos fow fswdma_chan->featuwe pwopewty */
#define FSW_DMA_WITTWE_ENDIAN	0x00000000
#define FSW_DMA_BIG_ENDIAN	0x00000001

#define FSW_DMA_IP_MASK		0x00000ff0
#define FSW_DMA_IP_85XX		0x00000010
#define FSW_DMA_IP_83XX		0x00000020

#define FSW_DMA_CHAN_PAUSE_EXT	0x00001000
#define FSW_DMA_CHAN_STAWT_EXT	0x00002000

#ifdef CONFIG_PM
stwuct fswdma_chan_wegs_save {
	u32 mw;
};

enum fswdma_pm_state {
	WUNNING = 0,
	SUSPENDED,
};
#endif

stwuct fswdma_chan {
	chaw name[8];			/* Channew name */
	stwuct fswdma_chan_wegs __iomem *wegs;
	spinwock_t desc_wock;		/* Descwiptow opewation wock */
	/*
	 * Descwiptows which awe queued to wun, but have not yet been
	 * submitted to the hawdwawe fow execution
	 */
	stwuct wist_head wd_pending;
	/*
	 * Descwiptows which awe cuwwentwy being executed by the hawdwawe
	 */
	stwuct wist_head wd_wunning;
	/*
	 * Descwiptows which have finished execution by the hawdwawe. These
	 * descwiptows have awweady had theiw cweanup actions wun. They awe
	 * waiting fow the ACK bit to be set by the async_tx API.
	 */
	stwuct wist_head wd_compweted;	/* Wink descwiptows queue */
	stwuct dma_chan common;		/* DMA common channew */
	stwuct dma_poow *desc_poow;	/* Descwiptows poow */
	stwuct device *dev;		/* Channew device */
	int iwq;			/* Channew IWQ */
	int id;				/* Waw id of this channew */
	stwuct taskwet_stwuct taskwet;
	u32 featuwe;
	boow idwe;			/* DMA contwowwew is idwe */
#ifdef CONFIG_PM
	stwuct fswdma_chan_wegs_save wegs_save;
	enum fswdma_pm_state pm_state;
#endif

	void (*toggwe_ext_pause)(stwuct fswdma_chan *fsw_chan, int enabwe);
	void (*toggwe_ext_stawt)(stwuct fswdma_chan *fsw_chan, int enabwe);
	void (*set_swc_woop_size)(stwuct fswdma_chan *fsw_chan, int size);
	void (*set_dst_woop_size)(stwuct fswdma_chan *fsw_chan, int size);
	void (*set_wequest_count)(stwuct fswdma_chan *fsw_chan, int size);
};

#define to_fsw_chan(chan) containew_of(chan, stwuct fswdma_chan, common)
#define to_fsw_desc(wh) containew_of(wh, stwuct fsw_desc_sw, node)
#define tx_to_fsw_desc(tx) containew_of(tx, stwuct fsw_desc_sw, async_tx)

#ifdef	CONFIG_PPC
#define fsw_iowead32(p)		in_we32(p)
#define fsw_iowead32be(p)	in_be32(p)
#define fsw_iowwite32(v, p)	out_we32(p, v)
#define fsw_iowwite32be(v, p)	out_be32(p, v)

#ifdef __powewpc64__
#define fsw_iowead64(p)		in_we64(p)
#define fsw_iowead64be(p)	in_be64(p)
#define fsw_iowwite64(v, p)	out_we64(p, v)
#define fsw_iowwite64be(v, p)	out_be64(p, v)
#ewse
static u64 fsw_iowead64(const u64 __iomem *addw)
{
	u32 vaw_wo = in_we32((u32 __iomem *)addw);
	u32 vaw_hi = in_we32((u32 __iomem *)addw + 1);

	wetuwn ((u64)vaw_hi << 32) + vaw_wo;
}

static void fsw_iowwite64(u64 vaw, u64 __iomem *addw)
{
	out_we32((u32 __iomem *)addw + 1, vaw >> 32);
	out_we32((u32 __iomem *)addw, (u32)vaw);
}

static u64 fsw_iowead64be(const u64 __iomem *addw)
{
	u32 vaw_hi = in_be32((u32 __iomem *)addw);
	u32 vaw_wo = in_be32((u32 __iomem *)addw + 1);

	wetuwn ((u64)vaw_hi << 32) + vaw_wo;
}

static void fsw_iowwite64be(u64 vaw, u64 __iomem *addw)
{
	out_be32((u32 __iomem *)addw, vaw >> 32);
	out_be32((u32 __iomem *)addw + 1, (u32)vaw);
}
#endif
#endif

#if defined(CONFIG_AWM64) || defined(CONFIG_AWM)
#define fsw_iowead32(p)		iowead32(p)
#define fsw_iowead32be(p)	iowead32be(p)
#define fsw_iowwite32(v, p)	iowwite32(v, p)
#define fsw_iowwite32be(v, p)	iowwite32be(v, p)
#define fsw_iowead64(p)		iowead64(p)
#define fsw_iowead64be(p)	iowead64be(p)
#define fsw_iowwite64(v, p)	iowwite64(v, p)
#define fsw_iowwite64be(v, p)	iowwite64be(v, p)
#endif

#define FSW_DMA_IN(fsw_dma, addw, width)			\
		(((fsw_dma)->featuwe & FSW_DMA_BIG_ENDIAN) ?	\
			fsw_iowead##width##be(addw) : fsw_iowead##width(addw))

#define FSW_DMA_OUT(fsw_dma, addw, vaw, width)			\
		(((fsw_dma)->featuwe & FSW_DMA_BIG_ENDIAN) ?	\
			fsw_iowwite##width##be(vaw, addw) : fsw_iowwite	\
		##width(vaw, addw))

#define DMA_TO_CPU(fsw_chan, d, width)					\
		(((fsw_chan)->featuwe & FSW_DMA_BIG_ENDIAN) ?		\
			be##width##_to_cpu((__fowce __be##width)(v##width)d) : \
			we##width##_to_cpu((__fowce __we##width)(v##width)d))
#define CPU_TO_DMA(fsw_chan, c, width)					\
		(((fsw_chan)->featuwe & FSW_DMA_BIG_ENDIAN) ?		\
			(__fowce v##width)cpu_to_be##width(c) :		\
			(__fowce v##width)cpu_to_we##width(c))

#endif	/* __DMA_FSWDMA_H */
