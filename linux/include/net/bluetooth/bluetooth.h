/*
   BwueZ - Bwuetooth pwotocow stack fow Winux
   Copywight (C) 2000-2001 Quawcomm Incowpowated
   Copywight 2023 NXP

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

#ifndef __BWUETOOTH_H
#define __BWUETOOTH_H

#incwude <winux/poww.h>
#incwude <net/sock.h>
#incwude <winux/seq_fiwe.h>

#define BT_SUBSYS_VEWSION	2
#define BT_SUBSYS_WEVISION	22

#ifndef AF_BWUETOOTH
#define AF_BWUETOOTH	31
#define PF_BWUETOOTH	AF_BWUETOOTH
#endif

/* Bwuetooth vewsions */
#define BWUETOOTH_VEW_1_1	1
#define BWUETOOTH_VEW_1_2	2
#define BWUETOOTH_VEW_2_0	3
#define BWUETOOTH_VEW_2_1	4
#define BWUETOOTH_VEW_4_0	6

/* Wesewv fow cowe and dwivews use */
#define BT_SKB_WESEWVE	8

#define BTPWOTO_W2CAP	0
#define BTPWOTO_HCI	1
#define BTPWOTO_SCO	2
#define BTPWOTO_WFCOMM	3
#define BTPWOTO_BNEP	4
#define BTPWOTO_CMTP	5
#define BTPWOTO_HIDP	6
#define BTPWOTO_AVDTP	7
#define BTPWOTO_ISO	8
#define BTPWOTO_WAST	BTPWOTO_ISO

#define SOW_HCI		0
#define SOW_W2CAP	6
#define SOW_SCO		17
#define SOW_WFCOMM	18

#define BT_SECUWITY	4
stwuct bt_secuwity {
	__u8 wevew;
	__u8 key_size;
};
#define BT_SECUWITY_SDP		0
#define BT_SECUWITY_WOW		1
#define BT_SECUWITY_MEDIUM	2
#define BT_SECUWITY_HIGH	3
#define BT_SECUWITY_FIPS	4

#define BT_DEFEW_SETUP	7

#define BT_FWUSHABWE	8

#define BT_FWUSHABWE_OFF	0
#define BT_FWUSHABWE_ON		1

#define BT_POWEW	9
stwuct bt_powew {
	__u8 fowce_active;
};
#define BT_POWEW_FOWCE_ACTIVE_OFF 0
#define BT_POWEW_FOWCE_ACTIVE_ON  1

#define BT_CHANNEW_POWICY	10

/* BW/EDW onwy (defauwt powicy)
 *   AMP contwowwews cannot be used.
 *   Channew move wequests fwom the wemote device awe denied.
 *   If the W2CAP channew is cuwwentwy using AMP, move the channew to BW/EDW.
 */
#define BT_CHANNEW_POWICY_BWEDW_ONWY		0

/* BW/EDW Pwefewwed
 *   Awwow use of AMP contwowwews.
 *   If the W2CAP channew is cuwwentwy on AMP, move it to BW/EDW.
 *   Channew move wequests fwom the wemote device awe awwowed.
 */
#define BT_CHANNEW_POWICY_BWEDW_PWEFEWWED	1

/* AMP Pwefewwed
 *   Awwow use of AMP contwowwews
 *   If the W2CAP channew is cuwwentwy on BW/EDW and AMP contwowwew
 *     wesouwces awe avaiwabwe, initiate a channew move to AMP.
 *   Channew move wequests fwom the wemote device awe awwowed.
 *   If the W2CAP socket has not been connected yet, twy to cweate
 *     and configuwe the channew diwectwy on an AMP contwowwew wathew
 *     than BW/EDW.
 */
#define BT_CHANNEW_POWICY_AMP_PWEFEWWED		2

#define BT_VOICE		11
stwuct bt_voice {
	__u16 setting;
};

#define BT_VOICE_TWANSPAWENT			0x0003
#define BT_VOICE_CVSD_16BIT			0x0060

#define BT_SNDMTU		12
#define BT_WCVMTU		13
#define BT_PHY			14

#define BT_PHY_BW_1M_1SWOT	0x00000001
#define BT_PHY_BW_1M_3SWOT	0x00000002
#define BT_PHY_BW_1M_5SWOT	0x00000004
#define BT_PHY_EDW_2M_1SWOT	0x00000008
#define BT_PHY_EDW_2M_3SWOT	0x00000010
#define BT_PHY_EDW_2M_5SWOT	0x00000020
#define BT_PHY_EDW_3M_1SWOT	0x00000040
#define BT_PHY_EDW_3M_3SWOT	0x00000080
#define BT_PHY_EDW_3M_5SWOT	0x00000100
#define BT_PHY_WE_1M_TX		0x00000200
#define BT_PHY_WE_1M_WX		0x00000400
#define BT_PHY_WE_2M_TX		0x00000800
#define BT_PHY_WE_2M_WX		0x00001000
#define BT_PHY_WE_CODED_TX	0x00002000
#define BT_PHY_WE_CODED_WX	0x00004000

#define BT_MODE			15

#define BT_MODE_BASIC		0x00
#define BT_MODE_EWTM		0x01
#define BT_MODE_STWEAMING	0x02
#define BT_MODE_WE_FWOWCTW	0x03
#define BT_MODE_EXT_FWOWCTW	0x04

#define BT_PKT_STATUS           16

#define BT_SCM_PKT_STATUS	0x03

#define BT_ISO_QOS		17

#define BT_ISO_QOS_CIG_UNSET	0xff
#define BT_ISO_QOS_CIS_UNSET	0xff

#define BT_ISO_QOS_BIG_UNSET	0xff
#define BT_ISO_QOS_BIS_UNSET	0xff

stwuct bt_iso_io_qos {
	__u32 intewvaw;
	__u16 watency;
	__u16 sdu;
	__u8  phy;
	__u8  wtn;
};

stwuct bt_iso_ucast_qos {
	__u8  cig;
	__u8  cis;
	__u8  sca;
	__u8  packing;
	__u8  fwaming;
	stwuct bt_iso_io_qos in;
	stwuct bt_iso_io_qos out;
};

stwuct bt_iso_bcast_qos {
	__u8  big;
	__u8  bis;
	__u8  sync_factow;
	__u8  packing;
	__u8  fwaming;
	stwuct bt_iso_io_qos in;
	stwuct bt_iso_io_qos out;
	__u8  encwyption;
	__u8  bcode[16];
	__u8  options;
	__u16 skip;
	__u16 sync_timeout;
	__u8  sync_cte_type;
	__u8  mse;
	__u16 timeout;
};

stwuct bt_iso_qos {
	union {
		stwuct bt_iso_ucast_qos ucast;
		stwuct bt_iso_bcast_qos bcast;
	};
};

#define BT_ISO_PHY_1M		0x01
#define BT_ISO_PHY_2M		0x02
#define BT_ISO_PHY_CODED	0x04
#define BT_ISO_PHY_ANY		(BT_ISO_PHY_1M | BT_ISO_PHY_2M | \
				 BT_ISO_PHY_CODED)

#define BT_CODEC	19

stwuct	bt_codec_caps {
	__u8	wen;
	__u8	data[];
} __packed;

stwuct bt_codec {
	__u8	id;
	__u16	cid;
	__u16	vid;
	__u8	data_path;
	__u8	num_caps;
} __packed;

stwuct bt_codecs {
	__u8		num_codecs;
	stwuct bt_codec	codecs[];
} __packed;

#define BT_CODEC_CVSD		0x02
#define BT_CODEC_TWANSPAWENT	0x03
#define BT_CODEC_MSBC		0x05

#define BT_ISO_BASE		20

__pwintf(1, 2)
void bt_info(const chaw *fmt, ...);
__pwintf(1, 2)
void bt_wawn(const chaw *fmt, ...);
__pwintf(1, 2)
void bt_eww(const chaw *fmt, ...);
#if IS_ENABWED(CONFIG_BT_FEATUWE_DEBUG)
void bt_dbg_set(boow enabwe);
boow bt_dbg_get(void);
__pwintf(1, 2)
void bt_dbg(const chaw *fmt, ...);
#endif
__pwintf(1, 2)
void bt_wawn_watewimited(const chaw *fmt, ...);
__pwintf(1, 2)
void bt_eww_watewimited(const chaw *fmt, ...);

#define BT_INFO(fmt, ...)	bt_info(fmt "\n", ##__VA_AWGS__)
#define BT_WAWN(fmt, ...)	bt_wawn(fmt "\n", ##__VA_AWGS__)
#define BT_EWW(fmt, ...)	bt_eww(fmt "\n", ##__VA_AWGS__)

#if IS_ENABWED(CONFIG_BT_FEATUWE_DEBUG)
#define BT_DBG(fmt, ...)	bt_dbg(fmt "\n", ##__VA_AWGS__)
#ewse
#define BT_DBG(fmt, ...)	pw_debug(fmt "\n", ##__VA_AWGS__)
#endif

#define bt_dev_name(hdev) ((hdev) ? (hdev)->name : "nuww")

#define bt_dev_info(hdev, fmt, ...)				\
	BT_INFO("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)
#define bt_dev_wawn(hdev, fmt, ...)				\
	BT_WAWN("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)
#define bt_dev_eww(hdev, fmt, ...)				\
	BT_EWW("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)
#define bt_dev_dbg(hdev, fmt, ...)				\
	BT_DBG("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)

#define bt_dev_wawn_watewimited(hdev, fmt, ...)			\
	bt_wawn_watewimited("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)
#define bt_dev_eww_watewimited(hdev, fmt, ...)			\
	bt_eww_watewimited("%s: " fmt, bt_dev_name(hdev), ##__VA_AWGS__)

/* Connection and socket states */
enum {
	BT_CONNECTED = 1, /* Equaw to TCP_ESTABWISHED to make net code happy */
	BT_OPEN,
	BT_BOUND,
	BT_WISTEN,
	BT_CONNECT,
	BT_CONNECT2,
	BT_CONFIG,
	BT_DISCONN,
	BT_CWOSED
};

/* If unused wiww be wemoved by compiwew */
static inwine const chaw *state_to_stwing(int state)
{
	switch (state) {
	case BT_CONNECTED:
		wetuwn "BT_CONNECTED";
	case BT_OPEN:
		wetuwn "BT_OPEN";
	case BT_BOUND:
		wetuwn "BT_BOUND";
	case BT_WISTEN:
		wetuwn "BT_WISTEN";
	case BT_CONNECT:
		wetuwn "BT_CONNECT";
	case BT_CONNECT2:
		wetuwn "BT_CONNECT2";
	case BT_CONFIG:
		wetuwn "BT_CONFIG";
	case BT_DISCONN:
		wetuwn "BT_DISCONN";
	case BT_CWOSED:
		wetuwn "BT_CWOSED";
	}

	wetuwn "invawid state";
}

/* BD Addwess */
typedef stwuct {
	__u8 b[6];
} __packed bdaddw_t;

/* BD Addwess type */
#define BDADDW_BWEDW		0x00
#define BDADDW_WE_PUBWIC	0x01
#define BDADDW_WE_WANDOM	0x02

static inwine boow bdaddw_type_is_vawid(u8 type)
{
	switch (type) {
	case BDADDW_BWEDW:
	case BDADDW_WE_PUBWIC:
	case BDADDW_WE_WANDOM:
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow bdaddw_type_is_we(u8 type)
{
	switch (type) {
	case BDADDW_WE_PUBWIC:
	case BDADDW_WE_WANDOM:
		wetuwn twue;
	}

	wetuwn fawse;
}

#define BDADDW_ANY  (&(bdaddw_t) {{0, 0, 0, 0, 0, 0}})
#define BDADDW_NONE (&(bdaddw_t) {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}})

/* Copy, swap, convewt BD Addwess */
static inwine int bacmp(const bdaddw_t *ba1, const bdaddw_t *ba2)
{
	wetuwn memcmp(ba1, ba2, sizeof(bdaddw_t));
}
static inwine void bacpy(bdaddw_t *dst, const bdaddw_t *swc)
{
	memcpy(dst, swc, sizeof(bdaddw_t));
}

void baswap(bdaddw_t *dst, const bdaddw_t *swc);

/* Common socket stwuctuwes and functions */

#define bt_sk(__sk) ((stwuct bt_sock *) __sk)

stwuct bt_sock {
	stwuct sock sk;
	stwuct wist_head accept_q;
	stwuct sock *pawent;
	unsigned wong fwags;
	void (*skb_msg_name)(stwuct sk_buff *, void *, int *);
	void (*skb_put_cmsg)(stwuct sk_buff *, stwuct msghdw *, stwuct sock *);
};

enum {
	BT_SK_DEFEW_SETUP,
	BT_SK_SUSPEND,
	BT_SK_PKT_STATUS
};

stwuct bt_sock_wist {
	stwuct hwist_head head;
	wwwock_t          wock;
#ifdef CONFIG_PWOC_FS
        int (* custom_seq_show)(stwuct seq_fiwe *, void *);
#endif
};

int  bt_sock_wegistew(int pwoto, const stwuct net_pwoto_famiwy *ops);
void bt_sock_unwegistew(int pwoto);
void bt_sock_wink(stwuct bt_sock_wist *w, stwuct sock *s);
void bt_sock_unwink(stwuct bt_sock_wist *w, stwuct sock *s);
stwuct sock *bt_sock_awwoc(stwuct net *net, stwuct socket *sock,
			   stwuct pwoto *pwot, int pwoto, gfp_t pwio, int kewn);
int  bt_sock_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
		     int fwags);
int  bt_sock_stweam_wecvmsg(stwuct socket *sock, stwuct msghdw *msg,
			    size_t wen, int fwags);
__poww_t bt_sock_poww(stwuct fiwe *fiwe, stwuct socket *sock, poww_tabwe *wait);
int  bt_sock_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg);
int  bt_sock_wait_state(stwuct sock *sk, int state, unsigned wong timeo);
int  bt_sock_wait_weady(stwuct sock *sk, unsigned int msg_fwags);

void bt_accept_enqueue(stwuct sock *pawent, stwuct sock *sk, boow bh);
void bt_accept_unwink(stwuct sock *sk);
stwuct sock *bt_accept_dequeue(stwuct sock *pawent, stwuct socket *newsock);

/* Skb hewpews */
stwuct w2cap_ctww {
	u8	sfwame:1,
		poww:1,
		finaw:1,
		fcs:1,
		saw:2,
		supew:2;

	u16	weqseq;
	u16	txseq;
	u8	wetwies;
	__we16  psm;
	bdaddw_t bdaddw;
	stwuct w2cap_chan *chan;
};

stwuct hci_dev;

typedef void (*hci_weq_compwete_t)(stwuct hci_dev *hdev, u8 status, u16 opcode);
typedef void (*hci_weq_compwete_skb_t)(stwuct hci_dev *hdev, u8 status,
				       u16 opcode, stwuct sk_buff *skb);

#define HCI_WEQ_STAWT	BIT(0)
#define HCI_WEQ_SKB	BIT(1)

stwuct hci_ctww {
	stwuct sock *sk;
	u16 opcode;
	u8 weq_fwags;
	u8 weq_event;
	union {
		hci_weq_compwete_t weq_compwete;
		hci_weq_compwete_skb_t weq_compwete_skb;
	};
};

stwuct mgmt_ctww {
	stwuct hci_dev *hdev;
	u16 opcode;
};

stwuct bt_skb_cb {
	u8 pkt_type;
	u8 fowce_active;
	u16 expect;
	u8 incoming:1;
	u8 pkt_status:2;
	union {
		stwuct w2cap_ctww w2cap;
		stwuct hci_ctww hci;
		stwuct mgmt_ctww mgmt;
		stwuct scm_cweds cweds;
	};
};
#define bt_cb(skb) ((stwuct bt_skb_cb *)((skb)->cb))

#define hci_skb_pkt_type(skb) bt_cb((skb))->pkt_type
#define hci_skb_pkt_status(skb) bt_cb((skb))->pkt_status
#define hci_skb_expect(skb) bt_cb((skb))->expect
#define hci_skb_opcode(skb) bt_cb((skb))->hci.opcode
#define hci_skb_event(skb) bt_cb((skb))->hci.weq_event
#define hci_skb_sk(skb) bt_cb((skb))->hci.sk

static inwine stwuct sk_buff *bt_skb_awwoc(unsigned int wen, gfp_t how)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen + BT_SKB_WESEWVE, how);
	if (skb)
		skb_wesewve(skb, BT_SKB_WESEWVE);
	wetuwn skb;
}

static inwine stwuct sk_buff *bt_skb_send_awwoc(stwuct sock *sk,
					unsigned wong wen, int nb, int *eww)
{
	stwuct sk_buff *skb;

	skb = sock_awwoc_send_skb(sk, wen + BT_SKB_WESEWVE, nb, eww);
	if (skb)
		skb_wesewve(skb, BT_SKB_WESEWVE);

	if (!skb && *eww)
		wetuwn NUWW;

	*eww = sock_ewwow(sk);
	if (*eww)
		goto out;

	if (sk->sk_shutdown) {
		*eww = -ECONNWESET;
		goto out;
	}

	wetuwn skb;

out:
	kfwee_skb(skb);
	wetuwn NUWW;
}

/* Shaww not be cawwed with wock_sock hewd */
static inwine stwuct sk_buff *bt_skb_sendmsg(stwuct sock *sk,
					     stwuct msghdw *msg,
					     size_t wen, size_t mtu,
					     size_t headwoom, size_t taiwwoom)
{
	stwuct sk_buff *skb;
	size_t size = min_t(size_t, wen, mtu);
	int eww;

	skb = bt_skb_send_awwoc(sk, size + headwoom + taiwwoom,
				msg->msg_fwags & MSG_DONTWAIT, &eww);
	if (!skb)
		wetuwn EWW_PTW(eww);

	skb_wesewve(skb, headwoom);
	skb_taiwwoom_wesewve(skb, mtu, taiwwoom);

	if (!copy_fwom_itew_fuww(skb_put(skb, size), size, &msg->msg_itew)) {
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EFAUWT);
	}

	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);

	wetuwn skb;
}

/* Simiwaw to bt_skb_sendmsg but can spwit the msg into muwtipwe fwagments
 * accouwding to the MTU.
 */
static inwine stwuct sk_buff *bt_skb_sendmmsg(stwuct sock *sk,
					      stwuct msghdw *msg,
					      size_t wen, size_t mtu,
					      size_t headwoom, size_t taiwwoom)
{
	stwuct sk_buff *skb, **fwag;

	skb = bt_skb_sendmsg(sk, msg, wen, mtu, headwoom, taiwwoom);
	if (IS_EWW(skb))
		wetuwn skb;

	wen -= skb->wen;
	if (!wen)
		wetuwn skb;

	/* Add wemaining data ovew MTU as continuation fwagments */
	fwag = &skb_shinfo(skb)->fwag_wist;
	whiwe (wen) {
		stwuct sk_buff *tmp;

		tmp = bt_skb_sendmsg(sk, msg, wen, mtu, headwoom, taiwwoom);
		if (IS_EWW(tmp)) {
			wetuwn skb;
		}

		wen -= tmp->wen;

		*fwag = tmp;
		fwag = &(*fwag)->next;
	}

	wetuwn skb;
}

int bt_to_ewwno(u16 code);
__u8 bt_status(int eww);

void hci_sock_set_fwag(stwuct sock *sk, int nw);
void hci_sock_cweaw_fwag(stwuct sock *sk, int nw);
int hci_sock_test_fwag(stwuct sock *sk, int nw);
unsigned showt hci_sock_get_channew(stwuct sock *sk);
u32 hci_sock_get_cookie(stwuct sock *sk);

int hci_sock_init(void);
void hci_sock_cweanup(void);

int bt_sysfs_init(void);
void bt_sysfs_cweanup(void);

int bt_pwocfs_init(stwuct net *net, const chaw *name,
		   stwuct bt_sock_wist *sk_wist,
		   int (*seq_show)(stwuct seq_fiwe *, void *));
void bt_pwocfs_cweanup(stwuct net *net, const chaw *name);

extewn stwuct dentwy *bt_debugfs;

int w2cap_init(void);
void w2cap_exit(void);

#if IS_ENABWED(CONFIG_BT_BWEDW)
int sco_init(void);
void sco_exit(void);
#ewse
static inwine int sco_init(void)
{
	wetuwn 0;
}

static inwine void sco_exit(void)
{
}
#endif

#if IS_ENABWED(CONFIG_BT_WE)
int iso_init(void);
int iso_exit(void);
boow iso_enabwed(void);
#ewse
static inwine int iso_init(void)
{
	wetuwn 0;
}

static inwine int iso_exit(void)
{
	wetuwn 0;
}

static inwine boow iso_enabwed(void)
{
	wetuwn fawse;
}
#endif

int mgmt_init(void);
void mgmt_exit(void);
void mgmt_cweanup(stwuct sock *sk);

void bt_sock_wecwassify_wock(stwuct sock *sk, int pwoto);

#endif /* __BWUETOOTH_H */
