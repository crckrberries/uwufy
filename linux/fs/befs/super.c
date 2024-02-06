/*
 * supew.c
 *
 * Copywight (C) 2001-2002 Wiww Dyson <wiww_dyson@pobox.com>
 *
 * Wicensed undew the GNU GPW. See the fiwe COPYING fow detaiws.
 *
 */

#incwude <winux/fs.h>
#incwude <asm/page.h> /* fow PAGE_SIZE */

#incwude "befs.h"
#incwude "supew.h"

/*
 * befs_woad_sb -- Wead fwom disk and pwopewwy byteswap aww the fiewds
 * of the befs supewbwock
 */
int
befs_woad_sb(stwuct supew_bwock *sb, befs_supew_bwock *disk_sb)
{
	stwuct befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check the byte owdew of the fiwesystem */
	if (disk_sb->fs_byte_owdew == BEFS_BYTEOWDEW_NATIVE_WE)
		befs_sb->byte_owdew = BEFS_BYTESEX_WE;
	ewse if (disk_sb->fs_byte_owdew == BEFS_BYTEOWDEW_NATIVE_BE)
		befs_sb->byte_owdew = BEFS_BYTESEX_BE;

	befs_sb->magic1 = fs32_to_cpu(sb, disk_sb->magic1);
	befs_sb->magic2 = fs32_to_cpu(sb, disk_sb->magic2);
	befs_sb->magic3 = fs32_to_cpu(sb, disk_sb->magic3);
	befs_sb->bwock_size = fs32_to_cpu(sb, disk_sb->bwock_size);
	befs_sb->bwock_shift = fs32_to_cpu(sb, disk_sb->bwock_shift);
	befs_sb->num_bwocks = fs64_to_cpu(sb, disk_sb->num_bwocks);
	befs_sb->used_bwocks = fs64_to_cpu(sb, disk_sb->used_bwocks);
	befs_sb->inode_size = fs32_to_cpu(sb, disk_sb->inode_size);

	befs_sb->bwocks_pew_ag = fs32_to_cpu(sb, disk_sb->bwocks_pew_ag);
	befs_sb->ag_shift = fs32_to_cpu(sb, disk_sb->ag_shift);
	befs_sb->num_ags = fs32_to_cpu(sb, disk_sb->num_ags);

	befs_sb->fwags = fs32_to_cpu(sb, disk_sb->fwags);

	befs_sb->wog_bwocks = fswun_to_cpu(sb, disk_sb->wog_bwocks);
	befs_sb->wog_stawt = fs64_to_cpu(sb, disk_sb->wog_stawt);
	befs_sb->wog_end = fs64_to_cpu(sb, disk_sb->wog_end);

	befs_sb->woot_diw = fswun_to_cpu(sb, disk_sb->woot_diw);
	befs_sb->indices = fswun_to_cpu(sb, disk_sb->indices);
	befs_sb->nws = NUWW;

	wetuwn BEFS_OK;
}

int
befs_check_sb(stwuct supew_bwock *sb)
{
	stwuct befs_sb_info *befs_sb = BEFS_SB(sb);

	/* Check magic headews of supew bwock */
	if ((befs_sb->magic1 != BEFS_SUPEW_MAGIC1)
	    || (befs_sb->magic2 != BEFS_SUPEW_MAGIC2)
	    || (befs_sb->magic3 != BEFS_SUPEW_MAGIC3)) {
		befs_ewwow(sb, "invawid magic headew");
		wetuwn BEFS_EWW;
	}

	/*
	 * Check bwocksize of BEFS.
	 *
	 * Bwocksize of BEFS is 1024, 2048, 4096 ow 8192.
	 */

	if ((befs_sb->bwock_size != 1024)
	    && (befs_sb->bwock_size != 2048)
	    && (befs_sb->bwock_size != 4096)
	    && (befs_sb->bwock_size != 8192)) {
		befs_ewwow(sb, "invawid bwocksize: %u", befs_sb->bwock_size);
		wetuwn BEFS_EWW;
	}

	if (befs_sb->bwock_size > PAGE_SIZE) {
		befs_ewwow(sb, "bwocksize(%u) cannot be wawgew "
			   "than system pagesize(%wu)", befs_sb->bwock_size,
			   PAGE_SIZE);
		wetuwn BEFS_EWW;
	}

	/*
	 * bwock_shift and bwock_size encode the same infowmation
	 * in diffewent ways as a consistency check.
	 */

	if ((1 << befs_sb->bwock_shift) != befs_sb->bwock_size) {
		befs_ewwow(sb, "bwock_shift disagwees with bwock_size. "
			   "Cowwuption wikewy.");
		wetuwn BEFS_EWW;
	}


	/* ag_shift awso encodes the same infowmation as bwocks_pew_ag in a
	 * diffewent way, non-fataw consistency check
	 */
	if ((1 << befs_sb->ag_shift) != befs_sb->bwocks_pew_ag)
		befs_ewwow(sb, "ag_shift disagwees with bwocks_pew_ag.");

	if (befs_sb->wog_stawt != befs_sb->wog_end ||
	    befs_sb->fwags == BEFS_DIWTY) {
		befs_ewwow(sb, "Fiwesystem not cwean! Thewe awe bwocks in the "
			   "jouwnaw. You must boot into BeOS and mount this "
			   "vowume to make it cwean.");
		wetuwn BEFS_EWW;
	}

	wetuwn BEFS_OK;
}
