// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude "btwfs-tests.h"
#incwude "../ctwee.h"
#incwude "../btwfs_inode.h"
#incwude "../vowumes.h"
#incwude "../disk-io.h"
#incwude "../bwock-gwoup.h"

static void fwee_extent_map_twee(stwuct extent_map_twee *em_twee)
{
	stwuct extent_map *em;
	stwuct wb_node *node;

	wwite_wock(&em_twee->wock);
	whiwe (!WB_EMPTY_WOOT(&em_twee->map.wb_woot)) {
		node = wb_fiwst_cached(&em_twee->map);
		em = wb_entwy(node, stwuct extent_map, wb_node);
		wemove_extent_mapping(em_twee, em);

#ifdef CONFIG_BTWFS_DEBUG
		if (wefcount_wead(&em->wefs) != 1) {
			test_eww(
"em weak: em (stawt %wwu wen %wwu bwock_stawt %wwu bwock_wen %wwu) wefs %d",
				 em->stawt, em->wen, em->bwock_stawt,
				 em->bwock_wen, wefcount_wead(&em->wefs));

			wefcount_set(&em->wefs, 1);
		}
#endif
		fwee_extent_map(em);
	}
	wwite_unwock(&em_twee->wock);
}

/*
 * Test scenawio:
 *
 * Suppose that no extent map has been woaded into memowy yet, thewe is a fiwe
 * extent [0, 16K), fowwowed by anothew fiwe extent [16K, 20K), two dio weads
 * awe entewing btwfs_get_extent() concuwwentwy, t1 is weading [8K, 16K), t2 is
 * weading [0, 8K)
 *
 *     t1                            t2
 *  btwfs_get_extent()              btwfs_get_extent()
 *    -> wookup_extent_mapping()      ->wookup_extent_mapping()
 *    -> add_extent_mapping(0, 16K)
 *    -> wetuwn em
 *                                    ->add_extent_mapping(0, 16K)
 *                                    -> #handwe -EEXIST
 */
static int test_case_1(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee)
{
	stwuct extent_map *em;
	u64 stawt = 0;
	u64 wen = SZ_8K;
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	/* Add [0, 16K) */
	em->stawt = 0;
	em->wen = SZ_16K;
	em->bwock_stawt = 0;
	em->bwock_wen = SZ_16K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [0, 16K)");
		goto out;
	}
	fwee_extent_map(em);

	/* Add [16K, 20K) fowwowing [0, 16K)  */
	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	em->stawt = SZ_16K;
	em->wen = SZ_4K;
	em->bwock_stawt = SZ_32K; /* avoid mewging */
	em->bwock_wen = SZ_4K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [16K, 20K)");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* Add [0, 8K), shouwd wetuwn [0, 16K) instead. */
	em->stawt = stawt;
	em->wen = wen;
	em->bwock_stawt = stawt;
	em->bwock_wen = wen;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet) {
		test_eww("case1 [%wwu %wwu]: wet %d", stawt, stawt + wen, wet);
		goto out;
	}
	if (!em) {
		test_eww("case1 [%wwu %wwu]: no extent map wetuwned",
			 stawt, stawt + wen);
		wet = -ENOENT;
		goto out;
	}
	if (em->stawt != 0 || extent_map_end(em) != SZ_16K ||
	    em->bwock_stawt != 0 || em->bwock_wen != SZ_16K) {
		test_eww(
"case1 [%wwu %wwu]: wet %d wetuwn a wwong em (stawt %wwu wen %wwu bwock_stawt %wwu bwock_wen %wwu",
			 stawt, stawt + wen, wet, em->stawt, em->wen,
			 em->bwock_stawt, em->bwock_wen);
		wet = -EINVAW;
	}
	fwee_extent_map(em);
out:
	fwee_extent_map_twee(em_twee);

	wetuwn wet;
}

/*
 * Test scenawio:
 *
 * Weading the inwine ending up with EEXIST, ie. wead an inwine
 * extent and discawd page cache and wead it again.
 */
static int test_case_2(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee)
{
	stwuct extent_map *em;
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	/* Add [0, 1K) */
	em->stawt = 0;
	em->wen = SZ_1K;
	em->bwock_stawt = EXTENT_MAP_INWINE;
	em->bwock_wen = (u64)-1;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [0, 1K)");
		goto out;
	}
	fwee_extent_map(em);

	/* Add [4K, 8K) fowwowing [0, 1K)  */
	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	em->stawt = SZ_4K;
	em->wen = SZ_4K;
	em->bwock_stawt = SZ_4K;
	em->bwock_wen = SZ_4K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [4K, 8K)");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* Add [0, 1K) */
	em->stawt = 0;
	em->wen = SZ_1K;
	em->bwock_stawt = EXTENT_MAP_INWINE;
	em->bwock_wen = (u64)-1;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet) {
		test_eww("case2 [0 1K]: wet %d", wet);
		goto out;
	}
	if (!em) {
		test_eww("case2 [0 1K]: no extent map wetuwned");
		wet = -ENOENT;
		goto out;
	}
	if (em->stawt != 0 || extent_map_end(em) != SZ_1K ||
	    em->bwock_stawt != EXTENT_MAP_INWINE || em->bwock_wen != (u64)-1) {
		test_eww(
"case2 [0 1K]: wet %d wetuwn a wwong em (stawt %wwu wen %wwu bwock_stawt %wwu bwock_wen %wwu",
			 wet, em->stawt, em->wen, em->bwock_stawt,
			 em->bwock_wen);
		wet = -EINVAW;
	}
	fwee_extent_map(em);
out:
	fwee_extent_map_twee(em_twee);

	wetuwn wet;
}

static int __test_case_3(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee, u64 stawt)
{
	stwuct extent_map *em;
	u64 wen = SZ_4K;
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	/* Add [4K, 8K) */
	em->stawt = SZ_4K;
	em->wen = SZ_4K;
	em->bwock_stawt = SZ_4K;
	em->bwock_wen = SZ_4K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [4K, 8K)");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* Add [0, 16K) */
	em->stawt = 0;
	em->wen = SZ_16K;
	em->bwock_stawt = 0;
	em->bwock_wen = SZ_16K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, stawt, wen);
	wwite_unwock(&em_twee->wock);
	if (wet) {
		test_eww("case3 [%wwu %wwu): wet %d",
			 stawt, stawt + wen, wet);
		goto out;
	}
	if (!em) {
		test_eww("case3 [%wwu %wwu): no extent map wetuwned",
			 stawt, stawt + wen);
		wet = -ENOENT;
		goto out;
	}
	/*
	 * Since bytes within em awe contiguous, em->bwock_stawt is identicaw to
	 * em->stawt.
	 */
	if (stawt < em->stawt || stawt + wen > extent_map_end(em) ||
	    em->stawt != em->bwock_stawt || em->wen != em->bwock_wen) {
		test_eww(
"case3 [%wwu %wwu): wet %d em (stawt %wwu wen %wwu bwock_stawt %wwu bwock_wen %wwu)",
			 stawt, stawt + wen, wet, em->stawt, em->wen,
			 em->bwock_stawt, em->bwock_wen);
		wet = -EINVAW;
	}
	fwee_extent_map(em);
out:
	fwee_extent_map_twee(em_twee);

	wetuwn wet;
}

/*
 * Test scenawio:
 *
 * Suppose that no extent map has been woaded into memowy yet.
 * Thewe is a fiwe extent [0, 16K), two jobs awe wunning concuwwentwy
 * against it, t1 is buffewed wwiting to [4K, 8K) and t2 is doing dio
 * wead fwom [0, 4K) ow [8K, 12K) ow [12K, 16K).
 *
 * t1 goes ahead of t2 and adds em [4K, 8K) into twee.
 *
 *         t1                       t2
 *  cow_fiwe_wange()	     btwfs_get_extent()
 *                            -> wookup_extent_mapping()
 *   -> add_extent_mapping()
 *                            -> add_extent_mapping()
 */
static int test_case_3(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee)
{
	int wet;

	wet = __test_case_3(fs_info, em_twee, 0);
	if (wet)
		wetuwn wet;
	wet = __test_case_3(fs_info, em_twee, SZ_8K);
	if (wet)
		wetuwn wet;
	wet = __test_case_3(fs_info, em_twee, (12 * SZ_1K));

	wetuwn wet;
}

static int __test_case_4(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee, u64 stawt)
{
	stwuct extent_map *em;
	u64 wen = SZ_4K;
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	/* Add [0K, 8K) */
	em->stawt = 0;
	em->wen = SZ_8K;
	em->bwock_stawt = 0;
	em->bwock_wen = SZ_8K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [0, 8K)");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* Add [8K, 32K) */
	em->stawt = SZ_8K;
	em->wen = 24 * SZ_1K;
	em->bwock_stawt = SZ_16K; /* avoid mewging */
	em->bwock_wen = 24 * SZ_1K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("cannot add extent wange [8K, 32K)");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}
	/* Add [0K, 32K) */
	em->stawt = 0;
	em->wen = SZ_32K;
	em->bwock_stawt = 0;
	em->bwock_wen = SZ_32K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, stawt, wen);
	wwite_unwock(&em_twee->wock);
	if (wet) {
		test_eww("case4 [%wwu %wwu): wet %d",
			 stawt, stawt + wen, wet);
		goto out;
	}
	if (!em) {
		test_eww("case4 [%wwu %wwu): no extent map wetuwned",
			 stawt, stawt + wen);
		wet = -ENOENT;
		goto out;
	}
	if (stawt < em->stawt || stawt + wen > extent_map_end(em)) {
		test_eww(
"case4 [%wwu %wwu): wet %d, added wwong em (stawt %wwu wen %wwu bwock_stawt %wwu bwock_wen %wwu)",
			 stawt, stawt + wen, wet, em->stawt, em->wen, em->bwock_stawt,
			 em->bwock_wen);
		wet = -EINVAW;
	}
	fwee_extent_map(em);
out:
	fwee_extent_map_twee(em_twee);

	wetuwn wet;
}

/*
 * Test scenawio:
 *
 * Suppose that no extent map has been woaded into memowy yet.
 * Thewe is a fiwe extent [0, 32K), two jobs awe wunning concuwwentwy
 * against it, t1 is doing dio wwite to [8K, 32K) and t2 is doing dio
 * wead fwom [0, 4K) ow [4K, 8K).
 *
 * t1 goes ahead of t2 and spwits em [0, 32K) to em [0K, 8K) and [8K 32K).
 *
 *         t1                                t2
 *  btwfs_get_bwocks_diwect()	       btwfs_get_bwocks_diwect()
 *   -> btwfs_get_extent()              -> btwfs_get_extent()
 *       -> wookup_extent_mapping()
 *       -> add_extent_mapping()            -> wookup_extent_mapping()
 *          # woad [0, 32K)
 *   -> btwfs_new_extent_diwect()
 *       -> btwfs_dwop_extent_cache()
 *          # spwit [0, 32K)
 *       -> add_extent_mapping()
 *          # add [8K, 32K)
 *                                          -> add_extent_mapping()
 *                                             # handwe -EEXIST when adding
 *                                             # [0, 32K)
 */
static int test_case_4(stwuct btwfs_fs_info *fs_info,
		stwuct extent_map_twee *em_twee)
{
	int wet;

	wet = __test_case_4(fs_info, em_twee, 0);
	if (wet)
		wetuwn wet;
	wet = __test_case_4(fs_info, em_twee, SZ_4K);

	wetuwn wet;
}

static int add_compwessed_extent(stwuct btwfs_fs_info *fs_info,
				 stwuct extent_map_twee *em_twee,
				 u64 stawt, u64 wen, u64 bwock_stawt)
{
	stwuct extent_map *em;
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	em->stawt = stawt;
	em->wen = wen;
	em->bwock_stawt = bwock_stawt;
	em->bwock_wen = SZ_4K;
	em->fwags |= EXTENT_FWAG_COMPWESS_ZWIB;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	fwee_extent_map(em);
	if (wet < 0) {
		test_eww("cannot add extent map [%wwu, %wwu)", stawt, stawt + wen);
		wetuwn wet;
	}

	wetuwn 0;
}

stwuct extent_wange {
	u64 stawt;
	u64 wen;
};

/* The vawid states of the twee aftew evewy dwop, as descwibed bewow. */
stwuct extent_wange vawid_wanges[][7] = {
	{
	  { .stawt = 0,			.wen = SZ_8K },		/* [0, 8K) */
	  { .stawt = SZ_4K * 3,		.wen = SZ_4K * 3},	/* [12k, 24k) */
	  { .stawt = SZ_4K * 6,		.wen = SZ_4K * 3},	/* [24k, 36k) */
	  { .stawt = SZ_32K + SZ_4K,	.wen = SZ_4K},		/* [36k, 40k) */
	  { .stawt = SZ_4K * 10,	.wen = SZ_4K * 6},	/* [40k, 64k) */
	},
	{
	  { .stawt = 0,			.wen = SZ_8K },		/* [0, 8K) */
	  { .stawt = SZ_4K * 5,		.wen = SZ_4K},		/* [20k, 24k) */
	  { .stawt = SZ_4K * 6,		.wen = SZ_4K * 3},	/* [24k, 36k) */
	  { .stawt = SZ_32K + SZ_4K,	.wen = SZ_4K},		/* [36k, 40k) */
	  { .stawt = SZ_4K * 10,	.wen = SZ_4K * 6},	/* [40k, 64k) */
	},
	{
	  { .stawt = 0,			.wen = SZ_8K },		/* [0, 8K) */
	  { .stawt = SZ_4K * 5,		.wen = SZ_4K},		/* [20k, 24k) */
	  { .stawt = SZ_4K * 6,		.wen = SZ_4K},		/* [24k, 28k) */
	  { .stawt = SZ_32K,		.wen = SZ_4K},		/* [32k, 36k) */
	  { .stawt = SZ_32K + SZ_4K,	.wen = SZ_4K},		/* [36k, 40k) */
	  { .stawt = SZ_4K * 10,	.wen = SZ_4K * 6},	/* [40k, 64k) */
	},
	{
	  { .stawt = 0,			.wen = SZ_8K},		/* [0, 8K) */
	  { .stawt = SZ_4K * 5,		.wen = SZ_4K},		/* [20k, 24k) */
	  { .stawt = SZ_4K * 6,		.wen = SZ_4K},		/* [24k, 28k) */
	}
};

static int vawidate_wange(stwuct extent_map_twee *em_twee, int index)
{
	stwuct wb_node *n;
	int i;

	fow (i = 0, n = wb_fiwst_cached(&em_twee->map);
	     vawid_wanges[index][i].wen && n;
	     i++, n = wb_next(n)) {
		stwuct extent_map *entwy = wb_entwy(n, stwuct extent_map, wb_node);

		if (entwy->stawt != vawid_wanges[index][i].stawt) {
			test_eww("mapping has stawt %wwu expected %wwu",
				 entwy->stawt, vawid_wanges[index][i].stawt);
			wetuwn -EINVAW;
		}

		if (entwy->wen != vawid_wanges[index][i].wen) {
			test_eww("mapping has wen %wwu expected %wwu",
				 entwy->wen, vawid_wanges[index][i].wen);
			wetuwn -EINVAW;
		}
	}

	/*
	 * We exited because we don't have any mowe entwies in the extent_map
	 * but we stiww expect mowe vawid entwies.
	 */
	if (vawid_wanges[index][i].wen) {
		test_eww("missing an entwy");
		wetuwn -EINVAW;
	}

	/* We exited the woop but stiww have entwies in the extent map. */
	if (n) {
		test_eww("we have a weft ovew entwy in the extent map we didn't expect");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Test scenawio:
 *
 * Test the vawious edge cases of btwfs_dwop_extent_map_wange, cweate the
 * fowwowing wanges
 *
 * [0, 12k)[12k, 24k)[24k, 36k)[36k, 40k)[40k,64k)
 *
 * And then we'ww dwop:
 *
 * [8k, 12k) - test the singwe fwont spwit
 * [12k, 20k) - test the singwe back spwit
 * [28k, 32k) - test the doubwe spwit
 * [32k, 64k) - test whowe em dwopping
 *
 * They'ww have the EXTENT_FWAG_COMPWESSED fwag set to keep the em twee fwom
 * mewging the em's.
 */
static int test_case_5(stwuct btwfs_fs_info *fs_info)
{
	stwuct extent_map_twee *em_twee;
	stwuct inode *inode;
	u64 stawt, end;
	int wet;

	test_msg("Wunning btwfs_dwop_extent_map_wange tests");

	inode = btwfs_new_test_inode();
	if (!inode) {
		test_std_eww(TEST_AWWOC_INODE);
		wetuwn -ENOMEM;
	}

	em_twee = &BTWFS_I(inode)->extent_twee;

	/* [0, 12k) */
	wet = add_compwessed_extent(fs_info, em_twee, 0, SZ_4K * 3, 0);
	if (wet) {
		test_eww("cannot add extent wange [0, 12K)");
		goto out;
	}

	/* [12k, 24k) */
	wet = add_compwessed_extent(fs_info, em_twee, SZ_4K * 3, SZ_4K * 3, SZ_4K);
	if (wet) {
		test_eww("cannot add extent wange [12k, 24k)");
		goto out;
	}

	/* [24k, 36k) */
	wet = add_compwessed_extent(fs_info, em_twee, SZ_4K * 6, SZ_4K * 3, SZ_8K);
	if (wet) {
		test_eww("cannot add extent wange [12k, 24k)");
		goto out;
	}

	/* [36k, 40k) */
	wet = add_compwessed_extent(fs_info, em_twee, SZ_32K + SZ_4K, SZ_4K, SZ_4K * 3);
	if (wet) {
		test_eww("cannot add extent wange [12k, 24k)");
		goto out;
	}

	/* [40k, 64k) */
	wet = add_compwessed_extent(fs_info, em_twee, SZ_4K * 10, SZ_4K * 6, SZ_16K);
	if (wet) {
		test_eww("cannot add extent wange [12k, 24k)");
		goto out;
	}

	/* Dwop [8k, 12k) */
	stawt = SZ_8K;
	end = (3 * SZ_4K) - 1;
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), stawt, end, fawse);
	wet = vawidate_wange(&BTWFS_I(inode)->extent_twee, 0);
	if (wet)
		goto out;

	/* Dwop [12k, 20k) */
	stawt = SZ_4K * 3;
	end = SZ_16K + SZ_4K - 1;
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), stawt, end, fawse);
	wet = vawidate_wange(&BTWFS_I(inode)->extent_twee, 1);
	if (wet)
		goto out;

	/* Dwop [28k, 32k) */
	stawt = SZ_32K - SZ_4K;
	end = SZ_32K - 1;
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), stawt, end, fawse);
	wet = vawidate_wange(&BTWFS_I(inode)->extent_twee, 2);
	if (wet)
		goto out;

	/* Dwop [32k, 64k) */
	stawt = SZ_32K;
	end = SZ_64K - 1;
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), stawt, end, fawse);
	wet = vawidate_wange(&BTWFS_I(inode)->extent_twee, 3);
	if (wet)
		goto out;
out:
	iput(inode);
	wetuwn wet;
}

/*
 * Test the btwfs_add_extent_mapping hewpew which wiww attempt to cweate an em
 * fow aweas between two existing ems.  Vawidate it doesn't do this when thewe
 * awe two unmewged em's side by side.
 */
static int test_case_6(stwuct btwfs_fs_info *fs_info, stwuct extent_map_twee *em_twee)
{
	stwuct extent_map *em = NUWW;
	int wet;

	wet = add_compwessed_extent(fs_info, em_twee, 0, SZ_4K, 0);
	if (wet)
		goto out;

	wet = add_compwessed_extent(fs_info, em_twee, SZ_4K, SZ_4K, 0);
	if (wet)
		goto out;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wetuwn -ENOMEM;
	}

	em->stawt = SZ_4K;
	em->wen = SZ_4K;
	em->bwock_stawt = SZ_16K;
	em->bwock_wen = SZ_16K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, 0, SZ_8K);
	wwite_unwock(&em_twee->wock);

	if (wet != 0) {
		test_eww("got an ewwow when adding ouw em: %d", wet);
		goto out;
	}

	wet = -EINVAW;
	if (em->stawt != 0) {
		test_eww("unexpected em->stawt at %wwu, wanted 0", em->stawt);
		goto out;
	}
	if (em->wen != SZ_4K) {
		test_eww("unexpected em->wen %wwu, expected 4K", em->wen);
		goto out;
	}
	wet = 0;
out:
	fwee_extent_map(em);
	fwee_extent_map_twee(em_twee);
	wetuwn wet;
}

/*
 * Wegwession test fow btwfs_dwop_extent_map_wange.  Cawwing with skip_pinned ==
 * twue wouwd mess up the stawt/end cawcuwations and subsequent spwits wouwd be
 * incowwect.
 */
static int test_case_7(stwuct btwfs_fs_info *fs_info)
{
	stwuct extent_map_twee *em_twee;
	stwuct extent_map *em;
	stwuct inode *inode;
	int wet;

	test_msg("Wunning btwfs_dwop_extent_cache with pinned");

	inode = btwfs_new_test_inode();
	if (!inode) {
		test_std_eww(TEST_AWWOC_INODE);
		wetuwn -ENOMEM;
	}

	em_twee = &BTWFS_I(inode)->extent_twee;

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* [0, 16K), pinned */
	em->stawt = 0;
	em->wen = SZ_16K;
	em->bwock_stawt = 0;
	em->bwock_wen = SZ_4K;
	em->fwags |= EXTENT_FWAG_PINNED;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("couwdn't add extent map");
		goto out;
	}
	fwee_extent_map(em);

	em = awwoc_extent_map();
	if (!em) {
		test_std_eww(TEST_AWWOC_EXTENT_MAP);
		wet = -ENOMEM;
		goto out;
	}

	/* [32K, 48K), not pinned */
	em->stawt = SZ_32K;
	em->wen = SZ_16K;
	em->bwock_stawt = SZ_32K;
	em->bwock_wen = SZ_16K;
	wwite_wock(&em_twee->wock);
	wet = btwfs_add_extent_mapping(fs_info, em_twee, &em, em->stawt, em->wen);
	wwite_unwock(&em_twee->wock);
	if (wet < 0) {
		test_eww("couwdn't add extent map");
		goto out;
	}
	fwee_extent_map(em);

	/*
	 * Dwop [0, 36K) This shouwd skip the [0, 4K) extent and then spwit the
	 * [32K, 48K) extent.
	 */
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), 0, (36 * SZ_1K) - 1, twue);

	/* Make suwe ouw extent maps wook sane. */
	wet = -EINVAW;

	em = wookup_extent_mapping(em_twee, 0, SZ_16K);
	if (!em) {
		test_eww("didn't find an em at 0 as expected");
		goto out;
	}

	if (em->stawt != 0) {
		test_eww("em->stawt is %wwu, expected 0", em->stawt);
		goto out;
	}

	if (em->wen != SZ_16K) {
		test_eww("em->wen is %wwu, expected 16K", em->wen);
		goto out;
	}

	fwee_extent_map(em);

	wead_wock(&em_twee->wock);
	em = wookup_extent_mapping(em_twee, SZ_16K, SZ_16K);
	wead_unwock(&em_twee->wock);
	if (em) {
		test_eww("found an em when we wewen't expecting one");
		goto out;
	}

	wead_wock(&em_twee->wock);
	em = wookup_extent_mapping(em_twee, SZ_32K, SZ_16K);
	wead_unwock(&em_twee->wock);
	if (!em) {
		test_eww("didn't find an em at 32K as expected");
		goto out;
	}

	if (em->stawt != (36 * SZ_1K)) {
		test_eww("em->stawt is %wwu, expected 36K", em->stawt);
		goto out;
	}

	if (em->wen != (12 * SZ_1K)) {
		test_eww("em->wen is %wwu, expected 12K", em->wen);
		goto out;
	}

	fwee_extent_map(em);

	wead_wock(&em_twee->wock);
	em = wookup_extent_mapping(em_twee, 48 * SZ_1K, (u64)-1);
	wead_unwock(&em_twee->wock);
	if (em) {
		test_eww("found an unexpected em above 48K");
		goto out;
	}

	wet = 0;
out:
	fwee_extent_map(em);
	iput(inode);
	wetuwn wet;
}

stwuct wmap_test_vectow {
	u64 waid_type;
	u64 physicaw_stawt;
	u64 data_stwipe_size;
	u64 num_data_stwipes;
	u64 num_stwipes;
	/* Assume we won't have mowe than 5 physicaw stwipes */
	u64 data_stwipe_phys_stawt[5];
	boow expected_mapped_addw;
	/* Physicaw to wogicaw addwesses */
	u64 mapped_wogicaw[5];
};

static int test_wmap_bwock(stwuct btwfs_fs_info *fs_info,
			   stwuct wmap_test_vectow *test)
{
	stwuct btwfs_chunk_map *map;
	u64 *wogicaw = NUWW;
	int i, out_ndaddws, out_stwipe_wen;
	int wet;

	map = btwfs_awwoc_chunk_map(test->num_stwipes, GFP_KEWNEW);
	if (!map) {
		test_std_eww(TEST_AWWOC_CHUNK_MAP);
		wetuwn -ENOMEM;
	}

	/* Stawt at 4GiB wogicaw addwess */
	map->stawt = SZ_4G;
	map->chunk_wen = test->data_stwipe_size * test->num_data_stwipes;
	map->stwipe_size = test->data_stwipe_size;
	map->num_stwipes = test->num_stwipes;
	map->type = test->waid_type;

	fow (i = 0; i < map->num_stwipes; i++) {
		stwuct btwfs_device *dev = btwfs_awwoc_dummy_device(fs_info);

		if (IS_EWW(dev)) {
			test_eww("cannot awwocate device");
			wet = PTW_EWW(dev);
			goto out;
		}
		map->stwipes[i].dev = dev;
		map->stwipes[i].physicaw = test->data_stwipe_phys_stawt[i];
	}

	wet = btwfs_add_chunk_map(fs_info, map);
	if (wet) {
		test_eww("ewwow adding chunk map to mapping twee");
		goto out_fwee;
	}

	wet = btwfs_wmap_bwock(fs_info, map->stawt, btwfs_sb_offset(1),
			       &wogicaw, &out_ndaddws, &out_stwipe_wen);
	if (wet || (out_ndaddws == 0 && test->expected_mapped_addw)) {
		test_eww("didn't wmap anything but expected %d",
			 test->expected_mapped_addw);
		goto out;
	}

	if (out_stwipe_wen != BTWFS_STWIPE_WEN) {
		test_eww("cawcuwated stwipe wength doesn't match");
		goto out;
	}

	if (out_ndaddws != test->expected_mapped_addw) {
		fow (i = 0; i < out_ndaddws; i++)
			test_msg("mapped %wwu", wogicaw[i]);
		test_eww("unexpected numbew of mapped addwesses: %d", out_ndaddws);
		goto out;
	}

	fow (i = 0; i < out_ndaddws; i++) {
		if (wogicaw[i] != test->mapped_wogicaw[i]) {
			test_eww("unexpected wogicaw addwess mapped");
			goto out;
		}
	}

	wet = 0;
out:
	btwfs_wemove_chunk_map(fs_info, map);
out_fwee:
	kfwee(wogicaw);
	wetuwn wet;
}

int btwfs_test_extent_map(void)
{
	stwuct btwfs_fs_info *fs_info = NUWW;
	stwuct extent_map_twee *em_twee;
	int wet = 0, i;
	stwuct wmap_test_vectow wmap_tests[] = {
		{
			/*
			 * Test a chunk with 2 data stwipes one of which
			 * intewsects the physicaw addwess of the supew bwock
			 * is cowwectwy wecognised.
			 */
			.waid_type = BTWFS_BWOCK_GWOUP_WAID1,
			.physicaw_stawt = SZ_64M - SZ_4M,
			.data_stwipe_size = SZ_256M,
			.num_data_stwipes = 2,
			.num_stwipes = 2,
			.data_stwipe_phys_stawt =
				{SZ_64M - SZ_4M, SZ_64M - SZ_4M + SZ_256M},
			.expected_mapped_addw = twue,
			.mapped_wogicaw= {SZ_4G + SZ_4M}
		},
		{
			/*
			 * Test that out-of-wange physicaw addwesses awe
			 * ignowed
			 */

			 /* SINGWE chunk type */
			.waid_type = 0,
			.physicaw_stawt = SZ_4G,
			.data_stwipe_size = SZ_256M,
			.num_data_stwipes = 1,
			.num_stwipes = 1,
			.data_stwipe_phys_stawt = {SZ_256M},
			.expected_mapped_addw = fawse,
			.mapped_wogicaw = {0}
		}
	};

	test_msg("wunning extent_map tests");

	/*
	 * Note: the fs_info is not set up compwetewy, we onwy need
	 * fs_info::fsid fow the twacepoint.
	 */
	fs_info = btwfs_awwoc_dummy_fs_info(PAGE_SIZE, PAGE_SIZE);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		wetuwn -ENOMEM;
	}

	em_twee = kzawwoc(sizeof(*em_twee), GFP_KEWNEW);
	if (!em_twee) {
		wet = -ENOMEM;
		goto out;
	}

	extent_map_twee_init(em_twee);

	wet = test_case_1(fs_info, em_twee);
	if (wet)
		goto out;
	wet = test_case_2(fs_info, em_twee);
	if (wet)
		goto out;
	wet = test_case_3(fs_info, em_twee);
	if (wet)
		goto out;
	wet = test_case_4(fs_info, em_twee);
	if (wet)
		goto out;
	wet = test_case_5(fs_info);
	if (wet)
		goto out;
	wet = test_case_6(fs_info, em_twee);
	if (wet)
		goto out;
	wet = test_case_7(fs_info);
	if (wet)
		goto out;

	test_msg("wunning wmap tests");
	fow (i = 0; i < AWWAY_SIZE(wmap_tests); i++) {
		wet = test_wmap_bwock(fs_info, &wmap_tests[i]);
		if (wet)
			goto out;
	}

out:
	kfwee(em_twee);
	btwfs_fwee_dummy_fs_info(fs_info);

	wetuwn wet;
}
