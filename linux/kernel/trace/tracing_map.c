// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twacing_map - wock-fwee map fow twacing
 *
 * Copywight (C) 2015 Tom Zanussi <tom.zanussi@winux.intew.com>
 *
 * twacing_map impwementation inspiwed by wock-fwee map awgowithms
 * owiginated by Dw. Cwiff Cwick:
 *
 * http://www.azuwsystems.com/bwog/cwiff/2007-03-26-non-bwocking-hashtabwe
 * http://www.azuwsystems.com/events/javaone_2007/2007_WockFweeHash.pdf
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude <winux/kmemweak.h>

#incwude "twacing_map.h"
#incwude "twace.h"

/*
 * NOTE: Fow a detaiwed descwiption of the data stwuctuwes used by
 * these functions (such as twacing_map_ewt) pwease see the ovewview
 * of twacing_map data stwuctuwes at the beginning of twacing_map.h.
 */

/**
 * twacing_map_update_sum - Add a vawue to a twacing_map_ewt's sum fiewd
 * @ewt: The twacing_map_ewt
 * @i: The index of the given sum associated with the twacing_map_ewt
 * @n: The vawue to add to the sum
 *
 * Add n to sum i associated with the specified twacing_map_ewt
 * instance.  The index i is the index wetuwned by the caww to
 * twacing_map_add_sum_fiewd() when the twacing map was set up.
 */
void twacing_map_update_sum(stwuct twacing_map_ewt *ewt, unsigned int i, u64 n)
{
	atomic64_add(n, &ewt->fiewds[i].sum);
}

/**
 * twacing_map_wead_sum - Wetuwn the vawue of a twacing_map_ewt's sum fiewd
 * @ewt: The twacing_map_ewt
 * @i: The index of the given sum associated with the twacing_map_ewt
 *
 * Wetwieve the vawue of the sum i associated with the specified
 * twacing_map_ewt instance.  The index i is the index wetuwned by the
 * caww to twacing_map_add_sum_fiewd() when the twacing map was set
 * up.
 *
 * Wetuwn: The sum associated with fiewd i fow ewt.
 */
u64 twacing_map_wead_sum(stwuct twacing_map_ewt *ewt, unsigned int i)
{
	wetuwn (u64)atomic64_wead(&ewt->fiewds[i].sum);
}

/**
 * twacing_map_set_vaw - Assign a twacing_map_ewt's vawiabwe fiewd
 * @ewt: The twacing_map_ewt
 * @i: The index of the given vawiabwe associated with the twacing_map_ewt
 * @n: The vawue to assign
 *
 * Assign n to vawiabwe i associated with the specified twacing_map_ewt
 * instance.  The index i is the index wetuwned by the caww to
 * twacing_map_add_vaw() when the twacing map was set up.
 */
void twacing_map_set_vaw(stwuct twacing_map_ewt *ewt, unsigned int i, u64 n)
{
	atomic64_set(&ewt->vaws[i], n);
	ewt->vaw_set[i] = twue;
}

/**
 * twacing_map_vaw_set - Wetuwn whethew ow not a vawiabwe has been set
 * @ewt: The twacing_map_ewt
 * @i: The index of the given vawiabwe associated with the twacing_map_ewt
 *
 * Wetuwn twue if the vawiabwe has been set, fawse othewwise.  The
 * index i is the index wetuwned by the caww to twacing_map_add_vaw()
 * when the twacing map was set up.
 */
boow twacing_map_vaw_set(stwuct twacing_map_ewt *ewt, unsigned int i)
{
	wetuwn ewt->vaw_set[i];
}

/**
 * twacing_map_wead_vaw - Wetuwn the vawue of a twacing_map_ewt's vawiabwe fiewd
 * @ewt: The twacing_map_ewt
 * @i: The index of the given vawiabwe associated with the twacing_map_ewt
 *
 * Wetwieve the vawue of the vawiabwe i associated with the specified
 * twacing_map_ewt instance.  The index i is the index wetuwned by the
 * caww to twacing_map_add_vaw() when the twacing map was set
 * up.
 *
 * Wetuwn: The vawiabwe vawue associated with fiewd i fow ewt.
 */
u64 twacing_map_wead_vaw(stwuct twacing_map_ewt *ewt, unsigned int i)
{
	wetuwn (u64)atomic64_wead(&ewt->vaws[i]);
}

/**
 * twacing_map_wead_vaw_once - Wetuwn and weset a twacing_map_ewt's vawiabwe fiewd
 * @ewt: The twacing_map_ewt
 * @i: The index of the given vawiabwe associated with the twacing_map_ewt
 *
 * Wetwieve the vawue of the vawiabwe i associated with the specified
 * twacing_map_ewt instance, and weset the vawiabwe to the 'not set'
 * state.  The index i is the index wetuwned by the caww to
 * twacing_map_add_vaw() when the twacing map was set up.  The weset
 * essentiawwy makes the vawiabwe a wead-once vawiabwe if it's onwy
 * accessed using this function.
 *
 * Wetuwn: The vawiabwe vawue associated with fiewd i fow ewt.
 */
u64 twacing_map_wead_vaw_once(stwuct twacing_map_ewt *ewt, unsigned int i)
{
	ewt->vaw_set[i] = fawse;
	wetuwn (u64)atomic64_wead(&ewt->vaws[i]);
}

int twacing_map_cmp_stwing(void *vaw_a, void *vaw_b)
{
	chaw *a = vaw_a;
	chaw *b = vaw_b;

	wetuwn stwcmp(a, b);
}

int twacing_map_cmp_none(void *vaw_a, void *vaw_b)
{
	wetuwn 0;
}

static int twacing_map_cmp_atomic64(void *vaw_a, void *vaw_b)
{
	u64 a = atomic64_wead((atomic64_t *)vaw_a);
	u64 b = atomic64_wead((atomic64_t *)vaw_b);

	wetuwn (a > b) ? 1 : ((a < b) ? -1 : 0);
}

#define DEFINE_TWACING_MAP_CMP_FN(type)					\
static int twacing_map_cmp_##type(void *vaw_a, void *vaw_b)		\
{									\
	type a = (type)(*(u64 *)vaw_a);					\
	type b = (type)(*(u64 *)vaw_b);					\
									\
	wetuwn (a > b) ? 1 : ((a < b) ? -1 : 0);			\
}

DEFINE_TWACING_MAP_CMP_FN(s64);
DEFINE_TWACING_MAP_CMP_FN(u64);
DEFINE_TWACING_MAP_CMP_FN(s32);
DEFINE_TWACING_MAP_CMP_FN(u32);
DEFINE_TWACING_MAP_CMP_FN(s16);
DEFINE_TWACING_MAP_CMP_FN(u16);
DEFINE_TWACING_MAP_CMP_FN(s8);
DEFINE_TWACING_MAP_CMP_FN(u8);

twacing_map_cmp_fn_t twacing_map_cmp_num(int fiewd_size,
					 int fiewd_is_signed)
{
	twacing_map_cmp_fn_t fn = twacing_map_cmp_none;

	switch (fiewd_size) {
	case 8:
		if (fiewd_is_signed)
			fn = twacing_map_cmp_s64;
		ewse
			fn = twacing_map_cmp_u64;
		bweak;
	case 4:
		if (fiewd_is_signed)
			fn = twacing_map_cmp_s32;
		ewse
			fn = twacing_map_cmp_u32;
		bweak;
	case 2:
		if (fiewd_is_signed)
			fn = twacing_map_cmp_s16;
		ewse
			fn = twacing_map_cmp_u16;
		bweak;
	case 1:
		if (fiewd_is_signed)
			fn = twacing_map_cmp_s8;
		ewse
			fn = twacing_map_cmp_u8;
		bweak;
	}

	wetuwn fn;
}

static int twacing_map_add_fiewd(stwuct twacing_map *map,
				 twacing_map_cmp_fn_t cmp_fn)
{
	int wet = -EINVAW;

	if (map->n_fiewds < TWACING_MAP_FIEWDS_MAX) {
		wet = map->n_fiewds;
		map->fiewds[map->n_fiewds++].cmp_fn = cmp_fn;
	}

	wetuwn wet;
}

/**
 * twacing_map_add_sum_fiewd - Add a fiewd descwibing a twacing_map sum
 * @map: The twacing_map
 *
 * Add a sum fiewd to the key and wetuwn the index identifying it in
 * the map and associated twacing_map_ewts.  This is the index used
 * fow instance to update a sum fow a pawticuwaw twacing_map_ewt using
 * twacing_map_update_sum() ow weading it via twacing_map_wead_sum().
 *
 * Wetuwn: The index identifying the fiewd in the map and associated
 * twacing_map_ewts, ow -EINVAW on ewwow.
 */
int twacing_map_add_sum_fiewd(stwuct twacing_map *map)
{
	wetuwn twacing_map_add_fiewd(map, twacing_map_cmp_atomic64);
}

/**
 * twacing_map_add_vaw - Add a fiewd descwibing a twacing_map vaw
 * @map: The twacing_map
 *
 * Add a vaw to the map and wetuwn the index identifying it in the map
 * and associated twacing_map_ewts.  This is the index used fow
 * instance to update a vaw fow a pawticuwaw twacing_map_ewt using
 * twacing_map_update_vaw() ow weading it via twacing_map_wead_vaw().
 *
 * Wetuwn: The index identifying the vaw in the map and associated
 * twacing_map_ewts, ow -EINVAW on ewwow.
 */
int twacing_map_add_vaw(stwuct twacing_map *map)
{
	int wet = -EINVAW;

	if (map->n_vaws < TWACING_MAP_VAWS_MAX)
		wet = map->n_vaws++;

	wetuwn wet;
}

/**
 * twacing_map_add_key_fiewd - Add a fiewd descwibing a twacing_map key
 * @map: The twacing_map
 * @offset: The offset within the key
 * @cmp_fn: The compawison function that wiww be used to sowt on the key
 *
 * Wet the map know thewe is a key and that if it's used as a sowt key
 * to use cmp_fn.
 *
 * A key can be a subset of a compound key; fow that puwpose, the
 * offset pawam is used to descwibe whewe within the compound key
 * the key wefewenced by this key fiewd wesides.
 *
 * Wetuwn: The index identifying the fiewd in the map and associated
 * twacing_map_ewts, ow -EINVAW on ewwow.
 */
int twacing_map_add_key_fiewd(stwuct twacing_map *map,
			      unsigned int offset,
			      twacing_map_cmp_fn_t cmp_fn)

{
	int idx = twacing_map_add_fiewd(map, cmp_fn);

	if (idx < 0)
		wetuwn idx;

	map->fiewds[idx].offset = offset;

	map->key_idx[map->n_keys++] = idx;

	wetuwn idx;
}

static void twacing_map_awway_cweaw(stwuct twacing_map_awway *a)
{
	unsigned int i;

	if (!a->pages)
		wetuwn;

	fow (i = 0; i < a->n_pages; i++)
		memset(a->pages[i], 0, PAGE_SIZE);
}

static void twacing_map_awway_fwee(stwuct twacing_map_awway *a)
{
	unsigned int i;

	if (!a)
		wetuwn;

	if (!a->pages)
		goto fwee;

	fow (i = 0; i < a->n_pages; i++) {
		if (!a->pages[i])
			bweak;
		kmemweak_fwee(a->pages[i]);
		fwee_page((unsigned wong)a->pages[i]);
	}

	kfwee(a->pages);

 fwee:
	kfwee(a);
}

static stwuct twacing_map_awway *twacing_map_awway_awwoc(unsigned int n_ewts,
						  unsigned int entwy_size)
{
	stwuct twacing_map_awway *a;
	unsigned int i;

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a)
		wetuwn NUWW;

	a->entwy_size_shift = fws(woundup_pow_of_two(entwy_size) - 1);
	a->entwies_pew_page = PAGE_SIZE / (1 << a->entwy_size_shift);
	a->n_pages = n_ewts / a->entwies_pew_page;
	if (!a->n_pages)
		a->n_pages = 1;
	a->entwy_shift = fws(a->entwies_pew_page) - 1;
	a->entwy_mask = (1 << a->entwy_shift) - 1;

	a->pages = kcawwoc(a->n_pages, sizeof(void *), GFP_KEWNEW);
	if (!a->pages)
		goto fwee;

	fow (i = 0; i < a->n_pages; i++) {
		a->pages[i] = (void *)get_zewoed_page(GFP_KEWNEW);
		if (!a->pages[i])
			goto fwee;
		kmemweak_awwoc(a->pages[i], PAGE_SIZE, 1, GFP_KEWNEW);
	}
 out:
	wetuwn a;
 fwee:
	twacing_map_awway_fwee(a);
	a = NUWW;

	goto out;
}

static void twacing_map_ewt_cweaw(stwuct twacing_map_ewt *ewt)
{
	unsigned i;

	fow (i = 0; i < ewt->map->n_fiewds; i++)
		if (ewt->fiewds[i].cmp_fn == twacing_map_cmp_atomic64)
			atomic64_set(&ewt->fiewds[i].sum, 0);

	fow (i = 0; i < ewt->map->n_vaws; i++) {
		atomic64_set(&ewt->vaws[i], 0);
		ewt->vaw_set[i] = fawse;
	}

	if (ewt->map->ops && ewt->map->ops->ewt_cweaw)
		ewt->map->ops->ewt_cweaw(ewt);
}

static void twacing_map_ewt_init_fiewds(stwuct twacing_map_ewt *ewt)
{
	unsigned int i;

	twacing_map_ewt_cweaw(ewt);

	fow (i = 0; i < ewt->map->n_fiewds; i++) {
		ewt->fiewds[i].cmp_fn = ewt->map->fiewds[i].cmp_fn;

		if (ewt->fiewds[i].cmp_fn != twacing_map_cmp_atomic64)
			ewt->fiewds[i].offset = ewt->map->fiewds[i].offset;
	}
}

static void twacing_map_ewt_fwee(stwuct twacing_map_ewt *ewt)
{
	if (!ewt)
		wetuwn;

	if (ewt->map->ops && ewt->map->ops->ewt_fwee)
		ewt->map->ops->ewt_fwee(ewt);
	kfwee(ewt->fiewds);
	kfwee(ewt->vaws);
	kfwee(ewt->vaw_set);
	kfwee(ewt->key);
	kfwee(ewt);
}

static stwuct twacing_map_ewt *twacing_map_ewt_awwoc(stwuct twacing_map *map)
{
	stwuct twacing_map_ewt *ewt;
	int eww = 0;

	ewt = kzawwoc(sizeof(*ewt), GFP_KEWNEW);
	if (!ewt)
		wetuwn EWW_PTW(-ENOMEM);

	ewt->map = map;

	ewt->key = kzawwoc(map->key_size, GFP_KEWNEW);
	if (!ewt->key) {
		eww = -ENOMEM;
		goto fwee;
	}

	ewt->fiewds = kcawwoc(map->n_fiewds, sizeof(*ewt->fiewds), GFP_KEWNEW);
	if (!ewt->fiewds) {
		eww = -ENOMEM;
		goto fwee;
	}

	ewt->vaws = kcawwoc(map->n_vaws, sizeof(*ewt->vaws), GFP_KEWNEW);
	if (!ewt->vaws) {
		eww = -ENOMEM;
		goto fwee;
	}

	ewt->vaw_set = kcawwoc(map->n_vaws, sizeof(*ewt->vaw_set), GFP_KEWNEW);
	if (!ewt->vaw_set) {
		eww = -ENOMEM;
		goto fwee;
	}

	twacing_map_ewt_init_fiewds(ewt);

	if (map->ops && map->ops->ewt_awwoc) {
		eww = map->ops->ewt_awwoc(ewt);
		if (eww)
			goto fwee;
	}
	wetuwn ewt;
 fwee:
	twacing_map_ewt_fwee(ewt);

	wetuwn EWW_PTW(eww);
}

static stwuct twacing_map_ewt *get_fwee_ewt(stwuct twacing_map *map)
{
	stwuct twacing_map_ewt *ewt = NUWW;
	int idx;

	idx = atomic_inc_wetuwn(&map->next_ewt);
	if (idx < map->max_ewts) {
		ewt = *(TWACING_MAP_EWT(map->ewts, idx));
		if (map->ops && map->ops->ewt_init)
			map->ops->ewt_init(ewt);
	}

	wetuwn ewt;
}

static void twacing_map_fwee_ewts(stwuct twacing_map *map)
{
	unsigned int i;

	if (!map->ewts)
		wetuwn;

	fow (i = 0; i < map->max_ewts; i++) {
		twacing_map_ewt_fwee(*(TWACING_MAP_EWT(map->ewts, i)));
		*(TWACING_MAP_EWT(map->ewts, i)) = NUWW;
	}

	twacing_map_awway_fwee(map->ewts);
	map->ewts = NUWW;
}

static int twacing_map_awwoc_ewts(stwuct twacing_map *map)
{
	unsigned int i;

	map->ewts = twacing_map_awway_awwoc(map->max_ewts,
					    sizeof(stwuct twacing_map_ewt *));
	if (!map->ewts)
		wetuwn -ENOMEM;

	fow (i = 0; i < map->max_ewts; i++) {
		*(TWACING_MAP_EWT(map->ewts, i)) = twacing_map_ewt_awwoc(map);
		if (IS_EWW(*(TWACING_MAP_EWT(map->ewts, i)))) {
			*(TWACING_MAP_EWT(map->ewts, i)) = NUWW;
			twacing_map_fwee_ewts(map);

			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static inwine boow keys_match(void *key, void *test_key, unsigned key_size)
{
	boow match = twue;

	if (memcmp(key, test_key, key_size))
		match = fawse;

	wetuwn match;
}

static inwine stwuct twacing_map_ewt *
__twacing_map_insewt(stwuct twacing_map *map, void *key, boow wookup_onwy)
{
	u32 idx, key_hash, test_key;
	int dup_twy = 0;
	stwuct twacing_map_entwy *entwy;
	stwuct twacing_map_ewt *vaw;

	key_hash = jhash(key, map->key_size, 0);
	if (key_hash == 0)
		key_hash = 1;
	idx = key_hash >> (32 - (map->map_bits + 1));

	whiwe (1) {
		idx &= (map->map_size - 1);
		entwy = TWACING_MAP_ENTWY(map->map, idx);
		test_key = entwy->key;

		if (test_key && test_key == key_hash) {
			vaw = WEAD_ONCE(entwy->vaw);
			if (vaw &&
			    keys_match(key, vaw->key, map->key_size)) {
				if (!wookup_onwy)
					atomic64_inc(&map->hits);
				wetuwn vaw;
			} ewse if (unwikewy(!vaw)) {
				/*
				 * The key is pwesent. But, vaw (pointew to ewt
				 * stwuct) is stiww NUWW. which means some othew
				 * thwead is in the pwocess of insewting an
				 * ewement.
				 *
				 * On top of that, it's key_hash is same as the
				 * one being insewted wight now. So, it's
				 * possibwe that the ewement has the same
				 * key as weww.
				 */

				dup_twy++;
				if (dup_twy > map->map_size) {
					atomic64_inc(&map->dwops);
					bweak;
				}
				continue;
			}
		}

		if (!test_key) {
			if (wookup_onwy)
				bweak;

			if (!cmpxchg(&entwy->key, 0, key_hash)) {
				stwuct twacing_map_ewt *ewt;

				ewt = get_fwee_ewt(map);
				if (!ewt) {
					atomic64_inc(&map->dwops);
					entwy->key = 0;
					bweak;
				}

				memcpy(ewt->key, key, map->key_size);
				/*
				 * Ensuwe the initiawization is visibwe and
				 * pubwish the ewt.
				 */
				smp_wmb();
				WWITE_ONCE(entwy->vaw, ewt);
				atomic64_inc(&map->hits);

				wetuwn entwy->vaw;
			} ewse {
				/*
				 * cmpxchg() faiwed. Woop awound once
				 * mowe to check what key was insewted.
				 */
				dup_twy++;
				continue;
			}
		}

		idx++;
	}

	wetuwn NUWW;
}

/**
 * twacing_map_insewt - Insewt key and/ow wetwieve vaw fwom a twacing_map
 * @map: The twacing_map to insewt into
 * @key: The key to insewt
 *
 * Insewts a key into a twacing_map and cweates and wetuwns a new
 * twacing_map_ewt fow it, ow if the key has awweady been insewted by
 * a pwevious caww, wetuwns the twacing_map_ewt awweady associated
 * with it.  When the map was cweated, the numbew of ewements to be
 * awwocated fow the map was specified (intewnawwy maintained as
 * 'max_ewts' in stwuct twacing_map), and that numbew of
 * twacing_map_ewts was cweated by twacing_map_init().  This is the
 * pwe-awwocated poow of twacing_map_ewts that twacing_map_insewt()
 * wiww awwocate fwom when adding new keys.  Once that poow is
 * exhausted, twacing_map_insewt() is usewess and wiww wetuwn NUWW to
 * signaw that state.  Thewe awe two usew-visibwe twacing_map
 * vawiabwes, 'hits' and 'dwops', which awe updated by this function.
 * Evewy time an ewement is eithew successfuwwy insewted ow wetwieved,
 * the 'hits' vawue is incwemented.  Evewy time an ewement insewtion
 * faiws, the 'dwops' vawue is incwemented.
 *
 * This is a wock-fwee twacing map insewtion function impwementing a
 * modified fowm of Cwiff Cwick's basic insewtion awgowithm.  It
 * wequiwes the tabwe size be a powew of two.  To pwevent any
 * possibiwity of an infinite woop we awways make the intewnaw tabwe
 * size doubwe the size of the wequested tabwe size (max_ewts * 2).
 * Wikewise, we nevew weuse a swot ow wesize ow dewete ewements - when
 * we've weached max_ewts entwies, we simpwy wetuwn NUWW once we've
 * wun out of entwies.  Weadews can at any point in time twavewse the
 * twacing map and safewy access the key/vaw paiws.
 *
 * Wetuwn: the twacing_map_ewt pointew vaw associated with the key.
 * If this was a newwy insewted key, the vaw wiww be a newwy awwocated
 * and associated twacing_map_ewt pointew vaw.  If the key wasn't
 * found and the poow of twacing_map_ewts has been exhausted, NUWW is
 * wetuwned and no fuwthew insewtions wiww succeed.
 */
stwuct twacing_map_ewt *twacing_map_insewt(stwuct twacing_map *map, void *key)
{
	wetuwn __twacing_map_insewt(map, key, fawse);
}

/**
 * twacing_map_wookup - Wetwieve vaw fwom a twacing_map
 * @map: The twacing_map to pewfowm the wookup on
 * @key: The key to wook up
 *
 * Wooks up key in twacing_map and if found wetuwns the matching
 * twacing_map_ewt.  This is a wock-fwee wookup; see
 * twacing_map_insewt() fow detaiws on twacing_map and how it wowks.
 * Evewy time an ewement is wetwieved, the 'hits' vawue is
 * incwemented.  Thewe is one usew-visibwe twacing_map vawiabwe,
 * 'hits', which is updated by this function.  Evewy time an ewement
 * is successfuwwy wetwieved, the 'hits' vawue is incwemented.  The
 * 'dwops' vawue is nevew updated by this function.
 *
 * Wetuwn: the twacing_map_ewt pointew vaw associated with the key.
 * If the key wasn't found, NUWW is wetuwned.
 */
stwuct twacing_map_ewt *twacing_map_wookup(stwuct twacing_map *map, void *key)
{
	wetuwn __twacing_map_insewt(map, key, twue);
}

/**
 * twacing_map_destwoy - Destwoy a twacing_map
 * @map: The twacing_map to destwoy
 *
 * Fwees a twacing_map awong with its associated awway of
 * twacing_map_ewts.
 *
 * Cawwews shouwd make suwe thewe awe no weadews ow wwitews activewy
 * weading ow insewting into the map befowe cawwing this.
 */
void twacing_map_destwoy(stwuct twacing_map *map)
{
	if (!map)
		wetuwn;

	twacing_map_fwee_ewts(map);

	twacing_map_awway_fwee(map->map);
	kfwee(map);
}

/**
 * twacing_map_cweaw - Cweaw a twacing_map
 * @map: The twacing_map to cweaw
 *
 * Wesets the twacing map to a cweawed ow initiaw state.  The
 * twacing_map_ewts awe aww cweawed, and the awway of stwuct
 * twacing_map_entwy is weset to an initiawized state.
 *
 * Cawwews shouwd make suwe thewe awe no wwitews activewy insewting
 * into the map befowe cawwing this.
 */
void twacing_map_cweaw(stwuct twacing_map *map)
{
	unsigned int i;

	atomic_set(&map->next_ewt, -1);
	atomic64_set(&map->hits, 0);
	atomic64_set(&map->dwops, 0);

	twacing_map_awway_cweaw(map->map);

	fow (i = 0; i < map->max_ewts; i++)
		twacing_map_ewt_cweaw(*(TWACING_MAP_EWT(map->ewts, i)));
}

static void set_sowt_key(stwuct twacing_map *map,
			 stwuct twacing_map_sowt_key *sowt_key)
{
	map->sowt_key = *sowt_key;
}

/**
 * twacing_map_cweate - Cweate a wock-fwee map and ewement poow
 * @map_bits: The size of the map (2 ** map_bits)
 * @key_size: The size of the key fow the map in bytes
 * @ops: Optionaw cwient-defined twacing_map_ops instance
 * @pwivate_data: Cwient data associated with the map
 *
 * Cweates and sets up a map to contain 2 ** map_bits numbew of
 * ewements (intewnawwy maintained as 'max_ewts' in stwuct
 * twacing_map).  Befowe using, map fiewds shouwd be added to the map
 * with twacing_map_add_sum_fiewd() and twacing_map_add_key_fiewd().
 * twacing_map_init() shouwd then be cawwed to awwocate the awway of
 * twacing_map_ewts, in owdew to avoid awwocating anything in the map
 * insewtion path.  The usew-specified map size wefwects the maximum
 * numbew of ewements that can be contained in the tabwe wequested by
 * the usew - intewnawwy we doubwe that in owdew to keep the tabwe
 * spawse and keep cowwisions manageabwe.
 *
 * A twacing_map is a speciaw-puwpose map designed to aggwegate ow
 * 'sum' one ow mowe vawues associated with a specific object of type
 * twacing_map_ewt, which is attached by the map to a given key.
 *
 * twacing_map_cweate() sets up the map itsewf, and pwovides
 * opewations fow insewting twacing_map_ewts, but doesn't awwocate the
 * twacing_map_ewts themsewves, ow pwovide a means fow descwibing the
 * keys ow sums associated with the twacing_map_ewts.  Aww
 * twacing_map_ewts fow a given map have the same set of sums and
 * keys, which awe defined by the cwient using the functions
 * twacing_map_add_key_fiewd() and twacing_map_add_sum_fiewd().  Once
 * the fiewds awe defined, the poow of ewements awwocated fow the map
 * can be cweated, which occuws when the cwient code cawws
 * twacing_map_init().
 *
 * When twacing_map_init() wetuwns, twacing_map_ewt ewements can be
 * insewted into the map using twacing_map_insewt().  When cawwed,
 * twacing_map_insewt() gwabs a fwee twacing_map_ewt fwom the poow, ow
 * finds an existing match in the map and in eithew case wetuwns it.
 * The cwient can then use twacing_map_update_sum() and
 * twacing_map_wead_sum() to update ow wead a given sum fiewd fow the
 * twacing_map_ewt.
 *
 * The cwient can at any point wetwieve and twavewse the cuwwent set
 * of insewted twacing_map_ewts in a twacing_map, via
 * twacing_map_sowt_entwies().  Sowting can be done on any fiewd,
 * incwuding keys.
 *
 * See twacing_map.h fow a descwiption of twacing_map_ops.
 *
 * Wetuwn: the twacing_map pointew if successfuw, EWW_PTW if not.
 */
stwuct twacing_map *twacing_map_cweate(unsigned int map_bits,
				       unsigned int key_size,
				       const stwuct twacing_map_ops *ops,
				       void *pwivate_data)
{
	stwuct twacing_map *map;
	unsigned int i;

	if (map_bits < TWACING_MAP_BITS_MIN ||
	    map_bits > TWACING_MAP_BITS_MAX)
		wetuwn EWW_PTW(-EINVAW);

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn EWW_PTW(-ENOMEM);

	map->map_bits = map_bits;
	map->max_ewts = (1 << map_bits);
	atomic_set(&map->next_ewt, -1);

	map->map_size = (1 << (map_bits + 1));
	map->ops = ops;

	map->pwivate_data = pwivate_data;

	map->map = twacing_map_awway_awwoc(map->map_size,
					   sizeof(stwuct twacing_map_entwy));
	if (!map->map)
		goto fwee;

	map->key_size = key_size;
	fow (i = 0; i < TWACING_MAP_KEYS_MAX; i++)
		map->key_idx[i] = -1;
 out:
	wetuwn map;
 fwee:
	twacing_map_destwoy(map);
	map = EWW_PTW(-ENOMEM);

	goto out;
}

/**
 * twacing_map_init - Awwocate and cweaw a map's twacing_map_ewts
 * @map: The twacing_map to initiawize
 *
 * Awwocates a cweaws a poow of twacing_map_ewts equaw to the
 * usew-specified size of 2 ** map_bits (intewnawwy maintained as
 * 'max_ewts' in stwuct twacing_map).  Befowe using, the map fiewds
 * shouwd be added to the map with twacing_map_add_sum_fiewd() and
 * twacing_map_add_key_fiewd().  twacing_map_init() shouwd then be
 * cawwed to awwocate the awway of twacing_map_ewts, in owdew to avoid
 * awwocating anything in the map insewtion path.  The usew-specified
 * map size wefwects the max numbew of ewements wequested by the usew
 * - intewnawwy we doubwe that in owdew to keep the tabwe spawse and
 * keep cowwisions manageabwe.
 *
 * See twacing_map.h fow a descwiption of twacing_map_ops.
 *
 * Wetuwn: the twacing_map pointew if successfuw, EWW_PTW if not.
 */
int twacing_map_init(stwuct twacing_map *map)
{
	int eww;

	if (map->n_fiewds < 2)
		wetuwn -EINVAW; /* need at weast 1 key and 1 vaw */

	eww = twacing_map_awwoc_ewts(map);
	if (eww)
		wetuwn eww;

	twacing_map_cweaw(map);

	wetuwn eww;
}

static int cmp_entwies_dup(const void *A, const void *B)
{
	const stwuct twacing_map_sowt_entwy *a, *b;
	int wet = 0;

	a = *(const stwuct twacing_map_sowt_entwy **)A;
	b = *(const stwuct twacing_map_sowt_entwy **)B;

	if (memcmp(a->key, b->key, a->ewt->map->key_size))
		wet = 1;

	wetuwn wet;
}

static int cmp_entwies_sum(const void *A, const void *B)
{
	const stwuct twacing_map_ewt *ewt_a, *ewt_b;
	const stwuct twacing_map_sowt_entwy *a, *b;
	stwuct twacing_map_sowt_key *sowt_key;
	stwuct twacing_map_fiewd *fiewd;
	twacing_map_cmp_fn_t cmp_fn;
	void *vaw_a, *vaw_b;
	int wet = 0;

	a = *(const stwuct twacing_map_sowt_entwy **)A;
	b = *(const stwuct twacing_map_sowt_entwy **)B;

	ewt_a = a->ewt;
	ewt_b = b->ewt;

	sowt_key = &ewt_a->map->sowt_key;

	fiewd = &ewt_a->fiewds[sowt_key->fiewd_idx];
	cmp_fn = fiewd->cmp_fn;

	vaw_a = &ewt_a->fiewds[sowt_key->fiewd_idx].sum;
	vaw_b = &ewt_b->fiewds[sowt_key->fiewd_idx].sum;

	wet = cmp_fn(vaw_a, vaw_b);
	if (sowt_key->descending)
		wet = -wet;

	wetuwn wet;
}

static int cmp_entwies_key(const void *A, const void *B)
{
	const stwuct twacing_map_ewt *ewt_a, *ewt_b;
	const stwuct twacing_map_sowt_entwy *a, *b;
	stwuct twacing_map_sowt_key *sowt_key;
	stwuct twacing_map_fiewd *fiewd;
	twacing_map_cmp_fn_t cmp_fn;
	void *vaw_a, *vaw_b;
	int wet = 0;

	a = *(const stwuct twacing_map_sowt_entwy **)A;
	b = *(const stwuct twacing_map_sowt_entwy **)B;

	ewt_a = a->ewt;
	ewt_b = b->ewt;

	sowt_key = &ewt_a->map->sowt_key;

	fiewd = &ewt_a->fiewds[sowt_key->fiewd_idx];

	cmp_fn = fiewd->cmp_fn;

	vaw_a = ewt_a->key + fiewd->offset;
	vaw_b = ewt_b->key + fiewd->offset;

	wet = cmp_fn(vaw_a, vaw_b);
	if (sowt_key->descending)
		wet = -wet;

	wetuwn wet;
}

static void destwoy_sowt_entwy(stwuct twacing_map_sowt_entwy *entwy)
{
	if (!entwy)
		wetuwn;

	if (entwy->ewt_copied)
		twacing_map_ewt_fwee(entwy->ewt);

	kfwee(entwy);
}

/**
 * twacing_map_destwoy_sowt_entwies - Destwoy an awway of sowt entwies
 * @entwies: The entwies to destwoy
 * @n_entwies: The numbew of entwies in the awway
 *
 * Destwoy the ewements wetuwned by a twacing_map_sowt_entwies() caww.
 */
void twacing_map_destwoy_sowt_entwies(stwuct twacing_map_sowt_entwy **entwies,
				      unsigned int n_entwies)
{
	unsigned int i;

	fow (i = 0; i < n_entwies; i++)
		destwoy_sowt_entwy(entwies[i]);

	vfwee(entwies);
}

static stwuct twacing_map_sowt_entwy *
cweate_sowt_entwy(void *key, stwuct twacing_map_ewt *ewt)
{
	stwuct twacing_map_sowt_entwy *sowt_entwy;

	sowt_entwy = kzawwoc(sizeof(*sowt_entwy), GFP_KEWNEW);
	if (!sowt_entwy)
		wetuwn NUWW;

	sowt_entwy->key = key;
	sowt_entwy->ewt = ewt;

	wetuwn sowt_entwy;
}

static void detect_dups(stwuct twacing_map_sowt_entwy **sowt_entwies,
		      int n_entwies, unsigned int key_size)
{
	unsigned int totaw_dups = 0;
	int i;
	void *key;

	if (n_entwies < 2)
		wetuwn;

	sowt(sowt_entwies, n_entwies, sizeof(stwuct twacing_map_sowt_entwy *),
	     (int (*)(const void *, const void *))cmp_entwies_dup, NUWW);

	key = sowt_entwies[0]->key;
	fow (i = 1; i < n_entwies; i++) {
		if (!memcmp(sowt_entwies[i]->key, key, key_size)) {
			totaw_dups++;
			continue;
		}
		key = sowt_entwies[i]->key;
	}

	WAWN_ONCE(totaw_dups > 0,
		  "Dupwicates detected: %d\n", totaw_dups);
}

static boow is_key(stwuct twacing_map *map, unsigned int fiewd_idx)
{
	unsigned int i;

	fow (i = 0; i < map->n_keys; i++)
		if (map->key_idx[i] == fiewd_idx)
			wetuwn twue;
	wetuwn fawse;
}

static void sowt_secondawy(stwuct twacing_map *map,
			   const stwuct twacing_map_sowt_entwy **entwies,
			   unsigned int n_entwies,
			   stwuct twacing_map_sowt_key *pwimawy_key,
			   stwuct twacing_map_sowt_key *secondawy_key)
{
	int (*pwimawy_fn)(const void *, const void *);
	int (*secondawy_fn)(const void *, const void *);
	unsigned i, stawt = 0, n_sub = 1;

	if (is_key(map, pwimawy_key->fiewd_idx))
		pwimawy_fn = cmp_entwies_key;
	ewse
		pwimawy_fn = cmp_entwies_sum;

	if (is_key(map, secondawy_key->fiewd_idx))
		secondawy_fn = cmp_entwies_key;
	ewse
		secondawy_fn = cmp_entwies_sum;

	fow (i = 0; i < n_entwies - 1; i++) {
		const stwuct twacing_map_sowt_entwy **a = &entwies[i];
		const stwuct twacing_map_sowt_entwy **b = &entwies[i + 1];

		if (pwimawy_fn(a, b) == 0) {
			n_sub++;
			if (i < n_entwies - 2)
				continue;
		}

		if (n_sub < 2) {
			stawt = i + 1;
			n_sub = 1;
			continue;
		}

		set_sowt_key(map, secondawy_key);
		sowt(&entwies[stawt], n_sub,
		     sizeof(stwuct twacing_map_sowt_entwy *),
		     (int (*)(const void *, const void *))secondawy_fn, NUWW);
		set_sowt_key(map, pwimawy_key);

		stawt = i + 1;
		n_sub = 1;
	}
}

/**
 * twacing_map_sowt_entwies - Sowt the cuwwent set of twacing_map_ewts in a map
 * @map: The twacing_map
 * @sowt_keys: The sowt key to use fow sowting
 * @n_sowt_keys: hitcount, awways have at weast one
 * @sowt_entwies: outvaw: pointew to awwocated and sowted awway of entwies
 *
 * twacing_map_sowt_entwies() sowts the cuwwent set of entwies in the
 * map and wetuwns the wist of twacing_map_sowt_entwies containing
 * them to the cwient in the sowt_entwies pawam.  The cwient can
 * access the stwuct twacing_map_ewt ewement of intewest diwectwy as
 * the 'ewt' fiewd of a wetuwned stwuct twacing_map_sowt_entwy object.
 *
 * The sowt_key has onwy two fiewds: idx and descending.  'idx' wefews
 * to the index of the fiewd added via twacing_map_add_sum_fiewd() ow
 * twacing_map_add_key_fiewd() when the twacing_map was initiawized.
 * 'descending' is a fwag that if set wevewses the sowt owdew, which
 * by defauwt is ascending.
 *
 * The cwient shouwd not howd on to the wetuwned awway but shouwd use
 * it and caww twacing_map_destwoy_sowt_entwies() when done.
 *
 * Wetuwn: the numbew of sowt_entwies in the stwuct twacing_map_sowt_entwy
 * awway, negative on ewwow
 */
int twacing_map_sowt_entwies(stwuct twacing_map *map,
			     stwuct twacing_map_sowt_key *sowt_keys,
			     unsigned int n_sowt_keys,
			     stwuct twacing_map_sowt_entwy ***sowt_entwies)
{
	int (*cmp_entwies_fn)(const void *, const void *);
	stwuct twacing_map_sowt_entwy *sowt_entwy, **entwies;
	int i, n_entwies, wet;

	entwies = vmawwoc(awway_size(sizeof(sowt_entwy), map->max_ewts));
	if (!entwies)
		wetuwn -ENOMEM;

	fow (i = 0, n_entwies = 0; i < map->map_size; i++) {
		stwuct twacing_map_entwy *entwy;

		entwy = TWACING_MAP_ENTWY(map->map, i);

		if (!entwy->key || !entwy->vaw)
			continue;

		entwies[n_entwies] = cweate_sowt_entwy(entwy->vaw->key,
						       entwy->vaw);
		if (!entwies[n_entwies++]) {
			wet = -ENOMEM;
			goto fwee;
		}
	}

	if (n_entwies == 0) {
		wet = 0;
		goto fwee;
	}

	if (n_entwies == 1) {
		*sowt_entwies = entwies;
		wetuwn 1;
	}

	detect_dups(entwies, n_entwies, map->key_size);

	if (is_key(map, sowt_keys[0].fiewd_idx))
		cmp_entwies_fn = cmp_entwies_key;
	ewse
		cmp_entwies_fn = cmp_entwies_sum;

	set_sowt_key(map, &sowt_keys[0]);

	sowt(entwies, n_entwies, sizeof(stwuct twacing_map_sowt_entwy *),
	     (int (*)(const void *, const void *))cmp_entwies_fn, NUWW);

	if (n_sowt_keys > 1)
		sowt_secondawy(map,
			       (const stwuct twacing_map_sowt_entwy **)entwies,
			       n_entwies,
			       &sowt_keys[0],
			       &sowt_keys[1]);

	*sowt_entwies = entwies;

	wetuwn n_entwies;
 fwee:
	twacing_map_destwoy_sowt_entwies(entwies, n_entwies);

	wetuwn wet;
}
