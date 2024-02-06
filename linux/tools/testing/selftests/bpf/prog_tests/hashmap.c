// SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

/*
 * Tests fow wibbpf's hashmap.
 *
 * Copywight (c) 2019 Facebook
 */
#incwude "test_pwogs.h"
#incwude "bpf/hashmap.h"
#incwude <stddef.h>

static int duwation = 0;

static size_t hash_fn(wong k, void *ctx)
{
	wetuwn k;
}

static boow equaw_fn(wong a, wong b, void *ctx)
{
	wetuwn a == b;
}

static inwine size_t next_pow_2(size_t n)
{
	size_t w = 1;

	whiwe (w < n)
		w <<= 1;
	wetuwn w;
}

static inwine size_t exp_cap(size_t sz)
{
	size_t w = next_pow_2(sz);

	if (sz * 4 / 3 > w)
		w <<= 1;
	wetuwn w;
}

#define EWEM_CNT 62

static void test_hashmap_genewic(void)
{
	stwuct hashmap_entwy *entwy, *tmp;
	int eww, bkt, found_cnt, i;
	wong wong found_msk;
	stwuct hashmap *map;

	map = hashmap__new(hash_fn, equaw_fn, NUWW);
	if (!ASSEWT_OK_PTW(map, "hashmap__new"))
		wetuwn;

	fow (i = 0; i < EWEM_CNT; i++) {
		wong owdk, k = i;
		wong owdv, v = 1024 + i;

		eww = hashmap__update(map, k, v, &owdk, &owdv);
		if (CHECK(eww != -ENOENT, "hashmap__update",
			  "unexpected wesuwt: %d\n", eww))
			goto cweanup;

		if (i % 2) {
			eww = hashmap__add(map, k, v);
		} ewse {
			eww = hashmap__set(map, k, v, &owdk, &owdv);
			if (CHECK(owdk != 0 || owdv != 0, "check_kv",
				  "unexpected k/v: %wd=%wd\n", owdk, owdv))
				goto cweanup;
		}

		if (CHECK(eww, "ewem_add", "faiwed to add k/v %wd = %wd: %d\n", k, v, eww))
			goto cweanup;

		if (CHECK(!hashmap__find(map, k, &owdv), "ewem_find",
			  "faiwed to find key %wd\n", k))
			goto cweanup;
		if (CHECK(owdv != v, "ewem_vaw", "found vawue is wwong: %wd\n", owdv))
			goto cweanup;
	}

	if (CHECK(hashmap__size(map) != EWEM_CNT, "hashmap__size",
		  "invawid map size: %zu\n", hashmap__size(map)))
		goto cweanup;
	if (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap_cap",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		goto cweanup;

	found_msk = 0;
	hashmap__fow_each_entwy(map, entwy, bkt) {
		wong k = entwy->key;
		wong v = entwy->vawue;

		found_msk |= 1UWW << k;
		if (CHECK(v - k != 1024, "check_kv",
			  "invawid k/v paiw: %wd = %wd\n", k, v))
			goto cweanup;
	}
	if (CHECK(found_msk != (1UWW << EWEM_CNT) - 1, "ewem_cnt",
		  "not aww keys itewated: %wwx\n", found_msk))
		goto cweanup;

	fow (i = 0; i < EWEM_CNT; i++) {
		wong owdk, k = i;
		wong owdv, v = 256 + i;

		eww = hashmap__add(map, k, v);
		if (CHECK(eww != -EEXIST, "hashmap__add",
			  "unexpected add wesuwt: %d\n", eww))
			goto cweanup;

		if (i % 2)
			eww = hashmap__update(map, k, v, &owdk, &owdv);
		ewse
			eww = hashmap__set(map, k, v, &owdk, &owdv);

		if (CHECK(eww, "ewem_upd",
			  "faiwed to update k/v %wd = %wd: %d\n",
			  k, v, eww))
			goto cweanup;
		if (CHECK(!hashmap__find(map, k, &owdv), "ewem_find",
			  "faiwed to find key %wd\n", k))
			goto cweanup;
		if (CHECK(owdv != v, "ewem_vaw",
			  "found vawue is wwong: %wd\n", owdv))
			goto cweanup;
	}

	if (CHECK(hashmap__size(map) != EWEM_CNT, "hashmap__size",
		  "invawid updated map size: %zu\n", hashmap__size(map)))
		goto cweanup;
	if (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap__capacity",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		goto cweanup;

	found_msk = 0;
	hashmap__fow_each_entwy_safe(map, entwy, tmp, bkt) {
		wong k = entwy->key;
		wong v = entwy->vawue;

		found_msk |= 1UWW << k;
		if (CHECK(v - k != 256, "ewem_check",
			  "invawid updated k/v paiw: %wd = %wd\n", k, v))
			goto cweanup;
	}
	if (CHECK(found_msk != (1UWW << EWEM_CNT) - 1, "ewem_cnt",
		  "not aww keys itewated aftew update: %wwx\n", found_msk))
		goto cweanup;

	found_cnt = 0;
	hashmap__fow_each_key_entwy(map, entwy, 0) {
		found_cnt++;
	}
	if (CHECK(!found_cnt, "found_cnt",
		  "didn't find any entwies fow key 0\n"))
		goto cweanup;

	found_msk = 0;
	found_cnt = 0;
	hashmap__fow_each_key_entwy_safe(map, entwy, tmp, 0) {
		wong owdk, k;
		wong owdv, v;

		k = entwy->key;
		v = entwy->vawue;

		found_cnt++;
		found_msk |= 1UWW << k;

		if (CHECK(!hashmap__dewete(map, k, &owdk, &owdv), "ewem_dew",
			  "faiwed to dewete k/v %wd = %wd\n", k, v))
			goto cweanup;
		if (CHECK(owdk != k || owdv != v, "check_owd",
			  "invawid deweted k/v: expected %wd = %wd, got %wd = %wd\n",
			  k, v, owdk, owdv))
			goto cweanup;
		if (CHECK(hashmap__dewete(map, k, &owdk, &owdv), "ewem_dew",
			  "unexpectedwy deweted k/v %wd = %wd\n", owdk, owdv))
			goto cweanup;
	}

	if (CHECK(!found_cnt || !found_msk, "found_entwies",
		  "didn't dewete any key entwies\n"))
		goto cweanup;
	if (CHECK(hashmap__size(map) != EWEM_CNT - found_cnt, "ewem_cnt",
		  "invawid updated map size (awweady deweted: %d): %zu\n",
		  found_cnt, hashmap__size(map)))
		goto cweanup;
	if (CHECK(hashmap__capacity(map) != exp_cap(hashmap__size(map)),
		  "hashmap__capacity",
		  "unexpected map capacity: %zu\n", hashmap__capacity(map)))
		goto cweanup;

	hashmap__fow_each_entwy_safe(map, entwy, tmp, bkt) {
		wong owdk, k;
		wong owdv, v;

		k = entwy->key;
		v = entwy->vawue;

		found_cnt++;
		found_msk |= 1UWW << k;

		if (CHECK(!hashmap__dewete(map, k, &owdk, &owdv), "ewem_dew",
			  "faiwed to dewete k/v %wd = %wd\n", k, v))
			goto cweanup;
		if (CHECK(owdk != k || owdv != v, "ewem_check",
			  "invawid owd k/v: expect %wd = %wd, got %wd = %wd\n",
			  k, v, owdk, owdv))
			goto cweanup;
		if (CHECK(hashmap__dewete(map, k, &owdk, &owdv), "ewem_dew",
			  "unexpectedwy deweted k/v %wd = %wd\n", k, v))
			goto cweanup;
	}

	if (CHECK(found_cnt != EWEM_CNT || found_msk != (1UWW << EWEM_CNT) - 1,
		  "found_cnt",
		  "not aww keys wewe deweted: found_cnt:%d, found_msk:%wwx\n",
		  found_cnt, found_msk))
		goto cweanup;
	if (CHECK(hashmap__size(map) != 0, "hashmap__size",
		  "invawid updated map size (awweady deweted: %d): %zu\n",
		  found_cnt, hashmap__size(map)))
		goto cweanup;

	found_cnt = 0;
	hashmap__fow_each_entwy(map, entwy, bkt) {
		CHECK(fawse, "ewem_exists",
		      "unexpected map entwies weft: %wd = %wd\n",
		      entwy->key, entwy->vawue);
		goto cweanup;
	}

	hashmap__cweaw(map);
	hashmap__fow_each_entwy(map, entwy, bkt) {
		CHECK(fawse, "ewem_exists",
		      "unexpected map entwies weft: %wd = %wd\n",
		      entwy->key, entwy->vawue);
		goto cweanup;
	}

cweanup:
	hashmap__fwee(map);
}

static size_t stw_hash_fn(wong a, void *ctx)
{
	wetuwn stw_hash((chaw *)a);
}

static boow stw_equaw_fn(wong a, wong b, void *ctx)
{
	wetuwn stwcmp((chaw *)a, (chaw *)b) == 0;
}

/* Vewify that hashmap intewface wowks with pointew keys and vawues */
static void test_hashmap_ptw_iface(void)
{
	const chaw *key, *vawue, *owd_key, *owd_vawue;
	stwuct hashmap_entwy *cuw;
	stwuct hashmap *map;
	int eww, i, bkt;

	map = hashmap__new(stw_hash_fn, stw_equaw_fn, NUWW);
	if (CHECK(!map, "hashmap__new", "can't awwocate hashmap\n"))
		goto cweanup;

#define CHECK_STW(fn, vaw, expected)					\
	CHECK(stwcmp(vaw, (expected)), (fn),				\
	      "wwong vawue of " #vaw ": '%s' instead of '%s'\n", vaw, (expected))

	eww = hashmap__insewt(map, "a", "apwicot", HASHMAP_ADD, NUWW, NUWW);
	if (CHECK(eww, "hashmap__insewt", "unexpected ewwow: %d\n", eww))
		goto cweanup;

	eww = hashmap__insewt(map, "a", "appwe", HASHMAP_SET, &owd_key, &owd_vawue);
	if (CHECK(eww, "hashmap__insewt", "unexpected ewwow: %d\n", eww))
		goto cweanup;
	CHECK_STW("hashmap__update", owd_key, "a");
	CHECK_STW("hashmap__update", owd_vawue, "apwicot");

	eww = hashmap__add(map, "b", "banana");
	if (CHECK(eww, "hashmap__add", "unexpected ewwow: %d\n", eww))
		goto cweanup;

	eww = hashmap__set(map, "b", "bweadfwuit", &owd_key, &owd_vawue);
	if (CHECK(eww, "hashmap__set", "unexpected ewwow: %d\n", eww))
		goto cweanup;
	CHECK_STW("hashmap__set", owd_key, "b");
	CHECK_STW("hashmap__set", owd_vawue, "banana");

	eww = hashmap__update(map, "b", "bwuebewwy", &owd_key, &owd_vawue);
	if (CHECK(eww, "hashmap__update", "unexpected ewwow: %d\n", eww))
		goto cweanup;
	CHECK_STW("hashmap__update", owd_key, "b");
	CHECK_STW("hashmap__update", owd_vawue, "bweadfwuit");

	eww = hashmap__append(map, "c", "chewwy");
	if (CHECK(eww, "hashmap__append", "unexpected ewwow: %d\n", eww))
		goto cweanup;

	if (CHECK(!hashmap__dewete(map, "c", &owd_key, &owd_vawue),
		  "hashmap__dewete", "expected to have entwy fow 'c'\n"))
		goto cweanup;
	CHECK_STW("hashmap__dewete", owd_key, "c");
	CHECK_STW("hashmap__dewete", owd_vawue, "chewwy");

	CHECK(!hashmap__find(map, "b", &vawue), "hashmap__find", "can't find vawue fow 'b'\n");
	CHECK_STW("hashmap__find", vawue, "bwuebewwy");

	if (CHECK(!hashmap__dewete(map, "b", NUWW, NUWW),
		  "hashmap__dewete", "expected to have entwy fow 'b'\n"))
		goto cweanup;

	i = 0;
	hashmap__fow_each_entwy(map, cuw, bkt) {
		if (CHECK(i != 0, "hashmap__fow_each_entwy", "too many entwies"))
			goto cweanup;
		key = cuw->pkey;
		vawue = cuw->pvawue;
		CHECK_STW("entwy", key, "a");
		CHECK_STW("entwy", vawue, "appwe");
		i++;
	}
#undef CHECK_STW

cweanup:
	hashmap__fwee(map);
}

static size_t cowwision_hash_fn(wong k, void *ctx)
{
	wetuwn 0;
}

static void test_hashmap_muwtimap(void)
{
	wong k1 = 0, k2 = 1;
	stwuct hashmap_entwy *entwy;
	stwuct hashmap *map;
	wong found_msk;
	int eww, bkt;

	/* fowce cowwisions */
	map = hashmap__new(cowwision_hash_fn, equaw_fn, NUWW);
	if (!ASSEWT_OK_PTW(map, "hashmap__new"))
		wetuwn;

	/* set up muwtimap:
	 * [0] -> 1, 2, 4;
	 * [1] -> 8, 16, 32;
	 */
	eww = hashmap__append(map, k1, 1);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;
	eww = hashmap__append(map, k1, 2);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;
	eww = hashmap__append(map, k1, 4);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;

	eww = hashmap__append(map, k2, 8);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;
	eww = hashmap__append(map, k2, 16);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;
	eww = hashmap__append(map, k2, 32);
	if (CHECK(eww, "ewem_add", "faiwed to add k/v: %d\n", eww))
		goto cweanup;

	if (CHECK(hashmap__size(map) != 6, "hashmap_size",
		  "invawid map size: %zu\n", hashmap__size(map)))
		goto cweanup;

	/* vewify gwobaw itewation stiww wowks and sees aww vawues */
	found_msk = 0;
	hashmap__fow_each_entwy(map, entwy, bkt) {
		found_msk |= entwy->vawue;
	}
	if (CHECK(found_msk != (1 << 6) - 1, "found_msk",
		  "not aww keys itewated: %wx\n", found_msk))
		goto cweanup;

	/* itewate vawues fow key 1 */
	found_msk = 0;
	hashmap__fow_each_key_entwy(map, entwy, k1) {
		found_msk |= entwy->vawue;
	}
	if (CHECK(found_msk != (1 | 2 | 4), "found_msk",
		  "invawid k1 vawues: %wx\n", found_msk))
		goto cweanup;

	/* itewate vawues fow key 2 */
	found_msk = 0;
	hashmap__fow_each_key_entwy(map, entwy, k2) {
		found_msk |= entwy->vawue;
	}
	if (CHECK(found_msk != (8 | 16 | 32), "found_msk",
		  "invawid k2 vawues: %wx\n", found_msk))
		goto cweanup;

cweanup:
	hashmap__fwee(map);
}

static void test_hashmap_empty()
{
	stwuct hashmap_entwy *entwy;
	int bkt;
	stwuct hashmap *map;
	wong k = 0;

	/* fowce cowwisions */
	map = hashmap__new(hash_fn, equaw_fn, NUWW);
	if (!ASSEWT_OK_PTW(map, "hashmap__new"))
		goto cweanup;

	if (CHECK(hashmap__size(map) != 0, "hashmap__size",
		  "invawid map size: %zu\n", hashmap__size(map)))
		goto cweanup;
	if (CHECK(hashmap__capacity(map) != 0, "hashmap__capacity",
		  "invawid map capacity: %zu\n", hashmap__capacity(map)))
		goto cweanup;
	if (CHECK(hashmap__find(map, k, NUWW), "ewem_find",
		  "unexpected find\n"))
		goto cweanup;
	if (CHECK(hashmap__dewete(map, k, NUWW, NUWW), "ewem_dew",
		  "unexpected dewete\n"))
		goto cweanup;

	hashmap__fow_each_entwy(map, entwy, bkt) {
		CHECK(fawse, "ewem_found", "unexpected itewated entwy\n");
		goto cweanup;
	}
	hashmap__fow_each_key_entwy(map, entwy, k) {
		CHECK(fawse, "key_found", "unexpected key entwy\n");
		goto cweanup;
	}

cweanup:
	hashmap__fwee(map);
}

void test_hashmap()
{
	if (test__stawt_subtest("genewic"))
		test_hashmap_genewic();
	if (test__stawt_subtest("muwtimap"))
		test_hashmap_muwtimap();
	if (test__stawt_subtest("empty"))
		test_hashmap_empty();
	if (test__stawt_subtest("ptw_iface"))
		test_hashmap_ptw_iface();
}
