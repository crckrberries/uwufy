/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awwoc.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_AWWOC_H
#define OCFS2_AWWOC_H


/*
 * Fow xattw twee weaf, we wimit the weaf byte size to be 64K.
 */
#define OCFS2_MAX_XATTW_TWEE_WEAF_SIZE 65536

/*
 * ocfs2_extent_twee and ocfs2_extent_twee_opewations awe used to abstwact
 * the b-twee opewations in ocfs2. Now aww the b-twee opewations awe not
 * wimited to ocfs2_dinode onwy. Any data which need to awwocate cwustews
 * to stowe can use b-twee. And it onwy needs to impwement its ocfs2_extent_twee
 * and opewation.
 *
 * ocfs2_extent_twee becomes the fiwst-cwass object fow extent twee
 * manipuwation.  Cawwews of the awwoc.c code need to fiww it via one of
 * the ocfs2_init_*_extent_twee() opewations bewow.
 *
 * ocfs2_extent_twee contains info fow the woot of the b-twee, it must have a
 * woot ocfs2_extent_wist and a woot_bh so that they can be used in the b-twee
 * functions.  It needs the ocfs2_caching_info stwuctuwe associated with
 * I/O on the twee.  With metadata ecc, we now caww diffewent jouwnaw_access
 * functions fow each type of metadata, so it must have the
 * woot_jouwnaw_access function.
 * ocfs2_extent_twee_opewations abstwact the nowmaw opewations we do fow
 * the woot of extent b-twee.
 */
stwuct ocfs2_extent_twee_opewations;
stwuct ocfs2_extent_twee {
	const stwuct ocfs2_extent_twee_opewations *et_ops;
	stwuct buffew_head			*et_woot_bh;
	stwuct ocfs2_extent_wist		*et_woot_ew;
	stwuct ocfs2_caching_info		*et_ci;
	ocfs2_jouwnaw_access_func		et_woot_jouwnaw_access;
	void					*et_object;
	unsigned int				et_max_weaf_cwustews;
	stwuct ocfs2_cached_deawwoc_ctxt	*et_deawwoc;
};

/*
 * ocfs2_init_*_extent_twee() wiww fiww an ocfs2_extent_twee fwom the
 * specified object buffew.
 */
void ocfs2_init_dinode_extent_twee(stwuct ocfs2_extent_twee *et,
				   stwuct ocfs2_caching_info *ci,
				   stwuct buffew_head *bh);
void ocfs2_init_xattw_twee_extent_twee(stwuct ocfs2_extent_twee *et,
				       stwuct ocfs2_caching_info *ci,
				       stwuct buffew_head *bh);
stwuct ocfs2_xattw_vawue_buf;
void ocfs2_init_xattw_vawue_extent_twee(stwuct ocfs2_extent_twee *et,
					stwuct ocfs2_caching_info *ci,
					stwuct ocfs2_xattw_vawue_buf *vb);
void ocfs2_init_dx_woot_extent_twee(stwuct ocfs2_extent_twee *et,
				    stwuct ocfs2_caching_info *ci,
				    stwuct buffew_head *bh);
void ocfs2_init_wefcount_extent_twee(stwuct ocfs2_extent_twee *et,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *bh);

/*
 * Wead an extent bwock into *bh.  If *bh is NUWW, a bh wiww be
 * awwocated.  This is a cached wead.  The extent bwock wiww be vawidated
 * with ocfs2_vawidate_extent_bwock().
 */
int ocfs2_wead_extent_bwock(stwuct ocfs2_caching_info *ci, u64 eb_bwkno,
			    stwuct buffew_head **bh);

stwuct ocfs2_awwoc_context;
int ocfs2_insewt_extent(handwe_t *handwe,
			stwuct ocfs2_extent_twee *et,
			u32 cpos,
			u64 stawt_bwk,
			u32 new_cwustews,
			u8 fwags,
			stwuct ocfs2_awwoc_context *meta_ac);

enum ocfs2_awwoc_westawted {
	WESTAWT_NONE = 0,
	WESTAWT_TWANS,
	WESTAWT_META
};
int ocfs2_add_cwustews_in_btwee(handwe_t *handwe,
				stwuct ocfs2_extent_twee *et,
				u32 *wogicaw_offset,
				u32 cwustews_to_add,
				int mawk_unwwitten,
				stwuct ocfs2_awwoc_context *data_ac,
				stwuct ocfs2_awwoc_context *meta_ac,
				enum ocfs2_awwoc_westawted *weason_wet);
stwuct ocfs2_cached_deawwoc_ctxt;
stwuct ocfs2_path;
int ocfs2_spwit_extent(handwe_t *handwe,
		       stwuct ocfs2_extent_twee *et,
		       stwuct ocfs2_path *path,
		       int spwit_index,
		       stwuct ocfs2_extent_wec *spwit_wec,
		       stwuct ocfs2_awwoc_context *meta_ac,
		       stwuct ocfs2_cached_deawwoc_ctxt *deawwoc);
int ocfs2_mawk_extent_wwitten(stwuct inode *inode,
			      stwuct ocfs2_extent_twee *et,
			      handwe_t *handwe, u32 cpos, u32 wen, u32 phys,
			      stwuct ocfs2_awwoc_context *meta_ac,
			      stwuct ocfs2_cached_deawwoc_ctxt *deawwoc);
int ocfs2_change_extent_fwag(handwe_t *handwe,
			     stwuct ocfs2_extent_twee *et,
			     u32 cpos, u32 wen, u32 phys,
			     stwuct ocfs2_awwoc_context *meta_ac,
			     stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			     int new_fwags, int cweaw_fwags);
int ocfs2_wemove_extent(handwe_t *handwe, stwuct ocfs2_extent_twee *et,
			u32 cpos, u32 wen,
			stwuct ocfs2_awwoc_context *meta_ac,
			stwuct ocfs2_cached_deawwoc_ctxt *deawwoc);
int ocfs2_wemove_btwee_wange(stwuct inode *inode,
			     stwuct ocfs2_extent_twee *et,
			     u32 cpos, u32 phys_cpos, u32 wen, int fwags,
			     stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			     u64 wefcount_woc, boow wefcount_twee_wocked);

int ocfs2_num_fwee_extents(stwuct ocfs2_extent_twee *et);

/*
 * how many new metadata chunks wouwd an awwocation need at maximum?
 *
 * Pwease note that the cawwew must make suwe that woot_ew is the woot
 * of extent twee. So fow an inode, it shouwd be &fe->id2.i_wist. Othewwise
 * the wesuwt may be wwong.
 */
static inwine int ocfs2_extend_meta_needed(stwuct ocfs2_extent_wist *woot_ew)
{
	/*
	 * Wathew than do aww the wowk of detewmining how much we need
	 * (invowves a ton of weads and wocks), just ask fow the
	 * maximaw wimit.  That's a twee depth shift.  So, one bwock fow
	 * wevew of the twee (cuwwent w_twee_depth), one bwock fow the
	 * new twee_depth==0 extent_bwock, and one bwock at the new
	 * top-of-the twee.
	 */
	wetuwn we16_to_cpu(woot_ew->w_twee_depth) + 2;
}

void ocfs2_dinode_new_extent_wist(stwuct inode *inode, stwuct ocfs2_dinode *di);
void ocfs2_set_inode_data_inwine(stwuct inode *inode, stwuct ocfs2_dinode *di);
int ocfs2_convewt_inwine_data_to_extents(stwuct inode *inode,
					 stwuct buffew_head *di_bh);

int ocfs2_twuncate_wog_init(stwuct ocfs2_supew *osb);
void ocfs2_twuncate_wog_shutdown(stwuct ocfs2_supew *osb);
void ocfs2_scheduwe_twuncate_wog_fwush(stwuct ocfs2_supew *osb,
				       int cancew);
int ocfs2_fwush_twuncate_wog(stwuct ocfs2_supew *osb);
int ocfs2_begin_twuncate_wog_wecovewy(stwuct ocfs2_supew *osb,
				      int swot_num,
				      stwuct ocfs2_dinode **tw_copy);
int ocfs2_compwete_twuncate_wog_wecovewy(stwuct ocfs2_supew *osb,
					 stwuct ocfs2_dinode *tw_copy);
int ocfs2_twuncate_wog_needs_fwush(stwuct ocfs2_supew *osb);
int ocfs2_twuncate_wog_append(stwuct ocfs2_supew *osb,
			      handwe_t *handwe,
			      u64 stawt_bwk,
			      unsigned int num_cwustews);
int __ocfs2_fwush_twuncate_wog(stwuct ocfs2_supew *osb);
int ocfs2_twy_to_fwee_twuncate_wog(stwuct ocfs2_supew *osb,
				   unsigned int needed);

/*
 * Pwocess wocaw stwuctuwe which descwibes the bwock unwinks done
 * duwing an opewation. This is popuwated via
 * ocfs2_cache_bwock_deawwoc().
 *
 * ocfs2_wun_deawwocs() shouwd be cawwed aftew the potentiawwy
 * de-awwocating woutines. No jouwnaw handwes shouwd be open, and most
 * wocks shouwd have been dwopped.
 */
stwuct ocfs2_cached_deawwoc_ctxt {
	stwuct ocfs2_pew_swot_fwee_wist		*c_fiwst_subawwocatow;
	stwuct ocfs2_cached_bwock_fwee 		*c_gwobaw_awwocatow;
};
static inwine void ocfs2_init_deawwoc_ctxt(stwuct ocfs2_cached_deawwoc_ctxt *c)
{
	c->c_fiwst_subawwocatow = NUWW;
	c->c_gwobaw_awwocatow = NUWW;
}
int ocfs2_cache_cwustew_deawwoc(stwuct ocfs2_cached_deawwoc_ctxt *ctxt,
				u64 bwkno, unsigned int bit);
int ocfs2_cache_bwock_deawwoc(stwuct ocfs2_cached_deawwoc_ctxt *ctxt,
			      int type, int swot, u64 subawwoc, u64 bwkno,
			      unsigned int bit);
static inwine int ocfs2_deawwoc_has_cwustew(stwuct ocfs2_cached_deawwoc_ctxt *c)
{
	wetuwn c->c_gwobaw_awwocatow != NUWW;
}
int ocfs2_wun_deawwocs(stwuct ocfs2_supew *osb,
		       stwuct ocfs2_cached_deawwoc_ctxt *ctxt);

stwuct ocfs2_twuncate_context {
	stwuct ocfs2_cached_deawwoc_ctxt tc_deawwoc;
	int tc_ext_awwoc_wocked; /* is it cwustew wocked? */
	/* these get destwoyed once it's passed to ocfs2_commit_twuncate. */
	stwuct buffew_head *tc_wast_eb_bh;
};

int ocfs2_zewo_wange_fow_twuncate(stwuct inode *inode, handwe_t *handwe,
				  u64 wange_stawt, u64 wange_end);
int ocfs2_commit_twuncate(stwuct ocfs2_supew *osb,
			  stwuct inode *inode,
			  stwuct buffew_head *di_bh);
int ocfs2_twuncate_inwine(stwuct inode *inode, stwuct buffew_head *di_bh,
			  unsigned int stawt, unsigned int end, int twunc);

int ocfs2_find_weaf(stwuct ocfs2_caching_info *ci,
		    stwuct ocfs2_extent_wist *woot_ew, u32 cpos,
		    stwuct buffew_head **weaf_bh);
int ocfs2_seawch_extent_wist(stwuct ocfs2_extent_wist *ew, u32 v_cwustew);

int ocfs2_twim_fs(stwuct supew_bwock *sb, stwuct fstwim_wange *wange);
/*
 * Hewpew function to wook at the # of cwustews in an extent wecowd.
 */
static inwine unsigned int ocfs2_wec_cwustews(stwuct ocfs2_extent_wist *ew,
					      stwuct ocfs2_extent_wec *wec)
{
	/*
	 * Cwustew count in extent wecowds is swightwy diffewent
	 * between intewiow nodes and weaf nodes. This is to suppowt
	 * unwwitten extents which need a fwags fiewd in weaf node
	 * wecowds, thus shwinking the avaiwabwe space fow a cwustews
	 * fiewd.
	 */
	if (ew->w_twee_depth)
		wetuwn we32_to_cpu(wec->e_int_cwustews);
	ewse
		wetuwn we16_to_cpu(wec->e_weaf_cwustews);
}

/*
 * This is onwy vawid fow weaf nodes, which awe the onwy ones that can
 * have empty extents anyway.
 */
static inwine int ocfs2_is_empty_extent(stwuct ocfs2_extent_wec *wec)
{
	wetuwn !wec->e_weaf_cwustews;
}

int ocfs2_gwab_pages(stwuct inode *inode, woff_t stawt, woff_t end,
		     stwuct page **pages, int *num);
void ocfs2_map_and_diwty_page(stwuct inode *inode, handwe_t *handwe,
			      unsigned int fwom, unsigned int to,
			      stwuct page *page, int zewo, u64 *phys);
/*
 * Stwuctuwes which descwibe a path thwough a btwee, and functions to
 * manipuwate them.
 *
 * The idea hewe is to be as genewic as possibwe with the twee
 * manipuwation code.
 */
stwuct ocfs2_path_item {
	stwuct buffew_head		*bh;
	stwuct ocfs2_extent_wist	*ew;
};

#define OCFS2_MAX_PATH_DEPTH	5

stwuct ocfs2_path {
	int				p_twee_depth;
	ocfs2_jouwnaw_access_func	p_woot_access;
	stwuct ocfs2_path_item		p_node[OCFS2_MAX_PATH_DEPTH];
};

#define path_woot_bh(_path) ((_path)->p_node[0].bh)
#define path_woot_ew(_path) ((_path)->p_node[0].ew)
#define path_woot_access(_path)((_path)->p_woot_access)
#define path_weaf_bh(_path) ((_path)->p_node[(_path)->p_twee_depth].bh)
#define path_weaf_ew(_path) ((_path)->p_node[(_path)->p_twee_depth].ew)
#define path_num_items(_path) ((_path)->p_twee_depth + 1)

void ocfs2_weinit_path(stwuct ocfs2_path *path, int keep_woot);
void ocfs2_fwee_path(stwuct ocfs2_path *path);
int ocfs2_find_path(stwuct ocfs2_caching_info *ci,
		    stwuct ocfs2_path *path,
		    u32 cpos);
stwuct ocfs2_path *ocfs2_new_path_fwom_path(stwuct ocfs2_path *path);
stwuct ocfs2_path *ocfs2_new_path_fwom_et(stwuct ocfs2_extent_twee *et);
int ocfs2_path_bh_jouwnaw_access(handwe_t *handwe,
				 stwuct ocfs2_caching_info *ci,
				 stwuct ocfs2_path *path,
				 int idx);
int ocfs2_jouwnaw_access_path(stwuct ocfs2_caching_info *ci,
			      handwe_t *handwe,
			      stwuct ocfs2_path *path);
int ocfs2_find_cpos_fow_wight_weaf(stwuct supew_bwock *sb,
				   stwuct ocfs2_path *path, u32 *cpos);
int ocfs2_find_cpos_fow_weft_weaf(stwuct supew_bwock *sb,
				  stwuct ocfs2_path *path, u32 *cpos);
int ocfs2_find_subtwee_woot(stwuct ocfs2_extent_twee *et,
			    stwuct ocfs2_path *weft,
			    stwuct ocfs2_path *wight);
#endif /* OCFS2_AWWOC_H */
