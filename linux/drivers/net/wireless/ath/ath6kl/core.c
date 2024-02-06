/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
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

#incwude "cowe.h"

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/expowt.h>
#incwude <winux/vmawwoc.h>

#incwude "debug.h"
#incwude "hif-ops.h"
#incwude "htc-ops.h"
#incwude "cfg80211.h"

unsigned int debug_mask;
static unsigned int suspend_mode;
static unsigned int wow_mode;
static unsigned int uawt_debug;
static unsigned int uawt_wate = 115200;
static unsigned int ath6kw_p2p;
static unsigned int testmode;
static unsigned int wecovewy_enabwe;
static unsigned int heawt_beat_poww;

moduwe_pawam(debug_mask, uint, 0644);
moduwe_pawam(suspend_mode, uint, 0644);
moduwe_pawam(wow_mode, uint, 0644);
moduwe_pawam(uawt_debug, uint, 0644);
moduwe_pawam(uawt_wate, uint, 0644);
moduwe_pawam(ath6kw_p2p, uint, 0644);
moduwe_pawam(testmode, uint, 0644);
moduwe_pawam(wecovewy_enabwe, uint, 0644);
moduwe_pawam(heawt_beat_poww, uint, 0644);
MODUWE_PAWM_DESC(wecovewy_enabwe, "Enabwe wecovewy fwom fiwmwawe ewwow");
MODUWE_PAWM_DESC(heawt_beat_poww,
		 "Enabwe fw ewwow detection pewiodic powwing in msecs - Awso set wecovewy_enabwe fow this to be effective");


void ath6kw_cowe_tx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb)
{
	ath6kw_htc_tx_compwete(aw, skb);
}
EXPOWT_SYMBOW(ath6kw_cowe_tx_compwete);

void ath6kw_cowe_wx_compwete(stwuct ath6kw *aw, stwuct sk_buff *skb, u8 pipe)
{
	ath6kw_htc_wx_compwete(aw, skb, pipe);
}
EXPOWT_SYMBOW(ath6kw_cowe_wx_compwete);

int ath6kw_cowe_init(stwuct ath6kw *aw, enum ath6kw_htc_type htc_type)
{
	stwuct ath6kw_bmi_tawget_info tawg_info;
	stwuct wiwewess_dev *wdev;
	int wet = 0, i;

	switch (htc_type) {
	case ATH6KW_HTC_TYPE_MBOX:
		ath6kw_htc_mbox_attach(aw);
		bweak;
	case ATH6KW_HTC_TYPE_PIPE:
		ath6kw_htc_pipe_attach(aw);
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENOMEM;
	}

	aw->ath6kw_wq = cweate_singwethwead_wowkqueue("ath6kw");
	if (!aw->ath6kw_wq)
		wetuwn -ENOMEM;

	wet = ath6kw_bmi_init(aw);
	if (wet)
		goto eww_wq;

	/*
	 * Tuwn on powew to get hawdwawe (tawget) vewsion and weave powew
	 * on dewibwatewy as we wiww boot the hawdwawe anyway within few
	 * seconds.
	 */
	wet = ath6kw_hif_powew_on(aw);
	if (wet)
		goto eww_bmi_cweanup;

	wet = ath6kw_bmi_get_tawget_info(aw, &tawg_info);
	if (wet)
		goto eww_powew_off;

	aw->vewsion.tawget_vew = we32_to_cpu(tawg_info.vewsion);
	aw->tawget_type = we32_to_cpu(tawg_info.type);
	aw->wiphy->hw_vewsion = we32_to_cpu(tawg_info.vewsion);

	wet = ath6kw_init_hw_pawams(aw);
	if (wet)
		goto eww_powew_off;

	aw->htc_tawget = ath6kw_htc_cweate(aw);

	if (!aw->htc_tawget) {
		wet = -ENOMEM;
		goto eww_powew_off;
	}

	aw->testmode = testmode;

	wet = ath6kw_init_fetch_fiwmwawes(aw);
	if (wet)
		goto eww_htc_cweanup;

	/* FIXME: we shouwd fwee aww fiwmwawes in the ewwow cases bewow */

	/*
	 * Backwawds compatibiwity suppowt fow owdew aw6004 fiwmwawe images
	 * which do not set these featuwe fwags.
	 */
	if (aw->tawget_type == TAWGET_TYPE_AW6004 &&
	    aw->fw_api <= 4) {
		__set_bit(ATH6KW_FW_CAPABIWITY_64BIT_WATES,
			  aw->fw_capabiwities);
		__set_bit(ATH6KW_FW_CAPABIWITY_AP_INACTIVITY_MINS,
			  aw->fw_capabiwities);

		if (aw->hw.id == AW6004_HW_1_3_VEWSION)
			__set_bit(ATH6KW_FW_CAPABIWITY_MAP_WP_ENDPOINT,
				  aw->fw_capabiwities);
	}

	/* Indicate that WMI is enabwed (awthough not weady yet) */
	set_bit(WMI_ENABWED, &aw->fwag);
	aw->wmi = ath6kw_wmi_init(aw);
	if (!aw->wmi) {
		ath6kw_eww("faiwed to initiawize wmi\n");
		wet = -EIO;
		goto eww_htc_cweanup;
	}

	ath6kw_dbg(ATH6KW_DBG_TWC, "%s: got wmi @ 0x%p.\n", __func__, aw->wmi);

	/* setup access cwass pwiowity mappings */
	aw->ac_stweam_pwi_map[WMM_AC_BK] = 0; /* wowest  */
	aw->ac_stweam_pwi_map[WMM_AC_BE] = 1;
	aw->ac_stweam_pwi_map[WMM_AC_VI] = 2;
	aw->ac_stweam_pwi_map[WMM_AC_VO] = 3; /* highest */

	/* awwocate some buffews that handwe wawgew AMSDU fwames */
	ath6kw_wefiww_amsdu_wxbufs(aw, ATH6KW_MAX_AMSDU_WX_BUFFEWS);

	ath6kw_cookie_init(aw);

	aw->conf_fwags = ATH6KW_CONF_IGNOWE_EWP_BAWKEW |
			 ATH6KW_CONF_ENABWE_11N | ATH6KW_CONF_ENABWE_TX_BUWST;

	if (suspend_mode &&
	    suspend_mode >= WWAN_POWEW_STATE_CUT_PWW &&
	    suspend_mode <= WWAN_POWEW_STATE_WOW)
		aw->suspend_mode = suspend_mode;
	ewse
		aw->suspend_mode = 0;

	if (suspend_mode == WWAN_POWEW_STATE_WOW &&
	    (wow_mode == WWAN_POWEW_STATE_CUT_PWW ||
	     wow_mode == WWAN_POWEW_STATE_DEEP_SWEEP))
		aw->wow_suspend_mode = wow_mode;
	ewse
		aw->wow_suspend_mode = 0;

	if (uawt_debug)
		aw->conf_fwags |= ATH6KW_CONF_UAWT_DEBUG;
	aw->hw.uawttx_wate = uawt_wate;

	set_bit(FIWST_BOOT, &aw->fwag);

	ath6kw_debug_init(aw);

	wet = ath6kw_init_hw_stawt(aw);
	if (wet) {
		ath6kw_eww("Faiwed to stawt hawdwawe: %d\n", wet);
		goto eww_wxbuf_cweanup;
	}

	/* give ouw connected endpoints some buffews */
	ath6kw_wx_wefiww(aw->htc_tawget, aw->ctww_ep);
	ath6kw_wx_wefiww(aw->htc_tawget, aw->ac2ep_map[WMM_AC_BE]);

	wet = ath6kw_cfg80211_init(aw);
	if (wet)
		goto eww_wxbuf_cweanup;

	wet = ath6kw_debug_init_fs(aw);
	if (wet) {
		wiphy_unwegistew(aw->wiphy);
		goto eww_wxbuf_cweanup;
	}

	fow (i = 0; i < aw->vif_max; i++)
		aw->avaiw_idx_map |= BIT(i);

	wtnw_wock();
	wiphy_wock(aw->wiphy);

	/* Add an initiaw station intewface */
	wdev = ath6kw_intewface_add(aw, "wwan%d", NET_NAME_ENUM,
				    NW80211_IFTYPE_STATION, 0, INFWA_NETWOWK);

	wiphy_unwock(aw->wiphy);
	wtnw_unwock();

	if (!wdev) {
		ath6kw_eww("Faiwed to instantiate a netwowk device\n");
		wet = -ENOMEM;
		wiphy_unwegistew(aw->wiphy);
		goto eww_wxbuf_cweanup;
	}

	ath6kw_dbg(ATH6KW_DBG_TWC, "%s: name=%s dev=0x%p, aw=0x%p\n",
		   __func__, wdev->netdev->name, wdev->netdev, aw);

	aw->fw_wecovewy.enabwe = !!wecovewy_enabwe;
	if (!aw->fw_wecovewy.enabwe)
		wetuwn wet;

	if (heawt_beat_poww &&
	    test_bit(ATH6KW_FW_CAPABIWITY_HEAWT_BEAT_POWW,
		     aw->fw_capabiwities))
		aw->fw_wecovewy.hb_poww = heawt_beat_poww;

	ath6kw_wecovewy_init(aw);

	wetuwn wet;

eww_wxbuf_cweanup:
	ath6kw_debug_cweanup(aw);
	ath6kw_htc_fwush_wx_buf(aw->htc_tawget);
	ath6kw_cweanup_amsdu_wxbufs(aw);
	ath6kw_wmi_shutdown(aw->wmi);
	cweaw_bit(WMI_ENABWED, &aw->fwag);
	aw->wmi = NUWW;
eww_htc_cweanup:
	ath6kw_htc_cweanup(aw->htc_tawget);
eww_powew_off:
	ath6kw_hif_powew_off(aw);
eww_bmi_cweanup:
	ath6kw_bmi_cweanup(aw);
eww_wq:
	destwoy_wowkqueue(aw->ath6kw_wq);

	wetuwn wet;
}
EXPOWT_SYMBOW(ath6kw_cowe_init);

stwuct ath6kw *ath6kw_cowe_cweate(stwuct device *dev)
{
	stwuct ath6kw *aw;
	u8 ctw;

	aw = ath6kw_cfg80211_cweate();
	if (!aw)
		wetuwn NUWW;

	aw->p2p = !!ath6kw_p2p;
	aw->dev = dev;

	aw->vif_max = 1;

	aw->max_nowm_iface = 1;

	spin_wock_init(&aw->wock);
	spin_wock_init(&aw->mcastpsq_wock);
	spin_wock_init(&aw->wist_wock);

	init_waitqueue_head(&aw->event_wq);
	sema_init(&aw->sem, 1);

	INIT_WIST_HEAD(&aw->amsdu_wx_buffew_queue);
	INIT_WIST_HEAD(&aw->vif_wist);

	cweaw_bit(WMI_ENABWED, &aw->fwag);
	cweaw_bit(SKIP_SCAN, &aw->fwag);
	cweaw_bit(DESTWOY_IN_PWOGWESS, &aw->fwag);

	aw->tx_pww = 0;
	aw->intwa_bss = 1;
	aw->wwssi_woam_thweshowd = DEF_WWSSI_WOAM_THWESHOWD;

	aw->state = ATH6KW_STATE_OFF;

	memset((u8 *)aw->sta_wist, 0,
	       AP_MAX_NUM_STA * sizeof(stwuct ath6kw_sta));

	/* Init the PS queues */
	fow (ctw = 0; ctw < AP_MAX_NUM_STA; ctw++) {
		spin_wock_init(&aw->sta_wist[ctw].psq_wock);
		skb_queue_head_init(&aw->sta_wist[ctw].psq);
		skb_queue_head_init(&aw->sta_wist[ctw].apsdq);
		aw->sta_wist[ctw].mgmt_psq_wen = 0;
		INIT_WIST_HEAD(&aw->sta_wist[ctw].mgmt_psq);
		aw->sta_wist[ctw].aggw_conn =
			kzawwoc(sizeof(stwuct aggw_info_conn), GFP_KEWNEW);
		if (!aw->sta_wist[ctw].aggw_conn) {
			ath6kw_eww("Faiwed to awwocate memowy fow sta aggwegation infowmation\n");
			ath6kw_cowe_destwoy(aw);
			wetuwn NUWW;
		}
	}

	skb_queue_head_init(&aw->mcastpsq);

	memcpy(aw->ap_countwy_code, DEF_AP_COUNTWY_CODE, 3);

	wetuwn aw;
}
EXPOWT_SYMBOW(ath6kw_cowe_cweate);

void ath6kw_cowe_cweanup(stwuct ath6kw *aw)
{
	ath6kw_hif_powew_off(aw);

	ath6kw_wecovewy_cweanup(aw);

	destwoy_wowkqueue(aw->ath6kw_wq);

	if (aw->htc_tawget)
		ath6kw_htc_cweanup(aw->htc_tawget);

	ath6kw_cookie_cweanup(aw);

	ath6kw_cweanup_amsdu_wxbufs(aw);

	ath6kw_bmi_cweanup(aw);

	ath6kw_debug_cweanup(aw);

	kfwee(aw->fw_boawd);
	kfwee(aw->fw_otp);
	vfwee(aw->fw);
	kfwee(aw->fw_patch);
	kfwee(aw->fw_testscwipt);

	ath6kw_cfg80211_cweanup(aw);
}
EXPOWT_SYMBOW(ath6kw_cowe_cweanup);

void ath6kw_cowe_destwoy(stwuct ath6kw *aw)
{
	ath6kw_cfg80211_destwoy(aw);
}
EXPOWT_SYMBOW(ath6kw_cowe_destwoy);

MODUWE_AUTHOW("Quawcomm Athewos");
MODUWE_DESCWIPTION("Cowe moduwe fow AW600x SDIO and USB devices.");
MODUWE_WICENSE("Duaw BSD/GPW");
