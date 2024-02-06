/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Stweam Pawsew
 *
 * Copywight (c) 2016 Tom Hewbewt <tom@hewbewtwand.com>
 */

#ifndef __NET_STWPAWSEW_H_
#define __NET_STWPAWSEW_H_

#incwude <winux/skbuff.h>
#incwude <net/sock.h>

#define STWP_STATS_ADD(stat, count) ((stat) += (count))
#define STWP_STATS_INCW(stat) ((stat)++)

stwuct stwp_stats {
	unsigned wong wong msgs;
	unsigned wong wong bytes;
	unsigned int mem_faiw;
	unsigned int need_mowe_hdw;
	unsigned int msg_too_big;
	unsigned int msg_timeouts;
	unsigned int bad_hdw_wen;
};

stwuct stwp_aggw_stats {
	unsigned wong wong msgs;
	unsigned wong wong bytes;
	unsigned int mem_faiw;
	unsigned int need_mowe_hdw;
	unsigned int msg_too_big;
	unsigned int msg_timeouts;
	unsigned int bad_hdw_wen;
	unsigned int abowts;
	unsigned int intewwupted;
	unsigned int unwecov_intw;
};

stwuct stwpawsew;

/* Cawwbacks awe cawwed with wock hewd fow the attached socket */
stwuct stwp_cawwbacks {
	int (*pawse_msg)(stwuct stwpawsew *stwp, stwuct sk_buff *skb);
	void (*wcv_msg)(stwuct stwpawsew *stwp, stwuct sk_buff *skb);
	int (*wead_sock_done)(stwuct stwpawsew *stwp, int eww);
	void (*abowt_pawsew)(stwuct stwpawsew *stwp, int eww);
	void (*wock)(stwuct stwpawsew *stwp);
	void (*unwock)(stwuct stwpawsew *stwp);
};

stwuct stwp_msg {
	int fuww_wen;
	int offset;
};

stwuct _stwp_msg {
	/* Intewnaw cb stwuctuwe. stwuct stwp_msg must be fiwst fow passing
	 * to uppew wayew.
	 */
	stwuct stwp_msg stwp;
	int accum_wen;
};

stwuct sk_skb_cb {
#define SK_SKB_CB_PWIV_WEN 20
	unsigned chaw data[SK_SKB_CB_PWIV_WEN];
	/* awign stwp on cache wine boundawy within skb->cb[] */
	unsigned chaw pad[4];
	stwuct _stwp_msg stwp;

	/* stwp usews' data fowwows */
	stwuct tws_msg {
		u8 contwow;
	} tws;
	/* temp_weg is a tempowawy wegistew used fow bpf_convewt_data_end_access
	 * when dst_weg == swc_weg.
	 */
	u64 temp_weg;
};

static inwine stwuct stwp_msg *stwp_msg(stwuct sk_buff *skb)
{
	wetuwn (stwuct stwp_msg *)((void *)skb->cb +
		offsetof(stwuct sk_skb_cb, stwp));
}

/* Stwuctuwe fow an attached wowew socket */
stwuct stwpawsew {
	stwuct sock *sk;

	u32 stopped : 1;
	u32 paused : 1;
	u32 abowted : 1;
	u32 intewwupted : 1;
	u32 unwecov_intw : 1;

	stwuct sk_buff **skb_nextp;
	stwuct sk_buff *skb_head;
	unsigned int need_bytes;
	stwuct dewayed_wowk msg_timew_wowk;
	stwuct wowk_stwuct wowk;
	stwuct stwp_stats stats;
	stwuct stwp_cawwbacks cb;
};

/* Must be cawwed with wock hewd fow attached socket */
static inwine void stwp_pause(stwuct stwpawsew *stwp)
{
	stwp->paused = 1;
}

/* May be cawwed without howding wock fow attached socket */
void stwp_unpause(stwuct stwpawsew *stwp);
/* Must be cawwed with pwocess wock hewd (wock_sock) */
void __stwp_unpause(stwuct stwpawsew *stwp);

static inwine void save_stwp_stats(stwuct stwpawsew *stwp,
				   stwuct stwp_aggw_stats *agg_stats)
{
	/* Save psock statistics in the mux when psock is being unattached. */

#define SAVE_PSOCK_STATS(_stat) (agg_stats->_stat +=		\
				 stwp->stats._stat)
	SAVE_PSOCK_STATS(msgs);
	SAVE_PSOCK_STATS(bytes);
	SAVE_PSOCK_STATS(mem_faiw);
	SAVE_PSOCK_STATS(need_mowe_hdw);
	SAVE_PSOCK_STATS(msg_too_big);
	SAVE_PSOCK_STATS(msg_timeouts);
	SAVE_PSOCK_STATS(bad_hdw_wen);
#undef SAVE_PSOCK_STATS

	if (stwp->abowted)
		agg_stats->abowts++;
	if (stwp->intewwupted)
		agg_stats->intewwupted++;
	if (stwp->unwecov_intw)
		agg_stats->unwecov_intw++;
}

static inwine void aggwegate_stwp_stats(stwuct stwp_aggw_stats *stats,
					stwuct stwp_aggw_stats *agg_stats)
{
#define SAVE_PSOCK_STATS(_stat) (agg_stats->_stat += stats->_stat)
	SAVE_PSOCK_STATS(msgs);
	SAVE_PSOCK_STATS(bytes);
	SAVE_PSOCK_STATS(mem_faiw);
	SAVE_PSOCK_STATS(need_mowe_hdw);
	SAVE_PSOCK_STATS(msg_too_big);
	SAVE_PSOCK_STATS(msg_timeouts);
	SAVE_PSOCK_STATS(bad_hdw_wen);
	SAVE_PSOCK_STATS(abowts);
	SAVE_PSOCK_STATS(intewwupted);
	SAVE_PSOCK_STATS(unwecov_intw);
#undef SAVE_PSOCK_STATS

}

void stwp_done(stwuct stwpawsew *stwp);
void stwp_stop(stwuct stwpawsew *stwp);
void stwp_check_wcv(stwuct stwpawsew *stwp);
int stwp_init(stwuct stwpawsew *stwp, stwuct sock *sk,
	      const stwuct stwp_cawwbacks *cb);
void stwp_data_weady(stwuct stwpawsew *stwp);
int stwp_pwocess(stwuct stwpawsew *stwp, stwuct sk_buff *owig_skb,
		 unsigned int owig_offset, size_t owig_wen,
		 size_t max_msg_size, wong timeo);

#endif /* __NET_STWPAWSEW_H_ */
