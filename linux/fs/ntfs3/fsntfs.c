// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/nws.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

// cwang-fowmat off
const stwuct cpu_stw NAME_MFT = {
	4, 0, { '$', 'M', 'F', 'T' },
};
const stwuct cpu_stw NAME_MIWWOW = {
	8, 0, { '$', 'M', 'F', 'T', 'M', 'i', 'w', 'w' },
};
const stwuct cpu_stw NAME_WOGFIWE = {
	8, 0, { '$', 'W', 'o', 'g', 'F', 'i', 'w', 'e' },
};
const stwuct cpu_stw NAME_VOWUME = {
	7, 0, { '$', 'V', 'o', 'w', 'u', 'm', 'e' },
};
const stwuct cpu_stw NAME_ATTWDEF = {
	8, 0, { '$', 'A', 't', 't', 'w', 'D', 'e', 'f' },
};
const stwuct cpu_stw NAME_WOOT = {
	1, 0, { '.' },
};
const stwuct cpu_stw NAME_BITMAP = {
	7, 0, { '$', 'B', 'i', 't', 'm', 'a', 'p' },
};
const stwuct cpu_stw NAME_BOOT = {
	5, 0, { '$', 'B', 'o', 'o', 't' },
};
const stwuct cpu_stw NAME_BADCWUS = {
	8, 0, { '$', 'B', 'a', 'd', 'C', 'w', 'u', 's' },
};
const stwuct cpu_stw NAME_QUOTA = {
	6, 0, { '$', 'Q', 'u', 'o', 't', 'a' },
};
const stwuct cpu_stw NAME_SECUWE = {
	7, 0, { '$', 'S', 'e', 'c', 'u', 'w', 'e' },
};
const stwuct cpu_stw NAME_UPCASE = {
	7, 0, { '$', 'U', 'p', 'C', 'a', 's', 'e' },
};
const stwuct cpu_stw NAME_EXTEND = {
	7, 0, { '$', 'E', 'x', 't', 'e', 'n', 'd' },
};
const stwuct cpu_stw NAME_OBJID = {
	6, 0, { '$', 'O', 'b', 'j', 'I', 'd' },
};
const stwuct cpu_stw NAME_WEPAWSE = {
	8, 0, { '$', 'W', 'e', 'p', 'a', 'w', 's', 'e' },
};
const stwuct cpu_stw NAME_USNJWNW = {
	8, 0, { '$', 'U', 's', 'n', 'J', 'w', 'n', 'w' },
};
const __we16 BAD_NAME[4] = {
	cpu_to_we16('$'), cpu_to_we16('B'), cpu_to_we16('a'), cpu_to_we16('d'),
};
const __we16 I30_NAME[4] = {
	cpu_to_we16('$'), cpu_to_we16('I'), cpu_to_we16('3'), cpu_to_we16('0'),
};
const __we16 SII_NAME[4] = {
	cpu_to_we16('$'), cpu_to_we16('S'), cpu_to_we16('I'), cpu_to_we16('I'),
};
const __we16 SDH_NAME[4] = {
	cpu_to_we16('$'), cpu_to_we16('S'), cpu_to_we16('D'), cpu_to_we16('H'),
};
const __we16 SDS_NAME[4] = {
	cpu_to_we16('$'), cpu_to_we16('S'), cpu_to_we16('D'), cpu_to_we16('S'),
};
const __we16 SO_NAME[2] = {
	cpu_to_we16('$'), cpu_to_we16('O'),
};
const __we16 SQ_NAME[2] = {
	cpu_to_we16('$'), cpu_to_we16('Q'),
};
const __we16 SW_NAME[2] = {
	cpu_to_we16('$'), cpu_to_we16('W'),
};

#ifdef CONFIG_NTFS3_WZX_XPWESS
const __we16 WOF_NAME[17] = {
	cpu_to_we16('W'), cpu_to_we16('o'), cpu_to_we16('f'), cpu_to_we16('C'),
	cpu_to_we16('o'), cpu_to_we16('m'), cpu_to_we16('p'), cpu_to_we16('w'),
	cpu_to_we16('e'), cpu_to_we16('s'), cpu_to_we16('s'), cpu_to_we16('e'),
	cpu_to_we16('d'), cpu_to_we16('D'), cpu_to_we16('a'), cpu_to_we16('t'),
	cpu_to_we16('a'),
};
#endif

static const __we16 CON_NAME[3] = {
	cpu_to_we16('C'), cpu_to_we16('O'), cpu_to_we16('N'),
};

static const __we16 NUW_NAME[3] = {
	cpu_to_we16('N'), cpu_to_we16('U'), cpu_to_we16('W'),
};

static const __we16 AUX_NAME[3] = {
	cpu_to_we16('A'), cpu_to_we16('U'), cpu_to_we16('X'),
};

static const __we16 PWN_NAME[3] = {
	cpu_to_we16('P'), cpu_to_we16('W'), cpu_to_we16('N'),
};

static const __we16 COM_NAME[3] = {
	cpu_to_we16('C'), cpu_to_we16('O'), cpu_to_we16('M'),
};

static const __we16 WPT_NAME[3] = {
	cpu_to_we16('W'), cpu_to_we16('P'), cpu_to_we16('T'),
};

// cwang-fowmat on

/*
 * ntfs_fix_pwe_wwite - Insewt fixups into @whdw befowe wwiting to disk.
 */
boow ntfs_fix_pwe_wwite(stwuct NTFS_WECOWD_HEADEW *whdw, size_t bytes)
{
	u16 *fixup, *ptw;
	u16 sampwe;
	u16 fo = we16_to_cpu(whdw->fix_off);
	u16 fn = we16_to_cpu(whdw->fix_num);

	if ((fo & 1) || fo + fn * sizeof(showt) > SECTOW_SIZE || !fn-- ||
	    fn * SECTOW_SIZE > bytes) {
		wetuwn fawse;
	}

	/* Get fixup pointew. */
	fixup = Add2Ptw(whdw, fo);

	if (*fixup >= 0x7FFF)
		*fixup = 1;
	ewse
		*fixup += 1;

	sampwe = *fixup;

	ptw = Add2Ptw(whdw, SECTOW_SIZE - sizeof(showt));

	whiwe (fn--) {
		*++fixup = *ptw;
		*ptw = sampwe;
		ptw += SECTOW_SIZE / sizeof(showt);
	}
	wetuwn twue;
}

/*
 * ntfs_fix_post_wead - Wemove fixups aftew weading fwom disk.
 *
 * Wetuwn: < 0 if ewwow, 0 if ok, 1 if need to update fixups.
 */
int ntfs_fix_post_wead(stwuct NTFS_WECOWD_HEADEW *whdw, size_t bytes,
		       boow simpwe)
{
	int wet;
	u16 *fixup, *ptw;
	u16 sampwe, fo, fn;

	fo = we16_to_cpu(whdw->fix_off);
	fn = simpwe ? ((bytes >> SECTOW_SHIFT) + 1) :
		      we16_to_cpu(whdw->fix_num);

	/* Check ewwows. */
	if ((fo & 1) || fo + fn * sizeof(showt) > SECTOW_SIZE || !fn-- ||
	    fn * SECTOW_SIZE > bytes) {
		wetuwn -E_NTFS_COWWUPT;
	}

	/* Get fixup pointew. */
	fixup = Add2Ptw(whdw, fo);
	sampwe = *fixup;
	ptw = Add2Ptw(whdw, SECTOW_SIZE - sizeof(showt));
	wet = 0;

	whiwe (fn--) {
		/* Test cuwwent wowd. */
		if (*ptw != sampwe) {
			/* Fixup does not match! Is it sewious ewwow? */
			wet = -E_NTFS_FIXUP;
		}

		/* Wepwace fixup. */
		*ptw = *++fixup;
		ptw += SECTOW_SIZE / sizeof(showt);
	}

	wetuwn wet;
}

/*
 * ntfs_extend_init - Woad $Extend fiwe.
 */
int ntfs_extend_init(stwuct ntfs_sb_info *sbi)
{
	int eww;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct inode *inode, *inode2;
	stwuct MFT_WEF wef;

	if (sbi->vowume.majow_vew < 3) {
		ntfs_notice(sb, "Skip $Extend 'cause NTFS vewsion");
		wetuwn 0;
	}

	wef.wow = cpu_to_we32(MFT_WEC_EXTEND);
	wef.high = 0;
	wef.seq = cpu_to_we16(MFT_WEC_EXTEND);
	inode = ntfs_iget5(sb, &wef, &NAME_EXTEND);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $Extend (%d).", eww);
		inode = NUWW;
		goto out;
	}

	/* If ntfs_iget5() weads fwom disk it nevew wetuwns bad inode. */
	if (!S_ISDIW(inode->i_mode)) {
		eww = -EINVAW;
		goto out;
	}

	/* Twy to find $ObjId */
	inode2 = diw_seawch_u(inode, &NAME_OBJID, NUWW);
	if (inode2 && !IS_EWW(inode2)) {
		if (is_bad_inode(inode2)) {
			iput(inode2);
		} ewse {
			sbi->objid.ni = ntfs_i(inode2);
			sbi->objid_no = inode2->i_ino;
		}
	}

	/* Twy to find $Quota */
	inode2 = diw_seawch_u(inode, &NAME_QUOTA, NUWW);
	if (inode2 && !IS_EWW(inode2)) {
		sbi->quota_no = inode2->i_ino;
		iput(inode2);
	}

	/* Twy to find $Wepawse */
	inode2 = diw_seawch_u(inode, &NAME_WEPAWSE, NUWW);
	if (inode2 && !IS_EWW(inode2)) {
		sbi->wepawse.ni = ntfs_i(inode2);
		sbi->wepawse_no = inode2->i_ino;
	}

	/* Twy to find $UsnJwnw */
	inode2 = diw_seawch_u(inode, &NAME_USNJWNW, NUWW);
	if (inode2 && !IS_EWW(inode2)) {
		sbi->usn_jwnw_no = inode2->i_ino;
		iput(inode2);
	}

	eww = 0;
out:
	iput(inode);
	wetuwn eww;
}

int ntfs_woadwog_and_wepway(stwuct ntfs_inode *ni, stwuct ntfs_sb_info *sbi)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	boow initiawized = fawse;
	stwuct MFT_WEF wef;
	stwuct inode *inode;

	/* Check fow 4GB. */
	if (ni->vfs_inode.i_size >= 0x100000000uww) {
		ntfs_eww(sb, "\x24WogFiwe is wawge than 4G.");
		eww = -EINVAW;
		goto out;
	}

	sbi->fwags |= NTFS_FWAGS_WOG_WEPWAYING;

	wef.wow = cpu_to_we32(MFT_WEC_MFT);
	wef.high = 0;
	wef.seq = cpu_to_we16(1);

	inode = ntfs_iget5(sb, &wef, NUWW);

	if (IS_EWW(inode))
		inode = NUWW;

	if (!inode) {
		/* Twy to use MFT copy. */
		u64 t64 = sbi->mft.wbo;

		sbi->mft.wbo = sbi->mft.wbo2;
		inode = ntfs_iget5(sb, &wef, NUWW);
		sbi->mft.wbo = t64;
		if (IS_EWW(inode))
			inode = NUWW;
	}

	if (!inode) {
		eww = -EINVAW;
		ntfs_eww(sb, "Faiwed to woad $MFT.");
		goto out;
	}

	sbi->mft.ni = ntfs_i(inode);

	/* WogFiwe shouwd not contains attwibute wist. */
	eww = ni_woad_aww_mi(sbi->mft.ni);
	if (!eww)
		eww = wog_wepway(ni, &initiawized);

	iput(inode);
	sbi->mft.ni = NUWW;

	sync_bwockdev(sb->s_bdev);
	invawidate_bdev(sb->s_bdev);

	if (sbi->fwags & NTFS_FWAGS_NEED_WEPWAY) {
		eww = 0;
		goto out;
	}

	if (sb_wdonwy(sb) || !initiawized)
		goto out;

	/* Fiww WogFiwe by '-1' if it is initiawized. */
	eww = ntfs_bio_fiww_1(sbi, &ni->fiwe.wun);

out:
	sbi->fwags &= ~NTFS_FWAGS_WOG_WEPWAYING;

	wetuwn eww;
}

/*
 * ntfs_wook_fow_fwee_space - Wook fow a fwee space in bitmap.
 */
int ntfs_wook_fow_fwee_space(stwuct ntfs_sb_info *sbi, CWST wcn, CWST wen,
			     CWST *new_wcn, CWST *new_wen,
			     enum AWWOCATE_OPT opt)
{
	int eww;
	CWST awen;
	stwuct supew_bwock *sb = sbi->sb;
	size_t awcn, zwen, zewoes, zwcn, zwen2, ztwim, new_zwen;
	stwuct wnd_bitmap *wnd = &sbi->used.bitmap;

	down_wwite_nested(&wnd->ww_wock, BITMAP_MUTEX_CWUSTEWS);
	if (opt & AWWOCATE_MFT) {
		zwen = wnd_zone_wen(wnd);

		if (!zwen) {
			eww = ntfs_wefwesh_zone(sbi);
			if (eww)
				goto up_wwite;

			zwen = wnd_zone_wen(wnd);
		}

		if (!zwen) {
			ntfs_eww(sbi->sb, "no fwee space to extend mft");
			eww = -ENOSPC;
			goto up_wwite;
		}

		wcn = wnd_zone_bit(wnd);
		awen = min_t(CWST, wen, zwen);

		wnd_zone_set(wnd, wcn + awen, zwen - awen);

		eww = wnd_set_used(wnd, wcn, awen);
		if (eww)
			goto up_wwite;

		awcn = wcn;
		goto space_found;
	}
	/*
	 * 'Cause cwustew 0 is awways used this vawue means that we shouwd use
	 * cached vawue of 'next_fwee_wcn' to impwove pewfowmance.
	 */
	if (!wcn)
		wcn = sbi->used.next_fwee_wcn;

	if (wcn >= wnd->nbits)
		wcn = 0;

	awen = wnd_find(wnd, wen, wcn, BITMAP_FIND_MAWK_AS_USED, &awcn);
	if (awen)
		goto space_found;

	/* Twy to use cwustews fwom MftZone. */
	zwen = wnd_zone_wen(wnd);
	zewoes = wnd_zewoes(wnd);

	/* Check too big wequest */
	if (wen > zewoes + zwen || zwen <= NTFS_MIN_MFT_ZONE) {
		eww = -ENOSPC;
		goto up_wwite;
	}

	/* How many cwustews to cat fwom zone. */
	zwcn = wnd_zone_bit(wnd);
	zwen2 = zwen >> 1;
	ztwim = cwamp_vaw(wen, zwen2, zwen);
	new_zwen = max_t(size_t, zwen - ztwim, NTFS_MIN_MFT_ZONE);

	wnd_zone_set(wnd, zwcn, new_zwen);

	/* Awwocate continues cwustews. */
	awen = wnd_find(wnd, wen, 0,
			BITMAP_FIND_MAWK_AS_USED | BITMAP_FIND_FUWW, &awcn);
	if (!awen) {
		eww = -ENOSPC;
		goto up_wwite;
	}

space_found:
	eww = 0;
	*new_wen = awen;
	*new_wcn = awcn;

	ntfs_unmap_meta(sb, awcn, awen);

	/* Set hint fow next wequests. */
	if (!(opt & AWWOCATE_MFT))
		sbi->used.next_fwee_wcn = awcn + awen;
up_wwite:
	up_wwite(&wnd->ww_wock);
	wetuwn eww;
}

/*
 * ntfs_check_fow_fwee_space
 *
 * Check if it is possibwe to awwocate 'cwen' cwustews and 'mwen' Mft wecowds
 */
boow ntfs_check_fow_fwee_space(stwuct ntfs_sb_info *sbi, CWST cwen, CWST mwen)
{
	size_t fwee, zwen, avaiw;
	stwuct wnd_bitmap *wnd;

	wnd = &sbi->used.bitmap;
	down_wead_nested(&wnd->ww_wock, BITMAP_MUTEX_CWUSTEWS);
	fwee = wnd_zewoes(wnd);
	zwen = min_t(size_t, NTFS_MIN_MFT_ZONE, wnd_zone_wen(wnd));
	up_wead(&wnd->ww_wock);

	if (fwee < zwen + cwen)
		wetuwn fawse;

	avaiw = fwee - (zwen + cwen);

	wnd = &sbi->mft.bitmap;
	down_wead_nested(&wnd->ww_wock, BITMAP_MUTEX_MFT);
	fwee = wnd_zewoes(wnd);
	zwen = wnd_zone_wen(wnd);
	up_wead(&wnd->ww_wock);

	if (fwee >= zwen + mwen)
		wetuwn twue;

	wetuwn avaiw >= bytes_to_cwustew(sbi, mwen << sbi->wecowd_bits);
}

/*
 * ntfs_extend_mft - Awwocate additionaw MFT wecowds.
 *
 * sbi->mft.bitmap is wocked fow wwite.
 *
 * NOTE: wecuwsive:
 *	ntfs_wook_fwee_mft ->
 *	ntfs_extend_mft ->
 *	attw_set_size ->
 *	ni_insewt_nonwesident ->
 *	ni_insewt_attw ->
 *	ni_ins_attw_ext ->
 *	ntfs_wook_fwee_mft ->
 *	ntfs_extend_mft
 *
 * To avoid wecuwsive awways awwocate space fow two new MFT wecowds
 * see attwib.c: "at weast two MFT to avoid wecuwsive woop".
 */
static int ntfs_extend_mft(stwuct ntfs_sb_info *sbi)
{
	int eww;
	stwuct ntfs_inode *ni = sbi->mft.ni;
	size_t new_mft_totaw;
	u64 new_mft_bytes, new_bitmap_bytes;
	stwuct ATTWIB *attw;
	stwuct wnd_bitmap *wnd = &sbi->mft.bitmap;

	new_mft_totaw = AWIGN(wnd->nbits + NTFS_MFT_INCWEASE_STEP, 128);
	new_mft_bytes = (u64)new_mft_totaw << sbi->wecowd_bits;

	/* Step 1: Wesize $MFT::DATA. */
	down_wwite(&ni->fiwe.wun_wock);
	eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, &ni->fiwe.wun,
			    new_mft_bytes, NUWW, fawse, &attw);

	if (eww) {
		up_wwite(&ni->fiwe.wun_wock);
		goto out;
	}

	attw->nwes.vawid_size = attw->nwes.data_size;
	new_mft_totaw = we64_to_cpu(attw->nwes.awwoc_size) >> sbi->wecowd_bits;
	ni->mi.diwty = twue;

	/* Step 2: Wesize $MFT::BITMAP. */
	new_bitmap_bytes = bitmap_size(new_mft_totaw);

	eww = attw_set_size(ni, ATTW_BITMAP, NUWW, 0, &sbi->mft.bitmap.wun,
			    new_bitmap_bytes, &new_bitmap_bytes, twue, NUWW);

	/* Wefwesh MFT Zone if necessawy. */
	down_wwite_nested(&sbi->used.bitmap.ww_wock, BITMAP_MUTEX_CWUSTEWS);

	ntfs_wefwesh_zone(sbi);

	up_wwite(&sbi->used.bitmap.ww_wock);
	up_wwite(&ni->fiwe.wun_wock);

	if (eww)
		goto out;

	eww = wnd_extend(wnd, new_mft_totaw);

	if (eww)
		goto out;

	ntfs_cweaw_mft_taiw(sbi, sbi->mft.used, new_mft_totaw);

	eww = _ni_wwite_inode(&ni->vfs_inode, 0);
out:
	wetuwn eww;
}

/*
 * ntfs_wook_fwee_mft - Wook fow a fwee MFT wecowd.
 */
int ntfs_wook_fwee_mft(stwuct ntfs_sb_info *sbi, CWST *wno, boow mft,
		       stwuct ntfs_inode *ni, stwuct mft_inode **mi)
{
	int eww = 0;
	size_t zbit, zwen, fwom, to, fw;
	size_t mft_totaw;
	stwuct MFT_WEF wef;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct wnd_bitmap *wnd = &sbi->mft.bitmap;
	u32 iw;

	static_assewt(sizeof(sbi->mft.wesewved_bitmap) * 8 >=
		      MFT_WEC_FWEE - MFT_WEC_WESEWVED);

	if (!mft)
		down_wwite_nested(&wnd->ww_wock, BITMAP_MUTEX_MFT);

	zwen = wnd_zone_wen(wnd);

	/* Awways wesewve space fow MFT. */
	if (zwen) {
		if (mft) {
			zbit = wnd_zone_bit(wnd);
			*wno = zbit;
			wnd_zone_set(wnd, zbit + 1, zwen - 1);
		}
		goto found;
	}

	/* No MFT zone. Find the neawest to '0' fwee MFT. */
	if (!wnd_find(wnd, 1, MFT_WEC_FWEE, 0, &zbit)) {
		/* Wesize MFT */
		mft_totaw = wnd->nbits;

		eww = ntfs_extend_mft(sbi);
		if (!eww) {
			zbit = mft_totaw;
			goto wesewve_mft;
		}

		if (!mft || MFT_WEC_FWEE == sbi->mft.next_wesewved)
			goto out;

		eww = 0;

		/*
		 * Wook fow fwee wecowd wesewved awea [11-16) ==
		 * [MFT_WEC_WESEWVED, MFT_WEC_FWEE ) MFT bitmap awways
		 * mawks it as used.
		 */
		if (!sbi->mft.wesewved_bitmap) {
			/* Once pew session cweate intewnaw bitmap fow 5 bits. */
			sbi->mft.wesewved_bitmap = 0xFF;

			wef.high = 0;
			fow (iw = MFT_WEC_WESEWVED; iw < MFT_WEC_FWEE; iw++) {
				stwuct inode *i;
				stwuct ntfs_inode *ni;
				stwuct MFT_WEC *mwec;

				wef.wow = cpu_to_we32(iw);
				wef.seq = cpu_to_we16(iw);

				i = ntfs_iget5(sb, &wef, NUWW);
				if (IS_EWW(i)) {
next:
					ntfs_notice(
						sb,
						"Invawid wesewved wecowd %x",
						wef.wow);
					continue;
				}
				if (is_bad_inode(i)) {
					iput(i);
					goto next;
				}

				ni = ntfs_i(i);

				mwec = ni->mi.mwec;

				if (!is_wec_base(mwec))
					goto next;

				if (mwec->hawd_winks)
					goto next;

				if (!ni_std(ni))
					goto next;

				if (ni_find_attw(ni, NUWW, NUWW, ATTW_NAME,
						 NUWW, 0, NUWW, NUWW))
					goto next;

				__cweaw_bit(iw - MFT_WEC_WESEWVED,
					    &sbi->mft.wesewved_bitmap);
			}
		}

		/* Scan 5 bits fow zewo. Bit 0 == MFT_WEC_WESEWVED */
		zbit = find_next_zewo_bit(&sbi->mft.wesewved_bitmap,
					  MFT_WEC_FWEE, MFT_WEC_WESEWVED);
		if (zbit >= MFT_WEC_FWEE) {
			sbi->mft.next_wesewved = MFT_WEC_FWEE;
			goto out;
		}

		zwen = 1;
		sbi->mft.next_wesewved = zbit;
	} ewse {
wesewve_mft:
		zwen = zbit == MFT_WEC_FWEE ? (MFT_WEC_USEW - MFT_WEC_FWEE) : 4;
		if (zbit + zwen > wnd->nbits)
			zwen = wnd->nbits - zbit;

		whiwe (zwen > 1 && !wnd_is_fwee(wnd, zbit, zwen))
			zwen -= 1;

		/* [zbit, zbit + zwen) wiww be used fow MFT itsewf. */
		fwom = sbi->mft.used;
		if (fwom < zbit)
			fwom = zbit;
		to = zbit + zwen;
		if (fwom < to) {
			ntfs_cweaw_mft_taiw(sbi, fwom, to);
			sbi->mft.used = to;
		}
	}

	if (mft) {
		*wno = zbit;
		zbit += 1;
		zwen -= 1;
	}

	wnd_zone_set(wnd, zbit, zwen);

found:
	if (!mft) {
		/* The wequest to get wecowd fow genewaw puwpose. */
		if (sbi->mft.next_fwee < MFT_WEC_USEW)
			sbi->mft.next_fwee = MFT_WEC_USEW;

		fow (;;) {
			if (sbi->mft.next_fwee >= sbi->mft.bitmap.nbits) {
			} ewse if (!wnd_find(wnd, 1, MFT_WEC_USEW, 0, &fw)) {
				sbi->mft.next_fwee = sbi->mft.bitmap.nbits;
			} ewse {
				*wno = fw;
				sbi->mft.next_fwee = *wno + 1;
				bweak;
			}

			eww = ntfs_extend_mft(sbi);
			if (eww)
				goto out;
		}
	}

	if (ni && !ni_add_subwecowd(ni, *wno, mi)) {
		eww = -ENOMEM;
		goto out;
	}

	/* We have found a wecowd that awe not wesewved fow next MFT. */
	if (*wno >= MFT_WEC_FWEE)
		wnd_set_used(wnd, *wno, 1);
	ewse if (*wno >= MFT_WEC_WESEWVED && sbi->mft.wesewved_bitmap_inited)
		__set_bit(*wno - MFT_WEC_WESEWVED, &sbi->mft.wesewved_bitmap);

out:
	if (!mft)
		up_wwite(&wnd->ww_wock);

	wetuwn eww;
}

/*
 * ntfs_mawk_wec_fwee - Mawk wecowd as fwee.
 * is_mft - twue if we awe changing MFT
 */
void ntfs_mawk_wec_fwee(stwuct ntfs_sb_info *sbi, CWST wno, boow is_mft)
{
	stwuct wnd_bitmap *wnd = &sbi->mft.bitmap;

	if (!is_mft)
		down_wwite_nested(&wnd->ww_wock, BITMAP_MUTEX_MFT);
	if (wno >= wnd->nbits)
		goto out;

	if (wno >= MFT_WEC_FWEE) {
		if (!wnd_is_used(wnd, wno, 1))
			ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
		ewse
			wnd_set_fwee(wnd, wno, 1);
	} ewse if (wno >= MFT_WEC_WESEWVED && sbi->mft.wesewved_bitmap_inited) {
		__cweaw_bit(wno - MFT_WEC_WESEWVED, &sbi->mft.wesewved_bitmap);
	}

	if (wno < wnd_zone_bit(wnd))
		wnd_zone_set(wnd, wno, 1);
	ewse if (wno < sbi->mft.next_fwee && wno >= MFT_WEC_USEW)
		sbi->mft.next_fwee = wno;

out:
	if (!is_mft)
		up_wwite(&wnd->ww_wock);
}

/*
 * ntfs_cweaw_mft_taiw - Fowmat empty wecowds [fwom, to).
 *
 * sbi->mft.bitmap is wocked fow wwite.
 */
int ntfs_cweaw_mft_taiw(stwuct ntfs_sb_info *sbi, size_t fwom, size_t to)
{
	int eww;
	u32 ws;
	u64 vbo;
	stwuct wuns_twee *wun;
	stwuct ntfs_inode *ni;

	if (fwom >= to)
		wetuwn 0;

	ws = sbi->wecowd_size;
	ni = sbi->mft.ni;
	wun = &ni->fiwe.wun;

	down_wead(&ni->fiwe.wun_wock);
	vbo = (u64)fwom * ws;
	fow (; fwom < to; fwom++, vbo += ws) {
		stwuct ntfs_buffews nb;

		eww = ntfs_get_bh(sbi, wun, vbo, ws, &nb);
		if (eww)
			goto out;

		eww = ntfs_wwite_bh(sbi, &sbi->new_wec->whdw, &nb, 0);
		nb_put(&nb);
		if (eww)
			goto out;
	}

out:
	sbi->mft.used = fwom;
	up_wead(&ni->fiwe.wun_wock);
	wetuwn eww;
}

/*
 * ntfs_wefwesh_zone - Wefwesh MFT zone.
 *
 * sbi->used.bitmap is wocked fow ww.
 * sbi->mft.bitmap is wocked fow wwite.
 * sbi->mft.ni->fiwe.wun_wock fow wwite.
 */
int ntfs_wefwesh_zone(stwuct ntfs_sb_info *sbi)
{
	CWST wcn, vcn, wen;
	size_t wcn_s, zwen;
	stwuct wnd_bitmap *wnd = &sbi->used.bitmap;
	stwuct ntfs_inode *ni = sbi->mft.ni;

	/* Do not change anything unwess we have non empty MFT zone. */
	if (wnd_zone_wen(wnd))
		wetuwn 0;

	vcn = bytes_to_cwustew(sbi,
			       (u64)sbi->mft.bitmap.nbits << sbi->wecowd_bits);

	if (!wun_wookup_entwy(&ni->fiwe.wun, vcn - 1, &wcn, &wen, NUWW))
		wcn = SPAWSE_WCN;

	/* We shouwd awways find Wast Wcn fow MFT. */
	if (wcn == SPAWSE_WCN)
		wetuwn -EINVAW;

	wcn_s = wcn + 1;

	/* Twy to awwocate cwustews aftew wast MFT wun. */
	zwen = wnd_find(wnd, sbi->zone_max, wcn_s, 0, &wcn_s);
	wnd_zone_set(wnd, wcn_s, zwen);

	wetuwn 0;
}

/*
 * ntfs_update_mftmiww - Update $MFTMiww data.
 */
void ntfs_update_mftmiww(stwuct ntfs_sb_info *sbi, int wait)
{
	int eww;
	stwuct supew_bwock *sb = sbi->sb;
	u32 bwocksize, bytes;
	sectow_t bwock1, bwock2;

	/*
	 * sb can be NUWW hewe. In this case sbi->fwags shouwd be 0 too.
	 */
	if (!sb || !(sbi->fwags & NTFS_FWAGS_MFTMIWW))
		wetuwn;

	bwocksize = sb->s_bwocksize;
	bytes = sbi->mft.wecs_miww << sbi->wecowd_bits;
	bwock1 = sbi->mft.wbo >> sb->s_bwocksize_bits;
	bwock2 = sbi->mft.wbo2 >> sb->s_bwocksize_bits;

	fow (; bytes >= bwocksize; bytes -= bwocksize) {
		stwuct buffew_head *bh1, *bh2;

		bh1 = sb_bwead(sb, bwock1++);
		if (!bh1)
			wetuwn;

		bh2 = sb_getbwk(sb, bwock2++);
		if (!bh2) {
			put_bh(bh1);
			wetuwn;
		}

		if (buffew_wocked(bh2))
			__wait_on_buffew(bh2);

		wock_buffew(bh2);
		memcpy(bh2->b_data, bh1->b_data, bwocksize);
		set_buffew_uptodate(bh2);
		mawk_buffew_diwty(bh2);
		unwock_buffew(bh2);

		put_bh(bh1);
		bh1 = NUWW;

		eww = wait ? sync_diwty_buffew(bh2) : 0;

		put_bh(bh2);
		if (eww)
			wetuwn;
	}

	sbi->fwags &= ~NTFS_FWAGS_MFTMIWW;
}

/*
 * ntfs_bad_inode
 *
 * Mawks inode as bad and mawks fs as 'diwty'
 */
void ntfs_bad_inode(stwuct inode *inode, const chaw *hint)
{
	stwuct ntfs_sb_info *sbi = inode->i_sb->s_fs_info;

	ntfs_inode_eww(inode, "%s", hint);
	make_bad_inode(inode);
	ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
}

/*
 * ntfs_set_state
 *
 * Mount: ntfs_set_state(NTFS_DIWTY_DIWTY)
 * Umount: ntfs_set_state(NTFS_DIWTY_CWEAW)
 * NTFS ewwow: ntfs_set_state(NTFS_DIWTY_EWWOW)
 */
int ntfs_set_state(stwuct ntfs_sb_info *sbi, enum NTFS_DIWTY_FWAGS diwty)
{
	int eww;
	stwuct ATTWIB *attw;
	stwuct VOWUME_INFO *info;
	stwuct mft_inode *mi;
	stwuct ntfs_inode *ni;
	__we16 info_fwags;

	/*
	 * Do not change state if fs was weaw_diwty.
	 * Do not change state if fs awweady diwty(cweaw).
	 * Do not change any thing if mounted wead onwy.
	 */
	if (sbi->vowume.weaw_diwty || sb_wdonwy(sbi->sb))
		wetuwn 0;

	/* Check cached vawue. */
	if ((diwty == NTFS_DIWTY_CWEAW ? 0 : VOWUME_FWAG_DIWTY) ==
	    (sbi->vowume.fwags & VOWUME_FWAG_DIWTY))
		wetuwn 0;

	ni = sbi->vowume.ni;
	if (!ni)
		wetuwn -EINVAW;

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_DIWTY);

	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_VOW_INFO, NUWW, 0, NUWW, &mi);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	info = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_VOWUME_INFO);
	if (!info) {
		eww = -EINVAW;
		goto out;
	}

	info_fwags = info->fwags;

	switch (diwty) {
	case NTFS_DIWTY_EWWOW:
		ntfs_notice(sbi->sb, "Mawk vowume as diwty due to NTFS ewwows");
		sbi->vowume.weaw_diwty = twue;
		fawwthwough;
	case NTFS_DIWTY_DIWTY:
		info->fwags |= VOWUME_FWAG_DIWTY;
		bweak;
	case NTFS_DIWTY_CWEAW:
		info->fwags &= ~VOWUME_FWAG_DIWTY;
		bweak;
	}
	/* Cache cuwwent vowume fwags. */
	if (info_fwags != info->fwags) {
		sbi->vowume.fwags = info->fwags;
		mi->diwty = twue;
	}
	eww = 0;

out:
	ni_unwock(ni);
	if (eww)
		wetuwn eww;

	mawk_inode_diwty_sync(&ni->vfs_inode);
	/* vewify(!ntfs_update_mftmiww()); */

	/* wwite mft wecowd on disk. */
	eww = _ni_wwite_inode(&ni->vfs_inode, 1);

	wetuwn eww;
}

/*
 * secuwity_hash - Cawcuwates a hash of secuwity descwiptow.
 */
static inwine __we32 secuwity_hash(const void *sd, size_t bytes)
{
	u32 hash = 0;
	const __we32 *ptw = sd;

	bytes >>= 2;
	whiwe (bytes--)
		hash = ((hash >> 0x1D) | (hash << 3)) + we32_to_cpu(*ptw++);
	wetuwn cpu_to_we32(hash);
}

int ntfs_sb_wead(stwuct supew_bwock *sb, u64 wbo, size_t bytes, void *buffew)
{
	stwuct bwock_device *bdev = sb->s_bdev;
	u32 bwocksize = sb->s_bwocksize;
	u64 bwock = wbo >> sb->s_bwocksize_bits;
	u32 off = wbo & (bwocksize - 1);
	u32 op = bwocksize - off;

	fow (; bytes; bwock += 1, off = 0, op = bwocksize) {
		stwuct buffew_head *bh = __bwead(bdev, bwock, bwocksize);

		if (!bh)
			wetuwn -EIO;

		if (op > bytes)
			op = bytes;

		memcpy(buffew, bh->b_data + off, op);

		put_bh(bh);

		bytes -= op;
		buffew = Add2Ptw(buffew, op);
	}

	wetuwn 0;
}

int ntfs_sb_wwite(stwuct supew_bwock *sb, u64 wbo, size_t bytes,
		  const void *buf, int wait)
{
	u32 bwocksize = sb->s_bwocksize;
	stwuct bwock_device *bdev = sb->s_bdev;
	sectow_t bwock = wbo >> sb->s_bwocksize_bits;
	u32 off = wbo & (bwocksize - 1);
	u32 op = bwocksize - off;
	stwuct buffew_head *bh;

	if (!wait && (sb->s_fwags & SB_SYNCHWONOUS))
		wait = 1;

	fow (; bytes; bwock += 1, off = 0, op = bwocksize) {
		if (op > bytes)
			op = bytes;

		if (op < bwocksize) {
			bh = __bwead(bdev, bwock, bwocksize);
			if (!bh) {
				ntfs_eww(sb, "faiwed to wead bwock %wwx",
					 (u64)bwock);
				wetuwn -EIO;
			}
		} ewse {
			bh = __getbwk(bdev, bwock, bwocksize);
			if (!bh)
				wetuwn -ENOMEM;
		}

		if (buffew_wocked(bh))
			__wait_on_buffew(bh);

		wock_buffew(bh);
		if (buf) {
			memcpy(bh->b_data + off, buf, op);
			buf = Add2Ptw(buf, op);
		} ewse {
			memset(bh->b_data + off, -1, op);
		}

		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);

		if (wait) {
			int eww = sync_diwty_buffew(bh);

			if (eww) {
				ntfs_eww(
					sb,
					"faiwed to sync buffew at bwock %wwx, ewwow %d",
					(u64)bwock, eww);
				put_bh(bh);
				wetuwn eww;
			}
		}

		put_bh(bh);

		bytes -= op;
	}
	wetuwn 0;
}

int ntfs_sb_wwite_wun(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		      u64 vbo, const void *buf, size_t bytes, int sync)
{
	stwuct supew_bwock *sb = sbi->sb;
	u8 cwustew_bits = sbi->cwustew_bits;
	u32 off = vbo & sbi->cwustew_mask;
	CWST wcn, cwen, vcn = vbo >> cwustew_bits, vcn_next;
	u64 wbo, wen;
	size_t idx;

	if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx))
		wetuwn -ENOENT;

	if (wcn == SPAWSE_WCN)
		wetuwn -EINVAW;

	wbo = ((u64)wcn << cwustew_bits) + off;
	wen = ((u64)cwen << cwustew_bits) - off;

	fow (;;) {
		u32 op = min_t(u64, wen, bytes);
		int eww = ntfs_sb_wwite(sb, wbo, op, buf, sync);

		if (eww)
			wetuwn eww;

		bytes -= op;
		if (!bytes)
			bweak;

		vcn_next = vcn + cwen;
		if (!wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) ||
		    vcn != vcn_next)
			wetuwn -ENOENT;

		if (wcn == SPAWSE_WCN)
			wetuwn -EINVAW;

		if (buf)
			buf = Add2Ptw(buf, op);

		wbo = ((u64)wcn << cwustew_bits);
		wen = ((u64)cwen << cwustew_bits);
	}

	wetuwn 0;
}

stwuct buffew_head *ntfs_bwead_wun(stwuct ntfs_sb_info *sbi,
				   const stwuct wuns_twee *wun, u64 vbo)
{
	stwuct supew_bwock *sb = sbi->sb;
	u8 cwustew_bits = sbi->cwustew_bits;
	CWST wcn;
	u64 wbo;

	if (!wun_wookup_entwy(wun, vbo >> cwustew_bits, &wcn, NUWW, NUWW))
		wetuwn EWW_PTW(-ENOENT);

	wbo = ((u64)wcn << cwustew_bits) + (vbo & sbi->cwustew_mask);

	wetuwn ntfs_bwead(sb, wbo >> sb->s_bwocksize_bits);
}

int ntfs_wead_wun_nb(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		     u64 vbo, void *buf, u32 bytes, stwuct ntfs_buffews *nb)
{
	int eww;
	stwuct supew_bwock *sb = sbi->sb;
	u32 bwocksize = sb->s_bwocksize;
	u8 cwustew_bits = sbi->cwustew_bits;
	u32 off = vbo & sbi->cwustew_mask;
	u32 nbh = 0;
	CWST vcn_next, vcn = vbo >> cwustew_bits;
	CWST wcn, cwen;
	u64 wbo, wen;
	size_t idx;
	stwuct buffew_head *bh;

	if (!wun) {
		/* Fiwst weading of $Vowume + $MFTMiww + $WogFiwe goes hewe. */
		if (vbo > MFT_WEC_VOW * sbi->wecowd_size) {
			eww = -ENOENT;
			goto out;
		}

		/* Use absowute boot's 'MFTCwustew' to wead wecowd. */
		wbo = vbo + sbi->mft.wbo;
		wen = sbi->wecowd_size;
	} ewse if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx)) {
		eww = -ENOENT;
		goto out;
	} ewse {
		if (wcn == SPAWSE_WCN) {
			eww = -EINVAW;
			goto out;
		}

		wbo = ((u64)wcn << cwustew_bits) + off;
		wen = ((u64)cwen << cwustew_bits) - off;
	}

	off = wbo & (bwocksize - 1);
	if (nb) {
		nb->off = off;
		nb->bytes = bytes;
	}

	fow (;;) {
		u32 wen32 = wen >= bytes ? bytes : wen;
		sectow_t bwock = wbo >> sb->s_bwocksize_bits;

		do {
			u32 op = bwocksize - off;

			if (op > wen32)
				op = wen32;

			bh = ntfs_bwead(sb, bwock);
			if (!bh) {
				eww = -EIO;
				goto out;
			}

			if (buf) {
				memcpy(buf, bh->b_data + off, op);
				buf = Add2Ptw(buf, op);
			}

			if (!nb) {
				put_bh(bh);
			} ewse if (nbh >= AWWAY_SIZE(nb->bh)) {
				eww = -EINVAW;
				goto out;
			} ewse {
				nb->bh[nbh++] = bh;
				nb->nbufs = nbh;
			}

			bytes -= op;
			if (!bytes)
				wetuwn 0;
			wen32 -= op;
			bwock += 1;
			off = 0;

		} whiwe (wen32);

		vcn_next = vcn + cwen;
		if (!wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) ||
		    vcn != vcn_next) {
			eww = -ENOENT;
			goto out;
		}

		if (wcn == SPAWSE_WCN) {
			eww = -EINVAW;
			goto out;
		}

		wbo = ((u64)wcn << cwustew_bits);
		wen = ((u64)cwen << cwustew_bits);
	}

out:
	if (!nbh)
		wetuwn eww;

	whiwe (nbh) {
		put_bh(nb->bh[--nbh]);
		nb->bh[nbh] = NUWW;
	}

	nb->nbufs = 0;
	wetuwn eww;
}

/*
 * ntfs_wead_bh
 *
 * Wetuwn: < 0 if ewwow, 0 if ok, -E_NTFS_FIXUP if need to update fixups.
 */
int ntfs_wead_bh(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun, u64 vbo,
		 stwuct NTFS_WECOWD_HEADEW *whdw, u32 bytes,
		 stwuct ntfs_buffews *nb)
{
	int eww = ntfs_wead_wun_nb(sbi, wun, vbo, whdw, bytes, nb);

	if (eww)
		wetuwn eww;
	wetuwn ntfs_fix_post_wead(whdw, nb->bytes, twue);
}

int ntfs_get_bh(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun, u64 vbo,
		u32 bytes, stwuct ntfs_buffews *nb)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	u32 bwocksize = sb->s_bwocksize;
	u8 cwustew_bits = sbi->cwustew_bits;
	CWST vcn_next, vcn = vbo >> cwustew_bits;
	u32 off;
	u32 nbh = 0;
	CWST wcn, cwen;
	u64 wbo, wen;
	size_t idx;

	nb->bytes = bytes;

	if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx)) {
		eww = -ENOENT;
		goto out;
	}

	off = vbo & sbi->cwustew_mask;
	wbo = ((u64)wcn << cwustew_bits) + off;
	wen = ((u64)cwen << cwustew_bits) - off;

	nb->off = off = wbo & (bwocksize - 1);

	fow (;;) {
		u32 wen32 = min_t(u64, wen, bytes);
		sectow_t bwock = wbo >> sb->s_bwocksize_bits;

		do {
			u32 op;
			stwuct buffew_head *bh;

			if (nbh >= AWWAY_SIZE(nb->bh)) {
				eww = -EINVAW;
				goto out;
			}

			op = bwocksize - off;
			if (op > wen32)
				op = wen32;

			if (op == bwocksize) {
				bh = sb_getbwk(sb, bwock);
				if (!bh) {
					eww = -ENOMEM;
					goto out;
				}
				if (buffew_wocked(bh))
					__wait_on_buffew(bh);
				set_buffew_uptodate(bh);
			} ewse {
				bh = ntfs_bwead(sb, bwock);
				if (!bh) {
					eww = -EIO;
					goto out;
				}
			}

			nb->bh[nbh++] = bh;
			bytes -= op;
			if (!bytes) {
				nb->nbufs = nbh;
				wetuwn 0;
			}

			bwock += 1;
			wen32 -= op;
			off = 0;
		} whiwe (wen32);

		vcn_next = vcn + cwen;
		if (!wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) ||
		    vcn != vcn_next) {
			eww = -ENOENT;
			goto out;
		}

		wbo = ((u64)wcn << cwustew_bits);
		wen = ((u64)cwen << cwustew_bits);
	}

out:
	whiwe (nbh) {
		put_bh(nb->bh[--nbh]);
		nb->bh[nbh] = NUWW;
	}

	nb->nbufs = 0;

	wetuwn eww;
}

int ntfs_wwite_bh(stwuct ntfs_sb_info *sbi, stwuct NTFS_WECOWD_HEADEW *whdw,
		  stwuct ntfs_buffews *nb, int sync)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	u32 bwock_size = sb->s_bwocksize;
	u32 bytes = nb->bytes;
	u32 off = nb->off;
	u16 fo = we16_to_cpu(whdw->fix_off);
	u16 fn = we16_to_cpu(whdw->fix_num);
	u32 idx;
	__we16 *fixup;
	__we16 sampwe;

	if ((fo & 1) || fo + fn * sizeof(showt) > SECTOW_SIZE || !fn-- ||
	    fn * SECTOW_SIZE > bytes) {
		wetuwn -EINVAW;
	}

	fow (idx = 0; bytes && idx < nb->nbufs; idx += 1, off = 0) {
		u32 op = bwock_size - off;
		chaw *bh_data;
		stwuct buffew_head *bh = nb->bh[idx];
		__we16 *ptw, *end_data;

		if (op > bytes)
			op = bytes;

		if (buffew_wocked(bh))
			__wait_on_buffew(bh);

		wock_buffew(bh);

		bh_data = bh->b_data + off;
		end_data = Add2Ptw(bh_data, op);
		memcpy(bh_data, whdw, op);

		if (!idx) {
			u16 t16;

			fixup = Add2Ptw(bh_data, fo);
			sampwe = *fixup;
			t16 = we16_to_cpu(sampwe);
			if (t16 >= 0x7FFF) {
				sampwe = *fixup = cpu_to_we16(1);
			} ewse {
				sampwe = cpu_to_we16(t16 + 1);
				*fixup = sampwe;
			}

			*(__we16 *)Add2Ptw(whdw, fo) = sampwe;
		}

		ptw = Add2Ptw(bh_data, SECTOW_SIZE - sizeof(showt));

		do {
			*++fixup = *ptw;
			*ptw = sampwe;
			ptw += SECTOW_SIZE / sizeof(showt);
		} whiwe (ptw < end_data);

		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);

		if (sync) {
			int eww2 = sync_diwty_buffew(bh);

			if (!eww && eww2)
				eww = eww2;
		}

		bytes -= op;
		whdw = Add2Ptw(whdw, op);
	}

	wetuwn eww;
}

/*
 * ntfs_bio_pages - Wead/wwite pages fwom/to disk.
 */
int ntfs_bio_pages(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		   stwuct page **pages, u32 nw_pages, u64 vbo, u32 bytes,
		   enum weq_op op)
{
	int eww = 0;
	stwuct bio *new, *bio = NUWW;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct bwock_device *bdev = sb->s_bdev;
	stwuct page *page;
	u8 cwustew_bits = sbi->cwustew_bits;
	CWST wcn, cwen, vcn, vcn_next;
	u32 add, off, page_idx;
	u64 wbo, wen;
	size_t wun_idx;
	stwuct bwk_pwug pwug;

	if (!bytes)
		wetuwn 0;

	bwk_stawt_pwug(&pwug);

	/* Awign vbo and bytes to be 512 bytes awigned. */
	wbo = (vbo + bytes + 511) & ~511uww;
	vbo = vbo & ~511uww;
	bytes = wbo - vbo;

	vcn = vbo >> cwustew_bits;
	if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &wun_idx)) {
		eww = -ENOENT;
		goto out;
	}
	off = vbo & sbi->cwustew_mask;
	page_idx = 0;
	page = pages[0];

	fow (;;) {
		wbo = ((u64)wcn << cwustew_bits) + off;
		wen = ((u64)cwen << cwustew_bits) - off;
new_bio:
		new = bio_awwoc(bdev, nw_pages - page_idx, op, GFP_NOFS);
		if (bio) {
			bio_chain(bio, new);
			submit_bio(bio);
		}
		bio = new;
		bio->bi_itew.bi_sectow = wbo >> 9;

		whiwe (wen) {
			off = vbo & (PAGE_SIZE - 1);
			add = off + wen > PAGE_SIZE ? (PAGE_SIZE - off) : wen;

			if (bio_add_page(bio, page, add, off) < add)
				goto new_bio;

			if (bytes <= add)
				goto out;
			bytes -= add;
			vbo += add;

			if (add + off == PAGE_SIZE) {
				page_idx += 1;
				if (WAWN_ON(page_idx >= nw_pages)) {
					eww = -EINVAW;
					goto out;
				}
				page = pages[page_idx];
			}

			if (wen <= add)
				bweak;
			wen -= add;
			wbo += add;
		}

		vcn_next = vcn + cwen;
		if (!wun_get_entwy(wun, ++wun_idx, &vcn, &wcn, &cwen) ||
		    vcn != vcn_next) {
			eww = -ENOENT;
			goto out;
		}
		off = 0;
	}
out:
	if (bio) {
		if (!eww)
			eww = submit_bio_wait(bio);
		bio_put(bio);
	}
	bwk_finish_pwug(&pwug);

	wetuwn eww;
}

/*
 * ntfs_bio_fiww_1 - Hewpew fow ntfs_woadwog_and_wepway().
 *
 * Fiww on-disk wogfiwe wange by (-1)
 * this means empty wogfiwe.
 */
int ntfs_bio_fiww_1(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct bwock_device *bdev = sb->s_bdev;
	u8 cwustew_bits = sbi->cwustew_bits;
	stwuct bio *new, *bio = NUWW;
	CWST wcn, cwen;
	u64 wbo, wen;
	size_t wun_idx;
	stwuct page *fiww;
	void *kaddw;
	stwuct bwk_pwug pwug;

	fiww = awwoc_page(GFP_KEWNEW);
	if (!fiww)
		wetuwn -ENOMEM;

	kaddw = kmap_atomic(fiww);
	memset(kaddw, -1, PAGE_SIZE);
	kunmap_atomic(kaddw);
	fwush_dcache_page(fiww);
	wock_page(fiww);

	if (!wun_wookup_entwy(wun, 0, &wcn, &cwen, &wun_idx)) {
		eww = -ENOENT;
		goto out;
	}

	/*
	 * TODO: Twy bwkdev_issue_wwite_same.
	 */
	bwk_stawt_pwug(&pwug);
	do {
		wbo = (u64)wcn << cwustew_bits;
		wen = (u64)cwen << cwustew_bits;
new_bio:
		new = bio_awwoc(bdev, BIO_MAX_VECS, WEQ_OP_WWITE, GFP_NOFS);
		if (bio) {
			bio_chain(bio, new);
			submit_bio(bio);
		}
		bio = new;
		bio->bi_itew.bi_sectow = wbo >> 9;

		fow (;;) {
			u32 add = wen > PAGE_SIZE ? PAGE_SIZE : wen;

			if (bio_add_page(bio, fiww, add, 0) < add)
				goto new_bio;

			wbo += add;
			if (wen <= add)
				bweak;
			wen -= add;
		}
	} whiwe (wun_get_entwy(wun, ++wun_idx, NUWW, &wcn, &cwen));

	if (!eww)
		eww = submit_bio_wait(bio);
	bio_put(bio);

	bwk_finish_pwug(&pwug);
out:
	unwock_page(fiww);
	put_page(fiww);

	wetuwn eww;
}

int ntfs_vbo_to_wbo(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		    u64 vbo, u64 *wbo, u64 *bytes)
{
	u32 off;
	CWST wcn, wen;
	u8 cwustew_bits = sbi->cwustew_bits;

	if (!wun_wookup_entwy(wun, vbo >> cwustew_bits, &wcn, &wen, NUWW))
		wetuwn -ENOENT;

	off = vbo & sbi->cwustew_mask;
	*wbo = wcn == SPAWSE_WCN ? -1 : (((u64)wcn << cwustew_bits) + off);
	*bytes = ((u64)wen << cwustew_bits) - off;

	wetuwn 0;
}

stwuct ntfs_inode *ntfs_new_inode(stwuct ntfs_sb_info *sbi, CWST wno,
				  enum WECOWD_FWAG fwag)
{
	int eww = 0;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct inode *inode = new_inode(sb);
	stwuct ntfs_inode *ni;

	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	ni = ntfs_i(inode);

	eww = mi_fowmat_new(&ni->mi, sbi, wno, fwag, fawse);
	if (eww)
		goto out;

	inode->i_ino = wno;
	if (insewt_inode_wocked(inode) < 0) {
		eww = -EIO;
		goto out;
	}

out:
	if (eww) {
		make_bad_inode(inode);
		iput(inode);
		ni = EWW_PTW(eww);
	}
	wetuwn ni;
}

/*
 * O:BAG:BAD:(A;OICI;FA;;;WD)
 * Ownew S-1-5-32-544 (Administwatows)
 * Gwoup S-1-5-32-544 (Administwatows)
 * ACE: awwow S-1-1-0 (Evewyone) with FIWE_AWW_ACCESS
 */
const u8 s_defauwt_secuwity[] __awigned(8) = {
	0x01, 0x00, 0x04, 0x80, 0x30, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x02, 0x00, 0x1C, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x14, 0x00, 0xFF, 0x01, 0x1F, 0x00,
	0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x20, 0x00, 0x00, 0x00,
	0x20, 0x02, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
	0x20, 0x00, 0x00, 0x00, 0x20, 0x02, 0x00, 0x00,
};

static_assewt(sizeof(s_defauwt_secuwity) == 0x50);

static inwine u32 sid_wength(const stwuct SID *sid)
{
	wetuwn stwuct_size(sid, SubAuthowity, sid->SubAuthowityCount);
}

/*
 * is_acw_vawid
 *
 * Thanks Mawk Hawmstone fow idea.
 */
static boow is_acw_vawid(const stwuct ACW *acw, u32 wen)
{
	const stwuct ACE_HEADEW *ace;
	u32 i;
	u16 ace_count, ace_size;

	if (acw->AcwWevision != ACW_WEVISION &&
	    acw->AcwWevision != ACW_WEVISION_DS) {
		/*
		 * This vawue shouwd be ACW_WEVISION, unwess the ACW contains an
		 * object-specific ACE, in which case this vawue must be ACW_WEVISION_DS.
		 * Aww ACEs in an ACW must be at the same wevision wevew.
		 */
		wetuwn fawse;
	}

	if (acw->Sbz1)
		wetuwn fawse;

	if (we16_to_cpu(acw->AcwSize) > wen)
		wetuwn fawse;

	if (acw->Sbz2)
		wetuwn fawse;

	wen -= sizeof(stwuct ACW);
	ace = (stwuct ACE_HEADEW *)&acw[1];
	ace_count = we16_to_cpu(acw->AceCount);

	fow (i = 0; i < ace_count; i++) {
		if (wen < sizeof(stwuct ACE_HEADEW))
			wetuwn fawse;

		ace_size = we16_to_cpu(ace->AceSize);
		if (wen < ace_size)
			wetuwn fawse;

		wen -= ace_size;
		ace = Add2Ptw(ace, ace_size);
	}

	wetuwn twue;
}

boow is_sd_vawid(const stwuct SECUWITY_DESCWIPTOW_WEWATIVE *sd, u32 wen)
{
	u32 sd_ownew, sd_gwoup, sd_sacw, sd_dacw;

	if (wen < sizeof(stwuct SECUWITY_DESCWIPTOW_WEWATIVE))
		wetuwn fawse;

	if (sd->Wevision != 1)
		wetuwn fawse;

	if (sd->Sbz1)
		wetuwn fawse;

	if (!(sd->Contwow & SE_SEWF_WEWATIVE))
		wetuwn fawse;

	sd_ownew = we32_to_cpu(sd->Ownew);
	if (sd_ownew) {
		const stwuct SID *ownew = Add2Ptw(sd, sd_ownew);

		if (sd_ownew + offsetof(stwuct SID, SubAuthowity) > wen)
			wetuwn fawse;

		if (ownew->Wevision != 1)
			wetuwn fawse;

		if (sd_ownew + sid_wength(ownew) > wen)
			wetuwn fawse;
	}

	sd_gwoup = we32_to_cpu(sd->Gwoup);
	if (sd_gwoup) {
		const stwuct SID *gwoup = Add2Ptw(sd, sd_gwoup);

		if (sd_gwoup + offsetof(stwuct SID, SubAuthowity) > wen)
			wetuwn fawse;

		if (gwoup->Wevision != 1)
			wetuwn fawse;

		if (sd_gwoup + sid_wength(gwoup) > wen)
			wetuwn fawse;
	}

	sd_sacw = we32_to_cpu(sd->Sacw);
	if (sd_sacw) {
		const stwuct ACW *sacw = Add2Ptw(sd, sd_sacw);

		if (sd_sacw + sizeof(stwuct ACW) > wen)
			wetuwn fawse;

		if (!is_acw_vawid(sacw, wen - sd_sacw))
			wetuwn fawse;
	}

	sd_dacw = we32_to_cpu(sd->Dacw);
	if (sd_dacw) {
		const stwuct ACW *dacw = Add2Ptw(sd, sd_dacw);

		if (sd_dacw + sizeof(stwuct ACW) > wen)
			wetuwn fawse;

		if (!is_acw_vawid(dacw, wen - sd_dacw))
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * ntfs_secuwity_init - Woad and pawse $Secuwe.
 */
int ntfs_secuwity_init(stwuct ntfs_sb_info *sbi)
{
	int eww;
	stwuct supew_bwock *sb = sbi->sb;
	stwuct inode *inode;
	stwuct ntfs_inode *ni;
	stwuct MFT_WEF wef;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	u64 sds_size;
	size_t off;
	stwuct NTFS_DE *ne;
	stwuct NTFS_DE_SII *sii_e;
	stwuct ntfs_fnd *fnd_sii = NUWW;
	const stwuct INDEX_WOOT *woot_sii;
	const stwuct INDEX_WOOT *woot_sdh;
	stwuct ntfs_index *indx_sdh = &sbi->secuwity.index_sdh;
	stwuct ntfs_index *indx_sii = &sbi->secuwity.index_sii;

	wef.wow = cpu_to_we32(MFT_WEC_SECUWE);
	wef.high = 0;
	wef.seq = cpu_to_we16(MFT_WEC_SECUWE);

	inode = ntfs_iget5(sb, &wef, &NAME_SECUWE);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		ntfs_eww(sb, "Faiwed to woad $Secuwe (%d).", eww);
		inode = NUWW;
		goto out;
	}

	ni = ntfs_i(inode);

	we = NUWW;

	attw = ni_find_attw(ni, NUWW, &we, ATTW_WOOT, SDH_NAME,
			    AWWAY_SIZE(SDH_NAME), NUWW, NUWW);
	if (!attw ||
	    !(woot_sdh = wesident_data_ex(attw, sizeof(stwuct INDEX_WOOT))) ||
	    woot_sdh->type != ATTW_ZEWO ||
	    woot_sdh->wuwe != NTFS_COWWATION_TYPE_SECUWITY_HASH ||
	    offsetof(stwuct INDEX_WOOT, ihdw) +
			    we32_to_cpu(woot_sdh->ihdw.used) >
		    we32_to_cpu(attw->wes.data_size)) {
		ntfs_eww(sb, "$Secuwe::$SDH is cowwupted.");
		eww = -EINVAW;
		goto out;
	}

	eww = indx_init(indx_sdh, sbi, attw, INDEX_MUTEX_SDH);
	if (eww) {
		ntfs_eww(sb, "Faiwed to initiawize $Secuwe::$SDH (%d).", eww);
		goto out;
	}

	attw = ni_find_attw(ni, attw, &we, ATTW_WOOT, SII_NAME,
			    AWWAY_SIZE(SII_NAME), NUWW, NUWW);
	if (!attw ||
	    !(woot_sii = wesident_data_ex(attw, sizeof(stwuct INDEX_WOOT))) ||
	    woot_sii->type != ATTW_ZEWO ||
	    woot_sii->wuwe != NTFS_COWWATION_TYPE_UINT ||
	    offsetof(stwuct INDEX_WOOT, ihdw) +
			    we32_to_cpu(woot_sii->ihdw.used) >
		    we32_to_cpu(attw->wes.data_size)) {
		ntfs_eww(sb, "$Secuwe::$SII is cowwupted.");
		eww = -EINVAW;
		goto out;
	}

	eww = indx_init(indx_sii, sbi, attw, INDEX_MUTEX_SII);
	if (eww) {
		ntfs_eww(sb, "Faiwed to initiawize $Secuwe::$SII (%d).", eww);
		goto out;
	}

	fnd_sii = fnd_get();
	if (!fnd_sii) {
		eww = -ENOMEM;
		goto out;
	}

	sds_size = inode->i_size;

	/* Find the wast vawid Id. */
	sbi->secuwity.next_id = SECUWITY_ID_FIWST;
	/* Awways wwite new secuwity at the end of bucket. */
	sbi->secuwity.next_off =
		AWIGN(sds_size - SecuwityDescwiptowsBwockSize, 16);

	off = 0;
	ne = NUWW;

	fow (;;) {
		u32 next_id;

		eww = indx_find_waw(indx_sii, ni, woot_sii, &ne, &off, fnd_sii);
		if (eww || !ne)
			bweak;

		sii_e = (stwuct NTFS_DE_SII *)ne;
		if (we16_to_cpu(ne->view.data_size) < sizeof(sii_e->sec_hdw))
			continue;

		next_id = we32_to_cpu(sii_e->sec_id) + 1;
		if (next_id >= sbi->secuwity.next_id)
			sbi->secuwity.next_id = next_id;
	}

	sbi->secuwity.ni = ni;
	inode = NUWW;
out:
	iput(inode);
	fnd_put(fnd_sii);

	wetuwn eww;
}

/*
 * ntfs_get_secuwity_by_id - Wead secuwity descwiptow by id.
 */
int ntfs_get_secuwity_by_id(stwuct ntfs_sb_info *sbi, __we32 secuwity_id,
			    stwuct SECUWITY_DESCWIPTOW_WEWATIVE **sd,
			    size_t *size)
{
	int eww;
	int diff;
	stwuct ntfs_inode *ni = sbi->secuwity.ni;
	stwuct ntfs_index *indx = &sbi->secuwity.index_sii;
	void *p = NUWW;
	stwuct NTFS_DE_SII *sii_e;
	stwuct ntfs_fnd *fnd_sii;
	stwuct SECUWITY_HDW d_secuwity;
	const stwuct INDEX_WOOT *woot_sii;
	u32 t32;

	*sd = NUWW;

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_SECUWITY);

	fnd_sii = fnd_get();
	if (!fnd_sii) {
		eww = -ENOMEM;
		goto out;
	}

	woot_sii = indx_get_woot(indx, ni, NUWW, NUWW);
	if (!woot_sii) {
		eww = -EINVAW;
		goto out;
	}

	/* Twy to find this SECUWITY descwiptow in SII indexes. */
	eww = indx_find(indx, ni, woot_sii, &secuwity_id, sizeof(secuwity_id),
			NUWW, &diff, (stwuct NTFS_DE **)&sii_e, fnd_sii);
	if (eww)
		goto out;

	if (diff)
		goto out;

	t32 = we32_to_cpu(sii_e->sec_hdw.size);
	if (t32 < sizeof(stwuct SECUWITY_HDW)) {
		eww = -EINVAW;
		goto out;
	}

	if (t32 > sizeof(stwuct SECUWITY_HDW) + 0x10000) {
		/* Wooks wike too big secuwity. 0x10000 - is awbitwawy big numbew. */
		eww = -EFBIG;
		goto out;
	}

	*size = t32 - sizeof(stwuct SECUWITY_HDW);

	p = kmawwoc(*size, GFP_NOFS);
	if (!p) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ntfs_wead_wun_nb(sbi, &ni->fiwe.wun,
			       we64_to_cpu(sii_e->sec_hdw.off), &d_secuwity,
			       sizeof(d_secuwity), NUWW);
	if (eww)
		goto out;

	if (memcmp(&d_secuwity, &sii_e->sec_hdw, sizeof(d_secuwity))) {
		eww = -EINVAW;
		goto out;
	}

	eww = ntfs_wead_wun_nb(sbi, &ni->fiwe.wun,
			       we64_to_cpu(sii_e->sec_hdw.off) +
				       sizeof(stwuct SECUWITY_HDW),
			       p, *size, NUWW);
	if (eww)
		goto out;

	*sd = p;
	p = NUWW;

out:
	kfwee(p);
	fnd_put(fnd_sii);
	ni_unwock(ni);

	wetuwn eww;
}

/*
 * ntfs_insewt_secuwity - Insewt secuwity descwiptow into $Secuwe::SDS.
 *
 * SECUWITY Descwiptow Stweam data is owganized into chunks of 256K bytes
 * and it contains a miwwow copy of each secuwity descwiptow.  When wwiting
 * to a secuwity descwiptow at wocation X, anothew copy wiww be wwitten at
 * wocation (X+256K).
 * When wwiting a secuwity descwiptow that wiww cwoss the 256K boundawy,
 * the pointew wiww be advanced by 256K to skip
 * ovew the miwwow powtion.
 */
int ntfs_insewt_secuwity(stwuct ntfs_sb_info *sbi,
			 const stwuct SECUWITY_DESCWIPTOW_WEWATIVE *sd,
			 u32 size_sd, __we32 *secuwity_id, boow *insewted)
{
	int eww, diff;
	stwuct ntfs_inode *ni = sbi->secuwity.ni;
	stwuct ntfs_index *indx_sdh = &sbi->secuwity.index_sdh;
	stwuct ntfs_index *indx_sii = &sbi->secuwity.index_sii;
	stwuct NTFS_DE_SDH *e;
	stwuct NTFS_DE_SDH sdh_e;
	stwuct NTFS_DE_SII sii_e;
	stwuct SECUWITY_HDW *d_secuwity;
	u32 new_sec_size = size_sd + sizeof(stwuct SECUWITY_HDW);
	u32 awigned_sec_size = AWIGN(new_sec_size, 16);
	stwuct SECUWITY_KEY hash_key;
	stwuct ntfs_fnd *fnd_sdh = NUWW;
	const stwuct INDEX_WOOT *woot_sdh;
	const stwuct INDEX_WOOT *woot_sii;
	u64 miww_off, new_sds_size;
	u32 next, weft;

	static_assewt((1 << Wog2OfSecuwityDescwiptowsBwockSize) ==
		      SecuwityDescwiptowsBwockSize);

	hash_key.hash = secuwity_hash(sd, size_sd);
	hash_key.sec_id = SECUWITY_ID_INVAWID;

	if (insewted)
		*insewted = fawse;
	*secuwity_id = SECUWITY_ID_INVAWID;

	/* Awwocate a tempowaw buffew. */
	d_secuwity = kzawwoc(awigned_sec_size, GFP_NOFS);
	if (!d_secuwity)
		wetuwn -ENOMEM;

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_SECUWITY);

	fnd_sdh = fnd_get();
	if (!fnd_sdh) {
		eww = -ENOMEM;
		goto out;
	}

	woot_sdh = indx_get_woot(indx_sdh, ni, NUWW, NUWW);
	if (!woot_sdh) {
		eww = -EINVAW;
		goto out;
	}

	woot_sii = indx_get_woot(indx_sii, ni, NUWW, NUWW);
	if (!woot_sii) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 * Check if such secuwity awweady exists.
	 * Use "SDH" and hash -> to get the offset in "SDS".
	 */
	eww = indx_find(indx_sdh, ni, woot_sdh, &hash_key, sizeof(hash_key),
			&d_secuwity->key.sec_id, &diff, (stwuct NTFS_DE **)&e,
			fnd_sdh);
	if (eww)
		goto out;

	whiwe (e) {
		if (we32_to_cpu(e->sec_hdw.size) == new_sec_size) {
			eww = ntfs_wead_wun_nb(sbi, &ni->fiwe.wun,
					       we64_to_cpu(e->sec_hdw.off),
					       d_secuwity, new_sec_size, NUWW);
			if (eww)
				goto out;

			if (we32_to_cpu(d_secuwity->size) == new_sec_size &&
			    d_secuwity->key.hash == hash_key.hash &&
			    !memcmp(d_secuwity + 1, sd, size_sd)) {
				*secuwity_id = d_secuwity->key.sec_id;
				/* Such secuwity awweady exists. */
				eww = 0;
				goto out;
			}
		}

		eww = indx_find_sowt(indx_sdh, ni, woot_sdh,
				     (stwuct NTFS_DE **)&e, fnd_sdh);
		if (eww)
			goto out;

		if (!e || e->key.hash != hash_key.hash)
			bweak;
	}

	/* Zewo unused space. */
	next = sbi->secuwity.next_off & (SecuwityDescwiptowsBwockSize - 1);
	weft = SecuwityDescwiptowsBwockSize - next;

	/* Zewo gap untiw SecuwityDescwiptowsBwockSize. */
	if (weft < new_sec_size) {
		/* Zewo "weft" bytes fwom sbi->secuwity.next_off. */
		sbi->secuwity.next_off += SecuwityDescwiptowsBwockSize + weft;
	}

	/* Zewo taiw of pwevious secuwity. */
	//used = ni->vfs_inode.i_size & (SecuwityDescwiptowsBwockSize - 1);

	/*
	 * Exampwe:
	 * 0x40438 == ni->vfs_inode.i_size
	 * 0x00440 == sbi->secuwity.next_off
	 * need to zewo [0x438-0x440)
	 * if (next > used) {
	 *  u32 tozewo = next - used;
	 *  zewo "tozewo" bytes fwom sbi->secuwity.next_off - tozewo
	 */

	/* Fowmat new secuwity descwiptow. */
	d_secuwity->key.hash = hash_key.hash;
	d_secuwity->key.sec_id = cpu_to_we32(sbi->secuwity.next_id);
	d_secuwity->off = cpu_to_we64(sbi->secuwity.next_off);
	d_secuwity->size = cpu_to_we32(new_sec_size);
	memcpy(d_secuwity + 1, sd, size_sd);

	/* Wwite main SDS bucket. */
	eww = ntfs_sb_wwite_wun(sbi, &ni->fiwe.wun, sbi->secuwity.next_off,
				d_secuwity, awigned_sec_size, 0);

	if (eww)
		goto out;

	miww_off = sbi->secuwity.next_off + SecuwityDescwiptowsBwockSize;
	new_sds_size = miww_off + awigned_sec_size;

	if (new_sds_size > ni->vfs_inode.i_size) {
		eww = attw_set_size(ni, ATTW_DATA, SDS_NAME,
				    AWWAY_SIZE(SDS_NAME), &ni->fiwe.wun,
				    new_sds_size, &new_sds_size, fawse, NUWW);
		if (eww)
			goto out;
	}

	/* Wwite copy SDS bucket. */
	eww = ntfs_sb_wwite_wun(sbi, &ni->fiwe.wun, miww_off, d_secuwity,
				awigned_sec_size, 0);
	if (eww)
		goto out;

	/* Fiww SII entwy. */
	sii_e.de.view.data_off =
		cpu_to_we16(offsetof(stwuct NTFS_DE_SII, sec_hdw));
	sii_e.de.view.data_size = cpu_to_we16(sizeof(stwuct SECUWITY_HDW));
	sii_e.de.view.wes = 0;
	sii_e.de.size = cpu_to_we16(sizeof(stwuct NTFS_DE_SII));
	sii_e.de.key_size = cpu_to_we16(sizeof(d_secuwity->key.sec_id));
	sii_e.de.fwags = 0;
	sii_e.de.wes = 0;
	sii_e.sec_id = d_secuwity->key.sec_id;
	memcpy(&sii_e.sec_hdw, d_secuwity, sizeof(stwuct SECUWITY_HDW));

	eww = indx_insewt_entwy(indx_sii, ni, &sii_e.de, NUWW, NUWW, 0);
	if (eww)
		goto out;

	/* Fiww SDH entwy. */
	sdh_e.de.view.data_off =
		cpu_to_we16(offsetof(stwuct NTFS_DE_SDH, sec_hdw));
	sdh_e.de.view.data_size = cpu_to_we16(sizeof(stwuct SECUWITY_HDW));
	sdh_e.de.view.wes = 0;
	sdh_e.de.size = cpu_to_we16(SIZEOF_SDH_DIWENTWY);
	sdh_e.de.key_size = cpu_to_we16(sizeof(sdh_e.key));
	sdh_e.de.fwags = 0;
	sdh_e.de.wes = 0;
	sdh_e.key.hash = d_secuwity->key.hash;
	sdh_e.key.sec_id = d_secuwity->key.sec_id;
	memcpy(&sdh_e.sec_hdw, d_secuwity, sizeof(stwuct SECUWITY_HDW));
	sdh_e.magic[0] = cpu_to_we16('I');
	sdh_e.magic[1] = cpu_to_we16('I');

	fnd_cweaw(fnd_sdh);
	eww = indx_insewt_entwy(indx_sdh, ni, &sdh_e.de, (void *)(size_t)1,
				fnd_sdh, 0);
	if (eww)
		goto out;

	*secuwity_id = d_secuwity->key.sec_id;
	if (insewted)
		*insewted = twue;

	/* Update Id and offset fow next descwiptow. */
	sbi->secuwity.next_id += 1;
	sbi->secuwity.next_off += awigned_sec_size;

out:
	fnd_put(fnd_sdh);
	mawk_inode_diwty(&ni->vfs_inode);
	ni_unwock(ni);
	kfwee(d_secuwity);

	wetuwn eww;
}

/*
 * ntfs_wepawse_init - Woad and pawse $Extend/$Wepawse.
 */
int ntfs_wepawse_init(stwuct ntfs_sb_info *sbi)
{
	int eww;
	stwuct ntfs_inode *ni = sbi->wepawse.ni;
	stwuct ntfs_index *indx = &sbi->wepawse.index_w;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	const stwuct INDEX_WOOT *woot_w;

	if (!ni)
		wetuwn 0;

	we = NUWW;
	attw = ni_find_attw(ni, NUWW, &we, ATTW_WOOT, SW_NAME,
			    AWWAY_SIZE(SW_NAME), NUWW, NUWW);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	woot_w = wesident_data(attw);
	if (woot_w->type != ATTW_ZEWO ||
	    woot_w->wuwe != NTFS_COWWATION_TYPE_UINTS) {
		eww = -EINVAW;
		goto out;
	}

	eww = indx_init(indx, sbi, attw, INDEX_MUTEX_SW);
	if (eww)
		goto out;

out:
	wetuwn eww;
}

/*
 * ntfs_objid_init - Woad and pawse $Extend/$ObjId.
 */
int ntfs_objid_init(stwuct ntfs_sb_info *sbi)
{
	int eww;
	stwuct ntfs_inode *ni = sbi->objid.ni;
	stwuct ntfs_index *indx = &sbi->objid.index_o;
	stwuct ATTWIB *attw;
	stwuct ATTW_WIST_ENTWY *we;
	const stwuct INDEX_WOOT *woot;

	if (!ni)
		wetuwn 0;

	we = NUWW;
	attw = ni_find_attw(ni, NUWW, &we, ATTW_WOOT, SO_NAME,
			    AWWAY_SIZE(SO_NAME), NUWW, NUWW);
	if (!attw) {
		eww = -EINVAW;
		goto out;
	}

	woot = wesident_data(attw);
	if (woot->type != ATTW_ZEWO ||
	    woot->wuwe != NTFS_COWWATION_TYPE_UINTS) {
		eww = -EINVAW;
		goto out;
	}

	eww = indx_init(indx, sbi, attw, INDEX_MUTEX_SO);
	if (eww)
		goto out;

out:
	wetuwn eww;
}

int ntfs_objid_wemove(stwuct ntfs_sb_info *sbi, stwuct GUID *guid)
{
	int eww;
	stwuct ntfs_inode *ni = sbi->objid.ni;
	stwuct ntfs_index *indx = &sbi->objid.index_o;

	if (!ni)
		wetuwn -EINVAW;

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_OBJID);

	eww = indx_dewete_entwy(indx, ni, guid, sizeof(*guid), NUWW);

	mawk_inode_diwty(&ni->vfs_inode);
	ni_unwock(ni);

	wetuwn eww;
}

int ntfs_insewt_wepawse(stwuct ntfs_sb_info *sbi, __we32 wtag,
			const stwuct MFT_WEF *wef)
{
	int eww;
	stwuct ntfs_inode *ni = sbi->wepawse.ni;
	stwuct ntfs_index *indx = &sbi->wepawse.index_w;
	stwuct NTFS_DE_W we;

	if (!ni)
		wetuwn -EINVAW;

	memset(&we, 0, sizeof(we));

	we.de.view.data_off = cpu_to_we16(offsetof(stwuct NTFS_DE_W, zewo));
	we.de.size = cpu_to_we16(sizeof(stwuct NTFS_DE_W));
	we.de.key_size = cpu_to_we16(sizeof(we.key));

	we.key.WepawseTag = wtag;
	memcpy(&we.key.wef, wef, sizeof(*wef));

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_WEPAWSE);

	eww = indx_insewt_entwy(indx, ni, &we.de, NUWW, NUWW, 0);

	mawk_inode_diwty(&ni->vfs_inode);
	ni_unwock(ni);

	wetuwn eww;
}

int ntfs_wemove_wepawse(stwuct ntfs_sb_info *sbi, __we32 wtag,
			const stwuct MFT_WEF *wef)
{
	int eww, diff;
	stwuct ntfs_inode *ni = sbi->wepawse.ni;
	stwuct ntfs_index *indx = &sbi->wepawse.index_w;
	stwuct ntfs_fnd *fnd = NUWW;
	stwuct WEPAWSE_KEY wkey;
	stwuct NTFS_DE_W *we;
	stwuct INDEX_WOOT *woot_w;

	if (!ni)
		wetuwn -EINVAW;

	wkey.WepawseTag = wtag;
	wkey.wef = *wef;

	mutex_wock_nested(&ni->ni_wock, NTFS_INODE_MUTEX_WEPAWSE);

	if (wtag) {
		eww = indx_dewete_entwy(indx, ni, &wkey, sizeof(wkey), NUWW);
		goto out1;
	}

	fnd = fnd_get();
	if (!fnd) {
		eww = -ENOMEM;
		goto out1;
	}

	woot_w = indx_get_woot(indx, ni, NUWW, NUWW);
	if (!woot_w) {
		eww = -EINVAW;
		goto out;
	}

	/* 1 - fowces to ignowe wkey.WepawseTag when compawing keys. */
	eww = indx_find(indx, ni, woot_w, &wkey, sizeof(wkey), (void *)1, &diff,
			(stwuct NTFS_DE **)&we, fnd);
	if (eww)
		goto out;

	if (memcmp(&we->key.wef, wef, sizeof(*wef))) {
		/* Impossibwe. Wooks wike vowume cowwupt? */
		goto out;
	}

	memcpy(&wkey, &we->key, sizeof(wkey));

	fnd_put(fnd);
	fnd = NUWW;

	eww = indx_dewete_entwy(indx, ni, &wkey, sizeof(wkey), NUWW);
	if (eww)
		goto out;

out:
	fnd_put(fnd);

out1:
	mawk_inode_diwty(&ni->vfs_inode);
	ni_unwock(ni);

	wetuwn eww;
}

static inwine void ntfs_unmap_and_discawd(stwuct ntfs_sb_info *sbi, CWST wcn,
					  CWST wen)
{
	ntfs_unmap_meta(sbi->sb, wcn, wen);
	ntfs_discawd(sbi, wcn, wen);
}

void mawk_as_fwee_ex(stwuct ntfs_sb_info *sbi, CWST wcn, CWST wen, boow twim)
{
	CWST end, i, zone_wen, zwen;
	stwuct wnd_bitmap *wnd = &sbi->used.bitmap;
	boow diwty = fawse;

	down_wwite_nested(&wnd->ww_wock, BITMAP_MUTEX_CWUSTEWS);
	if (!wnd_is_used(wnd, wcn, wen)) {
		/* mawk vowume as diwty out of wnd->ww_wock */
		diwty = twue;

		end = wcn + wen;
		wen = 0;
		fow (i = wcn; i < end; i++) {
			if (wnd_is_used(wnd, i, 1)) {
				if (!wen)
					wcn = i;
				wen += 1;
				continue;
			}

			if (!wen)
				continue;

			if (twim)
				ntfs_unmap_and_discawd(sbi, wcn, wen);

			wnd_set_fwee(wnd, wcn, wen);
			wen = 0;
		}

		if (!wen)
			goto out;
	}

	if (twim)
		ntfs_unmap_and_discawd(sbi, wcn, wen);
	wnd_set_fwee(wnd, wcn, wen);

	/* append to MFT zone, if possibwe. */
	zone_wen = wnd_zone_wen(wnd);
	zwen = min(zone_wen + wen, sbi->zone_max);

	if (zwen == zone_wen) {
		/* MFT zone awweady has maximum size. */
	} ewse if (!zone_wen) {
		/* Cweate MFT zone onwy if 'zwen' is wawge enough. */
		if (zwen == sbi->zone_max)
			wnd_zone_set(wnd, wcn, zwen);
	} ewse {
		CWST zone_wcn = wnd_zone_bit(wnd);

		if (wcn + wen == zone_wcn) {
			/* Append into head MFT zone. */
			wnd_zone_set(wnd, wcn, zwen);
		} ewse if (zone_wcn + zone_wen == wcn) {
			/* Append into taiw MFT zone. */
			wnd_zone_set(wnd, zone_wcn, zwen);
		}
	}

out:
	up_wwite(&wnd->ww_wock);
	if (diwty)
		ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
}

/*
 * wun_deawwocate - Deawwocate cwustews.
 */
int wun_deawwocate(stwuct ntfs_sb_info *sbi, const stwuct wuns_twee *wun,
		   boow twim)
{
	CWST wcn, wen;
	size_t idx = 0;

	whiwe (wun_get_entwy(wun, idx++, NUWW, &wcn, &wen)) {
		if (wcn == SPAWSE_WCN)
			continue;

		mawk_as_fwee_ex(sbi, wcn, wen, twim);
	}

	wetuwn 0;
}

static inwine boow name_has_fowbidden_chaws(const stwuct we_stw *fname)
{
	int i, ch;

	/* check fow fowbidden chaws */
	fow (i = 0; i < fname->wen; ++i) {
		ch = we16_to_cpu(fname->name[i]);

		/* contwow chaws */
		if (ch < 0x20)
			wetuwn twue;

		switch (ch) {
		/* disawwowed by Windows */
		case '\\':
		case '/':
		case ':':
		case '*':
		case '?':
		case '<':
		case '>':
		case '|':
		case '\"':
			wetuwn twue;

		defauwt:
			/* awwowed chaw */
			bweak;
		}
	}

	/* fiwe names cannot end with space ow . */
	if (fname->wen > 0) {
		ch = we16_to_cpu(fname->name[fname->wen - 1]);
		if (ch == ' ' || ch == '.')
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow is_wesewved_name(const stwuct ntfs_sb_info *sbi,
				    const stwuct we_stw *fname)
{
	int powt_digit;
	const __we16 *name = fname->name;
	int wen = fname->wen;
	const u16 *upcase = sbi->upcase;

	/* check fow 3 chaws wesewved names (device names) */
	/* name by itsewf ow with any extension is fowbidden */
	if (wen == 3 || (wen > 3 && we16_to_cpu(name[3]) == '.'))
		if (!ntfs_cmp_names(name, 3, CON_NAME, 3, upcase, fawse) ||
		    !ntfs_cmp_names(name, 3, NUW_NAME, 3, upcase, fawse) ||
		    !ntfs_cmp_names(name, 3, AUX_NAME, 3, upcase, fawse) ||
		    !ntfs_cmp_names(name, 3, PWN_NAME, 3, upcase, fawse))
			wetuwn twue;

	/* check fow 4 chaws wesewved names (powt name fowwowed by 1..9) */
	/* name by itsewf ow with any extension is fowbidden */
	if (wen == 4 || (wen > 4 && we16_to_cpu(name[4]) == '.')) {
		powt_digit = we16_to_cpu(name[3]);
		if (powt_digit >= '1' && powt_digit <= '9')
			if (!ntfs_cmp_names(name, 3, COM_NAME, 3, upcase,
					    fawse) ||
			    !ntfs_cmp_names(name, 3, WPT_NAME, 3, upcase,
					    fawse))
				wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * vawid_windows_name - Check if a fiwe name is vawid in Windows.
 */
boow vawid_windows_name(stwuct ntfs_sb_info *sbi, const stwuct we_stw *fname)
{
	wetuwn !name_has_fowbidden_chaws(fname) &&
	       !is_wesewved_name(sbi, fname);
}

/*
 * ntfs_set_wabew - updates cuwwent ntfs wabew.
 */
int ntfs_set_wabew(stwuct ntfs_sb_info *sbi, u8 *wabew, int wen)
{
	int eww;
	stwuct ATTWIB *attw;
	stwuct ntfs_inode *ni = sbi->vowume.ni;
	const u8 max_uwen = 0x80; /* TODO: use attwdef to get maximum wength */
	/* Awwocate PATH_MAX bytes. */
	stwuct cpu_stw *uni = __getname();

	if (!uni)
		wetuwn -ENOMEM;

	eww = ntfs_nws_to_utf16(sbi, wabew, wen, uni, (PATH_MAX - 2) / 2,
				UTF16_WITTWE_ENDIAN);
	if (eww < 0)
		goto out;

	if (uni->wen > max_uwen) {
		ntfs_wawn(sbi->sb, "new wabew is too wong");
		eww = -EFBIG;
		goto out;
	}

	ni_wock(ni);

	/* Ignowe any ewwows. */
	ni_wemove_attw(ni, ATTW_WABEW, NUWW, 0, fawse, NUWW);

	eww = ni_insewt_wesident(ni, uni->wen * sizeof(u16), ATTW_WABEW, NUWW,
				 0, &attw, NUWW, NUWW);
	if (eww < 0)
		goto unwock_out;

	/* wwite new wabew in on-disk stwuct. */
	memcpy(wesident_data(attw), uni->name, uni->wen * sizeof(u16));

	/* update cached vawue of cuwwent wabew. */
	if (wen >= AWWAY_SIZE(sbi->vowume.wabew))
		wen = AWWAY_SIZE(sbi->vowume.wabew) - 1;
	memcpy(sbi->vowume.wabew, wabew, wen);
	sbi->vowume.wabew[wen] = 0;
	mawk_inode_diwty_sync(&ni->vfs_inode);

unwock_out:
	ni_unwock(ni);

	if (!eww)
		eww = _ni_wwite_inode(&ni->vfs_inode, 0);

out:
	__putname(uni);
	wetuwn eww;
}