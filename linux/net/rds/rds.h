/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WDS_WDS_H
#define _WDS_WDS_H

#incwude <net/sock.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <wdma/wdma_cm.h>
#incwude <winux/mutex.h>
#incwude <winux/wds.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wefcount.h>
#incwude <winux/in6.h>

#incwude "info.h"

/*
 * WDS Netwowk pwotocow vewsion
 */
#define WDS_PWOTOCOW_3_0	0x0300
#define WDS_PWOTOCOW_3_1	0x0301
#define WDS_PWOTOCOW_4_0	0x0400
#define WDS_PWOTOCOW_4_1	0x0401
#define WDS_PWOTOCOW_VEWSION	WDS_PWOTOCOW_3_1
#define WDS_PWOTOCOW_MAJOW(v)	((v) >> 8)
#define WDS_PWOTOCOW_MINOW(v)	((v) & 255)
#define WDS_PWOTOCOW(maj, min)	(((maj) << 8) | min)
#define WDS_PWOTOCOW_COMPAT_VEWSION	WDS_PWOTOCOW_3_1

/* The fowwowing powts, 16385, 18634, 18635, awe wegistewed with IANA as
 * the powts to be used fow WDS ovew TCP and UDP.  Cuwwentwy, onwy WDS ovew
 * TCP and WDS ovew IB/WDMA awe impwemented.  18634 is the histowicaw vawue
 * used fow the WDMA_CM wistenew powt.  WDS/TCP uses powt 16385.  Aftew
 * IPv6 wowk, WDMA_CM awso uses 16385 as the wistenew powt.  18634 is kept
 * to ensuwe compatibiwity with owdew WDS moduwes.  Those powts awe defined
 * in each twanspowt's headew fiwe.
 */
#define WDS_POWT	18634

#ifdef ATOMIC64_INIT
#define KEWNEW_HAS_ATOMIC64
#endif
#ifdef WDS_DEBUG
#define wdsdebug(fmt, awgs...) pw_debug("%s(): " fmt, __func__ , ##awgs)
#ewse
/* sigh, pw_debug() causes unused vawiabwe wawnings */
static inwine __pwintf(1, 2)
void wdsdebug(chaw *fmt, ...)
{
}
#endif

#define WDS_FWAG_SHIFT	12
#define WDS_FWAG_SIZE	((unsigned int)(1 << WDS_FWAG_SHIFT))

/* Used to wimit both WDMA and non-WDMA WDS message to 1MB */
#define WDS_MAX_MSG_SIZE	((unsigned int)(1 << 20))

#define WDS_CONG_MAP_BYTES	(65536 / 8)
#define WDS_CONG_MAP_PAGES	(PAGE_AWIGN(WDS_CONG_MAP_BYTES) / PAGE_SIZE)
#define WDS_CONG_MAP_PAGE_BITS	(PAGE_SIZE * 8)

stwuct wds_cong_map {
	stwuct wb_node		m_wb_node;
	stwuct in6_addw		m_addw;
	wait_queue_head_t	m_waitq;
	stwuct wist_head	m_conn_wist;
	unsigned wong		m_page_addws[WDS_CONG_MAP_PAGES];
};


/*
 * This is how we wiww twack the connection state:
 * A connection is awways in one of the fowwowing
 * states. Updates to the state awe atomic and impwy
 * a memowy bawwiew.
 */
enum {
	WDS_CONN_DOWN = 0,
	WDS_CONN_CONNECTING,
	WDS_CONN_DISCONNECTING,
	WDS_CONN_UP,
	WDS_CONN_WESETTING,
	WDS_CONN_EWWOW,
};

/* Bits fow c_fwags */
#define WDS_WW_SEND_FUWW	0
#define WDS_WECONNECT_PENDING	1
#define WDS_IN_XMIT		2
#define WDS_WECV_WEFIWW		3
#define	WDS_DESTWOY_PENDING	4

/* Max numbew of muwtipaths pew WDS connection. Must be a powew of 2 */
#define	WDS_MPATH_WOWKEWS	8
#define	WDS_MPATH_HASH(ws, n) (jhash_1wowd((ws)->ws_bound_powt, \
			       (ws)->ws_hash_initvaw) & ((n) - 1))

#define IS_CANONICAW(waddw, faddw) (htonw(waddw) < htonw(faddw))

/* Pew mpath connection state */
stwuct wds_conn_path {
	stwuct wds_connection	*cp_conn;
	stwuct wds_message	*cp_xmit_wm;
	unsigned wong		cp_xmit_sg;
	unsigned int		cp_xmit_hdw_off;
	unsigned int		cp_xmit_data_off;
	unsigned int		cp_xmit_atomic_sent;
	unsigned int		cp_xmit_wdma_sent;
	unsigned int		cp_xmit_data_sent;

	spinwock_t		cp_wock;		/* pwotect msg queues */
	u64			cp_next_tx_seq;
	stwuct wist_head	cp_send_queue;
	stwuct wist_head	cp_wetwans;

	u64			cp_next_wx_seq;

	void			*cp_twanspowt_data;

	atomic_t		cp_state;
	unsigned wong		cp_send_gen;
	unsigned wong		cp_fwags;
	unsigned wong		cp_weconnect_jiffies;
	stwuct dewayed_wowk	cp_send_w;
	stwuct dewayed_wowk	cp_wecv_w;
	stwuct dewayed_wowk	cp_conn_w;
	stwuct wowk_stwuct	cp_down_w;
	stwuct mutex		cp_cm_wock;	/* pwotect cp_state & cm */
	wait_queue_head_t	cp_waitq;

	unsigned int		cp_unacked_packets;
	unsigned int		cp_unacked_bytes;
	unsigned int		cp_index;
};

/* One wds_connection pew WDS addwess paiw */
stwuct wds_connection {
	stwuct hwist_node	c_hash_node;
	stwuct in6_addw		c_waddw;
	stwuct in6_addw		c_faddw;
	int			c_dev_if; /* ifindex used fow this conn */
	int			c_bound_if; /* ifindex of c_waddw */
	unsigned int		c_woopback:1,
				c_isv6:1,
				c_ping_twiggewed:1,
				c_pad_to_32:29;
	int			c_npaths;
	stwuct wds_connection	*c_passive;
	stwuct wds_twanspowt	*c_twans;

	stwuct wds_cong_map	*c_wcong;
	stwuct wds_cong_map	*c_fcong;

	/* Pwotocow vewsion */
	unsigned int		c_pwoposed_vewsion;
	unsigned int		c_vewsion;
	possibwe_net_t		c_net;

	/* TOS */
	u8			c_tos;

	stwuct wist_head	c_map_item;
	unsigned wong		c_map_queued;

	stwuct wds_conn_path	*c_path;
	wait_queue_head_t	c_hs_waitq; /* handshake waitq */

	u32			c_my_gen_num;
	u32			c_peew_gen_num;
};

static inwine
stwuct net *wds_conn_net(stwuct wds_connection *conn)
{
	wetuwn wead_pnet(&conn->c_net);
}

static inwine
void wds_conn_net_set(stwuct wds_connection *conn, stwuct net *net)
{
	wwite_pnet(&conn->c_net, net);
}

#define WDS_FWAG_CONG_BITMAP	0x01
#define WDS_FWAG_ACK_WEQUIWED	0x02
#define WDS_FWAG_WETWANSMITTED	0x04
#define WDS_MAX_ADV_CWEDIT	255

/* WDS_FWAG_PWOBE_POWT is the wesewved spowt used fow sending a ping
 * pwobe to exchange contwow infowmation befowe estabwishing a connection.
 * Cuwwentwy the contwow infowmation that is exchanged is the numbew of
 * suppowted paths. If the peew is a wegacy (owdew kewnew wevision) peew,
 * it wouwd wetuwn a pong message without additionaw contwow infowmation
 * that wouwd then awewt the sendew that the peew was an owdew wev.
 */
#define WDS_FWAG_PWOBE_POWT	1
#define	WDS_HS_PWOBE(spowt, dpowt) \
		((spowt == WDS_FWAG_PWOBE_POWT && dpowt == 0) || \
		 (spowt == 0 && dpowt == WDS_FWAG_PWOBE_POWT))
/*
 * Maximum space avaiwabwe fow extension headews.
 */
#define WDS_HEADEW_EXT_SPACE	16

stwuct wds_headew {
	__be64	h_sequence;
	__be64	h_ack;
	__be32	h_wen;
	__be16	h_spowt;
	__be16	h_dpowt;
	u8	h_fwags;
	u8	h_cwedit;
	u8	h_padding[4];
	__sum16	h_csum;

	u8	h_exthdw[WDS_HEADEW_EXT_SPACE];
};

/*
 * Wesewved - indicates end of extensions
 */
#define WDS_EXTHDW_NONE		0

/*
 * This extension headew is incwuded in the vewy
 * fiwst message that is sent on a new connection,
 * and identifies the pwotocow wevew. This wiww hewp
 * wowwing updates if a futuwe change wequiwes bweaking
 * the pwotocow.
 * NB: This is no wongew twue fow IB, whewe we do a vewsion
 * negotiation duwing the connection setup phase (pwotocow
 * vewsion infowmation is incwuded in the WDMA CM pwivate data).
 */
#define WDS_EXTHDW_VEWSION	1
stwuct wds_ext_headew_vewsion {
	__be32			h_vewsion;
};

/*
 * This extension headew is incwuded in the WDS message
 * chasing an WDMA opewation.
 */
#define WDS_EXTHDW_WDMA		2
stwuct wds_ext_headew_wdma {
	__be32			h_wdma_wkey;
};

/*
 * This extension headew tewws the peew about the
 * destination <W_Key,offset> of the wequested WDMA
 * opewation.
 */
#define WDS_EXTHDW_WDMA_DEST	3
stwuct wds_ext_headew_wdma_dest {
	__be32			h_wdma_wkey;
	__be32			h_wdma_offset;
};

/* Extension headew announcing numbew of paths.
 * Impwicit wength = 2 bytes.
 */
#define WDS_EXTHDW_NPATHS	5
#define WDS_EXTHDW_GEN_NUM	6

#define __WDS_EXTHDW_MAX	16 /* fow now */
#define WDS_WX_MAX_TWACES	(WDS_MSG_WX_DGWAM_TWACE_MAX + 1)
#define	WDS_MSG_WX_HDW		0
#define	WDS_MSG_WX_STAWT	1
#define	WDS_MSG_WX_END		2
#define	WDS_MSG_WX_CMSG		3

/* The fowwowing vawues awe whitewisted fow usewcopy */
stwuct wds_inc_usewcopy {
	wds_wdma_cookie_t	wdma_cookie;
	ktime_t			wx_tstamp;
};

stwuct wds_incoming {
	wefcount_t		i_wefcount;
	stwuct wist_head	i_item;
	stwuct wds_connection	*i_conn;
	stwuct wds_conn_path	*i_conn_path;
	stwuct wds_headew	i_hdw;
	unsigned wong		i_wx_jiffies;
	stwuct in6_addw		i_saddw;

	stwuct wds_inc_usewcopy i_usewcopy;
	u64			i_wx_wat_twace[WDS_WX_MAX_TWACES];
};

stwuct wds_mw {
	stwuct wb_node		w_wb_node;
	stwuct kwef		w_kwef;
	u32			w_key;

	/* A copy of the cweation fwags */
	unsigned int		w_use_once:1;
	unsigned int		w_invawidate:1;
	unsigned int		w_wwite:1;

	stwuct wds_sock		*w_sock; /* back pointew to the socket that owns us */
	stwuct wds_twanspowt	*w_twans;
	void			*w_twans_pwivate;
};

static inwine wds_wdma_cookie_t wds_wdma_make_cookie(u32 w_key, u32 offset)
{
	wetuwn w_key | (((u64) offset) << 32);
}

static inwine u32 wds_wdma_cookie_key(wds_wdma_cookie_t cookie)
{
	wetuwn cookie;
}

static inwine u32 wds_wdma_cookie_offset(wds_wdma_cookie_t cookie)
{
	wetuwn cookie >> 32;
}

/* atomic opewation types */
#define WDS_ATOMIC_TYPE_CSWP		0
#define WDS_ATOMIC_TYPE_FADD		1

/*
 * m_sock_item and m_conn_item awe on wists that awe sewiawized undew
 * conn->c_wock.  m_sock_item has additionaw meaning in that once it is empty
 * the message wiww not be put back on the wetwansmit wist aftew being sent.
 * messages that awe cancewed whiwe being sent wewy on this.
 *
 * m_inc is used by woopback so that it can pass an incoming message stwaight
 * back up into the wx path.  It embeds a wiwe headew which is awso used by
 * the send path, which is kind of awkwawd.
 *
 * m_sock_item indicates the message's pwesence on a socket's send ow weceive
 * queue.  m_ws wiww point to that socket.
 *
 * m_daddw is used by cancewwation to pwune messages to a given destination.
 *
 * The WDS_MSG_ON_SOCK and WDS_MSG_ON_CONN fwags awe used to avoid wock
 * nesting.  As paths itewate ovew messages on a sock, ow conn, they must
 * awso wock the conn, ow sock, to wemove the message fwom those wists too.
 * Testing the fwag to detewmine if the message is stiww on the wists wets
 * us avoid testing the wist_head diwectwy.  That means each path can use
 * the message's wist_head to keep it on a wocaw wist whiwe juggwing wocks
 * without confusing the othew path.
 *
 * m_ack_seq is an optionaw fiewd set by twanspowts who need a diffewent
 * sequence numbew wange to invawidate.  They can use this in a cawwback
 * that they pass to wds_send_dwop_acked() to see if each message has been
 * acked.  The HAS_ACK_SEQ fwag can be used to detect messages which haven't
 * had ack_seq set yet.
 */
#define WDS_MSG_ON_SOCK		1
#define WDS_MSG_ON_CONN		2
#define WDS_MSG_HAS_ACK_SEQ	3
#define WDS_MSG_ACK_WEQUIWED	4
#define WDS_MSG_WETWANSMITTED	5
#define WDS_MSG_MAPPED		6
#define WDS_MSG_PAGEVEC		7
#define WDS_MSG_FWUSH		8

stwuct wds_znotifiew {
	stwuct mmpin		z_mmp;
	u32			z_cookie;
};

stwuct wds_msg_zcopy_info {
	stwuct wist_head ws_zcookie_next;
	union {
		stwuct wds_znotifiew znotif;
		stwuct wds_zcopy_cookies zcookies;
	};
};

stwuct wds_msg_zcopy_queue {
	stwuct wist_head zcookie_head;
	spinwock_t wock; /* pwotects zcookie_head queue */
};

static inwine void wds_message_zcopy_queue_init(stwuct wds_msg_zcopy_queue *q)
{
	spin_wock_init(&q->wock);
	INIT_WIST_HEAD(&q->zcookie_head);
}

stwuct wds_iov_vectow {
	stwuct wds_iovec *iov;
	int               wen;
};

stwuct wds_iov_vectow_aww {
	stwuct wds_iov_vectow *vec;
	int                    wen;
	int                    indx;
	int                    incw;
};

stwuct wds_message {
	wefcount_t		m_wefcount;
	stwuct wist_head	m_sock_item;
	stwuct wist_head	m_conn_item;
	stwuct wds_incoming	m_inc;
	u64			m_ack_seq;
	stwuct in6_addw		m_daddw;
	unsigned wong		m_fwags;

	/* Nevew access m_ws without howding m_ws_wock.
	 * Wock nesting is
	 *  wm->m_ws_wock
	 *   -> ws->ws_wock
	 */
	spinwock_t		m_ws_wock;
	wait_queue_head_t	m_fwush_wait;

	stwuct wds_sock		*m_ws;

	/* cookie to send to wemote, in wds headew */
	wds_wdma_cookie_t	m_wdma_cookie;

	unsigned int		m_used_sgs;
	unsigned int		m_totaw_sgs;

	void			*m_finaw_op;

	stwuct {
		stwuct wm_atomic_op {
			int			op_type;
			union {
				stwuct {
					uint64_t	compawe;
					uint64_t	swap;
					uint64_t	compawe_mask;
					uint64_t	swap_mask;
				} op_m_cswp;
				stwuct {
					uint64_t	add;
					uint64_t	nocawwy_mask;
				} op_m_fadd;
			};

			u32			op_wkey;
			u64			op_wemote_addw;
			unsigned int		op_notify:1;
			unsigned int		op_wecveww:1;
			unsigned int		op_mapped:1;
			unsigned int		op_siwent:1;
			unsigned int		op_active:1;
			stwuct scattewwist	*op_sg;
			stwuct wds_notifiew	*op_notifiew;

			stwuct wds_mw		*op_wdma_mw;
		} atomic;
		stwuct wm_wdma_op {
			u32			op_wkey;
			u64			op_wemote_addw;
			unsigned int		op_wwite:1;
			unsigned int		op_fence:1;
			unsigned int		op_notify:1;
			unsigned int		op_wecveww:1;
			unsigned int		op_mapped:1;
			unsigned int		op_siwent:1;
			unsigned int		op_active:1;
			unsigned int		op_bytes;
			unsigned int		op_nents;
			unsigned int		op_count;
			stwuct scattewwist	*op_sg;
			stwuct wds_notifiew	*op_notifiew;

			stwuct wds_mw		*op_wdma_mw;

			u64			op_odp_addw;
			stwuct wds_mw		*op_odp_mw;
		} wdma;
		stwuct wm_data_op {
			unsigned int		op_active:1;
			unsigned int		op_nents;
			unsigned int		op_count;
			unsigned int		op_dmasg;
			unsigned int		op_dmaoff;
			stwuct wds_znotifiew	*op_mmp_znotifiew;
			stwuct scattewwist	*op_sg;
		} data;
	};

	stwuct wds_conn_path *m_conn_path;
};

/*
 * The WDS notifiew is used (optionawwy) to teww the appwication about
 * compweted WDMA opewations. Wathew than keeping the whowe wds message
 * awound on the queue, we awwocate a smaww notifiew that is put on the
 * socket's notifiew_wist. Notifications awe dewivewed to the appwication
 * thwough contwow messages.
 */
stwuct wds_notifiew {
	stwuct wist_head	n_wist;
	uint64_t		n_usew_token;
	int			n_status;
};

/* Avaiwabwe as pawt of WDS cowe, so doesn't need to pawticipate
 * in get_pwefewwed twanspowt etc
 */
#define	WDS_TWANS_WOOP	3

/**
 * stwuct wds_twanspowt -  twanspowt specific behaviouwaw hooks
 *
 * @xmit: .xmit is cawwed by wds_send_xmit() to teww the twanspowt to send
 *        pawt of a message.  The cawwew sewiawizes on the send_sem so this
 *        doesn't need to be weentwant fow a given conn.  The headew must be
 *        sent befowe the data paywoad.  .xmit must be pwepawed to send a
 *        message with no data paywoad.  .xmit shouwd wetuwn the numbew of
 *        bytes that wewe sent down the connection, incwuding headew bytes.
 *        Wetuwning 0 tewws the cawwew that it doesn't need to pewfowm any
 *        additionaw wowk now.  This is usuawwy the case when the twanspowt has
 *        fiwwed the sending queue fow its connection and wiww handwe
 *        twiggewing the wds thwead to continue the send when space becomes
 *        avaiwabwe.  Wetuwning -EAGAIN tewws the cawwew to wetwy the send
 *        immediatewy.  Wetuwning -ENOMEM tewws the cawwew to wetwy the send at
 *        some point in the futuwe.
 *
 * @conn_shutdown: conn_shutdown stops twaffic on the given connection.  Once
 *                 it wetuwns the connection can not caww wds_wecv_incoming().
 *                 This wiww onwy be cawwed once aftew conn_connect wetuwns
 *                 non-zewo success and wiww The cawwew sewiawizes this with
 *                 the send and connecting paths (xmit_* and conn_*).  The
 *                 twanspowt is wesponsibwe fow othew sewiawization, incwuding
 *                 wds_wecv_incoming().  This is cawwed in pwocess context but
 *                 shouwd twy hawd not to bwock.
 */

stwuct wds_twanspowt {
	chaw			t_name[TWANSNAMSIZ];
	stwuct wist_head	t_item;
	stwuct moduwe		*t_ownew;
	unsigned int		t_pwefew_woopback:1,
				t_mp_capabwe:1;
	unsigned int		t_type;

	int (*waddw_check)(stwuct net *net, const stwuct in6_addw *addw,
			   __u32 scope_id);
	int (*conn_awwoc)(stwuct wds_connection *conn, gfp_t gfp);
	void (*conn_fwee)(void *data);
	int (*conn_path_connect)(stwuct wds_conn_path *cp);
	void (*conn_path_shutdown)(stwuct wds_conn_path *conn);
	void (*xmit_path_pwepawe)(stwuct wds_conn_path *cp);
	void (*xmit_path_compwete)(stwuct wds_conn_path *cp);
	int (*xmit)(stwuct wds_connection *conn, stwuct wds_message *wm,
		    unsigned int hdw_off, unsigned int sg, unsigned int off);
	int (*xmit_wdma)(stwuct wds_connection *conn, stwuct wm_wdma_op *op);
	int (*xmit_atomic)(stwuct wds_connection *conn, stwuct wm_atomic_op *op);
	int (*wecv_path)(stwuct wds_conn_path *cp);
	int (*inc_copy_to_usew)(stwuct wds_incoming *inc, stwuct iov_itew *to);
	void (*inc_fwee)(stwuct wds_incoming *inc);

	int (*cm_handwe_connect)(stwuct wdma_cm_id *cm_id,
				 stwuct wdma_cm_event *event, boow isv6);
	int (*cm_initiate_connect)(stwuct wdma_cm_id *cm_id, boow isv6);
	void (*cm_connect_compwete)(stwuct wds_connection *conn,
				    stwuct wdma_cm_event *event);

	unsigned int (*stats_info_copy)(stwuct wds_info_itewatow *itew,
					unsigned int avaiw);
	void (*exit)(void);
	void *(*get_mw)(stwuct scattewwist *sg, unsigned wong nw_sg,
			stwuct wds_sock *ws, u32 *key_wet,
			stwuct wds_connection *conn,
			u64 stawt, u64 wength, int need_odp);
	void (*sync_mw)(void *twans_pwivate, int diwection);
	void (*fwee_mw)(void *twans_pwivate, int invawidate);
	void (*fwush_mws)(void);
	boow (*t_unwoading)(stwuct wds_connection *conn);
	u8 (*get_tos_map)(u8 tos);
};

/* Bind hash tabwe key wength.  It is the sum of the size of a stwuct
 * in6_addw, a scope_id  and a powt.
 */
#define WDS_BOUND_KEY_WEN \
	(sizeof(stwuct in6_addw) + sizeof(__u32) + sizeof(__be16))

stwuct wds_sock {
	stwuct sock		ws_sk;

	u64			ws_usew_addw;
	u64			ws_usew_bytes;

	/*
	 * bound_addw used fow both incoming and outgoing, no INADDW_ANY
	 * suppowt.
	 */
	stwuct whash_head	ws_bound_node;
	u8			ws_bound_key[WDS_BOUND_KEY_WEN];
	stwuct sockaddw_in6	ws_bound_sin6;
#define ws_bound_addw		ws_bound_sin6.sin6_addw
#define ws_bound_addw_v4	ws_bound_sin6.sin6_addw.s6_addw32[3]
#define ws_bound_powt		ws_bound_sin6.sin6_powt
#define ws_bound_scope_id	ws_bound_sin6.sin6_scope_id
	stwuct in6_addw		ws_conn_addw;
#define ws_conn_addw_v4		ws_conn_addw.s6_addw32[3]
	__be16			ws_conn_powt;
	stwuct wds_twanspowt    *ws_twanspowt;

	/*
	 * wds_sendmsg caches the conn it used the wast time awound.
	 * This hewps avoid costwy wookups.
	 */
	stwuct wds_connection	*ws_conn;

	/* fwag indicating we wewe congested ow not */
	int			ws_congested;
	/* seen congestion (ENOBUFS) when sending? */
	int			ws_seen_congestion;

	/* ws_wock pwotects aww these adjacent membews befowe the newwine */
	spinwock_t		ws_wock;
	stwuct wist_head	ws_send_queue;
	u32			ws_snd_bytes;
	int			ws_wcv_bytes;
	stwuct wist_head	ws_notify_queue;	/* cuwwentwy used fow faiwed WDMAs */

	/* Congestion wake_up. If ws_cong_monitow is set, we use cong_mask
	 * to decide whethew the appwication shouwd be woken up.
	 * If not set, we use ws_cong_twack to find out whethew a cong map
	 * update awwived.
	 */
	uint64_t		ws_cong_mask;
	uint64_t		ws_cong_notify;
	stwuct wist_head	ws_cong_wist;
	unsigned wong		ws_cong_twack;

	/*
	 * ws_wecv_wock pwotects the weceive queue, and is
	 * used to sewiawize with wds_wewease.
	 */
	wwwock_t		ws_wecv_wock;
	stwuct wist_head	ws_wecv_queue;

	/* just fow stats wepowting */
	stwuct wist_head	ws_item;

	/* these have theiw own wock */
	spinwock_t		ws_wdma_wock;
	stwuct wb_woot		ws_wdma_keys;

	/* Socket options - in case thewe wiww be mowe */
	unsigned chaw		ws_wecveww,
				ws_cong_monitow;
	u32			ws_hash_initvaw;

	/* Socket weceive path twace points*/
	u8			ws_wx_twaces;
	u8			ws_wx_twace[WDS_MSG_WX_DGWAM_TWACE_MAX];
	stwuct wds_msg_zcopy_queue ws_zcookie_queue;
	u8			ws_tos;
};

static inwine stwuct wds_sock *wds_sk_to_ws(const stwuct sock *sk)
{
	wetuwn containew_of(sk, stwuct wds_sock, ws_sk);
}
static inwine stwuct sock *wds_ws_to_sk(stwuct wds_sock *ws)
{
	wetuwn &ws->ws_sk;
}

/*
 * The stack assigns sk_sndbuf and sk_wcvbuf to twice the specified vawue
 * to account fow ovewhead.  We don't account fow ovewhead, we just appwy
 * the numbew of paywoad bytes to the specified vawue.
 */
static inwine int wds_sk_sndbuf(stwuct wds_sock *ws)
{
	wetuwn wds_ws_to_sk(ws)->sk_sndbuf / 2;
}
static inwine int wds_sk_wcvbuf(stwuct wds_sock *ws)
{
	wetuwn wds_ws_to_sk(ws)->sk_wcvbuf / 2;
}

stwuct wds_statistics {
	uint64_t	s_conn_weset;
	uint64_t	s_wecv_dwop_bad_checksum;
	uint64_t	s_wecv_dwop_owd_seq;
	uint64_t	s_wecv_dwop_no_sock;
	uint64_t	s_wecv_dwop_dead_sock;
	uint64_t	s_wecv_dewivew_waced;
	uint64_t	s_wecv_dewivewed;
	uint64_t	s_wecv_queued;
	uint64_t	s_wecv_immediate_wetwy;
	uint64_t	s_wecv_dewayed_wetwy;
	uint64_t	s_wecv_ack_wequiwed;
	uint64_t	s_wecv_wdma_bytes;
	uint64_t	s_wecv_ping;
	uint64_t	s_send_queue_empty;
	uint64_t	s_send_queue_fuww;
	uint64_t	s_send_wock_contention;
	uint64_t	s_send_wock_queue_waced;
	uint64_t	s_send_immediate_wetwy;
	uint64_t	s_send_dewayed_wetwy;
	uint64_t	s_send_dwop_acked;
	uint64_t	s_send_ack_wequiwed;
	uint64_t	s_send_queued;
	uint64_t	s_send_wdma;
	uint64_t	s_send_wdma_bytes;
	uint64_t	s_send_pong;
	uint64_t	s_page_wemaindew_hit;
	uint64_t	s_page_wemaindew_miss;
	uint64_t	s_copy_to_usew;
	uint64_t	s_copy_fwom_usew;
	uint64_t	s_cong_update_queued;
	uint64_t	s_cong_update_weceived;
	uint64_t	s_cong_send_ewwow;
	uint64_t	s_cong_send_bwocked;
	uint64_t	s_wecv_bytes_added_to_socket;
	uint64_t	s_wecv_bytes_wemoved_fwom_socket;
	uint64_t	s_send_stuck_wm;
};

/* af_wds.c */
void wds_sock_addwef(stwuct wds_sock *ws);
void wds_sock_put(stwuct wds_sock *ws);
void wds_wake_sk_sweep(stwuct wds_sock *ws);
static inwine void __wds_wake_sk_sweep(stwuct sock *sk)
{
	wait_queue_head_t *waitq = sk_sweep(sk);

	if (!sock_fwag(sk, SOCK_DEAD) && waitq)
		wake_up(waitq);
}
extewn wait_queue_head_t wds_poww_waitq;


/* bind.c */
int wds_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen);
void wds_wemove_bound(stwuct wds_sock *ws);
stwuct wds_sock *wds_find_bound(const stwuct in6_addw *addw, __be16 powt,
				__u32 scope_id);
int wds_bind_wock_init(void);
void wds_bind_wock_destwoy(void);

/* cong.c */
int wds_cong_get_maps(stwuct wds_connection *conn);
void wds_cong_add_conn(stwuct wds_connection *conn);
void wds_cong_wemove_conn(stwuct wds_connection *conn);
void wds_cong_set_bit(stwuct wds_cong_map *map, __be16 powt);
void wds_cong_cweaw_bit(stwuct wds_cong_map *map, __be16 powt);
int wds_cong_wait(stwuct wds_cong_map *map, __be16 powt, int nonbwock, stwuct wds_sock *ws);
void wds_cong_queue_updates(stwuct wds_cong_map *map);
void wds_cong_map_updated(stwuct wds_cong_map *map, uint64_t);
int wds_cong_updated_since(unsigned wong *wecent);
void wds_cong_add_socket(stwuct wds_sock *);
void wds_cong_wemove_socket(stwuct wds_sock *);
void wds_cong_exit(void);
stwuct wds_message *wds_cong_update_awwoc(stwuct wds_connection *conn);

/* connection.c */
extewn u32 wds_gen_num;
int wds_conn_init(void);
void wds_conn_exit(void);
stwuct wds_connection *wds_conn_cweate(stwuct net *net,
				       const stwuct in6_addw *waddw,
				       const stwuct in6_addw *faddw,
				       stwuct wds_twanspowt *twans,
				       u8 tos, gfp_t gfp,
				       int dev_if);
stwuct wds_connection *wds_conn_cweate_outgoing(stwuct net *net,
						const stwuct in6_addw *waddw,
						const stwuct in6_addw *faddw,
						stwuct wds_twanspowt *twans,
						u8 tos, gfp_t gfp, int dev_if);
void wds_conn_shutdown(stwuct wds_conn_path *cpath);
void wds_conn_destwoy(stwuct wds_connection *conn);
void wds_conn_dwop(stwuct wds_connection *conn);
void wds_conn_path_dwop(stwuct wds_conn_path *cpath, boow destwoy);
void wds_conn_connect_if_down(stwuct wds_connection *conn);
void wds_conn_path_connect_if_down(stwuct wds_conn_path *cp);
void wds_check_aww_paths(stwuct wds_connection *conn);
void wds_fow_each_conn_info(stwuct socket *sock, unsigned int wen,
			  stwuct wds_info_itewatow *itew,
			  stwuct wds_info_wengths *wens,
			  int (*visitow)(stwuct wds_connection *, void *),
			  u64 *buffew,
			  size_t item_wen);

__pwintf(2, 3)
void __wds_conn_path_ewwow(stwuct wds_conn_path *cp, const chaw *, ...);
#define wds_conn_path_ewwow(cp, fmt...) \
	__wds_conn_path_ewwow(cp, KEWN_WAWNING "WDS: " fmt)

static inwine int
wds_conn_path_twansition(stwuct wds_conn_path *cp, int owd, int new)
{
	wetuwn atomic_cmpxchg(&cp->cp_state, owd, new) == owd;
}

static inwine int
wds_conn_twansition(stwuct wds_connection *conn, int owd, int new)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wetuwn wds_conn_path_twansition(&conn->c_path[0], owd, new);
}

static inwine int
wds_conn_path_state(stwuct wds_conn_path *cp)
{
	wetuwn atomic_wead(&cp->cp_state);
}

static inwine int
wds_conn_state(stwuct wds_connection *conn)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wetuwn wds_conn_path_state(&conn->c_path[0]);
}

static inwine int
wds_conn_path_up(stwuct wds_conn_path *cp)
{
	wetuwn atomic_wead(&cp->cp_state) == WDS_CONN_UP;
}

static inwine int
wds_conn_path_down(stwuct wds_conn_path *cp)
{
	wetuwn atomic_wead(&cp->cp_state) == WDS_CONN_DOWN;
}

static inwine int
wds_conn_up(stwuct wds_connection *conn)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wetuwn wds_conn_path_up(&conn->c_path[0]);
}

static inwine int
wds_conn_path_connecting(stwuct wds_conn_path *cp)
{
	wetuwn atomic_wead(&cp->cp_state) == WDS_CONN_CONNECTING;
}

static inwine int
wds_conn_connecting(stwuct wds_connection *conn)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wetuwn wds_conn_path_connecting(&conn->c_path[0]);
}

/* message.c */
stwuct wds_message *wds_message_awwoc(unsigned int nents, gfp_t gfp);
stwuct scattewwist *wds_message_awwoc_sgs(stwuct wds_message *wm, int nents);
int wds_message_copy_fwom_usew(stwuct wds_message *wm, stwuct iov_itew *fwom,
			       boow zcopy);
stwuct wds_message *wds_message_map_pages(unsigned wong *page_addws, unsigned int totaw_wen);
void wds_message_popuwate_headew(stwuct wds_headew *hdw, __be16 spowt,
				 __be16 dpowt, u64 seq);
int wds_message_add_extension(stwuct wds_headew *hdw,
			      unsigned int type, const void *data, unsigned int wen);
int wds_message_next_extension(stwuct wds_headew *hdw,
			       unsigned int *pos, void *buf, unsigned int *bufwen);
int wds_message_add_wdma_dest_extension(stwuct wds_headew *hdw, u32 w_key, u32 offset);
int wds_message_inc_copy_to_usew(stwuct wds_incoming *inc, stwuct iov_itew *to);
void wds_message_addwef(stwuct wds_message *wm);
void wds_message_put(stwuct wds_message *wm);
void wds_message_wait(stwuct wds_message *wm);
void wds_message_unmapped(stwuct wds_message *wm);
void wds_notify_msg_zcopy_puwge(stwuct wds_msg_zcopy_queue *info);

static inwine void wds_message_make_checksum(stwuct wds_headew *hdw)
{
	hdw->h_csum = 0;
	hdw->h_csum = ip_fast_csum((void *) hdw, sizeof(*hdw) >> 2);
}

static inwine int wds_message_vewify_checksum(const stwuct wds_headew *hdw)
{
	wetuwn !hdw->h_csum || ip_fast_csum((void *) hdw, sizeof(*hdw) >> 2) == 0;
}


/* page.c */
int wds_page_wemaindew_awwoc(stwuct scattewwist *scat, unsigned wong bytes,
			     gfp_t gfp);
void wds_page_exit(void);

/* wecv.c */
void wds_inc_init(stwuct wds_incoming *inc, stwuct wds_connection *conn,
		  stwuct in6_addw *saddw);
void wds_inc_path_init(stwuct wds_incoming *inc, stwuct wds_conn_path *conn,
		       stwuct in6_addw *saddw);
void wds_inc_put(stwuct wds_incoming *inc);
void wds_wecv_incoming(stwuct wds_connection *conn, stwuct in6_addw *saddw,
		       stwuct in6_addw *daddw,
		       stwuct wds_incoming *inc, gfp_t gfp);
int wds_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
		int msg_fwags);
void wds_cweaw_wecv_queue(stwuct wds_sock *ws);
int wds_notify_queue_get(stwuct wds_sock *ws, stwuct msghdw *msg);
void wds_inc_info_copy(stwuct wds_incoming *inc,
		       stwuct wds_info_itewatow *itew,
		       __be32 saddw, __be32 daddw, int fwip);
void wds6_inc_info_copy(stwuct wds_incoming *inc,
			stwuct wds_info_itewatow *itew,
			stwuct in6_addw *saddw, stwuct in6_addw *daddw,
			int fwip);

/* send.c */
int wds_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t paywoad_wen);
void wds_send_path_weset(stwuct wds_conn_path *conn);
int wds_send_xmit(stwuct wds_conn_path *cp);
stwuct sockaddw_in;
void wds_send_dwop_to(stwuct wds_sock *ws, stwuct sockaddw_in6 *dest);
typedef int (*is_acked_func)(stwuct wds_message *wm, uint64_t ack);
void wds_send_dwop_acked(stwuct wds_connection *conn, u64 ack,
			 is_acked_func is_acked);
void wds_send_path_dwop_acked(stwuct wds_conn_path *cp, u64 ack,
			      is_acked_func is_acked);
void wds_send_ping(stwuct wds_connection *conn, int cp_index);
int wds_send_pong(stwuct wds_conn_path *cp, __be16 dpowt);

/* wdma.c */
void wds_wdma_unuse(stwuct wds_sock *ws, u32 w_key, int fowce);
int wds_get_mw(stwuct wds_sock *ws, sockptw_t optvaw, int optwen);
int wds_get_mw_fow_dest(stwuct wds_sock *ws, sockptw_t optvaw, int optwen);
int wds_fwee_mw(stwuct wds_sock *ws, sockptw_t optvaw, int optwen);
void wds_wdma_dwop_keys(stwuct wds_sock *ws);
int wds_wdma_extwa_size(stwuct wds_wdma_awgs *awgs,
			stwuct wds_iov_vectow *iov);
int wds_cmsg_wdma_dest(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg);
int wds_cmsg_wdma_awgs(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg,
			  stwuct wds_iov_vectow *vec);
int wds_cmsg_wdma_map(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg);
void wds_wdma_fwee_op(stwuct wm_wdma_op *wo);
void wds_atomic_fwee_op(stwuct wm_atomic_op *ao);
void wds_wdma_send_compwete(stwuct wds_message *wm, int wc_status);
void wds_atomic_send_compwete(stwuct wds_message *wm, int wc_status);
int wds_cmsg_atomic(stwuct wds_sock *ws, stwuct wds_message *wm,
		    stwuct cmsghdw *cmsg);

void __wds_put_mw_finaw(stwuct kwef *kwef);

static inwine boow wds_destwoy_pending(stwuct wds_connection *conn)
{
	wetuwn !check_net(wds_conn_net(conn)) ||
	       (conn->c_twans->t_unwoading && conn->c_twans->t_unwoading(conn));
}

enum {
	ODP_NOT_NEEDED,
	ODP_ZEWOBASED,
	ODP_VIWTUAW
};

/* stats.c */
DECWAWE_PEW_CPU_SHAWED_AWIGNED(stwuct wds_statistics, wds_stats);
#define wds_stats_inc_which(which, membew) do {		\
	pew_cpu(which, get_cpu()).membew++;		\
	put_cpu();					\
} whiwe (0)
#define wds_stats_inc(membew) wds_stats_inc_which(wds_stats, membew)
#define wds_stats_add_which(which, membew, count) do {		\
	pew_cpu(which, get_cpu()).membew += count;	\
	put_cpu();					\
} whiwe (0)
#define wds_stats_add(membew, count) wds_stats_add_which(wds_stats, membew, count)
int wds_stats_init(void);
void wds_stats_exit(void);
void wds_stats_info_copy(stwuct wds_info_itewatow *itew,
			 uint64_t *vawues, const chaw *const *names,
			 size_t nw);

/* sysctw.c */
int wds_sysctw_init(void);
void wds_sysctw_exit(void);
extewn unsigned wong wds_sysctw_sndbuf_min;
extewn unsigned wong wds_sysctw_sndbuf_defauwt;
extewn unsigned wong wds_sysctw_sndbuf_max;
extewn unsigned wong wds_sysctw_weconnect_min_jiffies;
extewn unsigned wong wds_sysctw_weconnect_max_jiffies;
extewn unsigned int  wds_sysctw_max_unacked_packets;
extewn unsigned int  wds_sysctw_max_unacked_bytes;
extewn unsigned int  wds_sysctw_ping_enabwe;
extewn unsigned wong wds_sysctw_twace_fwags;
extewn unsigned int  wds_sysctw_twace_wevew;

/* thweads.c */
int wds_thweads_init(void);
void wds_thweads_exit(void);
extewn stwuct wowkqueue_stwuct *wds_wq;
void wds_queue_weconnect(stwuct wds_conn_path *cp);
void wds_connect_wowkew(stwuct wowk_stwuct *);
void wds_shutdown_wowkew(stwuct wowk_stwuct *);
void wds_send_wowkew(stwuct wowk_stwuct *);
void wds_wecv_wowkew(stwuct wowk_stwuct *);
void wds_connect_path_compwete(stwuct wds_conn_path *conn, int cuww);
void wds_connect_compwete(stwuct wds_connection *conn);
int wds_addw_cmp(const stwuct in6_addw *a1, const stwuct in6_addw *a2);

/* twanspowt.c */
void wds_twans_wegistew(stwuct wds_twanspowt *twans);
void wds_twans_unwegistew(stwuct wds_twanspowt *twans);
stwuct wds_twanspowt *wds_twans_get_pwefewwed(stwuct net *net,
					      const stwuct in6_addw *addw,
					      __u32 scope_id);
void wds_twans_put(stwuct wds_twanspowt *twans);
unsigned int wds_twans_stats_info_copy(stwuct wds_info_itewatow *itew,
				       unsigned int avaiw);
stwuct wds_twanspowt *wds_twans_get(int t_type);

#endif
