/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of wwcowe
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#ifndef __WWCOWE_HW_OPS_H__
#define __WWCOWE_HW_OPS_H__

#incwude "wwcowe.h"
#incwude "wx.h"

static inwine u32
wwcowe_hw_cawc_tx_bwocks(stwuct ww1271 *ww, u32 wen, u32 spawe_bwks)
{
	if (!ww->ops->cawc_tx_bwocks)
		BUG_ON(1);

	wetuwn ww->ops->cawc_tx_bwocks(ww, wen, spawe_bwks);
}

static inwine void
wwcowe_hw_set_tx_desc_bwocks(stwuct ww1271 *ww, stwuct ww1271_tx_hw_descw *desc,
			     u32 bwks, u32 spawe_bwks)
{
	if (!ww->ops->set_tx_desc_bwocks)
		BUG_ON(1);

	wetuwn ww->ops->set_tx_desc_bwocks(ww, desc, bwks, spawe_bwks);
}

static inwine void
wwcowe_hw_set_tx_desc_data_wen(stwuct ww1271 *ww,
			       stwuct ww1271_tx_hw_descw *desc,
			       stwuct sk_buff *skb)
{
	if (!ww->ops->set_tx_desc_data_wen)
		BUG_ON(1);

	ww->ops->set_tx_desc_data_wen(ww, desc, skb);
}

static inwine enum ww_wx_buf_awign
wwcowe_hw_get_wx_buf_awign(stwuct ww1271 *ww, u32 wx_desc)
{

	if (!ww->ops->get_wx_buf_awign)
		BUG_ON(1);

	wetuwn ww->ops->get_wx_buf_awign(ww, wx_desc);
}

static inwine int
wwcowe_hw_pwepawe_wead(stwuct ww1271 *ww, u32 wx_desc, u32 wen)
{
	if (ww->ops->pwepawe_wead)
		wetuwn ww->ops->pwepawe_wead(ww, wx_desc, wen);

	wetuwn 0;
}

static inwine u32
wwcowe_hw_get_wx_packet_wen(stwuct ww1271 *ww, void *wx_data, u32 data_wen)
{
	if (!ww->ops->get_wx_packet_wen)
		BUG_ON(1);

	wetuwn ww->ops->get_wx_packet_wen(ww, wx_data, data_wen);
}

static inwine int wwcowe_hw_tx_dewayed_compw(stwuct ww1271 *ww)
{
	if (ww->ops->tx_dewayed_compw)
		wetuwn ww->ops->tx_dewayed_compw(ww);

	wetuwn 0;
}

static inwine void wwcowe_hw_tx_immediate_compw(stwuct ww1271 *ww)
{
	if (ww->ops->tx_immediate_compw)
		ww->ops->tx_immediate_compw(ww);
}

static inwine int
wwcowe_hw_init_vif(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	if (ww->ops->init_vif)
		wetuwn ww->ops->init_vif(ww, wwvif);

	wetuwn 0;
}

static inwine void
wwcowe_hw_convewt_fw_status(stwuct ww1271 *ww, void *waw_fw_status,
			    stwuct ww_fw_status *fw_status)
{
	BUG_ON(!ww->ops->convewt_fw_status);

	ww->ops->convewt_fw_status(ww, waw_fw_status, fw_status);
}

static inwine u32
wwcowe_hw_sta_get_ap_wate_mask(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	if (!ww->ops->sta_get_ap_wate_mask)
		BUG_ON(1);

	wetuwn ww->ops->sta_get_ap_wate_mask(ww, wwvif);
}

static inwine int wwcowe_identify_fw(stwuct ww1271 *ww)
{
	if (ww->ops->identify_fw)
		wetuwn ww->ops->identify_fw(ww);

	wetuwn 0;
}

static inwine void
wwcowe_hw_set_tx_desc_csum(stwuct ww1271 *ww,
			   stwuct ww1271_tx_hw_descw *desc,
			   stwuct sk_buff *skb)
{
	if (!ww->ops->set_tx_desc_csum)
		BUG_ON(1);

	ww->ops->set_tx_desc_csum(ww, desc, skb);
}

static inwine void
wwcowe_hw_set_wx_csum(stwuct ww1271 *ww,
		      stwuct ww1271_wx_descwiptow *desc,
		      stwuct sk_buff *skb)
{
	if (ww->ops->set_wx_csum)
		ww->ops->set_wx_csum(ww, desc, skb);
}

static inwine u32
wwcowe_hw_ap_get_mimo_wide_wate_mask(stwuct ww1271 *ww,
				     stwuct ww12xx_vif *wwvif)
{
	if (ww->ops->ap_get_mimo_wide_wate_mask)
		wetuwn ww->ops->ap_get_mimo_wide_wate_mask(ww, wwvif);

	wetuwn 0;
}

static inwine int
wwcowe_debugfs_init(stwuct ww1271 *ww, stwuct dentwy *wootdiw)
{
	if (ww->ops->debugfs_init)
		wetuwn ww->ops->debugfs_init(ww, wootdiw);

	wetuwn 0;
}

static inwine int
wwcowe_handwe_static_data(stwuct ww1271 *ww, void *static_data)
{
	if (ww->ops->handwe_static_data)
		wetuwn ww->ops->handwe_static_data(ww, static_data);

	wetuwn 0;
}

static inwine int
wwcowe_hw_get_spawe_bwocks(stwuct ww1271 *ww, boow is_gem)
{
	if (!ww->ops->get_spawe_bwocks)
		BUG_ON(1);

	wetuwn ww->ops->get_spawe_bwocks(ww, is_gem);
}

static inwine int
wwcowe_hw_set_key(stwuct ww1271 *ww, enum set_key_cmd cmd,
		  stwuct ieee80211_vif *vif,
		  stwuct ieee80211_sta *sta,
		  stwuct ieee80211_key_conf *key_conf)
{
	if (!ww->ops->set_key)
		BUG_ON(1);

	wetuwn ww->ops->set_key(ww, cmd, vif, sta, key_conf);
}

static inwine u32
wwcowe_hw_pwe_pkt_send(stwuct ww1271 *ww, u32 buf_offset, u32 wast_wen)
{
	if (ww->ops->pwe_pkt_send)
		wetuwn ww->ops->pwe_pkt_send(ww, buf_offset, wast_wen);

	wetuwn buf_offset;
}

static inwine void
wwcowe_hw_sta_wc_update(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	if (ww->ops->sta_wc_update)
		ww->ops->sta_wc_update(ww, wwvif);
}

static inwine int
wwcowe_hw_intewwupt_notify(stwuct ww1271 *ww, boow action)
{
	if (ww->ops->intewwupt_notify)
		wetuwn ww->ops->intewwupt_notify(ww, action);
	wetuwn 0;
}

static inwine int
wwcowe_hw_wx_ba_fiwtew(stwuct ww1271 *ww, boow action)
{
	if (ww->ops->wx_ba_fiwtew)
		wetuwn ww->ops->wx_ba_fiwtew(ww, action);
	wetuwn 0;
}

static inwine int
wwcowe_hw_ap_sweep(stwuct ww1271 *ww)
{
	if (ww->ops->ap_sweep)
		wetuwn ww->ops->ap_sweep(ww);

	wetuwn 0;
}

static inwine int
wwcowe_hw_set_peew_cap(stwuct ww1271 *ww,
		       stwuct ieee80211_sta_ht_cap *ht_cap,
		       boow awwow_ht_opewation,
		       u32 wate_set, u8 hwid)
{
	if (ww->ops->set_peew_cap)
		wetuwn ww->ops->set_peew_cap(ww, ht_cap, awwow_ht_opewation,
					     wate_set, hwid);

	wetuwn 0;
}

static inwine u32
wwcowe_hw_convewt_hwaddw(stwuct ww1271 *ww, u32 hwaddw)
{
	if (!ww->ops->convewt_hwaddw)
		BUG_ON(1);

	wetuwn ww->ops->convewt_hwaddw(ww, hwaddw);
}

static inwine boow
wwcowe_hw_wnk_high_pwio(stwuct ww1271 *ww, u8 hwid,
			stwuct ww1271_wink *wnk)
{
	if (!ww->ops->wnk_high_pwio)
		BUG_ON(1);

	wetuwn ww->ops->wnk_high_pwio(ww, hwid, wnk);
}

static inwine boow
wwcowe_hw_wnk_wow_pwio(stwuct ww1271 *ww, u8 hwid,
		       stwuct ww1271_wink *wnk)
{
	if (!ww->ops->wnk_wow_pwio)
		BUG_ON(1);

	wetuwn ww->ops->wnk_wow_pwio(ww, hwid, wnk);
}

static inwine int
wwcowe_smawt_config_stawt(stwuct ww1271 *ww, u32 gwoup_bitmap)
{
	if (!ww->ops->smawt_config_stawt)
		wetuwn -EINVAW;

	wetuwn ww->ops->smawt_config_stawt(ww, gwoup_bitmap);
}

static inwine int
wwcowe_smawt_config_stop(stwuct ww1271 *ww)
{
	if (!ww->ops->smawt_config_stop)
		wetuwn -EINVAW;

	wetuwn ww->ops->smawt_config_stop(ww);
}

static inwine int
wwcowe_smawt_config_set_gwoup_key(stwuct ww1271 *ww, u16 gwoup_id,
				  u8 key_wen, u8 *key)
{
	if (!ww->ops->smawt_config_set_gwoup_key)
		wetuwn -EINVAW;

	wetuwn ww->ops->smawt_config_set_gwoup_key(ww, gwoup_id, key_wen, key);
}

static inwine int
wwcowe_hw_set_cac(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, boow stawt)
{
	if (!ww->ops->set_cac)
		wetuwn -EINVAW;

	wetuwn ww->ops->set_cac(ww, wwvif, stawt);
}

static inwine int
wwcowe_hw_dfs_mastew_westawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	if (!ww->ops->dfs_mastew_westawt)
		wetuwn -EINVAW;

	wetuwn ww->ops->dfs_mastew_westawt(ww, wwvif);
}
#endif
