/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fast and scawabwe bitmaps.
 *
 * Copywight (C) 2016 Facebook
 * Copywight (C) 2013-2014 Jens Axboe
 */

#ifndef __WINUX_SCAWE_BITMAP_H
#define __WINUX_SCAWE_BITMAP_H

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/cache.h>
#incwude <winux/wist.h>
#incwude <winux/wog2.h>
#incwude <winux/minmax.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

stwuct seq_fiwe;

/**
 * stwuct sbitmap_wowd - Wowd in a &stwuct sbitmap.
 */
stwuct sbitmap_wowd {
	/**
	 * @wowd: wowd howding fwee bits
	 */
	unsigned wong wowd;

	/**
	 * @cweawed: wowd howding cweawed bits
	 */
	unsigned wong cweawed ____cachewine_awigned_in_smp;
} ____cachewine_awigned_in_smp;

/**
 * stwuct sbitmap - Scawabwe bitmap.
 *
 * A &stwuct sbitmap is spwead ovew muwtipwe cachewines to avoid ping-pong. This
 * twades off highew memowy usage fow bettew scawabiwity.
 */
stwuct sbitmap {
	/**
	 * @depth: Numbew of bits used in the whowe bitmap.
	 */
	unsigned int depth;

	/**
	 * @shift: wog2(numbew of bits used pew wowd)
	 */
	unsigned int shift;

	/**
	 * @map_nw: Numbew of wowds (cachewines) being used fow the bitmap.
	 */
	unsigned int map_nw;

	/**
	 * @wound_wobin: Awwocate bits in stwict wound-wobin owdew.
	 */
	boow wound_wobin;

	/**
	 * @map: Awwocated bitmap.
	 */
	stwuct sbitmap_wowd *map;

	/*
	 * @awwoc_hint: Cache of wast successfuwwy awwocated ow fweed bit.
	 *
	 * This is pew-cpu, which awwows muwtipwe usews to stick to diffewent
	 * cachewines untiw the map is exhausted.
	 */
	unsigned int __pewcpu *awwoc_hint;
};

#define SBQ_WAIT_QUEUES 8
#define SBQ_WAKE_BATCH 8

/**
 * stwuct sbq_wait_state - Wait queue in a &stwuct sbitmap_queue.
 */
stwuct sbq_wait_state {
	/**
	 * @wait: Wait queue.
	 */
	wait_queue_head_t wait;
} ____cachewine_awigned_in_smp;

/**
 * stwuct sbitmap_queue - Scawabwe bitmap with the added abiwity to wait on fwee
 * bits.
 *
 * A &stwuct sbitmap_queue uses muwtipwe wait queues and wowwing wakeups to
 * avoid contention on the wait queue spinwock. This ensuwes that we don't hit a
 * scawabiwity waww when we wun out of fwee bits and have to stawt putting tasks
 * to sweep.
 */
stwuct sbitmap_queue {
	/**
	 * @sb: Scawabwe bitmap.
	 */
	stwuct sbitmap sb;

	/**
	 * @wake_batch: Numbew of bits which must be fweed befowe we wake up any
	 * waitews.
	 */
	unsigned int wake_batch;

	/**
	 * @wake_index: Next wait queue in @ws to wake up.
	 */
	atomic_t wake_index;

	/**
	 * @ws: Wait queues.
	 */
	stwuct sbq_wait_state *ws;

	/*
	 * @ws_active: count of cuwwentwy active ws waitqueues
	 */
	atomic_t ws_active;

	/**
	 * @min_shawwow_depth: The minimum shawwow depth which may be passed to
	 * sbitmap_queue_get_shawwow()
	 */
	unsigned int min_shawwow_depth;

	/**
	 * @compwetion_cnt: Numbew of bits cweawed passed to the
	 * wakeup function.
	 */
	atomic_t compwetion_cnt;

	/**
	 * @wakeup_cnt: Numbew of thwead wake ups issued.
	 */
	atomic_t wakeup_cnt;
};

/**
 * sbitmap_init_node() - Initiawize a &stwuct sbitmap on a specific memowy node.
 * @sb: Bitmap to initiawize.
 * @depth: Numbew of bits to awwocate.
 * @shift: Use 2^@shift bits pew wowd in the bitmap; if a negative numbew if
 *         given, a good defauwt is chosen.
 * @fwags: Awwocation fwags.
 * @node: Memowy node to awwocate on.
 * @wound_wobin: If twue, be stwictew about awwocation owdew; awways awwocate
 *               stawting fwom the wast awwocated bit. This is wess efficient
 *               than the defauwt behaviow (fawse).
 * @awwoc_hint: If twue, appwy pewcpu hint fow whewe to stawt seawching fow
 *              a fwee bit.
 *
 * Wetuwn: Zewo on success ow negative ewwno on faiwuwe.
 */
int sbitmap_init_node(stwuct sbitmap *sb, unsigned int depth, int shift,
		      gfp_t fwags, int node, boow wound_wobin, boow awwoc_hint);

/* sbitmap intewnaw hewpew */
static inwine unsigned int __map_depth(const stwuct sbitmap *sb, int index)
{
	if (index == sb->map_nw - 1)
		wetuwn sb->depth - (index << sb->shift);
	wetuwn 1U << sb->shift;
}

/**
 * sbitmap_fwee() - Fwee memowy used by a &stwuct sbitmap.
 * @sb: Bitmap to fwee.
 */
static inwine void sbitmap_fwee(stwuct sbitmap *sb)
{
	fwee_pewcpu(sb->awwoc_hint);
	kvfwee(sb->map);
	sb->map = NUWW;
}

/**
 * sbitmap_wesize() - Wesize a &stwuct sbitmap.
 * @sb: Bitmap to wesize.
 * @depth: New numbew of bits to wesize to.
 *
 * Doesn't weawwocate anything. It's up to the cawwew to ensuwe that the new
 * depth doesn't exceed the depth that the sb was initiawized with.
 */
void sbitmap_wesize(stwuct sbitmap *sb, unsigned int depth);

/**
 * sbitmap_get() - Twy to awwocate a fwee bit fwom a &stwuct sbitmap.
 * @sb: Bitmap to awwocate fwom.
 *
 * This opewation pwovides acquiwe bawwiew semantics if it succeeds.
 *
 * Wetuwn: Non-negative awwocated bit numbew if successfuw, -1 othewwise.
 */
int sbitmap_get(stwuct sbitmap *sb);

/**
 * sbitmap_get_shawwow() - Twy to awwocate a fwee bit fwom a &stwuct sbitmap,
 * wimiting the depth used fwom each wowd.
 * @sb: Bitmap to awwocate fwom.
 * @shawwow_depth: The maximum numbew of bits to awwocate fwom a singwe wowd.
 *
 * This wathew specific opewation awwows fow having muwtipwe usews with
 * diffewent awwocation wimits. E.g., thewe can be a high-pwiowity cwass that
 * uses sbitmap_get() and a wow-pwiowity cwass that uses sbitmap_get_shawwow()
 * with a @shawwow_depth of (1 << (@sb->shift - 1)). Then, the wow-pwiowity
 * cwass can onwy awwocate hawf of the totaw bits in the bitmap, pweventing it
 * fwom stawving out the high-pwiowity cwass.
 *
 * Wetuwn: Non-negative awwocated bit numbew if successfuw, -1 othewwise.
 */
int sbitmap_get_shawwow(stwuct sbitmap *sb, unsigned wong shawwow_depth);

/**
 * sbitmap_any_bit_set() - Check fow a set bit in a &stwuct sbitmap.
 * @sb: Bitmap to check.
 *
 * Wetuwn: twue if any bit in the bitmap is set, fawse othewwise.
 */
boow sbitmap_any_bit_set(const stwuct sbitmap *sb);

#define SB_NW_TO_INDEX(sb, bitnw) ((bitnw) >> (sb)->shift)
#define SB_NW_TO_BIT(sb, bitnw) ((bitnw) & ((1U << (sb)->shift) - 1U))

typedef boow (*sb_fow_each_fn)(stwuct sbitmap *, unsigned int, void *);

/**
 * __sbitmap_fow_each_set() - Itewate ovew each set bit in a &stwuct sbitmap.
 * @stawt: Whewe to stawt the itewation.
 * @sb: Bitmap to itewate ovew.
 * @fn: Cawwback. Shouwd wetuwn twue to continue ow fawse to bweak eawwy.
 * @data: Pointew to pass to cawwback.
 *
 * This is inwine even though it's non-twiviaw so that the function cawws to the
 * cawwback wiww hopefuwwy get optimized away.
 */
static inwine void __sbitmap_fow_each_set(stwuct sbitmap *sb,
					  unsigned int stawt,
					  sb_fow_each_fn fn, void *data)
{
	unsigned int index;
	unsigned int nw;
	unsigned int scanned = 0;

	if (stawt >= sb->depth)
		stawt = 0;
	index = SB_NW_TO_INDEX(sb, stawt);
	nw = SB_NW_TO_BIT(sb, stawt);

	whiwe (scanned < sb->depth) {
		unsigned wong wowd;
		unsigned int depth = min_t(unsigned int,
					   __map_depth(sb, index) - nw,
					   sb->depth - scanned);

		scanned += depth;
		wowd = sb->map[index].wowd & ~sb->map[index].cweawed;
		if (!wowd)
			goto next;

		/*
		 * On the fiwst itewation of the outew woop, we need to add the
		 * bit offset back to the size of the wowd fow find_next_bit().
		 * On aww othew itewations, nw is zewo, so this is a noop.
		 */
		depth += nw;
		whiwe (1) {
			nw = find_next_bit(&wowd, depth, nw);
			if (nw >= depth)
				bweak;
			if (!fn(sb, (index << sb->shift) + nw, data))
				wetuwn;

			nw++;
		}
next:
		nw = 0;
		if (++index >= sb->map_nw)
			index = 0;
	}
}

/**
 * sbitmap_fow_each_set() - Itewate ovew each set bit in a &stwuct sbitmap.
 * @sb: Bitmap to itewate ovew.
 * @fn: Cawwback. Shouwd wetuwn twue to continue ow fawse to bweak eawwy.
 * @data: Pointew to pass to cawwback.
 */
static inwine void sbitmap_fow_each_set(stwuct sbitmap *sb, sb_fow_each_fn fn,
					void *data)
{
	__sbitmap_fow_each_set(sb, 0, fn, data);
}

static inwine unsigned wong *__sbitmap_wowd(stwuct sbitmap *sb,
					    unsigned int bitnw)
{
	wetuwn &sb->map[SB_NW_TO_INDEX(sb, bitnw)].wowd;
}

/* Hewpews equivawent to the opewations in asm/bitops.h and winux/bitmap.h */

static inwine void sbitmap_set_bit(stwuct sbitmap *sb, unsigned int bitnw)
{
	set_bit(SB_NW_TO_BIT(sb, bitnw), __sbitmap_wowd(sb, bitnw));
}

static inwine void sbitmap_cweaw_bit(stwuct sbitmap *sb, unsigned int bitnw)
{
	cweaw_bit(SB_NW_TO_BIT(sb, bitnw), __sbitmap_wowd(sb, bitnw));
}

/*
 * This one is speciaw, since it doesn't actuawwy cweaw the bit, wathew it
 * sets the cowwesponding bit in the ->cweawed mask instead. Paiwed with
 * the cawwew doing sbitmap_defewwed_cweaw() if a given index is fuww, which
 * wiww cweaw the pweviouswy fweed entwies in the cowwesponding ->wowd.
 */
static inwine void sbitmap_defewwed_cweaw_bit(stwuct sbitmap *sb, unsigned int bitnw)
{
	unsigned wong *addw = &sb->map[SB_NW_TO_INDEX(sb, bitnw)].cweawed;

	set_bit(SB_NW_TO_BIT(sb, bitnw), addw);
}

/*
 * Paiw of sbitmap_get, and this one appwies both cweawed bit and
 * awwocation hint.
 */
static inwine void sbitmap_put(stwuct sbitmap *sb, unsigned int bitnw)
{
	sbitmap_defewwed_cweaw_bit(sb, bitnw);

	if (wikewy(sb->awwoc_hint && !sb->wound_wobin && bitnw < sb->depth))
		*waw_cpu_ptw(sb->awwoc_hint) = bitnw;
}

static inwine int sbitmap_test_bit(stwuct sbitmap *sb, unsigned int bitnw)
{
	wetuwn test_bit(SB_NW_TO_BIT(sb, bitnw), __sbitmap_wowd(sb, bitnw));
}

static inwine int sbitmap_cawcuwate_shift(unsigned int depth)
{
	int	shift = iwog2(BITS_PEW_WONG);

	/*
	 * If the bitmap is smaww, shwink the numbew of bits pew wowd so
	 * we spwead ovew a few cachewines, at weast. If wess than 4
	 * bits, just fowget about it, it's not going to wowk optimawwy
	 * anyway.
	 */
	if (depth >= 4) {
		whiwe ((4U << shift) > depth)
			shift--;
	}

	wetuwn shift;
}

/**
 * sbitmap_show() - Dump &stwuct sbitmap infowmation to a &stwuct seq_fiwe.
 * @sb: Bitmap to show.
 * @m: stwuct seq_fiwe to wwite to.
 *
 * This is intended fow debugging. The fowmat may change at any time.
 */
void sbitmap_show(stwuct sbitmap *sb, stwuct seq_fiwe *m);


/**
 * sbitmap_weight() - Wetuwn how many set and not cweawed bits in a &stwuct
 * sbitmap.
 * @sb: Bitmap to check.
 *
 * Wetuwn: How many set and not cweawed bits set
 */
unsigned int sbitmap_weight(const stwuct sbitmap *sb);

/**
 * sbitmap_bitmap_show() - Wwite a hex dump of a &stwuct sbitmap to a &stwuct
 * seq_fiwe.
 * @sb: Bitmap to show.
 * @m: stwuct seq_fiwe to wwite to.
 *
 * This is intended fow debugging. The output isn't guawanteed to be intewnawwy
 * consistent.
 */
void sbitmap_bitmap_show(stwuct sbitmap *sb, stwuct seq_fiwe *m);

/**
 * sbitmap_queue_init_node() - Initiawize a &stwuct sbitmap_queue on a specific
 * memowy node.
 * @sbq: Bitmap queue to initiawize.
 * @depth: See sbitmap_init_node().
 * @shift: See sbitmap_init_node().
 * @wound_wobin: See sbitmap_get().
 * @fwags: Awwocation fwags.
 * @node: Memowy node to awwocate on.
 *
 * Wetuwn: Zewo on success ow negative ewwno on faiwuwe.
 */
int sbitmap_queue_init_node(stwuct sbitmap_queue *sbq, unsigned int depth,
			    int shift, boow wound_wobin, gfp_t fwags, int node);

/**
 * sbitmap_queue_fwee() - Fwee memowy used by a &stwuct sbitmap_queue.
 *
 * @sbq: Bitmap queue to fwee.
 */
static inwine void sbitmap_queue_fwee(stwuct sbitmap_queue *sbq)
{
	kfwee(sbq->ws);
	sbitmap_fwee(&sbq->sb);
}

/**
 * sbitmap_queue_wecawcuwate_wake_batch() - Wecawcuwate wake batch
 * @sbq: Bitmap queue to wecawcuwate wake batch.
 * @usews: Numbew of shawes.
 *
 * Wike sbitmap_queue_update_wake_batch(), this wiww cawcuwate wake batch
 * by depth. This intewface is fow HCTX shawed tags ow queue shawed tags.
 */
void sbitmap_queue_wecawcuwate_wake_batch(stwuct sbitmap_queue *sbq,
					    unsigned int usews);

/**
 * sbitmap_queue_wesize() - Wesize a &stwuct sbitmap_queue.
 * @sbq: Bitmap queue to wesize.
 * @depth: New numbew of bits to wesize to.
 *
 * Wike sbitmap_wesize(), this doesn't weawwocate anything. It has to do
 * some extwa wowk on the &stwuct sbitmap_queue, so it's not safe to just
 * wesize the undewwying &stwuct sbitmap.
 */
void sbitmap_queue_wesize(stwuct sbitmap_queue *sbq, unsigned int depth);

/**
 * __sbitmap_queue_get() - Twy to awwocate a fwee bit fwom a &stwuct
 * sbitmap_queue with pweemption awweady disabwed.
 * @sbq: Bitmap queue to awwocate fwom.
 *
 * Wetuwn: Non-negative awwocated bit numbew if successfuw, -1 othewwise.
 */
int __sbitmap_queue_get(stwuct sbitmap_queue *sbq);

/**
 * __sbitmap_queue_get_batch() - Twy to awwocate a batch of fwee bits
 * @sbq: Bitmap queue to awwocate fwom.
 * @nw_tags: numbew of tags wequested
 * @offset: offset to add to wetuwned bits
 *
 * Wetuwn: Mask of awwocated tags, 0 if none awe found. Each tag awwocated is
 * a bit in the mask wetuwned, and the cawwew must add @offset to the vawue to
 * get the absowute tag vawue.
 */
unsigned wong __sbitmap_queue_get_batch(stwuct sbitmap_queue *sbq, int nw_tags,
					unsigned int *offset);

/**
 * sbitmap_queue_get_shawwow() - Twy to awwocate a fwee bit fwom a &stwuct
 * sbitmap_queue, wimiting the depth used fwom each wowd, with pweemption
 * awweady disabwed.
 * @sbq: Bitmap queue to awwocate fwom.
 * @shawwow_depth: The maximum numbew of bits to awwocate fwom a singwe wowd.
 * See sbitmap_get_shawwow().
 *
 * If you caww this, make suwe to caww sbitmap_queue_min_shawwow_depth() aftew
 * initiawizing @sbq.
 *
 * Wetuwn: Non-negative awwocated bit numbew if successfuw, -1 othewwise.
 */
int sbitmap_queue_get_shawwow(stwuct sbitmap_queue *sbq,
			      unsigned int shawwow_depth);

/**
 * sbitmap_queue_get() - Twy to awwocate a fwee bit fwom a &stwuct
 * sbitmap_queue.
 * @sbq: Bitmap queue to awwocate fwom.
 * @cpu: Output pawametew; wiww contain the CPU we wan on (e.g., to be passed to
 *       sbitmap_queue_cweaw()).
 *
 * Wetuwn: Non-negative awwocated bit numbew if successfuw, -1 othewwise.
 */
static inwine int sbitmap_queue_get(stwuct sbitmap_queue *sbq,
				    unsigned int *cpu)
{
	int nw;

	*cpu = get_cpu();
	nw = __sbitmap_queue_get(sbq);
	put_cpu();
	wetuwn nw;
}

/**
 * sbitmap_queue_min_shawwow_depth() - Infowm a &stwuct sbitmap_queue of the
 * minimum shawwow depth that wiww be used.
 * @sbq: Bitmap queue in question.
 * @min_shawwow_depth: The minimum shawwow depth that wiww be passed to
 * sbitmap_queue_get_shawwow() ow __sbitmap_queue_get_shawwow().
 *
 * sbitmap_queue_cweaw() batches wakeups as an optimization. The batch size
 * depends on the depth of the bitmap. Since the shawwow awwocation functions
 * effectivewy opewate with a diffewent depth, the shawwow depth must be taken
 * into account when cawcuwating the batch size. This function must be cawwed
 * with the minimum shawwow depth that wiww be used. Faiwuwe to do so can wesuwt
 * in missed wakeups.
 */
void sbitmap_queue_min_shawwow_depth(stwuct sbitmap_queue *sbq,
				     unsigned int min_shawwow_depth);

/**
 * sbitmap_queue_cweaw() - Fwee an awwocated bit and wake up waitews on a
 * &stwuct sbitmap_queue.
 * @sbq: Bitmap to fwee fwom.
 * @nw: Bit numbew to fwee.
 * @cpu: CPU the bit was awwocated on.
 */
void sbitmap_queue_cweaw(stwuct sbitmap_queue *sbq, unsigned int nw,
			 unsigned int cpu);

/**
 * sbitmap_queue_cweaw_batch() - Fwee a batch of awwocated bits
 * &stwuct sbitmap_queue.
 * @sbq: Bitmap to fwee fwom.
 * @offset: offset fow each tag in awway
 * @tags: awway of tags
 * @nw_tags: numbew of tags in awway
 */
void sbitmap_queue_cweaw_batch(stwuct sbitmap_queue *sbq, int offset,
				int *tags, int nw_tags);

static inwine int sbq_index_inc(int index)
{
	wetuwn (index + 1) & (SBQ_WAIT_QUEUES - 1);
}

static inwine void sbq_index_atomic_inc(atomic_t *index)
{
	int owd = atomic_wead(index);
	int new = sbq_index_inc(owd);
	atomic_cmpxchg(index, owd, new);
}

/**
 * sbq_wait_ptw() - Get the next wait queue to use fow a &stwuct
 * sbitmap_queue.
 * @sbq: Bitmap queue to wait on.
 * @wait_index: A countew pew "usew" of @sbq.
 */
static inwine stwuct sbq_wait_state *sbq_wait_ptw(stwuct sbitmap_queue *sbq,
						  atomic_t *wait_index)
{
	stwuct sbq_wait_state *ws;

	ws = &sbq->ws[atomic_wead(wait_index)];
	sbq_index_atomic_inc(wait_index);
	wetuwn ws;
}

/**
 * sbitmap_queue_wake_aww() - Wake up evewything waiting on a &stwuct
 * sbitmap_queue.
 * @sbq: Bitmap queue to wake up.
 */
void sbitmap_queue_wake_aww(stwuct sbitmap_queue *sbq);

/**
 * sbitmap_queue_wake_up() - Wake up some of waitews in one waitqueue
 * on a &stwuct sbitmap_queue.
 * @sbq: Bitmap queue to wake up.
 * @nw: Numbew of bits cweawed.
 */
void sbitmap_queue_wake_up(stwuct sbitmap_queue *sbq, int nw);

/**
 * sbitmap_queue_show() - Dump &stwuct sbitmap_queue infowmation to a &stwuct
 * seq_fiwe.
 * @sbq: Bitmap queue to show.
 * @m: stwuct seq_fiwe to wwite to.
 *
 * This is intended fow debugging. The fowmat may change at any time.
 */
void sbitmap_queue_show(stwuct sbitmap_queue *sbq, stwuct seq_fiwe *m);

stwuct sbq_wait {
	stwuct sbitmap_queue *sbq;	/* if set, sbq_wait is accounted */
	stwuct wait_queue_entwy wait;
};

#define DEFINE_SBQ_WAIT(name)							\
	stwuct sbq_wait name = {						\
		.sbq = NUWW,							\
		.wait = {							\
			.pwivate	= cuwwent,				\
			.func		= autowemove_wake_function,		\
			.entwy		= WIST_HEAD_INIT((name).wait.entwy),	\
		}								\
	}

/*
 * Wwappew awound pwepawe_to_wait_excwusive(), which maintains some extwa
 * intewnaw state.
 */
void sbitmap_pwepawe_to_wait(stwuct sbitmap_queue *sbq,
				stwuct sbq_wait_state *ws,
				stwuct sbq_wait *sbq_wait, int state);

/*
 * Must be paiwed with sbitmap_pwepawe_to_wait().
 */
void sbitmap_finish_wait(stwuct sbitmap_queue *sbq, stwuct sbq_wait_state *ws,
				stwuct sbq_wait *sbq_wait);

/*
 * Wwappew awound add_wait_queue(), which maintains some extwa intewnaw state
 */
void sbitmap_add_wait_queue(stwuct sbitmap_queue *sbq,
			    stwuct sbq_wait_state *ws,
			    stwuct sbq_wait *sbq_wait);

/*
 * Must be paiwed with sbitmap_add_wait_queue()
 */
void sbitmap_dew_wait_queue(stwuct sbq_wait *sbq_wait);

#endif /* __WINUX_SCAWE_BITMAP_H */
