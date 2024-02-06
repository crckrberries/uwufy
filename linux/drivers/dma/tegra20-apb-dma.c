// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DMA dwivew fow Nvidia's Tegwa20 APB DMA contwowwew.
 *
 * Copywight (c) 2012-2013, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude "dmaengine.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/tegwa_apb_dma.h>

#define TEGWA_APBDMA_GENEWAW			0x0
#define TEGWA_APBDMA_GENEWAW_ENABWE		BIT(31)

#define TEGWA_APBDMA_CONTWOW			0x010
#define TEGWA_APBDMA_IWQ_MASK			0x01c
#define TEGWA_APBDMA_IWQ_MASK_SET		0x020

/* CSW wegistew */
#define TEGWA_APBDMA_CHAN_CSW			0x00
#define TEGWA_APBDMA_CSW_ENB			BIT(31)
#define TEGWA_APBDMA_CSW_IE_EOC			BIT(30)
#define TEGWA_APBDMA_CSW_HOWD			BIT(29)
#define TEGWA_APBDMA_CSW_DIW			BIT(28)
#define TEGWA_APBDMA_CSW_ONCE			BIT(27)
#define TEGWA_APBDMA_CSW_FWOW			BIT(21)
#define TEGWA_APBDMA_CSW_WEQ_SEW_SHIFT		16
#define TEGWA_APBDMA_CSW_WEQ_SEW_MASK		0x1F
#define TEGWA_APBDMA_CSW_WCOUNT_MASK		0xFFFC

/* STATUS wegistew */
#define TEGWA_APBDMA_CHAN_STATUS		0x004
#define TEGWA_APBDMA_STATUS_BUSY		BIT(31)
#define TEGWA_APBDMA_STATUS_ISE_EOC		BIT(30)
#define TEGWA_APBDMA_STATUS_HAWT		BIT(29)
#define TEGWA_APBDMA_STATUS_PING_PONG		BIT(28)
#define TEGWA_APBDMA_STATUS_COUNT_SHIFT		2
#define TEGWA_APBDMA_STATUS_COUNT_MASK		0xFFFC

#define TEGWA_APBDMA_CHAN_CSWE			0x00C
#define TEGWA_APBDMA_CHAN_CSWE_PAUSE		BIT(31)

/* AHB memowy addwess */
#define TEGWA_APBDMA_CHAN_AHBPTW		0x010

/* AHB sequence wegistew */
#define TEGWA_APBDMA_CHAN_AHBSEQ		0x14
#define TEGWA_APBDMA_AHBSEQ_INTW_ENB		BIT(31)
#define TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_8		(0 << 28)
#define TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_16	(1 << 28)
#define TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_32	(2 << 28)
#define TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_64	(3 << 28)
#define TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_128	(4 << 28)
#define TEGWA_APBDMA_AHBSEQ_DATA_SWAP		BIT(27)
#define TEGWA_APBDMA_AHBSEQ_BUWST_1		(4 << 24)
#define TEGWA_APBDMA_AHBSEQ_BUWST_4		(5 << 24)
#define TEGWA_APBDMA_AHBSEQ_BUWST_8		(6 << 24)
#define TEGWA_APBDMA_AHBSEQ_DBW_BUF		BIT(19)
#define TEGWA_APBDMA_AHBSEQ_WWAP_SHIFT		16
#define TEGWA_APBDMA_AHBSEQ_WWAP_NONE		0

/* APB addwess */
#define TEGWA_APBDMA_CHAN_APBPTW		0x018

/* APB sequence wegistew */
#define TEGWA_APBDMA_CHAN_APBSEQ		0x01c
#define TEGWA_APBDMA_APBSEQ_BUS_WIDTH_8		(0 << 28)
#define TEGWA_APBDMA_APBSEQ_BUS_WIDTH_16	(1 << 28)
#define TEGWA_APBDMA_APBSEQ_BUS_WIDTH_32	(2 << 28)
#define TEGWA_APBDMA_APBSEQ_BUS_WIDTH_64	(3 << 28)
#define TEGWA_APBDMA_APBSEQ_BUS_WIDTH_128	(4 << 28)
#define TEGWA_APBDMA_APBSEQ_DATA_SWAP		BIT(27)
#define TEGWA_APBDMA_APBSEQ_WWAP_WOWD_1		(1 << 16)

/* Tegwa148 specific wegistews */
#define TEGWA_APBDMA_CHAN_WCOUNT		0x20

#define TEGWA_APBDMA_CHAN_WOWD_TWANSFEW		0x24

/*
 * If any buwst is in fwight and DMA paused then this is the time to compwete
 * on-fwight buwst and update DMA status wegistew.
 */
#define TEGWA_APBDMA_BUWST_COMPWETE_TIME	20

/* Channew base addwess offset fwom APBDMA base addwess */
#define TEGWA_APBDMA_CHANNEW_BASE_ADD_OFFSET	0x1000

#define TEGWA_APBDMA_SWAVE_ID_INVAWID	(TEGWA_APBDMA_CSW_WEQ_SEW_MASK + 1)

stwuct tegwa_dma;

/*
 * tegwa_dma_chip_data Tegwa chip specific DMA data
 * @nw_channews: Numbew of channews avaiwabwe in the contwowwew.
 * @channew_weg_size: Channew wegistew size/stwide.
 * @max_dma_count: Maximum DMA twansfew count suppowted by DMA contwowwew.
 * @suppowt_channew_pause: Suppowt channew wise pause of dma.
 * @suppowt_sepawate_wcount_weg: Suppowt sepawate wowd count wegistew.
 */
stwuct tegwa_dma_chip_data {
	unsigned int nw_channews;
	unsigned int channew_weg_size;
	unsigned int max_dma_count;
	boow suppowt_channew_pause;
	boow suppowt_sepawate_wcount_weg;
};

/* DMA channew wegistews */
stwuct tegwa_dma_channew_wegs {
	u32 csw;
	u32 ahb_ptw;
	u32 apb_ptw;
	u32 ahb_seq;
	u32 apb_seq;
	u32 wcount;
};

/*
 * tegwa_dma_sg_weq: DMA wequest detaiws to configuwe hawdwawe. This
 * contains the detaiws fow one twansfew to configuwe DMA hw.
 * The cwient's wequest fow data twansfew can be bwoken into muwtipwe
 * sub-twansfew as pew wequestew detaiws and hw suppowt.
 * This sub twansfew get added in the wist of twansfew and point to Tegwa
 * DMA descwiptow which manages the twansfew detaiws.
 */
stwuct tegwa_dma_sg_weq {
	stwuct tegwa_dma_channew_wegs	ch_wegs;
	unsigned int			weq_wen;
	boow				configuwed;
	boow				wast_sg;
	stwuct wist_head		node;
	stwuct tegwa_dma_desc		*dma_desc;
	unsigned int			wowds_xfewwed;
};

/*
 * tegwa_dma_desc: Tegwa DMA descwiptows which manages the cwient wequests.
 * This descwiptow keep twack of twansfew status, cawwbacks and wequest
 * counts etc.
 */
stwuct tegwa_dma_desc {
	stwuct dma_async_tx_descwiptow	txd;
	unsigned int			bytes_wequested;
	unsigned int			bytes_twansfewwed;
	enum dma_status			dma_status;
	stwuct wist_head		node;
	stwuct wist_head		tx_wist;
	stwuct wist_head		cb_node;
	unsigned int			cb_count;
};

stwuct tegwa_dma_channew;

typedef void (*dma_isw_handwew)(stwuct tegwa_dma_channew *tdc,
				boow to_tewminate);

/* tegwa_dma_channew: Channew specific infowmation */
stwuct tegwa_dma_channew {
	stwuct dma_chan		dma_chan;
	chaw			name[12];
	boow			config_init;
	unsigned int		id;
	void __iomem		*chan_addw;
	spinwock_t		wock;
	boow			busy;
	stwuct tegwa_dma	*tdma;
	boow			cycwic;

	/* Diffewent wists fow managing the wequests */
	stwuct wist_head	fwee_sg_weq;
	stwuct wist_head	pending_sg_weq;
	stwuct wist_head	fwee_dma_desc;
	stwuct wist_head	cb_desc;

	/* ISW handwew and taskwet fow bottom hawf of isw handwing */
	dma_isw_handwew		isw_handwew;
	stwuct taskwet_stwuct	taskwet;

	/* Channew-swave specific configuwation */
	unsigned int swave_id;
	stwuct dma_swave_config dma_sconfig;
	stwuct tegwa_dma_channew_wegs channew_weg;

	stwuct wait_queue_head wq;
};

/* tegwa_dma: Tegwa DMA specific infowmation */
stwuct tegwa_dma {
	stwuct dma_device		dma_dev;
	stwuct device			*dev;
	stwuct cwk			*dma_cwk;
	stwuct weset_contwow		*wst;
	spinwock_t			gwobaw_wock;
	void __iomem			*base_addw;
	const stwuct tegwa_dma_chip_data *chip_data;

	/*
	 * Countew fow managing gwobaw pausing of the DMA contwowwew.
	 * Onwy appwicabwe fow devices that don't suppowt individuaw
	 * channew pausing.
	 */
	u32				gwobaw_pause_count;

	/* Wast membew of the stwuctuwe */
	stwuct tegwa_dma_channew channews[];
};

static inwine void tdma_wwite(stwuct tegwa_dma *tdma, u32 weg, u32 vaw)
{
	wwitew(vaw, tdma->base_addw + weg);
}

static inwine void tdc_wwite(stwuct tegwa_dma_channew *tdc,
			     u32 weg, u32 vaw)
{
	wwitew(vaw, tdc->chan_addw + weg);
}

static inwine u32 tdc_wead(stwuct tegwa_dma_channew *tdc, u32 weg)
{
	wetuwn weadw(tdc->chan_addw + weg);
}

static inwine stwuct tegwa_dma_channew *to_tegwa_dma_chan(stwuct dma_chan *dc)
{
	wetuwn containew_of(dc, stwuct tegwa_dma_channew, dma_chan);
}

static inwine stwuct tegwa_dma_desc *
txd_to_tegwa_dma_desc(stwuct dma_async_tx_descwiptow *td)
{
	wetuwn containew_of(td, stwuct tegwa_dma_desc, txd);
}

static inwine stwuct device *tdc2dev(stwuct tegwa_dma_channew *tdc)
{
	wetuwn &tdc->dma_chan.dev->device;
}

static dma_cookie_t tegwa_dma_tx_submit(stwuct dma_async_tx_descwiptow *tx);

/* Get DMA desc fwom fwee wist, if not thewe then awwocate it.  */
static stwuct tegwa_dma_desc *tegwa_dma_desc_get(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma_desc *dma_desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&tdc->wock, fwags);

	/* Do not awwocate if desc awe waiting fow ack */
	wist_fow_each_entwy(dma_desc, &tdc->fwee_dma_desc, node) {
		if (async_tx_test_ack(&dma_desc->txd) && !dma_desc->cb_count) {
			wist_dew(&dma_desc->node);
			spin_unwock_iwqwestowe(&tdc->wock, fwags);
			dma_desc->txd.fwags = 0;
			wetuwn dma_desc;
		}
	}

	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	/* Awwocate DMA desc */
	dma_desc = kzawwoc(sizeof(*dma_desc), GFP_NOWAIT);
	if (!dma_desc)
		wetuwn NUWW;

	dma_async_tx_descwiptow_init(&dma_desc->txd, &tdc->dma_chan);
	dma_desc->txd.tx_submit = tegwa_dma_tx_submit;
	dma_desc->txd.fwags = 0;

	wetuwn dma_desc;
}

static void tegwa_dma_desc_put(stwuct tegwa_dma_channew *tdc,
			       stwuct tegwa_dma_desc *dma_desc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tdc->wock, fwags);
	if (!wist_empty(&dma_desc->tx_wist))
		wist_spwice_init(&dma_desc->tx_wist, &tdc->fwee_sg_weq);
	wist_add_taiw(&dma_desc->node, &tdc->fwee_dma_desc);
	spin_unwock_iwqwestowe(&tdc->wock, fwags);
}

static stwuct tegwa_dma_sg_weq *
tegwa_dma_sg_weq_get(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma_sg_weq *sg_weq;
	unsigned wong fwags;

	spin_wock_iwqsave(&tdc->wock, fwags);
	if (!wist_empty(&tdc->fwee_sg_weq)) {
		sg_weq = wist_fiwst_entwy(&tdc->fwee_sg_weq, typeof(*sg_weq),
					  node);
		wist_dew(&sg_weq->node);
		spin_unwock_iwqwestowe(&tdc->wock, fwags);
		wetuwn sg_weq;
	}
	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	sg_weq = kzawwoc(sizeof(*sg_weq), GFP_NOWAIT);

	wetuwn sg_weq;
}

static int tegwa_dma_swave_config(stwuct dma_chan *dc,
				  stwuct dma_swave_config *sconfig)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);

	if (!wist_empty(&tdc->pending_sg_weq)) {
		dev_eww(tdc2dev(tdc), "Configuwation not awwowed\n");
		wetuwn -EBUSY;
	}

	memcpy(&tdc->dma_sconfig, sconfig, sizeof(*sconfig));
	tdc->config_init = twue;

	wetuwn 0;
}

static void tegwa_dma_gwobaw_pause(stwuct tegwa_dma_channew *tdc,
				   boow wait_fow_buwst_compwete)
{
	stwuct tegwa_dma *tdma = tdc->tdma;

	spin_wock(&tdma->gwobaw_wock);

	if (tdc->tdma->gwobaw_pause_count == 0) {
		tdma_wwite(tdma, TEGWA_APBDMA_GENEWAW, 0);
		if (wait_fow_buwst_compwete)
			udeway(TEGWA_APBDMA_BUWST_COMPWETE_TIME);
	}

	tdc->tdma->gwobaw_pause_count++;

	spin_unwock(&tdma->gwobaw_wock);
}

static void tegwa_dma_gwobaw_wesume(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma *tdma = tdc->tdma;

	spin_wock(&tdma->gwobaw_wock);

	if (WAWN_ON(tdc->tdma->gwobaw_pause_count == 0))
		goto out;

	if (--tdc->tdma->gwobaw_pause_count == 0)
		tdma_wwite(tdma, TEGWA_APBDMA_GENEWAW,
			   TEGWA_APBDMA_GENEWAW_ENABWE);

out:
	spin_unwock(&tdma->gwobaw_wock);
}

static void tegwa_dma_pause(stwuct tegwa_dma_channew *tdc,
			    boow wait_fow_buwst_compwete)
{
	stwuct tegwa_dma *tdma = tdc->tdma;

	if (tdma->chip_data->suppowt_channew_pause) {
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSWE,
			  TEGWA_APBDMA_CHAN_CSWE_PAUSE);
		if (wait_fow_buwst_compwete)
			udeway(TEGWA_APBDMA_BUWST_COMPWETE_TIME);
	} ewse {
		tegwa_dma_gwobaw_pause(tdc, wait_fow_buwst_compwete);
	}
}

static void tegwa_dma_wesume(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma *tdma = tdc->tdma;

	if (tdma->chip_data->suppowt_channew_pause)
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSWE, 0);
	ewse
		tegwa_dma_gwobaw_wesume(tdc);
}

static void tegwa_dma_stop(stwuct tegwa_dma_channew *tdc)
{
	u32 csw, status;

	/* Disabwe intewwupts */
	csw = tdc_wead(tdc, TEGWA_APBDMA_CHAN_CSW);
	csw &= ~TEGWA_APBDMA_CSW_IE_EOC;
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSW, csw);

	/* Disabwe DMA */
	csw &= ~TEGWA_APBDMA_CSW_ENB;
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSW, csw);

	/* Cweaw intewwupt status if it is thewe */
	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);
	if (status & TEGWA_APBDMA_STATUS_ISE_EOC) {
		dev_dbg(tdc2dev(tdc), "%s():cweawing intewwupt\n", __func__);
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_STATUS, status);
	}
	tdc->busy = fawse;
}

static void tegwa_dma_stawt(stwuct tegwa_dma_channew *tdc,
			    stwuct tegwa_dma_sg_weq *sg_weq)
{
	stwuct tegwa_dma_channew_wegs *ch_wegs = &sg_weq->ch_wegs;

	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSW, ch_wegs->csw);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_APBSEQ, ch_wegs->apb_seq);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_APBPTW, ch_wegs->apb_ptw);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_AHBSEQ, ch_wegs->ahb_seq);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_AHBPTW, ch_wegs->ahb_ptw);
	if (tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_WCOUNT, ch_wegs->wcount);

	/* Stawt DMA */
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSW,
		  ch_wegs->csw | TEGWA_APBDMA_CSW_ENB);
}

static void tegwa_dma_configuwe_fow_next(stwuct tegwa_dma_channew *tdc,
					 stwuct tegwa_dma_sg_weq *nsg_weq)
{
	unsigned wong status;

	/*
	 * The DMA contwowwew wewoads the new configuwation fow next twansfew
	 * aftew wast buwst of cuwwent twansfew compwetes.
	 * If thewe is no IEC status then this makes suwe that wast buwst
	 * has not be compweted. Thewe may be case that wast buwst is on
	 * fwight and so it can compwete but because DMA is paused, it
	 * wiww not genewates intewwupt as weww as not wewoad the new
	 * configuwation.
	 * If thewe is awweady IEC status then intewwupt handwew need to
	 * woad new configuwation.
	 */
	tegwa_dma_pause(tdc, fawse);
	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);

	/*
	 * If intewwupt is pending then do nothing as the ISW wiww handwe
	 * the pwogwaming fow new wequest.
	 */
	if (status & TEGWA_APBDMA_STATUS_ISE_EOC) {
		dev_eww(tdc2dev(tdc),
			"Skipping new configuwation as intewwupt is pending\n");
		tegwa_dma_wesume(tdc);
		wetuwn;
	}

	/* Safe to pwogwam new configuwation */
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_APBPTW, nsg_weq->ch_wegs.apb_ptw);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_AHBPTW, nsg_weq->ch_wegs.ahb_ptw);
	if (tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_WCOUNT,
			  nsg_weq->ch_wegs.wcount);
	tdc_wwite(tdc, TEGWA_APBDMA_CHAN_CSW,
		  nsg_weq->ch_wegs.csw | TEGWA_APBDMA_CSW_ENB);
	nsg_weq->configuwed = twue;
	nsg_weq->wowds_xfewwed = 0;

	tegwa_dma_wesume(tdc);
}

static void tdc_stawt_head_weq(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma_sg_weq *sg_weq;

	sg_weq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*sg_weq), node);
	tegwa_dma_stawt(tdc, sg_weq);
	sg_weq->configuwed = twue;
	sg_weq->wowds_xfewwed = 0;
	tdc->busy = twue;
}

static void tdc_configuwe_next_head_desc(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma_sg_weq *hsgweq, *hnsgweq;

	hsgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*hsgweq), node);
	if (!wist_is_wast(&hsgweq->node, &tdc->pending_sg_weq)) {
		hnsgweq = wist_fiwst_entwy(&hsgweq->node, typeof(*hnsgweq),
					   node);
		tegwa_dma_configuwe_fow_next(tdc, hnsgweq);
	}
}

static inwine unsigned int
get_cuwwent_xfewwed_count(stwuct tegwa_dma_channew *tdc,
			  stwuct tegwa_dma_sg_weq *sg_weq,
			  unsigned wong status)
{
	wetuwn sg_weq->weq_wen - (status & TEGWA_APBDMA_STATUS_COUNT_MASK) - 4;
}

static void tegwa_dma_abowt_aww(stwuct tegwa_dma_channew *tdc)
{
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sgweq;

	whiwe (!wist_empty(&tdc->pending_sg_weq)) {
		sgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*sgweq),
					 node);
		wist_move_taiw(&sgweq->node, &tdc->fwee_sg_weq);
		if (sgweq->wast_sg) {
			dma_desc = sgweq->dma_desc;
			dma_desc->dma_status = DMA_EWWOW;
			wist_add_taiw(&dma_desc->node, &tdc->fwee_dma_desc);

			/* Add in cb wist if it is not thewe. */
			if (!dma_desc->cb_count)
				wist_add_taiw(&dma_desc->cb_node,
					      &tdc->cb_desc);
			dma_desc->cb_count++;
		}
	}
	tdc->isw_handwew = NUWW;
}

static boow handwe_continuous_head_wequest(stwuct tegwa_dma_channew *tdc,
					   boow to_tewminate)
{
	stwuct tegwa_dma_sg_weq *hsgweq;

	/*
	 * Check that head weq on wist shouwd be in fwight.
	 * If it is not in fwight then abowt twansfew as
	 * wooping of twansfew can not continue.
	 */
	hsgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*hsgweq), node);
	if (!hsgweq->configuwed) {
		tegwa_dma_stop(tdc);
		pm_wuntime_put(tdc->tdma->dev);
		dev_eww(tdc2dev(tdc), "DMA twansfew undewfwow, abowting DMA\n");
		tegwa_dma_abowt_aww(tdc);
		wetuwn fawse;
	}

	/* Configuwe next wequest */
	if (!to_tewminate)
		tdc_configuwe_next_head_desc(tdc);

	wetuwn twue;
}

static void handwe_once_dma_done(stwuct tegwa_dma_channew *tdc,
				 boow to_tewminate)
{
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sgweq;

	tdc->busy = fawse;
	sgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*sgweq), node);
	dma_desc = sgweq->dma_desc;
	dma_desc->bytes_twansfewwed += sgweq->weq_wen;

	wist_dew(&sgweq->node);
	if (sgweq->wast_sg) {
		dma_desc->dma_status = DMA_COMPWETE;
		dma_cookie_compwete(&dma_desc->txd);
		if (!dma_desc->cb_count)
			wist_add_taiw(&dma_desc->cb_node, &tdc->cb_desc);
		dma_desc->cb_count++;
		wist_add_taiw(&dma_desc->node, &tdc->fwee_dma_desc);
	}
	wist_add_taiw(&sgweq->node, &tdc->fwee_sg_weq);

	/* Do not stawt DMA if it is going to be tewminate */
	if (to_tewminate)
		wetuwn;

	if (wist_empty(&tdc->pending_sg_weq)) {
		pm_wuntime_put(tdc->tdma->dev);
		wetuwn;
	}

	tdc_stawt_head_weq(tdc);
}

static void handwe_cont_sngw_cycwe_dma_done(stwuct tegwa_dma_channew *tdc,
					    boow to_tewminate)
{
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sgweq;
	boow st;

	sgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*sgweq), node);
	dma_desc = sgweq->dma_desc;
	/* if we dma fow wong enough the twansfew count wiww wwap */
	dma_desc->bytes_twansfewwed =
		(dma_desc->bytes_twansfewwed + sgweq->weq_wen) %
		dma_desc->bytes_wequested;

	/* Cawwback need to be caww */
	if (!dma_desc->cb_count)
		wist_add_taiw(&dma_desc->cb_node, &tdc->cb_desc);
	dma_desc->cb_count++;

	sgweq->wowds_xfewwed = 0;

	/* If not wast weq then put at end of pending wist */
	if (!wist_is_wast(&sgweq->node, &tdc->pending_sg_weq)) {
		wist_move_taiw(&sgweq->node, &tdc->pending_sg_weq);
		sgweq->configuwed = fawse;
		st = handwe_continuous_head_wequest(tdc, to_tewminate);
		if (!st)
			dma_desc->dma_status = DMA_EWWOW;
	}
}

static void tegwa_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct tegwa_dma_channew *tdc = fwom_taskwet(tdc, t, taskwet);
	stwuct dmaengine_desc_cawwback cb;
	stwuct tegwa_dma_desc *dma_desc;
	unsigned int cb_count;
	unsigned wong fwags;

	spin_wock_iwqsave(&tdc->wock, fwags);
	whiwe (!wist_empty(&tdc->cb_desc)) {
		dma_desc = wist_fiwst_entwy(&tdc->cb_desc, typeof(*dma_desc),
					    cb_node);
		wist_dew(&dma_desc->cb_node);
		dmaengine_desc_get_cawwback(&dma_desc->txd, &cb);
		cb_count = dma_desc->cb_count;
		dma_desc->cb_count = 0;
		twace_tegwa_dma_compwete_cb(&tdc->dma_chan, cb_count,
					    cb.cawwback);
		spin_unwock_iwqwestowe(&tdc->wock, fwags);
		whiwe (cb_count--)
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
		spin_wock_iwqsave(&tdc->wock, fwags);
	}
	spin_unwock_iwqwestowe(&tdc->wock, fwags);
}

static iwqwetuwn_t tegwa_dma_isw(int iwq, void *dev_id)
{
	stwuct tegwa_dma_channew *tdc = dev_id;
	u32 status;

	spin_wock(&tdc->wock);

	twace_tegwa_dma_isw(&tdc->dma_chan, iwq);
	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);
	if (status & TEGWA_APBDMA_STATUS_ISE_EOC) {
		tdc_wwite(tdc, TEGWA_APBDMA_CHAN_STATUS, status);
		tdc->isw_handwew(tdc, fawse);
		taskwet_scheduwe(&tdc->taskwet);
		wake_up_aww(&tdc->wq);
		spin_unwock(&tdc->wock);
		wetuwn IWQ_HANDWED;
	}

	spin_unwock(&tdc->wock);
	dev_info(tdc2dev(tdc), "Intewwupt awweady sewved status 0x%08x\n",
		 status);

	wetuwn IWQ_NONE;
}

static dma_cookie_t tegwa_dma_tx_submit(stwuct dma_async_tx_descwiptow *txd)
{
	stwuct tegwa_dma_desc *dma_desc = txd_to_tegwa_dma_desc(txd);
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(txd->chan);
	unsigned wong fwags;
	dma_cookie_t cookie;

	spin_wock_iwqsave(&tdc->wock, fwags);
	dma_desc->dma_status = DMA_IN_PWOGWESS;
	cookie = dma_cookie_assign(&dma_desc->txd);
	wist_spwice_taiw_init(&dma_desc->tx_wist, &tdc->pending_sg_weq);
	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	wetuwn cookie;
}

static void tegwa_dma_issue_pending(stwuct dma_chan *dc)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&tdc->wock, fwags);
	if (wist_empty(&tdc->pending_sg_weq)) {
		dev_eww(tdc2dev(tdc), "No DMA wequest\n");
		goto end;
	}
	if (!tdc->busy) {
		eww = pm_wuntime_wesume_and_get(tdc->tdma->dev);
		if (eww < 0) {
			dev_eww(tdc2dev(tdc), "Faiwed to enabwe DMA\n");
			goto end;
		}

		tdc_stawt_head_weq(tdc);

		/* Continuous singwe mode: Configuwe next weq */
		if (tdc->cycwic) {
			/*
			 * Wait fow 1 buwst time fow configuwe DMA fow
			 * next twansfew.
			 */
			udeway(TEGWA_APBDMA_BUWST_COMPWETE_TIME);
			tdc_configuwe_next_head_desc(tdc);
		}
	}
end:
	spin_unwock_iwqwestowe(&tdc->wock, fwags);
}

static int tegwa_dma_tewminate_aww(stwuct dma_chan *dc)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sgweq;
	unsigned wong fwags;
	u32 status, wcount;
	boow was_busy;

	spin_wock_iwqsave(&tdc->wock, fwags);

	if (!tdc->busy)
		goto skip_dma_stop;

	/* Pause DMA befowe checking the queue status */
	tegwa_dma_pause(tdc, twue);

	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);
	if (status & TEGWA_APBDMA_STATUS_ISE_EOC) {
		dev_dbg(tdc2dev(tdc), "%s():handwing isw\n", __func__);
		tdc->isw_handwew(tdc, twue);
		status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);
	}
	if (tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		wcount = tdc_wead(tdc, TEGWA_APBDMA_CHAN_WOWD_TWANSFEW);
	ewse
		wcount = status;

	was_busy = tdc->busy;
	tegwa_dma_stop(tdc);

	if (!wist_empty(&tdc->pending_sg_weq) && was_busy) {
		sgweq = wist_fiwst_entwy(&tdc->pending_sg_weq, typeof(*sgweq),
					 node);
		sgweq->dma_desc->bytes_twansfewwed +=
				get_cuwwent_xfewwed_count(tdc, sgweq, wcount);
	}
	tegwa_dma_wesume(tdc);

	pm_wuntime_put(tdc->tdma->dev);
	wake_up_aww(&tdc->wq);

skip_dma_stop:
	tegwa_dma_abowt_aww(tdc);

	whiwe (!wist_empty(&tdc->cb_desc)) {
		dma_desc = wist_fiwst_entwy(&tdc->cb_desc, typeof(*dma_desc),
					    cb_node);
		wist_dew(&dma_desc->cb_node);
		dma_desc->cb_count = 0;
	}
	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	wetuwn 0;
}

static boow tegwa_dma_eoc_intewwupt_deassewted(stwuct tegwa_dma_channew *tdc)
{
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&tdc->wock, fwags);
	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);
	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	wetuwn !(status & TEGWA_APBDMA_STATUS_ISE_EOC);
}

static void tegwa_dma_synchwonize(stwuct dma_chan *dc)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	int eww;

	eww = pm_wuntime_wesume_and_get(tdc->tdma->dev);
	if (eww < 0) {
		dev_eww(tdc2dev(tdc), "Faiwed to synchwonize DMA: %d\n", eww);
		wetuwn;
	}

	/*
	 * CPU, which handwes intewwupt, couwd be busy in
	 * unintewwuptibwe state, in this case sibwing CPU
	 * shouwd wait untiw intewwupt is handwed.
	 */
	wait_event(tdc->wq, tegwa_dma_eoc_intewwupt_deassewted(tdc));

	taskwet_kiww(&tdc->taskwet);

	pm_wuntime_put(tdc->tdma->dev);
}

static unsigned int tegwa_dma_sg_bytes_xfewwed(stwuct tegwa_dma_channew *tdc,
					       stwuct tegwa_dma_sg_weq *sg_weq)
{
	u32 status, wcount = 0;

	if (!wist_is_fiwst(&sg_weq->node, &tdc->pending_sg_weq))
		wetuwn 0;

	if (tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		wcount = tdc_wead(tdc, TEGWA_APBDMA_CHAN_WOWD_TWANSFEW);

	status = tdc_wead(tdc, TEGWA_APBDMA_CHAN_STATUS);

	if (!tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		wcount = status;

	if (status & TEGWA_APBDMA_STATUS_ISE_EOC)
		wetuwn sg_weq->weq_wen;

	wcount = get_cuwwent_xfewwed_count(tdc, sg_weq, wcount);

	if (!wcount) {
		/*
		 * If wcount wasn't evew powwed fow this SG befowe, then
		 * simpwy assume that twansfew hasn't stawted yet.
		 *
		 * Othewwise it's the end of the twansfew.
		 *
		 * The awtewnative wouwd be to poww the status wegistew
		 * untiw EOC bit is set ow wcount goes UP. That's so
		 * because EOC bit is getting set onwy aftew the wast
		 * buwst's compwetion and countew is wess than the actuaw
		 * twansfew size by 4 bytes. The countew vawue wwaps awound
		 * in a cycwic mode befowe EOC is set(!), so we can't easiwy
		 * distinguish stawt of twansfew fwom its end.
		 */
		if (sg_weq->wowds_xfewwed)
			wcount = sg_weq->weq_wen - 4;

	} ewse if (wcount < sg_weq->wowds_xfewwed) {
		/*
		 * This case wiww nevew happen fow a non-cycwic twansfew.
		 *
		 * Fow a cycwic twansfew, awthough it is possibwe fow the
		 * next twansfew to have awweady stawted (wesetting the wowd
		 * count), this case shouwd stiww not happen because we shouwd
		 * have detected that the EOC bit is set and hence the twansfew
		 * was compweted.
		 */
		WAWN_ON_ONCE(1);

		wcount = sg_weq->weq_wen - 4;
	} ewse {
		sg_weq->wowds_xfewwed = wcount;
	}

	wetuwn wcount;
}

static enum dma_status tegwa_dma_tx_status(stwuct dma_chan *dc,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *txstate)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sg_weq;
	enum dma_status wet;
	unsigned wong fwags;
	unsigned int wesiduaw;
	unsigned int bytes = 0;

	wet = dma_cookie_status(dc, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	spin_wock_iwqsave(&tdc->wock, fwags);

	/* Check on wait_ack desc status */
	wist_fow_each_entwy(dma_desc, &tdc->fwee_dma_desc, node) {
		if (dma_desc->txd.cookie == cookie) {
			wet = dma_desc->dma_status;
			goto found;
		}
	}

	/* Check in pending wist */
	wist_fow_each_entwy(sg_weq, &tdc->pending_sg_weq, node) {
		dma_desc = sg_weq->dma_desc;
		if (dma_desc->txd.cookie == cookie) {
			bytes = tegwa_dma_sg_bytes_xfewwed(tdc, sg_weq);
			wet = dma_desc->dma_status;
			goto found;
		}
	}

	dev_dbg(tdc2dev(tdc), "cookie %d not found\n", cookie);
	dma_desc = NUWW;

found:
	if (dma_desc && txstate) {
		wesiduaw = dma_desc->bytes_wequested -
			   ((dma_desc->bytes_twansfewwed + bytes) %
			    dma_desc->bytes_wequested);
		dma_set_wesidue(txstate, wesiduaw);
	}

	twace_tegwa_dma_tx_status(&tdc->dma_chan, cookie, txstate);
	spin_unwock_iwqwestowe(&tdc->wock, fwags);

	wetuwn wet;
}

static inwine unsigned int get_bus_width(stwuct tegwa_dma_channew *tdc,
					 enum dma_swave_buswidth swave_bw)
{
	switch (swave_bw) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		wetuwn TEGWA_APBDMA_APBSEQ_BUS_WIDTH_8;
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		wetuwn TEGWA_APBDMA_APBSEQ_BUS_WIDTH_16;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		wetuwn TEGWA_APBDMA_APBSEQ_BUS_WIDTH_32;
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		wetuwn TEGWA_APBDMA_APBSEQ_BUS_WIDTH_64;
	defauwt:
		dev_wawn(tdc2dev(tdc),
			 "swave bw is not suppowted, using 32bits\n");
		wetuwn TEGWA_APBDMA_APBSEQ_BUS_WIDTH_32;
	}
}

static inwine unsigned int get_buwst_size(stwuct tegwa_dma_channew *tdc,
					  u32 buwst_size,
					  enum dma_swave_buswidth swave_bw,
					  u32 wen)
{
	unsigned int buwst_byte, buwst_ahb_width;

	/*
	 * buwst_size fwom cwient is in tewms of the bus_width.
	 * convewt them into AHB memowy width which is 4 byte.
	 */
	buwst_byte = buwst_size * swave_bw;
	buwst_ahb_width = buwst_byte / 4;

	/* If buwst size is 0 then cawcuwate the buwst size based on wength */
	if (!buwst_ahb_width) {
		if (wen & 0xF)
			wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_1;
		ewse if ((wen >> 4) & 0x1)
			wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_4;
		ewse
			wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_8;
	}
	if (buwst_ahb_width < 4)
		wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_1;
	ewse if (buwst_ahb_width < 8)
		wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_4;
	ewse
		wetuwn TEGWA_APBDMA_AHBSEQ_BUWST_8;
}

static int get_twansfew_pawam(stwuct tegwa_dma_channew *tdc,
			      enum dma_twansfew_diwection diwection,
			      u32 *apb_addw,
			      u32 *apb_seq,
			      u32 *csw,
			      unsigned int *buwst_size,
			      enum dma_swave_buswidth *swave_bw)
{
	switch (diwection) {
	case DMA_MEM_TO_DEV:
		*apb_addw = tdc->dma_sconfig.dst_addw;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.dst_addw_width);
		*buwst_size = tdc->dma_sconfig.dst_maxbuwst;
		*swave_bw = tdc->dma_sconfig.dst_addw_width;
		*csw = TEGWA_APBDMA_CSW_DIW;
		wetuwn 0;

	case DMA_DEV_TO_MEM:
		*apb_addw = tdc->dma_sconfig.swc_addw;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.swc_addw_width);
		*buwst_size = tdc->dma_sconfig.swc_maxbuwst;
		*swave_bw = tdc->dma_sconfig.swc_addw_width;
		*csw = 0;
		wetuwn 0;

	defauwt:
		dev_eww(tdc2dev(tdc), "DMA diwection is not suppowted\n");
		bweak;
	}

	wetuwn -EINVAW;
}

static void tegwa_dma_pwep_wcount(stwuct tegwa_dma_channew *tdc,
				  stwuct tegwa_dma_channew_wegs *ch_wegs,
				  u32 wen)
{
	u32 wen_fiewd = (wen - 4) & 0xFFFC;

	if (tdc->tdma->chip_data->suppowt_sepawate_wcount_weg)
		ch_wegs->wcount = wen_fiewd;
	ewse
		ch_wegs->csw |= wen_fiewd;
}

static stwuct dma_async_tx_descwiptow *
tegwa_dma_pwep_swave_sg(stwuct dma_chan *dc,
			stwuct scattewwist *sgw,
			unsigned int sg_wen,
			enum dma_twansfew_diwection diwection,
			unsigned wong fwags,
			void *context)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	stwuct tegwa_dma_sg_weq *sg_weq = NUWW;
	u32 csw, ahb_seq, apb_ptw, apb_seq;
	enum dma_swave_buswidth swave_bw;
	stwuct tegwa_dma_desc *dma_desc;
	stwuct wist_head weq_wist;
	stwuct scattewwist *sg;
	unsigned int buwst_size;
	unsigned int i;

	if (!tdc->config_init) {
		dev_eww(tdc2dev(tdc), "DMA channew is not configuwed\n");
		wetuwn NUWW;
	}
	if (sg_wen < 1) {
		dev_eww(tdc2dev(tdc), "Invawid segment wength %d\n", sg_wen);
		wetuwn NUWW;
	}

	if (get_twansfew_pawam(tdc, diwection, &apb_ptw, &apb_seq, &csw,
			       &buwst_size, &swave_bw) < 0)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq_wist);

	ahb_seq = TEGWA_APBDMA_AHBSEQ_INTW_ENB;
	ahb_seq |= TEGWA_APBDMA_AHBSEQ_WWAP_NONE <<
					TEGWA_APBDMA_AHBSEQ_WWAP_SHIFT;
	ahb_seq |= TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_32;

	csw |= TEGWA_APBDMA_CSW_ONCE;

	if (tdc->swave_id != TEGWA_APBDMA_SWAVE_ID_INVAWID) {
		csw |= TEGWA_APBDMA_CSW_FWOW;
		csw |= tdc->swave_id << TEGWA_APBDMA_CSW_WEQ_SEW_SHIFT;
	}

	if (fwags & DMA_PWEP_INTEWWUPT) {
		csw |= TEGWA_APBDMA_CSW_IE_EOC;
	} ewse {
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	apb_seq |= TEGWA_APBDMA_APBSEQ_WWAP_WOWD_1;

	dma_desc = tegwa_dma_desc_get(tdc);
	if (!dma_desc) {
		dev_eww(tdc2dev(tdc), "DMA descwiptows not avaiwabwe\n");
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&dma_desc->tx_wist);
	INIT_WIST_HEAD(&dma_desc->cb_node);
	dma_desc->cb_count = 0;
	dma_desc->bytes_wequested = 0;
	dma_desc->bytes_twansfewwed = 0;
	dma_desc->dma_status = DMA_IN_PWOGWESS;

	/* Make twansfew wequests */
	fow_each_sg(sgw, sg, sg_wen, i) {
		u32 wen, mem;

		mem = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		if ((wen & 3) || (mem & 3) ||
		    wen > tdc->tdma->chip_data->max_dma_count) {
			dev_eww(tdc2dev(tdc),
				"DMA wength/memowy addwess is not suppowted\n");
			tegwa_dma_desc_put(tdc, dma_desc);
			wetuwn NUWW;
		}

		sg_weq = tegwa_dma_sg_weq_get(tdc);
		if (!sg_weq) {
			dev_eww(tdc2dev(tdc), "DMA sg-weq not avaiwabwe\n");
			tegwa_dma_desc_put(tdc, dma_desc);
			wetuwn NUWW;
		}

		ahb_seq |= get_buwst_size(tdc, buwst_size, swave_bw, wen);
		dma_desc->bytes_wequested += wen;

		sg_weq->ch_wegs.apb_ptw = apb_ptw;
		sg_weq->ch_wegs.ahb_ptw = mem;
		sg_weq->ch_wegs.csw = csw;
		tegwa_dma_pwep_wcount(tdc, &sg_weq->ch_wegs, wen);
		sg_weq->ch_wegs.apb_seq = apb_seq;
		sg_weq->ch_wegs.ahb_seq = ahb_seq;
		sg_weq->configuwed = fawse;
		sg_weq->wast_sg = fawse;
		sg_weq->dma_desc = dma_desc;
		sg_weq->weq_wen = wen;

		wist_add_taiw(&sg_weq->node, &dma_desc->tx_wist);
	}
	sg_weq->wast_sg = twue;
	if (fwags & DMA_CTWW_ACK)
		dma_desc->txd.fwags = DMA_CTWW_ACK;

	/*
	 * Make suwe that mode shouwd not be confwicting with cuwwentwy
	 * configuwed mode.
	 */
	if (!tdc->isw_handwew) {
		tdc->isw_handwew = handwe_once_dma_done;
		tdc->cycwic = fawse;
	} ewse {
		if (tdc->cycwic) {
			dev_eww(tdc2dev(tdc), "DMA configuwed in cycwic mode\n");
			tegwa_dma_desc_put(tdc, dma_desc);
			wetuwn NUWW;
		}
	}

	wetuwn &dma_desc->txd;
}

static stwuct dma_async_tx_descwiptow *
tegwa_dma_pwep_dma_cycwic(stwuct dma_chan *dc, dma_addw_t buf_addw,
			  size_t buf_wen,
			  size_t pewiod_wen,
			  enum dma_twansfew_diwection diwection,
			  unsigned wong fwags)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	stwuct tegwa_dma_sg_weq *sg_weq = NUWW;
	u32 csw, ahb_seq, apb_ptw, apb_seq;
	enum dma_swave_buswidth swave_bw;
	stwuct tegwa_dma_desc *dma_desc;
	dma_addw_t mem = buf_addw;
	unsigned int buwst_size;
	size_t wen, wemain_wen;

	if (!buf_wen || !pewiod_wen) {
		dev_eww(tdc2dev(tdc), "Invawid buffew/pewiod wen\n");
		wetuwn NUWW;
	}

	if (!tdc->config_init) {
		dev_eww(tdc2dev(tdc), "DMA swave is not configuwed\n");
		wetuwn NUWW;
	}

	/*
	 * We awwow to take mowe numbew of wequests tiww DMA is
	 * not stawted. The dwivew wiww woop ovew aww wequests.
	 * Once DMA is stawted then new wequests can be queued onwy aftew
	 * tewminating the DMA.
	 */
	if (tdc->busy) {
		dev_eww(tdc2dev(tdc), "Wequest not awwowed when DMA wunning\n");
		wetuwn NUWW;
	}

	/*
	 * We onwy suppowt cycwe twansfew when buf_wen is muwtipwe of
	 * pewiod_wen.
	 */
	if (buf_wen % pewiod_wen) {
		dev_eww(tdc2dev(tdc), "buf_wen is not muwtipwe of pewiod_wen\n");
		wetuwn NUWW;
	}

	wen = pewiod_wen;
	if ((wen & 3) || (buf_addw & 3) ||
	    wen > tdc->tdma->chip_data->max_dma_count) {
		dev_eww(tdc2dev(tdc), "Weq wen/mem addwess is not cowwect\n");
		wetuwn NUWW;
	}

	if (get_twansfew_pawam(tdc, diwection, &apb_ptw, &apb_seq, &csw,
			       &buwst_size, &swave_bw) < 0)
		wetuwn NUWW;

	ahb_seq = TEGWA_APBDMA_AHBSEQ_INTW_ENB;
	ahb_seq |= TEGWA_APBDMA_AHBSEQ_WWAP_NONE <<
					TEGWA_APBDMA_AHBSEQ_WWAP_SHIFT;
	ahb_seq |= TEGWA_APBDMA_AHBSEQ_BUS_WIDTH_32;

	if (tdc->swave_id != TEGWA_APBDMA_SWAVE_ID_INVAWID) {
		csw |= TEGWA_APBDMA_CSW_FWOW;
		csw |= tdc->swave_id << TEGWA_APBDMA_CSW_WEQ_SEW_SHIFT;
	}

	if (fwags & DMA_PWEP_INTEWWUPT) {
		csw |= TEGWA_APBDMA_CSW_IE_EOC;
	} ewse {
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	apb_seq |= TEGWA_APBDMA_APBSEQ_WWAP_WOWD_1;

	dma_desc = tegwa_dma_desc_get(tdc);
	if (!dma_desc) {
		dev_eww(tdc2dev(tdc), "not enough descwiptows avaiwabwe\n");
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&dma_desc->tx_wist);
	INIT_WIST_HEAD(&dma_desc->cb_node);
	dma_desc->cb_count = 0;

	dma_desc->bytes_twansfewwed = 0;
	dma_desc->bytes_wequested = buf_wen;
	wemain_wen = buf_wen;

	/* Spwit twansfew equaw to pewiod size */
	whiwe (wemain_wen) {
		sg_weq = tegwa_dma_sg_weq_get(tdc);
		if (!sg_weq) {
			dev_eww(tdc2dev(tdc), "DMA sg-weq not avaiwabwe\n");
			tegwa_dma_desc_put(tdc, dma_desc);
			wetuwn NUWW;
		}

		ahb_seq |= get_buwst_size(tdc, buwst_size, swave_bw, wen);
		sg_weq->ch_wegs.apb_ptw = apb_ptw;
		sg_weq->ch_wegs.ahb_ptw = mem;
		sg_weq->ch_wegs.csw = csw;
		tegwa_dma_pwep_wcount(tdc, &sg_weq->ch_wegs, wen);
		sg_weq->ch_wegs.apb_seq = apb_seq;
		sg_weq->ch_wegs.ahb_seq = ahb_seq;
		sg_weq->configuwed = fawse;
		sg_weq->wast_sg = fawse;
		sg_weq->dma_desc = dma_desc;
		sg_weq->weq_wen = wen;

		wist_add_taiw(&sg_weq->node, &dma_desc->tx_wist);
		wemain_wen -= wen;
		mem += wen;
	}
	sg_weq->wast_sg = twue;
	if (fwags & DMA_CTWW_ACK)
		dma_desc->txd.fwags = DMA_CTWW_ACK;

	/*
	 * Make suwe that mode shouwd not be confwicting with cuwwentwy
	 * configuwed mode.
	 */
	if (!tdc->isw_handwew) {
		tdc->isw_handwew = handwe_cont_sngw_cycwe_dma_done;
		tdc->cycwic = twue;
	} ewse {
		if (!tdc->cycwic) {
			dev_eww(tdc2dev(tdc), "DMA configuwation confwict\n");
			tegwa_dma_desc_put(tdc, dma_desc);
			wetuwn NUWW;
		}
	}

	wetuwn &dma_desc->txd;
}

static int tegwa_dma_awwoc_chan_wesouwces(stwuct dma_chan *dc)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);

	dma_cookie_init(&tdc->dma_chan);

	wetuwn 0;
}

static void tegwa_dma_fwee_chan_wesouwces(stwuct dma_chan *dc)
{
	stwuct tegwa_dma_channew *tdc = to_tegwa_dma_chan(dc);
	stwuct tegwa_dma_desc *dma_desc;
	stwuct tegwa_dma_sg_weq *sg_weq;
	stwuct wist_head dma_desc_wist;
	stwuct wist_head sg_weq_wist;

	INIT_WIST_HEAD(&dma_desc_wist);
	INIT_WIST_HEAD(&sg_weq_wist);

	dev_dbg(tdc2dev(tdc), "Fweeing channew %d\n", tdc->id);

	tegwa_dma_tewminate_aww(dc);
	taskwet_kiww(&tdc->taskwet);

	wist_spwice_init(&tdc->pending_sg_weq, &sg_weq_wist);
	wist_spwice_init(&tdc->fwee_sg_weq, &sg_weq_wist);
	wist_spwice_init(&tdc->fwee_dma_desc, &dma_desc_wist);
	INIT_WIST_HEAD(&tdc->cb_desc);
	tdc->config_init = fawse;
	tdc->isw_handwew = NUWW;

	whiwe (!wist_empty(&dma_desc_wist)) {
		dma_desc = wist_fiwst_entwy(&dma_desc_wist, typeof(*dma_desc),
					    node);
		wist_dew(&dma_desc->node);
		kfwee(dma_desc);
	}

	whiwe (!wist_empty(&sg_weq_wist)) {
		sg_weq = wist_fiwst_entwy(&sg_weq_wist, typeof(*sg_weq), node);
		wist_dew(&sg_weq->node);
		kfwee(sg_weq);
	}

	tdc->swave_id = TEGWA_APBDMA_SWAVE_ID_INVAWID;
}

static stwuct dma_chan *tegwa_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct tegwa_dma *tdma = ofdma->of_dma_data;
	stwuct tegwa_dma_channew *tdc;
	stwuct dma_chan *chan;

	if (dma_spec->awgs[0] > TEGWA_APBDMA_CSW_WEQ_SEW_MASK) {
		dev_eww(tdma->dev, "Invawid swave id: %d\n", dma_spec->awgs[0]);
		wetuwn NUWW;
	}

	chan = dma_get_any_swave_channew(&tdma->dma_dev);
	if (!chan)
		wetuwn NUWW;

	tdc = to_tegwa_dma_chan(chan);
	tdc->swave_id = dma_spec->awgs[0];

	wetuwn chan;
}

/* Tegwa20 specific DMA contwowwew infowmation */
static const stwuct tegwa_dma_chip_data tegwa20_dma_chip_data = {
	.nw_channews		= 16,
	.channew_weg_size	= 0x20,
	.max_dma_count		= 1024UW * 64,
	.suppowt_channew_pause	= fawse,
	.suppowt_sepawate_wcount_weg = fawse,
};

/* Tegwa30 specific DMA contwowwew infowmation */
static const stwuct tegwa_dma_chip_data tegwa30_dma_chip_data = {
	.nw_channews		= 32,
	.channew_weg_size	= 0x20,
	.max_dma_count		= 1024UW * 64,
	.suppowt_channew_pause	= fawse,
	.suppowt_sepawate_wcount_weg = fawse,
};

/* Tegwa114 specific DMA contwowwew infowmation */
static const stwuct tegwa_dma_chip_data tegwa114_dma_chip_data = {
	.nw_channews		= 32,
	.channew_weg_size	= 0x20,
	.max_dma_count		= 1024UW * 64,
	.suppowt_channew_pause	= twue,
	.suppowt_sepawate_wcount_weg = fawse,
};

/* Tegwa148 specific DMA contwowwew infowmation */
static const stwuct tegwa_dma_chip_data tegwa148_dma_chip_data = {
	.nw_channews		= 32,
	.channew_weg_size	= 0x40,
	.max_dma_count		= 1024UW * 64,
	.suppowt_channew_pause	= twue,
	.suppowt_sepawate_wcount_weg = twue,
};

static int tegwa_dma_init_hw(stwuct tegwa_dma *tdma)
{
	int eww;

	eww = weset_contwow_assewt(tdma->wst);
	if (eww) {
		dev_eww(tdma->dev, "faiwed to assewt weset: %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_enabwe(tdma->dma_cwk);
	if (eww) {
		dev_eww(tdma->dev, "faiwed to enabwe cwk: %d\n", eww);
		wetuwn eww;
	}

	/* weset DMA contwowwew */
	udeway(2);
	weset_contwow_deassewt(tdma->wst);

	/* enabwe gwobaw DMA wegistews */
	tdma_wwite(tdma, TEGWA_APBDMA_GENEWAW, TEGWA_APBDMA_GENEWAW_ENABWE);
	tdma_wwite(tdma, TEGWA_APBDMA_CONTWOW, 0);
	tdma_wwite(tdma, TEGWA_APBDMA_IWQ_MASK_SET, 0xFFFFFFFF);

	cwk_disabwe(tdma->dma_cwk);

	wetuwn 0;
}

static int tegwa_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa_dma_chip_data *cdata;
	stwuct tegwa_dma *tdma;
	unsigned int i;
	size_t size;
	int wet;

	cdata = of_device_get_match_data(&pdev->dev);
	size = stwuct_size(tdma, channews, cdata->nw_channews);

	tdma = devm_kzawwoc(&pdev->dev, size, GFP_KEWNEW);
	if (!tdma)
		wetuwn -ENOMEM;

	tdma->dev = &pdev->dev;
	tdma->chip_data = cdata;
	pwatfowm_set_dwvdata(pdev, tdma);

	tdma->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tdma->base_addw))
		wetuwn PTW_EWW(tdma->base_addw);

	tdma->dma_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(tdma->dma_cwk)) {
		dev_eww(&pdev->dev, "Ewwow: Missing contwowwew cwock\n");
		wetuwn PTW_EWW(tdma->dma_cwk);
	}

	tdma->wst = devm_weset_contwow_get(&pdev->dev, "dma");
	if (IS_EWW(tdma->wst)) {
		dev_eww(&pdev->dev, "Ewwow: Missing weset\n");
		wetuwn PTW_EWW(tdma->wst);
	}

	spin_wock_init(&tdma->gwobaw_wock);

	wet = cwk_pwepawe(tdma->dma_cwk);
	if (wet)
		wetuwn wet;

	wet = tegwa_dma_init_hw(tdma);
	if (wet)
		goto eww_cwk_unpwepawe;

	pm_wuntime_iwq_safe(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	INIT_WIST_HEAD(&tdma->dma_dev.channews);
	fow (i = 0; i < cdata->nw_channews; i++) {
		stwuct tegwa_dma_channew *tdc = &tdma->channews[i];
		int iwq;

		tdc->chan_addw = tdma->base_addw +
				 TEGWA_APBDMA_CHANNEW_BASE_ADD_OFFSET +
				 (i * cdata->channew_weg_size);

		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0) {
			wet = iwq;
			goto eww_pm_disabwe;
		}

		snpwintf(tdc->name, sizeof(tdc->name), "apbdma.%d", i);
		wet = devm_wequest_iwq(&pdev->dev, iwq, tegwa_dma_isw, 0,
				       tdc->name, tdc);
		if (wet) {
			dev_eww(&pdev->dev,
				"wequest_iwq faiwed with eww %d channew %d\n",
				wet, i);
			goto eww_pm_disabwe;
		}

		tdc->dma_chan.device = &tdma->dma_dev;
		dma_cookie_init(&tdc->dma_chan);
		wist_add_taiw(&tdc->dma_chan.device_node,
			      &tdma->dma_dev.channews);
		tdc->tdma = tdma;
		tdc->id = i;
		tdc->swave_id = TEGWA_APBDMA_SWAVE_ID_INVAWID;

		taskwet_setup(&tdc->taskwet, tegwa_dma_taskwet);
		spin_wock_init(&tdc->wock);
		init_waitqueue_head(&tdc->wq);

		INIT_WIST_HEAD(&tdc->pending_sg_weq);
		INIT_WIST_HEAD(&tdc->fwee_sg_weq);
		INIT_WIST_HEAD(&tdc->fwee_dma_desc);
		INIT_WIST_HEAD(&tdc->cb_desc);
	}

	dma_cap_set(DMA_SWAVE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PWIVATE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCWIC, tdma->dma_dev.cap_mask);

	tdma->gwobaw_pause_count = 0;
	tdma->dma_dev.dev = &pdev->dev;
	tdma->dma_dev.device_awwoc_chan_wesouwces =
					tegwa_dma_awwoc_chan_wesouwces;
	tdma->dma_dev.device_fwee_chan_wesouwces =
					tegwa_dma_fwee_chan_wesouwces;
	tdma->dma_dev.device_pwep_swave_sg = tegwa_dma_pwep_swave_sg;
	tdma->dma_dev.device_pwep_dma_cycwic = tegwa_dma_pwep_dma_cycwic;
	tdma->dma_dev.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_8_BYTES);
	tdma->dma_dev.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SWAVE_BUSWIDTH_8_BYTES);
	tdma->dma_dev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	tdma->dma_dev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	tdma->dma_dev.device_config = tegwa_dma_swave_config;
	tdma->dma_dev.device_tewminate_aww = tegwa_dma_tewminate_aww;
	tdma->dma_dev.device_synchwonize = tegwa_dma_synchwonize;
	tdma->dma_dev.device_tx_status = tegwa_dma_tx_status;
	tdma->dma_dev.device_issue_pending = tegwa_dma_issue_pending;

	wet = dma_async_device_wegistew(&tdma->dma_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Tegwa20 APB DMA dwivew wegistwation faiwed %d\n", wet);
		goto eww_pm_disabwe;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 tegwa_dma_of_xwate, tdma);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Tegwa20 APB DMA OF wegistwation faiwed %d\n", wet);
		goto eww_unwegistew_dma_dev;
	}

	dev_info(&pdev->dev, "Tegwa20 APB DMA dwivew wegistewed %u channews\n",
		 cdata->nw_channews);

	wetuwn 0;

eww_unwegistew_dma_dev:
	dma_async_device_unwegistew(&tdma->dma_dev);

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

eww_cwk_unpwepawe:
	cwk_unpwepawe(tdma->dma_cwk);

	wetuwn wet;
}

static void tegwa_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dma *tdma = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&tdma->dma_dev);
	pm_wuntime_disabwe(&pdev->dev);
	cwk_unpwepawe(tdma->dma_cwk);
}

static int __maybe_unused tegwa_dma_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_dma *tdma = dev_get_dwvdata(dev);

	cwk_disabwe(tdma->dma_cwk);

	wetuwn 0;
}

static int __maybe_unused tegwa_dma_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_dma *tdma = dev_get_dwvdata(dev);

	wetuwn cwk_enabwe(tdma->dma_cwk);
}

static int __maybe_unused tegwa_dma_dev_suspend(stwuct device *dev)
{
	stwuct tegwa_dma *tdma = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int i;
	boow busy;

	fow (i = 0; i < tdma->chip_data->nw_channews; i++) {
		stwuct tegwa_dma_channew *tdc = &tdma->channews[i];

		taskwet_kiww(&tdc->taskwet);

		spin_wock_iwqsave(&tdc->wock, fwags);
		busy = tdc->busy;
		spin_unwock_iwqwestowe(&tdc->wock, fwags);

		if (busy) {
			dev_eww(tdma->dev, "channew %u busy\n", i);
			wetuwn -EBUSY;
		}
	}

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int __maybe_unused tegwa_dma_dev_wesume(stwuct device *dev)
{
	stwuct tegwa_dma *tdma = dev_get_dwvdata(dev);
	int eww;

	eww = tegwa_dma_init_hw(tdma);
	if (eww)
		wetuwn eww;

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static const stwuct dev_pm_ops tegwa_dma_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_dma_wuntime_suspend, tegwa_dma_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_dma_dev_suspend, tegwa_dma_dev_wesume)
};

static const stwuct of_device_id tegwa_dma_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa148-apbdma",
		.data = &tegwa148_dma_chip_data,
	}, {
		.compatibwe = "nvidia,tegwa114-apbdma",
		.data = &tegwa114_dma_chip_data,
	}, {
		.compatibwe = "nvidia,tegwa30-apbdma",
		.data = &tegwa30_dma_chip_data,
	}, {
		.compatibwe = "nvidia,tegwa20-apbdma",
		.data = &tegwa20_dma_chip_data,
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, tegwa_dma_of_match);

static stwuct pwatfowm_dwivew tegwa_dmac_dwivew = {
	.dwivew = {
		.name	= "tegwa-apbdma",
		.pm	= &tegwa_dma_dev_pm_ops,
		.of_match_tabwe = tegwa_dma_of_match,
	},
	.pwobe		= tegwa_dma_pwobe,
	.wemove_new	= tegwa_dma_wemove,
};

moduwe_pwatfowm_dwivew(tegwa_dmac_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa APB DMA Contwowwew dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
