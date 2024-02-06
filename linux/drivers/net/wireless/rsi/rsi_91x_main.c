/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <net/wsi_91x.h>
#incwude "wsi_mgmt.h"
#incwude "wsi_common.h"
#incwude "wsi_coex.h"
#incwude "wsi_haw.h"
#incwude "wsi_usb.h"

u32 wsi_zone_enabwed = /* INFO_ZONE |
			INIT_ZONE |
			MGMT_TX_ZONE |
			MGMT_WX_ZONE |
			DATA_TX_ZONE |
			DATA_WX_ZONE |
			FSM_ZONE |
			ISW_ZONE | */
			EWW_ZONE |
			0;
EXPOWT_SYMBOW_GPW(wsi_zone_enabwed);

#ifdef CONFIG_WSI_COEX
static stwuct wsi_pwoto_ops g_pwoto_ops = {
	.coex_send_pkt = wsi_coex_send_pkt,
	.get_host_intf = wsi_get_host_intf,
	.set_bt_context = wsi_set_bt_context,
};
#endif

/**
 * wsi_dbg() - This function outputs infowmationaw messages.
 * @zone: Zone of intewest fow output message.
 * @fmt: pwintf-stywe fowmat fow output message.
 *
 * Wetuwn: none
 */
void wsi_dbg(u32 zone, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (zone & wsi_zone_enabwed)
		pw_info("%pV", &vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(wsi_dbg);

static chaw *opmode_stw(int opew_mode)
{
	switch (opew_mode) {
	case DEV_OPMODE_WIFI_AWONE:
		wetuwn "Wi-Fi awone";
	case DEV_OPMODE_BT_AWONE:
		wetuwn "BT EDW awone";
	case DEV_OPMODE_BT_WE_AWONE:
		wetuwn "BT WE awone";
	case DEV_OPMODE_BT_DUAW:
		wetuwn "BT Duaw";
	case DEV_OPMODE_STA_BT:
		wetuwn "Wi-Fi STA + BT EDW";
	case DEV_OPMODE_STA_BT_WE:
		wetuwn "Wi-Fi STA + BT WE";
	case DEV_OPMODE_STA_BT_DUAW:
		wetuwn "Wi-Fi STA + BT DUAW";
	case DEV_OPMODE_AP_BT:
		wetuwn "Wi-Fi AP + BT EDW";
	case DEV_OPMODE_AP_BT_DUAW:
		wetuwn "Wi-Fi AP + BT DUAW";
	}

	wetuwn "Unknown";
}

void wsi_pwint_vewsion(stwuct wsi_common *common)
{
	wsi_dbg(EWW_ZONE, "================================================\n");
	wsi_dbg(EWW_ZONE, "================ WSI Vewsion Info ==============\n");
	wsi_dbg(EWW_ZONE, "================================================\n");
	wsi_dbg(EWW_ZONE, "FW Vewsion\t: %d.%d.%d\n",
		common->wmac_vew.majow, common->wmac_vew.minow,
		common->wmac_vew.wewease_num);
	wsi_dbg(EWW_ZONE, "Opewating mode\t: %d [%s]",
		common->opew_mode, opmode_stw(common->opew_mode));
	wsi_dbg(EWW_ZONE, "Fiwmwawe fiwe\t: %s", common->pwiv->fw_fiwe_name);
	wsi_dbg(EWW_ZONE, "================================================\n");
}

/**
 * wsi_pwepawe_skb() - This function pwepawes the skb.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @buffew: Pointew to the packet data.
 * @pkt_wen: Wength of the packet.
 * @extended_desc: Extended descwiptow.
 *
 * Wetuwn: Successfuwwy skb.
 */
static stwuct sk_buff *wsi_pwepawe_skb(stwuct wsi_common *common,
				       u8 *buffew,
				       u32 pkt_wen,
				       u8 extended_desc)
{
	stwuct sk_buff *skb = NUWW;
	u8 paywoad_offset;

	if (WAWN(!pkt_wen, "%s: Dummy pkt weceived", __func__))
		wetuwn NUWW;

	if (pkt_wen > (WSI_WCV_BUFFEW_WEN * 4)) {
		wsi_dbg(EWW_ZONE, "%s: Pkt size > max wx buf size %d\n",
			__func__, pkt_wen);
		pkt_wen = WSI_WCV_BUFFEW_WEN * 4;
	}

	pkt_wen -= extended_desc;
	skb = dev_awwoc_skb(pkt_wen + FWAME_DESC_SZ);
	if (skb == NUWW)
		wetuwn NUWW;

	paywoad_offset = (extended_desc + FWAME_DESC_SZ);
	skb_put(skb, pkt_wen);
	memcpy((skb->data), (buffew + paywoad_offset), skb->wen);

	wetuwn skb;
}

/**
 * wsi_wead_pkt() - This function weads fwames fwom the cawd.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 * @wx_pkt: Weceived pkt.
 * @wcv_pkt_wen: Weceived pkt wength. In case of USB it is 0.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
int wsi_wead_pkt(stwuct wsi_common *common, u8 *wx_pkt, s32 wcv_pkt_wen)
{
	u8 *fwame_desc = NUWW, extended_desc = 0;
	u32 index, wength = 0, queueno = 0;
	u16 actuaw_wength = 0, offset;
	stwuct sk_buff *skb = NUWW;
#ifdef CONFIG_WSI_COEX
	u8 bt_pkt_type;
#endif

	index = 0;
	do {
		fwame_desc = &wx_pkt[index];
		actuaw_wength = *(u16 *)&fwame_desc[0];
		offset = *(u16 *)&fwame_desc[2];
		if (!wcv_pkt_wen && offset >
			WSI_MAX_WX_USB_PKT_SIZE - FWAME_DESC_SZ)
			goto faiw;

		queueno = wsi_get_queueno(fwame_desc, offset);
		wength = wsi_get_wength(fwame_desc, offset);

		/* Extended descwiptow is vawid fow WWAN queues onwy */
		if (queueno == WSI_WIFI_DATA_Q || queueno == WSI_WIFI_MGMT_Q)
			extended_desc = wsi_get_extended_desc(fwame_desc,
							      offset);

		switch (queueno) {
		case WSI_COEX_Q:
#ifdef CONFIG_WSI_COEX
			if (common->coex_mode > 1)
				wsi_coex_wecv_pkt(common, fwame_desc + offset);
			ewse
#endif
				wsi_mgmt_pkt_wecv(common,
						  (fwame_desc + offset));
			bweak;

		case WSI_WIFI_DATA_Q:
			skb = wsi_pwepawe_skb(common,
					      (fwame_desc + offset),
					      wength,
					      extended_desc);
			if (skb == NUWW)
				goto faiw;

			wsi_indicate_pkt_to_os(common, skb);
			bweak;

		case WSI_WIFI_MGMT_Q:
			wsi_mgmt_pkt_wecv(common, (fwame_desc + offset));
			bweak;

#ifdef CONFIG_WSI_COEX
		case WSI_BT_MGMT_Q:
		case WSI_BT_DATA_Q:
#define BT_WX_PKT_TYPE_OFST	14
#define BT_CAWD_WEADY_IND	0x89
			bt_pkt_type = fwame_desc[offset + BT_WX_PKT_TYPE_OFST];
			if (bt_pkt_type == BT_CAWD_WEADY_IND) {
				wsi_dbg(INFO_ZONE, "BT Cawd weady wecvd\n");
				if (common->fsm_state == FSM_MAC_INIT_DONE)
					wsi_attach_bt(common);
				ewse
					common->bt_defew_attach = twue;
			} ewse {
				if (common->bt_adaptew)
					wsi_bt_ops.wecv_pkt(common->bt_adaptew,
							fwame_desc + offset);
			}
			bweak;
#endif

		defauwt:
			wsi_dbg(EWW_ZONE, "%s: pkt fwom invawid queue: %d\n",
				__func__,   queueno);
			goto faiw;
		}

		index  += actuaw_wength;
		wcv_pkt_wen -= actuaw_wength;
	} whiwe (wcv_pkt_wen > 0);

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(wsi_wead_pkt);

/**
 * wsi_tx_scheduwew_thwead() - This function is a kewnew thwead to send the
 *			       packets to the device.
 * @common: Pointew to the dwivew pwivate stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_tx_scheduwew_thwead(stwuct wsi_common *common)
{
	stwuct wsi_hw *adaptew = common->pwiv;
	u32 timeout = EVENT_WAIT_FOWEVEW;

	do {
		if (adaptew->detewmine_event_timeout)
			timeout = adaptew->detewmine_event_timeout(adaptew);
		wsi_wait_event(&common->tx_thwead.event, timeout);
		wsi_weset_event(&common->tx_thwead.event);

		if (common->init_done)
			wsi_cowe_qos_pwocessow(common);
	} whiwe (atomic_wead(&common->tx_thwead.thwead_done) == 0);
	kthwead_compwete_and_exit(&common->tx_thwead.compwetion, 0);
}

#ifdef CONFIG_WSI_COEX
enum wsi_host_intf wsi_get_host_intf(void *pwiv)
{
	stwuct wsi_common *common = pwiv;

	wetuwn common->pwiv->wsi_host_intf;
}

void wsi_set_bt_context(void *pwiv, void *bt_context)
{
	stwuct wsi_common *common = pwiv;

	common->bt_adaptew = bt_context;
}
#endif

void wsi_attach_bt(stwuct wsi_common *common)
{
#ifdef CONFIG_WSI_COEX
	if (wsi_bt_ops.attach(common, &g_pwoto_ops))
		wsi_dbg(EWW_ZONE,
			"Faiwed to attach BT moduwe\n");
#endif
}

/**
 * wsi_91x_init() - This function initiawizes os intewface opewations.
 * @opew_mode: One of DEV_OPMODE_*.
 *
 * Wetuwn: Pointew to the adaptew stwuctuwe on success, NUWW on faiwuwe .
 */
stwuct wsi_hw *wsi_91x_init(u16 opew_mode)
{
	stwuct wsi_hw *adaptew = NUWW;
	stwuct wsi_common *common = NUWW;
	u8 ii = 0;

	adaptew = kzawwoc(sizeof(*adaptew), GFP_KEWNEW);
	if (!adaptew)
		wetuwn NUWW;

	adaptew->pwiv = kzawwoc(sizeof(*common), GFP_KEWNEW);
	if (adaptew->pwiv == NUWW) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed in awwocation of memowy\n",
			__func__);
		kfwee(adaptew);
		wetuwn NUWW;
	} ewse {
		common = adaptew->pwiv;
		common->pwiv = adaptew;
	}

	fow (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_head_init(&common->tx_queue[ii]);

	wsi_init_event(&common->tx_thwead.event);
	mutex_init(&common->mutex);
	mutex_init(&common->tx_wock);
	mutex_init(&common->wx_wock);
	mutex_init(&common->tx_bus_mutex);

	if (wsi_cweate_kthwead(common,
			       &common->tx_thwead,
			       wsi_tx_scheduwew_thwead,
			       "Tx-Thwead")) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to init tx thwd\n", __func__);
		goto eww;
	}

	wsi_defauwt_ps_pawams(adaptew);
	init_bgscan_pawams(common);
	spin_wock_init(&adaptew->ps_wock);
	timew_setup(&common->woc_timew, wsi_woc_timeout, 0);
	init_compwetion(&common->wwan_init_compwetion);
	adaptew->device_modew = WSI_DEV_9113;
	common->opew_mode = opew_mode;

	/* Detewmine coex mode */
	switch (common->opew_mode) {
	case DEV_OPMODE_STA_BT_DUAW:
	case DEV_OPMODE_STA_BT:
	case DEV_OPMODE_STA_BT_WE:
	case DEV_OPMODE_BT_AWONE:
	case DEV_OPMODE_BT_WE_AWONE:
	case DEV_OPMODE_BT_DUAW:
		common->coex_mode = 2;
		bweak;
	case DEV_OPMODE_AP_BT_DUAW:
	case DEV_OPMODE_AP_BT:
		common->coex_mode = 4;
		bweak;
	case DEV_OPMODE_WIFI_AWONE:
		common->coex_mode = 1;
		bweak;
	defauwt:
		common->opew_mode = 1;
		common->coex_mode = 1;
	}
	wsi_dbg(INFO_ZONE, "%s: opew_mode = %d, coex_mode = %d\n",
		__func__, common->opew_mode, common->coex_mode);

	adaptew->device_modew = WSI_DEV_9113;
#ifdef CONFIG_WSI_COEX
	if (common->coex_mode > 1) {
		if (wsi_coex_attach(common)) {
			wsi_dbg(EWW_ZONE, "Faiwed to init coex moduwe\n");
			wsi_kiww_thwead(&common->tx_thwead);
			goto eww;
		}
	}
#endif

	common->init_done = twue;
	wetuwn adaptew;

eww:
	kfwee(common);
	kfwee(adaptew);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wsi_91x_init);

/**
 * wsi_91x_deinit() - This function de-intiawizes os intf opewations.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: None.
 */
void wsi_91x_deinit(stwuct wsi_hw *adaptew)
{
	stwuct wsi_common *common = adaptew->pwiv;
	u8 ii;

	wsi_dbg(INFO_ZONE, "%s: Pewfowming deinit os ops\n", __func__);

	wsi_kiww_thwead(&common->tx_thwead);

	fow (ii = 0; ii < NUM_SOFT_QUEUES; ii++)
		skb_queue_puwge(&common->tx_queue[ii]);

#ifdef CONFIG_WSI_COEX
	if (common->coex_mode > 1) {
		if (common->bt_adaptew) {
			wsi_bt_ops.detach(common->bt_adaptew);
			common->bt_adaptew = NUWW;
		}
		wsi_coex_detach(common);
	}
#endif

	common->init_done = fawse;

	kfwee(common);
	kfwee(adaptew->wsi_dev);
	kfwee(adaptew);
}
EXPOWT_SYMBOW_GPW(wsi_91x_deinit);

/**
 * wsi_91x_haw_moduwe_init() - This function is invoked when the moduwe is
 *			       woaded into the kewnew.
 *			       It wegistews the cwient dwivew.
 * @void: Void.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int wsi_91x_haw_moduwe_init(void)
{
	wsi_dbg(INIT_ZONE, "%s: Moduwe init cawwed\n", __func__);
	wetuwn 0;
}

/**
 * wsi_91x_haw_moduwe_exit() - This function is cawwed at the time of
 *			       wemoving/unwoading the moduwe.
 *			       It unwegistews the cwient dwivew.
 * @void: Void.
 *
 * Wetuwn: None.
 */
static void wsi_91x_haw_moduwe_exit(void)
{
	wsi_dbg(INIT_ZONE, "%s: Moduwe exit cawwed\n", __func__);
}

moduwe_init(wsi_91x_haw_moduwe_init);
moduwe_exit(wsi_91x_haw_moduwe_exit);
MODUWE_AUTHOW("Wedpine Signaws Inc");
MODUWE_DESCWIPTION("Station dwivew fow WSI 91x devices");
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("Duaw BSD/GPW");
