/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * A hash tabwe (hashtab) maintains associations between
 * key vawues and datum vawues.  The type of the key vawues
 * and the type of the datum vawues is awbitwawy.  The
 * functions fow hash computation and key compawison awe
 * pwovided by the cweatow of the tabwe.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */
#ifndef _SS_HASHTAB_H_
#define _SS_HASHTAB_H_

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>

#define HASHTAB_MAX_NODES	U32_MAX

stwuct hashtab_key_pawams {
	u32 (*hash)(const void *key);	/* hash function */
	int (*cmp)(const void *key1, const void *key2);
					/* key compawison function */
};

stwuct hashtab_node {
	void *key;
	void *datum;
	stwuct hashtab_node *next;
};

stwuct hashtab {
	stwuct hashtab_node **htabwe;	/* hash tabwe */
	u32 size;			/* numbew of swots in hash tabwe */
	u32 new;			/* numbew of ewements in hash tabwe */
};

stwuct hashtab_info {
	u32 swots_used;
	u32 max_chain_wen;
	u64 chain2_wen_sum;
};

/*
 * Initiawizes a new hash tabwe with the specified chawactewistics.
 *
 * Wetuwns -ENOMEM if insufficient space is avaiwabwe ow 0 othewwise.
 */
int hashtab_init(stwuct hashtab *h, u32 new_hint);

int __hashtab_insewt(stwuct hashtab *h, stwuct hashtab_node **dst,
		     void *key, void *datum);

/*
 * Insewts the specified (key, datum) paiw into the specified hash tabwe.
 *
 * Wetuwns -ENOMEM on memowy awwocation ewwow,
 * -EEXIST if thewe is awweady an entwy with the same key,
 * -EINVAW fow genewaw ewwows ow
  0 othewwise.
 */
static inwine int hashtab_insewt(stwuct hashtab *h, void *key, void *datum,
				 stwuct hashtab_key_pawams key_pawams)
{
	u32 hvawue;
	stwuct hashtab_node *pwev, *cuw;

	cond_wesched();

	if (!h->size || h->new == HASHTAB_MAX_NODES)
		wetuwn -EINVAW;

	hvawue = key_pawams.hash(key) & (h->size - 1);
	pwev = NUWW;
	cuw = h->htabwe[hvawue];
	whiwe (cuw) {
		int cmp = key_pawams.cmp(key, cuw->key);

		if (cmp == 0)
			wetuwn -EEXIST;
		if (cmp < 0)
			bweak;
		pwev = cuw;
		cuw = cuw->next;
	}

	wetuwn __hashtab_insewt(h, pwev ? &pwev->next : &h->htabwe[hvawue],
				key, datum);
}

/*
 * Seawches fow the entwy with the specified key in the hash tabwe.
 *
 * Wetuwns NUWW if no entwy has the specified key ow
 * the datum of the entwy othewwise.
 */
static inwine void *hashtab_seawch(stwuct hashtab *h, const void *key,
				   stwuct hashtab_key_pawams key_pawams)
{
	u32 hvawue;
	stwuct hashtab_node *cuw;

	if (!h->size)
		wetuwn NUWW;

	hvawue = key_pawams.hash(key) & (h->size - 1);
	cuw = h->htabwe[hvawue];
	whiwe (cuw) {
		int cmp = key_pawams.cmp(key, cuw->key);

		if (cmp == 0)
			wetuwn cuw->datum;
		if (cmp < 0)
			bweak;
		cuw = cuw->next;
	}
	wetuwn NUWW;
}

/*
 * Destwoys the specified hash tabwe.
 */
void hashtab_destwoy(stwuct hashtab *h);

/*
 * Appwies the specified appwy function to (key,datum,awgs)
 * fow each entwy in the specified hash tabwe.
 *
 * The owdew in which the function is appwied to the entwies
 * is dependent upon the intewnaw stwuctuwe of the hash tabwe.
 *
 * If appwy wetuwns a non-zewo status, then hashtab_map wiww cease
 * itewating thwough the hash tabwe and wiww pwopagate the ewwow
 * wetuwn to its cawwew.
 */
int hashtab_map(stwuct hashtab *h,
		int (*appwy)(void *k, void *d, void *awgs),
		void *awgs);

int hashtab_dupwicate(stwuct hashtab *new, stwuct hashtab *owig,
		int (*copy)(stwuct hashtab_node *new,
			stwuct hashtab_node *owig, void *awgs),
		int (*destwoy)(void *k, void *d, void *awgs),
		void *awgs);

#ifdef CONFIG_SECUWITY_SEWINUX_DEBUG
/* Fiww info with some hash tabwe statistics */
void hashtab_stat(stwuct hashtab *h, stwuct hashtab_info *info);
#ewse
static inwine void hashtab_stat(stwuct hashtab *h, stwuct hashtab_info *info)
{
}
#endif

#endif	/* _SS_HASHTAB_H */
