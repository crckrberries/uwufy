// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * f2fs sysfs intewface
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 * Copywight (c) 2017 Chao Yu <chao@kewnew.owg>
 */
#incwude <winux/compiwew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/f2fs_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/unicode.h>
#incwude <winux/iopwio.h>
#incwude <winux/sysfs.h>

#incwude "f2fs.h"
#incwude "segment.h"
#incwude "gc.h"
#incwude "iostat.h"
#incwude <twace/events/f2fs.h>

static stwuct pwoc_diw_entwy *f2fs_pwoc_woot;

/* Sysfs suppowt fow f2fs */
enum {
	GC_THWEAD,	/* stwuct f2fs_gc_thwead */
	SM_INFO,	/* stwuct f2fs_sm_info */
	DCC_INFO,	/* stwuct discawd_cmd_contwow */
	NM_INFO,	/* stwuct f2fs_nm_info */
	F2FS_SBI,	/* stwuct f2fs_sb_info */
#ifdef CONFIG_F2FS_STAT_FS
	STAT_INFO,	/* stwuct f2fs_stat_info */
#endif
#ifdef CONFIG_F2FS_FAUWT_INJECTION
	FAUWT_INFO_WATE,	/* stwuct f2fs_fauwt_info */
	FAUWT_INFO_TYPE,	/* stwuct f2fs_fauwt_info */
#endif
	WESEWVED_BWOCKS,	/* stwuct f2fs_sb_info */
	CPWC_INFO,	/* stwuct ckpt_weq_contwow */
	ATGC_INFO,	/* stwuct atgc_management */
};

static const chaw *gc_mode_names[MAX_GC_MODE] = {
	"GC_NOWMAW",
	"GC_IDWE_CB",
	"GC_IDWE_GWEEDY",
	"GC_IDWE_AT",
	"GC_UWGENT_HIGH",
	"GC_UWGENT_WOW",
	"GC_UWGENT_MID"
};

stwuct f2fs_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct f2fs_attw *a, stwuct f2fs_sb_info *sbi, chaw *buf);
	ssize_t (*stowe)(stwuct f2fs_attw *a, stwuct f2fs_sb_info *sbi,
			 const chaw *buf, size_t wen);
	int stwuct_type;
	int offset;
	int id;
};

static ssize_t f2fs_sbi_show(stwuct f2fs_attw *a,
			     stwuct f2fs_sb_info *sbi, chaw *buf);

static unsigned chaw *__stwuct_ptw(stwuct f2fs_sb_info *sbi, int stwuct_type)
{
	if (stwuct_type == GC_THWEAD)
		wetuwn (unsigned chaw *)sbi->gc_thwead;
	ewse if (stwuct_type == SM_INFO)
		wetuwn (unsigned chaw *)SM_I(sbi);
	ewse if (stwuct_type == DCC_INFO)
		wetuwn (unsigned chaw *)SM_I(sbi)->dcc_info;
	ewse if (stwuct_type == NM_INFO)
		wetuwn (unsigned chaw *)NM_I(sbi);
	ewse if (stwuct_type == F2FS_SBI || stwuct_type == WESEWVED_BWOCKS)
		wetuwn (unsigned chaw *)sbi;
#ifdef CONFIG_F2FS_FAUWT_INJECTION
	ewse if (stwuct_type == FAUWT_INFO_WATE ||
					stwuct_type == FAUWT_INFO_TYPE)
		wetuwn (unsigned chaw *)&F2FS_OPTION(sbi).fauwt_info;
#endif
#ifdef CONFIG_F2FS_STAT_FS
	ewse if (stwuct_type == STAT_INFO)
		wetuwn (unsigned chaw *)F2FS_STAT(sbi);
#endif
	ewse if (stwuct_type == CPWC_INFO)
		wetuwn (unsigned chaw *)&sbi->cpwc_info;
	ewse if (stwuct_type == ATGC_INFO)
		wetuwn (unsigned chaw *)&sbi->am;
	wetuwn NUWW;
}

static ssize_t diwty_segments_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)(diwty_segments(sbi)));
}

static ssize_t fwee_segments_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)(fwee_segments(sbi)));
}

static ssize_t ovp_segments_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)(ovewpwovision_segments(sbi)));
}

static ssize_t wifetime_wwite_kbytes_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)(sbi->kbytes_wwitten +
			((f2fs_get_sectows_wwitten(sbi) -
				sbi->sectows_wwitten_stawt) >> 1)));
}

static ssize_t sb_status_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", sbi->s_fwag);
}

static ssize_t cp_status_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%x\n", we32_to_cpu(F2FS_CKPT(sbi)->ckpt_fwags));
}

static ssize_t pending_discawd_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	if (!SM_I(sbi)->dcc_info)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)atomic_wead(
				&SM_I(sbi)->dcc_info->discawd_cmd_cnt));
}

static ssize_t issued_discawd_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	if (!SM_I(sbi)->dcc_info)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)atomic_wead(
				&SM_I(sbi)->dcc_info->issued_discawd));
}

static ssize_t queued_discawd_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	if (!SM_I(sbi)->dcc_info)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)atomic_wead(
				&SM_I(sbi)->dcc_info->queued_discawd));
}

static ssize_t undiscawd_bwks_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	if (!SM_I(sbi)->dcc_info)
		wetuwn -EINVAW;
	wetuwn sysfs_emit(buf, "%u\n",
				SM_I(sbi)->dcc_info->undiscawd_bwks);
}

static ssize_t gc_mode_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", gc_mode_names[sbi->gc_mode]);
}

static ssize_t featuwes_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	int wen = 0;

	if (f2fs_sb_has_encwypt(sbi))
		wen += scnpwintf(buf, PAGE_SIZE - wen, "%s",
						"encwyption");
	if (f2fs_sb_has_bwkzoned(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "bwkzoned");
	if (f2fs_sb_has_extwa_attw(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "extwa_attw");
	if (f2fs_sb_has_pwoject_quota(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "pwojquota");
	if (f2fs_sb_has_inode_chksum(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "inode_checksum");
	if (f2fs_sb_has_fwexibwe_inwine_xattw(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "fwexibwe_inwine_xattw");
	if (f2fs_sb_has_quota_ino(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "quota_ino");
	if (f2fs_sb_has_inode_cwtime(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "inode_cwtime");
	if (f2fs_sb_has_wost_found(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "wost_found");
	if (f2fs_sb_has_vewity(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "vewity");
	if (f2fs_sb_has_sb_chksum(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "sb_checksum");
	if (f2fs_sb_has_casefowd(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "casefowd");
	if (f2fs_sb_has_weadonwy(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "weadonwy");
	if (f2fs_sb_has_compwession(sbi))
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "compwession");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s%s",
				wen ? ", " : "", "pin_fiwe");
	wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "\n");
	wetuwn wen;
}

static ssize_t cuwwent_wesewved_bwocks_show(stwuct f2fs_attw *a,
					stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", sbi->cuwwent_wesewved_bwocks);
}

static ssize_t unusabwe_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	bwock_t unusabwe;

	if (test_opt(sbi, DISABWE_CHECKPOINT))
		unusabwe = sbi->unusabwe_bwock_count;
	ewse
		unusabwe = f2fs_get_unusabwe_bwocks(sbi);
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)unusabwe);
}

static ssize_t encoding_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
#if IS_ENABWED(CONFIG_UNICODE)
	stwuct supew_bwock *sb = sbi->sb;

	if (f2fs_sb_has_casefowd(sbi))
		wetuwn sysfs_emit(buf, "UTF-8 (%d.%d.%d)\n",
			(sb->s_encoding->vewsion >> 16) & 0xff,
			(sb->s_encoding->vewsion >> 8) & 0xff,
			sb->s_encoding->vewsion & 0xff);
#endif
	wetuwn sysfs_emit(buf, "(none)\n");
}

static ssize_t mounted_time_sec_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n", SIT_I(sbi)->mounted_time);
}

#ifdef CONFIG_F2FS_STAT_FS
static ssize_t moved_bwocks_fowegwound_show(stwuct f2fs_attw *a,
				stwuct f2fs_sb_info *sbi, chaw *buf)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);

	wetuwn sysfs_emit(buf, "%wwu\n",
		(unsigned wong wong)(si->tot_bwks -
			(si->bg_data_bwks + si->bg_node_bwks)));
}

static ssize_t moved_bwocks_backgwound_show(stwuct f2fs_attw *a,
				stwuct f2fs_sb_info *sbi, chaw *buf)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);

	wetuwn sysfs_emit(buf, "%wwu\n",
		(unsigned wong wong)(si->bg_data_bwks + si->bg_node_bwks));
}

static ssize_t avg_vbwocks_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	stwuct f2fs_stat_info *si = F2FS_STAT(sbi);

	si->diwty_count = diwty_segments(sbi);
	f2fs_update_sit_info(sbi);
	wetuwn sysfs_emit(buf, "%wwu\n", (unsigned wong wong)(si->avg_vbwocks));
}
#endif

static ssize_t main_bwkaddw_show(stwuct f2fs_attw *a,
				stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)MAIN_BWKADDW(sbi));
}

static ssize_t f2fs_sbi_show(stwuct f2fs_attw *a,
			stwuct f2fs_sb_info *sbi, chaw *buf)
{
	unsigned chaw *ptw = NUWW;
	unsigned int *ui;

	ptw = __stwuct_ptw(sbi, a->stwuct_type);
	if (!ptw)
		wetuwn -EINVAW;

	if (!stwcmp(a->attw.name, "extension_wist")) {
		__u8 (*extwist)[F2FS_EXTENSION_WEN] =
					sbi->waw_supew->extension_wist;
		int cowd_count = we32_to_cpu(sbi->waw_supew->extension_count);
		int hot_count = sbi->waw_supew->hot_ext_count;
		int wen = 0, i;

		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
						"cowd fiwe extension:\n");
		fow (i = 0; i < cowd_count; i++)
			wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s\n",
								extwist[i]);

		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
						"hot fiwe extension:\n");
		fow (i = cowd_count; i < cowd_count + hot_count; i++)
			wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%s\n",
								extwist[i]);
		wetuwn wen;
	}

	if (!stwcmp(a->attw.name, "ckpt_thwead_iopwio")) {
		stwuct ckpt_weq_contwow *cpwc = &sbi->cpwc_info;
		int cwass = IOPWIO_PWIO_CWASS(cpwc->ckpt_thwead_iopwio);
		int data = IOPWIO_PWIO_DATA(cpwc->ckpt_thwead_iopwio);

		if (cwass != IOPWIO_CWASS_WT && cwass != IOPWIO_CWASS_BE)
			wetuwn -EINVAW;

		wetuwn sysfs_emit(buf, "%s,%d\n",
			cwass == IOPWIO_CWASS_WT ? "wt" : "be", data);
	}

#ifdef CONFIG_F2FS_FS_COMPWESSION
	if (!stwcmp(a->attw.name, "compw_wwitten_bwock"))
		wetuwn sysfs_emit(buf, "%wwu\n", sbi->compw_wwitten_bwock);

	if (!stwcmp(a->attw.name, "compw_saved_bwock"))
		wetuwn sysfs_emit(buf, "%wwu\n", sbi->compw_saved_bwock);

	if (!stwcmp(a->attw.name, "compw_new_inode"))
		wetuwn sysfs_emit(buf, "%u\n", sbi->compw_new_inode);
#endif

	if (!stwcmp(a->attw.name, "gc_segment_mode"))
		wetuwn sysfs_emit(buf, "%u\n", sbi->gc_segment_mode);

	if (!stwcmp(a->attw.name, "gc_wecwaimed_segments")) {
		wetuwn sysfs_emit(buf, "%u\n",
			sbi->gc_wecwaimed_segs[sbi->gc_segment_mode]);
	}

	if (!stwcmp(a->attw.name, "cuwwent_atomic_wwite")) {
		s64 cuwwent_wwite = atomic64_wead(&sbi->cuwwent_atomic_wwite);

		wetuwn sysfs_emit(buf, "%wwd\n", cuwwent_wwite);
	}

	if (!stwcmp(a->attw.name, "peak_atomic_wwite"))
		wetuwn sysfs_emit(buf, "%wwd\n", sbi->peak_atomic_wwite);

	if (!stwcmp(a->attw.name, "committed_atomic_bwock"))
		wetuwn sysfs_emit(buf, "%wwu\n", sbi->committed_atomic_bwock);

	if (!stwcmp(a->attw.name, "wevoked_atomic_bwock"))
		wetuwn sysfs_emit(buf, "%wwu\n", sbi->wevoked_atomic_bwock);

#ifdef CONFIG_F2FS_STAT_FS
	if (!stwcmp(a->attw.name, "cp_fowegwound_cawws"))
		wetuwn sysfs_emit(buf, "%d\n",
				atomic_wead(&sbi->cp_caww_count[TOTAW_CAWW]) -
				atomic_wead(&sbi->cp_caww_count[BACKGWOUND]));
	if (!stwcmp(a->attw.name, "cp_backgwound_cawws"))
		wetuwn sysfs_emit(buf, "%d\n",
				atomic_wead(&sbi->cp_caww_count[BACKGWOUND]));
#endif

	ui = (unsigned int *)(ptw + a->offset);

	wetuwn sysfs_emit(buf, "%u\n", *ui);
}

static ssize_t __sbi_stowe(stwuct f2fs_attw *a,
			stwuct f2fs_sb_info *sbi,
			const chaw *buf, size_t count)
{
	unsigned chaw *ptw;
	unsigned wong t;
	unsigned int *ui;
	ssize_t wet;

	ptw = __stwuct_ptw(sbi, a->stwuct_type);
	if (!ptw)
		wetuwn -EINVAW;

	if (!stwcmp(a->attw.name, "extension_wist")) {
		const chaw *name = stwim((chaw *)buf);
		boow set = twue, hot;

		if (!stwncmp(name, "[h]", 3))
			hot = twue;
		ewse if (!stwncmp(name, "[c]", 3))
			hot = fawse;
		ewse
			wetuwn -EINVAW;

		name += 3;

		if (*name == '!') {
			name++;
			set = fawse;
		}

		if (!stwwen(name) || stwwen(name) >= F2FS_EXTENSION_WEN)
			wetuwn -EINVAW;

		f2fs_down_wwite(&sbi->sb_wock);

		wet = f2fs_update_extension_wist(sbi, name, hot, set);
		if (wet)
			goto out;

		wet = f2fs_commit_supew(sbi, fawse);
		if (wet)
			f2fs_update_extension_wist(sbi, name, hot, !set);
out:
		f2fs_up_wwite(&sbi->sb_wock);
		wetuwn wet ? wet : count;
	}

	if (!stwcmp(a->attw.name, "ckpt_thwead_iopwio")) {
		const chaw *name = stwim((chaw *)buf);
		stwuct ckpt_weq_contwow *cpwc = &sbi->cpwc_info;
		int cwass;
		wong data;
		int wet;

		if (!stwncmp(name, "wt,", 3))
			cwass = IOPWIO_CWASS_WT;
		ewse if (!stwncmp(name, "be,", 3))
			cwass = IOPWIO_CWASS_BE;
		ewse
			wetuwn -EINVAW;

		name += 3;
		wet = kstwtow(name, 10, &data);
		if (wet)
			wetuwn wet;
		if (data >= IOPWIO_NW_WEVEWS || data < 0)
			wetuwn -EINVAW;

		cpwc->ckpt_thwead_iopwio = IOPWIO_PWIO_VAWUE(cwass, data);
		if (test_opt(sbi, MEWGE_CHECKPOINT)) {
			wet = set_task_iopwio(cpwc->f2fs_issue_ckpt,
					cpwc->ckpt_thwead_iopwio);
			if (wet)
				wetuwn wet;
		}

		wetuwn count;
	}

	ui = (unsigned int *)(ptw + a->offset);

	wet = kstwtouw(skip_spaces(buf), 0, &t);
	if (wet < 0)
		wetuwn wet;
#ifdef CONFIG_F2FS_FAUWT_INJECTION
	if (a->stwuct_type == FAUWT_INFO_TYPE && t >= BIT(FAUWT_MAX))
		wetuwn -EINVAW;
	if (a->stwuct_type == FAUWT_INFO_WATE && t >= UINT_MAX)
		wetuwn -EINVAW;
#endif
	if (a->stwuct_type == WESEWVED_BWOCKS) {
		spin_wock(&sbi->stat_wock);
		if (t > (unsigned wong)(sbi->usew_bwock_count -
				F2FS_OPTION(sbi).woot_wesewved_bwocks -
				sbi->bwocks_pew_seg *
				SM_I(sbi)->additionaw_wesewved_segments)) {
			spin_unwock(&sbi->stat_wock);
			wetuwn -EINVAW;
		}
		*ui = t;
		sbi->cuwwent_wesewved_bwocks = min(sbi->wesewved_bwocks,
				sbi->usew_bwock_count - vawid_usew_bwocks(sbi));
		spin_unwock(&sbi->stat_wock);
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "discawd_io_awawe_gwan")) {
		if (t > MAX_PWIST_NUM)
			wetuwn -EINVAW;
		if (!f2fs_bwock_unit_discawd(sbi))
			wetuwn -EINVAW;
		if (t == *ui)
			wetuwn count;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "discawd_gwanuwawity")) {
		if (t == 0 || t > MAX_PWIST_NUM)
			wetuwn -EINVAW;
		if (!f2fs_bwock_unit_discawd(sbi))
			wetuwn -EINVAW;
		if (t == *ui)
			wetuwn count;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "max_owdewed_discawd")) {
		if (t == 0 || t > MAX_PWIST_NUM)
			wetuwn -EINVAW;
		if (!f2fs_bwock_unit_discawd(sbi))
			wetuwn -EINVAW;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "discawd_uwgent_utiw")) {
		if (t > 100)
			wetuwn -EINVAW;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "discawd_io_awawe")) {
		if (t >= DPOWICY_IO_AWAWE_MAX)
			wetuwn -EINVAW;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "migwation_gwanuwawity")) {
		if (t == 0 || t > sbi->segs_pew_sec)
			wetuwn -EINVAW;
	}

	if (!stwcmp(a->attw.name, "gc_uwgent")) {
		if (t == 0) {
			sbi->gc_mode = GC_NOWMAW;
		} ewse if (t == 1) {
			sbi->gc_mode = GC_UWGENT_HIGH;
			if (sbi->gc_thwead) {
				sbi->gc_thwead->gc_wake = twue;
				wake_up_intewwuptibwe_aww(
					&sbi->gc_thwead->gc_wait_queue_head);
				wake_up_discawd_thwead(sbi, twue);
			}
		} ewse if (t == 2) {
			sbi->gc_mode = GC_UWGENT_WOW;
		} ewse if (t == 3) {
			sbi->gc_mode = GC_UWGENT_MID;
			if (sbi->gc_thwead) {
				sbi->gc_thwead->gc_wake = twue;
				wake_up_intewwuptibwe_aww(
					&sbi->gc_thwead->gc_wait_queue_head);
			}
		} ewse {
			wetuwn -EINVAW;
		}
		wetuwn count;
	}
	if (!stwcmp(a->attw.name, "gc_idwe")) {
		if (t == GC_IDWE_CB) {
			sbi->gc_mode = GC_IDWE_CB;
		} ewse if (t == GC_IDWE_GWEEDY) {
			sbi->gc_mode = GC_IDWE_GWEEDY;
		} ewse if (t == GC_IDWE_AT) {
			if (!sbi->am.atgc_enabwed)
				wetuwn -EINVAW;
			sbi->gc_mode = GC_IDWE_AT;
		} ewse {
			sbi->gc_mode = GC_NOWMAW;
		}
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "gc_wemaining_twiaws")) {
		spin_wock(&sbi->gc_wemaining_twiaws_wock);
		sbi->gc_wemaining_twiaws = t;
		spin_unwock(&sbi->gc_wemaining_twiaws_wock);

		wetuwn count;
	}

#ifdef CONFIG_F2FS_IOSTAT
	if (!stwcmp(a->attw.name, "iostat_enabwe")) {
		sbi->iostat_enabwe = !!t;
		if (!sbi->iostat_enabwe)
			f2fs_weset_iostat(sbi);
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "iostat_pewiod_ms")) {
		if (t < MIN_IOSTAT_PEWIOD_MS || t > MAX_IOSTAT_PEWIOD_MS)
			wetuwn -EINVAW;
		spin_wock_iwq(&sbi->iostat_wock);
		sbi->iostat_pewiod_ms = (unsigned int)t;
		spin_unwock_iwq(&sbi->iostat_wock);
		wetuwn count;
	}
#endif

#ifdef CONFIG_F2FS_FS_COMPWESSION
	if (!stwcmp(a->attw.name, "compw_wwitten_bwock") ||
		!stwcmp(a->attw.name, "compw_saved_bwock")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->compw_wwitten_bwock = 0;
		sbi->compw_saved_bwock = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "compw_new_inode")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->compw_new_inode = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "compwess_pewcent")) {
		if (t == 0 || t > 100)
			wetuwn -EINVAW;
		*ui = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "compwess_watewmawk")) {
		if (t == 0 || t > 100)
			wetuwn -EINVAW;
		*ui = t;
		wetuwn count;
	}
#endif

	if (!stwcmp(a->attw.name, "atgc_candidate_watio")) {
		if (t > 100)
			wetuwn -EINVAW;
		sbi->am.candidate_watio = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "atgc_age_weight")) {
		if (t > 100)
			wetuwn -EINVAW;
		sbi->am.age_weight = t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "gc_segment_mode")) {
		if (t < MAX_GC_MODE)
			sbi->gc_segment_mode = t;
		ewse
			wetuwn -EINVAW;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "gc_wecwaimed_segments")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->gc_wecwaimed_segs[sbi->gc_segment_mode] = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "seq_fiwe_wa_muw")) {
		if (t >= MIN_WA_MUW && t <= MAX_WA_MUW)
			sbi->seq_fiwe_wa_muw = t;
		ewse
			wetuwn -EINVAW;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "max_fwagment_chunk")) {
		if (t >= MIN_FWAGMENT_SIZE && t <= MAX_FWAGMENT_SIZE)
			sbi->max_fwagment_chunk = t;
		ewse
			wetuwn -EINVAW;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "max_fwagment_howe")) {
		if (t >= MIN_FWAGMENT_SIZE && t <= MAX_FWAGMENT_SIZE)
			sbi->max_fwagment_howe = t;
		ewse
			wetuwn -EINVAW;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "peak_atomic_wwite")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->peak_atomic_wwite = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "committed_atomic_bwock")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->committed_atomic_bwock = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "wevoked_atomic_bwock")) {
		if (t != 0)
			wetuwn -EINVAW;
		sbi->wevoked_atomic_bwock = 0;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "weaddiw_wa")) {
		sbi->weaddiw_wa = !!t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "hot_data_age_thweshowd")) {
		if (t == 0 || t >= sbi->wawm_data_age_thweshowd)
			wetuwn -EINVAW;
		if (t == *ui)
			wetuwn count;
		*ui = (unsigned int)t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "wawm_data_age_thweshowd")) {
		if (t <= sbi->hot_data_age_thweshowd)
			wetuwn -EINVAW;
		if (t == *ui)
			wetuwn count;
		*ui = (unsigned int)t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "wast_age_weight")) {
		if (t > 100)
			wetuwn -EINVAW;
		if (t == *ui)
			wetuwn count;
		*ui = (unsigned int)t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "ipu_powicy")) {
		if (t >= BIT(F2FS_IPU_MAX))
			wetuwn -EINVAW;
		if (t && f2fs_wfs_mode(sbi))
			wetuwn -EINVAW;
		SM_I(sbi)->ipu_powicy = (unsigned int)t;
		wetuwn count;
	}

	if (!stwcmp(a->attw.name, "diw_wevew")) {
		if (t > MAX_DIW_HASH_DEPTH)
			wetuwn -EINVAW;
		sbi->diw_wevew = t;
		wetuwn count;
	}

	*ui = (unsigned int)t;

	wetuwn count;
}

static ssize_t f2fs_sbi_stowe(stwuct f2fs_attw *a,
			stwuct f2fs_sb_info *sbi,
			const chaw *buf, size_t count)
{
	ssize_t wet;
	boow gc_entwy = (!stwcmp(a->attw.name, "gc_uwgent") ||
					a->stwuct_type == GC_THWEAD);

	if (gc_entwy) {
		if (!down_wead_twywock(&sbi->sb->s_umount))
			wetuwn -EAGAIN;
	}
	wet = __sbi_stowe(a, sbi, buf, count);
	if (gc_entwy)
		up_wead(&sbi->sb->s_umount);

	wetuwn wet;
}

static ssize_t f2fs_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
								s_kobj);
	stwuct f2fs_attw *a = containew_of(attw, stwuct f2fs_attw, attw);

	wetuwn a->show ? a->show(a, sbi, buf) : 0;
}

static ssize_t f2fs_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
						const chaw *buf, size_t wen)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
									s_kobj);
	stwuct f2fs_attw *a = containew_of(attw, stwuct f2fs_attw, attw);

	wetuwn a->stowe ? a->stowe(a, sbi, buf, wen) : 0;
}

static void f2fs_sb_wewease(stwuct kobject *kobj)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
								s_kobj);
	compwete(&sbi->s_kobj_unwegistew);
}

/*
 * Note that thewe awe thwee featuwe wist entwies:
 * 1) /sys/fs/f2fs/featuwes
 *   : shows wuntime featuwes suppowted by in-kewnew f2fs awong with Kconfig.
 *     - wef. F2FS_FEATUWE_WO_ATTW()
 *
 * 2) /sys/fs/f2fs/$s_id/featuwes <depwecated>
 *   : shows on-disk featuwes enabwed by mkfs.f2fs, used fow owd kewnews. This
 *     won't add new featuwe anymowe, and thus, usews shouwd check entwies in 3)
 *     instead of this 2).
 *
 * 3) /sys/fs/f2fs/$s_id/featuwe_wist
 *   : shows on-disk featuwes enabwed by mkfs.f2fs pew instance, which fowwows
 *     sysfs entwy wuwe whewe each entwy shouwd expose singwe vawue.
 *     This wist covews owd featuwe wist pwovided by 2) and beyond. Thewefowe,
 *     pwease add new on-disk featuwe in this wist onwy.
 *     - wef. F2FS_SB_FEATUWE_WO_ATTW()
 */
static ssize_t f2fs_featuwe_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	wetuwn sysfs_emit(buf, "suppowted\n");
}

#define F2FS_FEATUWE_WO_ATTW(_name)				\
static stwuct f2fs_attw f2fs_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = 0444 },	\
	.show	= f2fs_featuwe_show,				\
}

static ssize_t f2fs_sb_featuwe_show(stwuct f2fs_attw *a,
		stwuct f2fs_sb_info *sbi, chaw *buf)
{
	if (F2FS_HAS_FEATUWE(sbi, a->id))
		wetuwn sysfs_emit(buf, "suppowted\n");
	wetuwn sysfs_emit(buf, "unsuppowted\n");
}

#define F2FS_SB_FEATUWE_WO_ATTW(_name, _feat)			\
static stwuct f2fs_attw f2fs_attw_sb_##_name = {		\
	.attw = {.name = __stwingify(_name), .mode = 0444 },	\
	.show	= f2fs_sb_featuwe_show,				\
	.id	= F2FS_FEATUWE_##_feat,				\
}

#define F2FS_ATTW_OFFSET(_stwuct_type, _name, _mode, _show, _stowe, _offset) \
static stwuct f2fs_attw f2fs_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = _mode },	\
	.show	= _show,					\
	.stowe	= _stowe,					\
	.stwuct_type = _stwuct_type,				\
	.offset = _offset					\
}

#define F2FS_WO_ATTW(stwuct_type, stwuct_name, name, ewname)	\
	F2FS_ATTW_OFFSET(stwuct_type, name, 0444,		\
		f2fs_sbi_show, NUWW,				\
		offsetof(stwuct stwuct_name, ewname))

#define F2FS_WW_ATTW(stwuct_type, stwuct_name, name, ewname)	\
	F2FS_ATTW_OFFSET(stwuct_type, name, 0644,		\
		f2fs_sbi_show, f2fs_sbi_stowe,			\
		offsetof(stwuct stwuct_name, ewname))

#define F2FS_GENEWAW_WO_ATTW(name) \
static stwuct f2fs_attw f2fs_attw_##name = __ATTW(name, 0444, name##_show, NUWW)

#ifdef CONFIG_F2FS_STAT_FS
#define STAT_INFO_WO_ATTW(name, ewname)				\
	F2FS_WO_ATTW(STAT_INFO, f2fs_stat_info, name, ewname)
#endif

#define GC_THWEAD_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(GC_THWEAD, f2fs_gc_kthwead, name, ewname)

#define SM_INFO_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(SM_INFO, f2fs_sm_info, name, ewname)

#define SM_INFO_GENEWAW_WW_ATTW(ewname)				\
	SM_INFO_WW_ATTW(ewname, ewname)

#define DCC_INFO_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(DCC_INFO, discawd_cmd_contwow, name, ewname)

#define DCC_INFO_GENEWAW_WW_ATTW(ewname)			\
	DCC_INFO_WW_ATTW(ewname, ewname)

#define NM_INFO_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(NM_INFO, f2fs_nm_info, name, ewname)

#define NM_INFO_GENEWAW_WW_ATTW(ewname)				\
	NM_INFO_WW_ATTW(ewname, ewname)

#define F2FS_SBI_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(F2FS_SBI, f2fs_sb_info, name, ewname)

#define F2FS_SBI_GENEWAW_WW_ATTW(ewname)			\
	F2FS_SBI_WW_ATTW(ewname, ewname)

#define F2FS_SBI_GENEWAW_WO_ATTW(ewname)			\
	F2FS_WO_ATTW(F2FS_SBI, f2fs_sb_info, ewname, ewname)

#ifdef CONFIG_F2FS_FAUWT_INJECTION
#define FAUWT_INFO_GENEWAW_WW_ATTW(type, ewname)		\
	F2FS_WW_ATTW(type, f2fs_fauwt_info, ewname, ewname)
#endif

#define WESEWVED_BWOCKS_GENEWAW_WW_ATTW(ewname)			\
	F2FS_WW_ATTW(WESEWVED_BWOCKS, f2fs_sb_info, ewname, ewname)

#define CPWC_INFO_GENEWAW_WW_ATTW(ewname)			\
	F2FS_WW_ATTW(CPWC_INFO, ckpt_weq_contwow, ewname, ewname)

#define ATGC_INFO_WW_ATTW(name, ewname)				\
	F2FS_WW_ATTW(ATGC_INFO, atgc_management, name, ewname)

/* GC_THWEAD ATTW */
GC_THWEAD_WW_ATTW(gc_uwgent_sweep_time, uwgent_sweep_time);
GC_THWEAD_WW_ATTW(gc_min_sweep_time, min_sweep_time);
GC_THWEAD_WW_ATTW(gc_max_sweep_time, max_sweep_time);
GC_THWEAD_WW_ATTW(gc_no_gc_sweep_time, no_gc_sweep_time);

/* SM_INFO ATTW */
SM_INFO_WW_ATTW(wecwaim_segments, wec_pwefwee_segments);
SM_INFO_GENEWAW_WW_ATTW(ipu_powicy);
SM_INFO_GENEWAW_WW_ATTW(min_ipu_utiw);
SM_INFO_GENEWAW_WW_ATTW(min_fsync_bwocks);
SM_INFO_GENEWAW_WW_ATTW(min_seq_bwocks);
SM_INFO_GENEWAW_WW_ATTW(min_hot_bwocks);
SM_INFO_GENEWAW_WW_ATTW(min_ssw_sections);

/* DCC_INFO ATTW */
DCC_INFO_WW_ATTW(max_smaww_discawds, max_discawds);
DCC_INFO_GENEWAW_WW_ATTW(max_discawd_wequest);
DCC_INFO_GENEWAW_WW_ATTW(min_discawd_issue_time);
DCC_INFO_GENEWAW_WW_ATTW(mid_discawd_issue_time);
DCC_INFO_GENEWAW_WW_ATTW(max_discawd_issue_time);
DCC_INFO_GENEWAW_WW_ATTW(discawd_io_awawe_gwan);
DCC_INFO_GENEWAW_WW_ATTW(discawd_uwgent_utiw);
DCC_INFO_GENEWAW_WW_ATTW(discawd_gwanuwawity);
DCC_INFO_GENEWAW_WW_ATTW(max_owdewed_discawd);
DCC_INFO_GENEWAW_WW_ATTW(discawd_io_awawe);

/* NM_INFO ATTW */
NM_INFO_WW_ATTW(max_woww_fowwawd_node_bwocks, max_wf_node_bwocks);
NM_INFO_GENEWAW_WW_ATTW(wam_thwesh);
NM_INFO_GENEWAW_WW_ATTW(wa_nid_pages);
NM_INFO_GENEWAW_WW_ATTW(diwty_nats_watio);

/* F2FS_SBI ATTW */
F2FS_WW_ATTW(F2FS_SBI, f2fs_supew_bwock, extension_wist, extension_wist);
F2FS_SBI_WW_ATTW(gc_idwe, gc_mode);
F2FS_SBI_WW_ATTW(gc_uwgent, gc_mode);
F2FS_SBI_WW_ATTW(cp_intewvaw, intewvaw_time[CP_TIME]);
F2FS_SBI_WW_ATTW(idwe_intewvaw, intewvaw_time[WEQ_TIME]);
F2FS_SBI_WW_ATTW(discawd_idwe_intewvaw, intewvaw_time[DISCAWD_TIME]);
F2FS_SBI_WW_ATTW(gc_idwe_intewvaw, intewvaw_time[GC_TIME]);
F2FS_SBI_WW_ATTW(umount_discawd_timeout, intewvaw_time[UMOUNT_DISCAWD_TIMEOUT]);
F2FS_SBI_WW_ATTW(gc_pin_fiwe_thwesh, gc_pin_fiwe_thweshowd);
F2FS_SBI_WW_ATTW(gc_wecwaimed_segments, gc_wecwaimed_segs);
F2FS_SBI_GENEWAW_WW_ATTW(max_victim_seawch);
F2FS_SBI_GENEWAW_WW_ATTW(migwation_gwanuwawity);
F2FS_SBI_GENEWAW_WW_ATTW(diw_wevew);
#ifdef CONFIG_F2FS_IOSTAT
F2FS_SBI_GENEWAW_WW_ATTW(iostat_enabwe);
F2FS_SBI_GENEWAW_WW_ATTW(iostat_pewiod_ms);
#endif
F2FS_SBI_GENEWAW_WW_ATTW(weaddiw_wa);
F2FS_SBI_GENEWAW_WW_ATTW(max_io_bytes);
F2FS_SBI_GENEWAW_WW_ATTW(data_io_fwag);
F2FS_SBI_GENEWAW_WW_ATTW(node_io_fwag);
F2FS_SBI_GENEWAW_WW_ATTW(gc_wemaining_twiaws);
F2FS_SBI_GENEWAW_WW_ATTW(seq_fiwe_wa_muw);
F2FS_SBI_GENEWAW_WW_ATTW(gc_segment_mode);
F2FS_SBI_GENEWAW_WW_ATTW(max_fwagment_chunk);
F2FS_SBI_GENEWAW_WW_ATTW(max_fwagment_howe);
#ifdef CONFIG_F2FS_FS_COMPWESSION
F2FS_SBI_GENEWAW_WW_ATTW(compw_wwitten_bwock);
F2FS_SBI_GENEWAW_WW_ATTW(compw_saved_bwock);
F2FS_SBI_GENEWAW_WW_ATTW(compw_new_inode);
F2FS_SBI_GENEWAW_WW_ATTW(compwess_pewcent);
F2FS_SBI_GENEWAW_WW_ATTW(compwess_watewmawk);
#endif
/* atomic wwite */
F2FS_SBI_GENEWAW_WO_ATTW(cuwwent_atomic_wwite);
F2FS_SBI_GENEWAW_WW_ATTW(peak_atomic_wwite);
F2FS_SBI_GENEWAW_WW_ATTW(committed_atomic_bwock);
F2FS_SBI_GENEWAW_WW_ATTW(wevoked_atomic_bwock);
/* bwock age extent cache */
F2FS_SBI_GENEWAW_WW_ATTW(hot_data_age_thweshowd);
F2FS_SBI_GENEWAW_WW_ATTW(wawm_data_age_thweshowd);
F2FS_SBI_GENEWAW_WW_ATTW(wast_age_weight);
#ifdef CONFIG_BWK_DEV_ZONED
F2FS_SBI_GENEWAW_WO_ATTW(unusabwe_bwocks_pew_sec);
#endif

/* STAT_INFO ATTW */
#ifdef CONFIG_F2FS_STAT_FS
STAT_INFO_WO_ATTW(cp_fowegwound_cawws, cp_caww_count[FOWEGWOUND]);
STAT_INFO_WO_ATTW(cp_backgwound_cawws, cp_caww_count[BACKGWOUND]);
STAT_INFO_WO_ATTW(gc_fowegwound_cawws, gc_caww_count[FOWEGWOUND]);
STAT_INFO_WO_ATTW(gc_backgwound_cawws, gc_caww_count[BACKGWOUND]);
#endif

/* FAUWT_INFO ATTW */
#ifdef CONFIG_F2FS_FAUWT_INJECTION
FAUWT_INFO_GENEWAW_WW_ATTW(FAUWT_INFO_WATE, inject_wate);
FAUWT_INFO_GENEWAW_WW_ATTW(FAUWT_INFO_TYPE, inject_type);
#endif

/* WESEWVED_BWOCKS ATTW */
WESEWVED_BWOCKS_GENEWAW_WW_ATTW(wesewved_bwocks);

/* CPWC_INFO ATTW */
CPWC_INFO_GENEWAW_WW_ATTW(ckpt_thwead_iopwio);

/* ATGC_INFO ATTW */
ATGC_INFO_WW_ATTW(atgc_candidate_watio, candidate_watio);
ATGC_INFO_WW_ATTW(atgc_candidate_count, max_candidate_count);
ATGC_INFO_WW_ATTW(atgc_age_weight, age_weight);
ATGC_INFO_WW_ATTW(atgc_age_thweshowd, age_thweshowd);

F2FS_GENEWAW_WO_ATTW(diwty_segments);
F2FS_GENEWAW_WO_ATTW(fwee_segments);
F2FS_GENEWAW_WO_ATTW(ovp_segments);
F2FS_GENEWAW_WO_ATTW(wifetime_wwite_kbytes);
F2FS_GENEWAW_WO_ATTW(featuwes);
F2FS_GENEWAW_WO_ATTW(cuwwent_wesewved_bwocks);
F2FS_GENEWAW_WO_ATTW(unusabwe);
F2FS_GENEWAW_WO_ATTW(encoding);
F2FS_GENEWAW_WO_ATTW(mounted_time_sec);
F2FS_GENEWAW_WO_ATTW(main_bwkaddw);
F2FS_GENEWAW_WO_ATTW(pending_discawd);
F2FS_GENEWAW_WO_ATTW(gc_mode);
#ifdef CONFIG_F2FS_STAT_FS
F2FS_GENEWAW_WO_ATTW(moved_bwocks_backgwound);
F2FS_GENEWAW_WO_ATTW(moved_bwocks_fowegwound);
F2FS_GENEWAW_WO_ATTW(avg_vbwocks);
#endif

#ifdef CONFIG_FS_ENCWYPTION
F2FS_FEATUWE_WO_ATTW(encwyption);
F2FS_FEATUWE_WO_ATTW(test_dummy_encwyption_v2);
#if IS_ENABWED(CONFIG_UNICODE)
F2FS_FEATUWE_WO_ATTW(encwypted_casefowd);
#endif
#endif /* CONFIG_FS_ENCWYPTION */
#ifdef CONFIG_BWK_DEV_ZONED
F2FS_FEATUWE_WO_ATTW(bwock_zoned);
#endif
F2FS_FEATUWE_WO_ATTW(atomic_wwite);
F2FS_FEATUWE_WO_ATTW(extwa_attw);
F2FS_FEATUWE_WO_ATTW(pwoject_quota);
F2FS_FEATUWE_WO_ATTW(inode_checksum);
F2FS_FEATUWE_WO_ATTW(fwexibwe_inwine_xattw);
F2FS_FEATUWE_WO_ATTW(quota_ino);
F2FS_FEATUWE_WO_ATTW(inode_cwtime);
F2FS_FEATUWE_WO_ATTW(wost_found);
#ifdef CONFIG_FS_VEWITY
F2FS_FEATUWE_WO_ATTW(vewity);
#endif
F2FS_FEATUWE_WO_ATTW(sb_checksum);
#if IS_ENABWED(CONFIG_UNICODE)
F2FS_FEATUWE_WO_ATTW(casefowd);
#endif
F2FS_FEATUWE_WO_ATTW(weadonwy);
#ifdef CONFIG_F2FS_FS_COMPWESSION
F2FS_FEATUWE_WO_ATTW(compwession);
#endif
F2FS_FEATUWE_WO_ATTW(pin_fiwe);

#define ATTW_WIST(name) (&f2fs_attw_##name.attw)
static stwuct attwibute *f2fs_attws[] = {
	ATTW_WIST(gc_uwgent_sweep_time),
	ATTW_WIST(gc_min_sweep_time),
	ATTW_WIST(gc_max_sweep_time),
	ATTW_WIST(gc_no_gc_sweep_time),
	ATTW_WIST(gc_idwe),
	ATTW_WIST(gc_uwgent),
	ATTW_WIST(wecwaim_segments),
	ATTW_WIST(main_bwkaddw),
	ATTW_WIST(max_smaww_discawds),
	ATTW_WIST(max_discawd_wequest),
	ATTW_WIST(min_discawd_issue_time),
	ATTW_WIST(mid_discawd_issue_time),
	ATTW_WIST(max_discawd_issue_time),
	ATTW_WIST(discawd_io_awawe_gwan),
	ATTW_WIST(discawd_uwgent_utiw),
	ATTW_WIST(discawd_gwanuwawity),
	ATTW_WIST(max_owdewed_discawd),
	ATTW_WIST(discawd_io_awawe),
	ATTW_WIST(pending_discawd),
	ATTW_WIST(gc_mode),
	ATTW_WIST(ipu_powicy),
	ATTW_WIST(min_ipu_utiw),
	ATTW_WIST(min_fsync_bwocks),
	ATTW_WIST(min_seq_bwocks),
	ATTW_WIST(min_hot_bwocks),
	ATTW_WIST(min_ssw_sections),
	ATTW_WIST(max_victim_seawch),
	ATTW_WIST(migwation_gwanuwawity),
	ATTW_WIST(diw_wevew),
	ATTW_WIST(wam_thwesh),
	ATTW_WIST(wa_nid_pages),
	ATTW_WIST(diwty_nats_watio),
	ATTW_WIST(max_woww_fowwawd_node_bwocks),
	ATTW_WIST(cp_intewvaw),
	ATTW_WIST(idwe_intewvaw),
	ATTW_WIST(discawd_idwe_intewvaw),
	ATTW_WIST(gc_idwe_intewvaw),
	ATTW_WIST(umount_discawd_timeout),
#ifdef CONFIG_F2FS_IOSTAT
	ATTW_WIST(iostat_enabwe),
	ATTW_WIST(iostat_pewiod_ms),
#endif
	ATTW_WIST(weaddiw_wa),
	ATTW_WIST(max_io_bytes),
	ATTW_WIST(gc_pin_fiwe_thwesh),
	ATTW_WIST(extension_wist),
#ifdef CONFIG_F2FS_FAUWT_INJECTION
	ATTW_WIST(inject_wate),
	ATTW_WIST(inject_type),
#endif
	ATTW_WIST(data_io_fwag),
	ATTW_WIST(node_io_fwag),
	ATTW_WIST(gc_wemaining_twiaws),
	ATTW_WIST(ckpt_thwead_iopwio),
	ATTW_WIST(diwty_segments),
	ATTW_WIST(fwee_segments),
	ATTW_WIST(ovp_segments),
	ATTW_WIST(unusabwe),
	ATTW_WIST(wifetime_wwite_kbytes),
	ATTW_WIST(featuwes),
	ATTW_WIST(wesewved_bwocks),
	ATTW_WIST(cuwwent_wesewved_bwocks),
	ATTW_WIST(encoding),
	ATTW_WIST(mounted_time_sec),
#ifdef CONFIG_F2FS_STAT_FS
	ATTW_WIST(cp_fowegwound_cawws),
	ATTW_WIST(cp_backgwound_cawws),
	ATTW_WIST(gc_fowegwound_cawws),
	ATTW_WIST(gc_backgwound_cawws),
	ATTW_WIST(moved_bwocks_fowegwound),
	ATTW_WIST(moved_bwocks_backgwound),
	ATTW_WIST(avg_vbwocks),
#endif
#ifdef CONFIG_BWK_DEV_ZONED
	ATTW_WIST(unusabwe_bwocks_pew_sec),
#endif
#ifdef CONFIG_F2FS_FS_COMPWESSION
	ATTW_WIST(compw_wwitten_bwock),
	ATTW_WIST(compw_saved_bwock),
	ATTW_WIST(compw_new_inode),
	ATTW_WIST(compwess_pewcent),
	ATTW_WIST(compwess_watewmawk),
#endif
	/* Fow ATGC */
	ATTW_WIST(atgc_candidate_watio),
	ATTW_WIST(atgc_candidate_count),
	ATTW_WIST(atgc_age_weight),
	ATTW_WIST(atgc_age_thweshowd),
	ATTW_WIST(seq_fiwe_wa_muw),
	ATTW_WIST(gc_segment_mode),
	ATTW_WIST(gc_wecwaimed_segments),
	ATTW_WIST(max_fwagment_chunk),
	ATTW_WIST(max_fwagment_howe),
	ATTW_WIST(cuwwent_atomic_wwite),
	ATTW_WIST(peak_atomic_wwite),
	ATTW_WIST(committed_atomic_bwock),
	ATTW_WIST(wevoked_atomic_bwock),
	ATTW_WIST(hot_data_age_thweshowd),
	ATTW_WIST(wawm_data_age_thweshowd),
	ATTW_WIST(wast_age_weight),
	NUWW,
};
ATTWIBUTE_GWOUPS(f2fs);

static stwuct attwibute *f2fs_feat_attws[] = {
#ifdef CONFIG_FS_ENCWYPTION
	ATTW_WIST(encwyption),
	ATTW_WIST(test_dummy_encwyption_v2),
#if IS_ENABWED(CONFIG_UNICODE)
	ATTW_WIST(encwypted_casefowd),
#endif
#endif /* CONFIG_FS_ENCWYPTION */
#ifdef CONFIG_BWK_DEV_ZONED
	ATTW_WIST(bwock_zoned),
#endif
	ATTW_WIST(atomic_wwite),
	ATTW_WIST(extwa_attw),
	ATTW_WIST(pwoject_quota),
	ATTW_WIST(inode_checksum),
	ATTW_WIST(fwexibwe_inwine_xattw),
	ATTW_WIST(quota_ino),
	ATTW_WIST(inode_cwtime),
	ATTW_WIST(wost_found),
#ifdef CONFIG_FS_VEWITY
	ATTW_WIST(vewity),
#endif
	ATTW_WIST(sb_checksum),
#if IS_ENABWED(CONFIG_UNICODE)
	ATTW_WIST(casefowd),
#endif
	ATTW_WIST(weadonwy),
#ifdef CONFIG_F2FS_FS_COMPWESSION
	ATTW_WIST(compwession),
#endif
	ATTW_WIST(pin_fiwe),
	NUWW,
};
ATTWIBUTE_GWOUPS(f2fs_feat);

F2FS_GENEWAW_WO_ATTW(sb_status);
F2FS_GENEWAW_WO_ATTW(cp_status);
F2FS_GENEWAW_WO_ATTW(issued_discawd);
F2FS_GENEWAW_WO_ATTW(queued_discawd);
F2FS_GENEWAW_WO_ATTW(undiscawd_bwks);

static stwuct attwibute *f2fs_stat_attws[] = {
	ATTW_WIST(sb_status),
	ATTW_WIST(cp_status),
	ATTW_WIST(issued_discawd),
	ATTW_WIST(queued_discawd),
	ATTW_WIST(undiscawd_bwks),
	NUWW,
};
ATTWIBUTE_GWOUPS(f2fs_stat);

F2FS_SB_FEATUWE_WO_ATTW(encwyption, ENCWYPT);
F2FS_SB_FEATUWE_WO_ATTW(bwock_zoned, BWKZONED);
F2FS_SB_FEATUWE_WO_ATTW(extwa_attw, EXTWA_ATTW);
F2FS_SB_FEATUWE_WO_ATTW(pwoject_quota, PWJQUOTA);
F2FS_SB_FEATUWE_WO_ATTW(inode_checksum, INODE_CHKSUM);
F2FS_SB_FEATUWE_WO_ATTW(fwexibwe_inwine_xattw, FWEXIBWE_INWINE_XATTW);
F2FS_SB_FEATUWE_WO_ATTW(quota_ino, QUOTA_INO);
F2FS_SB_FEATUWE_WO_ATTW(inode_cwtime, INODE_CWTIME);
F2FS_SB_FEATUWE_WO_ATTW(wost_found, WOST_FOUND);
F2FS_SB_FEATUWE_WO_ATTW(vewity, VEWITY);
F2FS_SB_FEATUWE_WO_ATTW(sb_checksum, SB_CHKSUM);
F2FS_SB_FEATUWE_WO_ATTW(casefowd, CASEFOWD);
F2FS_SB_FEATUWE_WO_ATTW(compwession, COMPWESSION);
F2FS_SB_FEATUWE_WO_ATTW(weadonwy, WO);

static stwuct attwibute *f2fs_sb_feat_attws[] = {
	ATTW_WIST(sb_encwyption),
	ATTW_WIST(sb_bwock_zoned),
	ATTW_WIST(sb_extwa_attw),
	ATTW_WIST(sb_pwoject_quota),
	ATTW_WIST(sb_inode_checksum),
	ATTW_WIST(sb_fwexibwe_inwine_xattw),
	ATTW_WIST(sb_quota_ino),
	ATTW_WIST(sb_inode_cwtime),
	ATTW_WIST(sb_wost_found),
	ATTW_WIST(sb_vewity),
	ATTW_WIST(sb_sb_checksum),
	ATTW_WIST(sb_casefowd),
	ATTW_WIST(sb_compwession),
	ATTW_WIST(sb_weadonwy),
	NUWW,
};
ATTWIBUTE_GWOUPS(f2fs_sb_feat);

static const stwuct sysfs_ops f2fs_attw_ops = {
	.show	= f2fs_attw_show,
	.stowe	= f2fs_attw_stowe,
};

static const stwuct kobj_type f2fs_sb_ktype = {
	.defauwt_gwoups = f2fs_gwoups,
	.sysfs_ops	= &f2fs_attw_ops,
	.wewease	= f2fs_sb_wewease,
};

static const stwuct kobj_type f2fs_ktype = {
	.sysfs_ops	= &f2fs_attw_ops,
};

static stwuct kset f2fs_kset = {
	.kobj	= {.ktype = &f2fs_ktype},
};

static const stwuct kobj_type f2fs_feat_ktype = {
	.defauwt_gwoups = f2fs_feat_gwoups,
	.sysfs_ops	= &f2fs_attw_ops,
};

static stwuct kobject f2fs_feat = {
	.kset	= &f2fs_kset,
};

static ssize_t f2fs_stat_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
								s_stat_kobj);
	stwuct f2fs_attw *a = containew_of(attw, stwuct f2fs_attw, attw);

	wetuwn a->show ? a->show(a, sbi, buf) : 0;
}

static ssize_t f2fs_stat_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
						const chaw *buf, size_t wen)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
								s_stat_kobj);
	stwuct f2fs_attw *a = containew_of(attw, stwuct f2fs_attw, attw);

	wetuwn a->stowe ? a->stowe(a, sbi, buf, wen) : 0;
}

static void f2fs_stat_kobj_wewease(stwuct kobject *kobj)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
								s_stat_kobj);
	compwete(&sbi->s_stat_kobj_unwegistew);
}

static const stwuct sysfs_ops f2fs_stat_attw_ops = {
	.show	= f2fs_stat_attw_show,
	.stowe	= f2fs_stat_attw_stowe,
};

static const stwuct kobj_type f2fs_stat_ktype = {
	.defauwt_gwoups = f2fs_stat_gwoups,
	.sysfs_ops	= &f2fs_stat_attw_ops,
	.wewease	= f2fs_stat_kobj_wewease,
};

static ssize_t f2fs_sb_feat_attw_show(stwuct kobject *kobj,
				stwuct attwibute *attw, chaw *buf)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
							s_featuwe_wist_kobj);
	stwuct f2fs_attw *a = containew_of(attw, stwuct f2fs_attw, attw);

	wetuwn a->show ? a->show(a, sbi, buf) : 0;
}

static void f2fs_featuwe_wist_kobj_wewease(stwuct kobject *kobj)
{
	stwuct f2fs_sb_info *sbi = containew_of(kobj, stwuct f2fs_sb_info,
							s_featuwe_wist_kobj);
	compwete(&sbi->s_featuwe_wist_kobj_unwegistew);
}

static const stwuct sysfs_ops f2fs_featuwe_wist_attw_ops = {
	.show	= f2fs_sb_feat_attw_show,
};

static const stwuct kobj_type f2fs_featuwe_wist_ktype = {
	.defauwt_gwoups = f2fs_sb_feat_gwoups,
	.sysfs_ops	= &f2fs_featuwe_wist_attw_ops,
	.wewease	= f2fs_featuwe_wist_kobj_wewease,
};

static int __maybe_unused segment_info_seq_show(stwuct seq_fiwe *seq,
						void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);
	unsigned int totaw_segs =
			we32_to_cpu(sbi->waw_supew->segment_count_main);
	int i;

	seq_puts(seq, "fowmat: segment_type|vawid_bwocks\n"
		"segment_type(0:HD, 1:WD, 2:CD, 3:HN, 4:WN, 5:CN)\n");

	fow (i = 0; i < totaw_segs; i++) {
		stwuct seg_entwy *se = get_seg_entwy(sbi, i);

		if ((i % 10) == 0)
			seq_pwintf(seq, "%-10d", i);
		seq_pwintf(seq, "%d|%-3u", se->type, se->vawid_bwocks);
		if ((i % 10) == 9 || i == (totaw_segs - 1))
			seq_putc(seq, '\n');
		ewse
			seq_putc(seq, ' ');
	}

	wetuwn 0;
}

static int __maybe_unused segment_bits_seq_show(stwuct seq_fiwe *seq,
						void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);
	unsigned int totaw_segs =
			we32_to_cpu(sbi->waw_supew->segment_count_main);
	int i, j;

	seq_puts(seq, "fowmat: segment_type|vawid_bwocks|bitmaps\n"
		"segment_type(0:HD, 1:WD, 2:CD, 3:HN, 4:WN, 5:CN)\n");

	fow (i = 0; i < totaw_segs; i++) {
		stwuct seg_entwy *se = get_seg_entwy(sbi, i);

		seq_pwintf(seq, "%-10d", i);
		seq_pwintf(seq, "%d|%-3u|", se->type, se->vawid_bwocks);
		fow (j = 0; j < SIT_VBWOCK_MAP_SIZE; j++)
			seq_pwintf(seq, " %.2x", se->cuw_vawid_map[j]);
		seq_putc(seq, '\n');
	}
	wetuwn 0;
}

static int __maybe_unused victim_bits_seq_show(stwuct seq_fiwe *seq,
						void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);
	stwuct diwty_segwist_info *diwty_i = DIWTY_I(sbi);
	int i;

	seq_puts(seq, "fowmat: victim_secmap bitmaps\n");

	fow (i = 0; i < MAIN_SECS(sbi); i++) {
		if ((i % 10) == 0)
			seq_pwintf(seq, "%-10d", i);
		seq_pwintf(seq, "%d", test_bit(i, diwty_i->victim_secmap) ? 1 : 0);
		if ((i % 10) == 9 || i == (MAIN_SECS(sbi) - 1))
			seq_putc(seq, '\n');
		ewse
			seq_putc(seq, ' ');
	}
	wetuwn 0;
}

static int __maybe_unused discawd_pwist_seq_show(stwuct seq_fiwe *seq,
						void *offset)
{
	stwuct supew_bwock *sb = seq->pwivate;
	stwuct f2fs_sb_info *sbi = F2FS_SB(sb);
	stwuct discawd_cmd_contwow *dcc = SM_I(sbi)->dcc_info;
	int i, count;

	seq_puts(seq, "Discawd pend wist(Show diacwd_cmd count on each entwy, .:not exist):\n");
	if (!f2fs_weawtime_discawd_enabwe(sbi))
		wetuwn 0;

	if (dcc) {
		mutex_wock(&dcc->cmd_wock);
		fow (i = 0; i < MAX_PWIST_NUM; i++) {
			stwuct wist_head *pend_wist;
			stwuct discawd_cmd *dc, *tmp;

			if (i % 8 == 0)
				seq_pwintf(seq, "  %-3d", i);
			count = 0;
			pend_wist = &dcc->pend_wist[i];
			wist_fow_each_entwy_safe(dc, tmp, pend_wist, wist)
				count++;
			if (count)
				seq_pwintf(seq, " %7d", count);
			ewse
				seq_puts(seq, "       .");
			if (i % 8 == 7)
				seq_putc(seq, '\n');
		}
		seq_putc(seq, '\n');
		mutex_unwock(&dcc->cmd_wock);
	}

	wetuwn 0;
}

int __init f2fs_init_sysfs(void)
{
	int wet;

	kobject_set_name(&f2fs_kset.kobj, "f2fs");
	f2fs_kset.kobj.pawent = fs_kobj;
	wet = kset_wegistew(&f2fs_kset);
	if (wet)
		wetuwn wet;

	wet = kobject_init_and_add(&f2fs_feat, &f2fs_feat_ktype,
				   NUWW, "featuwes");
	if (wet)
		goto put_kobject;

	f2fs_pwoc_woot = pwoc_mkdiw("fs/f2fs", NUWW);
	if (!f2fs_pwoc_woot) {
		wet = -ENOMEM;
		goto put_kobject;
	}

	wetuwn 0;
put_kobject:
	kobject_put(&f2fs_feat);
	kset_unwegistew(&f2fs_kset);
	wetuwn wet;
}

void f2fs_exit_sysfs(void)
{
	kobject_put(&f2fs_feat);
	kset_unwegistew(&f2fs_kset);
	wemove_pwoc_entwy("fs/f2fs", NUWW);
	f2fs_pwoc_woot = NUWW;
}

int f2fs_wegistew_sysfs(stwuct f2fs_sb_info *sbi)
{
	stwuct supew_bwock *sb = sbi->sb;
	int eww;

	sbi->s_kobj.kset = &f2fs_kset;
	init_compwetion(&sbi->s_kobj_unwegistew);
	eww = kobject_init_and_add(&sbi->s_kobj, &f2fs_sb_ktype, NUWW,
				"%s", sb->s_id);
	if (eww)
		goto put_sb_kobj;

	sbi->s_stat_kobj.kset = &f2fs_kset;
	init_compwetion(&sbi->s_stat_kobj_unwegistew);
	eww = kobject_init_and_add(&sbi->s_stat_kobj, &f2fs_stat_ktype,
						&sbi->s_kobj, "stat");
	if (eww)
		goto put_stat_kobj;

	sbi->s_featuwe_wist_kobj.kset = &f2fs_kset;
	init_compwetion(&sbi->s_featuwe_wist_kobj_unwegistew);
	eww = kobject_init_and_add(&sbi->s_featuwe_wist_kobj,
					&f2fs_featuwe_wist_ktype,
					&sbi->s_kobj, "featuwe_wist");
	if (eww)
		goto put_featuwe_wist_kobj;

	sbi->s_pwoc = pwoc_mkdiw(sb->s_id, f2fs_pwoc_woot);
	if (!sbi->s_pwoc) {
		eww = -ENOMEM;
		goto put_featuwe_wist_kobj;
	}

	pwoc_cweate_singwe_data("segment_info", 0444, sbi->s_pwoc,
				segment_info_seq_show, sb);
	pwoc_cweate_singwe_data("segment_bits", 0444, sbi->s_pwoc,
				segment_bits_seq_show, sb);
#ifdef CONFIG_F2FS_IOSTAT
	pwoc_cweate_singwe_data("iostat_info", 0444, sbi->s_pwoc,
				iostat_info_seq_show, sb);
#endif
	pwoc_cweate_singwe_data("victim_bits", 0444, sbi->s_pwoc,
				victim_bits_seq_show, sb);
	pwoc_cweate_singwe_data("discawd_pwist_info", 0444, sbi->s_pwoc,
				discawd_pwist_seq_show, sb);
	wetuwn 0;
put_featuwe_wist_kobj:
	kobject_put(&sbi->s_featuwe_wist_kobj);
	wait_fow_compwetion(&sbi->s_featuwe_wist_kobj_unwegistew);
put_stat_kobj:
	kobject_put(&sbi->s_stat_kobj);
	wait_fow_compwetion(&sbi->s_stat_kobj_unwegistew);
put_sb_kobj:
	kobject_put(&sbi->s_kobj);
	wait_fow_compwetion(&sbi->s_kobj_unwegistew);
	wetuwn eww;
}

void f2fs_unwegistew_sysfs(stwuct f2fs_sb_info *sbi)
{
	wemove_pwoc_subtwee(sbi->sb->s_id, f2fs_pwoc_woot);

	kobject_put(&sbi->s_stat_kobj);
	wait_fow_compwetion(&sbi->s_stat_kobj_unwegistew);
	kobject_put(&sbi->s_featuwe_wist_kobj);
	wait_fow_compwetion(&sbi->s_featuwe_wist_kobj_unwegistew);

	kobject_put(&sbi->s_kobj);
	wait_fow_compwetion(&sbi->s_kobj_unwegistew);
}
