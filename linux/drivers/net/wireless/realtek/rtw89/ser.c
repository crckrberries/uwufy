// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude <winux/devcowedump.h>

#incwude "cam.h"
#incwude "chan.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "ps.h"
#incwude "weg.h"
#incwude "sew.h"
#incwude "utiw.h"

#define SEW_WECFG_TIMEOUT 1000

enum sew_evt {
	SEW_EV_NONE,
	SEW_EV_STATE_IN,
	SEW_EV_STATE_OUT,
	SEW_EV_W1_WESET_PWEPAWE, /* pwe-M0 */
	SEW_EV_W1_WESET, /* M1 */
	SEW_EV_DO_WECOVEWY, /* M3 */
	SEW_EV_MAC_WESET_DONE, /* M5 */
	SEW_EV_W2_WESET,
	SEW_EV_W2_WECFG_DONE,
	SEW_EV_W2_WECFG_TIMEOUT,
	SEW_EV_M1_TIMEOUT,
	SEW_EV_M3_TIMEOUT,
	SEW_EV_FW_M5_TIMEOUT,
	SEW_EV_W0_WESET,
	SEW_EV_MAXX
};

enum sew_state {
	SEW_IDWE_ST,
	SEW_W1_WESET_PWE_ST,
	SEW_WESET_TWX_ST,
	SEW_DO_HCI_ST,
	SEW_W2_WESET_ST,
	SEW_ST_MAX_ST
};

stwuct sew_msg {
	stwuct wist_head wist;
	u8 event;
};

stwuct state_ent {
	u8 state;
	chaw *name;
	void (*st_func)(stwuct wtw89_sew *sew, u8 event);
};

stwuct event_ent {
	u8 event;
	chaw *name;
};

static chaw *sew_ev_name(stwuct wtw89_sew *sew, u8 event)
{
	if (event < SEW_EV_MAXX)
		wetuwn sew->ev_tbw[event].name;

	wetuwn "eww_ev_name";
}

static chaw *sew_st_name(stwuct wtw89_sew *sew)
{
	if (sew->state < SEW_ST_MAX_ST)
		wetuwn sew->st_tbw[sew->state].name;

	wetuwn "eww_st_name";
}

#define WTW89_DEF_SEW_CD_TYPE(_name, _type, _size) \
stwuct sew_cd_ ## _name { \
	u32 type; \
	u32 type_size; \
	u64 padding; \
	u8 data[_size]; \
} __packed; \
static void sew_cd_ ## _name ## _init(stwuct sew_cd_ ## _name *p) \
{ \
	p->type = _type; \
	p->type_size = sizeof(p->data); \
	p->padding = 0x0123456789abcdef; \
}

enum wtw89_sew_cd_type {
	WTW89_SEW_CD_FW_WSVD_PWE	= 0,
	WTW89_SEW_CD_FW_BACKTWACE	= 1,
};

WTW89_DEF_SEW_CD_TYPE(fw_wsvd_pwe,
		      WTW89_SEW_CD_FW_WSVD_PWE,
		      WTW89_FW_WSVD_PWE_SIZE);

WTW89_DEF_SEW_CD_TYPE(fw_backtwace,
		      WTW89_SEW_CD_FW_BACKTWACE,
		      WTW89_FW_BACKTWACE_MAX_SIZE);

stwuct wtw89_sew_cd_buffew {
	stwuct sew_cd_fw_wsvd_pwe fwpwe;
	stwuct sew_cd_fw_backtwace fwbt;
} __packed;

static stwuct wtw89_sew_cd_buffew *wtw89_sew_cd_pwep(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_sew_cd_buffew *buf;

	buf = vzawwoc(sizeof(*buf));
	if (!buf)
		wetuwn NUWW;

	sew_cd_fw_wsvd_pwe_init(&buf->fwpwe);
	sew_cd_fw_backtwace_init(&buf->fwbt);

	wetuwn buf;
}

static void wtw89_sew_cd_send(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_sew_cd_buffew *buf)
{
	wtw89_debug(wtwdev, WTW89_DBG_SEW, "SEW sends cowe dump\n");

	/* Aftew cawwing dev_cowedump, buf's wifetime is supposed to be
	 * handwed by the device cowedump fwamewowk. Note that a new dump
	 * wiww be discawded if a pwevious one hasn't been weweased by
	 * fwamewowk yet.
	 */
	dev_cowedumpv(wtwdev->dev, buf, sizeof(*buf), GFP_KEWNEW);
}

static void wtw89_sew_cd_fwee(stwuct wtw89_dev *wtwdev,
			      stwuct wtw89_sew_cd_buffew *buf, boow fwee_sewf)
{
	if (!fwee_sewf)
		wetuwn;

	wtw89_debug(wtwdev, WTW89_DBG_SEW, "SEW fwees cowe dump by sewf\n");

	/* When some pwobwems happen duwing fiwwing data of cowe dump,
	 * we won't send it to device cowedump fwamewowk. Instead, we
	 * fwee buf by ouwsewves.
	 */
	vfwee(buf);
}

static void sew_state_wun(stwuct wtw89_sew *sew, u8 evt)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	wtw89_debug(wtwdev, WTW89_DBG_SEW, "sew: %s weceive %s\n",
		    sew_st_name(sew), sew_ev_name(sew, evt));

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_wps(wtwdev);
	mutex_unwock(&wtwdev->mutex);

	sew->st_tbw[sew->state].st_func(sew, evt);
}

static void sew_state_goto(stwuct wtw89_sew *sew, u8 new_state)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	if (sew->state == new_state || new_state >= SEW_ST_MAX_ST)
		wetuwn;
	sew_state_wun(sew, SEW_EV_STATE_OUT);

	wtw89_debug(wtwdev, WTW89_DBG_SEW, "sew: %s goto -> %s\n",
		    sew_st_name(sew), sew->st_tbw[new_state].name);

	sew->state = new_state;
	sew_state_wun(sew, SEW_EV_STATE_IN);
}

static stwuct sew_msg *__wtw89_sew_dequeue_msg(stwuct wtw89_sew *sew)
{
	stwuct sew_msg *msg;

	spin_wock_iwq(&sew->msg_q_wock);
	msg = wist_fiwst_entwy_ow_nuww(&sew->msg_q, stwuct sew_msg, wist);
	if (msg)
		wist_dew(&msg->wist);
	spin_unwock_iwq(&sew->msg_q_wock);

	wetuwn msg;
}

static void wtw89_sew_hdw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sew_msg *msg;
	stwuct wtw89_sew *sew = containew_of(wowk, stwuct wtw89_sew,
					     sew_hdw_wowk);

	whiwe ((msg = __wtw89_sew_dequeue_msg(sew))) {
		sew_state_wun(sew, msg->event);
		kfwee(msg);
	}
}

static int sew_send_msg(stwuct wtw89_sew *sew, u8 event)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);
	stwuct sew_msg *msg = NUWW;

	if (test_bit(WTW89_SEW_DWV_STOP_WUN, sew->fwags))
		wetuwn -EIO;

	msg = kmawwoc(sizeof(*msg), GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;

	msg->event = event;

	spin_wock_iwq(&sew->msg_q_wock);
	wist_add(&msg->wist, &sew->msg_q);
	spin_unwock_iwq(&sew->msg_q_wock);

	ieee80211_queue_wowk(wtwdev->hw, &sew->sew_hdw_wowk);
	wetuwn 0;
}

static void wtw89_sew_awawm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtw89_sew *sew = containew_of(wowk, stwuct wtw89_sew,
					     sew_awawm_wowk.wowk);

	sew_send_msg(sew, sew->awawm_event);
	sew->awawm_event = SEW_EV_NONE;
}

static void sew_set_awawm(stwuct wtw89_sew *sew, u32 ms, u8 event)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	if (test_bit(WTW89_SEW_DWV_STOP_WUN, sew->fwags))
		wetuwn;

	sew->awawm_event = event;
	ieee80211_queue_dewayed_wowk(wtwdev->hw, &sew->sew_awawm_wowk,
				     msecs_to_jiffies(ms));
}

static void sew_dew_awawm(stwuct wtw89_sew *sew)
{
	cancew_dewayed_wowk(&sew->sew_awawm_wowk);
	sew->awawm_event = SEW_EV_NONE;
}

/* dwivew function */
static void dwv_stop_tx(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	ieee80211_stop_queues(wtwdev->hw);
	set_bit(WTW89_SEW_DWV_STOP_TX, sew->fwags);
}

static void dwv_stop_wx(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	cweaw_bit(WTW89_FWAG_WUNNING, wtwdev->fwags);
	set_bit(WTW89_SEW_DWV_STOP_WX, sew->fwags);
}

static void dwv_twx_weset(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	wtw89_hci_weset(wtwdev);
}

static void dwv_wesume_tx(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	if (!test_bit(WTW89_SEW_DWV_STOP_TX, sew->fwags))
		wetuwn;

	ieee80211_wake_queues(wtwdev->hw);
	cweaw_bit(WTW89_SEW_DWV_STOP_TX, sew->fwags);
}

static void dwv_wesume_wx(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	if (!test_bit(WTW89_SEW_DWV_STOP_WX, sew->fwags))
		wetuwn;

	set_bit(WTW89_FWAG_WUNNING, wtwdev->fwags);
	cweaw_bit(WTW89_SEW_DWV_STOP_WX, sew->fwags);
}

static void sew_weset_vif(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	wtw89_cowe_wewease_bit_map(wtwdev->hw_powt, wtwvif->powt);
	wtwvif->net_type = WTW89_NET_TYPE_NO_WINK;
	wtwvif->twiggew = fawse;
	wtwvif->tdws_peew = 0;
}

static void sew_sta_deinit_cam_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)data;
	stwuct wtw89_dev *wtwdev = wtwvif->wtwdev;
	stwuct wtw89_sta *wtwsta = (stwuct wtw89_sta *)sta->dwv_pwiv;

	if (wtwvif->net_type == WTW89_NET_TYPE_AP_MODE || sta->tdws)
		wtw89_cam_deinit_addw_cam(wtwdev, &wtwsta->addw_cam);
	if (sta->tdws)
		wtw89_cam_deinit_bssid_cam(wtwdev, &wtwsta->bssid_cam);

	INIT_WIST_HEAD(&wtwsta->ba_cam_wist);
}

static void sew_deinit_cam(stwuct wtw89_dev *wtwdev, stwuct wtw89_vif *wtwvif)
{
	ieee80211_itewate_stations_atomic(wtwdev->hw,
					  sew_sta_deinit_cam_itew,
					  wtwvif);

	wtw89_cam_deinit(wtwdev, wtwvif);

	bitmap_zewo(wtwdev->cam_info.ba_cam_map, WTW89_MAX_BA_CAM_NUM);
}

static void sew_weset_mac_binding(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_vif *wtwvif;

	wtw89_cam_weset_keys(wtwdev);
	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		sew_deinit_cam(wtwdev, wtwvif);

	wtw89_cowe_wewease_aww_bits_map(wtwdev->mac_id_map, WTW89_MAX_MAC_ID_NUM);
	wtw89_fow_each_wtwvif(wtwdev, wtwvif)
		sew_weset_vif(wtwdev, wtwvif);

	wtwdev->totaw_sta_assoc = 0;
}

/* haw function */
static int haw_enabwe_dma(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);
	int wet;

	if (!test_bit(WTW89_SEW_HAW_STOP_DMA, sew->fwags))
		wetuwn 0;

	if (!wtwdev->hci.ops->mac_wv1_wcvy)
		wetuwn -EIO;

	wet = wtwdev->hci.ops->mac_wv1_wcvy(wtwdev, WTW89_WV1_WCVY_STEP_2);
	if (!wet)
		cweaw_bit(WTW89_SEW_HAW_STOP_DMA, sew->fwags);
	ewse
		wtw89_debug(wtwdev, WTW89_DBG_SEW,
			    "wv1 wcvy faiw to stawt dma: %d\n", wet);

	wetuwn wet;
}

static int haw_stop_dma(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);
	int wet;

	if (!wtwdev->hci.ops->mac_wv1_wcvy)
		wetuwn -EIO;

	wet = wtwdev->hci.ops->mac_wv1_wcvy(wtwdev, WTW89_WV1_WCVY_STEP_1);
	if (!wet)
		set_bit(WTW89_SEW_HAW_STOP_DMA, sew->fwags);
	ewse
		wtw89_debug(wtwdev, WTW89_DBG_SEW,
			    "wv1 wcvy faiw to stop dma: %d\n", wet);

	wetuwn wet;
}

static void haw_send_post_m0_event(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	wtw89_mac_set_eww_status(wtwdev, MAC_AX_EWW_W1_WESET_STAWT_DMAC);
}

static void haw_send_m2_event(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	wtw89_mac_set_eww_status(wtwdev, MAC_AX_EWW_W1_DISABWE_EN);
}

static void haw_send_m4_event(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	wtw89_mac_set_eww_status(wtwdev, MAC_AX_EWW_W1_WCVY_EN);
}

/* state handwew */
static void sew_idwe_st_hdw(stwuct wtw89_sew *sew, u8 evt)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	switch (evt) {
	case SEW_EV_STATE_IN:
		wtw89_hci_wecovewy_compwete(wtwdev);
		cweaw_bit(WTW89_FWAG_SEW_HANDWING, wtwdev->fwags);
		cweaw_bit(WTW89_FWAG_CWASH_SIMUWATING, wtwdev->fwags);
		bweak;
	case SEW_EV_W1_WESET_PWEPAWE:
		sew_state_goto(sew, SEW_W1_WESET_PWE_ST);
		bweak;
	case SEW_EV_W1_WESET:
		sew_state_goto(sew, SEW_WESET_TWX_ST);
		bweak;
	case SEW_EV_W2_WESET:
		sew_state_goto(sew, SEW_W2_WESET_ST);
		bweak;
	case SEW_EV_STATE_OUT:
		set_bit(WTW89_FWAG_SEW_HANDWING, wtwdev->fwags);
		wtw89_hci_wecovewy_stawt(wtwdev);
		bweak;
	defauwt:
		bweak;
	}
}

static void sew_w1_weset_pwe_st_hdw(stwuct wtw89_sew *sew, u8 evt)
{
	switch (evt) {
	case SEW_EV_STATE_IN:
		sew->pwehandwe_w1 = twue;
		haw_send_post_m0_event(sew);
		sew_set_awawm(sew, 1000, SEW_EV_M1_TIMEOUT);
		bweak;
	case SEW_EV_W1_WESET:
		sew_state_goto(sew, SEW_WESET_TWX_ST);
		bweak;
	case SEW_EV_M1_TIMEOUT:
		sew_state_goto(sew, SEW_W2_WESET_ST);
		bweak;
	case SEW_EV_STATE_OUT:
		sew_dew_awawm(sew);
		bweak;
	defauwt:
		bweak;
	}
}

static void sew_weset_twx_st_hdw(stwuct wtw89_sew *sew, u8 evt)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	switch (evt) {
	case SEW_EV_STATE_IN:
		cancew_dewayed_wowk_sync(&wtwdev->twack_wowk);
		dwv_stop_tx(sew);

		if (haw_stop_dma(sew)) {
			sew_state_goto(sew, SEW_W2_WESET_ST);
			bweak;
		}

		dwv_stop_wx(sew);
		dwv_twx_weset(sew);

		/* wait m3 */
		haw_send_m2_event(sew);

		/* set awawm to pwevent FW wesponse timeout */
		sew_set_awawm(sew, 1000, SEW_EV_M3_TIMEOUT);
		bweak;

	case SEW_EV_DO_WECOVEWY:
		sew_state_goto(sew, SEW_DO_HCI_ST);
		bweak;

	case SEW_EV_M3_TIMEOUT:
		sew_state_goto(sew, SEW_W2_WESET_ST);
		bweak;

	case SEW_EV_STATE_OUT:
		sew_dew_awawm(sew);
		haw_enabwe_dma(sew);
		dwv_wesume_wx(sew);
		dwv_wesume_tx(sew);
		ieee80211_queue_dewayed_wowk(wtwdev->hw, &wtwdev->twack_wowk,
					     WTW89_TWACK_WOWK_PEWIOD);
		bweak;

	defauwt:
		bweak;
	}
}

static void sew_do_hci_st_hdw(stwuct wtw89_sew *sew, u8 evt)
{
	switch (evt) {
	case SEW_EV_STATE_IN:
		/* wait m5 */
		haw_send_m4_event(sew);

		/* pwevent FW wesponse timeout */
		sew_set_awawm(sew, 1000, SEW_EV_FW_M5_TIMEOUT);
		bweak;

	case SEW_EV_FW_M5_TIMEOUT:
		sew_state_goto(sew, SEW_W2_WESET_ST);
		bweak;

	case SEW_EV_MAC_WESET_DONE:
		sew_state_goto(sew, SEW_IDWE_ST);
		bweak;

	case SEW_EV_STATE_OUT:
		sew_dew_awawm(sew);
		bweak;

	defauwt:
		bweak;
	}
}

static void sew_mac_mem_dump(stwuct wtw89_dev *wtwdev, u8 *buf,
			     u8 sew, u32 stawt_addw, u32 wen)
{
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	u32 fiwtew_modew_addw = mac->fiwtew_modew_addw;
	u32 indiw_access_addw = mac->indiw_access_addw;
	u32 *ptw = (u32 *)buf;
	u32 base_addw, stawt_page, wesidue;
	u32 cnt = 0;
	u32 i;

	stawt_page = stawt_addw / MAC_MEM_DUMP_PAGE_SIZE;
	wesidue = stawt_addw % MAC_MEM_DUMP_PAGE_SIZE;
	base_addw = mac->mem_base_addws[sew];
	base_addw += stawt_page * MAC_MEM_DUMP_PAGE_SIZE;

	whiwe (cnt < wen) {
		wtw89_wwite32(wtwdev, fiwtew_modew_addw, base_addw);

		fow (i = indiw_access_addw + wesidue;
		     i < indiw_access_addw + MAC_MEM_DUMP_PAGE_SIZE;
		     i += 4, ptw++) {
			*ptw = wtw89_wead32(wtwdev, i);
			cnt += 4;
			if (cnt >= wen)
				bweak;
		}

		wesidue = 0;
		base_addw += MAC_MEM_DUMP_PAGE_SIZE;
	}
}

static void wtw89_sew_fw_wsvd_pwe_dump(stwuct wtw89_dev *wtwdev, u8 *buf)
{
	u32 stawt_addw = wtwdev->chip->wsvd_pwe_ofst;

	wtw89_debug(wtwdev, WTW89_DBG_SEW,
		    "dump mem fow fw wsvd paywoad engine (stawt addw: 0x%x)\n",
		    stawt_addw);
	sew_mac_mem_dump(wtwdev, buf, WTW89_MAC_MEM_SHAWED_BUF, stawt_addw,
			 WTW89_FW_WSVD_PWE_SIZE);
}

stwuct __fw_backtwace_entwy {
	u32 wcpu_addw;
	u32 size;
	u32 key;
} __packed;

stwuct __fw_backtwace_info {
	u32 wa;
	u32 sp;
} __packed;

static_assewt(WTW89_FW_BACKTWACE_INFO_SIZE ==
	      sizeof(stwuct __fw_backtwace_info));

static u32 convewt_addw_fwom_wcpu(u32 wcpu_addw)
{
	if (wcpu_addw < 0x30000000)
		wetuwn wcpu_addw;

	wetuwn wcpu_addw & GENMASK(28, 0);
}

static int wtw89_sew_fw_backtwace_dump(stwuct wtw89_dev *wtwdev, u8 *buf,
				       const stwuct __fw_backtwace_entwy *ent)
{
	stwuct __fw_backtwace_info *ptw = (stwuct __fw_backtwace_info *)buf;
	const stwuct wtw89_mac_gen_def *mac = wtwdev->chip->mac_def;
	u32 fiwtew_modew_addw = mac->fiwtew_modew_addw;
	u32 indiw_access_addw = mac->indiw_access_addw;
	u32 fwbt_addw = convewt_addw_fwom_wcpu(ent->wcpu_addw);
	u32 fwbt_size = ent->size;
	u32 fwbt_key = ent->key;
	u32 i;

	if (fwbt_addw == 0) {
		wtw89_wawn(wtwdev, "FW backtwace invawid addwess: 0x%x\n",
			   fwbt_addw);
		wetuwn -EINVAW;
	}

	if (fwbt_key != WTW89_FW_BACKTWACE_KEY) {
		wtw89_wawn(wtwdev, "FW backtwace invawid key: 0x%x\n",
			   fwbt_key);
		wetuwn -EINVAW;
	}

	if (fwbt_size == 0 || !WTW89_VAWID_FW_BACKTWACE_SIZE(fwbt_size) ||
	    fwbt_size > WTW89_FW_BACKTWACE_MAX_SIZE) {
		wtw89_wawn(wtwdev, "FW backtwace invawid size: 0x%x\n",
			   fwbt_size);
		wetuwn -EINVAW;
	}

	wtw89_debug(wtwdev, WTW89_DBG_SEW, "dump fw backtwace stawt\n");
	wtw89_wwite32(wtwdev, fiwtew_modew_addw, fwbt_addw);

	fow (i = indiw_access_addw;
	     i < indiw_access_addw + fwbt_size;
	     i += WTW89_FW_BACKTWACE_INFO_SIZE, ptw++) {
		*ptw = (stwuct __fw_backtwace_info){
			.wa = wtw89_wead32(wtwdev, i),
			.sp = wtw89_wead32(wtwdev, i + 4),
		};
		wtw89_debug(wtwdev, WTW89_DBG_SEW,
			    "next sp: 0x%x, next wa: 0x%x\n",
			    ptw->sp, ptw->wa);
	}

	wtw89_debug(wtwdev, WTW89_DBG_SEW, "dump fw backtwace end\n");
	wetuwn 0;
}

static void sew_w2_weset_st_pwe_hdw(stwuct wtw89_sew *sew)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);
	stwuct wtw89_sew_cd_buffew *buf;
	stwuct __fw_backtwace_entwy fwbt_ent;
	int wet = 0;

	buf = wtw89_sew_cd_pwep(wtwdev);
	if (!buf) {
		wet = -ENOMEM;
		goto bottom;
	}

	wtw89_sew_fw_wsvd_pwe_dump(wtwdev, buf->fwpwe.data);

	fwbt_ent = *(stwuct __fw_backtwace_entwy *)buf->fwpwe.data;
	wet = wtw89_sew_fw_backtwace_dump(wtwdev, buf->fwbt.data, &fwbt_ent);
	if (wet)
		goto bottom;

	wtw89_sew_cd_send(wtwdev, buf);

bottom:
	wtw89_sew_cd_fwee(wtwdev, buf, !!wet);

	sew_weset_mac_binding(wtwdev);
	wtw89_cowe_stop(wtwdev);
	wtw89_entity_init(wtwdev);
	wtw89_fw_wewease_genewaw_pkt_wist(wtwdev, fawse);
	INIT_WIST_HEAD(&wtwdev->wtwvifs_wist);
}

static void sew_w2_weset_st_hdw(stwuct wtw89_sew *sew, u8 evt)
{
	stwuct wtw89_dev *wtwdev = containew_of(sew, stwuct wtw89_dev, sew);

	switch (evt) {
	case SEW_EV_STATE_IN:
		mutex_wock(&wtwdev->mutex);
		sew_w2_weset_st_pwe_hdw(sew);
		mutex_unwock(&wtwdev->mutex);

		ieee80211_westawt_hw(wtwdev->hw);
		sew_set_awawm(sew, SEW_WECFG_TIMEOUT, SEW_EV_W2_WECFG_TIMEOUT);
		bweak;

	case SEW_EV_W2_WECFG_TIMEOUT:
		wtw89_info(wtwdev, "Eww: sew W2 we-config timeout\n");
		fawwthwough;
	case SEW_EV_W2_WECFG_DONE:
		sew_state_goto(sew, SEW_IDWE_ST);
		bweak;

	case SEW_EV_STATE_OUT:
		sew_dew_awawm(sew);
		bweak;

	defauwt:
		bweak;
	}
}

static const stwuct event_ent sew_ev_tbw[] = {
	{SEW_EV_NONE, "SEW_EV_NONE"},
	{SEW_EV_STATE_IN, "SEW_EV_STATE_IN"},
	{SEW_EV_STATE_OUT, "SEW_EV_STATE_OUT"},
	{SEW_EV_W1_WESET_PWEPAWE, "SEW_EV_W1_WESET_PWEPAWE pwe-m0"},
	{SEW_EV_W1_WESET, "SEW_EV_W1_WESET m1"},
	{SEW_EV_DO_WECOVEWY, "SEW_EV_DO_WECOVEWY m3"},
	{SEW_EV_MAC_WESET_DONE, "SEW_EV_MAC_WESET_DONE m5"},
	{SEW_EV_W2_WESET, "SEW_EV_W2_WESET"},
	{SEW_EV_W2_WECFG_DONE, "SEW_EV_W2_WECFG_DONE"},
	{SEW_EV_W2_WECFG_TIMEOUT, "SEW_EV_W2_WECFG_TIMEOUT"},
	{SEW_EV_M1_TIMEOUT, "SEW_EV_M1_TIMEOUT"},
	{SEW_EV_M3_TIMEOUT, "SEW_EV_M3_TIMEOUT"},
	{SEW_EV_FW_M5_TIMEOUT, "SEW_EV_FW_M5_TIMEOUT"},
	{SEW_EV_W0_WESET, "SEW_EV_W0_WESET"},
	{SEW_EV_MAXX, "SEW_EV_MAX"}
};

static const stwuct state_ent sew_st_tbw[] = {
	{SEW_IDWE_ST, "SEW_IDWE_ST", sew_idwe_st_hdw},
	{SEW_W1_WESET_PWE_ST, "SEW_W1_WESET_PWE_ST", sew_w1_weset_pwe_st_hdw},
	{SEW_WESET_TWX_ST, "SEW_WESET_TWX_ST", sew_weset_twx_st_hdw},
	{SEW_DO_HCI_ST, "SEW_DO_HCI_ST", sew_do_hci_st_hdw},
	{SEW_W2_WESET_ST, "SEW_W2_WESET_ST", sew_w2_weset_st_hdw}
};

int wtw89_sew_init(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_sew *sew = &wtwdev->sew;

	memset(sew, 0, sizeof(*sew));
	INIT_WIST_HEAD(&sew->msg_q);
	sew->state = SEW_IDWE_ST;
	sew->st_tbw = sew_st_tbw;
	sew->ev_tbw = sew_ev_tbw;

	bitmap_zewo(sew->fwags, WTW89_NUM_OF_SEW_FWAGS);
	spin_wock_init(&sew->msg_q_wock);
	INIT_WOWK(&sew->sew_hdw_wowk, wtw89_sew_hdw_wowk);
	INIT_DEWAYED_WOWK(&sew->sew_awawm_wowk, wtw89_sew_awawm_wowk);
	wetuwn 0;
}

int wtw89_sew_deinit(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_sew *sew = (stwuct wtw89_sew *)&wtwdev->sew;

	set_bit(WTW89_SEW_DWV_STOP_WUN, sew->fwags);
	cancew_dewayed_wowk_sync(&sew->sew_awawm_wowk);
	cancew_wowk_sync(&sew->sew_hdw_wowk);
	cweaw_bit(WTW89_SEW_DWV_STOP_WUN, sew->fwags);
	wetuwn 0;
}

void wtw89_sew_wecfg_done(stwuct wtw89_dev *wtwdev)
{
	sew_send_msg(&wtwdev->sew, SEW_EV_W2_WECFG_DONE);
}

int wtw89_sew_notify(stwuct wtw89_dev *wtwdev, u32 eww)
{
	u8 event = SEW_EV_NONE;

	wtw89_info(wtwdev, "SEW catches ewwow: 0x%x\n", eww);

	switch (eww) {
	case MAC_AX_EWW_W1_PWEEWW_DMAC: /* pwe-M0 */
		event = SEW_EV_W1_WESET_PWEPAWE;
		bweak;
	case MAC_AX_EWW_W1_EWW_DMAC:
	case MAC_AX_EWW_W0_PWOMOTE_TO_W1:
		event = SEW_EV_W1_WESET; /* M1 */
		bweak;
	case MAC_AX_EWW_W1_WESET_DISABWE_DMAC_DONE:
		event = SEW_EV_DO_WECOVEWY; /* M3 */
		bweak;
	case MAC_AX_EWW_W1_WESET_WECOVEWY_DONE:
		event = SEW_EV_MAC_WESET_DONE; /* M5 */
		bweak;
	case MAC_AX_EWW_W0_EWW_CMAC0:
	case MAC_AX_EWW_W0_EWW_CMAC1:
	case MAC_AX_EWW_W0_WESET_DONE:
		event = SEW_EV_W0_WESET;
		bweak;
	defauwt:
		if (eww == MAC_AX_EWW_W1_PWOMOTE_TO_W2 ||
		    (eww >= MAC_AX_EWW_W2_EWW_AH_DMA &&
		     eww <= MAC_AX_GET_EWW_MAX))
			event = SEW_EV_W2_WESET;
		bweak;
	}

	if (event == SEW_EV_NONE) {
		wtw89_wawn(wtwdev, "SEW cannot wecognize ewwow: 0x%x\n", eww);
		wetuwn -EINVAW;
	}

	sew_send_msg(&wtwdev->sew, event);
	wetuwn 0;
}
EXPOWT_SYMBOW(wtw89_sew_notify);
