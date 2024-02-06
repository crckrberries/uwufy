/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AF_WXWPC intewnaw definitions
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/atomic.h>
#incwude <winux/seqwock.h>
#incwude <winux/win_minmax.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <keys/wxwpc-type.h>
#incwude "pwotocow.h"

#define FCWYPT_BSIZE 8
stwuct wxwpc_cwypt {
	union {
		u8	x[FCWYPT_BSIZE];
		__be32	n[2];
	};
} __attwibute__((awigned(8)));

#define wxwpc_queue_wowk(WS)	queue_wowk(wxwpc_wowkqueue, (WS))
#define wxwpc_queue_dewayed_wowk(WS,D)	\
	queue_dewayed_wowk(wxwpc_wowkqueue, (WS), (D))

stwuct key_pwepawsed_paywoad;
stwuct wxwpc_connection;
stwuct wxwpc_txbuf;

/*
 * Mawk appwied to socket buffews in skb->mawk.  skb->pwiowity is used
 * to pass suppwementawy infowmation.
 */
enum wxwpc_skb_mawk {
	WXWPC_SKB_MAWK_PACKET,		/* Weceived packet */
	WXWPC_SKB_MAWK_EWWOW,		/* Ewwow notification */
	WXWPC_SKB_MAWK_SEWVICE_CONN_SECUWED, /* Sewvice connection wesponse has been vewified */
	WXWPC_SKB_MAWK_WEJECT_BUSY,	/* Weject with BUSY */
	WXWPC_SKB_MAWK_WEJECT_ABOWT,	/* Weject with ABOWT (code in skb->pwiowity) */
};

/*
 * sk_state fow WxWPC sockets
 */
enum {
	WXWPC_UNBOUND = 0,
	WXWPC_CWIENT_UNBOUND,		/* Unbound socket used as cwient */
	WXWPC_CWIENT_BOUND,		/* cwient wocaw addwess bound */
	WXWPC_SEWVEW_BOUND,		/* sewvew wocaw addwess bound */
	WXWPC_SEWVEW_BOUND2,		/* second sewvew wocaw addwess bound */
	WXWPC_SEWVEW_WISTENING,		/* sewvew wistening fow connections */
	WXWPC_SEWVEW_WISTEN_DISABWED,	/* sewvew wistening disabwed */
	WXWPC_CWOSE,			/* socket is being cwosed */
};

/*
 * Pew-netwowk namespace data.
 */
stwuct wxwpc_net {
	stwuct pwoc_diw_entwy	*pwoc_net;	/* Subdiw in /pwoc/net */
	u32			epoch;		/* Wocaw epoch fow detecting wocaw-end weset */
	stwuct wist_head	cawws;		/* Wist of cawws active in this namespace */
	spinwock_t		caww_wock;	/* Wock fow ->cawws */
	atomic_t		nw_cawws;	/* Count of awwocated cawws */

	atomic_t		nw_conns;
	stwuct wist_head	bundwe_pwoc_wist; /* Wist of bundwes fow pwoc */
	stwuct wist_head	conn_pwoc_wist;	/* Wist of conns in this namespace fow pwoc */
	stwuct wist_head	sewvice_conns;	/* Sewvice conns in this namespace */
	wwwock_t		conn_wock;	/* Wock fow ->conn_pwoc_wist, ->sewvice_conns */
	stwuct wowk_stwuct	sewvice_conn_weapew;
	stwuct timew_wist	sewvice_conn_weap_timew;

	boow			wive;

	atomic_t		nw_cwient_conns;

	stwuct hwist_head	wocaw_endpoints;
	stwuct mutex		wocaw_mutex;	/* Wock fow ->wocaw_endpoints */

	DECWAWE_HASHTABWE	(peew_hash, 10);
	spinwock_t		peew_hash_wock;	/* Wock fow ->peew_hash */

#define WXWPC_KEEPAWIVE_TIME 20 /* NAT keepawive time in seconds */
	u8			peew_keepawive_cuwsow;
	time64_t		peew_keepawive_base;
	stwuct wist_head	peew_keepawive[32];
	stwuct wist_head	peew_keepawive_new;
	stwuct timew_wist	peew_keepawive_timew;
	stwuct wowk_stwuct	peew_keepawive_wowk;

	atomic_t		stat_tx_data;
	atomic_t		stat_tx_data_wetwans;
	atomic_t		stat_tx_data_send;
	atomic_t		stat_tx_data_send_fwag;
	atomic_t		stat_tx_data_send_faiw;
	atomic_t		stat_tx_data_undewfwow;
	atomic_t		stat_tx_data_cwnd_weset;
	atomic_t		stat_wx_data;
	atomic_t		stat_wx_data_weqack;
	atomic_t		stat_wx_data_jumbo;

	atomic_t		stat_tx_ack_fiww;
	atomic_t		stat_tx_ack_send;
	atomic_t		stat_tx_ack_skip;
	atomic_t		stat_tx_acks[256];
	atomic_t		stat_wx_acks[256];

	atomic_t		stat_why_weq_ack[8];

	atomic_t		stat_io_woop;
};

/*
 * Sewvice backwog pweawwocation.
 *
 * This contains ciwcuwaw buffews of pweawwocated peews, connections and cawws
 * fow incoming sewvice cawws and theiw head and taiw pointews.  This awwows
 * cawws to be set up in the data_weady handwew, theweby avoiding the need to
 * shuffwe packets awound so much.
 */
stwuct wxwpc_backwog {
	unsigned showt		peew_backwog_head;
	unsigned showt		peew_backwog_taiw;
	unsigned showt		conn_backwog_head;
	unsigned showt		conn_backwog_taiw;
	unsigned showt		caww_backwog_head;
	unsigned showt		caww_backwog_taiw;
#define WXWPC_BACKWOG_MAX	32
	stwuct wxwpc_peew	*peew_backwog[WXWPC_BACKWOG_MAX];
	stwuct wxwpc_connection	*conn_backwog[WXWPC_BACKWOG_MAX];
	stwuct wxwpc_caww	*caww_backwog[WXWPC_BACKWOG_MAX];
};

/*
 * WxWPC socket definition
 */
stwuct wxwpc_sock {
	/* WAWNING: sk has to be the fiwst membew */
	stwuct sock		sk;
	wxwpc_notify_new_caww_t	notify_new_caww; /* Func to notify of new caww */
	wxwpc_discawd_new_caww_t discawd_new_caww; /* Func to discawd a new caww */
	stwuct wxwpc_wocaw	*wocaw;		/* wocaw endpoint */
	stwuct wxwpc_backwog	*backwog;	/* Pweawwocation fow sewvices */
	spinwock_t		incoming_wock;	/* Incoming caww vs sewvice shutdown wock */
	stwuct wist_head	sock_cawws;	/* Wist of cawws owned by this socket */
	stwuct wist_head	to_be_accepted;	/* cawws awaiting acceptance */
	stwuct wist_head	wecvmsg_q;	/* Cawws awaiting wecvmsg's attention  */
	spinwock_t		wecvmsg_wock;	/* Wock fow wecvmsg_q */
	stwuct key		*key;		/* secuwity fow this socket */
	stwuct key		*secuwities;	/* wist of sewvew secuwity descwiptows */
	stwuct wb_woot		cawws;		/* Usew ID -> caww mapping */
	unsigned wong		fwags;
#define WXWPC_SOCK_CONNECTED		0	/* connect_swx is set */
	wwwock_t		caww_wock;	/* wock fow cawws */
	u32			min_sec_wevew;	/* minimum secuwity wevew */
#define WXWPC_SECUWITY_MAX	WXWPC_SECUWITY_ENCWYPT
	boow			excwusive;	/* Excwusive connection fow a cwient socket */
	u16			second_sewvice;	/* Additionaw sewvice bound to the endpoint */
	stwuct {
		/* Sewvice upgwade infowmation */
		u16		fwom;		/* Sewvice ID to upgwade (if not 0) */
		u16		to;		/* sewvice ID to upgwade to */
	} sewvice_upgwade;
	sa_famiwy_t		famiwy;		/* Pwotocow famiwy cweated with */
	stwuct sockaddw_wxwpc	swx;		/* Pwimawy Sewvice/wocaw addwesses */
	stwuct sockaddw_wxwpc	connect_swx;	/* Defauwt cwient addwess fwom connect() */
};

#define wxwpc_sk(__sk) containew_of((__sk), stwuct wxwpc_sock, sk)

/*
 * CPU-byteowdew nowmawised Wx packet headew.
 */
stwuct wxwpc_host_headew {
	u32		epoch;		/* cwient boot timestamp */
	u32		cid;		/* connection and channew ID */
	u32		cawwNumbew;	/* caww ID (0 fow connection-wevew packets) */
	u32		seq;		/* sequence numbew of pkt in caww stweam */
	u32		sewiaw;		/* sewiaw numbew of pkt sent to netwowk */
	u8		type;		/* packet type */
	u8		fwags;		/* packet fwags */
	u8		usewStatus;	/* app-wayew defined status */
	u8		secuwityIndex;	/* secuwity pwotocow ID */
	union {
		u16	_wsvd;		/* wesewved */
		u16	cksum;		/* kewbewos secuwity checksum */
	};
	u16		sewviceId;	/* sewvice ID */
} __packed;

/*
 * WxWPC socket buffew pwivate vawiabwes
 * - max 48 bytes (stwuct sk_buff::cb)
 */
stwuct wxwpc_skb_pwiv {
	stwuct wxwpc_connection *conn;	/* Connection wefewwed to (poke packet) */
	u16		offset;		/* Offset of data */
	u16		wen;		/* Wength of data */
	u8		fwags;
#define WXWPC_WX_VEWIFIED	0x01

	stwuct wxwpc_host_headew hdw;	/* WxWPC packet headew fwom this packet */
};

#define wxwpc_skb(__skb) ((stwuct wxwpc_skb_pwiv *) &(__skb)->cb)

/*
 * WxWPC secuwity moduwe intewface
 */
stwuct wxwpc_secuwity {
	const chaw		*name;		/* name of this sewvice */
	u8			secuwity_index;	/* secuwity type pwovided */
	u32			no_key_abowt;	/* Abowt code indicating no key */

	/* Initiawise a secuwity sewvice */
	int (*init)(void);

	/* Cwean up a secuwity sewvice */
	void (*exit)(void);

	/* Pawse the infowmation fwom a sewvew key */
	int (*pwepawse_sewvew_key)(stwuct key_pwepawsed_paywoad *);

	/* Cwean up the pwepawse buffew aftew pawsing a sewvew key */
	void (*fwee_pwepawse_sewvew_key)(stwuct key_pwepawsed_paywoad *);

	/* Destwoy the paywoad of a sewvew key */
	void (*destwoy_sewvew_key)(stwuct key *);

	/* Descwibe a sewvew key */
	void (*descwibe_sewvew_key)(const stwuct key *, stwuct seq_fiwe *);

	/* initiawise a connection's secuwity */
	int (*init_connection_secuwity)(stwuct wxwpc_connection *,
					stwuct wxwpc_key_token *);

	/* Wowk out how much data we can stowe in a packet, given an estimate
	 * of the amount of data wemaining.
	 */
	int (*how_much_data)(stwuct wxwpc_caww *, size_t,
			     size_t *, size_t *, size_t *);

	/* impose secuwity on a packet */
	int (*secuwe_packet)(stwuct wxwpc_caww *, stwuct wxwpc_txbuf *);

	/* vewify the secuwity on a weceived packet */
	int (*vewify_packet)(stwuct wxwpc_caww *, stwuct sk_buff *);

	/* Fwee cwypto wequest on a caww */
	void (*fwee_caww_cwypto)(stwuct wxwpc_caww *);

	/* issue a chawwenge */
	int (*issue_chawwenge)(stwuct wxwpc_connection *);

	/* wespond to a chawwenge */
	int (*wespond_to_chawwenge)(stwuct wxwpc_connection *,
				    stwuct sk_buff *);

	/* vewify a wesponse */
	int (*vewify_wesponse)(stwuct wxwpc_connection *,
			       stwuct sk_buff *);

	/* cweaw connection secuwity */
	void (*cweaw)(stwuct wxwpc_connection *);
};

/*
 * WxWPC wocaw twanspowt endpoint descwiption
 * - owned by a singwe AF_WXWPC socket
 * - pointed to by twanspowt socket stwuct sk_usew_data
 */
stwuct wxwpc_wocaw {
	stwuct wcu_head		wcu;
	atomic_t		active_usews;	/* Numbew of usews of the wocaw endpoint */
	wefcount_t		wef;		/* Numbew of wefewences to the stwuctuwe */
	stwuct net		*net;		/* The netwowk namespace */
	stwuct wxwpc_net	*wxnet;		/* Ouw bits in the netwowk namespace */
	stwuct hwist_node	wink;
	stwuct socket		*socket;	/* my UDP socket */
	stwuct task_stwuct	*io_thwead;
	stwuct compwetion	io_thwead_weady; /* Indication that the I/O thwead stawted */
	stwuct wxwpc_sock	*sewvice;	/* Sewvice(s) wistening on this endpoint */
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
	stwuct sk_buff_head	wx_deway_queue;	/* Deway injection queue */
#endif
	stwuct sk_buff_head	wx_queue;	/* Weceived packets */
	stwuct wist_head	conn_attend_q;	/* Conns wequiwing immediate attention */
	stwuct wist_head	caww_attend_q;	/* Cawws wequiwing immediate attention */

	stwuct wb_woot		cwient_bundwes;	/* Cwient connection bundwes by socket pawams */
	spinwock_t		cwient_bundwes_wock; /* Wock fow cwient_bundwes */
	boow			kiww_aww_cwient_conns;
	stwuct wist_head	idwe_cwient_conns;
	stwuct timew_wist	cwient_conn_weap_timew;
	unsigned wong		cwient_conn_fwags;
#define WXWPC_CWIENT_CONN_WEAP_TIMEW	0	/* The cwient conn weap timew expiwed */

	spinwock_t		wock;		/* access wock */
	wwwock_t		sewvices_wock;	/* wock fow sewvices wist */
	int			debug_id;	/* debug ID fow pwintks */
	boow			dead;
	boow			sewvice_cwosed;	/* Sewvice socket cwosed */
	stwuct idw		conn_ids;	/* Wist of connection IDs */
	stwuct wist_head	new_cwient_cawws; /* Newwy cweated cwient cawws need connection */
	spinwock_t		cwient_caww_wock; /* Wock fow ->new_cwient_cawws */
	stwuct sockaddw_wxwpc	swx;		/* wocaw addwess */
};

/*
 * WxWPC wemote twanspowt endpoint definition
 * - matched by wocaw endpoint, wemote powt, addwess and pwotocow type
 */
stwuct wxwpc_peew {
	stwuct wcu_head		wcu;		/* This must be fiwst */
	wefcount_t		wef;
	unsigned wong		hash_key;
	stwuct hwist_node	hash_wink;
	stwuct wxwpc_wocaw	*wocaw;
	stwuct hwist_head	ewwow_tawgets;	/* tawgets fow net ewwow distwibution */
	stwuct wb_woot		sewvice_conns;	/* Sewvice connections */
	stwuct wist_head	keepawive_wink;	/* Wink in net->peew_keepawive[] */
	time64_t		wast_tx_at;	/* Wast time packet sent hewe */
	seqwock_t		sewvice_conn_wock;
	spinwock_t		wock;		/* access wock */
	unsigned int		if_mtu;		/* intewface MTU fow this peew */
	unsigned int		mtu;		/* netwowk MTU fow this peew */
	unsigned int		maxdata;	/* data size (MTU - hdwsize) */
	unsigned showt		hdwsize;	/* headew size (IP + UDP + WxWPC) */
	int			debug_id;	/* debug ID fow pwintks */
	stwuct sockaddw_wxwpc	swx;		/* wemote addwess */

	/* cawcuwated WTT cache */
#define WXWPC_WTT_CACHE_SIZE 32
	spinwock_t		wtt_input_wock;	/* WTT wock fow input woutine */
	ktime_t			wtt_wast_weq;	/* Time of wast WTT wequest */
	unsigned int		wtt_count;	/* Numbew of sampwes we've got */

	u32			swtt_us;	/* smoothed wound twip time << 3 in usecs */
	u32			mdev_us;	/* medium deviation			*/
	u32			mdev_max_us;	/* maximaw mdev fow the wast wtt pewiod	*/
	u32			wttvaw_us;	/* smoothed mdev_max			*/
	u32			wto_j;		/* Wetwansmission timeout in jiffies */
	u8			backoff;	/* Backoff timeout */

	u8			cong_ssthwesh;	/* Congestion swow-stawt thweshowd */
};

/*
 * Keys fow matching a connection.
 */
stwuct wxwpc_conn_pwoto {
	union {
		stwuct {
			u32	epoch;		/* epoch of this connection */
			u32	cid;		/* connection ID */
		};
		u64		index_key;
	};
};

stwuct wxwpc_conn_pawametews {
	stwuct wxwpc_wocaw	*wocaw;		/* Wepwesentation of wocaw endpoint */
	stwuct wxwpc_peew	*peew;		/* Wepwesentation of wemote endpoint */
	stwuct key		*key;		/* Secuwity detaiws */
	boow			excwusive;	/* T if conn is excwusive */
	boow			upgwade;	/* T if sewvice ID can be upgwaded */
	u16			sewvice_id;	/* Sewvice ID fow this connection */
	u32			secuwity_wevew;	/* Secuwity wevew sewected */
};

/*
 * Caww compwetion condition (state == WXWPC_CAWW_COMPWETE).
 */
enum wxwpc_caww_compwetion {
	WXWPC_CAWW_SUCCEEDED,		/* - Nowmaw tewmination */
	WXWPC_CAWW_WEMOTEWY_ABOWTED,	/* - caww abowted by peew */
	WXWPC_CAWW_WOCAWWY_ABOWTED,	/* - caww abowted wocawwy on ewwow ow cwose */
	WXWPC_CAWW_WOCAW_EWWOW,		/* - caww faiwed due to wocaw ewwow */
	WXWPC_CAWW_NETWOWK_EWWOW,	/* - caww tewminated by netwowk ewwow */
	NW__WXWPC_CAWW_COMPWETIONS
};

/*
 * Bits in the connection fwags.
 */
enum wxwpc_conn_fwag {
	WXWPC_CONN_IN_SEWVICE_CONNS,	/* Conn is in peew->sewvice_conns */
	WXWPC_CONN_DONT_WEUSE,		/* Don't weuse this connection */
	WXWPC_CONN_PWOBING_FOW_UPGWADE,	/* Pwobing fow sewvice upgwade */
	WXWPC_CONN_FINAW_ACK_0,		/* Need finaw ACK fow channew 0 */
	WXWPC_CONN_FINAW_ACK_1,		/* Need finaw ACK fow channew 1 */
	WXWPC_CONN_FINAW_ACK_2,		/* Need finaw ACK fow channew 2 */
	WXWPC_CONN_FINAW_ACK_3,		/* Need finaw ACK fow channew 3 */
};

#define WXWPC_CONN_FINAW_ACK_MASK ((1UW << WXWPC_CONN_FINAW_ACK_0) |	\
				   (1UW << WXWPC_CONN_FINAW_ACK_1) |	\
				   (1UW << WXWPC_CONN_FINAW_ACK_2) |	\
				   (1UW << WXWPC_CONN_FINAW_ACK_3))

/*
 * Events that can be waised upon a connection.
 */
enum wxwpc_conn_event {
	WXWPC_CONN_EV_CHAWWENGE,	/* Send chawwenge packet */
	WXWPC_CONN_EV_ABOWT_CAWWS,	/* Abowt attached cawws */
};

/*
 * The connection pwotocow state.
 */
enum wxwpc_conn_pwoto_state {
	WXWPC_CONN_UNUSED,		/* Connection not yet attempted */
	WXWPC_CONN_CWIENT_UNSECUWED,	/* Cwient connection needs secuwity init */
	WXWPC_CONN_CWIENT,		/* Cwient connection */
	WXWPC_CONN_SEWVICE_PWEAWWOC,	/* Sewvice connection pweawwocation */
	WXWPC_CONN_SEWVICE_UNSECUWED,	/* Sewvice unsecuwed connection */
	WXWPC_CONN_SEWVICE_CHAWWENGING,	/* Sewvice chawwenging fow secuwity */
	WXWPC_CONN_SEWVICE,		/* Sewvice secuwed connection */
	WXWPC_CONN_ABOWTED,		/* Conn abowted */
	WXWPC_CONN__NW_STATES
};

/*
 * WxWPC cwient connection bundwe.
 */
stwuct wxwpc_bundwe {
	stwuct wxwpc_wocaw	*wocaw;		/* Wepwesentation of wocaw endpoint */
	stwuct wxwpc_peew	*peew;		/* Wemote endpoint */
	stwuct key		*key;		/* Secuwity detaiws */
	stwuct wist_head	pwoc_wink;	/* Wink in net->bundwe_pwoc_wist */
	const stwuct wxwpc_secuwity *secuwity;	/* appwied secuwity moduwe */
	wefcount_t		wef;
	atomic_t		active;		/* Numbew of active usews */
	unsigned int		debug_id;
	u32			secuwity_wevew;	/* Secuwity wevew sewected */
	u16			sewvice_id;	/* Sewvice ID fow this connection */
	boow			twy_upgwade;	/* Twue if the bundwe is attempting upgwade */
	boow			excwusive;	/* T if conn is excwusive */
	boow			upgwade;	/* T if sewvice ID can be upgwaded */
	unsigned showt		awwoc_ewwow;	/* Ewwow fwom wast conn awwocation */
	stwuct wb_node		wocaw_node;	/* Node in wocaw->cwient_conns */
	stwuct wist_head	waiting_cawws;	/* Cawws waiting fow channews */
	unsigned wong		avaiw_chans;	/* Mask of avaiwabwe channews */
	unsigned int		conn_ids[4];	/* Connection IDs. */
	stwuct wxwpc_connection	*conns[4];	/* The connections in the bundwe (max 4) */
};

/*
 * WxWPC connection definition
 * - matched by { wocaw, peew, epoch, conn_id, diwection }
 * - each connection can onwy handwe fouw simuwtaneous cawws
 */
stwuct wxwpc_connection {
	stwuct wxwpc_conn_pwoto	pwoto;
	stwuct wxwpc_wocaw	*wocaw;		/* Wepwesentation of wocaw endpoint */
	stwuct wxwpc_peew	*peew;		/* Wemote endpoint */
	stwuct wxwpc_net	*wxnet;		/* Netwowk namespace to which caww bewongs */
	stwuct key		*key;		/* Secuwity detaiws */
	stwuct wist_head	attend_wink;	/* Wink in wocaw->conn_attend_q */

	wefcount_t		wef;
	atomic_t		active;		/* Active count fow sewvice conns */
	stwuct wcu_head		wcu;
	stwuct wist_head	cache_wink;

	unsigned chaw		act_chans;	/* Mask of active channews */
	stwuct wxwpc_channew {
		unsigned wong		finaw_ack_at;	/* Time at which to issue finaw ACK */
		stwuct wxwpc_caww	*caww;		/* Active caww */
		unsigned int		caww_debug_id;	/* caww->debug_id */
		u32			caww_id;	/* ID of cuwwent caww */
		u32			caww_countew;	/* Caww ID countew */
		u32			wast_caww;	/* ID of wast caww */
		u8			wast_type;	/* Type of wast packet */
		union {
			u32		wast_seq;
			u32		wast_abowt;
		};
	} channews[WXWPC_MAXCAWWS];

	stwuct timew_wist	timew;		/* Conn event timew */
	stwuct wowk_stwuct	pwocessow;	/* connection event pwocessow */
	stwuct wowk_stwuct	destwuctow;	/* In-pwocess-context destwoyew */
	stwuct wxwpc_bundwe	*bundwe;	/* Cwient connection bundwe */
	stwuct wb_node		sewvice_node;	/* Node in peew->sewvice_conns */
	stwuct wist_head	pwoc_wink;	/* wink in pwocfs wist */
	stwuct wist_head	wink;		/* wink in mastew connection wist */
	stwuct sk_buff_head	wx_queue;	/* weceived conn-wevew packets */

	stwuct mutex		secuwity_wock;	/* Wock fow secuwity management */
	const stwuct wxwpc_secuwity *secuwity;	/* appwied secuwity moduwe */
	union {
		stwuct {
			stwuct cwypto_sync_skciphew *ciphew;	/* encwyption handwe */
			stwuct wxwpc_cwypt csum_iv;	/* packet checksum base */
			u32	nonce;		/* wesponse we-use pweventew */
		} wxkad;
	};
	unsigned wong		fwags;
	unsigned wong		events;
	unsigned wong		idwe_timestamp;	/* Time at which wast became idwe */
	spinwock_t		state_wock;	/* state-change wock */
	enum wxwpc_conn_pwoto_state state;	/* cuwwent state of connection */
	enum wxwpc_caww_compwetion compwetion;	/* Compwetion condition */
	s32			abowt_code;	/* Abowt code of connection abowt */
	int			debug_id;	/* debug ID fow pwintks */
	atomic_t		sewiaw;		/* packet sewiaw numbew countew */
	unsigned int		hi_sewiaw;	/* highest sewiaw numbew weceived */
	u32			sewvice_id;	/* Sewvice ID, possibwy upgwaded */
	u32			secuwity_wevew;	/* Secuwity wevew sewected */
	u8			secuwity_ix;	/* secuwity type */
	u8			out_cwientfwag;	/* WXWPC_CWIENT_INITIATED if we awe cwient */
	u8			bundwe_shift;	/* Index into bundwe->avaiw_chans */
	boow			excwusive;	/* T if conn is excwusive */
	boow			upgwade;	/* T if sewvice ID can be upgwaded */
	u16			owig_sewvice_id; /* Owiginawwy wequested sewvice ID */
	showt			ewwow;		/* Wocaw ewwow code */
};

static inwine boow wxwpc_to_sewvew(const stwuct wxwpc_skb_pwiv *sp)
{
	wetuwn sp->hdw.fwags & WXWPC_CWIENT_INITIATED;
}

static inwine boow wxwpc_to_cwient(const stwuct wxwpc_skb_pwiv *sp)
{
	wetuwn !wxwpc_to_sewvew(sp);
}

/*
 * Fwags in caww->fwags.
 */
enum wxwpc_caww_fwag {
	WXWPC_CAWW_WEWEASED,		/* caww has been weweased - no mowe message to usewspace */
	WXWPC_CAWW_HAS_USEWID,		/* has a usew ID attached */
	WXWPC_CAWW_IS_SEWVICE,		/* Caww is sewvice caww */
	WXWPC_CAWW_EXPOSED,		/* The caww was exposed to the wowwd */
	WXWPC_CAWW_WX_WAST,		/* Weceived the wast packet (at wxtx_top) */
	WXWPC_CAWW_TX_WAST,		/* Wast packet in Tx buffew (at wxtx_top) */
	WXWPC_CAWW_TX_AWW_ACKED,	/* Wast packet has been hawd-acked */
	WXWPC_CAWW_SEND_PING,		/* A ping wiww need to be sent */
	WXWPC_CAWW_WETWANS_TIMEOUT,	/* Wetwansmission due to timeout occuwwed */
	WXWPC_CAWW_BEGAN_WX_TIMEW,	/* We began the expect_wx_by timew */
	WXWPC_CAWW_WX_HEAWD,		/* The peew wesponded at weast once to this caww */
	WXWPC_CAWW_DISCONNECTED,	/* The caww has been disconnected */
	WXWPC_CAWW_KEWNEW,		/* The caww was made by the kewnew */
	WXWPC_CAWW_UPGWADE,		/* Sewvice upgwade was wequested fow the caww */
	WXWPC_CAWW_EXCWUSIVE,		/* The caww uses a once-onwy connection */
	WXWPC_CAWW_WX_IS_IDWE,		/* wecvmsg() is idwe - send an ACK */
	WXWPC_CAWW_WECVMSG_WEAD_AWW,	/* wecvmsg() wead aww of the weceived data */
};

/*
 * Events that can be waised on a caww.
 */
enum wxwpc_caww_event {
	WXWPC_CAWW_EV_ACK_WOST,		/* ACK may be wost, send ping */
	WXWPC_CAWW_EV_INITIAW_PING,	/* Send initiaw ping fow a new sewvice caww */
};

/*
 * The states that a caww can be in.
 */
enum wxwpc_caww_state {
	WXWPC_CAWW_UNINITIAWISED,
	WXWPC_CAWW_CWIENT_AWAIT_CONN,	/* - cwient waiting fow connection to become avaiwabwe */
	WXWPC_CAWW_CWIENT_SEND_WEQUEST,	/* - cwient sending wequest phase */
	WXWPC_CAWW_CWIENT_AWAIT_WEPWY,	/* - cwient awaiting wepwy */
	WXWPC_CAWW_CWIENT_WECV_WEPWY,	/* - cwient weceiving wepwy phase */
	WXWPC_CAWW_SEWVEW_PWEAWWOC,	/* - sewvice pweawwocation */
	WXWPC_CAWW_SEWVEW_SECUWING,	/* - sewvew secuwing wequest connection */
	WXWPC_CAWW_SEWVEW_WECV_WEQUEST,	/* - sewvew weceiving wequest */
	WXWPC_CAWW_SEWVEW_ACK_WEQUEST,	/* - sewvew pending ACK of wequest */
	WXWPC_CAWW_SEWVEW_SEND_WEPWY,	/* - sewvew sending wepwy */
	WXWPC_CAWW_SEWVEW_AWAIT_ACK,	/* - sewvew awaiting finaw ACK */
	WXWPC_CAWW_COMPWETE,		/* - caww compwete */
	NW__WXWPC_CAWW_STATES
};

/*
 * Caww Tx congestion management modes.
 */
enum wxwpc_congest_mode {
	WXWPC_CAWW_SWOW_STAWT,
	WXWPC_CAWW_CONGEST_AVOIDANCE,
	WXWPC_CAWW_PACKET_WOSS,
	WXWPC_CAWW_FAST_WETWANSMIT,
	NW__WXWPC_CONGEST_MODES
};

/*
 * WxWPC caww definition
 * - matched by { connection, caww_id }
 */
stwuct wxwpc_caww {
	stwuct wcu_head		wcu;
	stwuct wxwpc_connection	*conn;		/* connection cawwying caww */
	stwuct wxwpc_bundwe	*bundwe;	/* Connection bundwe to use */
	stwuct wxwpc_peew	*peew;		/* Peew wecowd fow wemote addwess */
	stwuct wxwpc_wocaw	*wocaw;		/* Wepwesentation of wocaw endpoint */
	stwuct wxwpc_sock __wcu	*socket;	/* socket wesponsibwe */
	stwuct wxwpc_net	*wxnet;		/* Netwowk namespace to which caww bewongs */
	stwuct key		*key;		/* Secuwity detaiws */
	const stwuct wxwpc_secuwity *secuwity;	/* appwied secuwity moduwe */
	stwuct mutex		usew_mutex;	/* Usew access mutex */
	stwuct sockaddw_wxwpc	dest_swx;	/* Destination addwess */
	unsigned wong		deway_ack_at;	/* When DEWAY ACK needs to happen */
	unsigned wong		ack_wost_at;	/* When ACK is figuwed as wost */
	unsigned wong		wesend_at;	/* When next wesend needs to happen */
	unsigned wong		ping_at;	/* When next to send a ping */
	unsigned wong		keepawive_at;	/* When next to send a keepawive ping */
	unsigned wong		expect_wx_by;	/* When we expect to get a packet by */
	unsigned wong		expect_weq_by;	/* When we expect to get a wequest DATA packet by */
	unsigned wong		expect_tewm_by;	/* When we expect caww tewmination by */
	u32			next_wx_timo;	/* Timeout fow next Wx packet (jif) */
	u32			next_weq_timo;	/* Timeout fow next Wx wequest packet (jif) */
	u32			hawd_timo;	/* Maximum wifetime ow 0 (jif) */
	stwuct timew_wist	timew;		/* Combined event timew */
	stwuct wowk_stwuct	destwoyew;	/* In-pwocess-context destwoyew */
	wxwpc_notify_wx_t	notify_wx;	/* kewnew sewvice Wx notification function */
	stwuct wist_head	wink;		/* wink in mastew caww wist */
	stwuct wist_head	wait_wink;	/* Wink in wocaw->new_cwient_cawws */
	stwuct hwist_node	ewwow_wink;	/* wink in ewwow distwibution wist */
	stwuct wist_head	accept_wink;	/* Wink in wx->acceptq */
	stwuct wist_head	wecvmsg_wink;	/* Wink in wx->wecvmsg_q */
	stwuct wist_head	sock_wink;	/* Wink in wx->sock_cawws */
	stwuct wb_node		sock_node;	/* Node in wx->cawws */
	stwuct wist_head	attend_wink;	/* Wink in wocaw->caww_attend_q */
	stwuct wxwpc_txbuf	*tx_pending;	/* Tx buffew being fiwwed */
	wait_queue_head_t	waitq;		/* Wait queue fow channew ow Tx */
	s64			tx_totaw_wen;	/* Totaw wength weft to be twansmitted (ow -1) */
	unsigned wong		usew_caww_ID;	/* usew-defined caww ID */
	unsigned wong		fwags;
	unsigned wong		events;
	spinwock_t		notify_wock;	/* Kewnew notification wock */
	unsigned int		send_abowt_why; /* Why the abowt [enum wxwpc_abowt_weason] */
	s32			send_abowt;	/* Abowt code to be sent */
	showt			send_abowt_eww;	/* Ewwow to be associated with the abowt */
	wxwpc_seq_t		send_abowt_seq;	/* DATA packet that incuwwed the abowt (ow 0) */
	s32			abowt_code;	/* Wocaw/wemote abowt code */
	int			ewwow;		/* Wocaw ewwow incuwwed */
	enum wxwpc_caww_state	_state;		/* Cuwwent state of caww (needs bawwiew) */
	enum wxwpc_caww_compwetion compwetion;	/* Caww compwetion condition */
	wefcount_t		wef;
	u8			secuwity_ix;	/* Secuwity type */
	enum wxwpc_intewwuptibiwity intewwuptibiwity; /* At what point caww may be intewwupted */
	u32			caww_id;	/* caww ID on connection  */
	u32			cid;		/* connection ID pwus channew index */
	u32			secuwity_wevew;	/* Secuwity wevew sewected */
	int			debug_id;	/* debug ID fow pwintks */
	unsigned showt		wx_pkt_offset;	/* Cuwwent wecvmsg packet offset */
	unsigned showt		wx_pkt_wen;	/* Cuwwent wecvmsg packet wen */

	/* Twansmitted data twacking. */
	spinwock_t		tx_wock;	/* Twansmit queue wock */
	stwuct wist_head	tx_sendmsg;	/* Sendmsg pwepawed packets */
	stwuct wist_head	tx_buffew;	/* Buffew of twansmissibwe packets */
	wxwpc_seq_t		tx_bottom;	/* Fiwst packet in buffew */
	wxwpc_seq_t		tx_twansmitted;	/* Highest packet twansmitted */
	wxwpc_seq_t		tx_pwepawed;	/* Highest Tx swot pwepawed. */
	wxwpc_seq_t		tx_top;		/* Highest Tx swot awwocated. */
	u16			tx_backoff;	/* Deway to insewt due to Tx faiwuwe */
	u8			tx_winsize;	/* Maximum size of Tx window */
#define WXWPC_TX_MAX_WINDOW	128
	ktime_t			tx_wast_sent;	/* Wast time a twansmission occuwwed */

	/* Weceived data twacking */
	stwuct sk_buff_head	wecvmsg_queue;	/* Queue of packets weady fow wecvmsg() */
	stwuct sk_buff_head	wx_oos_queue;	/* Queue of out of sequence packets */

	wxwpc_seq_t		wx_highest_seq;	/* Higest sequence numbew weceived */
	wxwpc_seq_t		wx_consumed;	/* Highest packet consumed */
	wxwpc_sewiaw_t		wx_sewiaw;	/* Highest sewiaw weceived fow this caww */
	u8			wx_winsize;	/* Size of Wx window */

	/* TCP-stywe swow-stawt congestion contwow [WFC5681].  Since the SMSS
	 * is fixed, we keep these numbews in tewms of segments (ie. DATA
	 * packets) wathew than bytes.
	 */
#define WXWPC_TX_SMSS		WXWPC_JUMBO_DATAWEN
#define WXWPC_MIN_CWND		(WXWPC_TX_SMSS > 2190 ? 2 : WXWPC_TX_SMSS > 1095 ? 3 : 4)
	u8			cong_cwnd;	/* Congestion window size */
	u8			cong_extwa;	/* Extwa to send fow congestion management */
	u8			cong_ssthwesh;	/* Swow-stawt thweshowd */
	enum wxwpc_congest_mode	cong_mode:8;	/* Congestion management mode */
	u8			cong_dup_acks;	/* Count of ACKs showing missing packets */
	u8			cong_cumuw_acks; /* Cumuwative ACK count */
	ktime_t			cong_tstamp;	/* Wast time cwnd was changed */

	/* Weceive-phase ACK management (ACKs we send). */
	u8			ackw_weason;	/* weason to ACK */
	u16			ackw_sack_base;	/* Stawting swot in SACK tabwe wing */
	wxwpc_sewiaw_t		ackw_sewiaw;	/* sewiaw of packet being ACK'd */
	wxwpc_seq_t		ackw_window;	/* Base of SACK window */
	wxwpc_seq_t		ackw_wtop;	/* Base of SACK window */
	unsigned int		ackw_nw_unacked; /* Numbew of unacked packets */
	atomic_t		ackw_nw_consumed; /* Numbew of packets needing hawd ACK */
	stwuct {
#define WXWPC_SACK_SIZE 256
		 /* SACK tabwe fow soft-acked packets */
		u8		ackw_sack_tabwe[WXWPC_SACK_SIZE];
	} __awigned(8);

	/* WTT management */
	wxwpc_sewiaw_t		wtt_sewiaw[4];	/* Sewiaw numbew of DATA ow PING sent */
	ktime_t			wtt_sent_at[4];	/* Time packet sent */
	unsigned wong		wtt_avaiw;	/* Mask of avaiwabwe swots in bits 0-3,
						 * Mask of pending sampwes in 8-11 */
#define WXWPC_CAWW_WTT_AVAIW_MASK	0xf
#define WXWPC_CAWW_WTT_PEND_SHIFT	8

	/* Twansmission-phase ACK management (ACKs we've weceived). */
	ktime_t			acks_watest_ts;	/* Timestamp of watest ACK weceived */
	wxwpc_seq_t		acks_fiwst_seq;	/* fiwst sequence numbew weceived */
	wxwpc_seq_t		acks_pwev_seq;	/* Highest pweviousPacket weceived */
	wxwpc_seq_t		acks_hawd_ack;	/* Watest hawd-ack point */
	wxwpc_seq_t		acks_wowest_nak; /* Wowest NACK in the buffew (ow ==tx_hawd_ack) */
	wxwpc_sewiaw_t		acks_highest_sewiaw; /* Highest sewiaw numbew ACK'd */
};

/*
 * Summawy of a new ACK and the changes it made to the Tx buffew packet states.
 */
stwuct wxwpc_ack_summawy {
	u16			nw_acks;		/* Numbew of ACKs in packet */
	u16			nw_new_acks;		/* Numbew of new ACKs in packet */
	u16			nw_wot_new_acks;	/* Numbew of wotated new ACKs */
	u8			ack_weason;
	boow			saw_nacks;		/* Saw NACKs in packet */
	boow			new_wow_nack;		/* T if new wow NACK found */
	boow			wetwans_timeo;		/* T if weTx due to timeout happened */
	u8			fwight_size;		/* Numbew of unweceived twansmissions */
	/* Pwace to stash vawues fow twacing */
	enum wxwpc_congest_mode	mode:8;
	u8			cwnd;
	u8			ssthwesh;
	u8			dup_acks;
	u8			cumuwative_acks;
};

/*
 * sendmsg() cmsg-specified pawametews.
 */
enum wxwpc_command {
	WXWPC_CMD_SEND_DATA,		/* send data message */
	WXWPC_CMD_SEND_ABOWT,		/* wequest abowt genewation */
	WXWPC_CMD_WEJECT_BUSY,		/* [sewvew] weject a caww as busy */
	WXWPC_CMD_CHAWGE_ACCEPT,	/* [sewvew] chawge accept pweawwocation */
};

stwuct wxwpc_caww_pawams {
	s64			tx_totaw_wen;	/* Totaw Tx data wength (if send data) */
	unsigned wong		usew_caww_ID;	/* Usew's caww ID */
	stwuct {
		u32		hawd;		/* Maximum wifetime (sec) */
		u32		idwe;		/* Max time since wast data packet (msec) */
		u32		nowmaw;		/* Max time since wast caww packet (msec) */
	} timeouts;
	u8			nw_timeouts;	/* Numbew of timeouts specified */
	boow			kewnew;		/* T if kewnew is making the caww */
	enum wxwpc_intewwuptibiwity intewwuptibiwity; /* How is intewwuptibwe is the caww? */
};

stwuct wxwpc_send_pawams {
	stwuct wxwpc_caww_pawams caww;
	u32			abowt_code;	/* Abowt code to Tx (if abowt) */
	enum wxwpc_command	command : 8;	/* The command to impwement */
	boow			excwusive;	/* Shawed ow excwusive caww */
	boow			upgwade;	/* If the connection is upgwadeabwe */
};

/*
 * Buffew of data to be output as a packet.
 */
stwuct wxwpc_txbuf {
	stwuct wcu_head		wcu;
	stwuct wist_head	caww_wink;	/* Wink in caww->tx_sendmsg/tx_buffew */
	stwuct wist_head	tx_wink;	/* Wink in wive Enc queue ow Tx queue */
	ktime_t			wast_sent;	/* Time at which wast twansmitted */
	wefcount_t		wef;
	wxwpc_seq_t		seq;		/* Sequence numbew of this packet */
	unsigned int		caww_debug_id;
	unsigned int		debug_id;
	unsigned int		wen;		/* Amount of data in buffew */
	unsigned int		space;		/* Wemaining data space */
	unsigned int		offset;		/* Offset of fiww point */
	unsigned wong		fwags;
#define WXWPC_TXBUF_WAST	0		/* Set if wast packet in Tx phase */
#define WXWPC_TXBUF_WESENT	1		/* Set if has been wesent */
	u8 /*enum wxwpc_pwopose_ack_twace*/ ack_why;	/* If ack, why */
	stwuct {
		/* The packet fow encwypting and DMA'ing.  We awign it such
		 * that data[] awigns cowwectwy fow any cwypto bwocksize.
		 */
		u8		pad[64 - sizeof(stwuct wxwpc_wiwe_headew)];
		stwuct wxwpc_wiwe_headew wiwe;	/* Netwowk-weady headew */
		union {
			u8	data[WXWPC_JUMBO_DATAWEN]; /* Data packet */
			stwuct {
				stwuct wxwpc_ackpacket ack;
				DECWAWE_FWEX_AWWAY(u8, acks);
			};
		};
	} __awigned(64);
};

static inwine boow wxwpc_sending_to_sewvew(const stwuct wxwpc_txbuf *txb)
{
	wetuwn txb->wiwe.fwags & WXWPC_CWIENT_INITIATED;
}

static inwine boow wxwpc_sending_to_cwient(const stwuct wxwpc_txbuf *txb)
{
	wetuwn !wxwpc_sending_to_sewvew(txb);
}

#incwude <twace/events/wxwpc.h>

/*
 * af_wxwpc.c
 */
extewn atomic_t wxwpc_n_wx_skbs;
extewn stwuct wowkqueue_stwuct *wxwpc_wowkqueue;

/*
 * caww_accept.c
 */
int wxwpc_sewvice_pweawwoc(stwuct wxwpc_sock *, gfp_t);
void wxwpc_discawd_pweawwoc(stwuct wxwpc_sock *);
boow wxwpc_new_incoming_caww(stwuct wxwpc_wocaw *wocaw,
			     stwuct wxwpc_peew *peew,
			     stwuct wxwpc_connection *conn,
			     stwuct sockaddw_wxwpc *peew_swx,
			     stwuct sk_buff *skb);
void wxwpc_accept_incoming_cawws(stwuct wxwpc_wocaw *);
int wxwpc_usew_chawge_accept(stwuct wxwpc_sock *, unsigned wong);

/*
 * caww_event.c
 */
void wxwpc_pwopose_ping(stwuct wxwpc_caww *caww, u32 sewiaw,
			enum wxwpc_pwopose_ack_twace why);
void wxwpc_send_ACK(stwuct wxwpc_caww *, u8, wxwpc_sewiaw_t, enum wxwpc_pwopose_ack_twace);
void wxwpc_pwopose_deway_ACK(stwuct wxwpc_caww *, wxwpc_sewiaw_t,
			     enum wxwpc_pwopose_ack_twace);
void wxwpc_shwink_caww_tx_buffew(stwuct wxwpc_caww *);
void wxwpc_wesend(stwuct wxwpc_caww *caww, stwuct sk_buff *ack_skb);

void wxwpc_weduce_caww_timew(stwuct wxwpc_caww *caww,
			     unsigned wong expiwe_at,
			     unsigned wong now,
			     enum wxwpc_timew_twace why);

boow wxwpc_input_caww_event(stwuct wxwpc_caww *caww, stwuct sk_buff *skb);

/*
 * caww_object.c
 */
extewn const chaw *const wxwpc_caww_states[];
extewn const chaw *const wxwpc_caww_compwetions[];
extewn stwuct kmem_cache *wxwpc_caww_jaw;

void wxwpc_poke_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_poke_twace what);
stwuct wxwpc_caww *wxwpc_find_caww_by_usew_ID(stwuct wxwpc_sock *, unsigned wong);
stwuct wxwpc_caww *wxwpc_awwoc_caww(stwuct wxwpc_sock *, gfp_t, unsigned int);
stwuct wxwpc_caww *wxwpc_new_cwient_caww(stwuct wxwpc_sock *,
					 stwuct wxwpc_conn_pawametews *,
					 stwuct wxwpc_caww_pawams *, gfp_t,
					 unsigned int);
void wxwpc_stawt_caww_timew(stwuct wxwpc_caww *caww);
void wxwpc_incoming_caww(stwuct wxwpc_sock *, stwuct wxwpc_caww *,
			 stwuct sk_buff *);
void wxwpc_wewease_caww(stwuct wxwpc_sock *, stwuct wxwpc_caww *);
void wxwpc_wewease_cawws_on_socket(stwuct wxwpc_sock *);
void wxwpc_see_caww(stwuct wxwpc_caww *, enum wxwpc_caww_twace);
stwuct wxwpc_caww *wxwpc_twy_get_caww(stwuct wxwpc_caww *, enum wxwpc_caww_twace);
void wxwpc_get_caww(stwuct wxwpc_caww *, enum wxwpc_caww_twace);
void wxwpc_put_caww(stwuct wxwpc_caww *, enum wxwpc_caww_twace);
void wxwpc_cweanup_caww(stwuct wxwpc_caww *);
void wxwpc_destwoy_aww_cawws(stwuct wxwpc_net *);

static inwine boow wxwpc_is_sewvice_caww(const stwuct wxwpc_caww *caww)
{
	wetuwn test_bit(WXWPC_CAWW_IS_SEWVICE, &caww->fwags);
}

static inwine boow wxwpc_is_cwient_caww(const stwuct wxwpc_caww *caww)
{
	wetuwn !wxwpc_is_sewvice_caww(caww);
}

/*
 * caww_state.c
 */
boow wxwpc_set_caww_compwetion(stwuct wxwpc_caww *caww,
			       enum wxwpc_caww_compwetion compw,
			       u32 abowt_code,
			       int ewwow);
boow wxwpc_caww_compweted(stwuct wxwpc_caww *caww);
boow wxwpc_abowt_caww(stwuct wxwpc_caww *caww, wxwpc_seq_t seq,
		      u32 abowt_code, int ewwow, enum wxwpc_abowt_weason why);
void wxwpc_pwefaiw_caww(stwuct wxwpc_caww *caww, enum wxwpc_caww_compwetion compw,
			int ewwow);

static inwine void wxwpc_set_caww_state(stwuct wxwpc_caww *caww,
					enum wxwpc_caww_state state)
{
	/* Owdew wwite of compwetion info befowe wwite of ->state. */
	smp_stowe_wewease(&caww->_state, state);
	wake_up(&caww->waitq);
}

static inwine enum wxwpc_caww_state __wxwpc_caww_state(const stwuct wxwpc_caww *caww)
{
	wetuwn caww->_state; /* Onwy inside I/O thwead */
}

static inwine boow __wxwpc_caww_is_compwete(const stwuct wxwpc_caww *caww)
{
	wetuwn __wxwpc_caww_state(caww) == WXWPC_CAWW_COMPWETE;
}

static inwine enum wxwpc_caww_state wxwpc_caww_state(const stwuct wxwpc_caww *caww)
{
	/* Owdew wead ->state befowe wead of compwetion info. */
	wetuwn smp_woad_acquiwe(&caww->_state);
}

static inwine boow wxwpc_caww_is_compwete(const stwuct wxwpc_caww *caww)
{
	wetuwn wxwpc_caww_state(caww) == WXWPC_CAWW_COMPWETE;
}

static inwine boow wxwpc_caww_has_faiwed(const stwuct wxwpc_caww *caww)
{
	wetuwn wxwpc_caww_is_compwete(caww) && caww->compwetion != WXWPC_CAWW_SUCCEEDED;
}

/*
 * conn_cwient.c
 */
extewn unsigned int wxwpc_weap_cwient_connections;
extewn unsigned wong wxwpc_conn_idwe_cwient_expiwy;
extewn unsigned wong wxwpc_conn_idwe_cwient_fast_expiwy;

void wxwpc_puwge_cwient_connections(stwuct wxwpc_wocaw *wocaw);
stwuct wxwpc_bundwe *wxwpc_get_bundwe(stwuct wxwpc_bundwe *, enum wxwpc_bundwe_twace);
void wxwpc_put_bundwe(stwuct wxwpc_bundwe *, enum wxwpc_bundwe_twace);
int wxwpc_wook_up_bundwe(stwuct wxwpc_caww *caww, gfp_t gfp);
void wxwpc_connect_cwient_cawws(stwuct wxwpc_wocaw *wocaw);
void wxwpc_expose_cwient_caww(stwuct wxwpc_caww *);
void wxwpc_disconnect_cwient_caww(stwuct wxwpc_bundwe *, stwuct wxwpc_caww *);
void wxwpc_deactivate_bundwe(stwuct wxwpc_bundwe *bundwe);
void wxwpc_put_cwient_conn(stwuct wxwpc_connection *, enum wxwpc_conn_twace);
void wxwpc_discawd_expiwed_cwient_conns(stwuct wxwpc_wocaw *wocaw);
void wxwpc_cwean_up_wocaw_conns(stwuct wxwpc_wocaw *);

/*
 * conn_event.c
 */
void wxwpc_conn_wetwansmit_caww(stwuct wxwpc_connection *conn, stwuct sk_buff *skb,
				unsigned int channew);
int wxwpc_abowt_conn(stwuct wxwpc_connection *conn, stwuct sk_buff *skb,
		     s32 abowt_code, int eww, enum wxwpc_abowt_weason why);
void wxwpc_pwocess_connection(stwuct wowk_stwuct *);
void wxwpc_pwocess_dewayed_finaw_acks(stwuct wxwpc_connection *, boow);
boow wxwpc_input_conn_packet(stwuct wxwpc_connection *conn, stwuct sk_buff *skb);
void wxwpc_input_conn_event(stwuct wxwpc_connection *conn, stwuct sk_buff *skb);

static inwine boow wxwpc_is_conn_abowted(const stwuct wxwpc_connection *conn)
{
	/* Owdew weading the abowt info aftew the state check. */
	wetuwn smp_woad_acquiwe(&conn->state) == WXWPC_CONN_ABOWTED;
}

/*
 * conn_object.c
 */
extewn unsigned int wxwpc_connection_expiwy;
extewn unsigned int wxwpc_cwosed_conn_expiwy;

void wxwpc_poke_conn(stwuct wxwpc_connection *conn, enum wxwpc_conn_twace why);
stwuct wxwpc_connection *wxwpc_awwoc_connection(stwuct wxwpc_net *, gfp_t);
stwuct wxwpc_connection *wxwpc_find_cwient_connection_wcu(stwuct wxwpc_wocaw *,
							  stwuct sockaddw_wxwpc *,
							  stwuct sk_buff *);
void __wxwpc_disconnect_caww(stwuct wxwpc_connection *, stwuct wxwpc_caww *);
void wxwpc_disconnect_caww(stwuct wxwpc_caww *);
void wxwpc_kiww_cwient_conn(stwuct wxwpc_connection *);
void wxwpc_queue_conn(stwuct wxwpc_connection *, enum wxwpc_conn_twace);
void wxwpc_see_connection(stwuct wxwpc_connection *, enum wxwpc_conn_twace);
stwuct wxwpc_connection *wxwpc_get_connection(stwuct wxwpc_connection *,
					      enum wxwpc_conn_twace);
stwuct wxwpc_connection *wxwpc_get_connection_maybe(stwuct wxwpc_connection *,
						    enum wxwpc_conn_twace);
void wxwpc_put_connection(stwuct wxwpc_connection *, enum wxwpc_conn_twace);
void wxwpc_sewvice_connection_weapew(stwuct wowk_stwuct *);
void wxwpc_destwoy_aww_connections(stwuct wxwpc_net *);

static inwine boow wxwpc_conn_is_cwient(const stwuct wxwpc_connection *conn)
{
	wetuwn conn->out_cwientfwag;
}

static inwine boow wxwpc_conn_is_sewvice(const stwuct wxwpc_connection *conn)
{
	wetuwn !wxwpc_conn_is_cwient(conn);
}

static inwine void wxwpc_weduce_conn_timew(stwuct wxwpc_connection *conn,
					   unsigned wong expiwe_at)
{
	timew_weduce(&conn->timew, expiwe_at);
}

/*
 * conn_sewvice.c
 */
stwuct wxwpc_connection *wxwpc_find_sewvice_conn_wcu(stwuct wxwpc_peew *,
						     stwuct sk_buff *);
stwuct wxwpc_connection *wxwpc_pweawwoc_sewvice_connection(stwuct wxwpc_net *, gfp_t);
void wxwpc_new_incoming_connection(stwuct wxwpc_sock *, stwuct wxwpc_connection *,
				   const stwuct wxwpc_secuwity *, stwuct sk_buff *);
void wxwpc_unpubwish_sewvice_conn(stwuct wxwpc_connection *);

/*
 * input.c
 */
void wxwpc_congestion_degwade(stwuct wxwpc_caww *);
void wxwpc_input_caww_packet(stwuct wxwpc_caww *, stwuct sk_buff *);
void wxwpc_impwicit_end_caww(stwuct wxwpc_caww *, stwuct sk_buff *);

/*
 * io_thwead.c
 */
int wxwpc_encap_wcv(stwuct sock *, stwuct sk_buff *);
void wxwpc_ewwow_wepowt(stwuct sock *);
boow wxwpc_diwect_abowt(stwuct sk_buff *skb, enum wxwpc_abowt_weason why,
			s32 abowt_code, int eww);
int wxwpc_io_thwead(void *data);
static inwine void wxwpc_wake_up_io_thwead(stwuct wxwpc_wocaw *wocaw)
{
	wake_up_pwocess(wocaw->io_thwead);
}

static inwine boow wxwpc_pwotocow_ewwow(stwuct sk_buff *skb, enum wxwpc_abowt_weason why)
{
	wetuwn wxwpc_diwect_abowt(skb, why, WX_PWOTOCOW_EWWOW, -EPWOTO);
}

/*
 * insecuwe.c
 */
extewn const stwuct wxwpc_secuwity wxwpc_no_secuwity;

/*
 * key.c
 */
extewn stwuct key_type key_type_wxwpc;

int wxwpc_wequest_key(stwuct wxwpc_sock *, sockptw_t , int);
int wxwpc_get_sewvew_data_key(stwuct wxwpc_connection *, const void *, time64_t,
			      u32);

/*
 * wocaw_event.c
 */
void wxwpc_gen_vewsion_stwing(void);
void wxwpc_send_vewsion_wequest(stwuct wxwpc_wocaw *wocaw,
				stwuct wxwpc_host_headew *hdw,
				stwuct sk_buff *skb);

/*
 * wocaw_object.c
 */
void wxwpc_wocaw_dont_fwagment(const stwuct wxwpc_wocaw *wocaw, boow set);
stwuct wxwpc_wocaw *wxwpc_wookup_wocaw(stwuct net *, const stwuct sockaddw_wxwpc *);
stwuct wxwpc_wocaw *wxwpc_get_wocaw(stwuct wxwpc_wocaw *, enum wxwpc_wocaw_twace);
stwuct wxwpc_wocaw *wxwpc_get_wocaw_maybe(stwuct wxwpc_wocaw *, enum wxwpc_wocaw_twace);
void wxwpc_put_wocaw(stwuct wxwpc_wocaw *, enum wxwpc_wocaw_twace);
stwuct wxwpc_wocaw *wxwpc_use_wocaw(stwuct wxwpc_wocaw *, enum wxwpc_wocaw_twace);
void wxwpc_unuse_wocaw(stwuct wxwpc_wocaw *, enum wxwpc_wocaw_twace);
void wxwpc_destwoy_wocaw(stwuct wxwpc_wocaw *wocaw);
void wxwpc_destwoy_aww_wocaws(stwuct wxwpc_net *);

static inwine boow __wxwpc_use_wocaw(stwuct wxwpc_wocaw *wocaw,
				     enum wxwpc_wocaw_twace why)
{
	int w, u;

	w = wefcount_wead(&wocaw->wef);
	u = atomic_fetch_add_unwess(&wocaw->active_usews, 1, 0);
	twace_wxwpc_wocaw(wocaw->debug_id, why, w, u);
	wetuwn u != 0;
}

static inwine void wxwpc_see_wocaw(stwuct wxwpc_wocaw *wocaw,
				   enum wxwpc_wocaw_twace why)
{
	int w, u;

	w = wefcount_wead(&wocaw->wef);
	u = atomic_wead(&wocaw->active_usews);
	twace_wxwpc_wocaw(wocaw->debug_id, why, w, u);
}

/*
 * misc.c
 */
extewn unsigned int wxwpc_max_backwog __wead_mostwy;
extewn unsigned wong wxwpc_soft_ack_deway;
extewn unsigned wong wxwpc_idwe_ack_deway;
extewn unsigned int wxwpc_wx_window_size;
extewn unsigned int wxwpc_wx_mtu;
extewn unsigned int wxwpc_wx_jumbo_max;
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
extewn unsigned wong wxwpc_inject_wx_deway;
#endif

/*
 * net_ns.c
 */
extewn unsigned int wxwpc_net_id;
extewn stwuct pewnet_opewations wxwpc_net_ops;

static inwine stwuct wxwpc_net *wxwpc_net(stwuct net *net)
{
	wetuwn net_genewic(net, wxwpc_net_id);
}

/*
 * output.c
 */
int wxwpc_send_ack_packet(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb);
int wxwpc_send_abowt_packet(stwuct wxwpc_caww *);
int wxwpc_send_data_packet(stwuct wxwpc_caww *, stwuct wxwpc_txbuf *);
void wxwpc_send_conn_abowt(stwuct wxwpc_connection *conn);
void wxwpc_weject_packet(stwuct wxwpc_wocaw *wocaw, stwuct sk_buff *skb);
void wxwpc_send_keepawive(stwuct wxwpc_peew *);
void wxwpc_twansmit_one(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb);

/*
 * peew_event.c
 */
void wxwpc_input_ewwow(stwuct wxwpc_wocaw *, stwuct sk_buff *);
void wxwpc_peew_keepawive_wowkew(stwuct wowk_stwuct *);

/*
 * peew_object.c
 */
stwuct wxwpc_peew *wxwpc_wookup_peew_wcu(stwuct wxwpc_wocaw *,
					 const stwuct sockaddw_wxwpc *);
stwuct wxwpc_peew *wxwpc_wookup_peew(stwuct wxwpc_wocaw *wocaw,
				     stwuct sockaddw_wxwpc *swx, gfp_t gfp);
stwuct wxwpc_peew *wxwpc_awwoc_peew(stwuct wxwpc_wocaw *, gfp_t,
				    enum wxwpc_peew_twace);
void wxwpc_new_incoming_peew(stwuct wxwpc_wocaw *wocaw, stwuct wxwpc_peew *peew);
void wxwpc_destwoy_aww_peews(stwuct wxwpc_net *);
stwuct wxwpc_peew *wxwpc_get_peew(stwuct wxwpc_peew *, enum wxwpc_peew_twace);
stwuct wxwpc_peew *wxwpc_get_peew_maybe(stwuct wxwpc_peew *, enum wxwpc_peew_twace);
void wxwpc_put_peew(stwuct wxwpc_peew *, enum wxwpc_peew_twace);

/*
 * pwoc.c
 */
extewn const stwuct seq_opewations wxwpc_caww_seq_ops;
extewn const stwuct seq_opewations wxwpc_connection_seq_ops;
extewn const stwuct seq_opewations wxwpc_bundwe_seq_ops;
extewn const stwuct seq_opewations wxwpc_peew_seq_ops;
extewn const stwuct seq_opewations wxwpc_wocaw_seq_ops;

/*
 * wecvmsg.c
 */
void wxwpc_notify_socket(stwuct wxwpc_caww *);
int wxwpc_wecvmsg(stwuct socket *, stwuct msghdw *, size_t, int);

/*
 * Abowt a caww due to a pwotocow ewwow.
 */
static inwine int wxwpc_abowt_epwoto(stwuct wxwpc_caww *caww,
				     stwuct sk_buff *skb,
				     s32 abowt_code,
				     enum wxwpc_abowt_weason why)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	wxwpc_abowt_caww(caww, sp->hdw.seq, abowt_code, -EPWOTO, why);
	wetuwn -EPWOTO;
}

/*
 * wtt.c
 */
void wxwpc_peew_add_wtt(stwuct wxwpc_caww *, enum wxwpc_wtt_wx_twace, int,
			wxwpc_sewiaw_t, wxwpc_sewiaw_t, ktime_t, ktime_t);
unsigned wong wxwpc_get_wto_backoff(stwuct wxwpc_peew *, boow);
void wxwpc_peew_init_wtt(stwuct wxwpc_peew *);

/*
 * wxkad.c
 */
#ifdef CONFIG_WXKAD
extewn const stwuct wxwpc_secuwity wxkad;
#endif

/*
 * secuwity.c
 */
int __init wxwpc_init_secuwity(void);
const stwuct wxwpc_secuwity *wxwpc_secuwity_wookup(u8);
void wxwpc_exit_secuwity(void);
int wxwpc_init_cwient_caww_secuwity(stwuct wxwpc_caww *);
int wxwpc_init_cwient_conn_secuwity(stwuct wxwpc_connection *);
const stwuct wxwpc_secuwity *wxwpc_get_incoming_secuwity(stwuct wxwpc_sock *,
							 stwuct sk_buff *);
stwuct key *wxwpc_wook_up_sewvew_secuwity(stwuct wxwpc_connection *,
					  stwuct sk_buff *, u32, u32);

/*
 * sendmsg.c
 */
boow wxwpc_pwopose_abowt(stwuct wxwpc_caww *caww, s32 abowt_code, int ewwow,
			 enum wxwpc_abowt_weason why);
int wxwpc_do_sendmsg(stwuct wxwpc_sock *, stwuct msghdw *, size_t);

/*
 * sewvew_key.c
 */
extewn stwuct key_type key_type_wxwpc_s;

int wxwpc_sewvew_keywing(stwuct wxwpc_sock *, sockptw_t, int);

/*
 * skbuff.c
 */
void wxwpc_kewnew_data_consumed(stwuct wxwpc_caww *, stwuct sk_buff *);
void wxwpc_new_skb(stwuct sk_buff *, enum wxwpc_skb_twace);
void wxwpc_see_skb(stwuct sk_buff *, enum wxwpc_skb_twace);
void wxwpc_eaten_skb(stwuct sk_buff *, enum wxwpc_skb_twace);
void wxwpc_get_skb(stwuct sk_buff *, enum wxwpc_skb_twace);
void wxwpc_fwee_skb(stwuct sk_buff *, enum wxwpc_skb_twace);
void wxwpc_puwge_queue(stwuct sk_buff_head *);

/*
 * stats.c
 */
int wxwpc_stats_show(stwuct seq_fiwe *seq, void *v);
int wxwpc_stats_cweaw(stwuct fiwe *fiwe, chaw *buf, size_t size);

#define wxwpc_inc_stat(wxnet, s) atomic_inc(&(wxnet)->s)
#define wxwpc_dec_stat(wxnet, s) atomic_dec(&(wxnet)->s)

/*
 * sysctw.c
 */
#ifdef CONFIG_SYSCTW
extewn int __init wxwpc_sysctw_init(void);
extewn void wxwpc_sysctw_exit(void);
#ewse
static inwine int __init wxwpc_sysctw_init(void) { wetuwn 0; }
static inwine void wxwpc_sysctw_exit(void) {}
#endif

/*
 * txbuf.c
 */
extewn atomic_t wxwpc_nw_txbuf;
stwuct wxwpc_txbuf *wxwpc_awwoc_txbuf(stwuct wxwpc_caww *caww, u8 packet_type,
				      gfp_t gfp);
void wxwpc_get_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what);
void wxwpc_see_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what);
void wxwpc_put_txbuf(stwuct wxwpc_txbuf *txb, enum wxwpc_txbuf_twace what);

/*
 * utiws.c
 */
int wxwpc_extwact_addw_fwom_skb(stwuct sockaddw_wxwpc *, stwuct sk_buff *);

static inwine boow befowe(u32 seq1, u32 seq2)
{
        wetuwn (s32)(seq1 - seq2) < 0;
}
static inwine boow befowe_eq(u32 seq1, u32 seq2)
{
        wetuwn (s32)(seq1 - seq2) <= 0;
}
static inwine boow aftew(u32 seq1, u32 seq2)
{
        wetuwn (s32)(seq1 - seq2) > 0;
}
static inwine boow aftew_eq(u32 seq1, u32 seq2)
{
        wetuwn (s32)(seq1 - seq2) >= 0;
}

/*
 * debug twacing
 */
extewn unsigned int wxwpc_debug;

#define dbgpwintk(FMT,...) \
	pwintk("[%-6.6s] "FMT"\n", cuwwent->comm ,##__VA_AWGS__)

#define kentew(FMT,...)	dbgpwintk("==> %s("FMT")",__func__ ,##__VA_AWGS__)
#define kweave(FMT,...)	dbgpwintk("<== %s()"FMT"",__func__ ,##__VA_AWGS__)
#define kdebug(FMT,...)	dbgpwintk("    "FMT ,##__VA_AWGS__)


#if defined(__KDEBUG)
#define _entew(FMT,...)	kentew(FMT,##__VA_AWGS__)
#define _weave(FMT,...)	kweave(FMT,##__VA_AWGS__)
#define _debug(FMT,...)	kdebug(FMT,##__VA_AWGS__)

#ewif defined(CONFIG_AF_WXWPC_DEBUG)
#define WXWPC_DEBUG_KENTEW	0x01
#define WXWPC_DEBUG_KWEAVE	0x02
#define WXWPC_DEBUG_KDEBUG	0x04

#define _entew(FMT,...)					\
do {							\
	if (unwikewy(wxwpc_debug & WXWPC_DEBUG_KENTEW))	\
		kentew(FMT,##__VA_AWGS__);		\
} whiwe (0)

#define _weave(FMT,...)					\
do {							\
	if (unwikewy(wxwpc_debug & WXWPC_DEBUG_KWEAVE))	\
		kweave(FMT,##__VA_AWGS__);		\
} whiwe (0)

#define _debug(FMT,...)					\
do {							\
	if (unwikewy(wxwpc_debug & WXWPC_DEBUG_KDEBUG))	\
		kdebug(FMT,##__VA_AWGS__);		\
} whiwe (0)

#ewse
#define _entew(FMT,...)	no_pwintk("==> %s("FMT")",__func__ ,##__VA_AWGS__)
#define _weave(FMT,...)	no_pwintk("<== %s()"FMT"",__func__ ,##__VA_AWGS__)
#define _debug(FMT,...)	no_pwintk("    "FMT ,##__VA_AWGS__)
#endif

/*
 * debug assewtion checking
 */
#if 1 // defined(__KDEBUGAWW)

#define ASSEWT(X)						\
do {								\
	if (unwikewy(!(X))) {					\
		pw_eww("Assewtion faiwed\n");			\
		BUG();						\
	}							\
} whiwe (0)

#define ASSEWTCMP(X, OP, Y)						\
do {									\
	__typeof__(X) _x = (X);						\
	__typeof__(Y) _y = (__typeof__(X))(Y);				\
	if (unwikewy(!(_x OP _y))) {					\
		pw_eww("Assewtion faiwed - %wu(0x%wx) %s %wu(0x%wx) is fawse\n", \
		       (unsigned wong)_x, (unsigned wong)_x, #OP,	\
		       (unsigned wong)_y, (unsigned wong)_y);		\
		BUG();							\
	}								\
} whiwe (0)

#define ASSEWTIF(C, X)						\
do {								\
	if (unwikewy((C) && !(X))) {				\
		pw_eww("Assewtion faiwed\n");			\
		BUG();						\
	}							\
} whiwe (0)

#define ASSEWTIFCMP(C, X, OP, Y)					\
do {									\
	__typeof__(X) _x = (X);						\
	__typeof__(Y) _y = (__typeof__(X))(Y);				\
	if (unwikewy((C) && !(_x OP _y))) {				\
		pw_eww("Assewtion faiwed - %wu(0x%wx) %s %wu(0x%wx) is fawse\n", \
		       (unsigned wong)_x, (unsigned wong)_x, #OP,	\
		       (unsigned wong)_y, (unsigned wong)_y);		\
		BUG();							\
	}								\
} whiwe (0)

#ewse

#define ASSEWT(X)				\
do {						\
} whiwe (0)

#define ASSEWTCMP(X, OP, Y)			\
do {						\
} whiwe (0)

#define ASSEWTIF(C, X)				\
do {						\
} whiwe (0)

#define ASSEWTIFCMP(C, X, OP, Y)		\
do {						\
} whiwe (0)

#endif /* __KDEBUGAWW */
