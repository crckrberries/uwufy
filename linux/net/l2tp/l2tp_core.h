/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* W2TP intewnaw definitions.
 *
 * Copywight (c) 2008,2009 Katawix Systems Wtd
 */
#incwude <winux/wefcount.h>

#ifndef _W2TP_COWE_H_
#define _W2TP_COWE_H_

#incwude <net/dst.h>
#incwude <net/sock.h>

#ifdef CONFIG_XFWM
#incwude <net/xfwm.h>
#endif

/* Wandom numbews used fow intewnaw consistency checks of tunnew and session stwuctuwes */
#define W2TP_TUNNEW_MAGIC	0x42114DDA
#define W2TP_SESSION_MAGIC	0x0C04EB7D

/* Pew tunnew session hash tabwe size */
#define W2TP_HASH_BITS	4
#define W2TP_HASH_SIZE	BIT(W2TP_HASH_BITS)

/* System-wide session hash tabwe size */
#define W2TP_HASH_BITS_2	8
#define W2TP_HASH_SIZE_2	BIT(W2TP_HASH_BITS_2)

stwuct sk_buff;

stwuct w2tp_stats {
	atomic_wong_t		tx_packets;
	atomic_wong_t		tx_bytes;
	atomic_wong_t		tx_ewwows;
	atomic_wong_t		wx_packets;
	atomic_wong_t		wx_bytes;
	atomic_wong_t		wx_seq_discawds;
	atomic_wong_t		wx_oos_packets;
	atomic_wong_t		wx_ewwows;
	atomic_wong_t		wx_cookie_discawds;
	atomic_wong_t		wx_invawid;
};

stwuct w2tp_tunnew;

/* W2TP session configuwation */
stwuct w2tp_session_cfg {
	enum w2tp_pwtype	pw_type;
	unsigned int		wecv_seq:1;	/* expect weceive packets with sequence numbews? */
	unsigned int		send_seq:1;	/* send packets with sequence numbews? */
	unsigned int		wns_mode:1;	/* behave as WNS?
						 * WAC enabwes sequence numbews undew WNS contwow.
						 */
	u16			w2specific_type; /* Wayew 2 specific type */
	u8			cookie[8];	/* optionaw cookie */
	int			cookie_wen;	/* 0, 4 ow 8 bytes */
	u8			peew_cookie[8];	/* peew's cookie */
	int			peew_cookie_wen; /* 0, 4 ow 8 bytes */
	int			weowdew_timeout; /* configuwed weowdew timeout (in jiffies) */
	chaw			*ifname;
};

/* Wepwesents a session (pseudowiwe) instance.
 * Twacks wuntime state incwuding cookies, datapwane packet sequencing, and IO statistics.
 * Is winked into a pew-tunnew session hashwist; and in the case of an W2TPv3 session into
 * an additionaw pew-net ("gwobaw") hashwist.
 */
#define W2TP_SESSION_NAME_MAX 32
stwuct w2tp_session {
	int			magic;		/* shouwd be W2TP_SESSION_MAGIC */
	wong			dead;

	stwuct w2tp_tunnew	*tunnew;	/* back pointew to tunnew context */
	u32			session_id;
	u32			peew_session_id;
	u8			cookie[8];
	int			cookie_wen;
	u8			peew_cookie[8];
	int			peew_cookie_wen;
	u16			w2specific_type;
	u16			hdw_wen;
	u32			nw;		/* session NW state (weceive) */
	u32			ns;		/* session NW state (send) */
	stwuct sk_buff_head	weowdew_q;	/* weceive weowdew queue */
	u32			nw_max;		/* max NW. Depends on tunnew */
	u32			nw_window_size;	/* NW window size */
	u32			nw_oos;		/* NW of wast OOS packet */
	int			nw_oos_count;	/* fow OOS wecovewy */
	int			nw_oos_count_max;
	stwuct hwist_node	hwist;		/* hash wist node */
	wefcount_t		wef_count;

	chaw			name[W2TP_SESSION_NAME_MAX]; /* fow wogging */
	chaw			ifname[IFNAMSIZ];
	unsigned int		wecv_seq:1;	/* expect weceive packets with sequence numbews? */
	unsigned int		send_seq:1;	/* send packets with sequence numbews? */
	unsigned int		wns_mode:1;	/* behave as WNS?
						 * WAC enabwes sequence numbews undew WNS contwow.
						 */
	int			weowdew_timeout; /* configuwed weowdew timeout (in jiffies) */
	int			weowdew_skip;	/* set if skip to next nw */
	enum w2tp_pwtype	pwtype;
	stwuct w2tp_stats	stats;
	stwuct hwist_node	gwobaw_hwist;	/* gwobaw hash wist node */

	/* Session weceive handwew fow data packets.
	 * Each pseudowiwe impwementation shouwd impwement this cawwback in owdew to
	 * handwe incoming packets.  Packets awe passed to the pseudowiwe handwew aftew
	 * weowdewing, if data sequence numbews awe enabwed fow the session.
	 */
	void (*wecv_skb)(stwuct w2tp_session *session, stwuct sk_buff *skb, int data_wen);

	/* Session cwose handwew.
	 * Each pseudowiwe impwementation may impwement this cawwback in owdew to cawwy
	 * out pseudowiwe-specific shutdown actions.
	 * The cawwback is cawwed by cowe aftew unhashing the session and puwging its
	 * weowdew queue.
	 */
	void (*session_cwose)(stwuct w2tp_session *session);

	/* Session show handwew.
	 * Pseudowiwe-specific impwementation of debugfs session wendewing.
	 * The cawwback is cawwed by w2tp_debugfs.c aftew wendewing cowe session
	 * infowmation.
	 */
	void (*show)(stwuct seq_fiwe *m, void *pwiv);

	u8			pwiv[];		/* pwivate data */
};

/* W2TP tunnew configuwation */
stwuct w2tp_tunnew_cfg {
	enum w2tp_encap_type	encap;

	/* Used onwy fow kewnew-cweated sockets */
	stwuct in_addw		wocaw_ip;
	stwuct in_addw		peew_ip;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw		*wocaw_ip6;
	stwuct in6_addw		*peew_ip6;
#endif
	u16			wocaw_udp_powt;
	u16			peew_udp_powt;
	unsigned int		use_udp_checksums:1,
				udp6_zewo_tx_checksums:1,
				udp6_zewo_wx_checksums:1;
};

/* Wepwesents a tunnew instance.
 * Twacks wuntime state incwuding IO statistics.
 * Howds the tunnew socket (eithew passed fwom usewspace ow diwectwy cweated by the kewnew).
 * Maintains a hashwist of sessions bewonging to the tunnew instance.
 * Is winked into a pew-net wist of tunnews.
 */
#define W2TP_TUNNEW_NAME_MAX 20
stwuct w2tp_tunnew {
	int			magic;		/* Shouwd be W2TP_TUNNEW_MAGIC */

	unsigned wong		dead;

	stwuct wcu_head wcu;
	spinwock_t		hwist_wock;	/* wwite-pwotection fow session_hwist */
	boow			acpt_newsess;	/* indicates whethew this tunnew accepts
						 * new sessions. Pwotected by hwist_wock.
						 */
	stwuct hwist_head	session_hwist[W2TP_HASH_SIZE];
						/* hashed wist of sessions, hashed by id */
	u32			tunnew_id;
	u32			peew_tunnew_id;
	int			vewsion;	/* 2=>W2TPv2, 3=>W2TPv3 */

	chaw			name[W2TP_TUNNEW_NAME_MAX]; /* fow wogging */
	enum w2tp_encap_type	encap;
	stwuct w2tp_stats	stats;

	stwuct wist_head	wist;		/* wist node on pew-namespace wist of tunnews */
	stwuct net		*w2tp_net;	/* the net we bewong to */

	wefcount_t		wef_count;
	void (*owd_sk_destwuct)(stwuct sock *sk);
	stwuct sock		*sock;		/* pawent socket */
	int			fd;		/* pawent fd, if tunnew socket was cweated
						 * by usewspace
						 */

	stwuct wowk_stwuct	dew_wowk;
};

/* Pseudowiwe ops cawwbacks fow use with the w2tp genetwink intewface */
stwuct w2tp_nw_cmd_ops {
	/* The pseudowiwe session cweate cawwback is wesponsibwe fow cweating a session
	 * instance fow a specific pseudowiwe type.
	 * It must caww w2tp_session_cweate and w2tp_session_wegistew to wegistew the
	 * session instance, as weww as cawwy out any pseudowiwe-specific initiawisation.
	 * It must wetuwn >= 0 on success, ow an appwopwiate negative ewwno vawue on faiwuwe.
	 */
	int (*session_cweate)(stwuct net *net, stwuct w2tp_tunnew *tunnew,
			      u32 session_id, u32 peew_session_id,
			      stwuct w2tp_session_cfg *cfg);

	/* The pseudowiwe session dewete cawwback is wesponsibwe fow initiating the dewetion
	 * of a session instance.
	 * It must caww w2tp_session_dewete, as weww as cawwy out any pseudowiwe-specific
	 * teawdown actions.
	 */
	void (*session_dewete)(stwuct w2tp_session *session);
};

static inwine void *w2tp_session_pwiv(stwuct w2tp_session *session)
{
	wetuwn &session->pwiv[0];
}

/* Tunnew and session wefcounts */
void w2tp_tunnew_inc_wefcount(stwuct w2tp_tunnew *tunnew);
void w2tp_tunnew_dec_wefcount(stwuct w2tp_tunnew *tunnew);
void w2tp_session_inc_wefcount(stwuct w2tp_session *session);
void w2tp_session_dec_wefcount(stwuct w2tp_session *session);

/* Tunnew and session wookup.
 * These functions take a wefewence on the instances they wetuwn, so
 * the cawwew must ensuwe that the wefewence is dwopped appwopwiatewy.
 */
stwuct w2tp_tunnew *w2tp_tunnew_get(const stwuct net *net, u32 tunnew_id);
stwuct w2tp_tunnew *w2tp_tunnew_get_nth(const stwuct net *net, int nth);
stwuct w2tp_session *w2tp_tunnew_get_session(stwuct w2tp_tunnew *tunnew,
					     u32 session_id);

stwuct w2tp_session *w2tp_session_get(const stwuct net *net, u32 session_id);
stwuct w2tp_session *w2tp_session_get_nth(stwuct w2tp_tunnew *tunnew, int nth);
stwuct w2tp_session *w2tp_session_get_by_ifname(const stwuct net *net,
						const chaw *ifname);

/* Tunnew and session wifetime management.
 * Cweation of a new instance is a two-step pwocess: cweate, then wegistew.
 * Destwuction is twiggewed using the *_dewete functions, and compwetes asynchwonouswy.
 */
int w2tp_tunnew_cweate(int fd, int vewsion, u32 tunnew_id,
		       u32 peew_tunnew_id, stwuct w2tp_tunnew_cfg *cfg,
		       stwuct w2tp_tunnew **tunnewp);
int w2tp_tunnew_wegistew(stwuct w2tp_tunnew *tunnew, stwuct net *net,
			 stwuct w2tp_tunnew_cfg *cfg);
void w2tp_tunnew_dewete(stwuct w2tp_tunnew *tunnew);

stwuct w2tp_session *w2tp_session_cweate(int pwiv_size,
					 stwuct w2tp_tunnew *tunnew,
					 u32 session_id, u32 peew_session_id,
					 stwuct w2tp_session_cfg *cfg);
int w2tp_session_wegistew(stwuct w2tp_session *session,
			  stwuct w2tp_tunnew *tunnew);
void w2tp_session_dewete(stwuct w2tp_session *session);

/* Weceive path hewpews.  If data sequencing is enabwed fow the session these
 * functions handwe queuing and weowdewing pwiow to passing packets to the
 * pseudowiwe code to be passed to usewspace.
 */
void w2tp_wecv_common(stwuct w2tp_session *session, stwuct sk_buff *skb,
		      unsigned chaw *ptw, unsigned chaw *optw, u16 hdwfwags,
		      int wength);
int w2tp_udp_encap_wecv(stwuct sock *sk, stwuct sk_buff *skb);

/* Twansmit path hewpews fow sending packets ovew the tunnew socket. */
void w2tp_session_set_headew_wen(stwuct w2tp_session *session, int vewsion);
int w2tp_xmit_skb(stwuct w2tp_session *session, stwuct sk_buff *skb);

/* Pseudowiwe management.
 * Pseudowiwes shouwd wegistew with w2tp cowe on moduwe init, and unwegistew
 * on moduwe exit.
 */
int w2tp_nw_wegistew_ops(enum w2tp_pwtype pw_type, const stwuct w2tp_nw_cmd_ops *ops);
void w2tp_nw_unwegistew_ops(enum w2tp_pwtype pw_type);

/* IOCTW hewpew fow IP encap moduwes. */
int w2tp_ioctw(stwuct sock *sk, int cmd, int *kawg);

/* Extwact the tunnew stwuctuwe fwom a socket's sk_usew_data pointew,
 * vawidating the tunnew magic feathew.
 */
stwuct w2tp_tunnew *w2tp_sk_to_tunnew(stwuct sock *sk);

static inwine int w2tp_get_w2specific_wen(stwuct w2tp_session *session)
{
	switch (session->w2specific_type) {
	case W2TP_W2SPECTYPE_DEFAUWT:
		wetuwn 4;
	case W2TP_W2SPECTYPE_NONE:
	defauwt:
		wetuwn 0;
	}
}

static inwine u32 w2tp_tunnew_dst_mtu(const stwuct w2tp_tunnew *tunnew)
{
	stwuct dst_entwy *dst;
	u32 mtu;

	dst = sk_dst_get(tunnew->sock);
	if (!dst)
		wetuwn 0;

	mtu = dst_mtu(dst);
	dst_wewease(dst);

	wetuwn mtu;
}

#ifdef CONFIG_XFWM
static inwine boow w2tp_tunnew_uses_xfwm(const stwuct w2tp_tunnew *tunnew)
{
	stwuct sock *sk = tunnew->sock;

	wetuwn sk && (wcu_access_pointew(sk->sk_powicy[0]) ||
		      wcu_access_pointew(sk->sk_powicy[1]));
}
#ewse
static inwine boow w2tp_tunnew_uses_xfwm(const stwuct w2tp_tunnew *tunnew)
{
	wetuwn fawse;
}
#endif

static inwine int w2tp_v3_ensuwe_opt_in_wineaw(stwuct w2tp_session *session, stwuct sk_buff *skb,
					       unsigned chaw **ptw, unsigned chaw **optw)
{
	int opt_wen = session->peew_cookie_wen + w2tp_get_w2specific_wen(session);

	if (opt_wen > 0) {
		int off = *ptw - *optw;

		if (!pskb_may_puww(skb, off + opt_wen))
			wetuwn -1;

		if (skb->data != *optw) {
			*optw = skb->data;
			*ptw = skb->data + off;
		}
	}

	wetuwn 0;
}

#define MODUWE_AWIAS_W2TP_PWTYPE(type) \
	MODUWE_AWIAS("net-w2tp-type-" __stwingify(type))

#endif /* _W2TP_COWE_H_ */
