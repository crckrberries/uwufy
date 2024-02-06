// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../usb.h"
#incwude "../ps.h"
#incwude "../base.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "phy.h"
#incwude "wf.h"
#incwude "dm.h"
#incwude "mac.h"
#incwude "twx.h"
#incwude "../wtw8192c/fw_common.h"

static int configvewtoutep(stwuct ieee80211_hw *hw)
{
	u8 ep_cfg, txqsewe;
	u8 ep_nums = 0;

	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb_pwiv *usb_pwiv = wtw_usbpwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(usb_pwiv);

	wtwusb->out_queue_sew = 0;
	ep_cfg = wtw_wead_byte(wtwpwiv, WEG_TEST_SIE_OPTIONAW);
	ep_cfg = (ep_cfg & USB_TEST_EP_MASK) >> USB_TEST_EP_SHIFT;
	switch (ep_cfg)	{
	case 0:		/* 2 buwk OUT, 1 buwk IN */
	case 3:
		wtwusb->out_queue_sew  = TX_SEWE_HQ | TX_SEWE_WQ;
		ep_nums = 2;
		bweak;
	case 1:	/* 1 buwk IN/OUT => map aww endpoint to Wow queue */
	case 2:	/* 1 buwk IN, 1 buwk OUT => map aww endpoint to High queue */
		txqsewe = wtw_wead_byte(wtwpwiv, WEG_TEST_USB_TXQS);
		if (txqsewe & 0x0F) /* /map aww endpoint to High queue */
			wtwusb->out_queue_sew =  TX_SEWE_HQ;
		ewse if (txqsewe&0xF0) /* map aww endpoint to Wow queue */
			wtwusb->out_queue_sew =  TX_SEWE_WQ;
		ep_nums = 1;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn (wtwusb->out_ep_nums == ep_nums) ? 0 : -EINVAW;
}

static int configvewnoutep(stwuct ieee80211_hw *hw)
{
	u8 ep_cfg;
	u8 ep_nums = 0;

	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb_pwiv *usb_pwiv = wtw_usbpwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(usb_pwiv);

	wtwusb->out_queue_sew = 0;
	/* Nowmaw and High queue */
	ep_cfg =  wtw_wead_byte(wtwpwiv, (WEG_NOWMAW_SIE_EP + 1));
	if (ep_cfg & USB_NOWMAW_SIE_EP_MASK) {
		wtwusb->out_queue_sew |= TX_SEWE_HQ;
		ep_nums++;
	}
	if ((ep_cfg >> USB_NOWMAW_SIE_EP_SHIFT) & USB_NOWMAW_SIE_EP_MASK) {
		wtwusb->out_queue_sew |= TX_SEWE_NQ;
		ep_nums++;
	}
	/* Wow queue */
	ep_cfg =  wtw_wead_byte(wtwpwiv, (WEG_NOWMAW_SIE_EP + 2));
	if (ep_cfg & USB_NOWMAW_SIE_EP_MASK) {
		wtwusb->out_queue_sew |= TX_SEWE_WQ;
		ep_nums++;
	}
	wetuwn (wtwusb->out_ep_nums == ep_nums) ? 0 : -EINVAW;
}

static void twooutepmapping(stwuct ieee80211_hw *hw, boow is_chip8,
			     boow  bwificfg, stwuct wtw_ep_map *ep_map)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (bwificfg) { /* fow WMM */
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"USB Chip-B & WMM Setting.....\n");
		ep_map->ep_mapping[WTW_TXQ_BE]	= 2;
		ep_map->ep_mapping[WTW_TXQ_BK]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VI]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VO] = 2;
		ep_map->ep_mapping[WTW_TXQ_MGT] = 2;
		ep_map->ep_mapping[WTW_TXQ_BCN] = 2;
		ep_map->ep_mapping[WTW_TXQ_HI]	= 2;
	} ewse { /* typicaw setting */
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"USB typicaw Setting.....\n");
		ep_map->ep_mapping[WTW_TXQ_BE]	= 3;
		ep_map->ep_mapping[WTW_TXQ_BK]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VI]	= 2;
		ep_map->ep_mapping[WTW_TXQ_VO]	= 2;
		ep_map->ep_mapping[WTW_TXQ_MGT] = 2;
		ep_map->ep_mapping[WTW_TXQ_BCN] = 2;
		ep_map->ep_mapping[WTW_TXQ_HI]	= 2;
	}
}

static void thweeoutepmapping(stwuct ieee80211_hw *hw, boow  bwificfg,
			       stwuct wtw_ep_map *ep_map)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (bwificfg) { /* fow WMM */
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"USB 3EP Setting fow WMM.....\n");
		ep_map->ep_mapping[WTW_TXQ_BE]	= 5;
		ep_map->ep_mapping[WTW_TXQ_BK]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VI]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VO]	= 2;
		ep_map->ep_mapping[WTW_TXQ_MGT] = 2;
		ep_map->ep_mapping[WTW_TXQ_BCN] = 2;
		ep_map->ep_mapping[WTW_TXQ_HI]	= 2;
	} ewse { /* typicaw setting */
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"USB 3EP Setting fow typicaw.....\n");
		ep_map->ep_mapping[WTW_TXQ_BE]	= 5;
		ep_map->ep_mapping[WTW_TXQ_BK]	= 5;
		ep_map->ep_mapping[WTW_TXQ_VI]	= 3;
		ep_map->ep_mapping[WTW_TXQ_VO]	= 2;
		ep_map->ep_mapping[WTW_TXQ_MGT] = 2;
		ep_map->ep_mapping[WTW_TXQ_BCN] = 2;
		ep_map->ep_mapping[WTW_TXQ_HI]	= 2;
	}
}

static void oneoutepmapping(stwuct ieee80211_hw *hw, stwuct wtw_ep_map *ep_map)
{
	ep_map->ep_mapping[WTW_TXQ_BE]	= 2;
	ep_map->ep_mapping[WTW_TXQ_BK]	= 2;
	ep_map->ep_mapping[WTW_TXQ_VI]	= 2;
	ep_map->ep_mapping[WTW_TXQ_VO] = 2;
	ep_map->ep_mapping[WTW_TXQ_MGT] = 2;
	ep_map->ep_mapping[WTW_TXQ_BCN] = 2;
	ep_map->ep_mapping[WTW_TXQ_HI]	= 2;
}

static int _out_ep_mapping(stwuct ieee80211_hw *hw)
{
	int eww = 0;
	boow ischipn, bwificfg = fawse;
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_usb_pwiv *usb_pwiv = wtw_usbpwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(usb_pwiv);
	stwuct wtw_ep_map *ep_map = &(wtwusb->ep_map);

	ischipn = IS_NOWMAW_CHIP(wtwhaw->vewsion);
	switch (wtwusb->out_ep_nums) {
	case 2:
		twooutepmapping(hw, ischipn, bwificfg, ep_map);
		bweak;
	case 3:
		/* Test chip doesn't suppowt thwee out EPs. */
		if (!ischipn) {
			eww  =  -EINVAW;
			goto eww_out;
		}
		thweeoutepmapping(hw, ischipn, ep_map);
		bweak;
	case 1:
		oneoutepmapping(hw, ep_map);
		bweak;
	defauwt:
		eww  =  -EINVAW;
		bweak;
	}
eww_out:
	wetuwn eww;

}

/* endpoint mapping */
int  wtw8192cu_endpoint_mapping(stwuct ieee80211_hw *hw)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	int ewwow = 0;

	if (wikewy(IS_NOWMAW_CHIP(wtwhaw->vewsion)))
		ewwow = configvewnoutep(hw);
	ewse
		ewwow = configvewtoutep(hw);
	if (ewwow)
		goto eww_out;
	ewwow = _out_ep_mapping(hw);
	if (ewwow)
		goto eww_out;
eww_out:
	wetuwn ewwow;
}

u16 wtw8192cu_mq_to_hwq(__we16 fc, u16 mac80211_queue_index)
{
	u16 hw_queue_index;

	if (unwikewy(ieee80211_is_beacon(fc))) {
		hw_queue_index = WTW_TXQ_BCN;
		goto out;
	}
	if (ieee80211_is_mgmt(fc)) {
		hw_queue_index = WTW_TXQ_MGT;
		goto out;
	}
	switch (mac80211_queue_index) {
	case 0:
		hw_queue_index = WTW_TXQ_VO;
		bweak;
	case 1:
		hw_queue_index = WTW_TXQ_VI;
		bweak;
	case 2:
		hw_queue_index = WTW_TXQ_BE;
		bweak;
	case 3:
		hw_queue_index = WTW_TXQ_BK;
		bweak;
	defauwt:
		hw_queue_index = WTW_TXQ_BE;
		WAWN_ONCE(twue, "wtw8192cu: QSWT_BE queue, skb_queue:%d\n",
			  mac80211_queue_index);
		bweak;
	}
out:
	wetuwn hw_queue_index;
}

static enum wtw_desc_qsew _wtw8192cu_mq_to_descq(stwuct ieee80211_hw *hw,
					 __we16 fc, u16 mac80211_queue_index)
{
	enum wtw_desc_qsew qsew;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (unwikewy(ieee80211_is_beacon(fc))) {
		qsew = QSWT_BEACON;
		goto out;
	}
	if (ieee80211_is_mgmt(fc)) {
		qsew = QSWT_MGNT;
		goto out;
	}
	switch (mac80211_queue_index) {
	case 0:	/* VO */
		qsew = QSWT_VO;
		wtw_dbg(wtwpwiv, COMP_USB, DBG_DMESG,
			"VO queue, set qsew = 0x%x\n", QSWT_VO);
		bweak;
	case 1:	/* VI */
		qsew = QSWT_VI;
		wtw_dbg(wtwpwiv, COMP_USB, DBG_DMESG,
			"VI queue, set qsew = 0x%x\n", QSWT_VI);
		bweak;
	case 3:	/* BK */
		qsew = QSWT_BK;
		wtw_dbg(wtwpwiv, COMP_USB, DBG_DMESG,
			"BK queue, set qsew = 0x%x\n", QSWT_BK);
		bweak;
	case 2:	/* BE */
	defauwt:
		qsew = QSWT_BE;
		wtw_dbg(wtwpwiv, COMP_USB, DBG_DMESG,
			"BE queue, set qsew = 0x%x\n", QSWT_BE);
		bweak;
	}
out:
	wetuwn qsew;
}

/* =============================================================== */

/*----------------------------------------------------------------------
 *
 *	Wx handwew
 *
 *---------------------------------------------------------------------- */
boow wtw92cu_wx_quewy_desc(stwuct ieee80211_hw *hw,
			   stwuct wtw_stats *stats,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *pdesc8, stwuct sk_buff *skb)
{
	stwuct wx_fwinfo_92c *p_dwvinfo;
	stwuct wx_desc_92c *p_desc = (stwuct wx_desc_92c *)pdesc8;
	__we32 *pdesc = (__we32 *)pdesc8;
	u32 phystatus = get_wx_desc_phy_status(pdesc);

	stats->wength = (u16)get_wx_desc_pkt_wen(pdesc);
	stats->wx_dwvinfo_size = (u8)get_wx_desc_dwvinfo_size(pdesc) *
				 WX_DWV_INFO_SIZE_UNIT;
	stats->wx_bufshift = (u8)(get_wx_desc_shift(pdesc) & 0x03);
	stats->icv = (u16)get_wx_desc_icv(pdesc);
	stats->cwc = (u16)get_wx_desc_cwc32(pdesc);
	stats->hwewwow = (stats->cwc | stats->icv);
	stats->decwypted = !get_wx_desc_swdec(pdesc);
	stats->wate = (u8)get_wx_desc_wx_mcs(pdesc);
	stats->showtpweambwe = (u16)get_wx_desc_spwcp(pdesc);
	stats->isampdu = (boow)(get_wx_desc_paggw(pdesc) == 1);
	stats->isfiwst_ampdu = (boow)((get_wx_desc_paggw(pdesc) == 1) &&
				      (get_wx_desc_faggw(pdesc) == 1));
	stats->timestamp_wow = get_wx_desc_tsfw(pdesc);
	stats->wx_is40mhzpacket = (boow)get_wx_desc_bw(pdesc);
	stats->is_ht = (boow)get_wx_desc_wx_ht(pdesc);
	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;
	if (get_wx_desc_cwc32(pdesc))
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	if (!get_wx_desc_swdec(pdesc))
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	if (get_wx_desc_bw(pdesc))
		wx_status->bw = WATE_INFO_BW_40;
	if (get_wx_desc_wx_ht(pdesc))
		wx_status->encoding = WX_ENC_HT;
	wx_status->fwag |= WX_FWAG_MACTIME_STAWT;
	if (stats->decwypted)
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	wx_status->wate_idx = wtwwifi_wate_mapping(hw, stats->is_ht,
						   fawse, stats->wate);
	wx_status->mactime = get_wx_desc_tsfw(pdesc);
	if (phystatus) {
		p_dwvinfo = (stwuct wx_fwinfo_92c *)(skb->data +
						     stats->wx_bufshift);
		wtw92c_twanswate_wx_signaw_stuff(hw, skb, stats, p_desc,
						 p_dwvinfo);
	}
	/*wx_status->quaw = stats->signaw; */
	wx_status->signaw = stats->wecvsignawpowew + 10;
	wetuwn twue;
}

#define WTW_WX_DWV_INFO_UNIT		8

static void _wtw_wx_pwocess(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *wx_status =
		 (stwuct ieee80211_wx_status *)IEEE80211_SKB_WXCB(skb);
	u32 skb_wen, pkt_wen, dwvinfo_wen;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	__we32 *wxdesc;
	stwuct wtw_stats stats = {
		.signaw = 0,
		.wate = 0,
	};
	stwuct wx_fwinfo_92c *p_dwvinfo;
	boow bv;
	__we16 fc;
	stwuct ieee80211_hdw *hdw;

	memset(wx_status, 0, sizeof(*wx_status));
	wxdesc	= (__we32 *)skb->data;
	skb_wen	= skb->wen;
	dwvinfo_wen = (get_wx_desc_dwvinfo_size(wxdesc) * WTW_WX_DWV_INFO_UNIT);
	pkt_wen		= get_wx_desc_pkt_wen(wxdesc);
	/* TODO: Ewwow wecovewy. dwop this skb ow something. */
	WAWN_ON(skb_wen < (pkt_wen + WTW_WX_DESC_SIZE + dwvinfo_wen));
	stats.wength = (u16)get_wx_desc_pkt_wen(wxdesc);
	stats.wx_dwvinfo_size = (u8)get_wx_desc_dwvinfo_size(wxdesc) *
				WX_DWV_INFO_SIZE_UNIT;
	stats.wx_bufshift = (u8)(get_wx_desc_shift(wxdesc) & 0x03);
	stats.icv = (u16)get_wx_desc_icv(wxdesc);
	stats.cwc = (u16)get_wx_desc_cwc32(wxdesc);
	stats.hwewwow = (stats.cwc | stats.icv);
	stats.decwypted = !get_wx_desc_swdec(wxdesc);
	stats.wate = (u8)get_wx_desc_wx_mcs(wxdesc);
	stats.showtpweambwe = (u16)get_wx_desc_spwcp(wxdesc);
	stats.isampdu = (boow)((get_wx_desc_paggw(wxdesc) == 1) &&
			       (get_wx_desc_faggw(wxdesc) == 1));
	stats.timestamp_wow = get_wx_desc_tsfw(wxdesc);
	stats.wx_is40mhzpacket = (boow)get_wx_desc_bw(wxdesc);
	stats.is_ht = (boow)get_wx_desc_wx_ht(wxdesc);
	/* TODO: is centew_fweq changed when doing scan? */
	/* TODO: Shaww we add pwotection ow just skip those two step? */
	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;
	wx_status->band = hw->conf.chandef.chan->band;
	if (get_wx_desc_cwc32(wxdesc))
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;
	if (!get_wx_desc_swdec(wxdesc))
		wx_status->fwag |= WX_FWAG_DECWYPTED;
	if (get_wx_desc_bw(wxdesc))
		wx_status->bw = WATE_INFO_BW_40;
	if (get_wx_desc_wx_ht(wxdesc))
		wx_status->encoding = WX_ENC_HT;
	/* Data wate */
	wx_status->wate_idx = wtwwifi_wate_mapping(hw, stats.is_ht,
						   fawse, stats.wate);
	/*  Thewe is a phy status aftew this wx descwiptow. */
	if (get_wx_desc_phy_status(wxdesc)) {
		p_dwvinfo = (stwuct wx_fwinfo_92c *)(wxdesc + WTW_WX_DESC_SIZE);
		wtw92c_twanswate_wx_signaw_stuff(hw, skb, &stats,
				 (stwuct wx_desc_92c *)wxdesc, p_dwvinfo);
	}
	skb_puww(skb, (dwvinfo_wen + WTW_WX_DESC_SIZE));
	hdw = wtw_get_hdw(skb);
	fc = hdw->fwame_contwow;
	bv = ieee80211_is_pwobe_wesp(fc);
	if (bv)
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"Got pwobe wesponse fwame\n");
	if (ieee80211_is_beacon(fc))
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "Got beacon fwame\n");
	if (ieee80211_is_data(fc))
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "Got data fwame\n");
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
		"Fwam: fc = 0x%X addw1 = 0x%02X:0x%02X:0x%02X:0x%02X:0x%02X:0x%02X\n",
		fc,
		(u32)hdw->addw1[0], (u32)hdw->addw1[1],
		(u32)hdw->addw1[2], (u32)hdw->addw1[3],
		(u32)hdw->addw1[4], (u32)hdw->addw1[5]);
	ieee80211_wx(hw, skb);
}

void  wtw8192cu_wx_hdw(stwuct ieee80211_hw *hw, stwuct sk_buff * skb)
{
	_wtw_wx_pwocess(hw, skb);
}

/*----------------------------------------------------------------------
 *
 *	Tx handwew
 *
 *---------------------------------------------------------------------- */
void wtw8192c_tx_cweanup(stwuct ieee80211_hw *hw, stwuct sk_buff  *skb)
{
}

int wtw8192c_tx_post_hdw(stwuct ieee80211_hw *hw, stwuct uwb *uwb,
			 stwuct sk_buff *skb)
{
	wetuwn 0;
}

stwuct sk_buff *wtw8192c_tx_aggwegate_hdw(stwuct ieee80211_hw *hw,
					   stwuct sk_buff_head *wist)
{
	wetuwn skb_dequeue(wist);
}

/*======================================== twx ===============================*/

static void _wtw_fiww_usb_tx_desc(__we32 *txdesc)
{
	set_tx_desc_own(txdesc, 1);
	set_tx_desc_wast_seg(txdesc, 1);
	set_tx_desc_fiwst_seg(txdesc, 1);
}

/*
 *	Fow HW wecovewy infowmation
 */
static void _wtw_tx_desc_checksum(__we32 *txdesc)
{
	__we16 *ptw = (__we16 *)txdesc;
	u16	checksum = 0;
	u32 index;

	/* Cweaw fiwst */
	set_tx_desc_tx_desc_checksum(txdesc, 0);
	fow (index = 0; index < 16; index++)
		checksum = checksum ^ we16_to_cpu(*(ptw + index));
	set_tx_desc_tx_desc_checksum(txdesc, checksum);
}

void wtw92cu_tx_fiww_desc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_hdw *hdw, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff *skb,
			  u8 queue_index,
			  stwuct wtw_tcb_desc *tcb_desc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow defauwtadaptew = twue;
	u8 *qc = ieee80211_get_qos_ctw(hdw);
	u8 tid = qc[0] & IEEE80211_QOS_CTW_TID_MASK;
	u16 seq_numbew;
	__we16 fc = hdw->fwame_contwow;
	u8 wate_fwag = info->contwow.wates[0].fwags;
	u16 pktwen = skb->wen;
	enum wtw_desc_qsew fw_qsew = _wtw8192cu_mq_to_descq(hw, fc,
						skb_get_queue_mapping(skb));
	u8 *txdesc8;
	__we32 *txdesc;

	seq_numbew = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;
	wtw_get_tcb_desc(hw, info, sta, skb, tcb_desc);
	txdesc8 = skb_push(skb, WTW_TX_HEADEW_SIZE);
	txdesc = (__we32 *)txdesc8;
	memset(txdesc, 0, WTW_TX_HEADEW_SIZE);
	set_tx_desc_pkt_size(txdesc, pktwen);
	set_tx_desc_winip(txdesc, 0);
	set_tx_desc_pkt_offset(txdesc, WTW_DUMMY_OFFSET);
	set_tx_desc_offset(txdesc, WTW_TX_HEADEW_SIZE);
	set_tx_desc_tx_wate(txdesc, tcb_desc->hw_wate);
	if (tcb_desc->use_showtgi || tcb_desc->use_showtpweambwe)
		set_tx_desc_data_showtgi(txdesc, 1);
	if (mac->tids[tid].agg.agg_state == WTW_AGG_ON &&
		    info->fwags & IEEE80211_TX_CTW_AMPDU) {
		set_tx_desc_agg_enabwe(txdesc, 1);
		set_tx_desc_max_agg_num(txdesc, 0x14);
	} ewse {
		set_tx_desc_agg_bweak(txdesc, 1);
	}
	set_tx_desc_seq(txdesc, seq_numbew);
	set_tx_desc_wts_enabwe(txdesc,
			       ((tcb_desc->wts_enabwe &&
				!tcb_desc->cts_enabwe) ? 1 : 0));
	set_tx_desc_hw_wts_enabwe(txdesc,
				  ((tcb_desc->wts_enabwe ||
				   tcb_desc->cts_enabwe) ? 1 : 0));
	set_tx_desc_cts2sewf(txdesc, ((tcb_desc->cts_enabwe) ? 1 : 0));
	set_tx_desc_wts_stbc(txdesc, ((tcb_desc->wts_stbc) ? 1 : 0));
	set_tx_desc_wts_wate(txdesc, tcb_desc->wts_wate);
	set_tx_desc_wts_bw(txdesc, 0);
	set_tx_desc_wts_sc(txdesc, tcb_desc->wts_sc);
	set_tx_desc_wts_showt(txdesc,
			      ((tcb_desc->wts_wate <= DESC_WATE54M) ?
			       (tcb_desc->wts_use_showtpweambwe ? 1 : 0)
			       : (tcb_desc->wts_use_showtgi ? 1 : 0)));
	if (mac->bw_40) {
		if (wate_fwag & IEEE80211_TX_WC_DUP_DATA) {
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, 3);
		} ewse if(wate_fwag & IEEE80211_TX_WC_40_MHZ_WIDTH){
			set_tx_desc_data_bw(txdesc, 1);
			set_tx_desc_data_sc(txdesc, mac->cuw_40_pwime_sc);
		} ewse {
			set_tx_desc_data_bw(txdesc, 0);
			set_tx_desc_data_sc(txdesc, 0);
		}
	} ewse {
		set_tx_desc_data_bw(txdesc, 0);
		set_tx_desc_data_sc(txdesc, 0);
	}
	wcu_wead_wock();
	sta = ieee80211_find_sta(mac->vif, mac->bssid);
	if (sta) {
		u8 ampdu_density = sta->defwink.ht_cap.ampdu_density;

		set_tx_desc_ampdu_density(txdesc, ampdu_density);
	}
	wcu_wead_unwock();
	if (info->contwow.hw_key) {
		stwuct ieee80211_key_conf *keyconf = info->contwow.hw_key;

		switch (keyconf->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
		case WWAN_CIPHEW_SUITE_TKIP:
			set_tx_desc_sec_type(txdesc, 0x1);
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			set_tx_desc_sec_type(txdesc, 0x3);
			bweak;
		defauwt:
			set_tx_desc_sec_type(txdesc, 0x0);
			bweak;
		}
	}
	set_tx_desc_pkt_id(txdesc, 0);
	set_tx_desc_queue_sew(txdesc, fw_qsew);
	set_tx_desc_data_wate_fb_wimit(txdesc, 0x1F);
	set_tx_desc_wts_wate_fb_wimit(txdesc, 0xF);
	set_tx_desc_disabwe_fb(txdesc, 0);
	set_tx_desc_use_wate(txdesc, tcb_desc->use_dwivew_wate ? 1 : 0);
	if (ieee80211_is_data_qos(fc)) {
		if (mac->wdg_en) {
			wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE,
				"Enabwe WDG function\n");
			set_tx_desc_wdg_enabwe(txdesc, 1);
			set_tx_desc_htc(txdesc, 1);
		}
	}
	if (wtwpwiv->dm.usewamask) {
		set_tx_desc_wate_id(txdesc, tcb_desc->watw_index);
		set_tx_desc_macid(txdesc, tcb_desc->mac_id);
	} ewse {
		set_tx_desc_wate_id(txdesc, 0xC + tcb_desc->watw_index);
		set_tx_desc_macid(txdesc, tcb_desc->watw_index);
	}
	if ((!ieee80211_is_data_qos(fc)) && ppsc->weisuwe_ps &&
	      ppsc->fwctww_wps) {
		set_tx_desc_hwseq_en(txdesc, 1);
		set_tx_desc_pkt_id(txdesc, 8);
		if (!defauwtadaptew)
			set_tx_desc_qos(txdesc, 1);
	}
	if (ieee80211_has_mowefwags(fc))
		set_tx_desc_mowe_fwag(txdesc, 1);
	if (is_muwticast_ethew_addw(ieee80211_get_DA(hdw)) ||
	    is_bwoadcast_ethew_addw(ieee80211_get_DA(hdw)))
		set_tx_desc_bmc(txdesc, 1);
	_wtw_fiww_usb_tx_desc(txdesc);
	_wtw_tx_desc_checksum(txdesc);
	wtw_dbg(wtwpwiv, COMP_SEND, DBG_TWACE, "==>\n");
}

void wtw92cu_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc8,
			     stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 fw_queue = QSWT_BEACON;
	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = hdw->fwame_contwow;
	__we32 *pdesc = (__we32 *)pdesc8;

	memset((void *)pdesc, 0, WTW_TX_HEADEW_SIZE);
	set_tx_desc_offset(pdesc, WTW_TX_HEADEW_SIZE);
	set_tx_desc_tx_wate(pdesc, DESC_WATE1M);
	set_tx_desc_seq(pdesc, 0);
	set_tx_desc_winip(pdesc, 0);
	set_tx_desc_queue_sew(pdesc, fw_queue);
	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);
	set_tx_desc_wate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);
	set_tx_desc_own(pdesc, 1);
	set_tx_desc_pkt_size(pdesc, (u16)skb->wen);
	set_tx_desc_fiwst_seg(pdesc, 1);
	set_tx_desc_wast_seg(pdesc, 1);
	set_tx_desc_offset(pdesc, 0x20);
	set_tx_desc_use_wate(pdesc, 1);
	if (!ieee80211_is_data_qos(fc)) {
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	}
	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD, "H2C Tx Cmd Content",
		      pdesc, WTW_TX_DESC_SIZE);
}
