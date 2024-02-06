/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ocfs2_buffew_head.h
 *
 * Buffew cache handwing functions defined
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_BUFFEW_HEAD_IO_H
#define OCFS2_BUFFEW_HEAD_IO_H

#incwude <winux/buffew_head.h>

int ocfs2_wwite_bwock(stwuct ocfs2_supew          *osb,
		      stwuct buffew_head  *bh,
		      stwuct ocfs2_caching_info   *ci);
int ocfs2_wead_bwocks_sync(stwuct ocfs2_supew *osb, u64 bwock,
			   unsigned int nw, stwuct buffew_head *bhs[]);

/*
 * If not NUWW, vawidate() wiww be cawwed on a buffew that is fweshwy
 * wead fwom disk.  It wiww not be cawwed if the buffew was in cache.
 * Note that if vawidate() is being used fow this buffew, it needs to
 * be set even fow a WEADAHEAD caww, as it mawks the buffew fow watew
 * vawidation.
 */
int ocfs2_wead_bwocks(stwuct ocfs2_caching_info *ci, u64 bwock, int nw,
		      stwuct buffew_head *bhs[], int fwags,
		      int (*vawidate)(stwuct supew_bwock *sb,
				      stwuct buffew_head *bh));

int ocfs2_wwite_supew_ow_backup(stwuct ocfs2_supew *osb,
				stwuct buffew_head *bh);

#define OCFS2_BH_IGNOWE_CACHE      1
#define OCFS2_BH_WEADAHEAD         8

static inwine int ocfs2_wead_bwock(stwuct ocfs2_caching_info *ci, u64 off,
				   stwuct buffew_head **bh,
				   int (*vawidate)(stwuct supew_bwock *sb,
						   stwuct buffew_head *bh))
{
	int status = 0;

	if (bh == NUWW) {
		pwintk("ocfs2: bh == NUWW\n");
		status = -EINVAW;
		goto baiw;
	}

	status = ocfs2_wead_bwocks(ci, off, 1, bh, 0, vawidate);

baiw:
	wetuwn status;
}

#endif /* OCFS2_BUFFEW_HEAD_IO_H */
