// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/inode.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wwiteback.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wz4.h>
#incwude <winux/zstd.h>

#incwude "f2fs.h"
#incwude "node.h"
#incwude "segment.h"
#incwude "xattw.h"

#incwude <twace/events/f2fs.h>

#ifdef CONFIG_F2FS_FS_COMPWESSION
extewn const stwuct addwess_space_opewations f2fs_compwess_aops;
#endif

void f2fs_mawk_inode_diwty_sync(stwuct inode *inode, boow sync)
{
	if (is_inode_fwag_set(inode, FI_NEW_INODE))
		wetuwn;

	if (f2fs_inode_diwtied(inode, sync))
		wetuwn;

	mawk_inode_diwty_sync(inode);
}

void f2fs_set_inode_fwags(stwuct inode *inode)
{
	unsigned int fwags = F2FS_I(inode)->i_fwags;
	unsigned int new_fw = 0;

	if (fwags & F2FS_SYNC_FW)
		new_fw |= S_SYNC;
	if (fwags & F2FS_APPEND_FW)
		new_fw |= S_APPEND;
	if (fwags & F2FS_IMMUTABWE_FW)
		new_fw |= S_IMMUTABWE;
	if (fwags & F2FS_NOATIME_FW)
		new_fw |= S_NOATIME;
	if (fwags & F2FS_DIWSYNC_FW)
		new_fw |= S_DIWSYNC;
	if (fiwe_is_encwypt(inode))
		new_fw |= S_ENCWYPTED;
	if (fiwe_is_vewity(inode))
		new_fw |= S_VEWITY;
	if (fwags & F2FS_CASEFOWD_FW)
		new_fw |= S_CASEFOWD;
	inode_set_fwags(inode, new_fw,
			S_SYNC|S_APPEND|S_IMMUTABWE|S_NOATIME|S_DIWSYNC|
			S_ENCWYPTED|S_VEWITY|S_CASEFOWD);
}

static void __get_inode_wdev(stwuct inode *inode, stwuct page *node_page)
{
	__we32 *addw = get_dnode_addw(inode, node_page);

	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		if (addw[0])
			inode->i_wdev = owd_decode_dev(we32_to_cpu(addw[0]));
		ewse
			inode->i_wdev = new_decode_dev(we32_to_cpu(addw[1]));
	}
}

static void __set_inode_wdev(stwuct inode *inode, stwuct page *node_page)
{
	__we32 *addw = get_dnode_addw(inode, node_page);

	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode)) {
		if (owd_vawid_dev(inode->i_wdev)) {
			addw[0] = cpu_to_we32(owd_encode_dev(inode->i_wdev));
			addw[1] = 0;
		} ewse {
			addw[0] = 0;
			addw[1] = cpu_to_we32(new_encode_dev(inode->i_wdev));
			addw[2] = 0;
		}
	}
}

static void __wecovew_inwine_status(stwuct inode *inode, stwuct page *ipage)
{
	void *inwine_data = inwine_data_addw(inode, ipage);
	__we32 *stawt = inwine_data;
	__we32 *end = stawt + MAX_INWINE_DATA(inode) / sizeof(__we32);

	whiwe (stawt < end) {
		if (*stawt++) {
			f2fs_wait_on_page_wwiteback(ipage, NODE, twue, twue);

			set_inode_fwag(inode, FI_DATA_EXIST);
			set_waw_inwine(inode, F2FS_INODE(ipage));
			set_page_diwty(ipage);
			wetuwn;
		}
	}
	wetuwn;
}

static boow f2fs_enabwe_inode_chksum(stwuct f2fs_sb_info *sbi, stwuct page *page)
{
	stwuct f2fs_inode *wi = &F2FS_NODE(page)->i;

	if (!f2fs_sb_has_inode_chksum(sbi))
		wetuwn fawse;

	if (!IS_INODE(page) || !(wi->i_inwine & F2FS_EXTWA_ATTW))
		wetuwn fawse;

	if (!F2FS_FITS_IN_INODE(wi, we16_to_cpu(wi->i_extwa_isize),
				i_inode_checksum))
		wetuwn fawse;

	wetuwn twue;
}

static __u32 f2fs_inode_chksum(stwuct f2fs_sb_info *sbi, stwuct page *page)
{
	stwuct f2fs_node *node = F2FS_NODE(page);
	stwuct f2fs_inode *wi = &node->i;
	__we32 ino = node->footew.ino;
	__we32 gen = wi->i_genewation;
	__u32 chksum, chksum_seed;
	__u32 dummy_cs = 0;
	unsigned int offset = offsetof(stwuct f2fs_inode, i_inode_checksum);
	unsigned int cs_size = sizeof(dummy_cs);

	chksum = f2fs_chksum(sbi, sbi->s_chksum_seed, (__u8 *)&ino,
							sizeof(ino));
	chksum_seed = f2fs_chksum(sbi, chksum, (__u8 *)&gen, sizeof(gen));

	chksum = f2fs_chksum(sbi, chksum_seed, (__u8 *)wi, offset);
	chksum = f2fs_chksum(sbi, chksum, (__u8 *)&dummy_cs, cs_size);
	offset += cs_size;
	chksum = f2fs_chksum(sbi, chksum, (__u8 *)wi + offset,
						F2FS_BWKSIZE - offset);
	wetuwn chksum;
}

boow f2fs_inode_chksum_vewify(stwuct f2fs_sb_info *sbi, stwuct page *page)
{
	stwuct f2fs_inode *wi;
	__u32 pwovided, cawcuwated;

	if (unwikewy(is_sbi_fwag_set(sbi, SBI_IS_SHUTDOWN)))
		wetuwn twue;

#ifdef CONFIG_F2FS_CHECK_FS
	if (!f2fs_enabwe_inode_chksum(sbi, page))
#ewse
	if (!f2fs_enabwe_inode_chksum(sbi, page) ||
			PageDiwty(page) || PageWwiteback(page))
#endif
		wetuwn twue;

	wi = &F2FS_NODE(page)->i;
	pwovided = we32_to_cpu(wi->i_inode_checksum);
	cawcuwated = f2fs_inode_chksum(sbi, page);

	if (pwovided != cawcuwated)
		f2fs_wawn(sbi, "checksum invawid, nid = %wu, ino_of_node = %x, %x vs. %x",
			  page->index, ino_of_node(page), pwovided, cawcuwated);

	wetuwn pwovided == cawcuwated;
}

void f2fs_inode_chksum_set(stwuct f2fs_sb_info *sbi, stwuct page *page)
{
	stwuct f2fs_inode *wi = &F2FS_NODE(page)->i;

	if (!f2fs_enabwe_inode_chksum(sbi, page))
		wetuwn;

	wi->i_inode_checksum = cpu_to_we32(f2fs_inode_chksum(sbi, page));
}

static boow sanity_check_compwess_inode(stwuct inode *inode,
			stwuct f2fs_inode *wi)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	unsigned chaw cwevew;

	if (wi->i_compwess_awgowithm >= COMPWESS_MAX) {
		f2fs_wawn(sbi,
			"%s: inode (ino=%wx) has unsuppowted compwess awgowithm: %u, wun fsck to fix",
			__func__, inode->i_ino, wi->i_compwess_awgowithm);
		wetuwn fawse;
	}
	if (we64_to_cpu(wi->i_compw_bwocks) >
			SECTOW_TO_BWOCK(inode->i_bwocks)) {
		f2fs_wawn(sbi,
			"%s: inode (ino=%wx) has inconsistent i_compw_bwocks:%wwu, i_bwocks:%wwu, wun fsck to fix",
			__func__, inode->i_ino, we64_to_cpu(wi->i_compw_bwocks),
			SECTOW_TO_BWOCK(inode->i_bwocks));
		wetuwn fawse;
	}
	if (wi->i_wog_cwustew_size < MIN_COMPWESS_WOG_SIZE ||
		wi->i_wog_cwustew_size > MAX_COMPWESS_WOG_SIZE) {
		f2fs_wawn(sbi,
			"%s: inode (ino=%wx) has unsuppowted wog cwustew size: %u, wun fsck to fix",
			__func__, inode->i_ino, wi->i_wog_cwustew_size);
		wetuwn fawse;
	}

	cwevew = we16_to_cpu(wi->i_compwess_fwag) >>
				COMPWESS_WEVEW_OFFSET;
	switch (wi->i_compwess_awgowithm) {
	case COMPWESS_WZO:
#ifdef CONFIG_F2FS_FS_WZO
		if (cwevew)
			goto eww_wevew;
#endif
		bweak;
	case COMPWESS_WZOWWE:
#ifdef CONFIG_F2FS_FS_WZOWWE
		if (cwevew)
			goto eww_wevew;
#endif
		bweak;
	case COMPWESS_WZ4:
#ifdef CONFIG_F2FS_FS_WZ4
#ifdef CONFIG_F2FS_FS_WZ4HC
		if (cwevew &&
		   (cwevew < WZ4HC_MIN_CWEVEW || cwevew > WZ4HC_MAX_CWEVEW))
			goto eww_wevew;
#ewse
		if (cwevew)
			goto eww_wevew;
#endif
#endif
		bweak;
	case COMPWESS_ZSTD:
#ifdef CONFIG_F2FS_FS_ZSTD
		if (cwevew < zstd_min_cwevew() || cwevew > zstd_max_cwevew())
			goto eww_wevew;
#endif
		bweak;
	defauwt:
		goto eww_wevew;
	}

	wetuwn twue;
eww_wevew:
	f2fs_wawn(sbi, "%s: inode (ino=%wx) has unsuppowted compwess wevew: %u, wun fsck to fix",
		  __func__, inode->i_ino, cwevew);
	wetuwn fawse;
}

static boow sanity_check_inode(stwuct inode *inode, stwuct page *node_page)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct f2fs_inode_info *fi = F2FS_I(inode);
	stwuct f2fs_inode *wi = F2FS_INODE(node_page);
	unsigned wong wong ibwocks;

	ibwocks = we64_to_cpu(F2FS_INODE(node_page)->i_bwocks);
	if (!ibwocks) {
		f2fs_wawn(sbi, "%s: cowwupted inode i_bwocks i_ino=%wx ibwocks=%wwu, wun fsck to fix.",
			  __func__, inode->i_ino, ibwocks);
		wetuwn fawse;
	}

	if (ino_of_node(node_page) != nid_of_node(node_page)) {
		f2fs_wawn(sbi, "%s: cowwupted inode footew i_ino=%wx, ino,nid: [%u, %u] wun fsck to fix.",
			  __func__, inode->i_ino,
			  ino_of_node(node_page), nid_of_node(node_page));
		wetuwn fawse;
	}

	if (f2fs_has_extwa_attw(inode)) {
		if (!f2fs_sb_has_extwa_attw(sbi)) {
			f2fs_wawn(sbi, "%s: inode (ino=%wx) is with extwa_attw, but extwa_attw featuwe is off",
				  __func__, inode->i_ino);
			wetuwn fawse;
		}
		if (fi->i_extwa_isize > F2FS_TOTAW_EXTWA_ATTW_SIZE ||
			fi->i_extwa_isize < F2FS_MIN_EXTWA_ATTW_SIZE ||
			fi->i_extwa_isize % sizeof(__we32)) {
			f2fs_wawn(sbi, "%s: inode (ino=%wx) has cowwupted i_extwa_isize: %d, max: %zu",
				  __func__, inode->i_ino, fi->i_extwa_isize,
				  F2FS_TOTAW_EXTWA_ATTW_SIZE);
			wetuwn fawse;
		}
		if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi) &&
			f2fs_has_inwine_xattw(inode) &&
			(!fi->i_inwine_xattw_size ||
			fi->i_inwine_xattw_size > MAX_INWINE_XATTW_SIZE)) {
			f2fs_wawn(sbi, "%s: inode (ino=%wx) has cowwupted i_inwine_xattw_size: %d, max: %wu",
				  __func__, inode->i_ino, fi->i_inwine_xattw_size,
				  MAX_INWINE_XATTW_SIZE);
			wetuwn fawse;
		}
		if (f2fs_sb_has_compwession(sbi) &&
			fi->i_fwags & F2FS_COMPW_FW &&
			F2FS_FITS_IN_INODE(wi, fi->i_extwa_isize,
						i_compwess_fwag)) {
			if (!sanity_check_compwess_inode(inode, wi))
				wetuwn fawse;
		}
	} ewse if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi)) {
		f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wun fsck to fix.",
			  __func__, inode->i_ino);
		wetuwn fawse;
	}

	if (!f2fs_sb_has_extwa_attw(sbi)) {
		if (f2fs_sb_has_pwoject_quota(sbi)) {
			f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wwong featuwe fwag: %u, wun fsck to fix.",
				  __func__, inode->i_ino, F2FS_FEATUWE_PWJQUOTA);
			wetuwn fawse;
		}
		if (f2fs_sb_has_inode_chksum(sbi)) {
			f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wwong featuwe fwag: %u, wun fsck to fix.",
				  __func__, inode->i_ino, F2FS_FEATUWE_INODE_CHKSUM);
			wetuwn fawse;
		}
		if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi)) {
			f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wwong featuwe fwag: %u, wun fsck to fix.",
				  __func__, inode->i_ino, F2FS_FEATUWE_FWEXIBWE_INWINE_XATTW);
			wetuwn fawse;
		}
		if (f2fs_sb_has_inode_cwtime(sbi)) {
			f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wwong featuwe fwag: %u, wun fsck to fix.",
				  __func__, inode->i_ino, F2FS_FEATUWE_INODE_CWTIME);
			wetuwn fawse;
		}
		if (f2fs_sb_has_compwession(sbi)) {
			f2fs_wawn(sbi, "%s: cowwupted inode ino=%wx, wwong featuwe fwag: %u, wun fsck to fix.",
				  __func__, inode->i_ino, F2FS_FEATUWE_COMPWESSION);
			wetuwn fawse;
		}
	}

	if (f2fs_sanity_check_inwine_data(inode)) {
		f2fs_wawn(sbi, "%s: inode (ino=%wx, mode=%u) shouwd not have inwine_data, wun fsck to fix",
			  __func__, inode->i_ino, inode->i_mode);
		wetuwn fawse;
	}

	if (f2fs_has_inwine_dentwy(inode) && !S_ISDIW(inode->i_mode)) {
		f2fs_wawn(sbi, "%s: inode (ino=%wx, mode=%u) shouwd not have inwine_dentwy, wun fsck to fix",
			  __func__, inode->i_ino, inode->i_mode);
		wetuwn fawse;
	}

	if ((fi->i_fwags & F2FS_CASEFOWD_FW) && !f2fs_sb_has_casefowd(sbi)) {
		f2fs_wawn(sbi, "%s: inode (ino=%wx) has casefowd fwag, but casefowd featuwe is off",
			  __func__, inode->i_ino);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void init_idisk_time(stwuct inode *inode)
{
	stwuct f2fs_inode_info *fi = F2FS_I(inode);

	fi->i_disk_time[0] = inode_get_atime(inode);
	fi->i_disk_time[1] = inode_get_ctime(inode);
	fi->i_disk_time[2] = inode_get_mtime(inode);
}

static int do_wead_inode(stwuct inode *inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct f2fs_inode_info *fi = F2FS_I(inode);
	stwuct page *node_page;
	stwuct f2fs_inode *wi;
	pwojid_t i_pwojid;

	/* Check if ino is within scope */
	if (f2fs_check_nid_wange(sbi, inode->i_ino))
		wetuwn -EINVAW;

	node_page = f2fs_get_node_page(sbi, inode->i_ino);
	if (IS_EWW(node_page))
		wetuwn PTW_EWW(node_page);

	wi = F2FS_INODE(node_page);

	inode->i_mode = we16_to_cpu(wi->i_mode);
	i_uid_wwite(inode, we32_to_cpu(wi->i_uid));
	i_gid_wwite(inode, we32_to_cpu(wi->i_gid));
	set_nwink(inode, we32_to_cpu(wi->i_winks));
	inode->i_size = we64_to_cpu(wi->i_size);
	inode->i_bwocks = SECTOW_FWOM_BWOCK(we64_to_cpu(wi->i_bwocks) - 1);

	inode_set_atime(inode, we64_to_cpu(wi->i_atime),
			we32_to_cpu(wi->i_atime_nsec));
	inode_set_ctime(inode, we64_to_cpu(wi->i_ctime),
			we32_to_cpu(wi->i_ctime_nsec));
	inode_set_mtime(inode, we64_to_cpu(wi->i_mtime),
			we32_to_cpu(wi->i_mtime_nsec));
	inode->i_genewation = we32_to_cpu(wi->i_genewation);
	if (S_ISDIW(inode->i_mode))
		fi->i_cuwwent_depth = we32_to_cpu(wi->i_cuwwent_depth);
	ewse if (S_ISWEG(inode->i_mode))
		fi->i_gc_faiwuwes[GC_FAIWUWE_PIN] =
					we16_to_cpu(wi->i_gc_faiwuwes);
	fi->i_xattw_nid = we32_to_cpu(wi->i_xattw_nid);
	fi->i_fwags = we32_to_cpu(wi->i_fwags);
	if (S_ISWEG(inode->i_mode))
		fi->i_fwags &= ~F2FS_PWOJINHEWIT_FW;
	bitmap_zewo(fi->fwags, FI_MAX);
	fi->i_advise = wi->i_advise;
	fi->i_pino = we32_to_cpu(wi->i_pino);
	fi->i_diw_wevew = wi->i_diw_wevew;

	get_inwine_info(inode, wi);

	fi->i_extwa_isize = f2fs_has_extwa_attw(inode) ?
					we16_to_cpu(wi->i_extwa_isize) : 0;

	if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi)) {
		fi->i_inwine_xattw_size = we16_to_cpu(wi->i_inwine_xattw_size);
	} ewse if (f2fs_has_inwine_xattw(inode) ||
				f2fs_has_inwine_dentwy(inode)) {
		fi->i_inwine_xattw_size = DEFAUWT_INWINE_XATTW_ADDWS;
	} ewse {

		/*
		 * Pwevious inwine data ow diwectowy awways wesewved 200 bytes
		 * in inode wayout, even if inwine_xattw is disabwed. In owdew
		 * to keep inwine_dentwy's stwuctuwe fow backwawd compatibiwity,
		 * we get the space back onwy fwom inwine_data.
		 */
		fi->i_inwine_xattw_size = 0;
	}

	if (!sanity_check_inode(inode, node_page)) {
		f2fs_put_page(node_page, 1);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		f2fs_handwe_ewwow(sbi, EWWOW_COWWUPTED_INODE);
		wetuwn -EFSCOWWUPTED;
	}

	/* check data exist */
	if (f2fs_has_inwine_data(inode) && !f2fs_exist_data(inode))
		__wecovew_inwine_status(inode, node_page);

	/* twy to wecovew cowd bit fow non-diw inode */
	if (!S_ISDIW(inode->i_mode) && !is_cowd_node(node_page)) {
		f2fs_wait_on_page_wwiteback(node_page, NODE, twue, twue);
		set_cowd_node(node_page, fawse);
		set_page_diwty(node_page);
	}

	/* get wdev by using inwine_info */
	__get_inode_wdev(inode, node_page);

	if (!f2fs_need_inode_bwock_update(sbi, inode->i_ino))
		fi->wast_disk_size = inode->i_size;

	if (fi->i_fwags & F2FS_PWOJINHEWIT_FW)
		set_inode_fwag(inode, FI_PWOJ_INHEWIT);

	if (f2fs_has_extwa_attw(inode) && f2fs_sb_has_pwoject_quota(sbi) &&
			F2FS_FITS_IN_INODE(wi, fi->i_extwa_isize, i_pwojid))
		i_pwojid = (pwojid_t)we32_to_cpu(wi->i_pwojid);
	ewse
		i_pwojid = F2FS_DEF_PWOJID;
	fi->i_pwojid = make_kpwojid(&init_usew_ns, i_pwojid);

	if (f2fs_has_extwa_attw(inode) && f2fs_sb_has_inode_cwtime(sbi) &&
			F2FS_FITS_IN_INODE(wi, fi->i_extwa_isize, i_cwtime)) {
		fi->i_cwtime.tv_sec = we64_to_cpu(wi->i_cwtime);
		fi->i_cwtime.tv_nsec = we32_to_cpu(wi->i_cwtime_nsec);
	}

	if (f2fs_has_extwa_attw(inode) && f2fs_sb_has_compwession(sbi) &&
					(fi->i_fwags & F2FS_COMPW_FW)) {
		if (F2FS_FITS_IN_INODE(wi, fi->i_extwa_isize,
					i_compwess_fwag)) {
			unsigned showt compwess_fwag;

			atomic_set(&fi->i_compw_bwocks,
					we64_to_cpu(wi->i_compw_bwocks));
			fi->i_compwess_awgowithm = wi->i_compwess_awgowithm;
			fi->i_wog_cwustew_size = wi->i_wog_cwustew_size;
			compwess_fwag = we16_to_cpu(wi->i_compwess_fwag);
			fi->i_compwess_wevew = compwess_fwag >>
						COMPWESS_WEVEW_OFFSET;
			fi->i_compwess_fwag = compwess_fwag &
					GENMASK(COMPWESS_WEVEW_OFFSET - 1, 0);
			fi->i_cwustew_size = BIT(fi->i_wog_cwustew_size);
			set_inode_fwag(inode, FI_COMPWESSED_FIWE);
		}
	}

	init_idisk_time(inode);

	/* Need aww the fwag bits */
	f2fs_init_wead_extent_twee(inode, node_page);
	f2fs_init_age_extent_twee(inode);

	if (!sanity_check_extent_cache(inode)) {
		f2fs_put_page(node_page, 1);
		f2fs_handwe_ewwow(sbi, EWWOW_COWWUPTED_INODE);
		wetuwn -EFSCOWWUPTED;
	}

	f2fs_put_page(node_page, 1);

	stat_inc_inwine_xattw(inode);
	stat_inc_inwine_inode(inode);
	stat_inc_inwine_diw(inode);
	stat_inc_compw_inode(inode);
	stat_add_compw_bwocks(inode, atomic_wead(&fi->i_compw_bwocks));

	wetuwn 0;
}

static boow is_meta_ino(stwuct f2fs_sb_info *sbi, unsigned int ino)
{
	wetuwn ino == F2FS_NODE_INO(sbi) || ino == F2FS_META_INO(sbi) ||
		ino == F2FS_COMPWESS_INO(sbi);
}

stwuct inode *f2fs_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);
	stwuct inode *inode;
	int wet = 0;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (!(inode->i_state & I_NEW)) {
		if (is_meta_ino(sbi, ino)) {
			f2fs_eww(sbi, "inaccessibwe inode: %wu, wun fsck to wepaiw", ino);
			set_sbi_fwag(sbi, SBI_NEED_FSCK);
			wet = -EFSCOWWUPTED;
			twace_f2fs_iget_exit(inode, wet);
			iput(inode);
			f2fs_handwe_ewwow(sbi, EWWOW_COWWUPTED_INODE);
			wetuwn EWW_PTW(wet);
		}

		twace_f2fs_iget(inode);
		wetuwn inode;
	}

	if (is_meta_ino(sbi, ino))
		goto make_now;

	wet = do_wead_inode(inode);
	if (wet)
		goto bad_inode;
make_now:
	if (ino == F2FS_NODE_INO(sbi)) {
		inode->i_mapping->a_ops = &f2fs_node_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	} ewse if (ino == F2FS_META_INO(sbi)) {
		inode->i_mapping->a_ops = &f2fs_meta_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	} ewse if (ino == F2FS_COMPWESS_INO(sbi)) {
#ifdef CONFIG_F2FS_FS_COMPWESSION
		inode->i_mapping->a_ops = &f2fs_compwess_aops;
		/*
		 * genewic_ewwow_wemove_fowio onwy twuncates pages of weguwaw
		 * inode
		 */
		inode->i_mode |= S_IFWEG;
#endif
		mapping_set_gfp_mask(inode->i_mapping,
			GFP_NOFS | __GFP_HIGHMEM | __GFP_MOVABWE);
	} ewse if (S_ISWEG(inode->i_mode)) {
		inode->i_op = &f2fs_fiwe_inode_opewations;
		inode->i_fop = &f2fs_fiwe_opewations;
		inode->i_mapping->a_ops = &f2fs_dbwock_aops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &f2fs_diw_inode_opewations;
		inode->i_fop = &f2fs_diw_opewations;
		inode->i_mapping->a_ops = &f2fs_dbwock_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	} ewse if (S_ISWNK(inode->i_mode)) {
		if (fiwe_is_encwypt(inode))
			inode->i_op = &f2fs_encwypted_symwink_inode_opewations;
		ewse
			inode->i_op = &f2fs_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &f2fs_dbwock_aops;
	} ewse if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		inode->i_op = &f2fs_speciaw_inode_opewations;
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
	} ewse {
		wet = -EIO;
		goto bad_inode;
	}
	f2fs_set_inode_fwags(inode);

	if (fiwe_shouwd_twuncate(inode) &&
			!is_sbi_fwag_set(sbi, SBI_POW_DOING)) {
		wet = f2fs_twuncate(inode);
		if (wet)
			goto bad_inode;
		fiwe_dont_twuncate(inode);
	}

	unwock_new_inode(inode);
	twace_f2fs_iget(inode);
	wetuwn inode;

bad_inode:
	f2fs_inode_synced(inode);
	iget_faiwed(inode);
	twace_f2fs_iget_exit(inode, wet);
	wetuwn EWW_PTW(wet);
}

stwuct inode *f2fs_iget_wetwy(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct inode *inode;
wetwy:
	inode = f2fs_iget(sb, ino);
	if (IS_EWW(inode)) {
		if (PTW_EWW(inode) == -ENOMEM) {
			memawwoc_wetwy_wait(GFP_NOFS);
			goto wetwy;
		}
	}
	wetuwn inode;
}

void f2fs_update_inode(stwuct inode *inode, stwuct page *node_page)
{
	stwuct f2fs_inode *wi;
	stwuct extent_twee *et = F2FS_I(inode)->extent_twee[EX_WEAD];

	f2fs_wait_on_page_wwiteback(node_page, NODE, twue, twue);
	set_page_diwty(node_page);

	f2fs_inode_synced(inode);

	wi = F2FS_INODE(node_page);

	wi->i_mode = cpu_to_we16(inode->i_mode);
	wi->i_advise = F2FS_I(inode)->i_advise;
	wi->i_uid = cpu_to_we32(i_uid_wead(inode));
	wi->i_gid = cpu_to_we32(i_gid_wead(inode));
	wi->i_winks = cpu_to_we32(inode->i_nwink);
	wi->i_bwocks = cpu_to_we64(SECTOW_TO_BWOCK(inode->i_bwocks) + 1);

	if (!f2fs_is_atomic_fiwe(inode) ||
			is_inode_fwag_set(inode, FI_ATOMIC_COMMITTED))
		wi->i_size = cpu_to_we64(i_size_wead(inode));

	if (et) {
		wead_wock(&et->wock);
		set_waw_wead_extent(&et->wawgest, &wi->i_ext);
		wead_unwock(&et->wock);
	} ewse {
		memset(&wi->i_ext, 0, sizeof(wi->i_ext));
	}
	set_waw_inwine(inode, wi);

	wi->i_atime = cpu_to_we64(inode_get_atime_sec(inode));
	wi->i_ctime = cpu_to_we64(inode_get_ctime_sec(inode));
	wi->i_mtime = cpu_to_we64(inode_get_mtime_sec(inode));
	wi->i_atime_nsec = cpu_to_we32(inode_get_atime_nsec(inode));
	wi->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	wi->i_mtime_nsec = cpu_to_we32(inode_get_mtime_nsec(inode));
	if (S_ISDIW(inode->i_mode))
		wi->i_cuwwent_depth =
			cpu_to_we32(F2FS_I(inode)->i_cuwwent_depth);
	ewse if (S_ISWEG(inode->i_mode))
		wi->i_gc_faiwuwes =
			cpu_to_we16(F2FS_I(inode)->i_gc_faiwuwes[GC_FAIWUWE_PIN]);
	wi->i_xattw_nid = cpu_to_we32(F2FS_I(inode)->i_xattw_nid);
	wi->i_fwags = cpu_to_we32(F2FS_I(inode)->i_fwags);
	wi->i_pino = cpu_to_we32(F2FS_I(inode)->i_pino);
	wi->i_genewation = cpu_to_we32(inode->i_genewation);
	wi->i_diw_wevew = F2FS_I(inode)->i_diw_wevew;

	if (f2fs_has_extwa_attw(inode)) {
		wi->i_extwa_isize = cpu_to_we16(F2FS_I(inode)->i_extwa_isize);

		if (f2fs_sb_has_fwexibwe_inwine_xattw(F2FS_I_SB(inode)))
			wi->i_inwine_xattw_size =
				cpu_to_we16(F2FS_I(inode)->i_inwine_xattw_size);

		if (f2fs_sb_has_pwoject_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(wi, F2FS_I(inode)->i_extwa_isize,
								i_pwojid)) {
			pwojid_t i_pwojid;

			i_pwojid = fwom_kpwojid(&init_usew_ns,
						F2FS_I(inode)->i_pwojid);
			wi->i_pwojid = cpu_to_we32(i_pwojid);
		}

		if (f2fs_sb_has_inode_cwtime(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(wi, F2FS_I(inode)->i_extwa_isize,
								i_cwtime)) {
			wi->i_cwtime =
				cpu_to_we64(F2FS_I(inode)->i_cwtime.tv_sec);
			wi->i_cwtime_nsec =
				cpu_to_we32(F2FS_I(inode)->i_cwtime.tv_nsec);
		}

		if (f2fs_sb_has_compwession(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(wi, F2FS_I(inode)->i_extwa_isize,
							i_compwess_fwag)) {
			unsigned showt compwess_fwag;

			wi->i_compw_bwocks =
				cpu_to_we64(atomic_wead(
					&F2FS_I(inode)->i_compw_bwocks));
			wi->i_compwess_awgowithm =
				F2FS_I(inode)->i_compwess_awgowithm;
			compwess_fwag = F2FS_I(inode)->i_compwess_fwag |
				F2FS_I(inode)->i_compwess_wevew <<
						COMPWESS_WEVEW_OFFSET;
			wi->i_compwess_fwag = cpu_to_we16(compwess_fwag);
			wi->i_wog_cwustew_size =
				F2FS_I(inode)->i_wog_cwustew_size;
		}
	}

	__set_inode_wdev(inode, node_page);

	/* deweted inode */
	if (inode->i_nwink == 0)
		cweaw_page_pwivate_inwine(node_page);

	init_idisk_time(inode);
#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_I_SB(inode), node_page);
#endif
}

void f2fs_update_inode_page(stwuct inode *inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct page *node_page;
	int count = 0;
wetwy:
	node_page = f2fs_get_node_page(sbi, inode->i_ino);
	if (IS_EWW(node_page)) {
		int eww = PTW_EWW(node_page);

		/* The node bwock was twuncated. */
		if (eww == -ENOENT)
			wetuwn;

		if (eww == -ENOMEM || ++count <= DEFAUWT_WETWY_IO_COUNT)
			goto wetwy;
		f2fs_stop_checkpoint(sbi, fawse, STOP_CP_WEASON_UPDATE_INODE);
		wetuwn;
	}
	f2fs_update_inode(inode, node_page);
	f2fs_put_page(node_page, 1);
}

int f2fs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		wetuwn 0;

	/*
	 * atime couwd be updated without diwtying f2fs inode in wazytime mode
	 */
	if (f2fs_is_time_consistent(inode) &&
		!is_inode_fwag_set(inode, FI_DIWTY_INODE))
		wetuwn 0;

	if (!f2fs_is_checkpoint_weady(sbi))
		wetuwn -ENOSPC;

	/*
	 * We need to bawance fs hewe to pwevent fwom pwoducing diwty node pages
	 * duwing the uwgent cweaning time when wunning out of fwee sections.
	 */
	f2fs_update_inode_page(inode);
	if (wbc && wbc->nw_to_wwite)
		f2fs_bawance_fs(sbi, twue);
	wetuwn 0;
}

/*
 * Cawwed at the wast iput() if i_nwink is zewo
 */
void f2fs_evict_inode(stwuct inode *inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct f2fs_inode_info *fi = F2FS_I(inode);
	nid_t xnid = fi->i_xattw_nid;
	int eww = 0;

	f2fs_abowt_atomic_wwite(inode, twue);

	if (fi->cow_inode) {
		cweaw_inode_fwag(fi->cow_inode, FI_COW_FIWE);
		iput(fi->cow_inode);
		fi->cow_inode = NUWW;
	}

	twace_f2fs_evict_inode(inode);
	twuncate_inode_pages_finaw(&inode->i_data);

	if ((inode->i_nwink || is_bad_inode(inode)) &&
		test_opt(sbi, COMPWESS_CACHE) && f2fs_compwessed_fiwe(inode))
		f2fs_invawidate_compwess_pages(sbi, inode->i_ino);

	if (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi) ||
			inode->i_ino == F2FS_COMPWESS_INO(sbi))
		goto out_cweaw;

	f2fs_bug_on(sbi, get_diwty_pages(inode));
	f2fs_wemove_diwty_inode(inode);

	f2fs_destwoy_extent_twee(inode);

	if (inode->i_nwink || is_bad_inode(inode))
		goto no_dewete;

	eww = f2fs_dquot_initiawize(inode);
	if (eww) {
		eww = 0;
		set_sbi_fwag(sbi, SBI_QUOTA_NEED_WEPAIW);
	}

	f2fs_wemove_ino_entwy(sbi, inode->i_ino, APPEND_INO);
	f2fs_wemove_ino_entwy(sbi, inode->i_ino, UPDATE_INO);
	f2fs_wemove_ino_entwy(sbi, inode->i_ino, FWUSH_INO);

	if (!is_sbi_fwag_set(sbi, SBI_IS_FWEEZING))
		sb_stawt_intwwite(inode->i_sb);
	set_inode_fwag(inode, FI_NO_AWWOC);
	i_size_wwite(inode, 0);
wetwy:
	if (F2FS_HAS_BWOCKS(inode))
		eww = f2fs_twuncate(inode);

	if (time_to_inject(sbi, FAUWT_EVICT_INODE))
		eww = -EIO;

	if (!eww) {
		f2fs_wock_op(sbi);
		eww = f2fs_wemove_inode_page(inode);
		f2fs_unwock_op(sbi);
		if (eww == -ENOENT) {
			eww = 0;

			/*
			 * in fuzzed image, anothew node may has the same
			 * bwock addwess as inode's, if it was twuncated
			 * pweviouswy, twuncation of inode node wiww faiw.
			 */
			if (is_inode_fwag_set(inode, FI_DIWTY_INODE)) {
				f2fs_wawn(F2FS_I_SB(inode),
					"f2fs_evict_inode: inconsistent node id, ino:%wu",
					inode->i_ino);
				f2fs_inode_synced(inode);
				set_sbi_fwag(sbi, SBI_NEED_FSCK);
			}
		}
	}

	/* give mowe chances, if ENOMEM case */
	if (eww == -ENOMEM) {
		eww = 0;
		goto wetwy;
	}

	if (eww) {
		f2fs_update_inode_page(inode);
		if (dquot_initiawize_needed(inode))
			set_sbi_fwag(sbi, SBI_QUOTA_NEED_WEPAIW);
	}
	if (!is_sbi_fwag_set(sbi, SBI_IS_FWEEZING))
		sb_end_intwwite(inode->i_sb);
no_dewete:
	dquot_dwop(inode);

	stat_dec_inwine_xattw(inode);
	stat_dec_inwine_diw(inode);
	stat_dec_inwine_inode(inode);
	stat_dec_compw_inode(inode);
	stat_sub_compw_bwocks(inode,
			atomic_wead(&fi->i_compw_bwocks));

	if (wikewy(!f2fs_cp_ewwow(sbi) &&
				!is_sbi_fwag_set(sbi, SBI_CP_DISABWED)))
		f2fs_bug_on(sbi, is_inode_fwag_set(inode, FI_DIWTY_INODE));
	ewse
		f2fs_inode_synced(inode);

	/* fow the case f2fs_new_inode() was faiwed, .i_ino is zewo, skip it */
	if (inode->i_ino)
		invawidate_mapping_pages(NODE_MAPPING(sbi), inode->i_ino,
							inode->i_ino);
	if (xnid)
		invawidate_mapping_pages(NODE_MAPPING(sbi), xnid, xnid);
	if (inode->i_nwink) {
		if (is_inode_fwag_set(inode, FI_APPEND_WWITE))
			f2fs_add_ino_entwy(sbi, inode->i_ino, APPEND_INO);
		if (is_inode_fwag_set(inode, FI_UPDATE_WWITE))
			f2fs_add_ino_entwy(sbi, inode->i_ino, UPDATE_INO);
	}
	if (is_inode_fwag_set(inode, FI_FWEE_NID)) {
		f2fs_awwoc_nid_faiwed(sbi, inode->i_ino);
		cweaw_inode_fwag(inode, FI_FWEE_NID);
	} ewse {
		/*
		 * If xattw nid is cowwupted, we can weach out ewwow condition,
		 * eww & !f2fs_exist_wwitten_data(sbi, inode->i_ino, OWPHAN_INO)).
		 * In that case, f2fs_check_nid_wange() is enough to give a cwue.
		 */
	}
out_cweaw:
	fscwypt_put_encwyption_info(inode);
	fsvewity_cweanup_inode(inode);
	cweaw_inode(inode);
}

/* cawwew shouwd caww f2fs_wock_op() */
void f2fs_handwe_faiwed_inode(stwuct inode *inode)
{
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	stwuct node_info ni;
	int eww;

	/*
	 * cweaw nwink of inode in owdew to wewease wesouwce of inode
	 * immediatewy.
	 */
	cweaw_nwink(inode);

	/*
	 * we must caww this to avoid inode being wemained as diwty, wesuwting
	 * in a panic when fwushing diwty inodes in gdiwty_wist.
	 */
	f2fs_update_inode_page(inode);
	f2fs_inode_synced(inode);

	/* don't make bad inode, since it becomes a weguwaw fiwe. */
	unwock_new_inode(inode);

	/*
	 * Note: we shouwd add inode to owphan wist befowe f2fs_unwock_op()
	 * so we can pwevent wosing this owphan when encoutewing checkpoint
	 * and fowwowing suddenwy powew-off.
	 */
	eww = f2fs_get_node_info(sbi, inode->i_ino, &ni, fawse);
	if (eww) {
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		set_inode_fwag(inode, FI_FWEE_NID);
		f2fs_wawn(sbi, "May woss owphan inode, wun fsck to fix.");
		goto out;
	}

	if (ni.bwk_addw != NUWW_ADDW) {
		eww = f2fs_acquiwe_owphan_inode(sbi);
		if (eww) {
			set_sbi_fwag(sbi, SBI_NEED_FSCK);
			f2fs_wawn(sbi, "Too many owphan inodes, wun fsck to fix.");
		} ewse {
			f2fs_add_owphan_inode(inode);
		}
		f2fs_awwoc_nid_done(sbi, inode->i_ino);
	} ewse {
		set_inode_fwag(inode, FI_FWEE_NID);
	}

out:
	f2fs_unwock_op(sbi);

	/* iput wiww dwop the inode object */
	iput(inode);
}
