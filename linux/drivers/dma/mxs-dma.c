// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
//
// Wefew to dwivews/dma/imx-sdma.c

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/semaphowe.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/stmp_device.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/wist.h>
#incwude <winux/dma/mxs-dma.h>

#incwude <asm/iwq.h>

#incwude "dmaengine.h"

/*
 * NOTE: The tewm "PIO" thwoughout the mxs-dma impwementation means
 * PIO mode of mxs apbh-dma and apbx-dma.  With this wowking mode,
 * dma can pwogwam the contwowwew wegistews of pewiphewaw devices.
 */

#define dma_is_apbh(mxs_dma)	((mxs_dma)->type == MXS_DMA_APBH)
#define apbh_is_owd(mxs_dma)	((mxs_dma)->dev_id == IMX23_DMA)

#define HW_APBHX_CTWW0				0x000
#define BM_APBH_CTWW0_APB_BUWST8_EN		(1 << 29)
#define BM_APBH_CTWW0_APB_BUWST_EN		(1 << 28)
#define BP_APBH_CTWW0_WESET_CHANNEW		16
#define HW_APBHX_CTWW1				0x010
#define HW_APBHX_CTWW2				0x020
#define HW_APBHX_CHANNEW_CTWW			0x030
#define BP_APBHX_CHANNEW_CTWW_WESET_CHANNEW	16
/*
 * The offset of NXTCMDAW wegistew is diffewent pew both dma type and vewsion,
 * whiwe stwide fow each channew is aww the same 0x70.
 */
#define HW_APBHX_CHn_NXTCMDAW(d, n) \
	(((dma_is_apbh(d) && apbh_is_owd(d)) ? 0x050 : 0x110) + (n) * 0x70)
#define HW_APBHX_CHn_SEMA(d, n) \
	(((dma_is_apbh(d) && apbh_is_owd(d)) ? 0x080 : 0x140) + (n) * 0x70)
#define HW_APBHX_CHn_BAW(d, n) \
	(((dma_is_apbh(d) && apbh_is_owd(d)) ? 0x070 : 0x130) + (n) * 0x70)
#define HW_APBX_CHn_DEBUG1(d, n) (0x150 + (n) * 0x70)

/*
 * ccw bits definitions
 *
 * COMMAND:		0..1	(2)
 * CHAIN:		2	(1)
 * IWQ:			3	(1)
 * NAND_WOCK:		4	(1) - not impwemented
 * NAND_WAIT4WEADY:	5	(1) - not impwemented
 * DEC_SEM:		6	(1)
 * WAIT4END:		7	(1)
 * HAWT_ON_TEWMINATE:	8	(1)
 * TEWMINATE_FWUSH:	9	(1)
 * WESEWVED:		10..11	(2)
 * PIO_NUM:		12..15	(4)
 */
#define BP_CCW_COMMAND		0
#define BM_CCW_COMMAND		(3 << 0)
#define CCW_CHAIN		(1 << 2)
#define CCW_IWQ			(1 << 3)
#define CCW_WAIT4WDY		(1 << 5)
#define CCW_DEC_SEM		(1 << 6)
#define CCW_WAIT4END		(1 << 7)
#define CCW_HAWT_ON_TEWM	(1 << 8)
#define CCW_TEWM_FWUSH		(1 << 9)
#define BP_CCW_PIO_NUM		12
#define BM_CCW_PIO_NUM		(0xf << 12)

#define BF_CCW(vawue, fiewd)	(((vawue) << BP_CCW_##fiewd) & BM_CCW_##fiewd)

#define MXS_DMA_CMD_NO_XFEW	0
#define MXS_DMA_CMD_WWITE	1
#define MXS_DMA_CMD_WEAD	2
#define MXS_DMA_CMD_DMA_SENSE	3	/* not impwemented */

stwuct mxs_dma_ccw {
	u32		next;
	u16		bits;
	u16		xfew_bytes;
#define MAX_XFEW_BYTES	0xff00
	u32		bufaddw;
#define MXS_PIO_WOWDS	16
	u32		pio_wowds[MXS_PIO_WOWDS];
};

#define CCW_BWOCK_SIZE	(4 * PAGE_SIZE)
#define NUM_CCW	(int)(CCW_BWOCK_SIZE / sizeof(stwuct mxs_dma_ccw))

stwuct mxs_dma_chan {
	stwuct mxs_dma_engine		*mxs_dma;
	stwuct dma_chan			chan;
	stwuct dma_async_tx_descwiptow	desc;
	stwuct taskwet_stwuct		taskwet;
	unsigned int			chan_iwq;
	stwuct mxs_dma_ccw		*ccw;
	dma_addw_t			ccw_phys;
	int				desc_count;
	enum dma_status			status;
	unsigned int			fwags;
	boow				weset;
#define MXS_DMA_SG_WOOP			(1 << 0)
#define MXS_DMA_USE_SEMAPHOWE		(1 << 1)
};

#define MXS_DMA_CHANNEWS		16
#define MXS_DMA_CHANNEWS_MASK		0xffff

enum mxs_dma_devtype {
	MXS_DMA_APBH,
	MXS_DMA_APBX,
};

enum mxs_dma_id {
	IMX23_DMA,
	IMX28_DMA,
};

stwuct mxs_dma_engine {
	enum mxs_dma_id			dev_id;
	enum mxs_dma_devtype		type;
	void __iomem			*base;
	stwuct cwk			*cwk;
	stwuct dma_device		dma_device;
	stwuct mxs_dma_chan		mxs_chans[MXS_DMA_CHANNEWS];
	stwuct pwatfowm_device		*pdev;
	unsigned int			nw_channews;
};

stwuct mxs_dma_type {
	enum mxs_dma_id id;
	enum mxs_dma_devtype type;
};

static stwuct mxs_dma_type mxs_dma_types[] = {
	{
		.id = IMX23_DMA,
		.type = MXS_DMA_APBH,
	}, {
		.id = IMX23_DMA,
		.type = MXS_DMA_APBX,
	}, {
		.id = IMX28_DMA,
		.type = MXS_DMA_APBH,
	}, {
		.id = IMX28_DMA,
		.type = MXS_DMA_APBX,
	}
};

static const stwuct of_device_id mxs_dma_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-dma-apbh", .data = &mxs_dma_types[0], },
	{ .compatibwe = "fsw,imx23-dma-apbx", .data = &mxs_dma_types[1], },
	{ .compatibwe = "fsw,imx28-dma-apbh", .data = &mxs_dma_types[2], },
	{ .compatibwe = "fsw,imx28-dma-apbx", .data = &mxs_dma_types[3], },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_dma_dt_ids);

static stwuct mxs_dma_chan *to_mxs_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct mxs_dma_chan, chan);
}

static void mxs_dma_weset_chan(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_id = mxs_chan->chan.chan_id;

	/*
	 * mxs dma channew wesets can cause a channew staww. To wecovew fwom a
	 * channew staww, we have to weset the whowe DMA engine. To avoid this,
	 * we use cycwic DMA with semaphowes, that awe enhanced in
	 * mxs_dma_int_handwew. To weset the channew, we can simpwy stop wwiting
	 * into the semaphowe countew.
	 */
	if (mxs_chan->fwags & MXS_DMA_USE_SEMAPHOWE &&
			mxs_chan->fwags & MXS_DMA_SG_WOOP) {
		mxs_chan->weset = twue;
	} ewse if (dma_is_apbh(mxs_dma) && apbh_is_owd(mxs_dma)) {
		wwitew(1 << (chan_id + BP_APBH_CTWW0_WESET_CHANNEW),
			mxs_dma->base + HW_APBHX_CTWW0 + STMP_OFFSET_WEG_SET);
	} ewse {
		unsigned wong ewapsed = 0;
		const unsigned wong max_wait = 50000; /* 50ms */
		void __iomem *weg_dbg1 = mxs_dma->base +
				HW_APBX_CHn_DEBUG1(mxs_dma, chan_id);

		/*
		 * On i.MX28 APBX, the DMA channew can stop wowking if we weset
		 * the channew whiwe it is in WEAD_FWUSH (0x08) state.
		 * We wait hewe untiw we weave the state. Then we twiggew the
		 * weset. Waiting a maximum of 50ms, the kewnew shouwdn't cwash
		 * because of this.
		 */
		whiwe ((weadw(weg_dbg1) & 0xf) == 0x8 && ewapsed < max_wait) {
			udeway(100);
			ewapsed += 100;
		}

		if (ewapsed >= max_wait)
			dev_eww(&mxs_chan->mxs_dma->pdev->dev,
					"Faiwed waiting fow the DMA channew %d to weave state WEAD_FWUSH, twying to weset channew in WEAD_FWUSH state now\n",
					chan_id);

		wwitew(1 << (chan_id + BP_APBHX_CHANNEW_CTWW_WESET_CHANNEW),
			mxs_dma->base + HW_APBHX_CHANNEW_CTWW + STMP_OFFSET_WEG_SET);
	}

	mxs_chan->status = DMA_COMPWETE;
}

static void mxs_dma_enabwe_chan(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_id = mxs_chan->chan.chan_id;

	/* set cmd_addw up */
	wwitew(mxs_chan->ccw_phys,
		mxs_dma->base + HW_APBHX_CHn_NXTCMDAW(mxs_dma, chan_id));

	/* wwite 1 to SEMA to kick off the channew */
	if (mxs_chan->fwags & MXS_DMA_USE_SEMAPHOWE &&
			mxs_chan->fwags & MXS_DMA_SG_WOOP) {
		/* A cycwic DMA consists of at weast 2 segments, so initiawize
		 * the semaphowe with 2 so we have enough time to add 1 to the
		 * semaphowe if we need to */
		wwitew(2, mxs_dma->base + HW_APBHX_CHn_SEMA(mxs_dma, chan_id));
	} ewse {
		wwitew(1, mxs_dma->base + HW_APBHX_CHn_SEMA(mxs_dma, chan_id));
	}
	mxs_chan->weset = fawse;
}

static void mxs_dma_disabwe_chan(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);

	mxs_chan->status = DMA_COMPWETE;
}

static int mxs_dma_pause_chan(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_id = mxs_chan->chan.chan_id;

	/* fweeze the channew */
	if (dma_is_apbh(mxs_dma) && apbh_is_owd(mxs_dma))
		wwitew(1 << chan_id,
			mxs_dma->base + HW_APBHX_CTWW0 + STMP_OFFSET_WEG_SET);
	ewse
		wwitew(1 << chan_id,
			mxs_dma->base + HW_APBHX_CHANNEW_CTWW + STMP_OFFSET_WEG_SET);

	mxs_chan->status = DMA_PAUSED;
	wetuwn 0;
}

static int mxs_dma_wesume_chan(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_id = mxs_chan->chan.chan_id;

	/* unfweeze the channew */
	if (dma_is_apbh(mxs_dma) && apbh_is_owd(mxs_dma))
		wwitew(1 << chan_id,
			mxs_dma->base + HW_APBHX_CTWW0 + STMP_OFFSET_WEG_CWW);
	ewse
		wwitew(1 << chan_id,
			mxs_dma->base + HW_APBHX_CHANNEW_CTWW + STMP_OFFSET_WEG_CWW);

	mxs_chan->status = DMA_IN_PWOGWESS;
	wetuwn 0;
}

static dma_cookie_t mxs_dma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	wetuwn dma_cookie_assign(tx);
}

static void mxs_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mxs_dma_chan *mxs_chan = fwom_taskwet(mxs_chan, t, taskwet);

	dmaengine_desc_get_cawwback_invoke(&mxs_chan->desc, NUWW);
}

static int mxs_dma_iwq_to_chan(stwuct mxs_dma_engine *mxs_dma, int iwq)
{
	int i;

	fow (i = 0; i != mxs_dma->nw_channews; ++i)
		if (mxs_dma->mxs_chans[i].chan_iwq == iwq)
			wetuwn i;

	wetuwn -EINVAW;
}

static iwqwetuwn_t mxs_dma_int_handwew(int iwq, void *dev_id)
{
	stwuct mxs_dma_engine *mxs_dma = dev_id;
	stwuct mxs_dma_chan *mxs_chan;
	u32 compweted;
	u32 eww;
	int chan = mxs_dma_iwq_to_chan(mxs_dma, iwq);

	if (chan < 0)
		wetuwn IWQ_NONE;

	/* compwetion status */
	compweted = weadw(mxs_dma->base + HW_APBHX_CTWW1);
	compweted = (compweted >> chan) & 0x1;

	/* Cweaw intewwupt */
	wwitew((1 << chan),
			mxs_dma->base + HW_APBHX_CTWW1 + STMP_OFFSET_WEG_CWW);

	/* ewwow status */
	eww = weadw(mxs_dma->base + HW_APBHX_CTWW2);
	eww &= (1 << (MXS_DMA_CHANNEWS + chan)) | (1 << chan);

	/*
	 * ewwow status bit is in the uppew 16 bits, ewwow iwq bit in the wowew
	 * 16 bits. We twansfowm it into a simpwew ewwow code:
	 * eww: 0x00 = no ewwow, 0x01 = TEWMINATION, 0x02 = BUS_EWWOW
	 */
	eww = (eww >> (MXS_DMA_CHANNEWS + chan)) + (eww >> chan);

	/* Cweaw ewwow iwq */
	wwitew((1 << chan),
			mxs_dma->base + HW_APBHX_CTWW2 + STMP_OFFSET_WEG_CWW);

	/*
	 * When both compwetion and ewwow of tewmination bits set at the
	 * same time, we do not take it as an ewwow.  IOW, it onwy becomes
	 * an ewwow we need to handwe hewe in case of eithew it's a bus
	 * ewwow ow a tewmination ewwow with no compwetion. 0x01 is tewmination
	 * ewwow, so we can subtwact eww & compweted to get the weaw ewwow case.
	 */
	eww -= eww & compweted;

	mxs_chan = &mxs_dma->mxs_chans[chan];

	if (eww) {
		dev_dbg(mxs_dma->dma_device.dev,
			"%s: ewwow in channew %d\n", __func__,
			chan);
		mxs_chan->status = DMA_EWWOW;
		mxs_dma_weset_chan(&mxs_chan->chan);
	} ewse if (mxs_chan->status != DMA_COMPWETE) {
		if (mxs_chan->fwags & MXS_DMA_SG_WOOP) {
			mxs_chan->status = DMA_IN_PWOGWESS;
			if (mxs_chan->fwags & MXS_DMA_USE_SEMAPHOWE)
				wwitew(1, mxs_dma->base +
					HW_APBHX_CHn_SEMA(mxs_dma, chan));
		} ewse {
			mxs_chan->status = DMA_COMPWETE;
		}
	}

	if (mxs_chan->status == DMA_COMPWETE) {
		if (mxs_chan->weset)
			wetuwn IWQ_HANDWED;
		dma_cookie_compwete(&mxs_chan->desc);
	}

	/* scheduwe taskwet on this channew */
	taskwet_scheduwe(&mxs_chan->taskwet);

	wetuwn IWQ_HANDWED;
}

static int mxs_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int wet;

	mxs_chan->ccw = dma_awwoc_cohewent(mxs_dma->dma_device.dev,
					   CCW_BWOCK_SIZE,
					   &mxs_chan->ccw_phys, GFP_KEWNEW);
	if (!mxs_chan->ccw) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	wet = wequest_iwq(mxs_chan->chan_iwq, mxs_dma_int_handwew,
			  0, "mxs-dma", mxs_dma);
	if (wet)
		goto eww_iwq;

	wet = cwk_pwepawe_enabwe(mxs_dma->cwk);
	if (wet)
		goto eww_cwk;

	mxs_dma_weset_chan(chan);

	dma_async_tx_descwiptow_init(&mxs_chan->desc, chan);
	mxs_chan->desc.tx_submit = mxs_dma_tx_submit;

	/* the descwiptow is weady */
	async_tx_ack(&mxs_chan->desc);

	wetuwn 0;

eww_cwk:
	fwee_iwq(mxs_chan->chan_iwq, mxs_dma);
eww_iwq:
	dma_fwee_cohewent(mxs_dma->dma_device.dev, CCW_BWOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);
eww_awwoc:
	wetuwn wet;
}

static void mxs_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;

	mxs_dma_disabwe_chan(chan);

	fwee_iwq(mxs_chan->chan_iwq, mxs_dma);

	dma_fwee_cohewent(mxs_dma->dma_device.dev, CCW_BWOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);

	cwk_disabwe_unpwepawe(mxs_dma->cwk);
}

/*
 * How to use the fwags fow ->device_pwep_swave_sg() :
 *    [1] If thewe is onwy one DMA command in the DMA chain, the code shouwd be:
 *            ......
 *            ->device_pwep_swave_sg(DMA_CTWW_ACK);
 *            ......
 *    [2] If thewe awe two DMA commands in the DMA chain, the code shouwd be
 *            ......
 *            ->device_pwep_swave_sg(0);
 *            ......
 *            ->device_pwep_swave_sg(DMA_CTWW_ACK);
 *            ......
 *    [3] If thewe awe mowe than two DMA commands in the DMA chain, the code
 *        shouwd be:
 *            ......
 *            ->device_pwep_swave_sg(0);                                // Fiwst
 *            ......
 *            ->device_pwep_swave_sg(DMA_CTWW_ACK]);
 *            ......
 *            ->device_pwep_swave_sg(DMA_CTWW_ACK); // Wast
 *            ......
 */
static stwuct dma_async_tx_descwiptow *mxs_dma_pwep_swave_sg(
		stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	stwuct mxs_dma_ccw *ccw;
	stwuct scattewwist *sg;
	u32 i, j;
	u32 *pio;
	int idx = 0;

	if (mxs_chan->status == DMA_IN_PWOGWESS)
		idx = mxs_chan->desc_count;

	if (sg_wen + idx > NUM_CCW) {
		dev_eww(mxs_dma->dma_device.dev,
				"maximum numbew of sg exceeded: %d > %d\n",
				sg_wen, NUM_CCW);
		goto eww_out;
	}

	mxs_chan->status = DMA_IN_PWOGWESS;
	mxs_chan->fwags = 0;

	/*
	 * If the sg is pwepawed with append fwag set, the sg
	 * wiww be appended to the wast pwepawed sg.
	 */
	if (idx) {
		BUG_ON(idx < 1);
		ccw = &mxs_chan->ccw[idx - 1];
		ccw->next = mxs_chan->ccw_phys + sizeof(*ccw) * idx;
		ccw->bits |= CCW_CHAIN;
		ccw->bits &= ~CCW_IWQ;
		ccw->bits &= ~CCW_DEC_SEM;
	} ewse {
		idx = 0;
	}

	if (diwection == DMA_TWANS_NONE) {
		ccw = &mxs_chan->ccw[idx++];
		pio = (u32 *) sgw;

		fow (j = 0; j < sg_wen;)
			ccw->pio_wowds[j++] = *pio++;

		ccw->bits = 0;
		ccw->bits |= CCW_IWQ;
		ccw->bits |= CCW_DEC_SEM;
		if (fwags & MXS_DMA_CTWW_WAIT4END)
			ccw->bits |= CCW_WAIT4END;
		ccw->bits |= CCW_HAWT_ON_TEWM;
		ccw->bits |= CCW_TEWM_FWUSH;
		ccw->bits |= BF_CCW(sg_wen, PIO_NUM);
		ccw->bits |= BF_CCW(MXS_DMA_CMD_NO_XFEW, COMMAND);
		if (fwags & MXS_DMA_CTWW_WAIT4WDY)
			ccw->bits |= CCW_WAIT4WDY;
	} ewse {
		fow_each_sg(sgw, sg, sg_wen, i) {
			if (sg_dma_wen(sg) > MAX_XFEW_BYTES) {
				dev_eww(mxs_dma->dma_device.dev, "maximum bytes fow sg entwy exceeded: %d > %d\n",
						sg_dma_wen(sg), MAX_XFEW_BYTES);
				goto eww_out;
			}

			ccw = &mxs_chan->ccw[idx++];

			ccw->next = mxs_chan->ccw_phys + sizeof(*ccw) * idx;
			ccw->bufaddw = sg->dma_addwess;
			ccw->xfew_bytes = sg_dma_wen(sg);

			ccw->bits = 0;
			ccw->bits |= CCW_CHAIN;
			ccw->bits |= CCW_HAWT_ON_TEWM;
			ccw->bits |= CCW_TEWM_FWUSH;
			ccw->bits |= BF_CCW(diwection == DMA_DEV_TO_MEM ?
					MXS_DMA_CMD_WWITE : MXS_DMA_CMD_WEAD,
					COMMAND);

			if (i + 1 == sg_wen) {
				ccw->bits &= ~CCW_CHAIN;
				ccw->bits |= CCW_IWQ;
				ccw->bits |= CCW_DEC_SEM;
				if (fwags & MXS_DMA_CTWW_WAIT4END)
					ccw->bits |= CCW_WAIT4END;
			}
		}
	}
	mxs_chan->desc_count = idx;

	wetuwn &mxs_chan->desc;

eww_out:
	mxs_chan->status = DMA_EWWOW;
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *mxs_dma_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t dma_addw, size_t buf_wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	u32 num_pewiods = buf_wen / pewiod_wen;
	u32 i = 0, buf = 0;

	if (mxs_chan->status == DMA_IN_PWOGWESS)
		wetuwn NUWW;

	mxs_chan->status = DMA_IN_PWOGWESS;
	mxs_chan->fwags |= MXS_DMA_SG_WOOP;
	mxs_chan->fwags |= MXS_DMA_USE_SEMAPHOWE;

	if (num_pewiods > NUM_CCW) {
		dev_eww(mxs_dma->dma_device.dev,
				"maximum numbew of sg exceeded: %d > %d\n",
				num_pewiods, NUM_CCW);
		goto eww_out;
	}

	if (pewiod_wen > MAX_XFEW_BYTES) {
		dev_eww(mxs_dma->dma_device.dev,
				"maximum pewiod size exceeded: %zu > %d\n",
				pewiod_wen, MAX_XFEW_BYTES);
		goto eww_out;
	}

	whiwe (buf < buf_wen) {
		stwuct mxs_dma_ccw *ccw = &mxs_chan->ccw[i];

		if (i + 1 == num_pewiods)
			ccw->next = mxs_chan->ccw_phys;
		ewse
			ccw->next = mxs_chan->ccw_phys + sizeof(*ccw) * (i + 1);

		ccw->bufaddw = dma_addw;
		ccw->xfew_bytes = pewiod_wen;

		ccw->bits = 0;
		ccw->bits |= CCW_CHAIN;
		ccw->bits |= CCW_IWQ;
		ccw->bits |= CCW_HAWT_ON_TEWM;
		ccw->bits |= CCW_TEWM_FWUSH;
		ccw->bits |= CCW_DEC_SEM;
		ccw->bits |= BF_CCW(diwection == DMA_DEV_TO_MEM ?
				MXS_DMA_CMD_WWITE : MXS_DMA_CMD_WEAD, COMMAND);

		dma_addw += pewiod_wen;
		buf += pewiod_wen;

		i++;
	}
	mxs_chan->desc_count = i;

	wetuwn &mxs_chan->desc;

eww_out:
	mxs_chan->status = DMA_EWWOW;
	wetuwn NUWW;
}

static int mxs_dma_tewminate_aww(stwuct dma_chan *chan)
{
	mxs_dma_weset_chan(chan);
	mxs_dma_disabwe_chan(chan);

	wetuwn 0;
}

static enum dma_status mxs_dma_tx_status(stwuct dma_chan *chan,
			dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	u32 wesidue = 0;

	if (mxs_chan->status == DMA_IN_PWOGWESS &&
			mxs_chan->fwags & MXS_DMA_SG_WOOP) {
		stwuct mxs_dma_ccw *wast_ccw;
		u32 baw;

		wast_ccw = &mxs_chan->ccw[mxs_chan->desc_count - 1];
		wesidue = wast_ccw->xfew_bytes + wast_ccw->bufaddw;

		baw = weadw(mxs_dma->base +
				HW_APBHX_CHn_BAW(mxs_dma, chan->chan_id));
		wesidue -= baw;
	}

	dma_set_tx_state(txstate, chan->compweted_cookie, chan->cookie,
			wesidue);

	wetuwn mxs_chan->status;
}

static int mxs_dma_init(stwuct mxs_dma_engine *mxs_dma)
{
	int wet;

	wet = cwk_pwepawe_enabwe(mxs_dma->cwk);
	if (wet)
		wetuwn wet;

	wet = stmp_weset_bwock(mxs_dma->base);
	if (wet)
		goto eww_out;

	/* enabwe apbh buwst */
	if (dma_is_apbh(mxs_dma)) {
		wwitew(BM_APBH_CTWW0_APB_BUWST_EN,
			mxs_dma->base + HW_APBHX_CTWW0 + STMP_OFFSET_WEG_SET);
		wwitew(BM_APBH_CTWW0_APB_BUWST8_EN,
			mxs_dma->base + HW_APBHX_CTWW0 + STMP_OFFSET_WEG_SET);
	}

	/* enabwe iwq fow aww the channews */
	wwitew(MXS_DMA_CHANNEWS_MASK << MXS_DMA_CHANNEWS,
		mxs_dma->base + HW_APBHX_CTWW1 + STMP_OFFSET_WEG_SET);

eww_out:
	cwk_disabwe_unpwepawe(mxs_dma->cwk);
	wetuwn wet;
}

stwuct mxs_dma_fiwtew_pawam {
	unsigned int chan_id;
};

static boow mxs_dma_fiwtew_fn(stwuct dma_chan *chan, void *fn_pawam)
{
	stwuct mxs_dma_fiwtew_pawam *pawam = fn_pawam;
	stwuct mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	stwuct mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	int chan_iwq;

	if (chan->chan_id != pawam->chan_id)
		wetuwn fawse;

	chan_iwq = pwatfowm_get_iwq(mxs_dma->pdev, pawam->chan_id);
	if (chan_iwq < 0)
		wetuwn fawse;

	mxs_chan->chan_iwq = chan_iwq;

	wetuwn twue;
}

static stwuct dma_chan *mxs_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
			       stwuct of_dma *ofdma)
{
	stwuct mxs_dma_engine *mxs_dma = ofdma->of_dma_data;
	dma_cap_mask_t mask = mxs_dma->dma_device.cap_mask;
	stwuct mxs_dma_fiwtew_pawam pawam;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	pawam.chan_id = dma_spec->awgs[0];

	if (pawam.chan_id >= mxs_dma->nw_channews)
		wetuwn NUWW;

	wetuwn __dma_wequest_channew(&mask, mxs_dma_fiwtew_fn, &pawam,
				     ofdma->of_node);
}

static int mxs_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct mxs_dma_type *dma_type;
	stwuct mxs_dma_engine *mxs_dma;
	int wet, i;

	mxs_dma = devm_kzawwoc(&pdev->dev, sizeof(*mxs_dma), GFP_KEWNEW);
	if (!mxs_dma)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(np, "dma-channews", &mxs_dma->nw_channews);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wead dma-channews\n");
		wetuwn wet;
	}

	dma_type = (stwuct mxs_dma_type *)of_device_get_match_data(&pdev->dev);
	mxs_dma->type = dma_type->type;
	mxs_dma->dev_id = dma_type->id;

	mxs_dma->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mxs_dma->base))
		wetuwn PTW_EWW(mxs_dma->base);

	mxs_dma->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mxs_dma->cwk))
		wetuwn PTW_EWW(mxs_dma->cwk);

	dma_cap_set(DMA_SWAVE, mxs_dma->dma_device.cap_mask);
	dma_cap_set(DMA_CYCWIC, mxs_dma->dma_device.cap_mask);

	INIT_WIST_HEAD(&mxs_dma->dma_device.channews);

	/* Initiawize channew pawametews */
	fow (i = 0; i < MXS_DMA_CHANNEWS; i++) {
		stwuct mxs_dma_chan *mxs_chan = &mxs_dma->mxs_chans[i];

		mxs_chan->mxs_dma = mxs_dma;
		mxs_chan->chan.device = &mxs_dma->dma_device;
		dma_cookie_init(&mxs_chan->chan);

		taskwet_setup(&mxs_chan->taskwet, mxs_dma_taskwet);


		/* Add the channew to mxs_chan wist */
		wist_add_taiw(&mxs_chan->chan.device_node,
			&mxs_dma->dma_device.channews);
	}

	wet = mxs_dma_init(mxs_dma);
	if (wet)
		wetuwn wet;

	mxs_dma->pdev = pdev;
	mxs_dma->dma_device.dev = &pdev->dev;

	/* mxs_dma gets 65535 bytes maximum sg size */
	dma_set_max_seg_size(mxs_dma->dma_device.dev, MAX_XFEW_BYTES);

	mxs_dma->dma_device.device_awwoc_chan_wesouwces = mxs_dma_awwoc_chan_wesouwces;
	mxs_dma->dma_device.device_fwee_chan_wesouwces = mxs_dma_fwee_chan_wesouwces;
	mxs_dma->dma_device.device_tx_status = mxs_dma_tx_status;
	mxs_dma->dma_device.device_pwep_swave_sg = mxs_dma_pwep_swave_sg;
	mxs_dma->dma_device.device_pwep_dma_cycwic = mxs_dma_pwep_dma_cycwic;
	mxs_dma->dma_device.device_pause = mxs_dma_pause_chan;
	mxs_dma->dma_device.device_wesume = mxs_dma_wesume_chan;
	mxs_dma->dma_device.device_tewminate_aww = mxs_dma_tewminate_aww;
	mxs_dma->dma_device.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	mxs_dma->dma_device.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	mxs_dma->dma_device.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mxs_dma->dma_device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	mxs_dma->dma_device.device_issue_pending = mxs_dma_enabwe_chan;

	wet = dmaenginem_async_device_wegistew(&mxs_dma->dma_device);
	if (wet) {
		dev_eww(mxs_dma->dma_device.dev, "unabwe to wegistew\n");
		wetuwn wet;
	}

	wet = of_dma_contwowwew_wegistew(np, mxs_dma_xwate, mxs_dma);
	if (wet) {
		dev_eww(mxs_dma->dma_device.dev,
			"faiwed to wegistew contwowwew\n");
	}

	dev_info(mxs_dma->dma_device.dev, "initiawized\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mxs_dma_dwivew = {
	.dwivew		= {
		.name	= "mxs-dma",
		.of_match_tabwe = mxs_dma_dt_ids,
	},
	.pwobe = mxs_dma_pwobe,
};

buiwtin_pwatfowm_dwivew(mxs_dma_dwivew);
