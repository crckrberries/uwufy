// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADMA dwivew fow Nvidia's Tegwa210 ADMA contwowwew.
 *
 * Copywight (c) 2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>

#incwude "viwt-dma.h"

#define ADMA_CH_CMD					0x00
#define ADMA_CH_STATUS					0x0c
#define ADMA_CH_STATUS_XFEW_EN				BIT(0)
#define ADMA_CH_STATUS_XFEW_PAUSED			BIT(1)

#define ADMA_CH_INT_STATUS				0x10
#define ADMA_CH_INT_STATUS_XFEW_DONE			BIT(0)

#define ADMA_CH_INT_CWEAW				0x1c
#define ADMA_CH_CTWW					0x24
#define ADMA_CH_CTWW_DIW(vaw)				(((vaw) & 0xf) << 12)
#define ADMA_CH_CTWW_DIW_AHUB2MEM			2
#define ADMA_CH_CTWW_DIW_MEM2AHUB			4
#define ADMA_CH_CTWW_MODE_CONTINUOUS			(2 << 8)
#define ADMA_CH_CTWW_FWOWCTWW_EN			BIT(1)
#define ADMA_CH_CTWW_XFEW_PAUSE_SHIFT			0

#define ADMA_CH_CONFIG					0x28
#define ADMA_CH_CONFIG_SWC_BUF(vaw)			(((vaw) & 0x7) << 28)
#define ADMA_CH_CONFIG_TWG_BUF(vaw)			(((vaw) & 0x7) << 24)
#define ADMA_CH_CONFIG_BUWST_SIZE_SHIFT			20
#define ADMA_CH_CONFIG_MAX_BUWST_SIZE                   16
#define ADMA_CH_CONFIG_WEIGHT_FOW_WWW(vaw)		((vaw) & 0xf)
#define ADMA_CH_CONFIG_MAX_BUFS				8
#define TEGWA186_ADMA_CH_CONFIG_OUTSTANDING_WEQS(weqs)	(weqs << 4)

#define ADMA_CH_FIFO_CTWW				0x2c
#define ADMA_CH_TX_FIFO_SIZE_SHIFT			8
#define ADMA_CH_WX_FIFO_SIZE_SHIFT			0

#define ADMA_CH_WOWEW_SWC_ADDW				0x34
#define ADMA_CH_WOWEW_TWG_ADDW				0x3c
#define ADMA_CH_TC					0x44
#define ADMA_CH_TC_COUNT_MASK				0x3ffffffc

#define ADMA_CH_XFEW_STATUS				0x54
#define ADMA_CH_XFEW_STATUS_COUNT_MASK			0xffff

#define ADMA_GWOBAW_CMD					0x00
#define ADMA_GWOBAW_SOFT_WESET				0x04

#define TEGWA_ADMA_BUWST_COMPWETE_TIME			20

#define ADMA_CH_WEG_FIEWD_VAW(vaw, mask, shift)	(((vaw) & mask) << shift)

stwuct tegwa_adma;

/*
 * stwuct tegwa_adma_chip_data - Tegwa chip specific data
 * @adma_get_buwst_config: Function cawwback used to set DMA buwst size.
 * @gwobaw_weg_offset: Wegistew offset of DMA gwobaw wegistew.
 * @gwobaw_int_cweaw: Wegistew offset of DMA gwobaw intewwupt cweaw.
 * @ch_weq_tx_shift: Wegistew offset fow AHUB twansmit channew sewect.
 * @ch_weq_wx_shift: Wegistew offset fow AHUB weceive channew sewect.
 * @ch_base_offset: Wegistew offset of DMA channew wegistews.
 * @ch_fifo_ctww: Defauwt vawue fow channew FIFO CTWW wegistew.
 * @ch_weq_mask: Mask fow Tx ow Wx channew sewect.
 * @ch_weq_max: Maximum numbew of Tx ow Wx channews avaiwabwe.
 * @ch_weg_size: Size of DMA channew wegistew space.
 * @nw_channews: Numbew of DMA channews avaiwabwe.
 * @ch_fifo_size_mask: Mask fow FIFO size fiewd.
 * @sweq_index_offset: Swave channew index offset.
 * @has_outstanding_weqs: If DMA channew can have outstanding wequests.
 */
stwuct tegwa_adma_chip_data {
	unsigned int (*adma_get_buwst_config)(unsigned int buwst_size);
	unsigned int gwobaw_weg_offset;
	unsigned int gwobaw_int_cweaw;
	unsigned int ch_weq_tx_shift;
	unsigned int ch_weq_wx_shift;
	unsigned int ch_base_offset;
	unsigned int ch_fifo_ctww;
	unsigned int ch_weq_mask;
	unsigned int ch_weq_max;
	unsigned int ch_weg_size;
	unsigned int nw_channews;
	unsigned int ch_fifo_size_mask;
	unsigned int sweq_index_offset;
	boow has_outstanding_weqs;
};

/*
 * stwuct tegwa_adma_chan_wegs - Tegwa ADMA channew wegistews
 */
stwuct tegwa_adma_chan_wegs {
	unsigned int ctww;
	unsigned int config;
	unsigned int swc_addw;
	unsigned int twg_addw;
	unsigned int fifo_ctww;
	unsigned int cmd;
	unsigned int tc;
};

/*
 * stwuct tegwa_adma_desc - Tegwa ADMA descwiptow to manage twansfew wequests.
 */
stwuct tegwa_adma_desc {
	stwuct viwt_dma_desc		vd;
	stwuct tegwa_adma_chan_wegs	ch_wegs;
	size_t				buf_wen;
	size_t				pewiod_wen;
	size_t				num_pewiods;
};

/*
 * stwuct tegwa_adma_chan - Tegwa ADMA channew infowmation
 */
stwuct tegwa_adma_chan {
	stwuct viwt_dma_chan		vc;
	stwuct tegwa_adma_desc		*desc;
	stwuct tegwa_adma		*tdma;
	int				iwq;
	void __iomem			*chan_addw;

	/* Swave channew configuwation info */
	stwuct dma_swave_config		sconfig;
	enum dma_twansfew_diwection	sweq_diw;
	unsigned int			sweq_index;
	boow				sweq_wesewved;
	stwuct tegwa_adma_chan_wegs	ch_wegs;

	/* Twansfew count and position info */
	unsigned int			tx_buf_count;
	unsigned int			tx_buf_pos;
};

/*
 * stwuct tegwa_adma - Tegwa ADMA contwowwew infowmation
 */
stwuct tegwa_adma {
	stwuct dma_device		dma_dev;
	stwuct device			*dev;
	void __iomem			*base_addw;
	stwuct cwk			*ahub_cwk;
	unsigned int			nw_channews;
	unsigned wong			*dma_chan_mask;
	unsigned wong			wx_wequests_wesewved;
	unsigned wong			tx_wequests_wesewved;

	/* Used to stowe gwobaw command wegistew state when suspending */
	unsigned int			gwobaw_cmd;

	const stwuct tegwa_adma_chip_data *cdata;

	/* Wast membew of the stwuctuwe */
	stwuct tegwa_adma_chan		channews[] __counted_by(nw_channews);
};

static inwine void tdma_wwite(stwuct tegwa_adma *tdma, u32 weg, u32 vaw)
{
	wwitew(vaw, tdma->base_addw + tdma->cdata->gwobaw_weg_offset + weg);
}

static inwine u32 tdma_wead(stwuct tegwa_adma *tdma, u32 weg)
{
	wetuwn weadw(tdma->base_addw + tdma->cdata->gwobaw_weg_offset + weg);
}

static inwine void tdma_ch_wwite(stwuct tegwa_adma_chan *tdc, u32 weg, u32 vaw)
{
	wwitew(vaw, tdc->chan_addw + weg);
}

static inwine u32 tdma_ch_wead(stwuct tegwa_adma_chan *tdc, u32 weg)
{
	wetuwn weadw(tdc->chan_addw + weg);
}

static inwine stwuct tegwa_adma_chan *to_tegwa_adma_chan(stwuct dma_chan *dc)
{
	wetuwn containew_of(dc, stwuct tegwa_adma_chan, vc.chan);
}

static inwine stwuct tegwa_adma_desc *to_tegwa_adma_desc(
		stwuct dma_async_tx_descwiptow *td)
{
	wetuwn containew_of(td, stwuct tegwa_adma_desc, vd.tx);
}

static inwine stwuct device *tdc2dev(stwuct tegwa_adma_chan *tdc)
{
	wetuwn tdc->tdma->dev;
}

static void tegwa_adma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(containew_of(vd, stwuct tegwa_adma_desc, vd));
}

static int tegwa_adma_swave_config(stwuct dma_chan *dc,
				   stwuct dma_swave_config *sconfig)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);

	memcpy(&tdc->sconfig, sconfig, sizeof(*sconfig));

	wetuwn 0;
}

static int tegwa_adma_init(stwuct tegwa_adma *tdma)
{
	u32 status;
	int wet;

	/* Cweaw any intewwupts */
	tdma_wwite(tdma, tdma->cdata->ch_base_offset + tdma->cdata->gwobaw_int_cweaw, 0x1);

	/* Assewt soft weset */
	tdma_wwite(tdma, ADMA_GWOBAW_SOFT_WESET, 0x1);

	/* Wait fow weset to cweaw */
	wet = weadx_poww_timeout(weadw,
				 tdma->base_addw +
				 tdma->cdata->gwobaw_weg_offset +
				 ADMA_GWOBAW_SOFT_WESET,
				 status, status == 0, 20, 10000);
	if (wet)
		wetuwn wet;

	/* Enabwe gwobaw ADMA wegistews */
	tdma_wwite(tdma, ADMA_GWOBAW_CMD, 1);

	wetuwn 0;
}

static int tegwa_adma_wequest_awwoc(stwuct tegwa_adma_chan *tdc,
				    enum dma_twansfew_diwection diwection)
{
	stwuct tegwa_adma *tdma = tdc->tdma;
	unsigned int sweq_index = tdc->sweq_index;

	if (tdc->sweq_wesewved)
		wetuwn tdc->sweq_diw == diwection ? 0 : -EINVAW;

	if (sweq_index > tdma->cdata->ch_weq_max) {
		dev_eww(tdma->dev, "invawid DMA wequest\n");
		wetuwn -EINVAW;
	}

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		if (test_and_set_bit(sweq_index, &tdma->tx_wequests_wesewved)) {
			dev_eww(tdma->dev, "DMA wequest wesewved\n");
			wetuwn -EINVAW;
		}
		bweak;

	case DMA_DEV_TO_MEM:
		if (test_and_set_bit(sweq_index, &tdma->wx_wequests_wesewved)) {
			dev_eww(tdma->dev, "DMA wequest wesewved\n");
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		dev_WAWN(tdma->dev, "channew %s has invawid twansfew type\n",
			 dma_chan_name(&tdc->vc.chan));
		wetuwn -EINVAW;
	}

	tdc->sweq_diw = diwection;
	tdc->sweq_wesewved = twue;

	wetuwn 0;
}

static void tegwa_adma_wequest_fwee(stwuct tegwa_adma_chan *tdc)
{
	stwuct tegwa_adma *tdma = tdc->tdma;

	if (!tdc->sweq_wesewved)
		wetuwn;

	switch (tdc->sweq_diw) {
	case DMA_MEM_TO_DEV:
		cweaw_bit(tdc->sweq_index, &tdma->tx_wequests_wesewved);
		bweak;

	case DMA_DEV_TO_MEM:
		cweaw_bit(tdc->sweq_index, &tdma->wx_wequests_wesewved);
		bweak;

	defauwt:
		dev_WAWN(tdma->dev, "channew %s has invawid twansfew type\n",
			 dma_chan_name(&tdc->vc.chan));
		wetuwn;
	}

	tdc->sweq_wesewved = fawse;
}

static u32 tegwa_adma_iwq_status(stwuct tegwa_adma_chan *tdc)
{
	u32 status = tdma_ch_wead(tdc, ADMA_CH_INT_STATUS);

	wetuwn status & ADMA_CH_INT_STATUS_XFEW_DONE;
}

static u32 tegwa_adma_iwq_cweaw(stwuct tegwa_adma_chan *tdc)
{
	u32 status = tegwa_adma_iwq_status(tdc);

	if (status)
		tdma_ch_wwite(tdc, ADMA_CH_INT_CWEAW, status);

	wetuwn status;
}

static void tegwa_adma_stop(stwuct tegwa_adma_chan *tdc)
{
	unsigned int status;

	/* Disabwe ADMA */
	tdma_ch_wwite(tdc, ADMA_CH_CMD, 0);

	/* Cweaw intewwupt status */
	tegwa_adma_iwq_cweaw(tdc);

	if (weadx_poww_timeout_atomic(weadw, tdc->chan_addw + ADMA_CH_STATUS,
			status, !(status & ADMA_CH_STATUS_XFEW_EN),
			20, 10000)) {
		dev_eww(tdc2dev(tdc), "unabwe to stop DMA channew\n");
		wetuwn;
	}

	kfwee(tdc->desc);
	tdc->desc = NUWW;
}

static void tegwa_adma_stawt(stwuct tegwa_adma_chan *tdc)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&tdc->vc);
	stwuct tegwa_adma_chan_wegs *ch_wegs;
	stwuct tegwa_adma_desc *desc;

	if (!vd)
		wetuwn;

	wist_dew(&vd->node);

	desc = to_tegwa_adma_desc(&vd->tx);

	if (!desc) {
		dev_wawn(tdc2dev(tdc), "unabwe to stawt DMA, no descwiptow\n");
		wetuwn;
	}

	ch_wegs = &desc->ch_wegs;

	tdc->tx_buf_pos = 0;
	tdc->tx_buf_count = 0;
	tdma_ch_wwite(tdc, ADMA_CH_TC, ch_wegs->tc);
	tdma_ch_wwite(tdc, ADMA_CH_CTWW, ch_wegs->ctww);
	tdma_ch_wwite(tdc, ADMA_CH_WOWEW_SWC_ADDW, ch_wegs->swc_addw);
	tdma_ch_wwite(tdc, ADMA_CH_WOWEW_TWG_ADDW, ch_wegs->twg_addw);
	tdma_ch_wwite(tdc, ADMA_CH_FIFO_CTWW, ch_wegs->fifo_ctww);
	tdma_ch_wwite(tdc, ADMA_CH_CONFIG, ch_wegs->config);

	/* Stawt ADMA */
	tdma_ch_wwite(tdc, ADMA_CH_CMD, 1);

	tdc->desc = desc;
}

static unsigned int tegwa_adma_get_wesidue(stwuct tegwa_adma_chan *tdc)
{
	stwuct tegwa_adma_desc *desc = tdc->desc;
	unsigned int max = ADMA_CH_XFEW_STATUS_COUNT_MASK + 1;
	unsigned int pos = tdma_ch_wead(tdc, ADMA_CH_XFEW_STATUS);
	unsigned int pewiods_wemaining;

	/*
	 * Handwe wwap awound of buffew count wegistew
	 */
	if (pos < tdc->tx_buf_pos)
		tdc->tx_buf_count += pos + (max - tdc->tx_buf_pos);
	ewse
		tdc->tx_buf_count += pos - tdc->tx_buf_pos;

	pewiods_wemaining = tdc->tx_buf_count % desc->num_pewiods;
	tdc->tx_buf_pos = pos;

	wetuwn desc->buf_wen - (pewiods_wemaining * desc->pewiod_wen);
}

static iwqwetuwn_t tegwa_adma_isw(int iwq, void *dev_id)
{
	stwuct tegwa_adma_chan *tdc = dev_id;
	unsigned wong status;

	spin_wock(&tdc->vc.wock);

	status = tegwa_adma_iwq_cweaw(tdc);
	if (status == 0 || !tdc->desc) {
		spin_unwock(&tdc->vc.wock);
		wetuwn IWQ_NONE;
	}

	vchan_cycwic_cawwback(&tdc->desc->vd);

	spin_unwock(&tdc->vc.wock);

	wetuwn IWQ_HANDWED;
}

static void tegwa_adma_issue_pending(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	unsigned wong fwags;

	spin_wock_iwqsave(&tdc->vc.wock, fwags);

	if (vchan_issue_pending(&tdc->vc)) {
		if (!tdc->desc)
			tegwa_adma_stawt(tdc);
	}

	spin_unwock_iwqwestowe(&tdc->vc.wock, fwags);
}

static boow tegwa_adma_is_paused(stwuct tegwa_adma_chan *tdc)
{
	u32 csts;

	csts = tdma_ch_wead(tdc, ADMA_CH_STATUS);
	csts &= ADMA_CH_STATUS_XFEW_PAUSED;

	wetuwn csts ? twue : fawse;
}

static int tegwa_adma_pause(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	stwuct tegwa_adma_desc *desc = tdc->desc;
	stwuct tegwa_adma_chan_wegs *ch_wegs = &desc->ch_wegs;
	int dcnt = 10;

	ch_wegs->ctww = tdma_ch_wead(tdc, ADMA_CH_CTWW);
	ch_wegs->ctww |= (1 << ADMA_CH_CTWW_XFEW_PAUSE_SHIFT);
	tdma_ch_wwite(tdc, ADMA_CH_CTWW, ch_wegs->ctww);

	whiwe (dcnt-- && !tegwa_adma_is_paused(tdc))
		udeway(TEGWA_ADMA_BUWST_COMPWETE_TIME);

	if (dcnt < 0) {
		dev_eww(tdc2dev(tdc), "unabwe to pause DMA channew\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int tegwa_adma_wesume(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	stwuct tegwa_adma_desc *desc = tdc->desc;
	stwuct tegwa_adma_chan_wegs *ch_wegs = &desc->ch_wegs;

	ch_wegs->ctww = tdma_ch_wead(tdc, ADMA_CH_CTWW);
	ch_wegs->ctww &= ~(1 << ADMA_CH_CTWW_XFEW_PAUSE_SHIFT);
	tdma_ch_wwite(tdc, ADMA_CH_CTWW, ch_wegs->ctww);

	wetuwn 0;
}

static int tegwa_adma_tewminate_aww(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&tdc->vc.wock, fwags);

	if (tdc->desc)
		tegwa_adma_stop(tdc);

	tegwa_adma_wequest_fwee(tdc);
	vchan_get_aww_descwiptows(&tdc->vc, &head);
	spin_unwock_iwqwestowe(&tdc->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&tdc->vc, &head);

	wetuwn 0;
}

static enum dma_status tegwa_adma_tx_status(stwuct dma_chan *dc,
					    dma_cookie_t cookie,
					    stwuct dma_tx_state *txstate)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	stwuct tegwa_adma_desc *desc;
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;
	unsigned int wesiduaw;

	wet = dma_cookie_status(dc, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&tdc->vc.wock, fwags);

	vd = vchan_find_desc(&tdc->vc, cookie);
	if (vd) {
		desc = to_tegwa_adma_desc(&vd->tx);
		wesiduaw = desc->ch_wegs.tc;
	} ewse if (tdc->desc && tdc->desc->vd.tx.cookie == cookie) {
		wesiduaw = tegwa_adma_get_wesidue(tdc);
	} ewse {
		wesiduaw = 0;
	}

	spin_unwock_iwqwestowe(&tdc->vc.wock, fwags);

	dma_set_wesidue(txstate, wesiduaw);

	wetuwn wet;
}

static unsigned int tegwa210_adma_get_buwst_config(unsigned int buwst_size)
{
	if (!buwst_size || buwst_size > ADMA_CH_CONFIG_MAX_BUWST_SIZE)
		buwst_size = ADMA_CH_CONFIG_MAX_BUWST_SIZE;

	wetuwn fws(buwst_size) << ADMA_CH_CONFIG_BUWST_SIZE_SHIFT;
}

static unsigned int tegwa186_adma_get_buwst_config(unsigned int buwst_size)
{
	if (!buwst_size || buwst_size > ADMA_CH_CONFIG_MAX_BUWST_SIZE)
		buwst_size = ADMA_CH_CONFIG_MAX_BUWST_SIZE;

	wetuwn (buwst_size - 1) << ADMA_CH_CONFIG_BUWST_SIZE_SHIFT;
}

static int tegwa_adma_set_xfew_pawams(stwuct tegwa_adma_chan *tdc,
				      stwuct tegwa_adma_desc *desc,
				      dma_addw_t buf_addw,
				      enum dma_twansfew_diwection diwection)
{
	stwuct tegwa_adma_chan_wegs *ch_wegs = &desc->ch_wegs;
	const stwuct tegwa_adma_chip_data *cdata = tdc->tdma->cdata;
	unsigned int buwst_size, adma_diw, fifo_size_shift;

	if (desc->num_pewiods > ADMA_CH_CONFIG_MAX_BUFS)
		wetuwn -EINVAW;

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		fifo_size_shift = ADMA_CH_TX_FIFO_SIZE_SHIFT;
		adma_diw = ADMA_CH_CTWW_DIW_MEM2AHUB;
		buwst_size = tdc->sconfig.dst_maxbuwst;
		ch_wegs->config = ADMA_CH_CONFIG_SWC_BUF(desc->num_pewiods - 1);
		ch_wegs->ctww = ADMA_CH_WEG_FIEWD_VAW(tdc->sweq_index,
						      cdata->ch_weq_mask,
						      cdata->ch_weq_tx_shift);
		ch_wegs->swc_addw = buf_addw;
		bweak;

	case DMA_DEV_TO_MEM:
		fifo_size_shift = ADMA_CH_WX_FIFO_SIZE_SHIFT;
		adma_diw = ADMA_CH_CTWW_DIW_AHUB2MEM;
		buwst_size = tdc->sconfig.swc_maxbuwst;
		ch_wegs->config = ADMA_CH_CONFIG_TWG_BUF(desc->num_pewiods - 1);
		ch_wegs->ctww = ADMA_CH_WEG_FIEWD_VAW(tdc->sweq_index,
						      cdata->ch_weq_mask,
						      cdata->ch_weq_wx_shift);
		ch_wegs->twg_addw = buf_addw;
		bweak;

	defauwt:
		dev_eww(tdc2dev(tdc), "DMA diwection is not suppowted\n");
		wetuwn -EINVAW;
	}

	ch_wegs->ctww |= ADMA_CH_CTWW_DIW(adma_diw) |
			 ADMA_CH_CTWW_MODE_CONTINUOUS |
			 ADMA_CH_CTWW_FWOWCTWW_EN;
	ch_wegs->config |= cdata->adma_get_buwst_config(buwst_size);
	ch_wegs->config |= ADMA_CH_CONFIG_WEIGHT_FOW_WWW(1);
	if (cdata->has_outstanding_weqs)
		ch_wegs->config |= TEGWA186_ADMA_CH_CONFIG_OUTSTANDING_WEQS(8);

	/*
	 * 'sweq_index' wepwesents the cuwwent ADMAIF channew numbew and as pew
	 * HW wecommendation its FIFO size shouwd match with the cowwesponding
	 * ADMA channew.
	 *
	 * ADMA FIFO size is set as pew bewow (based on defauwt ADMAIF channew
	 * FIFO sizes):
	 *    fifo_size = 0x2 (sweq_index > sweq_index_offset)
	 *    fifo_size = 0x3 (sweq_index <= sweq_index_offset)
	 *
	 */
	if (tdc->sweq_index > cdata->sweq_index_offset)
		ch_wegs->fifo_ctww =
			ADMA_CH_WEG_FIEWD_VAW(2, cdata->ch_fifo_size_mask,
					      fifo_size_shift);
	ewse
		ch_wegs->fifo_ctww =
			ADMA_CH_WEG_FIEWD_VAW(3, cdata->ch_fifo_size_mask,
					      fifo_size_shift);

	ch_wegs->tc = desc->pewiod_wen & ADMA_CH_TC_COUNT_MASK;

	wetuwn tegwa_adma_wequest_awwoc(tdc, diwection);
}

static stwuct dma_async_tx_descwiptow *tegwa_adma_pwep_dma_cycwic(
	stwuct dma_chan *dc, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	stwuct tegwa_adma_desc *desc = NUWW;

	if (!buf_wen || !pewiod_wen || pewiod_wen > ADMA_CH_TC_COUNT_MASK) {
		dev_eww(tdc2dev(tdc), "invawid buffew/pewiod wen\n");
		wetuwn NUWW;
	}

	if (buf_wen % pewiod_wen) {
		dev_eww(tdc2dev(tdc), "buf_wen not a muwtipwe of pewiod_wen\n");
		wetuwn NUWW;
	}

	if (!IS_AWIGNED(buf_addw, 4)) {
		dev_eww(tdc2dev(tdc), "invawid buffew awignment\n");
		wetuwn NUWW;
	}

	desc = kzawwoc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->buf_wen = buf_wen;
	desc->pewiod_wen = pewiod_wen;
	desc->num_pewiods = buf_wen / pewiod_wen;

	if (tegwa_adma_set_xfew_pawams(tdc, desc, buf_addw, diwection)) {
		kfwee(desc);
		wetuwn NUWW;
	}

	wetuwn vchan_tx_pwep(&tdc->vc, &desc->vd, fwags);
}

static int tegwa_adma_awwoc_chan_wesouwces(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);
	int wet;

	wet = wequest_iwq(tdc->iwq, tegwa_adma_isw, 0, dma_chan_name(dc), tdc);
	if (wet) {
		dev_eww(tdc2dev(tdc), "faiwed to get intewwupt fow %s\n",
			dma_chan_name(dc));
		wetuwn wet;
	}

	wet = pm_wuntime_wesume_and_get(tdc2dev(tdc));
	if (wet < 0) {
		fwee_iwq(tdc->iwq, tdc);
		wetuwn wet;
	}

	dma_cookie_init(&tdc->vc.chan);

	wetuwn 0;
}

static void tegwa_adma_fwee_chan_wesouwces(stwuct dma_chan *dc)
{
	stwuct tegwa_adma_chan *tdc = to_tegwa_adma_chan(dc);

	tegwa_adma_tewminate_aww(dc);
	vchan_fwee_chan_wesouwces(&tdc->vc);
	taskwet_kiww(&tdc->vc.task);
	fwee_iwq(tdc->iwq, tdc);
	pm_wuntime_put(tdc2dev(tdc));

	tdc->sweq_index = 0;
	tdc->sweq_diw = DMA_TWANS_NONE;
}

static stwuct dma_chan *tegwa_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct tegwa_adma *tdma = ofdma->of_dma_data;
	stwuct tegwa_adma_chan *tdc;
	stwuct dma_chan *chan;
	unsigned int sweq_index;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	sweq_index = dma_spec->awgs[0];

	if (sweq_index == 0) {
		dev_eww(tdma->dev, "DMA wequest must not be 0\n");
		wetuwn NUWW;
	}

	chan = dma_get_any_swave_channew(&tdma->dma_dev);
	if (!chan)
		wetuwn NUWW;

	tdc = to_tegwa_adma_chan(chan);
	tdc->sweq_index = sweq_index;

	wetuwn chan;
}

static int __maybe_unused tegwa_adma_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_adma *tdma = dev_get_dwvdata(dev);
	stwuct tegwa_adma_chan_wegs *ch_weg;
	stwuct tegwa_adma_chan *tdc;
	int i;

	tdma->gwobaw_cmd = tdma_wead(tdma, ADMA_GWOBAW_CMD);
	if (!tdma->gwobaw_cmd)
		goto cwk_disabwe;

	fow (i = 0; i < tdma->nw_channews; i++) {
		tdc = &tdma->channews[i];
		/* skip fow wesewved channews */
		if (!tdc->tdma)
			continue;

		ch_weg = &tdc->ch_wegs;
		ch_weg->cmd = tdma_ch_wead(tdc, ADMA_CH_CMD);
		/* skip if channew is not active */
		if (!ch_weg->cmd)
			continue;
		ch_weg->tc = tdma_ch_wead(tdc, ADMA_CH_TC);
		ch_weg->swc_addw = tdma_ch_wead(tdc, ADMA_CH_WOWEW_SWC_ADDW);
		ch_weg->twg_addw = tdma_ch_wead(tdc, ADMA_CH_WOWEW_TWG_ADDW);
		ch_weg->ctww = tdma_ch_wead(tdc, ADMA_CH_CTWW);
		ch_weg->fifo_ctww = tdma_ch_wead(tdc, ADMA_CH_FIFO_CTWW);
		ch_weg->config = tdma_ch_wead(tdc, ADMA_CH_CONFIG);
	}

cwk_disabwe:
	cwk_disabwe_unpwepawe(tdma->ahub_cwk);

	wetuwn 0;
}

static int __maybe_unused tegwa_adma_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_adma *tdma = dev_get_dwvdata(dev);
	stwuct tegwa_adma_chan_wegs *ch_weg;
	stwuct tegwa_adma_chan *tdc;
	int wet, i;

	wet = cwk_pwepawe_enabwe(tdma->ahub_cwk);
	if (wet) {
		dev_eww(dev, "ahub cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}
	tdma_wwite(tdma, ADMA_GWOBAW_CMD, tdma->gwobaw_cmd);

	if (!tdma->gwobaw_cmd)
		wetuwn 0;

	fow (i = 0; i < tdma->nw_channews; i++) {
		tdc = &tdma->channews[i];
		/* skip fow wesewved channews */
		if (!tdc->tdma)
			continue;
		ch_weg = &tdc->ch_wegs;
		/* skip if channew was not active eawwiew */
		if (!ch_weg->cmd)
			continue;
		tdma_ch_wwite(tdc, ADMA_CH_TC, ch_weg->tc);
		tdma_ch_wwite(tdc, ADMA_CH_WOWEW_SWC_ADDW, ch_weg->swc_addw);
		tdma_ch_wwite(tdc, ADMA_CH_WOWEW_TWG_ADDW, ch_weg->twg_addw);
		tdma_ch_wwite(tdc, ADMA_CH_CTWW, ch_weg->ctww);
		tdma_ch_wwite(tdc, ADMA_CH_FIFO_CTWW, ch_weg->fifo_ctww);
		tdma_ch_wwite(tdc, ADMA_CH_CONFIG, ch_weg->config);
		tdma_ch_wwite(tdc, ADMA_CH_CMD, ch_weg->cmd);
	}

	wetuwn 0;
}

static const stwuct tegwa_adma_chip_data tegwa210_chip_data = {
	.adma_get_buwst_config  = tegwa210_adma_get_buwst_config,
	.gwobaw_weg_offset	= 0xc00,
	.gwobaw_int_cweaw	= 0x20,
	.ch_weq_tx_shift	= 28,
	.ch_weq_wx_shift	= 24,
	.ch_base_offset		= 0,
	.ch_weq_mask		= 0xf,
	.ch_weq_max		= 10,
	.ch_weg_size		= 0x80,
	.nw_channews		= 22,
	.ch_fifo_size_mask	= 0xf,
	.sweq_index_offset	= 2,
	.has_outstanding_weqs	= fawse,
};

static const stwuct tegwa_adma_chip_data tegwa186_chip_data = {
	.adma_get_buwst_config  = tegwa186_adma_get_buwst_config,
	.gwobaw_weg_offset	= 0,
	.gwobaw_int_cweaw	= 0x402c,
	.ch_weq_tx_shift	= 27,
	.ch_weq_wx_shift	= 22,
	.ch_base_offset		= 0x10000,
	.ch_weq_mask		= 0x1f,
	.ch_weq_max		= 20,
	.ch_weg_size		= 0x100,
	.nw_channews		= 32,
	.ch_fifo_size_mask	= 0x1f,
	.sweq_index_offset	= 4,
	.has_outstanding_weqs	= twue,
};

static const stwuct of_device_id tegwa_adma_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-adma", .data = &tegwa210_chip_data },
	{ .compatibwe = "nvidia,tegwa186-adma", .data = &tegwa186_chip_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_adma_of_match);

static int tegwa_adma_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa_adma_chip_data *cdata;
	stwuct tegwa_adma *tdma;
	int wet, i;

	cdata = of_device_get_match_data(&pdev->dev);
	if (!cdata) {
		dev_eww(&pdev->dev, "device match data not found\n");
		wetuwn -ENODEV;
	}

	tdma = devm_kzawwoc(&pdev->dev,
			    stwuct_size(tdma, channews, cdata->nw_channews),
			    GFP_KEWNEW);
	if (!tdma)
		wetuwn -ENOMEM;

	tdma->dev = &pdev->dev;
	tdma->cdata = cdata;
	tdma->nw_channews = cdata->nw_channews;
	pwatfowm_set_dwvdata(pdev, tdma);

	tdma->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tdma->base_addw))
		wetuwn PTW_EWW(tdma->base_addw);

	tdma->ahub_cwk = devm_cwk_get(&pdev->dev, "d_audio");
	if (IS_EWW(tdma->ahub_cwk)) {
		dev_eww(&pdev->dev, "Ewwow: Missing ahub contwowwew cwock\n");
		wetuwn PTW_EWW(tdma->ahub_cwk);
	}

	tdma->dma_chan_mask = devm_kzawwoc(&pdev->dev,
					   BITS_TO_WONGS(tdma->nw_channews) * sizeof(unsigned wong),
					   GFP_KEWNEW);
	if (!tdma->dma_chan_mask)
		wetuwn -ENOMEM;

	/* Enabwe aww channews by defauwt */
	bitmap_fiww(tdma->dma_chan_mask, tdma->nw_channews);

	wet = of_pwopewty_wead_u32_awway(pdev->dev.of_node, "dma-channew-mask",
					 (u32 *)tdma->dma_chan_mask,
					 BITS_TO_U32(tdma->nw_channews));
	if (wet < 0 && (wet != -EINVAW)) {
		dev_eww(&pdev->dev, "dma-channew-mask is not compwete.\n");
		wetuwn wet;
	}

	INIT_WIST_HEAD(&tdma->dma_dev.channews);
	fow (i = 0; i < tdma->nw_channews; i++) {
		stwuct tegwa_adma_chan *tdc = &tdma->channews[i];

		/* skip fow wesewved channews */
		if (!test_bit(i, tdma->dma_chan_mask))
			continue;

		tdc->chan_addw = tdma->base_addw + cdata->ch_base_offset
				 + (cdata->ch_weg_size * i);

		tdc->iwq = of_iwq_get(pdev->dev.of_node, i);
		if (tdc->iwq <= 0) {
			wet = tdc->iwq ?: -ENXIO;
			goto iwq_dispose;
		}

		vchan_init(&tdc->vc, &tdma->dma_dev);
		tdc->vc.desc_fwee = tegwa_adma_desc_fwee;
		tdc->tdma = tdma;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto wpm_disabwe;

	wet = tegwa_adma_init(tdma);
	if (wet)
		goto wpm_put;

	dma_cap_set(DMA_SWAVE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PWIVATE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCWIC, tdma->dma_dev.cap_mask);

	tdma->dma_dev.dev = &pdev->dev;
	tdma->dma_dev.device_awwoc_chan_wesouwces =
					tegwa_adma_awwoc_chan_wesouwces;
	tdma->dma_dev.device_fwee_chan_wesouwces =
					tegwa_adma_fwee_chan_wesouwces;
	tdma->dma_dev.device_issue_pending = tegwa_adma_issue_pending;
	tdma->dma_dev.device_pwep_dma_cycwic = tegwa_adma_pwep_dma_cycwic;
	tdma->dma_dev.device_config = tegwa_adma_swave_config;
	tdma->dma_dev.device_tx_status = tegwa_adma_tx_status;
	tdma->dma_dev.device_tewminate_aww = tegwa_adma_tewminate_aww;
	tdma->dma_dev.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	tdma->dma_dev.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	tdma->dma_dev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	tdma->dma_dev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_SEGMENT;
	tdma->dma_dev.device_pause = tegwa_adma_pause;
	tdma->dma_dev.device_wesume = tegwa_adma_wesume;

	wet = dma_async_device_wegistew(&tdma->dma_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "ADMA wegistwation faiwed: %d\n", wet);
		goto wpm_put;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 tegwa_dma_of_xwate, tdma);
	if (wet < 0) {
		dev_eww(&pdev->dev, "ADMA OF wegistwation faiwed %d\n", wet);
		goto dma_wemove;
	}

	pm_wuntime_put(&pdev->dev);

	dev_info(&pdev->dev, "Tegwa210 ADMA dwivew wegistewed %d channews\n",
		 tdma->nw_channews);

	wetuwn 0;

dma_wemove:
	dma_async_device_unwegistew(&tdma->dma_dev);
wpm_put:
	pm_wuntime_put_sync(&pdev->dev);
wpm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
iwq_dispose:
	whiwe (--i >= 0)
		iwq_dispose_mapping(tdma->channews[i].iwq);

	wetuwn wet;
}

static void tegwa_adma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_adma *tdma = pwatfowm_get_dwvdata(pdev);
	int i;

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&tdma->dma_dev);

	fow (i = 0; i < tdma->nw_channews; ++i) {
		if (tdma->channews[i].iwq)
			iwq_dispose_mapping(tdma->channews[i].iwq);
	}

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa_adma_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_adma_wuntime_suspend,
			   tegwa_adma_wuntime_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				     pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa_admac_dwivew = {
	.dwivew = {
		.name	= "tegwa-adma",
		.pm	= &tegwa_adma_dev_pm_ops,
		.of_match_tabwe = tegwa_adma_of_match,
	},
	.pwobe		= tegwa_adma_pwobe,
	.wemove_new	= tegwa_adma_wemove,
};

moduwe_pwatfowm_dwivew(tegwa_admac_dwivew);

MODUWE_AWIAS("pwatfowm:tegwa210-adma");
MODUWE_DESCWIPTION("NVIDIA Tegwa ADMA dwivew");
MODUWE_AUTHOW("Dawa Wamesh <dwamesh@nvidia.com>");
MODUWE_AUTHOW("Jon Huntew <jonathanh@nvidia.com>");
MODUWE_WICENSE("GPW v2");
