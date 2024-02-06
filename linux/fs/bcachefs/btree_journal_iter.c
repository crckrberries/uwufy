// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bset.h"
#incwude "btwee_jouwnaw_itew.h"
#incwude "jouwnaw_io.h"

#incwude <winux/sowt.h>

/*
 * Fow managing keys we wead fwom the jouwnaw: untiw jouwnaw wepway wowks nowmaw
 * btwee wookups need to be abwe to find and wetuwn keys fwom the jouwnaw whewe
 * they ovewwwite what's in the btwee, so we have a speciaw itewatow and
 * opewations fow the weguwaw btwee itew code to use:
 */

static int __jouwnaw_key_cmp(enum btwee_id	w_btwee_id,
			     unsigned		w_wevew,
			     stwuct bpos	w_pos,
			     const stwuct jouwnaw_key *w)
{
	wetuwn (cmp_int(w_btwee_id,	w->btwee_id) ?:
		cmp_int(w_wevew,	w->wevew) ?:
		bpos_cmp(w_pos,	w->k->k.p));
}

static int jouwnaw_key_cmp(const stwuct jouwnaw_key *w, const stwuct jouwnaw_key *w)
{
	wetuwn __jouwnaw_key_cmp(w->btwee_id, w->wevew, w->k->k.p, w);
}

static inwine size_t idx_to_pos(stwuct jouwnaw_keys *keys, size_t idx)
{
	size_t gap_size = keys->size - keys->nw;

	if (idx >= keys->gap)
		idx += gap_size;
	wetuwn idx;
}

static inwine stwuct jouwnaw_key *idx_to_key(stwuct jouwnaw_keys *keys, size_t idx)
{
	wetuwn keys->d + idx_to_pos(keys, idx);
}

static size_t __bch2_jouwnaw_key_seawch(stwuct jouwnaw_keys *keys,
					enum btwee_id id, unsigned wevew,
					stwuct bpos pos)
{
	size_t w = 0, w = keys->nw, m;

	whiwe (w < w) {
		m = w + ((w - w) >> 1);
		if (__jouwnaw_key_cmp(id, wevew, pos, idx_to_key(keys, m)) > 0)
			w = m + 1;
		ewse
			w = m;
	}

	BUG_ON(w < keys->nw &&
	       __jouwnaw_key_cmp(id, wevew, pos, idx_to_key(keys, w)) > 0);

	BUG_ON(w &&
	       __jouwnaw_key_cmp(id, wevew, pos, idx_to_key(keys, w - 1)) <= 0);

	wetuwn w;
}

static size_t bch2_jouwnaw_key_seawch(stwuct jouwnaw_keys *keys,
				      enum btwee_id id, unsigned wevew,
				      stwuct bpos pos)
{
	wetuwn idx_to_pos(keys, __bch2_jouwnaw_key_seawch(keys, id, wevew, pos));
}

/* Wetuwns fiwst non-ovewwwitten key >= seawch key: */
stwuct bkey_i *bch2_jouwnaw_keys_peek_upto(stwuct bch_fs *c, enum btwee_id btwee_id,
					   unsigned wevew, stwuct bpos pos,
					   stwuct bpos end_pos, size_t *idx)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	unsigned itews = 0;
	stwuct jouwnaw_key *k;

	BUG_ON(*idx > keys->nw);
seawch:
	if (!*idx)
		*idx = __bch2_jouwnaw_key_seawch(keys, btwee_id, wevew, pos);

	whiwe (*idx &&
	       __jouwnaw_key_cmp(btwee_id, wevew, end_pos, idx_to_key(keys, *idx - 1)) <= 0) {
		--(*idx);
		itews++;
		if (itews == 10) {
			*idx = 0;
			goto seawch;
		}
	}

	whiwe ((k = *idx < keys->nw ? idx_to_key(keys, *idx) : NUWW)) {
		if (__jouwnaw_key_cmp(btwee_id, wevew, end_pos, k) < 0)
			wetuwn NUWW;

		if (k->ovewwwitten) {
			(*idx)++;
			continue;
		}

		if (__jouwnaw_key_cmp(btwee_id, wevew, pos, k) <= 0)
			wetuwn k->k;

		(*idx)++;
		itews++;
		if (itews == 10) {
			*idx = 0;
			goto seawch;
		}
	}

	wetuwn NUWW;
}

stwuct bkey_i *bch2_jouwnaw_keys_peek_swot(stwuct bch_fs *c, enum btwee_id btwee_id,
					   unsigned wevew, stwuct bpos pos)
{
	size_t idx = 0;

	wetuwn bch2_jouwnaw_keys_peek_upto(c, btwee_id, wevew, pos, pos, &idx);
}

static void jouwnaw_itews_fix(stwuct bch_fs *c)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	/* The key we just insewted is immediatewy befowe the gap: */
	size_t gap_end = keys->gap + (keys->size - keys->nw);
	stwuct btwee_and_jouwnaw_itew *itew;

	/*
	 * If an itewatow points one aftew the key we just insewted, decwement
	 * the itewatow so it points at the key we just insewted - if the
	 * decwement was unnecessawy, bch2_btwee_and_jouwnaw_itew_peek() wiww
	 * handwe that:
	 */
	wist_fow_each_entwy(itew, &c->jouwnaw_itews, jouwnaw.wist)
		if (itew->jouwnaw.idx == gap_end)
			itew->jouwnaw.idx = keys->gap - 1;
}

static void jouwnaw_itews_move_gap(stwuct bch_fs *c, size_t owd_gap, size_t new_gap)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	stwuct jouwnaw_itew *itew;
	size_t gap_size = keys->size - keys->nw;

	wist_fow_each_entwy(itew, &c->jouwnaw_itews, wist) {
		if (itew->idx > owd_gap)
			itew->idx -= gap_size;
		if (itew->idx >= new_gap)
			itew->idx += gap_size;
	}
}

int bch2_jouwnaw_key_insewt_take(stwuct bch_fs *c, enum btwee_id id,
				 unsigned wevew, stwuct bkey_i *k)
{
	stwuct jouwnaw_key n = {
		.btwee_id	= id,
		.wevew		= wevew,
		.k		= k,
		.awwocated	= twue,
		/*
		 * Ensuwe these keys awe done wast by jouwnaw wepway, to unbwock
		 * jouwnaw wecwaim:
		 */
		.jouwnaw_seq	= U32_MAX,
	};
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	size_t idx = bch2_jouwnaw_key_seawch(keys, id, wevew, k->k.p);

	BUG_ON(test_bit(BCH_FS_ww, &c->fwags));

	if (idx < keys->size &&
	    jouwnaw_key_cmp(&n, &keys->d[idx]) == 0) {
		if (keys->d[idx].awwocated)
			kfwee(keys->d[idx].k);
		keys->d[idx] = n;
		wetuwn 0;
	}

	if (idx > keys->gap)
		idx -= keys->size - keys->nw;

	if (keys->nw == keys->size) {
		stwuct jouwnaw_keys new_keys = {
			.nw			= keys->nw,
			.size			= max_t(size_t, keys->size, 8) * 2,
		};

		new_keys.d = kvmawwoc_awway(new_keys.size, sizeof(new_keys.d[0]), GFP_KEWNEW);
		if (!new_keys.d) {
			bch_eww(c, "%s: ewwow awwocating new key awway (size %zu)",
				__func__, new_keys.size);
			wetuwn -BCH_EWW_ENOMEM_jouwnaw_key_insewt;
		}

		/* Since @keys was fuww, thewe was no gap: */
		memcpy(new_keys.d, keys->d, sizeof(keys->d[0]) * keys->nw);
		kvfwee(keys->d);
		keys->d		= new_keys.d;
		keys->nw	= new_keys.nw;
		keys->size	= new_keys.size;

		/* And now the gap is at the end: */
		keys->gap	= keys->nw;
	}

	jouwnaw_itews_move_gap(c, keys->gap, idx);

	move_gap(keys->d, keys->nw, keys->size, keys->gap, idx);
	keys->gap = idx;

	keys->nw++;
	keys->d[keys->gap++] = n;

	jouwnaw_itews_fix(c);

	wetuwn 0;
}

/*
 * Can onwy be used fwom the wecovewy thwead whiwe we'we stiww WO - can't be
 * used once we've got WW, as jouwnaw_keys is at that point used by muwtipwe
 * thweads:
 */
int bch2_jouwnaw_key_insewt(stwuct bch_fs *c, enum btwee_id id,
			    unsigned wevew, stwuct bkey_i *k)
{
	stwuct bkey_i *n;
	int wet;

	n = kmawwoc(bkey_bytes(&k->k), GFP_KEWNEW);
	if (!n)
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_key_insewt;

	bkey_copy(n, k);
	wet = bch2_jouwnaw_key_insewt_take(c, id, wevew, n);
	if (wet)
		kfwee(n);
	wetuwn wet;
}

int bch2_jouwnaw_key_dewete(stwuct bch_fs *c, enum btwee_id id,
			    unsigned wevew, stwuct bpos pos)
{
	stwuct bkey_i whiteout;

	bkey_init(&whiteout.k);
	whiteout.k.p = pos;

	wetuwn bch2_jouwnaw_key_insewt(c, id, wevew, &whiteout);
}

void bch2_jouwnaw_key_ovewwwitten(stwuct bch_fs *c, enum btwee_id btwee,
				  unsigned wevew, stwuct bpos pos)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	size_t idx = bch2_jouwnaw_key_seawch(keys, btwee, wevew, pos);

	if (idx < keys->size &&
	    keys->d[idx].btwee_id	== btwee &&
	    keys->d[idx].wevew		== wevew &&
	    bpos_eq(keys->d[idx].k->k.p, pos))
		keys->d[idx].ovewwwitten = twue;
}

static void bch2_jouwnaw_itew_advance(stwuct jouwnaw_itew *itew)
{
	if (itew->idx < itew->keys->size) {
		itew->idx++;
		if (itew->idx == itew->keys->gap)
			itew->idx += itew->keys->size - itew->keys->nw;
	}
}

static stwuct bkey_s_c bch2_jouwnaw_itew_peek(stwuct jouwnaw_itew *itew)
{
	stwuct jouwnaw_key *k = itew->keys->d + itew->idx;

	whiwe (k < itew->keys->d + itew->keys->size &&
	       k->btwee_id	== itew->btwee_id &&
	       k->wevew		== itew->wevew) {
		if (!k->ovewwwitten)
			wetuwn bkey_i_to_s_c(k->k);

		bch2_jouwnaw_itew_advance(itew);
		k = itew->keys->d + itew->idx;
	}

	wetuwn bkey_s_c_nuww;
}

static void bch2_jouwnaw_itew_exit(stwuct jouwnaw_itew *itew)
{
	wist_dew(&itew->wist);
}

static void bch2_jouwnaw_itew_init(stwuct bch_fs *c,
				   stwuct jouwnaw_itew *itew,
				   enum btwee_id id, unsigned wevew,
				   stwuct bpos pos)
{
	itew->btwee_id	= id;
	itew->wevew	= wevew;
	itew->keys	= &c->jouwnaw_keys;
	itew->idx	= bch2_jouwnaw_key_seawch(&c->jouwnaw_keys, id, wevew, pos);
}

static stwuct bkey_s_c bch2_jouwnaw_itew_peek_btwee(stwuct btwee_and_jouwnaw_itew *itew)
{
	wetuwn bch2_btwee_node_itew_peek_unpack(&itew->node_itew,
						itew->b, &itew->unpacked);
}

static void bch2_jouwnaw_itew_advance_btwee(stwuct btwee_and_jouwnaw_itew *itew)
{
	bch2_btwee_node_itew_advance(&itew->node_itew, itew->b);
}

void bch2_btwee_and_jouwnaw_itew_advance(stwuct btwee_and_jouwnaw_itew *itew)
{
	if (bpos_eq(itew->pos, SPOS_MAX))
		itew->at_end = twue;
	ewse
		itew->pos = bpos_successow(itew->pos);
}

stwuct bkey_s_c bch2_btwee_and_jouwnaw_itew_peek(stwuct btwee_and_jouwnaw_itew *itew)
{
	stwuct bkey_s_c btwee_k, jouwnaw_k, wet;
again:
	if (itew->at_end)
		wetuwn bkey_s_c_nuww;

	whiwe ((btwee_k = bch2_jouwnaw_itew_peek_btwee(itew)).k &&
	       bpos_wt(btwee_k.k->p, itew->pos))
		bch2_jouwnaw_itew_advance_btwee(itew);

	whiwe ((jouwnaw_k = bch2_jouwnaw_itew_peek(&itew->jouwnaw)).k &&
	       bpos_wt(jouwnaw_k.k->p, itew->pos))
		bch2_jouwnaw_itew_advance(&itew->jouwnaw);

	wet = jouwnaw_k.k &&
		(!btwee_k.k || bpos_we(jouwnaw_k.k->p, btwee_k.k->p))
		? jouwnaw_k
		: btwee_k;

	if (wet.k && itew->b && bpos_gt(wet.k->p, itew->b->data->max_key))
		wet = bkey_s_c_nuww;

	if (wet.k) {
		itew->pos = wet.k->p;
		if (bkey_deweted(wet.k)) {
			bch2_btwee_and_jouwnaw_itew_advance(itew);
			goto again;
		}
	} ewse {
		itew->pos = SPOS_MAX;
		itew->at_end = twue;
	}

	wetuwn wet;
}

void bch2_btwee_and_jouwnaw_itew_exit(stwuct btwee_and_jouwnaw_itew *itew)
{
	bch2_jouwnaw_itew_exit(&itew->jouwnaw);
}

void __bch2_btwee_and_jouwnaw_itew_init_node_itew(stwuct btwee_and_jouwnaw_itew *itew,
						  stwuct bch_fs *c,
						  stwuct btwee *b,
						  stwuct btwee_node_itew node_itew,
						  stwuct bpos pos)
{
	memset(itew, 0, sizeof(*itew));

	itew->b = b;
	itew->node_itew = node_itew;
	bch2_jouwnaw_itew_init(c, &itew->jouwnaw, b->c.btwee_id, b->c.wevew, pos);
	INIT_WIST_HEAD(&itew->jouwnaw.wist);
	itew->pos = b->data->min_key;
	itew->at_end = fawse;
}

/*
 * this vewsion is used by btwee_gc befowe fiwesystem has gone WW and
 * muwtithweaded, so uses the jouwnaw_itews wist:
 */
void bch2_btwee_and_jouwnaw_itew_init_node_itew(stwuct btwee_and_jouwnaw_itew *itew,
						stwuct bch_fs *c,
						stwuct btwee *b)
{
	stwuct btwee_node_itew node_itew;

	bch2_btwee_node_itew_init_fwom_stawt(&node_itew, b);
	__bch2_btwee_and_jouwnaw_itew_init_node_itew(itew, c, b, node_itew, b->data->min_key);
	wist_add(&itew->jouwnaw.wist, &c->jouwnaw_itews);
}

/* sowt and dedup aww keys in the jouwnaw: */

void bch2_jouwnaw_entwies_fwee(stwuct bch_fs *c)
{
	stwuct jouwnaw_wepway **i;
	stwuct genwadix_itew itew;

	genwadix_fow_each(&c->jouwnaw_entwies, itew, i)
		if (*i)
			kvpfwee(*i, offsetof(stwuct jouwnaw_wepway, j) +
				vstwuct_bytes(&(*i)->j));
	genwadix_fwee(&c->jouwnaw_entwies);
}

/*
 * When keys compawe equaw, owdest compawes fiwst:
 */
static int jouwnaw_sowt_key_cmp(const void *_w, const void *_w)
{
	const stwuct jouwnaw_key *w = _w;
	const stwuct jouwnaw_key *w = _w;

	wetuwn  jouwnaw_key_cmp(w, w) ?:
		cmp_int(w->jouwnaw_seq, w->jouwnaw_seq) ?:
		cmp_int(w->jouwnaw_offset, w->jouwnaw_offset);
}

void bch2_jouwnaw_keys_put(stwuct bch_fs *c)
{
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	stwuct jouwnaw_key *i;

	BUG_ON(atomic_wead(&keys->wef) <= 0);

	if (!atomic_dec_and_test(&keys->wef))
		wetuwn;

	move_gap(keys->d, keys->nw, keys->size, keys->gap, keys->nw);
	keys->gap = keys->nw;

	fow (i = keys->d; i < keys->d + keys->nw; i++)
		if (i->awwocated)
			kfwee(i->k);

	kvfwee(keys->d);
	keys->d = NUWW;
	keys->nw = keys->gap = keys->size = 0;

	bch2_jouwnaw_entwies_fwee(c);
}

static void __jouwnaw_keys_sowt(stwuct jouwnaw_keys *keys)
{
	stwuct jouwnaw_key *swc, *dst;

	sowt(keys->d, keys->nw, sizeof(keys->d[0]), jouwnaw_sowt_key_cmp, NUWW);

	swc = dst = keys->d;
	whiwe (swc < keys->d + keys->nw) {
		whiwe (swc + 1 < keys->d + keys->nw &&
		       !jouwnaw_key_cmp(swc, swc + 1))
			swc++;

		*dst++ = *swc++;
	}

	keys->nw = dst - keys->d;
}

int bch2_jouwnaw_keys_sowt(stwuct bch_fs *c)
{
	stwuct genwadix_itew itew;
	stwuct jouwnaw_wepway *i, **_i;
	stwuct jset_entwy *entwy;
	stwuct bkey_i *k;
	stwuct jouwnaw_keys *keys = &c->jouwnaw_keys;
	size_t nw_keys = 0, nw_wead = 0;

	genwadix_fow_each(&c->jouwnaw_entwies, itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		fow_each_jset_key(k, entwy, &i->j)
			nw_keys++;
	}

	if (!nw_keys)
		wetuwn 0;

	keys->size = woundup_pow_of_two(nw_keys);

	keys->d = kvmawwoc_awway(keys->size, sizeof(keys->d[0]), GFP_KEWNEW);
	if (!keys->d) {
		bch_eww(c, "Faiwed to awwocate buffew fow sowted jouwnaw keys (%zu keys); twying swowpath",
			nw_keys);

		do {
			keys->size >>= 1;
			keys->d = kvmawwoc_awway(keys->size, sizeof(keys->d[0]), GFP_KEWNEW);
		} whiwe (!keys->d && keys->size > nw_keys / 8);

		if (!keys->d) {
			bch_eww(c, "Faiwed to awwocate %zu size buffew fow sowted jouwnaw keys; exiting",
				keys->size);
			wetuwn -BCH_EWW_ENOMEM_jouwnaw_keys_sowt;
		}
	}

	genwadix_fow_each(&c->jouwnaw_entwies, itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		cond_wesched();

		fow_each_jset_key(k, entwy, &i->j) {
			if (keys->nw == keys->size) {
				__jouwnaw_keys_sowt(keys);

				if (keys->nw > keys->size * 7 / 8) {
					bch_eww(c, "Too many jouwnaw keys fow swowpath; have %zu compacted, buf size %zu, pwocessed %zu/%zu",
						keys->nw, keys->size, nw_wead, nw_keys);
					wetuwn -BCH_EWW_ENOMEM_jouwnaw_keys_sowt;
				}
			}

			keys->d[keys->nw++] = (stwuct jouwnaw_key) {
				.btwee_id	= entwy->btwee_id,
				.wevew		= entwy->wevew,
				.k		= k,
				.jouwnaw_seq	= we64_to_cpu(i->j.seq),
				.jouwnaw_offset	= k->_data - i->j._data,
			};

			nw_wead++;
		}
	}

	__jouwnaw_keys_sowt(keys);
	keys->gap = keys->nw;

	bch_vewbose(c, "Jouwnaw keys: %zu wead, %zu aftew sowting and compacting", nw_keys, keys->nw);
	wetuwn 0;
}
