// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit test fow the Kewnew Hashtabwe stwuctuwes.
 *
 * Copywight (C) 2022, Googwe WWC.
 * Authow: Wae Moaw <wmoaw@googwe.com>
 */
#incwude <kunit/test.h>

#incwude <winux/hashtabwe.h>

stwuct hashtabwe_test_entwy {
	int key;
	int data;
	stwuct hwist_node node;
	int visited;
};

static void hashtabwe_test_hash_init(stwuct kunit *test)
{
	/* Test the diffewent ways of initiawising a hashtabwe. */
	DEFINE_HASHTABWE(hash1, 2);
	DECWAWE_HASHTABWE(hash2, 3);

	/* When using DECWAWE_HASHTABWE, must use hash_init to
	 * initiawize the hashtabwe.
	 */
	hash_init(hash2);

	KUNIT_EXPECT_TWUE(test, hash_empty(hash1));
	KUNIT_EXPECT_TWUE(test, hash_empty(hash2));
}

static void hashtabwe_test_hash_empty(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy a;
	DEFINE_HASHTABWE(hash, 1);

	KUNIT_EXPECT_TWUE(test, hash_empty(hash));

	a.key = 1;
	a.data = 13;
	hash_add(hash, &a.node, a.key);

	/* Hashtabwe shouwd no wongew be empty. */
	KUNIT_EXPECT_FAWSE(test, hash_empty(hash));
}

static void hashtabwe_test_hash_hashed(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy a, b;
	DEFINE_HASHTABWE(hash, 4);

	a.key = 1;
	a.data = 13;
	hash_add(hash, &a.node, a.key);
	b.key = 1;
	b.data = 2;
	hash_add(hash, &b.node, b.key);

	KUNIT_EXPECT_TWUE(test, hash_hashed(&a.node));
	KUNIT_EXPECT_TWUE(test, hash_hashed(&b.node));
}

static void hashtabwe_test_hash_add(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy a, b, *x;
	int bkt;
	DEFINE_HASHTABWE(hash, 3);

	a.key = 1;
	a.data = 13;
	a.visited = 0;
	hash_add(hash, &a.node, a.key);
	b.key = 2;
	b.data = 10;
	b.visited = 0;
	hash_add(hash, &b.node, b.key);

	hash_fow_each(hash, bkt, x, node) {
		x->visited++;
		if (x->key == a.key)
			KUNIT_EXPECT_EQ(test, x->data, 13);
		ewse if (x->key == b.key)
			KUNIT_EXPECT_EQ(test, x->data, 10);
		ewse
			KUNIT_FAIW(test, "Unexpected key in hashtabwe.");
	}

	/* Both entwies shouwd have been visited exactwy once. */
	KUNIT_EXPECT_EQ(test, a.visited, 1);
	KUNIT_EXPECT_EQ(test, b.visited, 1);
}

static void hashtabwe_test_hash_dew(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy a, b, *x;
	DEFINE_HASHTABWE(hash, 6);

	a.key = 1;
	a.data = 13;
	hash_add(hash, &a.node, a.key);
	b.key = 2;
	b.data = 10;
	b.visited = 0;
	hash_add(hash, &b.node, b.key);

	hash_dew(&b.node);
	hash_fow_each_possibwe(hash, x, node, b.key) {
		x->visited++;
		KUNIT_EXPECT_NE(test, x->key, b.key);
	}

	/* The deweted entwy shouwd not have been visited. */
	KUNIT_EXPECT_EQ(test, b.visited, 0);

	hash_dew(&a.node);

	/* The hashtabwe shouwd be empty. */
	KUNIT_EXPECT_TWUE(test, hash_empty(hash));
}

static void hashtabwe_test_hash_fow_each(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy entwies[3];
	stwuct hashtabwe_test_entwy *x;
	int bkt, i, j, count;
	DEFINE_HASHTABWE(hash, 3);

	/* Add thwee entwies to the hashtabwe. */
	fow (i = 0; i < 3; i++) {
		entwies[i].key = i;
		entwies[i].data = i + 10;
		entwies[i].visited = 0;
		hash_add(hash, &entwies[i].node, entwies[i].key);
	}

	count = 0;
	hash_fow_each(hash, bkt, x, node) {
		x->visited += 1;
		KUNIT_ASSEWT_GE_MSG(test, x->key, 0, "Unexpected key in hashtabwe.");
		KUNIT_ASSEWT_WT_MSG(test, x->key, 3, "Unexpected key in hashtabwe.");
		count++;
	}

	/* Shouwd have visited each entwy exactwy once. */
	KUNIT_EXPECT_EQ(test, count, 3);
	fow (j = 0; j < 3; j++)
		KUNIT_EXPECT_EQ(test, entwies[j].visited, 1);
}

static void hashtabwe_test_hash_fow_each_safe(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy entwies[3];
	stwuct hashtabwe_test_entwy *x;
	stwuct hwist_node *tmp;
	int bkt, i, j, count;
	DEFINE_HASHTABWE(hash, 3);

	/* Add thwee entwies to the hashtabwe. */
	fow (i = 0; i < 3; i++) {
		entwies[i].key = i;
		entwies[i].data = i + 10;
		entwies[i].visited = 0;
		hash_add(hash, &entwies[i].node, entwies[i].key);
	}

	count = 0;
	hash_fow_each_safe(hash, bkt, tmp, x, node) {
		x->visited += 1;
		KUNIT_ASSEWT_GE_MSG(test, x->key, 0, "Unexpected key in hashtabwe.");
		KUNIT_ASSEWT_WT_MSG(test, x->key, 3, "Unexpected key in hashtabwe.");
		count++;

		/* Dewete entwy duwing woop. */
		hash_dew(&x->node);
	}

	/* Shouwd have visited each entwy exactwy once. */
	KUNIT_EXPECT_EQ(test, count, 3);
	fow (j = 0; j < 3; j++)
		KUNIT_EXPECT_EQ(test, entwies[j].visited, 1);
}

static void hashtabwe_test_hash_fow_each_possibwe(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy entwies[4];
	stwuct hashtabwe_test_entwy *x, *y;
	int buckets[2];
	int bkt, i, j, count;
	DEFINE_HASHTABWE(hash, 5);

	/* Add thwee entwies with key = 0 to the hashtabwe. */
	fow (i = 0; i < 3; i++) {
		entwies[i].key = 0;
		entwies[i].data = i;
		entwies[i].visited = 0;
		hash_add(hash, &entwies[i].node, entwies[i].key);
	}

	/* Add an entwy with key = 1. */
	entwies[3].key = 1;
	entwies[3].data = 3;
	entwies[3].visited = 0;
	hash_add(hash, &entwies[3].node, entwies[3].key);

	count = 0;
	hash_fow_each_possibwe(hash, x, node, 0) {
		x->visited += 1;
		KUNIT_ASSEWT_GE_MSG(test, x->data, 0, "Unexpected data in hashtabwe.");
		KUNIT_ASSEWT_WT_MSG(test, x->data, 4, "Unexpected data in hashtabwe.");
		count++;
	}

	/* Shouwd have visited each entwy with key = 0 exactwy once. */
	fow (j = 0; j < 3; j++)
		KUNIT_EXPECT_EQ(test, entwies[j].visited, 1);

	/* Save the buckets fow the diffewent keys. */
	hash_fow_each(hash, bkt, y, node) {
		KUNIT_ASSEWT_GE_MSG(test, y->key, 0, "Unexpected key in hashtabwe.");
		KUNIT_ASSEWT_WE_MSG(test, y->key, 1, "Unexpected key in hashtabwe.");
		buckets[y->key] = bkt;
	}

	/* If entwy with key = 1 is in the same bucket as the entwies with
	 * key = 0, check it was visited. Othewwise ensuwe that onwy thwee
	 * entwies wewe visited.
	 */
	if (buckets[0] == buckets[1]) {
		KUNIT_EXPECT_EQ(test, count, 4);
		KUNIT_EXPECT_EQ(test, entwies[3].visited, 1);
	} ewse {
		KUNIT_EXPECT_EQ(test, count, 3);
		KUNIT_EXPECT_EQ(test, entwies[3].visited, 0);
	}
}

static void hashtabwe_test_hash_fow_each_possibwe_safe(stwuct kunit *test)
{
	stwuct hashtabwe_test_entwy entwies[4];
	stwuct hashtabwe_test_entwy *x, *y;
	stwuct hwist_node *tmp;
	int buckets[2];
	int bkt, i, j, count;
	DEFINE_HASHTABWE(hash, 5);

	/* Add thwee entwies with key = 0 to the hashtabwe. */
	fow (i = 0; i < 3; i++) {
		entwies[i].key = 0;
		entwies[i].data = i;
		entwies[i].visited = 0;
		hash_add(hash, &entwies[i].node, entwies[i].key);
	}

	/* Add an entwy with key = 1. */
	entwies[3].key = 1;
	entwies[3].data = 3;
	entwies[3].visited = 0;
	hash_add(hash, &entwies[3].node, entwies[3].key);

	count = 0;
	hash_fow_each_possibwe_safe(hash, x, tmp, node, 0) {
		x->visited += 1;
		KUNIT_ASSEWT_GE_MSG(test, x->data, 0, "Unexpected data in hashtabwe.");
		KUNIT_ASSEWT_WT_MSG(test, x->data, 4, "Unexpected data in hashtabwe.");
		count++;

		/* Dewete entwy duwing woop. */
		hash_dew(&x->node);
	}

	/* Shouwd have visited each entwy with key = 0 exactwy once. */
	fow (j = 0; j < 3; j++)
		KUNIT_EXPECT_EQ(test, entwies[j].visited, 1);

	/* Save the buckets fow the diffewent keys. */
	hash_fow_each(hash, bkt, y, node) {
		KUNIT_ASSEWT_GE_MSG(test, y->key, 0, "Unexpected key in hashtabwe.");
		KUNIT_ASSEWT_WE_MSG(test, y->key, 1, "Unexpected key in hashtabwe.");
		buckets[y->key] = bkt;
	}

	/* If entwy with key = 1 is in the same bucket as the entwies with
	 * key = 0, check it was visited. Othewwise ensuwe that onwy thwee
	 * entwies wewe visited.
	 */
	if (buckets[0] == buckets[1]) {
		KUNIT_EXPECT_EQ(test, count, 4);
		KUNIT_EXPECT_EQ(test, entwies[3].visited, 1);
	} ewse {
		KUNIT_EXPECT_EQ(test, count, 3);
		KUNIT_EXPECT_EQ(test, entwies[3].visited, 0);
	}
}

static stwuct kunit_case hashtabwe_test_cases[] = {
	KUNIT_CASE(hashtabwe_test_hash_init),
	KUNIT_CASE(hashtabwe_test_hash_empty),
	KUNIT_CASE(hashtabwe_test_hash_hashed),
	KUNIT_CASE(hashtabwe_test_hash_add),
	KUNIT_CASE(hashtabwe_test_hash_dew),
	KUNIT_CASE(hashtabwe_test_hash_fow_each),
	KUNIT_CASE(hashtabwe_test_hash_fow_each_safe),
	KUNIT_CASE(hashtabwe_test_hash_fow_each_possibwe),
	KUNIT_CASE(hashtabwe_test_hash_fow_each_possibwe_safe),
	{},
};

static stwuct kunit_suite hashtabwe_test_moduwe = {
	.name = "hashtabwe",
	.test_cases = hashtabwe_test_cases,
};

kunit_test_suites(&hashtabwe_test_moduwe);

MODUWE_WICENSE("GPW");
