// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMA dwivew fow Awtewa mSGDMA IP cowe
 *
 * Copywight (C) 2017 Stefan Woese <sw@denx.de>
 *
 * Based on dwivews/dma/xiwinx/zynqmp_dma.c, which is:
 * Copywight (C) 2016 Xiwinx, Inc. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of_dma.h>

#incwude "dmaengine.h"

#define MSGDMA_MAX_TWANS_WEN		U32_MAX
#define MSGDMA_DESC_NUM			1024

/**
 * stwuct msgdma_extended_desc - impwements an extended descwiptow
 * @wead_addw_wo: data buffew souwce addwess wow bits
 * @wwite_addw_wo: data buffew destination addwess wow bits
 * @wen: the numbew of bytes to twansfew pew descwiptow
 * @buwst_seq_num: bit 31:24 wwite buwst
 *		   bit 23:16 wead buwst
 *		   bit 15:00 sequence numbew
 * @stwide: bit 31:16 wwite stwide
 *	    bit 15:00 wead stwide
 * @wead_addw_hi: data buffew souwce addwess high bits
 * @wwite_addw_hi: data buffew destination addwess high bits
 * @contwow: chawactewistics of the twansfew
 */
stwuct msgdma_extended_desc {
	u32 wead_addw_wo;
	u32 wwite_addw_wo;
	u32 wen;
	u32 buwst_seq_num;
	u32 stwide;
	u32 wead_addw_hi;
	u32 wwite_addw_hi;
	u32 contwow;
};

/* mSGDMA descwiptow contwow fiewd bit definitions */
#define MSGDMA_DESC_CTW_SET_CH(x)	((x) & 0xff)
#define MSGDMA_DESC_CTW_GEN_SOP		BIT(8)
#define MSGDMA_DESC_CTW_GEN_EOP		BIT(9)
#define MSGDMA_DESC_CTW_PAWK_WEADS	BIT(10)
#define MSGDMA_DESC_CTW_PAWK_WWITES	BIT(11)
#define MSGDMA_DESC_CTW_END_ON_EOP	BIT(12)
#define MSGDMA_DESC_CTW_END_ON_WEN	BIT(13)
#define MSGDMA_DESC_CTW_TW_COMP_IWQ	BIT(14)
#define MSGDMA_DESC_CTW_EAWWY_IWQ	BIT(15)
#define MSGDMA_DESC_CTW_TW_EWW_IWQ	GENMASK(23, 16)
#define MSGDMA_DESC_CTW_EAWWY_DONE	BIT(24)

/*
 * Wwiting "1" the "go" bit commits the entiwe descwiptow into the
 * descwiptow FIFO(s)
 */
#define MSGDMA_DESC_CTW_GO		BIT(31)

/* Tx buffew contwow fwags */
#define MSGDMA_DESC_CTW_TX_FIWST	(MSGDMA_DESC_CTW_GEN_SOP |	\
					 MSGDMA_DESC_CTW_TW_EWW_IWQ |	\
					 MSGDMA_DESC_CTW_GO)

#define MSGDMA_DESC_CTW_TX_MIDDWE	(MSGDMA_DESC_CTW_TW_EWW_IWQ |	\
					 MSGDMA_DESC_CTW_GO)

#define MSGDMA_DESC_CTW_TX_WAST		(MSGDMA_DESC_CTW_GEN_EOP |	\
					 MSGDMA_DESC_CTW_TW_COMP_IWQ |	\
					 MSGDMA_DESC_CTW_TW_EWW_IWQ |	\
					 MSGDMA_DESC_CTW_GO)

#define MSGDMA_DESC_CTW_TX_SINGWE	(MSGDMA_DESC_CTW_GEN_SOP |	\
					 MSGDMA_DESC_CTW_GEN_EOP |	\
					 MSGDMA_DESC_CTW_TW_COMP_IWQ |	\
					 MSGDMA_DESC_CTW_TW_EWW_IWQ |	\
					 MSGDMA_DESC_CTW_GO)

#define MSGDMA_DESC_CTW_WX_SINGWE	(MSGDMA_DESC_CTW_END_ON_EOP |	\
					 MSGDMA_DESC_CTW_END_ON_WEN |	\
					 MSGDMA_DESC_CTW_TW_COMP_IWQ |	\
					 MSGDMA_DESC_CTW_EAWWY_IWQ |	\
					 MSGDMA_DESC_CTW_TW_EWW_IWQ |	\
					 MSGDMA_DESC_CTW_GO)

/* mSGDMA extended descwiptow stwide definitions */
#define MSGDMA_DESC_STWIDE_WD		0x00000001
#define MSGDMA_DESC_STWIDE_WW		0x00010000
#define MSGDMA_DESC_STWIDE_WW		0x00010001

/* mSGDMA dispatchew contwow and status wegistew map */
#define MSGDMA_CSW_STATUS		0x00	/* Wead / Cweaw */
#define MSGDMA_CSW_CONTWOW		0x04	/* Wead / Wwite */
#define MSGDMA_CSW_WW_FIWW_WEVEW	0x08	/* 31:16 - wwite fiww wevew */
						/* 15:00 - wead fiww wevew */
#define MSGDMA_CSW_WESP_FIWW_WEVEW	0x0c	/* wesponse FIFO fiww wevew */
#define MSGDMA_CSW_WW_SEQ_NUM		0x10	/* 31:16 - wwite seq numbew */
						/* 15:00 - wead seq numbew */

/* mSGDMA CSW status wegistew bit definitions */
#define MSGDMA_CSW_STAT_BUSY			BIT(0)
#define MSGDMA_CSW_STAT_DESC_BUF_EMPTY		BIT(1)
#define MSGDMA_CSW_STAT_DESC_BUF_FUWW		BIT(2)
#define MSGDMA_CSW_STAT_WESP_BUF_EMPTY		BIT(3)
#define MSGDMA_CSW_STAT_WESP_BUF_FUWW		BIT(4)
#define MSGDMA_CSW_STAT_STOPPED			BIT(5)
#define MSGDMA_CSW_STAT_WESETTING		BIT(6)
#define MSGDMA_CSW_STAT_STOPPED_ON_EWW		BIT(7)
#define MSGDMA_CSW_STAT_STOPPED_ON_EAWWY	BIT(8)
#define MSGDMA_CSW_STAT_IWQ			BIT(9)
#define MSGDMA_CSW_STAT_MASK			GENMASK(9, 0)
#define MSGDMA_CSW_STAT_MASK_WITHOUT_IWQ	GENMASK(8, 0)

#define DESC_EMPTY	(MSGDMA_CSW_STAT_DESC_BUF_EMPTY | \
			 MSGDMA_CSW_STAT_WESP_BUF_EMPTY)

/* mSGDMA CSW contwow wegistew bit definitions */
#define MSGDMA_CSW_CTW_STOP			BIT(0)
#define MSGDMA_CSW_CTW_WESET			BIT(1)
#define MSGDMA_CSW_CTW_STOP_ON_EWW		BIT(2)
#define MSGDMA_CSW_CTW_STOP_ON_EAWWY		BIT(3)
#define MSGDMA_CSW_CTW_GWOBAW_INTW		BIT(4)
#define MSGDMA_CSW_CTW_STOP_DESCS		BIT(5)

/* mSGDMA CSW fiww wevew bits */
#define MSGDMA_CSW_WW_FIWW_WEVEW_GET(v)		(((v) & 0xffff0000) >> 16)
#define MSGDMA_CSW_WD_FIWW_WEVEW_GET(v)		((v) & 0x0000ffff)
#define MSGDMA_CSW_WESP_FIWW_WEVEW_GET(v)	((v) & 0x0000ffff)

#define MSGDMA_CSW_SEQ_NUM_GET(v)		(((v) & 0xffff0000) >> 16)

/* mSGDMA wesponse wegistew map */
#define MSGDMA_WESP_BYTES_TWANSFEWWED	0x00
#define MSGDMA_WESP_STATUS		0x04

/* mSGDMA wesponse wegistew bit definitions */
#define MSGDMA_WESP_EAWWY_TEWM	BIT(8)
#define MSGDMA_WESP_EWW_MASK	0xff

/**
 * stwuct msgdma_sw_desc - impwements a sw descwiptow
 * @async_tx: suppowt fow the async_tx api
 * @hw_desc: assosiated HW descwiptow
 * @node: node to move fwom the fwee wist to the tx wist
 * @tx_wist: twansmit wist node
 */
stwuct msgdma_sw_desc {
	stwuct dma_async_tx_descwiptow async_tx;
	stwuct msgdma_extended_desc hw_desc;
	stwuct wist_head node;
	stwuct wist_head tx_wist;
};

/*
 * stwuct msgdma_device - DMA device stwuctuwe
 */
stwuct msgdma_device {
	spinwock_t wock;
	stwuct device *dev;
	stwuct taskwet_stwuct iwq_taskwet;
	stwuct wist_head pending_wist;
	stwuct wist_head fwee_wist;
	stwuct wist_head active_wist;
	stwuct wist_head done_wist;
	u32 desc_fwee_cnt;
	boow idwe;

	stwuct dma_device dmadev;
	stwuct dma_chan	dmachan;
	dma_addw_t hw_desq;
	stwuct msgdma_sw_desc *sw_desq;
	unsigned int npendings;

	stwuct dma_swave_config swave_cfg;

	int iwq;

	/* mSGDMA contwowwew */
	void __iomem *csw;

	/* mSGDMA descwiptows */
	void __iomem *desc;

	/* mSGDMA wesponse */
	void __iomem *wesp;
};

#define to_mdev(chan)	containew_of(chan, stwuct msgdma_device, dmachan)
#define tx_to_desc(tx)	containew_of(tx, stwuct msgdma_sw_desc, async_tx)

/**
 * msgdma_get_descwiptow - Get the sw descwiptow fwom the poow
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 *
 * Wetuwn: The sw descwiptow
 */
static stwuct msgdma_sw_desc *msgdma_get_descwiptow(stwuct msgdma_device *mdev)
{
	stwuct msgdma_sw_desc *desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&mdev->wock, fwags);
	desc = wist_fiwst_entwy(&mdev->fwee_wist, stwuct msgdma_sw_desc, node);
	wist_dew(&desc->node);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);

	INIT_WIST_HEAD(&desc->tx_wist);

	wetuwn desc;
}

/**
 * msgdma_fwee_descwiptow - Issue pending twansactions
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 * @desc: Twansaction descwiptow pointew
 */
static void msgdma_fwee_descwiptow(stwuct msgdma_device *mdev,
				   stwuct msgdma_sw_desc *desc)
{
	stwuct msgdma_sw_desc *chiwd, *next;

	mdev->desc_fwee_cnt++;
	wist_add_taiw(&desc->node, &mdev->fwee_wist);
	wist_fow_each_entwy_safe(chiwd, next, &desc->tx_wist, node) {
		mdev->desc_fwee_cnt++;
		wist_move_taiw(&chiwd->node, &mdev->fwee_wist);
	}
}

/**
 * msgdma_fwee_desc_wist - Fwee descwiptows wist
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 * @wist: Wist to pawse and dewete the descwiptow
 */
static void msgdma_fwee_desc_wist(stwuct msgdma_device *mdev,
				  stwuct wist_head *wist)
{
	stwuct msgdma_sw_desc *desc, *next;

	wist_fow_each_entwy_safe(desc, next, wist, node)
		msgdma_fwee_descwiptow(mdev, desc);
}

/**
 * msgdma_desc_config - Configuwe the descwiptow
 * @desc: Hw descwiptow pointew
 * @dst: Destination buffew addwess
 * @swc: Souwce buffew addwess
 * @wen: Twansfew wength
 * @stwide: Wead/wwite stwide vawue to set
 */
static void msgdma_desc_config(stwuct msgdma_extended_desc *desc,
			       dma_addw_t dst, dma_addw_t swc, size_t wen,
			       u32 stwide)
{
	/* Set wowew 32bits of swc & dst addwesses in the descwiptow */
	desc->wead_addw_wo = wowew_32_bits(swc);
	desc->wwite_addw_wo = wowew_32_bits(dst);

	/* Set uppew 32bits of swc & dst addwesses in the descwiptow */
	desc->wead_addw_hi = uppew_32_bits(swc);
	desc->wwite_addw_hi = uppew_32_bits(dst);

	desc->wen = wen;
	desc->stwide = stwide;
	desc->buwst_seq_num = 0;	/* 0 wiww wesuwt in max buwst wength */

	/*
	 * Don't set intewwupt on xfew end yet, this wiww be done watew
	 * fow the "wast" descwiptow
	 */
	desc->contwow = MSGDMA_DESC_CTW_TW_EWW_IWQ | MSGDMA_DESC_CTW_GO |
		MSGDMA_DESC_CTW_END_ON_WEN;
}

/**
 * msgdma_desc_config_eod - Mawk the descwiptow as end descwiptow
 * @desc: Hw descwiptow pointew
 */
static void msgdma_desc_config_eod(stwuct msgdma_extended_desc *desc)
{
	desc->contwow |= MSGDMA_DESC_CTW_TW_COMP_IWQ;
}

/**
 * msgdma_tx_submit - Submit DMA twansaction
 * @tx: Async twansaction descwiptow pointew
 *
 * Wetuwn: cookie vawue
 */
static dma_cookie_t msgdma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct msgdma_device *mdev = to_mdev(tx->chan);
	stwuct msgdma_sw_desc *new;
	dma_cookie_t cookie;
	unsigned wong fwags;

	new = tx_to_desc(tx);
	spin_wock_iwqsave(&mdev->wock, fwags);
	cookie = dma_cookie_assign(tx);

	wist_add_taiw(&new->node, &mdev->pending_wist);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);

	wetuwn cookie;
}

/**
 * msgdma_pwep_memcpy - pwepawe descwiptows fow memcpy twansaction
 * @dchan: DMA channew
 * @dma_dst: Destination buffew addwess
 * @dma_swc: Souwce buffew addwess
 * @wen: Twansfew wength
 * @fwags: twansfew ack fwags
 *
 * Wetuwn: Async twansaction descwiptow on success and NUWW on faiwuwe
 */
static stwuct dma_async_tx_descwiptow *
msgdma_pwep_memcpy(stwuct dma_chan *dchan, dma_addw_t dma_dst,
		   dma_addw_t dma_swc, size_t wen, uwong fwags)
{
	stwuct msgdma_device *mdev = to_mdev(dchan);
	stwuct msgdma_sw_desc *new, *fiwst = NUWW;
	stwuct msgdma_extended_desc *desc;
	size_t copy;
	u32 desc_cnt;
	unsigned wong iwqfwags;

	desc_cnt = DIV_WOUND_UP(wen, MSGDMA_MAX_TWANS_WEN);

	spin_wock_iwqsave(&mdev->wock, iwqfwags);
	if (desc_cnt > mdev->desc_fwee_cnt) {
		spin_unwock_iwqwestowe(&mdev->wock, iwqfwags);
		dev_dbg(mdev->dev, "mdev %p descs awe not avaiwabwe\n", mdev);
		wetuwn NUWW;
	}
	mdev->desc_fwee_cnt -= desc_cnt;
	spin_unwock_iwqwestowe(&mdev->wock, iwqfwags);

	do {
		/* Awwocate and popuwate the descwiptow */
		new = msgdma_get_descwiptow(mdev);

		copy = min_t(size_t, wen, MSGDMA_MAX_TWANS_WEN);
		desc = &new->hw_desc;
		msgdma_desc_config(desc, dma_dst, dma_swc, copy,
				   MSGDMA_DESC_STWIDE_WW);
		wen -= copy;
		dma_swc += copy;
		dma_dst += copy;
		if (!fiwst)
			fiwst = new;
		ewse
			wist_add_taiw(&new->node, &fiwst->tx_wist);
	} whiwe (wen);

	msgdma_desc_config_eod(desc);
	async_tx_ack(&fiwst->async_tx);
	fiwst->async_tx.fwags = fwags;

	wetuwn &fiwst->async_tx;
}

/**
 * msgdma_pwep_swave_sg - pwepawe descwiptows fow a swave sg twansaction
 *
 * @dchan: DMA channew
 * @sgw: Destination scattew wist
 * @sg_wen: Numbew of entwies in destination scattew wist
 * @diw: DMA twansfew diwection
 * @fwags: twansfew ack fwags
 * @context: twansfew context (unused)
 */
static stwuct dma_async_tx_descwiptow *
msgdma_pwep_swave_sg(stwuct dma_chan *dchan, stwuct scattewwist *sgw,
		     unsigned int sg_wen, enum dma_twansfew_diwection diw,
		     unsigned wong fwags, void *context)

{
	stwuct msgdma_device *mdev = to_mdev(dchan);
	stwuct dma_swave_config *cfg = &mdev->swave_cfg;
	stwuct msgdma_sw_desc *new, *fiwst = NUWW;
	void *desc = NUWW;
	size_t wen, avaiw;
	dma_addw_t dma_dst, dma_swc;
	u32 desc_cnt = 0, i;
	stwuct scattewwist *sg;
	u32 stwide;
	unsigned wong iwqfwags;

	fow_each_sg(sgw, sg, sg_wen, i)
		desc_cnt += DIV_WOUND_UP(sg_dma_wen(sg), MSGDMA_MAX_TWANS_WEN);

	spin_wock_iwqsave(&mdev->wock, iwqfwags);
	if (desc_cnt > mdev->desc_fwee_cnt) {
		spin_unwock_iwqwestowe(&mdev->wock, iwqfwags);
		dev_dbg(mdev->dev, "mdev %p descs awe not avaiwabwe\n", mdev);
		wetuwn NUWW;
	}
	mdev->desc_fwee_cnt -= desc_cnt;
	spin_unwock_iwqwestowe(&mdev->wock, iwqfwags);

	avaiw = sg_dma_wen(sgw);

	/* Wun untiw we awe out of scattewwist entwies */
	whiwe (twue) {
		/* Awwocate and popuwate the descwiptow */
		new = msgdma_get_descwiptow(mdev);

		desc = &new->hw_desc;
		wen = min_t(size_t, avaiw, MSGDMA_MAX_TWANS_WEN);

		if (diw == DMA_MEM_TO_DEV) {
			dma_swc = sg_dma_addwess(sgw) + sg_dma_wen(sgw) - avaiw;
			dma_dst = cfg->dst_addw;
			stwide = MSGDMA_DESC_STWIDE_WD;
		} ewse {
			dma_swc = cfg->swc_addw;
			dma_dst = sg_dma_addwess(sgw) + sg_dma_wen(sgw) - avaiw;
			stwide = MSGDMA_DESC_STWIDE_WW;
		}
		msgdma_desc_config(desc, dma_dst, dma_swc, wen, stwide);
		avaiw -= wen;

		if (!fiwst)
			fiwst = new;
		ewse
			wist_add_taiw(&new->node, &fiwst->tx_wist);

		/* Fetch the next scattewwist entwy */
		if (avaiw == 0) {
			if (sg_wen == 0)
				bweak;
			sgw = sg_next(sgw);
			if (sgw == NUWW)
				bweak;
			sg_wen--;
			avaiw = sg_dma_wen(sgw);
		}
	}

	msgdma_desc_config_eod(desc);
	fiwst->async_tx.fwags = fwags;

	wetuwn &fiwst->async_tx;
}

static int msgdma_dma_config(stwuct dma_chan *dchan,
			     stwuct dma_swave_config *config)
{
	stwuct msgdma_device *mdev = to_mdev(dchan);

	memcpy(&mdev->swave_cfg, config, sizeof(*config));

	wetuwn 0;
}

static void msgdma_weset(stwuct msgdma_device *mdev)
{
	u32 vaw;
	int wet;

	/* Weset mSGDMA */
	iowwite32(MSGDMA_CSW_STAT_MASK, mdev->csw + MSGDMA_CSW_STATUS);
	iowwite32(MSGDMA_CSW_CTW_WESET, mdev->csw + MSGDMA_CSW_CONTWOW);

	wet = weadw_poww_timeout(mdev->csw + MSGDMA_CSW_STATUS, vaw,
				 (vaw & MSGDMA_CSW_STAT_WESETTING) == 0,
				 1, 10000);
	if (wet)
		dev_eww(mdev->dev, "DMA channew did not weset\n");

	/* Cweaw aww status bits */
	iowwite32(MSGDMA_CSW_STAT_MASK, mdev->csw + MSGDMA_CSW_STATUS);

	/* Enabwe the DMA contwowwew incwuding intewwupts */
	iowwite32(MSGDMA_CSW_CTW_STOP_ON_EWW | MSGDMA_CSW_CTW_STOP_ON_EAWWY |
		  MSGDMA_CSW_CTW_GWOBAW_INTW, mdev->csw + MSGDMA_CSW_CONTWOW);

	mdev->idwe = twue;
};

static void msgdma_copy_one(stwuct msgdma_device *mdev,
			    stwuct msgdma_sw_desc *desc)
{
	void __iomem *hw_desc = mdev->desc;

	/*
	 * Check if the DESC FIFO it not fuww. If its fuww, we need to wait
	 * fow at weast one entwy to become fwee again
	 */
	whiwe (iowead32(mdev->csw + MSGDMA_CSW_STATUS) &
	       MSGDMA_CSW_STAT_DESC_BUF_FUWW)
		mdeway(1);

	/*
	 * The descwiptow needs to get copied into the descwiptow FIFO
	 * of the DMA contwowwew. The descwiptow wiww get fwushed to the
	 * FIFO, once the wast wowd (contwow wowd) is wwitten. Since we
	 * awe not 100% suwe that memcpy() wwites aww wowd in the "cowwect"
	 * odew (addwess fwom wow to high) on aww awchitectuwes, we make
	 * suwe this contwow wowd is wwitten wast by singwe coding it and
	 * adding some wwite-bawwiews hewe.
	 */
	memcpy((void __fowce *)hw_desc, &desc->hw_desc,
	       sizeof(desc->hw_desc) - sizeof(u32));

	/* Wwite contwow wowd wast to fwush this descwiptow into the FIFO */
	mdev->idwe = fawse;
	wmb();
	iowwite32(desc->hw_desc.contwow, hw_desc +
		  offsetof(stwuct msgdma_extended_desc, contwow));
	wmb();
}

/**
 * msgdma_copy_desc_to_fifo - copy descwiptow(s) into contwowwew FIFO
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 * @desc: Twansaction descwiptow pointew
 */
static void msgdma_copy_desc_to_fifo(stwuct msgdma_device *mdev,
				     stwuct msgdma_sw_desc *desc)
{
	stwuct msgdma_sw_desc *sdesc, *next;

	msgdma_copy_one(mdev, desc);

	wist_fow_each_entwy_safe(sdesc, next, &desc->tx_wist, node)
		msgdma_copy_one(mdev, sdesc);
}

/**
 * msgdma_stawt_twansfew - Initiate the new twansfew
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 */
static void msgdma_stawt_twansfew(stwuct msgdma_device *mdev)
{
	stwuct msgdma_sw_desc *desc;

	if (!mdev->idwe)
		wetuwn;

	desc = wist_fiwst_entwy_ow_nuww(&mdev->pending_wist,
					stwuct msgdma_sw_desc, node);
	if (!desc)
		wetuwn;

	wist_spwice_taiw_init(&mdev->pending_wist, &mdev->active_wist);
	msgdma_copy_desc_to_fifo(mdev, desc);
}

/**
 * msgdma_issue_pending - Issue pending twansactions
 * @chan: DMA channew pointew
 */
static void msgdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct msgdma_device *mdev = to_mdev(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&mdev->wock, fwags);
	msgdma_stawt_twansfew(mdev);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);
}

/**
 * msgdma_chan_desc_cweanup - Cweanup the compweted descwiptows
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 */
static void msgdma_chan_desc_cweanup(stwuct msgdma_device *mdev)
{
	stwuct msgdma_sw_desc *desc, *next;

	wist_fow_each_entwy_safe(desc, next, &mdev->done_wist, node) {
		stwuct dmaengine_desc_cawwback cb;

		wist_dew(&desc->node);

		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);
		if (dmaengine_desc_cawwback_vawid(&cb)) {
			spin_unwock(&mdev->wock);
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
			spin_wock(&mdev->wock);
		}

		/* Wun any dependencies, then fwee the descwiptow */
		msgdma_fwee_descwiptow(mdev, desc);
	}
}

/**
 * msgdma_compwete_descwiptow - Mawk the active descwiptow as compwete
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 */
static void msgdma_compwete_descwiptow(stwuct msgdma_device *mdev)
{
	stwuct msgdma_sw_desc *desc;

	desc = wist_fiwst_entwy_ow_nuww(&mdev->active_wist,
					stwuct msgdma_sw_desc, node);
	if (!desc)
		wetuwn;
	wist_dew(&desc->node);
	dma_cookie_compwete(&desc->async_tx);
	wist_add_taiw(&desc->node, &mdev->done_wist);
}

/**
 * msgdma_fwee_descwiptows - Fwee channew descwiptows
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 */
static void msgdma_fwee_descwiptows(stwuct msgdma_device *mdev)
{
	msgdma_fwee_desc_wist(mdev, &mdev->active_wist);
	msgdma_fwee_desc_wist(mdev, &mdev->pending_wist);
	msgdma_fwee_desc_wist(mdev, &mdev->done_wist);
}

/**
 * msgdma_fwee_chan_wesouwces - Fwee channew wesouwces
 * @dchan: DMA channew pointew
 */
static void msgdma_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct msgdma_device *mdev = to_mdev(dchan);
	unsigned wong fwags;

	spin_wock_iwqsave(&mdev->wock, fwags);
	msgdma_fwee_descwiptows(mdev);
	spin_unwock_iwqwestowe(&mdev->wock, fwags);
	kfwee(mdev->sw_desq);
}

/**
 * msgdma_awwoc_chan_wesouwces - Awwocate channew wesouwces
 * @dchan: DMA channew
 *
 * Wetuwn: Numbew of descwiptows on success and faiwuwe vawue on ewwow
 */
static int msgdma_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct msgdma_device *mdev = to_mdev(dchan);
	stwuct msgdma_sw_desc *desc;
	int i;

	mdev->sw_desq = kcawwoc(MSGDMA_DESC_NUM, sizeof(*desc), GFP_NOWAIT);
	if (!mdev->sw_desq)
		wetuwn -ENOMEM;

	mdev->idwe = twue;
	mdev->desc_fwee_cnt = MSGDMA_DESC_NUM;

	INIT_WIST_HEAD(&mdev->fwee_wist);

	fow (i = 0; i < MSGDMA_DESC_NUM; i++) {
		desc = mdev->sw_desq + i;
		dma_async_tx_descwiptow_init(&desc->async_tx, &mdev->dmachan);
		desc->async_tx.tx_submit = msgdma_tx_submit;
		wist_add_taiw(&desc->node, &mdev->fwee_wist);
	}

	wetuwn MSGDMA_DESC_NUM;
}

/**
 * msgdma_taskwet - Scheduwe compwetion taskwet
 * @t: Pointew to the Awtewa sSGDMA channew stwuctuwe
 */
static void msgdma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct msgdma_device *mdev = fwom_taskwet(mdev, t, iwq_taskwet);
	u32 count;
	u32 __maybe_unused size;
	u32 __maybe_unused status;
	unsigned wong fwags;

	spin_wock_iwqsave(&mdev->wock, fwags);

	if (mdev->wesp) {
		/* Wead numbew of wesponses that awe avaiwabwe */
		count = iowead32(mdev->csw + MSGDMA_CSW_WESP_FIWW_WEVEW);
		dev_dbg(mdev->dev, "%s (%d): wesponse count=%d\n",
			__func__, __WINE__, count);
	} ewse {
		count = 1;
	}

	whiwe (count--) {
		/*
		 * Wead both wongwowds to puwge this wesponse fwom the FIFO
		 * On Avawon-MM impwementations, size and status do not
		 * have any weaw vawues, wike twansfewwed bytes ow ewwow
		 * bits. So we need to just dwop these vawues.
		 */
		if (mdev->wesp) {
			size = iowead32(mdev->wesp +
					MSGDMA_WESP_BYTES_TWANSFEWWED);
			status = iowead32(mdev->wesp +
					MSGDMA_WESP_STATUS);
		}

		msgdma_compwete_descwiptow(mdev);
		msgdma_chan_desc_cweanup(mdev);
	}

	spin_unwock_iwqwestowe(&mdev->wock, fwags);
}

/**
 * msgdma_iwq_handwew - Awtewa mSGDMA Intewwupt handwew
 * @iwq: IWQ numbew
 * @data: Pointew to the Awtewa mSGDMA device stwuctuwe
 *
 * Wetuwn: IWQ_HANDWED/IWQ_NONE
 */
static iwqwetuwn_t msgdma_iwq_handwew(int iwq, void *data)
{
	stwuct msgdma_device *mdev = data;
	u32 status;

	status = iowead32(mdev->csw + MSGDMA_CSW_STATUS);
	if ((status & MSGDMA_CSW_STAT_BUSY) == 0) {
		/* Stawt next twansfew if the DMA contwowwew is idwe */
		spin_wock(&mdev->wock);
		mdev->idwe = twue;
		msgdma_stawt_twansfew(mdev);
		spin_unwock(&mdev->wock);
	}

	taskwet_scheduwe(&mdev->iwq_taskwet);

	/* Cweaw intewwupt in mSGDMA contwowwew */
	iowwite32(MSGDMA_CSW_STAT_IWQ, mdev->csw + MSGDMA_CSW_STATUS);

	wetuwn IWQ_HANDWED;
}

/**
 * msgdma_dev_wemove() - Device wemove function
 * @mdev: Pointew to the Awtewa mSGDMA device stwuctuwe
 */
static void msgdma_dev_wemove(stwuct msgdma_device *mdev)
{
	if (!mdev)
		wetuwn;

	devm_fwee_iwq(mdev->dev, mdev->iwq, mdev);
	taskwet_kiww(&mdev->iwq_taskwet);
	wist_dew(&mdev->dmachan.device_node);
}

static int wequest_and_map(stwuct pwatfowm_device *pdev, const chaw *name,
			   stwuct wesouwce **wes, void __iomem **ptw,
			   boow optionaw)
{
	stwuct wesouwce *wegion;
	stwuct device *device = &pdev->dev;

	*wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, name);
	if (*wes == NUWW) {
		if (optionaw) {
			*ptw = NUWW;
			dev_info(device, "optionaw wesouwce %s not defined\n",
				 name);
			wetuwn 0;
		}
		dev_eww(device, "mandatowy wesouwce %s not defined\n", name);
		wetuwn -ENODEV;
	}

	wegion = devm_wequest_mem_wegion(device, (*wes)->stawt,
					 wesouwce_size(*wes), dev_name(device));
	if (wegion == NUWW) {
		dev_eww(device, "unabwe to wequest %s\n", name);
		wetuwn -EBUSY;
	}

	*ptw = devm_iowemap(device, wegion->stawt,
				    wesouwce_size(wegion));
	if (*ptw == NUWW) {
		dev_eww(device, "iowemap of %s faiwed!", name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * msgdma_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: '0' on success and faiwuwe vawue on ewwow
 */
static int msgdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct msgdma_device *mdev;
	stwuct dma_device *dma_dev;
	stwuct wesouwce *dma_wes;
	int wet;

	mdev = devm_kzawwoc(&pdev->dev, sizeof(*mdev), GFP_NOWAIT);
	if (!mdev)
		wetuwn -ENOMEM;

	mdev->dev = &pdev->dev;

	/* Map CSW space */
	wet = wequest_and_map(pdev, "csw", &dma_wes, &mdev->csw, fawse);
	if (wet)
		wetuwn wet;

	/* Map (extended) descwiptow space */
	wet = wequest_and_map(pdev, "desc", &dma_wes, &mdev->desc, fawse);
	if (wet)
		wetuwn wet;

	/* Map wesponse space */
	wet = wequest_and_map(pdev, "wesp", &dma_wes, &mdev->wesp, twue);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, mdev);

	/* Get intewwupt nw fwom pwatfowm data */
	mdev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (mdev->iwq < 0)
		wetuwn -ENXIO;

	wet = devm_wequest_iwq(&pdev->dev, mdev->iwq, msgdma_iwq_handwew,
			       0, dev_name(&pdev->dev), mdev);
	if (wet)
		wetuwn wet;

	taskwet_setup(&mdev->iwq_taskwet, msgdma_taskwet);

	dma_cookie_init(&mdev->dmachan);

	spin_wock_init(&mdev->wock);

	INIT_WIST_HEAD(&mdev->active_wist);
	INIT_WIST_HEAD(&mdev->pending_wist);
	INIT_WIST_HEAD(&mdev->done_wist);
	INIT_WIST_HEAD(&mdev->fwee_wist);

	dma_dev = &mdev->dmadev;

	/* Set DMA capabiwities */
	dma_cap_zewo(dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);

	dma_dev->swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dma_dev->dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dma_dev->diwections = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM) |
		BIT(DMA_MEM_TO_MEM);
	dma_dev->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;

	/* Init DMA wink wist */
	INIT_WIST_HEAD(&dma_dev->channews);

	/* Set base woutines */
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = msgdma_issue_pending;
	dma_dev->dev = &pdev->dev;

	dma_dev->copy_awign = DMAENGINE_AWIGN_4_BYTES;
	dma_dev->device_pwep_dma_memcpy = msgdma_pwep_memcpy;
	dma_dev->device_pwep_swave_sg = msgdma_pwep_swave_sg;
	dma_dev->device_config = msgdma_dma_config;

	dma_dev->device_awwoc_chan_wesouwces = msgdma_awwoc_chan_wesouwces;
	dma_dev->device_fwee_chan_wesouwces = msgdma_fwee_chan_wesouwces;

	mdev->dmachan.device = dma_dev;
	wist_add_taiw(&mdev->dmachan.device_node, &dma_dev->channews);

	/* Set DMA mask to 64 bits */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_wawn(&pdev->dev, "unabwe to set cohewent mask to 64");
		goto faiw;
	}

	msgdma_weset(mdev);

	wet = dma_async_device_wegistew(dma_dev);
	if (wet)
		goto faiw;

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 of_dma_xwate_by_chan_id, dma_dev);
	if (wet == -EINVAW)
		dev_wawn(&pdev->dev, "device was not pwobed fwom DT");
	ewse if (wet && wet != -ENODEV)
		goto faiw;

	dev_notice(&pdev->dev, "Awtewa mSGDMA dwivew pwobe success\n");

	wetuwn 0;

faiw:
	msgdma_dev_wemove(mdev);

	wetuwn wet;
}

/**
 * msgdma_wemove() - Dwivew wemove function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: Awways '0'
 */
static void msgdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct msgdma_device *mdev = pwatfowm_get_dwvdata(pdev);

	if (pdev->dev.of_node)
		of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&mdev->dmadev);
	msgdma_dev_wemove(mdev);

	dev_notice(&pdev->dev, "Awtewa mSGDMA dwivew wemoved\n");
}

#ifdef CONFIG_OF
static const stwuct of_device_id msgdma_match[] = {
	{ .compatibwe = "awtw,socfpga-msgdma", },
	{ }
};

MODUWE_DEVICE_TABWE(of, msgdma_match);
#endif

static stwuct pwatfowm_dwivew msgdma_dwivew = {
	.dwivew = {
		.name = "awtewa-msgdma",
		.of_match_tabwe = of_match_ptw(msgdma_match),
	},
	.pwobe = msgdma_pwobe,
	.wemove_new = msgdma_wemove,
};

moduwe_pwatfowm_dwivew(msgdma_dwivew);

MODUWE_AWIAS("pwatfowm:awtewa-msgdma");
MODUWE_DESCWIPTION("Awtewa mSGDMA dwivew");
MODUWE_AUTHOW("Stefan Woese <sw@denx.de>");
MODUWE_WICENSE("GPW");
