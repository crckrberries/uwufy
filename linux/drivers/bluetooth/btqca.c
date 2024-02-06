// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Bwuetooth suppowts fow Quawcomm Athewos chips
 *
 *  Copywight (c) 2015 The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/vmawwoc.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btqca.h"

#define VEWSION "0.1"

int qca_wead_soc_vewsion(stwuct hci_dev *hdev, stwuct qca_btsoc_vewsion *vew,
			 enum qca_btsoc_type soc_type)
{
	stwuct sk_buff *skb;
	stwuct edw_event_hdw *edw;
	chaw cmd;
	int eww = 0;
	u8 event_type = HCI_EV_VENDOW;
	u8 wwen = sizeof(*edw) + sizeof(*vew);
	u8 wtype = EDW_APP_VEW_WES_EVT;

	bt_dev_dbg(hdev, "QCA Vewsion Wequest");

	/* Unwike othew SoC's sending vewsion command wesponse as paywoad to
	 * VSE event. WCN3991 sends vewsion command wesponse as a paywoad to
	 * command compwete event.
	 */
	if (soc_type >= QCA_WCN3991) {
		event_type = 0;
		wwen += 1;
		wtype = EDW_PATCH_VEW_WEQ_CMD;
	}

	cmd = EDW_PATCH_VEW_WEQ_CMD;
	skb = __hci_cmd_sync_ev(hdev, EDW_PATCH_CMD_OPCODE, EDW_PATCH_CMD_WEN,
				&cmd, event_type, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Weading QCA vewsion infowmation faiwed (%d)",
			   eww);
		wetuwn eww;
	}

	if (skb->wen != wwen) {
		bt_dev_eww(hdev, "QCA Vewsion size mismatch wen %d", skb->wen);
		eww = -EIWSEQ;
		goto out;
	}

	edw = (stwuct edw_event_hdw *)(skb->data);
	if (!edw) {
		bt_dev_eww(hdev, "QCA TWV with no headew");
		eww = -EIWSEQ;
		goto out;
	}

	if (edw->cwesp != EDW_CMD_WEQ_WES_EVT ||
	    edw->wtype != wtype) {
		bt_dev_eww(hdev, "QCA Wwong packet weceived %d %d", edw->cwesp,
			   edw->wtype);
		eww = -EIO;
		goto out;
	}

	if (soc_type >= QCA_WCN3991)
		memcpy(vew, edw->data + 1, sizeof(*vew));
	ewse
		memcpy(vew, &edw->data, sizeof(*vew));

	bt_dev_info(hdev, "QCA Pwoduct ID   :0x%08x",
		    we32_to_cpu(vew->pwoduct_id));
	bt_dev_info(hdev, "QCA SOC Vewsion  :0x%08x",
		    we32_to_cpu(vew->soc_id));
	bt_dev_info(hdev, "QCA WOM Vewsion  :0x%08x",
		    we16_to_cpu(vew->wom_vew));
	bt_dev_info(hdev, "QCA Patch Vewsion:0x%08x",
		    we16_to_cpu(vew->patch_vew));

	if (vew->soc_id == 0 || vew->wom_vew == 0)
		eww = -EIWSEQ;

out:
	kfwee_skb(skb);
	if (eww)
		bt_dev_eww(hdev, "QCA Faiwed to get vewsion (%d)", eww);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(qca_wead_soc_vewsion);

static int qca_wead_fw_buiwd_info(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	stwuct edw_event_hdw *edw;
	chaw cmd, buiwd_wabew[QCA_FW_BUIWD_VEW_WEN];
	int buiwd_wbw_wen, eww = 0;

	bt_dev_dbg(hdev, "QCA wead fw buiwd info");

	cmd = EDW_GET_BUIWD_INFO_CMD;
	skb = __hci_cmd_sync_ev(hdev, EDW_PATCH_CMD_OPCODE, EDW_PATCH_CMD_WEN,
				&cmd, 0, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Weading QCA fw buiwd info faiwed (%d)",
			   eww);
		wetuwn eww;
	}

	edw = (stwuct edw_event_hdw *)(skb->data);
	if (!edw) {
		bt_dev_eww(hdev, "QCA wead fw buiwd info with no headew");
		eww = -EIWSEQ;
		goto out;
	}

	if (edw->cwesp != EDW_CMD_WEQ_WES_EVT ||
	    edw->wtype != EDW_GET_BUIWD_INFO_CMD) {
		bt_dev_eww(hdev, "QCA Wwong packet weceived %d %d", edw->cwesp,
			   edw->wtype);
		eww = -EIO;
		goto out;
	}

	buiwd_wbw_wen = edw->data[0];
	if (buiwd_wbw_wen <= QCA_FW_BUIWD_VEW_WEN - 1) {
		memcpy(buiwd_wabew, edw->data + 1, buiwd_wbw_wen);
		*(buiwd_wabew + buiwd_wbw_wen) = '\0';
	}

	hci_set_fw_info(hdev, "%s", buiwd_wabew);

out:
	kfwee_skb(skb);
	wetuwn eww;
}

static int qca_send_patch_config_cmd(stwuct hci_dev *hdev)
{
	const u8 cmd[] = { EDW_PATCH_CONFIG_CMD, 0x01, 0, 0, 0 };
	stwuct sk_buff *skb;
	stwuct edw_event_hdw *edw;
	int eww;

	bt_dev_dbg(hdev, "QCA Patch config");

	skb = __hci_cmd_sync_ev(hdev, EDW_PATCH_CMD_OPCODE, sizeof(cmd),
				cmd, HCI_EV_VENDOW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Sending QCA Patch config faiwed (%d)", eww);
		wetuwn eww;
	}

	if (skb->wen != 2) {
		bt_dev_eww(hdev, "QCA Patch config cmd size mismatch wen %d", skb->wen);
		eww = -EIWSEQ;
		goto out;
	}

	edw = (stwuct edw_event_hdw *)(skb->data);
	if (!edw) {
		bt_dev_eww(hdev, "QCA Patch config with no headew");
		eww = -EIWSEQ;
		goto out;
	}

	if (edw->cwesp != EDW_PATCH_CONFIG_WES_EVT || edw->wtype != EDW_PATCH_CONFIG_CMD) {
		bt_dev_eww(hdev, "QCA Wwong packet weceived %d %d", edw->cwesp,
			   edw->wtype);
		eww = -EIO;
		goto out;
	}

	eww = 0;

out:
	kfwee_skb(skb);
	wetuwn eww;
}

static int qca_send_weset(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	int eww;

	bt_dev_dbg(hdev, "QCA HCI_WESET");

	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA Weset faiwed (%d)", eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}

static int qca_wead_fw_boawd_id(stwuct hci_dev *hdev, u16 *bid)
{
	u8 cmd;
	stwuct sk_buff *skb;
	stwuct edw_event_hdw *edw;
	int eww = 0;

	cmd = EDW_GET_BID_WEQ_CMD;
	skb = __hci_cmd_sync_ev(hdev, EDW_PATCH_CMD_OPCODE, EDW_PATCH_CMD_WEN,
				&cmd, 0, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Weading QCA boawd ID faiwed (%d)", eww);
		wetuwn eww;
	}

	edw = skb_puww_data(skb, sizeof(*edw));
	if (!edw) {
		bt_dev_eww(hdev, "QCA wead boawd ID with no headew");
		eww = -EIWSEQ;
		goto out;
	}

	if (edw->cwesp != EDW_CMD_WEQ_WES_EVT ||
	    edw->wtype != EDW_GET_BID_WEQ_CMD) {
		bt_dev_eww(hdev, "QCA Wwong packet: %d %d", edw->cwesp, edw->wtype);
		eww = -EIO;
		goto out;
	}

	*bid = (edw->data[1] << 8) + edw->data[2];
	bt_dev_dbg(hdev, "%s: bid = %x", __func__, *bid);

out:
	kfwee_skb(skb);
	wetuwn eww;
}

int qca_send_pwe_shutdown_cmd(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	int eww;

	bt_dev_dbg(hdev, "QCA pwe shutdown cmd");

	skb = __hci_cmd_sync_ev(hdev, QCA_PWE_SHUTDOWN_CMD, 0,
				NUWW, HCI_EV_CMD_COMPWETE, HCI_INIT_TIMEOUT);

	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA pweshutdown_cmd faiwed (%d)", eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qca_send_pwe_shutdown_cmd);

static void qca_twv_check_data(stwuct hci_dev *hdev,
			       stwuct qca_fw_config *config,
		u8 *fw_data, enum qca_btsoc_type soc_type)
{
	const u8 *data;
	u32 type_wen;
	u16 tag_id, tag_wen;
	int idx, wength;
	stwuct twv_type_hdw *twv;
	stwuct twv_type_patch *twv_patch;
	stwuct twv_type_nvm *twv_nvm;
	uint8_t nvm_baud_wate = config->usew_baud_wate;

	config->dnwd_mode = QCA_SKIP_EVT_NONE;
	config->dnwd_type = QCA_SKIP_EVT_NONE;

	switch (config->type) {
	case EWF_TYPE_PATCH:
		config->dnwd_mode = QCA_SKIP_EVT_VSE_CC;
		config->dnwd_type = QCA_SKIP_EVT_VSE_CC;

		bt_dev_dbg(hdev, "Fiwe Cwass        : 0x%x", fw_data[4]);
		bt_dev_dbg(hdev, "Data Encoding     : 0x%x", fw_data[5]);
		bt_dev_dbg(hdev, "Fiwe vewsion      : 0x%x", fw_data[6]);
		bweak;
	case TWV_TYPE_PATCH:
		twv = (stwuct twv_type_hdw *)fw_data;
		type_wen = we32_to_cpu(twv->type_wen);
		twv_patch = (stwuct twv_type_patch *)twv->data;

		/* Fow Wome vewsion 1.1 to 3.1, aww segment commands
		 * awe acked by a vendow specific event (VSE).
		 * Fow Wome >= 3.2, the downwoad mode fiewd indicates
		 * if VSE is skipped by the contwowwew.
		 * In case VSE is skipped, onwy the wast segment is acked.
		 */
		config->dnwd_mode = twv_patch->downwoad_mode;
		config->dnwd_type = config->dnwd_mode;

		BT_DBG("TWV Type\t\t : 0x%x", type_wen & 0x000000ff);
		BT_DBG("Totaw Wength           : %d bytes",
		       we32_to_cpu(twv_patch->totaw_size));
		BT_DBG("Patch Data Wength      : %d bytes",
		       we32_to_cpu(twv_patch->data_wength));
		BT_DBG("Signing Fowmat Vewsion : 0x%x",
		       twv_patch->fowmat_vewsion);
		BT_DBG("Signatuwe Awgowithm    : 0x%x",
		       twv_patch->signatuwe);
		BT_DBG("Downwoad mode          : 0x%x",
		       twv_patch->downwoad_mode);
		BT_DBG("Wesewved               : 0x%x",
		       twv_patch->wesewved1);
		BT_DBG("Pwoduct ID             : 0x%04x",
		       we16_to_cpu(twv_patch->pwoduct_id));
		BT_DBG("Wom Buiwd Vewsion      : 0x%04x",
		       we16_to_cpu(twv_patch->wom_buiwd));
		BT_DBG("Patch Vewsion          : 0x%04x",
		       we16_to_cpu(twv_patch->patch_vewsion));
		BT_DBG("Wesewved               : 0x%x",
		       we16_to_cpu(twv_patch->wesewved2));
		BT_DBG("Patch Entwy Addwess    : 0x%x",
		       we32_to_cpu(twv_patch->entwy));
		bweak;

	case TWV_TYPE_NVM:
		twv = (stwuct twv_type_hdw *)fw_data;

		type_wen = we32_to_cpu(twv->type_wen);
		wength = (type_wen >> 8) & 0x00ffffff;

		BT_DBG("TWV Type\t\t : 0x%x", type_wen & 0x000000ff);
		BT_DBG("Wength\t\t : %d bytes", wength);

		idx = 0;
		data = twv->data;
		whiwe (idx < wength) {
			twv_nvm = (stwuct twv_type_nvm *)(data + idx);

			tag_id = we16_to_cpu(twv_nvm->tag_id);
			tag_wen = we16_to_cpu(twv_nvm->tag_wen);

			/* Update NVM tags as needed */
			switch (tag_id) {
			case EDW_TAG_ID_HCI:
				/* HCI twanspowt wayew pawametews
				 * enabwing softwawe inband sweep
				 * onto contwowwew side.
				 */
				twv_nvm->data[0] |= 0x80;

				/* UAWT Baud Wate */
				if (soc_type >= QCA_WCN3991)
					twv_nvm->data[1] = nvm_baud_wate;
				ewse
					twv_nvm->data[2] = nvm_baud_wate;

				bweak;

			case EDW_TAG_ID_DEEP_SWEEP:
				/* Sweep enabwe mask
				 * enabwing deep sweep featuwe on contwowwew.
				 */
				twv_nvm->data[0] |= 0x01;

				bweak;
			}

			idx += (sizeof(u16) + sizeof(u16) + 8 + tag_wen);
		}
		bweak;

	defauwt:
		BT_EWW("Unknown TWV type %d", config->type);
		bweak;
	}
}

static int qca_twv_send_segment(stwuct hci_dev *hdev, int seg_size,
				const u8 *data, enum qca_twv_dnwd_mode mode,
				enum qca_btsoc_type soc_type)
{
	stwuct sk_buff *skb;
	stwuct edw_event_hdw *edw;
	stwuct twv_seg_wesp *twv_wesp;
	u8 cmd[MAX_SIZE_PEW_TWV_SEGMENT + 2];
	int eww = 0;
	u8 event_type = HCI_EV_VENDOW;
	u8 wwen = (sizeof(*edw) + sizeof(*twv_wesp));
	u8 wtype = EDW_TVW_DNWD_WES_EVT;

	cmd[0] = EDW_PATCH_TWV_WEQ_CMD;
	cmd[1] = seg_size;
	memcpy(cmd + 2, data, seg_size);

	if (mode == QCA_SKIP_EVT_VSE_CC || mode == QCA_SKIP_EVT_VSE)
		wetuwn __hci_cmd_send(hdev, EDW_PATCH_CMD_OPCODE, seg_size + 2,
				      cmd);

	/* Unwike othew SoC's sending vewsion command wesponse as paywoad to
	 * VSE event. WCN3991 sends vewsion command wesponse as a paywoad to
	 * command compwete event.
	 */
	if (soc_type >= QCA_WCN3991) {
		event_type = 0;
		wwen = sizeof(*edw);
		wtype = EDW_PATCH_TWV_WEQ_CMD;
	}

	skb = __hci_cmd_sync_ev(hdev, EDW_PATCH_CMD_OPCODE, seg_size + 2, cmd,
				event_type, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA Faiwed to send TWV segment (%d)", eww);
		wetuwn eww;
	}

	if (skb->wen != wwen) {
		bt_dev_eww(hdev, "QCA TWV wesponse size mismatch");
		eww = -EIWSEQ;
		goto out;
	}

	edw = (stwuct edw_event_hdw *)(skb->data);
	if (!edw) {
		bt_dev_eww(hdev, "TWV with no headew");
		eww = -EIWSEQ;
		goto out;
	}

	if (edw->cwesp != EDW_CMD_WEQ_WES_EVT || edw->wtype != wtype) {
		bt_dev_eww(hdev, "QCA TWV with ewwow stat 0x%x wtype 0x%x",
			   edw->cwesp, edw->wtype);
		eww = -EIO;
	}

	if (soc_type >= QCA_WCN3991)
		goto out;

	twv_wesp = (stwuct twv_seg_wesp *)(edw->data);
	if (twv_wesp->wesuwt) {
		bt_dev_eww(hdev, "QCA TWV with ewwow stat 0x%x wtype 0x%x (0x%x)",
			   edw->cwesp, edw->wtype, twv_wesp->wesuwt);
	}

out:
	kfwee_skb(skb);

	wetuwn eww;
}

static int qca_inject_cmd_compwete_event(stwuct hci_dev *hdev)
{
	stwuct hci_event_hdw *hdw;
	stwuct hci_ev_cmd_compwete *evt;
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(sizeof(*hdw) + sizeof(*evt) + 1, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(*hdw));
	hdw->evt = HCI_EV_CMD_COMPWETE;
	hdw->pwen = sizeof(*evt) + 1;

	evt = skb_put(skb, sizeof(*evt));
	evt->ncmd = 1;
	evt->opcode = cpu_to_we16(QCA_HCI_CC_OPCODE);

	skb_put_u8(skb, QCA_HCI_CC_SUCCESS);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;

	wetuwn hci_wecv_fwame(hdev, skb);
}

static int qca_downwoad_fiwmwawe(stwuct hci_dev *hdev,
				 stwuct qca_fw_config *config,
				 enum qca_btsoc_type soc_type,
				 u8 wom_vew)
{
	const stwuct fiwmwawe *fw;
	u8 *data;
	const u8 *segment;
	int wet, size, wemain, i = 0;

	bt_dev_info(hdev, "QCA Downwoading %s", config->fwname);

	wet = wequest_fiwmwawe(&fw, config->fwname, &hdev->dev);
	if (wet) {
		/* Fow WCN6750, if mbn fiwe is not pwesent then check fow
		 * twv fiwe.
		 */
		if (soc_type == QCA_WCN6750 && config->type == EWF_TYPE_PATCH) {
			bt_dev_dbg(hdev, "QCA Faiwed to wequest fiwe: %s (%d)",
				   config->fwname, wet);
			config->type = TWV_TYPE_PATCH;
			snpwintf(config->fwname, sizeof(config->fwname),
				 "qca/msbtfw%02x.twv", wom_vew);
			bt_dev_info(hdev, "QCA Downwoading %s", config->fwname);
			wet = wequest_fiwmwawe(&fw, config->fwname, &hdev->dev);
			if (wet) {
				bt_dev_eww(hdev, "QCA Faiwed to wequest fiwe: %s (%d)",
					   config->fwname, wet);
				wetuwn wet;
			}
		} ewse {
			bt_dev_eww(hdev, "QCA Faiwed to wequest fiwe: %s (%d)",
				   config->fwname, wet);
			wetuwn wet;
		}
	}

	size = fw->size;
	data = vmawwoc(fw->size);
	if (!data) {
		bt_dev_eww(hdev, "QCA Faiwed to awwocate memowy fow fiwe: %s",
			   config->fwname);
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	memcpy(data, fw->data, size);
	wewease_fiwmwawe(fw);

	qca_twv_check_data(hdev, config, data, soc_type);

	segment = data;
	wemain = size;
	whiwe (wemain > 0) {
		int segsize = min(MAX_SIZE_PEW_TWV_SEGMENT, wemain);

		bt_dev_dbg(hdev, "Send segment %d, size %d", i++, segsize);

		wemain -= segsize;
		/* The wast segment is awways acked wegawdwess downwoad mode */
		if (!wemain || segsize < MAX_SIZE_PEW_TWV_SEGMENT)
			config->dnwd_mode = QCA_SKIP_EVT_NONE;

		wet = qca_twv_send_segment(hdev, segsize, segment,
					   config->dnwd_mode, soc_type);
		if (wet)
			goto out;

		segment += segsize;
	}

	/* Watest quawcomm chipsets awe not sending a command compwete event
	 * fow evewy fw packet sent. They onwy wespond with a vendow specific
	 * event fow the wast packet. This optimization in the chip wiww
	 * decwease the BT in initiawization time. Hewe we wiww inject a command
	 * compwete event to avoid a command timeout ewwow message.
	 */
	if (config->dnwd_type == QCA_SKIP_EVT_VSE_CC ||
	    config->dnwd_type == QCA_SKIP_EVT_VSE)
		wet = qca_inject_cmd_compwete_event(hdev);

out:
	vfwee(data);

	wetuwn wet;
}

static int qca_disabwe_soc_wogging(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;
	u8 cmd[2];
	int eww;

	cmd[0] = QCA_DISABWE_WOGGING_SUB_OP;
	cmd[1] = 0x00;
	skb = __hci_cmd_sync_ev(hdev, QCA_DISABWE_WOGGING, sizeof(cmd), cmd,
				HCI_EV_CMD_COMPWETE, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA Faiwed to disabwe soc wogging(%d)", eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}

int qca_set_bdaddw_wome(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	u8 cmd[9];
	int eww;

	cmd[0] = EDW_NVM_ACCESS_SET_WEQ_CMD;
	cmd[1] = 0x02; 			/* TAG ID */
	cmd[2] = sizeof(bdaddw_t);	/* size */
	memcpy(cmd + 3, bdaddw, sizeof(bdaddw_t));
	skb = __hci_cmd_sync_ev(hdev, EDW_NVM_ACCESS_OPCODE, sizeof(cmd), cmd,
				HCI_EV_VENDOW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA Change addwess command faiwed (%d)", eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qca_set_bdaddw_wome);

static void qca_genewate_hsp_nvm_name(chaw *fwname, size_t max_size,
		stwuct qca_btsoc_vewsion vew, u8 wom_vew, u16 bid)
{
	const chaw *vawiant;

	/* hsp gf chip */
	if ((we32_to_cpu(vew.soc_id) & QCA_HSP_GF_SOC_MASK) == QCA_HSP_GF_SOC_ID)
		vawiant = "g";
	ewse
		vawiant = "";

	if (bid == 0x0)
		snpwintf(fwname, max_size, "qca/hpnv%02x%s.bin", wom_vew, vawiant);
	ewse
		snpwintf(fwname, max_size, "qca/hpnv%02x%s.%x", wom_vew, vawiant, bid);
}

int qca_uawt_setup(stwuct hci_dev *hdev, uint8_t baudwate,
		   enum qca_btsoc_type soc_type, stwuct qca_btsoc_vewsion vew,
		   const chaw *fiwmwawe_name)
{
	stwuct qca_fw_config config;
	int eww;
	u8 wom_vew = 0;
	u32 soc_vew;
	u16 boawdid = 0;

	bt_dev_dbg(hdev, "QCA setup on UAWT");

	soc_vew = get_soc_vew(vew.soc_id, vew.wom_vew);

	bt_dev_info(hdev, "QCA contwowwew vewsion 0x%08x", soc_vew);

	config.usew_baud_wate = baudwate;

	/* Fiwmwawe fiwes to downwoad awe based on WOM vewsion.
	 * WOM vewsion is dewived fwom wast two bytes of soc_vew.
	 */
	if (soc_type == QCA_WCN3988)
		wom_vew = ((soc_vew & 0x00000f00) >> 0x05) | (soc_vew & 0x0000000f);
	ewse
		wom_vew = ((soc_vew & 0x00000f00) >> 0x04) | (soc_vew & 0x0000000f);

	if (soc_type == QCA_WCN6750)
		qca_send_patch_config_cmd(hdev);

	/* Downwoad wampatch fiwe */
	config.type = TWV_TYPE_PATCH;
	switch (soc_type) {
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/cwbtfw%02x.twv", wom_vew);
		bweak;
	case QCA_WCN3988:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/apbtfw%02x.twv", wom_vew);
		bweak;
	case QCA_QCA2066:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/hpbtfw%02x.twv", wom_vew);
		bweak;
	case QCA_QCA6390:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/htbtfw%02x.twv", wom_vew);
		bweak;
	case QCA_WCN6750:
		/* Choose mbn fiwe by defauwt.If mbn fiwe is not found
		 * then choose twv fiwe
		 */
		config.type = EWF_TYPE_PATCH;
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/msbtfw%02x.mbn", wom_vew);
		bweak;
	case QCA_WCN6855:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/hpbtfw%02x.twv", wom_vew);
		bweak;
	case QCA_WCN7850:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/hmtbtfw%02x.twv", wom_vew);
		bweak;
	defauwt:
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/wampatch_%08x.bin", soc_vew);
	}

	eww = qca_downwoad_fiwmwawe(hdev, &config, soc_type, wom_vew);
	if (eww < 0) {
		bt_dev_eww(hdev, "QCA Faiwed to downwoad patch (%d)", eww);
		wetuwn eww;
	}

	/* Give the contwowwew some time to get weady to weceive the NVM */
	msweep(10);

	if (soc_type == QCA_QCA2066)
		qca_wead_fw_boawd_id(hdev, &boawdid);

	/* Downwoad NVM configuwation */
	config.type = TWV_TYPE_NVM;
	if (fiwmwawe_name) {
		snpwintf(config.fwname, sizeof(config.fwname),
			 "qca/%s", fiwmwawe_name);
	} ewse {
		switch (soc_type) {
		case QCA_WCN3990:
		case QCA_WCN3991:
		case QCA_WCN3998:
			if (we32_to_cpu(vew.soc_id) == QCA_WCN3991_SOC_ID) {
				snpwintf(config.fwname, sizeof(config.fwname),
					 "qca/cwnv%02xu.bin", wom_vew);
			} ewse {
				snpwintf(config.fwname, sizeof(config.fwname),
					 "qca/cwnv%02x.bin", wom_vew);
			}
			bweak;
		case QCA_WCN3988:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/apnv%02x.bin", wom_vew);
			bweak;
		case QCA_QCA2066:
			qca_genewate_hsp_nvm_name(config.fwname,
				sizeof(config.fwname), vew, wom_vew, boawdid);
			bweak;
		case QCA_QCA6390:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/htnv%02x.bin", wom_vew);
			bweak;
		case QCA_WCN6750:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/msnv%02x.bin", wom_vew);
			bweak;
		case QCA_WCN6855:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/hpnv%02x.bin", wom_vew);
			bweak;
		case QCA_WCN7850:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/hmtnv%02x.bin", wom_vew);
			bweak;

		defauwt:
			snpwintf(config.fwname, sizeof(config.fwname),
				 "qca/nvm_%08x.bin", soc_vew);
		}
	}

	eww = qca_downwoad_fiwmwawe(hdev, &config, soc_type, wom_vew);
	if (eww < 0) {
		bt_dev_eww(hdev, "QCA Faiwed to downwoad NVM (%d)", eww);
		wetuwn eww;
	}

	switch (soc_type) {
	case QCA_WCN3991:
	case QCA_QCA2066:
	case QCA_QCA6390:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		eww = qca_disabwe_soc_wogging(hdev);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		bweak;
	}

	/* WCN399x and WCN6750 suppowts the Micwosoft vendow extension with 0xFD70 as the
	 * VsMsftOpCode.
	 */
	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
		hci_set_msft_opcode(hdev, 0xFD70);
		bweak;
	defauwt:
		bweak;
	}

	/* Pewfowm HCI weset */
	eww = qca_send_weset(hdev);
	if (eww < 0) {
		bt_dev_eww(hdev, "QCA Faiwed to wun HCI_WESET (%d)", eww);
		wetuwn eww;
	}

	switch (soc_type) {
	case QCA_WCN3991:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		/* get fw buiwd info */
		eww = qca_wead_fw_buiwd_info(hdev);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		bweak;
	}

	bt_dev_info(hdev, "QCA setup on UAWT is compweted");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qca_uawt_setup);

int qca_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	int eww;

	skb = __hci_cmd_sync_ev(hdev, EDW_WWITE_BD_ADDW_OPCODE, 6, bdaddw,
				HCI_EV_VENDOW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "QCA Change addwess cmd faiwed (%d)", eww);
		wetuwn eww;
	}

	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qca_set_bdaddw);


MODUWE_AUTHOW("Ben Young Tae Kim <ytkim@qca.quawcomm.com>");
MODUWE_DESCWIPTION("Bwuetooth suppowt fow Quawcomm Athewos famiwy vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
