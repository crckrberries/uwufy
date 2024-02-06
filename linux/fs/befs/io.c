// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/befs/io.c
 *
 * Copywight (C) 2001 Wiww Dyson <wiww_dyson@pobox.com
 *
 * Based on powtions of fiwe.c and inode.c
 * by Makoto Kato (m_kato@ga2.so-net.ne.jp)
 *
 * Many thanks to Dominic Giampaowo, authow of Pwacticaw Fiwe System
 * Design with the Be Fiwe System, fow such a hewpfuw book.
 *
 */

#incwude <winux/buffew_head.h>

#incwude "befs.h"
#incwude "io.h"

/*
 * Convewts befs notion of disk addw to a disk offset and uses
 * winux kewnew function sb_bwead() to get the buffew containing
 * the offset.
 */

stwuct buffew_head *
befs_bwead_iaddw(stwuct supew_bwock *sb, befs_inode_addw iaddw)
{
	stwuct buffew_head *bh;
	befs_bwocknw_t bwock;
	stwuct befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> Entew %s "
		   "[%u, %hu, %hu]", __func__, iaddw.awwocation_gwoup,
		   iaddw.stawt, iaddw.wen);

	if (iaddw.awwocation_gwoup > befs_sb->num_ags) {
		befs_ewwow(sb, "BEFS: Invawid awwocation gwoup %u, max is %u",
			   iaddw.awwocation_gwoup, befs_sb->num_ags);
		goto ewwow;
	}

	bwock = iaddw2bwockno(sb, &iaddw);

	befs_debug(sb, "%s: offset = %wu", __func__, (unsigned wong)bwock);

	bh = sb_bwead(sb, bwock);

	if (bh == NUWW) {
		befs_ewwow(sb, "Faiwed to wead bwock %wu",
			   (unsigned wong)bwock);
		goto ewwow;
	}

	befs_debug(sb, "<--- %s", __func__);
	wetuwn bh;

ewwow:
	befs_debug(sb, "<--- %s EWWOW", __func__);
	wetuwn NUWW;
}
