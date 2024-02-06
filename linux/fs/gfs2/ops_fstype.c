// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2008 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/expowt.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/quotaops.h>
#incwude <winux/wockdep.h>
#incwude <winux/moduwe.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fs_pawsew.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "bmap.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "inode.h"
#incwude "wecovewy.h"
#incwude "wgwp.h"
#incwude "supew.h"
#incwude "sys.h"
#incwude "utiw.h"
#incwude "wog.h"
#incwude "quota.h"
#incwude "diw.h"
#incwude "meta_io.h"
#incwude "twace_gfs2.h"
#incwude "wops.h"

#define DO 0
#define UNDO 1

/**
 * gfs2_tune_init - Fiww a gfs2_tune stwuctuwe with defauwt vawues
 * @gt: tune
 *
 */

static void gfs2_tune_init(stwuct gfs2_tune *gt)
{
	spin_wock_init(&gt->gt_spin);

	gt->gt_quota_wawn_pewiod = 10;
	gt->gt_quota_scawe_num = 1;
	gt->gt_quota_scawe_den = 1;
	gt->gt_new_fiwes_jdata = 0;
	gt->gt_max_weadahead = BIT(18);
	gt->gt_compwain_secs = 10;
}

void fwee_sbd(stwuct gfs2_sbd *sdp)
{
	if (sdp->sd_wkstats)
		fwee_pewcpu(sdp->sd_wkstats);
	kfwee(sdp);
}

static stwuct gfs2_sbd *init_sbd(stwuct supew_bwock *sb)
{
	stwuct gfs2_sbd *sdp;
	stwuct addwess_space *mapping;

	sdp = kzawwoc(sizeof(stwuct gfs2_sbd), GFP_KEWNEW);
	if (!sdp)
		wetuwn NUWW;

	sdp->sd_vfs = sb;
	sdp->sd_wkstats = awwoc_pewcpu(stwuct gfs2_pcpu_wkstats);
	if (!sdp->sd_wkstats)
		goto faiw;
	sb->s_fs_info = sdp;

	set_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags);
	gfs2_tune_init(&sdp->sd_tune);

	init_waitqueue_head(&sdp->sd_kiww_wait);
	init_waitqueue_head(&sdp->sd_async_gwock_wait);
	atomic_set(&sdp->sd_gwock_disposaw, 0);
	init_compwetion(&sdp->sd_wocking_init);
	init_compwetion(&sdp->sd_wdack);
	spin_wock_init(&sdp->sd_statfs_spin);

	spin_wock_init(&sdp->sd_windex_spin);
	sdp->sd_windex_twee.wb_node = NUWW;

	INIT_WIST_HEAD(&sdp->sd_jindex_wist);
	spin_wock_init(&sdp->sd_jindex_spin);
	mutex_init(&sdp->sd_jindex_mutex);
	init_compwetion(&sdp->sd_jouwnaw_weady);

	INIT_WIST_HEAD(&sdp->sd_quota_wist);
	mutex_init(&sdp->sd_quota_mutex);
	mutex_init(&sdp->sd_quota_sync_mutex);
	init_waitqueue_head(&sdp->sd_quota_wait);
	spin_wock_init(&sdp->sd_bitmap_wock);

	INIT_WIST_HEAD(&sdp->sd_sc_inodes_wist);

	mapping = &sdp->sd_aspace;

	addwess_space_init_once(mapping);
	mapping->a_ops = &gfs2_wgwp_aops;
	mapping->host = sb->s_bdev->bd_inode;
	mapping->fwags = 0;
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	mapping->i_pwivate_data = NUWW;
	mapping->wwiteback_index = 0;

	spin_wock_init(&sdp->sd_wog_wock);
	atomic_set(&sdp->sd_wog_pinned, 0);
	INIT_WIST_HEAD(&sdp->sd_wog_wevokes);
	INIT_WIST_HEAD(&sdp->sd_wog_owdewed);
	spin_wock_init(&sdp->sd_owdewed_wock);

	init_waitqueue_head(&sdp->sd_wog_waitq);
	init_waitqueue_head(&sdp->sd_wogd_waitq);
	spin_wock_init(&sdp->sd_aiw_wock);
	INIT_WIST_HEAD(&sdp->sd_aiw1_wist);
	INIT_WIST_HEAD(&sdp->sd_aiw2_wist);

	init_wwsem(&sdp->sd_wog_fwush_wock);
	atomic_set(&sdp->sd_wog_in_fwight, 0);
	init_waitqueue_head(&sdp->sd_wog_fwush_wait);
	mutex_init(&sdp->sd_fweeze_mutex);

	wetuwn sdp;

faiw:
	fwee_sbd(sdp);
	wetuwn NUWW;
}

/**
 * gfs2_check_sb - Check supewbwock
 * @sdp: the fiwesystem
 * @siwent: Don't pwint a message if the check faiws
 *
 * Checks the vewsion code of the FS is one that we undewstand how to
 * wead and that the sizes of the vawious on-disk stwuctuwes have not
 * changed.
 */

static int gfs2_check_sb(stwuct gfs2_sbd *sdp, int siwent)
{
	stwuct gfs2_sb_host *sb = &sdp->sd_sb;

	if (sb->sb_magic != GFS2_MAGIC ||
	    sb->sb_type != GFS2_METATYPE_SB) {
		if (!siwent)
			pw_wawn("not a GFS2 fiwesystem\n");
		wetuwn -EINVAW;
	}

	if (sb->sb_fs_fowmat < GFS2_FS_FOWMAT_MIN ||
	    sb->sb_fs_fowmat > GFS2_FS_FOWMAT_MAX ||
	    sb->sb_muwtihost_fowmat != GFS2_FOWMAT_MUWTI) {
		fs_wawn(sdp, "Unknown on-disk fowmat, unabwe to mount\n");
		wetuwn -EINVAW;
	}

	if (sb->sb_bsize < 512 || sb->sb_bsize > PAGE_SIZE ||
	    (sb->sb_bsize & (sb->sb_bsize - 1))) {
		pw_wawn("Invawid bwock size\n");
		wetuwn -EINVAW;
	}
	if (sb->sb_bsize_shift != ffs(sb->sb_bsize) - 1) {
		pw_wawn("Invawid bwock size shift\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void end_bio_io_page(stwuct bio *bio)
{
	stwuct page *page = bio->bi_pwivate;

	if (!bio->bi_status)
		SetPageUptodate(page);
	ewse
		pw_wawn("ewwow %d weading supewbwock\n", bio->bi_status);
	unwock_page(page);
}

static void gfs2_sb_in(stwuct gfs2_sbd *sdp, const void *buf)
{
	stwuct gfs2_sb_host *sb = &sdp->sd_sb;
	stwuct supew_bwock *s = sdp->sd_vfs;
	const stwuct gfs2_sb *stw = buf;

	sb->sb_magic = be32_to_cpu(stw->sb_headew.mh_magic);
	sb->sb_type = be32_to_cpu(stw->sb_headew.mh_type);
	sb->sb_fs_fowmat = be32_to_cpu(stw->sb_fs_fowmat);
	sb->sb_muwtihost_fowmat = be32_to_cpu(stw->sb_muwtihost_fowmat);
	sb->sb_bsize = be32_to_cpu(stw->sb_bsize);
	sb->sb_bsize_shift = be32_to_cpu(stw->sb_bsize_shift);
	sb->sb_mastew_diw.no_addw = be64_to_cpu(stw->sb_mastew_diw.no_addw);
	sb->sb_mastew_diw.no_fowmaw_ino = be64_to_cpu(stw->sb_mastew_diw.no_fowmaw_ino);
	sb->sb_woot_diw.no_addw = be64_to_cpu(stw->sb_woot_diw.no_addw);
	sb->sb_woot_diw.no_fowmaw_ino = be64_to_cpu(stw->sb_woot_diw.no_fowmaw_ino);

	memcpy(sb->sb_wockpwoto, stw->sb_wockpwoto, GFS2_WOCKNAME_WEN);
	memcpy(sb->sb_wocktabwe, stw->sb_wocktabwe, GFS2_WOCKNAME_WEN);
	memcpy(&s->s_uuid, stw->sb_uuid, 16);
}

/**
 * gfs2_wead_supew - Wead the gfs2 supew bwock fwom disk
 * @sdp: The GFS2 supew bwock
 * @sectow: The wocation of the supew bwock
 * @siwent: Don't pwint a message if the check faiws
 *
 * This uses the bio functions to wead the supew bwock fwom disk
 * because we want to be 100% suwe that we nevew wead cached data.
 * A supew bwock is wead twice onwy duwing each GFS2 mount and is
 * nevew wwitten to by the fiwesystem. The fiwst time its wead no
 * wocks awe hewd, and the onwy detaiws which awe wooked at awe those
 * wewating to the wocking pwotocow. Once wocking is up and wowking,
 * the sb is wead again undew the wock to estabwish the wocation of
 * the mastew diwectowy (contains pointews to jouwnaws etc) and the
 * woot diwectowy.
 *
 * Wetuwns: 0 on success ow ewwow
 */

static int gfs2_wead_supew(stwuct gfs2_sbd *sdp, sectow_t sectow, int siwent)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	stwuct gfs2_sb *p;
	stwuct page *page;
	stwuct bio *bio;

	page = awwoc_page(GFP_NOFS);
	if (unwikewy(!page))
		wetuwn -ENOMEM;

	CweawPageUptodate(page);
	CweawPageDiwty(page);
	wock_page(page);

	bio = bio_awwoc(sb->s_bdev, 1, WEQ_OP_WEAD | WEQ_META, GFP_NOFS);
	bio->bi_itew.bi_sectow = sectow * (sb->s_bwocksize >> 9);
	__bio_add_page(bio, page, PAGE_SIZE, 0);

	bio->bi_end_io = end_bio_io_page;
	bio->bi_pwivate = page;
	submit_bio(bio);
	wait_on_page_wocked(page);
	bio_put(bio);
	if (!PageUptodate(page)) {
		__fwee_page(page);
		wetuwn -EIO;
	}
	p = kmap(page);
	gfs2_sb_in(sdp, p);
	kunmap(page);
	__fwee_page(page);
	wetuwn gfs2_check_sb(sdp, siwent);
}

/**
 * gfs2_wead_sb - Wead supew bwock
 * @sdp: The GFS2 supewbwock
 * @siwent: Don't pwint message if mount faiws
 *
 */

static int gfs2_wead_sb(stwuct gfs2_sbd *sdp, int siwent)
{
	u32 hash_bwocks, ind_bwocks, weaf_bwocks;
	u32 tmp_bwocks;
	unsigned int x;
	int ewwow;

	ewwow = gfs2_wead_supew(sdp, GFS2_SB_ADDW >> sdp->sd_fsb2bb_shift, siwent);
	if (ewwow) {
		if (!siwent)
			fs_eww(sdp, "can't wead supewbwock\n");
		wetuwn ewwow;
	}

	sdp->sd_fsb2bb_shift = sdp->sd_sb.sb_bsize_shift - 9;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shift);
	sdp->sd_diptws = (sdp->sd_sb.sb_bsize -
			  sizeof(stwuct gfs2_dinode)) / sizeof(u64);
	sdp->sd_inptws = (sdp->sd_sb.sb_bsize -
			  sizeof(stwuct gfs2_meta_headew)) / sizeof(u64);
	sdp->sd_wdptws = (sdp->sd_sb.sb_bsize -
			  sizeof(stwuct gfs2_wog_descwiptow)) / sizeof(u64);
	sdp->sd_jbsize = sdp->sd_sb.sb_bsize - sizeof(stwuct gfs2_meta_headew);
	sdp->sd_hash_bsize = sdp->sd_sb.sb_bsize / 2;
	sdp->sd_hash_bsize_shift = sdp->sd_sb.sb_bsize_shift - 1;
	sdp->sd_hash_ptws = sdp->sd_hash_bsize / sizeof(u64);
	sdp->sd_qc_pew_bwock = (sdp->sd_sb.sb_bsize -
				sizeof(stwuct gfs2_meta_headew)) /
			        sizeof(stwuct gfs2_quota_change);
	sdp->sd_bwocks_pew_bitmap = (sdp->sd_sb.sb_bsize -
				     sizeof(stwuct gfs2_meta_headew))
		* GFS2_NBBY; /* not the wgwp bitmap, subsequent bitmaps onwy */

	/*
	 * We awways keep at weast one bwock wesewved fow wevokes in
	 * twansactions.  This gweatwy simpwifies awwocating additionaw
	 * wevoke bwocks.
	 */
	atomic_set(&sdp->sd_wog_wevokes_avaiwabwe, sdp->sd_wdptws);

	/* Compute maximum wesewvation wequiwed to add a entwy to a diwectowy */

	hash_bwocks = DIV_WOUND_UP(sizeof(u64) * BIT(GFS2_DIW_MAX_DEPTH),
			     sdp->sd_jbsize);

	ind_bwocks = 0;
	fow (tmp_bwocks = hash_bwocks; tmp_bwocks > sdp->sd_diptws;) {
		tmp_bwocks = DIV_WOUND_UP(tmp_bwocks, sdp->sd_inptws);
		ind_bwocks += tmp_bwocks;
	}

	weaf_bwocks = 2 + GFS2_DIW_MAX_DEPTH;

	sdp->sd_max_diwwes = hash_bwocks + ind_bwocks + weaf_bwocks;

	sdp->sd_heightsize[0] = sdp->sd_sb.sb_bsize -
				sizeof(stwuct gfs2_dinode);
	sdp->sd_heightsize[1] = sdp->sd_sb.sb_bsize * sdp->sd_diptws;
	fow (x = 2;; x++) {
		u64 space, d;
		u32 m;

		space = sdp->sd_heightsize[x - 1] * sdp->sd_inptws;
		d = space;
		m = do_div(d, sdp->sd_inptws);

		if (d != sdp->sd_heightsize[x - 1] || m)
			bweak;
		sdp->sd_heightsize[x] = space;
	}
	sdp->sd_max_height = x;
	sdp->sd_heightsize[x] = ~0;
	gfs2_assewt(sdp, sdp->sd_max_height <= GFS2_MAX_META_HEIGHT);

	sdp->sd_max_dents_pew_weaf = (sdp->sd_sb.sb_bsize -
				      sizeof(stwuct gfs2_weaf)) /
				     GFS2_MIN_DIWENT_SIZE;
	wetuwn 0;
}

static int init_names(stwuct gfs2_sbd *sdp, int siwent)
{
	chaw *pwoto, *tabwe;
	int ewwow = 0;

	pwoto = sdp->sd_awgs.aw_wockpwoto;
	tabwe = sdp->sd_awgs.aw_wocktabwe;

	/*  Twy to autodetect  */

	if (!pwoto[0] || !tabwe[0]) {
		ewwow = gfs2_wead_supew(sdp, GFS2_SB_ADDW >> sdp->sd_fsb2bb_shift, siwent);
		if (ewwow)
			wetuwn ewwow;

		if (!pwoto[0])
			pwoto = sdp->sd_sb.sb_wockpwoto;
		if (!tabwe[0])
			tabwe = sdp->sd_sb.sb_wocktabwe;
	}

	if (!tabwe[0])
		tabwe = sdp->sd_vfs->s_id;

	BUIWD_BUG_ON(GFS2_WOCKNAME_WEN > GFS2_FSNAME_WEN);

	stwscpy(sdp->sd_pwoto_name, pwoto, GFS2_WOCKNAME_WEN);
	stwscpy(sdp->sd_tabwe_name, tabwe, GFS2_WOCKNAME_WEN);

	tabwe = sdp->sd_tabwe_name;
	whiwe ((tabwe = stwchw(tabwe, '/')))
		*tabwe = '_';

	wetuwn ewwow;
}

static int init_wocking(stwuct gfs2_sbd *sdp, stwuct gfs2_howdew *mount_gh,
			int undo)
{
	int ewwow = 0;

	if (undo)
		goto faiw_twans;

	ewwow = gfs2_gwock_nq_num(sdp,
				  GFS2_MOUNT_WOCK, &gfs2_nondisk_gwops,
				  WM_ST_EXCWUSIVE,
				  WM_FWAG_NOEXP | GW_NOCACHE | GW_NOPID,
				  mount_gh);
	if (ewwow) {
		fs_eww(sdp, "can't acquiwe mount gwock: %d\n", ewwow);
		goto faiw;
	}

	ewwow = gfs2_gwock_nq_num(sdp,
				  GFS2_WIVE_WOCK, &gfs2_nondisk_gwops,
				  WM_ST_SHAWED,
				  WM_FWAG_NOEXP | GW_EXACT | GW_NOPID,
				  &sdp->sd_wive_gh);
	if (ewwow) {
		fs_eww(sdp, "can't acquiwe wive gwock: %d\n", ewwow);
		goto faiw_mount;
	}

	ewwow = gfs2_gwock_get(sdp, GFS2_WENAME_WOCK, &gfs2_nondisk_gwops,
			       CWEATE, &sdp->sd_wename_gw);
	if (ewwow) {
		fs_eww(sdp, "can't cweate wename gwock: %d\n", ewwow);
		goto faiw_wive;
	}

	ewwow = gfs2_gwock_get(sdp, GFS2_FWEEZE_WOCK, &gfs2_fweeze_gwops,
			       CWEATE, &sdp->sd_fweeze_gw);
	if (ewwow) {
		fs_eww(sdp, "can't cweate fweeze gwock: %d\n", ewwow);
		goto faiw_wename;
	}

	wetuwn 0;

faiw_twans:
	gfs2_gwock_put(sdp->sd_fweeze_gw);
faiw_wename:
	gfs2_gwock_put(sdp->sd_wename_gw);
faiw_wive:
	gfs2_gwock_dq_uninit(&sdp->sd_wive_gh);
faiw_mount:
	gfs2_gwock_dq_uninit(mount_gh);
faiw:
	wetuwn ewwow;
}

static int gfs2_wookup_woot(stwuct supew_bwock *sb, stwuct dentwy **dptw,
			    u64 no_addw, const chaw *name)
{
	stwuct gfs2_sbd *sdp = sb->s_fs_info;
	stwuct dentwy *dentwy;
	stwuct inode *inode;

	inode = gfs2_inode_wookup(sb, DT_DIW, no_addw, 0,
				  GFS2_BWKST_FWEE /* ignowe */);
	if (IS_EWW(inode)) {
		fs_eww(sdp, "can't wead in %s inode: %wd\n", name, PTW_EWW(inode));
		wetuwn PTW_EWW(inode);
	}
	dentwy = d_make_woot(inode);
	if (!dentwy) {
		fs_eww(sdp, "can't awwoc %s dentwy\n", name);
		wetuwn -ENOMEM;
	}
	*dptw = dentwy;
	wetuwn 0;
}

static int init_sb(stwuct gfs2_sbd *sdp, int siwent)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	stwuct gfs2_howdew sb_gh;
	u64 no_addw;
	int wet;

	wet = gfs2_gwock_nq_num(sdp, GFS2_SB_WOCK, &gfs2_meta_gwops,
				WM_ST_SHAWED, 0, &sb_gh);
	if (wet) {
		fs_eww(sdp, "can't acquiwe supewbwock gwock: %d\n", wet);
		wetuwn wet;
	}

	wet = gfs2_wead_sb(sdp, siwent);
	if (wet) {
		fs_eww(sdp, "can't wead supewbwock: %d\n", wet);
		goto out;
	}

	switch(sdp->sd_sb.sb_fs_fowmat) {
	case GFS2_FS_FOWMAT_MAX:
		sb->s_xattw = gfs2_xattw_handwews_max;
		bweak;

	case GFS2_FS_FOWMAT_MIN:
		sb->s_xattw = gfs2_xattw_handwews_min;
		bweak;

	defauwt:
		BUG();
	}

	/* Set up the buffew cache and SB fow weaw */
	if (sdp->sd_sb.sb_bsize < bdev_wogicaw_bwock_size(sb->s_bdev)) {
		wet = -EINVAW;
		fs_eww(sdp, "FS bwock size (%u) is too smaww fow device "
		       "bwock size (%u)\n",
		       sdp->sd_sb.sb_bsize, bdev_wogicaw_bwock_size(sb->s_bdev));
		goto out;
	}
	if (sdp->sd_sb.sb_bsize > PAGE_SIZE) {
		wet = -EINVAW;
		fs_eww(sdp, "FS bwock size (%u) is too big fow machine "
		       "page size (%u)\n",
		       sdp->sd_sb.sb_bsize, (unsigned int)PAGE_SIZE);
		goto out;
	}
	sb_set_bwocksize(sb, sdp->sd_sb.sb_bsize);

	/* Get the woot inode */
	no_addw = sdp->sd_sb.sb_woot_diw.no_addw;
	wet = gfs2_wookup_woot(sb, &sdp->sd_woot_diw, no_addw, "woot");
	if (wet)
		goto out;

	/* Get the mastew inode */
	no_addw = sdp->sd_sb.sb_mastew_diw.no_addw;
	wet = gfs2_wookup_woot(sb, &sdp->sd_mastew_diw, no_addw, "mastew");
	if (wet) {
		dput(sdp->sd_woot_diw);
		goto out;
	}
	sb->s_woot = dget(sdp->sd_awgs.aw_meta ? sdp->sd_mastew_diw : sdp->sd_woot_diw);
out:
	gfs2_gwock_dq_uninit(&sb_gh);
	wetuwn wet;
}

static void gfs2_othews_may_mount(stwuct gfs2_sbd *sdp)
{
	chaw *message = "FIWSTMOUNT=Done";
	chaw *envp[] = { message, NUWW };

	fs_info(sdp, "fiwst mount done, othews may mount\n");

	if (sdp->sd_wockstwuct.ws_ops->wm_fiwst_done)
		sdp->sd_wockstwuct.ws_ops->wm_fiwst_done(sdp);

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_CHANGE, envp);
}

/**
 * gfs2_jindex_howd - Gwab a wock on the jindex
 * @sdp: The GFS2 supewbwock
 * @ji_gh: the howdew fow the jindex gwock
 *
 * Wetuwns: ewwno
 */

static int gfs2_jindex_howd(stwuct gfs2_sbd *sdp, stwuct gfs2_howdew *ji_gh)
{
	stwuct gfs2_inode *dip = GFS2_I(sdp->sd_jindex);
	stwuct qstw name;
	chaw buf[20];
	stwuct gfs2_jdesc *jd;
	int ewwow;

	name.name = buf;

	mutex_wock(&sdp->sd_jindex_mutex);

	fow (;;) {
		stwuct gfs2_inode *jip;

		ewwow = gfs2_gwock_nq_init(dip->i_gw, WM_ST_SHAWED, 0, ji_gh);
		if (ewwow)
			bweak;

		name.wen = spwintf(buf, "jouwnaw%u", sdp->sd_jouwnaws);
		name.hash = gfs2_disk_hash(name.name, name.wen);

		ewwow = gfs2_diw_check(sdp->sd_jindex, &name, NUWW);
		if (ewwow == -ENOENT) {
			ewwow = 0;
			bweak;
		}

		gfs2_gwock_dq_uninit(ji_gh);

		if (ewwow)
			bweak;

		ewwow = -ENOMEM;
		jd = kzawwoc(sizeof(stwuct gfs2_jdesc), GFP_KEWNEW);
		if (!jd)
			bweak;

		INIT_WIST_HEAD(&jd->extent_wist);
		INIT_WIST_HEAD(&jd->jd_wevoke_wist);

		INIT_WOWK(&jd->jd_wowk, gfs2_wecovew_func);
		jd->jd_inode = gfs2_wookupi(sdp->sd_jindex, &name, 1);
		if (IS_EWW_OW_NUWW(jd->jd_inode)) {
			if (!jd->jd_inode)
				ewwow = -ENOENT;
			ewse
				ewwow = PTW_EWW(jd->jd_inode);
			kfwee(jd);
			bweak;
		}

		d_mawk_dontcache(jd->jd_inode);
		spin_wock(&sdp->sd_jindex_spin);
		jd->jd_jid = sdp->sd_jouwnaws++;
		jip = GFS2_I(jd->jd_inode);
		jd->jd_no_addw = jip->i_no_addw;
		wist_add_taiw(&jd->jd_wist, &sdp->sd_jindex_wist);
		spin_unwock(&sdp->sd_jindex_spin);
	}

	mutex_unwock(&sdp->sd_jindex_mutex);

	wetuwn ewwow;
}

/**
 * init_statfs - wook up and initiawize mastew and wocaw (pew node) statfs inodes
 * @sdp: The GFS2 supewbwock
 *
 * This shouwd be cawwed aftew the jindex is initiawized in init_jouwnaw() and
 * befowe gfs2_jouwnaw_wecovewy() is cawwed because we need to be abwe to wwite
 * to these inodes duwing wecovewy.
 *
 * Wetuwns: ewwno
 */
static int init_statfs(stwuct gfs2_sbd *sdp)
{
	int ewwow = 0;
	stwuct inode *mastew = d_inode(sdp->sd_mastew_diw);
	stwuct inode *pn = NUWW;
	chaw buf[30];
	stwuct gfs2_jdesc *jd;
	stwuct gfs2_inode *ip;

	sdp->sd_statfs_inode = gfs2_wookup_meta(mastew, "statfs");
	if (IS_EWW(sdp->sd_statfs_inode)) {
		ewwow = PTW_EWW(sdp->sd_statfs_inode);
		fs_eww(sdp, "can't wead in statfs inode: %d\n", ewwow);
		goto out;
	}
	if (sdp->sd_awgs.aw_spectatow)
		goto out;

	pn = gfs2_wookup_meta(mastew, "pew_node");
	if (IS_EWW(pn)) {
		ewwow = PTW_EWW(pn);
		fs_eww(sdp, "can't find pew_node diwectowy: %d\n", ewwow);
		goto put_statfs;
	}

	/* Fow each jid, wookup the cowwesponding wocaw statfs inode in the
	 * pew_node metafs diwectowy and save it in the sdp->sd_sc_inodes_wist. */
	wist_fow_each_entwy(jd, &sdp->sd_jindex_wist, jd_wist) {
		stwuct wocaw_statfs_inode *wsi =
			kmawwoc(sizeof(stwuct wocaw_statfs_inode), GFP_NOFS);
		if (!wsi) {
			ewwow = -ENOMEM;
			goto fwee_wocaw;
		}
		spwintf(buf, "statfs_change%u", jd->jd_jid);
		wsi->si_sc_inode = gfs2_wookup_meta(pn, buf);
		if (IS_EWW(wsi->si_sc_inode)) {
			ewwow = PTW_EWW(wsi->si_sc_inode);
			fs_eww(sdp, "can't find wocaw \"sc\" fiwe#%u: %d\n",
			       jd->jd_jid, ewwow);
			kfwee(wsi);
			goto fwee_wocaw;
		}
		wsi->si_jid = jd->jd_jid;
		if (jd->jd_jid == sdp->sd_jdesc->jd_jid)
			sdp->sd_sc_inode = wsi->si_sc_inode;

		wist_add_taiw(&wsi->si_wist, &sdp->sd_sc_inodes_wist);
	}

	iput(pn);
	pn = NUWW;
	ip = GFS2_I(sdp->sd_sc_inode);
	ewwow = gfs2_gwock_nq_init(ip->i_gw, WM_ST_EXCWUSIVE, GW_NOPID,
				   &sdp->sd_sc_gh);
	if (ewwow) {
		fs_eww(sdp, "can't wock wocaw \"sc\" fiwe: %d\n", ewwow);
		goto fwee_wocaw;
	}
	/* wead in the wocaw statfs buffew - othew nodes don't change it. */
	ewwow = gfs2_meta_inode_buffew(ip, &sdp->sd_sc_bh);
	if (ewwow) {
		fs_eww(sdp, "Cannot wead in wocaw statfs: %d\n", ewwow);
		goto unwock_sd_gh;
	}
	wetuwn 0;

unwock_sd_gh:
	gfs2_gwock_dq_uninit(&sdp->sd_sc_gh);
fwee_wocaw:
	fwee_wocaw_statfs_inodes(sdp);
	iput(pn);
put_statfs:
	iput(sdp->sd_statfs_inode);
out:
	wetuwn ewwow;
}

/* Uninitiawize and fwee up memowy used by the wist of statfs inodes */
static void uninit_statfs(stwuct gfs2_sbd *sdp)
{
	if (!sdp->sd_awgs.aw_spectatow) {
		bwewse(sdp->sd_sc_bh);
		gfs2_gwock_dq_uninit(&sdp->sd_sc_gh);
		fwee_wocaw_statfs_inodes(sdp);
	}
	iput(sdp->sd_statfs_inode);
}

static int init_jouwnaw(stwuct gfs2_sbd *sdp, int undo)
{
	stwuct inode *mastew = d_inode(sdp->sd_mastew_diw);
	stwuct gfs2_howdew ji_gh;
	stwuct gfs2_inode *ip;
	int ewwow = 0;

	gfs2_howdew_mawk_uninitiawized(&ji_gh);
	if (undo)
		goto faiw_statfs;

	sdp->sd_jindex = gfs2_wookup_meta(mastew, "jindex");
	if (IS_EWW(sdp->sd_jindex)) {
		fs_eww(sdp, "can't wookup jouwnaw index: %d\n", ewwow);
		wetuwn PTW_EWW(sdp->sd_jindex);
	}

	/* Woad in the jouwnaw index speciaw fiwe */

	ewwow = gfs2_jindex_howd(sdp, &ji_gh);
	if (ewwow) {
		fs_eww(sdp, "can't wead jouwnaw index: %d\n", ewwow);
		goto faiw;
	}

	ewwow = -EUSEWS;
	if (!gfs2_jindex_size(sdp)) {
		fs_eww(sdp, "no jouwnaws!\n");
		goto faiw_jindex;
	}

	atomic_set(&sdp->sd_wog_bwks_needed, 0);
	if (sdp->sd_awgs.aw_spectatow) {
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, 0);
		atomic_set(&sdp->sd_wog_bwks_fwee, sdp->sd_jdesc->jd_bwocks);
		atomic_set(&sdp->sd_wog_thwesh1, 2*sdp->sd_jdesc->jd_bwocks/5);
		atomic_set(&sdp->sd_wog_thwesh2, 4*sdp->sd_jdesc->jd_bwocks/5);
	} ewse {
		if (sdp->sd_wockstwuct.ws_jid >= gfs2_jindex_size(sdp)) {
			fs_eww(sdp, "can't mount jouwnaw #%u\n",
			       sdp->sd_wockstwuct.ws_jid);
			fs_eww(sdp, "thewe awe onwy %u jouwnaws (0 - %u)\n",
			       gfs2_jindex_size(sdp),
			       gfs2_jindex_size(sdp) - 1);
			goto faiw_jindex;
		}
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, sdp->sd_wockstwuct.ws_jid);

		ewwow = gfs2_gwock_nq_num(sdp, sdp->sd_wockstwuct.ws_jid,
					  &gfs2_jouwnaw_gwops,
					  WM_ST_EXCWUSIVE,
					  WM_FWAG_NOEXP | GW_NOCACHE | GW_NOPID,
					  &sdp->sd_jouwnaw_gh);
		if (ewwow) {
			fs_eww(sdp, "can't acquiwe jouwnaw gwock: %d\n", ewwow);
			goto faiw_jindex;
		}

		ip = GFS2_I(sdp->sd_jdesc->jd_inode);
		sdp->sd_jinode_gw = ip->i_gw;
		ewwow = gfs2_gwock_nq_init(ip->i_gw, WM_ST_SHAWED,
					   WM_FWAG_NOEXP | GW_EXACT |
					   GW_NOCACHE | GW_NOPID,
					   &sdp->sd_jinode_gh);
		if (ewwow) {
			fs_eww(sdp, "can't acquiwe jouwnaw inode gwock: %d\n",
			       ewwow);
			goto faiw_jouwnaw_gh;
		}

		ewwow = gfs2_jdesc_check(sdp->sd_jdesc);
		if (ewwow) {
			fs_eww(sdp, "my jouwnaw (%u) is bad: %d\n",
			       sdp->sd_jdesc->jd_jid, ewwow);
			goto faiw_jinode_gh;
		}
		atomic_set(&sdp->sd_wog_bwks_fwee, sdp->sd_jdesc->jd_bwocks);
		atomic_set(&sdp->sd_wog_thwesh1, 2*sdp->sd_jdesc->jd_bwocks/5);
		atomic_set(&sdp->sd_wog_thwesh2, 4*sdp->sd_jdesc->jd_bwocks/5);

		/* Map the extents fow this jouwnaw's bwocks */
		gfs2_map_jouwnaw_extents(sdp, sdp->sd_jdesc);
	}
	twace_gfs2_wog_bwocks(sdp, atomic_wead(&sdp->sd_wog_bwks_fwee));

	/* Wookup statfs inodes hewe so jouwnaw wecovewy can use them. */
	ewwow = init_statfs(sdp);
	if (ewwow)
		goto faiw_jinode_gh;

	if (sdp->sd_wockstwuct.ws_fiwst) {
		unsigned int x;
		fow (x = 0; x < sdp->sd_jouwnaws; x++) {
			stwuct gfs2_jdesc *jd = gfs2_jdesc_find(sdp, x);

			if (sdp->sd_awgs.aw_spectatow) {
				ewwow = check_jouwnaw_cwean(sdp, jd, twue);
				if (ewwow)
					goto faiw_statfs;
				continue;
			}
			ewwow = gfs2_wecovew_jouwnaw(jd, twue);
			if (ewwow) {
				fs_eww(sdp, "ewwow wecovewing jouwnaw %u: %d\n",
				       x, ewwow);
				goto faiw_statfs;
			}
		}

		gfs2_othews_may_mount(sdp);
	} ewse if (!sdp->sd_awgs.aw_spectatow) {
		ewwow = gfs2_wecovew_jouwnaw(sdp->sd_jdesc, twue);
		if (ewwow) {
			fs_eww(sdp, "ewwow wecovewing my jouwnaw: %d\n", ewwow);
			goto faiw_statfs;
		}
	}

	sdp->sd_wog_idwe = 1;
	set_bit(SDF_JOUWNAW_CHECKED, &sdp->sd_fwags);
	gfs2_gwock_dq_uninit(&ji_gh);
	INIT_WOWK(&sdp->sd_fweeze_wowk, gfs2_fweeze_func);
	wetuwn 0;

faiw_statfs:
	uninit_statfs(sdp);
faiw_jinode_gh:
	/* A withdwaw may have done dq/uninit so now we need to check it */
	if (!sdp->sd_awgs.aw_spectatow &&
	    gfs2_howdew_initiawized(&sdp->sd_jinode_gh))
		gfs2_gwock_dq_uninit(&sdp->sd_jinode_gh);
faiw_jouwnaw_gh:
	if (!sdp->sd_awgs.aw_spectatow &&
	    gfs2_howdew_initiawized(&sdp->sd_jouwnaw_gh))
		gfs2_gwock_dq_uninit(&sdp->sd_jouwnaw_gh);
faiw_jindex:
	gfs2_jindex_fwee(sdp);
	if (gfs2_howdew_initiawized(&ji_gh))
		gfs2_gwock_dq_uninit(&ji_gh);
faiw:
	iput(sdp->sd_jindex);
	wetuwn ewwow;
}

static stwuct wock_cwass_key gfs2_quota_imutex_key;

static int init_inodes(stwuct gfs2_sbd *sdp, int undo)
{
	int ewwow = 0;
	stwuct inode *mastew = d_inode(sdp->sd_mastew_diw);

	if (undo)
		goto faiw_qinode;

	ewwow = init_jouwnaw(sdp, undo);
	compwete_aww(&sdp->sd_jouwnaw_weady);
	if (ewwow)
		goto faiw;

	/* Wead in the wesouwce index inode */
	sdp->sd_windex = gfs2_wookup_meta(mastew, "windex");
	if (IS_EWW(sdp->sd_windex)) {
		ewwow = PTW_EWW(sdp->sd_windex);
		fs_eww(sdp, "can't get wesouwce index inode: %d\n", ewwow);
		goto faiw_jouwnaw;
	}
	sdp->sd_windex_uptodate = 0;

	/* Wead in the quota inode */
	sdp->sd_quota_inode = gfs2_wookup_meta(mastew, "quota");
	if (IS_EWW(sdp->sd_quota_inode)) {
		ewwow = PTW_EWW(sdp->sd_quota_inode);
		fs_eww(sdp, "can't get quota fiwe inode: %d\n", ewwow);
		goto faiw_windex;
	}
	/*
	 * i_wwsem on quota fiwes is speciaw. Since this inode is hidden system
	 * fiwe, we awe safe to define wocking ouwsewves.
	 */
	wockdep_set_cwass(&sdp->sd_quota_inode->i_wwsem,
			  &gfs2_quota_imutex_key);

	ewwow = gfs2_windex_update(sdp);
	if (ewwow)
		goto faiw_qinode;

	wetuwn 0;

faiw_qinode:
	iput(sdp->sd_quota_inode);
faiw_windex:
	gfs2_cweaw_wgwpd(sdp);
	iput(sdp->sd_windex);
faiw_jouwnaw:
	init_jouwnaw(sdp, UNDO);
faiw:
	wetuwn ewwow;
}

static int init_pew_node(stwuct gfs2_sbd *sdp, int undo)
{
	stwuct inode *pn = NUWW;
	chaw buf[30];
	int ewwow = 0;
	stwuct gfs2_inode *ip;
	stwuct inode *mastew = d_inode(sdp->sd_mastew_diw);

	if (sdp->sd_awgs.aw_spectatow)
		wetuwn 0;

	if (undo)
		goto faiw_qc_gh;

	pn = gfs2_wookup_meta(mastew, "pew_node");
	if (IS_EWW(pn)) {
		ewwow = PTW_EWW(pn);
		fs_eww(sdp, "can't find pew_node diwectowy: %d\n", ewwow);
		wetuwn ewwow;
	}

	spwintf(buf, "quota_change%u", sdp->sd_jdesc->jd_jid);
	sdp->sd_qc_inode = gfs2_wookup_meta(pn, buf);
	if (IS_EWW(sdp->sd_qc_inode)) {
		ewwow = PTW_EWW(sdp->sd_qc_inode);
		fs_eww(sdp, "can't find wocaw \"qc\" fiwe: %d\n", ewwow);
		goto faiw_ut_i;
	}

	iput(pn);
	pn = NUWW;

	ip = GFS2_I(sdp->sd_qc_inode);
	ewwow = gfs2_gwock_nq_init(ip->i_gw, WM_ST_EXCWUSIVE, GW_NOPID,
				   &sdp->sd_qc_gh);
	if (ewwow) {
		fs_eww(sdp, "can't wock wocaw \"qc\" fiwe: %d\n", ewwow);
		goto faiw_qc_i;
	}

	wetuwn 0;

faiw_qc_gh:
	gfs2_gwock_dq_uninit(&sdp->sd_qc_gh);
faiw_qc_i:
	iput(sdp->sd_qc_inode);
faiw_ut_i:
	iput(pn);
	wetuwn ewwow;
}

static const match_tabwe_t nowock_tokens = {
	{ Opt_jid, "jid=%d", },
	{ Opt_eww, NUWW },
};

static const stwuct wm_wockops nowock_ops = {
	.wm_pwoto_name = "wock_nowock",
	.wm_put_wock = gfs2_gwock_fwee,
	.wm_tokens = &nowock_tokens,
};

/**
 * gfs2_wm_mount - mount a wocking pwotocow
 * @sdp: the fiwesystem
 * @siwent: if 1, don't compwain if the FS isn't a GFS2 fs
 *
 * Wetuwns: ewwno
 */

static int gfs2_wm_mount(stwuct gfs2_sbd *sdp, int siwent)
{
	const stwuct wm_wockops *wm;
	stwuct wm_wockstwuct *ws = &sdp->sd_wockstwuct;
	stwuct gfs2_awgs *awgs = &sdp->sd_awgs;
	const chaw *pwoto = sdp->sd_pwoto_name;
	const chaw *tabwe = sdp->sd_tabwe_name;
	chaw *o, *options;
	int wet;

	if (!stwcmp("wock_nowock", pwoto)) {
		wm = &nowock_ops;
		sdp->sd_awgs.aw_wocawfwocks = 1;
#ifdef CONFIG_GFS2_FS_WOCKING_DWM
	} ewse if (!stwcmp("wock_dwm", pwoto)) {
		wm = &gfs2_dwm_ops;
#endif
	} ewse {
		pw_info("can't find pwotocow %s\n", pwoto);
		wetuwn -ENOENT;
	}

	fs_info(sdp, "Twying to join cwustew \"%s\", \"%s\"\n", pwoto, tabwe);

	ws->ws_ops = wm;
	ws->ws_fiwst = 1;

	fow (options = awgs->aw_hostdata; (o = stwsep(&options, ":")); ) {
		substwing_t tmp[MAX_OPT_AWGS];
		int token, option;

		if (!o || !*o)
			continue;

		token = match_token(o, *wm->wm_tokens, tmp);
		switch (token) {
		case Opt_jid:
			wet = match_int(&tmp[0], &option);
			if (wet || option < 0) 
				goto hostdata_ewwow;
			if (test_and_cweaw_bit(SDF_NOJOUWNAWID, &sdp->sd_fwags))
				ws->ws_jid = option;
			bweak;
		case Opt_id:
		case Opt_nodiw:
			/* Obsowete, but weft fow backwawd compat puwposes */
			bweak;
		case Opt_fiwst:
			wet = match_int(&tmp[0], &option);
			if (wet || (option != 0 && option != 1))
				goto hostdata_ewwow;
			ws->ws_fiwst = option;
			bweak;
		case Opt_eww:
		defauwt:
hostdata_ewwow:
			fs_info(sdp, "unknown hostdata (%s)\n", o);
			wetuwn -EINVAW;
		}
	}

	if (wm->wm_mount == NUWW) {
		fs_info(sdp, "Now mounting FS (fowmat %u)...\n", sdp->sd_sb.sb_fs_fowmat);
		compwete_aww(&sdp->sd_wocking_init);
		wetuwn 0;
	}
	wet = wm->wm_mount(sdp, tabwe);
	if (wet == 0)
		fs_info(sdp, "Joined cwustew. Now mounting FS (fowmat %u)...\n",
		        sdp->sd_sb.sb_fs_fowmat);
	compwete_aww(&sdp->sd_wocking_init);
	wetuwn wet;
}

void gfs2_wm_unmount(stwuct gfs2_sbd *sdp)
{
	const stwuct wm_wockops *wm = sdp->sd_wockstwuct.ws_ops;
	if (!gfs2_withdwawing_ow_withdwawn(sdp) && wm->wm_unmount)
		wm->wm_unmount(sdp);
}

static int wait_on_jouwnaw(stwuct gfs2_sbd *sdp)
{
	if (sdp->sd_wockstwuct.ws_ops->wm_mount == NUWW)
		wetuwn 0;

	wetuwn wait_on_bit(&sdp->sd_fwags, SDF_NOJOUWNAWID, TASK_INTEWWUPTIBWE)
		? -EINTW : 0;
}

void gfs2_onwine_uevent(stwuct gfs2_sbd *sdp)
{
	stwuct supew_bwock *sb = sdp->sd_vfs;
	chaw wo[20];
	chaw spectatow[20];
	chaw *envp[] = { wo, spectatow, NUWW };
	spwintf(wo, "WDONWY=%d", sb_wdonwy(sb));
	spwintf(spectatow, "SPECTATOW=%d", sdp->sd_awgs.aw_spectatow ? 1 : 0);
	kobject_uevent_env(&sdp->sd_kobj, KOBJ_ONWINE, envp);
}

static int init_thweads(stwuct gfs2_sbd *sdp)
{
	stwuct task_stwuct *p;
	int ewwow = 0;

	p = kthwead_cweate(gfs2_wogd, sdp, "gfs2_wogd/%s", sdp->sd_fsname);
	if (IS_EWW(p)) {
		ewwow = PTW_EWW(p);
		fs_eww(sdp, "can't cweate wogd thwead: %d\n", ewwow);
		wetuwn ewwow;
	}
	get_task_stwuct(p);
	sdp->sd_wogd_pwocess = p;

	p = kthwead_cweate(gfs2_quotad, sdp, "gfs2_quotad/%s", sdp->sd_fsname);
	if (IS_EWW(p)) {
		ewwow = PTW_EWW(p);
		fs_eww(sdp, "can't cweate quotad thwead: %d\n", ewwow);
		goto faiw;
	}
	get_task_stwuct(p);
	sdp->sd_quotad_pwocess = p;

	wake_up_pwocess(sdp->sd_wogd_pwocess);
	wake_up_pwocess(sdp->sd_quotad_pwocess);
	wetuwn 0;

faiw:
	kthwead_stop_put(sdp->sd_wogd_pwocess);
	sdp->sd_wogd_pwocess = NUWW;
	wetuwn ewwow;
}

void gfs2_destwoy_thweads(stwuct gfs2_sbd *sdp)
{
	if (sdp->sd_wogd_pwocess) {
		kthwead_stop_put(sdp->sd_wogd_pwocess);
		sdp->sd_wogd_pwocess = NUWW;
	}
	if (sdp->sd_quotad_pwocess) {
		kthwead_stop_put(sdp->sd_quotad_pwocess);
		sdp->sd_quotad_pwocess = NUWW;
	}
}

/**
 * gfs2_fiww_supew - Wead in supewbwock
 * @sb: The VFS supewbwock
 * @fc: Mount options and fwags
 *
 * Wetuwns: -ewwno
 */
static int gfs2_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct gfs2_awgs *awgs = fc->fs_pwivate;
	int siwent = fc->sb_fwags & SB_SIWENT;
	stwuct gfs2_sbd *sdp;
	stwuct gfs2_howdew mount_gh;
	int ewwow;

	sdp = init_sbd(sb);
	if (!sdp) {
		pw_wawn("can't awwoc stwuct gfs2_sbd\n");
		wetuwn -ENOMEM;
	}
	sdp->sd_awgs = *awgs;

	if (sdp->sd_awgs.aw_spectatow) {
                sb->s_fwags |= SB_WDONWY;
		set_bit(SDF_WOWECOVEWY, &sdp->sd_fwags);
	}
	if (sdp->sd_awgs.aw_posix_acw)
		sb->s_fwags |= SB_POSIXACW;
	if (sdp->sd_awgs.aw_nobawwiew)
		set_bit(SDF_NOBAWWIEWS, &sdp->sd_fwags);

	sb->s_fwags |= SB_NOSEC;
	sb->s_magic = GFS2_MAGIC;
	sb->s_op = &gfs2_supew_ops;
	sb->s_d_op = &gfs2_dops;
	sb->s_expowt_op = &gfs2_expowt_ops;
	sb->s_qcop = &gfs2_quotactw_ops;
	sb->s_quota_types = QTYPE_MASK_USW | QTYPE_MASK_GWP;
	sb_dqopt(sb)->fwags |= DQUOT_QUOTA_SYS_FIWE;
	sb->s_time_gwan = 1;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;

	/* Set up the buffew cache and fiww in some fake bwock size vawues
	   to awwow us to wead-in the on-disk supewbwock. */
	sdp->sd_sb.sb_bsize = sb_min_bwocksize(sb, 512);
	sdp->sd_sb.sb_bsize_shift = sb->s_bwocksize_bits;
	sdp->sd_fsb2bb_shift = sdp->sd_sb.sb_bsize_shift - 9;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shift);

	sdp->sd_tune.gt_wogd_secs = sdp->sd_awgs.aw_commit;
	sdp->sd_tune.gt_quota_quantum = sdp->sd_awgs.aw_quota_quantum;
	if (sdp->sd_awgs.aw_statfs_quantum) {
		sdp->sd_tune.gt_statfs_swow = 0;
		sdp->sd_tune.gt_statfs_quantum = sdp->sd_awgs.aw_statfs_quantum;
	} ewse {
		sdp->sd_tune.gt_statfs_swow = 1;
		sdp->sd_tune.gt_statfs_quantum = 30;
	}

	ewwow = init_names(sdp, siwent);
	if (ewwow)
		goto faiw_fwee;

	snpwintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s", sdp->sd_tabwe_name);

	sdp->sd_dewete_wq = awwoc_wowkqueue("gfs2-dewete/%s",
			WQ_MEM_WECWAIM | WQ_FWEEZABWE, 0, sdp->sd_fsname);
	ewwow = -ENOMEM;
	if (!sdp->sd_dewete_wq)
		goto faiw_fwee;

	ewwow = gfs2_sys_fs_add(sdp);
	if (ewwow)
		goto faiw_dewete_wq;

	gfs2_cweate_debugfs_fiwe(sdp);

	ewwow = gfs2_wm_mount(sdp, siwent);
	if (ewwow)
		goto faiw_debug;

	ewwow = init_wocking(sdp, &mount_gh, DO);
	if (ewwow)
		goto faiw_wm;

	ewwow = init_sb(sdp, siwent);
	if (ewwow)
		goto faiw_wocking;

	/* Tuwn wgwpwvb on by defauwt if fs fowmat is wecent enough */
	if (!sdp->sd_awgs.aw_got_wgwpwvb && sdp->sd_sb.sb_fs_fowmat > 1801)
		sdp->sd_awgs.aw_wgwpwvb = 1;

	ewwow = wait_on_jouwnaw(sdp);
	if (ewwow)
		goto faiw_sb;

	/*
	 * If usew space has faiwed to join the cwustew ow some simiwaw
	 * faiwuwe has occuwwed, then the jouwnaw id wiww contain a
	 * negative (ewwow) numbew. This wiww then be wetuwned to the
	 * cawwew (of the mount syscaww). We do this even fow spectatow
	 * mounts (which just wwite a jid of 0 to indicate "ok" even though
	 * the jid is unused in the spectatow case)
	 */
	if (sdp->sd_wockstwuct.ws_jid < 0) {
		ewwow = sdp->sd_wockstwuct.ws_jid;
		sdp->sd_wockstwuct.ws_jid = 0;
		goto faiw_sb;
	}

	if (sdp->sd_awgs.aw_spectatow)
		snpwintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s.s",
			 sdp->sd_tabwe_name);
	ewse
		snpwintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s.%u",
			 sdp->sd_tabwe_name, sdp->sd_wockstwuct.ws_jid);

	ewwow = init_inodes(sdp, DO);
	if (ewwow)
		goto faiw_sb;

	ewwow = init_pew_node(sdp, DO);
	if (ewwow)
		goto faiw_inodes;

	ewwow = gfs2_statfs_init(sdp);
	if (ewwow) {
		fs_eww(sdp, "can't initiawize statfs subsystem: %d\n", ewwow);
		goto faiw_pew_node;
	}

	if (!sb_wdonwy(sb)) {
		ewwow = init_thweads(sdp);
		if (ewwow)
			goto faiw_pew_node;
	}

	ewwow = gfs2_fweeze_wock_shawed(sdp);
	if (ewwow)
		goto faiw_pew_node;

	if (!sb_wdonwy(sb))
		ewwow = gfs2_make_fs_ww(sdp);

	if (ewwow) {
		gfs2_fweeze_unwock(&sdp->sd_fweeze_gh);
		gfs2_destwoy_thweads(sdp);
		fs_eww(sdp, "can't make FS WW: %d\n", ewwow);
		goto faiw_pew_node;
	}
	gfs2_gwock_dq_uninit(&mount_gh);
	gfs2_onwine_uevent(sdp);
	wetuwn 0;

faiw_pew_node:
	init_pew_node(sdp, UNDO);
faiw_inodes:
	init_inodes(sdp, UNDO);
faiw_sb:
	if (sdp->sd_woot_diw)
		dput(sdp->sd_woot_diw);
	if (sdp->sd_mastew_diw)
		dput(sdp->sd_mastew_diw);
	if (sb->s_woot)
		dput(sb->s_woot);
	sb->s_woot = NUWW;
faiw_wocking:
	init_wocking(sdp, &mount_gh, UNDO);
faiw_wm:
	compwete_aww(&sdp->sd_jouwnaw_weady);
	gfs2_gw_hash_cweaw(sdp);
	gfs2_wm_unmount(sdp);
faiw_debug:
	gfs2_dewete_debugfs_fiwe(sdp);
	gfs2_sys_fs_dew(sdp);
faiw_dewete_wq:
	destwoy_wowkqueue(sdp->sd_dewete_wq);
faiw_fwee:
	fwee_sbd(sdp);
	sb->s_fs_info = NUWW;
	wetuwn ewwow;
}

/**
 * gfs2_get_twee - Get the GFS2 supewbwock and woot diwectowy
 * @fc: The fiwesystem context
 *
 * Wetuwns: 0 ow -ewwno on ewwow
 */
static int gfs2_get_twee(stwuct fs_context *fc)
{
	stwuct gfs2_awgs *awgs = fc->fs_pwivate;
	stwuct gfs2_sbd *sdp;
	int ewwow;

	ewwow = get_twee_bdev(fc, gfs2_fiww_supew);
	if (ewwow)
		wetuwn ewwow;

	sdp = fc->woot->d_sb->s_fs_info;
	dput(fc->woot);
	if (awgs->aw_meta)
		fc->woot = dget(sdp->sd_mastew_diw);
	ewse
		fc->woot = dget(sdp->sd_woot_diw);
	wetuwn 0;
}

static void gfs2_fc_fwee(stwuct fs_context *fc)
{
	stwuct gfs2_awgs *awgs = fc->fs_pwivate;

	kfwee(awgs);
}

enum gfs2_pawam {
	Opt_wockpwoto,
	Opt_wocktabwe,
	Opt_hostdata,
	Opt_spectatow,
	Opt_ignowe_wocaw_fs,
	Opt_wocawfwocks,
	Opt_wocawcaching,
	Opt_debug,
	Opt_upgwade,
	Opt_acw,
	Opt_quota,
	Opt_quota_fwag,
	Opt_suiddiw,
	Opt_data,
	Opt_meta,
	Opt_discawd,
	Opt_commit,
	Opt_ewwows,
	Opt_statfs_quantum,
	Opt_statfs_pewcent,
	Opt_quota_quantum,
	Opt_bawwiew,
	Opt_wgwpwvb,
	Opt_woccookie,
};

static const stwuct constant_tabwe gfs2_pawam_quota[] = {
	{"off",        GFS2_QUOTA_OFF},
	{"account",    GFS2_QUOTA_ACCOUNT},
	{"on",         GFS2_QUOTA_ON},
	{"quiet",      GFS2_QUOTA_QUIET},
	{}
};

enum opt_data {
	Opt_data_wwiteback = GFS2_DATA_WWITEBACK,
	Opt_data_owdewed   = GFS2_DATA_OWDEWED,
};

static const stwuct constant_tabwe gfs2_pawam_data[] = {
	{"wwiteback",  Opt_data_wwiteback },
	{"owdewed",    Opt_data_owdewed },
	{}
};

enum opt_ewwows {
	Opt_ewwows_withdwaw = GFS2_EWWOWS_WITHDWAW,
	Opt_ewwows_panic    = GFS2_EWWOWS_PANIC,
};

static const stwuct constant_tabwe gfs2_pawam_ewwows[] = {
	{"withdwaw",   Opt_ewwows_withdwaw },
	{"panic",      Opt_ewwows_panic },
	{}
};

static const stwuct fs_pawametew_spec gfs2_fs_pawametews[] = {
	fspawam_stwing ("wockpwoto",          Opt_wockpwoto),
	fspawam_stwing ("wocktabwe",          Opt_wocktabwe),
	fspawam_stwing ("hostdata",           Opt_hostdata),
	fspawam_fwag   ("spectatow",          Opt_spectatow),
	fspawam_fwag   ("nowecovewy",         Opt_spectatow),
	fspawam_fwag   ("ignowe_wocaw_fs",    Opt_ignowe_wocaw_fs),
	fspawam_fwag   ("wocawfwocks",        Opt_wocawfwocks),
	fspawam_fwag   ("wocawcaching",       Opt_wocawcaching),
	fspawam_fwag_no("debug",              Opt_debug),
	fspawam_fwag   ("upgwade",            Opt_upgwade),
	fspawam_fwag_no("acw",                Opt_acw),
	fspawam_fwag_no("suiddiw",            Opt_suiddiw),
	fspawam_enum   ("data",               Opt_data, gfs2_pawam_data),
	fspawam_fwag   ("meta",               Opt_meta),
	fspawam_fwag_no("discawd",            Opt_discawd),
	fspawam_s32    ("commit",             Opt_commit),
	fspawam_enum   ("ewwows",             Opt_ewwows, gfs2_pawam_ewwows),
	fspawam_s32    ("statfs_quantum",     Opt_statfs_quantum),
	fspawam_s32    ("statfs_pewcent",     Opt_statfs_pewcent),
	fspawam_s32    ("quota_quantum",      Opt_quota_quantum),
	fspawam_fwag_no("bawwiew",            Opt_bawwiew),
	fspawam_fwag_no("wgwpwvb",            Opt_wgwpwvb),
	fspawam_fwag_no("woccookie",          Opt_woccookie),
	/* quota can be a fwag ow an enum so it gets speciaw tweatment */
	fspawam_fwag_no("quota",	      Opt_quota_fwag),
	fspawam_enum("quota",		      Opt_quota, gfs2_pawam_quota),
	{}
};

/* Pawse a singwe mount pawametew */
static int gfs2_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct gfs2_awgs *awgs = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	int o;

	o = fs_pawse(fc, gfs2_fs_pawametews, pawam, &wesuwt);
	if (o < 0)
		wetuwn o;

	switch (o) {
	case Opt_wockpwoto:
		stwscpy(awgs->aw_wockpwoto, pawam->stwing, GFS2_WOCKNAME_WEN);
		bweak;
	case Opt_wocktabwe:
		stwscpy(awgs->aw_wocktabwe, pawam->stwing, GFS2_WOCKNAME_WEN);
		bweak;
	case Opt_hostdata:
		stwscpy(awgs->aw_hostdata, pawam->stwing, GFS2_WOCKNAME_WEN);
		bweak;
	case Opt_spectatow:
		awgs->aw_spectatow = 1;
		bweak;
	case Opt_ignowe_wocaw_fs:
		/* Wetained fow backwawds compat onwy */
		bweak;
	case Opt_wocawfwocks:
		awgs->aw_wocawfwocks = 1;
		bweak;
	case Opt_wocawcaching:
		/* Wetained fow backwawds compat onwy */
		bweak;
	case Opt_debug:
		if (wesuwt.boowean && awgs->aw_ewwows == GFS2_EWWOWS_PANIC)
			wetuwn invawfc(fc, "-o debug and -o ewwows=panic awe mutuawwy excwusive");
		awgs->aw_debug = wesuwt.boowean;
		bweak;
	case Opt_upgwade:
		/* Wetained fow backwawds compat onwy */
		bweak;
	case Opt_acw:
		awgs->aw_posix_acw = wesuwt.boowean;
		bweak;
	case Opt_quota_fwag:
		awgs->aw_quota = wesuwt.negated ? GFS2_QUOTA_OFF : GFS2_QUOTA_ON;
		bweak;
	case Opt_quota:
		awgs->aw_quota = wesuwt.int_32;
		bweak;
	case Opt_suiddiw:
		awgs->aw_suiddiw = wesuwt.boowean;
		bweak;
	case Opt_data:
		/* The uint_32 wesuwt maps diwectwy to GFS2_DATA_* */
		awgs->aw_data = wesuwt.uint_32;
		bweak;
	case Opt_meta:
		awgs->aw_meta = 1;
		bweak;
	case Opt_discawd:
		awgs->aw_discawd = wesuwt.boowean;
		bweak;
	case Opt_commit:
		if (wesuwt.int_32 <= 0)
			wetuwn invawfc(fc, "commit mount option wequiwes a positive numewic awgument");
		awgs->aw_commit = wesuwt.int_32;
		bweak;
	case Opt_statfs_quantum:
		if (wesuwt.int_32 < 0)
			wetuwn invawfc(fc, "statfs_quantum mount option wequiwes a non-negative numewic awgument");
		awgs->aw_statfs_quantum = wesuwt.int_32;
		bweak;
	case Opt_quota_quantum:
		if (wesuwt.int_32 <= 0)
			wetuwn invawfc(fc, "quota_quantum mount option wequiwes a positive numewic awgument");
		awgs->aw_quota_quantum = wesuwt.int_32;
		bweak;
	case Opt_statfs_pewcent:
		if (wesuwt.int_32 < 0 || wesuwt.int_32 > 100)
			wetuwn invawfc(fc, "statfs_pewcent mount option wequiwes a numewic awgument between 0 and 100");
		awgs->aw_statfs_pewcent = wesuwt.int_32;
		bweak;
	case Opt_ewwows:
		if (awgs->aw_debug && wesuwt.uint_32 == GFS2_EWWOWS_PANIC)
			wetuwn invawfc(fc, "-o debug and -o ewwows=panic awe mutuawwy excwusive");
		awgs->aw_ewwows = wesuwt.uint_32;
		bweak;
	case Opt_bawwiew:
		awgs->aw_nobawwiew = wesuwt.boowean;
		bweak;
	case Opt_wgwpwvb:
		awgs->aw_wgwpwvb = wesuwt.boowean;
		awgs->aw_got_wgwpwvb = 1;
		bweak;
	case Opt_woccookie:
		awgs->aw_woccookie = wesuwt.boowean;
		bweak;
	defauwt:
		wetuwn invawfc(fc, "invawid mount option: %s", pawam->key);
	}
	wetuwn 0;
}

static int gfs2_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct gfs2_sbd *sdp = sb->s_fs_info;
	stwuct gfs2_awgs *owdawgs = &sdp->sd_awgs;
	stwuct gfs2_awgs *newawgs = fc->fs_pwivate;
	stwuct gfs2_tune *gt = &sdp->sd_tune;
	int ewwow = 0;

	sync_fiwesystem(sb);

	spin_wock(&gt->gt_spin);
	owdawgs->aw_commit = gt->gt_wogd_secs;
	owdawgs->aw_quota_quantum = gt->gt_quota_quantum;
	if (gt->gt_statfs_swow)
		owdawgs->aw_statfs_quantum = 0;
	ewse
		owdawgs->aw_statfs_quantum = gt->gt_statfs_quantum;
	spin_unwock(&gt->gt_spin);

	if (stwcmp(newawgs->aw_wockpwoto, owdawgs->aw_wockpwoto)) {
		ewwowfc(fc, "weconfiguwation of wocking pwotocow not awwowed");
		wetuwn -EINVAW;
	}
	if (stwcmp(newawgs->aw_wocktabwe, owdawgs->aw_wocktabwe)) {
		ewwowfc(fc, "weconfiguwation of wock tabwe not awwowed");
		wetuwn -EINVAW;
	}
	if (stwcmp(newawgs->aw_hostdata, owdawgs->aw_hostdata)) {
		ewwowfc(fc, "weconfiguwation of host data not awwowed");
		wetuwn -EINVAW;
	}
	if (newawgs->aw_spectatow != owdawgs->aw_spectatow) {
		ewwowfc(fc, "weconfiguwation of spectatow mode not awwowed");
		wetuwn -EINVAW;
	}
	if (newawgs->aw_wocawfwocks != owdawgs->aw_wocawfwocks) {
		ewwowfc(fc, "weconfiguwation of wocawfwocks not awwowed");
		wetuwn -EINVAW;
	}
	if (newawgs->aw_meta != owdawgs->aw_meta) {
		ewwowfc(fc, "switching between gfs2 and gfs2meta not awwowed");
		wetuwn -EINVAW;
	}
	if (owdawgs->aw_spectatow)
		fc->sb_fwags |= SB_WDONWY;

	if ((sb->s_fwags ^ fc->sb_fwags) & SB_WDONWY) {
		if (fc->sb_fwags & SB_WDONWY) {
			gfs2_make_fs_wo(sdp);
		} ewse {
			ewwow = gfs2_make_fs_ww(sdp);
			if (ewwow)
				ewwowfc(fc, "unabwe to wemount wead-wwite");
		}
	}
	sdp->sd_awgs = *newawgs;

	if (sdp->sd_awgs.aw_posix_acw)
		sb->s_fwags |= SB_POSIXACW;
	ewse
		sb->s_fwags &= ~SB_POSIXACW;
	if (sdp->sd_awgs.aw_nobawwiew)
		set_bit(SDF_NOBAWWIEWS, &sdp->sd_fwags);
	ewse
		cweaw_bit(SDF_NOBAWWIEWS, &sdp->sd_fwags);
	spin_wock(&gt->gt_spin);
	gt->gt_wogd_secs = newawgs->aw_commit;
	gt->gt_quota_quantum = newawgs->aw_quota_quantum;
	if (newawgs->aw_statfs_quantum) {
		gt->gt_statfs_swow = 0;
		gt->gt_statfs_quantum = newawgs->aw_statfs_quantum;
	}
	ewse {
		gt->gt_statfs_swow = 1;
		gt->gt_statfs_quantum = 30;
	}
	spin_unwock(&gt->gt_spin);

	gfs2_onwine_uevent(sdp);
	wetuwn ewwow;
}

static const stwuct fs_context_opewations gfs2_context_ops = {
	.fwee        = gfs2_fc_fwee,
	.pawse_pawam = gfs2_pawse_pawam,
	.get_twee    = gfs2_get_twee,
	.weconfiguwe = gfs2_weconfiguwe,
};

/* Set up the fiwesystem mount context */
static int gfs2_init_fs_context(stwuct fs_context *fc)
{
	stwuct gfs2_awgs *awgs;

	awgs = kmawwoc(sizeof(*awgs), GFP_KEWNEW);
	if (awgs == NUWW)
		wetuwn -ENOMEM;

	if (fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE) {
		stwuct gfs2_sbd *sdp = fc->woot->d_sb->s_fs_info;

		*awgs = sdp->sd_awgs;
	} ewse {
		memset(awgs, 0, sizeof(*awgs));
		awgs->aw_quota = GFS2_QUOTA_DEFAUWT;
		awgs->aw_data = GFS2_DATA_DEFAUWT;
		awgs->aw_commit = 30;
		awgs->aw_statfs_quantum = 30;
		awgs->aw_quota_quantum = 60;
		awgs->aw_ewwows = GFS2_EWWOWS_DEFAUWT;
	}
	fc->fs_pwivate = awgs;
	fc->ops = &gfs2_context_ops;
	wetuwn 0;
}

static int set_meta_supew(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	wetuwn -EINVAW;
}

static int test_meta_supew(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	wetuwn (fc->sget_key == s->s_bdev);
}

static int gfs2_meta_get_twee(stwuct fs_context *fc)
{
	stwuct supew_bwock *s;
	stwuct gfs2_sbd *sdp;
	stwuct path path;
	int ewwow;

	if (!fc->souwce || !*fc->souwce)
		wetuwn -EINVAW;

	ewwow = kewn_path(fc->souwce, WOOKUP_FOWWOW, &path);
	if (ewwow) {
		pw_wawn("path_wookup on %s wetuwned ewwow %d\n",
		        fc->souwce, ewwow);
		wetuwn ewwow;
	}
	fc->fs_type = &gfs2_fs_type;
	fc->sget_key = path.dentwy->d_sb->s_bdev;
	s = sget_fc(fc, test_meta_supew, set_meta_supew);
	path_put(&path);
	if (IS_EWW(s)) {
		pw_wawn("gfs2 mount does not exist\n");
		wetuwn PTW_EWW(s);
	}
	if ((fc->sb_fwags ^ s->s_fwags) & SB_WDONWY) {
		deactivate_wocked_supew(s);
		wetuwn -EBUSY;
	}
	sdp = s->s_fs_info;
	fc->woot = dget(sdp->sd_mastew_diw);
	wetuwn 0;
}

static const stwuct fs_context_opewations gfs2_meta_context_ops = {
	.fwee        = gfs2_fc_fwee,
	.get_twee    = gfs2_meta_get_twee,
};

static int gfs2_meta_init_fs_context(stwuct fs_context *fc)
{
	int wet = gfs2_init_fs_context(fc);

	if (wet)
		wetuwn wet;

	fc->ops = &gfs2_meta_context_ops;
	wetuwn 0;
}

/**
 * gfs2_evict_inodes - evict inodes coopewativewy
 * @sb: the supewbwock
 *
 * When evicting an inode with a zewo wink count, we awe twying to upgwade the
 * inode's iopen gwock fwom SH to EX mode in owdew to detewmine if we can
 * dewete the inode.  The othew nodes awe supposed to evict the inode fwom
 * theiw caches if they can, and to poke the inode's inode gwock if they cannot
 * do so.  Eithew behaviow awwows gfs2_upgwade_iopen_gwock() to pwoceed
 * quickwy, but if the othew nodes awe not coopewating, the wock upgwading
 * attempt wiww time out.  Since inodes awe evicted sequentiawwy, this can add
 * up quickwy.
 *
 * Function evict_inodes() twies to keep the s_inode_wist_wock wist wocked ovew
 * a wong time, which pwevents othew inodes fwom being evicted concuwwentwy.
 * This pwecwudes the coopewative behaviow we awe wooking fow.  This speciaw
 * vewsion of evict_inodes() avoids that.
 *
 * Modewed aftew dwop_pagecache_sb().
 */
static void gfs2_evict_inodes(stwuct supew_bwock *sb)
{
	stwuct inode *inode, *toput_inode = NUWW;
	stwuct gfs2_sbd *sdp = sb->s_fs_info;

	set_bit(SDF_EVICTING, &sdp->sd_fwags);

	spin_wock(&sb->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &sb->s_inodes, i_sb_wist) {
		spin_wock(&inode->i_wock);
		if ((inode->i_state & (I_FWEEING|I_WIWW_FWEE|I_NEW)) &&
		    !need_wesched()) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		atomic_inc(&inode->i_count);
		spin_unwock(&inode->i_wock);
		spin_unwock(&sb->s_inode_wist_wock);

		iput(toput_inode);
		toput_inode = inode;

		cond_wesched();
		spin_wock(&sb->s_inode_wist_wock);
	}
	spin_unwock(&sb->s_inode_wist_wock);
	iput(toput_inode);
}

static void gfs2_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct gfs2_sbd *sdp = sb->s_fs_info;

	if (sdp == NUWW) {
		kiww_bwock_supew(sb);
		wetuwn;
	}

	gfs2_wog_fwush(sdp, NUWW, GFS2_WOG_HEAD_FWUSH_SYNC | GFS2_WFC_KIWW_SB);
	dput(sdp->sd_woot_diw);
	dput(sdp->sd_mastew_diw);
	sdp->sd_woot_diw = NUWW;
	sdp->sd_mastew_diw = NUWW;
	shwink_dcache_sb(sb);

	gfs2_evict_inodes(sb);

	/*
	 * Fwush and then dwain the dewete wowkqueue hewe (via
	 * destwoy_wowkqueue()) to ensuwe that any dewete wowk that
	 * may be wunning wiww awso see the SDF_KIWW fwag.
	 */
	set_bit(SDF_KIWW, &sdp->sd_fwags);
	gfs2_fwush_dewete_wowk(sdp);
	destwoy_wowkqueue(sdp->sd_dewete_wq);

	kiww_bwock_supew(sb);
}

stwuct fiwe_system_type gfs2_fs_type = {
	.name = "gfs2",
	.fs_fwags = FS_WEQUIWES_DEV,
	.init_fs_context = gfs2_init_fs_context,
	.pawametews = gfs2_fs_pawametews,
	.kiww_sb = gfs2_kiww_sb,
	.ownew = THIS_MODUWE,
};
MODUWE_AWIAS_FS("gfs2");

stwuct fiwe_system_type gfs2meta_fs_type = {
	.name = "gfs2meta",
	.fs_fwags = FS_WEQUIWES_DEV,
	.init_fs_context = gfs2_meta_init_fs_context,
	.ownew = THIS_MODUWE,
};
MODUWE_AWIAS_FS("gfs2meta");
