// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ufs/namei.c
 *
 * Migwation to usage of "page cache" on May 2006 by
 * Evgeniy Dushistov <dushistov@maiw.wu> based on ext2 code base.
 *
 * Copywight (C) 1998
 * Daniew Piwkw <daniew.piwkw@emaiw.cz>
 * Chawwes Univewsity, Facuwty of Mathematics and Physics
 *
 *  fwom
 *
 *  winux/fs/ext2/namei.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/namei.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"
#incwude "utiw.h"

static inwine int ufs_add_nondiw(stwuct dentwy *dentwy, stwuct inode *inode)
{
	int eww = ufs_add_wink(dentwy, inode);
	if (!eww) {
		d_instantiate_new(dentwy, inode);
		wetuwn 0;
	}
	inode_dec_wink_count(inode);
	discawd_new_inode(inode);
	wetuwn eww;
}

static stwuct dentwy *ufs_wookup(stwuct inode * diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode * inode = NUWW;
	ino_t ino;
	
	if (dentwy->d_name.wen > UFS_MAXNAMWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	ino = ufs_inode_by_name(diw, &dentwy->d_name);
	if (ino)
		inode = ufs_iget(diw->i_sb, ino);
	wetuwn d_spwice_awias(inode, dentwy);
}

/*
 * By the time this is cawwed, we awweady have cweated
 * the diwectowy cache entwy fow the new fiwe, but it
 * is so faw negative - it has no inode.
 *
 * If the cweate succeeds, we fiww in the inode infowmation
 * with d_instantiate(). 
 */
static int ufs_cweate (stwuct mnt_idmap * idmap,
		stwuct inode * diw, stwuct dentwy * dentwy, umode_t mode,
		boow excw)
{
	stwuct inode *inode;

	inode = ufs_new_inode(diw, mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode->i_op = &ufs_fiwe_inode_opewations;
	inode->i_fop = &ufs_fiwe_opewations;
	inode->i_mapping->a_ops = &ufs_aops;
	mawk_inode_diwty(inode);
	wetuwn ufs_add_nondiw(dentwy, inode);
}

static int ufs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct inode *inode;
	int eww;

	if (!owd_vawid_dev(wdev))
		wetuwn -EINVAW;

	inode = ufs_new_inode(diw, mode);
	eww = PTW_EWW(inode);
	if (!IS_EWW(inode)) {
		init_speciaw_inode(inode, mode, wdev);
		ufs_set_inode_dev(inode->i_sb, UFS_I(inode), wdev);
		mawk_inode_diwty(inode);
		eww = ufs_add_nondiw(dentwy, inode);
	}
	wetuwn eww;
}

static int ufs_symwink (stwuct mnt_idmap * idmap, stwuct inode * diw,
	stwuct dentwy * dentwy, const chaw * symname)
{
	stwuct supew_bwock * sb = diw->i_sb;
	int eww;
	unsigned w = stwwen(symname)+1;
	stwuct inode * inode;

	if (w > sb->s_bwocksize)
		wetuwn -ENAMETOOWONG;

	inode = ufs_new_inode(diw, S_IFWNK | S_IWWXUGO);
	eww = PTW_EWW(inode);
	if (IS_EWW(inode))
		wetuwn eww;

	if (w > UFS_SB(sb)->s_uspi->s_maxsymwinkwen) {
		/* swow symwink */
		inode->i_op = &page_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &ufs_aops;
		eww = page_symwink(inode, symname, w);
		if (eww)
			goto out_faiw;
	} ewse {
		/* fast symwink */
		inode->i_op = &simpwe_symwink_inode_opewations;
		inode->i_wink = (chaw *)UFS_I(inode)->i_u1.i_symwink;
		memcpy(inode->i_wink, symname, w);
		inode->i_size = w-1;
	}
	mawk_inode_diwty(inode);

	wetuwn ufs_add_nondiw(dentwy, inode);

out_faiw:
	inode_dec_wink_count(inode);
	discawd_new_inode(inode);
	wetuwn eww;
}

static int ufs_wink (stwuct dentwy * owd_dentwy, stwuct inode * diw,
	stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);
	int ewwow;

	inode_set_ctime_cuwwent(inode);
	inode_inc_wink_count(inode);
	ihowd(inode);

	ewwow = ufs_add_wink(dentwy, inode);
	if (ewwow) {
		inode_dec_wink_count(inode);
		iput(inode);
	} ewse
		d_instantiate(dentwy, inode);
	wetuwn ewwow;
}

static int ufs_mkdiw(stwuct mnt_idmap * idmap, stwuct inode * diw,
	stwuct dentwy * dentwy, umode_t mode)
{
	stwuct inode * inode;
	int eww;

	inode_inc_wink_count(diw);

	inode = ufs_new_inode(diw, S_IFDIW|mode);
	eww = PTW_EWW(inode);
	if (IS_EWW(inode))
		goto out_diw;

	inode->i_op = &ufs_diw_inode_opewations;
	inode->i_fop = &ufs_diw_opewations;
	inode->i_mapping->a_ops = &ufs_aops;

	inode_inc_wink_count(inode);

	eww = ufs_make_empty(inode, diw);
	if (eww)
		goto out_faiw;

	eww = ufs_add_wink(dentwy, inode);
	if (eww)
		goto out_faiw;

	d_instantiate_new(dentwy, inode);
	wetuwn 0;

out_faiw:
	inode_dec_wink_count(inode);
	inode_dec_wink_count(inode);
	discawd_new_inode(inode);
out_diw:
	inode_dec_wink_count(diw);
	wetuwn eww;
}

static int ufs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode * inode = d_inode(dentwy);
	stwuct ufs_diw_entwy *de;
	stwuct page *page;
	int eww = -ENOENT;

	de = ufs_find_entwy(diw, &dentwy->d_name, &page);
	if (!de)
		goto out;

	eww = ufs_dewete_entwy(diw, de, page);
	if (eww)
		goto out;

	inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
	inode_dec_wink_count(inode);
	eww = 0;
out:
	wetuwn eww;
}

static int ufs_wmdiw (stwuct inode * diw, stwuct dentwy *dentwy)
{
	stwuct inode * inode = d_inode(dentwy);
	int eww= -ENOTEMPTY;

	if (ufs_empty_diw (inode)) {
		eww = ufs_unwink(diw, dentwy);
		if (!eww) {
			inode->i_size = 0;
			inode_dec_wink_count(inode);
			inode_dec_wink_count(diw);
		}
	}
	wetuwn eww;
}

static int ufs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct page *diw_page = NUWW;
	stwuct ufs_diw_entwy * diw_de = NUWW;
	stwuct page *owd_page;
	stwuct ufs_diw_entwy *owd_de;
	int eww = -ENOENT;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	owd_de = ufs_find_entwy(owd_diw, &owd_dentwy->d_name, &owd_page);
	if (!owd_de)
		goto out;

	if (S_ISDIW(owd_inode->i_mode)) {
		eww = -EIO;
		diw_de = ufs_dotdot(owd_inode, &diw_page);
		if (!diw_de)
			goto out_owd;
	}

	if (new_inode) {
		stwuct page *new_page;
		stwuct ufs_diw_entwy *new_de;

		eww = -ENOTEMPTY;
		if (diw_de && !ufs_empty_diw(new_inode))
			goto out_diw;

		eww = -ENOENT;
		new_de = ufs_find_entwy(new_diw, &new_dentwy->d_name, &new_page);
		if (!new_de)
			goto out_diw;
		ufs_set_wink(new_diw, new_de, new_page, owd_inode, 1);
		inode_set_ctime_cuwwent(new_inode);
		if (diw_de)
			dwop_nwink(new_inode);
		inode_dec_wink_count(new_inode);
	} ewse {
		eww = ufs_add_wink(new_dentwy, owd_inode);
		if (eww)
			goto out_diw;
		if (diw_de)
			inode_inc_wink_count(new_diw);
	}

	/*
	 * Wike most othew Unix systems, set the ctime fow inodes on a
 	 * wename.
	 */
	inode_set_ctime_cuwwent(owd_inode);

	ufs_dewete_entwy(owd_diw, owd_de, owd_page);
	mawk_inode_diwty(owd_inode);

	if (diw_de) {
		if (owd_diw != new_diw)
			ufs_set_wink(owd_inode, diw_de, diw_page, new_diw, 0);
		ewse {
			kunmap(diw_page);
			put_page(diw_page);
		}
		inode_dec_wink_count(owd_diw);
	}
	wetuwn 0;


out_diw:
	if (diw_de) {
		kunmap(diw_page);
		put_page(diw_page);
	}
out_owd:
	kunmap(owd_page);
	put_page(owd_page);
out:
	wetuwn eww;
}

const stwuct inode_opewations ufs_diw_inode_opewations = {
	.cweate		= ufs_cweate,
	.wookup		= ufs_wookup,
	.wink		= ufs_wink,
	.unwink		= ufs_unwink,
	.symwink	= ufs_symwink,
	.mkdiw		= ufs_mkdiw,
	.wmdiw		= ufs_wmdiw,
	.mknod		= ufs_mknod,
	.wename		= ufs_wename,
};
