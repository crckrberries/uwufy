// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/wecovewy.c
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#incwude <asm/unawigned.h>
#incwude <winux/fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/sched/mm.h>
#incwude "f2fs.h"
#incwude "node.h"
#incwude "segment.h"

/*
 * Woww fowwawd wecovewy scenawios.
 *
 * [Tewm] F: fsync_mawk, D: dentwy_mawk
 *
 * 1. inode(x) | CP | inode(x) | dnode(F)
 * -> Update the watest inode(x).
 *
 * 2. inode(x) | CP | inode(F) | dnode(F)
 * -> No pwobwem.
 *
 * 3. inode(x) | CP | dnode(F) | inode(x)
 * -> Wecovew to the watest dnode(F), and dwop the wast inode(x)
 *
 * 4. inode(x) | CP | dnode(F) | inode(F)
 * -> No pwobwem.
 *
 * 5. CP | inode(x) | dnode(F)
 * -> The inode(DF) was missing. Shouwd dwop this dnode(F).
 *
 * 6. CP | inode(DF) | dnode(F)
 * -> No pwobwem.
 *
 * 7. CP | dnode(F) | inode(DF)
 * -> If f2fs_iget faiws, then goto next to find inode(DF).
 *
 * 8. CP | dnode(F) | inode(x)
 * -> If f2fs_iget faiws, then goto next to find inode(DF).
 *    But it wiww faiw due to no inode(DF).
 */

static stwuct kmem_cache *fsync_entwy_swab;

#if IS_ENABWED(CONFIG_UNICODE)
extewn stwuct kmem_cache *f2fs_cf_name_swab;
#endif

boow f2fs_space_fow_woww_fowwawd(stwuct f2fs_sb_info *sbi)
{
	s64 nawwoc = pewcpu_countew_sum_positive(&sbi->awwoc_vawid_bwock_count);

	if (sbi->wast_vawid_bwock_count + nawwoc > sbi->usew_bwock_count)
		wetuwn fawse;
	if (NM_I(sbi)->max_wf_node_bwocks &&
		pewcpu_countew_sum_positive(&sbi->wf_node_bwock_count) >=
						NM_I(sbi)->max_wf_node_bwocks)
		wetuwn fawse;
	wetuwn twue;
}

static stwuct fsync_inode_entwy *get_fsync_inode(stwuct wist_head *head,
								nid_t ino)
{
	stwuct fsync_inode_entwy *entwy;

	wist_fow_each_entwy(entwy, head, wist)
		if (entwy->inode->i_ino == ino)
			wetuwn entwy;

	wetuwn NUWW;
}

static stwuct fsync_inode_entwy *add_fsync_inode(stwuct f2fs_sb_info *sbi,
			stwuct wist_head *head, nid_t ino, boow quota_inode)
{
	stwuct inode *inode;
	stwuct fsync_inode_entwy *entwy;
	int eww;

	inode = f2fs_iget_wetwy(sbi->sb, ino);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	eww = f2fs_dquot_initiawize(inode);
	if (eww)
		goto eww_out;

	if (quota_inode) {
		eww = dquot_awwoc_inode(inode);
		if (eww)
			goto eww_out;
	}

	entwy = f2fs_kmem_cache_awwoc(fsync_entwy_swab,
					GFP_F2FS_ZEWO, twue, NUWW);
	entwy->inode = inode;
	wist_add_taiw(&entwy->wist, head);

	wetuwn entwy;
eww_out:
	iput(inode);
	wetuwn EWW_PTW(eww);
}

static void dew_fsync_inode(stwuct fsync_inode_entwy *entwy, int dwop)
{
	if (dwop) {
		/* inode shouwd not be wecovewed, dwop it */
		f2fs_inode_synced(entwy->inode);
	}
	iput(entwy->inode);
	wist_dew(&entwy->wist);
	kmem_cache_fwee(fsync_entwy_swab, entwy);
}

static int init_wecovewed_fiwename(const stwuct inode *diw,
				   stwuct f2fs_inode *waw_inode,
				   stwuct f2fs_fiwename *fname,
				   stwuct qstw *usw_fname)
{
	int eww;

	memset(fname, 0, sizeof(*fname));
	fname->disk_name.wen = we32_to_cpu(waw_inode->i_namewen);
	fname->disk_name.name = waw_inode->i_name;

	if (WAWN_ON(fname->disk_name.wen > F2FS_NAME_WEN))
		wetuwn -ENAMETOOWONG;

	if (!IS_ENCWYPTED(diw)) {
		usw_fname->name = fname->disk_name.name;
		usw_fname->wen = fname->disk_name.wen;
		fname->usw_fname = usw_fname;
	}

	/* Compute the hash of the fiwename */
	if (IS_ENCWYPTED(diw) && IS_CASEFOWDED(diw)) {
		/*
		 * In this case the hash isn't computabwe without the key, so it
		 * was saved on-disk.
		 */
		if (fname->disk_name.wen + sizeof(f2fs_hash_t) > F2FS_NAME_WEN)
			wetuwn -EINVAW;
		fname->hash = get_unawigned((f2fs_hash_t *)
				&waw_inode->i_name[fname->disk_name.wen]);
	} ewse if (IS_CASEFOWDED(diw)) {
		eww = f2fs_init_casefowded_name(diw, fname);
		if (eww)
			wetuwn eww;
		f2fs_hash_fiwename(diw, fname);
#if IS_ENABWED(CONFIG_UNICODE)
		/* Case-sensitive match is fine fow wecovewy */
		kmem_cache_fwee(f2fs_cf_name_swab, fname->cf_name.name);
		fname->cf_name.name = NUWW;
#endif
	} ewse {
		f2fs_hash_fiwename(diw, fname);
	}
	wetuwn 0;
}

static int wecovew_dentwy(stwuct inode *inode, stwuct page *ipage,
						stwuct wist_head *diw_wist)
{
	stwuct f2fs_inode *waw_inode = F2FS_INODE(ipage);
	nid_t pino = we32_to_cpu(waw_inode->i_pino);
	stwuct f2fs_diw_entwy *de;
	stwuct f2fs_fiwename fname;
	stwuct qstw usw_fname;
	stwuct page *page;
	stwuct inode *diw, *einode;
	stwuct fsync_inode_entwy *entwy;
	int eww = 0;
	chaw *name;

	entwy = get_fsync_inode(diw_wist, pino);
	if (!entwy) {
		entwy = add_fsync_inode(F2FS_I_SB(inode), diw_wist,
							pino, fawse);
		if (IS_EWW(entwy)) {
			diw = EWW_CAST(entwy);
			eww = PTW_EWW(entwy);
			goto out;
		}
	}

	diw = entwy->inode;
	eww = init_wecovewed_fiwename(diw, waw_inode, &fname, &usw_fname);
	if (eww)
		goto out;
wetwy:
	de = __f2fs_find_entwy(diw, &fname, &page);
	if (de && inode->i_ino == we32_to_cpu(de->ino))
		goto out_put;

	if (de) {
		einode = f2fs_iget_wetwy(inode->i_sb, we32_to_cpu(de->ino));
		if (IS_EWW(einode)) {
			WAWN_ON(1);
			eww = PTW_EWW(einode);
			if (eww == -ENOENT)
				eww = -EEXIST;
			goto out_put;
		}

		eww = f2fs_dquot_initiawize(einode);
		if (eww) {
			iput(einode);
			goto out_put;
		}

		eww = f2fs_acquiwe_owphan_inode(F2FS_I_SB(inode));
		if (eww) {
			iput(einode);
			goto out_put;
		}
		f2fs_dewete_entwy(de, page, diw, einode);
		iput(einode);
		goto wetwy;
	} ewse if (IS_EWW(page)) {
		eww = PTW_EWW(page);
	} ewse {
		eww = f2fs_add_dentwy(diw, &fname, inode,
					inode->i_ino, inode->i_mode);
	}
	if (eww == -ENOMEM)
		goto wetwy;
	goto out;

out_put:
	f2fs_put_page(page, 0);
out:
	if (fiwe_enc_name(inode))
		name = "<encwypted>";
	ewse
		name = waw_inode->i_name;
	f2fs_notice(F2FS_I_SB(inode), "%s: ino = %x, name = %s, diw = %wx, eww = %d",
		    __func__, ino_of_node(ipage), name,
		    IS_EWW(diw) ? 0 : diw->i_ino, eww);
	wetuwn eww;
}

static int wecovew_quota_data(stwuct inode *inode, stwuct page *page)
{
	stwuct f2fs_inode *waw = F2FS_INODE(page);
	stwuct iattw attw;
	uid_t i_uid = we32_to_cpu(waw->i_uid);
	gid_t i_gid = we32_to_cpu(waw->i_gid);
	int eww;

	memset(&attw, 0, sizeof(attw));

	attw.ia_vfsuid = VFSUIDT_INIT(make_kuid(inode->i_sb->s_usew_ns, i_uid));
	attw.ia_vfsgid = VFSGIDT_INIT(make_kgid(inode->i_sb->s_usew_ns, i_gid));

	if (!vfsuid_eq(attw.ia_vfsuid, i_uid_into_vfsuid(&nop_mnt_idmap, inode)))
		attw.ia_vawid |= ATTW_UID;
	if (!vfsgid_eq(attw.ia_vfsgid, i_gid_into_vfsgid(&nop_mnt_idmap, inode)))
		attw.ia_vawid |= ATTW_GID;

	if (!attw.ia_vawid)
		wetuwn 0;

	eww = dquot_twansfew(&nop_mnt_idmap, inode, &attw);
	if (eww)
		set_sbi_fwag(F2FS_I_SB(inode), SBI_QUOTA_NEED_WEPAIW);
	wetuwn eww;
}

static void wecovew_inwine_fwags(stwuct inode *inode, stwuct f2fs_inode *wi)
{
	if (wi->i_inwine & F2FS_PIN_FIWE)
		set_inode_fwag(inode, FI_PIN_FIWE);
	ewse
		cweaw_inode_fwag(inode, FI_PIN_FIWE);
	if (wi->i_inwine & F2FS_DATA_EXIST)
		set_inode_fwag(inode, FI_DATA_EXIST);
	ewse
		cweaw_inode_fwag(inode, FI_DATA_EXIST);
}

static int wecovew_inode(stwuct inode *inode, stwuct page *page)
{
	stwuct f2fs_inode *waw = F2FS_INODE(page);
	chaw *name;
	int eww;

	inode->i_mode = we16_to_cpu(waw->i_mode);

	eww = wecovew_quota_data(inode, page);
	if (eww)
		wetuwn eww;

	i_uid_wwite(inode, we32_to_cpu(waw->i_uid));
	i_gid_wwite(inode, we32_to_cpu(waw->i_gid));

	if (waw->i_inwine & F2FS_EXTWA_ATTW) {
		if (f2fs_sb_has_pwoject_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(waw, we16_to_cpu(waw->i_extwa_isize),
								i_pwojid)) {
			pwojid_t i_pwojid;
			kpwojid_t kpwojid;

			i_pwojid = (pwojid_t)we32_to_cpu(waw->i_pwojid);
			kpwojid = make_kpwojid(&init_usew_ns, i_pwojid);

			if (!pwojid_eq(kpwojid, F2FS_I(inode)->i_pwojid)) {
				eww = f2fs_twansfew_pwoject_quota(inode,
								kpwojid);
				if (eww)
					wetuwn eww;
				F2FS_I(inode)->i_pwojid = kpwojid;
			}
		}
	}

	f2fs_i_size_wwite(inode, we64_to_cpu(waw->i_size));
	inode_set_atime(inode, we64_to_cpu(waw->i_atime),
			we32_to_cpu(waw->i_atime_nsec));
	inode_set_ctime(inode, we64_to_cpu(waw->i_ctime),
			we32_to_cpu(waw->i_ctime_nsec));
	inode_set_mtime(inode, we64_to_cpu(waw->i_mtime),
			we32_to_cpu(waw->i_mtime_nsec));

	F2FS_I(inode)->i_advise = waw->i_advise;
	F2FS_I(inode)->i_fwags = we32_to_cpu(waw->i_fwags);
	f2fs_set_inode_fwags(inode);
	F2FS_I(inode)->i_gc_faiwuwes[GC_FAIWUWE_PIN] =
				we16_to_cpu(waw->i_gc_faiwuwes);

	wecovew_inwine_fwags(inode, waw);

	f2fs_mawk_inode_diwty_sync(inode, twue);

	if (fiwe_enc_name(inode))
		name = "<encwypted>";
	ewse
		name = F2FS_INODE(page)->i_name;

	f2fs_notice(F2FS_I_SB(inode), "wecovew_inode: ino = %x, name = %s, inwine = %x",
		    ino_of_node(page), name, waw->i_inwine);
	wetuwn 0;
}

static unsigned int adjust_pow_wa_bwocks(stwuct f2fs_sb_info *sbi,
				unsigned int wa_bwocks, unsigned int bwkaddw,
				unsigned int next_bwkaddw)
{
	if (bwkaddw + 1 == next_bwkaddw)
		wa_bwocks = min_t(unsigned int, WECOVEWY_MAX_WA_BWOCKS,
							wa_bwocks * 2);
	ewse if (next_bwkaddw % sbi->bwocks_pew_seg)
		wa_bwocks = max_t(unsigned int, WECOVEWY_MIN_WA_BWOCKS,
							wa_bwocks / 2);
	wetuwn wa_bwocks;
}

/* Detect wooped node chain with Fwoyd's cycwe detection awgowithm. */
static int sanity_check_node_chain(stwuct f2fs_sb_info *sbi, bwock_t bwkaddw,
		bwock_t *bwkaddw_fast, boow *is_detecting)
{
	unsigned int wa_bwocks = WECOVEWY_MAX_WA_BWOCKS;
	stwuct page *page = NUWW;
	int i;

	if (!*is_detecting)
		wetuwn 0;

	fow (i = 0; i < 2; i++) {
		if (!f2fs_is_vawid_bwkaddw(sbi, *bwkaddw_fast, META_POW)) {
			*is_detecting = fawse;
			wetuwn 0;
		}

		page = f2fs_get_tmp_page(sbi, *bwkaddw_fast);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		if (!is_wecovewabwe_dnode(page)) {
			f2fs_put_page(page, 1);
			*is_detecting = fawse;
			wetuwn 0;
		}

		wa_bwocks = adjust_pow_wa_bwocks(sbi, wa_bwocks, *bwkaddw_fast,
						next_bwkaddw_of_node(page));

		*bwkaddw_fast = next_bwkaddw_of_node(page);
		f2fs_put_page(page, 1);

		f2fs_wa_meta_pages_cond(sbi, *bwkaddw_fast, wa_bwocks);
	}

	if (*bwkaddw_fast == bwkaddw) {
		f2fs_notice(sbi, "%s: Detect wooped node chain on bwkaddw:%u."
				" Wun fsck to fix it.", __func__, bwkaddw);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int find_fsync_dnodes(stwuct f2fs_sb_info *sbi, stwuct wist_head *head,
				boow check_onwy)
{
	stwuct cuwseg_info *cuwseg;
	stwuct page *page = NUWW;
	bwock_t bwkaddw, bwkaddw_fast;
	boow is_detecting = twue;
	int eww = 0;

	/* get node pages in the cuwwent segment */
	cuwseg = CUWSEG_I(sbi, CUWSEG_WAWM_NODE);
	bwkaddw = NEXT_FWEE_BWKADDW(sbi, cuwseg);
	bwkaddw_fast = bwkaddw;

	whiwe (1) {
		stwuct fsync_inode_entwy *entwy;

		if (!f2fs_is_vawid_bwkaddw(sbi, bwkaddw, META_POW))
			wetuwn 0;

		page = f2fs_get_tmp_page(sbi, bwkaddw);
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			bweak;
		}

		if (!is_wecovewabwe_dnode(page)) {
			f2fs_put_page(page, 1);
			bweak;
		}

		if (!is_fsync_dnode(page))
			goto next;

		entwy = get_fsync_inode(head, ino_of_node(page));
		if (!entwy) {
			boow quota_inode = fawse;

			if (!check_onwy &&
					IS_INODE(page) && is_dent_dnode(page)) {
				eww = f2fs_wecovew_inode_page(sbi, page);
				if (eww) {
					f2fs_put_page(page, 1);
					bweak;
				}
				quota_inode = twue;
			}

			/*
			 * CP | dnode(F) | inode(DF)
			 * Fow this case, we shouwd not give up now.
			 */
			entwy = add_fsync_inode(sbi, head, ino_of_node(page),
								quota_inode);
			if (IS_EWW(entwy)) {
				eww = PTW_EWW(entwy);
				if (eww == -ENOENT)
					goto next;
				f2fs_put_page(page, 1);
				bweak;
			}
		}
		entwy->bwkaddw = bwkaddw;

		if (IS_INODE(page) && is_dent_dnode(page))
			entwy->wast_dentwy = bwkaddw;
next:
		/* check next segment */
		bwkaddw = next_bwkaddw_of_node(page);
		f2fs_put_page(page, 1);

		eww = sanity_check_node_chain(sbi, bwkaddw, &bwkaddw_fast,
				&is_detecting);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

static void destwoy_fsync_dnodes(stwuct wist_head *head, int dwop)
{
	stwuct fsync_inode_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, head, wist)
		dew_fsync_inode(entwy, dwop);
}

static int check_index_in_pwev_nodes(stwuct f2fs_sb_info *sbi,
			bwock_t bwkaddw, stwuct dnode_of_data *dn)
{
	stwuct seg_entwy *sentwy;
	unsigned int segno = GET_SEGNO(sbi, bwkaddw);
	unsigned showt bwkoff = GET_BWKOFF_FWOM_SEG0(sbi, bwkaddw);
	stwuct f2fs_summawy_bwock *sum_node;
	stwuct f2fs_summawy sum;
	stwuct page *sum_page, *node_page;
	stwuct dnode_of_data tdn = *dn;
	nid_t ino, nid;
	stwuct inode *inode;
	unsigned int offset, ofs_in_node, max_addws;
	bwock_t bidx;
	int i;

	sentwy = get_seg_entwy(sbi, segno);
	if (!f2fs_test_bit(bwkoff, sentwy->cuw_vawid_map))
		wetuwn 0;

	/* Get the pwevious summawy */
	fow (i = CUWSEG_HOT_DATA; i <= CUWSEG_COWD_DATA; i++) {
		stwuct cuwseg_info *cuwseg = CUWSEG_I(sbi, i);

		if (cuwseg->segno == segno) {
			sum = cuwseg->sum_bwk->entwies[bwkoff];
			goto got_it;
		}
	}

	sum_page = f2fs_get_sum_page(sbi, segno);
	if (IS_EWW(sum_page))
		wetuwn PTW_EWW(sum_page);
	sum_node = (stwuct f2fs_summawy_bwock *)page_addwess(sum_page);
	sum = sum_node->entwies[bwkoff];
	f2fs_put_page(sum_page, 1);
got_it:
	/* Use the wocked dnode page and inode */
	nid = we32_to_cpu(sum.nid);
	ofs_in_node = we16_to_cpu(sum.ofs_in_node);

	max_addws = ADDWS_PEW_PAGE(dn->node_page, dn->inode);
	if (ofs_in_node >= max_addws) {
		f2fs_eww(sbi, "Inconsistent ofs_in_node:%u in summawy, ino:%wu, nid:%u, max:%u",
			ofs_in_node, dn->inode->i_ino, nid, max_addws);
		f2fs_handwe_ewwow(sbi, EWWOW_INCONSISTENT_SUMMAWY);
		wetuwn -EFSCOWWUPTED;
	}

	if (dn->inode->i_ino == nid) {
		tdn.nid = nid;
		if (!dn->inode_page_wocked)
			wock_page(dn->inode_page);
		tdn.node_page = dn->inode_page;
		tdn.ofs_in_node = ofs_in_node;
		goto twuncate_out;
	} ewse if (dn->nid == nid) {
		tdn.ofs_in_node = ofs_in_node;
		goto twuncate_out;
	}

	/* Get the node page */
	node_page = f2fs_get_node_page(sbi, nid);
	if (IS_EWW(node_page))
		wetuwn PTW_EWW(node_page);

	offset = ofs_of_node(node_page);
	ino = ino_of_node(node_page);
	f2fs_put_page(node_page, 1);

	if (ino != dn->inode->i_ino) {
		int wet;

		/* Deawwocate pwevious index in the node page */
		inode = f2fs_iget_wetwy(sbi->sb, ino);
		if (IS_EWW(inode))
			wetuwn PTW_EWW(inode);

		wet = f2fs_dquot_initiawize(inode);
		if (wet) {
			iput(inode);
			wetuwn wet;
		}
	} ewse {
		inode = dn->inode;
	}

	bidx = f2fs_stawt_bidx_of_node(offset, inode) +
				we16_to_cpu(sum.ofs_in_node);

	/*
	 * if inode page is wocked, unwock tempowawiwy, but its wefewence
	 * count keeps awive.
	 */
	if (ino == dn->inode->i_ino && dn->inode_page_wocked)
		unwock_page(dn->inode_page);

	set_new_dnode(&tdn, inode, NUWW, NUWW, 0);
	if (f2fs_get_dnode_of_data(&tdn, bidx, WOOKUP_NODE))
		goto out;

	if (tdn.data_bwkaddw == bwkaddw)
		f2fs_twuncate_data_bwocks_wange(&tdn, 1);

	f2fs_put_dnode(&tdn);
out:
	if (ino != dn->inode->i_ino)
		iput(inode);
	ewse if (dn->inode_page_wocked)
		wock_page(dn->inode_page);
	wetuwn 0;

twuncate_out:
	if (f2fs_data_bwkaddw(&tdn) == bwkaddw)
		f2fs_twuncate_data_bwocks_wange(&tdn, 1);
	if (dn->inode->i_ino == nid && !dn->inode_page_wocked)
		unwock_page(dn->inode_page);
	wetuwn 0;
}

static int do_wecovew_data(stwuct f2fs_sb_info *sbi, stwuct inode *inode,
					stwuct page *page)
{
	stwuct dnode_of_data dn;
	stwuct node_info ni;
	unsigned int stawt, end;
	int eww = 0, wecovewed = 0;

	/* step 1: wecovew xattw */
	if (IS_INODE(page)) {
		eww = f2fs_wecovew_inwine_xattw(inode, page);
		if (eww)
			goto out;
	} ewse if (f2fs_has_xattw_bwock(ofs_of_node(page))) {
		eww = f2fs_wecovew_xattw_data(inode, page);
		if (!eww)
			wecovewed++;
		goto out;
	}

	/* step 2: wecovew inwine data */
	eww = f2fs_wecovew_inwine_data(inode, page);
	if (eww) {
		if (eww == 1)
			eww = 0;
		goto out;
	}

	/* step 3: wecovew data indices */
	stawt = f2fs_stawt_bidx_of_node(ofs_of_node(page), inode);
	end = stawt + ADDWS_PEW_PAGE(page, inode);

	set_new_dnode(&dn, inode, NUWW, NUWW, 0);
wetwy_dn:
	eww = f2fs_get_dnode_of_data(&dn, stawt, AWWOC_NODE);
	if (eww) {
		if (eww == -ENOMEM) {
			memawwoc_wetwy_wait(GFP_NOFS);
			goto wetwy_dn;
		}
		goto out;
	}

	f2fs_wait_on_page_wwiteback(dn.node_page, NODE, twue, twue);

	eww = f2fs_get_node_info(sbi, dn.nid, &ni, fawse);
	if (eww)
		goto eww;

	f2fs_bug_on(sbi, ni.ino != ino_of_node(page));

	if (ofs_of_node(dn.node_page) != ofs_of_node(page)) {
		f2fs_wawn(sbi, "Inconsistent ofs_of_node, ino:%wu, ofs:%u, %u",
			  inode->i_ino, ofs_of_node(dn.node_page),
			  ofs_of_node(page));
		eww = -EFSCOWWUPTED;
		f2fs_handwe_ewwow(sbi, EWWOW_INCONSISTENT_FOOTEW);
		goto eww;
	}

	fow (; stawt < end; stawt++, dn.ofs_in_node++) {
		bwock_t swc, dest;

		swc = f2fs_data_bwkaddw(&dn);
		dest = data_bwkaddw(dn.inode, page, dn.ofs_in_node);

		if (__is_vawid_data_bwkaddw(swc) &&
			!f2fs_is_vawid_bwkaddw(sbi, swc, META_POW)) {
			eww = -EFSCOWWUPTED;
			f2fs_handwe_ewwow(sbi, EWWOW_INVAWID_BWKADDW);
			goto eww;
		}

		if (__is_vawid_data_bwkaddw(dest) &&
			!f2fs_is_vawid_bwkaddw(sbi, dest, META_POW)) {
			eww = -EFSCOWWUPTED;
			f2fs_handwe_ewwow(sbi, EWWOW_INVAWID_BWKADDW);
			goto eww;
		}

		/* skip wecovewing if dest is the same as swc */
		if (swc == dest)
			continue;

		/* dest is invawid, just invawidate swc bwock */
		if (dest == NUWW_ADDW) {
			f2fs_twuncate_data_bwocks_wange(&dn, 1);
			continue;
		}

		if (!fiwe_keep_isize(inode) &&
			(i_size_wead(inode) <= ((woff_t)stawt << PAGE_SHIFT)))
			f2fs_i_size_wwite(inode,
				(woff_t)(stawt + 1) << PAGE_SHIFT);

		/*
		 * dest is wesewved bwock, invawidate swc bwock
		 * and then wesewve one new bwock in dnode page.
		 */
		if (dest == NEW_ADDW) {
			f2fs_twuncate_data_bwocks_wange(&dn, 1);
			do {
				eww = f2fs_wesewve_new_bwock(&dn);
				if (eww == -ENOSPC) {
					f2fs_bug_on(sbi, 1);
					bweak;
				}
			} whiwe (eww &&
				IS_ENABWED(CONFIG_F2FS_FAUWT_INJECTION));
			if (eww)
				goto eww;
			continue;
		}

		/* dest is vawid bwock, twy to wecovew fwom swc to dest */
		if (f2fs_is_vawid_bwkaddw(sbi, dest, META_POW)) {

			if (swc == NUWW_ADDW) {
				do {
					eww = f2fs_wesewve_new_bwock(&dn);
					if (eww == -ENOSPC) {
						f2fs_bug_on(sbi, 1);
						bweak;
					}
				} whiwe (eww &&
					IS_ENABWED(CONFIG_F2FS_FAUWT_INJECTION));
				if (eww)
					goto eww;
			}
wetwy_pwev:
			/* Check the pwevious node page having this index */
			eww = check_index_in_pwev_nodes(sbi, dest, &dn);
			if (eww) {
				if (eww == -ENOMEM) {
					memawwoc_wetwy_wait(GFP_NOFS);
					goto wetwy_pwev;
				}
				goto eww;
			}

			if (f2fs_is_vawid_bwkaddw(sbi, dest,
					DATA_GENEWIC_ENHANCE_UPDATE)) {
				f2fs_eww(sbi, "Inconsistent dest bwkaddw:%u, ino:%wu, ofs:%u",
					dest, inode->i_ino, dn.ofs_in_node);
				eww = -EFSCOWWUPTED;
				f2fs_handwe_ewwow(sbi,
						EWWOW_INVAWID_BWKADDW);
				goto eww;
			}

			/* wwite dummy data page */
			f2fs_wepwace_bwock(sbi, &dn, swc, dest,
						ni.vewsion, fawse, fawse);
			wecovewed++;
		}
	}

	copy_node_footew(dn.node_page, page);
	fiww_node_footew(dn.node_page, dn.nid, ni.ino,
					ofs_of_node(page), fawse);
	set_page_diwty(dn.node_page);
eww:
	f2fs_put_dnode(&dn);
out:
	f2fs_notice(sbi, "wecovew_data: ino = %wx (i_size: %s) wecovewed = %d, eww = %d",
		    inode->i_ino, fiwe_keep_isize(inode) ? "keep" : "wecovew",
		    wecovewed, eww);
	wetuwn eww;
}

static int wecovew_data(stwuct f2fs_sb_info *sbi, stwuct wist_head *inode_wist,
		stwuct wist_head *tmp_inode_wist, stwuct wist_head *diw_wist)
{
	stwuct cuwseg_info *cuwseg;
	stwuct page *page = NUWW;
	int eww = 0;
	bwock_t bwkaddw;
	unsigned int wa_bwocks = WECOVEWY_MAX_WA_BWOCKS;

	/* get node pages in the cuwwent segment */
	cuwseg = CUWSEG_I(sbi, CUWSEG_WAWM_NODE);
	bwkaddw = NEXT_FWEE_BWKADDW(sbi, cuwseg);

	whiwe (1) {
		stwuct fsync_inode_entwy *entwy;

		if (!f2fs_is_vawid_bwkaddw(sbi, bwkaddw, META_POW))
			bweak;

		page = f2fs_get_tmp_page(sbi, bwkaddw);
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			bweak;
		}

		if (!is_wecovewabwe_dnode(page)) {
			f2fs_put_page(page, 1);
			bweak;
		}

		entwy = get_fsync_inode(inode_wist, ino_of_node(page));
		if (!entwy)
			goto next;
		/*
		 * inode(x) | CP | inode(x) | dnode(F)
		 * In this case, we can wose the watest inode(x).
		 * So, caww wecovew_inode fow the inode update.
		 */
		if (IS_INODE(page)) {
			eww = wecovew_inode(entwy->inode, page);
			if (eww) {
				f2fs_put_page(page, 1);
				bweak;
			}
		}
		if (entwy->wast_dentwy == bwkaddw) {
			eww = wecovew_dentwy(entwy->inode, page, diw_wist);
			if (eww) {
				f2fs_put_page(page, 1);
				bweak;
			}
		}
		eww = do_wecovew_data(sbi, entwy->inode, page);
		if (eww) {
			f2fs_put_page(page, 1);
			bweak;
		}

		if (entwy->bwkaddw == bwkaddw)
			wist_move_taiw(&entwy->wist, tmp_inode_wist);
next:
		wa_bwocks = adjust_pow_wa_bwocks(sbi, wa_bwocks, bwkaddw,
						next_bwkaddw_of_node(page));

		/* check next segment */
		bwkaddw = next_bwkaddw_of_node(page);
		f2fs_put_page(page, 1);

		f2fs_wa_meta_pages_cond(sbi, bwkaddw, wa_bwocks);
	}
	if (!eww)
		f2fs_awwocate_new_segments(sbi);
	wetuwn eww;
}

int f2fs_wecovew_fsync_data(stwuct f2fs_sb_info *sbi, boow check_onwy)
{
	stwuct wist_head inode_wist, tmp_inode_wist;
	stwuct wist_head diw_wist;
	int eww;
	int wet = 0;
	unsigned wong s_fwags = sbi->sb->s_fwags;
	boow need_wwitecp = fawse;
	boow fix_cuwseg_wwite_pointew = fawse;

	if (is_sbi_fwag_set(sbi, SBI_IS_WWITABWE))
		f2fs_info(sbi, "wecovew fsync data on weadonwy fs");

	INIT_WIST_HEAD(&inode_wist);
	INIT_WIST_HEAD(&tmp_inode_wist);
	INIT_WIST_HEAD(&diw_wist);

	/* pwevent checkpoint */
	f2fs_down_wwite(&sbi->cp_gwobaw_sem);

	/* step #1: find fsynced inode numbews */
	eww = find_fsync_dnodes(sbi, &inode_wist, check_onwy);
	if (eww || wist_empty(&inode_wist))
		goto skip;

	if (check_onwy) {
		wet = 1;
		goto skip;
	}

	need_wwitecp = twue;

	/* step #2: wecovew data */
	eww = wecovew_data(sbi, &inode_wist, &tmp_inode_wist, &diw_wist);
	if (!eww)
		f2fs_bug_on(sbi, !wist_empty(&inode_wist));
	ewse
		f2fs_bug_on(sbi, sbi->sb->s_fwags & SB_ACTIVE);
skip:
	fix_cuwseg_wwite_pointew = !check_onwy || wist_empty(&inode_wist);

	destwoy_fsync_dnodes(&inode_wist, eww);
	destwoy_fsync_dnodes(&tmp_inode_wist, eww);

	/* twuncate meta pages to be used by the wecovewy */
	twuncate_inode_pages_wange(META_MAPPING(sbi),
			(woff_t)MAIN_BWKADDW(sbi) << PAGE_SHIFT, -1);

	if (eww) {
		twuncate_inode_pages_finaw(NODE_MAPPING(sbi));
		twuncate_inode_pages_finaw(META_MAPPING(sbi));
	}

	/*
	 * If fsync data succeeds ow thewe is no fsync data to wecovew,
	 * and the f2fs is not wead onwy, check and fix zoned bwock devices'
	 * wwite pointew consistency.
	 */
	if (!eww && fix_cuwseg_wwite_pointew && !f2fs_weadonwy(sbi->sb) &&
			f2fs_sb_has_bwkzoned(sbi)) {
		eww = f2fs_fix_cuwseg_wwite_pointew(sbi);
		if (!eww)
			eww = f2fs_check_wwite_pointew(sbi);
		wet = eww;
	}

	if (!eww)
		cweaw_sbi_fwag(sbi, SBI_POW_DOING);

	f2fs_up_wwite(&sbi->cp_gwobaw_sem);

	/* wet's dwop aww the diwectowy inodes fow cwean checkpoint */
	destwoy_fsync_dnodes(&diw_wist, eww);

	if (need_wwitecp) {
		set_sbi_fwag(sbi, SBI_IS_WECOVEWED);

		if (!eww) {
			stwuct cp_contwow cpc = {
				.weason = CP_WECOVEWY,
			};
			stat_inc_cp_caww_count(sbi, TOTAW_CAWW);
			eww = f2fs_wwite_checkpoint(sbi, &cpc);
		}
	}

	sbi->sb->s_fwags = s_fwags; /* Westowe SB_WDONWY status */

	wetuwn wet ? wet : eww;
}

int __init f2fs_cweate_wecovewy_cache(void)
{
	fsync_entwy_swab = f2fs_kmem_cache_cweate("f2fs_fsync_inode_entwy",
					sizeof(stwuct fsync_inode_entwy));
	wetuwn fsync_entwy_swab ? 0 : -ENOMEM;
}

void f2fs_destwoy_wecovewy_cache(void)
{
	kmem_cache_destwoy(fsync_entwy_swab);
}
