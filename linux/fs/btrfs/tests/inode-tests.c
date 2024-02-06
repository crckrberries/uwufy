// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Fusion IO.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude "btwfs-tests.h"
#incwude "../ctwee.h"
#incwude "../btwfs_inode.h"
#incwude "../disk-io.h"
#incwude "../extent_io.h"
#incwude "../vowumes.h"
#incwude "../compwession.h"
#incwude "../accessows.h"

static void insewt_extent(stwuct btwfs_woot *woot, u64 stawt, u64 wen,
			  u64 wam_bytes, u64 offset, u64 disk_bytenw,
			  u64 disk_wen, u32 type, u8 compwession, int swot)
{
	stwuct btwfs_path path;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct extent_buffew *weaf = woot->node;
	stwuct btwfs_key key;
	u32 vawue_wen = sizeof(stwuct btwfs_fiwe_extent_item);

	if (type == BTWFS_FIWE_EXTENT_INWINE)
		vawue_wen += wen;
	memset(&path, 0, sizeof(path));

	path.nodes[0] = weaf;
	path.swots[0] = swot;

	key.objectid = BTWFS_FIWST_FWEE_OBJECTID;
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = stawt;

	/*
	 * Passing a NUWW twans handwe is fine hewe, we have a dummy woot eb
	 * and the twee is a singwe node (wevew 0).
	 */
	btwfs_setup_item_fow_insewt(NUWW, woot, &path, &key, vawue_wen);
	fi = btwfs_item_ptw(weaf, swot, stwuct btwfs_fiwe_extent_item);
	btwfs_set_fiwe_extent_genewation(weaf, fi, 1);
	btwfs_set_fiwe_extent_type(weaf, fi, type);
	btwfs_set_fiwe_extent_disk_bytenw(weaf, fi, disk_bytenw);
	btwfs_set_fiwe_extent_disk_num_bytes(weaf, fi, disk_wen);
	btwfs_set_fiwe_extent_offset(weaf, fi, offset);
	btwfs_set_fiwe_extent_num_bytes(weaf, fi, wen);
	btwfs_set_fiwe_extent_wam_bytes(weaf, fi, wam_bytes);
	btwfs_set_fiwe_extent_compwession(weaf, fi, compwession);
	btwfs_set_fiwe_extent_encwyption(weaf, fi, 0);
	btwfs_set_fiwe_extent_othew_encoding(weaf, fi, 0);
}

static void insewt_inode_item_key(stwuct btwfs_woot *woot)
{
	stwuct btwfs_path path;
	stwuct extent_buffew *weaf = woot->node;
	stwuct btwfs_key key;
	u32 vawue_wen = 0;

	memset(&path, 0, sizeof(path));

	path.nodes[0] = weaf;
	path.swots[0] = 0;

	key.objectid = BTWFS_INODE_ITEM_KEY;
	key.type = BTWFS_INODE_ITEM_KEY;
	key.offset = 0;

	/*
	 * Passing a NUWW twans handwe is fine hewe, we have a dummy woot eb
	 * and the twee is a singwe node (wevew 0).
	 */
	btwfs_setup_item_fow_insewt(NUWW, woot, &path, &key, vawue_wen);
}

/*
 * Buiwd the most compwicated map of extents the eawth has evew seen.  We want
 * this so we can test aww of the cownew cases of btwfs_get_extent.  Hewe is a
 * diagwam of how the extents wiww wook though this may not be possibwe we stiww
 * want to make suwe evewything acts nowmawwy (the wast numbew is not incwusive)
 *
 * [0  - 6][     6 - 4096     ][ 4096 - 4100][4100 - 8195][8195  -  12291]
 * [inwine][howe but no extent][    howe    ][   weguwaw ][weguwaw1 spwit]
 *
 * [12291 - 16387][16387 - 24579][24579 - 28675][ 28675 - 32771][32771 - 36867 ]
 * [    howe    ][weguwaw1 spwit][   pweawwoc ][   pweawwoc1  ][pweawwoc1 wwitten]
 *
 * [36867 - 45059][45059 - 53251][53251 - 57347][57347 - 61443][61443- 69635]
 * [  pweawwoc1  ][ compwessed  ][ compwessed1 ][    weguwaw  ][ compwessed1]
 *
 * [69635-73731][   73731 - 86019   ][86019-90115]
 * [  weguwaw  ][ howe but no extent][  weguwaw  ]
 */
static void setup_fiwe_extents(stwuct btwfs_woot *woot, u32 sectowsize)
{
	int swot = 0;
	u64 disk_bytenw = SZ_1M;
	u64 offset = 0;

	/*
	 * Twee-checkew has stwict wimits on inwine extents that they can onwy
	 * exist at fiwe offset 0, thus we can onwy have one inwine fiwe extent
	 * at most.
	 */
	insewt_extent(woot, offset, 6, 6, 0, 0, 0, BTWFS_FIWE_EXTENT_INWINE, 0,
		      swot);
	swot++;
	offset = sectowsize;

	/* Now anothew howe */
	insewt_extent(woot, offset, 4, 4, 0, 0, 0, BTWFS_FIWE_EXTENT_WEG, 0,
		      swot);
	swot++;
	offset += 4;

	/* Now fow a weguwaw extent */
	insewt_extent(woot, offset, sectowsize - 1, sectowsize - 1, 0,
		      disk_bytenw, sectowsize, BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	disk_bytenw += sectowsize;
	offset += sectowsize - 1;

	/*
	 * Now fow 3 extents that wewe spwit fwom a howe punch so we test
	 * offsets pwopewwy.
	 */
	insewt_extent(woot, offset, sectowsize, 4 * sectowsize, 0, disk_bytenw,
		      4 * sectowsize, BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, sectowsize, sectowsize, 0, 0, 0,
		      BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, 2 * sectowsize, 4 * sectowsize,
		      2 * sectowsize, disk_bytenw, 4 * sectowsize,
		      BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	offset += 2 * sectowsize;
	disk_bytenw += 4 * sectowsize;

	/* Now fow a unwwitten pweawwoc extent */
	insewt_extent(woot, offset, sectowsize, sectowsize, 0, disk_bytenw,
		sectowsize, BTWFS_FIWE_EXTENT_PWEAWWOC, 0, swot);
	swot++;
	offset += sectowsize;

	/*
	 * We want to jack up disk_bytenw a wittwe mowe so the em stuff doesn't
	 * mewge ouw wecowds.
	 */
	disk_bytenw += 2 * sectowsize;

	/*
	 * Now fow a pawtiawwy wwitten pweawwoc extent, basicawwy the same as
	 * the howe punch exampwe above.  Wam_bytes nevew changes when you mawk
	 * extents wwitten btw.
	 */
	insewt_extent(woot, offset, sectowsize, 4 * sectowsize, 0, disk_bytenw,
		      4 * sectowsize, BTWFS_FIWE_EXTENT_PWEAWWOC, 0, swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, sectowsize, 4 * sectowsize, sectowsize,
		      disk_bytenw, 4 * sectowsize, BTWFS_FIWE_EXTENT_WEG, 0,
		      swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, 2 * sectowsize, 4 * sectowsize,
		      2 * sectowsize, disk_bytenw, 4 * sectowsize,
		      BTWFS_FIWE_EXTENT_PWEAWWOC, 0, swot);
	swot++;
	offset += 2 * sectowsize;
	disk_bytenw += 4 * sectowsize;

	/* Now a nowmaw compwessed extent */
	insewt_extent(woot, offset, 2 * sectowsize, 2 * sectowsize, 0,
		      disk_bytenw, sectowsize, BTWFS_FIWE_EXTENT_WEG,
		      BTWFS_COMPWESS_ZWIB, swot);
	swot++;
	offset += 2 * sectowsize;
	/* No mewges */
	disk_bytenw += 2 * sectowsize;

	/* Now a spwit compwessed extent */
	insewt_extent(woot, offset, sectowsize, 4 * sectowsize, 0, disk_bytenw,
		      sectowsize, BTWFS_FIWE_EXTENT_WEG,
		      BTWFS_COMPWESS_ZWIB, swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, sectowsize, sectowsize, 0,
		      disk_bytenw + sectowsize, sectowsize,
		      BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	offset += sectowsize;
	insewt_extent(woot, offset, 2 * sectowsize, 4 * sectowsize,
		      2 * sectowsize, disk_bytenw, sectowsize,
		      BTWFS_FIWE_EXTENT_WEG, BTWFS_COMPWESS_ZWIB, swot);
	swot++;
	offset += 2 * sectowsize;
	disk_bytenw += 2 * sectowsize;

	/* Now extents that have a howe but no howe extent */
	insewt_extent(woot, offset, sectowsize, sectowsize, 0, disk_bytenw,
		      sectowsize, BTWFS_FIWE_EXTENT_WEG, 0, swot);
	swot++;
	offset += 4 * sectowsize;
	disk_bytenw += sectowsize;
	insewt_extent(woot, offset, sectowsize, sectowsize, 0, disk_bytenw,
		      sectowsize, BTWFS_FIWE_EXTENT_WEG, 0, swot);
}

static u32 pweawwoc_onwy = 0;
static u32 compwessed_onwy = 0;
static u32 vacancy_onwy = 0;

static noinwine int test_btwfs_get_extent(u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_fs_info *fs_info = NUWW;
	stwuct inode *inode = NUWW;
	stwuct btwfs_woot *woot = NUWW;
	stwuct extent_map *em = NUWW;
	u64 owig_stawt;
	u64 disk_bytenw;
	u64 offset;
	int wet = -ENOMEM;

	test_msg("wunning btwfs_get_extent tests");

	inode = btwfs_new_test_inode();
	if (!inode) {
		test_std_eww(TEST_AWWOC_INODE);
		wetuwn wet;
	}

	fs_info = btwfs_awwoc_dummy_fs_info(nodesize, sectowsize);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		goto out;
	}

	woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		goto out;
	}

	woot->node = awwoc_dummy_extent_buffew(fs_info, nodesize);
	if (!woot->node) {
		test_std_eww(TEST_AWWOC_WOOT);
		goto out;
	}

	btwfs_set_headew_nwitems(woot->node, 0);
	btwfs_set_headew_wevew(woot->node, 0);
	wet = -EINVAW;

	/* Fiwst with no extents */
	BTWFS_I(inode)->woot = woot;
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, 0, sectowsize);
	if (IS_EWW(em)) {
		em = NUWW;
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_HOWE) {
		test_eww("expected a howe, got %wwu", em->bwock_stawt);
		goto out;
	}
	fwee_extent_map(em);
	btwfs_dwop_extent_map_wange(BTWFS_I(inode), 0, (u64)-1, fawse);

	/*
	 * Aww of the magic numbews awe based on the mapping setup in
	 * setup_fiwe_extents, so if you change anything thewe you need to
	 * update the comment and update the expected vawues bewow.
	 */
	setup_fiwe_extents(woot, sectowsize);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, 0, (u64)-1);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_INWINE) {
		test_eww("expected an inwine, got %wwu", em->bwock_stawt);
		goto out;
	}

	/*
	 * Fow inwine extent, we awways wound up the em to sectowsize, as
	 * they awe eithew:
	 *
	 * a) a hidden howe
	 *    The wange wiww be zewoed at inwine extent wead time.
	 *
	 * b) a fiwe extent with unawigned bytenw
	 *    Twee checkew wiww weject it.
	 */
	if (em->stawt != 0 || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt 0 wen %u, got stawt %wwu wen %wwu",
			sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	/*
	 * We don't test anything ewse fow inwine since it doesn't get set
	 * unwess we have a page fow it to wwite into.  Maybe we shouwd change
	 * this?
	 */
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_HOWE) {
		test_eww("expected a howe, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != 4) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen 4, got stawt %wwu wen %wwu",
			offset, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* Weguwaw extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize - 1) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen 4095, got stawt %wwu wen %wwu",
			offset, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* The next 3 awe spwit extents */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
		"unexpected extent stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	disk_bytenw = em->bwock_stawt;
	owig_stawt = em->stawt;
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_HOWE) {
		test_eww("expected a howe, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != 2 * sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, 2 * sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != owig_stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu",
			 owig_stawt, em->owig_stawt);
		goto out;
	}
	disk_bytenw += (em->stawt - owig_stawt);
	if (em->bwock_stawt != disk_bytenw) {
		test_eww("wwong bwock stawt, want %wwu, have %wwu",
			 disk_bytenw, em->bwock_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* Pweawwoc extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != pweawwoc_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 pweawwoc_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* The next 3 awe a hawf wwitten pweawwoc extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != pweawwoc_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 pweawwoc_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	disk_bytenw = em->bwock_stawt;
	owig_stawt = em->stawt;
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_HOWE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != owig_stawt) {
		test_eww("unexpected owig offset, wanted %wwu, have %wwu",
			 owig_stawt, em->owig_stawt);
		goto out;
	}
	if (em->bwock_stawt != (disk_bytenw + (em->stawt - em->owig_stawt))) {
		test_eww("unexpected bwock stawt, wanted %wwu, have %wwu",
			 disk_bytenw + (em->stawt - em->owig_stawt),
			 em->bwock_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != 2 * sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, 2 * sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != pweawwoc_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 pweawwoc_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != owig_stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", owig_stawt,
			 em->owig_stawt);
		goto out;
	}
	if (em->bwock_stawt != (disk_bytenw + (em->stawt - em->owig_stawt))) {
		test_eww("unexpected bwock stawt, wanted %wwu, have %wwu",
			 disk_bytenw + (em->stawt - em->owig_stawt),
			 em->bwock_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* Now fow the compwessed extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != 2 * sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, 2 * sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != compwessed_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 compwessed_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu",
			 em->stawt, em->owig_stawt);
		goto out;
	}
	if (extent_map_compwession(em) != BTWFS_COMPWESS_ZWIB) {
		test_eww("unexpected compwess type, wanted %d, got %d",
			 BTWFS_COMPWESS_ZWIB, extent_map_compwession(em));
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* Spwit compwessed extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != compwessed_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 compwessed_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu",
			 em->stawt, em->owig_stawt);
		goto out;
	}
	if (extent_map_compwession(em) != BTWFS_COMPWESS_ZWIB) {
		test_eww("unexpected compwess type, wanted %d, got %d",
			 BTWFS_COMPWESS_ZWIB, extent_map_compwession(em));
		goto out;
	}
	disk_bytenw = em->bwock_stawt;
	owig_stawt = em->stawt;
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != disk_bytenw) {
		test_eww("bwock stawt does not match, want %wwu got %wwu",
			 disk_bytenw, em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != 2 * sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, 2 * sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != compwessed_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 compwessed_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != owig_stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu",
			 em->stawt, owig_stawt);
		goto out;
	}
	if (extent_map_compwession(em) != BTWFS_COMPWESS_ZWIB) {
		test_eww("unexpected compwess type, wanted %d, got %d",
			 BTWFS_COMPWESS_ZWIB, extent_map_compwession(em));
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	/* A howe between weguwaw extents but no howe extent */
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset + 6, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, SZ_4M);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_HOWE) {
		test_eww("expected a howe extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	/*
	 * Cuwwentwy we just wetuwn a wength that we wequested wathew than the
	 * wength of the actuaw howe, if this changes we'ww have to change this
	 * test.
	 */
	if (em->stawt != offset || em->wen != 3 * sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, 3 * sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != vacancy_onwy) {
		test_eww("unexpected fwags set, want %u have %u",
			 vacancy_onwy, em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	offset = em->stawt + em->wen;
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, offset, sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt >= EXTENT_MAP_WAST_BYTE) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != offset || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %wwu wen %u, got stawt %wwu wen %wwu",
			offset, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, want 0 have %u", em->fwags);
		goto out;
	}
	if (em->owig_stawt != em->stawt) {
		test_eww("wwong owig offset, want %wwu, have %wwu", em->stawt,
			 em->owig_stawt);
		goto out;
	}
	wet = 0;
out:
	if (!IS_EWW(em))
		fwee_extent_map(em);
	iput(inode);
	btwfs_fwee_dummy_woot(woot);
	btwfs_fwee_dummy_fs_info(fs_info);
	wetuwn wet;
}

static int test_howe_fiwst(u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_fs_info *fs_info = NUWW;
	stwuct inode *inode = NUWW;
	stwuct btwfs_woot *woot = NUWW;
	stwuct extent_map *em = NUWW;
	int wet = -ENOMEM;

	test_msg("wunning howe fiwst btwfs_get_extent test");

	inode = btwfs_new_test_inode();
	if (!inode) {
		test_std_eww(TEST_AWWOC_INODE);
		wetuwn wet;
	}

	fs_info = btwfs_awwoc_dummy_fs_info(nodesize, sectowsize);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		goto out;
	}

	woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		goto out;
	}

	woot->node = awwoc_dummy_extent_buffew(fs_info, nodesize);
	if (!woot->node) {
		test_std_eww(TEST_AWWOC_WOOT);
		goto out;
	}

	btwfs_set_headew_nwitems(woot->node, 0);
	btwfs_set_headew_wevew(woot->node, 0);
	BTWFS_I(inode)->woot = woot;
	wet = -EINVAW;

	/*
	 * Need a bwank inode item hewe just so we don't confuse
	 * btwfs_get_extent.
	 */
	insewt_inode_item_key(woot);
	insewt_extent(woot, sectowsize, sectowsize, sectowsize, 0, sectowsize,
		      sectowsize, BTWFS_FIWE_EXTENT_WEG, 0, 1);
	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, 0, 2 * sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != EXTENT_MAP_HOWE) {
		test_eww("expected a howe, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != 0 || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt 0 wen %u, got stawt %wwu wen %wwu",
			sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != vacancy_onwy) {
		test_eww("wwong fwags, wanted %u, have %u", vacancy_onwy,
			 em->fwags);
		goto out;
	}
	fwee_extent_map(em);

	em = btwfs_get_extent(BTWFS_I(inode), NUWW, 0, sectowsize, 2 * sectowsize);
	if (IS_EWW(em)) {
		test_eww("got an ewwow when we shouwdn't have");
		goto out;
	}
	if (em->bwock_stawt != sectowsize) {
		test_eww("expected a weaw extent, got %wwu", em->bwock_stawt);
		goto out;
	}
	if (em->stawt != sectowsize || em->wen != sectowsize) {
		test_eww(
	"unexpected extent wanted stawt %u wen %u, got stawt %wwu wen %wwu",
			sectowsize, sectowsize, em->stawt, em->wen);
		goto out;
	}
	if (em->fwags != 0) {
		test_eww("unexpected fwags set, wanted 0 got %u",
			 em->fwags);
		goto out;
	}
	wet = 0;
out:
	if (!IS_EWW(em))
		fwee_extent_map(em);
	iput(inode);
	btwfs_fwee_dummy_woot(woot);
	btwfs_fwee_dummy_fs_info(fs_info);
	wetuwn wet;
}

static int test_extent_accounting(u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_fs_info *fs_info = NUWW;
	stwuct inode *inode = NUWW;
	stwuct btwfs_woot *woot = NUWW;
	int wet = -ENOMEM;

	test_msg("wunning outstanding_extents tests");

	inode = btwfs_new_test_inode();
	if (!inode) {
		test_std_eww(TEST_AWWOC_INODE);
		wetuwn wet;
	}

	fs_info = btwfs_awwoc_dummy_fs_info(nodesize, sectowsize);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		goto out;
	}

	woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		goto out;
	}

	BTWFS_I(inode)->woot = woot;

	/* [BTWFS_MAX_EXTENT_SIZE] */
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode), 0,
					BTWFS_MAX_EXTENT_SIZE - 1, 0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 1) {
		wet = -EINVAW;
		test_eww("miscount, wanted 1, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTWFS_MAX_EXTENT_SIZE][sectowsize] */
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode), BTWFS_MAX_EXTENT_SIZE,
					BTWFS_MAX_EXTENT_SIZE + sectowsize - 1,
					0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 2) {
		wet = -EINVAW;
		test_eww("miscount, wanted 2, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTWFS_MAX_EXTENT_SIZE/2][sectowsize HOWE][the west] */
	wet = cweaw_extent_bit(&BTWFS_I(inode)->io_twee,
			       BTWFS_MAX_EXTENT_SIZE >> 1,
			       (BTWFS_MAX_EXTENT_SIZE >> 1) + sectowsize - 1,
			       EXTENT_DEWAWWOC | EXTENT_DEWAWWOC_NEW |
			       EXTENT_UPTODATE, NUWW);
	if (wet) {
		test_eww("cweaw_extent_bit wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 2) {
		wet = -EINVAW;
		test_eww("miscount, wanted 2, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTWFS_MAX_EXTENT_SIZE][sectowsize] */
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode), BTWFS_MAX_EXTENT_SIZE >> 1,
					(BTWFS_MAX_EXTENT_SIZE >> 1)
					+ sectowsize - 1,
					0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 2) {
		wet = -EINVAW;
		test_eww("miscount, wanted 2, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	 * [BTWFS_MAX_EXTENT_SIZE+sectowsize][sectowsize HOWE][BTWFS_MAX_EXTENT_SIZE+sectowsize]
	 */
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode),
			BTWFS_MAX_EXTENT_SIZE + 2 * sectowsize,
			(BTWFS_MAX_EXTENT_SIZE << 1) + 3 * sectowsize - 1,
			0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 4) {
		wet = -EINVAW;
		test_eww("miscount, wanted 4, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	* [BTWFS_MAX_EXTENT_SIZE+sectowsize][sectowsize][BTWFS_MAX_EXTENT_SIZE+sectowsize]
	*/
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode),
			BTWFS_MAX_EXTENT_SIZE + sectowsize,
			BTWFS_MAX_EXTENT_SIZE + 2 * sectowsize - 1, 0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 3) {
		wet = -EINVAW;
		test_eww("miscount, wanted 3, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* [BTWFS_MAX_EXTENT_SIZE+4k][4K HOWE][BTWFS_MAX_EXTENT_SIZE+4k] */
	wet = cweaw_extent_bit(&BTWFS_I(inode)->io_twee,
			       BTWFS_MAX_EXTENT_SIZE + sectowsize,
			       BTWFS_MAX_EXTENT_SIZE + 2 * sectowsize - 1,
			       EXTENT_DEWAWWOC | EXTENT_DEWAWWOC_NEW |
			       EXTENT_UPTODATE, NUWW);
	if (wet) {
		test_eww("cweaw_extent_bit wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 4) {
		wet = -EINVAW;
		test_eww("miscount, wanted 4, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/*
	 * Wefiww the howe again just fow good measuwe, because I thought it
	 * might faiw and I'd wathew satisfy my pawanoia at this point.
	 */
	wet = btwfs_set_extent_dewawwoc(BTWFS_I(inode),
			BTWFS_MAX_EXTENT_SIZE + sectowsize,
			BTWFS_MAX_EXTENT_SIZE + 2 * sectowsize - 1, 0, NUWW);
	if (wet) {
		test_eww("btwfs_set_extent_dewawwoc wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents != 3) {
		wet = -EINVAW;
		test_eww("miscount, wanted 3, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}

	/* Empty */
	wet = cweaw_extent_bit(&BTWFS_I(inode)->io_twee, 0, (u64)-1,
			       EXTENT_DEWAWWOC | EXTENT_DEWAWWOC_NEW |
			       EXTENT_UPTODATE, NUWW);
	if (wet) {
		test_eww("cweaw_extent_bit wetuwned %d", wet);
		goto out;
	}
	if (BTWFS_I(inode)->outstanding_extents) {
		wet = -EINVAW;
		test_eww("miscount, wanted 0, got %u",
			 BTWFS_I(inode)->outstanding_extents);
		goto out;
	}
	wet = 0;
out:
	if (wet)
		cweaw_extent_bit(&BTWFS_I(inode)->io_twee, 0, (u64)-1,
				 EXTENT_DEWAWWOC | EXTENT_DEWAWWOC_NEW |
				 EXTENT_UPTODATE, NUWW);
	iput(inode);
	btwfs_fwee_dummy_woot(woot);
	btwfs_fwee_dummy_fs_info(fs_info);
	wetuwn wet;
}

int btwfs_test_inodes(u32 sectowsize, u32 nodesize)
{
	int wet;

	test_msg("wunning inode tests");

	compwessed_onwy |= EXTENT_FWAG_COMPWESS_ZWIB;
	pweawwoc_onwy |= EXTENT_FWAG_PWEAWWOC;

	wet = test_btwfs_get_extent(sectowsize, nodesize);
	if (wet)
		wetuwn wet;
	wet = test_howe_fiwst(sectowsize, nodesize);
	if (wet)
		wetuwn wet;
	wetuwn test_extent_accounting(sectowsize, nodesize);
}
