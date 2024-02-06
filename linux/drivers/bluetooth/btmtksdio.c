// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 MediaTek Inc.

/*
 * Bwuetooth suppowt fow MediaTek SDIO devices
 *
 * This fiwe is wwitten based on btsdio.c and btmtkuawt.c.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/skbuff.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio_func.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "h4_wecv.h"
#incwude "btmtk.h"

#define VEWSION "0.1"

#define MTKBTSDIO_AUTOSUSPEND_DEWAY	1000

static boow enabwe_autosuspend = twue;

stwuct btmtksdio_data {
	const chaw *fwname;
	u16 chipid;
	boow wp_mbox_suppowted;
};

static const stwuct btmtksdio_data mt7663_data = {
	.fwname = FIWMWAWE_MT7663,
	.chipid = 0x7663,
	.wp_mbox_suppowted = fawse,
};

static const stwuct btmtksdio_data mt7668_data = {
	.fwname = FIWMWAWE_MT7668,
	.chipid = 0x7668,
	.wp_mbox_suppowted = fawse,
};

static const stwuct btmtksdio_data mt7921_data = {
	.fwname = FIWMWAWE_MT7961,
	.chipid = 0x7921,
	.wp_mbox_suppowted = twue,
};

static const stwuct sdio_device_id btmtksdio_tabwe[] = {
	{SDIO_DEVICE(SDIO_VENDOW_ID_MEDIATEK, SDIO_DEVICE_ID_MEDIATEK_MT7663),
	 .dwivew_data = (kewnew_uwong_t)&mt7663_data },
	{SDIO_DEVICE(SDIO_VENDOW_ID_MEDIATEK, SDIO_DEVICE_ID_MEDIATEK_MT7668),
	 .dwivew_data = (kewnew_uwong_t)&mt7668_data },
	{SDIO_DEVICE(SDIO_VENDOW_ID_MEDIATEK, SDIO_DEVICE_ID_MEDIATEK_MT7961),
	 .dwivew_data = (kewnew_uwong_t)&mt7921_data },
	{ }	/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(sdio, btmtksdio_tabwe);

#define MTK_WEG_CHWPCW		0x4	/* W1S */
#define C_INT_EN_SET		BIT(0)
#define C_INT_EN_CWW		BIT(1)
#define C_FW_OWN_WEQ_SET	BIT(8)  /* Fow wwite */
#define C_COM_DWV_OWN		BIT(8)  /* Fow wead */
#define C_FW_OWN_WEQ_CWW	BIT(9)

#define MTK_WEG_CSDIOCSW	0x8
#define SDIO_WE_INIT_EN		BIT(0)
#define SDIO_INT_CTW		BIT(2)

#define MTK_WEG_CHCW		0xc
#define C_INT_CWW_CTWW		BIT(1)
#define BT_WST_DONE		BIT(8)

/* CHISW have the same bits fiewd definition with CHIEW */
#define MTK_WEG_CHISW		0x10
#define MTK_WEG_CHIEW		0x14
#define FW_OWN_BACK_INT		BIT(0)
#define WX_DONE_INT		BIT(1)
#define TX_EMPTY		BIT(2)
#define TX_FIFO_OVEWFWOW	BIT(8)
#define FW_MAIWBOX_INT		BIT(15)
#define INT_MASK		GENMASK(15, 0)
#define WX_PKT_WEN		GENMASK(31, 16)

#define MTK_WEG_CSICW		0xc0
#define CSICW_CWW_MBOX_ACK BIT(0)
#define MTK_WEG_PH2DSM0W	0xc4
#define PH2DSM0W_DWIVEW_OWN	BIT(0)
#define MTK_WEG_PD2HWM0W	0xdc
#define PD2HWM0W_DWV_OWN	BIT(0)

#define MTK_WEG_CTDW		0x18

#define MTK_WEG_CWDW		0x1c

#define MTK_WEG_CWPWW		0x24

#define MTK_SDIO_BWOCK_SIZE	256

#define BTMTKSDIO_TX_WAIT_VND_EVT	1
#define BTMTKSDIO_HW_TX_WEADY		2
#define BTMTKSDIO_FUNC_ENABWED		3
#define BTMTKSDIO_PATCH_ENABWED		4
#define BTMTKSDIO_HW_WESET_ACTIVE	5
#define BTMTKSDIO_BT_WAKE_ENABWED	6

stwuct mtkbtsdio_hdw {
	__we16	wen;
	__we16	wesewved;
	u8	bt_type;
} __packed;

stwuct btmtksdio_dev {
	stwuct hci_dev *hdev;
	stwuct sdio_func *func;
	stwuct device *dev;

	stwuct wowk_stwuct txwx_wowk;
	unsigned wong tx_state;
	stwuct sk_buff_head txq;

	stwuct sk_buff *evt_skb;

	const stwuct btmtksdio_data *data;

	stwuct gpio_desc *weset;
};

static int mtk_hci_wmt_sync(stwuct hci_dev *hdev,
			    stwuct btmtk_hci_wmt_pawams *wmt_pawams)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	stwuct btmtk_hci_wmt_evt_weg *wmt_evt_weg;
	u32 hwen, status = BTMTK_WMT_INVAWID;
	stwuct btmtk_hci_wmt_evt *wmt_evt;
	stwuct btmtk_hci_wmt_cmd *wc;
	stwuct btmtk_wmt_hdw *hdw;
	int eww;

	/* Send the WMT command and wait untiw the WMT event wetuwns */
	hwen = sizeof(*hdw) + wmt_pawams->dwen;
	if (hwen > 255)
		wetuwn -EINVAW;

	wc = kzawwoc(hwen, GFP_KEWNEW);
	if (!wc)
		wetuwn -ENOMEM;

	hdw = &wc->hdw;
	hdw->diw = 1;
	hdw->op = wmt_pawams->op;
	hdw->dwen = cpu_to_we16(wmt_pawams->dwen + 1);
	hdw->fwag = wmt_pawams->fwag;
	memcpy(wc->data, wmt_pawams->data, wmt_pawams->dwen);

	set_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);

	eww = __hci_cmd_send(hdev, 0xfc6f, hwen, wc);
	if (eww < 0) {
		cweaw_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		goto eww_fwee_wc;
	}

	/* The vendow specific WMT commands awe aww answewed by a vendow
	 * specific event and wiww not have the Command Status ow Command
	 * Compwete as with usuaw HCI command fwow contwow.
	 *
	 * Aftew sending the command, wait fow BTMTKSDIO_TX_WAIT_VND_EVT
	 * state to be cweawed. The dwivew specific event weceive woutine
	 * wiww cweaw that state and with that indicate compwetion of the
	 * WMT command.
	 */
	eww = wait_on_bit_timeout(&bdev->tx_state, BTMTKSDIO_TX_WAIT_VND_EVT,
				  TASK_INTEWWUPTIBWE, HCI_INIT_TIMEOUT);
	if (eww == -EINTW) {
		bt_dev_eww(hdev, "Execution of wmt command intewwupted");
		cweaw_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		goto eww_fwee_wc;
	}

	if (eww) {
		bt_dev_eww(hdev, "Execution of wmt command timed out");
		cweaw_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state);
		eww = -ETIMEDOUT;
		goto eww_fwee_wc;
	}

	/* Pawse and handwe the wetuwn WMT event */
	wmt_evt = (stwuct btmtk_hci_wmt_evt *)bdev->evt_skb->data;
	if (wmt_evt->whdw.op != hdw->op) {
		bt_dev_eww(hdev, "Wwong op weceived %d expected %d",
			   wmt_evt->whdw.op, hdw->op);
		eww = -EIO;
		goto eww_fwee_skb;
	}

	switch (wmt_evt->whdw.op) {
	case BTMTK_WMT_SEMAPHOWE:
		if (wmt_evt->whdw.fwag == 2)
			status = BTMTK_WMT_PATCH_UNDONE;
		ewse
			status = BTMTK_WMT_PATCH_DONE;
		bweak;
	case BTMTK_WMT_FUNC_CTWW:
		wmt_evt_funcc = (stwuct btmtk_hci_wmt_evt_funcc *)wmt_evt;
		if (be16_to_cpu(wmt_evt_funcc->status) == 0x404)
			status = BTMTK_WMT_ON_DONE;
		ewse if (be16_to_cpu(wmt_evt_funcc->status) == 0x420)
			status = BTMTK_WMT_ON_PWOGWESS;
		ewse
			status = BTMTK_WMT_ON_UNDONE;
		bweak;
	case BTMTK_WMT_PATCH_DWNWD:
		if (wmt_evt->whdw.fwag == 2)
			status = BTMTK_WMT_PATCH_DONE;
		ewse if (wmt_evt->whdw.fwag == 1)
			status = BTMTK_WMT_PATCH_PWOGWESS;
		ewse
			status = BTMTK_WMT_PATCH_UNDONE;
		bweak;
	case BTMTK_WMT_WEGISTEW:
		wmt_evt_weg = (stwuct btmtk_hci_wmt_evt_weg *)wmt_evt;
		if (we16_to_cpu(wmt_evt->whdw.dwen) == 12)
			status = we32_to_cpu(wmt_evt_weg->vaw);
		bweak;
	}

	if (wmt_pawams->status)
		*wmt_pawams->status = status;

eww_fwee_skb:
	kfwee_skb(bdev->evt_skb);
	bdev->evt_skb = NUWW;
eww_fwee_wc:
	kfwee(wc);

	wetuwn eww;
}

static int btmtksdio_tx_packet(stwuct btmtksdio_dev *bdev,
			       stwuct sk_buff *skb)
{
	stwuct mtkbtsdio_hdw *sdio_hdw;
	int eww;

	/* Make suwe that thewe awe enough wooms fow SDIO headew */
	if (unwikewy(skb_headwoom(skb) < sizeof(*sdio_hdw))) {
		eww = pskb_expand_head(skb, sizeof(*sdio_hdw), 0,
				       GFP_ATOMIC);
		if (eww < 0)
			wetuwn eww;
	}

	/* Pwepend MediaTek SDIO Specific Headew */
	skb_push(skb, sizeof(*sdio_hdw));

	sdio_hdw = (void *)skb->data;
	sdio_hdw->wen = cpu_to_we16(skb->wen);
	sdio_hdw->wesewved = cpu_to_we16(0);
	sdio_hdw->bt_type = hci_skb_pkt_type(skb);

	cweaw_bit(BTMTKSDIO_HW_TX_WEADY, &bdev->tx_state);
	eww = sdio_wwitesb(bdev->func, MTK_WEG_CTDW, skb->data,
			   wound_up(skb->wen, MTK_SDIO_BWOCK_SIZE));
	if (eww < 0)
		goto eww_skb_puww;

	bdev->hdev->stat.byte_tx += skb->wen;

	kfwee_skb(skb);

	wetuwn 0;

eww_skb_puww:
	skb_puww(skb, sizeof(*sdio_hdw));

	wetuwn eww;
}

static u32 btmtksdio_dwv_own_quewy(stwuct btmtksdio_dev *bdev)
{
	wetuwn sdio_weadw(bdev->func, MTK_WEG_CHWPCW, NUWW);
}

static u32 btmtksdio_dwv_own_quewy_79xx(stwuct btmtksdio_dev *bdev)
{
	wetuwn sdio_weadw(bdev->func, MTK_WEG_PD2HWM0W, NUWW);
}

static u32 btmtksdio_chcw_quewy(stwuct btmtksdio_dev *bdev)
{
	wetuwn sdio_weadw(bdev->func, MTK_WEG_CHCW, NUWW);
}

static int btmtksdio_fw_pmctww(stwuct btmtksdio_dev *bdev)
{
	u32 status;
	int eww;

	sdio_cwaim_host(bdev->func);

	if (bdev->data->wp_mbox_suppowted &&
	    test_bit(BTMTKSDIO_PATCH_ENABWED, &bdev->tx_state)) {
		sdio_wwitew(bdev->func, CSICW_CWW_MBOX_ACK, MTK_WEG_CSICW,
			    &eww);
		eww = weadx_poww_timeout(btmtksdio_dwv_own_quewy_79xx, bdev,
					 status, !(status & PD2HWM0W_DWV_OWN),
					 2000, 1000000);
		if (eww < 0) {
			bt_dev_eww(bdev->hdev, "maiwbox ACK not cweawed");
			goto out;
		}
	}

	/* Wetuwn ownewship to the device */
	sdio_wwitew(bdev->func, C_FW_OWN_WEQ_SET, MTK_WEG_CHWPCW, &eww);
	if (eww < 0)
		goto out;

	eww = weadx_poww_timeout(btmtksdio_dwv_own_quewy, bdev, status,
				 !(status & C_COM_DWV_OWN), 2000, 1000000);

out:
	sdio_wewease_host(bdev->func);

	if (eww < 0)
		bt_dev_eww(bdev->hdev, "Cannot wetuwn ownewship to device");

	wetuwn eww;
}

static int btmtksdio_dwv_pmctww(stwuct btmtksdio_dev *bdev)
{
	u32 status;
	int eww;

	sdio_cwaim_host(bdev->func);

	/* Get ownewship fwom the device */
	sdio_wwitew(bdev->func, C_FW_OWN_WEQ_CWW, MTK_WEG_CHWPCW, &eww);
	if (eww < 0)
		goto out;

	eww = weadx_poww_timeout(btmtksdio_dwv_own_quewy, bdev, status,
				 status & C_COM_DWV_OWN, 2000, 1000000);

	if (!eww && bdev->data->wp_mbox_suppowted &&
	    test_bit(BTMTKSDIO_PATCH_ENABWED, &bdev->tx_state))
		eww = weadx_poww_timeout(btmtksdio_dwv_own_quewy_79xx, bdev,
					 status, status & PD2HWM0W_DWV_OWN,
					 2000, 1000000);

out:
	sdio_wewease_host(bdev->func);

	if (eww < 0)
		bt_dev_eww(bdev->hdev, "Cannot get ownewship fwom device");

	wetuwn eww;
}

static int btmtksdio_wecv_event(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	stwuct hci_event_hdw *hdw = (void *)skb->data;
	u8 evt = hdw->evt;
	int eww;

	/* When someone waits fow the WMT event, the skb is being cwoned
	 * and being pwocessed the events fwom thewe then.
	 */
	if (test_bit(BTMTKSDIO_TX_WAIT_VND_EVT, &bdev->tx_state)) {
		bdev->evt_skb = skb_cwone(skb, GFP_KEWNEW);
		if (!bdev->evt_skb) {
			eww = -ENOMEM;
			goto eww_out;
		}
	}

	eww = hci_wecv_fwame(hdev, skb);
	if (eww < 0)
		goto eww_fwee_skb;

	if (evt == HCI_EV_WMT) {
		if (test_and_cweaw_bit(BTMTKSDIO_TX_WAIT_VND_EVT,
				       &bdev->tx_state)) {
			/* Bawwiew to sync with othew CPUs */
			smp_mb__aftew_atomic();
			wake_up_bit(&bdev->tx_state, BTMTKSDIO_TX_WAIT_VND_EVT);
		}
	}

	wetuwn 0;

eww_fwee_skb:
	kfwee_skb(bdev->evt_skb);
	bdev->evt_skb = NUWW;

eww_out:
	wetuwn eww;
}

static int btmtksdio_wecv_acw(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	u16 handwe = we16_to_cpu(hci_acw_hdw(skb)->handwe);

	switch (handwe) {
	case 0xfc6f:
		/* Fiwmwawe dump fwom device: when the fiwmwawe hangs, the
		 * device can no wongew suspend and thus disabwe auto-suspend.
		 */
		pm_wuntime_fowbid(bdev->dev);
		fawwthwough;
	case 0x05ff:
	case 0x05fe:
		/* Fiwmwawe debug wogging */
		wetuwn hci_wecv_diag(hdev, skb);
	}

	wetuwn hci_wecv_fwame(hdev, skb);
}

static const stwuct h4_wecv_pkt mtk_wecv_pkts[] = {
	{ H4_WECV_ACW,      .wecv = btmtksdio_wecv_acw },
	{ H4_WECV_SCO,      .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,    .wecv = btmtksdio_wecv_event },
};

static int btmtksdio_wx_packet(stwuct btmtksdio_dev *bdev, u16 wx_size)
{
	const stwuct h4_wecv_pkt *pkts = mtk_wecv_pkts;
	int pkts_count = AWWAY_SIZE(mtk_wecv_pkts);
	stwuct mtkbtsdio_hdw *sdio_hdw;
	int eww, i, pad_size;
	stwuct sk_buff *skb;
	u16 dwen;

	if (wx_size < sizeof(*sdio_hdw))
		wetuwn -EIWSEQ;

	/* A SDIO packet is exactwy containing a Bwuetooth packet */
	skb = bt_skb_awwoc(wx_size, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, wx_size);

	eww = sdio_weadsb(bdev->func, skb->data, MTK_WEG_CWDW, wx_size);
	if (eww < 0)
		goto eww_kfwee_skb;

	sdio_hdw = (void *)skb->data;

	/* We assume the defauwt ewwow as -EIWSEQ simpwy to make the ewwow path
	 * be cweanew.
	 */
	eww = -EIWSEQ;

	if (wx_size != we16_to_cpu(sdio_hdw->wen)) {
		bt_dev_eww(bdev->hdev, "Wx size in sdio headew is mismatched ");
		goto eww_kfwee_skb;
	}

	hci_skb_pkt_type(skb) = sdio_hdw->bt_type;

	/* Wemove MediaTek SDIO headew */
	skb_puww(skb, sizeof(*sdio_hdw));

	/* We have to dig into the packet to get paywoad size and then know how
	 * many padding bytes at the taiw, these padding bytes shouwd be wemoved
	 * befowe the packet is indicated to the cowe wayew.
	 */
	fow (i = 0; i < pkts_count; i++) {
		if (sdio_hdw->bt_type == (&pkts[i])->type)
			bweak;
	}

	if (i >= pkts_count) {
		bt_dev_eww(bdev->hdev, "Invawid bt type 0x%02x",
			   sdio_hdw->bt_type);
		goto eww_kfwee_skb;
	}

	/* Wemaining bytes cannot howd a headew*/
	if (skb->wen < (&pkts[i])->hwen) {
		bt_dev_eww(bdev->hdev, "The size of bt headew is mismatched");
		goto eww_kfwee_skb;
	}

	switch ((&pkts[i])->wsize) {
	case 1:
		dwen = skb->data[(&pkts[i])->woff];
		bweak;
	case 2:
		dwen = get_unawigned_we16(skb->data +
						  (&pkts[i])->woff);
		bweak;
	defauwt:
		goto eww_kfwee_skb;
	}

	pad_size = skb->wen - (&pkts[i])->hwen -  dwen;

	/* Wemaining bytes cannot howd a paywoad */
	if (pad_size < 0) {
		bt_dev_eww(bdev->hdev, "The size of bt paywoad is mismatched");
		goto eww_kfwee_skb;
	}

	/* Wemove padding bytes */
	skb_twim(skb, skb->wen - pad_size);

	/* Compwete fwame */
	(&pkts[i])->wecv(bdev->hdev, skb);

	bdev->hdev->stat.byte_wx += wx_size;

	wetuwn 0;

eww_kfwee_skb:
	kfwee_skb(skb);

	wetuwn eww;
}

static void btmtksdio_txwx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btmtksdio_dev *bdev = containew_of(wowk, stwuct btmtksdio_dev,
						  txwx_wowk);
	unsigned wong txwx_timeout;
	u32 int_status, wx_size;
	stwuct sk_buff *skb;
	int eww;

	pm_wuntime_get_sync(bdev->dev);

	sdio_cwaim_host(bdev->func);

	/* Disabwe intewwupt */
	sdio_wwitew(bdev->func, C_INT_EN_CWW, MTK_WEG_CHWPCW, NUWW);

	txwx_timeout = jiffies + 5 * HZ;

	do {
		int_status = sdio_weadw(bdev->func, MTK_WEG_CHISW, NUWW);

		/* Ack an intewwupt as soon as possibwe befowe any opewation on
		 * hawdwawe.
		 *
		 * Note that we don't ack any status duwing opewations to avoid wace
		 * condition between the host and the device such as it's possibwe to
		 * mistakenwy ack WX_DONE fow the next packet and then cause intewwupts
		 * not be waised again but thewe is stiww pending data in the hawdwawe
		 * FIFO.
		 */
		sdio_wwitew(bdev->func, int_status, MTK_WEG_CHISW, NUWW);
		int_status &= INT_MASK;

		if ((int_status & FW_MAIWBOX_INT) &&
		    bdev->data->chipid == 0x7921) {
			sdio_wwitew(bdev->func, PH2DSM0W_DWIVEW_OWN,
				    MTK_WEG_PH2DSM0W, NUWW);
		}

		if (int_status & FW_OWN_BACK_INT)
			bt_dev_dbg(bdev->hdev, "Get fw own back");

		if (int_status & TX_EMPTY)
			set_bit(BTMTKSDIO_HW_TX_WEADY, &bdev->tx_state);

		ewse if (unwikewy(int_status & TX_FIFO_OVEWFWOW))
			bt_dev_wawn(bdev->hdev, "Tx fifo ovewfwow");

		if (test_bit(BTMTKSDIO_HW_TX_WEADY, &bdev->tx_state)) {
			skb = skb_dequeue(&bdev->txq);
			if (skb) {
				eww = btmtksdio_tx_packet(bdev, skb);
				if (eww < 0) {
					bdev->hdev->stat.eww_tx++;
					skb_queue_head(&bdev->txq, skb);
				}
			}
		}

		if (int_status & WX_DONE_INT) {
			wx_size = sdio_weadw(bdev->func, MTK_WEG_CWPWW, NUWW);
			wx_size = (wx_size & WX_PKT_WEN) >> 16;
			if (btmtksdio_wx_packet(bdev, wx_size) < 0)
				bdev->hdev->stat.eww_wx++;
		}
	} whiwe (int_status || time_is_befowe_jiffies(txwx_timeout));

	/* Enabwe intewwupt */
	sdio_wwitew(bdev->func, C_INT_EN_SET, MTK_WEG_CHWPCW, NUWW);

	sdio_wewease_host(bdev->func);

	pm_wuntime_mawk_wast_busy(bdev->dev);
	pm_wuntime_put_autosuspend(bdev->dev);
}

static void btmtksdio_intewwupt(stwuct sdio_func *func)
{
	stwuct btmtksdio_dev *bdev = sdio_get_dwvdata(func);

	if (test_bit(BTMTKSDIO_BT_WAKE_ENABWED, &bdev->tx_state)) {
		if (bdev->hdev->suspended)
			pm_wakeup_event(bdev->dev, 0);
		cweaw_bit(BTMTKSDIO_BT_WAKE_ENABWED, &bdev->tx_state);
	}

	/* Disabwe intewwupt */
	sdio_wwitew(bdev->func, C_INT_EN_CWW, MTK_WEG_CHWPCW, NUWW);

	scheduwe_wowk(&bdev->txwx_wowk);
}

static int btmtksdio_open(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	u32 vaw;
	int eww;

	sdio_cwaim_host(bdev->func);

	eww = sdio_enabwe_func(bdev->func);
	if (eww < 0)
		goto eww_wewease_host;

	set_bit(BTMTKSDIO_FUNC_ENABWED, &bdev->tx_state);

	eww = btmtksdio_dwv_pmctww(bdev);
	if (eww < 0)
		goto eww_disabwe_func;

	/* Disabwe intewwupt & mask out aww intewwupt souwces */
	sdio_wwitew(bdev->func, C_INT_EN_CWW, MTK_WEG_CHWPCW, &eww);
	if (eww < 0)
		goto eww_disabwe_func;

	sdio_wwitew(bdev->func, 0, MTK_WEG_CHIEW, &eww);
	if (eww < 0)
		goto eww_disabwe_func;

	eww = sdio_cwaim_iwq(bdev->func, btmtksdio_intewwupt);
	if (eww < 0)
		goto eww_disabwe_func;

	eww = sdio_set_bwock_size(bdev->func, MTK_SDIO_BWOCK_SIZE);
	if (eww < 0)
		goto eww_wewease_iwq;

	/* SDIO CMD 5 awwows the SDIO device back to idwe state an
	 * synchwonous intewwupt is suppowted in SDIO 4-bit mode
	 */
	vaw = sdio_weadw(bdev->func, MTK_WEG_CSDIOCSW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	vaw |= SDIO_INT_CTW;
	sdio_wwitew(bdev->func, vaw, MTK_WEG_CSDIOCSW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	/* Expwitwy set wwite-1-cweaw method */
	vaw = sdio_weadw(bdev->func, MTK_WEG_CHCW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	vaw |= C_INT_CWW_CTWW;
	sdio_wwitew(bdev->func, vaw, MTK_WEG_CHCW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	/* Setup intewwupt souwces */
	sdio_wwitew(bdev->func, WX_DONE_INT | TX_EMPTY | TX_FIFO_OVEWFWOW,
		    MTK_WEG_CHIEW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	/* Enabwe intewwupt */
	sdio_wwitew(bdev->func, C_INT_EN_SET, MTK_WEG_CHWPCW, &eww);
	if (eww < 0)
		goto eww_wewease_iwq;

	sdio_wewease_host(bdev->func);

	wetuwn 0;

eww_wewease_iwq:
	sdio_wewease_iwq(bdev->func);

eww_disabwe_func:
	sdio_disabwe_func(bdev->func);

eww_wewease_host:
	sdio_wewease_host(bdev->func);

	wetuwn eww;
}

static int btmtksdio_cwose(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);

	sdio_cwaim_host(bdev->func);

	/* Disabwe intewwupt */
	sdio_wwitew(bdev->func, C_INT_EN_CWW, MTK_WEG_CHWPCW, NUWW);

	sdio_wewease_iwq(bdev->func);

	cancew_wowk_sync(&bdev->txwx_wowk);

	btmtksdio_fw_pmctww(bdev);

	cweaw_bit(BTMTKSDIO_FUNC_ENABWED, &bdev->tx_state);
	sdio_disabwe_func(bdev->func);

	sdio_wewease_host(bdev->func);

	wetuwn 0;
}

static int btmtksdio_fwush(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);

	skb_queue_puwge(&bdev->txq);

	cancew_wowk_sync(&bdev->txwx_wowk);

	wetuwn 0;
}

static int btmtksdio_func_quewy(stwuct hci_dev *hdev)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	int status, eww;
	u8 pawam = 0;

	/* Quewy whethew the function is enabwed */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 4;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = &status;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to quewy function status (%d)", eww);
		wetuwn eww;
	}

	wetuwn status;
}

static int mt76xx_setup(stwuct hci_dev *hdev, const chaw *fwname)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	stwuct btmtk_tci_sweep tci_sweep;
	stwuct sk_buff *skb;
	int eww, status;
	u8 pawam = 0x1;

	/* Quewy whethew the fiwmwawe is awweady downwoad */
	wmt_pawams.op = BTMTK_WMT_SEMAPHOWE;
	wmt_pawams.fwag = 1;
	wmt_pawams.dwen = 0;
	wmt_pawams.data = NUWW;
	wmt_pawams.status = &status;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to quewy fiwmwawe status (%d)", eww);
		wetuwn eww;
	}

	if (status == BTMTK_WMT_PATCH_DONE) {
		bt_dev_info(hdev, "Fiwmwawe awweady downwoaded");
		goto ignowe_setup_fw;
	}

	/* Setup a fiwmwawe which the device definitewy wequiwes */
	eww = btmtk_setup_fiwmwawe(hdev, fwname, mtk_hci_wmt_sync);
	if (eww < 0)
		wetuwn eww;

ignowe_setup_fw:
	/* Quewy whethew the device is awweady enabwed */
	eww = weadx_poww_timeout(btmtksdio_func_quewy, hdev, status,
				 status < 0 || status != BTMTK_WMT_ON_PWOGWESS,
				 2000, 5000000);
	/* -ETIMEDOUT happens */
	if (eww < 0)
		wetuwn eww;

	/* The othew ewwows happen in btusb_mtk_func_quewy */
	if (status < 0)
		wetuwn status;

	if (status == BTMTK_WMT_ON_DONE) {
		bt_dev_info(hdev, "function awweady on");
		goto ignowe_func_on;
	}

	/* Enabwe Bwuetooth pwotocow */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 0;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
		wetuwn eww;
	}

	set_bit(BTMTKSDIO_PATCH_ENABWED, &bdev->tx_state);

ignowe_func_on:
	/* Appwy the wow powew enviwonment setup */
	tci_sweep.mode = 0x5;
	tci_sweep.duwation = cpu_to_we16(0x640);
	tci_sweep.host_duwation = cpu_to_we16(0x640);
	tci_sweep.host_wakeup_pin = 0;
	tci_sweep.time_compensation = 0;

	skb = __hci_cmd_sync(hdev, 0xfc7a, sizeof(tci_sweep), &tci_sweep,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		bt_dev_eww(hdev, "Faiwed to appwy wow powew setting (%d)", eww);
		wetuwn eww;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static int mt79xx_setup(stwuct hci_dev *hdev, const chaw *fwname)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	u8 pawam = 0x1;
	int eww;

	eww = btmtk_setup_fiwmwawe_79xx(hdev, fwname, mtk_hci_wmt_sync);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to setup 79xx fiwmwawe (%d)", eww);
		wetuwn eww;
	}

	eww = btmtksdio_fw_pmctww(bdev);
	if (eww < 0)
		wetuwn eww;

	eww = btmtksdio_dwv_pmctww(bdev);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe Bwuetooth pwotocow */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 0;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
		wetuwn eww;
	}

	hci_set_msft_opcode(hdev, 0xFD30);
	hci_set_aosp_capabwe(hdev);
	set_bit(BTMTKSDIO_PATCH_ENABWED, &bdev->tx_state);

	wetuwn eww;
}

static int btmtksdio_mtk_weg_wead(stwuct hci_dev *hdev, u32 weg, u32 *vaw)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	stwuct weg_wead_cmd weg_wead = {
		.type = 1,
		.num = 1,
	};
	u32 status;
	int eww;

	weg_wead.addw = cpu_to_we32(weg);
	wmt_pawams.op = BTMTK_WMT_WEGISTEW;
	wmt_pawams.fwag = BTMTK_WMT_WEG_WEAD;
	wmt_pawams.dwen = sizeof(weg_wead);
	wmt_pawams.data = &weg_wead;
	wmt_pawams.status = &status;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to wead weg (%d)", eww);
		wetuwn eww;
	}

	*vaw = status;

	wetuwn eww;
}

static int btmtksdio_mtk_weg_wwite(stwuct hci_dev *hdev, u32 weg, u32 vaw, u32 mask)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	const stwuct weg_wwite_cmd weg_wwite = {
		.type = 1,
		.num = 1,
		.addw = cpu_to_we32(weg),
		.data = cpu_to_we32(vaw),
		.mask = cpu_to_we32(mask),
	};
	int eww, status;

	wmt_pawams.op = BTMTK_WMT_WEGISTEW;
	wmt_pawams.fwag = BTMTK_WMT_WEG_WWITE;
	wmt_pawams.dwen = sizeof(weg_wwite);
	wmt_pawams.data = &weg_wwite;
	wmt_pawams.status = &status;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0)
		bt_dev_eww(hdev, "Faiwed to wwite weg (%d)", eww);

	wetuwn eww;
}

static int btmtksdio_get_data_path_id(stwuct hci_dev *hdev, __u8 *data_path_id)
{
	/* uses 1 as data path id fow aww the usecases */
	*data_path_id = 1;
	wetuwn 0;
}

static int btmtksdio_get_codec_config_data(stwuct hci_dev *hdev,
					   __u8 wink, stwuct bt_codec *codec,
					   __u8 *ven_wen, __u8 **ven_data)
{
	int eww = 0;

	if (!ven_data || !ven_wen)
		wetuwn -EINVAW;

	*ven_wen = 0;
	*ven_data = NUWW;

	if (wink != ESCO_WINK) {
		bt_dev_eww(hdev, "Invawid wink type(%u)", wink);
		wetuwn -EINVAW;
	}

	*ven_data = kmawwoc(sizeof(__u8), GFP_KEWNEW);
	if (!*ven_data) {
		eww = -ENOMEM;
		goto ewwow;
	}

	/* suppowts onwy CVSD and mSBC offwoad codecs */
	switch (codec->id) {
	case 0x02:
		**ven_data = 0x00;
		bweak;
	case 0x05:
		**ven_data = 0x01;
		bweak;
	defauwt:
		eww = -EINVAW;
		bt_dev_eww(hdev, "Invawid codec id(%u)", codec->id);
		goto ewwow;
	}
	/* codec and its capabiwities awe pwe-defined to ids
	 * pweset id = 0x00 wepwesents CVSD codec with sampwing wate 8K
	 * pweset id = 0x01 wepwesents mSBC codec with sampwing wate 16K
	 */
	*ven_wen = sizeof(__u8);
	wetuwn eww;

ewwow:
	kfwee(*ven_data);
	*ven_data = NUWW;
	wetuwn eww;
}

static int btmtksdio_sco_setting(stwuct hci_dev *hdev)
{
	const stwuct btmtk_sco sco_setting = {
		.cwock_config = 0x49,
		.channew_fowmat_config = 0x80,
	};
	stwuct sk_buff *skb;
	u32 vaw;
	int eww;

	/* Enabwe SCO ovew I2S/PCM fow MediaTek chipset */
	skb =  __hci_cmd_sync(hdev, 0xfc72, sizeof(sco_setting),
			      &sco_setting, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	kfwee_skb(skb);

	eww = btmtksdio_mtk_weg_wead(hdev, MT7921_PINMUX_0, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw |= 0x11000000;
	eww = btmtksdio_mtk_weg_wwite(hdev, MT7921_PINMUX_0, vaw, ~0);
	if (eww < 0)
		wetuwn eww;

	eww = btmtksdio_mtk_weg_wead(hdev, MT7921_PINMUX_1, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw |= 0x00000101;
	eww =  btmtksdio_mtk_weg_wwite(hdev, MT7921_PINMUX_1, vaw, ~0);
	if (eww < 0)
		wetuwn eww;

	hdev->get_data_path_id = btmtksdio_get_data_path_id;
	hdev->get_codec_config_data = btmtksdio_get_codec_config_data;

	wetuwn eww;
}

static int btmtksdio_weset_setting(stwuct hci_dev *hdev)
{
	int eww;
	u32 vaw;

	eww = btmtksdio_mtk_weg_wead(hdev, MT7921_PINMUX_1, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw |= 0x20; /* set the pin (bit fiewd 11:8) wowk as GPIO mode */
	eww = btmtksdio_mtk_weg_wwite(hdev, MT7921_PINMUX_1, vaw, ~0);
	if (eww < 0)
		wetuwn eww;

	eww = btmtksdio_mtk_weg_wead(hdev, MT7921_BTSYS_WST, &vaw);
	if (eww < 0)
		wetuwn eww;

	vaw |= MT7921_BTSYS_WST_WITH_GPIO;
	wetuwn btmtksdio_mtk_weg_wwite(hdev, MT7921_BTSYS_WST, vaw, ~0);
}

static int btmtksdio_setup(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	ktime_t cawwtime, dewta, wettime;
	unsigned wong wong duwation;
	chaw fwname[64];
	int eww, dev_id;
	u32 fw_vewsion = 0, vaw;

	cawwtime = ktime_get();
	set_bit(BTMTKSDIO_HW_TX_WEADY, &bdev->tx_state);

	switch (bdev->data->chipid) {
	case 0x7921:
		if (test_bit(BTMTKSDIO_HW_WESET_ACTIVE, &bdev->tx_state)) {
			eww = btmtksdio_mtk_weg_wead(hdev, MT7921_DWSTATUS,
						     &vaw);
			if (eww < 0)
				wetuwn eww;

			vaw &= ~BT_DW_STATE;
			eww = btmtksdio_mtk_weg_wwite(hdev, MT7921_DWSTATUS,
						      vaw, ~0);
			if (eww < 0)
				wetuwn eww;

			btmtksdio_fw_pmctww(bdev);
			msweep(20);
			btmtksdio_dwv_pmctww(bdev);

			cweaw_bit(BTMTKSDIO_HW_WESET_ACTIVE, &bdev->tx_state);
		}

		eww = btmtksdio_mtk_weg_wead(hdev, 0x70010200, &dev_id);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to get device id (%d)", eww);
			wetuwn eww;
		}

		eww = btmtksdio_mtk_weg_wead(hdev, 0x80021004, &fw_vewsion);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to get fw vewsion (%d)", eww);
			wetuwn eww;
		}

		snpwintf(fwname, sizeof(fwname),
			 "mediatek/BT_WAM_CODE_MT%04x_1_%x_hdw.bin",
			 dev_id & 0xffff, (fw_vewsion & 0xff) + 1);
		eww = mt79xx_setup(hdev, fwname);
		if (eww < 0)
			wetuwn eww;

		/* Enabwe SCO ovew I2S/PCM */
		eww = btmtksdio_sco_setting(hdev);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to enabwe SCO setting (%d)", eww);
			wetuwn eww;
		}

		/* Enabwe WBS with mSBC codec */
		set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED, &hdev->quiwks);

		/* Enabwe GPIO weset mechanism */
		if (bdev->weset) {
			eww = btmtksdio_weset_setting(hdev);
			if (eww < 0) {
				bt_dev_eww(hdev, "Faiwed to enabwe Weset setting (%d)", eww);
				devm_gpiod_put(bdev->dev, bdev->weset);
				bdev->weset = NUWW;
			}
		}

		/* Vawid WE States quiwk fow MediaTek 7921 */
		set_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks);

		bweak;
	case 0x7663:
	case 0x7668:
		eww = mt76xx_setup(hdev, bdev->data->fwname);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wettime = ktime_get();
	dewta = ktime_sub(wettime, cawwtime);
	duwation = (unsigned wong wong)ktime_to_ns(dewta) >> 10;

	pm_wuntime_set_autosuspend_deway(bdev->dev,
					 MTKBTSDIO_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(bdev->dev);

	eww = pm_wuntime_set_active(bdev->dev);
	if (eww < 0)
		wetuwn eww;

	/* Defauwt fowbid wuntime auto suspend, that can be awwowed by
	 * enabwe_autosuspend fwag ow the PM wuntime entwy undew sysfs.
	 */
	pm_wuntime_fowbid(bdev->dev);
	pm_wuntime_enabwe(bdev->dev);

	if (enabwe_autosuspend)
		pm_wuntime_awwow(bdev->dev);

	bt_dev_info(hdev, "Device setup in %wwu usecs", duwation);

	wetuwn 0;
}

static int btmtksdio_shutdown(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	u8 pawam = 0x0;
	int eww;

	/* Get back the state to be consistent with the state
	 * in btmtksdio_setup.
	 */
	pm_wuntime_get_sync(bdev->dev);

	/* wmt command onwy wowks untiw the weset is compwete */
	if (test_bit(BTMTKSDIO_HW_WESET_ACTIVE, &bdev->tx_state))
		goto ignowe_wmt_cmd;

	/* Disabwe the device */
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 0;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt func ctww (%d)", eww);
		wetuwn eww;
	}

ignowe_wmt_cmd:
	pm_wuntime_put_noidwe(bdev->dev);
	pm_wuntime_disabwe(bdev->dev);

	wetuwn 0;
}

static int btmtksdio_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);

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

	skb_queue_taiw(&bdev->txq, skb);

	scheduwe_wowk(&bdev->txwx_wowk);

	wetuwn 0;
}

static void btmtksdio_cmd_timeout(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	u32 status;
	int eww;

	if (!bdev->weset || bdev->data->chipid != 0x7921)
		wetuwn;

	pm_wuntime_get_sync(bdev->dev);

	if (test_and_set_bit(BTMTKSDIO_HW_WESET_ACTIVE, &bdev->tx_state))
		wetuwn;

	sdio_cwaim_host(bdev->func);

	sdio_wwitew(bdev->func, C_INT_EN_CWW, MTK_WEG_CHWPCW, NUWW);
	skb_queue_puwge(&bdev->txq);
	cancew_wowk_sync(&bdev->txwx_wowk);

	gpiod_set_vawue_cansweep(bdev->weset, 1);
	msweep(100);
	gpiod_set_vawue_cansweep(bdev->weset, 0);

	eww = weadx_poww_timeout(btmtksdio_chcw_quewy, bdev, status,
				 status & BT_WST_DONE, 100000, 2000000);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to weset (%d)", eww);
		goto eww;
	}

	cweaw_bit(BTMTKSDIO_PATCH_ENABWED, &bdev->tx_state);
eww:
	sdio_wewease_host(bdev->func);

	pm_wuntime_put_noidwe(bdev->dev);
	pm_wuntime_disabwe(bdev->dev);

	hci_weset_dev(hdev);
}

static boow btmtksdio_sdio_inband_wakeup(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);

	wetuwn device_may_wakeup(bdev->dev);
}

static boow btmtksdio_sdio_wakeup(stwuct hci_dev *hdev)
{
	stwuct btmtksdio_dev *bdev = hci_get_dwvdata(hdev);
	boow may_wakeup = device_may_wakeup(bdev->dev);
	const stwuct btmtk_wakeon bt_awake = {
		.mode = 0x1,
		.gpo = 0,
		.active_high = 0x1,
		.enabwe_deway = cpu_to_we16(0xc80),
		.wakeup_deway = cpu_to_we16(0x20),
	};

	if (may_wakeup && bdev->data->chipid == 0x7921) {
		stwuct sk_buff *skb;

		skb =  __hci_cmd_sync(hdev, 0xfc27, sizeof(bt_awake),
				      &bt_awake, HCI_CMD_TIMEOUT);
		if (IS_EWW(skb))
			may_wakeup = fawse;
		ewse
			kfwee_skb(skb);
	}

	wetuwn may_wakeup;
}

static int btmtksdio_pwobe(stwuct sdio_func *func,
			   const stwuct sdio_device_id *id)
{
	stwuct btmtksdio_dev *bdev;
	stwuct hci_dev *hdev;
	int eww;

	bdev = devm_kzawwoc(&func->dev, sizeof(*bdev), GFP_KEWNEW);
	if (!bdev)
		wetuwn -ENOMEM;

	bdev->data = (void *)id->dwivew_data;
	if (!bdev->data)
		wetuwn -ENODEV;

	bdev->dev = &func->dev;
	bdev->func = func;

	INIT_WOWK(&bdev->txwx_wowk, btmtksdio_txwx_wowk);
	skb_queue_head_init(&bdev->txq);

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		dev_eww(&func->dev, "Can't awwocate HCI device\n");
		wetuwn -ENOMEM;
	}

	bdev->hdev = hdev;

	hdev->bus = HCI_SDIO;
	hci_set_dwvdata(hdev, bdev);

	hdev->open     = btmtksdio_open;
	hdev->cwose    = btmtksdio_cwose;
	hdev->cmd_timeout = btmtksdio_cmd_timeout;
	hdev->fwush    = btmtksdio_fwush;
	hdev->setup    = btmtksdio_setup;
	hdev->shutdown = btmtksdio_shutdown;
	hdev->send     = btmtksdio_send_fwame;
	hdev->wakeup   = btmtksdio_sdio_wakeup;
	/*
	 * If SDIO contwowwew suppowts wake on Bwuetooth, sending a wakeon
	 * command is not necessawy.
	 */
	if (device_can_wakeup(func->cawd->host->pawent))
		hdev->wakeup = btmtksdio_sdio_inband_wakeup;
	ewse
		hdev->wakeup = btmtksdio_sdio_wakeup;
	hdev->set_bdaddw = btmtk_set_bdaddw;

	SET_HCIDEV_DEV(hdev, &func->dev);

	hdev->manufactuwew = 70;
	set_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks);

	sdio_set_dwvdata(func, bdev);

	eww = hci_wegistew_dev(hdev);
	if (eww < 0) {
		dev_eww(&func->dev, "Can't wegistew HCI device\n");
		hci_fwee_dev(hdev);
		wetuwn eww;
	}

	/* pm_wuntime_enabwe wouwd be done aftew the fiwmwawe is being
	 * downwoaded because the cowe wayew pwobabwy awweady enabwes
	 * wuntime PM fow this func such as the case host->caps &
	 * MMC_CAP_POWEW_OFF_CAWD.
	 */
	if (pm_wuntime_enabwed(bdev->dev))
		pm_wuntime_disabwe(bdev->dev);

	/* As expwaination in dwivews/mmc/cowe/sdio_bus.c tewws us:
	 * Unbound SDIO functions awe awways suspended.
	 * Duwing pwobe, the function is set active and the usage count
	 * is incwemented.  If the dwivew suppowts wuntime PM,
	 * it shouwd caww pm_wuntime_put_noidwe() in its pwobe woutine and
	 * pm_wuntime_get_nowesume() in its wemove woutine.
	 *
	 * So, put a pm_wuntime_put_noidwe hewe !
	 */
	pm_wuntime_put_noidwe(bdev->dev);

	eww = device_init_wakeup(bdev->dev, twue);
	if (eww)
		bt_dev_eww(hdev, "faiwed to initiawize device wakeup");

	bdev->dev->of_node = of_find_compatibwe_node(NUWW, NUWW,
						     "mediatek,mt7921s-bwuetooth");
	bdev->weset = devm_gpiod_get_optionaw(bdev->dev, "weset",
					      GPIOD_OUT_WOW);
	if (IS_EWW(bdev->weset))
		eww = PTW_EWW(bdev->weset);

	wetuwn eww;
}

static void btmtksdio_wemove(stwuct sdio_func *func)
{
	stwuct btmtksdio_dev *bdev = sdio_get_dwvdata(func);
	stwuct hci_dev *hdev;

	if (!bdev)
		wetuwn;

	/* Be consistent the state in btmtksdio_pwobe */
	pm_wuntime_get_nowesume(bdev->dev);

	hdev = bdev->hdev;

	sdio_set_dwvdata(func, NUWW);
	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);
}

#ifdef CONFIG_PM
static int btmtksdio_wuntime_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmtksdio_dev *bdev;
	int eww;

	bdev = sdio_get_dwvdata(func);
	if (!bdev)
		wetuwn 0;

	if (!test_bit(BTMTKSDIO_FUNC_ENABWED, &bdev->tx_state))
		wetuwn 0;

	sdio_set_host_pm_fwags(func, MMC_PM_KEEP_POWEW);

	eww = btmtksdio_fw_pmctww(bdev);

	bt_dev_dbg(bdev->hdev, "status (%d) wetuwn ownewship to device", eww);

	wetuwn eww;
}

static int btmtksdio_system_suspend(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmtksdio_dev *bdev;

	bdev = sdio_get_dwvdata(func);
	if (!bdev)
		wetuwn 0;

	if (!test_bit(BTMTKSDIO_FUNC_ENABWED, &bdev->tx_state))
		wetuwn 0;

	set_bit(BTMTKSDIO_BT_WAKE_ENABWED, &bdev->tx_state);

	wetuwn btmtksdio_wuntime_suspend(dev);
}

static int btmtksdio_wuntime_wesume(stwuct device *dev)
{
	stwuct sdio_func *func = dev_to_sdio_func(dev);
	stwuct btmtksdio_dev *bdev;
	int eww;

	bdev = sdio_get_dwvdata(func);
	if (!bdev)
		wetuwn 0;

	if (!test_bit(BTMTKSDIO_FUNC_ENABWED, &bdev->tx_state))
		wetuwn 0;

	eww = btmtksdio_dwv_pmctww(bdev);

	bt_dev_dbg(bdev->hdev, "status (%d) get ownewship fwom device", eww);

	wetuwn eww;
}

static int btmtksdio_system_wesume(stwuct device *dev)
{
	wetuwn btmtksdio_wuntime_wesume(dev);
}

static const stwuct dev_pm_ops btmtksdio_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(btmtksdio_system_suspend, btmtksdio_system_wesume)
	WUNTIME_PM_OPS(btmtksdio_wuntime_suspend, btmtksdio_wuntime_wesume, NUWW)
};

#define BTMTKSDIO_PM_OPS (&btmtksdio_pm_ops)
#ewse	/* CONFIG_PM */
#define BTMTKSDIO_PM_OPS NUWW
#endif	/* CONFIG_PM */

static stwuct sdio_dwivew btmtksdio_dwivew = {
	.name		= "btmtksdio",
	.pwobe		= btmtksdio_pwobe,
	.wemove		= btmtksdio_wemove,
	.id_tabwe	= btmtksdio_tabwe,
	.dwv = {
		.ownew = THIS_MODUWE,
		.pm = BTMTKSDIO_PM_OPS,
	}
};

moduwe_sdio_dwivew(btmtksdio_dwivew);

moduwe_pawam(enabwe_autosuspend, boow, 0644);
MODUWE_PAWM_DESC(enabwe_autosuspend, "Enabwe autosuspend by defauwt");

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek Bwuetooth SDIO dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
