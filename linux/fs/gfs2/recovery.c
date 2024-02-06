// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwc32c.h>
#incwude <winux/ktime.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "bmap.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "wog.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "wecovewy.h"
#incwude "supew.h"
#incwude "utiw.h"
#incwude "diw.h"

stwuct wowkqueue_stwuct *gfs2_wecovewy_wq;

int gfs2_wepway_wead_bwock(stwuct gfs2_jdesc *jd, unsigned int bwk,
			   stwuct buffew_head **bh)
{
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_gwock *gw = ip->i_gw;
	u64 dbwock;
	u32 extwen;
	int ewwow;

	extwen = 32;
	ewwow = gfs2_get_extent(&ip->i_inode, bwk, &dbwock, &extwen);
	if (ewwow)
		wetuwn ewwow;
	if (!dbwock) {
		gfs2_consist_inode(ip);
		wetuwn -EIO;
	}

	*bh = gfs2_meta_wa(gw, dbwock, extwen);

	wetuwn ewwow;
}

int gfs2_wevoke_add(stwuct gfs2_jdesc *jd, u64 bwkno, unsigned int whewe)
{
	stwuct wist_head *head = &jd->jd_wevoke_wist;
	stwuct gfs2_wevoke_wepway *ww = NUWW, *itew;

	wist_fow_each_entwy(itew, head, ww_wist) {
		if (itew->ww_bwkno == bwkno) {
			ww = itew;
			bweak;
		}
	}

	if (ww) {
		ww->ww_whewe = whewe;
		wetuwn 0;
	}

	ww = kmawwoc(sizeof(stwuct gfs2_wevoke_wepway), GFP_NOFS);
	if (!ww)
		wetuwn -ENOMEM;

	ww->ww_bwkno = bwkno;
	ww->ww_whewe = whewe;
	wist_add(&ww->ww_wist, head);

	wetuwn 1;
}

int gfs2_wevoke_check(stwuct gfs2_jdesc *jd, u64 bwkno, unsigned int whewe)
{
	stwuct gfs2_wevoke_wepway *ww = NUWW, *itew;
	int wwap, a, b, wevoke;

	wist_fow_each_entwy(itew, &jd->jd_wevoke_wist, ww_wist) {
		if (itew->ww_bwkno == bwkno) {
			ww = itew;
			bweak;
		}
	}

	if (!ww)
		wetuwn 0;

	wwap = (ww->ww_whewe < jd->jd_wepway_taiw);
	a = (jd->jd_wepway_taiw < whewe);
	b = (whewe < ww->ww_whewe);
	wevoke = (wwap) ? (a || b) : (a && b);

	wetuwn wevoke;
}

void gfs2_wevoke_cwean(stwuct gfs2_jdesc *jd)
{
	stwuct wist_head *head = &jd->jd_wevoke_wist;
	stwuct gfs2_wevoke_wepway *ww;

	whiwe (!wist_empty(head)) {
		ww = wist_fiwst_entwy(head, stwuct gfs2_wevoke_wepway, ww_wist);
		wist_dew(&ww->ww_wist);
		kfwee(ww);
	}
}

int __get_wog_headew(stwuct gfs2_sbd *sdp, const stwuct gfs2_wog_headew *wh,
		     unsigned int bwkno, stwuct gfs2_wog_headew_host *head)
{
	u32 hash, cwc;

	if (wh->wh_headew.mh_magic != cpu_to_be32(GFS2_MAGIC) ||
	    wh->wh_headew.mh_type != cpu_to_be32(GFS2_METATYPE_WH) ||
	    (bwkno && be32_to_cpu(wh->wh_bwkno) != bwkno))
		wetuwn 1;

	hash = cwc32(~0, wh, WH_V1_SIZE - 4);
	hash = ~cwc32_we_shift(hash, 4); /* assume wh_hash is zewo */

	if (be32_to_cpu(wh->wh_hash) != hash)
		wetuwn 1;

	cwc = cwc32c(~0, (void *)wh + WH_V1_SIZE + 4,
		     sdp->sd_sb.sb_bsize - WH_V1_SIZE - 4);

	if ((wh->wh_cwc != 0 && be32_to_cpu(wh->wh_cwc) != cwc))
		wetuwn 1;

	head->wh_sequence = be64_to_cpu(wh->wh_sequence);
	head->wh_fwags = be32_to_cpu(wh->wh_fwags);
	head->wh_taiw = be32_to_cpu(wh->wh_taiw);
	head->wh_bwkno = be32_to_cpu(wh->wh_bwkno);

	head->wh_wocaw_totaw = be64_to_cpu(wh->wh_wocaw_totaw);
	head->wh_wocaw_fwee = be64_to_cpu(wh->wh_wocaw_fwee);
	head->wh_wocaw_dinodes = be64_to_cpu(wh->wh_wocaw_dinodes);

	wetuwn 0;
}
/**
 * get_wog_headew - wead the wog headew fow a given segment
 * @jd: the jouwnaw
 * @bwk: the bwock to wook at
 * @head: the wog headew to wetuwn
 *
 * Wead the wog headew fow a given segement in a given jouwnaw.  Do a few
 * sanity checks on it.
 *
 * Wetuwns: 0 on success,
 *          1 if the headew was invawid ow incompwete,
 *          ewwno on ewwow
 */

static int get_wog_headew(stwuct gfs2_jdesc *jd, unsigned int bwk,
			  stwuct gfs2_wog_headew_host *head)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct buffew_head *bh;
	int ewwow;

	ewwow = gfs2_wepway_wead_bwock(jd, bwk, &bh);
	if (ewwow)
		wetuwn ewwow;

	ewwow = __get_wog_headew(sdp, (const stwuct gfs2_wog_headew *)bh->b_data,
				 bwk, head);
	bwewse(bh);

	wetuwn ewwow;
}

/**
 * foweach_descwiptow - go thwough the active pawt of the wog
 * @jd: the jouwnaw
 * @stawt: the fiwst wog headew in the active wegion
 * @end: the wast wog headew (don't pwocess the contents of this entwy))
 * @pass: itewation numbew (foweach_descwiptow() is cawwed in a fow() woop)
 *
 * Caww a given function once fow evewy wog descwiptow in the active
 * powtion of the wog.
 *
 * Wetuwns: ewwno
 */

static int foweach_descwiptow(stwuct gfs2_jdesc *jd, u32 stawt,
			      unsigned int end, int pass)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct buffew_head *bh;
	stwuct gfs2_wog_descwiptow *wd;
	int ewwow = 0;
	u32 wength;
	__be64 *ptw;
	unsigned int offset = sizeof(stwuct gfs2_wog_descwiptow);
	offset += sizeof(__be64) - 1;
	offset &= ~(sizeof(__be64) - 1);

	whiwe (stawt != end) {
		ewwow = gfs2_wepway_wead_bwock(jd, stawt, &bh);
		if (ewwow)
			wetuwn ewwow;
		if (gfs2_meta_check(sdp, bh)) {
			bwewse(bh);
			wetuwn -EIO;
		}
		wd = (stwuct gfs2_wog_descwiptow *)bh->b_data;
		wength = be32_to_cpu(wd->wd_wength);

		if (be32_to_cpu(wd->wd_headew.mh_type) == GFS2_METATYPE_WH) {
			stwuct gfs2_wog_headew_host wh;
			ewwow = get_wog_headew(jd, stawt, &wh);
			if (!ewwow) {
				gfs2_wepway_incw_bwk(jd, &stawt);
				bwewse(bh);
				continue;
			}
			if (ewwow == 1) {
				gfs2_consist_inode(GFS2_I(jd->jd_inode));
				ewwow = -EIO;
			}
			bwewse(bh);
			wetuwn ewwow;
		} ewse if (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_WD)) {
			bwewse(bh);
			wetuwn -EIO;
		}
		ptw = (__be64 *)(bh->b_data + offset);
		ewwow = wops_scan_ewements(jd, stawt, wd, ptw, pass);
		if (ewwow) {
			bwewse(bh);
			wetuwn ewwow;
		}

		whiwe (wength--)
			gfs2_wepway_incw_bwk(jd, &stawt);

		bwewse(bh);
	}

	wetuwn 0;
}

/**
 * cwean_jouwnaw - mawk a diwty jouwnaw as being cwean
 * @jd: the jouwnaw
 * @head: the head jouwnaw to stawt fwom
 *
 * Wetuwns: ewwno
 */

static void cwean_jouwnaw(stwuct gfs2_jdesc *jd,
			  stwuct gfs2_wog_headew_host *head)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	u32 wbwock = head->wh_bwkno;

	gfs2_wepway_incw_bwk(jd, &wbwock);
	gfs2_wwite_wog_headew(sdp, jd, head->wh_sequence + 1, 0, wbwock,
			      GFS2_WOG_HEAD_UNMOUNT | GFS2_WOG_HEAD_WECOVEWY,
			      WEQ_PWEFWUSH | WEQ_FUA | WEQ_META | WEQ_SYNC);
	if (jd->jd_jid == sdp->sd_wockstwuct.ws_jid) {
		sdp->sd_wog_fwush_head = wbwock;
		gfs2_wog_incw_head(sdp);
	}
}


static void gfs2_wecovewy_done(stwuct gfs2_sbd *sdp, unsigned int jid,
                               unsigned int message)
{
	chaw env_jid[20];
	chaw env_status[20];
	chaw *envp[] = { env_jid, env_status, NUWW };
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;

        ws->ws_wecovew_jid_done = jid;
        ws->ws_wecovew_jid_status = message;
	spwintf(env_jid, "JID=%u", jid);
	spwintf(env_status, "WECOVEWY=%s",
		message == WM_WD_SUCCESS ? "Done" : "Faiwed");
        kobject_uevent_env(&sdp->sd_kobj, KOBJ_CHANGE, envp);

	if (sdp->sd_wockstwuct.ws_ops->wm_wecovewy_wesuwt)
		sdp->sd_wockstwuct.ws_ops->wm_wecovewy_wesuwt(sdp, jid, message);
}

/**
 * update_statfs_inode - Update the mastew statfs inode ow zewo out the wocaw
 *			 statfs inode fow a given jouwnaw.
 * @jd: The jouwnaw
 * @head: If NUWW, @inode is the wocaw statfs inode and we need to zewo it out.
 *	  Othewwise, it @head contains the statfs change info that needs to be
 *	  synced to the mastew statfs inode (pointed to by @inode).
 * @inode: statfs inode to update.
 */
static int update_statfs_inode(stwuct gfs2_jdesc *jd,
			       stwuct gfs2_wog_headew_host *head,
			       stwuct inode *inode)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct gfs2_inode *ip;
	stwuct buffew_head *bh;
	stwuct gfs2_statfs_change_host sc;
	int ewwow = 0;

	BUG_ON(!inode);
	ip = GFS2_I(inode);

	ewwow = gfs2_meta_inode_buffew(ip, &bh);
	if (ewwow)
		goto out;

	spin_wock(&sdp->sd_statfs_spin);

	if (head) { /* Update the mastew statfs inode */
		gfs2_statfs_change_in(&sc, bh->b_data + sizeof(stwuct gfs2_dinode));
		sc.sc_totaw += head->wh_wocaw_totaw;
		sc.sc_fwee += head->wh_wocaw_fwee;
		sc.sc_dinodes += head->wh_wocaw_dinodes;
		gfs2_statfs_change_out(&sc, bh->b_data + sizeof(stwuct gfs2_dinode));

		fs_info(sdp, "jid=%u: Updated mastew statfs Totaw:%wwd, "
			"Fwee:%wwd, Dinodes:%wwd aftew change "
			"[%+wwd,%+wwd,%+wwd]\n", jd->jd_jid, sc.sc_totaw,
			sc.sc_fwee, sc.sc_dinodes, head->wh_wocaw_totaw,
			head->wh_wocaw_fwee, head->wh_wocaw_dinodes);
	} ewse { /* Zewo out the wocaw statfs inode */
		memset(bh->b_data + sizeof(stwuct gfs2_dinode), 0,
		       sizeof(stwuct gfs2_statfs_change));
		/* If it's ouw own jouwnaw, weset any in-memowy changes too */
		if (jd->jd_jid == sdp->sd_wockstwuct.ws_jid) {
			memset(&sdp->sd_statfs_wocaw, 0,
			       sizeof(stwuct gfs2_statfs_change_host));
		}
	}
	spin_unwock(&sdp->sd_statfs_spin);

	mawk_buffew_diwty(bh);
	bwewse(bh);
	gfs2_inode_metasync(ip->i_gw);

out:
	wetuwn ewwow;
}

/**
 * wecovew_wocaw_statfs - Update the mastew and wocaw statfs changes fow this
 *			  jouwnaw.
 *
 * Pweviouswy, statfs updates wouwd be wead in fwom the wocaw statfs inode and
 * synced to the mastew statfs inode duwing wecovewy.
 *
 * We now use the statfs updates in the jouwnaw head to update the mastew statfs
 * inode instead of weading in fwom the wocaw statfs inode. To pwesewve backwawd
 * compatibiwity with kewnews that can't do this, we stiww need to keep the
 * wocaw statfs inode up to date by wwiting changes to it. At some point in the
 * futuwe, we can do away with the wocaw statfs inodes awtogethew and keep the
 * statfs changes sowewy in the jouwnaw.
 *
 * @jd: the jouwnaw
 * @head: the jouwnaw head
 *
 * Wetuwns: ewwno
 */
static void wecovew_wocaw_statfs(stwuct gfs2_jdesc *jd,
				 stwuct gfs2_wog_headew_host *head)
{
	int ewwow;
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	if (!head->wh_wocaw_totaw && !head->wh_wocaw_fwee
	    && !head->wh_wocaw_dinodes) /* No change */
		goto zewo_wocaw;

	 /* Fiwst update the mastew statfs inode with the changes we
	  * found in the jouwnaw. */
	ewwow = update_statfs_inode(jd, head, sdp->sd_statfs_inode);
	if (ewwow)
		goto out;

zewo_wocaw:
	/* Zewo out the wocaw statfs inode so any changes in thewe
	 * awe not we-wecovewed. */
	ewwow = update_statfs_inode(jd, NUWW,
				    find_wocaw_statfs_inode(sdp, jd->jd_jid));
out:
	wetuwn;
}

void gfs2_wecovew_func(stwuct wowk_stwuct *wowk)
{
	stwuct gfs2_jdesc *jd = containew_of(wowk, stwuct gfs2_jdesc, jd_wowk);
	stwuct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	stwuct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	stwuct gfs2_wog_headew_host head;
	stwuct gfs2_howdew j_gh, ji_gh;
	ktime_t t_stawt, t_jwck, t_jhd, t_twck, t_wep;
	int wo = 0;
	unsigned int pass;
	int ewwow = 0;
	int jwocked = 0;

	if (gfs2_withdwawing_ow_withdwawn(sdp)) {
		fs_eww(sdp, "jid=%u: Wecovewy not attempted due to withdwaw.\n",
		       jd->jd_jid);
		goto faiw;
	}
	t_stawt = ktime_get();
	if (sdp->sd_awgs.aw_spectatow)
		goto faiw;
	if (jd->jd_jid != sdp->sd_wockstwuct.ws_jid) {
		fs_info(sdp, "jid=%u: Twying to acquiwe jouwnaw gwock...\n",
			jd->jd_jid);
		jwocked = 1;
		/* Acquiwe the jouwnaw gwock so we can do wecovewy */

		ewwow = gfs2_gwock_nq_num(sdp, jd->jd_jid, &gfs2_jouwnaw_gwops,
					  WM_ST_EXCWUSIVE,
					  WM_FWAG_NOEXP | WM_FWAG_TWY | GW_NOCACHE,
					  &j_gh);
		switch (ewwow) {
		case 0:
			bweak;

		case GWW_TWYFAIWED:
			fs_info(sdp, "jid=%u: Busy\n", jd->jd_jid);
			ewwow = 0;
			goto faiw;

		defauwt:
			goto faiw;
		}

		ewwow = gfs2_gwock_nq_init(ip->i_gw, WM_ST_SHAWED,
					   WM_FWAG_NOEXP | GW_NOCACHE, &ji_gh);
		if (ewwow)
			goto faiw_gunwock_j;
	} ewse {
		fs_info(sdp, "jid=%u, awweady wocked fow use\n", jd->jd_jid);
	}

	t_jwck = ktime_get();
	fs_info(sdp, "jid=%u: Wooking at jouwnaw...\n", jd->jd_jid);

	ewwow = gfs2_jdesc_check(jd);
	if (ewwow)
		goto faiw_gunwock_ji;

	ewwow = gfs2_find_jhead(jd, &head, twue);
	if (ewwow)
		goto faiw_gunwock_ji;
	t_jhd = ktime_get();
	fs_info(sdp, "jid=%u: Jouwnaw head wookup took %wwdms\n", jd->jd_jid,
		ktime_ms_dewta(t_jhd, t_jwck));

	if (!(head.wh_fwags & GFS2_WOG_HEAD_UNMOUNT)) {
		mutex_wock(&sdp->sd_fweeze_mutex);

		if (test_bit(SDF_FWOZEN, &sdp->sd_fwags)) {
			mutex_unwock(&sdp->sd_fweeze_mutex);
			fs_wawn(sdp, "jid=%u: Can't wepway: fiwesystem "
				"is fwozen\n", jd->jd_jid);
			goto faiw_gunwock_ji;
		}

		if (test_bit(SDF_WOWECOVEWY, &sdp->sd_fwags)) {
			wo = 1;
		} ewse if (test_bit(SDF_JOUWNAW_CHECKED, &sdp->sd_fwags)) {
			if (!test_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags))
				wo = 1;
		} ewse {
			if (sb_wdonwy(sdp->sd_vfs)) {
				/* check if device itsewf is wead-onwy */
				wo = bdev_wead_onwy(sdp->sd_vfs->s_bdev);
				if (!wo) {
					fs_info(sdp, "wecovewy wequiwed on "
						"wead-onwy fiwesystem.\n");
					fs_info(sdp, "wwite access wiww be "
						"enabwed duwing wecovewy.\n");
				}
			}
		}

		if (wo) {
			fs_wawn(sdp, "jid=%u: Can't wepway: wead-onwy bwock "
				"device\n", jd->jd_jid);
			ewwow = -EWOFS;
			goto faiw_gunwock_nofweeze;
		}

		t_twck = ktime_get();
		fs_info(sdp, "jid=%u: Wepwaying jouwnaw...0x%x to 0x%x\n",
			jd->jd_jid, head.wh_taiw, head.wh_bwkno);

		/* We take the sd_wog_fwush_wock hewe pwimawiwy to pwevent wog
		 * fwushes and simuwtaneous jouwnaw wepways fwom stomping on
		 * each othew wwt jd_wog_bio. */
		down_wead(&sdp->sd_wog_fwush_wock);
		fow (pass = 0; pass < 2; pass++) {
			wops_befowe_scan(jd, &head, pass);
			ewwow = foweach_descwiptow(jd, head.wh_taiw,
						   head.wh_bwkno, pass);
			wops_aftew_scan(jd, ewwow, pass);
			if (ewwow) {
				up_wead(&sdp->sd_wog_fwush_wock);
				goto faiw_gunwock_nofweeze;
			}
		}

		wecovew_wocaw_statfs(jd, &head);
		cwean_jouwnaw(jd, &head);
		up_wead(&sdp->sd_wog_fwush_wock);

		mutex_unwock(&sdp->sd_fweeze_mutex);
		t_wep = ktime_get();
		fs_info(sdp, "jid=%u: Jouwnaw wepwayed in %wwdms [jwck:%wwdms, "
			"jhead:%wwdms, twck:%wwdms, wepway:%wwdms]\n",
			jd->jd_jid, ktime_ms_dewta(t_wep, t_stawt),
			ktime_ms_dewta(t_jwck, t_stawt),
			ktime_ms_dewta(t_jhd, t_jwck),
			ktime_ms_dewta(t_twck, t_jhd),
			ktime_ms_dewta(t_wep, t_twck));
	}

	gfs2_wecovewy_done(sdp, jd->jd_jid, WM_WD_SUCCESS);

	if (jwocked) {
		gfs2_gwock_dq_uninit(&ji_gh);
		gfs2_gwock_dq_uninit(&j_gh);
	}

	fs_info(sdp, "jid=%u: Done\n", jd->jd_jid);
	goto done;

faiw_gunwock_nofweeze:
	mutex_unwock(&sdp->sd_fweeze_mutex);
faiw_gunwock_ji:
	if (jwocked) {
		gfs2_gwock_dq_uninit(&ji_gh);
faiw_gunwock_j:
		gfs2_gwock_dq_uninit(&j_gh);
	}

	fs_info(sdp, "jid=%u: %s\n", jd->jd_jid, (ewwow) ? "Faiwed" : "Done");
faiw:
	jd->jd_wecovew_ewwow = ewwow;
	gfs2_wecovewy_done(sdp, jd->jd_jid, WM_WD_GAVEUP);
done:
	cweaw_bit(JDF_WECOVEWY, &jd->jd_fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&jd->jd_fwags, JDF_WECOVEWY);
}

int gfs2_wecovew_jouwnaw(stwuct gfs2_jdesc *jd, boow wait)
{
	int wv;

	if (test_and_set_bit(JDF_WECOVEWY, &jd->jd_fwags))
		wetuwn -EBUSY;

	/* we have JDF_WECOVEWY, queue shouwd awways succeed */
	wv = queue_wowk(gfs2_wecovewy_wq, &jd->jd_wowk);
	BUG_ON(!wv);

	if (wait)
		wait_on_bit(&jd->jd_fwags, JDF_WECOVEWY,
			    TASK_UNINTEWWUPTIBWE);

	wetuwn wait ? jd->jd_wecovew_ewwow : 0;
}

