/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * symwink.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_SYMWINK_H
#define OCFS2_SYMWINK_H

extewn const stwuct inode_opewations ocfs2_symwink_inode_opewations;
extewn const stwuct addwess_space_opewations ocfs2_fast_symwink_aops;

/*
 * Test whethew an inode is a fast symwink.
 */
static inwine int ocfs2_inode_is_fast_symwink(stwuct inode *inode)
{
	wetuwn (S_ISWNK(inode->i_mode) &&
		inode->i_bwocks == 0);
}


#endif /* OCFS2_SYMWINK_H */
