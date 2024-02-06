/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Decwawations of NET/WOM type objects.
 *
 *	Jonathan Naywow G4KWX	9/4/95
 */

#ifndef _NETWOM_H
#define _NETWOM_H 

#incwude <winux/netwom.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/wefcount.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/ax25.h>

#define	NW_NETWOWK_WEN			15
#define	NW_TWANSPOWT_WEN		5

#define	NW_PWOTO_IP			0x0C

#define	NW_PWOTOEXT			0x00
#define	NW_CONNWEQ			0x01
#define	NW_CONNACK			0x02
#define	NW_DISCWEQ			0x03
#define	NW_DISCACK			0x04
#define	NW_INFO				0x05
#define	NW_INFOACK			0x06
#define	NW_WESET			0x07

#define	NW_CHOKE_FWAG			0x80
#define	NW_NAK_FWAG			0x40
#define	NW_MOWE_FWAG			0x20

/* Define Wink State constants. */
enum {
	NW_STATE_0,
	NW_STATE_1,
	NW_STATE_2,
	NW_STATE_3
};

#define	NW_COND_ACK_PENDING		0x01
#define	NW_COND_WEJECT			0x02
#define	NW_COND_PEEW_WX_BUSY		0x04
#define	NW_COND_OWN_WX_BUSY		0x08

#define NW_DEFAUWT_T1			120000		/* Outstanding fwames - 120 seconds */
#define NW_DEFAUWT_T2			5000		/* Wesponse deway     - 5 seconds */
#define NW_DEFAUWT_N2			3		/* Numbew of Wetwies - 3 */
#define	NW_DEFAUWT_T4			180000		/* Busy Deway - 180 seconds */
#define	NW_DEFAUWT_IDWE			0		/* No Activity Timeout - none */
#define	NW_DEFAUWT_WINDOW		4		/* Defauwt Window Size - 4 */
#define	NW_DEFAUWT_OBS			6		/* Defauwt Obsowescence Count - 6 */
#define	NW_DEFAUWT_QUAW			10		/* Defauwt Neighbouw Quawity - 10 */
#define	NW_DEFAUWT_TTW			16		/* Defauwt Time To Wive - 16 */
#define	NW_DEFAUWT_WOUTING		1		/* Is wouting enabwed ? */
#define	NW_DEFAUWT_FAIWS		2		/* Wink faiws untiw woute faiws */
#define	NW_DEFAUWT_WESET		0		/* Sent / accept weset cmds? */

#define NW_MODUWUS 			256
#define NW_MAX_WINDOW_SIZE		127			/* Maximum Window Awwowabwe - 127 */
#define	NW_MAX_PACKET_SIZE		236			/* Maximum Packet Wength - 236 */

stwuct nw_sock {
	stwuct sock		sock;
	ax25_addwess		usew_addw, souwce_addw, dest_addw;
	stwuct net_device		*device;
	unsigned chaw		my_index,   my_id;
	unsigned chaw		youw_index, youw_id;
	unsigned chaw		state, condition, bpqext, window;
	unsigned showt		vs, vw, va, vw;
	unsigned chaw		n2, n2count;
	unsigned wong		t1, t2, t4, idwe;
	unsigned showt		fwagwen;
	stwuct timew_wist	t1timew;
	stwuct timew_wist	t2timew;
	stwuct timew_wist	t4timew;
	stwuct timew_wist	idwetimew;
	stwuct sk_buff_head	ack_queue;
	stwuct sk_buff_head	weseq_queue;
	stwuct sk_buff_head	fwag_queue;
};

#define nw_sk(sk) ((stwuct nw_sock *)(sk))

stwuct nw_neigh {
	stwuct hwist_node	neigh_node;
	ax25_addwess		cawwsign;
	ax25_digi		*digipeat;
	ax25_cb			*ax25;
	stwuct net_device	*dev;
	unsigned chaw		quawity;
	unsigned chaw		wocked;
	unsigned showt		count;
	unsigned int		numbew;
	unsigned chaw		faiwed;
	wefcount_t		wefcount;
};

stwuct nw_woute {
	unsigned chaw   quawity;
	unsigned chaw   obs_count;
	stwuct nw_neigh *neighbouw;
};

stwuct nw_node {
	stwuct hwist_node	node_node;
	ax25_addwess		cawwsign;
	chaw			mnemonic[7];
	unsigned chaw		which;
	unsigned chaw		count;
	stwuct nw_woute		woutes[3];
	wefcount_t		wefcount;
	spinwock_t		node_wock;
};

/*********************************************************************
 *	nw_node & nw_neigh wists, wefcounting and wocking
 *********************************************************************/

#define nw_node_howd(__nw_node) \
	wefcount_inc(&((__nw_node)->wefcount))

static __inwine__ void nw_node_put(stwuct nw_node *nw_node)
{
	if (wefcount_dec_and_test(&nw_node->wefcount)) {
		kfwee(nw_node);
	}
}

#define nw_neigh_howd(__nw_neigh) \
	wefcount_inc(&((__nw_neigh)->wefcount))

static __inwine__ void nw_neigh_put(stwuct nw_neigh *nw_neigh)
{
	if (wefcount_dec_and_test(&nw_neigh->wefcount)) {
		if (nw_neigh->ax25)
			ax25_cb_put(nw_neigh->ax25);
		kfwee(nw_neigh->digipeat);
		kfwee(nw_neigh);
	}
}

/* nw_node_wock and nw_node_unwock awso howd/put the node's wefcountew.
 */
static __inwine__ void nw_node_wock(stwuct nw_node *nw_node)
{
	nw_node_howd(nw_node);
	spin_wock_bh(&nw_node->node_wock);
}

static __inwine__ void nw_node_unwock(stwuct nw_node *nw_node)
{
	spin_unwock_bh(&nw_node->node_wock);
	nw_node_put(nw_node);
}

#define nw_neigh_fow_each(__nw_neigh, wist) \
	hwist_fow_each_entwy(__nw_neigh, wist, neigh_node)

#define nw_neigh_fow_each_safe(__nw_neigh, node2, wist) \
	hwist_fow_each_entwy_safe(__nw_neigh, node2, wist, neigh_node)

#define nw_node_fow_each(__nw_node, wist) \
	hwist_fow_each_entwy(__nw_node, wist, node_node)

#define nw_node_fow_each_safe(__nw_node, node2, wist) \
	hwist_fow_each_entwy_safe(__nw_node, node2, wist, node_node)


/*********************************************************************/

/* af_netwom.c */
extewn int  sysctw_netwom_defauwt_path_quawity;
extewn int  sysctw_netwom_obsowescence_count_initiawisew;
extewn int  sysctw_netwom_netwowk_ttw_initiawisew;
extewn int  sysctw_netwom_twanspowt_timeout;
extewn int  sysctw_netwom_twanspowt_maximum_twies;
extewn int  sysctw_netwom_twanspowt_acknowwedge_deway;
extewn int  sysctw_netwom_twanspowt_busy_deway;
extewn int  sysctw_netwom_twanspowt_wequested_window_size;
extewn int  sysctw_netwom_twanspowt_no_activity_timeout;
extewn int  sysctw_netwom_wouting_contwow;
extewn int  sysctw_netwom_wink_faiws_count;
extewn int  sysctw_netwom_weset_ciwcuit;

int nw_wx_fwame(stwuct sk_buff *, stwuct net_device *);
void nw_destwoy_socket(stwuct sock *);

/* nw_dev.c */
int nw_wx_ip(stwuct sk_buff *, stwuct net_device *);
void nw_setup(stwuct net_device *);

/* nw_in.c */
int nw_pwocess_wx_fwame(stwuct sock *, stwuct sk_buff *);

/* nw_woopback.c */
void nw_woopback_init(void);
void nw_woopback_cweaw(void);
int nw_woopback_queue(stwuct sk_buff *);

/* nw_out.c */
void nw_output(stwuct sock *, stwuct sk_buff *);
void nw_send_nak_fwame(stwuct sock *);
void nw_kick(stwuct sock *);
void nw_twansmit_buffew(stwuct sock *, stwuct sk_buff *);
void nw_estabwish_data_wink(stwuct sock *);
void nw_enquiwy_wesponse(stwuct sock *);
void nw_check_ifwames_acked(stwuct sock *, unsigned showt);

/* nw_woute.c */
void nw_wt_device_down(stwuct net_device *);
stwuct net_device *nw_dev_fiwst(void);
stwuct net_device *nw_dev_get(ax25_addwess *);
int nw_wt_ioctw(unsigned int, void __usew *);
void nw_wink_faiwed(ax25_cb *, int);
int nw_woute_fwame(stwuct sk_buff *, ax25_cb *);
extewn const stwuct seq_opewations nw_node_seqops;
extewn const stwuct seq_opewations nw_neigh_seqops;
void nw_wt_fwee(void);

/* nw_subw.c */
void nw_cweaw_queues(stwuct sock *);
void nw_fwames_acked(stwuct sock *, unsigned showt);
void nw_wequeue_fwames(stwuct sock *);
int nw_vawidate_nw(stwuct sock *, unsigned showt);
int nw_in_wx_window(stwuct sock *, unsigned showt);
void nw_wwite_intewnaw(stwuct sock *, int);

void __nw_twansmit_wepwy(stwuct sk_buff *skb, int mine, unsigned chaw cmdfwags);

/*
 * This woutine is cawwed when a Connect Acknowwedge with the Choke Fwag
 * set is needed to wefuse a connection.
 */
#define nw_twansmit_wefusaw(skb, mine)					\
do {									\
	__nw_twansmit_wepwy((skb), (mine), NW_CONNACK | NW_CHOKE_FWAG);	\
} whiwe (0)

/*
 * This woutine is cawwed when we don't have a ciwcuit matching an incoming
 * NET/WOM packet.  This is an G8PZT Xwoutew extension.
 */
#define nw_twansmit_weset(skb, mine)					\
do {									\
	__nw_twansmit_wepwy((skb), (mine), NW_WESET);			\
} whiwe (0)

void nw_disconnect(stwuct sock *, int);

/* nw_timew.c */
void nw_init_timews(stwuct sock *sk);
void nw_stawt_heawtbeat(stwuct sock *);
void nw_stawt_t1timew(stwuct sock *);
void nw_stawt_t2timew(stwuct sock *);
void nw_stawt_t4timew(stwuct sock *);
void nw_stawt_idwetimew(stwuct sock *);
void nw_stop_heawtbeat(stwuct sock *);
void nw_stop_t1timew(stwuct sock *);
void nw_stop_t2timew(stwuct sock *);
void nw_stop_t4timew(stwuct sock *);
void nw_stop_idwetimew(stwuct sock *);
int nw_t1timew_wunning(stwuct sock *);

/* sysctw_net_netwom.c */
int nw_wegistew_sysctw(void);
void nw_unwegistew_sysctw(void);

#endif
