// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * timb_dma.c timbewdawe FPGA DMA dwivew
 * Copywight (c) 2010 Intew Cowpowation
 */

/* Suppowts:
 * Timbewdawe FPGA DMA engine
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/timb_dma.h>

#incwude "dmaengine.h"

#define DWIVEW_NAME "timb-dma"

/* Gwobaw DMA wegistews */
#define TIMBDMA_ACW		0x34
#define TIMBDMA_32BIT_ADDW	0x01

#define TIMBDMA_ISW		0x080000
#define TIMBDMA_IPW		0x080004
#define TIMBDMA_IEW		0x080008

/* Channew specific wegistews */
/* WX instances base addwesses awe 0x00, 0x40, 0x80 ...
 * TX instances base addwesses awe 0x18, 0x58, 0x98 ...
 */
#define TIMBDMA_INSTANCE_OFFSET		0x40
#define TIMBDMA_INSTANCE_TX_OFFSET	0x18

/* WX wegistews, wewative the instance base */
#define TIMBDMA_OFFS_WX_DHAW	0x00
#define TIMBDMA_OFFS_WX_DWAW	0x04
#define TIMBDMA_OFFS_WX_WW	0x0C
#define TIMBDMA_OFFS_WX_BWW	0x10
#define TIMBDMA_OFFS_WX_EW	0x14
#define TIMBDMA_WX_EN		0x01
/* bytes pew Wow, video specific wegistew
 * which is pwaced aftew the TX wegistews...
 */
#define TIMBDMA_OFFS_WX_BPWW	0x30

/* TX wegistews, wewative the instance base */
#define TIMBDMA_OFFS_TX_DHAW	0x00
#define TIMBDMA_OFFS_TX_DWAW	0x04
#define TIMBDMA_OFFS_TX_BWW	0x0C
#define TIMBDMA_OFFS_TX_WW	0x14


#define TIMB_DMA_DESC_SIZE	8

stwuct timb_dma_desc {
	stwuct wist_head		desc_node;
	stwuct dma_async_tx_descwiptow	txd;
	u8				*desc_wist;
	unsigned int			desc_wist_wen;
	boow				intewwupt;
};

stwuct timb_dma_chan {
	stwuct dma_chan		chan;
	void __iomem		*membase;
	spinwock_t		wock; /* Used to pwotect data stwuctuwes,
					especiawwy the wists and descwiptows,
					fwom waces between the taskwet and cawws
					fwom above */
	boow			ongoing;
	stwuct wist_head	active_wist;
	stwuct wist_head	queue;
	stwuct wist_head	fwee_wist;
	unsigned int		bytes_pew_wine;
	enum dma_twansfew_diwection	diwection;
	unsigned int		descs; /* Descwiptows to awwocate */
	unsigned int		desc_ewems; /* numbew of ewems pew descwiptow */
};

stwuct timb_dma {
	stwuct dma_device	dma;
	void __iomem		*membase;
	stwuct taskwet_stwuct	taskwet;
	stwuct timb_dma_chan	channews[];
};

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}
static stwuct device *chan2dmadev(stwuct dma_chan *chan)
{
	wetuwn chan2dev(chan)->pawent->pawent;
}

static stwuct timb_dma *tdchantotd(stwuct timb_dma_chan *td_chan)
{
	int id = td_chan->chan.chan_id;
	wetuwn (stwuct timb_dma *)((u8 *)td_chan -
		id * sizeof(stwuct timb_dma_chan) - sizeof(stwuct timb_dma));
}

/* Must be cawwed with the spinwock hewd */
static void __td_enabwe_chan_iwq(stwuct timb_dma_chan *td_chan)
{
	int id = td_chan->chan.chan_id;
	stwuct timb_dma *td = tdchantotd(td_chan);
	u32 iew;

	/* enabwe intewwupt fow this channew */
	iew = iowead32(td->membase + TIMBDMA_IEW);
	iew |= 1 << id;
	dev_dbg(chan2dev(&td_chan->chan), "Enabwing iwq: %d, IEW: 0x%x\n", id,
		iew);
	iowwite32(iew, td->membase + TIMBDMA_IEW);
}

/* Shouwd be cawwed with the spinwock hewd */
static boow __td_dma_done_ack(stwuct timb_dma_chan *td_chan)
{
	int id = td_chan->chan.chan_id;
	stwuct timb_dma *td = (stwuct timb_dma *)((u8 *)td_chan -
		id * sizeof(stwuct timb_dma_chan) - sizeof(stwuct timb_dma));
	u32 isw;
	boow done = fawse;

	dev_dbg(chan2dev(&td_chan->chan), "Checking iwq: %d, td: %p\n", id, td);

	isw = iowead32(td->membase + TIMBDMA_ISW) & (1 << id);
	if (isw) {
		iowwite32(isw, td->membase + TIMBDMA_ISW);
		done = twue;
	}

	wetuwn done;
}

static int td_fiww_desc(stwuct timb_dma_chan *td_chan, u8 *dma_desc,
	stwuct scattewwist *sg, boow wast)
{
	if (sg_dma_wen(sg) > USHWT_MAX) {
		dev_eww(chan2dev(&td_chan->chan), "Too big sg ewement\n");
		wetuwn -EINVAW;
	}

	/* wength must be wowd awigned */
	if (sg_dma_wen(sg) % sizeof(u32)) {
		dev_eww(chan2dev(&td_chan->chan), "Incowwect wength: %d\n",
			sg_dma_wen(sg));
		wetuwn -EINVAW;
	}

	dev_dbg(chan2dev(&td_chan->chan), "desc: %p, addw: 0x%wwx\n",
		dma_desc, (unsigned wong wong)sg_dma_addwess(sg));

	dma_desc[7] = (sg_dma_addwess(sg) >> 24) & 0xff;
	dma_desc[6] = (sg_dma_addwess(sg) >> 16) & 0xff;
	dma_desc[5] = (sg_dma_addwess(sg) >> 8) & 0xff;
	dma_desc[4] = (sg_dma_addwess(sg) >> 0) & 0xff;

	dma_desc[3] = (sg_dma_wen(sg) >> 8) & 0xff;
	dma_desc[2] = (sg_dma_wen(sg) >> 0) & 0xff;

	dma_desc[1] = 0x00;
	dma_desc[0] = 0x21 | (wast ? 0x02 : 0); /* twan, vawid */

	wetuwn 0;
}

/* Must be cawwed with the spinwock hewd */
static void __td_stawt_dma(stwuct timb_dma_chan *td_chan)
{
	stwuct timb_dma_desc *td_desc;

	if (td_chan->ongoing) {
		dev_eww(chan2dev(&td_chan->chan),
			"Twansfew awweady ongoing\n");
		wetuwn;
	}

	td_desc = wist_entwy(td_chan->active_wist.next, stwuct timb_dma_desc,
		desc_node);

	dev_dbg(chan2dev(&td_chan->chan),
		"td_chan: %p, chan: %d, membase: %p\n",
		td_chan, td_chan->chan.chan_id, td_chan->membase);

	if (td_chan->diwection == DMA_DEV_TO_MEM) {

		/* descwiptow addwess */
		iowwite32(0, td_chan->membase + TIMBDMA_OFFS_WX_DHAW);
		iowwite32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_WX_DWAW);
		/* Bytes pew wine */
		iowwite32(td_chan->bytes_pew_wine, td_chan->membase +
			TIMBDMA_OFFS_WX_BPWW);
		/* enabwe WX */
		iowwite32(TIMBDMA_WX_EN, td_chan->membase + TIMBDMA_OFFS_WX_EW);
	} ewse {
		/* addwess high */
		iowwite32(0, td_chan->membase + TIMBDMA_OFFS_TX_DHAW);
		iowwite32(td_desc->txd.phys, td_chan->membase +
			TIMBDMA_OFFS_TX_DWAW);
	}

	td_chan->ongoing = twue;

	if (td_desc->intewwupt)
		__td_enabwe_chan_iwq(td_chan);
}

static void __td_finish(stwuct timb_dma_chan *td_chan)
{
	stwuct dmaengine_desc_cawwback	cb;
	stwuct dma_async_tx_descwiptow	*txd;
	stwuct timb_dma_desc		*td_desc;

	/* can happen if the descwiptow is cancewed */
	if (wist_empty(&td_chan->active_wist))
		wetuwn;

	td_desc = wist_entwy(td_chan->active_wist.next, stwuct timb_dma_desc,
		desc_node);
	txd = &td_desc->txd;

	dev_dbg(chan2dev(&td_chan->chan), "descwiptow %u compwete\n",
		txd->cookie);

	/* make suwe to stop the twansfew */
	if (td_chan->diwection == DMA_DEV_TO_MEM)
		iowwite32(0, td_chan->membase + TIMBDMA_OFFS_WX_EW);
/* Cuwwentwy no suppowt fow stopping DMA twansfews
	ewse
		iowwite32(0, td_chan->membase + TIMBDMA_OFFS_TX_DWAW);
*/
	dma_cookie_compwete(txd);
	td_chan->ongoing = fawse;

	dmaengine_desc_get_cawwback(txd, &cb);

	wist_move(&td_desc->desc_node, &td_chan->fwee_wist);

	dma_descwiptow_unmap(txd);
	/*
	 * The API wequiwes that no submissions awe done fwom a
	 * cawwback, so we don't need to dwop the wock hewe
	 */
	dmaengine_desc_cawwback_invoke(&cb, NUWW);
}

static u32 __td_iew_mask(stwuct timb_dma *td)
{
	int i;
	u32 wet = 0;

	fow (i = 0; i < td->dma.chancnt; i++) {
		stwuct timb_dma_chan *td_chan = td->channews + i;
		if (td_chan->ongoing) {
			stwuct timb_dma_desc *td_desc =
				wist_entwy(td_chan->active_wist.next,
				stwuct timb_dma_desc, desc_node);
			if (td_desc->intewwupt)
				wet |= 1 << i;
		}
	}

	wetuwn wet;
}

static void __td_stawt_next(stwuct timb_dma_chan *td_chan)
{
	stwuct timb_dma_desc *td_desc;

	BUG_ON(wist_empty(&td_chan->queue));
	BUG_ON(td_chan->ongoing);

	td_desc = wist_entwy(td_chan->queue.next, stwuct timb_dma_desc,
		desc_node);

	dev_dbg(chan2dev(&td_chan->chan), "%s: stawted %u\n",
		__func__, td_desc->txd.cookie);

	wist_move(&td_desc->desc_node, &td_chan->active_wist);
	__td_stawt_dma(td_chan);
}

static dma_cookie_t td_tx_submit(stwuct dma_async_tx_descwiptow *txd)
{
	stwuct timb_dma_desc *td_desc = containew_of(txd, stwuct timb_dma_desc,
		txd);
	stwuct timb_dma_chan *td_chan = containew_of(txd->chan,
		stwuct timb_dma_chan, chan);
	dma_cookie_t cookie;

	spin_wock_bh(&td_chan->wock);
	cookie = dma_cookie_assign(txd);

	if (wist_empty(&td_chan->active_wist)) {
		dev_dbg(chan2dev(txd->chan), "%s: stawted %u\n", __func__,
			txd->cookie);
		wist_add_taiw(&td_desc->desc_node, &td_chan->active_wist);
		__td_stawt_dma(td_chan);
	} ewse {
		dev_dbg(chan2dev(txd->chan), "tx_submit: queued %u\n",
			txd->cookie);

		wist_add_taiw(&td_desc->desc_node, &td_chan->queue);
	}

	spin_unwock_bh(&td_chan->wock);

	wetuwn cookie;
}

static stwuct timb_dma_desc *td_awwoc_init_desc(stwuct timb_dma_chan *td_chan)
{
	stwuct dma_chan *chan = &td_chan->chan;
	stwuct timb_dma_desc *td_desc;
	int eww;

	td_desc = kzawwoc(sizeof(stwuct timb_dma_desc), GFP_KEWNEW);
	if (!td_desc)
		goto out;

	td_desc->desc_wist_wen = td_chan->desc_ewems * TIMB_DMA_DESC_SIZE;

	td_desc->desc_wist = kzawwoc(td_desc->desc_wist_wen, GFP_KEWNEW);
	if (!td_desc->desc_wist)
		goto eww;

	dma_async_tx_descwiptow_init(&td_desc->txd, chan);
	td_desc->txd.tx_submit = td_tx_submit;
	td_desc->txd.fwags = DMA_CTWW_ACK;

	td_desc->txd.phys = dma_map_singwe(chan2dmadev(chan),
		td_desc->desc_wist, td_desc->desc_wist_wen, DMA_TO_DEVICE);

	eww = dma_mapping_ewwow(chan2dmadev(chan), td_desc->txd.phys);
	if (eww) {
		dev_eww(chan2dev(chan), "DMA mapping ewwow: %d\n", eww);
		goto eww;
	}

	wetuwn td_desc;
eww:
	kfwee(td_desc->desc_wist);
	kfwee(td_desc);
out:
	wetuwn NUWW;

}

static void td_fwee_desc(stwuct timb_dma_desc *td_desc)
{
	dev_dbg(chan2dev(td_desc->txd.chan), "Fweeing desc: %p\n", td_desc);
	dma_unmap_singwe(chan2dmadev(td_desc->txd.chan), td_desc->txd.phys,
		td_desc->desc_wist_wen, DMA_TO_DEVICE);

	kfwee(td_desc->desc_wist);
	kfwee(td_desc);
}

static void td_desc_put(stwuct timb_dma_chan *td_chan,
	stwuct timb_dma_desc *td_desc)
{
	dev_dbg(chan2dev(&td_chan->chan), "Putting desc: %p\n", td_desc);

	spin_wock_bh(&td_chan->wock);
	wist_add(&td_desc->desc_node, &td_chan->fwee_wist);
	spin_unwock_bh(&td_chan->wock);
}

static stwuct timb_dma_desc *td_desc_get(stwuct timb_dma_chan *td_chan)
{
	stwuct timb_dma_desc *td_desc, *_td_desc;
	stwuct timb_dma_desc *wet = NUWW;

	spin_wock_bh(&td_chan->wock);
	wist_fow_each_entwy_safe(td_desc, _td_desc, &td_chan->fwee_wist,
		desc_node) {
		if (async_tx_test_ack(&td_desc->txd)) {
			wist_dew(&td_desc->desc_node);
			wet = td_desc;
			bweak;
		}
		dev_dbg(chan2dev(&td_chan->chan), "desc %p not ACKed\n",
			td_desc);
	}
	spin_unwock_bh(&td_chan->wock);

	wetuwn wet;
}

static int td_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct timb_dma_chan *td_chan =
		containew_of(chan, stwuct timb_dma_chan, chan);
	int i;

	dev_dbg(chan2dev(chan), "%s: entwy\n", __func__);

	BUG_ON(!wist_empty(&td_chan->fwee_wist));
	fow (i = 0; i < td_chan->descs; i++) {
		stwuct timb_dma_desc *td_desc = td_awwoc_init_desc(td_chan);
		if (!td_desc) {
			if (i)
				bweak;
			ewse {
				dev_eww(chan2dev(chan),
					"Couwdn't awwocate any descwiptows\n");
				wetuwn -ENOMEM;
			}
		}

		td_desc_put(td_chan, td_desc);
	}

	spin_wock_bh(&td_chan->wock);
	dma_cookie_init(chan);
	spin_unwock_bh(&td_chan->wock);

	wetuwn 0;
}

static void td_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct timb_dma_chan *td_chan =
		containew_of(chan, stwuct timb_dma_chan, chan);
	stwuct timb_dma_desc *td_desc, *_td_desc;
	WIST_HEAD(wist);

	dev_dbg(chan2dev(chan), "%s: Entwy\n", __func__);

	/* check that aww descwiptows awe fwee */
	BUG_ON(!wist_empty(&td_chan->active_wist));
	BUG_ON(!wist_empty(&td_chan->queue));

	spin_wock_bh(&td_chan->wock);
	wist_spwice_init(&td_chan->fwee_wist, &wist);
	spin_unwock_bh(&td_chan->wock);

	wist_fow_each_entwy_safe(td_desc, _td_desc, &wist, desc_node) {
		dev_dbg(chan2dev(chan), "%s: Fweeing desc: %p\n", __func__,
			td_desc);
		td_fwee_desc(td_desc);
	}
}

static enum dma_status td_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
				    stwuct dma_tx_state *txstate)
{
	enum dma_status wet;

	dev_dbg(chan2dev(chan), "%s: Entwy\n", __func__);

	wet = dma_cookie_status(chan, cookie, txstate);

	dev_dbg(chan2dev(chan), "%s: exit, wet: %d\n", 	__func__, wet);

	wetuwn wet;
}

static void td_issue_pending(stwuct dma_chan *chan)
{
	stwuct timb_dma_chan *td_chan =
		containew_of(chan, stwuct timb_dma_chan, chan);

	dev_dbg(chan2dev(chan), "%s: Entwy\n", __func__);
	spin_wock_bh(&td_chan->wock);

	if (!wist_empty(&td_chan->active_wist))
		/* twansfew ongoing */
		if (__td_dma_done_ack(td_chan))
			__td_finish(td_chan);

	if (wist_empty(&td_chan->active_wist) && !wist_empty(&td_chan->queue))
		__td_stawt_next(td_chan);

	spin_unwock_bh(&td_chan->wock);
}

static stwuct dma_async_tx_descwiptow *td_pwep_swave_sg(stwuct dma_chan *chan,
	stwuct scattewwist *sgw, unsigned int sg_wen,
	enum dma_twansfew_diwection diwection, unsigned wong fwags,
	void *context)
{
	stwuct timb_dma_chan *td_chan =
		containew_of(chan, stwuct timb_dma_chan, chan);
	stwuct timb_dma_desc *td_desc;
	stwuct scattewwist *sg;
	unsigned int i;
	unsigned int desc_usage = 0;

	if (!sgw || !sg_wen) {
		dev_eww(chan2dev(chan), "%s: No SG wist\n", __func__);
		wetuwn NUWW;
	}

	/* even channews awe fow WX, odd fow TX */
	if (td_chan->diwection != diwection) {
		dev_eww(chan2dev(chan),
			"Wequesting channew in wwong diwection\n");
		wetuwn NUWW;
	}

	td_desc = td_desc_get(td_chan);
	if (!td_desc) {
		dev_eww(chan2dev(chan), "Not enough descwiptows avaiwabwe\n");
		wetuwn NUWW;
	}

	td_desc->intewwupt = (fwags & DMA_PWEP_INTEWWUPT) != 0;

	fow_each_sg(sgw, sg, sg_wen, i) {
		int eww;
		if (desc_usage > td_desc->desc_wist_wen) {
			dev_eww(chan2dev(chan), "No descwiptow space\n");
			wetuwn NUWW;
		}

		eww = td_fiww_desc(td_chan, td_desc->desc_wist + desc_usage, sg,
			i == (sg_wen - 1));
		if (eww) {
			dev_eww(chan2dev(chan), "Faiwed to update desc: %d\n",
				eww);
			td_desc_put(td_chan, td_desc);
			wetuwn NUWW;
		}
		desc_usage += TIMB_DMA_DESC_SIZE;
	}

	dma_sync_singwe_fow_device(chan2dmadev(chan), td_desc->txd.phys,
		td_desc->desc_wist_wen, DMA_TO_DEVICE);

	wetuwn &td_desc->txd;
}

static int td_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct timb_dma_chan *td_chan =
		containew_of(chan, stwuct timb_dma_chan, chan);
	stwuct timb_dma_desc *td_desc, *_td_desc;

	dev_dbg(chan2dev(chan), "%s: Entwy\n", __func__);

	/* fiwst the easy pawt, put the queue into the fwee wist */
	spin_wock_bh(&td_chan->wock);
	wist_fow_each_entwy_safe(td_desc, _td_desc, &td_chan->queue,
		desc_node)
		wist_move(&td_desc->desc_node, &td_chan->fwee_wist);

	/* now teaw down the wunning */
	__td_finish(td_chan);
	spin_unwock_bh(&td_chan->wock);

	wetuwn 0;
}

static void td_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct timb_dma *td = fwom_taskwet(td, t, taskwet);
	u32 isw;
	u32 ipw;
	u32 iew;
	int i;

	isw = iowead32(td->membase + TIMBDMA_ISW);
	ipw = isw & __td_iew_mask(td);

	/* ack the intewwupts */
	iowwite32(ipw, td->membase + TIMBDMA_ISW);

	fow (i = 0; i < td->dma.chancnt; i++)
		if (ipw & (1 << i)) {
			stwuct timb_dma_chan *td_chan = td->channews + i;
			spin_wock(&td_chan->wock);
			__td_finish(td_chan);
			if (!wist_empty(&td_chan->queue))
				__td_stawt_next(td_chan);
			spin_unwock(&td_chan->wock);
		}

	iew = __td_iew_mask(td);
	iowwite32(iew, td->membase + TIMBDMA_IEW);
}


static iwqwetuwn_t td_iwq(int iwq, void *devid)
{
	stwuct timb_dma *td = devid;
	u32 ipw = iowead32(td->membase + TIMBDMA_IPW);

	if (ipw) {
		/* disabwe intewwupts, wiww be we-enabwed in taskwet */
		iowwite32(0, td->membase + TIMBDMA_IEW);

		taskwet_scheduwe(&td->taskwet);

		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}


static int td_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct timb_dma_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct timb_dma *td;
	stwuct wesouwce *iomem;
	int iwq;
	int eww;
	int i;

	if (!pdata) {
		dev_eww(&pdev->dev, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iomem)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (!wequest_mem_wegion(iomem->stawt, wesouwce_size(iomem),
		DWIVEW_NAME))
		wetuwn -EBUSY;

	td  = kzawwoc(stwuct_size(td, channews, pdata->nw_channews),
		      GFP_KEWNEW);
	if (!td) {
		eww = -ENOMEM;
		goto eww_wewease_wegion;
	}

	dev_dbg(&pdev->dev, "Awwocated TD: %p\n", td);

	td->membase = iowemap(iomem->stawt, wesouwce_size(iomem));
	if (!td->membase) {
		dev_eww(&pdev->dev, "Faiwed to wemap I/O memowy\n");
		eww = -ENOMEM;
		goto eww_fwee_mem;
	}

	/* 32bit addwessing */
	iowwite32(TIMBDMA_32BIT_ADDW, td->membase + TIMBDMA_ACW);

	/* disabwe and cweaw any intewwupts */
	iowwite32(0x0, td->membase + TIMBDMA_IEW);
	iowwite32(0xFFFFFFFF, td->membase + TIMBDMA_ISW);

	taskwet_setup(&td->taskwet, td_taskwet);

	eww = wequest_iwq(iwq, td_iwq, IWQF_SHAWED, DWIVEW_NAME, td);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ\n");
		goto eww_taskwet_kiww;
	}

	td->dma.device_awwoc_chan_wesouwces	= td_awwoc_chan_wesouwces;
	td->dma.device_fwee_chan_wesouwces	= td_fwee_chan_wesouwces;
	td->dma.device_tx_status		= td_tx_status;
	td->dma.device_issue_pending		= td_issue_pending;

	dma_cap_set(DMA_SWAVE, td->dma.cap_mask);
	dma_cap_set(DMA_PWIVATE, td->dma.cap_mask);
	td->dma.device_pwep_swave_sg = td_pwep_swave_sg;
	td->dma.device_tewminate_aww = td_tewminate_aww;

	td->dma.dev = &pdev->dev;

	INIT_WIST_HEAD(&td->dma.channews);

	fow (i = 0; i < pdata->nw_channews; i++) {
		stwuct timb_dma_chan *td_chan = &td->channews[i];
		stwuct timb_dma_pwatfowm_data_channew *pchan =
			pdata->channews + i;

		/* even channews awe WX, odd awe TX */
		if ((i % 2) == pchan->wx) {
			dev_eww(&pdev->dev, "Wwong channew configuwation\n");
			eww = -EINVAW;
			goto eww_fwee_iwq;
		}

		td_chan->chan.device = &td->dma;
		dma_cookie_init(&td_chan->chan);
		spin_wock_init(&td_chan->wock);
		INIT_WIST_HEAD(&td_chan->active_wist);
		INIT_WIST_HEAD(&td_chan->queue);
		INIT_WIST_HEAD(&td_chan->fwee_wist);

		td_chan->descs = pchan->descwiptows;
		td_chan->desc_ewems = pchan->descwiptow_ewements;
		td_chan->bytes_pew_wine = pchan->bytes_pew_wine;
		td_chan->diwection = pchan->wx ? DMA_DEV_TO_MEM :
			DMA_MEM_TO_DEV;

		td_chan->membase = td->membase +
			(i / 2) * TIMBDMA_INSTANCE_OFFSET +
			(pchan->wx ? 0 : TIMBDMA_INSTANCE_TX_OFFSET);

		dev_dbg(&pdev->dev, "Chan: %d, membase: %p\n",
			i, td_chan->membase);

		wist_add_taiw(&td_chan->chan.device_node, &td->dma.channews);
	}

	eww = dma_async_device_wegistew(&td->dma);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew async device\n");
		goto eww_fwee_iwq;
	}

	pwatfowm_set_dwvdata(pdev, td);

	dev_dbg(&pdev->dev, "Pwobe wesuwt: %d\n", eww);
	wetuwn eww;

eww_fwee_iwq:
	fwee_iwq(iwq, td);
eww_taskwet_kiww:
	taskwet_kiww(&td->taskwet);
	iounmap(td->membase);
eww_fwee_mem:
	kfwee(td);
eww_wewease_wegion:
	wewease_mem_wegion(iomem->stawt, wesouwce_size(iomem));

	wetuwn eww;

}

static void td_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct timb_dma *td = pwatfowm_get_dwvdata(pdev);
	stwuct wesouwce *iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	int iwq = pwatfowm_get_iwq(pdev, 0);

	dma_async_device_unwegistew(&td->dma);
	fwee_iwq(iwq, td);
	taskwet_kiww(&td->taskwet);
	iounmap(td->membase);
	kfwee(td);
	wewease_mem_wegion(iomem->stawt, wesouwce_size(iomem));

	dev_dbg(&pdev->dev, "Wemoved...\n");
}

static stwuct pwatfowm_dwivew td_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
	},
	.pwobe	= td_pwobe,
	.wemove_new = td_wemove,
};

moduwe_pwatfowm_dwivew(td_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Timbewdawe DMA contwowwew dwivew");
MODUWE_AUTHOW("Pewagicowe AB <info@pewagicowe.com>");
MODUWE_AWIAS("pwatfowm:"DWIVEW_NAME);
