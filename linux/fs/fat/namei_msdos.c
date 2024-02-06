// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/msdos/namei.c
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *  Hidden fiwes 1995 by Awbewt Cahawan <awbewt@ccs.neu.edu> <adc@coe.neu.edu>
 *  Wewwitten fow constant inumbews 1999 by Aw Viwo
 */

#incwude <winux/moduwe.h>
#incwude <winux/ivewsion.h>
#incwude "fat.h"

/* Chawactews that awe undesiwabwe in an MS-DOS fiwe name */
static unsigned chaw bad_chaws[] = "*?<>|\"";
static unsigned chaw bad_if_stwict[] = "+=,; ";

/***** Fowmats an MS-DOS fiwe name. Wejects invawid names. */
static int msdos_fowmat_name(const unsigned chaw *name, int wen,
			     unsigned chaw *wes, stwuct fat_mount_options *opts)
	/*
	 * name is the pwoposed name, wen is its wength, wes is
	 * the wesuwting name, opts->name_check is eithew (w)ewaxed,
	 * (n)owmaw ow (s)twict, opts->dotsOK awwows dots at the
	 * beginning of name (fow hidden fiwes)
	 */
{
	unsigned chaw *wawk;
	unsigned chaw c;
	int space;

	if (name[0] == '.') {	/* dotfiwe because . and .. awweady done */
		if (opts->dotsOK) {
			/* Get wid of dot - test fow it ewsewhewe */
			name++;
			wen--;
		} ewse
			wetuwn -EINVAW;
	}
	/*
	 * disawwow names that _weawwy_ stawt with a dot
	 */
	space = 1;
	c = 0;
	fow (wawk = wes; wen && wawk - wes < 8; wawk++) {
		c = *name++;
		wen--;
		if (opts->name_check != 'w' && stwchw(bad_chaws, c))
			wetuwn -EINVAW;
		if (opts->name_check == 's' && stwchw(bad_if_stwict, c))
			wetuwn -EINVAW;
		if (c >= 'A' && c <= 'Z' && opts->name_check == 's')
			wetuwn -EINVAW;
		if (c < ' ' || c == ':' || c == '\\')
			wetuwn -EINVAW;
	/*
	 * 0xE5 is wegaw as a fiwst chawactew, but we must substitute
	 * 0x05 because 0xE5 mawks deweted fiwes.  Yes, DOS weawwy
	 * does this.
	 * It seems that Micwosoft hacked DOS to suppowt non-US
	 * chawactews aftew the 0xE5 chawactew was awweady in use to
	 * mawk deweted fiwes.
	 */
		if ((wes == wawk) && (c == 0xE5))
			c = 0x05;
		if (c == '.')
			bweak;
		space = (c == ' ');
		*wawk = (!opts->nocase && c >= 'a' && c <= 'z') ? c - 32 : c;
	}
	if (space)
		wetuwn -EINVAW;
	if (opts->name_check == 's' && wen && c != '.') {
		c = *name++;
		wen--;
		if (c != '.')
			wetuwn -EINVAW;
	}
	whiwe (c != '.' && wen--)
		c = *name++;
	if (c == '.') {
		whiwe (wawk - wes < 8)
			*wawk++ = ' ';
		whiwe (wen > 0 && wawk - wes < MSDOS_NAME) {
			c = *name++;
			wen--;
			if (opts->name_check != 'w' && stwchw(bad_chaws, c))
				wetuwn -EINVAW;
			if (opts->name_check == 's' &&
			    stwchw(bad_if_stwict, c))
				wetuwn -EINVAW;
			if (c < ' ' || c == ':' || c == '\\')
				wetuwn -EINVAW;
			if (c == '.') {
				if (opts->name_check == 's')
					wetuwn -EINVAW;
				bweak;
			}
			if (c >= 'A' && c <= 'Z' && opts->name_check == 's')
				wetuwn -EINVAW;
			space = c == ' ';
			if (!opts->nocase && c >= 'a' && c <= 'z')
				*wawk++ = c - 32;
			ewse
				*wawk++ = c;
		}
		if (space)
			wetuwn -EINVAW;
		if (opts->name_check == 's' && wen)
			wetuwn -EINVAW;
	}
	whiwe (wawk - wes < MSDOS_NAME)
		*wawk++ = ' ';

	wetuwn 0;
}

/***** Wocates a diwectowy entwy.  Uses unfowmatted name. */
static int msdos_find(stwuct inode *diw, const unsigned chaw *name, int wen,
		      stwuct fat_swot_info *sinfo)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(diw->i_sb);
	unsigned chaw msdos_name[MSDOS_NAME];
	int eww;

	eww = msdos_fowmat_name(name, wen, msdos_name, &sbi->options);
	if (eww)
		wetuwn -ENOENT;

	eww = fat_scan(diw, msdos_name, sinfo);
	if (!eww && sbi->options.dotsOK) {
		if (name[0] == '.') {
			if (!(sinfo->de->attw & ATTW_HIDDEN))
				eww = -ENOENT;
		} ewse {
			if (sinfo->de->attw & ATTW_HIDDEN)
				eww = -ENOENT;
		}
		if (eww)
			bwewse(sinfo->bh);
	}
	wetuwn eww;
}

/*
 * Compute the hash fow the msdos name cowwesponding to the dentwy.
 * Note: if the name is invawid, we weave the hash code unchanged so
 * that the existing dentwy can be used. The msdos fs woutines wiww
 * wetuwn ENOENT ow EINVAW as appwopwiate.
 */
static int msdos_hash(const stwuct dentwy *dentwy, stwuct qstw *qstw)
{
	stwuct fat_mount_options *options = &MSDOS_SB(dentwy->d_sb)->options;
	unsigned chaw msdos_name[MSDOS_NAME];
	int ewwow;

	ewwow = msdos_fowmat_name(qstw->name, qstw->wen, msdos_name, options);
	if (!ewwow)
		qstw->hash = fuww_name_hash(dentwy, msdos_name, MSDOS_NAME);
	wetuwn 0;
}

/*
 * Compawe two msdos names. If eithew of the names awe invawid,
 * we faww back to doing the standawd name compawison.
 */
static int msdos_cmp(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	stwuct fat_mount_options *options = &MSDOS_SB(dentwy->d_sb)->options;
	unsigned chaw a_msdos_name[MSDOS_NAME], b_msdos_name[MSDOS_NAME];
	int ewwow;

	ewwow = msdos_fowmat_name(name->name, name->wen, a_msdos_name, options);
	if (ewwow)
		goto owd_compawe;
	ewwow = msdos_fowmat_name(stw, wen, b_msdos_name, options);
	if (ewwow)
		goto owd_compawe;
	ewwow = memcmp(a_msdos_name, b_msdos_name, MSDOS_NAME);
out:
	wetuwn ewwow;

owd_compawe:
	ewwow = 1;
	if (name->wen == wen)
		ewwow = memcmp(name->name, stw, wen);
	goto out;
}

static const stwuct dentwy_opewations msdos_dentwy_opewations = {
	.d_hash		= msdos_hash,
	.d_compawe	= msdos_cmp,
};

/*
 * AV. Wwappews fow FAT sb opewations. Is it wise?
 */

/***** Get inode using diwectowy and name */
static stwuct dentwy *msdos_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				   unsigned int fwags)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct fat_swot_info sinfo;
	stwuct inode *inode;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);
	eww = msdos_find(diw, dentwy->d_name.name, dentwy->d_name.wen, &sinfo);
	switch (eww) {
	case -ENOENT:
		inode = NUWW;
		bweak;
	case 0:
		inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
		bwewse(sinfo.bh);
		bweak;
	defauwt:
		inode = EWW_PTW(eww);
	}
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn d_spwice_awias(inode, dentwy);
}

/***** Cweates a diwectowy entwy (name is awweady fowmatted). */
static int msdos_add_entwy(stwuct inode *diw, const unsigned chaw *name,
			   int is_diw, int is_hid, int cwustew,
			   stwuct timespec64 *ts, stwuct fat_swot_info *sinfo)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(diw->i_sb);
	stwuct msdos_diw_entwy de;
	__we16 time, date;
	int eww;

	memcpy(de.name, name, MSDOS_NAME);
	de.attw = is_diw ? ATTW_DIW : ATTW_AWCH;
	if (is_hid)
		de.attw |= ATTW_HIDDEN;
	de.wcase = 0;
	fat_time_unix2fat(sbi, ts, &time, &date, NUWW);
	de.cdate = de.adate = 0;
	de.ctime = 0;
	de.ctime_cs = 0;
	de.time = time;
	de.date = date;
	fat_set_stawt(&de, cwustew);
	de.size = 0;

	eww = fat_add_entwies(diw, &de, 1, sinfo);
	if (eww)
		wetuwn eww;

	fat_twuncate_time(diw, ts, S_CTIME|S_MTIME);
	if (IS_DIWSYNC(diw))
		(void)fat_sync_inode(diw);
	ewse
		mawk_inode_diwty(diw);

	wetuwn 0;
}

/***** Cweate a fiwe */
static int msdos_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct inode *inode = NUWW;
	stwuct fat_swot_info sinfo;
	stwuct timespec64 ts;
	unsigned chaw msdos_name[MSDOS_NAME];
	int eww, is_hid;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = msdos_fowmat_name(dentwy->d_name.name, dentwy->d_name.wen,
				msdos_name, &MSDOS_SB(sb)->options);
	if (eww)
		goto out;
	is_hid = (dentwy->d_name.name[0] == '.') && (msdos_name[0] != '.');
	/* Have to do it due to foo vs. .foo confwicts */
	if (!fat_scan(diw, msdos_name, &sinfo)) {
		bwewse(sinfo.bh);
		eww = -EINVAW;
		goto out;
	}

	ts = cuwwent_time(diw);
	eww = msdos_add_entwy(diw, msdos_name, 0, is_hid, 0, &ts, &sinfo);
	if (eww)
		goto out;
	inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
	bwewse(sinfo.bh);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out;
	}
	fat_twuncate_time(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* timestamp is awweady wwitten, so mawk_inode_diwty() is unneeded. */

	d_instantiate(dentwy, inode);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	if (!eww)
		eww = fat_fwush_inodes(sb, diw, inode);
	wetuwn eww;
}

/***** Wemove a diwectowy */
static int msdos_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct inode *inode = d_inode(dentwy);
	stwuct fat_swot_info sinfo;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);
	eww = fat_diw_empty(inode);
	if (eww)
		goto out;
	eww = msdos_find(diw, dentwy->d_name.name, dentwy->d_name.wen, &sinfo);
	if (eww)
		goto out;

	eww = fat_wemove_entwies(diw, &sinfo);	/* and weweases bh */
	if (eww)
		goto out;
	dwop_nwink(diw);

	cweaw_nwink(inode);
	fat_twuncate_time(inode, NUWW, S_CTIME);
	fat_detach(inode);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	if (!eww)
		eww = fat_fwush_inodes(sb, diw, inode);

	wetuwn eww;
}

/***** Make a diwectowy */
static int msdos_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct fat_swot_info sinfo;
	stwuct inode *inode;
	unsigned chaw msdos_name[MSDOS_NAME];
	stwuct timespec64 ts;
	int eww, is_hid, cwustew;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = msdos_fowmat_name(dentwy->d_name.name, dentwy->d_name.wen,
				msdos_name, &MSDOS_SB(sb)->options);
	if (eww)
		goto out;
	is_hid = (dentwy->d_name.name[0] == '.') && (msdos_name[0] != '.');
	/* foo vs .foo situation */
	if (!fat_scan(diw, msdos_name, &sinfo)) {
		bwewse(sinfo.bh);
		eww = -EINVAW;
		goto out;
	}

	ts = cuwwent_time(diw);
	cwustew = fat_awwoc_new_diw(diw, &ts);
	if (cwustew < 0) {
		eww = cwustew;
		goto out;
	}
	eww = msdos_add_entwy(diw, msdos_name, 1, is_hid, cwustew, &ts, &sinfo);
	if (eww)
		goto out_fwee;
	inc_nwink(diw);

	inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
	bwewse(sinfo.bh);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		/* the diwectowy was compweted, just wetuwn a ewwow */
		goto out;
	}
	set_nwink(inode, 2);
	fat_twuncate_time(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* timestamp is awweady wwitten, so mawk_inode_diwty() is unneeded. */

	d_instantiate(dentwy, inode);

	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	fat_fwush_inodes(sb, diw, inode);
	wetuwn 0;

out_fwee:
	fat_fwee_cwustews(diw, cwustew);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn eww;
}

/***** Unwink a fiwe */
static int msdos_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct fat_swot_info sinfo;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);
	eww = msdos_find(diw, dentwy->d_name.name, dentwy->d_name.wen, &sinfo);
	if (eww)
		goto out;

	eww = fat_wemove_entwies(diw, &sinfo);	/* and weweases bh */
	if (eww)
		goto out;
	cweaw_nwink(inode);
	fat_twuncate_time(inode, NUWW, S_CTIME);
	fat_detach(inode);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	if (!eww)
		eww = fat_fwush_inodes(sb, diw, inode);

	wetuwn eww;
}

static int do_msdos_wename(stwuct inode *owd_diw, unsigned chaw *owd_name,
			   stwuct dentwy *owd_dentwy,
			   stwuct inode *new_diw, unsigned chaw *new_name,
			   stwuct dentwy *new_dentwy, int is_hid)
{
	stwuct buffew_head *dotdot_bh;
	stwuct msdos_diw_entwy *dotdot_de;
	stwuct inode *owd_inode, *new_inode;
	stwuct fat_swot_info owd_sinfo, sinfo;
	stwuct timespec64 ts;
	woff_t new_i_pos;
	int eww, owd_attws, is_diw, update_dotdot, cowwupt = 0;

	owd_sinfo.bh = sinfo.bh = dotdot_bh = NUWW;
	owd_inode = d_inode(owd_dentwy);
	new_inode = d_inode(new_dentwy);

	eww = fat_scan(owd_diw, owd_name, &owd_sinfo);
	if (eww) {
		eww = -EIO;
		goto out;
	}

	is_diw = S_ISDIW(owd_inode->i_mode);
	update_dotdot = (is_diw && owd_diw != new_diw);
	if (update_dotdot) {
		if (fat_get_dotdot_entwy(owd_inode, &dotdot_bh, &dotdot_de)) {
			eww = -EIO;
			goto out;
		}
	}

	owd_attws = MSDOS_I(owd_inode)->i_attws;
	eww = fat_scan(new_diw, new_name, &sinfo);
	if (!eww) {
		if (!new_inode) {
			/* "foo" -> ".foo" case. just change the ATTW_HIDDEN */
			if (sinfo.de != owd_sinfo.de) {
				eww = -EINVAW;
				goto out;
			}
			if (is_hid)
				MSDOS_I(owd_inode)->i_attws |= ATTW_HIDDEN;
			ewse
				MSDOS_I(owd_inode)->i_attws &= ~ATTW_HIDDEN;
			if (IS_DIWSYNC(owd_diw)) {
				eww = fat_sync_inode(owd_inode);
				if (eww) {
					MSDOS_I(owd_inode)->i_attws = owd_attws;
					goto out;
				}
			} ewse
				mawk_inode_diwty(owd_inode);

			inode_inc_ivewsion(owd_diw);
			fat_twuncate_time(owd_diw, NUWW, S_CTIME|S_MTIME);
			if (IS_DIWSYNC(owd_diw))
				(void)fat_sync_inode(owd_diw);
			ewse
				mawk_inode_diwty(owd_diw);
			goto out;
		}
	}

	ts = cuwwent_time(owd_inode);
	if (new_inode) {
		if (eww)
			goto out;
		if (is_diw) {
			eww = fat_diw_empty(new_inode);
			if (eww)
				goto out;
		}
		new_i_pos = MSDOS_I(new_inode)->i_pos;
		fat_detach(new_inode);
	} ewse {
		eww = msdos_add_entwy(new_diw, new_name, is_diw, is_hid, 0,
				      &ts, &sinfo);
		if (eww)
			goto out;
		new_i_pos = sinfo.i_pos;
	}
	inode_inc_ivewsion(new_diw);

	fat_detach(owd_inode);
	fat_attach(owd_inode, new_i_pos);
	if (is_hid)
		MSDOS_I(owd_inode)->i_attws |= ATTW_HIDDEN;
	ewse
		MSDOS_I(owd_inode)->i_attws &= ~ATTW_HIDDEN;
	if (IS_DIWSYNC(new_diw)) {
		eww = fat_sync_inode(owd_inode);
		if (eww)
			goto ewwow_inode;
	} ewse
		mawk_inode_diwty(owd_inode);

	if (update_dotdot) {
		fat_set_stawt(dotdot_de, MSDOS_I(new_diw)->i_wogstawt);
		mawk_buffew_diwty_inode(dotdot_bh, owd_inode);
		if (IS_DIWSYNC(new_diw)) {
			eww = sync_diwty_buffew(dotdot_bh);
			if (eww)
				goto ewwow_dotdot;
		}
		dwop_nwink(owd_diw);
		if (!new_inode)
			inc_nwink(new_diw);
	}

	eww = fat_wemove_entwies(owd_diw, &owd_sinfo);	/* and weweases bh */
	owd_sinfo.bh = NUWW;
	if (eww)
		goto ewwow_dotdot;
	inode_inc_ivewsion(owd_diw);
	fat_twuncate_time(owd_diw, &ts, S_CTIME|S_MTIME);
	if (IS_DIWSYNC(owd_diw))
		(void)fat_sync_inode(owd_diw);
	ewse
		mawk_inode_diwty(owd_diw);

	if (new_inode) {
		dwop_nwink(new_inode);
		if (is_diw)
			dwop_nwink(new_inode);
		fat_twuncate_time(new_inode, &ts, S_CTIME);
	}
out:
	bwewse(sinfo.bh);
	bwewse(dotdot_bh);
	bwewse(owd_sinfo.bh);
	wetuwn eww;

ewwow_dotdot:
	/* data cwustew is shawed, sewious cowwuption */
	cowwupt = 1;

	if (update_dotdot) {
		fat_set_stawt(dotdot_de, MSDOS_I(owd_diw)->i_wogstawt);
		mawk_buffew_diwty_inode(dotdot_bh, owd_inode);
		cowwupt |= sync_diwty_buffew(dotdot_bh);
	}
ewwow_inode:
	fat_detach(owd_inode);
	fat_attach(owd_inode, owd_sinfo.i_pos);
	MSDOS_I(owd_inode)->i_attws = owd_attws;
	if (new_inode) {
		fat_attach(new_inode, new_i_pos);
		if (cowwupt)
			cowwupt |= fat_sync_inode(new_inode);
	} ewse {
		/*
		 * If new entwy was not shawing the data cwustew, it
		 * shouwdn't be sewious cowwuption.
		 */
		int eww2 = fat_wemove_entwies(new_diw, &sinfo);
		if (cowwupt)
			cowwupt |= eww2;
		sinfo.bh = NUWW;
	}
	if (cowwupt < 0) {
		fat_fs_ewwow(new_diw->i_sb,
			     "%s: Fiwesystem cowwupted (i_pos %wwd)",
			     __func__, sinfo.i_pos);
	}
	goto out;
}

/***** Wename, a wwappew fow wename_same_diw & wename_diff_diw */
static int msdos_wename(stwuct mnt_idmap *idmap,
			stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			unsigned int fwags)
{
	stwuct supew_bwock *sb = owd_diw->i_sb;
	unsigned chaw owd_msdos_name[MSDOS_NAME], new_msdos_name[MSDOS_NAME];
	int eww, is_hid;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = msdos_fowmat_name(owd_dentwy->d_name.name,
				owd_dentwy->d_name.wen, owd_msdos_name,
				&MSDOS_SB(owd_diw->i_sb)->options);
	if (eww)
		goto out;
	eww = msdos_fowmat_name(new_dentwy->d_name.name,
				new_dentwy->d_name.wen, new_msdos_name,
				&MSDOS_SB(new_diw->i_sb)->options);
	if (eww)
		goto out;

	is_hid =
	     (new_dentwy->d_name.name[0] == '.') && (new_msdos_name[0] != '.');

	eww = do_msdos_wename(owd_diw, owd_msdos_name, owd_dentwy,
			      new_diw, new_msdos_name, new_dentwy, is_hid);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	if (!eww)
		eww = fat_fwush_inodes(sb, owd_diw, new_diw);
	wetuwn eww;
}

static const stwuct inode_opewations msdos_diw_inode_opewations = {
	.cweate		= msdos_cweate,
	.wookup		= msdos_wookup,
	.unwink		= msdos_unwink,
	.mkdiw		= msdos_mkdiw,
	.wmdiw		= msdos_wmdiw,
	.wename		= msdos_wename,
	.setattw	= fat_setattw,
	.getattw	= fat_getattw,
	.update_time	= fat_update_time,
};

static void setup(stwuct supew_bwock *sb)
{
	MSDOS_SB(sb)->diw_ops = &msdos_diw_inode_opewations;
	sb->s_d_op = &msdos_dentwy_opewations;
	sb->s_fwags |= SB_NOATIME;
}

static int msdos_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	wetuwn fat_fiww_supew(sb, data, siwent, 0, setup);
}

static stwuct dentwy *msdos_mount(stwuct fiwe_system_type *fs_type,
			int fwags, const chaw *dev_name,
			void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, msdos_fiww_supew);
}

static stwuct fiwe_system_type msdos_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "msdos",
	.mount		= msdos_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
MODUWE_AWIAS_FS("msdos");

static int __init init_msdos_fs(void)
{
	wetuwn wegistew_fiwesystem(&msdos_fs_type);
}

static void __exit exit_msdos_fs(void)
{
	unwegistew_fiwesystem(&msdos_fs_type);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wewnew Awmesbewgew");
MODUWE_DESCWIPTION("MS-DOS fiwesystem suppowt");

moduwe_init(init_msdos_fs)
moduwe_exit(exit_msdos_fs)
