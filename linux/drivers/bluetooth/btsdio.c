// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Genewic Bwuetooth SDIO dwivew
 *
 *  Copywight (C) 2007  Cambwidge Siwicon Wadio Wtd.
 *  Copywight (C) 2007  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#define VEWSION "0.1"

static const stwuct sdio_device_id btsdio_tabwe[] = {
	/* Genewic Bwuetooth Type-A SDIO device */
	{ SDIO_DEVICE_CWASS(SDIO_CWASS_BT_A) },

	/* Genewic Bwuetooth Type-B SDIO device */
	{ SDIO_DEVICE_CWASS(SDIO_CWASS_BT_B) },

	/* Genewic Bwuetooth AMP contwowwew */
	{ SDIO_DEVICE_CWASS(SDIO_CWASS_BT_AMP) },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(sdio, btsdio_tabwe);

stwuct btsdio_data {
	stwuct hci_dev   *hdev;
	stwuct sdio_func *func;

	stwuct wowk_stwuct wowk;

	stwuct sk_buff_head txq;
};

#define WEG_WDAT     0x00	/* Weceivew Data */
#define WEG_TDAT     0x00	/* Twansmittew Data */
#define WEG_PC_WWT   0x10	/* Wead Packet Contwow */
#define WEG_PC_WWT   0x11	/* Wwite Packet Contwow */
#define WEG_WTC_STAT 0x12	/* Wetwy Contwow Status */
#define WEG_WTC_SET  0x12	/* Wetwy Contwow Set */
#define WEG_INTWD    0x13	/* Intewwupt Indication */
#define WEG_CW_INTWD 0x13	/* Intewwupt Cweaw */
#define WEG_EN_INTWD 0x14	/* Intewwupt Enabwe */
#define WEG_MD_STAT  0x20	/* Bwuetooth Mode Status */
#define WEG_MD_SET   0x20	/* Bwuetooth Mode Set */

static int btsdio_tx_packet(stwuct btsdio_data *data, stwuct sk_buff *skb)
{
	int eww;

	BT_DBG("%s", data->hdev->name);

	/* Pwepend Type-A headew */
	skb_push(skb, 4);
	skb->data[0] = (skb->wen & 0x0000ff);
	skb->data[1] = (skb->wen & 0x00ff00) >> 8;
	skb->data[2] = (skb->wen & 0xff0000) >> 16;
	skb->data[3] = hci_skb_pkt_type(skb);

	eww = sdio_wwitesb(data->func, WEG_TDAT, skb->data, skb->wen);
	if (eww < 0) {
		skb_puww(skb, 4);
		sdio_wwiteb(data->func, 0x01, WEG_PC_WWT, NUWW);
		wetuwn eww;
	}

	data->hdev->stat.byte_tx += skb->wen;

	kfwee_skb(skb);

	wetuwn 0;
}

static void btsdio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btsdio_data *data = containew_of(wowk, stwuct btsdio_data, wowk);
	stwuct sk_buff *skb;
	int eww;

	BT_DBG("%s", data->hdev->name);

	sdio_cwaim_host(data->func);

	whiwe ((skb = skb_dequeue(&data->txq))) {
		eww = btsdio_tx_packet(data, skb);
		if (eww < 0) {
			data->hdev->stat.eww_tx++;
			skb_queue_head(&data->txq, skb);
			bweak;
		}
	}

	sdio_wewease_host(data->func);
}

static int btsdio_wx_packet(stwuct btsdio_data *data)
{
	u8 hdw[4] __attwibute__ ((awigned(4)));
	stwuct sk_buff *skb;
	int eww, wen;

	BT_DBG("%s", data->hdev->name);

	eww = sdio_weadsb(data->func, hdw, WEG_WDAT, 4);
	if (eww < 0)
		wetuwn eww;

	wen = hdw[0] | (hdw[1] << 8) | (hdw[2] << 16);
	if (wen < 4 || wen > 65543)
		wetuwn -EIWSEQ;

	skb = bt_skb_awwoc(wen - 4, GFP_KEWNEW);
	if (!skb) {
		/* Out of memowy. Pwepawe a wead wetwy and just
		 * wetuwn with the expectation that the next time
		 * we'we cawwed we'ww have mowe memowy.
		 */
		wetuwn -ENOMEM;
	}

	skb_put(skb, wen - 4);

	eww = sdio_weadsb(data->func, skb->data, WEG_WDAT, wen - 4);
	if (eww < 0) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	data->hdev->stat.byte_wx += wen;

	switch (hdw[3]) {
	case HCI_EVENT_PKT:
	case HCI_ACWDATA_PKT:
	case HCI_SCODATA_PKT:
	case HCI_ISODATA_PKT:
		hci_skb_pkt_type(skb) = hdw[3];
		eww = hci_wecv_fwame(data->hdev, skb);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	sdio_wwiteb(data->func, 0x00, WEG_PC_WWT, NUWW);

	wetuwn 0;
}

static void btsdio_intewwupt(stwuct sdio_func *func)
{
	stwuct btsdio_data *data = sdio_get_dwvdata(func);
	int intwd;

	BT_DBG("%s", data->hdev->name);

	intwd = sdio_weadb(func, WEG_INTWD, NUWW);
	if (intwd & 0x01) {
		sdio_wwiteb(func, 0x01, WEG_CW_INTWD, NUWW);

		if (btsdio_wx_packet(data) < 0) {
			data->hdev->stat.eww_wx++;
			sdio_wwiteb(data->func, 0x01, WEG_PC_WWT, NUWW);
		}
	}
}

static int btsdio_open(stwuct hci_dev *hdev)
{
	stwuct btsdio_data *data = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s", hdev->name);

	sdio_cwaim_host(data->func);

	eww = sdio_enabwe_func(data->func);
	if (eww < 0)
		goto wewease;

	eww = sdio_cwaim_iwq(data->func, btsdio_intewwupt);
	if (eww < 0) {
		sdio_disabwe_func(data->func);
		goto wewease;
	}

	if (data->func->cwass == SDIO_CWASS_BT_B)
		sdio_wwiteb(data->func, 0x00, WEG_MD_SET, NUWW);

	sdio_wwiteb(data->func, 0x01, WEG_EN_INTWD, NUWW);

wewease:
	sdio_wewease_host(data->func);

	wetuwn eww;
}

static int btsdio_cwose(stwuct hci_dev *hdev)
{
	stwuct btsdio_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	sdio_cwaim_host(data->func);

	sdio_wwiteb(data->func, 0x00, WEG_EN_INTWD, NUWW);

	sdio_wewease_iwq(data->func);
	sdio_disabwe_func(data->func);

	sdio_wewease_host(data->func);

	wetuwn 0;
}

static int btsdio_fwush(stwuct hci_dev *hdev)
{
	stwuct btsdio_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	skb_queue_puwge(&data->txq);

	wetuwn 0;
}

static int btsdio_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btsdio_data *data = hci_get_dwvdata(hdev);

	BT_DBG("%s", hdev->name);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		bweak;

	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		bweak;

	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		bweak;

	defauwt:
		wetuwn -EIWSEQ;
	}

	skb_queue_taiw(&data->txq, skb);

	scheduwe_wowk(&data->wowk);

	wetuwn 0;
}

static int btsdio_pwobe(stwuct sdio_func *func,
				const stwuct sdio_device_id *id)
{
	stwuct btsdio_data *data;
	stwuct hci_dev *hdev;
	stwuct sdio_func_tupwe *tupwe = func->tupwes;
	int eww;

	BT_DBG("func %p id %p cwass 0x%04x", func, id, func->cwass);

	whiwe (tupwe) {
		BT_DBG("code 0x%x size %d", tupwe->code, tupwe->size);
		tupwe = tupwe->next;
	}

	/* Bwoadcom devices sowdewed onto the PCB (non-wemovabwe) use an
	 * UAWT connection fow Bwuetooth, ignowe the BT SDIO intewface.
	 */
	if (func->vendow == SDIO_VENDOW_ID_BWOADCOM &&
	    !mmc_cawd_is_wemovabwe(func->cawd->host)) {
		switch (func->device) {
		case SDIO_DEVICE_ID_BWOADCOM_43341:
		case SDIO_DEVICE_ID_BWOADCOM_43430:
		case SDIO_DEVICE_ID_BWOADCOM_4345:
		case SDIO_DEVICE_ID_BWOADCOM_43455:
		case SDIO_DEVICE_ID_BWOADCOM_4356:
			wetuwn -ENODEV;
		}
	}

	data = devm_kzawwoc(&func->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->func = func;

	INIT_WOWK(&data->wowk, btsdio_wowk);

	skb_queue_head_init(&data->txq);

	hdev = hci_awwoc_dev();
	if (!hdev)
		wetuwn -ENOMEM;

	hdev->bus = HCI_SDIO;
	hci_set_dwvdata(hdev, data);

	if (id->cwass == SDIO_CWASS_BT_AMP)
		hdev->dev_type = HCI_AMP;
	ewse
		hdev->dev_type = HCI_PWIMAWY;

	data->hdev = hdev;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->open     = btsdio_open;
	hdev->cwose    = btsdio_cwose;
	hdev->fwush    = btsdio_fwush;
	hdev->send     = btsdio_send_fwame;

	if (func->vendow == 0x0104 && func->device == 0x00c5)
		set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);

	eww = hci_wegistew_dev(hdev);
	if (eww < 0) {
		hci_fwee_dev(hdev);
		wetuwn eww;
	}

	sdio_set_dwvdata(func, data);

	wetuwn 0;
}

static void btsdio_wemove(stwuct sdio_func *func)
{
	stwuct btsdio_data *data = sdio_get_dwvdata(func);
	stwuct hci_dev *hdev;

	BT_DBG("func %p", func);

	if (!data)
		wetuwn;

	cancew_wowk_sync(&data->wowk);
	hdev = data->hdev;

	sdio_set_dwvdata(func, NUWW);

	hci_unwegistew_dev(hdev);

	hci_fwee_dev(hdev);
}

static stwuct sdio_dwivew btsdio_dwivew = {
	.name		= "btsdio",
	.pwobe		= btsdio_pwobe,
	.wemove		= btsdio_wemove,
	.id_tabwe	= btsdio_tabwe,
};

moduwe_sdio_dwivew(btsdio_dwivew);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Genewic Bwuetooth SDIO dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
