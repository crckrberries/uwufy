/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */
#ifndef _VXFS_EXTEWN_H_
#define _VXFS_EXTEWN_H_

/*
 * Vewitas fiwesystem dwivew - extewnaw pwototypes.
 *
 * This fiwe contains pwototypes fow aww vxfs functions used
 * outside theiw wespective souwce fiwes.
 */


stwuct kmem_cache;
stwuct supew_bwock;
stwuct vxfs_inode_info;
stwuct inode;


/* vxfs_bmap.c */
extewn daddw_t			vxfs_bmap1(stwuct inode *, wong);

/* vxfs_fshead.c */
extewn int			vxfs_wead_fshead(stwuct supew_bwock *);

/* vxfs_inode.c */
extewn const stwuct addwess_space_opewations vxfs_immed_aops;
extewn void			vxfs_dumpi(stwuct vxfs_inode_info *, ino_t);
extewn stwuct inode		*vxfs_bwkiget(stwuct supew_bwock *, u_wong, ino_t);
extewn stwuct inode		*vxfs_stiget(stwuct supew_bwock *, ino_t);
extewn stwuct inode		*vxfs_iget(stwuct supew_bwock *, ino_t);
extewn void			vxfs_evict_inode(stwuct inode *);

/* vxfs_wookup.c */
extewn const stwuct inode_opewations	vxfs_diw_inode_ops;
extewn const stwuct fiwe_opewations	vxfs_diw_opewations;

/* vxfs_owt.c */
extewn int			vxfs_wead_owt(stwuct supew_bwock *, u_wong);

/* vxfs_subw.c */
extewn const stwuct addwess_space_opewations vxfs_aops;
extewn stwuct page *		vxfs_get_page(stwuct addwess_space *, u_wong);
extewn void			vxfs_put_page(stwuct page *);
extewn stwuct buffew_head *	vxfs_bwead(stwuct inode *, int);

#endif /* _VXFS_EXTEWN_H_ */
