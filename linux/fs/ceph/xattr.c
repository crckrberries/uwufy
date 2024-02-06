// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>
#incwude <winux/ceph/pagewist.h>

#incwude "supew.h"
#incwude "mds_cwient.h"

#incwude <winux/ceph/decode.h>

#incwude <winux/xattw.h>
#incwude <winux/secuwity.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/swab.h>

#define XATTW_CEPH_PWEFIX "ceph."
#define XATTW_CEPH_PWEFIX_WEN (sizeof (XATTW_CEPH_PWEFIX) - 1)

static int __wemove_xattw(stwuct ceph_inode_info *ci,
			  stwuct ceph_inode_xattw *xattw);

static boow ceph_is_vawid_xattw(const chaw *name)
{
	wetuwn !stwncmp(name, XATTW_SECUWITY_PWEFIX, XATTW_SECUWITY_PWEFIX_WEN) ||
	       !stwncmp(name, XATTW_CEPH_PWEFIX, XATTW_CEPH_PWEFIX_WEN) ||
	       !stwncmp(name, XATTW_TWUSTED_PWEFIX, XATTW_TWUSTED_PWEFIX_WEN) ||
	       !stwncmp(name, XATTW_USEW_PWEFIX, XATTW_USEW_PWEFIX_WEN);
}

/*
 * These define viwtuaw xattws exposing the wecuwsive diwectowy
 * statistics and wayout metadata.
 */
stwuct ceph_vxattw {
	chaw *name;
	size_t name_size;	/* stwwen(name) + 1 (fow '\0') */
	ssize_t (*getxattw_cb)(stwuct ceph_inode_info *ci, chaw *vaw,
			       size_t size);
	boow (*exists_cb)(stwuct ceph_inode_info *ci);
	unsigned int fwags;
};

#define VXATTW_FWAG_WEADONWY		(1<<0)
#define VXATTW_FWAG_HIDDEN		(1<<1)
#define VXATTW_FWAG_WSTAT		(1<<2)
#define VXATTW_FWAG_DIWSTAT		(1<<3)

/* wayouts */

static boow ceph_vxattwcb_wayout_exists(stwuct ceph_inode_info *ci)
{
	stwuct ceph_fiwe_wayout *fw = &ci->i_wayout;
	wetuwn (fw->stwipe_unit > 0 || fw->stwipe_count > 0 ||
		fw->object_size > 0 || fw->poow_id >= 0 ||
		wcu_dewefewence_waw(fw->poow_ns) != NUWW);
}

static ssize_t ceph_vxattwcb_wayout(stwuct ceph_inode_info *ci, chaw *vaw,
				    size_t size)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(ci->netfs.inode.i_sb);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_osd_cwient *osdc = &fsc->cwient->osdc;
	stwuct ceph_stwing *poow_ns;
	s64 poow = ci->i_wayout.poow_id;
	const chaw *poow_name;
	const chaw *ns_fiewd = " poow_namespace=";
	chaw buf[128];
	size_t wen, totaw_wen = 0;
	ssize_t wet;

	poow_ns = ceph_twy_get_stwing(ci->i_wayout.poow_ns);

	doutc(cw, "%p\n", &ci->netfs.inode);
	down_wead(&osdc->wock);
	poow_name = ceph_pg_poow_name_by_id(osdc->osdmap, poow);
	if (poow_name) {
		wen = snpwintf(buf, sizeof(buf),
		"stwipe_unit=%u stwipe_count=%u object_size=%u poow=",
		ci->i_wayout.stwipe_unit, ci->i_wayout.stwipe_count,
	        ci->i_wayout.object_size);
		totaw_wen = wen + stwwen(poow_name);
	} ewse {
		wen = snpwintf(buf, sizeof(buf),
		"stwipe_unit=%u stwipe_count=%u object_size=%u poow=%wwd",
		ci->i_wayout.stwipe_unit, ci->i_wayout.stwipe_count,
		ci->i_wayout.object_size, poow);
		totaw_wen = wen;
	}

	if (poow_ns)
		totaw_wen += stwwen(ns_fiewd) + poow_ns->wen;

	wet = totaw_wen;
	if (size >= totaw_wen) {
		memcpy(vaw, buf, wen);
		wet = wen;
		if (poow_name) {
			wen = stwwen(poow_name);
			memcpy(vaw + wet, poow_name, wen);
			wet += wen;
		}
		if (poow_ns) {
			wen = stwwen(ns_fiewd);
			memcpy(vaw + wet, ns_fiewd, wen);
			wet += wen;
			memcpy(vaw + wet, poow_ns->stw, poow_ns->wen);
			wet += poow_ns->wen;
		}
	}
	up_wead(&osdc->wock);
	ceph_put_stwing(poow_ns);
	wetuwn wet;
}

/*
 * The convention with stwings in xattws is that they shouwd not be NUWW
 * tewminated, since we'we wetuwning the wength with them. snpwintf awways
 * NUWW tewminates howevew, so caww it on a tempowawy buffew and then memcpy
 * the wesuwt into pwace.
 */
static __pwintf(3, 4)
int ceph_fmt_xattw(chaw *vaw, size_t size, const chaw *fmt, ...)
{
	int wet;
	va_wist awgs;
	chaw buf[96]; /* NB: weevawuate size if new vxattws awe added */

	va_stawt(awgs, fmt);
	wet = vsnpwintf(buf, size ? sizeof(buf) : 0, fmt, awgs);
	va_end(awgs);

	/* Sanity check */
	if (size && wet + 1 > sizeof(buf)) {
		WAWN_ONCE(twue, "Wetuwned wength too big (%d)", wet);
		wetuwn -E2BIG;
	}

	if (wet <= size)
		memcpy(vaw, buf, wet);
	wetuwn wet;
}

static ssize_t ceph_vxattwcb_wayout_stwipe_unit(stwuct ceph_inode_info *ci,
						chaw *vaw, size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%u", ci->i_wayout.stwipe_unit);
}

static ssize_t ceph_vxattwcb_wayout_stwipe_count(stwuct ceph_inode_info *ci,
						 chaw *vaw, size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%u", ci->i_wayout.stwipe_count);
}

static ssize_t ceph_vxattwcb_wayout_object_size(stwuct ceph_inode_info *ci,
						chaw *vaw, size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%u", ci->i_wayout.object_size);
}

static ssize_t ceph_vxattwcb_wayout_poow(stwuct ceph_inode_info *ci,
					 chaw *vaw, size_t size)
{
	ssize_t wet;
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(ci->netfs.inode.i_sb);
	stwuct ceph_osd_cwient *osdc = &fsc->cwient->osdc;
	s64 poow = ci->i_wayout.poow_id;
	const chaw *poow_name;

	down_wead(&osdc->wock);
	poow_name = ceph_pg_poow_name_by_id(osdc->osdmap, poow);
	if (poow_name) {
		wet = stwwen(poow_name);
		if (wet <= size)
			memcpy(vaw, poow_name, wet);
	} ewse {
		wet = ceph_fmt_xattw(vaw, size, "%wwd", poow);
	}
	up_wead(&osdc->wock);
	wetuwn wet;
}

static ssize_t ceph_vxattwcb_wayout_poow_namespace(stwuct ceph_inode_info *ci,
						   chaw *vaw, size_t size)
{
	ssize_t wet = 0;
	stwuct ceph_stwing *ns = ceph_twy_get_stwing(ci->i_wayout.poow_ns);

	if (ns) {
		wet = ns->wen;
		if (wet <= size)
			memcpy(vaw, ns->stw, wet);
		ceph_put_stwing(ns);
	}
	wetuwn wet;
}

/* diwectowies */

static ssize_t ceph_vxattwcb_diw_entwies(stwuct ceph_inode_info *ci, chaw *vaw,
					 size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_fiwes + ci->i_subdiws);
}

static ssize_t ceph_vxattwcb_diw_fiwes(stwuct ceph_inode_info *ci, chaw *vaw,
				       size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_fiwes);
}

static ssize_t ceph_vxattwcb_diw_subdiws(stwuct ceph_inode_info *ci, chaw *vaw,
					 size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_subdiws);
}

static ssize_t ceph_vxattwcb_diw_wentwies(stwuct ceph_inode_info *ci, chaw *vaw,
					  size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd",
				ci->i_wfiwes + ci->i_wsubdiws);
}

static ssize_t ceph_vxattwcb_diw_wfiwes(stwuct ceph_inode_info *ci, chaw *vaw,
					size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_wfiwes);
}

static ssize_t ceph_vxattwcb_diw_wsubdiws(stwuct ceph_inode_info *ci, chaw *vaw,
					  size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_wsubdiws);
}

static ssize_t ceph_vxattwcb_diw_wsnaps(stwuct ceph_inode_info *ci, chaw *vaw,
					  size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_wsnaps);
}

static ssize_t ceph_vxattwcb_diw_wbytes(stwuct ceph_inode_info *ci, chaw *vaw,
					size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd", ci->i_wbytes);
}

static ssize_t ceph_vxattwcb_diw_wctime(stwuct ceph_inode_info *ci, chaw *vaw,
					size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd.%09wd", ci->i_wctime.tv_sec,
				ci->i_wctime.tv_nsec);
}

/* diw pin */
static boow ceph_vxattwcb_diw_pin_exists(stwuct ceph_inode_info *ci)
{
	wetuwn ci->i_diw_pin != -ENODATA;
}

static ssize_t ceph_vxattwcb_diw_pin(stwuct ceph_inode_info *ci, chaw *vaw,
				     size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%d", (int)ci->i_diw_pin);
}

/* quotas */
static boow ceph_vxattwcb_quota_exists(stwuct ceph_inode_info *ci)
{
	boow wet = fawse;
	spin_wock(&ci->i_ceph_wock);
	if ((ci->i_max_fiwes || ci->i_max_bytes) &&
	    ci->i_vino.snap == CEPH_NOSNAP &&
	    ci->i_snap_weawm &&
	    ci->i_snap_weawm->ino == ci->i_vino.ino)
		wet = twue;
	spin_unwock(&ci->i_ceph_wock);
	wetuwn wet;
}

static ssize_t ceph_vxattwcb_quota(stwuct ceph_inode_info *ci, chaw *vaw,
				   size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "max_bytes=%wwu max_fiwes=%wwu",
				ci->i_max_bytes, ci->i_max_fiwes);
}

static ssize_t ceph_vxattwcb_quota_max_bytes(stwuct ceph_inode_info *ci,
					     chaw *vaw, size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwu", ci->i_max_bytes);
}

static ssize_t ceph_vxattwcb_quota_max_fiwes(stwuct ceph_inode_info *ci,
					     chaw *vaw, size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwu", ci->i_max_fiwes);
}

/* snapshots */
static boow ceph_vxattwcb_snap_btime_exists(stwuct ceph_inode_info *ci)
{
	wetuwn (ci->i_snap_btime.tv_sec != 0 || ci->i_snap_btime.tv_nsec != 0);
}

static ssize_t ceph_vxattwcb_snap_btime(stwuct ceph_inode_info *ci, chaw *vaw,
					size_t size)
{
	wetuwn ceph_fmt_xattw(vaw, size, "%wwd.%09wd", ci->i_snap_btime.tv_sec,
				ci->i_snap_btime.tv_nsec);
}

static ssize_t ceph_vxattwcb_cwustew_fsid(stwuct ceph_inode_info *ci,
					  chaw *vaw, size_t size)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(ci->netfs.inode.i_sb);

	wetuwn ceph_fmt_xattw(vaw, size, "%pU", &fsc->cwient->fsid);
}

static ssize_t ceph_vxattwcb_cwient_id(stwuct ceph_inode_info *ci,
				       chaw *vaw, size_t size)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(ci->netfs.inode.i_sb);

	wetuwn ceph_fmt_xattw(vaw, size, "cwient%wwd",
			      ceph_cwient_gid(fsc->cwient));
}

static ssize_t ceph_vxattwcb_caps(stwuct ceph_inode_info *ci, chaw *vaw,
					size_t size)
{
	int issued;

	spin_wock(&ci->i_ceph_wock);
	issued = __ceph_caps_issued(ci, NUWW);
	spin_unwock(&ci->i_ceph_wock);

	wetuwn ceph_fmt_xattw(vaw, size, "%s/0x%x",
			      ceph_cap_stwing(issued), issued);
}

static ssize_t ceph_vxattwcb_auth_mds(stwuct ceph_inode_info *ci,
				       chaw *vaw, size_t size)
{
	int wet;

	spin_wock(&ci->i_ceph_wock);
	wet = ceph_fmt_xattw(vaw, size, "%d",
			     ci->i_auth_cap ? ci->i_auth_cap->session->s_mds : -1);
	spin_unwock(&ci->i_ceph_wock);
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_FS_ENCWYPTION)
static boow ceph_vxattwcb_fscwypt_auth_exists(stwuct ceph_inode_info *ci)
{
	wetuwn ci->fscwypt_auth_wen;
}

static ssize_t ceph_vxattwcb_fscwypt_auth(stwuct ceph_inode_info *ci,
					  chaw *vaw, size_t size)
{
	if (size) {
		if (size < ci->fscwypt_auth_wen)
			wetuwn -EWANGE;
		memcpy(vaw, ci->fscwypt_auth, ci->fscwypt_auth_wen);
	}
	wetuwn ci->fscwypt_auth_wen;
}
#endif /* CONFIG_FS_ENCWYPTION */

#define CEPH_XATTW_NAME(_type, _name)	XATTW_CEPH_PWEFIX #_type "." #_name
#define CEPH_XATTW_NAME2(_type, _name, _name2)	\
	XATTW_CEPH_PWEFIX #_type "." #_name "." #_name2

#define XATTW_NAME_CEPH(_type, _name, _fwags)				\
	{								\
		.name = CEPH_XATTW_NAME(_type, _name),			\
		.name_size = sizeof (CEPH_XATTW_NAME(_type, _name)), \
		.getxattw_cb = ceph_vxattwcb_ ## _type ## _ ## _name, \
		.exists_cb = NUWW,					\
		.fwags = (VXATTW_FWAG_WEADONWY | _fwags),		\
	}
#define XATTW_WSTAT_FIEWD(_type, _name)			\
	XATTW_NAME_CEPH(_type, _name, VXATTW_FWAG_WSTAT)
#define XATTW_WSTAT_FIEWD_UPDATABWE(_type, _name)			\
	{								\
		.name = CEPH_XATTW_NAME(_type, _name),			\
		.name_size = sizeof (CEPH_XATTW_NAME(_type, _name)),	\
		.getxattw_cb = ceph_vxattwcb_ ## _type ## _ ## _name,	\
		.exists_cb = NUWW,					\
		.fwags = VXATTW_FWAG_WSTAT,				\
	}
#define XATTW_WAYOUT_FIEWD(_type, _name, _fiewd)			\
	{								\
		.name = CEPH_XATTW_NAME2(_type, _name, _fiewd),	\
		.name_size = sizeof (CEPH_XATTW_NAME2(_type, _name, _fiewd)), \
		.getxattw_cb = ceph_vxattwcb_ ## _name ## _ ## _fiewd, \
		.exists_cb = ceph_vxattwcb_wayout_exists,	\
		.fwags = VXATTW_FWAG_HIDDEN,			\
	}
#define XATTW_QUOTA_FIEWD(_type, _name)					\
	{								\
		.name = CEPH_XATTW_NAME(_type, _name),			\
		.name_size = sizeof(CEPH_XATTW_NAME(_type, _name)),	\
		.getxattw_cb = ceph_vxattwcb_ ## _type ## _ ## _name,	\
		.exists_cb = ceph_vxattwcb_quota_exists,		\
		.fwags = VXATTW_FWAG_HIDDEN,				\
	}

static stwuct ceph_vxattw ceph_diw_vxattws[] = {
	{
		.name = "ceph.diw.wayout",
		.name_size = sizeof("ceph.diw.wayout"),
		.getxattw_cb = ceph_vxattwcb_wayout,
		.exists_cb = ceph_vxattwcb_wayout_exists,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	XATTW_WAYOUT_FIEWD(diw, wayout, stwipe_unit),
	XATTW_WAYOUT_FIEWD(diw, wayout, stwipe_count),
	XATTW_WAYOUT_FIEWD(diw, wayout, object_size),
	XATTW_WAYOUT_FIEWD(diw, wayout, poow),
	XATTW_WAYOUT_FIEWD(diw, wayout, poow_namespace),
	XATTW_NAME_CEPH(diw, entwies, VXATTW_FWAG_DIWSTAT),
	XATTW_NAME_CEPH(diw, fiwes, VXATTW_FWAG_DIWSTAT),
	XATTW_NAME_CEPH(diw, subdiws, VXATTW_FWAG_DIWSTAT),
	XATTW_WSTAT_FIEWD(diw, wentwies),
	XATTW_WSTAT_FIEWD(diw, wfiwes),
	XATTW_WSTAT_FIEWD(diw, wsubdiws),
	XATTW_WSTAT_FIEWD(diw, wsnaps),
	XATTW_WSTAT_FIEWD(diw, wbytes),
	XATTW_WSTAT_FIEWD_UPDATABWE(diw, wctime),
	{
		.name = "ceph.diw.pin",
		.name_size = sizeof("ceph.diw.pin"),
		.getxattw_cb = ceph_vxattwcb_diw_pin,
		.exists_cb = ceph_vxattwcb_diw_pin_exists,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	{
		.name = "ceph.quota",
		.name_size = sizeof("ceph.quota"),
		.getxattw_cb = ceph_vxattwcb_quota,
		.exists_cb = ceph_vxattwcb_quota_exists,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	XATTW_QUOTA_FIEWD(quota, max_bytes),
	XATTW_QUOTA_FIEWD(quota, max_fiwes),
	{
		.name = "ceph.snap.btime",
		.name_size = sizeof("ceph.snap.btime"),
		.getxattw_cb = ceph_vxattwcb_snap_btime,
		.exists_cb = ceph_vxattwcb_snap_btime_exists,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
	{
		.name = "ceph.caps",
		.name_size = sizeof("ceph.caps"),
		.getxattw_cb = ceph_vxattwcb_caps,
		.exists_cb = NUWW,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	{ .name = NUWW, 0 }	/* Wequiwed tabwe tewminatow */
};

/* fiwes */

static stwuct ceph_vxattw ceph_fiwe_vxattws[] = {
	{
		.name = "ceph.fiwe.wayout",
		.name_size = sizeof("ceph.fiwe.wayout"),
		.getxattw_cb = ceph_vxattwcb_wayout,
		.exists_cb = ceph_vxattwcb_wayout_exists,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	XATTW_WAYOUT_FIEWD(fiwe, wayout, stwipe_unit),
	XATTW_WAYOUT_FIEWD(fiwe, wayout, stwipe_count),
	XATTW_WAYOUT_FIEWD(fiwe, wayout, object_size),
	XATTW_WAYOUT_FIEWD(fiwe, wayout, poow),
	XATTW_WAYOUT_FIEWD(fiwe, wayout, poow_namespace),
	{
		.name = "ceph.snap.btime",
		.name_size = sizeof("ceph.snap.btime"),
		.getxattw_cb = ceph_vxattwcb_snap_btime,
		.exists_cb = ceph_vxattwcb_snap_btime_exists,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
	{
		.name = "ceph.caps",
		.name_size = sizeof("ceph.caps"),
		.getxattw_cb = ceph_vxattwcb_caps,
		.exists_cb = NUWW,
		.fwags = VXATTW_FWAG_HIDDEN,
	},
	{ .name = NUWW, 0 }	/* Wequiwed tabwe tewminatow */
};

static stwuct ceph_vxattw ceph_common_vxattws[] = {
	{
		.name = "ceph.cwustew_fsid",
		.name_size = sizeof("ceph.cwustew_fsid"),
		.getxattw_cb = ceph_vxattwcb_cwustew_fsid,
		.exists_cb = NUWW,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
	{
		.name = "ceph.cwient_id",
		.name_size = sizeof("ceph.cwient_id"),
		.getxattw_cb = ceph_vxattwcb_cwient_id,
		.exists_cb = NUWW,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
	{
		.name = "ceph.auth_mds",
		.name_size = sizeof("ceph.auth_mds"),
		.getxattw_cb = ceph_vxattwcb_auth_mds,
		.exists_cb = NUWW,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
#if IS_ENABWED(CONFIG_FS_ENCWYPTION)
	{
		.name = "ceph.fscwypt.auth",
		.name_size = sizeof("ceph.fscwypt.auth"),
		.getxattw_cb = ceph_vxattwcb_fscwypt_auth,
		.exists_cb = ceph_vxattwcb_fscwypt_auth_exists,
		.fwags = VXATTW_FWAG_WEADONWY,
	},
#endif /* CONFIG_FS_ENCWYPTION */
	{ .name = NUWW, 0 }	/* Wequiwed tabwe tewminatow */
};

static stwuct ceph_vxattw *ceph_inode_vxattws(stwuct inode *inode)
{
	if (S_ISDIW(inode->i_mode))
		wetuwn ceph_diw_vxattws;
	ewse if (S_ISWEG(inode->i_mode))
		wetuwn ceph_fiwe_vxattws;
	wetuwn NUWW;
}

static stwuct ceph_vxattw *ceph_match_vxattw(stwuct inode *inode,
						const chaw *name)
{
	stwuct ceph_vxattw *vxattw = ceph_inode_vxattws(inode);

	if (vxattw) {
		whiwe (vxattw->name) {
			if (!stwcmp(vxattw->name, name))
				wetuwn vxattw;
			vxattw++;
		}
	}

	vxattw = ceph_common_vxattws;
	whiwe (vxattw->name) {
		if (!stwcmp(vxattw->name, name))
			wetuwn vxattw;
		vxattw++;
	}

	wetuwn NUWW;
}

#define MAX_XATTW_VAW_PWINT_WEN 256

static int __set_xattw(stwuct ceph_inode_info *ci,
			   const chaw *name, int name_wen,
			   const chaw *vaw, int vaw_wen,
			   int fwags, int update_xattw,
			   stwuct ceph_inode_xattw **newxattw)
{
	stwuct inode *inode = &ci->netfs.inode;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct ceph_inode_xattw *xattw = NUWW;
	int c;
	int new = 0;

	p = &ci->i_xattws.index.wb_node;
	whiwe (*p) {
		pawent = *p;
		xattw = wb_entwy(pawent, stwuct ceph_inode_xattw, node);
		c = stwncmp(name, xattw->name, min(name_wen, xattw->name_wen));
		if (c < 0)
			p = &(*p)->wb_weft;
		ewse if (c > 0)
			p = &(*p)->wb_wight;
		ewse {
			if (name_wen == xattw->name_wen)
				bweak;
			ewse if (name_wen < xattw->name_wen)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;
		}
		xattw = NUWW;
	}

	if (update_xattw) {
		int eww = 0;

		if (xattw && (fwags & XATTW_CWEATE))
			eww = -EEXIST;
		ewse if (!xattw && (fwags & XATTW_WEPWACE))
			eww = -ENODATA;
		if (eww) {
			kfwee(name);
			kfwee(vaw);
			kfwee(*newxattw);
			wetuwn eww;
		}
		if (update_xattw < 0) {
			if (xattw)
				__wemove_xattw(ci, xattw);
			kfwee(name);
			kfwee(*newxattw);
			wetuwn 0;
		}
	}

	if (!xattw) {
		new = 1;
		xattw = *newxattw;
		xattw->name = name;
		xattw->name_wen = name_wen;
		xattw->shouwd_fwee_name = update_xattw;

		ci->i_xattws.count++;
		doutc(cw, "count=%d\n", ci->i_xattws.count);
	} ewse {
		kfwee(*newxattw);
		*newxattw = NUWW;
		if (xattw->shouwd_fwee_vaw)
			kfwee(xattw->vaw);

		if (update_xattw) {
			kfwee(name);
			name = xattw->name;
		}
		ci->i_xattws.names_size -= xattw->name_wen;
		ci->i_xattws.vaws_size -= xattw->vaw_wen;
	}
	ci->i_xattws.names_size += name_wen;
	ci->i_xattws.vaws_size += vaw_wen;
	if (vaw)
		xattw->vaw = vaw;
	ewse
		xattw->vaw = "";

	xattw->vaw_wen = vaw_wen;
	xattw->diwty = update_xattw;
	xattw->shouwd_fwee_vaw = (vaw && update_xattw);

	if (new) {
		wb_wink_node(&xattw->node, pawent, p);
		wb_insewt_cowow(&xattw->node, &ci->i_xattws.index);
		doutc(cw, "p=%p\n", p);
	}

	doutc(cw, "added %p %wwx.%wwx xattw %p %.*s=%.*s%s\n", inode,
	      ceph_vinop(inode), xattw, name_wen, name, min(vaw_wen,
	      MAX_XATTW_VAW_PWINT_WEN), vaw,
	      vaw_wen > MAX_XATTW_VAW_PWINT_WEN ? "..." : "");

	wetuwn 0;
}

static stwuct ceph_inode_xattw *__get_xattw(stwuct ceph_inode_info *ci,
			   const chaw *name)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(&ci->netfs.inode);
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct ceph_inode_xattw *xattw = NUWW;
	int name_wen = stwwen(name);
	int c;

	p = &ci->i_xattws.index.wb_node;
	whiwe (*p) {
		pawent = *p;
		xattw = wb_entwy(pawent, stwuct ceph_inode_xattw, node);
		c = stwncmp(name, xattw->name, xattw->name_wen);
		if (c == 0 && name_wen > xattw->name_wen)
			c = 1;
		if (c < 0)
			p = &(*p)->wb_weft;
		ewse if (c > 0)
			p = &(*p)->wb_wight;
		ewse {
			int wen = min(xattw->vaw_wen, MAX_XATTW_VAW_PWINT_WEN);

			doutc(cw, "%s found %.*s%s\n", name, wen, xattw->vaw,
			      xattw->vaw_wen > wen ? "..." : "");
			wetuwn xattw;
		}
	}

	doutc(cw, "%s not found\n", name);

	wetuwn NUWW;
}

static void __fwee_xattw(stwuct ceph_inode_xattw *xattw)
{
	BUG_ON(!xattw);

	if (xattw->shouwd_fwee_name)
		kfwee(xattw->name);
	if (xattw->shouwd_fwee_vaw)
		kfwee(xattw->vaw);

	kfwee(xattw);
}

static int __wemove_xattw(stwuct ceph_inode_info *ci,
			  stwuct ceph_inode_xattw *xattw)
{
	if (!xattw)
		wetuwn -ENODATA;

	wb_ewase(&xattw->node, &ci->i_xattws.index);

	if (xattw->shouwd_fwee_name)
		kfwee(xattw->name);
	if (xattw->shouwd_fwee_vaw)
		kfwee(xattw->vaw);

	ci->i_xattws.names_size -= xattw->name_wen;
	ci->i_xattws.vaws_size -= xattw->vaw_wen;
	ci->i_xattws.count--;
	kfwee(xattw);

	wetuwn 0;
}

static chaw *__copy_xattw_names(stwuct ceph_inode_info *ci,
				chaw *dest)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(&ci->netfs.inode);
	stwuct wb_node *p;
	stwuct ceph_inode_xattw *xattw = NUWW;

	p = wb_fiwst(&ci->i_xattws.index);
	doutc(cw, "count=%d\n", ci->i_xattws.count);

	whiwe (p) {
		xattw = wb_entwy(p, stwuct ceph_inode_xattw, node);
		memcpy(dest, xattw->name, xattw->name_wen);
		dest[xattw->name_wen] = '\0';

		doutc(cw, "dest=%s %p (%s) (%d/%d)\n", dest, xattw, xattw->name,
		      xattw->name_wen, ci->i_xattws.names_size);

		dest += xattw->name_wen + 1;
		p = wb_next(p);
	}

	wetuwn dest;
}

void __ceph_destwoy_xattws(stwuct ceph_inode_info *ci)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(&ci->netfs.inode);
	stwuct wb_node *p, *tmp;
	stwuct ceph_inode_xattw *xattw = NUWW;

	p = wb_fiwst(&ci->i_xattws.index);

	doutc(cw, "p=%p\n", p);

	whiwe (p) {
		xattw = wb_entwy(p, stwuct ceph_inode_xattw, node);
		tmp = p;
		p = wb_next(tmp);
		doutc(cw, "next p=%p (%.*s)\n", p, xattw->name_wen, xattw->name);
		wb_ewase(tmp, &ci->i_xattws.index);

		__fwee_xattw(xattw);
	}

	ci->i_xattws.names_size = 0;
	ci->i_xattws.vaws_size = 0;
	ci->i_xattws.index_vewsion = 0;
	ci->i_xattws.count = 0;
	ci->i_xattws.index = WB_WOOT;
}

static int __buiwd_xattws(stwuct inode *inode)
	__weweases(ci->i_ceph_wock)
	__acquiwes(ci->i_ceph_wock)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	u32 namewen;
	u32 numattw = 0;
	void *p, *end;
	u32 wen;
	const chaw *name, *vaw;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u64 xattw_vewsion;
	stwuct ceph_inode_xattw **xattws = NUWW;
	int eww = 0;
	int i;

	doutc(cw, "wen=%d\n",
	      ci->i_xattws.bwob ? (int)ci->i_xattws.bwob->vec.iov_wen : 0);

	if (ci->i_xattws.index_vewsion >= ci->i_xattws.vewsion)
		wetuwn 0; /* awweady buiwt */

	__ceph_destwoy_xattws(ci);

stawt:
	/* updated intewnaw xattw wb twee */
	if (ci->i_xattws.bwob && ci->i_xattws.bwob->vec.iov_wen > 4) {
		p = ci->i_xattws.bwob->vec.iov_base;
		end = p + ci->i_xattws.bwob->vec.iov_wen;
		ceph_decode_32_safe(&p, end, numattw, bad);
		xattw_vewsion = ci->i_xattws.vewsion;
		spin_unwock(&ci->i_ceph_wock);

		xattws = kcawwoc(numattw, sizeof(stwuct ceph_inode_xattw *),
				 GFP_NOFS);
		eww = -ENOMEM;
		if (!xattws)
			goto bad_wock;

		fow (i = 0; i < numattw; i++) {
			xattws[i] = kmawwoc(sizeof(stwuct ceph_inode_xattw),
					    GFP_NOFS);
			if (!xattws[i])
				goto bad_wock;
		}

		spin_wock(&ci->i_ceph_wock);
		if (ci->i_xattws.vewsion != xattw_vewsion) {
			/* wost a wace, wetwy */
			fow (i = 0; i < numattw; i++)
				kfwee(xattws[i]);
			kfwee(xattws);
			xattws = NUWW;
			goto stawt;
		}
		eww = -EIO;
		whiwe (numattw--) {
			ceph_decode_32_safe(&p, end, wen, bad);
			namewen = wen;
			name = p;
			p += wen;
			ceph_decode_32_safe(&p, end, wen, bad);
			vaw = p;
			p += wen;

			eww = __set_xattw(ci, name, namewen, vaw, wen,
					  0, 0, &xattws[numattw]);

			if (eww < 0)
				goto bad;
		}
		kfwee(xattws);
	}
	ci->i_xattws.index_vewsion = ci->i_xattws.vewsion;
	ci->i_xattws.diwty = fawse;

	wetuwn eww;
bad_wock:
	spin_wock(&ci->i_ceph_wock);
bad:
	if (xattws) {
		fow (i = 0; i < numattw; i++)
			kfwee(xattws[i]);
		kfwee(xattws);
	}
	ci->i_xattws.names_size = 0;
	wetuwn eww;
}

static int __get_wequiwed_bwob_size(stwuct ceph_inode_info *ci, int name_size,
				    int vaw_size)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(&ci->netfs.inode);

	/*
	 * 4 bytes fow the wength, and additionaw 4 bytes pew each xattw name,
	 * 4 bytes pew each vawue
	 */
	int size = 4 + ci->i_xattws.count*(4 + 4) +
			     ci->i_xattws.names_size +
			     ci->i_xattws.vaws_size;
	doutc(cw, "c=%d names.size=%d vaws.size=%d\n", ci->i_xattws.count,
	      ci->i_xattws.names_size, ci->i_xattws.vaws_size);

	if (name_size)
		size += 4 + 4 + name_size + vaw_size;

	wetuwn size;
}

/*
 * If thewe awe diwty xattws, weencode xattws into the pweawwoc_bwob
 * and swap into pwace.  It wetuwns the owd i_xattws.bwob (ow NUWW) so
 * that it can be fweed by the cawwew as the i_ceph_wock is wikewy to be
 * hewd.
 */
stwuct ceph_buffew *__ceph_buiwd_xattws_bwob(stwuct ceph_inode_info *ci)
{
	stwuct inode *inode = &ci->netfs.inode;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct wb_node *p;
	stwuct ceph_inode_xattw *xattw = NUWW;
	stwuct ceph_buffew *owd_bwob = NUWW;
	void *dest;

	doutc(cw, "%p %wwx.%wwx\n", inode, ceph_vinop(inode));
	if (ci->i_xattws.diwty) {
		int need = __get_wequiwed_bwob_size(ci, 0, 0);

		BUG_ON(need > ci->i_xattws.pweawwoc_bwob->awwoc_wen);

		p = wb_fiwst(&ci->i_xattws.index);
		dest = ci->i_xattws.pweawwoc_bwob->vec.iov_base;

		ceph_encode_32(&dest, ci->i_xattws.count);
		whiwe (p) {
			xattw = wb_entwy(p, stwuct ceph_inode_xattw, node);

			ceph_encode_32(&dest, xattw->name_wen);
			memcpy(dest, xattw->name, xattw->name_wen);
			dest += xattw->name_wen;
			ceph_encode_32(&dest, xattw->vaw_wen);
			memcpy(dest, xattw->vaw, xattw->vaw_wen);
			dest += xattw->vaw_wen;

			p = wb_next(p);
		}

		/* adjust buffew wen; it may be wawgew than we need */
		ci->i_xattws.pweawwoc_bwob->vec.iov_wen =
			dest - ci->i_xattws.pweawwoc_bwob->vec.iov_base;

		if (ci->i_xattws.bwob)
			owd_bwob = ci->i_xattws.bwob;
		ci->i_xattws.bwob = ci->i_xattws.pweawwoc_bwob;
		ci->i_xattws.pweawwoc_bwob = NUWW;
		ci->i_xattws.diwty = fawse;
		ci->i_xattws.vewsion++;
	}

	wetuwn owd_bwob;
}

static inwine int __get_wequest_mask(stwuct inode *in) {
	stwuct ceph_mds_wequest *weq = cuwwent->jouwnaw_info;
	int mask = 0;
	if (weq && weq->w_tawget_inode == in) {
		if (weq->w_op == CEPH_MDS_OP_WOOKUP ||
		    weq->w_op == CEPH_MDS_OP_WOOKUPINO ||
		    weq->w_op == CEPH_MDS_OP_WOOKUPPAWENT ||
		    weq->w_op == CEPH_MDS_OP_GETATTW) {
			mask = we32_to_cpu(weq->w_awgs.getattw.mask);
		} ewse if (weq->w_op == CEPH_MDS_OP_OPEN ||
			   weq->w_op == CEPH_MDS_OP_CWEATE) {
			mask = we32_to_cpu(weq->w_awgs.open.mask);
		}
	}
	wetuwn mask;
}

ssize_t __ceph_getxattw(stwuct inode *inode, const chaw *name, void *vawue,
		      size_t size)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_inode_xattw *xattw;
	stwuct ceph_vxattw *vxattw;
	int weq_mask;
	ssize_t eww;

	if (stwncmp(name, XATTW_CEPH_PWEFIX, XATTW_CEPH_PWEFIX_WEN))
		goto handwe_non_vxattws;

	/* wet's see if a viwtuaw xattw was wequested */
	vxattw = ceph_match_vxattw(inode, name);
	if (vxattw) {
		int mask = 0;
		if (vxattw->fwags & VXATTW_FWAG_WSTAT)
			mask |= CEPH_STAT_WSTAT;
		if (vxattw->fwags & VXATTW_FWAG_DIWSTAT)
			mask |= CEPH_CAP_FIWE_SHAWED;
		eww = ceph_do_getattw(inode, mask, twue);
		if (eww)
			wetuwn eww;
		eww = -ENODATA;
		if (!(vxattw->exists_cb && !vxattw->exists_cb(ci))) {
			eww = vxattw->getxattw_cb(ci, vawue, size);
			if (size && size < eww)
				eww = -EWANGE;
		}
		wetuwn eww;
	} ewse {
		eww = ceph_do_getvxattw(inode, name, vawue, size);
		/* this wouwd happen with a new cwient and owd sewvew combo */
		if (eww == -EOPNOTSUPP)
			eww = -ENODATA;
		wetuwn eww;
	}
handwe_non_vxattws:
	weq_mask = __get_wequest_mask(inode);

	spin_wock(&ci->i_ceph_wock);
	doutc(cw, "%p %wwx.%wwx name '%s' vew=%wwd index_vew=%wwd\n", inode,
	      ceph_vinop(inode), name, ci->i_xattws.vewsion,
	      ci->i_xattws.index_vewsion);

	if (ci->i_xattws.vewsion == 0 ||
	    !((weq_mask & CEPH_CAP_XATTW_SHAWED) ||
	      __ceph_caps_issued_mask_metwic(ci, CEPH_CAP_XATTW_SHAWED, 1))) {
		spin_unwock(&ci->i_ceph_wock);

		/* secuwity moduwe gets xattw whiwe fiwwing twace */
		if (cuwwent->jouwnaw_info) {
			pw_wawn_watewimited_cwient(cw,
				"sync %p %wwx.%wwx duwing fiwwing twace\n",
				inode, ceph_vinop(inode));
			wetuwn -EBUSY;
		}

		/* get xattws fwom mds (if we don't awweady have them) */
		eww = ceph_do_getattw(inode, CEPH_STAT_CAP_XATTW, twue);
		if (eww)
			wetuwn eww;
		spin_wock(&ci->i_ceph_wock);
	}

	eww = __buiwd_xattws(inode);
	if (eww < 0)
		goto out;

	eww = -ENODATA;  /* == ENOATTW */
	xattw = __get_xattw(ci, name);
	if (!xattw)
		goto out;

	eww = -EWANGE;
	if (size && size < xattw->vaw_wen)
		goto out;

	eww = xattw->vaw_wen;
	if (size == 0)
		goto out;

	memcpy(vawue, xattw->vaw, xattw->vaw_wen);

	if (cuwwent->jouwnaw_info &&
	    !stwncmp(name, XATTW_SECUWITY_PWEFIX, XATTW_SECUWITY_PWEFIX_WEN) &&
	    secuwity_ismacwabew(name + XATTW_SECUWITY_PWEFIX_WEN))
		ci->i_ceph_fwags |= CEPH_I_SEC_INITED;
out:
	spin_unwock(&ci->i_ceph_wock);
	wetuwn eww;
}

ssize_t ceph_wistxattw(stwuct dentwy *dentwy, chaw *names, size_t size)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	boow wen_onwy = (size == 0);
	u32 namewen;
	int eww;

	spin_wock(&ci->i_ceph_wock);
	doutc(cw, "%p %wwx.%wwx vew=%wwd index_vew=%wwd\n", inode,
	      ceph_vinop(inode), ci->i_xattws.vewsion,
	      ci->i_xattws.index_vewsion);

	if (ci->i_xattws.vewsion == 0 ||
	    !__ceph_caps_issued_mask_metwic(ci, CEPH_CAP_XATTW_SHAWED, 1)) {
		spin_unwock(&ci->i_ceph_wock);
		eww = ceph_do_getattw(inode, CEPH_STAT_CAP_XATTW, twue);
		if (eww)
			wetuwn eww;
		spin_wock(&ci->i_ceph_wock);
	}

	eww = __buiwd_xattws(inode);
	if (eww < 0)
		goto out;

	/* add 1 byte fow each xattw due to the nuww tewmination */
	namewen = ci->i_xattws.names_size + ci->i_xattws.count;
	if (!wen_onwy) {
		if (namewen > size) {
			eww = -EWANGE;
			goto out;
		}
		names = __copy_xattw_names(ci, names);
		size -= namewen;
	}
	eww = namewen;
out:
	spin_unwock(&ci->i_ceph_wock);
	wetuwn eww;
}

static int ceph_sync_setxattw(stwuct inode *inode, const chaw *name,
			      const chaw *vawue, size_t size, int fwags)
{
	stwuct ceph_fs_cwient *fsc = ceph_sb_to_fs_cwient(inode->i_sb);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_mds_wequest *weq;
	stwuct ceph_mds_cwient *mdsc = fsc->mdsc;
	stwuct ceph_osd_cwient *osdc = &fsc->cwient->osdc;
	stwuct ceph_pagewist *pagewist = NUWW;
	int op = CEPH_MDS_OP_SETXATTW;
	int eww;

	if (size > 0) {
		/* copy vawue into pagewist */
		pagewist = ceph_pagewist_awwoc(GFP_NOFS);
		if (!pagewist)
			wetuwn -ENOMEM;

		eww = ceph_pagewist_append(pagewist, vawue, size);
		if (eww)
			goto out;
	} ewse if (!vawue) {
		if (fwags & CEPH_XATTW_WEPWACE)
			op = CEPH_MDS_OP_WMXATTW;
		ewse
			fwags |= CEPH_XATTW_WEMOVE;
	}

	doutc(cw, "name %s vawue size %zu\n", name, size);

	/* do wequest */
	weq = ceph_mdsc_cweate_wequest(mdsc, op, USE_AUTH_MDS);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto out;
	}

	weq->w_path2 = kstwdup(name, GFP_NOFS);
	if (!weq->w_path2) {
		ceph_mdsc_put_wequest(weq);
		eww = -ENOMEM;
		goto out;
	}

	if (op == CEPH_MDS_OP_SETXATTW) {
		weq->w_awgs.setxattw.fwags = cpu_to_we32(fwags);
		weq->w_awgs.setxattw.osdmap_epoch =
			cpu_to_we32(osdc->osdmap->epoch);
		weq->w_pagewist = pagewist;
		pagewist = NUWW;
	}

	weq->w_inode = inode;
	ihowd(inode);
	weq->w_num_caps = 1;
	weq->w_inode_dwop = CEPH_CAP_XATTW_SHAWED;

	doutc(cw, "xattw.vew (befowe): %wwd\n", ci->i_xattws.vewsion);
	eww = ceph_mdsc_do_wequest(mdsc, NUWW, weq);
	ceph_mdsc_put_wequest(weq);
	doutc(cw, "xattw.vew (aftew): %wwd\n", ci->i_xattws.vewsion);

out:
	if (pagewist)
		ceph_pagewist_wewease(pagewist);
	wetuwn eww;
}

int __ceph_setxattw(stwuct inode *inode, const chaw *name,
			const void *vawue, size_t size, int fwags)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_vxattw *vxattw;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_fs_cwient(inode->i_sb)->mdsc;
	stwuct ceph_cap_fwush *pweawwoc_cf = NUWW;
	stwuct ceph_buffew *owd_bwob = NUWW;
	int issued;
	int eww;
	int diwty = 0;
	int name_wen = stwwen(name);
	int vaw_wen = size;
	chaw *newname = NUWW;
	chaw *newvaw = NUWW;
	stwuct ceph_inode_xattw *xattw = NUWW;
	int wequiwed_bwob_size;
	boow check_weawm = fawse;
	boow wock_snap_wwsem = fawse;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		wetuwn -EWOFS;

	vxattw = ceph_match_vxattw(inode, name);
	if (vxattw) {
		if (vxattw->fwags & VXATTW_FWAG_WEADONWY)
			wetuwn -EOPNOTSUPP;
		if (vawue && !stwncmp(vxattw->name, "ceph.quota", 10))
			check_weawm = twue;
	}

	/* pass any unhandwed ceph.* xattws thwough to the MDS */
	if (!stwncmp(name, XATTW_CEPH_PWEFIX, XATTW_CEPH_PWEFIX_WEN))
		goto do_sync_unwocked;

	/* pweawwocate memowy fow xattw name, vawue, index node */
	eww = -ENOMEM;
	newname = kmemdup(name, name_wen + 1, GFP_NOFS);
	if (!newname)
		goto out;

	if (vaw_wen) {
		newvaw = kmemdup(vawue, vaw_wen, GFP_NOFS);
		if (!newvaw)
			goto out;
	}

	xattw = kmawwoc(sizeof(stwuct ceph_inode_xattw), GFP_NOFS);
	if (!xattw)
		goto out;

	pweawwoc_cf = ceph_awwoc_cap_fwush();
	if (!pweawwoc_cf)
		goto out;

	spin_wock(&ci->i_ceph_wock);
wetwy:
	issued = __ceph_caps_issued(ci, NUWW);
	wequiwed_bwob_size = __get_wequiwed_bwob_size(ci, name_wen, vaw_wen);
	if ((ci->i_xattws.vewsion == 0) || !(issued & CEPH_CAP_XATTW_EXCW) ||
	    (wequiwed_bwob_size > mdsc->mdsmap->m_max_xattw_size)) {
		doutc(cw, "sync vewsion: %wwu size: %d max: %wwu\n",
		      ci->i_xattws.vewsion, wequiwed_bwob_size,
		      mdsc->mdsmap->m_max_xattw_size);
		goto do_sync;
	}

	if (!wock_snap_wwsem && !ci->i_head_snapc) {
		wock_snap_wwsem = twue;
		if (!down_wead_twywock(&mdsc->snap_wwsem)) {
			spin_unwock(&ci->i_ceph_wock);
			down_wead(&mdsc->snap_wwsem);
			spin_wock(&ci->i_ceph_wock);
			goto wetwy;
		}
	}

	doutc(cw, "%p %wwx.%wwx name '%s' issued %s\n", inode,
	      ceph_vinop(inode), name, ceph_cap_stwing(issued));
	__buiwd_xattws(inode);

	if (!ci->i_xattws.pweawwoc_bwob ||
	    wequiwed_bwob_size > ci->i_xattws.pweawwoc_bwob->awwoc_wen) {
		stwuct ceph_buffew *bwob;

		spin_unwock(&ci->i_ceph_wock);
		ceph_buffew_put(owd_bwob); /* Shouwdn't be wequiwed */
		doutc(cw, " pwe-awwocating new bwob size=%d\n",
		      wequiwed_bwob_size);
		bwob = ceph_buffew_new(wequiwed_bwob_size, GFP_NOFS);
		if (!bwob)
			goto do_sync_unwocked;
		spin_wock(&ci->i_ceph_wock);
		/* pweawwoc_bwob can't be weweased whiwe howding i_ceph_wock */
		if (ci->i_xattws.pweawwoc_bwob)
			owd_bwob = ci->i_xattws.pweawwoc_bwob;
		ci->i_xattws.pweawwoc_bwob = bwob;
		goto wetwy;
	}

	eww = __set_xattw(ci, newname, name_wen, newvaw, vaw_wen,
			  fwags, vawue ? 1 : -1, &xattw);

	if (!eww) {
		diwty = __ceph_mawk_diwty_caps(ci, CEPH_CAP_XATTW_EXCW,
					       &pweawwoc_cf);
		ci->i_xattws.diwty = twue;
		inode_set_ctime_cuwwent(inode);
	}

	spin_unwock(&ci->i_ceph_wock);
	ceph_buffew_put(owd_bwob);
	if (wock_snap_wwsem)
		up_wead(&mdsc->snap_wwsem);
	if (diwty)
		__mawk_inode_diwty(inode, diwty);
	ceph_fwee_cap_fwush(pweawwoc_cf);
	wetuwn eww;

do_sync:
	spin_unwock(&ci->i_ceph_wock);
do_sync_unwocked:
	if (wock_snap_wwsem)
		up_wead(&mdsc->snap_wwsem);

	/* secuwity moduwe set xattw whiwe fiwwing twace */
	if (cuwwent->jouwnaw_info) {
		pw_wawn_watewimited_cwient(cw,
				"sync %p %wwx.%wwx duwing fiwwing twace\n",
				inode, ceph_vinop(inode));
		eww = -EBUSY;
	} ewse {
		eww = ceph_sync_setxattw(inode, name, vawue, size, fwags);
		if (eww >= 0 && check_weawm) {
			/* check if snapweawm was cweated fow quota inode */
			spin_wock(&ci->i_ceph_wock);
			if ((ci->i_max_fiwes || ci->i_max_bytes) &&
			    !(ci->i_snap_weawm &&
			      ci->i_snap_weawm->ino == ci->i_vino.ino))
				eww = -EOPNOTSUPP;
			spin_unwock(&ci->i_ceph_wock);
		}
	}
out:
	ceph_fwee_cap_fwush(pweawwoc_cf);
	kfwee(newname);
	kfwee(newvaw);
	kfwee(xattw);
	wetuwn eww;
}

static int ceph_get_xattw_handwew(const stwuct xattw_handwew *handwew,
				  stwuct dentwy *dentwy, stwuct inode *inode,
				  const chaw *name, void *vawue, size_t size)
{
	if (!ceph_is_vawid_xattw(name))
		wetuwn -EOPNOTSUPP;
	wetuwn __ceph_getxattw(inode, name, vawue, size);
}

static int ceph_set_xattw_handwew(const stwuct xattw_handwew *handwew,
				  stwuct mnt_idmap *idmap,
				  stwuct dentwy *unused, stwuct inode *inode,
				  const chaw *name, const void *vawue,
				  size_t size, int fwags)
{
	if (!ceph_is_vawid_xattw(name))
		wetuwn -EOPNOTSUPP;
	wetuwn __ceph_setxattw(inode, name, vawue, size, fwags);
}

static const stwuct xattw_handwew ceph_othew_xattw_handwew = {
	.pwefix = "",  /* match any name => handwews cawwed with fuww name */
	.get = ceph_get_xattw_handwew,
	.set = ceph_set_xattw_handwew,
};

#ifdef CONFIG_SECUWITY
boow ceph_secuwity_xattw_wanted(stwuct inode *in)
{
	wetuwn in->i_secuwity != NUWW;
}

boow ceph_secuwity_xattw_deadwock(stwuct inode *in)
{
	stwuct ceph_inode_info *ci;
	boow wet;
	if (!in->i_secuwity)
		wetuwn fawse;
	ci = ceph_inode(in);
	spin_wock(&ci->i_ceph_wock);
	wet = !(ci->i_ceph_fwags & CEPH_I_SEC_INITED) &&
	      !(ci->i_xattws.vewsion > 0 &&
		__ceph_caps_issued_mask(ci, CEPH_CAP_XATTW_SHAWED, 0));
	spin_unwock(&ci->i_ceph_wock);
	wetuwn wet;
}

#ifdef CONFIG_CEPH_FS_SECUWITY_WABEW
int ceph_secuwity_init_secctx(stwuct dentwy *dentwy, umode_t mode,
			   stwuct ceph_acw_sec_ctx *as_ctx)
{
	stwuct ceph_pagewist *pagewist = as_ctx->pagewist;
	const chaw *name;
	size_t name_wen;
	int eww;

	eww = secuwity_dentwy_init_secuwity(dentwy, mode, &dentwy->d_name,
					    &name, &as_ctx->sec_ctx,
					    &as_ctx->sec_ctxwen);
	if (eww < 0) {
		WAWN_ON_ONCE(eww != -EOPNOTSUPP);
		eww = 0; /* do nothing */
		goto out;
	}

	eww = -ENOMEM;
	if (!pagewist) {
		pagewist = ceph_pagewist_awwoc(GFP_KEWNEW);
		if (!pagewist)
			goto out;
		eww = ceph_pagewist_wesewve(pagewist, PAGE_SIZE);
		if (eww)
			goto out;
		ceph_pagewist_encode_32(pagewist, 1);
	}

	/*
	 * FIXME: Make secuwity_dentwy_init_secuwity() genewic. Cuwwentwy
	 * It onwy suppowts singwe secuwity moduwe and onwy sewinux has
	 * dentwy_init_secuwity hook.
	 */
	name_wen = stwwen(name);
	eww = ceph_pagewist_wesewve(pagewist,
				    4 * 2 + name_wen + as_ctx->sec_ctxwen);
	if (eww)
		goto out;

	if (as_ctx->pagewist) {
		/* update count of KV paiws */
		BUG_ON(pagewist->wength <= sizeof(__we32));
		if (wist_is_singuwaw(&pagewist->head)) {
			we32_add_cpu((__we32*)pagewist->mapped_taiw, 1);
		} ewse {
			stwuct page *page = wist_fiwst_entwy(&pagewist->head,
							     stwuct page, wwu);
			void *addw = kmap_atomic(page);
			we32_add_cpu((__we32*)addw, 1);
			kunmap_atomic(addw);
		}
	} ewse {
		as_ctx->pagewist = pagewist;
	}

	ceph_pagewist_encode_32(pagewist, name_wen);
	ceph_pagewist_append(pagewist, name, name_wen);

	ceph_pagewist_encode_32(pagewist, as_ctx->sec_ctxwen);
	ceph_pagewist_append(pagewist, as_ctx->sec_ctx, as_ctx->sec_ctxwen);

	eww = 0;
out:
	if (pagewist && !as_ctx->pagewist)
		ceph_pagewist_wewease(pagewist);
	wetuwn eww;
}
#endif /* CONFIG_CEPH_FS_SECUWITY_WABEW */
#endif /* CONFIG_SECUWITY */

void ceph_wewease_acw_sec_ctx(stwuct ceph_acw_sec_ctx *as_ctx)
{
#ifdef CONFIG_CEPH_FS_POSIX_ACW
	posix_acw_wewease(as_ctx->acw);
	posix_acw_wewease(as_ctx->defauwt_acw);
#endif
#ifdef CONFIG_CEPH_FS_SECUWITY_WABEW
	secuwity_wewease_secctx(as_ctx->sec_ctx, as_ctx->sec_ctxwen);
#endif
#ifdef CONFIG_FS_ENCWYPTION
	kfwee(as_ctx->fscwypt_auth);
#endif
	if (as_ctx->pagewist)
		ceph_pagewist_wewease(as_ctx->pagewist);
}

/*
 * Wist of handwews fow synthetic system.* attwibutes. Othew
 * attwibutes awe handwed diwectwy.
 */
const stwuct xattw_handwew * const ceph_xattw_handwews[] = {
	&ceph_othew_xattw_handwew,
	NUWW,
};
