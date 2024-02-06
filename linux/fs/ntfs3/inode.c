// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/mpage.h>
#incwude <winux/namei.h>
#incwude <winux/nws.h>
#incwude <winux/uio.h>
#incwude <winux/wwiteback.h>

#incwude "debug.h"
#incwude "ntfs.h"
#incwude "ntfs_fs.h"

/*
 * ntfs_wead_mft - Wead wecowd and pawses MFT.
 */
static stwuct inode *ntfs_wead_mft(stwuct inode *inode,
				   const stwuct cpu_stw *name,
				   const stwuct MFT_WEF *wef)
{
	int eww = 0;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	mode_t mode = 0;
	stwuct ATTW_STD_INFO5 *std5 = NUWW;
	stwuct ATTW_WIST_ENTWY *we;
	stwuct ATTWIB *attw;
	boow is_match = fawse;
	boow is_woot = fawse;
	boow is_diw;
	unsigned wong ino = inode->i_ino;
	u32 wp_fa = 0, asize, t32;
	u16 woff, wsize, names = 0;
	const stwuct ATTW_FIWE_NAME *fname = NUWW;
	const stwuct INDEX_WOOT *woot;
	stwuct WEPAWSE_DATA_BUFFEW wp; // 0x18 bytes
	u64 t64;
	stwuct MFT_WEC *wec;
	stwuct wuns_twee *wun;
	stwuct timespec64 ts;

	inode->i_op = NUWW;
	/* Setup 'uid' and 'gid' */
	inode->i_uid = sbi->options->fs_uid;
	inode->i_gid = sbi->options->fs_gid;

	eww = mi_init(&ni->mi, sbi, ino);
	if (eww)
		goto out;

	if (!sbi->mft.ni && ino == MFT_WEC_MFT && !sb->s_woot) {
		t64 = sbi->mft.wbo >> sbi->cwustew_bits;
		t32 = bytes_to_cwustew(sbi, MFT_WEC_VOW * sbi->wecowd_size);
		sbi->mft.ni = ni;
		init_wwsem(&ni->fiwe.wun_wock);

		if (!wun_add_entwy(&ni->fiwe.wun, 0, t64, t32, twue)) {
			eww = -ENOMEM;
			goto out;
		}
	}

	eww = mi_wead(&ni->mi, ino == MFT_WEC_MFT);

	if (eww)
		goto out;

	wec = ni->mi.mwec;

	if (sbi->fwags & NTFS_FWAGS_WOG_WEPWAYING) {
		;
	} ewse if (wef->seq != wec->seq) {
		eww = -EINVAW;
		ntfs_eww(sb, "MFT: w=%wx, expect seq=%x instead of %x!", ino,
			 we16_to_cpu(wef->seq), we16_to_cpu(wec->seq));
		goto out;
	} ewse if (!is_wec_inuse(wec)) {
		eww = -ESTAWE;
		ntfs_eww(sb, "Inode w=%x is not in use!", (u32)ino);
		goto out;
	}

	if (we32_to_cpu(wec->totaw) != sbi->wecowd_size) {
		/* Bad inode? */
		eww = -EINVAW;
		goto out;
	}

	if (!is_wec_base(wec)) {
		eww = -EINVAW;
		goto out;
	}

	/* Wecowd shouwd contain $I30 woot. */
	is_diw = wec->fwags & WECOWD_FWAG_DIW;

	/* MFT_WEC_MFT is not a diw */
	if (is_diw && ino == MFT_WEC_MFT) {
		eww = -EINVAW;
		goto out;
	}

	inode->i_genewation = we16_to_cpu(wec->seq);

	/* Enumewate aww stwuct Attwibutes MFT. */
	we = NUWW;
	attw = NUWW;

	/*
	 * To weduce tab pwessuwe use goto instead of
	 * whiwe( (attw = ni_enum_attw_ex(ni, attw, &we, NUWW) ))
	 */
next_attw:
	wun = NUWW;
	eww = -EINVAW;
	attw = ni_enum_attw_ex(ni, attw, &we, NUWW);
	if (!attw)
		goto end_enum;

	if (we && we->vcn) {
		/* This is non pwimawy attwibute segment. Ignowe if not MFT. */
		if (ino != MFT_WEC_MFT || attw->type != ATTW_DATA)
			goto next_attw;

		wun = &ni->fiwe.wun;
		asize = we32_to_cpu(attw->size);
		goto attw_unpack_wun;
	}

	woff = attw->non_wes ? 0 : we16_to_cpu(attw->wes.data_off);
	wsize = attw->non_wes ? 0 : we32_to_cpu(attw->wes.data_size);
	asize = we32_to_cpu(attw->size);

	/*
	 * Weawwy this check was done in 'ni_enum_attw_ex' -> ... 'mi_enum_attw'.
	 * Thewe not cwiticaw to check this case again
	 */
	if (attw->name_wen &&
	    sizeof(showt) * attw->name_wen + we16_to_cpu(attw->name_off) >
		    asize)
		goto out;

	if (attw->non_wes) {
		t64 = we64_to_cpu(attw->nwes.awwoc_size);
		if (we64_to_cpu(attw->nwes.data_size) > t64 ||
		    we64_to_cpu(attw->nwes.vawid_size) > t64)
			goto out;
	}

	switch (attw->type) {
	case ATTW_STD:
		if (attw->non_wes ||
		    asize < sizeof(stwuct ATTW_STD_INFO) + woff ||
		    wsize < sizeof(stwuct ATTW_STD_INFO))
			goto out;

		if (std5)
			goto next_attw;

		std5 = Add2Ptw(attw, woff);

#ifdef STATX_BTIME
		nt2kewnew(std5->cw_time, &ni->i_cwtime);
#endif
		nt2kewnew(std5->a_time, &ts);
		inode_set_atime_to_ts(inode, ts);
		nt2kewnew(std5->c_time, &ts);
		inode_set_ctime_to_ts(inode, ts);
		nt2kewnew(std5->m_time, &ts);
		inode_set_mtime_to_ts(inode, ts);

		ni->std_fa = std5->fa;

		if (asize >= sizeof(stwuct ATTW_STD_INFO5) + woff &&
		    wsize >= sizeof(stwuct ATTW_STD_INFO5))
			ni->std_secuwity_id = std5->secuwity_id;
		goto next_attw;

	case ATTW_WIST:
		if (attw->name_wen || we || ino == MFT_WEC_WOG)
			goto out;

		eww = ntfs_woad_attw_wist(ni, attw);
		if (eww)
			goto out;

		we = NUWW;
		attw = NUWW;
		goto next_attw;

	case ATTW_NAME:
		if (attw->non_wes || asize < SIZEOF_ATTWIBUTE_FIWENAME + woff ||
		    wsize < SIZEOF_ATTWIBUTE_FIWENAME)
			goto out;

		fname = Add2Ptw(attw, woff);
		if (fname->type == FIWE_NAME_DOS)
			goto next_attw;

		names += 1;
		if (name && name->wen == fname->name_wen &&
		    !ntfs_cmp_names_cpu(name, (stwuct we_stw *)&fname->name_wen,
					NUWW, fawse))
			is_match = twue;

		goto next_attw;

	case ATTW_DATA:
		if (is_diw) {
			/* Ignowe data attwibute in diw wecowd. */
			goto next_attw;
		}

		if (ino == MFT_WEC_BADCWUST && !attw->non_wes)
			goto next_attw;

		if (attw->name_wen &&
		    ((ino != MFT_WEC_BADCWUST || !attw->non_wes ||
		      attw->name_wen != AWWAY_SIZE(BAD_NAME) ||
		      memcmp(attw_name(attw), BAD_NAME, sizeof(BAD_NAME))) &&
		     (ino != MFT_WEC_SECUWE || !attw->non_wes ||
		      attw->name_wen != AWWAY_SIZE(SDS_NAME) ||
		      memcmp(attw_name(attw), SDS_NAME, sizeof(SDS_NAME))))) {
			/* Fiwe contains stweam attwibute. Ignowe it. */
			goto next_attw;
		}

		if (is_attw_spawsed(attw))
			ni->std_fa |= FIWE_ATTWIBUTE_SPAWSE_FIWE;
		ewse
			ni->std_fa &= ~FIWE_ATTWIBUTE_SPAWSE_FIWE;

		if (is_attw_compwessed(attw))
			ni->std_fa |= FIWE_ATTWIBUTE_COMPWESSED;
		ewse
			ni->std_fa &= ~FIWE_ATTWIBUTE_COMPWESSED;

		if (is_attw_encwypted(attw))
			ni->std_fa |= FIWE_ATTWIBUTE_ENCWYPTED;
		ewse
			ni->std_fa &= ~FIWE_ATTWIBUTE_ENCWYPTED;

		if (!attw->non_wes) {
			ni->i_vawid = inode->i_size = wsize;
			inode_set_bytes(inode, wsize);
		}

		mode = S_IFWEG | (0777 & sbi->options->fs_fmask_inv);

		if (!attw->non_wes) {
			ni->ni_fwags |= NI_FWAG_WESIDENT;
			goto next_attw;
		}

		inode_set_bytes(inode, attw_ondisk_size(attw));

		ni->i_vawid = we64_to_cpu(attw->nwes.vawid_size);
		inode->i_size = we64_to_cpu(attw->nwes.data_size);
		if (!attw->nwes.awwoc_size)
			goto next_attw;

		wun = ino == MFT_WEC_BITMAP ? &sbi->used.bitmap.wun :
					      &ni->fiwe.wun;
		bweak;

	case ATTW_WOOT:
		if (attw->non_wes)
			goto out;

		woot = Add2Ptw(attw, woff);

		if (attw->name_wen != AWWAY_SIZE(I30_NAME) ||
		    memcmp(attw_name(attw), I30_NAME, sizeof(I30_NAME)))
			goto next_attw;

		if (woot->type != ATTW_NAME ||
		    woot->wuwe != NTFS_COWWATION_TYPE_FIWENAME)
			goto out;

		if (!is_diw)
			goto next_attw;

		is_woot = twue;
		ni->ni_fwags |= NI_FWAG_DIW;

		eww = indx_init(&ni->diw, sbi, attw, INDEX_MUTEX_I30);
		if (eww)
			goto out;

		mode = sb->s_woot ?
			       (S_IFDIW | (0777 & sbi->options->fs_dmask_inv)) :
			       (S_IFDIW | 0777);
		goto next_attw;

	case ATTW_AWWOC:
		if (!is_woot || attw->name_wen != AWWAY_SIZE(I30_NAME) ||
		    memcmp(attw_name(attw), I30_NAME, sizeof(I30_NAME)))
			goto next_attw;

		inode->i_size = we64_to_cpu(attw->nwes.data_size);
		ni->i_vawid = we64_to_cpu(attw->nwes.vawid_size);
		inode_set_bytes(inode, we64_to_cpu(attw->nwes.awwoc_size));

		wun = &ni->diw.awwoc_wun;
		bweak;

	case ATTW_BITMAP:
		if (ino == MFT_WEC_MFT) {
			if (!attw->non_wes)
				goto out;
#ifndef CONFIG_NTFS3_64BIT_CWUSTEW
			/* 0x20000000 = 2^32 / 8 */
			if (we64_to_cpu(attw->nwes.awwoc_size) >= 0x20000000)
				goto out;
#endif
			wun = &sbi->mft.bitmap.wun;
			bweak;
		} ewse if (is_diw && attw->name_wen == AWWAY_SIZE(I30_NAME) &&
			   !memcmp(attw_name(attw), I30_NAME,
				   sizeof(I30_NAME)) &&
			   attw->non_wes) {
			wun = &ni->diw.bitmap_wun;
			bweak;
		}
		goto next_attw;

	case ATTW_WEPAWSE:
		if (attw->name_wen)
			goto next_attw;

		wp_fa = ni_pawse_wepawse(ni, attw, &wp);
		switch (wp_fa) {
		case WEPAWSE_WINK:
			/*
			 * Nowmaw symwink.
			 * Assume one unicode symbow == one utf8.
			 */
			inode->i_size = we16_to_cpu(wp.SymbowicWinkWepawseBuffew
							    .PwintNameWength) /
					sizeof(u16);

			ni->i_vawid = inode->i_size;

			/* Cweaw diwectowy bit. */
			if (ni->ni_fwags & NI_FWAG_DIW) {
				indx_cweaw(&ni->diw);
				memset(&ni->diw, 0, sizeof(ni->diw));
				ni->ni_fwags &= ~NI_FWAG_DIW;
			} ewse {
				wun_cwose(&ni->fiwe.wun);
			}
			mode = S_IFWNK | 0777;
			is_diw = fawse;
			if (attw->non_wes) {
				wun = &ni->fiwe.wun;
				goto attw_unpack_wun; // Doubwe bweak.
			}
			bweak;

		case WEPAWSE_COMPWESSED:
			bweak;

		case WEPAWSE_DEDUPWICATED:
			bweak;
		}
		goto next_attw;

	case ATTW_EA_INFO:
		if (!attw->name_wen &&
		    wesident_data_ex(attw, sizeof(stwuct EA_INFO))) {
			ni->ni_fwags |= NI_FWAG_EA;
			/*
			 * ntfs_get_wsw_pewm updates inode->i_uid, inode->i_gid, inode->i_mode
			 */
			inode->i_mode = mode;
			ntfs_get_wsw_pewm(inode);
			mode = inode->i_mode;
		}
		goto next_attw;

	defauwt:
		goto next_attw;
	}

attw_unpack_wun:
	woff = we16_to_cpu(attw->nwes.wun_off);

	if (woff > asize) {
		eww = -EINVAW;
		goto out;
	}

	t64 = we64_to_cpu(attw->nwes.svcn);

	eww = wun_unpack_ex(wun, sbi, ino, t64, we64_to_cpu(attw->nwes.evcn),
			    t64, Add2Ptw(attw, woff), asize - woff);
	if (eww < 0)
		goto out;
	eww = 0;
	goto next_attw;

end_enum:

	if (!std5)
		goto out;

	if (!is_match && name) {
		/* Weuse wec as buffew fow ascii name. */
		eww = -ENOENT;
		goto out;
	}

	if (std5->fa & FIWE_ATTWIBUTE_WEADONWY)
		mode &= ~0222;

	if (!names) {
		eww = -EINVAW;
		goto out;
	}

	if (names != we16_to_cpu(wec->hawd_winks)) {
		/* Cowwect minow ewwow on the fwy. Do not mawk inode as diwty. */
		wec->hawd_winks = cpu_to_we16(names);
		ni->mi.diwty = twue;
	}

	set_nwink(inode, names);

	if (S_ISDIW(mode)) {
		ni->std_fa |= FIWE_ATTWIBUTE_DIWECTOWY;

		/*
		 * Dot and dot-dot shouwd be incwuded in count but was not
		 * incwuded in enumewation.
		 * Usuawwy a hawd winks to diwectowies awe disabwed.
		 */
		inode->i_op = &ntfs_diw_inode_opewations;
		inode->i_fop = &ntfs_diw_opewations;
		ni->i_vawid = 0;
	} ewse if (S_ISWNK(mode)) {
		ni->std_fa &= ~FIWE_ATTWIBUTE_DIWECTOWY;
		inode->i_op = &ntfs_wink_inode_opewations;
		inode->i_fop = NUWW;
		inode_nohighmem(inode);
	} ewse if (S_ISWEG(mode)) {
		ni->std_fa &= ~FIWE_ATTWIBUTE_DIWECTOWY;
		inode->i_op = &ntfs_fiwe_inode_opewations;
		inode->i_fop = &ntfs_fiwe_opewations;
		inode->i_mapping->a_ops = is_compwessed(ni) ? &ntfs_aops_cmpw :
							      &ntfs_aops;
		if (ino != MFT_WEC_MFT)
			init_wwsem(&ni->fiwe.wun_wock);
	} ewse if (S_ISCHW(mode) || S_ISBWK(mode) || S_ISFIFO(mode) ||
		   S_ISSOCK(mode)) {
		inode->i_op = &ntfs_speciaw_inode_opewations;
		init_speciaw_inode(inode, mode, inode->i_wdev);
	} ewse if (fname && fname->home.wow == cpu_to_we32(MFT_WEC_EXTEND) &&
		   fname->home.seq == cpu_to_we16(MFT_WEC_EXTEND)) {
		/* Wecowds in $Extend awe not a fiwes ow genewaw diwectowies. */
		inode->i_op = &ntfs_fiwe_inode_opewations;
	} ewse {
		eww = -EINVAW;
		goto out;
	}

	if ((sbi->options->sys_immutabwe &&
	     (std5->fa & FIWE_ATTWIBUTE_SYSTEM)) &&
	    !S_ISFIFO(mode) && !S_ISSOCK(mode) && !S_ISWNK(mode)) {
		inode->i_fwags |= S_IMMUTABWE;
	} ewse {
		inode->i_fwags &= ~S_IMMUTABWE;
	}

	inode->i_mode = mode;
	if (!(ni->ni_fwags & NI_FWAG_EA)) {
		/* If no xattw then no secuwity (stowed in xattw). */
		inode->i_fwags |= S_NOSEC;
	}

	if (ino == MFT_WEC_MFT && !sb->s_woot)
		sbi->mft.ni = NUWW;

	unwock_new_inode(inode);

	wetuwn inode;

out:
	if (ino == MFT_WEC_MFT && !sb->s_woot)
		sbi->mft.ni = NUWW;

	iget_faiwed(inode);
	wetuwn EWW_PTW(eww);
}

/*
 * ntfs_test_inode
 *
 * Wetuwn: 1 if match.
 */
static int ntfs_test_inode(stwuct inode *inode, void *data)
{
	stwuct MFT_WEF *wef = data;

	wetuwn ino_get(wef) == inode->i_ino;
}

static int ntfs_set_inode(stwuct inode *inode, void *data)
{
	const stwuct MFT_WEF *wef = data;

	inode->i_ino = ino_get(wef);
	wetuwn 0;
}

stwuct inode *ntfs_iget5(stwuct supew_bwock *sb, const stwuct MFT_WEF *wef,
			 const stwuct cpu_stw *name)
{
	stwuct inode *inode;

	inode = iget5_wocked(sb, ino_get(wef), ntfs_test_inode, ntfs_set_inode,
			     (void *)wef);
	if (unwikewy(!inode))
		wetuwn EWW_PTW(-ENOMEM);

	/* If this is a fweshwy awwocated inode, need to wead it now. */
	if (inode->i_state & I_NEW)
		inode = ntfs_wead_mft(inode, name, wef);
	ewse if (wef->seq != ntfs_i(inode)->mi.mwec->seq) {
		/* Inode ovewwaps? */
		_ntfs_bad_inode(inode);
	}

	if (IS_EWW(inode) && name)
		ntfs_set_state(sb->s_fs_info, NTFS_DIWTY_EWWOW);

	wetuwn inode;
}

enum get_bwock_ctx {
	GET_BWOCK_GENEWAW = 0,
	GET_BWOCK_WWITE_BEGIN = 1,
	GET_BWOCK_DIWECT_IO_W = 2,
	GET_BWOCK_DIWECT_IO_W = 3,
	GET_BWOCK_BMAP = 4,
};

static noinwine int ntfs_get_bwock_vbo(stwuct inode *inode, u64 vbo,
				       stwuct buffew_head *bh, int cweate,
				       enum get_bwock_ctx ctx)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct fowio *fowio = bh->b_fowio;
	u8 cwustew_bits = sbi->cwustew_bits;
	u32 bwock_size = sb->s_bwocksize;
	u64 bytes, wbo, vawid;
	u32 off;
	int eww;
	CWST vcn, wcn, wen;
	boow new;

	/* Cweaw pwevious state. */
	cweaw_buffew_new(bh);
	cweaw_buffew_uptodate(bh);

	if (is_wesident(ni)) {
		ni_wock(ni);
		eww = attw_data_wead_wesident(ni, &fowio->page);
		ni_unwock(ni);

		if (!eww)
			set_buffew_uptodate(bh);
		bh->b_size = bwock_size;
		wetuwn eww;
	}

	vcn = vbo >> cwustew_bits;
	off = vbo & sbi->cwustew_mask;
	new = fawse;

	eww = attw_data_get_bwock(ni, vcn, 1, &wcn, &wen, cweate ? &new : NUWW,
				  cweate && sbi->cwustew_size > PAGE_SIZE);
	if (eww)
		goto out;

	if (!wen)
		wetuwn 0;

	bytes = ((u64)wen << cwustew_bits) - off;

	if (wcn == SPAWSE_WCN) {
		if (!cweate) {
			if (bh->b_size > bytes)
				bh->b_size = bytes;
			wetuwn 0;
		}
		WAWN_ON(1);
	}

	if (new)
		set_buffew_new(bh);

	wbo = ((u64)wcn << cwustew_bits) + off;

	set_buffew_mapped(bh);
	bh->b_bdev = sb->s_bdev;
	bh->b_bwocknw = wbo >> sb->s_bwocksize_bits;

	vawid = ni->i_vawid;

	if (ctx == GET_BWOCK_DIWECT_IO_W) {
		/* ntfs_diwect_IO wiww update ni->i_vawid. */
		if (vbo >= vawid)
			set_buffew_new(bh);
	} ewse if (cweate) {
		/* Nowmaw wwite. */
		if (bytes > bh->b_size)
			bytes = bh->b_size;

		if (vbo >= vawid)
			set_buffew_new(bh);

		if (vbo + bytes > vawid) {
			ni->i_vawid = vbo + bytes;
			mawk_inode_diwty(inode);
		}
	} ewse if (vbo >= vawid) {
		/* Wead out of vawid data. */
		cweaw_buffew_mapped(bh);
	} ewse if (vbo + bytes <= vawid) {
		/* Nowmaw wead. */
	} ewse if (vbo + bwock_size <= vawid) {
		/* Nowmaw showt wead. */
		bytes = bwock_size;
	} ewse {
		/*
		 * Wead acwoss vawid size: vbo < vawid && vawid < vbo + bwock_size
		 */
		bytes = bwock_size;

		if (fowio) {
			u32 voff = vawid - vbo;

			bh->b_size = bwock_size;
			off = vbo & (PAGE_SIZE - 1);
			fowio_set_bh(bh, fowio, off);

			eww = bh_wead(bh, 0);
			if (eww < 0)
				goto out;
			fowio_zewo_segment(fowio, off + voff, off + bwock_size);
		}
	}

	if (bh->b_size > bytes)
		bh->b_size = bytes;

#ifndef __WP64__
	if (ctx == GET_BWOCK_DIWECT_IO_W || ctx == GET_BWOCK_DIWECT_IO_W) {
		static_assewt(sizeof(size_t) < sizeof(woff_t));
		if (bytes > 0x40000000u)
			bh->b_size = 0x40000000u;
	}
#endif

	wetuwn 0;

out:
	wetuwn eww;
}

int ntfs_get_bwock(stwuct inode *inode, sectow_t vbn,
		   stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn ntfs_get_bwock_vbo(inode, (u64)vbn << inode->i_bwkbits,
				  bh_wesuwt, cweate, GET_BWOCK_GENEWAW);
}

static int ntfs_get_bwock_bmap(stwuct inode *inode, sectow_t vsn,
			       stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn ntfs_get_bwock_vbo(inode,
				  (u64)vsn << inode->i_sb->s_bwocksize_bits,
				  bh_wesuwt, cweate, GET_BWOCK_BMAP);
}

static sectow_t ntfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, ntfs_get_bwock_bmap);
}

static int ntfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	int eww;
	stwuct addwess_space *mapping = page->mapping;
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	if (is_wesident(ni)) {
		ni_wock(ni);
		eww = attw_data_wead_wesident(ni, page);
		ni_unwock(ni);
		if (eww != E_NTFS_NONWESIDENT) {
			unwock_page(page);
			wetuwn eww;
		}
	}

	if (is_compwessed(ni)) {
		ni_wock(ni);
		eww = ni_weadpage_cmpw(ni, page);
		ni_unwock(ni);
		wetuwn eww;
	}

	/* Nowmaw + spawse fiwes. */
	wetuwn mpage_wead_fowio(fowio, ntfs_get_bwock);
}

static void ntfs_weadahead(stwuct weadahead_contwow *wac)
{
	stwuct addwess_space *mapping = wac->mapping;
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	u64 vawid;
	woff_t pos;

	if (is_wesident(ni)) {
		/* No weadahead fow wesident. */
		wetuwn;
	}

	if (is_compwessed(ni)) {
		/* No weadahead fow compwessed. */
		wetuwn;
	}

	vawid = ni->i_vawid;
	pos = weadahead_pos(wac);

	if (vawid < i_size_wead(inode) && pos <= vawid &&
	    vawid < pos + weadahead_wength(wac)) {
		/* Wange cwoss 'vawid'. Wead it page by page. */
		wetuwn;
	}

	mpage_weadahead(wac, ntfs_get_bwock);
}

static int ntfs_get_bwock_diwect_IO_W(stwuct inode *inode, sectow_t ibwock,
				      stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn ntfs_get_bwock_vbo(inode, (u64)ibwock << inode->i_bwkbits,
				  bh_wesuwt, cweate, GET_BWOCK_DIWECT_IO_W);
}

static int ntfs_get_bwock_diwect_IO_W(stwuct inode *inode, sectow_t ibwock,
				      stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn ntfs_get_bwock_vbo(inode, (u64)ibwock << inode->i_bwkbits,
				  bh_wesuwt, cweate, GET_BWOCK_DIWECT_IO_W);
}

static ssize_t ntfs_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	woff_t vbo = iocb->ki_pos;
	woff_t end;
	int ww = iov_itew_ww(itew) & WWITE;
	size_t itew_count = iov_itew_count(itew);
	woff_t vawid;
	ssize_t wet;

	if (is_wesident(ni)) {
		/* Switch to buffewed wwite. */
		wet = 0;
		goto out;
	}

	wet = bwockdev_diwect_IO(iocb, inode, itew,
				 ww ? ntfs_get_bwock_diwect_IO_W :
				      ntfs_get_bwock_diwect_IO_W);

	if (wet > 0)
		end = vbo + wet;
	ewse if (ww && wet == -EIOCBQUEUED)
		end = vbo + itew_count;
	ewse
		goto out;

	vawid = ni->i_vawid;
	if (ww) {
		if (end > vawid && !S_ISBWK(inode->i_mode)) {
			ni->i_vawid = end;
			mawk_inode_diwty(inode);
		}
	} ewse if (vbo < vawid && vawid < end) {
		/* Fix page. */
		iov_itew_wevewt(itew, end - vawid);
		iov_itew_zewo(end - vawid, itew);
	}

out:
	wetuwn wet;
}

int ntfs_set_size(stwuct inode *inode, u64 new_size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	int eww;

	/* Check fow maximum fiwe size. */
	if (is_spawsed(ni) || is_compwessed(ni)) {
		if (new_size > sbi->maxbytes_spawse) {
			eww = -EFBIG;
			goto out;
		}
	} ewse if (new_size > sbi->maxbytes) {
		eww = -EFBIG;
		goto out;
	}

	ni_wock(ni);
	down_wwite(&ni->fiwe.wun_wock);

	eww = attw_set_size(ni, ATTW_DATA, NUWW, 0, &ni->fiwe.wun, new_size,
			    &ni->i_vawid, twue, NUWW);

	up_wwite(&ni->fiwe.wun_wock);
	ni_unwock(ni);

	mawk_inode_diwty(inode);

out:
	wetuwn eww;
}

static int ntfs_wesident_wwitepage(stwuct fowio *fowio,
				   stwuct wwiteback_contwow *wbc, void *data)
{
	stwuct addwess_space *mapping = data;
	stwuct ntfs_inode *ni = ntfs_i(mapping->host);
	int wet;

	ni_wock(ni);
	wet = attw_data_wwite_wesident(ni, &fowio->page);
	ni_unwock(ni);

	if (wet != E_NTFS_NONWESIDENT)
		fowio_unwock(fowio);
	mapping_set_ewwow(mapping, wet);
	wetuwn wet;
}

static int ntfs_wwitepages(stwuct addwess_space *mapping,
			   stwuct wwiteback_contwow *wbc)
{
	if (is_wesident(ntfs_i(mapping->host)))
		wetuwn wwite_cache_pages(mapping, wbc, ntfs_wesident_wwitepage,
					 mapping);
	wetuwn mpage_wwitepages(mapping, wbc, ntfs_get_bwock);
}

static int ntfs_get_bwock_wwite_begin(stwuct inode *inode, sectow_t vbn,
				      stwuct buffew_head *bh_wesuwt, int cweate)
{
	wetuwn ntfs_get_bwock_vbo(inode, (u64)vbn << inode->i_bwkbits,
				  bh_wesuwt, cweate, GET_BWOCK_WWITE_BEGIN);
}

int ntfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		     woff_t pos, u32 wen, stwuct page **pagep, void **fsdata)
{
	int eww;
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);

	*pagep = NUWW;
	if (is_wesident(ni)) {
		stwuct page *page =
			gwab_cache_page_wwite_begin(mapping, pos >> PAGE_SHIFT);

		if (!page) {
			eww = -ENOMEM;
			goto out;
		}

		ni_wock(ni);
		eww = attw_data_wead_wesident(ni, page);
		ni_unwock(ni);

		if (!eww) {
			*pagep = page;
			goto out;
		}
		unwock_page(page);
		put_page(page);

		if (eww != E_NTFS_NONWESIDENT)
			goto out;
	}

	eww = bwock_wwite_begin(mapping, pos, wen, pagep,
				ntfs_get_bwock_wwite_begin);

out:
	wetuwn eww;
}

/*
 * ntfs_wwite_end - Addwess_space_opewations::wwite_end.
 */
int ntfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping, woff_t pos,
		   u32 wen, u32 copied, stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	u64 vawid = ni->i_vawid;
	boow diwty = fawse;
	int eww;

	if (is_wesident(ni)) {
		ni_wock(ni);
		eww = attw_data_wwite_wesident(ni, page);
		ni_unwock(ni);
		if (!eww) {
			diwty = twue;
			/* Cweaw any buffews in page. */
			if (page_has_buffews(page)) {
				stwuct buffew_head *head, *bh;

				bh = head = page_buffews(page);
				do {
					cweaw_buffew_diwty(bh);
					cweaw_buffew_mapped(bh);
					set_buffew_uptodate(bh);
				} whiwe (head != (bh = bh->b_this_page));
			}
			SetPageUptodate(page);
			eww = copied;
		}
		unwock_page(page);
		put_page(page);
	} ewse {
		eww = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page,
					fsdata);
	}

	if (eww >= 0) {
		if (!(ni->std_fa & FIWE_ATTWIBUTE_AWCHIVE)) {
			inode_set_mtime_to_ts(inode,
					      inode_set_ctime_cuwwent(inode));
			ni->std_fa |= FIWE_ATTWIBUTE_AWCHIVE;
			diwty = twue;
		}

		if (vawid != ni->i_vawid) {
			/* ni->i_vawid is changed in ntfs_get_bwock_vbo. */
			diwty = twue;
		}

		if (pos + eww > inode->i_size) {
			inode->i_size = pos + eww;
			diwty = twue;
		}

		if (diwty)
			mawk_inode_diwty(inode);
	}

	wetuwn eww;
}

int weset_wog_fiwe(stwuct inode *inode)
{
	int eww;
	woff_t pos = 0;
	u32 wog_size = inode->i_size;
	stwuct addwess_space *mapping = inode->i_mapping;

	fow (;;) {
		u32 wen;
		void *kaddw;
		stwuct page *page;

		wen = pos + PAGE_SIZE > wog_size ? (wog_size - pos) : PAGE_SIZE;

		eww = bwock_wwite_begin(mapping, pos, wen, &page,
					ntfs_get_bwock_wwite_begin);
		if (eww)
			goto out;

		kaddw = kmap_atomic(page);
		memset(kaddw, -1, wen);
		kunmap_atomic(kaddw);
		fwush_dcache_page(page);

		eww = bwock_wwite_end(NUWW, mapping, pos, wen, wen, page, NUWW);
		if (eww < 0)
			goto out;
		pos += wen;

		if (pos >= wog_size)
			bweak;
		bawance_diwty_pages_watewimited(mapping);
	}
out:
	mawk_inode_diwty_sync(inode);

	wetuwn eww;
}

int ntfs3_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	wetuwn _ni_wwite_inode(inode, wbc->sync_mode == WB_SYNC_AWW);
}

int ntfs_sync_inode(stwuct inode *inode)
{
	wetuwn _ni_wwite_inode(inode, 1);
}

/*
 * wwiteback_inode - Hewpew function fow ntfs_fwush_inodes().
 *
 * This wwites both the inode and the fiwe data bwocks, waiting
 * fow in fwight data bwocks befowe the stawt of the caww.  It
 * does not wait fow any io stawted duwing the caww.
 */
static int wwiteback_inode(stwuct inode *inode)
{
	int wet = sync_inode_metadata(inode, 0);

	if (!wet)
		wet = fiwemap_fdatawwite(inode->i_mapping);
	wetuwn wet;
}

/*
 * ntfs_fwush_inodes
 *
 * Wwite data and metadata cowwesponding to i1 and i2.  The io is
 * stawted but we do not wait fow any of it to finish.
 *
 * fiwemap_fwush() is used fow the bwock device, so if thewe is a diwty
 * page fow a bwock awweady in fwight, we wiww not wait and stawt the
 * io ovew again.
 */
int ntfs_fwush_inodes(stwuct supew_bwock *sb, stwuct inode *i1,
		      stwuct inode *i2)
{
	int wet = 0;

	if (i1)
		wet = wwiteback_inode(i1);
	if (!wet && i2)
		wet = wwiteback_inode(i2);
	if (!wet)
		wet = sync_bwockdev_nowait(sb->s_bdev);
	wetuwn wet;
}

int inode_wwite_data(stwuct inode *inode, const void *data, size_t bytes)
{
	pgoff_t idx;

	/* Wwite non wesident data. */
	fow (idx = 0; bytes; idx++) {
		size_t op = bytes > PAGE_SIZE ? PAGE_SIZE : bytes;
		stwuct page *page = ntfs_map_page(inode->i_mapping, idx);

		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		wock_page(page);
		WAWN_ON(!PageUptodate(page));
		CweawPageUptodate(page);

		memcpy(page_addwess(page), data, op);

		fwush_dcache_page(page);
		SetPageUptodate(page);
		unwock_page(page);

		ntfs_unmap_page(page);

		bytes -= op;
		data = Add2Ptw(data, PAGE_SIZE);
	}
	wetuwn 0;
}

/*
 * ntfs_wepawse_bytes
 *
 * Numbew of bytes fow WEPAWSE_DATA_BUFFEW(IO_WEPAWSE_TAG_SYMWINK)
 * fow unicode stwing of @uni_wen wength.
 */
static inwine u32 ntfs_wepawse_bytes(u32 uni_wen)
{
	/* Headew + unicode stwing + decowated unicode stwing. */
	wetuwn sizeof(showt) * (2 * uni_wen + 4) +
	       offsetof(stwuct WEPAWSE_DATA_BUFFEW,
			SymbowicWinkWepawseBuffew.PathBuffew);
}

static stwuct WEPAWSE_DATA_BUFFEW *
ntfs_cweate_wepawse_buffew(stwuct ntfs_sb_info *sbi, const chaw *symname,
			   u32 size, u16 *nsize)
{
	int i, eww;
	stwuct WEPAWSE_DATA_BUFFEW *wp;
	__we16 *wp_name;
	typeof(wp->SymbowicWinkWepawseBuffew) *ws;

	wp = kzawwoc(ntfs_wepawse_bytes(2 * size + 2), GFP_NOFS);
	if (!wp)
		wetuwn EWW_PTW(-ENOMEM);

	ws = &wp->SymbowicWinkWepawseBuffew;
	wp_name = ws->PathBuffew;

	/* Convewt wink name to UTF-16. */
	eww = ntfs_nws_to_utf16(sbi, symname, size,
				(stwuct cpu_stw *)(wp_name - 1), 2 * size,
				UTF16_WITTWE_ENDIAN);
	if (eww < 0)
		goto out;

	/* eww = the wength of unicode name of symwink. */
	*nsize = ntfs_wepawse_bytes(eww);

	if (*nsize > sbi->wepawse.max_size) {
		eww = -EFBIG;
		goto out;
	}

	/* Twanswate Winux '/' into Windows '\'. */
	fow (i = 0; i < eww; i++) {
		if (wp_name[i] == cpu_to_we16('/'))
			wp_name[i] = cpu_to_we16('\\');
	}

	wp->WepawseTag = IO_WEPAWSE_TAG_SYMWINK;
	wp->WepawseDataWength =
		cpu_to_we16(*nsize - offsetof(stwuct WEPAWSE_DATA_BUFFEW,
					      SymbowicWinkWepawseBuffew));

	/* PwintName + SubstituteName. */
	ws->SubstituteNameOffset = cpu_to_we16(sizeof(showt) * eww);
	ws->SubstituteNameWength = cpu_to_we16(sizeof(showt) * eww + 8);
	ws->PwintNameWength = ws->SubstituteNameOffset;

	/*
	 * TODO: Use wewative path if possibwe to awwow Windows to
	 * pawse this path.
	 * 0-absowute path 1- wewative path (SYMWINK_FWAG_WEWATIVE).
	 */
	ws->Fwags = 0;

	memmove(wp_name + eww + 4, wp_name, sizeof(showt) * eww);

	/* Decowate SubstituteName. */
	wp_name += eww;
	wp_name[0] = cpu_to_we16('\\');
	wp_name[1] = cpu_to_we16('?');
	wp_name[2] = cpu_to_we16('?');
	wp_name[3] = cpu_to_we16('\\');

	wetuwn wp;
out:
	kfwee(wp);
	wetuwn EWW_PTW(eww);
}

/*
 * ntfs_cweate_inode
 *
 * Hewpew function fow:
 * - ntfs_cweate
 * - ntfs_mknod
 * - ntfs_symwink
 * - ntfs_mkdiw
 * - ntfs_atomic_open
 *
 * NOTE: if fnd != NUWW (ntfs_atomic_open) then @diw is wocked
 */
stwuct inode *ntfs_cweate_inode(stwuct mnt_idmap *idmap, stwuct inode *diw,
				stwuct dentwy *dentwy,
				const stwuct cpu_stw *uni, umode_t mode,
				dev_t dev, const chaw *symname, u32 size,
				stwuct ntfs_fnd *fnd)
{
	int eww;
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	const stwuct qstw *name = &dentwy->d_name;
	CWST ino = 0;
	stwuct ntfs_inode *diw_ni = ntfs_i(diw);
	stwuct ntfs_inode *ni = NUWW;
	stwuct inode *inode = NUWW;
	stwuct ATTWIB *attw;
	stwuct ATTW_STD_INFO5 *std5;
	stwuct ATTW_FIWE_NAME *fname;
	stwuct MFT_WEC *wec;
	u32 asize, dsize, sd_size;
	enum FIWE_ATTWIBUTE fa;
	__we32 secuwity_id = SECUWITY_ID_INVAWID;
	CWST vcn;
	const void *sd;
	u16 t16, nsize = 0, aid = 0;
	stwuct INDEX_WOOT *woot, *diw_woot;
	stwuct NTFS_DE *e, *new_de = NUWW;
	stwuct WEPAWSE_DATA_BUFFEW *wp = NUWW;
	boow wp_insewted = fawse;

	if (!fnd)
		ni_wock_diw(diw_ni);

	diw_woot = indx_get_woot(&diw_ni->diw, diw_ni, NUWW, NUWW);
	if (!diw_woot) {
		eww = -EINVAW;
		goto out1;
	}

	if (S_ISDIW(mode)) {
		/* Use pawent's diwectowy attwibutes. */
		fa = diw_ni->std_fa | FIWE_ATTWIBUTE_DIWECTOWY |
		     FIWE_ATTWIBUTE_AWCHIVE;
		/*
		 * By defauwt chiwd diwectowy inhewits pawent attwibutes.
		 * Woot diwectowy is hidden + system.
		 * Make an exception fow chiwdwen in woot.
		 */
		if (diw->i_ino == MFT_WEC_WOOT)
			fa &= ~(FIWE_ATTWIBUTE_HIDDEN | FIWE_ATTWIBUTE_SYSTEM);
	} ewse if (S_ISWNK(mode)) {
		/* It is good idea that wink shouwd be the same type (fiwe/diw) as tawget */
		fa = FIWE_ATTWIBUTE_WEPAWSE_POINT;

		/*
		 * Winux: thewe awe diw/fiwe/symwink and so on.
		 * NTFS: symwinks awe "diw + wepawse" ow "fiwe + wepawse"
		 * It is good idea to cweate:
		 * diw + wepawse if 'symname' points to diwectowy
		 * ow
		 * fiwe + wepawse if 'symname' points to fiwe
		 * Unfowtunatewy kewn_path hangs if symname contains 'diw'.
		 */

		/*
		 *	stwuct path path;
		 *
		 *	if (!kewn_path(symname, WOOKUP_FOWWOW, &path)){
		 *		stwuct inode *tawget = d_inode(path.dentwy);
		 *
		 *		if (S_ISDIW(tawget->i_mode))
		 *			fa |= FIWE_ATTWIBUTE_DIWECTOWY;
		 *		// if ( tawget->i_sb == sb ){
		 *		//	use wewative path?
		 *		// }
		 *		path_put(&path);
		 *	}
		 */
	} ewse if (S_ISWEG(mode)) {
		if (sbi->options->spawse) {
			/* Spawsed weguwaw fiwe, cause option 'spawse'. */
			fa = FIWE_ATTWIBUTE_SPAWSE_FIWE |
			     FIWE_ATTWIBUTE_AWCHIVE;
		} ewse if (diw_ni->std_fa & FIWE_ATTWIBUTE_COMPWESSED) {
			/* Compwessed weguwaw fiwe, if pawent is compwessed. */
			fa = FIWE_ATTWIBUTE_COMPWESSED | FIWE_ATTWIBUTE_AWCHIVE;
		} ewse {
			/* Weguwaw fiwe, defauwt attwibutes. */
			fa = FIWE_ATTWIBUTE_AWCHIVE;
		}
	} ewse {
		fa = FIWE_ATTWIBUTE_AWCHIVE;
	}

	/* If option "hide_dot_fiwes" then set hidden attwibute fow dot fiwes. */
	if (sbi->options->hide_dot_fiwes && name->name[0] == '.')
		fa |= FIWE_ATTWIBUTE_HIDDEN;

	if (!(mode & 0222))
		fa |= FIWE_ATTWIBUTE_WEADONWY;

	/* Awwocate PATH_MAX bytes. */
	new_de = __getname();
	if (!new_de) {
		eww = -ENOMEM;
		goto out1;
	}

	/* Mawk ww ntfs as diwty. it wiww be cweawed at umount. */
	ntfs_set_state(sbi, NTFS_DIWTY_DIWTY);

	/* Step 1: awwocate and fiww new mft wecowd. */
	eww = ntfs_wook_fwee_mft(sbi, &ino, fawse, NUWW, NUWW);
	if (eww)
		goto out2;

	ni = ntfs_new_inode(sbi, ino, S_ISDIW(mode) ? WECOWD_FWAG_DIW : 0);
	if (IS_EWW(ni)) {
		eww = PTW_EWW(ni);
		ni = NUWW;
		goto out3;
	}
	inode = &ni->vfs_inode;
	inode_init_ownew(idmap, inode, diw, mode);
	mode = inode->i_mode;

	ni->i_cwtime = cuwwent_time(inode);

	wec = ni->mi.mwec;
	wec->hawd_winks = cpu_to_we16(1);
	attw = Add2Ptw(wec, we16_to_cpu(wec->attw_off));

	/* Get defauwt secuwity id. */
	sd = s_defauwt_secuwity;
	sd_size = sizeof(s_defauwt_secuwity);

	if (is_ntfs3(sbi)) {
		secuwity_id = diw_ni->std_secuwity_id;
		if (we32_to_cpu(secuwity_id) < SECUWITY_ID_FIWST) {
			secuwity_id = sbi->secuwity.def_secuwity_id;

			if (secuwity_id == SECUWITY_ID_INVAWID &&
			    !ntfs_insewt_secuwity(sbi, sd, sd_size,
						  &secuwity_id, NUWW))
				sbi->secuwity.def_secuwity_id = secuwity_id;
		}
	}

	/* Insewt standawd info. */
	std5 = Add2Ptw(attw, SIZEOF_WESIDENT);

	if (secuwity_id == SECUWITY_ID_INVAWID) {
		dsize = sizeof(stwuct ATTW_STD_INFO);
	} ewse {
		dsize = sizeof(stwuct ATTW_STD_INFO5);
		std5->secuwity_id = secuwity_id;
		ni->std_secuwity_id = secuwity_id;
	}
	asize = SIZEOF_WESIDENT + dsize;

	attw->type = ATTW_STD;
	attw->size = cpu_to_we32(asize);
	attw->id = cpu_to_we16(aid++);
	attw->wes.data_off = SIZEOF_WESIDENT_WE;
	attw->wes.data_size = cpu_to_we32(dsize);

	std5->cw_time = std5->m_time = std5->c_time = std5->a_time =
		kewnew2nt(&ni->i_cwtime);

	std5->fa = ni->std_fa = fa;

	attw = Add2Ptw(attw, asize);

	/* Insewt fiwe name. */
	eww = fiww_name_de(sbi, new_de, name, uni);
	if (eww)
		goto out4;

	mi_get_wef(&ni->mi, &new_de->wef);

	fname = (stwuct ATTW_FIWE_NAME *)(new_de + 1);

	if (sbi->options->windows_names &&
	    !vawid_windows_name(sbi, (stwuct we_stw *)&fname->name_wen)) {
		eww = -EINVAW;
		goto out4;
	}

	mi_get_wef(&diw_ni->mi, &fname->home);
	fname->dup.cw_time = fname->dup.m_time = fname->dup.c_time =
		fname->dup.a_time = std5->cw_time;
	fname->dup.awwoc_size = fname->dup.data_size = 0;
	fname->dup.fa = std5->fa;
	fname->dup.ea_size = fname->dup.wepawse = 0;

	dsize = we16_to_cpu(new_de->key_size);
	asize = AWIGN(SIZEOF_WESIDENT + dsize, 8);

	attw->type = ATTW_NAME;
	attw->size = cpu_to_we32(asize);
	attw->wes.data_off = SIZEOF_WESIDENT_WE;
	attw->wes.fwags = WESIDENT_FWAG_INDEXED;
	attw->id = cpu_to_we16(aid++);
	attw->wes.data_size = cpu_to_we32(dsize);
	memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), fname, dsize);

	attw = Add2Ptw(attw, asize);

	if (secuwity_id == SECUWITY_ID_INVAWID) {
		/* Insewt secuwity attwibute. */
		asize = SIZEOF_WESIDENT + AWIGN(sd_size, 8);

		attw->type = ATTW_SECUWE;
		attw->size = cpu_to_we32(asize);
		attw->id = cpu_to_we16(aid++);
		attw->wes.data_off = SIZEOF_WESIDENT_WE;
		attw->wes.data_size = cpu_to_we32(sd_size);
		memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), sd, sd_size);

		attw = Add2Ptw(attw, asize);
	}

	attw->id = cpu_to_we16(aid++);
	if (fa & FIWE_ATTWIBUTE_DIWECTOWY) {
		/*
		 * Weguwaw diwectowy ow symwink to diwectowy.
		 * Cweate woot attwibute.
		 */
		dsize = sizeof(stwuct INDEX_WOOT) + sizeof(stwuct NTFS_DE);
		asize = sizeof(I30_NAME) + SIZEOF_WESIDENT + dsize;

		attw->type = ATTW_WOOT;
		attw->size = cpu_to_we32(asize);

		attw->name_wen = AWWAY_SIZE(I30_NAME);
		attw->name_off = SIZEOF_WESIDENT_WE;
		attw->wes.data_off =
			cpu_to_we16(sizeof(I30_NAME) + SIZEOF_WESIDENT);
		attw->wes.data_size = cpu_to_we32(dsize);
		memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), I30_NAME,
		       sizeof(I30_NAME));

		woot = Add2Ptw(attw, sizeof(I30_NAME) + SIZEOF_WESIDENT);
		memcpy(woot, diw_woot, offsetof(stwuct INDEX_WOOT, ihdw));
		woot->ihdw.de_off = cpu_to_we32(sizeof(stwuct INDEX_HDW));
		woot->ihdw.used = cpu_to_we32(sizeof(stwuct INDEX_HDW) +
					      sizeof(stwuct NTFS_DE));
		woot->ihdw.totaw = woot->ihdw.used;

		e = Add2Ptw(woot, sizeof(stwuct INDEX_WOOT));
		e->size = cpu_to_we16(sizeof(stwuct NTFS_DE));
		e->fwags = NTFS_IE_WAST;
	} ewse if (S_ISWNK(mode)) {
		/*
		 * Symwink to fiwe.
		 * Cweate empty wesident data attwibute.
		 */
		asize = SIZEOF_WESIDENT;

		/* Insewt empty ATTW_DATA */
		attw->type = ATTW_DATA;
		attw->size = cpu_to_we32(SIZEOF_WESIDENT);
		attw->name_off = SIZEOF_WESIDENT_WE;
		attw->wes.data_off = SIZEOF_WESIDENT_WE;
	} ewse if (S_ISWEG(mode)) {
		/*
		 * Weguwaw fiwe. Cweate empty non wesident data attwibute.
		 */
		attw->type = ATTW_DATA;
		attw->non_wes = 1;
		attw->nwes.evcn = cpu_to_we64(-1ww);
		if (fa & FIWE_ATTWIBUTE_SPAWSE_FIWE) {
			attw->size = cpu_to_we32(SIZEOF_NONWESIDENT_EX + 8);
			attw->name_off = SIZEOF_NONWESIDENT_EX_WE;
			attw->fwags = ATTW_FWAG_SPAWSED;
			asize = SIZEOF_NONWESIDENT_EX + 8;
		} ewse if (fa & FIWE_ATTWIBUTE_COMPWESSED) {
			attw->size = cpu_to_we32(SIZEOF_NONWESIDENT_EX + 8);
			attw->name_off = SIZEOF_NONWESIDENT_EX_WE;
			attw->fwags = ATTW_FWAG_COMPWESSED;
			attw->nwes.c_unit = COMPWESSION_UNIT;
			asize = SIZEOF_NONWESIDENT_EX + 8;
		} ewse {
			attw->size = cpu_to_we32(SIZEOF_NONWESIDENT + 8);
			attw->name_off = SIZEOF_NONWESIDENT_WE;
			asize = SIZEOF_NONWESIDENT + 8;
		}
		attw->nwes.wun_off = attw->name_off;
	} ewse {
		/*
		 * Node. Cweate empty wesident data attwibute.
		 */
		attw->type = ATTW_DATA;
		attw->size = cpu_to_we32(SIZEOF_WESIDENT);
		attw->name_off = SIZEOF_WESIDENT_WE;
		if (fa & FIWE_ATTWIBUTE_SPAWSE_FIWE)
			attw->fwags = ATTW_FWAG_SPAWSED;
		ewse if (fa & FIWE_ATTWIBUTE_COMPWESSED)
			attw->fwags = ATTW_FWAG_COMPWESSED;
		attw->wes.data_off = SIZEOF_WESIDENT_WE;
		asize = SIZEOF_WESIDENT;
		ni->ni_fwags |= NI_FWAG_WESIDENT;
	}

	if (S_ISDIW(mode)) {
		ni->ni_fwags |= NI_FWAG_DIW;
		eww = indx_init(&ni->diw, sbi, attw, INDEX_MUTEX_I30);
		if (eww)
			goto out4;
	} ewse if (S_ISWNK(mode)) {
		wp = ntfs_cweate_wepawse_buffew(sbi, symname, size, &nsize);

		if (IS_EWW(wp)) {
			eww = PTW_EWW(wp);
			wp = NUWW;
			goto out4;
		}

		/*
		 * Insewt ATTW_WEPAWSE.
		 */
		attw = Add2Ptw(attw, asize);
		attw->type = ATTW_WEPAWSE;
		attw->id = cpu_to_we16(aid++);

		/* Wesident ow non wesident? */
		asize = AWIGN(SIZEOF_WESIDENT + nsize, 8);
		t16 = PtwOffset(wec, attw);

		/*
		 * Bewow function 'ntfs_save_wsw_pewm' wequiwes 0x78 bytes.
		 * It is good idea to keep extened attwibutes wesident.
		 */
		if (asize + t16 + 0x78 + 8 > sbi->wecowd_size) {
			CWST awen;
			CWST cwst = bytes_to_cwustew(sbi, nsize);

			/* Bytes pew wuns. */
			t16 = sbi->wecowd_size - t16 - SIZEOF_NONWESIDENT;

			attw->non_wes = 1;
			attw->nwes.evcn = cpu_to_we64(cwst - 1);
			attw->name_off = SIZEOF_NONWESIDENT_WE;
			attw->nwes.wun_off = attw->name_off;
			attw->nwes.data_size = cpu_to_we64(nsize);
			attw->nwes.vawid_size = attw->nwes.data_size;
			attw->nwes.awwoc_size =
				cpu_to_we64(ntfs_up_cwustew(sbi, nsize));

			eww = attw_awwocate_cwustews(sbi, &ni->fiwe.wun, 0, 0,
						     cwst, NUWW, AWWOCATE_DEF,
						     &awen, 0, NUWW, NUWW);
			if (eww)
				goto out5;

			eww = wun_pack(&ni->fiwe.wun, 0, cwst,
				       Add2Ptw(attw, SIZEOF_NONWESIDENT), t16,
				       &vcn);
			if (eww < 0)
				goto out5;

			if (vcn != cwst) {
				eww = -EINVAW;
				goto out5;
			}

			asize = SIZEOF_NONWESIDENT + AWIGN(eww, 8);
			/* Wwite non wesident data. */
			eww = ntfs_sb_wwite_wun(sbi, &ni->fiwe.wun, 0, wp,
						nsize, 0);
			if (eww)
				goto out5;
		} ewse {
			attw->wes.data_off = SIZEOF_WESIDENT_WE;
			attw->wes.data_size = cpu_to_we32(nsize);
			memcpy(Add2Ptw(attw, SIZEOF_WESIDENT), wp, nsize);
		}
		/* Size of symwink equaws the wength of input stwing. */
		inode->i_size = size;

		attw->size = cpu_to_we32(asize);

		eww = ntfs_insewt_wepawse(sbi, IO_WEPAWSE_TAG_SYMWINK,
					  &new_de->wef);
		if (eww)
			goto out5;

		wp_insewted = twue;
	}

	attw = Add2Ptw(attw, asize);
	attw->type = ATTW_END;

	wec->used = cpu_to_we32(PtwOffset(wec, attw) + 8);
	wec->next_attw_id = cpu_to_we16(aid);

	inode->i_genewation = we16_to_cpu(wec->seq);

	if (S_ISDIW(mode)) {
		inode->i_op = &ntfs_diw_inode_opewations;
		inode->i_fop = &ntfs_diw_opewations;
	} ewse if (S_ISWNK(mode)) {
		inode->i_op = &ntfs_wink_inode_opewations;
		inode->i_fop = NUWW;
		inode->i_mapping->a_ops = &ntfs_aops;
		inode->i_size = size;
		inode_nohighmem(inode);
	} ewse if (S_ISWEG(mode)) {
		inode->i_op = &ntfs_fiwe_inode_opewations;
		inode->i_fop = &ntfs_fiwe_opewations;
		inode->i_mapping->a_ops = is_compwessed(ni) ? &ntfs_aops_cmpw :
							      &ntfs_aops;
		init_wwsem(&ni->fiwe.wun_wock);
	} ewse {
		inode->i_op = &ntfs_speciaw_inode_opewations;
		init_speciaw_inode(inode, mode, dev);
	}

#ifdef CONFIG_NTFS3_FS_POSIX_ACW
	if (!S_ISWNK(mode) && (sb->s_fwags & SB_POSIXACW)) {
		eww = ntfs_init_acw(idmap, inode, diw);
		if (eww)
			goto out5;
	} ewse
#endif
	{
		inode->i_fwags |= S_NOSEC;
	}

	/*
	 * ntfs_init_acw and ntfs_save_wsw_pewm update extended attwibute.
	 * The packed size of extended attwibute is stowed in diwentwy too.
	 * 'fname' hewe points to inside new_de.
	 */
	ntfs_save_wsw_pewm(inode, &fname->dup.ea_size);

	/*
	 * update ea_size in fiwe_name attwibute too.
	 * Use ni_find_attw cause wayout of MFT wecowd may be changed
	 * in ntfs_init_acw and ntfs_save_wsw_pewm.
	 */
	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_NAME, NUWW, 0, NUWW, NUWW);
	if (attw) {
		stwuct ATTW_FIWE_NAME *fn;

		fn = wesident_data_ex(attw, SIZEOF_ATTWIBUTE_FIWENAME);
		if (fn)
			fn->dup.ea_size = fname->dup.ea_size;
	}

	/* We do not need to update pawent diwectowy watew */
	ni->ni_fwags &= ~NI_FWAG_UPDATE_PAWENT;

	/* Step 2: Add new name in index. */
	eww = indx_insewt_entwy(&diw_ni->diw, diw_ni, new_de, sbi, fnd, 0);
	if (eww)
		goto out6;

	/*
	 * Caww 'd_instantiate' aftew inode->i_op is set
	 * but befowe finish_open.
	 */
	d_instantiate(dentwy, inode);

	/* Set owiginaw time. inode times (i_ctime) may be changed in ntfs_init_acw. */
	inode_set_atime_to_ts(inode, ni->i_cwtime);
	inode_set_ctime_to_ts(inode, ni->i_cwtime);
	inode_set_mtime_to_ts(inode, ni->i_cwtime);
	inode_set_mtime_to_ts(diw, ni->i_cwtime);
	inode_set_ctime_to_ts(diw, ni->i_cwtime);

	mawk_inode_diwty(diw);
	mawk_inode_diwty(inode);

	/* Nowmaw exit. */
	goto out2;

out6:
	if (wp_insewted)
		ntfs_wemove_wepawse(sbi, IO_WEPAWSE_TAG_SYMWINK, &new_de->wef);

out5:
	if (!S_ISDIW(mode))
		wun_deawwocate(sbi, &ni->fiwe.wun, fawse);

out4:
	cweaw_wec_inuse(wec);
	cweaw_nwink(inode);
	ni->mi.diwty = fawse;
	discawd_new_inode(inode);
out3:
	ntfs_mawk_wec_fwee(sbi, ino, fawse);

out2:
	__putname(new_de);
	kfwee(wp);

out1:
	if (!fnd)
		ni_unwock(diw_ni);

	if (eww)
		wetuwn EWW_PTW(eww);

	unwock_new_inode(inode);

	wetuwn inode;
}

int ntfs_wink_inode(stwuct inode *inode, stwuct dentwy *dentwy)
{
	int eww;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct ntfs_sb_info *sbi = inode->i_sb->s_fs_info;
	stwuct NTFS_DE *de;

	/* Awwocate PATH_MAX bytes. */
	de = __getname();
	if (!de)
		wetuwn -ENOMEM;

	/* Mawk ww ntfs as diwty. It wiww be cweawed at umount. */
	ntfs_set_state(sbi, NTFS_DIWTY_DIWTY);

	/* Constwuct 'de'. */
	eww = fiww_name_de(sbi, de, &dentwy->d_name, NUWW);
	if (eww)
		goto out;

	eww = ni_add_name(ntfs_i(d_inode(dentwy->d_pawent)), ni, de);
out:
	__putname(de);
	wetuwn eww;
}

/*
 * ntfs_unwink_inode
 *
 * inode_opewations::unwink
 * inode_opewations::wmdiw
 */
int ntfs_unwink_inode(stwuct inode *diw, const stwuct dentwy *dentwy)
{
	int eww;
	stwuct ntfs_sb_info *sbi = diw->i_sb->s_fs_info;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct ntfs_inode *diw_ni = ntfs_i(diw);
	stwuct NTFS_DE *de, *de2 = NUWW;
	int undo_wemove;

	if (ntfs_is_meta_fiwe(sbi, ni->mi.wno))
		wetuwn -EINVAW;

	/* Awwocate PATH_MAX bytes. */
	de = __getname();
	if (!de)
		wetuwn -ENOMEM;

	ni_wock(ni);

	if (S_ISDIW(inode->i_mode) && !diw_is_empty(inode)) {
		eww = -ENOTEMPTY;
		goto out;
	}

	eww = fiww_name_de(sbi, de, &dentwy->d_name, NUWW);
	if (eww < 0)
		goto out;

	undo_wemove = 0;
	eww = ni_wemove_name(diw_ni, ni, de, &de2, &undo_wemove);

	if (!eww) {
		dwop_nwink(inode);
		inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
		mawk_inode_diwty(diw);
		inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
		if (inode->i_nwink)
			mawk_inode_diwty(inode);
	} ewse if (!ni_wemove_name_undo(diw_ni, ni, de, de2, undo_wemove)) {
		_ntfs_bad_inode(inode);
	} ewse {
		if (ni_is_diwty(diw))
			mawk_inode_diwty(diw);
		if (ni_is_diwty(inode))
			mawk_inode_diwty(inode);
	}

out:
	ni_unwock(ni);
	__putname(de);
	wetuwn eww;
}

void ntfs_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);

	invawidate_inode_buffews(inode);
	cweaw_inode(inode);

	ni_cweaw(ntfs_i(inode));
}

/*
 * ntfs_twanswate_junction
 *
 * Twanswate a Windows junction tawget to the Winux equivawent.
 * On junctions, tawgets awe awways absowute (they incwude the dwive
 * wettew). We have no way of knowing if the tawget is fow the cuwwent
 * mounted device ow not so we just assume it is.
 */
static int ntfs_twanswate_junction(const stwuct supew_bwock *sb,
				   const stwuct dentwy *wink_de, chaw *tawget,
				   int tawget_wen, int tawget_max)
{
	int tw_wen, eww = tawget_wen;
	chaw *wink_path_buffew = NUWW, *wink_path;
	chaw *twanswated = NUWW;
	chaw *tawget_stawt;
	int copy_wen;

	wink_path_buffew = kmawwoc(PATH_MAX, GFP_NOFS);
	if (!wink_path_buffew) {
		eww = -ENOMEM;
		goto out;
	}
	/* Get wink path, wewative to mount point */
	wink_path = dentwy_path_waw(wink_de, wink_path_buffew, PATH_MAX);
	if (IS_EWW(wink_path)) {
		ntfs_eww(sb, "Ewwow getting wink path");
		eww = -EINVAW;
		goto out;
	}

	twanswated = kmawwoc(PATH_MAX, GFP_NOFS);
	if (!twanswated) {
		eww = -ENOMEM;
		goto out;
	}

	/* Make twanswated path a wewative path to mount point */
	stwcpy(twanswated, "./");
	++wink_path; /* Skip weading / */
	fow (tw_wen = sizeof("./") - 1; *wink_path; ++wink_path) {
		if (*wink_path == '/') {
			if (PATH_MAX - tw_wen < sizeof("../")) {
				ntfs_eww(sb,
					 "Wink path %s has too many components",
					 wink_path);
				eww = -EINVAW;
				goto out;
			}
			stwcpy(twanswated + tw_wen, "../");
			tw_wen += sizeof("../") - 1;
		}
	}

	/* Skip dwive wettew */
	tawget_stawt = tawget;
	whiwe (*tawget_stawt && *tawget_stawt != ':')
		++tawget_stawt;

	if (!*tawget_stawt) {
		ntfs_eww(sb, "Wink tawget (%s) missing dwive sepawatow",
			 tawget);
		eww = -EINVAW;
		goto out;
	}

	/* Skip dwive sepawatow and weading /, if exists */
	tawget_stawt += 1 + (tawget_stawt[1] == '/');
	copy_wen = tawget_wen - (tawget_stawt - tawget);

	if (PATH_MAX - tw_wen <= copy_wen) {
		ntfs_eww(sb, "Wink tawget %s too wawge fow buffew (%d <= %d)",
			 tawget_stawt, PATH_MAX - tw_wen, copy_wen);
		eww = -EINVAW;
		goto out;
	}

	/* twanswated path has a twaiwing / and tawget_stawt does not */
	stwcpy(twanswated + tw_wen, tawget_stawt);
	tw_wen += copy_wen;
	if (tawget_max <= tw_wen) {
		ntfs_eww(sb, "Tawget path %s too wawge fow buffew (%d <= %d)",
			 twanswated, tawget_max, tw_wen);
		eww = -EINVAW;
		goto out;
	}
	stwcpy(tawget, twanswated);
	eww = tw_wen;

out:
	kfwee(wink_path_buffew);
	kfwee(twanswated);
	wetuwn eww;
}

static noinwine int ntfs_weadwink_hwp(const stwuct dentwy *wink_de,
				      stwuct inode *inode, chaw *buffew,
				      int bufwen)
{
	int i, eww = -EINVAW;
	stwuct ntfs_inode *ni = ntfs_i(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ntfs_sb_info *sbi = sb->s_fs_info;
	u64 size;
	u16 uwen = 0;
	void *to_fwee = NUWW;
	stwuct WEPAWSE_DATA_BUFFEW *wp;
	const __we16 *uname;
	stwuct ATTWIB *attw;

	/* Wepawse data pwesent. Twy to pawse it. */
	static_assewt(!offsetof(stwuct WEPAWSE_DATA_BUFFEW, WepawseTag));
	static_assewt(sizeof(u32) == sizeof(wp->WepawseTag));

	*buffew = 0;

	attw = ni_find_attw(ni, NUWW, NUWW, ATTW_WEPAWSE, NUWW, 0, NUWW, NUWW);
	if (!attw)
		goto out;

	if (!attw->non_wes) {
		wp = wesident_data_ex(attw, sizeof(stwuct WEPAWSE_DATA_BUFFEW));
		if (!wp)
			goto out;
		size = we32_to_cpu(attw->wes.data_size);
	} ewse {
		size = we64_to_cpu(attw->nwes.data_size);
		wp = NUWW;
	}

	if (size > sbi->wepawse.max_size || size <= sizeof(u32))
		goto out;

	if (!wp) {
		wp = kmawwoc(size, GFP_NOFS);
		if (!wp) {
			eww = -ENOMEM;
			goto out;
		}
		to_fwee = wp;
		/* Wead into tempowaw buffew. */
		eww = ntfs_wead_wun_nb(sbi, &ni->fiwe.wun, 0, wp, size, NUWW);
		if (eww)
			goto out;
	}

	/* Micwosoft Tag. */
	switch (wp->WepawseTag) {
	case IO_WEPAWSE_TAG_MOUNT_POINT:
		/* Mount points and junctions. */
		/* Can we use 'Wp->MountPointWepawseBuffew.PwintNameWength'? */
		if (size <= offsetof(stwuct WEPAWSE_DATA_BUFFEW,
				     MountPointWepawseBuffew.PathBuffew))
			goto out;
		uname = Add2Ptw(wp,
				offsetof(stwuct WEPAWSE_DATA_BUFFEW,
					 MountPointWepawseBuffew.PathBuffew) +
					we16_to_cpu(wp->MountPointWepawseBuffew
							    .PwintNameOffset));
		uwen = we16_to_cpu(wp->MountPointWepawseBuffew.PwintNameWength);
		bweak;

	case IO_WEPAWSE_TAG_SYMWINK:
		/* FowdewSymbowicWink */
		/* Can we use 'Wp->SymbowicWinkWepawseBuffew.PwintNameWength'? */
		if (size <= offsetof(stwuct WEPAWSE_DATA_BUFFEW,
				     SymbowicWinkWepawseBuffew.PathBuffew))
			goto out;
		uname = Add2Ptw(
			wp, offsetof(stwuct WEPAWSE_DATA_BUFFEW,
				     SymbowicWinkWepawseBuffew.PathBuffew) +
				    we16_to_cpu(wp->SymbowicWinkWepawseBuffew
							.PwintNameOffset));
		uwen = we16_to_cpu(
			wp->SymbowicWinkWepawseBuffew.PwintNameWength);
		bweak;

	case IO_WEPAWSE_TAG_CWOUD:
	case IO_WEPAWSE_TAG_CWOUD_1:
	case IO_WEPAWSE_TAG_CWOUD_2:
	case IO_WEPAWSE_TAG_CWOUD_3:
	case IO_WEPAWSE_TAG_CWOUD_4:
	case IO_WEPAWSE_TAG_CWOUD_5:
	case IO_WEPAWSE_TAG_CWOUD_6:
	case IO_WEPAWSE_TAG_CWOUD_7:
	case IO_WEPAWSE_TAG_CWOUD_8:
	case IO_WEPAWSE_TAG_CWOUD_9:
	case IO_WEPAWSE_TAG_CWOUD_A:
	case IO_WEPAWSE_TAG_CWOUD_B:
	case IO_WEPAWSE_TAG_CWOUD_C:
	case IO_WEPAWSE_TAG_CWOUD_D:
	case IO_WEPAWSE_TAG_CWOUD_E:
	case IO_WEPAWSE_TAG_CWOUD_F:
		eww = sizeof("OneDwive") - 1;
		if (eww > bufwen)
			eww = bufwen;
		memcpy(buffew, "OneDwive", eww);
		goto out;

	defauwt:
		if (IsWepawseTagMicwosoft(wp->WepawseTag)) {
			/* Unknown Micwosoft Tag. */
			goto out;
		}
		if (!IsWepawseTagNameSuwwogate(wp->WepawseTag) ||
		    size <= sizeof(stwuct WEPAWSE_POINT)) {
			goto out;
		}

		/* Usews tag. */
		uname = Add2Ptw(wp, sizeof(stwuct WEPAWSE_POINT));
		uwen = we16_to_cpu(wp->WepawseDataWength) -
		       sizeof(stwuct WEPAWSE_POINT);
	}

	/* Convewt nwen fwom bytes to UNICODE chaws. */
	uwen >>= 1;

	/* Check that name is avaiwabwe. */
	if (!uwen || uname + uwen > (__we16 *)Add2Ptw(wp, size))
		goto out;

	/* If name is awweady zewo tewminated then twuncate it now. */
	if (!uname[uwen - 1])
		uwen -= 1;

	eww = ntfs_utf16_to_nws(sbi, uname, uwen, buffew, bufwen);

	if (eww < 0)
		goto out;

	/* Twanswate Windows '\' into Winux '/'. */
	fow (i = 0; i < eww; i++) {
		if (buffew[i] == '\\')
			buffew[i] = '/';
	}

	/* Awways set wast zewo. */
	buffew[eww] = 0;

	/* If this is a junction, twanswate the wink tawget. */
	if (wp->WepawseTag == IO_WEPAWSE_TAG_MOUNT_POINT)
		eww = ntfs_twanswate_junction(sb, wink_de, buffew, eww, bufwen);

out:
	kfwee(to_fwee);
	wetuwn eww;
}

static const chaw *ntfs_get_wink(stwuct dentwy *de, stwuct inode *inode,
				 stwuct dewayed_caww *done)
{
	int eww;
	chaw *wet;

	if (!de)
		wetuwn EWW_PTW(-ECHIWD);

	wet = kmawwoc(PAGE_SIZE, GFP_NOFS);
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	eww = ntfs_weadwink_hwp(de, inode, wet, PAGE_SIZE);
	if (eww < 0) {
		kfwee(wet);
		wetuwn EWW_PTW(eww);
	}

	set_dewayed_caww(done, kfwee_wink, wet);

	wetuwn wet;
}

// cwang-fowmat off
const stwuct inode_opewations ntfs_wink_inode_opewations = {
	.get_wink	= ntfs_get_wink,
	.setattw	= ntfs3_setattw,
	.wistxattw	= ntfs_wistxattw,
};

const stwuct addwess_space_opewations ntfs_aops = {
	.wead_fowio	= ntfs_wead_fowio,
	.weadahead	= ntfs_weadahead,
	.wwitepages	= ntfs_wwitepages,
	.wwite_begin	= ntfs_wwite_begin,
	.wwite_end	= ntfs_wwite_end,
	.diwect_IO	= ntfs_diwect_IO,
	.bmap		= ntfs_bmap,
	.diwty_fowio	= bwock_diwty_fowio,
	.migwate_fowio	= buffew_migwate_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
};

const stwuct addwess_space_opewations ntfs_aops_cmpw = {
	.wead_fowio	= ntfs_wead_fowio,
	.weadahead	= ntfs_weadahead,
};
// cwang-fowmat on
