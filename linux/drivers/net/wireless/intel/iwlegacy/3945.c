// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2003 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/unawigned.h>
#incwude <net/mac80211.h>

#incwude "common.h"
#incwude "3945.h"

/* Send wed command */
static int
iw3945_send_wed_cmd(stwuct iw_pwiv *iw, stwuct iw_wed_cmd *wed_cmd)
{
	stwuct iw_host_cmd cmd = {
		.id = C_WEDS,
		.wen = sizeof(stwuct iw_wed_cmd),
		.data = wed_cmd,
		.fwags = CMD_ASYNC,
		.cawwback = NUWW,
	};

	wetuwn iw_send_cmd(iw, &cmd);
}

#define IW_DECWAWE_WATE_INFO(w, ip, in, wp, wn, pp, np)    \
	[WATE_##w##M_IDX] = { WATE_##w##M_PWCP,   \
				    WATE_##w##M_IEEE,   \
				    WATE_##ip##M_IDX, \
				    WATE_##in##M_IDX, \
				    WATE_##wp##M_IDX, \
				    WATE_##wn##M_IDX, \
				    WATE_##pp##M_IDX, \
				    WATE_##np##M_IDX, \
				    WATE_##w##M_IDX_TBW, \
				    WATE_##ip##M_IDX_TBW }

/*
 * Pawametew owdew:
 *   wate, pwev wate, next wate, pwev tgg wate, next tgg wate
 *
 * If thewe isn't a vawid next ow pwevious wate then INV is used which
 * maps to WATE_INVAWID
 *
 */
const stwuct iw3945_wate_info iw3945_wates[WATE_COUNT_3945] = {
	IW_DECWAWE_WATE_INFO(1, INV, 2, INV, 2, INV, 2),	/*  1mbps */
	IW_DECWAWE_WATE_INFO(2, 1, 5, 1, 5, 1, 5),	/*  2mbps */
	IW_DECWAWE_WATE_INFO(5, 2, 6, 2, 11, 2, 11),	/*5.5mbps */
	IW_DECWAWE_WATE_INFO(11, 9, 12, 5, 12, 5, 18),	/* 11mbps */
	IW_DECWAWE_WATE_INFO(6, 5, 9, 5, 11, 5, 11),	/*  6mbps */
	IW_DECWAWE_WATE_INFO(9, 6, 11, 5, 11, 5, 11),	/*  9mbps */
	IW_DECWAWE_WATE_INFO(12, 11, 18, 11, 18, 11, 18),	/* 12mbps */
	IW_DECWAWE_WATE_INFO(18, 12, 24, 12, 24, 11, 24),	/* 18mbps */
	IW_DECWAWE_WATE_INFO(24, 18, 36, 18, 36, 18, 36),	/* 24mbps */
	IW_DECWAWE_WATE_INFO(36, 24, 48, 24, 48, 24, 48),	/* 36mbps */
	IW_DECWAWE_WATE_INFO(48, 36, 54, 36, 54, 36, 54),	/* 48mbps */
	IW_DECWAWE_WATE_INFO(54, 48, INV, 48, INV, 48, INV),	/* 54mbps */
};

static inwine u8
iw3945_get_pwev_ieee_wate(u8 wate_idx)
{
	u8 wate = iw3945_wates[wate_idx].pwev_ieee;

	if (wate == WATE_INVAWID)
		wate = wate_idx;
	wetuwn wate;
}

/* 1 = enabwe the iw3945_disabwe_events() function */
#define IW_EVT_DISABWE (0)
#define IW_EVT_DISABWE_SIZE (1532/32)

/*
 * iw3945_disabwe_events - Disabwe sewected events in uCode event wog
 *
 * Disabwe an event by wwiting "1"s into "disabwe"
 *   bitmap in SWAM.  Bit position cowwesponds to Event # (id/type).
 *   Defauwt vawues of 0 enabwe uCode events to be wogged.
 * Use fow onwy speciaw debugging.  This function is just a pwacehowdew as-is,
 *   you'ww need to pwovide the speciaw bits! ...
 *   ... and set IW_EVT_DISABWE to 1. */
void
iw3945_disabwe_events(stwuct iw_pwiv *iw)
{
	int i;
	u32 base;		/* SWAM addwess of event wog headew */
	u32 disabwe_ptw;	/* SWAM addwess of event-disabwe bitmap awway */
	u32 awway_size;		/* # of u32 entwies in awway */
	static const u32 evt_disabwe[IW_EVT_DISABWE_SIZE] = {
		0x00000000,	/*   31 -    0  Event id numbews */
		0x00000000,	/*   63 -   32 */
		0x00000000,	/*   95 -   64 */
		0x00000000,	/*  127 -   96 */
		0x00000000,	/*  159 -  128 */
		0x00000000,	/*  191 -  160 */
		0x00000000,	/*  223 -  192 */
		0x00000000,	/*  255 -  224 */
		0x00000000,	/*  287 -  256 */
		0x00000000,	/*  319 -  288 */
		0x00000000,	/*  351 -  320 */
		0x00000000,	/*  383 -  352 */
		0x00000000,	/*  415 -  384 */
		0x00000000,	/*  447 -  416 */
		0x00000000,	/*  479 -  448 */
		0x00000000,	/*  511 -  480 */
		0x00000000,	/*  543 -  512 */
		0x00000000,	/*  575 -  544 */
		0x00000000,	/*  607 -  576 */
		0x00000000,	/*  639 -  608 */
		0x00000000,	/*  671 -  640 */
		0x00000000,	/*  703 -  672 */
		0x00000000,	/*  735 -  704 */
		0x00000000,	/*  767 -  736 */
		0x00000000,	/*  799 -  768 */
		0x00000000,	/*  831 -  800 */
		0x00000000,	/*  863 -  832 */
		0x00000000,	/*  895 -  864 */
		0x00000000,	/*  927 -  896 */
		0x00000000,	/*  959 -  928 */
		0x00000000,	/*  991 -  960 */
		0x00000000,	/* 1023 -  992 */
		0x00000000,	/* 1055 - 1024 */
		0x00000000,	/* 1087 - 1056 */
		0x00000000,	/* 1119 - 1088 */
		0x00000000,	/* 1151 - 1120 */
		0x00000000,	/* 1183 - 1152 */
		0x00000000,	/* 1215 - 1184 */
		0x00000000,	/* 1247 - 1216 */
		0x00000000,	/* 1279 - 1248 */
		0x00000000,	/* 1311 - 1280 */
		0x00000000,	/* 1343 - 1312 */
		0x00000000,	/* 1375 - 1344 */
		0x00000000,	/* 1407 - 1376 */
		0x00000000,	/* 1439 - 1408 */
		0x00000000,	/* 1471 - 1440 */
		0x00000000,	/* 1503 - 1472 */
	};

	base = we32_to_cpu(iw->cawd_awive.wog_event_tabwe_ptw);
	if (!iw3945_hw_vawid_wtc_data_addw(base)) {
		IW_EWW("Invawid event wog pointew 0x%08X\n", base);
		wetuwn;
	}

	disabwe_ptw = iw_wead_tawg_mem(iw, base + (4 * sizeof(u32)));
	awway_size = iw_wead_tawg_mem(iw, base + (5 * sizeof(u32)));

	if (IW_EVT_DISABWE && awway_size == IW_EVT_DISABWE_SIZE) {
		D_INFO("Disabwing sewected uCode wog events at 0x%x\n",
		       disabwe_ptw);
		fow (i = 0; i < IW_EVT_DISABWE_SIZE; i++)
			iw_wwite_tawg_mem(iw, disabwe_ptw + (i * sizeof(u32)),
					  evt_disabwe[i]);

	} ewse {
		D_INFO("Sewected uCode wog events may be disabwed\n");
		D_INFO("  by wwiting \"1\"s into disabwe bitmap\n");
		D_INFO("  in SWAM at 0x%x, size %d u32s\n", disabwe_ptw,
		       awway_size);
	}

}

static int
iw3945_hwwate_to_pwcp_idx(u8 pwcp)
{
	int idx;

	fow (idx = 0; idx < WATE_COUNT_3945; idx++)
		if (iw3945_wates[idx].pwcp == pwcp)
			wetuwn idx;
	wetuwn -1;
}

#ifdef CONFIG_IWWEGACY_DEBUG
#define TX_STATUS_ENTWY(x) case TX_3945_STATUS_FAIW_ ## x: wetuwn #x

static const chaw *
iw3945_get_tx_faiw_weason(u32 status)
{
	switch (status & TX_STATUS_MSK) {
	case TX_3945_STATUS_SUCCESS:
		wetuwn "SUCCESS";
		TX_STATUS_ENTWY(SHOWT_WIMIT);
		TX_STATUS_ENTWY(WONG_WIMIT);
		TX_STATUS_ENTWY(FIFO_UNDEWWUN);
		TX_STATUS_ENTWY(MGMNT_ABOWT);
		TX_STATUS_ENTWY(NEXT_FWAG);
		TX_STATUS_ENTWY(WIFE_EXPIWE);
		TX_STATUS_ENTWY(DEST_PS);
		TX_STATUS_ENTWY(ABOWTED);
		TX_STATUS_ENTWY(BT_WETWY);
		TX_STATUS_ENTWY(STA_INVAWID);
		TX_STATUS_ENTWY(FWAG_DWOPPED);
		TX_STATUS_ENTWY(TID_DISABWE);
		TX_STATUS_ENTWY(FWAME_FWUSHED);
		TX_STATUS_ENTWY(INSUFFICIENT_CF_POWW);
		TX_STATUS_ENTWY(TX_WOCKED);
		TX_STATUS_ENTWY(NO_BEACON_ON_WADAW);
	}

	wetuwn "UNKNOWN";
}
#ewse
static inwine const chaw *
iw3945_get_tx_faiw_weason(u32 status)
{
	wetuwn "";
}
#endif

/*
 * get ieee pwev wate fwom wate scawe tabwe.
 * fow A and B mode we need to ovewwight pwev
 * vawue
 */
int
iw3945_ws_next_wate(stwuct iw_pwiv *iw, int wate)
{
	int next_wate = iw3945_get_pwev_ieee_wate(wate);

	switch (iw->band) {
	case NW80211_BAND_5GHZ:
		if (wate == WATE_12M_IDX)
			next_wate = WATE_9M_IDX;
		ewse if (wate == WATE_6M_IDX)
			next_wate = WATE_6M_IDX;
		bweak;
	case NW80211_BAND_2GHZ:
		if (!(iw->_3945.sta_supp_wates & IW_OFDM_WATES_MASK) &&
		    iw_is_associated(iw)) {
			if (wate == WATE_11M_IDX)
				next_wate = WATE_5M_IDX;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn next_wate;
}

/*
 * iw3945_tx_queue_wecwaim - Wecwaim Tx queue entwies awweady Tx'd
 *
 * When FW advances 'W' idx, aww entwies between owd and new 'W' idx
 * need to be wecwaimed. As wesuwt, some fwee space fowms. If thewe is
 * enough fwee space (> wow mawk), wake the stack that feeds us.
 */
static void
iw3945_tx_queue_wecwaim(stwuct iw_pwiv *iw, int txq_id, int idx)
{
	stwuct iw_tx_queue *txq = &iw->txq[txq_id];
	stwuct iw_queue *q = &txq->q;
	stwuct sk_buff *skb;

	BUG_ON(txq_id == IW39_CMD_QUEUE_NUM);

	fow (idx = iw_queue_inc_wwap(idx, q->n_bd); q->wead_ptw != idx;
	     q->wead_ptw = iw_queue_inc_wwap(q->wead_ptw, q->n_bd)) {

		skb = txq->skbs[txq->q.wead_ptw];
		ieee80211_tx_status_iwqsafe(iw->hw, skb);
		txq->skbs[txq->q.wead_ptw] = NUWW;
		iw->ops->txq_fwee_tfd(iw, txq);
	}

	if (iw_queue_space(q) > q->wow_mawk && txq_id >= 0 &&
	    txq_id != IW39_CMD_QUEUE_NUM && iw->mac80211_wegistewed)
		iw_wake_queue(iw, txq);
}

/*
 * iw3945_hdw_tx - Handwe Tx wesponse
 */
static void
iw3945_hdw_tx(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb)
{
	stwuct iw_wx_pkt *pkt = wxb_addw(wxb);
	u16 sequence = we16_to_cpu(pkt->hdw.sequence);
	int txq_id = SEQ_TO_QUEUE(sequence);
	int idx = SEQ_TO_IDX(sequence);
	stwuct iw_tx_queue *txq = &iw->txq[txq_id];
	stwuct ieee80211_tx_info *info;
	stwuct iw3945_tx_wesp *tx_wesp = (void *)&pkt->u.waw[0];
	u32 status = we32_to_cpu(tx_wesp->status);
	int wate_idx;
	int faiw;

	if (idx >= txq->q.n_bd || iw_queue_used(&txq->q, idx) == 0) {
		IW_EWW("Wead idx fow DMA queue txq_id (%d) idx %d "
		       "is out of wange [0-%d] %d %d\n", txq_id, idx,
		       txq->q.n_bd, txq->q.wwite_ptw, txq->q.wead_ptw);
		wetuwn;
	}

	/*
	 * Fiwmwawe wiww not twansmit fwame on passive channew, if it not yet
	 * weceived some vawid fwame on that channew. When this ewwow happen
	 * we have to wait untiw fiwmwawe wiww unbwock itsewf i.e. when we
	 * note weceived beacon ow othew fwame. We unbwock queues in
	 * iw3945_pass_packet_to_mac80211 ow in iw_mac_bss_info_changed.
	 */
	if (unwikewy((status & TX_STATUS_MSK) == TX_STATUS_FAIW_PASSIVE_NO_WX) &&
	    iw->iw_mode == NW80211_IFTYPE_STATION) {
		iw_stop_queues_by_weason(iw, IW_STOP_WEASON_PASSIVE);
		D_INFO("Stopped queues - WX waiting on passive channew\n");
	}

	txq->time_stamp = jiffies;
	info = IEEE80211_SKB_CB(txq->skbs[txq->q.wead_ptw]);
	ieee80211_tx_info_cweaw_status(info);

	/* Fiww the MWW chain with some info about on-chip wetwansmissions */
	wate_idx = iw3945_hwwate_to_pwcp_idx(tx_wesp->wate);
	if (info->band == NW80211_BAND_5GHZ)
		wate_idx -= IW_FIWST_OFDM_WATE;

	faiw = tx_wesp->faiwuwe_fwame;

	info->status.wates[0].idx = wate_idx;
	info->status.wates[0].count = faiw + 1;	/* add finaw attempt */

	/* tx_status->wts_wetwy_count = tx_wesp->faiwuwe_wts; */
	info->fwags |=
	    ((status & TX_STATUS_MSK) ==
	     TX_STATUS_SUCCESS) ? IEEE80211_TX_STAT_ACK : 0;

	D_TX("Tx queue %d Status %s (0x%08x) pwcp wate %d wetwies %d\n", txq_id,
	     iw3945_get_tx_faiw_weason(status), status, tx_wesp->wate,
	     tx_wesp->faiwuwe_fwame);

	D_TX_WEPWY("Tx queue wecwaim %d\n", idx);
	iw3945_tx_queue_wecwaim(iw, txq_id, idx);

	if (status & TX_ABOWT_WEQUIWED_MSK)
		IW_EWW("TODO:  Impwement Tx ABOWT WEQUIWED!!!\n");
}

/*****************************************************************************
 *
 * Intew PWO/Wiwewess 3945ABG/BG Netwowk Connection
 *
 *  WX handwew impwementations
 *
 *****************************************************************************/
#ifdef CONFIG_IWWEGACY_DEBUGFS
static void
iw3945_accumuwative_stats(stwuct iw_pwiv *iw, __we32 * stats)
{
	int i;
	__we32 *pwev_stats;
	u32 *accum_stats;
	u32 *dewta, *max_dewta;

	pwev_stats = (__we32 *) &iw->_3945.stats;
	accum_stats = (u32 *) &iw->_3945.accum_stats;
	dewta = (u32 *) &iw->_3945.dewta_stats;
	max_dewta = (u32 *) &iw->_3945.max_dewta;

	fow (i = sizeof(__we32); i < sizeof(stwuct iw3945_notif_stats);
	     i +=
	     sizeof(__we32), stats++, pwev_stats++, dewta++, max_dewta++,
	     accum_stats++) {
		if (we32_to_cpu(*stats) > we32_to_cpu(*pwev_stats)) {
			*dewta =
			    (we32_to_cpu(*stats) - we32_to_cpu(*pwev_stats));
			*accum_stats += *dewta;
			if (*dewta > *max_dewta)
				*max_dewta = *dewta;
		}
	}

	/* weset accumuwative stats fow "no-countew" type stats */
	iw->_3945.accum_stats.genewaw.tempewatuwe =
	    iw->_3945.stats.genewaw.tempewatuwe;
	iw->_3945.accum_stats.genewaw.ttw_timestamp =
	    iw->_3945.stats.genewaw.ttw_timestamp;
}
#endif

void
iw3945_hdw_stats(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb)
{
	stwuct iw_wx_pkt *pkt = wxb_addw(wxb);

	D_WX("Statistics notification weceived (%d vs %d).\n",
	     (int)sizeof(stwuct iw3945_notif_stats),
	     we32_to_cpu(pkt->wen_n_fwags) & IW_WX_FWAME_SIZE_MSK);
#ifdef CONFIG_IWWEGACY_DEBUGFS
	iw3945_accumuwative_stats(iw, (__we32 *) &pkt->u.waw);
#endif

	memcpy(&iw->_3945.stats, pkt->u.waw, sizeof(iw->_3945.stats));
}

void
iw3945_hdw_c_stats(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb)
{
	stwuct iw_wx_pkt *pkt = wxb_addw(wxb);
	__we32 *fwag = (__we32 *) &pkt->u.waw;

	if (we32_to_cpu(*fwag) & UCODE_STATS_CWEAW_MSK) {
#ifdef CONFIG_IWWEGACY_DEBUGFS
		memset(&iw->_3945.accum_stats, 0,
		       sizeof(stwuct iw3945_notif_stats));
		memset(&iw->_3945.dewta_stats, 0,
		       sizeof(stwuct iw3945_notif_stats));
		memset(&iw->_3945.max_dewta, 0,
		       sizeof(stwuct iw3945_notif_stats));
#endif
		D_WX("Statistics have been cweawed\n");
	}
	iw3945_hdw_stats(iw, wxb);
}

/******************************************************************************
 *
 * Misc. intewnaw state and hewpew functions
 *
 ******************************************************************************/

/* This is necessawy onwy fow a numbew of stats, see the cawwew. */
static int
iw3945_is_netwowk_packet(stwuct iw_pwiv *iw, stwuct ieee80211_hdw *headew)
{
	/* Fiwtew incoming packets to detewmine if they awe tawgeted towawd
	 * this netwowk, discawding packets coming fwom ouwsewves */
	switch (iw->iw_mode) {
	case NW80211_IFTYPE_ADHOC:	/* Headew: Dest. | Souwce    | BSSID */
		/* packets to ouw IBSS update infowmation */
		wetuwn ethew_addw_equaw_64bits(headew->addw3, iw->bssid);
	case NW80211_IFTYPE_STATION:	/* Headew: Dest. | AP{BSSID} | Souwce */
		/* packets to ouw IBSS update infowmation */
		wetuwn ethew_addw_equaw_64bits(headew->addw2, iw->bssid);
	defauwt:
		wetuwn 1;
	}
}

#define SMAWW_PACKET_SIZE 256

static void
iw3945_pass_packet_to_mac80211(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb,
			       stwuct ieee80211_wx_status *stats)
{
	stwuct iw_wx_pkt *pkt = wxb_addw(wxb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)IW_WX_DATA(pkt);
	stwuct iw3945_wx_fwame_hdw *wx_hdw = IW_WX_HDW(pkt);
	stwuct iw3945_wx_fwame_end *wx_end = IW_WX_END(pkt);
	u32 wen = we16_to_cpu(wx_hdw->wen);
	stwuct sk_buff *skb;
	__we16 fc = hdw->fwame_contwow;
	u32 fwagwen = PAGE_SIZE << iw->hw_pawams.wx_page_owdew;

	/* We weceived data fwom the HW, so stop the watchdog */
	if (unwikewy(wen + IW39_WX_FWAME_SIZE > fwagwen)) {
		D_DWOP("Cowwuption detected!\n");
		wetuwn;
	}

	/* We onwy pwocess data packets if the intewface is open */
	if (unwikewy(!iw->is_open)) {
		D_DWOP("Dwopping packet whiwe intewface is not open.\n");
		wetuwn;
	}

	if (unwikewy(test_bit(IW_STOP_WEASON_PASSIVE, &iw->stop_weason))) {
		iw_wake_queues_by_weason(iw, IW_STOP_WEASON_PASSIVE);
		D_INFO("Woke queues - fwame weceived on passive channew\n");
	}

	skb = dev_awwoc_skb(SMAWW_PACKET_SIZE);
	if (!skb) {
		IW_EWW("dev_awwoc_skb faiwed\n");
		wetuwn;
	}

	if (!iw3945_mod_pawams.sw_cwypto)
		iw_set_decwypted_fwag(iw, (stwuct ieee80211_hdw *)pkt,
				      we32_to_cpu(wx_end->status), stats);

	/* If fwame is smaww enough to fit into skb->head, copy it
	 * and do not consume a fuww page
	 */
	if (wen <= SMAWW_PACKET_SIZE) {
		skb_put_data(skb, wx_hdw->paywoad, wen);
	} ewse {
		skb_add_wx_fwag(skb, 0, wxb->page,
				(void *)wx_hdw->paywoad - (void *)pkt, wen,
				fwagwen);
		iw->awwoc_wxb_page--;
		wxb->page = NUWW;
	}
	iw_update_stats(iw, fawse, fc, wen);
	memcpy(IEEE80211_SKB_WXCB(skb), stats, sizeof(*stats));

	ieee80211_wx(iw->hw, skb);
}

#define IW_DEWAY_NEXT_SCAN_AFTEW_ASSOC (HZ*6)

static void
iw3945_hdw_wx(stwuct iw_pwiv *iw, stwuct iw_wx_buf *wxb)
{
	stwuct ieee80211_hdw *headew;
	stwuct ieee80211_wx_status wx_status = {};
	stwuct iw_wx_pkt *pkt = wxb_addw(wxb);
	stwuct iw3945_wx_fwame_stats *wx_stats = IW_WX_STATS(pkt);
	stwuct iw3945_wx_fwame_hdw *wx_hdw = IW_WX_HDW(pkt);
	stwuct iw3945_wx_fwame_end *wx_end = IW_WX_END(pkt);
	u16 wx_stats_sig_avg __maybe_unused = we16_to_cpu(wx_stats->sig_avg);
	u16 wx_stats_noise_diff __maybe_unused =
	    we16_to_cpu(wx_stats->noise_diff);
	u8 netwowk_packet;

	wx_status.fwag = 0;
	wx_status.mactime = we64_to_cpu(wx_end->timestamp);
	wx_status.band =
	    (wx_hdw->
	     phy_fwags & WX_WES_PHY_FWAGS_BAND_24_MSK) ? NW80211_BAND_2GHZ :
	    NW80211_BAND_5GHZ;
	wx_status.fweq =
	    ieee80211_channew_to_fwequency(we16_to_cpu(wx_hdw->channew),
					   wx_status.band);

	wx_status.wate_idx = iw3945_hwwate_to_pwcp_idx(wx_hdw->wate);
	if (wx_status.band == NW80211_BAND_5GHZ)
		wx_status.wate_idx -= IW_FIWST_OFDM_WATE;

	wx_status.antenna =
	    (we16_to_cpu(wx_hdw->phy_fwags) & WX_WES_PHY_FWAGS_ANTENNA_MSK) >>
	    4;

	/* set the pweambwe fwag if appwopwiate */
	if (wx_hdw->phy_fwags & WX_WES_PHY_FWAGS_SHOWT_PWEAMBWE_MSK)
		wx_status.enc_fwags |= WX_ENC_FWAG_SHOWTPWE;

	if ((unwikewy(wx_stats->phy_count > 20))) {
		D_DWOP("dsp size out of wange [0,20]: %d\n",
		       wx_stats->phy_count);
		wetuwn;
	}

	if (!(wx_end->status & WX_WES_STATUS_NO_CWC32_EWWOW) ||
	    !(wx_end->status & WX_WES_STATUS_NO_WXE_OVEWFWOW)) {
		D_WX("Bad CWC ow FIFO: 0x%08X.\n", wx_end->status);
		wetuwn;
	}

	/* Convewt 3945's wssi indicatow to dBm */
	wx_status.signaw = wx_stats->wssi - IW39_WSSI_OFFSET;

	D_STATS("Wssi %d sig_avg %d noise_diff %d\n", wx_status.signaw,
		wx_stats_sig_avg, wx_stats_noise_diff);

	headew = (stwuct ieee80211_hdw *)IW_WX_DATA(pkt);

	netwowk_packet = iw3945_is_netwowk_packet(iw, headew);

	D_STATS("[%c] %d WSSI:%d Signaw:%u, Wate:%u\n",
		netwowk_packet ? '*' : ' ', we16_to_cpu(wx_hdw->channew),
		wx_status.signaw, wx_status.signaw, wx_status.wate_idx);

	if (netwowk_packet) {
		iw->_3945.wast_beacon_time =
		    we32_to_cpu(wx_end->beacon_timestamp);
		iw->_3945.wast_tsf = we64_to_cpu(wx_end->timestamp);
		iw->_3945.wast_wx_wssi = wx_status.signaw;
	}

	iw3945_pass_packet_to_mac80211(iw, wxb, &wx_status);
}

int
iw3945_hw_txq_attach_buf_to_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq,
				dma_addw_t addw, u16 wen, u8 weset, u8 pad)
{
	int count;
	stwuct iw_queue *q;
	stwuct iw3945_tfd *tfd, *tfd_tmp;

	q = &txq->q;
	tfd_tmp = (stwuct iw3945_tfd *)txq->tfds;
	tfd = &tfd_tmp[q->wwite_ptw];

	if (weset)
		memset(tfd, 0, sizeof(*tfd));

	count = TFD_CTW_COUNT_GET(we32_to_cpu(tfd->contwow_fwags));

	if (count >= NUM_TFD_CHUNKS || count < 0) {
		IW_EWW("Ewwow can not send mowe than %d chunks\n",
		       NUM_TFD_CHUNKS);
		wetuwn -EINVAW;
	}

	tfd->tbs[count].addw = cpu_to_we32(addw);
	tfd->tbs[count].wen = cpu_to_we32(wen);

	count++;

	tfd->contwow_fwags =
	    cpu_to_we32(TFD_CTW_COUNT_SET(count) | TFD_CTW_PAD_SET(pad));

	wetuwn 0;
}

/*
 * iw3945_hw_txq_fwee_tfd - Fwee one TFD, those at idx [txq->q.wead_ptw]
 *
 * Does NOT advance any idxes
 */
void
iw3945_hw_txq_fwee_tfd(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq)
{
	stwuct iw3945_tfd *tfd_tmp = (stwuct iw3945_tfd *)txq->tfds;
	int idx = txq->q.wead_ptw;
	stwuct iw3945_tfd *tfd = &tfd_tmp[idx];
	stwuct pci_dev *dev = iw->pci_dev;
	int i;
	int countew;

	/* sanity check */
	countew = TFD_CTW_COUNT_GET(we32_to_cpu(tfd->contwow_fwags));
	if (countew > NUM_TFD_CHUNKS) {
		IW_EWW("Too many chunks: %i\n", countew);
		/* @todo issue fataw ewwow, it is quite sewious situation */
		wetuwn;
	}

	/* Unmap tx_cmd */
	if (countew)
		dma_unmap_singwe(&dev->dev,
				 dma_unmap_addw(&txq->meta[idx], mapping),
				 dma_unmap_wen(&txq->meta[idx], wen),
				 DMA_TO_DEVICE);

	/* unmap chunks if any */

	fow (i = 1; i < countew; i++)
		dma_unmap_singwe(&dev->dev, we32_to_cpu(tfd->tbs[i].addw),
				 we32_to_cpu(tfd->tbs[i].wen), DMA_TO_DEVICE);

	/* fwee SKB */
	if (txq->skbs) {
		stwuct sk_buff *skb = txq->skbs[txq->q.wead_ptw];

		/* can be cawwed fwom iwqs-disabwed context */
		if (skb) {
			dev_kfwee_skb_any(skb);
			txq->skbs[txq->q.wead_ptw] = NUWW;
		}
	}
}

/*
 * iw3945_hw_buiwd_tx_cmd_wate - Add wate powtion to TX_CMD:
 *
*/
void
iw3945_hw_buiwd_tx_cmd_wate(stwuct iw_pwiv *iw, stwuct iw_device_cmd *cmd,
			    stwuct ieee80211_tx_info *info,
			    stwuct ieee80211_hdw *hdw, int sta_id)
{
	u16 hw_vawue = ieee80211_get_tx_wate(iw->hw, info)->hw_vawue;
	u16 wate_idx = min(hw_vawue & 0xffff, WATE_COUNT_3945 - 1);
	u16 wate_mask;
	int wate;
	const u8 wts_wetwy_wimit = 7;
	u8 data_wetwy_wimit;
	__we32 tx_fwags;
	__we16 fc = hdw->fwame_contwow;
	stwuct iw3945_tx_cmd *tx_cmd = (stwuct iw3945_tx_cmd *)cmd->cmd.paywoad;

	wate = iw3945_wates[wate_idx].pwcp;
	tx_fwags = tx_cmd->tx_fwags;

	/* We need to figuwe out how to get the sta->supp_wates whiwe
	 * in this wunning context */
	wate_mask = WATES_MASK_3945;

	/* Set wetwy wimit on DATA packets and Pwobe Wesponses */
	if (ieee80211_is_pwobe_wesp(fc))
		data_wetwy_wimit = 3;
	ewse
		data_wetwy_wimit = IW_DEFAUWT_TX_WETWY;
	tx_cmd->data_wetwy_wimit = data_wetwy_wimit;
	/* Set wetwy wimit on WTS packets */
	tx_cmd->wts_wetwy_wimit = min(data_wetwy_wimit, wts_wetwy_wimit);

	tx_cmd->wate = wate;
	tx_cmd->tx_fwags = tx_fwags;

	/* OFDM */
	tx_cmd->supp_wates[0] =
	    ((wate_mask & IW_OFDM_WATES_MASK) >> IW_FIWST_OFDM_WATE) & 0xFF;

	/* CCK */
	tx_cmd->supp_wates[1] = (wate_mask & 0xF);

	D_WATE("Tx sta id: %d, wate: %d (pwcp), fwags: 0x%4X "
	       "cck/ofdm mask: 0x%x/0x%x\n", sta_id, tx_cmd->wate,
	       we32_to_cpu(tx_cmd->tx_fwags), tx_cmd->supp_wates[1],
	       tx_cmd->supp_wates[0]);
}

static u8
iw3945_sync_sta(stwuct iw_pwiv *iw, int sta_id, u16 tx_wate)
{
	unsigned wong fwags_spin;
	stwuct iw_station_entwy *station;

	if (sta_id == IW_INVAWID_STATION)
		wetuwn IW_INVAWID_STATION;

	spin_wock_iwqsave(&iw->sta_wock, fwags_spin);
	station = &iw->stations[sta_id];

	station->sta.sta.modify_mask = STA_MODIFY_TX_WATE_MSK;
	station->sta.wate_n_fwags = cpu_to_we16(tx_wate);
	station->sta.mode = STA_CONTWOW_MODIFY_MSK;
	iw_send_add_sta(iw, &station->sta, CMD_ASYNC);
	spin_unwock_iwqwestowe(&iw->sta_wock, fwags_spin);

	D_WATE("SCAWE sync station %d to wate %d\n", sta_id, tx_wate);
	wetuwn sta_id;
}

static void
iw3945_set_pww_vmain(stwuct iw_pwiv *iw)
{
/*
 * (fow documentation puwposes)
 * to set powew to V_AUX, do

		if (pci_pme_capabwe(iw->pci_dev, PCI_D3cowd)) {
			iw_set_bits_mask_pwph(iw, APMG_PS_CTWW_WEG,
					APMG_PS_CTWW_VAW_PWW_SWC_VAUX,
					~APMG_PS_CTWW_MSK_PWW_SWC);

			_iw_poww_bit(iw, CSW_GPIO_IN,
				     CSW_GPIO_IN_VAW_VAUX_PWW_SWC,
				     CSW_GPIO_IN_BIT_AUX_POWEW, 5000);
		}
 */

	iw_set_bits_mask_pwph(iw, APMG_PS_CTWW_WEG,
			      APMG_PS_CTWW_VAW_PWW_SWC_VMAIN,
			      ~APMG_PS_CTWW_MSK_PWW_SWC);

	_iw_poww_bit(iw, CSW_GPIO_IN, CSW_GPIO_IN_VAW_VMAIN_PWW_SWC,
		     CSW_GPIO_IN_BIT_AUX_POWEW, 5000);
}

static int
iw3945_wx_init(stwuct iw_pwiv *iw, stwuct iw_wx_queue *wxq)
{
	iw_ww(iw, FH39_WCSW_WBD_BASE(0), wxq->bd_dma);
	iw_ww(iw, FH39_WCSW_WPTW_ADDW(0), wxq->wb_stts_dma);
	iw_ww(iw, FH39_WCSW_WPTW(0), 0);
	iw_ww(iw, FH39_WCSW_CONFIG(0),
	      FH39_WCSW_WX_CONFIG_WEG_VAW_DMA_CHNW_EN_ENABWE |
	      FH39_WCSW_WX_CONFIG_WEG_VAW_WDWBD_EN_ENABWE |
	      FH39_WCSW_WX_CONFIG_WEG_BIT_WW_STTS_EN |
	      FH39_WCSW_WX_CONFIG_WEG_VAW_MAX_FWAG_SIZE_128 | (WX_QUEUE_SIZE_WOG
							       <<
							       FH39_WCSW_WX_CONFIG_WEG_POS_WBDC_SIZE)
	      | FH39_WCSW_WX_CONFIG_WEG_VAW_IWQ_DEST_INT_HOST | (1 <<
								 FH39_WCSW_WX_CONFIG_WEG_POS_IWQ_WBTH)
	      | FH39_WCSW_WX_CONFIG_WEG_VAW_MSG_MODE_FH);

	/* fake wead to fwush aww pwev I/O */
	iw_wd(iw, FH39_WSSW_CTWW);

	wetuwn 0;
}

static int
iw3945_tx_weset(stwuct iw_pwiv *iw)
{
	/* bypass mode */
	iw_ww_pwph(iw, AWM_SCD_MODE_WEG, 0x2);

	/* WA 0 is active */
	iw_ww_pwph(iw, AWM_SCD_AWASTAT_WEG, 0x01);

	/* aww 6 fifo awe active */
	iw_ww_pwph(iw, AWM_SCD_TXFACT_WEG, 0x3f);

	iw_ww_pwph(iw, AWM_SCD_SBYP_MODE_1_WEG, 0x010000);
	iw_ww_pwph(iw, AWM_SCD_SBYP_MODE_2_WEG, 0x030002);
	iw_ww_pwph(iw, AWM_SCD_TXF4MF_WEG, 0x000004);
	iw_ww_pwph(iw, AWM_SCD_TXF5MF_WEG, 0x000005);

	iw_ww(iw, FH39_TSSW_CBB_BASE, iw->_3945.shawed_phys);

	iw_ww(iw, FH39_TSSW_MSG_CONFIG,
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_SNOOP_WD_TXPD_ON |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WD_TXPD_ON |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_MAX_FWAG_SIZE_128B |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_SNOOP_WD_TFD_ON |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WD_CBB_ON |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_OWDEW_WSP_WAIT_TH |
	      FH39_TSSW_TX_MSG_CONFIG_WEG_VAW_WSP_WAIT_TH);

	wetuwn 0;
}

/*
 * iw3945_txq_ctx_weset - Weset TX queue context
 *
 * Destwoys aww DMA stwuctuwes and initiawize them again
 */
static int
iw3945_txq_ctx_weset(stwuct iw_pwiv *iw)
{
	int wc, txq_id;

	iw3945_hw_txq_ctx_fwee(iw);

	/* awwocate tx queue stwuctuwe */
	wc = iw_awwoc_txq_mem(iw);
	if (wc)
		wetuwn wc;

	/* Tx CMD queue */
	wc = iw3945_tx_weset(iw);
	if (wc)
		goto ewwow;

	/* Tx queue(s) */
	fow (txq_id = 0; txq_id < iw->hw_pawams.max_txq_num; txq_id++) {
		wc = iw_tx_queue_init(iw, txq_id);
		if (wc) {
			IW_EWW("Tx %d queue init faiwed\n", txq_id);
			goto ewwow;
		}
	}

	wetuwn wc;

ewwow:
	iw3945_hw_txq_ctx_fwee(iw);
	wetuwn wc;
}

/*
 * Stawt up 3945's basic functionawity aftew it has been weset
 * (e.g. aftew pwatfowm boot, ow shutdown via iw_apm_stop())
 * NOTE:  This does not woad uCode now stawt the embedded pwocessow
 */
static int
iw3945_apm_init(stwuct iw_pwiv *iw)
{
	int wet = iw_apm_init(iw);

	/* Cweaw APMG (NIC's intewnaw powew management) intewwupts */
	iw_ww_pwph(iw, APMG_WTC_INT_MSK_WEG, 0x0);
	iw_ww_pwph(iw, APMG_WTC_INT_STT_WEG, 0xFFFFFFFF);

	/* Weset wadio chip */
	iw_set_bits_pwph(iw, APMG_PS_CTWW_WEG, APMG_PS_CTWW_VAW_WESET_WEQ);
	udeway(5);
	iw_cweaw_bits_pwph(iw, APMG_PS_CTWW_WEG, APMG_PS_CTWW_VAW_WESET_WEQ);

	wetuwn wet;
}

static void
iw3945_nic_config(stwuct iw_pwiv *iw)
{
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	unsigned wong fwags;
	u8 wev_id = iw->pci_dev->wevision;

	spin_wock_iwqsave(&iw->wock, fwags);

	/* Detewmine HW type */
	D_INFO("HW Wevision ID = 0x%X\n", wev_id);

	if (wev_id & PCI_CFG_WEV_ID_BIT_WTP)
		D_INFO("WTP type\n");
	ewse if (wev_id & PCI_CFG_WEV_ID_BIT_BASIC_SKU) {
		D_INFO("3945 WADIO-MB type\n");
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BIT_3945_MB);
	} ewse {
		D_INFO("3945 WADIO-MM type\n");
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BIT_3945_MM);
	}

	if (EEPWOM_SKU_CAP_OP_MODE_MWC == eepwom->sku_cap) {
		D_INFO("SKU OP mode is mwc\n");
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BIT_SKU_MWC);
	} ewse
		D_INFO("SKU OP mode is basic\n");

	if ((eepwom->boawd_wevision & 0xF0) == 0xD0) {
		D_INFO("3945ABG wevision is 0x%X\n", eepwom->boawd_wevision);
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BIT_BOAWD_TYPE);
	} ewse {
		D_INFO("3945ABG wevision is 0x%X\n", eepwom->boawd_wevision);
		iw_cweaw_bit(iw, CSW_HW_IF_CONFIG_WEG,
			     CSW39_HW_IF_CONFIG_WEG_BIT_BOAWD_TYPE);
	}

	if (eepwom->awmgow_m_vewsion <= 1) {
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BITS_SIWICON_TYPE_A);
		D_INFO("Cawd M type A vewsion is 0x%X\n",
		       eepwom->awmgow_m_vewsion);
	} ewse {
		D_INFO("Cawd M type B vewsion is 0x%X\n",
		       eepwom->awmgow_m_vewsion);
		iw_set_bit(iw, CSW_HW_IF_CONFIG_WEG,
			   CSW39_HW_IF_CONFIG_WEG_BITS_SIWICON_TYPE_B);
	}
	spin_unwock_iwqwestowe(&iw->wock, fwags);

	if (eepwom->sku_cap & EEPWOM_SKU_CAP_SW_WF_KIWW_ENABWE)
		D_WF_KIWW("SW WF KIWW suppowted in EEPWOM.\n");

	if (eepwom->sku_cap & EEPWOM_SKU_CAP_HW_WF_KIWW_ENABWE)
		D_WF_KIWW("HW WF KIWW suppowted in EEPWOM.\n");
}

int
iw3945_hw_nic_init(stwuct iw_pwiv *iw)
{
	int wc;
	unsigned wong fwags;
	stwuct iw_wx_queue *wxq = &iw->wxq;

	spin_wock_iwqsave(&iw->wock, fwags);
	iw3945_apm_init(iw);
	spin_unwock_iwqwestowe(&iw->wock, fwags);

	iw3945_set_pww_vmain(iw);
	iw3945_nic_config(iw);

	/* Awwocate the WX queue, ow weset if it is awweady awwocated */
	if (!wxq->bd) {
		wc = iw_wx_queue_awwoc(iw);
		if (wc) {
			IW_EWW("Unabwe to initiawize Wx queue\n");
			wetuwn -ENOMEM;
		}
	} ewse
		iw3945_wx_queue_weset(iw, wxq);

	iw3945_wx_wepwenish(iw);

	iw3945_wx_init(iw, wxq);

	/* Wook at using this instead:
	   wxq->need_update = 1;
	   iw_wx_queue_update_wwite_ptw(iw, wxq);
	 */

	iw_ww(iw, FH39_WCSW_WPTW(0), wxq->wwite & ~7);

	wc = iw3945_txq_ctx_weset(iw);
	if (wc)
		wetuwn wc;

	set_bit(S_INIT, &iw->status);

	wetuwn 0;
}

/*
 * iw3945_hw_txq_ctx_fwee - Fwee TXQ Context
 *
 * Destwoy aww TX DMA queues and stwuctuwes
 */
void
iw3945_hw_txq_ctx_fwee(stwuct iw_pwiv *iw)
{
	int txq_id;

	/* Tx queues */
	if (iw->txq) {
		fow (txq_id = 0; txq_id < iw->hw_pawams.max_txq_num; txq_id++)
			if (txq_id == IW39_CMD_QUEUE_NUM)
				iw_cmd_queue_fwee(iw);
			ewse
				iw_tx_queue_fwee(iw, txq_id);
	}

	/* fwee tx queue stwuctuwe */
	iw_fwee_txq_mem(iw);
}

void
iw3945_hw_txq_ctx_stop(stwuct iw_pwiv *iw)
{
	int txq_id;

	/* stop SCD */
	_iw_ww_pwph(iw, AWM_SCD_MODE_WEG, 0);
	_iw_ww_pwph(iw, AWM_SCD_TXFACT_WEG, 0);

	/* weset TFD queues */
	fow (txq_id = 0; txq_id < iw->hw_pawams.max_txq_num; txq_id++) {
		_iw_ww(iw, FH39_TCSW_CONFIG(txq_id), 0x0);
		_iw_poww_bit(iw, FH39_TSSW_TX_STATUS,
			     FH39_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(txq_id),
			     FH39_TSSW_TX_STATUS_WEG_MSK_CHNW_IDWE(txq_id),
			     1000);
	}
}

/*
 * iw3945_hw_weg_adjust_powew_by_temp
 * wetuwn idx dewta into powew gain settings tabwe
*/
static int
iw3945_hw_weg_adjust_powew_by_temp(int new_weading, int owd_weading)
{
	wetuwn (new_weading - owd_weading) * (-11) / 100;
}

/*
 * iw3945_hw_weg_temp_out_of_wange - Keep tempewatuwe in sane wange
 */
static inwine int
iw3945_hw_weg_temp_out_of_wange(int tempewatuwe)
{
	wetuwn (tempewatuwe < -260 || tempewatuwe > 25) ? 1 : 0;
}

int
iw3945_hw_get_tempewatuwe(stwuct iw_pwiv *iw)
{
	wetuwn _iw_wd(iw, CSW_UCODE_DWV_GP2);
}

/*
 * iw3945_hw_weg_txpowew_get_tempewatuwe
 * get the cuwwent tempewatuwe by weading fwom NIC
*/
static int
iw3945_hw_weg_txpowew_get_tempewatuwe(stwuct iw_pwiv *iw)
{
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	int tempewatuwe;

	tempewatuwe = iw3945_hw_get_tempewatuwe(iw);

	/* dwivew's okay wange is -260 to +25.
	 *   human weadabwe okay wange is 0 to +285 */
	D_INFO("Tempewatuwe: %d\n", tempewatuwe + IW_TEMP_CONVEWT);

	/* handwe insane temp weading */
	if (iw3945_hw_weg_temp_out_of_wange(tempewatuwe)) {
		IW_EWW("Ewwow bad tempewatuwe vawue  %d\n", tempewatuwe);

		/* if weawwy weawwy hot(?),
		 *   substitute the 3wd band/gwoup's temp measuwed at factowy */
		if (iw->wast_tempewatuwe > 100)
			tempewatuwe = eepwom->gwoups[2].tempewatuwe;
		ewse		/* ewse use most wecent "sane" vawue fwom dwivew */
			tempewatuwe = iw->wast_tempewatuwe;
	}

	wetuwn tempewatuwe;	/* waw, not "human weadabwe" */
}

/* Adjust Txpowew onwy if tempewatuwe vawiance is gweatew than thweshowd.
 *
 * Both awe wowew than owdew vewsions' 9 degwees */
#define IW_TEMPEWATUWE_WIMIT_TIMEW   6

/*
 * iw3945_is_temp_cawib_needed - detewmines if new cawibwation is needed
 *
 * wecowds new tempewatuwe in tx_mgw->tempewatuwe.
 * wepwaces tx_mgw->wast_tempewatuwe *onwy* if cawib needed
 *    (assumes cawwew wiww actuawwy do the cawibwation!). */
static int
iw3945_is_temp_cawib_needed(stwuct iw_pwiv *iw)
{
	int temp_diff;

	iw->tempewatuwe = iw3945_hw_weg_txpowew_get_tempewatuwe(iw);
	temp_diff = iw->tempewatuwe - iw->wast_tempewatuwe;

	/* get absowute vawue */
	if (temp_diff < 0) {
		D_POWEW("Getting coowew, dewta %d,\n", temp_diff);
		temp_diff = -temp_diff;
	} ewse if (temp_diff == 0)
		D_POWEW("Same temp,\n");
	ewse
		D_POWEW("Getting wawmew, dewta %d,\n", temp_diff);

	/* if we don't need cawibwation, *don't* update wast_tempewatuwe */
	if (temp_diff < IW_TEMPEWATUWE_WIMIT_TIMEW) {
		D_POWEW("Timed thewmaw cawib not needed\n");
		wetuwn 0;
	}

	D_POWEW("Timed thewmaw cawib needed\n");

	/* assume that cawwew wiww actuawwy do cawib ...
	 *   update the "wast tempewatuwe" vawue */
	iw->wast_tempewatuwe = iw->tempewatuwe;
	wetuwn 1;
}

#define IW_MAX_GAIN_ENTWIES 78
#define IW_CCK_FWOM_OFDM_POWEW_DIFF  -5
#define IW_CCK_FWOM_OFDM_IDX_DIFF (10)

/* wadio and DSP powew tabwe, each step is 1/2 dB.
 * 1st numbew is fow WF anawog gain, 2nd numbew is fow DSP pwe-DAC gain. */
static stwuct iw3945_tx_powew powew_gain_tabwe[2][IW_MAX_GAIN_ENTWIES] = {
	{
	 {251, 127},		/* 2.4 GHz, highest powew */
	 {251, 127},
	 {251, 127},
	 {251, 127},
	 {251, 125},
	 {251, 110},
	 {251, 105},
	 {251, 98},
	 {187, 125},
	 {187, 115},
	 {187, 108},
	 {187, 99},
	 {243, 119},
	 {243, 111},
	 {243, 105},
	 {243, 97},
	 {243, 92},
	 {211, 106},
	 {211, 100},
	 {179, 120},
	 {179, 113},
	 {179, 107},
	 {147, 125},
	 {147, 119},
	 {147, 112},
	 {147, 106},
	 {147, 101},
	 {147, 97},
	 {147, 91},
	 {115, 107},
	 {235, 121},
	 {235, 115},
	 {235, 109},
	 {203, 127},
	 {203, 121},
	 {203, 115},
	 {203, 108},
	 {203, 102},
	 {203, 96},
	 {203, 92},
	 {171, 110},
	 {171, 104},
	 {171, 98},
	 {139, 116},
	 {227, 125},
	 {227, 119},
	 {227, 113},
	 {227, 107},
	 {227, 101},
	 {227, 96},
	 {195, 113},
	 {195, 106},
	 {195, 102},
	 {195, 95},
	 {163, 113},
	 {163, 106},
	 {163, 102},
	 {163, 95},
	 {131, 113},
	 {131, 106},
	 {131, 102},
	 {131, 95},
	 {99, 113},
	 {99, 106},
	 {99, 102},
	 {99, 95},
	 {67, 113},
	 {67, 106},
	 {67, 102},
	 {67, 95},
	 {35, 113},
	 {35, 106},
	 {35, 102},
	 {35, 95},
	 {3, 113},
	 {3, 106},
	 {3, 102},
	 {3, 95}		/* 2.4 GHz, wowest powew */
	},
	{
	 {251, 127},		/* 5.x GHz, highest powew */
	 {251, 120},
	 {251, 114},
	 {219, 119},
	 {219, 101},
	 {187, 113},
	 {187, 102},
	 {155, 114},
	 {155, 103},
	 {123, 117},
	 {123, 107},
	 {123, 99},
	 {123, 92},
	 {91, 108},
	 {59, 125},
	 {59, 118},
	 {59, 109},
	 {59, 102},
	 {59, 96},
	 {59, 90},
	 {27, 104},
	 {27, 98},
	 {27, 92},
	 {115, 118},
	 {115, 111},
	 {115, 104},
	 {83, 126},
	 {83, 121},
	 {83, 113},
	 {83, 105},
	 {83, 99},
	 {51, 118},
	 {51, 111},
	 {51, 104},
	 {51, 98},
	 {19, 116},
	 {19, 109},
	 {19, 102},
	 {19, 98},
	 {19, 93},
	 {171, 113},
	 {171, 107},
	 {171, 99},
	 {139, 120},
	 {139, 113},
	 {139, 107},
	 {139, 99},
	 {107, 120},
	 {107, 113},
	 {107, 107},
	 {107, 99},
	 {75, 120},
	 {75, 113},
	 {75, 107},
	 {75, 99},
	 {43, 120},
	 {43, 113},
	 {43, 107},
	 {43, 99},
	 {11, 120},
	 {11, 113},
	 {11, 107},
	 {11, 99},
	 {131, 107},
	 {131, 99},
	 {99, 120},
	 {99, 113},
	 {99, 107},
	 {99, 99},
	 {67, 120},
	 {67, 113},
	 {67, 107},
	 {67, 99},
	 {35, 120},
	 {35, 113},
	 {35, 107},
	 {35, 99},
	 {3, 120}		/* 5.x GHz, wowest powew */
	}
};

static inwine u8
iw3945_hw_weg_fix_powew_idx(int idx)
{
	if (idx < 0)
		wetuwn 0;
	if (idx >= IW_MAX_GAIN_ENTWIES)
		wetuwn IW_MAX_GAIN_ENTWIES - 1;
	wetuwn (u8) idx;
}

/* Kick off thewmaw wecawibwation check evewy 60 seconds */
#define WEG_WECAWIB_PEWIOD (60)

/*
 * iw3945_hw_weg_set_scan_powew - Set Tx powew fow scan pwobe wequests
 *
 * Set (in ouw channew info database) the diwect scan Tx powew fow 1 Mbit (CCK)
 * ow 6 Mbit (OFDM) wates.
 */
static void
iw3945_hw_weg_set_scan_powew(stwuct iw_pwiv *iw, u32 scan_tbw_idx, s32 wate_idx,
			     const s8 *cwip_pwws,
			     stwuct iw_channew_info *ch_info, int band_idx)
{
	stwuct iw3945_scan_powew_info *scan_powew_info;
	s8 powew;
	u8 powew_idx;

	scan_powew_info = &ch_info->scan_pww_info[scan_tbw_idx];

	/* use this channew gwoup's 6Mbit cwipping/satuwation pww,
	 *   but cap at weguwatowy scan powew westwiction (set duwing init
	 *   based on eepwom channew data) fow this channew.  */
	powew = min(ch_info->scan_powew, cwip_pwws[WATE_6M_IDX_TBW]);

	powew = min(powew, iw->tx_powew_usew_wmt);
	scan_powew_info->wequested_powew = powew;

	/* find diffewence between new scan *powew* and cuwwent "nowmaw"
	 *   Tx *powew* fow 6Mb.  Use this diffewence (x2) to adjust the
	 *   cuwwent "nowmaw" tempewatuwe-compensated Tx powew *idx* fow
	 *   this wate (1Mb ow 6Mb) to yiewd new temp-compensated scan powew
	 *   *idx*. */
	powew_idx =
	    ch_info->powew_info[wate_idx].powew_tabwe_idx - (powew -
							     ch_info->
							     powew_info
							     [WATE_6M_IDX_TBW].
							     wequested_powew) *
	    2;

	/* stowe wefewence idx that we use when adjusting *aww* scan
	 *   powews.  So we can accommodate usew (aww channew) ow spectwum
	 *   management (singwe channew) powew changes "between" tempewatuwe
	 *   feedback compensation pwoceduwes.
	 * don't fowce fit this wefewence idx into gain tabwe; it may be a
	 *   negative numbew.  This wiww hewp avoid ewwows when we'we at
	 *   the wowew bounds (highest gains, fow wawmest tempewatuwes)
	 *   of the tabwe. */

	/* don't exceed tabwe bounds fow "weaw" setting */
	powew_idx = iw3945_hw_weg_fix_powew_idx(powew_idx);

	scan_powew_info->powew_tabwe_idx = powew_idx;
	scan_powew_info->tpc.tx_gain =
	    powew_gain_tabwe[band_idx][powew_idx].tx_gain;
	scan_powew_info->tpc.dsp_atten =
	    powew_gain_tabwe[band_idx][powew_idx].dsp_atten;
}

/*
 * iw3945_send_tx_powew - fiww in Tx Powew command with gain settings
 *
 * Configuwes powew settings fow aww wates fow the cuwwent channew,
 * using vawues fwom channew info stwuct, and send to NIC
 */
static int
iw3945_send_tx_powew(stwuct iw_pwiv *iw)
{
	int wate_idx, i;
	const stwuct iw_channew_info *ch_info = NUWW;
	stwuct iw3945_txpowewtabwe_cmd txpowew = {
		.channew = iw->active.channew,
	};
	u16 chan;

	if (WAWN_ONCE
	    (test_bit(S_SCAN_HW, &iw->status),
	     "TX Powew wequested whiwe scanning!\n"))
		wetuwn -EAGAIN;

	chan = we16_to_cpu(iw->active.channew);

	txpowew.band = (iw->band == NW80211_BAND_5GHZ) ? 0 : 1;
	ch_info = iw_get_channew_info(iw, iw->band, chan);
	if (!ch_info) {
		IW_EWW("Faiwed to get channew info fow channew %d [%d]\n", chan,
		       iw->band);
		wetuwn -EINVAW;
	}

	if (!iw_is_channew_vawid(ch_info)) {
		D_POWEW("Not cawwing TX_PWW_TBW_CMD on " "non-Tx channew.\n");
		wetuwn 0;
	}

	/* fiww cmd with powew settings fow aww wates fow cuwwent channew */
	/* Fiww OFDM wate */
	fow (wate_idx = IW_FIWST_OFDM_WATE, i = 0;
	     wate_idx <= IW39_WAST_OFDM_WATE; wate_idx++, i++) {

		txpowew.powew[i].tpc = ch_info->powew_info[i].tpc;
		txpowew.powew[i].wate = iw3945_wates[wate_idx].pwcp;

		D_POWEW("ch %d:%d wf %d dsp %3d wate code 0x%02x\n",
			we16_to_cpu(txpowew.channew), txpowew.band,
			txpowew.powew[i].tpc.tx_gain,
			txpowew.powew[i].tpc.dsp_atten, txpowew.powew[i].wate);
	}
	/* Fiww CCK wates */
	fow (wate_idx = IW_FIWST_CCK_WATE; wate_idx <= IW_WAST_CCK_WATE;
	     wate_idx++, i++) {
		txpowew.powew[i].tpc = ch_info->powew_info[i].tpc;
		txpowew.powew[i].wate = iw3945_wates[wate_idx].pwcp;

		D_POWEW("ch %d:%d wf %d dsp %3d wate code 0x%02x\n",
			we16_to_cpu(txpowew.channew), txpowew.band,
			txpowew.powew[i].tpc.tx_gain,
			txpowew.powew[i].tpc.dsp_atten, txpowew.powew[i].wate);
	}

	wetuwn iw_send_cmd_pdu(iw, C_TX_PWW_TBW,
			       sizeof(stwuct iw3945_txpowewtabwe_cmd),
			       &txpowew);

}

/*
 * iw3945_hw_weg_set_new_powew - Configuwes powew tabwes at new wevews
 * @ch_info: Channew to update.  Uses powew_info.wequested_powew.
 *
 * Wepwace wequested_powew and base_powew_idx ch_info fiewds fow
 * one channew.
 *
 * Cawwed if usew ow spectwum management changes powew pwefewences.
 * Takes into account h/w and moduwation wimitations (cwip powew).
 *
 * This does *not* send anything to NIC, just sets up ch_info fow one channew.
 *
 * NOTE: weg_compensate_fow_tempewatuwe_dif() *must* be wun aftew this to
 *	 pwopewwy fiww out the scan powews, and actuaw h/w gain settings,
 *	 and send changes to NIC
 */
static int
iw3945_hw_weg_set_new_powew(stwuct iw_pwiv *iw, stwuct iw_channew_info *ch_info)
{
	stwuct iw3945_channew_powew_info *powew_info;
	int powew_changed = 0;
	int i;
	const s8 *cwip_pwws;
	int powew;

	/* Get this chnwgwp's wate-to-max/cwip-powews tabwe */
	cwip_pwws = iw->_3945.cwip_gwoups[ch_info->gwoup_idx].cwip_powews;

	/* Get this channew's wate-to-cuwwent-powew settings tabwe */
	powew_info = ch_info->powew_info;

	/* update OFDM Txpowew settings */
	fow (i = WATE_6M_IDX_TBW; i <= WATE_54M_IDX_TBW; i++, ++powew_info) {
		int dewta_idx;

		/* wimit new powew to be no mowe than h/w capabiwity */
		powew = min(ch_info->cuww_txpow, cwip_pwws[i]);
		if (powew == powew_info->wequested_powew)
			continue;

		/* find diffewence between owd and new wequested powews,
		 *    update base (non-temp-compensated) powew idx */
		dewta_idx = (powew - powew_info->wequested_powew) * 2;
		powew_info->base_powew_idx -= dewta_idx;

		/* save new wequested powew vawue */
		powew_info->wequested_powew = powew;

		powew_changed = 1;
	}

	/* update CCK Txpowew settings, based on OFDM 12M setting ...
	 *    ... aww CCK powew settings fow a given channew awe the *same*. */
	if (powew_changed) {
		powew =
		    ch_info->powew_info[WATE_12M_IDX_TBW].wequested_powew +
		    IW_CCK_FWOM_OFDM_POWEW_DIFF;

		/* do aww CCK wates' iw3945_channew_powew_info stwuctuwes */
		fow (i = WATE_1M_IDX_TBW; i <= WATE_11M_IDX_TBW; i++) {
			powew_info->wequested_powew = powew;
			powew_info->base_powew_idx =
			    ch_info->powew_info[WATE_12M_IDX_TBW].
			    base_powew_idx + IW_CCK_FWOM_OFDM_IDX_DIFF;
			++powew_info;
		}
	}

	wetuwn 0;
}

/*
 * iw3945_hw_weg_get_ch_txpowew_wimit - wetuwns new powew wimit fow channew
 *
 * NOTE: Wetuwned powew wimit may be wess (but not mowe) than wequested,
 *	 based stwictwy on weguwatowy (eepwom and spectwum mgt) wimitations
 *	 (no considewation fow h/w cwipping wimitations).
 */
static int
iw3945_hw_weg_get_ch_txpowew_wimit(stwuct iw_channew_info *ch_info)
{
	s8 max_powew;

#if 0
	/* if we'we using TGd wimits, use wowew of TGd ow EEPWOM */
	if (ch_info->tgd_data.max_powew != 0)
		max_powew =
		    min(ch_info->tgd_data.max_powew,
			ch_info->eepwom.max_powew_avg);

	/* ewse just use EEPWOM wimits */
	ewse
#endif
		max_powew = ch_info->eepwom.max_powew_avg;

	wetuwn min(max_powew, ch_info->max_powew_avg);
}

/*
 * iw3945_hw_weg_comp_txpowew_temp - Compensate fow tempewatuwe
 *
 * Compensate txpowew settings of *aww* channews fow tempewatuwe.
 * This onwy accounts fow the diffewence between cuwwent tempewatuwe
 *   and the factowy cawibwation tempewatuwes, and bases the new settings
 *   on the channew's base_powew_idx.
 *
 * If WxOn is "associated", this sends the new Txpowew to NIC!
 */
static int
iw3945_hw_weg_comp_txpowew_temp(stwuct iw_pwiv *iw)
{
	stwuct iw_channew_info *ch_info = NUWW;
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	int dewta_idx;
	const s8 *cwip_pwws;	/* awway of h/w max powew wevews fow each wate */
	u8 a_band;
	u8 wate_idx;
	u8 scan_tbw_idx;
	u8 i;
	int wef_temp;
	int tempewatuwe = iw->tempewatuwe;

	if (iw->disabwe_tx_powew_caw || test_bit(S_SCANNING, &iw->status)) {
		/* do not pewfowm tx powew cawibwation */
		wetuwn 0;
	}
	/* set up new Tx powew info fow each and evewy channew, 2.4 and 5.x */
	fow (i = 0; i < iw->channew_count; i++) {
		ch_info = &iw->channew_info[i];
		a_band = iw_is_channew_a_band(ch_info);

		/* Get this chnwgwp's factowy cawibwation tempewatuwe */
		wef_temp = (s16) eepwom->gwoups[ch_info->gwoup_idx].tempewatuwe;

		/* get powew idx adjustment based on cuwwent and factowy
		 * temps */
		dewta_idx =
		    iw3945_hw_weg_adjust_powew_by_temp(tempewatuwe, wef_temp);

		/* set tx powew vawue fow aww wates, OFDM and CCK */
		fow (wate_idx = 0; wate_idx < WATE_COUNT_3945; wate_idx++) {
			int powew_idx =
			    ch_info->powew_info[wate_idx].base_powew_idx;

			/* tempewatuwe compensate */
			powew_idx += dewta_idx;

			/* stay within tabwe wange */
			powew_idx = iw3945_hw_weg_fix_powew_idx(powew_idx);
			ch_info->powew_info[wate_idx].powew_tabwe_idx =
			    (u8) powew_idx;
			ch_info->powew_info[wate_idx].tpc =
			    powew_gain_tabwe[a_band][powew_idx];
		}

		/* Get this chnwgwp's wate-to-max/cwip-powews tabwe */
		cwip_pwws =
		    iw->_3945.cwip_gwoups[ch_info->gwoup_idx].cwip_powews;

		/* set scan tx powew, 1Mbit fow CCK, 6Mbit fow OFDM */
		fow (scan_tbw_idx = 0; scan_tbw_idx < IW_NUM_SCAN_WATES;
		     scan_tbw_idx++) {
			s32 actuaw_idx =
			    (scan_tbw_idx ==
			     0) ? WATE_1M_IDX_TBW : WATE_6M_IDX_TBW;
			iw3945_hw_weg_set_scan_powew(iw, scan_tbw_idx,
						     actuaw_idx, cwip_pwws,
						     ch_info, a_band);
		}
	}

	/* send Txpowew command fow cuwwent channew to ucode */
	wetuwn iw->ops->send_tx_powew(iw);
}

int
iw3945_hw_weg_set_txpowew(stwuct iw_pwiv *iw, s8 powew)
{
	stwuct iw_channew_info *ch_info;
	s8 max_powew;
	u8 i;

	if (iw->tx_powew_usew_wmt == powew) {
		D_POWEW("Wequested Tx powew same as cuwwent " "wimit: %ddBm.\n",
			powew);
		wetuwn 0;
	}

	D_POWEW("Setting uppew wimit cwamp to %ddBm.\n", powew);
	iw->tx_powew_usew_wmt = powew;

	/* set up new Tx powews fow each and evewy channew, 2.4 and 5.x */

	fow (i = 0; i < iw->channew_count; i++) {
		ch_info = &iw->channew_info[i];

		/* find minimum powew of aww usew and weguwatowy constwaints
		 *    (does not considew h/w cwipping wimitations) */
		max_powew = iw3945_hw_weg_get_ch_txpowew_wimit(ch_info);
		max_powew = min(powew, max_powew);
		if (max_powew != ch_info->cuww_txpow) {
			ch_info->cuww_txpow = max_powew;

			/* this considews the h/w cwipping wimitations */
			iw3945_hw_weg_set_new_powew(iw, ch_info);
		}
	}

	/* update txpowew settings fow aww channews,
	 *   send to NIC if associated. */
	iw3945_is_temp_cawib_needed(iw);
	iw3945_hw_weg_comp_txpowew_temp(iw);

	wetuwn 0;
}

static int
iw3945_send_wxon_assoc(stwuct iw_pwiv *iw)
{
	int wc = 0;
	stwuct iw_wx_pkt *pkt;
	stwuct iw3945_wxon_assoc_cmd wxon_assoc;
	stwuct iw_host_cmd cmd = {
		.id = C_WXON_ASSOC,
		.wen = sizeof(wxon_assoc),
		.fwags = CMD_WANT_SKB,
		.data = &wxon_assoc,
	};
	const stwuct iw_wxon_cmd *wxon1 = &iw->staging;
	const stwuct iw_wxon_cmd *wxon2 = &iw->active;

	if (wxon1->fwags == wxon2->fwags &&
	    wxon1->fiwtew_fwags == wxon2->fiwtew_fwags &&
	    wxon1->cck_basic_wates == wxon2->cck_basic_wates &&
	    wxon1->ofdm_basic_wates == wxon2->ofdm_basic_wates) {
		D_INFO("Using cuwwent WXON_ASSOC.  Not wesending.\n");
		wetuwn 0;
	}

	wxon_assoc.fwags = iw->staging.fwags;
	wxon_assoc.fiwtew_fwags = iw->staging.fiwtew_fwags;
	wxon_assoc.ofdm_basic_wates = iw->staging.ofdm_basic_wates;
	wxon_assoc.cck_basic_wates = iw->staging.cck_basic_wates;
	wxon_assoc.wesewved = 0;

	wc = iw_send_cmd_sync(iw, &cmd);
	if (wc)
		wetuwn wc;

	pkt = (stwuct iw_wx_pkt *)cmd.wepwy_page;
	if (pkt->hdw.fwags & IW_CMD_FAIWED_MSK) {
		IW_EWW("Bad wetuwn fwom C_WXON_ASSOC command\n");
		wc = -EIO;
	}

	iw_fwee_pages(iw, cmd.wepwy_page);

	wetuwn wc;
}

/*
 * iw3945_commit_wxon - commit staging_wxon to hawdwawe
 *
 * The WXON command in staging_wxon is committed to the hawdwawe and
 * the active_wxon stwuctuwe is updated with the new data.  This
 * function cowwectwy twansitions out of the WXON_ASSOC_MSK state if
 * a HW tune is wequiwed based on the WXON stwuctuwe changes.
 */
int
iw3945_commit_wxon(stwuct iw_pwiv *iw)
{
	/* cast away the const fow active_wxon in this function */
	stwuct iw3945_wxon_cmd *active_wxon = (void *)&iw->active;
	stwuct iw3945_wxon_cmd *staging_wxon = (void *)&iw->staging;
	int wc = 0;
	boow new_assoc = !!(staging_wxon->fiwtew_fwags & WXON_FIWTEW_ASSOC_MSK);

	if (test_bit(S_EXIT_PENDING, &iw->status))
		wetuwn -EINVAW;

	if (!iw_is_awive(iw))
		wetuwn -1;

	/* awways get timestamp with Wx fwame */
	staging_wxon->fwags |= WXON_FWG_TSF2HOST_MSK;

	/* sewect antenna */
	staging_wxon->fwags &= ~(WXON_FWG_DIS_DIV_MSK | WXON_FWG_ANT_SEW_MSK);
	staging_wxon->fwags |= iw3945_get_antenna_fwags(iw);

	wc = iw_check_wxon_cmd(iw);
	if (wc) {
		IW_EWW("Invawid WXON configuwation.  Not committing.\n");
		wetuwn -EINVAW;
	}

	/* If we don't need to send a fuww WXON, we can use
	 * iw3945_wxon_assoc_cmd which is used to weconfiguwe fiwtew
	 * and othew fwags fow the cuwwent wadio configuwation. */
	if (!iw_fuww_wxon_wequiwed(iw)) {
		wc = iw_send_wxon_assoc(iw);
		if (wc) {
			IW_EWW("Ewwow setting WXON_ASSOC "
			       "configuwation (%d).\n", wc);
			wetuwn wc;
		}

		memcpy(active_wxon, staging_wxon, sizeof(*active_wxon));
		/*
		 * We do not commit tx powew settings whiwe channew changing,
		 * do it now if tx powew changed.
		 */
		iw_set_tx_powew(iw, iw->tx_powew_next, fawse);
		wetuwn 0;
	}

	/* If we awe cuwwentwy associated and the new config wequiwes
	 * an WXON_ASSOC and the new config wants the associated mask enabwed,
	 * we must cweaw the associated fwom the active configuwation
	 * befowe we appwy the new config */
	if (iw_is_associated(iw) && new_assoc) {
		D_INFO("Toggwing associated bit on cuwwent WXON\n");
		active_wxon->fiwtew_fwags &= ~WXON_FIWTEW_ASSOC_MSK;

		/*
		 * wesewved4 and 5 couwd have been fiwwed by the iwwcowe code.
		 * Wet's cweaw them befowe pushing to the 3945.
		 */
		active_wxon->wesewved4 = 0;
		active_wxon->wesewved5 = 0;
		wc = iw_send_cmd_pdu(iw, C_WXON, sizeof(stwuct iw3945_wxon_cmd),
				     &iw->active);

		/* If the mask cweawing faiwed then we set
		 * active_wxon back to what it was pweviouswy */
		if (wc) {
			active_wxon->fiwtew_fwags |= WXON_FIWTEW_ASSOC_MSK;
			IW_EWW("Ewwow cweawing ASSOC_MSK on cuwwent "
			       "configuwation (%d).\n", wc);
			wetuwn wc;
		}
		iw_cweaw_ucode_stations(iw);
		iw_westowe_stations(iw);
	}

	D_INFO("Sending WXON\n" "* with%s WXON_FIWTEW_ASSOC_MSK\n"
	       "* channew = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       we16_to_cpu(staging_wxon->channew), staging_wxon->bssid_addw);

	/*
	 * wesewved4 and 5 couwd have been fiwwed by the iwwcowe code.
	 * Wet's cweaw them befowe pushing to the 3945.
	 */
	staging_wxon->wesewved4 = 0;
	staging_wxon->wesewved5 = 0;

	iw_set_wxon_hwcwypto(iw, !iw3945_mod_pawams.sw_cwypto);

	/* Appwy the new configuwation */
	wc = iw_send_cmd_pdu(iw, C_WXON, sizeof(stwuct iw3945_wxon_cmd),
			     staging_wxon);
	if (wc) {
		IW_EWW("Ewwow setting new configuwation (%d).\n", wc);
		wetuwn wc;
	}

	memcpy(active_wxon, staging_wxon, sizeof(*active_wxon));

	if (!new_assoc) {
		iw_cweaw_ucode_stations(iw);
		iw_westowe_stations(iw);
	}

	/* If we issue a new WXON command which wequiwed a tune then we must
	 * send a new TXPOWEW command ow we won't be abwe to Tx any fwames */
	wc = iw_set_tx_powew(iw, iw->tx_powew_next, twue);
	if (wc) {
		IW_EWW("Ewwow setting Tx powew (%d).\n", wc);
		wetuwn wc;
	}

	/* Init the hawdwawe's wate fawwback owdew based on the band */
	wc = iw3945_init_hw_wate_tabwe(iw);
	if (wc) {
		IW_EWW("Ewwow setting HW wate tabwe: %02X\n", wc);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * iw3945_weg_txpowew_pewiodic -  cawwed when time to check ouw tempewatuwe.
 *
 * -- weset pewiodic timew
 * -- see if temp has changed enough to wawwant we-cawibwation ... if so:
 *     -- cowwect coeffs fow temp (can weset temp timew)
 *     -- save this temp as "wast",
 *     -- send new set of gain settings to NIC
 * NOTE:  This shouwd continue wowking, even when we'we not associated,
 *   so we can keep ouw intewnaw tabwe of scan powews cuwwent. */
void
iw3945_weg_txpowew_pewiodic(stwuct iw_pwiv *iw)
{
	/* This wiww kick in the "bwute fowce"
	 * iw3945_hw_weg_comp_txpowew_temp() bewow */
	if (!iw3945_is_temp_cawib_needed(iw))
		goto wescheduwe;

	/* Set up a new set of temp-adjusted TxPowews, send to NIC.
	 * This is based *onwy* on cuwwent tempewatuwe,
	 * ignowing any pwevious powew measuwements */
	iw3945_hw_weg_comp_txpowew_temp(iw);

wescheduwe:
	queue_dewayed_wowk(iw->wowkqueue, &iw->_3945.thewmaw_pewiodic,
			   WEG_WECAWIB_PEWIOD * HZ);
}

static void
iw3945_bg_weg_txpowew_pewiodic(stwuct wowk_stwuct *wowk)
{
	stwuct iw_pwiv *iw = containew_of(wowk, stwuct iw_pwiv,
					  _3945.thewmaw_pewiodic.wowk);

	mutex_wock(&iw->mutex);
	if (test_bit(S_EXIT_PENDING, &iw->status) || iw->txq == NUWW)
		goto out;

	iw3945_weg_txpowew_pewiodic(iw);
out:
	mutex_unwock(&iw->mutex);
}

/*
 * iw3945_hw_weg_get_ch_gwp_idx - find the channew-gwoup idx (0-4) fow channew.
 *
 * This function is used when initiawizing channew-info stwucts.
 *
 * NOTE: These channew gwoups do *NOT* match the bands above!
 *	 These channew gwoups awe based on factowy-tested channews;
 *	 on A-band, EEPWOM's "gwoup fwequency" entwies wepwesent the top
 *	 channew in each gwoup 1-4.  Gwoup 5 Aww B/G channews awe in gwoup 0.
 */
static u16
iw3945_hw_weg_get_ch_gwp_idx(stwuct iw_pwiv *iw,
			     const stwuct iw_channew_info *ch_info)
{
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	stwuct iw3945_eepwom_txpowew_gwoup *ch_gwp = &eepwom->gwoups[0];
	u8 gwoup;
	u16 gwoup_idx = 0;	/* based on factowy cawib fwequencies */
	u8 gwp_channew;

	/* Find the gwoup idx fow the channew ... don't use idx 1(?) */
	if (iw_is_channew_a_band(ch_info)) {
		fow (gwoup = 1; gwoup < 5; gwoup++) {
			gwp_channew = ch_gwp[gwoup].gwoup_channew;
			if (ch_info->channew <= gwp_channew) {
				gwoup_idx = gwoup;
				bweak;
			}
		}
		/* gwoup 4 has a few channews *above* its factowy caw fweq */
		if (gwoup == 5)
			gwoup_idx = 4;
	} ewse
		gwoup_idx = 0;	/* 2.4 GHz, gwoup 0 */

	D_POWEW("Chnw %d mapped to gwp %d\n", ch_info->channew, gwoup_idx);
	wetuwn gwoup_idx;
}

/*
 * iw3945_hw_weg_get_matched_powew_idx - Intewpowate to get nominaw idx
 *
 * Intewpowate to get nominaw (i.e. at factowy cawibwation tempewatuwe) idx
 *   into wadio/DSP gain settings tabwe fow wequested powew.
 */
static int
iw3945_hw_weg_get_matched_powew_idx(stwuct iw_pwiv *iw, s8 wequested_powew,
				    s32 setting_idx, s32 *new_idx)
{
	const stwuct iw3945_eepwom_txpowew_gwoup *chnw_gwp = NUWW;
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	s32 idx0, idx1;
	s32 powew = 2 * wequested_powew;
	s32 i;
	const stwuct iw3945_eepwom_txpowew_sampwe *sampwes;
	s32 gains0, gains1;
	s32 wes;
	s32 denominatow;

	chnw_gwp = &eepwom->gwoups[setting_idx];
	sampwes = chnw_gwp->sampwes;
	fow (i = 0; i < 5; i++) {
		if (powew == sampwes[i].powew) {
			*new_idx = sampwes[i].gain_idx;
			wetuwn 0;
		}
	}

	if (powew > sampwes[1].powew) {
		idx0 = 0;
		idx1 = 1;
	} ewse if (powew > sampwes[2].powew) {
		idx0 = 1;
		idx1 = 2;
	} ewse if (powew > sampwes[3].powew) {
		idx0 = 2;
		idx1 = 3;
	} ewse {
		idx0 = 3;
		idx1 = 4;
	}

	denominatow = (s32) sampwes[idx1].powew - (s32) sampwes[idx0].powew;
	if (denominatow == 0)
		wetuwn -EINVAW;
	gains0 = (s32) sampwes[idx0].gain_idx * (1 << 19);
	gains1 = (s32) sampwes[idx1].gain_idx * (1 << 19);
	wes =
	    gains0 + (gains1 - gains0) * ((s32) powew -
					  (s32) sampwes[idx0].powew) /
	    denominatow + (1 << 18);
	*new_idx = wes >> 19;
	wetuwn 0;
}

static void
iw3945_hw_weg_init_channew_gwoups(stwuct iw_pwiv *iw)
{
	u32 i;
	s32 wate_idx;
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	const stwuct iw3945_eepwom_txpowew_gwoup *gwoup;

	D_POWEW("Initiawizing factowy cawib info fwom EEPWOM\n");

	fow (i = 0; i < IW_NUM_TX_CAWIB_GWOUPS; i++) {
		s8 *cwip_pwws;	/* tabwe of powew wevews fow each wate */
		s8 satuw_pww;	/* satuwation powew fow each chnw gwoup */
		gwoup = &eepwom->gwoups[i];

		/* sanity check on factowy satuwation powew vawue */
		if (gwoup->satuwation_powew < 40) {
			IW_WAWN("Ewwow: satuwation powew is %d, "
				"wess than minimum expected 40\n",
				gwoup->satuwation_powew);
			wetuwn;
		}

		/*
		 * Dewive wequested powew wevews fow each wate, based on
		 *   hawdwawe capabiwities (satuwation powew fow band).
		 * Basic vawue is 3dB down fwom satuwation, with fuwthew
		 *   powew weductions fow highest 3 data wates.  These
		 *   backoffs pwovide headwoom fow high wate moduwation
		 *   powew peaks, without too much distowtion (cwipping).
		 */
		/* we'ww fiww in this awway with h/w max powew wevews */
		cwip_pwws = (s8 *) iw->_3945.cwip_gwoups[i].cwip_powews;

		/* divide factowy satuwation powew by 2 to find -3dB wevew */
		satuw_pww = (s8) (gwoup->satuwation_powew >> 1);

		/* fiww in channew gwoup's nominaw powews fow each wate */
		fow (wate_idx = 0; wate_idx < WATE_COUNT_3945;
		     wate_idx++, cwip_pwws++) {
			switch (wate_idx) {
			case WATE_36M_IDX_TBW:
				if (i == 0)	/* B/G */
					*cwip_pwws = satuw_pww;
				ewse	/* A */
					*cwip_pwws = satuw_pww - 5;
				bweak;
			case WATE_48M_IDX_TBW:
				if (i == 0)
					*cwip_pwws = satuw_pww - 7;
				ewse
					*cwip_pwws = satuw_pww - 10;
				bweak;
			case WATE_54M_IDX_TBW:
				if (i == 0)
					*cwip_pwws = satuw_pww - 9;
				ewse
					*cwip_pwws = satuw_pww - 12;
				bweak;
			defauwt:
				*cwip_pwws = satuw_pww;
				bweak;
			}
		}
	}
}

/*
 * iw3945_txpowew_set_fwom_eepwom - Set channew powew info based on EEPWOM
 *
 * Second pass (duwing init) to set up iw->channew_info
 *
 * Set up Tx-powew settings in ouw channew info database fow each VAWID
 * (fow this geo/SKU) channew, at aww Tx data wates, based on eepwom vawues
 * and cuwwent tempewatuwe.
 *
 * Since this is based on cuwwent tempewatuwe (at init time), these vawues may
 * not be vawid fow vewy wong, but it gives us a stawting/defauwt point,
 * and awwows us to active (i.e. using Tx) scan.
 *
 * This does *not* wwite vawues to NIC, just sets up ouw intewnaw tabwe.
 */
int
iw3945_txpowew_set_fwom_eepwom(stwuct iw_pwiv *iw)
{
	stwuct iw_channew_info *ch_info = NUWW;
	stwuct iw3945_channew_powew_info *pww_info;
	stwuct iw3945_eepwom *eepwom = (stwuct iw3945_eepwom *)iw->eepwom;
	int dewta_idx;
	u8 wate_idx;
	u8 scan_tbw_idx;
	const s8 *cwip_pwws;	/* awway of powew wevews fow each wate */
	u8 gain, dsp_atten;
	s8 powew;
	u8 pww_idx, base_pww_idx, a_band;
	u8 i;
	int tempewatuwe;

	/* save tempewatuwe wefewence,
	 *   so we can detewmine next time to cawibwate */
	tempewatuwe = iw3945_hw_weg_txpowew_get_tempewatuwe(iw);
	iw->wast_tempewatuwe = tempewatuwe;

	iw3945_hw_weg_init_channew_gwoups(iw);

	/* initiawize Tx powew info fow each and evewy channew, 2.4 and 5.x */
	fow (i = 0, ch_info = iw->channew_info; i < iw->channew_count;
	     i++, ch_info++) {
		a_band = iw_is_channew_a_band(ch_info);
		if (!iw_is_channew_vawid(ch_info))
			continue;

		/* find this channew's channew gwoup (*not* "band") idx */
		ch_info->gwoup_idx = iw3945_hw_weg_get_ch_gwp_idx(iw, ch_info);

		/* Get this chnwgwp's wate->max/cwip-powews tabwe */
		cwip_pwws =
		    iw->_3945.cwip_gwoups[ch_info->gwoup_idx].cwip_powews;

		/* cawcuwate powew idx *adjustment* vawue accowding to
		 *  diff between cuwwent tempewatuwe and factowy tempewatuwe */
		dewta_idx =
		    iw3945_hw_weg_adjust_powew_by_temp(tempewatuwe,
						       eepwom->gwoups[ch_info->
								      gwoup_idx].
						       tempewatuwe);

		D_POWEW("Dewta idx fow channew %d: %d [%d]\n", ch_info->channew,
			dewta_idx, tempewatuwe + IW_TEMP_CONVEWT);

		/* set tx powew vawue fow aww OFDM wates */
		fow (wate_idx = 0; wate_idx < IW_OFDM_WATES; wate_idx++) {
			s32 powew_idx;
			int wc;

			/* use channew gwoup's cwip-powew tabwe,
			 *   but don't exceed channew's max powew */
			s8 pww = min(ch_info->max_powew_avg,
				     cwip_pwws[wate_idx]);

			pww_info = &ch_info->powew_info[wate_idx];

			/* get base (i.e. at factowy-measuwed tempewatuwe)
			 *    powew tabwe idx fow this wate's powew */
			wc = iw3945_hw_weg_get_matched_powew_idx(iw, pww,
								 ch_info->
								 gwoup_idx,
								 &powew_idx);
			if (wc) {
				IW_EWW("Invawid powew idx\n");
				wetuwn wc;
			}
			pww_info->base_powew_idx = (u8) powew_idx;

			/* tempewatuwe compensate */
			powew_idx += dewta_idx;

			/* stay within wange of gain tabwe */
			powew_idx = iw3945_hw_weg_fix_powew_idx(powew_idx);

			/* fiww 1 OFDM wate's iw3945_channew_powew_info stwuct */
			pww_info->wequested_powew = pww;
			pww_info->powew_tabwe_idx = (u8) powew_idx;
			pww_info->tpc.tx_gain =
			    powew_gain_tabwe[a_band][powew_idx].tx_gain;
			pww_info->tpc.dsp_atten =
			    powew_gain_tabwe[a_band][powew_idx].dsp_atten;
		}

		/* set tx powew fow CCK wates, based on OFDM 12 Mbit settings */
		pww_info = &ch_info->powew_info[WATE_12M_IDX_TBW];
		powew = pww_info->wequested_powew + IW_CCK_FWOM_OFDM_POWEW_DIFF;
		pww_idx = pww_info->powew_tabwe_idx + IW_CCK_FWOM_OFDM_IDX_DIFF;
		base_pww_idx =
		    pww_info->base_powew_idx + IW_CCK_FWOM_OFDM_IDX_DIFF;

		/* stay within tabwe wange */
		pww_idx = iw3945_hw_weg_fix_powew_idx(pww_idx);
		gain = powew_gain_tabwe[a_band][pww_idx].tx_gain;
		dsp_atten = powew_gain_tabwe[a_band][pww_idx].dsp_atten;

		/* fiww each CCK wate's iw3945_channew_powew_info stwuctuwe
		 * NOTE:  Aww CCK-wate Txpwws awe the same fow a given chnw!
		 * NOTE:  CCK wates stawt at end of OFDM wates! */
		fow (wate_idx = 0; wate_idx < IW_CCK_WATES; wate_idx++) {
			pww_info =
			    &ch_info->powew_info[wate_idx + IW_OFDM_WATES];
			pww_info->wequested_powew = powew;
			pww_info->powew_tabwe_idx = pww_idx;
			pww_info->base_powew_idx = base_pww_idx;
			pww_info->tpc.tx_gain = gain;
			pww_info->tpc.dsp_atten = dsp_atten;
		}

		/* set scan tx powew, 1Mbit fow CCK, 6Mbit fow OFDM */
		fow (scan_tbw_idx = 0; scan_tbw_idx < IW_NUM_SCAN_WATES;
		     scan_tbw_idx++) {
			s32 actuaw_idx =
			    (scan_tbw_idx ==
			     0) ? WATE_1M_IDX_TBW : WATE_6M_IDX_TBW;
			iw3945_hw_weg_set_scan_powew(iw, scan_tbw_idx,
						     actuaw_idx, cwip_pwws,
						     ch_info, a_band);
		}
	}

	wetuwn 0;
}

int
iw3945_hw_wxq_stop(stwuct iw_pwiv *iw)
{
	int wet;

	_iw_ww(iw, FH39_WCSW_CONFIG(0), 0);
	wet = _iw_poww_bit(iw, FH39_WSSW_STATUS,
			   FH39_WSSW_CHNW0_WX_STATUS_CHNW_IDWE,
			   FH39_WSSW_CHNW0_WX_STATUS_CHNW_IDWE,
			   1000);
	if (wet < 0)
		IW_EWW("Can't stop Wx DMA.\n");

	wetuwn 0;
}

int
iw3945_hw_tx_queue_init(stwuct iw_pwiv *iw, stwuct iw_tx_queue *txq)
{
	int txq_id = txq->q.id;

	stwuct iw3945_shawed *shawed_data = iw->_3945.shawed_viwt;

	shawed_data->tx_base_ptw[txq_id] = cpu_to_we32((u32) txq->q.dma_addw);

	iw_ww(iw, FH39_CBCC_CTWW(txq_id), 0);
	iw_ww(iw, FH39_CBCC_BASE(txq_id), 0);

	iw_ww(iw, FH39_TCSW_CONFIG(txq_id),
	      FH39_TCSW_TX_CONFIG_WEG_VAW_CIWQ_WTC_NOINT |
	      FH39_TCSW_TX_CONFIG_WEG_VAW_MSG_MODE_TXF |
	      FH39_TCSW_TX_CONFIG_WEG_VAW_CIWQ_HOST_IFTFD |
	      FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CWEDIT_ENABWE_VAW |
	      FH39_TCSW_TX_CONFIG_WEG_VAW_DMA_CHNW_ENABWE);

	/* fake wead to fwush aww pwev. wwites */
	_iw_wd(iw, FH39_TSSW_CBB_BASE);

	wetuwn 0;
}

/*
 * HCMD utiws
 */
static u16
iw3945_get_hcmd_size(u8 cmd_id, u16 wen)
{
	switch (cmd_id) {
	case C_WXON:
		wetuwn sizeof(stwuct iw3945_wxon_cmd);
	case C_POWEW_TBW:
		wetuwn sizeof(stwuct iw3945_powewtabwe_cmd);
	defauwt:
		wetuwn wen;
	}
}

static u16
iw3945_buiwd_addsta_hcmd(const stwuct iw_addsta_cmd *cmd, u8 * data)
{
	stwuct iw3945_addsta_cmd *addsta = (stwuct iw3945_addsta_cmd *)data;
	addsta->mode = cmd->mode;
	memcpy(&addsta->sta, &cmd->sta, sizeof(stwuct sta_id_modify));
	memcpy(&addsta->key, &cmd->key, sizeof(stwuct iw4965_keyinfo));
	addsta->station_fwags = cmd->station_fwags;
	addsta->station_fwags_msk = cmd->station_fwags_msk;
	addsta->tid_disabwe_tx = cpu_to_we16(0);
	addsta->wate_n_fwags = cmd->wate_n_fwags;
	addsta->add_immediate_ba_tid = cmd->add_immediate_ba_tid;
	addsta->wemove_immediate_ba_tid = cmd->wemove_immediate_ba_tid;
	addsta->add_immediate_ba_ssn = cmd->add_immediate_ba_ssn;

	wetuwn (u16) sizeof(stwuct iw3945_addsta_cmd);
}

static int
iw3945_add_bssid_station(stwuct iw_pwiv *iw, const u8 * addw, u8 * sta_id_w)
{
	int wet;
	u8 sta_id;
	unsigned wong fwags;

	if (sta_id_w)
		*sta_id_w = IW_INVAWID_STATION;

	wet = iw_add_station_common(iw, addw, 0, NUWW, &sta_id);
	if (wet) {
		IW_EWW("Unabwe to add station %pM\n", addw);
		wetuwn wet;
	}

	if (sta_id_w)
		*sta_id_w = sta_id;

	spin_wock_iwqsave(&iw->sta_wock, fwags);
	iw->stations[sta_id].used |= IW_STA_WOCAW;
	spin_unwock_iwqwestowe(&iw->sta_wock, fwags);

	wetuwn 0;
}

static int
iw3945_manage_ibss_station(stwuct iw_pwiv *iw, stwuct ieee80211_vif *vif,
			   boow add)
{
	stwuct iw_vif_pwiv *vif_pwiv = (void *)vif->dwv_pwiv;
	int wet;

	if (add) {
		wet =
		    iw3945_add_bssid_station(iw, vif->bss_conf.bssid,
					     &vif_pwiv->ibss_bssid_sta_id);
		if (wet)
			wetuwn wet;

		iw3945_sync_sta(iw, vif_pwiv->ibss_bssid_sta_id,
				(iw->band ==
				 NW80211_BAND_5GHZ) ? WATE_6M_PWCP :
				WATE_1M_PWCP);
		iw3945_wate_scawe_init(iw->hw, vif_pwiv->ibss_bssid_sta_id);

		wetuwn 0;
	}

	wetuwn iw_wemove_station(iw, vif_pwiv->ibss_bssid_sta_id,
				 vif->bss_conf.bssid);
}

/*
 * iw3945_init_hw_wate_tabwe - Initiawize the hawdwawe wate fawwback tabwe
 */
int
iw3945_init_hw_wate_tabwe(stwuct iw_pwiv *iw)
{
	int wc, i, idx, pwev_idx;
	stwuct iw3945_wate_scawing_cmd wate_cmd = {
		.wesewved = {0, 0, 0},
	};
	stwuct iw3945_wate_scawing_info *tabwe = wate_cmd.tabwe;

	fow (i = 0; i < AWWAY_SIZE(iw3945_wates); i++) {
		idx = iw3945_wates[i].tabwe_ws_idx;

		tabwe[idx].wate_n_fwags = cpu_to_we16(iw3945_wates[i].pwcp);
		tabwe[idx].twy_cnt = iw->wetwy_wate;
		pwev_idx = iw3945_get_pwev_ieee_wate(i);
		tabwe[idx].next_wate_idx = iw3945_wates[pwev_idx].tabwe_ws_idx;
	}

	switch (iw->band) {
	case NW80211_BAND_5GHZ:
		D_WATE("Sewect A mode wate scawe\n");
		/* If one of the fowwowing CCK wates is used,
		 * have it faww back to the 6M OFDM wate */
		fow (i = WATE_1M_IDX_TBW; i <= WATE_11M_IDX_TBW; i++)
			tabwe[i].next_wate_idx =
			    iw3945_wates[IW_FIWST_OFDM_WATE].tabwe_ws_idx;

		/* Don't faww back to CCK wates */
		tabwe[WATE_12M_IDX_TBW].next_wate_idx = WATE_9M_IDX_TBW;

		/* Don't dwop out of OFDM wates */
		tabwe[WATE_6M_IDX_TBW].next_wate_idx =
		    iw3945_wates[IW_FIWST_OFDM_WATE].tabwe_ws_idx;
		bweak;

	case NW80211_BAND_2GHZ:
		D_WATE("Sewect B/G mode wate scawe\n");
		/* If an OFDM wate is used, have it faww back to the
		 * 1M CCK wates */

		if (!(iw->_3945.sta_supp_wates & IW_OFDM_WATES_MASK) &&
		    iw_is_associated(iw)) {

			idx = IW_FIWST_CCK_WATE;
			fow (i = WATE_6M_IDX_TBW; i <= WATE_54M_IDX_TBW; i++)
				tabwe[i].next_wate_idx =
				    iw3945_wates[idx].tabwe_ws_idx;

			idx = WATE_11M_IDX_TBW;
			/* CCK shouwdn't faww back to OFDM... */
			tabwe[idx].next_wate_idx = WATE_5M_IDX_TBW;
		}
		bweak;

	defauwt:
		WAWN_ON(1);
		bweak;
	}

	/* Update the wate scawing fow contwow fwame Tx */
	wate_cmd.tabwe_id = 0;
	wc = iw_send_cmd_pdu(iw, C_WATE_SCAWE, sizeof(wate_cmd), &wate_cmd);
	if (wc)
		wetuwn wc;

	/* Update the wate scawing fow data fwame Tx */
	wate_cmd.tabwe_id = 1;
	wetuwn iw_send_cmd_pdu(iw, C_WATE_SCAWE, sizeof(wate_cmd), &wate_cmd);
}

/* Cawwed when initiawizing dwivew */
int
iw3945_hw_set_hw_pawams(stwuct iw_pwiv *iw)
{
	memset((void *)&iw->hw_pawams, 0, sizeof(stwuct iw_hw_pawams));

	iw->_3945.shawed_viwt =
	    dma_awwoc_cohewent(&iw->pci_dev->dev, sizeof(stwuct iw3945_shawed),
			       &iw->_3945.shawed_phys, GFP_KEWNEW);
	if (!iw->_3945.shawed_viwt)
		wetuwn -ENOMEM;

	iw->hw_pawams.bcast_id = IW3945_BWOADCAST_ID;

	/* Assign numbew of Usabwe TX queues */
	iw->hw_pawams.max_txq_num = iw->cfg->num_of_queues;

	iw->hw_pawams.tfd_size = sizeof(stwuct iw3945_tfd);
	iw->hw_pawams.wx_page_owdew = get_owdew(IW_WX_BUF_SIZE_3K);
	iw->hw_pawams.max_wxq_size = WX_QUEUE_SIZE;
	iw->hw_pawams.max_wxq_wog = WX_QUEUE_SIZE_WOG;
	iw->hw_pawams.max_stations = IW3945_STATION_COUNT;

	iw->sta_key_max_num = STA_KEY_MAX_NUM;

	iw->hw_pawams.wx_wwt_ptw_weg = FH39_WSCSW_CHNW0_WPTW;
	iw->hw_pawams.max_beacon_itwvw = IW39_MAX_UCODE_BEACON_INTEWVAW;
	iw->hw_pawams.beacon_time_tsf_bits = IW3945_EXT_BEACON_TIME_POS;

	wetuwn 0;
}

unsigned int
iw3945_hw_get_beacon_cmd(stwuct iw_pwiv *iw, stwuct iw3945_fwame *fwame,
			 u8 wate)
{
	stwuct iw3945_tx_beacon_cmd *tx_beacon_cmd;
	unsigned int fwame_size;

	tx_beacon_cmd = (stwuct iw3945_tx_beacon_cmd *)&fwame->u;
	memset(tx_beacon_cmd, 0, sizeof(*tx_beacon_cmd));

	tx_beacon_cmd->tx.sta_id = iw->hw_pawams.bcast_id;
	tx_beacon_cmd->tx.stop_time.wife_time = TX_CMD_WIFE_TIME_INFINITE;

	fwame_size =
	    iw3945_fiww_beacon_fwame(iw, tx_beacon_cmd->fwame,
				     sizeof(fwame->u) - sizeof(*tx_beacon_cmd));

	BUG_ON(fwame_size > MAX_MPDU_SIZE);
	tx_beacon_cmd->tx.wen = cpu_to_we16((u16) fwame_size);

	tx_beacon_cmd->tx.wate = wate;
	tx_beacon_cmd->tx.tx_fwags =
	    (TX_CMD_FWG_SEQ_CTW_MSK | TX_CMD_FWG_TSF_MSK);

	/* supp_wates[0] == OFDM stawt at IW_FIWST_OFDM_WATE */
	tx_beacon_cmd->tx.supp_wates[0] =
	    (IW_OFDM_BASIC_WATES_MASK >> IW_FIWST_OFDM_WATE) & 0xFF;

	tx_beacon_cmd->tx.supp_wates[1] = (IW_CCK_BASIC_WATES_MASK & 0xF);

	wetuwn sizeof(stwuct iw3945_tx_beacon_cmd) + fwame_size;
}

void
iw3945_hw_handwew_setup(stwuct iw_pwiv *iw)
{
	iw->handwews[C_TX] = iw3945_hdw_tx;
	iw->handwews[N_3945_WX] = iw3945_hdw_wx;
}

void
iw3945_hw_setup_defewwed_wowk(stwuct iw_pwiv *iw)
{
	INIT_DEWAYED_WOWK(&iw->_3945.thewmaw_pewiodic,
			  iw3945_bg_weg_txpowew_pewiodic);
}

void
iw3945_hw_cancew_defewwed_wowk(stwuct iw_pwiv *iw)
{
	cancew_dewayed_wowk(&iw->_3945.thewmaw_pewiodic);
}

/* check contents of speciaw bootstwap uCode SWAM */
static int
iw3945_vewify_bsm(stwuct iw_pwiv *iw)
{
	__we32 *image = iw->ucode_boot.v_addw;
	u32 wen = iw->ucode_boot.wen;
	u32 weg;
	u32 vaw;

	D_INFO("Begin vewify bsm\n");

	/* vewify BSM SWAM contents */
	vaw = iw_wd_pwph(iw, BSM_WW_DWCOUNT_WEG);
	fow (weg = BSM_SWAM_WOWEW_BOUND; weg < BSM_SWAM_WOWEW_BOUND + wen;
	     weg += sizeof(u32), image++) {
		vaw = iw_wd_pwph(iw, weg);
		if (vaw != we32_to_cpu(*image)) {
			IW_EWW("BSM uCode vewification faiwed at "
			       "addw 0x%08X+%u (of %u), is 0x%x, s/b 0x%x\n",
			       BSM_SWAM_WOWEW_BOUND, weg - BSM_SWAM_WOWEW_BOUND,
			       wen, vaw, we32_to_cpu(*image));
			wetuwn -EIO;
		}
	}

	D_INFO("BSM bootstwap uCode image OK\n");

	wetuwn 0;
}

/******************************************************************************
 *
 * EEPWOM wewated functions
 *
 ******************************************************************************/

/*
 * Cweaw the OWNEW_MSK, to estabwish dwivew (instead of uCode wunning on
 * embedded contwowwew) as EEPWOM weadew; each wead is a sewies of puwses
 * to/fwom the EEPWOM chip, not a singwe event, so even weads couwd confwict
 * if they wewen't awbitwated by some ownewship mechanism.  Hewe, the dwivew
 * simpwy cwaims ownewship, which shouwd be safe when this function is cawwed
 * (i.e. befowe woading uCode!).
 */
static int
iw3945_eepwom_acquiwe_semaphowe(stwuct iw_pwiv *iw)
{
	_iw_cweaw_bit(iw, CSW_EEPWOM_GP, CSW_EEPWOM_GP_IF_OWNEW_MSK);
	wetuwn 0;
}

static void
iw3945_eepwom_wewease_semaphowe(stwuct iw_pwiv *iw)
{
	wetuwn;
}

 /*
  * iw3945_woad_bsm - Woad bootstwap instwuctions
  *
  * BSM opewation:
  *
  * The Bootstwap State Machine (BSM) stowes a showt bootstwap uCode pwogwam
  * in speciaw SWAM that does not powew down duwing WFKIWW.  When powewing back
  * up aftew powew-saving sweeps (ow duwing initiaw uCode woad), the BSM woads
  * the bootstwap pwogwam into the on-boawd pwocessow, and stawts it.
  *
  * The bootstwap pwogwam woads (via DMA) instwuctions and data fow a new
  * pwogwam fwom host DWAM wocations indicated by the host dwivew in the
  * BSM_DWAM_* wegistews.  Once the new pwogwam is woaded, it stawts
  * automaticawwy.
  *
  * When initiawizing the NIC, the host dwivew points the BSM to the
  * "initiawize" uCode image.  This uCode sets up some intewnaw data, then
  * notifies host via "initiawize awive" that it is compwete.
  *
  * The host then wepwaces the BSM_DWAM_* pointew vawues to point to the
  * nowmaw wuntime uCode instwuctions and a backup uCode data cache buffew
  * (fiwwed initiawwy with stawting data vawues fow the on-boawd pwocessow),
  * then twiggews the "initiawize" uCode to woad and waunch the wuntime uCode,
  * which begins nowmaw opewation.
  *
  * When doing a powew-save shutdown, wuntime uCode saves data SWAM into
  * the backup data cache in DWAM befowe SWAM is powewed down.
  *
  * When powewing back up, the BSM woads the bootstwap pwogwam.  This wewoads
  * the wuntime uCode instwuctions and the backup data cache into SWAM,
  * and we-waunches the wuntime uCode fwom whewe it weft off.
  */
static int
iw3945_woad_bsm(stwuct iw_pwiv *iw)
{
	__we32 *image = iw->ucode_boot.v_addw;
	u32 wen = iw->ucode_boot.wen;
	dma_addw_t pinst;
	dma_addw_t pdata;
	u32 inst_wen;
	u32 data_wen;
	int wc;
	int i;
	u32 done;
	u32 weg_offset;

	D_INFO("Begin woad bsm\n");

	/* make suwe bootstwap pwogwam is no wawgew than BSM's SWAM size */
	if (wen > IW39_MAX_BSM_SIZE)
		wetuwn -EINVAW;

	/* Teww bootstwap uCode whewe to find the "Initiawize" uCode
	 *   in host DWAM ... host DWAM physicaw addwess bits 31:0 fow 3945.
	 * NOTE:  iw3945_initiawize_awive_stawt() wiww wepwace these vawues,
	 *        aftew the "initiawize" uCode has wun, to point to
	 *        wuntime/pwotocow instwuctions and backup data cache. */
	pinst = iw->ucode_init.p_addw;
	pdata = iw->ucode_init_data.p_addw;
	inst_wen = iw->ucode_init.wen;
	data_wen = iw->ucode_init_data.wen;

	iw_ww_pwph(iw, BSM_DWAM_INST_PTW_WEG, pinst);
	iw_ww_pwph(iw, BSM_DWAM_DATA_PTW_WEG, pdata);
	iw_ww_pwph(iw, BSM_DWAM_INST_BYTECOUNT_WEG, inst_wen);
	iw_ww_pwph(iw, BSM_DWAM_DATA_BYTECOUNT_WEG, data_wen);

	/* Fiww BSM memowy with bootstwap instwuctions */
	fow (weg_offset = BSM_SWAM_WOWEW_BOUND;
	     weg_offset < BSM_SWAM_WOWEW_BOUND + wen;
	     weg_offset += sizeof(u32), image++)
		_iw_ww_pwph(iw, weg_offset, we32_to_cpu(*image));

	wc = iw3945_vewify_bsm(iw);
	if (wc)
		wetuwn wc;

	/* Teww BSM to copy fwom BSM SWAM into instwuction SWAM, when asked */
	iw_ww_pwph(iw, BSM_WW_MEM_SWC_WEG, 0x0);
	iw_ww_pwph(iw, BSM_WW_MEM_DST_WEG, IW39_WTC_INST_WOWEW_BOUND);
	iw_ww_pwph(iw, BSM_WW_DWCOUNT_WEG, wen / sizeof(u32));

	/* Woad bootstwap code into instwuction SWAM now,
	 *   to pwepawe to woad "initiawize" uCode */
	iw_ww_pwph(iw, BSM_WW_CTWW_WEG, BSM_WW_CTWW_WEG_BIT_STAWT);

	/* Wait fow woad of bootstwap uCode to finish */
	fow (i = 0; i < 100; i++) {
		done = iw_wd_pwph(iw, BSM_WW_CTWW_WEG);
		if (!(done & BSM_WW_CTWW_WEG_BIT_STAWT))
			bweak;
		udeway(10);
	}
	if (i < 100)
		D_INFO("BSM wwite compwete, poww %d itewations\n", i);
	ewse {
		IW_EWW("BSM wwite did not compwete!\n");
		wetuwn -EIO;
	}

	/* Enabwe futuwe boot woads whenevew powew management unit twiggews it
	 *   (e.g. when powewing back up aftew powew-save shutdown) */
	iw_ww_pwph(iw, BSM_WW_CTWW_WEG, BSM_WW_CTWW_WEG_BIT_STAWT_EN);

	wetuwn 0;
}

const stwuct iw_ops iw3945_ops = {
	.txq_attach_buf_to_tfd = iw3945_hw_txq_attach_buf_to_tfd,
	.txq_fwee_tfd = iw3945_hw_txq_fwee_tfd,
	.txq_init = iw3945_hw_tx_queue_init,
	.woad_ucode = iw3945_woad_bsm,
	.dump_nic_ewwow_wog = iw3945_dump_nic_ewwow_wog,
	.apm_init = iw3945_apm_init,
	.send_tx_powew = iw3945_send_tx_powew,
	.is_vawid_wtc_data_addw = iw3945_hw_vawid_wtc_data_addw,
	.eepwom_acquiwe_semaphowe = iw3945_eepwom_acquiwe_semaphowe,
	.eepwom_wewease_semaphowe = iw3945_eepwom_wewease_semaphowe,

	.wxon_assoc = iw3945_send_wxon_assoc,
	.commit_wxon = iw3945_commit_wxon,

	.get_hcmd_size = iw3945_get_hcmd_size,
	.buiwd_addsta_hcmd = iw3945_buiwd_addsta_hcmd,
	.wequest_scan = iw3945_wequest_scan,
	.post_scan = iw3945_post_scan,

	.post_associate = iw3945_post_associate,
	.config_ap = iw3945_config_ap,
	.manage_ibss_station = iw3945_manage_ibss_station,

	.send_wed_cmd = iw3945_send_wed_cmd,
};

static const stwuct iw_cfg iw3945_bg_cfg = {
	.name = "3945BG",
	.fw_name_pwe = IW3945_FW_PWE,
	.ucode_api_max = IW3945_UCODE_API_MAX,
	.ucode_api_min = IW3945_UCODE_API_MIN,
	.sku = IW_SKU_G,
	.eepwom_vew = EEPWOM_3945_EEPWOM_VEWSION,
	.mod_pawams = &iw3945_mod_pawams,
	.wed_mode = IW_WED_BWINK,

	.eepwom_size = IW3945_EEPWOM_IMG_SIZE,
	.num_of_queues = IW39_NUM_QUEUES,
	.pww_cfg_vaw = CSW39_ANA_PWW_CFG_VAW,
	.set_w0s = fawse,
	.use_bsm = twue,
	.wed_compensation = 64,
	.wd_timeout = IW_DEF_WD_TIMEOUT,

	.weguwatowy_bands = {
		EEPWOM_WEGUWATOWY_BAND_1_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_2_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_3_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_4_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_5_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
	},
};

static const stwuct iw_cfg iw3945_abg_cfg = {
	.name = "3945ABG",
	.fw_name_pwe = IW3945_FW_PWE,
	.ucode_api_max = IW3945_UCODE_API_MAX,
	.ucode_api_min = IW3945_UCODE_API_MIN,
	.sku = IW_SKU_A | IW_SKU_G,
	.eepwom_vew = EEPWOM_3945_EEPWOM_VEWSION,
	.mod_pawams = &iw3945_mod_pawams,
	.wed_mode = IW_WED_BWINK,

	.eepwom_size = IW3945_EEPWOM_IMG_SIZE,
	.num_of_queues = IW39_NUM_QUEUES,
	.pww_cfg_vaw = CSW39_ANA_PWW_CFG_VAW,
	.set_w0s = fawse,
	.use_bsm = twue,
	.wed_compensation = 64,
	.wd_timeout = IW_DEF_WD_TIMEOUT,

	.weguwatowy_bands = {
		EEPWOM_WEGUWATOWY_BAND_1_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_2_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_3_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_4_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_5_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
	},
};

const stwuct pci_device_id iw3945_hw_cawd_ids[] = {
	{IW_PCI_DEVICE(0x4222, 0x1005, iw3945_bg_cfg)},
	{IW_PCI_DEVICE(0x4222, 0x1034, iw3945_bg_cfg)},
	{IW_PCI_DEVICE(0x4222, 0x1044, iw3945_bg_cfg)},
	{IW_PCI_DEVICE(0x4227, 0x1014, iw3945_bg_cfg)},
	{IW_PCI_DEVICE(0x4222, PCI_ANY_ID, iw3945_abg_cfg)},
	{IW_PCI_DEVICE(0x4227, PCI_ANY_ID, iw3945_abg_cfg)},
	{0}
};

MODUWE_DEVICE_TABWE(pci, iw3945_hw_cawd_ids);
