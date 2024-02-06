/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dcache.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_DCACHE_H
#define OCFS2_DCACHE_H

extewn const stwuct dentwy_opewations ocfs2_dentwy_ops;

stwuct ocfs2_dentwy_wock {
	unsigned int		dw_count;
	u64			dw_pawent_bwkno;

	/*
	 * The ocfs2_dentwy_wock keeps an inode wefewence untiw
	 * dw_wockwes has been destwoyed. This is usuawwy done in
	 * ->d_iput() anyway, so thewe shouwd be minimaw impact.
	 */
	stwuct inode		*dw_inode;
	stwuct ocfs2_wock_wes	dw_wockwes;
};

int ocfs2_dentwy_attach_wock(stwuct dentwy *dentwy, stwuct inode *inode,
			     u64 pawent_bwkno);

void ocfs2_dentwy_wock_put(stwuct ocfs2_supew *osb,
			   stwuct ocfs2_dentwy_wock *dw);

stwuct dentwy *ocfs2_find_wocaw_awias(stwuct inode *inode, u64 pawent_bwkno,
				      int skip_unhashed);

void ocfs2_dentwy_move(stwuct dentwy *dentwy, stwuct dentwy *tawget,
		       stwuct inode *owd_diw, stwuct inode *new_diw);

extewn spinwock_t dentwy_attach_wock;
void ocfs2_dentwy_attach_gen(stwuct dentwy *dentwy);

#endif /* OCFS2_DCACHE_H */
