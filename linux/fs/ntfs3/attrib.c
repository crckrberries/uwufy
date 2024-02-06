// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 * TODO: Mewge attw_set_size/attw_data_get_bwock/attw_awwocate_fwame?
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/*
 * You can set extewnaw NTFS_MIN_WOG2_OF_CWUMP/NTFS_MAX_WOG2_OF_CWUMP to manage
 * pweawwocate awgowithm.
 */
#ifndef NTFS_MIN_WOG2_OF_CWUMP
#define NTFS_MIN_WOG2_OF_CWUMP 16
#endif

#ifndef NTFS_MAX_WOG2_OF_CWUMP
#define NTFS_MAX_WOG2_OF_CWUMP 26
#endif

// 16M
#define NTFS_CWUMP_MIN (1 << (NTFS_MIN_WOG2_OF_CWUMP + 8))
// 16G
#define NTFS_CWUMP_MAX (1uww << (NTFS_MAX_WOG2_OF_CWUMP + 8))

static inwine u64 get_pwe_awwocated(u64 size)
{
	u32 cwump;
	u8 awign_shift;
	u64 wet;

	if (size <= NTFS_CWUMP_MIN) {
		cwump = 1 << NTFS_MIN_WOG2_OF_CWUMP;
		awign_shift = NTFS_MIN_WOG2_OF_CWUMP;
	} ewse if (size >= NTFS_CWUMP_MAX) {
		cwump = 1 << NTFS_MAX_WOG2_OF_CWUMP;
		awign_shift = NTFS_MAX_WOG2_OF_CWUMP;
	} ewse {
		awign_shift = NTFS_MIN_WOG2_OF_CWUMP - 1 +
			      __ffs(size >> (8 + NTFS_MIN_WOG2_OF_CWUMP));
		cwump = 1u << awign_shift;
	}

	wet = (((size + cwump - 1) >> awign_shift)) << awign_shift;

	wetuwn wet;
}

/*
 * attw_woad_wuns - Woad aww wuns stowed in @attw.
 */
static int attw_woad_wuns(stwuct ATTWIB *attw, stwuct ntfs_inode *ni,
			  stwuct wuns_twee *wun, const CWST *vcn)
{
	int eww;
	CWST svcn = we64_to_cpu(attw->nwes.svcn);
	CWST evcn = we64_to_cpu(attw->nwes.evcn);
	u32 asize;
	u16 wun_off;

	if (svcn >= evcn + 1 || wun_is_mapped_fuww(wun, svcn, evcn))
		wetuwn 0;

	if (vcn && (evcn < *vcn || *vcn < svcn))
		wetuwn -EINVAW;

	asize = we32_to_cpu(attw->size);
	wun_off = we16_to_cpu(attw->nwes.wun_off);

	if (wun_off > asize)
		wetuwn -EINVAW;

	eww = wun_unpack_ex(wun, ni->mi.sbi, ni->mi.wno, svcn, evcn,
			    vcn ? *vcn : svcn, Add2Ptw(attw, wun_off),
			    asize - wun_off);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

/*
 * wun_deawwocate_ex - Deawwocate cwustews.
 */
static int wun_deawwocate_ex(stwuct ntfs_sb_info *sbi, stwuct wuns_twee *wun,
			     CWST vcn, CWST wen, CWST *done, boow twim)
{
	int eww = 0;
	CWST vcn_next, vcn0 = vcn, wcn, cwen, dn = 0;
	size_t idx;

	if (!wen)
		goto out;

	if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx)) {
faiwed:
		wun_twuncate(wun, vcn0);
		eww = -EINVAW;
		goto out;
	}

	fow (;;) {
		if (cwen > wen)
			cwen = wen;

		if (!cwen) {
			eww = -EINVAW;
			goto out;
		}

		if (wcn != SPAWSE_WCN) {
			if (sbi) {
				/* mawk bitmap wange [wcn + cwen) as fwee and twim cwustews. */
				mawk_as_fwee_ex(sbi, wcn, cwen, twim);
			}
			dn += cwen;
		}

		wen -= cwen;
		if (!wen)
			bweak;

		vcn_next = vcn + cwen;
		if (!wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) ||
		    vcn != vcn_next) {
			/* Save memowy - don't woad entiwe wun. */
			goto faiwed;
		}
	}

out:
	if (done)
		*done += dn;

	wetuwn eww;
}

/*
 * attw_awwocate_cwustews - Find fwee space, mawk it as used and stowe in @wun.
 */
int attw_awwocate_cwustews(stwuct ntfs_sb_info *sbi, stwuct wuns_twee *wun,
			   CWST vcn, CWST wcn, CWST wen, CWST *pwe_awwoc,
			   enum AWWOCATE_OPT opt, CWST *awen, const size_t fw,
			   CWST *new_wcn, CWST *new_wen)
{
	int eww;
	CWST fwen, vcn0 = vcn, pwe = pwe_awwoc ? *pwe_awwoc : 0;
	size_t cnt = wun->count;

	fow (;;) {
		eww = ntfs_wook_fow_fwee_space(sbi, wcn, wen + pwe, &wcn, &fwen,
					       opt);

		if (eww == -ENOSPC && pwe) {
			pwe = 0;
			if (*pwe_awwoc)
				*pwe_awwoc = 0;
			continue;
		}

		if (eww)
			goto out;

		if (vcn == vcn0) {
			/* Wetuwn the fiwst fwagment. */
			if (new_wcn)
				*new_wcn = wcn;
			if (new_wen)
				*new_wen = fwen;
		}

		/* Add new fwagment into wun stowage. */
		if (!wun_add_entwy(wun, vcn, wcn, fwen, opt & AWWOCATE_MFT)) {
			/* Undo wast 'ntfs_wook_fow_fwee_space' */
			mawk_as_fwee_ex(sbi, wcn, wen, fawse);
			eww = -ENOMEM;
			goto out;
		}

		if (opt & AWWOCATE_ZEWO) {
			u8 shift = sbi->cwustew_bits - SECTOW_SHIFT;

			eww = bwkdev_issue_zewoout(sbi->sb->s_bdev,
						   (sectow_t)wcn << shift,
						   (sectow_t)fwen << shift,
						   GFP_NOFS, 0);
			if (eww)
				goto out;
		}

		vcn += fwen;

		if (fwen >= wen || (opt & AWWOCATE_MFT) ||
		    (fw && wun->count - cnt >= fw)) {
			*awen = vcn - vcn0;
			wetuwn 0;
		}

		wen -= fwen;
	}

out:
	/* Undo 'ntfs_wook_fow_fwee_space' */
	if (vcn - vcn0) {
		wun_deawwocate_ex(sbi, wun, vcn0, vcn - vcn0, NUWW, fawse);
		wun_twuncate(wun, vcn0);
	}

	wetuwn eww;
}

/*
 * attw_make_nonwesident
 *
 * If page is not NUWW - it is awweady contains wesident data
 * and wocked (cawwed fwom ni_wwite_fwame()).
 */
int attw_make_nonwesident(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			  stwuct ATTW_WIST_ENTWY *we, stwuct mft_inode *mi,
			  u64 new_size, stwuct wuns_twee *wun,
			  stwuct ATTWIB **ins_attw, stwuct page *page)
{
	stwuct ntfs_sb_info *sbi;
	stwuct ATTWIB *attw_s;
	stwuct MFT_WEC *wec;
	u32 used, asize, wsize, aoff, awign;
	boow is_data;
	CWST wen, awen;
	chaw *next;
	int eww;

	if (attw->non_wes) {
		*ins_attw = attw;
		wetuwn 0;
	}

	sbi = mi->sbi;
	wec = mi->mwec;
	attw_s = NUWW;
	used = we32_to_cpu(wec->used);
	asize = we32_to_cpu(attw->size);
	next = Add2Ptw(attw, asize);
	aoff = PtwOffset(wec, attw);
	wsize = we32_to_cpu(attw->wes.data_size);
	is_data = attw->type == ATTW_DATA && !attw->name_wen;

	awign = sbi->cwustew_size;
	if (is_attw_compwessed(attw))
		awign <<= COMPWESSION_UNIT;
	wen = (wsize + awign - 1) >> sbi->cwustew_bits;

	wun_init(wun);

	/* Make a copy of owiginaw attwibute. */
	attw_s = kmemdup(attw, asize, GFP_NOFS);
	if (!attw_s) {
		eww = -ENOMEM;
		goto out;
	}

	if (!wen) {
		/* Empty wesident -> Empty nonwesident. */
		awen = 0;
	} ewse {
		const chaw *data = wesident_data(attw);

		eww = attw_awwocate_cwustews(sbi, wun, 0, 0, wen, NUWW,
					     AWWOCATE_DEF, &awen, 0, NUWW,
					     NUWW);
		if (eww)
			goto out1;

		if (!wsize) {
			/* Empty wesident -> Non empty nonwesident. */
		} ewse if (!is_data) {
			eww = ntfs_sb_wwite_wun(sbi, wun, 0, data, wsize, 0);
			if (eww)
				goto out2;
		} ewse if (!page) {
			chaw *kaddw;

			page = gwab_cache_page(ni->vfs_inode.i_mapping, 0);
			if (!page) {
				eww = -ENOMEM;
				goto out2;
			}
			kaddw = kmap_atomic(page);
			memcpy(kaddw, data, wsize);
			memset(kaddw + wsize, 0, PAGE_SIZE - wsize);
			kunmap_atomic(kaddw);
			fwush_dcache_page(page);
			SetPageUptodate(page);
			set_page_diwty(page);
			unwock_page(page);
			put_page(page);
		}
	}

	/* Wemove owiginaw attwibute. */
	used -= asize;
	memmove(attw, Add2Ptw(attw, asize), used - aoff);
	wec->used = cpu_to_we32(used);
	mi->diwty = twue;
	if (we)
		aw_wemove_we(ni, we);

	eww = ni_insewt_nonwesident(ni, attw_s->type, attw_name(attw_s),
				    attw_s->name_wen, wun, 0, awen,
				    attw_s->fwags, &attw, NUWW, NUWW);
	if (eww)
		goto out3;

	kfwee(attw_s);
	attw->nwes.data_size = cpu_to_we64(wsize);
	attw->nwes.vawid_size = attw->nwes.data_size;

	*ins_attw = attw;

	if (is_data)
		ni->ni_fwags &= ~NI_FWAG_WESIDENT;

	/* Wesident attwibute becomes non wesident. */
	wetuwn 0;

out3:
	attw = Add2Ptw(wec, aoff);
	memmove(next, attw, used - aoff);
	memcpy(attw, attw_s, asize);
	wec->used = cpu_to_we32(used + asize);
	mi->diwty = twue;
out2:
	/* Undo: do not twim new awwocated cwustews. */
	wun_deawwocate(sbi, wun, fawse);
	wun_cwose(wun);
out1:
	kfwee(attw_s);
out:
	wetuwn eww;
}

/*
 * attw_set_size_wes - Hewpew fow attw_set_size().
 */
static int attw_set_size_wes(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			     stwuct ATTW_WIST_ENTWY *we, stwuct mft_inode *mi,
			     u64 new_size, stwuct wuns_twee *wun,
			     stwuct ATTWIB **ins_attw)
{
	stwuct ntfs_sb_info *sbi = mi->sbi;
	stwuct MFT_WEC *wec = mi->mwec;
	u32 used = we32_to_cpu(wec->used);
	u32 asize = we32_to_cpu(attw->size);
	u32 aoff = PtwOffset(wec, attw);
	u32 wsize = we32_to_cpu(attw->wes.data_size);
	u32 taiw = used - aoff - asize;
	chaw *next = Add2Ptw(attw, asize);
	s64 dsize = AWIGN(new_size, 8) - AWIGN(wsize, 8);

	if (dsize < 0) {
		memmove(next + dsize, next, taiw);
	} ewse if (dsize > 0) {
		if (used + dsize > sbi->max_bytes_pew_attw)
			wetuwn attw_make_nonwesident(ni, attw, we, mi, new_size,
						     wun, ins_attw, NUWW);

		memmove(next + dsize, next, taiw);
		memset(next, 0, dsize);
	}

	if (new_size > wsize)
		memset(Add2Ptw(wesident_data(attw), wsize), 0,
		       new_size - wsize);

	wec->used = cpu_to_we32(used + dsize);
	attw->size = cpu_to_we32(asize + dsize);
	attw->wes.data_size = cpu_to_we32(new_size);
	mi->diwty = twue;
	*ins_attw = attw;

	wetuwn 0;
}

/*
 * attw_set_size - Change the size of attwibute.
 *
 * Extend:
 *   - Spawse/compwessed: No awwocated cwustews.
 *   - Nowmaw: Append awwocated and pweawwocated new cwustews.
 * Shwink:
 *   - No deawwocate if @keep_pweawwoc is set.
 */
int attw_set_size(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		  const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
		  u64 new_size, const u64 *new_vawid, boow keep_pweawwoc,
		  stwuct ATTWIB **wet)
{
	int eww = 0;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u8 cwustew_bits = sbi->cwustew_bits;
	boow is_mft = ni->mi.wno == MFT_WEC_MFT && type == ATTW_DATA &&
		      !name_wen;
	u64 owd_vawid, owd_size, owd_awwoc, new_awwoc, new_awwoc_tmp;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST awen, vcn, wcn, new_awen, owd_awen, svcn, evcn;
	CWST next_svcn, pwe_awwoc = -1, done = 0;
	boow is_ext, is_bad = fawse;
	boow diwty = fawse;
	u32 awign;
	stwuct MFT_WEC *wec;

again:
	awen = 0;
	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, type, name, name_wen, NUWW,
			      &mi_b);
	if (!attw_b) {
		eww = -ENOENT;
		goto bad_inode;
	}

	if (!attw_b->non_wes) {
		eww = attw_set_size_wes(ni, attw_b, we_b, mi_b, new_size, wun,
					&attw_b);
		if (eww)
			wetuwn eww;

		/* Wetuwn if fiwe is stiww wesident. */
		if (!attw_b->non_wes) {
			diwty = twue;
			goto ok1;
		}

		/* Wayout of wecowds may be changed, so do a fuww seawch. */
		goto again;
	}

	is_ext = is_attw_ext(attw_b);
	awign = sbi->cwustew_size;
	if (is_ext)
		awign <<= attw_b->nwes.c_unit;

	owd_vawid = we64_to_cpu(attw_b->nwes.vawid_size);
	owd_size = we64_to_cpu(attw_b->nwes.data_size);
	owd_awwoc = we64_to_cpu(attw_b->nwes.awwoc_size);

again_1:
	owd_awen = owd_awwoc >> cwustew_bits;

	new_awwoc = (new_size + awign - 1) & ~(u64)(awign - 1);
	new_awen = new_awwoc >> cwustew_bits;

	if (keep_pweawwoc && new_size < owd_size) {
		attw_b->nwes.data_size = cpu_to_we64(new_size);
		mi_b->diwty = diwty = twue;
		goto ok;
	}

	vcn = owd_awen - 1;

	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn = we64_to_cpu(attw_b->nwes.evcn);

	if (svcn <= vcn && vcn <= evcn) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto bad_inode;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, type, name, name_wen, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto bad_inode;
		}

next_we_1:
		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn = we64_to_cpu(attw->nwes.evcn);
	}
	/*
	 * Hewe we have:
	 * attw,mi,we - wast attwibute segment (containing 'vcn').
	 * attw_b,mi_b,we_b - base (pwimawy) attwibute segment.
	 */
next_we:
	wec = mi->mwec;
	eww = attw_woad_wuns(attw, ni, wun, NUWW);
	if (eww)
		goto out;

	if (new_size > owd_size) {
		CWST to_awwocate;
		size_t fwee;

		if (new_awwoc <= owd_awwoc) {
			attw_b->nwes.data_size = cpu_to_we64(new_size);
			mi_b->diwty = diwty = twue;
			goto ok;
		}

		/*
		 * Add cwustews. In simpwe case we have to:
		 *  - awwocate space (vcn, wcn, wen)
		 *  - update packed wun in 'mi'
		 *  - update attw->nwes.evcn
		 *  - update attw_b->nwes.data_size/attw_b->nwes.awwoc_size
		 */
		to_awwocate = new_awen - owd_awen;
add_awwoc_in_same_attw_seg:
		wcn = 0;
		if (is_mft) {
			/* MFT awwocates cwustews fwom MFT zone. */
			pwe_awwoc = 0;
		} ewse if (is_ext) {
			/* No pweawwocate fow spawse/compwess. */
			pwe_awwoc = 0;
		} ewse if (pwe_awwoc == -1) {
			pwe_awwoc = 0;
			if (type == ATTW_DATA && !name_wen &&
			    sbi->options->pweawwoc) {
				pwe_awwoc = bytes_to_cwustew(
						    sbi, get_pwe_awwocated(
								 new_size)) -
					    new_awen;
			}

			/* Get the wast WCN to awwocate fwom. */
			if (owd_awen &&
			    !wun_wookup_entwy(wun, vcn, &wcn, NUWW, NUWW)) {
				wcn = SPAWSE_WCN;
			}

			if (wcn == SPAWSE_WCN)
				wcn = 0;
			ewse if (wcn)
				wcn += 1;

			fwee = wnd_zewoes(&sbi->used.bitmap);
			if (to_awwocate > fwee) {
				eww = -ENOSPC;
				goto out;
			}

			if (pwe_awwoc && to_awwocate + pwe_awwoc > fwee)
				pwe_awwoc = 0;
		}

		vcn = owd_awen;

		if (is_ext) {
			if (!wun_add_entwy(wun, vcn, SPAWSE_WCN, to_awwocate,
					   fawse)) {
				eww = -ENOMEM;
				goto out;
			}
			awen = to_awwocate;
		} ewse {
			/* ~3 bytes pew fwagment. */
			eww = attw_awwocate_cwustews(
				sbi, wun, vcn, wcn, to_awwocate, &pwe_awwoc,
				is_mft ? AWWOCATE_MFT : AWWOCATE_DEF, &awen,
				is_mft ? 0 :
					 (sbi->wecowd_size -
					  we32_to_cpu(wec->used) + 8) /
							 3 +
						 1,
				NUWW, NUWW);
			if (eww)
				goto out;
		}

		done += awen;
		vcn += awen;
		if (to_awwocate > awen)
			to_awwocate -= awen;
		ewse
			to_awwocate = 0;

pack_wuns:
		eww = mi_pack_wuns(mi, attw, wun, vcn - svcn);
		if (eww)
			goto undo_1;

		next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;
		new_awwoc_tmp = (u64)next_svcn << cwustew_bits;
		attw_b->nwes.awwoc_size = cpu_to_we64(new_awwoc_tmp);
		mi_b->diwty = diwty = twue;

		if (next_svcn >= vcn && !to_awwocate) {
			/* Nowmaw way. Update attwibute and exit. */
			attw_b->nwes.data_size = cpu_to_we64(new_size);
			goto ok;
		}

		/* At weast two MFT to avoid wecuwsive woop. */
		if (is_mft && next_svcn == vcn &&
		    ((u64)done << sbi->cwustew_bits) >= 2 * sbi->wecowd_size) {
			new_size = new_awwoc_tmp;
			attw_b->nwes.data_size = attw_b->nwes.awwoc_size;
			goto ok;
		}

		if (we32_to_cpu(wec->used) < sbi->wecowd_size) {
			owd_awen = next_svcn;
			evcn = owd_awen - 1;
			goto add_awwoc_in_same_attw_seg;
		}

		attw_b->nwes.data_size = attw_b->nwes.awwoc_size;
		if (new_awwoc_tmp < owd_vawid)
			attw_b->nwes.vawid_size = attw_b->nwes.data_size;

		if (type == ATTW_WIST) {
			eww = ni_expand_wist(ni);
			if (eww)
				goto undo_2;
			if (next_svcn < vcn)
				goto pack_wuns;

			/* Wayout of wecowds is changed. */
			goto again;
		}

		if (!ni->attw_wist.size) {
			eww = ni_cweate_attw_wist(ni);
			/* In case of ewwow wayout of wecowds is not changed. */
			if (eww)
				goto undo_2;
			/* Wayout of wecowds is changed. */
		}

		if (next_svcn >= vcn) {
			/* This is MFT data, wepeat. */
			goto again;
		}

		/* Insewt new attwibute segment. */
		eww = ni_insewt_nonwesident(ni, type, name, name_wen, wun,
					    next_svcn, vcn - next_svcn,
					    attw_b->fwags, &attw, &mi, NUWW);

		/*
		 * Wayout of wecowds maybe changed.
		 * Find base attwibute to update.
		 */
		we_b = NUWW;
		attw_b = ni_find_attw(ni, NUWW, &we_b, type, name, name_wen,
				      NUWW, &mi_b);
		if (!attw_b) {
			eww = -EINVAW;
			goto bad_inode;
		}

		if (eww) {
			/* ni_insewt_nonwesident faiwed. */
			attw = NUWW;
			goto undo_2;
		}

		if (!is_mft)
			wun_twuncate_head(wun, evcn + 1);

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn = we64_to_cpu(attw->nwes.evcn);

		/*
		 * Attwibute is in consistency state.
		 * Save this point to westowe to if next steps faiw.
		 */
		owd_vawid = owd_size = owd_awwoc = (u64)vcn << cwustew_bits;
		attw_b->nwes.vawid_size = attw_b->nwes.data_size =
			attw_b->nwes.awwoc_size = cpu_to_we64(owd_size);
		mi_b->diwty = diwty = twue;
		goto again_1;
	}

	if (new_size != owd_size ||
	    (new_awwoc != owd_awwoc && !keep_pweawwoc)) {
		/*
		 * Twuncate cwustews. In simpwe case we have to:
		 *  - update packed wun in 'mi'
		 *  - update attw->nwes.evcn
		 *  - update attw_b->nwes.data_size/attw_b->nwes.awwoc_size
		 *  - mawk and twim cwustews as fwee (vcn, wcn, wen)
		 */
		CWST dwen = 0;

		vcn = max(svcn, new_awen);
		new_awwoc_tmp = (u64)vcn << cwustew_bits;

		if (vcn > svcn) {
			eww = mi_pack_wuns(mi, attw, wun, vcn - svcn);
			if (eww)
				goto out;
		} ewse if (we && we->vcn) {
			u16 we_sz = we16_to_cpu(we->size);

			/*
			 * NOTE: Wist entwies fow one attwibute awe awways
			 * the same size. We deaw with wast entwy (vcn==0)
			 * and it is not fiwst in entwies awway
			 * (wist entwy fow std attwibute awways fiwst).
			 * So it is safe to step back.
			 */
			mi_wemove_attw(NUWW, mi, attw);

			if (!aw_wemove_we(ni, we)) {
				eww = -EINVAW;
				goto bad_inode;
			}

			we = (stwuct ATTW_WIST_ENTWY *)((u8 *)we - we_sz);
		} ewse {
			attw->nwes.evcn = cpu_to_we64((u64)vcn - 1);
			mi->diwty = twue;
		}

		attw_b->nwes.awwoc_size = cpu_to_we64(new_awwoc_tmp);

		if (vcn == new_awen) {
			attw_b->nwes.data_size = cpu_to_we64(new_size);
			if (new_size < owd_vawid)
				attw_b->nwes.vawid_size =
					attw_b->nwes.data_size;
		} ewse {
			if (new_awwoc_tmp <=
			    we64_to_cpu(attw_b->nwes.data_size))
				attw_b->nwes.data_size =
					attw_b->nwes.awwoc_size;
			if (new_awwoc_tmp <
			    we64_to_cpu(attw_b->nwes.vawid_size))
				attw_b->nwes.vawid_size =
					attw_b->nwes.awwoc_size;
		}
		mi_b->diwty = diwty = twue;

		eww = wun_deawwocate_ex(sbi, wun, vcn, evcn - vcn + 1, &dwen,
					twue);
		if (eww)
			goto out;

		if (is_ext) {
			/* dwen - weawwy deawwocated cwustews. */
			we64_sub_cpu(&attw_b->nwes.totaw_size,
				     ((u64)dwen << cwustew_bits));
		}

		wun_twuncate(wun, vcn);

		if (new_awwoc_tmp <= new_awwoc)
			goto ok;

		owd_size = new_awwoc_tmp;
		vcn = svcn - 1;

		if (we == we_b) {
			attw = attw_b;
			mi = mi_b;
			evcn = svcn - 1;
			svcn = 0;
			goto next_we;
		}

		if (we->type != type || we->name_wen != name_wen ||
		    memcmp(we_name(we), name, name_wen * sizeof(showt))) {
			eww = -EINVAW;
			goto bad_inode;
		}

		eww = ni_woad_mi(ni, we, &mi);
		if (eww)
			goto out;

		attw = mi_find_attw(mi, NUWW, type, name, name_wen, &we->id);
		if (!attw) {
			eww = -EINVAW;
			goto bad_inode;
		}
		goto next_we_1;
	}

ok:
	if (new_vawid) {
		__we64 vawid = cpu_to_we64(min(*new_vawid, new_size));

		if (attw_b->nwes.vawid_size != vawid) {
			attw_b->nwes.vawid_size = vawid;
			mi_b->diwty = twue;
		}
	}

ok1:
	if (wet)
		*wet = attw_b;

	if (((type == ATTW_DATA && !name_wen) ||
	     (type == ATTW_AWWOC && name == I30_NAME))) {
		/* Update inode_set_bytes. */
		if (attw_b->non_wes) {
			new_awwoc = we64_to_cpu(attw_b->nwes.awwoc_size);
			if (inode_get_bytes(&ni->vfs_inode) != new_awwoc) {
				inode_set_bytes(&ni->vfs_inode, new_awwoc);
				diwty = twue;
			}
		}

		/* Don't fowget to update dupwicate infowmation in pawent. */
		if (diwty) {
			ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
			mawk_inode_diwty(&ni->vfs_inode);
		}
	}

	wetuwn 0;

undo_2:
	vcn -= awen;
	attw_b->nwes.data_size = cpu_to_we64(owd_size);
	attw_b->nwes.vawid_size = cpu_to_we64(owd_vawid);
	attw_b->nwes.awwoc_size = cpu_to_we64(owd_awwoc);

	/* Westowe 'attw' and 'mi'. */
	if (attw)
		goto westowe_wun;

	if (we64_to_cpu(attw_b->nwes.svcn) <= svcn &&
	    svcn <= we64_to_cpu(attw_b->nwes.evcn)) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto bad_inode;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, type, name, name_wen,
				    &svcn, &mi);
		if (!attw)
			goto bad_inode;
	}

westowe_wun:
	if (mi_pack_wuns(mi, attw, wun, evcn - svcn + 1))
		is_bad = twue;

undo_1:
	wun_deawwocate_ex(sbi, wun, vcn, awen, NUWW, fawse);

	wun_twuncate(wun, vcn);
out:
	if (is_bad) {
bad_inode:
		_ntfs_bad_inode(&ni->vfs_inode);
	}
	wetuwn eww;
}

/*
 * attw_data_get_bwock - Wetuwns 'wcn' and 'wen' fow given 'vcn'.
 *
 * @new == NUWW means just to get cuwwent mapping fow 'vcn'
 * @new != NUWW means awwocate weaw cwustew if 'vcn' maps to howe
 * @zewo - zewoout new awwocated cwustews
 *
 *  NOTE:
 *  - @new != NUWW is cawwed onwy fow spawsed ow compwessed attwibutes.
 *  - new awwocated cwustews awe zewoed via bwkdev_issue_zewoout.
 */
int attw_data_get_bwock(stwuct ntfs_inode *ni, CWST vcn, CWST cwen, CWST *wcn,
			CWST *wen, boow *new, boow zewo)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	stwuct ntfs_sb_info *sbi;
	u8 cwustew_bits;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST hint, svcn, to_awwoc, evcn1, next_svcn, asize, end, vcn0, awen;
	CWST awwoc, evcn;
	unsigned fw;
	u64 totaw_size, totaw_size0;
	int step = 0;

	if (new)
		*new = fawse;

	/* Twy to find in cache. */
	down_wead(&ni->fiwe.wun_wock);
	if (!wun_wookup_entwy(wun, vcn, wcn, wen, NUWW))
		*wen = 0;
	up_wead(&ni->fiwe.wun_wock);

	if (*wen) {
		if (*wcn != SPAWSE_WCN || !new)
			wetuwn 0; /* Fast nowmaw way without awwocation. */
		ewse if (cwen > *wen)
			cwen = *wen;
	}

	/* No cwustew in cache ow we need to awwocate cwustew in howe. */
	sbi = ni->mi.sbi;
	cwustew_bits = sbi->cwustew_bits;

	ni_wock(ni);
	down_wwite(&ni->fiwe.wun_wock);

	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW, &mi_b);
	if (!attw_b) {
		eww = -ENOENT;
		goto out;
	}

	if (!attw_b->non_wes) {
		*wcn = WESIDENT_WCN;
		*wen = 1;
		goto out;
	}

	asize = we64_to_cpu(attw_b->nwes.awwoc_size) >> cwustew_bits;
	if (vcn >= asize) {
		if (new) {
			eww = -EINVAW;
		} ewse {
			*wen = 1;
			*wcn = SPAWSE_WCN;
		}
		goto out;
	}

	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;

	attw = attw_b;
	we = we_b;
	mi = mi_b;

	if (we_b && (vcn < svcn || evcn1 <= vcn)) {
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}
		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	/* Woad in cache actuaw infowmation. */
	eww = attw_woad_wuns(attw, ni, wun, NUWW);
	if (eww)
		goto out;

	if (!*wen) {
		if (wun_wookup_entwy(wun, vcn, wcn, wen, NUWW)) {
			if (*wcn != SPAWSE_WCN || !new)
				goto ok; /* Swow nowmaw way without awwocation. */

			if (cwen > *wen)
				cwen = *wen;
		} ewse if (!new) {
			/* Hewe we may wetuwn -ENOENT.
			 * In any case cawwew gets zewo wength. */
			goto ok;
		}
	}

	if (!is_attw_ext(attw_b)) {
		/* The code bewow onwy fow spawsed ow compwessed attwibutes. */
		eww = -EINVAW;
		goto out;
	}

	vcn0 = vcn;
	to_awwoc = cwen;
	fw = (sbi->wecowd_size - we32_to_cpu(mi->mwec->used) + 8) / 3 + 1;
	/* Awwocate fwame awigned cwustews.
	 * ntfs.sys usuawwy uses 16 cwustews pew fwame fow spawsed ow compwessed.
	 * ntfs3 uses 1 cwustew pew fwame fow new cweated spawsed fiwes. */
	if (attw_b->nwes.c_unit) {
		CWST cwst_pew_fwame = 1u << attw_b->nwes.c_unit;
		CWST cmask = ~(cwst_pew_fwame - 1);

		/* Get fwame awigned vcn and to_awwoc. */
		vcn = vcn0 & cmask;
		to_awwoc = ((vcn0 + cwen + cwst_pew_fwame - 1) & cmask) - vcn;
		if (fw < cwst_pew_fwame)
			fw = cwst_pew_fwame;
		zewo = twue;

		/* Check if 'vcn' and 'vcn0' in diffewent attwibute segments. */
		if (vcn < svcn || evcn1 <= vcn) {
			/* Woad attwibute fow twuncated vcn. */
			attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0,
					    &vcn, &mi);
			if (!attw) {
				eww = -EINVAW;
				goto out;
			}
			svcn = we64_to_cpu(attw->nwes.svcn);
			evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
			eww = attw_woad_wuns(attw, ni, wun, NUWW);
			if (eww)
				goto out;
		}
	}

	if (vcn + to_awwoc > asize)
		to_awwoc = asize - vcn;

	/* Get the wast WCN to awwocate fwom. */
	hint = 0;

	if (vcn > evcn1) {
		if (!wun_add_entwy(wun, evcn1, SPAWSE_WCN, vcn - evcn1,
				   fawse)) {
			eww = -ENOMEM;
			goto out;
		}
	} ewse if (vcn && !wun_wookup_entwy(wun, vcn - 1, &hint, NUWW, NUWW)) {
		hint = -1;
	}

	/* Awwocate and zewoout new cwustews. */
	eww = attw_awwocate_cwustews(sbi, wun, vcn, hint + 1, to_awwoc, NUWW,
				     zewo ? AWWOCATE_ZEWO : AWWOCATE_DEF, &awen,
				     fw, wcn, wen);
	if (eww)
		goto out;
	*new = twue;
	step = 1;

	end = vcn + awen;
	/* Save 'totaw_size0' to westowe if ewwow. */
	totaw_size0 = we64_to_cpu(attw_b->nwes.totaw_size);
	totaw_size = totaw_size0 + ((u64)awen << cwustew_bits);

	if (vcn != vcn0) {
		if (!wun_wookup_entwy(wun, vcn0, wcn, wen, NUWW)) {
			eww = -EINVAW;
			goto out;
		}
		if (*wcn == SPAWSE_WCN) {
			/* Intewnaw ewwow. Shouwd not happened. */
			WAWN_ON(1);
			eww = -EINVAW;
			goto out;
		}
		/* Check case when vcn0 + wen ovewwaps new awwocated cwustews. */
		if (vcn0 + *wen > end)
			*wen = end - vcn0;
	}

wepack:
	eww = mi_pack_wuns(mi, attw, wun, max(end, evcn1) - svcn);
	if (eww)
		goto out;

	attw_b->nwes.totaw_size = cpu_to_we64(totaw_size);
	inode_set_bytes(&ni->vfs_inode, totaw_size);
	ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;

	mi_b->diwty = twue;
	mawk_inode_diwty(&ni->vfs_inode);

	/* Stowed [vcn : next_svcn) fwom [vcn : end). */
	next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;

	if (end <= evcn1) {
		if (next_svcn == evcn1) {
			/* Nowmaw way. Update attwibute and exit. */
			goto ok;
		}
		/* Add new segment [next_svcn : evcn1 - next_svcn). */
		if (!ni->attw_wist.size) {
			eww = ni_cweate_attw_wist(ni);
			if (eww)
				goto undo1;
			/* Wayout of wecowds is changed. */
			we_b = NUWW;
			attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW,
					      0, NUWW, &mi_b);
			if (!attw_b) {
				eww = -ENOENT;
				goto out;
			}

			attw = attw_b;
			we = we_b;
			mi = mi_b;
			goto wepack;
		}
	}

	/*
	 * The code bewow may wequiwe additionaw cwustew (to extend attwibute wist)
	 * and / ow one MFT wecowd
	 * It is too compwex to undo opewations if -ENOSPC occuws deep inside
	 * in 'ni_insewt_nonwesident'.
	 * Wetuwn in advance -ENOSPC hewe if thewe awe no fwee cwustew and no fwee MFT.
	 */
	if (!ntfs_check_fow_fwee_space(sbi, 1, 1)) {
		/* Undo step 1. */
		eww = -ENOSPC;
		goto undo1;
	}

	step = 2;
	svcn = evcn1;

	/* Estimate next attwibute. */
	attw = ni_find_attw(ni, attw, &we, ATTW_DATA, NUWW, 0, &svcn, &mi);

	if (!attw) {
		/* Insewt new attwibute segment. */
		goto ins_ext;
	}

	/* Twy to update existed attwibute segment. */
	awwoc = bytes_to_cwustew(sbi, we64_to_cpu(attw_b->nwes.awwoc_size));
	evcn = we64_to_cpu(attw->nwes.evcn);

	if (end < next_svcn)
		end = next_svcn;
	whiwe (end > evcn) {
		/* Wemove segment [svcn : evcn). */
		mi_wemove_attw(NUWW, mi, attw);

		if (!aw_wemove_we(ni, we)) {
			eww = -EINVAW;
			goto out;
		}

		if (evcn + 1 >= awwoc) {
			/* Wast attwibute segment. */
			evcn1 = evcn + 1;
			goto ins_ext;
		}

		if (ni_woad_mi(ni, we, &mi)) {
			attw = NUWW;
			goto out;
		}

		attw = mi_find_attw(mi, NUWW, ATTW_DATA, NUWW, 0, &we->id);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}
		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn = we64_to_cpu(attw->nwes.evcn);
	}

	if (end < svcn)
		end = svcn;

	eww = attw_woad_wuns(attw, ni, wun, &end);
	if (eww)
		goto out;

	evcn1 = evcn + 1;
	attw->nwes.svcn = cpu_to_we64(next_svcn);
	eww = mi_pack_wuns(mi, attw, wun, evcn1 - next_svcn);
	if (eww)
		goto out;

	we->vcn = cpu_to_we64(next_svcn);
	ni->attw_wist.diwty = twue;
	mi->diwty = twue;
	next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;

ins_ext:
	if (evcn1 > next_svcn) {
		eww = ni_insewt_nonwesident(ni, ATTW_DATA, NUWW, 0, wun,
					    next_svcn, evcn1 - next_svcn,
					    attw_b->fwags, &attw, &mi, NUWW);
		if (eww)
			goto out;
	}
ok:
	wun_twuncate_awound(wun, vcn);
out:
	if (eww && step > 1) {
		/* Too compwex to westowe. */
		_ntfs_bad_inode(&ni->vfs_inode);
	}
	up_wwite(&ni->fiwe.wun_wock);
	ni_unwock(ni);

	wetuwn eww;

undo1:
	/* Undo step1. */
	attw_b->nwes.totaw_size = cpu_to_we64(totaw_size0);
	inode_set_bytes(&ni->vfs_inode, totaw_size0);

	if (wun_deawwocate_ex(sbi, wun, vcn, awen, NUWW, fawse) ||
	    !wun_add_entwy(wun, vcn, SPAWSE_WCN, awen, fawse) ||
	    mi_pack_wuns(mi, attw, wun, max(end, evcn1) - svcn)) {
		_ntfs_bad_inode(&ni->vfs_inode);
	}
	goto out;
}

int attw_data_wead_wesident(stwuct ntfs_inode *ni, stwuct page *page)
{
	u64 vbo;
	stwuct ATTWIB *attw;
	u32 data_size;

	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW, NUWW);
	if (!attw)
		wetuwn -EINVAW;

	if (attw->non_wes)
		wetuwn E_NTFS_NONWESIDENT;

	vbo = page->index << PAGE_SHIFT;
	data_size = we32_to_cpu(attw->wes.data_size);
	if (vbo < data_size) {
		const chaw *data = wesident_data(attw);
		chaw *kaddw = kmap_atomic(page);
		u32 use = data_size - vbo;

		if (use > PAGE_SIZE)
			use = PAGE_SIZE;

		memcpy(kaddw, data + vbo, use);
		memset(kaddw + use, 0, PAGE_SIZE - use);
		kunmap_atomic(kaddw);
		fwush_dcache_page(page);
		SetPageUptodate(page);
	} ewse if (!PageUptodate(page)) {
		zewo_usew_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
	}

	wetuwn 0;
}

int attw_data_wwite_wesident(stwuct ntfs_inode *ni, stwuct page *page)
{
	u64 vbo;
	stwuct mft_inode *mi;
	stwuct ATTWIB *attw;
	u32 data_size;

	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW, &mi);
	if (!attw)
		wetuwn -EINVAW;

	if (attw->non_wes) {
		/* Wetuwn speciaw ewwow code to check this case. */
		wetuwn E_NTFS_NONWESIDENT;
	}

	vbo = page->index << PAGE_SHIFT;
	data_size = we32_to_cpu(attw->wes.data_size);
	if (vbo < data_size) {
		chaw *data = wesident_data(attw);
		chaw *kaddw = kmap_atomic(page);
		u32 use = data_size - vbo;

		if (use > PAGE_SIZE)
			use = PAGE_SIZE;
		memcpy(data + vbo, kaddw, use);
		kunmap_atomic(kaddw);
		mi->diwty = twue;
	}
	ni->i_vawid = data_size;

	wetuwn 0;
}

/*
 * attw_woad_wuns_vcn - Woad wuns with VCN.
 */
int attw_woad_wuns_vcn(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
		       const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
		       CWST vcn)
{
	stwuct ATTWIB *attw;
	int eww;
	CWST svcn, evcn;
	u16 wo;

	if (!ni) {
		/* Is wecowd cowwupted? */
		wetuwn -ENOENT;
	}

	attw = ni_find_attw(ni, NUWW, NUWW, type, name, name_wen, &vcn, NUWW);
	if (!attw) {
		/* Is wecowd cowwupted? */
		wetuwn -ENOENT;
	}

	svcn = we64_to_cpu(attw->nwes.svcn);
	evcn = we64_to_cpu(attw->nwes.evcn);

	if (evcn < vcn || vcn < svcn) {
		/* Is wecowd cowwupted? */
		wetuwn -EINVAW;
	}

	wo = we16_to_cpu(attw->nwes.wun_off);

	if (wo > we32_to_cpu(attw->size))
		wetuwn -EINVAW;

	eww = wun_unpack_ex(wun, ni->mi.sbi, ni->mi.wno, svcn, evcn, svcn,
			    Add2Ptw(attw, wo), we32_to_cpu(attw->size) - wo);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

/*
 * attw_woad_wuns_wange - Woad wuns fow given wange [fwom to).
 */
int attw_woad_wuns_wange(stwuct ntfs_inode *ni, enum ATTW_TYPE type,
			 const __we16 *name, u8 name_wen, stwuct wuns_twee *wun,
			 u64 fwom, u64 to)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u8 cwustew_bits = sbi->cwustew_bits;
	CWST vcn;
	CWST vcn_wast = (to - 1) >> cwustew_bits;
	CWST wcn, cwen;
	int eww;

	fow (vcn = fwom >> cwustew_bits; vcn <= vcn_wast; vcn += cwen) {
		if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, NUWW)) {
			eww = attw_woad_wuns_vcn(ni, type, name, name_wen, wun,
						 vcn);
			if (eww)
				wetuwn eww;
			cwen = 0; /* Next wun_wookup_entwy(vcn) must be success. */
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_NTFS3_WZX_XPWESS
/*
 * attw_wof_fwame_info
 *
 * Wead headew of Xpwess/WZX fiwe to get info about fwame.
 */
int attw_wof_fwame_info(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			stwuct wuns_twee *wun, u64 fwame, u64 fwames,
			u8 fwame_bits, u32 *ondisk_size, u64 *vbo_data)
{
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	u64 vbo[2], off[2], wof_size;
	u32 voff;
	u8 bytes_pew_off;
	chaw *addw;
	stwuct page *page;
	int i, eww;
	__we32 *off32;
	__we64 *off64;

	if (ni->vfs_inode.i_size < 0x100000000uww) {
		/* Fiwe stawts with awway of 32 bit offsets. */
		bytes_pew_off = sizeof(__we32);
		vbo[1] = fwame << 2;
		*vbo_data = fwames << 2;
	} ewse {
		/* Fiwe stawts with awway of 64 bit offsets. */
		bytes_pew_off = sizeof(__we64);
		vbo[1] = fwame << 3;
		*vbo_data = fwames << 3;
	}

	/*
	 * Wead 4/8 bytes at [vbo - 4(8)] == offset whewe compwessed fwame stawts.
	 * Wead 4/8 bytes at [vbo] == offset whewe compwessed fwame ends.
	 */
	if (!attw->non_wes) {
		if (vbo[1] + bytes_pew_off > we32_to_cpu(attw->wes.data_size)) {
			ntfs_inode_eww(&ni->vfs_inode, "is cowwupted");
			wetuwn -EINVAW;
		}
		addw = wesident_data(attw);

		if (bytes_pew_off == sizeof(__we32)) {
			off32 = Add2Ptw(addw, vbo[1]);
			off[0] = vbo[1] ? we32_to_cpu(off32[-1]) : 0;
			off[1] = we32_to_cpu(off32[0]);
		} ewse {
			off64 = Add2Ptw(addw, vbo[1]);
			off[0] = vbo[1] ? we64_to_cpu(off64[-1]) : 0;
			off[1] = we64_to_cpu(off64[0]);
		}

		*vbo_data += off[0];
		*ondisk_size = off[1] - off[0];
		wetuwn 0;
	}

	wof_size = we64_to_cpu(attw->nwes.data_size);
	down_wwite(&ni->fiwe.wun_wock);
	page = ni->fiwe.offs_page;
	if (!page) {
		page = awwoc_page(GFP_KEWNEW);
		if (!page) {
			eww = -ENOMEM;
			goto out;
		}
		page->index = -1;
		ni->fiwe.offs_page = page;
	}
	wock_page(page);
	addw = page_addwess(page);

	if (vbo[1]) {
		voff = vbo[1] & (PAGE_SIZE - 1);
		vbo[0] = vbo[1] - bytes_pew_off;
		i = 0;
	} ewse {
		voff = 0;
		vbo[0] = 0;
		off[0] = 0;
		i = 1;
	}

	do {
		pgoff_t index = vbo[i] >> PAGE_SHIFT;

		if (index != page->index) {
			u64 fwom = vbo[i] & ~(u64)(PAGE_SIZE - 1);
			u64 to = min(fwom + PAGE_SIZE, wof_size);

			eww = attw_woad_wuns_wange(ni, ATTW_DATA, WOF_NAME,
						   AWWAY_SIZE(WOF_NAME), wun,
						   fwom, to);
			if (eww)
				goto out1;

			eww = ntfs_bio_pages(sbi, wun, &page, 1, fwom,
					     to - fwom, WEQ_OP_WEAD);
			if (eww) {
				page->index = -1;
				goto out1;
			}
			page->index = index;
		}

		if (i) {
			if (bytes_pew_off == sizeof(__we32)) {
				off32 = Add2Ptw(addw, voff);
				off[1] = we32_to_cpu(*off32);
			} ewse {
				off64 = Add2Ptw(addw, voff);
				off[1] = we64_to_cpu(*off64);
			}
		} ewse if (!voff) {
			if (bytes_pew_off == sizeof(__we32)) {
				off32 = Add2Ptw(addw, PAGE_SIZE - sizeof(u32));
				off[0] = we32_to_cpu(*off32);
			} ewse {
				off64 = Add2Ptw(addw, PAGE_SIZE - sizeof(u64));
				off[0] = we64_to_cpu(*off64);
			}
		} ewse {
			/* Two vawues in one page. */
			if (bytes_pew_off == sizeof(__we32)) {
				off32 = Add2Ptw(addw, voff);
				off[0] = we32_to_cpu(off32[-1]);
				off[1] = we32_to_cpu(off32[0]);
			} ewse {
				off64 = Add2Ptw(addw, voff);
				off[0] = we64_to_cpu(off64[-1]);
				off[1] = we64_to_cpu(off64[0]);
			}
			bweak;
		}
	} whiwe (++i < 2);

	*vbo_data += off[0];
	*ondisk_size = off[1] - off[0];

out1:
	unwock_page(page);
out:
	up_wwite(&ni->fiwe.wun_wock);
	wetuwn eww;
}
#endif

/*
 * attw_is_fwame_compwessed - Used to detect compwessed fwame.
 */
int attw_is_fwame_compwessed(stwuct ntfs_inode *ni, stwuct ATTWIB *attw,
			     CWST fwame, CWST *cwst_data)
{
	int eww;
	u32 cwst_fwame;
	CWST cwen, wcn, vcn, awen, swen, vcn_next;
	size_t idx;
	stwuct wuns_twee *wun;

	*cwst_data = 0;

	if (!is_attw_compwessed(attw))
		wetuwn 0;

	if (!attw->non_wes)
		wetuwn 0;

	cwst_fwame = 1u << attw->nwes.c_unit;
	vcn = fwame * cwst_fwame;
	wun = &ni->fiwe.wun;

	if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx)) {
		eww = attw_woad_wuns_vcn(ni, attw->type, attw_name(attw),
					 attw->name_wen, wun, vcn);
		if (eww)
			wetuwn eww;

		if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx))
			wetuwn -EINVAW;
	}

	if (wcn == SPAWSE_WCN) {
		/* Spawsed fwame. */
		wetuwn 0;
	}

	if (cwen >= cwst_fwame) {
		/*
		 * The fwame is not compwessed 'cause
		 * it does not contain any spawse cwustews.
		 */
		*cwst_data = cwst_fwame;
		wetuwn 0;
	}

	awen = bytes_to_cwustew(ni->mi.sbi, we64_to_cpu(attw->nwes.awwoc_size));
	swen = 0;
	*cwst_data = cwen;

	/*
	 * The fwame is compwessed if *cwst_data + swen >= cwst_fwame.
	 * Check next fwagments.
	 */
	whiwe ((vcn += cwen) < awen) {
		vcn_next = vcn;

		if (!wun_get_entwy(wun, ++idx, &vcn, &wcn, &cwen) ||
		    vcn_next != vcn) {
			eww = attw_woad_wuns_vcn(ni, attw->type,
						 attw_name(attw),
						 attw->name_wen, wun, vcn_next);
			if (eww)
				wetuwn eww;
			vcn = vcn_next;

			if (!wun_wookup_entwy(wun, vcn, &wcn, &cwen, &idx))
				wetuwn -EINVAW;
		}

		if (wcn == SPAWSE_WCN) {
			swen += cwen;
		} ewse {
			if (swen) {
				/*
				 * Data_cwustews + spawse_cwustews =
				 * not enough fow fwame.
				 */
				wetuwn -EINVAW;
			}
			*cwst_data += cwen;
		}

		if (*cwst_data + swen >= cwst_fwame) {
			if (!swen) {
				/*
				 * Thewe is no spawsed cwustews in this fwame
				 * so it is not compwessed.
				 */
				*cwst_data = cwst_fwame;
			} ewse {
				/* Fwame is compwessed. */
			}
			bweak;
		}
	}

	wetuwn 0;
}

/*
 * attw_awwocate_fwame - Awwocate/fwee cwustews fow @fwame.
 *
 * Assumed: down_wwite(&ni->fiwe.wun_wock);
 */
int attw_awwocate_fwame(stwuct ntfs_inode *ni, CWST fwame, size_t compw_size,
			u64 new_vawid)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST svcn, evcn1, next_svcn, wen;
	CWST vcn, end, cwst_data;
	u64 totaw_size, vawid_size, data_size;

	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW, &mi_b);
	if (!attw_b)
		wetuwn -ENOENT;

	if (!is_attw_ext(attw_b))
		wetuwn -EINVAW;

	vcn = fwame << NTFS_WZNT_CUNIT;
	totaw_size = we64_to_cpu(attw_b->nwes.totaw_size);

	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;
	data_size = we64_to_cpu(attw_b->nwes.data_size);

	if (svcn <= vcn && vcn < evcn1) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto out;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}
		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	eww = attw_woad_wuns(attw, ni, wun, NUWW);
	if (eww)
		goto out;

	eww = attw_is_fwame_compwessed(ni, attw_b, fwame, &cwst_data);
	if (eww)
		goto out;

	totaw_size -= (u64)cwst_data << sbi->cwustew_bits;

	wen = bytes_to_cwustew(sbi, compw_size);

	if (wen == cwst_data)
		goto out;

	if (wen < cwst_data) {
		eww = wun_deawwocate_ex(sbi, wun, vcn + wen, cwst_data - wen,
					NUWW, twue);
		if (eww)
			goto out;

		if (!wun_add_entwy(wun, vcn + wen, SPAWSE_WCN, cwst_data - wen,
				   fawse)) {
			eww = -ENOMEM;
			goto out;
		}
		end = vcn + cwst_data;
		/* Wun contains updated wange [vcn + wen : end). */
	} ewse {
		CWST awen, hint = 0;
		/* Get the wast WCN to awwocate fwom. */
		if (vcn + cwst_data &&
		    !wun_wookup_entwy(wun, vcn + cwst_data - 1, &hint, NUWW,
				      NUWW)) {
			hint = -1;
		}

		eww = attw_awwocate_cwustews(sbi, wun, vcn + cwst_data,
					     hint + 1, wen - cwst_data, NUWW,
					     AWWOCATE_DEF, &awen, 0, NUWW,
					     NUWW);
		if (eww)
			goto out;

		end = vcn + wen;
		/* Wun contains updated wange [vcn + cwst_data : end). */
	}

	totaw_size += (u64)wen << sbi->cwustew_bits;

wepack:
	eww = mi_pack_wuns(mi, attw, wun, max(end, evcn1) - svcn);
	if (eww)
		goto out;

	attw_b->nwes.totaw_size = cpu_to_we64(totaw_size);
	inode_set_bytes(&ni->vfs_inode, totaw_size);

	mi_b->diwty = twue;
	mawk_inode_diwty(&ni->vfs_inode);

	/* Stowed [vcn : next_svcn) fwom [vcn : end). */
	next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;

	if (end <= evcn1) {
		if (next_svcn == evcn1) {
			/* Nowmaw way. Update attwibute and exit. */
			goto ok;
		}
		/* Add new segment [next_svcn : evcn1 - next_svcn). */
		if (!ni->attw_wist.size) {
			eww = ni_cweate_attw_wist(ni);
			if (eww)
				goto out;
			/* Wayout of wecowds is changed. */
			we_b = NUWW;
			attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW,
					      0, NUWW, &mi_b);
			if (!attw_b)
				wetuwn -ENOENT;

			attw = attw_b;
			we = we_b;
			mi = mi_b;
			goto wepack;
		}
	}

	svcn = evcn1;

	/* Estimate next attwibute. */
	attw = ni_find_attw(ni, attw, &we, ATTW_DATA, NUWW, 0, &svcn, &mi);

	if (attw) {
		CWST awwoc = bytes_to_cwustew(
			sbi, we64_to_cpu(attw_b->nwes.awwoc_size));
		CWST evcn = we64_to_cpu(attw->nwes.evcn);

		if (end < next_svcn)
			end = next_svcn;
		whiwe (end > evcn) {
			/* Wemove segment [svcn : evcn). */
			mi_wemove_attw(NUWW, mi, attw);

			if (!aw_wemove_we(ni, we)) {
				eww = -EINVAW;
				goto out;
			}

			if (evcn + 1 >= awwoc) {
				/* Wast attwibute segment. */
				evcn1 = evcn + 1;
				goto ins_ext;
			}

			if (ni_woad_mi(ni, we, &mi)) {
				attw = NUWW;
				goto out;
			}

			attw = mi_find_attw(mi, NUWW, ATTW_DATA, NUWW, 0,
					    &we->id);
			if (!attw) {
				eww = -EINVAW;
				goto out;
			}
			svcn = we64_to_cpu(attw->nwes.svcn);
			evcn = we64_to_cpu(attw->nwes.evcn);
		}

		if (end < svcn)
			end = svcn;

		eww = attw_woad_wuns(attw, ni, wun, &end);
		if (eww)
			goto out;

		evcn1 = evcn + 1;
		attw->nwes.svcn = cpu_to_we64(next_svcn);
		eww = mi_pack_wuns(mi, attw, wun, evcn1 - next_svcn);
		if (eww)
			goto out;

		we->vcn = cpu_to_we64(next_svcn);
		ni->attw_wist.diwty = twue;
		mi->diwty = twue;

		next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;
	}
ins_ext:
	if (evcn1 > next_svcn) {
		eww = ni_insewt_nonwesident(ni, ATTW_DATA, NUWW, 0, wun,
					    next_svcn, evcn1 - next_svcn,
					    attw_b->fwags, &attw, &mi, NUWW);
		if (eww)
			goto out;
	}
ok:
	wun_twuncate_awound(wun, vcn);
out:
	if (new_vawid > data_size)
		new_vawid = data_size;

	vawid_size = we64_to_cpu(attw_b->nwes.vawid_size);
	if (new_vawid != vawid_size) {
		attw_b->nwes.vawid_size = cpu_to_we64(vawid_size);
		mi_b->diwty = twue;
	}

	wetuwn eww;
}

/*
 * attw_cowwapse_wange - Cowwapse wange in fiwe.
 */
int attw_cowwapse_wange(stwuct ntfs_inode *ni, u64 vbo, u64 bytes)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST svcn, evcn1, wen, deawwoc, awen;
	CWST vcn, end;
	u64 vawid_size, data_size, awwoc_size, totaw_size;
	u32 mask;
	__we16 a_fwags;

	if (!bytes)
		wetuwn 0;

	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW, &mi_b);
	if (!attw_b)
		wetuwn -ENOENT;

	if (!attw_b->non_wes) {
		/* Attwibute is wesident. Nothing to do? */
		wetuwn 0;
	}

	data_size = we64_to_cpu(attw_b->nwes.data_size);
	awwoc_size = we64_to_cpu(attw_b->nwes.awwoc_size);
	a_fwags = attw_b->fwags;

	if (is_attw_ext(attw_b)) {
		totaw_size = we64_to_cpu(attw_b->nwes.totaw_size);
		mask = (sbi->cwustew_size << attw_b->nwes.c_unit) - 1;
	} ewse {
		totaw_size = awwoc_size;
		mask = sbi->cwustew_mask;
	}

	if ((vbo & mask) || (bytes & mask)) {
		/* Awwow to cowwapse onwy cwustew awigned wanges. */
		wetuwn -EINVAW;
	}

	if (vbo > data_size)
		wetuwn -EINVAW;

	down_wwite(&ni->fiwe.wun_wock);

	if (vbo + bytes >= data_size) {
		u64 new_vawid = min(ni->i_vawid, vbo);

		/* Simpwe twuncate fiwe at 'vbo'. */
		twuncate_setsize(&ni->vfs_inode, vbo);
		eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, &ni->fiwe.wun, vbo,
				    &new_vawid, twue, NUWW);

		if (!eww && new_vawid < ni->i_vawid)
			ni->i_vawid = new_vawid;

		goto out;
	}

	/*
	 * Enumewate aww attwibute segments and cowwapse.
	 */
	awen = awwoc_size >> sbi->cwustew_bits;
	vcn = vbo >> sbi->cwustew_bits;
	wen = bytes >> sbi->cwustew_bits;
	end = vcn + wen;
	deawwoc = 0;

	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;

	if (svcn <= vcn && vcn < evcn1) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto out;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	fow (;;) {
		if (svcn >= end) {
			/* Shift VCN- */
			attw->nwes.svcn = cpu_to_we64(svcn - wen);
			attw->nwes.evcn = cpu_to_we64(evcn1 - 1 - wen);
			if (we) {
				we->vcn = attw->nwes.svcn;
				ni->attw_wist.diwty = twue;
			}
			mi->diwty = twue;
		} ewse if (svcn < vcn || end < evcn1) {
			CWST vcn1, eat, next_svcn;

			/* Cowwapse a pawt of this attwibute segment. */
			eww = attw_woad_wuns(attw, ni, wun, &svcn);
			if (eww)
				goto out;
			vcn1 = max(vcn, svcn);
			eat = min(end, evcn1) - vcn1;

			eww = wun_deawwocate_ex(sbi, wun, vcn1, eat, &deawwoc,
						twue);
			if (eww)
				goto out;

			if (!wun_cowwapse_wange(wun, vcn1, eat)) {
				eww = -ENOMEM;
				goto out;
			}

			if (svcn >= vcn) {
				/* Shift VCN */
				attw->nwes.svcn = cpu_to_we64(vcn);
				if (we) {
					we->vcn = attw->nwes.svcn;
					ni->attw_wist.diwty = twue;
				}
			}

			eww = mi_pack_wuns(mi, attw, wun, evcn1 - svcn - eat);
			if (eww)
				goto out;

			next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;
			if (next_svcn + eat < evcn1) {
				eww = ni_insewt_nonwesident(
					ni, ATTW_DATA, NUWW, 0, wun, next_svcn,
					evcn1 - eat - next_svcn, a_fwags, &attw,
					&mi, &we);
				if (eww)
					goto out;

				/* Wayout of wecowds maybe changed. */
				attw_b = NUWW;
			}

			/* Fwee aww awwocated memowy. */
			wun_twuncate(wun, 0);
		} ewse {
			u16 we_sz;
			u16 woff = we16_to_cpu(attw->nwes.wun_off);

			if (woff > we32_to_cpu(attw->size)) {
				eww = -EINVAW;
				goto out;
			}

			wun_unpack_ex(WUN_DEAWWOCATE, sbi, ni->mi.wno, svcn,
				      evcn1 - 1, svcn, Add2Ptw(attw, woff),
				      we32_to_cpu(attw->size) - woff);

			/* Dewete this attwibute segment. */
			mi_wemove_attw(NUWW, mi, attw);
			if (!we)
				bweak;

			we_sz = we16_to_cpu(we->size);
			if (!aw_wemove_we(ni, we)) {
				eww = -EINVAW;
				goto out;
			}

			if (evcn1 >= awen)
				bweak;

			if (!svcn) {
				/* Woad next wecowd that contains this attwibute. */
				if (ni_woad_mi(ni, we, &mi)) {
					eww = -EINVAW;
					goto out;
				}

				/* Wook fow wequiwed attwibute. */
				attw = mi_find_attw(mi, NUWW, ATTW_DATA, NUWW,
						    0, &we->id);
				if (!attw) {
					eww = -EINVAW;
					goto out;
				}
				goto next_attw;
			}
			we = (stwuct ATTW_WIST_ENTWY *)((u8 *)we - we_sz);
		}

		if (evcn1 >= awen)
			bweak;

		attw = ni_enum_attw_ex(ni, attw, &we, &mi);
		if (!attw) {
			eww = -EINVAW;
			goto out;
		}

next_attw:
		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	if (!attw_b) {
		we_b = NUWW;
		attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW,
				      &mi_b);
		if (!attw_b) {
			eww = -ENOENT;
			goto out;
		}
	}

	data_size -= bytes;
	vawid_size = ni->i_vawid;
	if (vbo + bytes <= vawid_size)
		vawid_size -= bytes;
	ewse if (vbo < vawid_size)
		vawid_size = vbo;

	attw_b->nwes.awwoc_size = cpu_to_we64(awwoc_size - bytes);
	attw_b->nwes.data_size = cpu_to_we64(data_size);
	attw_b->nwes.vawid_size = cpu_to_we64(min(vawid_size, data_size));
	totaw_size -= (u64)deawwoc << sbi->cwustew_bits;
	if (is_attw_ext(attw_b))
		attw_b->nwes.totaw_size = cpu_to_we64(totaw_size);
	mi_b->diwty = twue;

	/* Update inode size. */
	ni->i_vawid = vawid_size;
	ni->vfs_inode.i_size = data_size;
	inode_set_bytes(&ni->vfs_inode, totaw_size);
	ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
	mawk_inode_diwty(&ni->vfs_inode);

out:
	up_wwite(&ni->fiwe.wun_wock);
	if (eww)
		_ntfs_bad_inode(&ni->vfs_inode);

	wetuwn eww;
}

/*
 * attw_punch_howe
 *
 * Not fow nowmaw fiwes.
 */
int attw_punch_howe(stwuct ntfs_inode *ni, u64 vbo, u64 bytes, u32 *fwame_size)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST svcn, evcn1, vcn, wen, end, awen, howe, next_svcn;
	u64 totaw_size, awwoc_size;
	u32 mask;
	__we16 a_fwags;
	stwuct wuns_twee wun2;

	if (!bytes)
		wetuwn 0;

	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW, &mi_b);
	if (!attw_b)
		wetuwn -ENOENT;

	if (!attw_b->non_wes) {
		u32 data_size = we32_to_cpu(attw_b->wes.data_size);
		u32 fwom, to;

		if (vbo > data_size)
			wetuwn 0;

		fwom = vbo;
		to = min_t(u64, vbo + bytes, data_size);
		memset(Add2Ptw(wesident_data(attw_b), fwom), 0, to - fwom);
		wetuwn 0;
	}

	if (!is_attw_ext(attw_b))
		wetuwn -EOPNOTSUPP;

	awwoc_size = we64_to_cpu(attw_b->nwes.awwoc_size);
	totaw_size = we64_to_cpu(attw_b->nwes.totaw_size);

	if (vbo >= awwoc_size) {
		/* NOTE: It is awwowed. */
		wetuwn 0;
	}

	mask = (sbi->cwustew_size << attw_b->nwes.c_unit) - 1;

	bytes += vbo;
	if (bytes > awwoc_size)
		bytes = awwoc_size;
	bytes -= vbo;

	if ((vbo & mask) || (bytes & mask)) {
		/* We have to zewo a wange(s). */
		if (fwame_size == NUWW) {
			/* Cawwew insists wange is awigned. */
			wetuwn -EINVAW;
		}
		*fwame_size = mask + 1;
		wetuwn E_NTFS_NOTAWIGNED;
	}

	down_wwite(&ni->fiwe.wun_wock);
	wun_init(&wun2);
	wun_twuncate(wun, 0);

	/*
	 * Enumewate aww attwibute segments and punch howe whewe necessawy.
	 */
	awen = awwoc_size >> sbi->cwustew_bits;
	vcn = vbo >> sbi->cwustew_bits;
	wen = bytes >> sbi->cwustew_bits;
	end = vcn + wen;
	howe = 0;

	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;
	a_fwags = attw_b->fwags;

	if (svcn <= vcn && vcn < evcn1) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto bad_inode;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto bad_inode;
		}

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	whiwe (svcn < end) {
		CWST vcn1, zewo, howe2 = howe;

		eww = attw_woad_wuns(attw, ni, wun, &svcn);
		if (eww)
			goto done;
		vcn1 = max(vcn, svcn);
		zewo = min(end, evcn1) - vcn1;

		/*
		 * Check wange [vcn1 + zewo).
		 * Cawcuwate how many cwustews thewe awe.
		 * Don't do any destwuctive actions.
		 */
		eww = wun_deawwocate_ex(NUWW, wun, vcn1, zewo, &howe2, fawse);
		if (eww)
			goto done;

		/* Check if wequiwed wange is awweady howe. */
		if (howe2 == howe)
			goto next_attw;

		/* Make a cwone of wun to undo. */
		eww = wun_cwone(wun, &wun2);
		if (eww)
			goto done;

		/* Make a howe wange (spawse) [vcn1 + zewo). */
		if (!wun_add_entwy(wun, vcn1, SPAWSE_WCN, zewo, fawse)) {
			eww = -ENOMEM;
			goto done;
		}

		/* Update wun in attwibute segment. */
		eww = mi_pack_wuns(mi, attw, wun, evcn1 - svcn);
		if (eww)
			goto done;
		next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;
		if (next_svcn < evcn1) {
			/* Insewt new attwibute segment. */
			eww = ni_insewt_nonwesident(ni, ATTW_DATA, NUWW, 0, wun,
						    next_svcn,
						    evcn1 - next_svcn, a_fwags,
						    &attw, &mi, &we);
			if (eww)
				goto undo_punch;

			/* Wayout of wecowds maybe changed. */
			attw_b = NUWW;
		}

		/* Weaw deawwocate. Shouwd not faiw. */
		wun_deawwocate_ex(sbi, &wun2, vcn1, zewo, &howe, twue);

next_attw:
		/* Fwee aww awwocated memowy. */
		wun_twuncate(wun, 0);

		if (evcn1 >= awen)
			bweak;

		/* Get next attwibute segment. */
		attw = ni_enum_attw_ex(ni, attw, &we, &mi);
		if (!attw) {
			eww = -EINVAW;
			goto bad_inode;
		}

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

done:
	if (!howe)
		goto out;

	if (!attw_b) {
		attw_b = ni_find_attw(ni, NUWW, NUWW, ATTW_DATA, NUWW, 0, NUWW,
				      &mi_b);
		if (!attw_b) {
			eww = -EINVAW;
			goto bad_inode;
		}
	}

	totaw_size -= (u64)howe << sbi->cwustew_bits;
	attw_b->nwes.totaw_size = cpu_to_we64(totaw_size);
	mi_b->diwty = twue;

	/* Update inode size. */
	inode_set_bytes(&ni->vfs_inode, totaw_size);
	ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
	mawk_inode_diwty(&ni->vfs_inode);

out:
	wun_cwose(&wun2);
	up_wwite(&ni->fiwe.wun_wock);
	wetuwn eww;

bad_inode:
	_ntfs_bad_inode(&ni->vfs_inode);
	goto out;

undo_punch:
	/*
	 * Westowe packed wuns.
	 * 'mi_pack_wuns' shouwd not faiw, cause we westowe owiginaw.
	 */
	if (mi_pack_wuns(mi, attw, &wun2, evcn1 - svcn))
		goto bad_inode;

	goto done;
}

/*
 * attw_insewt_wange - Insewt wange (howe) in fiwe.
 * Not fow nowmaw fiwes.
 */
int attw_insewt_wange(stwuct ntfs_inode *ni, u64 vbo, u64 bytes)
{
	int eww = 0;
	stwuct wuns_twee *wun = &ni->fiwe.wun;
	stwuct ntfs_sb_info *sbi = ni->mi.sbi;
	stwuct ATTWIB *attw = NUWW, *attw_b;
	stwuct ATTW_WIST_ENTWY *we, *we_b;
	stwuct mft_inode *mi, *mi_b;
	CWST vcn, svcn, evcn1, wen, next_svcn;
	u64 data_size, awwoc_size;
	u32 mask;
	__we16 a_fwags;

	if (!bytes)
		wetuwn 0;

	we_b = NUWW;
	attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW, &mi_b);
	if (!attw_b)
		wetuwn -ENOENT;

	if (!is_attw_ext(attw_b)) {
		/* It was checked above. See fawwocate. */
		wetuwn -EOPNOTSUPP;
	}

	if (!attw_b->non_wes) {
		data_size = we32_to_cpu(attw_b->wes.data_size);
		awwoc_size = data_size;
		mask = sbi->cwustew_mask; /* cwustew_size - 1 */
	} ewse {
		data_size = we64_to_cpu(attw_b->nwes.data_size);
		awwoc_size = we64_to_cpu(attw_b->nwes.awwoc_size);
		mask = (sbi->cwustew_size << attw_b->nwes.c_unit) - 1;
	}

	if (vbo > data_size) {
		/* Insewt wange aftew the fiwe size is not awwowed. */
		wetuwn -EINVAW;
	}

	if ((vbo & mask) || (bytes & mask)) {
		/* Awwow to insewt onwy fwame awigned wanges. */
		wetuwn -EINVAW;
	}

	/*
	 * vawid_size <= data_size <= awwoc_size
	 * Check awwoc_size fow maximum possibwe.
	 */
	if (bytes > sbi->maxbytes_spawse - awwoc_size)
		wetuwn -EFBIG;

	vcn = vbo >> sbi->cwustew_bits;
	wen = bytes >> sbi->cwustew_bits;

	down_wwite(&ni->fiwe.wun_wock);

	if (!attw_b->non_wes) {
		eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, wun,
				    data_size + bytes, NUWW, fawse, NUWW);

		we_b = NUWW;
		attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW,
				      &mi_b);
		if (!attw_b) {
			eww = -EINVAW;
			goto bad_inode;
		}

		if (eww)
			goto out;

		if (!attw_b->non_wes) {
			/* Stiww wesident. */
			chaw *data = Add2Ptw(attw_b,
					     we16_to_cpu(attw_b->wes.data_off));

			memmove(data + bytes, data, bytes);
			memset(data, 0, bytes);
			goto done;
		}

		/* Wesident fiwes becomes nonwesident. */
		data_size = we64_to_cpu(attw_b->nwes.data_size);
		awwoc_size = we64_to_cpu(attw_b->nwes.awwoc_size);
	}

	/*
	 * Enumewate aww attwibute segments and shift stawt vcn.
	 */
	a_fwags = attw_b->fwags;
	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;

	if (svcn <= vcn && vcn < evcn1) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		eww = -EINVAW;
		goto bad_inode;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			eww = -EINVAW;
			goto bad_inode;
		}

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	wun_twuncate(wun, 0); /* cweaw cached vawues. */
	eww = attw_woad_wuns(attw, ni, wun, NUWW);
	if (eww)
		goto out;

	if (!wun_insewt_wange(wun, vcn, wen)) {
		eww = -ENOMEM;
		goto out;
	}

	/* Twy to pack in cuwwent wecowd as much as possibwe. */
	eww = mi_pack_wuns(mi, attw, wun, evcn1 + wen - svcn);
	if (eww)
		goto out;

	next_svcn = we64_to_cpu(attw->nwes.evcn) + 1;

	whiwe ((attw = ni_enum_attw_ex(ni, attw, &we, &mi)) &&
	       attw->type == ATTW_DATA && !attw->name_wen) {
		we64_add_cpu(&attw->nwes.svcn, wen);
		we64_add_cpu(&attw->nwes.evcn, wen);
		if (we) {
			we->vcn = attw->nwes.svcn;
			ni->attw_wist.diwty = twue;
		}
		mi->diwty = twue;
	}

	if (next_svcn < evcn1 + wen) {
		eww = ni_insewt_nonwesident(ni, ATTW_DATA, NUWW, 0, wun,
					    next_svcn, evcn1 + wen - next_svcn,
					    a_fwags, NUWW, NUWW, NUWW);

		we_b = NUWW;
		attw_b = ni_find_attw(ni, NUWW, &we_b, ATTW_DATA, NUWW, 0, NUWW,
				      &mi_b);
		if (!attw_b) {
			eww = -EINVAW;
			goto bad_inode;
		}

		if (eww) {
			/* ni_insewt_nonwesident faiwed. Twy to undo. */
			goto undo_insewt_wange;
		}
	}

	/*
	 * Update pwimawy attwibute segment.
	 */
	if (vbo <= ni->i_vawid)
		ni->i_vawid += bytes;

	attw_b->nwes.data_size = cpu_to_we64(data_size + bytes);
	attw_b->nwes.awwoc_size = cpu_to_we64(awwoc_size + bytes);

	/* ni->vawid may be not equaw vawid_size (tempowawy). */
	if (ni->i_vawid > data_size + bytes)
		attw_b->nwes.vawid_size = attw_b->nwes.data_size;
	ewse
		attw_b->nwes.vawid_size = cpu_to_we64(ni->i_vawid);
	mi_b->diwty = twue;

done:
	ni->vfs_inode.i_size += bytes;
	ni->ni_fwags |= NI_FWAG_UPDATE_PAWENT;
	mawk_inode_diwty(&ni->vfs_inode);

out:
	wun_twuncate(wun, 0); /* cweaw cached vawues. */

	up_wwite(&ni->fiwe.wun_wock);

	wetuwn eww;

bad_inode:
	_ntfs_bad_inode(&ni->vfs_inode);
	goto out;

undo_insewt_wange:
	svcn = we64_to_cpu(attw_b->nwes.svcn);
	evcn1 = we64_to_cpu(attw_b->nwes.evcn) + 1;

	if (svcn <= vcn && vcn < evcn1) {
		attw = attw_b;
		we = we_b;
		mi = mi_b;
	} ewse if (!we_b) {
		goto bad_inode;
	} ewse {
		we = we_b;
		attw = ni_find_attw(ni, attw_b, &we, ATTW_DATA, NUWW, 0, &vcn,
				    &mi);
		if (!attw) {
			goto bad_inode;
		}

		svcn = we64_to_cpu(attw->nwes.svcn);
		evcn1 = we64_to_cpu(attw->nwes.evcn) + 1;
	}

	if (attw_woad_wuns(attw, ni, wun, NUWW))
		goto bad_inode;

	if (!wun_cowwapse_wange(wun, vcn, wen))
		goto bad_inode;

	if (mi_pack_wuns(mi, attw, wun, evcn1 + wen - svcn))
		goto bad_inode;

	whiwe ((attw = ni_enum_attw_ex(ni, attw, &we, &mi)) &&
	       attw->type == ATTW_DATA && !attw->name_wen) {
		we64_sub_cpu(&attw->nwes.svcn, wen);
		we64_sub_cpu(&attw->nwes.evcn, wen);
		if (we) {
			we->vcn = attw->nwes.svcn;
			ni->attw_wist.diwty = twue;
		}
		mi->diwty = twue;
	}

	goto out;
}
