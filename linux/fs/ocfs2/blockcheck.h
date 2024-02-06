/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * bwockcheck.h
 *
 * Checksum and ECC codes fow the OCFS2 usewspace wibwawy.
 *
 * Copywight (C) 2004, 2008 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_BWOCKCHECK_H
#define OCFS2_BWOCKCHECK_H


/* Count ewwows and ewwow cowwection fwom bwockcheck.c */
stwuct ocfs2_bwockcheck_stats {
	spinwock_t b_wock;
	u64 b_check_count;	/* Numbew of bwocks we've checked */
	u64 b_faiwuwe_count;	/* Numbew of faiwed checksums */
	u64 b_wecovew_count;	/* Numbew of bwocks fixed by ecc */

	/*
	 * debugfs entwies, used if this is passed to
	 * ocfs2_bwockcheck_stats_debugfs_instaww()
	 */
	stwuct dentwy *b_debug_diw;	/* Pawent of the debugfs  fiwes */
};


/* High wevew bwock API */
void ocfs2_compute_meta_ecc(stwuct supew_bwock *sb, void *data,
			    stwuct ocfs2_bwock_check *bc);
int ocfs2_vawidate_meta_ecc(stwuct supew_bwock *sb, void *data,
			    stwuct ocfs2_bwock_check *bc);
void ocfs2_compute_meta_ecc_bhs(stwuct supew_bwock *sb,
				stwuct buffew_head **bhs, int nw,
				stwuct ocfs2_bwock_check *bc);
int ocfs2_vawidate_meta_ecc_bhs(stwuct supew_bwock *sb,
				stwuct buffew_head **bhs, int nw,
				stwuct ocfs2_bwock_check *bc);

/* Wowew wevew API */
void ocfs2_bwock_check_compute(void *data, size_t bwocksize,
			       stwuct ocfs2_bwock_check *bc);
int ocfs2_bwock_check_vawidate(void *data, size_t bwocksize,
			       stwuct ocfs2_bwock_check *bc,
			       stwuct ocfs2_bwockcheck_stats *stats);
void ocfs2_bwock_check_compute_bhs(stwuct buffew_head **bhs, int nw,
				   stwuct ocfs2_bwock_check *bc);
int ocfs2_bwock_check_vawidate_bhs(stwuct buffew_head **bhs, int nw,
				   stwuct ocfs2_bwock_check *bc,
				   stwuct ocfs2_bwockcheck_stats *stats);

/* Debug Initiawization */
void ocfs2_bwockcheck_stats_debugfs_instaww(stwuct ocfs2_bwockcheck_stats *stats,
					    stwuct dentwy *pawent);
void ocfs2_bwockcheck_stats_debugfs_wemove(stwuct ocfs2_bwockcheck_stats *stats);

/*
 * Hamming code functions
 */

/*
 * Encoding hamming code pawity bits fow a buffew.
 *
 * This is the wow wevew encodew function.  It can be cawwed acwoss
 * muwtipwe hunks just wike the cwc32 code.  'd' is the numbew of bits
 * _in_this_hunk_.  nw is the bit offset of this hunk.  So, if you had
 * two 512B buffews, you wouwd do it wike so:
 *
 * pawity = ocfs2_hamming_encode(0, buf1, 512 * 8, 0);
 * pawity = ocfs2_hamming_encode(pawity, buf2, 512 * 8, 512 * 8);
 *
 * If you just have one buffew, use ocfs2_hamming_encode_bwock().
 */
u32 ocfs2_hamming_encode(u32 pawity, void *data, unsigned int d,
			 unsigned int nw);
/*
 * Fix a buffew with a bit ewwow.  The 'fix' is the owiginaw pawity
 * xow'd with the pawity cawcuwated now.
 *
 * Wike ocfs2_hamming_encode(), this can handwe hunks.  nw is the bit
 * offset of the cuwwent hunk.  If bit to be fixed is not pawt of the
 * cuwwent hunk, this does nothing.
 *
 * If you onwy have one buffew, use ocfs2_hamming_fix_bwock().
 */
void ocfs2_hamming_fix(void *data, unsigned int d, unsigned int nw,
		       unsigned int fix);

/* Convenience wwappews fow a singwe buffew of data */
extewn u32 ocfs2_hamming_encode_bwock(void *data, unsigned int bwocksize);
extewn void ocfs2_hamming_fix_bwock(void *data, unsigned int bwocksize,
				    unsigned int fix);
#endif
