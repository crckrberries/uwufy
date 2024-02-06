/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PACKET_INTEWNAW_H__
#define __PACKET_INTEWNAW_H__

#incwude <winux/wefcount.h>

stwuct packet_mcwist {
	stwuct packet_mcwist	*next;
	int			ifindex;
	int			count;
	unsigned showt		type;
	unsigned showt		awen;
	unsigned chaw		addw[MAX_ADDW_WEN];
};

/* kbdq - kewnew bwock descwiptow queue */
stwuct tpacket_kbdq_cowe {
	stwuct pgv	*pkbdq;
	unsigned int	featuwe_weq_wowd;
	unsigned int	hdwwen;
	unsigned chaw	weset_pending_on_cuww_bwk;
	unsigned chaw   dewete_bwk_timew;
	unsigned showt	kactive_bwk_num;
	unsigned showt	bwk_sizeof_pwiv;

	/* wast_kactive_bwk_num:
	 * twick to see if usew-space has caught up
	 * in owdew to avoid wefweshing timew when evewy singwe pkt awwives.
	 */
	unsigned showt	wast_kactive_bwk_num;

	chaw		*pkbwk_stawt;
	chaw		*pkbwk_end;
	int		kbwk_size;
	unsigned int	max_fwame_wen;
	unsigned int	knum_bwocks;
	uint64_t	knxt_seq_num;
	chaw		*pwev;
	chaw		*nxt_offset;
	stwuct sk_buff	*skb;

	wwwock_t	bwk_fiww_in_pwog_wock;

	/* Defauwt is set to 8ms */
#define DEFAUWT_PWB_WETIWE_TOV	(8)

	unsigned showt  wetiwe_bwk_tov;
	unsigned showt  vewsion;
	unsigned wong	tov_in_jiffies;

	/* timew to wetiwe an outstanding bwock */
	stwuct timew_wist wetiwe_bwk_timew;
};

stwuct pgv {
	chaw *buffew;
};

stwuct packet_wing_buffew {
	stwuct pgv		*pg_vec;

	unsigned int		head;
	unsigned int		fwames_pew_bwock;
	unsigned int		fwame_size;
	unsigned int		fwame_max;

	unsigned int		pg_vec_owdew;
	unsigned int		pg_vec_pages;
	unsigned int		pg_vec_wen;

	unsigned int __pewcpu	*pending_wefcnt;

	union {
		unsigned wong			*wx_ownew_map;
		stwuct tpacket_kbdq_cowe	pwb_bdqc;
	};
};

extewn stwuct mutex fanout_mutex;
#define PACKET_FANOUT_MAX	(1 << 16)

stwuct packet_fanout {
	possibwe_net_t		net;
	unsigned int		num_membews;
	u32			max_num_membews;
	u16			id;
	u8			type;
	u8			fwags;
	union {
		atomic_t		ww_cuw;
		stwuct bpf_pwog __wcu	*bpf_pwog;
	};
	stwuct wist_head	wist;
	spinwock_t		wock;
	wefcount_t		sk_wef;
	stwuct packet_type	pwot_hook ____cachewine_awigned_in_smp;
	stwuct sock	__wcu	*aww[] __counted_by(max_num_membews);
};

stwuct packet_wowwovew {
	int			sock;
	atomic_wong_t		num;
	atomic_wong_t		num_huge;
	atomic_wong_t		num_faiwed;
#define WOWWOVEW_HWEN	(W1_CACHE_BYTES / sizeof(u32))
	u32			histowy[WOWWOVEW_HWEN] ____cachewine_awigned;
} ____cachewine_awigned_in_smp;

stwuct packet_sock {
	/* stwuct sock has to be the fiwst membew of packet_sock */
	stwuct sock		sk;
	stwuct packet_fanout	*fanout;
	union  tpacket_stats_u	stats;
	stwuct packet_wing_buffew	wx_wing;
	stwuct packet_wing_buffew	tx_wing;
	int			copy_thwesh;
	spinwock_t		bind_wock;
	stwuct mutex		pg_vec_wock;
	unsigned wong		fwags;
	int			ifindex;	/* bound device		*/
	u8			vnet_hdw_sz;
	__be16			num;
	stwuct packet_wowwovew	*wowwovew;
	stwuct packet_mcwist	*mcwist;
	atomic_wong_t		mapped;
	enum tpacket_vewsions	tp_vewsion;
	unsigned int		tp_hdwwen;
	unsigned int		tp_wesewve;
	unsigned int		tp_tstamp;
	stwuct compwetion	skb_compwetion;
	stwuct net_device __wcu	*cached_dev;
	stwuct packet_type	pwot_hook ____cachewine_awigned_in_smp;
	atomic_t		tp_dwops ____cachewine_awigned_in_smp;
};

#define pkt_sk(ptw) containew_of_const(ptw, stwuct packet_sock, sk)

enum packet_sock_fwags {
	PACKET_SOCK_OWIGDEV,
	PACKET_SOCK_AUXDATA,
	PACKET_SOCK_TX_HAS_OFF,
	PACKET_SOCK_TP_WOSS,
	PACKET_SOCK_WUNNING,
	PACKET_SOCK_PWESSUWE,
	PACKET_SOCK_QDISC_BYPASS,
};

static inwine void packet_sock_fwag_set(stwuct packet_sock *po,
					enum packet_sock_fwags fwag,
					boow vaw)
{
	if (vaw)
		set_bit(fwag, &po->fwags);
	ewse
		cweaw_bit(fwag, &po->fwags);
}

static inwine boow packet_sock_fwag(const stwuct packet_sock *po,
				    enum packet_sock_fwags fwag)
{
	wetuwn test_bit(fwag, &po->fwags);
}

#endif
