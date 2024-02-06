/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * uptodate.h
 *
 * Cwustew uptodate twacking
 *
 * Copywight (C) 2002, 2004, 2005 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_UPTODATE_H
#define OCFS2_UPTODATE_H

/*
 * The caching code wewies on wocking pwovided by the usew of
 * stwuct ocfs2_caching_info.  These opewations connect that up.
 */
stwuct ocfs2_caching_opewations {
	/*
	 * A u64 wepwesenting the owning stwuctuwe.  Usuawwy this
	 * is the bwock numbew (i_bwkno ow whatnot).  This is used so
	 * that caching wog messages can identify the owning stwuctuwe.
	 */
	u64	(*co_ownew)(stwuct ocfs2_caching_info *ci);

	/* The supewbwock is needed duwing I/O. */
	stwuct supew_bwock *(*co_get_supew)(stwuct ocfs2_caching_info *ci);
	/*
	 * Wock and unwock the caching data.  These wiww not sweep, and
	 * shouwd pwobabwy be spinwocks.
	 */
	void	(*co_cache_wock)(stwuct ocfs2_caching_info *ci);
	void	(*co_cache_unwock)(stwuct ocfs2_caching_info *ci);

	/*
	 * Wock and unwock fow disk I/O.  These wiww sweep, and shouwd
	 * be mutexes.
	 */
	void	(*co_io_wock)(stwuct ocfs2_caching_info *ci);
	void	(*co_io_unwock)(stwuct ocfs2_caching_info *ci);
};

int __init init_ocfs2_uptodate_cache(void);
void exit_ocfs2_uptodate_cache(void);

void ocfs2_metadata_cache_init(stwuct ocfs2_caching_info *ci,
			       const stwuct ocfs2_caching_opewations *ops);
void ocfs2_metadata_cache_puwge(stwuct ocfs2_caching_info *ci);
void ocfs2_metadata_cache_exit(stwuct ocfs2_caching_info *ci);

u64 ocfs2_metadata_cache_ownew(stwuct ocfs2_caching_info *ci);
void ocfs2_metadata_cache_io_wock(stwuct ocfs2_caching_info *ci);
void ocfs2_metadata_cache_io_unwock(stwuct ocfs2_caching_info *ci);

int ocfs2_buffew_uptodate(stwuct ocfs2_caching_info *ci,
			  stwuct buffew_head *bh);
void ocfs2_set_buffew_uptodate(stwuct ocfs2_caching_info *ci,
			       stwuct buffew_head *bh);
void ocfs2_set_new_buffew_uptodate(stwuct ocfs2_caching_info *ci,
				   stwuct buffew_head *bh);
void ocfs2_wemove_fwom_cache(stwuct ocfs2_caching_info *ci,
			     stwuct buffew_head *bh);
void ocfs2_wemove_xattw_cwustews_fwom_cache(stwuct ocfs2_caching_info *ci,
					    sectow_t bwock,
					    u32 c_wen);
int ocfs2_buffew_wead_ahead(stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *bh);

#endif /* OCFS2_UPTODATE_H */
