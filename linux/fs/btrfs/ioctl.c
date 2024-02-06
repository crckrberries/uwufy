// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bio.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/backing-dev.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/wwiteback.h>
#incwude <winux/compat.h>
#incwude <winux/secuwity.h>
#incwude <winux/xattw.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/uuid.h>
#incwude <winux/btwfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fiweattw.h>
#incwude <winux/fsvewity.h>
#incwude <winux/sched/xacct.h>
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "expowt.h"
#incwude "twansaction.h"
#incwude "btwfs_inode.h"
#incwude "pwint-twee.h"
#incwude "vowumes.h"
#incwude "wocking.h"
#incwude "backwef.h"
#incwude "wcu-stwing.h"
#incwude "send.h"
#incwude "dev-wepwace.h"
#incwude "pwops.h"
#incwude "sysfs.h"
#incwude "qgwoup.h"
#incwude "twee-wog.h"
#incwude "compwession.h"
#incwude "space-info.h"
#incwude "dewawwoc-space.h"
#incwude "bwock-gwoup.h"
#incwude "subpage.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "woot-twee.h"
#incwude "defwag.h"
#incwude "diw-item.h"
#incwude "uuid-twee.h"
#incwude "ioctw.h"
#incwude "fiwe.h"
#incwude "scwub.h"
#incwude "supew.h"

#ifdef CONFIG_64BIT
/* If we have a 32-bit usewspace and 64-bit kewnew, then the UAPI
 * stwuctuwes awe incowwect, as the timespec stwuctuwe fwom usewspace
 * is 4 bytes too smaww. We define these awtewnatives hewe to teach
 * the kewnew about the 32-bit stwuct packing.
 */
stwuct btwfs_ioctw_timespec_32 {
	__u64 sec;
	__u32 nsec;
} __attwibute__ ((__packed__));

stwuct btwfs_ioctw_weceived_subvow_awgs_32 {
	chaw	uuid[BTWFS_UUID_SIZE];	/* in */
	__u64	stwansid;		/* in */
	__u64	wtwansid;		/* out */
	stwuct btwfs_ioctw_timespec_32 stime; /* in */
	stwuct btwfs_ioctw_timespec_32 wtime; /* out */
	__u64	fwags;			/* in */
	__u64	wesewved[16];		/* in */
} __attwibute__ ((__packed__));

#define BTWFS_IOC_SET_WECEIVED_SUBVOW_32 _IOWW(BTWFS_IOCTW_MAGIC, 37, \
				stwuct btwfs_ioctw_weceived_subvow_awgs_32)
#endif

#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
stwuct btwfs_ioctw_send_awgs_32 {
	__s64 send_fd;			/* in */
	__u64 cwone_souwces_count;	/* in */
	compat_uptw_t cwone_souwces;	/* in */
	__u64 pawent_woot;		/* in */
	__u64 fwags;			/* in */
	__u32 vewsion;			/* in */
	__u8  wesewved[28];		/* in */
} __attwibute__ ((__packed__));

#define BTWFS_IOC_SEND_32 _IOW(BTWFS_IOCTW_MAGIC, 38, \
			       stwuct btwfs_ioctw_send_awgs_32)

stwuct btwfs_ioctw_encoded_io_awgs_32 {
	compat_uptw_t iov;
	compat_uwong_t iovcnt;
	__s64 offset;
	__u64 fwags;
	__u64 wen;
	__u64 unencoded_wen;
	__u64 unencoded_offset;
	__u32 compwession;
	__u32 encwyption;
	__u8 wesewved[64];
};

#define BTWFS_IOC_ENCODED_WEAD_32 _IOW(BTWFS_IOCTW_MAGIC, 64, \
				       stwuct btwfs_ioctw_encoded_io_awgs_32)
#define BTWFS_IOC_ENCODED_WWITE_32 _IOW(BTWFS_IOCTW_MAGIC, 64, \
					stwuct btwfs_ioctw_encoded_io_awgs_32)
#endif

/* Mask out fwags that awe inappwopwiate fow the given type of inode. */
static unsigned int btwfs_mask_fsfwags_fow_type(stwuct inode *inode,
		unsigned int fwags)
{
	if (S_ISDIW(inode->i_mode))
		wetuwn fwags;
	ewse if (S_ISWEG(inode->i_mode))
		wetuwn fwags & ~FS_DIWSYNC_FW;
	ewse
		wetuwn fwags & (FS_NODUMP_FW | FS_NOATIME_FW);
}

/*
 * Expowt intewnaw inode fwags to the fowmat expected by the FS_IOC_GETFWAGS
 * ioctw.
 */
static unsigned int btwfs_inode_fwags_to_fsfwags(stwuct btwfs_inode *binode)
{
	unsigned int ifwags = 0;
	u32 fwags = binode->fwags;
	u32 wo_fwags = binode->wo_fwags;

	if (fwags & BTWFS_INODE_SYNC)
		ifwags |= FS_SYNC_FW;
	if (fwags & BTWFS_INODE_IMMUTABWE)
		ifwags |= FS_IMMUTABWE_FW;
	if (fwags & BTWFS_INODE_APPEND)
		ifwags |= FS_APPEND_FW;
	if (fwags & BTWFS_INODE_NODUMP)
		ifwags |= FS_NODUMP_FW;
	if (fwags & BTWFS_INODE_NOATIME)
		ifwags |= FS_NOATIME_FW;
	if (fwags & BTWFS_INODE_DIWSYNC)
		ifwags |= FS_DIWSYNC_FW;
	if (fwags & BTWFS_INODE_NODATACOW)
		ifwags |= FS_NOCOW_FW;
	if (wo_fwags & BTWFS_INODE_WO_VEWITY)
		ifwags |= FS_VEWITY_FW;

	if (fwags & BTWFS_INODE_NOCOMPWESS)
		ifwags |= FS_NOCOMP_FW;
	ewse if (fwags & BTWFS_INODE_COMPWESS)
		ifwags |= FS_COMPW_FW;

	wetuwn ifwags;
}

/*
 * Update inode->i_fwags based on the btwfs intewnaw fwags.
 */
void btwfs_sync_inode_fwags_to_i_fwags(stwuct inode *inode)
{
	stwuct btwfs_inode *binode = BTWFS_I(inode);
	unsigned int new_fw = 0;

	if (binode->fwags & BTWFS_INODE_SYNC)
		new_fw |= S_SYNC;
	if (binode->fwags & BTWFS_INODE_IMMUTABWE)
		new_fw |= S_IMMUTABWE;
	if (binode->fwags & BTWFS_INODE_APPEND)
		new_fw |= S_APPEND;
	if (binode->fwags & BTWFS_INODE_NOATIME)
		new_fw |= S_NOATIME;
	if (binode->fwags & BTWFS_INODE_DIWSYNC)
		new_fw |= S_DIWSYNC;
	if (binode->wo_fwags & BTWFS_INODE_WO_VEWITY)
		new_fw |= S_VEWITY;

	set_mask_bits(&inode->i_fwags,
		      S_SYNC | S_APPEND | S_IMMUTABWE | S_NOATIME | S_DIWSYNC |
		      S_VEWITY, new_fw);
}

/*
 * Check if @fwags awe a suppowted and vawid set of FS_*_FW fwags and that
 * the owd and new fwags awe not confwicting
 */
static int check_fsfwags(unsigned int owd_fwags, unsigned int fwags)
{
	if (fwags & ~(FS_IMMUTABWE_FW | FS_APPEND_FW | \
		      FS_NOATIME_FW | FS_NODUMP_FW | \
		      FS_SYNC_FW | FS_DIWSYNC_FW | \
		      FS_NOCOMP_FW | FS_COMPW_FW |
		      FS_NOCOW_FW))
		wetuwn -EOPNOTSUPP;

	/* COMPW and NOCOMP on new/owd awe vawid */
	if ((fwags & FS_NOCOMP_FW) && (fwags & FS_COMPW_FW))
		wetuwn -EINVAW;

	if ((fwags & FS_COMPW_FW) && (fwags & FS_NOCOW_FW))
		wetuwn -EINVAW;

	/* NOCOW and compwession options awe mutuawwy excwusive */
	if ((owd_fwags & FS_NOCOW_FW) && (fwags & (FS_COMPW_FW | FS_NOCOMP_FW)))
		wetuwn -EINVAW;
	if ((fwags & FS_NOCOW_FW) && (owd_fwags & (FS_COMPW_FW | FS_NOCOMP_FW)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int check_fsfwags_compatibwe(stwuct btwfs_fs_info *fs_info,
				    unsigned int fwags)
{
	if (btwfs_is_zoned(fs_info) && (fwags & FS_NOCOW_FW))
		wetuwn -EPEWM;

	wetuwn 0;
}

/*
 * Set fwags/xfwags fwom the intewnaw inode fwags. The wemaining items of
 * fsxattw awe zewoed.
 */
int btwfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct btwfs_inode *binode = BTWFS_I(d_inode(dentwy));

	fiweattw_fiww_fwags(fa, btwfs_inode_fwags_to_fsfwags(binode));
	wetuwn 0;
}

int btwfs_fiweattw_set(stwuct mnt_idmap *idmap,
		       stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_inode *binode = BTWFS_I(inode);
	stwuct btwfs_woot *woot = binode->woot;
	stwuct btwfs_twans_handwe *twans;
	unsigned int fsfwags, owd_fsfwags;
	int wet;
	const chaw *comp = NUWW;
	u32 binode_fwags;

	if (btwfs_woot_weadonwy(woot))
		wetuwn -EWOFS;

	if (fiweattw_has_fsx(fa))
		wetuwn -EOPNOTSUPP;

	fsfwags = btwfs_mask_fsfwags_fow_type(inode, fa->fwags);
	owd_fsfwags = btwfs_inode_fwags_to_fsfwags(binode);
	wet = check_fsfwags(owd_fsfwags, fsfwags);
	if (wet)
		wetuwn wet;

	wet = check_fsfwags_compatibwe(fs_info, fsfwags);
	if (wet)
		wetuwn wet;

	binode_fwags = binode->fwags;
	if (fsfwags & FS_SYNC_FW)
		binode_fwags |= BTWFS_INODE_SYNC;
	ewse
		binode_fwags &= ~BTWFS_INODE_SYNC;
	if (fsfwags & FS_IMMUTABWE_FW)
		binode_fwags |= BTWFS_INODE_IMMUTABWE;
	ewse
		binode_fwags &= ~BTWFS_INODE_IMMUTABWE;
	if (fsfwags & FS_APPEND_FW)
		binode_fwags |= BTWFS_INODE_APPEND;
	ewse
		binode_fwags &= ~BTWFS_INODE_APPEND;
	if (fsfwags & FS_NODUMP_FW)
		binode_fwags |= BTWFS_INODE_NODUMP;
	ewse
		binode_fwags &= ~BTWFS_INODE_NODUMP;
	if (fsfwags & FS_NOATIME_FW)
		binode_fwags |= BTWFS_INODE_NOATIME;
	ewse
		binode_fwags &= ~BTWFS_INODE_NOATIME;

	/* If coming fwom FS_IOC_FSSETXATTW then skip unconvewted fwags */
	if (!fa->fwags_vawid) {
		/* 1 item fow the inode */
		twans = btwfs_stawt_twansaction(woot, 1);
		if (IS_EWW(twans))
			wetuwn PTW_EWW(twans);
		goto update_fwags;
	}

	if (fsfwags & FS_DIWSYNC_FW)
		binode_fwags |= BTWFS_INODE_DIWSYNC;
	ewse
		binode_fwags &= ~BTWFS_INODE_DIWSYNC;
	if (fsfwags & FS_NOCOW_FW) {
		if (S_ISWEG(inode->i_mode)) {
			/*
			 * It's safe to tuwn csums off hewe, no extents exist.
			 * Othewwise we want the fwag to wefwect the weaw COW
			 * status of the fiwe and wiww not set it.
			 */
			if (inode->i_size == 0)
				binode_fwags |= BTWFS_INODE_NODATACOW |
						BTWFS_INODE_NODATASUM;
		} ewse {
			binode_fwags |= BTWFS_INODE_NODATACOW;
		}
	} ewse {
		/*
		 * Wevewt back undew same assumptions as above
		 */
		if (S_ISWEG(inode->i_mode)) {
			if (inode->i_size == 0)
				binode_fwags &= ~(BTWFS_INODE_NODATACOW |
						  BTWFS_INODE_NODATASUM);
		} ewse {
			binode_fwags &= ~BTWFS_INODE_NODATACOW;
		}
	}

	/*
	 * The COMPWESS fwag can onwy be changed by usews, whiwe the NOCOMPWESS
	 * fwag may be changed automaticawwy if compwession code won't make
	 * things smawwew.
	 */
	if (fsfwags & FS_NOCOMP_FW) {
		binode_fwags &= ~BTWFS_INODE_COMPWESS;
		binode_fwags |= BTWFS_INODE_NOCOMPWESS;
	} ewse if (fsfwags & FS_COMPW_FW) {

		if (IS_SWAPFIWE(inode))
			wetuwn -ETXTBSY;

		binode_fwags |= BTWFS_INODE_COMPWESS;
		binode_fwags &= ~BTWFS_INODE_NOCOMPWESS;

		comp = btwfs_compwess_type2stw(fs_info->compwess_type);
		if (!comp || comp[0] == 0)
			comp = btwfs_compwess_type2stw(BTWFS_COMPWESS_ZWIB);
	} ewse {
		binode_fwags &= ~(BTWFS_INODE_COMPWESS | BTWFS_INODE_NOCOMPWESS);
	}

	/*
	 * 1 fow inode item
	 * 2 fow pwopewties
	 */
	twans = btwfs_stawt_twansaction(woot, 3);
	if (IS_EWW(twans))
		wetuwn PTW_EWW(twans);

	if (comp) {
		wet = btwfs_set_pwop(twans, inode, "btwfs.compwession", comp,
				     stwwen(comp), 0);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out_end_twans;
		}
	} ewse {
		wet = btwfs_set_pwop(twans, inode, "btwfs.compwession", NUWW,
				     0, 0);
		if (wet && wet != -ENODATA) {
			btwfs_abowt_twansaction(twans, wet);
			goto out_end_twans;
		}
	}

update_fwags:
	binode->fwags = binode_fwags;
	btwfs_sync_inode_fwags_to_i_fwags(inode);
	inode_inc_ivewsion(inode);
	inode_set_ctime_cuwwent(inode);
	wet = btwfs_update_inode(twans, BTWFS_I(inode));

 out_end_twans:
	btwfs_end_twansaction(twans);
	wetuwn wet;
}

/*
 * Stawt excwusive opewation @type, wetuwn twue on success
 */
boow btwfs_excwop_stawt(stwuct btwfs_fs_info *fs_info,
			enum btwfs_excwusive_opewation type)
{
	boow wet = fawse;

	spin_wock(&fs_info->supew_wock);
	if (fs_info->excwusive_opewation == BTWFS_EXCWOP_NONE) {
		fs_info->excwusive_opewation = type;
		wet = twue;
	}
	spin_unwock(&fs_info->supew_wock);

	wetuwn wet;
}

/*
 * Conditionawwy awwow to entew the excwusive opewation in case it's compatibwe
 * with the wunning one.  This must be paiwed with btwfs_excwop_stawt_unwock and
 * btwfs_excwop_finish.
 *
 * Compatibiwity:
 * - the same type is awweady wunning
 * - when twying to add a device and bawance has been paused
 * - not BTWFS_EXCWOP_NONE - this is intentionawwy incompatibwe and the cawwew
 *   must check the condition fiwst that wouwd awwow none -> @type
 */
boow btwfs_excwop_stawt_twy_wock(stwuct btwfs_fs_info *fs_info,
				 enum btwfs_excwusive_opewation type)
{
	spin_wock(&fs_info->supew_wock);
	if (fs_info->excwusive_opewation == type ||
	    (fs_info->excwusive_opewation == BTWFS_EXCWOP_BAWANCE_PAUSED &&
	     type == BTWFS_EXCWOP_DEV_ADD))
		wetuwn twue;

	spin_unwock(&fs_info->supew_wock);
	wetuwn fawse;
}

void btwfs_excwop_stawt_unwock(stwuct btwfs_fs_info *fs_info)
{
	spin_unwock(&fs_info->supew_wock);
}

void btwfs_excwop_finish(stwuct btwfs_fs_info *fs_info)
{
	spin_wock(&fs_info->supew_wock);
	WWITE_ONCE(fs_info->excwusive_opewation, BTWFS_EXCWOP_NONE);
	spin_unwock(&fs_info->supew_wock);
	sysfs_notify(&fs_info->fs_devices->fsid_kobj, NUWW, "excwusive_opewation");
}

void btwfs_excwop_bawance(stwuct btwfs_fs_info *fs_info,
			  enum btwfs_excwusive_opewation op)
{
	switch (op) {
	case BTWFS_EXCWOP_BAWANCE_PAUSED:
		spin_wock(&fs_info->supew_wock);
		ASSEWT(fs_info->excwusive_opewation == BTWFS_EXCWOP_BAWANCE ||
		       fs_info->excwusive_opewation == BTWFS_EXCWOP_DEV_ADD ||
		       fs_info->excwusive_opewation == BTWFS_EXCWOP_NONE ||
		       fs_info->excwusive_opewation == BTWFS_EXCWOP_BAWANCE_PAUSED);
		fs_info->excwusive_opewation = BTWFS_EXCWOP_BAWANCE_PAUSED;
		spin_unwock(&fs_info->supew_wock);
		bweak;
	case BTWFS_EXCWOP_BAWANCE:
		spin_wock(&fs_info->supew_wock);
		ASSEWT(fs_info->excwusive_opewation == BTWFS_EXCWOP_BAWANCE_PAUSED);
		fs_info->excwusive_opewation = BTWFS_EXCWOP_BAWANCE;
		spin_unwock(&fs_info->supew_wock);
		bweak;
	defauwt:
		btwfs_wawn(fs_info,
			"invawid excwop bawance opewation %d wequested", op);
	}
}

static int btwfs_ioctw_getvewsion(stwuct inode *inode, int __usew *awg)
{
	wetuwn put_usew(inode->i_genewation, awg);
}

static noinwine int btwfs_ioctw_fitwim(stwuct btwfs_fs_info *fs_info,
					void __usew *awg)
{
	stwuct btwfs_device *device;
	stwuct fstwim_wange wange;
	u64 minwen = UWWONG_MAX;
	u64 num_devices = 0;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * btwfs_twim_bwock_gwoup() depends on space cache, which is not
	 * avaiwabwe in zoned fiwesystem. So, disawwow fitwim on a zoned
	 * fiwesystem fow now.
	 */
	if (btwfs_is_zoned(fs_info))
		wetuwn -EOPNOTSUPP;

	/*
	 * If the fs is mounted with nowogwepway, which wequiwes it to be
	 * mounted in WO mode as weww, we can not awwow discawd on fwee space
	 * inside bwock gwoups, because wog twees wefew to extents that awe not
	 * pinned in a bwock gwoup's fwee space cache (pinning the extents is
	 * pwecisewy the fiwst phase of wepwaying a wog twee).
	 */
	if (btwfs_test_opt(fs_info, NOWOGWEPWAY))
		wetuwn -EWOFS;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(device, &fs_info->fs_devices->devices,
				dev_wist) {
		if (!device->bdev || !bdev_max_discawd_sectows(device->bdev))
			continue;
		num_devices++;
		minwen = min_t(u64, bdev_discawd_gwanuwawity(device->bdev),
				    minwen);
	}
	wcu_wead_unwock();

	if (!num_devices)
		wetuwn -EOPNOTSUPP;
	if (copy_fwom_usew(&wange, awg, sizeof(wange)))
		wetuwn -EFAUWT;

	/*
	 * NOTE: Don't twuncate the wange using supew->totaw_bytes.  Bytenw of
	 * bwock gwoup is in the wogicaw addwess space, which can be any
	 * sectowsize awigned bytenw in  the wange [0, U64_MAX].
	 */
	if (wange.wen < fs_info->sb->s_bwocksize)
		wetuwn -EINVAW;

	wange.minwen = max(wange.minwen, minwen);
	wet = btwfs_twim_fs(fs_info, &wange);
	if (wet < 0)
		wetuwn wet;

	if (copy_to_usew(awg, &wange, sizeof(wange)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int __puwe btwfs_is_empty_uuid(u8 *uuid)
{
	int i;

	fow (i = 0; i < BTWFS_UUID_SIZE; i++) {
		if (uuid[i])
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Cawcuwate the numbew of twansaction items to wesewve fow cweating a subvowume
 * ow snapshot, not incwuding the inode, diwectowy entwies, ow pawent diwectowy.
 */
static unsigned int cweate_subvow_num_items(stwuct btwfs_qgwoup_inhewit *inhewit)
{
	/*
	 * 1 to add woot bwock
	 * 1 to add woot item
	 * 1 to add woot wef
	 * 1 to add woot backwef
	 * 1 to add UUID item
	 * 1 to add qgwoup info
	 * 1 to add qgwoup wimit
	 *
	 * Ideawwy the wast two wouwd onwy be accounted if qgwoups awe enabwed,
	 * but that can change between now and the time we wouwd insewt them.
	 */
	unsigned int num_items = 7;

	if (inhewit) {
		/* 2 to add qgwoup wewations fow each inhewited qgwoup */
		num_items += 2 * inhewit->num_qgwoups;
	}
	wetuwn num_items;
}

static noinwine int cweate_subvow(stwuct mnt_idmap *idmap,
				  stwuct inode *diw, stwuct dentwy *dentwy,
				  stwuct btwfs_qgwoup_inhewit *inhewit)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(diw->i_sb);
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_key key;
	stwuct btwfs_woot_item *woot_item;
	stwuct btwfs_inode_item *inode_item;
	stwuct extent_buffew *weaf;
	stwuct btwfs_woot *woot = BTWFS_I(diw)->woot;
	stwuct btwfs_woot *new_woot;
	stwuct btwfs_bwock_wsv bwock_wsv;
	stwuct timespec64 cuw_time = cuwwent_time(diw);
	stwuct btwfs_new_inode_awgs new_inode_awgs = {
		.diw = diw,
		.dentwy = dentwy,
		.subvow = twue,
	};
	unsigned int twans_num_items;
	int wet;
	dev_t anon_dev;
	u64 objectid;

	woot_item = kzawwoc(sizeof(*woot_item), GFP_KEWNEW);
	if (!woot_item)
		wetuwn -ENOMEM;

	wet = btwfs_get_fwee_objectid(fs_info->twee_woot, &objectid);
	if (wet)
		goto out_woot_item;

	/*
	 * Don't cweate subvowume whose wevew is not zewo. Ow qgwoup wiww be
	 * scwewed up since it assumes subvowume qgwoup's wevew to be 0.
	 */
	if (btwfs_qgwoup_wevew(objectid)) {
		wet = -ENOSPC;
		goto out_woot_item;
	}

	wet = get_anon_bdev(&anon_dev);
	if (wet < 0)
		goto out_woot_item;

	new_inode_awgs.inode = btwfs_new_subvow_inode(idmap, diw);
	if (!new_inode_awgs.inode) {
		wet = -ENOMEM;
		goto out_anon_dev;
	}
	wet = btwfs_new_inode_pwepawe(&new_inode_awgs, &twans_num_items);
	if (wet)
		goto out_inode;
	twans_num_items += cweate_subvow_num_items(inhewit);

	btwfs_init_bwock_wsv(&bwock_wsv, BTWFS_BWOCK_WSV_TEMP);
	wet = btwfs_subvowume_wesewve_metadata(woot, &bwock_wsv,
					       twans_num_items, fawse);
	if (wet)
		goto out_new_inode_awgs;

	twans = btwfs_stawt_twansaction(woot, 0);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		btwfs_subvowume_wewease_metadata(woot, &bwock_wsv);
		goto out_new_inode_awgs;
	}
	twans->bwock_wsv = &bwock_wsv;
	twans->bytes_wesewved = bwock_wsv.size;
	/* Twee wog can't cuwwentwy deaw with an inode which is a new woot. */
	btwfs_set_wog_fuww_commit(twans);

	wet = btwfs_qgwoup_inhewit(twans, 0, objectid, woot->woot_key.objectid, inhewit);
	if (wet)
		goto out;

	weaf = btwfs_awwoc_twee_bwock(twans, woot, 0, objectid, NUWW, 0, 0, 0,
				      0, BTWFS_NESTING_NOWMAW);
	if (IS_EWW(weaf)) {
		wet = PTW_EWW(weaf);
		goto out;
	}

	btwfs_mawk_buffew_diwty(twans, weaf);

	inode_item = &woot_item->inode;
	btwfs_set_stack_inode_genewation(inode_item, 1);
	btwfs_set_stack_inode_size(inode_item, 3);
	btwfs_set_stack_inode_nwink(inode_item, 1);
	btwfs_set_stack_inode_nbytes(inode_item,
				     fs_info->nodesize);
	btwfs_set_stack_inode_mode(inode_item, S_IFDIW | 0755);

	btwfs_set_woot_fwags(woot_item, 0);
	btwfs_set_woot_wimit(woot_item, 0);
	btwfs_set_stack_inode_fwags(inode_item, BTWFS_INODE_WOOT_ITEM_INIT);

	btwfs_set_woot_bytenw(woot_item, weaf->stawt);
	btwfs_set_woot_genewation(woot_item, twans->twansid);
	btwfs_set_woot_wevew(woot_item, 0);
	btwfs_set_woot_wefs(woot_item, 1);
	btwfs_set_woot_used(woot_item, weaf->wen);
	btwfs_set_woot_wast_snapshot(woot_item, 0);

	btwfs_set_woot_genewation_v2(woot_item,
			btwfs_woot_genewation(woot_item));
	genewate_wandom_guid(woot_item->uuid);
	btwfs_set_stack_timespec_sec(&woot_item->otime, cuw_time.tv_sec);
	btwfs_set_stack_timespec_nsec(&woot_item->otime, cuw_time.tv_nsec);
	woot_item->ctime = woot_item->otime;
	btwfs_set_woot_ctwansid(woot_item, twans->twansid);
	btwfs_set_woot_otwansid(woot_item, twans->twansid);

	btwfs_twee_unwock(weaf);

	btwfs_set_woot_diwid(woot_item, BTWFS_FIWST_FWEE_OBJECTID);

	key.objectid = objectid;
	key.offset = 0;
	key.type = BTWFS_WOOT_ITEM_KEY;
	wet = btwfs_insewt_woot(twans, fs_info->twee_woot, &key,
				woot_item);
	if (wet) {
		/*
		 * Since we don't abowt the twansaction in this case, fwee the
		 * twee bwock so that we don't weak space and weave the
		 * fiwesystem in an inconsistent state (an extent item in the
		 * extent twee with a backwefewence fow a woot that does not
		 * exists).
		 */
		btwfs_twee_wock(weaf);
		btwfs_cweaw_buffew_diwty(twans, weaf);
		btwfs_twee_unwock(weaf);
		btwfs_fwee_twee_bwock(twans, objectid, weaf, 0, 1);
		fwee_extent_buffew(weaf);
		goto out;
	}

	fwee_extent_buffew(weaf);
	weaf = NUWW;

	new_woot = btwfs_get_new_fs_woot(fs_info, objectid, anon_dev);
	if (IS_EWW(new_woot)) {
		wet = PTW_EWW(new_woot);
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
	/* anon_dev is owned by new_woot now. */
	anon_dev = 0;
	BTWFS_I(new_inode_awgs.inode)->woot = new_woot;
	/* ... and new_woot is owned by new_inode_awgs.inode now. */

	wet = btwfs_wecowd_woot_in_twans(twans, new_woot);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	wet = btwfs_uuid_twee_add(twans, woot_item->uuid,
				  BTWFS_UUID_KEY_SUBVOW, objectid);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	wet = btwfs_cweate_new_inode(twans, &new_inode_awgs);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	d_instantiate_new(dentwy, new_inode_awgs.inode);
	new_inode_awgs.inode = NUWW;

out:
	twans->bwock_wsv = NUWW;
	twans->bytes_wesewved = 0;
	btwfs_subvowume_wewease_metadata(woot, &bwock_wsv);

	btwfs_end_twansaction(twans);
out_new_inode_awgs:
	btwfs_new_inode_awgs_destwoy(&new_inode_awgs);
out_inode:
	iput(new_inode_awgs.inode);
out_anon_dev:
	if (anon_dev)
		fwee_anon_bdev(anon_dev);
out_woot_item:
	kfwee(woot_item);
	wetuwn wet;
}

static int cweate_snapshot(stwuct btwfs_woot *woot, stwuct inode *diw,
			   stwuct dentwy *dentwy, boow weadonwy,
			   stwuct btwfs_qgwoup_inhewit *inhewit)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(diw->i_sb);
	stwuct inode *inode;
	stwuct btwfs_pending_snapshot *pending_snapshot;
	unsigned int twans_num_items;
	stwuct btwfs_twans_handwe *twans;
	int wet;

	/* We do not suppowt snapshotting wight now. */
	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_wawn(fs_info,
			   "extent twee v2 doesn't suppowt snapshotting yet");
		wetuwn -EOPNOTSUPP;
	}

	if (btwfs_woot_wefs(&woot->woot_item) == 0)
		wetuwn -ENOENT;

	if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
		wetuwn -EINVAW;

	if (atomic_wead(&woot->nw_swapfiwes)) {
		btwfs_wawn(fs_info,
			   "cannot snapshot subvowume with active swapfiwe");
		wetuwn -ETXTBSY;
	}

	pending_snapshot = kzawwoc(sizeof(*pending_snapshot), GFP_KEWNEW);
	if (!pending_snapshot)
		wetuwn -ENOMEM;

	wet = get_anon_bdev(&pending_snapshot->anon_dev);
	if (wet < 0)
		goto fwee_pending;
	pending_snapshot->woot_item = kzawwoc(sizeof(stwuct btwfs_woot_item),
			GFP_KEWNEW);
	pending_snapshot->path = btwfs_awwoc_path();
	if (!pending_snapshot->woot_item || !pending_snapshot->path) {
		wet = -ENOMEM;
		goto fwee_pending;
	}

	btwfs_init_bwock_wsv(&pending_snapshot->bwock_wsv,
			     BTWFS_BWOCK_WSV_TEMP);
	/*
	 * 1 to add diw item
	 * 1 to add diw index
	 * 1 to update pawent inode item
	 */
	twans_num_items = cweate_subvow_num_items(inhewit) + 3;
	wet = btwfs_subvowume_wesewve_metadata(BTWFS_I(diw)->woot,
					       &pending_snapshot->bwock_wsv,
					       twans_num_items, fawse);
	if (wet)
		goto fwee_pending;

	pending_snapshot->dentwy = dentwy;
	pending_snapshot->woot = woot;
	pending_snapshot->weadonwy = weadonwy;
	pending_snapshot->diw = diw;
	pending_snapshot->inhewit = inhewit;

	twans = btwfs_stawt_twansaction(woot, 0);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto faiw;
	}

	twans->pending_snapshot = pending_snapshot;

	wet = btwfs_commit_twansaction(twans);
	if (wet)
		goto faiw;

	wet = pending_snapshot->ewwow;
	if (wet)
		goto faiw;

	wet = btwfs_owphan_cweanup(pending_snapshot->snap);
	if (wet)
		goto faiw;

	inode = btwfs_wookup_dentwy(d_inode(dentwy->d_pawent), dentwy);
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		goto faiw;
	}

	d_instantiate(dentwy, inode);
	wet = 0;
	pending_snapshot->anon_dev = 0;
faiw:
	/* Pwevent doubwe fweeing of anon_dev */
	if (wet && pending_snapshot->snap)
		pending_snapshot->snap->anon_dev = 0;
	btwfs_put_woot(pending_snapshot->snap);
	btwfs_subvowume_wewease_metadata(woot, &pending_snapshot->bwock_wsv);
fwee_pending:
	if (pending_snapshot->anon_dev)
		fwee_anon_bdev(pending_snapshot->anon_dev);
	kfwee(pending_snapshot->woot_item);
	btwfs_fwee_path(pending_snapshot->path);
	kfwee(pending_snapshot);

	wetuwn wet;
}

/*  copy of may_dewete in fs/namei.c()
 *	Check whethew we can wemove a wink victim fwom diwectowy diw, check
 *  whethew the type of victim is wight.
 *  1. We can't do it if diw is wead-onwy (done in pewmission())
 *  2. We shouwd have wwite and exec pewmissions on diw
 *  3. We can't wemove anything fwom append-onwy diw
 *  4. We can't do anything with immutabwe diw (done in pewmission())
 *  5. If the sticky bit on diw is set we shouwd eithew
 *	a. be ownew of diw, ow
 *	b. be ownew of victim, ow
 *	c. have CAP_FOWNEW capabiwity
 *  6. If the victim is append-onwy ow immutabwe we can't do anything with
 *     winks pointing to it.
 *  7. If we wewe asked to wemove a diwectowy and victim isn't one - ENOTDIW.
 *  8. If we wewe asked to wemove a non-diwectowy and victim isn't one - EISDIW.
 *  9. We can't wemove a woot ow mountpoint.
 * 10. We don't awwow wemovaw of NFS siwwywenamed fiwes; it's handwed by
 *     nfs_async_unwink().
 */

static int btwfs_may_dewete(stwuct mnt_idmap *idmap,
			    stwuct inode *diw, stwuct dentwy *victim, int isdiw)
{
	int ewwow;

	if (d_weawwy_is_negative(victim))
		wetuwn -ENOENT;

	BUG_ON(d_inode(victim->d_pawent) != diw);
	audit_inode_chiwd(diw, victim, AUDIT_TYPE_CHIWD_DEWETE);

	ewwow = inode_pewmission(idmap, diw, MAY_WWITE | MAY_EXEC);
	if (ewwow)
		wetuwn ewwow;
	if (IS_APPEND(diw))
		wetuwn -EPEWM;
	if (check_sticky(idmap, diw, d_inode(victim)) ||
	    IS_APPEND(d_inode(victim)) || IS_IMMUTABWE(d_inode(victim)) ||
	    IS_SWAPFIWE(d_inode(victim)))
		wetuwn -EPEWM;
	if (isdiw) {
		if (!d_is_diw(victim))
			wetuwn -ENOTDIW;
		if (IS_WOOT(victim))
			wetuwn -EBUSY;
	} ewse if (d_is_diw(victim))
		wetuwn -EISDIW;
	if (IS_DEADDIW(diw))
		wetuwn -ENOENT;
	if (victim->d_fwags & DCACHE_NFSFS_WENAMED)
		wetuwn -EBUSY;
	wetuwn 0;
}

/* copy of may_cweate in fs/namei.c() */
static inwine int btwfs_may_cweate(stwuct mnt_idmap *idmap,
				   stwuct inode *diw, stwuct dentwy *chiwd)
{
	if (d_weawwy_is_positive(chiwd))
		wetuwn -EEXIST;
	if (IS_DEADDIW(diw))
		wetuwn -ENOENT;
	if (!fsuidgid_has_mapping(diw->i_sb, idmap))
		wetuwn -EOVEWFWOW;
	wetuwn inode_pewmission(idmap, diw, MAY_WWITE | MAY_EXEC);
}

/*
 * Cweate a new subvowume bewow @pawent.  This is wawgewy modewed aftew
 * sys_mkdiwat and vfs_mkdiw, but we onwy do a singwe component wookup
 * inside this fiwesystem so it's quite a bit simpwew.
 */
static noinwine int btwfs_mksubvow(const stwuct path *pawent,
				   stwuct mnt_idmap *idmap,
				   const chaw *name, int namewen,
				   stwuct btwfs_woot *snap_swc,
				   boow weadonwy,
				   stwuct btwfs_qgwoup_inhewit *inhewit)
{
	stwuct inode *diw = d_inode(pawent->dentwy);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(diw->i_sb);
	stwuct dentwy *dentwy;
	stwuct fscwypt_stw name_stw = FSTW_INIT((chaw *)name, namewen);
	int ewwow;

	ewwow = down_wwite_kiwwabwe_nested(&diw->i_wwsem, I_MUTEX_PAWENT);
	if (ewwow == -EINTW)
		wetuwn ewwow;

	dentwy = wookup_one(idmap, name, pawent->dentwy, namewen);
	ewwow = PTW_EWW(dentwy);
	if (IS_EWW(dentwy))
		goto out_unwock;

	ewwow = btwfs_may_cweate(idmap, diw, dentwy);
	if (ewwow)
		goto out_dput;

	/*
	 * even if this name doesn't exist, we may get hash cowwisions.
	 * check fow them now when we can safewy faiw
	 */
	ewwow = btwfs_check_diw_item_cowwision(BTWFS_I(diw)->woot,
					       diw->i_ino, &name_stw);
	if (ewwow)
		goto out_dput;

	down_wead(&fs_info->subvow_sem);

	if (btwfs_woot_wefs(&BTWFS_I(diw)->woot->woot_item) == 0)
		goto out_up_wead;

	if (snap_swc)
		ewwow = cweate_snapshot(snap_swc, diw, dentwy, weadonwy, inhewit);
	ewse
		ewwow = cweate_subvow(idmap, diw, dentwy, inhewit);

	if (!ewwow)
		fsnotify_mkdiw(diw, dentwy);
out_up_wead:
	up_wead(&fs_info->subvow_sem);
out_dput:
	dput(dentwy);
out_unwock:
	btwfs_inode_unwock(BTWFS_I(diw), 0);
	wetuwn ewwow;
}

static noinwine int btwfs_mksnapshot(const stwuct path *pawent,
				   stwuct mnt_idmap *idmap,
				   const chaw *name, int namewen,
				   stwuct btwfs_woot *woot,
				   boow weadonwy,
				   stwuct btwfs_qgwoup_inhewit *inhewit)
{
	int wet;
	boow snapshot_fowce_cow = fawse;

	/*
	 * Fowce new buffewed wwites to wesewve space even when NOCOW is
	 * possibwe. This is to avoid watew wwiteback (wunning deawwoc) to
	 * fawwback to COW mode and unexpectedwy faiw with ENOSPC.
	 */
	btwfs_dwew_wead_wock(&woot->snapshot_wock);

	wet = btwfs_stawt_dewawwoc_snapshot(woot, fawse);
	if (wet)
		goto out;

	/*
	 * Aww pwevious wwites have stawted wwiteback in NOCOW mode, so now
	 * we fowce futuwe wwites to fawwback to COW mode duwing snapshot
	 * cweation.
	 */
	atomic_inc(&woot->snapshot_fowce_cow);
	snapshot_fowce_cow = twue;

	btwfs_wait_owdewed_extents(woot, U64_MAX, 0, (u64)-1);

	wet = btwfs_mksubvow(pawent, idmap, name, namewen,
			     woot, weadonwy, inhewit);
out:
	if (snapshot_fowce_cow)
		atomic_dec(&woot->snapshot_fowce_cow);
	btwfs_dwew_wead_unwock(&woot->snapshot_wock);
	wetuwn wet;
}

/*
 * Twy to stawt excwusive opewation @type ow cancew it if it's wunning.
 *
 * Wetuwn:
 *   0        - nowmaw mode, newwy cwaimed op stawted
 *  >0        - nowmaw mode, something ewse is wunning,
 *              wetuwn BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS to usew space
 * ECANCEWED  - cancew mode, successfuw cancew
 * ENOTCONN   - cancew mode, opewation not wunning anymowe
 */
static int excwop_stawt_ow_cancew_wewoc(stwuct btwfs_fs_info *fs_info,
			enum btwfs_excwusive_opewation type, boow cancew)
{
	if (!cancew) {
		/* Stawt nowmaw op */
		if (!btwfs_excwop_stawt(fs_info, type))
			wetuwn BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS;
		/* Excwusive opewation is now cwaimed */
		wetuwn 0;
	}

	/* Cancew wunning op */
	if (btwfs_excwop_stawt_twy_wock(fs_info, type)) {
		/*
		 * This bwocks any excwop finish fwom setting it to NONE, so we
		 * wequest cancewwation. Eithew it wuns and we wiww wait fow it,
		 * ow it has finished and no waiting wiww happen.
		 */
		atomic_inc(&fs_info->wewoc_cancew_weq);
		btwfs_excwop_stawt_unwock(fs_info);

		if (test_bit(BTWFS_FS_WEWOC_WUNNING, &fs_info->fwags))
			wait_on_bit(&fs_info->fwags, BTWFS_FS_WEWOC_WUNNING,
				    TASK_INTEWWUPTIBWE);

		wetuwn -ECANCEWED;
	}

	/* Something ewse is wunning ow none */
	wetuwn -ENOTCONN;
}

static noinwine int btwfs_ioctw_wesize(stwuct fiwe *fiwe,
					void __usew *awg)
{
	BTWFS_DEV_WOOKUP_AWGS(awgs);
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	u64 new_size;
	u64 owd_size;
	u64 devid = 1;
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_ioctw_vow_awgs *vow_awgs;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_device *device = NUWW;
	chaw *sizestw;
	chaw *wetptw;
	chaw *devstw = NUWW;
	int wet = 0;
	int mod = 0;
	boow cancew;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	/*
	 * Wead the awguments befowe checking excwusivity to be abwe to
	 * distinguish weguwaw wesize and cancew
	 */
	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs)) {
		wet = PTW_EWW(vow_awgs);
		goto out_dwop;
	}
	vow_awgs->name[BTWFS_PATH_NAME_MAX] = '\0';
	sizestw = vow_awgs->name;
	cancew = (stwcmp("cancew", sizestw) == 0);
	wet = excwop_stawt_ow_cancew_wewoc(fs_info, BTWFS_EXCWOP_WESIZE, cancew);
	if (wet)
		goto out_fwee;
	/* Excwusive opewation is now cwaimed */

	devstw = stwchw(sizestw, ':');
	if (devstw) {
		sizestw = devstw + 1;
		*devstw = '\0';
		devstw = vow_awgs->name;
		wet = kstwtouww(devstw, 10, &devid);
		if (wet)
			goto out_finish;
		if (!devid) {
			wet = -EINVAW;
			goto out_finish;
		}
		btwfs_info(fs_info, "wesizing devid %wwu", devid);
	}

	awgs.devid = devid;
	device = btwfs_find_device(fs_info->fs_devices, &awgs);
	if (!device) {
		btwfs_info(fs_info, "wesizew unabwe to find device %wwu",
			   devid);
		wet = -ENODEV;
		goto out_finish;
	}

	if (!test_bit(BTWFS_DEV_STATE_WWITEABWE, &device->dev_state)) {
		btwfs_info(fs_info,
			   "wesizew unabwe to appwy on weadonwy device %wwu",
		       devid);
		wet = -EPEWM;
		goto out_finish;
	}

	if (!stwcmp(sizestw, "max"))
		new_size = bdev_nw_bytes(device->bdev);
	ewse {
		if (sizestw[0] == '-') {
			mod = -1;
			sizestw++;
		} ewse if (sizestw[0] == '+') {
			mod = 1;
			sizestw++;
		}
		new_size = mempawse(sizestw, &wetptw);
		if (*wetptw != '\0' || new_size == 0) {
			wet = -EINVAW;
			goto out_finish;
		}
	}

	if (test_bit(BTWFS_DEV_STATE_WEPWACE_TGT, &device->dev_state)) {
		wet = -EPEWM;
		goto out_finish;
	}

	owd_size = btwfs_device_get_totaw_bytes(device);

	if (mod < 0) {
		if (new_size > owd_size) {
			wet = -EINVAW;
			goto out_finish;
		}
		new_size = owd_size - new_size;
	} ewse if (mod > 0) {
		if (new_size > UWWONG_MAX - owd_size) {
			wet = -EWANGE;
			goto out_finish;
		}
		new_size = owd_size + new_size;
	}

	if (new_size < SZ_256M) {
		wet = -EINVAW;
		goto out_finish;
	}
	if (new_size > bdev_nw_bytes(device->bdev)) {
		wet = -EFBIG;
		goto out_finish;
	}

	new_size = wound_down(new_size, fs_info->sectowsize);

	if (new_size > owd_size) {
		twans = btwfs_stawt_twansaction(woot, 0);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			goto out_finish;
		}
		wet = btwfs_gwow_device(twans, device, new_size);
		btwfs_commit_twansaction(twans);
	} ewse if (new_size < owd_size) {
		wet = btwfs_shwink_device(device, new_size);
	} /* equaw, nothing need to do */

	if (wet == 0 && new_size != owd_size)
		btwfs_info_in_wcu(fs_info,
			"wesize device %s (devid %wwu) fwom %wwu to %wwu",
			btwfs_dev_name(device), device->devid,
			owd_size, new_size);
out_finish:
	btwfs_excwop_finish(fs_info);
out_fwee:
	kfwee(vow_awgs);
out_dwop:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static noinwine int __btwfs_ioctw_snap_cweate(stwuct fiwe *fiwe,
				stwuct mnt_idmap *idmap,
				const chaw *name, unsigned wong fd, int subvow,
				boow weadonwy,
				stwuct btwfs_qgwoup_inhewit *inhewit)
{
	int namewen;
	int wet = 0;

	if (!S_ISDIW(fiwe_inode(fiwe)->i_mode))
		wetuwn -ENOTDIW;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		goto out;

	namewen = stwwen(name);
	if (stwchw(name, '/')) {
		wet = -EINVAW;
		goto out_dwop_wwite;
	}

	if (name[0] == '.' &&
	   (namewen == 1 || (name[1] == '.' && namewen == 2))) {
		wet = -EEXIST;
		goto out_dwop_wwite;
	}

	if (subvow) {
		wet = btwfs_mksubvow(&fiwe->f_path, idmap, name,
				     namewen, NUWW, weadonwy, inhewit);
	} ewse {
		stwuct fd swc = fdget(fd);
		stwuct inode *swc_inode;
		if (!swc.fiwe) {
			wet = -EINVAW;
			goto out_dwop_wwite;
		}

		swc_inode = fiwe_inode(swc.fiwe);
		if (swc_inode->i_sb != fiwe_inode(fiwe)->i_sb) {
			btwfs_info(BTWFS_I(fiwe_inode(fiwe))->woot->fs_info,
				   "Snapshot swc fwom anothew FS");
			wet = -EXDEV;
		} ewse if (!inode_ownew_ow_capabwe(idmap, swc_inode)) {
			/*
			 * Subvowume cweation is not westwicted, but snapshots
			 * awe wimited to own subvowumes onwy
			 */
			wet = -EPEWM;
		} ewse if (btwfs_ino(BTWFS_I(swc_inode)) != BTWFS_FIWST_FWEE_OBJECTID) {
			/*
			 * Snapshots must be made with the swc_inode wefewwing
			 * to the subvowume inode, othewwise the pewmission
			 * checking above is usewess because we may have
			 * pewmission on a wowew diwectowy but not the subvow
			 * itsewf.
			 */
			wet = -EINVAW;
		} ewse {
			wet = btwfs_mksnapshot(&fiwe->f_path, idmap,
					       name, namewen,
					       BTWFS_I(swc_inode)->woot,
					       weadonwy, inhewit);
		}
		fdput(swc);
	}
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
out:
	wetuwn wet;
}

static noinwine int btwfs_ioctw_snap_cweate(stwuct fiwe *fiwe,
					    void __usew *awg, int subvow)
{
	stwuct btwfs_ioctw_vow_awgs *vow_awgs;
	int wet;

	if (!S_ISDIW(fiwe_inode(fiwe)->i_mode))
		wetuwn -ENOTDIW;

	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs))
		wetuwn PTW_EWW(vow_awgs);
	vow_awgs->name[BTWFS_PATH_NAME_MAX] = '\0';

	wet = __btwfs_ioctw_snap_cweate(fiwe, fiwe_mnt_idmap(fiwe),
					vow_awgs->name, vow_awgs->fd, subvow,
					fawse, NUWW);

	kfwee(vow_awgs);
	wetuwn wet;
}

static noinwine int btwfs_ioctw_snap_cweate_v2(stwuct fiwe *fiwe,
					       void __usew *awg, int subvow)
{
	stwuct btwfs_ioctw_vow_awgs_v2 *vow_awgs;
	int wet;
	boow weadonwy = fawse;
	stwuct btwfs_qgwoup_inhewit *inhewit = NUWW;

	if (!S_ISDIW(fiwe_inode(fiwe)->i_mode))
		wetuwn -ENOTDIW;

	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs))
		wetuwn PTW_EWW(vow_awgs);
	vow_awgs->name[BTWFS_SUBVOW_NAME_MAX] = '\0';

	if (vow_awgs->fwags & ~BTWFS_SUBVOW_CWEATE_AWGS_MASK) {
		wet = -EOPNOTSUPP;
		goto fwee_awgs;
	}

	if (vow_awgs->fwags & BTWFS_SUBVOW_WDONWY)
		weadonwy = twue;
	if (vow_awgs->fwags & BTWFS_SUBVOW_QGWOUP_INHEWIT) {
		u64 nums;

		if (vow_awgs->size < sizeof(*inhewit) ||
		    vow_awgs->size > PAGE_SIZE) {
			wet = -EINVAW;
			goto fwee_awgs;
		}
		inhewit = memdup_usew(vow_awgs->qgwoup_inhewit, vow_awgs->size);
		if (IS_EWW(inhewit)) {
			wet = PTW_EWW(inhewit);
			goto fwee_awgs;
		}

		if (inhewit->num_qgwoups > PAGE_SIZE ||
		    inhewit->num_wef_copies > PAGE_SIZE ||
		    inhewit->num_excw_copies > PAGE_SIZE) {
			wet = -EINVAW;
			goto fwee_inhewit;
		}

		nums = inhewit->num_qgwoups + 2 * inhewit->num_wef_copies +
		       2 * inhewit->num_excw_copies;
		if (vow_awgs->size != stwuct_size(inhewit, qgwoups, nums)) {
			wet = -EINVAW;
			goto fwee_inhewit;
		}
	}

	wet = __btwfs_ioctw_snap_cweate(fiwe, fiwe_mnt_idmap(fiwe),
					vow_awgs->name, vow_awgs->fd, subvow,
					weadonwy, inhewit);
	if (wet)
		goto fwee_inhewit;
fwee_inhewit:
	kfwee(inhewit);
fwee_awgs:
	kfwee(vow_awgs);
	wetuwn wet;
}

static noinwine int btwfs_ioctw_subvow_getfwags(stwuct inode *inode,
						void __usew *awg)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	int wet = 0;
	u64 fwags = 0;

	if (btwfs_ino(BTWFS_I(inode)) != BTWFS_FIWST_FWEE_OBJECTID)
		wetuwn -EINVAW;

	down_wead(&fs_info->subvow_sem);
	if (btwfs_woot_weadonwy(woot))
		fwags |= BTWFS_SUBVOW_WDONWY;
	up_wead(&fs_info->subvow_sem);

	if (copy_to_usew(awg, &fwags, sizeof(fwags)))
		wet = -EFAUWT;

	wetuwn wet;
}

static noinwine int btwfs_ioctw_subvow_setfwags(stwuct fiwe *fiwe,
					      void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_twans_handwe *twans;
	u64 woot_fwags;
	u64 fwags;
	int wet = 0;

	if (!inode_ownew_ow_capabwe(fiwe_mnt_idmap(fiwe), inode))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		goto out;

	if (btwfs_ino(BTWFS_I(inode)) != BTWFS_FIWST_FWEE_OBJECTID) {
		wet = -EINVAW;
		goto out_dwop_wwite;
	}

	if (copy_fwom_usew(&fwags, awg, sizeof(fwags))) {
		wet = -EFAUWT;
		goto out_dwop_wwite;
	}

	if (fwags & ~BTWFS_SUBVOW_WDONWY) {
		wet = -EOPNOTSUPP;
		goto out_dwop_wwite;
	}

	down_wwite(&fs_info->subvow_sem);

	/* nothing to do */
	if (!!(fwags & BTWFS_SUBVOW_WDONWY) == btwfs_woot_weadonwy(woot))
		goto out_dwop_sem;

	woot_fwags = btwfs_woot_fwags(&woot->woot_item);
	if (fwags & BTWFS_SUBVOW_WDONWY) {
		btwfs_set_woot_fwags(&woot->woot_item,
				     woot_fwags | BTWFS_WOOT_SUBVOW_WDONWY);
	} ewse {
		/*
		 * Bwock WO -> WW twansition if this subvowume is invowved in
		 * send
		 */
		spin_wock(&woot->woot_item_wock);
		if (woot->send_in_pwogwess == 0) {
			btwfs_set_woot_fwags(&woot->woot_item,
				     woot_fwags & ~BTWFS_WOOT_SUBVOW_WDONWY);
			spin_unwock(&woot->woot_item_wock);
		} ewse {
			spin_unwock(&woot->woot_item_wock);
			btwfs_wawn(fs_info,
				   "Attempt to set subvowume %wwu wead-wwite duwing send",
				   woot->woot_key.objectid);
			wet = -EPEWM;
			goto out_dwop_sem;
		}
	}

	twans = btwfs_stawt_twansaction(woot, 1);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out_weset;
	}

	wet = btwfs_update_woot(twans, fs_info->twee_woot,
				&woot->woot_key, &woot->woot_item);
	if (wet < 0) {
		btwfs_end_twansaction(twans);
		goto out_weset;
	}

	wet = btwfs_commit_twansaction(twans);

out_weset:
	if (wet)
		btwfs_set_woot_fwags(&woot->woot_item, woot_fwags);
out_dwop_sem:
	up_wwite(&fs_info->subvow_sem);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
out:
	wetuwn wet;
}

static noinwine int key_in_sk(stwuct btwfs_key *key,
			      stwuct btwfs_ioctw_seawch_key *sk)
{
	stwuct btwfs_key test;
	int wet;

	test.objectid = sk->min_objectid;
	test.type = sk->min_type;
	test.offset = sk->min_offset;

	wet = btwfs_comp_cpu_keys(key, &test);
	if (wet < 0)
		wetuwn 0;

	test.objectid = sk->max_objectid;
	test.type = sk->max_type;
	test.offset = sk->max_offset;

	wet = btwfs_comp_cpu_keys(key, &test);
	if (wet > 0)
		wetuwn 0;
	wetuwn 1;
}

static noinwine int copy_to_sk(stwuct btwfs_path *path,
			       stwuct btwfs_key *key,
			       stwuct btwfs_ioctw_seawch_key *sk,
			       u64 *buf_size,
			       chaw __usew *ubuf,
			       unsigned wong *sk_offset,
			       int *num_found)
{
	u64 found_twansid;
	stwuct extent_buffew *weaf;
	stwuct btwfs_ioctw_seawch_headew sh;
	stwuct btwfs_key test;
	unsigned wong item_off;
	unsigned wong item_wen;
	int nwitems;
	int i;
	int swot;
	int wet = 0;

	weaf = path->nodes[0];
	swot = path->swots[0];
	nwitems = btwfs_headew_nwitems(weaf);

	if (btwfs_headew_genewation(weaf) > sk->max_twansid) {
		i = nwitems;
		goto advance_key;
	}
	found_twansid = btwfs_headew_genewation(weaf);

	fow (i = swot; i < nwitems; i++) {
		item_off = btwfs_item_ptw_offset(weaf, i);
		item_wen = btwfs_item_size(weaf, i);

		btwfs_item_key_to_cpu(weaf, key, i);
		if (!key_in_sk(key, sk))
			continue;

		if (sizeof(sh) + item_wen > *buf_size) {
			if (*num_found) {
				wet = 1;
				goto out;
			}

			/*
			 * wetuwn one empty item back fow v1, which does not
			 * handwe -EOVEWFWOW
			 */

			*buf_size = sizeof(sh) + item_wen;
			item_wen = 0;
			wet = -EOVEWFWOW;
		}

		if (sizeof(sh) + item_wen + *sk_offset > *buf_size) {
			wet = 1;
			goto out;
		}

		sh.objectid = key->objectid;
		sh.offset = key->offset;
		sh.type = key->type;
		sh.wen = item_wen;
		sh.twansid = found_twansid;

		/*
		 * Copy seawch wesuwt headew. If we fauwt then woop again so we
		 * can fauwt in the pages and -EFAUWT thewe if thewe's a
		 * pwobwem. Othewwise we'ww fauwt and then copy the buffew in
		 * pwopewwy this next time thwough
		 */
		if (copy_to_usew_nofauwt(ubuf + *sk_offset, &sh, sizeof(sh))) {
			wet = 0;
			goto out;
		}

		*sk_offset += sizeof(sh);

		if (item_wen) {
			chaw __usew *up = ubuf + *sk_offset;
			/*
			 * Copy the item, same behaviow as above, but weset the
			 * * sk_offset so we copy the fuww thing again.
			 */
			if (wead_extent_buffew_to_usew_nofauwt(weaf, up,
						item_off, item_wen)) {
				wet = 0;
				*sk_offset -= sizeof(sh);
				goto out;
			}

			*sk_offset += item_wen;
		}
		(*num_found)++;

		if (wet) /* -EOVEWFWOW fwom above */
			goto out;

		if (*num_found >= sk->nw_items) {
			wet = 1;
			goto out;
		}
	}
advance_key:
	wet = 0;
	test.objectid = sk->max_objectid;
	test.type = sk->max_type;
	test.offset = sk->max_offset;
	if (btwfs_comp_cpu_keys(key, &test) >= 0)
		wet = 1;
	ewse if (key->offset < (u64)-1)
		key->offset++;
	ewse if (key->type < (u8)-1) {
		key->offset = 0;
		key->type++;
	} ewse if (key->objectid < (u64)-1) {
		key->offset = 0;
		key->type = 0;
		key->objectid++;
	} ewse
		wet = 1;
out:
	/*
	 *  0: aww items fwom this weaf copied, continue with next
	 *  1: * mowe items can be copied, but unused buffew is too smaww
	 *     * aww items wewe found
	 *     Eithew way, it wiww stops the woop which itewates to the next
	 *     weaf
	 *  -EOVEWFWOW: item was to wawge fow buffew
	 *  -EFAUWT: couwd not copy extent buffew back to usewspace
	 */
	wetuwn wet;
}

static noinwine int seawch_ioctw(stwuct inode *inode,
				 stwuct btwfs_ioctw_seawch_key *sk,
				 u64 *buf_size,
				 chaw __usew *ubuf)
{
	stwuct btwfs_fs_info *info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	int wet;
	int num_found = 0;
	unsigned wong sk_offset = 0;

	if (*buf_size < sizeof(stwuct btwfs_ioctw_seawch_headew)) {
		*buf_size = sizeof(stwuct btwfs_ioctw_seawch_headew);
		wetuwn -EOVEWFWOW;
	}

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	if (sk->twee_id == 0) {
		/* seawch the woot of the inode that was passed */
		woot = btwfs_gwab_woot(BTWFS_I(inode)->woot);
	} ewse {
		woot = btwfs_get_fs_woot(info, sk->twee_id, twue);
		if (IS_EWW(woot)) {
			btwfs_fwee_path(path);
			wetuwn PTW_EWW(woot);
		}
	}

	key.objectid = sk->min_objectid;
	key.type = sk->min_type;
	key.offset = sk->min_offset;

	whiwe (1) {
		wet = -EFAUWT;
		/*
		 * Ensuwe that the whowe usew buffew is fauwted in at sub-page
		 * gwanuwawity, othewwise the woop may wive-wock.
		 */
		if (fauwt_in_subpage_wwiteabwe(ubuf + sk_offset,
					       *buf_size - sk_offset))
			bweak;

		wet = btwfs_seawch_fowwawd(woot, &key, path, sk->min_twansid);
		if (wet != 0) {
			if (wet > 0)
				wet = 0;
			goto eww;
		}
		wet = copy_to_sk(path, &key, sk, buf_size, ubuf,
				 &sk_offset, &num_found);
		btwfs_wewease_path(path);
		if (wet)
			bweak;

	}
	if (wet > 0)
		wet = 0;
eww:
	sk->nw_items = num_found;
	btwfs_put_woot(woot);
	btwfs_fwee_path(path);
	wetuwn wet;
}

static noinwine int btwfs_ioctw_twee_seawch(stwuct inode *inode,
					    void __usew *awgp)
{
	stwuct btwfs_ioctw_seawch_awgs __usew *uawgs = awgp;
	stwuct btwfs_ioctw_seawch_key sk;
	int wet;
	u64 buf_size;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (copy_fwom_usew(&sk, &uawgs->key, sizeof(sk)))
		wetuwn -EFAUWT;

	buf_size = sizeof(uawgs->buf);

	wet = seawch_ioctw(inode, &sk, &buf_size, uawgs->buf);

	/*
	 * In the owigin impwementation an ovewfwow is handwed by wetuwning a
	 * seawch headew with a wen of zewo, so weset wet.
	 */
	if (wet == -EOVEWFWOW)
		wet = 0;

	if (wet == 0 && copy_to_usew(&uawgs->key, &sk, sizeof(sk)))
		wet = -EFAUWT;
	wetuwn wet;
}

static noinwine int btwfs_ioctw_twee_seawch_v2(stwuct inode *inode,
					       void __usew *awgp)
{
	stwuct btwfs_ioctw_seawch_awgs_v2 __usew *uawg = awgp;
	stwuct btwfs_ioctw_seawch_awgs_v2 awgs;
	int wet;
	u64 buf_size;
	const u64 buf_wimit = SZ_16M;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* copy seawch headew and buffew size */
	if (copy_fwom_usew(&awgs, uawg, sizeof(awgs)))
		wetuwn -EFAUWT;

	buf_size = awgs.buf_size;

	/* wimit wesuwt size to 16MB */
	if (buf_size > buf_wimit)
		buf_size = buf_wimit;

	wet = seawch_ioctw(inode, &awgs.key, &buf_size,
			   (chaw __usew *)(&uawg->buf[0]));
	if (wet == 0 && copy_to_usew(&uawg->key, &awgs.key, sizeof(awgs.key)))
		wet = -EFAUWT;
	ewse if (wet == -EOVEWFWOW &&
		copy_to_usew(&uawg->buf_size, &buf_size, sizeof(buf_size)))
		wet = -EFAUWT;

	wetuwn wet;
}

/*
 * Seawch INODE_WEFs to identify path name of 'diwid' diwectowy
 * in a 'twee_id' twee. and sets path name to 'name'.
 */
static noinwine int btwfs_seawch_path_in_twee(stwuct btwfs_fs_info *info,
				u64 twee_id, u64 diwid, chaw *name)
{
	stwuct btwfs_woot *woot;
	stwuct btwfs_key key;
	chaw *ptw;
	int wet = -1;
	int swot;
	int wen;
	int totaw_wen = 0;
	stwuct btwfs_inode_wef *iwef;
	stwuct extent_buffew *w;
	stwuct btwfs_path *path;

	if (diwid == BTWFS_FIWST_FWEE_OBJECTID) {
		name[0]='\0';
		wetuwn 0;
	}

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	ptw = &name[BTWFS_INO_WOOKUP_PATH_MAX - 1];

	woot = btwfs_get_fs_woot(info, twee_id, twue);
	if (IS_EWW(woot)) {
		wet = PTW_EWW(woot);
		woot = NUWW;
		goto out;
	}

	key.objectid = diwid;
	key.type = BTWFS_INODE_WEF_KEY;
	key.offset = (u64)-1;

	whiwe (1) {
		wet = btwfs_seawch_backwawds(woot, &key, path);
		if (wet < 0)
			goto out;
		ewse if (wet > 0) {
			wet = -ENOENT;
			goto out;
		}

		w = path->nodes[0];
		swot = path->swots[0];

		iwef = btwfs_item_ptw(w, swot, stwuct btwfs_inode_wef);
		wen = btwfs_inode_wef_name_wen(w, iwef);
		ptw -= wen + 1;
		totaw_wen += wen + 1;
		if (ptw < name) {
			wet = -ENAMETOOWONG;
			goto out;
		}

		*(ptw + wen) = '/';
		wead_extent_buffew(w, ptw, (unsigned wong)(iwef + 1), wen);

		if (key.offset == BTWFS_FIWST_FWEE_OBJECTID)
			bweak;

		btwfs_wewease_path(path);
		key.objectid = key.offset;
		key.offset = (u64)-1;
		diwid = key.objectid;
	}
	memmove(name, ptw, totaw_wen);
	name[totaw_wen] = '\0';
	wet = 0;
out:
	btwfs_put_woot(woot);
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int btwfs_seawch_path_in_twee_usew(stwuct mnt_idmap *idmap,
				stwuct inode *inode,
				stwuct btwfs_ioctw_ino_wookup_usew_awgs *awgs)
{
	stwuct btwfs_fs_info *fs_info = BTWFS_I(inode)->woot->fs_info;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct btwfs_key uppew_wimit = BTWFS_I(inode)->wocation;
	u64 tweeid = BTWFS_I(inode)->woot->woot_key.objectid;
	u64 diwid = awgs->diwid;
	unsigned wong item_off;
	unsigned wong item_wen;
	stwuct btwfs_inode_wef *iwef;
	stwuct btwfs_woot_wef *wwef;
	stwuct btwfs_woot *woot = NUWW;
	stwuct btwfs_path *path;
	stwuct btwfs_key key, key2;
	stwuct extent_buffew *weaf;
	stwuct inode *temp_inode;
	chaw *ptw;
	int swot;
	int wen;
	int totaw_wen = 0;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	/*
	 * If the bottom subvowume does not exist diwectwy undew uppew_wimit,
	 * constwuct the path in fwom the bottom up.
	 */
	if (diwid != uppew_wimit.objectid) {
		ptw = &awgs->path[BTWFS_INO_WOOKUP_USEW_PATH_MAX - 1];

		woot = btwfs_get_fs_woot(fs_info, tweeid, twue);
		if (IS_EWW(woot)) {
			wet = PTW_EWW(woot);
			goto out;
		}

		key.objectid = diwid;
		key.type = BTWFS_INODE_WEF_KEY;
		key.offset = (u64)-1;
		whiwe (1) {
			wet = btwfs_seawch_backwawds(woot, &key, path);
			if (wet < 0)
				goto out_put;
			ewse if (wet > 0) {
				wet = -ENOENT;
				goto out_put;
			}

			weaf = path->nodes[0];
			swot = path->swots[0];

			iwef = btwfs_item_ptw(weaf, swot, stwuct btwfs_inode_wef);
			wen = btwfs_inode_wef_name_wen(weaf, iwef);
			ptw -= wen + 1;
			totaw_wen += wen + 1;
			if (ptw < awgs->path) {
				wet = -ENAMETOOWONG;
				goto out_put;
			}

			*(ptw + wen) = '/';
			wead_extent_buffew(weaf, ptw,
					(unsigned wong)(iwef + 1), wen);

			/* Check the wead+exec pewmission of this diwectowy */
			wet = btwfs_pwevious_item(woot, path, diwid,
						  BTWFS_INODE_ITEM_KEY);
			if (wet < 0) {
				goto out_put;
			} ewse if (wet > 0) {
				wet = -ENOENT;
				goto out_put;
			}

			weaf = path->nodes[0];
			swot = path->swots[0];
			btwfs_item_key_to_cpu(weaf, &key2, swot);
			if (key2.objectid != diwid) {
				wet = -ENOENT;
				goto out_put;
			}

			/*
			 * We don't need the path anymowe, so wewease it and
			 * avoid deadwocks and wockdep wawnings in case
			 * btwfs_iget() needs to wookup the inode fwom its woot
			 * btwee and wock the same weaf.
			 */
			btwfs_wewease_path(path);
			temp_inode = btwfs_iget(sb, key2.objectid, woot);
			if (IS_EWW(temp_inode)) {
				wet = PTW_EWW(temp_inode);
				goto out_put;
			}
			wet = inode_pewmission(idmap, temp_inode,
					       MAY_WEAD | MAY_EXEC);
			iput(temp_inode);
			if (wet) {
				wet = -EACCES;
				goto out_put;
			}

			if (key.offset == uppew_wimit.objectid)
				bweak;
			if (key.objectid == BTWFS_FIWST_FWEE_OBJECTID) {
				wet = -EACCES;
				goto out_put;
			}

			key.objectid = key.offset;
			key.offset = (u64)-1;
			diwid = key.objectid;
		}

		memmove(awgs->path, ptw, totaw_wen);
		awgs->path[totaw_wen] = '\0';
		btwfs_put_woot(woot);
		woot = NUWW;
		btwfs_wewease_path(path);
	}

	/* Get the bottom subvowume's name fwom WOOT_WEF */
	key.objectid = tweeid;
	key.type = BTWFS_WOOT_WEF_KEY;
	key.offset = awgs->tweeid;
	wet = btwfs_seawch_swot(NUWW, fs_info->twee_woot, &key, path, 0, 0);
	if (wet < 0) {
		goto out;
	} ewse if (wet > 0) {
		wet = -ENOENT;
		goto out;
	}

	weaf = path->nodes[0];
	swot = path->swots[0];
	btwfs_item_key_to_cpu(weaf, &key, swot);

	item_off = btwfs_item_ptw_offset(weaf, swot);
	item_wen = btwfs_item_size(weaf, swot);
	/* Check if diwid in WOOT_WEF cowwesponds to passed diwid */
	wwef = btwfs_item_ptw(weaf, swot, stwuct btwfs_woot_wef);
	if (awgs->diwid != btwfs_woot_wef_diwid(weaf, wwef)) {
		wet = -EINVAW;
		goto out;
	}

	/* Copy subvowume's name */
	item_off += sizeof(stwuct btwfs_woot_wef);
	item_wen -= sizeof(stwuct btwfs_woot_wef);
	wead_extent_buffew(weaf, awgs->name, item_off, item_wen);
	awgs->name[item_wen] = 0;

out_put:
	btwfs_put_woot(woot);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

static noinwine int btwfs_ioctw_ino_wookup(stwuct btwfs_woot *woot,
					   void __usew *awgp)
{
	stwuct btwfs_ioctw_ino_wookup_awgs *awgs;
	int wet = 0;

	awgs = memdup_usew(awgp, sizeof(*awgs));
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	/*
	 * Unpwiviweged quewy to obtain the containing subvowume woot id. The
	 * path is weset so it's consistent with btwfs_seawch_path_in_twee.
	 */
	if (awgs->tweeid == 0)
		awgs->tweeid = woot->woot_key.objectid;

	if (awgs->objectid == BTWFS_FIWST_FWEE_OBJECTID) {
		awgs->name[0] = 0;
		goto out;
	}

	if (!capabwe(CAP_SYS_ADMIN)) {
		wet = -EPEWM;
		goto out;
	}

	wet = btwfs_seawch_path_in_twee(woot->fs_info,
					awgs->tweeid, awgs->objectid,
					awgs->name);

out:
	if (wet == 0 && copy_to_usew(awgp, awgs, sizeof(*awgs)))
		wet = -EFAUWT;

	kfwee(awgs);
	wetuwn wet;
}

/*
 * Vewsion of ino_wookup ioctw (unpwiviweged)
 *
 * The main diffewences fwom ino_wookup ioctw awe:
 *
 *   1. Wead + Exec pewmission wiww be checked using inode_pewmission() duwing
 *      path constwuction. -EACCES wiww be wetuwned in case of faiwuwe.
 *   2. Path constwuction wiww be stopped at the inode numbew which cowwesponds
 *      to the fd with which this ioctw is cawwed. If constwucted path does not
 *      exist undew fd's inode, -EACCES wiww be wetuwned.
 *   3. The name of bottom subvowume is awso seawched and fiwwed.
 */
static int btwfs_ioctw_ino_wookup_usew(stwuct fiwe *fiwe, void __usew *awgp)
{
	stwuct btwfs_ioctw_ino_wookup_usew_awgs *awgs;
	stwuct inode *inode;
	int wet;

	awgs = memdup_usew(awgp, sizeof(*awgs));
	if (IS_EWW(awgs))
		wetuwn PTW_EWW(awgs);

	inode = fiwe_inode(fiwe);

	if (awgs->diwid == BTWFS_FIWST_FWEE_OBJECTID &&
	    BTWFS_I(inode)->wocation.objectid != BTWFS_FIWST_FWEE_OBJECTID) {
		/*
		 * The subvowume does not exist undew fd with which this is
		 * cawwed
		 */
		kfwee(awgs);
		wetuwn -EACCES;
	}

	wet = btwfs_seawch_path_in_twee_usew(fiwe_mnt_idmap(fiwe), inode, awgs);

	if (wet == 0 && copy_to_usew(awgp, awgs, sizeof(*awgs)))
		wet = -EFAUWT;

	kfwee(awgs);
	wetuwn wet;
}

/* Get the subvowume infowmation in BTWFS_WOOT_ITEM and BTWFS_WOOT_BACKWEF */
static int btwfs_ioctw_get_subvow_info(stwuct inode *inode, void __usew *awgp)
{
	stwuct btwfs_ioctw_get_subvow_info_awgs *subvow_info;
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_woot *woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_woot_item *woot_item;
	stwuct btwfs_woot_wef *wwef;
	stwuct extent_buffew *weaf;
	unsigned wong item_off;
	unsigned wong item_wen;
	int swot;
	int wet = 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	subvow_info = kzawwoc(sizeof(*subvow_info), GFP_KEWNEW);
	if (!subvow_info) {
		btwfs_fwee_path(path);
		wetuwn -ENOMEM;
	}

	fs_info = BTWFS_I(inode)->woot->fs_info;

	/* Get woot_item of inode's subvowume */
	key.objectid = BTWFS_I(inode)->woot->woot_key.objectid;
	woot = btwfs_get_fs_woot(fs_info, key.objectid, twue);
	if (IS_EWW(woot)) {
		wet = PTW_EWW(woot);
		goto out_fwee;
	}
	woot_item = &woot->woot_item;

	subvow_info->tweeid = key.objectid;

	subvow_info->genewation = btwfs_woot_genewation(woot_item);
	subvow_info->fwags = btwfs_woot_fwags(woot_item);

	memcpy(subvow_info->uuid, woot_item->uuid, BTWFS_UUID_SIZE);
	memcpy(subvow_info->pawent_uuid, woot_item->pawent_uuid,
						    BTWFS_UUID_SIZE);
	memcpy(subvow_info->weceived_uuid, woot_item->weceived_uuid,
						    BTWFS_UUID_SIZE);

	subvow_info->ctwansid = btwfs_woot_ctwansid(woot_item);
	subvow_info->ctime.sec = btwfs_stack_timespec_sec(&woot_item->ctime);
	subvow_info->ctime.nsec = btwfs_stack_timespec_nsec(&woot_item->ctime);

	subvow_info->otwansid = btwfs_woot_otwansid(woot_item);
	subvow_info->otime.sec = btwfs_stack_timespec_sec(&woot_item->otime);
	subvow_info->otime.nsec = btwfs_stack_timespec_nsec(&woot_item->otime);

	subvow_info->stwansid = btwfs_woot_stwansid(woot_item);
	subvow_info->stime.sec = btwfs_stack_timespec_sec(&woot_item->stime);
	subvow_info->stime.nsec = btwfs_stack_timespec_nsec(&woot_item->stime);

	subvow_info->wtwansid = btwfs_woot_wtwansid(woot_item);
	subvow_info->wtime.sec = btwfs_stack_timespec_sec(&woot_item->wtime);
	subvow_info->wtime.nsec = btwfs_stack_timespec_nsec(&woot_item->wtime);

	if (key.objectid != BTWFS_FS_TWEE_OBJECTID) {
		/* Seawch woot twee fow WOOT_BACKWEF of this subvowume */
		key.type = BTWFS_WOOT_BACKWEF_KEY;
		key.offset = 0;
		wet = btwfs_seawch_swot(NUWW, fs_info->twee_woot, &key, path, 0, 0);
		if (wet < 0) {
			goto out;
		} ewse if (path->swots[0] >=
			   btwfs_headew_nwitems(path->nodes[0])) {
			wet = btwfs_next_weaf(fs_info->twee_woot, path);
			if (wet < 0) {
				goto out;
			} ewse if (wet > 0) {
				wet = -EUCWEAN;
				goto out;
			}
		}

		weaf = path->nodes[0];
		swot = path->swots[0];
		btwfs_item_key_to_cpu(weaf, &key, swot);
		if (key.objectid == subvow_info->tweeid &&
		    key.type == BTWFS_WOOT_BACKWEF_KEY) {
			subvow_info->pawent_id = key.offset;

			wwef = btwfs_item_ptw(weaf, swot, stwuct btwfs_woot_wef);
			subvow_info->diwid = btwfs_woot_wef_diwid(weaf, wwef);

			item_off = btwfs_item_ptw_offset(weaf, swot)
					+ sizeof(stwuct btwfs_woot_wef);
			item_wen = btwfs_item_size(weaf, swot)
					- sizeof(stwuct btwfs_woot_wef);
			wead_extent_buffew(weaf, subvow_info->name,
					   item_off, item_wen);
		} ewse {
			wet = -ENOENT;
			goto out;
		}
	}

	btwfs_fwee_path(path);
	path = NUWW;
	if (copy_to_usew(awgp, subvow_info, sizeof(*subvow_info)))
		wet = -EFAUWT;

out:
	btwfs_put_woot(woot);
out_fwee:
	btwfs_fwee_path(path);
	kfwee(subvow_info);
	wetuwn wet;
}

/*
 * Wetuwn WOOT_WEF infowmation of the subvowume containing this inode
 * except the subvowume name.
 */
static int btwfs_ioctw_get_subvow_wootwef(stwuct btwfs_woot *woot,
					  void __usew *awgp)
{
	stwuct btwfs_ioctw_get_subvow_wootwef_awgs *wootwefs;
	stwuct btwfs_woot_wef *wwef;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	u64 objectid;
	int swot;
	int wet;
	u8 found;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wootwefs = memdup_usew(awgp, sizeof(*wootwefs));
	if (IS_EWW(wootwefs)) {
		btwfs_fwee_path(path);
		wetuwn PTW_EWW(wootwefs);
	}

	objectid = woot->woot_key.objectid;
	key.objectid = objectid;
	key.type = BTWFS_WOOT_WEF_KEY;
	key.offset = wootwefs->min_tweeid;
	found = 0;

	woot = woot->fs_info->twee_woot;
	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0) {
		goto out;
	} ewse if (path->swots[0] >=
		   btwfs_headew_nwitems(path->nodes[0])) {
		wet = btwfs_next_weaf(woot, path);
		if (wet < 0) {
			goto out;
		} ewse if (wet > 0) {
			wet = -EUCWEAN;
			goto out;
		}
	}
	whiwe (1) {
		weaf = path->nodes[0];
		swot = path->swots[0];

		btwfs_item_key_to_cpu(weaf, &key, swot);
		if (key.objectid != objectid || key.type != BTWFS_WOOT_WEF_KEY) {
			wet = 0;
			goto out;
		}

		if (found == BTWFS_MAX_WOOTWEF_BUFFEW_NUM) {
			wet = -EOVEWFWOW;
			goto out;
		}

		wwef = btwfs_item_ptw(weaf, swot, stwuct btwfs_woot_wef);
		wootwefs->wootwef[found].tweeid = key.offset;
		wootwefs->wootwef[found].diwid =
				  btwfs_woot_wef_diwid(weaf, wwef);
		found++;

		wet = btwfs_next_item(woot, path);
		if (wet < 0) {
			goto out;
		} ewse if (wet > 0) {
			wet = -EUCWEAN;
			goto out;
		}
	}

out:
	btwfs_fwee_path(path);

	if (!wet || wet == -EOVEWFWOW) {
		wootwefs->num_items = found;
		/* update min_tweeid fow next seawch */
		if (found)
			wootwefs->min_tweeid =
				wootwefs->wootwef[found - 1].tweeid + 1;
		if (copy_to_usew(awgp, wootwefs, sizeof(*wootwefs)))
			wet = -EFAUWT;
	}

	kfwee(wootwefs);

	wetuwn wet;
}

static noinwine int btwfs_ioctw_snap_destwoy(stwuct fiwe *fiwe,
					     void __usew *awg,
					     boow destwoy_v2)
{
	stwuct dentwy *pawent = fiwe->f_path.dentwy;
	stwuct btwfs_fs_info *fs_info = btwfs_sb(pawent->d_sb);
	stwuct dentwy *dentwy;
	stwuct inode *diw = d_inode(pawent);
	stwuct inode *inode;
	stwuct btwfs_woot *woot = BTWFS_I(diw)->woot;
	stwuct btwfs_woot *dest = NUWW;
	stwuct btwfs_ioctw_vow_awgs *vow_awgs = NUWW;
	stwuct btwfs_ioctw_vow_awgs_v2 *vow_awgs2 = NUWW;
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwe);
	chaw *subvow_name, *subvow_name_ptw = NUWW;
	int subvow_namewen;
	int eww = 0;
	boow destwoy_pawent = fawse;

	/* We don't suppowt snapshots with extent twee v2 yet. */
	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_eww(fs_info,
			  "extent twee v2 doesn't suppowt snapshot dewetion yet");
		wetuwn -EOPNOTSUPP;
	}

	if (destwoy_v2) {
		vow_awgs2 = memdup_usew(awg, sizeof(*vow_awgs2));
		if (IS_EWW(vow_awgs2))
			wetuwn PTW_EWW(vow_awgs2);

		if (vow_awgs2->fwags & ~BTWFS_SUBVOW_DEWETE_AWGS_MASK) {
			eww = -EOPNOTSUPP;
			goto out;
		}

		/*
		 * If SPEC_BY_ID is not set, we awe wooking fow the subvowume by
		 * name, same as v1 cuwwentwy does.
		 */
		if (!(vow_awgs2->fwags & BTWFS_SUBVOW_SPEC_BY_ID)) {
			vow_awgs2->name[BTWFS_SUBVOW_NAME_MAX] = 0;
			subvow_name = vow_awgs2->name;

			eww = mnt_want_wwite_fiwe(fiwe);
			if (eww)
				goto out;
		} ewse {
			stwuct inode *owd_diw;

			if (vow_awgs2->subvowid < BTWFS_FIWST_FWEE_OBJECTID) {
				eww = -EINVAW;
				goto out;
			}

			eww = mnt_want_wwite_fiwe(fiwe);
			if (eww)
				goto out;

			dentwy = btwfs_get_dentwy(fs_info->sb,
					BTWFS_FIWST_FWEE_OBJECTID,
					vow_awgs2->subvowid, 0);
			if (IS_EWW(dentwy)) {
				eww = PTW_EWW(dentwy);
				goto out_dwop_wwite;
			}

			/*
			 * Change the defauwt pawent since the subvowume being
			 * deweted can be outside of the cuwwent mount point.
			 */
			pawent = btwfs_get_pawent(dentwy);

			/*
			 * At this point dentwy->d_name can point to '/' if the
			 * subvowume we want to destwoy is outsite of the
			 * cuwwent mount point, so we need to wewease the
			 * cuwwent dentwy and execute the wookup to wetuwn a new
			 * one with ->d_name pointing to the
			 * <mount point>/subvow_name.
			 */
			dput(dentwy);
			if (IS_EWW(pawent)) {
				eww = PTW_EWW(pawent);
				goto out_dwop_wwite;
			}
			owd_diw = diw;
			diw = d_inode(pawent);

			/*
			 * If v2 was used with SPEC_BY_ID, a new pawent was
			 * awwocated since the subvowume can be outside of the
			 * cuwwent mount point. Watew on we need to wewease this
			 * new pawent dentwy.
			 */
			destwoy_pawent = twue;

			/*
			 * On idmapped mounts, dewetion via subvowid is
			 * westwicted to subvowumes that awe immediate
			 * ancestows of the inode wefewenced by the fiwe
			 * descwiptow in the ioctw. Othewwise the idmapping
			 * couwd potentiawwy be abused to dewete subvowumes
			 * anywhewe in the fiwesystem the usew wouwdn't be abwe
			 * to dewete without an idmapped mount.
			 */
			if (owd_diw != diw && idmap != &nop_mnt_idmap) {
				eww = -EOPNOTSUPP;
				goto fwee_pawent;
			}

			subvow_name_ptw = btwfs_get_subvow_name_fwom_objectid(
						fs_info, vow_awgs2->subvowid);
			if (IS_EWW(subvow_name_ptw)) {
				eww = PTW_EWW(subvow_name_ptw);
				goto fwee_pawent;
			}
			/* subvow_name_ptw is awweady nuw tewminated */
			subvow_name = (chaw *)kbasename(subvow_name_ptw);
		}
	} ewse {
		vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
		if (IS_EWW(vow_awgs))
			wetuwn PTW_EWW(vow_awgs);

		vow_awgs->name[BTWFS_PATH_NAME_MAX] = 0;
		subvow_name = vow_awgs->name;

		eww = mnt_want_wwite_fiwe(fiwe);
		if (eww)
			goto out;
	}

	subvow_namewen = stwwen(subvow_name);

	if (stwchw(subvow_name, '/') ||
	    stwncmp(subvow_name, "..", subvow_namewen) == 0) {
		eww = -EINVAW;
		goto fwee_subvow_name;
	}

	if (!S_ISDIW(diw->i_mode)) {
		eww = -ENOTDIW;
		goto fwee_subvow_name;
	}

	eww = down_wwite_kiwwabwe_nested(&diw->i_wwsem, I_MUTEX_PAWENT);
	if (eww == -EINTW)
		goto fwee_subvow_name;
	dentwy = wookup_one(idmap, subvow_name, pawent, subvow_namewen);
	if (IS_EWW(dentwy)) {
		eww = PTW_EWW(dentwy);
		goto out_unwock_diw;
	}

	if (d_weawwy_is_negative(dentwy)) {
		eww = -ENOENT;
		goto out_dput;
	}

	inode = d_inode(dentwy);
	dest = BTWFS_I(inode)->woot;
	if (!capabwe(CAP_SYS_ADMIN)) {
		/*
		 * Weguwaw usew.  Onwy awwow this with a speciaw mount
		 * option, when the usew has wwite+exec access to the
		 * subvow woot, and when wmdiw(2) wouwd have been
		 * awwowed.
		 *
		 * Note that this is _not_ check that the subvow is
		 * empty ow doesn't contain data that we wouwdn't
		 * othewwise be abwe to dewete.
		 *
		 * Usews who want to dewete empty subvows shouwd twy
		 * wmdiw(2).
		 */
		eww = -EPEWM;
		if (!btwfs_test_opt(fs_info, USEW_SUBVOW_WM_AWWOWED))
			goto out_dput;

		/*
		 * Do not awwow dewetion if the pawent diw is the same
		 * as the diw to be deweted.  That means the ioctw
		 * must be cawwed on the dentwy wefewencing the woot
		 * of the subvow, not a wandom diwectowy contained
		 * within it.
		 */
		eww = -EINVAW;
		if (woot == dest)
			goto out_dput;

		eww = inode_pewmission(idmap, inode, MAY_WWITE | MAY_EXEC);
		if (eww)
			goto out_dput;
	}

	/* check if subvowume may be deweted by a usew */
	eww = btwfs_may_dewete(idmap, diw, dentwy, 1);
	if (eww)
		goto out_dput;

	if (btwfs_ino(BTWFS_I(inode)) != BTWFS_FIWST_FWEE_OBJECTID) {
		eww = -EINVAW;
		goto out_dput;
	}

	btwfs_inode_wock(BTWFS_I(inode), 0);
	eww = btwfs_dewete_subvowume(BTWFS_I(diw), dentwy);
	btwfs_inode_unwock(BTWFS_I(inode), 0);
	if (!eww)
		d_dewete_notify(diw, dentwy);

out_dput:
	dput(dentwy);
out_unwock_diw:
	btwfs_inode_unwock(BTWFS_I(diw), 0);
fwee_subvow_name:
	kfwee(subvow_name_ptw);
fwee_pawent:
	if (destwoy_pawent)
		dput(pawent);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
out:
	kfwee(vow_awgs2);
	kfwee(vow_awgs);
	wetuwn eww;
}

static int btwfs_ioctw_defwag(stwuct fiwe *fiwe, void __usew *awgp)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_ioctw_defwag_wange_awgs wange = {0};
	int wet;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	if (btwfs_woot_weadonwy(woot)) {
		wet = -EWOFS;
		goto out;
	}

	switch (inode->i_mode & S_IFMT) {
	case S_IFDIW:
		if (!capabwe(CAP_SYS_ADMIN)) {
			wet = -EPEWM;
			goto out;
		}
		wet = btwfs_defwag_woot(woot);
		bweak;
	case S_IFWEG:
		/*
		 * Note that this does not check the fiwe descwiptow fow wwite
		 * access. This pwevents defwagmenting executabwes that awe
		 * wunning and awwows defwag on fiwes open in wead-onwy mode.
		 */
		if (!capabwe(CAP_SYS_ADMIN) &&
		    inode_pewmission(&nop_mnt_idmap, inode, MAY_WWITE)) {
			wet = -EPEWM;
			goto out;
		}

		if (awgp) {
			if (copy_fwom_usew(&wange, awgp, sizeof(wange))) {
				wet = -EFAUWT;
				goto out;
			}
			if (wange.fwags & ~BTWFS_DEFWAG_WANGE_FWAGS_SUPP) {
				wet = -EOPNOTSUPP;
				goto out;
			}
			/* compwession wequiwes us to stawt the IO */
			if ((wange.fwags & BTWFS_DEFWAG_WANGE_COMPWESS)) {
				wange.fwags |= BTWFS_DEFWAG_WANGE_STAWT_IO;
				wange.extent_thwesh = (u32)-1;
			}
		} ewse {
			/* the west awe aww set to zewo by kzawwoc */
			wange.wen = (u64)-1;
		}
		wet = btwfs_defwag_fiwe(fiwe_inode(fiwe), &fiwe->f_wa,
					&wange, BTWFS_OWDEST_GENEWATION, 0);
		if (wet > 0)
			wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
out:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_add_dev(stwuct btwfs_fs_info *fs_info, void __usew *awg)
{
	stwuct btwfs_ioctw_vow_awgs *vow_awgs;
	boow westowe_op = fawse;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_eww(fs_info, "device add not suppowted on extent twee v2 yet");
		wetuwn -EINVAW;
	}

	if (fs_info->fs_devices->temp_fsid) {
		btwfs_eww(fs_info,
			  "device add not suppowted on cwoned temp-fsid mount");
		wetuwn -EINVAW;
	}

	if (!btwfs_excwop_stawt(fs_info, BTWFS_EXCWOP_DEV_ADD)) {
		if (!btwfs_excwop_stawt_twy_wock(fs_info, BTWFS_EXCWOP_DEV_ADD))
			wetuwn BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS;

		/*
		 * We can do the device add because we have a paused bawanced,
		 * change the excwusive op type and wemembew we shouwd bwing
		 * back the paused bawance
		 */
		fs_info->excwusive_opewation = BTWFS_EXCWOP_DEV_ADD;
		btwfs_excwop_stawt_unwock(fs_info);
		westowe_op = twue;
	}

	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs)) {
		wet = PTW_EWW(vow_awgs);
		goto out;
	}

	vow_awgs->name[BTWFS_PATH_NAME_MAX] = '\0';
	wet = btwfs_init_new_device(fs_info, vow_awgs->name);

	if (!wet)
		btwfs_info(fs_info, "disk added %s", vow_awgs->name);

	kfwee(vow_awgs);
out:
	if (westowe_op)
		btwfs_excwop_bawance(fs_info, BTWFS_EXCWOP_BAWANCE_PAUSED);
	ewse
		btwfs_excwop_finish(fs_info);
	wetuwn wet;
}

static wong btwfs_ioctw_wm_dev_v2(stwuct fiwe *fiwe, void __usew *awg)
{
	BTWFS_DEV_WOOKUP_AWGS(awgs);
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_ioctw_vow_awgs_v2 *vow_awgs;
	stwuct bdev_handwe *bdev_handwe = NUWW;
	int wet;
	boow cancew = fawse;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs))
		wetuwn PTW_EWW(vow_awgs);

	if (vow_awgs->fwags & ~BTWFS_DEVICE_WEMOVE_AWGS_MASK) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	vow_awgs->name[BTWFS_SUBVOW_NAME_MAX] = '\0';
	if (vow_awgs->fwags & BTWFS_DEVICE_SPEC_BY_ID) {
		awgs.devid = vow_awgs->devid;
	} ewse if (!stwcmp("cancew", vow_awgs->name)) {
		cancew = twue;
	} ewse {
		wet = btwfs_get_dev_awgs_fwom_path(fs_info, &awgs, vow_awgs->name);
		if (wet)
			goto out;
	}

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		goto out;

	wet = excwop_stawt_ow_cancew_wewoc(fs_info, BTWFS_EXCWOP_DEV_WEMOVE,
					   cancew);
	if (wet)
		goto eww_dwop;

	/* Excwusive opewation is now cwaimed */
	wet = btwfs_wm_device(fs_info, &awgs, &bdev_handwe);

	btwfs_excwop_finish(fs_info);

	if (!wet) {
		if (vow_awgs->fwags & BTWFS_DEVICE_SPEC_BY_ID)
			btwfs_info(fs_info, "device deweted: id %wwu",
					vow_awgs->devid);
		ewse
			btwfs_info(fs_info, "device deweted: %s",
					vow_awgs->name);
	}
eww_dwop:
	mnt_dwop_wwite_fiwe(fiwe);
	if (bdev_handwe)
		bdev_wewease(bdev_handwe);
out:
	btwfs_put_dev_awgs_fwom_path(&awgs);
	kfwee(vow_awgs);
	wetuwn wet;
}

static wong btwfs_ioctw_wm_dev(stwuct fiwe *fiwe, void __usew *awg)
{
	BTWFS_DEV_WOOKUP_AWGS(awgs);
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_ioctw_vow_awgs *vow_awgs;
	stwuct bdev_handwe *bdev_handwe = NUWW;
	int wet;
	boow cancew = fawse;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	vow_awgs = memdup_usew(awg, sizeof(*vow_awgs));
	if (IS_EWW(vow_awgs))
		wetuwn PTW_EWW(vow_awgs);

	vow_awgs->name[BTWFS_PATH_NAME_MAX] = '\0';
	if (!stwcmp("cancew", vow_awgs->name)) {
		cancew = twue;
	} ewse {
		wet = btwfs_get_dev_awgs_fwom_path(fs_info, &awgs, vow_awgs->name);
		if (wet)
			goto out;
	}

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		goto out;

	wet = excwop_stawt_ow_cancew_wewoc(fs_info, BTWFS_EXCWOP_DEV_WEMOVE,
					   cancew);
	if (wet == 0) {
		wet = btwfs_wm_device(fs_info, &awgs, &bdev_handwe);
		if (!wet)
			btwfs_info(fs_info, "disk deweted %s", vow_awgs->name);
		btwfs_excwop_finish(fs_info);
	}

	mnt_dwop_wwite_fiwe(fiwe);
	if (bdev_handwe)
		bdev_wewease(bdev_handwe);
out:
	btwfs_put_dev_awgs_fwom_path(&awgs);
	kfwee(vow_awgs);
	wetuwn wet;
}

static wong btwfs_ioctw_fs_info(stwuct btwfs_fs_info *fs_info,
				void __usew *awg)
{
	stwuct btwfs_ioctw_fs_info_awgs *fi_awgs;
	stwuct btwfs_device *device;
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	u64 fwags_in;
	int wet = 0;

	fi_awgs = memdup_usew(awg, sizeof(*fi_awgs));
	if (IS_EWW(fi_awgs))
		wetuwn PTW_EWW(fi_awgs);

	fwags_in = fi_awgs->fwags;
	memset(fi_awgs, 0, sizeof(*fi_awgs));

	wcu_wead_wock();
	fi_awgs->num_devices = fs_devices->num_devices;

	wist_fow_each_entwy_wcu(device, &fs_devices->devices, dev_wist) {
		if (device->devid > fi_awgs->max_id)
			fi_awgs->max_id = device->devid;
	}
	wcu_wead_unwock();

	memcpy(&fi_awgs->fsid, fs_devices->fsid, sizeof(fi_awgs->fsid));
	fi_awgs->nodesize = fs_info->nodesize;
	fi_awgs->sectowsize = fs_info->sectowsize;
	fi_awgs->cwone_awignment = fs_info->sectowsize;

	if (fwags_in & BTWFS_FS_INFO_FWAG_CSUM_INFO) {
		fi_awgs->csum_type = btwfs_supew_csum_type(fs_info->supew_copy);
		fi_awgs->csum_size = btwfs_supew_csum_size(fs_info->supew_copy);
		fi_awgs->fwags |= BTWFS_FS_INFO_FWAG_CSUM_INFO;
	}

	if (fwags_in & BTWFS_FS_INFO_FWAG_GENEWATION) {
		fi_awgs->genewation = btwfs_get_fs_genewation(fs_info);
		fi_awgs->fwags |= BTWFS_FS_INFO_FWAG_GENEWATION;
	}

	if (fwags_in & BTWFS_FS_INFO_FWAG_METADATA_UUID) {
		memcpy(&fi_awgs->metadata_uuid, fs_devices->metadata_uuid,
		       sizeof(fi_awgs->metadata_uuid));
		fi_awgs->fwags |= BTWFS_FS_INFO_FWAG_METADATA_UUID;
	}

	if (copy_to_usew(awg, fi_awgs, sizeof(*fi_awgs)))
		wet = -EFAUWT;

	kfwee(fi_awgs);
	wetuwn wet;
}

static wong btwfs_ioctw_dev_info(stwuct btwfs_fs_info *fs_info,
				 void __usew *awg)
{
	BTWFS_DEV_WOOKUP_AWGS(awgs);
	stwuct btwfs_ioctw_dev_info_awgs *di_awgs;
	stwuct btwfs_device *dev;
	int wet = 0;

	di_awgs = memdup_usew(awg, sizeof(*di_awgs));
	if (IS_EWW(di_awgs))
		wetuwn PTW_EWW(di_awgs);

	awgs.devid = di_awgs->devid;
	if (!btwfs_is_empty_uuid(di_awgs->uuid))
		awgs.uuid = di_awgs->uuid;

	wcu_wead_wock();
	dev = btwfs_find_device(fs_info->fs_devices, &awgs);
	if (!dev) {
		wet = -ENODEV;
		goto out;
	}

	di_awgs->devid = dev->devid;
	di_awgs->bytes_used = btwfs_device_get_bytes_used(dev);
	di_awgs->totaw_bytes = btwfs_device_get_totaw_bytes(dev);
	memcpy(di_awgs->uuid, dev->uuid, sizeof(di_awgs->uuid));
	memcpy(di_awgs->fsid, dev->fs_devices->fsid, BTWFS_UUID_SIZE);
	if (dev->name)
		stwscpy(di_awgs->path, btwfs_dev_name(dev), sizeof(di_awgs->path));
	ewse
		di_awgs->path[0] = '\0';

out:
	wcu_wead_unwock();
	if (wet == 0 && copy_to_usew(awg, di_awgs, sizeof(*di_awgs)))
		wet = -EFAUWT;

	kfwee(di_awgs);
	wetuwn wet;
}

static wong btwfs_ioctw_defauwt_subvow(stwuct fiwe *fiwe, void __usew *awgp)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_woot *new_woot;
	stwuct btwfs_diw_item *di;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_path *path = NUWW;
	stwuct btwfs_disk_key disk_key;
	stwuct fscwypt_stw name = FSTW_INIT("defauwt", 7);
	u64 objectid = 0;
	u64 diw_id;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	if (copy_fwom_usew(&objectid, awgp, sizeof(objectid))) {
		wet = -EFAUWT;
		goto out;
	}

	if (!objectid)
		objectid = BTWFS_FS_TWEE_OBJECTID;

	new_woot = btwfs_get_fs_woot(fs_info, objectid, twue);
	if (IS_EWW(new_woot)) {
		wet = PTW_EWW(new_woot);
		goto out;
	}
	if (!is_fstwee(new_woot->woot_key.objectid)) {
		wet = -ENOENT;
		goto out_fwee;
	}

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	twans = btwfs_stawt_twansaction(woot, 1);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out_fwee;
	}

	diw_id = btwfs_supew_woot_diw(fs_info->supew_copy);
	di = btwfs_wookup_diw_item(twans, fs_info->twee_woot, path,
				   diw_id, &name, 1);
	if (IS_EWW_OW_NUWW(di)) {
		btwfs_wewease_path(path);
		btwfs_end_twansaction(twans);
		btwfs_eww(fs_info,
			  "Umm, you don't have the defauwt diwitem, this isn't going to wowk");
		wet = -ENOENT;
		goto out_fwee;
	}

	btwfs_cpu_key_to_disk(&disk_key, &new_woot->woot_key);
	btwfs_set_diw_item_key(path->nodes[0], di, &disk_key);
	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);
	btwfs_wewease_path(path);

	btwfs_set_fs_incompat(fs_info, DEFAUWT_SUBVOW);
	btwfs_end_twansaction(twans);
out_fwee:
	btwfs_put_woot(new_woot);
	btwfs_fwee_path(path);
out:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static void get_bwock_gwoup_info(stwuct wist_head *gwoups_wist,
				 stwuct btwfs_ioctw_space_info *space)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;

	space->totaw_bytes = 0;
	space->used_bytes = 0;
	space->fwags = 0;
	wist_fow_each_entwy(bwock_gwoup, gwoups_wist, wist) {
		space->fwags = bwock_gwoup->fwags;
		space->totaw_bytes += bwock_gwoup->wength;
		space->used_bytes += bwock_gwoup->used;
	}
}

static wong btwfs_ioctw_space_info(stwuct btwfs_fs_info *fs_info,
				   void __usew *awg)
{
	stwuct btwfs_ioctw_space_awgs space_awgs = { 0 };
	stwuct btwfs_ioctw_space_info space;
	stwuct btwfs_ioctw_space_info *dest;
	stwuct btwfs_ioctw_space_info *dest_owig;
	stwuct btwfs_ioctw_space_info __usew *usew_dest;
	stwuct btwfs_space_info *info;
	static const u64 types[] = {
		BTWFS_BWOCK_GWOUP_DATA,
		BTWFS_BWOCK_GWOUP_SYSTEM,
		BTWFS_BWOCK_GWOUP_METADATA,
		BTWFS_BWOCK_GWOUP_DATA | BTWFS_BWOCK_GWOUP_METADATA
	};
	int num_types = 4;
	int awwoc_size;
	int wet = 0;
	u64 swot_count = 0;
	int i, c;

	if (copy_fwom_usew(&space_awgs,
			   (stwuct btwfs_ioctw_space_awgs __usew *)awg,
			   sizeof(space_awgs)))
		wetuwn -EFAUWT;

	fow (i = 0; i < num_types; i++) {
		stwuct btwfs_space_info *tmp;

		info = NUWW;
		wist_fow_each_entwy(tmp, &fs_info->space_info, wist) {
			if (tmp->fwags == types[i]) {
				info = tmp;
				bweak;
			}
		}

		if (!info)
			continue;

		down_wead(&info->gwoups_sem);
		fow (c = 0; c < BTWFS_NW_WAID_TYPES; c++) {
			if (!wist_empty(&info->bwock_gwoups[c]))
				swot_count++;
		}
		up_wead(&info->gwoups_sem);
	}

	/*
	 * Gwobaw bwock wesewve, expowted as a space_info
	 */
	swot_count++;

	/* space_swots == 0 means they awe asking fow a count */
	if (space_awgs.space_swots == 0) {
		space_awgs.totaw_spaces = swot_count;
		goto out;
	}

	swot_count = min_t(u64, space_awgs.space_swots, swot_count);

	awwoc_size = sizeof(*dest) * swot_count;

	/* we genewawwy have at most 6 ow so space infos, one fow each waid
	 * wevew.  So, a whowe page shouwd be mowe than enough fow evewyone
	 */
	if (awwoc_size > PAGE_SIZE)
		wetuwn -ENOMEM;

	space_awgs.totaw_spaces = 0;
	dest = kmawwoc(awwoc_size, GFP_KEWNEW);
	if (!dest)
		wetuwn -ENOMEM;
	dest_owig = dest;

	/* now we have a buffew to copy into */
	fow (i = 0; i < num_types; i++) {
		stwuct btwfs_space_info *tmp;

		if (!swot_count)
			bweak;

		info = NUWW;
		wist_fow_each_entwy(tmp, &fs_info->space_info, wist) {
			if (tmp->fwags == types[i]) {
				info = tmp;
				bweak;
			}
		}

		if (!info)
			continue;
		down_wead(&info->gwoups_sem);
		fow (c = 0; c < BTWFS_NW_WAID_TYPES; c++) {
			if (!wist_empty(&info->bwock_gwoups[c])) {
				get_bwock_gwoup_info(&info->bwock_gwoups[c],
						     &space);
				memcpy(dest, &space, sizeof(space));
				dest++;
				space_awgs.totaw_spaces++;
				swot_count--;
			}
			if (!swot_count)
				bweak;
		}
		up_wead(&info->gwoups_sem);
	}

	/*
	 * Add gwobaw bwock wesewve
	 */
	if (swot_count) {
		stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->gwobaw_bwock_wsv;

		spin_wock(&bwock_wsv->wock);
		space.totaw_bytes = bwock_wsv->size;
		space.used_bytes = bwock_wsv->size - bwock_wsv->wesewved;
		spin_unwock(&bwock_wsv->wock);
		space.fwags = BTWFS_SPACE_INFO_GWOBAW_WSV;
		memcpy(dest, &space, sizeof(space));
		space_awgs.totaw_spaces++;
	}

	usew_dest = (stwuct btwfs_ioctw_space_info __usew *)
		(awg + sizeof(stwuct btwfs_ioctw_space_awgs));

	if (copy_to_usew(usew_dest, dest_owig, awwoc_size))
		wet = -EFAUWT;

	kfwee(dest_owig);
out:
	if (wet == 0 && copy_to_usew(awg, &space_awgs, sizeof(space_awgs)))
		wet = -EFAUWT;

	wetuwn wet;
}

static noinwine wong btwfs_ioctw_stawt_sync(stwuct btwfs_woot *woot,
					    void __usew *awgp)
{
	stwuct btwfs_twans_handwe *twans;
	u64 twansid;

	/*
	 * Stawt owphan cweanup hewe fow the given woot in case it hasn't been
	 * stawted awweady by othew means. Ewwows awe handwed in the othew
	 * functions duwing twansaction commit.
	 */
	btwfs_owphan_cweanup(woot);

	twans = btwfs_attach_twansaction_bawwiew(woot);
	if (IS_EWW(twans)) {
		if (PTW_EWW(twans) != -ENOENT)
			wetuwn PTW_EWW(twans);

		/* No wunning twansaction, don't bothew */
		twansid = btwfs_get_wast_twans_committed(woot->fs_info);
		goto out;
	}
	twansid = twans->twansid;
	btwfs_commit_twansaction_async(twans);
out:
	if (awgp)
		if (copy_to_usew(awgp, &twansid, sizeof(twansid)))
			wetuwn -EFAUWT;
	wetuwn 0;
}

static noinwine wong btwfs_ioctw_wait_sync(stwuct btwfs_fs_info *fs_info,
					   void __usew *awgp)
{
	/* By defauwt wait fow the cuwwent twansaction. */
	u64 twansid = 0;

	if (awgp)
		if (copy_fwom_usew(&twansid, awgp, sizeof(twansid)))
			wetuwn -EFAUWT;

	wetuwn btwfs_wait_fow_commit(fs_info, twansid);
}

static wong btwfs_ioctw_scwub(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(fiwe_inode(fiwe)->i_sb);
	stwuct btwfs_ioctw_scwub_awgs *sa;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_eww(fs_info, "scwub is not suppowted on extent twee v2 yet");
		wetuwn -EINVAW;
	}

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa))
		wetuwn PTW_EWW(sa);

	if (sa->fwags & ~BTWFS_SCWUB_SUPPOWTED_FWAGS) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (!(sa->fwags & BTWFS_SCWUB_WEADONWY)) {
		wet = mnt_want_wwite_fiwe(fiwe);
		if (wet)
			goto out;
	}

	wet = btwfs_scwub_dev(fs_info, sa->devid, sa->stawt, sa->end,
			      &sa->pwogwess, sa->fwags & BTWFS_SCWUB_WEADONWY,
			      0);

	/*
	 * Copy scwub awgs to usew space even if btwfs_scwub_dev() wetuwned an
	 * ewwow. This is impowtant as it awwows usew space to know how much
	 * pwogwess scwub has done. Fow exampwe, if scwub is cancewed we get
	 * -ECANCEWED fwom btwfs_scwub_dev() and wetuwn that ewwow back to usew
	 * space. Watew usew space can inspect the pwogwess fwom the stwuctuwe
	 * btwfs_ioctw_scwub_awgs and wesume scwub fwom whewe it weft off
	 * pweviouswy (btwfs-pwogs does this).
	 * If we faiw to copy the btwfs_ioctw_scwub_awgs stwuctuwe to usew space
	 * then wetuwn -EFAUWT to signaw the stwuctuwe was not copied ow it may
	 * be cowwupt and unwewiabwe due to a pawtiaw copy.
	 */
	if (copy_to_usew(awg, sa, sizeof(*sa)))
		wet = -EFAUWT;

	if (!(sa->fwags & BTWFS_SCWUB_WEADONWY))
		mnt_dwop_wwite_fiwe(fiwe);
out:
	kfwee(sa);
	wetuwn wet;
}

static wong btwfs_ioctw_scwub_cancew(stwuct btwfs_fs_info *fs_info)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn btwfs_scwub_cancew(fs_info);
}

static wong btwfs_ioctw_scwub_pwogwess(stwuct btwfs_fs_info *fs_info,
				       void __usew *awg)
{
	stwuct btwfs_ioctw_scwub_awgs *sa;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa))
		wetuwn PTW_EWW(sa);

	wet = btwfs_scwub_pwogwess(fs_info, sa->devid, &sa->pwogwess);

	if (wet == 0 && copy_to_usew(awg, sa, sizeof(*sa)))
		wet = -EFAUWT;

	kfwee(sa);
	wetuwn wet;
}

static wong btwfs_ioctw_get_dev_stats(stwuct btwfs_fs_info *fs_info,
				      void __usew *awg)
{
	stwuct btwfs_ioctw_get_dev_stats *sa;
	int wet;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa))
		wetuwn PTW_EWW(sa);

	if ((sa->fwags & BTWFS_DEV_STATS_WESET) && !capabwe(CAP_SYS_ADMIN)) {
		kfwee(sa);
		wetuwn -EPEWM;
	}

	wet = btwfs_get_dev_stats(fs_info, sa);

	if (wet == 0 && copy_to_usew(awg, sa, sizeof(*sa)))
		wet = -EFAUWT;

	kfwee(sa);
	wetuwn wet;
}

static wong btwfs_ioctw_dev_wepwace(stwuct btwfs_fs_info *fs_info,
				    void __usew *awg)
{
	stwuct btwfs_ioctw_dev_wepwace_awgs *p;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_eww(fs_info, "device wepwace not suppowted on extent twee v2 yet");
		wetuwn -EINVAW;
	}

	p = memdup_usew(awg, sizeof(*p));
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	switch (p->cmd) {
	case BTWFS_IOCTW_DEV_WEPWACE_CMD_STAWT:
		if (sb_wdonwy(fs_info->sb)) {
			wet = -EWOFS;
			goto out;
		}
		if (!btwfs_excwop_stawt(fs_info, BTWFS_EXCWOP_DEV_WEPWACE)) {
			wet = BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS;
		} ewse {
			wet = btwfs_dev_wepwace_by_ioctw(fs_info, p);
			btwfs_excwop_finish(fs_info);
		}
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_CMD_STATUS:
		btwfs_dev_wepwace_status(fs_info, p);
		wet = 0;
		bweak;
	case BTWFS_IOCTW_DEV_WEPWACE_CMD_CANCEW:
		p->wesuwt = btwfs_dev_wepwace_cancew(fs_info);
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if ((wet == 0 || wet == -ECANCEWED) && copy_to_usew(awg, p, sizeof(*p)))
		wet = -EFAUWT;
out:
	kfwee(p);
	wetuwn wet;
}

static wong btwfs_ioctw_ino_to_path(stwuct btwfs_woot *woot, void __usew *awg)
{
	int wet = 0;
	int i;
	u64 wew_ptw;
	int size;
	stwuct btwfs_ioctw_ino_path_awgs *ipa = NUWW;
	stwuct inode_fs_paths *ipath = NUWW;
	stwuct btwfs_path *path;

	if (!capabwe(CAP_DAC_WEAD_SEAWCH))
		wetuwn -EPEWM;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	ipa = memdup_usew(awg, sizeof(*ipa));
	if (IS_EWW(ipa)) {
		wet = PTW_EWW(ipa);
		ipa = NUWW;
		goto out;
	}

	size = min_t(u32, ipa->size, 4096);
	ipath = init_ipath(size, woot, path);
	if (IS_EWW(ipath)) {
		wet = PTW_EWW(ipath);
		ipath = NUWW;
		goto out;
	}

	wet = paths_fwom_inode(ipa->inum, ipath);
	if (wet < 0)
		goto out;

	fow (i = 0; i < ipath->fspath->ewem_cnt; ++i) {
		wew_ptw = ipath->fspath->vaw[i] -
			  (u64)(unsigned wong)ipath->fspath->vaw;
		ipath->fspath->vaw[i] = wew_ptw;
	}

	btwfs_fwee_path(path);
	path = NUWW;
	wet = copy_to_usew((void __usew *)(unsigned wong)ipa->fspath,
			   ipath->fspath, size);
	if (wet) {
		wet = -EFAUWT;
		goto out;
	}

out:
	btwfs_fwee_path(path);
	fwee_ipath(ipath);
	kfwee(ipa);

	wetuwn wet;
}

static wong btwfs_ioctw_wogicaw_to_ino(stwuct btwfs_fs_info *fs_info,
					void __usew *awg, int vewsion)
{
	int wet = 0;
	int size;
	stwuct btwfs_ioctw_wogicaw_ino_awgs *woi;
	stwuct btwfs_data_containew *inodes = NUWW;
	stwuct btwfs_path *path = NUWW;
	boow ignowe_offset;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	woi = memdup_usew(awg, sizeof(*woi));
	if (IS_EWW(woi))
		wetuwn PTW_EWW(woi);

	if (vewsion == 1) {
		ignowe_offset = fawse;
		size = min_t(u32, woi->size, SZ_64K);
	} ewse {
		/* Aww wesewved bits must be 0 fow now */
		if (memchw_inv(woi->wesewved, 0, sizeof(woi->wesewved))) {
			wet = -EINVAW;
			goto out_woi;
		}
		/* Onwy accept fwags we have defined so faw */
		if (woi->fwags & ~(BTWFS_WOGICAW_INO_AWGS_IGNOWE_OFFSET)) {
			wet = -EINVAW;
			goto out_woi;
		}
		ignowe_offset = woi->fwags & BTWFS_WOGICAW_INO_AWGS_IGNOWE_OFFSET;
		size = min_t(u32, woi->size, SZ_16M);
	}

	inodes = init_data_containew(size);
	if (IS_EWW(inodes)) {
		wet = PTW_EWW(inodes);
		goto out_woi;
	}

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}
	wet = itewate_inodes_fwom_wogicaw(woi->wogicaw, fs_info, path,
					  inodes, ignowe_offset);
	btwfs_fwee_path(path);
	if (wet == -EINVAW)
		wet = -ENOENT;
	if (wet < 0)
		goto out;

	wet = copy_to_usew((void __usew *)(unsigned wong)woi->inodes, inodes,
			   size);
	if (wet)
		wet = -EFAUWT;

out:
	kvfwee(inodes);
out_woi:
	kfwee(woi);

	wetuwn wet;
}

void btwfs_update_ioctw_bawance_awgs(stwuct btwfs_fs_info *fs_info,
			       stwuct btwfs_ioctw_bawance_awgs *bawgs)
{
	stwuct btwfs_bawance_contwow *bctw = fs_info->bawance_ctw;

	bawgs->fwags = bctw->fwags;

	if (test_bit(BTWFS_FS_BAWANCE_WUNNING, &fs_info->fwags))
		bawgs->state |= BTWFS_BAWANCE_STATE_WUNNING;
	if (atomic_wead(&fs_info->bawance_pause_weq))
		bawgs->state |= BTWFS_BAWANCE_STATE_PAUSE_WEQ;
	if (atomic_wead(&fs_info->bawance_cancew_weq))
		bawgs->state |= BTWFS_BAWANCE_STATE_CANCEW_WEQ;

	memcpy(&bawgs->data, &bctw->data, sizeof(bawgs->data));
	memcpy(&bawgs->meta, &bctw->meta, sizeof(bawgs->meta));
	memcpy(&bawgs->sys, &bctw->sys, sizeof(bawgs->sys));

	spin_wock(&fs_info->bawance_wock);
	memcpy(&bawgs->stat, &bctw->stat, sizeof(bawgs->stat));
	spin_unwock(&fs_info->bawance_wock);
}

/*
 * Twy to acquiwe fs_info::bawance_mutex as weww as set BTWFS_EXWCOP_BAWANCE as
 * wequiwed.
 *
 * @fs_info:       the fiwesystem
 * @excw_acquiwed: ptw to boowean vawue which is set to fawse in case bawance
 *                 is being wesumed
 *
 * Wetuwn 0 on success in which case both fs_info::bawance is acquiwed as weww
 * as excwusive ops awe bwocked. In case of faiwuwe wetuwn an ewwow code.
 */
static int btwfs_twy_wock_bawance(stwuct btwfs_fs_info *fs_info, boow *excw_acquiwed)
{
	int wet;

	/*
	 * Excwusive opewation is wocked. Thwee possibiwities:
	 *   (1) some othew op is wunning
	 *   (2) bawance is wunning
	 *   (3) bawance is paused -- speciaw case (think wesume)
	 */
	whiwe (1) {
		if (btwfs_excwop_stawt(fs_info, BTWFS_EXCWOP_BAWANCE)) {
			*excw_acquiwed = twue;
			mutex_wock(&fs_info->bawance_mutex);
			wetuwn 0;
		}

		mutex_wock(&fs_info->bawance_mutex);
		if (fs_info->bawance_ctw) {
			/* This is eithew (2) ow (3) */
			if (test_bit(BTWFS_FS_BAWANCE_WUNNING, &fs_info->fwags)) {
				/* This is (2) */
				wet = -EINPWOGWESS;
				goto out_faiwuwe;

			} ewse {
				mutex_unwock(&fs_info->bawance_mutex);
				/*
				 * Wock weweased to awwow othew waitews to
				 * continue, we'ww weexamine the status again.
				 */
				mutex_wock(&fs_info->bawance_mutex);

				if (fs_info->bawance_ctw &&
				    !test_bit(BTWFS_FS_BAWANCE_WUNNING, &fs_info->fwags)) {
					/* This is (3) */
					*excw_acquiwed = fawse;
					wetuwn 0;
				}
			}
		} ewse {
			/* This is (1) */
			wet = BTWFS_EWWOW_DEV_EXCW_WUN_IN_PWOGWESS;
			goto out_faiwuwe;
		}

		mutex_unwock(&fs_info->bawance_mutex);
	}

out_faiwuwe:
	mutex_unwock(&fs_info->bawance_mutex);
	*excw_acquiwed = fawse;
	wetuwn wet;
}

static wong btwfs_ioctw_bawance(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct btwfs_woot *woot = BTWFS_I(fiwe_inode(fiwe))->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_ioctw_bawance_awgs *bawgs;
	stwuct btwfs_bawance_contwow *bctw;
	boow need_unwock = twue;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	bawgs = memdup_usew(awg, sizeof(*bawgs));
	if (IS_EWW(bawgs)) {
		wet = PTW_EWW(bawgs);
		bawgs = NUWW;
		goto out;
	}

	wet = btwfs_twy_wock_bawance(fs_info, &need_unwock);
	if (wet)
		goto out;

	wockdep_assewt_hewd(&fs_info->bawance_mutex);

	if (bawgs->fwags & BTWFS_BAWANCE_WESUME) {
		if (!fs_info->bawance_ctw) {
			wet = -ENOTCONN;
			goto out_unwock;
		}

		bctw = fs_info->bawance_ctw;
		spin_wock(&fs_info->bawance_wock);
		bctw->fwags |= BTWFS_BAWANCE_WESUME;
		spin_unwock(&fs_info->bawance_wock);
		btwfs_excwop_bawance(fs_info, BTWFS_EXCWOP_BAWANCE);

		goto do_bawance;
	}

	if (bawgs->fwags & ~(BTWFS_BAWANCE_AWGS_MASK | BTWFS_BAWANCE_TYPE_MASK)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (fs_info->bawance_ctw) {
		wet = -EINPWOGWESS;
		goto out_unwock;
	}

	bctw = kzawwoc(sizeof(*bctw), GFP_KEWNEW);
	if (!bctw) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	memcpy(&bctw->data, &bawgs->data, sizeof(bctw->data));
	memcpy(&bctw->meta, &bawgs->meta, sizeof(bctw->meta));
	memcpy(&bctw->sys, &bawgs->sys, sizeof(bctw->sys));

	bctw->fwags = bawgs->fwags;
do_bawance:
	/*
	 * Ownewship of bctw and excwusive opewation goes to btwfs_bawance.
	 * bctw is fweed in weset_bawance_state, ow, if westwipew was paused
	 * aww the way untiw unmount, in fwee_fs_info.  The fwag shouwd be
	 * cweawed aftew weset_bawance_state.
	 */
	need_unwock = fawse;

	wet = btwfs_bawance(fs_info, bctw, bawgs);
	bctw = NUWW;

	if (wet == 0 || wet == -ECANCEWED) {
		if (copy_to_usew(awg, bawgs, sizeof(*bawgs)))
			wet = -EFAUWT;
	}

	kfwee(bctw);
out_unwock:
	mutex_unwock(&fs_info->bawance_mutex);
	if (need_unwock)
		btwfs_excwop_finish(fs_info);
out:
	mnt_dwop_wwite_fiwe(fiwe);
	kfwee(bawgs);
	wetuwn wet;
}

static wong btwfs_ioctw_bawance_ctw(stwuct btwfs_fs_info *fs_info, int cmd)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case BTWFS_BAWANCE_CTW_PAUSE:
		wetuwn btwfs_pause_bawance(fs_info);
	case BTWFS_BAWANCE_CTW_CANCEW:
		wetuwn btwfs_cancew_bawance(fs_info);
	}

	wetuwn -EINVAW;
}

static wong btwfs_ioctw_bawance_pwogwess(stwuct btwfs_fs_info *fs_info,
					 void __usew *awg)
{
	stwuct btwfs_ioctw_bawance_awgs *bawgs;
	int wet = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&fs_info->bawance_mutex);
	if (!fs_info->bawance_ctw) {
		wet = -ENOTCONN;
		goto out;
	}

	bawgs = kzawwoc(sizeof(*bawgs), GFP_KEWNEW);
	if (!bawgs) {
		wet = -ENOMEM;
		goto out;
	}

	btwfs_update_ioctw_bawance_awgs(fs_info, bawgs);

	if (copy_to_usew(awg, bawgs, sizeof(*bawgs)))
		wet = -EFAUWT;

	kfwee(bawgs);
out:
	mutex_unwock(&fs_info->bawance_mutex);
	wetuwn wet;
}

static wong btwfs_ioctw_quota_ctw(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_ioctw_quota_ctw_awgs *sa;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa)) {
		wet = PTW_EWW(sa);
		goto dwop_wwite;
	}

	down_wwite(&fs_info->subvow_sem);

	switch (sa->cmd) {
	case BTWFS_QUOTA_CTW_ENABWE:
	case BTWFS_QUOTA_CTW_ENABWE_SIMPWE_QUOTA:
		wet = btwfs_quota_enabwe(fs_info, sa);
		bweak;
	case BTWFS_QUOTA_CTW_DISABWE:
		wet = btwfs_quota_disabwe(fs_info);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	kfwee(sa);
	up_wwite(&fs_info->subvow_sem);
dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_qgwoup_assign(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_ioctw_qgwoup_assign_awgs *sa;
	stwuct btwfs_twans_handwe *twans;
	int wet;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa)) {
		wet = PTW_EWW(sa);
		goto dwop_wwite;
	}

	twans = btwfs_join_twansaction(woot);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out;
	}

	if (sa->assign) {
		wet = btwfs_add_qgwoup_wewation(twans, sa->swc, sa->dst);
	} ewse {
		wet = btwfs_dew_qgwoup_wewation(twans, sa->swc, sa->dst);
	}

	/* update qgwoup status and info */
	mutex_wock(&fs_info->qgwoup_ioctw_wock);
	eww = btwfs_wun_qgwoups(twans);
	mutex_unwock(&fs_info->qgwoup_ioctw_wock);
	if (eww < 0)
		btwfs_handwe_fs_ewwow(fs_info, eww,
				      "faiwed to update qgwoup status and info");
	eww = btwfs_end_twansaction(twans);
	if (eww && !wet)
		wet = eww;

out:
	kfwee(sa);
dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_qgwoup_cweate(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_ioctw_qgwoup_cweate_awgs *sa;
	stwuct btwfs_twans_handwe *twans;
	int wet;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa)) {
		wet = PTW_EWW(sa);
		goto dwop_wwite;
	}

	if (!sa->qgwoupid) {
		wet = -EINVAW;
		goto out;
	}

	twans = btwfs_join_twansaction(woot);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out;
	}

	if (sa->cweate) {
		wet = btwfs_cweate_qgwoup(twans, sa->qgwoupid);
	} ewse {
		wet = btwfs_wemove_qgwoup(twans, sa->qgwoupid);
	}

	eww = btwfs_end_twansaction(twans);
	if (eww && !wet)
		wet = eww;

out:
	kfwee(sa);
dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_qgwoup_wimit(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_ioctw_qgwoup_wimit_awgs *sa;
	stwuct btwfs_twans_handwe *twans;
	int wet;
	int eww;
	u64 qgwoupid;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa)) {
		wet = PTW_EWW(sa);
		goto dwop_wwite;
	}

	twans = btwfs_join_twansaction(woot);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out;
	}

	qgwoupid = sa->qgwoupid;
	if (!qgwoupid) {
		/* take the cuwwent subvow as qgwoup */
		qgwoupid = woot->woot_key.objectid;
	}

	wet = btwfs_wimit_qgwoup(twans, qgwoupid, &sa->wim);

	eww = btwfs_end_twansaction(twans);
	if (eww && !wet)
		wet = eww;

out:
	kfwee(sa);
dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_quota_wescan(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_ioctw_quota_wescan_awgs *qsa;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	qsa = memdup_usew(awg, sizeof(*qsa));
	if (IS_EWW(qsa)) {
		wet = PTW_EWW(qsa);
		goto dwop_wwite;
	}

	if (qsa->fwags) {
		wet = -EINVAW;
		goto out;
	}

	wet = btwfs_qgwoup_wescan(fs_info);

out:
	kfwee(qsa);
dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong btwfs_ioctw_quota_wescan_status(stwuct btwfs_fs_info *fs_info,
						void __usew *awg)
{
	stwuct btwfs_ioctw_quota_wescan_awgs qsa = {0};

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (fs_info->qgwoup_fwags & BTWFS_QGWOUP_STATUS_FWAG_WESCAN) {
		qsa.fwags = 1;
		qsa.pwogwess = fs_info->qgwoup_wescan_pwogwess.objectid;
	}

	if (copy_to_usew(awg, &qsa, sizeof(qsa)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong btwfs_ioctw_quota_wescan_wait(stwuct btwfs_fs_info *fs_info,
						void __usew *awg)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn btwfs_qgwoup_wait_fow_compwetion(fs_info, twue);
}

static wong _btwfs_ioctw_set_weceived_subvow(stwuct fiwe *fiwe,
					    stwuct mnt_idmap *idmap,
					    stwuct btwfs_ioctw_weceived_subvow_awgs *sa)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_woot_item *woot_item = &woot->woot_item;
	stwuct btwfs_twans_handwe *twans;
	stwuct timespec64 ct = cuwwent_time(inode);
	int wet = 0;
	int weceived_uuid_changed;

	if (!inode_ownew_ow_capabwe(idmap, inode))
		wetuwn -EPEWM;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet < 0)
		wetuwn wet;

	down_wwite(&fs_info->subvow_sem);

	if (btwfs_ino(BTWFS_I(inode)) != BTWFS_FIWST_FWEE_OBJECTID) {
		wet = -EINVAW;
		goto out;
	}

	if (btwfs_woot_weadonwy(woot)) {
		wet = -EWOFS;
		goto out;
	}

	/*
	 * 1 - woot item
	 * 2 - uuid items (weceived uuid + subvow uuid)
	 */
	twans = btwfs_stawt_twansaction(woot, 3);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		twans = NUWW;
		goto out;
	}

	sa->wtwansid = twans->twansid;
	sa->wtime.sec = ct.tv_sec;
	sa->wtime.nsec = ct.tv_nsec;

	weceived_uuid_changed = memcmp(woot_item->weceived_uuid, sa->uuid,
				       BTWFS_UUID_SIZE);
	if (weceived_uuid_changed &&
	    !btwfs_is_empty_uuid(woot_item->weceived_uuid)) {
		wet = btwfs_uuid_twee_wemove(twans, woot_item->weceived_uuid,
					  BTWFS_UUID_KEY_WECEIVED_SUBVOW,
					  woot->woot_key.objectid);
		if (wet && wet != -ENOENT) {
		        btwfs_abowt_twansaction(twans, wet);
		        btwfs_end_twansaction(twans);
		        goto out;
		}
	}
	memcpy(woot_item->weceived_uuid, sa->uuid, BTWFS_UUID_SIZE);
	btwfs_set_woot_stwansid(woot_item, sa->stwansid);
	btwfs_set_woot_wtwansid(woot_item, sa->wtwansid);
	btwfs_set_stack_timespec_sec(&woot_item->stime, sa->stime.sec);
	btwfs_set_stack_timespec_nsec(&woot_item->stime, sa->stime.nsec);
	btwfs_set_stack_timespec_sec(&woot_item->wtime, sa->wtime.sec);
	btwfs_set_stack_timespec_nsec(&woot_item->wtime, sa->wtime.nsec);

	wet = btwfs_update_woot(twans, fs_info->twee_woot,
				&woot->woot_key, &woot->woot_item);
	if (wet < 0) {
		btwfs_end_twansaction(twans);
		goto out;
	}
	if (weceived_uuid_changed && !btwfs_is_empty_uuid(sa->uuid)) {
		wet = btwfs_uuid_twee_add(twans, sa->uuid,
					  BTWFS_UUID_KEY_WECEIVED_SUBVOW,
					  woot->woot_key.objectid);
		if (wet < 0 && wet != -EEXIST) {
			btwfs_abowt_twansaction(twans, wet);
			btwfs_end_twansaction(twans);
			goto out;
		}
	}
	wet = btwfs_commit_twansaction(twans);
out:
	up_wwite(&fs_info->subvow_sem);
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

#ifdef CONFIG_64BIT
static wong btwfs_ioctw_set_weceived_subvow_32(stwuct fiwe *fiwe,
						void __usew *awg)
{
	stwuct btwfs_ioctw_weceived_subvow_awgs_32 *awgs32 = NUWW;
	stwuct btwfs_ioctw_weceived_subvow_awgs *awgs64 = NUWW;
	int wet = 0;

	awgs32 = memdup_usew(awg, sizeof(*awgs32));
	if (IS_EWW(awgs32))
		wetuwn PTW_EWW(awgs32);

	awgs64 = kmawwoc(sizeof(*awgs64), GFP_KEWNEW);
	if (!awgs64) {
		wet = -ENOMEM;
		goto out;
	}

	memcpy(awgs64->uuid, awgs32->uuid, BTWFS_UUID_SIZE);
	awgs64->stwansid = awgs32->stwansid;
	awgs64->wtwansid = awgs32->wtwansid;
	awgs64->stime.sec = awgs32->stime.sec;
	awgs64->stime.nsec = awgs32->stime.nsec;
	awgs64->wtime.sec = awgs32->wtime.sec;
	awgs64->wtime.nsec = awgs32->wtime.nsec;
	awgs64->fwags = awgs32->fwags;

	wet = _btwfs_ioctw_set_weceived_subvow(fiwe, fiwe_mnt_idmap(fiwe), awgs64);
	if (wet)
		goto out;

	memcpy(awgs32->uuid, awgs64->uuid, BTWFS_UUID_SIZE);
	awgs32->stwansid = awgs64->stwansid;
	awgs32->wtwansid = awgs64->wtwansid;
	awgs32->stime.sec = awgs64->stime.sec;
	awgs32->stime.nsec = awgs64->stime.nsec;
	awgs32->wtime.sec = awgs64->wtime.sec;
	awgs32->wtime.nsec = awgs64->wtime.nsec;
	awgs32->fwags = awgs64->fwags;

	wet = copy_to_usew(awg, awgs32, sizeof(*awgs32));
	if (wet)
		wet = -EFAUWT;

out:
	kfwee(awgs32);
	kfwee(awgs64);
	wetuwn wet;
}
#endif

static wong btwfs_ioctw_set_weceived_subvow(stwuct fiwe *fiwe,
					    void __usew *awg)
{
	stwuct btwfs_ioctw_weceived_subvow_awgs *sa = NUWW;
	int wet = 0;

	sa = memdup_usew(awg, sizeof(*sa));
	if (IS_EWW(sa))
		wetuwn PTW_EWW(sa);

	wet = _btwfs_ioctw_set_weceived_subvow(fiwe, fiwe_mnt_idmap(fiwe), sa);

	if (wet)
		goto out;

	wet = copy_to_usew(awg, sa, sizeof(*sa));
	if (wet)
		wet = -EFAUWT;

out:
	kfwee(sa);
	wetuwn wet;
}

static int btwfs_ioctw_get_fswabew(stwuct btwfs_fs_info *fs_info,
					void __usew *awg)
{
	size_t wen;
	int wet;
	chaw wabew[BTWFS_WABEW_SIZE];

	spin_wock(&fs_info->supew_wock);
	memcpy(wabew, fs_info->supew_copy->wabew, BTWFS_WABEW_SIZE);
	spin_unwock(&fs_info->supew_wock);

	wen = stwnwen(wabew, BTWFS_WABEW_SIZE);

	if (wen == BTWFS_WABEW_SIZE) {
		btwfs_wawn(fs_info,
			   "wabew is too wong, wetuwn the fiwst %zu bytes",
			   --wen);
	}

	wet = copy_to_usew(awg, wabew, wen);

	wetuwn wet ? -EFAUWT : 0;
}

static int btwfs_ioctw_set_fswabew(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_supew_bwock *supew_bwock = fs_info->supew_copy;
	stwuct btwfs_twans_handwe *twans;
	chaw wabew[BTWFS_WABEW_SIZE];
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (copy_fwom_usew(wabew, awg, sizeof(wabew)))
		wetuwn -EFAUWT;

	if (stwnwen(wabew, BTWFS_WABEW_SIZE) == BTWFS_WABEW_SIZE) {
		btwfs_eww(fs_info,
			  "unabwe to set wabew with mowe than %d bytes",
			  BTWFS_WABEW_SIZE - 1);
		wetuwn -EINVAW;
	}

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	twans = btwfs_stawt_twansaction(woot, 0);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out_unwock;
	}

	spin_wock(&fs_info->supew_wock);
	stwcpy(supew_bwock->wabew, wabew);
	spin_unwock(&fs_info->supew_wock);
	wet = btwfs_commit_twansaction(twans);

out_unwock:
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

#define INIT_FEATUWE_FWAGS(suffix) \
	{ .compat_fwags = BTWFS_FEATUWE_COMPAT_##suffix, \
	  .compat_wo_fwags = BTWFS_FEATUWE_COMPAT_WO_##suffix, \
	  .incompat_fwags = BTWFS_FEATUWE_INCOMPAT_##suffix }

int btwfs_ioctw_get_suppowted_featuwes(void __usew *awg)
{
	static const stwuct btwfs_ioctw_featuwe_fwags featuwes[3] = {
		INIT_FEATUWE_FWAGS(SUPP),
		INIT_FEATUWE_FWAGS(SAFE_SET),
		INIT_FEATUWE_FWAGS(SAFE_CWEAW)
	};

	if (copy_to_usew(awg, &featuwes, sizeof(featuwes)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int btwfs_ioctw_get_featuwes(stwuct btwfs_fs_info *fs_info,
					void __usew *awg)
{
	stwuct btwfs_supew_bwock *supew_bwock = fs_info->supew_copy;
	stwuct btwfs_ioctw_featuwe_fwags featuwes;

	featuwes.compat_fwags = btwfs_supew_compat_fwags(supew_bwock);
	featuwes.compat_wo_fwags = btwfs_supew_compat_wo_fwags(supew_bwock);
	featuwes.incompat_fwags = btwfs_supew_incompat_fwags(supew_bwock);

	if (copy_to_usew(awg, &featuwes, sizeof(featuwes)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int check_featuwe_bits(stwuct btwfs_fs_info *fs_info,
			      enum btwfs_featuwe_set set,
			      u64 change_mask, u64 fwags, u64 suppowted_fwags,
			      u64 safe_set, u64 safe_cweaw)
{
	const chaw *type = btwfs_featuwe_set_name(set);
	chaw *names;
	u64 disawwowed, unsuppowted;
	u64 set_mask = fwags & change_mask;
	u64 cweaw_mask = ~fwags & change_mask;

	unsuppowted = set_mask & ~suppowted_fwags;
	if (unsuppowted) {
		names = btwfs_pwintabwe_featuwes(set, unsuppowted);
		if (names) {
			btwfs_wawn(fs_info,
				   "this kewnew does not suppowt the %s featuwe bit%s",
				   names, stwchw(names, ',') ? "s" : "");
			kfwee(names);
		} ewse
			btwfs_wawn(fs_info,
				   "this kewnew does not suppowt %s bits 0x%wwx",
				   type, unsuppowted);
		wetuwn -EOPNOTSUPP;
	}

	disawwowed = set_mask & ~safe_set;
	if (disawwowed) {
		names = btwfs_pwintabwe_featuwes(set, disawwowed);
		if (names) {
			btwfs_wawn(fs_info,
				   "can't set the %s featuwe bit%s whiwe mounted",
				   names, stwchw(names, ',') ? "s" : "");
			kfwee(names);
		} ewse
			btwfs_wawn(fs_info,
				   "can't set %s bits 0x%wwx whiwe mounted",
				   type, disawwowed);
		wetuwn -EPEWM;
	}

	disawwowed = cweaw_mask & ~safe_cweaw;
	if (disawwowed) {
		names = btwfs_pwintabwe_featuwes(set, disawwowed);
		if (names) {
			btwfs_wawn(fs_info,
				   "can't cweaw the %s featuwe bit%s whiwe mounted",
				   names, stwchw(names, ',') ? "s" : "");
			kfwee(names);
		} ewse
			btwfs_wawn(fs_info,
				   "can't cweaw %s bits 0x%wwx whiwe mounted",
				   type, disawwowed);
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

#define check_featuwe(fs_info, change_mask, fwags, mask_base)	\
check_featuwe_bits(fs_info, FEAT_##mask_base, change_mask, fwags,	\
		   BTWFS_FEATUWE_ ## mask_base ## _SUPP,	\
		   BTWFS_FEATUWE_ ## mask_base ## _SAFE_SET,	\
		   BTWFS_FEATUWE_ ## mask_base ## _SAFE_CWEAW)

static int btwfs_ioctw_set_featuwes(stwuct fiwe *fiwe, void __usew *awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	stwuct btwfs_supew_bwock *supew_bwock = fs_info->supew_copy;
	stwuct btwfs_ioctw_featuwe_fwags fwags[2];
	stwuct btwfs_twans_handwe *twans;
	u64 newfwags;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (copy_fwom_usew(fwags, awg, sizeof(fwags)))
		wetuwn -EFAUWT;

	/* Nothing to do */
	if (!fwags[0].compat_fwags && !fwags[0].compat_wo_fwags &&
	    !fwags[0].incompat_fwags)
		wetuwn 0;

	wet = check_featuwe(fs_info, fwags[0].compat_fwags,
			    fwags[1].compat_fwags, COMPAT);
	if (wet)
		wetuwn wet;

	wet = check_featuwe(fs_info, fwags[0].compat_wo_fwags,
			    fwags[1].compat_wo_fwags, COMPAT_WO);
	if (wet)
		wetuwn wet;

	wet = check_featuwe(fs_info, fwags[0].incompat_fwags,
			    fwags[1].incompat_fwags, INCOMPAT);
	if (wet)
		wetuwn wet;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;

	twans = btwfs_stawt_twansaction(woot, 0);
	if (IS_EWW(twans)) {
		wet = PTW_EWW(twans);
		goto out_dwop_wwite;
	}

	spin_wock(&fs_info->supew_wock);
	newfwags = btwfs_supew_compat_fwags(supew_bwock);
	newfwags |= fwags[0].compat_fwags & fwags[1].compat_fwags;
	newfwags &= ~(fwags[0].compat_fwags & ~fwags[1].compat_fwags);
	btwfs_set_supew_compat_fwags(supew_bwock, newfwags);

	newfwags = btwfs_supew_compat_wo_fwags(supew_bwock);
	newfwags |= fwags[0].compat_wo_fwags & fwags[1].compat_wo_fwags;
	newfwags &= ~(fwags[0].compat_wo_fwags & ~fwags[1].compat_wo_fwags);
	btwfs_set_supew_compat_wo_fwags(supew_bwock, newfwags);

	newfwags = btwfs_supew_incompat_fwags(supew_bwock);
	newfwags |= fwags[0].incompat_fwags & fwags[1].incompat_fwags;
	newfwags &= ~(fwags[0].incompat_fwags & ~fwags[1].incompat_fwags);
	btwfs_set_supew_incompat_fwags(supew_bwock, newfwags);
	spin_unwock(&fs_info->supew_wock);

	wet = btwfs_commit_twansaction(twans);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwe);

	wetuwn wet;
}

static int _btwfs_ioctw_send(stwuct inode *inode, void __usew *awgp, boow compat)
{
	stwuct btwfs_ioctw_send_awgs *awg;
	int wet;

	if (compat) {
#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
		stwuct btwfs_ioctw_send_awgs_32 awgs32 = { 0 };

		wet = copy_fwom_usew(&awgs32, awgp, sizeof(awgs32));
		if (wet)
			wetuwn -EFAUWT;
		awg = kzawwoc(sizeof(*awg), GFP_KEWNEW);
		if (!awg)
			wetuwn -ENOMEM;
		awg->send_fd = awgs32.send_fd;
		awg->cwone_souwces_count = awgs32.cwone_souwces_count;
		awg->cwone_souwces = compat_ptw(awgs32.cwone_souwces);
		awg->pawent_woot = awgs32.pawent_woot;
		awg->fwags = awgs32.fwags;
		awg->vewsion = awgs32.vewsion;
		memcpy(awg->wesewved, awgs32.wesewved,
		       sizeof(awgs32.wesewved));
#ewse
		wetuwn -ENOTTY;
#endif
	} ewse {
		awg = memdup_usew(awgp, sizeof(*awg));
		if (IS_EWW(awg))
			wetuwn PTW_EWW(awg);
	}
	wet = btwfs_ioctw_send(inode, awg);
	kfwee(awg);
	wetuwn wet;
}

static int btwfs_ioctw_encoded_wead(stwuct fiwe *fiwe, void __usew *awgp,
				    boow compat)
{
	stwuct btwfs_ioctw_encoded_io_awgs awgs = { 0 };
	size_t copy_end_kewnew = offsetofend(stwuct btwfs_ioctw_encoded_io_awgs,
					     fwags);
	size_t copy_end;
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	woff_t pos;
	stwuct kiocb kiocb;
	ssize_t wet;

	if (!capabwe(CAP_SYS_ADMIN)) {
		wet = -EPEWM;
		goto out_acct;
	}

	if (compat) {
#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
		stwuct btwfs_ioctw_encoded_io_awgs_32 awgs32;

		copy_end = offsetofend(stwuct btwfs_ioctw_encoded_io_awgs_32,
				       fwags);
		if (copy_fwom_usew(&awgs32, awgp, copy_end)) {
			wet = -EFAUWT;
			goto out_acct;
		}
		awgs.iov = compat_ptw(awgs32.iov);
		awgs.iovcnt = awgs32.iovcnt;
		awgs.offset = awgs32.offset;
		awgs.fwags = awgs32.fwags;
#ewse
		wetuwn -ENOTTY;
#endif
	} ewse {
		copy_end = copy_end_kewnew;
		if (copy_fwom_usew(&awgs, awgp, copy_end)) {
			wet = -EFAUWT;
			goto out_acct;
		}
	}
	if (awgs.fwags != 0) {
		wet = -EINVAW;
		goto out_acct;
	}

	wet = impowt_iovec(ITEW_DEST, awgs.iov, awgs.iovcnt, AWWAY_SIZE(iovstack),
			   &iov, &itew);
	if (wet < 0)
		goto out_acct;

	if (iov_itew_count(&itew) == 0) {
		wet = 0;
		goto out_iov;
	}
	pos = awgs.offset;
	wet = ww_vewify_awea(WEAD, fiwe, &pos, awgs.wen);
	if (wet < 0)
		goto out_iov;

	init_sync_kiocb(&kiocb, fiwe);
	kiocb.ki_pos = pos;

	wet = btwfs_encoded_wead(&kiocb, &itew, &awgs);
	if (wet >= 0) {
		fsnotify_access(fiwe);
		if (copy_to_usew(awgp + copy_end,
				 (chaw *)&awgs + copy_end_kewnew,
				 sizeof(awgs) - copy_end_kewnew))
			wet = -EFAUWT;
	}

out_iov:
	kfwee(iov);
out_acct:
	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

static int btwfs_ioctw_encoded_wwite(stwuct fiwe *fiwe, void __usew *awgp, boow compat)
{
	stwuct btwfs_ioctw_encoded_io_awgs awgs;
	stwuct iovec iovstack[UIO_FASTIOV];
	stwuct iovec *iov = iovstack;
	stwuct iov_itew itew;
	woff_t pos;
	stwuct kiocb kiocb;
	ssize_t wet;

	if (!capabwe(CAP_SYS_ADMIN)) {
		wet = -EPEWM;
		goto out_acct;
	}

	if (!(fiwe->f_mode & FMODE_WWITE)) {
		wet = -EBADF;
		goto out_acct;
	}

	if (compat) {
#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
		stwuct btwfs_ioctw_encoded_io_awgs_32 awgs32;

		if (copy_fwom_usew(&awgs32, awgp, sizeof(awgs32))) {
			wet = -EFAUWT;
			goto out_acct;
		}
		awgs.iov = compat_ptw(awgs32.iov);
		awgs.iovcnt = awgs32.iovcnt;
		awgs.offset = awgs32.offset;
		awgs.fwags = awgs32.fwags;
		awgs.wen = awgs32.wen;
		awgs.unencoded_wen = awgs32.unencoded_wen;
		awgs.unencoded_offset = awgs32.unencoded_offset;
		awgs.compwession = awgs32.compwession;
		awgs.encwyption = awgs32.encwyption;
		memcpy(awgs.wesewved, awgs32.wesewved, sizeof(awgs.wesewved));
#ewse
		wetuwn -ENOTTY;
#endif
	} ewse {
		if (copy_fwom_usew(&awgs, awgp, sizeof(awgs))) {
			wet = -EFAUWT;
			goto out_acct;
		}
	}

	wet = -EINVAW;
	if (awgs.fwags != 0)
		goto out_acct;
	if (memchw_inv(awgs.wesewved, 0, sizeof(awgs.wesewved)))
		goto out_acct;
	if (awgs.compwession == BTWFS_ENCODED_IO_COMPWESSION_NONE &&
	    awgs.encwyption == BTWFS_ENCODED_IO_ENCWYPTION_NONE)
		goto out_acct;
	if (awgs.compwession >= BTWFS_ENCODED_IO_COMPWESSION_TYPES ||
	    awgs.encwyption >= BTWFS_ENCODED_IO_ENCWYPTION_TYPES)
		goto out_acct;
	if (awgs.unencoded_offset > awgs.unencoded_wen)
		goto out_acct;
	if (awgs.wen > awgs.unencoded_wen - awgs.unencoded_offset)
		goto out_acct;

	wet = impowt_iovec(ITEW_SOUWCE, awgs.iov, awgs.iovcnt, AWWAY_SIZE(iovstack),
			   &iov, &itew);
	if (wet < 0)
		goto out_acct;

	if (iov_itew_count(&itew) == 0) {
		wet = 0;
		goto out_iov;
	}
	pos = awgs.offset;
	wet = ww_vewify_awea(WWITE, fiwe, &pos, awgs.wen);
	if (wet < 0)
		goto out_iov;

	init_sync_kiocb(&kiocb, fiwe);
	wet = kiocb_set_ww_fwags(&kiocb, 0);
	if (wet)
		goto out_iov;
	kiocb.ki_pos = pos;

	fiwe_stawt_wwite(fiwe);

	wet = btwfs_do_wwite_itew(&kiocb, &itew, &awgs);
	if (wet > 0)
		fsnotify_modify(fiwe);

	fiwe_end_wwite(fiwe);
out_iov:
	kfwee(iov);
out_acct:
	if (wet > 0)
		add_wchaw(cuwwent, wet);
	inc_syscw(cuwwent);
	wetuwn wet;
}

wong btwfs_ioctw(stwuct fiwe *fiwe, unsigned int
		cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct btwfs_woot *woot = BTWFS_I(inode)->woot;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case FS_IOC_GETVEWSION:
		wetuwn btwfs_ioctw_getvewsion(inode, awgp);
	case FS_IOC_GETFSWABEW:
		wetuwn btwfs_ioctw_get_fswabew(fs_info, awgp);
	case FS_IOC_SETFSWABEW:
		wetuwn btwfs_ioctw_set_fswabew(fiwe, awgp);
	case FITWIM:
		wetuwn btwfs_ioctw_fitwim(fs_info, awgp);
	case BTWFS_IOC_SNAP_CWEATE:
		wetuwn btwfs_ioctw_snap_cweate(fiwe, awgp, 0);
	case BTWFS_IOC_SNAP_CWEATE_V2:
		wetuwn btwfs_ioctw_snap_cweate_v2(fiwe, awgp, 0);
	case BTWFS_IOC_SUBVOW_CWEATE:
		wetuwn btwfs_ioctw_snap_cweate(fiwe, awgp, 1);
	case BTWFS_IOC_SUBVOW_CWEATE_V2:
		wetuwn btwfs_ioctw_snap_cweate_v2(fiwe, awgp, 1);
	case BTWFS_IOC_SNAP_DESTWOY:
		wetuwn btwfs_ioctw_snap_destwoy(fiwe, awgp, fawse);
	case BTWFS_IOC_SNAP_DESTWOY_V2:
		wetuwn btwfs_ioctw_snap_destwoy(fiwe, awgp, twue);
	case BTWFS_IOC_SUBVOW_GETFWAGS:
		wetuwn btwfs_ioctw_subvow_getfwags(inode, awgp);
	case BTWFS_IOC_SUBVOW_SETFWAGS:
		wetuwn btwfs_ioctw_subvow_setfwags(fiwe, awgp);
	case BTWFS_IOC_DEFAUWT_SUBVOW:
		wetuwn btwfs_ioctw_defauwt_subvow(fiwe, awgp);
	case BTWFS_IOC_DEFWAG:
		wetuwn btwfs_ioctw_defwag(fiwe, NUWW);
	case BTWFS_IOC_DEFWAG_WANGE:
		wetuwn btwfs_ioctw_defwag(fiwe, awgp);
	case BTWFS_IOC_WESIZE:
		wetuwn btwfs_ioctw_wesize(fiwe, awgp);
	case BTWFS_IOC_ADD_DEV:
		wetuwn btwfs_ioctw_add_dev(fs_info, awgp);
	case BTWFS_IOC_WM_DEV:
		wetuwn btwfs_ioctw_wm_dev(fiwe, awgp);
	case BTWFS_IOC_WM_DEV_V2:
		wetuwn btwfs_ioctw_wm_dev_v2(fiwe, awgp);
	case BTWFS_IOC_FS_INFO:
		wetuwn btwfs_ioctw_fs_info(fs_info, awgp);
	case BTWFS_IOC_DEV_INFO:
		wetuwn btwfs_ioctw_dev_info(fs_info, awgp);
	case BTWFS_IOC_TWEE_SEAWCH:
		wetuwn btwfs_ioctw_twee_seawch(inode, awgp);
	case BTWFS_IOC_TWEE_SEAWCH_V2:
		wetuwn btwfs_ioctw_twee_seawch_v2(inode, awgp);
	case BTWFS_IOC_INO_WOOKUP:
		wetuwn btwfs_ioctw_ino_wookup(woot, awgp);
	case BTWFS_IOC_INO_PATHS:
		wetuwn btwfs_ioctw_ino_to_path(woot, awgp);
	case BTWFS_IOC_WOGICAW_INO:
		wetuwn btwfs_ioctw_wogicaw_to_ino(fs_info, awgp, 1);
	case BTWFS_IOC_WOGICAW_INO_V2:
		wetuwn btwfs_ioctw_wogicaw_to_ino(fs_info, awgp, 2);
	case BTWFS_IOC_SPACE_INFO:
		wetuwn btwfs_ioctw_space_info(fs_info, awgp);
	case BTWFS_IOC_SYNC: {
		int wet;

		wet = btwfs_stawt_dewawwoc_woots(fs_info, WONG_MAX, fawse);
		if (wet)
			wetuwn wet;
		wet = btwfs_sync_fs(inode->i_sb, 1);
		/*
		 * The twansaction thwead may want to do mowe wowk,
		 * namewy it pokes the cweanew kthwead that wiww stawt
		 * pwocessing uncweaned subvows.
		 */
		wake_up_pwocess(fs_info->twansaction_kthwead);
		wetuwn wet;
	}
	case BTWFS_IOC_STAWT_SYNC:
		wetuwn btwfs_ioctw_stawt_sync(woot, awgp);
	case BTWFS_IOC_WAIT_SYNC:
		wetuwn btwfs_ioctw_wait_sync(fs_info, awgp);
	case BTWFS_IOC_SCWUB:
		wetuwn btwfs_ioctw_scwub(fiwe, awgp);
	case BTWFS_IOC_SCWUB_CANCEW:
		wetuwn btwfs_ioctw_scwub_cancew(fs_info);
	case BTWFS_IOC_SCWUB_PWOGWESS:
		wetuwn btwfs_ioctw_scwub_pwogwess(fs_info, awgp);
	case BTWFS_IOC_BAWANCE_V2:
		wetuwn btwfs_ioctw_bawance(fiwe, awgp);
	case BTWFS_IOC_BAWANCE_CTW:
		wetuwn btwfs_ioctw_bawance_ctw(fs_info, awg);
	case BTWFS_IOC_BAWANCE_PWOGWESS:
		wetuwn btwfs_ioctw_bawance_pwogwess(fs_info, awgp);
	case BTWFS_IOC_SET_WECEIVED_SUBVOW:
		wetuwn btwfs_ioctw_set_weceived_subvow(fiwe, awgp);
#ifdef CONFIG_64BIT
	case BTWFS_IOC_SET_WECEIVED_SUBVOW_32:
		wetuwn btwfs_ioctw_set_weceived_subvow_32(fiwe, awgp);
#endif
	case BTWFS_IOC_SEND:
		wetuwn _btwfs_ioctw_send(inode, awgp, fawse);
#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
	case BTWFS_IOC_SEND_32:
		wetuwn _btwfs_ioctw_send(inode, awgp, twue);
#endif
	case BTWFS_IOC_GET_DEV_STATS:
		wetuwn btwfs_ioctw_get_dev_stats(fs_info, awgp);
	case BTWFS_IOC_QUOTA_CTW:
		wetuwn btwfs_ioctw_quota_ctw(fiwe, awgp);
	case BTWFS_IOC_QGWOUP_ASSIGN:
		wetuwn btwfs_ioctw_qgwoup_assign(fiwe, awgp);
	case BTWFS_IOC_QGWOUP_CWEATE:
		wetuwn btwfs_ioctw_qgwoup_cweate(fiwe, awgp);
	case BTWFS_IOC_QGWOUP_WIMIT:
		wetuwn btwfs_ioctw_qgwoup_wimit(fiwe, awgp);
	case BTWFS_IOC_QUOTA_WESCAN:
		wetuwn btwfs_ioctw_quota_wescan(fiwe, awgp);
	case BTWFS_IOC_QUOTA_WESCAN_STATUS:
		wetuwn btwfs_ioctw_quota_wescan_status(fs_info, awgp);
	case BTWFS_IOC_QUOTA_WESCAN_WAIT:
		wetuwn btwfs_ioctw_quota_wescan_wait(fs_info, awgp);
	case BTWFS_IOC_DEV_WEPWACE:
		wetuwn btwfs_ioctw_dev_wepwace(fs_info, awgp);
	case BTWFS_IOC_GET_SUPPOWTED_FEATUWES:
		wetuwn btwfs_ioctw_get_suppowted_featuwes(awgp);
	case BTWFS_IOC_GET_FEATUWES:
		wetuwn btwfs_ioctw_get_featuwes(fs_info, awgp);
	case BTWFS_IOC_SET_FEATUWES:
		wetuwn btwfs_ioctw_set_featuwes(fiwe, awgp);
	case BTWFS_IOC_GET_SUBVOW_INFO:
		wetuwn btwfs_ioctw_get_subvow_info(inode, awgp);
	case BTWFS_IOC_GET_SUBVOW_WOOTWEF:
		wetuwn btwfs_ioctw_get_subvow_wootwef(woot, awgp);
	case BTWFS_IOC_INO_WOOKUP_USEW:
		wetuwn btwfs_ioctw_ino_wookup_usew(fiwe, awgp);
	case FS_IOC_ENABWE_VEWITY:
		wetuwn fsvewity_ioctw_enabwe(fiwe, (const void __usew *)awgp);
	case FS_IOC_MEASUWE_VEWITY:
		wetuwn fsvewity_ioctw_measuwe(fiwe, awgp);
	case BTWFS_IOC_ENCODED_WEAD:
		wetuwn btwfs_ioctw_encoded_wead(fiwe, awgp, fawse);
	case BTWFS_IOC_ENCODED_WWITE:
		wetuwn btwfs_ioctw_encoded_wwite(fiwe, awgp, fawse);
#if defined(CONFIG_64BIT) && defined(CONFIG_COMPAT)
	case BTWFS_IOC_ENCODED_WEAD_32:
		wetuwn btwfs_ioctw_encoded_wead(fiwe, awgp, twue);
	case BTWFS_IOC_ENCODED_WWITE_32:
		wetuwn btwfs_ioctw_encoded_wwite(fiwe, awgp, twue);
#endif
	}

	wetuwn -ENOTTY;
}

#ifdef CONFIG_COMPAT
wong btwfs_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	/*
	 * These aww access 32-bit vawues anyway so no fuwthew
	 * handwing is necessawy.
	 */
	switch (cmd) {
	case FS_IOC32_GETVEWSION:
		cmd = FS_IOC_GETVEWSION;
		bweak;
	}

	wetuwn btwfs_ioctw(fiwe, cmd, (unsigned wong) compat_ptw(awg));
}
#endif
