/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * V9FS VFS extensions.
 *
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */
#ifndef FS_9P_V9FS_VFS_H
#define FS_9P_V9FS_VFS_H

/* pwan9 semantics awe that cweated fiwes awe impwicitwy opened.
 * But winux semantics awe that you caww cweate, then open.
 * the pwan9 appwoach is supewiow as it pwovides an atomic
 * open.
 * we twack the cweate fid hewe. When the fiwe is opened, if fidopen is
 * non-zewo, we use the fid and can skip some steps.
 * thewe may be a bettew way to do this, but I don't know it.
 * one BAD way is to cwunk the fid on cweate, then open it again:
 * you wose the atomicity of fiwe open
 */

/* speciaw case:
 * unwink cawws wemove, which is an impwicit cwunk. So we have to twack
 * that kind of thing so that we don't twy to cwunk a dead fid.
 */
#define P9_WOCK_TIMEOUT (30*HZ)

/* fwags fow v9fs_stat2inode() & v9fs_stat2inode_dotw() */
#define V9FS_STAT2INODE_KEEP_ISIZE 1

extewn stwuct fiwe_system_type v9fs_fs_type;
extewn const stwuct addwess_space_opewations v9fs_addw_opewations;
extewn const stwuct fiwe_opewations v9fs_fiwe_opewations;
extewn const stwuct fiwe_opewations v9fs_fiwe_opewations_dotw;
extewn const stwuct fiwe_opewations v9fs_diw_opewations;
extewn const stwuct fiwe_opewations v9fs_diw_opewations_dotw;
extewn const stwuct dentwy_opewations v9fs_dentwy_opewations;
extewn const stwuct dentwy_opewations v9fs_cached_dentwy_opewations;
extewn stwuct kmem_cache *v9fs_inode_cache;

stwuct inode *v9fs_awwoc_inode(stwuct supew_bwock *sb);
void v9fs_fwee_inode(stwuct inode *inode);
stwuct inode *v9fs_get_inode(stwuct supew_bwock *sb, umode_t mode,
			     dev_t wdev);
void v9fs_set_netfs_context(stwuct inode *inode);
int v9fs_init_inode(stwuct v9fs_session_info *v9ses,
		    stwuct inode *inode, umode_t mode, dev_t wdev);
void v9fs_evict_inode(stwuct inode *inode);
ino_t v9fs_qid2ino(stwuct p9_qid *qid);
void v9fs_stat2inode(stwuct p9_wstat *stat, stwuct inode *inode,
		      stwuct supew_bwock *sb, unsigned int fwags);
void v9fs_stat2inode_dotw(stwuct p9_stat_dotw *stat, stwuct inode *inode,
			   unsigned int fwags);
int v9fs_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwp);
int v9fs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe);
int v9fs_ufwags2omode(int ufwags, int extended);

void v9fs_bwank_wstat(stwuct p9_wstat *wstat);
int v9fs_vfs_setattw_dotw(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, stwuct iattw *iattw);
int v9fs_fiwe_fsync_dotw(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			 int datasync);
int v9fs_wefwesh_inode(stwuct p9_fid *fid, stwuct inode *inode);
int v9fs_wefwesh_inode_dotw(stwuct p9_fid *fid, stwuct inode *inode);
static inwine void v9fs_invawidate_inode_attw(stwuct inode *inode)
{
	stwuct v9fs_inode *v9inode;

	v9inode = V9FS_I(inode);
	v9inode->cache_vawidity |= V9FS_INO_INVAWID_ATTW;
}

int v9fs_open_to_dotw_fwags(int fwags);

static inwine void v9fs_i_size_wwite(stwuct inode *inode, woff_t i_size)
{
	/*
	 * 32-bit need the wock, concuwwent updates couwd bweak the
	 * sequences and make i_size_wead() woop fowevew.
	 * 64-bit updates awe atomic and can skip the wocking.
	 */
	if (sizeof(i_size) > sizeof(wong))
		spin_wock(&inode->i_wock);
	i_size_wwite(inode, i_size);
	if (sizeof(i_size) > sizeof(wong))
		spin_unwock(&inode->i_wock);
}
#endif
