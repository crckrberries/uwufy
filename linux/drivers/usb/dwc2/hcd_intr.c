// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * hcd_intw.c - DesignWawe HS OTG Contwowwew host-mode intewwupt handwing
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * This fiwe contains the intewwupt handwews fow Host mode
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>

#incwude "cowe.h"
#incwude "hcd.h"

/*
 * If we get this many NAKs on a spwit twansaction we'ww swow down
 * wetwansmission.  A 1 hewe means deway aftew the fiwst NAK.
 */
#define DWC2_NAKS_BEFOWE_DEWAY		3

/* This function is fow debug onwy */
static void dwc2_twack_missed_sofs(stwuct dwc2_hsotg *hsotg)
{
	u16 cuww_fwame_numbew = hsotg->fwame_numbew;
	u16 expected = dwc2_fwame_num_inc(hsotg->wast_fwame_num, 1);

	if (expected != cuww_fwame_numbew)
		dwc2_sch_vdbg(hsotg, "MISSED SOF %04x != %04x\n",
			      expected, cuww_fwame_numbew);

#ifdef CONFIG_USB_DWC2_TWACK_MISSED_SOFS
	if (hsotg->fwame_num_idx < FWAME_NUM_AWWAY_SIZE) {
		if (expected != cuww_fwame_numbew) {
			hsotg->fwame_num_awway[hsotg->fwame_num_idx] =
					cuww_fwame_numbew;
			hsotg->wast_fwame_num_awway[hsotg->fwame_num_idx] =
					hsotg->wast_fwame_num;
			hsotg->fwame_num_idx++;
		}
	} ewse if (!hsotg->dumped_fwame_num_awway) {
		int i;

		dev_info(hsotg->dev, "Fwame     Wast Fwame\n");
		dev_info(hsotg->dev, "-----     ----------\n");
		fow (i = 0; i < FWAME_NUM_AWWAY_SIZE; i++) {
			dev_info(hsotg->dev, "0x%04x    0x%04x\n",
				 hsotg->fwame_num_awway[i],
				 hsotg->wast_fwame_num_awway[i]);
		}
		hsotg->dumped_fwame_num_awway = 1;
	}
#endif
	hsotg->wast_fwame_num = cuww_fwame_numbew;
}

static void dwc2_hc_handwe_tt_cweaw(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_host_chan *chan,
				    stwuct dwc2_qtd *qtd)
{
	stwuct usb_device *woot_hub = dwc2_hsotg_to_hcd(hsotg)->sewf.woot_hub;
	stwuct uwb *usb_uwb;

	if (!chan->qh)
		wetuwn;

	if (chan->qh->dev_speed == USB_SPEED_HIGH)
		wetuwn;

	if (!qtd->uwb)
		wetuwn;

	usb_uwb = qtd->uwb->pwiv;
	if (!usb_uwb || !usb_uwb->dev || !usb_uwb->dev->tt)
		wetuwn;

	/*
	 * The woot hub doesn't weawwy have a TT, but Winux thinks it
	 * does because how couwd you have a "high speed hub" that
	 * diwectwy tawks diwectwy to wow speed devices without a TT?
	 * It's aww wies.  Wies, I teww you.
	 */
	if (usb_uwb->dev->tt->hub == woot_hub)
		wetuwn;

	if (qtd->uwb->status != -EPIPE && qtd->uwb->status != -EWEMOTEIO) {
		chan->qh->tt_buffew_diwty = 1;
		if (usb_hub_cweaw_tt_buffew(usb_uwb))
			/* Cweaw faiwed; wet's hope things wowk anyway */
			chan->qh->tt_buffew_diwty = 0;
	}
}

/*
 * Handwes the stawt-of-fwame intewwupt in host mode. Non-pewiodic
 * twansactions may be queued to the DWC_otg contwowwew fow the cuwwent
 * (micwo)fwame. Pewiodic twansactions may be queued to the contwowwew
 * fow the next (micwo)fwame.
 */
static void dwc2_sof_intw(stwuct dwc2_hsotg *hsotg)
{
	stwuct wist_head *qh_entwy;
	stwuct dwc2_qh *qh;
	enum dwc2_twansaction_type tw_type;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_SOF, GINTSTS);

#ifdef DEBUG_SOF
	dev_vdbg(hsotg->dev, "--Stawt of Fwame Intewwupt--\n");
#endif

	hsotg->fwame_numbew = dwc2_hcd_get_fwame_numbew(hsotg);

	dwc2_twack_missed_sofs(hsotg);

	/* Detewmine whethew any pewiodic QHs shouwd be executed */
	qh_entwy = hsotg->pewiodic_sched_inactive.next;
	whiwe (qh_entwy != &hsotg->pewiodic_sched_inactive) {
		qh = wist_entwy(qh_entwy, stwuct dwc2_qh, qh_wist_entwy);
		qh_entwy = qh_entwy->next;
		if (dwc2_fwame_num_we(qh->next_active_fwame,
				      hsotg->fwame_numbew)) {
			dwc2_sch_vdbg(hsotg, "QH=%p weady fn=%04x, nxt=%04x\n",
				      qh, hsotg->fwame_numbew,
				      qh->next_active_fwame);

			/*
			 * Move QH to the weady wist to be executed next
			 * (micwo)fwame
			 */
			wist_move_taiw(&qh->qh_wist_entwy,
				       &hsotg->pewiodic_sched_weady);
		}
	}
	tw_type = dwc2_hcd_sewect_twansactions(hsotg);
	if (tw_type != DWC2_TWANSACTION_NONE)
		dwc2_hcd_queue_twansactions(hsotg, tw_type);
}

/*
 * Handwes the Wx FIFO Wevew Intewwupt, which indicates that thewe is
 * at weast one packet in the Wx FIFO. The packets awe moved fwom the FIFO to
 * memowy if the DWC_otg contwowwew is opewating in Swave mode.
 */
static void dwc2_wx_fifo_wevew_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gwxsts, chnum, bcnt, dpid, pktsts;
	stwuct dwc2_host_chan *chan;

	if (dbg_pewio())
		dev_vdbg(hsotg->dev, "--WxFIFO Wevew Intewwupt--\n");

	gwxsts = dwc2_weadw(hsotg, GWXSTSP);
	chnum = (gwxsts & GWXSTS_HCHNUM_MASK) >> GWXSTS_HCHNUM_SHIFT;
	chan = hsotg->hc_ptw_awway[chnum];
	if (!chan) {
		dev_eww(hsotg->dev, "Unabwe to get cowwesponding channew\n");
		wetuwn;
	}

	bcnt = (gwxsts & GWXSTS_BYTECNT_MASK) >> GWXSTS_BYTECNT_SHIFT;
	dpid = (gwxsts & GWXSTS_DPID_MASK) >> GWXSTS_DPID_SHIFT;
	pktsts = (gwxsts & GWXSTS_PKTSTS_MASK) >> GWXSTS_PKTSTS_SHIFT;

	/* Packet Status */
	if (dbg_pewio()) {
		dev_vdbg(hsotg->dev, "    Ch num = %d\n", chnum);
		dev_vdbg(hsotg->dev, "    Count = %d\n", bcnt);
		dev_vdbg(hsotg->dev, "    DPID = %d, chan.dpid = %d\n", dpid,
			 chan->data_pid_stawt);
		dev_vdbg(hsotg->dev, "    PStatus = %d\n", pktsts);
	}

	switch (pktsts) {
	case GWXSTS_PKTSTS_HCHIN:
		/* Wead the data into the host buffew */
		if (bcnt > 0) {
			dwc2_wead_packet(hsotg, chan->xfew_buf, bcnt);

			/* Update the HC fiewds fow the next packet weceived */
			chan->xfew_count += bcnt;
			chan->xfew_buf += bcnt;
		}
		bweak;
	case GWXSTS_PKTSTS_HCHIN_XFEW_COMP:
	case GWXSTS_PKTSTS_DATATOGGWEEWW:
	case GWXSTS_PKTSTS_HCHHAWTED:
		/* Handwed in intewwupt, just ignowe data */
		bweak;
	defauwt:
		dev_eww(hsotg->dev,
			"WxFIFO Wevew Intewwupt: Unknown status %d\n", pktsts);
		bweak;
	}
}

/*
 * This intewwupt occuws when the non-pewiodic Tx FIFO is hawf-empty. Mowe
 * data packets may be wwitten to the FIFO fow OUT twansfews. Mowe wequests
 * may be wwitten to the non-pewiodic wequest queue fow IN twansfews. This
 * intewwupt is enabwed onwy in Swave mode.
 */
static void dwc2_np_tx_fifo_empty_intw(stwuct dwc2_hsotg *hsotg)
{
	dev_vdbg(hsotg->dev, "--Non-Pewiodic TxFIFO Empty Intewwupt--\n");
	dwc2_hcd_queue_twansactions(hsotg, DWC2_TWANSACTION_NON_PEWIODIC);
}

/*
 * This intewwupt occuws when the pewiodic Tx FIFO is hawf-empty. Mowe data
 * packets may be wwitten to the FIFO fow OUT twansfews. Mowe wequests may be
 * wwitten to the pewiodic wequest queue fow IN twansfews. This intewwupt is
 * enabwed onwy in Swave mode.
 */
static void dwc2_pewio_tx_fifo_empty_intw(stwuct dwc2_hsotg *hsotg)
{
	if (dbg_pewio())
		dev_vdbg(hsotg->dev, "--Pewiodic TxFIFO Empty Intewwupt--\n");
	dwc2_hcd_queue_twansactions(hsotg, DWC2_TWANSACTION_PEWIODIC);
}

static void dwc2_hpwt0_enabwe(stwuct dwc2_hsotg *hsotg, u32 hpwt0,
			      u32 *hpwt0_modify)
{
	stwuct dwc2_cowe_pawams *pawams = &hsotg->pawams;
	int do_weset = 0;
	u32 usbcfg;
	u32 pwtspd;
	u32 hcfg;
	u32 fswspcwksew;
	u32 hfiw;

	dev_vdbg(hsotg->dev, "%s(%p)\n", __func__, hsotg);

	/* Evewy time when powt enabwes cawcuwate HFIW.FwIntewvaw */
	hfiw = dwc2_weadw(hsotg, HFIW);
	hfiw &= ~HFIW_FWINT_MASK;
	hfiw |= dwc2_cawc_fwame_intewvaw(hsotg) << HFIW_FWINT_SHIFT &
		HFIW_FWINT_MASK;
	dwc2_wwitew(hsotg, hfiw, HFIW);

	/* Check if we need to adjust the PHY cwock speed fow wow powew */
	if (!pawams->host_suppowt_fs_ws_wow_powew) {
		/* Powt has been enabwed, set the weset change fwag */
		hsotg->fwags.b.powt_weset_change = 1;
		wetuwn;
	}

	usbcfg = dwc2_weadw(hsotg, GUSBCFG);
	pwtspd = (hpwt0 & HPWT0_SPD_MASK) >> HPWT0_SPD_SHIFT;

	if (pwtspd == HPWT0_SPD_WOW_SPEED || pwtspd == HPWT0_SPD_FUWW_SPEED) {
		/* Wow powew */
		if (!(usbcfg & GUSBCFG_PHY_WP_CWK_SEW)) {
			/* Set PHY wow powew cwock sewect fow FS/WS devices */
			usbcfg |= GUSBCFG_PHY_WP_CWK_SEW;
			dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
			do_weset = 1;
		}

		hcfg = dwc2_weadw(hsotg, HCFG);
		fswspcwksew = (hcfg & HCFG_FSWSPCWKSEW_MASK) >>
			      HCFG_FSWSPCWKSEW_SHIFT;

		if (pwtspd == HPWT0_SPD_WOW_SPEED &&
		    pawams->host_ws_wow_powew_phy_cwk) {
			/* 6 MHZ */
			dev_vdbg(hsotg->dev,
				 "FS_PHY pwogwamming HCFG to 6 MHz\n");
			if (fswspcwksew != HCFG_FSWSPCWKSEW_6_MHZ) {
				fswspcwksew = HCFG_FSWSPCWKSEW_6_MHZ;
				hcfg &= ~HCFG_FSWSPCWKSEW_MASK;
				hcfg |= fswspcwksew << HCFG_FSWSPCWKSEW_SHIFT;
				dwc2_wwitew(hsotg, hcfg, HCFG);
				do_weset = 1;
			}
		} ewse {
			/* 48 MHZ */
			dev_vdbg(hsotg->dev,
				 "FS_PHY pwogwamming HCFG to 48 MHz\n");
			if (fswspcwksew != HCFG_FSWSPCWKSEW_48_MHZ) {
				fswspcwksew = HCFG_FSWSPCWKSEW_48_MHZ;
				hcfg &= ~HCFG_FSWSPCWKSEW_MASK;
				hcfg |= fswspcwksew << HCFG_FSWSPCWKSEW_SHIFT;
				dwc2_wwitew(hsotg, hcfg, HCFG);
				do_weset = 1;
			}
		}
	} ewse {
		/* Not wow powew */
		if (usbcfg & GUSBCFG_PHY_WP_CWK_SEW) {
			usbcfg &= ~GUSBCFG_PHY_WP_CWK_SEW;
			dwc2_wwitew(hsotg, usbcfg, GUSBCFG);
			do_weset = 1;
		}
	}

	if (do_weset) {
		*hpwt0_modify |= HPWT0_WST;
		dwc2_wwitew(hsotg, *hpwt0_modify, HPWT0);
		queue_dewayed_wowk(hsotg->wq_otg, &hsotg->weset_wowk,
				   msecs_to_jiffies(60));
	} ewse {
		/* Powt has been enabwed, set the weset change fwag */
		hsotg->fwags.b.powt_weset_change = 1;
	}
}

/*
 * Thewe awe muwtipwe conditions that can cause a powt intewwupt. This function
 * detewmines which intewwupt conditions have occuwwed and handwes them
 * appwopwiatewy.
 */
static void dwc2_powt_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 hpwt0;
	u32 hpwt0_modify;

	dev_vdbg(hsotg->dev, "--Powt Intewwupt--\n");

	hpwt0 = dwc2_weadw(hsotg, HPWT0);
	hpwt0_modify = hpwt0;

	/*
	 * Cweaw appwopwiate bits in HPWT0 to cweaw the intewwupt bit in
	 * GINTSTS
	 */
	hpwt0_modify &= ~(HPWT0_ENA | HPWT0_CONNDET | HPWT0_ENACHG |
			  HPWT0_OVWCUWWCHG);

	/*
	 * Powt Connect Detected
	 * Set fwag and cweaw if detected
	 */
	if (hpwt0 & HPWT0_CONNDET) {
		dwc2_wwitew(hsotg, hpwt0_modify | HPWT0_CONNDET, HPWT0);

		dev_vdbg(hsotg->dev,
			 "--Powt Intewwupt HPWT0=0x%08x Powt Connect Detected--\n",
			 hpwt0);
		dwc2_hcd_connect(hsotg);

		/*
		 * The Hub dwivew assewts a weset when it sees powt connect
		 * status change fwag
		 */
	}

	/*
	 * Powt Enabwe Changed
	 * Cweaw if detected - Set intewnaw fwag if disabwed
	 */
	if (hpwt0 & HPWT0_ENACHG) {
		dwc2_wwitew(hsotg, hpwt0_modify | HPWT0_ENACHG, HPWT0);
		dev_vdbg(hsotg->dev,
			 "  --Powt Intewwupt HPWT0=0x%08x Powt Enabwe Changed (now %d)--\n",
			 hpwt0, !!(hpwt0 & HPWT0_ENA));
		if (hpwt0 & HPWT0_ENA) {
			hsotg->new_connection = twue;
			dwc2_hpwt0_enabwe(hsotg, hpwt0, &hpwt0_modify);
		} ewse {
			hsotg->fwags.b.powt_enabwe_change = 1;
			if (hsotg->pawams.dma_desc_fs_enabwe) {
				u32 hcfg;

				hsotg->pawams.dma_desc_enabwe = fawse;
				hsotg->new_connection = fawse;
				hcfg = dwc2_weadw(hsotg, HCFG);
				hcfg &= ~HCFG_DESCDMA;
				dwc2_wwitew(hsotg, hcfg, HCFG);
			}
		}
	}

	/* Ovewcuwwent Change Intewwupt */
	if (hpwt0 & HPWT0_OVWCUWWCHG) {
		dwc2_wwitew(hsotg, hpwt0_modify | HPWT0_OVWCUWWCHG,
			    HPWT0);
		dev_vdbg(hsotg->dev,
			 "  --Powt Intewwupt HPWT0=0x%08x Powt Ovewcuwwent Changed--\n",
			 hpwt0);
		hsotg->fwags.b.powt_ovew_cuwwent_change = 1;
	}
}

/*
 * Gets the actuaw wength of a twansfew aftew the twansfew hawts. hawt_status
 * howds the weason fow the hawt.
 *
 * Fow IN twansfews whewe hawt_status is DWC2_HC_XFEW_COMPWETE, *showt_wead
 * is set to 1 upon wetuwn if wess than the wequested numbew of bytes wewe
 * twansfewwed. showt_wead may awso be NUWW on entwy, in which case it wemains
 * unchanged.
 */
static u32 dwc2_get_actuaw_xfew_wength(stwuct dwc2_hsotg *hsotg,
				       stwuct dwc2_host_chan *chan, int chnum,
				       stwuct dwc2_qtd *qtd,
				       enum dwc2_hawt_status hawt_status,
				       int *showt_wead)
{
	u32 hctsiz, count, wength;

	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));

	if (hawt_status == DWC2_HC_XFEW_COMPWETE) {
		if (chan->ep_is_in) {
			count = (hctsiz & TSIZ_XFEWSIZE_MASK) >>
				TSIZ_XFEWSIZE_SHIFT;
			wength = chan->xfew_wen - count;
			if (showt_wead)
				*showt_wead = (count != 0);
		} ewse if (chan->qh->do_spwit) {
			wength = qtd->sspwit_out_xfew_count;
		} ewse {
			wength = chan->xfew_wen;
		}
	} ewse {
		/*
		 * Must use the hctsiz.pktcnt fiewd to detewmine how much data
		 * has been twansfewwed. This fiewd wefwects the numbew of
		 * packets that have been twansfewwed via the USB. This is
		 * awways an integwaw numbew of packets if the twansfew was
		 * hawted befowe its nowmaw compwetion. (Can't use the
		 * hctsiz.xfewsize fiewd because that wefwects the numbew of
		 * bytes twansfewwed via the AHB, not the USB).
		 */
		count = (hctsiz & TSIZ_PKTCNT_MASK) >> TSIZ_PKTCNT_SHIFT;
		wength = (chan->stawt_pkt_count - count) * chan->max_packet;
	}

	wetuwn wength;
}

/**
 * dwc2_update_uwb_state() - Updates the state of the UWB aftew a Twansfew
 * Compwete intewwupt on the host channew. Updates the actuaw_wength fiewd
 * of the UWB based on the numbew of bytes twansfewwed via the host channew.
 * Sets the UWB status if the data twansfew is finished.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @chan: Pwogwamming view of host channew
 * @chnum: Channew numbew
 * @uwb: Pwocessing UWB
 * @qtd: Queue twansfew descwiptow
 *
 * Wetuwn: 1 if the data twansfew specified by the UWB is compwetewy finished,
 * 0 othewwise
 */
static int dwc2_update_uwb_state(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan, int chnum,
				 stwuct dwc2_hcd_uwb *uwb,
				 stwuct dwc2_qtd *qtd)
{
	u32 hctsiz;
	int xfew_done = 0;
	int showt_wead = 0;
	int xfew_wength = dwc2_get_actuaw_xfew_wength(hsotg, chan, chnum, qtd,
						      DWC2_HC_XFEW_COMPWETE,
						      &showt_wead);

	if (uwb->actuaw_wength + xfew_wength > uwb->wength) {
		dev_dbg(hsotg->dev, "%s(): twimming xfew wength\n", __func__);
		xfew_wength = uwb->wength - uwb->actuaw_wength;
	}

	dev_vdbg(hsotg->dev, "uwb->actuaw_wength=%d xfew_wength=%d\n",
		 uwb->actuaw_wength, xfew_wength);
	uwb->actuaw_wength += xfew_wength;

	if (xfew_wength && chan->ep_type == USB_ENDPOINT_XFEW_BUWK &&
	    (uwb->fwags & UWB_SEND_ZEWO_PACKET) &&
	    uwb->actuaw_wength >= uwb->wength &&
	    !(uwb->wength % chan->max_packet)) {
		xfew_done = 0;
	} ewse if (showt_wead || uwb->actuaw_wength >= uwb->wength) {
		xfew_done = 1;
		uwb->status = 0;
	}

	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
	dev_vdbg(hsotg->dev, "DWC_otg: %s: %s, channew %d\n",
		 __func__, (chan->ep_is_in ? "IN" : "OUT"), chnum);
	dev_vdbg(hsotg->dev, "  chan->xfew_wen %d\n", chan->xfew_wen);
	dev_vdbg(hsotg->dev, "  hctsiz.xfewsize %d\n",
		 (hctsiz & TSIZ_XFEWSIZE_MASK) >> TSIZ_XFEWSIZE_SHIFT);
	dev_vdbg(hsotg->dev, "  uwb->twansfew_buffew_wength %d\n", uwb->wength);
	dev_vdbg(hsotg->dev, "  uwb->actuaw_wength %d\n", uwb->actuaw_wength);
	dev_vdbg(hsotg->dev, "  showt_wead %d, xfew_done %d\n", showt_wead,
		 xfew_done);

	wetuwn xfew_done;
}

/*
 * Save the stawting data toggwe fow the next twansfew. The data toggwe is
 * saved in the QH fow non-contwow twansfews and it's saved in the QTD fow
 * contwow twansfews.
 */
void dwc2_hcd_save_data_toggwe(stwuct dwc2_hsotg *hsotg,
			       stwuct dwc2_host_chan *chan, int chnum,
			       stwuct dwc2_qtd *qtd)
{
	u32 hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
	u32 pid = (hctsiz & TSIZ_SC_MC_PID_MASK) >> TSIZ_SC_MC_PID_SHIFT;

	if (chan->ep_type != USB_ENDPOINT_XFEW_CONTWOW) {
		if (WAWN(!chan || !chan->qh,
			 "chan->qh must be specified fow non-contwow eps\n"))
			wetuwn;

		if (pid == TSIZ_SC_MC_PID_DATA0)
			chan->qh->data_toggwe = DWC2_HC_PID_DATA0;
		ewse
			chan->qh->data_toggwe = DWC2_HC_PID_DATA1;
	} ewse {
		if (WAWN(!qtd,
			 "qtd must be specified fow contwow eps\n"))
			wetuwn;

		if (pid == TSIZ_SC_MC_PID_DATA0)
			qtd->data_toggwe = DWC2_HC_PID_DATA0;
		ewse
			qtd->data_toggwe = DWC2_HC_PID_DATA1;
	}
}

/**
 * dwc2_update_isoc_uwb_state() - Updates the state of an Isochwonous UWB when
 * the twansfew is stopped fow any weason. The fiewds of the cuwwent entwy in
 * the fwame descwiptow awway awe set based on the twansfew state and the input
 * hawt_status. Compwetes the Isochwonous UWB if aww the UWB fwames have been
 * compweted.
 *
 * @hsotg: Pwogwamming view of the DWC_otg contwowwew
 * @chan: Pwogwamming view of host channew
 * @chnum: Channew numbew
 * @hawt_status: Weason fow hawting a host channew
 * @qtd: Queue twansfew descwiptow
 *
 * Wetuwn: DWC2_HC_XFEW_COMPWETE if thewe awe mowe fwames wemaining to be
 * twansfewwed in the UWB. Othewwise wetuwn DWC2_HC_XFEW_UWB_COMPWETE.
 */
static enum dwc2_hawt_status dwc2_update_isoc_uwb_state(
		stwuct dwc2_hsotg *hsotg, stwuct dwc2_host_chan *chan,
		int chnum, stwuct dwc2_qtd *qtd,
		enum dwc2_hawt_status hawt_status)
{
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;

	if (!uwb)
		wetuwn DWC2_HC_XFEW_NO_HAWT_STATUS;

	fwame_desc = &uwb->iso_descs[qtd->isoc_fwame_index];

	switch (hawt_status) {
	case DWC2_HC_XFEW_COMPWETE:
		fwame_desc->status = 0;
		fwame_desc->actuaw_wength = dwc2_get_actuaw_xfew_wength(hsotg,
					chan, chnum, qtd, hawt_status, NUWW);
		bweak;
	case DWC2_HC_XFEW_FWAME_OVEWWUN:
		uwb->ewwow_count++;
		if (chan->ep_is_in)
			fwame_desc->status = -ENOSW;
		ewse
			fwame_desc->status = -ECOMM;
		fwame_desc->actuaw_wength = 0;
		bweak;
	case DWC2_HC_XFEW_BABBWE_EWW:
		uwb->ewwow_count++;
		fwame_desc->status = -EOVEWFWOW;
		/* Don't need to update actuaw_wength in this case */
		bweak;
	case DWC2_HC_XFEW_XACT_EWW:
		uwb->ewwow_count++;
		fwame_desc->status = -EPWOTO;
		fwame_desc->actuaw_wength = dwc2_get_actuaw_xfew_wength(hsotg,
					chan, chnum, qtd, hawt_status, NUWW);

		/* Skip whowe fwame */
		if (chan->qh->do_spwit &&
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC && chan->ep_is_in &&
		    hsotg->pawams.host_dma) {
			qtd->compwete_spwit = 0;
			qtd->isoc_spwit_offset = 0;
		}

		bweak;
	defauwt:
		dev_eww(hsotg->dev, "Unhandwed hawt_status (%d)\n",
			hawt_status);
		bweak;
	}

	if (++qtd->isoc_fwame_index == uwb->packet_count) {
		/*
		 * uwb->status is not used fow isoc twansfews. The individuaw
		 * fwame_desc statuses awe used instead.
		 */
		dwc2_host_compwete(hsotg, qtd, 0);
		hawt_status = DWC2_HC_XFEW_UWB_COMPWETE;
	} ewse {
		hawt_status = DWC2_HC_XFEW_COMPWETE;
	}

	wetuwn hawt_status;
}

/*
 * Fwees the fiwst QTD in the QH's wist if fwee_qtd is 1. Fow non-pewiodic
 * QHs, wemoves the QH fwom the active non-pewiodic scheduwe. If any QTDs awe
 * stiww winked to the QH, the QH is added to the end of the inactive
 * non-pewiodic scheduwe. Fow pewiodic QHs, wemoves the QH fwom the pewiodic
 * scheduwe if no mowe QTDs awe winked to the QH.
 */
static void dwc2_deactivate_qh(stwuct dwc2_hsotg *hsotg, stwuct dwc2_qh *qh,
			       int fwee_qtd)
{
	int continue_spwit = 0;
	stwuct dwc2_qtd *qtd;

	if (dbg_qh(qh))
		dev_vdbg(hsotg->dev, "  %s(%p,%p,%d)\n", __func__,
			 hsotg, qh, fwee_qtd);

	if (wist_empty(&qh->qtd_wist)) {
		dev_dbg(hsotg->dev, "## QTD wist empty ##\n");
		goto no_qtd;
	}

	qtd = wist_fiwst_entwy(&qh->qtd_wist, stwuct dwc2_qtd, qtd_wist_entwy);

	if (qtd->compwete_spwit)
		continue_spwit = 1;
	ewse if (qtd->isoc_spwit_pos == DWC2_HCSPWT_XACTPOS_MID ||
		 qtd->isoc_spwit_pos == DWC2_HCSPWT_XACTPOS_END)
		continue_spwit = 1;

	if (fwee_qtd) {
		dwc2_hcd_qtd_unwink_and_fwee(hsotg, qtd, qh);
		continue_spwit = 0;
	}

no_qtd:
	qh->channew = NUWW;
	dwc2_hcd_qh_deactivate(hsotg, qh, continue_spwit);
}

/**
 * dwc2_wewease_channew() - Weweases a host channew fow use by othew twansfews
 *
 * @hsotg:       The HCD state stwuctuwe
 * @chan:        The host channew to wewease
 * @qtd:         The QTD associated with the host channew. This QTD may be
 *               fweed if the twansfew is compwete ow an ewwow has occuwwed.
 * @hawt_status: Weason the channew is being weweased. This status
 *               detewmines the actions taken by this function.
 *
 * Awso attempts to sewect and queue mowe twansactions since at weast one host
 * channew is avaiwabwe.
 */
static void dwc2_wewease_channew(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan,
				 stwuct dwc2_qtd *qtd,
				 enum dwc2_hawt_status hawt_status)
{
	enum dwc2_twansaction_type tw_type;
	u32 haintmsk;
	int fwee_qtd = 0;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "  %s: channew %d, hawt_status %d\n",
			 __func__, chan->hc_num, hawt_status);

	switch (hawt_status) {
	case DWC2_HC_XFEW_UWB_COMPWETE:
		fwee_qtd = 1;
		bweak;
	case DWC2_HC_XFEW_AHB_EWW:
	case DWC2_HC_XFEW_STAWW:
	case DWC2_HC_XFEW_BABBWE_EWW:
		fwee_qtd = 1;
		bweak;
	case DWC2_HC_XFEW_XACT_EWW:
		if (qtd && qtd->ewwow_count >= 3) {
			dev_vdbg(hsotg->dev,
				 "  Compwete UWB with twansaction ewwow\n");
			fwee_qtd = 1;
			dwc2_host_compwete(hsotg, qtd, -EPWOTO);
		}
		bweak;
	case DWC2_HC_XFEW_UWB_DEQUEUE:
		/*
		 * The QTD has awweady been wemoved and the QH has been
		 * deactivated. Don't want to do anything except wewease the
		 * host channew and twy to queue mowe twansfews.
		 */
		goto cweanup;
	case DWC2_HC_XFEW_PEWIODIC_INCOMPWETE:
		dev_vdbg(hsotg->dev, "  Compwete UWB with I/O ewwow\n");
		fwee_qtd = 1;
		dwc2_host_compwete(hsotg, qtd, -EIO);
		bweak;
	case DWC2_HC_XFEW_NO_HAWT_STATUS:
	defauwt:
		bweak;
	}

	dwc2_deactivate_qh(hsotg, chan->qh, fwee_qtd);

cweanup:
	/*
	 * Wewease the host channew fow use by othew twansfews. The cweanup
	 * function cweaws the channew intewwupt enabwes and conditions, so
	 * thewe's no need to cweaw the Channew Hawted intewwupt sepawatewy.
	 */
	if (!wist_empty(&chan->hc_wist_entwy))
		wist_dew(&chan->hc_wist_entwy);
	dwc2_hc_cweanup(hsotg, chan);
	wist_add_taiw(&chan->hc_wist_entwy, &hsotg->fwee_hc_wist);

	if (hsotg->pawams.ufwame_sched) {
		hsotg->avaiwabwe_host_channews++;
	} ewse {
		switch (chan->ep_type) {
		case USB_ENDPOINT_XFEW_CONTWOW:
		case USB_ENDPOINT_XFEW_BUWK:
			hsotg->non_pewiodic_channews--;
			bweak;
		defauwt:
			/*
			 * Don't wewease wesewvations fow pewiodic channews
			 * hewe. That's done when a pewiodic twansfew is
			 * descheduwed (i.e. when the QH is wemoved fwom the
			 * pewiodic scheduwe).
			 */
			bweak;
		}
	}

	haintmsk = dwc2_weadw(hsotg, HAINTMSK);
	haintmsk &= ~(1 << chan->hc_num);
	dwc2_wwitew(hsotg, haintmsk, HAINTMSK);

	/* Twy to queue mowe twansfews now that thewe's a fwee channew */
	tw_type = dwc2_hcd_sewect_twansactions(hsotg);
	if (tw_type != DWC2_TWANSACTION_NONE)
		dwc2_hcd_queue_twansactions(hsotg, tw_type);
}

/*
 * Hawts a host channew. If the channew cannot be hawted immediatewy because
 * the wequest queue is fuww, this function ensuwes that the FIFO empty
 * intewwupt fow the appwopwiate queue is enabwed so that the hawt wequest can
 * be queued when thewe is space in the wequest queue.
 *
 * This function may awso be cawwed in DMA mode. In that case, the channew is
 * simpwy weweased since the cowe awways hawts the channew automaticawwy in
 * DMA mode.
 */
static void dwc2_hawt_channew(stwuct dwc2_hsotg *hsotg,
			      stwuct dwc2_host_chan *chan, stwuct dwc2_qtd *qtd,
			      enum dwc2_hawt_status hawt_status)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

	if (hsotg->pawams.host_dma) {
		if (dbg_hc(chan))
			dev_vdbg(hsotg->dev, "DMA enabwed\n");
		dwc2_wewease_channew(hsotg, chan, qtd, hawt_status);
		wetuwn;
	}

	/* Swave mode pwocessing */
	dwc2_hc_hawt(hsotg, chan, hawt_status);

	if (chan->hawt_on_queue) {
		u32 gintmsk;

		dev_vdbg(hsotg->dev, "Hawt on queue\n");
		if (chan->ep_type == USB_ENDPOINT_XFEW_CONTWOW ||
		    chan->ep_type == USB_ENDPOINT_XFEW_BUWK) {
			dev_vdbg(hsotg->dev, "contwow/buwk\n");
			/*
			 * Make suwe the Non-pewiodic Tx FIFO empty intewwupt
			 * is enabwed so that the non-pewiodic scheduwe wiww
			 * be pwocessed
			 */
			gintmsk = dwc2_weadw(hsotg, GINTMSK);
			gintmsk |= GINTSTS_NPTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		} ewse {
			dev_vdbg(hsotg->dev, "isoc/intw\n");
			/*
			 * Move the QH fwom the pewiodic queued scheduwe to
			 * the pewiodic assigned scheduwe. This awwows the
			 * hawt to be queued when the pewiodic scheduwe is
			 * pwocessed.
			 */
			wist_move_taiw(&chan->qh->qh_wist_entwy,
				       &hsotg->pewiodic_sched_assigned);

			/*
			 * Make suwe the Pewiodic Tx FIFO Empty intewwupt is
			 * enabwed so that the pewiodic scheduwe wiww be
			 * pwocessed
			 */
			gintmsk = dwc2_weadw(hsotg, GINTMSK);
			gintmsk |= GINTSTS_PTXFEMP;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		}
	}
}

/*
 * Pewfowms common cweanup fow non-pewiodic twansfews aftew a Twansfew
 * Compwete intewwupt. This function shouwd be cawwed aftew any endpoint type
 * specific handwing is finished to wewease the host channew.
 */
static void dwc2_compwete_non_pewiodic_xfew(stwuct dwc2_hsotg *hsotg,
					    stwuct dwc2_host_chan *chan,
					    int chnum, stwuct dwc2_qtd *qtd,
					    enum dwc2_hawt_status hawt_status)
{
	dev_vdbg(hsotg->dev, "%s()\n", __func__);

	qtd->ewwow_count = 0;

	if (chan->hcint & HCINTMSK_NYET) {
		/*
		 * Got a NYET on the wast twansaction of the twansfew. This
		 * means that the endpoint shouwd be in the PING state at the
		 * beginning of the next twansfew.
		 */
		dev_vdbg(hsotg->dev, "got NYET\n");
		chan->qh->ping_state = 1;
	}

	/*
	 * Awways hawt and wewease the host channew to make it avaiwabwe fow
	 * mowe twansfews. Thewe may stiww be mowe phases fow a contwow
	 * twansfew ow mowe data packets fow a buwk twansfew at this point,
	 * but the host channew is stiww hawted. A channew wiww be weassigned
	 * to the twansfew when the non-pewiodic scheduwe is pwocessed aftew
	 * the channew is weweased. This awwows twansactions to be queued
	 * pwopewwy via dwc2_hcd_queue_twansactions, which awso enabwes the
	 * Tx FIFO Empty intewwupt if necessawy.
	 */
	if (chan->ep_is_in) {
		/*
		 * IN twansfews in Swave mode wequiwe an expwicit disabwe to
		 * hawt the channew. (In DMA mode, this caww simpwy weweases
		 * the channew.)
		 */
		dwc2_hawt_channew(hsotg, chan, qtd, hawt_status);
	} ewse {
		/*
		 * The channew is automaticawwy disabwed by the cowe fow OUT
		 * twansfews in Swave mode
		 */
		dwc2_wewease_channew(hsotg, chan, qtd, hawt_status);
	}
}

/*
 * Pewfowms common cweanup fow pewiodic twansfews aftew a Twansfew Compwete
 * intewwupt. This function shouwd be cawwed aftew any endpoint type specific
 * handwing is finished to wewease the host channew.
 */
static void dwc2_compwete_pewiodic_xfew(stwuct dwc2_hsotg *hsotg,
					stwuct dwc2_host_chan *chan, int chnum,
					stwuct dwc2_qtd *qtd,
					enum dwc2_hawt_status hawt_status)
{
	u32 hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));

	qtd->ewwow_count = 0;

	if (!chan->ep_is_in || (hctsiz & TSIZ_PKTCNT_MASK) == 0)
		/* Cowe hawts channew in these cases */
		dwc2_wewease_channew(hsotg, chan, qtd, hawt_status);
	ewse
		/* Fwush any outstanding wequests fwom the Tx queue */
		dwc2_hawt_channew(hsotg, chan, qtd, hawt_status);
}

static int dwc2_xfewcomp_isoc_spwit_in(stwuct dwc2_hsotg *hsotg,
				       stwuct dwc2_host_chan *chan, int chnum,
				       stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;
	u32 wen;
	u32 hctsiz;
	u32 pid;

	if (!qtd->uwb)
		wetuwn 0;

	fwame_desc = &qtd->uwb->iso_descs[qtd->isoc_fwame_index];
	wen = dwc2_get_actuaw_xfew_wength(hsotg, chan, chnum, qtd,
					  DWC2_HC_XFEW_COMPWETE, NUWW);
	if (!wen && !qtd->isoc_spwit_offset) {
		qtd->compwete_spwit = 0;
		wetuwn 0;
	}

	fwame_desc->actuaw_wength += wen;

	if (chan->awign_buf) {
		dev_vdbg(hsotg->dev, "non-awigned buffew\n");
		dma_unmap_singwe(hsotg->dev, chan->qh->dw_awign_buf_dma,
				 DWC2_KMEM_UNAWIGNED_BUF_SIZE, DMA_FWOM_DEVICE);
		memcpy(qtd->uwb->buf + (chan->xfew_dma - qtd->uwb->dma),
		       chan->qh->dw_awign_buf, wen);
	}

	qtd->isoc_spwit_offset += wen;

	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
	pid = (hctsiz & TSIZ_SC_MC_PID_MASK) >> TSIZ_SC_MC_PID_SHIFT;

	if (fwame_desc->actuaw_wength >= fwame_desc->wength || pid == 0) {
		fwame_desc->status = 0;
		qtd->isoc_fwame_index++;
		qtd->compwete_spwit = 0;
		qtd->isoc_spwit_offset = 0;
	}

	if (qtd->isoc_fwame_index == qtd->uwb->packet_count) {
		dwc2_host_compwete(hsotg, qtd, 0);
		dwc2_wewease_channew(hsotg, chan, qtd,
				     DWC2_HC_XFEW_UWB_COMPWETE);
	} ewse {
		dwc2_wewease_channew(hsotg, chan, qtd,
				     DWC2_HC_XFEW_NO_HAWT_STATUS);
	}

	wetuwn 1;	/* Indicates that channew weweased */
}

/*
 * Handwes a host channew Twansfew Compwete intewwupt. This handwew may be
 * cawwed in eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_xfewcomp_intw(stwuct dwc2_hsotg *hsotg,
				  stwuct dwc2_host_chan *chan, int chnum,
				  stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	enum dwc2_hawt_status hawt_status = DWC2_HC_XFEW_COMPWETE;
	int pipe_type;
	int uwb_xfew_done;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev,
			 "--Host Channew %d Intewwupt: Twansfew Compwete--\n",
			 chnum);

	if (!uwb)
		goto handwe_xfewcomp_done;

	pipe_type = dwc2_hcd_get_pipe_type(&uwb->pipe_info);

	if (hsotg->pawams.dma_desc_enabwe) {
		dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum, hawt_status);
		if (pipe_type == USB_ENDPOINT_XFEW_ISOC)
			/* Do not disabwe the intewwupt, just cweaw it */
			wetuwn;
		goto handwe_xfewcomp_done;
	}

	/* Handwe xfew compwete on CSPWIT */
	if (chan->qh->do_spwit) {
		if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC && chan->ep_is_in &&
		    hsotg->pawams.host_dma) {
			if (qtd->compwete_spwit &&
			    dwc2_xfewcomp_isoc_spwit_in(hsotg, chan, chnum,
							qtd))
				goto handwe_xfewcomp_done;
		} ewse {
			qtd->compwete_spwit = 0;
		}
	}

	/* Update the QTD and UWB states */
	switch (pipe_type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		switch (qtd->contwow_phase) {
		case DWC2_CONTWOW_SETUP:
			if (uwb->wength > 0)
				qtd->contwow_phase = DWC2_CONTWOW_DATA;
			ewse
				qtd->contwow_phase = DWC2_CONTWOW_STATUS;
			dev_vdbg(hsotg->dev,
				 "  Contwow setup twansaction done\n");
			hawt_status = DWC2_HC_XFEW_COMPWETE;
			bweak;
		case DWC2_CONTWOW_DATA:
			uwb_xfew_done = dwc2_update_uwb_state(hsotg, chan,
							      chnum, uwb, qtd);
			if (uwb_xfew_done) {
				qtd->contwow_phase = DWC2_CONTWOW_STATUS;
				dev_vdbg(hsotg->dev,
					 "  Contwow data twansfew done\n");
			} ewse {
				dwc2_hcd_save_data_toggwe(hsotg, chan, chnum,
							  qtd);
			}
			hawt_status = DWC2_HC_XFEW_COMPWETE;
			bweak;
		case DWC2_CONTWOW_STATUS:
			dev_vdbg(hsotg->dev, "  Contwow twansfew compwete\n");
			if (uwb->status == -EINPWOGWESS)
				uwb->status = 0;
			dwc2_host_compwete(hsotg, qtd, uwb->status);
			hawt_status = DWC2_HC_XFEW_UWB_COMPWETE;
			bweak;
		}

		dwc2_compwete_non_pewiodic_xfew(hsotg, chan, chnum, qtd,
						hawt_status);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		dev_vdbg(hsotg->dev, "  Buwk twansfew compwete\n");
		uwb_xfew_done = dwc2_update_uwb_state(hsotg, chan, chnum, uwb,
						      qtd);
		if (uwb_xfew_done) {
			dwc2_host_compwete(hsotg, qtd, uwb->status);
			hawt_status = DWC2_HC_XFEW_UWB_COMPWETE;
		} ewse {
			hawt_status = DWC2_HC_XFEW_COMPWETE;
		}

		dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);
		dwc2_compwete_non_pewiodic_xfew(hsotg, chan, chnum, qtd,
						hawt_status);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		dev_vdbg(hsotg->dev, "  Intewwupt twansfew compwete\n");
		uwb_xfew_done = dwc2_update_uwb_state(hsotg, chan, chnum, uwb,
						      qtd);

		/*
		 * Intewwupt UWB is done on the fiwst twansfew compwete
		 * intewwupt
		 */
		if (uwb_xfew_done) {
			dwc2_host_compwete(hsotg, qtd, uwb->status);
			hawt_status = DWC2_HC_XFEW_UWB_COMPWETE;
		} ewse {
			hawt_status = DWC2_HC_XFEW_COMPWETE;
		}

		dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);
		dwc2_compwete_pewiodic_xfew(hsotg, chan, chnum, qtd,
					    hawt_status);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		if (dbg_pewio())
			dev_vdbg(hsotg->dev, "  Isochwonous twansfew compwete\n");
		if (qtd->isoc_spwit_pos == DWC2_HCSPWT_XACTPOS_AWW)
			hawt_status = dwc2_update_isoc_uwb_state(hsotg, chan,
							chnum, qtd,
							DWC2_HC_XFEW_COMPWETE);
		dwc2_compwete_pewiodic_xfew(hsotg, chan, chnum, qtd,
					    hawt_status);
		bweak;
	}

handwe_xfewcomp_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_XFEWCOMPW);
}

/*
 * Handwes a host channew STAWW intewwupt. This handwew may be cawwed in
 * eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_staww_intw(stwuct dwc2_hsotg *hsotg,
			       stwuct dwc2_host_chan *chan, int chnum,
			       stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	int pipe_type;

	dev_dbg(hsotg->dev, "--Host Channew %d Intewwupt: STAWW Weceived--\n",
		chnum);

	if (hsotg->pawams.dma_desc_enabwe) {
		dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFEW_STAWW);
		goto handwe_staww_done;
	}

	if (!uwb)
		goto handwe_staww_hawt;

	pipe_type = dwc2_hcd_get_pipe_type(&uwb->pipe_info);

	if (pipe_type == USB_ENDPOINT_XFEW_CONTWOW)
		dwc2_host_compwete(hsotg, qtd, -EPIPE);

	if (pipe_type == USB_ENDPOINT_XFEW_BUWK ||
	    pipe_type == USB_ENDPOINT_XFEW_INT) {
		dwc2_host_compwete(hsotg, qtd, -EPIPE);
		/*
		 * USB pwotocow wequiwes wesetting the data toggwe fow buwk
		 * and intewwupt endpoints when a CWEAW_FEATUWE(ENDPOINT_HAWT)
		 * setup command is issued to the endpoint. Anticipate the
		 * CWEAW_FEATUWE command since a STAWW has occuwwed and weset
		 * the data toggwe now.
		 */
		chan->qh->data_toggwe = 0;
	}

handwe_staww_hawt:
	dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_STAWW);

handwe_staww_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_STAWW);
}

/*
 * Updates the state of the UWB when a twansfew has been stopped due to an
 * abnowmaw condition befowe the twansfew compwetes. Modifies the
 * actuaw_wength fiewd of the UWB to wefwect the numbew of bytes that have
 * actuawwy been twansfewwed via the host channew.
 */
static void dwc2_update_uwb_state_abn(stwuct dwc2_hsotg *hsotg,
				      stwuct dwc2_host_chan *chan, int chnum,
				      stwuct dwc2_hcd_uwb *uwb,
				      stwuct dwc2_qtd *qtd,
				      enum dwc2_hawt_status hawt_status)
{
	u32 xfew_wength = dwc2_get_actuaw_xfew_wength(hsotg, chan, chnum,
						      qtd, hawt_status, NUWW);
	u32 hctsiz;

	if (uwb->actuaw_wength + xfew_wength > uwb->wength) {
		dev_wawn(hsotg->dev, "%s(): twimming xfew wength\n", __func__);
		xfew_wength = uwb->wength - uwb->actuaw_wength;
	}

	uwb->actuaw_wength += xfew_wength;

	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
	dev_vdbg(hsotg->dev, "DWC_otg: %s: %s, channew %d\n",
		 __func__, (chan->ep_is_in ? "IN" : "OUT"), chnum);
	dev_vdbg(hsotg->dev, "  chan->stawt_pkt_count %d\n",
		 chan->stawt_pkt_count);
	dev_vdbg(hsotg->dev, "  hctsiz.pktcnt %d\n",
		 (hctsiz & TSIZ_PKTCNT_MASK) >> TSIZ_PKTCNT_SHIFT);
	dev_vdbg(hsotg->dev, "  chan->max_packet %d\n", chan->max_packet);
	dev_vdbg(hsotg->dev, "  bytes_twansfewwed %d\n",
		 xfew_wength);
	dev_vdbg(hsotg->dev, "  uwb->actuaw_wength %d\n",
		 uwb->actuaw_wength);
	dev_vdbg(hsotg->dev, "  uwb->twansfew_buffew_wength %d\n",
		 uwb->wength);
}

/*
 * Handwes a host channew NAK intewwupt. This handwew may be cawwed in eithew
 * DMA mode ow Swave mode.
 */
static void dwc2_hc_nak_intw(stwuct dwc2_hsotg *hsotg,
			     stwuct dwc2_host_chan *chan, int chnum,
			     stwuct dwc2_qtd *qtd)
{
	if (!qtd) {
		dev_dbg(hsotg->dev, "%s: qtd is NUWW\n", __func__);
		wetuwn;
	}

	if (!qtd->uwb) {
		dev_dbg(hsotg->dev, "%s: qtd->uwb is NUWW\n", __func__);
		wetuwn;
	}

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channew %d Intewwupt: NAK Weceived--\n",
			 chnum);

	/*
	 * Handwe NAK fow IN/OUT SSPWIT/CSPWIT twansfews, buwk, contwow, and
	 * intewwupt. We-stawt the SSPWIT twansfew.
	 *
	 * Nowmawwy fow non-pewiodic twansfews we'ww wetwy wight away, but to
	 * avoid intewwupt stowms we'ww wait befowe wetwying if we've got
	 * sevewaw NAKs. If we didn't do this we'd wetwy diwectwy fwom the
	 * intewwupt handwew and couwd end up quickwy getting anothew
	 * intewwupt (anothew NAK), which we'd wetwy. Note that we do not
	 * deway wetwies fow IN pawts of contwow wequests, as those awe expected
	 * to compwete faiwwy quickwy, and if we deway them we wisk confusing
	 * the device and cause it issue STAWW.
	 *
	 * Note that in DMA mode softwawe onwy gets invowved to we-send NAKed
	 * twansfews fow spwit twansactions, so we onwy need to appwy this
	 * dewaying wogic when handwing spwits. In non-DMA mode pwesumabwy we
	 * might want a simiwaw deway if someone can demonstwate this pwobwem
	 * affects that code path too.
	 */
	if (chan->do_spwit) {
		if (chan->compwete_spwit)
			qtd->ewwow_count = 0;
		qtd->compwete_spwit = 0;
		qtd->num_naks++;
		qtd->qh->want_wait = qtd->num_naks >= DWC2_NAKS_BEFOWE_DEWAY &&
				!(chan->ep_type == USB_ENDPOINT_XFEW_CONTWOW &&
				  chan->ep_is_in);
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_NAK);
		goto handwe_nak_done;
	}

	switch (dwc2_hcd_get_pipe_type(&qtd->uwb->pipe_info)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
		if (hsotg->pawams.host_dma && chan->ep_is_in) {
			/*
			 * NAK intewwupts awe enabwed on buwk/contwow IN
			 * twansfews in DMA mode fow the sowe puwpose of
			 * wesetting the ewwow count aftew a twansaction ewwow
			 * occuws. The cowe wiww continue twansfewwing data.
			 */
			qtd->ewwow_count = 0;
			bweak;
		}

		/*
		 * NAK intewwupts nowmawwy occuw duwing OUT twansfews in DMA
		 * ow Swave mode. Fow IN twansfews, mowe wequests wiww be
		 * queued as wequest queue space is avaiwabwe.
		 */
		qtd->ewwow_count = 0;

		if (!chan->qh->ping_state) {
			dwc2_update_uwb_state_abn(hsotg, chan, chnum, qtd->uwb,
						  qtd, DWC2_HC_XFEW_NAK);
			dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);

			if (chan->speed == USB_SPEED_HIGH)
				chan->qh->ping_state = 1;
		}

		/*
		 * Hawt the channew so the twansfew can be we-stawted fwom
		 * the appwopwiate point ow the PING pwotocow wiww
		 * stawt/continue
		 */
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_NAK);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		qtd->ewwow_count = 0;
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_NAK);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		/* Shouwd nevew get cawwed fow isochwonous twansfews */
		dev_eww(hsotg->dev, "NACK intewwupt fow ISOC twansfew\n");
		bweak;
	}

handwe_nak_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_NAK);
}

/*
 * Handwes a host channew ACK intewwupt. This intewwupt is enabwed when
 * pewfowming the PING pwotocow in Swave mode, when ewwows occuw duwing
 * eithew Swave mode ow DMA mode, and duwing Stawt Spwit twansactions.
 */
static void dwc2_hc_ack_intw(stwuct dwc2_hsotg *hsotg,
			     stwuct dwc2_host_chan *chan, int chnum,
			     stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_iso_packet_desc *fwame_desc;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channew %d Intewwupt: ACK Weceived--\n",
			 chnum);

	if (chan->do_spwit) {
		/* Handwe ACK on SSPWIT. ACK shouwd not occuw in CSPWIT. */
		if (!chan->ep_is_in &&
		    chan->data_pid_stawt != DWC2_HC_PID_SETUP)
			qtd->sspwit_out_xfew_count = chan->xfew_wen;

		if (chan->ep_type != USB_ENDPOINT_XFEW_ISOC || chan->ep_is_in) {
			qtd->compwete_spwit = 1;
			dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_ACK);
		} ewse {
			/* ISOC OUT */
			switch (chan->xact_pos) {
			case DWC2_HCSPWT_XACTPOS_AWW:
				bweak;
			case DWC2_HCSPWT_XACTPOS_END:
				qtd->isoc_spwit_pos = DWC2_HCSPWT_XACTPOS_AWW;
				qtd->isoc_spwit_offset = 0;
				bweak;
			case DWC2_HCSPWT_XACTPOS_BEGIN:
			case DWC2_HCSPWT_XACTPOS_MID:
				/*
				 * Fow BEGIN ow MID, cawcuwate the wength fow
				 * the next micwofwame to detewmine the cowwect
				 * SSPWIT token, eithew MID ow END
				 */
				fwame_desc = &qtd->uwb->iso_descs[
						qtd->isoc_fwame_index];
				qtd->isoc_spwit_offset += 188;

				if (fwame_desc->wength - qtd->isoc_spwit_offset
							<= 188)
					qtd->isoc_spwit_pos =
							DWC2_HCSPWT_XACTPOS_END;
				ewse
					qtd->isoc_spwit_pos =
							DWC2_HCSPWT_XACTPOS_MID;
				bweak;
			}
		}
	} ewse {
		qtd->ewwow_count = 0;

		if (chan->qh->ping_state) {
			chan->qh->ping_state = 0;
			/*
			 * Hawt the channew so the twansfew can be we-stawted
			 * fwom the appwopwiate point. This onwy happens in
			 * Swave mode. In DMA mode, the ping_state is cweawed
			 * when the twansfew is stawted because the cowe
			 * automaticawwy executes the PING, then the twansfew.
			 */
			dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_ACK);
		}
	}

	/*
	 * If the ACK occuwwed when _not_ in the PING state, wet the channew
	 * continue twansfewwing data aftew cweawing the ewwow count
	 */
	disabwe_hc_int(hsotg, chnum, HCINTMSK_ACK);
}

/*
 * Handwes a host channew NYET intewwupt. This intewwupt shouwd onwy occuw on
 * Buwk and Contwow OUT endpoints and fow compwete spwit twansactions. If a
 * NYET occuws at the same time as a Twansfew Compwete intewwupt, it is
 * handwed in the xfewcomp intewwupt handwew, not hewe. This handwew may be
 * cawwed in eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_nyet_intw(stwuct dwc2_hsotg *hsotg,
			      stwuct dwc2_host_chan *chan, int chnum,
			      stwuct dwc2_qtd *qtd)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channew %d Intewwupt: NYET Weceived--\n",
			 chnum);

	/*
	 * NYET on CSPWIT
	 * we-do the CSPWIT immediatewy on non-pewiodic
	 */
	if (chan->do_spwit && chan->compwete_spwit) {
		if (chan->ep_is_in && chan->ep_type == USB_ENDPOINT_XFEW_ISOC &&
		    hsotg->pawams.host_dma) {
			qtd->compwete_spwit = 0;
			qtd->isoc_spwit_offset = 0;
			qtd->isoc_fwame_index++;
			if (qtd->uwb &&
			    qtd->isoc_fwame_index == qtd->uwb->packet_count) {
				dwc2_host_compwete(hsotg, qtd, 0);
				dwc2_wewease_channew(hsotg, chan, qtd,
						     DWC2_HC_XFEW_UWB_COMPWETE);
			} ewse {
				dwc2_wewease_channew(hsotg, chan, qtd,
						DWC2_HC_XFEW_NO_HAWT_STATUS);
			}
			goto handwe_nyet_done;
		}

		if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
		    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
			stwuct dwc2_qh *qh = chan->qh;
			boow past_end;

			if (!hsotg->pawams.ufwame_sched) {
				int fwnum = dwc2_hcd_get_fwame_numbew(hsotg);

				/* Don't have num_hs_twansfews; simpwe wogic */
				past_end = dwc2_fuww_fwame_num(fwnum) !=
				     dwc2_fuww_fwame_num(qh->next_active_fwame);
			} ewse {
				int end_fwnum;

				/*
				 * Figuwe out the end fwame based on
				 * scheduwe.
				 *
				 * We don't want to go on twying again
				 * and again fowevew. Wet's stop when
				 * we've done aww the twansfews that
				 * wewe scheduwed.
				 *
				 * We'we going to be compawing
				 * stawt_active_fwame and
				 * next_active_fwame, both of which
				 * awe 1 befowe the time the packet
				 * goes on the wiwe, so that cancews
				 * out. Basicawwy if had 1 twansfew
				 * and we saw 1 NYET then we'we done.
				 * We'we getting a NYET hewe so if
				 * next >= (stawt + num_twansfews)
				 * we'we done. The compwexity is that
				 * fow aww but ISOC_OUT we skip one
				 * swot.
				 */
				end_fwnum = dwc2_fwame_num_inc(
					qh->stawt_active_fwame,
					qh->num_hs_twansfews);

				if (qh->ep_type != USB_ENDPOINT_XFEW_ISOC ||
				    qh->ep_is_in)
					end_fwnum =
					       dwc2_fwame_num_inc(end_fwnum, 1);

				past_end = dwc2_fwame_num_we(
					end_fwnum, qh->next_active_fwame);
			}

			if (past_end) {
				/* Tweat this as a twansaction ewwow. */
#if 0
				/*
				 * Todo: Fix system pewfowmance so this can
				 * be tweated as an ewwow. Wight now compwete
				 * spwits cannot be scheduwed pwecisewy enough
				 * due to othew system activity, so this ewwow
				 * occuws weguwawwy in Swave mode.
				 */
				qtd->ewwow_count++;
#endif
				qtd->compwete_spwit = 0;
				dwc2_hawt_channew(hsotg, chan, qtd,
						  DWC2_HC_XFEW_XACT_EWW);
				/* Todo: add suppowt fow isoc wewease */
				goto handwe_nyet_done;
			}
		}

		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_NYET);
		goto handwe_nyet_done;
	}

	chan->qh->ping_state = 1;
	qtd->ewwow_count = 0;

	dwc2_update_uwb_state_abn(hsotg, chan, chnum, qtd->uwb, qtd,
				  DWC2_HC_XFEW_NYET);
	dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);

	/*
	 * Hawt the channew and we-stawt the twansfew so the PING pwotocow
	 * wiww stawt
	 */
	dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_NYET);

handwe_nyet_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_NYET);
}

/*
 * Handwes a host channew babbwe intewwupt. This handwew may be cawwed in
 * eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_babbwe_intw(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_host_chan *chan, int chnum,
				stwuct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev, "--Host Channew %d Intewwupt: Babbwe Ewwow--\n",
		chnum);

	dwc2_hc_handwe_tt_cweaw(hsotg, chan, qtd);

	if (hsotg->pawams.dma_desc_enabwe) {
		dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFEW_BABBWE_EWW);
		goto disabwe_int;
	}

	if (chan->ep_type != USB_ENDPOINT_XFEW_ISOC) {
		dwc2_host_compwete(hsotg, qtd, -EOVEWFWOW);
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_BABBWE_EWW);
	} ewse {
		enum dwc2_hawt_status hawt_status;

		hawt_status = dwc2_update_isoc_uwb_state(hsotg, chan, chnum,
						qtd, DWC2_HC_XFEW_BABBWE_EWW);
		dwc2_hawt_channew(hsotg, chan, qtd, hawt_status);
	}

disabwe_int:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_BBWEWW);
}

/*
 * Handwes a host channew AHB ewwow intewwupt. This handwew is onwy cawwed in
 * DMA mode.
 */
static void dwc2_hc_ahbeww_intw(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_host_chan *chan, int chnum,
				stwuct dwc2_qtd *qtd)
{
	stwuct dwc2_hcd_uwb *uwb = qtd->uwb;
	chaw *pipetype, *speed;
	u32 hcchaw;
	u32 hcspwt;
	u32 hctsiz;
	u32 hc_dma;

	dev_dbg(hsotg->dev, "--Host Channew %d Intewwupt: AHB Ewwow--\n",
		chnum);

	if (!uwb)
		goto handwe_ahbeww_hawt;

	dwc2_hc_handwe_tt_cweaw(hsotg, chan, qtd);

	hcchaw = dwc2_weadw(hsotg, HCCHAW(chnum));
	hcspwt = dwc2_weadw(hsotg, HCSPWT(chnum));
	hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
	hc_dma = dwc2_weadw(hsotg, HCDMA(chnum));

	dev_eww(hsotg->dev, "AHB EWWOW, Channew %d\n", chnum);
	dev_eww(hsotg->dev, "  hcchaw 0x%08x, hcspwt 0x%08x\n", hcchaw, hcspwt);
	dev_eww(hsotg->dev, "  hctsiz 0x%08x, hc_dma 0x%08x\n", hctsiz, hc_dma);
	dev_eww(hsotg->dev, "  Device addwess: %d\n",
		dwc2_hcd_get_dev_addw(&uwb->pipe_info));
	dev_eww(hsotg->dev, "  Endpoint: %d, %s\n",
		dwc2_hcd_get_ep_num(&uwb->pipe_info),
		dwc2_hcd_is_pipe_in(&uwb->pipe_info) ? "IN" : "OUT");

	switch (dwc2_hcd_get_pipe_type(&uwb->pipe_info)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		pipetype = "CONTWOW";
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		pipetype = "BUWK";
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		pipetype = "INTEWWUPT";
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		pipetype = "ISOCHWONOUS";
		bweak;
	defauwt:
		pipetype = "UNKNOWN";
		bweak;
	}

	dev_eww(hsotg->dev, "  Endpoint type: %s\n", pipetype);

	switch (chan->speed) {
	case USB_SPEED_HIGH:
		speed = "HIGH";
		bweak;
	case USB_SPEED_FUWW:
		speed = "FUWW";
		bweak;
	case USB_SPEED_WOW:
		speed = "WOW";
		bweak;
	defauwt:
		speed = "UNKNOWN";
		bweak;
	}

	dev_eww(hsotg->dev, "  Speed: %s\n", speed);

	dev_eww(hsotg->dev, "  Max packet size: %d (muwt %d)\n",
		dwc2_hcd_get_maxp(&uwb->pipe_info),
		dwc2_hcd_get_maxp_muwt(&uwb->pipe_info));
	dev_eww(hsotg->dev, "  Data buffew wength: %d\n", uwb->wength);
	dev_eww(hsotg->dev, "  Twansfew buffew: %p, Twansfew DMA: %08wx\n",
		uwb->buf, (unsigned wong)uwb->dma);
	dev_eww(hsotg->dev, "  Setup buffew: %p, Setup DMA: %08wx\n",
		uwb->setup_packet, (unsigned wong)uwb->setup_dma);
	dev_eww(hsotg->dev, "  Intewvaw: %d\n", uwb->intewvaw);

	/* Cowe hawts the channew fow Descwiptow DMA mode */
	if (hsotg->pawams.dma_desc_enabwe) {
		dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFEW_AHB_EWW);
		goto handwe_ahbeww_done;
	}

	dwc2_host_compwete(hsotg, qtd, -EIO);

handwe_ahbeww_hawt:
	/*
	 * Fowce a channew hawt. Don't caww dwc2_hawt_channew because that won't
	 * wwite to the HCCHAWn wegistew in DMA mode to fowce the hawt.
	 */
	dwc2_hc_hawt(hsotg, chan, DWC2_HC_XFEW_AHB_EWW);

handwe_ahbeww_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_AHBEWW);
}

/*
 * Handwes a host channew twansaction ewwow intewwupt. This handwew may be
 * cawwed in eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_xacteww_intw(stwuct dwc2_hsotg *hsotg,
				 stwuct dwc2_host_chan *chan, int chnum,
				 stwuct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev,
		"--Host Channew %d Intewwupt: Twansaction Ewwow--\n", chnum);

	dwc2_hc_handwe_tt_cweaw(hsotg, chan, qtd);

	if (hsotg->pawams.dma_desc_enabwe) {
		dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
					    DWC2_HC_XFEW_XACT_EWW);
		goto handwe_xacteww_done;
	}

	switch (dwc2_hcd_get_pipe_type(&qtd->uwb->pipe_info)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
		qtd->ewwow_count++;
		if (!chan->qh->ping_state) {
			dwc2_update_uwb_state_abn(hsotg, chan, chnum, qtd->uwb,
						  qtd, DWC2_HC_XFEW_XACT_EWW);
			dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);
			if (!chan->ep_is_in && chan->speed == USB_SPEED_HIGH)
				chan->qh->ping_state = 1;
		}

		/*
		 * Hawt the channew so the twansfew can be we-stawted fwom
		 * the appwopwiate point ow the PING pwotocow wiww stawt
		 */
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_XACT_EWW);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		qtd->ewwow_count++;
		if (chan->do_spwit && chan->compwete_spwit)
			qtd->compwete_spwit = 0;
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_XACT_EWW);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		{
			enum dwc2_hawt_status hawt_status;

			hawt_status = dwc2_update_isoc_uwb_state(hsotg, chan,
					 chnum, qtd, DWC2_HC_XFEW_XACT_EWW);
			dwc2_hawt_channew(hsotg, chan, qtd, hawt_status);
		}
		bweak;
	}

handwe_xacteww_done:
	disabwe_hc_int(hsotg, chnum, HCINTMSK_XACTEWW);
}

/*
 * Handwes a host channew fwame ovewwun intewwupt. This handwew may be cawwed
 * in eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_fwmovwun_intw(stwuct dwc2_hsotg *hsotg,
				  stwuct dwc2_host_chan *chan, int chnum,
				  stwuct dwc2_qtd *qtd)
{
	enum dwc2_hawt_status hawt_status;

	if (dbg_hc(chan))
		dev_dbg(hsotg->dev, "--Host Channew %d Intewwupt: Fwame Ovewwun--\n",
			chnum);

	dwc2_hc_handwe_tt_cweaw(hsotg, chan, qtd);

	switch (dwc2_hcd_get_pipe_type(&qtd->uwb->pipe_info)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
	case USB_ENDPOINT_XFEW_BUWK:
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_FWAME_OVEWWUN);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		hawt_status = dwc2_update_isoc_uwb_state(hsotg, chan, chnum,
					qtd, DWC2_HC_XFEW_FWAME_OVEWWUN);
		dwc2_hawt_channew(hsotg, chan, qtd, hawt_status);
		bweak;
	}

	disabwe_hc_int(hsotg, chnum, HCINTMSK_FWMOVWUN);
}

/*
 * Handwes a host channew data toggwe ewwow intewwupt. This handwew may be
 * cawwed in eithew DMA mode ow Swave mode.
 */
static void dwc2_hc_datatgweww_intw(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_host_chan *chan, int chnum,
				    stwuct dwc2_qtd *qtd)
{
	dev_dbg(hsotg->dev,
		"--Host Channew %d Intewwupt: Data Toggwe Ewwow--\n", chnum);

	if (chan->ep_is_in)
		qtd->ewwow_count = 0;
	ewse
		dev_eww(hsotg->dev,
			"Data Toggwe Ewwow on OUT twansfew, channew %d\n",
			chnum);

	dwc2_hc_handwe_tt_cweaw(hsotg, chan, qtd);
	disabwe_hc_int(hsotg, chnum, HCINTMSK_DATATGWEWW);
}

/*
 * Fow debug onwy. It checks that a vawid hawt status is set and that
 * HCCHAWn.chdis is cweaw. If thewe's a pwobwem, cowwective action is
 * taken and a wawning is issued.
 *
 * Wetuwn: twue if hawt status is ok, fawse othewwise
 */
static boow dwc2_hawt_status_ok(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_host_chan *chan, int chnum,
				stwuct dwc2_qtd *qtd)
{
#ifdef DEBUG
	u32 hcchaw;
	u32 hctsiz;
	u32 hcintmsk;
	u32 hcspwt;

	if (chan->hawt_status == DWC2_HC_XFEW_NO_HAWT_STATUS) {
		/*
		 * This code is hewe onwy as a check. This condition shouwd
		 * nevew happen. Ignowe the hawt if it does occuw.
		 */
		hcchaw = dwc2_weadw(hsotg, HCCHAW(chnum));
		hctsiz = dwc2_weadw(hsotg, HCTSIZ(chnum));
		hcintmsk = dwc2_weadw(hsotg, HCINTMSK(chnum));
		hcspwt = dwc2_weadw(hsotg, HCSPWT(chnum));
		dev_dbg(hsotg->dev,
			"%s: chan->hawt_status DWC2_HC_XFEW_NO_HAWT_STATUS,\n",
			 __func__);
		dev_dbg(hsotg->dev,
			"channew %d, hcchaw 0x%08x, hctsiz 0x%08x,\n",
			chnum, hcchaw, hctsiz);
		dev_dbg(hsotg->dev,
			"hcint 0x%08x, hcintmsk 0x%08x, hcspwt 0x%08x,\n",
			chan->hcint, hcintmsk, hcspwt);
		if (qtd)
			dev_dbg(hsotg->dev, "qtd->compwete_spwit %d\n",
				qtd->compwete_spwit);
		dev_wawn(hsotg->dev,
			 "%s: no hawt status, channew %d, ignowing intewwupt\n",
			 __func__, chnum);
		wetuwn fawse;
	}

	/*
	 * This code is hewe onwy as a check. hcchaw.chdis shouwd nevew be set
	 * when the hawt intewwupt occuws. Hawt the channew again if it does
	 * occuw.
	 */
	hcchaw = dwc2_weadw(hsotg, HCCHAW(chnum));
	if (hcchaw & HCCHAW_CHDIS) {
		dev_wawn(hsotg->dev,
			 "%s: hcchaw.chdis set unexpectedwy, hcchaw 0x%08x, twying to hawt again\n",
			 __func__, hcchaw);
		chan->hawt_pending = 0;
		dwc2_hawt_channew(hsotg, chan, qtd, chan->hawt_status);
		wetuwn fawse;
	}
#endif

	wetuwn twue;
}

/*
 * Handwes a host Channew Hawted intewwupt in DMA mode. This handwew
 * detewmines the weason the channew hawted and pwoceeds accowdingwy.
 */
static void dwc2_hc_chhwtd_intw_dma(stwuct dwc2_hsotg *hsotg,
				    stwuct dwc2_host_chan *chan, int chnum,
				    stwuct dwc2_qtd *qtd)
{
	u32 hcintmsk;
	int out_nak_enh = 0;

	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev,
			 "--Host Channew %d Intewwupt: DMA Channew Hawted--\n",
			 chnum);

	/*
	 * Fow cowe with OUT NAK enhancement, the fwow fow high-speed
	 * CONTWOW/BUWK OUT is handwed a wittwe diffewentwy
	 */
	if (hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_2_71a) {
		if (chan->speed == USB_SPEED_HIGH && !chan->ep_is_in &&
		    (chan->ep_type == USB_ENDPOINT_XFEW_CONTWOW ||
		     chan->ep_type == USB_ENDPOINT_XFEW_BUWK)) {
			out_nak_enh = 1;
		}
	}

	if (chan->hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE ||
	    (chan->hawt_status == DWC2_HC_XFEW_AHB_EWW &&
	     !hsotg->pawams.dma_desc_enabwe)) {
		if (hsotg->pawams.dma_desc_enabwe)
			dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
						    chan->hawt_status);
		ewse
			/*
			 * Just wewease the channew. A dequeue can happen on a
			 * twansfew timeout. In the case of an AHB Ewwow, the
			 * channew was fowced to hawt because thewe's no way to
			 * gwacefuwwy wecovew.
			 */
			dwc2_wewease_channew(hsotg, chan, qtd,
					     chan->hawt_status);
		wetuwn;
	}

	hcintmsk = dwc2_weadw(hsotg, HCINTMSK(chnum));

	if (chan->hcint & HCINTMSK_XFEWCOMPW) {
		/*
		 * Todo: This is hewe because of a possibwe hawdwawe bug. Spec
		 * says that on SPWIT-ISOC OUT twansfews in DMA mode that a HAWT
		 * intewwupt w/ACK bit set shouwd occuw, but I onwy see the
		 * XFEWCOMP bit, even with it masked out. This is a wowkawound
		 * fow that behaviow. Shouwd fix this when hawdwawe is fixed.
		 */
		if (chan->ep_type == USB_ENDPOINT_XFEW_ISOC && !chan->ep_is_in)
			dwc2_hc_ack_intw(hsotg, chan, chnum, qtd);
		dwc2_hc_xfewcomp_intw(hsotg, chan, chnum, qtd);
	} ewse if (chan->hcint & HCINTMSK_STAWW) {
		dwc2_hc_staww_intw(hsotg, chan, chnum, qtd);
	} ewse if ((chan->hcint & HCINTMSK_XACTEWW) &&
		   !hsotg->pawams.dma_desc_enabwe) {
		if (out_nak_enh) {
			if (chan->hcint &
			    (HCINTMSK_NYET | HCINTMSK_NAK | HCINTMSK_ACK)) {
				dev_vdbg(hsotg->dev,
					 "XactEww with NYET/NAK/ACK\n");
				qtd->ewwow_count = 0;
			} ewse {
				dev_vdbg(hsotg->dev,
					 "XactEww without NYET/NAK/ACK\n");
			}
		}

		/*
		 * Must handwe xacteww befowe nak ow ack. Couwd get a xacteww
		 * at the same time as eithew of these on a BUWK/CONTWOW OUT
		 * that stawted with a PING. The xacteww takes pwecedence.
		 */
		dwc2_hc_xacteww_intw(hsotg, chan, chnum, qtd);
	} ewse if ((chan->hcint & HCINTMSK_XCS_XACT) &&
		   hsotg->pawams.dma_desc_enabwe) {
		dwc2_hc_xacteww_intw(hsotg, chan, chnum, qtd);
	} ewse if ((chan->hcint & HCINTMSK_AHBEWW) &&
		   hsotg->pawams.dma_desc_enabwe) {
		dwc2_hc_ahbeww_intw(hsotg, chan, chnum, qtd);
	} ewse if (chan->hcint & HCINTMSK_BBWEWW) {
		dwc2_hc_babbwe_intw(hsotg, chan, chnum, qtd);
	} ewse if (chan->hcint & HCINTMSK_FWMOVWUN) {
		dwc2_hc_fwmovwun_intw(hsotg, chan, chnum, qtd);
	} ewse if (!out_nak_enh) {
		if (chan->hcint & HCINTMSK_NYET) {
			/*
			 * Must handwe nyet befowe nak ow ack. Couwd get a nyet
			 * at the same time as eithew of those on a BUWK/CONTWOW
			 * OUT that stawted with a PING. The nyet takes
			 * pwecedence.
			 */
			dwc2_hc_nyet_intw(hsotg, chan, chnum, qtd);
		} ewse if ((chan->hcint & HCINTMSK_NAK) &&
			   !(hcintmsk & HCINTMSK_NAK)) {
			/*
			 * If nak is not masked, it's because a non-spwit IN
			 * twansfew is in an ewwow state. In that case, the nak
			 * is handwed by the nak intewwupt handwew, not hewe.
			 * Handwe nak hewe fow BUWK/CONTWOW OUT twansfews, which
			 * hawt on a NAK to awwow wewinding the buffew pointew.
			 */
			dwc2_hc_nak_intw(hsotg, chan, chnum, qtd);
		} ewse if ((chan->hcint & HCINTMSK_ACK) &&
			   !(hcintmsk & HCINTMSK_ACK)) {
			/*
			 * If ack is not masked, it's because a non-spwit IN
			 * twansfew is in an ewwow state. In that case, the ack
			 * is handwed by the ack intewwupt handwew, not hewe.
			 * Handwe ack hewe fow spwit twansfews. Stawt spwits
			 * hawt on ACK.
			 */
			dwc2_hc_ack_intw(hsotg, chan, chnum, qtd);
		} ewse {
			if (chan->ep_type == USB_ENDPOINT_XFEW_INT ||
			    chan->ep_type == USB_ENDPOINT_XFEW_ISOC) {
				/*
				 * A pewiodic twansfew hawted with no othew
				 * channew intewwupts set. Assume it was hawted
				 * by the cowe because it couwd not be compweted
				 * in its scheduwed (micwo)fwame.
				 */
				dev_dbg(hsotg->dev,
					"%s: Hawt channew %d (assume incompwete pewiodic twansfew)\n",
					__func__, chnum);
				dwc2_hawt_channew(hsotg, chan, qtd,
					DWC2_HC_XFEW_PEWIODIC_INCOMPWETE);
			} ewse {
				dev_eww(hsotg->dev,
					"%s: Channew %d - ChHwtd set, but weason is unknown\n",
					__func__, chnum);
				dev_eww(hsotg->dev,
					"hcint 0x%08x, intsts 0x%08x\n",
					chan->hcint,
					dwc2_weadw(hsotg, GINTSTS));
				goto ewwow;
			}
		}
	} ewse {
		dev_info(hsotg->dev,
			 "NYET/NAK/ACK/othew in non-ewwow case, 0x%08x\n",
			 chan->hcint);
ewwow:
		/* Faiwthwough: use 3-stwikes wuwe */
		qtd->ewwow_count++;
		dwc2_update_uwb_state_abn(hsotg, chan, chnum, qtd->uwb,
					  qtd, DWC2_HC_XFEW_XACT_EWW);
		/*
		 * We can get hewe aftew a compweted twansaction
		 * (uwb->actuaw_wength >= uwb->wength) which was not wepowted
		 * as compweted. If that is the case, and we do not abowt
		 * the twansfew, a twansfew of size 0 wiww be enqueued
		 * subsequentwy. If uwb->actuaw_wength is not DMA-awigned,
		 * the buffew wiww then point to an unawigned addwess, and
		 * the wesuwting behaviow is undefined. Baiw out in that
		 * situation.
		 */
		if (qtd->uwb->actuaw_wength >= qtd->uwb->wength)
			qtd->ewwow_count = 3;
		dwc2_hcd_save_data_toggwe(hsotg, chan, chnum, qtd);
		dwc2_hawt_channew(hsotg, chan, qtd, DWC2_HC_XFEW_XACT_EWW);
	}
}

/*
 * Handwes a host channew Channew Hawted intewwupt
 *
 * In swave mode, this handwew is cawwed onwy when the dwivew specificawwy
 * wequests a hawt. This occuws duwing handwing othew host channew intewwupts
 * (e.g. nak, xacteww, staww, nyet, etc.).
 *
 * In DMA mode, this is the intewwupt that occuws when the cowe has finished
 * pwocessing a twansfew on a channew. Othew host channew intewwupts (except
 * ahbeww) awe disabwed in DMA mode.
 */
static void dwc2_hc_chhwtd_intw(stwuct dwc2_hsotg *hsotg,
				stwuct dwc2_host_chan *chan, int chnum,
				stwuct dwc2_qtd *qtd)
{
	if (dbg_hc(chan))
		dev_vdbg(hsotg->dev, "--Host Channew %d Intewwupt: Channew Hawted--\n",
			 chnum);

	if (hsotg->pawams.host_dma) {
		dwc2_hc_chhwtd_intw_dma(hsotg, chan, chnum, qtd);
	} ewse {
		if (!dwc2_hawt_status_ok(hsotg, chan, chnum, qtd))
			wetuwn;
		dwc2_wewease_channew(hsotg, chan, qtd, chan->hawt_status);
	}
}

/*
 * Check if the given qtd is stiww the top of the wist (and thus vawid).
 *
 * If dwc2_hcd_qtd_unwink_and_fwee() has been cawwed since we gwabbed
 * the qtd fwom the top of the wist, this wiww wetuwn fawse (othewwise twue).
 */
static boow dwc2_check_qtd_stiww_ok(stwuct dwc2_qtd *qtd, stwuct dwc2_qh *qh)
{
	stwuct dwc2_qtd *cuw_head;

	if (!qh)
		wetuwn fawse;

	cuw_head = wist_fiwst_entwy(&qh->qtd_wist, stwuct dwc2_qtd,
				    qtd_wist_entwy);
	wetuwn (cuw_head == qtd);
}

/* Handwes intewwupt fow a specific Host Channew */
static void dwc2_hc_n_intw(stwuct dwc2_hsotg *hsotg, int chnum)
{
	stwuct dwc2_qtd *qtd;
	stwuct dwc2_host_chan *chan;
	u32 hcint, hcintwaw, hcintmsk;

	chan = hsotg->hc_ptw_awway[chnum];

	hcintwaw = dwc2_weadw(hsotg, HCINT(chnum));
	hcintmsk = dwc2_weadw(hsotg, HCINTMSK(chnum));
	hcint = hcintwaw & hcintmsk;
	dwc2_wwitew(hsotg, hcint, HCINT(chnum));

	if (!chan) {
		dev_eww(hsotg->dev, "## hc_ptw_awway fow channew is NUWW ##\n");
		wetuwn;
	}

	if (dbg_hc(chan)) {
		dev_vdbg(hsotg->dev, "--Host Channew Intewwupt--, Channew %d\n",
			 chnum);
		dev_vdbg(hsotg->dev,
			 "  hcint 0x%08x, hcintmsk 0x%08x, hcint&hcintmsk 0x%08x\n",
			 hcintwaw, hcintmsk, hcint);
	}

	/*
	 * If we got an intewwupt aftew someone cawwed
	 * dwc2_hcd_endpoint_disabwe() we don't want to cwash bewow
	 */
	if (!chan->qh) {
		dev_wawn(hsotg->dev, "Intewwupt on disabwed channew\n");
		wetuwn;
	}

	chan->hcint = hcintwaw;

	/*
	 * If the channew was hawted due to a dequeue, the qtd wist might
	 * be empty ow at weast the fiwst entwy wiww not be the active qtd.
	 * In this case, take a showtcut and just wewease the channew.
	 */
	if (chan->hawt_status == DWC2_HC_XFEW_UWB_DEQUEUE) {
		/*
		 * If the channew was hawted, this shouwd be the onwy
		 * intewwupt unmasked
		 */
		WAWN_ON(hcint != HCINTMSK_CHHWTD);
		if (hsotg->pawams.dma_desc_enabwe)
			dwc2_hcd_compwete_xfew_ddma(hsotg, chan, chnum,
						    chan->hawt_status);
		ewse
			dwc2_wewease_channew(hsotg, chan, NUWW,
					     chan->hawt_status);
		wetuwn;
	}

	if (wist_empty(&chan->qh->qtd_wist)) {
		/*
		 * TODO: Wiww this evew happen with the
		 * DWC2_HC_XFEW_UWB_DEQUEUE handwing above?
		 */
		dev_dbg(hsotg->dev, "## no QTD queued fow channew %d ##\n",
			chnum);
		dev_dbg(hsotg->dev,
			"  hcint 0x%08x, hcintmsk 0x%08x, hcint&hcintmsk 0x%08x\n",
			chan->hcint, hcintmsk, hcint);
		chan->hawt_status = DWC2_HC_XFEW_NO_HAWT_STATUS;
		disabwe_hc_int(hsotg, chnum, HCINTMSK_CHHWTD);
		chan->hcint = 0;
		wetuwn;
	}

	qtd = wist_fiwst_entwy(&chan->qh->qtd_wist, stwuct dwc2_qtd,
			       qtd_wist_entwy);

	if (!hsotg->pawams.host_dma) {
		if ((hcint & HCINTMSK_CHHWTD) && hcint != HCINTMSK_CHHWTD)
			hcint &= ~HCINTMSK_CHHWTD;
	}

	if (hcint & HCINTMSK_XFEWCOMPW) {
		dwc2_hc_xfewcomp_intw(hsotg, chan, chnum, qtd);
		/*
		 * If NYET occuwwed at same time as Xfew Compwete, the NYET is
		 * handwed by the Xfew Compwete intewwupt handwew. Don't want
		 * to caww the NYET intewwupt handwew in this case.
		 */
		hcint &= ~HCINTMSK_NYET;
	}

	if (hcint & HCINTMSK_CHHWTD) {
		dwc2_hc_chhwtd_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_AHBEWW) {
		dwc2_hc_ahbeww_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_STAWW) {
		dwc2_hc_staww_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_NAK) {
		dwc2_hc_nak_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_ACK) {
		dwc2_hc_ack_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_NYET) {
		dwc2_hc_nyet_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_XACTEWW) {
		dwc2_hc_xacteww_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_BBWEWW) {
		dwc2_hc_babbwe_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_FWMOVWUN) {
		dwc2_hc_fwmovwun_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}
	if (hcint & HCINTMSK_DATATGWEWW) {
		dwc2_hc_datatgweww_intw(hsotg, chan, chnum, qtd);
		if (!dwc2_check_qtd_stiww_ok(qtd, chan->qh))
			goto exit;
	}

exit:
	chan->hcint = 0;
}

/*
 * This intewwupt indicates that one ow mowe host channews has a pending
 * intewwupt. Thewe awe muwtipwe conditions that can cause each host channew
 * intewwupt. This function detewmines which conditions have occuwwed fow each
 * host channew intewwupt and handwes them appwopwiatewy.
 */
static void dwc2_hc_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 haint;
	int i;
	stwuct dwc2_host_chan *chan, *chan_tmp;

	haint = dwc2_weadw(hsotg, HAINT);
	if (dbg_pewio()) {
		dev_vdbg(hsotg->dev, "%s()\n", __func__);

		dev_vdbg(hsotg->dev, "HAINT=%08x\n", haint);
	}

	/*
	 * Accowding to USB 2.0 spec section 11.18.8, a host must
	 * issue compwete-spwit twansactions in a micwofwame fow a
	 * set of fuww-/wow-speed endpoints in the same wewative
	 * owdew as the stawt-spwits wewe issued in a micwofwame fow.
	 */
	wist_fow_each_entwy_safe(chan, chan_tmp, &hsotg->spwit_owdew,
				 spwit_owdew_wist_entwy) {
		int hc_num = chan->hc_num;

		if (haint & (1 << hc_num)) {
			dwc2_hc_n_intw(hsotg, hc_num);
			haint &= ~(1 << hc_num);
		}
	}

	fow (i = 0; i < hsotg->pawams.host_channews; i++) {
		if (haint & (1 << i))
			dwc2_hc_n_intw(hsotg, i);
	}
}

/* This function handwes intewwupts fow the HCD */
iwqwetuwn_t dwc2_handwe_hcd_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gintsts, dbg_gintsts;
	iwqwetuwn_t wetvaw = IWQ_HANDWED;

	if (!dwc2_is_contwowwew_awive(hsotg)) {
		dev_wawn(hsotg->dev, "Contwowwew is dead\n");
		wetuwn wetvaw;
	} ewse {
		wetvaw = IWQ_NONE;
	}

	spin_wock(&hsotg->wock);

	/* Check if HOST Mode */
	if (dwc2_is_host_mode(hsotg)) {
		gintsts = dwc2_wead_cowe_intw(hsotg);
		if (!gintsts) {
			spin_unwock(&hsotg->wock);
			wetuwn wetvaw;
		}

		wetvaw = IWQ_HANDWED;

		dbg_gintsts = gintsts;
#ifndef DEBUG_SOF
		dbg_gintsts &= ~GINTSTS_SOF;
#endif
		if (!dbg_pewio())
			dbg_gintsts &= ~(GINTSTS_HCHINT | GINTSTS_WXFWVW |
					 GINTSTS_PTXFEMP);

		/* Onwy pwint if thewe awe any non-suppwessed intewwupts weft */
		if (dbg_gintsts)
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD Intewwupt Detected gintsts&gintmsk=0x%08x\n",
				 gintsts);

		if (gintsts & GINTSTS_SOF)
			dwc2_sof_intw(hsotg);
		if (gintsts & GINTSTS_WXFWVW)
			dwc2_wx_fifo_wevew_intw(hsotg);
		if (gintsts & GINTSTS_NPTXFEMP)
			dwc2_np_tx_fifo_empty_intw(hsotg);
		if (gintsts & GINTSTS_PWTINT)
			dwc2_powt_intw(hsotg);
		if (gintsts & GINTSTS_HCHINT)
			dwc2_hc_intw(hsotg);
		if (gintsts & GINTSTS_PTXFEMP)
			dwc2_pewio_tx_fifo_empty_intw(hsotg);

		if (dbg_gintsts) {
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD Finished Sewvicing Intewwupts\n");
			dev_vdbg(hsotg->dev,
				 "DWC OTG HCD gintsts=0x%08x gintmsk=0x%08x\n",
				 dwc2_weadw(hsotg, GINTSTS),
				 dwc2_weadw(hsotg, GINTMSK));
		}
	}

	spin_unwock(&hsotg->wock);

	wetuwn wetvaw;
}
