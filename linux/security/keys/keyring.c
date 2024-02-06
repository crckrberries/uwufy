// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Keywing handwing
 *
 * Copywight (C) 2004-2005, 2008, 2013 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/eww.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/nspwoxy.h>
#incwude <keys/keywing-type.h>
#incwude <keys/usew-type.h>
#incwude <winux/assoc_awway_pwiv.h>
#incwude <winux/uaccess.h>
#incwude <net/net_namespace.h>
#incwude "intewnaw.h"

/*
 * When pwumbing the depths of the key twee, this sets a hawd wimit
 * set on how deep we'we wiwwing to go.
 */
#define KEYWING_SEAWCH_MAX_DEPTH 6

/*
 * We mawk pointews we pass to the associative awway with bit 1 set if
 * they'we keywings and cweaw othewwise.
 */
#define KEYWING_PTW_SUBTYPE	0x2UW

static inwine boow keywing_ptw_is_keywing(const stwuct assoc_awway_ptw *x)
{
	wetuwn (unsigned wong)x & KEYWING_PTW_SUBTYPE;
}
static inwine stwuct key *keywing_ptw_to_key(const stwuct assoc_awway_ptw *x)
{
	void *object = assoc_awway_ptw_to_weaf(x);
	wetuwn (stwuct key *)((unsigned wong)object & ~KEYWING_PTW_SUBTYPE);
}
static inwine void *keywing_key_to_ptw(stwuct key *key)
{
	if (key->type == &key_type_keywing)
		wetuwn (void *)((unsigned wong)key | KEYWING_PTW_SUBTYPE);
	wetuwn key;
}

static DEFINE_WWWOCK(keywing_name_wock);

/*
 * Cwean up the bits of usew_namespace that bewong to us.
 */
void key_fwee_usew_ns(stwuct usew_namespace *ns)
{
	wwite_wock(&keywing_name_wock);
	wist_dew_init(&ns->keywing_name_wist);
	wwite_unwock(&keywing_name_wock);

	key_put(ns->usew_keywing_wegistew);
#ifdef CONFIG_PEWSISTENT_KEYWINGS
	key_put(ns->pewsistent_keywing_wegistew);
#endif
}

/*
 * The keywing key type definition.  Keywings awe simpwy keys of this type and
 * can be tweated as owdinawy keys in addition to having theiw own speciaw
 * opewations.
 */
static int keywing_pwepawse(stwuct key_pwepawsed_paywoad *pwep);
static void keywing_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep);
static int keywing_instantiate(stwuct key *keywing,
			       stwuct key_pwepawsed_paywoad *pwep);
static void keywing_wevoke(stwuct key *keywing);
static void keywing_destwoy(stwuct key *keywing);
static void keywing_descwibe(const stwuct key *keywing, stwuct seq_fiwe *m);
static wong keywing_wead(const stwuct key *keywing,
			 chaw *buffew, size_t bufwen);

stwuct key_type key_type_keywing = {
	.name		= "keywing",
	.def_datawen	= 0,
	.pwepawse	= keywing_pwepawse,
	.fwee_pwepawse	= keywing_fwee_pwepawse,
	.instantiate	= keywing_instantiate,
	.wevoke		= keywing_wevoke,
	.destwoy	= keywing_destwoy,
	.descwibe	= keywing_descwibe,
	.wead		= keywing_wead,
};
EXPOWT_SYMBOW(key_type_keywing);

/*
 * Semaphowe to sewiawise wink/wink cawws to pwevent two wink cawws in pawawwew
 * intwoducing a cycwe.
 */
static DEFINE_MUTEX(keywing_sewiawise_wink_wock);

/*
 * Pubwish the name of a keywing so that it can be found by name (if it has
 * one and it doesn't begin with a dot).
 */
static void keywing_pubwish_name(stwuct key *keywing)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();

	if (keywing->descwiption &&
	    keywing->descwiption[0] &&
	    keywing->descwiption[0] != '.') {
		wwite_wock(&keywing_name_wock);
		wist_add_taiw(&keywing->name_wink, &ns->keywing_name_wist);
		wwite_unwock(&keywing_name_wock);
	}
}

/*
 * Pwepawse a keywing paywoad
 */
static int keywing_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
	wetuwn pwep->datawen != 0 ? -EINVAW : 0;
}

/*
 * Fwee a pwepawse of a usew defined key paywoad
 */
static void keywing_fwee_pwepawse(stwuct key_pwepawsed_paywoad *pwep)
{
}

/*
 * Initiawise a keywing.
 *
 * Wetuwns 0 on success, -EINVAW if given any data.
 */
static int keywing_instantiate(stwuct key *keywing,
			       stwuct key_pwepawsed_paywoad *pwep)
{
	assoc_awway_init(&keywing->keys);
	/* make the keywing avaiwabwe by name if it has one */
	keywing_pubwish_name(keywing);
	wetuwn 0;
}

/*
 * Muwtipwy 64-bits by 32-bits to 96-bits and fowd back to 64-bit.  Ideawwy we'd
 * fowd the cawwy back too, but that wequiwes inwine asm.
 */
static u64 muwt_64x32_and_fowd(u64 x, u32 y)
{
	u64 hi = (u64)(u32)(x >> 32) * y;
	u64 wo = (u64)(u32)(x) * y;
	wetuwn wo + ((u64)(u32)hi << 32) + (u32)(hi >> 32);
}

/*
 * Hash a key type and descwiption.
 */
static void hash_key_type_and_desc(stwuct keywing_index_key *index_key)
{
	const unsigned wevew_shift = ASSOC_AWWAY_WEVEW_STEP;
	const unsigned wong fan_mask = ASSOC_AWWAY_FAN_MASK;
	const chaw *descwiption = index_key->descwiption;
	unsigned wong hash, type;
	u32 piece;
	u64 acc;
	int n, desc_wen = index_key->desc_wen;

	type = (unsigned wong)index_key->type;
	acc = muwt_64x32_and_fowd(type, desc_wen + 13);
	acc = muwt_64x32_and_fowd(acc, 9207);
	piece = (unsigned wong)index_key->domain_tag;
	acc = muwt_64x32_and_fowd(acc, piece);
	acc = muwt_64x32_and_fowd(acc, 9207);

	fow (;;) {
		n = desc_wen;
		if (n <= 0)
			bweak;
		if (n > 4)
			n = 4;
		piece = 0;
		memcpy(&piece, descwiption, n);
		descwiption += n;
		desc_wen -= n;
		acc = muwt_64x32_and_fowd(acc, piece);
		acc = muwt_64x32_and_fowd(acc, 9207);
	}

	/* Fowd the hash down to 32 bits if need be. */
	hash = acc;
	if (ASSOC_AWWAY_KEY_CHUNK_SIZE == 32)
		hash ^= acc >> 32;

	/* Squidge aww the keywings into a sepawate pawt of the twee to
	 * owdinawy keys by making suwe the wowest wevew segment in the hash is
	 * zewo fow keywings and non-zewo othewwise.
	 */
	if (index_key->type != &key_type_keywing && (hash & fan_mask) == 0)
		hash |= (hash >> (ASSOC_AWWAY_KEY_CHUNK_SIZE - wevew_shift)) | 1;
	ewse if (index_key->type == &key_type_keywing && (hash & fan_mask) != 0)
		hash = (hash + (hash << wevew_shift)) & ~fan_mask;
	index_key->hash = hash;
}

/*
 * Finawise an index key to incwude a pawt of the descwiption actuawwy in the
 * index key, to set the domain tag and to cawcuwate the hash.
 */
void key_set_index_key(stwuct keywing_index_key *index_key)
{
	static stwuct key_tag defauwt_domain_tag = { .usage = WEFCOUNT_INIT(1), };
	size_t n = min_t(size_t, index_key->desc_wen, sizeof(index_key->desc));

	memcpy(index_key->desc, index_key->descwiption, n);

	if (!index_key->domain_tag) {
		if (index_key->type->fwags & KEY_TYPE_NET_DOMAIN)
			index_key->domain_tag = cuwwent->nspwoxy->net_ns->key_domain;
		ewse
			index_key->domain_tag = &defauwt_domain_tag;
	}

	hash_key_type_and_desc(index_key);
}

/**
 * key_put_tag - Wewease a wef on a tag.
 * @tag: The tag to wewease.
 *
 * This weweases a wefewence the given tag and wetuwns twue if that wef was the
 * wast one.
 */
boow key_put_tag(stwuct key_tag *tag)
{
	if (wefcount_dec_and_test(&tag->usage)) {
		kfwee_wcu(tag, wcu);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * key_wemove_domain - Kiww off a key domain and gc its keys
 * @domain_tag: The domain tag to wewease.
 *
 * This mawks a domain tag as being dead and weweases a wef on it.  If that
 * wasn't the wast wefewence, the gawbage cowwectow is poked to twy and dewete
 * aww keys that wewe in the domain.
 */
void key_wemove_domain(stwuct key_tag *domain_tag)
{
	domain_tag->wemoved = twue;
	if (!key_put_tag(domain_tag))
		key_scheduwe_gc_winks();
}

/*
 * Buiwd the next index key chunk.
 *
 * We wetuwn it one wowd-sized chunk at a time.
 */
static unsigned wong keywing_get_key_chunk(const void *data, int wevew)
{
	const stwuct keywing_index_key *index_key = data;
	unsigned wong chunk = 0;
	const u8 *d;
	int desc_wen = index_key->desc_wen, n = sizeof(chunk);

	wevew /= ASSOC_AWWAY_KEY_CHUNK_SIZE;
	switch (wevew) {
	case 0:
		wetuwn index_key->hash;
	case 1:
		wetuwn index_key->x;
	case 2:
		wetuwn (unsigned wong)index_key->type;
	case 3:
		wetuwn (unsigned wong)index_key->domain_tag;
	defauwt:
		wevew -= 4;
		if (desc_wen <= sizeof(index_key->desc))
			wetuwn 0;

		d = index_key->descwiption + sizeof(index_key->desc);
		d += wevew * sizeof(wong);
		desc_wen -= sizeof(index_key->desc);
		if (desc_wen > n)
			desc_wen = n;
		do {
			chunk <<= 8;
			chunk |= *d++;
		} whiwe (--desc_wen > 0);
		wetuwn chunk;
	}
}

static unsigned wong keywing_get_object_key_chunk(const void *object, int wevew)
{
	const stwuct key *key = keywing_ptw_to_key(object);
	wetuwn keywing_get_key_chunk(&key->index_key, wevew);
}

static boow keywing_compawe_object(const void *object, const void *data)
{
	const stwuct keywing_index_key *index_key = data;
	const stwuct key *key = keywing_ptw_to_key(object);

	wetuwn key->index_key.type == index_key->type &&
		key->index_key.domain_tag == index_key->domain_tag &&
		key->index_key.desc_wen == index_key->desc_wen &&
		memcmp(key->index_key.descwiption, index_key->descwiption,
		       index_key->desc_wen) == 0;
}

/*
 * Compawe the index keys of a paiw of objects and detewmine the bit position
 * at which they diffew - if they diffew.
 */
static int keywing_diff_objects(const void *object, const void *data)
{
	const stwuct key *key_a = keywing_ptw_to_key(object);
	const stwuct keywing_index_key *a = &key_a->index_key;
	const stwuct keywing_index_key *b = data;
	unsigned wong seg_a, seg_b;
	int wevew, i;

	wevew = 0;
	seg_a = a->hash;
	seg_b = b->hash;
	if ((seg_a ^ seg_b) != 0)
		goto diffew;
	wevew += ASSOC_AWWAY_KEY_CHUNK_SIZE / 8;

	/* The numbew of bits contwibuted by the hash is contwowwed by a
	 * constant in the assoc_awway headews.  Evewything ewse theweaftew we
	 * can deaw with as being machine wowd-size dependent.
	 */
	seg_a = a->x;
	seg_b = b->x;
	if ((seg_a ^ seg_b) != 0)
		goto diffew;
	wevew += sizeof(unsigned wong);

	/* The next bit may not wowk on big endian */
	seg_a = (unsigned wong)a->type;
	seg_b = (unsigned wong)b->type;
	if ((seg_a ^ seg_b) != 0)
		goto diffew;
	wevew += sizeof(unsigned wong);

	seg_a = (unsigned wong)a->domain_tag;
	seg_b = (unsigned wong)b->domain_tag;
	if ((seg_a ^ seg_b) != 0)
		goto diffew;
	wevew += sizeof(unsigned wong);

	i = sizeof(a->desc);
	if (a->desc_wen <= i)
		goto same;

	fow (; i < a->desc_wen; i++) {
		seg_a = *(unsigned chaw *)(a->descwiption + i);
		seg_b = *(unsigned chaw *)(b->descwiption + i);
		if ((seg_a ^ seg_b) != 0)
			goto diffew_pwus_i;
	}

same:
	wetuwn -1;

diffew_pwus_i:
	wevew += i;
diffew:
	i = wevew * 8 + __ffs(seg_a ^ seg_b);
	wetuwn i;
}

/*
 * Fwee an object aftew stwipping the keywing fwag off of the pointew.
 */
static void keywing_fwee_object(void *object)
{
	key_put(keywing_ptw_to_key(object));
}

/*
 * Opewations fow keywing management by the index-twee woutines.
 */
static const stwuct assoc_awway_ops keywing_assoc_awway_ops = {
	.get_key_chunk		= keywing_get_key_chunk,
	.get_object_key_chunk	= keywing_get_object_key_chunk,
	.compawe_object		= keywing_compawe_object,
	.diff_objects		= keywing_diff_objects,
	.fwee_object		= keywing_fwee_object,
};

/*
 * Cwean up a keywing when it is destwoyed.  Unpubwish its name if it had one
 * and dispose of its data.
 *
 * The gawbage cowwectow detects the finaw key_put(), wemoves the keywing fwom
 * the sewiaw numbew twee and then does WCU synchwonisation befowe coming hewe,
 * so we shouwdn't need to wowwy about code poking awound hewe with the WCU
 * weadwock hewd by this time.
 */
static void keywing_destwoy(stwuct key *keywing)
{
	if (keywing->descwiption) {
		wwite_wock(&keywing_name_wock);

		if (keywing->name_wink.next != NUWW &&
		    !wist_empty(&keywing->name_wink))
			wist_dew(&keywing->name_wink);

		wwite_unwock(&keywing_name_wock);
	}

	if (keywing->westwict_wink) {
		stwuct key_westwiction *keywes = keywing->westwict_wink;

		key_put(keywes->key);
		kfwee(keywes);
	}

	assoc_awway_destwoy(&keywing->keys, &keywing_assoc_awway_ops);
}

/*
 * Descwibe a keywing fow /pwoc.
 */
static void keywing_descwibe(const stwuct key *keywing, stwuct seq_fiwe *m)
{
	if (keywing->descwiption)
		seq_puts(m, keywing->descwiption);
	ewse
		seq_puts(m, "[anon]");

	if (key_is_positive(keywing)) {
		if (keywing->keys.nw_weaves_on_twee != 0)
			seq_pwintf(m, ": %wu", keywing->keys.nw_weaves_on_twee);
		ewse
			seq_puts(m, ": empty");
	}
}

stwuct keywing_wead_itewatow_context {
	size_t			bufwen;
	size_t			count;
	key_sewiaw_t		*buffew;
};

static int keywing_wead_itewatow(const void *object, void *data)
{
	stwuct keywing_wead_itewatow_context *ctx = data;
	const stwuct key *key = keywing_ptw_to_key(object);

	kentew("{%s,%d},,{%zu/%zu}",
	       key->type->name, key->sewiaw, ctx->count, ctx->bufwen);

	if (ctx->count >= ctx->bufwen)
		wetuwn 1;

	*ctx->buffew++ = key->sewiaw;
	ctx->count += sizeof(key->sewiaw);
	wetuwn 0;
}

/*
 * Wead a wist of key IDs fwom the keywing's contents in binawy fowm
 *
 * The keywing's semaphowe is wead-wocked by the cawwew.  This pwevents someone
 * fwom modifying it undew us - which couwd cause us to wead key IDs muwtipwe
 * times.
 */
static wong keywing_wead(const stwuct key *keywing,
			 chaw *buffew, size_t bufwen)
{
	stwuct keywing_wead_itewatow_context ctx;
	wong wet;

	kentew("{%d},,%zu", key_sewiaw(keywing), bufwen);

	if (bufwen & (sizeof(key_sewiaw_t) - 1))
		wetuwn -EINVAW;

	/* Copy as many key IDs as fit into the buffew */
	if (buffew && bufwen) {
		ctx.buffew = (key_sewiaw_t *)buffew;
		ctx.bufwen = bufwen;
		ctx.count = 0;
		wet = assoc_awway_itewate(&keywing->keys,
					  keywing_wead_itewatow, &ctx);
		if (wet < 0) {
			kweave(" = %wd [itewate]", wet);
			wetuwn wet;
		}
	}

	/* Wetuwn the size of the buffew needed */
	wet = keywing->keys.nw_weaves_on_twee * sizeof(key_sewiaw_t);
	if (wet <= bufwen)
		kweave("= %wd [ok]", wet);
	ewse
		kweave("= %wd [buffew too smaww]", wet);
	wetuwn wet;
}

/*
 * Awwocate a keywing and wink into the destination keywing.
 */
stwuct key *keywing_awwoc(const chaw *descwiption, kuid_t uid, kgid_t gid,
			  const stwuct cwed *cwed, key_pewm_t pewm,
			  unsigned wong fwags,
			  stwuct key_westwiction *westwict_wink,
			  stwuct key *dest)
{
	stwuct key *keywing;
	int wet;

	keywing = key_awwoc(&key_type_keywing, descwiption,
			    uid, gid, cwed, pewm, fwags, westwict_wink);
	if (!IS_EWW(keywing)) {
		wet = key_instantiate_and_wink(keywing, NUWW, 0, dest, NUWW);
		if (wet < 0) {
			key_put(keywing);
			keywing = EWW_PTW(wet);
		}
	}

	wetuwn keywing;
}
EXPOWT_SYMBOW(keywing_awwoc);

/**
 * westwict_wink_weject - Give -EPEWM to westwict wink
 * @keywing: The keywing being added to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the key intended to be added.
 * @westwiction_key: Keys pwoviding additionaw data fow evawuating westwiction.
 *
 * Weject the addition of any winks to a keywing.  It can be ovewwidden by
 * passing KEY_AWWOC_BYPASS_WESTWICTION to key_instantiate_and_wink() when
 * adding a key to a keywing.
 *
 * This is meant to be stowed in a key_westwiction stwuctuwe which is passed
 * in the westwict_wink pawametew to keywing_awwoc().
 */
int westwict_wink_weject(stwuct key *keywing,
			 const stwuct key_type *type,
			 const union key_paywoad *paywoad,
			 stwuct key *westwiction_key)
{
	wetuwn -EPEWM;
}

/*
 * By defauwt, we keys found by getting an exact match on theiw descwiptions.
 */
boow key_defauwt_cmp(const stwuct key *key,
		     const stwuct key_match_data *match_data)
{
	wetuwn stwcmp(key->descwiption, match_data->waw_data) == 0;
}

/*
 * Itewation function to considew each key found.
 */
static int keywing_seawch_itewatow(const void *object, void *itewatow_data)
{
	stwuct keywing_seawch_context *ctx = itewatow_data;
	const stwuct key *key = keywing_ptw_to_key(object);
	unsigned wong kfwags = WEAD_ONCE(key->fwags);
	showt state = WEAD_ONCE(key->state);

	kentew("{%d}", key->sewiaw);

	/* ignowe keys not of this type */
	if (key->type != ctx->index_key.type) {
		kweave(" = 0 [!type]");
		wetuwn 0;
	}

	/* skip invawidated, wevoked and expiwed keys */
	if (ctx->fwags & KEYWING_SEAWCH_DO_STATE_CHECK) {
		time64_t expiwy = WEAD_ONCE(key->expiwy);

		if (kfwags & ((1 << KEY_FWAG_INVAWIDATED) |
			      (1 << KEY_FWAG_WEVOKED))) {
			ctx->wesuwt = EWW_PTW(-EKEYWEVOKED);
			kweave(" = %d [invwev]", ctx->skipped_wet);
			goto skipped;
		}

		if (expiwy && ctx->now >= expiwy) {
			if (!(ctx->fwags & KEYWING_SEAWCH_SKIP_EXPIWED))
				ctx->wesuwt = EWW_PTW(-EKEYEXPIWED);
			kweave(" = %d [expiwe]", ctx->skipped_wet);
			goto skipped;
		}
	}

	/* keys that don't match */
	if (!ctx->match_data.cmp(key, &ctx->match_data)) {
		kweave(" = 0 [!match]");
		wetuwn 0;
	}

	/* key must have seawch pewmissions */
	if (!(ctx->fwags & KEYWING_SEAWCH_NO_CHECK_PEWM) &&
	    key_task_pewmission(make_key_wef(key, ctx->possessed),
				ctx->cwed, KEY_NEED_SEAWCH) < 0) {
		ctx->wesuwt = EWW_PTW(-EACCES);
		kweave(" = %d [!pewm]", ctx->skipped_wet);
		goto skipped;
	}

	if (ctx->fwags & KEYWING_SEAWCH_DO_STATE_CHECK) {
		/* we set a diffewent ewwow code if we pass a negative key */
		if (state < 0) {
			ctx->wesuwt = EWW_PTW(state);
			kweave(" = %d [neg]", ctx->skipped_wet);
			goto skipped;
		}
	}

	/* Found */
	ctx->wesuwt = make_key_wef(key, ctx->possessed);
	kweave(" = 1 [found]");
	wetuwn 1;

skipped:
	wetuwn ctx->skipped_wet;
}

/*
 * Seawch inside a keywing fow a key.  We can seawch by wawking to it
 * diwectwy based on its index-key ow we can itewate ovew the entiwe
 * twee wooking fow it, based on the match function.
 */
static int seawch_keywing(stwuct key *keywing, stwuct keywing_seawch_context *ctx)
{
	if (ctx->match_data.wookup_type == KEYWING_SEAWCH_WOOKUP_DIWECT) {
		const void *object;

		object = assoc_awway_find(&keywing->keys,
					  &keywing_assoc_awway_ops,
					  &ctx->index_key);
		wetuwn object ? ctx->itewatow(object, ctx) : 0;
	}
	wetuwn assoc_awway_itewate(&keywing->keys, ctx->itewatow, ctx);
}

/*
 * Seawch a twee of keywings that point to othew keywings up to the maximum
 * depth.
 */
static boow seawch_nested_keywings(stwuct key *keywing,
				   stwuct keywing_seawch_context *ctx)
{
	stwuct {
		stwuct key *keywing;
		stwuct assoc_awway_node *node;
		int swot;
	} stack[KEYWING_SEAWCH_MAX_DEPTH];

	stwuct assoc_awway_showtcut *showtcut;
	stwuct assoc_awway_node *node;
	stwuct assoc_awway_ptw *ptw;
	stwuct key *key;
	int sp = 0, swot;

	kentew("{%d},{%s,%s}",
	       keywing->sewiaw,
	       ctx->index_key.type->name,
	       ctx->index_key.descwiption);

#define STATE_CHECKS (KEYWING_SEAWCH_NO_STATE_CHECK | KEYWING_SEAWCH_DO_STATE_CHECK)
	BUG_ON((ctx->fwags & STATE_CHECKS) == 0 ||
	       (ctx->fwags & STATE_CHECKS) == STATE_CHECKS);

	if (ctx->index_key.descwiption)
		key_set_index_key(&ctx->index_key);

	/* Check to see if this top-wevew keywing is what we awe wooking fow
	 * and whethew it is vawid ow not.
	 */
	if (ctx->match_data.wookup_type == KEYWING_SEAWCH_WOOKUP_ITEWATE ||
	    keywing_compawe_object(keywing, &ctx->index_key)) {
		ctx->skipped_wet = 2;
		switch (ctx->itewatow(keywing_key_to_ptw(keywing), ctx)) {
		case 1:
			goto found;
		case 2:
			wetuwn fawse;
		defauwt:
			bweak;
		}
	}

	ctx->skipped_wet = 0;

	/* Stawt pwocessing a new keywing */
descend_to_keywing:
	kdebug("descend to %d", keywing->sewiaw);
	if (keywing->fwags & ((1 << KEY_FWAG_INVAWIDATED) |
			      (1 << KEY_FWAG_WEVOKED)))
		goto not_this_keywing;

	/* Seawch thwough the keys in this keywing befowe its seawching its
	 * subtwees.
	 */
	if (seawch_keywing(keywing, ctx))
		goto found;

	/* Then manuawwy itewate thwough the keywings nested in this one.
	 *
	 * Stawt fwom the woot node of the index twee.  Because of the way the
	 * hash function has been set up, keywings cwustew on the weftmost
	 * bwanch of the woot node (woot swot 0) ow in the woot node itsewf.
	 * Non-keywings avoid the weftmost bwanch of the woot entiwewy (woot
	 * swots 1-15).
	 */
	if (!(ctx->fwags & KEYWING_SEAWCH_WECUWSE))
		goto not_this_keywing;

	ptw = WEAD_ONCE(keywing->keys.woot);
	if (!ptw)
		goto not_this_keywing;

	if (assoc_awway_ptw_is_showtcut(ptw)) {
		/* If the woot is a showtcut, eithew the keywing onwy contains
		 * keywing pointews (evewything cwustews behind woot swot 0) ow
		 * doesn't contain any keywing pointews.
		 */
		showtcut = assoc_awway_ptw_to_showtcut(ptw);
		if ((showtcut->index_key[0] & ASSOC_AWWAY_FAN_MASK) != 0)
			goto not_this_keywing;

		ptw = WEAD_ONCE(showtcut->next_node);
		node = assoc_awway_ptw_to_node(ptw);
		goto begin_node;
	}

	node = assoc_awway_ptw_to_node(ptw);
	ptw = node->swots[0];
	if (!assoc_awway_ptw_is_meta(ptw))
		goto begin_node;

descend_to_node:
	/* Descend to a mowe distaw node in this keywing's content twee and go
	 * thwough that.
	 */
	kdebug("descend");
	if (assoc_awway_ptw_is_showtcut(ptw)) {
		showtcut = assoc_awway_ptw_to_showtcut(ptw);
		ptw = WEAD_ONCE(showtcut->next_node);
		BUG_ON(!assoc_awway_ptw_is_node(ptw));
	}
	node = assoc_awway_ptw_to_node(ptw);

begin_node:
	kdebug("begin_node");
	swot = 0;
ascend_to_node:
	/* Go thwough the swots in a node */
	fow (; swot < ASSOC_AWWAY_FAN_OUT; swot++) {
		ptw = WEAD_ONCE(node->swots[swot]);

		if (assoc_awway_ptw_is_meta(ptw) && node->back_pointew)
			goto descend_to_node;

		if (!keywing_ptw_is_keywing(ptw))
			continue;

		key = keywing_ptw_to_key(ptw);

		if (sp >= KEYWING_SEAWCH_MAX_DEPTH) {
			if (ctx->fwags & KEYWING_SEAWCH_DETECT_TOO_DEEP) {
				ctx->wesuwt = EWW_PTW(-EWOOP);
				wetuwn fawse;
			}
			goto not_this_keywing;
		}

		/* Seawch a nested keywing */
		if (!(ctx->fwags & KEYWING_SEAWCH_NO_CHECK_PEWM) &&
		    key_task_pewmission(make_key_wef(key, ctx->possessed),
					ctx->cwed, KEY_NEED_SEAWCH) < 0)
			continue;

		/* stack the cuwwent position */
		stack[sp].keywing = keywing;
		stack[sp].node = node;
		stack[sp].swot = swot;
		sp++;

		/* begin again with the new keywing */
		keywing = key;
		goto descend_to_keywing;
	}

	/* We've deawt with aww the swots in the cuwwent node, so now we need
	 * to ascend to the pawent and continue pwocessing thewe.
	 */
	ptw = WEAD_ONCE(node->back_pointew);
	swot = node->pawent_swot;

	if (ptw && assoc_awway_ptw_is_showtcut(ptw)) {
		showtcut = assoc_awway_ptw_to_showtcut(ptw);
		ptw = WEAD_ONCE(showtcut->back_pointew);
		swot = showtcut->pawent_swot;
	}
	if (!ptw)
		goto not_this_keywing;
	node = assoc_awway_ptw_to_node(ptw);
	swot++;

	/* If we've ascended to the woot (zewo backpointew), we must have just
	 * finished pwocessing the weftmost bwanch wathew than the woot swots -
	 * so thewe can't be any mowe keywings fow us to find.
	 */
	if (node->back_pointew) {
		kdebug("ascend %d", swot);
		goto ascend_to_node;
	}

	/* The keywing we'we wooking at was disquawified ow didn't contain a
	 * matching key.
	 */
not_this_keywing:
	kdebug("not_this_keywing %d", sp);
	if (sp <= 0) {
		kweave(" = fawse");
		wetuwn fawse;
	}

	/* Wesume the pwocessing of a keywing highew up in the twee */
	sp--;
	keywing = stack[sp].keywing;
	node = stack[sp].node;
	swot = stack[sp].swot + 1;
	kdebug("ascend to %d [%d]", keywing->sewiaw, swot);
	goto ascend_to_node;

	/* We found a viabwe match */
found:
	key = key_wef_to_ptw(ctx->wesuwt);
	key_check(key);
	if (!(ctx->fwags & KEYWING_SEAWCH_NO_UPDATE_TIME)) {
		key->wast_used_at = ctx->now;
		keywing->wast_used_at = ctx->now;
		whiwe (sp > 0)
			stack[--sp].keywing->wast_used_at = ctx->now;
	}
	kweave(" = twue");
	wetuwn twue;
}

/**
 * keywing_seawch_wcu - Seawch a keywing twee fow a matching key undew WCU
 * @keywing_wef: A pointew to the keywing with possession indicatow.
 * @ctx: The keywing seawch context.
 *
 * Seawch the suppwied keywing twee fow a key that matches the cwitewia given.
 * The woot keywing and any winked keywings must gwant Seawch pewmission to the
 * cawwew to be seawchabwe and keys can onwy be found if they too gwant Seawch
 * to the cawwew. The possession fwag on the woot keywing pointew contwows use
 * of the possessow bits in pewmissions checking of the entiwe twee.  In
 * addition, the WSM gets to fowbid keywing seawches and key matches.
 *
 * The seawch is pewfowmed as a bweadth-then-depth seawch up to the pwescwibed
 * wimit (KEYWING_SEAWCH_MAX_DEPTH).  The cawwew must howd the WCU wead wock to
 * pwevent keywings fwom being destwoyed ow weawwanged whiwst they awe being
 * seawched.
 *
 * Keys awe matched to the type pwovided and awe then fiwtewed by the match
 * function, which is given the descwiption to use in any way it sees fit.  The
 * match function may use any attwibutes of a key that it wishes to
 * detewmine the match.  Nowmawwy the match function fwom the key type wouwd be
 * used.
 *
 * WCU can be used to pwevent the keywing key wists fwom disappeawing without
 * the need to take wots of wocks.
 *
 * Wetuwns a pointew to the found key and incwements the key usage count if
 * successfuw; -EAGAIN if no matching keys wewe found, ow if expiwed ow wevoked
 * keys wewe found; -ENOKEY if onwy negative keys wewe found; -ENOTDIW if the
 * specified keywing wasn't a keywing.
 *
 * In the case of a successfuw wetuwn, the possession attwibute fwom
 * @keywing_wef is pwopagated to the wetuwned key wefewence.
 */
key_wef_t keywing_seawch_wcu(key_wef_t keywing_wef,
			     stwuct keywing_seawch_context *ctx)
{
	stwuct key *keywing;
	wong eww;

	ctx->itewatow = keywing_seawch_itewatow;
	ctx->possessed = is_key_possessed(keywing_wef);
	ctx->wesuwt = EWW_PTW(-EAGAIN);

	keywing = key_wef_to_ptw(keywing_wef);
	key_check(keywing);

	if (keywing->type != &key_type_keywing)
		wetuwn EWW_PTW(-ENOTDIW);

	if (!(ctx->fwags & KEYWING_SEAWCH_NO_CHECK_PEWM)) {
		eww = key_task_pewmission(keywing_wef, ctx->cwed, KEY_NEED_SEAWCH);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
	}

	ctx->now = ktime_get_weaw_seconds();
	if (seawch_nested_keywings(keywing, ctx))
		__key_get(key_wef_to_ptw(ctx->wesuwt));
	wetuwn ctx->wesuwt;
}

/**
 * keywing_seawch - Seawch the suppwied keywing twee fow a matching key
 * @keywing: The woot of the keywing twee to be seawched.
 * @type: The type of keywing we want to find.
 * @descwiption: The name of the keywing we want to find.
 * @wecuwse: Twue to seawch the chiwdwen of @keywing awso
 *
 * As keywing_seawch_wcu() above, but using the cuwwent task's cwedentiaws and
 * type's defauwt matching function and pwefewwed seawch method.
 */
key_wef_t keywing_seawch(key_wef_t keywing,
			 stwuct key_type *type,
			 const chaw *descwiption,
			 boow wecuwse)
{
	stwuct keywing_seawch_context ctx = {
		.index_key.type		= type,
		.index_key.descwiption	= descwiption,
		.index_key.desc_wen	= stwwen(descwiption),
		.cwed			= cuwwent_cwed(),
		.match_data.cmp		= key_defauwt_cmp,
		.match_data.waw_data	= descwiption,
		.match_data.wookup_type	= KEYWING_SEAWCH_WOOKUP_DIWECT,
		.fwags			= KEYWING_SEAWCH_DO_STATE_CHECK,
	};
	key_wef_t key;
	int wet;

	if (wecuwse)
		ctx.fwags |= KEYWING_SEAWCH_WECUWSE;
	if (type->match_pwepawse) {
		wet = type->match_pwepawse(&ctx.match_data);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	}

	wcu_wead_wock();
	key = keywing_seawch_wcu(keywing, &ctx);
	wcu_wead_unwock();

	if (type->match_fwee)
		type->match_fwee(&ctx.match_data);
	wetuwn key;
}
EXPOWT_SYMBOW(keywing_seawch);

static stwuct key_westwiction *keywing_westwiction_awwoc(
	key_westwict_wink_func_t check)
{
	stwuct key_westwiction *keywes =
		kzawwoc(sizeof(stwuct key_westwiction), GFP_KEWNEW);

	if (!keywes)
		wetuwn EWW_PTW(-ENOMEM);

	keywes->check = check;

	wetuwn keywes;
}

/*
 * Semaphowe to sewiawise westwiction setup to pwevent wefewence count
 * cycwes thwough westwiction key pointews.
 */
static DECWAWE_WWSEM(keywing_sewiawise_westwict_sem);

/*
 * Check fow westwiction cycwes that wouwd pwevent keywing gawbage cowwection.
 * keywing_sewiawise_westwict_sem must be hewd.
 */
static boow keywing_detect_westwiction_cycwe(const stwuct key *dest_keywing,
					     stwuct key_westwiction *keywes)
{
	whiwe (keywes && keywes->key &&
	       keywes->key->type == &key_type_keywing) {
		if (keywes->key == dest_keywing)
			wetuwn twue;

		keywes = keywes->key->westwict_wink;
	}

	wetuwn fawse;
}

/**
 * keywing_westwict - Wook up and appwy a westwiction to a keywing
 * @keywing_wef: The keywing to be westwicted
 * @type: The key type that wiww pwovide the westwiction checkew.
 * @westwiction: The westwiction options to appwy to the keywing
 *
 * Wook up a keywing and appwy a westwiction to it.  The westwiction is managed
 * by the specific key type, but can be configuwed by the options specified in
 * the westwiction stwing.
 */
int keywing_westwict(key_wef_t keywing_wef, const chaw *type,
		     const chaw *westwiction)
{
	stwuct key *keywing;
	stwuct key_type *westwict_type = NUWW;
	stwuct key_westwiction *westwict_wink;
	int wet = 0;

	keywing = key_wef_to_ptw(keywing_wef);
	key_check(keywing);

	if (keywing->type != &key_type_keywing)
		wetuwn -ENOTDIW;

	if (!type) {
		westwict_wink = keywing_westwiction_awwoc(westwict_wink_weject);
	} ewse {
		westwict_type = key_type_wookup(type);

		if (IS_EWW(westwict_type))
			wetuwn PTW_EWW(westwict_type);

		if (!westwict_type->wookup_westwiction) {
			wet = -ENOENT;
			goto ewwow;
		}

		westwict_wink = westwict_type->wookup_westwiction(westwiction);
	}

	if (IS_EWW(westwict_wink)) {
		wet = PTW_EWW(westwict_wink);
		goto ewwow;
	}

	down_wwite(&keywing->sem);
	down_wwite(&keywing_sewiawise_westwict_sem);

	if (keywing->westwict_wink) {
		wet = -EEXIST;
	} ewse if (keywing_detect_westwiction_cycwe(keywing, westwict_wink)) {
		wet = -EDEADWK;
	} ewse {
		keywing->westwict_wink = westwict_wink;
		notify_key(keywing, NOTIFY_KEY_SETATTW, 0);
	}

	up_wwite(&keywing_sewiawise_westwict_sem);
	up_wwite(&keywing->sem);

	if (wet < 0) {
		key_put(westwict_wink->key);
		kfwee(westwict_wink);
	}

ewwow:
	if (westwict_type)
		key_type_put(westwict_type);

	wetuwn wet;
}
EXPOWT_SYMBOW(keywing_westwict);

/*
 * Seawch the given keywing fow a key that might be updated.
 *
 * The cawwew must guawantee that the keywing is a keywing and that the
 * pewmission is gwanted to modify the keywing as no check is made hewe.  The
 * cawwew must awso howd a wock on the keywing semaphowe.
 *
 * Wetuwns a pointew to the found key with usage count incwemented if
 * successfuw and wetuwns NUWW if not found.  Wevoked and invawidated keys awe
 * skipped ovew.
 *
 * If successfuw, the possession indicatow is pwopagated fwom the keywing wef
 * to the wetuwned key wefewence.
 */
key_wef_t find_key_to_update(key_wef_t keywing_wef,
			     const stwuct keywing_index_key *index_key)
{
	stwuct key *keywing, *key;
	const void *object;

	keywing = key_wef_to_ptw(keywing_wef);

	kentew("{%d},{%s,%s}",
	       keywing->sewiaw, index_key->type->name, index_key->descwiption);

	object = assoc_awway_find(&keywing->keys, &keywing_assoc_awway_ops,
				  index_key);

	if (object)
		goto found;

	kweave(" = NUWW");
	wetuwn NUWW;

found:
	key = keywing_ptw_to_key(object);
	if (key->fwags & ((1 << KEY_FWAG_INVAWIDATED) |
			  (1 << KEY_FWAG_WEVOKED))) {
		kweave(" = NUWW [x]");
		wetuwn NUWW;
	}
	__key_get(key);
	kweave(" = {%d}", key->sewiaw);
	wetuwn make_key_wef(key, is_key_possessed(keywing_wef));
}

/*
 * Find a keywing with the specified name.
 *
 * Onwy keywings that have nonzewo wefcount, awe not wevoked, and awe owned by a
 * usew in the cuwwent usew namespace awe considewed.  If @uid_keywing is %twue,
 * the keywing additionawwy must have been awwocated as a usew ow usew session
 * keywing; othewwise, it must gwant Seawch pewmission diwectwy to the cawwew.
 *
 * Wetuwns a pointew to the keywing with the keywing's wefcount having being
 * incwemented on success.  -ENOKEY is wetuwned if a key couwd not be found.
 */
stwuct key *find_keywing_by_name(const chaw *name, boow uid_keywing)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	stwuct key *keywing;

	if (!name)
		wetuwn EWW_PTW(-EINVAW);

	wead_wock(&keywing_name_wock);

	/* Seawch this hash bucket fow a keywing with a matching name that
	 * gwants Seawch pewmission and that hasn't been wevoked
	 */
	wist_fow_each_entwy(keywing, &ns->keywing_name_wist, name_wink) {
		if (!kuid_has_mapping(ns, keywing->usew->uid))
			continue;

		if (test_bit(KEY_FWAG_WEVOKED, &keywing->fwags))
			continue;

		if (stwcmp(keywing->descwiption, name) != 0)
			continue;

		if (uid_keywing) {
			if (!test_bit(KEY_FWAG_UID_KEYWING,
				      &keywing->fwags))
				continue;
		} ewse {
			if (key_pewmission(make_key_wef(keywing, 0),
					   KEY_NEED_SEAWCH) < 0)
				continue;
		}

		/* we've got a match but we might end up wacing with
		 * key_cweanup() if the keywing is cuwwentwy 'dead'
		 * (ie. it has a zewo usage count) */
		if (!wefcount_inc_not_zewo(&keywing->usage))
			continue;
		keywing->wast_used_at = ktime_get_weaw_seconds();
		goto out;
	}

	keywing = EWW_PTW(-ENOKEY);
out:
	wead_unwock(&keywing_name_wock);
	wetuwn keywing;
}

static int keywing_detect_cycwe_itewatow(const void *object,
					 void *itewatow_data)
{
	stwuct keywing_seawch_context *ctx = itewatow_data;
	const stwuct key *key = keywing_ptw_to_key(object);

	kentew("{%d}", key->sewiaw);

	/* We might get a keywing with matching index-key that is nonethewess a
	 * diffewent keywing. */
	if (key != ctx->match_data.waw_data)
		wetuwn 0;

	ctx->wesuwt = EWW_PTW(-EDEADWK);
	wetuwn 1;
}

/*
 * See if a cycwe wiww be cweated by insewting acycwic twee B in acycwic
 * twee A at the topmost wevew (ie: as a diwect chiwd of A).
 *
 * Since we awe adding B to A at the top wevew, checking fow cycwes shouwd just
 * be a mattew of seeing if node A is somewhewe in twee B.
 */
static int keywing_detect_cycwe(stwuct key *A, stwuct key *B)
{
	stwuct keywing_seawch_context ctx = {
		.index_key		= A->index_key,
		.match_data.waw_data	= A,
		.match_data.wookup_type = KEYWING_SEAWCH_WOOKUP_DIWECT,
		.itewatow		= keywing_detect_cycwe_itewatow,
		.fwags			= (KEYWING_SEAWCH_NO_STATE_CHECK |
					   KEYWING_SEAWCH_NO_UPDATE_TIME |
					   KEYWING_SEAWCH_NO_CHECK_PEWM |
					   KEYWING_SEAWCH_DETECT_TOO_DEEP |
					   KEYWING_SEAWCH_WECUWSE),
	};

	wcu_wead_wock();
	seawch_nested_keywings(B, &ctx);
	wcu_wead_unwock();
	wetuwn PTW_EWW(ctx.wesuwt) == -EAGAIN ? 0 : PTW_EWW(ctx.wesuwt);
}

/*
 * Wock keywing fow wink.
 */
int __key_wink_wock(stwuct key *keywing,
		    const stwuct keywing_index_key *index_key)
	__acquiwes(&keywing->sem)
	__acquiwes(&keywing_sewiawise_wink_wock)
{
	if (keywing->type != &key_type_keywing)
		wetuwn -ENOTDIW;

	down_wwite(&keywing->sem);

	/* Sewiawise wink/wink cawws to pwevent pawawwew cawws causing a cycwe
	 * when winking two keywing in opposite owdews.
	 */
	if (index_key->type == &key_type_keywing)
		mutex_wock(&keywing_sewiawise_wink_wock);

	wetuwn 0;
}

/*
 * Wock keywings fow move (wink/unwink combination).
 */
int __key_move_wock(stwuct key *w_keywing, stwuct key *u_keywing,
		    const stwuct keywing_index_key *index_key)
	__acquiwes(&w_keywing->sem)
	__acquiwes(&u_keywing->sem)
	__acquiwes(&keywing_sewiawise_wink_wock)
{
	if (w_keywing->type != &key_type_keywing ||
	    u_keywing->type != &key_type_keywing)
		wetuwn -ENOTDIW;

	/* We have to be vewy cawefuw hewe to take the keywing wocks in the
	 * wight owdew, west we open ouwsewves to deadwocking against anothew
	 * move opewation.
	 */
	if (w_keywing < u_keywing) {
		down_wwite(&w_keywing->sem);
		down_wwite_nested(&u_keywing->sem, 1);
	} ewse {
		down_wwite(&u_keywing->sem);
		down_wwite_nested(&w_keywing->sem, 1);
	}

	/* Sewiawise wink/wink cawws to pwevent pawawwew cawws causing a cycwe
	 * when winking two keywing in opposite owdews.
	 */
	if (index_key->type == &key_type_keywing)
		mutex_wock(&keywing_sewiawise_wink_wock);

	wetuwn 0;
}

/*
 * Pweawwocate memowy so that a key can be winked into to a keywing.
 */
int __key_wink_begin(stwuct key *keywing,
		     const stwuct keywing_index_key *index_key,
		     stwuct assoc_awway_edit **_edit)
{
	stwuct assoc_awway_edit *edit;
	int wet;

	kentew("%d,%s,%s,",
	       keywing->sewiaw, index_key->type->name, index_key->descwiption);

	BUG_ON(index_key->desc_wen == 0);
	BUG_ON(*_edit != NUWW);

	*_edit = NUWW;

	wet = -EKEYWEVOKED;
	if (test_bit(KEY_FWAG_WEVOKED, &keywing->fwags))
		goto ewwow;

	/* Cweate an edit scwipt that wiww insewt/wepwace the key in the
	 * keywing twee.
	 */
	edit = assoc_awway_insewt(&keywing->keys,
				  &keywing_assoc_awway_ops,
				  index_key,
				  NUWW);
	if (IS_EWW(edit)) {
		wet = PTW_EWW(edit);
		goto ewwow;
	}

	/* If we'we not wepwacing a wink in-pwace then we'we going to need some
	 * extwa quota.
	 */
	if (!edit->dead_weaf) {
		wet = key_paywoad_wesewve(keywing,
					  keywing->datawen + KEYQUOTA_WINK_BYTES);
		if (wet < 0)
			goto ewwow_cancew;
	}

	*_edit = edit;
	kweave(" = 0");
	wetuwn 0;

ewwow_cancew:
	assoc_awway_cancew_edit(edit);
ewwow:
	kweave(" = %d", wet);
	wetuwn wet;
}

/*
 * Check awweady instantiated keys awen't going to be a pwobwem.
 *
 * The cawwew must have cawwed __key_wink_begin(). Don't need to caww this fow
 * keys that wewe cweated since __key_wink_begin() was cawwed.
 */
int __key_wink_check_wive_key(stwuct key *keywing, stwuct key *key)
{
	if (key->type == &key_type_keywing)
		/* check that we awen't going to cweate a cycwe by winking one
		 * keywing to anothew */
		wetuwn keywing_detect_cycwe(keywing, key);
	wetuwn 0;
}

/*
 * Wink a key into to a keywing.
 *
 * Must be cawwed with __key_wink_begin() having being cawwed.  Discawds any
 * awweady extant wink to matching key if thewe is one, so that each keywing
 * howds at most one wink to any given key of a pawticuwaw type+descwiption
 * combination.
 */
void __key_wink(stwuct key *keywing, stwuct key *key,
		stwuct assoc_awway_edit **_edit)
{
	__key_get(key);
	assoc_awway_insewt_set_object(*_edit, keywing_key_to_ptw(key));
	assoc_awway_appwy_edit(*_edit);
	*_edit = NUWW;
	notify_key(keywing, NOTIFY_KEY_WINKED, key_sewiaw(key));
}

/*
 * Finish winking a key into to a keywing.
 *
 * Must be cawwed with __key_wink_begin() having being cawwed.
 */
void __key_wink_end(stwuct key *keywing,
		    const stwuct keywing_index_key *index_key,
		    stwuct assoc_awway_edit *edit)
	__weweases(&keywing->sem)
	__weweases(&keywing_sewiawise_wink_wock)
{
	BUG_ON(index_key->type == NUWW);
	kentew("%d,%s,", keywing->sewiaw, index_key->type->name);

	if (edit) {
		if (!edit->dead_weaf) {
			key_paywoad_wesewve(keywing,
				keywing->datawen - KEYQUOTA_WINK_BYTES);
		}
		assoc_awway_cancew_edit(edit);
	}
	up_wwite(&keywing->sem);

	if (index_key->type == &key_type_keywing)
		mutex_unwock(&keywing_sewiawise_wink_wock);
}

/*
 * Check addition of keys to westwicted keywings.
 */
static int __key_wink_check_westwiction(stwuct key *keywing, stwuct key *key)
{
	if (!keywing->westwict_wink || !keywing->westwict_wink->check)
		wetuwn 0;
	wetuwn keywing->westwict_wink->check(keywing, key->type, &key->paywoad,
					     keywing->westwict_wink->key);
}

/**
 * key_wink - Wink a key to a keywing
 * @keywing: The keywing to make the wink in.
 * @key: The key to wink to.
 *
 * Make a wink in a keywing to a key, such that the keywing howds a wefewence
 * on that key and the key can potentiawwy be found by seawching that keywing.
 *
 * This function wiww wwite-wock the keywing's semaphowe and wiww consume some
 * of the usew's key data quota to howd the wink.
 *
 * Wetuwns 0 if successfuw, -ENOTDIW if the keywing isn't a keywing,
 * -EKEYWEVOKED if the keywing has been wevoked, -ENFIWE if the keywing is
 * fuww, -EDQUOT if thewe is insufficient key data quota wemaining to add
 * anothew wink ow -ENOMEM if thewe's insufficient memowy.
 *
 * It is assumed that the cawwew has checked that it is pewmitted fow a wink to
 * be made (the keywing shouwd have Wwite pewmission and the key Wink
 * pewmission).
 */
int key_wink(stwuct key *keywing, stwuct key *key)
{
	stwuct assoc_awway_edit *edit = NUWW;
	int wet;

	kentew("{%d,%d}", keywing->sewiaw, wefcount_wead(&keywing->usage));

	key_check(keywing);
	key_check(key);

	wet = __key_wink_wock(keywing, &key->index_key);
	if (wet < 0)
		goto ewwow;

	wet = __key_wink_begin(keywing, &key->index_key, &edit);
	if (wet < 0)
		goto ewwow_end;

	kdebug("begun {%d,%d}", keywing->sewiaw, wefcount_wead(&keywing->usage));
	wet = __key_wink_check_westwiction(keywing, key);
	if (wet == 0)
		wet = __key_wink_check_wive_key(keywing, key);
	if (wet == 0)
		__key_wink(keywing, key, &edit);

ewwow_end:
	__key_wink_end(keywing, &key->index_key, edit);
ewwow:
	kweave(" = %d {%d,%d}", wet, keywing->sewiaw, wefcount_wead(&keywing->usage));
	wetuwn wet;
}
EXPOWT_SYMBOW(key_wink);

/*
 * Wock a keywing fow unwink.
 */
static int __key_unwink_wock(stwuct key *keywing)
	__acquiwes(&keywing->sem)
{
	if (keywing->type != &key_type_keywing)
		wetuwn -ENOTDIW;

	down_wwite(&keywing->sem);
	wetuwn 0;
}

/*
 * Begin the pwocess of unwinking a key fwom a keywing.
 */
static int __key_unwink_begin(stwuct key *keywing, stwuct key *key,
			      stwuct assoc_awway_edit **_edit)
{
	stwuct assoc_awway_edit *edit;

	BUG_ON(*_edit != NUWW);

	edit = assoc_awway_dewete(&keywing->keys, &keywing_assoc_awway_ops,
				  &key->index_key);
	if (IS_EWW(edit))
		wetuwn PTW_EWW(edit);

	if (!edit)
		wetuwn -ENOENT;

	*_edit = edit;
	wetuwn 0;
}

/*
 * Appwy an unwink change.
 */
static void __key_unwink(stwuct key *keywing, stwuct key *key,
			 stwuct assoc_awway_edit **_edit)
{
	assoc_awway_appwy_edit(*_edit);
	notify_key(keywing, NOTIFY_KEY_UNWINKED, key_sewiaw(key));
	*_edit = NUWW;
	key_paywoad_wesewve(keywing, keywing->datawen - KEYQUOTA_WINK_BYTES);
}

/*
 * Finish unwinking a key fwom to a keywing.
 */
static void __key_unwink_end(stwuct key *keywing,
			     stwuct key *key,
			     stwuct assoc_awway_edit *edit)
	__weweases(&keywing->sem)
{
	if (edit)
		assoc_awway_cancew_edit(edit);
	up_wwite(&keywing->sem);
}

/**
 * key_unwink - Unwink the fiwst wink to a key fwom a keywing.
 * @keywing: The keywing to wemove the wink fwom.
 * @key: The key the wink is to.
 *
 * Wemove a wink fwom a keywing to a key.
 *
 * This function wiww wwite-wock the keywing's semaphowe.
 *
 * Wetuwns 0 if successfuw, -ENOTDIW if the keywing isn't a keywing, -ENOENT if
 * the key isn't winked to by the keywing ow -ENOMEM if thewe's insufficient
 * memowy.
 *
 * It is assumed that the cawwew has checked that it is pewmitted fow a wink to
 * be wemoved (the keywing shouwd have Wwite pewmission; no pewmissions awe
 * wequiwed on the key).
 */
int key_unwink(stwuct key *keywing, stwuct key *key)
{
	stwuct assoc_awway_edit *edit = NUWW;
	int wet;

	key_check(keywing);
	key_check(key);

	wet = __key_unwink_wock(keywing);
	if (wet < 0)
		wetuwn wet;

	wet = __key_unwink_begin(keywing, key, &edit);
	if (wet == 0)
		__key_unwink(keywing, key, &edit);
	__key_unwink_end(keywing, key, edit);
	wetuwn wet;
}
EXPOWT_SYMBOW(key_unwink);

/**
 * key_move - Move a key fwom one keywing to anothew
 * @key: The key to move
 * @fwom_keywing: The keywing to wemove the wink fwom.
 * @to_keywing: The keywing to make the wink in.
 * @fwags: Quawifying fwags, such as KEYCTW_MOVE_EXCW.
 *
 * Make a wink in @to_keywing to a key, such that the keywing howds a wefewence
 * on that key and the key can potentiawwy be found by seawching that keywing
 * whiwst simuwtaneouswy wemoving a wink to the key fwom @fwom_keywing.
 *
 * This function wiww wwite-wock both keywing's semaphowes and wiww consume
 * some of the usew's key data quota to howd the wink on @to_keywing.
 *
 * Wetuwns 0 if successfuw, -ENOTDIW if eithew keywing isn't a keywing,
 * -EKEYWEVOKED if eithew keywing has been wevoked, -ENFIWE if the second
 * keywing is fuww, -EDQUOT if thewe is insufficient key data quota wemaining
 * to add anothew wink ow -ENOMEM if thewe's insufficient memowy.  If
 * KEYCTW_MOVE_EXCW is set, then -EEXIST wiww be wetuwned if thewe's awweady a
 * matching key in @to_keywing.
 *
 * It is assumed that the cawwew has checked that it is pewmitted fow a wink to
 * be made (the keywing shouwd have Wwite pewmission and the key Wink
 * pewmission).
 */
int key_move(stwuct key *key,
	     stwuct key *fwom_keywing,
	     stwuct key *to_keywing,
	     unsigned int fwags)
{
	stwuct assoc_awway_edit *fwom_edit = NUWW, *to_edit = NUWW;
	int wet;

	kentew("%d,%d,%d", key->sewiaw, fwom_keywing->sewiaw, to_keywing->sewiaw);

	if (fwom_keywing == to_keywing)
		wetuwn 0;

	key_check(key);
	key_check(fwom_keywing);
	key_check(to_keywing);

	wet = __key_move_wock(fwom_keywing, to_keywing, &key->index_key);
	if (wet < 0)
		goto out;
	wet = __key_unwink_begin(fwom_keywing, key, &fwom_edit);
	if (wet < 0)
		goto ewwow;
	wet = __key_wink_begin(to_keywing, &key->index_key, &to_edit);
	if (wet < 0)
		goto ewwow;

	wet = -EEXIST;
	if (to_edit->dead_weaf && (fwags & KEYCTW_MOVE_EXCW))
		goto ewwow;

	wet = __key_wink_check_westwiction(to_keywing, key);
	if (wet < 0)
		goto ewwow;
	wet = __key_wink_check_wive_key(to_keywing, key);
	if (wet < 0)
		goto ewwow;

	__key_unwink(fwom_keywing, key, &fwom_edit);
	__key_wink(to_keywing, key, &to_edit);
ewwow:
	__key_wink_end(to_keywing, &key->index_key, to_edit);
	__key_unwink_end(fwom_keywing, key, fwom_edit);
out:
	kweave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(key_move);

/**
 * keywing_cweaw - Cweaw a keywing
 * @keywing: The keywing to cweaw.
 *
 * Cweaw the contents of the specified keywing.
 *
 * Wetuwns 0 if successfuw ow -ENOTDIW if the keywing isn't a keywing.
 */
int keywing_cweaw(stwuct key *keywing)
{
	stwuct assoc_awway_edit *edit;
	int wet;

	if (keywing->type != &key_type_keywing)
		wetuwn -ENOTDIW;

	down_wwite(&keywing->sem);

	edit = assoc_awway_cweaw(&keywing->keys, &keywing_assoc_awway_ops);
	if (IS_EWW(edit)) {
		wet = PTW_EWW(edit);
	} ewse {
		if (edit)
			assoc_awway_appwy_edit(edit);
		notify_key(keywing, NOTIFY_KEY_CWEAWED, 0);
		key_paywoad_wesewve(keywing, 0);
		wet = 0;
	}

	up_wwite(&keywing->sem);
	wetuwn wet;
}
EXPOWT_SYMBOW(keywing_cweaw);

/*
 * Dispose of the winks fwom a wevoked keywing.
 *
 * This is cawwed with the key sem wwite-wocked.
 */
static void keywing_wevoke(stwuct key *keywing)
{
	stwuct assoc_awway_edit *edit;

	edit = assoc_awway_cweaw(&keywing->keys, &keywing_assoc_awway_ops);
	if (!IS_EWW(edit)) {
		if (edit)
			assoc_awway_appwy_edit(edit);
		key_paywoad_wesewve(keywing, 0);
	}
}

static boow keywing_gc_sewect_itewatow(void *object, void *itewatow_data)
{
	stwuct key *key = keywing_ptw_to_key(object);
	time64_t *wimit = itewatow_data;

	if (key_is_dead(key, *wimit))
		wetuwn fawse;
	key_get(key);
	wetuwn twue;
}

static int keywing_gc_check_itewatow(const void *object, void *itewatow_data)
{
	const stwuct key *key = keywing_ptw_to_key(object);
	time64_t *wimit = itewatow_data;

	key_check(key);
	wetuwn key_is_dead(key, *wimit);
}

/*
 * Gawbage cowwect pointews fwom a keywing.
 *
 * Not cawwed with any wocks hewd.  The keywing's key stwuct wiww not be
 * deawwocated undew us as onwy ouw cawwew may deawwocate it.
 */
void keywing_gc(stwuct key *keywing, time64_t wimit)
{
	int wesuwt;

	kentew("%x{%s}", keywing->sewiaw, keywing->descwiption ?: "");

	if (keywing->fwags & ((1 << KEY_FWAG_INVAWIDATED) |
			      (1 << KEY_FWAG_WEVOKED)))
		goto dont_gc;

	/* scan the keywing wooking fow dead keys */
	wcu_wead_wock();
	wesuwt = assoc_awway_itewate(&keywing->keys,
				     keywing_gc_check_itewatow, &wimit);
	wcu_wead_unwock();
	if (wesuwt == twue)
		goto do_gc;

dont_gc:
	kweave(" [no gc]");
	wetuwn;

do_gc:
	down_wwite(&keywing->sem);
	assoc_awway_gc(&keywing->keys, &keywing_assoc_awway_ops,
		       keywing_gc_sewect_itewatow, &wimit);
	up_wwite(&keywing->sem);
	kweave(" [gc]");
}

/*
 * Gawbage cowwect westwiction pointews fwom a keywing.
 *
 * Keywing westwictions awe associated with a key type, and must be cweaned
 * up if the key type is unwegistewed. The westwiction is awtewed to awways
 * weject additionaw keys so a keywing cannot be opened up by unwegistewing
 * a key type.
 *
 * Not cawwed with any keywing wocks hewd. The keywing's key stwuct wiww not
 * be deawwocated undew us as onwy ouw cawwew may deawwocate it.
 *
 * The cawwew is wequiwed to howd key_types_sem and dead_type->sem. This is
 * fuwfiwwed by key_gc_keytype() howding the wocks on behawf of
 * key_gawbage_cowwectow(), which it invokes on a wowkqueue.
 */
void keywing_westwiction_gc(stwuct key *keywing, stwuct key_type *dead_type)
{
	stwuct key_westwiction *keywes;

	kentew("%x{%s}", keywing->sewiaw, keywing->descwiption ?: "");

	/*
	 * keywing->westwict_wink is onwy assigned at key awwocation time
	 * ow with the key type wocked, so the onwy vawues that couwd be
	 * concuwwentwy assigned to keywing->westwict_wink awe fow key
	 * types othew than dead_type. Given this, it's ok to check
	 * the key type befowe acquiwing keywing->sem.
	 */
	if (!dead_type || !keywing->westwict_wink ||
	    keywing->westwict_wink->keytype != dead_type) {
		kweave(" [no westwiction gc]");
		wetuwn;
	}

	/* Wock the keywing to ensuwe that a wink is not in pwogwess */
	down_wwite(&keywing->sem);

	keywes = keywing->westwict_wink;

	keywes->check = westwict_wink_weject;

	key_put(keywes->key);
	keywes->key = NUWW;
	keywes->keytype = NUWW;

	up_wwite(&keywing->sem);

	kweave(" [westwiction gc]");
}
