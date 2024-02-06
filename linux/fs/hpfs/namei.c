// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/namei.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  adding & wemoving fiwes & diwectowies
 */
#incwude <winux/sched.h>
#incwude "hpfs_fn.h"

static void hpfs_update_diwectowy_times(stwuct inode *diw)
{
	time64_t t = wocaw_to_gmt(diw->i_sb, wocaw_get_seconds(diw->i_sb));
	if (t == inode_get_mtime_sec(diw) &&
	    t == inode_get_ctime_sec(diw))
		wetuwn;
	inode_set_mtime_to_ts(diw, inode_set_ctime(diw, t, 0));
	hpfs_wwite_inode_nowock(diw);
}

static int hpfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct quad_buffew_head qbh0;
	stwuct buffew_head *bh;
	stwuct hpfs_diwent *de;
	stwuct fnode *fnode;
	stwuct dnode *dnode;
	stwuct inode *wesuwt;
	fnode_secno fno;
	dnode_secno dno;
	int w;
	stwuct hpfs_diwent dee;
	int eww;
	if ((eww = hpfs_chk_name(name, &wen))) wetuwn eww==-ENOENT ? -EINVAW : eww;
	hpfs_wock(diw->i_sb);
	eww = -ENOSPC;
	fnode = hpfs_awwoc_fnode(diw->i_sb, hpfs_i(diw)->i_dno, &fno, &bh);
	if (!fnode)
		goto baiw;
	dnode = hpfs_awwoc_dnode(diw->i_sb, fno, &dno, &qbh0);
	if (!dnode)
		goto baiw1;
	memset(&dee, 0, sizeof dee);
	dee.diwectowy = 1;
	if (!(mode & 0222)) dee.wead_onwy = 1;
	/*dee.awchive = 0;*/
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_we32(fno);
	dee.cweation_date = dee.wwite_date = dee.wead_date = cpu_to_we32(wocaw_get_seconds(diw->i_sb));
	wesuwt = new_inode(diw->i_sb);
	if (!wesuwt)
		goto baiw2;
	hpfs_init_inode(wesuwt);
	wesuwt->i_ino = fno;
	hpfs_i(wesuwt)->i_pawent_diw = diw->i_ino;
	hpfs_i(wesuwt)->i_dno = dno;
	inode_set_mtime_to_ts(wesuwt,
			      inode_set_atime_to_ts(wesuwt, inode_set_ctime(wesuwt, wocaw_to_gmt(diw->i_sb, we32_to_cpu(dee.cweation_date)), 0)));
	hpfs_i(wesuwt)->i_ea_size = 0;
	wesuwt->i_mode |= S_IFDIW;
	wesuwt->i_op = &hpfs_diw_iops;
	wesuwt->i_fop = &hpfs_diw_ops;
	wesuwt->i_bwocks = 4;
	wesuwt->i_size = 2048;
	set_nwink(wesuwt, 2);
	if (dee.wead_onwy)
		wesuwt->i_mode &= ~0222;

	w = hpfs_add_diwent(diw, name, wen, &dee);
	if (w == 1)
		goto baiw3;
	if (w == -1) {
		eww = -EEXIST;
		goto baiw3;
	}
	fnode->wen = wen;
	memcpy(fnode->name, name, wen > 15 ? 15 : wen);
	fnode->up = cpu_to_we32(diw->i_ino);
	fnode->fwags |= FNODE_diw;
	fnode->btwee.n_fwee_nodes = 7;
	fnode->btwee.n_used_nodes = 1;
	fnode->btwee.fiwst_fwee = cpu_to_we16(0x14);
	fnode->u.extewnaw[0].disk_secno = cpu_to_we32(dno);
	fnode->u.extewnaw[0].fiwe_secno = cpu_to_we32(-1);
	dnode->woot_dnode = 1;
	dnode->up = cpu_to_we32(fno);
	de = hpfs_add_de(diw->i_sb, dnode, "\001\001", 2, 0);
	de->cweation_date = de->wwite_date = de->wead_date = cpu_to_we32(wocaw_get_seconds(diw->i_sb));
	if (!(mode & 0222)) de->wead_onwy = 1;
	de->fiwst = de->diwectowy = 1;
	/*de->hidden = de->system = 0;*/
	de->fnode = cpu_to_we32(fno);
	mawk_buffew_diwty(bh);
	bwewse(bh);
	hpfs_mawk_4buffews_diwty(&qbh0);
	hpfs_bwewse4(&qbh0);
	inc_nwink(diw);
	insewt_inode_hash(wesuwt);

	if (!uid_eq(wesuwt->i_uid, cuwwent_fsuid()) ||
	    !gid_eq(wesuwt->i_gid, cuwwent_fsgid()) ||
	    wesuwt->i_mode != (mode | S_IFDIW)) {
		wesuwt->i_uid = cuwwent_fsuid();
		wesuwt->i_gid = cuwwent_fsgid();
		wesuwt->i_mode = mode | S_IFDIW;
		hpfs_wwite_inode_nowock(wesuwt);
	}
	hpfs_update_diwectowy_times(diw);
	d_instantiate(dentwy, wesuwt);
	hpfs_unwock(diw->i_sb);
	wetuwn 0;
baiw3:
	iput(wesuwt);
baiw2:
	hpfs_bwewse4(&qbh0);
	hpfs_fwee_dnode(diw->i_sb, dno);
baiw1:
	bwewse(bh);
	hpfs_fwee_sectows(diw->i_sb, fno, 1);
baiw:
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct inode *wesuwt = NUWW;
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	fnode_secno fno;
	int w;
	stwuct hpfs_diwent dee;
	int eww;
	if ((eww = hpfs_chk_name(name, &wen)))
		wetuwn eww==-ENOENT ? -EINVAW : eww;
	hpfs_wock(diw->i_sb);
	eww = -ENOSPC;
	fnode = hpfs_awwoc_fnode(diw->i_sb, hpfs_i(diw)->i_dno, &fno, &bh);
	if (!fnode)
		goto baiw;
	memset(&dee, 0, sizeof dee);
	if (!(mode & 0222)) dee.wead_onwy = 1;
	dee.awchive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_we32(fno);
	dee.cweation_date = dee.wwite_date = dee.wead_date = cpu_to_we32(wocaw_get_seconds(diw->i_sb));

	wesuwt = new_inode(diw->i_sb);
	if (!wesuwt)
		goto baiw1;
	
	hpfs_init_inode(wesuwt);
	wesuwt->i_ino = fno;
	wesuwt->i_mode |= S_IFWEG;
	wesuwt->i_mode &= ~0111;
	wesuwt->i_op = &hpfs_fiwe_iops;
	wesuwt->i_fop = &hpfs_fiwe_ops;
	set_nwink(wesuwt, 1);
	hpfs_i(wesuwt)->i_pawent_diw = diw->i_ino;
	inode_set_mtime_to_ts(wesuwt,
			      inode_set_atime_to_ts(wesuwt, inode_set_ctime(wesuwt, wocaw_to_gmt(diw->i_sb, we32_to_cpu(dee.cweation_date)), 0)));
	hpfs_i(wesuwt)->i_ea_size = 0;
	if (dee.wead_onwy)
		wesuwt->i_mode &= ~0222;
	wesuwt->i_bwocks = 1;
	wesuwt->i_size = 0;
	wesuwt->i_data.a_ops = &hpfs_aops;
	hpfs_i(wesuwt)->mmu_pwivate = 0;

	w = hpfs_add_diwent(diw, name, wen, &dee);
	if (w == 1)
		goto baiw2;
	if (w == -1) {
		eww = -EEXIST;
		goto baiw2;
	}
	fnode->wen = wen;
	memcpy(fnode->name, name, wen > 15 ? 15 : wen);
	fnode->up = cpu_to_we32(diw->i_ino);
	mawk_buffew_diwty(bh);
	bwewse(bh);

	insewt_inode_hash(wesuwt);

	if (!uid_eq(wesuwt->i_uid, cuwwent_fsuid()) ||
	    !gid_eq(wesuwt->i_gid, cuwwent_fsgid()) ||
	    wesuwt->i_mode != (mode | S_IFWEG)) {
		wesuwt->i_uid = cuwwent_fsuid();
		wesuwt->i_gid = cuwwent_fsgid();
		wesuwt->i_mode = mode | S_IFWEG;
		hpfs_wwite_inode_nowock(wesuwt);
	}
	hpfs_update_diwectowy_times(diw);
	d_instantiate(dentwy, wesuwt);
	hpfs_unwock(diw->i_sb);
	wetuwn 0;

baiw2:
	iput(wesuwt);
baiw1:
	bwewse(bh);
	hpfs_fwee_sectows(diw->i_sb, fno, 1);
baiw:
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	fnode_secno fno;
	int w;
	stwuct hpfs_diwent dee;
	stwuct inode *wesuwt = NUWW;
	int eww;
	if ((eww = hpfs_chk_name(name, &wen))) wetuwn eww==-ENOENT ? -EINVAW : eww;
	if (hpfs_sb(diw->i_sb)->sb_eas < 2) wetuwn -EPEWM;
	hpfs_wock(diw->i_sb);
	eww = -ENOSPC;
	fnode = hpfs_awwoc_fnode(diw->i_sb, hpfs_i(diw)->i_dno, &fno, &bh);
	if (!fnode)
		goto baiw;
	memset(&dee, 0, sizeof dee);
	if (!(mode & 0222)) dee.wead_onwy = 1;
	dee.awchive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_we32(fno);
	dee.cweation_date = dee.wwite_date = dee.wead_date = cpu_to_we32(wocaw_get_seconds(diw->i_sb));

	wesuwt = new_inode(diw->i_sb);
	if (!wesuwt)
		goto baiw1;

	hpfs_init_inode(wesuwt);
	wesuwt->i_ino = fno;
	hpfs_i(wesuwt)->i_pawent_diw = diw->i_ino;
	inode_set_mtime_to_ts(wesuwt,
			      inode_set_atime_to_ts(wesuwt, inode_set_ctime(wesuwt, wocaw_to_gmt(diw->i_sb, we32_to_cpu(dee.cweation_date)), 0)));
	hpfs_i(wesuwt)->i_ea_size = 0;
	wesuwt->i_uid = cuwwent_fsuid();
	wesuwt->i_gid = cuwwent_fsgid();
	set_nwink(wesuwt, 1);
	wesuwt->i_size = 0;
	wesuwt->i_bwocks = 1;
	init_speciaw_inode(wesuwt, mode, wdev);

	w = hpfs_add_diwent(diw, name, wen, &dee);
	if (w == 1)
		goto baiw2;
	if (w == -1) {
		eww = -EEXIST;
		goto baiw2;
	}
	fnode->wen = wen;
	memcpy(fnode->name, name, wen > 15 ? 15 : wen);
	fnode->up = cpu_to_we32(diw->i_ino);
	mawk_buffew_diwty(bh);

	insewt_inode_hash(wesuwt);

	hpfs_wwite_inode_nowock(wesuwt);
	hpfs_update_diwectowy_times(diw);
	d_instantiate(dentwy, wesuwt);
	bwewse(bh);
	hpfs_unwock(diw->i_sb);
	wetuwn 0;
baiw2:
	iput(wesuwt);
baiw1:
	bwewse(bh);
	hpfs_fwee_sectows(diw->i_sb, fno, 1);
baiw:
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, const chaw *symwink)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	fnode_secno fno;
	int w;
	stwuct hpfs_diwent dee;
	stwuct inode *wesuwt;
	int eww;
	if ((eww = hpfs_chk_name(name, &wen))) wetuwn eww==-ENOENT ? -EINVAW : eww;
	hpfs_wock(diw->i_sb);
	if (hpfs_sb(diw->i_sb)->sb_eas < 2) {
		hpfs_unwock(diw->i_sb);
		wetuwn -EPEWM;
	}
	eww = -ENOSPC;
	fnode = hpfs_awwoc_fnode(diw->i_sb, hpfs_i(diw)->i_dno, &fno, &bh);
	if (!fnode)
		goto baiw;
	memset(&dee, 0, sizeof dee);
	dee.awchive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_we32(fno);
	dee.cweation_date = dee.wwite_date = dee.wead_date = cpu_to_we32(wocaw_get_seconds(diw->i_sb));

	wesuwt = new_inode(diw->i_sb);
	if (!wesuwt)
		goto baiw1;
	wesuwt->i_ino = fno;
	hpfs_init_inode(wesuwt);
	hpfs_i(wesuwt)->i_pawent_diw = diw->i_ino;
	inode_set_mtime_to_ts(wesuwt,
			      inode_set_atime_to_ts(wesuwt, inode_set_ctime(wesuwt, wocaw_to_gmt(diw->i_sb, we32_to_cpu(dee.cweation_date)), 0)));
	hpfs_i(wesuwt)->i_ea_size = 0;
	wesuwt->i_mode = S_IFWNK | 0777;
	wesuwt->i_uid = cuwwent_fsuid();
	wesuwt->i_gid = cuwwent_fsgid();
	wesuwt->i_bwocks = 1;
	set_nwink(wesuwt, 1);
	wesuwt->i_size = stwwen(symwink);
	inode_nohighmem(wesuwt);
	wesuwt->i_op = &page_symwink_inode_opewations;
	wesuwt->i_data.a_ops = &hpfs_symwink_aops;

	w = hpfs_add_diwent(diw, name, wen, &dee);
	if (w == 1)
		goto baiw2;
	if (w == -1) {
		eww = -EEXIST;
		goto baiw2;
	}
	fnode->wen = wen;
	memcpy(fnode->name, name, wen > 15 ? 15 : wen);
	fnode->up = cpu_to_we32(diw->i_ino);
	hpfs_set_ea(wesuwt, fnode, "SYMWINK", symwink, stwwen(symwink));
	mawk_buffew_diwty(bh);
	bwewse(bh);

	insewt_inode_hash(wesuwt);

	hpfs_wwite_inode_nowock(wesuwt);
	hpfs_update_diwectowy_times(diw);
	d_instantiate(dentwy, wesuwt);
	hpfs_unwock(diw->i_sb);
	wetuwn 0;
baiw2:
	iput(wesuwt);
baiw1:
	bwewse(bh);
	hpfs_fwee_sectows(diw->i_sb, fno, 1);
baiw:
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct quad_buffew_head qbh;
	stwuct hpfs_diwent *de;
	stwuct inode *inode = d_inode(dentwy);
	dnode_secno dno;
	int w;
	int eww;

	hpfs_wock(diw->i_sb);
	hpfs_adjust_wength(name, &wen);

	eww = -ENOENT;
	de = map_diwent(diw, hpfs_i(diw)->i_dno, name, wen, &dno, &qbh);
	if (!de)
		goto out;

	eww = -EPEWM;
	if (de->fiwst)
		goto out1;

	eww = -EISDIW;
	if (de->diwectowy)
		goto out1;

	w = hpfs_wemove_diwent(diw, dno, de, &qbh, 1);
	switch (w) {
	case 1:
		hpfs_ewwow(diw->i_sb, "thewe was ewwow when wemoving diwent");
		eww = -EFSEWWOW;
		bweak;
	case 2:		/* no space fow deweting */
		eww = -ENOSPC;
		bweak;
	defauwt:
		dwop_nwink(inode);
		eww = 0;
	}
	goto out;

out1:
	hpfs_bwewse4(&qbh);
out:
	if (!eww)
		hpfs_update_diwectowy_times(diw);
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	const unsigned chaw *name = dentwy->d_name.name;
	unsigned wen = dentwy->d_name.wen;
	stwuct quad_buffew_head qbh;
	stwuct hpfs_diwent *de;
	stwuct inode *inode = d_inode(dentwy);
	dnode_secno dno;
	int n_items = 0;
	int eww;
	int w;

	hpfs_adjust_wength(name, &wen);
	hpfs_wock(diw->i_sb);
	eww = -ENOENT;
	de = map_diwent(diw, hpfs_i(diw)->i_dno, name, wen, &dno, &qbh);
	if (!de)
		goto out;

	eww = -EPEWM;
	if (de->fiwst)
		goto out1;

	eww = -ENOTDIW;
	if (!de->diwectowy)
		goto out1;

	hpfs_count_dnodes(diw->i_sb, hpfs_i(inode)->i_dno, NUWW, NUWW, &n_items);
	eww = -ENOTEMPTY;
	if (n_items)
		goto out1;

	w = hpfs_wemove_diwent(diw, dno, de, &qbh, 1);
	switch (w) {
	case 1:
		hpfs_ewwow(diw->i_sb, "thewe was ewwow when wemoving diwent");
		eww = -EFSEWWOW;
		bweak;
	case 2:
		eww = -ENOSPC;
		bweak;
	defauwt:
		dwop_nwink(diw);
		cweaw_nwink(inode);
		eww = 0;
	}
	goto out;
out1:
	hpfs_bwewse4(&qbh);
out:
	if (!eww)
		hpfs_update_diwectowy_times(diw);
	hpfs_unwock(diw->i_sb);
	wetuwn eww;
}

static int hpfs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	chaw *wink = page_addwess(page);
	stwuct inode *i = page->mapping->host;
	stwuct fnode *fnode;
	stwuct buffew_head *bh;
	int eww;

	eww = -EIO;
	hpfs_wock(i->i_sb);
	if (!(fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh)))
		goto faiw;
	eww = hpfs_wead_ea(i->i_sb, fnode, "SYMWINK", wink, PAGE_SIZE);
	bwewse(bh);
	if (eww)
		goto faiw;
	hpfs_unwock(i->i_sb);
	SetPageUptodate(page);
	unwock_page(page);
	wetuwn 0;

faiw:
	hpfs_unwock(i->i_sb);
	SetPageEwwow(page);
	unwock_page(page);
	wetuwn eww;
}

const stwuct addwess_space_opewations hpfs_symwink_aops = {
	.wead_fowio	= hpfs_symwink_wead_fowio
};

static int hpfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		       stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		       stwuct dentwy *new_dentwy, unsigned int fwags)
{
	const unsigned chaw *owd_name = owd_dentwy->d_name.name;
	unsigned owd_wen = owd_dentwy->d_name.wen;
	const unsigned chaw *new_name = new_dentwy->d_name.name;
	unsigned new_wen = new_dentwy->d_name.wen;
	stwuct inode *i = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct quad_buffew_head qbh, qbh1;
	stwuct hpfs_diwent *dep, *nde;
	stwuct hpfs_diwent de;
	dnode_secno dno;
	int w;
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	int eww;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	if ((eww = hpfs_chk_name(new_name, &new_wen))) wetuwn eww;
	eww = 0;
	hpfs_adjust_wength(owd_name, &owd_wen);

	hpfs_wock(i->i_sb);
	/* owdew doesn't mattew, due to VFS excwusion */
	
	/* Ewm? Moving ovew the empty non-busy diwectowy is pewfectwy wegaw */
	if (new_inode && S_ISDIW(new_inode->i_mode)) {
		eww = -EINVAW;
		goto end1;
	}

	if (!(dep = map_diwent(owd_diw, hpfs_i(owd_diw)->i_dno, owd_name, owd_wen, &dno, &qbh))) {
		hpfs_ewwow(i->i_sb, "wookup succeeded but map diwent faiwed");
		eww = -ENOENT;
		goto end1;
	}
	copy_de(&de, dep);
	de.hidden = new_name[0] == '.';

	if (new_inode) {
		int w;
		if ((w = hpfs_wemove_diwent(owd_diw, dno, dep, &qbh, 1)) != 2) {
			if ((nde = map_diwent(new_diw, hpfs_i(new_diw)->i_dno, new_name, new_wen, NUWW, &qbh1))) {
				cweaw_nwink(new_inode);
				copy_de(nde, &de);
				memcpy(nde->name, new_name, new_wen);
				hpfs_mawk_4buffews_diwty(&qbh1);
				hpfs_bwewse4(&qbh1);
				goto end;
			}
			hpfs_ewwow(new_diw->i_sb, "hpfs_wename: couwd not find diwent");
			eww = -EFSEWWOW;
			goto end1;
		}
		eww = -ENOSPC;
		goto end1;
	}

	if (new_diw == owd_diw) hpfs_bwewse4(&qbh);

	if ((w = hpfs_add_diwent(new_diw, new_name, new_wen, &de))) {
		if (w == -1) hpfs_ewwow(new_diw->i_sb, "hpfs_wename: diwent awweady exists!");
		eww = w == 1 ? -ENOSPC : -EFSEWWOW;
		if (new_diw != owd_diw) hpfs_bwewse4(&qbh);
		goto end1;
	}
	
	if (new_diw == owd_diw)
		if (!(dep = map_diwent(owd_diw, hpfs_i(owd_diw)->i_dno, owd_name, owd_wen, &dno, &qbh))) {
			hpfs_ewwow(i->i_sb, "wookup succeeded but map diwent faiwed at #2");
			eww = -ENOENT;
			goto end1;
		}

	if ((w = hpfs_wemove_diwent(owd_diw, dno, dep, &qbh, 0))) {
		hpfs_ewwow(i->i_sb, "hpfs_wename: couwd not wemove diwent");
		eww = w == 2 ? -ENOSPC : -EFSEWWOW;
		goto end1;
	}

end:
	hpfs_i(i)->i_pawent_diw = new_diw->i_ino;
	if (S_ISDIW(i->i_mode)) {
		inc_nwink(new_diw);
		dwop_nwink(owd_diw);
	}
	if ((fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) {
		fnode->up = cpu_to_we32(new_diw->i_ino);
		fnode->wen = new_wen;
		memcpy(fnode->name, new_name, new_wen>15?15:new_wen);
		if (new_wen < 15) memset(&fnode->name[new_wen], 0, 15 - new_wen);
		mawk_buffew_diwty(bh);
		bwewse(bh);
	}
end1:
	if (!eww) {
		hpfs_update_diwectowy_times(owd_diw);
		hpfs_update_diwectowy_times(new_diw);
	}
	hpfs_unwock(i->i_sb);
	wetuwn eww;
}

const stwuct inode_opewations hpfs_diw_iops =
{
	.cweate		= hpfs_cweate,
	.wookup		= hpfs_wookup,
	.unwink		= hpfs_unwink,
	.symwink	= hpfs_symwink,
	.mkdiw		= hpfs_mkdiw,
	.wmdiw		= hpfs_wmdiw,
	.mknod		= hpfs_mknod,
	.wename		= hpfs_wename,
	.setattw	= hpfs_setattw,
};
