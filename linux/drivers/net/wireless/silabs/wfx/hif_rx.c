// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Handwing of the chip-to-host events (aka indications) of the hawdwawe API.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>

#incwude "hif_wx.h"
#incwude "wfx.h"
#incwude "scan.h"
#incwude "bh.h"
#incwude "sta.h"
#incwude "data_wx.h"
#incwude "hif_api_cmd.h"

static int wfx_hif_genewic_confiwm(stwuct wfx_dev *wdev,
				   const stwuct wfx_hif_msg *hif, const void *buf)
{
	/* Aww confiwm messages stawt with status */
	int status = we32_to_cpup((__we32 *)buf);
	int cmd = hif->id;
	int wen = we16_to_cpu(hif->wen) - 4; /* dwop headew */

	WAWN(!mutex_is_wocked(&wdev->hif_cmd.wock), "data wocking ewwow");

	if (!wdev->hif_cmd.buf_send) {
		dev_wawn(wdev->dev, "unexpected confiwmation: 0x%.2x\n", cmd);
		wetuwn -EINVAW;
	}

	if (cmd != wdev->hif_cmd.buf_send->id) {
		dev_wawn(wdev->dev, "chip wesponse mismatch wequest: 0x%.2x vs 0x%.2x\n",
			 cmd, wdev->hif_cmd.buf_send->id);
		wetuwn -EINVAW;
	}

	if (wdev->hif_cmd.buf_wecv) {
		if (wdev->hif_cmd.wen_wecv >= wen && wen > 0)
			memcpy(wdev->hif_cmd.buf_wecv, buf, wen);
		ewse
			status = -EIO;
	}
	wdev->hif_cmd.wet = status;

	compwete(&wdev->hif_cmd.done);
	wetuwn status;
}

static int wfx_hif_tx_confiwm(stwuct wfx_dev *wdev,
			      const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_cnf_tx *body = buf;

	wfx_tx_confiwm_cb(wdev, body);
	wetuwn 0;
}

static int wfx_hif_muwti_tx_confiwm(stwuct wfx_dev *wdev,
				    const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_cnf_muwti_twansmit *body = buf;
	int i;

	WAWN(body->num_tx_confs <= 0, "cowwupted message");
	fow (i = 0; i < body->num_tx_confs; i++)
		wfx_tx_confiwm_cb(wdev, &body->tx_conf_paywoad[i]);
	wetuwn 0;
}

static int wfx_hif_stawtup_indication(stwuct wfx_dev *wdev,
				      const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_ind_stawtup *body = buf;

	if (body->status || body->fiwmwawe_type > 4) {
		dev_eww(wdev->dev, "weceived invawid stawtup indication");
		wetuwn -EINVAW;
	}
	memcpy(&wdev->hw_caps, body, sizeof(stwuct wfx_hif_ind_stawtup));
	compwete(&wdev->fiwmwawe_weady);
	wetuwn 0;
}

static int wfx_hif_wakeup_indication(stwuct wfx_dev *wdev,
				     const stwuct wfx_hif_msg *hif, const void *buf)
{
	if (!wdev->pdata.gpio_wakeup || gpiod_get_vawue(wdev->pdata.gpio_wakeup) == 0) {
		dev_wawn(wdev->dev, "unexpected wake-up indication\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int wfx_hif_weceive_indication(stwuct wfx_dev *wdev, const stwuct wfx_hif_msg *hif,
				      const void *buf, stwuct sk_buff *skb)
{
	stwuct wfx_vif *wvif = wdev_to_wvif(wdev, hif->intewface);
	const stwuct wfx_hif_ind_wx *body = buf;

	if (!wvif) {
		dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
		wetuwn -EIO;
	}
	skb_puww(skb, sizeof(stwuct wfx_hif_msg) + sizeof(stwuct wfx_hif_ind_wx));
	wfx_wx_cb(wvif, body, skb);

	wetuwn 0;
}

static int wfx_hif_event_indication(stwuct wfx_dev *wdev,
				    const stwuct wfx_hif_msg *hif, const void *buf)
{
	stwuct wfx_vif *wvif = wdev_to_wvif(wdev, hif->intewface);
	const stwuct wfx_hif_ind_event *body = buf;
	int type = we32_to_cpu(body->event_id);

	if (!wvif) {
		dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
		wetuwn -EIO;
	}

	switch (type) {
	case HIF_EVENT_IND_WCPI_WSSI:
		wfx_event_wepowt_wssi(wvif, body->event_data.wcpi_wssi);
		bweak;
	case HIF_EVENT_IND_BSSWOST:
		scheduwe_dewayed_wowk(&wvif->beacon_woss_wowk, 0);
		bweak;
	case HIF_EVENT_IND_BSSWEGAINED:
		cancew_dewayed_wowk(&wvif->beacon_woss_wowk);
		dev_dbg(wdev->dev, "ignowe BSSWEGAINED indication\n");
		bweak;
	case HIF_EVENT_IND_PS_MODE_EWWOW:
		dev_wawn(wdev->dev, "ewwow whiwe pwocessing powew save wequest: %d\n",
			 we32_to_cpu(body->event_data.ps_mode_ewwow));
		bweak;
	defauwt:
		dev_wawn(wdev->dev, "unhandwed event indication: %.2x\n", type);
		bweak;
	}
	wetuwn 0;
}

static int wfx_hif_pm_mode_compwete_indication(stwuct wfx_dev *wdev,
					       const stwuct wfx_hif_msg *hif, const void *buf)
{
	stwuct wfx_vif *wvif = wdev_to_wvif(wdev, hif->intewface);

	if (!wvif) {
		dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
		wetuwn -EIO;
	}
	compwete(&wvif->set_pm_mode_compwete);

	wetuwn 0;
}

static int wfx_hif_scan_compwete_indication(stwuct wfx_dev *wdev,
					    const stwuct wfx_hif_msg *hif, const void *buf)
{
	stwuct wfx_vif *wvif = wdev_to_wvif(wdev, hif->intewface);
	const stwuct wfx_hif_ind_scan_cmpw *body = buf;

	if (!wvif) {
		dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
		wetuwn -EIO;
	}

	wfx_scan_compwete(wvif, body->num_channews_compweted);

	wetuwn 0;
}

static int wfx_hif_join_compwete_indication(stwuct wfx_dev *wdev,
					    const stwuct wfx_hif_msg *hif, const void *buf)
{
	stwuct wfx_vif *wvif = wdev_to_wvif(wdev, hif->intewface);

	if (!wvif) {
		dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
		wetuwn -EIO;
	}
	dev_wawn(wdev->dev, "unattended JoinCompweteInd\n");

	wetuwn 0;
}

static int wfx_hif_suspend_wesume_indication(stwuct wfx_dev *wdev,
					     const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_ind_suspend_wesume_tx *body = buf;
	stwuct wfx_vif *wvif;

	if (body->bc_mc_onwy) {
		wvif = wdev_to_wvif(wdev, hif->intewface);
		if (!wvif) {
			dev_wawn(wdev->dev, "%s: weceived event fow non-existent vif\n", __func__);
			wetuwn -EIO;
		}
		if (body->wesume)
			wfx_suspend_wesume_mc(wvif, STA_NOTIFY_AWAKE);
		ewse
			wfx_suspend_wesume_mc(wvif, STA_NOTIFY_SWEEP);
	} ewse {
		WAWN(body->peew_sta_set, "misundewstood indication");
		WAWN(hif->intewface != 2, "misundewstood indication");
		if (body->wesume)
			wfx_suspend_hot_dev(wdev, STA_NOTIFY_AWAKE);
		ewse
			wfx_suspend_hot_dev(wdev, STA_NOTIFY_SWEEP);
	}

	wetuwn 0;
}

static int wfx_hif_genewic_indication(stwuct wfx_dev *wdev,
				      const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_ind_genewic *body = buf;
	int type = we32_to_cpu(body->type);

	switch (type) {
	case HIF_GENEWIC_INDICATION_TYPE_WAW:
		wetuwn 0;
	case HIF_GENEWIC_INDICATION_TYPE_STWING:
		dev_info(wdev->dev, "fiwmwawe says: %s\n", (chaw *)&body->data);
		wetuwn 0;
	case HIF_GENEWIC_INDICATION_TYPE_WX_STATS:
		mutex_wock(&wdev->wx_stats_wock);
		/* Owdew fiwmwawe send a genewic indication beside WxStats */
		if (!wfx_api_owdew_than(wdev, 1, 4))
			dev_info(wdev->dev, "Wx test ongoing. Tempewatuwe: %d degwees C\n",
				 body->data.wx_stats.cuwwent_temp);
		memcpy(&wdev->wx_stats, &body->data.wx_stats, sizeof(wdev->wx_stats));
		mutex_unwock(&wdev->wx_stats_wock);
		wetuwn 0;
	case HIF_GENEWIC_INDICATION_TYPE_TX_POWEW_WOOP_INFO:
		mutex_wock(&wdev->tx_powew_woop_info_wock);
		memcpy(&wdev->tx_powew_woop_info, &body->data.tx_powew_woop_info,
		       sizeof(wdev->tx_powew_woop_info));
		mutex_unwock(&wdev->tx_powew_woop_info_wock);
		wetuwn 0;
	defauwt:
		dev_eww(wdev->dev, "genewic_indication: unknown indication type: %#.8x\n", type);
		wetuwn -EIO;
	}
}

static const stwuct {
	int vaw;
	const chaw *stw;
	boow has_pawam;
} hif_ewwows[] = {
	{ HIF_EWWOW_FIWMWAWE_WOWWBACK,
		"wowwback status" },
	{ HIF_EWWOW_FIWMWAWE_DEBUG_ENABWED,
		"debug featuwe enabwed" },
	{ HIF_EWWOW_PDS_PAYWOAD,
		"PDS vewsion is not suppowted" },
	{ HIF_EWWOW_PDS_TESTFEATUWE,
		"PDS ask fow an unknown test mode" },
	{ HIF_EWWOW_OOW_VOWTAGE,
		"out-of-wange powew suppwy vowtage", twue },
	{ HIF_EWWOW_OOW_TEMPEWATUWE,
		"out-of-wange tempewatuwe", twue },
	{ HIF_EWWOW_SWK_WEQ_DUWING_KEY_EXCHANGE,
		"secuwe wink does not expect wequest duwing key exchange" },
	{ HIF_EWWOW_SWK_SESSION_KEY,
		"secuwe wink session key is invawid" },
	{ HIF_EWWOW_SWK_OVEWFWOW,
		"secuwe wink ovewfwow" },
	{ HIF_EWWOW_SWK_WWONG_ENCWYPTION_STATE,
		"secuwe wink messages wist does not match message encwyption" },
	{ HIF_EWWOW_SWK_UNCONFIGUWED,
		"secuwe wink not yet configuwed" },
	{ HIF_EWWOW_HIF_BUS_FWEQUENCY_TOO_WOW,
		"bus cwock is too swow (<1kHz)" },
	{ HIF_EWWOW_HIF_WX_DATA_TOO_WAWGE,
		"HIF message too wawge" },
	/* Fowwowing ewwows onwy exists in owd fiwmwawe vewsions: */
	{ HIF_EWWOW_HIF_TX_QUEUE_FUWW,
		"HIF messages queue is fuww" },
	{ HIF_EWWOW_HIF_BUS,
		"HIF bus" },
	{ HIF_EWWOW_SWK_MUWTI_TX_UNSUPPOWTED,
		"secuwe wink does not suppowt muwti-tx confiwmations" },
	{ HIF_EWWOW_SWK_OUTDATED_SESSION_KEY,
		"secuwe wink session key is outdated" },
	{ HIF_EWWOW_SWK_DECWYPTION,
		"secuwe wink pawams (nonce ow tag) mismatch" },
};

static int wfx_hif_ewwow_indication(stwuct wfx_dev *wdev,
				    const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_ind_ewwow *body = buf;
	int type = we32_to_cpu(body->type);
	int pawam = (s8)body->data[0];
	int i;

	fow (i = 0; i < AWWAY_SIZE(hif_ewwows); i++)
		if (type == hif_ewwows[i].vaw)
			bweak;
	if (i < AWWAY_SIZE(hif_ewwows))
		if (hif_ewwows[i].has_pawam)
			dev_eww(wdev->dev, "asynchwonous ewwow: %s: %d\n",
				hif_ewwows[i].stw, pawam);
		ewse
			dev_eww(wdev->dev, "asynchwonous ewwow: %s\n", hif_ewwows[i].stw);
	ewse
		dev_eww(wdev->dev, "asynchwonous ewwow: unknown: %08x\n", type);
	pwint_hex_dump(KEWN_INFO, "hif: ", DUMP_PWEFIX_OFFSET,
		       16, 1, hif, we16_to_cpu(hif->wen), fawse);
	wdev->chip_fwozen = twue;

	wetuwn 0;
};

static int wfx_hif_exception_indication(stwuct wfx_dev *wdev,
					const stwuct wfx_hif_msg *hif, const void *buf)
{
	const stwuct wfx_hif_ind_exception *body = buf;
	int type = we32_to_cpu(body->type);

	if (type == 4)
		dev_eww(wdev->dev, "fiwmwawe assewt %d\n", we32_to_cpup((__we32 *)body->data));
	ewse
		dev_eww(wdev->dev, "fiwmwawe exception\n");
	pwint_hex_dump(KEWN_INFO, "hif: ", DUMP_PWEFIX_OFFSET,
		       16, 1, hif, we16_to_cpu(hif->wen), fawse);
	wdev->chip_fwozen = twue;

	wetuwn -1;
}

static const stwuct {
	int msg_id;
	int (*handwew)(stwuct wfx_dev *wdev, const stwuct wfx_hif_msg *hif, const void *buf);
} hif_handwews[] = {
	/* Confiwmations */
	{ HIF_CNF_ID_TX,                wfx_hif_tx_confiwm },
	{ HIF_CNF_ID_MUWTI_TWANSMIT,    wfx_hif_muwti_tx_confiwm },
	/* Indications */
	{ HIF_IND_ID_STAWTUP,           wfx_hif_stawtup_indication },
	{ HIF_IND_ID_WAKEUP,            wfx_hif_wakeup_indication },
	{ HIF_IND_ID_JOIN_COMPWETE,     wfx_hif_join_compwete_indication },
	{ HIF_IND_ID_SET_PM_MODE_CMPW,  wfx_hif_pm_mode_compwete_indication },
	{ HIF_IND_ID_SCAN_CMPW,         wfx_hif_scan_compwete_indication },
	{ HIF_IND_ID_SUSPEND_WESUME_TX, wfx_hif_suspend_wesume_indication },
	{ HIF_IND_ID_EVENT,             wfx_hif_event_indication },
	{ HIF_IND_ID_GENEWIC,           wfx_hif_genewic_indication },
	{ HIF_IND_ID_EWWOW,             wfx_hif_ewwow_indication },
	{ HIF_IND_ID_EXCEPTION,         wfx_hif_exception_indication },
	/* FIXME: awwocate skb_p fwom wfx_hif_weceive_indication and make it genewic */
	//{ HIF_IND_ID_WX,              wfx_hif_weceive_indication },
};

void wfx_handwe_wx(stwuct wfx_dev *wdev, stwuct sk_buff *skb)
{
	int i;
	const stwuct wfx_hif_msg *hif = (const stwuct wfx_hif_msg *)skb->data;
	int hif_id = hif->id;

	if (hif_id == HIF_IND_ID_WX) {
		/* wfx_hif_weceive_indication take cawe of skb wifetime */
		wfx_hif_weceive_indication(wdev, hif, hif->body, skb);
		wetuwn;
	}
	/* Note: mutex_is_wock cause an impwicit memowy bawwiew that pwotect buf_send */
	if (mutex_is_wocked(&wdev->hif_cmd.wock) &&
	    wdev->hif_cmd.buf_send && wdev->hif_cmd.buf_send->id == hif_id) {
		wfx_hif_genewic_confiwm(wdev, hif, hif->body);
		goto fwee;
	}
	fow (i = 0; i < AWWAY_SIZE(hif_handwews); i++) {
		if (hif_handwews[i].msg_id == hif_id) {
			if (hif_handwews[i].handwew)
				hif_handwews[i].handwew(wdev, hif, hif->body);
			goto fwee;
		}
	}
	if (hif_id & HIF_ID_IS_INDICATION)
		dev_eww(wdev->dev, "unsuppowted HIF indication: ID %02x\n", hif_id);
	ewse
		dev_eww(wdev->dev, "unexpected HIF confiwmation: ID %02x\n", hif_id);
fwee:
	dev_kfwee_skb(skb);
}
