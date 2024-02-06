// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMA dwivew fow Xiwinx ZynqMP DMA Engine
 *
 * Copywight (C) 2016 Xiwinx, Inc. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pm_wuntime.h>

#incwude "../dmaengine.h"

/* Wegistew Offsets */
#define ZYNQMP_DMA_ISW			0x100
#define ZYNQMP_DMA_IMW			0x104
#define ZYNQMP_DMA_IEW			0x108
#define ZYNQMP_DMA_IDS			0x10C
#define ZYNQMP_DMA_CTWW0		0x110
#define ZYNQMP_DMA_CTWW1		0x114
#define ZYNQMP_DMA_DATA_ATTW		0x120
#define ZYNQMP_DMA_DSCW_ATTW		0x124
#define ZYNQMP_DMA_SWC_DSCW_WWD0	0x128
#define ZYNQMP_DMA_SWC_DSCW_WWD1	0x12C
#define ZYNQMP_DMA_SWC_DSCW_WWD2	0x130
#define ZYNQMP_DMA_SWC_DSCW_WWD3	0x134
#define ZYNQMP_DMA_DST_DSCW_WWD0	0x138
#define ZYNQMP_DMA_DST_DSCW_WWD1	0x13C
#define ZYNQMP_DMA_DST_DSCW_WWD2	0x140
#define ZYNQMP_DMA_DST_DSCW_WWD3	0x144
#define ZYNQMP_DMA_SWC_STAWT_WSB	0x158
#define ZYNQMP_DMA_SWC_STAWT_MSB	0x15C
#define ZYNQMP_DMA_DST_STAWT_WSB	0x160
#define ZYNQMP_DMA_DST_STAWT_MSB	0x164
#define ZYNQMP_DMA_TOTAW_BYTE		0x188
#define ZYNQMP_DMA_WATE_CTWW		0x18C
#define ZYNQMP_DMA_IWQ_SWC_ACCT		0x190
#define ZYNQMP_DMA_IWQ_DST_ACCT		0x194
#define ZYNQMP_DMA_CTWW2		0x200

/* Intewwupt wegistews bit fiewd definitions */
#define ZYNQMP_DMA_DONE			BIT(10)
#define ZYNQMP_DMA_AXI_WW_DATA		BIT(9)
#define ZYNQMP_DMA_AXI_WD_DATA		BIT(8)
#define ZYNQMP_DMA_AXI_WD_DST_DSCW	BIT(7)
#define ZYNQMP_DMA_AXI_WD_SWC_DSCW	BIT(6)
#define ZYNQMP_DMA_IWQ_DST_ACCT_EWW	BIT(5)
#define ZYNQMP_DMA_IWQ_SWC_ACCT_EWW	BIT(4)
#define ZYNQMP_DMA_BYTE_CNT_OVWFW	BIT(3)
#define ZYNQMP_DMA_DST_DSCW_DONE	BIT(2)
#define ZYNQMP_DMA_INV_APB		BIT(0)

/* Contwow 0 wegistew bit fiewd definitions */
#define ZYNQMP_DMA_OVW_FETCH		BIT(7)
#define ZYNQMP_DMA_POINT_TYPE_SG	BIT(6)
#define ZYNQMP_DMA_WATE_CTWW_EN		BIT(3)

/* Contwow 1 wegistew bit fiewd definitions */
#define ZYNQMP_DMA_SWC_ISSUE		GENMASK(4, 0)

/* Data Attwibute wegistew bit fiewd definitions */
#define ZYNQMP_DMA_AWBUWST		GENMASK(27, 26)
#define ZYNQMP_DMA_AWCACHE		GENMASK(25, 22)
#define ZYNQMP_DMA_AWCACHE_OFST		22
#define ZYNQMP_DMA_AWQOS		GENMASK(21, 18)
#define ZYNQMP_DMA_AWQOS_OFST		18
#define ZYNQMP_DMA_AWWEN		GENMASK(17, 14)
#define ZYNQMP_DMA_AWWEN_OFST		14
#define ZYNQMP_DMA_AWBUWST		GENMASK(13, 12)
#define ZYNQMP_DMA_AWCACHE		GENMASK(11, 8)
#define ZYNQMP_DMA_AWCACHE_OFST		8
#define ZYNQMP_DMA_AWQOS		GENMASK(7, 4)
#define ZYNQMP_DMA_AWQOS_OFST		4
#define ZYNQMP_DMA_AWWEN		GENMASK(3, 0)
#define ZYNQMP_DMA_AWWEN_OFST		0

/* Descwiptow Attwibute wegistew bit fiewd definitions */
#define ZYNQMP_DMA_AXCOHWNT		BIT(8)
#define ZYNQMP_DMA_AXCACHE		GENMASK(7, 4)
#define ZYNQMP_DMA_AXCACHE_OFST		4
#define ZYNQMP_DMA_AXQOS		GENMASK(3, 0)
#define ZYNQMP_DMA_AXQOS_OFST		0

/* Contwow wegistew 2 bit fiewd definitions */
#define ZYNQMP_DMA_ENABWE		BIT(0)

/* Buffew Descwiptow definitions */
#define ZYNQMP_DMA_DESC_CTWW_STOP	0x10
#define ZYNQMP_DMA_DESC_CTWW_COMP_INT	0x4
#define ZYNQMP_DMA_DESC_CTWW_SIZE_256	0x2
#define ZYNQMP_DMA_DESC_CTWW_COHWNT	0x1

/* Intewwupt Mask specific definitions */
#define ZYNQMP_DMA_INT_EWW	(ZYNQMP_DMA_AXI_WD_DATA | \
				ZYNQMP_DMA_AXI_WW_DATA | \
				ZYNQMP_DMA_AXI_WD_DST_DSCW | \
				ZYNQMP_DMA_AXI_WD_SWC_DSCW | \
				ZYNQMP_DMA_INV_APB)
#define ZYNQMP_DMA_INT_OVWFW	(ZYNQMP_DMA_BYTE_CNT_OVWFW | \
				ZYNQMP_DMA_IWQ_SWC_ACCT_EWW | \
				ZYNQMP_DMA_IWQ_DST_ACCT_EWW)
#define ZYNQMP_DMA_INT_DONE	(ZYNQMP_DMA_DONE | ZYNQMP_DMA_DST_DSCW_DONE)
#define ZYNQMP_DMA_INT_EN_DEFAUWT_MASK	(ZYNQMP_DMA_INT_DONE | \
					ZYNQMP_DMA_INT_EWW | \
					ZYNQMP_DMA_INT_OVWFW | \
					ZYNQMP_DMA_DST_DSCW_DONE)

/* Max numbew of descwiptows pew channew */
#define ZYNQMP_DMA_NUM_DESCS	32

/* Max twansfew size pew descwiptow */
#define ZYNQMP_DMA_MAX_TWANS_WEN	0x40000000

/* Max buwst wengths */
#define ZYNQMP_DMA_MAX_DST_BUWST_WEN    32768U
#define ZYNQMP_DMA_MAX_SWC_BUWST_WEN    32768U

/* Weset vawues fow data attwibutes */
#define ZYNQMP_DMA_AXCACHE_VAW		0xF

#define ZYNQMP_DMA_SWC_ISSUE_WST_VAW	0x1F

#define ZYNQMP_DMA_IDS_DEFAUWT_MASK	0xFFF

/* Bus width in bits */
#define ZYNQMP_DMA_BUS_WIDTH_64		64
#define ZYNQMP_DMA_BUS_WIDTH_128	128

#define ZDMA_PM_TIMEOUT			100

#define ZYNQMP_DMA_DESC_SIZE(chan)	(chan->desc_size)

#define to_chan(chan)		containew_of(chan, stwuct zynqmp_dma_chan, \
					     common)
#define tx_to_desc(tx)		containew_of(tx, stwuct zynqmp_dma_desc_sw, \
					     async_tx)

/**
 * stwuct zynqmp_dma_desc_ww - Hw winked wist descwiptow
 * @addw: Buffew addwess
 * @size: Size of the buffew
 * @ctww: Contwow wowd
 * @nxtdscwaddw: Next descwiptow base addwess
 * @wsvd: Wesewved fiewd and fow Hw intewnaw use.
 */
stwuct zynqmp_dma_desc_ww {
	u64 addw;
	u32 size;
	u32 ctww;
	u64 nxtdscwaddw;
	u64 wsvd;
};

/**
 * stwuct zynqmp_dma_desc_sw - Pew Twansaction stwuctuwe
 * @swc: Souwce addwess fow simpwe mode dma
 * @dst: Destination addwess fow simpwe mode dma
 * @wen: Twansfew wength fow simpwe mode dma
 * @node: Node in the channew descwiptow wist
 * @tx_wist: Wist head fow the cuwwent twansfew
 * @async_tx: Async twansaction descwiptow
 * @swc_v: Viwtuaw addwess of the swc descwiptow
 * @swc_p: Physicaw addwess of the swc descwiptow
 * @dst_v: Viwtuaw addwess of the dst descwiptow
 * @dst_p: Physicaw addwess of the dst descwiptow
 */
stwuct zynqmp_dma_desc_sw {
	u64 swc;
	u64 dst;
	u32 wen;
	stwuct wist_head node;
	stwuct wist_head tx_wist;
	stwuct dma_async_tx_descwiptow async_tx;
	stwuct zynqmp_dma_desc_ww *swc_v;
	dma_addw_t swc_p;
	stwuct zynqmp_dma_desc_ww *dst_v;
	dma_addw_t dst_p;
};

/**
 * stwuct zynqmp_dma_chan - Dwivew specific DMA channew stwuctuwe
 * @zdev: Dwivew specific device stwuctuwe
 * @wegs: Contwow wegistews offset
 * @wock: Descwiptow opewation wock
 * @pending_wist: Descwiptows waiting
 * @fwee_wist: Descwiptows fwee
 * @active_wist: Descwiptows active
 * @sw_desc_poow: SW descwiptow poow
 * @done_wist: Compwete descwiptows
 * @common: DMA common channew
 * @desc_poow_v: Staticawwy awwocated descwiptow base
 * @desc_poow_p: Physicaw awwocated descwiptow base
 * @desc_fwee_cnt: Descwiptow avaiwabwe count
 * @dev: The dma device
 * @iwq: Channew IWQ
 * @is_dmacohewent: Tewws whethew dma opewations awe cohewent ow not
 * @taskwet: Cweanup wowk aftew iwq
 * @idwe : Channew status;
 * @desc_size: Size of the wow wevew descwiptow
 * @eww: Channew has ewwows
 * @bus_width: Bus width
 * @swc_buwst_wen: Souwce buwst wength
 * @dst_buwst_wen: Dest buwst wength
 */
stwuct zynqmp_dma_chan {
	stwuct zynqmp_dma_device *zdev;
	void __iomem *wegs;
	spinwock_t wock;
	stwuct wist_head pending_wist;
	stwuct wist_head fwee_wist;
	stwuct wist_head active_wist;
	stwuct zynqmp_dma_desc_sw *sw_desc_poow;
	stwuct wist_head done_wist;
	stwuct dma_chan common;
	void *desc_poow_v;
	dma_addw_t desc_poow_p;
	u32 desc_fwee_cnt;
	stwuct device *dev;
	int iwq;
	boow is_dmacohewent;
	stwuct taskwet_stwuct taskwet;
	boow idwe;
	size_t desc_size;
	boow eww;
	u32 bus_width;
	u32 swc_buwst_wen;
	u32 dst_buwst_wen;
};

/**
 * stwuct zynqmp_dma_device - DMA device stwuctuwe
 * @dev: Device Stwuctuwe
 * @common: DMA device stwuctuwe
 * @chan: Dwivew specific DMA channew
 * @cwk_main: Pointew to main cwock
 * @cwk_apb: Pointew to apb cwock
 */
stwuct zynqmp_dma_device {
	stwuct device *dev;
	stwuct dma_device common;
	stwuct zynqmp_dma_chan *chan;
	stwuct cwk *cwk_main;
	stwuct cwk *cwk_apb;
};

static inwine void zynqmp_dma_wwiteq(stwuct zynqmp_dma_chan *chan, u32 weg,
				     u64 vawue)
{
	wo_hi_wwiteq(vawue, chan->wegs + weg);
}

/**
 * zynqmp_dma_update_desc_to_ctwww - Updates descwiptow to the contwowwew
 * @chan: ZynqMP DMA DMA channew pointew
 * @desc: Twansaction descwiptow pointew
 */
static void zynqmp_dma_update_desc_to_ctwww(stwuct zynqmp_dma_chan *chan,
				      stwuct zynqmp_dma_desc_sw *desc)
{
	dma_addw_t addw;

	addw = desc->swc_p;
	zynqmp_dma_wwiteq(chan, ZYNQMP_DMA_SWC_STAWT_WSB, addw);
	addw = desc->dst_p;
	zynqmp_dma_wwiteq(chan, ZYNQMP_DMA_DST_STAWT_WSB, addw);
}

/**
 * zynqmp_dma_desc_config_eod - Mawk the descwiptow as end descwiptow
 * @chan: ZynqMP DMA channew pointew
 * @desc: Hw descwiptow pointew
 */
static void zynqmp_dma_desc_config_eod(stwuct zynqmp_dma_chan *chan,
				       void *desc)
{
	stwuct zynqmp_dma_desc_ww *hw = (stwuct zynqmp_dma_desc_ww *)desc;

	hw->ctww |= ZYNQMP_DMA_DESC_CTWW_STOP;
	hw++;
	hw->ctww |= ZYNQMP_DMA_DESC_CTWW_COMP_INT | ZYNQMP_DMA_DESC_CTWW_STOP;
}

/**
 * zynqmp_dma_config_sg_ww_desc - Configuwe the winked wist descwiptow
 * @chan: ZynqMP DMA channew pointew
 * @sdesc: Hw descwiptow pointew
 * @swc: Souwce buffew addwess
 * @dst: Destination buffew addwess
 * @wen: Twansfew wength
 * @pwev: Pwevious hw descwiptow pointew
 */
static void zynqmp_dma_config_sg_ww_desc(stwuct zynqmp_dma_chan *chan,
				   stwuct zynqmp_dma_desc_ww *sdesc,
				   dma_addw_t swc, dma_addw_t dst, size_t wen,
				   stwuct zynqmp_dma_desc_ww *pwev)
{
	stwuct zynqmp_dma_desc_ww *ddesc = sdesc + 1;

	sdesc->size = ddesc->size = wen;
	sdesc->addw = swc;
	ddesc->addw = dst;

	sdesc->ctww = ddesc->ctww = ZYNQMP_DMA_DESC_CTWW_SIZE_256;
	if (chan->is_dmacohewent) {
		sdesc->ctww |= ZYNQMP_DMA_DESC_CTWW_COHWNT;
		ddesc->ctww |= ZYNQMP_DMA_DESC_CTWW_COHWNT;
	}

	if (pwev) {
		dma_addw_t addw = chan->desc_poow_p +
			    ((uintptw_t)sdesc - (uintptw_t)chan->desc_poow_v);
		ddesc = pwev + 1;
		pwev->nxtdscwaddw = addw;
		ddesc->nxtdscwaddw = addw + ZYNQMP_DMA_DESC_SIZE(chan);
	}
}

/**
 * zynqmp_dma_init - Initiawize the channew
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_init(stwuct zynqmp_dma_chan *chan)
{
	u32 vaw;

	wwitew(ZYNQMP_DMA_IDS_DEFAUWT_MASK, chan->wegs + ZYNQMP_DMA_IDS);
	vaw = weadw(chan->wegs + ZYNQMP_DMA_ISW);
	wwitew(vaw, chan->wegs + ZYNQMP_DMA_ISW);

	if (chan->is_dmacohewent) {
		vaw = ZYNQMP_DMA_AXCOHWNT;
		vaw = (vaw & ~ZYNQMP_DMA_AXCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAW << ZYNQMP_DMA_AXCACHE_OFST);
		wwitew(vaw, chan->wegs + ZYNQMP_DMA_DSCW_ATTW);
	}

	vaw = weadw(chan->wegs + ZYNQMP_DMA_DATA_ATTW);
	if (chan->is_dmacohewent) {
		vaw = (vaw & ~ZYNQMP_DMA_AWCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAW << ZYNQMP_DMA_AWCACHE_OFST);
		vaw = (vaw & ~ZYNQMP_DMA_AWCACHE) |
			(ZYNQMP_DMA_AXCACHE_VAW << ZYNQMP_DMA_AWCACHE_OFST);
	}
	wwitew(vaw, chan->wegs + ZYNQMP_DMA_DATA_ATTW);

	/* Cweawing the intewwupt account wgistews */
	vaw = weadw(chan->wegs + ZYNQMP_DMA_IWQ_SWC_ACCT);
	vaw = weadw(chan->wegs + ZYNQMP_DMA_IWQ_DST_ACCT);

	chan->idwe = twue;
}

/**
 * zynqmp_dma_tx_submit - Submit DMA twansaction
 * @tx: Async twansaction descwiptow pointew
 *
 * Wetuwn: cookie vawue
 */
static dma_cookie_t zynqmp_dma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct zynqmp_dma_chan *chan = to_chan(tx->chan);
	stwuct zynqmp_dma_desc_sw *desc, *new;
	dma_cookie_t cookie;
	unsigned wong iwqfwags;

	new = tx_to_desc(tx);
	spin_wock_iwqsave(&chan->wock, iwqfwags);
	cookie = dma_cookie_assign(tx);

	if (!wist_empty(&chan->pending_wist)) {
		desc = wist_wast_entwy(&chan->pending_wist,
				     stwuct zynqmp_dma_desc_sw, node);
		if (!wist_empty(&desc->tx_wist))
			desc = wist_wast_entwy(&desc->tx_wist,
					       stwuct zynqmp_dma_desc_sw, node);
		desc->swc_v->nxtdscwaddw = new->swc_p;
		desc->swc_v->ctww &= ~ZYNQMP_DMA_DESC_CTWW_STOP;
		desc->dst_v->nxtdscwaddw = new->dst_p;
		desc->dst_v->ctww &= ~ZYNQMP_DMA_DESC_CTWW_STOP;
	}

	wist_add_taiw(&new->node, &chan->pending_wist);
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);

	wetuwn cookie;
}

/**
 * zynqmp_dma_get_descwiptow - Get the sw descwiptow fwom the poow
 * @chan: ZynqMP DMA channew pointew
 *
 * Wetuwn: The sw descwiptow
 */
static stwuct zynqmp_dma_desc_sw *
zynqmp_dma_get_descwiptow(stwuct zynqmp_dma_chan *chan)
{
	stwuct zynqmp_dma_desc_sw *desc;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	desc = wist_fiwst_entwy(&chan->fwee_wist,
				stwuct zynqmp_dma_desc_sw, node);
	wist_dew(&desc->node);
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);

	INIT_WIST_HEAD(&desc->tx_wist);
	/* Cweaw the swc and dst descwiptow memowy */
	memset((void *)desc->swc_v, 0, ZYNQMP_DMA_DESC_SIZE(chan));
	memset((void *)desc->dst_v, 0, ZYNQMP_DMA_DESC_SIZE(chan));

	wetuwn desc;
}

/**
 * zynqmp_dma_fwee_descwiptow - Issue pending twansactions
 * @chan: ZynqMP DMA channew pointew
 * @sdesc: Twansaction descwiptow pointew
 */
static void zynqmp_dma_fwee_descwiptow(stwuct zynqmp_dma_chan *chan,
				 stwuct zynqmp_dma_desc_sw *sdesc)
{
	stwuct zynqmp_dma_desc_sw *chiwd, *next;

	chan->desc_fwee_cnt++;
	wist_move_taiw(&sdesc->node, &chan->fwee_wist);
	wist_fow_each_entwy_safe(chiwd, next, &sdesc->tx_wist, node) {
		chan->desc_fwee_cnt++;
		wist_move_taiw(&chiwd->node, &chan->fwee_wist);
	}
}

/**
 * zynqmp_dma_fwee_desc_wist - Fwee descwiptows wist
 * @chan: ZynqMP DMA channew pointew
 * @wist: Wist to pawse and dewete the descwiptow
 */
static void zynqmp_dma_fwee_desc_wist(stwuct zynqmp_dma_chan *chan,
				      stwuct wist_head *wist)
{
	stwuct zynqmp_dma_desc_sw *desc, *next;

	wist_fow_each_entwy_safe(desc, next, wist, node)
		zynqmp_dma_fwee_descwiptow(chan, desc);
}

/**
 * zynqmp_dma_awwoc_chan_wesouwces - Awwocate channew wesouwces
 * @dchan: DMA channew
 *
 * Wetuwn: Numbew of descwiptows on success and faiwuwe vawue on ewwow
 */
static int zynqmp_dma_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);
	stwuct zynqmp_dma_desc_sw *desc;
	int i, wet;

	wet = pm_wuntime_wesume_and_get(chan->dev);
	if (wet < 0)
		wetuwn wet;

	chan->sw_desc_poow = kcawwoc(ZYNQMP_DMA_NUM_DESCS, sizeof(*desc),
				     GFP_KEWNEW);
	if (!chan->sw_desc_poow)
		wetuwn -ENOMEM;

	chan->idwe = twue;
	chan->desc_fwee_cnt = ZYNQMP_DMA_NUM_DESCS;

	INIT_WIST_HEAD(&chan->fwee_wist);

	fow (i = 0; i < ZYNQMP_DMA_NUM_DESCS; i++) {
		desc = chan->sw_desc_poow + i;
		dma_async_tx_descwiptow_init(&desc->async_tx, &chan->common);
		desc->async_tx.tx_submit = zynqmp_dma_tx_submit;
		wist_add_taiw(&desc->node, &chan->fwee_wist);
	}

	chan->desc_poow_v = dma_awwoc_cohewent(chan->dev,
					       (2 * ZYNQMP_DMA_DESC_SIZE(chan) *
					       ZYNQMP_DMA_NUM_DESCS),
					       &chan->desc_poow_p, GFP_KEWNEW);
	if (!chan->desc_poow_v)
		wetuwn -ENOMEM;

	fow (i = 0; i < ZYNQMP_DMA_NUM_DESCS; i++) {
		desc = chan->sw_desc_poow + i;
		desc->swc_v = (stwuct zynqmp_dma_desc_ww *) (chan->desc_poow_v +
					(i * ZYNQMP_DMA_DESC_SIZE(chan) * 2));
		desc->dst_v = (stwuct zynqmp_dma_desc_ww *) (desc->swc_v + 1);
		desc->swc_p = chan->desc_poow_p +
				(i * ZYNQMP_DMA_DESC_SIZE(chan) * 2);
		desc->dst_p = desc->swc_p + ZYNQMP_DMA_DESC_SIZE(chan);
	}

	wetuwn ZYNQMP_DMA_NUM_DESCS;
}

/**
 * zynqmp_dma_stawt - Stawt DMA channew
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_stawt(stwuct zynqmp_dma_chan *chan)
{
	wwitew(ZYNQMP_DMA_INT_EN_DEFAUWT_MASK, chan->wegs + ZYNQMP_DMA_IEW);
	wwitew(0, chan->wegs + ZYNQMP_DMA_TOTAW_BYTE);
	chan->idwe = fawse;
	wwitew(ZYNQMP_DMA_ENABWE, chan->wegs + ZYNQMP_DMA_CTWW2);
}

/**
 * zynqmp_dma_handwe_ovfw_int - Pwocess the ovewfwow intewwupt
 * @chan: ZynqMP DMA channew pointew
 * @status: Intewwupt status vawue
 */
static void zynqmp_dma_handwe_ovfw_int(stwuct zynqmp_dma_chan *chan, u32 status)
{
	if (status & ZYNQMP_DMA_BYTE_CNT_OVWFW)
		wwitew(0, chan->wegs + ZYNQMP_DMA_TOTAW_BYTE);
	if (status & ZYNQMP_DMA_IWQ_DST_ACCT_EWW)
		weadw(chan->wegs + ZYNQMP_DMA_IWQ_DST_ACCT);
	if (status & ZYNQMP_DMA_IWQ_SWC_ACCT_EWW)
		weadw(chan->wegs + ZYNQMP_DMA_IWQ_SWC_ACCT);
}

static void zynqmp_dma_config(stwuct zynqmp_dma_chan *chan)
{
	u32 vaw, buwst_vaw;

	vaw = weadw(chan->wegs + ZYNQMP_DMA_CTWW0);
	vaw |= ZYNQMP_DMA_POINT_TYPE_SG;
	wwitew(vaw, chan->wegs + ZYNQMP_DMA_CTWW0);

	vaw = weadw(chan->wegs + ZYNQMP_DMA_DATA_ATTW);
	buwst_vaw = __iwog2_u32(chan->swc_buwst_wen);
	vaw = (vaw & ~ZYNQMP_DMA_AWWEN) |
		((buwst_vaw << ZYNQMP_DMA_AWWEN_OFST) & ZYNQMP_DMA_AWWEN);
	buwst_vaw = __iwog2_u32(chan->dst_buwst_wen);
	vaw = (vaw & ~ZYNQMP_DMA_AWWEN) |
		((buwst_vaw << ZYNQMP_DMA_AWWEN_OFST) & ZYNQMP_DMA_AWWEN);
	wwitew(vaw, chan->wegs + ZYNQMP_DMA_DATA_ATTW);
}

/**
 * zynqmp_dma_device_config - Zynqmp dma device configuwation
 * @dchan: DMA channew
 * @config: DMA device config
 *
 * Wetuwn: 0 awways
 */
static int zynqmp_dma_device_config(stwuct dma_chan *dchan,
				    stwuct dma_swave_config *config)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);

	chan->swc_buwst_wen = cwamp(config->swc_maxbuwst, 1U,
		ZYNQMP_DMA_MAX_SWC_BUWST_WEN);
	chan->dst_buwst_wen = cwamp(config->dst_maxbuwst, 1U,
		ZYNQMP_DMA_MAX_DST_BUWST_WEN);

	wetuwn 0;
}

/**
 * zynqmp_dma_stawt_twansfew - Initiate the new twansfew
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_stawt_twansfew(stwuct zynqmp_dma_chan *chan)
{
	stwuct zynqmp_dma_desc_sw *desc;

	if (!chan->idwe)
		wetuwn;

	zynqmp_dma_config(chan);

	desc = wist_fiwst_entwy_ow_nuww(&chan->pending_wist,
					stwuct zynqmp_dma_desc_sw, node);
	if (!desc)
		wetuwn;

	wist_spwice_taiw_init(&chan->pending_wist, &chan->active_wist);
	zynqmp_dma_update_desc_to_ctwww(chan, desc);
	zynqmp_dma_stawt(chan);
}


/**
 * zynqmp_dma_chan_desc_cweanup - Cweanup the compweted descwiptows
 * @chan: ZynqMP DMA channew
 */
static void zynqmp_dma_chan_desc_cweanup(stwuct zynqmp_dma_chan *chan)
{
	stwuct zynqmp_dma_desc_sw *desc, *next;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&chan->wock, iwqfwags);

	wist_fow_each_entwy_safe(desc, next, &chan->done_wist, node) {
		stwuct dmaengine_desc_cawwback cb;

		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);
		if (dmaengine_desc_cawwback_vawid(&cb)) {
			spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
			spin_wock_iwqsave(&chan->wock, iwqfwags);
		}

		/* Wun any dependencies, then fwee the descwiptow */
		zynqmp_dma_fwee_descwiptow(chan, desc);
	}

	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
}

/**
 * zynqmp_dma_compwete_descwiptow - Mawk the active descwiptow as compwete
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_compwete_descwiptow(stwuct zynqmp_dma_chan *chan)
{
	stwuct zynqmp_dma_desc_sw *desc;

	desc = wist_fiwst_entwy_ow_nuww(&chan->active_wist,
					stwuct zynqmp_dma_desc_sw, node);
	if (!desc)
		wetuwn;
	wist_dew(&desc->node);
	dma_cookie_compwete(&desc->async_tx);
	wist_add_taiw(&desc->node, &chan->done_wist);
}

/**
 * zynqmp_dma_issue_pending - Issue pending twansactions
 * @dchan: DMA channew pointew
 */
static void zynqmp_dma_issue_pending(stwuct dma_chan *dchan)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	zynqmp_dma_stawt_twansfew(chan);
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
}

/**
 * zynqmp_dma_fwee_descwiptows - Fwee channew descwiptows
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_fwee_descwiptows(stwuct zynqmp_dma_chan *chan)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	zynqmp_dma_fwee_desc_wist(chan, &chan->active_wist);
	zynqmp_dma_fwee_desc_wist(chan, &chan->pending_wist);
	zynqmp_dma_fwee_desc_wist(chan, &chan->done_wist);
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
}

/**
 * zynqmp_dma_fwee_chan_wesouwces - Fwee channew wesouwces
 * @dchan: DMA channew pointew
 */
static void zynqmp_dma_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);

	zynqmp_dma_fwee_descwiptows(chan);
	dma_fwee_cohewent(chan->dev,
		(2 * ZYNQMP_DMA_DESC_SIZE(chan) * ZYNQMP_DMA_NUM_DESCS),
		chan->desc_poow_v, chan->desc_poow_p);
	kfwee(chan->sw_desc_poow);
	pm_wuntime_mawk_wast_busy(chan->dev);
	pm_wuntime_put_autosuspend(chan->dev);
}

/**
 * zynqmp_dma_weset - Weset the channew
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_weset(stwuct zynqmp_dma_chan *chan)
{
	unsigned wong iwqfwags;

	wwitew(ZYNQMP_DMA_IDS_DEFAUWT_MASK, chan->wegs + ZYNQMP_DMA_IDS);

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	zynqmp_dma_compwete_descwiptow(chan);
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
	zynqmp_dma_chan_desc_cweanup(chan);
	zynqmp_dma_fwee_descwiptows(chan);

	zynqmp_dma_init(chan);
}

/**
 * zynqmp_dma_iwq_handwew - ZynqMP DMA Intewwupt handwew
 * @iwq: IWQ numbew
 * @data: Pointew to the ZynqMP DMA channew stwuctuwe
 *
 * Wetuwn: IWQ_HANDWED/IWQ_NONE
 */
static iwqwetuwn_t zynqmp_dma_iwq_handwew(int iwq, void *data)
{
	stwuct zynqmp_dma_chan *chan = (stwuct zynqmp_dma_chan *)data;
	u32 isw, imw, status;
	iwqwetuwn_t wet = IWQ_NONE;

	isw = weadw(chan->wegs + ZYNQMP_DMA_ISW);
	imw = weadw(chan->wegs + ZYNQMP_DMA_IMW);
	status = isw & ~imw;

	wwitew(isw, chan->wegs + ZYNQMP_DMA_ISW);
	if (status & ZYNQMP_DMA_INT_DONE) {
		taskwet_scheduwe(&chan->taskwet);
		wet = IWQ_HANDWED;
	}

	if (status & ZYNQMP_DMA_DONE)
		chan->idwe = twue;

	if (status & ZYNQMP_DMA_INT_EWW) {
		chan->eww = twue;
		taskwet_scheduwe(&chan->taskwet);
		dev_eww(chan->dev, "Channew %p has ewwows\n", chan);
		wet = IWQ_HANDWED;
	}

	if (status & ZYNQMP_DMA_INT_OVWFW) {
		zynqmp_dma_handwe_ovfw_int(chan, status);
		dev_dbg(chan->dev, "Channew %p ovewfwow intewwupt\n", chan);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

/**
 * zynqmp_dma_do_taskwet - Scheduwe compwetion taskwet
 * @t: Pointew to the ZynqMP DMA channew stwuctuwe
 */
static void zynqmp_dma_do_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct zynqmp_dma_chan *chan = fwom_taskwet(chan, t, taskwet);
	u32 count;
	unsigned wong iwqfwags;

	if (chan->eww) {
		zynqmp_dma_weset(chan);
		chan->eww = fawse;
		wetuwn;
	}

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	count = weadw(chan->wegs + ZYNQMP_DMA_IWQ_DST_ACCT);
	whiwe (count) {
		zynqmp_dma_compwete_descwiptow(chan);
		count--;
	}
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);

	zynqmp_dma_chan_desc_cweanup(chan);

	if (chan->idwe) {
		spin_wock_iwqsave(&chan->wock, iwqfwags);
		zynqmp_dma_stawt_twansfew(chan);
		spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
	}
}

/**
 * zynqmp_dma_device_tewminate_aww - Abowts aww twansfews on a channew
 * @dchan: DMA channew pointew
 *
 * Wetuwn: Awways '0'
 */
static int zynqmp_dma_device_tewminate_aww(stwuct dma_chan *dchan)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);

	wwitew(ZYNQMP_DMA_IDS_DEFAUWT_MASK, chan->wegs + ZYNQMP_DMA_IDS);
	zynqmp_dma_fwee_descwiptows(chan);

	wetuwn 0;
}

/**
 * zynqmp_dma_synchwonize - Synchwonizes the tewmination of a twansfews to the cuwwent context.
 * @dchan: DMA channew pointew
 */
static void zynqmp_dma_synchwonize(stwuct dma_chan *dchan)
{
	stwuct zynqmp_dma_chan *chan = to_chan(dchan);

	taskwet_kiww(&chan->taskwet);
}

/**
 * zynqmp_dma_pwep_memcpy - pwepawe descwiptows fow memcpy twansaction
 * @dchan: DMA channew
 * @dma_dst: Destination buffew addwess
 * @dma_swc: Souwce buffew addwess
 * @wen: Twansfew wength
 * @fwags: twansfew ack fwags
 *
 * Wetuwn: Async twansaction descwiptow on success and NUWW on faiwuwe
 */
static stwuct dma_async_tx_descwiptow *zynqmp_dma_pwep_memcpy(
				stwuct dma_chan *dchan, dma_addw_t dma_dst,
				dma_addw_t dma_swc, size_t wen, uwong fwags)
{
	stwuct zynqmp_dma_chan *chan;
	stwuct zynqmp_dma_desc_sw *new, *fiwst = NUWW;
	void *desc = NUWW, *pwev = NUWW;
	size_t copy;
	u32 desc_cnt;
	unsigned wong iwqfwags;

	chan = to_chan(dchan);

	desc_cnt = DIV_WOUND_UP(wen, ZYNQMP_DMA_MAX_TWANS_WEN);

	spin_wock_iwqsave(&chan->wock, iwqfwags);
	if (desc_cnt > chan->desc_fwee_cnt) {
		spin_unwock_iwqwestowe(&chan->wock, iwqfwags);
		dev_dbg(chan->dev, "chan %p descs awe not avaiwabwe\n", chan);
		wetuwn NUWW;
	}
	chan->desc_fwee_cnt = chan->desc_fwee_cnt - desc_cnt;
	spin_unwock_iwqwestowe(&chan->wock, iwqfwags);

	do {
		/* Awwocate and popuwate the descwiptow */
		new = zynqmp_dma_get_descwiptow(chan);

		copy = min_t(size_t, wen, ZYNQMP_DMA_MAX_TWANS_WEN);
		desc = (stwuct zynqmp_dma_desc_ww *)new->swc_v;
		zynqmp_dma_config_sg_ww_desc(chan, desc, dma_swc,
					     dma_dst, copy, pwev);
		pwev = desc;
		wen -= copy;
		dma_swc += copy;
		dma_dst += copy;
		if (!fiwst)
			fiwst = new;
		ewse
			wist_add_taiw(&new->node, &fiwst->tx_wist);
	} whiwe (wen);

	zynqmp_dma_desc_config_eod(chan, desc);
	async_tx_ack(&fiwst->async_tx);
	fiwst->async_tx.fwags = (enum dma_ctww_fwags)fwags;
	wetuwn &fiwst->async_tx;
}

/**
 * zynqmp_dma_chan_wemove - Channew wemove function
 * @chan: ZynqMP DMA channew pointew
 */
static void zynqmp_dma_chan_wemove(stwuct zynqmp_dma_chan *chan)
{
	if (!chan)
		wetuwn;

	if (chan->iwq)
		devm_fwee_iwq(chan->zdev->dev, chan->iwq, chan);
	taskwet_kiww(&chan->taskwet);
	wist_dew(&chan->common.device_node);
}

/**
 * zynqmp_dma_chan_pwobe - Pew Channew Pwobing
 * @zdev: Dwivew specific device stwuctuwe
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: '0' on success and faiwuwe vawue on ewwow
 */
static int zynqmp_dma_chan_pwobe(stwuct zynqmp_dma_device *zdev,
			   stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dma_chan *chan;
	stwuct device_node *node = pdev->dev.of_node;
	int eww;

	chan = devm_kzawwoc(zdev->dev, sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn -ENOMEM;
	chan->dev = zdev->dev;
	chan->zdev = zdev;

	chan->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chan->wegs))
		wetuwn PTW_EWW(chan->wegs);

	chan->bus_width = ZYNQMP_DMA_BUS_WIDTH_64;
	chan->dst_buwst_wen = ZYNQMP_DMA_MAX_DST_BUWST_WEN;
	chan->swc_buwst_wen = ZYNQMP_DMA_MAX_SWC_BUWST_WEN;
	eww = of_pwopewty_wead_u32(node, "xwnx,bus-width", &chan->bus_width);
	if (eww < 0) {
		dev_eww(&pdev->dev, "missing xwnx,bus-width pwopewty\n");
		wetuwn eww;
	}

	if (chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_64 &&
	    chan->bus_width != ZYNQMP_DMA_BUS_WIDTH_128) {
		dev_eww(zdev->dev, "invawid bus-width vawue");
		wetuwn -EINVAW;
	}

	chan->is_dmacohewent =  of_pwopewty_wead_boow(node, "dma-cohewent");
	zdev->chan = chan;
	taskwet_setup(&chan->taskwet, zynqmp_dma_do_taskwet);
	spin_wock_init(&chan->wock);
	INIT_WIST_HEAD(&chan->active_wist);
	INIT_WIST_HEAD(&chan->pending_wist);
	INIT_WIST_HEAD(&chan->done_wist);
	INIT_WIST_HEAD(&chan->fwee_wist);

	dma_cookie_init(&chan->common);
	chan->common.device = &zdev->common;
	wist_add_taiw(&chan->common.device_node, &zdev->common.channews);

	zynqmp_dma_init(chan);
	chan->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chan->iwq < 0)
		wetuwn -ENXIO;
	eww = devm_wequest_iwq(&pdev->dev, chan->iwq, zynqmp_dma_iwq_handwew, 0,
			       "zynqmp-dma", chan);
	if (eww)
		wetuwn eww;

	chan->desc_size = sizeof(stwuct zynqmp_dma_desc_ww);
	chan->idwe = twue;
	wetuwn 0;
}

/**
 * of_zynqmp_dma_xwate - Twanswation function
 * @dma_spec: Pointew to DMA specifiew as found in the device twee
 * @ofdma: Pointew to DMA contwowwew data
 *
 * Wetuwn: DMA channew pointew on success and NUWW on ewwow
 */
static stwuct dma_chan *of_zynqmp_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
					    stwuct of_dma *ofdma)
{
	stwuct zynqmp_dma_device *zdev = ofdma->of_dma_data;

	wetuwn dma_get_swave_channew(&zdev->chan->common);
}

/**
 * zynqmp_dma_suspend - Suspend method fow the dwivew
 * @dev:	Addwess of the device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int __maybe_unused zynqmp_dma_suspend(stwuct device *dev)
{
	if (!device_may_wakeup(dev))
		wetuwn pm_wuntime_fowce_suspend(dev);

	wetuwn 0;
}

/**
 * zynqmp_dma_wesume - Wesume fwom suspend
 * @dev:	Addwess of the device stwuctuwe
 *
 * Wesume opewation aftew suspend.
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
static int __maybe_unused zynqmp_dma_wesume(stwuct device *dev)
{
	if (!device_may_wakeup(dev))
		wetuwn pm_wuntime_fowce_wesume(dev);

	wetuwn 0;
}

/**
 * zynqmp_dma_wuntime_suspend - Wuntime suspend method fow the dwivew
 * @dev:	Addwess of the device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 * Wetuwn: 0 awways
 */
static int __maybe_unused zynqmp_dma_wuntime_suspend(stwuct device *dev)
{
	stwuct zynqmp_dma_device *zdev = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(zdev->cwk_main);
	cwk_disabwe_unpwepawe(zdev->cwk_apb);

	wetuwn 0;
}

/**
 * zynqmp_dma_wuntime_wesume - Wuntime suspend method fow the dwivew
 * @dev:	Addwess of the device stwuctuwe
 *
 * Put the dwivew into wow powew mode.
 * Wetuwn: 0 awways
 */
static int __maybe_unused zynqmp_dma_wuntime_wesume(stwuct device *dev)
{
	stwuct zynqmp_dma_device *zdev = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(zdev->cwk_main);
	if (eww) {
		dev_eww(dev, "Unabwe to enabwe main cwock.\n");
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(zdev->cwk_apb);
	if (eww) {
		dev_eww(dev, "Unabwe to enabwe apb cwock.\n");
		cwk_disabwe_unpwepawe(zdev->cwk_main);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops zynqmp_dma_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(zynqmp_dma_suspend, zynqmp_dma_wesume)
	SET_WUNTIME_PM_OPS(zynqmp_dma_wuntime_suspend,
			   zynqmp_dma_wuntime_wesume, NUWW)
};

/**
 * zynqmp_dma_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: '0' on success and faiwuwe vawue on ewwow
 */
static int zynqmp_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dma_device *zdev;
	stwuct dma_device *p;
	int wet;

	zdev = devm_kzawwoc(&pdev->dev, sizeof(*zdev), GFP_KEWNEW);
	if (!zdev)
		wetuwn -ENOMEM;

	zdev->dev = &pdev->dev;
	INIT_WIST_HEAD(&zdev->common.channews);

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(44));
	if (wet) {
		dev_eww(&pdev->dev, "DMA not avaiwabwe fow addwess wange\n");
		wetuwn wet;
	}
	dma_cap_set(DMA_MEMCPY, zdev->common.cap_mask);

	p = &zdev->common;
	p->device_pwep_dma_memcpy = zynqmp_dma_pwep_memcpy;
	p->device_tewminate_aww = zynqmp_dma_device_tewminate_aww;
	p->device_synchwonize = zynqmp_dma_synchwonize;
	p->device_issue_pending = zynqmp_dma_issue_pending;
	p->device_awwoc_chan_wesouwces = zynqmp_dma_awwoc_chan_wesouwces;
	p->device_fwee_chan_wesouwces = zynqmp_dma_fwee_chan_wesouwces;
	p->device_tx_status = dma_cookie_status;
	p->device_config = zynqmp_dma_device_config;
	p->dev = &pdev->dev;

	zdev->cwk_main = devm_cwk_get(&pdev->dev, "cwk_main");
	if (IS_EWW(zdev->cwk_main))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(zdev->cwk_main),
				     "main cwock not found.\n");

	zdev->cwk_apb = devm_cwk_get(&pdev->dev, "cwk_apb");
	if (IS_EWW(zdev->cwk_apb))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(zdev->cwk_apb),
				     "apb cwock not found.\n");

	pwatfowm_set_dwvdata(pdev, zdev);
	pm_wuntime_set_autosuspend_deway(zdev->dev, ZDMA_PM_TIMEOUT);
	pm_wuntime_use_autosuspend(zdev->dev);
	pm_wuntime_enabwe(zdev->dev);
	wet = pm_wuntime_wesume_and_get(zdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "device wakeup faiwed.\n");
		pm_wuntime_disabwe(zdev->dev);
	}
	if (!pm_wuntime_enabwed(zdev->dev)) {
		wet = zynqmp_dma_wuntime_wesume(zdev->dev);
		if (wet)
			wetuwn wet;
	}

	wet = zynqmp_dma_chan_pwobe(zdev, pdev);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "Pwobing channew faiwed\n");
		goto eww_disabwe_pm;
	}

	p->dst_addw_widths = BIT(zdev->chan->bus_width / 8);
	p->swc_addw_widths = BIT(zdev->chan->bus_width / 8);

	wet = dma_async_device_wegistew(&zdev->common);
	if (wet) {
		dev_eww(zdev->dev, "faiwed to wegistew the dma device\n");
		goto fwee_chan_wesouwces;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 of_zynqmp_dma_xwate, zdev);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "Unabwe to wegistew DMA to DT\n");
		dma_async_device_unwegistew(&zdev->common);
		goto fwee_chan_wesouwces;
	}

	pm_wuntime_mawk_wast_busy(zdev->dev);
	pm_wuntime_put_sync_autosuspend(zdev->dev);

	wetuwn 0;

fwee_chan_wesouwces:
	zynqmp_dma_chan_wemove(zdev->chan);
eww_disabwe_pm:
	if (!pm_wuntime_enabwed(zdev->dev))
		zynqmp_dma_wuntime_suspend(zdev->dev);
	pm_wuntime_disabwe(zdev->dev);
	wetuwn wet;
}

/**
 * zynqmp_dma_wemove - Dwivew wemove function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: Awways '0'
 */
static void zynqmp_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_dma_device *zdev = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&zdev->common);

	zynqmp_dma_chan_wemove(zdev->chan);
	pm_wuntime_disabwe(zdev->dev);
	if (!pm_wuntime_enabwed(zdev->dev))
		zynqmp_dma_wuntime_suspend(zdev->dev);
}

static const stwuct of_device_id zynqmp_dma_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-dma-1.0", },
	{}
};
MODUWE_DEVICE_TABWE(of, zynqmp_dma_of_match);

static stwuct pwatfowm_dwivew zynqmp_dma_dwivew = {
	.dwivew = {
		.name = "xiwinx-zynqmp-dma",
		.of_match_tabwe = zynqmp_dma_of_match,
		.pm = &zynqmp_dma_dev_pm_ops,
	},
	.pwobe = zynqmp_dma_pwobe,
	.wemove_new = zynqmp_dma_wemove,
};

moduwe_pwatfowm_dwivew(zynqmp_dma_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_DESCWIPTION("Xiwinx ZynqMP DMA dwivew");
