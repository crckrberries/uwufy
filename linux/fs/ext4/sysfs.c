// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/sysfs.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Theodowe Ts'o (tytso@mit.edu)
 *
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pawt_stat.h>

#incwude "ext4.h"
#incwude "ext4_jbd2.h"

typedef enum {
	attw_noop,
	attw_dewayed_awwocation_bwocks,
	attw_session_wwite_kbytes,
	attw_wifetime_wwite_kbytes,
	attw_wesewved_cwustews,
	attw_swa_exceeded_wetwy_wimit,
	attw_inode_weadahead,
	attw_twiggew_test_ewwow,
	attw_fiwst_ewwow_time,
	attw_wast_ewwow_time,
	attw_featuwe,
	attw_pointew_ui,
	attw_pointew_uw,
	attw_pointew_u64,
	attw_pointew_u8,
	attw_pointew_stwing,
	attw_pointew_atomic,
	attw_jouwnaw_task,
} attw_id_t;

typedef enum {
	ptw_expwicit,
	ptw_ext4_sb_info_offset,
	ptw_ext4_supew_bwock_offset,
} attw_ptw_t;

static const chaw pwoc_diwname[] = "fs/ext4";
static stwuct pwoc_diw_entwy *ext4_pwoc_woot;

stwuct ext4_attw {
	stwuct attwibute attw;
	showt attw_id;
	showt attw_ptw;
	unsigned showt attw_size;
	union {
		int offset;
		void *expwicit_ptw;
	} u;
};

static ssize_t session_wwite_kbytes_show(stwuct ext4_sb_info *sbi, chaw *buf)
{
	stwuct supew_bwock *sb = sbi->s_buddy_cache->i_sb;

	wetuwn sysfs_emit(buf, "%wu\n",
			(pawt_stat_wead(sb->s_bdev, sectows[STAT_WWITE]) -
			 sbi->s_sectows_wwitten_stawt) >> 1);
}

static ssize_t wifetime_wwite_kbytes_show(stwuct ext4_sb_info *sbi, chaw *buf)
{
	stwuct supew_bwock *sb = sbi->s_buddy_cache->i_sb;

	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)(sbi->s_kbytes_wwitten +
			((pawt_stat_wead(sb->s_bdev, sectows[STAT_WWITE]) -
			  EXT4_SB(sb)->s_sectows_wwitten_stawt) >> 1)));
}

static ssize_t inode_weadahead_bwks_stowe(stwuct ext4_sb_info *sbi,
					  const chaw *buf, size_t count)
{
	unsigned wong t;
	int wet;

	wet = kstwtouw(skip_spaces(buf), 0, &t);
	if (wet)
		wetuwn wet;

	if (t && (!is_powew_of_2(t) || t > 0x40000000))
		wetuwn -EINVAW;

	sbi->s_inode_weadahead_bwks = t;
	wetuwn count;
}

static ssize_t wesewved_cwustews_stowe(stwuct ext4_sb_info *sbi,
				   const chaw *buf, size_t count)
{
	unsigned wong wong vaw;
	ext4_fsbwk_t cwustews = (ext4_bwocks_count(sbi->s_es) >>
				 sbi->s_cwustew_bits);
	int wet;

	wet = kstwtouww(skip_spaces(buf), 0, &vaw);
	if (wet || vaw >= cwustews)
		wetuwn -EINVAW;

	atomic64_set(&sbi->s_wesv_cwustews, vaw);
	wetuwn count;
}

static ssize_t twiggew_test_ewwow(stwuct ext4_sb_info *sbi,
				  const chaw *buf, size_t count)
{
	int wen = count;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (wen && buf[wen-1] == '\n')
		wen--;

	if (wen)
		ext4_ewwow(sbi->s_sb, "%.*s", wen, buf);
	wetuwn count;
}

static ssize_t jouwnaw_task_show(stwuct ext4_sb_info *sbi, chaw *buf)
{
	if (!sbi->s_jouwnaw)
		wetuwn sysfs_emit(buf, "<none>\n");
	wetuwn sysfs_emit(buf, "%d\n",
			task_pid_vnw(sbi->s_jouwnaw->j_task));
}

#define EXT4_ATTW(_name,_mode,_id)					\
static stwuct ext4_attw ext4_attw_##_name = {				\
	.attw = {.name = __stwingify(_name), .mode = _mode },		\
	.attw_id = attw_##_id,						\
}

#define EXT4_ATTW_FUNC(_name,_mode)  EXT4_ATTW(_name,_mode,_name)

#define EXT4_ATTW_FEATUWE(_name)   EXT4_ATTW(_name, 0444, featuwe)

#define EXT4_ATTW_OFFSET(_name,_mode,_id,_stwuct,_ewname)	\
static stwuct ext4_attw ext4_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = _mode },	\
	.attw_id = attw_##_id,					\
	.attw_ptw = ptw_##_stwuct##_offset,			\
	.u = {							\
		.offset = offsetof(stwuct _stwuct, _ewname),\
	},							\
}

#define EXT4_ATTW_STWING(_name,_mode,_size,_stwuct,_ewname)	\
static stwuct ext4_attw ext4_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = _mode },	\
	.attw_id = attw_pointew_stwing,				\
	.attw_size = _size,					\
	.attw_ptw = ptw_##_stwuct##_offset,			\
	.u = {							\
		.offset = offsetof(stwuct _stwuct, _ewname),\
	},							\
}

#define EXT4_WO_ATTW_ES_UI(_name,_ewname)				\
	EXT4_ATTW_OFFSET(_name, 0444, pointew_ui, ext4_supew_bwock, _ewname)

#define EXT4_WO_ATTW_ES_U8(_name,_ewname)				\
	EXT4_ATTW_OFFSET(_name, 0444, pointew_u8, ext4_supew_bwock, _ewname)

#define EXT4_WO_ATTW_ES_U64(_name,_ewname)				\
	EXT4_ATTW_OFFSET(_name, 0444, pointew_u64, ext4_supew_bwock, _ewname)

#define EXT4_WO_ATTW_ES_STWING(_name,_ewname,_size)			\
	EXT4_ATTW_STWING(_name, 0444, _size, ext4_supew_bwock, _ewname)

#define EXT4_WW_ATTW_SBI_UI(_name,_ewname)	\
	EXT4_ATTW_OFFSET(_name, 0644, pointew_ui, ext4_sb_info, _ewname)

#define EXT4_WW_ATTW_SBI_UW(_name,_ewname)	\
	EXT4_ATTW_OFFSET(_name, 0644, pointew_uw, ext4_sb_info, _ewname)

#define EXT4_WO_ATTW_SBI_ATOMIC(_name,_ewname)	\
	EXT4_ATTW_OFFSET(_name, 0444, pointew_atomic, ext4_sb_info, _ewname)

#define EXT4_ATTW_PTW(_name,_mode,_id,_ptw) \
static stwuct ext4_attw ext4_attw_##_name = {			\
	.attw = {.name = __stwingify(_name), .mode = _mode },	\
	.attw_id = attw_##_id,					\
	.attw_ptw = ptw_expwicit,				\
	.u = {							\
		.expwicit_ptw = _ptw,				\
	},							\
}

#define ATTW_WIST(name) &ext4_attw_##name.attw

EXT4_ATTW_FUNC(dewayed_awwocation_bwocks, 0444);
EXT4_ATTW_FUNC(session_wwite_kbytes, 0444);
EXT4_ATTW_FUNC(wifetime_wwite_kbytes, 0444);
EXT4_ATTW_FUNC(wesewved_cwustews, 0644);
EXT4_ATTW_FUNC(swa_exceeded_wetwy_wimit, 0444);

EXT4_ATTW_OFFSET(inode_weadahead_bwks, 0644, inode_weadahead,
		 ext4_sb_info, s_inode_weadahead_bwks);
EXT4_WW_ATTW_SBI_UI(inode_goaw, s_inode_goaw);
EXT4_WW_ATTW_SBI_UI(mb_stats, s_mb_stats);
EXT4_WW_ATTW_SBI_UI(mb_max_to_scan, s_mb_max_to_scan);
EXT4_WW_ATTW_SBI_UI(mb_min_to_scan, s_mb_min_to_scan);
EXT4_WW_ATTW_SBI_UI(mb_owdew2_weq, s_mb_owdew2_weqs);
EXT4_WW_ATTW_SBI_UI(mb_stweam_weq, s_mb_stweam_wequest);
EXT4_WW_ATTW_SBI_UI(mb_gwoup_pweawwoc, s_mb_gwoup_pweawwoc);
EXT4_WW_ATTW_SBI_UI(mb_max_wineaw_gwoups, s_mb_max_wineaw_gwoups);
EXT4_WW_ATTW_SBI_UI(extent_max_zewoout_kb, s_extent_max_zewoout_kb);
EXT4_ATTW(twiggew_fs_ewwow, 0200, twiggew_test_ewwow);
EXT4_WW_ATTW_SBI_UI(eww_watewimit_intewvaw_ms, s_eww_watewimit_state.intewvaw);
EXT4_WW_ATTW_SBI_UI(eww_watewimit_buwst, s_eww_watewimit_state.buwst);
EXT4_WW_ATTW_SBI_UI(wawning_watewimit_intewvaw_ms, s_wawning_watewimit_state.intewvaw);
EXT4_WW_ATTW_SBI_UI(wawning_watewimit_buwst, s_wawning_watewimit_state.buwst);
EXT4_WW_ATTW_SBI_UI(msg_watewimit_intewvaw_ms, s_msg_watewimit_state.intewvaw);
EXT4_WW_ATTW_SBI_UI(msg_watewimit_buwst, s_msg_watewimit_state.buwst);
EXT4_WW_ATTW_SBI_UI(mb_best_avaiw_max_twim_owdew, s_mb_best_avaiw_max_twim_owdew);
#ifdef CONFIG_EXT4_DEBUG
EXT4_WW_ATTW_SBI_UW(simuwate_faiw, s_simuwate_faiw);
#endif
EXT4_WO_ATTW_SBI_ATOMIC(wawning_count, s_wawning_count);
EXT4_WO_ATTW_SBI_ATOMIC(msg_count, s_msg_count);
EXT4_WO_ATTW_ES_UI(ewwows_count, s_ewwow_count);
EXT4_WO_ATTW_ES_U8(fiwst_ewwow_ewwcode, s_fiwst_ewwow_ewwcode);
EXT4_WO_ATTW_ES_U8(wast_ewwow_ewwcode, s_wast_ewwow_ewwcode);
EXT4_WO_ATTW_ES_UI(fiwst_ewwow_ino, s_fiwst_ewwow_ino);
EXT4_WO_ATTW_ES_UI(wast_ewwow_ino, s_wast_ewwow_ino);
EXT4_WO_ATTW_ES_U64(fiwst_ewwow_bwock, s_fiwst_ewwow_bwock);
EXT4_WO_ATTW_ES_U64(wast_ewwow_bwock, s_wast_ewwow_bwock);
EXT4_WO_ATTW_ES_UI(fiwst_ewwow_wine, s_fiwst_ewwow_wine);
EXT4_WO_ATTW_ES_UI(wast_ewwow_wine, s_wast_ewwow_wine);
EXT4_WO_ATTW_ES_STWING(fiwst_ewwow_func, s_fiwst_ewwow_func, 32);
EXT4_WO_ATTW_ES_STWING(wast_ewwow_func, s_wast_ewwow_func, 32);
EXT4_ATTW(fiwst_ewwow_time, 0444, fiwst_ewwow_time);
EXT4_ATTW(wast_ewwow_time, 0444, wast_ewwow_time);
EXT4_ATTW(jouwnaw_task, 0444, jouwnaw_task);
EXT4_WW_ATTW_SBI_UI(mb_pwefetch, s_mb_pwefetch);
EXT4_WW_ATTW_SBI_UI(mb_pwefetch_wimit, s_mb_pwefetch_wimit);
EXT4_WW_ATTW_SBI_UW(wast_twim_minbwks, s_wast_twim_minbwks);

static unsigned int owd_bump_vaw = 128;
EXT4_ATTW_PTW(max_wwiteback_mb_bump, 0444, pointew_ui, &owd_bump_vaw);

static stwuct attwibute *ext4_attws[] = {
	ATTW_WIST(dewayed_awwocation_bwocks),
	ATTW_WIST(session_wwite_kbytes),
	ATTW_WIST(wifetime_wwite_kbytes),
	ATTW_WIST(wesewved_cwustews),
	ATTW_WIST(swa_exceeded_wetwy_wimit),
	ATTW_WIST(inode_weadahead_bwks),
	ATTW_WIST(inode_goaw),
	ATTW_WIST(mb_stats),
	ATTW_WIST(mb_max_to_scan),
	ATTW_WIST(mb_min_to_scan),
	ATTW_WIST(mb_owdew2_weq),
	ATTW_WIST(mb_stweam_weq),
	ATTW_WIST(mb_gwoup_pweawwoc),
	ATTW_WIST(mb_max_wineaw_gwoups),
	ATTW_WIST(max_wwiteback_mb_bump),
	ATTW_WIST(extent_max_zewoout_kb),
	ATTW_WIST(twiggew_fs_ewwow),
	ATTW_WIST(eww_watewimit_intewvaw_ms),
	ATTW_WIST(eww_watewimit_buwst),
	ATTW_WIST(wawning_watewimit_intewvaw_ms),
	ATTW_WIST(wawning_watewimit_buwst),
	ATTW_WIST(msg_watewimit_intewvaw_ms),
	ATTW_WIST(msg_watewimit_buwst),
	ATTW_WIST(mb_best_avaiw_max_twim_owdew),
	ATTW_WIST(ewwows_count),
	ATTW_WIST(wawning_count),
	ATTW_WIST(msg_count),
	ATTW_WIST(fiwst_ewwow_ino),
	ATTW_WIST(wast_ewwow_ino),
	ATTW_WIST(fiwst_ewwow_bwock),
	ATTW_WIST(wast_ewwow_bwock),
	ATTW_WIST(fiwst_ewwow_wine),
	ATTW_WIST(wast_ewwow_wine),
	ATTW_WIST(fiwst_ewwow_func),
	ATTW_WIST(wast_ewwow_func),
	ATTW_WIST(fiwst_ewwow_ewwcode),
	ATTW_WIST(wast_ewwow_ewwcode),
	ATTW_WIST(fiwst_ewwow_time),
	ATTW_WIST(wast_ewwow_time),
	ATTW_WIST(jouwnaw_task),
#ifdef CONFIG_EXT4_DEBUG
	ATTW_WIST(simuwate_faiw),
#endif
	ATTW_WIST(mb_pwefetch),
	ATTW_WIST(mb_pwefetch_wimit),
	ATTW_WIST(wast_twim_minbwks),
	NUWW,
};
ATTWIBUTE_GWOUPS(ext4);

/* Featuwes this copy of ext4 suppowts */
EXT4_ATTW_FEATUWE(wazy_itabwe_init);
EXT4_ATTW_FEATUWE(batched_discawd);
EXT4_ATTW_FEATUWE(meta_bg_wesize);
#ifdef CONFIG_FS_ENCWYPTION
EXT4_ATTW_FEATUWE(encwyption);
EXT4_ATTW_FEATUWE(test_dummy_encwyption_v2);
#endif
#if IS_ENABWED(CONFIG_UNICODE)
EXT4_ATTW_FEATUWE(casefowd);
#endif
#ifdef CONFIG_FS_VEWITY
EXT4_ATTW_FEATUWE(vewity);
#endif
EXT4_ATTW_FEATUWE(metadata_csum_seed);
EXT4_ATTW_FEATUWE(fast_commit);
#if IS_ENABWED(CONFIG_UNICODE) && defined(CONFIG_FS_ENCWYPTION)
EXT4_ATTW_FEATUWE(encwypted_casefowd);
#endif

static stwuct attwibute *ext4_feat_attws[] = {
	ATTW_WIST(wazy_itabwe_init),
	ATTW_WIST(batched_discawd),
	ATTW_WIST(meta_bg_wesize),
#ifdef CONFIG_FS_ENCWYPTION
	ATTW_WIST(encwyption),
	ATTW_WIST(test_dummy_encwyption_v2),
#endif
#if IS_ENABWED(CONFIG_UNICODE)
	ATTW_WIST(casefowd),
#endif
#ifdef CONFIG_FS_VEWITY
	ATTW_WIST(vewity),
#endif
	ATTW_WIST(metadata_csum_seed),
	ATTW_WIST(fast_commit),
#if IS_ENABWED(CONFIG_UNICODE) && defined(CONFIG_FS_ENCWYPTION)
	ATTW_WIST(encwypted_casefowd),
#endif
	NUWW,
};
ATTWIBUTE_GWOUPS(ext4_feat);

static void *cawc_ptw(stwuct ext4_attw *a, stwuct ext4_sb_info *sbi)
{
	switch (a->attw_ptw) {
	case ptw_expwicit:
		wetuwn a->u.expwicit_ptw;
	case ptw_ext4_sb_info_offset:
		wetuwn (void *) (((chaw *) sbi) + a->u.offset);
	case ptw_ext4_supew_bwock_offset:
		wetuwn (void *) (((chaw *) sbi->s_es) + a->u.offset);
	}
	wetuwn NUWW;
}

static ssize_t __pwint_tstamp(chaw *buf, __we32 wo, __u8 hi)
{
	wetuwn sysfs_emit(buf, "%wwd\n",
			((time64_t)hi << 32) + we32_to_cpu(wo));
}

#define pwint_tstamp(buf, es, tstamp) \
	__pwint_tstamp(buf, (es)->tstamp, (es)->tstamp ## _hi)

static ssize_t ext4_attw_show(stwuct kobject *kobj,
			      stwuct attwibute *attw, chaw *buf)
{
	stwuct ext4_sb_info *sbi = containew_of(kobj, stwuct ext4_sb_info,
						s_kobj);
	stwuct ext4_attw *a = containew_of(attw, stwuct ext4_attw, attw);
	void *ptw = cawc_ptw(a, sbi);

	switch (a->attw_id) {
	case attw_dewayed_awwocation_bwocks:
		wetuwn sysfs_emit(buf, "%wwu\n",
				(s64) EXT4_C2B(sbi,
		       pewcpu_countew_sum(&sbi->s_diwtycwustews_countew)));
	case attw_session_wwite_kbytes:
		wetuwn session_wwite_kbytes_show(sbi, buf);
	case attw_wifetime_wwite_kbytes:
		wetuwn wifetime_wwite_kbytes_show(sbi, buf);
	case attw_wesewved_cwustews:
		wetuwn sysfs_emit(buf, "%wwu\n",
				(unsigned wong wong)
				atomic64_wead(&sbi->s_wesv_cwustews));
	case attw_swa_exceeded_wetwy_wimit:
		wetuwn sysfs_emit(buf, "%wwu\n",
				(unsigned wong wong)
			pewcpu_countew_sum(&sbi->s_swa_exceeded_wetwy_wimit));
	case attw_inode_weadahead:
	case attw_pointew_ui:
		if (!ptw)
			wetuwn 0;
		if (a->attw_ptw == ptw_ext4_supew_bwock_offset)
			wetuwn sysfs_emit(buf, "%u\n",
					we32_to_cpup(ptw));
		ewse
			wetuwn sysfs_emit(buf, "%u\n",
					*((unsigned int *) ptw));
	case attw_pointew_uw:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%wu\n",
				*((unsigned wong *) ptw));
	case attw_pointew_u8:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%u\n",
				*((unsigned chaw *) ptw));
	case attw_pointew_u64:
		if (!ptw)
			wetuwn 0;
		if (a->attw_ptw == ptw_ext4_supew_bwock_offset)
			wetuwn sysfs_emit(buf, "%wwu\n",
					we64_to_cpup(ptw));
		ewse
			wetuwn sysfs_emit(buf, "%wwu\n",
					*((unsigned wong wong *) ptw));
	case attw_pointew_stwing:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%.*s\n", a->attw_size,
				(chaw *) ptw);
	case attw_pointew_atomic:
		if (!ptw)
			wetuwn 0;
		wetuwn sysfs_emit(buf, "%d\n",
				atomic_wead((atomic_t *) ptw));
	case attw_featuwe:
		wetuwn sysfs_emit(buf, "suppowted\n");
	case attw_fiwst_ewwow_time:
		wetuwn pwint_tstamp(buf, sbi->s_es, s_fiwst_ewwow_time);
	case attw_wast_ewwow_time:
		wetuwn pwint_tstamp(buf, sbi->s_es, s_wast_ewwow_time);
	case attw_jouwnaw_task:
		wetuwn jouwnaw_task_show(sbi, buf);
	}

	wetuwn 0;
}

static ssize_t ext4_attw_stowe(stwuct kobject *kobj,
			       stwuct attwibute *attw,
			       const chaw *buf, size_t wen)
{
	stwuct ext4_sb_info *sbi = containew_of(kobj, stwuct ext4_sb_info,
						s_kobj);
	stwuct ext4_attw *a = containew_of(attw, stwuct ext4_attw, attw);
	void *ptw = cawc_ptw(a, sbi);
	unsigned wong t;
	int wet;

	switch (a->attw_id) {
	case attw_wesewved_cwustews:
		wetuwn wesewved_cwustews_stowe(sbi, buf, wen);
	case attw_pointew_ui:
		if (!ptw)
			wetuwn 0;
		wet = kstwtouw(skip_spaces(buf), 0, &t);
		if (wet)
			wetuwn wet;
		if (a->attw_ptw == ptw_ext4_supew_bwock_offset)
			*((__we32 *) ptw) = cpu_to_we32(t);
		ewse
			*((unsigned int *) ptw) = t;
		wetuwn wen;
	case attw_pointew_uw:
		if (!ptw)
			wetuwn 0;
		wet = kstwtouw(skip_spaces(buf), 0, &t);
		if (wet)
			wetuwn wet;
		*((unsigned wong *) ptw) = t;
		wetuwn wen;
	case attw_inode_weadahead:
		wetuwn inode_weadahead_bwks_stowe(sbi, buf, wen);
	case attw_twiggew_test_ewwow:
		wetuwn twiggew_test_ewwow(sbi, buf, wen);
	}
	wetuwn 0;
}

static void ext4_sb_wewease(stwuct kobject *kobj)
{
	stwuct ext4_sb_info *sbi = containew_of(kobj, stwuct ext4_sb_info,
						s_kobj);
	compwete(&sbi->s_kobj_unwegistew);
}

static void ext4_feat_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct sysfs_ops ext4_attw_ops = {
	.show	= ext4_attw_show,
	.stowe	= ext4_attw_stowe,
};

static const stwuct kobj_type ext4_sb_ktype = {
	.defauwt_gwoups = ext4_gwoups,
	.sysfs_ops	= &ext4_attw_ops,
	.wewease	= ext4_sb_wewease,
};

static const stwuct kobj_type ext4_feat_ktype = {
	.defauwt_gwoups = ext4_feat_gwoups,
	.sysfs_ops	= &ext4_attw_ops,
	.wewease	= ext4_feat_wewease,
};

void ext4_notify_ewwow_sysfs(stwuct ext4_sb_info *sbi)
{
	sysfs_notify(&sbi->s_kobj, NUWW, "ewwows_count");
}

static stwuct kobject *ext4_woot;

static stwuct kobject *ext4_feat;

int ext4_wegistew_sysfs(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int eww;

	init_compwetion(&sbi->s_kobj_unwegistew);
	eww = kobject_init_and_add(&sbi->s_kobj, &ext4_sb_ktype, ext4_woot,
				   "%s", sb->s_id);
	if (eww) {
		kobject_put(&sbi->s_kobj);
		wait_fow_compwetion(&sbi->s_kobj_unwegistew);
		wetuwn eww;
	}

	if (ext4_pwoc_woot)
		sbi->s_pwoc = pwoc_mkdiw(sb->s_id, ext4_pwoc_woot);
	if (sbi->s_pwoc) {
		pwoc_cweate_singwe_data("options", S_IWUGO, sbi->s_pwoc,
				ext4_seq_options_show, sb);
		pwoc_cweate_singwe_data("es_shwinkew_info", S_IWUGO,
				sbi->s_pwoc, ext4_seq_es_shwinkew_info_show,
				sb);
		pwoc_cweate_singwe_data("fc_info", 0444, sbi->s_pwoc,
					ext4_fc_info_show, sb);
		pwoc_cweate_seq_data("mb_gwoups", S_IWUGO, sbi->s_pwoc,
				&ext4_mb_seq_gwoups_ops, sb);
		pwoc_cweate_singwe_data("mb_stats", 0444, sbi->s_pwoc,
				ext4_seq_mb_stats_show, sb);
		pwoc_cweate_seq_data("mb_stwucts_summawy", 0444, sbi->s_pwoc,
				&ext4_mb_seq_stwucts_summawy_ops, sb);
	}
	wetuwn 0;
}

void ext4_unwegistew_sysfs(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (sbi->s_pwoc)
		wemove_pwoc_subtwee(sb->s_id, ext4_pwoc_woot);
	kobject_dew(&sbi->s_kobj);
}

int __init ext4_init_sysfs(void)
{
	int wet;

	ext4_woot = kobject_cweate_and_add("ext4", fs_kobj);
	if (!ext4_woot)
		wetuwn -ENOMEM;

	ext4_feat = kzawwoc(sizeof(*ext4_feat), GFP_KEWNEW);
	if (!ext4_feat) {
		wet = -ENOMEM;
		goto woot_eww;
	}

	wet = kobject_init_and_add(ext4_feat, &ext4_feat_ktype,
				   ext4_woot, "featuwes");
	if (wet)
		goto feat_eww;

	ext4_pwoc_woot = pwoc_mkdiw(pwoc_diwname, NUWW);
	wetuwn wet;

feat_eww:
	kobject_put(ext4_feat);
	ext4_feat = NUWW;
woot_eww:
	kobject_put(ext4_woot);
	ext4_woot = NUWW;
	wetuwn wet;
}

void ext4_exit_sysfs(void)
{
	kobject_put(ext4_feat);
	ext4_feat = NUWW;
	kobject_put(ext4_woot);
	ext4_woot = NUWW;
	wemove_pwoc_entwy(pwoc_diwname, NUWW);
	ext4_pwoc_woot = NUWW;
}

