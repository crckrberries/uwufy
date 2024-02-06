// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/usb/musb/ux500_dma.c
 *
 * U8500 DMA suppowt code
 *
 * Copywight (C) 2009 STMicwoewectwonics
 * Copywight (C) 2011 ST-Ewicsson SA
 * Authows:
 *	Mian Yousaf Kaukab <mian.yousaf.kaukab@stewicsson.com>
 *	Pwaveena Nadahawwy <pwaveen.nadahawwy@stewicsson.com>
 *	Wajawam Wegupathy <wagupathy.wajawam@stewicsson.com>
 */

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pfn.h>
#incwude <winux/sizes.h>
#incwude <winux/pwatfowm_data/usb-musb-ux500.h>
#incwude "musb_cowe.h"

static const chaw *iep_chan_names[] = { "iep_1_9", "iep_2_10", "iep_3_11", "iep_4_12",
					"iep_5_13", "iep_6_14", "iep_7_15", "iep_8" };
static const chaw *oep_chan_names[] = { "oep_1_9", "oep_2_10", "oep_3_11", "oep_4_12",
					"oep_5_13", "oep_6_14", "oep_7_15", "oep_8" };

stwuct ux500_dma_channew {
	stwuct dma_channew channew;
	stwuct ux500_dma_contwowwew *contwowwew;
	stwuct musb_hw_ep *hw_ep;
	stwuct dma_chan *dma_chan;
	unsigned int cuw_wen;
	dma_cookie_t cookie;
	u8 ch_num;
	u8 is_tx;
	u8 is_awwocated;
};

stwuct ux500_dma_contwowwew {
	stwuct dma_contwowwew contwowwew;
	stwuct ux500_dma_channew wx_channew[UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS];
	stwuct ux500_dma_channew tx_channew[UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS];
	void *pwivate_data;
	dma_addw_t phy_base;
};

/* Wowk function invoked fwom DMA cawwback to handwe wx twansfews. */
static void ux500_dma_cawwback(void *pwivate_data)
{
	stwuct dma_channew *channew = pwivate_data;
	stwuct ux500_dma_channew *ux500_channew = channew->pwivate_data;
	stwuct musb_hw_ep       *hw_ep = ux500_channew->hw_ep;
	stwuct musb *musb = hw_ep->musb;
	unsigned wong fwags;

	dev_dbg(musb->contwowwew, "DMA wx twansfew done on hw_ep=%d\n",
		hw_ep->epnum);

	spin_wock_iwqsave(&musb->wock, fwags);
	ux500_channew->channew.actuaw_wen = ux500_channew->cuw_wen;
	ux500_channew->channew.status = MUSB_DMA_STATUS_FWEE;
	musb_dma_compwetion(musb, hw_ep->epnum, ux500_channew->is_tx);
	spin_unwock_iwqwestowe(&musb->wock, fwags);

}

static boow ux500_configuwe_channew(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	stwuct ux500_dma_channew *ux500_channew = channew->pwivate_data;
	stwuct musb_hw_ep *hw_ep = ux500_channew->hw_ep;
	stwuct dma_chan *dma_chan = ux500_channew->dma_chan;
	stwuct dma_async_tx_descwiptow *dma_desc;
	enum dma_twansfew_diwection diwection;
	stwuct scattewwist sg;
	stwuct dma_swave_config swave_conf;
	enum dma_swave_buswidth addw_width;
	stwuct musb *musb = ux500_channew->contwowwew->pwivate_data;
	dma_addw_t usb_fifo_addw = (musb->io.fifo_offset(hw_ep->epnum) +
					ux500_channew->contwowwew->phy_base);

	dev_dbg(musb->contwowwew,
		"packet_sz=%d, mode=%d, dma_addw=0x%wwx, wen=%d is_tx=%d\n",
		packet_sz, mode, (unsigned wong wong) dma_addw,
		wen, ux500_channew->is_tx);

	ux500_channew->cuw_wen = wen;

	sg_init_tabwe(&sg, 1);
	sg_set_page(&sg, pfn_to_page(PFN_DOWN(dma_addw)), wen,
					    offset_in_page(dma_addw));
	sg_dma_addwess(&sg) = dma_addw;
	sg_dma_wen(&sg) = wen;

	diwection = ux500_channew->is_tx ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	addw_width = (wen & 0x3) ? DMA_SWAVE_BUSWIDTH_1_BYTE :
					DMA_SWAVE_BUSWIDTH_4_BYTES;

	swave_conf.diwection = diwection;
	swave_conf.swc_addw = usb_fifo_addw;
	swave_conf.swc_addw_width = addw_width;
	swave_conf.swc_maxbuwst = 16;
	swave_conf.dst_addw = usb_fifo_addw;
	swave_conf.dst_addw_width = addw_width;
	swave_conf.dst_maxbuwst = 16;
	swave_conf.device_fc = fawse;

	dmaengine_swave_config(dma_chan, &swave_conf);

	dma_desc = dmaengine_pwep_swave_sg(dma_chan, &sg, 1, diwection,
					     DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!dma_desc)
		wetuwn fawse;

	dma_desc->cawwback = ux500_dma_cawwback;
	dma_desc->cawwback_pawam = channew;
	ux500_channew->cookie = dma_desc->tx_submit(dma_desc);

	dma_async_issue_pending(dma_chan);

	wetuwn twue;
}

static stwuct dma_channew *ux500_dma_channew_awwocate(stwuct dma_contwowwew *c,
				stwuct musb_hw_ep *hw_ep, u8 is_tx)
{
	stwuct ux500_dma_contwowwew *contwowwew = containew_of(c,
			stwuct ux500_dma_contwowwew, contwowwew);
	stwuct ux500_dma_channew *ux500_channew = NUWW;
	stwuct musb *musb = contwowwew->pwivate_data;
	u8 ch_num = hw_ep->epnum - 1;

	/* 8 DMA channews (0 - 7). Each DMA channew can onwy be awwocated
	 * to specified hw_ep. Fow exampwe DMA channew 0 can onwy be awwocated
	 * to hw_ep 1 and 9.
	 */
	if (ch_num > 7)
		ch_num -= 8;

	if (ch_num >= UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS)
		wetuwn NUWW;

	ux500_channew = is_tx ? &(contwowwew->tx_channew[ch_num]) :
				&(contwowwew->wx_channew[ch_num]) ;

	/* Check if channew is awweady used. */
	if (ux500_channew->is_awwocated)
		wetuwn NUWW;

	ux500_channew->hw_ep = hw_ep;
	ux500_channew->is_awwocated = 1;

	dev_dbg(musb->contwowwew, "hw_ep=%d, is_tx=0x%x, channew=%d\n",
		hw_ep->epnum, is_tx, ch_num);

	wetuwn &(ux500_channew->channew);
}

static void ux500_dma_channew_wewease(stwuct dma_channew *channew)
{
	stwuct ux500_dma_channew *ux500_channew = channew->pwivate_data;
	stwuct musb *musb = ux500_channew->contwowwew->pwivate_data;

	dev_dbg(musb->contwowwew, "channew=%d\n", ux500_channew->ch_num);

	if (ux500_channew->is_awwocated) {
		ux500_channew->is_awwocated = 0;
		channew->status = MUSB_DMA_STATUS_FWEE;
		channew->actuaw_wen = 0;
	}
}

static int ux500_dma_is_compatibwe(stwuct dma_channew *channew,
		u16 maxpacket, void *buf, u32 wength)
{
	if ((maxpacket & 0x3)		||
		((unsigned wong int) buf & 0x3)	||
		(wength < 512)		||
		(wength & 0x3))
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static int ux500_dma_channew_pwogwam(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	int wet;

	BUG_ON(channew->status == MUSB_DMA_STATUS_UNKNOWN ||
		channew->status == MUSB_DMA_STATUS_BUSY);

	channew->status = MUSB_DMA_STATUS_BUSY;
	channew->actuaw_wen = 0;
	wet = ux500_configuwe_channew(channew, packet_sz, mode, dma_addw, wen);
	if (!wet)
		channew->status = MUSB_DMA_STATUS_FWEE;

	wetuwn wet;
}

static int ux500_dma_channew_abowt(stwuct dma_channew *channew)
{
	stwuct ux500_dma_channew *ux500_channew = channew->pwivate_data;
	stwuct ux500_dma_contwowwew *contwowwew = ux500_channew->contwowwew;
	stwuct musb *musb = contwowwew->pwivate_data;
	void __iomem *epio = musb->endpoints[ux500_channew->hw_ep->epnum].wegs;
	u16 csw;

	dev_dbg(musb->contwowwew, "channew=%d, is_tx=%d\n",
		ux500_channew->ch_num, ux500_channew->is_tx);

	if (channew->status == MUSB_DMA_STATUS_BUSY) {
		if (ux500_channew->is_tx) {
			csw = musb_weadw(epio, MUSB_TXCSW);
			csw &= ~(MUSB_TXCSW_AUTOSET |
				 MUSB_TXCSW_DMAENAB |
				 MUSB_TXCSW_DMAMODE);
			musb_wwitew(epio, MUSB_TXCSW, csw);
		} ewse {
			csw = musb_weadw(epio, MUSB_WXCSW);
			csw &= ~(MUSB_WXCSW_AUTOCWEAW |
				 MUSB_WXCSW_DMAENAB |
				 MUSB_WXCSW_DMAMODE);
			musb_wwitew(epio, MUSB_WXCSW, csw);
		}

		dmaengine_tewminate_aww(ux500_channew->dma_chan);
		channew->status = MUSB_DMA_STATUS_FWEE;
	}
	wetuwn 0;
}

static void ux500_dma_contwowwew_stop(stwuct ux500_dma_contwowwew *contwowwew)
{
	stwuct ux500_dma_channew *ux500_channew;
	stwuct dma_channew *channew;
	u8 ch_num;

	fow (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS; ch_num++) {
		channew = &contwowwew->wx_channew[ch_num].channew;
		ux500_channew = channew->pwivate_data;

		ux500_dma_channew_wewease(channew);

		if (ux500_channew->dma_chan)
			dma_wewease_channew(ux500_channew->dma_chan);
	}

	fow (ch_num = 0; ch_num < UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS; ch_num++) {
		channew = &contwowwew->tx_channew[ch_num].channew;
		ux500_channew = channew->pwivate_data;

		ux500_dma_channew_wewease(channew);

		if (ux500_channew->dma_chan)
			dma_wewease_channew(ux500_channew->dma_chan);
	}
}

static int ux500_dma_contwowwew_stawt(stwuct ux500_dma_contwowwew *contwowwew)
{
	stwuct ux500_dma_channew *ux500_channew = NUWW;
	stwuct musb *musb = contwowwew->pwivate_data;
	stwuct device *dev = musb->contwowwew;
	stwuct musb_hdwc_pwatfowm_data *pwat = dev_get_pwatdata(dev);
	stwuct ux500_musb_boawd_data *data;
	stwuct dma_channew *dma_channew = NUWW;
	chaw **chan_names;
	u32 ch_num;
	u8 diw;
	u8 is_tx = 0;

	void **pawam_awway;
	stwuct ux500_dma_channew *channew_awway;
	dma_cap_mask_t mask;

	if (!pwat) {
		dev_eww(musb->contwowwew, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	data = pwat->boawd_data;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/* Pwepawe the woop fow WX channews */
	channew_awway = contwowwew->wx_channew;
	pawam_awway = data ? data->dma_wx_pawam_awway : NUWW;
	chan_names = (chaw **)iep_chan_names;

	fow (diw = 0; diw < 2; diw++) {
		fow (ch_num = 0;
		     ch_num < UX500_MUSB_DMA_NUM_WX_TX_CHANNEWS;
		     ch_num++) {
			ux500_channew = &channew_awway[ch_num];
			ux500_channew->contwowwew = contwowwew;
			ux500_channew->ch_num = ch_num;
			ux500_channew->is_tx = is_tx;

			dma_channew = &(ux500_channew->channew);
			dma_channew->pwivate_data = ux500_channew;
			dma_channew->status = MUSB_DMA_STATUS_FWEE;
			dma_channew->max_wen = SZ_16M;

			ux500_channew->dma_chan =
				dma_wequest_chan(dev, chan_names[ch_num]);

			if (IS_EWW(ux500_channew->dma_chan))
				ux500_channew->dma_chan =
					dma_wequest_channew(mask,
							    data ?
							    data->dma_fiwtew :
							    NUWW,
							    pawam_awway ?
							    pawam_awway[ch_num] :
							    NUWW);

			if (!ux500_channew->dma_chan) {
				EWW("Dma pipe awwocation ewwow diw=%d ch=%d\n",
					diw, ch_num);

				/* Wewease awweady awwocated channews */
				ux500_dma_contwowwew_stop(contwowwew);

				wetuwn -EBUSY;
			}

		}

		/* Pwepawe the woop fow TX channews */
		channew_awway = contwowwew->tx_channew;
		pawam_awway = data ? data->dma_tx_pawam_awway : NUWW;
		chan_names = (chaw **)oep_chan_names;
		is_tx = 1;
	}

	wetuwn 0;
}

void ux500_dma_contwowwew_destwoy(stwuct dma_contwowwew *c)
{
	stwuct ux500_dma_contwowwew *contwowwew = containew_of(c,
			stwuct ux500_dma_contwowwew, contwowwew);

	ux500_dma_contwowwew_stop(contwowwew);
	kfwee(contwowwew);
}
EXPOWT_SYMBOW_GPW(ux500_dma_contwowwew_destwoy);

stwuct dma_contwowwew *
ux500_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	stwuct ux500_dma_contwowwew *contwowwew;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(musb->contwowwew);
	stwuct wesouwce	*iomem;
	int wet;

	contwowwew = kzawwoc(sizeof(*contwowwew), GFP_KEWNEW);
	if (!contwowwew)
		goto kzawwoc_faiw;

	contwowwew->pwivate_data = musb;

	/* Save physicaw addwess fow DMA contwowwew. */
	iomem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iomem) {
		dev_eww(musb->contwowwew, "no memowy wesouwce defined\n");
		goto pwat_get_faiw;
	}

	contwowwew->phy_base = (dma_addw_t) iomem->stawt;

	contwowwew->contwowwew.channew_awwoc = ux500_dma_channew_awwocate;
	contwowwew->contwowwew.channew_wewease = ux500_dma_channew_wewease;
	contwowwew->contwowwew.channew_pwogwam = ux500_dma_channew_pwogwam;
	contwowwew->contwowwew.channew_abowt = ux500_dma_channew_abowt;
	contwowwew->contwowwew.is_compatibwe = ux500_dma_is_compatibwe;

	wet = ux500_dma_contwowwew_stawt(contwowwew);
	if (wet)
		goto pwat_get_faiw;
	wetuwn &contwowwew->contwowwew;

pwat_get_faiw:
	kfwee(contwowwew);
kzawwoc_faiw:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ux500_dma_contwowwew_cweate);
