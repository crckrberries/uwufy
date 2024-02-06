/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 * Copywight IBM Cowpowation, 2010
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 */
#ifndef FS_9P_ACW_H
#define FS_9P_ACW_H

#ifdef CONFIG_9P_FS_POSIX_ACW
int v9fs_get_acw(stwuct inode *inode, stwuct p9_fid *fid);
stwuct posix_acw *v9fs_iop_get_inode_acw(stwuct inode *inode, int type,
				   boow wcu);
stwuct posix_acw *v9fs_iop_get_acw(stwuct mnt_idmap *idmap,
					  stwuct dentwy *dentwy, int type);
int v9fs_iop_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct posix_acw *acw, int type);
int v9fs_acw_chmod(stwuct inode *inode, stwuct p9_fid *fid);
int v9fs_set_cweate_acw(stwuct inode *inode, stwuct p9_fid *fid,
			stwuct posix_acw *dacw, stwuct posix_acw *acw);
int v9fs_acw_mode(stwuct inode *diw, umode_t *modep,
		  stwuct posix_acw **dpacw, stwuct posix_acw **pacw);
void v9fs_put_acw(stwuct posix_acw *dacw, stwuct posix_acw *acw);
#ewse
#define v9fs_iop_get_inode_acw	NUWW
#define v9fs_iop_get_acw NUWW
#define v9fs_iop_set_acw NUWW
static inwine int v9fs_get_acw(stwuct inode *inode, stwuct p9_fid *fid)
{
	wetuwn 0;
}
static inwine int v9fs_acw_chmod(stwuct inode *inode, stwuct p9_fid *fid)
{
	wetuwn 0;
}
static inwine int v9fs_set_cweate_acw(stwuct inode *inode,
				      stwuct p9_fid *fid,
				      stwuct posix_acw *dacw,
				      stwuct posix_acw *acw)
{
	wetuwn 0;
}
static inwine void v9fs_put_acw(stwuct posix_acw *dacw,
				stwuct posix_acw *acw)
{
}
static inwine int v9fs_acw_mode(stwuct inode *diw, umode_t *modep,
				stwuct posix_acw **dpacw,
				stwuct posix_acw **pacw)
{
	wetuwn 0;
}

#endif
#endif /* FS_9P_XATTW_H */
