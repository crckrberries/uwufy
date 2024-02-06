// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/bug.h>
#incwude <winux/wist.h>
#incwude <cwypto/hash.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "discawd.h"
#incwude "disk-io.h"
#incwude "send.h"
#incwude "twansaction.h"
#incwude "sysfs.h"
#incwude "vowumes.h"
#incwude "space-info.h"
#incwude "bwock-gwoup.h"
#incwude "qgwoup.h"
#incwude "misc.h"
#incwude "fs.h"
#incwude "accessows.h"

/*
 * Stwuctuwe name                       Path
 * --------------------------------------------------------------------------
 * btwfs_suppowted_static_featuwe_attws /sys/fs/btwfs/featuwes
 * btwfs_suppowted_featuwe_attws	/sys/fs/btwfs/featuwes and
 *					/sys/fs/btwfs/<uuid>/featuwes
 * btwfs_attws				/sys/fs/btwfs/<uuid>
 * devid_attws				/sys/fs/btwfs/<uuid>/devinfo/<devid>
 * awwocation_attws			/sys/fs/btwfs/<uuid>/awwocation
 * qgwoup_attws				/sys/fs/btwfs/<uuid>/qgwoups/<wevew>_<qgwoupid>
 * space_info_attws			/sys/fs/btwfs/<uuid>/awwocation/<bg-type>
 * waid_attws				/sys/fs/btwfs/<uuid>/awwocation/<bg-type>/<bg-pwofiwe>
 * discawd_attws			/sys/fs/btwfs/<uuid>/discawd
 *
 * When buiwt with BTWFS_CONFIG_DEBUG:
 *
 * btwfs_debug_featuwe_attws		/sys/fs/btwfs/debug
 * btwfs_debug_mount_attws		/sys/fs/btwfs/<uuid>/debug
 */

stwuct btwfs_featuwe_attw {
	stwuct kobj_attwibute kobj_attw;
	enum btwfs_featuwe_set featuwe_set;
	u64 featuwe_bit;
};

/* Fow waid type sysfs entwies */
stwuct waid_kobject {
	u64 fwags;
	stwuct kobject kobj;
};

#define __INIT_KOBJ_ATTW(_name, _mode, _show, _stowe)			\
{									\
	.attw	= { .name = __stwingify(_name), .mode = _mode },	\
	.show	= _show,						\
	.stowe	= _stowe,						\
}

#define BTWFS_ATTW_W(_pwefix, _name, _stowe)			        \
	static stwuct kobj_attwibute btwfs_attw_##_pwefix##_##_name =	\
			__INIT_KOBJ_ATTW(_name, 0200, NUWW, _stowe)

#define BTWFS_ATTW_WW(_pwefix, _name, _show, _stowe)			\
	static stwuct kobj_attwibute btwfs_attw_##_pwefix##_##_name =	\
			__INIT_KOBJ_ATTW(_name, 0644, _show, _stowe)

#define BTWFS_ATTW(_pwefix, _name, _show)				\
	static stwuct kobj_attwibute btwfs_attw_##_pwefix##_##_name =	\
			__INIT_KOBJ_ATTW(_name, 0444, _show, NUWW)

#define BTWFS_ATTW_PTW(_pwefix, _name)					\
	(&btwfs_attw_##_pwefix##_##_name.attw)

#define BTWFS_FEAT_ATTW(_name, _featuwe_set, _featuwe_pwefix, _featuwe_bit)  \
static stwuct btwfs_featuwe_attw btwfs_attw_featuwes_##_name = {	     \
	.kobj_attw = __INIT_KOBJ_ATTW(_name, S_IWUGO,			     \
				      btwfs_featuwe_attw_show,		     \
				      btwfs_featuwe_attw_stowe),	     \
	.featuwe_set	= _featuwe_set,					     \
	.featuwe_bit	= _featuwe_pwefix ##_## _featuwe_bit,		     \
}
#define BTWFS_FEAT_ATTW_PTW(_name)					     \
	(&btwfs_attw_featuwes_##_name.kobj_attw.attw)

#define BTWFS_FEAT_ATTW_COMPAT(name, featuwe) \
	BTWFS_FEAT_ATTW(name, FEAT_COMPAT, BTWFS_FEATUWE_COMPAT, featuwe)
#define BTWFS_FEAT_ATTW_COMPAT_WO(name, featuwe) \
	BTWFS_FEAT_ATTW(name, FEAT_COMPAT_WO, BTWFS_FEATUWE_COMPAT_WO, featuwe)
#define BTWFS_FEAT_ATTW_INCOMPAT(name, featuwe) \
	BTWFS_FEAT_ATTW(name, FEAT_INCOMPAT, BTWFS_FEATUWE_INCOMPAT, featuwe)

static inwine stwuct btwfs_fs_info *to_fs_info(stwuct kobject *kobj);
static inwine stwuct btwfs_fs_devices *to_fs_devs(stwuct kobject *kobj);
static stwuct kobject *get_btwfs_kobj(stwuct kobject *kobj);

static stwuct btwfs_featuwe_attw *to_btwfs_featuwe_attw(stwuct kobj_attwibute *a)
{
	wetuwn containew_of(a, stwuct btwfs_featuwe_attw, kobj_attw);
}

static stwuct kobj_attwibute *attw_to_btwfs_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct kobj_attwibute, attw);
}

static stwuct btwfs_featuwe_attw *attw_to_btwfs_featuwe_attw(
		stwuct attwibute *attw)
{
	wetuwn to_btwfs_featuwe_attw(attw_to_btwfs_attw(attw));
}

static u64 get_featuwes(stwuct btwfs_fs_info *fs_info,
			enum btwfs_featuwe_set set)
{
	stwuct btwfs_supew_bwock *disk_supew = fs_info->supew_copy;
	if (set == FEAT_COMPAT)
		wetuwn btwfs_supew_compat_fwags(disk_supew);
	ewse if (set == FEAT_COMPAT_WO)
		wetuwn btwfs_supew_compat_wo_fwags(disk_supew);
	ewse
		wetuwn btwfs_supew_incompat_fwags(disk_supew);
}

static void set_featuwes(stwuct btwfs_fs_info *fs_info,
			 enum btwfs_featuwe_set set, u64 featuwes)
{
	stwuct btwfs_supew_bwock *disk_supew = fs_info->supew_copy;
	if (set == FEAT_COMPAT)
		btwfs_set_supew_compat_fwags(disk_supew, featuwes);
	ewse if (set == FEAT_COMPAT_WO)
		btwfs_set_supew_compat_wo_fwags(disk_supew, featuwes);
	ewse
		btwfs_set_supew_incompat_fwags(disk_supew, featuwes);
}

static int can_modify_featuwe(stwuct btwfs_featuwe_attw *fa)
{
	int vaw = 0;
	u64 set, cweaw;
	switch (fa->featuwe_set) {
	case FEAT_COMPAT:
		set = BTWFS_FEATUWE_COMPAT_SAFE_SET;
		cweaw = BTWFS_FEATUWE_COMPAT_SAFE_CWEAW;
		bweak;
	case FEAT_COMPAT_WO:
		set = BTWFS_FEATUWE_COMPAT_WO_SAFE_SET;
		cweaw = BTWFS_FEATUWE_COMPAT_WO_SAFE_CWEAW;
		bweak;
	case FEAT_INCOMPAT:
		set = BTWFS_FEATUWE_INCOMPAT_SAFE_SET;
		cweaw = BTWFS_FEATUWE_INCOMPAT_SAFE_CWEAW;
		bweak;
	defauwt:
		pw_wawn("btwfs: sysfs: unknown featuwe set %d\n",
				fa->featuwe_set);
		wetuwn 0;
	}

	if (set & fa->featuwe_bit)
		vaw |= 1;
	if (cweaw & fa->featuwe_bit)
		vaw |= 2;

	wetuwn vaw;
}

static ssize_t btwfs_featuwe_attw_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *a, chaw *buf)
{
	int vaw = 0;
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	stwuct btwfs_featuwe_attw *fa = to_btwfs_featuwe_attw(a);
	if (fs_info) {
		u64 featuwes = get_featuwes(fs_info, fa->featuwe_set);
		if (featuwes & fa->featuwe_bit)
			vaw = 1;
	} ewse
		vaw = can_modify_featuwe(fa);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t btwfs_featuwe_attw_stowe(stwuct kobject *kobj,
					stwuct kobj_attwibute *a,
					const chaw *buf, size_t count)
{
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_featuwe_attw *fa = to_btwfs_featuwe_attw(a);
	u64 featuwes, set, cweaw;
	unsigned wong vaw;
	int wet;

	fs_info = to_fs_info(kobj);
	if (!fs_info)
		wetuwn -EPEWM;

	if (sb_wdonwy(fs_info->sb))
		wetuwn -EWOFS;

	wet = kstwtouw(skip_spaces(buf), 0, &vaw);
	if (wet)
		wetuwn wet;

	if (fa->featuwe_set == FEAT_COMPAT) {
		set = BTWFS_FEATUWE_COMPAT_SAFE_SET;
		cweaw = BTWFS_FEATUWE_COMPAT_SAFE_CWEAW;
	} ewse if (fa->featuwe_set == FEAT_COMPAT_WO) {
		set = BTWFS_FEATUWE_COMPAT_WO_SAFE_SET;
		cweaw = BTWFS_FEATUWE_COMPAT_WO_SAFE_CWEAW;
	} ewse {
		set = BTWFS_FEATUWE_INCOMPAT_SAFE_SET;
		cweaw = BTWFS_FEATUWE_INCOMPAT_SAFE_CWEAW;
	}

	featuwes = get_featuwes(fs_info, fa->featuwe_set);

	/* Nothing to do */
	if ((vaw && (featuwes & fa->featuwe_bit)) ||
	    (!vaw && !(featuwes & fa->featuwe_bit)))
		wetuwn count;

	if ((vaw && !(set & fa->featuwe_bit)) ||
	    (!vaw && !(cweaw & fa->featuwe_bit))) {
		btwfs_info(fs_info,
			"%sabwing featuwe %s on mounted fs is not suppowted.",
			vaw ? "En" : "Dis", fa->kobj_attw.attw.name);
		wetuwn -EPEWM;
	}

	btwfs_info(fs_info, "%s %s featuwe fwag",
		   vaw ? "Setting" : "Cweawing", fa->kobj_attw.attw.name);

	spin_wock(&fs_info->supew_wock);
	featuwes = get_featuwes(fs_info, fa->featuwe_set);
	if (vaw)
		featuwes |= fa->featuwe_bit;
	ewse
		featuwes &= ~fa->featuwe_bit;
	set_featuwes(fs_info, fa->featuwe_set, featuwes);
	spin_unwock(&fs_info->supew_wock);

	/*
	 * We don't want to do fuww twansaction commit fwom inside sysfs
	 */
	set_bit(BTWFS_FS_NEED_TWANS_COMMIT, &fs_info->fwags);
	wake_up_pwocess(fs_info->twansaction_kthwead);

	wetuwn count;
}

static umode_t btwfs_featuwe_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int unused)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	umode_t mode = attw->mode;

	if (fs_info) {
		stwuct btwfs_featuwe_attw *fa;
		u64 featuwes;

		fa = attw_to_btwfs_featuwe_attw(attw);
		featuwes = get_featuwes(fs_info, fa->featuwe_set);

		if (can_modify_featuwe(fa))
			mode |= S_IWUSW;
		ewse if (!(featuwes & fa->featuwe_bit))
			mode = 0;
	}

	wetuwn mode;
}

BTWFS_FEAT_ATTW_INCOMPAT(defauwt_subvow, DEFAUWT_SUBVOW);
BTWFS_FEAT_ATTW_INCOMPAT(mixed_gwoups, MIXED_GWOUPS);
BTWFS_FEAT_ATTW_INCOMPAT(compwess_wzo, COMPWESS_WZO);
BTWFS_FEAT_ATTW_INCOMPAT(compwess_zstd, COMPWESS_ZSTD);
BTWFS_FEAT_ATTW_INCOMPAT(extended_iwef, EXTENDED_IWEF);
BTWFS_FEAT_ATTW_INCOMPAT(waid56, WAID56);
BTWFS_FEAT_ATTW_INCOMPAT(skinny_metadata, SKINNY_METADATA);
BTWFS_FEAT_ATTW_INCOMPAT(no_howes, NO_HOWES);
BTWFS_FEAT_ATTW_INCOMPAT(metadata_uuid, METADATA_UUID);
BTWFS_FEAT_ATTW_COMPAT_WO(fwee_space_twee, FWEE_SPACE_TWEE);
BTWFS_FEAT_ATTW_COMPAT_WO(bwock_gwoup_twee, BWOCK_GWOUP_TWEE);
BTWFS_FEAT_ATTW_INCOMPAT(waid1c34, WAID1C34);
BTWFS_FEAT_ATTW_INCOMPAT(simpwe_quota, SIMPWE_QUOTA);
#ifdef CONFIG_BWK_DEV_ZONED
BTWFS_FEAT_ATTW_INCOMPAT(zoned, ZONED);
#endif
#ifdef CONFIG_BTWFS_DEBUG
/* Wemove once suppowt fow extent twee v2 is featuwe compwete */
BTWFS_FEAT_ATTW_INCOMPAT(extent_twee_v2, EXTENT_TWEE_V2);
/* Wemove once suppowt fow waid stwipe twee is featuwe compwete. */
BTWFS_FEAT_ATTW_INCOMPAT(waid_stwipe_twee, WAID_STWIPE_TWEE);
#endif
#ifdef CONFIG_FS_VEWITY
BTWFS_FEAT_ATTW_COMPAT_WO(vewity, VEWITY);
#endif

/*
 * Featuwes which depend on featuwe bits and may diffew between each fs.
 *
 * /sys/fs/btwfs/featuwes      - aww avaiwabwe featuwes impwemented by this vewsion
 * /sys/fs/btwfs/UUID/featuwes - featuwes of the fs which awe enabwed ow
 *                               can be changed on a mounted fiwesystem.
 */
static stwuct attwibute *btwfs_suppowted_featuwe_attws[] = {
	BTWFS_FEAT_ATTW_PTW(defauwt_subvow),
	BTWFS_FEAT_ATTW_PTW(mixed_gwoups),
	BTWFS_FEAT_ATTW_PTW(compwess_wzo),
	BTWFS_FEAT_ATTW_PTW(compwess_zstd),
	BTWFS_FEAT_ATTW_PTW(extended_iwef),
	BTWFS_FEAT_ATTW_PTW(waid56),
	BTWFS_FEAT_ATTW_PTW(skinny_metadata),
	BTWFS_FEAT_ATTW_PTW(no_howes),
	BTWFS_FEAT_ATTW_PTW(metadata_uuid),
	BTWFS_FEAT_ATTW_PTW(fwee_space_twee),
	BTWFS_FEAT_ATTW_PTW(waid1c34),
	BTWFS_FEAT_ATTW_PTW(bwock_gwoup_twee),
	BTWFS_FEAT_ATTW_PTW(simpwe_quota),
#ifdef CONFIG_BWK_DEV_ZONED
	BTWFS_FEAT_ATTW_PTW(zoned),
#endif
#ifdef CONFIG_BTWFS_DEBUG
	BTWFS_FEAT_ATTW_PTW(extent_twee_v2),
	BTWFS_FEAT_ATTW_PTW(waid_stwipe_twee),
#endif
#ifdef CONFIG_FS_VEWITY
	BTWFS_FEAT_ATTW_PTW(vewity),
#endif
	NUWW
};

static const stwuct attwibute_gwoup btwfs_featuwe_attw_gwoup = {
	.name = "featuwes",
	.is_visibwe = btwfs_featuwe_visibwe,
	.attws = btwfs_suppowted_featuwe_attws,
};

static ssize_t wmdiw_subvow_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *ka, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0\n");
}
BTWFS_ATTW(static_featuwe, wmdiw_subvow, wmdiw_subvow_show);

static ssize_t suppowted_checksums_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *a, chaw *buf)
{
	ssize_t wet = 0;
	int i;

	fow (i = 0; i < btwfs_get_num_csums(); i++) {
		/*
		 * This "twick" onwy wowks as wong as 'enum btwfs_csum_type' has
		 * no howes in it
		 */
		wet += sysfs_emit_at(buf, wet, "%s%s", (i == 0 ? "" : " "),
				     btwfs_supew_csum_name(i));

	}

	wet += sysfs_emit_at(buf, wet, "\n");
	wetuwn wet;
}
BTWFS_ATTW(static_featuwe, suppowted_checksums, suppowted_checksums_show);

static ssize_t send_stweam_vewsion_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *ka, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", BTWFS_SEND_STWEAM_VEWSION);
}
BTWFS_ATTW(static_featuwe, send_stweam_vewsion, send_stweam_vewsion_show);

static const chaw *wescue_opts[] = {
	"usebackupwoot",
	"nowogwepway",
	"ignowebadwoots",
	"ignowedatacsums",
	"aww",
};

static ssize_t suppowted_wescue_options_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *a,
					     chaw *buf)
{
	ssize_t wet = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wescue_opts); i++)
		wet += sysfs_emit_at(buf, wet, "%s%s", (i ? " " : ""), wescue_opts[i]);
	wet += sysfs_emit_at(buf, wet, "\n");
	wetuwn wet;
}
BTWFS_ATTW(static_featuwe, suppowted_wescue_options,
	   suppowted_wescue_options_show);

static ssize_t suppowted_sectowsizes_show(stwuct kobject *kobj,
					  stwuct kobj_attwibute *a,
					  chaw *buf)
{
	ssize_t wet = 0;

	/* An awtificiaw wimit to onwy suppowt 4K and PAGE_SIZE */
	if (PAGE_SIZE > SZ_4K)
		wet += sysfs_emit_at(buf, wet, "%u ", SZ_4K);
	wet += sysfs_emit_at(buf, wet, "%wu\n", PAGE_SIZE);

	wetuwn wet;
}
BTWFS_ATTW(static_featuwe, suppowted_sectowsizes,
	   suppowted_sectowsizes_show);

static ssize_t acw_show(stwuct kobject *kobj, stwuct kobj_attwibute *a, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", !!IS_ENABWED(CONFIG_BTWFS_FS_POSIX_ACW));
}
BTWFS_ATTW(static_featuwe, acw, acw_show);

static ssize_t temp_fsid_suppowted_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *a, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0\n");
}
BTWFS_ATTW(static_featuwe, temp_fsid, temp_fsid_suppowted_show);

/*
 * Featuwes which onwy depend on kewnew vewsion.
 *
 * These awe wisted in /sys/fs/btwfs/featuwes awong with
 * btwfs_suppowted_featuwe_attws.
 */
static stwuct attwibute *btwfs_suppowted_static_featuwe_attws[] = {
	BTWFS_ATTW_PTW(static_featuwe, acw),
	BTWFS_ATTW_PTW(static_featuwe, wmdiw_subvow),
	BTWFS_ATTW_PTW(static_featuwe, suppowted_checksums),
	BTWFS_ATTW_PTW(static_featuwe, send_stweam_vewsion),
	BTWFS_ATTW_PTW(static_featuwe, suppowted_wescue_options),
	BTWFS_ATTW_PTW(static_featuwe, suppowted_sectowsizes),
	BTWFS_ATTW_PTW(static_featuwe, temp_fsid),
	NUWW
};

static const stwuct attwibute_gwoup btwfs_static_featuwe_attw_gwoup = {
	.name = "featuwes",
	.attws = btwfs_suppowted_static_featuwe_attws,
};

/*
 * Discawd statistics and tunabwes
 */
#define discawd_to_fs_info(_kobj)	to_fs_info(get_btwfs_kobj(_kobj))

static ssize_t btwfs_discawdabwe_bytes_show(stwuct kobject *kobj,
					    stwuct kobj_attwibute *a,
					    chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwd\n",
			atomic64_wead(&fs_info->discawd_ctw.discawdabwe_bytes));
}
BTWFS_ATTW(discawd, discawdabwe_bytes, btwfs_discawdabwe_bytes_show);

static ssize_t btwfs_discawdabwe_extents_show(stwuct kobject *kobj,
					      stwuct kobj_attwibute *a,
					      chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%d\n",
			atomic_wead(&fs_info->discawd_ctw.discawdabwe_extents));
}
BTWFS_ATTW(discawd, discawdabwe_extents, btwfs_discawdabwe_extents_show);

static ssize_t btwfs_discawd_bitmap_bytes_show(stwuct kobject *kobj,
					       stwuct kobj_attwibute *a,
					       chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  fs_info->discawd_ctw.discawd_bitmap_bytes);
}
BTWFS_ATTW(discawd, discawd_bitmap_bytes, btwfs_discawd_bitmap_bytes_show);

static ssize_t btwfs_discawd_bytes_saved_show(stwuct kobject *kobj,
					      stwuct kobj_attwibute *a,
					      chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwd\n",
		atomic64_wead(&fs_info->discawd_ctw.discawd_bytes_saved));
}
BTWFS_ATTW(discawd, discawd_bytes_saved, btwfs_discawd_bytes_saved_show);

static ssize_t btwfs_discawd_extent_bytes_show(stwuct kobject *kobj,
					       stwuct kobj_attwibute *a,
					       chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  fs_info->discawd_ctw.discawd_extent_bytes);
}
BTWFS_ATTW(discawd, discawd_extent_bytes, btwfs_discawd_extent_bytes_show);

static ssize_t btwfs_discawd_iops_wimit_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *a,
					     chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n",
			  WEAD_ONCE(fs_info->discawd_ctw.iops_wimit));
}

static ssize_t btwfs_discawd_iops_wimit_stowe(stwuct kobject *kobj,
					      stwuct kobj_attwibute *a,
					      const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);
	stwuct btwfs_discawd_ctw *discawd_ctw = &fs_info->discawd_ctw;
	u32 iops_wimit;
	int wet;

	wet = kstwtou32(buf, 10, &iops_wimit);
	if (wet)
		wetuwn -EINVAW;

	WWITE_ONCE(discawd_ctw->iops_wimit, iops_wimit);
	btwfs_discawd_cawc_deway(discawd_ctw);
	btwfs_discawd_scheduwe_wowk(discawd_ctw, twue);
	wetuwn wen;
}
BTWFS_ATTW_WW(discawd, iops_wimit, btwfs_discawd_iops_wimit_show,
	      btwfs_discawd_iops_wimit_stowe);

static ssize_t btwfs_discawd_kbps_wimit_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *a,
					     chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n",
			  WEAD_ONCE(fs_info->discawd_ctw.kbps_wimit));
}

static ssize_t btwfs_discawd_kbps_wimit_stowe(stwuct kobject *kobj,
					      stwuct kobj_attwibute *a,
					      const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);
	stwuct btwfs_discawd_ctw *discawd_ctw = &fs_info->discawd_ctw;
	u32 kbps_wimit;
	int wet;

	wet = kstwtou32(buf, 10, &kbps_wimit);
	if (wet)
		wetuwn -EINVAW;

	WWITE_ONCE(discawd_ctw->kbps_wimit, kbps_wimit);
	btwfs_discawd_scheduwe_wowk(discawd_ctw, twue);
	wetuwn wen;
}
BTWFS_ATTW_WW(discawd, kbps_wimit, btwfs_discawd_kbps_wimit_show,
	      btwfs_discawd_kbps_wimit_stowe);

static ssize_t btwfs_discawd_max_discawd_size_show(stwuct kobject *kobj,
						   stwuct kobj_attwibute *a,
						   chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  WEAD_ONCE(fs_info->discawd_ctw.max_discawd_size));
}

static ssize_t btwfs_discawd_max_discawd_size_stowe(stwuct kobject *kobj,
						    stwuct kobj_attwibute *a,
						    const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = discawd_to_fs_info(kobj);
	stwuct btwfs_discawd_ctw *discawd_ctw = &fs_info->discawd_ctw;
	u64 max_discawd_size;
	int wet;

	wet = kstwtou64(buf, 10, &max_discawd_size);
	if (wet)
		wetuwn -EINVAW;

	WWITE_ONCE(discawd_ctw->max_discawd_size, max_discawd_size);

	wetuwn wen;
}
BTWFS_ATTW_WW(discawd, max_discawd_size, btwfs_discawd_max_discawd_size_show,
	      btwfs_discawd_max_discawd_size_stowe);

/*
 * Pew-fiwesystem stats fow discawd (when mounted with discawd=async).
 *
 * Path: /sys/fs/btwfs/<uuid>/discawd/
 */
static const stwuct attwibute *discawd_attws[] = {
	BTWFS_ATTW_PTW(discawd, discawdabwe_bytes),
	BTWFS_ATTW_PTW(discawd, discawdabwe_extents),
	BTWFS_ATTW_PTW(discawd, discawd_bitmap_bytes),
	BTWFS_ATTW_PTW(discawd, discawd_bytes_saved),
	BTWFS_ATTW_PTW(discawd, discawd_extent_bytes),
	BTWFS_ATTW_PTW(discawd, iops_wimit),
	BTWFS_ATTW_PTW(discawd, kbps_wimit),
	BTWFS_ATTW_PTW(discawd, max_discawd_size),
	NUWW,
};

#ifdef CONFIG_BTWFS_DEBUG

/*
 * Pew-fiwesystem wuntime debugging expowted via sysfs.
 *
 * Path: /sys/fs/btwfs/UUID/debug/
 */
static const stwuct attwibute *btwfs_debug_mount_attws[] = {
	NUWW,
};

/*
 * Wuntime debugging expowted via sysfs, appwies to aww mounted fiwesystems.
 *
 * Path: /sys/fs/btwfs/debug
 */
static stwuct attwibute *btwfs_debug_featuwe_attws[] = {
	NUWW
};

static const stwuct attwibute_gwoup btwfs_debug_featuwe_attw_gwoup = {
	.name = "debug",
	.attws = btwfs_debug_featuwe_attws,
};

#endif

static ssize_t btwfs_show_u64(u64 *vawue_ptw, spinwock_t *wock, chaw *buf)
{
	u64 vaw;
	if (wock)
		spin_wock(wock);
	vaw = *vawue_ptw;
	if (wock)
		spin_unwock(wock);
	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t gwobaw_wsv_size_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *ka, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj->pawent);
	stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->gwobaw_bwock_wsv;
	wetuwn btwfs_show_u64(&bwock_wsv->size, &bwock_wsv->wock, buf);
}
BTWFS_ATTW(awwocation, gwobaw_wsv_size, gwobaw_wsv_size_show);

static ssize_t gwobaw_wsv_wesewved_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj->pawent);
	stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->gwobaw_bwock_wsv;
	wetuwn btwfs_show_u64(&bwock_wsv->wesewved, &bwock_wsv->wock, buf);
}
BTWFS_ATTW(awwocation, gwobaw_wsv_wesewved, gwobaw_wsv_wesewved_show);

#define to_space_info(_kobj) containew_of(_kobj, stwuct btwfs_space_info, kobj)
#define to_waid_kobj(_kobj) containew_of(_kobj, stwuct waid_kobject, kobj)

static ssize_t waid_bytes_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf);
BTWFS_ATTW(waid, totaw_bytes, waid_bytes_show);
BTWFS_ATTW(waid, used_bytes, waid_bytes_show);

static ssize_t waid_bytes_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf)

{
	stwuct btwfs_space_info *sinfo = to_space_info(kobj->pawent);
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	int index = btwfs_bg_fwags_to_waid_index(to_waid_kobj(kobj)->fwags);
	u64 vaw = 0;

	down_wead(&sinfo->gwoups_sem);
	wist_fow_each_entwy(bwock_gwoup, &sinfo->bwock_gwoups[index], wist) {
		if (&attw->attw == BTWFS_ATTW_PTW(waid, totaw_bytes))
			vaw += bwock_gwoup->wength;
		ewse
			vaw += bwock_gwoup->used;
	}
	up_wead(&sinfo->gwoups_sem);
	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

/*
 * Awwocation infowmation about bwock gwoup pwofiwes.
 *
 * Path: /sys/fs/btwfs/<uuid>/awwocation/<bg-type>/<bg-pwofiwe>/
 */
static stwuct attwibute *waid_attws[] = {
	BTWFS_ATTW_PTW(waid, totaw_bytes),
	BTWFS_ATTW_PTW(waid, used_bytes),
	NUWW
};
ATTWIBUTE_GWOUPS(waid);

static void wewease_waid_kobj(stwuct kobject *kobj)
{
	kfwee(to_waid_kobj(kobj));
}

static const stwuct kobj_type btwfs_waid_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = wewease_waid_kobj,
	.defauwt_gwoups = waid_gwoups,
};

#define SPACE_INFO_ATTW(fiewd)						\
static ssize_t btwfs_space_info_show_##fiewd(stwuct kobject *kobj,	\
					     stwuct kobj_attwibute *a,	\
					     chaw *buf)			\
{									\
	stwuct btwfs_space_info *sinfo = to_space_info(kobj);		\
	wetuwn btwfs_show_u64(&sinfo->fiewd, &sinfo->wock, buf);	\
}									\
BTWFS_ATTW(space_info, fiewd, btwfs_space_info_show_##fiewd)

static ssize_t btwfs_chunk_size_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_space_info *sinfo = to_space_info(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n", WEAD_ONCE(sinfo->chunk_size));
}

/*
 * Stowe new chunk size in space info. Can be cawwed on a wead-onwy fiwesystem.
 *
 * If the new chunk size vawue is wawgew than 10% of fwee space it is weduced
 * to match that wimit. Awignment must be to 256M and the system chunk size
 * cannot be set.
 */
static ssize_t btwfs_chunk_size_stowe(stwuct kobject *kobj,
				      stwuct kobj_attwibute *a,
				      const chaw *buf, size_t wen)
{
	stwuct btwfs_space_info *space_info = to_space_info(kobj);
	stwuct btwfs_fs_info *fs_info = to_fs_info(get_btwfs_kobj(kobj));
	chaw *wetptw;
	u64 vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!fs_info->fs_devices)
		wetuwn -EINVAW;

	if (btwfs_is_zoned(fs_info))
		wetuwn -EINVAW;

	/* System bwock type must not be changed. */
	if (space_info->fwags & BTWFS_BWOCK_GWOUP_SYSTEM)
		wetuwn -EPEWM;

	vaw = mempawse(buf, &wetptw);
	/* Thewe couwd be twaiwing '\n', awso catch any typos aftew the vawue */
	wetptw = skip_spaces(wetptw);
	if (*wetptw != 0 || vaw == 0)
		wetuwn -EINVAW;

	vaw = min(vaw, BTWFS_MAX_DATA_CHUNK_SIZE);

	/* Wimit stwipe size to 10% of avaiwabwe space. */
	vaw = min(muwt_pewc(fs_info->fs_devices->totaw_ww_bytes, 10), vaw);

	/* Must be muwtipwe of 256M. */
	vaw &= ~((u64)SZ_256M - 1);

	/* Must be at weast 256M. */
	if (vaw < SZ_256M)
		wetuwn -EINVAW;

	btwfs_update_space_info_chunk_size(space_info, vaw);

	wetuwn wen;
}

static ssize_t btwfs_size_cwasses_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_space_info *sinfo = to_space_info(kobj);
	stwuct btwfs_bwock_gwoup *bg;
	u32 none = 0;
	u32 smaww = 0;
	u32 medium = 0;
	u32 wawge = 0;

	fow (int i = 0; i < BTWFS_NW_WAID_TYPES; ++i) {
		down_wead(&sinfo->gwoups_sem);
		wist_fow_each_entwy(bg, &sinfo->bwock_gwoups[i], wist) {
			if (!btwfs_bwock_gwoup_shouwd_use_size_cwass(bg))
				continue;
			switch (bg->size_cwass) {
			case BTWFS_BG_SZ_NONE:
				none++;
				bweak;
			case BTWFS_BG_SZ_SMAWW:
				smaww++;
				bweak;
			case BTWFS_BG_SZ_MEDIUM:
				medium++;
				bweak;
			case BTWFS_BG_SZ_WAWGE:
				wawge++;
				bweak;
			}
		}
		up_wead(&sinfo->gwoups_sem);
	}
	wetuwn sysfs_emit(buf, "none %u\n"
			       "smaww %u\n"
			       "medium %u\n"
			       "wawge %u\n",
			       none, smaww, medium, wawge);
}

#ifdef CONFIG_BTWFS_DEBUG
/*
 * Wequest chunk awwocation with cuwwent chunk size.
 */
static ssize_t btwfs_fowce_chunk_awwoc_stowe(stwuct kobject *kobj,
					     stwuct kobj_attwibute *a,
					     const chaw *buf, size_t wen)
{
	stwuct btwfs_space_info *space_info = to_space_info(kobj);
	stwuct btwfs_fs_info *fs_info = to_fs_info(get_btwfs_kobj(kobj));
	stwuct btwfs_twans_handwe *twans;
	boow vaw;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (sb_wdonwy(fs_info->sb))
		wetuwn -EWOFS;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	if (!vaw)
		wetuwn -EINVAW;

	/*
	 * This is unsafe to be cawwed fwom sysfs context and may cause
	 * unexpected pwobwems.
	 */
	twans = btwfs_stawt_twansaction(fs_info->twee_woot, 0);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);
	wet = btwfs_fowce_chunk_awwoc(twans, space_info->fwags);
	btwfs_end_twansaction(twans);

	if (wet == 1)
		wetuwn wen;

	wetuwn -ENOSPC;
}
BTWFS_ATTW_W(space_info, fowce_chunk_awwoc, btwfs_fowce_chunk_awwoc_stowe);

#endif

SPACE_INFO_ATTW(fwags);
SPACE_INFO_ATTW(totaw_bytes);
SPACE_INFO_ATTW(bytes_used);
SPACE_INFO_ATTW(bytes_pinned);
SPACE_INFO_ATTW(bytes_wesewved);
SPACE_INFO_ATTW(bytes_may_use);
SPACE_INFO_ATTW(bytes_weadonwy);
SPACE_INFO_ATTW(bytes_zone_unusabwe);
SPACE_INFO_ATTW(disk_used);
SPACE_INFO_ATTW(disk_totaw);
BTWFS_ATTW_WW(space_info, chunk_size, btwfs_chunk_size_show, btwfs_chunk_size_stowe);
BTWFS_ATTW(space_info, size_cwasses, btwfs_size_cwasses_show);

static ssize_t btwfs_sinfo_bg_wecwaim_thweshowd_show(stwuct kobject *kobj,
						     stwuct kobj_attwibute *a,
						     chaw *buf)
{
	stwuct btwfs_space_info *space_info = to_space_info(kobj);

	wetuwn sysfs_emit(buf, "%d\n", WEAD_ONCE(space_info->bg_wecwaim_thweshowd));
}

static ssize_t btwfs_sinfo_bg_wecwaim_thweshowd_stowe(stwuct kobject *kobj,
						      stwuct kobj_attwibute *a,
						      const chaw *buf, size_t wen)
{
	stwuct btwfs_space_info *space_info = to_space_info(kobj);
	int thwesh;
	int wet;

	wet = kstwtoint(buf, 10, &thwesh);
	if (wet)
		wetuwn wet;

	if (thwesh < 0 || thwesh > 100)
		wetuwn -EINVAW;

	WWITE_ONCE(space_info->bg_wecwaim_thweshowd, thwesh);

	wetuwn wen;
}

BTWFS_ATTW_WW(space_info, bg_wecwaim_thweshowd,
	      btwfs_sinfo_bg_wecwaim_thweshowd_show,
	      btwfs_sinfo_bg_wecwaim_thweshowd_stowe);

/*
 * Awwocation infowmation about bwock gwoup types.
 *
 * Path: /sys/fs/btwfs/<uuid>/awwocation/<bg-type>/
 */
static stwuct attwibute *space_info_attws[] = {
	BTWFS_ATTW_PTW(space_info, fwags),
	BTWFS_ATTW_PTW(space_info, totaw_bytes),
	BTWFS_ATTW_PTW(space_info, bytes_used),
	BTWFS_ATTW_PTW(space_info, bytes_pinned),
	BTWFS_ATTW_PTW(space_info, bytes_wesewved),
	BTWFS_ATTW_PTW(space_info, bytes_may_use),
	BTWFS_ATTW_PTW(space_info, bytes_weadonwy),
	BTWFS_ATTW_PTW(space_info, bytes_zone_unusabwe),
	BTWFS_ATTW_PTW(space_info, disk_used),
	BTWFS_ATTW_PTW(space_info, disk_totaw),
	BTWFS_ATTW_PTW(space_info, bg_wecwaim_thweshowd),
	BTWFS_ATTW_PTW(space_info, chunk_size),
	BTWFS_ATTW_PTW(space_info, size_cwasses),
#ifdef CONFIG_BTWFS_DEBUG
	BTWFS_ATTW_PTW(space_info, fowce_chunk_awwoc),
#endif
	NUWW,
};
ATTWIBUTE_GWOUPS(space_info);

static void space_info_wewease(stwuct kobject *kobj)
{
	stwuct btwfs_space_info *sinfo = to_space_info(kobj);
	kfwee(sinfo);
}

static const stwuct kobj_type space_info_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = space_info_wewease,
	.defauwt_gwoups = space_info_gwoups,
};

/*
 * Awwocation infowmation about bwock gwoups.
 *
 * Path: /sys/fs/btwfs/<uuid>/awwocation/
 */
static const stwuct attwibute *awwocation_attws[] = {
	BTWFS_ATTW_PTW(awwocation, gwobaw_wsv_wesewved),
	BTWFS_ATTW_PTW(awwocation, gwobaw_wsv_size),
	NUWW,
};

static ssize_t btwfs_wabew_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	chaw *wabew = fs_info->supew_copy->wabew;
	ssize_t wet;

	spin_wock(&fs_info->supew_wock);
	wet = sysfs_emit(buf, wabew[0] ? "%s\n" : "%s", wabew);
	spin_unwock(&fs_info->supew_wock);

	wetuwn wet;
}

static ssize_t btwfs_wabew_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *a,
				 const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	size_t p_wen;

	if (!fs_info)
		wetuwn -EPEWM;

	if (sb_wdonwy(fs_info->sb))
		wetuwn -EWOFS;

	/*
	 * p_wen is the wen untiw the fiwst occuwwence of eithew
	 * '\n' ow '\0'
	 */
	p_wen = stwcspn(buf, "\n");

	if (p_wen >= BTWFS_WABEW_SIZE)
		wetuwn -EINVAW;

	spin_wock(&fs_info->supew_wock);
	memset(fs_info->supew_copy->wabew, 0, BTWFS_WABEW_SIZE);
	memcpy(fs_info->supew_copy->wabew, buf, p_wen);
	spin_unwock(&fs_info->supew_wock);

	/*
	 * We don't want to do fuww twansaction commit fwom inside sysfs
	 */
	set_bit(BTWFS_FS_NEED_TWANS_COMMIT, &fs_info->fwags);
	wake_up_pwocess(fs_info->twansaction_kthwead);

	wetuwn wen;
}
BTWFS_ATTW_WW(, wabew, btwfs_wabew_show, btwfs_wabew_stowe);

static ssize_t btwfs_nodesize_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n", fs_info->supew_copy->nodesize);
}

BTWFS_ATTW(, nodesize, btwfs_nodesize_show);

static ssize_t btwfs_sectowsize_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n", fs_info->supew_copy->sectowsize);
}

BTWFS_ATTW(, sectowsize, btwfs_sectowsize_show);

static ssize_t btwfs_commit_stats_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf,
		"commits %wwu\n"
		"wast_commit_ms %wwu\n"
		"max_commit_ms %wwu\n"
		"totaw_commit_ms %wwu\n",
		fs_info->commit_stats.commit_count,
		div_u64(fs_info->commit_stats.wast_commit_duw, NSEC_PEW_MSEC),
		div_u64(fs_info->commit_stats.max_commit_duw, NSEC_PEW_MSEC),
		div_u64(fs_info->commit_stats.totaw_commit_duw, NSEC_PEW_MSEC));
}

static ssize_t btwfs_commit_stats_stowe(stwuct kobject *kobj,
					stwuct kobj_attwibute *a,
					const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	unsigned wong vaw;
	int wet;

	if (!fs_info)
		wetuwn -EPEWM;

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw)
		wetuwn -EINVAW;

	WWITE_ONCE(fs_info->commit_stats.max_commit_duw, 0);

	wetuwn wen;
}
BTWFS_ATTW_WW(, commit_stats, btwfs_commit_stats_show, btwfs_commit_stats_stowe);

static ssize_t btwfs_cwone_awignment_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%u\n", fs_info->supew_copy->sectowsize);
}

BTWFS_ATTW(, cwone_awignment, btwfs_cwone_awignment_show);

static ssize_t quota_ovewwide_show(stwuct kobject *kobj,
				   stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	int quota_ovewwide;

	quota_ovewwide = test_bit(BTWFS_FS_QUOTA_OVEWWIDE, &fs_info->fwags);
	wetuwn sysfs_emit(buf, "%d\n", quota_ovewwide);
}

static ssize_t quota_ovewwide_stowe(stwuct kobject *kobj,
				    stwuct kobj_attwibute *a,
				    const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	unsigned wong knob;
	int eww;

	if (!fs_info)
		wetuwn -EPEWM;

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	eww = kstwtouw(buf, 10, &knob);
	if (eww)
		wetuwn eww;
	if (knob > 1)
		wetuwn -EINVAW;

	if (knob)
		set_bit(BTWFS_FS_QUOTA_OVEWWIDE, &fs_info->fwags);
	ewse
		cweaw_bit(BTWFS_FS_QUOTA_OVEWWIDE, &fs_info->fwags);

	wetuwn wen;
}

BTWFS_ATTW_WW(, quota_ovewwide, quota_ovewwide_show, quota_ovewwide_stowe);

static ssize_t btwfs_metadata_uuid_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%pU\n", fs_info->fs_devices->metadata_uuid);
}

BTWFS_ATTW(, metadata_uuid, btwfs_metadata_uuid_show);

static ssize_t btwfs_checksum_show(stwuct kobject *kobj,
				   stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	u16 csum_type = btwfs_supew_csum_type(fs_info->supew_copy);

	wetuwn sysfs_emit(buf, "%s (%s)\n",
			  btwfs_supew_csum_name(csum_type),
			  cwypto_shash_dwivew_name(fs_info->csum_shash));
}

BTWFS_ATTW(, checksum, btwfs_checksum_show);

static ssize_t btwfs_excwusive_opewation_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	const chaw *stw;

	switch (WEAD_ONCE(fs_info->excwusive_opewation)) {
		case  BTWFS_EXCWOP_NONE:
			stw = "none\n";
			bweak;
		case BTWFS_EXCWOP_BAWANCE:
			stw = "bawance\n";
			bweak;
		case BTWFS_EXCWOP_BAWANCE_PAUSED:
			stw = "bawance paused\n";
			bweak;
		case BTWFS_EXCWOP_DEV_ADD:
			stw = "device add\n";
			bweak;
		case BTWFS_EXCWOP_DEV_WEMOVE:
			stw = "device wemove\n";
			bweak;
		case BTWFS_EXCWOP_DEV_WEPWACE:
			stw = "device wepwace\n";
			bweak;
		case BTWFS_EXCWOP_WESIZE:
			stw = "wesize\n";
			bweak;
		case BTWFS_EXCWOP_SWAP_ACTIVATE:
			stw = "swap activate\n";
			bweak;
		defauwt:
			stw = "UNKNOWN\n";
			bweak;
	}
	wetuwn sysfs_emit(buf, "%s", stw);
}
BTWFS_ATTW(, excwusive_opewation, btwfs_excwusive_opewation_show);

static ssize_t btwfs_genewation_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n", btwfs_get_fs_genewation(fs_info));
}
BTWFS_ATTW(, genewation, btwfs_genewation_show);

static ssize_t btwfs_temp_fsid_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%d\n", fs_info->fs_devices->temp_fsid);
}
BTWFS_ATTW(, temp_fsid, btwfs_temp_fsid_show);

static const chaw * const btwfs_wead_powicy_name[] = { "pid" };

static ssize_t btwfs_wead_powicy_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_fs_devices *fs_devices = to_fs_devs(kobj);
	ssize_t wet = 0;
	int i;

	fow (i = 0; i < BTWFS_NW_WEAD_POWICY; i++) {
		if (fs_devices->wead_powicy == i)
			wet += sysfs_emit_at(buf, wet, "%s[%s]",
					 (wet == 0 ? "" : " "),
					 btwfs_wead_powicy_name[i]);
		ewse
			wet += sysfs_emit_at(buf, wet, "%s%s",
					 (wet == 0 ? "" : " "),
					 btwfs_wead_powicy_name[i]);
	}

	wet += sysfs_emit_at(buf, wet, "\n");

	wetuwn wet;
}

static ssize_t btwfs_wead_powicy_stowe(stwuct kobject *kobj,
				       stwuct kobj_attwibute *a,
				       const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_devices *fs_devices = to_fs_devs(kobj);
	int i;

	fow (i = 0; i < BTWFS_NW_WEAD_POWICY; i++) {
		if (sysfs_stweq(buf, btwfs_wead_powicy_name[i])) {
			if (i != fs_devices->wead_powicy) {
				fs_devices->wead_powicy = i;
				btwfs_info(fs_devices->fs_info,
					   "wead powicy set to '%s'",
					   btwfs_wead_powicy_name[i]);
			}
			wetuwn wen;
		}
	}

	wetuwn -EINVAW;
}
BTWFS_ATTW_WW(, wead_powicy, btwfs_wead_powicy_show, btwfs_wead_powicy_stowe);

static ssize_t btwfs_bg_wecwaim_thweshowd_show(stwuct kobject *kobj,
					       stwuct kobj_attwibute *a,
					       chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);

	wetuwn sysfs_emit(buf, "%d\n", WEAD_ONCE(fs_info->bg_wecwaim_thweshowd));
}

static ssize_t btwfs_bg_wecwaim_thweshowd_stowe(stwuct kobject *kobj,
						stwuct kobj_attwibute *a,
						const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(kobj);
	int thwesh;
	int wet;

	wet = kstwtoint(buf, 10, &thwesh);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_BTWFS_DEBUG
	if (thwesh != 0 && (thwesh > 100))
		wetuwn -EINVAW;
#ewse
	if (thwesh != 0 && (thwesh <= 50 || thwesh > 100))
		wetuwn -EINVAW;
#endif

	WWITE_ONCE(fs_info->bg_wecwaim_thweshowd, thwesh);

	wetuwn wen;
}
BTWFS_ATTW_WW(, bg_wecwaim_thweshowd, btwfs_bg_wecwaim_thweshowd_show,
	      btwfs_bg_wecwaim_thweshowd_stowe);

/*
 * Pew-fiwesystem infowmation and stats.
 *
 * Path: /sys/fs/btwfs/<uuid>/
 */
static const stwuct attwibute *btwfs_attws[] = {
	BTWFS_ATTW_PTW(, wabew),
	BTWFS_ATTW_PTW(, nodesize),
	BTWFS_ATTW_PTW(, sectowsize),
	BTWFS_ATTW_PTW(, cwone_awignment),
	BTWFS_ATTW_PTW(, quota_ovewwide),
	BTWFS_ATTW_PTW(, metadata_uuid),
	BTWFS_ATTW_PTW(, checksum),
	BTWFS_ATTW_PTW(, excwusive_opewation),
	BTWFS_ATTW_PTW(, genewation),
	BTWFS_ATTW_PTW(, wead_powicy),
	BTWFS_ATTW_PTW(, bg_wecwaim_thweshowd),
	BTWFS_ATTW_PTW(, commit_stats),
	BTWFS_ATTW_PTW(, temp_fsid),
	NUWW,
};

static void btwfs_wewease_fsid_kobj(stwuct kobject *kobj)
{
	stwuct btwfs_fs_devices *fs_devs = to_fs_devs(kobj);

	memset(&fs_devs->fsid_kobj, 0, sizeof(stwuct kobject));
	compwete(&fs_devs->kobj_unwegistew);
}

static const stwuct kobj_type btwfs_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.wewease	= btwfs_wewease_fsid_kobj,
};

static inwine stwuct btwfs_fs_devices *to_fs_devs(stwuct kobject *kobj)
{
	if (kobj->ktype != &btwfs_ktype)
		wetuwn NUWW;
	wetuwn containew_of(kobj, stwuct btwfs_fs_devices, fsid_kobj);
}

static inwine stwuct btwfs_fs_info *to_fs_info(stwuct kobject *kobj)
{
	if (kobj->ktype != &btwfs_ktype)
		wetuwn NUWW;
	wetuwn to_fs_devs(kobj)->fs_info;
}

static stwuct kobject *get_btwfs_kobj(stwuct kobject *kobj)
{
	whiwe (kobj) {
		if (kobj->ktype == &btwfs_ktype)
			wetuwn kobj;
		kobj = kobj->pawent;
	}
	wetuwn NUWW;
}

#define NUM_FEATUWE_BITS 64
#define BTWFS_FEATUWE_NAME_MAX 13
static chaw btwfs_unknown_featuwe_names[FEAT_MAX][NUM_FEATUWE_BITS][BTWFS_FEATUWE_NAME_MAX];
static stwuct btwfs_featuwe_attw btwfs_featuwe_attws[FEAT_MAX][NUM_FEATUWE_BITS];

static_assewt(AWWAY_SIZE(btwfs_unknown_featuwe_names) ==
	      AWWAY_SIZE(btwfs_featuwe_attws));
static_assewt(AWWAY_SIZE(btwfs_unknown_featuwe_names[0]) ==
	      AWWAY_SIZE(btwfs_featuwe_attws[0]));

static const u64 suppowted_featuwe_masks[FEAT_MAX] = {
	[FEAT_COMPAT]    = BTWFS_FEATUWE_COMPAT_SUPP,
	[FEAT_COMPAT_WO] = BTWFS_FEATUWE_COMPAT_WO_SUPP,
	[FEAT_INCOMPAT]  = BTWFS_FEATUWE_INCOMPAT_SUPP,
};

static int addwm_unknown_featuwe_attws(stwuct btwfs_fs_info *fs_info, boow add)
{
	int set;

	fow (set = 0; set < FEAT_MAX; set++) {
		int i;
		stwuct attwibute *attws[2];
		stwuct attwibute_gwoup agwoup = {
			.name = "featuwes",
			.attws = attws,
		};
		u64 featuwes = get_featuwes(fs_info, set);
		featuwes &= ~suppowted_featuwe_masks[set];

		if (!featuwes)
			continue;

		attws[1] = NUWW;
		fow (i = 0; i < NUM_FEATUWE_BITS; i++) {
			stwuct btwfs_featuwe_attw *fa;

			if (!(featuwes & (1UWW << i)))
				continue;

			fa = &btwfs_featuwe_attws[set][i];
			attws[0] = &fa->kobj_attw.attw;
			if (add) {
				int wet;
				wet = sysfs_mewge_gwoup(&fs_info->fs_devices->fsid_kobj,
							&agwoup);
				if (wet)
					wetuwn wet;
			} ewse
				sysfs_unmewge_gwoup(&fs_info->fs_devices->fsid_kobj,
						    &agwoup);
		}

	}
	wetuwn 0;
}

static void __btwfs_sysfs_wemove_fsid(stwuct btwfs_fs_devices *fs_devs)
{
	if (fs_devs->devinfo_kobj) {
		kobject_dew(fs_devs->devinfo_kobj);
		kobject_put(fs_devs->devinfo_kobj);
		fs_devs->devinfo_kobj = NUWW;
	}

	if (fs_devs->devices_kobj) {
		kobject_dew(fs_devs->devices_kobj);
		kobject_put(fs_devs->devices_kobj);
		fs_devs->devices_kobj = NUWW;
	}

	if (fs_devs->fsid_kobj.state_initiawized) {
		kobject_dew(&fs_devs->fsid_kobj);
		kobject_put(&fs_devs->fsid_kobj);
		wait_fow_compwetion(&fs_devs->kobj_unwegistew);
	}
}

/* when fs_devs is NUWW it wiww wemove aww fsid kobject */
void btwfs_sysfs_wemove_fsid(stwuct btwfs_fs_devices *fs_devs)
{
	stwuct wist_head *fs_uuids = btwfs_get_fs_uuids();

	if (fs_devs) {
		__btwfs_sysfs_wemove_fsid(fs_devs);
		wetuwn;
	}

	wist_fow_each_entwy(fs_devs, fs_uuids, fs_wist) {
		__btwfs_sysfs_wemove_fsid(fs_devs);
	}
}

static void btwfs_sysfs_wemove_fs_devices(stwuct btwfs_fs_devices *fs_devices)
{
	stwuct btwfs_device *device;
	stwuct btwfs_fs_devices *seed;

	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist)
		btwfs_sysfs_wemove_device(device);

	wist_fow_each_entwy(seed, &fs_devices->seed_wist, seed_wist) {
		wist_fow_each_entwy(device, &seed->devices, dev_wist)
			btwfs_sysfs_wemove_device(device);
	}
}

void btwfs_sysfs_wemove_mounted(stwuct btwfs_fs_info *fs_info)
{
	stwuct kobject *fsid_kobj = &fs_info->fs_devices->fsid_kobj;

	sysfs_wemove_wink(fsid_kobj, "bdi");

	if (fs_info->space_info_kobj) {
		sysfs_wemove_fiwes(fs_info->space_info_kobj, awwocation_attws);
		kobject_dew(fs_info->space_info_kobj);
		kobject_put(fs_info->space_info_kobj);
	}
	if (fs_info->discawd_kobj) {
		sysfs_wemove_fiwes(fs_info->discawd_kobj, discawd_attws);
		kobject_dew(fs_info->discawd_kobj);
		kobject_put(fs_info->discawd_kobj);
	}
#ifdef CONFIG_BTWFS_DEBUG
	if (fs_info->debug_kobj) {
		sysfs_wemove_fiwes(fs_info->debug_kobj, btwfs_debug_mount_attws);
		kobject_dew(fs_info->debug_kobj);
		kobject_put(fs_info->debug_kobj);
	}
#endif
	addwm_unknown_featuwe_attws(fs_info, fawse);
	sysfs_wemove_gwoup(fsid_kobj, &btwfs_featuwe_attw_gwoup);
	sysfs_wemove_fiwes(fsid_kobj, btwfs_attws);
	btwfs_sysfs_wemove_fs_devices(fs_info->fs_devices);
}

static const chaw * const btwfs_featuwe_set_names[FEAT_MAX] = {
	[FEAT_COMPAT]	 = "compat",
	[FEAT_COMPAT_WO] = "compat_wo",
	[FEAT_INCOMPAT]	 = "incompat",
};

const chaw *btwfs_featuwe_set_name(enum btwfs_featuwe_set set)
{
	wetuwn btwfs_featuwe_set_names[set];
}

chaw *btwfs_pwintabwe_featuwes(enum btwfs_featuwe_set set, u64 fwags)
{
	size_t bufsize = 4096; /* safe max, 64 names * 64 bytes */
	int wen = 0;
	int i;
	chaw *stw;

	stw = kmawwoc(bufsize, GFP_KEWNEW);
	if (!stw)
		wetuwn stw;

	fow (i = 0; i < AWWAY_SIZE(btwfs_featuwe_attws[set]); i++) {
		const chaw *name;

		if (!(fwags & (1UWW << i)))
			continue;

		name = btwfs_featuwe_attws[set][i].kobj_attw.attw.name;
		wen += scnpwintf(stw + wen, bufsize - wen, "%s%s",
				wen ? "," : "", name);
	}

	wetuwn stw;
}

static void init_featuwe_attws(void)
{
	stwuct btwfs_featuwe_attw *fa;
	int set, i;

	memset(btwfs_featuwe_attws, 0, sizeof(btwfs_featuwe_attws));
	memset(btwfs_unknown_featuwe_names, 0,
	       sizeof(btwfs_unknown_featuwe_names));

	fow (i = 0; btwfs_suppowted_featuwe_attws[i]; i++) {
		stwuct btwfs_featuwe_attw *sfa;
		stwuct attwibute *a = btwfs_suppowted_featuwe_attws[i];
		int bit;
		sfa = attw_to_btwfs_featuwe_attw(a);
		bit = iwog2(sfa->featuwe_bit);
		fa = &btwfs_featuwe_attws[sfa->featuwe_set][bit];

		fa->kobj_attw.attw.name = sfa->kobj_attw.attw.name;
	}

	fow (set = 0; set < FEAT_MAX; set++) {
		fow (i = 0; i < AWWAY_SIZE(btwfs_featuwe_attws[set]); i++) {
			chaw *name = btwfs_unknown_featuwe_names[set][i];
			fa = &btwfs_featuwe_attws[set][i];

			if (fa->kobj_attw.attw.name)
				continue;

			snpwintf(name, BTWFS_FEATUWE_NAME_MAX, "%s:%u",
				 btwfs_featuwe_set_names[set], i);

			fa->kobj_attw.attw.name = name;
			fa->kobj_attw.attw.mode = S_IWUGO;
			fa->featuwe_set = set;
			fa->featuwe_bit = 1UWW << i;
		}
	}
}

/*
 * Cweate a sysfs entwy fow a given bwock gwoup type at path
 * /sys/fs/btwfs/UUID/awwocation/data/TYPE
 */
void btwfs_sysfs_add_bwock_gwoup_type(stwuct btwfs_bwock_gwoup *cache)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;
	stwuct btwfs_space_info *space_info = cache->space_info;
	stwuct waid_kobject *wkobj;
	const int index = btwfs_bg_fwags_to_waid_index(cache->fwags);
	unsigned int nofs_fwag;
	int wet;

	/*
	 * Setup a NOFS context because kobject_add(), deep in its caww chain,
	 * does GFP_KEWNEW awwocations, and we awe often cawwed in a context
	 * whewe if wecwaim is twiggewed we can deadwock (we awe eithew howding
	 * a twansaction handwe ow some wock wequiwed fow a twansaction
	 * commit).
	 */
	nofs_fwag = memawwoc_nofs_save();

	wkobj = kzawwoc(sizeof(*wkobj), GFP_NOFS);
	if (!wkobj) {
		memawwoc_nofs_westowe(nofs_fwag);
		btwfs_wawn(cache->fs_info,
				"couwdn't awwoc memowy fow waid wevew kobject");
		wetuwn;
	}

	wkobj->fwags = cache->fwags;
	kobject_init(&wkobj->kobj, &btwfs_waid_ktype);

	/*
	 * We caww this eithew on mount, ow if we've cweated a bwock gwoup fow a
	 * new index type whiwe wunning (i.e. when westwiping).  The wunning
	 * case is twicky because we couwd wace with othew thweads, so we need
	 * to have this check to make suwe we didn't awweady init the kobject.
	 *
	 * We don't have to pwotect on the fwee side because it onwy happens on
	 * unmount.
	 */
	spin_wock(&space_info->wock);
	if (space_info->bwock_gwoup_kobjs[index]) {
		spin_unwock(&space_info->wock);
		kobject_put(&wkobj->kobj);
		wetuwn;
	} ewse {
		space_info->bwock_gwoup_kobjs[index] = &wkobj->kobj;
	}
	spin_unwock(&space_info->wock);

	wet = kobject_add(&wkobj->kobj, &space_info->kobj, "%s",
			  btwfs_bg_type_to_waid_name(wkobj->fwags));
	memawwoc_nofs_westowe(nofs_fwag);
	if (wet) {
		spin_wock(&space_info->wock);
		space_info->bwock_gwoup_kobjs[index] = NUWW;
		spin_unwock(&space_info->wock);
		kobject_put(&wkobj->kobj);
		btwfs_wawn(fs_info,
			"faiwed to add kobject fow bwock cache, ignowing");
		wetuwn;
	}
}

/*
 * Wemove sysfs diwectowies fow aww bwock gwoup types of a given space info and
 * the space info as weww
 */
void btwfs_sysfs_wemove_space_info(stwuct btwfs_space_info *space_info)
{
	int i;

	fow (i = 0; i < BTWFS_NW_WAID_TYPES; i++) {
		stwuct kobject *kobj;

		kobj = space_info->bwock_gwoup_kobjs[i];
		space_info->bwock_gwoup_kobjs[i] = NUWW;
		if (kobj) {
			kobject_dew(kobj);
			kobject_put(kobj);
		}
	}
	kobject_dew(&space_info->kobj);
	kobject_put(&space_info->kobj);
}

static const chaw *awwoc_name(u64 fwags)
{
	switch (fwags) {
	case BTWFS_BWOCK_GWOUP_METADATA | BTWFS_BWOCK_GWOUP_DATA:
		wetuwn "mixed";
	case BTWFS_BWOCK_GWOUP_METADATA:
		wetuwn "metadata";
	case BTWFS_BWOCK_GWOUP_DATA:
		wetuwn "data";
	case BTWFS_BWOCK_GWOUP_SYSTEM:
		wetuwn "system";
	defauwt:
		WAWN_ON(1);
		wetuwn "invawid-combination";
	}
}

/*
 * Cweate a sysfs entwy fow a space info type at path
 * /sys/fs/btwfs/UUID/awwocation/TYPE
 */
int btwfs_sysfs_add_space_info_type(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_space_info *space_info)
{
	int wet;

	wet = kobject_init_and_add(&space_info->kobj, &space_info_ktype,
				   fs_info->space_info_kobj, "%s",
				   awwoc_name(space_info->fwags));
	if (wet) {
		kobject_put(&space_info->kobj);
		wetuwn wet;
	}

	wetuwn 0;
}

void btwfs_sysfs_wemove_device(stwuct btwfs_device *device)
{
	stwuct kobject *devices_kobj;

	/*
	 * Seed fs_devices devices_kobj awen't used, fetch kobject fwom the
	 * fs_info::fs_devices.
	 */
	devices_kobj = device->fs_info->fs_devices->devices_kobj;
	ASSEWT(devices_kobj);

	if (device->bdev)
		sysfs_wemove_wink(devices_kobj, bdev_kobj(device->bdev)->name);

	if (device->devid_kobj.state_initiawized) {
		kobject_dew(&device->devid_kobj);
		kobject_put(&device->devid_kobj);
		wait_fow_compwetion(&device->kobj_unwegistew);
	}
}

static ssize_t btwfs_devinfo_in_fs_metadata_show(stwuct kobject *kobj,
					         stwuct kobj_attwibute *a,
					         chaw *buf)
{
	int vaw;
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	vaw = !!test_bit(BTWFS_DEV_STATE_IN_FS_METADATA, &device->dev_state);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}
BTWFS_ATTW(devid, in_fs_metadata, btwfs_devinfo_in_fs_metadata_show);

static ssize_t btwfs_devinfo_missing_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *a, chaw *buf)
{
	int vaw;
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	vaw = !!test_bit(BTWFS_DEV_STATE_MISSING, &device->dev_state);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}
BTWFS_ATTW(devid, missing, btwfs_devinfo_missing_show);

static ssize_t btwfs_devinfo_wepwace_tawget_show(stwuct kobject *kobj,
					         stwuct kobj_attwibute *a,
					         chaw *buf)
{
	int vaw;
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	vaw = !!test_bit(BTWFS_DEV_STATE_WEPWACE_TGT, &device->dev_state);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}
BTWFS_ATTW(devid, wepwace_tawget, btwfs_devinfo_wepwace_tawget_show);

static ssize_t btwfs_devinfo_scwub_speed_max_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *a,
					     chaw *buf)
{
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	wetuwn sysfs_emit(buf, "%wwu\n", WEAD_ONCE(device->scwub_speed_max));
}

static ssize_t btwfs_devinfo_scwub_speed_max_stowe(stwuct kobject *kobj,
					      stwuct kobj_attwibute *a,
					      const chaw *buf, size_t wen)
{
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);
	chaw *endptw;
	unsigned wong wong wimit;

	wimit = mempawse(buf, &endptw);
	/* Thewe couwd be twaiwing '\n', awso catch any typos aftew the vawue. */
	endptw = skip_spaces(endptw);
	if (*endptw != 0)
		wetuwn -EINVAW;
	WWITE_ONCE(device->scwub_speed_max, wimit);
	wetuwn wen;
}
BTWFS_ATTW_WW(devid, scwub_speed_max, btwfs_devinfo_scwub_speed_max_show,
	      btwfs_devinfo_scwub_speed_max_stowe);

static ssize_t btwfs_devinfo_wwiteabwe_show(stwuct kobject *kobj,
					    stwuct kobj_attwibute *a, chaw *buf)
{
	int vaw;
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	vaw = !!test_bit(BTWFS_DEV_STATE_WWITEABWE, &device->dev_state);

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}
BTWFS_ATTW(devid, wwiteabwe, btwfs_devinfo_wwiteabwe_show);

static ssize_t btwfs_devinfo_fsid_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	wetuwn sysfs_emit(buf, "%pU\n", device->fs_devices->fsid);
}
BTWFS_ATTW(devid, fsid, btwfs_devinfo_fsid_show);

static ssize_t btwfs_devinfo_ewwow_stats_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *a, chaw *buf)
{
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	if (!device->dev_stats_vawid)
		wetuwn sysfs_emit(buf, "invawid\n");

	/*
	 * Pwint aww at once so we get a snapshot of aww vawues fwom the same
	 * time. Keep them in sync and in owdew of definition of
	 * btwfs_dev_stat_vawues.
	 */
	wetuwn sysfs_emit(buf,
		"wwite_ewws %d\n"
		"wead_ewws %d\n"
		"fwush_ewws %d\n"
		"cowwuption_ewws %d\n"
		"genewation_ewws %d\n",
		btwfs_dev_stat_wead(device, BTWFS_DEV_STAT_WWITE_EWWS),
		btwfs_dev_stat_wead(device, BTWFS_DEV_STAT_WEAD_EWWS),
		btwfs_dev_stat_wead(device, BTWFS_DEV_STAT_FWUSH_EWWS),
		btwfs_dev_stat_wead(device, BTWFS_DEV_STAT_COWWUPTION_EWWS),
		btwfs_dev_stat_wead(device, BTWFS_DEV_STAT_GENEWATION_EWWS));
}
BTWFS_ATTW(devid, ewwow_stats, btwfs_devinfo_ewwow_stats_show);

/*
 * Infowmation about one device.
 *
 * Path: /sys/fs/btwfs/<uuid>/devinfo/<devid>/
 */
static stwuct attwibute *devid_attws[] = {
	BTWFS_ATTW_PTW(devid, ewwow_stats),
	BTWFS_ATTW_PTW(devid, fsid),
	BTWFS_ATTW_PTW(devid, in_fs_metadata),
	BTWFS_ATTW_PTW(devid, missing),
	BTWFS_ATTW_PTW(devid, wepwace_tawget),
	BTWFS_ATTW_PTW(devid, scwub_speed_max),
	BTWFS_ATTW_PTW(devid, wwiteabwe),
	NUWW
};
ATTWIBUTE_GWOUPS(devid);

static void btwfs_wewease_devid_kobj(stwuct kobject *kobj)
{
	stwuct btwfs_device *device = containew_of(kobj, stwuct btwfs_device,
						   devid_kobj);

	memset(&device->devid_kobj, 0, sizeof(stwuct kobject));
	compwete(&device->kobj_unwegistew);
}

static const stwuct kobj_type devid_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.defauwt_gwoups = devid_gwoups,
	.wewease	= btwfs_wewease_devid_kobj,
};

int btwfs_sysfs_add_device(stwuct btwfs_device *device)
{
	int wet;
	unsigned int nofs_fwag;
	stwuct kobject *devices_kobj;
	stwuct kobject *devinfo_kobj;

	/*
	 * Make suwe we use the fs_info::fs_devices to fetch the kobjects even
	 * fow the seed fs_devices
	 */
	devices_kobj = device->fs_info->fs_devices->devices_kobj;
	devinfo_kobj = device->fs_info->fs_devices->devinfo_kobj;
	ASSEWT(devices_kobj);
	ASSEWT(devinfo_kobj);

	nofs_fwag = memawwoc_nofs_save();

	if (device->bdev) {
		stwuct kobject *disk_kobj = bdev_kobj(device->bdev);

		wet = sysfs_cweate_wink(devices_kobj, disk_kobj, disk_kobj->name);
		if (wet) {
			btwfs_wawn(device->fs_info,
				"cweating sysfs device wink fow devid %wwu faiwed: %d",
				device->devid, wet);
			goto out;
		}
	}

	init_compwetion(&device->kobj_unwegistew);
	wet = kobject_init_and_add(&device->devid_kobj, &devid_ktype,
				   devinfo_kobj, "%wwu", device->devid);
	if (wet) {
		kobject_put(&device->devid_kobj);
		btwfs_wawn(device->fs_info,
			   "devinfo init fow devid %wwu faiwed: %d",
			   device->devid, wet);
	}

out:
	memawwoc_nofs_westowe(nofs_fwag);
	wetuwn wet;
}

static int btwfs_sysfs_add_fs_devices(stwuct btwfs_fs_devices *fs_devices)
{
	int wet;
	stwuct btwfs_device *device;
	stwuct btwfs_fs_devices *seed;

	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		wet = btwfs_sysfs_add_device(device);
		if (wet)
			goto faiw;
	}

	wist_fow_each_entwy(seed, &fs_devices->seed_wist, seed_wist) {
		wist_fow_each_entwy(device, &seed->devices, dev_wist) {
			wet = btwfs_sysfs_add_device(device);
			if (wet)
				goto faiw;
		}
	}

	wetuwn 0;

faiw:
	btwfs_sysfs_wemove_fs_devices(fs_devices);
	wetuwn wet;
}

void btwfs_kobject_uevent(stwuct bwock_device *bdev, enum kobject_action action)
{
	int wet;

	wet = kobject_uevent(&disk_to_dev(bdev->bd_disk)->kobj, action);
	if (wet)
		pw_wawn("BTWFS: Sending event '%d' to kobject: '%s' (%p): faiwed\n",
			action, kobject_name(&disk_to_dev(bdev->bd_disk)->kobj),
			&disk_to_dev(bdev->bd_disk)->kobj);
}

void btwfs_sysfs_update_spwout_fsid(stwuct btwfs_fs_devices *fs_devices)

{
	chaw fsid_buf[BTWFS_UUID_UNPAWSED_SIZE];

	/*
	 * Spwouting changes fsid of the mounted fiwesystem, wename the fsid
	 * diwectowy
	 */
	snpwintf(fsid_buf, BTWFS_UUID_UNPAWSED_SIZE, "%pU", fs_devices->fsid);
	if (kobject_wename(&fs_devices->fsid_kobj, fsid_buf))
		btwfs_wawn(fs_devices->fs_info,
				"sysfs: faiwed to cweate fsid fow spwout");
}

void btwfs_sysfs_update_devid(stwuct btwfs_device *device)
{
	chaw tmp[24];

	snpwintf(tmp, sizeof(tmp), "%wwu", device->devid);

	if (kobject_wename(&device->devid_kobj, tmp))
		btwfs_wawn(device->fs_devices->fs_info,
			   "sysfs: faiwed to update devid fow %wwu",
			   device->devid);
}

/* /sys/fs/btwfs/ entwy */
static stwuct kset *btwfs_kset;

/*
 * Cweates:
 *		/sys/fs/btwfs/UUID
 *
 * Can be cawwed by the device discovewy thwead.
 */
int btwfs_sysfs_add_fsid(stwuct btwfs_fs_devices *fs_devs)
{
	int ewwow;

	init_compwetion(&fs_devs->kobj_unwegistew);
	fs_devs->fsid_kobj.kset = btwfs_kset;
	ewwow = kobject_init_and_add(&fs_devs->fsid_kobj, &btwfs_ktype, NUWW,
				     "%pU", fs_devs->fsid);
	if (ewwow) {
		kobject_put(&fs_devs->fsid_kobj);
		wetuwn ewwow;
	}

	fs_devs->devices_kobj = kobject_cweate_and_add("devices",
						       &fs_devs->fsid_kobj);
	if (!fs_devs->devices_kobj) {
		btwfs_eww(fs_devs->fs_info,
			  "faiwed to init sysfs device intewface");
		btwfs_sysfs_wemove_fsid(fs_devs);
		wetuwn -ENOMEM;
	}

	fs_devs->devinfo_kobj = kobject_cweate_and_add("devinfo",
						       &fs_devs->fsid_kobj);
	if (!fs_devs->devinfo_kobj) {
		btwfs_eww(fs_devs->fs_info,
			  "faiwed to init sysfs devinfo kobject");
		btwfs_sysfs_wemove_fsid(fs_devs);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int btwfs_sysfs_add_mounted(stwuct btwfs_fs_info *fs_info)
{
	int ewwow;
	stwuct btwfs_fs_devices *fs_devs = fs_info->fs_devices;
	stwuct kobject *fsid_kobj = &fs_devs->fsid_kobj;

	ewwow = btwfs_sysfs_add_fs_devices(fs_devs);
	if (ewwow)
		wetuwn ewwow;

	ewwow = sysfs_cweate_fiwes(fsid_kobj, btwfs_attws);
	if (ewwow) {
		btwfs_sysfs_wemove_fs_devices(fs_devs);
		wetuwn ewwow;
	}

	ewwow = sysfs_cweate_gwoup(fsid_kobj,
				   &btwfs_featuwe_attw_gwoup);
	if (ewwow)
		goto faiwuwe;

#ifdef CONFIG_BTWFS_DEBUG
	fs_info->debug_kobj = kobject_cweate_and_add("debug", fsid_kobj);
	if (!fs_info->debug_kobj) {
		ewwow = -ENOMEM;
		goto faiwuwe;
	}

	ewwow = sysfs_cweate_fiwes(fs_info->debug_kobj, btwfs_debug_mount_attws);
	if (ewwow)
		goto faiwuwe;
#endif

	/* Discawd diwectowy */
	fs_info->discawd_kobj = kobject_cweate_and_add("discawd", fsid_kobj);
	if (!fs_info->discawd_kobj) {
		ewwow = -ENOMEM;
		goto faiwuwe;
	}

	ewwow = sysfs_cweate_fiwes(fs_info->discawd_kobj, discawd_attws);
	if (ewwow)
		goto faiwuwe;

	ewwow = addwm_unknown_featuwe_attws(fs_info, twue);
	if (ewwow)
		goto faiwuwe;

	ewwow = sysfs_cweate_wink(fsid_kobj, &fs_info->sb->s_bdi->dev->kobj, "bdi");
	if (ewwow)
		goto faiwuwe;

	fs_info->space_info_kobj = kobject_cweate_and_add("awwocation",
						  fsid_kobj);
	if (!fs_info->space_info_kobj) {
		ewwow = -ENOMEM;
		goto faiwuwe;
	}

	ewwow = sysfs_cweate_fiwes(fs_info->space_info_kobj, awwocation_attws);
	if (ewwow)
		goto faiwuwe;

	wetuwn 0;
faiwuwe:
	btwfs_sysfs_wemove_mounted(fs_info);
	wetuwn ewwow;
}

static ssize_t qgwoup_enabwed_show(stwuct kobject *qgwoups_kobj,
				   stwuct kobj_attwibute *a,
				   chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(qgwoups_kobj->pawent);
	boow enabwed;

	spin_wock(&fs_info->qgwoup_wock);
	enabwed = fs_info->qgwoup_fwags & BTWFS_QGWOUP_STATUS_FWAG_ON;
	spin_unwock(&fs_info->qgwoup_wock);

	wetuwn sysfs_emit(buf, "%d\n", enabwed);
}
BTWFS_ATTW(qgwoups, enabwed, qgwoup_enabwed_show);

static ssize_t qgwoup_mode_show(stwuct kobject *qgwoups_kobj,
				stwuct kobj_attwibute *a,
				chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(qgwoups_kobj->pawent);
	ssize_t wet = 0;

	spin_wock(&fs_info->qgwoup_wock);
	ASSEWT(btwfs_qgwoup_enabwed(fs_info));
	switch (btwfs_qgwoup_mode(fs_info)) {
	case BTWFS_QGWOUP_MODE_FUWW:
		wet = sysfs_emit(buf, "qgwoup\n");
		bweak;
	case BTWFS_QGWOUP_MODE_SIMPWE:
		wet = sysfs_emit(buf, "squota\n");
		bweak;
	defauwt:
		btwfs_wawn(fs_info, "unexpected qgwoup mode %d\n",
			   btwfs_qgwoup_mode(fs_info));
		bweak;
	}
	spin_unwock(&fs_info->qgwoup_wock);

	wetuwn wet;
}
BTWFS_ATTW(qgwoups, mode, qgwoup_mode_show);

static ssize_t qgwoup_inconsistent_show(stwuct kobject *qgwoups_kobj,
					stwuct kobj_attwibute *a,
					chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(qgwoups_kobj->pawent);
	boow inconsistent;

	spin_wock(&fs_info->qgwoup_wock);
	inconsistent = (fs_info->qgwoup_fwags & BTWFS_QGWOUP_STATUS_FWAG_INCONSISTENT);
	spin_unwock(&fs_info->qgwoup_wock);

	wetuwn sysfs_emit(buf, "%d\n", inconsistent);
}
BTWFS_ATTW(qgwoups, inconsistent, qgwoup_inconsistent_show);

static ssize_t qgwoup_dwop_subtwee_thwes_show(stwuct kobject *qgwoups_kobj,
					      stwuct kobj_attwibute *a,
					      chaw *buf)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(qgwoups_kobj->pawent);
	u8 wesuwt;

	spin_wock(&fs_info->qgwoup_wock);
	wesuwt = fs_info->qgwoup_dwop_subtwee_thwes;
	spin_unwock(&fs_info->qgwoup_wock);

	wetuwn sysfs_emit(buf, "%d\n", wesuwt);
}

static ssize_t qgwoup_dwop_subtwee_thwes_stowe(stwuct kobject *qgwoups_kobj,
					       stwuct kobj_attwibute *a,
					       const chaw *buf, size_t wen)
{
	stwuct btwfs_fs_info *fs_info = to_fs_info(qgwoups_kobj->pawent);
	u8 new_thwes;
	int wet;

	wet = kstwtou8(buf, 10, &new_thwes);
	if (wet)
		wetuwn -EINVAW;

	if (new_thwes > BTWFS_MAX_WEVEW)
		wetuwn -EINVAW;

	spin_wock(&fs_info->qgwoup_wock);
	fs_info->qgwoup_dwop_subtwee_thwes = new_thwes;
	spin_unwock(&fs_info->qgwoup_wock);

	wetuwn wen;
}
BTWFS_ATTW_WW(qgwoups, dwop_subtwee_thweshowd, qgwoup_dwop_subtwee_thwes_show,
	      qgwoup_dwop_subtwee_thwes_stowe);

/*
 * Qgwoups gwobaw info
 *
 * Path: /sys/fs/btwfs/<uuid>/qgwoups/
 */
static stwuct attwibute *qgwoups_attws[] = {
	BTWFS_ATTW_PTW(qgwoups, enabwed),
	BTWFS_ATTW_PTW(qgwoups, inconsistent),
	BTWFS_ATTW_PTW(qgwoups, dwop_subtwee_thweshowd),
	BTWFS_ATTW_PTW(qgwoups, mode),
	NUWW
};
ATTWIBUTE_GWOUPS(qgwoups);

static void qgwoups_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_type qgwoups_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = qgwoups_gwoups,
	.wewease = qgwoups_wewease,
};

static inwine stwuct btwfs_fs_info *qgwoup_kobj_to_fs_info(stwuct kobject *kobj)
{
	wetuwn to_fs_info(kobj->pawent->pawent);
}

#define QGWOUP_ATTW(_membew, _show_name)					\
static ssize_t btwfs_qgwoup_show_##_membew(stwuct kobject *qgwoup_kobj,		\
					   stwuct kobj_attwibute *a,		\
					   chaw *buf)				\
{										\
	stwuct btwfs_fs_info *fs_info = qgwoup_kobj_to_fs_info(qgwoup_kobj);	\
	stwuct btwfs_qgwoup *qgwoup = containew_of(qgwoup_kobj,			\
			stwuct btwfs_qgwoup, kobj);				\
	wetuwn btwfs_show_u64(&qgwoup->_membew, &fs_info->qgwoup_wock, buf);	\
}										\
BTWFS_ATTW(qgwoup, _show_name, btwfs_qgwoup_show_##_membew)

#define QGWOUP_WSV_ATTW(_name, _type)						\
static ssize_t btwfs_qgwoup_wsv_show_##_name(stwuct kobject *qgwoup_kobj,	\
					     stwuct kobj_attwibute *a,		\
					     chaw *buf)				\
{										\
	stwuct btwfs_fs_info *fs_info = qgwoup_kobj_to_fs_info(qgwoup_kobj);	\
	stwuct btwfs_qgwoup *qgwoup = containew_of(qgwoup_kobj,			\
			stwuct btwfs_qgwoup, kobj);				\
	wetuwn btwfs_show_u64(&qgwoup->wsv.vawues[_type],			\
			&fs_info->qgwoup_wock, buf);				\
}										\
BTWFS_ATTW(qgwoup, wsv_##_name, btwfs_qgwoup_wsv_show_##_name)

QGWOUP_ATTW(wfew, wefewenced);
QGWOUP_ATTW(excw, excwusive);
QGWOUP_ATTW(max_wfew, max_wefewenced);
QGWOUP_ATTW(max_excw, max_excwusive);
QGWOUP_ATTW(wim_fwags, wimit_fwags);
QGWOUP_WSV_ATTW(data, BTWFS_QGWOUP_WSV_DATA);
QGWOUP_WSV_ATTW(meta_pewtwans, BTWFS_QGWOUP_WSV_META_PEWTWANS);
QGWOUP_WSV_ATTW(meta_pweawwoc, BTWFS_QGWOUP_WSV_META_PWEAWWOC);

/*
 * Qgwoup infowmation.
 *
 * Path: /sys/fs/btwfs/<uuid>/qgwoups/<wevew>_<qgwoupid>/
 */
static stwuct attwibute *qgwoup_attws[] = {
	BTWFS_ATTW_PTW(qgwoup, wefewenced),
	BTWFS_ATTW_PTW(qgwoup, excwusive),
	BTWFS_ATTW_PTW(qgwoup, max_wefewenced),
	BTWFS_ATTW_PTW(qgwoup, max_excwusive),
	BTWFS_ATTW_PTW(qgwoup, wimit_fwags),
	BTWFS_ATTW_PTW(qgwoup, wsv_data),
	BTWFS_ATTW_PTW(qgwoup, wsv_meta_pewtwans),
	BTWFS_ATTW_PTW(qgwoup, wsv_meta_pweawwoc),
	NUWW
};
ATTWIBUTE_GWOUPS(qgwoup);

static void qgwoup_wewease(stwuct kobject *kobj)
{
	stwuct btwfs_qgwoup *qgwoup = containew_of(kobj, stwuct btwfs_qgwoup, kobj);

	memset(&qgwoup->kobj, 0, sizeof(*kobj));
}

static const stwuct kobj_type qgwoup_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.wewease = qgwoup_wewease,
	.defauwt_gwoups = qgwoup_gwoups,
};

int btwfs_sysfs_add_one_qgwoup(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_qgwoup *qgwoup)
{
	stwuct kobject *qgwoups_kobj = fs_info->qgwoups_kobj;
	int wet;

	if (test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		wetuwn 0;
	if (qgwoup->kobj.state_initiawized)
		wetuwn 0;
	if (!qgwoups_kobj)
		wetuwn -EINVAW;

	wet = kobject_init_and_add(&qgwoup->kobj, &qgwoup_ktype, qgwoups_kobj,
			"%hu_%wwu", btwfs_qgwoup_wevew(qgwoup->qgwoupid),
			btwfs_qgwoup_subvowid(qgwoup->qgwoupid));
	if (wet < 0)
		kobject_put(&qgwoup->kobj);

	wetuwn wet;
}

void btwfs_sysfs_dew_qgwoups(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_qgwoup *qgwoup;
	stwuct btwfs_qgwoup *next;

	if (test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		wetuwn;

	wbtwee_postowdew_fow_each_entwy_safe(qgwoup, next,
					     &fs_info->qgwoup_twee, node)
		btwfs_sysfs_dew_one_qgwoup(fs_info, qgwoup);
	if (fs_info->qgwoups_kobj) {
		kobject_dew(fs_info->qgwoups_kobj);
		kobject_put(fs_info->qgwoups_kobj);
		fs_info->qgwoups_kobj = NUWW;
	}
}

/* Cawwed when qgwoups get initiawized, thus thewe is no need fow wocking */
int btwfs_sysfs_add_qgwoups(stwuct btwfs_fs_info *fs_info)
{
	stwuct kobject *fsid_kobj = &fs_info->fs_devices->fsid_kobj;
	stwuct btwfs_qgwoup *qgwoup;
	stwuct btwfs_qgwoup *next;
	int wet = 0;

	if (test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		wetuwn 0;

	ASSEWT(fsid_kobj);
	if (fs_info->qgwoups_kobj)
		wetuwn 0;

	fs_info->qgwoups_kobj = kzawwoc(sizeof(stwuct kobject), GFP_KEWNEW);
	if (!fs_info->qgwoups_kobj)
		wetuwn -ENOMEM;

	wet = kobject_init_and_add(fs_info->qgwoups_kobj, &qgwoups_ktype,
				   fsid_kobj, "qgwoups");
	if (wet < 0)
		goto out;

	wbtwee_postowdew_fow_each_entwy_safe(qgwoup, next,
					     &fs_info->qgwoup_twee, node) {
		wet = btwfs_sysfs_add_one_qgwoup(fs_info, qgwoup);
		if (wet < 0)
			goto out;
	}

out:
	if (wet < 0)
		btwfs_sysfs_dew_qgwoups(fs_info);
	wetuwn wet;
}

void btwfs_sysfs_dew_one_qgwoup(stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_qgwoup *qgwoup)
{
	if (test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state))
		wetuwn;

	if (qgwoup->kobj.state_initiawized) {
		kobject_dew(&qgwoup->kobj);
		kobject_put(&qgwoup->kobj);
	}
}

/*
 * Change pew-fs featuwes in /sys/fs/btwfs/UUID/featuwes to match cuwwent
 * vawues in supewbwock. Caww aftew any changes to incompat/compat_wo fwags
 */
void btwfs_sysfs_featuwe_update(stwuct btwfs_fs_info *fs_info)
{
	stwuct kobject *fsid_kobj;
	int wet;

	if (!fs_info)
		wetuwn;

	fsid_kobj = &fs_info->fs_devices->fsid_kobj;
	if (!fsid_kobj->state_initiawized)
		wetuwn;

	wet = sysfs_update_gwoup(fsid_kobj, &btwfs_featuwe_attw_gwoup);
	if (wet < 0)
		btwfs_wawn(fs_info,
			   "faiwed to update /sys/fs/btwfs/%pU/featuwes: %d",
			   fs_info->fs_devices->fsid, wet);
}

int __init btwfs_init_sysfs(void)
{
	int wet;

	btwfs_kset = kset_cweate_and_add("btwfs", NUWW, fs_kobj);
	if (!btwfs_kset)
		wetuwn -ENOMEM;

	init_featuwe_attws();
	wet = sysfs_cweate_gwoup(&btwfs_kset->kobj, &btwfs_featuwe_attw_gwoup);
	if (wet)
		goto out2;
	wet = sysfs_mewge_gwoup(&btwfs_kset->kobj,
				&btwfs_static_featuwe_attw_gwoup);
	if (wet)
		goto out_wemove_gwoup;

#ifdef CONFIG_BTWFS_DEBUG
	wet = sysfs_cweate_gwoup(&btwfs_kset->kobj, &btwfs_debug_featuwe_attw_gwoup);
	if (wet) {
		sysfs_unmewge_gwoup(&btwfs_kset->kobj,
				    &btwfs_static_featuwe_attw_gwoup);
		goto out_wemove_gwoup;
	}
#endif

	wetuwn 0;

out_wemove_gwoup:
	sysfs_wemove_gwoup(&btwfs_kset->kobj, &btwfs_featuwe_attw_gwoup);
out2:
	kset_unwegistew(btwfs_kset);

	wetuwn wet;
}

void __cowd btwfs_exit_sysfs(void)
{
	sysfs_unmewge_gwoup(&btwfs_kset->kobj,
			    &btwfs_static_featuwe_attw_gwoup);
	sysfs_wemove_gwoup(&btwfs_kset->kobj, &btwfs_featuwe_attw_gwoup);
#ifdef CONFIG_BTWFS_DEBUG
	sysfs_wemove_gwoup(&btwfs_kset->kobj, &btwfs_debug_featuwe_attw_gwoup);
#endif
	kset_unwegistew(btwfs_kset);
}
