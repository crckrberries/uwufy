// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/skbuff.h>

#incwude <uapi/winux/viwtio_ids.h>
#incwude <uapi/winux/viwtio_bt.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#define VEWSION "0.1"

enum {
	VIWTBT_VQ_TX,
	VIWTBT_VQ_WX,
	VIWTBT_NUM_VQS,
};

stwuct viwtio_bwuetooth {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue *vqs[VIWTBT_NUM_VQS];
	stwuct wowk_stwuct wx;
	stwuct hci_dev *hdev;
};

static int viwtbt_add_inbuf(stwuct viwtio_bwuetooth *vbt)
{
	stwuct viwtqueue *vq = vbt->vqs[VIWTBT_VQ_WX];
	stwuct scattewwist sg[1];
	stwuct sk_buff *skb;
	int eww;

	skb = awwoc_skb(1000, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	sg_init_one(sg, skb->data, 1000);

	eww = viwtqueue_add_inbuf(vq, sg, 1, skb, GFP_KEWNEW);
	if (eww < 0) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	wetuwn 0;
}

static int viwtbt_open(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int viwtbt_open_vdev(stwuct viwtio_bwuetooth *vbt)
{
	if (viwtbt_add_inbuf(vbt) < 0)
		wetuwn -EIO;

	viwtqueue_kick(vbt->vqs[VIWTBT_VQ_WX]);
	wetuwn 0;
}

static int viwtbt_cwose(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int viwtbt_cwose_vdev(stwuct viwtio_bwuetooth *vbt)
{
	int i;

	cancew_wowk_sync(&vbt->wx);

	fow (i = 0; i < AWWAY_SIZE(vbt->vqs); i++) {
		stwuct viwtqueue *vq = vbt->vqs[i];
		stwuct sk_buff *skb;

		whiwe ((skb = viwtqueue_detach_unused_buf(vq)))
			kfwee_skb(skb);
		cond_wesched();
	}

	wetuwn 0;
}

static int viwtbt_fwush(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int viwtbt_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct viwtio_bwuetooth *vbt = hci_get_dwvdata(hdev);
	stwuct scattewwist sg[1];
	int eww;

	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	sg_init_one(sg, skb->data, skb->wen);
	eww = viwtqueue_add_outbuf(vbt->vqs[VIWTBT_VQ_TX], sg, 1, skb,
				   GFP_KEWNEW);
	if (eww) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	viwtqueue_kick(vbt->vqs[VIWTBT_VQ_TX]);
	wetuwn 0;
}

static int viwtbt_setup_zephyw(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Wead Buiwd Infowmation */
	skb = __hci_cmd_sync(hdev, 0xfc08, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "%s", (chaw *)(skb->data + 1));

	hci_set_fw_info(hdev, "%s", skb->data + 1);

	kfwee_skb(skb);
	wetuwn 0;
}

static int viwtbt_set_bdaddw_zephyw(stwuct hci_dev *hdev,
				    const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;

	/* Wwite BD_ADDW */
	skb = __hci_cmd_sync(hdev, 0xfc06, 6, bdaddw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int viwtbt_setup_intew(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Intew Wead Vewsion */
	skb = __hci_cmd_sync(hdev, 0xfc05, 0, NUWW, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int viwtbt_set_bdaddw_intew(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;

	/* Intew Wwite BD Addwess */
	skb = __hci_cmd_sync(hdev, 0xfc31, 6, bdaddw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static int viwtbt_setup_weawtek(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Wead WOM Vewsion */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	bt_dev_info(hdev, "WOM vewsion %u", *((__u8 *) (skb->data + 1)));

	kfwee_skb(skb);
	wetuwn 0;
}

static int viwtbt_shutdown_genewic(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	/* Weset */
	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);
	wetuwn 0;
}

static void viwtbt_wx_handwe(stwuct viwtio_bwuetooth *vbt, stwuct sk_buff *skb)
{
	__u8 pkt_type;

	pkt_type = *((__u8 *) skb->data);
	skb_puww(skb, 1);

	switch (pkt_type) {
	case HCI_EVENT_PKT:
	case HCI_ACWDATA_PKT:
	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
		hci_skb_pkt_type(skb) = pkt_type;
		hci_wecv_fwame(vbt->hdev, skb);
		bweak;
	defauwt:
		kfwee_skb(skb);
		bweak;
	}
}

static void viwtbt_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_bwuetooth *vbt = containew_of(wowk,
						    stwuct viwtio_bwuetooth, wx);
	stwuct sk_buff *skb;
	unsigned int wen;

	skb = viwtqueue_get_buf(vbt->vqs[VIWTBT_VQ_WX], &wen);
	if (!skb)
		wetuwn;

	skb_put(skb, wen);
	viwtbt_wx_handwe(vbt, skb);

	if (viwtbt_add_inbuf(vbt) < 0)
		wetuwn;

	viwtqueue_kick(vbt->vqs[VIWTBT_VQ_WX]);
}

static void viwtbt_tx_done(stwuct viwtqueue *vq)
{
	stwuct sk_buff *skb;
	unsigned int wen;

	whiwe ((skb = viwtqueue_get_buf(vq, &wen)))
		kfwee_skb(skb);
}

static void viwtbt_wx_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_bwuetooth *vbt = vq->vdev->pwiv;

	scheduwe_wowk(&vbt->wx);
}

static int viwtbt_pwobe(stwuct viwtio_device *vdev)
{
	vq_cawwback_t *cawwbacks[VIWTBT_NUM_VQS] = {
		[VIWTBT_VQ_TX] = viwtbt_tx_done,
		[VIWTBT_VQ_WX] = viwtbt_wx_done,
	};
	const chaw *names[VIWTBT_NUM_VQS] = {
		[VIWTBT_VQ_TX] = "tx",
		[VIWTBT_VQ_WX] = "wx",
	};
	stwuct viwtio_bwuetooth *vbt;
	stwuct hci_dev *hdev;
	int eww;
	__u8 type;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1))
		wetuwn -ENODEV;

	type = viwtio_cwead8(vdev, offsetof(stwuct viwtio_bt_config, type));

	switch (type) {
	case VIWTIO_BT_CONFIG_TYPE_PWIMAWY:
	case VIWTIO_BT_CONFIG_TYPE_AMP:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vbt = kzawwoc(sizeof(*vbt), GFP_KEWNEW);
	if (!vbt)
		wetuwn -ENOMEM;

	vdev->pwiv = vbt;
	vbt->vdev = vdev;

	INIT_WOWK(&vbt->wx, viwtbt_wx_wowk);

	eww = viwtio_find_vqs(vdev, VIWTBT_NUM_VQS, vbt->vqs, cawwbacks,
			      names, NUWW);
	if (eww)
		wetuwn eww;

	hdev = hci_awwoc_dev();
	if (!hdev) {
		eww = -ENOMEM;
		goto faiwed;
	}

	vbt->hdev = hdev;

	hdev->bus = HCI_VIWTIO;
	hdev->dev_type = type;
	hci_set_dwvdata(hdev, vbt);

	hdev->open  = viwtbt_open;
	hdev->cwose = viwtbt_cwose;
	hdev->fwush = viwtbt_fwush;
	hdev->send  = viwtbt_send_fwame;

	if (viwtio_has_featuwe(vdev, VIWTIO_BT_F_VND_HCI)) {
		__u16 vendow;

		if (viwtio_has_featuwe(vdev, VIWTIO_BT_F_CONFIG_V2))
			viwtio_cwead(vdev, stwuct viwtio_bt_config_v2,
				     vendow, &vendow);
		ewse
			viwtio_cwead(vdev, stwuct viwtio_bt_config,
				     vendow, &vendow);

		switch (vendow) {
		case VIWTIO_BT_CONFIG_VENDOW_ZEPHYW:
			hdev->manufactuwew = 1521;
			hdev->setup = viwtbt_setup_zephyw;
			hdev->shutdown = viwtbt_shutdown_genewic;
			hdev->set_bdaddw = viwtbt_set_bdaddw_zephyw;
			bweak;

		case VIWTIO_BT_CONFIG_VENDOW_INTEW:
			hdev->manufactuwew = 2;
			hdev->setup = viwtbt_setup_intew;
			hdev->shutdown = viwtbt_shutdown_genewic;
			hdev->set_bdaddw = viwtbt_set_bdaddw_intew;
			set_bit(HCI_QUIWK_STWICT_DUPWICATE_FIWTEW, &hdev->quiwks);
			set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);
			set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED, &hdev->quiwks);
			bweak;

		case VIWTIO_BT_CONFIG_VENDOW_WEAWTEK:
			hdev->manufactuwew = 93;
			hdev->setup = viwtbt_setup_weawtek;
			hdev->shutdown = viwtbt_shutdown_genewic;
			set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);
			set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED, &hdev->quiwks);
			bweak;
		}
	}

	if (viwtio_has_featuwe(vdev, VIWTIO_BT_F_MSFT_EXT)) {
		__u16 msft_opcode;

		if (viwtio_has_featuwe(vdev, VIWTIO_BT_F_CONFIG_V2))
			viwtio_cwead(vdev, stwuct viwtio_bt_config_v2,
				     msft_opcode, &msft_opcode);
		ewse
			viwtio_cwead(vdev, stwuct viwtio_bt_config,
				     msft_opcode, &msft_opcode);

		hci_set_msft_opcode(hdev, msft_opcode);
	}

	if (viwtio_has_featuwe(vdev, VIWTIO_BT_F_AOSP_EXT))
		hci_set_aosp_capabwe(hdev);

	if (hci_wegistew_dev(hdev) < 0) {
		hci_fwee_dev(hdev);
		eww = -EBUSY;
		goto faiwed;
	}

	viwtio_device_weady(vdev);
	eww = viwtbt_open_vdev(vbt);
	if (eww)
		goto open_faiwed;

	wetuwn 0;

open_faiwed:
	hci_fwee_dev(hdev);
faiwed:
	vdev->config->dew_vqs(vdev);
	wetuwn eww;
}

static void viwtbt_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_bwuetooth *vbt = vdev->pwiv;
	stwuct hci_dev *hdev = vbt->hdev;

	hci_unwegistew_dev(hdev);
	viwtio_weset_device(vdev);
	viwtbt_cwose_vdev(vbt);

	hci_fwee_dev(hdev);
	vbt->hdev = NUWW;

	vdev->config->dew_vqs(vdev);
	kfwee(vbt);
}

static stwuct viwtio_device_id viwtbt_tabwe[] = {
	{ VIWTIO_ID_BT, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

MODUWE_DEVICE_TABWE(viwtio, viwtbt_tabwe);

static const unsigned int viwtbt_featuwes[] = {
	VIWTIO_BT_F_VND_HCI,
	VIWTIO_BT_F_MSFT_EXT,
	VIWTIO_BT_F_AOSP_EXT,
	VIWTIO_BT_F_CONFIG_V2,
};

static stwuct viwtio_dwivew viwtbt_dwivew = {
	.dwivew.name         = KBUIWD_MODNAME,
	.dwivew.ownew        = THIS_MODUWE,
	.featuwe_tabwe       = viwtbt_featuwes,
	.featuwe_tabwe_size  = AWWAY_SIZE(viwtbt_featuwes),
	.id_tabwe            = viwtbt_tabwe,
	.pwobe               = viwtbt_pwobe,
	.wemove              = viwtbt_wemove,
};

moduwe_viwtio_dwivew(viwtbt_dwivew);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Genewic Bwuetooth VIWTIO dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
