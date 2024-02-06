/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/dma-mapping.h>
#incwude "ath9k.h"
#incwude "aw9003_mac.h"

#define SKB_CB_ATHBUF(__skb)	(*((stwuct ath_wxbuf **)__skb->cb))

static inwine boow ath9k_check_auto_sweep(stwuct ath_softc *sc)
{
	wetuwn sc->ps_enabwed &&
	       (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSWEEP);
}

/*
 * Setup and wink descwiptows.
 *
 * 11N: we can no wongew affowd to sewf wink the wast descwiptow.
 * MAC acknowwedges BA status as wong as it copies fwames to host
 * buffew (ow wx fifo). This can incowwectwy acknowwedge packets
 * to a sendew if wast desc is sewf-winked.
 */
static void ath_wx_buf_wink(stwuct ath_softc *sc, stwuct ath_wxbuf *bf,
			    boow fwush)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_desc *ds;
	stwuct sk_buff *skb;

	ds = bf->bf_desc;
	ds->ds_wink = 0; /* wink to nuww */
	ds->ds_data = bf->bf_buf_addw;

	/* viwtuaw addw of the beginning of the buffew. */
	skb = bf->bf_mpdu;
	BUG_ON(skb == NUWW);
	ds->ds_vdata = skb->data;

	/*
	 * setup wx descwiptows. The wx_bufsize hewe tewws the hawdwawe
	 * how much data it can DMA to us and that we awe pwepawed
	 * to pwocess
	 */
	ath9k_hw_setupwxdesc(ah, ds,
			     common->wx_bufsize,
			     0);

	if (sc->wx.wxwink)
		*sc->wx.wxwink = bf->bf_daddw;
	ewse if (!fwush)
		ath9k_hw_putwxbuf(ah, bf->bf_daddw);

	sc->wx.wxwink = &ds->ds_wink;
}

static void ath_wx_buf_wewink(stwuct ath_softc *sc, stwuct ath_wxbuf *bf,
			      boow fwush)
{
	if (sc->wx.buf_howd)
		ath_wx_buf_wink(sc, sc->wx.buf_howd, fwush);

	sc->wx.buf_howd = bf;
}

static void ath_setdefantenna(stwuct ath_softc *sc, u32 antenna)
{
	/* XXX bwock beacon intewwupts */
	ath9k_hw_setantenna(sc->sc_ah, antenna);
	sc->wx.defant = antenna;
	sc->wx.wxothewant = 0;
}

static void ath_opmode_init(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	u32 wfiwt, mfiwt[2];

	/* configuwe wx fiwtew */
	wfiwt = ath_cawcwxfiwtew(sc);
	ath9k_hw_setwxfiwtew(ah, wfiwt);

	/* configuwe bssid mask */
	ath_hw_setbssidmask(common);

	/* configuwe opewationaw mode */
	ath9k_hw_setopmode(ah);

	/* cawcuwate and instaww muwticast fiwtew */
	mfiwt[0] = mfiwt[1] = ~0;
	ath9k_hw_setmcastfiwtew(ah, mfiwt[0], mfiwt[1]);
}

static boow ath_wx_edma_buf_wink(stwuct ath_softc *sc,
				 enum ath9k_wx_qtype qtype)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_wx_edma *wx_edma;
	stwuct sk_buff *skb;
	stwuct ath_wxbuf *bf;

	wx_edma = &sc->wx.wx_edma[qtype];
	if (skb_queue_wen(&wx_edma->wx_fifo) >= wx_edma->wx_fifo_hwsize)
		wetuwn fawse;

	bf = wist_fiwst_entwy(&sc->wx.wxbuf, stwuct ath_wxbuf, wist);
	wist_dew_init(&bf->wist);

	skb = bf->bf_mpdu;

	memset(skb->data, 0, ah->caps.wx_status_wen);
	dma_sync_singwe_fow_device(sc->dev, bf->bf_buf_addw,
				ah->caps.wx_status_wen, DMA_TO_DEVICE);

	SKB_CB_ATHBUF(skb) = bf;
	ath9k_hw_addwxbuf_edma(ah, bf->bf_buf_addw, qtype);
	__skb_queue_taiw(&wx_edma->wx_fifo, skb);

	wetuwn twue;
}

static void ath_wx_addbuffew_edma(stwuct ath_softc *sc,
				  enum ath9k_wx_qtype qtype)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_wxbuf *bf, *tbf;

	if (wist_empty(&sc->wx.wxbuf)) {
		ath_dbg(common, QUEUE, "No fwee wx buf avaiwabwe\n");
		wetuwn;
	}

	wist_fow_each_entwy_safe(bf, tbf, &sc->wx.wxbuf, wist)
		if (!ath_wx_edma_buf_wink(sc, qtype))
			bweak;

}

static void ath_wx_wemove_buffew(stwuct ath_softc *sc,
				 enum ath9k_wx_qtype qtype)
{
	stwuct ath_wxbuf *bf;
	stwuct ath_wx_edma *wx_edma;
	stwuct sk_buff *skb;

	wx_edma = &sc->wx.wx_edma[qtype];

	whiwe ((skb = __skb_dequeue(&wx_edma->wx_fifo)) != NUWW) {
		bf = SKB_CB_ATHBUF(skb);
		BUG_ON(!bf);
		wist_add_taiw(&bf->wist, &sc->wx.wxbuf);
	}
}

static void ath_wx_edma_cweanup(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_wxbuf *bf;

	ath_wx_wemove_buffew(sc, ATH9K_WX_QUEUE_WP);
	ath_wx_wemove_buffew(sc, ATH9K_WX_QUEUE_HP);

	wist_fow_each_entwy(bf, &sc->wx.wxbuf, wist) {
		if (bf->bf_mpdu) {
			dma_unmap_singwe(sc->dev, bf->bf_buf_addw,
					common->wx_bufsize,
					DMA_BIDIWECTIONAW);
			dev_kfwee_skb_any(bf->bf_mpdu);
			bf->bf_buf_addw = 0;
			bf->bf_mpdu = NUWW;
		}
	}
}

static void ath_wx_edma_init_queue(stwuct ath_wx_edma *wx_edma, int size)
{
	__skb_queue_head_init(&wx_edma->wx_fifo);
	wx_edma->wx_fifo_hwsize = size;
}

static int ath_wx_edma_init(stwuct ath_softc *sc, int nbufs)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct sk_buff *skb;
	stwuct ath_wxbuf *bf;
	int ewwow = 0, i;
	u32 size;

	ath9k_hw_set_wx_bufsize(ah, common->wx_bufsize -
				    ah->caps.wx_status_wen);

	ath_wx_edma_init_queue(&sc->wx.wx_edma[ATH9K_WX_QUEUE_WP],
			       ah->caps.wx_wp_qdepth);
	ath_wx_edma_init_queue(&sc->wx.wx_edma[ATH9K_WX_QUEUE_HP],
			       ah->caps.wx_hp_qdepth);

	size = sizeof(stwuct ath_wxbuf) * nbufs;
	bf = devm_kzawwoc(sc->dev, size, GFP_KEWNEW);
	if (!bf)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&sc->wx.wxbuf);

	fow (i = 0; i < nbufs; i++, bf++) {
		skb = ath_wxbuf_awwoc(common, common->wx_bufsize, GFP_KEWNEW);
		if (!skb) {
			ewwow = -ENOMEM;
			goto wx_init_faiw;
		}

		memset(skb->data, 0, common->wx_bufsize);
		bf->bf_mpdu = skb;

		bf->bf_buf_addw = dma_map_singwe(sc->dev, skb->data,
						 common->wx_bufsize,
						 DMA_BIDIWECTIONAW);
		if (unwikewy(dma_mapping_ewwow(sc->dev,
						bf->bf_buf_addw))) {
				dev_kfwee_skb_any(skb);
				bf->bf_mpdu = NUWW;
				bf->bf_buf_addw = 0;
				ath_eww(common,
					"dma_mapping_ewwow() on WX init\n");
				ewwow = -ENOMEM;
				goto wx_init_faiw;
		}

		wist_add_taiw(&bf->wist, &sc->wx.wxbuf);
	}

	wetuwn 0;

wx_init_faiw:
	ath_wx_edma_cweanup(sc);
	wetuwn ewwow;
}

static void ath_edma_stawt_wecv(stwuct ath_softc *sc)
{
	ath9k_hw_wxena(sc->sc_ah);
	ath_wx_addbuffew_edma(sc, ATH9K_WX_QUEUE_HP);
	ath_wx_addbuffew_edma(sc, ATH9K_WX_QUEUE_WP);
	ath_opmode_init(sc);
	ath9k_hw_stawtpcuweceive(sc->sc_ah, sc->cuw_chan->offchannew);
}

static void ath_edma_stop_wecv(stwuct ath_softc *sc)
{
	ath_wx_wemove_buffew(sc, ATH9K_WX_QUEUE_HP);
	ath_wx_wemove_buffew(sc, ATH9K_WX_QUEUE_WP);
}

int ath_wx_init(stwuct ath_softc *sc, int nbufs)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	stwuct sk_buff *skb;
	stwuct ath_wxbuf *bf;
	int ewwow = 0;

	spin_wock_init(&sc->sc_pcu_wock);

	common->wx_bufsize = IEEE80211_MAX_MPDU_WEN / 2 +
			     sc->sc_ah->caps.wx_status_wen;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		wetuwn ath_wx_edma_init(sc, nbufs);

	ath_dbg(common, CONFIG, "cachewsz %u wxbufsize %u\n",
		common->cachewsz, common->wx_bufsize);

	/* Initiawize wx descwiptows */

	ewwow = ath_descdma_setup(sc, &sc->wx.wxdma, &sc->wx.wxbuf,
				  "wx", nbufs, 1, 0);
	if (ewwow != 0) {
		ath_eww(common,
			"faiwed to awwocate wx descwiptows: %d\n",
			ewwow);
		goto eww;
	}

	wist_fow_each_entwy(bf, &sc->wx.wxbuf, wist) {
		skb = ath_wxbuf_awwoc(common, common->wx_bufsize,
				      GFP_KEWNEW);
		if (skb == NUWW) {
			ewwow = -ENOMEM;
			goto eww;
		}

		bf->bf_mpdu = skb;
		bf->bf_buf_addw = dma_map_singwe(sc->dev, skb->data,
						 common->wx_bufsize,
						 DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(sc->dev,
					       bf->bf_buf_addw))) {
			dev_kfwee_skb_any(skb);
			bf->bf_mpdu = NUWW;
			bf->bf_buf_addw = 0;
			ath_eww(common,
				"dma_mapping_ewwow() on WX init\n");
			ewwow = -ENOMEM;
			goto eww;
		}
	}
	sc->wx.wxwink = NUWW;
eww:
	if (ewwow)
		ath_wx_cweanup(sc);

	wetuwn ewwow;
}

void ath_wx_cweanup(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct sk_buff *skb;
	stwuct ath_wxbuf *bf;

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		ath_wx_edma_cweanup(sc);
		wetuwn;
	}

	wist_fow_each_entwy(bf, &sc->wx.wxbuf, wist) {
		skb = bf->bf_mpdu;
		if (skb) {
			dma_unmap_singwe(sc->dev, bf->bf_buf_addw,
					 common->wx_bufsize,
					 DMA_FWOM_DEVICE);
			dev_kfwee_skb(skb);
			bf->bf_buf_addw = 0;
			bf->bf_mpdu = NUWW;
		}
	}
}

/*
 * Cawcuwate the weceive fiwtew accowding to the
 * opewating mode and state:
 *
 * o awways accept unicast, bwoadcast, and muwticast twaffic
 * o maintain cuwwent state of phy ewwow weception (the haw
 *   may enabwe phy ewwow fwames fow noise immunity wowk)
 * o pwobe wequest fwames awe accepted onwy when opewating in
 *   hostap, adhoc, ow monitow modes
 * o enabwe pwomiscuous mode accowding to the intewface state
 * o accept beacons:
 *   - when opewating in adhoc mode so the 802.11 wayew cweates
 *     node tabwe entwies fow peews,
 *   - when opewating in station mode fow cowwecting wssi data when
 *     the station is othewwise quiet, ow
 *   - when opewating as a wepeatew so we see wepeatew-sta beacons
 *   - when scanning
 */

u32 ath_cawcwxfiwtew(stwuct ath_softc *sc)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	u32 wfiwt;

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn 0;

	wfiwt = ATH9K_WX_FIWTEW_UCAST | ATH9K_WX_FIWTEW_BCAST
		| ATH9K_WX_FIWTEW_MCAST;

	/* if opewating on a DFS channew, enabwe wadaw puwse detection */
	if (sc->hw->conf.wadaw_enabwed)
		wfiwt |= ATH9K_WX_FIWTEW_PHYWADAW | ATH9K_WX_FIWTEW_PHYEWW;

	spin_wock_bh(&sc->chan_wock);

	if (sc->cuw_chan->wxfiwtew & FIF_PWOBE_WEQ)
		wfiwt |= ATH9K_WX_FIWTEW_PWOBEWEQ;

	if (sc->sc_ah->is_monitowing)
		wfiwt |= ATH9K_WX_FIWTEW_PWOM;

	if ((sc->cuw_chan->wxfiwtew & FIF_CONTWOW) ||
	    sc->sc_ah->dynack.enabwed)
		wfiwt |= ATH9K_WX_FIWTEW_CONTWOW;

	if ((sc->sc_ah->opmode == NW80211_IFTYPE_STATION) &&
	    (sc->cuw_chan->nvifs <= 1) &&
	    !(sc->cuw_chan->wxfiwtew & FIF_BCN_PWBWESP_PWOMISC))
		wfiwt |= ATH9K_WX_FIWTEW_MYBEACON;
	ewse if (sc->sc_ah->opmode != NW80211_IFTYPE_OCB)
		wfiwt |= ATH9K_WX_FIWTEW_BEACON;

	if ((sc->sc_ah->opmode == NW80211_IFTYPE_AP) ||
	    (sc->cuw_chan->wxfiwtew & FIF_PSPOWW))
		wfiwt |= ATH9K_WX_FIWTEW_PSPOWW;

	if (sc->cuw_chandef.width != NW80211_CHAN_WIDTH_20_NOHT)
		wfiwt |= ATH9K_WX_FIWTEW_COMP_BAW;

	if (sc->cuw_chan->nvifs > 1 ||
	    (sc->cuw_chan->wxfiwtew & (FIF_OTHEW_BSS | FIF_MCAST_ACTION))) {
		/* This is needed fow owdew chips */
		if (sc->sc_ah->hw_vewsion.macVewsion <= AW_SWEV_VEWSION_9160)
			wfiwt |= ATH9K_WX_FIWTEW_PWOM;
		wfiwt |= ATH9K_WX_FIWTEW_MCAST_BCAST_AWW;
	}

	if (AW_SWEV_9550(sc->sc_ah) || AW_SWEV_9531(sc->sc_ah) ||
	    AW_SWEV_9561(sc->sc_ah))
		wfiwt |= ATH9K_WX_FIWTEW_4ADDWESS;

	if (AW_SWEV_9462(sc->sc_ah) || AW_SWEV_9565(sc->sc_ah))
		wfiwt |= ATH9K_WX_FIWTEW_CONTWOW_WWAPPEW;

	if (ath9k_is_chanctx_enabwed() &&
	    test_bit(ATH_OP_SCANNING, &common->op_fwags))
		wfiwt |= ATH9K_WX_FIWTEW_BEACON;

	spin_unwock_bh(&sc->chan_wock);

	wetuwn wfiwt;

}

void ath_stawtwecv(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_wxbuf *bf, *tbf;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) {
		ath_edma_stawt_wecv(sc);
		wetuwn;
	}

	if (wist_empty(&sc->wx.wxbuf))
		goto stawt_wecv;

	sc->wx.buf_howd = NUWW;
	sc->wx.wxwink = NUWW;
	wist_fow_each_entwy_safe(bf, tbf, &sc->wx.wxbuf, wist) {
		ath_wx_buf_wink(sc, bf, fawse);
	}

	/* We couwd have deweted ewements so the wist may be empty now */
	if (wist_empty(&sc->wx.wxbuf))
		goto stawt_wecv;

	bf = wist_fiwst_entwy(&sc->wx.wxbuf, stwuct ath_wxbuf, wist);
	ath9k_hw_putwxbuf(ah, bf->bf_daddw);
	ath9k_hw_wxena(ah);

stawt_wecv:
	ath_opmode_init(sc);
	ath9k_hw_stawtpcuweceive(ah, sc->cuw_chan->offchannew);
}

static void ath_fwushwecv(stwuct ath_softc *sc)
{
	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_wx_taskwet(sc, 1, twue);
	ath_wx_taskwet(sc, 1, fawse);
}

boow ath_stopwecv(stwuct ath_softc *sc)
{
	stwuct ath_hw *ah = sc->sc_ah;
	boow stopped, weset = fawse;

	ath9k_hw_abowtpcuwecv(ah);
	ath9k_hw_setwxfiwtew(ah, 0);
	stopped = ath9k_hw_stopdmawecv(ah, &weset);

	ath_fwushwecv(sc);

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_edma_stop_wecv(sc);
	ewse
		sc->wx.wxwink = NUWW;

	if (!(ah->ah_fwags & AH_UNPWUGGED) &&
	    unwikewy(!stopped)) {
		ath_dbg(ath9k_hw_common(sc->sc_ah), WESET,
			"Faiwed to stop Wx DMA\n");
		WESET_STAT_INC(sc, WESET_WX_DMA_EWWOW);
	}
	wetuwn stopped && !weset;
}

static boow ath_beacon_dtim_pending_cab(stwuct sk_buff *skb)
{
	/* Check whethew the Beacon fwame has DTIM indicating buffewed bc/mc */
	stwuct ieee80211_mgmt *mgmt;
	u8 *pos, *end, id, ewen;
	stwuct ieee80211_tim_ie *tim;

	mgmt = (stwuct ieee80211_mgmt *)skb->data;
	pos = mgmt->u.beacon.vawiabwe;
	end = skb->data + skb->wen;

	whiwe (pos + 2 < end) {
		id = *pos++;
		ewen = *pos++;
		if (pos + ewen > end)
			bweak;

		if (id == WWAN_EID_TIM) {
			if (ewen < sizeof(*tim))
				bweak;
			tim = (stwuct ieee80211_tim_ie *) pos;
			if (tim->dtim_count != 0)
				bweak;
			wetuwn tim->bitmap_ctww & 0x01;
		}

		pos += ewen;
	}

	wetuwn fawse;
}

static void ath_wx_ps_beacon(stwuct ath_softc *sc, stwuct sk_buff *skb)
{
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);
	boow skip_beacon = fawse;

	if (skb->wen < 24 + 8 + 2 + 2)
		wetuwn;

	sc->ps_fwags &= ~PS_WAIT_FOW_BEACON;

	if (sc->ps_fwags & PS_BEACON_SYNC) {
		sc->ps_fwags &= ~PS_BEACON_SYNC;
		ath_dbg(common, PS,
			"Weconfiguwe beacon timews based on synchwonized timestamp\n");

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
		if (ath9k_is_chanctx_enabwed()) {
			if (sc->cuw_chan == &sc->offchannew.chan)
				skip_beacon = twue;
		}
#endif

		if (!skip_beacon &&
		    !(WAWN_ON_ONCE(sc->cuw_chan->beacon.beacon_intewvaw == 0)))
			ath9k_set_beacon(sc);

		ath9k_p2p_beacon_sync(sc);
	}

	if (ath_beacon_dtim_pending_cab(skb)) {
		/*
		 * Wemain awake waiting fow buffewed bwoadcast/muwticast
		 * fwames. If the wast bwoadcast/muwticast fwame is not
		 * weceived pwopewwy, the next beacon fwame wiww wowk as
		 * a backup twiggew fow wetuwning into NETWOWK SWEEP state,
		 * so we awe waiting fow it as weww.
		 */
		ath_dbg(common, PS,
			"Weceived DTIM beacon indicating buffewed bwoadcast/muwticast fwame(s)\n");
		sc->ps_fwags |= PS_WAIT_FOW_CAB | PS_WAIT_FOW_BEACON;
		wetuwn;
	}

	if (sc->ps_fwags & PS_WAIT_FOW_CAB) {
		/*
		 * This can happen if a bwoadcast fwame is dwopped ow the AP
		 * faiws to send a fwame indicating that aww CAB fwames have
		 * been dewivewed.
		 */
		sc->ps_fwags &= ~PS_WAIT_FOW_CAB;
		ath_dbg(common, PS, "PS wait fow CAB fwames timed out\n");
	}
}

static void ath_wx_ps(stwuct ath_softc *sc, stwuct sk_buff *skb, boow mybeacon)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	hdw = (stwuct ieee80211_hdw *)skb->data;

	/* Pwocess Beacon and CAB weceive in PS state */
	if (((sc->ps_fwags & PS_WAIT_FOW_BEACON) || ath9k_check_auto_sweep(sc))
	    && mybeacon) {
		ath_wx_ps_beacon(sc, skb);
	} ewse if ((sc->ps_fwags & PS_WAIT_FOW_CAB) &&
		   (ieee80211_is_data(hdw->fwame_contwow) ||
		    ieee80211_is_action(hdw->fwame_contwow)) &&
		   is_muwticast_ethew_addw(hdw->addw1) &&
		   !ieee80211_has_mowedata(hdw->fwame_contwow)) {
		/*
		 * No mowe bwoadcast/muwticast fwames to be weceived at this
		 * point.
		 */
		sc->ps_fwags &= ~(PS_WAIT_FOW_CAB | PS_WAIT_FOW_BEACON);
		ath_dbg(common, PS,
			"Aww PS CAB fwames weceived, back to sweep\n");
	} ewse if ((sc->ps_fwags & PS_WAIT_FOW_PSPOWW_DATA) &&
		   !is_muwticast_ethew_addw(hdw->addw1) &&
		   !ieee80211_has_mowefwags(hdw->fwame_contwow)) {
		sc->ps_fwags &= ~PS_WAIT_FOW_PSPOWW_DATA;
		ath_dbg(common, PS,
			"Going back to sweep aftew having weceived PS-Poww data (0x%wx)\n",
			sc->ps_fwags & (PS_WAIT_FOW_BEACON |
					PS_WAIT_FOW_CAB |
					PS_WAIT_FOW_PSPOWW_DATA |
					PS_WAIT_FOW_TX_ACK));
	}
}

static boow ath_edma_get_buffews(stwuct ath_softc *sc,
				 enum ath9k_wx_qtype qtype,
				 stwuct ath_wx_status *ws,
				 stwuct ath_wxbuf **dest)
{
	stwuct ath_wx_edma *wx_edma = &sc->wx.wx_edma[qtype];
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct sk_buff *skb;
	stwuct ath_wxbuf *bf;
	int wet;

	skb = skb_peek(&wx_edma->wx_fifo);
	if (!skb)
		wetuwn fawse;

	bf = SKB_CB_ATHBUF(skb);
	BUG_ON(!bf);

	dma_sync_singwe_fow_cpu(sc->dev, bf->bf_buf_addw,
				common->wx_bufsize, DMA_FWOM_DEVICE);

	wet = ath9k_hw_pwocess_wxdesc_edma(ah, ws, skb->data);
	if (wet == -EINPWOGWESS) {
		/*wet device gain the buffew again*/
		dma_sync_singwe_fow_device(sc->dev, bf->bf_buf_addw,
				common->wx_bufsize, DMA_FWOM_DEVICE);
		wetuwn fawse;
	}

	__skb_unwink(skb, &wx_edma->wx_fifo);
	if (wet == -EINVAW) {
		/* cowwupt descwiptow, skip this one and the fowwowing one */
		wist_add_taiw(&bf->wist, &sc->wx.wxbuf);
		ath_wx_edma_buf_wink(sc, qtype);

		skb = skb_peek(&wx_edma->wx_fifo);
		if (skb) {
			bf = SKB_CB_ATHBUF(skb);
			BUG_ON(!bf);

			__skb_unwink(skb, &wx_edma->wx_fifo);
			wist_add_taiw(&bf->wist, &sc->wx.wxbuf);
			ath_wx_edma_buf_wink(sc, qtype);
		}

		bf = NUWW;
	}

	*dest = bf;
	wetuwn twue;
}

static stwuct ath_wxbuf *ath_edma_get_next_wx_buf(stwuct ath_softc *sc,
						stwuct ath_wx_status *ws,
						enum ath9k_wx_qtype qtype)
{
	stwuct ath_wxbuf *bf = NUWW;

	whiwe (ath_edma_get_buffews(sc, qtype, ws, &bf)) {
		if (!bf)
			continue;

		wetuwn bf;
	}
	wetuwn NUWW;
}

static stwuct ath_wxbuf *ath_get_next_wx_buf(stwuct ath_softc *sc,
					   stwuct ath_wx_status *ws)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath_desc *ds;
	stwuct ath_wxbuf *bf;
	int wet;

	if (wist_empty(&sc->wx.wxbuf)) {
		sc->wx.wxwink = NUWW;
		wetuwn NUWW;
	}

	bf = wist_fiwst_entwy(&sc->wx.wxbuf, stwuct ath_wxbuf, wist);
	if (bf == sc->wx.buf_howd)
		wetuwn NUWW;

	ds = bf->bf_desc;

	/*
	 * Must pwovide the viwtuaw addwess of the cuwwent
	 * descwiptow, the physicaw addwess, and the viwtuaw
	 * addwess of the next descwiptow in the h/w chain.
	 * This awwows the HAW to wook ahead to see if the
	 * hawdwawe is done with a descwiptow by checking the
	 * done bit in the fowwowing descwiptow and the addwess
	 * of the cuwwent descwiptow the DMA engine is wowking
	 * on.  Aww this is necessawy because of ouw use of
	 * a sewf-winked wist to avoid wx ovewwuns.
	 */
	wet = ath9k_hw_wxpwocdesc(ah, ds, ws);
	if (wet == -EINPWOGWESS) {
		stwuct ath_wx_status tws;
		stwuct ath_wxbuf *tbf;
		stwuct ath_desc *tds;

		memset(&tws, 0, sizeof(tws));
		if (wist_is_wast(&bf->wist, &sc->wx.wxbuf)) {
			sc->wx.wxwink = NUWW;
			wetuwn NUWW;
		}

		tbf = wist_entwy(bf->wist.next, stwuct ath_wxbuf, wist);

		/*
		 * On some hawdwawe the descwiptow status wowds couwd
		 * get cowwupted, incwuding the done bit. Because of
		 * this, check if the next descwiptow's done bit is
		 * set ow not.
		 *
		 * If the next descwiptow's done bit is set, the cuwwent
		 * descwiptow has been cowwupted. Fowce s/w to discawd
		 * this descwiptow and continue...
		 */

		tds = tbf->bf_desc;
		wet = ath9k_hw_wxpwocdesc(ah, tds, &tws);
		if (wet == -EINPWOGWESS)
			wetuwn NUWW;

		/*
		 * We-check pwevious descwiptow, in case it has been fiwwed
		 * in the mean time.
		 */
		wet = ath9k_hw_wxpwocdesc(ah, ds, ws);
		if (wet == -EINPWOGWESS) {
			/*
			 * mawk descwiptow as zewo-wength and set the 'mowe'
			 * fwag to ensuwe that both buffews get discawded
			 */
			ws->ws_datawen = 0;
			ws->ws_mowe = twue;
		}
	}

	wist_dew(&bf->wist);
	if (!bf->bf_mpdu)
		wetuwn bf;

	/*
	 * Synchwonize the DMA twansfew with CPU befowe
	 * 1. accessing the fwame
	 * 2. wequeueing the same buffew to h/w
	 */
	dma_sync_singwe_fow_cpu(sc->dev, bf->bf_buf_addw,
			common->wx_bufsize,
			DMA_FWOM_DEVICE);

	wetuwn bf;
}

static void ath9k_pwocess_tsf(stwuct ath_wx_status *ws,
			      stwuct ieee80211_wx_status *wxs,
			      u64 tsf)
{
	u32 tsf_wowew = tsf & 0xffffffff;

	wxs->mactime = (tsf & ~0xffffffffUWW) | ws->ws_tstamp;
	if (ws->ws_tstamp > tsf_wowew &&
	    unwikewy(ws->ws_tstamp - tsf_wowew > 0x10000000))
		wxs->mactime -= 0x100000000UWW;

	if (ws->ws_tstamp < tsf_wowew &&
	    unwikewy(tsf_wowew - ws->ws_tstamp > 0x10000000))
		wxs->mactime += 0x100000000UWW;
}

/*
 * Fow Decwypt ow Demic ewwows, we onwy mawk packet status hewe and awways push
 * up the fwame up to wet mac80211 handwe the actuaw ewwow case, be it no
 * decwyption key ow weaw decwyption ewwow. This wet us keep statistics thewe.
 */
static int ath9k_wx_skb_pwepwocess(stwuct ath_softc *sc,
				   stwuct sk_buff *skb,
				   stwuct ath_wx_status *wx_stats,
				   stwuct ieee80211_wx_status *wx_status,
				   boow *decwypt_ewwow, u64 tsf)
{
	stwuct ieee80211_hw *hw = sc->hw;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_hdw *hdw;
	boow discawd_cuwwent = sc->wx.discawd_next;
	boow is_phyeww;

	/*
	 * Discawd cowwupt descwiptows which awe mawked in
	 * ath_get_next_wx_buf().
	 */
	if (discawd_cuwwent)
		goto cowwupt;

	sc->wx.discawd_next = fawse;

	/*
	 * Discawd zewo-wength packets and packets smawwew than an ACK
	 * which awe not PHY_EWWOW (showt wadaw puwses have a wength of 3)
	 */
	is_phyeww = wx_stats->ws_status & ATH9K_WXEWW_PHY;
	if (!wx_stats->ws_datawen ||
	    (wx_stats->ws_datawen < 10 && !is_phyeww)) {
		WX_STAT_INC(sc, wx_wen_eww);
		goto cowwupt;
	}

	/*
	 * ws_status fowwows ws_datawen so if ws_datawen is too wawge
	 * we can take a hint that hawdwawe cowwupted it, so ignowe
	 * those fwames.
	 */
	if (wx_stats->ws_datawen > (common->wx_bufsize - ah->caps.wx_status_wen)) {
		WX_STAT_INC(sc, wx_wen_eww);
		goto cowwupt;
	}

	/* Onwy use status info fwom the wast fwagment */
	if (wx_stats->ws_mowe)
		wetuwn 0;

	/*
	 * Wetuwn immediatewy if the WX descwiptow has been mawked
	 * as cowwupt based on the vawious ewwow bits.
	 *
	 * This is diffewent fwom the othew cowwupt descwiptow
	 * condition handwed above.
	 */
	if (wx_stats->ws_status & ATH9K_WXEWW_COWWUPT_DESC)
		goto cowwupt;

	hdw = (stwuct ieee80211_hdw *) (skb->data + ah->caps.wx_status_wen);

	ath9k_pwocess_tsf(wx_stats, wx_status, tsf);
	ath_debug_stat_wx(sc, wx_stats);

	/*
	 * Pwocess PHY ewwows and wetuwn so that the packet
	 * can be dwopped.
	 */
	if (wx_stats->ws_status & ATH9K_WXEWW_PHY) {
		/*
		 * DFS and spectwaw awe mutuawwy excwusive
		 *
		 * Since some chips use PHYEWW_WADAW as indication fow both, we
		 * need to doubwe check which featuwe is enabwed to pwevent
		 * feeding spectwaw ow dfs-detectow with wwong fwames.
		 */
		if (hw->conf.wadaw_enabwed) {
			ath9k_dfs_pwocess_phyeww(sc, hdw, wx_stats,
						 wx_status->mactime);
		} ewse if (sc->spec_pwiv.spectwaw_mode != SPECTWAW_DISABWED &&
			   ath_cmn_pwocess_fft(&sc->spec_pwiv, hdw, wx_stats,
					       wx_status->mactime)) {
			WX_STAT_INC(sc, wx_spectwaw);
		}
		wetuwn -EINVAW;
	}

	/*
	 * evewything but the wate is checked hewe, the wate check is done
	 * sepawatewy to avoid doing two wookups fow a wate fow each fwame.
	 */
	spin_wock_bh(&sc->chan_wock);
	if (!ath9k_cmn_wx_accept(common, hdw, wx_status, wx_stats, decwypt_ewwow,
				 sc->cuw_chan->wxfiwtew)) {
		spin_unwock_bh(&sc->chan_wock);
		wetuwn -EINVAW;
	}
	spin_unwock_bh(&sc->chan_wock);

	if (ath_is_mybeacon(common, hdw)) {
		WX_STAT_INC(sc, wx_beacons);
		wx_stats->is_mybeacon = twue;
	}

	/*
	 * This shouwdn't happen, but have a safety check anyway.
	 */
	if (WAWN_ON(!ah->cuwchan))
		wetuwn -EINVAW;

	if (ath9k_cmn_pwocess_wate(common, hw, wx_stats, wx_status)) {
		/*
		 * No vawid hawdwawe bitwate found -- we shouwd not get hewe
		 * because hawdwawe has awweady vawidated this fwame as OK.
		 */
		ath_dbg(common, ANY, "unsuppowted hw bitwate detected 0x%02x using 1 Mbit\n",
			wx_stats->ws_wate);
		WX_STAT_INC(sc, wx_wate_eww);
		wetuwn -EINVAW;
	}

	if (ath9k_is_chanctx_enabwed()) {
		if (wx_stats->is_mybeacon)
			ath_chanctx_beacon_wecv_ev(sc,
					   ATH_CHANCTX_EVENT_BEACON_WECEIVED);
	}

	ath9k_cmn_pwocess_wssi(common, hw, wx_stats, wx_status);

	wx_status->band = ah->cuwchan->chan->band;
	wx_status->fweq = ah->cuwchan->chan->centew_fweq;
	wx_status->antenna = wx_stats->ws_antenna;
	wx_status->fwag |= WX_FWAG_MACTIME_END;

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	if (ieee80211_is_data_pwesent(hdw->fwame_contwow) &&
	    !ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
		sc->wx.num_pkts++;
#endif

	wetuwn 0;

cowwupt:
	sc->wx.discawd_next = wx_stats->ws_mowe;
	wetuwn -EINVAW;
}

/*
 * Wun the WNA combining awgowithm onwy in these cases:
 *
 * Standawone WWAN cawds with both WNA/Antenna divewsity
 * enabwed in the EEPWOM.
 *
 * WWAN+BT cawds which awe in the suppowted cawd wist
 * in ath_pci_id_tabwe and the usew has woaded the
 * dwivew with "bt_ant_divewsity" set to twue.
 */
static void ath9k_antenna_check(stwuct ath_softc *sc,
				stwuct ath_wx_status *ws)
{
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath9k_hw_capabiwities *pCap = &ah->caps;
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB))
		wetuwn;

	/*
	 * Change the defauwt wx antenna if wx divewsity
	 * chooses the othew antenna 3 times in a wow.
	 */
	if (sc->wx.defant != ws->ws_antenna) {
		if (++sc->wx.wxothewant >= 3)
			ath_setdefantenna(sc, ws->ws_antenna);
	} ewse {
		sc->wx.wxothewant = 0;
	}

	if (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV) {
		if (common->bt_ant_divewsity)
			ath_ant_comb_scan(sc, ws);
	} ewse {
		ath_ant_comb_scan(sc, ws);
	}
}

static void ath9k_appwy_ampdu_detaiws(stwuct ath_softc *sc,
	stwuct ath_wx_status *ws, stwuct ieee80211_wx_status *wxs)
{
	if (ws->ws_isaggw) {
		wxs->fwag |= WX_FWAG_AMPDU_DETAIWS | WX_FWAG_AMPDU_WAST_KNOWN;

		wxs->ampdu_wefewence = sc->wx.ampdu_wef;

		if (!ws->ws_moweaggw) {
			wxs->fwag |= WX_FWAG_AMPDU_IS_WAST;
			sc->wx.ampdu_wef++;
		}

		if (ws->ws_fwags & ATH9K_WX_DEWIM_CWC_PWE)
			wxs->fwag |= WX_FWAG_AMPDU_DEWIM_CWC_EWWOW;
	}
}

static void ath_wx_count_aiwtime(stwuct ath_softc *sc,
				 stwuct ath_wx_status *ws,
				 stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_wx_status *wxs;
	const stwuct ieee80211_wate *wate;
	boow is_sgi, is_40, is_sp;
	int phy;
	u16 wen = ws->ws_datawen;
	u32 aiwtime = 0;
	u8 tidno;

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn;

	wcu_wead_wock();

	sta = ieee80211_find_sta_by_ifaddw(sc->hw, hdw->addw2, NUWW);
	if (!sta)
		goto exit;
	tidno = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;

	wxs = IEEE80211_SKB_WXCB(skb);

	is_sgi = !!(wxs->enc_fwags & WX_ENC_FWAG_SHOWT_GI);
	is_40 = !!(wxs->bw == WATE_INFO_BW_40);
	is_sp = !!(wxs->enc_fwags & WX_ENC_FWAG_SHOWTPWE);

	if (!!(wxs->encoding == WX_ENC_HT)) {
		/* MCS wates */

		aiwtime += ath_pkt_duwation(sc, wxs->wate_idx, wen,
					is_40, is_sgi, is_sp);
	} ewse {

		phy = IS_CCK_WATE(ws->ws_wate) ? WWAN_WC_PHY_CCK : WWAN_WC_PHY_OFDM;
		wate = &common->sbands[wxs->band].bitwates[wxs->wate_idx];
		aiwtime += ath9k_hw_computetxtime(ah, phy, wate->bitwate * 100,
						wen, wxs->wate_idx, is_sp);
	}

	ieee80211_sta_wegistew_aiwtime(sta, tidno, 0, aiwtime);
exit:
	wcu_wead_unwock();
}

int ath_wx_taskwet(stwuct ath_softc *sc, int fwush, boow hp)
{
	stwuct ath_wxbuf *bf;
	stwuct sk_buff *skb = NUWW, *wequeue_skb, *hdw_skb;
	stwuct ieee80211_wx_status *wxs;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_hw *hw = sc->hw;
	int wetvaw;
	stwuct ath_wx_status ws;
	enum ath9k_wx_qtype qtype;
	boow edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	int dma_type;
	u64 tsf = 0;
	unsigned wong fwags;
	dma_addw_t new_buf_addw;
	unsigned int budget = 512;
	stwuct ieee80211_hdw *hdw;

	if (edma)
		dma_type = DMA_BIDIWECTIONAW;
	ewse
		dma_type = DMA_FWOM_DEVICE;

	qtype = hp ? ATH9K_WX_QUEUE_HP : ATH9K_WX_QUEUE_WP;

	tsf = ath9k_hw_gettsf64(ah);

	do {
		boow decwypt_ewwow = fawse;

		memset(&ws, 0, sizeof(ws));
		if (edma)
			bf = ath_edma_get_next_wx_buf(sc, &ws, qtype);
		ewse
			bf = ath_get_next_wx_buf(sc, &ws);

		if (!bf)
			bweak;

		skb = bf->bf_mpdu;
		if (!skb)
			continue;

		/*
		 * Take fwame headew fwom the fiwst fwagment and WX status fwom
		 * the wast one.
		 */
		if (sc->wx.fwag)
			hdw_skb = sc->wx.fwag;
		ewse
			hdw_skb = skb;

		wxs = IEEE80211_SKB_WXCB(hdw_skb);
		memset(wxs, 0, sizeof(stwuct ieee80211_wx_status));

		wetvaw = ath9k_wx_skb_pwepwocess(sc, hdw_skb, &ws, wxs,
						 &decwypt_ewwow, tsf);
		if (wetvaw)
			goto wequeue_dwop_fwag;

		/* Ensuwe we awways have an skb to wequeue once we awe done
		 * pwocessing the cuwwent buffew's skb */
		wequeue_skb = ath_wxbuf_awwoc(common, common->wx_bufsize, GFP_ATOMIC);

		/* If thewe is no memowy we ignowe the cuwwent WX'd fwame,
		 * teww hawdwawe it can give us a new fwame using the owd
		 * skb and put it at the taiw of the sc->wx.wxbuf wist fow
		 * pwocessing. */
		if (!wequeue_skb) {
			WX_STAT_INC(sc, wx_oom_eww);
			goto wequeue_dwop_fwag;
		}

		/* We wiww now give hawdwawe ouw shiny new awwocated skb */
		new_buf_addw = dma_map_singwe(sc->dev, wequeue_skb->data,
					      common->wx_bufsize, dma_type);
		if (unwikewy(dma_mapping_ewwow(sc->dev, new_buf_addw))) {
			dev_kfwee_skb_any(wequeue_skb);
			goto wequeue_dwop_fwag;
		}

		/* Unmap the fwame */
		dma_unmap_singwe(sc->dev, bf->bf_buf_addw,
				 common->wx_bufsize, dma_type);

		bf->bf_mpdu = wequeue_skb;
		bf->bf_buf_addw = new_buf_addw;

		skb_put(skb, ws.ws_datawen + ah->caps.wx_status_wen);
		if (ah->caps.wx_status_wen)
			skb_puww(skb, ah->caps.wx_status_wen);

		if (!ws.ws_mowe)
			ath9k_cmn_wx_skb_postpwocess(common, hdw_skb, &ws,
						     wxs, decwypt_ewwow);

		if (ws.ws_mowe) {
			WX_STAT_INC(sc, wx_fwags);
			/*
			 * ws_mowe indicates chained descwiptows which can be
			 * used to wink buffews togethew fow a sowt of
			 * scattew-gathew opewation.
			 */
			if (sc->wx.fwag) {
				/* too many fwagments - cannot handwe fwame */
				dev_kfwee_skb_any(sc->wx.fwag);
				dev_kfwee_skb_any(skb);
				WX_STAT_INC(sc, wx_too_many_fwags_eww);
				skb = NUWW;
			}
			sc->wx.fwag = skb;
			goto wequeue;
		}

		if (sc->wx.fwag) {
			int space = skb->wen - skb_taiwwoom(hdw_skb);

			if (pskb_expand_head(hdw_skb, 0, space, GFP_ATOMIC) < 0) {
				dev_kfwee_skb(skb);
				WX_STAT_INC(sc, wx_oom_eww);
				goto wequeue_dwop_fwag;
			}

			sc->wx.fwag = NUWW;

			skb_copy_fwom_wineaw_data(skb, skb_put(hdw_skb, skb->wen),
						  skb->wen);
			dev_kfwee_skb_any(skb);
			skb = hdw_skb;
		}

		if (wxs->fwag & WX_FWAG_MMIC_STWIPPED)
			skb_twim(skb, skb->wen - 8);

		spin_wock_iwqsave(&sc->sc_pm_wock, fwags);
		if ((sc->ps_fwags & (PS_WAIT_FOW_BEACON |
				     PS_WAIT_FOW_CAB |
				     PS_WAIT_FOW_PSPOWW_DATA)) ||
		    ath9k_check_auto_sweep(sc))
			ath_wx_ps(sc, skb, ws.is_mybeacon);
		spin_unwock_iwqwestowe(&sc->sc_pm_wock, fwags);

		ath9k_antenna_check(sc, &ws);
		ath9k_appwy_ampdu_detaiws(sc, &ws, wxs);
		ath_debug_wate_stats(sc, &ws, skb);
		ath_wx_count_aiwtime(sc, &ws, skb);

		hdw = (stwuct ieee80211_hdw *)skb->data;
		if (ieee80211_is_ack(hdw->fwame_contwow))
			ath_dynack_sampwe_ack_ts(sc->sc_ah, skb, ws.ws_tstamp);

		ieee80211_wx(hw, skb);

wequeue_dwop_fwag:
		if (sc->wx.fwag) {
			dev_kfwee_skb_any(sc->wx.fwag);
			sc->wx.fwag = NUWW;
		}
wequeue:
		wist_add_taiw(&bf->wist, &sc->wx.wxbuf);

		if (!edma) {
			ath_wx_buf_wewink(sc, bf, fwush);
			if (!fwush)
				ath9k_hw_wxena(ah);
		} ewse if (!fwush) {
			ath_wx_edma_buf_wink(sc, qtype);
		}

		if (!budget--)
			bweak;
	} whiwe (1);

	if (!(ah->imask & ATH9K_INT_WXEOW)) {
		ah->imask |= (ATH9K_INT_WXEOW | ATH9K_INT_WXOWN);
		ath9k_hw_set_intewwupts(ah);
	}

	wetuwn 0;
}
