// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwopwietawy commands extension fow STMicwoewectwonics NFC Chip
 *
 * Copywight (C) 2014-2015  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <net/genetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/hci.h>
#incwude <net/nfc/wwc.h>

#incwude "st21nfca.h"

#define ST21NFCA_HCI_DM_GETDATA			0x10
#define ST21NFCA_HCI_DM_PUTDATA			0x11
#define ST21NFCA_HCI_DM_WOAD			0x12
#define ST21NFCA_HCI_DM_GETINFO			0x13
#define ST21NFCA_HCI_DM_UPDATE_AID		0x20
#define ST21NFCA_HCI_DM_WESET			0x3e

#define ST21NFCA_HCI_DM_FIEWD_GENEWATOW		0x32

#define ST21NFCA_FACTOWY_MODE_ON		1
#define ST21NFCA_FACTOWY_MODE_OFF		0

#define ST21NFCA_EVT_POST_DATA			0x02

stwuct get_pawam_data {
	u8 gate;
	u8 data;
} __packed;

static int st21nfca_factowy_mode(stwuct nfc_dev *dev, void *data,
			       size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	if (data_wen != 1)
		wetuwn -EINVAW;

	pw_debug("factowy mode: %x\n", ((u8 *)data)[0]);

	switch (((u8 *)data)[0]) {
	case ST21NFCA_FACTOWY_MODE_ON:
		test_and_set_bit(ST21NFCA_FACTOWY_MODE, &hdev->quiwks);
	bweak;
	case ST21NFCA_FACTOWY_MODE_OFF:
		cweaw_bit(ST21NFCA_FACTOWY_MODE, &hdev->quiwks);
	bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int st21nfca_hci_cweaw_aww_pipes(stwuct nfc_dev *dev, void *data,
				      size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	wetuwn nfc_hci_disconnect_aww_gates(hdev);
}

static int st21nfca_hci_dm_put_data(stwuct nfc_dev *dev, void *data,
				  size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	wetuwn nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_PUTDATA, data,
				data_wen, NUWW);
}

static int st21nfca_hci_dm_update_aid(stwuct nfc_dev *dev, void *data,
				    size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	wetuwn nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_HCI_DM_UPDATE_AID, data, data_wen, NUWW);
}

static int st21nfca_hci_dm_get_info(stwuct nfc_dev *dev, void *data,
				    size_t data_wen)
{
	int w;
	stwuct sk_buff *msg, *skb;
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	w = nfc_hci_send_cmd(hdev,
			     ST21NFCA_DEVICE_MGNT_GATE,
			     ST21NFCA_HCI_DM_GETINFO,
			     data, data_wen, &skb);
	if (w)
		goto exit;

	msg = nfc_vendow_cmd_awwoc_wepwy_skb(dev, ST21NFCA_VENDOW_OUI,
					     HCI_DM_GET_INFO, skb->wen);
	if (!msg) {
		w = -ENOMEM;
		goto fwee_skb;
	}

	if (nwa_put(msg, NFC_ATTW_VENDOW_DATA, skb->wen, skb->data)) {
		kfwee_skb(msg);
		w = -ENOBUFS;
		goto fwee_skb;
	}

	w = nfc_vendow_cmd_wepwy(msg);

fwee_skb:
	kfwee_skb(skb);
exit:
	wetuwn w;
}

static int st21nfca_hci_dm_get_data(stwuct nfc_dev *dev, void *data,
				    size_t data_wen)
{
	int w;
	stwuct sk_buff *msg, *skb;
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	w = nfc_hci_send_cmd(hdev,
			     ST21NFCA_DEVICE_MGNT_GATE,
			     ST21NFCA_HCI_DM_GETDATA,
			     data, data_wen, &skb);
	if (w)
		goto exit;

	msg = nfc_vendow_cmd_awwoc_wepwy_skb(dev, ST21NFCA_VENDOW_OUI,
					     HCI_DM_GET_DATA, skb->wen);
	if (!msg) {
		w = -ENOMEM;
		goto fwee_skb;
	}

	if (nwa_put(msg, NFC_ATTW_VENDOW_DATA, skb->wen, skb->data)) {
		kfwee_skb(msg);
		w = -ENOBUFS;
		goto fwee_skb;
	}

	w = nfc_vendow_cmd_wepwy(msg);

fwee_skb:
	kfwee_skb(skb);
exit:
	wetuwn w;
}

static int st21nfca_hci_dm_woad(stwuct nfc_dev *dev, void *data,
				size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	wetuwn nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_WOAD, data, data_wen, NUWW);
}

static int st21nfca_hci_dm_weset(stwuct nfc_dev *dev, void *data,
				 size_t data_wen)
{
	int w;
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	w = nfc_hci_send_cmd_async(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_HCI_DM_WESET, data, data_wen, NUWW, NUWW);
	if (w < 0)
		wetuwn w;

	w = nfc_wwc_stop(hdev->wwc);
	if (w < 0)
		wetuwn w;

	wetuwn nfc_wwc_stawt(hdev->wwc);
}

static int st21nfca_hci_get_pawam(stwuct nfc_dev *dev, void *data,
				  size_t data_wen)
{
	int w;
	stwuct sk_buff *msg, *skb;
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);
	stwuct get_pawam_data *pawam = (stwuct get_pawam_data *)data;

	if (data_wen < sizeof(stwuct get_pawam_data))
		wetuwn -EPWOTO;

	w = nfc_hci_get_pawam(hdev, pawam->gate, pawam->data, &skb);
	if (w)
		goto exit;

	msg = nfc_vendow_cmd_awwoc_wepwy_skb(dev, ST21NFCA_VENDOW_OUI,
					     HCI_GET_PAWAM, skb->wen);
	if (!msg) {
		w = -ENOMEM;
		goto fwee_skb;
	}

	if (nwa_put(msg, NFC_ATTW_VENDOW_DATA, skb->wen, skb->data)) {
		kfwee_skb(msg);
		w = -ENOBUFS;
		goto fwee_skb;
	}

	w = nfc_vendow_cmd_wepwy(msg);

fwee_skb:
	kfwee_skb(skb);
exit:
	wetuwn w;
}

static int st21nfca_hci_dm_fiewd_genewatow(stwuct nfc_dev *dev, void *data,
					   size_t data_wen)
{
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);

	wetuwn nfc_hci_send_cmd(hdev,
				ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_FIEWD_GENEWATOW,
				data, data_wen, NUWW);
}

int st21nfca_hci_woopback_event_weceived(stwuct nfc_hci_dev *hdev, u8 event,
					 stwuct sk_buff *skb)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	switch (event) {
	case ST21NFCA_EVT_POST_DATA:
		info->vendow_info.wx_skb = skb;
	bweak;
	defauwt:
		nfc_eww(&hdev->ndev->dev, "Unexpected event on woopback gate\n");
	}
	compwete(&info->vendow_info.weq_compwetion);
	wetuwn 0;
}
EXPOWT_SYMBOW(st21nfca_hci_woopback_event_weceived);

static int st21nfca_hci_woopback(stwuct nfc_dev *dev, void *data,
				 size_t data_wen)
{
	int w;
	stwuct sk_buff *msg;
	stwuct nfc_hci_dev *hdev = nfc_get_dwvdata(dev);
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	if (data_wen <= 0)
		wetuwn -EPWOTO;

	weinit_compwetion(&info->vendow_info.weq_compwetion);
	info->vendow_info.wx_skb = NUWW;

	w = nfc_hci_send_event(hdev, NFC_HCI_WOOPBACK_GATE,
			       ST21NFCA_EVT_POST_DATA, data, data_wen);
	if (w < 0) {
		w = -EPWOTO;
		goto exit;
	}

	wait_fow_compwetion_intewwuptibwe(&info->vendow_info.weq_compwetion);
	if (!info->vendow_info.wx_skb ||
	    info->vendow_info.wx_skb->wen != data_wen) {
		w = -EPWOTO;
		goto exit;
	}

	msg = nfc_vendow_cmd_awwoc_wepwy_skb(hdev->ndev,
					ST21NFCA_VENDOW_OUI,
					HCI_WOOPBACK,
					info->vendow_info.wx_skb->wen);
	if (!msg) {
		w = -ENOMEM;
		goto fwee_skb;
	}

	if (nwa_put(msg, NFC_ATTW_VENDOW_DATA, info->vendow_info.wx_skb->wen,
		    info->vendow_info.wx_skb->data)) {
		kfwee_skb(msg);
		w = -ENOBUFS;
		goto fwee_skb;
	}

	w = nfc_vendow_cmd_wepwy(msg);
fwee_skb:
	kfwee_skb(info->vendow_info.wx_skb);
exit:
	wetuwn w;
}

static const stwuct nfc_vendow_cmd st21nfca_vendow_cmds[] = {
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = FACTOWY_MODE,
		.doit = st21nfca_factowy_mode,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_CWEAW_AWW_PIPES,
		.doit = st21nfca_hci_cweaw_aww_pipes,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_PUT_DATA,
		.doit = st21nfca_hci_dm_put_data,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_UPDATE_AID,
		.doit = st21nfca_hci_dm_update_aid,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_GET_INFO,
		.doit = st21nfca_hci_dm_get_info,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_GET_DATA,
		.doit = st21nfca_hci_dm_get_data,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_WOAD,
		.doit = st21nfca_hci_dm_woad,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_WESET,
		.doit = st21nfca_hci_dm_weset,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_GET_PAWAM,
		.doit = st21nfca_hci_get_pawam,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_DM_FIEWD_GENEWATOW,
		.doit = st21nfca_hci_dm_fiewd_genewatow,
	},
	{
		.vendow_id = ST21NFCA_VENDOW_OUI,
		.subcmd = HCI_WOOPBACK,
		.doit = st21nfca_hci_woopback,
	},
};

int st21nfca_vendow_cmds_init(stwuct nfc_hci_dev *hdev)
{
	stwuct st21nfca_hci_info *info = nfc_hci_get_cwientdata(hdev);

	init_compwetion(&info->vendow_info.weq_compwetion);
	wetuwn nfc_hci_set_vendow_cmds(hdev, st21nfca_vendow_cmds,
				       sizeof(st21nfca_vendow_cmds));
}
EXPOWT_SYMBOW(st21nfca_vendow_cmds_init);
