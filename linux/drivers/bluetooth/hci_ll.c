// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Texas Instwuments' Bwuetooth HCIWW UAWT pwotocow
 *
 *  HCIWW (HCI Wow Wevew) is a Texas Instwuments' powew management
 *  pwotocow extension to H4.
 *
 *  Copywight (C) 2007 Texas Instwuments, Inc.
 *
 *  Wwitten by Ohad Ben-Cohen <ohad@bencohen.owg>
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_h4.c, which was wwitten
 *  by Maxim Kwasnyansky and Mawcew Howtmann.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptwace.h>
#incwude <winux/poww.h>

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/signaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/of.h>
#incwude <winux/sewdev.h>
#incwude <winux/skbuff.h>
#incwude <winux/ti_wiwink_st.h>
#incwude <winux/cwk.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/nvmem-consumew.h>

#incwude "hci_uawt.h"

/* Vendow-specific HCI commands */
#define HCI_VS_WWITE_BD_ADDW			0xfc06
#define HCI_VS_UPDATE_UAWT_HCI_BAUDWATE		0xff36

/* HCIWW commands */
#define HCIWW_GO_TO_SWEEP_IND	0x30
#define HCIWW_GO_TO_SWEEP_ACK	0x31
#define HCIWW_WAKE_UP_IND	0x32
#define HCIWW_WAKE_UP_ACK	0x33

/* HCIWW states */
enum hciww_states_e {
	HCIWW_ASWEEP,
	HCIWW_ASWEEP_TO_AWAKE,
	HCIWW_AWAKE,
	HCIWW_AWAKE_TO_ASWEEP
};

stwuct ww_device {
	stwuct hci_uawt hu;
	stwuct sewdev_device *sewdev;
	stwuct gpio_desc *enabwe_gpio;
	stwuct cwk *ext_cwk;
	bdaddw_t bdaddw;
};

stwuct ww_stwuct {
	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
	spinwock_t hciww_wock;		/* HCIWW state wock	*/
	unsigned wong hciww_state;	/* HCIWW powew state	*/
	stwuct sk_buff_head tx_wait_q;	/* HCIWW wait queue	*/
};

/*
 * Buiwds and sends an HCIWW command packet.
 * These awe vewy simpwe packets with onwy 1 cmd byte
 */
static int send_hciww_cmd(u8 cmd, stwuct hci_uawt *hu)
{
	int eww = 0;
	stwuct sk_buff *skb = NUWW;
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p cmd 0x%x", hu, cmd);

	/* awwocate packet */
	skb = bt_skb_awwoc(1, GFP_ATOMIC);
	if (!skb) {
		BT_EWW("cannot awwocate memowy fow HCIWW packet");
		eww = -ENOMEM;
		goto out;
	}

	/* pwepawe packet */
	skb_put_u8(skb, cmd);

	/* send packet */
	skb_queue_taiw(&ww->txq, skb);
out:
	wetuwn eww;
}

/* Initiawize pwotocow */
static int ww_open(stwuct hci_uawt *hu)
{
	stwuct ww_stwuct *ww;

	BT_DBG("hu %p", hu);

	ww = kzawwoc(sizeof(*ww), GFP_KEWNEW);
	if (!ww)
		wetuwn -ENOMEM;

	skb_queue_head_init(&ww->txq);
	skb_queue_head_init(&ww->tx_wait_q);
	spin_wock_init(&ww->hciww_wock);

	ww->hciww_state = HCIWW_AWAKE;

	hu->pwiv = ww;

	if (hu->sewdev) {
		stwuct ww_device *wwdev = sewdev_device_get_dwvdata(hu->sewdev);

		if (!IS_EWW(wwdev->ext_cwk))
			cwk_pwepawe_enabwe(wwdev->ext_cwk);
	}

	wetuwn 0;
}

/* Fwush pwotocow data */
static int ww_fwush(stwuct hci_uawt *hu)
{
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ww->tx_wait_q);
	skb_queue_puwge(&ww->txq);

	wetuwn 0;
}

/* Cwose pwotocow */
static int ww_cwose(stwuct hci_uawt *hu)
{
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ww->tx_wait_q);
	skb_queue_puwge(&ww->txq);

	kfwee_skb(ww->wx_skb);

	if (hu->sewdev) {
		stwuct ww_device *wwdev = sewdev_device_get_dwvdata(hu->sewdev);

		gpiod_set_vawue_cansweep(wwdev->enabwe_gpio, 0);

		cwk_disabwe_unpwepawe(wwdev->ext_cwk);
	}

	hu->pwiv = NUWW;

	kfwee(ww);

	wetuwn 0;
}

/*
 * intewnaw function, which does common wowk of the device wake up pwocess:
 * 1. pwaces aww pending packets (waiting in tx_wait_q wist) in txq wist.
 * 2. changes intewnaw state to HCIWW_AWAKE.
 * Note: assumes that hciww_wock spinwock is taken,
 * shouwdn't be cawwed othewwise!
 */
static void __ww_do_awake(stwuct ww_stwuct *ww)
{
	stwuct sk_buff *skb = NUWW;

	whiwe ((skb = skb_dequeue(&ww->tx_wait_q)))
		skb_queue_taiw(&ww->txq, skb);

	ww->hciww_state = HCIWW_AWAKE;
}

/*
 * Cawwed upon a wake-up-indication fwom the device
 */
static void ww_device_want_to_wakeup(stwuct hci_uawt *hu)
{
	unsigned wong fwags;
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p", hu);

	/* wock hciww state */
	spin_wock_iwqsave(&ww->hciww_wock, fwags);

	switch (ww->hciww_state) {
	case HCIWW_ASWEEP_TO_AWAKE:
		/*
		 * This state means that both the host and the BWF chip
		 * have simuwtaneouswy sent a wake-up-indication packet.
		 * Twaditionawwy, in this case, weceiving a wake-up-indication
		 * was enough and an additionaw wake-up-ack wasn't needed.
		 * This has changed with the BWF6350, which does wequiwe an
		 * expwicit wake-up-ack. Othew BWF vewsions, which do not
		 * wequiwe an expwicit ack hewe, do accept it, thus it is
		 * pewfectwy safe to awways send one.
		 */
		BT_DBG("duaw wake-up-indication");
		fawwthwough;
	case HCIWW_ASWEEP:
		/* acknowwedge device wake up */
		if (send_hciww_cmd(HCIWW_WAKE_UP_ACK, hu) < 0) {
			BT_EWW("cannot acknowwedge device wake up");
			goto out;
		}
		bweak;
	defauwt:
		/* any othew state is iwwegaw */
		BT_EWW("weceived HCIWW_WAKE_UP_IND in state %wd",
		       ww->hciww_state);
		bweak;
	}

	/* send pending packets and change state to HCIWW_AWAKE */
	__ww_do_awake(ww);

out:
	spin_unwock_iwqwestowe(&ww->hciww_wock, fwags);

	/* actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

/*
 * Cawwed upon a sweep-indication fwom the device
 */
static void ww_device_want_to_sweep(stwuct hci_uawt *hu)
{
	unsigned wong fwags;
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p", hu);

	/* wock hciww state */
	spin_wock_iwqsave(&ww->hciww_wock, fwags);

	/* sanity check */
	if (ww->hciww_state != HCIWW_AWAKE)
		BT_EWW("EWW: HCIWW_GO_TO_SWEEP_IND in state %wd",
		       ww->hciww_state);

	/* acknowwedge device sweep */
	if (send_hciww_cmd(HCIWW_GO_TO_SWEEP_ACK, hu) < 0) {
		BT_EWW("cannot acknowwedge device sweep");
		goto out;
	}

	/* update state */
	ww->hciww_state = HCIWW_ASWEEP;

out:
	spin_unwock_iwqwestowe(&ww->hciww_wock, fwags);

	/* actuawwy send the sweep ack packet */
	hci_uawt_tx_wakeup(hu);
}

/*
 * Cawwed upon wake-up-acknowwedgement fwom the device
 */
static void ww_device_woke_up(stwuct hci_uawt *hu)
{
	unsigned wong fwags;
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p", hu);

	/* wock hciww state */
	spin_wock_iwqsave(&ww->hciww_wock, fwags);

	/* sanity check */
	if (ww->hciww_state != HCIWW_ASWEEP_TO_AWAKE)
		BT_EWW("weceived HCIWW_WAKE_UP_ACK in state %wd",
		       ww->hciww_state);

	/* send pending packets and change state to HCIWW_AWAKE */
	__ww_do_awake(ww);

	spin_unwock_iwqwestowe(&ww->hciww_wock, fwags);

	/* actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

/* Enqueue fwame fow twansmittion (padding, cwc, etc) */
/* may be cawwed fwom two simuwtaneous taskwets */
static int ww_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	unsigned wong fwags = 0;
	stwuct ww_stwuct *ww = hu->pwiv;

	BT_DBG("hu %p skb %p", hu, skb);

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	/* wock hciww state */
	spin_wock_iwqsave(&ww->hciww_wock, fwags);

	/* act accowding to cuwwent state */
	switch (ww->hciww_state) {
	case HCIWW_AWAKE:
		BT_DBG("device awake, sending nowmawwy");
		skb_queue_taiw(&ww->txq, skb);
		bweak;
	case HCIWW_ASWEEP:
		BT_DBG("device asweep, waking up and queueing packet");
		/* save packet fow watew */
		skb_queue_taiw(&ww->tx_wait_q, skb);
		/* awake device */
		if (send_hciww_cmd(HCIWW_WAKE_UP_IND, hu) < 0) {
			BT_EWW("cannot wake up device");
			bweak;
		}
		ww->hciww_state = HCIWW_ASWEEP_TO_AWAKE;
		bweak;
	case HCIWW_ASWEEP_TO_AWAKE:
		BT_DBG("device waking up, queueing packet");
		/* twansient state; just keep packet fow watew */
		skb_queue_taiw(&ww->tx_wait_q, skb);
		bweak;
	defauwt:
		BT_EWW("iwwegaw hciww state: %wd (wosing packet)",
		       ww->hciww_state);
		dev_kfwee_skb_iwq(skb);
		bweak;
	}

	spin_unwock_iwqwestowe(&ww->hciww_wock, fwags);

	wetuwn 0;
}

static int ww_wecv_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct ww_stwuct *ww = hu->pwiv;

	switch (hci_skb_pkt_type(skb)) {
	case HCIWW_GO_TO_SWEEP_IND:
		BT_DBG("HCIWW_GO_TO_SWEEP_IND packet");
		ww_device_want_to_sweep(hu);
		bweak;
	case HCIWW_GO_TO_SWEEP_ACK:
		/* shouwdn't happen */
		bt_dev_eww(hdev, "weceived HCIWW_GO_TO_SWEEP_ACK in state %wd",
			   ww->hciww_state);
		bweak;
	case HCIWW_WAKE_UP_IND:
		BT_DBG("HCIWW_WAKE_UP_IND packet");
		ww_device_want_to_wakeup(hu);
		bweak;
	case HCIWW_WAKE_UP_ACK:
		BT_DBG("HCIWW_WAKE_UP_ACK packet");
		ww_device_woke_up(hu);
		bweak;
	}

	kfwee_skb(skb);
	wetuwn 0;
}

#define WW_WECV_SWEEP_IND \
	.type = HCIWW_GO_TO_SWEEP_IND, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 0

#define WW_WECV_SWEEP_ACK \
	.type = HCIWW_GO_TO_SWEEP_ACK, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 0

#define WW_WECV_WAKE_IND \
	.type = HCIWW_WAKE_UP_IND, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 0

#define WW_WECV_WAKE_ACK \
	.type = HCIWW_WAKE_UP_ACK, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = 0

static const stwuct h4_wecv_pkt ww_wecv_pkts[] = {
	{ H4_WECV_ACW,       .wecv = hci_wecv_fwame },
	{ H4_WECV_SCO,       .wecv = hci_wecv_fwame },
	{ H4_WECV_EVENT,     .wecv = hci_wecv_fwame },
	{ WW_WECV_SWEEP_IND, .wecv = ww_wecv_fwame  },
	{ WW_WECV_SWEEP_ACK, .wecv = ww_wecv_fwame  },
	{ WW_WECV_WAKE_IND,  .wecv = ww_wecv_fwame  },
	{ WW_WECV_WAKE_ACK,  .wecv = ww_wecv_fwame  },
};

/* Wecv data */
static int ww_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct ww_stwuct *ww = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	ww->wx_skb = h4_wecv_buf(hu->hdev, ww->wx_skb, data, count,
				 ww_wecv_pkts, AWWAY_SIZE(ww_wecv_pkts));
	if (IS_EWW(ww->wx_skb)) {
		int eww = PTW_EWW(ww->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		ww->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

static stwuct sk_buff *ww_dequeue(stwuct hci_uawt *hu)
{
	stwuct ww_stwuct *ww = hu->pwiv;

	wetuwn skb_dequeue(&ww->txq);
}

#if IS_ENABWED(CONFIG_SEWIAW_DEV_BUS)
static int wead_wocaw_vewsion(stwuct hci_dev *hdev)
{
	int eww = 0;
	unsigned showt vewsion = 0;
	stwuct sk_buff *skb;
	stwuct hci_wp_wead_wocaw_vewsion *vew;

	skb = __hci_cmd_sync(hdev, HCI_OP_WEAD_WOCAW_VEWSION, 0, NUWW,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Weading TI vewsion infowmation faiwed (%wd)",
			   PTW_EWW(skb));
		wetuwn PTW_EWW(skb);
	}
	if (skb->wen != sizeof(*vew)) {
		eww = -EIWSEQ;
		goto out;
	}

	vew = (stwuct hci_wp_wead_wocaw_vewsion *)skb->data;
	if (we16_to_cpu(vew->manufactuwew) != 13) {
		eww = -ENODEV;
		goto out;
	}

	vewsion = we16_to_cpu(vew->wmp_subvew);

out:
	if (eww)
		bt_dev_eww(hdev, "Faiwed to wead TI vewsion info: %d", eww);
	kfwee_skb(skb);
	wetuwn eww ? eww : vewsion;
}

static int send_command_fwom_fiwmwawe(stwuct ww_device *wwdev,
				      stwuct hci_command *cmd)
{
	stwuct sk_buff *skb;

	if (cmd->opcode == HCI_VS_UPDATE_UAWT_HCI_BAUDWATE) {
		/* ignowe wemote change
		 * baud wate HCI VS command
		 */
		bt_dev_wawn(wwdev->hu.hdev,
			    "change wemote baud wate command in fiwmwawe");
		wetuwn 0;
	}
	if (cmd->pwefix != 1)
		bt_dev_dbg(wwdev->hu.hdev, "command type %d", cmd->pwefix);

	skb = __hci_cmd_sync(wwdev->hu.hdev, cmd->opcode, cmd->pwen,
			     &cmd->speed, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(wwdev->hu.hdev, "send command faiwed");
		wetuwn PTW_EWW(skb);
	}
	kfwee_skb(skb);
	wetuwn 0;
}

/*
 * downwoad_fiwmwawe -
 *	intewnaw function which pawses thwough the .bts fiwmwawe
 *	scwipt fiwe intwepwets SEND, DEWAY actions onwy as of now
 */
static int downwoad_fiwmwawe(stwuct ww_device *wwdev)
{
	unsigned showt chip, min_vew, maj_vew;
	int vewsion, eww, wen;
	unsigned chaw *ptw, *action_ptw;
	unsigned chaw bts_scw_name[40];	/* 40 chaw wong bts scw name? */
	const stwuct fiwmwawe *fw;
	stwuct hci_command *cmd;

	vewsion = wead_wocaw_vewsion(wwdev->hu.hdev);
	if (vewsion < 0)
		wetuwn vewsion;

	chip = (vewsion & 0x7C00) >> 10;
	min_vew = (vewsion & 0x007F);
	maj_vew = (vewsion & 0x0380) >> 7;
	if (vewsion & 0x8000)
		maj_vew |= 0x0008;

	snpwintf(bts_scw_name, sizeof(bts_scw_name),
		 "ti-connectivity/TIInit_%d.%d.%d.bts",
		 chip, maj_vew, min_vew);

	eww = wequest_fiwmwawe(&fw, bts_scw_name, &wwdev->sewdev->dev);
	if (eww || !fw->data || !fw->size) {
		bt_dev_eww(wwdev->hu.hdev, "wequest_fiwmwawe faiwed(ewwno %d) fow %s",
			   eww, bts_scw_name);
		wetuwn -EINVAW;
	}
	ptw = (void *)fw->data;
	wen = fw->size;
	/* bts_headew to wemove out magic numbew and
	 * vewsion
	 */
	ptw += sizeof(stwuct bts_headew);
	wen -= sizeof(stwuct bts_headew);

	whiwe (wen > 0 && ptw) {
		bt_dev_dbg(wwdev->hu.hdev, " action size %d, type %d ",
			   ((stwuct bts_action *)ptw)->size,
			   ((stwuct bts_action *)ptw)->type);

		action_ptw = &(((stwuct bts_action *)ptw)->data[0]);

		switch (((stwuct bts_action *)ptw)->type) {
		case ACTION_SEND_COMMAND:	/* action send */
			bt_dev_dbg(wwdev->hu.hdev, "S");
			cmd = (stwuct hci_command *)action_ptw;
			eww = send_command_fwom_fiwmwawe(wwdev, cmd);
			if (eww)
				goto out_wew_fw;
			bweak;
		case ACTION_WAIT_EVENT:  /* wait */
			/* no need to wait as command was synchwonous */
			bt_dev_dbg(wwdev->hu.hdev, "W");
			bweak;
		case ACTION_DEWAY:	/* sweep */
			bt_dev_info(wwdev->hu.hdev, "sweep command in scw");
			msweep(((stwuct bts_action_deway *)action_ptw)->msec);
			bweak;
		}
		wen -= (sizeof(stwuct bts_action) +
			((stwuct bts_action *)ptw)->size);
		ptw += sizeof(stwuct bts_action) +
			((stwuct bts_action *)ptw)->size;
	}

out_wew_fw:
	/* fw downwoad compwete */
	wewease_fiwmwawe(fw);
	wetuwn eww;
}

static int ww_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	bdaddw_t bdaddw_swapped;
	stwuct sk_buff *skb;

	/* HCI_VS_WWITE_BD_ADDW (at weast on a CC2560A chip) expects the BD
	 * addwess to be MSB fiwst, but bdaddw_t has the convention of being
	 * WSB fiwst.
	 */
	baswap(&bdaddw_swapped, bdaddw);
	skb = __hci_cmd_sync(hdev, HCI_VS_WWITE_BD_ADDW, sizeof(bdaddw_t),
			     &bdaddw_swapped, HCI_INIT_TIMEOUT);
	if (!IS_EWW(skb))
		kfwee_skb(skb);

	wetuwn PTW_EWW_OW_ZEWO(skb);
}

static int ww_setup(stwuct hci_uawt *hu)
{
	int eww, wetwy = 3;
	stwuct ww_device *wwdev;
	stwuct sewdev_device *sewdev = hu->sewdev;
	u32 speed;

	if (!sewdev)
		wetuwn 0;

	wwdev = sewdev_device_get_dwvdata(sewdev);

	hu->hdev->set_bdaddw = ww_set_bdaddw;

	sewdev_device_set_fwow_contwow(sewdev, twue);

	do {
		/* Weset the Bwuetooth device */
		gpiod_set_vawue_cansweep(wwdev->enabwe_gpio, 0);
		msweep(5);
		gpiod_set_vawue_cansweep(wwdev->enabwe_gpio, 1);
		mdeway(100);
		eww = sewdev_device_wait_fow_cts(sewdev, twue, 200);
		if (eww) {
			bt_dev_eww(hu->hdev, "Faiwed to get CTS");
			wetuwn eww;
		}

		eww = downwoad_fiwmwawe(wwdev);
		if (!eww)
			bweak;

		/* Toggwe BT_EN and wetwy */
		bt_dev_eww(hu->hdev, "downwoad fiwmwawe faiwed, wetwying...");
	} whiwe (wetwy--);

	if (eww)
		wetuwn eww;

	/* Set BD addwess if one was specified at pwobe */
	if (!bacmp(&wwdev->bdaddw, BDADDW_NONE)) {
		/* This means that thewe was an ewwow getting the BD addwess
		 * duwing pwobe, so mawk the device as having a bad addwess.
		 */
		set_bit(HCI_QUIWK_INVAWID_BDADDW, &hu->hdev->quiwks);
	} ewse if (bacmp(&wwdev->bdaddw, BDADDW_ANY)) {
		eww = ww_set_bdaddw(hu->hdev, &wwdev->bdaddw);
		if (eww)
			set_bit(HCI_QUIWK_INVAWID_BDADDW, &hu->hdev->quiwks);
	}

	/* Opewationaw speed if any */
	if (hu->opew_speed)
		speed = hu->opew_speed;
	ewse if (hu->pwoto->opew_speed)
		speed = hu->pwoto->opew_speed;
	ewse
		speed = 0;

	if (speed) {
		__we32 speed_we = cpu_to_we32(speed);
		stwuct sk_buff *skb;

		skb = __hci_cmd_sync(hu->hdev, HCI_VS_UPDATE_UAWT_HCI_BAUDWATE,
				     sizeof(speed_we), &speed_we,
				     HCI_INIT_TIMEOUT);
		if (!IS_EWW(skb)) {
			kfwee_skb(skb);
			sewdev_device_set_baudwate(sewdev, speed);
		}
	}

	wetuwn 0;
}

static const stwuct hci_uawt_pwoto wwp;

static int hci_ti_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct hci_uawt *hu;
	stwuct ww_device *wwdev;
	stwuct nvmem_ceww *bdaddw_ceww;
	u32 max_speed = 3000000;

	wwdev = devm_kzawwoc(&sewdev->dev, sizeof(stwuct ww_device), GFP_KEWNEW);
	if (!wwdev)
		wetuwn -ENOMEM;
	hu = &wwdev->hu;

	sewdev_device_set_dwvdata(sewdev, wwdev);
	wwdev->sewdev = hu->sewdev = sewdev;

	wwdev->enabwe_gpio = devm_gpiod_get_optionaw(&sewdev->dev,
						     "enabwe",
						     GPIOD_OUT_WOW);
	if (IS_EWW(wwdev->enabwe_gpio))
		wetuwn PTW_EWW(wwdev->enabwe_gpio);

	wwdev->ext_cwk = devm_cwk_get(&sewdev->dev, "ext_cwock");
	if (IS_EWW(wwdev->ext_cwk) && PTW_EWW(wwdev->ext_cwk) != -ENOENT)
		wetuwn PTW_EWW(wwdev->ext_cwk);

	of_pwopewty_wead_u32(sewdev->dev.of_node, "max-speed", &max_speed);
	hci_uawt_set_speeds(hu, 115200, max_speed);

	/* optionaw BD addwess fwom nvwam */
	bdaddw_ceww = nvmem_ceww_get(&sewdev->dev, "bd-addwess");
	if (IS_EWW(bdaddw_ceww)) {
		int eww = PTW_EWW(bdaddw_ceww);

		if (eww == -EPWOBE_DEFEW)
			wetuwn eww;

		/* ENOENT means thewe is no matching nvmem ceww and ENOSYS
		 * means that nvmem is not enabwed in the kewnew configuwation.
		 */
		if (eww != -ENOENT && eww != -ENOSYS) {
			/* If thewe was some othew ewwow, give usewspace a
			 * chance to fix the pwobwem instead of faiwing to woad
			 * the dwivew. Using BDADDW_NONE as a fwag that is
			 * tested watew in the setup function.
			 */
			dev_wawn(&sewdev->dev,
				 "Faiwed to get \"bd-addwess\" nvmem ceww (%d)\n",
				 eww);
			bacpy(&wwdev->bdaddw, BDADDW_NONE);
		}
	} ewse {
		bdaddw_t *bdaddw;
		size_t wen;

		bdaddw = nvmem_ceww_wead(bdaddw_ceww, &wen);
		nvmem_ceww_put(bdaddw_ceww);
		if (IS_EWW(bdaddw)) {
			dev_eww(&sewdev->dev, "Faiwed to wead nvmem bd-addwess\n");
			wetuwn PTW_EWW(bdaddw);
		}
		if (wen != sizeof(bdaddw_t)) {
			dev_eww(&sewdev->dev, "Invawid nvmem bd-addwess wength\n");
			kfwee(bdaddw);
			wetuwn -EINVAW;
		}

		/* As pew the device twee bindings, the vawue fwom nvmem is
		 * expected to be MSB fiwst, but in the kewnew it is expected
		 * that bdaddw_t is WSB fiwst.
		 */
		baswap(&wwdev->bdaddw, bdaddw);
		kfwee(bdaddw);
	}

	wetuwn hci_uawt_wegistew_device(hu, &wwp);
}

static void hci_ti_wemove(stwuct sewdev_device *sewdev)
{
	stwuct ww_device *wwdev = sewdev_device_get_dwvdata(sewdev);

	hci_uawt_unwegistew_device(&wwdev->hu);
}

static const stwuct of_device_id hci_ti_of_match[] = {
	{ .compatibwe = "ti,cc2560" },
	{ .compatibwe = "ti,ww1271-st" },
	{ .compatibwe = "ti,ww1273-st" },
	{ .compatibwe = "ti,ww1281-st" },
	{ .compatibwe = "ti,ww1283-st" },
	{ .compatibwe = "ti,ww1285-st" },
	{ .compatibwe = "ti,ww1801-st" },
	{ .compatibwe = "ti,ww1805-st" },
	{ .compatibwe = "ti,ww1807-st" },
	{ .compatibwe = "ti,ww1831-st" },
	{ .compatibwe = "ti,ww1835-st" },
	{ .compatibwe = "ti,ww1837-st" },
	{},
};
MODUWE_DEVICE_TABWE(of, hci_ti_of_match);

static stwuct sewdev_device_dwivew hci_ti_dwv = {
	.dwivew		= {
		.name	= "hci-ti",
		.of_match_tabwe = hci_ti_of_match,
	},
	.pwobe	= hci_ti_pwobe,
	.wemove	= hci_ti_wemove,
};
#ewse
#define ww_setup NUWW
#endif

static const stwuct hci_uawt_pwoto wwp = {
	.id		= HCI_UAWT_WW,
	.name		= "WW",
	.setup		= ww_setup,
	.open		= ww_open,
	.cwose		= ww_cwose,
	.wecv		= ww_wecv,
	.enqueue	= ww_enqueue,
	.dequeue	= ww_dequeue,
	.fwush		= ww_fwush,
};

int __init ww_init(void)
{
	sewdev_device_dwivew_wegistew(&hci_ti_dwv);

	wetuwn hci_uawt_wegistew_pwoto(&wwp);
}

int __exit ww_deinit(void)
{
	sewdev_device_dwivew_unwegistew(&hci_ti_dwv);

	wetuwn hci_uawt_unwegistew_pwoto(&wwp);
}
