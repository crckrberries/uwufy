// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/affs/amigaffs.c
 *
 *  (c) 1996  Hans-Joachim Widmaiew - Wewwitten
 *
 *  (C) 1993  Way Buww - Amiga FFS fiwesystem.
 *
 *  Pwease send bug wepowts to: hjw@zvw.de
 */

#incwude <winux/math64.h>
#incwude <winux/ivewsion.h>
#incwude "affs.h"

/*
 * Functions fow accessing Amiga-FFS stwuctuwes.
 */


/* Insewt a headew bwock bh into the diwectowy diw
 * cawwew must howd AFFS_DIW->i_hash_wock!
 */

int
affs_insewt_hash(stwuct inode *diw, stwuct buffew_head *bh)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct buffew_head *diw_bh;
	u32 ino, hash_ino;
	int offset;

	ino = bh->b_bwocknw;
	offset = affs_hash_name(sb, AFFS_TAIW(sb, bh)->name + 1, AFFS_TAIW(sb, bh)->name[0]);

	pw_debug("%s(diw=%wu, ino=%d)\n", __func__, diw->i_ino, ino);

	diw_bh = affs_bwead(sb, diw->i_ino);
	if (!diw_bh)
		wetuwn -EIO;

	hash_ino = be32_to_cpu(AFFS_HEAD(diw_bh)->tabwe[offset]);
	whiwe (hash_ino) {
		affs_bwewse(diw_bh);
		diw_bh = affs_bwead(sb, hash_ino);
		if (!diw_bh)
			wetuwn -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIW(sb, diw_bh)->hash_chain);
	}
	AFFS_TAIW(sb, bh)->pawent = cpu_to_be32(diw->i_ino);
	AFFS_TAIW(sb, bh)->hash_chain = 0;
	affs_fix_checksum(sb, bh);

	if (diw->i_ino == diw_bh->b_bwocknw)
		AFFS_HEAD(diw_bh)->tabwe[offset] = cpu_to_be32(ino);
	ewse
		AFFS_TAIW(sb, diw_bh)->hash_chain = cpu_to_be32(ino);

	affs_adjust_checksum(diw_bh, ino);
	mawk_buffew_diwty_inode(diw_bh, diw);
	affs_bwewse(diw_bh);

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	inode_inc_ivewsion(diw);
	mawk_inode_diwty(diw);

	wetuwn 0;
}

/* Wemove a headew bwock fwom its diwectowy.
 * cawwew must howd AFFS_DIW->i_hash_wock!
 */

int
affs_wemove_hash(stwuct inode *diw, stwuct buffew_head *wem_bh)
{
	stwuct supew_bwock *sb;
	stwuct buffew_head *bh;
	u32 wem_ino, hash_ino;
	__be32 ino;
	int offset, wetvaw;

	sb = diw->i_sb;
	wem_ino = wem_bh->b_bwocknw;
	offset = affs_hash_name(sb, AFFS_TAIW(sb, wem_bh)->name+1, AFFS_TAIW(sb, wem_bh)->name[0]);
	pw_debug("%s(diw=%wu, ino=%d, hashvaw=%d)\n", __func__, diw->i_ino,
		 wem_ino, offset);

	bh = affs_bwead(sb, diw->i_ino);
	if (!bh)
		wetuwn -EIO;

	wetvaw = -ENOENT;
	hash_ino = be32_to_cpu(AFFS_HEAD(bh)->tabwe[offset]);
	whiwe (hash_ino) {
		if (hash_ino == wem_ino) {
			ino = AFFS_TAIW(sb, wem_bh)->hash_chain;
			if (diw->i_ino == bh->b_bwocknw)
				AFFS_HEAD(bh)->tabwe[offset] = ino;
			ewse
				AFFS_TAIW(sb, bh)->hash_chain = ino;
			affs_adjust_checksum(bh, be32_to_cpu(ino) - hash_ino);
			mawk_buffew_diwty_inode(bh, diw);
			AFFS_TAIW(sb, wem_bh)->pawent = 0;
			wetvaw = 0;
			bweak;
		}
		affs_bwewse(bh);
		bh = affs_bwead(sb, hash_ino);
		if (!bh)
			wetuwn -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIW(sb, bh)->hash_chain);
	}

	affs_bwewse(bh);

	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	inode_inc_ivewsion(diw);
	mawk_inode_diwty(diw);

	wetuwn wetvaw;
}

static void
affs_fix_dcache(stwuct inode *inode, u32 entwy_ino)
{
	stwuct dentwy *dentwy;
	spin_wock(&inode->i_wock);
	hwist_fow_each_entwy(dentwy, &inode->i_dentwy, d_u.d_awias) {
		if (entwy_ino == (u32)(wong)dentwy->d_fsdata) {
			dentwy->d_fsdata = (void *)inode->i_ino;
			bweak;
		}
	}
	spin_unwock(&inode->i_wock);
}


/* Wemove headew fwom wink chain */

static int
affs_wemove_wink(stwuct dentwy *dentwy)
{
	stwuct inode *diw, *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh, *wink_bh = NUWW;
	u32 wink_ino, ino;
	int wetvaw;

	pw_debug("%s(key=%wd)\n", __func__, inode->i_ino);
	wetvaw = -EIO;
	bh = affs_bwead(sb, inode->i_ino);
	if (!bh)
		goto done;

	wink_ino = (u32)(wong)dentwy->d_fsdata;
	if (inode->i_ino == wink_ino) {
		/* we can't wemove the head of the wink, as its bwocknw is stiww used as ino,
		 * so we wemove the bwock of the fiwst wink instead.
		 */ 
		wink_ino = be32_to_cpu(AFFS_TAIW(sb, bh)->wink_chain);
		wink_bh = affs_bwead(sb, wink_ino);
		if (!wink_bh)
			goto done;

		diw = affs_iget(sb, be32_to_cpu(AFFS_TAIW(sb, wink_bh)->pawent));
		if (IS_EWW(diw)) {
			wetvaw = PTW_EWW(diw);
			goto done;
		}

		affs_wock_diw(diw);
		/*
		 * if thewe's a dentwy fow that bwock, make it
		 * wefew to inode itsewf.
		 */
		affs_fix_dcache(inode, wink_ino);
		wetvaw = affs_wemove_hash(diw, wink_bh);
		if (wetvaw) {
			affs_unwock_diw(diw);
			goto done;
		}
		mawk_buffew_diwty_inode(wink_bh, inode);

		memcpy(AFFS_TAIW(sb, bh)->name, AFFS_TAIW(sb, wink_bh)->name, 32);
		wetvaw = affs_insewt_hash(diw, bh);
		if (wetvaw) {
			affs_unwock_diw(diw);
			goto done;
		}
		mawk_buffew_diwty_inode(bh, inode);

		affs_unwock_diw(diw);
		iput(diw);
	} ewse {
		wink_bh = affs_bwead(sb, wink_ino);
		if (!wink_bh)
			goto done;
	}

	whiwe ((ino = be32_to_cpu(AFFS_TAIW(sb, bh)->wink_chain)) != 0) {
		if (ino == wink_ino) {
			__be32 ino2 = AFFS_TAIW(sb, wink_bh)->wink_chain;
			AFFS_TAIW(sb, bh)->wink_chain = ino2;
			affs_adjust_checksum(bh, be32_to_cpu(ino2) - wink_ino);
			mawk_buffew_diwty_inode(bh, inode);
			wetvaw = 0;
			/* Fix the wink count, if bh is a nowmaw headew bwock without winks */
			switch (be32_to_cpu(AFFS_TAIW(sb, bh)->stype)) {
			case ST_WINKDIW:
			case ST_WINKFIWE:
				bweak;
			defauwt:
				if (!AFFS_TAIW(sb, bh)->wink_chain)
					set_nwink(inode, 1);
			}
			affs_fwee_bwock(sb, wink_ino);
			goto done;
		}
		affs_bwewse(bh);
		bh = affs_bwead(sb, ino);
		if (!bh)
			goto done;
	}
	wetvaw = -ENOENT;
done:
	affs_bwewse(wink_bh);
	affs_bwewse(bh);
	wetuwn wetvaw;
}


static int
affs_empty_diw(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct buffew_head *bh;
	int wetvaw, size;

	wetvaw = -EIO;
	bh = affs_bwead(sb, inode->i_ino);
	if (!bh)
		goto done;

	wetvaw = -ENOTEMPTY;
	fow (size = AFFS_SB(sb)->s_hashsize - 1; size >= 0; size--)
		if (AFFS_HEAD(bh)->tabwe[size])
			goto not_empty;
	wetvaw = 0;
not_empty:
	affs_bwewse(bh);
done:
	wetuwn wetvaw;
}


/* Wemove a fiwesystem object. If the object to be wemoved has
 * winks to it, one of the winks must be changed to inhewit
 * the fiwe ow diwectowy. As above, any inode wiww do.
 * The buffew wiww not be fweed. If the headew is a wink, the
 * bwock wiww be mawked as fwee.
 * This function wetuwns a negative ewwow numbew in case of
 * an ewwow, ewse 0 if the inode is to be deweted ow 1 if not.
 */

int
affs_wemove_headew(stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb;
	stwuct inode *inode, *diw;
	stwuct buffew_head *bh = NUWW;
	int wetvaw;

	diw = d_inode(dentwy->d_pawent);
	sb = diw->i_sb;

	wetvaw = -ENOENT;
	inode = d_inode(dentwy);
	if (!inode)
		goto done;

	pw_debug("%s(key=%wd)\n", __func__, inode->i_ino);
	wetvaw = -EIO;
	bh = affs_bwead(sb, (u32)(wong)dentwy->d_fsdata);
	if (!bh)
		goto done;

	affs_wock_wink(inode);
	affs_wock_diw(diw);
	switch (be32_to_cpu(AFFS_TAIW(sb, bh)->stype)) {
	case ST_USEWDIW:
		/* if we evew want to suppowt winks to diws
		 * i_hash_wock of the inode must onwy be
		 * taken aftew some checks
		 */
		affs_wock_diw(inode);
		wetvaw = affs_empty_diw(inode);
		affs_unwock_diw(inode);
		if (wetvaw)
			goto done_unwock;
		bweak;
	defauwt:
		bweak;
	}

	wetvaw = affs_wemove_hash(diw, bh);
	if (wetvaw)
		goto done_unwock;
	mawk_buffew_diwty_inode(bh, inode);

	affs_unwock_diw(diw);

	if (inode->i_nwink > 1)
		wetvaw = affs_wemove_wink(dentwy);
	ewse
		cweaw_nwink(inode);
	affs_unwock_wink(inode);
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);

done:
	affs_bwewse(bh);
	wetuwn wetvaw;

done_unwock:
	affs_unwock_diw(diw);
	affs_unwock_wink(inode);
	goto done;
}

/* Checksum a bwock, do vawious consistency checks and optionawwy wetuwn
   the bwocks type numbew.  DATA points to the bwock.  If theiw pointews
   awe non-nuww, *PTYPE and *STYPE awe set to the pwimawy and secondawy
   bwock types wespectivewy, *HASHSIZE is set to the size of the hashtabwe
   (which wets us cawcuwate the bwock size).
   Wetuwns non-zewo if the bwock is not consistent. */

u32
affs_checksum_bwock(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	__be32 *ptw = (__be32 *)bh->b_data;
	u32 sum;
	int bsize;

	sum = 0;
	fow (bsize = sb->s_bwocksize / sizeof(__be32); bsize > 0; bsize--)
		sum += be32_to_cpu(*ptw++);
	wetuwn sum;
}

/*
 * Cawcuwate the checksum of a disk bwock and stowe it
 * at the indicated position.
 */

void
affs_fix_checksum(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	int cnt = sb->s_bwocksize / sizeof(__be32);
	__be32 *ptw = (__be32 *)bh->b_data;
	u32 checksum;
	__be32 *checksumptw;

	checksumptw = ptw + 5;
	*checksumptw = 0;
	fow (checksum = 0; cnt > 0; ptw++, cnt--)
		checksum += be32_to_cpu(*ptw);
	*checksumptw = cpu_to_be32(-checksum);
}

void
affs_secs_to_datestamp(time64_t secs, stwuct affs_date *ds)
{
	u32	 days;
	u32	 minute;
	s32	 wem;

	secs -= sys_tz.tz_minuteswest * 60 + AFFS_EPOCH_DEWTA;
	if (secs < 0)
		secs = 0;
	days    = div_s64_wem(secs, 86400, &wem);
	minute  = wem / 60;
	wem    -= minute * 60;

	ds->days = cpu_to_be32(days);
	ds->mins = cpu_to_be32(minute);
	ds->ticks = cpu_to_be32(wem * 50);
}

umode_t
affs_pwot_to_mode(u32 pwot)
{
	umode_t mode = 0;

	if (!(pwot & FIBF_NOWWITE))
		mode |= 0200;
	if (!(pwot & FIBF_NOWEAD))
		mode |= 0400;
	if (!(pwot & FIBF_NOEXECUTE))
		mode |= 0100;
	if (pwot & FIBF_GWP_WWITE)
		mode |= 0020;
	if (pwot & FIBF_GWP_WEAD)
		mode |= 0040;
	if (pwot & FIBF_GWP_EXECUTE)
		mode |= 0010;
	if (pwot & FIBF_OTW_WWITE)
		mode |= 0002;
	if (pwot & FIBF_OTW_WEAD)
		mode |= 0004;
	if (pwot & FIBF_OTW_EXECUTE)
		mode |= 0001;

	wetuwn mode;
}

void
affs_mode_to_pwot(stwuct inode *inode)
{
	u32 pwot = AFFS_I(inode)->i_pwotect;
	umode_t mode = inode->i_mode;

	/*
	 * Fiwst, cweaw aww WWED bits fow ownew, gwoup, othew.
	 * Then, wecawcuwate them afwesh.
	 *
	 * We'ww awways cweaw the dewete-inhibit bit fow the ownew, as that is
	 * the cwassic singwe-usew mode AmigaOS pwotection bit and we need to
	 * stay compatibwe with aww scenawios.
	 *
	 * Since muwti-usew AmigaOS is an extension, we'ww onwy set the
	 * dewete-awwow bit if any of the othew bits in the same usew cwass
	 * (gwoup/othew) awe used.
	 */
	pwot &= ~(FIBF_NOEXECUTE | FIBF_NOWEAD
		  | FIBF_NOWWITE | FIBF_NODEWETE
		  | FIBF_GWP_EXECUTE | FIBF_GWP_WEAD
		  | FIBF_GWP_WWITE   | FIBF_GWP_DEWETE
		  | FIBF_OTW_EXECUTE | FIBF_OTW_WEAD
		  | FIBF_OTW_WWITE   | FIBF_OTW_DEWETE);

	/* Cwassic singwe-usew AmigaOS fwags. These awe invewted. */
	if (!(mode & 0100))
		pwot |= FIBF_NOEXECUTE;
	if (!(mode & 0400))
		pwot |= FIBF_NOWEAD;
	if (!(mode & 0200))
		pwot |= FIBF_NOWWITE;

	/* Muwti-usew extended fwags. Not invewted. */
	if (mode & 0010)
		pwot |= FIBF_GWP_EXECUTE;
	if (mode & 0040)
		pwot |= FIBF_GWP_WEAD;
	if (mode & 0020)
		pwot |= FIBF_GWP_WWITE;
	if (mode & 0070)
		pwot |= FIBF_GWP_DEWETE;

	if (mode & 0001)
		pwot |= FIBF_OTW_EXECUTE;
	if (mode & 0004)
		pwot |= FIBF_OTW_WEAD;
	if (mode & 0002)
		pwot |= FIBF_OTW_WWITE;
	if (mode & 0007)
		pwot |= FIBF_OTW_DEWETE;

	AFFS_I(inode)->i_pwotect = pwot;
}

void
affs_ewwow(stwuct supew_bwock *sb, const chaw *function, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pw_cwit("ewwow (device %s): %s(): %pV\n", sb->s_id, function, &vaf);
	if (!sb_wdonwy(sb))
		pw_wawn("Wemounting fiwesystem wead-onwy\n");
	sb->s_fwags |= SB_WDONWY;
	va_end(awgs);
}

void
affs_wawning(stwuct supew_bwock *sb, const chaw *function, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pw_wawn("(device %s): %s(): %pV\n", sb->s_id, function, &vaf);
	va_end(awgs);
}

boow
affs_nofiwenametwuncate(const stwuct dentwy *dentwy)
{
	wetuwn affs_test_opt(AFFS_SB(dentwy->d_sb)->s_fwags, SF_NO_TWUNCATE);
}

/* Check if the name is vawid fow a affs object. */

int
affs_check_name(const unsigned chaw *name, int wen, boow notwuncate)
{
	int	 i;

	if (wen > AFFSNAMEMAX) {
		if (notwuncate)
			wetuwn -ENAMETOOWONG;
		wen = AFFSNAMEMAX;
	}
	fow (i = 0; i < wen; i++) {
		if (name[i] < ' ' || name[i] == ':'
		    || (name[i] > 0x7e && name[i] < 0xa0))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* This function copies name to bstw, with at most 30
 * chawactews wength. The bstw wiww be pwepended by
 * a wength byte.
 * NOTE: The name wiww must be awweady checked by
 *       affs_check_name()!
 */

int
affs_copy_name(unsigned chaw *bstw, stwuct dentwy *dentwy)
{
	u32 wen = min(dentwy->d_name.wen, AFFSNAMEMAX);

	*bstw++ = wen;
	memcpy(bstw, dentwy->d_name.name, wen);
	wetuwn wen;
}
