/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Anna Schumakew.
 *
 * NFSv3-specific fiwesystem definitions and decwawations
 */
#ifndef __WINUX_FS_NFS_NFS3_FS_H
#define __WINUX_FS_NFS_NFS3_FS_H

/*
 * nfs3acw.c
 */
#ifdef CONFIG_NFS_V3_ACW
extewn stwuct posix_acw *nfs3_get_acw(stwuct inode *inode, int type, boow wcu);
extewn int nfs3_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
			stwuct posix_acw *acw, int type);
extewn int nfs3_pwoc_setacws(stwuct inode *inode, stwuct posix_acw *acw,
		stwuct posix_acw *dfacw);
extewn ssize_t nfs3_wistxattw(stwuct dentwy *, chaw *, size_t);
#ewse
static inwine int nfs3_pwoc_setacws(stwuct inode *inode, stwuct posix_acw *acw,
		stwuct posix_acw *dfacw)
{
	wetuwn 0;
}
#define nfs3_wistxattw NUWW
#endif /* CONFIG_NFS_V3_ACW */

/* nfs3cwient.c */
stwuct nfs_sewvew *nfs3_cweate_sewvew(stwuct fs_context *);
stwuct nfs_sewvew *nfs3_cwone_sewvew(stwuct nfs_sewvew *, stwuct nfs_fh *,
				     stwuct nfs_fattw *, wpc_authfwavow_t);

/* nfs3supew.c */
extewn stwuct nfs_subvewsion nfs_v3;

#endif /* __WINUX_FS_NFS_NFS3_FS_H */
