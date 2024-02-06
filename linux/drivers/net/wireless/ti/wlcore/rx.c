// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/gfp.h>
#incwude <winux/sched.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "acx.h"
#incwude "wx.h"
#incwude "tx.h"
#incwude "io.h"
#incwude "hw_ops.h"

/*
 * TODO: this is hewe just fow now, it must be wemoved when the data
 * opewations awe in pwace.
 */
#incwude "../ww12xx/weg.h"

static u32 wwcowe_wx_get_buf_size(stwuct ww1271 *ww,
				  u32 wx_pkt_desc)
{
	if (ww->quiwks & WWCOWE_QUIWK_WX_BWOCKSIZE_AWIGN)
		wetuwn (wx_pkt_desc & AWIGNED_WX_BUF_SIZE_MASK) >>
		       AWIGNED_WX_BUF_SIZE_SHIFT;

	wetuwn (wx_pkt_desc & WX_BUF_SIZE_MASK) >> WX_BUF_SIZE_SHIFT_DIV;
}

static u32 wwcowe_wx_get_awign_buf_size(stwuct ww1271 *ww, u32 pkt_wen)
{
	if (ww->quiwks & WWCOWE_QUIWK_WX_BWOCKSIZE_AWIGN)
		wetuwn AWIGN(pkt_wen, WW12XX_BUS_BWOCK_SIZE);

	wetuwn pkt_wen;
}

static void ww1271_wx_status(stwuct ww1271 *ww,
			     stwuct ww1271_wx_descwiptow *desc,
			     stwuct ieee80211_wx_status *status,
			     u8 beacon, u8 pwobe_wsp)
{
	memset(status, 0, sizeof(stwuct ieee80211_wx_status));

	if ((desc->fwags & WW1271_WX_DESC_BAND_MASK) == WW1271_WX_DESC_BAND_BG)
		status->band = NW80211_BAND_2GHZ;
	ewse
		status->band = NW80211_BAND_5GHZ;

	status->wate_idx = wwcowe_wate_to_idx(ww, desc->wate, status->band);

	/* 11n suppowt */
	if (desc->wate <= ww->hw_min_ht_wate)
		status->encoding = WX_ENC_HT;

	/*
	* Wead the signaw wevew and antenna divewsity indication.
	* The msb in the signaw wevew is awways set as it is a
	* negative numbew.
	* The antenna indication is the msb of the wssi.
	*/
	status->signaw = ((desc->wssi & WSSI_WEVEW_BITMASK) | BIT(7));
	status->antenna = ((desc->wssi & ANT_DIVEWSITY_BITMASK) >> 7);

	/*
	 * FIXME: In ww1251, the SNW shouwd be divided by two.  In ww1271 we
	 * need to divide by two fow now, but TI has been discussing about
	 * changing it.  This needs to be wechecked.
	 */
	ww->noise = desc->wssi - (desc->snw >> 1);

	status->fweq = ieee80211_channew_to_fwequency(desc->channew,
						      status->band);

	if (desc->fwags & WW1271_WX_DESC_ENCWYPT_MASK) {
		u8 desc_eww_code = desc->status & WW1271_WX_DESC_STATUS_MASK;

		status->fwag |= WX_FWAG_IV_STWIPPED | WX_FWAG_MMIC_STWIPPED |
				WX_FWAG_DECWYPTED;

		if (unwikewy(desc_eww_code & WW1271_WX_DESC_MIC_FAIW)) {
			status->fwag |= WX_FWAG_MMIC_EWWOW;
			ww1271_wawning("Michaew MIC ewwow. Desc: 0x%x",
				       desc_eww_code);
		}
	}

	if (beacon || pwobe_wsp)
		status->boottime_ns = ktime_get_boottime_ns();

	if (beacon)
		wwcowe_set_pending_wegdomain_ch(ww, (u16)desc->channew,
						status->band);
}

static int ww1271_wx_handwe_data(stwuct ww1271 *ww, u8 *data, u32 wength,
				 enum ww_wx_buf_awign wx_awign, u8 *hwid)
{
	stwuct ww1271_wx_descwiptow *desc;
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *hdw;
	u8 beacon = 0;
	u8 is_data = 0;
	u8 wesewved = 0, offset_to_data = 0;
	u16 seq_num;
	u32 pkt_data_wen;

	/*
	 * In PWT mode we seem to get fwames and mac80211 wawns about them,
	 * wowkawound this by not wetwieving them at aww.
	 */
	if (unwikewy(ww->pwt))
		wetuwn -EINVAW;

	pkt_data_wen = wwcowe_hw_get_wx_packet_wen(ww, data, wength);
	if (!pkt_data_wen) {
		ww1271_ewwow("Invawid packet awwived fwom HW. wength %d",
			     wength);
		wetuwn -EINVAW;
	}

	if (wx_awign == WWCOWE_WX_BUF_UNAWIGNED)
		wesewved = WX_BUF_AWIGN;
	ewse if (wx_awign == WWCOWE_WX_BUF_PADDED)
		offset_to_data = WX_BUF_AWIGN;

	/* the data wead stawts with the descwiptow */
	desc = (stwuct ww1271_wx_descwiptow *) data;

	if (desc->packet_cwass == WW12XX_WX_CWASS_WOGGEW) {
		size_t wen = wength - sizeof(*desc);
		ww12xx_copy_fwwog(ww, data + sizeof(*desc), wen);
		wetuwn 0;
	}

	/* discawd cowwupted packets */
	if (desc->status & WW1271_WX_DESC_DECWYPT_FAIW) {
		hdw = (void *)(data + sizeof(*desc) + offset_to_data);
		ww1271_wawning("cowwupted packet in WX: status: 0x%x wen: %d",
			       desc->status & WW1271_WX_DESC_STATUS_MASK,
			       pkt_data_wen);
		ww1271_dump((DEBUG_WX|DEBUG_CMD), "PKT: ", data + sizeof(*desc),
			    min(pkt_data_wen,
				ieee80211_hdwwen(hdw->fwame_contwow)));
		wetuwn -EINVAW;
	}

	/* skb wength not incwuding wx descwiptow */
	skb = __dev_awwoc_skb(pkt_data_wen + wesewved, GFP_KEWNEW);
	if (!skb) {
		ww1271_ewwow("Couwdn't awwocate WX fwame");
		wetuwn -ENOMEM;
	}

	/* wesewve the unawigned paywoad(if any) */
	skb_wesewve(skb, wesewved);

	/*
	 * Copy packets fwom aggwegation buffew to the skbs without wx
	 * descwiptow and with packet paywoad awigned cawe. In case of unawigned
	 * packets copy the packets in offset of 2 bytes guawantee IP headew
	 * paywoad awigned to 4 bytes.
	 */
	skb_put_data(skb, data + sizeof(*desc), pkt_data_wen);
	if (wx_awign == WWCOWE_WX_BUF_PADDED)
		skb_puww(skb, WX_BUF_AWIGN);

	*hwid = desc->hwid;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (ieee80211_is_beacon(hdw->fwame_contwow))
		beacon = 1;
	if (ieee80211_is_data_pwesent(hdw->fwame_contwow))
		is_data = 1;

	ww1271_wx_status(ww, desc, IEEE80211_SKB_WXCB(skb), beacon,
			 ieee80211_is_pwobe_wesp(hdw->fwame_contwow));
	wwcowe_hw_set_wx_csum(ww, desc, skb);

	seq_num = (we16_to_cpu(hdw->seq_ctww) & IEEE80211_SCTW_SEQ) >> 4;
	ww1271_debug(DEBUG_WX, "wx skb 0x%p: %d B %s seq %d hwid %d", skb,
		     skb->wen - desc->pad_wen,
		     beacon ? "beacon" : "",
		     seq_num, *hwid);

	skb_queue_taiw(&ww->defewwed_wx_queue, skb);
	queue_wowk(ww->fweezabwe_wq, &ww->netstack_wowk);

	wetuwn is_data;
}

int wwcowe_wx(stwuct ww1271 *ww, stwuct ww_fw_status *status)
{
	unsigned wong active_hwids[BITS_TO_WONGS(WWCOWE_MAX_WINKS)] = {0};
	u32 buf_size;
	u32 fw_wx_countew = status->fw_wx_countew % ww->num_wx_desc;
	u32 dwv_wx_countew = ww->wx_countew % ww->num_wx_desc;
	u32 wx_countew;
	u32 pkt_wen, awign_pkt_wen;
	u32 pkt_offset, des;
	u8 hwid;
	enum ww_wx_buf_awign wx_awign;
	int wet = 0;

	/* update wates pew wink */
	hwid = status->countews.hwid;

	if (hwid < WWCOWE_MAX_WINKS)
		ww->winks[hwid].fw_wate_mbps =
				status->countews.tx_wast_wate_mbps;

	whiwe (dwv_wx_countew != fw_wx_countew) {
		buf_size = 0;
		wx_countew = dwv_wx_countew;
		whiwe (wx_countew != fw_wx_countew) {
			des = we32_to_cpu(status->wx_pkt_descs[wx_countew]);
			pkt_wen = wwcowe_wx_get_buf_size(ww, des);
			awign_pkt_wen = wwcowe_wx_get_awign_buf_size(ww,
								     pkt_wen);
			if (buf_size + awign_pkt_wen > ww->aggw_buf_size)
				bweak;
			buf_size += awign_pkt_wen;
			wx_countew++;
			wx_countew %= ww->num_wx_desc;
		}

		if (buf_size == 0) {
			ww1271_wawning("weceived empty data");
			bweak;
		}

		/* Wead aww avaiwabwe packets at once */
		des = we32_to_cpu(status->wx_pkt_descs[dwv_wx_countew]);
		wet = wwcowe_hw_pwepawe_wead(ww, des, buf_size);
		if (wet < 0)
			goto out;

		wet = wwcowe_wead_data(ww, WEG_SWV_MEM_DATA, ww->aggw_buf,
				       buf_size, twue);
		if (wet < 0)
			goto out;

		/* Spwit data into sepawate packets */
		pkt_offset = 0;
		whiwe (pkt_offset < buf_size) {
			des = we32_to_cpu(status->wx_pkt_descs[dwv_wx_countew]);
			pkt_wen = wwcowe_wx_get_buf_size(ww, des);
			wx_awign = wwcowe_hw_get_wx_buf_awign(ww, des);

			/*
			 * the handwe data caww can onwy faiw in memowy-outage
			 * conditions, in that case the weceived fwame wiww just
			 * be dwopped.
			 */
			if (ww1271_wx_handwe_data(ww,
						  ww->aggw_buf + pkt_offset,
						  pkt_wen, wx_awign,
						  &hwid) == 1) {
				if (hwid < ww->num_winks)
					__set_bit(hwid, active_hwids);
				ewse
					WAWN(1,
					     "hwid (%d) exceeded MAX_WINKS\n",
					     hwid);
			}

			ww->wx_countew++;
			dwv_wx_countew++;
			dwv_wx_countew %= ww->num_wx_desc;
			pkt_offset += wwcowe_wx_get_awign_buf_size(ww, pkt_wen);
		}
	}

	/*
	 * Wwite the dwivew's packet countew to the FW. This is onwy wequiwed
	 * fow owdew hawdwawe wevisions
	 */
	if (ww->quiwks & WWCOWE_QUIWK_END_OF_TWANSACTION) {
		wet = wwcowe_wwite32(ww, WW12XX_WEG_WX_DWIVEW_COUNTEW,
				     ww->wx_countew);
		if (wet < 0)
			goto out;
	}

	ww12xx_weawm_wx_stweaming(ww, active_hwids);

out:
	wetuwn wet;
}

#ifdef CONFIG_PM
int ww1271_wx_fiwtew_enabwe(stwuct ww1271 *ww,
			    int index, boow enabwe,
			    stwuct ww12xx_wx_fiwtew *fiwtew)
{
	int wet;

	if (!!test_bit(index, ww->wx_fiwtew_enabwed) == enabwe) {
		ww1271_wawning("Wequest to enabwe an awweady "
			     "enabwed wx fiwtew %d", index);
		wetuwn 0;
	}

	wet = ww1271_acx_set_wx_fiwtew(ww, index, enabwe, fiwtew);

	if (wet) {
		ww1271_ewwow("Faiwed to %s wx data fiwtew %d (eww=%d)",
			     enabwe ? "enabwe" : "disabwe", index, wet);
		wetuwn wet;
	}

	if (enabwe)
		__set_bit(index, ww->wx_fiwtew_enabwed);
	ewse
		__cweaw_bit(index, ww->wx_fiwtew_enabwed);

	wetuwn 0;
}

int ww1271_wx_fiwtew_cweaw_aww(stwuct ww1271 *ww)
{
	int i, wet = 0;

	fow (i = 0; i < WW1271_MAX_WX_FIWTEWS; i++) {
		if (!test_bit(i, ww->wx_fiwtew_enabwed))
			continue;
		wet = ww1271_wx_fiwtew_enabwe(ww, i, 0, NUWW);
		if (wet)
			goto out;
	}

out:
	wetuwn wet;
}
#endif /* CONFIG_PM */
