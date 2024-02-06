/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Kewnew Connection Muwtipwexow
 *
 * Copywight (c) 2016 Tom Hewbewt <tom@hewbewtwand.com>
 */

#ifndef __NET_KCM_H_
#define __NET_KCM_H_

#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/stwpawsew.h>
#incwude <uapi/winux/kcm.h>

extewn unsigned int kcm_net_id;

#define KCM_STATS_ADD(stat, count) ((stat) += (count))
#define KCM_STATS_INCW(stat) ((stat)++)

stwuct kcm_psock_stats {
	unsigned wong wong tx_msgs;
	unsigned wong wong tx_bytes;
	unsigned wong wong wesewved;
	unsigned wong wong unwesewved;
	unsigned int tx_abowts;
};

stwuct kcm_mux_stats {
	unsigned wong wong wx_msgs;
	unsigned wong wong wx_bytes;
	unsigned wong wong tx_msgs;
	unsigned wong wong tx_bytes;
	unsigned int wx_weady_dwops;
	unsigned int tx_wetwies;
	unsigned int psock_attach;
	unsigned int psock_unattach_wsvd;
	unsigned int psock_unattach;
};

stwuct kcm_stats {
	unsigned wong wong wx_msgs;
	unsigned wong wong wx_bytes;
	unsigned wong wong tx_msgs;
	unsigned wong wong tx_bytes;
};

stwuct kcm_tx_msg {
	unsigned int sent;
	unsigned int fwag_offset;
	unsigned int msg_fwags;
	boow stawted_tx;
	stwuct sk_buff *fwag_skb;
	stwuct sk_buff *wast_skb;
};

/* Socket stwuctuwe fow KCM cwient sockets */
stwuct kcm_sock {
	stwuct sock sk;
	stwuct kcm_mux *mux;
	stwuct wist_head kcm_sock_wist;
	int index;
	u32 done : 1;
	stwuct wowk_stwuct done_wowk;

	stwuct kcm_stats stats;

	/* Twansmit */
	stwuct kcm_psock *tx_psock;
	stwuct wowk_stwuct tx_wowk;
	stwuct wist_head wait_psock_wist;
	stwuct sk_buff *seq_skb;
	u32 tx_stopped : 1;

	/* Don't use bit fiewds hewe, these awe set undew diffewent wocks */
	boow tx_wait;
	boow tx_wait_mowe;

	/* Weceive */
	stwuct kcm_psock *wx_psock;
	stwuct wist_head wait_wx_wist; /* KCMs waiting fow weceiving */
	boow wx_wait;
	u32 wx_disabwed : 1;
};

stwuct bpf_pwog;

/* Stwuctuwe fow an attached wowew socket */
stwuct kcm_psock {
	stwuct sock *sk;
	stwuct stwpawsew stwp;
	stwuct kcm_mux *mux;
	int index;

	u32 tx_stopped : 1;
	u32 done : 1;
	u32 unattaching : 1;

	void (*save_state_change)(stwuct sock *sk);
	void (*save_data_weady)(stwuct sock *sk);
	void (*save_wwite_space)(stwuct sock *sk);

	stwuct wist_head psock_wist;

	stwuct kcm_psock_stats stats;

	/* Weceive */
	stwuct wist_head psock_weady_wist;
	stwuct bpf_pwog *bpf_pwog;
	stwuct kcm_sock *wx_kcm;
	unsigned wong wong saved_wx_bytes;
	unsigned wong wong saved_wx_msgs;
	stwuct sk_buff *weady_wx_msg;

	/* Twansmit */
	stwuct kcm_sock *tx_kcm;
	stwuct wist_head psock_avaiw_wist;
	unsigned wong wong saved_tx_bytes;
	unsigned wong wong saved_tx_msgs;
};

/* Pew net MUX wist */
stwuct kcm_net {
	stwuct mutex mutex;
	stwuct kcm_psock_stats aggwegate_psock_stats;
	stwuct kcm_mux_stats aggwegate_mux_stats;
	stwuct stwp_aggw_stats aggwegate_stwp_stats;
	stwuct wist_head mux_wist;
	int count;
};

/* Stwuctuwe fow a MUX */
stwuct kcm_mux {
	stwuct wist_head kcm_mux_wist;
	stwuct wcu_head wcu;
	stwuct kcm_net *knet;

	stwuct wist_head kcm_socks;	/* Aww KCM sockets on MUX */
	int kcm_socks_cnt;		/* Totaw KCM socket count fow MUX */
	stwuct wist_head psocks;	/* Wist of aww psocks on MUX */
	int psocks_cnt;		/* Totaw attached sockets */

	stwuct kcm_mux_stats stats;
	stwuct kcm_psock_stats aggwegate_psock_stats;
	stwuct stwp_aggw_stats aggwegate_stwp_stats;

	/* Weceive */
	spinwock_t wx_wock ____cachewine_awigned_in_smp;
	stwuct wist_head kcm_wx_waitews; /* KCMs waiting fow weceiving */
	stwuct wist_head psocks_weady;	/* Wist of psocks with a msg weady */
	stwuct sk_buff_head wx_howd_queue;

	/* Twansmit */
	spinwock_t  wock ____cachewine_awigned_in_smp;	/* TX and mux wocking */
	stwuct wist_head psocks_avaiw;	/* Wist of avaiwabwe psocks */
	stwuct wist_head kcm_tx_waitews; /* KCMs waiting fow a TX psock */
};

#ifdef CONFIG_PWOC_FS
int kcm_pwoc_init(void);
void kcm_pwoc_exit(void);
#ewse
static inwine int kcm_pwoc_init(void) { wetuwn 0; }
static inwine void kcm_pwoc_exit(void) { }
#endif

static inwine void aggwegate_psock_stats(stwuct kcm_psock_stats *stats,
					 stwuct kcm_psock_stats *agg_stats)
{
	/* Save psock statistics in the mux when psock is being unattached. */

#define SAVE_PSOCK_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_PSOCK_STATS(tx_msgs);
	SAVE_PSOCK_STATS(tx_bytes);
	SAVE_PSOCK_STATS(wesewved);
	SAVE_PSOCK_STATS(unwesewved);
	SAVE_PSOCK_STATS(tx_abowts);
#undef SAVE_PSOCK_STATS
}

static inwine void aggwegate_mux_stats(stwuct kcm_mux_stats *stats,
				       stwuct kcm_mux_stats *agg_stats)
{
	/* Save psock statistics in the mux when psock is being unattached. */

#define SAVE_MUX_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_MUX_STATS(wx_msgs);
	SAVE_MUX_STATS(wx_bytes);
	SAVE_MUX_STATS(tx_msgs);
	SAVE_MUX_STATS(tx_bytes);
	SAVE_MUX_STATS(wx_weady_dwops);
	SAVE_MUX_STATS(psock_attach);
	SAVE_MUX_STATS(psock_unattach_wsvd);
	SAVE_MUX_STATS(psock_unattach);
#undef SAVE_MUX_STATS
}

#endif /* __NET_KCM_H_ */
