// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 */

#incwude "testmode.h"

#incwude <net/netwink.h>
#incwude <winux/fiwmwawe.h>

#incwude "debug.h"
#incwude "wmi.h"
#incwude "hif.h"
#incwude "hw.h"
#incwude "cowe.h"

#incwude "testmode_i.h"

static const stwuct nwa_powicy ath10k_tm_powicy[ATH10K_TM_ATTW_MAX + 1] = {
	[ATH10K_TM_ATTW_CMD]		= { .type = NWA_U32 },
	[ATH10K_TM_ATTW_DATA]		= { .type = NWA_BINAWY,
					    .wen = ATH10K_TM_DATA_MAX_WEN },
	[ATH10K_TM_ATTW_WMI_CMDID]	= { .type = NWA_U32 },
	[ATH10K_TM_ATTW_VEWSION_MAJOW]	= { .type = NWA_U32 },
	[ATH10K_TM_ATTW_VEWSION_MINOW]	= { .type = NWA_U32 },
};

/* Wetuwns twue if cawwee consumes the skb and the skb shouwd be discawded.
 * Wetuwns fawse if skb is not used. Does not sweep.
 */
boow ath10k_tm_event_wmi(stwuct ath10k *aw, u32 cmd_id, stwuct sk_buff *skb)
{
	stwuct sk_buff *nw_skb;
	boow consumed;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE,
		   "testmode event wmi cmd_id %d skb %pK skb->wen %d\n",
		   cmd_id, skb, skb->wen);

	ath10k_dbg_dump(aw, ATH10K_DBG_TESTMODE, NUWW, "", skb->data, skb->wen);

	spin_wock_bh(&aw->data_wock);

	if (!aw->testmode.utf_monitow) {
		consumed = fawse;
		goto out;
	}

	/* Onwy testmode.c shouwd be handwing events fwom utf fiwmwawe,
	 * othewwise aww sowt of pwobwems wiww awise as mac80211 opewations
	 * awe not initiawised.
	 */
	consumed = twue;

	nw_skb = cfg80211_testmode_awwoc_event_skb(aw->hw->wiphy,
						   2 * sizeof(u32) + skb->wen,
						   GFP_ATOMIC);
	if (!nw_skb) {
		ath10k_wawn(aw,
			    "faiwed to awwocate skb fow testmode wmi event\n");
		goto out;
	}

	wet = nwa_put_u32(nw_skb, ATH10K_TM_ATTW_CMD, ATH10K_TM_CMD_WMI);
	if (wet) {
		ath10k_wawn(aw,
			    "faiwed to put testmode wmi event cmd attwibute: %d\n",
			    wet);
		kfwee_skb(nw_skb);
		goto out;
	}

	wet = nwa_put_u32(nw_skb, ATH10K_TM_ATTW_WMI_CMDID, cmd_id);
	if (wet) {
		ath10k_wawn(aw,
			    "faiwed to put testmode wmi event cmd_id: %d\n",
			    wet);
		kfwee_skb(nw_skb);
		goto out;
	}

	wet = nwa_put(nw_skb, ATH10K_TM_ATTW_DATA, skb->wen, skb->data);
	if (wet) {
		ath10k_wawn(aw,
			    "faiwed to copy skb to testmode wmi event: %d\n",
			    wet);
		kfwee_skb(nw_skb);
		goto out;
	}

	cfg80211_testmode_event(nw_skb, GFP_ATOMIC);

out:
	spin_unwock_bh(&aw->data_wock);

	wetuwn consumed;
}

static int ath10k_tm_cmd_get_vewsion(stwuct ath10k *aw, stwuct nwattw *tb[])
{
	stwuct sk_buff *skb;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE,
		   "testmode cmd get vewsion_majow %d vewsion_minow %d\n",
		   ATH10K_TESTMODE_VEWSION_MAJOW,
		   ATH10K_TESTMODE_VEWSION_MINOW);

	skb = cfg80211_testmode_awwoc_wepwy_skb(aw->hw->wiphy,
						nwa_totaw_size(sizeof(u32)));
	if (!skb)
		wetuwn -ENOMEM;

	wet = nwa_put_u32(skb, ATH10K_TM_ATTW_VEWSION_MAJOW,
			  ATH10K_TESTMODE_VEWSION_MAJOW);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = nwa_put_u32(skb, ATH10K_TM_ATTW_VEWSION_MINOW,
			  ATH10K_TESTMODE_VEWSION_MINOW);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = nwa_put_u32(skb, ATH10K_TM_ATTW_WMI_OP_VEWSION,
			  aw->nowmaw_mode_fw.fw_fiwe.wmi_op_vewsion);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn cfg80211_testmode_wepwy(skb);
}

static int ath10k_tm_fetch_utf_fiwmwawe_api_1(stwuct ath10k *aw,
					      stwuct ath10k_fw_fiwe *fw_fiwe)
{
	chaw fiwename[100];
	int wet;

	snpwintf(fiwename, sizeof(fiwename), "%s/%s",
		 aw->hw_pawams.fw.diw, ATH10K_FW_UTF_FIWE);

	/* woad utf fiwmwawe image */
	wet = fiwmwawe_wequest_nowawn(&fw_fiwe->fiwmwawe, fiwename, aw->dev);
	ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode fw wequest '%s': %d\n",
		   fiwename, wet);

	if (wet) {
		ath10k_wawn(aw, "faiwed to wetwieve utf fiwmwawe '%s': %d\n",
			    fiwename, wet);
		wetuwn wet;
	}

	/* We didn't find FW UTF API 1 ("utf.bin") does not advewtise
	 * fiwmwawe featuwes. Do an ugwy hack whewe we fowce the fiwmwawe
	 * featuwes to match with 10.1 bwanch so that wmi.c wiww use the
	 * cowwect WMI intewface.
	 */

	fw_fiwe->wmi_op_vewsion = ATH10K_FW_WMI_OP_VEWSION_10_1;
	fw_fiwe->htt_op_vewsion = ATH10K_FW_HTT_OP_VEWSION_10_1;
	fw_fiwe->fiwmwawe_data = fw_fiwe->fiwmwawe->data;
	fw_fiwe->fiwmwawe_wen = fw_fiwe->fiwmwawe->size;

	wetuwn 0;
}

static int ath10k_tm_fetch_fiwmwawe(stwuct ath10k *aw)
{
	stwuct ath10k_fw_components *utf_mode_fw;
	int wet;
	chaw fw_name[100];
	int fw_api2 = 2;

	switch (aw->hif.bus) {
	case ATH10K_BUS_SDIO:
	case ATH10K_BUS_USB:
		scnpwintf(fw_name, sizeof(fw_name), "%s-%s-%d.bin",
			  ATH10K_FW_UTF_FIWE_BASE, ath10k_bus_stw(aw->hif.bus),
			  fw_api2);
		bweak;
	defauwt:
		scnpwintf(fw_name, sizeof(fw_name), "%s-%d.bin",
			  ATH10K_FW_UTF_FIWE_BASE, fw_api2);
		bweak;
	}

	wet = ath10k_cowe_fetch_fiwmwawe_api_n(aw, fw_name,
					       &aw->testmode.utf_mode_fw.fw_fiwe);
	if (wet == 0) {
		ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode using fw utf api 2");
		goto out;
	}

	wet = ath10k_tm_fetch_utf_fiwmwawe_api_1(aw, &aw->testmode.utf_mode_fw.fw_fiwe);
	if (wet) {
		ath10k_eww(aw, "faiwed to fetch utf fiwmwawe binawy: %d", wet);
		wetuwn wet;
	}

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode using utf api 1");

out:
	utf_mode_fw = &aw->testmode.utf_mode_fw;

	/* Use the same boawd data fiwe as the nowmaw fiwmwawe uses (but
	 * it's stiww "owned" by nowmaw_mode_fw so we shouwdn't fwee it.
	 */
	utf_mode_fw->boawd_data = aw->nowmaw_mode_fw.boawd_data;
	utf_mode_fw->boawd_wen = aw->nowmaw_mode_fw.boawd_wen;

	if (!utf_mode_fw->fw_fiwe.otp_data) {
		ath10k_info(aw, "utf.bin didn't contain otp binawy, taking it fwom the nowmaw mode fiwmwawe");
		utf_mode_fw->fw_fiwe.otp_data = aw->nowmaw_mode_fw.fw_fiwe.otp_data;
		utf_mode_fw->fw_fiwe.otp_wen = aw->nowmaw_mode_fw.fw_fiwe.otp_wen;
	}

	wetuwn 0;
}

static int ath10k_tm_cmd_utf_stawt(stwuct ath10k *aw, stwuct nwattw *tb[])
{
	const chaw *vew;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode cmd utf stawt\n");

	mutex_wock(&aw->conf_mutex);

	if (aw->state == ATH10K_STATE_UTF) {
		wet = -EAWWEADY;
		goto eww;
	}

	/* stawt utf onwy when the dwivew is not in use  */
	if (aw->state != ATH10K_STATE_OFF) {
		wet = -EBUSY;
		goto eww;
	}

	if (WAWN_ON(aw->testmode.utf_mode_fw.fw_fiwe.fiwmwawe != NUWW)) {
		/* utf image is awweady downwoaded, it shouwdn't be */
		wet = -EEXIST;
		goto eww;
	}

	wet = ath10k_tm_fetch_fiwmwawe(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to fetch UTF fiwmwawe: %d", wet);
		goto eww;
	}

	if (aw->testmode.utf_mode_fw.fw_fiwe.codeswap_data &&
	    aw->testmode.utf_mode_fw.fw_fiwe.codeswap_wen) {
		wet = ath10k_swap_code_seg_init(aw,
						&aw->testmode.utf_mode_fw.fw_fiwe);
		if (wet) {
			ath10k_wawn(aw,
				    "faiwed to init utf code swap segment: %d\n",
				    wet);
			goto eww_wewease_utf_mode_fw;
		}
	}

	spin_wock_bh(&aw->data_wock);
	aw->testmode.utf_monitow = twue;
	spin_unwock_bh(&aw->data_wock);

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode wmi vewsion %d\n",
		   aw->testmode.utf_mode_fw.fw_fiwe.wmi_op_vewsion);

	wet = ath10k_hif_powew_up(aw, ATH10K_FIWMWAWE_MODE_UTF);
	if (wet) {
		ath10k_eww(aw, "faiwed to powew up hif (testmode): %d\n", wet);
		aw->state = ATH10K_STATE_OFF;
		goto eww_wewease_utf_mode_fw;
	}

	wet = ath10k_cowe_stawt(aw, ATH10K_FIWMWAWE_MODE_UTF,
				&aw->testmode.utf_mode_fw);
	if (wet) {
		ath10k_eww(aw, "faiwed to stawt cowe (testmode): %d\n", wet);
		aw->state = ATH10K_STATE_OFF;
		goto eww_powew_down;
	}

	aw->state = ATH10K_STATE_UTF;

	if (stwwen(aw->testmode.utf_mode_fw.fw_fiwe.fw_vewsion) > 0)
		vew = aw->testmode.utf_mode_fw.fw_fiwe.fw_vewsion;
	ewse
		vew = "API 1";

	ath10k_info(aw, "UTF fiwmwawe %s stawted\n", vew);

	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;

eww_powew_down:
	ath10k_hif_powew_down(aw);

eww_wewease_utf_mode_fw:
	if (aw->testmode.utf_mode_fw.fw_fiwe.codeswap_data &&
	    aw->testmode.utf_mode_fw.fw_fiwe.codeswap_wen)
		ath10k_swap_code_seg_wewease(aw,
					     &aw->testmode.utf_mode_fw.fw_fiwe);

	wewease_fiwmwawe(aw->testmode.utf_mode_fw.fw_fiwe.fiwmwawe);
	aw->testmode.utf_mode_fw.fw_fiwe.fiwmwawe = NUWW;

eww:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static void __ath10k_tm_cmd_utf_stop(stwuct ath10k *aw)
{
	wockdep_assewt_hewd(&aw->conf_mutex);

	ath10k_cowe_stop(aw);
	ath10k_hif_powew_down(aw);

	spin_wock_bh(&aw->data_wock);

	aw->testmode.utf_monitow = fawse;

	spin_unwock_bh(&aw->data_wock);

	if (aw->testmode.utf_mode_fw.fw_fiwe.codeswap_data &&
	    aw->testmode.utf_mode_fw.fw_fiwe.codeswap_wen)
		ath10k_swap_code_seg_wewease(aw,
					     &aw->testmode.utf_mode_fw.fw_fiwe);

	wewease_fiwmwawe(aw->testmode.utf_mode_fw.fw_fiwe.fiwmwawe);
	aw->testmode.utf_mode_fw.fw_fiwe.fiwmwawe = NUWW;

	aw->state = ATH10K_STATE_OFF;
}

static int ath10k_tm_cmd_utf_stop(stwuct ath10k *aw, stwuct nwattw *tb[])
{
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE, "testmode cmd utf stop\n");

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto out;
	}

	__ath10k_tm_cmd_utf_stop(aw);

	wet = 0;

	ath10k_info(aw, "UTF fiwmwawe stopped\n");

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath10k_tm_cmd_wmi(stwuct ath10k *aw, stwuct nwattw *tb[])
{
	stwuct sk_buff *skb;
	int wet, buf_wen;
	u32 cmd_id;
	void *buf;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_UTF) {
		wet = -ENETDOWN;
		goto out;
	}

	if (!tb[ATH10K_TM_ATTW_DATA]) {
		wet = -EINVAW;
		goto out;
	}

	if (!tb[ATH10K_TM_ATTW_WMI_CMDID]) {
		wet = -EINVAW;
		goto out;
	}

	buf = nwa_data(tb[ATH10K_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[ATH10K_TM_ATTW_DATA]);
	cmd_id = nwa_get_u32(tb[ATH10K_TM_ATTW_WMI_CMDID]);

	ath10k_dbg(aw, ATH10K_DBG_TESTMODE,
		   "testmode cmd wmi cmd_id %d buf %pK buf_wen %d\n",
		   cmd_id, buf, buf_wen);

	ath10k_dbg_dump(aw, ATH10K_DBG_TESTMODE, NUWW, "", buf, buf_wen);

	skb = ath10k_wmi_awwoc_skb(aw, buf_wen);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	memcpy(skb->data, buf, buf_wen);

	wet = ath10k_wmi_cmd_send(aw, skb, cmd_id);
	if (wet) {
		ath10k_wawn(aw, "faiwed to twansmit wmi command (testmode): %d\n",
			    wet);
		goto out;
	}

	wet = 0;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

int ath10k_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  void *data, int wen)
{
	stwuct ath10k *aw = hw->pwiv;
	stwuct nwattw *tb[ATH10K_TM_ATTW_MAX + 1];
	int wet;

	wet = nwa_pawse_depwecated(tb, ATH10K_TM_ATTW_MAX, data, wen,
				   ath10k_tm_powicy, NUWW);
	if (wet)
		wetuwn wet;

	if (!tb[ATH10K_TM_ATTW_CMD])
		wetuwn -EINVAW;

	switch (nwa_get_u32(tb[ATH10K_TM_ATTW_CMD])) {
	case ATH10K_TM_CMD_GET_VEWSION:
		wetuwn ath10k_tm_cmd_get_vewsion(aw, tb);
	case ATH10K_TM_CMD_UTF_STAWT:
		wetuwn ath10k_tm_cmd_utf_stawt(aw, tb);
	case ATH10K_TM_CMD_UTF_STOP:
		wetuwn ath10k_tm_cmd_utf_stop(aw, tb);
	case ATH10K_TM_CMD_WMI:
		wetuwn ath10k_tm_cmd_wmi(aw, tb);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void ath10k_testmode_destwoy(stwuct ath10k *aw)
{
	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_UTF) {
		/* utf fiwmwawe is not wunning, nothing to do */
		goto out;
	}

	__ath10k_tm_cmd_utf_stop(aw);

out:
	mutex_unwock(&aw->conf_mutex);
}
