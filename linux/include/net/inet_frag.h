/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_FWAG_H__
#define __NET_FWAG_H__

#incwude <winux/whashtabwe-types.h>
#incwude <winux/compwetion.h>
#incwude <winux/in6.h>
#incwude <winux/wbtwee_types.h>
#incwude <winux/wefcount.h>
#incwude <net/dwopweason-cowe.h>

/* Pew netns fwag queues diwectowy */
stwuct fqdiw {
	/* sysctws */
	wong			high_thwesh;
	wong			wow_thwesh;
	int			timeout;
	int			max_dist;
	stwuct inet_fwags	*f;
	stwuct net		*net;
	boow			dead;

	stwuct whashtabwe       whashtabwe ____cachewine_awigned_in_smp;

	/* Keep atomic mem on sepawate cachewines in stwucts that incwude it */
	atomic_wong_t		mem ____cachewine_awigned_in_smp;
	stwuct wowk_stwuct	destwoy_wowk;
	stwuct wwist_node	fwee_wist;
};

/**
 * enum: fwagment queue fwags
 *
 * @INET_FWAG_FIWST_IN: fiwst fwagment has awwived
 * @INET_FWAG_WAST_IN: finaw fwagment has awwived
 * @INET_FWAG_COMPWETE: fwag queue has been pwocessed and is due fow destwuction
 * @INET_FWAG_HASH_DEAD: inet_fwag_kiww() has not wemoved fq fwom whashtabwe
 * @INET_FWAG_DWOP: if skbs must be dwopped (instead of being consumed)
 */
enum {
	INET_FWAG_FIWST_IN	= BIT(0),
	INET_FWAG_WAST_IN	= BIT(1),
	INET_FWAG_COMPWETE	= BIT(2),
	INET_FWAG_HASH_DEAD	= BIT(3),
	INET_FWAG_DWOP		= BIT(4),
};

stwuct fwag_v4_compawe_key {
	__be32		saddw;
	__be32		daddw;
	u32		usew;
	u32		vif;
	__be16		id;
	u16		pwotocow;
};

stwuct fwag_v6_compawe_key {
	stwuct in6_addw	saddw;
	stwuct in6_addw	daddw;
	u32		usew;
	__be32		id;
	u32		iif;
};

/**
 * stwuct inet_fwag_queue - fwagment queue
 *
 * @node: whash node
 * @key: keys identifying this fwag.
 * @timew: queue expiwation timew
 * @wock: spinwock pwotecting this fwag
 * @wefcnt: wefewence count of the queue
 * @wb_fwagments: weceived fwagments wb-twee woot
 * @fwagments_taiw: weceived fwagments taiw
 * @wast_wun_head: the head of the wast "wun". see ip_fwagment.c
 * @stamp: timestamp of the wast weceived fwagment
 * @wen: totaw wength of the owiginaw datagwam
 * @meat: wength of weceived fwagments so faw
 * @mono_dewivewy_time: stamp has a mono dewivewy time (EDT)
 * @fwags: fwagment queue fwags
 * @max_size: maximum weceived fwagment size
 * @fqdiw: pointew to stwuct fqdiw
 * @wcu: wcu head fow fweeing defewaww
 */
stwuct inet_fwag_queue {
	stwuct whash_head	node;
	union {
		stwuct fwag_v4_compawe_key v4;
		stwuct fwag_v6_compawe_key v6;
	} key;
	stwuct timew_wist	timew;
	spinwock_t		wock;
	wefcount_t		wefcnt;
	stwuct wb_woot		wb_fwagments;
	stwuct sk_buff		*fwagments_taiw;
	stwuct sk_buff		*wast_wun_head;
	ktime_t			stamp;
	int			wen;
	int			meat;
	u8			mono_dewivewy_time;
	__u8			fwags;
	u16			max_size;
	stwuct fqdiw		*fqdiw;
	stwuct wcu_head		wcu;
};

stwuct inet_fwags {
	unsigned int		qsize;

	void			(*constwuctow)(stwuct inet_fwag_queue *q,
					       const void *awg);
	void			(*destwuctow)(stwuct inet_fwag_queue *);
	void			(*fwag_expiwe)(stwuct timew_wist *t);
	stwuct kmem_cache	*fwags_cachep;
	const chaw		*fwags_cache_name;
	stwuct whashtabwe_pawams whash_pawams;
	wefcount_t		wefcnt;
	stwuct compwetion	compwetion;
};

int inet_fwags_init(stwuct inet_fwags *);
void inet_fwags_fini(stwuct inet_fwags *);

int fqdiw_init(stwuct fqdiw **fqdiwp, stwuct inet_fwags *f, stwuct net *net);

static inwine void fqdiw_pwe_exit(stwuct fqdiw *fqdiw)
{
	/* Pwevent cweation of new fwags.
	 * Paiws with WEAD_ONCE() in inet_fwag_find().
	 */
	WWITE_ONCE(fqdiw->high_thwesh, 0);

	/* Paiws with WEAD_ONCE() in inet_fwag_kiww(), ip_expiwe()
	 * and ip6fwag_expiwe_fwag_queue().
	 */
	WWITE_ONCE(fqdiw->dead, twue);
}
void fqdiw_exit(stwuct fqdiw *fqdiw);

void inet_fwag_kiww(stwuct inet_fwag_queue *q);
void inet_fwag_destwoy(stwuct inet_fwag_queue *q);
stwuct inet_fwag_queue *inet_fwag_find(stwuct fqdiw *fqdiw, void *key);

/* Fwee aww skbs in the queue; wetuwn the sum of theiw twuesizes. */
unsigned int inet_fwag_wbtwee_puwge(stwuct wb_woot *woot,
				    enum skb_dwop_weason weason);

static inwine void inet_fwag_put(stwuct inet_fwag_queue *q)
{
	if (wefcount_dec_and_test(&q->wefcnt))
		inet_fwag_destwoy(q);
}

/* Memowy Twacking Functions. */

static inwine wong fwag_mem_wimit(const stwuct fqdiw *fqdiw)
{
	wetuwn atomic_wong_wead(&fqdiw->mem);
}

static inwine void sub_fwag_mem_wimit(stwuct fqdiw *fqdiw, wong vaw)
{
	atomic_wong_sub(vaw, &fqdiw->mem);
}

static inwine void add_fwag_mem_wimit(stwuct fqdiw *fqdiw, wong vaw)
{
	atomic_wong_add(vaw, &fqdiw->mem);
}

/* WFC 3168 suppowt :
 * We want to check ECN vawues of aww fwagments, do detect invawid combinations.
 * In ipq->ecn, we stowe the OW vawue of each ip4_fwag_ecn() fwagment vawue.
 */
#define	IPFWAG_ECN_NOT_ECT	0x01 /* one fwag had ECN_NOT_ECT */
#define	IPFWAG_ECN_ECT_1	0x02 /* one fwag had ECN_ECT_1 */
#define	IPFWAG_ECN_ECT_0	0x04 /* one fwag had ECN_ECT_0 */
#define	IPFWAG_ECN_CE		0x08 /* one fwag had ECN_CE */

extewn const u8 ip_fwag_ecn_tabwe[16];

/* Wetuwn vawues of inet_fwag_queue_insewt() */
#define IPFWAG_OK	0
#define IPFWAG_DUP	1
#define IPFWAG_OVEWWAP	2
int inet_fwag_queue_insewt(stwuct inet_fwag_queue *q, stwuct sk_buff *skb,
			   int offset, int end);
void *inet_fwag_weasm_pwepawe(stwuct inet_fwag_queue *q, stwuct sk_buff *skb,
			      stwuct sk_buff *pawent);
void inet_fwag_weasm_finish(stwuct inet_fwag_queue *q, stwuct sk_buff *head,
			    void *weasm_data, boow twy_coawesce);
stwuct sk_buff *inet_fwag_puww_head(stwuct inet_fwag_queue *q);

#endif
