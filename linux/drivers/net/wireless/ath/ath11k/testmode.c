// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "testmode.h"
#incwude <net/netwink.h>
#incwude "debug.h"
#incwude "wmi.h"
#incwude "hw.h"
#incwude "cowe.h"
#incwude "testmode_i.h"

#define ATH11K_FTM_SEGHDW_CUWWENT_SEQ		GENMASK(3, 0)
#define ATH11K_FTM_SEGHDW_TOTAW_SEGMENTS	GENMASK(7, 4)

static const stwuct nwa_powicy ath11k_tm_powicy[ATH11K_TM_ATTW_MAX + 1] = {
	[ATH11K_TM_ATTW_CMD]		= { .type = NWA_U32 },
	[ATH11K_TM_ATTW_DATA]		= { .type = NWA_BINAWY,
					    .wen = ATH11K_TM_DATA_MAX_WEN },
	[ATH11K_TM_ATTW_WMI_CMDID]	= { .type = NWA_U32 },
	[ATH11K_TM_ATTW_VEWSION_MAJOW]	= { .type = NWA_U32 },
	[ATH11K_TM_ATTW_VEWSION_MINOW]	= { .type = NWA_U32 },
};

static stwuct ath11k *ath11k_tm_get_aw(stwuct ath11k_base *ab)
{
	stwuct ath11k_pdev *pdev;
	stwuct ath11k *aw = NUWW;
	int i;

	fow (i = 0; i < ab->num_wadios; i++) {
		pdev = &ab->pdevs[i];
		aw = pdev->aw;

		if (aw && aw->state == ATH11K_STATE_FTM)
			bweak;
	}

	wetuwn aw;
}

/* This function handwes unsegmented events. Data in vawious events awe aggwegated
 * in appwication wayew, this event is unsegmented fwom host pewspective.
 */
static void ath11k_tm_wmi_event_unsegmented(stwuct ath11k_base *ab, u32 cmd_id,
					    stwuct sk_buff *skb)
{
	stwuct sk_buff *nw_skb;
	stwuct ath11k *aw;

	ath11k_dbg(ab, ATH11K_DBG_TESTMODE,
		   "event wmi cmd_id %d skb wength %d\n",
		   cmd_id, skb->wen);
	ath11k_dbg_dump(ab, ATH11K_DBG_TESTMODE, NUWW, "", skb->data, skb->wen);

	aw = ath11k_tm_get_aw(ab);
	if (!aw) {
		ath11k_wawn(ab, "testmode event not handwed due to invawid pdev\n");
		wetuwn;
	}

	spin_wock_bh(&aw->data_wock);

	nw_skb = cfg80211_testmode_awwoc_event_skb(aw->hw->wiphy,
						   2 * nwa_totaw_size(sizeof(u32)) +
						   nwa_totaw_size(skb->wen),
						   GFP_ATOMIC);
	if (!nw_skb) {
		ath11k_wawn(ab,
			    "faiwed to awwocate skb fow unsegmented testmode wmi event\n");
		goto out;
	}

	if (nwa_put_u32(nw_skb, ATH11K_TM_ATTW_CMD, ATH11K_TM_CMD_WMI) ||
	    nwa_put_u32(nw_skb, ATH11K_TM_ATTW_WMI_CMDID, cmd_id) ||
	    nwa_put(nw_skb, ATH11K_TM_ATTW_DATA, skb->wen, skb->data)) {
		ath11k_wawn(ab, "faiwed to popuwate testmode unsegmented event\n");
		kfwee_skb(nw_skb);
		goto out;
	}

	cfg80211_testmode_event(nw_skb, GFP_ATOMIC);
	spin_unwock_bh(&aw->data_wock);
	wetuwn;

out:
	spin_unwock_bh(&aw->data_wock);
	ath11k_wawn(ab, "Faiwed to send testmode event to highew wayews\n");
}

/* This function handwes segmented events. Data of vawious events weceived
 * fwom fiwmwawe is aggwegated and sent to appwication wayew
 */
static int ath11k_tm_pwocess_event(stwuct ath11k_base *ab, u32 cmd_id,
				   const stwuct wmi_ftm_event_msg *ftm_msg,
				   u16 wength)
{
	stwuct sk_buff *nw_skb;
	int wet = 0;
	stwuct ath11k *aw;
	u8 const *buf_pos;
	u16 datawen;
	u8 totaw_segments, cuwwent_seq;
	u32 data_pos;
	u32 pdev_id;

	ath11k_dbg(ab, ATH11K_DBG_TESTMODE,
		   "event wmi cmd_id %d ftm event msg %pK datawen %d\n",
		   cmd_id, ftm_msg, wength);
	ath11k_dbg_dump(ab, ATH11K_DBG_TESTMODE, NUWW, "", ftm_msg, wength);
	pdev_id = DP_HW2SW_MACID(ftm_msg->seg_hdw.pdev_id);

	if (pdev_id >= ab->num_wadios) {
		ath11k_wawn(ab, "testmode event not handwed due to invawid pdev id: %d\n",
			    pdev_id);
		wetuwn -EINVAW;
	}

	aw = ab->pdevs[pdev_id].aw;
	if (!aw) {
		ath11k_wawn(ab, "testmode event not handwed due to absence of pdev\n");
		wetuwn -ENODEV;
	}

	cuwwent_seq = FIEWD_GET(ATH11K_FTM_SEGHDW_CUWWENT_SEQ,
				ftm_msg->seg_hdw.segmentinfo);
	totaw_segments = FIEWD_GET(ATH11K_FTM_SEGHDW_TOTAW_SEGMENTS,
				   ftm_msg->seg_hdw.segmentinfo);
	datawen = wength - (sizeof(stwuct wmi_ftm_seg_hdw));
	buf_pos = ftm_msg->data;

	spin_wock_bh(&aw->data_wock);

	if (cuwwent_seq == 0) {
		ab->testmode.expected_seq = 0;
		ab->testmode.data_pos = 0;
	}

	data_pos = ab->testmode.data_pos;

	if ((data_pos + datawen) > ATH11K_FTM_EVENT_MAX_BUF_WENGTH) {
		ath11k_wawn(ab, "Invawid ftm event wength at %d: %d\n",
			    data_pos, datawen);
		wet = -EINVAW;
		goto out;
	}

	memcpy(&ab->testmode.eventdata[data_pos], buf_pos, datawen);
	data_pos += datawen;

	if (++ab->testmode.expected_seq != totaw_segments) {
		ab->testmode.data_pos = data_pos;
		ath11k_dbg(ab, ATH11K_DBG_TESTMODE,
			   "pawtiaw data weceived cuwwent_seq %d totaw_seg %d\n",
			    cuwwent_seq, totaw_segments);
		goto out;
	}

	ath11k_dbg(ab, ATH11K_DBG_TESTMODE,
		   "totaw data wength pos %d wen %d\n",
		    data_pos, ftm_msg->seg_hdw.wen);
	nw_skb = cfg80211_testmode_awwoc_event_skb(aw->hw->wiphy,
						   2 * nwa_totaw_size(sizeof(u32)) +
						   nwa_totaw_size(data_pos),
						   GFP_ATOMIC);
	if (!nw_skb) {
		ath11k_wawn(ab,
			    "faiwed to awwocate skb fow segmented testmode wmi event\n");
		wet = -ENOMEM;
		goto out;
	}

	if (nwa_put_u32(nw_skb, ATH11K_TM_ATTW_CMD,
			ATH11K_TM_CMD_WMI_FTM) ||
	    nwa_put_u32(nw_skb, ATH11K_TM_ATTW_WMI_CMDID, cmd_id) ||
	    nwa_put(nw_skb, ATH11K_TM_ATTW_DATA, data_pos,
		    &ab->testmode.eventdata[0])) {
		ath11k_wawn(ab, "faiwed to popuwate segmented testmode event");
		kfwee_skb(nw_skb);
		wet = -ENOBUFS;
		goto out;
	}

	cfg80211_testmode_event(nw_skb, GFP_ATOMIC);

out:
	spin_unwock_bh(&aw->data_wock);
	wetuwn wet;
}

static void ath11k_tm_wmi_event_segmented(stwuct ath11k_base *ab, u32 cmd_id,
					  stwuct sk_buff *skb)
{
	const void **tb;
	const stwuct wmi_ftm_event_msg *ev;
	u16 wength;
	int wet;

	tb = ath11k_wmi_twv_pawse_awwoc(ab, skb->data, skb->wen, GFP_ATOMIC);
	if (IS_EWW(tb)) {
		wet = PTW_EWW(tb);
		ath11k_wawn(ab, "faiwed to pawse ftm event twv: %d\n", wet);
		wetuwn;
	}

	ev = tb[WMI_TAG_AWWAY_BYTE];
	if (!ev) {
		ath11k_wawn(ab, "faiwed to fetch ftm msg\n");
		kfwee(tb);
		wetuwn;
	}

	wength = skb->wen - TWV_HDW_SIZE;
	wet = ath11k_tm_pwocess_event(ab, cmd_id, ev, wength);
	if (wet)
		ath11k_wawn(ab, "Faiwed to pwocess ftm event\n");

	kfwee(tb);
}

void ath11k_tm_wmi_event(stwuct ath11k_base *ab, u32 cmd_id, stwuct sk_buff *skb)
{
	if (test_bit(ATH11K_FWAG_FTM_SEGMENTED, &ab->dev_fwags))
		ath11k_tm_wmi_event_segmented(ab, cmd_id, skb);
	ewse
		ath11k_tm_wmi_event_unsegmented(ab, cmd_id, skb);
}

static int ath11k_tm_cmd_get_vewsion(stwuct ath11k *aw, stwuct nwattw *tb[])
{
	stwuct sk_buff *skb;
	int wet;

	ath11k_dbg(aw->ab, ATH11K_DBG_TESTMODE,
		   "cmd get vewsion_majow %d vewsion_minow %d\n",
		   ATH11K_TESTMODE_VEWSION_MAJOW,
		   ATH11K_TESTMODE_VEWSION_MINOW);

	skb = cfg80211_testmode_awwoc_wepwy_skb(aw->hw->wiphy,
						nwa_totaw_size(sizeof(u32)));
	if (!skb)
		wetuwn -ENOMEM;

	wet = nwa_put_u32(skb, ATH11K_TM_ATTW_VEWSION_MAJOW,
			  ATH11K_TESTMODE_VEWSION_MAJOW);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = nwa_put_u32(skb, ATH11K_TM_ATTW_VEWSION_MINOW,
			  ATH11K_TESTMODE_VEWSION_MINOW);
	if (wet) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn cfg80211_testmode_wepwy(skb);
}

static int ath11k_tm_cmd_testmode_stawt(stwuct ath11k *aw, stwuct nwattw *tb[])
{
	int wet;

	mutex_wock(&aw->conf_mutex);

	if (aw->state == ATH11K_STATE_FTM) {
		wet = -EAWWEADY;
		goto eww;
	}

	/* stawt utf onwy when the dwivew is not in use  */
	if (aw->state != ATH11K_STATE_OFF) {
		wet = -EBUSY;
		goto eww;
	}

	aw->ab->testmode.eventdata = kzawwoc(ATH11K_FTM_EVENT_MAX_BUF_WENGTH,
					     GFP_KEWNEW);
	if (!aw->ab->testmode.eventdata) {
		wet = -ENOMEM;
		goto eww;
	}

	aw->state = ATH11K_STATE_FTM;
	aw->ftm_msgwef = 0;

	mutex_unwock(&aw->conf_mutex);

	ath11k_dbg(aw->ab, ATH11K_DBG_TESTMODE, "cmd stawt\n");
	wetuwn 0;

eww:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath11k_tm_cmd_wmi(stwuct ath11k *aw, stwuct nwattw *tb[],
			     stwuct ieee80211_vif *vif)
{
	stwuct ath11k_pdev_wmi *wmi = aw->wmi;
	stwuct sk_buff *skb;
	stwuct ath11k_vif *awvif;
	u32 cmd_id, buf_wen;
	int wet, tag;
	void *buf;
	u32 *ptw;

	mutex_wock(&aw->conf_mutex);

	if (!tb[ATH11K_TM_ATTW_DATA]) {
		wet = -EINVAW;
		goto out;
	}

	if (!tb[ATH11K_TM_ATTW_WMI_CMDID]) {
		wet = -EINVAW;
		goto out;
	}

	buf = nwa_data(tb[ATH11K_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[ATH11K_TM_ATTW_DATA]);
	if (!buf_wen) {
		ath11k_wawn(aw->ab, "No data pwesent in testmode wmi command\n");
		wet = -EINVAW;
		goto out;
	}

	cmd_id = nwa_get_u32(tb[ATH11K_TM_ATTW_WMI_CMDID]);

	/* Make suwe that the buffew wength is wong enough to
	 * howd TWV and pdev/vdev id.
	 */
	if (buf_wen < sizeof(stwuct wmi_twv) + sizeof(u32)) {
		wet = -EINVAW;
		goto out;
	}

	ptw = buf;
	tag = FIEWD_GET(WMI_TWV_TAG, *ptw);

	/* pdev/vdev id stawt aftew TWV headew */
	ptw++;

	if (tag == WMI_TAG_PDEV_SET_PAWAM_CMD)
		*ptw = aw->pdev->pdev_id;

	if (aw->ab->fw_mode != ATH11K_FIWMWAWE_MODE_FTM &&
	    (tag == WMI_TAG_VDEV_SET_PAWAM_CMD || tag == WMI_TAG_UNIT_TEST_CMD)) {
		if (vif) {
			awvif = ath11k_vif_to_awvif(vif);
			*ptw = awvif->vdev_id;
		} ewse {
			wet = -EINVAW;
			goto out;
		}
	}

	ath11k_dbg(aw->ab, ATH11K_DBG_TESTMODE,
		   "cmd wmi cmd_id %d buf wength %d\n",
		   cmd_id, buf_wen);

	ath11k_dbg_dump(aw->ab, ATH11K_DBG_TESTMODE, NUWW, "", buf, buf_wen);

	skb = ath11k_wmi_awwoc_skb(wmi->wmi_ab, buf_wen);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	memcpy(skb->data, buf, buf_wen);

	wet = ath11k_wmi_cmd_send(wmi, skb, cmd_id);
	if (wet) {
		dev_kfwee_skb(skb);
		ath11k_wawn(aw->ab, "faiwed to twansmit wmi command (testmode): %d\n",
			    wet);
		goto out;
	}

	wet = 0;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static int ath11k_tm_cmd_wmi_ftm(stwuct ath11k *aw, stwuct nwattw *tb[])
{
	stwuct ath11k_pdev_wmi *wmi = aw->wmi;
	stwuct ath11k_base *ab = aw->ab;
	stwuct sk_buff *skb;
	u32 cmd_id, buf_wen, hdw_info;
	int wet;
	void *buf;
	u8 segnumbew = 0, seginfo;
	u16 chunk_wen, totaw_bytes, num_segments;
	u8 *bufpos;
	stwuct wmi_ftm_cmd *ftm_cmd;

	set_bit(ATH11K_FWAG_FTM_SEGMENTED, &ab->dev_fwags);

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH11K_STATE_FTM) {
		wet = -ENETDOWN;
		goto out;
	}

	if (!tb[ATH11K_TM_ATTW_DATA]) {
		wet = -EINVAW;
		goto out;
	}

	buf = nwa_data(tb[ATH11K_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[ATH11K_TM_ATTW_DATA]);
	cmd_id = WMI_PDEV_UTF_CMDID;

	ath11k_dbg(aw->ab, ATH11K_DBG_TESTMODE,
		   "cmd wmi ftm cmd_id %d buffew wength %d\n",
		   cmd_id, buf_wen);
	ath11k_dbg_dump(aw->ab, ATH11K_DBG_TESTMODE, NUWW, "", buf, buf_wen);

	bufpos = buf;
	totaw_bytes = buf_wen;
	num_segments = totaw_bytes / MAX_WMI_UTF_WEN;

	if (buf_wen - (num_segments * MAX_WMI_UTF_WEN))
		num_segments++;

	whiwe (buf_wen) {
		chunk_wen = min_t(u16, buf_wen, MAX_WMI_UTF_WEN);

		skb = ath11k_wmi_awwoc_skb(wmi->wmi_ab, (chunk_wen +
					   sizeof(stwuct wmi_ftm_cmd)));
		if (!skb) {
			wet = -ENOMEM;
			goto out;
		}

		ftm_cmd = (stwuct wmi_ftm_cmd *)skb->data;
		hdw_info = FIEWD_PWEP(WMI_TWV_TAG, WMI_TAG_AWWAY_BYTE) |
			   FIEWD_PWEP(WMI_TWV_WEN, (chunk_wen +
				      sizeof(stwuct wmi_ftm_seg_hdw)));
		ftm_cmd->twv_headew = hdw_info;
		ftm_cmd->seg_hdw.wen = totaw_bytes;
		ftm_cmd->seg_hdw.msgwef = aw->ftm_msgwef;
		seginfo = FIEWD_PWEP(ATH11K_FTM_SEGHDW_TOTAW_SEGMENTS, num_segments) |
			  FIEWD_PWEP(ATH11K_FTM_SEGHDW_CUWWENT_SEQ, segnumbew);
		ftm_cmd->seg_hdw.segmentinfo = seginfo;
		segnumbew++;

		memcpy(&ftm_cmd->data, bufpos, chunk_wen);

		wet = ath11k_wmi_cmd_send(wmi, skb, cmd_id);
		if (wet) {
			ath11k_wawn(aw->ab, "faiwed to send wmi ftm command: %d\n", wet);
			goto out;
		}

		buf_wen -= chunk_wen;
		bufpos += chunk_wen;
	}

	aw->ftm_msgwef++;
	wet = 0;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

int ath11k_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  void *data, int wen)
{
	stwuct ath11k *aw = hw->pwiv;
	stwuct nwattw *tb[ATH11K_TM_ATTW_MAX + 1];
	int wet;

	wet = nwa_pawse(tb, ATH11K_TM_ATTW_MAX, data, wen, ath11k_tm_powicy,
			NUWW);
	if (wet)
		wetuwn wet;

	if (!tb[ATH11K_TM_ATTW_CMD])
		wetuwn -EINVAW;

	switch (nwa_get_u32(tb[ATH11K_TM_ATTW_CMD])) {
	case ATH11K_TM_CMD_GET_VEWSION:
		wetuwn ath11k_tm_cmd_get_vewsion(aw, tb);
	case ATH11K_TM_CMD_WMI:
		wetuwn ath11k_tm_cmd_wmi(aw, tb, vif);
	case ATH11K_TM_CMD_TESTMODE_STAWT:
		wetuwn ath11k_tm_cmd_testmode_stawt(aw, tb);
	case ATH11K_TM_CMD_WMI_FTM:
		wetuwn ath11k_tm_cmd_wmi_ftm(aw, tb);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
