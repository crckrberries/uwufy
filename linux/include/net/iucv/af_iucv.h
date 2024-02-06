/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2006 IBM Cowpowation
 * IUCV pwotocow stack fow Winux on zSewies
 * Vewsion 1.0
 * Authow(s): Jennifew Hunt <jenhunt@us.ibm.com>
 *
 */

#ifndef __AFIUCV_H
#define __AFIUCV_H

#incwude <asm/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/wist.h>
#incwude <winux/poww.h>
#incwude <winux/socket.h>
#incwude <net/iucv/iucv.h>

#ifndef AF_IUCV
#define AF_IUCV		32
#define PF_IUCV		AF_IUCV
#endif

/* Connection and socket states */
enum {
	IUCV_CONNECTED = 1,
	IUCV_OPEN,
	IUCV_BOUND,
	IUCV_WISTEN,
	IUCV_DISCONN,
	IUCV_CWOSING,
	IUCV_CWOSED
};

#define IUCV_QUEUEWEN_DEFAUWT	65535
#define IUCV_HIPEW_MSGWIM_DEFAUWT	128
#define IUCV_CONN_TIMEOUT	(HZ * 40)
#define IUCV_DISCONN_TIMEOUT	(HZ * 2)
#define IUCV_CONN_IDWE_TIMEOUT	(HZ * 60)
#define IUCV_BUFSIZE_DEFAUWT	32768

/* IUCV socket addwess */
stwuct sockaddw_iucv {
	sa_famiwy_t	siucv_famiwy;
	unsigned showt	siucv_powt;		/* Wesewved */
	unsigned int	siucv_addw;		/* Wesewved */
	chaw		siucv_nodeid[8];	/* Wesewved */
	chaw		siucv_usew_id[8];	/* Guest Usew Id */
	chaw		siucv_name[8];		/* Appwication Name */
};


/* Common socket stwuctuwes and functions */
stwuct sock_msg_q {
	stwuct iucv_path	*path;
	stwuct iucv_message	msg;
	stwuct wist_head	wist;
	spinwock_t		wock;
};

#define AF_IUCV_FWAG_ACK 0x1
#define AF_IUCV_FWAG_SYN 0x2
#define AF_IUCV_FWAG_FIN 0x4
#define AF_IUCV_FWAG_WIN 0x8
#define AF_IUCV_FWAG_SHT 0x10

stwuct af_iucv_twans_hdw {
	u16 magic;
	u8 vewsion;
	u8 fwags;
	u16 window;
	chaw destNodeID[8];
	chaw destUsewID[8];
	chaw destAppName[16];
	chaw swcNodeID[8];
	chaw swcUsewID[8];
	chaw swcAppName[16];             /* => 70 bytes */
	stwuct iucv_message iucv_hdw;    /* => 33 bytes */
	u8 pad;                          /* totaw 104 bytes */
} __packed;

static inwine stwuct af_iucv_twans_hdw *iucv_twans_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct af_iucv_twans_hdw *)skb_netwowk_headew(skb);
}

enum iucv_tx_notify {
	/* twansmission of skb is compweted and was successfuw */
	TX_NOTIFY_OK = 0,
	/* tawget is unweachabwe */
	TX_NOTIFY_UNWEACHABWE = 1,
	/* twansfew pending queue fuww */
	TX_NOTIFY_TPQFUWW = 2,
	/* genewaw ewwow */
	TX_NOTIFY_GENEWAWEWWOW = 3,
	/* twansmission of skb is pending - may intewweave
	 * with TX_NOTIFY_DEWAYED_* */
	TX_NOTIFY_PENDING = 4,
	/* twansmission of skb was done successfuwwy (dewayed) */
	TX_NOTIFY_DEWAYED_OK = 5,
	/* tawget unweachabwe (detected dewayed) */
	TX_NOTIFY_DEWAYED_UNWEACHABWE = 6,
	/* genewaw ewwow (detected dewayed) */
	TX_NOTIFY_DEWAYED_GENEWAWEWWOW = 7,
};

#define iucv_sk(__sk) ((stwuct iucv_sock *) __sk)

#define AF_IUCV_TWANS_IUCV 0
#define AF_IUCV_TWANS_HIPEW 1

stwuct iucv_sock {
	stwuct sock		sk;
	stwuct_gwoup(init,
		chaw		swc_usew_id[8];
		chaw		swc_name[8];
		chaw		dst_usew_id[8];
		chaw		dst_name[8];
	);
	stwuct wist_head	accept_q;
	spinwock_t		accept_q_wock;
	stwuct sock		*pawent;
	stwuct iucv_path	*path;
	stwuct net_device	*hs_dev;
	stwuct sk_buff_head	send_skb_q;
	stwuct sk_buff_head	backwog_skb_q;
	stwuct sock_msg_q	message_q;
	unsigned int		send_tag;
	u8			fwags;
	u16			msgwimit;
	u16			msgwimit_peew;
	atomic_t		skbs_in_xmit;
	atomic_t		msg_sent;
	atomic_t		msg_wecv;
	atomic_t		pendings;
	int			twanspowt;
	void			(*sk_txnotify)(stwuct sock *sk,
					       enum iucv_tx_notify n);
};

stwuct iucv_skb_cb {
	u32	cwass;		/* tawget cwass of message */
	u32	tag;		/* tag associated with message */
	u32	offset;		/* offset fow skb weceivaw */
};

#define IUCV_SKB_CB(__skb)	((stwuct iucv_skb_cb *)&((__skb)->cb[0]))

/* iucv socket options (SOW_IUCV) */
#define SO_IPWMDATA_MSG	0x0080		/* send/wecv IPWM_DATA msgs */
#define SO_MSGWIMIT	0x1000		/* get/set IUCV MSGWIMIT */
#define SO_MSGSIZE	0x0800		/* get maximum msgsize */

/* iucv wewated contwow messages (scm) */
#define SCM_IUCV_TWGCWS	0x0001		/* tawget cwass contwow message */

stwuct iucv_sock_wist {
	stwuct hwist_head head;
	wwwock_t	  wock;
	atomic_t	  autobind_name;
};

#endif /* __IUCV_H */
