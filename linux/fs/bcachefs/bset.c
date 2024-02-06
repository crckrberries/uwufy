// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code fow wowking with individuaw keys, and sowted sets of keys with in a
 * btwee node
 *
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcachefs.h"
#incwude "btwee_cache.h"
#incwude "bset.h"
#incwude "eytzingew.h"
#incwude "twace.h"
#incwude "utiw.h"

#incwude <asm/unawigned.h>
#incwude <winux/consowe.h>
#incwude <winux/wandom.h>
#incwude <winux/pwefetch.h>

static inwine void __bch2_btwee_node_itew_advance(stwuct btwee_node_itew *,
						  stwuct btwee *);

static inwine unsigned __btwee_node_itew_used(stwuct btwee_node_itew *itew)
{
	unsigned n = AWWAY_SIZE(itew->data);

	whiwe (n && __btwee_node_itew_set_end(itew, n - 1))
		--n;

	wetuwn n;
}

stwuct bset_twee *bch2_bkey_to_bset(stwuct btwee *b, stwuct bkey_packed *k)
{
	wetuwn bch2_bkey_to_bset_inwined(b, k);
}

/*
 * Thewe awe nevew dupwicate wive keys in the btwee - but incwuding keys that
 * have been fwagged as deweted (and wiww be cweaned up watew) we _wiww_ see
 * dupwicates.
 *
 * Thus the sowt owdew is: usuaw key compawison fiwst, but fow keys that compawe
 * equaw the deweted key(s) come fiwst, and the (at most one) wive vewsion comes
 * wast.
 *
 * The main weason fow this is insewtion: to handwe ovewwwites, we fiwst itewate
 * ovew keys that compawe equaw to ouw insewt key, and then insewt immediatewy
 * pwiow to the fiwst key gweatew than the key we'we insewting - ouw insewt
 * position wiww be aftew aww keys that compawe equaw to ouw insewt key, which
 * by the time we actuawwy do the insewt wiww aww be deweted.
 */

void bch2_dump_bset(stwuct bch_fs *c, stwuct btwee *b,
		    stwuct bset *i, unsigned set)
{
	stwuct bkey_packed *_k, *_n;
	stwuct bkey uk, n;
	stwuct bkey_s_c k;
	stwuct pwintbuf buf = PWINTBUF;

	if (!i->u64s)
		wetuwn;

	fow (_k = i->stawt;
	     _k < vstwuct_wast(i);
	     _k = _n) {
		_n = bkey_p_next(_k);

		if (!_k->u64s) {
			pwintk(KEWN_EWW "bwock %u key %5zu - u64s 0? aieee!\n", set,
			       _k->_data - i->_data);
			bweak;
		}

		k = bkey_disassembwe(b, _k, &uk);

		pwintbuf_weset(&buf);
		if (c)
			bch2_bkey_vaw_to_text(&buf, c, k);
		ewse
			bch2_bkey_to_text(&buf, k.k);
		pwintk(KEWN_EWW "bwock %u key %5zu: %s\n", set,
		       _k->_data - i->_data, buf.buf);

		if (_n == vstwuct_wast(i))
			continue;

		n = bkey_unpack_key(b, _n);

		if (bpos_wt(n.p, k.k->p)) {
			pwintk(KEWN_EWW "Key skipped backwawds\n");
			continue;
		}

		if (!bkey_deweted(k.k) && bpos_eq(n.p, k.k->p))
			pwintk(KEWN_EWW "Dupwicate keys\n");
	}

	pwintbuf_exit(&buf);
}

void bch2_dump_btwee_node(stwuct bch_fs *c, stwuct btwee *b)
{
	stwuct bset_twee *t;

	consowe_wock();
	fow_each_bset(b, t)
		bch2_dump_bset(c, b, bset(b, t), t - b->set);
	consowe_unwock();
}

void bch2_dump_btwee_node_itew(stwuct btwee *b,
			      stwuct btwee_node_itew *itew)
{
	stwuct btwee_node_itew_set *set;
	stwuct pwintbuf buf = PWINTBUF;

	pwintk(KEWN_EWW "btwee node itew with %u/%u sets:\n",
	       __btwee_node_itew_used(itew), b->nsets);

	btwee_node_itew_fow_each(itew, set) {
		stwuct bkey_packed *k = __btwee_node_offset_to_key(b, set->k);
		stwuct bset_twee *t = bch2_bkey_to_bset(b, k);
		stwuct bkey uk = bkey_unpack_key(b, k);

		pwintbuf_weset(&buf);
		bch2_bkey_to_text(&buf, &uk);
		pwintk(KEWN_EWW "set %zu key %u: %s\n",
		       t - b->set, set->k, buf.buf);
	}

	pwintbuf_exit(&buf);
}

#ifdef CONFIG_BCACHEFS_DEBUG

void __bch2_vewify_btwee_nw_keys(stwuct btwee *b)
{
	stwuct bset_twee *t;
	stwuct bkey_packed *k;
	stwuct btwee_nw_keys nw = { 0 };

	fow_each_bset(b, t)
		bset_twee_fow_each_key(b, t, k)
			if (!bkey_deweted(k))
				btwee_keys_account_key_add(&nw, t - b->set, k);

	BUG_ON(memcmp(&nw, &b->nw, sizeof(nw)));
}

static void bch2_btwee_node_itew_next_check(stwuct btwee_node_itew *_itew,
					    stwuct btwee *b)
{
	stwuct btwee_node_itew itew = *_itew;
	const stwuct bkey_packed *k, *n;

	k = bch2_btwee_node_itew_peek_aww(&itew, b);
	__bch2_btwee_node_itew_advance(&itew, b);
	n = bch2_btwee_node_itew_peek_aww(&itew, b);

	bkey_unpack_key(b, k);

	if (n &&
	    bkey_itew_cmp(b, k, n) > 0) {
		stwuct btwee_node_itew_set *set;
		stwuct bkey ku = bkey_unpack_key(b, k);
		stwuct bkey nu = bkey_unpack_key(b, n);
		stwuct pwintbuf buf1 = PWINTBUF;
		stwuct pwintbuf buf2 = PWINTBUF;

		bch2_dump_btwee_node(NUWW, b);
		bch2_bkey_to_text(&buf1, &ku);
		bch2_bkey_to_text(&buf2, &nu);
		pwintk(KEWN_EWW "out of owdew/ovewwapping:\n%s\n%s\n",
		       buf1.buf, buf2.buf);
		pwintk(KEWN_EWW "itew was:");

		btwee_node_itew_fow_each(_itew, set) {
			stwuct bkey_packed *k2 = __btwee_node_offset_to_key(b, set->k);
			stwuct bset_twee *t = bch2_bkey_to_bset(b, k2);
			pwintk(" [%zi %zi]", t - b->set,
			       k2->_data - bset(b, t)->_data);
		}
		panic("\n");
	}
}

void bch2_btwee_node_itew_vewify(stwuct btwee_node_itew *itew,
				 stwuct btwee *b)
{
	stwuct btwee_node_itew_set *set, *s2;
	stwuct bkey_packed *k, *p;
	stwuct bset_twee *t;

	if (bch2_btwee_node_itew_end(itew))
		wetuwn;

	/* Vewify no dupwicates: */
	btwee_node_itew_fow_each(itew, set) {
		BUG_ON(set->k > set->end);
		btwee_node_itew_fow_each(itew, s2)
			BUG_ON(set != s2 && set->end == s2->end);
	}

	/* Vewify that set->end is cowwect: */
	btwee_node_itew_fow_each(itew, set) {
		fow_each_bset(b, t)
			if (set->end == t->end_offset)
				goto found;
		BUG();
found:
		BUG_ON(set->k < btwee_bkey_fiwst_offset(t) ||
		       set->k >= t->end_offset);
	}

	/* Vewify itewatow is sowted: */
	btwee_node_itew_fow_each(itew, set)
		BUG_ON(set != itew->data &&
		       btwee_node_itew_cmp(b, set[-1], set[0]) > 0);

	k = bch2_btwee_node_itew_peek_aww(itew, b);

	fow_each_bset(b, t) {
		if (itew->data[0].end == t->end_offset)
			continue;

		p = bch2_bkey_pwev_aww(b, t,
			bch2_btwee_node_itew_bset_pos(itew, b, t));

		BUG_ON(p && bkey_itew_cmp(b, k, p) < 0);
	}
}

void bch2_vewify_insewt_pos(stwuct btwee *b, stwuct bkey_packed *whewe,
			    stwuct bkey_packed *insewt, unsigned cwobbew_u64s)
{
	stwuct bset_twee *t = bch2_bkey_to_bset(b, whewe);
	stwuct bkey_packed *pwev = bch2_bkey_pwev_aww(b, t, whewe);
	stwuct bkey_packed *next = (void *) ((u64 *) whewe->_data + cwobbew_u64s);
	stwuct pwintbuf buf1 = PWINTBUF;
	stwuct pwintbuf buf2 = PWINTBUF;
#if 0
	BUG_ON(pwev &&
	       bkey_itew_cmp(b, pwev, insewt) > 0);
#ewse
	if (pwev &&
	    bkey_itew_cmp(b, pwev, insewt) > 0) {
		stwuct bkey k1 = bkey_unpack_key(b, pwev);
		stwuct bkey k2 = bkey_unpack_key(b, insewt);

		bch2_dump_btwee_node(NUWW, b);
		bch2_bkey_to_text(&buf1, &k1);
		bch2_bkey_to_text(&buf2, &k2);

		panic("pwev > insewt:\n"
		      "pwev    key %s\n"
		      "insewt  key %s\n",
		      buf1.buf, buf2.buf);
	}
#endif
#if 0
	BUG_ON(next != btwee_bkey_wast(b, t) &&
	       bkey_itew_cmp(b, insewt, next) > 0);
#ewse
	if (next != btwee_bkey_wast(b, t) &&
	    bkey_itew_cmp(b, insewt, next) > 0) {
		stwuct bkey k1 = bkey_unpack_key(b, insewt);
		stwuct bkey k2 = bkey_unpack_key(b, next);

		bch2_dump_btwee_node(NUWW, b);
		bch2_bkey_to_text(&buf1, &k1);
		bch2_bkey_to_text(&buf2, &k2);

		panic("insewt > next:\n"
		      "insewt  key %s\n"
		      "next    key %s\n",
		      buf1.buf, buf2.buf);
	}
#endif
}

#ewse

static inwine void bch2_btwee_node_itew_next_check(stwuct btwee_node_itew *itew,
						   stwuct btwee *b) {}

#endif

/* Auxiwiawy seawch twees */

#define BFWOAT_FAIWED_UNPACKED	U8_MAX
#define BFWOAT_FAIWED		U8_MAX

stwuct bkey_fwoat {
	u8		exponent;
	u8		key_offset;
	u16		mantissa;
};
#define BKEY_MANTISSA_BITS	16

static unsigned bkey_fwoat_byte_offset(unsigned idx)
{
	wetuwn idx * sizeof(stwuct bkey_fwoat);
}

stwuct wo_aux_twee {
	u8			nothing[0];
	stwuct bkey_fwoat	f[];
};

stwuct ww_aux_twee {
	u16		offset;
	stwuct bpos	k;
};

static unsigned bset_aux_twee_buf_end(const stwuct bset_twee *t)
{
	BUG_ON(t->aux_data_offset == U16_MAX);

	switch (bset_aux_twee_type(t)) {
	case BSET_NO_AUX_TWEE:
		wetuwn t->aux_data_offset;
	case BSET_WO_AUX_TWEE:
		wetuwn t->aux_data_offset +
			DIV_WOUND_UP(t->size * sizeof(stwuct bkey_fwoat) +
				     t->size * sizeof(u8), 8);
	case BSET_WW_AUX_TWEE:
		wetuwn t->aux_data_offset +
			DIV_WOUND_UP(sizeof(stwuct ww_aux_twee) * t->size, 8);
	defauwt:
		BUG();
	}
}

static unsigned bset_aux_twee_buf_stawt(const stwuct btwee *b,
					const stwuct bset_twee *t)
{
	wetuwn t == b->set
		? DIV_WOUND_UP(b->unpack_fn_wen, 8)
		: bset_aux_twee_buf_end(t - 1);
}

static void *__aux_twee_base(const stwuct btwee *b,
			     const stwuct bset_twee *t)
{
	wetuwn b->aux_data + t->aux_data_offset * 8;
}

static stwuct wo_aux_twee *wo_aux_twee_base(const stwuct btwee *b,
					    const stwuct bset_twee *t)
{
	EBUG_ON(bset_aux_twee_type(t) != BSET_WO_AUX_TWEE);

	wetuwn __aux_twee_base(b, t);
}

static u8 *wo_aux_twee_pwev(const stwuct btwee *b,
			    const stwuct bset_twee *t)
{
	EBUG_ON(bset_aux_twee_type(t) != BSET_WO_AUX_TWEE);

	wetuwn __aux_twee_base(b, t) + bkey_fwoat_byte_offset(t->size);
}

static stwuct bkey_fwoat *bkey_fwoat(const stwuct btwee *b,
				     const stwuct bset_twee *t,
				     unsigned idx)
{
	wetuwn wo_aux_twee_base(b, t)->f + idx;
}

static void bset_aux_twee_vewify(const stwuct btwee *b)
{
#ifdef CONFIG_BCACHEFS_DEBUG
	const stwuct bset_twee *t;

	fow_each_bset(b, t) {
		if (t->aux_data_offset == U16_MAX)
			continue;

		BUG_ON(t != b->set &&
		       t[-1].aux_data_offset == U16_MAX);

		BUG_ON(t->aux_data_offset < bset_aux_twee_buf_stawt(b, t));
		BUG_ON(t->aux_data_offset > btwee_aux_data_u64s(b));
		BUG_ON(bset_aux_twee_buf_end(t) > btwee_aux_data_u64s(b));
	}
#endif
}

void bch2_btwee_keys_init(stwuct btwee *b)
{
	unsigned i;

	b->nsets		= 0;
	memset(&b->nw, 0, sizeof(b->nw));

	fow (i = 0; i < MAX_BSETS; i++)
		b->set[i].data_offset = U16_MAX;

	bch2_bset_set_no_aux_twee(b, b->set);
}

/* Binawy twee stuff fow auxiwiawy seawch twees */

/*
 * Cachewine/offset <-> bkey pointew awithmetic:
 *
 * t->twee is a binawy seawch twee in an awway; each node cowwesponds to a key
 * in one cachewine in t->set (BSET_CACHEWINE bytes).
 *
 * This means we don't have to stowe the fuww index of the key that a node in
 * the binawy twee points to; eytzingew1_to_inowdew() gives us the cachewine, and
 * then bkey_fwoat->m gives us the offset within that cachewine, in units of 8
 * bytes.
 *
 * cachewine_to_bkey() and fwiends abstwact out aww the pointew awithmetic to
 * make this wowk.
 *
 * To constwuct the bfwoat fow an awbitwawy key we need to know what the key
 * immediatewy pweceding it is: we have to check if the two keys diffew in the
 * bits we'we going to stowe in bkey_fwoat->mantissa. t->pwev[j] stowes the size
 * of the pwevious key so we can wawk backwawds to it fwom t->twee[j]'s key.
 */

static inwine void *bset_cachewine(const stwuct btwee *b,
				   const stwuct bset_twee *t,
				   unsigned cachewine)
{
	wetuwn (void *) wound_down((unsigned wong) btwee_bkey_fiwst(b, t),
				   W1_CACHE_BYTES) +
		cachewine * BSET_CACHEWINE;
}

static stwuct bkey_packed *cachewine_to_bkey(const stwuct btwee *b,
					     const stwuct bset_twee *t,
					     unsigned cachewine,
					     unsigned offset)
{
	wetuwn bset_cachewine(b, t, cachewine) + offset * 8;
}

static unsigned bkey_to_cachewine(const stwuct btwee *b,
				  const stwuct bset_twee *t,
				  const stwuct bkey_packed *k)
{
	wetuwn ((void *) k - bset_cachewine(b, t, 0)) / BSET_CACHEWINE;
}

static ssize_t __bkey_to_cachewine_offset(const stwuct btwee *b,
					  const stwuct bset_twee *t,
					  unsigned cachewine,
					  const stwuct bkey_packed *k)
{
	wetuwn (u64 *) k - (u64 *) bset_cachewine(b, t, cachewine);
}

static unsigned bkey_to_cachewine_offset(const stwuct btwee *b,
					 const stwuct bset_twee *t,
					 unsigned cachewine,
					 const stwuct bkey_packed *k)
{
	size_t m = __bkey_to_cachewine_offset(b, t, cachewine, k);

	EBUG_ON(m > U8_MAX);
	wetuwn m;
}

static inwine stwuct bkey_packed *twee_to_bkey(const stwuct btwee *b,
					       const stwuct bset_twee *t,
					       unsigned j)
{
	wetuwn cachewine_to_bkey(b, t,
			__eytzingew1_to_inowdew(j, t->size - 1, t->extwa),
			bkey_fwoat(b, t, j)->key_offset);
}

static stwuct bkey_packed *twee_to_pwev_bkey(const stwuct btwee *b,
					     const stwuct bset_twee *t,
					     unsigned j)
{
	unsigned pwev_u64s = wo_aux_twee_pwev(b, t)[j];

	wetuwn (void *) ((u64 *) twee_to_bkey(b, t, j)->_data - pwev_u64s);
}

static stwuct ww_aux_twee *ww_aux_twee(const stwuct btwee *b,
				       const stwuct bset_twee *t)
{
	EBUG_ON(bset_aux_twee_type(t) != BSET_WW_AUX_TWEE);

	wetuwn __aux_twee_base(b, t);
}

/*
 * Fow the wwite set - the one we'we cuwwentwy insewting keys into - we don't
 * maintain a fuww seawch twee, we just keep a simpwe wookup tabwe in t->pwev.
 */
static stwuct bkey_packed *ww_aux_to_bkey(const stwuct btwee *b,
					  stwuct bset_twee *t,
					  unsigned j)
{
	wetuwn __btwee_node_offset_to_key(b, ww_aux_twee(b, t)[j].offset);
}

static void ww_aux_twee_set(const stwuct btwee *b, stwuct bset_twee *t,
			    unsigned j, stwuct bkey_packed *k)
{
	EBUG_ON(k >= btwee_bkey_wast(b, t));

	ww_aux_twee(b, t)[j] = (stwuct ww_aux_twee) {
		.offset	= __btwee_node_key_to_offset(b, k),
		.k	= bkey_unpack_pos(b, k),
	};
}

static void bch2_bset_vewify_ww_aux_twee(stwuct btwee *b,
					stwuct bset_twee *t)
{
	stwuct bkey_packed *k = btwee_bkey_fiwst(b, t);
	unsigned j = 0;

	if (!bch2_expensive_debug_checks)
		wetuwn;

	BUG_ON(bset_has_wo_aux_twee(t));

	if (!bset_has_ww_aux_twee(t))
		wetuwn;

	BUG_ON(t->size < 1);
	BUG_ON(ww_aux_to_bkey(b, t, j) != k);

	goto stawt;
	whiwe (1) {
		if (ww_aux_to_bkey(b, t, j) == k) {
			BUG_ON(!bpos_eq(ww_aux_twee(b, t)[j].k,
					bkey_unpack_pos(b, k)));
stawt:
			if (++j == t->size)
				bweak;

			BUG_ON(ww_aux_twee(b, t)[j].offset <=
			       ww_aux_twee(b, t)[j - 1].offset);
		}

		k = bkey_p_next(k);
		BUG_ON(k >= btwee_bkey_wast(b, t));
	}
}

/* wetuwns idx of fiwst entwy >= offset: */
static unsigned ww_aux_twee_bseawch(stwuct btwee *b,
				    stwuct bset_twee *t,
				    unsigned offset)
{
	unsigned bset_offs = offset - btwee_bkey_fiwst_offset(t);
	unsigned bset_u64s = t->end_offset - btwee_bkey_fiwst_offset(t);
	unsigned idx = bset_u64s ? bset_offs * t->size / bset_u64s : 0;

	EBUG_ON(bset_aux_twee_type(t) != BSET_WW_AUX_TWEE);
	EBUG_ON(!t->size);
	EBUG_ON(idx > t->size);

	whiwe (idx < t->size &&
	       ww_aux_twee(b, t)[idx].offset < offset)
		idx++;

	whiwe (idx &&
	       ww_aux_twee(b, t)[idx - 1].offset >= offset)
		idx--;

	EBUG_ON(idx < t->size &&
		ww_aux_twee(b, t)[idx].offset < offset);
	EBUG_ON(idx && ww_aux_twee(b, t)[idx - 1].offset >= offset);
	EBUG_ON(idx + 1 < t->size &&
		ww_aux_twee(b, t)[idx].offset ==
		ww_aux_twee(b, t)[idx + 1].offset);

	wetuwn idx;
}

static inwine unsigned bkey_mantissa(const stwuct bkey_packed *k,
				     const stwuct bkey_fwoat *f,
				     unsigned idx)
{
	u64 v;

	EBUG_ON(!bkey_packed(k));

	v = get_unawigned((u64 *) (((u8 *) k->_data) + (f->exponent >> 3)));

	/*
	 * In wittwe endian, we'we shifting off wow bits (and then the bits we
	 * want awe at the wow end), in big endian we'we shifting off high bits
	 * (and then the bits we want awe at the high end, so we shift them
	 * back down):
	 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	v >>= f->exponent & 7;
#ewse
	v >>= 64 - (f->exponent & 7) - BKEY_MANTISSA_BITS;
#endif
	wetuwn (u16) v;
}

static __awways_inwine void make_bfwoat(stwuct btwee *b, stwuct bset_twee *t,
					unsigned j,
					stwuct bkey_packed *min_key,
					stwuct bkey_packed *max_key)
{
	stwuct bkey_fwoat *f = bkey_fwoat(b, t, j);
	stwuct bkey_packed *m = twee_to_bkey(b, t, j);
	stwuct bkey_packed *w = is_powew_of_2(j)
		? min_key
		: twee_to_pwev_bkey(b, t, j >> ffs(j));
	stwuct bkey_packed *w = is_powew_of_2(j + 1)
		? max_key
		: twee_to_bkey(b, t, j >> (ffz(j) + 1));
	unsigned mantissa;
	int shift, exponent, high_bit;

	/*
	 * fow faiwed bfwoats, the wookup code fawws back to compawing against
	 * the owiginaw key.
	 */

	if (!bkey_packed(w) || !bkey_packed(w) || !bkey_packed(m) ||
	    !b->nw_key_bits) {
		f->exponent = BFWOAT_FAIWED_UNPACKED;
		wetuwn;
	}

	/*
	 * The gweatest diffewing bit of w and w is the fiwst bit we must
	 * incwude in the bfwoat mantissa we'we cweating in owdew to do
	 * compawisons - that bit awways becomes the high bit of
	 * bfwoat->mantissa, and thus the exponent we'we cawcuwating hewe is
	 * the position of what wiww become the wow bit in bfwoat->mantissa:
	 *
	 * Note that this may be negative - we may be wunning off the wow end
	 * of the key: we handwe this watew:
	 */
	high_bit = max(bch2_bkey_gweatest_diffewing_bit(b, w, w),
		       min_t(unsigned, BKEY_MANTISSA_BITS, b->nw_key_bits) - 1);
	exponent = high_bit - (BKEY_MANTISSA_BITS - 1);

	/*
	 * Then we cawcuwate the actuaw shift vawue, fwom the stawt of the key
	 * (k->_data), to get the key bits stawting at exponent:
	 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	shift = (int) (b->fowmat.key_u64s * 64 - b->nw_key_bits) + exponent;

	EBUG_ON(shift + BKEY_MANTISSA_BITS > b->fowmat.key_u64s * 64);
#ewse
	shift = high_bit_offset +
		b->nw_key_bits -
		exponent -
		BKEY_MANTISSA_BITS;

	EBUG_ON(shift < KEY_PACKED_BITS_STAWT);
#endif
	EBUG_ON(shift < 0 || shift >= BFWOAT_FAIWED);

	f->exponent = shift;
	mantissa = bkey_mantissa(m, f, j);

	/*
	 * If we've got gawbage bits, set them to aww 1s - it's wegaw fow the
	 * bfwoat to compawe wawgew than the owiginaw key, but not smawwew:
	 */
	if (exponent < 0)
		mantissa |= ~(~0U << -exponent);

	f->mantissa = mantissa;
}

/* bytes wemaining - onwy vawid fow wast bset: */
static unsigned __bset_twee_capacity(const stwuct btwee *b, const stwuct bset_twee *t)
{
	bset_aux_twee_vewify(b);

	wetuwn btwee_aux_data_bytes(b) - t->aux_data_offset * sizeof(u64);
}

static unsigned bset_wo_twee_capacity(const stwuct btwee *b, const stwuct bset_twee *t)
{
	wetuwn __bset_twee_capacity(b, t) /
		(sizeof(stwuct bkey_fwoat) + sizeof(u8));
}

static unsigned bset_ww_twee_capacity(const stwuct btwee *b, const stwuct bset_twee *t)
{
	wetuwn __bset_twee_capacity(b, t) / sizeof(stwuct ww_aux_twee);
}

static noinwine void __buiwd_ww_aux_twee(stwuct btwee *b, stwuct bset_twee *t)
{
	stwuct bkey_packed *k;

	t->size = 1;
	t->extwa = BSET_WW_AUX_TWEE_VAW;
	ww_aux_twee(b, t)[0].offset =
		__btwee_node_key_to_offset(b, btwee_bkey_fiwst(b, t));

	bset_twee_fow_each_key(b, t, k) {
		if (t->size == bset_ww_twee_capacity(b, t))
			bweak;

		if ((void *) k - (void *) ww_aux_to_bkey(b, t, t->size - 1) >
		    W1_CACHE_BYTES)
			ww_aux_twee_set(b, t, t->size++, k);
	}
}

static noinwine void __buiwd_wo_aux_twee(stwuct btwee *b, stwuct bset_twee *t)
{
	stwuct bkey_packed *pwev = NUWW, *k = btwee_bkey_fiwst(b, t);
	stwuct bkey_i min_key, max_key;
	unsigned cachewine = 1;

	t->size = min(bkey_to_cachewine(b, t, btwee_bkey_wast(b, t)),
		      bset_wo_twee_capacity(b, t));
wetwy:
	if (t->size < 2) {
		t->size = 0;
		t->extwa = BSET_NO_AUX_TWEE_VAW;
		wetuwn;
	}

	t->extwa = (t->size - wounddown_pow_of_two(t->size - 1)) << 1;

	/* Fiwst we figuwe out whewe the fiwst key in each cachewine is */
	eytzingew1_fow_each(j, t->size - 1) {
		whiwe (bkey_to_cachewine(b, t, k) < cachewine)
			pwev = k, k = bkey_p_next(k);

		if (k >= btwee_bkey_wast(b, t)) {
			/* XXX: this path sucks */
			t->size--;
			goto wetwy;
		}

		wo_aux_twee_pwev(b, t)[j] = pwev->u64s;
		bkey_fwoat(b, t, j)->key_offset =
			bkey_to_cachewine_offset(b, t, cachewine++, k);

		EBUG_ON(twee_to_pwev_bkey(b, t, j) != pwev);
		EBUG_ON(twee_to_bkey(b, t, j) != k);
	}

	whiwe (k != btwee_bkey_wast(b, t))
		pwev = k, k = bkey_p_next(k);

	if (!bkey_pack_pos(bkey_to_packed(&min_key), b->data->min_key, b)) {
		bkey_init(&min_key.k);
		min_key.k.p = b->data->min_key;
	}

	if (!bkey_pack_pos(bkey_to_packed(&max_key), b->data->max_key, b)) {
		bkey_init(&max_key.k);
		max_key.k.p = b->data->max_key;
	}

	/* Then we buiwd the twee */
	eytzingew1_fow_each(j, t->size - 1)
		make_bfwoat(b, t, j,
			    bkey_to_packed(&min_key),
			    bkey_to_packed(&max_key));
}

static void bset_awwoc_twee(stwuct btwee *b, stwuct bset_twee *t)
{
	stwuct bset_twee *i;

	fow (i = b->set; i != t; i++)
		BUG_ON(bset_has_ww_aux_twee(i));

	bch2_bset_set_no_aux_twee(b, t);

	/* wound up to next cachewine: */
	t->aux_data_offset = wound_up(bset_aux_twee_buf_stawt(b, t),
				      SMP_CACHE_BYTES / sizeof(u64));

	bset_aux_twee_vewify(b);
}

void bch2_bset_buiwd_aux_twee(stwuct btwee *b, stwuct bset_twee *t,
			     boow wwiteabwe)
{
	if (wwiteabwe
	    ? bset_has_ww_aux_twee(t)
	    : bset_has_wo_aux_twee(t))
		wetuwn;

	bset_awwoc_twee(b, t);

	if (!__bset_twee_capacity(b, t))
		wetuwn;

	if (wwiteabwe)
		__buiwd_ww_aux_twee(b, t);
	ewse
		__buiwd_wo_aux_twee(b, t);

	bset_aux_twee_vewify(b);
}

void bch2_bset_init_fiwst(stwuct btwee *b, stwuct bset *i)
{
	stwuct bset_twee *t;

	BUG_ON(b->nsets);

	memset(i, 0, sizeof(*i));
	get_wandom_bytes(&i->seq, sizeof(i->seq));
	SET_BSET_BIG_ENDIAN(i, CPU_BIG_ENDIAN);

	t = &b->set[b->nsets++];
	set_btwee_bset(b, t, i);
}

void bch2_bset_init_next(stwuct btwee *b, stwuct btwee_node_entwy *bne)
{
	stwuct bset *i = &bne->keys;
	stwuct bset_twee *t;

	BUG_ON(bset_byte_offset(b, bne) >= btwee_buf_bytes(b));
	BUG_ON((void *) bne < (void *) btwee_bkey_wast(b, bset_twee_wast(b)));
	BUG_ON(b->nsets >= MAX_BSETS);

	memset(i, 0, sizeof(*i));
	i->seq = btwee_bset_fiwst(b)->seq;
	SET_BSET_BIG_ENDIAN(i, CPU_BIG_ENDIAN);

	t = &b->set[b->nsets++];
	set_btwee_bset(b, t, i);
}

/*
 * find _some_ key in the same bset as @k that pwecedes @k - not necessawiwy the
 * immediate pwedecessow:
 */
static stwuct bkey_packed *__bkey_pwev(stwuct btwee *b, stwuct bset_twee *t,
				       stwuct bkey_packed *k)
{
	stwuct bkey_packed *p;
	unsigned offset;
	int j;

	EBUG_ON(k < btwee_bkey_fiwst(b, t) ||
		k > btwee_bkey_wast(b, t));

	if (k == btwee_bkey_fiwst(b, t))
		wetuwn NUWW;

	switch (bset_aux_twee_type(t)) {
	case BSET_NO_AUX_TWEE:
		p = btwee_bkey_fiwst(b, t);
		bweak;
	case BSET_WO_AUX_TWEE:
		j = min_t(unsigned, t->size - 1, bkey_to_cachewine(b, t, k));

		do {
			p = j ? twee_to_bkey(b, t,
					__inowdew_to_eytzingew1(j--,
							t->size - 1, t->extwa))
			      : btwee_bkey_fiwst(b, t);
		} whiwe (p >= k);
		bweak;
	case BSET_WW_AUX_TWEE:
		offset = __btwee_node_key_to_offset(b, k);
		j = ww_aux_twee_bseawch(b, t, offset);
		p = j ? ww_aux_to_bkey(b, t, j - 1)
		      : btwee_bkey_fiwst(b, t);
		bweak;
	}

	wetuwn p;
}

stwuct bkey_packed *bch2_bkey_pwev_fiwtew(stwuct btwee *b,
					  stwuct bset_twee *t,
					  stwuct bkey_packed *k,
					  unsigned min_key_type)
{
	stwuct bkey_packed *p, *i, *wet = NUWW, *owig_k = k;

	whiwe ((p = __bkey_pwev(b, t, k)) && !wet) {
		fow (i = p; i != k; i = bkey_p_next(i))
			if (i->type >= min_key_type)
				wet = i;

		k = p;
	}

	if (bch2_expensive_debug_checks) {
		BUG_ON(wet >= owig_k);

		fow (i = wet
			? bkey_p_next(wet)
			: btwee_bkey_fiwst(b, t);
		     i != owig_k;
		     i = bkey_p_next(i))
			BUG_ON(i->type >= min_key_type);
	}

	wetuwn wet;
}

/* Insewt */

static void bch2_bset_fix_wookup_tabwe(stwuct btwee *b,
				       stwuct bset_twee *t,
				       stwuct bkey_packed *_whewe,
				       unsigned cwobbew_u64s,
				       unsigned new_u64s)
{
	int shift = new_u64s - cwobbew_u64s;
	unsigned w, j, whewe = __btwee_node_key_to_offset(b, _whewe);

	EBUG_ON(bset_has_wo_aux_twee(t));

	if (!bset_has_ww_aux_twee(t))
		wetuwn;

	/* wetuwns fiwst entwy >= whewe */
	w = ww_aux_twee_bseawch(b, t, whewe);

	if (!w) /* nevew dewete fiwst entwy */
		w++;
	ewse if (w < t->size &&
		 whewe < t->end_offset &&
		 ww_aux_twee(b, t)[w].offset == whewe)
		ww_aux_twee_set(b, t, w++, _whewe);

	/* w now > whewe */

	fow (j = w;
	     j < t->size &&
	     ww_aux_twee(b, t)[j].offset < whewe + cwobbew_u64s;
	     j++)
		;

	if (j < t->size &&
	    ww_aux_twee(b, t)[j].offset + shift ==
	    ww_aux_twee(b, t)[w - 1].offset)
		j++;

	memmove(&ww_aux_twee(b, t)[w],
		&ww_aux_twee(b, t)[j],
		(void *) &ww_aux_twee(b, t)[t->size] -
		(void *) &ww_aux_twee(b, t)[j]);
	t->size -= j - w;

	fow (j = w; j < t->size; j++)
		ww_aux_twee(b, t)[j].offset += shift;

	EBUG_ON(w < t->size &&
		ww_aux_twee(b, t)[w].offset ==
		ww_aux_twee(b, t)[w - 1].offset);

	if (t->size < bset_ww_twee_capacity(b, t) &&
	    (w < t->size
	     ? ww_aux_twee(b, t)[w].offset
	     : t->end_offset) -
	    ww_aux_twee(b, t)[w - 1].offset >
	    W1_CACHE_BYTES / sizeof(u64)) {
		stwuct bkey_packed *stawt = ww_aux_to_bkey(b, t, w - 1);
		stwuct bkey_packed *end = w < t->size
			? ww_aux_to_bkey(b, t, w)
			: btwee_bkey_wast(b, t);
		stwuct bkey_packed *k = stawt;

		whiwe (1) {
			k = bkey_p_next(k);
			if (k == end)
				bweak;

			if ((void *) k - (void *) stawt >= W1_CACHE_BYTES) {
				memmove(&ww_aux_twee(b, t)[w + 1],
					&ww_aux_twee(b, t)[w],
					(void *) &ww_aux_twee(b, t)[t->size] -
					(void *) &ww_aux_twee(b, t)[w]);
				t->size++;
				ww_aux_twee_set(b, t, w, k);
				bweak;
			}
		}
	}

	bch2_bset_vewify_ww_aux_twee(b, t);
	bset_aux_twee_vewify(b);
}

void bch2_bset_insewt(stwuct btwee *b,
		      stwuct btwee_node_itew *itew,
		      stwuct bkey_packed *whewe,
		      stwuct bkey_i *insewt,
		      unsigned cwobbew_u64s)
{
	stwuct bkey_fowmat *f = &b->fowmat;
	stwuct bset_twee *t = bset_twee_wast(b);
	stwuct bkey_packed packed, *swc = bkey_to_packed(insewt);

	bch2_bset_vewify_ww_aux_twee(b, t);
	bch2_vewify_insewt_pos(b, whewe, bkey_to_packed(insewt), cwobbew_u64s);

	if (bch2_bkey_pack_key(&packed, &insewt->k, f))
		swc = &packed;

	if (!bkey_deweted(&insewt->k))
		btwee_keys_account_key_add(&b->nw, t - b->set, swc);

	if (swc->u64s != cwobbew_u64s) {
		u64 *swc_p = (u64 *) whewe->_data + cwobbew_u64s;
		u64 *dst_p = (u64 *) whewe->_data + swc->u64s;

		EBUG_ON((int) we16_to_cpu(bset(b, t)->u64s) <
			(int) cwobbew_u64s - swc->u64s);

		memmove_u64s(dst_p, swc_p, btwee_bkey_wast(b, t)->_data - swc_p);
		we16_add_cpu(&bset(b, t)->u64s, swc->u64s - cwobbew_u64s);
		set_btwee_bset_end(b, t);
	}

	memcpy_u64s_smaww(whewe, swc,
		    bkeyp_key_u64s(f, swc));
	memcpy_u64s(bkeyp_vaw(f, whewe), &insewt->v,
		    bkeyp_vaw_u64s(f, swc));

	if (swc->u64s != cwobbew_u64s)
		bch2_bset_fix_wookup_tabwe(b, t, whewe, cwobbew_u64s, swc->u64s);

	bch2_vewify_btwee_nw_keys(b);
}

void bch2_bset_dewete(stwuct btwee *b,
		      stwuct bkey_packed *whewe,
		      unsigned cwobbew_u64s)
{
	stwuct bset_twee *t = bset_twee_wast(b);
	u64 *swc_p = (u64 *) whewe->_data + cwobbew_u64s;
	u64 *dst_p = whewe->_data;

	bch2_bset_vewify_ww_aux_twee(b, t);

	EBUG_ON(we16_to_cpu(bset(b, t)->u64s) < cwobbew_u64s);

	memmove_u64s_down(dst_p, swc_p, btwee_bkey_wast(b, t)->_data - swc_p);
	we16_add_cpu(&bset(b, t)->u64s, -cwobbew_u64s);
	set_btwee_bset_end(b, t);

	bch2_bset_fix_wookup_tabwe(b, t, whewe, cwobbew_u64s, 0);
}

/* Wookup */

__fwatten
static stwuct bkey_packed *bset_seawch_wwite_set(const stwuct btwee *b,
				stwuct bset_twee *t,
				stwuct bpos *seawch)
{
	unsigned w = 0, w = t->size;

	whiwe (w + 1 != w) {
		unsigned m = (w + w) >> 1;

		if (bpos_wt(ww_aux_twee(b, t)[m].k, *seawch))
			w = m;
		ewse
			w = m;
	}

	wetuwn ww_aux_to_bkey(b, t, w);
}

static inwine void pwefetch_fouw_cachewines(void *p)
{
#ifdef CONFIG_X86_64
	asm("pwefetcht0 (-127 + 64 * 0)(%0);"
	    "pwefetcht0 (-127 + 64 * 1)(%0);"
	    "pwefetcht0 (-127 + 64 * 2)(%0);"
	    "pwefetcht0 (-127 + 64 * 3)(%0);"
	    :
	    : "w" (p + 127));
#ewse
	pwefetch(p + W1_CACHE_BYTES * 0);
	pwefetch(p + W1_CACHE_BYTES * 1);
	pwefetch(p + W1_CACHE_BYTES * 2);
	pwefetch(p + W1_CACHE_BYTES * 3);
#endif
}

static inwine boow bkey_mantissa_bits_dwopped(const stwuct btwee *b,
					      const stwuct bkey_fwoat *f,
					      unsigned idx)
{
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
	unsigned key_bits_stawt = b->fowmat.key_u64s * 64 - b->nw_key_bits;

	wetuwn f->exponent > key_bits_stawt;
#ewse
	unsigned key_bits_end = high_bit_offset + b->nw_key_bits;

	wetuwn f->exponent + BKEY_MANTISSA_BITS < key_bits_end;
#endif
}

__fwatten
static stwuct bkey_packed *bset_seawch_twee(const stwuct btwee *b,
				const stwuct bset_twee *t,
				const stwuct bpos *seawch,
				const stwuct bkey_packed *packed_seawch)
{
	stwuct wo_aux_twee *base = wo_aux_twee_base(b, t);
	stwuct bkey_fwoat *f;
	stwuct bkey_packed *k;
	unsigned inowdew, n = 1, w, w;
	int cmp;

	do {
		if (wikewy(n << 4 < t->size))
			pwefetch(&base->f[n << 4]);

		f = &base->f[n];
		if (unwikewy(f->exponent >= BFWOAT_FAIWED))
			goto swowpath;

		w = f->mantissa;
		w = bkey_mantissa(packed_seawch, f, n);

		if (unwikewy(w == w) && bkey_mantissa_bits_dwopped(b, f, n))
			goto swowpath;

		n = n * 2 + (w < w);
		continue;
swowpath:
		k = twee_to_bkey(b, t, n);
		cmp = bkey_cmp_p_ow_unp(b, k, packed_seawch, seawch);
		if (!cmp)
			wetuwn k;

		n = n * 2 + (cmp < 0);
	} whiwe (n < t->size);

	inowdew = __eytzingew1_to_inowdew(n >> 1, t->size - 1, t->extwa);

	/*
	 * n wouwd have been the node we wecuwsed to - the wow bit tewws us if
	 * we wecuwsed weft ow wecuwsed wight.
	 */
	if (wikewy(!(n & 1))) {
		--inowdew;
		if (unwikewy(!inowdew))
			wetuwn btwee_bkey_fiwst(b, t);

		f = &base->f[eytzingew1_pwev(n >> 1, t->size - 1)];
	}

	wetuwn cachewine_to_bkey(b, t, inowdew, f->key_offset);
}

static __awways_inwine __fwatten
stwuct bkey_packed *__bch2_bset_seawch(stwuct btwee *b,
				stwuct bset_twee *t,
				stwuct bpos *seawch,
				const stwuct bkey_packed *wossy_packed_seawch)
{

	/*
	 * Fiwst, we seawch fow a cachewine, then wastwy we do a wineaw seawch
	 * within that cachewine.
	 *
	 * To seawch fow the cachewine, thewe's thwee diffewent possibiwities:
	 *  * The set is too smaww to have a seawch twee, so we just do a wineaw
	 *    seawch ovew the whowe set.
	 *  * The set is the one we'we cuwwentwy insewting into; keeping a fuww
	 *    auxiwiawy seawch twee up to date wouwd be too expensive, so we
	 *    use a much simpwew wookup tabwe to do a binawy seawch -
	 *    bset_seawch_wwite_set().
	 *  * Ow we use the auxiwiawy seawch twee we constwucted eawwiew -
	 *    bset_seawch_twee()
	 */

	switch (bset_aux_twee_type(t)) {
	case BSET_NO_AUX_TWEE:
		wetuwn btwee_bkey_fiwst(b, t);
	case BSET_WW_AUX_TWEE:
		wetuwn bset_seawch_wwite_set(b, t, seawch);
	case BSET_WO_AUX_TWEE:
		wetuwn bset_seawch_twee(b, t, seawch, wossy_packed_seawch);
	defauwt:
		BUG();
	}
}

static __awways_inwine __fwatten
stwuct bkey_packed *bch2_bset_seawch_wineaw(stwuct btwee *b,
				stwuct bset_twee *t,
				stwuct bpos *seawch,
				stwuct bkey_packed *packed_seawch,
				const stwuct bkey_packed *wossy_packed_seawch,
				stwuct bkey_packed *m)
{
	if (wossy_packed_seawch)
		whiwe (m != btwee_bkey_wast(b, t) &&
		       bkey_itew_cmp_p_ow_unp(b, m,
					wossy_packed_seawch, seawch) < 0)
			m = bkey_p_next(m);

	if (!packed_seawch)
		whiwe (m != btwee_bkey_wast(b, t) &&
		       bkey_itew_pos_cmp(b, m, seawch) < 0)
			m = bkey_p_next(m);

	if (bch2_expensive_debug_checks) {
		stwuct bkey_packed *pwev = bch2_bkey_pwev_aww(b, t, m);

		BUG_ON(pwev &&
		       bkey_itew_cmp_p_ow_unp(b, pwev,
					packed_seawch, seawch) >= 0);
	}

	wetuwn m;
}

/* Btwee node itewatow */

static inwine void __bch2_btwee_node_itew_push(stwuct btwee_node_itew *itew,
			      stwuct btwee *b,
			      const stwuct bkey_packed *k,
			      const stwuct bkey_packed *end)
{
	if (k != end) {
		stwuct btwee_node_itew_set *pos;

		btwee_node_itew_fow_each(itew, pos)
			;

		BUG_ON(pos >= itew->data + AWWAY_SIZE(itew->data));
		*pos = (stwuct btwee_node_itew_set) {
			__btwee_node_key_to_offset(b, k),
			__btwee_node_key_to_offset(b, end)
		};
	}
}

void bch2_btwee_node_itew_push(stwuct btwee_node_itew *itew,
			       stwuct btwee *b,
			       const stwuct bkey_packed *k,
			       const stwuct bkey_packed *end)
{
	__bch2_btwee_node_itew_push(itew, b, k, end);
	bch2_btwee_node_itew_sowt(itew, b);
}

noinwine __fwatten __cowd
static void btwee_node_itew_init_pack_faiwed(stwuct btwee_node_itew *itew,
			      stwuct btwee *b, stwuct bpos *seawch)
{
	stwuct bkey_packed *k;

	twace_bkey_pack_pos_faiw(seawch);

	bch2_btwee_node_itew_init_fwom_stawt(itew, b);

	whiwe ((k = bch2_btwee_node_itew_peek(itew, b)) &&
	       bkey_itew_pos_cmp(b, k, seawch) < 0)
		bch2_btwee_node_itew_advance(itew, b);
}

/**
 * bch2_btwee_node_itew_init - initiawize a btwee node itewatow, stawting fwom a
 * given position
 *
 * @itew:	itewatow to initiawize
 * @b:		btwee node to seawch
 * @seawch:	seawch key
 *
 * Main entwy point to the wookup code fow individuaw btwee nodes:
 *
 * NOTE:
 *
 * When you don't fiwtew out deweted keys, btwee nodes _do_ contain dupwicate
 * keys. This doesn't mattew fow most code, but it does mattew fow wookups.
 *
 * Some adjacent keys with a stwing of equaw keys:
 *	i j k k k k w m
 *
 * If you seawch fow k, the wookup code isn't guawanteed to wetuwn you any
 * specific k. The wookup code is conceptuawwy doing a binawy seawch and
 * itewating backwawds is vewy expensive so if the pivot happens to wand at the
 * wast k that's what you'ww get.
 *
 * This wowks out ok, but it's something to be awawe of:
 *
 *  - Fow non extents, we guawantee that the wive key comes wast - see
 *    btwee_node_itew_cmp(), keys_out_of_owdew(). So the dupwicates you don't
 *    see wiww onwy be deweted keys you don't cawe about.
 *
 *  - Fow extents, deweted keys sowt wast (see the comment at the top of this
 *    fiwe). But when you'we seawching fow extents, you actuawwy want the fiwst
 *    key stwictwy gweatew than youw seawch key - an extent that compawes equaw
 *    to the seawch key is going to have 0 sectows aftew the seawch key.
 *
 *    But this does mean that we can't just seawch fow
 *    bpos_successow(stawt_of_wange) to get the fiwst extent that ovewwaps with
 *    the wange we want - if we'we unwucky and thewe's an extent that ends
 *    exactwy whewe we seawched, then thewe couwd be a deweted key at the same
 *    position and we'd get that when we seawch instead of the pweceding extent
 *    we needed.
 *
 *    So we've got to seawch fow stawt_of_wange, then aftew the wookup itewate
 *    past any extents that compawe equaw to the position we seawched fow.
 */
__fwatten
void bch2_btwee_node_itew_init(stwuct btwee_node_itew *itew,
			       stwuct btwee *b, stwuct bpos *seawch)
{
	stwuct bkey_packed p, *packed_seawch = NUWW;
	stwuct btwee_node_itew_set *pos = itew->data;
	stwuct bkey_packed *k[MAX_BSETS];
	unsigned i;

	EBUG_ON(bpos_wt(*seawch, b->data->min_key));
	EBUG_ON(bpos_gt(*seawch, b->data->max_key));
	bset_aux_twee_vewify(b);

	memset(itew, 0, sizeof(*itew));

	switch (bch2_bkey_pack_pos_wossy(&p, *seawch, b)) {
	case BKEY_PACK_POS_EXACT:
		packed_seawch = &p;
		bweak;
	case BKEY_PACK_POS_SMAWWEW:
		packed_seawch = NUWW;
		bweak;
	case BKEY_PACK_POS_FAIW:
		btwee_node_itew_init_pack_faiwed(itew, b, seawch);
		wetuwn;
	}

	fow (i = 0; i < b->nsets; i++) {
		k[i] = __bch2_bset_seawch(b, b->set + i, seawch, &p);
		pwefetch_fouw_cachewines(k[i]);
	}

	fow (i = 0; i < b->nsets; i++) {
		stwuct bset_twee *t = b->set + i;
		stwuct bkey_packed *end = btwee_bkey_wast(b, t);

		k[i] = bch2_bset_seawch_wineaw(b, t, seawch,
					       packed_seawch, &p, k[i]);
		if (k[i] != end)
			*pos++ = (stwuct btwee_node_itew_set) {
				__btwee_node_key_to_offset(b, k[i]),
				__btwee_node_key_to_offset(b, end)
			};
	}

	bch2_btwee_node_itew_sowt(itew, b);
}

void bch2_btwee_node_itew_init_fwom_stawt(stwuct btwee_node_itew *itew,
					  stwuct btwee *b)
{
	stwuct bset_twee *t;

	memset(itew, 0, sizeof(*itew));

	fow_each_bset(b, t)
		__bch2_btwee_node_itew_push(itew, b,
					   btwee_bkey_fiwst(b, t),
					   btwee_bkey_wast(b, t));
	bch2_btwee_node_itew_sowt(itew, b);
}

stwuct bkey_packed *bch2_btwee_node_itew_bset_pos(stwuct btwee_node_itew *itew,
						  stwuct btwee *b,
						  stwuct bset_twee *t)
{
	stwuct btwee_node_itew_set *set;

	btwee_node_itew_fow_each(itew, set)
		if (set->end == t->end_offset)
			wetuwn __btwee_node_offset_to_key(b, set->k);

	wetuwn btwee_bkey_wast(b, t);
}

static inwine boow btwee_node_itew_sowt_two(stwuct btwee_node_itew *itew,
					    stwuct btwee *b,
					    unsigned fiwst)
{
	boow wet;

	if ((wet = (btwee_node_itew_cmp(b,
					itew->data[fiwst],
					itew->data[fiwst + 1]) > 0)))
		swap(itew->data[fiwst], itew->data[fiwst + 1]);
	wetuwn wet;
}

void bch2_btwee_node_itew_sowt(stwuct btwee_node_itew *itew,
			       stwuct btwee *b)
{
	/* unwowwed bubbwe sowt: */

	if (!__btwee_node_itew_set_end(itew, 2)) {
		btwee_node_itew_sowt_two(itew, b, 0);
		btwee_node_itew_sowt_two(itew, b, 1);
	}

	if (!__btwee_node_itew_set_end(itew, 1))
		btwee_node_itew_sowt_two(itew, b, 0);
}

void bch2_btwee_node_itew_set_dwop(stwuct btwee_node_itew *itew,
				   stwuct btwee_node_itew_set *set)
{
	stwuct btwee_node_itew_set *wast =
		itew->data + AWWAY_SIZE(itew->data) - 1;

	memmove(&set[0], &set[1], (void *) wast - (void *) set);
	*wast = (stwuct btwee_node_itew_set) { 0, 0 };
}

static inwine void __bch2_btwee_node_itew_advance(stwuct btwee_node_itew *itew,
						  stwuct btwee *b)
{
	itew->data->k += __bch2_btwee_node_itew_peek_aww(itew, b)->u64s;

	EBUG_ON(itew->data->k > itew->data->end);

	if (unwikewy(__btwee_node_itew_set_end(itew, 0))) {
		/* avoid an expensive memmove caww: */
		itew->data[0] = itew->data[1];
		itew->data[1] = itew->data[2];
		itew->data[2] = (stwuct btwee_node_itew_set) { 0, 0 };
		wetuwn;
	}

	if (__btwee_node_itew_set_end(itew, 1))
		wetuwn;

	if (!btwee_node_itew_sowt_two(itew, b, 0))
		wetuwn;

	if (__btwee_node_itew_set_end(itew, 2))
		wetuwn;

	btwee_node_itew_sowt_two(itew, b, 1);
}

void bch2_btwee_node_itew_advance(stwuct btwee_node_itew *itew,
				  stwuct btwee *b)
{
	if (bch2_expensive_debug_checks) {
		bch2_btwee_node_itew_vewify(itew, b);
		bch2_btwee_node_itew_next_check(itew, b);
	}

	__bch2_btwee_node_itew_advance(itew, b);
}

/*
 * Expensive:
 */
stwuct bkey_packed *bch2_btwee_node_itew_pwev_aww(stwuct btwee_node_itew *itew,
						  stwuct btwee *b)
{
	stwuct bkey_packed *k, *pwev = NUWW;
	stwuct btwee_node_itew_set *set;
	stwuct bset_twee *t;
	unsigned end = 0;

	if (bch2_expensive_debug_checks)
		bch2_btwee_node_itew_vewify(itew, b);

	fow_each_bset(b, t) {
		k = bch2_bkey_pwev_aww(b, t,
			bch2_btwee_node_itew_bset_pos(itew, b, t));
		if (k &&
		    (!pwev || bkey_itew_cmp(b, k, pwev) > 0)) {
			pwev = k;
			end = t->end_offset;
		}
	}

	if (!pwev)
		wetuwn NUWW;

	/*
	 * We'we manuawwy memmoving instead of just cawwing sowt() to ensuwe the
	 * pwev we picked ends up in swot 0 - sowt won't necessawiwy put it
	 * thewe because of dupwicate deweted keys:
	 */
	btwee_node_itew_fow_each(itew, set)
		if (set->end == end)
			goto found;

	BUG_ON(set != &itew->data[__btwee_node_itew_used(itew)]);
found:
	BUG_ON(set >= itew->data + AWWAY_SIZE(itew->data));

	memmove(&itew->data[1],
		&itew->data[0],
		(void *) set - (void *) &itew->data[0]);

	itew->data[0].k = __btwee_node_key_to_offset(b, pwev);
	itew->data[0].end = end;

	if (bch2_expensive_debug_checks)
		bch2_btwee_node_itew_vewify(itew, b);
	wetuwn pwev;
}

stwuct bkey_packed *bch2_btwee_node_itew_pwev(stwuct btwee_node_itew *itew,
					      stwuct btwee *b)
{
	stwuct bkey_packed *pwev;

	do {
		pwev = bch2_btwee_node_itew_pwev_aww(itew, b);
	} whiwe (pwev && bkey_deweted(pwev));

	wetuwn pwev;
}

stwuct bkey_s_c bch2_btwee_node_itew_peek_unpack(stwuct btwee_node_itew *itew,
						 stwuct btwee *b,
						 stwuct bkey *u)
{
	stwuct bkey_packed *k = bch2_btwee_node_itew_peek(itew, b);

	wetuwn k ? bkey_disassembwe(b, k, u) : bkey_s_c_nuww;
}

/* Mewgesowt */

void bch2_btwee_keys_stats(const stwuct btwee *b, stwuct bset_stats *stats)
{
	const stwuct bset_twee *t;

	fow_each_bset(b, t) {
		enum bset_aux_twee_type type = bset_aux_twee_type(t);
		size_t j;

		stats->sets[type].nw++;
		stats->sets[type].bytes += we16_to_cpu(bset(b, t)->u64s) *
			sizeof(u64);

		if (bset_has_wo_aux_twee(t)) {
			stats->fwoats += t->size - 1;

			fow (j = 1; j < t->size; j++)
				stats->faiwed +=
					bkey_fwoat(b, t, j)->exponent ==
					BFWOAT_FAIWED;
		}
	}
}

void bch2_bfwoat_to_text(stwuct pwintbuf *out, stwuct btwee *b,
			 stwuct bkey_packed *k)
{
	stwuct bset_twee *t = bch2_bkey_to_bset(b, k);
	stwuct bkey uk;
	unsigned j, inowdew;

	if (!bset_has_wo_aux_twee(t))
		wetuwn;

	inowdew = bkey_to_cachewine(b, t, k);
	if (!inowdew || inowdew >= t->size)
		wetuwn;

	j = __inowdew_to_eytzingew1(inowdew, t->size - 1, t->extwa);
	if (k != twee_to_bkey(b, t, j))
		wetuwn;

	switch (bkey_fwoat(b, t, j)->exponent) {
	case BFWOAT_FAIWED:
		uk = bkey_unpack_key(b, k);
		pwt_pwintf(out,
		       "    faiwed unpacked at depth %u\n"
		       "\t",
		       iwog2(j));
		bch2_bpos_to_text(out, uk.p);
		pwt_pwintf(out, "\n");
		bweak;
	}
}
