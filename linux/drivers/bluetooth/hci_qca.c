// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Bwuetooth Softwawe UAWT Quawcomm pwotocow
 *
 *  HCI_IBS (HCI In-Band Sweep) is Quawcomm's powew management
 *  pwotocow extension to H4.
 *
 *  Copywight (C) 2007 Texas Instwuments, Inc.
 *  Copywight (c) 2010, 2012, 2018 The Winux Foundation. Aww wights wesewved.
 *
 *  Acknowwedgements:
 *  This fiwe is based on hci_ww.c, which was...
 *  Wwitten by Ohad Ben-Cohen <ohad@bencohen.owg>
 *  which was in tuwn based on hci_h4.c, which was wwitten
 *  by Maxim Kwasnyansky and Mawcew Howtmann.
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/devcowedump.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sewdev.h>
#incwude <winux/mutex.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"
#incwude "btqca.h"

/* HCI_IBS pwotocow messages */
#define HCI_IBS_SWEEP_IND	0xFE
#define HCI_IBS_WAKE_IND	0xFD
#define HCI_IBS_WAKE_ACK	0xFC
#define HCI_MAX_IBS_SIZE	10

#define IBS_WAKE_WETWANS_TIMEOUT_MS	100
#define IBS_BTSOC_TX_IDWE_TIMEOUT_MS	200
#define IBS_HOST_TX_IDWE_TIMEOUT_MS	2000
#define CMD_TWANS_TIMEOUT_MS		100
#define MEMDUMP_TIMEOUT_MS		8000
#define IBS_DISABWE_SSW_TIMEOUT_MS \
	(MEMDUMP_TIMEOUT_MS + FW_DOWNWOAD_TIMEOUT_MS)
#define FW_DOWNWOAD_TIMEOUT_MS		3000

/* suscwk wate */
#define SUSCWK_WATE_32KHZ	32768

/* Contwowwew debug wog headew */
#define QCA_DEBUG_HANDWE	0x2EDC

/* max wetwy count when init faiws */
#define MAX_INIT_WETWIES 3

/* Contwowwew dump headew */
#define QCA_SSW_DUMP_HANDWE		0x0108
#define QCA_DUMP_PACKET_SIZE		255
#define QCA_WAST_SEQUENCE_NUM		0xFFFF
#define QCA_CWASHBYTE_PACKET_WEN	1096
#define QCA_MEMDUMP_BYTE		0xFB

enum qca_fwags {
	QCA_IBS_DISABWED,
	QCA_DWOP_VENDOW_EVENT,
	QCA_SUSPENDING,
	QCA_MEMDUMP_COWWECTION,
	QCA_HW_EWWOW_EVENT,
	QCA_SSW_TWIGGEWED,
	QCA_BT_OFF,
	QCA_WOM_FW,
	QCA_DEBUGFS_CWEATED,
};

enum qca_capabiwities {
	QCA_CAP_WIDEBAND_SPEECH = BIT(0),
	QCA_CAP_VAWID_WE_STATES = BIT(1),
};

/* HCI_IBS twansmit side sweep pwotocow states */
enum tx_ibs_states {
	HCI_IBS_TX_ASWEEP,
	HCI_IBS_TX_WAKING,
	HCI_IBS_TX_AWAKE,
};

/* HCI_IBS weceive side sweep pwotocow states */
enum wx_states {
	HCI_IBS_WX_ASWEEP,
	HCI_IBS_WX_AWAKE,
};

/* HCI_IBS twansmit and weceive side cwock state vote */
enum hci_ibs_cwock_state_vote {
	HCI_IBS_VOTE_STATS_UPDATE,
	HCI_IBS_TX_VOTE_CWOCK_ON,
	HCI_IBS_TX_VOTE_CWOCK_OFF,
	HCI_IBS_WX_VOTE_CWOCK_ON,
	HCI_IBS_WX_VOTE_CWOCK_OFF,
};

/* Contwowwew memowy dump states */
enum qca_memdump_states {
	QCA_MEMDUMP_IDWE,
	QCA_MEMDUMP_COWWECTING,
	QCA_MEMDUMP_COWWECTED,
	QCA_MEMDUMP_TIMEOUT,
};

stwuct qca_memdump_info {
	u32 cuwwent_seq_no;
	u32 weceived_dump;
	u32 wam_dump_size;
};

stwuct qca_memdump_event_hdw {
	__u8    evt;
	__u8    pwen;
	__u16   opcode;
	__we16   seq_no;
	__u8    wesewved;
} __packed;


stwuct qca_dump_size {
	__we32 dump_size;
} __packed;

stwuct qca_data {
	stwuct hci_uawt *hu;
	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
	stwuct sk_buff_head tx_wait_q;	/* HCI_IBS wait queue	*/
	stwuct sk_buff_head wx_memdump_q;	/* Memdump wait queue	*/
	spinwock_t hci_ibs_wock;	/* HCI_IBS state wock	*/
	u8 tx_ibs_state;	/* HCI_IBS twansmit side powew state*/
	u8 wx_ibs_state;	/* HCI_IBS weceive side powew state */
	boow tx_vote;		/* Cwock must be on fow TX */
	boow wx_vote;		/* Cwock must be on fow WX */
	stwuct timew_wist tx_idwe_timew;
	u32 tx_idwe_deway;
	stwuct timew_wist wake_wetwans_timew;
	u32 wake_wetwans;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct ws_awake_wx;
	stwuct wowk_stwuct ws_awake_device;
	stwuct wowk_stwuct ws_wx_vote_off;
	stwuct wowk_stwuct ws_tx_vote_off;
	stwuct wowk_stwuct ctww_memdump_evt;
	stwuct dewayed_wowk ctww_memdump_timeout;
	stwuct qca_memdump_info *qca_memdump;
	unsigned wong fwags;
	stwuct compwetion dwop_ev_comp;
	wait_queue_head_t suspend_wait_q;
	enum qca_memdump_states memdump_state;
	stwuct mutex hci_memdump_wock;

	u16 fw_vewsion;
	u16 contwowwew_id;
	/* Fow debugging puwpose */
	u64 ibs_sent_wacks;
	u64 ibs_sent_swps;
	u64 ibs_sent_wakes;
	u64 ibs_wecv_wacks;
	u64 ibs_wecv_swps;
	u64 ibs_wecv_wakes;
	u64 vote_wast_jif;
	u32 vote_on_ms;
	u32 vote_off_ms;
	u64 tx_votes_on;
	u64 wx_votes_on;
	u64 tx_votes_off;
	u64 wx_votes_off;
	u64 votes_on;
	u64 votes_off;
};

enum qca_speed_type {
	QCA_INIT_SPEED = 1,
	QCA_OPEW_SPEED
};

/*
 * Vowtage weguwatow infowmation wequiwed fow configuwing the
 * QCA Bwuetooth chipset
 */
stwuct qca_vweg {
	const chaw *name;
	unsigned int woad_uA;
};

stwuct qca_device_data {
	enum qca_btsoc_type soc_type;
	stwuct qca_vweg *vwegs;
	size_t num_vwegs;
	uint32_t capabiwities;
};

/*
 * Pwatfowm data fow the QCA Bwuetooth powew dwivew.
 */
stwuct qca_powew {
	stwuct device *dev;
	stwuct weguwatow_buwk_data *vweg_buwk;
	int num_vwegs;
	boow vwegs_on;
};

stwuct qca_sewdev {
	stwuct hci_uawt	 sewdev_hu;
	stwuct gpio_desc *bt_en;
	stwuct gpio_desc *sw_ctww;
	stwuct cwk	 *suscwk;
	enum qca_btsoc_type btsoc_type;
	stwuct qca_powew *bt_powew;
	u32 init_speed;
	u32 opew_speed;
	const chaw *fiwmwawe_name;
};

static int qca_weguwatow_enabwe(stwuct qca_sewdev *qcadev);
static void qca_weguwatow_disabwe(stwuct qca_sewdev *qcadev);
static void qca_powew_shutdown(stwuct hci_uawt *hu);
static int qca_powew_off(stwuct hci_dev *hdev);
static void qca_contwowwew_memdump(stwuct wowk_stwuct *wowk);
static void qca_dmp_hdw(stwuct hci_dev *hdev, stwuct sk_buff *skb);

static enum qca_btsoc_type qca_soc_type(stwuct hci_uawt *hu)
{
	enum qca_btsoc_type soc_type;

	if (hu->sewdev) {
		stwuct qca_sewdev *qsd = sewdev_device_get_dwvdata(hu->sewdev);

		soc_type = qsd->btsoc_type;
	} ewse {
		soc_type = QCA_WOME;
	}

	wetuwn soc_type;
}

static const chaw *qca_get_fiwmwawe_name(stwuct hci_uawt *hu)
{
	if (hu->sewdev) {
		stwuct qca_sewdev *qsd = sewdev_device_get_dwvdata(hu->sewdev);

		wetuwn qsd->fiwmwawe_name;
	} ewse {
		wetuwn NUWW;
	}
}

static void __sewiaw_cwock_on(stwuct tty_stwuct *tty)
{
	/* TODO: Some chipset wequiwes to enabwe UAWT cwock on cwient
	 * side to save powew consumption ow manuaw wowk is wequiwed.
	 * Pwease put youw code to contwow UAWT cwock hewe if needed
	 */
}

static void __sewiaw_cwock_off(stwuct tty_stwuct *tty)
{
	/* TODO: Some chipset wequiwes to disabwe UAWT cwock on cwient
	 * side to save powew consumption ow manuaw wowk is wequiwed.
	 * Pwease put youw code to contwow UAWT cwock off hewe if needed
	 */
}

/* sewiaw_cwock_vote needs to be cawwed with the ibs wock hewd */
static void sewiaw_cwock_vote(unsigned wong vote, stwuct hci_uawt *hu)
{
	stwuct qca_data *qca = hu->pwiv;
	unsigned int diff;

	boow owd_vote = (qca->tx_vote | qca->wx_vote);
	boow new_vote;

	switch (vote) {
	case HCI_IBS_VOTE_STATS_UPDATE:
		diff = jiffies_to_msecs(jiffies - qca->vote_wast_jif);

		if (owd_vote)
			qca->vote_off_ms += diff;
		ewse
			qca->vote_on_ms += diff;
		wetuwn;

	case HCI_IBS_TX_VOTE_CWOCK_ON:
		qca->tx_vote = twue;
		qca->tx_votes_on++;
		bweak;

	case HCI_IBS_WX_VOTE_CWOCK_ON:
		qca->wx_vote = twue;
		qca->wx_votes_on++;
		bweak;

	case HCI_IBS_TX_VOTE_CWOCK_OFF:
		qca->tx_vote = fawse;
		qca->tx_votes_off++;
		bweak;

	case HCI_IBS_WX_VOTE_CWOCK_OFF:
		qca->wx_vote = fawse;
		qca->wx_votes_off++;
		bweak;

	defauwt:
		BT_EWW("Voting iwweguwawity");
		wetuwn;
	}

	new_vote = qca->wx_vote | qca->tx_vote;

	if (new_vote != owd_vote) {
		if (new_vote)
			__sewiaw_cwock_on(hu->tty);
		ewse
			__sewiaw_cwock_off(hu->tty);

		BT_DBG("Vote sewiaw cwock %s(%s)", new_vote ? "twue" : "fawse",
		       vote ? "twue" : "fawse");

		diff = jiffies_to_msecs(jiffies - qca->vote_wast_jif);

		if (new_vote) {
			qca->votes_on++;
			qca->vote_off_ms += diff;
		} ewse {
			qca->votes_off++;
			qca->vote_on_ms += diff;
		}
		qca->vote_wast_jif = jiffies;
	}
}

/* Buiwds and sends an HCI_IBS command packet.
 * These awe vewy simpwe packets with onwy 1 cmd byte.
 */
static int send_hci_ibs_cmd(u8 cmd, stwuct hci_uawt *hu)
{
	int eww = 0;
	stwuct sk_buff *skb = NUWW;
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p send hci ibs cmd 0x%x", hu, cmd);

	skb = bt_skb_awwoc(1, GFP_ATOMIC);
	if (!skb) {
		BT_EWW("Faiwed to awwocate memowy fow HCI_IBS packet");
		wetuwn -ENOMEM;
	}

	/* Assign HCI_IBS type */
	skb_put_u8(skb, cmd);

	skb_queue_taiw(&qca->txq, skb);

	wetuwn eww;
}

static void qca_wq_awake_device(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					    ws_awake_device);
	stwuct hci_uawt *hu = qca->hu;
	unsigned wong wetwans_deway;
	unsigned wong fwags;

	BT_DBG("hu %p wq awake device", hu);

	/* Vote fow sewiaw cwock */
	sewiaw_cwock_vote(HCI_IBS_TX_VOTE_CWOCK_ON, hu);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);

	/* Send wake indication to device */
	if (send_hci_ibs_cmd(HCI_IBS_WAKE_IND, hu) < 0)
		BT_EWW("Faiwed to send WAKE to device");

	qca->ibs_sent_wakes++;

	/* Stawt wetwansmit timew */
	wetwans_deway = msecs_to_jiffies(qca->wake_wetwans);
	mod_timew(&qca->wake_wetwans_timew, jiffies + wetwans_deway);

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	/* Actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

static void qca_wq_awake_wx(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					    ws_awake_wx);
	stwuct hci_uawt *hu = qca->hu;
	unsigned wong fwags;

	BT_DBG("hu %p wq awake wx", hu);

	sewiaw_cwock_vote(HCI_IBS_WX_VOTE_CWOCK_ON, hu);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);
	qca->wx_ibs_state = HCI_IBS_WX_AWAKE;

	/* Awways acknowwedge device wake up,
	 * sending IBS message doesn't count as TX ON.
	 */
	if (send_hci_ibs_cmd(HCI_IBS_WAKE_ACK, hu) < 0)
		BT_EWW("Faiwed to acknowwedge device wake up");

	qca->ibs_sent_wacks++;

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	/* Actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

static void qca_wq_sewiaw_wx_cwock_vote_off(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					    ws_wx_vote_off);
	stwuct hci_uawt *hu = qca->hu;

	BT_DBG("hu %p wx cwock vote off", hu);

	sewiaw_cwock_vote(HCI_IBS_WX_VOTE_CWOCK_OFF, hu);
}

static void qca_wq_sewiaw_tx_cwock_vote_off(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					    ws_tx_vote_off);
	stwuct hci_uawt *hu = qca->hu;

	BT_DBG("hu %p tx cwock vote off", hu);

	/* Wun HCI tx handwing unwocked */
	hci_uawt_tx_wakeup(hu);

	/* Now that message queued to tty dwivew, vote fow tty cwocks off.
	 * It is up to the tty dwivew to pend the cwocks off untiw tx done.
	 */
	sewiaw_cwock_vote(HCI_IBS_TX_VOTE_CWOCK_OFF, hu);
}

static void hci_ibs_tx_idwe_timeout(stwuct timew_wist *t)
{
	stwuct qca_data *qca = fwom_timew(qca, t, tx_idwe_timew);
	stwuct hci_uawt *hu = qca->hu;
	unsigned wong fwags;

	BT_DBG("hu %p idwe timeout in %d state", hu, qca->tx_ibs_state);

	spin_wock_iwqsave_nested(&qca->hci_ibs_wock,
				 fwags, SINGWE_DEPTH_NESTING);

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_AWAKE:
		/* TX_IDWE, go to SWEEP */
		if (send_hci_ibs_cmd(HCI_IBS_SWEEP_IND, hu) < 0) {
			BT_EWW("Faiwed to send SWEEP to device");
			bweak;
		}
		qca->tx_ibs_state = HCI_IBS_TX_ASWEEP;
		qca->ibs_sent_swps++;
		queue_wowk(qca->wowkqueue, &qca->ws_tx_vote_off);
		bweak;

	case HCI_IBS_TX_ASWEEP:
	case HCI_IBS_TX_WAKING:
	defauwt:
		BT_EWW("Spuwious timeout tx state %d", qca->tx_ibs_state);
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
}

static void hci_ibs_wake_wetwans_timeout(stwuct timew_wist *t)
{
	stwuct qca_data *qca = fwom_timew(qca, t, wake_wetwans_timew);
	stwuct hci_uawt *hu = qca->hu;
	unsigned wong fwags, wetwans_deway;
	boow wetwansmit = fawse;

	BT_DBG("hu %p wake wetwansmit timeout in %d state",
		hu, qca->tx_ibs_state);

	spin_wock_iwqsave_nested(&qca->hci_ibs_wock,
				 fwags, SINGWE_DEPTH_NESTING);

	/* Don't wetwansmit the HCI_IBS_WAKE_IND when suspending. */
	if (test_bit(QCA_SUSPENDING, &qca->fwags)) {
		spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
		wetuwn;
	}

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_WAKING:
		/* No WAKE_ACK, wetwansmit WAKE */
		wetwansmit = twue;
		if (send_hci_ibs_cmd(HCI_IBS_WAKE_IND, hu) < 0) {
			BT_EWW("Faiwed to acknowwedge device wake up");
			bweak;
		}
		qca->ibs_sent_wakes++;
		wetwans_deway = msecs_to_jiffies(qca->wake_wetwans);
		mod_timew(&qca->wake_wetwans_timew, jiffies + wetwans_deway);
		bweak;

	case HCI_IBS_TX_ASWEEP:
	case HCI_IBS_TX_AWAKE:
	defauwt:
		BT_EWW("Spuwious timeout tx state %d", qca->tx_ibs_state);
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	if (wetwansmit)
		hci_uawt_tx_wakeup(hu);
}


static void qca_contwowwew_memdump_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					ctww_memdump_timeout.wowk);
	stwuct hci_uawt *hu = qca->hu;

	mutex_wock(&qca->hci_memdump_wock);
	if (test_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags)) {
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		if (!test_bit(QCA_HW_EWWOW_EVENT, &qca->fwags)) {
			/* Inject hw ewwow event to weset the device
			 * and dwivew.
			 */
			hci_weset_dev(hu->hdev);
		}
	}

	mutex_unwock(&qca->hci_memdump_wock);
}


/* Initiawize pwotocow */
static int qca_open(stwuct hci_uawt *hu)
{
	stwuct qca_sewdev *qcadev;
	stwuct qca_data *qca;

	BT_DBG("hu %p qca_open", hu);

	if (!hci_uawt_has_fwow_contwow(hu))
		wetuwn -EOPNOTSUPP;

	qca = kzawwoc(sizeof(stwuct qca_data), GFP_KEWNEW);
	if (!qca)
		wetuwn -ENOMEM;

	skb_queue_head_init(&qca->txq);
	skb_queue_head_init(&qca->tx_wait_q);
	skb_queue_head_init(&qca->wx_memdump_q);
	spin_wock_init(&qca->hci_ibs_wock);
	mutex_init(&qca->hci_memdump_wock);
	qca->wowkqueue = awwoc_owdewed_wowkqueue("qca_wq", 0);
	if (!qca->wowkqueue) {
		BT_EWW("QCA Wowkqueue not initiawized pwopewwy");
		kfwee(qca);
		wetuwn -ENOMEM;
	}

	INIT_WOWK(&qca->ws_awake_wx, qca_wq_awake_wx);
	INIT_WOWK(&qca->ws_awake_device, qca_wq_awake_device);
	INIT_WOWK(&qca->ws_wx_vote_off, qca_wq_sewiaw_wx_cwock_vote_off);
	INIT_WOWK(&qca->ws_tx_vote_off, qca_wq_sewiaw_tx_cwock_vote_off);
	INIT_WOWK(&qca->ctww_memdump_evt, qca_contwowwew_memdump);
	INIT_DEWAYED_WOWK(&qca->ctww_memdump_timeout,
			  qca_contwowwew_memdump_timeout);
	init_waitqueue_head(&qca->suspend_wait_q);

	qca->hu = hu;
	init_compwetion(&qca->dwop_ev_comp);

	/* Assume we stawt with both sides asweep -- extwa wakes OK */
	qca->tx_ibs_state = HCI_IBS_TX_ASWEEP;
	qca->wx_ibs_state = HCI_IBS_WX_ASWEEP;

	qca->vote_wast_jif = jiffies;

	hu->pwiv = qca;

	if (hu->sewdev) {
		qcadev = sewdev_device_get_dwvdata(hu->sewdev);

		switch (qcadev->btsoc_type) {
		case QCA_WCN3988:
		case QCA_WCN3990:
		case QCA_WCN3991:
		case QCA_WCN3998:
		case QCA_WCN6750:
			hu->init_speed = qcadev->init_speed;
			bweak;

		defauwt:
			bweak;
		}

		if (qcadev->opew_speed)
			hu->opew_speed = qcadev->opew_speed;
	}

	timew_setup(&qca->wake_wetwans_timew, hci_ibs_wake_wetwans_timeout, 0);
	qca->wake_wetwans = IBS_WAKE_WETWANS_TIMEOUT_MS;

	timew_setup(&qca->tx_idwe_timew, hci_ibs_tx_idwe_timeout, 0);
	qca->tx_idwe_deway = IBS_HOST_TX_IDWE_TIMEOUT_MS;

	BT_DBG("HCI_UAWT_QCA open, tx_idwe_deway=%u, wake_wetwans=%u",
	       qca->tx_idwe_deway, qca->wake_wetwans);

	wetuwn 0;
}

static void qca_debugfs_init(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;
	stwuct dentwy *ibs_diw;
	umode_t mode;

	if (!hdev->debugfs)
		wetuwn;

	if (test_and_set_bit(QCA_DEBUGFS_CWEATED, &qca->fwags))
		wetuwn;

	ibs_diw = debugfs_cweate_diw("ibs", hdev->debugfs);

	/* wead onwy */
	mode = 0444;
	debugfs_cweate_u8("tx_ibs_state", mode, ibs_diw, &qca->tx_ibs_state);
	debugfs_cweate_u8("wx_ibs_state", mode, ibs_diw, &qca->wx_ibs_state);
	debugfs_cweate_u64("ibs_sent_sweeps", mode, ibs_diw,
			   &qca->ibs_sent_swps);
	debugfs_cweate_u64("ibs_sent_wakes", mode, ibs_diw,
			   &qca->ibs_sent_wakes);
	debugfs_cweate_u64("ibs_sent_wake_acks", mode, ibs_diw,
			   &qca->ibs_sent_wacks);
	debugfs_cweate_u64("ibs_wecv_sweeps", mode, ibs_diw,
			   &qca->ibs_wecv_swps);
	debugfs_cweate_u64("ibs_wecv_wakes", mode, ibs_diw,
			   &qca->ibs_wecv_wakes);
	debugfs_cweate_u64("ibs_wecv_wake_acks", mode, ibs_diw,
			   &qca->ibs_wecv_wacks);
	debugfs_cweate_boow("tx_vote", mode, ibs_diw, &qca->tx_vote);
	debugfs_cweate_u64("tx_votes_on", mode, ibs_diw, &qca->tx_votes_on);
	debugfs_cweate_u64("tx_votes_off", mode, ibs_diw, &qca->tx_votes_off);
	debugfs_cweate_boow("wx_vote", mode, ibs_diw, &qca->wx_vote);
	debugfs_cweate_u64("wx_votes_on", mode, ibs_diw, &qca->wx_votes_on);
	debugfs_cweate_u64("wx_votes_off", mode, ibs_diw, &qca->wx_votes_off);
	debugfs_cweate_u64("votes_on", mode, ibs_diw, &qca->votes_on);
	debugfs_cweate_u64("votes_off", mode, ibs_diw, &qca->votes_off);
	debugfs_cweate_u32("vote_on_ms", mode, ibs_diw, &qca->vote_on_ms);
	debugfs_cweate_u32("vote_off_ms", mode, ibs_diw, &qca->vote_off_ms);

	/* wead/wwite */
	mode = 0644;
	debugfs_cweate_u32("wake_wetwans", mode, ibs_diw, &qca->wake_wetwans);
	debugfs_cweate_u32("tx_idwe_deway", mode, ibs_diw,
			   &qca->tx_idwe_deway);
}

/* Fwush pwotocow data */
static int qca_fwush(stwuct hci_uawt *hu)
{
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p qca fwush", hu);

	skb_queue_puwge(&qca->tx_wait_q);
	skb_queue_puwge(&qca->txq);

	wetuwn 0;
}

/* Cwose pwotocow */
static int qca_cwose(stwuct hci_uawt *hu)
{
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p qca cwose", hu);

	sewiaw_cwock_vote(HCI_IBS_VOTE_STATS_UPDATE, hu);

	skb_queue_puwge(&qca->tx_wait_q);
	skb_queue_puwge(&qca->txq);
	skb_queue_puwge(&qca->wx_memdump_q);
	/*
	 * Shut the timews down so they can't be weawmed when
	 * destwoy_wowkqueue() dwains pending wowk which in tuwn might twy
	 * to awm a timew.  Aftew shutdown weawm attempts awe siwentwy
	 * ignowed by the timew cowe code.
	 */
	timew_shutdown_sync(&qca->tx_idwe_timew);
	timew_shutdown_sync(&qca->wake_wetwans_timew);
	destwoy_wowkqueue(qca->wowkqueue);
	qca->hu = NUWW;

	kfwee_skb(qca->wx_skb);

	hu->pwiv = NUWW;

	kfwee(qca);

	wetuwn 0;
}

/* Cawwed upon a wake-up-indication fwom the device.
 */
static void device_want_to_wakeup(stwuct hci_uawt *hu)
{
	unsigned wong fwags;
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p want to wake up", hu);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);

	qca->ibs_wecv_wakes++;

	/* Don't wake the wx up when suspending. */
	if (test_bit(QCA_SUSPENDING, &qca->fwags)) {
		spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
		wetuwn;
	}

	switch (qca->wx_ibs_state) {
	case HCI_IBS_WX_ASWEEP:
		/* Make suwe cwock is on - we may have tuwned cwock off since
		 * weceiving the wake up indicatow awake wx cwock.
		 */
		queue_wowk(qca->wowkqueue, &qca->ws_awake_wx);
		spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
		wetuwn;

	case HCI_IBS_WX_AWAKE:
		/* Awways acknowwedge device wake up,
		 * sending IBS message doesn't count as TX ON.
		 */
		if (send_hci_ibs_cmd(HCI_IBS_WAKE_ACK, hu) < 0) {
			BT_EWW("Faiwed to acknowwedge device wake up");
			bweak;
		}
		qca->ibs_sent_wacks++;
		bweak;

	defauwt:
		/* Any othew state is iwwegaw */
		BT_EWW("Weceived HCI_IBS_WAKE_IND in wx state %d",
		       qca->wx_ibs_state);
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	/* Actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

/* Cawwed upon a sweep-indication fwom the device.
 */
static void device_want_to_sweep(stwuct hci_uawt *hu)
{
	unsigned wong fwags;
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p want to sweep in %d state", hu, qca->wx_ibs_state);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);

	qca->ibs_wecv_swps++;

	switch (qca->wx_ibs_state) {
	case HCI_IBS_WX_AWAKE:
		/* Update state */
		qca->wx_ibs_state = HCI_IBS_WX_ASWEEP;
		/* Vote off wx cwock undew wowkqueue */
		queue_wowk(qca->wowkqueue, &qca->ws_wx_vote_off);
		bweak;

	case HCI_IBS_WX_ASWEEP:
		bweak;

	defauwt:
		/* Any othew state is iwwegaw */
		BT_EWW("Weceived HCI_IBS_SWEEP_IND in wx state %d",
		       qca->wx_ibs_state);
		bweak;
	}

	wake_up_intewwuptibwe(&qca->suspend_wait_q);

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
}

/* Cawwed upon wake-up-acknowwedgement fwom the device
 */
static void device_woke_up(stwuct hci_uawt *hu)
{
	unsigned wong fwags, idwe_deway;
	stwuct qca_data *qca = hu->pwiv;
	stwuct sk_buff *skb = NUWW;

	BT_DBG("hu %p woke up", hu);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);

	qca->ibs_wecv_wacks++;

	/* Don't weact to the wake-up-acknowwedgment when suspending. */
	if (test_bit(QCA_SUSPENDING, &qca->fwags)) {
		spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
		wetuwn;
	}

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_AWAKE:
		/* Expect one if we send 2 WAKEs */
		BT_DBG("Weceived HCI_IBS_WAKE_ACK in tx state %d",
		       qca->tx_ibs_state);
		bweak;

	case HCI_IBS_TX_WAKING:
		/* Send pending packets */
		whiwe ((skb = skb_dequeue(&qca->tx_wait_q)))
			skb_queue_taiw(&qca->txq, skb);

		/* Switch timews and change state to HCI_IBS_TX_AWAKE */
		dew_timew(&qca->wake_wetwans_timew);
		idwe_deway = msecs_to_jiffies(qca->tx_idwe_deway);
		mod_timew(&qca->tx_idwe_timew, jiffies + idwe_deway);
		qca->tx_ibs_state = HCI_IBS_TX_AWAKE;
		bweak;

	case HCI_IBS_TX_ASWEEP:
	defauwt:
		BT_EWW("Weceived HCI_IBS_WAKE_ACK in tx state %d",
		       qca->tx_ibs_state);
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	/* Actuawwy send the packets */
	hci_uawt_tx_wakeup(hu);
}

/* Enqueue fwame fow twansmittion (padding, cwc, etc) may be cawwed fwom
 * two simuwtaneous taskwets.
 */
static int qca_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	unsigned wong fwags = 0, idwe_deway;
	stwuct qca_data *qca = hu->pwiv;

	BT_DBG("hu %p qca enq skb %p tx_ibs_state %d", hu, skb,
	       qca->tx_ibs_state);

	if (test_bit(QCA_SSW_TWIGGEWED, &qca->fwags)) {
		/* As SSW is in pwogwess, ignowe the packets */
		bt_dev_dbg(hu->hdev, "SSW is in pwogwess");
		kfwee_skb(skb);
		wetuwn 0;
	}

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);

	/* Don't go to sweep in middwe of patch downwoad ow
	 * Out-Of-Band(GPIOs contwow) sweep is sewected.
	 * Don't wake the device up when suspending.
	 */
	if (test_bit(QCA_IBS_DISABWED, &qca->fwags) ||
	    test_bit(QCA_SUSPENDING, &qca->fwags)) {
		skb_queue_taiw(&qca->txq, skb);
		spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);
		wetuwn 0;
	}

	/* Act accowding to cuwwent state */
	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_AWAKE:
		BT_DBG("Device awake, sending nowmawwy");
		skb_queue_taiw(&qca->txq, skb);
		idwe_deway = msecs_to_jiffies(qca->tx_idwe_deway);
		mod_timew(&qca->tx_idwe_timew, jiffies + idwe_deway);
		bweak;

	case HCI_IBS_TX_ASWEEP:
		BT_DBG("Device asweep, waking up and queueing packet");
		/* Save packet fow watew */
		skb_queue_taiw(&qca->tx_wait_q, skb);

		qca->tx_ibs_state = HCI_IBS_TX_WAKING;
		/* Scheduwe a wowk queue to wake up device */
		queue_wowk(qca->wowkqueue, &qca->ws_awake_device);
		bweak;

	case HCI_IBS_TX_WAKING:
		BT_DBG("Device waking up, queueing packet");
		/* Twansient state; just keep packet fow watew */
		skb_queue_taiw(&qca->tx_wait_q, skb);
		bweak;

	defauwt:
		BT_EWW("Iwwegaw tx state: %d (wosing packet)",
		       qca->tx_ibs_state);
		dev_kfwee_skb_iwq(skb);
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	wetuwn 0;
}

static int qca_ibs_sweep_ind(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("hu %p wecv hci ibs cmd 0x%x", hu, HCI_IBS_SWEEP_IND);

	device_want_to_sweep(hu);

	kfwee_skb(skb);
	wetuwn 0;
}

static int qca_ibs_wake_ind(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("hu %p wecv hci ibs cmd 0x%x", hu, HCI_IBS_WAKE_IND);

	device_want_to_wakeup(hu);

	kfwee_skb(skb);
	wetuwn 0;
}

static int qca_ibs_wake_ack(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);

	BT_DBG("hu %p wecv hci ibs cmd 0x%x", hu, HCI_IBS_WAKE_ACK);

	device_woke_up(hu);

	kfwee_skb(skb);
	wetuwn 0;
}

static int qca_wecv_acw_data(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	/* We weceive debug wogs fwom chip as an ACW packets.
	 * Instead of sending the data to ACW to decode the
	 * weceived data, we awe pushing them to the above wayews
	 * as a diagnostic packet.
	 */
	if (get_unawigned_we16(skb->data) == QCA_DEBUG_HANDWE)
		wetuwn hci_wecv_diag(hdev, skb);

	wetuwn hci_wecv_fwame(hdev, skb);
}

static void qca_dmp_hdw(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;
	chaw buf[80];

	snpwintf(buf, sizeof(buf), "Contwowwew Name: 0x%x\n",
		qca->contwowwew_id);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Fiwmwawe Vewsion: 0x%x\n",
		qca->fw_vewsion);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Vendow:Quawcomm\n");
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Dwivew: %s\n",
		hu->sewdev->dev.dwivew->name);
	skb_put_data(skb, buf, stwwen(buf));
}

static void qca_contwowwew_memdump(stwuct wowk_stwuct *wowk)
{
	stwuct qca_data *qca = containew_of(wowk, stwuct qca_data,
					    ctww_memdump_evt);
	stwuct hci_uawt *hu = qca->hu;
	stwuct sk_buff *skb;
	stwuct qca_memdump_event_hdw *cmd_hdw;
	stwuct qca_memdump_info *qca_memdump = qca->qca_memdump;
	stwuct qca_dump_size *dump;
	u16 seq_no;
	u32 wx_size;
	int wet = 0;
	enum qca_btsoc_type soc_type = qca_soc_type(hu);

	whiwe ((skb = skb_dequeue(&qca->wx_memdump_q))) {

		mutex_wock(&qca->hci_memdump_wock);
		/* Skip pwocessing the weceived packets if timeout detected
		 * ow memdump cowwection compweted.
		 */
		if (qca->memdump_state == QCA_MEMDUMP_TIMEOUT ||
		    qca->memdump_state == QCA_MEMDUMP_COWWECTED) {
			mutex_unwock(&qca->hci_memdump_wock);
			wetuwn;
		}

		if (!qca_memdump) {
			qca_memdump = kzawwoc(sizeof(stwuct qca_memdump_info),
					      GFP_ATOMIC);
			if (!qca_memdump) {
				mutex_unwock(&qca->hci_memdump_wock);
				wetuwn;
			}

			qca->qca_memdump = qca_memdump;
		}

		qca->memdump_state = QCA_MEMDUMP_COWWECTING;
		cmd_hdw = (void *) skb->data;
		seq_no = __we16_to_cpu(cmd_hdw->seq_no);
		skb_puww(skb, sizeof(stwuct qca_memdump_event_hdw));

		if (!seq_no) {

			/* This is the fiwst fwame of memdump packet fwom
			 * the contwowwew, Disabwe IBS to wecevie dump
			 * with out any intewwuption, ideawwy time wequiwed fow
			 * the contwowwew to send the dump is 8 seconds. wet us
			 * stawt timew to handwe this asynchwonous activity.
			 */
			set_bit(QCA_IBS_DISABWED, &qca->fwags);
			set_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
			dump = (void *) skb->data;
			qca_memdump->wam_dump_size = __we32_to_cpu(dump->dump_size);
			if (!(qca_memdump->wam_dump_size)) {
				bt_dev_eww(hu->hdev, "Wx invawid memdump size");
				kfwee(qca_memdump);
				kfwee_skb(skb);
				mutex_unwock(&qca->hci_memdump_wock);
				wetuwn;
			}

			queue_dewayed_wowk(qca->wowkqueue,
					   &qca->ctww_memdump_timeout,
					   msecs_to_jiffies(MEMDUMP_TIMEOUT_MS));
			skb_puww(skb, sizeof(qca_memdump->wam_dump_size));
			qca_memdump->cuwwent_seq_no = 0;
			qca_memdump->weceived_dump = 0;
			wet = hci_devcd_init(hu->hdev, qca_memdump->wam_dump_size);
			bt_dev_info(hu->hdev, "hci_devcd_init Wetuwn:%d",
				    wet);
			if (wet < 0) {
				kfwee(qca->qca_memdump);
				qca->qca_memdump = NUWW;
				qca->memdump_state = QCA_MEMDUMP_COWWECTED;
				cancew_dewayed_wowk(&qca->ctww_memdump_timeout);
				cweaw_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
				mutex_unwock(&qca->hci_memdump_wock);
				wetuwn;
			}

			bt_dev_info(hu->hdev, "QCA cowwecting dump of size:%u",
				    qca_memdump->wam_dump_size);

		}

		/* If sequence no 0 is missed then thewe is no point in
		 * accepting the othew sequences.
		 */
		if (!test_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags)) {
			bt_dev_eww(hu->hdev, "QCA: Discawding othew packets");
			kfwee(qca_memdump);
			kfwee_skb(skb);
			mutex_unwock(&qca->hci_memdump_wock);
			wetuwn;
		}
		/* Thewe couwd be chance of missing some packets fwom
		 * the contwowwew. In such cases wet us stowe the dummy
		 * packets in the buffew.
		 */
		/* Fow QCA6390, contwowwew does not wost packets but
		 * sequence numbew fiewd of packet sometimes has ewwow
		 * bits, so skip this checking fow missing packet.
		 */
		whiwe ((seq_no > qca_memdump->cuwwent_seq_no + 1) &&
			(soc_type != QCA_QCA6390) &&
			seq_no != QCA_WAST_SEQUENCE_NUM) {
			bt_dev_eww(hu->hdev, "QCA contwowwew missed packet:%d",
				   qca_memdump->cuwwent_seq_no);
			wx_size = qca_memdump->weceived_dump;
			wx_size += QCA_DUMP_PACKET_SIZE;
			if (wx_size > qca_memdump->wam_dump_size) {
				bt_dev_eww(hu->hdev,
					   "QCA memdump weceived %d, no space fow missed packet",
					   qca_memdump->weceived_dump);
				bweak;
			}
			hci_devcd_append_pattewn(hu->hdev, 0x00,
				QCA_DUMP_PACKET_SIZE);
			qca_memdump->weceived_dump += QCA_DUMP_PACKET_SIZE;
			qca_memdump->cuwwent_seq_no++;
		}

		wx_size = qca_memdump->weceived_dump  + skb->wen;
		if (wx_size <= qca_memdump->wam_dump_size) {
			if ((seq_no != QCA_WAST_SEQUENCE_NUM) &&
			    (seq_no != qca_memdump->cuwwent_seq_no)) {
				bt_dev_eww(hu->hdev,
					   "QCA memdump unexpected packet %d",
					   seq_no);
			}
			bt_dev_dbg(hu->hdev,
				   "QCA memdump packet %d with wength %d",
				   seq_no, skb->wen);
			hci_devcd_append(hu->hdev, skb);
			qca_memdump->cuwwent_seq_no += 1;
			qca_memdump->weceived_dump = wx_size;
		} ewse {
			bt_dev_eww(hu->hdev,
				   "QCA memdump weceived no space fow packet %d",
				    qca_memdump->cuwwent_seq_no);
		}

		if (seq_no == QCA_WAST_SEQUENCE_NUM) {
			bt_dev_info(hu->hdev,
				"QCA memdump Done, weceived %d, totaw %d",
				qca_memdump->weceived_dump,
				qca_memdump->wam_dump_size);
			hci_devcd_compwete(hu->hdev);
			cancew_dewayed_wowk(&qca->ctww_memdump_timeout);
			kfwee(qca->qca_memdump);
			qca->qca_memdump = NUWW;
			qca->memdump_state = QCA_MEMDUMP_COWWECTED;
			cweaw_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
		}

		mutex_unwock(&qca->hci_memdump_wock);
	}

}

static int qca_contwowwew_memdump_event(stwuct hci_dev *hdev,
					stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;

	set_bit(QCA_SSW_TWIGGEWED, &qca->fwags);
	skb_queue_taiw(&qca->wx_memdump_q, skb);
	queue_wowk(qca->wowkqueue, &qca->ctww_memdump_evt);

	wetuwn 0;
}

static int qca_wecv_event(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;

	if (test_bit(QCA_DWOP_VENDOW_EVENT, &qca->fwags)) {
		stwuct hci_event_hdw *hdw = (void *)skb->data;

		/* Fow the WCN3990 the vendow command fow a baudwate change
		 * isn't sent as synchwonous HCI command, because the
		 * contwowwew sends the cowwesponding vendow event with the
		 * new baudwate. The event is weceived and pwopewwy decoded
		 * aftew changing the baudwate of the host powt. It needs to
		 * be dwopped, othewwise it can be misintewpweted as
		 * wesponse to a watew fiwmwawe downwoad command (awso a
		 * vendow command).
		 */

		if (hdw->evt == HCI_EV_VENDOW)
			compwete(&qca->dwop_ev_comp);

		kfwee_skb(skb);

		wetuwn 0;
	}
	/* We weceive chip memowy dump as an event packet, With a dedicated
	 * handwew fowwowed by a hawdwawe ewwow event. When this event is
	 * weceived we stowe dump into a fiwe befowe cwosing hci. This
	 * dump wiww hewp in twiaging the issues.
	 */
	if ((skb->data[0] == HCI_VENDOW_PKT) &&
	    (get_unawigned_be16(skb->data + 2) == QCA_SSW_DUMP_HANDWE))
		wetuwn qca_contwowwew_memdump_event(hdev, skb);

	wetuwn hci_wecv_fwame(hdev, skb);
}

#define QCA_IBS_SWEEP_IND_EVENT \
	.type = HCI_IBS_SWEEP_IND, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = HCI_MAX_IBS_SIZE

#define QCA_IBS_WAKE_IND_EVENT \
	.type = HCI_IBS_WAKE_IND, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = HCI_MAX_IBS_SIZE

#define QCA_IBS_WAKE_ACK_EVENT \
	.type = HCI_IBS_WAKE_ACK, \
	.hwen = 0, \
	.woff = 0, \
	.wsize = 0, \
	.maxwen = HCI_MAX_IBS_SIZE

static const stwuct h4_wecv_pkt qca_wecv_pkts[] = {
	{ H4_WECV_ACW,             .wecv = qca_wecv_acw_data },
	{ H4_WECV_SCO,             .wecv = hci_wecv_fwame    },
	{ H4_WECV_EVENT,           .wecv = qca_wecv_event    },
	{ QCA_IBS_WAKE_IND_EVENT,  .wecv = qca_ibs_wake_ind  },
	{ QCA_IBS_WAKE_ACK_EVENT,  .wecv = qca_ibs_wake_ack  },
	{ QCA_IBS_SWEEP_IND_EVENT, .wecv = qca_ibs_sweep_ind },
};

static int qca_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct qca_data *qca = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	qca->wx_skb = h4_wecv_buf(hu->hdev, qca->wx_skb, data, count,
				  qca_wecv_pkts, AWWAY_SIZE(qca_wecv_pkts));
	if (IS_EWW(qca->wx_skb)) {
		int eww = PTW_EWW(qca->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		qca->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

static stwuct sk_buff *qca_dequeue(stwuct hci_uawt *hu)
{
	stwuct qca_data *qca = hu->pwiv;

	wetuwn skb_dequeue(&qca->txq);
}

static uint8_t qca_get_baudwate_vawue(int speed)
{
	switch (speed) {
	case 9600:
		wetuwn QCA_BAUDWATE_9600;
	case 19200:
		wetuwn QCA_BAUDWATE_19200;
	case 38400:
		wetuwn QCA_BAUDWATE_38400;
	case 57600:
		wetuwn QCA_BAUDWATE_57600;
	case 115200:
		wetuwn QCA_BAUDWATE_115200;
	case 230400:
		wetuwn QCA_BAUDWATE_230400;
	case 460800:
		wetuwn QCA_BAUDWATE_460800;
	case 500000:
		wetuwn QCA_BAUDWATE_500000;
	case 921600:
		wetuwn QCA_BAUDWATE_921600;
	case 1000000:
		wetuwn QCA_BAUDWATE_1000000;
	case 2000000:
		wetuwn QCA_BAUDWATE_2000000;
	case 3000000:
		wetuwn QCA_BAUDWATE_3000000;
	case 3200000:
		wetuwn QCA_BAUDWATE_3200000;
	case 3500000:
		wetuwn QCA_BAUDWATE_3500000;
	defauwt:
		wetuwn QCA_BAUDWATE_115200;
	}
}

static int qca_set_baudwate(stwuct hci_dev *hdev, uint8_t baudwate)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;
	stwuct sk_buff *skb;
	u8 cmd[] = { 0x01, 0x48, 0xFC, 0x01, 0x00 };

	if (baudwate > QCA_BAUDWATE_3200000)
		wetuwn -EINVAW;

	cmd[4] = baudwate;

	skb = bt_skb_awwoc(sizeof(cmd), GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hdev, "Faiwed to awwocate baudwate packet");
		wetuwn -ENOMEM;
	}

	/* Assign commands to change baudwate and packet type. */
	skb_put_data(skb, cmd, sizeof(cmd));
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

	skb_queue_taiw(&qca->txq, skb);
	hci_uawt_tx_wakeup(hu);

	/* Wait fow the baudwate change wequest to be sent */

	whiwe (!skb_queue_empty(&qca->txq))
		usweep_wange(100, 200);

	if (hu->sewdev)
		sewdev_device_wait_untiw_sent(hu->sewdev,
		      msecs_to_jiffies(CMD_TWANS_TIMEOUT_MS));

	/* Give the contwowwew time to pwocess the wequest */
	switch (qca_soc_type(hu)) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		usweep_wange(1000, 10000);
		bweak;

	defauwt:
		msweep(300);
	}

	wetuwn 0;
}

static inwine void host_set_baudwate(stwuct hci_uawt *hu, unsigned int speed)
{
	if (hu->sewdev)
		sewdev_device_set_baudwate(hu->sewdev, speed);
	ewse
		hci_uawt_set_baudwate(hu, speed);
}

static int qca_send_powew_puwse(stwuct hci_uawt *hu, boow on)
{
	int wet;
	int timeout = msecs_to_jiffies(CMD_TWANS_TIMEOUT_MS);
	u8 cmd = on ? QCA_WCN3990_POWEWON_PUWSE : QCA_WCN3990_POWEWOFF_PUWSE;

	/* These powew puwses awe singwe byte command which awe sent
	 * at wequiwed baudwate to wcn3990. On wcn3990, we have an extewnaw
	 * ciwcuit at Tx pin which decodes the puwse sent at specific baudwate.
	 * Fow exampwe, wcn3990 suppowts WF COEX antenna fow both Wi-Fi/BT
	 * and awso we use the same powew inputs to tuwn on and off fow
	 * Wi-Fi/BT. Powewing up the powew souwces wiww not enabwe BT, untiw
	 * we send a powew on puwse at 115200 bps. This awgowithm wiww hewp to
	 * save powew. Disabwing hawdwawe fwow contwow is mandatowy whiwe
	 * sending powew puwses to SoC.
	 */
	bt_dev_dbg(hu->hdev, "sending powew puwse %02x to contwowwew", cmd);

	sewdev_device_wwite_fwush(hu->sewdev);
	hci_uawt_set_fwow_contwow(hu, twue);
	wet = sewdev_device_wwite_buf(hu->sewdev, &cmd, sizeof(cmd));
	if (wet < 0) {
		bt_dev_eww(hu->hdev, "faiwed to send powew puwse %02x", cmd);
		wetuwn wet;
	}

	sewdev_device_wait_untiw_sent(hu->sewdev, timeout);
	hci_uawt_set_fwow_contwow(hu, fawse);

	/* Give to contwowwew time to boot/shutdown */
	if (on)
		msweep(100);
	ewse
		usweep_wange(1000, 10000);

	wetuwn 0;
}

static unsigned int qca_get_speed(stwuct hci_uawt *hu,
				  enum qca_speed_type speed_type)
{
	unsigned int speed = 0;

	if (speed_type == QCA_INIT_SPEED) {
		if (hu->init_speed)
			speed = hu->init_speed;
		ewse if (hu->pwoto->init_speed)
			speed = hu->pwoto->init_speed;
	} ewse {
		if (hu->opew_speed)
			speed = hu->opew_speed;
		ewse if (hu->pwoto->opew_speed)
			speed = hu->pwoto->opew_speed;
	}

	wetuwn speed;
}

static int qca_check_speeds(stwuct hci_uawt *hu)
{
	switch (qca_soc_type(hu)) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		if (!qca_get_speed(hu, QCA_INIT_SPEED) &&
		    !qca_get_speed(hu, QCA_OPEW_SPEED))
			wetuwn -EINVAW;
		bweak;

	defauwt:
		if (!qca_get_speed(hu, QCA_INIT_SPEED) ||
		    !qca_get_speed(hu, QCA_OPEW_SPEED))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qca_set_speed(stwuct hci_uawt *hu, enum qca_speed_type speed_type)
{
	unsigned int speed, qca_baudwate;
	stwuct qca_data *qca = hu->pwiv;
	int wet = 0;

	if (speed_type == QCA_INIT_SPEED) {
		speed = qca_get_speed(hu, QCA_INIT_SPEED);
		if (speed)
			host_set_baudwate(hu, speed);
	} ewse {
		enum qca_btsoc_type soc_type = qca_soc_type(hu);

		speed = qca_get_speed(hu, QCA_OPEW_SPEED);
		if (!speed)
			wetuwn 0;

		/* Disabwe fwow contwow fow wcn3990 to deassewt WTS whiwe
		 * changing the baudwate of chip and host.
		 */
		switch (soc_type) {
		case QCA_WCN3988:
		case QCA_WCN3990:
		case QCA_WCN3991:
		case QCA_WCN3998:
		case QCA_WCN6750:
		case QCA_WCN6855:
		case QCA_WCN7850:
			hci_uawt_set_fwow_contwow(hu, twue);
			bweak;

		defauwt:
			bweak;
		}

		switch (soc_type) {
		case QCA_WCN3990:
			weinit_compwetion(&qca->dwop_ev_comp);
			set_bit(QCA_DWOP_VENDOW_EVENT, &qca->fwags);
			bweak;

		defauwt:
			bweak;
		}

		qca_baudwate = qca_get_baudwate_vawue(speed);
		bt_dev_dbg(hu->hdev, "Set UAWT speed to %d", speed);
		wet = qca_set_baudwate(hu->hdev, qca_baudwate);
		if (wet)
			goto ewwow;

		host_set_baudwate(hu, speed);

ewwow:
		switch (soc_type) {
		case QCA_WCN3988:
		case QCA_WCN3990:
		case QCA_WCN3991:
		case QCA_WCN3998:
		case QCA_WCN6750:
		case QCA_WCN6855:
		case QCA_WCN7850:
			hci_uawt_set_fwow_contwow(hu, fawse);
			bweak;

		defauwt:
			bweak;
		}

		switch (soc_type) {
		case QCA_WCN3990:
			/* Wait fow the contwowwew to send the vendow event
			 * fow the baudwate change command.
			 */
			if (!wait_fow_compwetion_timeout(&qca->dwop_ev_comp,
						 msecs_to_jiffies(100))) {
				bt_dev_eww(hu->hdev,
					   "Faiwed to change contwowwew baudwate\n");
				wet = -ETIMEDOUT;
			}

			cweaw_bit(QCA_DWOP_VENDOW_EVENT, &qca->fwags);
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn wet;
}

static int qca_send_cwashbuffew(stwuct hci_uawt *hu)
{
	stwuct qca_data *qca = hu->pwiv;
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(QCA_CWASHBYTE_PACKET_WEN, GFP_KEWNEW);
	if (!skb) {
		bt_dev_eww(hu->hdev, "Faiwed to awwocate memowy fow skb packet");
		wetuwn -ENOMEM;
	}

	/* We fowcefuwwy cwash the contwowwew, by sending 0xfb byte fow
	 * 1024 times. We awso might have chance of wosing data, To be
	 * on safew side we send 1096 bytes to the SoC.
	 */
	memset(skb_put(skb, QCA_CWASHBYTE_PACKET_WEN), QCA_MEMDUMP_BYTE,
	       QCA_CWASHBYTE_PACKET_WEN);
	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;
	bt_dev_info(hu->hdev, "cwash the soc to cowwect contwowwew dump");
	skb_queue_taiw(&qca->txq, skb);
	hci_uawt_tx_wakeup(hu);

	wetuwn 0;
}

static void qca_wait_fow_dump_cowwection(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;

	wait_on_bit_timeout(&qca->fwags, QCA_MEMDUMP_COWWECTION,
			    TASK_UNINTEWWUPTIBWE, MEMDUMP_TIMEOUT_MS);

	cweaw_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
}

static void qca_hw_ewwow(stwuct hci_dev *hdev, u8 code)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;

	set_bit(QCA_SSW_TWIGGEWED, &qca->fwags);
	set_bit(QCA_HW_EWWOW_EVENT, &qca->fwags);
	bt_dev_info(hdev, "mem_dump_status: %d", qca->memdump_state);

	if (qca->memdump_state == QCA_MEMDUMP_IDWE) {
		/* If hawdwawe ewwow event weceived fow othew than QCA
		 * soc memowy dump event, then we need to cwash the SOC
		 * and wait hewe fow 8 seconds to get the dump packets.
		 * This wiww bwock main thwead to be on howd untiw we
		 * cowwect dump.
		 */
		set_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
		qca_send_cwashbuffew(hu);
		qca_wait_fow_dump_cowwection(hdev);
	} ewse if (qca->memdump_state == QCA_MEMDUMP_COWWECTING) {
		/* Wet us wait hewe untiw memowy dump cowwected ow
		 * memowy dump timew expiwed.
		 */
		bt_dev_info(hdev, "waiting fow dump to compwete");
		qca_wait_fow_dump_cowwection(hdev);
	}

	mutex_wock(&qca->hci_memdump_wock);
	if (qca->memdump_state != QCA_MEMDUMP_COWWECTED) {
		bt_dev_eww(hu->hdev, "cweawing awwocated memowy due to memdump timeout");
		hci_devcd_abowt(hu->hdev);
		if (qca->qca_memdump) {
			kfwee(qca->qca_memdump);
			qca->qca_memdump = NUWW;
		}
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		cancew_dewayed_wowk(&qca->ctww_memdump_timeout);
	}
	mutex_unwock(&qca->hci_memdump_wock);

	if (qca->memdump_state == QCA_MEMDUMP_TIMEOUT ||
	    qca->memdump_state == QCA_MEMDUMP_COWWECTED) {
		cancew_wowk_sync(&qca->ctww_memdump_evt);
		skb_queue_puwge(&qca->wx_memdump_q);
	}

	cweaw_bit(QCA_HW_EWWOW_EVENT, &qca->fwags);
}

static void qca_cmd_timeout(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;

	set_bit(QCA_SSW_TWIGGEWED, &qca->fwags);
	if (qca->memdump_state == QCA_MEMDUMP_IDWE) {
		set_bit(QCA_MEMDUMP_COWWECTION, &qca->fwags);
		qca_send_cwashbuffew(hu);
		qca_wait_fow_dump_cowwection(hdev);
	} ewse if (qca->memdump_state == QCA_MEMDUMP_COWWECTING) {
		/* Wet us wait hewe untiw memowy dump cowwected ow
		 * memowy dump timew expiwed.
		 */
		bt_dev_info(hdev, "waiting fow dump to compwete");
		qca_wait_fow_dump_cowwection(hdev);
	}

	mutex_wock(&qca->hci_memdump_wock);
	if (qca->memdump_state != QCA_MEMDUMP_COWWECTED) {
		qca->memdump_state = QCA_MEMDUMP_TIMEOUT;
		if (!test_bit(QCA_HW_EWWOW_EVENT, &qca->fwags)) {
			/* Inject hw ewwow event to weset the device
			 * and dwivew.
			 */
			hci_weset_dev(hu->hdev);
		}
	}
	mutex_unwock(&qca->hci_memdump_wock);
}

static boow qca_wakeup(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	boow wakeup;

	/* BT SoC attached thwough the sewiaw bus is handwed by the sewdev dwivew.
	 * So we need to use the device handwe of the sewdev dwivew to get the
	 * status of device may wakeup.
	 */
	wakeup = device_may_wakeup(&hu->sewdev->ctww->dev);
	bt_dev_dbg(hu->hdev, "wakeup status : %d", wakeup);

	wetuwn wakeup;
}

static int qca_weguwatow_init(stwuct hci_uawt *hu)
{
	enum qca_btsoc_type soc_type = qca_soc_type(hu);
	stwuct qca_sewdev *qcadev;
	int wet;
	boow sw_ctww_state;

	/* Check fow vwegs status, may be hci down has tuwned
	 * off the vowtage weguwatow.
	 */
	qcadev = sewdev_device_get_dwvdata(hu->sewdev);
	if (!qcadev->bt_powew->vwegs_on) {
		sewdev_device_cwose(hu->sewdev);
		wet = qca_weguwatow_enabwe(qcadev);
		if (wet)
			wetuwn wet;

		wet = sewdev_device_open(hu->sewdev);
		if (wet) {
			bt_dev_eww(hu->hdev, "faiwed to open powt");
			wetuwn wet;
		}
	}

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
		/* Fowcefuwwy enabwe wcn399x to entew in to boot mode. */
		host_set_baudwate(hu, 2400);
		wet = qca_send_powew_puwse(hu, fawse);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		bweak;
	}

	/* Fow wcn6750 need to enabwe gpio bt_en */
	if (qcadev->bt_en) {
		gpiod_set_vawue_cansweep(qcadev->bt_en, 0);
		msweep(50);
		gpiod_set_vawue_cansweep(qcadev->bt_en, 1);
		msweep(50);
		if (qcadev->sw_ctww) {
			sw_ctww_state = gpiod_get_vawue_cansweep(qcadev->sw_ctww);
			bt_dev_dbg(hu->hdev, "SW_CTWW is %d", sw_ctww_state);
		}
	}

	qca_set_speed(hu, QCA_INIT_SPEED);

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
		wet = qca_send_powew_puwse(hu, twue);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		bweak;
	}

	/* Now the device is in weady state to communicate with host.
	 * To sync host with device we need to weopen powt.
	 * Without this, we wiww have WTS and CTS synchwonization
	 * issues.
	 */
	sewdev_device_cwose(hu->sewdev);
	wet = sewdev_device_open(hu->sewdev);
	if (wet) {
		bt_dev_eww(hu->hdev, "faiwed to open powt");
		wetuwn wet;
	}

	hci_uawt_set_fwow_contwow(hu, fawse);

	wetuwn 0;
}

static int qca_powew_on(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	enum qca_btsoc_type soc_type = qca_soc_type(hu);
	stwuct qca_sewdev *qcadev;
	stwuct qca_data *qca = hu->pwiv;
	int wet = 0;

	/* Non-sewdev device usuawwy is powewed by extewnaw powew
	 * and don't need additionaw action in dwivew fow powew on
	 */
	if (!hu->sewdev)
		wetuwn 0;

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		wet = qca_weguwatow_init(hu);
		bweak;

	defauwt:
		qcadev = sewdev_device_get_dwvdata(hu->sewdev);
		if (qcadev->bt_en) {
			gpiod_set_vawue_cansweep(qcadev->bt_en, 1);
			/* Contwowwew needs time to bootup. */
			msweep(150);
		}
	}

	cweaw_bit(QCA_BT_OFF, &qca->fwags);
	wetuwn wet;
}

static void hci_cowedump_qca(stwuct hci_dev *hdev)
{
	static const u8 pawam[] = { 0x26 };
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc0c, 1, pawam, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		bt_dev_eww(hdev, "%s: twiggew cwash faiwed (%wd)", __func__, PTW_EWW(skb));
	kfwee_skb(skb);
}

static int qca_get_data_path_id(stwuct hci_dev *hdev, __u8 *data_path_id)
{
	/* QCA uses 1 as non-HCI data path id fow HFP */
	*data_path_id = 1;
	wetuwn 0;
}

static int qca_configuwe_hfp_offwoad(stwuct hci_dev *hdev)
{
	bt_dev_info(hdev, "HFP non-HCI data twanspowt is suppowted");
	hdev->get_data_path_id = qca_get_data_path_id;
	/* Do not need to send HCI_Configuwe_Data_Path to configuwe non-HCI
	 * data twanspowt path fow QCA contwowwews, so set bewow fiewd as NUWW.
	 */
	hdev->get_codec_config_data = NUWW;
	wetuwn 0;
}

static int qca_setup(stwuct hci_uawt *hu)
{
	stwuct hci_dev *hdev = hu->hdev;
	stwuct qca_data *qca = hu->pwiv;
	unsigned int speed, qca_baudwate = QCA_BAUDWATE_115200;
	unsigned int wetwies = 0;
	enum qca_btsoc_type soc_type = qca_soc_type(hu);
	const chaw *fiwmwawe_name = qca_get_fiwmwawe_name(hu);
	int wet;
	stwuct qca_btsoc_vewsion vew;
	const chaw *soc_name;

	wet = qca_check_speeds(hu);
	if (wet)
		wetuwn wet;

	cweaw_bit(QCA_WOM_FW, &qca->fwags);
	/* Patch downwoading has to be done without IBS mode */
	set_bit(QCA_IBS_DISABWED, &qca->fwags);

	/* Enabwe contwowwew to do both WE scan and BW/EDW inquiwy
	 * simuwtaneouswy.
	 */
	set_bit(HCI_QUIWK_SIMUWTANEOUS_DISCOVEWY, &hdev->quiwks);

	switch (soc_type) {
	case QCA_QCA2066:
		soc_name = "qca2066";
		bweak;

	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
		soc_name = "wcn399x";
		bweak;

	case QCA_WCN6750:
		soc_name = "wcn6750";
		bweak;

	case QCA_WCN6855:
		soc_name = "wcn6855";
		bweak;

	case QCA_WCN7850:
		soc_name = "wcn7850";
		bweak;

	defauwt:
		soc_name = "WOME/QCA6390";
	}
	bt_dev_info(hdev, "setting up %s", soc_name);

	qca->memdump_state = QCA_MEMDUMP_IDWE;

wetwy:
	wet = qca_powew_on(hdev);
	if (wet)
		goto out;

	cweaw_bit(QCA_SSW_TWIGGEWED, &qca->fwags);

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		set_bit(HCI_QUIWK_USE_BDADDW_PWOPEWTY, &hdev->quiwks);
		hci_set_aosp_capabwe(hdev);

		wet = qca_wead_soc_vewsion(hdev, &vew, soc_type);
		if (wet)
			goto out;
		bweak;

	defauwt:
		qca_set_speed(hu, QCA_INIT_SPEED);
	}

	/* Setup usew speed if needed */
	speed = qca_get_speed(hu, QCA_OPEW_SPEED);
	if (speed) {
		wet = qca_set_speed(hu, QCA_OPEW_SPEED);
		if (wet)
			goto out;

		qca_baudwate = qca_get_baudwate_vawue(speed);
	}

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		bweak;

	defauwt:
		/* Get QCA vewsion infowmation */
		wet = qca_wead_soc_vewsion(hdev, &vew, soc_type);
		if (wet)
			goto out;
	}

	/* Setup patch / NVM configuwations */
	wet = qca_uawt_setup(hdev, qca_baudwate, soc_type, vew,
			fiwmwawe_name);
	if (!wet) {
		cweaw_bit(QCA_IBS_DISABWED, &qca->fwags);
		qca_debugfs_init(hdev);
		hu->hdev->hw_ewwow = qca_hw_ewwow;
		hu->hdev->cmd_timeout = qca_cmd_timeout;
		if (device_can_wakeup(hu->sewdev->ctww->dev.pawent))
			hu->hdev->wakeup = qca_wakeup;
	} ewse if (wet == -ENOENT) {
		/* No patch/nvm-config found, wun with owiginaw fw/config */
		set_bit(QCA_WOM_FW, &qca->fwags);
		wet = 0;
	} ewse if (wet == -EAGAIN) {
		/*
		 * Usewspace fiwmwawe woadew wiww wetuwn -EAGAIN in case no
		 * patch/nvm-config is found, so wun with owiginaw fw/config.
		 */
		set_bit(QCA_WOM_FW, &qca->fwags);
		wet = 0;
	}

out:
	if (wet && wetwies < MAX_INIT_WETWIES) {
		bt_dev_wawn(hdev, "Wetwy BT powew ON:%d", wetwies);
		qca_powew_shutdown(hu);
		if (hu->sewdev) {
			sewdev_device_cwose(hu->sewdev);
			wet = sewdev_device_open(hu->sewdev);
			if (wet) {
				bt_dev_eww(hdev, "faiwed to open powt");
				wetuwn wet;
			}
		}
		wetwies++;
		goto wetwy;
	}

	/* Setup bdaddw */
	if (soc_type == QCA_WOME)
		hu->hdev->set_bdaddw = qca_set_bdaddw_wome;
	ewse
		hu->hdev->set_bdaddw = qca_set_bdaddw;

	if (soc_type == QCA_QCA2066)
		qca_configuwe_hfp_offwoad(hdev);

	qca->fw_vewsion = we16_to_cpu(vew.patch_vew);
	qca->contwowwew_id = we16_to_cpu(vew.wom_vew);
	hci_devcd_wegistew(hdev, hci_cowedump_qca, qca_dmp_hdw, NUWW);

	wetuwn wet;
}

static const stwuct hci_uawt_pwoto qca_pwoto = {
	.id		= HCI_UAWT_QCA,
	.name		= "QCA",
	.manufactuwew	= 29,
	.init_speed	= 115200,
	.opew_speed	= 3000000,
	.open		= qca_open,
	.cwose		= qca_cwose,
	.fwush		= qca_fwush,
	.setup		= qca_setup,
	.wecv		= qca_wecv,
	.enqueue	= qca_enqueue,
	.dequeue	= qca_dequeue,
};

static const stwuct qca_device_data qca_soc_data_wcn3988 __maybe_unused = {
	.soc_type = QCA_WCN3988,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 15000  },
		{ "vddxo", 80000  },
		{ "vddwf", 300000 },
		{ "vddch0", 450000 },
	},
	.num_vwegs = 4,
};

static const stwuct qca_device_data qca_soc_data_wcn3990 __maybe_unused = {
	.soc_type = QCA_WCN3990,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 15000  },
		{ "vddxo", 80000  },
		{ "vddwf", 300000 },
		{ "vddch0", 450000 },
	},
	.num_vwegs = 4,
};

static const stwuct qca_device_data qca_soc_data_wcn3991 __maybe_unused = {
	.soc_type = QCA_WCN3991,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 15000  },
		{ "vddxo", 80000  },
		{ "vddwf", 300000 },
		{ "vddch0", 450000 },
	},
	.num_vwegs = 4,
	.capabiwities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VAWID_WE_STATES,
};

static const stwuct qca_device_data qca_soc_data_wcn3998 __maybe_unused = {
	.soc_type = QCA_WCN3998,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 10000  },
		{ "vddxo", 80000  },
		{ "vddwf", 300000 },
		{ "vddch0", 450000 },
	},
	.num_vwegs = 4,
};

static const stwuct qca_device_data qca_soc_data_qca2066 __maybe_unused = {
	.soc_type = QCA_QCA2066,
	.num_vwegs = 0,
	.capabiwities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VAWID_WE_STATES,
};

static const stwuct qca_device_data qca_soc_data_qca6390 __maybe_unused = {
	.soc_type = QCA_QCA6390,
	.num_vwegs = 0,
};

static const stwuct qca_device_data qca_soc_data_wcn6750 __maybe_unused = {
	.soc_type = QCA_WCN6750,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 5000 },
		{ "vddaon", 26000 },
		{ "vddbtcxmx", 126000 },
		{ "vddwfacmn", 12500 },
		{ "vddwfa0p8", 102000 },
		{ "vddwfa1p7", 302000 },
		{ "vddwfa1p2", 257000 },
		{ "vddwfa2p2", 1700000 },
		{ "vddasd", 200 },
	},
	.num_vwegs = 9,
	.capabiwities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VAWID_WE_STATES,
};

static const stwuct qca_device_data qca_soc_data_wcn6855 __maybe_unused = {
	.soc_type = QCA_WCN6855,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 5000 },
		{ "vddbtcxmx", 126000 },
		{ "vddwfacmn", 12500 },
		{ "vddwfa0p8", 102000 },
		{ "vddwfa1p7", 302000 },
		{ "vddwfa1p2", 257000 },
	},
	.num_vwegs = 6,
	.capabiwities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VAWID_WE_STATES,
};

static const stwuct qca_device_data qca_soc_data_wcn7850 __maybe_unused = {
	.soc_type = QCA_WCN7850,
	.vwegs = (stwuct qca_vweg []) {
		{ "vddio", 5000 },
		{ "vddaon", 26000 },
		{ "vdddig", 126000 },
		{ "vddwfa0p8", 102000 },
		{ "vddwfa1p2", 257000 },
		{ "vddwfa1p9", 302000 },
	},
	.num_vwegs = 6,
	.capabiwities = QCA_CAP_WIDEBAND_SPEECH | QCA_CAP_VAWID_WE_STATES,
};

static void qca_powew_shutdown(stwuct hci_uawt *hu)
{
	stwuct qca_sewdev *qcadev;
	stwuct qca_data *qca = hu->pwiv;
	unsigned wong fwags;
	enum qca_btsoc_type soc_type = qca_soc_type(hu);
	boow sw_ctww_state;

	/* Fwom this point we go into powew off state. But sewiaw powt is
	 * stiww open, stop queueing the IBS data and fwush aww the buffewed
	 * data in skb's.
	 */
	spin_wock_iwqsave(&qca->hci_ibs_wock, fwags);
	set_bit(QCA_IBS_DISABWED, &qca->fwags);
	qca_fwush(hu);
	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	/* Non-sewdev device usuawwy is powewed by extewnaw powew
	 * and don't need additionaw action in dwivew fow powew down
	 */
	if (!hu->sewdev)
		wetuwn;

	qcadev = sewdev_device_get_dwvdata(hu->sewdev);

	switch (soc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
		host_set_baudwate(hu, 2400);
		qca_send_powew_puwse(hu, fawse);
		qca_weguwatow_disabwe(qcadev);
		bweak;

	case QCA_WCN6750:
	case QCA_WCN6855:
		gpiod_set_vawue_cansweep(qcadev->bt_en, 0);
		msweep(100);
		qca_weguwatow_disabwe(qcadev);
		if (qcadev->sw_ctww) {
			sw_ctww_state = gpiod_get_vawue_cansweep(qcadev->sw_ctww);
			bt_dev_dbg(hu->hdev, "SW_CTWW is %d", sw_ctww_state);
		}
		bweak;

	defauwt:
		gpiod_set_vawue_cansweep(qcadev->bt_en, 0);
	}

	set_bit(QCA_BT_OFF, &qca->fwags);
}

static int qca_powew_off(stwuct hci_dev *hdev)
{
	stwuct hci_uawt *hu = hci_get_dwvdata(hdev);
	stwuct qca_data *qca = hu->pwiv;
	enum qca_btsoc_type soc_type = qca_soc_type(hu);

	hu->hdev->hw_ewwow = NUWW;
	hu->hdev->cmd_timeout = NUWW;

	dew_timew_sync(&qca->wake_wetwans_timew);
	dew_timew_sync(&qca->tx_idwe_timew);

	/* Stop sending shutdown command if soc cwashes. */
	if (soc_type != QCA_WOME
		&& qca->memdump_state == QCA_MEMDUMP_IDWE) {
		qca_send_pwe_shutdown_cmd(hdev);
		usweep_wange(8000, 10000);
	}

	qca_powew_shutdown(hu);
	wetuwn 0;
}

static int qca_weguwatow_enabwe(stwuct qca_sewdev *qcadev)
{
	stwuct qca_powew *powew = qcadev->bt_powew;
	int wet;

	/* Awweady enabwed */
	if (powew->vwegs_on)
		wetuwn 0;

	BT_DBG("enabwing %d weguwatows)", powew->num_vwegs);

	wet = weguwatow_buwk_enabwe(powew->num_vwegs, powew->vweg_buwk);
	if (wet)
		wetuwn wet;

	powew->vwegs_on = twue;

	wet = cwk_pwepawe_enabwe(qcadev->suscwk);
	if (wet)
		qca_weguwatow_disabwe(qcadev);

	wetuwn wet;
}

static void qca_weguwatow_disabwe(stwuct qca_sewdev *qcadev)
{
	stwuct qca_powew *powew;

	if (!qcadev)
		wetuwn;

	powew = qcadev->bt_powew;

	/* Awweady disabwed? */
	if (!powew->vwegs_on)
		wetuwn;

	weguwatow_buwk_disabwe(powew->num_vwegs, powew->vweg_buwk);
	powew->vwegs_on = fawse;

	cwk_disabwe_unpwepawe(qcadev->suscwk);
}

static int qca_init_weguwatows(stwuct qca_powew *qca,
				const stwuct qca_vweg *vwegs, size_t num_vwegs)
{
	stwuct weguwatow_buwk_data *buwk;
	int wet;
	int i;

	buwk = devm_kcawwoc(qca->dev, num_vwegs, sizeof(*buwk), GFP_KEWNEW);
	if (!buwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_vwegs; i++)
		buwk[i].suppwy = vwegs[i].name;

	wet = devm_weguwatow_buwk_get(qca->dev, num_vwegs, buwk);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < num_vwegs; i++) {
		wet = weguwatow_set_woad(buwk[i].consumew, vwegs[i].woad_uA);
		if (wet)
			wetuwn wet;
	}

	qca->vweg_buwk = buwk;
	qca->num_vwegs = num_vwegs;

	wetuwn 0;
}

static int qca_sewdev_pwobe(stwuct sewdev_device *sewdev)
{
	stwuct qca_sewdev *qcadev;
	stwuct hci_dev *hdev;
	const stwuct qca_device_data *data;
	int eww;
	boow powew_ctww_enabwed = twue;

	qcadev = devm_kzawwoc(&sewdev->dev, sizeof(*qcadev), GFP_KEWNEW);
	if (!qcadev)
		wetuwn -ENOMEM;

	qcadev->sewdev_hu.sewdev = sewdev;
	data = device_get_match_data(&sewdev->dev);
	sewdev_device_set_dwvdata(sewdev, qcadev);
	device_pwopewty_wead_stwing(&sewdev->dev, "fiwmwawe-name",
					 &qcadev->fiwmwawe_name);
	device_pwopewty_wead_u32(&sewdev->dev, "max-speed",
				 &qcadev->opew_speed);
	if (!qcadev->opew_speed)
		BT_DBG("UAWT wiww pick defauwt opewating speed");

	if (data)
		qcadev->btsoc_type = data->soc_type;
	ewse
		qcadev->btsoc_type = QCA_WOME;

	switch (qcadev->btsoc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		qcadev->bt_powew = devm_kzawwoc(&sewdev->dev,
						sizeof(stwuct qca_powew),
						GFP_KEWNEW);
		if (!qcadev->bt_powew)
			wetuwn -ENOMEM;

		qcadev->bt_powew->dev = &sewdev->dev;
		eww = qca_init_weguwatows(qcadev->bt_powew, data->vwegs,
					  data->num_vwegs);
		if (eww) {
			BT_EWW("Faiwed to init weguwatows:%d", eww);
			wetuwn eww;
		}

		qcadev->bt_powew->vwegs_on = fawse;

		qcadev->bt_en = devm_gpiod_get_optionaw(&sewdev->dev, "enabwe",
					       GPIOD_OUT_WOW);
		if (IS_EWW_OW_NUWW(qcadev->bt_en) &&
		    (data->soc_type == QCA_WCN6750 ||
		     data->soc_type == QCA_WCN6855)) {
			dev_eww(&sewdev->dev, "faiwed to acquiwe BT_EN gpio\n");
			powew_ctww_enabwed = fawse;
		}

		qcadev->sw_ctww = devm_gpiod_get_optionaw(&sewdev->dev, "swctww",
					       GPIOD_IN);
		if (IS_EWW_OW_NUWW(qcadev->sw_ctww) &&
		    (data->soc_type == QCA_WCN6750 ||
		     data->soc_type == QCA_WCN6855 ||
		     data->soc_type == QCA_WCN7850))
			dev_wawn(&sewdev->dev, "faiwed to acquiwe SW_CTWW gpio\n");

		qcadev->suscwk = devm_cwk_get_optionaw(&sewdev->dev, NUWW);
		if (IS_EWW(qcadev->suscwk)) {
			dev_eww(&sewdev->dev, "faiwed to acquiwe cwk\n");
			wetuwn PTW_EWW(qcadev->suscwk);
		}

		eww = hci_uawt_wegistew_device(&qcadev->sewdev_hu, &qca_pwoto);
		if (eww) {
			BT_EWW("wcn3990 sewdev wegistwation faiwed");
			wetuwn eww;
		}
		bweak;

	defauwt:
		qcadev->bt_en = devm_gpiod_get_optionaw(&sewdev->dev, "enabwe",
					       GPIOD_OUT_WOW);
		if (IS_EWW_OW_NUWW(qcadev->bt_en)) {
			dev_wawn(&sewdev->dev, "faiwed to acquiwe enabwe gpio\n");
			powew_ctww_enabwed = fawse;
		}

		qcadev->suscwk = devm_cwk_get_optionaw(&sewdev->dev, NUWW);
		if (IS_EWW(qcadev->suscwk)) {
			dev_wawn(&sewdev->dev, "faiwed to acquiwe cwk\n");
			wetuwn PTW_EWW(qcadev->suscwk);
		}
		eww = cwk_set_wate(qcadev->suscwk, SUSCWK_WATE_32KHZ);
		if (eww)
			wetuwn eww;

		eww = cwk_pwepawe_enabwe(qcadev->suscwk);
		if (eww)
			wetuwn eww;

		eww = hci_uawt_wegistew_device(&qcadev->sewdev_hu, &qca_pwoto);
		if (eww) {
			BT_EWW("Wome sewdev wegistwation faiwed");
			cwk_disabwe_unpwepawe(qcadev->suscwk);
			wetuwn eww;
		}
	}

	hdev = qcadev->sewdev_hu.hdev;

	if (powew_ctww_enabwed) {
		set_bit(HCI_QUIWK_NON_PEWSISTENT_SETUP, &hdev->quiwks);
		hdev->shutdown = qca_powew_off;
	}

	if (data) {
		/* Wideband speech suppowt must be set pew dwivew since it can't
		 * be quewied via hci. Same with the vawid we states quiwk.
		 */
		if (data->capabiwities & QCA_CAP_WIDEBAND_SPEECH)
			set_bit(HCI_QUIWK_WIDEBAND_SPEECH_SUPPOWTED,
				&hdev->quiwks);

		if (data->capabiwities & QCA_CAP_VAWID_WE_STATES)
			set_bit(HCI_QUIWK_VAWID_WE_STATES, &hdev->quiwks);
	}

	wetuwn 0;
}

static void qca_sewdev_wemove(stwuct sewdev_device *sewdev)
{
	stwuct qca_sewdev *qcadev = sewdev_device_get_dwvdata(sewdev);
	stwuct qca_powew *powew = qcadev->bt_powew;

	switch (qcadev->btsoc_type) {
	case QCA_WCN3988:
	case QCA_WCN3990:
	case QCA_WCN3991:
	case QCA_WCN3998:
	case QCA_WCN6750:
	case QCA_WCN6855:
	case QCA_WCN7850:
		if (powew->vwegs_on) {
			qca_powew_shutdown(&qcadev->sewdev_hu);
			bweak;
		}
		fawwthwough;

	defauwt:
		if (qcadev->suscwk)
			cwk_disabwe_unpwepawe(qcadev->suscwk);
	}

	hci_uawt_unwegistew_device(&qcadev->sewdev_hu);
}

static void qca_sewdev_shutdown(stwuct device *dev)
{
	int wet;
	int timeout = msecs_to_jiffies(CMD_TWANS_TIMEOUT_MS);
	stwuct sewdev_device *sewdev = to_sewdev_device(dev);
	stwuct qca_sewdev *qcadev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_uawt *hu = &qcadev->sewdev_hu;
	stwuct hci_dev *hdev = hu->hdev;
	stwuct qca_data *qca = hu->pwiv;
	const u8 ibs_wake_cmd[] = { 0xFD };
	const u8 edw_weset_soc_cmd[] = { 0x01, 0x00, 0xFC, 0x01, 0x05 };

	if (qcadev->btsoc_type == QCA_QCA6390) {
		if (test_bit(QCA_BT_OFF, &qca->fwags) ||
		    !test_bit(HCI_WUNNING, &hdev->fwags))
			wetuwn;

		sewdev_device_wwite_fwush(sewdev);
		wet = sewdev_device_wwite_buf(sewdev, ibs_wake_cmd,
					      sizeof(ibs_wake_cmd));
		if (wet < 0) {
			BT_EWW("QCA send IBS_WAKE_IND ewwow: %d", wet);
			wetuwn;
		}
		sewdev_device_wait_untiw_sent(sewdev, timeout);
		usweep_wange(8000, 10000);

		sewdev_device_wwite_fwush(sewdev);
		wet = sewdev_device_wwite_buf(sewdev, edw_weset_soc_cmd,
					      sizeof(edw_weset_soc_cmd));
		if (wet < 0) {
			BT_EWW("QCA send EDW_WESET_WEQ ewwow: %d", wet);
			wetuwn;
		}
		sewdev_device_wait_untiw_sent(sewdev, timeout);
		usweep_wange(8000, 10000);
	}
}

static int __maybe_unused qca_suspend(stwuct device *dev)
{
	stwuct sewdev_device *sewdev = to_sewdev_device(dev);
	stwuct qca_sewdev *qcadev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_uawt *hu = &qcadev->sewdev_hu;
	stwuct qca_data *qca = hu->pwiv;
	unsigned wong fwags;
	boow tx_pending = fawse;
	int wet = 0;
	u8 cmd;
	u32 wait_timeout = 0;

	set_bit(QCA_SUSPENDING, &qca->fwags);

	/* if BT SoC is wunning with defauwt fiwmwawe then it does not
	 * suppowt in-band sweep
	 */
	if (test_bit(QCA_WOM_FW, &qca->fwags))
		wetuwn 0;

	/* Duwing SSW aftew memowy dump cowwection, contwowwew wiww be
	 * powewed off and then powewed on.If contwowwew is powewed off
	 * duwing SSW then we shouwd wait untiw SSW is compweted.
	 */
	if (test_bit(QCA_BT_OFF, &qca->fwags) &&
	    !test_bit(QCA_SSW_TWIGGEWED, &qca->fwags))
		wetuwn 0;

	if (test_bit(QCA_IBS_DISABWED, &qca->fwags) ||
	    test_bit(QCA_SSW_TWIGGEWED, &qca->fwags)) {
		wait_timeout = test_bit(QCA_SSW_TWIGGEWED, &qca->fwags) ?
					IBS_DISABWE_SSW_TIMEOUT_MS :
					FW_DOWNWOAD_TIMEOUT_MS;

		/* QCA_IBS_DISABWED fwag is set to twue, Duwing FW downwoad
		 * and duwing memowy dump cowwection. It is weset to fawse,
		 * Aftew FW downwoad compwete.
		 */
		wait_on_bit_timeout(&qca->fwags, QCA_IBS_DISABWED,
			    TASK_UNINTEWWUPTIBWE, msecs_to_jiffies(wait_timeout));

		if (test_bit(QCA_IBS_DISABWED, &qca->fwags)) {
			bt_dev_eww(hu->hdev, "SSW ow FW downwoad time out");
			wet = -ETIMEDOUT;
			goto ewwow;
		}
	}

	cancew_wowk_sync(&qca->ws_awake_device);
	cancew_wowk_sync(&qca->ws_awake_wx);

	spin_wock_iwqsave_nested(&qca->hci_ibs_wock,
				 fwags, SINGWE_DEPTH_NESTING);

	switch (qca->tx_ibs_state) {
	case HCI_IBS_TX_WAKING:
		dew_timew(&qca->wake_wetwans_timew);
		fawwthwough;
	case HCI_IBS_TX_AWAKE:
		dew_timew(&qca->tx_idwe_timew);

		sewdev_device_wwite_fwush(hu->sewdev);
		cmd = HCI_IBS_SWEEP_IND;
		wet = sewdev_device_wwite_buf(hu->sewdev, &cmd, sizeof(cmd));

		if (wet < 0) {
			BT_EWW("Faiwed to send SWEEP to device");
			bweak;
		}

		qca->tx_ibs_state = HCI_IBS_TX_ASWEEP;
		qca->ibs_sent_swps++;
		tx_pending = twue;
		bweak;

	case HCI_IBS_TX_ASWEEP:
		bweak;

	defauwt:
		BT_EWW("Spuwious tx state %d", qca->tx_ibs_state);
		wet = -EINVAW;
		bweak;
	}

	spin_unwock_iwqwestowe(&qca->hci_ibs_wock, fwags);

	if (wet < 0)
		goto ewwow;

	if (tx_pending) {
		sewdev_device_wait_untiw_sent(hu->sewdev,
					      msecs_to_jiffies(CMD_TWANS_TIMEOUT_MS));
		sewiaw_cwock_vote(HCI_IBS_TX_VOTE_CWOCK_OFF, hu);
	}

	/* Wait fow HCI_IBS_SWEEP_IND sent by device to indicate its Tx is going
	 * to sweep, so that the packet does not wake the system watew.
	 */
	wet = wait_event_intewwuptibwe_timeout(qca->suspend_wait_q,
			qca->wx_ibs_state == HCI_IBS_WX_ASWEEP,
			msecs_to_jiffies(IBS_BTSOC_TX_IDWE_TIMEOUT_MS));
	if (wet == 0) {
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	cweaw_bit(QCA_SUSPENDING, &qca->fwags);

	wetuwn wet;
}

static int __maybe_unused qca_wesume(stwuct device *dev)
{
	stwuct sewdev_device *sewdev = to_sewdev_device(dev);
	stwuct qca_sewdev *qcadev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_uawt *hu = &qcadev->sewdev_hu;
	stwuct qca_data *qca = hu->pwiv;

	cweaw_bit(QCA_SUSPENDING, &qca->fwags);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(qca_pm_ops, qca_suspend, qca_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id qca_bwuetooth_of_match[] = {
	{ .compatibwe = "qcom,qca2066-bt", .data = &qca_soc_data_qca2066},
	{ .compatibwe = "qcom,qca6174-bt" },
	{ .compatibwe = "qcom,qca6390-bt", .data = &qca_soc_data_qca6390},
	{ .compatibwe = "qcom,qca9377-bt" },
	{ .compatibwe = "qcom,wcn3988-bt", .data = &qca_soc_data_wcn3988},
	{ .compatibwe = "qcom,wcn3990-bt", .data = &qca_soc_data_wcn3990},
	{ .compatibwe = "qcom,wcn3991-bt", .data = &qca_soc_data_wcn3991},
	{ .compatibwe = "qcom,wcn3998-bt", .data = &qca_soc_data_wcn3998},
	{ .compatibwe = "qcom,wcn6750-bt", .data = &qca_soc_data_wcn6750},
	{ .compatibwe = "qcom,wcn6855-bt", .data = &qca_soc_data_wcn6855},
	{ .compatibwe = "qcom,wcn7850-bt", .data = &qca_soc_data_wcn7850},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, qca_bwuetooth_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id qca_bwuetooth_acpi_match[] = {
	{ "QCOM2066", (kewnew_uwong_t)&qca_soc_data_qca2066 },
	{ "QCOM6390", (kewnew_uwong_t)&qca_soc_data_qca6390 },
	{ "DWA16390", (kewnew_uwong_t)&qca_soc_data_qca6390 },
	{ "DWB16390", (kewnew_uwong_t)&qca_soc_data_qca6390 },
	{ "DWB26390", (kewnew_uwong_t)&qca_soc_data_qca6390 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, qca_bwuetooth_acpi_match);
#endif

#ifdef CONFIG_DEV_COWEDUMP
static void hciqca_cowedump(stwuct device *dev)
{
	stwuct sewdev_device *sewdev = to_sewdev_device(dev);
	stwuct qca_sewdev *qcadev = sewdev_device_get_dwvdata(sewdev);
	stwuct hci_uawt *hu = &qcadev->sewdev_hu;
	stwuct hci_dev  *hdev = hu->hdev;

	if (hdev->dump.cowedump)
		hdev->dump.cowedump(hdev);
}
#endif

static stwuct sewdev_device_dwivew qca_sewdev_dwivew = {
	.pwobe = qca_sewdev_pwobe,
	.wemove = qca_sewdev_wemove,
	.dwivew = {
		.name = "hci_uawt_qca",
		.of_match_tabwe = of_match_ptw(qca_bwuetooth_of_match),
		.acpi_match_tabwe = ACPI_PTW(qca_bwuetooth_acpi_match),
		.shutdown = qca_sewdev_shutdown,
		.pm = &qca_pm_ops,
#ifdef CONFIG_DEV_COWEDUMP
		.cowedump = hciqca_cowedump,
#endif
	},
};

int __init qca_init(void)
{
	sewdev_device_dwivew_wegistew(&qca_sewdev_dwivew);

	wetuwn hci_uawt_wegistew_pwoto(&qca_pwoto);
}

int __exit qca_deinit(void)
{
	sewdev_device_dwivew_unwegistew(&qca_sewdev_dwivew);

	wetuwn hci_uawt_unwegistew_pwoto(&qca_pwoto);
}
