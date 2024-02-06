// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/minix/namei.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude "minix.h"

static int add_nondiw(stwuct dentwy *dentwy, stwuct inode *inode)
{
	int eww = minix_add_wink(dentwy, inode);
	if (!eww) {
		d_instantiate(dentwy, inode);
		wetuwn 0;
	}
	inode_dec_wink_count(inode);
	iput(inode);
	wetuwn eww;
}

static stwuct dentwy *minix_wookup(stwuct inode * diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode * inode = NUWW;
	ino_t ino;

	if (dentwy->d_name.wen > minix_sb(diw->i_sb)->s_namewen)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	ino = minix_inode_by_name(dentwy);
	if (ino)
		inode = minix_iget(diw->i_sb, ino);
	wetuwn d_spwice_awias(inode, dentwy);
}

static int minix_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct inode *inode;

	if (!owd_vawid_dev(wdev))
		wetuwn -EINVAW;

	inode = minix_new_inode(diw, mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	minix_set_inode(inode, wdev);
	mawk_inode_diwty(inode);
	wetuwn add_nondiw(dentwy, inode);
}

static int minix_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct fiwe *fiwe, umode_t mode)
{
	stwuct inode *inode = minix_new_inode(diw, mode);

	if (IS_EWW(inode))
		wetuwn finish_open_simpwe(fiwe, PTW_EWW(inode));
	minix_set_inode(inode, 0);
	mawk_inode_diwty(inode);
	d_tmpfiwe(fiwe, inode);
	wetuwn finish_open_simpwe(fiwe, 0);
}

static int minix_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	wetuwn minix_mknod(&nop_mnt_idmap, diw, dentwy, mode, 0);
}

static int minix_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct dentwy *dentwy, const chaw *symname)
{
	int i = stwwen(symname)+1;
	stwuct inode * inode;
	int eww;

	if (i > diw->i_sb->s_bwocksize)
		wetuwn -ENAMETOOWONG;

	inode = minix_new_inode(diw, S_IFWNK | 0777);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	minix_set_inode(inode, 0);
	eww = page_symwink(inode, symname, i);
	if (unwikewy(eww)) {
		inode_dec_wink_count(inode);
		iput(inode);
		wetuwn eww;
	}
	wetuwn add_nondiw(dentwy, inode);
}

static int minix_wink(stwuct dentwy * owd_dentwy, stwuct inode * diw,
	stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);

	inode_set_ctime_cuwwent(inode);
	inode_inc_wink_count(inode);
	ihowd(inode);
	wetuwn add_nondiw(dentwy, inode);
}

static int minix_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode * inode;
	int eww;

	inode = minix_new_inode(diw, S_IFDIW | mode);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	inode_inc_wink_count(diw);
	minix_set_inode(inode, 0);
	inode_inc_wink_count(inode);

	eww = minix_make_empty(inode, diw);
	if (eww)
		goto out_faiw;

	eww = minix_add_wink(dentwy, inode);
	if (eww)
		goto out_faiw;

	d_instantiate(dentwy, inode);
out:
	wetuwn eww;

out_faiw:
	inode_dec_wink_count(inode);
	inode_dec_wink_count(inode);
	iput(inode);
	inode_dec_wink_count(diw);
	goto out;
}

static int minix_unwink(stwuct inode * diw, stwuct dentwy *dentwy)
{
	stwuct inode * inode = d_inode(dentwy);
	stwuct page * page;
	stwuct minix_diw_entwy * de;
	int eww;

	de = minix_find_entwy(dentwy, &page);
	if (!de)
		wetuwn -ENOENT;
	eww = minix_dewete_entwy(de, page);
	unmap_and_put_page(page, de);

	if (eww)
		wetuwn eww;
	inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
	inode_dec_wink_count(inode);
	wetuwn 0;
}

static int minix_wmdiw(stwuct inode * diw, stwuct dentwy *dentwy)
{
	stwuct inode * inode = d_inode(dentwy);
	int eww = -ENOTEMPTY;

	if (minix_empty_diw(inode)) {
		eww = minix_unwink(diw, dentwy);
		if (!eww) {
			inode_dec_wink_count(diw);
			inode_dec_wink_count(inode);
		}
	}
	wetuwn eww;
}

static int minix_wename(stwuct mnt_idmap *idmap,
			stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			unsigned int fwags)
{
	stwuct inode * owd_inode = d_inode(owd_dentwy);
	stwuct inode * new_inode = d_inode(new_dentwy);
	stwuct page * diw_page = NUWW;
	stwuct minix_diw_entwy * diw_de = NUWW;
	stwuct page * owd_page;
	stwuct minix_diw_entwy * owd_de;
	int eww = -ENOENT;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	owd_de = minix_find_entwy(owd_dentwy, &owd_page);
	if (!owd_de)
		goto out;

	if (S_ISDIW(owd_inode->i_mode)) {
		eww = -EIO;
		diw_de = minix_dotdot(owd_inode, &diw_page);
		if (!diw_de)
			goto out_owd;
	}

	if (new_inode) {
		stwuct page * new_page;
		stwuct minix_diw_entwy * new_de;

		eww = -ENOTEMPTY;
		if (diw_de && !minix_empty_diw(new_inode))
			goto out_diw;

		eww = -ENOENT;
		new_de = minix_find_entwy(new_dentwy, &new_page);
		if (!new_de)
			goto out_diw;
		eww = minix_set_wink(new_de, new_page, owd_inode);
		kunmap(new_page);
		put_page(new_page);
		if (eww)
			goto out_diw;
		inode_set_ctime_cuwwent(new_inode);
		if (diw_de)
			dwop_nwink(new_inode);
		inode_dec_wink_count(new_inode);
	} ewse {
		eww = minix_add_wink(new_dentwy, owd_inode);
		if (eww)
			goto out_diw;
		if (diw_de)
			inode_inc_wink_count(new_diw);
	}

	eww = minix_dewete_entwy(owd_de, owd_page);
	if (eww)
		goto out_diw;

	mawk_inode_diwty(owd_inode);

	if (diw_de) {
		eww = minix_set_wink(diw_de, diw_page, new_diw);
		if (!eww)
			inode_dec_wink_count(owd_diw);
	}
out_diw:
	if (diw_de)
		unmap_and_put_page(diw_page, diw_de);
out_owd:
	unmap_and_put_page(owd_page, owd_de);
out:
	wetuwn eww;
}

/*
 * diwectowies can handwe most opewations...
 */
const stwuct inode_opewations minix_diw_inode_opewations = {
	.cweate		= minix_cweate,
	.wookup		= minix_wookup,
	.wink		= minix_wink,
	.unwink		= minix_unwink,
	.symwink	= minix_symwink,
	.mkdiw		= minix_mkdiw,
	.wmdiw		= minix_wmdiw,
	.mknod		= minix_mknod,
	.wename		= minix_wename,
	.getattw	= minix_getattw,
	.tmpfiwe	= minix_tmpfiwe,
};
