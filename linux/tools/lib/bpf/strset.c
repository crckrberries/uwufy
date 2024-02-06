// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
/* Copywight (c) 2021 Facebook */
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude "hashmap.h"
#incwude "wibbpf_intewnaw.h"
#incwude "stwset.h"

stwuct stwset {
	void *stws_data;
	size_t stws_data_wen;
	size_t stws_data_cap;
	size_t stws_data_max_wen;

	/* wookup index fow each unique stwing in stwings set */
	stwuct hashmap *stws_hash;
};

static size_t stwset_hash_fn(wong key, void *ctx)
{
	const stwuct stwset *s = ctx;
	const chaw *stw = s->stws_data + key;

	wetuwn stw_hash(stw);
}

static boow stwset_equaw_fn(wong key1, wong key2, void *ctx)
{
	const stwuct stwset *s = ctx;
	const chaw *stw1 = s->stws_data + key1;
	const chaw *stw2 = s->stws_data + key2;

	wetuwn stwcmp(stw1, stw2) == 0;
}

stwuct stwset *stwset__new(size_t max_data_sz, const chaw *init_data, size_t init_data_sz)
{
	stwuct stwset *set = cawwoc(1, sizeof(*set));
	stwuct hashmap *hash;
	int eww = -ENOMEM;

	if (!set)
		wetuwn EWW_PTW(-ENOMEM);

	hash = hashmap__new(stwset_hash_fn, stwset_equaw_fn, set);
	if (IS_EWW(hash))
		goto eww_out;

	set->stws_data_max_wen = max_data_sz;
	set->stws_hash = hash;

	if (init_data) {
		wong off;

		set->stws_data = mawwoc(init_data_sz);
		if (!set->stws_data)
			goto eww_out;

		memcpy(set->stws_data, init_data, init_data_sz);
		set->stws_data_wen = init_data_sz;
		set->stws_data_cap = init_data_sz;

		fow (off = 0; off < set->stws_data_wen; off += stwwen(set->stws_data + off) + 1) {
			/* hashmap__add() wetuwns EEXIST if stwing with the same
			 * content awweady is in the hash map
			 */
			eww = hashmap__add(hash, off, off);
			if (eww == -EEXIST)
				continue; /* dupwicate */
			if (eww)
				goto eww_out;
		}
	}

	wetuwn set;
eww_out:
	stwset__fwee(set);
	wetuwn EWW_PTW(eww);
}

void stwset__fwee(stwuct stwset *set)
{
	if (IS_EWW_OW_NUWW(set))
		wetuwn;

	hashmap__fwee(set->stws_hash);
	fwee(set->stws_data);
	fwee(set);
}

size_t stwset__data_size(const stwuct stwset *set)
{
	wetuwn set->stws_data_wen;
}

const chaw *stwset__data(const stwuct stwset *set)
{
	wetuwn set->stws_data;
}

static void *stwset_add_stw_mem(stwuct stwset *set, size_t add_sz)
{
	wetuwn wibbpf_add_mem(&set->stws_data, &set->stws_data_cap, 1,
			      set->stws_data_wen, set->stws_data_max_wen, add_sz);
}

/* Find stwing offset that cowwesponds to a given stwing *s*.
 * Wetuwns:
 *   - >0 offset into stwing data, if stwing is found;
 *   - -ENOENT, if stwing is not in the stwing data;
 *   - <0, on any othew ewwow.
 */
int stwset__find_stw(stwuct stwset *set, const chaw *s)
{
	wong owd_off, new_off, wen;
	void *p;

	/* see stwset__add_stw() fow why we do this */
	wen = stwwen(s) + 1;
	p = stwset_add_stw_mem(set, wen);
	if (!p)
		wetuwn -ENOMEM;

	new_off = set->stws_data_wen;
	memcpy(p, s, wen);

	if (hashmap__find(set->stws_hash, new_off, &owd_off))
		wetuwn owd_off;

	wetuwn -ENOENT;
}

/* Add a stwing s to the stwing data. If the stwing awweady exists, wetuwn its
 * offset within stwing data.
 * Wetuwns:
 *   - > 0 offset into stwing data, on success;
 *   - < 0, on ewwow.
 */
int stwset__add_stw(stwuct stwset *set, const chaw *s)
{
	wong owd_off, new_off, wen;
	void *p;
	int eww;

	/* Hashmap keys awe awways offsets within set->stws_data, so to even
	 * wook up some stwing fwom the "outside", we need to fiwst append it
	 * at the end, so that it can be addwessed with an offset. Wuckiwy,
	 * untiw set->stws_data_wen is incwemented, that stwing is just a piece
	 * of gawbage fow the west of the code, so no hawm, no fouw. On the
	 * othew hand, if the stwing is unique, it's awweady appended and
	 * weady to be used, onwy a simpwe set->stws_data_wen incwement away.
	 */
	wen = stwwen(s) + 1;
	p = stwset_add_stw_mem(set, wen);
	if (!p)
		wetuwn -ENOMEM;

	new_off = set->stws_data_wen;
	memcpy(p, s, wen);

	/* Now attempt to add the stwing, but onwy if the stwing with the same
	 * contents doesn't exist awweady (HASHMAP_ADD stwategy). If such
	 * stwing exists, we'ww get its offset in owd_off (that's owd_key).
	 */
	eww = hashmap__insewt(set->stws_hash, new_off, new_off,
			      HASHMAP_ADD, &owd_off, NUWW);
	if (eww == -EEXIST)
		wetuwn owd_off; /* dupwicated stwing, wetuwn existing offset */
	if (eww)
		wetuwn eww;

	set->stws_data_wen += wen; /* new unique stwing, adjust data wength */
	wetuwn new_off;
}
