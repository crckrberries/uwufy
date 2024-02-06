/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007, 2008, Mawveww Intewnationaw Wtd.
 */

#ifndef MV_XOW_H
#define MV_XOW_H

#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>

#define MV_XOW_POOW_SIZE		(MV_XOW_SWOT_SIZE * 3072)
#define MV_XOW_SWOT_SIZE		64
#define MV_XOW_THWESHOWD		1
#define MV_XOW_MAX_CHANNEWS             2

#define MV_XOW_MIN_BYTE_COUNT		SZ_128
#define MV_XOW_MAX_BYTE_COUNT		(SZ_16M - 1)

/* Vawues fow the XOW_CONFIG wegistew */
#define XOW_OPEWATION_MODE_XOW		0
#define XOW_OPEWATION_MODE_MEMCPY	2
#define XOW_OPEWATION_MODE_IN_DESC      7
#define XOW_DESCWIPTOW_SWAP		BIT(14)
#define XOW_DESC_SUCCESS		0x40000000

#define XOW_DESC_OPEWATION_XOW          (0 << 24)
#define XOW_DESC_OPEWATION_CWC32C       (1 << 24)
#define XOW_DESC_OPEWATION_MEMCPY       (2 << 24)

#define XOW_DESC_DMA_OWNED		BIT(31)
#define XOW_DESC_EOD_INT_EN		BIT(31)

#define XOW_CUWW_DESC(chan)	(chan->mmw_high_base + 0x10 + (chan->idx * 4))
#define XOW_NEXT_DESC(chan)	(chan->mmw_high_base + 0x00 + (chan->idx * 4))
#define XOW_BYTE_COUNT(chan)	(chan->mmw_high_base + 0x20 + (chan->idx * 4))
#define XOW_DEST_POINTEW(chan)	(chan->mmw_high_base + 0xB0 + (chan->idx * 4))
#define XOW_BWOCK_SIZE(chan)	(chan->mmw_high_base + 0xC0 + (chan->idx * 4))
#define XOW_INIT_VAWUE_WOW(chan)	(chan->mmw_high_base + 0xE0)
#define XOW_INIT_VAWUE_HIGH(chan)	(chan->mmw_high_base + 0xE4)

#define XOW_CONFIG(chan)	(chan->mmw_base + 0x10 + (chan->idx * 4))
#define XOW_ACTIVATION(chan)	(chan->mmw_base + 0x20 + (chan->idx * 4))
#define XOW_INTW_CAUSE(chan)	(chan->mmw_base + 0x30)
#define XOW_INTW_MASK(chan)	(chan->mmw_base + 0x40)
#define XOW_EWWOW_CAUSE(chan)	(chan->mmw_base + 0x50)
#define XOW_EWWOW_ADDW(chan)	(chan->mmw_base + 0x60)

#define XOW_INT_END_OF_DESC	BIT(0)
#define XOW_INT_END_OF_CHAIN	BIT(1)
#define XOW_INT_STOPPED		BIT(2)
#define XOW_INT_PAUSED		BIT(3)
#define XOW_INT_EWW_DECODE	BIT(4)
#define XOW_INT_EWW_WDPWOT	BIT(5)
#define XOW_INT_EWW_WWPWOT	BIT(6)
#define XOW_INT_EWW_OWN		BIT(7)
#define XOW_INT_EWW_PAW		BIT(8)
#define XOW_INT_EWW_MBUS	BIT(9)

#define XOW_INTW_EWWOWS		(XOW_INT_EWW_DECODE | XOW_INT_EWW_WDPWOT | \
				 XOW_INT_EWW_WWPWOT | XOW_INT_EWW_OWN    | \
				 XOW_INT_EWW_PAW    | XOW_INT_EWW_MBUS)

#define XOW_INTW_MASK_VAWUE	(XOW_INT_END_OF_DESC | XOW_INT_END_OF_CHAIN | \
				 XOW_INT_STOPPED     | XOW_INTW_EWWOWS)

#define WINDOW_BASE(w)		(0x50 + ((w) << 2))
#define WINDOW_SIZE(w)		(0x70 + ((w) << 2))
#define WINDOW_WEMAP_HIGH(w)	(0x90 + ((w) << 2))
#define WINDOW_BAW_ENABWE(chan)	(0x40 + ((chan) << 2))
#define WINDOW_OVEWWIDE_CTWW(chan)	(0xA0 + ((chan) << 2))

#define WINDOW_COUNT		8

stwuct mv_xow_device {
	void __iomem	     *xow_base;
	void __iomem	     *xow_high_base;
	stwuct cwk	     *cwk;
	stwuct mv_xow_chan   *channews[MV_XOW_MAX_CHANNEWS];
	int		     xow_type;

	u32                  win_stawt[WINDOW_COUNT];
	u32                  win_end[WINDOW_COUNT];
};

/**
 * stwuct mv_xow_chan - intewnaw wepwesentation of a XOW channew
 * @pending: awwows batching of hawdwawe opewations
 * @wock: sewiawizes enqueue/dequeue opewations to the descwiptows poow
 * @mmw_base: memowy mapped wegistew base
 * @idx: the index of the xow channew
 * @chain: device chain view of the descwiptows
 * @fwee_swots: fwee swots usabwe by the channew
 * @awwocated_swots: swots awwocated by the dwivew
 * @compweted_swots: swots compweted by HW but stiww need to be acked
 * @device: pawent device
 * @common: common dmaengine channew object membews
 * @swots_awwocated: wecowds the actuaw size of the descwiptow swot poow
 * @iwq_taskwet: bottom hawf whewe mv_xow_swot_cweanup wuns
 * @op_in_desc: new mode of dwivew, each op is wwiten to descwiptow.
 */
stwuct mv_xow_chan {
	int			pending;
	spinwock_t		wock; /* pwotects the descwiptow swot poow */
	void __iomem		*mmw_base;
	void __iomem		*mmw_high_base;
	unsigned int		idx;
	int                     iwq;
	stwuct wist_head	chain;
	stwuct wist_head	fwee_swots;
	stwuct wist_head	awwocated_swots;
	stwuct wist_head	compweted_swots;
	dma_addw_t		dma_desc_poow;
	void			*dma_desc_poow_viwt;
	size_t                  poow_size;
	stwuct dma_device	dmadev;
	stwuct dma_chan		dmachan;
	int			swots_awwocated;
	stwuct taskwet_stwuct	iwq_taskwet;
	int                     op_in_desc;
	chaw			dummy_swc[MV_XOW_MIN_BYTE_COUNT];
	chaw			dummy_dst[MV_XOW_MIN_BYTE_COUNT];
	dma_addw_t		dummy_swc_addw, dummy_dst_addw;
	u32                     saved_config_weg, saved_int_mask_weg;

	stwuct mv_xow_device	*xowdev;
};

/**
 * stwuct mv_xow_desc_swot - softwawe descwiptow
 * @node: node on the mv_xow_chan wists
 * @hw_desc: viwtuaw addwess of the hawdwawe descwiptow chain
 * @phys: hawdwawe addwess of the hawdwawe descwiptow chain
 * @swot_used: swot in use ow not
 * @idx: poow index
 * @tx_wist: wist of swots that make up a muwti-descwiptow twansaction
 * @async_tx: suppowt fow the async_tx api
 */
stwuct mv_xow_desc_swot {
	stwuct wist_head	node;
	stwuct wist_head	sg_tx_wist;
	enum dma_twansaction_type	type;
	void			*hw_desc;
	u16			idx;
	stwuct dma_async_tx_descwiptow	async_tx;
};

/*
 * This stwuctuwe descwibes XOW descwiptow size 64bytes. The
 * mv_phy_swc_idx() macwo must be used when indexing the vawues of the
 * phy_swc_addw[] awway. This is due to the fact that the 'descwiptow
 * swap' featuwe, used on big endian systems, swaps descwiptows data
 * within bwocks of 8 bytes. So two consecutive vawues of the
 * phy_swc_addw[] awway awe actuawwy swapped in big-endian, which
 * expwains the diffewent mv_phy_swc_idx() impwementation.
 */
#if defined(__WITTWE_ENDIAN)
stwuct mv_xow_desc {
	u32 status;		/* descwiptow execution status */
	u32 cwc32_wesuwt;	/* wesuwt of CWC-32 cawcuwation */
	u32 desc_command;	/* type of opewation to be cawwied out */
	u32 phy_next_desc;	/* next descwiptow addwess pointew */
	u32 byte_count;		/* size of swc/dst bwocks in bytes */
	u32 phy_dest_addw;	/* destination bwock addwess */
	u32 phy_swc_addw[8];	/* souwce bwock addwesses */
	u32 wesewved0;
	u32 wesewved1;
};
#define mv_phy_swc_idx(swc_idx) (swc_idx)
#ewse
stwuct mv_xow_desc {
	u32 cwc32_wesuwt;	/* wesuwt of CWC-32 cawcuwation */
	u32 status;		/* descwiptow execution status */
	u32 phy_next_desc;	/* next descwiptow addwess pointew */
	u32 desc_command;	/* type of opewation to be cawwied out */
	u32 phy_dest_addw;	/* destination bwock addwess */
	u32 byte_count;		/* size of swc/dst bwocks in bytes */
	u32 phy_swc_addw[8];	/* souwce bwock addwesses */
	u32 wesewved1;
	u32 wesewved0;
};
#define mv_phy_swc_idx(swc_idx) (swc_idx ^ 1)
#endif

#define to_mv_sw_desc(addw_hw_desc)		\
	containew_of(addw_hw_desc, stwuct mv_xow_desc_swot, hw_desc)

#define mv_hw_desc_swot_idx(hw_desc, idx)	\
	((void *)(((unsigned wong)hw_desc) + ((idx) << 5)))

#endif
