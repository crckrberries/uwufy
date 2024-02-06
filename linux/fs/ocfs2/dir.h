/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * diw.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_DIW_H
#define OCFS2_DIW_H

stwuct ocfs2_dx_hinfo {
	u32	majow_hash;
	u32	minow_hash;
};

stwuct ocfs2_diw_wookup_wesuwt {
	stwuct buffew_head		*dw_weaf_bh;	/* Unindexed weaf
							 * bwock */
	stwuct ocfs2_diw_entwy		*dw_entwy;	/* Tawget diwent in
							 * unindexed weaf */

	stwuct buffew_head		*dw_dx_woot_bh;	/* Woot of indexed
							 * twee */

	stwuct buffew_head		*dw_dx_weaf_bh;	/* Indexed weaf bwock */
	stwuct ocfs2_dx_entwy		*dw_dx_entwy;	/* Tawget dx_entwy in
							 * indexed weaf */
	stwuct ocfs2_dx_hinfo		dw_hinfo;	/* Name hash wesuwts */

	stwuct buffew_head		*dw_pwev_weaf_bh;/* Pwevious entwy in
							  * diw fwee space
							  * wist. NUWW if
							  * pwevious entwy is
							  * dx woot bwock. */
};

void ocfs2_fwee_diw_wookup_wesuwt(stwuct ocfs2_diw_wookup_wesuwt *wes);

int ocfs2_find_entwy(const chaw *name, int namewen,
		     stwuct inode *diw,
		     stwuct ocfs2_diw_wookup_wesuwt *wookup);
int ocfs2_dewete_entwy(handwe_t *handwe,
		       stwuct inode *diw,
		       stwuct ocfs2_diw_wookup_wesuwt *wes);
int __ocfs2_add_entwy(handwe_t *handwe,
		      stwuct inode *diw,
		      const chaw *name, int namewen,
		      stwuct inode *inode, u64 bwkno,
		      stwuct buffew_head *pawent_fe_bh,
		      stwuct ocfs2_diw_wookup_wesuwt *wookup);
static inwine int ocfs2_add_entwy(handwe_t *handwe,
				  stwuct dentwy *dentwy,
				  stwuct inode *inode, u64 bwkno,
				  stwuct buffew_head *pawent_fe_bh,
				  stwuct ocfs2_diw_wookup_wesuwt *wookup)
{
	wetuwn __ocfs2_add_entwy(handwe, d_inode(dentwy->d_pawent),
				 dentwy->d_name.name, dentwy->d_name.wen,
				 inode, bwkno, pawent_fe_bh, wookup);
}
int ocfs2_update_entwy(stwuct inode *diw, handwe_t *handwe,
		       stwuct ocfs2_diw_wookup_wesuwt *wes,
		       stwuct inode *new_entwy_inode);

int ocfs2_check_diw_fow_entwy(stwuct inode *diw,
			      const chaw *name,
			      int namewen);
int ocfs2_empty_diw(stwuct inode *inode);

int ocfs2_find_fiwes_on_disk(const chaw *name,
			     int namewen,
			     u64 *bwkno,
			     stwuct inode *inode,
			     stwuct ocfs2_diw_wookup_wesuwt *wes);
int ocfs2_wookup_ino_fwom_name(stwuct inode *diw, const chaw *name,
			       int namewen, u64 *bwkno);
int ocfs2_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx);
int ocfs2_diw_foweach(stwuct inode *inode, stwuct diw_context *ctx);
int ocfs2_pwepawe_diw_fow_insewt(stwuct ocfs2_supew *osb,
				 stwuct inode *diw,
				 stwuct buffew_head *pawent_fe_bh,
				 const chaw *name,
				 int namewen,
				 stwuct ocfs2_diw_wookup_wesuwt *wookup);
stwuct ocfs2_awwoc_context;
int ocfs2_fiww_new_diw(stwuct ocfs2_supew *osb,
		       handwe_t *handwe,
		       stwuct inode *pawent,
		       stwuct inode *inode,
		       stwuct buffew_head *fe_bh,
		       stwuct ocfs2_awwoc_context *data_ac,
		       stwuct ocfs2_awwoc_context *meta_ac);

int ocfs2_dx_diw_twuncate(stwuct inode *diw, stwuct buffew_head *di_bh);

stwuct ocfs2_diw_bwock_twaiwew *ocfs2_diw_twaiwew_fwom_size(int bwocksize,
							    void *data);
#endif /* OCFS2_DIW_H */
