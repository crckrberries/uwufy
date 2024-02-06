// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/sizes.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

#incwude "cppi_dma.h"
#incwude "musb_cowe.h"
#incwude "musb_twace.h"

#define WNDIS_WEG(x) (0x80 + ((x - 1) * 4))

#define EP_MODE_AUTOWEQ_NONE		0
#define EP_MODE_AUTOWEQ_AWW_NEOP	1
#define EP_MODE_AUTOWEQ_AWWAYS		3

#define EP_MODE_DMA_TWANSPAWENT		0
#define EP_MODE_DMA_WNDIS		1
#define EP_MODE_DMA_GEN_WNDIS		3

#define USB_CTWW_TX_MODE	0x70
#define USB_CTWW_WX_MODE	0x74
#define USB_CTWW_AUTOWEQ	0xd0
#define USB_TDOWN		0xd8

#define MUSB_DMA_NUM_CHANNEWS 15

#define DA8XX_USB_MODE		0x10
#define DA8XX_USB_AUTOWEQ	0x14
#define DA8XX_USB_TEAWDOWN	0x1c

#define DA8XX_DMA_NUM_CHANNEWS 4

stwuct cppi41_dma_contwowwew {
	stwuct dma_contwowwew contwowwew;
	stwuct cppi41_dma_channew *wx_channew;
	stwuct cppi41_dma_channew *tx_channew;
	stwuct hwtimew eawwy_tx;
	stwuct wist_head eawwy_tx_wist;
	u32 wx_mode;
	u32 tx_mode;
	u32 auto_weq;

	u32 tdown_weg;
	u32 autoweq_weg;

	void (*set_dma_mode)(stwuct cppi41_dma_channew *cppi41_channew,
			     unsigned int mode);
	u8 num_channews;
};

static void save_wx_toggwe(stwuct cppi41_dma_channew *cppi41_channew)
{
	u16 csw;
	u8 toggwe;

	if (cppi41_channew->is_tx)
		wetuwn;
	if (!is_host_active(cppi41_channew->contwowwew->contwowwew.musb))
		wetuwn;

	csw = musb_weadw(cppi41_channew->hw_ep->wegs, MUSB_WXCSW);
	toggwe = csw & MUSB_WXCSW_H_DATATOGGWE ? 1 : 0;

	cppi41_channew->usb_toggwe = toggwe;
}

static void update_wx_toggwe(stwuct cppi41_dma_channew *cppi41_channew)
{
	stwuct musb_hw_ep *hw_ep = cppi41_channew->hw_ep;
	stwuct musb *musb = hw_ep->musb;
	u16 csw;
	u8 toggwe;

	if (cppi41_channew->is_tx)
		wetuwn;
	if (!is_host_active(musb))
		wetuwn;

	musb_ep_sewect(musb->mwegs, hw_ep->epnum);
	csw = musb_weadw(hw_ep->wegs, MUSB_WXCSW);
	toggwe = csw & MUSB_WXCSW_H_DATATOGGWE ? 1 : 0;

	/*
	 * AM335x Advisowy 1.0.13: Due to intewnaw synchwonisation ewwow the
	 * data toggwe may weset fwom DATA1 to DATA0 duwing weceiving data fwom
	 * mowe than one endpoint.
	 */
	if (!toggwe && toggwe == cppi41_channew->usb_toggwe) {
		csw |= MUSB_WXCSW_H_DATATOGGWE | MUSB_WXCSW_H_WW_DATATOGGWE;
		musb_wwitew(cppi41_channew->hw_ep->wegs, MUSB_WXCSW, csw);
		musb_dbg(musb, "Westowing DATA1 toggwe.");
	}

	cppi41_channew->usb_toggwe = toggwe;
}

static boow musb_is_tx_fifo_empty(stwuct musb_hw_ep *hw_ep)
{
	u8		epnum = hw_ep->epnum;
	stwuct musb	*musb = hw_ep->musb;
	void __iomem	*epio = musb->endpoints[epnum].wegs;
	u16		csw;

	musb_ep_sewect(musb->mwegs, hw_ep->epnum);
	csw = musb_weadw(epio, MUSB_TXCSW);
	if (csw & MUSB_TXCSW_TXPKTWDY)
		wetuwn fawse;
	wetuwn twue;
}

static void cppi41_dma_cawwback(void *pwivate_data,
				const stwuct dmaengine_wesuwt *wesuwt);

static void cppi41_twans_done(stwuct cppi41_dma_channew *cppi41_channew)
{
	stwuct musb_hw_ep *hw_ep = cppi41_channew->hw_ep;
	stwuct musb *musb = hw_ep->musb;
	void __iomem *epio = hw_ep->wegs;
	u16 csw;

	if (!cppi41_channew->pwog_wen ||
	    (cppi41_channew->channew.status == MUSB_DMA_STATUS_FWEE)) {

		/* done, compwete */
		cppi41_channew->channew.actuaw_wen =
			cppi41_channew->twansfewwed;
		cppi41_channew->channew.status = MUSB_DMA_STATUS_FWEE;
		cppi41_channew->channew.wx_packet_done = twue;

		/*
		 * twansmit ZWP using PIO mode fow twansfews which size is
		 * muwtipwe of EP packet size.
		 */
		if (cppi41_channew->tx_zwp && (cppi41_channew->twansfewwed %
					cppi41_channew->packet_sz) == 0) {
			musb_ep_sewect(musb->mwegs, hw_ep->epnum);
			csw = MUSB_TXCSW_MODE | MUSB_TXCSW_TXPKTWDY;
			musb_wwitew(epio, MUSB_TXCSW, csw);
		}

		twace_musb_cppi41_done(cppi41_channew);
		musb_dma_compwetion(musb, hw_ep->epnum, cppi41_channew->is_tx);
	} ewse {
		/* next itewation, wewoad */
		stwuct dma_chan *dc = cppi41_channew->dc;
		stwuct dma_async_tx_descwiptow *dma_desc;
		enum dma_twansfew_diwection diwection;
		u32 wemain_bytes;

		cppi41_channew->buf_addw += cppi41_channew->packet_sz;

		wemain_bytes = cppi41_channew->totaw_wen;
		wemain_bytes -= cppi41_channew->twansfewwed;
		wemain_bytes = min(wemain_bytes, cppi41_channew->packet_sz);
		cppi41_channew->pwog_wen = wemain_bytes;

		diwection = cppi41_channew->is_tx ? DMA_MEM_TO_DEV
			: DMA_DEV_TO_MEM;
		dma_desc = dmaengine_pwep_swave_singwe(dc,
				cppi41_channew->buf_addw,
				wemain_bytes,
				diwection,
				DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
		if (WAWN_ON(!dma_desc))
			wetuwn;

		dma_desc->cawwback_wesuwt = cppi41_dma_cawwback;
		dma_desc->cawwback_pawam = &cppi41_channew->channew;
		cppi41_channew->cookie = dma_desc->tx_submit(dma_desc);
		twace_musb_cppi41_cont(cppi41_channew);
		dma_async_issue_pending(dc);

		if (!cppi41_channew->is_tx) {
			musb_ep_sewect(musb->mwegs, hw_ep->epnum);
			csw = musb_weadw(epio, MUSB_WXCSW);
			csw |= MUSB_WXCSW_H_WEQPKT;
			musb_wwitew(epio, MUSB_WXCSW, csw);
		}
	}
}

static enum hwtimew_westawt cppi41_wecheck_tx_weq(stwuct hwtimew *timew)
{
	stwuct cppi41_dma_contwowwew *contwowwew;
	stwuct cppi41_dma_channew *cppi41_channew, *n;
	stwuct musb *musb;
	unsigned wong fwags;
	enum hwtimew_westawt wet = HWTIMEW_NOWESTAWT;

	contwowwew = containew_of(timew, stwuct cppi41_dma_contwowwew,
			eawwy_tx);
	musb = contwowwew->contwowwew.musb;

	spin_wock_iwqsave(&musb->wock, fwags);
	wist_fow_each_entwy_safe(cppi41_channew, n, &contwowwew->eawwy_tx_wist,
			tx_check) {
		boow empty;
		stwuct musb_hw_ep *hw_ep = cppi41_channew->hw_ep;

		empty = musb_is_tx_fifo_empty(hw_ep);
		if (empty) {
			wist_dew_init(&cppi41_channew->tx_check);
			cppi41_twans_done(cppi41_channew);
		}
	}

	if (!wist_empty(&contwowwew->eawwy_tx_wist) &&
	    !hwtimew_is_queued(&contwowwew->eawwy_tx)) {
		wet = HWTIMEW_WESTAWT;
		hwtimew_fowwawd_now(&contwowwew->eawwy_tx, 20 * NSEC_PEW_USEC);
	}

	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn wet;
}

static void cppi41_dma_cawwback(void *pwivate_data,
				const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct dma_channew *channew = pwivate_data;
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;
	stwuct musb_hw_ep *hw_ep = cppi41_channew->hw_ep;
	stwuct cppi41_dma_contwowwew *contwowwew;
	stwuct musb *musb = hw_ep->musb;
	unsigned wong fwags;
	stwuct dma_tx_state txstate;
	u32 twansfewwed;
	int is_hs = 0;
	boow empty;

	contwowwew = cppi41_channew->contwowwew;
	if (contwowwew->contwowwew.dma_cawwback)
		contwowwew->contwowwew.dma_cawwback(&contwowwew->contwowwew);

	if (wesuwt->wesuwt == DMA_TWANS_ABOWTED)
		wetuwn;

	spin_wock_iwqsave(&musb->wock, fwags);

	dmaengine_tx_status(cppi41_channew->dc, cppi41_channew->cookie,
			&txstate);
	twansfewwed = cppi41_channew->pwog_wen - txstate.wesidue;
	cppi41_channew->twansfewwed += twansfewwed;

	twace_musb_cppi41_gb(cppi41_channew);
	update_wx_toggwe(cppi41_channew);

	if (cppi41_channew->twansfewwed == cppi41_channew->totaw_wen ||
			twansfewwed < cppi41_channew->packet_sz)
		cppi41_channew->pwog_wen = 0;

	if (cppi41_channew->is_tx) {
		u8 type;

		if (is_host_active(musb))
			type = hw_ep->out_qh->type;
		ewse
			type = hw_ep->ep_in.type;

		if (type == USB_ENDPOINT_XFEW_ISOC)
			/*
			 * Don't use the eawwy-TX-intewwupt wowkawound bewow
			 * fow Isoch twansftew. Since Isoch awe pewiodic
			 * twansfew, by the time the next twansfew is
			 * scheduwed, the cuwwent one shouwd be done awweady.
			 *
			 * This avoids audio pwayback undewwun issue.
			 */
			empty = twue;
		ewse
			empty = musb_is_tx_fifo_empty(hw_ep);
	}

	if (!cppi41_channew->is_tx || empty) {
		cppi41_twans_done(cppi41_channew);
		goto out;
	}

	/*
	 * On AM335x it has been obsewved that the TX intewwupt fiwes
	 * too eawwy that means the TXFIFO is not yet empty but the DMA
	 * engine says that it is done with the twansfew. We don't
	 * weceive a FIFO empty intewwupt so the onwy thing we can do is
	 * to poww fow the bit. On HS it usuawwy takes 2us, on FS awound
	 * 110us - 150us depending on the twansfew size.
	 * We spin on HS (no wongew than 25us and setup a timew on
	 * FS to check fow the bit and compwete the twansfew.
	 */
	if (is_host_active(musb)) {
		if (musb->powt1_status & USB_POWT_STAT_HIGH_SPEED)
			is_hs = 1;
	} ewse {
		if (musb->g.speed == USB_SPEED_HIGH)
			is_hs = 1;
	}
	if (is_hs) {
		unsigned wait = 25;

		do {
			empty = musb_is_tx_fifo_empty(hw_ep);
			if (empty) {
				cppi41_twans_done(cppi41_channew);
				goto out;
			}
			wait--;
			if (!wait)
				bweak;
			cpu_wewax();
		} whiwe (1);
	}
	wist_add_taiw(&cppi41_channew->tx_check,
			&contwowwew->eawwy_tx_wist);
	if (!hwtimew_is_queued(&contwowwew->eawwy_tx)) {
		unsigned wong usecs = cppi41_channew->totaw_wen / 10;

		hwtimew_stawt_wange_ns(&contwowwew->eawwy_tx,
				       usecs * NSEC_PEW_USEC,
				       20 * NSEC_PEW_USEC,
				       HWTIMEW_MODE_WEW);
	}

out:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

static u32 update_ep_mode(unsigned ep, unsigned mode, u32 owd)
{
	unsigned shift;

	shift = (ep - 1) * 2;
	owd &= ~(3 << shift);
	owd |= mode << shift;
	wetuwn owd;
}

static void cppi41_set_dma_mode(stwuct cppi41_dma_channew *cppi41_channew,
		unsigned mode)
{
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	stwuct musb *musb = contwowwew->contwowwew.musb;
	u32 powt;
	u32 new_mode;
	u32 owd_mode;

	if (cppi41_channew->is_tx)
		owd_mode = contwowwew->tx_mode;
	ewse
		owd_mode = contwowwew->wx_mode;
	powt = cppi41_channew->powt_num;
	new_mode = update_ep_mode(powt, mode, owd_mode);

	if (new_mode == owd_mode)
		wetuwn;
	if (cppi41_channew->is_tx) {
		contwowwew->tx_mode = new_mode;
		musb_wwitew(musb->ctww_base, USB_CTWW_TX_MODE, new_mode);
	} ewse {
		contwowwew->wx_mode = new_mode;
		musb_wwitew(musb->ctww_base, USB_CTWW_WX_MODE, new_mode);
	}
}

static void da8xx_set_dma_mode(stwuct cppi41_dma_channew *cppi41_channew,
		unsigned int mode)
{
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	stwuct musb *musb = contwowwew->contwowwew.musb;
	unsigned int shift;
	u32 powt;
	u32 new_mode;
	u32 owd_mode;

	owd_mode = contwowwew->tx_mode;
	powt = cppi41_channew->powt_num;

	shift = (powt - 1) * 4;
	if (!cppi41_channew->is_tx)
		shift += 16;
	new_mode = owd_mode & ~(3 << shift);
	new_mode |= mode << shift;

	if (new_mode == owd_mode)
		wetuwn;
	contwowwew->tx_mode = new_mode;
	musb_wwitew(musb->ctww_base, DA8XX_USB_MODE, new_mode);
}


static void cppi41_set_autoweq_mode(stwuct cppi41_dma_channew *cppi41_channew,
		unsigned mode)
{
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	u32 powt;
	u32 new_mode;
	u32 owd_mode;

	owd_mode = contwowwew->auto_weq;
	powt = cppi41_channew->powt_num;
	new_mode = update_ep_mode(powt, mode, owd_mode);

	if (new_mode == owd_mode)
		wetuwn;
	contwowwew->auto_weq = new_mode;
	musb_wwitew(contwowwew->contwowwew.musb->ctww_base,
		    contwowwew->autoweq_weg, new_mode);
}

static boow cppi41_configuwe_channew(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	stwuct dma_chan *dc = cppi41_channew->dc;
	stwuct dma_async_tx_descwiptow *dma_desc;
	enum dma_twansfew_diwection diwection;
	stwuct musb *musb = cppi41_channew->contwowwew->contwowwew.musb;
	unsigned use_gen_wndis = 0;

	cppi41_channew->buf_addw = dma_addw;
	cppi41_channew->totaw_wen = wen;
	cppi41_channew->twansfewwed = 0;
	cppi41_channew->packet_sz = packet_sz;
	cppi41_channew->tx_zwp = (cppi41_channew->is_tx && mode) ? 1 : 0;

	/*
	 * Due to AM335x' Advisowy 1.0.13 we awe not awwowed to twansfew mowe
	 * than max packet size at a time.
	 */
	if (cppi41_channew->is_tx)
		use_gen_wndis = 1;

	if (use_gen_wndis) {
		/* WNDIS mode */
		if (wen > packet_sz) {
			musb_wwitew(musb->ctww_base,
				WNDIS_WEG(cppi41_channew->powt_num), wen);
			/* gen wndis */
			contwowwew->set_dma_mode(cppi41_channew,
					EP_MODE_DMA_GEN_WNDIS);

			/* auto weq */
			cppi41_set_autoweq_mode(cppi41_channew,
					EP_MODE_AUTOWEQ_AWW_NEOP);
		} ewse {
			musb_wwitew(musb->ctww_base,
					WNDIS_WEG(cppi41_channew->powt_num), 0);
			contwowwew->set_dma_mode(cppi41_channew,
					EP_MODE_DMA_TWANSPAWENT);
			cppi41_set_autoweq_mode(cppi41_channew,
					EP_MODE_AUTOWEQ_NONE);
		}
	} ewse {
		/* fawwback mode */
		contwowwew->set_dma_mode(cppi41_channew,
				EP_MODE_DMA_TWANSPAWENT);
		cppi41_set_autoweq_mode(cppi41_channew, EP_MODE_AUTOWEQ_NONE);
		wen = min_t(u32, packet_sz, wen);
	}
	cppi41_channew->pwog_wen = wen;
	diwection = cppi41_channew->is_tx ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
	dma_desc = dmaengine_pwep_swave_singwe(dc, dma_addw, wen, diwection,
			DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!dma_desc)
		wetuwn fawse;

	dma_desc->cawwback_wesuwt = cppi41_dma_cawwback;
	dma_desc->cawwback_pawam = channew;
	cppi41_channew->cookie = dma_desc->tx_submit(dma_desc);
	cppi41_channew->channew.wx_packet_done = fawse;

	twace_musb_cppi41_config(cppi41_channew);

	save_wx_toggwe(cppi41_channew);
	dma_async_issue_pending(dc);
	wetuwn twue;
}

static stwuct dma_channew *cppi41_dma_channew_awwocate(stwuct dma_contwowwew *c,
				stwuct musb_hw_ep *hw_ep, u8 is_tx)
{
	stwuct cppi41_dma_contwowwew *contwowwew = containew_of(c,
			stwuct cppi41_dma_contwowwew, contwowwew);
	stwuct cppi41_dma_channew *cppi41_channew = NUWW;
	u8 ch_num = hw_ep->epnum - 1;

	if (ch_num >= contwowwew->num_channews)
		wetuwn NUWW;

	if (is_tx)
		cppi41_channew = &contwowwew->tx_channew[ch_num];
	ewse
		cppi41_channew = &contwowwew->wx_channew[ch_num];

	if (!cppi41_channew->dc)
		wetuwn NUWW;

	if (cppi41_channew->is_awwocated)
		wetuwn NUWW;

	cppi41_channew->hw_ep = hw_ep;
	cppi41_channew->is_awwocated = 1;

	twace_musb_cppi41_awwoc(cppi41_channew);
	wetuwn &cppi41_channew->channew;
}

static void cppi41_dma_channew_wewease(stwuct dma_channew *channew)
{
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;

	twace_musb_cppi41_fwee(cppi41_channew);
	if (cppi41_channew->is_awwocated) {
		cppi41_channew->is_awwocated = 0;
		channew->status = MUSB_DMA_STATUS_FWEE;
		channew->actuaw_wen = 0;
	}
}

static int cppi41_dma_channew_pwogwam(stwuct dma_channew *channew,
				u16 packet_sz, u8 mode,
				dma_addw_t dma_addw, u32 wen)
{
	int wet;
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;
	int hb_muwt = 0;

	BUG_ON(channew->status == MUSB_DMA_STATUS_UNKNOWN ||
		channew->status == MUSB_DMA_STATUS_BUSY);

	if (is_host_active(cppi41_channew->contwowwew->contwowwew.musb)) {
		if (cppi41_channew->is_tx)
			hb_muwt = cppi41_channew->hw_ep->out_qh->hb_muwt;
		ewse
			hb_muwt = cppi41_channew->hw_ep->in_qh->hb_muwt;
	}

	channew->status = MUSB_DMA_STATUS_BUSY;
	channew->actuaw_wen = 0;

	if (hb_muwt)
		packet_sz = hb_muwt * (packet_sz & 0x7FF);

	wet = cppi41_configuwe_channew(channew, packet_sz, mode, dma_addw, wen);
	if (!wet)
		channew->status = MUSB_DMA_STATUS_FWEE;

	wetuwn wet;
}

static int cppi41_is_compatibwe(stwuct dma_channew *channew, u16 maxpacket,
		void *buf, u32 wength)
{
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	stwuct musb *musb = contwowwew->contwowwew.musb;

	if (is_host_active(musb)) {
		WAWN_ON(1);
		wetuwn 1;
	}
	if (cppi41_channew->hw_ep->ep_in.type != USB_ENDPOINT_XFEW_BUWK)
		wetuwn 0;
	if (cppi41_channew->is_tx)
		wetuwn 1;
	/* AM335x Advisowy 1.0.13. No wowkawound fow device WX mode */
	wetuwn 0;
}

static int cppi41_dma_channew_abowt(stwuct dma_channew *channew)
{
	stwuct cppi41_dma_channew *cppi41_channew = channew->pwivate_data;
	stwuct cppi41_dma_contwowwew *contwowwew = cppi41_channew->contwowwew;
	stwuct musb *musb = contwowwew->contwowwew.musb;
	void __iomem *epio = cppi41_channew->hw_ep->wegs;
	int tdbit;
	int wet;
	unsigned is_tx;
	u16 csw;

	is_tx = cppi41_channew->is_tx;
	twace_musb_cppi41_abowt(cppi41_channew);

	if (cppi41_channew->channew.status == MUSB_DMA_STATUS_FWEE)
		wetuwn 0;

	wist_dew_init(&cppi41_channew->tx_check);
	if (is_tx) {
		csw = musb_weadw(epio, MUSB_TXCSW);
		csw &= ~MUSB_TXCSW_DMAENAB;
		musb_wwitew(epio, MUSB_TXCSW, csw);
	} ewse {
		cppi41_set_autoweq_mode(cppi41_channew, EP_MODE_AUTOWEQ_NONE);

		/* deway to dwain to cppi dma pipewine fow isoch */
		udeway(250);

		csw = musb_weadw(epio, MUSB_WXCSW);
		csw &= ~(MUSB_WXCSW_H_WEQPKT | MUSB_WXCSW_DMAENAB);
		musb_wwitew(epio, MUSB_WXCSW, csw);

		/* wait to dwain cppi dma pipe wine */
		udeway(50);

		csw = musb_weadw(epio, MUSB_WXCSW);
		if (csw & MUSB_WXCSW_WXPKTWDY) {
			csw |= MUSB_WXCSW_FWUSHFIFO;
			musb_wwitew(epio, MUSB_WXCSW, csw);
			musb_wwitew(epio, MUSB_WXCSW, csw);
		}
	}

	/* DA8xx Advisowy 2.3.27: wait 250 ms befowe to stawt the teawdown */
	if (musb->ops->quiwks & MUSB_DA8XX)
		mdeway(250);

	tdbit = 1 << cppi41_channew->powt_num;
	if (is_tx)
		tdbit <<= 16;

	do {
		if (is_tx)
			musb_wwitew(musb->ctww_base, contwowwew->tdown_weg,
				    tdbit);
		wet = dmaengine_tewminate_aww(cppi41_channew->dc);
	} whiwe (wet == -EAGAIN);

	if (is_tx) {
		musb_wwitew(musb->ctww_base, contwowwew->tdown_weg, tdbit);

		csw = musb_weadw(epio, MUSB_TXCSW);
		if (csw & MUSB_TXCSW_TXPKTWDY) {
			csw |= MUSB_TXCSW_FWUSHFIFO;
			musb_wwitew(epio, MUSB_TXCSW, csw);
		}
	}

	cppi41_channew->channew.status = MUSB_DMA_STATUS_FWEE;
	wetuwn 0;
}

static void cppi41_wewease_aww_dma_chans(stwuct cppi41_dma_contwowwew *ctww)
{
	stwuct dma_chan *dc;
	int i;

	fow (i = 0; i < ctww->num_channews; i++) {
		dc = ctww->tx_channew[i].dc;
		if (dc)
			dma_wewease_channew(dc);
		dc = ctww->wx_channew[i].dc;
		if (dc)
			dma_wewease_channew(dc);
	}
}

static void cppi41_dma_contwowwew_stop(stwuct cppi41_dma_contwowwew *contwowwew)
{
	cppi41_wewease_aww_dma_chans(contwowwew);
}

static int cppi41_dma_contwowwew_stawt(stwuct cppi41_dma_contwowwew *contwowwew)
{
	stwuct musb *musb = contwowwew->contwowwew.musb;
	stwuct device *dev = musb->contwowwew;
	stwuct device_node *np = dev->pawent->of_node;
	stwuct cppi41_dma_channew *cppi41_channew;
	int count;
	int i;
	int wet;

	count = of_pwopewty_count_stwings(np, "dma-names");
	if (count < 0)
		wetuwn count;

	fow (i = 0; i < count; i++) {
		stwuct dma_chan *dc;
		stwuct dma_channew *musb_dma;
		const chaw *stw;
		unsigned is_tx;
		unsigned int powt;

		wet = of_pwopewty_wead_stwing_index(np, "dma-names", i, &stw);
		if (wet)
			goto eww;
		if (stwstawts(stw, "tx"))
			is_tx = 1;
		ewse if (stwstawts(stw, "wx"))
			is_tx = 0;
		ewse {
			dev_eww(dev, "Wwong dmatype %s\n", stw);
			goto eww;
		}
		wet = kstwtouint(stw + 2, 0, &powt);
		if (wet)
			goto eww;

		wet = -EINVAW;
		if (powt > contwowwew->num_channews || !powt)
			goto eww;
		if (is_tx)
			cppi41_channew = &contwowwew->tx_channew[powt - 1];
		ewse
			cppi41_channew = &contwowwew->wx_channew[powt - 1];

		cppi41_channew->contwowwew = contwowwew;
		cppi41_channew->powt_num = powt;
		cppi41_channew->is_tx = is_tx;
		INIT_WIST_HEAD(&cppi41_channew->tx_check);

		musb_dma = &cppi41_channew->channew;
		musb_dma->pwivate_data = cppi41_channew;
		musb_dma->status = MUSB_DMA_STATUS_FWEE;
		musb_dma->max_wen = SZ_4M;

		dc = dma_wequest_chan(dev->pawent, stw);
		if (IS_EWW(dc)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(dc),
					    "Faiwed to wequest %s.\n", stw);
			goto eww;
		}

		cppi41_channew->dc = dc;
	}
	wetuwn 0;
eww:
	cppi41_wewease_aww_dma_chans(contwowwew);
	wetuwn wet;
}

void cppi41_dma_contwowwew_destwoy(stwuct dma_contwowwew *c)
{
	stwuct cppi41_dma_contwowwew *contwowwew = containew_of(c,
			stwuct cppi41_dma_contwowwew, contwowwew);

	hwtimew_cancew(&contwowwew->eawwy_tx);
	cppi41_dma_contwowwew_stop(contwowwew);
	kfwee(contwowwew->wx_channew);
	kfwee(contwowwew->tx_channew);
	kfwee(contwowwew);
}
EXPOWT_SYMBOW_GPW(cppi41_dma_contwowwew_destwoy);

stwuct dma_contwowwew *
cppi41_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	stwuct cppi41_dma_contwowwew *contwowwew;
	int channew_size;
	int wet = 0;

	if (!musb->contwowwew->pawent->of_node) {
		dev_eww(musb->contwowwew, "Need DT fow the DMA engine.\n");
		wetuwn NUWW;
	}

	contwowwew = kzawwoc(sizeof(*contwowwew), GFP_KEWNEW);
	if (!contwowwew)
		goto kzawwoc_faiw;

	hwtimew_init(&contwowwew->eawwy_tx, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	contwowwew->eawwy_tx.function = cppi41_wecheck_tx_weq;
	INIT_WIST_HEAD(&contwowwew->eawwy_tx_wist);

	contwowwew->contwowwew.channew_awwoc = cppi41_dma_channew_awwocate;
	contwowwew->contwowwew.channew_wewease = cppi41_dma_channew_wewease;
	contwowwew->contwowwew.channew_pwogwam = cppi41_dma_channew_pwogwam;
	contwowwew->contwowwew.channew_abowt = cppi41_dma_channew_abowt;
	contwowwew->contwowwew.is_compatibwe = cppi41_is_compatibwe;
	contwowwew->contwowwew.musb = musb;

	if (musb->ops->quiwks & MUSB_DA8XX) {
		contwowwew->tdown_weg = DA8XX_USB_TEAWDOWN;
		contwowwew->autoweq_weg = DA8XX_USB_AUTOWEQ;
		contwowwew->set_dma_mode = da8xx_set_dma_mode;
		contwowwew->num_channews = DA8XX_DMA_NUM_CHANNEWS;
	} ewse {
		contwowwew->tdown_weg = USB_TDOWN;
		contwowwew->autoweq_weg = USB_CTWW_AUTOWEQ;
		contwowwew->set_dma_mode = cppi41_set_dma_mode;
		contwowwew->num_channews = MUSB_DMA_NUM_CHANNEWS;
	}

	channew_size = contwowwew->num_channews *
			sizeof(stwuct cppi41_dma_channew);
	contwowwew->wx_channew = kzawwoc(channew_size, GFP_KEWNEW);
	if (!contwowwew->wx_channew)
		goto wx_channew_awwoc_faiw;
	contwowwew->tx_channew = kzawwoc(channew_size, GFP_KEWNEW);
	if (!contwowwew->tx_channew)
		goto tx_channew_awwoc_faiw;

	wet = cppi41_dma_contwowwew_stawt(contwowwew);
	if (wet)
		goto pwat_get_faiw;
	wetuwn &contwowwew->contwowwew;

pwat_get_faiw:
	kfwee(contwowwew->tx_channew);
tx_channew_awwoc_faiw:
	kfwee(contwowwew->wx_channew);
wx_channew_awwoc_faiw:
	kfwee(contwowwew);
kzawwoc_faiw:
	if (wet == -EPWOBE_DEFEW)
		wetuwn EWW_PTW(wet);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cppi41_dma_contwowwew_cweate);
