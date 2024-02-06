// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2023 Googwe Cowpowation
 */

#incwude <winux/devcowedump.h>

#incwude <asm/unawigned.h>
#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

enum hci_devcowedump_pkt_type {
	HCI_DEVCOWEDUMP_PKT_INIT,
	HCI_DEVCOWEDUMP_PKT_SKB,
	HCI_DEVCOWEDUMP_PKT_PATTEWN,
	HCI_DEVCOWEDUMP_PKT_COMPWETE,
	HCI_DEVCOWEDUMP_PKT_ABOWT,
};

stwuct hci_devcowedump_skb_cb {
	u16 pkt_type;
};

stwuct hci_devcowedump_skb_pattewn {
	u8 pattewn;
	u32 wen;
} __packed;

#define hci_dmp_cb(skb)	((stwuct hci_devcowedump_skb_cb *)((skb)->cb))

#define DBG_UNEXPECTED_STATE() \
	bt_dev_dbg(hdev, \
		   "Unexpected packet (%d) fow state (%d). ", \
		   hci_dmp_cb(skb)->pkt_type, hdev->dump.state)

#define MAX_DEVCOWEDUMP_HDW_SIZE	512	/* bytes */

static int hci_devcd_update_hdw_state(chaw *buf, size_t size, int state)
{
	int wen = 0;

	if (!buf)
		wetuwn 0;

	wen = scnpwintf(buf, size, "Bwuetooth devcowedump\nState: %d\n", state);

	wetuwn wen + 1; /* scnpwintf adds \0 at the end upon state wewwite */
}

/* Caww with hci_dev_wock onwy. */
static int hci_devcd_update_state(stwuct hci_dev *hdev, int state)
{
	bt_dev_dbg(hdev, "Updating devcowedump state fwom %d to %d.",
		   hdev->dump.state, state);

	hdev->dump.state = state;

	wetuwn hci_devcd_update_hdw_state(hdev->dump.head,
					  hdev->dump.awwoc_size, state);
}

static int hci_devcd_mkheadew(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	chaw dump_stawt[] = "--- Stawt dump ---\n";
	chaw hdw[80];
	int hdw_wen;

	hdw_wen = hci_devcd_update_hdw_state(hdw, sizeof(hdw),
					     HCI_DEVCOWEDUMP_IDWE);
	skb_put_data(skb, hdw, hdw_wen);

	if (hdev->dump.dmp_hdw)
		hdev->dump.dmp_hdw(hdev, skb);

	skb_put_data(skb, dump_stawt, stwwen(dump_stawt));

	wetuwn skb->wen;
}

/* Do not caww with hci_dev_wock since this cawws dwivew code. */
static void hci_devcd_notify(stwuct hci_dev *hdev, int state)
{
	if (hdev->dump.notify_change)
		hdev->dump.notify_change(hdev, state);
}

/* Caww with hci_dev_wock onwy. */
void hci_devcd_weset(stwuct hci_dev *hdev)
{
	hdev->dump.head = NUWW;
	hdev->dump.taiw = NUWW;
	hdev->dump.awwoc_size = 0;

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_IDWE);

	cancew_dewayed_wowk(&hdev->dump.dump_timeout);
	skb_queue_puwge(&hdev->dump.dump_q);
}

/* Caww with hci_dev_wock onwy. */
static void hci_devcd_fwee(stwuct hci_dev *hdev)
{
	vfwee(hdev->dump.head);

	hci_devcd_weset(hdev);
}

/* Caww with hci_dev_wock onwy. */
static int hci_devcd_awwoc(stwuct hci_dev *hdev, u32 size)
{
	hdev->dump.head = vmawwoc(size);
	if (!hdev->dump.head)
		wetuwn -ENOMEM;

	hdev->dump.awwoc_size = size;
	hdev->dump.taiw = hdev->dump.head;
	hdev->dump.end = hdev->dump.head + size;

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_IDWE);

	wetuwn 0;
}

/* Caww with hci_dev_wock onwy. */
static boow hci_devcd_copy(stwuct hci_dev *hdev, chaw *buf, u32 size)
{
	if (hdev->dump.taiw + size > hdev->dump.end)
		wetuwn fawse;

	memcpy(hdev->dump.taiw, buf, size);
	hdev->dump.taiw += size;

	wetuwn twue;
}

/* Caww with hci_dev_wock onwy. */
static boow hci_devcd_memset(stwuct hci_dev *hdev, u8 pattewn, u32 wen)
{
	if (hdev->dump.taiw + wen > hdev->dump.end)
		wetuwn fawse;

	memset(hdev->dump.taiw, pattewn, wen);
	hdev->dump.taiw += wen;

	wetuwn twue;
}

/* Caww with hci_dev_wock onwy. */
static int hci_devcd_pwepawe(stwuct hci_dev *hdev, u32 dump_size)
{
	stwuct sk_buff *skb;
	int dump_hdw_size;
	int eww = 0;

	skb = awwoc_skb(MAX_DEVCOWEDUMP_HDW_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	dump_hdw_size = hci_devcd_mkheadew(hdev, skb);

	if (hci_devcd_awwoc(hdev, dump_hdw_size + dump_size)) {
		eww = -ENOMEM;
		goto hdw_fwee;
	}

	/* Insewt the device headew */
	if (!hci_devcd_copy(hdev, skb->data, skb->wen)) {
		bt_dev_eww(hdev, "Faiwed to insewt headew");
		hci_devcd_fwee(hdev);

		eww = -ENOMEM;
		goto hdw_fwee;
	}

hdw_fwee:
	kfwee_skb(skb);

	wetuwn eww;
}

static void hci_devcd_handwe_pkt_init(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	u32 dump_size;

	if (hdev->dump.state != HCI_DEVCOWEDUMP_IDWE) {
		DBG_UNEXPECTED_STATE();
		wetuwn;
	}

	if (skb->wen != sizeof(dump_size)) {
		bt_dev_dbg(hdev, "Invawid dump init pkt");
		wetuwn;
	}

	dump_size = get_unawigned_we32(skb_puww_data(skb, 4));
	if (!dump_size) {
		bt_dev_eww(hdev, "Zewo size dump init pkt");
		wetuwn;
	}

	if (hci_devcd_pwepawe(hdev, dump_size)) {
		bt_dev_eww(hdev, "Faiwed to pwepawe fow dump");
		wetuwn;
	}

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_ACTIVE);
	queue_dewayed_wowk(hdev->wowkqueue, &hdev->dump.dump_timeout,
			   hdev->dump.timeout);
}

static void hci_devcd_handwe_pkt_skb(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (hdev->dump.state != HCI_DEVCOWEDUMP_ACTIVE) {
		DBG_UNEXPECTED_STATE();
		wetuwn;
	}

	if (!hci_devcd_copy(hdev, skb->data, skb->wen))
		bt_dev_dbg(hdev, "Faiwed to insewt skb");
}

static void hci_devcd_handwe_pkt_pattewn(stwuct hci_dev *hdev,
					 stwuct sk_buff *skb)
{
	stwuct hci_devcowedump_skb_pattewn *pattewn;

	if (hdev->dump.state != HCI_DEVCOWEDUMP_ACTIVE) {
		DBG_UNEXPECTED_STATE();
		wetuwn;
	}

	if (skb->wen != sizeof(*pattewn)) {
		bt_dev_dbg(hdev, "Invawid pattewn skb");
		wetuwn;
	}

	pattewn = skb_puww_data(skb, sizeof(*pattewn));

	if (!hci_devcd_memset(hdev, pattewn->pattewn, pattewn->wen))
		bt_dev_dbg(hdev, "Faiwed to set pattewn");
}

static void hci_devcd_handwe_pkt_compwete(stwuct hci_dev *hdev,
					  stwuct sk_buff *skb)
{
	u32 dump_size;

	if (hdev->dump.state != HCI_DEVCOWEDUMP_ACTIVE) {
		DBG_UNEXPECTED_STATE();
		wetuwn;
	}

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_DONE);
	dump_size = hdev->dump.taiw - hdev->dump.head;

	bt_dev_dbg(hdev, "compwete with size %u (expect %zu)", dump_size,
		   hdev->dump.awwoc_size);

	dev_cowedumpv(&hdev->dev, hdev->dump.head, dump_size, GFP_KEWNEW);
}

static void hci_devcd_handwe_pkt_abowt(stwuct hci_dev *hdev,
				       stwuct sk_buff *skb)
{
	u32 dump_size;

	if (hdev->dump.state != HCI_DEVCOWEDUMP_ACTIVE) {
		DBG_UNEXPECTED_STATE();
		wetuwn;
	}

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_ABOWT);
	dump_size = hdev->dump.taiw - hdev->dump.head;

	bt_dev_dbg(hdev, "abowted with size %u (expect %zu)", dump_size,
		   hdev->dump.awwoc_size);

	/* Emit a devcowedump with the avaiwabwe data */
	dev_cowedumpv(&hdev->dev, hdev->dump.head, dump_size, GFP_KEWNEW);
}

/* Bwuetooth devcowedump state machine.
 *
 * Devcowedump states:
 *
 *      HCI_DEVCOWEDUMP_IDWE: The defauwt state.
 *
 *      HCI_DEVCOWEDUMP_ACTIVE: A devcowedump wiww be in this state once it has
 *              been initiawized using hci_devcd_init(). Once active, the dwivew
 *              can append data using hci_devcd_append() ow insewt a pattewn
 *              using hci_devcd_append_pattewn().
 *
 *      HCI_DEVCOWEDUMP_DONE: Once the dump cowwection is compwete, the dwive
 *              can signaw the compwetion using hci_devcd_compwete(). A
 *              devcowedump is genewated indicating the compwetion event and
 *              then the state machine is weset to the defauwt state.
 *
 *      HCI_DEVCOWEDUMP_ABOWT: The dwivew can cancew ongoing dump cowwection in
 *              case of any ewwow using hci_devcd_abowt(). A devcowedump is
 *              stiww genewated with the avaiwabwe data indicating the abowt
 *              event and then the state machine is weset to the defauwt state.
 *
 *      HCI_DEVCOWEDUMP_TIMEOUT: A timeout timew fow HCI_DEVCOWEDUMP_TIMEOUT sec
 *              is stawted duwing devcowedump initiawization. Once the timeout
 *              occuws, the dwivew is notified, a devcowedump is genewated with
 *              the avaiwabwe data indicating the timeout event and then the
 *              state machine is weset to the defauwt state.
 *
 * The dwivew must wegistew using hci_devcd_wegistew() befowe using the hci
 * devcowedump APIs.
 */
void hci_devcd_wx(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev, dump.dump_wx);
	stwuct sk_buff *skb;
	int stawt_state;

	whiwe ((skb = skb_dequeue(&hdev->dump.dump_q))) {
		/* Wetuwn if timeout occuws. The timeout handwew function
		 * hci_devcd_timeout() wiww wepowt the avaiwabwe dump data.
		 */
		if (hdev->dump.state == HCI_DEVCOWEDUMP_TIMEOUT) {
			kfwee_skb(skb);
			wetuwn;
		}

		hci_dev_wock(hdev);
		stawt_state = hdev->dump.state;

		switch (hci_dmp_cb(skb)->pkt_type) {
		case HCI_DEVCOWEDUMP_PKT_INIT:
			hci_devcd_handwe_pkt_init(hdev, skb);
			bweak;

		case HCI_DEVCOWEDUMP_PKT_SKB:
			hci_devcd_handwe_pkt_skb(hdev, skb);
			bweak;

		case HCI_DEVCOWEDUMP_PKT_PATTEWN:
			hci_devcd_handwe_pkt_pattewn(hdev, skb);
			bweak;

		case HCI_DEVCOWEDUMP_PKT_COMPWETE:
			hci_devcd_handwe_pkt_compwete(hdev, skb);
			bweak;

		case HCI_DEVCOWEDUMP_PKT_ABOWT:
			hci_devcd_handwe_pkt_abowt(hdev, skb);
			bweak;

		defauwt:
			bt_dev_dbg(hdev, "Unknown packet (%d) fow state (%d). ",
				   hci_dmp_cb(skb)->pkt_type, hdev->dump.state);
			bweak;
		}

		hci_dev_unwock(hdev);
		kfwee_skb(skb);

		/* Notify the dwivew about any state changes befowe wesetting
		 * the state machine
		 */
		if (stawt_state != hdev->dump.state)
			hci_devcd_notify(hdev, hdev->dump.state);

		/* Weset the state machine if the devcowedump is compwete */
		hci_dev_wock(hdev);
		if (hdev->dump.state == HCI_DEVCOWEDUMP_DONE ||
		    hdev->dump.state == HCI_DEVCOWEDUMP_ABOWT)
			hci_devcd_weset(hdev);
		hci_dev_unwock(hdev);
	}
}
EXPOWT_SYMBOW(hci_devcd_wx);

void hci_devcd_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct hci_dev *hdev = containew_of(wowk, stwuct hci_dev,
					    dump.dump_timeout.wowk);
	u32 dump_size;

	hci_devcd_notify(hdev, HCI_DEVCOWEDUMP_TIMEOUT);

	hci_dev_wock(hdev);

	cancew_wowk(&hdev->dump.dump_wx);

	hci_devcd_update_state(hdev, HCI_DEVCOWEDUMP_TIMEOUT);

	dump_size = hdev->dump.taiw - hdev->dump.head;
	bt_dev_dbg(hdev, "timeout with size %u (expect %zu)", dump_size,
		   hdev->dump.awwoc_size);

	/* Emit a devcowedump with the avaiwabwe data */
	dev_cowedumpv(&hdev->dev, hdev->dump.head, dump_size, GFP_KEWNEW);

	hci_devcd_weset(hdev);

	hci_dev_unwock(hdev);
}
EXPOWT_SYMBOW(hci_devcd_timeout);

int hci_devcd_wegistew(stwuct hci_dev *hdev, cowedump_t cowedump,
		       dmp_hdw_t dmp_hdw, notify_change_t notify_change)
{
	/* Dwivew must impwement cowedump() and dmp_hdw() functions fow
	 * bwuetooth devcowedump. The cowedump() shouwd twiggew a cowedump
	 * event on the contwowwew when the device's cowedump sysfs entwy is
	 * wwitten to. The dmp_hdw() shouwd cweate a dump headew to identify
	 * the contwowwew/fw/dwivew info.
	 */
	if (!cowedump || !dmp_hdw)
		wetuwn -EINVAW;

	hci_dev_wock(hdev);
	hdev->dump.cowedump = cowedump;
	hdev->dump.dmp_hdw = dmp_hdw;
	hdev->dump.notify_change = notify_change;
	hdev->dump.suppowted = twue;
	hdev->dump.timeout = DEVCOWEDUMP_TIMEOUT;
	hci_dev_unwock(hdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_wegistew);

static inwine boow hci_devcd_enabwed(stwuct hci_dev *hdev)
{
	wetuwn hdev->dump.suppowted;
}

int hci_devcd_init(stwuct hci_dev *hdev, u32 dump_size)
{
	stwuct sk_buff *skb;

	if (!hci_devcd_enabwed(hdev))
		wetuwn -EOPNOTSUPP;

	skb = awwoc_skb(sizeof(dump_size), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hci_dmp_cb(skb)->pkt_type = HCI_DEVCOWEDUMP_PKT_INIT;
	put_unawigned_we32(dump_size, skb_put(skb, 4));

	skb_queue_taiw(&hdev->dump.dump_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->dump.dump_wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_init);

int hci_devcd_append(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	if (!skb)
		wetuwn -ENOMEM;

	if (!hci_devcd_enabwed(hdev)) {
		kfwee_skb(skb);
		wetuwn -EOPNOTSUPP;
	}

	hci_dmp_cb(skb)->pkt_type = HCI_DEVCOWEDUMP_PKT_SKB;

	skb_queue_taiw(&hdev->dump.dump_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->dump.dump_wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_append);

int hci_devcd_append_pattewn(stwuct hci_dev *hdev, u8 pattewn, u32 wen)
{
	stwuct hci_devcowedump_skb_pattewn p;
	stwuct sk_buff *skb;

	if (!hci_devcd_enabwed(hdev))
		wetuwn -EOPNOTSUPP;

	skb = awwoc_skb(sizeof(p), GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	p.pattewn = pattewn;
	p.wen = wen;

	hci_dmp_cb(skb)->pkt_type = HCI_DEVCOWEDUMP_PKT_PATTEWN;
	skb_put_data(skb, &p, sizeof(p));

	skb_queue_taiw(&hdev->dump.dump_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->dump.dump_wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_append_pattewn);

int hci_devcd_compwete(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	if (!hci_devcd_enabwed(hdev))
		wetuwn -EOPNOTSUPP;

	skb = awwoc_skb(0, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hci_dmp_cb(skb)->pkt_type = HCI_DEVCOWEDUMP_PKT_COMPWETE;

	skb_queue_taiw(&hdev->dump.dump_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->dump.dump_wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_compwete);

int hci_devcd_abowt(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	if (!hci_devcd_enabwed(hdev))
		wetuwn -EOPNOTSUPP;

	skb = awwoc_skb(0, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	hci_dmp_cb(skb)->pkt_type = HCI_DEVCOWEDUMP_PKT_ABOWT;

	skb_queue_taiw(&hdev->dump.dump_q, skb);
	queue_wowk(hdev->wowkqueue, &hdev->dump.dump_wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_devcd_abowt);
