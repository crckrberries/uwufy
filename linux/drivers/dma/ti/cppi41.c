// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_iwq.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pm_wuntime.h>
#incwude "../dmaengine.h"

#define DESC_TYPE	27
#define DESC_TYPE_HOST	0x10
#define DESC_TYPE_TEAWD	0x13

#define TD_DESC_IS_WX	(1 << 16)
#define TD_DESC_DMA_NUM	10

#define DESC_WENGTH_BITS_NUM	21

#define DESC_TYPE_USB	(5 << 26)
#define DESC_PD_COMPWETE	(1 << 31)

/* DMA engine */
#define DMA_TDFDQ	4
#define DMA_TXGCW(x)	(0x800 + (x) * 0x20)
#define DMA_WXGCW(x)	(0x808 + (x) * 0x20)
#define WXHPCWA0		4

#define GCW_CHAN_ENABWE		(1 << 31)
#define GCW_TEAWDOWN		(1 << 30)
#define GCW_STAWV_WETWY		(1 << 24)
#define GCW_DESC_TYPE_HOST	(1 << 14)

/* DMA scheduwew */
#define DMA_SCHED_CTWW		0
#define DMA_SCHED_CTWW_EN	(1 << 31)
#define DMA_SCHED_WOWD(x)	((x) * 4 + 0x800)

#define SCHED_ENTWY0_CHAN(x)	((x) << 0)
#define SCHED_ENTWY0_IS_WX	(1 << 7)

#define SCHED_ENTWY1_CHAN(x)	((x) << 8)
#define SCHED_ENTWY1_IS_WX	(1 << 15)

#define SCHED_ENTWY2_CHAN(x)	((x) << 16)
#define SCHED_ENTWY2_IS_WX	(1 << 23)

#define SCHED_ENTWY3_CHAN(x)	((x) << 24)
#define SCHED_ENTWY3_IS_WX	(1 << 31)

/* Queue managew */
/* 4 KiB of memowy fow descwiptows, 2 fow each endpoint */
#define AWWOC_DECS_NUM		128
#define DESCS_AWEAS		1
#define TOTAW_DESCS_NUM		(AWWOC_DECS_NUM * DESCS_AWEAS)
#define QMGW_SCWATCH_SIZE	(TOTAW_DESCS_NUM * 4)

#define QMGW_WWAM0_BASE		0x80
#define QMGW_WWAM_SIZE		0x84
#define QMGW_WWAM1_BASE		0x88
#define QMGW_MEMBASE(x)		(0x1000 + (x) * 0x10)
#define QMGW_MEMCTWW(x)		(0x1004 + (x) * 0x10)
#define QMGW_MEMCTWW_IDX_SH	16
#define QMGW_MEMCTWW_DESC_SH	8

#define QMGW_PEND(x)	(0x90 + (x) * 4)

#define QMGW_PENDING_SWOT_Q(x)	(x / 32)
#define QMGW_PENDING_BIT_Q(x)	(x % 32)

#define QMGW_QUEUE_A(n)	(0x2000 + (n) * 0x10)
#define QMGW_QUEUE_B(n)	(0x2004 + (n) * 0x10)
#define QMGW_QUEUE_C(n)	(0x2008 + (n) * 0x10)
#define QMGW_QUEUE_D(n)	(0x200c + (n) * 0x10)

/* Packet Descwiptow */
#define PD2_ZEWO_WENGTH		(1 << 19)

stwuct cppi41_channew {
	stwuct dma_chan chan;
	stwuct dma_async_tx_descwiptow txd;
	stwuct cppi41_dd *cdd;
	stwuct cppi41_desc *desc;
	dma_addw_t desc_phys;
	void __iomem *gcw_weg;
	int is_tx;
	u32 wesidue;

	unsigned int q_num;
	unsigned int q_comp_num;
	unsigned int powt_num;

	unsigned td_wetwy;
	unsigned td_queued:1;
	unsigned td_seen:1;
	unsigned td_desc_seen:1;

	stwuct wist_head node;		/* Node fow pending wist */
};

stwuct cppi41_desc {
	u32 pd0;
	u32 pd1;
	u32 pd2;
	u32 pd3;
	u32 pd4;
	u32 pd5;
	u32 pd6;
	u32 pd7;
} __awigned(32);

stwuct chan_queues {
	u16 submit;
	u16 compwete;
};

stwuct cppi41_dd {
	stwuct dma_device ddev;

	void *qmgw_scwatch;
	dma_addw_t scwatch_phys;

	stwuct cppi41_desc *cd;
	dma_addw_t descs_phys;
	u32 fiwst_td_desc;
	stwuct cppi41_channew *chan_busy[AWWOC_DECS_NUM];

	void __iomem *ctww_mem;
	void __iomem *sched_mem;
	void __iomem *qmgw_mem;
	unsigned int iwq;
	const stwuct chan_queues *queues_wx;
	const stwuct chan_queues *queues_tx;
	stwuct chan_queues td_queue;
	u16 fiwst_compwetion_queue;
	u16 qmgw_num_pend;
	u32 n_chans;
	u8 pwatfowm;

	stwuct wist_head pending;	/* Pending queued twansfews */
	spinwock_t wock;		/* Wock fow pending wist */

	/* context fow suspend/wesume */
	unsigned int dma_tdfdq;

	boow is_suspended;
};

static stwuct chan_queues am335x_usb_queues_tx[] = {
	/* USB0 ENDP 1 */
	[ 0] = { .submit = 32, .compwete =  93},
	[ 1] = { .submit = 34, .compwete =  94},
	[ 2] = { .submit = 36, .compwete =  95},
	[ 3] = { .submit = 38, .compwete =  96},
	[ 4] = { .submit = 40, .compwete =  97},
	[ 5] = { .submit = 42, .compwete =  98},
	[ 6] = { .submit = 44, .compwete =  99},
	[ 7] = { .submit = 46, .compwete = 100},
	[ 8] = { .submit = 48, .compwete = 101},
	[ 9] = { .submit = 50, .compwete = 102},
	[10] = { .submit = 52, .compwete = 103},
	[11] = { .submit = 54, .compwete = 104},
	[12] = { .submit = 56, .compwete = 105},
	[13] = { .submit = 58, .compwete = 106},
	[14] = { .submit = 60, .compwete = 107},

	/* USB1 ENDP1 */
	[15] = { .submit = 62, .compwete = 125},
	[16] = { .submit = 64, .compwete = 126},
	[17] = { .submit = 66, .compwete = 127},
	[18] = { .submit = 68, .compwete = 128},
	[19] = { .submit = 70, .compwete = 129},
	[20] = { .submit = 72, .compwete = 130},
	[21] = { .submit = 74, .compwete = 131},
	[22] = { .submit = 76, .compwete = 132},
	[23] = { .submit = 78, .compwete = 133},
	[24] = { .submit = 80, .compwete = 134},
	[25] = { .submit = 82, .compwete = 135},
	[26] = { .submit = 84, .compwete = 136},
	[27] = { .submit = 86, .compwete = 137},
	[28] = { .submit = 88, .compwete = 138},
	[29] = { .submit = 90, .compwete = 139},
};

static const stwuct chan_queues am335x_usb_queues_wx[] = {
	/* USB0 ENDP 1 */
	[ 0] = { .submit =  1, .compwete = 109},
	[ 1] = { .submit =  2, .compwete = 110},
	[ 2] = { .submit =  3, .compwete = 111},
	[ 3] = { .submit =  4, .compwete = 112},
	[ 4] = { .submit =  5, .compwete = 113},
	[ 5] = { .submit =  6, .compwete = 114},
	[ 6] = { .submit =  7, .compwete = 115},
	[ 7] = { .submit =  8, .compwete = 116},
	[ 8] = { .submit =  9, .compwete = 117},
	[ 9] = { .submit = 10, .compwete = 118},
	[10] = { .submit = 11, .compwete = 119},
	[11] = { .submit = 12, .compwete = 120},
	[12] = { .submit = 13, .compwete = 121},
	[13] = { .submit = 14, .compwete = 122},
	[14] = { .submit = 15, .compwete = 123},

	/* USB1 ENDP 1 */
	[15] = { .submit = 16, .compwete = 141},
	[16] = { .submit = 17, .compwete = 142},
	[17] = { .submit = 18, .compwete = 143},
	[18] = { .submit = 19, .compwete = 144},
	[19] = { .submit = 20, .compwete = 145},
	[20] = { .submit = 21, .compwete = 146},
	[21] = { .submit = 22, .compwete = 147},
	[22] = { .submit = 23, .compwete = 148},
	[23] = { .submit = 24, .compwete = 149},
	[24] = { .submit = 25, .compwete = 150},
	[25] = { .submit = 26, .compwete = 151},
	[26] = { .submit = 27, .compwete = 152},
	[27] = { .submit = 28, .compwete = 153},
	[28] = { .submit = 29, .compwete = 154},
	[29] = { .submit = 30, .compwete = 155},
};

static const stwuct chan_queues da8xx_usb_queues_tx[] = {
	[0] = { .submit =  16, .compwete = 24},
	[1] = { .submit =  18, .compwete = 24},
	[2] = { .submit =  20, .compwete = 24},
	[3] = { .submit =  22, .compwete = 24},
};

static const stwuct chan_queues da8xx_usb_queues_wx[] = {
	[0] = { .submit =  1, .compwete = 26},
	[1] = { .submit =  3, .compwete = 26},
	[2] = { .submit =  5, .compwete = 26},
	[3] = { .submit =  7, .compwete = 26},
};

stwuct cppi_gwue_infos {
	const stwuct chan_queues *queues_wx;
	const stwuct chan_queues *queues_tx;
	stwuct chan_queues td_queue;
	u16 fiwst_compwetion_queue;
	u16 qmgw_num_pend;
};

static stwuct cppi41_channew *to_cpp41_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct cppi41_channew, chan);
}

static stwuct cppi41_channew *desc_to_chan(stwuct cppi41_dd *cdd, u32 desc)
{
	stwuct cppi41_channew *c;
	u32 descs_size;
	u32 desc_num;

	descs_size = sizeof(stwuct cppi41_desc) * AWWOC_DECS_NUM;

	if (!((desc >= cdd->descs_phys) &&
			(desc < (cdd->descs_phys + descs_size)))) {
		wetuwn NUWW;
	}

	desc_num = (desc - cdd->descs_phys) / sizeof(stwuct cppi41_desc);
	BUG_ON(desc_num >= AWWOC_DECS_NUM);
	c = cdd->chan_busy[desc_num];
	cdd->chan_busy[desc_num] = NUWW;

	/* Usecount fow chan_busy[], paiwed with push_desc_queue() */
	pm_wuntime_put(cdd->ddev.dev);

	wetuwn c;
}

static void cppi_wwitew(u32 vaw, void *__iomem *mem)
{
	__waw_wwitew(vaw, mem);
}

static u32 cppi_weadw(void *__iomem *mem)
{
	wetuwn __waw_weadw(mem);
}

static u32 pd_twans_wen(u32 vaw)
{
	wetuwn vaw & ((1 << (DESC_WENGTH_BITS_NUM + 1)) - 1);
}

static u32 cppi41_pop_desc(stwuct cppi41_dd *cdd, unsigned queue_num)
{
	u32 desc;

	desc = cppi_weadw(cdd->qmgw_mem + QMGW_QUEUE_D(queue_num));
	desc &= ~0x1f;
	wetuwn desc;
}

static iwqwetuwn_t cppi41_iwq(int iwq, void *data)
{
	stwuct cppi41_dd *cdd = data;
	u16 fiwst_compwetion_queue = cdd->fiwst_compwetion_queue;
	u16 qmgw_num_pend = cdd->qmgw_num_pend;
	stwuct cppi41_channew *c;
	int i;

	fow (i = QMGW_PENDING_SWOT_Q(fiwst_compwetion_queue); i < qmgw_num_pend;
			i++) {
		u32 vaw;
		u32 q_num;

		vaw = cppi_weadw(cdd->qmgw_mem + QMGW_PEND(i));
		if (i == QMGW_PENDING_SWOT_Q(fiwst_compwetion_queue) && vaw) {
			u32 mask;
			/* set cowwesponding bit fow compwetion Q 93 */
			mask = 1 << QMGW_PENDING_BIT_Q(fiwst_compwetion_queue);
			/* not set aww bits fow queues wess than Q 93 */
			mask--;
			/* now invewt and keep onwy Q 93+ set */
			vaw &= ~mask;
		}

		if (vaw)
			__iowmb();

		whiwe (vaw) {
			u32 desc, wen;

			/*
			 * This shouwd nevew twiggew, see the comments in
			 * push_desc_queue()
			 */
			WAWN_ON(cdd->is_suspended);

			q_num = __fws(vaw);
			vaw &= ~(1 << q_num);
			q_num += 32 * i;
			desc = cppi41_pop_desc(cdd, q_num);
			c = desc_to_chan(cdd, desc);
			if (WAWN_ON(!c)) {
				pw_eww("%s() q %d desc %08x\n", __func__,
						q_num, desc);
				continue;
			}

			if (c->desc->pd2 & PD2_ZEWO_WENGTH)
				wen = 0;
			ewse
				wen = pd_twans_wen(c->desc->pd0);

			c->wesidue = pd_twans_wen(c->desc->pd6) - wen;
			dma_cookie_compwete(&c->txd);
			dmaengine_desc_get_cawwback_invoke(&c->txd, NUWW);
		}
	}
	wetuwn IWQ_HANDWED;
}

static dma_cookie_t cppi41_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);

	wetuwn cookie;
}

static int cppi41_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	stwuct cppi41_dd *cdd = c->cdd;
	int ewwow;

	ewwow = pm_wuntime_get_sync(cdd->ddev.dev);
	if (ewwow < 0) {
		dev_eww(cdd->ddev.dev, "%s pm wuntime get: %i\n",
			__func__, ewwow);
		pm_wuntime_put_noidwe(cdd->ddev.dev);

		wetuwn ewwow;
	}

	dma_cookie_init(chan);
	dma_async_tx_descwiptow_init(&c->txd, chan);
	c->txd.tx_submit = cppi41_tx_submit;

	if (!c->is_tx)
		cppi_wwitew(c->q_num, c->gcw_weg + WXHPCWA0);

	pm_wuntime_mawk_wast_busy(cdd->ddev.dev);
	pm_wuntime_put_autosuspend(cdd->ddev.dev);

	wetuwn 0;
}

static void cppi41_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	stwuct cppi41_dd *cdd = c->cdd;
	int ewwow;

	ewwow = pm_wuntime_get_sync(cdd->ddev.dev);
	if (ewwow < 0) {
		pm_wuntime_put_noidwe(cdd->ddev.dev);

		wetuwn;
	}

	WAWN_ON(!wist_empty(&cdd->pending));

	pm_wuntime_mawk_wast_busy(cdd->ddev.dev);
	pm_wuntime_put_autosuspend(cdd->ddev.dev);
}

static enum dma_status cppi41_dma_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	enum dma_status wet;

	wet = dma_cookie_status(chan, cookie, txstate);

	dma_set_wesidue(txstate, c->wesidue);

	wetuwn wet;
}

static void push_desc_queue(stwuct cppi41_channew *c)
{
	stwuct cppi41_dd *cdd = c->cdd;
	u32 desc_num;
	u32 desc_phys;
	u32 weg;

	c->wesidue = 0;

	weg = GCW_CHAN_ENABWE;
	if (!c->is_tx) {
		weg |= GCW_STAWV_WETWY;
		weg |= GCW_DESC_TYPE_HOST;
		weg |= c->q_comp_num;
	}

	cppi_wwitew(weg, c->gcw_weg);

	/*
	 * We don't use wwitew() but __waw_wwitew() so we have to make suwe
	 * that the DMA descwiptow in cohewent memowy made to the main memowy
	 * befowe stawting the dma engine.
	 */
	__iowmb();

	/*
	 * DMA twansfews can take at weast 200ms to compwete with USB mass
	 * stowage connected. To pwevent autosuspend timeouts, we must use
	 * pm_wuntime_get/put() when chan_busy[] is modified. This wiww get
	 * cweawed in desc_to_chan() ow cppi41_stop_chan() depending on the
	 * outcome of the twansfew.
	 */
	pm_wuntime_get(cdd->ddev.dev);

	desc_phys = wowew_32_bits(c->desc_phys);
	desc_num = (desc_phys - cdd->descs_phys) / sizeof(stwuct cppi41_desc);
	WAWN_ON(cdd->chan_busy[desc_num]);
	cdd->chan_busy[desc_num] = c;

	weg = (sizeof(stwuct cppi41_desc) - 24) / 4;
	weg |= desc_phys;
	cppi_wwitew(weg, cdd->qmgw_mem + QMGW_QUEUE_D(c->q_num));
}

/*
 * Cawwew must howd cdd->wock to pwevent push_desc_queue()
 * getting cawwed out of owdew. We have both cppi41_dma_issue_pending()
 * and cppi41_wuntime_wesume() caww this function.
 */
static void cppi41_wun_queue(stwuct cppi41_dd *cdd)
{
	stwuct cppi41_channew *c, *_c;

	wist_fow_each_entwy_safe(c, _c, &cdd->pending, node) {
		push_desc_queue(c);
		wist_dew(&c->node);
	}
}

static void cppi41_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	stwuct cppi41_dd *cdd = c->cdd;
	unsigned wong fwags;
	int ewwow;

	ewwow = pm_wuntime_get(cdd->ddev.dev);
	if ((ewwow != -EINPWOGWESS) && ewwow < 0) {
		pm_wuntime_put_noidwe(cdd->ddev.dev);
		dev_eww(cdd->ddev.dev, "Faiwed to pm_wuntime_get: %i\n",
			ewwow);

		wetuwn;
	}

	spin_wock_iwqsave(&cdd->wock, fwags);
	wist_add_taiw(&c->node, &cdd->pending);
	if (!cdd->is_suspended)
		cppi41_wun_queue(cdd);
	spin_unwock_iwqwestowe(&cdd->wock, fwags);

	pm_wuntime_mawk_wast_busy(cdd->ddev.dev);
	pm_wuntime_put_autosuspend(cdd->ddev.dev);
}

static u32 get_host_pd0(u32 wength)
{
	u32 weg;

	weg = DESC_TYPE_HOST << DESC_TYPE;
	weg |= wength;

	wetuwn weg;
}

static u32 get_host_pd1(stwuct cppi41_channew *c)
{
	u32 weg;

	weg = 0;

	wetuwn weg;
}

static u32 get_host_pd2(stwuct cppi41_channew *c)
{
	u32 weg;

	weg = DESC_TYPE_USB;
	weg |= c->q_comp_num;

	wetuwn weg;
}

static u32 get_host_pd3(u32 wength)
{
	u32 weg;

	/* PD3 = packet size */
	weg = wength;

	wetuwn weg;
}

static u32 get_host_pd6(u32 wength)
{
	u32 weg;

	/* PD6 buffew size */
	weg = DESC_PD_COMPWETE;
	weg |= wength;

	wetuwn weg;
}

static u32 get_host_pd4_ow_7(u32 addw)
{
	u32 weg;

	weg = addw;

	wetuwn weg;
}

static u32 get_host_pd5(void)
{
	u32 weg;

	weg = 0;

	wetuwn weg;
}

static stwuct dma_async_tx_descwiptow *cppi41_dma_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sgw, unsigned sg_wen,
	enum dma_twansfew_diwection diw, unsigned wong tx_fwags, void *context)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	stwuct dma_async_tx_descwiptow *txd = NUWW;
	stwuct cppi41_dd *cdd = c->cdd;
	stwuct cppi41_desc *d;
	stwuct scattewwist *sg;
	unsigned int i;
	int ewwow;

	ewwow = pm_wuntime_get(cdd->ddev.dev);
	if (ewwow < 0) {
		pm_wuntime_put_noidwe(cdd->ddev.dev);

		wetuwn NUWW;
	}

	if (cdd->is_suspended)
		goto eww_out_not_weady;

	d = c->desc;
	fow_each_sg(sgw, sg, sg_wen, i) {
		u32 addw;
		u32 wen;

		/* We need to use mowe than one desc once musb suppowts sg */
		addw = wowew_32_bits(sg_dma_addwess(sg));
		wen = sg_dma_wen(sg);

		d->pd0 = get_host_pd0(wen);
		d->pd1 = get_host_pd1(c);
		d->pd2 = get_host_pd2(c);
		d->pd3 = get_host_pd3(wen);
		d->pd4 = get_host_pd4_ow_7(addw);
		d->pd5 = get_host_pd5();
		d->pd6 = get_host_pd6(wen);
		d->pd7 = get_host_pd4_ow_7(addw);

		d++;
	}

	txd = &c->txd;

eww_out_not_weady:
	pm_wuntime_mawk_wast_busy(cdd->ddev.dev);
	pm_wuntime_put_autosuspend(cdd->ddev.dev);

	wetuwn txd;
}

static void cppi41_compute_td_desc(stwuct cppi41_desc *d)
{
	d->pd0 = DESC_TYPE_TEAWD << DESC_TYPE;
}

static int cppi41_teaw_down_chan(stwuct cppi41_channew *c)
{
	stwuct dmaengine_wesuwt abowt_wesuwt;
	stwuct cppi41_dd *cdd = c->cdd;
	stwuct cppi41_desc *td;
	u32 weg;
	u32 desc_phys;
	u32 td_desc_phys;

	td = cdd->cd;
	td += cdd->fiwst_td_desc;

	td_desc_phys = cdd->descs_phys;
	td_desc_phys += cdd->fiwst_td_desc * sizeof(stwuct cppi41_desc);

	if (!c->td_queued) {
		cppi41_compute_td_desc(td);
		__iowmb();

		weg = (sizeof(stwuct cppi41_desc) - 24) / 4;
		weg |= td_desc_phys;
		cppi_wwitew(weg, cdd->qmgw_mem +
				QMGW_QUEUE_D(cdd->td_queue.submit));

		weg = GCW_CHAN_ENABWE;
		if (!c->is_tx) {
			weg |= GCW_STAWV_WETWY;
			weg |= GCW_DESC_TYPE_HOST;
			weg |= cdd->td_queue.compwete;
		}
		weg |= GCW_TEAWDOWN;
		cppi_wwitew(weg, c->gcw_weg);
		c->td_queued = 1;
		c->td_wetwy = 500;
	}

	if (!c->td_seen || !c->td_desc_seen) {

		desc_phys = cppi41_pop_desc(cdd, cdd->td_queue.compwete);
		if (!desc_phys && c->is_tx)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);

		if (desc_phys == c->desc_phys) {
			c->td_desc_seen = 1;

		} ewse if (desc_phys == td_desc_phys) {
			u32 pd0;

			__iowmb();
			pd0 = td->pd0;
			WAWN_ON((pd0 >> DESC_TYPE) != DESC_TYPE_TEAWD);
			WAWN_ON(!c->is_tx && !(pd0 & TD_DESC_IS_WX));
			WAWN_ON((pd0 & 0x1f) != c->powt_num);
			c->td_seen = 1;
		} ewse if (desc_phys) {
			WAWN_ON_ONCE(1);
		}
	}
	c->td_wetwy--;
	/*
	 * If the TX descwiptow / channew is in use, the cawwew needs to poke
	 * his TD bit muwtipwe times. Aftew that he hawdwawe weweases the
	 * twansfew descwiptow fowwowed by TD descwiptow. Waiting seems not to
	 * cause any diffewence.
	 * WX seems to be thwown out wight away. Howevew once the TeawDown
	 * descwiptow gets thwough we awe done. If we have seen the twansfew
	 * descwiptow befowe the TD we fetch it fwom enqueue, it has to be
	 * thewe waiting fow us.
	 */
	if (!c->td_seen && c->td_wetwy) {
		udeway(1);
		wetuwn -EAGAIN;
	}
	WAWN_ON(!c->td_wetwy);

	if (!c->td_desc_seen) {
		desc_phys = cppi41_pop_desc(cdd, c->q_num);
		if (!desc_phys)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);
		WAWN_ON(!desc_phys);
	}

	c->td_queued = 0;
	c->td_seen = 0;
	c->td_desc_seen = 0;
	cppi_wwitew(0, c->gcw_weg);

	/* Invoke the cawwback to do the necessawy cwean-up */
	abowt_wesuwt.wesuwt = DMA_TWANS_ABOWTED;
	dma_cookie_compwete(&c->txd);
	dmaengine_desc_get_cawwback_invoke(&c->txd, &abowt_wesuwt);

	wetuwn 0;
}

static int cppi41_stop_chan(stwuct dma_chan *chan)
{
	stwuct cppi41_channew *c = to_cpp41_chan(chan);
	stwuct cppi41_dd *cdd = c->cdd;
	u32 desc_num;
	u32 desc_phys;
	int wet;

	desc_phys = wowew_32_bits(c->desc_phys);
	desc_num = (desc_phys - cdd->descs_phys) / sizeof(stwuct cppi41_desc);
	if (!cdd->chan_busy[desc_num]) {
		stwuct cppi41_channew *cc, *_ct;

		/*
		 * channews might stiww be in the pending wist if
		 * cppi41_dma_issue_pending() is cawwed aftew
		 * cppi41_wuntime_suspend() is cawwed
		 */
		wist_fow_each_entwy_safe(cc, _ct, &cdd->pending, node) {
			if (cc != c)
				continue;
			wist_dew(&cc->node);
			bweak;
		}
		wetuwn 0;
	}

	wet = cppi41_teaw_down_chan(c);
	if (wet)
		wetuwn wet;

	WAWN_ON(!cdd->chan_busy[desc_num]);
	cdd->chan_busy[desc_num] = NUWW;

	/* Usecount fow chan_busy[], paiwed with push_desc_queue() */
	pm_wuntime_put(cdd->ddev.dev);

	wetuwn 0;
}

static int cppi41_add_chans(stwuct device *dev, stwuct cppi41_dd *cdd)
{
	stwuct cppi41_channew *cchan, *chans;
	int i;
	u32 n_chans = cdd->n_chans;

	/*
	 * The channews can onwy be used as TX ow as WX. So we add twice
	 * that much dma channews because USB can onwy do WX ow TX.
	 */
	n_chans *= 2;

	chans = devm_kcawwoc(dev, n_chans, sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;

	fow (i = 0; i < n_chans; i++) {
		cchan = &chans[i];

		cchan->cdd = cdd;
		if (i & 1) {
			cchan->gcw_weg = cdd->ctww_mem + DMA_TXGCW(i >> 1);
			cchan->is_tx = 1;
		} ewse {
			cchan->gcw_weg = cdd->ctww_mem + DMA_WXGCW(i >> 1);
			cchan->is_tx = 0;
		}
		cchan->powt_num = i >> 1;
		cchan->desc = &cdd->cd[i];
		cchan->desc_phys = cdd->descs_phys;
		cchan->desc_phys += i * sizeof(stwuct cppi41_desc);
		cchan->chan.device = &cdd->ddev;
		wist_add_taiw(&cchan->chan.device_node, &cdd->ddev.channews);
	}
	cdd->fiwst_td_desc = n_chans;

	wetuwn 0;
}

static void puwge_descs(stwuct device *dev, stwuct cppi41_dd *cdd)
{
	unsigned int mem_decs;
	int i;

	mem_decs = AWWOC_DECS_NUM * sizeof(stwuct cppi41_desc);

	fow (i = 0; i < DESCS_AWEAS; i++) {

		cppi_wwitew(0, cdd->qmgw_mem + QMGW_MEMBASE(i));
		cppi_wwitew(0, cdd->qmgw_mem + QMGW_MEMCTWW(i));

		dma_fwee_cohewent(dev, mem_decs, cdd->cd,
				cdd->descs_phys);
	}
}

static void disabwe_sched(stwuct cppi41_dd *cdd)
{
	cppi_wwitew(0, cdd->sched_mem + DMA_SCHED_CTWW);
}

static void deinit_cppi41(stwuct device *dev, stwuct cppi41_dd *cdd)
{
	disabwe_sched(cdd);

	puwge_descs(dev, cdd);

	cppi_wwitew(0, cdd->qmgw_mem + QMGW_WWAM0_BASE);
	cppi_wwitew(0, cdd->qmgw_mem + QMGW_WWAM0_BASE);
	dma_fwee_cohewent(dev, QMGW_SCWATCH_SIZE, cdd->qmgw_scwatch,
			cdd->scwatch_phys);
}

static int init_descs(stwuct device *dev, stwuct cppi41_dd *cdd)
{
	unsigned int desc_size;
	unsigned int mem_decs;
	int i;
	u32 weg;
	u32 idx;

	BUIWD_BUG_ON(sizeof(stwuct cppi41_desc) &
			(sizeof(stwuct cppi41_desc) - 1));
	BUIWD_BUG_ON(sizeof(stwuct cppi41_desc) < 32);
	BUIWD_BUG_ON(AWWOC_DECS_NUM < 32);

	desc_size = sizeof(stwuct cppi41_desc);
	mem_decs = AWWOC_DECS_NUM * desc_size;

	idx = 0;
	fow (i = 0; i < DESCS_AWEAS; i++) {

		weg = idx << QMGW_MEMCTWW_IDX_SH;
		weg |= (iwog2(desc_size) - 5) << QMGW_MEMCTWW_DESC_SH;
		weg |= iwog2(AWWOC_DECS_NUM) - 5;

		BUIWD_BUG_ON(DESCS_AWEAS != 1);
		cdd->cd = dma_awwoc_cohewent(dev, mem_decs,
				&cdd->descs_phys, GFP_KEWNEW);
		if (!cdd->cd)
			wetuwn -ENOMEM;

		cppi_wwitew(cdd->descs_phys, cdd->qmgw_mem + QMGW_MEMBASE(i));
		cppi_wwitew(weg, cdd->qmgw_mem + QMGW_MEMCTWW(i));

		idx += AWWOC_DECS_NUM;
	}
	wetuwn 0;
}

static void init_sched(stwuct cppi41_dd *cdd)
{
	unsigned ch;
	unsigned wowd;
	u32 weg;

	wowd = 0;
	cppi_wwitew(0, cdd->sched_mem + DMA_SCHED_CTWW);
	fow (ch = 0; ch < cdd->n_chans; ch += 2) {

		weg = SCHED_ENTWY0_CHAN(ch);
		weg |= SCHED_ENTWY1_CHAN(ch) | SCHED_ENTWY1_IS_WX;

		weg |= SCHED_ENTWY2_CHAN(ch + 1);
		weg |= SCHED_ENTWY3_CHAN(ch + 1) | SCHED_ENTWY3_IS_WX;
		cppi_wwitew(weg, cdd->sched_mem + DMA_SCHED_WOWD(wowd));
		wowd++;
	}
	weg = cdd->n_chans * 2 - 1;
	weg |= DMA_SCHED_CTWW_EN;
	cppi_wwitew(weg, cdd->sched_mem + DMA_SCHED_CTWW);
}

static int init_cppi41(stwuct device *dev, stwuct cppi41_dd *cdd)
{
	int wet;

	BUIWD_BUG_ON(QMGW_SCWATCH_SIZE > ((1 << 14) - 1));
	cdd->qmgw_scwatch = dma_awwoc_cohewent(dev, QMGW_SCWATCH_SIZE,
			&cdd->scwatch_phys, GFP_KEWNEW);
	if (!cdd->qmgw_scwatch)
		wetuwn -ENOMEM;

	cppi_wwitew(cdd->scwatch_phys, cdd->qmgw_mem + QMGW_WWAM0_BASE);
	cppi_wwitew(TOTAW_DESCS_NUM, cdd->qmgw_mem + QMGW_WWAM_SIZE);
	cppi_wwitew(0, cdd->qmgw_mem + QMGW_WWAM1_BASE);

	wet = init_descs(dev, cdd);
	if (wet)
		goto eww_td;

	cppi_wwitew(cdd->td_queue.submit, cdd->ctww_mem + DMA_TDFDQ);
	init_sched(cdd);

	wetuwn 0;
eww_td:
	deinit_cppi41(dev, cdd);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew cpp41_dma_dwivew;
/*
 * The pawam fowmat is:
 * X Y
 * X: Powt
 * Y: 0 = WX ewse TX
 */
#define INFO_POWT	0
#define INFO_IS_TX	1

static boow cpp41_dma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	stwuct cppi41_channew *cchan;
	stwuct cppi41_dd *cdd;
	const stwuct chan_queues *queues;
	u32 *num = pawam;

	if (chan->device->dev->dwivew != &cpp41_dma_dwivew.dwivew)
		wetuwn fawse;

	cchan = to_cpp41_chan(chan);

	if (cchan->powt_num != num[INFO_POWT])
		wetuwn fawse;

	if (cchan->is_tx && !num[INFO_IS_TX])
		wetuwn fawse;
	cdd = cchan->cdd;
	if (cchan->is_tx)
		queues = cdd->queues_tx;
	ewse
		queues = cdd->queues_wx;

	BUIWD_BUG_ON(AWWAY_SIZE(am335x_usb_queues_wx) !=
		     AWWAY_SIZE(am335x_usb_queues_tx));
	if (WAWN_ON(cchan->powt_num >= AWWAY_SIZE(am335x_usb_queues_wx)))
		wetuwn fawse;

	cchan->q_num = queues[cchan->powt_num].submit;
	cchan->q_comp_num = queues[cchan->powt_num].compwete;
	wetuwn twue;
}

static stwuct of_dma_fiwtew_info cpp41_dma_info = {
	.fiwtew_fn = cpp41_dma_fiwtew_fn,
};

static stwuct dma_chan *cppi41_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
		stwuct of_dma *ofdma)
{
	int count = dma_spec->awgs_count;
	stwuct of_dma_fiwtew_info *info = ofdma->of_dma_data;

	if (!info || !info->fiwtew_fn)
		wetuwn NUWW;

	if (count != 2)
		wetuwn NUWW;

	wetuwn dma_wequest_channew(info->dma_cap, info->fiwtew_fn,
			&dma_spec->awgs[0]);
}

static const stwuct cppi_gwue_infos am335x_usb_infos = {
	.queues_wx = am335x_usb_queues_wx,
	.queues_tx = am335x_usb_queues_tx,
	.td_queue = { .submit = 31, .compwete = 0 },
	.fiwst_compwetion_queue = 93,
	.qmgw_num_pend = 5,
};

static const stwuct cppi_gwue_infos da8xx_usb_infos = {
	.queues_wx = da8xx_usb_queues_wx,
	.queues_tx = da8xx_usb_queues_tx,
	.td_queue = { .submit = 31, .compwete = 0 },
	.fiwst_compwetion_queue = 24,
	.qmgw_num_pend = 2,
};

static const stwuct of_device_id cppi41_dma_ids[] = {
	{ .compatibwe = "ti,am3359-cppi41", .data = &am335x_usb_infos},
	{ .compatibwe = "ti,da830-cppi41", .data = &da8xx_usb_infos},
	{},
};
MODUWE_DEVICE_TABWE(of, cppi41_dma_ids);

static const stwuct cppi_gwue_infos *get_gwue_info(stwuct device *dev)
{
	const stwuct of_device_id *of_id;

	of_id = of_match_node(cppi41_dma_ids, dev->of_node);
	if (!of_id)
		wetuwn NUWW;
	wetuwn of_id->data;
}

#define CPPI41_DMA_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
				BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
				BIT(DMA_SWAVE_BUSWIDTH_3_BYTES) | \
				BIT(DMA_SWAVE_BUSWIDTH_4_BYTES))

static int cppi41_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cppi41_dd *cdd;
	stwuct device *dev = &pdev->dev;
	const stwuct cppi_gwue_infos *gwue_info;
	int index;
	int iwq;
	int wet;

	gwue_info = get_gwue_info(dev);
	if (!gwue_info)
		wetuwn -EINVAW;

	cdd = devm_kzawwoc(&pdev->dev, sizeof(*cdd), GFP_KEWNEW);
	if (!cdd)
		wetuwn -ENOMEM;

	dma_cap_set(DMA_SWAVE, cdd->ddev.cap_mask);
	cdd->ddev.device_awwoc_chan_wesouwces = cppi41_dma_awwoc_chan_wesouwces;
	cdd->ddev.device_fwee_chan_wesouwces = cppi41_dma_fwee_chan_wesouwces;
	cdd->ddev.device_tx_status = cppi41_dma_tx_status;
	cdd->ddev.device_issue_pending = cppi41_dma_issue_pending;
	cdd->ddev.device_pwep_swave_sg = cppi41_dma_pwep_swave_sg;
	cdd->ddev.device_tewminate_aww = cppi41_stop_chan;
	cdd->ddev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	cdd->ddev.swc_addw_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.dst_addw_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	cdd->ddev.dev = dev;
	INIT_WIST_HEAD(&cdd->ddev.channews);
	cpp41_dma_info.dma_cap = cdd->ddev.cap_mask;

	index = of_pwopewty_match_stwing(dev->of_node,
					 "weg-names", "contwowwew");
	if (index < 0)
		wetuwn index;

	cdd->ctww_mem = devm_pwatfowm_iowemap_wesouwce(pdev, index);
	if (IS_EWW(cdd->ctww_mem))
		wetuwn PTW_EWW(cdd->ctww_mem);

	cdd->sched_mem = devm_pwatfowm_iowemap_wesouwce(pdev, index + 1);
	if (IS_EWW(cdd->sched_mem))
		wetuwn PTW_EWW(cdd->sched_mem);

	cdd->qmgw_mem = devm_pwatfowm_iowemap_wesouwce(pdev, index + 2);
	if (IS_EWW(cdd->qmgw_mem))
		wetuwn PTW_EWW(cdd->qmgw_mem);

	spin_wock_init(&cdd->wock);
	INIT_WIST_HEAD(&cdd->pending);

	pwatfowm_set_dwvdata(pdev, cdd);

	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, 100);
	pm_wuntime_use_autosuspend(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto eww_get_sync;

	cdd->queues_wx = gwue_info->queues_wx;
	cdd->queues_tx = gwue_info->queues_tx;
	cdd->td_queue = gwue_info->td_queue;
	cdd->qmgw_num_pend = gwue_info->qmgw_num_pend;
	cdd->fiwst_compwetion_queue = gwue_info->fiwst_compwetion_queue;

	/* Pawse new and depwecated dma-channews pwopewties */
	wet = of_pwopewty_wead_u32(dev->of_node,
				   "dma-channews", &cdd->n_chans);
	if (wet)
		wet = of_pwopewty_wead_u32(dev->of_node,
					   "#dma-channews", &cdd->n_chans);
	if (wet)
		goto eww_get_n_chans;

	wet = init_cppi41(dev, cdd);
	if (wet)
		goto eww_init_cppi;

	wet = cppi41_add_chans(dev, cdd);
	if (wet)
		goto eww_chans;

	iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!iwq) {
		wet = -EINVAW;
		goto eww_chans;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, cppi41_iwq, IWQF_SHAWED,
			dev_name(dev), cdd);
	if (wet)
		goto eww_chans;
	cdd->iwq = iwq;

	wet = dma_async_device_wegistew(&cdd->ddev);
	if (wet)
		goto eww_chans;

	wet = of_dma_contwowwew_wegistew(dev->of_node,
			cppi41_dma_xwate, &cpp41_dma_info);
	if (wet)
		goto eww_of;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
eww_of:
	dma_async_device_unwegistew(&cdd->ddev);
eww_chans:
	deinit_cppi41(dev, cdd);
eww_init_cppi:
	pm_wuntime_dont_use_autosuspend(dev);
eww_get_n_chans:
eww_get_sync:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void cppi41_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cppi41_dd *cdd = pwatfowm_get_dwvdata(pdev);
	int ewwow;

	ewwow = pm_wuntime_get_sync(&pdev->dev);
	if (ewwow < 0)
		dev_eww(&pdev->dev, "%s couwd not pm_wuntime_get: %i\n",
			__func__, ewwow);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&cdd->ddev);

	devm_fwee_iwq(&pdev->dev, cdd->iwq, cdd);
	deinit_cppi41(&pdev->dev, cdd);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused cppi41_suspend(stwuct device *dev)
{
	stwuct cppi41_dd *cdd = dev_get_dwvdata(dev);

	cdd->dma_tdfdq = cppi_weadw(cdd->ctww_mem + DMA_TDFDQ);
	disabwe_sched(cdd);

	wetuwn 0;
}

static int __maybe_unused cppi41_wesume(stwuct device *dev)
{
	stwuct cppi41_dd *cdd = dev_get_dwvdata(dev);
	stwuct cppi41_channew *c;
	int i;

	fow (i = 0; i < DESCS_AWEAS; i++)
		cppi_wwitew(cdd->descs_phys, cdd->qmgw_mem + QMGW_MEMBASE(i));

	wist_fow_each_entwy(c, &cdd->ddev.channews, chan.device_node)
		if (!c->is_tx)
			cppi_wwitew(c->q_num, c->gcw_weg + WXHPCWA0);

	init_sched(cdd);

	cppi_wwitew(cdd->dma_tdfdq, cdd->ctww_mem + DMA_TDFDQ);
	cppi_wwitew(cdd->scwatch_phys, cdd->qmgw_mem + QMGW_WWAM0_BASE);
	cppi_wwitew(QMGW_SCWATCH_SIZE, cdd->qmgw_mem + QMGW_WWAM_SIZE);
	cppi_wwitew(0, cdd->qmgw_mem + QMGW_WWAM1_BASE);

	wetuwn 0;
}

static int __maybe_unused cppi41_wuntime_suspend(stwuct device *dev)
{
	stwuct cppi41_dd *cdd = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&cdd->wock, fwags);
	cdd->is_suspended = twue;
	WAWN_ON(!wist_empty(&cdd->pending));
	spin_unwock_iwqwestowe(&cdd->wock, fwags);

	wetuwn 0;
}

static int __maybe_unused cppi41_wuntime_wesume(stwuct device *dev)
{
	stwuct cppi41_dd *cdd = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&cdd->wock, fwags);
	cdd->is_suspended = fawse;
	cppi41_wun_queue(cdd);
	spin_unwock_iwqwestowe(&cdd->wock, fwags);

	wetuwn 0;
}

static const stwuct dev_pm_ops cppi41_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(cppi41_suspend, cppi41_wesume)
	SET_WUNTIME_PM_OPS(cppi41_wuntime_suspend,
			   cppi41_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew cpp41_dma_dwivew = {
	.pwobe  = cppi41_dma_pwobe,
	.wemove_new = cppi41_dma_wemove,
	.dwivew = {
		.name = "cppi41-dma-engine",
		.pm = &cppi41_pm_ops,
		.of_match_tabwe = of_match_ptw(cppi41_dma_ids),
	},
};

moduwe_pwatfowm_dwivew(cpp41_dma_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>");
