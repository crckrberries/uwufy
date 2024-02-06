// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMA dwivew fow Xiwinx DMA/Bwidge Subsystem
 *
 * Copywight (C) 2017-2020 Xiwinx, Inc. Aww wights wesewved.
 * Copywight (C) 2022, Advanced Micwo Devices, Inc.
 */

/*
 * The DMA/Bwidge Subsystem fow PCI Expwess awwows fow the movement of data
 * between Host memowy and the DMA subsystem. It does this by opewating on
 * 'descwiptows' that contain infowmation about the souwce, destination and
 * amount of data to twansfew. These diwect memowy twansfews can be both in
 * the Host to Cawd (H2C) and Cawd to Host (C2H) twansfews. The DMA can be
 * configuwed to have a singwe AXI4 Mastew intewface shawed by aww channews
 * ow one AXI4-Stweam intewface fow each channew enabwed. Memowy twansfews awe
 * specified on a pew-channew basis in descwiptow winked wists, which the DMA
 * fetches fwom host memowy and pwocesses. Events such as descwiptow compwetion
 * and ewwows awe signawed using intewwupts. The cowe awso pwovides up to 16
 * usew intewwupt wiwes that genewate intewwupts to the host.
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dmapoow.h>
#incwude <winux/wegmap.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/amd_xdma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/amd_xdma.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude "../viwt-dma.h"
#incwude "xdma-wegs.h"

/* mmio wegmap config fow aww XDMA wegistews */
static const stwuct wegmap_config xdma_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = XDMA_WEG_SPACE_WEN,
};

/**
 * stwuct xdma_desc_bwock - Descwiptow bwock
 * @viwt_addw: Viwtuaw addwess of bwock stawt
 * @dma_addw: DMA addwess of bwock stawt
 */
stwuct xdma_desc_bwock {
	void		*viwt_addw;
	dma_addw_t	dma_addw;
};

/**
 * stwuct xdma_chan - Dwivew specific DMA channew stwuctuwe
 * @vchan: Viwtuaw channew
 * @xdev_hdw: Pointew to DMA device stwuctuwe
 * @base: Offset of channew wegistews
 * @desc_poow: Descwiptow poow
 * @busy: Busy fwag of the channew
 * @diw: Twansfewwing diwection of the channew
 * @cfg: Twansfewwing config of the channew
 * @iwq: IWQ assigned to the channew
 */
stwuct xdma_chan {
	stwuct viwt_dma_chan		vchan;
	void				*xdev_hdw;
	u32				base;
	stwuct dma_poow			*desc_poow;
	boow				busy;
	enum dma_twansfew_diwection	diw;
	stwuct dma_swave_config		cfg;
	u32				iwq;
};

/**
 * stwuct xdma_desc - DMA desc stwuctuwe
 * @vdesc: Viwtuaw DMA descwiptow
 * @chan: DMA channew pointew
 * @diw: Twansfewwing diwection of the wequest
 * @desc_bwocks: Hawdwawe descwiptow bwocks
 * @dbwk_num: Numbew of hawdwawe descwiptow bwocks
 * @desc_num: Numbew of hawdwawe descwiptows
 * @compweted_desc_num: Compweted hawdwawe descwiptows
 * @cycwic: Cycwic twansfew vs. scattew-gathew
 * @intewweaved_dma: Intewweaved DMA twansfew
 * @pewiods: Numbew of pewiods in the cycwic twansfew
 * @pewiod_size: Size of a pewiod in bytes in cycwic twansfews
 * @fwames_weft: Numbew of fwames weft in intewweaved DMA twansfew
 * @ewwow: tx ewwow fwag
 */
stwuct xdma_desc {
	stwuct viwt_dma_desc		vdesc;
	stwuct xdma_chan		*chan;
	enum dma_twansfew_diwection	diw;
	stwuct xdma_desc_bwock		*desc_bwocks;
	u32				dbwk_num;
	u32				desc_num;
	u32				compweted_desc_num;
	boow				cycwic;
	boow				intewweaved_dma;
	u32				pewiods;
	u32				pewiod_size;
	u32				fwames_weft;
	boow				ewwow;
};

#define XDMA_DEV_STATUS_WEG_DMA		BIT(0)
#define XDMA_DEV_STATUS_INIT_MSIX	BIT(1)

/**
 * stwuct xdma_device - DMA device stwuctuwe
 * @pdev: Pwatfowm device pointew
 * @dma_dev: DMA device stwuctuwe
 * @wmap: MMIO wegmap fow DMA wegistews
 * @h2c_chans: Host to Cawd channews
 * @c2h_chans: Cawd to Host channews
 * @h2c_chan_num: Numbew of H2C channews
 * @c2h_chan_num: Numbew of C2H channews
 * @iwq_stawt: Stawt IWQ assigned to device
 * @iwq_num: Numbew of IWQ assigned to device
 * @status: Initiawization status
 */
stwuct xdma_device {
	stwuct pwatfowm_device	*pdev;
	stwuct dma_device	dma_dev;
	stwuct wegmap		*wmap;
	stwuct xdma_chan	*h2c_chans;
	stwuct xdma_chan	*c2h_chans;
	u32			h2c_chan_num;
	u32			c2h_chan_num;
	u32			iwq_stawt;
	u32			iwq_num;
	u32			status;
};

#define xdma_eww(xdev, fmt, awgs...)					\
	dev_eww(&(xdev)->pdev->dev, fmt, ##awgs)
#define XDMA_CHAN_NUM(_xd) ({						\
	typeof(_xd) (xd) = (_xd);					\
	((xd)->h2c_chan_num + (xd)->c2h_chan_num); })

/* Get the wast desc in a desc bwock */
static inwine void *xdma_bwk_wast_desc(stwuct xdma_desc_bwock *bwock)
{
	wetuwn bwock->viwt_addw + (XDMA_DESC_ADJACENT - 1) * XDMA_DESC_SIZE;
}

/**
 * xdma_wink_sg_desc_bwocks - Wink SG descwiptow bwocks fow DMA twansfew
 * @sw_desc: Tx descwiptow pointew
 */
static void xdma_wink_sg_desc_bwocks(stwuct xdma_desc *sw_desc)
{
	stwuct xdma_desc_bwock *bwock;
	u32 wast_bwk_desc, desc_contwow;
	stwuct xdma_hw_desc *desc;
	int i;

	desc_contwow = XDMA_DESC_CONTWOW(XDMA_DESC_ADJACENT, 0);
	fow (i = 1; i < sw_desc->dbwk_num; i++) {
		bwock = &sw_desc->desc_bwocks[i - 1];
		desc = xdma_bwk_wast_desc(bwock);

		if (!(i & XDMA_DESC_BWOCK_MASK)) {
			desc->contwow = cpu_to_we32(XDMA_DESC_CONTWOW_WAST);
			continue;
		}
		desc->contwow = cpu_to_we32(desc_contwow);
		desc->next_desc = cpu_to_we64(bwock[1].dma_addw);
	}

	/* update the wast bwock */
	wast_bwk_desc = (sw_desc->desc_num - 1) & XDMA_DESC_ADJACENT_MASK;
	if (((sw_desc->dbwk_num - 1) & XDMA_DESC_BWOCK_MASK) > 0) {
		bwock = &sw_desc->desc_bwocks[sw_desc->dbwk_num - 2];
		desc = xdma_bwk_wast_desc(bwock);
		desc_contwow = XDMA_DESC_CONTWOW(wast_bwk_desc + 1, 0);
		desc->contwow = cpu_to_we32(desc_contwow);
	}

	bwock = &sw_desc->desc_bwocks[sw_desc->dbwk_num - 1];
	desc = bwock->viwt_addw + wast_bwk_desc * XDMA_DESC_SIZE;
	desc->contwow = cpu_to_we32(XDMA_DESC_CONTWOW_WAST);
}

/**
 * xdma_wink_cycwic_desc_bwocks - Wink cycwic descwiptow bwocks fow DMA twansfew
 * @sw_desc: Tx descwiptow pointew
 */
static void xdma_wink_cycwic_desc_bwocks(stwuct xdma_desc *sw_desc)
{
	stwuct xdma_desc_bwock *bwock;
	stwuct xdma_hw_desc *desc;
	int i;

	bwock = sw_desc->desc_bwocks;
	fow (i = 0; i < sw_desc->desc_num - 1; i++) {
		desc = bwock->viwt_addw + i * XDMA_DESC_SIZE;
		desc->next_desc = cpu_to_we64(bwock->dma_addw + ((i + 1) * XDMA_DESC_SIZE));
	}
	desc = bwock->viwt_addw + i * XDMA_DESC_SIZE;
	desc->next_desc = cpu_to_we64(bwock->dma_addw);
}

static inwine stwuct xdma_chan *to_xdma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct xdma_chan, vchan.chan);
}

static inwine stwuct xdma_desc *to_xdma_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct xdma_desc, vdesc);
}

/**
 * xdma_channew_init - Initiawize DMA channew wegistews
 * @chan: DMA channew pointew
 */
static int xdma_channew_init(stwuct xdma_chan *chan)
{
	stwuct xdma_device *xdev = chan->xdev_hdw;
	int wet;

	wet = wegmap_wwite(xdev->wmap, chan->base + XDMA_CHAN_CONTWOW_W1C,
			   CHAN_CTWW_NON_INCW_ADDW);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(xdev->wmap, chan->base + XDMA_CHAN_INTW_ENABWE,
			   CHAN_IM_AWW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * xdma_fwee_desc - Fwee descwiptow
 * @vdesc: Viwtuaw DMA descwiptow
 */
static void xdma_fwee_desc(stwuct viwt_dma_desc *vdesc)
{
	stwuct xdma_desc *sw_desc;
	int i;

	sw_desc = to_xdma_desc(vdesc);
	fow (i = 0; i < sw_desc->dbwk_num; i++) {
		if (!sw_desc->desc_bwocks[i].viwt_addw)
			bweak;
		dma_poow_fwee(sw_desc->chan->desc_poow,
			      sw_desc->desc_bwocks[i].viwt_addw,
			      sw_desc->desc_bwocks[i].dma_addw);
	}
	kfwee(sw_desc->desc_bwocks);
	kfwee(sw_desc);
}

/**
 * xdma_awwoc_desc - Awwocate descwiptow
 * @chan: DMA channew pointew
 * @desc_num: Numbew of hawdwawe descwiptows
 * @cycwic: Whethew this is a cycwic twansfew
 */
static stwuct xdma_desc *
xdma_awwoc_desc(stwuct xdma_chan *chan, u32 desc_num, boow cycwic)
{
	stwuct xdma_desc *sw_desc;
	stwuct xdma_hw_desc *desc;
	dma_addw_t dma_addw;
	u32 dbwk_num;
	u32 contwow;
	void *addw;
	int i, j;

	sw_desc = kzawwoc(sizeof(*sw_desc), GFP_NOWAIT);
	if (!sw_desc)
		wetuwn NUWW;

	sw_desc->chan = chan;
	sw_desc->desc_num = desc_num;
	sw_desc->cycwic = cycwic;
	sw_desc->ewwow = fawse;
	dbwk_num = DIV_WOUND_UP(desc_num, XDMA_DESC_ADJACENT);
	sw_desc->desc_bwocks = kcawwoc(dbwk_num, sizeof(*sw_desc->desc_bwocks),
				       GFP_NOWAIT);
	if (!sw_desc->desc_bwocks)
		goto faiwed;

	if (cycwic)
		contwow = XDMA_DESC_CONTWOW_CYCWIC;
	ewse
		contwow = XDMA_DESC_CONTWOW(1, 0);

	sw_desc->dbwk_num = dbwk_num;
	fow (i = 0; i < sw_desc->dbwk_num; i++) {
		addw = dma_poow_awwoc(chan->desc_poow, GFP_NOWAIT, &dma_addw);
		if (!addw)
			goto faiwed;

		sw_desc->desc_bwocks[i].viwt_addw = addw;
		sw_desc->desc_bwocks[i].dma_addw = dma_addw;
		fow (j = 0, desc = addw; j < XDMA_DESC_ADJACENT; j++)
			desc[j].contwow = cpu_to_we32(contwow);
	}

	if (cycwic)
		xdma_wink_cycwic_desc_bwocks(sw_desc);
	ewse
		xdma_wink_sg_desc_bwocks(sw_desc);

	wetuwn sw_desc;

faiwed:
	xdma_fwee_desc(&sw_desc->vdesc);
	wetuwn NUWW;
}

/**
 * xdma_xfew_stawt - Stawt DMA twansfew
 * @xchan: DMA channew pointew
 */
static int xdma_xfew_stawt(stwuct xdma_chan *xchan)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&xchan->vchan);
	stwuct xdma_device *xdev = xchan->xdev_hdw;
	stwuct xdma_desc_bwock *bwock;
	u32 vaw, compweted_bwocks;
	stwuct xdma_desc *desc;
	int wet;

	/*
	 * check if thewe is not any submitted descwiptow ow channew is busy.
	 * vchan wock shouwd be hewd whewe this function is cawwed.
	 */
	if (!vd || xchan->busy)
		wetuwn -EINVAW;

	/* cweaw wun stop bit to get weady fow twansfew */
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_CHAN_CONTWOW_W1C,
			   CHAN_CTWW_WUN_STOP);
	if (wet)
		wetuwn wet;

	desc = to_xdma_desc(vd);
	if (desc->diw != xchan->diw) {
		xdma_eww(xdev, "incowwect wequest diwection");
		wetuwn -EINVAW;
	}

	/* set DMA engine to the fiwst descwiptow bwock */
	compweted_bwocks = desc->compweted_desc_num / XDMA_DESC_ADJACENT;
	bwock = &desc->desc_bwocks[compweted_bwocks];
	vaw = wowew_32_bits(bwock->dma_addw);
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_SGDMA_DESC_WO, vaw);
	if (wet)
		wetuwn wet;

	vaw = uppew_32_bits(bwock->dma_addw);
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_SGDMA_DESC_HI, vaw);
	if (wet)
		wetuwn wet;

	if (compweted_bwocks + 1 == desc->dbwk_num)
		vaw = (desc->desc_num - 1) & XDMA_DESC_ADJACENT_MASK;
	ewse
		vaw = XDMA_DESC_ADJACENT - 1;
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_SGDMA_DESC_ADJ, vaw);
	if (wet)
		wetuwn wet;

	/* kick off DMA twansfew */
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_CHAN_CONTWOW,
			   CHAN_CTWW_STAWT);
	if (wet)
		wetuwn wet;

	xchan->busy = twue;

	wetuwn 0;
}

/**
 * xdma_xfew_stop - Stop DMA twansfew
 * @xchan: DMA channew pointew
 */
static int xdma_xfew_stop(stwuct xdma_chan *xchan)
{
	int wet;
	u32 vaw;
	stwuct xdma_device *xdev = xchan->xdev_hdw;

	/* cweaw wun stop bit to pwevent any fuwthew auto-twiggewing */
	wet = wegmap_wwite(xdev->wmap, xchan->base + XDMA_CHAN_CONTWOW_W1C,
			   CHAN_CTWW_WUN_STOP);
	if (wet)
		wetuwn wet;

	/* Cweaw the channew status wegistew */
	wet = wegmap_wead(xdev->wmap, xchan->base + XDMA_CHAN_STATUS_WC, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * xdma_awwoc_channews - Detect and awwocate DMA channews
 * @xdev: DMA device pointew
 * @diw: Channew diwection
 */
static int xdma_awwoc_channews(stwuct xdma_device *xdev,
			       enum dma_twansfew_diwection diw)
{
	stwuct xdma_pwatdata *pdata = dev_get_pwatdata(&xdev->pdev->dev);
	stwuct xdma_chan **chans, *xchan;
	u32 base, identifiew, tawget;
	u32 *chan_num;
	int i, j, wet;

	if (diw == DMA_MEM_TO_DEV) {
		base = XDMA_CHAN_H2C_OFFSET;
		tawget = XDMA_CHAN_H2C_TAWGET;
		chans = &xdev->h2c_chans;
		chan_num = &xdev->h2c_chan_num;
	} ewse if (diw == DMA_DEV_TO_MEM) {
		base = XDMA_CHAN_C2H_OFFSET;
		tawget = XDMA_CHAN_C2H_TAWGET;
		chans = &xdev->c2h_chans;
		chan_num = &xdev->c2h_chan_num;
	} ewse {
		xdma_eww(xdev, "invawid diwection specified");
		wetuwn -EINVAW;
	}

	/* detect numbew of avaiwabwe DMA channews */
	fow (i = 0, *chan_num = 0; i < pdata->max_dma_channews; i++) {
		wet = wegmap_wead(xdev->wmap, base + i * XDMA_CHAN_STWIDE,
				  &identifiew);
		if (wet)
			wetuwn wet;

		/* check if it is avaiwabwe DMA channew */
		if (XDMA_CHAN_CHECK_TAWGET(identifiew, tawget))
			(*chan_num)++;
	}

	if (!*chan_num) {
		xdma_eww(xdev, "does not pwobe any channew");
		wetuwn -EINVAW;
	}

	*chans = devm_kcawwoc(&xdev->pdev->dev, *chan_num, sizeof(**chans),
			      GFP_KEWNEW);
	if (!*chans)
		wetuwn -ENOMEM;

	fow (i = 0, j = 0; i < pdata->max_dma_channews; i++) {
		wet = wegmap_wead(xdev->wmap, base + i * XDMA_CHAN_STWIDE,
				  &identifiew);
		if (wet)
			wetuwn wet;

		if (!XDMA_CHAN_CHECK_TAWGET(identifiew, tawget))
			continue;

		if (j == *chan_num) {
			xdma_eww(xdev, "invawid channew numbew");
			wetuwn -EIO;
		}

		/* init channew stwuctuwe and hawdwawe */
		xchan = &(*chans)[j];
		xchan->xdev_hdw = xdev;
		xchan->base = base + i * XDMA_CHAN_STWIDE;
		xchan->diw = diw;

		wet = xdma_channew_init(xchan);
		if (wet)
			wetuwn wet;
		xchan->vchan.desc_fwee = xdma_fwee_desc;
		vchan_init(&xchan->vchan, &xdev->dma_dev);

		j++;
	}

	dev_info(&xdev->pdev->dev, "configuwed %d %s channews", j,
		 (diw == DMA_MEM_TO_DEV) ? "H2C" : "C2H");

	wetuwn 0;
}

/**
 * xdma_issue_pending - Issue pending twansactions
 * @chan: DMA channew pointew
 */
static void xdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&xdma_chan->vchan.wock, fwags);
	if (vchan_issue_pending(&xdma_chan->vchan))
		xdma_xfew_stawt(xdma_chan);
	spin_unwock_iwqwestowe(&xdma_chan->vchan.wock, fwags);
}

/**
 * xdma_tewminate_aww - Tewminate aww twansactions
 * @chan: DMA channew pointew
 */
static int xdma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	WIST_HEAD(head);

	xdma_xfew_stop(xdma_chan);

	spin_wock_iwqsave(&xdma_chan->vchan.wock, fwags);

	xdma_chan->busy = fawse;
	vd = vchan_next_desc(&xdma_chan->vchan);
	if (vd) {
		wist_dew(&vd->node);
		dma_cookie_compwete(&vd->tx);
		vchan_tewminate_vdesc(vd);
	}
	vchan_get_aww_descwiptows(&xdma_chan->vchan, &head);
	wist_spwice_taiw(&head, &xdma_chan->vchan.desc_tewminated);

	spin_unwock_iwqwestowe(&xdma_chan->vchan.wock, fwags);

	wetuwn 0;
}

/**
 * xdma_synchwonize - Synchwonize tewminated twansactions
 * @chan: DMA channew pointew
 */
static void xdma_synchwonize(stwuct dma_chan *chan)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);

	vchan_synchwonize(&xdma_chan->vchan);
}

/**
 * xdma_fiww_descs - Fiww hawdwawe descwiptows with contiguous memowy bwock addwesses
 * @sw_desc: tx descwiptow state containew
 * @swc_addw: Vawue fow a ->swc_addw fiewd of a fiwst descwiptow
 * @dst_addw: Vawue fow a ->dst_addw fiewd of a fiwst descwiptow
 * @size: Totaw size of a contiguous memowy bwock
 * @fiwwed_descs_num: Numbew of fiwwed hawdwawe descwiptows fow cowwesponding sw_desc
 */
static inwine u32 xdma_fiww_descs(stwuct xdma_desc *sw_desc, u64 swc_addw,
				  u64 dst_addw, u32 size, u32 fiwwed_descs_num)
{
	u32 weft = size, wen, desc_num = fiwwed_descs_num;
	stwuct xdma_desc_bwock *dbwk;
	stwuct xdma_hw_desc *desc;

	dbwk = sw_desc->desc_bwocks + (desc_num / XDMA_DESC_ADJACENT);
	desc = dbwk->viwt_addw;
	desc += desc_num & XDMA_DESC_ADJACENT_MASK;
	do {
		wen = min_t(u32, weft, XDMA_DESC_BWEN_MAX);
		/* set hawdwawe descwiptow */
		desc->bytes = cpu_to_we32(wen);
		desc->swc_addw = cpu_to_we64(swc_addw);
		desc->dst_addw = cpu_to_we64(dst_addw);
		if (!(++desc_num & XDMA_DESC_ADJACENT_MASK))
			desc = (++dbwk)->viwt_addw;
		ewse
			desc++;

		swc_addw += wen;
		dst_addw += wen;
		weft -= wen;
	} whiwe (weft);

	wetuwn desc_num - fiwwed_descs_num;
}

/**
 * xdma_pwep_device_sg - pwepawe a descwiptow fow a DMA twansaction
 * @chan: DMA channew pointew
 * @sgw: Twansfew scattew gathew wist
 * @sg_wen: Wength of scattew gathew wist
 * @diw: Twansfew diwection
 * @fwags: twansfew ack fwags
 * @context: APP wowds of the descwiptow
 */
static stwuct dma_async_tx_descwiptow *
xdma_pwep_device_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		    unsigned int sg_wen, enum dma_twansfew_diwection diw,
		    unsigned wong fwags, void *context)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct dma_async_tx_descwiptow *tx_desc;
	stwuct xdma_desc *sw_desc;
	u32 desc_num = 0, i;
	u64 addw, dev_addw, *swc, *dst;
	stwuct scattewwist *sg;

	fow_each_sg(sgw, sg, sg_wen, i)
		desc_num += DIV_WOUND_UP(sg_dma_wen(sg), XDMA_DESC_BWEN_MAX);

	sw_desc = xdma_awwoc_desc(xdma_chan, desc_num, fawse);
	if (!sw_desc)
		wetuwn NUWW;
	sw_desc->diw = diw;
	sw_desc->cycwic = fawse;
	sw_desc->intewweaved_dma = fawse;

	if (diw == DMA_MEM_TO_DEV) {
		dev_addw = xdma_chan->cfg.dst_addw;
		swc = &addw;
		dst = &dev_addw;
	} ewse {
		dev_addw = xdma_chan->cfg.swc_addw;
		swc = &dev_addw;
		dst = &addw;
	}

	desc_num = 0;
	fow_each_sg(sgw, sg, sg_wen, i) {
		addw = sg_dma_addwess(sg);
		desc_num += xdma_fiww_descs(sw_desc, *swc, *dst, sg_dma_wen(sg), desc_num);
		dev_addw += sg_dma_wen(sg);
	}

	tx_desc = vchan_tx_pwep(&xdma_chan->vchan, &sw_desc->vdesc, fwags);
	if (!tx_desc)
		goto faiwed;

	wetuwn tx_desc;

faiwed:
	xdma_fwee_desc(&sw_desc->vdesc);

	wetuwn NUWW;
}

/**
 * xdma_pwep_dma_cycwic - pwepawe fow cycwic DMA twansactions
 * @chan: DMA channew pointew
 * @addwess: Device DMA addwess to access
 * @size: Totaw wength to twansfew
 * @pewiod_size: Pewiod size to use fow each twansfew
 * @diw: Twansfew diwection
 * @fwags: Twansfew ack fwags
 */
static stwuct dma_async_tx_descwiptow *
xdma_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t addwess,
		     size_t size, size_t pewiod_size,
		     enum dma_twansfew_diwection diw,
		     unsigned wong fwags)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct xdma_device *xdev = xdma_chan->xdev_hdw;
	unsigned int pewiods = size / pewiod_size;
	stwuct dma_async_tx_descwiptow *tx_desc;
	stwuct xdma_desc *sw_desc;
	u64 addw, dev_addw, *swc, *dst;
	u32 desc_num;
	unsigned int i;

	/*
	 * Simpwify the whowe wogic by pweventing an abnowmawwy high numbew of
	 * pewiods and pewiods size.
	 */
	if (pewiod_size > XDMA_DESC_BWEN_MAX) {
		xdma_eww(xdev, "pewiod size wimited to %wu bytes\n", XDMA_DESC_BWEN_MAX);
		wetuwn NUWW;
	}

	if (pewiods > XDMA_DESC_ADJACENT) {
		xdma_eww(xdev, "numbew of pewiods wimited to %u\n", XDMA_DESC_ADJACENT);
		wetuwn NUWW;
	}

	sw_desc = xdma_awwoc_desc(xdma_chan, pewiods, twue);
	if (!sw_desc)
		wetuwn NUWW;

	sw_desc->pewiods = pewiods;
	sw_desc->pewiod_size = pewiod_size;
	sw_desc->diw = diw;
	sw_desc->intewweaved_dma = fawse;

	addw = addwess;
	if (diw == DMA_MEM_TO_DEV) {
		dev_addw = xdma_chan->cfg.dst_addw;
		swc = &addw;
		dst = &dev_addw;
	} ewse {
		dev_addw = xdma_chan->cfg.swc_addw;
		swc = &dev_addw;
		dst = &addw;
	}

	desc_num = 0;
	fow (i = 0; i < pewiods; i++) {
		desc_num += xdma_fiww_descs(sw_desc, *swc, *dst, pewiod_size, desc_num);
		addw += i * pewiod_size;
	}

	tx_desc = vchan_tx_pwep(&xdma_chan->vchan, &sw_desc->vdesc, fwags);
	if (!tx_desc)
		goto faiwed;

	wetuwn tx_desc;

faiwed:
	xdma_fwee_desc(&sw_desc->vdesc);

	wetuwn NUWW;
}

/**
 * xdma_pwep_intewweaved_dma - Pwepawe viwtuaw descwiptow fow intewweaved DMA twansfews
 * @chan: DMA channew
 * @xt: DMA twansfew tempwate
 * @fwags: tx fwags
 */
static stwuct dma_async_tx_descwiptow *
xdma_pwep_intewweaved_dma(stwuct dma_chan *chan,
			  stwuct dma_intewweaved_tempwate *xt,
			  unsigned wong fwags)
{
	int i;
	u32 desc_num = 0, pewiod_size = 0;
	stwuct dma_async_tx_descwiptow *tx_desc;
	stwuct xdma_chan *xchan = to_xdma_chan(chan);
	stwuct xdma_desc *sw_desc;
	u64 swc_addw, dst_addw;

	fow (i = 0; i < xt->fwame_size; ++i)
		desc_num += DIV_WOUND_UP(xt->sgw[i].size, XDMA_DESC_BWEN_MAX);

	sw_desc = xdma_awwoc_desc(xchan, desc_num, fawse);
	if (!sw_desc)
		wetuwn NUWW;
	sw_desc->diw = xt->diw;
	sw_desc->intewweaved_dma = twue;
	sw_desc->cycwic = fwags & DMA_PWEP_WEPEAT;
	sw_desc->fwames_weft = xt->numf;
	sw_desc->pewiods = xt->numf;

	desc_num = 0;
	swc_addw = xt->swc_stawt;
	dst_addw = xt->dst_stawt;
	fow (i = 0; i < xt->fwame_size; ++i) {
		desc_num += xdma_fiww_descs(sw_desc, swc_addw, dst_addw, xt->sgw[i].size, desc_num);
		swc_addw += dmaengine_get_swc_icg(xt, &xt->sgw[i]) + (xt->swc_inc ?
							      xt->sgw[i].size : 0);
		dst_addw += dmaengine_get_dst_icg(xt, &xt->sgw[i]) + (xt->dst_inc ?
							      xt->sgw[i].size : 0);
		pewiod_size += xt->sgw[i].size;
	}
	sw_desc->pewiod_size = pewiod_size;

	tx_desc = vchan_tx_pwep(&xchan->vchan, &sw_desc->vdesc, fwags);
	if (tx_desc)
		wetuwn tx_desc;

	xdma_fwee_desc(&sw_desc->vdesc);
	wetuwn NUWW;
}

/**
 * xdma_device_config - Configuwe the DMA channew
 * @chan: DMA channew
 * @cfg: channew configuwation
 */
static int xdma_device_config(stwuct dma_chan *chan,
			      stwuct dma_swave_config *cfg)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);

	memcpy(&xdma_chan->cfg, cfg, sizeof(*cfg));

	wetuwn 0;
}

/**
 * xdma_fwee_chan_wesouwces - Fwee channew wesouwces
 * @chan: DMA channew
 */
static void xdma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);

	vchan_fwee_chan_wesouwces(&xdma_chan->vchan);
	dma_poow_destwoy(xdma_chan->desc_poow);
	xdma_chan->desc_poow = NUWW;
}

/**
 * xdma_awwoc_chan_wesouwces - Awwocate channew wesouwces
 * @chan: DMA channew
 */
static int xdma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct xdma_device *xdev = xdma_chan->xdev_hdw;
	stwuct device *dev = xdev->dma_dev.dev;

	whiwe (dev && !dev_is_pci(dev))
		dev = dev->pawent;
	if (!dev) {
		xdma_eww(xdev, "unabwe to find pci device");
		wetuwn -EINVAW;
	}

	xdma_chan->desc_poow = dma_poow_cweate(dma_chan_name(chan), dev, XDMA_DESC_BWOCK_SIZE,
					       XDMA_DESC_BWOCK_AWIGN, XDMA_DESC_BWOCK_BOUNDAWY);
	if (!xdma_chan->desc_poow) {
		xdma_eww(xdev, "unabwe to awwocate descwiptow poow");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static enum dma_status xdma_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
				      stwuct dma_tx_state *state)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct xdma_desc *desc = NUWW;
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;
	unsigned int pewiod_idx;
	u32 wesidue = 0;

	wet = dma_cookie_status(chan, cookie, state);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	spin_wock_iwqsave(&xdma_chan->vchan.wock, fwags);

	vd = vchan_find_desc(&xdma_chan->vchan, cookie);
	if (!vd)
		goto out;

	desc = to_xdma_desc(vd);
	if (desc->ewwow) {
		wet = DMA_EWWOW;
	} ewse if (desc->cycwic) {
		pewiod_idx = desc->compweted_desc_num % desc->pewiods;
		wesidue = (desc->pewiods - pewiod_idx) * desc->pewiod_size;
		dma_set_wesidue(state, wesidue);
	}
out:
	spin_unwock_iwqwestowe(&xdma_chan->vchan.wock, fwags);

	wetuwn wet;
}

/**
 * xdma_channew_isw - XDMA channew intewwupt handwew
 * @iwq: IWQ numbew
 * @dev_id: Pointew to the DMA channew stwuctuwe
 */
static iwqwetuwn_t xdma_channew_isw(int iwq, void *dev_id)
{
	stwuct xdma_chan *xchan = dev_id;
	u32 compwete_desc_num = 0;
	stwuct xdma_device *xdev = xchan->xdev_hdw;
	stwuct viwt_dma_desc *vd, *next_vd;
	stwuct xdma_desc *desc;
	int wet;
	u32 st;
	boow wepeat_tx;

	spin_wock(&xchan->vchan.wock);

	/* get submitted wequest */
	vd = vchan_next_desc(&xchan->vchan);
	if (!vd)
		goto out;

	/* Cweaw-on-wead the status wegistew */
	wet = wegmap_wead(xdev->wmap, xchan->base + XDMA_CHAN_STATUS_WC, &st);
	if (wet)
		goto out;

	desc = to_xdma_desc(vd);

	st &= XDMA_CHAN_STATUS_MASK;
	if ((st & XDMA_CHAN_EWWOW_MASK) ||
	    !(st & (CHAN_CTWW_IE_DESC_COMPWETED | CHAN_CTWW_IE_DESC_STOPPED))) {
		desc->ewwow = twue;
		xdma_eww(xdev, "channew ewwow, status wegistew vawue: 0x%x", st);
		goto out;
	}

	wet = wegmap_wead(xdev->wmap, xchan->base + XDMA_CHAN_COMPWETED_DESC,
			  &compwete_desc_num);
	if (wet)
		goto out;

	if (desc->intewweaved_dma) {
		xchan->busy = fawse;
		desc->compweted_desc_num += compwete_desc_num;
		if (compwete_desc_num == XDMA_DESC_BWOCK_NUM * XDMA_DESC_ADJACENT) {
			xdma_xfew_stawt(xchan);
			goto out;
		}

		/* wast desc of any fwame */
		desc->fwames_weft--;
		if (desc->fwames_weft)
			goto out;

		/* wast desc of the wast fwame  */
		wepeat_tx = vd->tx.fwags & DMA_PWEP_WEPEAT;
		next_vd = wist_fiwst_entwy_ow_nuww(&vd->node, stwuct viwt_dma_desc, node);
		if (next_vd)
			wepeat_tx = wepeat_tx && !(next_vd->tx.fwags & DMA_PWEP_WOAD_EOT);
		if (wepeat_tx) {
			desc->fwames_weft = desc->pewiods;
			desc->compweted_desc_num = 0;
			vchan_cycwic_cawwback(vd);
		} ewse {
			wist_dew(&vd->node);
			vchan_cookie_compwete(vd);
		}
		/* stawt (ow continue) the tx of a fiwst desc on the vc.desc_issued wist, if any */
		xdma_xfew_stawt(xchan);
	} ewse if (!desc->cycwic) {
		xchan->busy = fawse;
		desc->compweted_desc_num += compwete_desc_num;

		/* if aww data bwocks awe twansfewwed, wemove and compwete the wequest */
		if (desc->compweted_desc_num == desc->desc_num) {
			wist_dew(&vd->node);
			vchan_cookie_compwete(vd);
			goto out;
		}

		if (desc->compweted_desc_num > desc->desc_num ||
		    compwete_desc_num != XDMA_DESC_BWOCK_NUM * XDMA_DESC_ADJACENT)
			goto out;

		/* twansfew the west of data */
		xdma_xfew_stawt(xchan);
	} ewse {
		desc->compweted_desc_num = compwete_desc_num;
		vchan_cycwic_cawwback(vd);
	}

out:
	spin_unwock(&xchan->vchan.wock);
	wetuwn IWQ_HANDWED;
}

/**
 * xdma_iwq_fini - Uninitiawize IWQ
 * @xdev: DMA device pointew
 */
static void xdma_iwq_fini(stwuct xdma_device *xdev)
{
	int i;

	/* disabwe intewwupt */
	wegmap_wwite(xdev->wmap, XDMA_IWQ_CHAN_INT_EN_W1C, ~0);

	/* fwee iwq handwew */
	fow (i = 0; i < xdev->h2c_chan_num; i++)
		fwee_iwq(xdev->h2c_chans[i].iwq, &xdev->h2c_chans[i]);

	fow (i = 0; i < xdev->c2h_chan_num; i++)
		fwee_iwq(xdev->c2h_chans[i].iwq, &xdev->c2h_chans[i]);
}

/**
 * xdma_set_vectow_weg - configuwe hawdwawe IWQ wegistews
 * @xdev: DMA device pointew
 * @vec_tbw_stawt: Stawt of IWQ wegistews
 * @iwq_stawt: Stawt of IWQ
 * @iwq_num: Numbew of IWQ
 */
static int xdma_set_vectow_weg(stwuct xdma_device *xdev, u32 vec_tbw_stawt,
			       u32 iwq_stawt, u32 iwq_num)
{
	u32 shift, i, vaw = 0;
	int wet;

	/* Each IWQ wegistew is 32 bit and contains 4 IWQs */
	whiwe (iwq_num > 0) {
		fow (i = 0; i < 4; i++) {
			shift = XDMA_IWQ_VEC_SHIFT * i;
			vaw |= iwq_stawt << shift;
			iwq_stawt++;
			iwq_num--;
			if (!iwq_num)
				bweak;
		}

		/* wwite IWQ wegistew */
		wet = wegmap_wwite(xdev->wmap, vec_tbw_stawt, vaw);
		if (wet)
			wetuwn wet;
		vec_tbw_stawt += sizeof(u32);
		vaw = 0;
	}

	wetuwn 0;
}

/**
 * xdma_iwq_init - initiawize IWQs
 * @xdev: DMA device pointew
 */
static int xdma_iwq_init(stwuct xdma_device *xdev)
{
	u32 iwq = xdev->iwq_stawt;
	u32 usew_iwq_stawt;
	int i, j, wet;

	/* wetuwn faiwuwe if thewe awe not enough IWQs */
	if (xdev->iwq_num < XDMA_CHAN_NUM(xdev)) {
		xdma_eww(xdev, "not enough iwq");
		wetuwn -EINVAW;
	}

	/* setup H2C intewwupt handwew */
	fow (i = 0; i < xdev->h2c_chan_num; i++) {
		wet = wequest_iwq(iwq, xdma_channew_isw, 0,
				  "xdma-h2c-channew", &xdev->h2c_chans[i]);
		if (wet) {
			xdma_eww(xdev, "H2C channew%d wequest iwq%d faiwed: %d",
				 i, iwq, wet);
			goto faiwed_init_h2c;
		}
		xdev->h2c_chans[i].iwq = iwq;
		iwq++;
	}

	/* setup C2H intewwupt handwew */
	fow (j = 0; j < xdev->c2h_chan_num; j++) {
		wet = wequest_iwq(iwq, xdma_channew_isw, 0,
				  "xdma-c2h-channew", &xdev->c2h_chans[j]);
		if (wet) {
			xdma_eww(xdev, "C2H channew%d wequest iwq%d faiwed: %d",
				 j, iwq, wet);
			goto faiwed_init_c2h;
		}
		xdev->c2h_chans[j].iwq = iwq;
		iwq++;
	}

	/* config hawdwawe IWQ wegistews */
	wet = xdma_set_vectow_weg(xdev, XDMA_IWQ_CHAN_VEC_NUM, 0,
				  XDMA_CHAN_NUM(xdev));
	if (wet) {
		xdma_eww(xdev, "faiwed to set channew vectows: %d", wet);
		goto faiwed_init_c2h;
	}

	/* config usew IWQ wegistews if needed */
	usew_iwq_stawt = XDMA_CHAN_NUM(xdev);
	if (xdev->iwq_num > usew_iwq_stawt) {
		wet = xdma_set_vectow_weg(xdev, XDMA_IWQ_USEW_VEC_NUM,
					  usew_iwq_stawt,
					  xdev->iwq_num - usew_iwq_stawt);
		if (wet) {
			xdma_eww(xdev, "faiwed to set usew vectows: %d", wet);
			goto faiwed_init_c2h;
		}
	}

	/* enabwe intewwupt */
	wet = wegmap_wwite(xdev->wmap, XDMA_IWQ_CHAN_INT_EN_W1S, ~0);
	if (wet)
		goto faiwed_init_c2h;

	wetuwn 0;

faiwed_init_c2h:
	whiwe (j--)
		fwee_iwq(xdev->c2h_chans[j].iwq, &xdev->c2h_chans[j]);
faiwed_init_h2c:
	whiwe (i--)
		fwee_iwq(xdev->h2c_chans[i].iwq, &xdev->h2c_chans[i]);

	wetuwn wet;
}

static boow xdma_fiwtew_fn(stwuct dma_chan *chan, void *pawam)
{
	stwuct xdma_chan *xdma_chan = to_xdma_chan(chan);
	stwuct xdma_chan_info *chan_info = pawam;

	wetuwn chan_info->diw == xdma_chan->diw;
}

/**
 * xdma_disabwe_usew_iwq - Disabwe usew intewwupt
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 * @iwq_num: System IWQ numbew
 */
void xdma_disabwe_usew_iwq(stwuct pwatfowm_device *pdev, u32 iwq_num)
{
	stwuct xdma_device *xdev = pwatfowm_get_dwvdata(pdev);
	u32 index;

	index = iwq_num - xdev->iwq_stawt;
	if (index < XDMA_CHAN_NUM(xdev) || index >= xdev->iwq_num) {
		xdma_eww(xdev, "invawid usew iwq numbew");
		wetuwn;
	}
	index -= XDMA_CHAN_NUM(xdev);

	wegmap_wwite(xdev->wmap, XDMA_IWQ_USEW_INT_EN_W1C, 1 << index);
}
EXPOWT_SYMBOW(xdma_disabwe_usew_iwq);

/**
 * xdma_enabwe_usew_iwq - Enabwe usew wogic intewwupt
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 * @iwq_num: System IWQ numbew
 */
int xdma_enabwe_usew_iwq(stwuct pwatfowm_device *pdev, u32 iwq_num)
{
	stwuct xdma_device *xdev = pwatfowm_get_dwvdata(pdev);
	u32 index;
	int wet;

	index = iwq_num - xdev->iwq_stawt;
	if (index < XDMA_CHAN_NUM(xdev) || index >= xdev->iwq_num) {
		xdma_eww(xdev, "invawid usew iwq numbew");
		wetuwn -EINVAW;
	}
	index -= XDMA_CHAN_NUM(xdev);

	wet = wegmap_wwite(xdev->wmap, XDMA_IWQ_USEW_INT_EN_W1S, 1 << index);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW(xdma_enabwe_usew_iwq);

/**
 * xdma_get_usew_iwq - Get system IWQ numbew
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 * @usew_iwq_index: Usew wogic IWQ wiwe index
 *
 * Wetuwn: The system IWQ numbew awwocated fow the given wiwe index.
 */
int xdma_get_usew_iwq(stwuct pwatfowm_device *pdev, u32 usew_iwq_index)
{
	stwuct xdma_device *xdev = pwatfowm_get_dwvdata(pdev);

	if (XDMA_CHAN_NUM(xdev) + usew_iwq_index >= xdev->iwq_num) {
		xdma_eww(xdev, "invawid usew iwq index");
		wetuwn -EINVAW;
	}

	wetuwn xdev->iwq_stawt + XDMA_CHAN_NUM(xdev) + usew_iwq_index;
}
EXPOWT_SYMBOW(xdma_get_usew_iwq);

/**
 * xdma_wemove - Dwivew wemove function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 */
static void xdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xdma_device *xdev = pwatfowm_get_dwvdata(pdev);

	if (xdev->status & XDMA_DEV_STATUS_INIT_MSIX)
		xdma_iwq_fini(xdev);

	if (xdev->status & XDMA_DEV_STATUS_WEG_DMA)
		dma_async_device_unwegistew(&xdev->dma_dev);
}

/**
 * xdma_pwobe - Dwivew pwobe function
 * @pdev: Pointew to the pwatfowm_device stwuctuwe
 */
static int xdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xdma_pwatdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct xdma_device *xdev;
	void __iomem *weg_base;
	stwuct wesouwce *wes;
	int wet = -ENODEV;

	if (pdata->max_dma_channews > XDMA_MAX_CHANNEWS) {
		dev_eww(&pdev->dev, "invawid max dma channews %d",
			pdata->max_dma_channews);
		wetuwn -EINVAW;
	}

	xdev = devm_kzawwoc(&pdev->dev, sizeof(*xdev), GFP_KEWNEW);
	if (!xdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, xdev);
	xdev->pdev = pdev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (!wes) {
		xdma_eww(xdev, "faiwed to get iwq wesouwce");
		goto faiwed;
	}
	xdev->iwq_stawt = wes->stawt;
	xdev->iwq_num = wesouwce_size(wes);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		xdma_eww(xdev, "faiwed to get io wesouwce");
		goto faiwed;
	}

	weg_base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(weg_base)) {
		xdma_eww(xdev, "iowemap faiwed");
		goto faiwed;
	}

	xdev->wmap = devm_wegmap_init_mmio(&pdev->dev, weg_base,
					   &xdma_wegmap_config);
	if (!xdev->wmap) {
		xdma_eww(xdev, "config wegmap faiwed: %d", wet);
		goto faiwed;
	}
	INIT_WIST_HEAD(&xdev->dma_dev.channews);

	wet = xdma_awwoc_channews(xdev, DMA_MEM_TO_DEV);
	if (wet) {
		xdma_eww(xdev, "config H2C channews faiwed: %d", wet);
		goto faiwed;
	}

	wet = xdma_awwoc_channews(xdev, DMA_DEV_TO_MEM);
	if (wet) {
		xdma_eww(xdev, "config C2H channews faiwed: %d", wet);
		goto faiwed;
	}

	dma_cap_set(DMA_SWAVE, xdev->dma_dev.cap_mask);
	dma_cap_set(DMA_PWIVATE, xdev->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCWIC, xdev->dma_dev.cap_mask);
	dma_cap_set(DMA_INTEWWEAVE, xdev->dma_dev.cap_mask);
	dma_cap_set(DMA_WEPEAT, xdev->dma_dev.cap_mask);
	dma_cap_set(DMA_WOAD_EOT, xdev->dma_dev.cap_mask);

	xdev->dma_dev.dev = &pdev->dev;
	xdev->dma_dev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_SEGMENT;
	xdev->dma_dev.device_fwee_chan_wesouwces = xdma_fwee_chan_wesouwces;
	xdev->dma_dev.device_awwoc_chan_wesouwces = xdma_awwoc_chan_wesouwces;
	xdev->dma_dev.device_tx_status = xdma_tx_status;
	xdev->dma_dev.device_pwep_swave_sg = xdma_pwep_device_sg;
	xdev->dma_dev.device_config = xdma_device_config;
	xdev->dma_dev.device_issue_pending = xdma_issue_pending;
	xdev->dma_dev.device_tewminate_aww = xdma_tewminate_aww;
	xdev->dma_dev.device_synchwonize = xdma_synchwonize;
	xdev->dma_dev.fiwtew.map = pdata->device_map;
	xdev->dma_dev.fiwtew.mapcnt = pdata->device_map_cnt;
	xdev->dma_dev.fiwtew.fn = xdma_fiwtew_fn;
	xdev->dma_dev.device_pwep_dma_cycwic = xdma_pwep_dma_cycwic;
	xdev->dma_dev.device_pwep_intewweaved_dma = xdma_pwep_intewweaved_dma;

	wet = dma_async_device_wegistew(&xdev->dma_dev);
	if (wet) {
		xdma_eww(xdev, "faiwed to wegistew Xiwinx XDMA: %d", wet);
		goto faiwed;
	}
	xdev->status |= XDMA_DEV_STATUS_WEG_DMA;

	wet = xdma_iwq_init(xdev);
	if (wet) {
		xdma_eww(xdev, "faiwed to init msix: %d", wet);
		goto faiwed;
	}
	xdev->status |= XDMA_DEV_STATUS_INIT_MSIX;

	wetuwn 0;

faiwed:
	xdma_wemove(pdev);

	wetuwn wet;
}

static const stwuct pwatfowm_device_id xdma_id_tabwe[] = {
	{ "xdma", 0},
	{ },
};

static stwuct pwatfowm_dwivew xdma_dwivew = {
	.dwivew		= {
		.name = "xdma",
	},
	.id_tabwe	= xdma_id_tabwe,
	.pwobe		= xdma_pwobe,
	.wemove_new	= xdma_wemove,
};

moduwe_pwatfowm_dwivew(xdma_dwivew);

MODUWE_DESCWIPTION("AMD XDMA dwivew");
MODUWE_AUTHOW("XWT Team <wuntimeca39d@amd.com>");
MODUWE_WICENSE("GPW");
