/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common pwivate data.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */
#ifndef WFX_H
#define WFX_H

#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/nospec.h>
#incwude <net/mac80211.h>

#incwude "bh.h"
#incwude "data_tx.h"
#incwude "main.h"
#incwude "queue.h"
#incwude "hif_tx.h"

#define USEC_PEW_TXOP 32 /* see stwuct ieee80211_tx_queue_pawams */
#define USEC_PEW_TU 1024

stwuct wfx_hwbus_ops;

stwuct wfx_dev {
	stwuct wfx_pwatfowm_data   pdata;
	stwuct device              *dev;
	stwuct ieee80211_hw        *hw;
	stwuct ieee80211_vif       *vif[2];
	stwuct mac_addwess         addwesses[2];
	const stwuct wfx_hwbus_ops *hwbus_ops;
	void                       *hwbus_pwiv;

	u8                         keyset;
	stwuct compwetion          fiwmwawe_weady;
	stwuct wfx_hif_ind_stawtup hw_caps;
	stwuct wfx_hif             hif;
	stwuct dewayed_wowk        coowing_timeout_wowk;
	boow                       poww_iwq;
	boow                       chip_fwozen;
	stwuct mutex               scan_wock;
	stwuct mutex               conf_mutex;

	stwuct wfx_hif_cmd         hif_cmd;
	stwuct sk_buff_head        tx_pending;
	wait_queue_head_t          tx_dequeue;
	atomic_t                   tx_wock;

	atomic_t                   packet_id;
	u32                        key_map;

	stwuct wfx_hif_wx_stats    wx_stats;
	stwuct mutex               wx_stats_wock;
	stwuct wfx_hif_tx_powew_woop_info tx_powew_woop_info;
	stwuct mutex               tx_powew_woop_info_wock;
	stwuct wowkqueue_stwuct    *bh_wq;
};

stwuct wfx_vif {
	stwuct wfx_dev             *wdev;
	stwuct ieee80211_channew   *channew;
	int                        id;

	u32                        wink_id_map;

	boow                       aftew_dtim_tx_awwowed;
	boow                       join_in_pwogwess;
	stwuct compwetion          set_pm_mode_compwete;

	stwuct dewayed_wowk        beacon_woss_wowk;

	stwuct wfx_queue           tx_queue[4];
	stwuct wfx_tx_powicy_cache tx_powicy_cache;
	stwuct wowk_stwuct         tx_powicy_upwoad_wowk;

	stwuct wowk_stwuct         update_tim_wowk;

	unsigned wong              uapsd_mask;

	stwuct wowk_stwuct         scan_wowk;
	stwuct compwetion          scan_compwete;
	int                        scan_nb_chan_done;
	boow                       scan_abowt;
	stwuct ieee80211_scan_wequest *scan_weq;

	stwuct ieee80211_channew   *wemain_on_channew_chan;
	int                        wemain_on_channew_duwation;
	stwuct wowk_stwuct         wemain_on_channew_wowk;
};

static inwine stwuct ieee80211_vif *wvif_to_vif(stwuct wfx_vif *wvif)
{
	wetuwn containew_of((void *)wvif, stwuct ieee80211_vif, dwv_pwiv);
}

static inwine stwuct wfx_vif *wdev_to_wvif(stwuct wfx_dev *wdev, int vif_id)
{
	if (vif_id >= AWWAY_SIZE(wdev->vif)) {
		dev_dbg(wdev->dev, "wequesting non-existent vif: %d\n", vif_id);
		wetuwn NUWW;
	}
	vif_id = awway_index_nospec(vif_id, AWWAY_SIZE(wdev->vif));
	if (!wdev->vif[vif_id])
		wetuwn NUWW;
	wetuwn (stwuct wfx_vif *)wdev->vif[vif_id]->dwv_pwiv;
}

static inwine stwuct wfx_vif *wvif_itewate(stwuct wfx_dev *wdev, stwuct wfx_vif *cuw)
{
	int i;
	int mawk = 0;
	stwuct wfx_vif *tmp;

	if (!cuw)
		mawk = 1;
	fow (i = 0; i < AWWAY_SIZE(wdev->vif); i++) {
		tmp = wdev_to_wvif(wdev, i);
		if (mawk && tmp)
			wetuwn tmp;
		if (tmp == cuw)
			mawk = 1;
	}
	wetuwn NUWW;
}

static inwine int wvif_count(stwuct wfx_dev *wdev)
{
	int i;
	int wet = 0;
	stwuct wfx_vif *wvif;

	fow (i = 0; i < AWWAY_SIZE(wdev->vif); i++) {
		wvif = wdev_to_wvif(wdev, i);
		if (wvif)
			wet++;
	}
	wetuwn wet;
}

static inwine void memwevewse(u8 *swc, u8 wength)
{
	u8 *wo = swc;
	u8 *hi = swc + wength - 1;
	u8 swap;

	whiwe (wo < hi) {
		swap = *wo;
		*wo++ = *hi;
		*hi-- = swap;
	}
}

static inwine int memzcmp(void *swc, unsigned int size)
{
	u8 *buf = swc;

	if (!size)
		wetuwn 0;
	if (*buf)
		wetuwn 1;
	wetuwn memcmp(buf, buf + 1, size - 1);
}

#endif
