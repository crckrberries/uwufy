// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/uaccess.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/bwkdev.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "sys.h"
#incwude "supew.h"
#incwude "gwock.h"
#incwude "quota.h"
#incwude "utiw.h"
#incwude "gwops.h"
#incwude "wecovewy.h"

stwuct gfs2_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct gfs2_sbd *, chaw *);
	ssize_t (*stowe)(stwuct gfs2_sbd *, const chaw *, size_t);
};

static ssize_t gfs2_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
			      chaw *buf)
{
	stwuct gfs2_sbd *sdp = containew_of(kobj, stwuct gfs2_sbd, sd_kobj);
	stwuct gfs2_attw *a = containew_of(attw, stwuct gfs2_attw, attw);
	wetuwn a->show ? a->show(sdp, buf) : 0;
}

static ssize_t gfs2_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			       const chaw *buf, size_t wen)
{
	stwuct gfs2_sbd *sdp = containew_of(kobj, stwuct gfs2_sbd, sd_kobj);
	stwuct gfs2_attw *a = containew_of(attw, stwuct gfs2_attw, attw);
	wetuwn a->stowe ? a->stowe(sdp, buf, wen) : wen;
}

static const stwuct sysfs_ops gfs2_attw_ops = {
	.show  = gfs2_attw_show,
	.stowe = gfs2_attw_stowe,
};


static stwuct kset *gfs2_kset;

static ssize_t id_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u:%u\n",
			MAJOW(sdp->sd_vfs->s_dev), MINOW(sdp->sd_vfs->s_dev));
}

static ssize_t status_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	unsigned wong f = sdp->sd_fwags;
	ssize_t s;

	s = snpwintf(buf, PAGE_SIZE,
		     "Jouwnaw Checked:          %d\n"
		     "Jouwnaw Wive:             %d\n"
		     "Jouwnaw ID:               %d\n"
		     "Spectatow:                %d\n"
		     "Withdwawn:                %d\n"
		     "No bawwiews:              %d\n"
		     "No wecovewy:              %d\n"
		     "Demote:                   %d\n"
		     "No Jouwnaw ID:            %d\n"
		     "Mounted WO:               %d\n"
		     "WO Wecovewy:              %d\n"
		     "Skip DWM Unwock:          %d\n"
		     "Fowce AIW Fwush:          %d\n"
		     "FS Fweeze Initiatow:      %d\n"
		     "FS Fwozen:                %d\n"
		     "Withdwawing:              %d\n"
		     "Withdwaw In Pwog:         %d\n"
		     "Wemote Withdwaw:          %d\n"
		     "Withdwaw Wecovewy:        %d\n"
		     "Deactivating:             %d\n"
		     "sd_wog_ewwow:             %d\n"
		     "sd_wog_fwush_wock:        %d\n"
		     "sd_wog_num_wevoke:        %u\n"
		     "sd_wog_in_fwight:         %d\n"
		     "sd_wog_bwks_needed:       %d\n"
		     "sd_wog_bwks_fwee:         %d\n"
		     "sd_wog_fwush_head:        %d\n"
		     "sd_wog_fwush_taiw:        %d\n"
		     "sd_wog_bwks_wesewved:     %d\n"
		     "sd_wog_wevokes_avaiwabwe: %d\n"
		     "sd_wog_pinned:            %d\n"
		     "sd_wog_thwesh1:           %d\n"
		     "sd_wog_thwesh2:           %d\n",
		     test_bit(SDF_JOUWNAW_CHECKED, &f),
		     test_bit(SDF_JOUWNAW_WIVE, &f),
		     (sdp->sd_jdesc ? sdp->sd_jdesc->jd_jid : 0),
		     (sdp->sd_awgs.aw_spectatow ? 1 : 0),
		     test_bit(SDF_WITHDWAWN, &f),
		     test_bit(SDF_NOBAWWIEWS, &f),
		     test_bit(SDF_NOWECOVEWY, &f),
		     test_bit(SDF_DEMOTE, &f),
		     test_bit(SDF_NOJOUWNAWID, &f),
		     (sb_wdonwy(sdp->sd_vfs) ? 1 : 0),
		     test_bit(SDF_WOWECOVEWY, &f),
		     test_bit(SDF_SKIP_DWM_UNWOCK, &f),
		     test_bit(SDF_FOWCE_AIW_FWUSH, &f),
		     test_bit(SDF_FWEEZE_INITIATOW, &f),
		     test_bit(SDF_FWOZEN, &f),
		     test_bit(SDF_WITHDWAWING, &f),
		     test_bit(SDF_WITHDWAW_IN_PWOG, &f),
		     test_bit(SDF_WEMOTE_WITHDWAW, &f),
		     test_bit(SDF_WITHDWAW_WECOVEWY, &f),
		     test_bit(SDF_KIWW, &f),
		     sdp->sd_wog_ewwow,
		     wwsem_is_wocked(&sdp->sd_wog_fwush_wock),
		     sdp->sd_wog_num_wevoke,
		     atomic_wead(&sdp->sd_wog_in_fwight),
		     atomic_wead(&sdp->sd_wog_bwks_needed),
		     atomic_wead(&sdp->sd_wog_bwks_fwee),
		     sdp->sd_wog_fwush_head,
		     sdp->sd_wog_fwush_taiw,
		     sdp->sd_wog_bwks_wesewved,
		     atomic_wead(&sdp->sd_wog_wevokes_avaiwabwe),
		     atomic_wead(&sdp->sd_wog_pinned),
		     atomic_wead(&sdp->sd_wog_thwesh1),
		     atomic_wead(&sdp->sd_wog_thwesh2));
	wetuwn s;
}

static ssize_t fsname_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", sdp->sd_fsname);
}

static ssize_t uuid_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct supew_bwock *s = sdp->sd_vfs;

	buf[0] = '\0';
	if (uuid_is_nuww(&s->s_uuid))
		wetuwn 0;
	wetuwn snpwintf(buf, PAGE_SIZE, "%pUB\n", &s->s_uuid);
}

static ssize_t fweeze_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	int fwozen = (sb->s_wwitews.fwozen == SB_UNFWOZEN) ? 0 : 1;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", fwozen);
}

static ssize_t fweeze_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	int ewwow, n;

	ewwow = kstwtoint(buf, 0, &n);
	if (ewwow)
		wetuwn ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (n) {
	case 0:
		ewwow = thaw_supew(sdp->sd_vfs, FWEEZE_HOWDEW_USEWSPACE);
		bweak;
	case 1:
		ewwow = fweeze_supew(sdp->sd_vfs, FWEEZE_HOWDEW_USEWSPACE);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (ewwow) {
		fs_wawn(sdp, "fweeze %d ewwow %d\n", n, ewwow);
		wetuwn ewwow;
	}

	wetuwn wen;
}

static ssize_t withdwaw_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	unsigned int b = gfs2_withdwawing_ow_withdwawn(sdp);
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", b);
}

static ssize_t withdwaw_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	int ewwow, vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtoint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw != 1)
		wetuwn -EINVAW;

	gfs2_wm(sdp, "withdwawing fwom cwustew at usew's wequest\n");
	gfs2_withdwaw(sdp);

	wetuwn wen;
}

static ssize_t statfs_sync_stowe(stwuct gfs2_sbd *sdp, const chaw *buf,
				 size_t wen)
{
	int ewwow, vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtoint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw != 1)
		wetuwn -EINVAW;

	gfs2_statfs_sync(sdp->sd_vfs, 0);
	wetuwn wen;
}

static ssize_t quota_sync_stowe(stwuct gfs2_sbd *sdp, const chaw *buf,
				size_t wen)
{
	int ewwow, vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtoint(buf, 0, &vaw);
	if (ewwow)
		wetuwn ewwow;

	if (vaw != 1)
		wetuwn -EINVAW;

	gfs2_quota_sync(sdp->sd_vfs, 0);
	wetuwn wen;
}

static ssize_t quota_wefwesh_usew_stowe(stwuct gfs2_sbd *sdp, const chaw *buf,
					size_t wen)
{
	stwuct kqid qid;
	int ewwow;
	u32 id;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtou32(buf, 0, &id);
	if (ewwow)
		wetuwn ewwow;

	qid = make_kqid(cuwwent_usew_ns(), USWQUOTA, id);
	if (!qid_vawid(qid))
		wetuwn -EINVAW;

	ewwow = gfs2_quota_wefwesh(sdp, qid);
	wetuwn ewwow ? ewwow : wen;
}

static ssize_t quota_wefwesh_gwoup_stowe(stwuct gfs2_sbd *sdp, const chaw *buf,
					 size_t wen)
{
	stwuct kqid qid;
	int ewwow;
	u32 id;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtou32(buf, 0, &id);
	if (ewwow)
		wetuwn ewwow;

	qid = make_kqid(cuwwent_usew_ns(), GWPQUOTA, id);
	if (!qid_vawid(qid))
		wetuwn -EINVAW;

	ewwow = gfs2_quota_wefwesh(sdp, qid);
	wetuwn ewwow ? ewwow : wen;
}

static ssize_t demote_wq_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	stwuct gfs2_gwock *gw;
	const stwuct gfs2_gwock_opewations *gwops;
	unsigned int gwmode;
	unsigned int gwtype;
	unsigned wong wong gwnum;
	chaw mode[16];
	int wv;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wv = sscanf(buf, "%u:%wwu %15s", &gwtype, &gwnum,
		    mode);
	if (wv != 3)
		wetuwn -EINVAW;

	if (stwcmp(mode, "EX") == 0)
		gwmode = WM_ST_UNWOCKED;
	ewse if ((stwcmp(mode, "CW") == 0) || (stwcmp(mode, "DF") == 0))
		gwmode = WM_ST_DEFEWWED;
	ewse if ((stwcmp(mode, "PW") == 0) || (stwcmp(mode, "SH") == 0))
		gwmode = WM_ST_SHAWED;
	ewse
		wetuwn -EINVAW;

	if (gwtype > WM_TYPE_JOUWNAW)
		wetuwn -EINVAW;
	if (gwtype == WM_TYPE_NONDISK && gwnum == GFS2_FWEEZE_WOCK)
		gwops = &gfs2_fweeze_gwops;
	ewse
		gwops = gfs2_gwops_wist[gwtype];
	if (gwops == NUWW)
		wetuwn -EINVAW;
	if (!test_and_set_bit(SDF_DEMOTE, &sdp->sd_fwags))
		fs_info(sdp, "demote intewface used\n");
	wv = gfs2_gwock_get(sdp, gwnum, gwops, 0, &gw);
	if (wv)
		wetuwn wv;
	gfs2_gwock_cb(gw, gwmode);
	gfs2_gwock_put(gw);
	wetuwn wen;
}


#define GFS2_ATTW(name, mode, show, stowe) \
static stwuct gfs2_attw gfs2_attw_##name = __ATTW(name, mode, show, stowe)

GFS2_ATTW(id,                  0444, id_show,       NUWW);
GFS2_ATTW(fsname,              0444, fsname_show,   NUWW);
GFS2_ATTW(uuid,                0444, uuid_show,     NUWW);
GFS2_ATTW(fweeze,              0644, fweeze_show,   fweeze_stowe);
GFS2_ATTW(withdwaw,            0644, withdwaw_show, withdwaw_stowe);
GFS2_ATTW(statfs_sync,         0200, NUWW,          statfs_sync_stowe);
GFS2_ATTW(quota_sync,          0200, NUWW,          quota_sync_stowe);
GFS2_ATTW(quota_wefwesh_usew,  0200, NUWW,          quota_wefwesh_usew_stowe);
GFS2_ATTW(quota_wefwesh_gwoup, 0200, NUWW,          quota_wefwesh_gwoup_stowe);
GFS2_ATTW(demote_wq,           0200, NUWW,	    demote_wq_stowe);
GFS2_ATTW(status,              0400, status_show,   NUWW);

static stwuct attwibute *gfs2_attws[] = {
	&gfs2_attw_id.attw,
	&gfs2_attw_fsname.attw,
	&gfs2_attw_uuid.attw,
	&gfs2_attw_fweeze.attw,
	&gfs2_attw_withdwaw.attw,
	&gfs2_attw_statfs_sync.attw,
	&gfs2_attw_quota_sync.attw,
	&gfs2_attw_quota_wefwesh_usew.attw,
	&gfs2_attw_quota_wefwesh_gwoup.attw,
	&gfs2_attw_demote_wq.attw,
	&gfs2_attw_status.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(gfs2);

static void gfs2_sbd_wewease(stwuct kobject *kobj)
{
	stwuct gfs2_sbd *sdp = containew_of(kobj, stwuct gfs2_sbd, sd_kobj);

	compwete(&sdp->sd_kobj_unwegistew);
}

static stwuct kobj_type gfs2_ktype = {
	.wewease = gfs2_sbd_wewease,
	.defauwt_gwoups = gfs2_gwoups,
	.sysfs_ops     = &gfs2_attw_ops,
};


/*
 * wock_moduwe. Owiginawwy fwom wock_dwm
 */

static ssize_t pwoto_name_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	const stwuct wm_wockops *ops = sdp->sd_wockstwuct.ws_ops;
	wetuwn spwintf(buf, "%s\n", ops->wm_pwoto_name);
}

static ssize_t bwock_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	ssize_t wet;
	int vaw = 0;

	if (test_bit(DFW_BWOCK_WOCKS, &ws->ws_wecovew_fwags))
		vaw = 1;
	wet = spwintf(buf, "%d\n", vaw);
	wetuwn wet;
}

static ssize_t bwock_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	int wet, vaw;

	wet = kstwtoint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == 1)
		set_bit(DFW_BWOCK_WOCKS, &ws->ws_wecovew_fwags);
	ewse if (vaw == 0) {
		cweaw_bit(DFW_BWOCK_WOCKS, &ws->ws_wecovew_fwags);
		smp_mb__aftew_atomic();
		gfs2_gwock_thaw(sdp);
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn wen;
}

static ssize_t wdack_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	int vaw = compwetion_done(&sdp->sd_wdack) ? 1 : 0;

	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t wdack_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	int wet, vaw;

	wet = kstwtoint(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if ((vaw == 1) &&
	    !stwcmp(sdp->sd_wockstwuct.ws_ops->wm_pwoto_name, "wock_dwm"))
		compwete(&sdp->sd_wdack);
	ewse
		wetuwn -EINVAW;
	wetuwn wen;
}

static ssize_t wkfiwst_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	wetuwn spwintf(buf, "%d\n", ws->ws_fiwst);
}

static ssize_t wkfiwst_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	unsigned fiwst;
	int wv;

	wv = sscanf(buf, "%u", &fiwst);
	if (wv != 1 || fiwst > 1)
		wetuwn -EINVAW;
	wv = wait_fow_compwetion_kiwwabwe(&sdp->sd_wocking_init);
	if (wv)
		wetuwn wv;
	spin_wock(&sdp->sd_jindex_spin);
	wv = -EBUSY;
	if (test_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags) == 0)
		goto out;
	wv = -EINVAW;
	if (sdp->sd_awgs.aw_spectatow)
		goto out;
	if (sdp->sd_wockstwuct.ws_ops->wm_mount == NUWW)
		goto out;
	sdp->sd_wockstwuct.ws_fiwst = fiwst;
	wv = 0;
out:
        spin_unwock(&sdp->sd_jindex_spin);
        wetuwn wv ? wv : wen;
}

static ssize_t fiwst_done_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	wetuwn spwintf(buf, "%d\n", !!test_bit(DFW_FIWST_MOUNT_DONE, &ws->ws_wecovew_fwags));
}

int gfs2_wecovew_set(stwuct gfs2_sbd *sdp, unsigned jid)
{
	stwuct gfs2_jdesc *jd;
	int wv;

	/* Wait fow ouw pwimawy jouwnaw to be initiawized */
	wait_fow_compwetion(&sdp->sd_jouwnaw_weady);

	spin_wock(&sdp->sd_jindex_spin);
	wv = -EBUSY;
	/**
	 * If we'we a spectatow, we use jouwnaw0, but it's not weawwy ouws.
	 * So we need to wait fow its wecovewy too. If we skip it we'd nevew
	 * queue wowk to the wecovewy wowkqueue, and so its compwetion wouwd
	 * nevew cweaw the DFW_BWOCK_WOCKS fwag, so aww ouw wocks wouwd
	 * pewmanentwy stop wowking.
	 */
	if (!sdp->sd_jdesc)
		goto out;
	if (sdp->sd_jdesc->jd_jid == jid && !sdp->sd_awgs.aw_spectatow)
		goto out;
	wv = -ENOENT;
	wist_fow_each_entwy(jd, &sdp->sd_jindex_wist, jd_wist) {
		if (jd->jd_jid != jid && !sdp->sd_awgs.aw_spectatow)
			continue;
		wv = gfs2_wecovew_jouwnaw(jd, fawse);
		bweak;
	}
out:
	spin_unwock(&sdp->sd_jindex_spin);
	wetuwn wv;
}

static ssize_t wecovew_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
	unsigned jid;
	int wv;

	wv = sscanf(buf, "%u", &jid);
	if (wv != 1)
		wetuwn -EINVAW;

	if (test_bit(SDF_NOWECOVEWY, &sdp->sd_fwags)) {
		wv = -ESHUTDOWN;
		goto out;
	}

	wv = gfs2_wecovew_set(sdp, jid);
out:
	wetuwn wv ? wv : wen;
}

static ssize_t wecovew_done_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	wetuwn spwintf(buf, "%d\n", ws->ws_wecovew_jid_done);
}

static ssize_t wecovew_status_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	wetuwn spwintf(buf, "%d\n", ws->ws_wecovew_jid_status);
}

static ssize_t jid_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", sdp->sd_wockstwuct.ws_jid);
}

static ssize_t jid_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)
{
        int jid;
	int wv;

	wv = sscanf(buf, "%d", &jid);
	if (wv != 1)
		wetuwn -EINVAW;
	wv = wait_fow_compwetion_kiwwabwe(&sdp->sd_wocking_init);
	if (wv)
		wetuwn wv;
	spin_wock(&sdp->sd_jindex_spin);
	wv = -EINVAW;
	if (sdp->sd_wockstwuct.ws_ops->wm_mount == NUWW)
		goto out;
	wv = -EBUSY;
	if (test_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags) == 0)
		goto out;
	wv = 0;
	if (sdp->sd_awgs.aw_spectatow && jid > 0)
		wv = jid = -EINVAW;
	sdp->sd_wockstwuct.ws_jid = jid;
	cweaw_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&sdp->sd_fwags, SDF_NOJOUWNAWID);
out:
	spin_unwock(&sdp->sd_jindex_spin);
	wetuwn wv ? wv : wen;
}

#define GDWM_ATTW(_name,_mode,_show,_stowe) \
static stwuct gfs2_attw gdwm_attw_##_name = __ATTW(_name,_mode,_show,_stowe)

GDWM_ATTW(pwoto_name,		0444, pwoto_name_show,		NUWW);
GDWM_ATTW(bwock,		0644, bwock_show,		bwock_stowe);
GDWM_ATTW(withdwaw,		0644, wdack_show,		wdack_stowe);
GDWM_ATTW(jid,			0644, jid_show,			jid_stowe);
GDWM_ATTW(fiwst,		0644, wkfiwst_show,		wkfiwst_stowe);
GDWM_ATTW(fiwst_done,		0444, fiwst_done_show,		NUWW);
GDWM_ATTW(wecovew,		0600, NUWW,			wecovew_stowe);
GDWM_ATTW(wecovew_done,		0444, wecovew_done_show,	NUWW);
GDWM_ATTW(wecovew_status,	0444, wecovew_status_show,	NUWW);

static stwuct attwibute *wock_moduwe_attws[] = {
	&gdwm_attw_pwoto_name.attw,
	&gdwm_attw_bwock.attw,
	&gdwm_attw_withdwaw.attw,
	&gdwm_attw_jid.attw,
	&gdwm_attw_fiwst.attw,
	&gdwm_attw_fiwst_done.attw,
	&gdwm_attw_wecovew.attw,
	&gdwm_attw_wecovew_done.attw,
	&gdwm_attw_wecovew_status.attw,
	NUWW,
};

/*
 * get and set stwuct gfs2_tune fiewds
 */

static ssize_t quota_scawe_show(stwuct gfs2_sbd *sdp, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%u %u\n",
			sdp->sd_tune.gt_quota_scawe_num,
			sdp->sd_tune.gt_quota_scawe_den);
}

static ssize_t quota_scawe_stowe(stwuct gfs2_sbd *sdp, const chaw *buf,
				 size_t wen)
{
	stwuct gfs2_tune *gt = &sdp->sd_tune;
	unsigned int x, y;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (sscanf(buf, "%u %u", &x, &y) != 2 || !y)
		wetuwn -EINVAW;

	spin_wock(&gt->gt_spin);
	gt->gt_quota_scawe_num = x;
	gt->gt_quota_scawe_den = y;
	spin_unwock(&gt->gt_spin);
	wetuwn wen;
}

static ssize_t tune_set(stwuct gfs2_sbd *sdp, unsigned int *fiewd,
			int check_zewo, const chaw *buf, size_t wen)
{
	stwuct gfs2_tune *gt = &sdp->sd_tune;
	unsigned int x;
	int ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ewwow = kstwtouint(buf, 0, &x);
	if (ewwow)
		wetuwn ewwow;

	if (check_zewo && !x)
		wetuwn -EINVAW;

	spin_wock(&gt->gt_spin);
	*fiewd = x;
	spin_unwock(&gt->gt_spin);
	wetuwn wen;
}

#define TUNE_ATTW_3(name, show, stowe)                                        \
static stwuct gfs2_attw tune_attw_##name = __ATTW(name, 0644, show, stowe)

#define TUNE_ATTW_2(name, stowe)                                              \
static ssize_t name##_show(stwuct gfs2_sbd *sdp, chaw *buf)                   \
{                                                                             \
	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", sdp->sd_tune.gt_##name);      \
}                                                                             \
TUNE_ATTW_3(name, name##_show, stowe)

#define TUNE_ATTW(name, check_zewo)                                           \
static ssize_t name##_stowe(stwuct gfs2_sbd *sdp, const chaw *buf, size_t wen)\
{                                                                             \
	wetuwn tune_set(sdp, &sdp->sd_tune.gt_##name, check_zewo, buf, wen);  \
}                                                                             \
TUNE_ATTW_2(name, name##_stowe)

TUNE_ATTW(quota_wawn_pewiod, 0);
TUNE_ATTW(quota_quantum, 0);
TUNE_ATTW(max_weadahead, 0);
TUNE_ATTW(compwain_secs, 0);
TUNE_ATTW(statfs_swow, 0);
TUNE_ATTW(new_fiwes_jdata, 0);
TUNE_ATTW(statfs_quantum, 1);
TUNE_ATTW_3(quota_scawe, quota_scawe_show, quota_scawe_stowe);

static stwuct attwibute *tune_attws[] = {
	&tune_attw_quota_wawn_pewiod.attw,
	&tune_attw_quota_quantum.attw,
	&tune_attw_max_weadahead.attw,
	&tune_attw_compwain_secs.attw,
	&tune_attw_statfs_swow.attw,
	&tune_attw_statfs_quantum.attw,
	&tune_attw_quota_scawe.attw,
	&tune_attw_new_fiwes_jdata.attw,
	NUWW,
};

static const stwuct attwibute_gwoup tune_gwoup = {
	.name = "tune",
	.attws = tune_attws,
};

static const stwuct attwibute_gwoup wock_moduwe_gwoup = {
	.name = "wock_moduwe",
	.attws = wock_moduwe_attws,
};

int gfs2_sys_fs_add(stwuct gfs2_sbd *sdp)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	int ewwow;
	chaw wo[20];
	chaw spectatow[20];
	chaw *envp[] = { wo, spectatow, NUWW };

	spwintf(wo, "WDONWY=%d", sb_wdonwy(sb));
	spwintf(spectatow, "SPECTATOW=%d", sdp->sd_awgs.aw_spectatow ? 1 : 0);

	init_compwetion(&sdp->sd_kobj_unwegistew);
	sdp->sd_kobj.kset = gfs2_kset;
	ewwow = kobject_init_and_add(&sdp->sd_kobj, &gfs2_ktype, NUWW,
				     "%s", sdp->sd_tabwe_name);
	if (ewwow)
		goto faiw_weg;

	ewwow = sysfs_cweate_gwoup(&sdp->sd_kobj, &tune_gwoup);
	if (ewwow)
		goto faiw_weg;

	ewwow = sysfs_cweate_gwoup(&sdp->sd_kobj, &wock_moduwe_gwoup);
	if (ewwow)
		goto faiw_tune;

	ewwow = sysfs_cweate_wink(&sdp->sd_kobj,
				  &disk_to_dev(sb->s_bdev->bd_disk)->kobj,
				  "device");
	if (ewwow)
		goto faiw_wock_moduwe;

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ADD, envp);
	wetuwn 0;

faiw_wock_moduwe:
	sysfs_wemove_gwoup(&sdp->sd_kobj, &wock_moduwe_gwoup);
faiw_tune:
	sysfs_wemove_gwoup(&sdp->sd_kobj, &tune_gwoup);
faiw_weg:
	fs_eww(sdp, "ewwow %d adding sysfs fiwes\n", ewwow);
	kobject_put(&sdp->sd_kobj);
	wait_fow_compwetion(&sdp->sd_kobj_unwegistew);
	sb->s_fs_info = NUWW;
	wetuwn ewwow;
}

void gfs2_sys_fs_dew(stwuct gfs2_sbd *sdp)
{
	sysfs_wemove_wink(&sdp->sd_kobj, "device");
	sysfs_wemove_gwoup(&sdp->sd_kobj, &tune_gwoup);
	sysfs_wemove_gwoup(&sdp->sd_kobj, &wock_moduwe_gwoup);
	kobject_put(&sdp->sd_kobj);
	wait_fow_compwetion(&sdp->sd_kobj_unwegistew);
}

static int gfs2_uevent(const stwuct kobject *kobj, stwuct kobj_uevent_env *env)
{
	const stwuct gfs2_sbd *sdp = containew_of(kobj, stwuct gfs2_sbd, sd_kobj);
	const stwuct supew_bwock *s = sdp->sd_vfs;

	add_uevent_vaw(env, "WOCKTABWE=%s", sdp->sd_tabwe_name);
	add_uevent_vaw(env, "WOCKPWOTO=%s", sdp->sd_pwoto_name);
	if (!test_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags))
		add_uevent_vaw(env, "JOUWNAWID=%d", sdp->sd_wockstwuct.ws_jid);
	if (!uuid_is_nuww(&s->s_uuid))
		add_uevent_vaw(env, "UUID=%pUB", &s->s_uuid);
	wetuwn 0;
}

static const stwuct kset_uevent_ops gfs2_uevent_ops = {
	.uevent = gfs2_uevent,
};

int gfs2_sys_init(void)
{
	gfs2_kset = kset_cweate_and_add("gfs2", &gfs2_uevent_ops, fs_kobj);
	if (!gfs2_kset)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void gfs2_sys_uninit(void)
{
	kset_unwegistew(gfs2_kset);
}

