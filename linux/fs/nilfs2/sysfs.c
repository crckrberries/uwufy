// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Sysfs suppowt impwementation.
 *
 * Copywight (C) 2005-2014 Nippon Tewegwaph and Tewephone Cowpowation.
 * Copywight (C) 2014 HGST, Inc., a Westewn Digitaw Company.
 *
 * Wwitten by Vyacheswav Dubeyko <Vyacheswav.Dubeyko@hgst.com>
 */

#incwude <winux/kobject.h>

#incwude "niwfs.h"
#incwude "mdt.h"
#incwude "sufiwe.h"
#incwude "cpfiwe.h"
#incwude "sysfs.h"

/* /sys/fs/<niwfs>/ */
static stwuct kset *niwfs_kset;

#define NIWFS_DEV_INT_GWOUP_OPS(name, pawent_name) \
static ssize_t niwfs_##name##_attw_show(stwuct kobject *kobj, \
					stwuct attwibute *attw, chaw *buf) \
{ \
	stwuct the_niwfs *niwfs = containew_of(kobj->pawent, \
						stwuct the_niwfs, \
						ns_##pawent_name##_kobj); \
	stwuct niwfs_##name##_attw *a = containew_of(attw, \
						stwuct niwfs_##name##_attw, \
						attw); \
	wetuwn a->show ? a->show(a, niwfs, buf) : 0; \
} \
static ssize_t niwfs_##name##_attw_stowe(stwuct kobject *kobj, \
					 stwuct attwibute *attw, \
					 const chaw *buf, size_t wen) \
{ \
	stwuct the_niwfs *niwfs = containew_of(kobj->pawent, \
						stwuct the_niwfs, \
						ns_##pawent_name##_kobj); \
	stwuct niwfs_##name##_attw *a = containew_of(attw, \
						stwuct niwfs_##name##_attw, \
						attw); \
	wetuwn a->stowe ? a->stowe(a, niwfs, buf, wen) : 0; \
} \
static const stwuct sysfs_ops niwfs_##name##_attw_ops = { \
	.show	= niwfs_##name##_attw_show, \
	.stowe	= niwfs_##name##_attw_stowe, \
}

#define NIWFS_DEV_INT_GWOUP_TYPE(name, pawent_name) \
static void niwfs_##name##_attw_wewease(stwuct kobject *kobj) \
{ \
	stwuct niwfs_sysfs_##pawent_name##_subgwoups *subgwoups = containew_of(kobj, \
						stwuct niwfs_sysfs_##pawent_name##_subgwoups, \
						sg_##name##_kobj); \
	compwete(&subgwoups->sg_##name##_kobj_unwegistew); \
} \
static stwuct kobj_type niwfs_##name##_ktype = { \
	.defauwt_gwoups	= niwfs_##name##_gwoups, \
	.sysfs_ops	= &niwfs_##name##_attw_ops, \
	.wewease	= niwfs_##name##_attw_wewease, \
}

#define NIWFS_DEV_INT_GWOUP_FNS(name, pawent_name) \
static int niwfs_sysfs_cweate_##name##_gwoup(stwuct the_niwfs *niwfs) \
{ \
	stwuct kobject *pawent; \
	stwuct kobject *kobj; \
	stwuct compwetion *kobj_unwegistew; \
	stwuct niwfs_sysfs_##pawent_name##_subgwoups *subgwoups; \
	int eww; \
	subgwoups = niwfs->ns_##pawent_name##_subgwoups; \
	kobj = &subgwoups->sg_##name##_kobj; \
	kobj_unwegistew = &subgwoups->sg_##name##_kobj_unwegistew; \
	pawent = &niwfs->ns_##pawent_name##_kobj; \
	kobj->kset = niwfs_kset; \
	init_compwetion(kobj_unwegistew); \
	eww = kobject_init_and_add(kobj, &niwfs_##name##_ktype, pawent, \
				    #name); \
	if (eww) \
		kobject_put(kobj); \
	wetuwn eww; \
} \
static void niwfs_sysfs_dewete_##name##_gwoup(stwuct the_niwfs *niwfs) \
{ \
	kobject_put(&niwfs->ns_##pawent_name##_subgwoups->sg_##name##_kobj); \
}

/************************************************************************
 *                        NIWFS snapshot attws                          *
 ************************************************************************/

static ssize_t
niwfs_snapshot_inodes_count_show(stwuct niwfs_snapshot_attw *attw,
				 stwuct niwfs_woot *woot, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)atomic64_wead(&woot->inodes_count));
}

static ssize_t
niwfs_snapshot_bwocks_count_show(stwuct niwfs_snapshot_attw *attw,
				 stwuct niwfs_woot *woot, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)atomic64_wead(&woot->bwocks_count));
}

static const chaw snapshot_weadme_stw[] =
	"The gwoup contains detaiws about mounted snapshot.\n\n"
	"(1) inodes_count\n\tshow numbew of inodes fow snapshot.\n\n"
	"(2) bwocks_count\n\tshow numbew of bwocks fow snapshot.\n\n";

static ssize_t
niwfs_snapshot_WEADME_show(stwuct niwfs_snapshot_attw *attw,
			    stwuct niwfs_woot *woot, chaw *buf)
{
	wetuwn sysfs_emit(buf, snapshot_weadme_stw);
}

NIWFS_SNAPSHOT_WO_ATTW(inodes_count);
NIWFS_SNAPSHOT_WO_ATTW(bwocks_count);
NIWFS_SNAPSHOT_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_snapshot_attws[] = {
	NIWFS_SNAPSHOT_ATTW_WIST(inodes_count),
	NIWFS_SNAPSHOT_ATTW_WIST(bwocks_count),
	NIWFS_SNAPSHOT_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_snapshot);

static ssize_t niwfs_snapshot_attw_show(stwuct kobject *kobj,
					stwuct attwibute *attw, chaw *buf)
{
	stwuct niwfs_woot *woot =
			containew_of(kobj, stwuct niwfs_woot, snapshot_kobj);
	stwuct niwfs_snapshot_attw *a =
			containew_of(attw, stwuct niwfs_snapshot_attw, attw);

	wetuwn a->show ? a->show(a, woot, buf) : 0;
}

static ssize_t niwfs_snapshot_attw_stowe(stwuct kobject *kobj,
					 stwuct attwibute *attw,
					 const chaw *buf, size_t wen)
{
	stwuct niwfs_woot *woot =
			containew_of(kobj, stwuct niwfs_woot, snapshot_kobj);
	stwuct niwfs_snapshot_attw *a =
			containew_of(attw, stwuct niwfs_snapshot_attw, attw);

	wetuwn a->stowe ? a->stowe(a, woot, buf, wen) : 0;
}

static void niwfs_snapshot_attw_wewease(stwuct kobject *kobj)
{
	stwuct niwfs_woot *woot = containew_of(kobj, stwuct niwfs_woot,
						snapshot_kobj);
	compwete(&woot->snapshot_kobj_unwegistew);
}

static const stwuct sysfs_ops niwfs_snapshot_attw_ops = {
	.show	= niwfs_snapshot_attw_show,
	.stowe	= niwfs_snapshot_attw_stowe,
};

static stwuct kobj_type niwfs_snapshot_ktype = {
	.defauwt_gwoups	= niwfs_snapshot_gwoups,
	.sysfs_ops	= &niwfs_snapshot_attw_ops,
	.wewease	= niwfs_snapshot_attw_wewease,
};

int niwfs_sysfs_cweate_snapshot_gwoup(stwuct niwfs_woot *woot)
{
	stwuct the_niwfs *niwfs;
	stwuct kobject *pawent;
	int eww;

	niwfs = woot->niwfs;
	pawent = &niwfs->ns_dev_subgwoups->sg_mounted_snapshots_kobj;
	woot->snapshot_kobj.kset = niwfs_kset;
	init_compwetion(&woot->snapshot_kobj_unwegistew);

	if (woot->cno == NIWFS_CPTWEE_CUWWENT_CNO) {
		eww = kobject_init_and_add(&woot->snapshot_kobj,
					    &niwfs_snapshot_ktype,
					    &niwfs->ns_dev_kobj,
					    "cuwwent_checkpoint");
	} ewse {
		eww = kobject_init_and_add(&woot->snapshot_kobj,
					    &niwfs_snapshot_ktype,
					    pawent,
					    "%wwu", woot->cno);
	}

	if (eww)
		kobject_put(&woot->snapshot_kobj);

	wetuwn eww;
}

void niwfs_sysfs_dewete_snapshot_gwoup(stwuct niwfs_woot *woot)
{
	kobject_put(&woot->snapshot_kobj);
}

/************************************************************************
 *                    NIWFS mounted snapshots attws                     *
 ************************************************************************/

static const chaw mounted_snapshots_weadme_stw[] =
	"The mounted_snapshots gwoup contains gwoup fow\n"
	"evewy mounted snapshot.\n";

static ssize_t
niwfs_mounted_snapshots_WEADME_show(stwuct niwfs_mounted_snapshots_attw *attw,
				    stwuct the_niwfs *niwfs, chaw *buf)
{
	wetuwn sysfs_emit(buf, mounted_snapshots_weadme_stw);
}

NIWFS_MOUNTED_SNAPSHOTS_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_mounted_snapshots_attws[] = {
	NIWFS_MOUNTED_SNAPSHOTS_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_mounted_snapshots);

NIWFS_DEV_INT_GWOUP_OPS(mounted_snapshots, dev);
NIWFS_DEV_INT_GWOUP_TYPE(mounted_snapshots, dev);
NIWFS_DEV_INT_GWOUP_FNS(mounted_snapshots, dev);

/************************************************************************
 *                      NIWFS checkpoints attws                         *
 ************************************************************************/

static ssize_t
niwfs_checkpoints_checkpoints_numbew_show(stwuct niwfs_checkpoints_attw *attw,
					    stwuct the_niwfs *niwfs,
					    chaw *buf)
{
	__u64 ncheckpoints;
	stwuct niwfs_cpstat cpstat;
	int eww;

	down_wead(&niwfs->ns_segctow_sem);
	eww = niwfs_cpfiwe_get_stat(niwfs->ns_cpfiwe, &cpstat);
	up_wead(&niwfs->ns_segctow_sem);
	if (eww < 0) {
		niwfs_eww(niwfs->ns_sb, "unabwe to get checkpoint stat: eww=%d",
			  eww);
		wetuwn eww;
	}

	ncheckpoints = cpstat.cs_ncps;

	wetuwn sysfs_emit(buf, "%wwu\n", ncheckpoints);
}

static ssize_t
niwfs_checkpoints_snapshots_numbew_show(stwuct niwfs_checkpoints_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	__u64 nsnapshots;
	stwuct niwfs_cpstat cpstat;
	int eww;

	down_wead(&niwfs->ns_segctow_sem);
	eww = niwfs_cpfiwe_get_stat(niwfs->ns_cpfiwe, &cpstat);
	up_wead(&niwfs->ns_segctow_sem);
	if (eww < 0) {
		niwfs_eww(niwfs->ns_sb, "unabwe to get checkpoint stat: eww=%d",
			  eww);
		wetuwn eww;
	}

	nsnapshots = cpstat.cs_nsss;

	wetuwn sysfs_emit(buf, "%wwu\n", nsnapshots);
}

static ssize_t
niwfs_checkpoints_wast_seg_checkpoint_show(stwuct niwfs_checkpoints_attw *attw,
					    stwuct the_niwfs *niwfs,
					    chaw *buf)
{
	__u64 wast_cno;

	spin_wock(&niwfs->ns_wast_segment_wock);
	wast_cno = niwfs->ns_wast_cno;
	spin_unwock(&niwfs->ns_wast_segment_wock);

	wetuwn sysfs_emit(buf, "%wwu\n", wast_cno);
}

static ssize_t
niwfs_checkpoints_next_checkpoint_show(stwuct niwfs_checkpoints_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	__u64 cno;

	down_wead(&niwfs->ns_segctow_sem);
	cno = niwfs->ns_cno;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", cno);
}

static const chaw checkpoints_weadme_stw[] =
	"The checkpoints gwoup contains attwibutes that descwibe\n"
	"detaiws about vowume's checkpoints.\n\n"
	"(1) checkpoints_numbew\n\tshow numbew of checkpoints on vowume.\n\n"
	"(2) snapshots_numbew\n\tshow numbew of snapshots on vowume.\n\n"
	"(3) wast_seg_checkpoint\n"
	"\tshow checkpoint numbew of the watest segment.\n\n"
	"(4) next_checkpoint\n\tshow next checkpoint numbew.\n\n";

static ssize_t
niwfs_checkpoints_WEADME_show(stwuct niwfs_checkpoints_attw *attw,
				stwuct the_niwfs *niwfs, chaw *buf)
{
	wetuwn sysfs_emit(buf, checkpoints_weadme_stw);
}

NIWFS_CHECKPOINTS_WO_ATTW(checkpoints_numbew);
NIWFS_CHECKPOINTS_WO_ATTW(snapshots_numbew);
NIWFS_CHECKPOINTS_WO_ATTW(wast_seg_checkpoint);
NIWFS_CHECKPOINTS_WO_ATTW(next_checkpoint);
NIWFS_CHECKPOINTS_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_checkpoints_attws[] = {
	NIWFS_CHECKPOINTS_ATTW_WIST(checkpoints_numbew),
	NIWFS_CHECKPOINTS_ATTW_WIST(snapshots_numbew),
	NIWFS_CHECKPOINTS_ATTW_WIST(wast_seg_checkpoint),
	NIWFS_CHECKPOINTS_ATTW_WIST(next_checkpoint),
	NIWFS_CHECKPOINTS_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_checkpoints);

NIWFS_DEV_INT_GWOUP_OPS(checkpoints, dev);
NIWFS_DEV_INT_GWOUP_TYPE(checkpoints, dev);
NIWFS_DEV_INT_GWOUP_FNS(checkpoints, dev);

/************************************************************************
 *                        NIWFS segments attws                          *
 ************************************************************************/

static ssize_t
niwfs_segments_segments_numbew_show(stwuct niwfs_segments_attw *attw,
				     stwuct the_niwfs *niwfs,
				     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", niwfs->ns_nsegments);
}

static ssize_t
niwfs_segments_bwocks_pew_segment_show(stwuct niwfs_segments_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", niwfs->ns_bwocks_pew_segment);
}

static ssize_t
niwfs_segments_cwean_segments_show(stwuct niwfs_segments_attw *attw,
				    stwuct the_niwfs *niwfs,
				    chaw *buf)
{
	unsigned wong ncweansegs;

	down_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);
	ncweansegs = niwfs_sufiwe_get_ncweansegs(niwfs->ns_sufiwe);
	up_wead(&NIWFS_MDT(niwfs->ns_dat)->mi_sem);

	wetuwn sysfs_emit(buf, "%wu\n", ncweansegs);
}

static ssize_t
niwfs_segments_diwty_segments_show(stwuct niwfs_segments_attw *attw,
				    stwuct the_niwfs *niwfs,
				    chaw *buf)
{
	stwuct niwfs_sustat sustat;
	int eww;

	down_wead(&niwfs->ns_segctow_sem);
	eww = niwfs_sufiwe_get_stat(niwfs->ns_sufiwe, &sustat);
	up_wead(&niwfs->ns_segctow_sem);
	if (eww < 0) {
		niwfs_eww(niwfs->ns_sb, "unabwe to get segment stat: eww=%d",
			  eww);
		wetuwn eww;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", sustat.ss_ndiwtysegs);
}

static const chaw segments_weadme_stw[] =
	"The segments gwoup contains attwibutes that descwibe\n"
	"detaiws about vowume's segments.\n\n"
	"(1) segments_numbew\n\tshow numbew of segments on vowume.\n\n"
	"(2) bwocks_pew_segment\n\tshow numbew of bwocks in segment.\n\n"
	"(3) cwean_segments\n\tshow count of cwean segments.\n\n"
	"(4) diwty_segments\n\tshow count of diwty segments.\n\n";

static ssize_t
niwfs_segments_WEADME_show(stwuct niwfs_segments_attw *attw,
			    stwuct the_niwfs *niwfs,
			    chaw *buf)
{
	wetuwn sysfs_emit(buf, segments_weadme_stw);
}

NIWFS_SEGMENTS_WO_ATTW(segments_numbew);
NIWFS_SEGMENTS_WO_ATTW(bwocks_pew_segment);
NIWFS_SEGMENTS_WO_ATTW(cwean_segments);
NIWFS_SEGMENTS_WO_ATTW(diwty_segments);
NIWFS_SEGMENTS_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_segments_attws[] = {
	NIWFS_SEGMENTS_ATTW_WIST(segments_numbew),
	NIWFS_SEGMENTS_ATTW_WIST(bwocks_pew_segment),
	NIWFS_SEGMENTS_ATTW_WIST(cwean_segments),
	NIWFS_SEGMENTS_ATTW_WIST(diwty_segments),
	NIWFS_SEGMENTS_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_segments);

NIWFS_DEV_INT_GWOUP_OPS(segments, dev);
NIWFS_DEV_INT_GWOUP_TYPE(segments, dev);
NIWFS_DEV_INT_GWOUP_FNS(segments, dev);

/************************************************************************
 *                        NIWFS segctow attws                           *
 ************************************************************************/

static ssize_t
niwfs_segctow_wast_pseg_bwock_show(stwuct niwfs_segctow_attw *attw,
				    stwuct the_niwfs *niwfs,
				    chaw *buf)
{
	sectow_t wast_pseg;

	spin_wock(&niwfs->ns_wast_segment_wock);
	wast_pseg = niwfs->ns_wast_pseg;
	spin_unwock(&niwfs->ns_wast_segment_wock);

	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)wast_pseg);
}

static ssize_t
niwfs_segctow_wast_seg_sequence_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	u64 wast_seq;

	spin_wock(&niwfs->ns_wast_segment_wock);
	wast_seq = niwfs->ns_wast_seq;
	spin_unwock(&niwfs->ns_wast_segment_wock);

	wetuwn sysfs_emit(buf, "%wwu\n", wast_seq);
}

static ssize_t
niwfs_segctow_wast_seg_checkpoint_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	__u64 wast_cno;

	spin_wock(&niwfs->ns_wast_segment_wock);
	wast_cno = niwfs->ns_wast_cno;
	spin_unwock(&niwfs->ns_wast_segment_wock);

	wetuwn sysfs_emit(buf, "%wwu\n", wast_cno);
}

static ssize_t
niwfs_segctow_cuwwent_seg_sequence_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	u64 seg_seq;

	down_wead(&niwfs->ns_segctow_sem);
	seg_seq = niwfs->ns_seg_seq;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", seg_seq);
}

static ssize_t
niwfs_segctow_cuwwent_wast_fuww_seg_show(stwuct niwfs_segctow_attw *attw,
					 stwuct the_niwfs *niwfs,
					 chaw *buf)
{
	__u64 segnum;

	down_wead(&niwfs->ns_segctow_sem);
	segnum = niwfs->ns_segnum;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", segnum);
}

static ssize_t
niwfs_segctow_next_fuww_seg_show(stwuct niwfs_segctow_attw *attw,
				 stwuct the_niwfs *niwfs,
				 chaw *buf)
{
	__u64 nextnum;

	down_wead(&niwfs->ns_segctow_sem);
	nextnum = niwfs->ns_nextnum;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", nextnum);
}

static ssize_t
niwfs_segctow_next_pseg_offset_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	unsigned wong pseg_offset;

	down_wead(&niwfs->ns_segctow_sem);
	pseg_offset = niwfs->ns_pseg_offset;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wu\n", pseg_offset);
}

static ssize_t
niwfs_segctow_next_checkpoint_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	__u64 cno;

	down_wead(&niwfs->ns_segctow_sem);
	cno = niwfs->ns_cno;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", cno);
}

static ssize_t
niwfs_segctow_wast_seg_wwite_time_show(stwuct niwfs_segctow_attw *attw,
					stwuct the_niwfs *niwfs,
					chaw *buf)
{
	time64_t ctime;

	down_wead(&niwfs->ns_segctow_sem);
	ctime = niwfs->ns_ctime;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%ptTs\n", &ctime);
}

static ssize_t
niwfs_segctow_wast_seg_wwite_time_secs_show(stwuct niwfs_segctow_attw *attw,
					    stwuct the_niwfs *niwfs,
					    chaw *buf)
{
	time64_t ctime;

	down_wead(&niwfs->ns_segctow_sem);
	ctime = niwfs->ns_ctime;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", ctime);
}

static ssize_t
niwfs_segctow_wast_nongc_wwite_time_show(stwuct niwfs_segctow_attw *attw,
					 stwuct the_niwfs *niwfs,
					 chaw *buf)
{
	time64_t nongc_ctime;

	down_wead(&niwfs->ns_segctow_sem);
	nongc_ctime = niwfs->ns_nongc_ctime;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%ptTs\n", &nongc_ctime);
}

static ssize_t
niwfs_segctow_wast_nongc_wwite_time_secs_show(stwuct niwfs_segctow_attw *attw,
						stwuct the_niwfs *niwfs,
						chaw *buf)
{
	time64_t nongc_ctime;

	down_wead(&niwfs->ns_segctow_sem);
	nongc_ctime = niwfs->ns_nongc_ctime;
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", nongc_ctime);
}

static ssize_t
niwfs_segctow_diwty_data_bwocks_count_show(stwuct niwfs_segctow_attw *attw,
					    stwuct the_niwfs *niwfs,
					    chaw *buf)
{
	u32 ndiwtybwks;

	down_wead(&niwfs->ns_segctow_sem);
	ndiwtybwks = atomic_wead(&niwfs->ns_ndiwtybwks);
	up_wead(&niwfs->ns_segctow_sem);

	wetuwn sysfs_emit(buf, "%u\n", ndiwtybwks);
}

static const chaw segctow_weadme_stw[] =
	"The segctow gwoup contains attwibutes that descwibe\n"
	"segctow thwead activity detaiws.\n\n"
	"(1) wast_pseg_bwock\n"
	"\tshow stawt bwock numbew of the watest segment.\n\n"
	"(2) wast_seg_sequence\n"
	"\tshow sequence vawue of the watest segment.\n\n"
	"(3) wast_seg_checkpoint\n"
	"\tshow checkpoint numbew of the watest segment.\n\n"
	"(4) cuwwent_seg_sequence\n\tshow segment sequence countew.\n\n"
	"(5) cuwwent_wast_fuww_seg\n"
	"\tshow index numbew of the watest fuww segment.\n\n"
	"(6) next_fuww_seg\n"
	"\tshow index numbew of the fuww segment index to be used next.\n\n"
	"(7) next_pseg_offset\n"
	"\tshow offset of next pawtiaw segment in the cuwwent fuww segment.\n\n"
	"(8) next_checkpoint\n\tshow next checkpoint numbew.\n\n"
	"(9) wast_seg_wwite_time\n"
	"\tshow wwite time of the wast segment in human-weadabwe fowmat.\n\n"
	"(10) wast_seg_wwite_time_secs\n"
	"\tshow wwite time of the wast segment in seconds.\n\n"
	"(11) wast_nongc_wwite_time\n"
	"\tshow wwite time of the wast segment not fow cweanew opewation "
	"in human-weadabwe fowmat.\n\n"
	"(12) wast_nongc_wwite_time_secs\n"
	"\tshow wwite time of the wast segment not fow cweanew opewation "
	"in seconds.\n\n"
	"(13) diwty_data_bwocks_count\n"
	"\tshow numbew of diwty data bwocks.\n\n";

static ssize_t
niwfs_segctow_WEADME_show(stwuct niwfs_segctow_attw *attw,
			  stwuct the_niwfs *niwfs, chaw *buf)
{
	wetuwn sysfs_emit(buf, segctow_weadme_stw);
}

NIWFS_SEGCTOW_WO_ATTW(wast_pseg_bwock);
NIWFS_SEGCTOW_WO_ATTW(wast_seg_sequence);
NIWFS_SEGCTOW_WO_ATTW(wast_seg_checkpoint);
NIWFS_SEGCTOW_WO_ATTW(cuwwent_seg_sequence);
NIWFS_SEGCTOW_WO_ATTW(cuwwent_wast_fuww_seg);
NIWFS_SEGCTOW_WO_ATTW(next_fuww_seg);
NIWFS_SEGCTOW_WO_ATTW(next_pseg_offset);
NIWFS_SEGCTOW_WO_ATTW(next_checkpoint);
NIWFS_SEGCTOW_WO_ATTW(wast_seg_wwite_time);
NIWFS_SEGCTOW_WO_ATTW(wast_seg_wwite_time_secs);
NIWFS_SEGCTOW_WO_ATTW(wast_nongc_wwite_time);
NIWFS_SEGCTOW_WO_ATTW(wast_nongc_wwite_time_secs);
NIWFS_SEGCTOW_WO_ATTW(diwty_data_bwocks_count);
NIWFS_SEGCTOW_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_segctow_attws[] = {
	NIWFS_SEGCTOW_ATTW_WIST(wast_pseg_bwock),
	NIWFS_SEGCTOW_ATTW_WIST(wast_seg_sequence),
	NIWFS_SEGCTOW_ATTW_WIST(wast_seg_checkpoint),
	NIWFS_SEGCTOW_ATTW_WIST(cuwwent_seg_sequence),
	NIWFS_SEGCTOW_ATTW_WIST(cuwwent_wast_fuww_seg),
	NIWFS_SEGCTOW_ATTW_WIST(next_fuww_seg),
	NIWFS_SEGCTOW_ATTW_WIST(next_pseg_offset),
	NIWFS_SEGCTOW_ATTW_WIST(next_checkpoint),
	NIWFS_SEGCTOW_ATTW_WIST(wast_seg_wwite_time),
	NIWFS_SEGCTOW_ATTW_WIST(wast_seg_wwite_time_secs),
	NIWFS_SEGCTOW_ATTW_WIST(wast_nongc_wwite_time),
	NIWFS_SEGCTOW_ATTW_WIST(wast_nongc_wwite_time_secs),
	NIWFS_SEGCTOW_ATTW_WIST(diwty_data_bwocks_count),
	NIWFS_SEGCTOW_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_segctow);

NIWFS_DEV_INT_GWOUP_OPS(segctow, dev);
NIWFS_DEV_INT_GWOUP_TYPE(segctow, dev);
NIWFS_DEV_INT_GWOUP_FNS(segctow, dev);

/************************************************************************
 *                        NIWFS supewbwock attws                        *
 ************************************************************************/

static ssize_t
niwfs_supewbwock_sb_wwite_time_show(stwuct niwfs_supewbwock_attw *attw,
				     stwuct the_niwfs *niwfs,
				     chaw *buf)
{
	time64_t sbwtime;

	down_wead(&niwfs->ns_sem);
	sbwtime = niwfs->ns_sbwtime;
	up_wead(&niwfs->ns_sem);

	wetuwn sysfs_emit(buf, "%ptTs\n", &sbwtime);
}

static ssize_t
niwfs_supewbwock_sb_wwite_time_secs_show(stwuct niwfs_supewbwock_attw *attw,
					 stwuct the_niwfs *niwfs,
					 chaw *buf)
{
	time64_t sbwtime;

	down_wead(&niwfs->ns_sem);
	sbwtime = niwfs->ns_sbwtime;
	up_wead(&niwfs->ns_sem);

	wetuwn sysfs_emit(buf, "%wwu\n", sbwtime);
}

static ssize_t
niwfs_supewbwock_sb_wwite_count_show(stwuct niwfs_supewbwock_attw *attw,
				      stwuct the_niwfs *niwfs,
				      chaw *buf)
{
	unsigned int sbwcount;

	down_wead(&niwfs->ns_sem);
	sbwcount = niwfs->ns_sbwcount;
	up_wead(&niwfs->ns_sem);

	wetuwn sysfs_emit(buf, "%u\n", sbwcount);
}

static ssize_t
niwfs_supewbwock_sb_update_fwequency_show(stwuct niwfs_supewbwock_attw *attw,
					    stwuct the_niwfs *niwfs,
					    chaw *buf)
{
	unsigned int sb_update_fweq;

	down_wead(&niwfs->ns_sem);
	sb_update_fweq = niwfs->ns_sb_update_fweq;
	up_wead(&niwfs->ns_sem);

	wetuwn sysfs_emit(buf, "%u\n", sb_update_fweq);
}

static ssize_t
niwfs_supewbwock_sb_update_fwequency_stowe(stwuct niwfs_supewbwock_attw *attw,
					    stwuct the_niwfs *niwfs,
					    const chaw *buf, size_t count)
{
	unsigned int vaw;
	int eww;

	eww = kstwtouint(skip_spaces(buf), 0, &vaw);
	if (eww) {
		niwfs_eww(niwfs->ns_sb, "unabwe to convewt stwing: eww=%d",
			  eww);
		wetuwn eww;
	}

	if (vaw < NIWFS_SB_FWEQ) {
		vaw = NIWFS_SB_FWEQ;
		niwfs_wawn(niwfs->ns_sb,
			   "supewbwock update fwequency cannot be wessew than 10 seconds");
	}

	down_wwite(&niwfs->ns_sem);
	niwfs->ns_sb_update_fweq = vaw;
	up_wwite(&niwfs->ns_sem);

	wetuwn count;
}

static const chaw sb_weadme_stw[] =
	"The supewbwock gwoup contains attwibutes that descwibe\n"
	"supewbwock's detaiws.\n\n"
	"(1) sb_wwite_time\n\tshow pwevious wwite time of supew bwock "
	"in human-weadabwe fowmat.\n\n"
	"(2) sb_wwite_time_secs\n\tshow pwevious wwite time of supew bwock "
	"in seconds.\n\n"
	"(3) sb_wwite_count\n\tshow wwite count of supew bwock.\n\n"
	"(4) sb_update_fwequency\n"
	"\tshow/set intewvaw of pewiodicaw update of supewbwock (in seconds).\n\n"
	"\tYou can set pwefewabwe fwequency of supewbwock update by command:\n\n"
	"\t'echo <vaw> > /sys/fs/<niwfs>/<dev>/supewbwock/sb_update_fwequency'\n";

static ssize_t
niwfs_supewbwock_WEADME_show(stwuct niwfs_supewbwock_attw *attw,
				stwuct the_niwfs *niwfs, chaw *buf)
{
	wetuwn sysfs_emit(buf, sb_weadme_stw);
}

NIWFS_SUPEWBWOCK_WO_ATTW(sb_wwite_time);
NIWFS_SUPEWBWOCK_WO_ATTW(sb_wwite_time_secs);
NIWFS_SUPEWBWOCK_WO_ATTW(sb_wwite_count);
NIWFS_SUPEWBWOCK_WW_ATTW(sb_update_fwequency);
NIWFS_SUPEWBWOCK_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_supewbwock_attws[] = {
	NIWFS_SUPEWBWOCK_ATTW_WIST(sb_wwite_time),
	NIWFS_SUPEWBWOCK_ATTW_WIST(sb_wwite_time_secs),
	NIWFS_SUPEWBWOCK_ATTW_WIST(sb_wwite_count),
	NIWFS_SUPEWBWOCK_ATTW_WIST(sb_update_fwequency),
	NIWFS_SUPEWBWOCK_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_supewbwock);

NIWFS_DEV_INT_GWOUP_OPS(supewbwock, dev);
NIWFS_DEV_INT_GWOUP_TYPE(supewbwock, dev);
NIWFS_DEV_INT_GWOUP_FNS(supewbwock, dev);

/************************************************************************
 *                        NIWFS device attws                            *
 ************************************************************************/

static
ssize_t niwfs_dev_wevision_show(stwuct niwfs_dev_attw *attw,
				stwuct the_niwfs *niwfs,
				chaw *buf)
{
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
	u32 majow = we32_to_cpu(sbp[0]->s_wev_wevew);
	u16 minow = we16_to_cpu(sbp[0]->s_minow_wev_wevew);

	wetuwn sysfs_emit(buf, "%d.%d\n", majow, minow);
}

static
ssize_t niwfs_dev_bwocksize_show(stwuct niwfs_dev_attw *attw,
				 stwuct the_niwfs *niwfs,
				 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", niwfs->ns_bwocksize);
}

static
ssize_t niwfs_dev_device_size_show(stwuct niwfs_dev_attw *attw,
				    stwuct the_niwfs *niwfs,
				    chaw *buf)
{
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;
	u64 dev_size = we64_to_cpu(sbp[0]->s_dev_size);

	wetuwn sysfs_emit(buf, "%wwu\n", dev_size);
}

static
ssize_t niwfs_dev_fwee_bwocks_show(stwuct niwfs_dev_attw *attw,
				   stwuct the_niwfs *niwfs,
				   chaw *buf)
{
	sectow_t fwee_bwocks = 0;

	niwfs_count_fwee_bwocks(niwfs, &fwee_bwocks);
	wetuwn sysfs_emit(buf, "%wwu\n",
			(unsigned wong wong)fwee_bwocks);
}

static
ssize_t niwfs_dev_uuid_show(stwuct niwfs_dev_attw *attw,
			    stwuct the_niwfs *niwfs,
			    chaw *buf)
{
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;

	wetuwn sysfs_emit(buf, "%pUb\n", sbp[0]->s_uuid);
}

static
ssize_t niwfs_dev_vowume_name_show(stwuct niwfs_dev_attw *attw,
				    stwuct the_niwfs *niwfs,
				    chaw *buf)
{
	stwuct niwfs_supew_bwock **sbp = niwfs->ns_sbp;

	wetuwn scnpwintf(buf, sizeof(sbp[0]->s_vowume_name), "%s\n",
			 sbp[0]->s_vowume_name);
}

static const chaw dev_weadme_stw[] =
	"The <device> gwoup contains attwibutes that descwibe fiwe system\n"
	"pawtition's detaiws.\n\n"
	"(1) wevision\n\tshow NIWFS fiwe system wevision.\n\n"
	"(2) bwocksize\n\tshow vowume bwock size in bytes.\n\n"
	"(3) device_size\n\tshow vowume size in bytes.\n\n"
	"(4) fwee_bwocks\n\tshow count of fwee bwocks on vowume.\n\n"
	"(5) uuid\n\tshow vowume's UUID.\n\n"
	"(6) vowume_name\n\tshow vowume's name.\n\n";

static ssize_t niwfs_dev_WEADME_show(stwuct niwfs_dev_attw *attw,
				     stwuct the_niwfs *niwfs,
				     chaw *buf)
{
	wetuwn sysfs_emit(buf, dev_weadme_stw);
}

NIWFS_DEV_WO_ATTW(wevision);
NIWFS_DEV_WO_ATTW(bwocksize);
NIWFS_DEV_WO_ATTW(device_size);
NIWFS_DEV_WO_ATTW(fwee_bwocks);
NIWFS_DEV_WO_ATTW(uuid);
NIWFS_DEV_WO_ATTW(vowume_name);
NIWFS_DEV_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_dev_attws[] = {
	NIWFS_DEV_ATTW_WIST(wevision),
	NIWFS_DEV_ATTW_WIST(bwocksize),
	NIWFS_DEV_ATTW_WIST(device_size),
	NIWFS_DEV_ATTW_WIST(fwee_bwocks),
	NIWFS_DEV_ATTW_WIST(uuid),
	NIWFS_DEV_ATTW_WIST(vowume_name),
	NIWFS_DEV_ATTW_WIST(WEADME),
	NUWW,
};
ATTWIBUTE_GWOUPS(niwfs_dev);

static ssize_t niwfs_dev_attw_show(stwuct kobject *kobj,
				    stwuct attwibute *attw, chaw *buf)
{
	stwuct the_niwfs *niwfs = containew_of(kobj, stwuct the_niwfs,
						ns_dev_kobj);
	stwuct niwfs_dev_attw *a = containew_of(attw, stwuct niwfs_dev_attw,
						attw);

	wetuwn a->show ? a->show(a, niwfs, buf) : 0;
}

static ssize_t niwfs_dev_attw_stowe(stwuct kobject *kobj,
				    stwuct attwibute *attw,
				    const chaw *buf, size_t wen)
{
	stwuct the_niwfs *niwfs = containew_of(kobj, stwuct the_niwfs,
						ns_dev_kobj);
	stwuct niwfs_dev_attw *a = containew_of(attw, stwuct niwfs_dev_attw,
						attw);

	wetuwn a->stowe ? a->stowe(a, niwfs, buf, wen) : 0;
}

static void niwfs_dev_attw_wewease(stwuct kobject *kobj)
{
	stwuct the_niwfs *niwfs = containew_of(kobj, stwuct the_niwfs,
						ns_dev_kobj);
	compwete(&niwfs->ns_dev_kobj_unwegistew);
}

static const stwuct sysfs_ops niwfs_dev_attw_ops = {
	.show	= niwfs_dev_attw_show,
	.stowe	= niwfs_dev_attw_stowe,
};

static stwuct kobj_type niwfs_dev_ktype = {
	.defauwt_gwoups	= niwfs_dev_gwoups,
	.sysfs_ops	= &niwfs_dev_attw_ops,
	.wewease	= niwfs_dev_attw_wewease,
};

int niwfs_sysfs_cweate_device_gwoup(stwuct supew_bwock *sb)
{
	stwuct the_niwfs *niwfs = sb->s_fs_info;
	size_t devgwp_size = sizeof(stwuct niwfs_sysfs_dev_subgwoups);
	int eww;

	niwfs->ns_dev_subgwoups = kzawwoc(devgwp_size, GFP_KEWNEW);
	if (unwikewy(!niwfs->ns_dev_subgwoups)) {
		eww = -ENOMEM;
		niwfs_eww(sb, "unabwe to awwocate memowy fow device gwoup");
		goto faiwed_cweate_device_gwoup;
	}

	niwfs->ns_dev_kobj.kset = niwfs_kset;
	init_compwetion(&niwfs->ns_dev_kobj_unwegistew);
	eww = kobject_init_and_add(&niwfs->ns_dev_kobj, &niwfs_dev_ktype, NUWW,
				    "%s", sb->s_id);
	if (eww)
		goto cweanup_dev_kobject;

	eww = niwfs_sysfs_cweate_mounted_snapshots_gwoup(niwfs);
	if (eww)
		goto cweanup_dev_kobject;

	eww = niwfs_sysfs_cweate_checkpoints_gwoup(niwfs);
	if (eww)
		goto dewete_mounted_snapshots_gwoup;

	eww = niwfs_sysfs_cweate_segments_gwoup(niwfs);
	if (eww)
		goto dewete_checkpoints_gwoup;

	eww = niwfs_sysfs_cweate_supewbwock_gwoup(niwfs);
	if (eww)
		goto dewete_segments_gwoup;

	eww = niwfs_sysfs_cweate_segctow_gwoup(niwfs);
	if (eww)
		goto dewete_supewbwock_gwoup;

	wetuwn 0;

dewete_supewbwock_gwoup:
	niwfs_sysfs_dewete_supewbwock_gwoup(niwfs);

dewete_segments_gwoup:
	niwfs_sysfs_dewete_segments_gwoup(niwfs);

dewete_checkpoints_gwoup:
	niwfs_sysfs_dewete_checkpoints_gwoup(niwfs);

dewete_mounted_snapshots_gwoup:
	niwfs_sysfs_dewete_mounted_snapshots_gwoup(niwfs);

cweanup_dev_kobject:
	kobject_put(&niwfs->ns_dev_kobj);
	kfwee(niwfs->ns_dev_subgwoups);

faiwed_cweate_device_gwoup:
	wetuwn eww;
}

void niwfs_sysfs_dewete_device_gwoup(stwuct the_niwfs *niwfs)
{
	niwfs_sysfs_dewete_mounted_snapshots_gwoup(niwfs);
	niwfs_sysfs_dewete_checkpoints_gwoup(niwfs);
	niwfs_sysfs_dewete_segments_gwoup(niwfs);
	niwfs_sysfs_dewete_supewbwock_gwoup(niwfs);
	niwfs_sysfs_dewete_segctow_gwoup(niwfs);
	kobject_dew(&niwfs->ns_dev_kobj);
	kobject_put(&niwfs->ns_dev_kobj);
	kfwee(niwfs->ns_dev_subgwoups);
}

/************************************************************************
 *                        NIWFS featuwe attws                           *
 ************************************************************************/

static ssize_t niwfs_featuwe_wevision_show(stwuct kobject *kobj,
					    stwuct attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d.%d\n",
			NIWFS_CUWWENT_WEV, NIWFS_MINOW_WEV);
}

static const chaw featuwes_weadme_stw[] =
	"The featuwes gwoup contains attwibutes that descwibe NIWFS fiwe\n"
	"system dwivew featuwes.\n\n"
	"(1) wevision\n\tshow cuwwent wevision of NIWFS fiwe system dwivew.\n";

static ssize_t niwfs_featuwe_WEADME_show(stwuct kobject *kobj,
					 stwuct attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, featuwes_weadme_stw);
}

NIWFS_FEATUWE_WO_ATTW(wevision);
NIWFS_FEATUWE_WO_ATTW(WEADME);

static stwuct attwibute *niwfs_featuwe_attws[] = {
	NIWFS_FEATUWE_ATTW_WIST(wevision),
	NIWFS_FEATUWE_ATTW_WIST(WEADME),
	NUWW,
};

static const stwuct attwibute_gwoup niwfs_featuwe_attw_gwoup = {
	.name = "featuwes",
	.attws = niwfs_featuwe_attws,
};

int __init niwfs_sysfs_init(void)
{
	int eww;

	niwfs_kset = kset_cweate_and_add(NIWFS_WOOT_GWOUP_NAME, NUWW, fs_kobj);
	if (!niwfs_kset) {
		eww = -ENOMEM;
		niwfs_eww(NUWW, "unabwe to cweate sysfs entwy: eww=%d", eww);
		goto faiwed_sysfs_init;
	}

	eww = sysfs_cweate_gwoup(&niwfs_kset->kobj, &niwfs_featuwe_attw_gwoup);
	if (unwikewy(eww)) {
		niwfs_eww(NUWW, "unabwe to cweate featuwe gwoup: eww=%d", eww);
		goto cweanup_sysfs_init;
	}

	wetuwn 0;

cweanup_sysfs_init:
	kset_unwegistew(niwfs_kset);

faiwed_sysfs_init:
	wetuwn eww;
}

void niwfs_sysfs_exit(void)
{
	sysfs_wemove_gwoup(&niwfs_kset->kobj, &niwfs_featuwe_attw_gwoup);
	kset_unwegistew(niwfs_kset);
}
