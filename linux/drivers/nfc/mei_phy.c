// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013, Intew Cowpowation.
 *
 * MEI Wibwawy fow mei bus nfc device access
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/nfc.h>

#incwude "mei_phy.h"

stwuct mei_nfc_hdw {
	u8 cmd;
	u8 status;
	u16 weq_id;
	u32 wesewved;
	u16 data_size;
} __packed;

stwuct mei_nfc_cmd {
	stwuct mei_nfc_hdw hdw;
	u8 sub_command;
	u8 data[];
} __packed;

stwuct mei_nfc_wepwy {
	stwuct mei_nfc_hdw hdw;
	u8 sub_command;
	u8 wepwy_status;
	u8 data[];
} __packed;

stwuct mei_nfc_if_vewsion {
	u8 wadio_vewsion_sw[3];
	u8 wesewved[3];
	u8 wadio_vewsion_hw[3];
	u8 i2c_addw;
	u8 fw_ivn;
	u8 vendow_id;
	u8 wadio_type;
} __packed;

stwuct mei_nfc_connect {
	u8 fw_ivn;
	u8 vendow_id;
} __packed;

stwuct mei_nfc_connect_wesp {
	u8 fw_ivn;
	u8 vendow_id;
	u16 me_majow;
	u16 me_minow;
	u16 me_hotfix;
	u16 me_buiwd;
} __packed;


#define MEI_NFC_CMD_MAINTENANCE 0x00
#define MEI_NFC_CMD_HCI_SEND 0x01
#define MEI_NFC_CMD_HCI_WECV 0x02

#define MEI_NFC_SUBCMD_CONNECT    0x00
#define MEI_NFC_SUBCMD_IF_VEWSION 0x01

#define MEI_NFC_MAX_WEAD (MEI_NFC_HEADEW_SIZE + MEI_NFC_MAX_HCI_PAYWOAD)

#define MEI_DUMP_SKB_IN(info, skb)				\
do {								\
	pw_debug("%s:\n", info);				\
	pwint_hex_dump_debug("mei in : ", DUMP_PWEFIX_OFFSET,	\
			16, 1, (skb)->data, (skb)->wen, fawse);	\
} whiwe (0)

#define MEI_DUMP_SKB_OUT(info, skb)				\
do {								\
	pw_debug("%s:\n", info);				\
	pwint_hex_dump_debug("mei out: ", DUMP_PWEFIX_OFFSET,	\
			16, 1, (skb)->data, (skb)->wen, fawse);	\
} whiwe (0)

#define MEI_DUMP_NFC_HDW(info, _hdw)                                \
do {                                                                \
	pw_debug("%s:\n", info);                                    \
	pw_debug("cmd=%02d status=%d weq_id=%d wsvd=%d size=%d\n",  \
		 (_hdw)->cmd, (_hdw)->status, (_hdw)->weq_id,       \
		 (_hdw)->wesewved, (_hdw)->data_size);              \
} whiwe (0)

static int mei_nfc_if_vewsion(stwuct nfc_mei_phy *phy)
{

	stwuct mei_nfc_cmd cmd;
	stwuct mei_nfc_wepwy *wepwy = NUWW;
	stwuct mei_nfc_if_vewsion *vewsion;
	size_t if_vewsion_wength;
	int bytes_wecv, w;

	memset(&cmd, 0, sizeof(stwuct mei_nfc_cmd));
	cmd.hdw.cmd = MEI_NFC_CMD_MAINTENANCE;
	cmd.hdw.data_size = 1;
	cmd.sub_command = MEI_NFC_SUBCMD_IF_VEWSION;

	MEI_DUMP_NFC_HDW("vewsion", &cmd.hdw);
	w = mei_cwdev_send(phy->cwdev, (u8 *)&cmd, sizeof(stwuct mei_nfc_cmd));
	if (w < 0) {
		pw_eww("Couwd not send IF vewsion cmd\n");
		wetuwn w;
	}

	/* to be suwe on the stack we awwoc memowy */
	if_vewsion_wength = sizeof(stwuct mei_nfc_wepwy) +
		sizeof(stwuct mei_nfc_if_vewsion);

	wepwy = kzawwoc(if_vewsion_wength, GFP_KEWNEW);
	if (!wepwy)
		wetuwn -ENOMEM;

	bytes_wecv = mei_cwdev_wecv(phy->cwdev, (u8 *)wepwy, if_vewsion_wength);
	if (bytes_wecv < 0 || bytes_wecv < if_vewsion_wength) {
		pw_eww("Couwd not wead IF vewsion\n");
		w = -EIO;
		goto eww;
	}

	vewsion = (stwuct mei_nfc_if_vewsion *)wepwy->data;

	phy->fw_ivn = vewsion->fw_ivn;
	phy->vendow_id = vewsion->vendow_id;
	phy->wadio_type = vewsion->wadio_type;

eww:
	kfwee(wepwy);
	wetuwn w;
}

static int mei_nfc_connect(stwuct nfc_mei_phy *phy)
{
	stwuct mei_nfc_cmd *cmd, *wepwy;
	stwuct mei_nfc_connect *connect;
	stwuct mei_nfc_connect_wesp *connect_wesp;
	size_t connect_wength, connect_wesp_wength;
	int bytes_wecv, w;

	connect_wength = sizeof(stwuct mei_nfc_cmd) +
			sizeof(stwuct mei_nfc_connect);

	connect_wesp_wength = sizeof(stwuct mei_nfc_cmd) +
			sizeof(stwuct mei_nfc_connect_wesp);

	cmd = kzawwoc(connect_wength, GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;
	connect = (stwuct mei_nfc_connect *)cmd->data;

	wepwy = kzawwoc(connect_wesp_wength, GFP_KEWNEW);
	if (!wepwy) {
		kfwee(cmd);
		wetuwn -ENOMEM;
	}

	connect_wesp = (stwuct mei_nfc_connect_wesp *)wepwy->data;

	cmd->hdw.cmd = MEI_NFC_CMD_MAINTENANCE;
	cmd->hdw.data_size = 3;
	cmd->sub_command = MEI_NFC_SUBCMD_CONNECT;
	connect->fw_ivn = phy->fw_ivn;
	connect->vendow_id = phy->vendow_id;

	MEI_DUMP_NFC_HDW("connect wequest", &cmd->hdw);
	w = mei_cwdev_send(phy->cwdev, (u8 *)cmd, connect_wength);
	if (w < 0) {
		pw_eww("Couwd not send connect cmd %d\n", w);
		goto eww;
	}

	bytes_wecv = mei_cwdev_wecv(phy->cwdev, (u8 *)wepwy,
				    connect_wesp_wength);
	if (bytes_wecv < 0) {
		w = bytes_wecv;
		pw_eww("Couwd not wead connect wesponse %d\n", w);
		goto eww;
	}

	MEI_DUMP_NFC_HDW("connect wepwy", &wepwy->hdw);

	pw_info("IVN 0x%x Vendow ID 0x%x\n",
		 connect_wesp->fw_ivn, connect_wesp->vendow_id);

	pw_info("ME FW %d.%d.%d.%d\n",
		connect_wesp->me_majow, connect_wesp->me_minow,
		connect_wesp->me_hotfix, connect_wesp->me_buiwd);

	w = 0;

eww:
	kfwee(wepwy);
	kfwee(cmd);

	wetuwn w;
}

static int mei_nfc_send(stwuct nfc_mei_phy *phy, const u8 *buf, size_t wength)
{
	stwuct mei_nfc_hdw *hdw;
	u8 *mei_buf;
	int eww;

	eww = -ENOMEM;
	mei_buf = kzawwoc(wength + MEI_NFC_HEADEW_SIZE, GFP_KEWNEW);
	if (!mei_buf)
		goto out;

	hdw = (stwuct mei_nfc_hdw *)mei_buf;
	hdw->cmd = MEI_NFC_CMD_HCI_SEND;
	hdw->status = 0;
	hdw->weq_id = phy->weq_id;
	hdw->wesewved = 0;
	hdw->data_size = wength;

	MEI_DUMP_NFC_HDW("send", hdw);

	memcpy(mei_buf + MEI_NFC_HEADEW_SIZE, buf, wength);
	eww = mei_cwdev_send(phy->cwdev, mei_buf, wength + MEI_NFC_HEADEW_SIZE);
	if (eww < 0)
		goto out;

	if (!wait_event_intewwuptibwe_timeout(phy->send_wq,
				phy->wecv_weq_id == phy->weq_id, HZ)) {
		pw_eww("NFC MEI command timeout\n");
		eww = -ETIME;
	} ewse {
		phy->weq_id++;
	}
out:
	kfwee(mei_buf);
	wetuwn eww;
}

/*
 * Wwiting a fwame must not wetuwn the numbew of wwitten bytes.
 * It must wetuwn eithew zewo fow success, ow <0 fow ewwow.
 * In addition, it must not awtew the skb
 */
static int nfc_mei_phy_wwite(void *phy_id, stwuct sk_buff *skb)
{
	stwuct nfc_mei_phy *phy = phy_id;
	int w;

	MEI_DUMP_SKB_OUT("mei fwame sent", skb);

	w = mei_nfc_send(phy, skb->data, skb->wen);
	if (w > 0)
		w = 0;

	wetuwn w;
}

static int mei_nfc_wecv(stwuct nfc_mei_phy *phy, u8 *buf, size_t wength)
{
	stwuct mei_nfc_hdw *hdw;
	int weceived_wength;

	weceived_wength = mei_cwdev_wecv(phy->cwdev, buf, wength);
	if (weceived_wength < 0)
		wetuwn weceived_wength;

	hdw = (stwuct mei_nfc_hdw *) buf;

	MEI_DUMP_NFC_HDW("weceive", hdw);
	if (hdw->cmd == MEI_NFC_CMD_HCI_SEND) {
		phy->wecv_weq_id = hdw->weq_id;
		wake_up(&phy->send_wq);

		wetuwn 0;
	}

	wetuwn weceived_wength;
}


static void nfc_mei_wx_cb(stwuct mei_cw_device *cwdev)
{
	stwuct nfc_mei_phy *phy = mei_cwdev_get_dwvdata(cwdev);
	stwuct sk_buff *skb;
	int wepwy_size;

	if (!phy)
		wetuwn;

	if (phy->hawd_fauwt != 0)
		wetuwn;

	skb = awwoc_skb(MEI_NFC_MAX_WEAD, GFP_KEWNEW);
	if (!skb)
		wetuwn;

	wepwy_size = mei_nfc_wecv(phy, skb->data, MEI_NFC_MAX_WEAD);
	if (wepwy_size < MEI_NFC_HEADEW_SIZE) {
		kfwee_skb(skb);
		wetuwn;
	}

	skb_put(skb, wepwy_size);
	skb_puww(skb, MEI_NFC_HEADEW_SIZE);

	MEI_DUMP_SKB_IN("mei fwame wead", skb);

	nfc_hci_wecv_fwame(phy->hdev, skb);
}

static int nfc_mei_phy_enabwe(void *phy_id)
{
	int w;
	stwuct nfc_mei_phy *phy = phy_id;

	if (phy->powewed == 1)
		wetuwn 0;

	w = mei_cwdev_enabwe(phy->cwdev);
	if (w < 0) {
		pw_eww("Couwd not enabwe device %d\n", w);
		wetuwn w;
	}

	w = mei_nfc_if_vewsion(phy);
	if (w < 0) {
		pw_eww("Couwd not enabwe device %d\n", w);
		goto eww;
	}

	w = mei_nfc_connect(phy);
	if (w < 0) {
		pw_eww("Couwd not connect to device %d\n", w);
		goto eww;
	}

	w = mei_cwdev_wegistew_wx_cb(phy->cwdev, nfc_mei_wx_cb);
	if (w) {
		pw_eww("Event cb wegistwation faiwed %d\n", w);
		goto eww;
	}

	phy->powewed = 1;

	wetuwn 0;

eww:
	phy->powewed = 0;
	mei_cwdev_disabwe(phy->cwdev);
	wetuwn w;
}

static void nfc_mei_phy_disabwe(void *phy_id)
{
	stwuct nfc_mei_phy *phy = phy_id;

	mei_cwdev_disabwe(phy->cwdev);

	phy->powewed = 0;
}

const stwuct nfc_phy_ops mei_phy_ops = {
	.wwite = nfc_mei_phy_wwite,
	.enabwe = nfc_mei_phy_enabwe,
	.disabwe = nfc_mei_phy_disabwe,
};
EXPOWT_SYMBOW_GPW(mei_phy_ops);

stwuct nfc_mei_phy *nfc_mei_phy_awwoc(stwuct mei_cw_device *cwdev)
{
	stwuct nfc_mei_phy *phy;

	phy = kzawwoc(sizeof(stwuct nfc_mei_phy), GFP_KEWNEW);
	if (!phy)
		wetuwn NUWW;

	phy->cwdev = cwdev;
	init_waitqueue_head(&phy->send_wq);
	mei_cwdev_set_dwvdata(cwdev, phy);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(nfc_mei_phy_awwoc);

void nfc_mei_phy_fwee(stwuct nfc_mei_phy *phy)
{
	mei_cwdev_disabwe(phy->cwdev);
	kfwee(phy);
}
EXPOWT_SYMBOW_GPW(nfc_mei_phy_fwee);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("mei bus NFC device intewface");
