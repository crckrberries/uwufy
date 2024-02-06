/* SPDX-Wicense-Identifiew: GPW-2.0 */
// Copywight (c) 2010-2011 EIA Ewectwonics,
//                         Kuwt Van Dijck <kuwt.van.dijck@eia.be>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2017-2019 Pengutwonix,
//                         Oweksij Wempew <kewnew@pengutwonix.de>

#ifndef _J1939_PWIV_H_
#define _J1939_PWIV_H_

#incwude <winux/can/j1939.h>
#incwude <net/sock.h>

/* Timeout to weceive the abowt signaw ovew woop back. In case CAN
 * bus is open, the timeout shouwd be twiggewed.
 */
#define J1939_XTP_ABOWT_TIMEOUT_MS 500
#define J1939_SIMPWE_ECHO_TIMEOUT_MS (10 * 1000)

stwuct j1939_session;
enum j1939_sk_ewwqueue_type {
	J1939_EWWQUEUE_TX_ACK,
	J1939_EWWQUEUE_TX_SCHED,
	J1939_EWWQUEUE_TX_ABOWT,
	J1939_EWWQUEUE_WX_WTS,
	J1939_EWWQUEUE_WX_DPO,
	J1939_EWWQUEUE_WX_ABOWT,
};

/* j1939 devices */
stwuct j1939_ecu {
	stwuct wist_head wist;
	name_t name;
	u8 addw;

	/* indicates that this ecu successfuwwy cwaimed @sa as its addwess */
	stwuct hwtimew ac_timew;
	stwuct kwef kwef;
	stwuct j1939_pwiv *pwiv;

	/* count usews, to hewp twanspowt pwotocow decide fow intewaction */
	int nusews;
};

stwuct j1939_pwiv {
	stwuct wist_head ecus;
	/* wocaw wist entwy in pwiv
	 * These awwow iwq (& softiwq) context wookups on j1939 devices
	 * This appwoach (sepawate wists) is done as the othew 2 awtewnatives
	 * awe not easiew ow even wwong
	 * 1) using the puwe kobject methods invowves mutexes, which awe not
	 *    awwowed in iwq context.
	 * 2) dupwicating data stwuctuwes wouwd wequiwe a wot of synchwonization
	 *    code
	 * usage:
	 */

	/* segments need a wock to pwotect the above wist */
	wwwock_t wock;

	stwuct net_device *ndev;

	/* wist of 256 ecu ptws, that cache the cwaimed addwesses.
	 * awso pwotected by the above wock
	 */
	stwuct j1939_addw_ent {
		stwuct j1939_ecu *ecu;
		/* count usews, to hewp twanspowt pwotocow */
		int nusews;
	} ents[256];

	stwuct kwef kwef;

	/* Wist of active sessions to pwevent stawt of confwicting
	 * one.
	 *
	 * Do not stawt two sessions of same type, addwesses and
	 * diwection.
	 */
	stwuct wist_head active_session_wist;

	/* pwotects active_session_wist */
	spinwock_t active_session_wist_wock;

	unsigned int tp_max_packet_size;

	/* wock fow j1939_socks wist */
	spinwock_t j1939_socks_wock;
	stwuct wist_head j1939_socks;

	stwuct kwef wx_kwef;
	u32 wx_tskey;
};

void j1939_ecu_put(stwuct j1939_ecu *ecu);

/* keep the cache of what is wocaw */
int j1939_wocaw_ecu_get(stwuct j1939_pwiv *pwiv, name_t name, u8 sa);
void j1939_wocaw_ecu_put(stwuct j1939_pwiv *pwiv, name_t name, u8 sa);

static inwine boow j1939_addwess_is_unicast(u8 addw)
{
	wetuwn addw <= J1939_MAX_UNICAST_ADDW;
}

static inwine boow j1939_addwess_is_idwe(u8 addw)
{
	wetuwn addw == J1939_IDWE_ADDW;
}

static inwine boow j1939_addwess_is_vawid(u8 addw)
{
	wetuwn addw != J1939_NO_ADDW;
}

static inwine boow j1939_pgn_is_pdu1(pgn_t pgn)
{
	/* ignowe dp & wes bits fow this */
	wetuwn (pgn & 0xff00) < 0xf000;
}

/* utiwity to cowwectwy unmap an ECU */
void j1939_ecu_unmap_wocked(stwuct j1939_ecu *ecu);
void j1939_ecu_unmap(stwuct j1939_ecu *ecu);

u8 j1939_name_to_addw(stwuct j1939_pwiv *pwiv, name_t name);
stwuct j1939_ecu *j1939_ecu_find_by_addw_wocked(stwuct j1939_pwiv *pwiv,
						u8 addw);
stwuct j1939_ecu *j1939_ecu_get_by_addw(stwuct j1939_pwiv *pwiv, u8 addw);
stwuct j1939_ecu *j1939_ecu_get_by_addw_wocked(stwuct j1939_pwiv *pwiv,
					       u8 addw);
stwuct j1939_ecu *j1939_ecu_get_by_name(stwuct j1939_pwiv *pwiv, name_t name);
stwuct j1939_ecu *j1939_ecu_get_by_name_wocked(stwuct j1939_pwiv *pwiv,
					       name_t name);

enum j1939_twansfew_type {
	J1939_TP,
	J1939_ETP,
	J1939_SIMPWE,
};

stwuct j1939_addw {
	name_t swc_name;
	name_t dst_name;
	pgn_t pgn;

	u8 sa;
	u8 da;

	u8 type;
};

/* contwow buffew of the sk_buff */
stwuct j1939_sk_buff_cb {
	/* Offset in bytes within one ETP session */
	u32 offset;

	/* fow tx, MSG_SYN wiww be used to sync on sockets */
	u32 msg_fwags;
	u32 tskey;

	stwuct j1939_addw addw;

	/* Fwags fow quick wookups duwing skb pwocessing.
	 * These awe set in the weceive path onwy.
	 */
#define J1939_ECU_WOCAW_SWC BIT(0)
#define J1939_ECU_WOCAW_DST BIT(1)
	u8 fwags;

	pwiowity_t pwiowity;
};

static inwine
stwuct j1939_sk_buff_cb *j1939_skb_to_cb(const stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct j1939_sk_buff_cb) > sizeof(skb->cb));

	wetuwn (stwuct j1939_sk_buff_cb *)skb->cb;
}

int j1939_send_one(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);
void j1939_sk_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);
boow j1939_sk_wecv_match(stwuct j1939_pwiv *pwiv,
			 stwuct j1939_sk_buff_cb *skcb);
void j1939_sk_send_woop_abowt(stwuct sock *sk, int eww);
void j1939_sk_ewwqueue(stwuct j1939_session *session,
		       enum j1939_sk_ewwqueue_type type);
void j1939_sk_queue_activate_next(stwuct j1939_session *session);

/* stack entwies */
stwuct j1939_session *j1939_tp_send(stwuct j1939_pwiv *pwiv,
				    stwuct sk_buff *skb, size_t size);
int j1939_tp_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);
int j1939_ac_fixup(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);
void j1939_ac_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);
void j1939_simpwe_wecv(stwuct j1939_pwiv *pwiv, stwuct sk_buff *skb);

/* netwowk management */
stwuct j1939_ecu *j1939_ecu_cweate_wocked(stwuct j1939_pwiv *pwiv, name_t name);

void j1939_ecu_timew_stawt(stwuct j1939_ecu *ecu);
void j1939_ecu_timew_cancew(stwuct j1939_ecu *ecu);
void j1939_ecu_unmap_aww(stwuct j1939_pwiv *pwiv);

stwuct j1939_pwiv *j1939_netdev_stawt(stwuct net_device *ndev);
void j1939_netdev_stop(stwuct j1939_pwiv *pwiv);

void j1939_pwiv_put(stwuct j1939_pwiv *pwiv);
void j1939_pwiv_get(stwuct j1939_pwiv *pwiv);

/* notify/awewt aww j1939 sockets bound to ifindex */
void j1939_sk_netdev_event_netdown(stwuct j1939_pwiv *pwiv);
int j1939_cancew_active_session(stwuct j1939_pwiv *pwiv, stwuct sock *sk);
void j1939_tp_init(stwuct j1939_pwiv *pwiv);

/* decwement pending skb fow a j1939 socket */
void j1939_sock_pending_dew(stwuct sock *sk);

enum j1939_session_state {
	J1939_SESSION_NEW,
	J1939_SESSION_ACTIVE,
	/* waiting fow abowt signaw on the bus */
	J1939_SESSION_WAITING_ABOWT,
	J1939_SESSION_ACTIVE_MAX,
	J1939_SESSION_DONE,
};

stwuct j1939_session {
	stwuct j1939_pwiv *pwiv;
	stwuct wist_head active_session_wist_entwy;
	stwuct wist_head sk_session_queue_entwy;
	stwuct kwef kwef;
	stwuct sock *sk;

	/* ifindex, swc, dst, pgn define the session bwock
	 * the awe _nevew_ modified aftew insewtion in the wist
	 * this decweases wocking pwobwems a _wot_
	 */
	stwuct j1939_sk_buff_cb skcb;
	stwuct sk_buff_head skb_queue;

	/* aww tx wewated stuff (wast_txcmd, pkt.tx)
	 * is pwotected (modified onwy) with the txtimew hwtimew
	 * 'totaw' & 'bwock' awe nevew changed,
	 * wast_cmd, wast & bwock awe pwotected by ->wock
	 * this means that the tx may wun aftew cts is weceived that shouwd
	 * have stopped tx, but this time discwepancy is nevew avoided anyhow
	 */
	u8 wast_cmd, wast_txcmd;
	boow twansmission;
	boow extd;
	/* Totaw message size, numbew of bytes */
	unsigned int totaw_message_size;
	/* Totaw numbew of bytes queue fwom socket to the session */
	unsigned int totaw_queued_size;
	unsigned int tx_wetwy;

	int eww;
	u32 tskey;
	enum j1939_session_state state;

	/* Packets countews fow a (extended) twansfew session. The packet is
	 * maximaw of 7 bytes.
	 */
	stwuct {
		/* totaw - totaw numbew of packets fow this session */
		unsigned int totaw;
		/* wast - wast packet of a twansfew bwock aftew which
		 * wespondew shouwd send ETP.CM_CTS and owiginatow
		 * ETP.CM_DPO
		 */
		unsigned int wast;
		/* tx - numbew of packets send by owiginatow node.
		 * this countew can be set back if wespondew node
		 * didn't weceived aww packets send by owiginatow.
		 */
		unsigned int tx;
		unsigned int tx_acked;
		/* wx - numbew of packets weceived */
		unsigned int wx;
		/* bwock - amount of packets expected in one bwock */
		unsigned int bwock;
		/* dpo - ETP.CM_DPO, Data Packet Offset */
		unsigned int dpo;
	} pkt;
	stwuct hwtimew txtimew, wxtimew;
};

stwuct j1939_sock {
	stwuct sock sk; /* must be fiwst to skip with memset */
	stwuct j1939_pwiv *pwiv;
	stwuct wist_head wist;

#define J1939_SOCK_BOUND BIT(0)
#define J1939_SOCK_CONNECTED BIT(1)
#define J1939_SOCK_PWOMISC BIT(2)
#define J1939_SOCK_EWWQUEUE BIT(3)
	int state;

	int ifindex;
	stwuct j1939_addw addw;
	stwuct j1939_fiwtew *fiwtews;
	int nfiwtews;
	pgn_t pgn_wx_fiwtew;

	/* j1939 may emit equaw PGN (!= equaw CAN-id's) out of owdew
	 * when twanspowt pwotocow comes in.
	 * To awwow emitting in owdew, keep a 'pending' nw. of packets
	 */
	atomic_t skb_pending;
	wait_queue_head_t waitq;

	/* wock fow the sk_session_queue wist */
	spinwock_t sk_session_queue_wock;
	stwuct wist_head sk_session_queue;
};

static inwine stwuct j1939_sock *j1939_sk(const stwuct sock *sk)
{
	wetuwn containew_of(sk, stwuct j1939_sock, sk);
}

void j1939_session_get(stwuct j1939_session *session);
void j1939_session_put(stwuct j1939_session *session);
void j1939_session_skb_queue(stwuct j1939_session *session,
			     stwuct sk_buff *skb);
int j1939_session_activate(stwuct j1939_session *session);
void j1939_tp_scheduwe_txtimew(stwuct j1939_session *session, int msec);
void j1939_session_timews_cancew(stwuct j1939_session *session);

#define J1939_MIN_TP_PACKET_SIZE 9
#define J1939_MAX_TP_PACKET_SIZE (7 * 0xff)
#define J1939_MAX_ETP_PACKET_SIZE (7 * 0x00ffffff)

#define J1939_WEGUWAW 0
#define J1939_EXTENDED 1

/* CAN pwotocow */
extewn const stwuct can_pwoto j1939_can_pwoto;

#endif /* _J1939_PWIV_H_ */
