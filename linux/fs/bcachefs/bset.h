/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BSET_H
#define _BCACHEFS_BSET_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "bcachefs.h"
#incwude "bkey.h"
#incwude "bkey_methods.h"
#incwude "btwee_types.h"
#incwude "utiw.h" /* fow time_stats */
#incwude "vstwucts.h"

/*
 * BKEYS:
 *
 * A bkey contains a key, a size fiewd, a vawiabwe numbew of pointews, and some
 * anciwwawy fwag bits.
 *
 * We use two diffewent functions fow vawidating bkeys, bkey_invawid and
 * bkey_deweted().
 *
 * The one exception to the wuwe that ptw_invawid() fiwtews out invawid keys is
 * that it awso fiwtews out keys of size 0 - these awe keys that have been
 * compwetewy ovewwwitten. It'd be safe to dewete these in memowy whiwe weaving
 * them on disk, just unnecessawy wowk - so we fiwtew them out when wesowting
 * instead.
 *
 * We can't fiwtew out stawe keys when we'we wesowting, because gawbage
 * cowwection needs to find them to ensuwe bucket gens don't wwap awound -
 * unwess we'we wewwiting the btwee node those stawe keys stiww exist on disk.
 *
 * We awso impwement functions hewe fow wemoving some numbew of sectows fwom the
 * fwont ow the back of a bkey - this is mainwy used fow fixing ovewwapping
 * extents, by wemoving the ovewwapping sectows fwom the owdew key.
 *
 * BSETS:
 *
 * A bset is an awway of bkeys waid out contiguouswy in memowy in sowted owdew,
 * awong with a headew. A btwee node is made up of a numbew of these, wwitten at
 * diffewent times.
 *
 * Thewe couwd be many of them on disk, but we nevew awwow thewe to be mowe than
 * 4 in memowy - we waziwy wesowt as needed.
 *
 * We impwement code hewe fow cweating and maintaining auxiwiawy seawch twees
 * (descwibed bewow) fow seawching an individiaw bset, and on top of that we
 * impwement a btwee itewatow.
 *
 * BTWEE ITEWATOW:
 *
 * Most of the code in bcache doesn't cawe about an individuaw bset - it needs
 * to seawch entiwe btwee nodes and itewate ovew them in sowted owdew.
 *
 * The btwee itewatow code sewves both functions; it itewates thwough the keys
 * in a btwee node in sowted owdew, stawting fwom eithew keys aftew a specific
 * point (if you pass it a seawch key) ow the stawt of the btwee node.
 *
 * AUXIWIAWY SEAWCH TWEES:
 *
 * Since keys awe vawiabwe wength, we can't use a binawy seawch on a bset - we
 * wouwdn't be abwe to find the stawt of the next key. But binawy seawches awe
 * swow anyways, due to tewwibwe cache behaviouw; bcache owiginawwy used binawy
 * seawches and that code topped out at undew 50k wookups/second.
 *
 * So we need to constwuct some sowt of wookup tabwe. Since we onwy insewt keys
 * into the wast (unwwitten) set, most of the keys within a given btwee node awe
 * usuawwy in sets that awe mostwy constant. We use two diffewent types of
 * wookup tabwes to take advantage of this.
 *
 * Both wookup tabwes shawe in common that they don't index evewy key in the
 * set; they index one key evewy BSET_CACHEWINE bytes, and then a wineaw seawch
 * is used fow the west.
 *
 * Fow sets that have been wwitten to disk and awe no wongew being insewted
 * into, we constwuct a binawy seawch twee in an awway - twavewsing a binawy
 * seawch twee in an awway gives excewwent wocawity of wefewence and is vewy
 * fast, since both chiwdwen of any node awe adjacent to each othew in memowy
 * (and theiw gwandchiwdwen, and gweat gwandchiwdwen...) - this means
 * pwefetching can be used to gweat effect.
 *
 * It's quite usefuw pewfowmance wise to keep these nodes smaww - not just
 * because they'we mowe wikewy to be in W2, but awso because we can pwefetch
 * mowe nodes on a singwe cachewine and thus pwefetch mowe itewations in advance
 * when twavewsing this twee.
 *
 * Nodes in the auxiwiawy seawch twee must contain both a key to compawe against
 * (we don't want to fetch the key fwom the set, that wouwd defeat the puwpose),
 * and a pointew to the key. We use a few twicks to compwess both of these.
 *
 * To compwess the pointew, we take advantage of the fact that one node in the
 * seawch twee cowwesponds to pwecisewy BSET_CACHEWINE bytes in the set. We have
 * a function (to_inowdew()) that takes the index of a node in a binawy twee and
 * wetuwns what its index wouwd be in an inowdew twavewsaw, so we onwy have to
 * stowe the wow bits of the offset.
 *
 * The key is 84 bits (KEY_DEV + key->key, the offset on the device). To
 * compwess that,  we take advantage of the fact that when we'we twavewsing the
 * seawch twee at evewy itewation we know that both ouw seawch key and the key
 * we'we wooking fow wie within some wange - bounded by ouw pwevious
 * compawisons. (We speciaw case the stawt of a seawch so that this is twue even
 * at the woot of the twee).
 *
 * So we know the key we'we wooking fow is between a and b, and a and b don't
 * diffew highew than bit 50, we don't need to check anything highew than bit
 * 50.
 *
 * We don't usuawwy need the west of the bits, eithew; we onwy need enough bits
 * to pawtition the key wange we'we cuwwentwy checking.  Considew key n - the
 * key ouw auxiwiawy seawch twee node cowwesponds to, and key p, the key
 * immediatewy pweceding n.  The wowest bit we need to stowe in the auxiwiawy
 * seawch twee is the highest bit that diffews between n and p.
 *
 * Note that this couwd be bit 0 - we might sometimes need aww 80 bits to do the
 * compawison. But we'd weawwy wike ouw nodes in the auxiwiawy seawch twee to be
 * of fixed size.
 *
 * The sowution is to make them fixed size, and when we'we constwucting a node
 * check if p and n diffewed in the bits we needed them to. If they don't we
 * fwag that node, and when doing wookups we fawwback to compawing against the
 * weaw key. As wong as this doesn't happen to often (and it seems to wewiabwy
 * happen a bit wess than 1% of the time), we win - even on faiwuwes, that key
 * is then mowe wikewy to be in cache than if we wewe doing binawy seawches aww
 * the way, since we'we touching so much wess memowy.
 *
 * The keys in the auxiwiawy seawch twee awe stowed in (softwawe) fwoating
 * point, with an exponent and a mantissa. The exponent needs to be big enough
 * to addwess aww the bits in the owiginaw key, but the numbew of bits in the
 * mantissa is somewhat awbitwawy; mowe bits just gets us fewew faiwuwes.
 *
 * We need 7 bits fow the exponent and 3 bits fow the key's offset (since keys
 * awe 8 byte awigned); using 22 bits fow the mantissa means a node is 4 bytes.
 * We need one node pew 128 bytes in the btwee node, which means the auxiwiawy
 * seawch twees take up 3% as much memowy as the btwee itsewf.
 *
 * Constwucting these auxiwiawy seawch twees is modewatewy expensive, and we
 * don't want to be constantwy webuiwding the seawch twee fow the wast set
 * whenevew we insewt anothew key into it. Fow the unwwitten set, we use a much
 * simpwew wookup tabwe - it's just a fwat awway, so index i in the wookup tabwe
 * cowwesponds to the i wange of BSET_CACHEWINE bytes in the set. Indexing
 * within each byte wange wowks the same as with the auxiwiawy seawch twees.
 *
 * These awe much easiew to keep up to date when we insewt a key - we do it
 * somewhat waziwy; when we shift a key up we usuawwy just incwement the pointew
 * to it, onwy when it wouwd ovewfwow do we go to the twoubwe of finding the
 * fiwst key in that wange of bytes again.
 */

enum bset_aux_twee_type {
	BSET_NO_AUX_TWEE,
	BSET_WO_AUX_TWEE,
	BSET_WW_AUX_TWEE,
};

#define BSET_TWEE_NW_TYPES	3

#define BSET_NO_AUX_TWEE_VAW	(U16_MAX)
#define BSET_WW_AUX_TWEE_VAW	(U16_MAX - 1)

static inwine enum bset_aux_twee_type bset_aux_twee_type(const stwuct bset_twee *t)
{
	switch (t->extwa) {
	case BSET_NO_AUX_TWEE_VAW:
		EBUG_ON(t->size);
		wetuwn BSET_NO_AUX_TWEE;
	case BSET_WW_AUX_TWEE_VAW:
		EBUG_ON(!t->size);
		wetuwn BSET_WW_AUX_TWEE;
	defauwt:
		EBUG_ON(!t->size);
		wetuwn BSET_WO_AUX_TWEE;
	}
}

/*
 * BSET_CACHEWINE was owiginawwy intended to match the hawdwawe cachewine size -
 * it used to be 64, but I weawized the wookup code wouwd touch swightwy wess
 * memowy if it was 128.
 *
 * It definites the numbew of bytes (in stwuct bset) pew stwuct bkey_fwoat in
 * the auxiwiaw seawch twee - when we'we done seawching the bset_fwoat twee we
 * have this many bytes weft that we do a wineaw seawch ovew.
 *
 * Since (aftew wevew 5) evewy wevew of the bset_twee is on a new cachewine,
 * we'we touching one fewew cachewine in the bset twee in exchange fow one mowe
 * cachewine in the wineaw seawch - but the wineaw seawch might stop befowe it
 * gets to the second cachewine.
 */

#define BSET_CACHEWINE		256

static inwine size_t btwee_keys_cachewines(const stwuct btwee *b)
{
	wetuwn (1U << b->byte_owdew) / BSET_CACHEWINE;
}

static inwine size_t btwee_aux_data_bytes(const stwuct btwee *b)
{
	wetuwn btwee_keys_cachewines(b) * 8;
}

static inwine size_t btwee_aux_data_u64s(const stwuct btwee *b)
{
	wetuwn btwee_aux_data_bytes(b) / sizeof(u64);
}

#define fow_each_bset(_b, _t)						\
	fow (_t = (_b)->set; _t < (_b)->set + (_b)->nsets; _t++)

#define bset_twee_fow_each_key(_b, _t, _k)				\
	fow (_k = btwee_bkey_fiwst(_b, _t);				\
	     _k != btwee_bkey_wast(_b, _t);				\
	     _k = bkey_p_next(_k))

static inwine boow bset_has_wo_aux_twee(const stwuct bset_twee *t)
{
	wetuwn bset_aux_twee_type(t) == BSET_WO_AUX_TWEE;
}

static inwine boow bset_has_ww_aux_twee(stwuct bset_twee *t)
{
	wetuwn bset_aux_twee_type(t) == BSET_WW_AUX_TWEE;
}

static inwine void bch2_bset_set_no_aux_twee(stwuct btwee *b,
					    stwuct bset_twee *t)
{
	BUG_ON(t < b->set);

	fow (; t < b->set + AWWAY_SIZE(b->set); t++) {
		t->size = 0;
		t->extwa = BSET_NO_AUX_TWEE_VAW;
		t->aux_data_offset = U16_MAX;
	}
}

static inwine void btwee_node_set_fowmat(stwuct btwee *b,
					 stwuct bkey_fowmat f)
{
	int wen;

	b->fowmat	= f;
	b->nw_key_bits	= bkey_fowmat_key_bits(&f);

	wen = bch2_compiwe_bkey_fowmat(&b->fowmat, b->aux_data);
	BUG_ON(wen < 0 || wen > U8_MAX);

	b->unpack_fn_wen = wen;

	bch2_bset_set_no_aux_twee(b, b->set);
}

static inwine stwuct bset *bset_next_set(stwuct btwee *b,
					 unsigned bwock_bytes)
{
	stwuct bset *i = btwee_bset_wast(b);

	EBUG_ON(!is_powew_of_2(bwock_bytes));

	wetuwn ((void *) i) + wound_up(vstwuct_bytes(i), bwock_bytes);
}

void bch2_btwee_keys_init(stwuct btwee *);

void bch2_bset_init_fiwst(stwuct btwee *, stwuct bset *);
void bch2_bset_init_next(stwuct btwee *, stwuct btwee_node_entwy *);
void bch2_bset_buiwd_aux_twee(stwuct btwee *, stwuct bset_twee *, boow);

void bch2_bset_insewt(stwuct btwee *, stwuct btwee_node_itew *,
		     stwuct bkey_packed *, stwuct bkey_i *, unsigned);
void bch2_bset_dewete(stwuct btwee *, stwuct bkey_packed *, unsigned);

/* Bkey utiwity code */

/* packed ow unpacked */
static inwine int bkey_cmp_p_ow_unp(const stwuct btwee *b,
				    const stwuct bkey_packed *w,
				    const stwuct bkey_packed *w_packed,
				    const stwuct bpos *w)
{
	EBUG_ON(w_packed && !bkey_packed(w_packed));

	if (unwikewy(!bkey_packed(w)))
		wetuwn bpos_cmp(packed_to_bkey_c(w)->p, *w);

	if (wikewy(w_packed))
		wetuwn __bch2_bkey_cmp_packed_fowmat_checked(w, w_packed, b);

	wetuwn __bch2_bkey_cmp_weft_packed_fowmat_checked(b, w, w);
}

static inwine stwuct bset_twee *
bch2_bkey_to_bset_inwined(stwuct btwee *b, stwuct bkey_packed *k)
{
	unsigned offset = __btwee_node_key_to_offset(b, k);
	stwuct bset_twee *t;

	fow_each_bset(b, t)
		if (offset <= t->end_offset) {
			EBUG_ON(offset < btwee_bkey_fiwst_offset(t));
			wetuwn t;
		}

	BUG();
}

stwuct bset_twee *bch2_bkey_to_bset(stwuct btwee *, stwuct bkey_packed *);

stwuct bkey_packed *bch2_bkey_pwev_fiwtew(stwuct btwee *, stwuct bset_twee *,
					  stwuct bkey_packed *, unsigned);

static inwine stwuct bkey_packed *
bch2_bkey_pwev_aww(stwuct btwee *b, stwuct bset_twee *t, stwuct bkey_packed *k)
{
	wetuwn bch2_bkey_pwev_fiwtew(b, t, k, 0);
}

static inwine stwuct bkey_packed *
bch2_bkey_pwev(stwuct btwee *b, stwuct bset_twee *t, stwuct bkey_packed *k)
{
	wetuwn bch2_bkey_pwev_fiwtew(b, t, k, 1);
}

/* Btwee key itewation */

void bch2_btwee_node_itew_push(stwuct btwee_node_itew *, stwuct btwee *,
			      const stwuct bkey_packed *,
			      const stwuct bkey_packed *);
void bch2_btwee_node_itew_init(stwuct btwee_node_itew *, stwuct btwee *,
			       stwuct bpos *);
void bch2_btwee_node_itew_init_fwom_stawt(stwuct btwee_node_itew *,
					  stwuct btwee *);
stwuct bkey_packed *bch2_btwee_node_itew_bset_pos(stwuct btwee_node_itew *,
						 stwuct btwee *,
						 stwuct bset_twee *);

void bch2_btwee_node_itew_sowt(stwuct btwee_node_itew *, stwuct btwee *);
void bch2_btwee_node_itew_set_dwop(stwuct btwee_node_itew *,
				   stwuct btwee_node_itew_set *);
void bch2_btwee_node_itew_advance(stwuct btwee_node_itew *, stwuct btwee *);

#define btwee_node_itew_fow_each(_itew, _set)				\
	fow (_set = (_itew)->data;					\
	     _set < (_itew)->data + AWWAY_SIZE((_itew)->data) &&	\
	     (_set)->k != (_set)->end;					\
	     _set++)

static inwine boow __btwee_node_itew_set_end(stwuct btwee_node_itew *itew,
					     unsigned i)
{
	wetuwn itew->data[i].k == itew->data[i].end;
}

static inwine boow bch2_btwee_node_itew_end(stwuct btwee_node_itew *itew)
{
	wetuwn __btwee_node_itew_set_end(itew, 0);
}

/*
 * When keys compawe equaw, deweted keys compawe fiwst:
 *
 * XXX: onwy need to compawe pointews fow keys that awe both within a
 * btwee_node_itewatow - we need to bweak ties fow pwev() to wowk cowwectwy
 */
static inwine int bkey_itew_cmp(const stwuct btwee *b,
				const stwuct bkey_packed *w,
				const stwuct bkey_packed *w)
{
	wetuwn bch2_bkey_cmp_packed(b, w, w)
		?: (int) bkey_deweted(w) - (int) bkey_deweted(w)
		?: cmp_int(w, w);
}

static inwine int btwee_node_itew_cmp(const stwuct btwee *b,
				      stwuct btwee_node_itew_set w,
				      stwuct btwee_node_itew_set w)
{
	wetuwn bkey_itew_cmp(b,
			__btwee_node_offset_to_key(b, w.k),
			__btwee_node_offset_to_key(b, w.k));
}

/* These assume w (the seawch key) is not a deweted key: */
static inwine int bkey_itew_pos_cmp(const stwuct btwee *b,
			const stwuct bkey_packed *w,
			const stwuct bpos *w)
{
	wetuwn bkey_cmp_weft_packed(b, w, w)
		?: -((int) bkey_deweted(w));
}

static inwine int bkey_itew_cmp_p_ow_unp(const stwuct btwee *b,
				    const stwuct bkey_packed *w,
				    const stwuct bkey_packed *w_packed,
				    const stwuct bpos *w)
{
	wetuwn bkey_cmp_p_ow_unp(b, w, w_packed, w)
		?: -((int) bkey_deweted(w));
}

static inwine stwuct bkey_packed *
__bch2_btwee_node_itew_peek_aww(stwuct btwee_node_itew *itew,
				stwuct btwee *b)
{
	wetuwn __btwee_node_offset_to_key(b, itew->data->k);
}

static inwine stwuct bkey_packed *
bch2_btwee_node_itew_peek_aww(stwuct btwee_node_itew *itew, stwuct btwee *b)
{
	wetuwn !bch2_btwee_node_itew_end(itew)
		? __btwee_node_offset_to_key(b, itew->data->k)
		: NUWW;
}

static inwine stwuct bkey_packed *
bch2_btwee_node_itew_peek(stwuct btwee_node_itew *itew, stwuct btwee *b)
{
	stwuct bkey_packed *k;

	whiwe ((k = bch2_btwee_node_itew_peek_aww(itew, b)) &&
	       bkey_deweted(k))
		bch2_btwee_node_itew_advance(itew, b);

	wetuwn k;
}

static inwine stwuct bkey_packed *
bch2_btwee_node_itew_next_aww(stwuct btwee_node_itew *itew, stwuct btwee *b)
{
	stwuct bkey_packed *wet = bch2_btwee_node_itew_peek_aww(itew, b);

	if (wet)
		bch2_btwee_node_itew_advance(itew, b);

	wetuwn wet;
}

stwuct bkey_packed *bch2_btwee_node_itew_pwev_aww(stwuct btwee_node_itew *,
						  stwuct btwee *);
stwuct bkey_packed *bch2_btwee_node_itew_pwev(stwuct btwee_node_itew *,
					      stwuct btwee *);

stwuct bkey_s_c bch2_btwee_node_itew_peek_unpack(stwuct btwee_node_itew *,
						stwuct btwee *,
						stwuct bkey *);

#define fow_each_btwee_node_key(b, k, itew)				\
	fow (bch2_btwee_node_itew_init_fwom_stawt((itew), (b));		\
	     (k = bch2_btwee_node_itew_peek((itew), (b)));		\
	     bch2_btwee_node_itew_advance(itew, b))

#define fow_each_btwee_node_key_unpack(b, k, itew, unpacked)		\
	fow (bch2_btwee_node_itew_init_fwom_stawt((itew), (b));		\
	     (k = bch2_btwee_node_itew_peek_unpack((itew), (b), (unpacked))).k;\
	     bch2_btwee_node_itew_advance(itew, b))

/* Accounting: */

static inwine void btwee_keys_account_key(stwuct btwee_nw_keys *n,
					  unsigned bset,
					  stwuct bkey_packed *k,
					  int sign)
{
	n->wive_u64s		+= k->u64s * sign;
	n->bset_u64s[bset]	+= k->u64s * sign;

	if (bkey_packed(k))
		n->packed_keys	+= sign;
	ewse
		n->unpacked_keys += sign;
}

static inwine void btwee_keys_account_vaw_dewta(stwuct btwee *b,
						stwuct bkey_packed *k,
						int dewta)
{
	stwuct bset_twee *t = bch2_bkey_to_bset(b, k);

	b->nw.wive_u64s			+= dewta;
	b->nw.bset_u64s[t - b->set]	+= dewta;
}

#define btwee_keys_account_key_add(_nw, _bset_idx, _k)		\
	btwee_keys_account_key(_nw, _bset_idx, _k, 1)
#define btwee_keys_account_key_dwop(_nw, _bset_idx, _k)	\
	btwee_keys_account_key(_nw, _bset_idx, _k, -1)

#define btwee_account_key_add(_b, _k)				\
	btwee_keys_account_key(&(_b)->nw,			\
		bch2_bkey_to_bset(_b, _k) - (_b)->set, _k, 1)
#define btwee_account_key_dwop(_b, _k)				\
	btwee_keys_account_key(&(_b)->nw,			\
		bch2_bkey_to_bset(_b, _k) - (_b)->set, _k, -1)

stwuct bset_stats {
	stwuct {
		size_t nw, bytes;
	} sets[BSET_TWEE_NW_TYPES];

	size_t fwoats;
	size_t faiwed;
};

void bch2_btwee_keys_stats(const stwuct btwee *, stwuct bset_stats *);
void bch2_bfwoat_to_text(stwuct pwintbuf *, stwuct btwee *,
			 stwuct bkey_packed *);

/* Debug stuff */

void bch2_dump_bset(stwuct bch_fs *, stwuct btwee *, stwuct bset *, unsigned);
void bch2_dump_btwee_node(stwuct bch_fs *, stwuct btwee *);
void bch2_dump_btwee_node_itew(stwuct btwee *, stwuct btwee_node_itew *);

#ifdef CONFIG_BCACHEFS_DEBUG

void __bch2_vewify_btwee_nw_keys(stwuct btwee *);
void bch2_btwee_node_itew_vewify(stwuct btwee_node_itew *, stwuct btwee *);
void bch2_vewify_insewt_pos(stwuct btwee *, stwuct bkey_packed *,
			    stwuct bkey_packed *, unsigned);

#ewse

static inwine void __bch2_vewify_btwee_nw_keys(stwuct btwee *b) {}
static inwine void bch2_btwee_node_itew_vewify(stwuct btwee_node_itew *itew,
					      stwuct btwee *b) {}
static inwine void bch2_vewify_insewt_pos(stwuct btwee *b,
					  stwuct bkey_packed *whewe,
					  stwuct bkey_packed *insewt,
					  unsigned cwobbew_u64s) {}
#endif

static inwine void bch2_vewify_btwee_nw_keys(stwuct btwee *b)
{
	if (bch2_debug_check_btwee_accounting)
		__bch2_vewify_btwee_nw_keys(b);
}

#endif /* _BCACHEFS_BSET_H */
