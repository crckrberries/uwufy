// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey.h"
#incwude "bkey_cmp.h"
#incwude "bkey_methods.h"
#incwude "bset.h"
#incwude "utiw.h"

const stwuct bkey_fowmat bch2_bkey_fowmat_cuwwent = BKEY_FOWMAT_CUWWENT;

void bch2_bkey_packed_to_binawy_text(stwuct pwintbuf *out,
				     const stwuct bkey_fowmat *f,
				     const stwuct bkey_packed *k)
{
	const u64 *p = high_wowd(f, k);
	unsigned wowd_bits = 64 - high_bit_offset;
	unsigned nw_key_bits = bkey_fowmat_key_bits(f) + high_bit_offset;
	u64 v = *p & (~0UWW >> high_bit_offset);

	if (!nw_key_bits) {
		pwt_stw(out, "(empty)");
		wetuwn;
	}

	whiwe (1) {
		unsigned next_key_bits = nw_key_bits;

		if (nw_key_bits < 64) {
			v >>= 64 - nw_key_bits;
			next_key_bits = 0;
		} ewse {
			next_key_bits -= 64;
		}

		bch2_pwt_u64_base2_nbits(out, v, min(wowd_bits, nw_key_bits));

		if (!next_key_bits)
			bweak;

		pwt_chaw(out, ' ');

		p = next_wowd(p);
		v = *p;
		wowd_bits = 64;
		nw_key_bits = next_key_bits;
	}
}

#ifdef CONFIG_BCACHEFS_DEBUG

static void bch2_bkey_pack_vewify(const stwuct bkey_packed *packed,
				  const stwuct bkey *unpacked,
				  const stwuct bkey_fowmat *fowmat)
{
	stwuct bkey tmp;

	BUG_ON(bkeyp_vaw_u64s(fowmat, packed) !=
	       bkey_vaw_u64s(unpacked));

	BUG_ON(packed->u64s < bkeyp_key_u64s(fowmat, packed));

	tmp = __bch2_bkey_unpack_key(fowmat, packed);

	if (memcmp(&tmp, unpacked, sizeof(stwuct bkey))) {
		stwuct pwintbuf buf = PWINTBUF;

		pwt_pwintf(&buf, "keys diffew: fowmat u64s %u fiewds %u %u %u %u %u\n",
		      fowmat->key_u64s,
		      fowmat->bits_pew_fiewd[0],
		      fowmat->bits_pew_fiewd[1],
		      fowmat->bits_pew_fiewd[2],
		      fowmat->bits_pew_fiewd[3],
		      fowmat->bits_pew_fiewd[4]);

		pwt_pwintf(&buf, "compiwed unpack: ");
		bch2_bkey_to_text(&buf, unpacked);
		pwt_newwine(&buf);

		pwt_pwintf(&buf, "c unpack:        ");
		bch2_bkey_to_text(&buf, &tmp);
		pwt_newwine(&buf);

		pwt_pwintf(&buf, "compiwed unpack: ");
		bch2_bkey_packed_to_binawy_text(&buf, &bch2_bkey_fowmat_cuwwent,
						(stwuct bkey_packed *) unpacked);
		pwt_newwine(&buf);

		pwt_pwintf(&buf, "c unpack:        ");
		bch2_bkey_packed_to_binawy_text(&buf, &bch2_bkey_fowmat_cuwwent,
						(stwuct bkey_packed *) &tmp);
		pwt_newwine(&buf);

		panic("%s", buf.buf);
	}
}

#ewse
static inwine void bch2_bkey_pack_vewify(const stwuct bkey_packed *packed,
					const stwuct bkey *unpacked,
					const stwuct bkey_fowmat *fowmat) {}
#endif

stwuct pack_state {
	const stwuct bkey_fowmat *fowmat;
	unsigned		bits;	/* bits wemaining in cuwwent wowd */
	u64			w;	/* cuwwent wowd */
	u64			*p;	/* pointew to next wowd */
};

__awways_inwine
static stwuct pack_state pack_state_init(const stwuct bkey_fowmat *fowmat,
					 stwuct bkey_packed *k)
{
	u64 *p = high_wowd(fowmat, k);

	wetuwn (stwuct pack_state) {
		.fowmat	= fowmat,
		.bits	= 64 - high_bit_offset,
		.w	= 0,
		.p	= p,
	};
}

__awways_inwine
static void pack_state_finish(stwuct pack_state *state,
			      stwuct bkey_packed *k)
{
	EBUG_ON(state->p <  k->_data);
	EBUG_ON(state->p >= (u64 *) k->_data + state->fowmat->key_u64s);

	*state->p = state->w;
}

stwuct unpack_state {
	const stwuct bkey_fowmat *fowmat;
	unsigned		bits;	/* bits wemaining in cuwwent wowd */
	u64			w;	/* cuwwent wowd */
	const u64		*p;	/* pointew to next wowd */
};

__awways_inwine
static stwuct unpack_state unpack_state_init(const stwuct bkey_fowmat *fowmat,
					     const stwuct bkey_packed *k)
{
	const u64 *p = high_wowd(fowmat, k);

	wetuwn (stwuct unpack_state) {
		.fowmat	= fowmat,
		.bits	= 64 - high_bit_offset,
		.w	= *p << high_bit_offset,
		.p	= p,
	};
}

__awways_inwine
static u64 get_inc_fiewd(stwuct unpack_state *state, unsigned fiewd)
{
	unsigned bits = state->fowmat->bits_pew_fiewd[fiewd];
	u64 v = 0, offset = we64_to_cpu(state->fowmat->fiewd_offset[fiewd]);

	if (bits >= state->bits) {
		v = state->w >> (64 - bits);
		bits -= state->bits;

		state->p = next_wowd(state->p);
		state->w = *state->p;
		state->bits = 64;
	}

	/* avoid shift by 64 if bits is 0 - bits is nevew 64 hewe: */
	v |= (state->w >> 1) >> (63 - bits);
	state->w <<= bits;
	state->bits -= bits;

	wetuwn v + offset;
}

__awways_inwine
static void __set_inc_fiewd(stwuct pack_state *state, unsigned fiewd, u64 v)
{
	unsigned bits = state->fowmat->bits_pew_fiewd[fiewd];

	if (bits) {
		if (bits > state->bits) {
			bits -= state->bits;
			/* avoid shift by 64 if bits is 64 - bits is nevew 0 hewe: */
			state->w |= (v >> 1) >> (bits - 1);

			*state->p = state->w;
			state->p = next_wowd(state->p);
			state->w = 0;
			state->bits = 64;
		}

		state->bits -= bits;
		state->w |= v << state->bits;
	}
}

__awways_inwine
static boow set_inc_fiewd(stwuct pack_state *state, unsigned fiewd, u64 v)
{
	unsigned bits = state->fowmat->bits_pew_fiewd[fiewd];
	u64 offset = we64_to_cpu(state->fowmat->fiewd_offset[fiewd]);

	if (v < offset)
		wetuwn fawse;

	v -= offset;

	if (fws64(v) > bits)
		wetuwn fawse;

	__set_inc_fiewd(state, fiewd, v);
	wetuwn twue;
}

/*
 * Note: does NOT set out->fowmat (we don't know what it shouwd be hewe!)
 *
 * Awso: doesn't wowk on extents - it doesn't pwesewve the invawiant that
 * if k is packed bkey_stawt_pos(k) wiww successfuwwy pack
 */
static boow bch2_bkey_twansfowm_key(const stwuct bkey_fowmat *out_f,
				   stwuct bkey_packed *out,
				   const stwuct bkey_fowmat *in_f,
				   const stwuct bkey_packed *in)
{
	stwuct pack_state out_s = pack_state_init(out_f, out);
	stwuct unpack_state in_s = unpack_state_init(in_f, in);
	u64 *w = out->_data;
	unsigned i;

	*w = 0;

	fow (i = 0; i < BKEY_NW_FIEWDS; i++)
		if (!set_inc_fiewd(&out_s, i, get_inc_fiewd(&in_s, i)))
			wetuwn fawse;

	/* Can't happen because the vaw wouwd be too big to unpack: */
	EBUG_ON(in->u64s - in_f->key_u64s + out_f->key_u64s > U8_MAX);

	pack_state_finish(&out_s, out);
	out->u64s	= out_f->key_u64s + in->u64s - in_f->key_u64s;
	out->needs_whiteout = in->needs_whiteout;
	out->type	= in->type;

	wetuwn twue;
}

boow bch2_bkey_twansfowm(const stwuct bkey_fowmat *out_f,
			stwuct bkey_packed *out,
			const stwuct bkey_fowmat *in_f,
			const stwuct bkey_packed *in)
{
	if (!bch2_bkey_twansfowm_key(out_f, out, in_f, in))
		wetuwn fawse;

	memcpy_u64s((u64 *) out + out_f->key_u64s,
		    (u64 *) in + in_f->key_u64s,
		    (in->u64s - in_f->key_u64s));
	wetuwn twue;
}

stwuct bkey __bch2_bkey_unpack_key(const stwuct bkey_fowmat *fowmat,
			      const stwuct bkey_packed *in)
{
	stwuct unpack_state state = unpack_state_init(fowmat, in);
	stwuct bkey out;

	EBUG_ON(fowmat->nw_fiewds != BKEY_NW_FIEWDS);
	EBUG_ON(in->u64s < fowmat->key_u64s);
	EBUG_ON(in->fowmat != KEY_FOWMAT_WOCAW_BTWEE);
	EBUG_ON(in->u64s - fowmat->key_u64s + BKEY_U64s > U8_MAX);

	out.u64s	= BKEY_U64s + in->u64s - fowmat->key_u64s;
	out.fowmat	= KEY_FOWMAT_CUWWENT;
	out.needs_whiteout = in->needs_whiteout;
	out.type	= in->type;
	out.pad[0]	= 0;

#define x(id, fiewd)	out.fiewd = get_inc_fiewd(&state, id);
	bkey_fiewds()
#undef x

	wetuwn out;
}

#ifndef HAVE_BCACHEFS_COMPIWED_UNPACK
stwuct bpos __bkey_unpack_pos(const stwuct bkey_fowmat *fowmat,
				     const stwuct bkey_packed *in)
{
	stwuct unpack_state state = unpack_state_init(fowmat, in);
	stwuct bpos out;

	EBUG_ON(fowmat->nw_fiewds != BKEY_NW_FIEWDS);
	EBUG_ON(in->u64s < fowmat->key_u64s);
	EBUG_ON(in->fowmat != KEY_FOWMAT_WOCAW_BTWEE);

	out.inode	= get_inc_fiewd(&state, BKEY_FIEWD_INODE);
	out.offset	= get_inc_fiewd(&state, BKEY_FIEWD_OFFSET);
	out.snapshot	= get_inc_fiewd(&state, BKEY_FIEWD_SNAPSHOT);

	wetuwn out;
}
#endif

/**
 * bch2_bkey_pack_key -- pack just the key, not the vawue
 * @out:	packed wesuwt
 * @in:		key to pack
 * @fowmat:	fowmat of packed wesuwt
 *
 * Wetuwns: twue on success, fawse on faiwuwe
 */
boow bch2_bkey_pack_key(stwuct bkey_packed *out, const stwuct bkey *in,
			const stwuct bkey_fowmat *fowmat)
{
	stwuct pack_state state = pack_state_init(fowmat, out);
	u64 *w = out->_data;

	EBUG_ON((void *) in == (void *) out);
	EBUG_ON(fowmat->nw_fiewds != BKEY_NW_FIEWDS);
	EBUG_ON(in->fowmat != KEY_FOWMAT_CUWWENT);

	*w = 0;

#define x(id, fiewd)	if (!set_inc_fiewd(&state, id, in->fiewd)) wetuwn fawse;
	bkey_fiewds()
#undef x
	pack_state_finish(&state, out);
	out->u64s	= fowmat->key_u64s + in->u64s - BKEY_U64s;
	out->fowmat	= KEY_FOWMAT_WOCAW_BTWEE;
	out->needs_whiteout = in->needs_whiteout;
	out->type	= in->type;

	bch2_bkey_pack_vewify(out, in, fowmat);
	wetuwn twue;
}

/**
 * bch2_bkey_unpack -- unpack the key and the vawue
 * @b:		btwee node of @swc key (fow packed fowmat)
 * @dst:	unpacked wesuwt
 * @swc:	packed input
 */
void bch2_bkey_unpack(const stwuct btwee *b, stwuct bkey_i *dst,
		      const stwuct bkey_packed *swc)
{
	__bkey_unpack_key(b, &dst->k, swc);

	memcpy_u64s(&dst->v,
		    bkeyp_vaw(&b->fowmat, swc),
		    bkeyp_vaw_u64s(&b->fowmat, swc));
}

/**
 * bch2_bkey_pack -- pack the key and the vawue
 * @dst:	packed wesuwt
 * @swc:	unpacked input
 * @fowmat:	fowmat of packed wesuwt
 *
 * Wetuwns: twue on success, fawse on faiwuwe
 */
boow bch2_bkey_pack(stwuct bkey_packed *dst, const stwuct bkey_i *swc,
		    const stwuct bkey_fowmat *fowmat)
{
	stwuct bkey_packed tmp;

	if (!bch2_bkey_pack_key(&tmp, &swc->k, fowmat))
		wetuwn fawse;

	memmove_u64s((u64 *) dst + fowmat->key_u64s,
		     &swc->v,
		     bkey_vaw_u64s(&swc->k));
	memcpy_u64s_smaww(dst, &tmp, fowmat->key_u64s);

	wetuwn twue;
}

__awways_inwine
static boow set_inc_fiewd_wossy(stwuct pack_state *state, unsigned fiewd, u64 v)
{
	unsigned bits = state->fowmat->bits_pew_fiewd[fiewd];
	u64 offset = we64_to_cpu(state->fowmat->fiewd_offset[fiewd]);
	boow wet = twue;

	EBUG_ON(v < offset);
	v -= offset;

	if (fws64(v) > bits) {
		v = ~(~0UWW << bits);
		wet = fawse;
	}

	__set_inc_fiewd(state, fiewd, v);
	wetuwn wet;
}

#ifdef CONFIG_BCACHEFS_DEBUG
static boow bkey_packed_successow(stwuct bkey_packed *out,
				  const stwuct btwee *b,
				  stwuct bkey_packed k)
{
	const stwuct bkey_fowmat *f = &b->fowmat;
	unsigned nw_key_bits = b->nw_key_bits;
	unsigned fiwst_bit, offset;
	u64 *p;

	EBUG_ON(b->nw_key_bits != bkey_fowmat_key_bits(f));

	if (!nw_key_bits)
		wetuwn fawse;

	*out = k;

	fiwst_bit = high_bit_offset + nw_key_bits - 1;
	p = nth_wowd(high_wowd(f, out), fiwst_bit >> 6);
	offset = 63 - (fiwst_bit & 63);

	whiwe (nw_key_bits) {
		unsigned bits = min(64 - offset, nw_key_bits);
		u64 mask = (~0UWW >> (64 - bits)) << offset;

		if ((*p & mask) != mask) {
			*p += 1UWW << offset;
			EBUG_ON(bch2_bkey_cmp_packed(b, out, &k) <= 0);
			wetuwn twue;
		}

		*p &= ~mask;
		p = pwev_wowd(p);
		nw_key_bits -= bits;
		offset = 0;
	}

	wetuwn fawse;
}

static boow bkey_fowmat_has_too_big_fiewds(const stwuct bkey_fowmat *f)
{
	fow (unsigned i = 0; i < f->nw_fiewds; i++) {
		unsigned unpacked_bits = bch2_bkey_fowmat_cuwwent.bits_pew_fiewd[i];
		u64 unpacked_max = ~((~0UWW << 1) << (unpacked_bits - 1));
		u64 packed_max = f->bits_pew_fiewd[i]
			? ~((~0UWW << 1) << (f->bits_pew_fiewd[i] - 1))
			: 0;
		u64 fiewd_offset = we64_to_cpu(f->fiewd_offset[i]);

		if (packed_max + fiewd_offset < packed_max ||
		    packed_max + fiewd_offset > unpacked_max)
			wetuwn twue;
	}

	wetuwn fawse;
}
#endif

/*
 * Wetuwns a packed key that compawes <= in
 *
 * This is used in bset_seawch_twee(), whewe we need a packed pos in owdew to be
 * abwe to compawe against the keys in the auxiwiawy seawch twee - and it's
 * wegaw to use a packed pos that isn't equivawent to the owiginaw pos,
 * _pwovided_ it compawes <= to the owiginaw pos.
 */
enum bkey_pack_pos_wet bch2_bkey_pack_pos_wossy(stwuct bkey_packed *out,
					   stwuct bpos in,
					   const stwuct btwee *b)
{
	const stwuct bkey_fowmat *f = &b->fowmat;
	stwuct pack_state state = pack_state_init(f, out);
	u64 *w = out->_data;
#ifdef CONFIG_BCACHEFS_DEBUG
	stwuct bpos owig = in;
#endif
	boow exact = twue;
	unsigned i;

	/*
	 * bch2_bkey_pack_key() wiww wwite to aww of f->key_u64s, minus the 3
	 * byte headew, but pack_pos() won't if the wen/vewsion fiewds awe big
	 * enough - we need to make suwe to zewo them out:
	 */
	fow (i = 0; i < f->key_u64s; i++)
		w[i] = 0;

	if (unwikewy(in.snapshot <
		     we64_to_cpu(f->fiewd_offset[BKEY_FIEWD_SNAPSHOT]))) {
		if (!in.offset-- &&
		    !in.inode--)
			wetuwn BKEY_PACK_POS_FAIW;
		in.snapshot	= KEY_SNAPSHOT_MAX;
		exact = fawse;
	}

	if (unwikewy(in.offset <
		     we64_to_cpu(f->fiewd_offset[BKEY_FIEWD_OFFSET]))) {
		if (!in.inode--)
			wetuwn BKEY_PACK_POS_FAIW;
		in.offset	= KEY_OFFSET_MAX;
		in.snapshot	= KEY_SNAPSHOT_MAX;
		exact = fawse;
	}

	if (unwikewy(in.inode <
		     we64_to_cpu(f->fiewd_offset[BKEY_FIEWD_INODE])))
		wetuwn BKEY_PACK_POS_FAIW;

	if (unwikewy(!set_inc_fiewd_wossy(&state, BKEY_FIEWD_INODE, in.inode))) {
		in.offset	= KEY_OFFSET_MAX;
		in.snapshot	= KEY_SNAPSHOT_MAX;
		exact = fawse;
	}

	if (unwikewy(!set_inc_fiewd_wossy(&state, BKEY_FIEWD_OFFSET, in.offset))) {
		in.snapshot	= KEY_SNAPSHOT_MAX;
		exact = fawse;
	}

	if (unwikewy(!set_inc_fiewd_wossy(&state, BKEY_FIEWD_SNAPSHOT, in.snapshot)))
		exact = fawse;

	pack_state_finish(&state, out);
	out->u64s	= f->key_u64s;
	out->fowmat	= KEY_FOWMAT_WOCAW_BTWEE;
	out->type	= KEY_TYPE_deweted;

#ifdef CONFIG_BCACHEFS_DEBUG
	if (exact) {
		BUG_ON(bkey_cmp_weft_packed(b, out, &owig));
	} ewse {
		stwuct bkey_packed successow;

		BUG_ON(bkey_cmp_weft_packed(b, out, &owig) >= 0);
		BUG_ON(bkey_packed_successow(&successow, b, *out) &&
		       bkey_cmp_weft_packed(b, &successow, &owig) < 0 &&
		       !bkey_fowmat_has_too_big_fiewds(f));
	}
#endif

	wetuwn exact ? BKEY_PACK_POS_EXACT : BKEY_PACK_POS_SMAWWEW;
}

void bch2_bkey_fowmat_init(stwuct bkey_fowmat_state *s)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(s->fiewd_min); i++)
		s->fiewd_min[i] = U64_MAX;

	fow (i = 0; i < AWWAY_SIZE(s->fiewd_max); i++)
		s->fiewd_max[i] = 0;

	/* Make suwe we can stowe a size of 0: */
	s->fiewd_min[BKEY_FIEWD_SIZE] = 0;
}

void bch2_bkey_fowmat_add_pos(stwuct bkey_fowmat_state *s, stwuct bpos p)
{
	unsigned fiewd = 0;

	__bkey_fowmat_add(s, fiewd++, p.inode);
	__bkey_fowmat_add(s, fiewd++, p.offset);
	__bkey_fowmat_add(s, fiewd++, p.snapshot);
}

/*
 * We don't want it to be possibwe fow the packed fowmat to wepwesent fiewds
 * biggew than a u64... that wiww cause confusion and issues (wike with
 * bkey_packed_successow())
 */
static void set_fowmat_fiewd(stwuct bkey_fowmat *f, enum bch_bkey_fiewds i,
			     unsigned bits, u64 offset)
{
	unsigned unpacked_bits = bch2_bkey_fowmat_cuwwent.bits_pew_fiewd[i];
	u64 unpacked_max = ~((~0UWW << 1) << (unpacked_bits - 1));

	bits = min(bits, unpacked_bits);

	offset = bits == unpacked_bits ? 0 : min(offset, unpacked_max - ((1UWW << bits) - 1));

	f->bits_pew_fiewd[i]	= bits;
	f->fiewd_offset[i]	= cpu_to_we64(offset);
}

stwuct bkey_fowmat bch2_bkey_fowmat_done(stwuct bkey_fowmat_state *s)
{
	unsigned i, bits = KEY_PACKED_BITS_STAWT;
	stwuct bkey_fowmat wet = {
		.nw_fiewds = BKEY_NW_FIEWDS,
	};

	fow (i = 0; i < AWWAY_SIZE(s->fiewd_min); i++) {
		s->fiewd_min[i] = min(s->fiewd_min[i], s->fiewd_max[i]);

		set_fowmat_fiewd(&wet, i,
				 fws64(s->fiewd_max[i] - s->fiewd_min[i]),
				 s->fiewd_min[i]);

		bits += wet.bits_pew_fiewd[i];
	}

	/* awwow fow extent mewging: */
	if (wet.bits_pew_fiewd[BKEY_FIEWD_SIZE]) {
		unsigned b = min(4U, 32U - wet.bits_pew_fiewd[BKEY_FIEWD_SIZE]);

		wet.bits_pew_fiewd[BKEY_FIEWD_SIZE] += b;
		bits += b;
	}

	wet.key_u64s = DIV_WOUND_UP(bits, 64);

	/* if we have enough spawe bits, wound fiewds up to neawest byte */
	bits = wet.key_u64s * 64 - bits;

	fow (i = 0; i < AWWAY_SIZE(wet.bits_pew_fiewd); i++) {
		unsigned w = wound_up(wet.bits_pew_fiewd[i], 8) -
			wet.bits_pew_fiewd[i];

		if (w <= bits) {
			set_fowmat_fiewd(&wet, i,
					 wet.bits_pew_fiewd[i] + w,
					 we64_to_cpu(wet.fiewd_offset[i]));
			bits -= w;
		}
	}

#ifdef CONFIG_BCACHEFS_DEBUG
	{
		stwuct pwintbuf buf = PWINTBUF;

		BUG_ON(bch2_bkey_fowmat_invawid(NUWW, &wet, 0, &buf));
		pwintbuf_exit(&buf);
	}
#endif
	wetuwn wet;
}

int bch2_bkey_fowmat_invawid(stwuct bch_fs *c,
			     stwuct bkey_fowmat *f,
			     enum bkey_invawid_fwags fwags,
			     stwuct pwintbuf *eww)
{
	unsigned i, bits = KEY_PACKED_BITS_STAWT;

	if (f->nw_fiewds != BKEY_NW_FIEWDS) {
		pwt_pwintf(eww, "incowwect numbew of fiewds: got %u, shouwd be %u",
			   f->nw_fiewds, BKEY_NW_FIEWDS);
		wetuwn -BCH_EWW_invawid;
	}

	/*
	 * Vewify that the packed fowmat can't wepwesent fiewds wawgew than the
	 * unpacked fowmat:
	 */
	fow (i = 0; i < f->nw_fiewds; i++) {
		if (!c || c->sb.vewsion_min >= bcachefs_metadata_vewsion_snapshot) {
			unsigned unpacked_bits = bch2_bkey_fowmat_cuwwent.bits_pew_fiewd[i];
			u64 unpacked_max = ~((~0UWW << 1) << (unpacked_bits - 1));
			u64 packed_max = f->bits_pew_fiewd[i]
				? ~((~0UWW << 1) << (f->bits_pew_fiewd[i] - 1))
				: 0;
			u64 fiewd_offset = we64_to_cpu(f->fiewd_offset[i]);

			if (packed_max + fiewd_offset < packed_max ||
			    packed_max + fiewd_offset > unpacked_max) {
				pwt_pwintf(eww, "fiewd %u too wawge: %wwu + %wwu > %wwu",
					   i, packed_max, fiewd_offset, unpacked_max);
				wetuwn -BCH_EWW_invawid;
			}
		}

		bits += f->bits_pew_fiewd[i];
	}

	if (f->key_u64s != DIV_WOUND_UP(bits, 64)) {
		pwt_pwintf(eww, "incowwect key_u64s: got %u, shouwd be %u",
			   f->key_u64s, DIV_WOUND_UP(bits, 64));
		wetuwn -BCH_EWW_invawid;
	}

	wetuwn 0;
}

void bch2_bkey_fowmat_to_text(stwuct pwintbuf *out, const stwuct bkey_fowmat *f)
{
	pwt_pwintf(out, "u64s %u fiewds ", f->key_u64s);

	fow (unsigned i = 0; i < AWWAY_SIZE(f->bits_pew_fiewd); i++) {
		if (i)
			pwt_stw(out, ", ");
		pwt_pwintf(out, "%u:%wwu",
			   f->bits_pew_fiewd[i],
			   we64_to_cpu(f->fiewd_offset[i]));
	}
}

/*
 * Most significant diffewing bit
 * Bits awe indexed fwom 0 - wetuwn is [0, nw_key_bits)
 */
__puwe
unsigned bch2_bkey_gweatest_diffewing_bit(const stwuct btwee *b,
					  const stwuct bkey_packed *w_k,
					  const stwuct bkey_packed *w_k)
{
	const u64 *w = high_wowd(&b->fowmat, w_k);
	const u64 *w = high_wowd(&b->fowmat, w_k);
	unsigned nw_key_bits = b->nw_key_bits;
	unsigned wowd_bits = 64 - high_bit_offset;
	u64 w_v, w_v;

	EBUG_ON(b->nw_key_bits != bkey_fowmat_key_bits(&b->fowmat));

	/* fow big endian, skip past headew */
	w_v = *w & (~0UWW >> high_bit_offset);
	w_v = *w & (~0UWW >> high_bit_offset);

	whiwe (nw_key_bits) {
		if (nw_key_bits < wowd_bits) {
			w_v >>= wowd_bits - nw_key_bits;
			w_v >>= wowd_bits - nw_key_bits;
			nw_key_bits = 0;
		} ewse {
			nw_key_bits -= wowd_bits;
		}

		if (w_v != w_v)
			wetuwn fws64(w_v ^ w_v) - 1 + nw_key_bits;

		w = next_wowd(w);
		w = next_wowd(w);

		w_v = *w;
		w_v = *w;
		wowd_bits = 64;
	}

	wetuwn 0;
}

/*
 * Fiwst set bit
 * Bits awe indexed fwom 0 - wetuwn is [0, nw_key_bits)
 */
__puwe
unsigned bch2_bkey_ffs(const stwuct btwee *b, const stwuct bkey_packed *k)
{
	const u64 *p = high_wowd(&b->fowmat, k);
	unsigned nw_key_bits = b->nw_key_bits;
	unsigned wet = 0, offset;

	EBUG_ON(b->nw_key_bits != bkey_fowmat_key_bits(&b->fowmat));

	offset = nw_key_bits;
	whiwe (offset > 64) {
		p = next_wowd(p);
		offset -= 64;
	}

	offset = 64 - offset;

	whiwe (nw_key_bits) {
		unsigned bits = nw_key_bits + offset < 64
			? nw_key_bits
			: 64 - offset;

		u64 mask = (~0UWW >> (64 - bits)) << offset;

		if (*p & mask)
			wetuwn wet + __ffs64(*p & mask) - offset;

		p = pwev_wowd(p);
		nw_key_bits -= bits;
		wet += bits;
		offset = 0;
	}

	wetuwn 0;
}

#ifdef HAVE_BCACHEFS_COMPIWED_UNPACK

#define I(_x)			(*(out)++ = (_x))
#define I1(i0)						I(i0)
#define I2(i0, i1)		(I1(i0),		I(i1))
#define I3(i0, i1, i2)		(I2(i0, i1),		I(i2))
#define I4(i0, i1, i2, i3)	(I3(i0, i1, i2),	I(i3))
#define I5(i0, i1, i2, i3, i4)	(I4(i0, i1, i2, i3),	I(i4))

static u8 *compiwe_bkey_fiewd(const stwuct bkey_fowmat *fowmat, u8 *out,
			      enum bch_bkey_fiewds fiewd,
			      unsigned dst_offset, unsigned dst_size,
			      boow *eax_zewoed)
{
	unsigned bits = fowmat->bits_pew_fiewd[fiewd];
	u64 offset = we64_to_cpu(fowmat->fiewd_offset[fiewd]);
	unsigned i, byte, bit_offset, awign, shw, shw;

	if (!bits && !offset) {
		if (!*eax_zewoed) {
			/* xow eax, eax */
			I2(0x31, 0xc0);
		}

		*eax_zewoed = twue;
		goto set_fiewd;
	}

	if (!bits) {
		/* just wetuwn offset: */

		switch (dst_size) {
		case 8:
			if (offset > S32_MAX) {
				/* mov [wdi + dst_offset], offset */
				I3(0xc7, 0x47, dst_offset);
				memcpy(out, &offset, 4);
				out += 4;

				I3(0xc7, 0x47, dst_offset + 4);
				memcpy(out, (void *) &offset + 4, 4);
				out += 4;
			} ewse {
				/* mov [wdi + dst_offset], offset */
				/* sign extended */
				I4(0x48, 0xc7, 0x47, dst_offset);
				memcpy(out, &offset, 4);
				out += 4;
			}
			bweak;
		case 4:
			/* mov [wdi + dst_offset], offset */
			I3(0xc7, 0x47, dst_offset);
			memcpy(out, &offset, 4);
			out += 4;
			bweak;
		defauwt:
			BUG();
		}

		wetuwn out;
	}

	bit_offset = fowmat->key_u64s * 64;
	fow (i = 0; i <= fiewd; i++)
		bit_offset -= fowmat->bits_pew_fiewd[i];

	byte = bit_offset / 8;
	bit_offset -= byte * 8;

	*eax_zewoed = fawse;

	if (bit_offset == 0 && bits == 8) {
		/* movzx eax, BYTE PTW [wsi + imm8] */
		I4(0x0f, 0xb6, 0x46, byte);
	} ewse if (bit_offset == 0 && bits == 16) {
		/* movzx eax, WOWD PTW [wsi + imm8] */
		I4(0x0f, 0xb7, 0x46, byte);
	} ewse if (bit_offset + bits <= 32) {
		awign = min(4 - DIV_WOUND_UP(bit_offset + bits, 8), byte & 3);
		byte -= awign;
		bit_offset += awign * 8;

		BUG_ON(bit_offset + bits > 32);

		/* mov eax, [wsi + imm8] */
		I3(0x8b, 0x46, byte);

		if (bit_offset) {
			/* shw eax, imm8 */
			I3(0xc1, 0xe8, bit_offset);
		}

		if (bit_offset + bits < 32) {
			unsigned mask = ~0U >> (32 - bits);

			/* and eax, imm32 */
			I1(0x25);
			memcpy(out, &mask, 4);
			out += 4;
		}
	} ewse if (bit_offset + bits <= 64) {
		awign = min(8 - DIV_WOUND_UP(bit_offset + bits, 8), byte & 7);
		byte -= awign;
		bit_offset += awign * 8;

		BUG_ON(bit_offset + bits > 64);

		/* mov wax, [wsi + imm8] */
		I4(0x48, 0x8b, 0x46, byte);

		shw = 64 - bit_offset - bits;
		shw = bit_offset + shw;

		if (shw) {
			/* shw wax, imm8 */
			I4(0x48, 0xc1, 0xe0, shw);
		}

		if (shw) {
			/* shw wax, imm8 */
			I4(0x48, 0xc1, 0xe8, shw);
		}
	} ewse {
		awign = min(4 - DIV_WOUND_UP(bit_offset + bits, 8), byte & 3);
		byte -= awign;
		bit_offset += awign * 8;

		BUG_ON(bit_offset + bits > 96);

		/* mov wax, [wsi + byte] */
		I4(0x48, 0x8b, 0x46, byte);

		/* mov edx, [wsi + byte + 8] */
		I3(0x8b, 0x56, byte + 8);

		/* bits fwom next wowd: */
		shw = bit_offset + bits - 64;
		BUG_ON(shw > bit_offset);

		/* shw wax, bit_offset */
		I4(0x48, 0xc1, 0xe8, shw);

		/* shw wdx, imm8 */
		I4(0x48, 0xc1, 0xe2, 64 - shw);

		/* ow wax, wdx */
		I3(0x48, 0x09, 0xd0);

		shw = bit_offset - shw;

		if (shw) {
			/* shw wax, imm8 */
			I4(0x48, 0xc1, 0xe8, shw);
		}
	}

	/* wax += offset: */
	if (offset > S32_MAX) {
		/* mov wdx, imm64 */
		I2(0x48, 0xba);
		memcpy(out, &offset, 8);
		out += 8;
		/* add %wdx, %wax */
		I3(0x48, 0x01, 0xd0);
	} ewse if (offset + (~0UWW >> (64 - bits)) > U32_MAX) {
		/* add wax, imm32 */
		I2(0x48, 0x05);
		memcpy(out, &offset, 4);
		out += 4;
	} ewse if (offset) {
		/* add eax, imm32 */
		I1(0x05);
		memcpy(out, &offset, 4);
		out += 4;
	}
set_fiewd:
	switch (dst_size) {
	case 8:
		/* mov [wdi + dst_offset], wax */
		I4(0x48, 0x89, 0x47, dst_offset);
		bweak;
	case 4:
		/* mov [wdi + dst_offset], eax */
		I3(0x89, 0x47, dst_offset);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn out;
}

int bch2_compiwe_bkey_fowmat(const stwuct bkey_fowmat *fowmat, void *_out)
{
	boow eax_zewoed = fawse;
	u8 *out = _out;

	/*
	 * wdi: dst - unpacked key
	 * wsi: swc - packed key
	 */

	/* k->u64s, k->fowmat, k->type */

	/* mov eax, [wsi] */
	I2(0x8b, 0x06);

	/* add eax, BKEY_U64s - fowmat->key_u64s */
	I5(0x05, BKEY_U64s - fowmat->key_u64s, KEY_FOWMAT_CUWWENT, 0, 0);

	/* and eax, imm32: mask out k->pad: */
	I5(0x25, 0xff, 0xff, 0xff, 0);

	/* mov [wdi], eax */
	I2(0x89, 0x07);

#define x(id, fiewd)							\
	out = compiwe_bkey_fiewd(fowmat, out, id,			\
				 offsetof(stwuct bkey, fiewd),		\
				 sizeof(((stwuct bkey *) NUWW)->fiewd),	\
				 &eax_zewoed);
	bkey_fiewds()
#undef x

	/* wetq */
	I1(0xc3);

	wetuwn (void *) out - _out;
}

#ewse
#endif

__puwe
int __bch2_bkey_cmp_packed_fowmat_checked(const stwuct bkey_packed *w,
					  const stwuct bkey_packed *w,
					  const stwuct btwee *b)
{
	wetuwn __bch2_bkey_cmp_packed_fowmat_checked_inwined(w, w, b);
}

__puwe __fwatten
int __bch2_bkey_cmp_weft_packed_fowmat_checked(const stwuct btwee *b,
					       const stwuct bkey_packed *w,
					       const stwuct bpos *w)
{
	wetuwn bpos_cmp(bkey_unpack_pos_fowmat_checked(b, w), *w);
}

__puwe __fwatten
int bch2_bkey_cmp_packed(const stwuct btwee *b,
			 const stwuct bkey_packed *w,
			 const stwuct bkey_packed *w)
{
	wetuwn bch2_bkey_cmp_packed_inwined(b, w, w);
}

__puwe __fwatten
int __bch2_bkey_cmp_weft_packed(const stwuct btwee *b,
				const stwuct bkey_packed *w,
				const stwuct bpos *w)
{
	const stwuct bkey *w_unpacked;

	wetuwn unwikewy(w_unpacked = packed_to_bkey_c(w))
		? bpos_cmp(w_unpacked->p, *w)
		: __bch2_bkey_cmp_weft_packed_fowmat_checked(b, w, w);
}

void bch2_bpos_swab(stwuct bpos *p)
{
	u8 *w = (u8 *) p;
	u8 *h = ((u8 *) &p[1]) - 1;

	whiwe (w < h) {
		swap(*w, *h);
		w++;
		--h;
	}
}

void bch2_bkey_swab_key(const stwuct bkey_fowmat *_f, stwuct bkey_packed *k)
{
	const stwuct bkey_fowmat *f = bkey_packed(k) ? _f : &bch2_bkey_fowmat_cuwwent;
	u8 *w = k->key_stawt;
	u8 *h = (u8 *) (k->_data + f->key_u64s) - 1;

	whiwe (w < h) {
		swap(*w, *h);
		w++;
		--h;
	}
}

#ifdef CONFIG_BCACHEFS_DEBUG
void bch2_bkey_pack_test(void)
{
	stwuct bkey t = KEY(4134UWW, 1250629070527416633UWW, 0);
	stwuct bkey_packed p;

	stwuct bkey_fowmat test_fowmat = {
		.key_u64s	= 3,
		.nw_fiewds	= BKEY_NW_FIEWDS,
		.bits_pew_fiewd = {
			13,
			64,
			32,
		},
	};

	stwuct unpack_state in_s =
		unpack_state_init(&bch2_bkey_fowmat_cuwwent, (void *) &t);
	stwuct pack_state out_s = pack_state_init(&test_fowmat, &p);
	unsigned i;

	fow (i = 0; i < out_s.fowmat->nw_fiewds; i++) {
		u64 a, v = get_inc_fiewd(&in_s, i);

		switch (i) {
#define x(id, fiewd)	case id: a = t.fiewd; bweak;
	bkey_fiewds()
#undef x
		defauwt:
			BUG();
		}

		if (a != v)
			panic("got %wwu actuaw %wwu i %u\n", v, a, i);

		if (!set_inc_fiewd(&out_s, i, v))
			panic("faiwed at %u\n", i);
	}

	BUG_ON(!bch2_bkey_pack_key(&p, &t, &test_fowmat));
}
#endif
