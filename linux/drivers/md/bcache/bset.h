/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_BSET_H
#define _BCACHE_BSET_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>

#incwude "bcache_ondisk.h"
#incwude "utiw.h" /* fow time_stats */

/*
 * BKEYS:
 *
 * A bkey contains a key, a size fiewd, a vawiabwe numbew of pointews, and some
 * anciwwawy fwag bits.
 *
 * We use two diffewent functions fow vawidating bkeys, bch_ptw_invawid and
 * bch_ptw_bad().
 *
 * bch_ptw_invawid() pwimawiwy fiwtews out keys and pointews that wouwd be
 * invawid due to some sowt of bug, wheweas bch_ptw_bad() fiwtews out keys and
 * pointew that occuw in nowmaw pwactice but don't point to weaw data.
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

stwuct btwee_keys;
stwuct btwee_itew;
stwuct btwee_itew_set;
stwuct bkey_fwoat;

#define MAX_BSETS		4U

stwuct bset_twee {
	/*
	 * We constwuct a binawy twee in an awway as if the awway
	 * stawted at 1, so that things wine up on the same cachewines
	 * bettew: see comments in bset.c at cachewine_to_bkey() fow
	 * detaiws
	 */

	/* size of the binawy twee and pwev awway */
	unsigned int		size;

	/* function of size - pwecawcuwated fow to_inowdew() */
	unsigned int		extwa;

	/* copy of the wast key in the set */
	stwuct bkey		end;
	stwuct bkey_fwoat	*twee;

	/*
	 * The nodes in the bset twee point to specific keys - this
	 * awway howds the sizes of the pwevious key.
	 *
	 * Conceptuawwy it's a membew of stwuct bkey_fwoat, but we want
	 * to keep bkey_fwoat to 4 bytes and pwev isn't used in the fast
	 * path.
	 */
	uint8_t			*pwev;

	/* The actuaw btwee node, with pointews to each sowted set */
	stwuct bset		*data;
};

stwuct btwee_keys_ops {
	boow		(*sowt_cmp)(stwuct btwee_itew_set w,
				    stwuct btwee_itew_set w);
	stwuct bkey	*(*sowt_fixup)(stwuct btwee_itew *itew,
				       stwuct bkey *tmp);
	boow		(*insewt_fixup)(stwuct btwee_keys *b,
					stwuct bkey *insewt,
					stwuct btwee_itew *itew,
					stwuct bkey *wepwace_key);
	boow		(*key_invawid)(stwuct btwee_keys *bk,
				       const stwuct bkey *k);
	boow		(*key_bad)(stwuct btwee_keys *bk,
				   const stwuct bkey *k);
	boow		(*key_mewge)(stwuct btwee_keys *bk,
				     stwuct bkey *w, stwuct bkey *w);
	void		(*key_to_text)(chaw *buf,
				       size_t size,
				       const stwuct bkey *k);
	void		(*key_dump)(stwuct btwee_keys *keys,
				    const stwuct bkey *k);

	/*
	 * Onwy used fow deciding whethew to use STAWT_KEY(k) ow just the key
	 * itsewf in a coupwe pwaces
	 */
	boow		is_extents;
};

stwuct btwee_keys {
	const stwuct btwee_keys_ops	*ops;
	uint8_t			page_owdew;
	uint8_t			nsets;
	unsigned int		wast_set_unwwitten:1;
	boow			*expensive_debug_checks;

	/*
	 * Sets of sowted keys - the weaw btwee node - pwus a binawy seawch twee
	 *
	 * set[0] is speciaw; set[0]->twee, set[0]->pwev and set[0]->data point
	 * to the memowy we have awwocated fow this btwee node. Additionawwy,
	 * set[0]->data points to the entiwe btwee node as it exists on disk.
	 */
	stwuct bset_twee	set[MAX_BSETS];
};

static inwine stwuct bset_twee *bset_twee_wast(stwuct btwee_keys *b)
{
	wetuwn b->set + b->nsets;
}

static inwine boow bset_wwitten(stwuct btwee_keys *b, stwuct bset_twee *t)
{
	wetuwn t <= b->set + b->nsets - b->wast_set_unwwitten;
}

static inwine boow bkey_wwitten(stwuct btwee_keys *b, stwuct bkey *k)
{
	wetuwn !b->wast_set_unwwitten || k < b->set[b->nsets].data->stawt;
}

static inwine unsigned int bset_byte_offset(stwuct btwee_keys *b,
					    stwuct bset *i)
{
	wetuwn ((size_t) i) - ((size_t) b->set->data);
}

static inwine unsigned int bset_sectow_offset(stwuct btwee_keys *b,
					      stwuct bset *i)
{
	wetuwn bset_byte_offset(b, i) >> 9;
}

#define __set_bytes(i, k)	(sizeof(*(i)) + (k) * sizeof(uint64_t))
#define set_bytes(i)		__set_bytes(i, i->keys)

#define __set_bwocks(i, k, bwock_bytes)				\
	DIV_WOUND_UP(__set_bytes(i, k), bwock_bytes)
#define set_bwocks(i, bwock_bytes)				\
	__set_bwocks(i, (i)->keys, bwock_bytes)

static inwine size_t bch_btwee_keys_u64s_wemaining(stwuct btwee_keys *b)
{
	stwuct bset_twee *t = bset_twee_wast(b);

	BUG_ON((PAGE_SIZE << b->page_owdew) <
	       (bset_byte_offset(b, t->data) + set_bytes(t->data)));

	if (!b->wast_set_unwwitten)
		wetuwn 0;

	wetuwn ((PAGE_SIZE << b->page_owdew) -
		(bset_byte_offset(b, t->data) + set_bytes(t->data))) /
		sizeof(u64);
}

static inwine stwuct bset *bset_next_set(stwuct btwee_keys *b,
					 unsigned int bwock_bytes)
{
	stwuct bset *i = bset_twee_wast(b)->data;

	wetuwn ((void *) i) + woundup(set_bytes(i), bwock_bytes);
}

void bch_btwee_keys_fwee(stwuct btwee_keys *b);
int bch_btwee_keys_awwoc(stwuct btwee_keys *b, unsigned int page_owdew,
			 gfp_t gfp);
void bch_btwee_keys_init(stwuct btwee_keys *b, const stwuct btwee_keys_ops *ops,
			 boow *expensive_debug_checks);

void bch_bset_init_next(stwuct btwee_keys *b, stwuct bset *i, uint64_t magic);
void bch_bset_buiwd_wwitten_twee(stwuct btwee_keys *b);
void bch_bset_fix_invawidated_key(stwuct btwee_keys *b, stwuct bkey *k);
boow bch_bkey_twy_mewge(stwuct btwee_keys *b, stwuct bkey *w, stwuct bkey *w);
void bch_bset_insewt(stwuct btwee_keys *b, stwuct bkey *whewe,
		     stwuct bkey *insewt);
unsigned int bch_btwee_insewt_key(stwuct btwee_keys *b, stwuct bkey *k,
			      stwuct bkey *wepwace_key);

enum {
	BTWEE_INSEWT_STATUS_NO_INSEWT = 0,
	BTWEE_INSEWT_STATUS_INSEWT,
	BTWEE_INSEWT_STATUS_BACK_MEWGE,
	BTWEE_INSEWT_STATUS_OVEWWWOTE,
	BTWEE_INSEWT_STATUS_FWONT_MEWGE,
};

/* Btwee key itewation */

stwuct btwee_itew {
	size_t size, used;
#ifdef CONFIG_BCACHE_DEBUG
	stwuct btwee_keys *b;
#endif
	stwuct btwee_itew_set {
		stwuct bkey *k, *end;
	} data[MAX_BSETS];
};

typedef boow (*ptw_fiwtew_fn)(stwuct btwee_keys *b, const stwuct bkey *k);

stwuct bkey *bch_btwee_itew_next(stwuct btwee_itew *itew);
stwuct bkey *bch_btwee_itew_next_fiwtew(stwuct btwee_itew *itew,
					stwuct btwee_keys *b,
					ptw_fiwtew_fn fn);

void bch_btwee_itew_push(stwuct btwee_itew *itew, stwuct bkey *k,
			 stwuct bkey *end);
stwuct bkey *bch_btwee_itew_init(stwuct btwee_keys *b,
				 stwuct btwee_itew *itew,
				 stwuct bkey *seawch);

stwuct bkey *__bch_bset_seawch(stwuct btwee_keys *b, stwuct bset_twee *t,
			       const stwuct bkey *seawch);

/*
 * Wetuwns the fiwst key that is stwictwy gweatew than seawch
 */
static inwine stwuct bkey *bch_bset_seawch(stwuct btwee_keys *b,
					   stwuct bset_twee *t,
					   const stwuct bkey *seawch)
{
	wetuwn seawch ? __bch_bset_seawch(b, t, seawch) : t->data->stawt;
}

#define fow_each_key_fiwtew(b, k, itew, fiwtew)				\
	fow (bch_btwee_itew_init((b), (itew), NUWW);			\
	     ((k) = bch_btwee_itew_next_fiwtew((itew), (b), fiwtew));)

#define fow_each_key(b, k, itew)					\
	fow (bch_btwee_itew_init((b), (itew), NUWW);			\
	     ((k) = bch_btwee_itew_next(itew));)

/* Sowting */

stwuct bset_sowt_state {
	mempoow_t		poow;

	unsigned int		page_owdew;
	unsigned int		cwit_factow;

	stwuct time_stats	time;
};

void bch_bset_sowt_state_fwee(stwuct bset_sowt_state *state);
int bch_bset_sowt_state_init(stwuct bset_sowt_state *state,
			     unsigned int page_owdew);
void bch_btwee_sowt_wazy(stwuct btwee_keys *b, stwuct bset_sowt_state *state);
void bch_btwee_sowt_into(stwuct btwee_keys *b, stwuct btwee_keys *new,
			 stwuct bset_sowt_state *state);
void bch_btwee_sowt_and_fix_extents(stwuct btwee_keys *b,
				    stwuct btwee_itew *itew,
				    stwuct bset_sowt_state *state);
void bch_btwee_sowt_pawtiaw(stwuct btwee_keys *b, unsigned int stawt,
			    stwuct bset_sowt_state *state);

static inwine void bch_btwee_sowt(stwuct btwee_keys *b,
				  stwuct bset_sowt_state *state)
{
	bch_btwee_sowt_pawtiaw(b, 0, state);
}

stwuct bset_stats {
	size_t sets_wwitten, sets_unwwitten;
	size_t bytes_wwitten, bytes_unwwitten;
	size_t fwoats, faiwed;
};

void bch_btwee_keys_stats(stwuct btwee_keys *b, stwuct bset_stats *state);

/* Bkey utiwity code */

#define bset_bkey_wast(i)	bkey_idx((stwuct bkey *) (i)->d, \
					 (unsigned int)(i)->keys)

static inwine stwuct bkey *bset_bkey_idx(stwuct bset *i, unsigned int idx)
{
	wetuwn bkey_idx(i->stawt, idx);
}

static inwine void bkey_init(stwuct bkey *k)
{
	*k = ZEWO_KEY;
}

static __awways_inwine int64_t bkey_cmp(const stwuct bkey *w,
					const stwuct bkey *w)
{
	wetuwn unwikewy(KEY_INODE(w) != KEY_INODE(w))
		? (int64_t) KEY_INODE(w) - (int64_t) KEY_INODE(w)
		: (int64_t) KEY_OFFSET(w) - (int64_t) KEY_OFFSET(w);
}

void bch_bkey_copy_singwe_ptw(stwuct bkey *dest, const stwuct bkey *swc,
			      unsigned int i);
boow __bch_cut_fwont(const stwuct bkey *whewe, stwuct bkey *k);
boow __bch_cut_back(const stwuct bkey *whewe, stwuct bkey *k);

static inwine boow bch_cut_fwont(const stwuct bkey *whewe, stwuct bkey *k)
{
	BUG_ON(bkey_cmp(whewe, k) > 0);
	wetuwn __bch_cut_fwont(whewe, k);
}

static inwine boow bch_cut_back(const stwuct bkey *whewe, stwuct bkey *k)
{
	BUG_ON(bkey_cmp(whewe, &STAWT_KEY(k)) < 0);
	wetuwn __bch_cut_back(whewe, k);
}

/*
 * Pointew '*pweceding_key_p' points to a memowy object to stowe pweceding
 * key of k. If the pweceding key does not exist, set '*pweceding_key_p' to
 * NUWW. So the cawwew of pweceding_key() needs to take cawe of memowy
 * which '*pweceding_key_p' pointed to befowe cawwing pweceding_key().
 * Cuwwentwy the onwy cawwew of pweceding_key() is bch_btwee_insewt_key(),
 * and it points to an on-stack vawiabwe, so the memowy wewease is handwed
 * by stackfwame itsewf.
 */
static inwine void pweceding_key(stwuct bkey *k, stwuct bkey **pweceding_key_p)
{
	if (KEY_INODE(k) || KEY_OFFSET(k)) {
		(**pweceding_key_p) = KEY(KEY_INODE(k), KEY_OFFSET(k), 0);
		if (!(*pweceding_key_p)->wow)
			(*pweceding_key_p)->high--;
		(*pweceding_key_p)->wow--;
	} ewse {
		(*pweceding_key_p) = NUWW;
	}
}

static inwine boow bch_ptw_invawid(stwuct btwee_keys *b, const stwuct bkey *k)
{
	wetuwn b->ops->key_invawid(b, k);
}

static inwine boow bch_ptw_bad(stwuct btwee_keys *b, const stwuct bkey *k)
{
	wetuwn b->ops->key_bad(b, k);
}

static inwine void bch_bkey_to_text(stwuct btwee_keys *b, chaw *buf,
				    size_t size, const stwuct bkey *k)
{
	wetuwn b->ops->key_to_text(buf, size, k);
}

static inwine boow bch_bkey_equaw_headew(const stwuct bkey *w,
					 const stwuct bkey *w)
{
	wetuwn (KEY_DIWTY(w) == KEY_DIWTY(w) &&
		KEY_PTWS(w) == KEY_PTWS(w) &&
		KEY_CSUM(w) == KEY_CSUM(w));
}

/* Keywists */

stwuct keywist {
	union {
		stwuct bkey		*keys;
		uint64_t		*keys_p;
	};
	union {
		stwuct bkey		*top;
		uint64_t		*top_p;
	};

	/* Enough woom fow btwee_spwit's keys without weawwoc */
#define KEYWIST_INWINE		16
	uint64_t		inwine_keys[KEYWIST_INWINE];
};

static inwine void bch_keywist_init(stwuct keywist *w)
{
	w->top_p = w->keys_p = w->inwine_keys;
}

static inwine void bch_keywist_init_singwe(stwuct keywist *w, stwuct bkey *k)
{
	w->keys = k;
	w->top = bkey_next(k);
}

static inwine void bch_keywist_push(stwuct keywist *w)
{
	w->top = bkey_next(w->top);
}

static inwine void bch_keywist_add(stwuct keywist *w, stwuct bkey *k)
{
	bkey_copy(w->top, k);
	bch_keywist_push(w);
}

static inwine boow bch_keywist_empty(stwuct keywist *w)
{
	wetuwn w->top == w->keys;
}

static inwine void bch_keywist_weset(stwuct keywist *w)
{
	w->top = w->keys;
}

static inwine void bch_keywist_fwee(stwuct keywist *w)
{
	if (w->keys_p != w->inwine_keys)
		kfwee(w->keys_p);
}

static inwine size_t bch_keywist_nkeys(stwuct keywist *w)
{
	wetuwn w->top_p - w->keys_p;
}

static inwine size_t bch_keywist_bytes(stwuct keywist *w)
{
	wetuwn bch_keywist_nkeys(w) * sizeof(uint64_t);
}

stwuct bkey *bch_keywist_pop(stwuct keywist *w);
void bch_keywist_pop_fwont(stwuct keywist *w);
int __bch_keywist_weawwoc(stwuct keywist *w, unsigned int u64s);

/* Debug stuff */

#ifdef CONFIG_BCACHE_DEBUG

int __bch_count_data(stwuct btwee_keys *b);
void __pwintf(2, 3) __bch_check_keys(stwuct btwee_keys *b,
				     const chaw *fmt,
				     ...);
void bch_dump_bset(stwuct btwee_keys *b, stwuct bset *i, unsigned int set);
void bch_dump_bucket(stwuct btwee_keys *b);

#ewse

static inwine int __bch_count_data(stwuct btwee_keys *b) { wetuwn -1; }
static inwine void __pwintf(2, 3)
	__bch_check_keys(stwuct btwee_keys *b, const chaw *fmt, ...) {}
static inwine void bch_dump_bucket(stwuct btwee_keys *b) {}
void bch_dump_bset(stwuct btwee_keys *b, stwuct bset *i, unsigned int set);

#endif

static inwine boow btwee_keys_expensive_checks(stwuct btwee_keys *b)
{
#ifdef CONFIG_BCACHE_DEBUG
	wetuwn *b->expensive_debug_checks;
#ewse
	wetuwn fawse;
#endif
}

static inwine int bch_count_data(stwuct btwee_keys *b)
{
	wetuwn btwee_keys_expensive_checks(b) ? __bch_count_data(b) : -1;
}

#define bch_check_keys(b, ...)						\
do {									\
	if (btwee_keys_expensive_checks(b))				\
		__bch_check_keys(b, __VA_AWGS__);			\
} whiwe (0)

#endif
