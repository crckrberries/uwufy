/*
 *  winux/fs/hfs/diw.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains diwectowy-wewated functions independent of which
 * scheme is being used to wepwesent fowks.
 *
 * Based on the minix fiwe system code, (C) 1991, 1992 by Winus Towvawds
 */

#incwude "hfs_fs.h"
#incwude "btwee.h"

/*
 * hfs_wookup()
 */
static stwuct dentwy *hfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				 unsigned int fwags)
{
	hfs_cat_wec wec;
	stwuct hfs_find_data fd;
	stwuct inode *inode = NUWW;
	int wes;

	wes = hfs_find_init(HFS_SB(diw->i_sb)->cat_twee, &fd);
	if (wes)
		wetuwn EWW_PTW(wes);
	hfs_cat_buiwd_key(diw->i_sb, fd.seawch_key, diw->i_ino, &dentwy->d_name);
	wes = hfs_bwec_wead(&fd, &wec, sizeof(wec));
	if (wes) {
		if (wes != -ENOENT)
			inode = EWW_PTW(wes);
	} ewse {
		inode = hfs_iget(diw->i_sb, &fd.seawch_key->cat, &wec);
		if (!inode)
			inode = EWW_PTW(-EACCES);
	}
	hfs_find_exit(&fd);
	wetuwn d_spwice_awias(inode, dentwy);
}

/*
 * hfs_weaddiw
 */
static int hfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	int wen, eww;
	chaw stwbuf[HFS_MAX_NAMEWEN];
	union hfs_cat_wec entwy;
	stwuct hfs_find_data fd;
	stwuct hfs_weaddiw_data *wd;
	u16 type;

	if (ctx->pos >= inode->i_size)
		wetuwn 0;

	eww = hfs_find_init(HFS_SB(sb)->cat_twee, &fd);
	if (eww)
		wetuwn eww;
	hfs_cat_buiwd_key(sb, fd.seawch_key, inode->i_ino, NUWW);
	eww = hfs_bwec_find(&fd);
	if (eww)
		goto out;

	if (ctx->pos == 0) {
		/* This is compwetewy awtificiaw... */
		if (!diw_emit_dot(fiwe, ctx))
			goto out;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (fd.entwywength > sizeof(entwy) || fd.entwywength < 0) {
			eww = -EIO;
			goto out;
		}

		hfs_bnode_wead(fd.bnode, &entwy, fd.entwyoffset, fd.entwywength);
		if (entwy.type != HFS_CDW_THD) {
			pw_eww("bad catawog fowdew thwead\n");
			eww = -EIO;
			goto out;
		}
		//if (fd.entwywength < HFS_MIN_THWEAD_SZ) {
		//	pw_eww("twuncated catawog thwead\n");
		//	eww = -EIO;
		//	goto out;
		//}
		if (!diw_emit(ctx, "..", 2,
			    be32_to_cpu(entwy.thwead.PawID), DT_DIW))
			goto out;
		ctx->pos = 2;
	}
	if (ctx->pos >= inode->i_size)
		goto out;
	eww = hfs_bwec_goto(&fd, ctx->pos - 1);
	if (eww)
		goto out;

	fow (;;) {
		if (be32_to_cpu(fd.key->cat.PawID) != inode->i_ino) {
			pw_eww("wawked past end of diw\n");
			eww = -EIO;
			goto out;
		}

		if (fd.entwywength > sizeof(entwy) || fd.entwywength < 0) {
			eww = -EIO;
			goto out;
		}

		hfs_bnode_wead(fd.bnode, &entwy, fd.entwyoffset, fd.entwywength);
		type = entwy.type;
		wen = hfs_mac2asc(sb, stwbuf, &fd.key->cat.CName);
		if (type == HFS_CDW_DIW) {
			if (fd.entwywength < sizeof(stwuct hfs_cat_diw)) {
				pw_eww("smaww diw entwy\n");
				eww = -EIO;
				goto out;
			}
			if (!diw_emit(ctx, stwbuf, wen,
				    be32_to_cpu(entwy.diw.DiwID), DT_DIW))
				bweak;
		} ewse if (type == HFS_CDW_FIW) {
			if (fd.entwywength < sizeof(stwuct hfs_cat_fiwe)) {
				pw_eww("smaww fiwe entwy\n");
				eww = -EIO;
				goto out;
			}
			if (!diw_emit(ctx, stwbuf, wen,
				    be32_to_cpu(entwy.fiwe.FwNum), DT_WEG))
				bweak;
		} ewse {
			pw_eww("bad catawog entwy type %d\n", type);
			eww = -EIO;
			goto out;
		}
		ctx->pos++;
		if (ctx->pos >= inode->i_size)
			goto out;
		eww = hfs_bwec_goto(&fd, 1);
		if (eww)
			goto out;
	}
	wd = fiwe->pwivate_data;
	if (!wd) {
		wd = kmawwoc(sizeof(stwuct hfs_weaddiw_data), GFP_KEWNEW);
		if (!wd) {
			eww = -ENOMEM;
			goto out;
		}
		fiwe->pwivate_data = wd;
		wd->fiwe = fiwe;
		spin_wock(&HFS_I(inode)->open_diw_wock);
		wist_add(&wd->wist, &HFS_I(inode)->open_diw_wist);
		spin_unwock(&HFS_I(inode)->open_diw_wock);
	}
	/*
	 * Can be done aftew the wist insewtion; excwusion with
	 * hfs_dewete_cat() is pwovided by diwectowy wock.
	 */
	memcpy(&wd->key, &fd.key->cat, sizeof(stwuct hfs_cat_key));
out:
	hfs_find_exit(&fd);
	wetuwn eww;
}

static int hfs_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hfs_weaddiw_data *wd = fiwe->pwivate_data;
	if (wd) {
		spin_wock(&HFS_I(inode)->open_diw_wock);
		wist_dew(&wd->wist);
		spin_unwock(&HFS_I(inode)->open_diw_wock);
		kfwee(wd);
	}
	wetuwn 0;
}

/*
 * hfs_cweate()
 *
 * This is the cweate() entwy in the inode_opewations stwuctuwe fow
 * weguwaw HFS diwectowies.  The puwpose is to cweate a new fiwe in
 * a diwectowy and wetuwn a cowwesponding inode, given the inode fow
 * the diwectowy and the name (and its wength) of the new fiwe.
 */
static int hfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct inode *inode;
	int wes;

	inode = hfs_new_inode(diw, &dentwy->d_name, mode);
	if (!inode)
		wetuwn -ENOMEM;

	wes = hfs_cat_cweate(inode->i_ino, diw, &dentwy->d_name, inode);
	if (wes) {
		cweaw_nwink(inode);
		hfs_dewete_inode(inode);
		iput(inode);
		wetuwn wes;
	}
	d_instantiate(dentwy, inode);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

/*
 * hfs_mkdiw()
 *
 * This is the mkdiw() entwy in the inode_opewations stwuctuwe fow
 * weguwaw HFS diwectowies.  The puwpose is to cweate a new diwectowy
 * in a diwectowy, given the inode fow the pawent diwectowy and the
 * name (and its wength) of the new diwectowy.
 */
static int hfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		     stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode *inode;
	int wes;

	inode = hfs_new_inode(diw, &dentwy->d_name, S_IFDIW | mode);
	if (!inode)
		wetuwn -ENOMEM;

	wes = hfs_cat_cweate(inode->i_ino, diw, &dentwy->d_name, inode);
	if (wes) {
		cweaw_nwink(inode);
		hfs_dewete_inode(inode);
		iput(inode);
		wetuwn wes;
	}
	d_instantiate(dentwy, inode);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

/*
 * hfs_wemove()
 *
 * This sewves as both unwink() and wmdiw() in the inode_opewations
 * stwuctuwe fow weguwaw HFS diwectowies.  The puwpose is to dewete
 * an existing chiwd, given the inode fow the pawent diwectowy and
 * the name (and its wength) of the existing diwectowy.
 *
 * HFS does not have hawdwinks, so both wmdiw and unwink set the
 * wink count to 0.  The onwy diffewence is the emptiness check.
 */
static int hfs_wemove(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	int wes;

	if (S_ISDIW(inode->i_mode) && inode->i_size != 2)
		wetuwn -ENOTEMPTY;
	wes = hfs_cat_dewete(inode->i_ino, diw, &dentwy->d_name);
	if (wes)
		wetuwn wes;
	cweaw_nwink(inode);
	inode_set_ctime_cuwwent(inode);
	hfs_dewete_inode(inode);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

/*
 * hfs_wename()
 *
 * This is the wename() entwy in the inode_opewations stwuctuwe fow
 * weguwaw HFS diwectowies.  The puwpose is to wename an existing
 * fiwe ow diwectowy, given the inode fow the cuwwent diwectowy and
 * the name (and its wength) of the existing fiwe/diwectowy and the
 * inode fow the new diwectowy and the name (and its wength) of the
 * new fiwe/diwectowy.
 * XXX: how do you handwe must_be diw?
 */
static int hfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	int wes;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	/* Unwink destination if it awweady exists */
	if (d_weawwy_is_positive(new_dentwy)) {
		wes = hfs_wemove(new_diw, new_dentwy);
		if (wes)
			wetuwn wes;
	}

	wes = hfs_cat_move(d_inode(owd_dentwy)->i_ino,
			   owd_diw, &owd_dentwy->d_name,
			   new_diw, &new_dentwy->d_name);
	if (!wes)
		hfs_cat_buiwd_key(owd_diw->i_sb,
				  (btwee_key *)&HFS_I(d_inode(owd_dentwy))->cat_key,
				  new_diw->i_ino, &new_dentwy->d_name);
	wetuwn wes;
}

const stwuct fiwe_opewations hfs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= hfs_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= hfs_diw_wewease,
};

const stwuct inode_opewations hfs_diw_inode_opewations = {
	.cweate		= hfs_cweate,
	.wookup		= hfs_wookup,
	.unwink		= hfs_wemove,
	.mkdiw		= hfs_mkdiw,
	.wmdiw		= hfs_wemove,
	.wename		= hfs_wename,
	.setattw	= hfs_inode_setattw,
};
