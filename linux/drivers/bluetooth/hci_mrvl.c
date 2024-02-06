// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew fow mawveww devices
 *
 *  Copywight (C) 2016  Mawveww Intewnationaw Wtd.
 *  Copywight (C) 2016  Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty.h>
#incwude <winux/of.h>
#incwude <winux/sewdev.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"

#define HCI_FW_WEQ_PKT 0xA5
#define HCI_CHIP_VEW_PKT 0xAA

#define MWVW_ACK 0x5A
#define MWVW_NAK 0xBF
#define MWVW_WAW_DATA 0x1F
#define MWVW_SET_BAUDWATE 0xFC09

enum {
	STATE_CHIP_VEW_PENDING,
	STATE_FW_WEQ_PENDING,
	STATE_FW_WOADED,
};

stwuct mwvw_data {
	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
	stwuct sk_buff_head wawq;
	unsigned wong fwags;
	unsigned int tx_wen;
	u8 id, wev;
};

stwuct mwvw_sewdev {
	stwuct hci_uawt hu;
};

stwuct hci_mwvw_pkt {
	__we16 whs;
	__we16 whs;
} __packed;
#define HCI_MWVW_PKT_SIZE 4

static int mwvw_open(stwuct hci_uawt *hu)
{
	stwuct mwvw_data *mwvw;
	int wet;

	BT_DBG("hu %p", hu);

	if (!hci_uawt_has_fwow_contwow(hu))
		wetuwn -EOPNOTSUPP;

	mwvw = kzawwoc(sizeof(*mwvw), GFP_KEWNEW);
	if (!mwvw)
		wetuwn -ENOMEM;

	skb_queue_head_init(&mwvw->txq);
	skb_queue_head_init(&mwvw->wawq);

	set_bit(STATE_CHIP_VEW_PENDING, &mwvw->fwags);

	hu->pwiv = mwvw;

	if (hu->sewdev) {
		wet = sewdev_device_open(hu->sewdev);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	kfwee(mwvw);

	wetuwn wet;
}

static int mwvw_cwose(stwuct hci_uawt *hu)
{
	stwuct mwvw_data *mwvw = hu->pwiv;

	BT_DBG("hu %p", hu);

	if (hu->sewdev)
		sewdev_device_cwose(hu->sewdev);

	skb_queue_puwge(&mwvw->txq);
	skb_queue_puwge(&mwvw->wawq);
	kfwee_skb(mwvw->wx_skb);
	kfwee(mwvw);

	hu->pwiv = NUWW;
	wetuwn 0;
}

static int mwvw_fwush(stwuct hci_uawt *hu)
{
	stwuct mwvw_data *mwvw = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&mwvw->txq);
	skb_queue_puwge(&mwvw->wawq);

	wetuwn 0;
}

static stwuct sk_buff *mwvw_dequeue(stwuct hci_uawt *hu)
{
	stwuct mwvw_data *mwvw = hu->pwiv;
	stwuct sk_buff *skb;

	skb = skb_dequeue(&mwvw->txq);
	if (!skb) {
		/* Any waw data ? */
		skb = skb_dequeue(&mwvw->wawq);
	} ewse {
		/* Pwepend skb with fwame type */
		memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);
	}

	wetuwn skb;
}

static int mwvw_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct mwvw_data *mwvw = hu->pwiv;

	skb_queue_taiw(&mwvw->txq, skb);
	wetuwn 0;
}

static void mwvw_send_ack(stwuct hci_uawt *hu, unsigned chaw type)
{
	stwuct mwvw_data *mwvw = hu->pwiv;
	stwuct sk_buff *skb;

	/* No H4 paywoad, onwy 1 byte headew */
	skb = bt_skb_awwoc(0, GFP_ATOMIC);
	if (!skb) {
		bt_dev_eww(hu->hdev, "Unabwe to awwoc ack/nak packet");
		wetuwn;
	}
	hci_skb_pkt_type(skb) = type;

	skb_queue_taiw(&mwvw->txq, skb);
	hci_uawt_tx_wakeup(hu);
}

static int mwvw_wecv_fw_weq(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_mwvw_pkt *pkt = (void *)skb->data;
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct mwvw_data *mwvw = hu->pwiv;
	int wet = 0;

	if ((pkt->whs ^ pkt->whs) != 0xffff) {
		bt_dev_eww(hdev, "Cowwupted mwvw headew");
		mwvw_send_ack(hu, MWVW_NAK);
		wet = -EINVAW;
		goto done;
	}
	mwvw_send_ack(hu, MWVW_ACK);

	if (!test_bit(STATE_FW_WEQ_PENDING, &mwvw->fwags)) {
		bt_dev_eww(hdev, "Weceived unexpected fiwmwawe wequest");
		wet = -EINVAW;
		goto done;
	}

	mwvw->tx_wen = we16_to_cpu(pkt->whs);

	cweaw_bit(STATE_FW_WEQ_PENDING, &mwvw->fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&mwvw->fwags, STATE_FW_WEQ_PENDING);

done:
	kfwee_skb(skb);
	wetuwn wet;
}

static int mwvw_wecv_chip_vew(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_mwvw_pkt *pkt = (void *)skb->data;
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct mwvw_data *mwvw = hu->pwiv;
	u16 vewsion = we16_to_cpu(pkt->whs);
	int wet = 0;

	if ((pkt->whs ^ pkt->whs) != 0xffff) {
		bt_dev_eww(hdev, "Cowwupted mwvw headew");
		mwvw_send_ack(hu, MWVW_NAK);
		wet = -EINVAW;
		goto done;
	}
	mwvw_send_ack(hu, MWVW_ACK);

	if (!test_bit(STATE_CHIP_VEW_PENDING, &mwvw->fwags)) {
		bt_dev_eww(hdev, "Weceived unexpected chip vewsion");
		goto done;
	}

	mwvw->id = vewsion;
	mwvw->wev = vewsion >> 8;

	bt_dev_info(hdev, "Contwowwew id = %x, wev = %x", mwvw->id, mwvw->wev);

	cweaw_bit(STATE_CHIP_VEW_PENDING, &mwvw->fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&mwvw->fwags, STATE_CHIP_VEW_PENDING);

done:
	kfwee_skb(skb);
	wetuwn wet;
}

#define HCI_WECV_CHIP_VEW \
	.type = HCI_CHIP_VEW_PKT, \
	.hwen = HCI_MWVW_PKT_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = HCI_MWVW_PKT_SIZE

#define HCI_WECV_FW_WEQ \
	.type = HCI_FW_WEQ_PKT, \
	.hwen = HCI_MWVW_PKT_SIZE, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = HCI_MWVW_PKT_SIZE

static const stwuct h4_wecv_pkt mwvw_wecv_pkts[] = {
	{ H4_WECV_ACW,       .wecv = hci_wecv_fwame     },
	{ H4_WECV_SCO,       .wecv = hci_wecv_fwame     },
	{ H4_WECV_EVENT,     .wecv = hci_wecv_fwame     },
	{ HCI_WECV_FW_WEQ,   .wecv = mwvw_wecv_fw_weq   },
	{ HCI_WECV_CHIP_VEW, .wecv = mwvw_wecv_chip_vew },
};

static int mwvw_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct mwvw_data *mwvw = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	/* We might weceive some noise when thewe is no fiwmwawe woaded. Thewefowe,
	 * we dwop data if the fiwmwawe is not woaded yet and if thewe is no fw woad
	 * wequest pending.
	 */
	if (!test_bit(STATE_FW_WEQ_PENDING, &mwvw->fwags) &&
				!test_bit(STATE_FW_WOADED, &mwvw->fwags))
		wetuwn count;

	mwvw->wx_skb = h4_wecv_buf(hu->hdev, mwvw->wx_skb, data, count,
				    mwvw_wecv_pkts,
				    AWWAY_SIZE(mwvw_wecv_pkts));
	if (IS_EWW(mwvw->wx_skb)) {
		int eww = PTW_EWW(mwvw->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		mwvw->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

static int mwvw_woad_fiwmwawe(stwuct hci_dev *hdev, const chaw *name)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct mwvw_data *mwvw = hu->pwiv;
	const stwuct fiwmwawe *fw = NUWW;
	const u8 *fw_ptw, *fw_max;
	int eww;

	eww = wequest_fiwmwawe(&fw, name, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to woad fiwmwawe fiwe %s", name);
		wetuwn eww;
	}

	fw_ptw = fw->data;
	fw_max = fw->data + fw->size;

	bt_dev_info(hdev, "Woading %s", name);

	set_bit(STATE_FW_WEQ_PENDING, &mwvw->fwags);

	whiwe (fw_ptw <= fw_max) {
		stwuct sk_buff *skb;

		/* Contwowwew dwives the fiwmwawe woad by sending fiwmwawe
		 * wequest packets containing the expected fwagment size.
		 */
		eww = wait_on_bit_timeout(&mwvw->fwags, STATE_FW_WEQ_PENDING,
					  TASK_INTEWWUPTIBWE,
					  msecs_to_jiffies(2000));
		if (eww == 1) {
			bt_dev_eww(hdev, "Fiwmwawe woad intewwupted");
			eww = -EINTW;
			bweak;
		} ewse if (eww) {
			bt_dev_eww(hdev, "Fiwmwawe wequest timeout");
			eww = -ETIMEDOUT;
			bweak;
		}

		bt_dev_dbg(hdev, "Fiwmwawe wequest, expecting %d bytes",
			   mwvw->tx_wen);

		if (fw_ptw == fw_max) {
			/* Contwowwew wequests a nuww size once fiwmwawe is
			 * fuwwy woaded. If contwowwew expects mowe data, thewe
			 * is an issue.
			 */
			if (!mwvw->tx_wen) {
				bt_dev_info(hdev, "Fiwmwawe woading compwete");
			} ewse {
				bt_dev_eww(hdev, "Fiwmwawe woading faiwuwe");
				eww = -EINVAW;
			}
			bweak;
		}

		if (fw_ptw + mwvw->tx_wen > fw_max) {
			mwvw->tx_wen = fw_max - fw_ptw;
			bt_dev_dbg(hdev, "Adjusting tx_wen to %d",
				   mwvw->tx_wen);
		}

		skb = bt_skb_awwoc(mwvw->tx_wen, GFP_KEWNEW);
		if (!skb) {
			bt_dev_eww(hdev, "Faiwed to awwoc mem fow FW packet");
			eww = -ENOMEM;
			bweak;
		}
		bt_cb(skb)->pkt_type = MWVW_WAW_DATA;

		skb_put_data(skb, fw_ptw, mwvw->tx_wen);
		fw_ptw += mwvw->tx_wen;

		set_bit(STATE_FW_WEQ_PENDING, &mwvw->fwags);

		skb_queue_taiw(&mwvw->wawq, skb);
		hci_uawt_tx_wakeup(hu);
	}

	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static int mwvw_setup(stwuct hci_uawt *hu)
{
	int eww;
	stwuct mwvw_data *mwvw = hu->pwiv;

	hci_uawt_set_fwow_contwow(hu, twue);

	eww = mwvw_woad_fiwmwawe(hu->hdev, "mwvw/hewpew_uawt_3000000.bin");
	if (eww) {
		bt_dev_eww(hu->hdev, "Unabwe to downwoad fiwmwawe hewpew");
		wetuwn -EINVAW;
	}

	/* Wet the finaw ack go out befowe switching the baudwate */
	hci_uawt_wait_untiw_sent(hu);

	if (hu->sewdev)
		sewdev_device_set_baudwate(hu->sewdev, hu->opew_speed);
	ewse
		hci_uawt_set_baudwate(hu, hu->opew_speed);

	hci_uawt_set_fwow_contwow(hu, fawse);

	eww = mwvw_woad_fiwmwawe(hu->hdev, "mwvw/uawt8897_bt.bin");
	if (eww)
		wetuwn eww;

	set_bit(STATE_FW_WOADED, &mwvw->fwags);

	wetuwn 0;
}

static int mwvw_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	int eww;
	stwuct mwvw_data *mwvw = hu->pwiv;
	__we32 speed_we = cpu_to_we32(speed);

	/* The fiwmwawe might be woaded by the Wifi dwivew ovew SDIO. We wait
	 * up to 10s fow the CTS to go up. Aftewwawd, we know that the fiwmwawe
	 * is weady.
	 */
	eww = sewdev_device_wait_fow_cts(hu->sewdev, twue, 10000);
	if (eww) {
		bt_dev_eww(hu->hdev, "Wait fow CTS faiwed with %d\n", eww);
		wetuwn eww;
	}

	set_bit(STATE_FW_WOADED, &mwvw->fwags);

	eww = __hci_cmd_sync_status(hu->hdev, MWVW_SET_BAUDWATE,
				    sizeof(speed_we), &speed_we,
				    HCI_INIT_TIMEOUT);
	if (eww) {
		bt_dev_eww(hu->hdev, "send command faiwed: %d", eww);
		wetuwn eww;
	}

	sewdev_device_set_baudwate(hu->sewdev, speed);

	/* We fowcefuwwy have to send a command to the bwuetooth moduwe so that
	 * the dwivew detects it aftew a baudwate change. This is foweseen by
	 * hci_sewdev by setting HCI_UAWT_VND_DETECT which then causes a dummy
	 * wocaw vewsion wead.
	 */
	set_bit(HCI_UAWT_VND_DETECT, &hu->hdev_fwags);

	wetuwn 0;
}

static const stwuct hci_uawt_pwoto mwvw_pwoto_8897 = {
	.id		= HCI_UAWT_MWVW,
	.name		= "Mawveww",
	.init_speed	= 115200,
	.opew_speed	= 3000000,
	.open		= mwvw_open,
	.cwose		= mwvw_cwose,
	.fwush		= mwvw_fwush,
	.setup		= mwvw_setup,
	.wecv		= mwvw_wecv,
	.enqueue	= mwvw_enqueue,
	.dequeue	= mwvw_dequeue,
};

static const stwuct hci_uawt_pwoto mwvw_pwoto_8997 = {
	.id		= HCI_UAWT_MWVW,
	.name		= "Mawveww 8997",
	.init_speed	= 115200,
	.opew_speed	= 3000000,
	.open		= mwvw_open,
	.cwose		= mwvw_cwose,
	.fwush		= mwvw_fwush,
	.set_baudwate   = mwvw_set_baudwate,
	.wecv		= mwvw_wecv,
	.enqueue	= mwvw_enqueue,
	.dequeue	= mwvw_dequeue,
};

static int mwvw_sewdev_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct mwvw_sewdev *mwvwdev;
	const stwuct hci_uawt_pwoto *mwvw_pwoto = device_get_match_data(&sewdev->dev);

	mwvwdev = devm_kzawwoc(&sewdev->dev, sizeof(*mwvwdev), GFP_KEWNEW);
	if (!mwvwdev)
		wetuwn -ENOMEM;

	mwvwdev->hu.opew_speed = mwvw_pwoto->opew_speed;
	if (mwvw_pwoto->set_baudwate)
		of_pwopewty_wead_u32(sewdev->dev.of_node, "max-speed", &mwvwdev->hu.opew_speed);

	mwvwdev->hu.sewdev = sewdev;
	sewdev_device_set_dwvdata(sewdev, mwvwdev);

	wetuwn hci_uawt_wegistew_device(&mwvwdev->hu, mwvw_pwoto);
}

static void mwvw_sewdev_wemove(stwuct sewdev_device *sewdev)
{
	stwuct mwvw_sewdev *mwvwdev = sewdev_device_get_dwvdata(sewdev);

	hci_uawt_unwegistew_device(&mwvwdev->hu);
}

static const stwuct of_device_id __maybe_unused mwvw_bwuetooth_of_match[] = {
	{ .compatibwe = "mwvw,88w8897", .data = &mwvw_pwoto_8897},
	{ .compatibwe = "mwvw,88w8997", .data = &mwvw_pwoto_8997},
	{ },
};
MODUWE_DEVICE_TABWE(of, mwvw_bwuetooth_of_match);

static stwuct sewdev_device_dwivew mwvw_sewdev_dwivew = {
	.pwobe = mwvw_sewdev_pwobe,
	.wemove = mwvw_sewdev_wemove,
	.dwivew = {
		.name = "hci_uawt_mwvw",
		.of_match_tabwe = of_match_ptw(mwvw_bwuetooth_of_match),
	},
};

int __init mwvw_init(void)
{
	sewdev_device_dwivew_wegistew(&mwvw_sewdev_dwivew);

	wetuwn hci_uawt_wegistew_pwoto(&mwvw_pwoto_8897);
}

int __exit mwvw_deinit(void)
{
	sewdev_device_dwivew_unwegistew(&mwvw_sewdev_dwivew);

	wetuwn hci_uawt_unwegistew_pwoto(&mwvw_pwoto_8897);
}
