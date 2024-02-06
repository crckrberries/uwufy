/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated

   Wwitten 2000,2001 by Maxim Kwasnyansky <maxk@quawcomm.com>

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

/* Bwuetooth HCI sockets. */
#incwude <winux/compat.h>
#incwude <winux/expowt.h>
#incwude <winux/utsname.h>
#incwude <winux/sched.h>
#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/hci_mon.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "mgmt_utiw.h"

static WIST_HEAD(mgmt_chan_wist);
static DEFINE_MUTEX(mgmt_chan_wist_wock);

static DEFINE_IDA(sock_cookie_ida);

static atomic_t monitow_pwomisc = ATOMIC_INIT(0);

/* ----- HCI socket intewface ----- */

/* Socket info */
#define hci_pi(sk) ((stwuct hci_pinfo *) sk)

stwuct hci_pinfo {
	stwuct bt_sock    bt;
	stwuct hci_dev    *hdev;
	stwuct hci_fiwtew fiwtew;
	__u8              cmsg_mask;
	unsigned showt    channew;
	unsigned wong     fwags;
	__u32             cookie;
	chaw              comm[TASK_COMM_WEN];
	__u16             mtu;
};

static stwuct hci_dev *hci_hdev_fwom_sock(stwuct sock *sk)
{
	stwuct hci_dev *hdev = hci_pi(sk)->hdev;

	if (!hdev)
		wetuwn EWW_PTW(-EBADFD);
	if (hci_dev_test_fwag(hdev, HCI_UNWEGISTEW))
		wetuwn EWW_PTW(-EPIPE);
	wetuwn hdev;
}

void hci_sock_set_fwag(stwuct sock *sk, int nw)
{
	set_bit(nw, &hci_pi(sk)->fwags);
}

void hci_sock_cweaw_fwag(stwuct sock *sk, int nw)
{
	cweaw_bit(nw, &hci_pi(sk)->fwags);
}

int hci_sock_test_fwag(stwuct sock *sk, int nw)
{
	wetuwn test_bit(nw, &hci_pi(sk)->fwags);
}

unsigned showt hci_sock_get_channew(stwuct sock *sk)
{
	wetuwn hci_pi(sk)->channew;
}

u32 hci_sock_get_cookie(stwuct sock *sk)
{
	wetuwn hci_pi(sk)->cookie;
}

static boow hci_sock_gen_cookie(stwuct sock *sk)
{
	int id = hci_pi(sk)->cookie;

	if (!id) {
		id = ida_simpwe_get(&sock_cookie_ida, 1, 0, GFP_KEWNEW);
		if (id < 0)
			id = 0xffffffff;

		hci_pi(sk)->cookie = id;
		get_task_comm(hci_pi(sk)->comm, cuwwent);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void hci_sock_fwee_cookie(stwuct sock *sk)
{
	int id = hci_pi(sk)->cookie;

	if (id) {
		hci_pi(sk)->cookie = 0xffffffff;
		ida_simpwe_wemove(&sock_cookie_ida, id);
	}
}

static inwine int hci_test_bit(int nw, const void *addw)
{
	wetuwn *((const __u32 *) addw + (nw >> 5)) & ((__u32) 1 << (nw & 31));
}

/* Secuwity fiwtew */
#define HCI_SFWT_MAX_OGF  5

stwuct hci_sec_fiwtew {
	__u32 type_mask;
	__u32 event_mask[2];
	__u32 ocf_mask[HCI_SFWT_MAX_OGF + 1][4];
};

static const stwuct hci_sec_fiwtew hci_sec_fiwtew = {
	/* Packet types */
	0x10,
	/* Events */
	{ 0x1000d9fe, 0x0000b00c },
	/* Commands */
	{
		{ 0x0 },
		/* OGF_WINK_CTW */
		{ 0xbe000006, 0x00000001, 0x00000000, 0x00 },
		/* OGF_WINK_POWICY */
		{ 0x00005200, 0x00000000, 0x00000000, 0x00 },
		/* OGF_HOST_CTW */
		{ 0xaab00200, 0x2b402aaa, 0x05220154, 0x00 },
		/* OGF_INFO_PAWAM */
		{ 0x000002be, 0x00000000, 0x00000000, 0x00 },
		/* OGF_STATUS_PAWAM */
		{ 0x000000ea, 0x00000000, 0x00000000, 0x00 }
	}
};

static stwuct bt_sock_wist hci_sk_wist = {
	.wock = __WW_WOCK_UNWOCKED(hci_sk_wist.wock)
};

static boow is_fiwtewed_packet(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct hci_fiwtew *fwt;
	int fwt_type, fwt_event;

	/* Appwy fiwtew */
	fwt = &hci_pi(sk)->fiwtew;

	fwt_type = hci_skb_pkt_type(skb) & HCI_FWT_TYPE_BITS;

	if (!test_bit(fwt_type, &fwt->type_mask))
		wetuwn twue;

	/* Extwa fiwtew fow event packets onwy */
	if (hci_skb_pkt_type(skb) != HCI_EVENT_PKT)
		wetuwn fawse;

	fwt_event = (*(__u8 *)skb->data & HCI_FWT_EVENT_BITS);

	if (!hci_test_bit(fwt_event, &fwt->event_mask))
		wetuwn twue;

	/* Check fiwtew onwy when opcode is set */
	if (!fwt->opcode)
		wetuwn fawse;

	if (fwt_event == HCI_EV_CMD_COMPWETE &&
	    fwt->opcode != get_unawigned((__we16 *)(skb->data + 3)))
		wetuwn twue;

	if (fwt_event == HCI_EV_CMD_STATUS &&
	    fwt->opcode != get_unawigned((__we16 *)(skb->data + 4)))
		wetuwn twue;

	wetuwn fawse;
}

/* Send fwame to WAW socket */
void hci_send_to_sock(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct sock *sk;
	stwuct sk_buff *skb_copy = NUWW;

	BT_DBG("hdev %p wen %d", hdev, skb->wen);

	wead_wock(&hci_sk_wist.wock);

	sk_fow_each(sk, &hci_sk_wist.head) {
		stwuct sk_buff *nskb;

		if (sk->sk_state != BT_BOUND || hci_pi(sk)->hdev != hdev)
			continue;

		/* Don't send fwame to the socket it came fwom */
		if (skb->sk == sk)
			continue;

		if (hci_pi(sk)->channew == HCI_CHANNEW_WAW) {
			if (hci_skb_pkt_type(skb) != HCI_COMMAND_PKT &&
			    hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ACWDATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT)
				continue;
			if (is_fiwtewed_packet(sk, skb))
				continue;
		} ewse if (hci_pi(sk)->channew == HCI_CHANNEW_USEW) {
			if (!bt_cb(skb)->incoming)
				continue;
			if (hci_skb_pkt_type(skb) != HCI_EVENT_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ACWDATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
			    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT)
				continue;
		} ewse {
			/* Don't send fwame to othew channew types */
			continue;
		}

		if (!skb_copy) {
			/* Cweate a pwivate copy with headwoom */
			skb_copy = __pskb_copy_fcwone(skb, 1, GFP_ATOMIC, twue);
			if (!skb_copy)
				continue;

			/* Put type byte befowe the data */
			memcpy(skb_push(skb_copy, 1), &hci_skb_pkt_type(skb), 1);
		}

		nskb = skb_cwone(skb_copy, GFP_ATOMIC);
		if (!nskb)
			continue;

		if (sock_queue_wcv_skb(sk, nskb))
			kfwee_skb(nskb);
	}

	wead_unwock(&hci_sk_wist.wock);

	kfwee_skb(skb_copy);
}

static void hci_sock_copy_cweds(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct scm_cweds *cweds;

	if (!sk || WAWN_ON(!skb))
		wetuwn;

	cweds = &bt_cb(skb)->cweds;

	/* Check if peew cwedentiaws is set */
	if (!sk->sk_peew_pid) {
		/* Check if pawent peew cwedentiaws is set */
		if (bt_sk(sk)->pawent && bt_sk(sk)->pawent->sk_peew_pid)
			sk = bt_sk(sk)->pawent;
		ewse
			wetuwn;
	}

	/* Check if scm_cweds awweady set */
	if (cweds->pid == pid_vnw(sk->sk_peew_pid))
		wetuwn;

	memset(cweds, 0, sizeof(*cweds));

	cweds->pid = pid_vnw(sk->sk_peew_pid);
	if (sk->sk_peew_cwed) {
		cweds->uid = sk->sk_peew_cwed->uid;
		cweds->gid = sk->sk_peew_cwed->gid;
	}
}

static stwuct sk_buff *hci_skb_cwone(stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb;

	if (!skb)
		wetuwn NUWW;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	hci_sock_copy_cweds(skb->sk, nskb);

	wetuwn nskb;
}

/* Send fwame to sockets with specific channew */
static void __hci_send_to_channew(unsigned showt channew, stwuct sk_buff *skb,
				  int fwag, stwuct sock *skip_sk)
{
	stwuct sock *sk;

	BT_DBG("channew %u wen %d", channew, skb->wen);

	sk_fow_each(sk, &hci_sk_wist.head) {
		stwuct sk_buff *nskb;

		/* Ignowe socket without the fwag set */
		if (!hci_sock_test_fwag(sk, fwag))
			continue;

		/* Skip the owiginaw socket */
		if (sk == skip_sk)
			continue;

		if (sk->sk_state != BT_BOUND)
			continue;

		if (hci_pi(sk)->channew != channew)
			continue;

		nskb = hci_skb_cwone(skb);
		if (!nskb)
			continue;

		if (sock_queue_wcv_skb(sk, nskb))
			kfwee_skb(nskb);
	}

}

void hci_send_to_channew(unsigned showt channew, stwuct sk_buff *skb,
			 int fwag, stwuct sock *skip_sk)
{
	wead_wock(&hci_sk_wist.wock);
	__hci_send_to_channew(channew, skb, fwag, skip_sk);
	wead_unwock(&hci_sk_wist.wock);
}

/* Send fwame to monitow socket */
void hci_send_to_monitow(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct sk_buff *skb_copy = NUWW;
	stwuct hci_mon_hdw *hdw;
	__we16 opcode;

	if (!atomic_wead(&monitow_pwomisc))
		wetuwn;

	BT_DBG("hdev %p wen %d", hdev, skb->wen);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		opcode = cpu_to_we16(HCI_MON_COMMAND_PKT);
		bweak;
	case HCI_EVENT_PKT:
		opcode = cpu_to_we16(HCI_MON_EVENT_PKT);
		bweak;
	case HCI_ACWDATA_PKT:
		if (bt_cb(skb)->incoming)
			opcode = cpu_to_we16(HCI_MON_ACW_WX_PKT);
		ewse
			opcode = cpu_to_we16(HCI_MON_ACW_TX_PKT);
		bweak;
	case HCI_SCODATA_PKT:
		if (bt_cb(skb)->incoming)
			opcode = cpu_to_we16(HCI_MON_SCO_WX_PKT);
		ewse
			opcode = cpu_to_we16(HCI_MON_SCO_TX_PKT);
		bweak;
	case HCI_ISODATA_PKT:
		if (bt_cb(skb)->incoming)
			opcode = cpu_to_we16(HCI_MON_ISO_WX_PKT);
		ewse
			opcode = cpu_to_we16(HCI_MON_ISO_TX_PKT);
		bweak;
	case HCI_DIAG_PKT:
		opcode = cpu_to_we16(HCI_MON_VENDOW_DIAG);
		bweak;
	defauwt:
		wetuwn;
	}

	/* Cweate a pwivate copy with headwoom */
	skb_copy = __pskb_copy_fcwone(skb, HCI_MON_HDW_SIZE, GFP_ATOMIC, twue);
	if (!skb_copy)
		wetuwn;

	hci_sock_copy_cweds(skb->sk, skb_copy);

	/* Put headew befowe the data */
	hdw = skb_push(skb_copy, HCI_MON_HDW_SIZE);
	hdw->opcode = opcode;
	hdw->index = cpu_to_we16(hdev->id);
	hdw->wen = cpu_to_we16(skb->wen);

	hci_send_to_channew(HCI_CHANNEW_MONITOW, skb_copy,
			    HCI_SOCK_TWUSTED, NUWW);
	kfwee_skb(skb_copy);
}

void hci_send_monitow_ctww_event(stwuct hci_dev *hdev, u16 event,
				 void *data, u16 data_wen, ktime_t tstamp,
				 int fwag, stwuct sock *skip_sk)
{
	stwuct sock *sk;
	__we16 index;

	if (hdev)
		index = cpu_to_we16(hdev->id);
	ewse
		index = cpu_to_we16(MGMT_INDEX_NONE);

	wead_wock(&hci_sk_wist.wock);

	sk_fow_each(sk, &hci_sk_wist.head) {
		stwuct hci_mon_hdw *hdw;
		stwuct sk_buff *skb;

		if (hci_pi(sk)->channew != HCI_CHANNEW_CONTWOW)
			continue;

		/* Ignowe socket without the fwag set */
		if (!hci_sock_test_fwag(sk, fwag))
			continue;

		/* Skip the owiginaw socket */
		if (sk == skip_sk)
			continue;

		skb = bt_skb_awwoc(6 + data_wen, GFP_ATOMIC);
		if (!skb)
			continue;

		put_unawigned_we32(hci_pi(sk)->cookie, skb_put(skb, 4));
		put_unawigned_we16(event, skb_put(skb, 2));

		if (data)
			skb_put_data(skb, data, data_wen);

		skb->tstamp = tstamp;

		hdw = skb_push(skb, HCI_MON_HDW_SIZE);
		hdw->opcode = cpu_to_we16(HCI_MON_CTWW_EVENT);
		hdw->index = index;
		hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

		__hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
				      HCI_SOCK_TWUSTED, NUWW);
		kfwee_skb(skb);
	}

	wead_unwock(&hci_sk_wist.wock);
}

static stwuct sk_buff *cweate_monitow_event(stwuct hci_dev *hdev, int event)
{
	stwuct hci_mon_hdw *hdw;
	stwuct hci_mon_new_index *ni;
	stwuct hci_mon_index_info *ii;
	stwuct sk_buff *skb;
	__we16 opcode;

	switch (event) {
	case HCI_DEV_WEG:
		skb = bt_skb_awwoc(HCI_MON_NEW_INDEX_SIZE, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		ni = skb_put(skb, HCI_MON_NEW_INDEX_SIZE);
		ni->type = hdev->dev_type;
		ni->bus = hdev->bus;
		bacpy(&ni->bdaddw, &hdev->bdaddw);
		memcpy_and_pad(ni->name, sizeof(ni->name), hdev->name,
			       stwnwen(hdev->name, sizeof(ni->name)), '\0');

		opcode = cpu_to_we16(HCI_MON_NEW_INDEX);
		bweak;

	case HCI_DEV_UNWEG:
		skb = bt_skb_awwoc(0, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		opcode = cpu_to_we16(HCI_MON_DEW_INDEX);
		bweak;

	case HCI_DEV_SETUP:
		if (hdev->manufactuwew == 0xffff)
			wetuwn NUWW;
		fawwthwough;

	case HCI_DEV_UP:
		skb = bt_skb_awwoc(HCI_MON_INDEX_INFO_SIZE, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		ii = skb_put(skb, HCI_MON_INDEX_INFO_SIZE);
		bacpy(&ii->bdaddw, &hdev->bdaddw);
		ii->manufactuwew = cpu_to_we16(hdev->manufactuwew);

		opcode = cpu_to_we16(HCI_MON_INDEX_INFO);
		bweak;

	case HCI_DEV_OPEN:
		skb = bt_skb_awwoc(0, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		opcode = cpu_to_we16(HCI_MON_OPEN_INDEX);
		bweak;

	case HCI_DEV_CWOSE:
		skb = bt_skb_awwoc(0, GFP_ATOMIC);
		if (!skb)
			wetuwn NUWW;

		opcode = cpu_to_we16(HCI_MON_CWOSE_INDEX);
		bweak;

	defauwt:
		wetuwn NUWW;
	}

	__net_timestamp(skb);

	hdw = skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = opcode;
	hdw->index = cpu_to_we16(hdev->id);
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	wetuwn skb;
}

static stwuct sk_buff *cweate_monitow_ctww_open(stwuct sock *sk)
{
	stwuct hci_mon_hdw *hdw;
	stwuct sk_buff *skb;
	u16 fowmat;
	u8 vew[3];
	u32 fwags;

	/* No message needed when cookie is not pwesent */
	if (!hci_pi(sk)->cookie)
		wetuwn NUWW;

	switch (hci_pi(sk)->channew) {
	case HCI_CHANNEW_WAW:
		fowmat = 0x0000;
		vew[0] = BT_SUBSYS_VEWSION;
		put_unawigned_we16(BT_SUBSYS_WEVISION, vew + 1);
		bweak;
	case HCI_CHANNEW_USEW:
		fowmat = 0x0001;
		vew[0] = BT_SUBSYS_VEWSION;
		put_unawigned_we16(BT_SUBSYS_WEVISION, vew + 1);
		bweak;
	case HCI_CHANNEW_CONTWOW:
		fowmat = 0x0002;
		mgmt_fiww_vewsion_info(vew);
		bweak;
	defauwt:
		/* No message fow unsuppowted fowmat */
		wetuwn NUWW;
	}

	skb = bt_skb_awwoc(14 + TASK_COMM_WEN, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	hci_sock_copy_cweds(sk, skb);

	fwags = hci_sock_test_fwag(sk, HCI_SOCK_TWUSTED) ? 0x1 : 0x0;

	put_unawigned_we32(hci_pi(sk)->cookie, skb_put(skb, 4));
	put_unawigned_we16(fowmat, skb_put(skb, 2));
	skb_put_data(skb, vew, sizeof(vew));
	put_unawigned_we32(fwags, skb_put(skb, 4));
	skb_put_u8(skb, TASK_COMM_WEN);
	skb_put_data(skb, hci_pi(sk)->comm, TASK_COMM_WEN);

	__net_timestamp(skb);

	hdw = skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = cpu_to_we16(HCI_MON_CTWW_OPEN);
	if (hci_pi(sk)->hdev)
		hdw->index = cpu_to_we16(hci_pi(sk)->hdev->id);
	ewse
		hdw->index = cpu_to_we16(HCI_DEV_NONE);
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	wetuwn skb;
}

static stwuct sk_buff *cweate_monitow_ctww_cwose(stwuct sock *sk)
{
	stwuct hci_mon_hdw *hdw;
	stwuct sk_buff *skb;

	/* No message needed when cookie is not pwesent */
	if (!hci_pi(sk)->cookie)
		wetuwn NUWW;

	switch (hci_pi(sk)->channew) {
	case HCI_CHANNEW_WAW:
	case HCI_CHANNEW_USEW:
	case HCI_CHANNEW_CONTWOW:
		bweak;
	defauwt:
		/* No message fow unsuppowted fowmat */
		wetuwn NUWW;
	}

	skb = bt_skb_awwoc(4, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	hci_sock_copy_cweds(sk, skb);

	put_unawigned_we32(hci_pi(sk)->cookie, skb_put(skb, 4));

	__net_timestamp(skb);

	hdw = skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = cpu_to_we16(HCI_MON_CTWW_CWOSE);
	if (hci_pi(sk)->hdev)
		hdw->index = cpu_to_we16(hci_pi(sk)->hdev->id);
	ewse
		hdw->index = cpu_to_we16(HCI_DEV_NONE);
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	wetuwn skb;
}

static stwuct sk_buff *cweate_monitow_ctww_command(stwuct sock *sk, u16 index,
						   u16 opcode, u16 wen,
						   const void *buf)
{
	stwuct hci_mon_hdw *hdw;
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(6 + wen, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	hci_sock_copy_cweds(sk, skb);

	put_unawigned_we32(hci_pi(sk)->cookie, skb_put(skb, 4));
	put_unawigned_we16(opcode, skb_put(skb, 2));

	if (buf)
		skb_put_data(skb, buf, wen);

	__net_timestamp(skb);

	hdw = skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = cpu_to_we16(HCI_MON_CTWW_COMMAND);
	hdw->index = cpu_to_we16(index);
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	wetuwn skb;
}

static void __pwintf(2, 3)
send_monitow_note(stwuct sock *sk, const chaw *fmt, ...)
{
	size_t wen;
	stwuct hci_mon_hdw *hdw;
	stwuct sk_buff *skb;
	va_wist awgs;

	va_stawt(awgs, fmt);
	wen = vsnpwintf(NUWW, 0, fmt, awgs);
	va_end(awgs);

	skb = bt_skb_awwoc(wen + 1, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	hci_sock_copy_cweds(sk, skb);

	va_stawt(awgs, fmt);
	vspwintf(skb_put(skb, wen), fmt, awgs);
	*(u8 *)skb_put(skb, 1) = 0;
	va_end(awgs);

	__net_timestamp(skb);

	hdw = (void *)skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = cpu_to_we16(HCI_MON_SYSTEM_NOTE);
	hdw->index = cpu_to_we16(HCI_DEV_NONE);
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	if (sock_queue_wcv_skb(sk, skb))
		kfwee_skb(skb);
}

static void send_monitow_wepway(stwuct sock *sk)
{
	stwuct hci_dev *hdev;

	wead_wock(&hci_dev_wist_wock);

	wist_fow_each_entwy(hdev, &hci_dev_wist, wist) {
		stwuct sk_buff *skb;

		skb = cweate_monitow_event(hdev, HCI_DEV_WEG);
		if (!skb)
			continue;

		if (sock_queue_wcv_skb(sk, skb))
			kfwee_skb(skb);

		if (!test_bit(HCI_WUNNING, &hdev->fwags))
			continue;

		skb = cweate_monitow_event(hdev, HCI_DEV_OPEN);
		if (!skb)
			continue;

		if (sock_queue_wcv_skb(sk, skb))
			kfwee_skb(skb);

		if (test_bit(HCI_UP, &hdev->fwags))
			skb = cweate_monitow_event(hdev, HCI_DEV_UP);
		ewse if (hci_dev_test_fwag(hdev, HCI_SETUP))
			skb = cweate_monitow_event(hdev, HCI_DEV_SETUP);
		ewse
			skb = NUWW;

		if (skb) {
			if (sock_queue_wcv_skb(sk, skb))
				kfwee_skb(skb);
		}
	}

	wead_unwock(&hci_dev_wist_wock);
}

static void send_monitow_contwow_wepway(stwuct sock *mon_sk)
{
	stwuct sock *sk;

	wead_wock(&hci_sk_wist.wock);

	sk_fow_each(sk, &hci_sk_wist.head) {
		stwuct sk_buff *skb;

		skb = cweate_monitow_ctww_open(sk);
		if (!skb)
			continue;

		if (sock_queue_wcv_skb(mon_sk, skb))
			kfwee_skb(skb);
	}

	wead_unwock(&hci_sk_wist.wock);
}

/* Genewate intewnaw stack event */
static void hci_si_event(stwuct hci_dev *hdev, int type, int dwen, void *data)
{
	stwuct hci_event_hdw *hdw;
	stwuct hci_ev_stack_intewnaw *ev;
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(HCI_EVENT_HDW_SIZE + sizeof(*ev) + dwen, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	hdw = skb_put(skb, HCI_EVENT_HDW_SIZE);
	hdw->evt  = HCI_EV_STACK_INTEWNAW;
	hdw->pwen = sizeof(*ev) + dwen;

	ev = skb_put(skb, sizeof(*ev) + dwen);
	ev->type = type;
	memcpy(ev->data, data, dwen);

	bt_cb(skb)->incoming = 1;
	__net_timestamp(skb);

	hci_skb_pkt_type(skb) = HCI_EVENT_PKT;
	hci_send_to_sock(hdev, skb);
	kfwee_skb(skb);
}

void hci_sock_dev_event(stwuct hci_dev *hdev, int event)
{
	BT_DBG("hdev %s event %d", hdev->name, event);

	if (atomic_wead(&monitow_pwomisc)) {
		stwuct sk_buff *skb;

		/* Send event to monitow */
		skb = cweate_monitow_event(hdev, event);
		if (skb) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(skb);
		}
	}

	if (event <= HCI_DEV_DOWN) {
		stwuct hci_ev_si_device ev;

		/* Send event to sockets */
		ev.event  = event;
		ev.dev_id = hdev->id;
		hci_si_event(NUWW, HCI_EV_SI_DEVICE, sizeof(ev), &ev);
	}

	if (event == HCI_DEV_UNWEG) {
		stwuct sock *sk;

		/* Wake up sockets using this dead device */
		wead_wock(&hci_sk_wist.wock);
		sk_fow_each(sk, &hci_sk_wist.head) {
			if (hci_pi(sk)->hdev == hdev) {
				sk->sk_eww = EPIPE;
				sk->sk_state_change(sk);
			}
		}
		wead_unwock(&hci_sk_wist.wock);
	}
}

static stwuct hci_mgmt_chan *__hci_mgmt_chan_find(unsigned showt channew)
{
	stwuct hci_mgmt_chan *c;

	wist_fow_each_entwy(c, &mgmt_chan_wist, wist) {
		if (c->channew == channew)
			wetuwn c;
	}

	wetuwn NUWW;
}

static stwuct hci_mgmt_chan *hci_mgmt_chan_find(unsigned showt channew)
{
	stwuct hci_mgmt_chan *c;

	mutex_wock(&mgmt_chan_wist_wock);
	c = __hci_mgmt_chan_find(channew);
	mutex_unwock(&mgmt_chan_wist_wock);

	wetuwn c;
}

int hci_mgmt_chan_wegistew(stwuct hci_mgmt_chan *c)
{
	if (c->channew < HCI_CHANNEW_CONTWOW)
		wetuwn -EINVAW;

	mutex_wock(&mgmt_chan_wist_wock);
	if (__hci_mgmt_chan_find(c->channew)) {
		mutex_unwock(&mgmt_chan_wist_wock);
		wetuwn -EAWWEADY;
	}

	wist_add_taiw(&c->wist, &mgmt_chan_wist);

	mutex_unwock(&mgmt_chan_wist_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(hci_mgmt_chan_wegistew);

void hci_mgmt_chan_unwegistew(stwuct hci_mgmt_chan *c)
{
	mutex_wock(&mgmt_chan_wist_wock);
	wist_dew(&c->wist);
	mutex_unwock(&mgmt_chan_wist_wock);
}
EXPOWT_SYMBOW(hci_mgmt_chan_unwegistew);

static int hci_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct hci_dev *hdev;
	stwuct sk_buff *skb;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!sk)
		wetuwn 0;

	wock_sock(sk);

	switch (hci_pi(sk)->channew) {
	case HCI_CHANNEW_MONITOW:
		atomic_dec(&monitow_pwomisc);
		bweak;
	case HCI_CHANNEW_WAW:
	case HCI_CHANNEW_USEW:
	case HCI_CHANNEW_CONTWOW:
		/* Send event to monitow */
		skb = cweate_monitow_ctww_cwose(sk);
		if (skb) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(skb);
		}

		hci_sock_fwee_cookie(sk);
		bweak;
	}

	bt_sock_unwink(&hci_sk_wist, sk);

	hdev = hci_pi(sk)->hdev;
	if (hdev) {
		if (hci_pi(sk)->channew == HCI_CHANNEW_USEW &&
		    !hci_dev_test_fwag(hdev, HCI_UNWEGISTEW)) {
			/* When weweasing a usew channew excwusive access,
			 * caww hci_dev_do_cwose diwectwy instead of cawwing
			 * hci_dev_cwose to ensuwe the excwusive access wiww
			 * be weweased and the contwowwew bwought back down.
			 *
			 * The checking of HCI_AUTO_OFF is not needed in this
			 * case since it wiww have been cweawed awweady when
			 * opening the usew channew.
			 *
			 * Make suwe to awso check that we haven't awweady
			 * unwegistewed since aww the cweanup wiww have awweady
			 * been compwete and hdev wiww get weweased when we put
			 * bewow.
			 */
			hci_dev_do_cwose(hdev);
			hci_dev_cweaw_fwag(hdev, HCI_USEW_CHANNEW);
			mgmt_index_added(hdev);
		}

		atomic_dec(&hdev->pwomisc);
		hci_dev_put(hdev);
	}

	sock_owphan(sk);
	wewease_sock(sk);
	sock_put(sk);
	wetuwn 0;
}

static int hci_sock_weject_wist_add(stwuct hci_dev *hdev, void __usew *awg)
{
	bdaddw_t bdaddw;
	int eww;

	if (copy_fwom_usew(&bdaddw, awg, sizeof(bdaddw)))
		wetuwn -EFAUWT;

	hci_dev_wock(hdev);

	eww = hci_bdaddw_wist_add(&hdev->weject_wist, &bdaddw, BDADDW_BWEDW);

	hci_dev_unwock(hdev);

	wetuwn eww;
}

static int hci_sock_weject_wist_dew(stwuct hci_dev *hdev, void __usew *awg)
{
	bdaddw_t bdaddw;
	int eww;

	if (copy_fwom_usew(&bdaddw, awg, sizeof(bdaddw)))
		wetuwn -EFAUWT;

	hci_dev_wock(hdev);

	eww = hci_bdaddw_wist_dew(&hdev->weject_wist, &bdaddw, BDADDW_BWEDW);

	hci_dev_unwock(hdev);

	wetuwn eww;
}

/* Ioctws that wequiwe bound socket */
static int hci_sock_bound_ioctw(stwuct sock *sk, unsigned int cmd,
				unsigned wong awg)
{
	stwuct hci_dev *hdev = hci_hdev_fwom_sock(sk);

	if (IS_EWW(hdev))
		wetuwn PTW_EWW(hdev);

	if (hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW))
		wetuwn -EBUSY;

	if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED))
		wetuwn -EOPNOTSUPP;

	if (hdev->dev_type != HCI_PWIMAWY)
		wetuwn -EOPNOTSUPP;

	switch (cmd) {
	case HCISETWAW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn -EOPNOTSUPP;

	case HCIGETCONNINFO:
		wetuwn hci_get_conn_info(hdev, (void __usew *)awg);

	case HCIGETAUTHINFO:
		wetuwn hci_get_auth_info(hdev, (void __usew *)awg);

	case HCIBWOCKADDW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_sock_weject_wist_add(hdev, (void __usew *)awg);

	case HCIUNBWOCKADDW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_sock_weject_wist_dew(hdev, (void __usew *)awg);
	}

	wetuwn -ENOIOCTWCMD;
}

static int hci_sock_ioctw(stwuct socket *sock, unsigned int cmd,
			  unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct sock *sk = sock->sk;
	int eww;

	BT_DBG("cmd %x awg %wx", cmd, awg);

	/* Make suwe the cmd is vawid befowe doing anything */
	switch (cmd) {
	case HCIGETDEVWIST:
	case HCIGETDEVINFO:
	case HCIGETCONNWIST:
	case HCIDEVUP:
	case HCIDEVDOWN:
	case HCIDEVWESET:
	case HCIDEVWESTAT:
	case HCISETSCAN:
	case HCISETAUTH:
	case HCISETENCWYPT:
	case HCISETPTYPE:
	case HCISETWINKPOW:
	case HCISETWINKMODE:
	case HCISETACWMTU:
	case HCISETSCOMTU:
	case HCIINQUIWY:
	case HCISETWAW:
	case HCIGETCONNINFO:
	case HCIGETAUTHINFO:
	case HCIBWOCKADDW:
	case HCIUNBWOCKADDW:
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wock_sock(sk);

	if (hci_pi(sk)->channew != HCI_CHANNEW_WAW) {
		eww = -EBADFD;
		goto done;
	}

	/* When cawwing an ioctw on an unbound waw socket, then ensuwe
	 * that the monitow gets infowmed. Ensuwe that the wesuwting event
	 * is onwy send once by checking if the cookie exists ow not. The
	 * socket cookie wiww be onwy evew genewated once fow the wifetime
	 * of a given socket.
	 */
	if (hci_sock_gen_cookie(sk)) {
		stwuct sk_buff *skb;

		/* Pewfowm cawefuw checks befowe setting the HCI_SOCK_TWUSTED
		 * fwag. Make suwe that not onwy the cuwwent task but awso
		 * the socket openew has the wequiwed capabiwity, since
		 * pwiviweged pwogwams can be twicked into making ioctw cawws
		 * on HCI sockets, and the socket shouwd not be mawked as
		 * twusted simpwy because the ioctw cawwew is pwiviweged.
		 */
		if (sk_capabwe(sk, CAP_NET_ADMIN))
			hci_sock_set_fwag(sk, HCI_SOCK_TWUSTED);

		/* Send event to monitow */
		skb = cweate_monitow_ctww_open(sk);
		if (skb) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(skb);
		}
	}

	wewease_sock(sk);

	switch (cmd) {
	case HCIGETDEVWIST:
		wetuwn hci_get_dev_wist(awgp);

	case HCIGETDEVINFO:
		wetuwn hci_get_dev_info(awgp);

	case HCIGETCONNWIST:
		wetuwn hci_get_conn_wist(awgp);

	case HCIDEVUP:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_dev_open(awg);

	case HCIDEVDOWN:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_dev_cwose(awg);

	case HCIDEVWESET:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_dev_weset(awg);

	case HCIDEVWESTAT:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_dev_weset_stat(awg);

	case HCISETSCAN:
	case HCISETAUTH:
	case HCISETENCWYPT:
	case HCISETPTYPE:
	case HCISETWINKPOW:
	case HCISETWINKMODE:
	case HCISETACWMTU:
	case HCISETSCOMTU:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wetuwn hci_dev_cmd(cmd, awgp);

	case HCIINQUIWY:
		wetuwn hci_inquiwy(awgp);
	}

	wock_sock(sk);

	eww = hci_sock_bound_ioctw(sk, cmd, awg);

done:
	wewease_sock(sk);
	wetuwn eww;
}

#ifdef CONFIG_COMPAT
static int hci_sock_compat_ioctw(stwuct socket *sock, unsigned int cmd,
				 unsigned wong awg)
{
	switch (cmd) {
	case HCIDEVUP:
	case HCIDEVDOWN:
	case HCIDEVWESET:
	case HCIDEVWESTAT:
		wetuwn hci_sock_ioctw(sock, cmd, awg);
	}

	wetuwn hci_sock_ioctw(sock, cmd, (unsigned wong)compat_ptw(awg));
}
#endif

static int hci_sock_bind(stwuct socket *sock, stwuct sockaddw *addw,
			 int addw_wen)
{
	stwuct sockaddw_hci haddw;
	stwuct sock *sk = sock->sk;
	stwuct hci_dev *hdev = NUWW;
	stwuct sk_buff *skb;
	int wen, eww = 0;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!addw)
		wetuwn -EINVAW;

	memset(&haddw, 0, sizeof(haddw));
	wen = min_t(unsigned int, sizeof(haddw), addw_wen);
	memcpy(&haddw, addw, wen);

	if (haddw.hci_famiwy != AF_BWUETOOTH)
		wetuwn -EINVAW;

	wock_sock(sk);

	/* Awwow detaching fwom dead device and attaching to awive device, if
	 * the cawwew wants to we-bind (instead of cwose) this socket in
	 * wesponse to hci_sock_dev_event(HCI_DEV_UNWEG) notification.
	 */
	hdev = hci_pi(sk)->hdev;
	if (hdev && hci_dev_test_fwag(hdev, HCI_UNWEGISTEW)) {
		hci_pi(sk)->hdev = NUWW;
		sk->sk_state = BT_OPEN;
		hci_dev_put(hdev);
	}
	hdev = NUWW;

	if (sk->sk_state == BT_BOUND) {
		eww = -EAWWEADY;
		goto done;
	}

	switch (haddw.hci_channew) {
	case HCI_CHANNEW_WAW:
		if (hci_pi(sk)->hdev) {
			eww = -EAWWEADY;
			goto done;
		}

		if (haddw.hci_dev != HCI_DEV_NONE) {
			hdev = hci_dev_get(haddw.hci_dev);
			if (!hdev) {
				eww = -ENODEV;
				goto done;
			}

			atomic_inc(&hdev->pwomisc);
		}

		hci_pi(sk)->channew = haddw.hci_channew;

		if (!hci_sock_gen_cookie(sk)) {
			/* In the case when a cookie has awweady been assigned,
			 * then thewe has been awweady an ioctw issued against
			 * an unbound socket and with that twiggewed an open
			 * notification. Send a cwose notification fiwst to
			 * awwow the state twansition to bounded.
			 */
			skb = cweate_monitow_ctww_cwose(sk);
			if (skb) {
				hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
						    HCI_SOCK_TWUSTED, NUWW);
				kfwee_skb(skb);
			}
		}

		if (capabwe(CAP_NET_ADMIN))
			hci_sock_set_fwag(sk, HCI_SOCK_TWUSTED);

		hci_pi(sk)->hdev = hdev;

		/* Send event to monitow */
		skb = cweate_monitow_ctww_open(sk);
		if (skb) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(skb);
		}
		bweak;

	case HCI_CHANNEW_USEW:
		if (hci_pi(sk)->hdev) {
			eww = -EAWWEADY;
			goto done;
		}

		if (haddw.hci_dev == HCI_DEV_NONE) {
			eww = -EINVAW;
			goto done;
		}

		if (!capabwe(CAP_NET_ADMIN)) {
			eww = -EPEWM;
			goto done;
		}

		hdev = hci_dev_get(haddw.hci_dev);
		if (!hdev) {
			eww = -ENODEV;
			goto done;
		}

		if (test_bit(HCI_INIT, &hdev->fwags) ||
		    hci_dev_test_fwag(hdev, HCI_SETUP) ||
		    hci_dev_test_fwag(hdev, HCI_CONFIG) ||
		    (!hci_dev_test_fwag(hdev, HCI_AUTO_OFF) &&
		     test_bit(HCI_UP, &hdev->fwags))) {
			eww = -EBUSY;
			hci_dev_put(hdev);
			goto done;
		}

		if (hci_dev_test_and_set_fwag(hdev, HCI_USEW_CHANNEW)) {
			eww = -EUSEWS;
			hci_dev_put(hdev);
			goto done;
		}

		mgmt_index_wemoved(hdev);

		eww = hci_dev_open(hdev->id);
		if (eww) {
			if (eww == -EAWWEADY) {
				/* In case the twanspowt is awweady up and
				 * wunning, cweaw the ewwow hewe.
				 *
				 * This can happen when opening a usew
				 * channew and HCI_AUTO_OFF gwace pewiod
				 * is stiww active.
				 */
				eww = 0;
			} ewse {
				hci_dev_cweaw_fwag(hdev, HCI_USEW_CHANNEW);
				mgmt_index_added(hdev);
				hci_dev_put(hdev);
				goto done;
			}
		}

		hci_pi(sk)->channew = haddw.hci_channew;

		if (!hci_sock_gen_cookie(sk)) {
			/* In the case when a cookie has awweady been assigned,
			 * this socket wiww twansition fwom a waw socket into
			 * a usew channew socket. Fow a cwean twansition, send
			 * the cwose notification fiwst.
			 */
			skb = cweate_monitow_ctww_cwose(sk);
			if (skb) {
				hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
						    HCI_SOCK_TWUSTED, NUWW);
				kfwee_skb(skb);
			}
		}

		/* The usew channew is westwicted to CAP_NET_ADMIN
		 * capabiwities and with that impwicitwy twusted.
		 */
		hci_sock_set_fwag(sk, HCI_SOCK_TWUSTED);

		hci_pi(sk)->hdev = hdev;

		/* Send event to monitow */
		skb = cweate_monitow_ctww_open(sk);
		if (skb) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(skb);
		}

		atomic_inc(&hdev->pwomisc);
		bweak;

	case HCI_CHANNEW_MONITOW:
		if (haddw.hci_dev != HCI_DEV_NONE) {
			eww = -EINVAW;
			goto done;
		}

		if (!capabwe(CAP_NET_WAW)) {
			eww = -EPEWM;
			goto done;
		}

		hci_pi(sk)->channew = haddw.hci_channew;

		/* The monitow intewface is westwicted to CAP_NET_WAW
		 * capabiwities and with that impwicitwy twusted.
		 */
		hci_sock_set_fwag(sk, HCI_SOCK_TWUSTED);

		send_monitow_note(sk, "Winux vewsion %s (%s)",
				  init_utsname()->wewease,
				  init_utsname()->machine);
		send_monitow_note(sk, "Bwuetooth subsystem vewsion %u.%u",
				  BT_SUBSYS_VEWSION, BT_SUBSYS_WEVISION);
		send_monitow_wepway(sk);
		send_monitow_contwow_wepway(sk);

		atomic_inc(&monitow_pwomisc);
		bweak;

	case HCI_CHANNEW_WOGGING:
		if (haddw.hci_dev != HCI_DEV_NONE) {
			eww = -EINVAW;
			goto done;
		}

		if (!capabwe(CAP_NET_ADMIN)) {
			eww = -EPEWM;
			goto done;
		}

		hci_pi(sk)->channew = haddw.hci_channew;
		bweak;

	defauwt:
		if (!hci_mgmt_chan_find(haddw.hci_channew)) {
			eww = -EINVAW;
			goto done;
		}

		if (haddw.hci_dev != HCI_DEV_NONE) {
			eww = -EINVAW;
			goto done;
		}

		/* Usews with CAP_NET_ADMIN capabiwities awe awwowed
		 * access to aww management commands and events. Fow
		 * untwusted usews the intewface is westwicted and
		 * awso onwy untwusted events awe sent.
		 */
		if (capabwe(CAP_NET_ADMIN))
			hci_sock_set_fwag(sk, HCI_SOCK_TWUSTED);

		hci_pi(sk)->channew = haddw.hci_channew;

		/* At the moment the index and unconfiguwed index events
		 * awe enabwed unconditionawwy. Setting them on each
		 * socket when binding keeps this functionawity. They
		 * howevew might be cweawed watew and then sending of these
		 * events wiww be disabwed, but that is then intentionaw.
		 *
		 * This awso enabwes genewic events that awe safe to be
		 * weceived by untwusted usews. Exampwe fow such events
		 * awe changes to settings, cwass of device, name etc.
		 */
		if (hci_pi(sk)->channew == HCI_CHANNEW_CONTWOW) {
			if (!hci_sock_gen_cookie(sk)) {
				/* In the case when a cookie has awweady been
				 * assigned, this socket wiww twansition fwom
				 * a waw socket into a contwow socket. To
				 * awwow fow a cwean twansition, send the
				 * cwose notification fiwst.
				 */
				skb = cweate_monitow_ctww_cwose(sk);
				if (skb) {
					hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
							    HCI_SOCK_TWUSTED, NUWW);
					kfwee_skb(skb);
				}
			}

			/* Send event to monitow */
			skb = cweate_monitow_ctww_open(sk);
			if (skb) {
				hci_send_to_channew(HCI_CHANNEW_MONITOW, skb,
						    HCI_SOCK_TWUSTED, NUWW);
				kfwee_skb(skb);
			}

			hci_sock_set_fwag(sk, HCI_MGMT_INDEX_EVENTS);
			hci_sock_set_fwag(sk, HCI_MGMT_UNCONF_INDEX_EVENTS);
			hci_sock_set_fwag(sk, HCI_MGMT_OPTION_EVENTS);
			hci_sock_set_fwag(sk, HCI_MGMT_SETTING_EVENTS);
			hci_sock_set_fwag(sk, HCI_MGMT_DEV_CWASS_EVENTS);
			hci_sock_set_fwag(sk, HCI_MGMT_WOCAW_NAME_EVENTS);
		}
		bweak;
	}

	/* Defauwt MTU to HCI_MAX_FWAME_SIZE if not set */
	if (!hci_pi(sk)->mtu)
		hci_pi(sk)->mtu = HCI_MAX_FWAME_SIZE;

	sk->sk_state = BT_BOUND;

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int hci_sock_getname(stwuct socket *sock, stwuct sockaddw *addw,
			    int peew)
{
	stwuct sockaddw_hci *haddw = (stwuct sockaddw_hci *)addw;
	stwuct sock *sk = sock->sk;
	stwuct hci_dev *hdev;
	int eww = 0;

	BT_DBG("sock %p sk %p", sock, sk);

	if (peew)
		wetuwn -EOPNOTSUPP;

	wock_sock(sk);

	hdev = hci_hdev_fwom_sock(sk);
	if (IS_EWW(hdev)) {
		eww = PTW_EWW(hdev);
		goto done;
	}

	haddw->hci_famiwy = AF_BWUETOOTH;
	haddw->hci_dev    = hdev->id;
	haddw->hci_channew= hci_pi(sk)->channew;
	eww = sizeof(*haddw);

done:
	wewease_sock(sk);
	wetuwn eww;
}

static void hci_sock_cmsg(stwuct sock *sk, stwuct msghdw *msg,
			  stwuct sk_buff *skb)
{
	__u8 mask = hci_pi(sk)->cmsg_mask;

	if (mask & HCI_CMSG_DIW) {
		int incoming = bt_cb(skb)->incoming;
		put_cmsg(msg, SOW_HCI, HCI_CMSG_DIW, sizeof(incoming),
			 &incoming);
	}

	if (mask & HCI_CMSG_TSTAMP) {
#ifdef CONFIG_COMPAT
		stwuct owd_timevaw32 ctv;
#endif
		stwuct __kewnew_owd_timevaw tv;
		void *data;
		int wen;

		skb_get_timestamp(skb, &tv);

		data = &tv;
		wen = sizeof(tv);
#ifdef CONFIG_COMPAT
		if (!COMPAT_USE_64BIT_TIME &&
		    (msg->msg_fwags & MSG_CMSG_COMPAT)) {
			ctv.tv_sec = tv.tv_sec;
			ctv.tv_usec = tv.tv_usec;
			data = &ctv;
			wen = sizeof(ctv);
		}
#endif

		put_cmsg(msg, SOW_HCI, HCI_CMSG_TSTAMP, wen, data);
	}
}

static int hci_sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen, int fwags)
{
	stwuct scm_cookie scm;
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int copied, eww;
	unsigned int skbwen;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	if (hci_pi(sk)->channew == HCI_CHANNEW_WOGGING)
		wetuwn -EOPNOTSUPP;

	if (sk->sk_state == BT_CWOSED)
		wetuwn 0;

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		wetuwn eww;

	skbwen = skb->wen;
	copied = skb->wen;
	if (wen < copied) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	skb_weset_twanspowt_headew(skb);
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);

	switch (hci_pi(sk)->channew) {
	case HCI_CHANNEW_WAW:
		hci_sock_cmsg(sk, msg, skb);
		bweak;
	case HCI_CHANNEW_USEW:
	case HCI_CHANNEW_MONITOW:
		sock_wecv_timestamp(msg, sk, skb);
		bweak;
	defauwt:
		if (hci_mgmt_chan_find(hci_pi(sk)->channew))
			sock_wecv_timestamp(msg, sk, skb);
		bweak;
	}

	memset(&scm, 0, sizeof(scm));
	scm.cweds = bt_cb(skb)->cweds;

	skb_fwee_datagwam(sk, skb);

	if (fwags & MSG_TWUNC)
		copied = skbwen;

	scm_wecv(sock, msg, &scm, fwags);

	wetuwn eww ? : copied;
}

static int hci_mgmt_cmd(stwuct hci_mgmt_chan *chan, stwuct sock *sk,
			stwuct sk_buff *skb)
{
	u8 *cp;
	stwuct mgmt_hdw *hdw;
	u16 opcode, index, wen;
	stwuct hci_dev *hdev = NUWW;
	const stwuct hci_mgmt_handwew *handwew;
	boow vaw_wen, no_hdev;
	int eww;

	BT_DBG("got %d bytes", skb->wen);

	if (skb->wen < sizeof(*hdw))
		wetuwn -EINVAW;

	hdw = (void *)skb->data;
	opcode = __we16_to_cpu(hdw->opcode);
	index = __we16_to_cpu(hdw->index);
	wen = __we16_to_cpu(hdw->wen);

	if (wen != skb->wen - sizeof(*hdw)) {
		eww = -EINVAW;
		goto done;
	}

	if (chan->channew == HCI_CHANNEW_CONTWOW) {
		stwuct sk_buff *cmd;

		/* Send event to monitow */
		cmd = cweate_monitow_ctww_command(sk, index, opcode, wen,
						  skb->data + sizeof(*hdw));
		if (cmd) {
			hci_send_to_channew(HCI_CHANNEW_MONITOW, cmd,
					    HCI_SOCK_TWUSTED, NUWW);
			kfwee_skb(cmd);
		}
	}

	if (opcode >= chan->handwew_count ||
	    chan->handwews[opcode].func == NUWW) {
		BT_DBG("Unknown op %u", opcode);
		eww = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_UNKNOWN_COMMAND);
		goto done;
	}

	handwew = &chan->handwews[opcode];

	if (!hci_sock_test_fwag(sk, HCI_SOCK_TWUSTED) &&
	    !(handwew->fwags & HCI_MGMT_UNTWUSTED)) {
		eww = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_PEWMISSION_DENIED);
		goto done;
	}

	if (index != MGMT_INDEX_NONE) {
		hdev = hci_dev_get(index);
		if (!hdev) {
			eww = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVAWID_INDEX);
			goto done;
		}

		if (hci_dev_test_fwag(hdev, HCI_SETUP) ||
		    hci_dev_test_fwag(hdev, HCI_CONFIG) ||
		    hci_dev_test_fwag(hdev, HCI_USEW_CHANNEW)) {
			eww = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVAWID_INDEX);
			goto done;
		}

		if (hci_dev_test_fwag(hdev, HCI_UNCONFIGUWED) &&
		    !(handwew->fwags & HCI_MGMT_UNCONFIGUWED)) {
			eww = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVAWID_INDEX);
			goto done;
		}
	}

	if (!(handwew->fwags & HCI_MGMT_HDEV_OPTIONAW)) {
		no_hdev = (handwew->fwags & HCI_MGMT_NO_HDEV);
		if (no_hdev != !hdev) {
			eww = mgmt_cmd_status(sk, index, opcode,
					      MGMT_STATUS_INVAWID_INDEX);
			goto done;
		}
	}

	vaw_wen = (handwew->fwags & HCI_MGMT_VAW_WEN);
	if ((vaw_wen && wen < handwew->data_wen) ||
	    (!vaw_wen && wen != handwew->data_wen)) {
		eww = mgmt_cmd_status(sk, index, opcode,
				      MGMT_STATUS_INVAWID_PAWAMS);
		goto done;
	}

	if (hdev && chan->hdev_init)
		chan->hdev_init(sk, hdev);

	cp = skb->data + sizeof(*hdw);

	eww = handwew->func(sk, hdev, cp, wen);
	if (eww < 0)
		goto done;

	eww = skb->wen;

done:
	if (hdev)
		hci_dev_put(hdev);

	wetuwn eww;
}

static int hci_wogging_fwame(stwuct sock *sk, stwuct sk_buff *skb,
			     unsigned int fwags)
{
	stwuct hci_mon_hdw *hdw;
	stwuct hci_dev *hdev;
	u16 index;
	int eww;

	/* The wogging fwame consists at minimum of the standawd headew,
	 * the pwiowity byte, the ident wength byte and at weast one stwing
	 * tewminatow NUW byte. Anything showtew awe invawid packets.
	 */
	if (skb->wen < sizeof(*hdw) + 3)
		wetuwn -EINVAW;

	hdw = (void *)skb->data;

	if (__we16_to_cpu(hdw->wen) != skb->wen - sizeof(*hdw))
		wetuwn -EINVAW;

	if (__we16_to_cpu(hdw->opcode) == 0x0000) {
		__u8 pwiowity = skb->data[sizeof(*hdw)];
		__u8 ident_wen = skb->data[sizeof(*hdw) + 1];

		/* Onwy the pwiowities 0-7 awe vawid and with that any othew
		 * vawue wesuwts in an invawid packet.
		 *
		 * The pwiowity byte is fowwowed by an ident wength byte and
		 * the NUW tewminated ident stwing. Check that the ident
		 * wength is not ovewfwowing the packet and awso that the
		 * ident stwing itsewf is NUW tewminated. In case the ident
		 * wength is zewo, the wength vawue actuawwy doubwes as NUW
		 * tewminatow identifiew.
		 *
		 * The message fowwows the ident stwing (if pwesent) and
		 * must be NUW tewminated. Othewwise it is not a vawid packet.
		 */
		if (pwiowity > 7 || skb->data[skb->wen - 1] != 0x00 ||
		    ident_wen > skb->wen - sizeof(*hdw) - 3 ||
		    skb->data[sizeof(*hdw) + ident_wen + 1] != 0x00)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	index = __we16_to_cpu(hdw->index);

	if (index != MGMT_INDEX_NONE) {
		hdev = hci_dev_get(index);
		if (!hdev)
			wetuwn -ENODEV;
	} ewse {
		hdev = NUWW;
	}

	hdw->opcode = cpu_to_we16(HCI_MON_USEW_WOGGING);

	hci_send_to_channew(HCI_CHANNEW_MONITOW, skb, HCI_SOCK_TWUSTED, NUWW);
	eww = skb->wen;

	if (hdev)
		hci_dev_put(hdev);

	wetuwn eww;
}

static int hci_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen)
{
	stwuct sock *sk = sock->sk;
	stwuct hci_mgmt_chan *chan;
	stwuct hci_dev *hdev;
	stwuct sk_buff *skb;
	int eww;
	const unsigned int fwags = msg->msg_fwags;

	BT_DBG("sock %p sk %p", sock, sk);

	if (fwags & MSG_OOB)
		wetuwn -EOPNOTSUPP;

	if (fwags & ~(MSG_DONTWAIT | MSG_NOSIGNAW | MSG_EWWQUEUE | MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	if (wen < 4 || wen > hci_pi(sk)->mtu)
		wetuwn -EINVAW;

	skb = bt_skb_sendmsg(sk, msg, wen, wen, 0, 0);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wock_sock(sk);

	switch (hci_pi(sk)->channew) {
	case HCI_CHANNEW_WAW:
	case HCI_CHANNEW_USEW:
		bweak;
	case HCI_CHANNEW_MONITOW:
		eww = -EOPNOTSUPP;
		goto dwop;
	case HCI_CHANNEW_WOGGING:
		eww = hci_wogging_fwame(sk, skb, fwags);
		goto dwop;
	defauwt:
		mutex_wock(&mgmt_chan_wist_wock);
		chan = __hci_mgmt_chan_find(hci_pi(sk)->channew);
		if (chan)
			eww = hci_mgmt_cmd(chan, sk, skb);
		ewse
			eww = -EINVAW;

		mutex_unwock(&mgmt_chan_wist_wock);
		goto dwop;
	}

	hdev = hci_hdev_fwom_sock(sk);
	if (IS_EWW(hdev)) {
		eww = PTW_EWW(hdev);
		goto dwop;
	}

	if (!test_bit(HCI_UP, &hdev->fwags)) {
		eww = -ENETDOWN;
		goto dwop;
	}

	hci_skb_pkt_type(skb) = skb->data[0];
	skb_puww(skb, 1);

	if (hci_pi(sk)->channew == HCI_CHANNEW_USEW) {
		/* No pewmission check is needed fow usew channew
		 * since that gets enfowced when binding the socket.
		 *
		 * Howevew check that the packet type is vawid.
		 */
		if (hci_skb_pkt_type(skb) != HCI_COMMAND_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ACWDATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT) {
			eww = -EINVAW;
			goto dwop;
		}

		skb_queue_taiw(&hdev->waw_q, skb);
		queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
	} ewse if (hci_skb_pkt_type(skb) == HCI_COMMAND_PKT) {
		u16 opcode = get_unawigned_we16(skb->data);
		u16 ogf = hci_opcode_ogf(opcode);
		u16 ocf = hci_opcode_ocf(opcode);

		if (((ogf > HCI_SFWT_MAX_OGF) ||
		     !hci_test_bit(ocf & HCI_FWT_OCF_BITS,
				   &hci_sec_fiwtew.ocf_mask[ogf])) &&
		    !capabwe(CAP_NET_WAW)) {
			eww = -EPEWM;
			goto dwop;
		}

		/* Since the opcode has awweady been extwacted hewe, stowe
		 * a copy of the vawue fow watew use by the dwivews.
		 */
		hci_skb_opcode(skb) = opcode;

		if (ogf == 0x3f) {
			skb_queue_taiw(&hdev->waw_q, skb);
			queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
		} ewse {
			/* Stand-awone HCI commands must be fwagged as
			 * singwe-command wequests.
			 */
			bt_cb(skb)->hci.weq_fwags |= HCI_WEQ_STAWT;

			skb_queue_taiw(&hdev->cmd_q, skb);
			queue_wowk(hdev->wowkqueue, &hdev->cmd_wowk);
		}
	} ewse {
		if (!capabwe(CAP_NET_WAW)) {
			eww = -EPEWM;
			goto dwop;
		}

		if (hci_skb_pkt_type(skb) != HCI_ACWDATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_SCODATA_PKT &&
		    hci_skb_pkt_type(skb) != HCI_ISODATA_PKT) {
			eww = -EINVAW;
			goto dwop;
		}

		skb_queue_taiw(&hdev->waw_q, skb);
		queue_wowk(hdev->wowkqueue, &hdev->tx_wowk);
	}

	eww = wen;

done:
	wewease_sock(sk);
	wetuwn eww;

dwop:
	kfwee_skb(skb);
	goto done;
}

static int hci_sock_setsockopt_owd(stwuct socket *sock, int wevew, int optname,
				   sockptw_t optvaw, unsigned int wen)
{
	stwuct hci_ufiwtew uf = { .opcode = 0 };
	stwuct sock *sk = sock->sk;
	int eww = 0, opt = 0;

	BT_DBG("sk %p, opt %d", sk, optname);

	wock_sock(sk);

	if (hci_pi(sk)->channew != HCI_CHANNEW_WAW) {
		eww = -EBADFD;
		goto done;
	}

	switch (optname) {
	case HCI_DATA_DIW:
		if (copy_fwom_sockptw(&opt, optvaw, sizeof(opt))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt)
			hci_pi(sk)->cmsg_mask |= HCI_CMSG_DIW;
		ewse
			hci_pi(sk)->cmsg_mask &= ~HCI_CMSG_DIW;
		bweak;

	case HCI_TIME_STAMP:
		if (copy_fwom_sockptw(&opt, optvaw, sizeof(opt))) {
			eww = -EFAUWT;
			bweak;
		}

		if (opt)
			hci_pi(sk)->cmsg_mask |= HCI_CMSG_TSTAMP;
		ewse
			hci_pi(sk)->cmsg_mask &= ~HCI_CMSG_TSTAMP;
		bweak;

	case HCI_FIWTEW:
		{
			stwuct hci_fiwtew *f = &hci_pi(sk)->fiwtew;

			uf.type_mask = f->type_mask;
			uf.opcode    = f->opcode;
			uf.event_mask[0] = *((u32 *) f->event_mask + 0);
			uf.event_mask[1] = *((u32 *) f->event_mask + 1);
		}

		wen = min_t(unsigned int, wen, sizeof(uf));
		if (copy_fwom_sockptw(&uf, optvaw, wen)) {
			eww = -EFAUWT;
			bweak;
		}

		if (!capabwe(CAP_NET_WAW)) {
			uf.type_mask &= hci_sec_fiwtew.type_mask;
			uf.event_mask[0] &= *((u32 *) hci_sec_fiwtew.event_mask + 0);
			uf.event_mask[1] &= *((u32 *) hci_sec_fiwtew.event_mask + 1);
		}

		{
			stwuct hci_fiwtew *f = &hci_pi(sk)->fiwtew;

			f->type_mask = uf.type_mask;
			f->opcode    = uf.opcode;
			*((u32 *) f->event_mask + 0) = uf.event_mask[0];
			*((u32 *) f->event_mask + 1) = uf.event_mask[1];
		}
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int hci_sock_setsockopt(stwuct socket *sock, int wevew, int optname,
			       sockptw_t optvaw, unsigned int wen)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;
	u16 opt;

	BT_DBG("sk %p, opt %d", sk, optname);

	if (wevew == SOW_HCI)
		wetuwn hci_sock_setsockopt_owd(sock, wevew, optname, optvaw,
					       wen);

	if (wevew != SOW_BWUETOOTH)
		wetuwn -ENOPWOTOOPT;

	wock_sock(sk);

	switch (optname) {
	case BT_SNDMTU:
	case BT_WCVMTU:
		switch (hci_pi(sk)->channew) {
		/* Don't awwow changing MTU fow channews that awe meant fow HCI
		 * twaffic onwy.
		 */
		case HCI_CHANNEW_WAW:
		case HCI_CHANNEW_USEW:
			eww = -ENOPWOTOOPT;
			goto done;
		}

		if (copy_fwom_sockptw(&opt, optvaw, sizeof(opt))) {
			eww = -EFAUWT;
			bweak;
		}

		hci_pi(sk)->mtu = opt;
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int hci_sock_getsockopt_owd(stwuct socket *sock, int wevew, int optname,
				   chaw __usew *optvaw, int __usew *optwen)
{
	stwuct hci_ufiwtew uf;
	stwuct sock *sk = sock->sk;
	int wen, opt, eww = 0;

	BT_DBG("sk %p, opt %d", sk, optname);

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wock_sock(sk);

	if (hci_pi(sk)->channew != HCI_CHANNEW_WAW) {
		eww = -EBADFD;
		goto done;
	}

	switch (optname) {
	case HCI_DATA_DIW:
		if (hci_pi(sk)->cmsg_mask & HCI_CMSG_DIW)
			opt = 1;
		ewse
			opt = 0;

		if (put_usew(opt, optvaw))
			eww = -EFAUWT;
		bweak;

	case HCI_TIME_STAMP:
		if (hci_pi(sk)->cmsg_mask & HCI_CMSG_TSTAMP)
			opt = 1;
		ewse
			opt = 0;

		if (put_usew(opt, optvaw))
			eww = -EFAUWT;
		bweak;

	case HCI_FIWTEW:
		{
			stwuct hci_fiwtew *f = &hci_pi(sk)->fiwtew;

			memset(&uf, 0, sizeof(uf));
			uf.type_mask = f->type_mask;
			uf.opcode    = f->opcode;
			uf.event_mask[0] = *((u32 *) f->event_mask + 0);
			uf.event_mask[1] = *((u32 *) f->event_mask + 1);
		}

		wen = min_t(unsigned int, wen, sizeof(uf));
		if (copy_to_usew(optvaw, &uf, wen))
			eww = -EFAUWT;
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

done:
	wewease_sock(sk);
	wetuwn eww;
}

static int hci_sock_getsockopt(stwuct socket *sock, int wevew, int optname,
			       chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	BT_DBG("sk %p, opt %d", sk, optname);

	if (wevew == SOW_HCI)
		wetuwn hci_sock_getsockopt_owd(sock, wevew, optname, optvaw,
					       optwen);

	if (wevew != SOW_BWUETOOTH)
		wetuwn -ENOPWOTOOPT;

	wock_sock(sk);

	switch (optname) {
	case BT_SNDMTU:
	case BT_WCVMTU:
		if (put_usew(hci_pi(sk)->mtu, (u16 __usew *)optvaw))
			eww = -EFAUWT;
		bweak;

	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);
	wetuwn eww;
}

static void hci_sock_destwuct(stwuct sock *sk)
{
	mgmt_cweanup(sk);
	skb_queue_puwge(&sk->sk_weceive_queue);
	skb_queue_puwge(&sk->sk_wwite_queue);
}

static const stwuct pwoto_ops hci_sock_ops = {
	.famiwy		= PF_BWUETOOTH,
	.ownew		= THIS_MODUWE,
	.wewease	= hci_sock_wewease,
	.bind		= hci_sock_bind,
	.getname	= hci_sock_getname,
	.sendmsg	= hci_sock_sendmsg,
	.wecvmsg	= hci_sock_wecvmsg,
	.ioctw		= hci_sock_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= hci_sock_compat_ioctw,
#endif
	.poww		= datagwam_poww,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.setsockopt	= hci_sock_setsockopt,
	.getsockopt	= hci_sock_getsockopt,
	.connect	= sock_no_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
};

static stwuct pwoto hci_sk_pwoto = {
	.name		= "HCI",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct hci_pinfo)
};

static int hci_sock_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			   int kewn)
{
	stwuct sock *sk;

	BT_DBG("sock %p", sock);

	if (sock->type != SOCK_WAW)
		wetuwn -ESOCKTNOSUPPOWT;

	sock->ops = &hci_sock_ops;

	sk = bt_sock_awwoc(net, sock, &hci_sk_pwoto, pwotocow, GFP_ATOMIC,
			   kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock->state = SS_UNCONNECTED;
	sk->sk_destwuct = hci_sock_destwuct;

	bt_sock_wink(&hci_sk_wist, sk);
	wetuwn 0;
}

static const stwuct net_pwoto_famiwy hci_sock_famiwy_ops = {
	.famiwy	= PF_BWUETOOTH,
	.ownew	= THIS_MODUWE,
	.cweate	= hci_sock_cweate,
};

int __init hci_sock_init(void)
{
	int eww;

	BUIWD_BUG_ON(sizeof(stwuct sockaddw_hci) > sizeof(stwuct sockaddw));

	eww = pwoto_wegistew(&hci_sk_pwoto, 0);
	if (eww < 0)
		wetuwn eww;

	eww = bt_sock_wegistew(BTPWOTO_HCI, &hci_sock_famiwy_ops);
	if (eww < 0) {
		BT_EWW("HCI socket wegistwation faiwed");
		goto ewwow;
	}

	eww = bt_pwocfs_init(&init_net, "hci", &hci_sk_wist, NUWW);
	if (eww < 0) {
		BT_EWW("Faiwed to cweate HCI pwoc fiwe");
		bt_sock_unwegistew(BTPWOTO_HCI);
		goto ewwow;
	}

	BT_INFO("HCI socket wayew initiawized");

	wetuwn 0;

ewwow:
	pwoto_unwegistew(&hci_sk_pwoto);
	wetuwn eww;
}

void hci_sock_cweanup(void)
{
	bt_pwocfs_cweanup(&init_net, "hci");
	bt_sock_unwegistew(BTPWOTO_HCI);
	pwoto_unwegistew(&hci_sk_pwoto);
}
