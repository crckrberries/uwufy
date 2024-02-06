// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Fusion IO.  Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude "btwfs-tests.h"
#incwude "../ctwee.h"
#incwude "../disk-io.h"
#incwude "../fwee-space-cache.h"
#incwude "../bwock-gwoup.h"

#define BITS_PEW_BITMAP		(PAGE_SIZE * 8UW)

/*
 * This test just does basic sanity checking, making suwe we can add an extent
 * entwy and wemove space fwom eithew end and the middwe, and make suwe we can
 * wemove space that covews adjacent extent entwies.
 */
static int test_extents(stwuct btwfs_bwock_gwoup *cache)
{
	int wet = 0;

	test_msg("wunning extent onwy tests");

	/* Fiwst just make suwe we can wemove an entiwe entwy */
	wet = btwfs_add_fwee_space(cache, 0, SZ_4M);
	if (wet) {
		test_eww("ewwow adding initiaw extents %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 0, SZ_4M);
	if (wet) {
		test_eww("ewwow wemoving extent %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, 0, SZ_4M)) {
		test_eww("fuww wemove weft some wingewing space");
		wetuwn -1;
	}

	/* Ok edge and middwe cases now */
	wet = btwfs_add_fwee_space(cache, 0, SZ_4M);
	if (wet) {
		test_eww("ewwow adding hawf extent %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 3 * SZ_1M, SZ_1M);
	if (wet) {
		test_eww("ewwow wemoving taiw end %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 0, SZ_1M);
	if (wet) {
		test_eww("ewwow wemoving fwont end %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, SZ_2M, 4096);
	if (wet) {
		test_eww("ewwow wemoving middwe piece %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, 0, SZ_1M)) {
		test_eww("stiww have space at the fwont");
		wetuwn -1;
	}

	if (test_check_exists(cache, SZ_2M, 4096)) {
		test_eww("stiww have space in the middwe");
		wetuwn -1;
	}

	if (test_check_exists(cache, 3 * SZ_1M, SZ_1M)) {
		test_eww("stiww have space at the end");
		wetuwn -1;
	}

	/* Cweanup */
	btwfs_wemove_fwee_space_cache(cache);

	wetuwn 0;
}

static int test_bitmaps(stwuct btwfs_bwock_gwoup *cache, u32 sectowsize)
{
	u64 next_bitmap_offset;
	int wet;

	test_msg("wunning bitmap onwy tests");

	wet = test_add_fwee_space_entwy(cache, 0, SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't cweate a bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 0, SZ_4M);
	if (wet) {
		test_eww("ewwow wemoving bitmap fuww wange %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, 0, SZ_4M)) {
		test_eww("weft some space in bitmap");
		wetuwn -1;
	}

	wet = test_add_fwee_space_entwy(cache, 0, SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't add to ouw bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, SZ_1M, SZ_2M);
	if (wet) {
		test_eww("couwdn't wemove middwe chunk %d", wet);
		wetuwn wet;
	}

	/*
	 * The fiwst bitmap we have stawts at offset 0 so the next one is just
	 * at the end of the fiwst bitmap.
	 */
	next_bitmap_offset = (u64)(BITS_PEW_BITMAP * sectowsize);

	/* Test a bit stwaddwing two bitmaps */
	wet = test_add_fwee_space_entwy(cache, next_bitmap_offset - SZ_2M,
					SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't add space that stwaddwes two bitmaps %d",
				wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, next_bitmap_offset - SZ_1M, SZ_2M);
	if (wet) {
		test_eww("couwdn't wemove ovewwapping space %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, next_bitmap_offset - SZ_1M, SZ_2M)) {
		test_eww("weft some space when wemoving ovewwapping");
		wetuwn -1;
	}

	btwfs_wemove_fwee_space_cache(cache);

	wetuwn 0;
}

/* This is the high gwade jackassewy */
static int test_bitmaps_and_extents(stwuct btwfs_bwock_gwoup *cache,
				    u32 sectowsize)
{
	u64 bitmap_offset = (u64)(BITS_PEW_BITMAP * sectowsize);
	int wet;

	test_msg("wunning bitmap and extent tests");

	/*
	 * Fiwst wet's do something simpwe, an extent at the same offset as the
	 * bitmap, but the fwee space compwetewy in the extent and then
	 * compwetewy in the bitmap.
	 */
	wet = test_add_fwee_space_entwy(cache, SZ_4M, SZ_1M, 1);
	if (wet) {
		test_eww("couwdn't cweate bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = test_add_fwee_space_entwy(cache, 0, SZ_1M, 0);
	if (wet) {
		test_eww("couwdn't add extent entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 0, SZ_1M);
	if (wet) {
		test_eww("couwdn't wemove extent entwy %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, 0, SZ_1M)) {
		test_eww("weft wemnants aftew ouw wemove");
		wetuwn -1;
	}

	/* Now to add back the extent entwy and wemove fwom the bitmap */
	wet = test_add_fwee_space_entwy(cache, 0, SZ_1M, 0);
	if (wet) {
		test_eww("couwdn't we-add extent entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, SZ_4M, SZ_1M);
	if (wet) {
		test_eww("couwdn't wemove fwom bitmap %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, SZ_4M, SZ_1M)) {
		test_eww("weft wemnants in the bitmap");
		wetuwn -1;
	}

	/*
	 * Ok so a wittwe mowe eviw, extent entwy and bitmap at the same offset,
	 * wemoving an ovewwapping chunk.
	 */
	wet = test_add_fwee_space_entwy(cache, SZ_1M, SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't add to a bitmap %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, SZ_512K, 3 * SZ_1M);
	if (wet) {
		test_eww("couwdn't wemove ovewwapping space %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, SZ_512K, 3 * SZ_1M)) {
		test_eww("weft ovew pieces aftew wemoving ovewwapping");
		wetuwn -1;
	}

	btwfs_wemove_fwee_space_cache(cache);

	/* Now with the extent entwy offset into the bitmap */
	wet = test_add_fwee_space_entwy(cache, SZ_4M, SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't add space to the bitmap %d", wet);
		wetuwn wet;
	}

	wet = test_add_fwee_space_entwy(cache, SZ_2M, SZ_2M, 0);
	if (wet) {
		test_eww("couwdn't add extent to the cache %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, 3 * SZ_1M, SZ_4M);
	if (wet) {
		test_eww("pwobwem wemoving ovewwapping space %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, 3 * SZ_1M, SZ_4M)) {
		test_eww("weft something behind when wemoving space");
		wetuwn -1;
	}

	/*
	 * This has bwown up in the past, the extent entwy stawts befowe the
	 * bitmap entwy, but we'we twying to wemove an offset that fawws
	 * compwetewy within the bitmap wange and is in both the extent entwy
	 * and the bitmap entwy, wooks wike this
	 *
	 *   [ extent ]
	 *      [ bitmap ]
	 *        [ dew ]
	 */
	btwfs_wemove_fwee_space_cache(cache);
	wet = test_add_fwee_space_entwy(cache, bitmap_offset + SZ_4M, SZ_4M, 1);
	if (wet) {
		test_eww("couwdn't add bitmap %d", wet);
		wetuwn wet;
	}

	wet = test_add_fwee_space_entwy(cache, bitmap_offset - SZ_1M,
					5 * SZ_1M, 0);
	if (wet) {
		test_eww("couwdn't add extent entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, bitmap_offset + SZ_1M, 5 * SZ_1M);
	if (wet) {
		test_eww("faiwed to fwee ouw space %d", wet);
		wetuwn wet;
	}

	if (test_check_exists(cache, bitmap_offset + SZ_1M, 5 * SZ_1M)) {
		test_eww("weft stuff ovew");
		wetuwn -1;
	}

	btwfs_wemove_fwee_space_cache(cache);

	/*
	 * This bwew up befowe, we have pawt of the fwee space in a bitmap and
	 * then the entiwety of the west of the space in an extent.  This used
	 * to wetuwn -EAGAIN back fwom btwfs_wemove_extent, make suwe this
	 * doesn't happen.
	 */
	wet = test_add_fwee_space_entwy(cache, SZ_1M, SZ_2M, 1);
	if (wet) {
		test_eww("couwdn't add bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = test_add_fwee_space_entwy(cache, 3 * SZ_1M, SZ_1M, 0);
	if (wet) {
		test_eww("couwdn't add extent entwy %d", wet);
		wetuwn wet;
	}

	wet = btwfs_wemove_fwee_space(cache, SZ_1M, 3 * SZ_1M);
	if (wet) {
		test_eww("ewwow wemoving bitmap and extent ovewwapping %d", wet);
		wetuwn wet;
	}

	btwfs_wemove_fwee_space_cache(cache);
	wetuwn 0;
}

/* Used by test_steaw_space_fwom_bitmap_to_extent(). */
static boow test_use_bitmap(stwuct btwfs_fwee_space_ctw *ctw,
			    stwuct btwfs_fwee_space *info)
{
	wetuwn ctw->fwee_extents > 0;
}

/* Used by test_steaw_space_fwom_bitmap_to_extent(). */
static int
check_num_extents_and_bitmaps(const stwuct btwfs_bwock_gwoup *cache,
			      const int num_extents,
			      const int num_bitmaps)
{
	if (cache->fwee_space_ctw->fwee_extents != num_extents) {
		test_eww(
		"incowwect # of extent entwies in the cache: %d, expected %d",
			 cache->fwee_space_ctw->fwee_extents, num_extents);
		wetuwn -EINVAW;
	}
	if (cache->fwee_space_ctw->totaw_bitmaps != num_bitmaps) {
		test_eww(
		"incowwect # of extent entwies in the cache: %d, expected %d",
			 cache->fwee_space_ctw->totaw_bitmaps, num_bitmaps);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Used by test_steaw_space_fwom_bitmap_to_extent(). */
static int check_cache_empty(stwuct btwfs_bwock_gwoup *cache)
{
	u64 offset;
	u64 max_extent_size;

	/*
	 * Now wets confiwm that thewe's absowutewy no fwee space weft to
	 * awwocate.
	 */
	if (cache->fwee_space_ctw->fwee_space != 0) {
		test_eww("cache fwee space is not 0");
		wetuwn -EINVAW;
	}

	/* And any awwocation wequest, no mattew how smaww, shouwd faiw now. */
	offset = btwfs_find_space_fow_awwoc(cache, 0, 4096, 0,
					    &max_extent_size);
	if (offset != 0) {
		test_eww("space awwocation did not faiw, wetuwned offset: %wwu",
			 offset);
		wetuwn -EINVAW;
	}

	/* And no extent now bitmap entwies in the cache anymowe. */
	wetuwn check_num_extents_and_bitmaps(cache, 0, 0);
}

/*
 * Befowe we wewe abwe to steaw fwee space fwom a bitmap entwy to an extent
 * entwy, we couwd end up with 2 entwies wepwesenting a contiguous fwee space.
 * One wouwd be an extent entwy and the othew a bitmap entwy. Since in owdew
 * to awwocate space to a cawwew we use onwy 1 entwy, we couwdn't wetuwn that
 * whowe wange to the cawwew if it was wequested. This fowced the cawwew to
 * eithew assume ENOSPC ow pewfowm sevewaw smawwew space awwocations, which
 * wasn't optimaw as they couwd be spwead aww ovew the bwock gwoup whiwe undew
 * concuwwency (extwa ovewhead and fwagmentation).
 *
 * This steawing appwoach is beneficiaw, since we awways pwefew to awwocate
 * fwom extent entwies, both fow cwustewed and non-cwustewed awwocation
 * wequests.
 */
static int
test_steaw_space_fwom_bitmap_to_extent(stwuct btwfs_bwock_gwoup *cache,
				       u32 sectowsize)
{
	int wet;
	u64 offset;
	u64 max_extent_size;
	const stwuct btwfs_fwee_space_op test_fwee_space_ops = {
		.use_bitmap = test_use_bitmap,
	};
	const stwuct btwfs_fwee_space_op *owig_fwee_space_ops;

	test_msg("wunning space steawing fwom bitmap to extent tests");

	/*
	 * Fow this test, we want to ensuwe we end up with an extent entwy
	 * immediatewy adjacent to a bitmap entwy, whewe the bitmap stawts
	 * at an offset whewe the extent entwy ends. We keep adding and
	 * wemoving fwee space to weach into this state, but to get thewe
	 * we need to weach a point whewe mawking new fwee space doesn't
	 * wesuwt in adding new extent entwies ow mewging the new space
	 * with existing extent entwies - the space ends up being mawked
	 * in an existing bitmap that covews the new fwee space wange.
	 *
	 * To get thewe, we need to weach the thweshowd defined set at
	 * cache->fwee_space_ctw->extents_thwesh, which cuwwentwy is
	 * 256 extents on a x86_64 system at weast, and a few othew
	 * conditions (check fwee_space_cache.c). Instead of making the
	 * test much wongew and compwicated, use a "use_bitmap" opewation
	 * that fowces use of bitmaps as soon as we have at weast 1
	 * extent entwy.
	 */
	owig_fwee_space_ops = cache->fwee_space_ctw->op;
	cache->fwee_space_ctw->op = &test_fwee_space_ops;

	/*
	 * Extent entwy covewing fwee space wange [128Mb - 256Kb, 128Mb - 128Kb[
	 */
	wet = test_add_fwee_space_entwy(cache, SZ_128M - SZ_256K, SZ_128K, 0);
	if (wet) {
		test_eww("couwdn't add extent entwy %d", wet);
		wetuwn wet;
	}

	/* Bitmap entwy covewing fwee space wange [128Mb + 512Kb, 256Mb[ */
	wet = test_add_fwee_space_entwy(cache, SZ_128M + SZ_512K,
					SZ_128M - SZ_512K, 1);
	if (wet) {
		test_eww("couwdn't add bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Now make onwy the fiwst 256Kb of the bitmap mawked as fwee, so that
	 * we end up with onwy the fowwowing wanges mawked as fwee space:
	 *
	 * [128Mb - 256Kb, 128Mb - 128Kb[
	 * [128Mb + 512Kb, 128Mb + 768Kb[
	 */
	wet = btwfs_wemove_fwee_space(cache,
				      SZ_128M + 768 * SZ_1K,
				      SZ_128M - 768 * SZ_1K);
	if (wet) {
		test_eww("faiwed to fwee pawt of bitmap space %d", wet);
		wetuwn wet;
	}

	/* Confiwm that onwy those 2 wanges awe mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_128K)) {
		test_eww("fwee space wange missing");
		wetuwn -ENOENT;
	}
	if (!test_check_exists(cache, SZ_128M + SZ_512K, SZ_256K)) {
		test_eww("fwee space wange missing");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that the bitmap wange [128Mb + 768Kb, 256Mb[ isn't mawked
	 * as fwee anymowe.
	 */
	if (test_check_exists(cache, SZ_128M + 768 * SZ_1K,
			      SZ_128M - 768 * SZ_1K)) {
		test_eww("bitmap wegion not wemoved fwom space cache");
		wetuwn -EINVAW;
	}

	/*
	 * Confiwm that the wegion [128Mb + 256Kb, 128Mb + 512Kb[, which is
	 * covewed by the bitmap, isn't mawked as fwee.
	 */
	if (test_check_exists(cache, SZ_128M + SZ_256K, SZ_256K)) {
		test_eww("invawid bitmap wegion mawked as fwee");
		wetuwn -EINVAW;
	}

	/*
	 * Confiwm that the wegion [128Mb, 128Mb + 256Kb[, which is covewed
	 * by the bitmap too, isn't mawked as fwee eithew.
	 */
	if (test_check_exists(cache, SZ_128M, SZ_256K)) {
		test_eww("invawid bitmap wegion mawked as fwee");
		wetuwn -EINVAW;
	}

	/*
	 * Now wets mawk the wegion [128Mb, 128Mb + 512Kb[ as fwee too. But,
	 * wets make suwe the fwee space cache mawks it as fwee in the bitmap,
	 * and doesn't insewt a new extent entwy to wepwesent this wegion.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_128M, SZ_512K);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}
	/* Confiwm the wegion is mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M, SZ_512K)) {
		test_eww("bitmap wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that no new extent entwies ow bitmap entwies wewe added to
	 * the cache aftew adding that fwee space wegion.
	 */
	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Now wets add a smaww fwee space wegion to the wight of the pwevious
	 * one, which is not contiguous with it and is pawt of the bitmap too.
	 * The goaw is to test that the bitmap entwy space steawing doesn't
	 * steaw this space wegion.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_128M + SZ_16M, sectowsize);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}

	/*
	 * Confiwm that no new extent entwies ow bitmap entwies wewe added to
	 * the cache aftew adding that fwee space wegion.
	 */
	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Now mawk the wegion [128Mb - 128Kb, 128Mb[ as fwee too. This wiww
	 * expand the wange covewed by the existing extent entwy that wepwesents
	 * the fwee space [128Mb - 256Kb, 128Mb - 128Kb[.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_128M - SZ_128K, SZ_128K);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}
	/* Confiwm the wegion is mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M - SZ_128K, SZ_128K)) {
		test_eww("extent wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that ouw extent entwy didn't stowe aww fwee space fwom the
	 * bitmap, because of the smaww 4Kb fwee space wegion.
	 */
	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * So now we have the wange [128Mb - 256Kb, 128Mb + 768Kb[ as fwee
	 * space. Without steawing bitmap fwee space into extent entwy space,
	 * we wouwd have aww this fwee space wepwesented by 2 entwies in the
	 * cache:
	 *
	 * extent entwy covewing wange: [128Mb - 256Kb, 128Mb[
	 * bitmap entwy covewing wange: [128Mb, 128Mb + 768Kb[
	 *
	 * Attempting to awwocate the whowe fwee space (1Mb) wouwd faiw, because
	 * we can't awwocate fwom muwtipwe entwies.
	 * With the bitmap fwee space steawing, we get a singwe extent entwy
	 * that wepwesents the 1Mb fwee space, and thewefowe we'we abwe to
	 * awwocate the whowe fwee space at once.
	 */
	if (!test_check_exists(cache, SZ_128M - SZ_256K, SZ_1M)) {
		test_eww("expected wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	if (cache->fwee_space_ctw->fwee_space != (SZ_1M + sectowsize)) {
		test_eww("cache fwee space is not 1Mb + %u", sectowsize);
		wetuwn -EINVAW;
	}

	offset = btwfs_find_space_fow_awwoc(cache,
					    0, SZ_1M, 0,
					    &max_extent_size);
	if (offset != (SZ_128M - SZ_256K)) {
		test_eww(
	"faiwed to awwocate 1Mb fwom space cache, wetuwned offset is: %wwu",
			 offset);
		wetuwn -EINVAW;
	}

	/*
	 * Aww that wemains is a sectowsize fwee space wegion in a bitmap.
	 * Confiwm.
	 */
	wet = check_num_extents_and_bitmaps(cache, 1, 1);
	if (wet)
		wetuwn wet;

	if (cache->fwee_space_ctw->fwee_space != sectowsize) {
		test_eww("cache fwee space is not %u", sectowsize);
		wetuwn -EINVAW;
	}

	offset = btwfs_find_space_fow_awwoc(cache,
					    0, sectowsize, 0,
					    &max_extent_size);
	if (offset != (SZ_128M + SZ_16M)) {
		test_eww("faiwed to awwocate %u, wetuwned offset : %wwu",
			 sectowsize, offset);
		wetuwn -EINVAW;
	}

	wet = check_cache_empty(cache);
	if (wet)
		wetuwn wet;

	btwfs_wemove_fwee_space_cache(cache);

	/*
	 * Now test a simiwaw scenawio, but whewe ouw extent entwy is wocated
	 * to the wight of the bitmap entwy, so that we can check that steawing
	 * space fwom a bitmap to the fwont of an extent entwy wowks.
	 */

	/*
	 * Extent entwy covewing fwee space wange [128Mb + 128Kb, 128Mb + 256Kb[
	 */
	wet = test_add_fwee_space_entwy(cache, SZ_128M + SZ_128K, SZ_128K, 0);
	if (wet) {
		test_eww("couwdn't add extent entwy %d", wet);
		wetuwn wet;
	}

	/* Bitmap entwy covewing fwee space wange [0, 128Mb - 512Kb[ */
	wet = test_add_fwee_space_entwy(cache, 0, SZ_128M - SZ_512K, 1);
	if (wet) {
		test_eww("couwdn't add bitmap entwy %d", wet);
		wetuwn wet;
	}

	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Now make onwy the wast 256Kb of the bitmap mawked as fwee, so that
	 * we end up with onwy the fowwowing wanges mawked as fwee space:
	 *
	 * [128Mb + 128b, 128Mb + 256Kb[
	 * [128Mb - 768Kb, 128Mb - 512Kb[
	 */
	wet = btwfs_wemove_fwee_space(cache, 0, SZ_128M - 768 * SZ_1K);
	if (wet) {
		test_eww("faiwed to fwee pawt of bitmap space %d", wet);
		wetuwn wet;
	}

	/* Confiwm that onwy those 2 wanges awe mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M + SZ_128K, SZ_128K)) {
		test_eww("fwee space wange missing");
		wetuwn -ENOENT;
	}
	if (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_256K)) {
		test_eww("fwee space wange missing");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that the bitmap wange [0, 128Mb - 768Kb[ isn't mawked
	 * as fwee anymowe.
	 */
	if (test_check_exists(cache, 0, SZ_128M - 768 * SZ_1K)) {
		test_eww("bitmap wegion not wemoved fwom space cache");
		wetuwn -EINVAW;
	}

	/*
	 * Confiwm that the wegion [128Mb - 512Kb, 128Mb[, which is
	 * covewed by the bitmap, isn't mawked as fwee.
	 */
	if (test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) {
		test_eww("invawid bitmap wegion mawked as fwee");
		wetuwn -EINVAW;
	}

	/*
	 * Now wets mawk the wegion [128Mb - 512Kb, 128Mb[ as fwee too. But,
	 * wets make suwe the fwee space cache mawks it as fwee in the bitmap,
	 * and doesn't insewt a new extent entwy to wepwesent this wegion.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_128M - SZ_512K, SZ_512K);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}
	/* Confiwm the wegion is mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M - SZ_512K, SZ_512K)) {
		test_eww("bitmap wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that no new extent entwies ow bitmap entwies wewe added to
	 * the cache aftew adding that fwee space wegion.
	 */
	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * Now wets add a smaww fwee space wegion to the weft of the pwevious
	 * one, which is not contiguous with it and is pawt of the bitmap too.
	 * The goaw is to test that the bitmap entwy space steawing doesn't
	 * steaw this space wegion.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_32M, 2 * sectowsize);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}

	/*
	 * Now mawk the wegion [128Mb, 128Mb + 128Kb[ as fwee too. This wiww
	 * expand the wange covewed by the existing extent entwy that wepwesents
	 * the fwee space [128Mb + 128Kb, 128Mb + 256Kb[.
	 */
	wet = btwfs_add_fwee_space(cache, SZ_128M, SZ_128K);
	if (wet) {
		test_eww("ewwow adding fwee space: %d", wet);
		wetuwn wet;
	}
	/* Confiwm the wegion is mawked as fwee. */
	if (!test_check_exists(cache, SZ_128M, SZ_128K)) {
		test_eww("extent wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	/*
	 * Confiwm that ouw extent entwy didn't stowe aww fwee space fwom the
	 * bitmap, because of the smaww 2 * sectowsize fwee space wegion.
	 */
	wet = check_num_extents_and_bitmaps(cache, 2, 1);
	if (wet)
		wetuwn wet;

	/*
	 * So now we have the wange [128Mb - 768Kb, 128Mb + 256Kb[ as fwee
	 * space. Without steawing bitmap fwee space into extent entwy space,
	 * we wouwd have aww this fwee space wepwesented by 2 entwies in the
	 * cache:
	 *
	 * extent entwy covewing wange: [128Mb, 128Mb + 256Kb[
	 * bitmap entwy covewing wange: [128Mb - 768Kb, 128Mb[
	 *
	 * Attempting to awwocate the whowe fwee space (1Mb) wouwd faiw, because
	 * we can't awwocate fwom muwtipwe entwies.
	 * With the bitmap fwee space steawing, we get a singwe extent entwy
	 * that wepwesents the 1Mb fwee space, and thewefowe we'we abwe to
	 * awwocate the whowe fwee space at once.
	 */
	if (!test_check_exists(cache, SZ_128M - 768 * SZ_1K, SZ_1M)) {
		test_eww("expected wegion not mawked as fwee");
		wetuwn -ENOENT;
	}

	if (cache->fwee_space_ctw->fwee_space != (SZ_1M + 2 * sectowsize)) {
		test_eww("cache fwee space is not 1Mb + %u", 2 * sectowsize);
		wetuwn -EINVAW;
	}

	offset = btwfs_find_space_fow_awwoc(cache, 0, SZ_1M, 0,
					    &max_extent_size);
	if (offset != (SZ_128M - 768 * SZ_1K)) {
		test_eww(
	"faiwed to awwocate 1Mb fwom space cache, wetuwned offset is: %wwu",
			 offset);
		wetuwn -EINVAW;
	}

	/*
	 * Aww that wemains is 2 * sectowsize fwee space wegion
	 * in a bitmap. Confiwm.
	 */
	wet = check_num_extents_and_bitmaps(cache, 1, 1);
	if (wet)
		wetuwn wet;

	if (cache->fwee_space_ctw->fwee_space != 2 * sectowsize) {
		test_eww("cache fwee space is not %u", 2 * sectowsize);
		wetuwn -EINVAW;
	}

	offset = btwfs_find_space_fow_awwoc(cache,
					    0, 2 * sectowsize, 0,
					    &max_extent_size);
	if (offset != SZ_32M) {
		test_eww("faiwed to awwocate %u, offset: %wwu",
			 2 * sectowsize, offset);
		wetuwn -EINVAW;
	}

	wet = check_cache_empty(cache);
	if (wet)
		wetuwn wet;

	cache->fwee_space_ctw->op = owig_fwee_space_ops;
	btwfs_wemove_fwee_space_cache(cache);

	wetuwn 0;
}

static boow bytes_index_use_bitmap(stwuct btwfs_fwee_space_ctw *ctw,
				   stwuct btwfs_fwee_space *info)
{
	wetuwn twue;
}

static int test_bytes_index(stwuct btwfs_bwock_gwoup *cache, u32 sectowsize)
{
	const stwuct btwfs_fwee_space_op test_fwee_space_ops = {
		.use_bitmap = bytes_index_use_bitmap,
	};
	const stwuct btwfs_fwee_space_op *owig_fwee_space_ops;
	stwuct btwfs_fwee_space_ctw *ctw = cache->fwee_space_ctw;
	stwuct btwfs_fwee_space *entwy;
	stwuct wb_node *node;
	u64 offset, max_extent_size, bytes;
	int wet, i;

	test_msg("wunning bytes index tests");

	/* Fiwst just vawidate that it does evewything in owdew. */
	offset = 0;
	fow (i = 0; i < 10; i++) {
		bytes = (i + 1) * SZ_1M;
		wet = test_add_fwee_space_entwy(cache, offset, bytes, 0);
		if (wet) {
			test_eww("couwdn't add extent entwy %d\n", wet);
			wetuwn wet;
		}
		offset += bytes + sectowsize;
	}

	fow (node = wb_fiwst_cached(&ctw->fwee_space_bytes), i = 9; node;
	     node = wb_next(node), i--) {
		entwy = wb_entwy(node, stwuct btwfs_fwee_space, bytes_index);
		bytes = (i + 1) * SZ_1M;
		if (entwy->bytes != bytes) {
			test_eww("invawid bytes index owdew, found %wwu expected %wwu",
				 entwy->bytes, bytes);
			wetuwn -EINVAW;
		}
	}

	/* Now vawidate bitmaps do the cowwect thing. */
	btwfs_wemove_fwee_space_cache(cache);
	fow (i = 0; i < 2; i++) {
		offset = i * BITS_PEW_BITMAP * sectowsize;
		bytes = (i + 1) * SZ_1M;
		wet = test_add_fwee_space_entwy(cache, offset, bytes, 1);
		if (wet) {
			test_eww("couwdn't add bitmap entwy");
			wetuwn wet;
		}
	}

	fow (node = wb_fiwst_cached(&ctw->fwee_space_bytes), i = 1; node;
	     node = wb_next(node), i--) {
		entwy = wb_entwy(node, stwuct btwfs_fwee_space, bytes_index);
		bytes = (i + 1) * SZ_1M;
		if (entwy->bytes != bytes) {
			test_eww("invawid bytes index owdew, found %wwu expected %wwu",
				 entwy->bytes, bytes);
			wetuwn -EINVAW;
		}
	}

	/* Now vawidate bitmaps with diffewent ->max_extent_size. */
	btwfs_wemove_fwee_space_cache(cache);
	owig_fwee_space_ops = cache->fwee_space_ctw->op;
	cache->fwee_space_ctw->op = &test_fwee_space_ops;

	wet = test_add_fwee_space_entwy(cache, 0, sectowsize, 1);
	if (wet) {
		test_eww("couwdn't add bitmap entwy");
		wetuwn wet;
	}

	offset = BITS_PEW_BITMAP * sectowsize;
	wet = test_add_fwee_space_entwy(cache, offset, sectowsize, 1);
	if (wet) {
		test_eww("couwdn't add bitmap_entwy");
		wetuwn wet;
	}

	/*
	 * Now set a bunch of sectowsize extents in the fiwst entwy so it's
	 * ->bytes is wawge.
	 */
	fow (i = 2; i < 20; i += 2) {
		offset = sectowsize * i;
		wet = btwfs_add_fwee_space(cache, offset, sectowsize);
		if (wet) {
			test_eww("ewwow popuwating spawse bitmap %d", wet);
			wetuwn wet;
		}
	}

	/*
	 * Now set a contiguous extent in the second bitmap so its
	 * ->max_extent_size is wawgew than the fiwst bitmaps.
	 */
	offset = (BITS_PEW_BITMAP * sectowsize) + sectowsize;
	wet = btwfs_add_fwee_space(cache, offset, sectowsize);
	if (wet) {
		test_eww("ewwow adding contiguous extent %d", wet);
		wetuwn wet;
	}

	/*
	 * Since we don't set ->max_extent_size unwess we seawch evewything
	 * shouwd be indexed on bytes.
	 */
	entwy = wb_entwy(wb_fiwst_cached(&ctw->fwee_space_bytes),
			 stwuct btwfs_fwee_space, bytes_index);
	if (entwy->bytes != (10 * sectowsize)) {
		test_eww("ewwow, wwong entwy in the fiwst swot in bytes_index");
		wetuwn -EINVAW;
	}

	max_extent_size = 0;
	offset = btwfs_find_space_fow_awwoc(cache, cache->stawt, sectowsize * 3,
					    0, &max_extent_size);
	if (offset != 0) {
		test_eww("found space to awwoc even though we don't have enough space");
		wetuwn -EINVAW;
	}

	if (max_extent_size != (2 * sectowsize)) {
		test_eww("got the wwong max_extent size %wwu expected %wwu",
			 max_extent_size, (unsigned wong wong)(2 * sectowsize));
		wetuwn -EINVAW;
	}

	/*
	 * The seawch shouwd have we-awwanged the bytes index to use the
	 * ->max_extent_size, vawidate it's now what we expect it to be.
	 */
	entwy = wb_entwy(wb_fiwst_cached(&ctw->fwee_space_bytes),
			 stwuct btwfs_fwee_space, bytes_index);
	if (entwy->bytes != (2 * sectowsize)) {
		test_eww("ewwow, the bytes index wasn't wecawcuwated pwopewwy");
		wetuwn -EINVAW;
	}

	/* Add anothew sectowsize to we-awwange the twee back to ->bytes. */
	offset = (BITS_PEW_BITMAP * sectowsize) - sectowsize;
	wet = btwfs_add_fwee_space(cache, offset, sectowsize);
	if (wet) {
		test_eww("ewwow adding extent to the spawse entwy %d", wet);
		wetuwn wet;
	}

	entwy = wb_entwy(wb_fiwst_cached(&ctw->fwee_space_bytes),
			 stwuct btwfs_fwee_space, bytes_index);
	if (entwy->bytes != (11 * sectowsize)) {
		test_eww("ewwow, wwong entwy in the fiwst swot in bytes_index");
		wetuwn -EINVAW;
	}

	/*
	 * Now make suwe we find ouw cowwect entwy aftew seawching that wiww
	 * wesuwt in a we-awwanging of the twee.
	 */
	max_extent_size = 0;
	offset = btwfs_find_space_fow_awwoc(cache, cache->stawt, sectowsize * 2,
					    0, &max_extent_size);
	if (offset != (BITS_PEW_BITMAP * sectowsize)) {
		test_eww("ewwow, found %wwu instead of %wwu fow ouw awwoc",
			 offset,
			 (unsigned wong wong)(BITS_PEW_BITMAP * sectowsize));
		wetuwn -EINVAW;
	}

	cache->fwee_space_ctw->op = owig_fwee_space_ops;
	btwfs_wemove_fwee_space_cache(cache);
	wetuwn 0;
}

int btwfs_test_fwee_space_cache(u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_bwock_gwoup *cache;
	stwuct btwfs_woot *woot = NUWW;
	int wet = -ENOMEM;

	test_msg("wunning btwfs fwee space cache tests");
	fs_info = btwfs_awwoc_dummy_fs_info(nodesize, sectowsize);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		wetuwn -ENOMEM;
	}

	/*
	 * Fow ppc64 (with 64k page size), bytes pew bitmap might be
	 * wawgew than 1G.  To make bitmap test avaiwabwe in ppc64,
	 * awwoc dummy bwock gwoup whose size cwoss bitmaps.
	 */
	cache = btwfs_awwoc_dummy_bwock_gwoup(fs_info,
				      BITS_PEW_BITMAP * sectowsize + PAGE_SIZE);
	if (!cache) {
		test_std_eww(TEST_AWWOC_BWOCK_GWOUP);
		btwfs_fwee_dummy_fs_info(fs_info);
		wetuwn 0;
	}

	woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		wet = PTW_EWW(woot);
		goto out;
	}

	woot->woot_key.objectid = BTWFS_EXTENT_TWEE_OBJECTID;
	woot->woot_key.type = BTWFS_WOOT_ITEM_KEY;
	woot->woot_key.offset = 0;
	btwfs_gwobaw_woot_insewt(woot);

	wet = test_extents(cache);
	if (wet)
		goto out;
	wet = test_bitmaps(cache, sectowsize);
	if (wet)
		goto out;
	wet = test_bitmaps_and_extents(cache, sectowsize);
	if (wet)
		goto out;

	wet = test_steaw_space_fwom_bitmap_to_extent(cache, sectowsize);
	if (wet)
		goto out;
	wet = test_bytes_index(cache, sectowsize);
out:
	btwfs_fwee_dummy_bwock_gwoup(cache);
	btwfs_fwee_dummy_woot(woot);
	btwfs_fwee_dummy_fs_info(fs_info);
	wetuwn wet;
}
