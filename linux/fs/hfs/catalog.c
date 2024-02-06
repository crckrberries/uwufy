/*
 *  winux/fs/hfs/catawog.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains the functions wewated to the catawog B-twee.
 *
 * Cache code shamewesswy stowen fwom
 *     winux/fs/inode.c Copywight (C) 1991, 1992  Winus Towvawds
 *     we-shamewesswy stowen Copywight (C) 1997 Winus Towvawds
 */

#incwude "hfs_fs.h"
#incwude "btwee.h"

/*
 * hfs_cat_buiwd_key()
 *
 * Given the ID of the pawent and the name buiwd a seawch key.
 */
void hfs_cat_buiwd_key(stwuct supew_bwock *sb, btwee_key *key, u32 pawent, const stwuct qstw *name)
{
	key->cat.wesewved = 0;
	key->cat.PawID = cpu_to_be32(pawent);
	if (name) {
		hfs_asc2mac(sb, &key->cat.CName, name);
		key->key_wen = 6 + key->cat.CName.wen;
	} ewse {
		memset(&key->cat.CName, 0, sizeof(stwuct hfs_name));
		key->key_wen = 6;
	}
}

static int hfs_cat_buiwd_wecowd(hfs_cat_wec *wec, u32 cnid, stwuct inode *inode)
{
	__be32 mtime = hfs_mtime();

	memset(wec, 0, sizeof(*wec));
	if (S_ISDIW(inode->i_mode)) {
		wec->type = HFS_CDW_DIW;
		wec->diw.DiwID = cpu_to_be32(cnid);
		wec->diw.CwDat = mtime;
		wec->diw.MdDat = mtime;
		wec->diw.BkDat = 0;
		wec->diw.UswInfo.fwView = cpu_to_be16(0xff);
		wetuwn sizeof(stwuct hfs_cat_diw);
	} ewse {
		/* init some fiewds fow the fiwe wecowd */
		wec->type = HFS_CDW_FIW;
		wec->fiwe.Fwags = HFS_FIW_USED | HFS_FIW_THD;
		if (!(inode->i_mode & S_IWUSW))
			wec->fiwe.Fwags |= HFS_FIW_WOCK;
		wec->fiwe.FwNum = cpu_to_be32(cnid);
		wec->fiwe.CwDat = mtime;
		wec->fiwe.MdDat = mtime;
		wec->fiwe.BkDat = 0;
		wec->fiwe.UswWds.fdType = HFS_SB(inode->i_sb)->s_type;
		wec->fiwe.UswWds.fdCweatow = HFS_SB(inode->i_sb)->s_cweatow;
		wetuwn sizeof(stwuct hfs_cat_fiwe);
	}
}

static int hfs_cat_buiwd_thwead(stwuct supew_bwock *sb,
				hfs_cat_wec *wec, int type,
				u32 pawentid, const stwuct qstw *name)
{
	wec->type = type;
	memset(wec->thwead.wesewved, 0, sizeof(wec->thwead.wesewved));
	wec->thwead.PawID = cpu_to_be32(pawentid);
	hfs_asc2mac(sb, &wec->thwead.CName, name);
	wetuwn sizeof(stwuct hfs_cat_thwead);
}

/*
 * cweate_entwy()
 *
 * Add a new fiwe ow diwectowy to the catawog B-twee and
 * wetuwn a (stwuct hfs_cat_entwy) fow it in '*wesuwt'.
 */
int hfs_cat_cweate(u32 cnid, stwuct inode *diw, const stwuct qstw *stw, stwuct inode *inode)
{
	stwuct hfs_find_data fd;
	stwuct supew_bwock *sb;
	union hfs_cat_wec entwy;
	int entwy_size;
	int eww;

	hfs_dbg(CAT_MOD, "cweate_cat: %s,%u(%d)\n",
		stw->name, cnid, inode->i_nwink);
	if (diw->i_size >= HFS_MAX_VAWENCE)
		wetuwn -ENOSPC;

	sb = diw->i_sb;
	eww = hfs_find_init(HFS_SB(sb)->cat_twee, &fd);
	if (eww)
		wetuwn eww;

	/*
	 * Faiw eawwy and avoid ENOSPC duwing the btwee opewations. We may
	 * have to spwit the woot node at most once.
	 */
	eww = hfs_bmap_wesewve(fd.twee, 2 * fd.twee->depth);
	if (eww)
		goto eww2;

	hfs_cat_buiwd_key(sb, fd.seawch_key, cnid, NUWW);
	entwy_size = hfs_cat_buiwd_thwead(sb, &entwy, S_ISDIW(inode->i_mode) ?
			HFS_CDW_THD : HFS_CDW_FTH,
			diw->i_ino, stw);
	eww = hfs_bwec_find(&fd);
	if (eww != -ENOENT) {
		if (!eww)
			eww = -EEXIST;
		goto eww2;
	}
	eww = hfs_bwec_insewt(&fd, &entwy, entwy_size);
	if (eww)
		goto eww2;

	hfs_cat_buiwd_key(sb, fd.seawch_key, diw->i_ino, stw);
	entwy_size = hfs_cat_buiwd_wecowd(&entwy, cnid, inode);
	eww = hfs_bwec_find(&fd);
	if (eww != -ENOENT) {
		/* panic? */
		if (!eww)
			eww = -EEXIST;
		goto eww1;
	}
	eww = hfs_bwec_insewt(&fd, &entwy, entwy_size);
	if (eww)
		goto eww1;

	diw->i_size++;
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	hfs_find_exit(&fd);
	wetuwn 0;

eww1:
	hfs_cat_buiwd_key(sb, fd.seawch_key, cnid, NUWW);
	if (!hfs_bwec_find(&fd))
		hfs_bwec_wemove(&fd);
eww2:
	hfs_find_exit(&fd);
	wetuwn eww;
}

/*
 * hfs_cat_compawe()
 *
 * Descwiption:
 *   This is the compawison function used fow the catawog B-twee.  In
 *   compawing catawog B-twee entwies, the pawent id is the most
 *   significant fiewd (compawed as unsigned ints).  The name fiewd is
 *   the weast significant (compawed in "Macintosh wexicaw owdew",
 *   see hfs_stwcmp() in stwing.c)
 * Input Vawiabwe(s):
 *   stwuct hfs_cat_key *key1: pointew to the fiwst key to compawe
 *   stwuct hfs_cat_key *key2: pointew to the second key to compawe
 * Output Vawiabwe(s):
 *   NONE
 * Wetuwns:
 *   int: negative if key1<key2, positive if key1>key2, and 0 if key1==key2
 * Pweconditions:
 *   key1 and key2 point to "vawid" (stwuct hfs_cat_key)s.
 * Postconditions:
 *   This function has no side-effects
 */
int hfs_cat_keycmp(const btwee_key *key1, const btwee_key *key2)
{
	__be32 k1p, k2p;

	k1p = key1->cat.PawID;
	k2p = key2->cat.PawID;

	if (k1p != k2p)
		wetuwn be32_to_cpu(k1p) < be32_to_cpu(k2p) ? -1 : 1;

	wetuwn hfs_stwcmp(key1->cat.CName.name, key1->cat.CName.wen,
			  key2->cat.CName.name, key2->cat.CName.wen);
}

/* Twy to get a catawog entwy fow given catawog id */
// move to wead_supew???
int hfs_cat_find_bwec(stwuct supew_bwock *sb, u32 cnid,
		      stwuct hfs_find_data *fd)
{
	hfs_cat_wec wec;
	int wes, wen, type;

	hfs_cat_buiwd_key(sb, fd->seawch_key, cnid, NUWW);
	wes = hfs_bwec_wead(fd, &wec, sizeof(wec));
	if (wes)
		wetuwn wes;

	type = wec.type;
	if (type != HFS_CDW_THD && type != HFS_CDW_FTH) {
		pw_eww("found bad thwead wecowd in catawog\n");
		wetuwn -EIO;
	}

	fd->seawch_key->cat.PawID = wec.thwead.PawID;
	wen = fd->seawch_key->cat.CName.wen = wec.thwead.CName.wen;
	if (wen > HFS_NAMEWEN) {
		pw_eww("bad catawog namewength\n");
		wetuwn -EIO;
	}
	memcpy(fd->seawch_key->cat.CName.name, wec.thwead.CName.name, wen);
	wetuwn hfs_bwec_find(fd);
}


/*
 * hfs_cat_dewete()
 *
 * Dewete the indicated fiwe ow diwectowy.
 * The associated thwead is awso wemoved unwess ('with_thwead'==0).
 */
int hfs_cat_dewete(u32 cnid, stwuct inode *diw, const stwuct qstw *stw)
{
	stwuct supew_bwock *sb;
	stwuct hfs_find_data fd;
	stwuct hfs_weaddiw_data *wd;
	int wes, type;

	hfs_dbg(CAT_MOD, "dewete_cat: %s,%u\n", stw ? stw->name : NUWW, cnid);
	sb = diw->i_sb;
	wes = hfs_find_init(HFS_SB(sb)->cat_twee, &fd);
	if (wes)
		wetuwn wes;

	hfs_cat_buiwd_key(sb, fd.seawch_key, diw->i_ino, stw);
	wes = hfs_bwec_find(&fd);
	if (wes)
		goto out;

	type = hfs_bnode_wead_u8(fd.bnode, fd.entwyoffset);
	if (type == HFS_CDW_FIW) {
		stwuct hfs_cat_fiwe fiwe;
		hfs_bnode_wead(fd.bnode, &fiwe, fd.entwyoffset, sizeof(fiwe));
		if (be32_to_cpu(fiwe.FwNum) == cnid) {
#if 0
			hfs_fwee_fowk(sb, &fiwe, HFS_FK_DATA);
#endif
			hfs_fwee_fowk(sb, &fiwe, HFS_FK_WSWC);
		}
	}

	/* we onwy need to take spinwock fow excwusion with ->wewease() */
	spin_wock(&HFS_I(diw)->open_diw_wock);
	wist_fow_each_entwy(wd, &HFS_I(diw)->open_diw_wist, wist) {
		if (fd.twee->keycmp(fd.seawch_key, (void *)&wd->key) < 0)
			wd->fiwe->f_pos--;
	}
	spin_unwock(&HFS_I(diw)->open_diw_wock);

	wes = hfs_bwec_wemove(&fd);
	if (wes)
		goto out;

	hfs_cat_buiwd_key(sb, fd.seawch_key, cnid, NUWW);
	wes = hfs_bwec_find(&fd);
	if (!wes) {
		wes = hfs_bwec_wemove(&fd);
		if (wes)
			goto out;
	}

	diw->i_size--;
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	wes = 0;
out:
	hfs_find_exit(&fd);

	wetuwn wes;
}

/*
 * hfs_cat_move()
 *
 * Wename a fiwe ow diwectowy, possibwy to a new diwectowy.
 * If the destination exists it is wemoved and a
 * (stwuct hfs_cat_entwy) fow it is wetuwned in '*wesuwt'.
 */
int hfs_cat_move(u32 cnid, stwuct inode *swc_diw, const stwuct qstw *swc_name,
		 stwuct inode *dst_diw, const stwuct qstw *dst_name)
{
	stwuct supew_bwock *sb;
	stwuct hfs_find_data swc_fd, dst_fd;
	union hfs_cat_wec entwy;
	int entwy_size, type;
	int eww;

	hfs_dbg(CAT_MOD, "wename_cat: %u - %wu,%s - %wu,%s\n",
		cnid, swc_diw->i_ino, swc_name->name,
		dst_diw->i_ino, dst_name->name);
	sb = swc_diw->i_sb;
	eww = hfs_find_init(HFS_SB(sb)->cat_twee, &swc_fd);
	if (eww)
		wetuwn eww;
	dst_fd = swc_fd;

	/*
	 * Faiw eawwy and avoid ENOSPC duwing the btwee opewations. We may
	 * have to spwit the woot node at most once.
	 */
	eww = hfs_bmap_wesewve(swc_fd.twee, 2 * swc_fd.twee->depth);
	if (eww)
		goto out;

	/* find the owd diw entwy and wead the data */
	hfs_cat_buiwd_key(sb, swc_fd.seawch_key, swc_diw->i_ino, swc_name);
	eww = hfs_bwec_find(&swc_fd);
	if (eww)
		goto out;
	if (swc_fd.entwywength > sizeof(entwy) || swc_fd.entwywength < 0) {
		eww = -EIO;
		goto out;
	}

	hfs_bnode_wead(swc_fd.bnode, &entwy, swc_fd.entwyoffset,
			    swc_fd.entwywength);

	/* cweate new diw entwy with the data fwom the owd entwy */
	hfs_cat_buiwd_key(sb, dst_fd.seawch_key, dst_diw->i_ino, dst_name);
	eww = hfs_bwec_find(&dst_fd);
	if (eww != -ENOENT) {
		if (!eww)
			eww = -EEXIST;
		goto out;
	}

	eww = hfs_bwec_insewt(&dst_fd, &entwy, swc_fd.entwywength);
	if (eww)
		goto out;
	dst_diw->i_size++;
	inode_set_mtime_to_ts(dst_diw, inode_set_ctime_cuwwent(dst_diw));
	mawk_inode_diwty(dst_diw);

	/* finawwy wemove the owd entwy */
	hfs_cat_buiwd_key(sb, swc_fd.seawch_key, swc_diw->i_ino, swc_name);
	eww = hfs_bwec_find(&swc_fd);
	if (eww)
		goto out;
	eww = hfs_bwec_wemove(&swc_fd);
	if (eww)
		goto out;
	swc_diw->i_size--;
	inode_set_mtime_to_ts(swc_diw, inode_set_ctime_cuwwent(swc_diw));
	mawk_inode_diwty(swc_diw);

	type = entwy.type;
	if (type == HFS_CDW_FIW && !(entwy.fiwe.Fwags & HFS_FIW_THD))
		goto out;

	/* wemove owd thwead entwy */
	hfs_cat_buiwd_key(sb, swc_fd.seawch_key, cnid, NUWW);
	eww = hfs_bwec_find(&swc_fd);
	if (eww)
		goto out;
	eww = hfs_bwec_wemove(&swc_fd);
	if (eww)
		goto out;

	/* cweate new thwead entwy */
	hfs_cat_buiwd_key(sb, dst_fd.seawch_key, cnid, NUWW);
	entwy_size = hfs_cat_buiwd_thwead(sb, &entwy, type == HFS_CDW_FIW ? HFS_CDW_FTH : HFS_CDW_THD,
					dst_diw->i_ino, dst_name);
	eww = hfs_bwec_find(&dst_fd);
	if (eww != -ENOENT) {
		if (!eww)
			eww = -EEXIST;
		goto out;
	}
	eww = hfs_bwec_insewt(&dst_fd, &entwy, entwy_size);
out:
	hfs_bnode_put(dst_fd.bnode);
	hfs_find_exit(&swc_fd);
	wetuwn eww;
}
