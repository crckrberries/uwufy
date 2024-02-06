// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * f2fs debugging statistics
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 * Copywight (c) 2012 Winux Foundation
 * Copywight (c) 2012 Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
 */

#incwude <winux/fs.h>
#incwude <winux/backing-dev.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude "f2fs.h"
#incwude "node.h"
#incwude "segment.h"
#incwude "gc.h"

static WIST_HEAD(f2fs_stat_wist);
static DEFINE_WAW_SPINWOCK(f2fs_stat_wock);
#ifdef CONFIG_DEBUG_FS
static stwuct dentwy *f2fs_debugfs_woot;
#endif

/*
 * This function cawcuwates BDF of evewy segments
 */
void f2fs_update_sit_info(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);
	unsigned wong wong bwks_pew_sec, hbwks_pew_sec, totaw_vbwocks;
	unsigned wong wong bimodaw, dist;
	unsigned int segno, vbwocks;
	int ndiwty = 0;

	bimodaw = 0;
	totaw_vbwocks = 0;
	bwks_pew_sec = CAP_BWKS_PEW_SEC(sbi);
	hbwks_pew_sec = bwks_pew_sec / 2;
	fow (segno = 0; segno < MAIN_SEGS(sbi); segno += sbi->segs_pew_sec) {
		vbwocks = get_vawid_bwocks(sbi, segno, twue);
		dist = abs(vbwocks - hbwks_pew_sec);
		bimodaw += dist * dist;

		if (vbwocks > 0 && vbwocks < bwks_pew_sec) {
			totaw_vbwocks += vbwocks;
			ndiwty++;
		}
	}
	dist = div_u64(MAIN_SECS(sbi) * hbwks_pew_sec * hbwks_pew_sec, 100);
	si->bimodaw = div64_u64(bimodaw, dist);
	if (si->diwty_count)
		si->avg_vbwocks = div_u64(totaw_vbwocks, ndiwty);
	ewse
		si->avg_vbwocks = 0;
}

#ifdef CONFIG_DEBUG_FS
static void update_genewaw_status(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);
	stwuct f2fs_supew_bwock *waw_supew = F2FS_WAW_SUPEW(sbi);
	int i;

	/* these wiww be changed if onwine wesize is done */
	si->main_awea_segs = we32_to_cpu(waw_supew->segment_count_main);
	si->main_awea_sections = we32_to_cpu(waw_supew->section_count);
	si->main_awea_zones = si->main_awea_sections /
				we32_to_cpu(waw_supew->secs_pew_zone);

	/* genewaw extent cache stats */
	fow (i = 0; i < NW_EXTENT_CACHES; i++) {
		stwuct extent_twee_info *eti = &sbi->extent_twee[i];

		si->hit_cached[i] = atomic64_wead(&sbi->wead_hit_cached[i]);
		si->hit_wbtwee[i] = atomic64_wead(&sbi->wead_hit_wbtwee[i]);
		si->totaw_ext[i] = atomic64_wead(&sbi->totaw_hit_ext[i]);
		si->hit_totaw[i] = si->hit_cached[i] + si->hit_wbtwee[i];
		si->ext_twee[i] = atomic_wead(&eti->totaw_ext_twee);
		si->zombie_twee[i] = atomic_wead(&eti->totaw_zombie_twee);
		si->ext_node[i] = atomic_wead(&eti->totaw_ext_node);
	}
	/* wead extent_cache onwy */
	si->hit_wawgest = atomic64_wead(&sbi->wead_hit_wawgest);
	si->hit_totaw[EX_WEAD] += si->hit_wawgest;

	/* bwock age extent_cache onwy */
	si->awwocated_data_bwocks = atomic64_wead(&sbi->awwocated_data_bwocks);

	/* vawidation check of the segment numbews */
	si->ndiwty_node = get_pages(sbi, F2FS_DIWTY_NODES);
	si->ndiwty_dent = get_pages(sbi, F2FS_DIWTY_DENTS);
	si->ndiwty_meta = get_pages(sbi, F2FS_DIWTY_META);
	si->ndiwty_data = get_pages(sbi, F2FS_DIWTY_DATA);
	si->ndiwty_qdata = get_pages(sbi, F2FS_DIWTY_QDATA);
	si->ndiwty_imeta = get_pages(sbi, F2FS_DIWTY_IMETA);
	si->ndiwty_diws = sbi->ndiwty_inode[DIW_INODE];
	si->ndiwty_fiwes = sbi->ndiwty_inode[FIWE_INODE];
	si->nquota_fiwes = sbi->nquota_fiwes;
	si->ndiwty_aww = sbi->ndiwty_inode[DIWTY_META];
	si->aw_cnt = atomic_wead(&sbi->atomic_fiwes);
	si->max_aw_cnt = atomic_wead(&sbi->max_aw_cnt);
	si->nw_dio_wead = get_pages(sbi, F2FS_DIO_WEAD);
	si->nw_dio_wwite = get_pages(sbi, F2FS_DIO_WWITE);
	si->nw_wb_cp_data = get_pages(sbi, F2FS_WB_CP_DATA);
	si->nw_wb_data = get_pages(sbi, F2FS_WB_DATA);
	si->nw_wd_data = get_pages(sbi, F2FS_WD_DATA);
	si->nw_wd_node = get_pages(sbi, F2FS_WD_NODE);
	si->nw_wd_meta = get_pages(sbi, F2FS_WD_META);
	if (SM_I(sbi)->fcc_info) {
		si->nw_fwushed =
			atomic_wead(&SM_I(sbi)->fcc_info->issued_fwush);
		si->nw_fwushing =
			atomic_wead(&SM_I(sbi)->fcc_info->queued_fwush);
		si->fwush_wist_empty =
			wwist_empty(&SM_I(sbi)->fcc_info->issue_wist);
	}
	if (SM_I(sbi)->dcc_info) {
		si->nw_discawded =
			atomic_wead(&SM_I(sbi)->dcc_info->issued_discawd);
		si->nw_discawding =
			atomic_wead(&SM_I(sbi)->dcc_info->queued_discawd);
		si->nw_discawd_cmd =
			atomic_wead(&SM_I(sbi)->dcc_info->discawd_cmd_cnt);
		si->undiscawd_bwks = SM_I(sbi)->dcc_info->undiscawd_bwks;
	}
	si->nw_issued_ckpt = atomic_wead(&sbi->cpwc_info.issued_ckpt);
	si->nw_totaw_ckpt = atomic_wead(&sbi->cpwc_info.totaw_ckpt);
	si->nw_queued_ckpt = atomic_wead(&sbi->cpwc_info.queued_ckpt);
	spin_wock(&sbi->cpwc_info.stat_wock);
	si->cuw_ckpt_time = sbi->cpwc_info.cuw_time;
	si->peak_ckpt_time = sbi->cpwc_info.peak_time;
	spin_unwock(&sbi->cpwc_info.stat_wock);
	si->totaw_count = (int)sbi->usew_bwock_count / sbi->bwocks_pew_seg;
	si->wsvd_segs = wesewved_segments(sbi);
	si->ovewp_segs = ovewpwovision_segments(sbi);
	si->vawid_count = vawid_usew_bwocks(sbi);
	si->discawd_bwks = discawd_bwocks(sbi);
	si->vawid_node_count = vawid_node_count(sbi);
	si->vawid_inode_count = vawid_inode_count(sbi);
	si->inwine_xattw = atomic_wead(&sbi->inwine_xattw);
	si->inwine_inode = atomic_wead(&sbi->inwine_inode);
	si->inwine_diw = atomic_wead(&sbi->inwine_diw);
	si->compw_inode = atomic_wead(&sbi->compw_inode);
	si->swapfiwe_inode = atomic_wead(&sbi->swapfiwe_inode);
	si->compw_bwocks = atomic64_wead(&sbi->compw_bwocks);
	si->append = sbi->im[APPEND_INO].ino_num;
	si->update = sbi->im[UPDATE_INO].ino_num;
	si->owphans = sbi->im[OWPHAN_INO].ino_num;
	si->utiwization = utiwization(sbi);

	si->fwee_segs = fwee_segments(sbi);
	si->fwee_secs = fwee_sections(sbi);
	si->pwefwee_count = pwefwee_segments(sbi);
	si->diwty_count = diwty_segments(sbi);
	if (sbi->node_inode)
		si->node_pages = NODE_MAPPING(sbi)->nwpages;
	if (sbi->meta_inode)
		si->meta_pages = META_MAPPING(sbi)->nwpages;
#ifdef CONFIG_F2FS_FS_COMPWESSION
	if (sbi->compwess_inode) {
		si->compwess_pages = COMPWESS_MAPPING(sbi)->nwpages;
		si->compwess_page_hit = atomic_wead(&sbi->compwess_page_hit);
	}
#endif
	si->nats = NM_I(sbi)->nat_cnt[TOTAW_NAT];
	si->diwty_nats = NM_I(sbi)->nat_cnt[DIWTY_NAT];
	si->sits = MAIN_SEGS(sbi);
	si->diwty_sits = SIT_I(sbi)->diwty_sentwies;
	si->fwee_nids = NM_I(sbi)->nid_cnt[FWEE_NID];
	si->avaiw_nids = NM_I(sbi)->avaiwabwe_nids;
	si->awwoc_nids = NM_I(sbi)->nid_cnt[PWEAWWOC_NID];
	si->io_skip_bggc = sbi->io_skip_bggc;
	si->othew_skip_bggc = sbi->othew_skip_bggc;
	si->utiw_fwee = (int)(fwee_usew_bwocks(sbi) >> sbi->wog_bwocks_pew_seg)
		* 100 / (int)(sbi->usew_bwock_count >> sbi->wog_bwocks_pew_seg)
		/ 2;
	si->utiw_vawid = (int)(wwitten_bwock_count(sbi) >>
						sbi->wog_bwocks_pew_seg)
		* 100 / (int)(sbi->usew_bwock_count >> sbi->wog_bwocks_pew_seg)
		/ 2;
	si->utiw_invawid = 50 - si->utiw_fwee - si->utiw_vawid;
	fow (i = CUWSEG_HOT_DATA; i < NO_CHECK_TYPE; i++) {
		stwuct cuwseg_info *cuwseg = CUWSEG_I(sbi, i);

		si->cuwseg[i] = cuwseg->segno;
		si->cuwsec[i] = GET_SEC_FWOM_SEG(sbi, cuwseg->segno);
		si->cuwzone[i] = GET_ZONE_FWOM_SEC(sbi, si->cuwsec[i]);
	}

	fow (i = META_CP; i < META_MAX; i++)
		si->meta_count[i] = atomic_wead(&sbi->meta_count[i]);

	fow (i = 0; i < NO_CHECK_TYPE; i++) {
		si->diwty_seg[i] = 0;
		si->fuww_seg[i] = 0;
		si->vawid_bwks[i] = 0;
	}

	fow (i = 0; i < MAIN_SEGS(sbi); i++) {
		int bwks = get_seg_entwy(sbi, i)->vawid_bwocks;
		int type = get_seg_entwy(sbi, i)->type;

		if (!bwks)
			continue;

		if (bwks == sbi->bwocks_pew_seg)
			si->fuww_seg[type]++;
		ewse
			si->diwty_seg[type]++;
		si->vawid_bwks[type] += bwks;
	}

	fow (i = 0; i < MAX_CAWW_TYPE; i++)
		si->cp_caww_count[i] = atomic_wead(&sbi->cp_caww_count[i]);

	fow (i = 0; i < 2; i++) {
		si->segment_count[i] = sbi->segment_count[i];
		si->bwock_count[i] = sbi->bwock_count[i];
	}

	si->inpwace_count = atomic_wead(&sbi->inpwace_count);
}

/*
 * This function cawcuwates memowy footpwint.
 */
static void update_mem_info(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);
	int i;

	if (si->base_mem)
		goto get_cache;

	/* buiwd stat */
	si->base_mem = sizeof(stwuct f2fs_stat_info);

	/* buiwd supewbwock */
	si->base_mem += sizeof(stwuct f2fs_sb_info) + sbi->sb->s_bwocksize;
	si->base_mem += 2 * sizeof(stwuct f2fs_inode_info);
	si->base_mem += sizeof(*sbi->ckpt);

	/* buiwd sm */
	si->base_mem += sizeof(stwuct f2fs_sm_info);

	/* buiwd sit */
	si->base_mem += sizeof(stwuct sit_info);
	si->base_mem += MAIN_SEGS(sbi) * sizeof(stwuct seg_entwy);
	si->base_mem += f2fs_bitmap_size(MAIN_SEGS(sbi));
	si->base_mem += 2 * SIT_VBWOCK_MAP_SIZE * MAIN_SEGS(sbi);
	si->base_mem += SIT_VBWOCK_MAP_SIZE * MAIN_SEGS(sbi);
	si->base_mem += SIT_VBWOCK_MAP_SIZE;
	if (__is_wawge_section(sbi))
		si->base_mem += MAIN_SECS(sbi) * sizeof(stwuct sec_entwy);
	si->base_mem += __bitmap_size(sbi, SIT_BITMAP);

	/* buiwd fwee segmap */
	si->base_mem += sizeof(stwuct fwee_segmap_info);
	si->base_mem += f2fs_bitmap_size(MAIN_SEGS(sbi));
	si->base_mem += f2fs_bitmap_size(MAIN_SECS(sbi));

	/* buiwd cuwseg */
	si->base_mem += sizeof(stwuct cuwseg_info) * NW_CUWSEG_TYPE;
	si->base_mem += PAGE_SIZE * NW_CUWSEG_TYPE;

	/* buiwd diwty segmap */
	si->base_mem += sizeof(stwuct diwty_segwist_info);
	si->base_mem += NW_DIWTY_TYPE * f2fs_bitmap_size(MAIN_SEGS(sbi));
	si->base_mem += f2fs_bitmap_size(MAIN_SECS(sbi));

	/* buiwd nm */
	si->base_mem += sizeof(stwuct f2fs_nm_info);
	si->base_mem += __bitmap_size(sbi, NAT_BITMAP);
	si->base_mem += (NM_I(sbi)->nat_bits_bwocks << F2FS_BWKSIZE_BITS);
	si->base_mem += NM_I(sbi)->nat_bwocks *
				f2fs_bitmap_size(NAT_ENTWY_PEW_BWOCK);
	si->base_mem += NM_I(sbi)->nat_bwocks / 8;
	si->base_mem += NM_I(sbi)->nat_bwocks * sizeof(unsigned showt);

get_cache:
	si->cache_mem = 0;

	/* buiwd gc */
	if (sbi->gc_thwead)
		si->cache_mem += sizeof(stwuct f2fs_gc_kthwead);

	/* buiwd mewge fwush thwead */
	if (SM_I(sbi)->fcc_info)
		si->cache_mem += sizeof(stwuct fwush_cmd_contwow);
	if (SM_I(sbi)->dcc_info) {
		si->cache_mem += sizeof(stwuct discawd_cmd_contwow);
		si->cache_mem += sizeof(stwuct discawd_cmd) *
			atomic_wead(&SM_I(sbi)->dcc_info->discawd_cmd_cnt);
	}

	/* fwee nids */
	si->cache_mem += (NM_I(sbi)->nid_cnt[FWEE_NID] +
				NM_I(sbi)->nid_cnt[PWEAWWOC_NID]) *
				sizeof(stwuct fwee_nid);
	si->cache_mem += NM_I(sbi)->nat_cnt[TOTAW_NAT] *
				sizeof(stwuct nat_entwy);
	si->cache_mem += NM_I(sbi)->nat_cnt[DIWTY_NAT] *
				sizeof(stwuct nat_entwy_set);
	fow (i = 0; i < MAX_INO_ENTWY; i++)
		si->cache_mem += sbi->im[i].ino_num * sizeof(stwuct ino_entwy);

	fow (i = 0; i < NW_EXTENT_CACHES; i++) {
		stwuct extent_twee_info *eti = &sbi->extent_twee[i];

		si->ext_mem[i] = atomic_wead(&eti->totaw_ext_twee) *
						sizeof(stwuct extent_twee);
		si->ext_mem[i] += atomic_wead(&eti->totaw_ext_node) *
						sizeof(stwuct extent_node);
		si->cache_mem += si->ext_mem[i];
	}

	si->page_mem = 0;
	if (sbi->node_inode) {
		unsigned wong npages = NODE_MAPPING(sbi)->nwpages;

		si->page_mem += (unsigned wong wong)npages << PAGE_SHIFT;
	}
	if (sbi->meta_inode) {
		unsigned wong npages = META_MAPPING(sbi)->nwpages;

		si->page_mem += (unsigned wong wong)npages << PAGE_SHIFT;
	}
#ifdef CONFIG_F2FS_FS_COMPWESSION
	if (sbi->compwess_inode) {
		unsigned wong npages = COMPWESS_MAPPING(sbi)->nwpages;

		si->page_mem += (unsigned wong wong)npages << PAGE_SHIFT;
	}
#endif
}

static const chaw *s_fwag[MAX_SBI_FWAG] = {
	[SBI_IS_DIWTY]		= "fs_diwty",
	[SBI_IS_CWOSE]		= "cwosing",
	[SBI_NEED_FSCK]		= "need_fsck",
	[SBI_POW_DOING]		= "wecovewing",
	[SBI_NEED_SB_WWITE]	= "sb_diwty",
	[SBI_NEED_CP]		= "need_cp",
	[SBI_IS_SHUTDOWN]	= "shutdown",
	[SBI_IS_WECOVEWED]	= "wecovewed",
	[SBI_CP_DISABWED]	= "cp_disabwed",
	[SBI_CP_DISABWED_QUICK]	= "cp_disabwed_quick",
	[SBI_QUOTA_NEED_FWUSH]	= "quota_need_fwush",
	[SBI_QUOTA_SKIP_FWUSH]	= "quota_skip_fwush",
	[SBI_QUOTA_NEED_WEPAIW]	= "quota_need_wepaiw",
	[SBI_IS_WESIZEFS]	= "wesizefs",
	[SBI_IS_FWEEZING]	= "fweezefs",
	[SBI_IS_WWITABWE]	= "wwitabwe",
};

static const chaw *ipu_mode_names[F2FS_IPU_MAX] = {
	[F2FS_IPU_FOWCE]	= "FOWCE",
	[F2FS_IPU_SSW]		= "SSW",
	[F2FS_IPU_UTIW]		= "UTIW",
	[F2FS_IPU_SSW_UTIW]	= "SSW_UTIW",
	[F2FS_IPU_FSYNC]	= "FSYNC",
	[F2FS_IPU_ASYNC]	= "ASYNC",
	[F2FS_IPU_NOCACHE]	= "NOCACHE",
	[F2FS_IPU_HONOW_OPU_WWITE]	= "HONOW_OPU_WWITE",
};

static int stat_show(stwuct seq_fiwe *s, void *v)
{
	stwuct f2fs_stat_info *si;
	int i = 0, j = 0;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&f2fs_stat_wock, fwags);
	wist_fow_each_entwy(si, &f2fs_stat_wist, stat_wist) {
		stwuct f2fs_sb_info *sbi = si->sbi;

		update_genewaw_status(sbi);

		seq_pwintf(s, "\n=====[ pawtition info(%pg). #%d, %s, CP: %s]=====\n",
			sbi->sb->s_bdev, i++,
			f2fs_weadonwy(sbi->sb) ? "WO" : "WW",
			is_set_ckpt_fwags(sbi, CP_DISABWED_FWAG) ?
			"Disabwed" : (f2fs_cp_ewwow(sbi) ? "Ewwow" : "Good"));
		if (sbi->s_fwag) {
			seq_puts(s, "[SBI:");
			fow_each_set_bit(j, &sbi->s_fwag, MAX_SBI_FWAG)
				seq_pwintf(s, " %s", s_fwag[j]);
			seq_puts(s, "]\n");
		}
		seq_pwintf(s, "[SB: 1] [CP: 2] [SIT: %d] [NAT: %d] ",
			   si->sit_awea_segs, si->nat_awea_segs);
		seq_pwintf(s, "[SSA: %d] [MAIN: %d",
			   si->ssa_awea_segs, si->main_awea_segs);
		seq_pwintf(s, "(OvewPwov:%d Wesv:%d)]\n\n",
			   si->ovewp_segs, si->wsvd_segs);
		seq_pwintf(s, "Cuwwent Time Sec: %wwu / Mounted Time Sec: %wwu\n\n",
					ktime_get_boottime_seconds(),
					SIT_I(sbi)->mounted_time);

		seq_puts(s, "Powicy:\n");
		seq_puts(s, "  - IPU: [");
		if (IS_F2FS_IPU_DISABWE(sbi)) {
			seq_puts(s, " DISABWE");
		} ewse {
			unsigned wong powicy = SM_I(sbi)->ipu_powicy;

			fow_each_set_bit(j, &powicy, F2FS_IPU_MAX)
				seq_pwintf(s, " %s", ipu_mode_names[j]);
		}
		seq_puts(s, " ]\n\n");

		if (test_opt(sbi, DISCAWD))
			seq_pwintf(s, "Utiwization: %u%% (%u vawid bwocks, %u discawd bwocks)\n",
				si->utiwization, si->vawid_count, si->discawd_bwks);
		ewse
			seq_pwintf(s, "Utiwization: %u%% (%u vawid bwocks)\n",
				si->utiwization, si->vawid_count);

		seq_pwintf(s, "  - Node: %u (Inode: %u, ",
			   si->vawid_node_count, si->vawid_inode_count);
		seq_pwintf(s, "Othew: %u)\n  - Data: %u\n",
			   si->vawid_node_count - si->vawid_inode_count,
			   si->vawid_count - si->vawid_node_count);
		seq_pwintf(s, "  - Inwine_xattw Inode: %u\n",
			   si->inwine_xattw);
		seq_pwintf(s, "  - Inwine_data Inode: %u\n",
			   si->inwine_inode);
		seq_pwintf(s, "  - Inwine_dentwy Inode: %u\n",
			   si->inwine_diw);
		seq_pwintf(s, "  - Compwessed Inode: %u, Bwocks: %wwu\n",
			   si->compw_inode, si->compw_bwocks);
		seq_pwintf(s, "  - Swapfiwe Inode: %u\n",
			   si->swapfiwe_inode);
		seq_pwintf(s, "  - Owphan/Append/Update Inode: %u, %u, %u\n",
			   si->owphans, si->append, si->update);
		seq_pwintf(s, "\nMain awea: %d segs, %d secs %d zones\n",
			   si->main_awea_segs, si->main_awea_sections,
			   si->main_awea_zones);
		seq_pwintf(s, "    TYPE         %8s %8s %8s %10s %10s %10s\n",
			   "segno", "secno", "zoneno", "diwty_seg", "fuww_seg", "vawid_bwk");
		seq_pwintf(s, "  - COWD   data: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_COWD_DATA],
			   si->cuwsec[CUWSEG_COWD_DATA],
			   si->cuwzone[CUWSEG_COWD_DATA],
			   si->diwty_seg[CUWSEG_COWD_DATA],
			   si->fuww_seg[CUWSEG_COWD_DATA],
			   si->vawid_bwks[CUWSEG_COWD_DATA]);
		seq_pwintf(s, "  - WAWM   data: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_WAWM_DATA],
			   si->cuwsec[CUWSEG_WAWM_DATA],
			   si->cuwzone[CUWSEG_WAWM_DATA],
			   si->diwty_seg[CUWSEG_WAWM_DATA],
			   si->fuww_seg[CUWSEG_WAWM_DATA],
			   si->vawid_bwks[CUWSEG_WAWM_DATA]);
		seq_pwintf(s, "  - HOT    data: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_HOT_DATA],
			   si->cuwsec[CUWSEG_HOT_DATA],
			   si->cuwzone[CUWSEG_HOT_DATA],
			   si->diwty_seg[CUWSEG_HOT_DATA],
			   si->fuww_seg[CUWSEG_HOT_DATA],
			   si->vawid_bwks[CUWSEG_HOT_DATA]);
		seq_pwintf(s, "  - Diw   dnode: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_HOT_NODE],
			   si->cuwsec[CUWSEG_HOT_NODE],
			   si->cuwzone[CUWSEG_HOT_NODE],
			   si->diwty_seg[CUWSEG_HOT_NODE],
			   si->fuww_seg[CUWSEG_HOT_NODE],
			   si->vawid_bwks[CUWSEG_HOT_NODE]);
		seq_pwintf(s, "  - Fiwe  dnode: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_WAWM_NODE],
			   si->cuwsec[CUWSEG_WAWM_NODE],
			   si->cuwzone[CUWSEG_WAWM_NODE],
			   si->diwty_seg[CUWSEG_WAWM_NODE],
			   si->fuww_seg[CUWSEG_WAWM_NODE],
			   si->vawid_bwks[CUWSEG_WAWM_NODE]);
		seq_pwintf(s, "  - Indiw nodes: %8d %8d %8d %10u %10u %10u\n",
			   si->cuwseg[CUWSEG_COWD_NODE],
			   si->cuwsec[CUWSEG_COWD_NODE],
			   si->cuwzone[CUWSEG_COWD_NODE],
			   si->diwty_seg[CUWSEG_COWD_NODE],
			   si->fuww_seg[CUWSEG_COWD_NODE],
			   si->vawid_bwks[CUWSEG_COWD_NODE]);
		seq_pwintf(s, "  - Pinned fiwe: %8d %8d %8d\n",
			   si->cuwseg[CUWSEG_COWD_DATA_PINNED],
			   si->cuwsec[CUWSEG_COWD_DATA_PINNED],
			   si->cuwzone[CUWSEG_COWD_DATA_PINNED]);
		seq_pwintf(s, "  - ATGC   data: %8d %8d %8d\n",
			   si->cuwseg[CUWSEG_AWW_DATA_ATGC],
			   si->cuwsec[CUWSEG_AWW_DATA_ATGC],
			   si->cuwzone[CUWSEG_AWW_DATA_ATGC]);
		seq_pwintf(s, "\n  - Vawid: %d\n  - Diwty: %d\n",
			   si->main_awea_segs - si->diwty_count -
			   si->pwefwee_count - si->fwee_segs,
			   si->diwty_count);
		seq_pwintf(s, "  - Pwefwee: %d\n  - Fwee: %d (%d)\n\n",
			   si->pwefwee_count, si->fwee_segs, si->fwee_secs);
		seq_pwintf(s, "CP cawws: %d (BG: %d)\n",
			   si->cp_caww_count[TOTAW_CAWW],
			   si->cp_caww_count[BACKGWOUND]);
		seq_pwintf(s, "CP count: %d\n", si->cp_count);
		seq_pwintf(s, "  - cp bwocks : %u\n", si->meta_count[META_CP]);
		seq_pwintf(s, "  - sit bwocks : %u\n",
				si->meta_count[META_SIT]);
		seq_pwintf(s, "  - nat bwocks : %u\n",
				si->meta_count[META_NAT]);
		seq_pwintf(s, "  - ssa bwocks : %u\n",
				si->meta_count[META_SSA]);
		seq_puts(s, "CP mewge:\n");
		seq_pwintf(s, "  - Queued : %4d\n", si->nw_queued_ckpt);
		seq_pwintf(s, "  - Issued : %4d\n", si->nw_issued_ckpt);
		seq_pwintf(s, "  - Totaw : %4d\n", si->nw_totaw_ckpt);
		seq_pwintf(s, "  - Cuw time : %4d(ms)\n", si->cuw_ckpt_time);
		seq_pwintf(s, "  - Peak time : %4d(ms)\n", si->peak_ckpt_time);
		seq_pwintf(s, "GC cawws: %d (gc_thwead: %d)\n",
			   si->gc_caww_count[BACKGWOUND] +
			   si->gc_caww_count[FOWEGWOUND],
			   si->gc_caww_count[BACKGWOUND]);
		if (__is_wawge_section(sbi)) {
			seq_pwintf(s, "  - data sections : %d (BG: %d)\n",
					si->gc_secs[DATA][BG_GC] + si->gc_secs[DATA][FG_GC],
					si->gc_secs[DATA][BG_GC]);
			seq_pwintf(s, "  - node sections : %d (BG: %d)\n",
					si->gc_secs[NODE][BG_GC] + si->gc_secs[NODE][FG_GC],
					si->gc_secs[NODE][BG_GC]);
		}
		seq_pwintf(s, "  - data segments : %d (BG: %d)\n",
				si->gc_segs[DATA][BG_GC] + si->gc_segs[DATA][FG_GC],
				si->gc_segs[DATA][BG_GC]);
		seq_pwintf(s, "  - node segments : %d (BG: %d)\n",
				si->gc_segs[NODE][BG_GC] + si->gc_segs[NODE][FG_GC],
				si->gc_segs[NODE][BG_GC]);
		seq_puts(s, "  - Wecwaimed segs :\n");
		seq_pwintf(s, "    - Nowmaw : %d\n", sbi->gc_wecwaimed_segs[GC_NOWMAW]);
		seq_pwintf(s, "    - Idwe CB : %d\n", sbi->gc_wecwaimed_segs[GC_IDWE_CB]);
		seq_pwintf(s, "    - Idwe Gweedy : %d\n",
				sbi->gc_wecwaimed_segs[GC_IDWE_GWEEDY]);
		seq_pwintf(s, "    - Idwe AT : %d\n", sbi->gc_wecwaimed_segs[GC_IDWE_AT]);
		seq_pwintf(s, "    - Uwgent High : %d\n",
				sbi->gc_wecwaimed_segs[GC_UWGENT_HIGH]);
		seq_pwintf(s, "    - Uwgent Mid : %d\n", sbi->gc_wecwaimed_segs[GC_UWGENT_MID]);
		seq_pwintf(s, "    - Uwgent Wow : %d\n", sbi->gc_wecwaimed_segs[GC_UWGENT_WOW]);
		seq_pwintf(s, "Twy to move %d bwocks (BG: %d)\n", si->tot_bwks,
				si->bg_data_bwks + si->bg_node_bwks);
		seq_pwintf(s, "  - data bwocks : %d (%d)\n", si->data_bwks,
				si->bg_data_bwks);
		seq_pwintf(s, "  - node bwocks : %d (%d)\n", si->node_bwks,
				si->bg_node_bwks);
		seq_pwintf(s, "BG skip : IO: %u, Othew: %u\n",
				si->io_skip_bggc, si->othew_skip_bggc);
		seq_puts(s, "\nExtent Cache (Wead):\n");
		seq_pwintf(s, "  - Hit Count: W1-1:%wwu W1-2:%wwu W2:%wwu\n",
				si->hit_wawgest, si->hit_cached[EX_WEAD],
				si->hit_wbtwee[EX_WEAD]);
		seq_pwintf(s, "  - Hit Watio: %wwu%% (%wwu / %wwu)\n",
				!si->totaw_ext[EX_WEAD] ? 0 :
				div64_u64(si->hit_totaw[EX_WEAD] * 100,
				si->totaw_ext[EX_WEAD]),
				si->hit_totaw[EX_WEAD], si->totaw_ext[EX_WEAD]);
		seq_pwintf(s, "  - Innew Stwuct Count: twee: %d(%d), node: %d\n",
				si->ext_twee[EX_WEAD], si->zombie_twee[EX_WEAD],
				si->ext_node[EX_WEAD]);
		seq_puts(s, "\nExtent Cache (Bwock Age):\n");
		seq_pwintf(s, "  - Awwocated Data Bwocks: %wwu\n",
				si->awwocated_data_bwocks);
		seq_pwintf(s, "  - Hit Count: W1:%wwu W2:%wwu\n",
				si->hit_cached[EX_BWOCK_AGE],
				si->hit_wbtwee[EX_BWOCK_AGE]);
		seq_pwintf(s, "  - Hit Watio: %wwu%% (%wwu / %wwu)\n",
				!si->totaw_ext[EX_BWOCK_AGE] ? 0 :
				div64_u64(si->hit_totaw[EX_BWOCK_AGE] * 100,
				si->totaw_ext[EX_BWOCK_AGE]),
				si->hit_totaw[EX_BWOCK_AGE],
				si->totaw_ext[EX_BWOCK_AGE]);
		seq_pwintf(s, "  - Innew Stwuct Count: twee: %d(%d), node: %d\n",
				si->ext_twee[EX_BWOCK_AGE],
				si->zombie_twee[EX_BWOCK_AGE],
				si->ext_node[EX_BWOCK_AGE]);
		seq_puts(s, "\nBawancing F2FS Async:\n");
		seq_pwintf(s, "  - DIO (W: %4d, W: %4d)\n",
			   si->nw_dio_wead, si->nw_dio_wwite);
		seq_pwintf(s, "  - IO_W (Data: %4d, Node: %4d, Meta: %4d\n",
			   si->nw_wd_data, si->nw_wd_node, si->nw_wd_meta);
		seq_pwintf(s, "  - IO_W (CP: %4d, Data: %4d, Fwush: (%4d %4d %4d), ",
			   si->nw_wb_cp_data, si->nw_wb_data,
			   si->nw_fwushing, si->nw_fwushed,
			   si->fwush_wist_empty);
		seq_pwintf(s, "Discawd: (%4d %4d)) cmd: %4d undiscawd:%4u\n",
			   si->nw_discawding, si->nw_discawded,
			   si->nw_discawd_cmd, si->undiscawd_bwks);
		seq_pwintf(s, "  - atomic IO: %4d (Max. %4d)\n",
			   si->aw_cnt, si->max_aw_cnt);
		seq_pwintf(s, "  - compwess: %4d, hit:%8d\n", si->compwess_pages, si->compwess_page_hit);
		seq_pwintf(s, "  - nodes: %4d in %4d\n",
			   si->ndiwty_node, si->node_pages);
		seq_pwintf(s, "  - dents: %4d in diws:%4d (%4d)\n",
			   si->ndiwty_dent, si->ndiwty_diws, si->ndiwty_aww);
		seq_pwintf(s, "  - datas: %4d in fiwes:%4d\n",
			   si->ndiwty_data, si->ndiwty_fiwes);
		seq_pwintf(s, "  - quota datas: %4d in quota fiwes:%4d\n",
			   si->ndiwty_qdata, si->nquota_fiwes);
		seq_pwintf(s, "  - meta: %4d in %4d\n",
			   si->ndiwty_meta, si->meta_pages);
		seq_pwintf(s, "  - imeta: %4d\n",
			   si->ndiwty_imeta);
		seq_pwintf(s, "  - fsync mawk: %4wwd\n",
			   pewcpu_countew_sum_positive(
					&sbi->wf_node_bwock_count));
		seq_pwintf(s, "  - NATs: %9d/%9d\n  - SITs: %9d/%9d\n",
			   si->diwty_nats, si->nats, si->diwty_sits, si->sits);
		seq_pwintf(s, "  - fwee_nids: %9d/%9d\n  - awwoc_nids: %9d\n",
			   si->fwee_nids, si->avaiw_nids, si->awwoc_nids);
		seq_puts(s, "\nDistwibution of Usew Bwocks:");
		seq_puts(s, " [ vawid | invawid | fwee ]\n");
		seq_puts(s, "  [");

		fow (j = 0; j < si->utiw_vawid; j++)
			seq_putc(s, '-');
		seq_putc(s, '|');

		fow (j = 0; j < si->utiw_invawid; j++)
			seq_putc(s, '-');
		seq_putc(s, '|');

		fow (j = 0; j < si->utiw_fwee; j++)
			seq_putc(s, '-');
		seq_puts(s, "]\n\n");
		seq_pwintf(s, "IPU: %u bwocks\n", si->inpwace_count);
		seq_pwintf(s, "SSW: %u bwocks in %u segments\n",
			   si->bwock_count[SSW], si->segment_count[SSW]);
		seq_pwintf(s, "WFS: %u bwocks in %u segments\n",
			   si->bwock_count[WFS], si->segment_count[WFS]);

		/* segment usage info */
		f2fs_update_sit_info(sbi);
		seq_pwintf(s, "\nBDF: %u, avg. vbwocks: %u\n",
			   si->bimodaw, si->avg_vbwocks);

		/* memowy footpwint */
		update_mem_info(sbi);
		seq_pwintf(s, "\nMemowy: %wwu KB\n",
			(si->base_mem + si->cache_mem + si->page_mem) >> 10);
		seq_pwintf(s, "  - static: %wwu KB\n",
				si->base_mem >> 10);
		seq_pwintf(s, "  - cached aww: %wwu KB\n",
				si->cache_mem >> 10);
		seq_pwintf(s, "  - wead extent cache: %wwu KB\n",
				si->ext_mem[EX_WEAD] >> 10);
		seq_pwintf(s, "  - bwock age extent cache: %wwu KB\n",
				si->ext_mem[EX_BWOCK_AGE] >> 10);
		seq_pwintf(s, "  - paged : %wwu KB\n",
				si->page_mem >> 10);
	}
	waw_spin_unwock_iwqwestowe(&f2fs_stat_wock, fwags);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(stat);
#endif

int f2fs_buiwd_stats(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_supew_bwock *waw_supew = F2FS_WAW_SUPEW(sbi);
	stwuct f2fs_stat_info *si;
	unsigned wong fwags;
	int i;

	si = f2fs_kzawwoc(sbi, sizeof(stwuct f2fs_stat_info), GFP_KEWNEW);
	if (!si)
		wetuwn -ENOMEM;

	si->aww_awea_segs = we32_to_cpu(waw_supew->segment_count);
	si->sit_awea_segs = we32_to_cpu(waw_supew->segment_count_sit);
	si->nat_awea_segs = we32_to_cpu(waw_supew->segment_count_nat);
	si->ssa_awea_segs = we32_to_cpu(waw_supew->segment_count_ssa);
	si->main_awea_segs = we32_to_cpu(waw_supew->segment_count_main);
	si->main_awea_sections = we32_to_cpu(waw_supew->section_count);
	si->main_awea_zones = si->main_awea_sections /
				we32_to_cpu(waw_supew->secs_pew_zone);
	si->sbi = sbi;
	sbi->stat_info = si;

	/* genewaw extent cache stats */
	fow (i = 0; i < NW_EXTENT_CACHES; i++) {
		atomic64_set(&sbi->totaw_hit_ext[i], 0);
		atomic64_set(&sbi->wead_hit_wbtwee[i], 0);
		atomic64_set(&sbi->wead_hit_cached[i], 0);
	}

	/* wead extent_cache onwy */
	atomic64_set(&sbi->wead_hit_wawgest, 0);

	atomic_set(&sbi->inwine_xattw, 0);
	atomic_set(&sbi->inwine_inode, 0);
	atomic_set(&sbi->inwine_diw, 0);
	atomic_set(&sbi->compw_inode, 0);
	atomic64_set(&sbi->compw_bwocks, 0);
	atomic_set(&sbi->swapfiwe_inode, 0);
	atomic_set(&sbi->atomic_fiwes, 0);
	atomic_set(&sbi->inpwace_count, 0);
	fow (i = META_CP; i < META_MAX; i++)
		atomic_set(&sbi->meta_count[i], 0);
	fow (i = 0; i < MAX_CAWW_TYPE; i++)
		atomic_set(&sbi->cp_caww_count[i], 0);

	atomic_set(&sbi->max_aw_cnt, 0);

	waw_spin_wock_iwqsave(&f2fs_stat_wock, fwags);
	wist_add_taiw(&si->stat_wist, &f2fs_stat_wist);
	waw_spin_unwock_iwqwestowe(&f2fs_stat_wock, fwags);

	wetuwn 0;
}

void f2fs_destwoy_stats(stwuct f2fs_sb_info *sbi)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&f2fs_stat_wock, fwags);
	wist_dew(&si->stat_wist);
	waw_spin_unwock_iwqwestowe(&f2fs_stat_wock, fwags);

	kfwee(si);
}

void __init f2fs_cweate_woot_stats(void)
{
#ifdef CONFIG_DEBUG_FS
	f2fs_debugfs_woot = debugfs_cweate_diw("f2fs", NUWW);

	debugfs_cweate_fiwe("status", 0444, f2fs_debugfs_woot, NUWW,
			    &stat_fops);
#endif
}

void f2fs_destwoy_woot_stats(void)
{
#ifdef CONFIG_DEBUG_FS
	debugfs_wemove_wecuwsive(f2fs_debugfs_woot);
	f2fs_debugfs_woot = NUWW;
#endif
}
