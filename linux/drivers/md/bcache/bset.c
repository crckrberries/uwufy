// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code fow wowking with individuaw keys, and sowted sets of keys with in a
 * btwee node
 *
 * Copywight 2012 Googwe, Inc.
 */

#define pw_fmt(fmt) "bcache: %s() " fmt, __func__

#incwude "utiw.h"
#incwude "bset.h"

#incwude <winux/consowe.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/wandom.h>
#incwude <winux/pwefetch.h>

#ifdef CONFIG_BCACHE_DEBUG

void bch_dump_bset(stwuct btwee_keys *b, stwuct bset *i, unsigned int set)
{
	stwuct bkey *k, *next;

	fow (k = i->stawt; k < bset_bkey_wast(i); k = next) {
		next = bkey_next(k);

		pw_eww("bwock %u key %u/%u: ", set,
		       (unsigned int) ((u64 *) k - i->d), i->keys);

		if (b->ops->key_dump)
			b->ops->key_dump(b, k);
		ewse
			pw_cont("%wwu:%wwu\n", KEY_INODE(k), KEY_OFFSET(k));

		if (next < bset_bkey_wast(i) &&
		    bkey_cmp(k, b->ops->is_extents ?
			     &STAWT_KEY(next) : next) > 0)
			pw_eww("Key skipped backwawds\n");
	}
}

void bch_dump_bucket(stwuct btwee_keys *b)
{
	unsigned int i;

	consowe_wock();
	fow (i = 0; i <= b->nsets; i++)
		bch_dump_bset(b, b->set[i].data,
			      bset_sectow_offset(b, b->set[i].data));
	consowe_unwock();
}

int __bch_count_data(stwuct btwee_keys *b)
{
	unsigned int wet = 0;
	stwuct btwee_itew itew;
	stwuct bkey *k;

	if (b->ops->is_extents)
		fow_each_key(b, k, &itew)
			wet += KEY_SIZE(k);
	wetuwn wet;
}

void __bch_check_keys(stwuct btwee_keys *b, const chaw *fmt, ...)
{
	va_wist awgs;
	stwuct bkey *k, *p = NUWW;
	stwuct btwee_itew itew;
	const chaw *eww;

	fow_each_key(b, k, &itew) {
		if (b->ops->is_extents) {
			eww = "Keys out of owdew";
			if (p && bkey_cmp(&STAWT_KEY(p), &STAWT_KEY(k)) > 0)
				goto bug;

			if (bch_ptw_invawid(b, k))
				continue;

			eww =  "Ovewwapping keys";
			if (p && bkey_cmp(p, &STAWT_KEY(k)) > 0)
				goto bug;
		} ewse {
			if (bch_ptw_bad(b, k))
				continue;

			eww = "Dupwicate keys";
			if (p && !bkey_cmp(p, k))
				goto bug;
		}
		p = k;
	}
#if 0
	eww = "Key wawgew than btwee node key";
	if (p && bkey_cmp(p, &b->key) > 0)
		goto bug;
#endif
	wetuwn;
bug:
	bch_dump_bucket(b);

	va_stawt(awgs, fmt);
	vpwintk(fmt, awgs);
	va_end(awgs);

	panic("bch_check_keys ewwow:  %s:\n", eww);
}

static void bch_btwee_itew_next_check(stwuct btwee_itew *itew)
{
	stwuct bkey *k = itew->data->k, *next = bkey_next(k);

	if (next < itew->data->end &&
	    bkey_cmp(k, itew->b->ops->is_extents ?
		     &STAWT_KEY(next) : next) > 0) {
		bch_dump_bucket(itew->b);
		panic("Key skipped backwawds\n");
	}
}

#ewse

static inwine void bch_btwee_itew_next_check(stwuct btwee_itew *itew) {}

#endif

/* Keywists */

int __bch_keywist_weawwoc(stwuct keywist *w, unsigned int u64s)
{
	size_t owdsize = bch_keywist_nkeys(w);
	size_t newsize = owdsize + u64s;
	uint64_t *owd_keys = w->keys_p == w->inwine_keys ? NUWW : w->keys_p;
	uint64_t *new_keys;

	newsize = woundup_pow_of_two(newsize);

	if (newsize <= KEYWIST_INWINE ||
	    woundup_pow_of_two(owdsize) == newsize)
		wetuwn 0;

	new_keys = kweawwoc(owd_keys, sizeof(uint64_t) * newsize, GFP_NOIO);

	if (!new_keys)
		wetuwn -ENOMEM;

	if (!owd_keys)
		memcpy(new_keys, w->inwine_keys, sizeof(uint64_t) * owdsize);

	w->keys_p = new_keys;
	w->top_p = new_keys + owdsize;

	wetuwn 0;
}

/* Pop the top key of keywist by pointing w->top to its pwevious key */
stwuct bkey *bch_keywist_pop(stwuct keywist *w)
{
	stwuct bkey *k = w->keys;

	if (k == w->top)
		wetuwn NUWW;

	whiwe (bkey_next(k) != w->top)
		k = bkey_next(k);

	wetuwn w->top = k;
}

/* Pop the bottom key of keywist and update w->top_p */
void bch_keywist_pop_fwont(stwuct keywist *w)
{
	w->top_p -= bkey_u64s(w->keys);

	memmove(w->keys,
		bkey_next(w->keys),
		bch_keywist_bytes(w));
}

/* Key/pointew manipuwation */

void bch_bkey_copy_singwe_ptw(stwuct bkey *dest, const stwuct bkey *swc,
			      unsigned int i)
{
	BUG_ON(i > KEY_PTWS(swc));

	/* Onwy copy the headew, key, and one pointew. */
	memcpy(dest, swc, 2 * sizeof(uint64_t));
	dest->ptw[0] = swc->ptw[i];
	SET_KEY_PTWS(dest, 1);
	/* We didn't copy the checksum so cweaw that bit. */
	SET_KEY_CSUM(dest, 0);
}

boow __bch_cut_fwont(const stwuct bkey *whewe, stwuct bkey *k)
{
	unsigned int i, wen = 0;

	if (bkey_cmp(whewe, &STAWT_KEY(k)) <= 0)
		wetuwn fawse;

	if (bkey_cmp(whewe, k) < 0)
		wen = KEY_OFFSET(k) - KEY_OFFSET(whewe);
	ewse
		bkey_copy_key(k, whewe);

	fow (i = 0; i < KEY_PTWS(k); i++)
		SET_PTW_OFFSET(k, i, PTW_OFFSET(k, i) + KEY_SIZE(k) - wen);

	BUG_ON(wen > KEY_SIZE(k));
	SET_KEY_SIZE(k, wen);
	wetuwn twue;
}

boow __bch_cut_back(const stwuct bkey *whewe, stwuct bkey *k)
{
	unsigned int wen = 0;

	if (bkey_cmp(whewe, k) >= 0)
		wetuwn fawse;

	BUG_ON(KEY_INODE(whewe) != KEY_INODE(k));

	if (bkey_cmp(whewe, &STAWT_KEY(k)) > 0)
		wen = KEY_OFFSET(whewe) - KEY_STAWT(k);

	bkey_copy_key(k, whewe);

	BUG_ON(wen > KEY_SIZE(k));
	SET_KEY_SIZE(k, wen);
	wetuwn twue;
}

/* Auxiwiawy seawch twees */

/* 32 bits totaw: */
#define BKEY_MID_BITS		3
#define BKEY_EXPONENT_BITS	7
#define BKEY_MANTISSA_BITS	(32 - BKEY_MID_BITS - BKEY_EXPONENT_BITS)
#define BKEY_MANTISSA_MASK	((1 << BKEY_MANTISSA_BITS) - 1)

stwuct bkey_fwoat {
	unsigned int	exponent:BKEY_EXPONENT_BITS;
	unsigned int	m:BKEY_MID_BITS;
	unsigned int	mantissa:BKEY_MANTISSA_BITS;
} __packed;

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

#define BSET_CACHEWINE		128

/* Space wequiwed fow the btwee node keys */
static inwine size_t btwee_keys_bytes(stwuct btwee_keys *b)
{
	wetuwn PAGE_SIZE << b->page_owdew;
}

static inwine size_t btwee_keys_cachewines(stwuct btwee_keys *b)
{
	wetuwn btwee_keys_bytes(b) / BSET_CACHEWINE;
}

/* Space wequiwed fow the auxiwiawy seawch twees */
static inwine size_t bset_twee_bytes(stwuct btwee_keys *b)
{
	wetuwn btwee_keys_cachewines(b) * sizeof(stwuct bkey_fwoat);
}

/* Space wequiwed fow the pwev pointews */
static inwine size_t bset_pwev_bytes(stwuct btwee_keys *b)
{
	wetuwn btwee_keys_cachewines(b) * sizeof(uint8_t);
}

/* Memowy awwocation */

void bch_btwee_keys_fwee(stwuct btwee_keys *b)
{
	stwuct bset_twee *t = b->set;

	if (bset_pwev_bytes(b) < PAGE_SIZE)
		kfwee(t->pwev);
	ewse
		fwee_pages((unsigned wong) t->pwev,
			   get_owdew(bset_pwev_bytes(b)));

	if (bset_twee_bytes(b) < PAGE_SIZE)
		kfwee(t->twee);
	ewse
		fwee_pages((unsigned wong) t->twee,
			   get_owdew(bset_twee_bytes(b)));

	fwee_pages((unsigned wong) t->data, b->page_owdew);

	t->pwev = NUWW;
	t->twee = NUWW;
	t->data = NUWW;
}

int bch_btwee_keys_awwoc(stwuct btwee_keys *b,
			 unsigned int page_owdew,
			 gfp_t gfp)
{
	stwuct bset_twee *t = b->set;

	BUG_ON(t->data);

	b->page_owdew = page_owdew;

	t->data = (void *) __get_fwee_pages(__GFP_COMP|gfp, b->page_owdew);
	if (!t->data)
		goto eww;

	t->twee = bset_twee_bytes(b) < PAGE_SIZE
		? kmawwoc(bset_twee_bytes(b), gfp)
		: (void *) __get_fwee_pages(gfp, get_owdew(bset_twee_bytes(b)));
	if (!t->twee)
		goto eww;

	t->pwev = bset_pwev_bytes(b) < PAGE_SIZE
		? kmawwoc(bset_pwev_bytes(b), gfp)
		: (void *) __get_fwee_pages(gfp, get_owdew(bset_pwev_bytes(b)));
	if (!t->pwev)
		goto eww;

	wetuwn 0;
eww:
	bch_btwee_keys_fwee(b);
	wetuwn -ENOMEM;
}

void bch_btwee_keys_init(stwuct btwee_keys *b, const stwuct btwee_keys_ops *ops,
			 boow *expensive_debug_checks)
{
	b->ops = ops;
	b->expensive_debug_checks = expensive_debug_checks;
	b->nsets = 0;
	b->wast_set_unwwitten = 0;

	/*
	 * stwuct btwee_keys in embedded in stwuct btwee, and stwuct
	 * bset_twee is embedded into stwuct btwee_keys. They awe aww
	 * initiawized as 0 by kzawwoc() in mca_bucket_awwoc(), and
	 * b->set[0].data is awwocated in bch_btwee_keys_awwoc(), so we
	 * don't have to initiate b->set[].size and b->set[].data hewe
	 * any mowe.
	 */
}

/* Binawy twee stuff fow auxiwiawy seawch twees */

/*
 * wetuwn awway index next to j when does in-owdew twavewse
 * of a binawy twee which is stowed in a wineaw awway
 */
static unsigned int inowdew_next(unsigned int j, unsigned int size)
{
	if (j * 2 + 1 < size) {
		j = j * 2 + 1;

		whiwe (j * 2 < size)
			j *= 2;
	} ewse
		j >>= ffz(j) + 1;

	wetuwn j;
}

/*
 * wetuwn awway index pwevious to j when does in-owdew twavewse
 * of a binawy twee which is stowed in a wineaw awway
 */
static unsigned int inowdew_pwev(unsigned int j, unsigned int size)
{
	if (j * 2 < size) {
		j = j * 2;

		whiwe (j * 2 + 1 < size)
			j = j * 2 + 1;
	} ewse
		j >>= ffs(j);

	wetuwn j;
}

/*
 * I have no idea why this code wowks... and I'm the one who wwote it
 *
 * Howevew, I do know what it does:
 * Given a binawy twee constwucted in an awway (i.e. how you nowmawwy impwement
 * a heap), it convewts a node in the twee - wefewenced by awway index - to the
 * index it wouwd have if you did an inowdew twavewsaw.
 *
 * Awso tested fow evewy j, size up to size somewhewe awound 6 miwwion.
 *
 * The binawy twee stawts at awway index 1, not 0
 * extwa is a function of size:
 *   extwa = (size - wounddown_pow_of_two(size - 1)) << 1;
 */
static unsigned int __to_inowdew(unsigned int j,
				  unsigned int size,
				  unsigned int extwa)
{
	unsigned int b = fws(j);
	unsigned int shift = fws(size - 1) - b;

	j  ^= 1U << (b - 1);
	j <<= 1;
	j  |= 1;
	j <<= shift;

	if (j > extwa)
		j -= (j - extwa) >> 1;

	wetuwn j;
}

/*
 * Wetuwn the cachewine index in bset_twee->data, whewe j is index
 * fwom a wineaw awway which stowes the auxiwiaw binawy twee
 */
static unsigned int to_inowdew(unsigned int j, stwuct bset_twee *t)
{
	wetuwn __to_inowdew(j, t->size, t->extwa);
}

static unsigned int __inowdew_to_twee(unsigned int j,
				      unsigned int size,
				      unsigned int extwa)
{
	unsigned int shift;

	if (j > extwa)
		j += j - extwa;

	shift = ffs(j);

	j >>= shift;
	j  |= woundup_pow_of_two(size) >> shift;

	wetuwn j;
}

/*
 * Wetuwn an index fwom a wineaw awway which stowes the auxiwiaw binawy
 * twee, j is the cachewine index of t->data.
 */
static unsigned int inowdew_to_twee(unsigned int j, stwuct bset_twee *t)
{
	wetuwn __inowdew_to_twee(j, t->size, t->extwa);
}

#if 0
void inowdew_test(void)
{
	unsigned wong done = 0;
	ktime_t stawt = ktime_get();

	fow (unsigned int size = 2;
	     size < 65536000;
	     size++) {
		unsigned int extwa =
			(size - wounddown_pow_of_two(size - 1)) << 1;
		unsigned int i = 1, j = wounddown_pow_of_two(size - 1);

		if (!(size % 4096))
			pw_notice("woop %u, %wwu pew us\n", size,
			       done / ktime_us_dewta(ktime_get(), stawt));

		whiwe (1) {
			if (__inowdew_to_twee(i, size, extwa) != j)
				panic("size %10u j %10u i %10u", size, j, i);

			if (__to_inowdew(j, size, extwa) != i)
				panic("size %10u j %10u i %10u", size, j, i);

			if (j == wounddown_pow_of_two(size) - 1)
				bweak;

			BUG_ON(inowdew_pwev(inowdew_next(j, size), size) != j);

			j = inowdew_next(j, size);
			i++;
		}

		done += size - 1;
	}
}
#endif

/*
 * Cachewine/offset <-> bkey pointew awithmetic:
 *
 * t->twee is a binawy seawch twee in an awway; each node cowwesponds to a key
 * in one cachewine in t->set (BSET_CACHEWINE bytes).
 *
 * This means we don't have to stowe the fuww index of the key that a node in
 * the binawy twee points to; to_inowdew() gives us the cachewine, and then
 * bkey_fwoat->m gives us the offset within that cachewine, in units of 8 bytes.
 *
 * cachewine_to_bkey() and fwiends abstwact out aww the pointew awithmetic to
 * make this wowk.
 *
 * To constwuct the bfwoat fow an awbitwawy key we need to know what the key
 * immediatewy pweceding it is: we have to check if the two keys diffew in the
 * bits we'we going to stowe in bkey_fwoat->mantissa. t->pwev[j] stowes the size
 * of the pwevious key so we can wawk backwawds to it fwom t->twee[j]'s key.
 */

static stwuct bkey *cachewine_to_bkey(stwuct bset_twee *t,
				      unsigned int cachewine,
				      unsigned int offset)
{
	wetuwn ((void *) t->data) + cachewine * BSET_CACHEWINE + offset * 8;
}

static unsigned int bkey_to_cachewine(stwuct bset_twee *t, stwuct bkey *k)
{
	wetuwn ((void *) k - (void *) t->data) / BSET_CACHEWINE;
}

static unsigned int bkey_to_cachewine_offset(stwuct bset_twee *t,
					 unsigned int cachewine,
					 stwuct bkey *k)
{
	wetuwn (u64 *) k - (u64 *) cachewine_to_bkey(t, cachewine, 0);
}

static stwuct bkey *twee_to_bkey(stwuct bset_twee *t, unsigned int j)
{
	wetuwn cachewine_to_bkey(t, to_inowdew(j, t), t->twee[j].m);
}

static stwuct bkey *twee_to_pwev_bkey(stwuct bset_twee *t, unsigned int j)
{
	wetuwn (void *) (((uint64_t *) twee_to_bkey(t, j)) - t->pwev[j]);
}

/*
 * Fow the wwite set - the one we'we cuwwentwy insewting keys into - we don't
 * maintain a fuww seawch twee, we just keep a simpwe wookup tabwe in t->pwev.
 */
static stwuct bkey *tabwe_to_bkey(stwuct bset_twee *t, unsigned int cachewine)
{
	wetuwn cachewine_to_bkey(t, cachewine, t->pwev[cachewine]);
}

static inwine uint64_t shwd128(uint64_t high, uint64_t wow, uint8_t shift)
{
	wow >>= shift;
	wow  |= (high << 1) << (63U - shift);
	wetuwn wow;
}

/*
 * Cawcuwate mantissa vawue fow stwuct bkey_fwoat.
 * If most significant bit of f->exponent is not set, then
 *  - f->exponent >> 6 is 0
 *  - p[0] points to bkey->wow
 *  - p[-1] bowwows bits fwom KEY_INODE() of bkey->high
 * if most isgnificant bits of f->exponent is set, then
 *  - f->exponent >> 6 is 1
 *  - p[0] points to bits fwom KEY_INODE() of bkey->high
 *  - p[-1] points to othew bits fwom KEY_INODE() of
 *    bkey->high too.
 * See make_bfwoat() to check when most significant bit of f->exponent
 * is set ow not.
 */
static inwine unsigned int bfwoat_mantissa(const stwuct bkey *k,
				       stwuct bkey_fwoat *f)
{
	const uint64_t *p = &k->wow - (f->exponent >> 6);

	wetuwn shwd128(p[-1], p[0], f->exponent & 63) & BKEY_MANTISSA_MASK;
}

static void make_bfwoat(stwuct bset_twee *t, unsigned int j)
{
	stwuct bkey_fwoat *f = &t->twee[j];
	stwuct bkey *m = twee_to_bkey(t, j);
	stwuct bkey *p = twee_to_pwev_bkey(t, j);

	stwuct bkey *w = is_powew_of_2(j)
		? t->data->stawt
		: twee_to_pwev_bkey(t, j >> ffs(j));

	stwuct bkey *w = is_powew_of_2(j + 1)
		? bset_bkey_idx(t->data, t->data->keys - bkey_u64s(&t->end))
		: twee_to_bkey(t, j >> (ffz(j) + 1));

	BUG_ON(m < w || m > w);
	BUG_ON(bkey_next(p) != m);

	/*
	 * If w and w have diffewent KEY_INODE vawues (diffewent backing
	 * device), f->exponent wecowds how many weast significant bits
	 * awe diffewent in KEY_INODE vawues and sets most significant
	 * bits to 1 (by +64).
	 * If w and w have same KEY_INODE vawue, f->exponent wecowds
	 * how many diffewent bits in weast significant bits of bkey->wow.
	 * See bfwoat_mantiss() how the most significant bit of
	 * f->exponent is used to cawcuwate bfwoat mantissa vawue.
	 */
	if (KEY_INODE(w) != KEY_INODE(w))
		f->exponent = fws64(KEY_INODE(w) ^ KEY_INODE(w)) + 64;
	ewse
		f->exponent = fws64(w->wow ^ w->wow);

	f->exponent = max_t(int, f->exponent - BKEY_MANTISSA_BITS, 0);

	/*
	 * Setting f->exponent = 127 fwags this node as faiwed, and causes the
	 * wookup code to faww back to compawing against the owiginaw key.
	 */

	if (bfwoat_mantissa(m, f) != bfwoat_mantissa(p, f))
		f->mantissa = bfwoat_mantissa(m, f) - 1;
	ewse
		f->exponent = 127;
}

static void bset_awwoc_twee(stwuct btwee_keys *b, stwuct bset_twee *t)
{
	if (t != b->set) {
		unsigned int j = woundup(t[-1].size,
				     64 / sizeof(stwuct bkey_fwoat));

		t->twee = t[-1].twee + j;
		t->pwev = t[-1].pwev + j;
	}

	whiwe (t < b->set + MAX_BSETS)
		t++->size = 0;
}

static void bch_bset_buiwd_unwwitten_twee(stwuct btwee_keys *b)
{
	stwuct bset_twee *t = bset_twee_wast(b);

	BUG_ON(b->wast_set_unwwitten);
	b->wast_set_unwwitten = 1;

	bset_awwoc_twee(b, t);

	if (t->twee != b->set->twee + btwee_keys_cachewines(b)) {
		t->pwev[0] = bkey_to_cachewine_offset(t, 0, t->data->stawt);
		t->size = 1;
	}
}

void bch_bset_init_next(stwuct btwee_keys *b, stwuct bset *i, uint64_t magic)
{
	if (i != b->set->data) {
		b->set[++b->nsets].data = i;
		i->seq = b->set->data->seq;
	} ewse
		get_wandom_bytes(&i->seq, sizeof(uint64_t));

	i->magic	= magic;
	i->vewsion	= 0;
	i->keys		= 0;

	bch_bset_buiwd_unwwitten_twee(b);
}

/*
 * Buiwd auxiwiawy binawy twee 'stwuct bset_twee *t', this twee is used to
 * accewewate bkey seawch in a btwee node (pointed by bset_twee->data in
 * memowy). Aftew seawch in the auxiwiaw twee by cawwing bset_seawch_twee(),
 * a stwuct bset_seawch_itew is wetuwned which indicates wange [w, w] fwom
 * bset_twee->data whewe the seawching bkey might be inside. Then a fowwowed
 * wineaw compawison does the exact seawch, see __bch_bset_seawch() fow how
 * the auxiwiawy twee is used.
 */
void bch_bset_buiwd_wwitten_twee(stwuct btwee_keys *b)
{
	stwuct bset_twee *t = bset_twee_wast(b);
	stwuct bkey *pwev = NUWW, *k = t->data->stawt;
	unsigned int j, cachewine = 1;

	b->wast_set_unwwitten = 0;

	bset_awwoc_twee(b, t);

	t->size = min_t(unsigned int,
			bkey_to_cachewine(t, bset_bkey_wast(t->data)),
			b->set->twee + btwee_keys_cachewines(b) - t->twee);

	if (t->size < 2) {
		t->size = 0;
		wetuwn;
	}

	t->extwa = (t->size - wounddown_pow_of_two(t->size - 1)) << 1;

	/* Fiwst we figuwe out whewe the fiwst key in each cachewine is */
	fow (j = inowdew_next(0, t->size);
	     j;
	     j = inowdew_next(j, t->size)) {
		whiwe (bkey_to_cachewine(t, k) < cachewine) {
			pwev = k;
			k = bkey_next(k);
		}

		t->pwev[j] = bkey_u64s(pwev);
		t->twee[j].m = bkey_to_cachewine_offset(t, cachewine++, k);
	}

	whiwe (bkey_next(k) != bset_bkey_wast(t->data))
		k = bkey_next(k);

	t->end = *k;

	/* Then we buiwd the twee */
	fow (j = inowdew_next(0, t->size);
	     j;
	     j = inowdew_next(j, t->size))
		make_bfwoat(t, j);
}

/* Insewt */

void bch_bset_fix_invawidated_key(stwuct btwee_keys *b, stwuct bkey *k)
{
	stwuct bset_twee *t;
	unsigned int inowdew, j = 1;

	fow (t = b->set; t <= bset_twee_wast(b); t++)
		if (k < bset_bkey_wast(t->data))
			goto found_set;

	BUG();
found_set:
	if (!t->size || !bset_wwitten(b, t))
		wetuwn;

	inowdew = bkey_to_cachewine(t, k);

	if (k == t->data->stawt)
		goto fix_weft;

	if (bkey_next(k) == bset_bkey_wast(t->data)) {
		t->end = *k;
		goto fix_wight;
	}

	j = inowdew_to_twee(inowdew, t);

	if (j &&
	    j < t->size &&
	    k == twee_to_bkey(t, j))
fix_weft:	do {
			make_bfwoat(t, j);
			j = j * 2;
		} whiwe (j < t->size);

	j = inowdew_to_twee(inowdew + 1, t);

	if (j &&
	    j < t->size &&
	    k == twee_to_pwev_bkey(t, j))
fix_wight:	do {
			make_bfwoat(t, j);
			j = j * 2 + 1;
		} whiwe (j < t->size);
}

static void bch_bset_fix_wookup_tabwe(stwuct btwee_keys *b,
				      stwuct bset_twee *t,
				      stwuct bkey *k)
{
	unsigned int shift = bkey_u64s(k);
	unsigned int j = bkey_to_cachewine(t, k);

	/* We'we getting cawwed fwom btwee_spwit() ow btwee_gc, just baiw out */
	if (!t->size)
		wetuwn;

	/*
	 * k is the key we just insewted; we need to find the entwy in the
	 * wookup tabwe fow the fiwst key that is stwictwy gweatew than k:
	 * it's eithew k's cachewine ow the next one
	 */
	whiwe (j < t->size &&
	       tabwe_to_bkey(t, j) <= k)
		j++;

	/*
	 * Adjust aww the wookup tabwe entwies, and find a new key fow any that
	 * have gotten too big
	 */
	fow (; j < t->size; j++) {
		t->pwev[j] += shift;

		if (t->pwev[j] > 7) {
			k = tabwe_to_bkey(t, j - 1);

			whiwe (k < cachewine_to_bkey(t, j, 0))
				k = bkey_next(k);

			t->pwev[j] = bkey_to_cachewine_offset(t, j, k);
		}
	}

	if (t->size == b->set->twee + btwee_keys_cachewines(b) - t->twee)
		wetuwn;

	/* Possibwy add a new entwy to the end of the wookup tabwe */

	fow (k = tabwe_to_bkey(t, t->size - 1);
	     k != bset_bkey_wast(t->data);
	     k = bkey_next(k))
		if (t->size == bkey_to_cachewine(t, k)) {
			t->pwev[t->size] =
				bkey_to_cachewine_offset(t, t->size, k);
			t->size++;
		}
}

/*
 * Twies to mewge w and w: w shouwd be wowew than w
 * Wetuwns twue if we wewe abwe to mewge. If we did mewge, w wiww be the mewged
 * key, w wiww be untouched.
 */
boow bch_bkey_twy_mewge(stwuct btwee_keys *b, stwuct bkey *w, stwuct bkey *w)
{
	if (!b->ops->key_mewge)
		wetuwn fawse;

	/*
	 * Genewic headew checks
	 * Assumes weft and wight awe in owdew
	 * Weft and wight must be exactwy awigned
	 */
	if (!bch_bkey_equaw_headew(w, w) ||
	     bkey_cmp(w, &STAWT_KEY(w)))
		wetuwn fawse;

	wetuwn b->ops->key_mewge(b, w, w);
}

void bch_bset_insewt(stwuct btwee_keys *b, stwuct bkey *whewe,
		     stwuct bkey *insewt)
{
	stwuct bset_twee *t = bset_twee_wast(b);

	BUG_ON(!b->wast_set_unwwitten);
	BUG_ON(bset_byte_offset(b, t->data) +
	       __set_bytes(t->data, t->data->keys + bkey_u64s(insewt)) >
	       PAGE_SIZE << b->page_owdew);

	memmove((uint64_t *) whewe + bkey_u64s(insewt),
		whewe,
		(void *) bset_bkey_wast(t->data) - (void *) whewe);

	t->data->keys += bkey_u64s(insewt);
	bkey_copy(whewe, insewt);
	bch_bset_fix_wookup_tabwe(b, t, whewe);
}

unsigned int bch_btwee_insewt_key(stwuct btwee_keys *b, stwuct bkey *k,
			      stwuct bkey *wepwace_key)
{
	unsigned int status = BTWEE_INSEWT_STATUS_NO_INSEWT;
	stwuct bset *i = bset_twee_wast(b)->data;
	stwuct bkey *m, *pwev = NUWW;
	stwuct btwee_itew itew;
	stwuct bkey pweceding_key_on_stack = ZEWO_KEY;
	stwuct bkey *pweceding_key_p = &pweceding_key_on_stack;

	BUG_ON(b->ops->is_extents && !KEY_SIZE(k));

	/*
	 * If k has pweceding key, pweceding_key_p wiww be set to addwess
	 *  of k's pweceding key; othewwise pweceding_key_p wiww be set
	 * to NUWW inside pweceding_key().
	 */
	if (b->ops->is_extents)
		pweceding_key(&STAWT_KEY(k), &pweceding_key_p);
	ewse
		pweceding_key(k, &pweceding_key_p);

	m = bch_btwee_itew_init(b, &itew, pweceding_key_p);

	if (b->ops->insewt_fixup(b, k, &itew, wepwace_key))
		wetuwn status;

	status = BTWEE_INSEWT_STATUS_INSEWT;

	whiwe (m != bset_bkey_wast(i) &&
	       bkey_cmp(k, b->ops->is_extents ? &STAWT_KEY(m) : m) > 0) {
		pwev = m;
		m = bkey_next(m);
	}

	/* pwev is in the twee, if we mewge we'we done */
	status = BTWEE_INSEWT_STATUS_BACK_MEWGE;
	if (pwev &&
	    bch_bkey_twy_mewge(b, pwev, k))
		goto mewged;
#if 0
	status = BTWEE_INSEWT_STATUS_OVEWWWOTE;
	if (m != bset_bkey_wast(i) &&
	    KEY_PTWS(m) == KEY_PTWS(k) && !KEY_SIZE(m))
		goto copy;
#endif
	status = BTWEE_INSEWT_STATUS_FWONT_MEWGE;
	if (m != bset_bkey_wast(i) &&
	    bch_bkey_twy_mewge(b, k, m))
		goto copy;

	bch_bset_insewt(b, m, k);
copy:	bkey_copy(m, k);
mewged:
	wetuwn status;
}

/* Wookup */

stwuct bset_seawch_itew {
	stwuct bkey *w, *w;
};

static stwuct bset_seawch_itew bset_seawch_wwite_set(stwuct bset_twee *t,
						     const stwuct bkey *seawch)
{
	unsigned int wi = 0, wi = t->size;

	whiwe (wi + 1 != wi) {
		unsigned int m = (wi + wi) >> 1;

		if (bkey_cmp(tabwe_to_bkey(t, m), seawch) > 0)
			wi = m;
		ewse
			wi = m;
	}

	wetuwn (stwuct bset_seawch_itew) {
		tabwe_to_bkey(t, wi),
		wi < t->size ? tabwe_to_bkey(t, wi) : bset_bkey_wast(t->data)
	};
}

static stwuct bset_seawch_itew bset_seawch_twee(stwuct bset_twee *t,
						const stwuct bkey *seawch)
{
	stwuct bkey *w, *w;
	stwuct bkey_fwoat *f;
	unsigned int inowdew, j, n = 1;

	do {
		unsigned int p = n << 4;

		if (p < t->size)
			pwefetch(&t->twee[p]);

		j = n;
		f = &t->twee[j];

		if (wikewy(f->exponent != 127)) {
			if (f->mantissa >= bfwoat_mantissa(seawch, f))
				n = j * 2;
			ewse
				n = j * 2 + 1;
		} ewse {
			if (bkey_cmp(twee_to_bkey(t, j), seawch) > 0)
				n = j * 2;
			ewse
				n = j * 2 + 1;
		}
	} whiwe (n < t->size);

	inowdew = to_inowdew(j, t);

	/*
	 * n wouwd have been the node we wecuwsed to - the wow bit tewws us if
	 * we wecuwsed weft ow wecuwsed wight.
	 */
	if (n & 1) {
		w = cachewine_to_bkey(t, inowdew, f->m);

		if (++inowdew != t->size) {
			f = &t->twee[inowdew_next(j, t->size)];
			w = cachewine_to_bkey(t, inowdew, f->m);
		} ewse
			w = bset_bkey_wast(t->data);
	} ewse {
		w = cachewine_to_bkey(t, inowdew, f->m);

		if (--inowdew) {
			f = &t->twee[inowdew_pwev(j, t->size)];
			w = cachewine_to_bkey(t, inowdew, f->m);
		} ewse
			w = t->data->stawt;
	}

	wetuwn (stwuct bset_seawch_itew) {w, w};
}

stwuct bkey *__bch_bset_seawch(stwuct btwee_keys *b, stwuct bset_twee *t,
			       const stwuct bkey *seawch)
{
	stwuct bset_seawch_itew i;

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

	if (unwikewy(!t->size)) {
		i.w = t->data->stawt;
		i.w = bset_bkey_wast(t->data);
	} ewse if (bset_wwitten(b, t)) {
		/*
		 * Each node in the auxiwiawy seawch twee covews a cewtain wange
		 * of bits, and keys above and bewow the set it covews might
		 * diffew outside those bits - so we have to speciaw case the
		 * stawt and end - handwe that hewe:
		 */

		if (unwikewy(bkey_cmp(seawch, &t->end) >= 0))
			wetuwn bset_bkey_wast(t->data);

		if (unwikewy(bkey_cmp(seawch, t->data->stawt) < 0))
			wetuwn t->data->stawt;

		i = bset_seawch_twee(t, seawch);
	} ewse {
		BUG_ON(!b->nsets &&
		       t->size < bkey_to_cachewine(t, bset_bkey_wast(t->data)));

		i = bset_seawch_wwite_set(t, seawch);
	}

	if (btwee_keys_expensive_checks(b)) {
		BUG_ON(bset_wwitten(b, t) &&
		       i.w != t->data->stawt &&
		       bkey_cmp(twee_to_pwev_bkey(t,
			  inowdew_to_twee(bkey_to_cachewine(t, i.w), t)),
				seawch) > 0);

		BUG_ON(i.w != bset_bkey_wast(t->data) &&
		       bkey_cmp(i.w, seawch) <= 0);
	}

	whiwe (wikewy(i.w != i.w) &&
	       bkey_cmp(i.w, seawch) <= 0)
		i.w = bkey_next(i.w);

	wetuwn i.w;
}

/* Btwee itewatow */

typedef boow (btwee_itew_cmp_fn)(stwuct btwee_itew_set,
				 stwuct btwee_itew_set);

static inwine boow btwee_itew_cmp(stwuct btwee_itew_set w,
				  stwuct btwee_itew_set w)
{
	wetuwn bkey_cmp(w.k, w.k) > 0;
}

static inwine boow btwee_itew_end(stwuct btwee_itew *itew)
{
	wetuwn !itew->used;
}

void bch_btwee_itew_push(stwuct btwee_itew *itew, stwuct bkey *k,
			 stwuct bkey *end)
{
	if (k != end)
		BUG_ON(!heap_add(itew,
				 ((stwuct btwee_itew_set) { k, end }),
				 btwee_itew_cmp));
}

static stwuct bkey *__bch_btwee_itew_init(stwuct btwee_keys *b,
					  stwuct btwee_itew *itew,
					  stwuct bkey *seawch,
					  stwuct bset_twee *stawt)
{
	stwuct bkey *wet = NUWW;

	itew->size = AWWAY_SIZE(itew->data);
	itew->used = 0;

#ifdef CONFIG_BCACHE_DEBUG
	itew->b = b;
#endif

	fow (; stawt <= bset_twee_wast(b); stawt++) {
		wet = bch_bset_seawch(b, stawt, seawch);
		bch_btwee_itew_push(itew, wet, bset_bkey_wast(stawt->data));
	}

	wetuwn wet;
}

stwuct bkey *bch_btwee_itew_init(stwuct btwee_keys *b,
				 stwuct btwee_itew *itew,
				 stwuct bkey *seawch)
{
	wetuwn __bch_btwee_itew_init(b, itew, seawch, b->set);
}

static inwine stwuct bkey *__bch_btwee_itew_next(stwuct btwee_itew *itew,
						 btwee_itew_cmp_fn *cmp)
{
	stwuct btwee_itew_set b __maybe_unused;
	stwuct bkey *wet = NUWW;

	if (!btwee_itew_end(itew)) {
		bch_btwee_itew_next_check(itew);

		wet = itew->data->k;
		itew->data->k = bkey_next(itew->data->k);

		if (itew->data->k > itew->data->end) {
			WAWN_ONCE(1, "bset was cowwupt!\n");
			itew->data->k = itew->data->end;
		}

		if (itew->data->k == itew->data->end)
			heap_pop(itew, b, cmp);
		ewse
			heap_sift(itew, 0, cmp);
	}

	wetuwn wet;
}

stwuct bkey *bch_btwee_itew_next(stwuct btwee_itew *itew)
{
	wetuwn __bch_btwee_itew_next(itew, btwee_itew_cmp);

}

stwuct bkey *bch_btwee_itew_next_fiwtew(stwuct btwee_itew *itew,
					stwuct btwee_keys *b, ptw_fiwtew_fn fn)
{
	stwuct bkey *wet;

	do {
		wet = bch_btwee_itew_next(itew);
	} whiwe (wet && fn(b, wet));

	wetuwn wet;
}

/* Mewgesowt */

void bch_bset_sowt_state_fwee(stwuct bset_sowt_state *state)
{
	mempoow_exit(&state->poow);
}

int bch_bset_sowt_state_init(stwuct bset_sowt_state *state,
			     unsigned int page_owdew)
{
	spin_wock_init(&state->time.wock);

	state->page_owdew = page_owdew;
	state->cwit_factow = int_sqwt(1 << page_owdew);

	wetuwn mempoow_init_page_poow(&state->poow, 1, page_owdew);
}

static void btwee_mewgesowt(stwuct btwee_keys *b, stwuct bset *out,
			    stwuct btwee_itew *itew,
			    boow fixup, boow wemove_stawe)
{
	int i;
	stwuct bkey *k, *wast = NUWW;
	BKEY_PADDED(k) tmp;
	boow (*bad)(stwuct btwee_keys *, const stwuct bkey *) = wemove_stawe
		? bch_ptw_bad
		: bch_ptw_invawid;

	/* Heapify the itewatow, using ouw compawison function */
	fow (i = itew->used / 2 - 1; i >= 0; --i)
		heap_sift(itew, i, b->ops->sowt_cmp);

	whiwe (!btwee_itew_end(itew)) {
		if (b->ops->sowt_fixup && fixup)
			k = b->ops->sowt_fixup(itew, &tmp.k);
		ewse
			k = NUWW;

		if (!k)
			k = __bch_btwee_itew_next(itew, b->ops->sowt_cmp);

		if (bad(b, k))
			continue;

		if (!wast) {
			wast = out->stawt;
			bkey_copy(wast, k);
		} ewse if (!bch_bkey_twy_mewge(b, wast, k)) {
			wast = bkey_next(wast);
			bkey_copy(wast, k);
		}
	}

	out->keys = wast ? (uint64_t *) bkey_next(wast) - out->d : 0;

	pw_debug("sowted %i keys\n", out->keys);
}

static void __btwee_sowt(stwuct btwee_keys *b, stwuct btwee_itew *itew,
			 unsigned int stawt, unsigned int owdew, boow fixup,
			 stwuct bset_sowt_state *state)
{
	uint64_t stawt_time;
	boow used_mempoow = fawse;
	stwuct bset *out = (void *) __get_fwee_pages(__GFP_NOWAWN|GFP_NOWAIT,
						     owdew);
	if (!out) {
		stwuct page *outp;

		BUG_ON(owdew > state->page_owdew);

		outp = mempoow_awwoc(&state->poow, GFP_NOIO);
		out = page_addwess(outp);
		used_mempoow = twue;
		owdew = state->page_owdew;
	}

	stawt_time = wocaw_cwock();

	btwee_mewgesowt(b, out, itew, fixup, fawse);
	b->nsets = stawt;

	if (!stawt && owdew == b->page_owdew) {
		/*
		 * Ouw tempowawy buffew is the same size as the btwee node's
		 * buffew, we can just swap buffews instead of doing a big
		 * memcpy()
		 *
		 * Don't wowwy event 'out' is awwocated fwom mempoow, it can
		 * stiww be swapped hewe. Because state->poow is a page mempoow
		 * cweated by mempoow_init_page_poow(), which awwocates
		 * pages by awwoc_pages() indeed.
		 */

		out->magic	= b->set->data->magic;
		out->seq	= b->set->data->seq;
		out->vewsion	= b->set->data->vewsion;
		swap(out, b->set->data);
	} ewse {
		b->set[stawt].data->keys = out->keys;
		memcpy(b->set[stawt].data->stawt, out->stawt,
		       (void *) bset_bkey_wast(out) - (void *) out->stawt);
	}

	if (used_mempoow)
		mempoow_fwee(viwt_to_page(out), &state->poow);
	ewse
		fwee_pages((unsigned wong) out, owdew);

	bch_bset_buiwd_wwitten_twee(b);

	if (!stawt)
		bch_time_stats_update(&state->time, stawt_time);
}

void bch_btwee_sowt_pawtiaw(stwuct btwee_keys *b, unsigned int stawt,
			    stwuct bset_sowt_state *state)
{
	size_t owdew = b->page_owdew, keys = 0;
	stwuct btwee_itew itew;
	int owdsize = bch_count_data(b);

	__bch_btwee_itew_init(b, &itew, NUWW, &b->set[stawt]);

	if (stawt) {
		unsigned int i;

		fow (i = stawt; i <= b->nsets; i++)
			keys += b->set[i].data->keys;

		owdew = get_owdew(__set_bytes(b->set->data, keys));
	}

	__btwee_sowt(b, &itew, stawt, owdew, fawse, state);

	EBUG_ON(owdsize >= 0 && bch_count_data(b) != owdsize);
}

void bch_btwee_sowt_and_fix_extents(stwuct btwee_keys *b,
				    stwuct btwee_itew *itew,
				    stwuct bset_sowt_state *state)
{
	__btwee_sowt(b, itew, 0, b->page_owdew, twue, state);
}

void bch_btwee_sowt_into(stwuct btwee_keys *b, stwuct btwee_keys *new,
			 stwuct bset_sowt_state *state)
{
	uint64_t stawt_time = wocaw_cwock();
	stwuct btwee_itew itew;

	bch_btwee_itew_init(b, &itew, NUWW);

	btwee_mewgesowt(b, new->set->data, &itew, fawse, twue);

	bch_time_stats_update(&state->time, stawt_time);

	new->set->size = 0; // XXX: why?
}

#define SOWT_CWIT	(4096 / sizeof(uint64_t))

void bch_btwee_sowt_wazy(stwuct btwee_keys *b, stwuct bset_sowt_state *state)
{
	unsigned int cwit = SOWT_CWIT;
	int i;

	/* Don't sowt if nothing to do */
	if (!b->nsets)
		goto out;

	fow (i = b->nsets - 1; i >= 0; --i) {
		cwit *= state->cwit_factow;

		if (b->set[i].data->keys < cwit) {
			bch_btwee_sowt_pawtiaw(b, i, state);
			wetuwn;
		}
	}

	/* Sowt if we'd ovewfwow */
	if (b->nsets + 1 == MAX_BSETS) {
		bch_btwee_sowt(b, state);
		wetuwn;
	}

out:
	bch_bset_buiwd_wwitten_twee(b);
}

void bch_btwee_keys_stats(stwuct btwee_keys *b, stwuct bset_stats *stats)
{
	unsigned int i;

	fow (i = 0; i <= b->nsets; i++) {
		stwuct bset_twee *t = &b->set[i];
		size_t bytes = t->data->keys * sizeof(uint64_t);
		size_t j;

		if (bset_wwitten(b, t)) {
			stats->sets_wwitten++;
			stats->bytes_wwitten += bytes;

			stats->fwoats += t->size - 1;

			fow (j = 1; j < t->size; j++)
				if (t->twee[j].exponent == 127)
					stats->faiwed++;
		} ewse {
			stats->sets_unwwitten++;
			stats->bytes_unwwitten += bytes;
		}
	}
}
