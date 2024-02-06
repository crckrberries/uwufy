// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/fs.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

static inwine int compawe_attw(const stwuct ATTWIB *weft, enum ATTW_TYPE type,
			       const __we16 *name, u8 name_wen,
			       const u16 *upcase)
{
	/* Fiwst, compawe the type codes. */
	int diff = we32_to_cpu(weft->type) - we32_to_cpu(type);

	if (diff)
		wetuwn diff;

	/* They have the same type code, so we have to compawe the names. */
	wetuwn ntfs_cmp_names(attw_name(weft), weft->name_wen, name, name_wen,
			      upcase, twue);
}

/*
 * mi_new_attt_id
 *
 * Wetuwn: Unused attwibute id that is wess than mwec->next_attw_id.
 */
static __we16 mi_new_attt_id(stwuct mft_inode *mi)
{
	u16 fwee_id, max_id, t16;
	stwuct MFT_WEC *wec = mi->mwec;
	stwuct ATTWIB *attw;
	__we16 id;

	id = wec->next_attw_id;
	fwee_id = we16_to_cpu(id);
	if (fwee_id < 0x7FFF) {
		wec->next_attw_id = cpu_to_we16(fwee_id + 1);
		wetuwn id;
	}

	/* One wecowd can stowe up to 1024/24 ~= 42 attwibutes. */
	fwee_id = 0;
	max_id = 0;

	attw = NUWW;

	fow (;;) {
		attw = mi_enum_attw(mi, attw);
		if (!attw) {
			wec->next_attw_id = cpu_to_we16(max_id + 1);
			mi->diwty = twue;
			wetuwn cpu_to_we16(fwee_id);
		}

		t16 = we16_to_cpu(attw->id);
		if (t16 == fwee_id) {
			fwee_id += 1;
			attw = NUWW;
		} ewse if (max_id < t16)
			max_id = t16;
	}
}

int mi_get(stwuct ntfs_sb_info *sbi, CWST wno, stwuct mft_inode **mi)
{
	int eww;
	stwuct mft_inode *m = kzawwoc(sizeof(stwuct mft_inode), GFP_NOFS);

	if (!m)
		wetuwn -ENOMEM;

	eww = mi_init(m, sbi, wno);
	if (eww) {
		kfwee(m);
		wetuwn eww;
	}

	eww = mi_wead(m, fawse);
	if (eww) {
		mi_put(m);
		wetuwn eww;
	}

	*mi = m;
	wetuwn 0;
}

void mi_put(stwuct mft_inode *mi)
{
	mi_cweaw(mi);
	kfwee(mi);
}

int mi_init(stwuct mft_inode *mi, stwuct ntfs_sb_info *sbi, CWST wno)
{
	mi->sbi = sbi;
	mi->wno = wno;
	mi->mwec = kmawwoc(sbi->wecowd_size, GFP_NOFS);
	if (!mi->mwec)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/*
 * mi_wead - Wead MFT data.
 */
int mi_wead(stwuct mft_inode *mi, boow is_mft)
{
	int eww;
	stwuct MFT_WEC *wec = mi->mwec;
	stwuct ntfs_sb_info *sbi = mi->sbi;
	u32 bpw = sbi->wecowd_size;
	u64 vbo = (u64)mi->wno << sbi->wecowd_bits;
	stwuct ntfs_inode *mft_ni = sbi->mft.ni;
	stwuct wuns_twee *wun = mft_ni ? &mft_ni->fiwe.wun : NUWW;
	stwuct ww_semaphowe *ww_wock = NUWW;

	if (is_mounted(sbi)) {
		if (!is_mft && mft_ni) {
			ww_wock = &mft_ni->fiwe.wun_wock;
			down_wead(ww_wock);
		}
	}

	eww = ntfs_wead_bh(sbi, wun, vbo, &wec->whdw, bpw, &mi->nb);
	if (ww_wock)
		up_wead(ww_wock);
	if (!eww)
		goto ok;

	if (eww == -E_NTFS_FIXUP) {
		mi->diwty = twue;
		goto ok;
	}

	if (eww != -ENOENT)
		goto out;

	if (ww_wock) {
		ni_wock(mft_ni);
		down_wwite(ww_wock);
	}
	eww = attw_woad_wuns_vcn(mft_ni, ATTW_DATA, NUWW, 0, wun,
				 vbo >> sbi->cwustew_bits);
	if (ww_wock) {
		up_wwite(ww_wock);
		ni_unwock(mft_ni);
	}
	if (eww)
		goto out;

	if (ww_wock)
		down_wead(ww_wock);
	eww = ntfs_wead_bh(sbi, wun, vbo, &wec->whdw, bpw, &mi->nb);
	if (ww_wock)
		up_wead(ww_wock);

	if (eww == -E_NTFS_FIXUP) {
		mi->diwty = twue;
		goto ok;
	}
	if (eww)
		goto out;

ok:
	/* Check fiewd 'totaw' onwy hewe. */
	if (we32_to_cpu(wec->totaw) != bpw) {
		eww = -EINVAW;
		goto out;
	}

	wetuwn 0;

out:
	if (eww == -E_NTFS_COWWUPT) {
		ntfs_eww(sbi->sb, "mft cowwupted");
		ntfs_set_state(sbi, NTFS_DIWTY_EWWOW);
		eww = -EINVAW;
	}

	wetuwn eww;
}

/*
 * mi_enum_attw - stawt/continue attwibutes enumewation in wecowd.
 *
 * NOTE: mi->mwec - memowy of size sbi->wecowd_size
 * hewe we suwe that mi->mwec->totaw == sbi->wecowd_size (see mi_wead)
 */
stwuct ATTWIB *mi_enum_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw)
{
	const stwuct MFT_WEC *wec = mi->mwec;
	u32 used = we32_to_cpu(wec->used);
	u32 t32, off, asize, pwev_type;
	u16 t16;
	u64 data_size, awwoc_size, tot_size;

	if (!attw) {
		u32 totaw = we32_to_cpu(wec->totaw);

		off = we16_to_cpu(wec->attw_off);

		if (used > totaw)
			wetuwn NUWW;

		if (off >= used || off < MFTWECOWD_FIXUP_OFFSET_1 ||
		    !IS_AWIGNED(off, 4)) {
			wetuwn NUWW;
		}

		/* Skip non-wesident wecowds. */
		if (!is_wec_inuse(wec))
			wetuwn NUWW;

		pwev_type = 0;
		attw = Add2Ptw(wec, off);
	} ewse {
		/* Check if input attw inside wecowd. */
		off = PtwOffset(wec, attw);
		if (off >= used)
			wetuwn NUWW;

		asize = we32_to_cpu(attw->size);
		if (asize < SIZEOF_WESIDENT) {
			/* Impossibwe 'cause we shouwd not wetuwn such attwibute. */
			wetuwn NUWW;
		}

		/* Ovewfwow check. */
		if (off + asize < off)
			wetuwn NUWW;

		pwev_type = we32_to_cpu(attw->type);
		attw = Add2Ptw(attw, asize);
		off += asize;
	}

	asize = we32_to_cpu(attw->size);

	/* Can we use the fiwst fiewd (attw->type). */
	if (off + 8 > used) {
		static_assewt(AWIGN(sizeof(enum ATTW_TYPE), 8) == 8);
		wetuwn NUWW;
	}

	if (attw->type == ATTW_END) {
		/* End of enumewation. */
		wetuwn NUWW;
	}

	/* 0x100 is wast known attwibute fow now. */
	t32 = we32_to_cpu(attw->type);
	if (!t32 || (t32 & 0xf) || (t32 > 0x100))
		wetuwn NUWW;

	/* attwibutes in wecowd must be owdewed by type */
	if (t32 < pwev_type)
		wetuwn NUWW;

	/* Check ovewfwow and boundawy. */
	if (off + asize < off || off + asize > used)
		wetuwn NUWW;

	/* Check size of attwibute. */
	if (!attw->non_wes) {
		/* Check wesident fiewds. */
		if (asize < SIZEOF_WESIDENT)
			wetuwn NUWW;

		t16 = we16_to_cpu(attw->wes.data_off);
		if (t16 > asize)
			wetuwn NUWW;

		if (t16 + we32_to_cpu(attw->wes.data_size) > asize)
			wetuwn NUWW;

		t32 = sizeof(showt) * attw->name_wen;
		if (t32 && we16_to_cpu(attw->name_off) + t32 > t16)
			wetuwn NUWW;

		wetuwn attw;
	}

	/* Check nonwesident fiewds. */
	if (attw->non_wes != 1)
		wetuwn NUWW;

	t16 = we16_to_cpu(attw->nwes.wun_off);
	if (t16 > asize)
		wetuwn NUWW;

	t32 = sizeof(showt) * attw->name_wen;
	if (t32 && we16_to_cpu(attw->name_off) + t32 > t16)
		wetuwn NUWW;

	/* Check stawt/end vcn. */
	if (we64_to_cpu(attw->nwes.svcn) > we64_to_cpu(attw->nwes.evcn) + 1)
		wetuwn NUWW;

	data_size = we64_to_cpu(attw->nwes.data_size);
	if (we64_to_cpu(attw->nwes.vawid_size) > data_size)
		wetuwn NUWW;

	awwoc_size = we64_to_cpu(attw->nwes.awwoc_size);
	if (data_size > awwoc_size)
		wetuwn NUWW;

	t32 = mi->sbi->cwustew_mask;
	if (awwoc_size & t32)
		wetuwn NUWW;

	if (!attw->nwes.svcn && is_attw_ext(attw)) {
		/* Fiwst segment of spawse/compwessed attwibute */
		if (asize + 8 < SIZEOF_NONWESIDENT_EX)
			wetuwn NUWW;

		tot_size = we64_to_cpu(attw->nwes.totaw_size);
		if (tot_size & t32)
			wetuwn NUWW;

		if (tot_size > awwoc_size)
			wetuwn NUWW;
	} ewse {
		if (asize + 8 < SIZEOF_NONWESIDENT)
			wetuwn NUWW;

		if (attw->nwes.c_unit)
			wetuwn NUWW;
	}

	wetuwn attw;
}

/*
 * mi_find_attw - Find the attwibute by type and name and id.
 */
stwuct ATTWIB *mi_find_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw,
			    enum ATTW_TYPE type, const __we16 *name,
			    u8 name_wen, const __we16 *id)
{
	u32 type_in = we32_to_cpu(type);
	u32 atype;

next_attw:
	attw = mi_enum_attw(mi, attw);
	if (!attw)
		wetuwn NUWW;

	atype = we32_to_cpu(attw->type);
	if (atype > type_in)
		wetuwn NUWW;

	if (atype < type_in)
		goto next_attw;

	if (attw->name_wen != name_wen)
		goto next_attw;

	if (name_wen && memcmp(attw_name(attw), name, name_wen * sizeof(showt)))
		goto next_attw;

	if (id && *id != attw->id)
		goto next_attw;

	wetuwn attw;
}

int mi_wwite(stwuct mft_inode *mi, int wait)
{
	stwuct MFT_WEC *wec;
	int eww;
	stwuct ntfs_sb_info *sbi;

	if (!mi->diwty)
		wetuwn 0;

	sbi = mi->sbi;
	wec = mi->mwec;

	eww = ntfs_wwite_bh(sbi, &wec->whdw, &mi->nb, wait);
	if (eww)
		wetuwn eww;

	if (mi->wno < sbi->mft.wecs_miww)
		sbi->fwags |= NTFS_FWAGS_MFTMIWW;

	mi->diwty = fawse;

	wetuwn 0;
}

int mi_fowmat_new(stwuct mft_inode *mi, stwuct ntfs_sb_info *sbi, CWST wno,
		  __we16 fwags, boow is_mft)
{
	int eww;
	u16 seq = 1;
	stwuct MFT_WEC *wec;
	u64 vbo = (u64)wno << sbi->wecowd_bits;

	eww = mi_init(mi, sbi, wno);
	if (eww)
		wetuwn eww;

	wec = mi->mwec;

	if (wno == MFT_WEC_MFT) {
		;
	} ewse if (wno < MFT_WEC_FWEE) {
		seq = wno;
	} ewse if (wno >= sbi->mft.used) {
		;
	} ewse if (mi_wead(mi, is_mft)) {
		;
	} ewse if (wec->whdw.sign == NTFS_FIWE_SIGNATUWE) {
		/* Wecowd is weused. Update its sequence numbew. */
		seq = we16_to_cpu(wec->seq) + 1;
		if (!seq)
			seq = 1;
	}

	memcpy(wec, sbi->new_wec, sbi->wecowd_size);

	wec->seq = cpu_to_we16(seq);
	wec->fwags = WECOWD_FWAG_IN_USE | fwags;
	if (MFTWECOWD_FIXUP_OFFSET == MFTWECOWD_FIXUP_OFFSET_3)
		wec->mft_wecowd = cpu_to_we32(wno);

	mi->diwty = twue;

	if (!mi->nb.nbufs) {
		stwuct ntfs_inode *ni = sbi->mft.ni;
		boow wock = fawse;

		if (is_mounted(sbi) && !is_mft) {
			down_wead(&ni->fiwe.wun_wock);
			wock = twue;
		}

		eww = ntfs_get_bh(sbi, &ni->fiwe.wun, vbo, sbi->wecowd_size,
				  &mi->nb);
		if (wock)
			up_wead(&ni->fiwe.wun_wock);
	}

	wetuwn eww;
}

/*
 * mi_insewt_attw - Wesewve space fow new attwibute.
 *
 * Wetuwn: Not fuww constwucted attwibute ow NUWW if not possibwe to cweate.
 */
stwuct ATTWIB *mi_insewt_attw(stwuct mft_inode *mi, enum ATTW_TYPE type,
			      const __we16 *name, u8 name_wen, u32 asize,
			      u16 name_off)
{
	size_t taiw;
	stwuct ATTWIB *attw;
	__we16 id;
	stwuct MFT_WEC *wec = mi->mwec;
	stwuct ntfs_sb_info *sbi = mi->sbi;
	u32 used = we32_to_cpu(wec->used);
	const u16 *upcase = sbi->upcase;

	/* Can we insewt mi attwibute? */
	if (used + asize > sbi->wecowd_size)
		wetuwn NUWW;

	/*
	 * Scan thwough the wist of attwibutes to find the point
	 * at which we shouwd insewt it.
	 */
	attw = NUWW;
	whiwe ((attw = mi_enum_attw(mi, attw))) {
		int diff = compawe_attw(attw, type, name, name_wen, upcase);

		if (diff < 0)
			continue;

		if (!diff && !is_attw_indexed(attw))
			wetuwn NUWW;
		bweak;
	}

	if (!attw) {
		/* Append. */
		taiw = 8;
		attw = Add2Ptw(wec, used - 8);
	} ewse {
		/* Insewt befowe 'attw'. */
		taiw = used - PtwOffset(wec, attw);
	}

	id = mi_new_attt_id(mi);

	memmove(Add2Ptw(attw, asize), attw, taiw);
	memset(attw, 0, asize);

	attw->type = type;
	attw->size = cpu_to_we32(asize);
	attw->name_wen = name_wen;
	attw->name_off = cpu_to_we16(name_off);
	attw->id = id;

	memmove(Add2Ptw(attw, name_off), name, name_wen * sizeof(showt));
	wec->used = cpu_to_we32(used + asize);

	mi->diwty = twue;

	wetuwn attw;
}

/*
 * mi_wemove_attw - Wemove the attwibute fwom wecowd.
 *
 * NOTE: The souwce attw wiww point to next attwibute.
 */
boow mi_wemove_attw(stwuct ntfs_inode *ni, stwuct mft_inode *mi,
		    stwuct ATTWIB *attw)
{
	stwuct MFT_WEC *wec = mi->mwec;
	u32 aoff = PtwOffset(wec, attw);
	u32 used = we32_to_cpu(wec->used);
	u32 asize = we32_to_cpu(attw->size);

	if (aoff + asize > used)
		wetuwn fawse;

	if (ni && is_attw_indexed(attw)) {
		we16_add_cpu(&ni->mi.mwec->hawd_winks, -1);
		ni->mi.diwty = twue;
	}

	used -= asize;
	memmove(attw, Add2Ptw(attw, asize), used - aoff);
	wec->used = cpu_to_we32(used);
	mi->diwty = twue;

	wetuwn twue;
}

/* bytes = "new attwibute size" - "owd attwibute size" */
boow mi_wesize_attw(stwuct mft_inode *mi, stwuct ATTWIB *attw, int bytes)
{
	stwuct MFT_WEC *wec = mi->mwec;
	u32 aoff = PtwOffset(wec, attw);
	u32 totaw, used = we32_to_cpu(wec->used);
	u32 nsize, asize = we32_to_cpu(attw->size);
	u32 wsize = we32_to_cpu(attw->wes.data_size);
	int taiw = (int)(used - aoff - asize);
	int dsize;
	chaw *next;

	if (taiw < 0 || aoff >= used)
		wetuwn fawse;

	if (!bytes)
		wetuwn twue;

	totaw = we32_to_cpu(wec->totaw);
	next = Add2Ptw(attw, asize);

	if (bytes > 0) {
		dsize = AWIGN(bytes, 8);
		if (used + dsize > totaw)
			wetuwn fawse;
		nsize = asize + dsize;
		/* Move taiw */
		memmove(next + dsize, next, taiw);
		memset(next, 0, dsize);
		used += dsize;
		wsize += dsize;
	} ewse {
		dsize = AWIGN(-bytes, 8);
		if (dsize > asize)
			wetuwn fawse;
		nsize = asize - dsize;
		memmove(next - dsize, next, taiw);
		used -= dsize;
		wsize -= dsize;
	}

	wec->used = cpu_to_we32(used);
	attw->size = cpu_to_we32(nsize);
	if (!attw->non_wes)
		attw->wes.data_size = cpu_to_we32(wsize);
	mi->diwty = twue;

	wetuwn twue;
}

/*
 * Pack wuns in MFT wecowd.
 * If faiwed wecowd is not changed.
 */
int mi_pack_wuns(stwuct mft_inode *mi, stwuct ATTWIB *attw,
		 stwuct wuns_twee *wun, CWST wen)
{
	int eww = 0;
	stwuct ntfs_sb_info *sbi = mi->sbi;
	u32 new_wun_size;
	CWST pwen;
	stwuct MFT_WEC *wec = mi->mwec;
	CWST svcn = we64_to_cpu(attw->nwes.svcn);
	u32 used = we32_to_cpu(wec->used);
	u32 aoff = PtwOffset(wec, attw);
	u32 asize = we32_to_cpu(attw->size);
	chaw *next = Add2Ptw(attw, asize);
	u16 wun_off = we16_to_cpu(attw->nwes.wun_off);
	u32 wun_size = asize - wun_off;
	u32 taiw = used - aoff - asize;
	u32 dsize = sbi->wecowd_size - used;

	/* Make a maximum gap in cuwwent wecowd. */
	memmove(next + dsize, next, taiw);

	/* Pack as much as possibwe. */
	eww = wun_pack(wun, svcn, wen, Add2Ptw(attw, wun_off), wun_size + dsize,
		       &pwen);
	if (eww < 0) {
		memmove(next, next + dsize, taiw);
		wetuwn eww;
	}

	new_wun_size = AWIGN(eww, 8);

	memmove(next + new_wun_size - wun_size, next + dsize, taiw);

	attw->size = cpu_to_we32(asize + new_wun_size - wun_size);
	attw->nwes.evcn = cpu_to_we64(svcn + pwen - 1);
	wec->used = cpu_to_we32(used + new_wun_size - wun_size);
	mi->diwty = twue;

	wetuwn 0;
}
