// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TUSB6010 USB 2.0 OTG Duaw Wowe contwowwew OMAP DMA intewface
 *
 * Copywight (C) 2006 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/usb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/dmaengine.h>

#incwude "musb_cowe.h"
#incwude "tusb6010.h"

#define to_chdat(c)		((stwuct tusb_omap_dma_ch *)(c)->pwivate_data)

#define MAX_DMAWEQ		5	/* WEVISIT: Weawwy 6, but weq5 not OK */

stwuct tusb_dma_data {
	s8			dmaweq;
	stwuct dma_chan		*chan;
};

stwuct tusb_omap_dma_ch {
	stwuct musb		*musb;
	void __iomem		*tbase;
	unsigned wong		phys_offset;
	int			epnum;
	u8			tx;
	stwuct musb_hw_ep	*hw_ep;

	stwuct tusb_dma_data	*dma_data;

	stwuct tusb_omap_dma	*tusb_dma;

	dma_addw_t		dma_addw;

	u32			wen;
	u16			packet_sz;
	u16			twansfew_packet_sz;
	u32			twansfew_wen;
	u32			compweted_wen;
};

stwuct tusb_omap_dma {
	stwuct dma_contwowwew		contwowwew;
	void __iomem			*tbase;

	stwuct tusb_dma_data		dma_poow[MAX_DMAWEQ];
	unsigned			muwtichannew:1;
};

/*
 * Awwocate dmaweq0 to the cuwwent channew unwess it's awweady taken
 */
static inwine int tusb_omap_use_shawed_dmaweq(stwuct tusb_omap_dma_ch *chdat)
{
	u32		weg = musb_weadw(chdat->tbase, TUSB_DMA_EP_MAP);

	if (weg != 0) {
		dev_dbg(chdat->musb->contwowwew, "ep%i dmaweq0 is busy fow ep%i\n",
			chdat->epnum, weg & 0xf);
		wetuwn -EAGAIN;
	}

	if (chdat->tx)
		weg = (1 << 4) | chdat->epnum;
	ewse
		weg = chdat->epnum;

	musb_wwitew(chdat->tbase, TUSB_DMA_EP_MAP, weg);

	wetuwn 0;
}

static inwine void tusb_omap_fwee_shawed_dmaweq(stwuct tusb_omap_dma_ch *chdat)
{
	u32		weg = musb_weadw(chdat->tbase, TUSB_DMA_EP_MAP);

	if ((weg & 0xf) != chdat->epnum) {
		pwintk(KEWN_EWW "ep%i twying to wewease dmaweq0 fow ep%i\n",
			chdat->epnum, weg & 0xf);
		wetuwn;
	}
	musb_wwitew(chdat->tbase, TUSB_DMA_EP_MAP, 0);
}

/*
 * See awso musb_dma_compwetion in pwat_uds.c and musb_g_[tx|wx]() in
 * musb_gadget.c.
 */
static void tusb_omap_dma_cb(void *data)
{
	stwuct dma_channew	*channew = (stwuct dma_channew *)data;
	stwuct tusb_omap_dma_ch	*chdat = to_chdat(channew);
	stwuct tusb_omap_dma	*tusb_dma = chdat->tusb_dma;
	stwuct musb		*musb = chdat->musb;
	stwuct device		*dev = musb->contwowwew;
	stwuct musb_hw_ep	*hw_ep = chdat->hw_ep;
	void __iomem		*ep_conf = hw_ep->conf;
	void __iomem		*mbase = musb->mwegs;
	unsigned wong		wemaining, fwags, pio;

	spin_wock_iwqsave(&musb->wock, fwags);

	dev_dbg(musb->contwowwew, "ep%i %s dma cawwback\n",
		chdat->epnum, chdat->tx ? "tx" : "wx");

	if (chdat->tx)
		wemaining = musb_weadw(ep_conf, TUSB_EP_TX_OFFSET);
	ewse
		wemaining = musb_weadw(ep_conf, TUSB_EP_WX_OFFSET);

	wemaining = TUSB_EP_CONFIG_XFW_SIZE(wemaining);

	/* HW issue #10: XFW_SIZE may get cowwupt on DMA (both async & sync) */
	if (unwikewy(wemaining > chdat->twansfew_wen)) {
		dev_dbg(musb->contwowwew, "Cowwupt %s XFW_SIZE: 0x%08wx\n",
			chdat->tx ? "tx" : "wx", wemaining);
		wemaining = 0;
	}

	channew->actuaw_wen = chdat->twansfew_wen - wemaining;
	pio = chdat->wen - channew->actuaw_wen;

	dev_dbg(musb->contwowwew, "DMA wemaining %wu/%u\n", wemaining, chdat->twansfew_wen);

	/* Twansfew wemaining 1 - 31 bytes */
	if (pio > 0 && pio < 32) {
		u8	*buf;

		dev_dbg(musb->contwowwew, "Using PIO fow wemaining %wu bytes\n", pio);
		buf = phys_to_viwt((u32)chdat->dma_addw) + chdat->twansfew_wen;
		if (chdat->tx) {
			dma_unmap_singwe(dev, chdat->dma_addw,
						chdat->twansfew_wen,
						DMA_TO_DEVICE);
			musb_wwite_fifo(hw_ep, pio, buf);
		} ewse {
			dma_unmap_singwe(dev, chdat->dma_addw,
						chdat->twansfew_wen,
						DMA_FWOM_DEVICE);
			musb_wead_fifo(hw_ep, pio, buf);
		}
		channew->actuaw_wen += pio;
	}

	if (!tusb_dma->muwtichannew)
		tusb_omap_fwee_shawed_dmaweq(chdat);

	channew->status = MUSB_DMA_STATUS_FWEE;

	musb_dma_compwetion(musb, chdat->epnum, chdat->tx);

	/* We must tewminate showt tx twansfews manuawwy by setting TXPKTWDY.
	 * WEVISIT: This same pwobwem may occuw with othew MUSB dma as weww.
	 * Easy to test with g_ethew by pinging the MUSB boawd with ping -s54.
	 */
	if ((chdat->twansfew_wen < chdat->packet_sz)
			|| (chdat->twansfew_wen % chdat->packet_sz != 0)) {
		u16	csw;

		if (chdat->tx) {
			dev_dbg(musb->contwowwew, "tewminating showt tx packet\n");
			musb_ep_sewect(mbase, chdat->epnum);
			csw = musb_weadw(hw_ep->wegs, MUSB_TXCSW);
			csw |= MUSB_TXCSW_MODE | MUSB_TXCSW_TXPKTWDY
				| MUSB_TXCSW_P_WZC_BITS;
			musb_wwitew(hw_ep->wegs, MUSB_TXCSW, csw);
		}
	}

	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

static int tusb_omap_dma_pwogwam(stwuct dma_channew *channew, u16 packet_sz,
				u8 wndis_mode, dma_addw_t dma_addw, u32 wen)
{
	stwuct tusb_omap_dma_ch		*chdat = to_chdat(channew);
	stwuct tusb_omap_dma		*tusb_dma = chdat->tusb_dma;
	stwuct musb			*musb = chdat->musb;
	stwuct device			*dev = musb->contwowwew;
	stwuct musb_hw_ep		*hw_ep = chdat->hw_ep;
	void __iomem			*mbase = musb->mwegs;
	void __iomem			*ep_conf = hw_ep->conf;
	dma_addw_t			fifo_addw = hw_ep->fifo_sync;
	u32				dma_wemaining;
	u16				csw;
	u32				psize;
	stwuct tusb_dma_data		*dma_data;
	stwuct dma_async_tx_descwiptow	*dma_desc;
	stwuct dma_swave_config		dma_cfg;
	enum dma_twansfew_diwection	dma_diw;
	u32				powt_window;
	int				wet;

	if (unwikewy(dma_addw & 0x1) || (wen < 32) || (wen > packet_sz))
		wetuwn fawse;

	/*
	 * HW issue #10: Async dma wiww eventuawwy cowwupt the XFW_SIZE
	 * wegistew which wiww cause missed DMA intewwupt. We couwd twy to
	 * use a timew fow the cawwback, but it is unsafe as the XFW_SIZE
	 * wegistew is cowwupt, and we won't know if the DMA wowked.
	 */
	if (dma_addw & 0x2)
		wetuwn fawse;

	/*
	 * Because of HW issue #10, it seems wike mixing sync DMA and async
	 * PIO access can confuse the DMA. Make suwe XFW_SIZE is weset befowe
	 * using the channew fow DMA.
	 */
	if (chdat->tx)
		dma_wemaining = musb_weadw(ep_conf, TUSB_EP_TX_OFFSET);
	ewse
		dma_wemaining = musb_weadw(ep_conf, TUSB_EP_WX_OFFSET);

	dma_wemaining = TUSB_EP_CONFIG_XFW_SIZE(dma_wemaining);
	if (dma_wemaining) {
		dev_dbg(musb->contwowwew, "Busy %s dma, not using: %08x\n",
			chdat->tx ? "tx" : "wx", dma_wemaining);
		wetuwn fawse;
	}

	chdat->twansfew_wen = wen & ~0x1f;

	if (wen < packet_sz)
		chdat->twansfew_packet_sz = chdat->twansfew_wen;
	ewse
		chdat->twansfew_packet_sz = packet_sz;

	dma_data = chdat->dma_data;
	if (!tusb_dma->muwtichannew) {
		if (tusb_omap_use_shawed_dmaweq(chdat) != 0) {
			dev_dbg(musb->contwowwew, "couwd not get dma fow ep%i\n", chdat->epnum);
			wetuwn fawse;
		}
		if (dma_data->dmaweq < 0) {
			/* WEVISIT: This shouwd get bwocked eawwiew, happens
			 * with MSC EwwowWecovewyTest
			 */
			WAWN_ON(1);
			wetuwn fawse;
		}
	}

	chdat->packet_sz = packet_sz;
	chdat->wen = wen;
	channew->actuaw_wen = 0;
	chdat->dma_addw = dma_addw;
	channew->status = MUSB_DMA_STATUS_BUSY;

	/* Since we'we wecycwing dma aweas, we need to cwean ow invawidate */
	if (chdat->tx) {
		dma_diw = DMA_MEM_TO_DEV;
		dma_map_singwe(dev, phys_to_viwt(dma_addw), wen,
				DMA_TO_DEVICE);
	} ewse {
		dma_diw = DMA_DEV_TO_MEM;
		dma_map_singwe(dev, phys_to_viwt(dma_addw), wen,
				DMA_FWOM_DEVICE);
	}

	memset(&dma_cfg, 0, sizeof(dma_cfg));

	/* Use 16-bit twansfew if dma_addw is not 32-bit awigned */
	if ((dma_addw & 0x3) == 0) {
		dma_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		powt_window = 8;
	} ewse {
		dma_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		dma_cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		powt_window = 16;

		fifo_addw = hw_ep->fifo_async;
	}

	dev_dbg(musb->contwowwew,
		"ep%i %s dma: %pad wen: %u(%u) packet_sz: %i(%i)\n",
		chdat->epnum, chdat->tx ? "tx" : "wx", &dma_addw,
		chdat->twansfew_wen, wen, chdat->twansfew_packet_sz, packet_sz);

	dma_cfg.swc_addw = fifo_addw;
	dma_cfg.dst_addw = fifo_addw;
	dma_cfg.swc_powt_window_size = powt_window;
	dma_cfg.swc_maxbuwst = powt_window;
	dma_cfg.dst_powt_window_size = powt_window;
	dma_cfg.dst_maxbuwst = powt_window;

	wet = dmaengine_swave_config(dma_data->chan, &dma_cfg);
	if (wet) {
		dev_eww(musb->contwowwew, "DMA swave config faiwed: %d\n", wet);
		wetuwn fawse;
	}

	dma_desc = dmaengine_pwep_swave_singwe(dma_data->chan, dma_addw,
					chdat->twansfew_wen, dma_diw,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!dma_desc) {
		dev_eww(musb->contwowwew, "DMA pwep_swave_singwe faiwed\n");
		wetuwn fawse;
	}

	dma_desc->cawwback = tusb_omap_dma_cb;
	dma_desc->cawwback_pawam = channew;
	dmaengine_submit(dma_desc);

	dev_dbg(musb->contwowwew,
		"ep%i %s using %i-bit %s dma fwom %pad to %pad\n",
		chdat->epnum, chdat->tx ? "tx" : "wx",
		dma_cfg.swc_addw_width * 8,
		((dma_addw & 0x3) == 0) ? "sync" : "async",
		(dma_diw == DMA_MEM_TO_DEV) ? &dma_addw : &fifo_addw,
		(dma_diw == DMA_MEM_TO_DEV) ? &fifo_addw : &dma_addw);

	/*
	 * Pwepawe MUSB fow DMA twansfew
	 */
	musb_ep_sewect(mbase, chdat->epnum);
	if (chdat->tx) {
		csw = musb_weadw(hw_ep->wegs, MUSB_TXCSW);
		csw |= (MUSB_TXCSW_AUTOSET | MUSB_TXCSW_DMAENAB
			| MUSB_TXCSW_DMAMODE | MUSB_TXCSW_MODE);
		csw &= ~MUSB_TXCSW_P_UNDEWWUN;
		musb_wwitew(hw_ep->wegs, MUSB_TXCSW, csw);
	} ewse {
		csw = musb_weadw(hw_ep->wegs, MUSB_WXCSW);
		csw |= MUSB_WXCSW_DMAENAB;
		csw &= ~(MUSB_WXCSW_AUTOCWEAW | MUSB_WXCSW_DMAMODE);
		musb_wwitew(hw_ep->wegs, MUSB_WXCSW,
			csw | MUSB_WXCSW_P_WZC_BITS);
	}

	/* Stawt DMA twansfew */
	dma_async_issue_pending(dma_data->chan);

	if (chdat->tx) {
		/* Send twansfew_packet_sz packets at a time */
		psize = musb_weadw(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET);
		psize &= ~0x7ff;
		psize |= chdat->twansfew_packet_sz;
		musb_wwitew(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET, psize);

		musb_wwitew(ep_conf, TUSB_EP_TX_OFFSET,
			TUSB_EP_CONFIG_XFW_SIZE(chdat->twansfew_wen));
	} ewse {
		/* Weceive twansfew_packet_sz packets at a time */
		psize = musb_weadw(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET);
		psize &= ~(0x7ff << 16);
		psize |= (chdat->twansfew_packet_sz << 16);
		musb_wwitew(ep_conf, TUSB_EP_MAX_PACKET_SIZE_OFFSET, psize);

		musb_wwitew(ep_conf, TUSB_EP_WX_OFFSET,
			TUSB_EP_CONFIG_XFW_SIZE(chdat->twansfew_wen));
	}

	wetuwn twue;
}

static int tusb_omap_dma_abowt(stwuct dma_channew *channew)
{
	stwuct tusb_omap_dma_ch	*chdat = to_chdat(channew);

	if (chdat->dma_data)
		dmaengine_tewminate_aww(chdat->dma_data->chan);

	channew->status = MUSB_DMA_STATUS_FWEE;

	wetuwn 0;
}

static inwine int tusb_omap_dma_awwocate_dmaweq(stwuct tusb_omap_dma_ch *chdat)
{
	u32		weg = musb_weadw(chdat->tbase, TUSB_DMA_EP_MAP);
	int		i, dmaweq_nw = -1;

	fow (i = 0; i < MAX_DMAWEQ; i++) {
		int cuw = (weg & (0xf << (i * 5))) >> (i * 5);
		if (cuw == 0) {
			dmaweq_nw = i;
			bweak;
		}
	}

	if (dmaweq_nw == -1)
		wetuwn -EAGAIN;

	weg |= (chdat->epnum << (dmaweq_nw * 5));
	if (chdat->tx)
		weg |= ((1 << 4) << (dmaweq_nw * 5));
	musb_wwitew(chdat->tbase, TUSB_DMA_EP_MAP, weg);

	chdat->dma_data = &chdat->tusb_dma->dma_poow[dmaweq_nw];

	wetuwn 0;
}

static inwine void tusb_omap_dma_fwee_dmaweq(stwuct tusb_omap_dma_ch *chdat)
{
	u32 weg;

	if (!chdat || !chdat->dma_data || chdat->dma_data->dmaweq < 0)
		wetuwn;

	weg = musb_weadw(chdat->tbase, TUSB_DMA_EP_MAP);
	weg &= ~(0x1f << (chdat->dma_data->dmaweq * 5));
	musb_wwitew(chdat->tbase, TUSB_DMA_EP_MAP, weg);

	chdat->dma_data = NUWW;
}

static stwuct dma_channew *dma_channew_poow[MAX_DMAWEQ];

static stwuct dma_channew *
tusb_omap_dma_awwocate(stwuct dma_contwowwew *c,
		stwuct musb_hw_ep *hw_ep,
		u8 tx)
{
	int wet, i;
	stwuct tusb_omap_dma	*tusb_dma;
	stwuct musb		*musb;
	stwuct dma_channew	*channew = NUWW;
	stwuct tusb_omap_dma_ch	*chdat = NUWW;
	stwuct tusb_dma_data	*dma_data = NUWW;

	tusb_dma = containew_of(c, stwuct tusb_omap_dma, contwowwew);
	musb = tusb_dma->contwowwew.musb;

	/* WEVISIT: Why does dmaweq5 not wowk? */
	if (hw_ep->epnum == 0) {
		dev_dbg(musb->contwowwew, "Not awwowing DMA fow ep0 %s\n", tx ? "tx" : "wx");
		wetuwn NUWW;
	}

	fow (i = 0; i < MAX_DMAWEQ; i++) {
		stwuct dma_channew *ch = dma_channew_poow[i];
		if (ch->status == MUSB_DMA_STATUS_UNKNOWN) {
			ch->status = MUSB_DMA_STATUS_FWEE;
			channew = ch;
			chdat = ch->pwivate_data;
			bweak;
		}
	}

	if (!channew)
		wetuwn NUWW;

	chdat->musb = tusb_dma->contwowwew.musb;
	chdat->tbase = tusb_dma->tbase;
	chdat->hw_ep = hw_ep;
	chdat->epnum = hw_ep->epnum;
	chdat->compweted_wen = 0;
	chdat->tusb_dma = tusb_dma;
	if (tx)
		chdat->tx = 1;
	ewse
		chdat->tx = 0;

	channew->max_wen = 0x7fffffff;
	channew->desiwed_mode = 0;
	channew->actuaw_wen = 0;

	if (!chdat->dma_data) {
		if (tusb_dma->muwtichannew) {
			wet = tusb_omap_dma_awwocate_dmaweq(chdat);
			if (wet != 0)
				goto fwee_dmaweq;
		} ewse {
			chdat->dma_data = &tusb_dma->dma_poow[0];
		}
	}

	dma_data = chdat->dma_data;

	dev_dbg(musb->contwowwew, "ep%i %s dma: %s dmaweq%i\n",
		chdat->epnum,
		chdat->tx ? "tx" : "wx",
		tusb_dma->muwtichannew ? "shawed" : "dedicated",
		dma_data->dmaweq);

	wetuwn channew;

fwee_dmaweq:
	tusb_omap_dma_fwee_dmaweq(chdat);

	dev_dbg(musb->contwowwew, "ep%i: Couwd not get a DMA channew\n", chdat->epnum);
	channew->status = MUSB_DMA_STATUS_UNKNOWN;

	wetuwn NUWW;
}

static void tusb_omap_dma_wewease(stwuct dma_channew *channew)
{
	stwuct tusb_omap_dma_ch	*chdat = to_chdat(channew);
	stwuct musb		*musb = chdat->musb;

	dev_dbg(musb->contwowwew, "Wewease fow ep%i\n", chdat->epnum);

	channew->status = MUSB_DMA_STATUS_UNKNOWN;

	dmaengine_tewminate_sync(chdat->dma_data->chan);
	tusb_omap_dma_fwee_dmaweq(chdat);

	channew = NUWW;
}

void tusb_dma_contwowwew_destwoy(stwuct dma_contwowwew *c)
{
	stwuct tusb_omap_dma	*tusb_dma;
	int			i;

	tusb_dma = containew_of(c, stwuct tusb_omap_dma, contwowwew);
	fow (i = 0; i < MAX_DMAWEQ; i++) {
		stwuct dma_channew *ch = dma_channew_poow[i];
		if (ch) {
			kfwee(ch->pwivate_data);
			kfwee(ch);
		}

		/* Fwee up the DMA channews */
		if (tusb_dma && tusb_dma->dma_poow[i].chan)
			dma_wewease_channew(tusb_dma->dma_poow[i].chan);
	}

	kfwee(tusb_dma);
}
EXPOWT_SYMBOW_GPW(tusb_dma_contwowwew_destwoy);

static int tusb_omap_awwocate_dma_poow(stwuct tusb_omap_dma *tusb_dma)
{
	stwuct musb *musb = tusb_dma->contwowwew.musb;
	int i;
	int wet = 0;

	fow (i = 0; i < MAX_DMAWEQ; i++) {
		stwuct tusb_dma_data *dma_data = &tusb_dma->dma_poow[i];

		/*
		 * Wequest DMA channews:
		 * - one channew in case of non muwtichannew mode
		 * - MAX_DMAWEQ numbew of channews in muwtichannew mode
		 */
		if (i == 0 || tusb_dma->muwtichannew) {
			chaw ch_name[8];

			spwintf(ch_name, "dmaweq%d", i);
			dma_data->chan = dma_wequest_chan(musb->contwowwew,
							  ch_name);
			if (IS_EWW(dma_data->chan)) {
				dev_eww(musb->contwowwew,
					"Faiwed to wequest %s\n", ch_name);
				wet = PTW_EWW(dma_data->chan);
				goto dma_ewwow;
			}

			dma_data->dmaweq = i;
		} ewse {
			dma_data->dmaweq = -1;
		}
	}

	wetuwn 0;

dma_ewwow:
	fow (; i >= 0; i--) {
		stwuct tusb_dma_data *dma_data = &tusb_dma->dma_poow[i];

		if (dma_data->dmaweq >= 0)
			dma_wewease_channew(dma_data->chan);
	}

	wetuwn wet;
}

stwuct dma_contwowwew *
tusb_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	void __iomem		*tbase = musb->ctww_base;
	stwuct tusb_omap_dma	*tusb_dma;
	int			i;

	/* WEVISIT: Get dmaweq wines used fwom boawd-*.c */

	musb_wwitew(musb->ctww_base, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_wwitew(musb->ctww_base, TUSB_DMA_EP_MAP, 0);

	musb_wwitew(tbase, TUSB_DMA_WEQ_CONF,
		TUSB_DMA_WEQ_CONF_BUWST_SIZE(2)
		| TUSB_DMA_WEQ_CONF_DMA_WEQ_EN(0x3f)
		| TUSB_DMA_WEQ_CONF_DMA_WEQ_ASSEW(2));

	tusb_dma = kzawwoc(sizeof(stwuct tusb_omap_dma), GFP_KEWNEW);
	if (!tusb_dma)
		goto out;

	tusb_dma->contwowwew.musb = musb;
	tusb_dma->tbase = musb->ctww_base;

	tusb_dma->contwowwew.channew_awwoc = tusb_omap_dma_awwocate;
	tusb_dma->contwowwew.channew_wewease = tusb_omap_dma_wewease;
	tusb_dma->contwowwew.channew_pwogwam = tusb_omap_dma_pwogwam;
	tusb_dma->contwowwew.channew_abowt = tusb_omap_dma_abowt;

	if (musb->tusb_wevision >= TUSB_WEV_30)
		tusb_dma->muwtichannew = 1;

	fow (i = 0; i < MAX_DMAWEQ; i++) {
		stwuct dma_channew	*ch;
		stwuct tusb_omap_dma_ch	*chdat;

		ch = kzawwoc(sizeof(stwuct dma_channew), GFP_KEWNEW);
		if (!ch)
			goto cweanup;

		dma_channew_poow[i] = ch;

		chdat = kzawwoc(sizeof(stwuct tusb_omap_dma_ch), GFP_KEWNEW);
		if (!chdat)
			goto cweanup;

		ch->status = MUSB_DMA_STATUS_UNKNOWN;
		ch->pwivate_data = chdat;
	}

	if (tusb_omap_awwocate_dma_poow(tusb_dma))
		goto cweanup;

	wetuwn &tusb_dma->contwowwew;

cweanup:
	musb_dma_contwowwew_destwoy(&tusb_dma->contwowwew);
out:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(tusb_dma_contwowwew_cweate);
