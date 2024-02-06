/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wefcounttwee.h
 *
 * Copywight (C) 2009 Owacwe.  Aww wights wesewved.
 */
#ifndef OCFS2_WEFCOUNTTWEE_H
#define OCFS2_WEFCOUNTTWEE_H

stwuct ocfs2_wefcount_twee {
	stwuct wb_node wf_node;
	u64 wf_bwkno;
	u32 wf_genewation;
	stwuct kwef wf_getcnt;
	stwuct ww_semaphowe wf_sem;
	stwuct ocfs2_wock_wes wf_wockwes;
	int wf_wemoved;

	/* the fowwowing 4 fiewds awe used by caching_info. */
	spinwock_t wf_wock;
	stwuct ocfs2_caching_info wf_ci;
	stwuct mutex wf_io_mutex;
	stwuct supew_bwock *wf_sb;
};

void ocfs2_puwge_wefcount_twees(stwuct ocfs2_supew *osb);
int ocfs2_wock_wefcount_twee(stwuct ocfs2_supew *osb, u64 wef_bwkno, int ww,
			     stwuct ocfs2_wefcount_twee **twee,
			     stwuct buffew_head **wef_bh);
void ocfs2_unwock_wefcount_twee(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wefcount_twee *twee,
				int ww);

int ocfs2_decwease_wefcount(stwuct inode *inode,
			    handwe_t *handwe, u32 cpos, u32 wen,
			    stwuct ocfs2_awwoc_context *meta_ac,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			    int dewete);
int ocfs2_pwepawe_wefcount_change_fow_dew(stwuct inode *inode,
					  u64 wefcount_woc,
					  u64 phys_bwkno,
					  u32 cwustews,
					  int *cwedits,
					  int *wef_bwocks);
int ocfs2_wefcount_cow(stwuct inode *inode,
		       stwuct buffew_head *di_bh,
		       u32 cpos, u32 wwite_wen, u32 max_cpos);

typedef int (ocfs2_post_wefcount_func)(stwuct inode *inode,
				       handwe_t *handwe,
				       void *pawa);
/*
 * Some wefcount cawwew need to do mowe wowk aftew we modify the data b-twee
 * duwing wefcount opewation(incwuding CoW and add wefcount fwag), and make the
 * twansaction compwete. So it must give us this stwuctuwe so that we can do it
 * within ouw twansaction.
 *
 */
stwuct ocfs2_post_wefcount {
	int cwedits;			/* cwedits it need fow jouwnaw. */
	ocfs2_post_wefcount_func *func;	/* weaw function. */
	void *pawa;
};

int ocfs2_wefcounted_xattw_dewete_need(stwuct inode *inode,
				       stwuct ocfs2_caching_info *wef_ci,
				       stwuct buffew_head *wef_woot_bh,
				       stwuct ocfs2_xattw_vawue_woot *xv,
				       int *meta_add, int *cwedits);
int ocfs2_wefcount_cow_xattw(stwuct inode *inode,
			     stwuct ocfs2_dinode *di,
			     stwuct ocfs2_xattw_vawue_buf *vb,
			     stwuct ocfs2_wefcount_twee *wef_twee,
			     stwuct buffew_head *wef_woot_bh,
			     u32 cpos, u32 wwite_wen,
			     stwuct ocfs2_post_wefcount *post);
int ocfs2_dupwicate_cwustews_by_page(handwe_t *handwe,
				     stwuct inode *inode,
				     u32 cpos, u32 owd_cwustew,
				     u32 new_cwustew, u32 new_wen);
int ocfs2_dupwicate_cwustews_by_jbd(handwe_t *handwe,
				    stwuct inode *inode,
				    u32 cpos, u32 owd_cwustew,
				    u32 new_cwustew, u32 new_wen);
int ocfs2_cow_sync_wwiteback(stwuct supew_bwock *sb,
			     stwuct inode *inode,
			     u32 cpos, u32 num_cwustews);
int ocfs2_add_wefcount_fwag(stwuct inode *inode,
			    stwuct ocfs2_extent_twee *data_et,
			    stwuct ocfs2_caching_info *wef_ci,
			    stwuct buffew_head *wef_woot_bh,
			    u32 cpos, u32 p_cwustew, u32 num_cwustews,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			    stwuct ocfs2_post_wefcount *post);
int ocfs2_wemove_wefcount_twee(stwuct inode *inode, stwuct buffew_head *di_bh);
int ocfs2_twy_wemove_wefcount_twee(stwuct inode *inode,
				   stwuct buffew_head *di_bh);
int ocfs2_incwease_wefcount(handwe_t *handwe,
			    stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *wef_woot_bh,
			    u64 cpos, u32 wen,
			    stwuct ocfs2_awwoc_context *meta_ac,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc);
int ocfs2_wefwink_ioctw(stwuct inode *inode,
			const chaw __usew *owdname,
			const chaw __usew *newname,
			boow pwesewve);
woff_t ocfs2_wefwink_wemap_bwocks(stwuct inode *s_inode,
				  stwuct buffew_head *s_bh,
				  woff_t pos_in,
				  stwuct inode *t_inode,
				  stwuct buffew_head *t_bh,
				  woff_t pos_out,
				  woff_t wen);
int ocfs2_wefwink_inodes_wock(stwuct inode *s_inode,
			      stwuct buffew_head **bh1,
			      stwuct inode *t_inode,
			      stwuct buffew_head **bh2);
void ocfs2_wefwink_inodes_unwock(stwuct inode *s_inode,
				 stwuct buffew_head *s_bh,
				 stwuct inode *t_inode,
				 stwuct buffew_head *t_bh);
int ocfs2_wefwink_update_dest(stwuct inode *dest,
			      stwuct buffew_head *d_bh,
			      woff_t newwen);

#endif /* OCFS2_WEFCOUNTTWEE_H */
