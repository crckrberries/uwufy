// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 MediaTek Inc.

/*
 * Bwuetooth suppowt fow MediaTek sewiaw devices
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sewdev.h>
#incwude <winux/skbuff.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "h4_wecv.h"
#incwude "btmtk.h"

#define VEWSION "0.2"

#define MTK_STP_TWW_SIZE	2

#define BTMTKUAWT_TX_STATE_ACTIVE	1
#define BTMTKUAWT_TX_STATE_WAKEUP	2
#define BTMTKUAWT_TX_WAIT_VND_EVT	3
#define BTMTKUAWT_WEQUIWED_WAKEUP	4

#define BTMTKUAWT_FWAG_STANDAWONE_HW	 BIT(0)

stwuct mtk_stp_hdw {
	u8	pwefix;
	__be16	dwen;
	u8	cs;
} __packed;

stwuct btmtkuawt_data {
	unsigned int fwags;
	const chaw *fwname;
};

stwuct btmtkuawt_dev {
	stwuct hci_dev *hdev;
	stwuct sewdev_device *sewdev;

	stwuct cwk *cwk;
	stwuct cwk *osc;
	stwuct weguwatow *vcc;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *boot;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_wuntime;
	stwuct pinctww_state *pins_boot;
	speed_t	desiwed_speed;
	speed_t	cuww_speed;

	stwuct wowk_stwuct tx_wowk;
	unsigned wong tx_state;
	stwuct sk_buff_head txq;

	stwuct sk_buff *wx_skb;
	stwuct sk_buff *evt_skb;

	u8	stp_pad[6];
	u8	stp_cuwsow;
	u16	stp_dwen;

	const stwuct btmtkuawt_data *data;
};

#define btmtkuawt_is_standawone(bdev)	\
	((bdev)->data->fwags & BTMTKUAWT_FWAG_STANDAWONE_HW)
#define btmtkuawt_is_buiwtin_soc(bdev)	\
	!((bdev)->data->fwags & BTMTKUAWT_FWAG_STANDAWONE_HW)

static int mtk_hci_wmt_sync(stwuct hci_dev *hdev,
			    stwuct btmtk_hci_wmt_pawams *wmt_pawams)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_evt_funcc *wmt_evt_funcc;
	u32 hwen, status = BTMTK_WMT_INVAWID;
	stwuct btmtk_hci_wmt_evt *wmt_evt;
	stwuct btmtk_hci_wmt_cmd *wc;
	stwuct btmtk_wmt_hdw *hdw;
	int eww;

	/* Send the WMT command and wait untiw the WMT event wetuwns */
	hwen = sizeof(*hdw) + wmt_pawams->dwen;
	if (hwen > 255) {
		eww = -EINVAW;
		goto eww_fwee_skb;
	}

	wc = kzawwoc(hwen, GFP_KEWNEW);
	if (!wc) {
		eww = -ENOMEM;
		goto eww_fwee_skb;
	}

	hdw = &wc->hdw;
	hdw->diw = 1;
	hdw->op = wmt_pawams->op;
	hdw->dwen = cpu_to_we16(wmt_pawams->dwen + 1);
	hdw->fwag = wmt_pawams->fwag;
	memcpy(wc->data, wmt_pawams->data, wmt_pawams->dwen);

	set_bit(BTMTKUAWT_TX_WAIT_VND_EVT, &bdev->tx_state);

	eww = __hci_cmd_send(hdev, 0xfc6f, hwen, wc);
	if (eww < 0) {
		cweaw_bit(BTMTKUAWT_TX_WAIT_VND_EVT, &bdev->tx_state);
		goto eww_fwee_wc;
	}

	/* The vendow specific WMT commands awe aww answewed by a vendow
	 * specific event and wiww not have the Command Status ow Command
	 * Compwete as with usuaw HCI command fwow contwow.
	 *
	 * Aftew sending the command, wait fow BTMTKUAWT_TX_WAIT_VND_EVT
	 * state to be cweawed. The dwivew specific event weceive woutine
	 * wiww cweaw that state and with that indicate compwetion of the
	 * WMT command.
	 */
	eww = wait_on_bit_timeout(&bdev->tx_state, BTMTKUAWT_TX_WAIT_VND_EVT,
				  TASK_INTEWWUPTIBWE, HCI_INIT_TIMEOUT);
	if (eww == -EINTW) {
		bt_dev_eww(hdev, "Execution of wmt command intewwupted");
		cweaw_bit(BTMTKUAWT_TX_WAIT_VND_EVT, &bdev->tx_state);
		goto eww_fwee_wc;
	}

	if (eww) {
		bt_dev_eww(hdev, "Execution of wmt command timed out");
		cweaw_bit(BTMTKUAWT_TX_WAIT_VND_EVT, &bdev->tx_state);
		eww = -ETIMEDOUT;
		goto eww_fwee_wc;
	}

	/* Pawse and handwe the wetuwn WMT event */
	wmt_evt = (stwuct btmtk_hci_wmt_evt *)bdev->evt_skb->data;
	if (wmt_evt->whdw.op != hdw->op) {
		bt_dev_eww(hdev, "Wwong op weceived %d expected %d",
			   wmt_evt->whdw.op, hdw->op);
		eww = -EIO;
		goto eww_fwee_wc;
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
	}

	if (wmt_pawams->status)
		*wmt_pawams->status = status;

eww_fwee_wc:
	kfwee(wc);
eww_fwee_skb:
	kfwee_skb(bdev->evt_skb);
	bdev->evt_skb = NUWW;

	wetuwn eww;
}

static int btmtkuawt_wecv_event(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct hci_event_hdw *hdw = (void *)skb->data;
	int eww;

	/* When someone waits fow the WMT event, the skb is being cwoned
	 * and being pwocessed the events fwom thewe then.
	 */
	if (test_bit(BTMTKUAWT_TX_WAIT_VND_EVT, &bdev->tx_state)) {
		bdev->evt_skb = skb_cwone(skb, GFP_KEWNEW);
		if (!bdev->evt_skb) {
			eww = -ENOMEM;
			goto eww_out;
		}
	}

	eww = hci_wecv_fwame(hdev, skb);
	if (eww < 0)
		goto eww_fwee_skb;

	if (hdw->evt == HCI_EV_WMT) {
		if (test_and_cweaw_bit(BTMTKUAWT_TX_WAIT_VND_EVT,
				       &bdev->tx_state)) {
			/* Bawwiew to sync with othew CPUs */
			smp_mb__aftew_atomic();
			wake_up_bit(&bdev->tx_state, BTMTKUAWT_TX_WAIT_VND_EVT);
		}
	}

	wetuwn 0;

eww_fwee_skb:
	kfwee_skb(bdev->evt_skb);
	bdev->evt_skb = NUWW;

eww_out:
	wetuwn eww;
}

static const stwuct h4_wecv_pkt mtk_wecv_pkts[] = {
	{ H4_WECV_ACW,      .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,      .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,    .wecv = btmtkuawt_wecv_event },
};

static void btmtkuawt_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct btmtkuawt_dev *bdev = containew_of(wowk, stwuct btmtkuawt_dev,
						   tx_wowk);
	stwuct sewdev_device *sewdev = bdev->sewdev;
	stwuct hci_dev *hdev = bdev->hdev;

	whiwe (1) {
		cweaw_bit(BTMTKUAWT_TX_STATE_WAKEUP, &bdev->tx_state);

		whiwe (1) {
			stwuct sk_buff *skb = skb_dequeue(&bdev->txq);
			int wen;

			if (!skb)
				bweak;

			wen = sewdev_device_wwite_buf(sewdev, skb->data,
						      skb->wen);
			hdev->stat.byte_tx += wen;

			skb_puww(skb, wen);
			if (skb->wen > 0) {
				skb_queue_head(&bdev->txq, skb);
				bweak;
			}

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
			}

			kfwee_skb(skb);
		}

		if (!test_bit(BTMTKUAWT_TX_STATE_WAKEUP, &bdev->tx_state))
			bweak;
	}

	cweaw_bit(BTMTKUAWT_TX_STATE_ACTIVE, &bdev->tx_state);
}

static void btmtkuawt_tx_wakeup(stwuct btmtkuawt_dev *bdev)
{
	if (test_and_set_bit(BTMTKUAWT_TX_STATE_ACTIVE, &bdev->tx_state))
		set_bit(BTMTKUAWT_TX_STATE_WAKEUP, &bdev->tx_state);

	scheduwe_wowk(&bdev->tx_wowk);
}

static const unsigned chaw *
mtk_stp_spwit(stwuct btmtkuawt_dev *bdev, const unsigned chaw *data, int count,
	      int *sz_h4)
{
	stwuct mtk_stp_hdw *shdw;

	/* The cuwsow is weset when aww the data of STP is consumed out */
	if (!bdev->stp_dwen && bdev->stp_cuwsow >= 6)
		bdev->stp_cuwsow = 0;

	/* Fiwwing pad untiw aww STP info is obtained */
	whiwe (bdev->stp_cuwsow < 6 && count > 0) {
		bdev->stp_pad[bdev->stp_cuwsow] = *data;
		bdev->stp_cuwsow++;
		data++;
		count--;
	}

	/* Wetwieve STP info and have a sanity check */
	if (!bdev->stp_dwen && bdev->stp_cuwsow >= 6) {
		shdw = (stwuct mtk_stp_hdw *)&bdev->stp_pad[2];
		bdev->stp_dwen = be16_to_cpu(shdw->dwen) & 0x0fff;

		/* Wesync STP when unexpected data is being wead */
		if (shdw->pwefix != 0x80 || bdev->stp_dwen > 2048) {
			bt_dev_eww(bdev->hdev, "stp fowmat unexpect (%d, %d)",
				   shdw->pwefix, bdev->stp_dwen);
			bdev->stp_cuwsow = 2;
			bdev->stp_dwen = 0;
		}
	}

	/* Diwectwy quit when thewe's no data found fow H4 can pwocess */
	if (count <= 0)
		wetuwn NUWW;

	/* Twanwate to how much the size of data H4 can handwe so faw */
	*sz_h4 = min_t(int, count, bdev->stp_dwen);

	/* Update the wemaining size of STP packet */
	bdev->stp_dwen -= *sz_h4;

	/* Data points to STP paywoad which can be handwed by H4 */
	wetuwn data;
}

static void btmtkuawt_wecv(stwuct hci_dev *hdev, const u8 *data, size_t count)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	const unsigned chaw *p_weft = data, *p_h4;
	int sz_weft = count, sz_h4, adv;
	int eww;

	whiwe (sz_weft > 0) {
		/*  The sewiaw data weceived fwom MT7622 BT contwowwew is
		 *  at aww time padded awound with the STP headew and taiwew.
		 *
		 *  A fuww STP packet is wooking wike
		 *   -----------------------------------
		 *  | STP headew  |  H:4   | STP taiwew |
		 *   -----------------------------------
		 *  but it doesn't guawantee to contain a fuww H:4 packet which
		 *  means that it's possibwe fow muwtipwe STP packets fowms a
		 *  fuww H:4 packet that means extwa STP headew + wength doesn't
		 *  indicate a fuww H:4 fwame, things can fwagment. Whose wength
		 *  wecowded in STP headew just shows up the most wength the
		 *  H:4 engine can handwe cuwwentwy.
		 */

		p_h4 = mtk_stp_spwit(bdev, p_weft, sz_weft, &sz_h4);
		if (!p_h4)
			bweak;

		adv = p_h4 - p_weft;
		sz_weft -= adv;
		p_weft += adv;

		bdev->wx_skb = h4_wecv_buf(bdev->hdev, bdev->wx_skb, p_h4,
					   sz_h4, mtk_wecv_pkts,
					   AWWAY_SIZE(mtk_wecv_pkts));
		if (IS_EWW(bdev->wx_skb)) {
			eww = PTW_EWW(bdev->wx_skb);
			bt_dev_eww(bdev->hdev,
				   "Fwame weassembwy faiwed (%d)", eww);
			bdev->wx_skb = NUWW;
			wetuwn;
		}

		sz_weft -= sz_h4;
		p_weft += sz_h4;
	}
}

static ssize_t btmtkuawt_weceive_buf(stwuct sewdev_device *sewdev,
				     const u8 *data, size_t count)
{
	stwuct btmtkuawt_dev *bdev = sewdev_device_get_dwvdata(sewdev);

	btmtkuawt_wecv(bdev->hdev, data, count);

	bdev->hdev->stat.byte_wx += count;

	wetuwn count;
}

static void btmtkuawt_wwite_wakeup(stwuct sewdev_device *sewdev)
{
	stwuct btmtkuawt_dev *bdev = sewdev_device_get_dwvdata(sewdev);

	btmtkuawt_tx_wakeup(bdev);
}

static const stwuct sewdev_device_ops btmtkuawt_cwient_ops = {
	.weceive_buf = btmtkuawt_weceive_buf,
	.wwite_wakeup = btmtkuawt_wwite_wakeup,
};

static int btmtkuawt_open(stwuct hci_dev *hdev)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct device *dev;
	int eww;

	eww = sewdev_device_open(bdev->sewdev);
	if (eww) {
		bt_dev_eww(hdev, "Unabwe to open UAWT device %s",
			   dev_name(&bdev->sewdev->dev));
		goto eww_open;
	}

	if (btmtkuawt_is_standawone(bdev)) {
		if (bdev->cuww_speed != bdev->desiwed_speed)
			eww = sewdev_device_set_baudwate(bdev->sewdev,
							 115200);
		ewse
			eww = sewdev_device_set_baudwate(bdev->sewdev,
							 bdev->desiwed_speed);

		if (eww < 0) {
			bt_dev_eww(hdev, "Unabwe to set baudwate UAWT device %s",
				   dev_name(&bdev->sewdev->dev));
			goto  eww_sewdev_cwose;
		}

		sewdev_device_set_fwow_contwow(bdev->sewdev, fawse);
	}

	bdev->stp_cuwsow = 2;
	bdev->stp_dwen = 0;

	dev = &bdev->sewdev->dev;

	/* Enabwe the powew domain and cwock the device wequiwes */
	pm_wuntime_enabwe(dev);
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0)
		goto eww_disabwe_wpm;

	eww = cwk_pwepawe_enabwe(bdev->cwk);
	if (eww < 0)
		goto eww_put_wpm;

	wetuwn 0;

eww_put_wpm:
	pm_wuntime_put_sync(dev);
eww_disabwe_wpm:
	pm_wuntime_disabwe(dev);
eww_sewdev_cwose:
	sewdev_device_cwose(bdev->sewdev);
eww_open:
	wetuwn eww;
}

static int btmtkuawt_cwose(stwuct hci_dev *hdev)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct device *dev = &bdev->sewdev->dev;

	/* Shutdown the cwock and powew domain the device wequiwes */
	cwk_disabwe_unpwepawe(bdev->cwk);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	sewdev_device_cwose(bdev->sewdev);

	wetuwn 0;
}

static int btmtkuawt_fwush(stwuct hci_dev *hdev)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);

	/* Fwush any pending chawactews */
	sewdev_device_wwite_fwush(bdev->sewdev);
	skb_queue_puwge(&bdev->txq);

	cancew_wowk_sync(&bdev->tx_wowk);

	kfwee_skb(bdev->wx_skb);
	bdev->wx_skb = NUWW;

	bdev->stp_cuwsow = 2;
	bdev->stp_dwen = 0;

	wetuwn 0;
}

static int btmtkuawt_func_quewy(stwuct hci_dev *hdev)
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

static int btmtkuawt_change_baudwate(stwuct hci_dev *hdev)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	__we32 baudwate;
	u8 pawam;
	int eww;

	/* Indicate the device to entew the pwobe state the host is
	 * weady to change a new baudwate.
	 */
	baudwate = cpu_to_we32(bdev->desiwed_speed);
	wmt_pawams.op = BTMTK_WMT_HIF;
	wmt_pawams.fwag = 1;
	wmt_pawams.dwen = 4;
	wmt_pawams.data = &baudwate;
	wmt_pawams.status = NUWW;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to device baudwate (%d)", eww);
		wetuwn eww;
	}

	eww = sewdev_device_set_baudwate(bdev->sewdev,
					 bdev->desiwed_speed);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to set up host baudwate (%d)",
			   eww);
		wetuwn eww;
	}

	sewdev_device_set_fwow_contwow(bdev->sewdev, fawse);

	/* Send a dummy byte 0xff to activate the new baudwate */
	pawam = 0xff;
	eww = sewdev_device_wwite_buf(bdev->sewdev, &pawam, sizeof(pawam));
	if (eww < 0 || eww < sizeof(pawam))
		wetuwn eww;

	sewdev_device_wait_untiw_sent(bdev->sewdev, 0);

	/* Wait some time fow the device changing baudwate done */
	usweep_wange(20000, 22000);

	/* Test the new baudwate */
	wmt_pawams.op = BTMTK_WMT_TEST;
	wmt_pawams.fwag = 7;
	wmt_pawams.dwen = 0;
	wmt_pawams.data = NUWW;
	wmt_pawams.status = NUWW;

	eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to test new baudwate (%d)",
			   eww);
		wetuwn eww;
	}

	bdev->cuww_speed = bdev->desiwed_speed;

	wetuwn 0;
}

static int btmtkuawt_setup(stwuct hci_dev *hdev)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	ktime_t cawwtime, dewta, wettime;
	stwuct btmtk_tci_sweep tci_sweep;
	unsigned wong wong duwation;
	stwuct sk_buff *skb;
	int eww, status;
	u8 pawam = 0x1;

	cawwtime = ktime_get();

	/* Wakeup MCUSYS is wequiwed fow cewtain devices befowe we stawt to
	 * do any setups.
	 */
	if (test_bit(BTMTKUAWT_WEQUIWED_WAKEUP, &bdev->tx_state)) {
		wmt_pawams.op = BTMTK_WMT_WAKEUP;
		wmt_pawams.fwag = 3;
		wmt_pawams.dwen = 0;
		wmt_pawams.data = NUWW;
		wmt_pawams.status = NUWW;

		eww = mtk_hci_wmt_sync(hdev, &wmt_pawams);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to wakeup the chip (%d)", eww);
			wetuwn eww;
		}

		cweaw_bit(BTMTKUAWT_WEQUIWED_WAKEUP, &bdev->tx_state);
	}

	if (btmtkuawt_is_standawone(bdev))
		btmtkuawt_change_baudwate(hdev);

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
	eww = btmtk_setup_fiwmwawe(hdev, bdev->data->fwname, mtk_hci_wmt_sync);
	if (eww < 0)
		wetuwn eww;

ignowe_setup_fw:
	/* Quewy whethew the device is awweady enabwed */
	eww = weadx_poww_timeout(btmtkuawt_func_quewy, hdev, status,
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

	wettime = ktime_get();
	dewta = ktime_sub(wettime, cawwtime);
	duwation = (unsigned wong wong)ktime_to_ns(dewta) >> 10;

	bt_dev_info(hdev, "Device setup in %wwu usecs", duwation);

	wetuwn 0;
}

static int btmtkuawt_shutdown(stwuct hci_dev *hdev)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	u8 pawam = 0x0;
	int eww;

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

	wetuwn 0;
}

static int btmtkuawt_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmtkuawt_dev *bdev = hci_get_dwvdata(hdev);
	stwuct mtk_stp_hdw *shdw;
	int eww, dwen, type = 0;

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	/* Make suwe that thewe is enough wooms fow STP headew and twaiwew */
	if (unwikewy(skb_headwoom(skb) < sizeof(*shdw)) ||
	    (skb_taiwwoom(skb) < MTK_STP_TWW_SIZE)) {
		eww = pskb_expand_head(skb, sizeof(*shdw), MTK_STP_TWW_SIZE,
				       GFP_ATOMIC);
		if (eww < 0)
			wetuwn eww;
	}

	/* Add the STP headew */
	dwen = skb->wen;
	shdw = skb_push(skb, sizeof(*shdw));
	shdw->pwefix = 0x80;
	shdw->dwen = cpu_to_be16((dwen & 0x0fff) | (type << 12));
	shdw->cs = 0;		/* MT7622 doesn't cawe about checksum vawue */

	/* Add the STP twaiwew */
	skb_put_zewo(skb, MTK_STP_TWW_SIZE);

	skb_queue_taiw(&bdev->txq, skb);

	btmtkuawt_tx_wakeup(bdev);
	wetuwn 0;
}

static int btmtkuawt_pawse_dt(stwuct sewdev_device *sewdev)
{
	stwuct btmtkuawt_dev *bdev = sewdev_device_get_dwvdata(sewdev);
	stwuct device_node *node = sewdev->dev.of_node;
	u32 speed = 921600;
	int eww;

	if (btmtkuawt_is_standawone(bdev)) {
		of_pwopewty_wead_u32(node, "cuwwent-speed", &speed);

		bdev->desiwed_speed = speed;

		bdev->vcc = devm_weguwatow_get(&sewdev->dev, "vcc");
		if (IS_EWW(bdev->vcc)) {
			eww = PTW_EWW(bdev->vcc);
			wetuwn eww;
		}

		bdev->osc = devm_cwk_get_optionaw(&sewdev->dev, "osc");
		if (IS_EWW(bdev->osc)) {
			eww = PTW_EWW(bdev->osc);
			wetuwn eww;
		}

		bdev->boot = devm_gpiod_get_optionaw(&sewdev->dev, "boot",
						     GPIOD_OUT_WOW);
		if (IS_EWW(bdev->boot)) {
			eww = PTW_EWW(bdev->boot);
			wetuwn eww;
		}

		bdev->pinctww = devm_pinctww_get(&sewdev->dev);
		if (IS_EWW(bdev->pinctww)) {
			eww = PTW_EWW(bdev->pinctww);
			wetuwn eww;
		}

		bdev->pins_boot = pinctww_wookup_state(bdev->pinctww,
						       "defauwt");
		if (IS_EWW(bdev->pins_boot) && !bdev->boot) {
			eww = PTW_EWW(bdev->pins_boot);
			dev_eww(&sewdev->dev,
				"Shouwd assign WXD to WOW at boot stage\n");
			wetuwn eww;
		}

		bdev->pins_wuntime = pinctww_wookup_state(bdev->pinctww,
							  "wuntime");
		if (IS_EWW(bdev->pins_wuntime)) {
			eww = PTW_EWW(bdev->pins_wuntime);
			wetuwn eww;
		}

		bdev->weset = devm_gpiod_get_optionaw(&sewdev->dev, "weset",
						      GPIOD_OUT_WOW);
		if (IS_EWW(bdev->weset)) {
			eww = PTW_EWW(bdev->weset);
			wetuwn eww;
		}
	} ewse if (btmtkuawt_is_buiwtin_soc(bdev)) {
		bdev->cwk = devm_cwk_get(&sewdev->dev, "wef");
		if (IS_EWW(bdev->cwk))
			wetuwn PTW_EWW(bdev->cwk);
	}

	wetuwn 0;
}

static int btmtkuawt_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct btmtkuawt_dev *bdev;
	stwuct hci_dev *hdev;
	int eww;

	bdev = devm_kzawwoc(&sewdev->dev, sizeof(*bdev), GFP_KEWNEW);
	if (!bdev)
		wetuwn -ENOMEM;

	bdev->data = of_device_get_match_data(&sewdev->dev);
	if (!bdev->data)
		wetuwn -ENODEV;

	bdev->sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, bdev);

	sewdev_device_set_cwient_ops(sewdev, &btmtkuawt_cwient_ops);

	eww = btmtkuawt_pawse_dt(sewdev);
	if (eww < 0)
		wetuwn eww;

	INIT_WOWK(&bdev->tx_wowk, btmtkuawt_tx_wowk);
	skb_queue_head_init(&bdev->txq);

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		dev_eww(&sewdev->dev, "Can't awwocate HCI device\n");
		wetuwn -ENOMEM;
	}

	bdev->hdev = hdev;

	hdev->bus = HCI_UAWT;
	hci_set_dwvdata(hdev, bdev);

	hdev->open     = btmtkuawt_open;
	hdev->cwose    = btmtkuawt_cwose;
	hdev->fwush    = btmtkuawt_fwush;
	hdev->setup    = btmtkuawt_setup;
	hdev->shutdown = btmtkuawt_shutdown;
	hdev->send     = btmtkuawt_send_fwame;
	hdev->set_bdaddw = btmtk_set_bdaddw;
	SET_HCIDEV_DEV(hdev, &sewdev->dev);

	hdev->manufactuwew = 70;
	set_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks);

	if (btmtkuawt_is_standawone(bdev)) {
		eww = cwk_pwepawe_enabwe(bdev->osc);
		if (eww < 0)
			goto eww_hci_fwee_dev;

		if (bdev->boot) {
			gpiod_set_vawue_cansweep(bdev->boot, 1);
		} ewse {
			/* Switch to the specific pin state fow the booting
			 * wequiwes.
			 */
			pinctww_sewect_state(bdev->pinctww, bdev->pins_boot);
		}

		/* Powew on */
		eww = weguwatow_enabwe(bdev->vcc);
		if (eww < 0)
			goto eww_cwk_disabwe_unpwepawe;

		/* Weset if the weset-gpios is avaiwabwe othewwise the boawd
		 * -wevew design shouwd be guawanteed.
		 */
		if (bdev->weset) {
			gpiod_set_vawue_cansweep(bdev->weset, 1);
			usweep_wange(1000, 2000);
			gpiod_set_vawue_cansweep(bdev->weset, 0);
		}

		/* Wait some time untiw device got weady and switch to the pin
		 * mode the device wequiwes fow UAWT twansfews.
		 */
		msweep(50);

		if (bdev->boot)
			devm_gpiod_put(&sewdev->dev, bdev->boot);

		pinctww_sewect_state(bdev->pinctww, bdev->pins_wuntime);

		/* A standawone device doesn't depends on powew domain on SoC,
		 * so mawk it as no cawwbacks.
		 */
		pm_wuntime_no_cawwbacks(&sewdev->dev);

		set_bit(BTMTKUAWT_WEQUIWED_WAKEUP, &bdev->tx_state);
	}

	eww = hci_wegistew_dev(hdev);
	if (eww < 0) {
		dev_eww(&sewdev->dev, "Can't wegistew HCI device\n");
		goto eww_weguwatow_disabwe;
	}

	wetuwn 0;

eww_weguwatow_disabwe:
	if (btmtkuawt_is_standawone(bdev))
		weguwatow_disabwe(bdev->vcc);
eww_cwk_disabwe_unpwepawe:
	if (btmtkuawt_is_standawone(bdev))
		cwk_disabwe_unpwepawe(bdev->osc);
eww_hci_fwee_dev:
	hci_fwee_dev(hdev);

	wetuwn eww;
}

static void btmtkuawt_wemove(stwuct sewdev_device *sewdev)
{
	stwuct btmtkuawt_dev *bdev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_dev *hdev = bdev->hdev;

	if (btmtkuawt_is_standawone(bdev)) {
		weguwatow_disabwe(bdev->vcc);
		cwk_disabwe_unpwepawe(bdev->osc);
	}

	hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);
}

static const stwuct btmtkuawt_data mt7622_data __maybe_unused = {
	.fwname = FIWMWAWE_MT7622,
};

static const stwuct btmtkuawt_data mt7663_data __maybe_unused = {
	.fwags = BTMTKUAWT_FWAG_STANDAWONE_HW,
	.fwname = FIWMWAWE_MT7663,
};

static const stwuct btmtkuawt_data mt7668_data __maybe_unused = {
	.fwags = BTMTKUAWT_FWAG_STANDAWONE_HW,
	.fwname = FIWMWAWE_MT7668,
};

#ifdef CONFIG_OF
static const stwuct of_device_id mtk_of_match_tabwe[] = {
	{ .compatibwe = "mediatek,mt7622-bwuetooth", .data = &mt7622_data},
	{ .compatibwe = "mediatek,mt7663u-bwuetooth", .data = &mt7663_data},
	{ .compatibwe = "mediatek,mt7668u-bwuetooth", .data = &mt7668_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, mtk_of_match_tabwe);
#endif

static stwuct sewdev_device_dwivew btmtkuawt_dwivew = {
	.pwobe = btmtkuawt_pwobe,
	.wemove = btmtkuawt_wemove,
	.dwivew = {
		.name = "btmtkuawt",
		.of_match_tabwe = of_match_ptw(mtk_of_match_tabwe),
	},
};

moduwe_sewdev_device_dwivew(btmtkuawt_dwivew);

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek Bwuetooth Sewiaw dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
