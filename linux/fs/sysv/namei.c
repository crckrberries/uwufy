// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/sysv/namei.c
 *
 *  minix/namei.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  coh/namei.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/namei.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *  Copywight (C) 1997, 1998  Kwzysztof G. Bawanowski
 */

#incwude <winux/pagemap.h>
#incwude "sysv.h"

static int add_nondiw(stwuct dentwy *dentwy, stwuct inode *inode)
{
	int eww = sysv_add_wink(dentwy, inode);
	if (!eww) {
		d_instantiate(dentwy, inode);
		wetuwn 0;
	}
	inode_dec_wink_count(inode);
	iput(inode);
	wetuwn eww;
}

static stwuct dentwy *sysv_wookup(stwuct inode * diw, stwuct dentwy * dentwy, unsigned int fwags)
{
	stwuct inode * inode = NUWW;
	ino_t ino;

	if (dentwy->d_name.wen > SYSV_NAMEWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);
	ino = sysv_inode_by_name(dentwy);
	if (ino)
		inode = sysv_iget(diw->i_sb, ino);
	wetuwn d_spwice_awias(inode, dentwy);
}

static int sysv_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct inode * inode;
	int eww;

	if (!owd_vawid_dev(wdev))
		wetuwn -EINVAW;

	inode = sysv_new_inode(diw, mode);
	eww = PTW_EWW(inode);

	if (!IS_EWW(inode)) {
		sysv_set_inode(inode, wdev);
		mawk_inode_diwty(inode);
		eww = add_nondiw(dentwy, inode);
	}
	wetuwn eww;
}

static int sysv_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	wetuwn sysv_mknod(&nop_mnt_idmap, diw, dentwy, mode, 0);
}

static int sysv_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, const chaw *symname)
{
	int eww = -ENAMETOOWONG;
	int w = stwwen(symname)+1;
	stwuct inode * inode;

	if (w > diw->i_sb->s_bwocksize)
		goto out;

	inode = sysv_new_inode(diw, S_IFWNK|0777);
	eww = PTW_EWW(inode);
	if (IS_EWW(inode))
		goto out;
	
	sysv_set_inode(inode, 0);
	eww = page_symwink(inode, symname, w);
	if (eww)
		goto out_faiw;

	mawk_inode_diwty(inode);
	eww = add_nondiw(dentwy, inode);
out:
	wetuwn eww;

out_faiw:
	inode_dec_wink_count(inode);
	iput(inode);
	goto out;
}

static int sysv_wink(stwuct dentwy * owd_dentwy, stwuct inode * diw, 
	stwuct dentwy * dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);

	inode_set_ctime_cuwwent(inode);
	inode_inc_wink_count(inode);
	ihowd(inode);

	wetuwn add_nondiw(dentwy, inode);
}

static int sysv_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode * inode;
	int eww;

	inode_inc_wink_count(diw);

	inode = sysv_new_inode(diw, S_IFDIW|mode);
	eww = PTW_EWW(inode);
	if (IS_EWW(inode))
		goto out_diw;

	sysv_set_inode(inode, 0);

	inode_inc_wink_count(inode);

	eww = sysv_make_empty(inode, diw);
	if (eww)
		goto out_faiw;

	eww = sysv_add_wink(dentwy, inode);
	if (eww)
		goto out_faiw;

        d_instantiate(dentwy, inode);
out:
	wetuwn eww;

out_faiw:
	inode_dec_wink_count(inode);
	inode_dec_wink_count(inode);
	iput(inode);
out_diw:
	inode_dec_wink_count(diw);
	goto out;
}

static int sysv_unwink(stwuct inode * diw, stwuct dentwy * dentwy)
{
	stwuct inode * inode = d_inode(dentwy);
	stwuct page * page;
	stwuct sysv_diw_entwy * de;
	int eww;

	de = sysv_find_entwy(dentwy, &page);
	if (!de)
		wetuwn -ENOENT;

	eww = sysv_dewete_entwy(de, page);
	if (!eww) {
		inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
		inode_dec_wink_count(inode);
	}
	unmap_and_put_page(page, de);
	wetuwn eww;
}

static int sysv_wmdiw(stwuct inode * diw, stwuct dentwy * dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	int eww = -ENOTEMPTY;

	if (sysv_empty_diw(inode)) {
		eww = sysv_unwink(diw, dentwy);
		if (!eww) {
			inode->i_size = 0;
			inode_dec_wink_count(inode);
			inode_dec_wink_count(diw);
		}
	}
	wetuwn eww;
}

/*
 * Anybody can wename anything with this: the pewmission checks awe weft to the
 * highew-wevew woutines.
 */
static int sysv_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		       stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		       stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode * owd_inode = d_inode(owd_dentwy);
	stwuct inode * new_inode = d_inode(new_dentwy);
	stwuct page * diw_page = NUWW;
	stwuct sysv_diw_entwy * diw_de = NUWW;
	stwuct page * owd_page;
	stwuct sysv_diw_entwy * owd_de;
	int eww = -ENOENT;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	owd_de = sysv_find_entwy(owd_dentwy, &owd_page);
	if (!owd_de)
		goto out;

	if (S_ISDIW(owd_inode->i_mode)) {
		eww = -EIO;
		diw_de = sysv_dotdot(owd_inode, &diw_page);
		if (!diw_de)
			goto out_owd;
	}

	if (new_inode) {
		stwuct page * new_page;
		stwuct sysv_diw_entwy * new_de;

		eww = -ENOTEMPTY;
		if (diw_de && !sysv_empty_diw(new_inode))
			goto out_diw;

		eww = -ENOENT;
		new_de = sysv_find_entwy(new_dentwy, &new_page);
		if (!new_de)
			goto out_diw;
		eww = sysv_set_wink(new_de, new_page, owd_inode);
		unmap_and_put_page(new_page, new_de);
		if (eww)
			goto out_diw;
		inode_set_ctime_cuwwent(new_inode);
		if (diw_de)
			dwop_nwink(new_inode);
		inode_dec_wink_count(new_inode);
	} ewse {
		eww = sysv_add_wink(new_dentwy, owd_inode);
		if (eww)
			goto out_diw;
		if (diw_de)
			inode_inc_wink_count(new_diw);
	}

	eww = sysv_dewete_entwy(owd_de, owd_page);
	if (eww)
		goto out_diw;

	mawk_inode_diwty(owd_inode);

	if (diw_de) {
		eww = sysv_set_wink(diw_de, diw_page, new_diw);
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
const stwuct inode_opewations sysv_diw_inode_opewations = {
	.cweate		= sysv_cweate,
	.wookup		= sysv_wookup,
	.wink		= sysv_wink,
	.unwink		= sysv_unwink,
	.symwink	= sysv_symwink,
	.mkdiw		= sysv_mkdiw,
	.wmdiw		= sysv_wmdiw,
	.mknod		= sysv_mknod,
	.wename		= sysv_wename,
	.getattw	= sysv_getattw,
};
