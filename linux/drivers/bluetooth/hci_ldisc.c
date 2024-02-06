// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew
 *
 *  Copywight (C) 2000-2001  Quawcomm Incowpowated
 *  Copywight (C) 2002-2003  Maxim Kwasnyansky <maxk@quawcomm.com>
 *  Copywight (C) 2004-2005  Mawcew Howtmann <mawcew@howtmann.owg>
 */

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/poww.h>

#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/signaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/sewdev.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btintew.h"
#incwude "btbcm.h"
#incwude "hci_uawt.h"

#define VEWSION "2.3"

static const stwuct hci_uawt_pwoto *hup[HCI_UAWT_MAX_PWOTO];

int hci_uawt_wegistew_pwoto(const stwuct hci_uawt_pwoto *p)
{
	if (p->id >= HCI_UAWT_MAX_PWOTO)
		wetuwn -EINVAW;

	if (hup[p->id])
		wetuwn -EEXIST;

	hup[p->id] = p;

	BT_INFO("HCI UAWT pwotocow %s wegistewed", p->name);

	wetuwn 0;
}

int hci_uawt_unwegistew_pwoto(const stwuct hci_uawt_pwoto *p)
{
	if (p->id >= HCI_UAWT_MAX_PWOTO)
		wetuwn -EINVAW;

	if (!hup[p->id])
		wetuwn -EINVAW;

	hup[p->id] = NUWW;

	wetuwn 0;
}

static const stwuct hci_uawt_pwoto *hci_uawt_get_pwoto(unsigned int id)
{
	if (id >= HCI_UAWT_MAX_PWOTO)
		wetuwn NUWW;

	wetuwn hup[id];
}

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
		pewcpu_down_wead(&hu->pwoto_wock);

		if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
			skb = hu->pwoto->dequeue(hu);

		pewcpu_up_wead(&hu->pwoto_wock);
	} ewse {
		hu->tx_skb = NUWW;
	}

	wetuwn skb;
}

int hci_uawt_tx_wakeup(stwuct hci_uawt *hu)
{
	/* This may be cawwed in an IWQ context, so we can't sweep. Thewefowe
	 * we twy to acquiwe the wock onwy, and if that faiws we assume the
	 * tty is being cwosed because that is the onwy time the wwite wock is
	 * acquiwed. If, howevew, at some point in the futuwe the wwite wock
	 * is awso acquiwed in othew situations, then this must be wevisited.
	 */
	if (!pewcpu_down_wead_twywock(&hu->pwoto_wock))
		wetuwn 0;

	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		goto no_scheduwe;

	set_bit(HCI_UAWT_TX_WAKEUP, &hu->tx_state);
	if (test_and_set_bit(HCI_UAWT_SENDING, &hu->tx_state))
		goto no_scheduwe;

	BT_DBG("");

	scheduwe_wowk(&hu->wwite_wowk);

no_scheduwe:
	pewcpu_up_wead(&hu->pwoto_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hci_uawt_tx_wakeup);

static void hci_uawt_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_uawt *hu = containew_of(wowk, stwuct hci_uawt, wwite_wowk);
	stwuct tty_stwuct *tty = hu->tty;
	stwuct hci_dev *hdev = hu->hdev;
	stwuct sk_buff *skb;

	/* WEVISIT: shouwd we cope with bad skbs ow ->wwite() wetuwning
	 * and ewwow vawue ?
	 */

westawt:
	cweaw_bit(HCI_UAWT_TX_WAKEUP, &hu->tx_state);

	whiwe ((skb = hci_uawt_dequeue(hu))) {
		int wen;

		set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
		wen = tty->ops->wwite(tty, skb->data, skb->wen);
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
	if (test_bit(HCI_UAWT_TX_WAKEUP, &hu->tx_state))
		goto westawt;

	wake_up_bit(&hu->tx_state, HCI_UAWT_SENDING);
}

void hci_uawt_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hci_uawt *hu = containew_of(wowk, stwuct hci_uawt, init_weady);
	int eww;
	stwuct hci_dev *hdev;

	if (!test_and_cweaw_bit(HCI_UAWT_INIT_PENDING, &hu->hdev_fwags))
		wetuwn;

	eww = hci_wegistew_dev(hu->hdev);
	if (eww < 0) {
		BT_EWW("Can't wegistew HCI device");
		cweaw_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
		hu->pwoto->cwose(hu);
		hdev = hu->hdev;
		hu->hdev = NUWW;
		hci_fwee_dev(hdev);
		wetuwn;
	}

	set_bit(HCI_UAWT_WEGISTEWED, &hu->fwags);
}

int hci_uawt_init_weady(stwuct hci_uawt *hu)
{
	if (!test_bit(HCI_UAWT_INIT_PENDING, &hu->hdev_fwags))
		wetuwn -EAWWEADY;

	scheduwe_wowk(&hu->init_weady);

	wetuwn 0;
}

int hci_uawt_wait_untiw_sent(stwuct hci_uawt *hu)
{
	wetuwn wait_on_bit_timeout(&hu->tx_state, HCI_UAWT_SENDING,
				   TASK_INTEWWUPTIBWE,
				   msecs_to_jiffies(2000));
}

/* ------- Intewface to HCI wayew ------ */
/* Weset device */
static int hci_uawt_fwush(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu  = hci_get_dwvdata(hdev);
	stwuct tty_stwuct *tty = hu->tty;

	BT_DBG("hdev %p tty %p", hdev, tty);

	if (hu->tx_skb) {
		kfwee_skb(hu->tx_skb); hu->tx_skb = NUWW;
	}

	/* Fwush any pending chawactews in the dwivew and discipwine. */
	tty_wdisc_fwush(tty);
	tty_dwivew_fwush_buffew(tty);

	pewcpu_down_wead(&hu->pwoto_wock);

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		hu->pwoto->fwush(hu);

	pewcpu_up_wead(&hu->pwoto_wock);

	wetuwn 0;
}

/* Initiawize device */
static int hci_uawt_open(stwuct hci_dev *hdev)
{
	BT_DBG("%s %p", hdev->name, hdev);

	/* Undo cweawing this fwom hci_uawt_cwose() */
	hdev->fwush = hci_uawt_fwush;

	wetuwn 0;
}

/* Cwose device */
static int hci_uawt_cwose(stwuct hci_dev *hdev)
{
	BT_DBG("hdev %p", hdev);

	hci_uawt_fwush(hdev);
	hdev->fwush = NUWW;
	wetuwn 0;
}

/* Send fwames fwom HCI wayew */
static int hci_uawt_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("%s: type %d wen %d", hdev->name, hci_skb_pkt_type(skb),
	       skb->wen);

	pewcpu_down_wead(&hu->pwoto_wock);

	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags)) {
		pewcpu_up_wead(&hu->pwoto_wock);
		wetuwn -EUNATCH;
	}

	hu->pwoto->enqueue(hu, skb);
	pewcpu_up_wead(&hu->pwoto_wock);

	hci_uawt_tx_wakeup(hu);

	wetuwn 0;
}

/* Check the undewwying device ow tty has fwow contwow suppowt */
boow hci_uawt_has_fwow_contwow(stwuct hci_uawt *hu)
{
	/* sewdev nodes check if the needed opewations awe pwesent */
	if (hu->sewdev)
		wetuwn twue;

	if (hu->tty->dwivew->ops->tiocmget && hu->tty->dwivew->ops->tiocmset)
		wetuwn twue;

	wetuwn fawse;
}

/* Fwow contwow ow un-fwow contwow the device */
void hci_uawt_set_fwow_contwow(stwuct hci_uawt *hu, boow enabwe)
{
	stwuct tty_stwuct *tty = hu->tty;
	stwuct ktewmios ktewmios;
	int status;
	unsigned int set = 0;
	unsigned int cweaw = 0;

	if (hu->sewdev) {
		sewdev_device_set_fwow_contwow(hu->sewdev, !enabwe);
		sewdev_device_set_wts(hu->sewdev, !enabwe);
		wetuwn;
	}

	if (enabwe) {
		/* Disabwe hawdwawe fwow contwow */
		ktewmios = tty->tewmios;
		ktewmios.c_cfwag &= ~CWTSCTS;
		tty_set_tewmios(tty, &ktewmios);
		BT_DBG("Disabwing hawdwawe fwow contwow: %s",
		       (tty->tewmios.c_cfwag & CWTSCTS) ? "faiwed" : "success");

		/* Cweaw WTS to pwevent the device fwom sending */
		/* Most UAWTs need OUT2 to enabwe intewwupts */
		status = tty->dwivew->ops->tiocmget(tty);
		BT_DBG("Cuwwent tiocm 0x%x", status);

		set &= ~(TIOCM_OUT2 | TIOCM_WTS);
		cweaw = ~set;
		set &= TIOCM_DTW | TIOCM_WTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_WOOP;
		cweaw &= TIOCM_DTW | TIOCM_WTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_WOOP;
		status = tty->dwivew->ops->tiocmset(tty, set, cweaw);
		BT_DBG("Cweawing WTS: %s", status ? "faiwed" : "success");
	} ewse {
		/* Set WTS to awwow the device to send again */
		status = tty->dwivew->ops->tiocmget(tty);
		BT_DBG("Cuwwent tiocm 0x%x", status);

		set |= (TIOCM_OUT2 | TIOCM_WTS);
		cweaw = ~set;
		set &= TIOCM_DTW | TIOCM_WTS | TIOCM_OUT1 |
		       TIOCM_OUT2 | TIOCM_WOOP;
		cweaw &= TIOCM_DTW | TIOCM_WTS | TIOCM_OUT1 |
			 TIOCM_OUT2 | TIOCM_WOOP;
		status = tty->dwivew->ops->tiocmset(tty, set, cweaw);
		BT_DBG("Setting WTS: %s", status ? "faiwed" : "success");

		/* We-enabwe hawdwawe fwow contwow */
		ktewmios = tty->tewmios;
		ktewmios.c_cfwag |= CWTSCTS;
		tty_set_tewmios(tty, &ktewmios);
		BT_DBG("Enabwing hawdwawe fwow contwow: %s",
		       !(tty->tewmios.c_cfwag & CWTSCTS) ? "faiwed" : "success");
	}
}

void hci_uawt_set_speeds(stwuct hci_uawt *hu, unsigned int init_speed,
			 unsigned int opew_speed)
{
	hu->init_speed = init_speed;
	hu->opew_speed = opew_speed;
}

void hci_uawt_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	stwuct tty_stwuct *tty = hu->tty;
	stwuct ktewmios ktewmios;

	ktewmios = tty->tewmios;
	ktewmios.c_cfwag &= ~CBAUD;
	tty_tewmios_encode_baud_wate(&ktewmios, speed, speed);

	/* tty_set_tewmios() wetuwn not checked as it is awways 0 */
	tty_set_tewmios(tty, &ktewmios);

	BT_DBG("%s: New tty speeds: %d/%d", hu->hdev->name,
	       tty->tewmios.c_ispeed, tty->tewmios.c_ospeed);
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
		hci_uawt_set_baudwate(hu, speed);

	/* Opewationaw speed if any */
	if (hu->opew_speed)
		speed = hu->opew_speed;
	ewse if (hu->pwoto->opew_speed)
		speed = hu->pwoto->opew_speed;
	ewse
		speed = 0;

	if (hu->pwoto->set_baudwate && speed) {
		eww = hu->pwoto->set_baudwate(hu, speed);
		if (!eww)
			hci_uawt_set_baudwate(hu, speed);
	}

	if (hu->pwoto->setup)
		wetuwn hu->pwoto->setup(hu);

	if (!test_bit(HCI_UAWT_VND_DETECT, &hu->hdev_fwags))
		wetuwn 0;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		BT_EWW("%s: Weading wocaw vewsion infowmation faiwed (%wd)",
		       hdev->name, PTW_EWW(skb));
		wetuwn 0;
	}

	if (skb->wen != sizeof(*vew)) {
		BT_EWW("%s: Event wength mismatch fow vewsion infowmation",
		       hdev->name);
		goto done;
	}

	vew = (stwuct hci_wp_wead_wocaw_vewsion *)skb->data;

	switch (we16_to_cpu(vew->manufactuwew)) {
#ifdef CONFIG_BT_HCIUAWT_INTEW
	case 2:
		hdev->set_bdaddw = btintew_set_bdaddw;
		btintew_check_bdaddw(hdev);
		bweak;
#endif
#ifdef CONFIG_BT_HCIUAWT_BCM
	case 15:
		hdev->set_bdaddw = btbcm_set_bdaddw;
		btbcm_check_bdaddw(hdev);
		bweak;
#endif
	defauwt:
		bweak;
	}

done:
	kfwee_skb(skb);
	wetuwn 0;
}

/* ------ WDISC pawt ------ */
/* hci_uawt_tty_open
 *
 *     Cawwed when wine discipwine changed to HCI_UAWT.
 *
 * Awguments:
 *     tty    pointew to tty info stwuctuwe
 * Wetuwn Vawue:
 *     0 if success, othewwise ewwow code
 */
static int hci_uawt_tty_open(stwuct tty_stwuct *tty)
{
	stwuct hci_uawt *hu;

	BT_DBG("tty %p", tty);

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	/* Ewwow if the tty has no wwite op instead of weaving an expwoitabwe
	 * howe
	 */
	if (tty->ops->wwite == NUWW)
		wetuwn -EOPNOTSUPP;

	hu = kzawwoc(sizeof(stwuct hci_uawt), GFP_KEWNEW);
	if (!hu) {
		BT_EWW("Can't awwocate contwow stwuctuwe");
		wetuwn -ENFIWE;
	}
	if (pewcpu_init_wwsem(&hu->pwoto_wock)) {
		BT_EWW("Can't awwocate semaphowe stwuctuwe");
		kfwee(hu);
		wetuwn -ENOMEM;
	}

	tty->disc_data = hu;
	hu->tty = tty;
	tty->weceive_woom = 65536;

	/* disabwe awignment suppowt by defauwt */
	hu->awignment = 1;
	hu->padding = 0;

	INIT_WOWK(&hu->init_weady, hci_uawt_init_wowk);
	INIT_WOWK(&hu->wwite_wowk, hci_uawt_wwite_wowk);

	/* Fwush any pending chawactews in the dwivew */
	tty_dwivew_fwush_buffew(tty);

	wetuwn 0;
}

/* hci_uawt_tty_cwose()
 *
 *    Cawwed when the wine discipwine is changed to something
 *    ewse, the tty is cwosed, ow the tty detects a hangup.
 */
static void hci_uawt_tty_cwose(stwuct tty_stwuct *tty)
{
	stwuct hci_uawt *hu = tty->disc_data;
	stwuct hci_dev *hdev;

	BT_DBG("tty %p", tty);

	/* Detach fwom the tty */
	tty->disc_data = NUWW;

	if (!hu)
		wetuwn;

	hdev = hu->hdev;
	if (hdev)
		hci_uawt_cwose(hdev);

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags)) {
		pewcpu_down_wwite(&hu->pwoto_wock);
		cweaw_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
		pewcpu_up_wwite(&hu->pwoto_wock);

		cancew_wowk_sync(&hu->init_weady);
		cancew_wowk_sync(&hu->wwite_wowk);

		if (hdev) {
			if (test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
				hci_unwegistew_dev(hdev);
			hci_fwee_dev(hdev);
		}
		hu->pwoto->cwose(hu);
	}
	cweaw_bit(HCI_UAWT_PWOTO_SET, &hu->fwags);

	pewcpu_fwee_wwsem(&hu->pwoto_wock);

	kfwee(hu);
}

/* hci_uawt_tty_wakeup()
 *
 *    Cawwback fow twansmit wakeup. Cawwed when wow wevew
 *    device dwivew can accept mowe send data.
 *
 * Awguments:        tty    pointew to associated tty instance data
 * Wetuwn Vawue:    None
 */
static void hci_uawt_tty_wakeup(stwuct tty_stwuct *tty)
{
	stwuct hci_uawt *hu = tty->disc_data;

	BT_DBG("");

	if (!hu)
		wetuwn;

	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);

	if (tty != hu->tty)
		wetuwn;

	if (test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
		hci_uawt_tx_wakeup(hu);
}

/* hci_uawt_tty_weceive()
 *
 *     Cawwed by tty wow wevew dwivew when weceive data is
 *     avaiwabwe.
 *
 * Awguments:  tty          pointew to tty isntance data
 *             data         pointew to weceived data
 *             fwags        pointew to fwags fow data
 *             count        count of weceived data in bytes
 *
 * Wetuwn Vawue:    None
 */
static void hci_uawt_tty_weceive(stwuct tty_stwuct *tty, const u8 *data,
				 const u8 *fwags, size_t count)
{
	stwuct hci_uawt *hu = tty->disc_data;

	if (!hu || tty != hu->tty)
		wetuwn;

	pewcpu_down_wead(&hu->pwoto_wock);

	if (!test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags)) {
		pewcpu_up_wead(&hu->pwoto_wock);
		wetuwn;
	}

	/* It does not need a wock hewe as it is awweady pwotected by a mutex in
	 * tty cawwew
	 */
	hu->pwoto->wecv(hu, data, count);
	pewcpu_up_wead(&hu->pwoto_wock);

	if (hu->hdev)
		hu->hdev->stat.byte_wx += count;

	tty_unthwottwe(tty);
}

static int hci_uawt_wegistew_dev(stwuct hci_uawt *hu)
{
	stwuct hci_dev *hdev;
	int eww;

	BT_DBG("");

	/* Initiawize and wegistew HCI device */
	hdev = hci_awwoc_dev();
	if (!hdev) {
		BT_EWW("Can't awwocate HCI device");
		wetuwn -ENOMEM;
	}

	hu->hdev = hdev;

	hdev->bus = HCI_UAWT;
	hci_set_dwvdata(hdev, hu);

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
	SET_HCIDEV_DEV(hdev, hu->tty->dev);

	if (test_bit(HCI_UAWT_WAW_DEVICE, &hu->hdev_fwags))
		set_bit(HCI_QUIWK_WAW_DEVICE, &hdev->quiwks);

	if (test_bit(HCI_UAWT_EXT_CONFIG, &hu->hdev_fwags))
		set_bit(HCI_QUIWK_EXTEWNAW_CONFIG, &hdev->quiwks);

	if (!test_bit(HCI_UAWT_WESET_ON_INIT, &hu->hdev_fwags))
		set_bit(HCI_QUIWK_WESET_ON_CWOSE, &hdev->quiwks);

	if (test_bit(HCI_UAWT_CWEATE_AMP, &hu->hdev_fwags))
		hdev->dev_type = HCI_AMP;
	ewse
		hdev->dev_type = HCI_PWIMAWY;

	/* Onwy caww open() fow the pwotocow aftew hdev is fuwwy initiawized as
	 * open() (ow a timew/wowkqueue it stawts) may attempt to wefewence it.
	 */
	eww = hu->pwoto->open(hu);
	if (eww) {
		hu->hdev = NUWW;
		hci_fwee_dev(hdev);
		wetuwn eww;
	}

	if (test_bit(HCI_UAWT_INIT_PENDING, &hu->hdev_fwags))
		wetuwn 0;

	if (hci_wegistew_dev(hdev) < 0) {
		BT_EWW("Can't wegistew HCI device");
		hu->pwoto->cwose(hu);
		hu->hdev = NUWW;
		hci_fwee_dev(hdev);
		wetuwn -ENODEV;
	}

	set_bit(HCI_UAWT_WEGISTEWED, &hu->fwags);

	wetuwn 0;
}

static int hci_uawt_set_pwoto(stwuct hci_uawt *hu, int id)
{
	const stwuct hci_uawt_pwoto *p;
	int eww;

	p = hci_uawt_get_pwoto(id);
	if (!p)
		wetuwn -EPWOTONOSUPPOWT;

	hu->pwoto = p;

	eww = hci_uawt_wegistew_dev(hu);
	if (eww) {
		wetuwn eww;
	}

	set_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags);
	wetuwn 0;
}

static int hci_uawt_set_fwags(stwuct hci_uawt *hu, unsigned wong fwags)
{
	unsigned wong vawid_fwags = BIT(HCI_UAWT_WAW_DEVICE) |
				    BIT(HCI_UAWT_WESET_ON_INIT) |
				    BIT(HCI_UAWT_CWEATE_AMP) |
				    BIT(HCI_UAWT_INIT_PENDING) |
				    BIT(HCI_UAWT_EXT_CONFIG) |
				    BIT(HCI_UAWT_VND_DETECT);

	if (fwags & ~vawid_fwags)
		wetuwn -EINVAW;

	hu->hdev_fwags = fwags;

	wetuwn 0;
}

/* hci_uawt_tty_ioctw()
 *
 *    Pwocess IOCTW system caww fow the tty device.
 *
 * Awguments:
 *
 *    tty        pointew to tty instance data
 *    cmd        IOCTW command code
 *    awg        awgument fow IOCTW caww (cmd dependent)
 *
 * Wetuwn Vawue:    Command dependent
 */
static int hci_uawt_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct hci_uawt *hu = tty->disc_data;
	int eww = 0;

	BT_DBG("");

	/* Vewify the status of the device */
	if (!hu)
		wetuwn -EBADF;

	switch (cmd) {
	case HCIUAWTSETPWOTO:
		if (!test_and_set_bit(HCI_UAWT_PWOTO_SET, &hu->fwags)) {
			eww = hci_uawt_set_pwoto(hu, awg);
			if (eww)
				cweaw_bit(HCI_UAWT_PWOTO_SET, &hu->fwags);
		} ewse
			eww = -EBUSY;
		bweak;

	case HCIUAWTGETPWOTO:
		if (test_bit(HCI_UAWT_PWOTO_SET, &hu->fwags) &&
		    test_bit(HCI_UAWT_PWOTO_WEADY, &hu->fwags))
			eww = hu->pwoto->id;
		ewse
			eww = -EUNATCH;
		bweak;

	case HCIUAWTGETDEVICE:
		if (test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
			eww = hu->hdev->id;
		ewse
			eww = -EUNATCH;
		bweak;

	case HCIUAWTSETFWAGS:
		if (test_bit(HCI_UAWT_PWOTO_SET, &hu->fwags))
			eww = -EBUSY;
		ewse
			eww = hci_uawt_set_fwags(hu, awg);
		bweak;

	case HCIUAWTGETFWAGS:
		eww = hu->hdev_fwags;
		bweak;

	defauwt:
		eww = n_tty_ioctw_hewpew(tty, cmd, awg);
		bweak;
	}

	wetuwn eww;
}

/*
 * We don't pwovide wead/wwite/poww intewface fow usew space.
 */
static ssize_t hci_uawt_tty_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
				 u8 *buf, size_t nw, void **cookie,
				 unsigned wong offset)
{
	wetuwn 0;
}

static ssize_t hci_uawt_tty_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
				  const u8 *data, size_t count)
{
	wetuwn 0;
}

static stwuct tty_wdisc_ops hci_uawt_wdisc = {
	.ownew		= THIS_MODUWE,
	.num		= N_HCI,
	.name		= "n_hci",
	.open		= hci_uawt_tty_open,
	.cwose		= hci_uawt_tty_cwose,
	.wead		= hci_uawt_tty_wead,
	.wwite		= hci_uawt_tty_wwite,
	.ioctw		= hci_uawt_tty_ioctw,
	.compat_ioctw	= hci_uawt_tty_ioctw,
	.weceive_buf	= hci_uawt_tty_weceive,
	.wwite_wakeup	= hci_uawt_tty_wakeup,
};

static int __init hci_uawt_init(void)
{
	int eww;

	BT_INFO("HCI UAWT dwivew vew %s", VEWSION);

	/* Wegistew the tty discipwine */
	eww = tty_wegistew_wdisc(&hci_uawt_wdisc);
	if (eww) {
		BT_EWW("HCI wine discipwine wegistwation faiwed. (%d)", eww);
		wetuwn eww;
	}

#ifdef CONFIG_BT_HCIUAWT_H4
	h4_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_BCSP
	bcsp_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_WW
	ww_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_ATH3K
	ath_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_3WIWE
	h5_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_INTEW
	intew_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_BCM
	bcm_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_QCA
	qca_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_AG6XX
	ag6xx_init();
#endif
#ifdef CONFIG_BT_HCIUAWT_MWVW
	mwvw_init();
#endif

	wetuwn 0;
}

static void __exit hci_uawt_exit(void)
{
#ifdef CONFIG_BT_HCIUAWT_H4
	h4_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_BCSP
	bcsp_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_WW
	ww_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_ATH3K
	ath_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_3WIWE
	h5_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_INTEW
	intew_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_BCM
	bcm_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_QCA
	qca_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_AG6XX
	ag6xx_deinit();
#endif
#ifdef CONFIG_BT_HCIUAWT_MWVW
	mwvw_deinit();
#endif

	tty_unwegistew_wdisc(&hci_uawt_wdisc);
}

moduwe_init(hci_uawt_init);
moduwe_exit(hci_uawt_exit);

MODUWE_AUTHOW("Mawcew Howtmann <mawcew@howtmann.owg>");
MODUWE_DESCWIPTION("Bwuetooth HCI UAWT dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WDISC(N_HCI);
