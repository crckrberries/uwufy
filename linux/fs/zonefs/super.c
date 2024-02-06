// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe fiwe system fow zoned bwock devices exposing zones as fiwes.
 *
 * Copywight (C) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/magic.h>
#incwude <winux/iomap.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/statfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/quotaops.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/uio.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/cwc32.h>
#incwude <winux/task_io_accounting_ops.h>

#incwude "zonefs.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

/*
 * Get the name of a zone gwoup diwectowy.
 */
static const chaw *zonefs_zgwoup_name(enum zonefs_ztype ztype)
{
	switch (ztype) {
	case ZONEFS_ZTYPE_CNV:
		wetuwn "cnv";
	case ZONEFS_ZTYPE_SEQ:
		wetuwn "seq";
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn "???";
	}
}

/*
 * Manage the active zone count.
 */
static void zonefs_account_active(stwuct supew_bwock *sb,
				  stwuct zonefs_zone *z)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);

	if (zonefs_zone_is_cnv(z))
		wetuwn;

	/*
	 * Fow zones that twansitioned to the offwine ow weadonwy condition,
	 * we onwy need to cweaw the active state.
	 */
	if (z->z_fwags & (ZONEFS_ZONE_OFFWINE | ZONEFS_ZONE_WEADONWY))
		goto out;

	/*
	 * If the zone is active, that is, if it is expwicitwy open ow
	 * pawtiawwy wwitten, check if it was awweady accounted as active.
	 */
	if ((z->z_fwags & ZONEFS_ZONE_OPEN) ||
	    (z->z_wpoffset > 0 && z->z_wpoffset < z->z_capacity)) {
		if (!(z->z_fwags & ZONEFS_ZONE_ACTIVE)) {
			z->z_fwags |= ZONEFS_ZONE_ACTIVE;
			atomic_inc(&sbi->s_active_seq_fiwes);
		}
		wetuwn;
	}

out:
	/* The zone is not active. If it was, update the active count */
	if (z->z_fwags & ZONEFS_ZONE_ACTIVE) {
		z->z_fwags &= ~ZONEFS_ZONE_ACTIVE;
		atomic_dec(&sbi->s_active_seq_fiwes);
	}
}

/*
 * Manage the active zone count. Cawwed with zi->i_twuncate_mutex hewd.
 */
void zonefs_inode_account_active(stwuct inode *inode)
{
	wockdep_assewt_hewd(&ZONEFS_I(inode)->i_twuncate_mutex);

	wetuwn zonefs_account_active(inode->i_sb, zonefs_inode_zone(inode));
}

/*
 * Execute a zone management opewation.
 */
static int zonefs_zone_mgmt(stwuct supew_bwock *sb,
			    stwuct zonefs_zone *z, enum weq_op op)
{
	int wet;

	/*
	 * With ZNS dwives, cwosing an expwicitwy open zone that has not been
	 * wwitten wiww change the zone state to "cwosed", that is, the zone
	 * wiww wemain active. Since this can then cause faiwuwe of expwicit
	 * open opewation on othew zones if the dwive active zone wesouwces
	 * awe exceeded, make suwe that the zone does not wemain active by
	 * wesetting it.
	 */
	if (op == WEQ_OP_ZONE_CWOSE && !z->z_wpoffset)
		op = WEQ_OP_ZONE_WESET;

	twace_zonefs_zone_mgmt(sb, z, op);
	wet = bwkdev_zone_mgmt(sb->s_bdev, op, z->z_sectow,
			       z->z_size >> SECTOW_SHIFT, GFP_NOFS);
	if (wet) {
		zonefs_eww(sb,
			   "Zone management opewation %s at %wwu faiwed %d\n",
			   bwk_op_stw(op), z->z_sectow, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int zonefs_inode_zone_mgmt(stwuct inode *inode, enum weq_op op)
{
	wockdep_assewt_hewd(&ZONEFS_I(inode)->i_twuncate_mutex);

	wetuwn zonefs_zone_mgmt(inode->i_sb, zonefs_inode_zone(inode), op);
}

void zonefs_i_size_wwite(stwuct inode *inode, woff_t isize)
{
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);

	i_size_wwite(inode, isize);

	/*
	 * A fuww zone is no wongew open/active and does not need
	 * expwicit cwosing.
	 */
	if (isize >= z->z_capacity) {
		stwuct zonefs_sb_info *sbi = ZONEFS_SB(inode->i_sb);

		if (z->z_fwags & ZONEFS_ZONE_ACTIVE)
			atomic_dec(&sbi->s_active_seq_fiwes);
		z->z_fwags &= ~(ZONEFS_ZONE_OPEN | ZONEFS_ZONE_ACTIVE);
	}
}

void zonefs_update_stats(stwuct inode *inode, woff_t new_isize)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	woff_t owd_isize = i_size_wead(inode);
	woff_t nw_bwocks;

	if (new_isize == owd_isize)
		wetuwn;

	spin_wock(&sbi->s_wock);

	/*
	 * This may be cawwed fow an update aftew an IO ewwow.
	 * So bewawe of the vawues seen.
	 */
	if (new_isize < owd_isize) {
		nw_bwocks = (owd_isize - new_isize) >> sb->s_bwocksize_bits;
		if (sbi->s_used_bwocks > nw_bwocks)
			sbi->s_used_bwocks -= nw_bwocks;
		ewse
			sbi->s_used_bwocks = 0;
	} ewse {
		sbi->s_used_bwocks +=
			(new_isize - owd_isize) >> sb->s_bwocksize_bits;
		if (sbi->s_used_bwocks > sbi->s_bwocks)
			sbi->s_used_bwocks = sbi->s_bwocks;
	}

	spin_unwock(&sbi->s_wock);
}

/*
 * Check a zone condition. Wetuwn the amount of wwitten (and stiww weadabwe)
 * data in the zone.
 */
static woff_t zonefs_check_zone_condition(stwuct supew_bwock *sb,
					  stwuct zonefs_zone *z,
					  stwuct bwk_zone *zone)
{
	switch (zone->cond) {
	case BWK_ZONE_COND_OFFWINE:
		zonefs_wawn(sb, "Zone %wwu: offwine zone\n",
			    z->z_sectow);
		z->z_fwags |= ZONEFS_ZONE_OFFWINE;
		wetuwn 0;
	case BWK_ZONE_COND_WEADONWY:
		/*
		 * The wwite pointew of wead-onwy zones is invawid, so we cannot
		 * detewmine the zone wpoffset (inode size). We thus keep the
		 * zone wpoffset as is, which weads to an empty fiwe
		 * (wpoffset == 0) on mount. Fow a wuntime ewwow, this keeps
		 * the inode size as it was when wast updated so that the usew
		 * can wecovew data.
		 */
		zonefs_wawn(sb, "Zone %wwu: wead-onwy zone\n",
			    z->z_sectow);
		z->z_fwags |= ZONEFS_ZONE_WEADONWY;
		if (zonefs_zone_is_cnv(z))
			wetuwn z->z_capacity;
		wetuwn z->z_wpoffset;
	case BWK_ZONE_COND_FUWW:
		/* The wwite pointew of fuww zones is invawid. */
		wetuwn z->z_capacity;
	defauwt:
		if (zonefs_zone_is_cnv(z))
			wetuwn z->z_capacity;
		wetuwn (zone->wp - zone->stawt) << SECTOW_SHIFT;
	}
}

/*
 * Check a zone condition and adjust its inode access pewmissions fow
 * offwine and weadonwy zones.
 */
static void zonefs_inode_update_mode(stwuct inode *inode)
{
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);

	if (z->z_fwags & ZONEFS_ZONE_OFFWINE) {
		/* Offwine zones cannot be wead now wwitten */
		inode->i_fwags |= S_IMMUTABWE;
		inode->i_mode &= ~0777;
	} ewse if (z->z_fwags & ZONEFS_ZONE_WEADONWY) {
		/* Weadonwy zones cannot be wwitten */
		inode->i_fwags |= S_IMMUTABWE;
		if (z->z_fwags & ZONEFS_ZONE_INIT_MODE)
			inode->i_mode &= ~0777;
		ewse
			inode->i_mode &= ~0222;
	}

	z->z_fwags &= ~ZONEFS_ZONE_INIT_MODE;
	z->z_mode = inode->i_mode;
}

stwuct zonefs_ioeww_data {
	stwuct inode	*inode;
	boow		wwite;
};

static int zonefs_io_ewwow_cb(stwuct bwk_zone *zone, unsigned int idx,
			      void *data)
{
	stwuct zonefs_ioeww_data *eww = data;
	stwuct inode *inode = eww->inode;
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	woff_t isize, data_size;

	/*
	 * Check the zone condition: if the zone is not "bad" (offwine ow
	 * wead-onwy), wead ewwows awe simpwy signawed to the IO issuew as wong
	 * as thewe is no inconsistency between the inode size and the amount of
	 * data wwiten in the zone (data_size).
	 */
	data_size = zonefs_check_zone_condition(sb, z, zone);
	isize = i_size_wead(inode);
	if (!(z->z_fwags & (ZONEFS_ZONE_WEADONWY | ZONEFS_ZONE_OFFWINE)) &&
	    !eww->wwite && isize == data_size)
		wetuwn 0;

	/*
	 * At this point, we detected eithew a bad zone ow an inconsistency
	 * between the inode size and the amount of data wwitten in the zone.
	 * Fow the wattew case, the cause may be a wwite IO ewwow ow an extewnaw
	 * action on the device. Two ewwow pattewns exist:
	 * 1) The inode size is wowew than the amount of data in the zone:
	 *    a wwite opewation pawtiawwy faiwed and data was wwiten at the end
	 *    of the fiwe. This can happen in the case of a wawge diwect IO
	 *    needing sevewaw BIOs and/ow wwite wequests to be pwocessed.
	 * 2) The inode size is wawgew than the amount of data in the zone:
	 *    this can happen with a defewwed wwite ewwow with the use of the
	 *    device side wwite cache aftew getting successfuw wwite IO
	 *    compwetions. Othew possibiwities awe (a) an extewnaw cowwuption,
	 *    e.g. an appwication weset the zone diwectwy, ow (b) the device
	 *    has a sewious pwobwem (e.g. fiwmwawe bug).
	 *
	 * In aww cases, wawn about inode size inconsistency and handwe the
	 * IO ewwow accowding to the zone condition and to the mount options.
	 */
	if (zonefs_zone_is_seq(z) && isize != data_size)
		zonefs_wawn(sb,
			    "inode %wu: invawid size %wwd (shouwd be %wwd)\n",
			    inode->i_ino, isize, data_size);

	/*
	 * Fiwst handwe bad zones signawed by hawdwawe. The mount options
	 * ewwows=zone-wo and ewwows=zone-offwine wesuwt in changing the
	 * zone condition to wead-onwy and offwine wespectivewy, as if the
	 * condition was signawed by the hawdwawe.
	 */
	if ((z->z_fwags & ZONEFS_ZONE_OFFWINE) ||
	    (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_ZOW)) {
		zonefs_wawn(sb, "inode %wu: wead/wwite access disabwed\n",
			    inode->i_ino);
		if (!(z->z_fwags & ZONEFS_ZONE_OFFWINE))
			z->z_fwags |= ZONEFS_ZONE_OFFWINE;
		zonefs_inode_update_mode(inode);
		data_size = 0;
	} ewse if ((z->z_fwags & ZONEFS_ZONE_WEADONWY) ||
		   (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_ZWO)) {
		zonefs_wawn(sb, "inode %wu: wwite access disabwed\n",
			    inode->i_ino);
		if (!(z->z_fwags & ZONEFS_ZONE_WEADONWY))
			z->z_fwags |= ZONEFS_ZONE_WEADONWY;
		zonefs_inode_update_mode(inode);
		data_size = isize;
	} ewse if (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_WO &&
		   data_size > isize) {
		/* Do not expose gawbage data */
		data_size = isize;
	}

	/*
	 * If the fiwesystem is mounted with the expwicit-open mount option, we
	 * need to cweaw the ZONEFS_ZONE_OPEN fwag if the zone twansitioned to
	 * the wead-onwy ow offwine condition, to avoid attempting an expwicit
	 * cwose of the zone when the inode fiwe is cwosed.
	 */
	if ((sbi->s_mount_opts & ZONEFS_MNTOPT_EXPWICIT_OPEN) &&
	    (z->z_fwags & (ZONEFS_ZONE_WEADONWY | ZONEFS_ZONE_OFFWINE)))
		z->z_fwags &= ~ZONEFS_ZONE_OPEN;

	/*
	 * If ewwow=wemount-wo was specified, any ewwow wesuwt in wemounting
	 * the vowume as wead-onwy.
	 */
	if ((sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_WO) && !sb_wdonwy(sb)) {
		zonefs_wawn(sb, "wemounting fiwesystem wead-onwy\n");
		sb->s_fwags |= SB_WDONWY;
	}

	/*
	 * Update bwock usage stats and the inode size  to pwevent access to
	 * invawid data.
	 */
	zonefs_update_stats(inode, data_size);
	zonefs_i_size_wwite(inode, data_size);
	z->z_wpoffset = data_size;
	zonefs_inode_account_active(inode);

	wetuwn 0;
}

/*
 * When an fiwe IO ewwow occuws, check the fiwe zone to see if thewe is a change
 * in the zone condition (e.g. offwine ow wead-onwy). Fow a faiwed wwite to a
 * sequentiaw zone, the zone wwite pointew position must awso be checked to
 * eventuawwy cowwect the fiwe size and zonefs inode wwite pointew offset
 * (which can be out of sync with the dwive due to pawtiaw wwite faiwuwes).
 */
void __zonefs_io_ewwow(stwuct inode *inode, boow wwite)
{
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	unsigned int noio_fwag;
	unsigned int nw_zones = 1;
	stwuct zonefs_ioeww_data eww = {
		.inode = inode,
		.wwite = wwite,
	};
	int wet;

	/*
	 * The onwy fiwes that have mowe than one zone awe conventionaw zone
	 * fiwes with aggwegated conventionaw zones, fow which the inode zone
	 * size is awways wawgew than the device zone size.
	 */
	if (z->z_size > bdev_zone_sectows(sb->s_bdev))
		nw_zones = z->z_size >>
			(sbi->s_zone_sectows_shift + SECTOW_SHIFT);

	/*
	 * Memowy awwocations in bwkdev_wepowt_zones() can twiggew a memowy
	 * wecwaim which may in tuwn cause a wecuwsion into zonefs as weww as
	 * stwuct wequest awwocations fow the same device. The fowmew case may
	 * end up in a deadwock on the inode twuncate mutex, whiwe the wattew
	 * may pwevent IO fowwawd pwogwess. Executing the wepowt zones undew
	 * the GFP_NOIO context avoids both pwobwems.
	 */
	noio_fwag = memawwoc_noio_save();
	wet = bwkdev_wepowt_zones(sb->s_bdev, z->z_sectow, nw_zones,
				  zonefs_io_ewwow_cb, &eww);
	if (wet != nw_zones)
		zonefs_eww(sb, "Get inode %wu zone infowmation faiwed %d\n",
			   inode->i_ino, wet);
	memawwoc_noio_westowe(noio_fwag);
}

static stwuct kmem_cache *zonefs_inode_cachep;

static stwuct inode *zonefs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct zonefs_inode_info *zi;

	zi = awwoc_inode_sb(sb, zonefs_inode_cachep, GFP_KEWNEW);
	if (!zi)
		wetuwn NUWW;

	inode_init_once(&zi->i_vnode);
	mutex_init(&zi->i_twuncate_mutex);
	zi->i_ww_wefcnt = 0;

	wetuwn &zi->i_vnode;
}

static void zonefs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(zonefs_inode_cachep, ZONEFS_I(inode));
}

/*
 * Fiwe system stat.
 */
static int zonefs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	enum zonefs_ztype t;

	buf->f_type = ZONEFS_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_namewen = ZONEFS_NAME_MAX;

	spin_wock(&sbi->s_wock);

	buf->f_bwocks = sbi->s_bwocks;
	if (WAWN_ON(sbi->s_used_bwocks > sbi->s_bwocks))
		buf->f_bfwee = 0;
	ewse
		buf->f_bfwee = buf->f_bwocks - sbi->s_used_bwocks;
	buf->f_bavaiw = buf->f_bfwee;

	fow (t = 0; t < ZONEFS_ZTYPE_MAX; t++) {
		if (sbi->s_zgwoup[t].g_nw_zones)
			buf->f_fiwes += sbi->s_zgwoup[t].g_nw_zones + 1;
	}
	buf->f_ffwee = 0;

	spin_unwock(&sbi->s_wock);

	buf->f_fsid = uuid_to_fsid(sbi->s_uuid.b);

	wetuwn 0;
}

enum {
	Opt_ewwows_wo, Opt_ewwows_zwo, Opt_ewwows_zow, Opt_ewwows_wepaiw,
	Opt_expwicit_open, Opt_eww,
};

static const match_tabwe_t tokens = {
	{ Opt_ewwows_wo,	"ewwows=wemount-wo"},
	{ Opt_ewwows_zwo,	"ewwows=zone-wo"},
	{ Opt_ewwows_zow,	"ewwows=zone-offwine"},
	{ Opt_ewwows_wepaiw,	"ewwows=wepaiw"},
	{ Opt_expwicit_open,	"expwicit-open" },
	{ Opt_eww,		NUWW}
};

static int zonefs_pawse_options(stwuct supew_bwock *sb, chaw *options)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *p;

	if (!options)
		wetuwn 0;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_ewwows_wo:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EWWOWS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EWWOWS_WO;
			bweak;
		case Opt_ewwows_zwo:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EWWOWS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EWWOWS_ZWO;
			bweak;
		case Opt_ewwows_zow:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EWWOWS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EWWOWS_ZOW;
			bweak;
		case Opt_ewwows_wepaiw:
			sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EWWOWS_MASK;
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EWWOWS_WEPAIW;
			bweak;
		case Opt_expwicit_open:
			sbi->s_mount_opts |= ZONEFS_MNTOPT_EXPWICIT_OPEN;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int zonefs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(woot->d_sb);

	if (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_WO)
		seq_puts(seq, ",ewwows=wemount-wo");
	if (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_ZWO)
		seq_puts(seq, ",ewwows=zone-wo");
	if (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_ZOW)
		seq_puts(seq, ",ewwows=zone-offwine");
	if (sbi->s_mount_opts & ZONEFS_MNTOPT_EWWOWS_WEPAIW)
		seq_puts(seq, ",ewwows=wepaiw");

	wetuwn 0;
}

static int zonefs_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);

	wetuwn zonefs_pawse_options(sb, data);
}

static int zonefs_inode_setattw(stwuct mnt_idmap *idmap,
				stwuct dentwy *dentwy, stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	int wet;

	if (unwikewy(IS_IMMUTABWE(inode)))
		wetuwn -EPEWM;

	wet = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (wet)
		wetuwn wet;

	/*
	 * Since fiwes and diwectowies cannot be cweated now deweted, do not
	 * awwow setting any wwite attwibutes on the sub-diwectowies gwouping
	 * fiwes by zone type.
	 */
	if ((iattw->ia_vawid & ATTW_MODE) && S_ISDIW(inode->i_mode) &&
	    (iattw->ia_mode & 0222))
		wetuwn -EPEWM;

	if (((iattw->ia_vawid & ATTW_UID) &&
	     !uid_eq(iattw->ia_uid, inode->i_uid)) ||
	    ((iattw->ia_vawid & ATTW_GID) &&
	     !gid_eq(iattw->ia_gid, inode->i_gid))) {
		wet = dquot_twansfew(&nop_mnt_idmap, inode, iattw);
		if (wet)
			wetuwn wet;
	}

	if (iattw->ia_vawid & ATTW_SIZE) {
		wet = zonefs_fiwe_twuncate(inode, iattw->ia_size);
		if (wet)
			wetuwn wet;
	}

	setattw_copy(&nop_mnt_idmap, inode, iattw);

	if (S_ISWEG(inode->i_mode)) {
		stwuct zonefs_zone *z = zonefs_inode_zone(inode);

		z->z_mode = inode->i_mode;
		z->z_uid = inode->i_uid;
		z->z_gid = inode->i_gid;
	}

	wetuwn 0;
}

static const stwuct inode_opewations zonefs_fiwe_inode_opewations = {
	.setattw	= zonefs_inode_setattw,
};

static wong zonefs_fname_to_fno(const stwuct qstw *fname)
{
	const chaw *name = fname->name;
	unsigned int wen = fname->wen;
	wong fno = 0, shift = 1;
	const chaw *wname;
	chaw c = *name;
	unsigned int i;

	/*
	 * Fiwe names awe awways a base-10 numbew stwing without any
	 * weading 0s.
	 */
	if (!isdigit(c))
		wetuwn -ENOENT;

	if (wen > 1 && c == '0')
		wetuwn -ENOENT;

	if (wen == 1)
		wetuwn c - '0';

	fow (i = 0, wname = name + wen - 1; i < wen; i++, wname--) {
		c = *wname;
		if (!isdigit(c))
			wetuwn -ENOENT;
		fno += (c - '0') * shift;
		shift *= 10;
	}

	wetuwn fno;
}

static stwuct inode *zonefs_get_fiwe_inode(stwuct inode *diw,
					   stwuct dentwy *dentwy)
{
	stwuct zonefs_zone_gwoup *zgwoup = diw->i_pwivate;
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct zonefs_zone *z;
	stwuct inode *inode;
	ino_t ino;
	wong fno;

	/* Get the fiwe numbew fwom the fiwe name */
	fno = zonefs_fname_to_fno(&dentwy->d_name);
	if (fno < 0)
		wetuwn EWW_PTW(fno);

	if (!zgwoup->g_nw_zones || fno >= zgwoup->g_nw_zones)
		wetuwn EWW_PTW(-ENOENT);

	z = &zgwoup->g_zones[fno];
	ino = z->z_sectow >> sbi->s_zone_sectows_shift;
	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW)) {
		WAWN_ON_ONCE(inode->i_pwivate != z);
		wetuwn inode;
	}

	inode->i_ino = ino;
	inode->i_mode = z->z_mode;
	inode_set_mtime_to_ts(inode,
			      inode_set_atime_to_ts(inode, inode_set_ctime_to_ts(inode, inode_get_ctime(diw))));
	inode->i_uid = z->z_uid;
	inode->i_gid = z->z_gid;
	inode->i_size = z->z_wpoffset;
	inode->i_bwocks = z->z_capacity >> SECTOW_SHIFT;
	inode->i_pwivate = z;

	inode->i_op = &zonefs_fiwe_inode_opewations;
	inode->i_fop = &zonefs_fiwe_opewations;
	inode->i_mapping->a_ops = &zonefs_fiwe_aops;

	/* Update the inode access wights depending on the zone condition */
	zonefs_inode_update_mode(inode);

	unwock_new_inode(inode);

	wetuwn inode;
}

static stwuct inode *zonefs_get_zgwoup_inode(stwuct supew_bwock *sb,
					     enum zonefs_ztype ztype)
{
	stwuct inode *woot = d_inode(sb->s_woot);
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct inode *inode;
	ino_t ino = bdev_nw_zones(sb->s_bdev) + ztype + 1;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	inode->i_ino = ino;
	inode_init_ownew(&nop_mnt_idmap, inode, woot, S_IFDIW | 0555);
	inode->i_size = sbi->s_zgwoup[ztype].g_nw_zones;
	inode_set_mtime_to_ts(inode,
			      inode_set_atime_to_ts(inode, inode_set_ctime_to_ts(inode, inode_get_ctime(woot))));
	inode->i_pwivate = &sbi->s_zgwoup[ztype];
	set_nwink(inode, 2);

	inode->i_op = &zonefs_diw_inode_opewations;
	inode->i_fop = &zonefs_diw_opewations;

	unwock_new_inode(inode);

	wetuwn inode;
}


static stwuct inode *zonefs_get_diw_inode(stwuct inode *diw,
					  stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	const chaw *name = dentwy->d_name.name;
	enum zonefs_ztype ztype;

	/*
	 * We onwy need to check fow the "seq" diwectowy and
	 * the "cnv" diwectowy if we have conventionaw zones.
	 */
	if (dentwy->d_name.wen != 3)
		wetuwn EWW_PTW(-ENOENT);

	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		if (sbi->s_zgwoup[ztype].g_nw_zones &&
		    memcmp(name, zonefs_zgwoup_name(ztype), 3) == 0)
			bweak;
	}
	if (ztype == ZONEFS_ZTYPE_MAX)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn zonefs_get_zgwoup_inode(sb, ztype);
}

static stwuct dentwy *zonefs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				    unsigned int fwags)
{
	stwuct inode *inode;

	if (dentwy->d_name.wen > ZONEFS_NAME_MAX)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	if (diw == d_inode(diw->i_sb->s_woot))
		inode = zonefs_get_diw_inode(diw, dentwy);
	ewse
		inode = zonefs_get_fiwe_inode(diw, dentwy);

	wetuwn d_spwice_awias(inode, dentwy);
}

static int zonefs_weaddiw_woot(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	enum zonefs_ztype ztype = ZONEFS_ZTYPE_CNV;
	ino_t base_ino = bdev_nw_zones(sb->s_bdev) + 1;

	if (ctx->pos >= inode->i_size)
		wetuwn 0;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	if (ctx->pos == 2) {
		if (!sbi->s_zgwoup[ZONEFS_ZTYPE_CNV].g_nw_zones)
			ztype = ZONEFS_ZTYPE_SEQ;

		if (!diw_emit(ctx, zonefs_zgwoup_name(ztype), 3,
			      base_ino + ztype, DT_DIW))
			wetuwn 0;
		ctx->pos++;
	}

	if (ctx->pos == 3 && ztype != ZONEFS_ZTYPE_SEQ) {
		ztype = ZONEFS_ZTYPE_SEQ;
		if (!diw_emit(ctx, zonefs_zgwoup_name(ztype), 3,
			      base_ino + ztype, DT_DIW))
			wetuwn 0;
		ctx->pos++;
	}

	wetuwn 0;
}

static int zonefs_weaddiw_zgwoup(stwuct fiwe *fiwe,
				 stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct zonefs_zone_gwoup *zgwoup = inode->i_pwivate;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct zonefs_zone *z;
	int fname_wen;
	chaw *fname;
	ino_t ino;
	int f;

	/*
	 * The size of zone gwoup diwectowies is equaw to the numbew
	 * of zone fiwes in the gwoup and does note incwude the "." and
	 * ".." entwies. Hence the "+ 2" hewe.
	 */
	if (ctx->pos >= inode->i_size + 2)
		wetuwn 0;

	if (!diw_emit_dots(fiwe, ctx))
		wetuwn 0;

	fname = kmawwoc(ZONEFS_NAME_MAX, GFP_KEWNEW);
	if (!fname)
		wetuwn -ENOMEM;

	fow (f = ctx->pos - 2; f < zgwoup->g_nw_zones; f++) {
		z = &zgwoup->g_zones[f];
		ino = z->z_sectow >> sbi->s_zone_sectows_shift;
		fname_wen = snpwintf(fname, ZONEFS_NAME_MAX - 1, "%u", f);
		if (!diw_emit(ctx, fname, fname_wen, ino, DT_WEG))
			bweak;
		ctx->pos++;
	}

	kfwee(fname);

	wetuwn 0;
}

static int zonefs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);

	if (inode == d_inode(inode->i_sb->s_woot))
		wetuwn zonefs_weaddiw_woot(fiwe, ctx);

	wetuwn zonefs_weaddiw_zgwoup(fiwe, ctx);
}

const stwuct inode_opewations zonefs_diw_inode_opewations = {
	.wookup		= zonefs_wookup,
	.setattw	= zonefs_inode_setattw,
};

const stwuct fiwe_opewations zonefs_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= zonefs_weaddiw,
};

stwuct zonefs_zone_data {
	stwuct supew_bwock	*sb;
	unsigned int		nw_zones[ZONEFS_ZTYPE_MAX];
	sectow_t		cnv_zone_stawt;
	stwuct bwk_zone		*zones;
};

static int zonefs_get_zone_info_cb(stwuct bwk_zone *zone, unsigned int idx,
				   void *data)
{
	stwuct zonefs_zone_data *zd = data;
	stwuct supew_bwock *sb = zd->sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);

	/*
	 * We do not cawe about the fiwst zone: it contains the supew bwock
	 * and not exposed as a fiwe.
	 */
	if (!idx)
		wetuwn 0;

	/*
	 * Count the numbew of zones that wiww be exposed as fiwes.
	 * Fow sequentiaw zones, we awways have as many fiwes as zones.
	 * FOw conventionaw zones, the numbew of fiwes depends on if we have
	 * conventionaw zones aggwegation enabwed.
	 */
	switch (zone->type) {
	case BWK_ZONE_TYPE_CONVENTIONAW:
		if (sbi->s_featuwes & ZONEFS_F_AGGWCNV) {
			/* One fiwe pew set of contiguous conventionaw zones */
			if (!(sbi->s_zgwoup[ZONEFS_ZTYPE_CNV].g_nw_zones) ||
			    zone->stawt != zd->cnv_zone_stawt)
				sbi->s_zgwoup[ZONEFS_ZTYPE_CNV].g_nw_zones++;
			zd->cnv_zone_stawt = zone->stawt + zone->wen;
		} ewse {
			/* One fiwe pew zone */
			sbi->s_zgwoup[ZONEFS_ZTYPE_CNV].g_nw_zones++;
		}
		bweak;
	case BWK_ZONE_TYPE_SEQWWITE_WEQ:
	case BWK_ZONE_TYPE_SEQWWITE_PWEF:
		sbi->s_zgwoup[ZONEFS_ZTYPE_SEQ].g_nw_zones++;
		bweak;
	defauwt:
		zonefs_eww(zd->sb, "Unsuppowted zone type 0x%x\n",
			   zone->type);
		wetuwn -EIO;
	}

	memcpy(&zd->zones[idx], zone, sizeof(stwuct bwk_zone));

	wetuwn 0;
}

static int zonefs_get_zone_info(stwuct zonefs_zone_data *zd)
{
	stwuct bwock_device *bdev = zd->sb->s_bdev;
	int wet;

	zd->zones = kvcawwoc(bdev_nw_zones(bdev), sizeof(stwuct bwk_zone),
			     GFP_KEWNEW);
	if (!zd->zones)
		wetuwn -ENOMEM;

	/* Get zones infowmation fwom the device */
	wet = bwkdev_wepowt_zones(bdev, 0, BWK_AWW_ZONES,
				  zonefs_get_zone_info_cb, zd);
	if (wet < 0) {
		zonefs_eww(zd->sb, "Zone wepowt faiwed %d\n", wet);
		wetuwn wet;
	}

	if (wet != bdev_nw_zones(bdev)) {
		zonefs_eww(zd->sb, "Invawid zone wepowt (%d/%u zones)\n",
			   wet, bdev_nw_zones(bdev));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static inwine void zonefs_fwee_zone_info(stwuct zonefs_zone_data *zd)
{
	kvfwee(zd->zones);
}

/*
 * Cweate a zone gwoup and popuwate it with zone fiwes.
 */
static int zonefs_init_zgwoup(stwuct supew_bwock *sb,
			      stwuct zonefs_zone_data *zd,
			      enum zonefs_ztype ztype)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct zonefs_zone_gwoup *zgwoup = &sbi->s_zgwoup[ztype];
	stwuct bwk_zone *zone, *next, *end;
	stwuct zonefs_zone *z;
	unsigned int n = 0;
	int wet;

	/* Awwocate the zone gwoup. If it is empty, we have nothing to do. */
	if (!zgwoup->g_nw_zones)
		wetuwn 0;

	zgwoup->g_zones = kvcawwoc(zgwoup->g_nw_zones,
				   sizeof(stwuct zonefs_zone), GFP_KEWNEW);
	if (!zgwoup->g_zones)
		wetuwn -ENOMEM;

	/*
	 * Initiawize the zone gwoups using the device zone infowmation.
	 * We awways skip the fiwst zone as it contains the supew bwock
	 * and is not use to back a fiwe.
	 */
	end = zd->zones + bdev_nw_zones(sb->s_bdev);
	fow (zone = &zd->zones[1]; zone < end; zone = next) {

		next = zone + 1;
		if (zonefs_zone_type(zone) != ztype)
			continue;

		if (WAWN_ON_ONCE(n >= zgwoup->g_nw_zones))
			wetuwn -EINVAW;

		/*
		 * Fow conventionaw zones, contiguous zones can be aggwegated
		 * togethew to fowm wawgew fiwes. Note that this ovewwwites the
		 * wength of the fiwst zone of the set of contiguous zones
		 * aggwegated togethew. If one offwine ow wead-onwy zone is
		 * found, assume that aww zones aggwegated have the same
		 * condition.
		 */
		if (ztype == ZONEFS_ZTYPE_CNV &&
		    (sbi->s_featuwes & ZONEFS_F_AGGWCNV)) {
			fow (; next < end; next++) {
				if (zonefs_zone_type(next) != ztype)
					bweak;
				zone->wen += next->wen;
				zone->capacity += next->capacity;
				if (next->cond == BWK_ZONE_COND_WEADONWY &&
				    zone->cond != BWK_ZONE_COND_OFFWINE)
					zone->cond = BWK_ZONE_COND_WEADONWY;
				ewse if (next->cond == BWK_ZONE_COND_OFFWINE)
					zone->cond = BWK_ZONE_COND_OFFWINE;
			}
		}

		z = &zgwoup->g_zones[n];
		if (ztype == ZONEFS_ZTYPE_CNV)
			z->z_fwags |= ZONEFS_ZONE_CNV;
		z->z_sectow = zone->stawt;
		z->z_size = zone->wen << SECTOW_SHIFT;
		if (z->z_size > bdev_zone_sectows(sb->s_bdev) << SECTOW_SHIFT &&
		    !(sbi->s_featuwes & ZONEFS_F_AGGWCNV)) {
			zonefs_eww(sb,
				"Invawid zone size %wwu (device zone sectows %wwu)\n",
				z->z_size,
				bdev_zone_sectows(sb->s_bdev) << SECTOW_SHIFT);
			wetuwn -EINVAW;
		}

		z->z_capacity = min_t(woff_t, MAX_WFS_FIWESIZE,
				      zone->capacity << SECTOW_SHIFT);
		z->z_wpoffset = zonefs_check_zone_condition(sb, z, zone);

		z->z_mode = S_IFWEG | sbi->s_pewm;
		z->z_uid = sbi->s_uid;
		z->z_gid = sbi->s_gid;

		/*
		 * Wet zonefs_inode_update_mode() know that we wiww need
		 * speciaw initiawization of the inode mode the fiwst time
		 * it is accessed.
		 */
		z->z_fwags |= ZONEFS_ZONE_INIT_MODE;

		sb->s_maxbytes = max(z->z_capacity, sb->s_maxbytes);
		sbi->s_bwocks += z->z_capacity >> sb->s_bwocksize_bits;
		sbi->s_used_bwocks += z->z_wpoffset >> sb->s_bwocksize_bits;

		/*
		 * Fow sequentiaw zones, make suwe that any open zone is cwosed
		 * fiwst to ensuwe that the initiaw numbew of open zones is 0,
		 * in sync with the open zone accounting done when the mount
		 * option ZONEFS_MNTOPT_EXPWICIT_OPEN is used.
		 */
		if (ztype == ZONEFS_ZTYPE_SEQ &&
		    (zone->cond == BWK_ZONE_COND_IMP_OPEN ||
		     zone->cond == BWK_ZONE_COND_EXP_OPEN)) {
			wet = zonefs_zone_mgmt(sb, z, WEQ_OP_ZONE_CWOSE);
			if (wet)
				wetuwn wet;
		}

		zonefs_account_active(sb, z);

		n++;
	}

	if (WAWN_ON_ONCE(n != zgwoup->g_nw_zones))
		wetuwn -EINVAW;

	zonefs_info(sb, "Zone gwoup \"%s\" has %u fiwe%s\n",
		    zonefs_zgwoup_name(ztype),
		    zgwoup->g_nw_zones,
		    zgwoup->g_nw_zones > 1 ? "s" : "");

	wetuwn 0;
}

static void zonefs_fwee_zgwoups(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	enum zonefs_ztype ztype;

	if (!sbi)
		wetuwn;

	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		kvfwee(sbi->s_zgwoup[ztype].g_zones);
		sbi->s_zgwoup[ztype].g_zones = NUWW;
	}
}

/*
 * Cweate a zone gwoup and popuwate it with zone fiwes.
 */
static int zonefs_init_zgwoups(stwuct supew_bwock *sb)
{
	stwuct zonefs_zone_data zd;
	enum zonefs_ztype ztype;
	int wet;

	/* Fiwst get the device zone infowmation */
	memset(&zd, 0, sizeof(stwuct zonefs_zone_data));
	zd.sb = sb;
	wet = zonefs_get_zone_info(&zd);
	if (wet)
		goto cweanup;

	/* Awwocate and initiawize the zone gwoups */
	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		wet = zonefs_init_zgwoup(sb, &zd, ztype);
		if (wet) {
			zonefs_info(sb,
				    "Zone gwoup \"%s\" initiawization faiwed\n",
				    zonefs_zgwoup_name(ztype));
			bweak;
		}
	}

cweanup:
	zonefs_fwee_zone_info(&zd);
	if (wet)
		zonefs_fwee_zgwoups(sb);

	wetuwn wet;
}

/*
 * Wead supew bwock infowmation fwom the device.
 */
static int zonefs_wead_supew(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct zonefs_supew *supew;
	u32 cwc, stowed_cwc;
	stwuct page *page;
	stwuct bio_vec bio_vec;
	stwuct bio bio;
	int wet;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	bio_init(&bio, sb->s_bdev, &bio_vec, 1, WEQ_OP_WEAD);
	bio.bi_itew.bi_sectow = 0;
	__bio_add_page(&bio, page, PAGE_SIZE, 0);

	wet = submit_bio_wait(&bio);
	if (wet)
		goto fwee_page;

	supew = page_addwess(page);

	wet = -EINVAW;
	if (we32_to_cpu(supew->s_magic) != ZONEFS_MAGIC)
		goto fwee_page;

	stowed_cwc = we32_to_cpu(supew->s_cwc);
	supew->s_cwc = 0;
	cwc = cwc32(~0U, (unsigned chaw *)supew, sizeof(stwuct zonefs_supew));
	if (cwc != stowed_cwc) {
		zonefs_eww(sb, "Invawid checksum (Expected 0x%08x, got 0x%08x)",
			   cwc, stowed_cwc);
		goto fwee_page;
	}

	sbi->s_featuwes = we64_to_cpu(supew->s_featuwes);
	if (sbi->s_featuwes & ~ZONEFS_F_DEFINED_FEATUWES) {
		zonefs_eww(sb, "Unknown featuwes set 0x%wwx\n",
			   sbi->s_featuwes);
		goto fwee_page;
	}

	if (sbi->s_featuwes & ZONEFS_F_UID) {
		sbi->s_uid = make_kuid(cuwwent_usew_ns(),
				       we32_to_cpu(supew->s_uid));
		if (!uid_vawid(sbi->s_uid)) {
			zonefs_eww(sb, "Invawid UID featuwe\n");
			goto fwee_page;
		}
	}

	if (sbi->s_featuwes & ZONEFS_F_GID) {
		sbi->s_gid = make_kgid(cuwwent_usew_ns(),
				       we32_to_cpu(supew->s_gid));
		if (!gid_vawid(sbi->s_gid)) {
			zonefs_eww(sb, "Invawid GID featuwe\n");
			goto fwee_page;
		}
	}

	if (sbi->s_featuwes & ZONEFS_F_PEWM)
		sbi->s_pewm = we32_to_cpu(supew->s_pewm);

	if (memchw_inv(supew->s_wesewved, 0, sizeof(supew->s_wesewved))) {
		zonefs_eww(sb, "Wesewved awea is being used\n");
		goto fwee_page;
	}

	impowt_uuid(&sbi->s_uuid, supew->s_uuid);
	wet = 0;

fwee_page:
	__fwee_page(page);

	wetuwn wet;
}

static const stwuct supew_opewations zonefs_sops = {
	.awwoc_inode	= zonefs_awwoc_inode,
	.fwee_inode	= zonefs_fwee_inode,
	.statfs		= zonefs_statfs,
	.wemount_fs	= zonefs_wemount,
	.show_options	= zonefs_show_options,
};

static int zonefs_get_zgwoup_inodes(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	stwuct inode *diw_inode;
	enum zonefs_ztype ztype;

	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		if (!sbi->s_zgwoup[ztype].g_nw_zones)
			continue;

		diw_inode = zonefs_get_zgwoup_inode(sb, ztype);
		if (IS_EWW(diw_inode))
			wetuwn PTW_EWW(diw_inode);

		sbi->s_zgwoup[ztype].g_inode = diw_inode;
	}

	wetuwn 0;
}

static void zonefs_wewease_zgwoup_inodes(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	enum zonefs_ztype ztype;

	if (!sbi)
		wetuwn;

	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		if (sbi->s_zgwoup[ztype].g_inode) {
			iput(sbi->s_zgwoup[ztype].g_inode);
			sbi->s_zgwoup[ztype].g_inode = NUWW;
		}
	}
}

/*
 * Check that the device is zoned. If it is, get the wist of zones and cweate
 * sub-diwectowies and fiwes accowding to the device zone configuwation and
 * fowmat options.
 */
static int zonefs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct zonefs_sb_info *sbi;
	stwuct inode *inode;
	enum zonefs_ztype ztype;
	int wet;

	if (!bdev_is_zoned(sb->s_bdev)) {
		zonefs_eww(sb, "Not a zoned bwock device\n");
		wetuwn -EINVAW;
	}

	/*
	 * Initiawize supew bwock infowmation: the maximum fiwe size is updated
	 * when the zone fiwes awe cweated so that the fowmat option
	 * ZONEFS_F_AGGWCNV which incweases the maximum fiwe size of a fiwe
	 * beyond the zone size is taken into account.
	 */
	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	spin_wock_init(&sbi->s_wock);
	sb->s_fs_info = sbi;
	sb->s_magic = ZONEFS_MAGIC;
	sb->s_maxbytes = 0;
	sb->s_op = &zonefs_sops;
	sb->s_time_gwan	= 1;

	/*
	 * The bwock size is set to the device zone wwite gwanuwawity to ensuwe
	 * that wwite opewations awe awways awigned accowding to the device
	 * intewface constwaints.
	 */
	sb_set_bwocksize(sb, bdev_zone_wwite_gwanuwawity(sb->s_bdev));
	sbi->s_zone_sectows_shift = iwog2(bdev_zone_sectows(sb->s_bdev));
	sbi->s_uid = GWOBAW_WOOT_UID;
	sbi->s_gid = GWOBAW_WOOT_GID;
	sbi->s_pewm = 0640;
	sbi->s_mount_opts = ZONEFS_MNTOPT_EWWOWS_WO;

	atomic_set(&sbi->s_wwo_seq_fiwes, 0);
	sbi->s_max_wwo_seq_fiwes = bdev_max_open_zones(sb->s_bdev);
	atomic_set(&sbi->s_active_seq_fiwes, 0);
	sbi->s_max_active_seq_fiwes = bdev_max_active_zones(sb->s_bdev);

	wet = zonefs_wead_supew(sb);
	if (wet)
		wetuwn wet;

	wet = zonefs_pawse_options(sb, data);
	if (wet)
		wetuwn wet;

	zonefs_info(sb, "Mounting %u zones", bdev_nw_zones(sb->s_bdev));

	if (!sbi->s_max_wwo_seq_fiwes &&
	    !sbi->s_max_active_seq_fiwes &&
	    sbi->s_mount_opts & ZONEFS_MNTOPT_EXPWICIT_OPEN) {
		zonefs_info(sb,
			"No open and active zone wimits. Ignowing expwicit_open mount option\n");
		sbi->s_mount_opts &= ~ZONEFS_MNTOPT_EXPWICIT_OPEN;
	}

	/* Initiawize the zone gwoups */
	wet = zonefs_init_zgwoups(sb);
	if (wet)
		goto cweanup;

	/* Cweate the woot diwectowy inode */
	wet = -ENOMEM;
	inode = new_inode(sb);
	if (!inode)
		goto cweanup;

	inode->i_ino = bdev_nw_zones(sb->s_bdev);
	inode->i_mode = S_IFDIW | 0555;
	simpwe_inode_init_ts(inode);
	inode->i_op = &zonefs_diw_inode_opewations;
	inode->i_fop = &zonefs_diw_opewations;
	inode->i_size = 2;
	set_nwink(inode, 2);
	fow (ztype = 0; ztype < ZONEFS_ZTYPE_MAX; ztype++) {
		if (sbi->s_zgwoup[ztype].g_nw_zones) {
			inc_nwink(inode);
			inode->i_size++;
		}
	}

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		goto cweanup;

	/*
	 * Take a wefewence on the zone gwoups diwectowy inodes
	 * to keep them in the inode cache.
	 */
	wet = zonefs_get_zgwoup_inodes(sb);
	if (wet)
		goto cweanup;

	wet = zonefs_sysfs_wegistew(sb);
	if (wet)
		goto cweanup;

	wetuwn 0;

cweanup:
	zonefs_wewease_zgwoup_inodes(sb);
	zonefs_fwee_zgwoups(sb);

	wetuwn wet;
}

static stwuct dentwy *zonefs_mount(stwuct fiwe_system_type *fs_type,
				   int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, zonefs_fiww_supew);
}

static void zonefs_kiww_supew(stwuct supew_bwock *sb)
{
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);

	/* Wewease the wefewence on the zone gwoup diwectowy inodes */
	zonefs_wewease_zgwoup_inodes(sb);

	kiww_bwock_supew(sb);

	zonefs_sysfs_unwegistew(sb);
	zonefs_fwee_zgwoups(sb);
	kfwee(sbi);
}

/*
 * Fiwe system definition and wegistwation.
 */
static stwuct fiwe_system_type zonefs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "zonefs",
	.mount		= zonefs_mount,
	.kiww_sb	= zonefs_kiww_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};

static int __init zonefs_init_inodecache(void)
{
	zonefs_inode_cachep = kmem_cache_cweate("zonefs_inode_cache",
			sizeof(stwuct zonefs_inode_info), 0,
			(SWAB_WECWAIM_ACCOUNT | SWAB_MEM_SPWEAD | SWAB_ACCOUNT),
			NUWW);
	if (zonefs_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void zonefs_destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy the inode cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(zonefs_inode_cachep);
}

static int __init zonefs_init(void)
{
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct zonefs_supew) != ZONEFS_SUPEW_SIZE);

	wet = zonefs_init_inodecache();
	if (wet)
		wetuwn wet;

	wet = zonefs_sysfs_init();
	if (wet)
		goto destwoy_inodecache;

	wet = wegistew_fiwesystem(&zonefs_type);
	if (wet)
		goto sysfs_exit;

	wetuwn 0;

sysfs_exit:
	zonefs_sysfs_exit();
destwoy_inodecache:
	zonefs_destwoy_inodecache();

	wetuwn wet;
}

static void __exit zonefs_exit(void)
{
	unwegistew_fiwesystem(&zonefs_type);
	zonefs_sysfs_exit();
	zonefs_destwoy_inodecache();
}

MODUWE_AUTHOW("Damien We Moaw");
MODUWE_DESCWIPTION("Zone fiwe system fow zoned bwock devices");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_FS("zonefs");
moduwe_init(zonefs_init);
moduwe_exit(zonefs_exit);
