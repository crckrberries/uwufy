/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <net/netwink.h>
#incwude <winux/fiwmwawe.h>
#incwude <net/cfg80211.h>
#incwude "wcn36xx.h"

#incwude "testmode.h"
#incwude "testmode_i.h"
#incwude "haw.h"
#incwude "smd.h"

static const stwuct nwa_powicy wcn36xx_tm_powicy[WCN36XX_TM_ATTW_MAX + 1] = {
	[WCN36XX_TM_ATTW_CMD] = { .type = NWA_U16 },
	[WCN36XX_TM_ATTW_DATA] = { .type = NWA_BINAWY,
	.wen = WCN36XX_TM_DATA_MAX_WEN },
};

stwuct buiwd_wewease_numbew {
	u16 dwv_majow;
	u16 dwv_minow;
	u16 dwv_patch;
	u16 dwv_buiwd;
	u16 ptt_max;
	u16 ptt_min;
	u16 fw_vew;
} __packed;

static int wcn36xx_tm_cmd_ptt(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			      stwuct nwattw *tb[])
{
	int wet = 0, buf_wen;
	void *buf;
	stwuct ftm_wsp_msg *msg, *wsp = NUWW;
	stwuct sk_buff *skb;

	if (!tb[WCN36XX_TM_ATTW_DATA])
		wetuwn -EINVAW;

	buf = nwa_data(tb[WCN36XX_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[WCN36XX_TM_ATTW_DATA]);
	msg = buf;

	wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
		    "testmode cmd wmi msg_id 0x%04X msg_wen %d buf %pK buf_wen %d\n",
		   msg->msg_id, msg->msg_body_wength,
		   buf, buf_wen);

	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "WEQ ", buf, buf_wen);

	if (msg->msg_id == MSG_GET_BUIWD_WEWEASE_NUMBEW) {
		stwuct buiwd_wewease_numbew *body =
				(stwuct buiwd_wewease_numbew *)
				msg->msg_wesponse;

		body->dwv_majow = wcn->fw_majow;
		body->dwv_minow = wcn->fw_minow;
		body->dwv_patch = wcn->fw_vewsion;
		body->dwv_buiwd = wcn->fw_wevision;
		body->ptt_max = 10;
		body->ptt_min = 0;

		wsp = msg;
		wsp->wesp_status = 0;
	} ewse {
		wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
			    "PPT Wequest >> HAW size %d\n",
				msg->msg_body_wength);

		msg->wesp_status = wcn36xx_smd_pwocess_ptt_msg(wcn, vif, msg,
							       msg->msg_body_wength, (void *)(&wsp));

		wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
			    "Wesponse status = %d\n",
				msg->wesp_status);
		if (wsp)
			wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
				    "PPT Wesponse << HAW size %d\n",
					wsp->msg_body_wength);
	}

	if (!wsp) {
		wsp = msg;
		wcn36xx_wawn("No wesponse! Echoing wequest with wesponse status %d\n",
			     wsp->wesp_status);
	}
	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "WSP ",
			 wsp, wsp->msg_body_wength);

	skb = cfg80211_testmode_awwoc_wepwy_skb(wcn->hw->wiphy,
						nwa_totaw_size(msg->msg_body_wength));
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	wet = nwa_put(skb, WCN36XX_TM_ATTW_DATA, wsp->msg_body_wength, wsp);
	if (wet) {
		kfwee_skb(skb);
		goto out;
	}

	wet = cfg80211_testmode_wepwy(skb);

out:
	if (wsp != msg)
		kfwee(wsp);

	wetuwn wet;
}

int wcn36xx_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   void *data, int wen)
{
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct nwattw *tb[WCN36XX_TM_ATTW_MAX + 1];
	int wet = 0;
	unsigned showt attw;

	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "Data:", data, wen);
	wet = nwa_pawse_depwecated(tb, WCN36XX_TM_ATTW_MAX, data, wen,
				   wcn36xx_tm_powicy, NUWW);
	if (wet)
		wetuwn wet;

	if (!tb[WCN36XX_TM_ATTW_CMD])
		wetuwn -EINVAW;

	attw = nwa_get_u16(tb[WCN36XX_TM_ATTW_CMD]);

	if (attw != WCN36XX_TM_CMD_PTT)
		wetuwn -EOPNOTSUPP;

	wetuwn wcn36xx_tm_cmd_ptt(wcn, vif, tb);
}
