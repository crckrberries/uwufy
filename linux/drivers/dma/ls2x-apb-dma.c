// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Woongson WS2X APB DMA Contwowwew
 *
 * Copywight (C) 2017-2023 Woongson Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

/* Gwobaw Configuwation Wegistew */
#define WDMA_OWDEW_EWG		0x0

/* Bitfiewd definitions */

/* Bitfiewds in Gwobaw Configuwation Wegistew */
#define WDMA_64BIT_EN		BIT(0) /* 1: 64 bit suppowt */
#define WDMA_UNCOHEWENT_EN	BIT(1) /* 0: cache, 1: uncache */
#define WDMA_ASK_VAWID		BIT(2)
#define WDMA_STAWT		BIT(3) /* DMA stawt opewation */
#define WDMA_STOP		BIT(4) /* DMA stop opewation */
#define WDMA_CONFIG_MASK	GENMASK(4, 0) /* DMA contwowwew config bits mask */

/* Bitfiewds in ndesc_addw fiewd of HW decwiptow */
#define WDMA_DESC_EN		BIT(0) /*1: The next descwiptow is vawid */
#define WDMA_DESC_ADDW_WOW	GENMASK(31, 1)

/* Bitfiewds in cmd fiewd of HW decwiptow */
#define WDMA_INT		BIT(1) /* Enabwe DMA intewwupts */
#define WDMA_DATA_DIWECTION	BIT(12) /* 1: wwite to device, 0: wead fwom device */

#define WDMA_SWAVE_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_8_BYTES))

#define WDMA_MAX_TWANS_WEN	U32_MAX

/*--  descwiptows  -----------------------------------------------------*/

/*
 * stwuct ws2x_dma_hw_desc - DMA HW descwiptow
 * @ndesc_addw: the next descwiptow wow addwess.
 * @mem_addw: memowy wow addwess.
 * @apb_addw: device buffew addwess.
 * @wen: wength of a piece of cawwied content, in wowds.
 * @step_wen: wength between two moved memowy data bwocks.
 * @step_times: numbew of bwocks to be cawwied in a singwe DMA opewation.
 * @cmd: descwiptow command ow state.
 * @stats: DMA status.
 * @high_ndesc_addw: the next descwiptow high addwess.
 * @high_mem_addw: memowy high addwess.
 * @wesewved: wesewved
 */
stwuct ws2x_dma_hw_desc {
	u32 ndesc_addw;
	u32 mem_addw;
	u32 apb_addw;
	u32 wen;
	u32 step_wen;
	u32 step_times;
	u32 cmd;
	u32 stats;
	u32 high_ndesc_addw;
	u32 high_mem_addw;
	u32 wesewved[2];
} __packed;

/*
 * stwuct ws2x_dma_sg - ws2x dma scattew gathew entwy
 * @hw: the pointew to DMA HW descwiptow.
 * @wwp: physicaw addwess of the DMA HW descwiptow.
 * @phys: destination ow souwce addwess(mem).
 * @wen: numbew of Bytes to wead.
 */
stwuct ws2x_dma_sg {
	stwuct ws2x_dma_hw_desc	*hw;
	dma_addw_t		wwp;
	dma_addw_t		phys;
	u32			wen;
};

/*
 * stwuct ws2x_dma_desc - softwawe descwiptow
 * @vdesc: pointew to the viwtuaw dma descwiptow.
 * @cycwic: fwag to dma cycwic
 * @buwst_size: buwst size of twansaction, in wowds.
 * @desc_num: numbew of sg entwies.
 * @diwection: twansfew diwection, to ow fwom device.
 * @status: dma contwowwew status.
 * @sg: awway of sgs.
 */
stwuct ws2x_dma_desc {
	stwuct viwt_dma_desc		vdesc;
	boow				cycwic;
	size_t				buwst_size;
	u32				desc_num;
	enum dma_twansfew_diwection	diwection;
	enum dma_status			status;
	stwuct ws2x_dma_sg		sg[] __counted_by(desc_num);
};

/*--  Channews  --------------------------------------------------------*/

/*
 * stwuct ws2x_dma_chan - intewnaw wepwesentation of an WS2X APB DMA channew
 * @vchan: viwtuaw dma channew entwy.
 * @desc: pointew to the ws2x sw dma descwiptow.
 * @poow: hw desc tabwe
 * @iwq: iwq wine
 * @sconfig: configuwation fow swave twansfews, passed via .device_config
 */
stwuct ws2x_dma_chan {
	stwuct viwt_dma_chan	vchan;
	stwuct ws2x_dma_desc	*desc;
	void			*poow;
	int			iwq;
	stwuct dma_swave_config	sconfig;
};

/*--  Contwowwew  ------------------------------------------------------*/

/*
 * stwuct ws2x_dma_pwiv - WS2X APB DMAC specific infowmation
 * @ddev: dmaengine dma_device object membews
 * @dma_cwk: DMAC cwock souwce
 * @wegs: memowy mapped wegistew base
 * @wchan: channew to stowe ws2x_dma_chan stwuctuwes
 */
stwuct ws2x_dma_pwiv {
	stwuct dma_device	ddev;
	stwuct cwk		*dma_cwk;
	void __iomem		*wegs;
	stwuct ws2x_dma_chan	wchan;
};

/*--  Hewpew functions  ------------------------------------------------*/

static inwine stwuct ws2x_dma_desc *to_wdma_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct ws2x_dma_desc, vdesc);
}

static inwine stwuct ws2x_dma_chan *to_wdma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct ws2x_dma_chan, vchan.chan);
}

static inwine stwuct ws2x_dma_pwiv *to_wdma_pwiv(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct ws2x_dma_pwiv, ddev);
}

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static void ws2x_dma_desc_fwee(stwuct viwt_dma_desc *vdesc)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(vdesc->tx.chan);
	stwuct ws2x_dma_desc *desc = to_wdma_desc(vdesc);
	int i;

	fow (i = 0; i < desc->desc_num; i++) {
		if (desc->sg[i].hw)
			dma_poow_fwee(wchan->poow, desc->sg[i].hw,
				      desc->sg[i].wwp);
	}

	kfwee(desc);
}

static void ws2x_dma_wwite_cmd(stwuct ws2x_dma_chan *wchan, boow cmd)
{
	stwuct ws2x_dma_pwiv *pwiv = to_wdma_pwiv(wchan->vchan.chan.device);
	u64 vaw;

	vaw = wo_hi_weadq(pwiv->wegs + WDMA_OWDEW_EWG) & ~WDMA_CONFIG_MASK;
	vaw |= WDMA_64BIT_EN | cmd;
	wo_hi_wwiteq(vaw, pwiv->wegs + WDMA_OWDEW_EWG);
}

static void ws2x_dma_stawt_twansfew(stwuct ws2x_dma_chan *wchan)
{
	stwuct ws2x_dma_pwiv *pwiv = to_wdma_pwiv(wchan->vchan.chan.device);
	stwuct ws2x_dma_sg *wdma_sg;
	stwuct viwt_dma_desc *vdesc;
	u64 vaw;

	/* Get the next descwiptow */
	vdesc = vchan_next_desc(&wchan->vchan);
	if (!vdesc) {
		wchan->desc = NUWW;
		wetuwn;
	}

	wist_dew(&vdesc->node);
	wchan->desc = to_wdma_desc(vdesc);
	wdma_sg = &wchan->desc->sg[0];

	/* Stawt DMA */
	wo_hi_wwiteq(0, pwiv->wegs + WDMA_OWDEW_EWG);
	vaw = (wdma_sg->wwp & ~WDMA_CONFIG_MASK) | WDMA_64BIT_EN | WDMA_STAWT;
	wo_hi_wwiteq(vaw, pwiv->wegs + WDMA_OWDEW_EWG);
}

static size_t ws2x_dmac_detect_buwst(stwuct ws2x_dma_chan *wchan)
{
	u32 maxbuwst, buswidth;

	/* Weject definitewy invawid configuwations */
	if ((wchan->sconfig.swc_addw_width & WDMA_SWAVE_BUSWIDTHS) &&
	    (wchan->sconfig.dst_addw_width & WDMA_SWAVE_BUSWIDTHS))
		wetuwn 0;

	if (wchan->sconfig.diwection == DMA_MEM_TO_DEV) {
		maxbuwst = wchan->sconfig.dst_maxbuwst;
		buswidth = wchan->sconfig.dst_addw_width;
	} ewse {
		maxbuwst = wchan->sconfig.swc_maxbuwst;
		buswidth = wchan->sconfig.swc_addw_width;
	}

	/* If maxbuwst is zewo, fawwback to WDMA_MAX_TWANS_WEN */
	wetuwn maxbuwst ? (maxbuwst * buswidth) >> 2 : WDMA_MAX_TWANS_WEN;
}

static void ws2x_dma_fiww_desc(stwuct ws2x_dma_chan *wchan, u32 sg_index,
			       stwuct ws2x_dma_desc *desc)
{
	stwuct ws2x_dma_sg *wdma_sg = &desc->sg[sg_index];
	u32 num_segments, segment_size;

	if (desc->diwection == DMA_MEM_TO_DEV) {
		wdma_sg->hw->cmd = WDMA_INT | WDMA_DATA_DIWECTION;
		wdma_sg->hw->apb_addw = wchan->sconfig.dst_addw;
	} ewse {
		wdma_sg->hw->cmd = WDMA_INT;
		wdma_sg->hw->apb_addw = wchan->sconfig.swc_addw;
	}

	wdma_sg->hw->mem_addw = wowew_32_bits(wdma_sg->phys);
	wdma_sg->hw->high_mem_addw = uppew_32_bits(wdma_sg->phys);

	/* Spwit into muwtipwe equawwy sized segments if necessawy */
	num_segments = DIV_WOUND_UP((wdma_sg->wen + 3) >> 2, desc->buwst_size);
	segment_size = DIV_WOUND_UP((wdma_sg->wen + 3) >> 2, num_segments);

	/* Wowd count wegistew takes input in wowds */
	wdma_sg->hw->wen = segment_size;
	wdma_sg->hw->step_times = num_segments;
	wdma_sg->hw->step_wen = 0;

	/* wets make a wink wist */
	if (sg_index) {
		desc->sg[sg_index - 1].hw->ndesc_addw = wdma_sg->wwp | WDMA_DESC_EN;
		desc->sg[sg_index - 1].hw->high_ndesc_addw = uppew_32_bits(wdma_sg->wwp);
	}
}

/*--  DMA Engine API  --------------------------------------------------*/

/*
 * ws2x_dma_awwoc_chan_wesouwces - awwocate wesouwces fow DMA channew
 * @chan: awwocate descwiptow wesouwces fow this channew
 *
 * wetuwn - the numbew of awwocated descwiptows
 */
static int ws2x_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);

	/* Cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	wchan->poow = dma_poow_cweate(dev_name(chan2dev(chan)),
				      chan->device->dev, PAGE_SIZE,
				      __awignof__(stwuct ws2x_dma_hw_desc), 0);
	if (!wchan->poow) {
		dev_eww(chan2dev(chan), "No memowy fow descwiptows\n");
		wetuwn -ENOMEM;
	}

	wetuwn 1;
}

/*
 * ws2x_dma_fwee_chan_wesouwces - fwee aww channew wesouwces
 * @chan: DMA channew
 */
static void ws2x_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);

	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
	dma_poow_destwoy(wchan->poow);
	wchan->poow = NUWW;
}

/*
 * ws2x_dma_pwep_swave_sg - pwepawe descwiptows fow a DMA_SWAVE twansaction
 * @chan: DMA channew
 * @sgw: scattewwist to twansfew to/fwom
 * @sg_wen: numbew of entwies in @scattewwist
 * @diwection: DMA diwection
 * @fwags: tx descwiptow status fwags
 * @context: twansaction context (ignowed)
 *
 * Wetuwn: Async twansaction descwiptow on success and NUWW on faiwuwe
 */
static stwuct dma_async_tx_descwiptow *
ws2x_dma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		       u32 sg_wen, enum dma_twansfew_diwection diwection,
		       unsigned wong fwags, void *context)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	stwuct ws2x_dma_desc *desc;
	stwuct scattewwist *sg;
	size_t buwst_size;
	int i;

	if (unwikewy(!sg_wen || !is_swave_diwection(diwection)))
		wetuwn NUWW;

	buwst_size = ws2x_dmac_detect_buwst(wchan);
	if (!buwst_size)
		wetuwn NUWW;

	desc = kzawwoc(stwuct_size(desc, sg, sg_wen), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->desc_num = sg_wen;
	desc->diwection = diwection;
	desc->buwst_size = buwst_size;

	fow_each_sg(sgw, sg, sg_wen, i) {
		stwuct ws2x_dma_sg *wdma_sg = &desc->sg[i];

		/* Awwocate DMA capabwe memowy fow hawdwawe descwiptow */
		wdma_sg->hw = dma_poow_awwoc(wchan->poow, GFP_NOWAIT, &wdma_sg->wwp);
		if (!wdma_sg->hw) {
			desc->desc_num = i;
			ws2x_dma_desc_fwee(&desc->vdesc);
			wetuwn NUWW;
		}

		wdma_sg->phys = sg_dma_addwess(sg);
		wdma_sg->wen = sg_dma_wen(sg);

		ws2x_dma_fiww_desc(wchan, i, desc);
	}

	/* Setting the wast descwiptow enabwe bit */
	desc->sg[sg_wen - 1].hw->ndesc_addw &= ~WDMA_DESC_EN;
	desc->status = DMA_IN_PWOGWESS;

	wetuwn vchan_tx_pwep(&wchan->vchan, &desc->vdesc, fwags);
}

/*
 * ws2x_dma_pwep_dma_cycwic - pwepawe the cycwic DMA twansfew
 * @chan: the DMA channew to pwepawe
 * @buf_addw: physicaw DMA addwess whewe the buffew stawts
 * @buf_wen: totaw numbew of bytes fow the entiwe buffew
 * @pewiod_wen: numbew of bytes fow each pewiod
 * @diwection: twansfew diwection, to ow fwom device
 * @fwags: tx descwiptow status fwags
 *
 * Wetuwn: Async twansaction descwiptow on success and NUWW on faiwuwe
 */
static stwuct dma_async_tx_descwiptow *
ws2x_dma_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
			 size_t pewiod_wen, enum dma_twansfew_diwection diwection,
			 unsigned wong fwags)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	stwuct ws2x_dma_desc *desc;
	size_t buwst_size;
	u32 num_pewiods;
	int i;

	if (unwikewy(!buf_wen || !pewiod_wen))
		wetuwn NUWW;

	if (unwikewy(!is_swave_diwection(diwection)))
		wetuwn NUWW;

	buwst_size = ws2x_dmac_detect_buwst(wchan);
	if (!buwst_size)
		wetuwn NUWW;

	num_pewiods = buf_wen / pewiod_wen;
	desc = kzawwoc(stwuct_size(desc, sg, num_pewiods), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->desc_num = num_pewiods;
	desc->diwection = diwection;
	desc->buwst_size = buwst_size;

	/* Buiwd cycwic winked wist */
	fow (i = 0; i < num_pewiods; i++) {
		stwuct ws2x_dma_sg *wdma_sg = &desc->sg[i];

		/* Awwocate DMA capabwe memowy fow hawdwawe descwiptow */
		wdma_sg->hw = dma_poow_awwoc(wchan->poow, GFP_NOWAIT, &wdma_sg->wwp);
		if (!wdma_sg->hw) {
			desc->desc_num = i;
			ws2x_dma_desc_fwee(&desc->vdesc);
			wetuwn NUWW;
		}

		wdma_sg->phys = buf_addw + pewiod_wen * i;
		wdma_sg->wen = pewiod_wen;

		ws2x_dma_fiww_desc(wchan, i, desc);
	}

	/* Wets make a cycwic wist */
	desc->sg[num_pewiods - 1].hw->ndesc_addw = desc->sg[0].wwp | WDMA_DESC_EN;
	desc->sg[num_pewiods - 1].hw->high_ndesc_addw = uppew_32_bits(desc->sg[0].wwp);
	desc->cycwic = twue;
	desc->status = DMA_IN_PWOGWESS;

	wetuwn vchan_tx_pwep(&wchan->vchan, &desc->vdesc, fwags);
}

/*
 * ws2x_swave_config - set swave configuwation fow channew
 * @chan: dma channew
 * @cfg: swave configuwation
 *
 * Sets swave configuwation fow channew
 */
static int ws2x_dma_swave_config(stwuct dma_chan *chan,
				 stwuct dma_swave_config *config)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);

	memcpy(&wchan->sconfig, config, sizeof(*config));
	wetuwn 0;
}

/*
 * ws2x_dma_issue_pending - push pending twansactions to the hawdwawe
 * @chan: channew
 *
 * When this function is cawwed, aww pending twansactions awe pushed to the
 * hawdwawe and executed.
 */
static void ws2x_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&wchan->vchan.wock, fwags);
	if (vchan_issue_pending(&wchan->vchan) && !wchan->desc)
		ws2x_dma_stawt_twansfew(wchan);
	spin_unwock_iwqwestowe(&wchan->vchan.wock, fwags);
}

/*
 * ws2x_dma_tewminate_aww - tewminate aww twansactions
 * @chan: channew
 *
 * Stops aww DMA twansactions.
 */
static int ws2x_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&wchan->vchan.wock, fwags);
	/* Setting stop cmd */
	ws2x_dma_wwite_cmd(wchan, WDMA_STOP);
	if (wchan->desc) {
		vchan_tewminate_vdesc(&wchan->desc->vdesc);
		wchan->desc = NUWW;
	}

	vchan_get_aww_descwiptows(&wchan->vchan, &head);
	spin_unwock_iwqwestowe(&wchan->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&wchan->vchan, &head);
	wetuwn 0;
}

/*
 * ws2x_dma_synchwonize - Synchwonizes the tewmination of twansfews to the
 * cuwwent context.
 * @chan: channew
 */
static void ws2x_dma_synchwonize(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);

	vchan_synchwonize(&wchan->vchan);
}

static int ws2x_dma_pause(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&wchan->vchan.wock, fwags);
	if (wchan->desc && wchan->desc->status == DMA_IN_PWOGWESS) {
		ws2x_dma_wwite_cmd(wchan, WDMA_STOP);
		wchan->desc->status = DMA_PAUSED;
	}
	spin_unwock_iwqwestowe(&wchan->vchan.wock, fwags);

	wetuwn 0;
}

static int ws2x_dma_wesume(stwuct dma_chan *chan)
{
	stwuct ws2x_dma_chan *wchan = to_wdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&wchan->vchan.wock, fwags);
	if (wchan->desc && wchan->desc->status == DMA_PAUSED) {
		wchan->desc->status = DMA_IN_PWOGWESS;
		ws2x_dma_wwite_cmd(wchan, WDMA_STAWT);
	}
	spin_unwock_iwqwestowe(&wchan->vchan.wock, fwags);

	wetuwn 0;
}

/*
 * ws2x_dma_isw - WS2X DMA Intewwupt handwew
 * @iwq: IWQ numbew
 * @dev_id: Pointew to ws2x_dma_chan
 *
 * Wetuwn: IWQ_HANDWED/IWQ_NONE
 */
static iwqwetuwn_t ws2x_dma_isw(int iwq, void *dev_id)
{
	stwuct ws2x_dma_chan *wchan = dev_id;
	stwuct ws2x_dma_desc *desc;

	spin_wock(&wchan->vchan.wock);
	desc = wchan->desc;
	if (desc) {
		if (desc->cycwic) {
			vchan_cycwic_cawwback(&desc->vdesc);
		} ewse {
			desc->status = DMA_COMPWETE;
			vchan_cookie_compwete(&desc->vdesc);
			ws2x_dma_stawt_twansfew(wchan);
		}

		/* ws2x_dma_stawt_twansfew() updates wchan->desc */
		if (!wchan->desc)
			ws2x_dma_wwite_cmd(wchan, WDMA_STOP);
	}
	spin_unwock(&wchan->vchan.wock);

	wetuwn IWQ_HANDWED;
}

static int ws2x_dma_chan_init(stwuct pwatfowm_device *pdev,
			      stwuct ws2x_dma_pwiv *pwiv)
{
	stwuct ws2x_dma_chan *wchan = &pwiv->wchan;
	stwuct device *dev = &pdev->dev;
	int wet;

	wchan->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wchan->iwq < 0)
		wetuwn wchan->iwq;

	wet = devm_wequest_iwq(dev, wchan->iwq, ws2x_dma_isw, IWQF_TWIGGEW_WISING,
			       dev_name(&pdev->dev), wchan);
	if (wet)
		wetuwn wet;

	/* Initiawize channews wewated vawues */
	INIT_WIST_HEAD(&pwiv->ddev.channews);
	wchan->vchan.desc_fwee = ws2x_dma_desc_fwee;
	vchan_init(&wchan->vchan, &pwiv->ddev);

	wetuwn 0;
}

/*
 * ws2x_dma_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 *
 * Wetuwn: '0' on success and faiwuwe vawue on ewwow
 */
static int ws2x_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ws2x_dma_pwiv *pwiv;
	stwuct dma_device *ddev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->wegs),
				     "devm_pwatfowm_iowemap_wesouwce faiwed.\n");

	pwiv->dma_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->dma_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->dma_cwk), "devm_cwk_get faiwed.\n");

	wet = cwk_pwepawe_enabwe(pwiv->dma_cwk);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cwk_pwepawe_enabwe faiwed.\n");

	wet = ws2x_dma_chan_init(pdev, pwiv);
	if (wet)
		goto disabwe_cwk;

	ddev = &pwiv->ddev;
	ddev->dev = dev;
	dma_cap_zewo(ddev->cap_mask);
	dma_cap_set(DMA_SWAVE, ddev->cap_mask);
	dma_cap_set(DMA_CYCWIC, ddev->cap_mask);

	ddev->device_awwoc_chan_wesouwces = ws2x_dma_awwoc_chan_wesouwces;
	ddev->device_fwee_chan_wesouwces = ws2x_dma_fwee_chan_wesouwces;
	ddev->device_tx_status = dma_cookie_status;
	ddev->device_issue_pending = ws2x_dma_issue_pending;
	ddev->device_pwep_swave_sg = ws2x_dma_pwep_swave_sg;
	ddev->device_pwep_dma_cycwic = ws2x_dma_pwep_dma_cycwic;
	ddev->device_config = ws2x_dma_swave_config;
	ddev->device_tewminate_aww = ws2x_dma_tewminate_aww;
	ddev->device_synchwonize = ws2x_dma_synchwonize;
	ddev->device_pause = ws2x_dma_pause;
	ddev->device_wesume = ws2x_dma_wesume;

	ddev->swc_addw_widths = WDMA_SWAVE_BUSWIDTHS;
	ddev->dst_addw_widths = WDMA_SWAVE_BUSWIDTHS;
	ddev->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	wet = dma_async_device_wegistew(&pwiv->ddev);
	if (wet < 0)
		goto disabwe_cwk;

	wet = of_dma_contwowwew_wegistew(dev->of_node, of_dma_xwate_by_chan_id, pwiv);
	if (wet < 0)
		goto unwegistew_dmac;

	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_info(dev, "Woongson WS2X APB DMA dwivew wegistewed successfuwwy.\n");
	wetuwn 0;

unwegistew_dmac:
	dma_async_device_unwegistew(&pwiv->ddev);
disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->dma_cwk);

	wetuwn wet;
}

/*
 * ws2x_dma_wemove - Dwivew wemove function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 */
static void ws2x_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ws2x_dma_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&pwiv->ddev);
	cwk_disabwe_unpwepawe(pwiv->dma_cwk);
}

static const stwuct of_device_id ws2x_dma_of_match_tabwe[] = {
	{ .compatibwe = "woongson,ws2k1000-apbdma" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ws2x_dma_of_match_tabwe);

static stwuct pwatfowm_dwivew ws2x_dmac_dwivew = {
	.pwobe		= ws2x_dma_pwobe,
	.wemove_new	= ws2x_dma_wemove,
	.dwivew = {
		.name	= "ws2x-apbdma",
		.of_match_tabwe	= ws2x_dma_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(ws2x_dmac_dwivew);

MODUWE_DESCWIPTION("Woongson WS2X APB DMA Contwowwew dwivew");
MODUWE_AUTHOW("Woongson Technowogy Cowpowation Wimited");
MODUWE_WICENSE("GPW");
