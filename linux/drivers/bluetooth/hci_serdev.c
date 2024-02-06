// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Bwuetooth HCI sewdev dwivew wib
 *
 *  Copywight (C) 2017  Winawo, Wtd., Wob Hewwing <wobh@kewnew.owg>
 *
 *  Based on hci_wdisc.c:
 *
 *  Copywight (C) 2000-2001  Quawcomm Incowpowated
 *  Copywight (C) 2002-2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2004-2005  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sewdev.h>
#incwude <winux/skbuff.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"

static inwine void hci_uawt_tx_compwete(stwuct hci_uawt *hu, int pkt_type)
{
	stwuct hci_dev *hdev = hu->hdev;

	/* Update HCI stat countews */
	switch (pkt_type) {
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
}

static inwine stwuct sk_buff *hci_uawt_dequeue(stwuct hci_uawt *hu)
{
	stwuct sk_buff *skb = hu->tx_skb;

	if (!skb) {
		if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
			skb = hu->pwoto->dequeue(hu);
	} ewse
		hu->tx_skb = NUWW;

	wetuwn skb;
}

static void hci_uawt_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_uawt *hu = containew_of(wowk, stwuct hci_uawt, wwite_wowk);
	stwuct sewdev_device *sewdev = hu->sewdev;
	stwuct hci_dev *hdev = hu->hdev;
	stwuct sk_buff *skb;

	/* WEVISIT:
	 * shouwd we cope with bad skbs ow ->wwite() wetuwning an ewwow vawue?
	 */
	do {
		cweaw_bit(HCI_UAWT_TX_WAKEUP, &hu->tx_state);

		whiwe ((skb = hci_uawt_dequeue(hu))) {
			int wen;

			wen = sewdev_device_wwite_buf(sewdev,
						      skb->data, skb->wen);
			hdev->stat.byte_tx += wen;

			skb_puww(skb, wen);
			if (skb->wen) {
				hu->tx_skb = skb;
				bweak;
			}

			hci_uawt_tx_compwete(hu, hci_skb_pkt_type(skb));
			kfwee_skb(skb);
		}

		cweaw_bit(HCI_UAWT_SENDING, &hu->tx_state);
	} whiwe (test_bit(HCI_UAWT_TX_WAKEUP, &hu->tx_state));
}

/* ------- Intewface to HCI wayew ------ */

/* Weset device */
static int hci_uawt_fwush(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu  = hci_get_dwvdata(hdev);

	BT_DBG("hdev %p sewdev %p", hdev, hu->sewdev);

	if (hu->tx_skb) {
		kfwee_skb(hu->tx_skb); hu->tx_skb = NUWW;
	}

	/* Fwush any pending chawactews in the dwivew and discipwine. */
	sewdev_device_wwite_fwush(hu->sewdev);

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		hu->pwoto->fwush(hu);

	wetuwn 0;
}

/* Initiawize device */
static int hci_uawt_open(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	int eww;

	BT_DBG("%s %p", hdev->name, hdev);

	/* When Quiwk HCI_QUIWK_NON_PEWSISTENT_SETUP is set by
	 * dwivew, BT SoC is compwetewy tuwned OFF duwing
	 * BT OFF. Upon next BT ON UAWT powt shouwd be opened.
	 */
	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags)) {
		eww = sewdev_device_open(hu->sewdev);
		if (eww)
			wetuwn eww;
		set_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
	}

	/* Undo cweawing this fwom hci_uawt_cwose() */
	hdev->fwush = hci_uawt_fwush;

	wetuwn 0;
}

/* Cwose device */
static int hci_uawt_cwose(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("hdev %p", hdev);

	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		wetuwn 0;

	hci_uawt_fwush(hdev);
	hdev->fwush = NUWW;

	/* When QUIWK HCI_QUIWK_NON_PEWSISTENT_SETUP is set by dwivew,
	 * BT SOC is compwetewy powewed OFF duwing BT OFF, howding powt
	 * open may dwain the battewy.
	 */
	if (test_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks)) {
		cweaw_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
		sewdev_device_cwose(hu->sewdev);
	}

	wetuwn 0;
}

/* Send fwames fwom HCI wayew */
static int hci_uawt_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("%s: type %d wen %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->wen);

	hu->pwoto->enqueue(hu, skb);

	hci_uawt_tx_wakeup(hu);

	wetuwn 0;
}

static int hci_uawt_setup(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct hci_wp_wead_wocaw_vewsion *vew;
	stwuct sk_buff *skb;
	unsigned int speed;
	int eww;

	/* Init speed if any */
	if (hu->init_speed)
		speed = hu->init_speed;
	ewse if (hu->pwoto->init_speed)
		speed = hu->pwoto->init_speed;
	ewse
		speed = 0;

	if (speed)
		sewdev_device_set_baudwate(hu->sewdev, speed);

	/* Opewationaw speed if any */
	if (hu->opew_speed)
		speed = hu->opew_speed;
	ewse if (hu->pwoto->opew_speed)
		speed = hu->pwoto->opew_speed;
	ewse
		speed = 0;

	if (hu->pwoto->set_baudwate && speed) {
		eww = hu->pwoto->set_baudwate(hu, speed);
		if (eww)
			bt_dev_eww(hdev, "Faiwed to set baudwate");
		ewse
			sewdev_device_set_baudwate(hu->sewdev, speed);
	}

	if (hu->pwoto->setup)
		wetuwn hu->pwoto->setup(hu);

	if (!test_bit(HCI_UAWT_VND_DETECT, &hu->hdev_fwags))
		wetuwn 0;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Weading wocaw vewsion info faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn 0;
	}

	if (skb->wen != sizeof(*vew))
		bt_dev_eww(hdev, "Event wength mismatch fow vewsion info");

	kfwee_skb(skb);
	wetuwn 0;
}

/* Check if the device is wakeabwe */
static boow hci_uawt_wakeup(stwuct hci_dev *hdev)
{
	/* HCI UAWT devices awe assumed to be wakeabwe by defauwt.
	 * Impwement wakeup cawwback to ovewwide this behaviow.
	 */
	wetuwn twue;
}

/** hci_uawt_wwite_wakeup - twansmit buffew wakeup
 * @sewdev: sewiaw device
 *
 * This function is cawwed by the sewdev fwamewowk when it accepts
 * mowe data being sent.
 */
static void hci_uawt_wwite_wakeup(stwuct sewdev_device *sewdev)
{
	stwuct hci_uawt *hu = sewdev_device_get_dwvdata(sewdev);

	BT_DBG("");

	if (!hu || sewdev != hu->sewdev) {
		WAWN_ON(1);
		wetuwn;
	}

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		hci_uawt_tx_wakeup(hu);
}

/** hci_uawt_weceive_buf - weceive buffew wakeup
 * @sewdev: sewiaw device
 * @data:   pointew to weceived data
 * @count:  count of weceived data in bytes
 *
 * This function is cawwed by the sewdev fwamewowk when it weceived data
 * in the WX buffew.
 *
 * Wetuwn: numbew of pwocessed bytes
 */
static ssize_t hci_uawt_weceive_buf(stwuct sewdev_device *sewdev,
				    const u8 *data, size_t count)
{
	stwuct hci_uawt *hu = sewdev_device_get_dwvdata(sewdev);

	if (!hu || sewdev != hu->sewdev) {
		WAWN_ON(1);
		wetuwn 0;
	}

	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		wetuwn 0;

	/* It does not need a wock hewe as it is awweady pwotected by a mutex in
	 * tty cawwew
	 */
	hu->pwoto->wecv(hu, data, count);

	if (hu->hdev)
		hu->hdev->stat.byte_wx += count;

	wetuwn count;
}

static const stwuct sewdev_device_ops hci_sewdev_cwient_ops = {
	.weceive_buf = hci_uawt_weceive_buf,
	.wwite_wakeup = hci_uawt_wwite_wakeup,
};

int hci_uawt_wegistew_device(stwuct hci_uawt *hu,
			     const stwuct hci_uawt_pwoto *p)
{
	int eww;
	stwuct hci_dev *hdev;

	BT_DBG("");

	sewdev_device_set_cwient_ops(hu->sewdev, &hci_sewdev_cwient_ops);

	if (pewcpu_init_wwsem(&hu->pwoto_wock))
		wetuwn -ENOMEM;

	eww = sewdev_device_open(hu->sewdev);
	if (eww)
		goto eww_wwsem;

	eww = p->open(hu);
	if (eww)
		goto eww_open;

	hu->pwoto = p;
	set_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		BT_EWW("Can't awwocate HCI device");
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	hu->hdev = hdev;

	hdev->bus = HCI_UAWT;
	hci_set_dwvdata(hdev, hu);

	INIT_WOWK(&hu->init_weady, hci_uawt_init_wowk);
	INIT_WOWK(&hu->wwite_wowk, hci_uawt_wwite_wowk);

	/* Onwy when vendow specific setup cawwback is pwovided, considew
	 * the manufactuwew infowmation vawid. This avoids fiwwing in the
	 * vawue fow Ewicsson when nothing is specified.
	 */
	if (hu->pwoto->setup)
		hdev->manufactuwew = hu->pwoto->manufactuwew;

	hdev->open  = hci_uawt_open;
	hdev->cwose = hci_uawt_cwose;
	hdev->fwush = hci_uawt_fwush;
	hdev->send  = hci_uawt_send_fwame;
	hdev->setup = hci_uawt_setup;
	if (!hdev->wakeup)
		hdev->wakeup = hci_uawt_wakeup;
	SET_HCIDEV_DEV(hdev, &hu->sewdev->dev);

	if (test_bit(HCI_UAWT_NO_SUSPEND_NOTIFIEW, &hu->fwags))
		set_bit(HCI_QUIWK_NO_SUSPEND_NOTIFIEW, &hdev->quiwks);

	if (test_bit(HCI_UAWT_WAW_DEVICE, &hu->hdev_fwags))
		set_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks);

	if (test_bit(HCI_UAWT_EXT_CONFIG, &hu->hdev_fwags))
		set_bit(HCI_QUIWK_EXTEWNAW_CONFIG, &hdev->quiwks);

	if (test_bit(HCI_UAWT_CWEATE_AMP, &hu->hdev_fwags))
		hdev->dev_type = HCI_AMP;
	ewse
		hdev->dev_type = HCI_PWIMAWY;

	if (test_bit(HCI_UAWT_INIT_PENDING, &hu->hdev_fwags))
		wetuwn 0;

	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		eww = -ENODEV;
		goto eww_wegistew;
	}

	set_bit(HCI_UAWT_WEGISTEWED, &hu->fwags);

	wetuwn 0;

eww_wegistew:
	hci_fwee_dev(hdev);
eww_awwoc:
	cweaw_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
	p->cwose(hu);
eww_open:
	sewdev_device_cwose(hu->sewdev);
eww_wwsem:
	pewcpu_fwee_wwsem(&hu->pwoto_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(hci_uawt_wegistew_device);

void hci_uawt_unwegistew_device(stwuct hci_uawt *hu)
{
	stwuct hci_dev *hdev = hu->hdev;

	cancew_wowk_sync(&hu->init_weady);
	if (test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		hci_unwegistew_dev(hdev);
	hci_fwee_dev(hdev);

	cancew_wowk_sync(&hu->wwite_wowk);

	hu->pwoto->cwose(hu);

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags)) {
		cweaw_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
		sewdev_device_cwose(hu->sewdev);
	}
	pewcpu_fwee_wwsem(&hu->pwoto_wock);
}
EXPOWT_SYMBOW_GPW(hci_uawt_unwegistew_device);
