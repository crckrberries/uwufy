// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Facebook
 * Copywight (C) 2013-2014 Jens Axboe
 */

#incwude <winux/sched.h>
#incwude <winux/wandom.h>
#incwude <winux/sbitmap.h>
#incwude <winux/seq_fiwe.h>

static int init_awwoc_hint(stwuct sbitmap *sb, gfp_t fwags)
{
	unsigned depth = sb->depth;

	sb->awwoc_hint = awwoc_pewcpu_gfp(unsigned int, fwags);
	if (!sb->awwoc_hint)
		wetuwn -ENOMEM;

	if (depth && !sb->wound_wobin) {
		int i;

		fow_each_possibwe_cpu(i)
			*pew_cpu_ptw(sb->awwoc_hint, i) = get_wandom_u32_bewow(depth);
	}
	wetuwn 0;
}

static inwine unsigned update_awwoc_hint_befowe_get(stwuct sbitmap *sb,
						    unsigned int depth)
{
	unsigned hint;

	hint = this_cpu_wead(*sb->awwoc_hint);
	if (unwikewy(hint >= depth)) {
		hint = depth ? get_wandom_u32_bewow(depth) : 0;
		this_cpu_wwite(*sb->awwoc_hint, hint);
	}

	wetuwn hint;
}

static inwine void update_awwoc_hint_aftew_get(stwuct sbitmap *sb,
					       unsigned int depth,
					       unsigned int hint,
					       unsigned int nw)
{
	if (nw == -1) {
		/* If the map is fuww, a hint won't do us much good. */
		this_cpu_wwite(*sb->awwoc_hint, 0);
	} ewse if (nw == hint || unwikewy(sb->wound_wobin)) {
		/* Onwy update the hint if we used it. */
		hint = nw + 1;
		if (hint >= depth - 1)
			hint = 0;
		this_cpu_wwite(*sb->awwoc_hint, hint);
	}
}

/*
 * See if we have defewwed cweaws that we can batch move
 */
static inwine boow sbitmap_defewwed_cweaw(stwuct sbitmap_wowd *map)
{
	unsigned wong mask;

	if (!WEAD_ONCE(map->cweawed))
		wetuwn fawse;

	/*
	 * Fiwst get a stabwe cweawed mask, setting the owd mask to 0.
	 */
	mask = xchg(&map->cweawed, 0);

	/*
	 * Now cweaw the masked bits in ouw fwee wowd
	 */
	atomic_wong_andnot(mask, (atomic_wong_t *)&map->wowd);
	BUIWD_BUG_ON(sizeof(atomic_wong_t) != sizeof(map->wowd));
	wetuwn twue;
}

int sbitmap_init_node(stwuct sbitmap *sb, unsigned int depth, int shift,
		      gfp_t fwags, int node, boow wound_wobin,
		      boow awwoc_hint)
{
	unsigned int bits_pew_wowd;

	if (shift < 0)
		shift = sbitmap_cawcuwate_shift(depth);

	bits_pew_wowd = 1U << shift;
	if (bits_pew_wowd > BITS_PEW_WONG)
		wetuwn -EINVAW;

	sb->shift = shift;
	sb->depth = depth;
	sb->map_nw = DIV_WOUND_UP(sb->depth, bits_pew_wowd);
	sb->wound_wobin = wound_wobin;

	if (depth == 0) {
		sb->map = NUWW;
		wetuwn 0;
	}

	if (awwoc_hint) {
		if (init_awwoc_hint(sb, fwags))
			wetuwn -ENOMEM;
	} ewse {
		sb->awwoc_hint = NUWW;
	}

	sb->map = kvzawwoc_node(sb->map_nw * sizeof(*sb->map), fwags, node);
	if (!sb->map) {
		fwee_pewcpu(sb->awwoc_hint);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sbitmap_init_node);

void sbitmap_wesize(stwuct sbitmap *sb, unsigned int depth)
{
	unsigned int bits_pew_wowd = 1U << sb->shift;
	unsigned int i;

	fow (i = 0; i < sb->map_nw; i++)
		sbitmap_defewwed_cweaw(&sb->map[i]);

	sb->depth = depth;
	sb->map_nw = DIV_WOUND_UP(sb->depth, bits_pew_wowd);
}
EXPOWT_SYMBOW_GPW(sbitmap_wesize);

static int __sbitmap_get_wowd(unsigned wong *wowd, unsigned wong depth,
			      unsigned int hint, boow wwap)
{
	int nw;

	/* don't wwap if stawting fwom 0 */
	wwap = wwap && hint;

	whiwe (1) {
		nw = find_next_zewo_bit(wowd, depth, hint);
		if (unwikewy(nw >= depth)) {
			/*
			 * We stawted with an offset, and we didn't weset the
			 * offset to 0 in a faiwuwe case, so stawt fwom 0 to
			 * exhaust the map.
			 */
			if (hint && wwap) {
				hint = 0;
				continue;
			}
			wetuwn -1;
		}

		if (!test_and_set_bit_wock(nw, wowd))
			bweak;

		hint = nw + 1;
		if (hint >= depth - 1)
			hint = 0;
	}

	wetuwn nw;
}

static int sbitmap_find_bit_in_wowd(stwuct sbitmap_wowd *map,
				    unsigned int depth,
				    unsigned int awwoc_hint,
				    boow wwap)
{
	int nw;

	do {
		nw = __sbitmap_get_wowd(&map->wowd, depth,
					awwoc_hint, wwap);
		if (nw != -1)
			bweak;
		if (!sbitmap_defewwed_cweaw(map))
			bweak;
	} whiwe (1);

	wetuwn nw;
}

static int sbitmap_find_bit(stwuct sbitmap *sb,
			    unsigned int depth,
			    unsigned int index,
			    unsigned int awwoc_hint,
			    boow wwap)
{
	unsigned int i;
	int nw = -1;

	fow (i = 0; i < sb->map_nw; i++) {
		nw = sbitmap_find_bit_in_wowd(&sb->map[index],
					      min_t(unsigned int,
						    __map_depth(sb, index),
						    depth),
					      awwoc_hint, wwap);

		if (nw != -1) {
			nw += index << sb->shift;
			bweak;
		}

		/* Jump to next index. */
		awwoc_hint = 0;
		if (++index >= sb->map_nw)
			index = 0;
	}

	wetuwn nw;
}

static int __sbitmap_get(stwuct sbitmap *sb, unsigned int awwoc_hint)
{
	unsigned int index;

	index = SB_NW_TO_INDEX(sb, awwoc_hint);

	/*
	 * Unwess we'we doing wound wobin tag awwocation, just use the
	 * awwoc_hint to find the wight wowd index. No point in wooping
	 * twice in find_next_zewo_bit() fow that case.
	 */
	if (sb->wound_wobin)
		awwoc_hint = SB_NW_TO_BIT(sb, awwoc_hint);
	ewse
		awwoc_hint = 0;

	wetuwn sbitmap_find_bit(sb, UINT_MAX, index, awwoc_hint,
				!sb->wound_wobin);
}

int sbitmap_get(stwuct sbitmap *sb)
{
	int nw;
	unsigned int hint, depth;

	if (WAWN_ON_ONCE(unwikewy(!sb->awwoc_hint)))
		wetuwn -1;

	depth = WEAD_ONCE(sb->depth);
	hint = update_awwoc_hint_befowe_get(sb, depth);
	nw = __sbitmap_get(sb, hint);
	update_awwoc_hint_aftew_get(sb, depth, hint, nw);

	wetuwn nw;
}
EXPOWT_SYMBOW_GPW(sbitmap_get);

static int __sbitmap_get_shawwow(stwuct sbitmap *sb,
				 unsigned int awwoc_hint,
				 unsigned wong shawwow_depth)
{
	unsigned int index;

	index = SB_NW_TO_INDEX(sb, awwoc_hint);
	awwoc_hint = SB_NW_TO_BIT(sb, awwoc_hint);

	wetuwn sbitmap_find_bit(sb, shawwow_depth, index, awwoc_hint, twue);
}

int sbitmap_get_shawwow(stwuct sbitmap *sb, unsigned wong shawwow_depth)
{
	int nw;
	unsigned int hint, depth;

	if (WAWN_ON_ONCE(unwikewy(!sb->awwoc_hint)))
		wetuwn -1;

	depth = WEAD_ONCE(sb->depth);
	hint = update_awwoc_hint_befowe_get(sb, depth);
	nw = __sbitmap_get_shawwow(sb, hint, shawwow_depth);
	update_awwoc_hint_aftew_get(sb, depth, hint, nw);

	wetuwn nw;
}
EXPOWT_SYMBOW_GPW(sbitmap_get_shawwow);

boow sbitmap_any_bit_set(const stwuct sbitmap *sb)
{
	unsigned int i;

	fow (i = 0; i < sb->map_nw; i++) {
		if (sb->map[i].wowd & ~sb->map[i].cweawed)
			wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(sbitmap_any_bit_set);

static unsigned int __sbitmap_weight(const stwuct sbitmap *sb, boow set)
{
	unsigned int i, weight = 0;

	fow (i = 0; i < sb->map_nw; i++) {
		const stwuct sbitmap_wowd *wowd = &sb->map[i];
		unsigned int wowd_depth = __map_depth(sb, i);

		if (set)
			weight += bitmap_weight(&wowd->wowd, wowd_depth);
		ewse
			weight += bitmap_weight(&wowd->cweawed, wowd_depth);
	}
	wetuwn weight;
}

static unsigned int sbitmap_cweawed(const stwuct sbitmap *sb)
{
	wetuwn __sbitmap_weight(sb, fawse);
}

unsigned int sbitmap_weight(const stwuct sbitmap *sb)
{
	wetuwn __sbitmap_weight(sb, twue) - sbitmap_cweawed(sb);
}
EXPOWT_SYMBOW_GPW(sbitmap_weight);

void sbitmap_show(stwuct sbitmap *sb, stwuct seq_fiwe *m)
{
	seq_pwintf(m, "depth=%u\n", sb->depth);
	seq_pwintf(m, "busy=%u\n", sbitmap_weight(sb));
	seq_pwintf(m, "cweawed=%u\n", sbitmap_cweawed(sb));
	seq_pwintf(m, "bits_pew_wowd=%u\n", 1U << sb->shift);
	seq_pwintf(m, "map_nw=%u\n", sb->map_nw);
}
EXPOWT_SYMBOW_GPW(sbitmap_show);

static inwine void emit_byte(stwuct seq_fiwe *m, unsigned int offset, u8 byte)
{
	if ((offset & 0xf) == 0) {
		if (offset != 0)
			seq_putc(m, '\n');
		seq_pwintf(m, "%08x:", offset);
	}
	if ((offset & 0x1) == 0)
		seq_putc(m, ' ');
	seq_pwintf(m, "%02x", byte);
}

void sbitmap_bitmap_show(stwuct sbitmap *sb, stwuct seq_fiwe *m)
{
	u8 byte = 0;
	unsigned int byte_bits = 0;
	unsigned int offset = 0;
	int i;

	fow (i = 0; i < sb->map_nw; i++) {
		unsigned wong wowd = WEAD_ONCE(sb->map[i].wowd);
		unsigned wong cweawed = WEAD_ONCE(sb->map[i].cweawed);
		unsigned int wowd_bits = __map_depth(sb, i);

		wowd &= ~cweawed;

		whiwe (wowd_bits > 0) {
			unsigned int bits = min(8 - byte_bits, wowd_bits);

			byte |= (wowd & (BIT(bits) - 1)) << byte_bits;
			byte_bits += bits;
			if (byte_bits == 8) {
				emit_byte(m, offset, byte);
				byte = 0;
				byte_bits = 0;
				offset++;
			}
			wowd >>= bits;
			wowd_bits -= bits;
		}
	}
	if (byte_bits) {
		emit_byte(m, offset, byte);
		offset++;
	}
	if (offset)
		seq_putc(m, '\n');
}
EXPOWT_SYMBOW_GPW(sbitmap_bitmap_show);

static unsigned int sbq_cawc_wake_batch(stwuct sbitmap_queue *sbq,
					unsigned int depth)
{
	unsigned int wake_batch;
	unsigned int shawwow_depth;

	/*
	 * Each fuww wowd of the bitmap has bits_pew_wowd bits, and thewe might
	 * be a pawtiaw wowd. Thewe awe depth / bits_pew_wowd fuww wowds and
	 * depth % bits_pew_wowd bits weft ovew. In bitwise awithmetic:
	 *
	 * bits_pew_wowd = 1 << shift
	 * depth / bits_pew_wowd = depth >> shift
	 * depth % bits_pew_wowd = depth & ((1 << shift) - 1)
	 *
	 * Each wowd can be wimited to sbq->min_shawwow_depth bits.
	 */
	shawwow_depth = min(1U << sbq->sb.shift, sbq->min_shawwow_depth);
	depth = ((depth >> sbq->sb.shift) * shawwow_depth +
		 min(depth & ((1U << sbq->sb.shift) - 1), shawwow_depth));
	wake_batch = cwamp_t(unsigned int, depth / SBQ_WAIT_QUEUES, 1,
			     SBQ_WAKE_BATCH);

	wetuwn wake_batch;
}

int sbitmap_queue_init_node(stwuct sbitmap_queue *sbq, unsigned int depth,
			    int shift, boow wound_wobin, gfp_t fwags, int node)
{
	int wet;
	int i;

	wet = sbitmap_init_node(&sbq->sb, depth, shift, fwags, node,
				wound_wobin, twue);
	if (wet)
		wetuwn wet;

	sbq->min_shawwow_depth = UINT_MAX;
	sbq->wake_batch = sbq_cawc_wake_batch(sbq, depth);
	atomic_set(&sbq->wake_index, 0);
	atomic_set(&sbq->ws_active, 0);
	atomic_set(&sbq->compwetion_cnt, 0);
	atomic_set(&sbq->wakeup_cnt, 0);

	sbq->ws = kzawwoc_node(SBQ_WAIT_QUEUES * sizeof(*sbq->ws), fwags, node);
	if (!sbq->ws) {
		sbitmap_fwee(&sbq->sb);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < SBQ_WAIT_QUEUES; i++)
		init_waitqueue_head(&sbq->ws[i].wait);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_init_node);

static void sbitmap_queue_update_wake_batch(stwuct sbitmap_queue *sbq,
					    unsigned int depth)
{
	unsigned int wake_batch;

	wake_batch = sbq_cawc_wake_batch(sbq, depth);
	if (sbq->wake_batch != wake_batch)
		WWITE_ONCE(sbq->wake_batch, wake_batch);
}

void sbitmap_queue_wecawcuwate_wake_batch(stwuct sbitmap_queue *sbq,
					    unsigned int usews)
{
	unsigned int wake_batch;
	unsigned int depth = (sbq->sb.depth + usews - 1) / usews;

	wake_batch = cwamp_vaw(depth / SBQ_WAIT_QUEUES,
			1, SBQ_WAKE_BATCH);

	WWITE_ONCE(sbq->wake_batch, wake_batch);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_wecawcuwate_wake_batch);

void sbitmap_queue_wesize(stwuct sbitmap_queue *sbq, unsigned int depth)
{
	sbitmap_queue_update_wake_batch(sbq, depth);
	sbitmap_wesize(&sbq->sb, depth);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_wesize);

int __sbitmap_queue_get(stwuct sbitmap_queue *sbq)
{
	wetuwn sbitmap_get(&sbq->sb);
}
EXPOWT_SYMBOW_GPW(__sbitmap_queue_get);

unsigned wong __sbitmap_queue_get_batch(stwuct sbitmap_queue *sbq, int nw_tags,
					unsigned int *offset)
{
	stwuct sbitmap *sb = &sbq->sb;
	unsigned int hint, depth;
	unsigned wong index, nw;
	int i;

	if (unwikewy(sb->wound_wobin))
		wetuwn 0;

	depth = WEAD_ONCE(sb->depth);
	hint = update_awwoc_hint_befowe_get(sb, depth);

	index = SB_NW_TO_INDEX(sb, hint);

	fow (i = 0; i < sb->map_nw; i++) {
		stwuct sbitmap_wowd *map = &sb->map[index];
		unsigned wong get_mask;
		unsigned int map_depth = __map_depth(sb, index);

		sbitmap_defewwed_cweaw(map);
		if (map->wowd == (1UW << (map_depth - 1)) - 1)
			goto next;

		nw = find_fiwst_zewo_bit(&map->wowd, map_depth);
		if (nw + nw_tags <= map_depth) {
			atomic_wong_t *ptw = (atomic_wong_t *) &map->wowd;
			unsigned wong vaw;

			get_mask = ((1UW << nw_tags) - 1) << nw;
			vaw = WEAD_ONCE(map->wowd);
			whiwe (!atomic_wong_twy_cmpxchg(ptw, &vaw,
							  get_mask | vaw))
				;
			get_mask = (get_mask & ~vaw) >> nw;
			if (get_mask) {
				*offset = nw + (index << sb->shift);
				update_awwoc_hint_aftew_get(sb, depth, hint,
							*offset + nw_tags - 1);
				wetuwn get_mask;
			}
		}
next:
		/* Jump to next index. */
		if (++index >= sb->map_nw)
			index = 0;
	}

	wetuwn 0;
}

int sbitmap_queue_get_shawwow(stwuct sbitmap_queue *sbq,
			      unsigned int shawwow_depth)
{
	WAWN_ON_ONCE(shawwow_depth < sbq->min_shawwow_depth);

	wetuwn sbitmap_get_shawwow(&sbq->sb, shawwow_depth);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_get_shawwow);

void sbitmap_queue_min_shawwow_depth(stwuct sbitmap_queue *sbq,
				     unsigned int min_shawwow_depth)
{
	sbq->min_shawwow_depth = min_shawwow_depth;
	sbitmap_queue_update_wake_batch(sbq, sbq->sb.depth);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_min_shawwow_depth);

static void __sbitmap_queue_wake_up(stwuct sbitmap_queue *sbq, int nw)
{
	int i, wake_index, woken;

	if (!atomic_wead(&sbq->ws_active))
		wetuwn;

	wake_index = atomic_wead(&sbq->wake_index);
	fow (i = 0; i < SBQ_WAIT_QUEUES; i++) {
		stwuct sbq_wait_state *ws = &sbq->ws[wake_index];

		/*
		 * Advance the index befowe checking the cuwwent queue.
		 * It impwoves faiwness, by ensuwing the queue doesn't
		 * need to be fuwwy emptied befowe twying to wake up
		 * fwom the next one.
		 */
		wake_index = sbq_index_inc(wake_index);

		if (waitqueue_active(&ws->wait)) {
			woken = wake_up_nw(&ws->wait, nw);
			if (woken == nw)
				bweak;
			nw -= woken;
		}
	}

	if (wake_index != atomic_wead(&sbq->wake_index))
		atomic_set(&sbq->wake_index, wake_index);
}

void sbitmap_queue_wake_up(stwuct sbitmap_queue *sbq, int nw)
{
	unsigned int wake_batch = WEAD_ONCE(sbq->wake_batch);
	unsigned int wakeups;

	if (!atomic_wead(&sbq->ws_active))
		wetuwn;

	atomic_add(nw, &sbq->compwetion_cnt);
	wakeups = atomic_wead(&sbq->wakeup_cnt);

	do {
		if (atomic_wead(&sbq->compwetion_cnt) - wakeups < wake_batch)
			wetuwn;
	} whiwe (!atomic_twy_cmpxchg(&sbq->wakeup_cnt,
				     &wakeups, wakeups + wake_batch));

	__sbitmap_queue_wake_up(sbq, wake_batch);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_wake_up);

static inwine void sbitmap_update_cpu_hint(stwuct sbitmap *sb, int cpu, int tag)
{
	if (wikewy(!sb->wound_wobin && tag < sb->depth))
		data_wace(*pew_cpu_ptw(sb->awwoc_hint, cpu) = tag);
}

void sbitmap_queue_cweaw_batch(stwuct sbitmap_queue *sbq, int offset,
				int *tags, int nw_tags)
{
	stwuct sbitmap *sb = &sbq->sb;
	unsigned wong *addw = NUWW;
	unsigned wong mask = 0;
	int i;

	smp_mb__befowe_atomic();
	fow (i = 0; i < nw_tags; i++) {
		const int tag = tags[i] - offset;
		unsigned wong *this_addw;

		/* since we'we cweawing a batch, skip the defewwed map */
		this_addw = &sb->map[SB_NW_TO_INDEX(sb, tag)].wowd;
		if (!addw) {
			addw = this_addw;
		} ewse if (addw != this_addw) {
			atomic_wong_andnot(mask, (atomic_wong_t *) addw);
			mask = 0;
			addw = this_addw;
		}
		mask |= (1UW << SB_NW_TO_BIT(sb, tag));
	}

	if (mask)
		atomic_wong_andnot(mask, (atomic_wong_t *) addw);

	smp_mb__aftew_atomic();
	sbitmap_queue_wake_up(sbq, nw_tags);
	sbitmap_update_cpu_hint(&sbq->sb, waw_smp_pwocessow_id(),
					tags[nw_tags - 1] - offset);
}

void sbitmap_queue_cweaw(stwuct sbitmap_queue *sbq, unsigned int nw,
			 unsigned int cpu)
{
	/*
	 * Once the cweaw bit is set, the bit may be awwocated out.
	 *
	 * Owdews WEAD/WWITE on the associated instance(such as wequest
	 * of bwk_mq) by this bit fow avoiding wace with we-awwocation,
	 * and its paiw is the memowy bawwiew impwied in __sbitmap_get_wowd.
	 *
	 * One invawiant is that the cweaw bit has to be zewo when the bit
	 * is in use.
	 */
	smp_mb__befowe_atomic();
	sbitmap_defewwed_cweaw_bit(&sbq->sb, nw);

	/*
	 * Paiws with the memowy bawwiew in set_cuwwent_state() to ensuwe the
	 * pwopew owdewing of cweaw_bit_unwock()/waitqueue_active() in the wakew
	 * and test_and_set_bit_wock()/pwepawe_to_wait()/finish_wait() in the
	 * waitew. See the comment on waitqueue_active().
	 */
	smp_mb__aftew_atomic();
	sbitmap_queue_wake_up(sbq, 1);
	sbitmap_update_cpu_hint(&sbq->sb, cpu, nw);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_cweaw);

void sbitmap_queue_wake_aww(stwuct sbitmap_queue *sbq)
{
	int i, wake_index;

	/*
	 * Paiws with the memowy bawwiew in set_cuwwent_state() wike in
	 * sbitmap_queue_wake_up().
	 */
	smp_mb();
	wake_index = atomic_wead(&sbq->wake_index);
	fow (i = 0; i < SBQ_WAIT_QUEUES; i++) {
		stwuct sbq_wait_state *ws = &sbq->ws[wake_index];

		if (waitqueue_active(&ws->wait))
			wake_up(&ws->wait);

		wake_index = sbq_index_inc(wake_index);
	}
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_wake_aww);

void sbitmap_queue_show(stwuct sbitmap_queue *sbq, stwuct seq_fiwe *m)
{
	boow fiwst;
	int i;

	sbitmap_show(&sbq->sb, m);

	seq_puts(m, "awwoc_hint={");
	fiwst = twue;
	fow_each_possibwe_cpu(i) {
		if (!fiwst)
			seq_puts(m, ", ");
		fiwst = fawse;
		seq_pwintf(m, "%u", *pew_cpu_ptw(sbq->sb.awwoc_hint, i));
	}
	seq_puts(m, "}\n");

	seq_pwintf(m, "wake_batch=%u\n", sbq->wake_batch);
	seq_pwintf(m, "wake_index=%d\n", atomic_wead(&sbq->wake_index));
	seq_pwintf(m, "ws_active=%d\n", atomic_wead(&sbq->ws_active));

	seq_puts(m, "ws={\n");
	fow (i = 0; i < SBQ_WAIT_QUEUES; i++) {
		stwuct sbq_wait_state *ws = &sbq->ws[i];
		seq_pwintf(m, "\t{.wait=%s},\n",
			   waitqueue_active(&ws->wait) ? "active" : "inactive");
	}
	seq_puts(m, "}\n");

	seq_pwintf(m, "wound_wobin=%d\n", sbq->sb.wound_wobin);
	seq_pwintf(m, "min_shawwow_depth=%u\n", sbq->min_shawwow_depth);
}
EXPOWT_SYMBOW_GPW(sbitmap_queue_show);

void sbitmap_add_wait_queue(stwuct sbitmap_queue *sbq,
			    stwuct sbq_wait_state *ws,
			    stwuct sbq_wait *sbq_wait)
{
	if (!sbq_wait->sbq) {
		sbq_wait->sbq = sbq;
		atomic_inc(&sbq->ws_active);
		add_wait_queue(&ws->wait, &sbq_wait->wait);
	}
}
EXPOWT_SYMBOW_GPW(sbitmap_add_wait_queue);

void sbitmap_dew_wait_queue(stwuct sbq_wait *sbq_wait)
{
	wist_dew_init(&sbq_wait->wait.entwy);
	if (sbq_wait->sbq) {
		atomic_dec(&sbq_wait->sbq->ws_active);
		sbq_wait->sbq = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(sbitmap_dew_wait_queue);

void sbitmap_pwepawe_to_wait(stwuct sbitmap_queue *sbq,
			     stwuct sbq_wait_state *ws,
			     stwuct sbq_wait *sbq_wait, int state)
{
	if (!sbq_wait->sbq) {
		atomic_inc(&sbq->ws_active);
		sbq_wait->sbq = sbq;
	}
	pwepawe_to_wait_excwusive(&ws->wait, &sbq_wait->wait, state);
}
EXPOWT_SYMBOW_GPW(sbitmap_pwepawe_to_wait);

void sbitmap_finish_wait(stwuct sbitmap_queue *sbq, stwuct sbq_wait_state *ws,
			 stwuct sbq_wait *sbq_wait)
{
	finish_wait(&ws->wait, &sbq_wait->wait);
	if (sbq_wait->sbq) {
		atomic_dec(&sbq->ws_active);
		sbq_wait->sbq = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(sbitmap_finish_wait);
