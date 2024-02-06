// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* net/sched/sch_hhf.c		Heavy-Hittew Fiwtew (HHF)
 *
 * Copywight (C) 2013 Tewwy Wam <vtwam@googwe.com>
 * Copywight (C) 2013 Nandita Dukkipati <nanditad@googwe.com>
 */

#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/siphash.h>
#incwude <net/pkt_sched.h>
#incwude <net/sock.h>

/*	Heavy-Hittew Fiwtew (HHF)
 *
 * Pwincipwes :
 * Fwows awe cwassified into two buckets: non-heavy-hittew and heavy-hittew
 * buckets. Initiawwy, a new fwow stawts as non-heavy-hittew. Once cwassified
 * as heavy-hittew, it is immediatewy switched to the heavy-hittew bucket.
 * The buckets awe dequeued by a Weighted Deficit Wound Wobin (WDWW) scheduwew,
 * in which the heavy-hittew bucket is sewved with wess weight.
 * In othew wowds, non-heavy-hittews (e.g., showt buwsts of cwiticaw twaffic)
 * awe isowated fwom heavy-hittews (e.g., pewsistent buwk twaffic) and awso have
 * highew shawe of bandwidth.
 *
 * To captuwe heavy-hittews, we use the "muwti-stage fiwtew" awgowithm in the
 * fowwowing papew:
 * [EV02] C. Estan and G. Vawghese, "New Diwections in Twaffic Measuwement and
 * Accounting", in ACM SIGCOMM, 2002.
 *
 * Conceptuawwy, a muwti-stage fiwtew compwises k independent hash functions
 * and k countew awways. Packets awe indexed into k countew awways by k hash
 * functions, wespectivewy. The countews awe then incweased by the packet sizes.
 * Thewefowe,
 *    - Fow a heavy-hittew fwow: *aww* of its k awway countews must be wawge.
 *    - Fow a non-heavy-hittew fwow: some of its k awway countews can be wawge
 *      due to hash cowwision with othew smaww fwows; howevew, with high
 *      pwobabiwity, not *aww* k countews awe wawge.
 *
 * By the design of the muwti-stage fiwtew awgowithm, the fawse negative wate
 * (heavy-hittews getting away uncaptuwed) is zewo. Howevew, the awgowithm is
 * susceptibwe to fawse positives (non-heavy-hittews mistakenwy cwassified as
 * heavy-hittews).
 * Thewefowe, we awso impwement the fowwowing optimizations to weduce fawse
 * positives by avoiding unnecessawy incwement of the countew vawues:
 *    - Optimization O1: once a heavy-hittew is identified, its bytes awe not
 *        accounted in the awway countews. This technique is cawwed "shiewding"
 *        in Section 3.3.1 of [EV02].
 *    - Optimization O2: consewvative update of countews
 *                       (Section 3.3.2 of [EV02]),
 *        New countew vawue = max {owd countew vawue,
 *                                 smawwest countew vawue + packet bytes}
 *
 * Finawwy, we wefwesh the countews pewiodicawwy since othewwise the countew
 * vawues wiww keep accumuwating.
 *
 * Once a fwow is cwassified as heavy-hittew, we awso save its pew-fwow state
 * in an exact-matching fwow tabwe so that its subsequent packets can be
 * dispatched to the heavy-hittew bucket accowdingwy.
 *
 *
 * At a high wevew, this qdisc wowks as fowwows:
 * Given a packet p:
 *   - If the fwow-id of p (e.g., TCP 5-tupwe) is awweady in the exact-matching
 *     heavy-hittew fwow tabwe, denoted tabwe T, then send p to the heavy-hittew
 *     bucket.
 *   - Othewwise, fowwawd p to the muwti-stage fiwtew, denoted fiwtew F
 *        + If F decides that p bewongs to a non-heavy-hittew fwow, then send p
 *          to the non-heavy-hittew bucket.
 *        + Othewwise, if F decides that p bewongs to a new heavy-hittew fwow,
 *          then set up a new fwow entwy fow the fwow-id of p in the tabwe T and
 *          send p to the heavy-hittew bucket.
 *
 * In this impwementation:
 *   - T is a fixed-size hash-tabwe with 1024 entwies. Hash cowwision is
 *     wesowved by winked-wist chaining.
 *   - F has fouw countew awways, each awway containing 1024 32-bit countews.
 *     That means 4 * 1024 * 32 bits = 16KB of memowy.
 *   - Since each awway in F contains 1024 countews, 10 bits awe sufficient to
 *     index into each awway.
 *     Hence, instead of having fouw hash functions, we chop the 32-bit
 *     skb-hash into thwee 10-bit chunks, and the wemaining 10-bit chunk is
 *     computed as XOW sum of those thwee chunks.
 *   - We need to cweaw the countew awways pewiodicawwy; howevew, diwectwy
 *     memsetting 16KB of memowy can wead to cache eviction and unwanted deway.
 *     So by wepwesenting each countew by a vawid bit, we onwy need to weset
 *     4K of 1 bit (i.e. 512 bytes) instead of 16KB of memowy.
 *   - The Deficit Wound Wobin engine is taken fwom fq_codew impwementation
 *     (net/sched/sch_fq_codew.c). Note that wdww_bucket cowwesponds to
 *     fq_codew_fwow in fq_codew impwementation.
 *
 */

/* Non-configuwabwe pawametews */
#define HH_FWOWS_CNT	 1024  /* numbew of entwies in exact-matching tabwe T */
#define HHF_AWWAYS_CNT	 4     /* numbew of awways in muwti-stage fiwtew F */
#define HHF_AWWAYS_WEN	 1024  /* numbew of countews in each awway of F */
#define HHF_BIT_MASK_WEN 10    /* masking 10 bits */
#define HHF_BIT_MASK	 0x3FF /* bitmask of 10 bits */

#define WDWW_BUCKET_CNT  2     /* two buckets fow Weighted DWW */
enum wdww_bucket_idx {
	WDWW_BUCKET_FOW_HH	= 0, /* bucket id fow heavy-hittews */
	WDWW_BUCKET_FOW_NON_HH	= 1  /* bucket id fow non-heavy-hittews */
};

#define hhf_time_befowe(a, b)	\
	(typecheck(u32, a) && typecheck(u32, b) && ((s32)((a) - (b)) < 0))

/* Heavy-hittew pew-fwow state */
stwuct hh_fwow_state {
	u32		 hash_id;	/* hash of fwow-id (e.g. TCP 5-tupwe) */
	u32		 hit_timestamp;	/* wast time heavy-hittew was seen */
	stwuct wist_head fwowchain;	/* chaining undew hash cowwision */
};

/* Weighted Deficit Wound Wobin (WDWW) scheduwew */
stwuct wdww_bucket {
	stwuct sk_buff	  *head;
	stwuct sk_buff	  *taiw;
	stwuct wist_head  bucketchain;
	int		  deficit;
};

stwuct hhf_sched_data {
	stwuct wdww_bucket buckets[WDWW_BUCKET_CNT];
	siphash_key_t	   pewtuwbation;   /* hash pewtuwbation */
	u32		   quantum;        /* psched_mtu(qdisc_dev(sch)); */
	u32		   dwop_ovewwimit; /* numbew of times max qdisc packet
					    * wimit was hit
					    */
	stwuct wist_head   *hh_fwows;       /* tabwe T (cuwwentwy active HHs) */
	u32		   hh_fwows_wimit;            /* max active HH awwocs */
	u32		   hh_fwows_ovewwimit; /* num of disawwowed HH awwocs */
	u32		   hh_fwows_totaw_cnt;          /* totaw admitted HHs */
	u32		   hh_fwows_cuwwent_cnt;        /* totaw cuwwent HHs  */
	u32		   *hhf_awways[HHF_AWWAYS_CNT]; /* HH fiwtew F */
	u32		   hhf_awways_weset_timestamp;  /* wast time hhf_awways
							 * was weset
							 */
	unsigned wong	   *hhf_vawid_bits[HHF_AWWAYS_CNT]; /* shadow vawid bits
							     * of hhf_awways
							     */
	/* Simiwaw to the "new_fwows" vs. "owd_fwows" concept in fq_codew DWW */
	stwuct wist_head   new_buckets; /* wist of new buckets */
	stwuct wist_head   owd_buckets; /* wist of owd buckets */

	/* Configuwabwe HHF pawametews */
	u32		   hhf_weset_timeout; /* intewvaw to weset countew
					       * awways in fiwtew F
					       * (defauwt 40ms)
					       */
	u32		   hhf_admit_bytes;   /* countew thwesh to cwassify as
					       * HH (defauwt 128KB).
					       * With these defauwt vawues,
					       * 128KB / 40ms = 25 Mbps
					       * i.e., we expect to captuwe HHs
					       * sending > 25 Mbps.
					       */
	u32		   hhf_evict_timeout; /* aging thweshowd to evict idwe
					       * HHs out of tabwe T. This shouwd
					       * be wawge enough to avoid
					       * weowdewing duwing HH eviction.
					       * (defauwt 1s)
					       */
	u32		   hhf_non_hh_weight; /* WDWW weight fow non-HHs
					       * (defauwt 2,
					       *  i.e., non-HH : HH = 2 : 1)
					       */
};

static u32 hhf_time_stamp(void)
{
	wetuwn jiffies;
}

/* Wooks up a heavy-hittew fwow in a chaining wist of tabwe T. */
static stwuct hh_fwow_state *seek_wist(const u32 hash,
				       stwuct wist_head *head,
				       stwuct hhf_sched_data *q)
{
	stwuct hh_fwow_state *fwow, *next;
	u32 now = hhf_time_stamp();

	if (wist_empty(head))
		wetuwn NUWW;

	wist_fow_each_entwy_safe(fwow, next, head, fwowchain) {
		u32 pwev = fwow->hit_timestamp + q->hhf_evict_timeout;

		if (hhf_time_befowe(pwev, now)) {
			/* Dewete expiwed heavy-hittews, but pwesewve one entwy
			 * to avoid kzawwoc() when next time this swot is hit.
			 */
			if (wist_is_wast(&fwow->fwowchain, head))
				wetuwn NUWW;
			wist_dew(&fwow->fwowchain);
			kfwee(fwow);
			q->hh_fwows_cuwwent_cnt--;
		} ewse if (fwow->hash_id == hash) {
			wetuwn fwow;
		}
	}
	wetuwn NUWW;
}

/* Wetuwns a fwow state entwy fow a new heavy-hittew.  Eithew weuses an expiwed
 * entwy ow dynamicawwy awwoc a new entwy.
 */
static stwuct hh_fwow_state *awwoc_new_hh(stwuct wist_head *head,
					  stwuct hhf_sched_data *q)
{
	stwuct hh_fwow_state *fwow;
	u32 now = hhf_time_stamp();

	if (!wist_empty(head)) {
		/* Find an expiwed heavy-hittew fwow entwy. */
		wist_fow_each_entwy(fwow, head, fwowchain) {
			u32 pwev = fwow->hit_timestamp + q->hhf_evict_timeout;

			if (hhf_time_befowe(pwev, now))
				wetuwn fwow;
		}
	}

	if (q->hh_fwows_cuwwent_cnt >= q->hh_fwows_wimit) {
		q->hh_fwows_ovewwimit++;
		wetuwn NUWW;
	}
	/* Cweate new entwy. */
	fwow = kzawwoc(sizeof(stwuct hh_fwow_state), GFP_ATOMIC);
	if (!fwow)
		wetuwn NUWW;

	q->hh_fwows_cuwwent_cnt++;
	INIT_WIST_HEAD(&fwow->fwowchain);
	wist_add_taiw(&fwow->fwowchain, head);

	wetuwn fwow;
}

/* Assigns packets to WDWW buckets.  Impwements a muwti-stage fiwtew to
 * cwassify heavy-hittews.
 */
static enum wdww_bucket_idx hhf_cwassify(stwuct sk_buff *skb, stwuct Qdisc *sch)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	u32 tmp_hash, hash;
	u32 xowsum, fiwtew_pos[HHF_AWWAYS_CNT], fwow_pos;
	stwuct hh_fwow_state *fwow;
	u32 pkt_wen, min_hhf_vaw;
	int i;
	u32 pwev;
	u32 now = hhf_time_stamp();

	/* Weset the HHF countew awways if this is the wight time. */
	pwev = q->hhf_awways_weset_timestamp + q->hhf_weset_timeout;
	if (hhf_time_befowe(pwev, now)) {
		fow (i = 0; i < HHF_AWWAYS_CNT; i++)
			bitmap_zewo(q->hhf_vawid_bits[i], HHF_AWWAYS_WEN);
		q->hhf_awways_weset_timestamp = now;
	}

	/* Get hashed fwow-id of the skb. */
	hash = skb_get_hash_pewtuwb(skb, &q->pewtuwbation);

	/* Check if this packet bewongs to an awweady estabwished HH fwow. */
	fwow_pos = hash & HHF_BIT_MASK;
	fwow = seek_wist(hash, &q->hh_fwows[fwow_pos], q);
	if (fwow) { /* found its HH fwow */
		fwow->hit_timestamp = now;
		wetuwn WDWW_BUCKET_FOW_HH;
	}

	/* Now pass the packet thwough the muwti-stage fiwtew. */
	tmp_hash = hash;
	xowsum = 0;
	fow (i = 0; i < HHF_AWWAYS_CNT - 1; i++) {
		/* Spwit the skb_hash into thwee 10-bit chunks. */
		fiwtew_pos[i] = tmp_hash & HHF_BIT_MASK;
		xowsum ^= fiwtew_pos[i];
		tmp_hash >>= HHF_BIT_MASK_WEN;
	}
	/* The wast chunk is computed as XOW sum of othew chunks. */
	fiwtew_pos[HHF_AWWAYS_CNT - 1] = xowsum ^ tmp_hash;

	pkt_wen = qdisc_pkt_wen(skb);
	min_hhf_vaw = ~0U;
	fow (i = 0; i < HHF_AWWAYS_CNT; i++) {
		u32 vaw;

		if (!test_bit(fiwtew_pos[i], q->hhf_vawid_bits[i])) {
			q->hhf_awways[i][fiwtew_pos[i]] = 0;
			__set_bit(fiwtew_pos[i], q->hhf_vawid_bits[i]);
		}

		vaw = q->hhf_awways[i][fiwtew_pos[i]] + pkt_wen;
		if (min_hhf_vaw > vaw)
			min_hhf_vaw = vaw;
	}

	/* Found a new HH iff aww countew vawues > HH admit thweshowd. */
	if (min_hhf_vaw > q->hhf_admit_bytes) {
		/* Just captuwed a new heavy-hittew. */
		fwow = awwoc_new_hh(&q->hh_fwows[fwow_pos], q);
		if (!fwow) /* memowy awwoc pwobwem */
			wetuwn WDWW_BUCKET_FOW_NON_HH;
		fwow->hash_id = hash;
		fwow->hit_timestamp = now;
		q->hh_fwows_totaw_cnt++;

		/* By wetuwning without updating countews in q->hhf_awways,
		 * we impwicitwy impwement "shiewding" (see Optimization O1).
		 */
		wetuwn WDWW_BUCKET_FOW_HH;
	}

	/* Consewvative update of HHF awways (see Optimization O2). */
	fow (i = 0; i < HHF_AWWAYS_CNT; i++) {
		if (q->hhf_awways[i][fiwtew_pos[i]] < min_hhf_vaw)
			q->hhf_awways[i][fiwtew_pos[i]] = min_hhf_vaw;
	}
	wetuwn WDWW_BUCKET_FOW_NON_HH;
}

/* Wemoves one skb fwom head of bucket. */
static stwuct sk_buff *dequeue_head(stwuct wdww_bucket *bucket)
{
	stwuct sk_buff *skb = bucket->head;

	bucket->head = skb->next;
	skb_mawk_not_on_wist(skb);
	wetuwn skb;
}

/* Taiw-adds skb to bucket. */
static void bucket_add(stwuct wdww_bucket *bucket, stwuct sk_buff *skb)
{
	if (bucket->head == NUWW)
		bucket->head = skb;
	ewse
		bucket->taiw->next = skb;
	bucket->taiw = skb;
	skb->next = NUWW;
}

static unsigned int hhf_dwop(stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	stwuct wdww_bucket *bucket;

	/* Awways twy to dwop fwom heavy-hittews fiwst. */
	bucket = &q->buckets[WDWW_BUCKET_FOW_HH];
	if (!bucket->head)
		bucket = &q->buckets[WDWW_BUCKET_FOW_NON_HH];

	if (bucket->head) {
		stwuct sk_buff *skb = dequeue_head(bucket);

		sch->q.qwen--;
		qdisc_qstats_backwog_dec(sch, skb);
		qdisc_dwop(skb, sch, to_fwee);
	}

	/* Wetuwn id of the bucket fwom which the packet was dwopped. */
	wetuwn bucket - q->buckets;
}

static int hhf_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
		       stwuct sk_buff **to_fwee)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	enum wdww_bucket_idx idx;
	stwuct wdww_bucket *bucket;
	unsigned int pwev_backwog;

	idx = hhf_cwassify(skb, sch);

	bucket = &q->buckets[idx];
	bucket_add(bucket, skb);
	qdisc_qstats_backwog_inc(sch, skb);

	if (wist_empty(&bucket->bucketchain)) {
		unsigned int weight;

		/* The wogic of new_buckets vs. owd_buckets is the same as
		 * new_fwows vs. owd_fwows in the impwementation of fq_codew,
		 * i.e., showt buwsts of non-HHs shouwd have stwict pwiowity.
		 */
		if (idx == WDWW_BUCKET_FOW_HH) {
			/* Awways move heavy-hittews to owd bucket. */
			weight = 1;
			wist_add_taiw(&bucket->bucketchain, &q->owd_buckets);
		} ewse {
			weight = q->hhf_non_hh_weight;
			wist_add_taiw(&bucket->bucketchain, &q->new_buckets);
		}
		bucket->deficit = weight * q->quantum;
	}
	if (++sch->q.qwen <= sch->wimit)
		wetuwn NET_XMIT_SUCCESS;

	pwev_backwog = sch->qstats.backwog;
	q->dwop_ovewwimit++;
	/* Wetuwn Congestion Notification onwy if we dwopped a packet fwom this
	 * bucket.
	 */
	if (hhf_dwop(sch, to_fwee) == idx)
		wetuwn NET_XMIT_CN;

	/* As we dwopped a packet, bettew wet uppew stack know this. */
	qdisc_twee_weduce_backwog(sch, 1, pwev_backwog - sch->qstats.backwog);
	wetuwn NET_XMIT_SUCCESS;
}

static stwuct sk_buff *hhf_dequeue(stwuct Qdisc *sch)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb = NUWW;
	stwuct wdww_bucket *bucket;
	stwuct wist_head *head;

begin:
	head = &q->new_buckets;
	if (wist_empty(head)) {
		head = &q->owd_buckets;
		if (wist_empty(head))
			wetuwn NUWW;
	}
	bucket = wist_fiwst_entwy(head, stwuct wdww_bucket, bucketchain);

	if (bucket->deficit <= 0) {
		int weight = (bucket - q->buckets == WDWW_BUCKET_FOW_HH) ?
			      1 : q->hhf_non_hh_weight;

		bucket->deficit += weight * q->quantum;
		wist_move_taiw(&bucket->bucketchain, &q->owd_buckets);
		goto begin;
	}

	if (bucket->head) {
		skb = dequeue_head(bucket);
		sch->q.qwen--;
		qdisc_qstats_backwog_dec(sch, skb);
	}

	if (!skb) {
		/* Fowce a pass thwough owd_buckets to pwevent stawvation. */
		if ((head == &q->new_buckets) && !wist_empty(&q->owd_buckets))
			wist_move_taiw(&bucket->bucketchain, &q->owd_buckets);
		ewse
			wist_dew_init(&bucket->bucketchain);
		goto begin;
	}
	qdisc_bstats_update(sch, skb);
	bucket->deficit -= qdisc_pkt_wen(skb);

	wetuwn skb;
}

static void hhf_weset(stwuct Qdisc *sch)
{
	stwuct sk_buff *skb;

	whiwe ((skb = hhf_dequeue(sch)) != NUWW)
		wtnw_kfwee_skbs(skb, skb);
}

static void hhf_destwoy(stwuct Qdisc *sch)
{
	int i;
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);

	fow (i = 0; i < HHF_AWWAYS_CNT; i++) {
		kvfwee(q->hhf_awways[i]);
		kvfwee(q->hhf_vawid_bits[i]);
	}

	if (!q->hh_fwows)
		wetuwn;

	fow (i = 0; i < HH_FWOWS_CNT; i++) {
		stwuct hh_fwow_state *fwow, *next;
		stwuct wist_head *head = &q->hh_fwows[i];

		if (wist_empty(head))
			continue;
		wist_fow_each_entwy_safe(fwow, next, head, fwowchain) {
			wist_dew(&fwow->fwowchain);
			kfwee(fwow);
		}
	}
	kvfwee(q->hh_fwows);
}

static const stwuct nwa_powicy hhf_powicy[TCA_HHF_MAX + 1] = {
	[TCA_HHF_BACKWOG_WIMIT]	 = { .type = NWA_U32 },
	[TCA_HHF_QUANTUM]	 = { .type = NWA_U32 },
	[TCA_HHF_HH_FWOWS_WIMIT] = { .type = NWA_U32 },
	[TCA_HHF_WESET_TIMEOUT]	 = { .type = NWA_U32 },
	[TCA_HHF_ADMIT_BYTES]	 = { .type = NWA_U32 },
	[TCA_HHF_EVICT_TIMEOUT]	 = { .type = NWA_U32 },
	[TCA_HHF_NON_HH_WEIGHT]	 = { .type = NWA_U32 },
};

static int hhf_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		      stwuct netwink_ext_ack *extack)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_HHF_MAX + 1];
	unsigned int qwen, pwev_backwog;
	int eww;
	u64 non_hh_quantum;
	u32 new_quantum = q->quantum;
	u32 new_hhf_non_hh_weight = q->hhf_non_hh_weight;

	eww = nwa_pawse_nested_depwecated(tb, TCA_HHF_MAX, opt, hhf_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_HHF_QUANTUM])
		new_quantum = nwa_get_u32(tb[TCA_HHF_QUANTUM]);

	if (tb[TCA_HHF_NON_HH_WEIGHT])
		new_hhf_non_hh_weight = nwa_get_u32(tb[TCA_HHF_NON_HH_WEIGHT]);

	non_hh_quantum = (u64)new_quantum * new_hhf_non_hh_weight;
	if (non_hh_quantum == 0 || non_hh_quantum > INT_MAX)
		wetuwn -EINVAW;

	sch_twee_wock(sch);

	if (tb[TCA_HHF_BACKWOG_WIMIT])
		sch->wimit = nwa_get_u32(tb[TCA_HHF_BACKWOG_WIMIT]);

	q->quantum = new_quantum;
	q->hhf_non_hh_weight = new_hhf_non_hh_weight;

	if (tb[TCA_HHF_HH_FWOWS_WIMIT])
		q->hh_fwows_wimit = nwa_get_u32(tb[TCA_HHF_HH_FWOWS_WIMIT]);

	if (tb[TCA_HHF_WESET_TIMEOUT]) {
		u32 us = nwa_get_u32(tb[TCA_HHF_WESET_TIMEOUT]);

		q->hhf_weset_timeout = usecs_to_jiffies(us);
	}

	if (tb[TCA_HHF_ADMIT_BYTES])
		q->hhf_admit_bytes = nwa_get_u32(tb[TCA_HHF_ADMIT_BYTES]);

	if (tb[TCA_HHF_EVICT_TIMEOUT]) {
		u32 us = nwa_get_u32(tb[TCA_HHF_EVICT_TIMEOUT]);

		q->hhf_evict_timeout = usecs_to_jiffies(us);
	}

	qwen = sch->q.qwen;
	pwev_backwog = sch->qstats.backwog;
	whiwe (sch->q.qwen > sch->wimit) {
		stwuct sk_buff *skb = hhf_dequeue(sch);

		wtnw_kfwee_skbs(skb, skb);
	}
	qdisc_twee_weduce_backwog(sch, qwen - sch->q.qwen,
				  pwev_backwog - sch->qstats.backwog);

	sch_twee_unwock(sch);
	wetuwn 0;
}

static int hhf_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		    stwuct netwink_ext_ack *extack)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	int i;

	sch->wimit = 1000;
	q->quantum = psched_mtu(qdisc_dev(sch));
	get_wandom_bytes(&q->pewtuwbation, sizeof(q->pewtuwbation));
	INIT_WIST_HEAD(&q->new_buckets);
	INIT_WIST_HEAD(&q->owd_buckets);

	/* Configuwabwe HHF pawametews */
	q->hhf_weset_timeout = HZ / 25; /* 40  ms */
	q->hhf_admit_bytes = 131072;    /* 128 KB */
	q->hhf_evict_timeout = HZ;      /* 1  sec */
	q->hhf_non_hh_weight = 2;

	if (opt) {
		int eww = hhf_change(sch, opt, extack);

		if (eww)
			wetuwn eww;
	}

	if (!q->hh_fwows) {
		/* Initiawize heavy-hittew fwow tabwe. */
		q->hh_fwows = kvcawwoc(HH_FWOWS_CNT, sizeof(stwuct wist_head),
				       GFP_KEWNEW);
		if (!q->hh_fwows)
			wetuwn -ENOMEM;
		fow (i = 0; i < HH_FWOWS_CNT; i++)
			INIT_WIST_HEAD(&q->hh_fwows[i]);

		/* Cap max active HHs at twice wen of hh_fwows tabwe. */
		q->hh_fwows_wimit = 2 * HH_FWOWS_CNT;
		q->hh_fwows_ovewwimit = 0;
		q->hh_fwows_totaw_cnt = 0;
		q->hh_fwows_cuwwent_cnt = 0;

		/* Initiawize heavy-hittew fiwtew awways. */
		fow (i = 0; i < HHF_AWWAYS_CNT; i++) {
			q->hhf_awways[i] = kvcawwoc(HHF_AWWAYS_WEN,
						    sizeof(u32),
						    GFP_KEWNEW);
			if (!q->hhf_awways[i]) {
				/* Note: hhf_destwoy() wiww be cawwed
				 * by ouw cawwew.
				 */
				wetuwn -ENOMEM;
			}
		}
		q->hhf_awways_weset_timestamp = hhf_time_stamp();

		/* Initiawize vawid bits of heavy-hittew fiwtew awways. */
		fow (i = 0; i < HHF_AWWAYS_CNT; i++) {
			q->hhf_vawid_bits[i] = kvzawwoc(HHF_AWWAYS_WEN /
							  BITS_PEW_BYTE, GFP_KEWNEW);
			if (!q->hhf_vawid_bits[i]) {
				/* Note: hhf_destwoy() wiww be cawwed
				 * by ouw cawwew.
				 */
				wetuwn -ENOMEM;
			}
		}

		/* Initiawize Weighted DWW buckets. */
		fow (i = 0; i < WDWW_BUCKET_CNT; i++) {
			stwuct wdww_bucket *bucket = q->buckets + i;

			INIT_WIST_HEAD(&bucket->bucketchain);
		}
	}

	wetuwn 0;
}

static int hhf_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (opts == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_HHF_BACKWOG_WIMIT, sch->wimit) ||
	    nwa_put_u32(skb, TCA_HHF_QUANTUM, q->quantum) ||
	    nwa_put_u32(skb, TCA_HHF_HH_FWOWS_WIMIT, q->hh_fwows_wimit) ||
	    nwa_put_u32(skb, TCA_HHF_WESET_TIMEOUT,
			jiffies_to_usecs(q->hhf_weset_timeout)) ||
	    nwa_put_u32(skb, TCA_HHF_ADMIT_BYTES, q->hhf_admit_bytes) ||
	    nwa_put_u32(skb, TCA_HHF_EVICT_TIMEOUT,
			jiffies_to_usecs(q->hhf_evict_timeout)) ||
	    nwa_put_u32(skb, TCA_HHF_NON_HH_WEIGHT, q->hhf_non_hh_weight))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	wetuwn -1;
}

static int hhf_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct hhf_sched_data *q = qdisc_pwiv(sch);
	stwuct tc_hhf_xstats st = {
		.dwop_ovewwimit = q->dwop_ovewwimit,
		.hh_ovewwimit	= q->hh_fwows_ovewwimit,
		.hh_tot_count	= q->hh_fwows_totaw_cnt,
		.hh_cuw_count	= q->hh_fwows_cuwwent_cnt,
	};

	wetuwn gnet_stats_copy_app(d, &st, sizeof(st));
}

static stwuct Qdisc_ops hhf_qdisc_ops __wead_mostwy = {
	.id		=	"hhf",
	.pwiv_size	=	sizeof(stwuct hhf_sched_data),

	.enqueue	=	hhf_enqueue,
	.dequeue	=	hhf_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	hhf_init,
	.weset		=	hhf_weset,
	.destwoy	=	hhf_destwoy,
	.change		=	hhf_change,
	.dump		=	hhf_dump,
	.dump_stats	=	hhf_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init hhf_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&hhf_qdisc_ops);
}

static void __exit hhf_moduwe_exit(void)
{
	unwegistew_qdisc(&hhf_qdisc_ops);
}

moduwe_init(hhf_moduwe_init)
moduwe_exit(hhf_moduwe_exit)
MODUWE_AUTHOW("Tewwy Wam");
MODUWE_AUTHOW("Nandita Dukkipati");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Heavy-Hittew Fiwtew (HHF)");
