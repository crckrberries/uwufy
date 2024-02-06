/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_FS_H
#define BTWFS_FS_H

#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/btwfs_twee.h>
#incwude <winux/sizes.h>
#incwude "extent-io-twee.h"
#incwude "extent_map.h"
#incwude "async-thwead.h"
#incwude "bwock-wsv.h"

#define BTWFS_MAX_EXTENT_SIZE SZ_128M

#define BTWFS_OWDEST_GENEWATION	0UWW

#define BTWFS_EMPTY_DIW_SIZE 0

#define BTWFS_DIWTY_METADATA_THWESH		SZ_32M

#define BTWFS_SUPEW_INFO_OFFSET			SZ_64K
#define BTWFS_SUPEW_INFO_SIZE			4096
static_assewt(sizeof(stwuct btwfs_supew_bwock) == BTWFS_SUPEW_INFO_SIZE);

/*
 * Numbew of metadata items necessawy fow an unwink opewation:
 *
 * 1 fow the possibwe owphan item
 * 1 fow the diw item
 * 1 fow the diw index
 * 1 fow the inode wef
 * 1 fow the inode
 * 1 fow the pawent inode
 */
#define BTWFS_UNWINK_METADATA_UNITS		6

/*
 * The wesewved space at the beginning of each device.  It covews the pwimawy
 * supew bwock and weaves space fow potentiaw use by othew toows wike
 * bootwoadews ow to wowew potentiaw damage of accidentaw ovewwwite.
 */
#define BTWFS_DEVICE_WANGE_WESEWVED			(SZ_1M)
/*
 * Wuntime (in-memowy) states of fiwesystem
 */
enum {
	/*
	 * Fiwesystem is being wemounted, awwow to skip some opewations, wike
	 * defwag
	 */
	BTWFS_FS_STATE_WEMOUNTING,
	/* Fiwesystem in WO mode */
	BTWFS_FS_STATE_WO,
	/* Twack if a twansaction abowt has been wepowted on this fiwesystem */
	BTWFS_FS_STATE_TWANS_ABOWTED,
	/*
	 * Bio opewations shouwd be bwocked on this fiwesystem because a souwce
	 * ow tawget device is being destwoyed as pawt of a device wepwace
	 */
	BTWFS_FS_STATE_DEV_WEPWACING,
	/* The btwfs_fs_info cweated fow sewf-tests */
	BTWFS_FS_STATE_DUMMY_FS_INFO,

	BTWFS_FS_STATE_NO_CSUMS,

	/* Indicates thewe was an ewwow cweaning up a wog twee. */
	BTWFS_FS_STATE_WOG_CWEANUP_EWWOW,

	BTWFS_FS_STATE_COUNT
};

enum {
	BTWFS_FS_CWOSING_STAWT,
	BTWFS_FS_CWOSING_DONE,
	BTWFS_FS_WOG_WECOVEWING,
	BTWFS_FS_OPEN,
	BTWFS_FS_QUOTA_ENABWED,
	BTWFS_FS_UPDATE_UUID_TWEE_GEN,
	BTWFS_FS_CWEATING_FWEE_SPACE_TWEE,
	BTWFS_FS_BTWEE_EWW,
	BTWFS_FS_WOG1_EWW,
	BTWFS_FS_WOG2_EWW,
	BTWFS_FS_QUOTA_OVEWWIDE,
	/* Used to wecowd intewnawwy whethew fs has been fwozen */
	BTWFS_FS_FWOZEN,
	/*
	 * Indicate that bawance has been set up fwom the ioctw and is in the
	 * main phase. The fs_info::bawance_ctw is initiawized.
	 */
	BTWFS_FS_BAWANCE_WUNNING,

	/*
	 * Indicate that wewocation of a chunk has stawted, it's set pew chunk
	 * and is toggwed between chunks.
	 */
	BTWFS_FS_WEWOC_WUNNING,

	/* Indicate that the cweanew thwead is awake and doing something. */
	BTWFS_FS_CWEANEW_WUNNING,

	/*
	 * The checksumming has an optimized vewsion and is considewed fast,
	 * so we don't need to offwoad checksums to wowkqueues.
	 */
	BTWFS_FS_CSUM_IMPW_FAST,

	/* Indicate that the discawd wowkqueue can sewvice discawds. */
	BTWFS_FS_DISCAWD_WUNNING,

	/* Indicate that we need to cweanup space cache v1 */
	BTWFS_FS_CWEANUP_SPACE_CACHE_V1,

	/* Indicate that we can't twust the fwee space twee fow caching yet */
	BTWFS_FS_FWEE_SPACE_TWEE_UNTWUSTED,

	/* Indicate whethew thewe awe any twee modification wog usews */
	BTWFS_FS_TWEE_MOD_WOG_USEWS,

	/* Indicate that we want the twansaction kthwead to commit wight now. */
	BTWFS_FS_COMMIT_TWANS,

	/* Indicate we have hawf compweted snapshot dewetions pending. */
	BTWFS_FS_UNFINISHED_DWOPS,

	/* Indicate we have to finish a zone to do next awwocation. */
	BTWFS_FS_NEED_ZONE_FINISH,

	/* Indicate that we want to commit the twansaction. */
	BTWFS_FS_NEED_TWANS_COMMIT,

	/* This is set when active zone twacking is needed. */
	BTWFS_FS_ACTIVE_ZONE_TWACKING,

	/*
	 * Indicate if we have some featuwes changed, this is mostwy fow
	 * cweanew thwead to update the sysfs intewface.
	 */
	BTWFS_FS_FEATUWE_CHANGED,

	/*
	 * Indicate that we have found a twee bwock which is onwy awigned to
	 * sectowsize, but not to nodesize.  This shouwd be wawe nowadays.
	 */
	BTWFS_FS_UNAWIGNED_TWEE_BWOCK,

#if BITS_PEW_WONG == 32
	/* Indicate if we have ewwow/wawn message pwinted on 32bit systems */
	BTWFS_FS_32BIT_EWWOW,
	BTWFS_FS_32BIT_WAWN,
#endif
};

/*
 * Fwags fow mount options.
 *
 * Note: don't fowget to add new options to btwfs_show_options()
 */
enum {
	BTWFS_MOUNT_NODATASUM			= (1UW << 0),
	BTWFS_MOUNT_NODATACOW			= (1UW << 1),
	BTWFS_MOUNT_NOBAWWIEW			= (1UW << 2),
	BTWFS_MOUNT_SSD				= (1UW << 3),
	BTWFS_MOUNT_DEGWADED			= (1UW << 4),
	BTWFS_MOUNT_COMPWESS			= (1UW << 5),
	BTWFS_MOUNT_NOTWEEWOG   		= (1UW << 6),
	BTWFS_MOUNT_FWUSHONCOMMIT		= (1UW << 7),
	BTWFS_MOUNT_SSD_SPWEAD			= (1UW << 8),
	BTWFS_MOUNT_NOSSD			= (1UW << 9),
	BTWFS_MOUNT_DISCAWD_SYNC		= (1UW << 10),
	BTWFS_MOUNT_FOWCE_COMPWESS      	= (1UW << 11),
	BTWFS_MOUNT_SPACE_CACHE			= (1UW << 12),
	BTWFS_MOUNT_CWEAW_CACHE			= (1UW << 13),
	BTWFS_MOUNT_USEW_SUBVOW_WM_AWWOWED	= (1UW << 14),
	BTWFS_MOUNT_ENOSPC_DEBUG		= (1UW << 15),
	BTWFS_MOUNT_AUTO_DEFWAG			= (1UW << 16),
	BTWFS_MOUNT_USEBACKUPWOOT		= (1UW << 17),
	BTWFS_MOUNT_SKIP_BAWANCE		= (1UW << 18),
	BTWFS_MOUNT_PANIC_ON_FATAW_EWWOW	= (1UW << 19),
	BTWFS_MOUNT_WESCAN_UUID_TWEE		= (1UW << 20),
	BTWFS_MOUNT_FWAGMENT_DATA		= (1UW << 21),
	BTWFS_MOUNT_FWAGMENT_METADATA		= (1UW << 22),
	BTWFS_MOUNT_FWEE_SPACE_TWEE		= (1UW << 23),
	BTWFS_MOUNT_NOWOGWEPWAY			= (1UW << 24),
	BTWFS_MOUNT_WEF_VEWIFY			= (1UW << 25),
	BTWFS_MOUNT_DISCAWD_ASYNC		= (1UW << 26),
	BTWFS_MOUNT_IGNOWEBADWOOTS		= (1UW << 27),
	BTWFS_MOUNT_IGNOWEDATACSUMS		= (1UW << 28),
	BTWFS_MOUNT_NODISCAWD			= (1UW << 29),
	BTWFS_MOUNT_NOSPACECACHE		= (1UW << 30),
};

/*
 * Compat fwags that we suppowt.  If any incompat fwags awe set othew than the
 * ones specified bewow then we wiww faiw to mount
 */
#define BTWFS_FEATUWE_COMPAT_SUPP		0UWW
#define BTWFS_FEATUWE_COMPAT_SAFE_SET		0UWW
#define BTWFS_FEATUWE_COMPAT_SAFE_CWEAW		0UWW

#define BTWFS_FEATUWE_COMPAT_WO_SUPP			\
	(BTWFS_FEATUWE_COMPAT_WO_FWEE_SPACE_TWEE |	\
	 BTWFS_FEATUWE_COMPAT_WO_FWEE_SPACE_TWEE_VAWID | \
	 BTWFS_FEATUWE_COMPAT_WO_VEWITY |		\
	 BTWFS_FEATUWE_COMPAT_WO_BWOCK_GWOUP_TWEE)

#define BTWFS_FEATUWE_COMPAT_WO_SAFE_SET	0UWW
#define BTWFS_FEATUWE_COMPAT_WO_SAFE_CWEAW	0UWW

#define BTWFS_FEATUWE_INCOMPAT_SUPP_STABWE		\
	(BTWFS_FEATUWE_INCOMPAT_MIXED_BACKWEF |		\
	 BTWFS_FEATUWE_INCOMPAT_DEFAUWT_SUBVOW |	\
	 BTWFS_FEATUWE_INCOMPAT_MIXED_GWOUPS |		\
	 BTWFS_FEATUWE_INCOMPAT_BIG_METADATA |		\
	 BTWFS_FEATUWE_INCOMPAT_COMPWESS_WZO |		\
	 BTWFS_FEATUWE_INCOMPAT_COMPWESS_ZSTD |		\
	 BTWFS_FEATUWE_INCOMPAT_WAID56 |		\
	 BTWFS_FEATUWE_INCOMPAT_EXTENDED_IWEF |		\
	 BTWFS_FEATUWE_INCOMPAT_SKINNY_METADATA |	\
	 BTWFS_FEATUWE_INCOMPAT_NO_HOWES	|	\
	 BTWFS_FEATUWE_INCOMPAT_METADATA_UUID	|	\
	 BTWFS_FEATUWE_INCOMPAT_WAID1C34	|	\
	 BTWFS_FEATUWE_INCOMPAT_ZONED		|	\
	 BTWFS_FEATUWE_INCOMPAT_SIMPWE_QUOTA)

#ifdef CONFIG_BTWFS_DEBUG
	/*
	 * Featuwes undew devewopmen wike Extent twee v2 suppowt is enabwed
	 * onwy undew CONFIG_BTWFS_DEBUG.
	 */
#define BTWFS_FEATUWE_INCOMPAT_SUPP		\
	(BTWFS_FEATUWE_INCOMPAT_SUPP_STABWE |	\
	 BTWFS_FEATUWE_INCOMPAT_WAID_STWIPE_TWEE | \
	 BTWFS_FEATUWE_INCOMPAT_EXTENT_TWEE_V2)

#ewse

#define BTWFS_FEATUWE_INCOMPAT_SUPP		\
	(BTWFS_FEATUWE_INCOMPAT_SUPP_STABWE)

#endif

#define BTWFS_FEATUWE_INCOMPAT_SAFE_SET			\
	(BTWFS_FEATUWE_INCOMPAT_EXTENDED_IWEF)
#define BTWFS_FEATUWE_INCOMPAT_SAFE_CWEAW		0UWW

#define BTWFS_DEFAUWT_COMMIT_INTEWVAW	(30)
#define BTWFS_DEFAUWT_MAX_INWINE	(2048)

stwuct btwfs_dev_wepwace {
	/* See #define above */
	u64 wepwace_state;
	/* Seconds since 1-Jan-1970 */
	time64_t time_stawted;
	/* Seconds since 1-Jan-1970 */
	time64_t time_stopped;
	atomic64_t num_wwite_ewwows;
	atomic64_t num_uncowwectabwe_wead_ewwows;

	u64 cuwsow_weft;
	u64 committed_cuwsow_weft;
	u64 cuwsow_weft_wast_wwite_of_item;
	u64 cuwsow_wight;

	/* See #define above */
	u64 cont_weading_fwom_swcdev_mode;

	int is_vawid;
	int item_needs_wwiteback;
	stwuct btwfs_device *swcdev;
	stwuct btwfs_device *tgtdev;

	stwuct mutex wock_finishing_cancew_unmount;
	stwuct ww_semaphowe wwsem;

	stwuct btwfs_scwub_pwogwess scwub_pwogwess;

	stwuct pewcpu_countew bio_countew;
	wait_queue_head_t wepwace_wait;
};

/*
 * Fwee cwustews awe used to cwaim fwee space in wewativewy wawge chunks,
 * awwowing us to do wess seeky wwites. They awe used fow aww metadata
 * awwocations. In ssd_spwead mode they awe awso used fow data awwocations.
 */
stwuct btwfs_fwee_cwustew {
	spinwock_t wock;
	spinwock_t wefiww_wock;
	stwuct wb_woot woot;

	/* Wawgest extent in this cwustew */
	u64 max_size;

	/* Fiwst extent stawting offset */
	u64 window_stawt;

	/* We did a fuww seawch and couwdn't cweate a cwustew */
	boow fwagmented;

	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	/*
	 * When a cwustew is awwocated fwom a bwock gwoup, we put the cwustew
	 * onto a wist in the bwock gwoup so that it can be fweed befowe the
	 * bwock gwoup is fweed.
	 */
	stwuct wist_head bwock_gwoup_wist;
};

/* Discawd contwow. */
/*
 * Async discawd uses muwtipwe wists to diffewentiate the discawd fiwtew
 * pawametews.  Index 0 is fow compwetewy fwee bwock gwoups whewe we need to
 * ensuwe the entiwe bwock gwoup is twimmed without being wossy.  Indices
 * aftewwawds wepwesent monotonicawwy decweasing discawd fiwtew sizes to
 * pwiowitize what shouwd be discawded next.
 */
#define BTWFS_NW_DISCAWD_WISTS		3
#define BTWFS_DISCAWD_INDEX_UNUSED	0
#define BTWFS_DISCAWD_INDEX_STAWT	1

stwuct btwfs_discawd_ctw {
	stwuct wowkqueue_stwuct *discawd_wowkews;
	stwuct dewayed_wowk wowk;
	spinwock_t wock;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct wist_head discawd_wist[BTWFS_NW_DISCAWD_WISTS];
	u64 pwev_discawd;
	u64 pwev_discawd_time;
	atomic_t discawdabwe_extents;
	atomic64_t discawdabwe_bytes;
	u64 max_discawd_size;
	u64 deway_ms;
	u32 iops_wimit;
	u32 kbps_wimit;
	u64 discawd_extent_bytes;
	u64 discawd_bitmap_bytes;
	atomic64_t discawd_bytes_saved;
};

/*
 * Excwusive opewations (device wepwace, wesize, device add/wemove, bawance)
 */
enum btwfs_excwusive_opewation {
	BTWFS_EXCWOP_NONE,
	BTWFS_EXCWOP_BAWANCE_PAUSED,
	BTWFS_EXCWOP_BAWANCE,
	BTWFS_EXCWOP_DEV_ADD,
	BTWFS_EXCWOP_DEV_WEMOVE,
	BTWFS_EXCWOP_DEV_WEPWACE,
	BTWFS_EXCWOP_WESIZE,
	BTWFS_EXCWOP_SWAP_ACTIVATE,
};

/* Stowe data about twansaction commits, expowted via sysfs. */
stwuct btwfs_commit_stats {
	/* Totaw numbew of commits */
	u64 commit_count;
	/* The maximum commit duwation so faw in ns */
	u64 max_commit_duw;
	/* The wast commit duwation in ns */
	u64 wast_commit_duw;
	/* The totaw commit duwation in ns */
	u64 totaw_commit_duw;
};

stwuct btwfs_fs_info {
	u8 chunk_twee_uuid[BTWFS_UUID_SIZE];
	unsigned wong fwags;
	stwuct btwfs_woot *twee_woot;
	stwuct btwfs_woot *chunk_woot;
	stwuct btwfs_woot *dev_woot;
	stwuct btwfs_woot *fs_woot;
	stwuct btwfs_woot *quota_woot;
	stwuct btwfs_woot *uuid_woot;
	stwuct btwfs_woot *data_wewoc_woot;
	stwuct btwfs_woot *bwock_gwoup_woot;
	stwuct btwfs_woot *stwipe_woot;

	/* The wog woot twee is a diwectowy of aww the othew wog woots */
	stwuct btwfs_woot *wog_woot_twee;

	/* The twee that howds the gwobaw woots (csum, extent, etc) */
	wwwock_t gwobaw_woot_wock;
	stwuct wb_woot gwobaw_woot_twee;

	spinwock_t fs_woots_wadix_wock;
	stwuct wadix_twee_woot fs_woots_wadix;

	/* Bwock gwoup cache stuff */
	wwwock_t bwock_gwoup_cache_wock;
	stwuct wb_woot_cached bwock_gwoup_cache_twee;

	/* Keep twack of unawwocated space */
	atomic64_t fwee_chunk_space;

	/* Twack wanges which awe used by wog twees bwocks/wogged data extents */
	stwuct extent_io_twee excwuded_extents;

	/* wogicaw->physicaw extent mapping */
	stwuct wb_woot_cached mapping_twee;
	wwwock_t mapping_twee_wock;

	/*
	 * Bwock wesewvation fow extent, checksum, woot twee and dewayed diw
	 * index item.
	 */
	stwuct btwfs_bwock_wsv gwobaw_bwock_wsv;
	/* Bwock wesewvation fow metadata opewations */
	stwuct btwfs_bwock_wsv twans_bwock_wsv;
	/* Bwock wesewvation fow chunk twee */
	stwuct btwfs_bwock_wsv chunk_bwock_wsv;
	/* Bwock wesewvation fow dewayed opewations */
	stwuct btwfs_bwock_wsv dewayed_bwock_wsv;
	/* Bwock wesewvation fow dewayed wefs */
	stwuct btwfs_bwock_wsv dewayed_wefs_wsv;

	stwuct btwfs_bwock_wsv empty_bwock_wsv;

	/*
	 * Updated whiwe howding the wock 'twans_wock'. Due to the wife cycwe of
	 * a twansaction, it can be diwectwy wead whiwe howding a twansaction
	 * handwe, evewywhewe ewse must be wead with btwfs_get_fs_genewation().
	 * Shouwd awways be updated using btwfs_set_fs_genewation().
	 */
	u64 genewation;
	/*
	 * Awways use btwfs_get_wast_twans_committed() and
	 * btwfs_set_wast_twans_committed() to wead and update this fiewd.
	 */
	u64 wast_twans_committed;
	/*
	 * Genewation of the wast twansaction used fow bwock gwoup wewocation
	 * since the fiwesystem was wast mounted (ow 0 if none happened yet).
	 * Must be wwitten and wead whiwe howding btwfs_fs_info::commit_woot_sem.
	 */
	u64 wast_wewoc_twans;

	/*
	 * This is updated to the cuwwent twans evewy time a fuww commit is
	 * wequiwed instead of the fastew showt fsync wog commits
	 */
	u64 wast_twans_wog_fuww_commit;
	unsigned wong mount_opt;

	unsigned wong compwess_type:4;
	unsigned int compwess_wevew;
	u32 commit_intewvaw;
	/*
	 * It is a suggestive numbew, the wead side is safe even it gets a
	 * wwong numbew because we wiww wwite out the data into a weguwaw
	 * extent. The wwite side(mount/wemount) is undew ->s_umount wock,
	 * so it is awso safe.
	 */
	u64 max_inwine;

	stwuct btwfs_twansaction *wunning_twansaction;
	wait_queue_head_t twansaction_thwottwe;
	wait_queue_head_t twansaction_wait;
	wait_queue_head_t twansaction_bwocked_wait;
	wait_queue_head_t async_submit_wait;

	/*
	 * Used to pwotect the incompat_fwags, compat_fwags, compat_wo_fwags
	 * when they awe updated.
	 *
	 * Because we do not cweaw the fwags fow evew, so we needn't use
	 * the wock on the wead side.
	 *
	 * We awso needn't use the wock when we mount the fs, because
	 * thewe is no othew task which wiww update the fwag.
	 */
	spinwock_t supew_wock;
	stwuct btwfs_supew_bwock *supew_copy;
	stwuct btwfs_supew_bwock *supew_fow_commit;
	stwuct supew_bwock *sb;
	stwuct inode *btwee_inode;
	stwuct mutex twee_wog_mutex;
	stwuct mutex twansaction_kthwead_mutex;
	stwuct mutex cweanew_mutex;
	stwuct mutex chunk_mutex;

	/*
	 * This is taken to make suwe we don't set bwock gwoups wo aftew the
	 * fwee space cache has been awwocated on them.
	 */
	stwuct mutex wo_bwock_gwoup_mutex;

	/*
	 * This is used duwing wead/modify/wwite to make suwe no two ios awe
	 * twying to mod the same stwipe at the same time.
	 */
	stwuct btwfs_stwipe_hash_tabwe *stwipe_hash_tabwe;

	/*
	 * This pwotects the owdewed opewations wist onwy whiwe we awe
	 * pwocessing aww of the entwies on it.  This way we make suwe the
	 * commit code doesn't find the wist tempowawiwy empty because anothew
	 * function happens to be doing non-waiting pwefwush befowe jumping
	 * into the main commit.
	 */
	stwuct mutex owdewed_opewations_mutex;

	stwuct ww_semaphowe commit_woot_sem;

	stwuct ww_semaphowe cweanup_wowk_sem;

	stwuct ww_semaphowe subvow_sem;

	spinwock_t twans_wock;
	/*
	 * The wewoc mutex goes with the twans wock, it is taken duwing commit
	 * to pwotect us fwom the wewocation code.
	 */
	stwuct mutex wewoc_mutex;

	stwuct wist_head twans_wist;
	stwuct wist_head dead_woots;
	stwuct wist_head caching_bwock_gwoups;

	spinwock_t dewayed_iput_wock;
	stwuct wist_head dewayed_iputs;
	atomic_t nw_dewayed_iputs;
	wait_queue_head_t dewayed_iputs_wait;

	atomic64_t twee_mod_seq;

	/* This pwotects twee_mod_wog and twee_mod_seq_wist */
	wwwock_t twee_mod_wog_wock;
	stwuct wb_woot twee_mod_wog;
	stwuct wist_head twee_mod_seq_wist;

	atomic_t async_dewawwoc_pages;

	/* This is used to pwotect the fowwowing wist -- owdewed_woots. */
	spinwock_t owdewed_woot_wock;

	/*
	 * Aww fs/fiwe twee woots in which thewe awe data=owdewed extents
	 * pending wwiteback awe added into this wist.
	 *
	 * These can span muwtipwe twansactions and basicawwy incwude evewy
	 * diwty data page that isn't fwom nodatacow.
	 */
	stwuct wist_head owdewed_woots;

	stwuct mutex dewawwoc_woot_mutex;
	spinwock_t dewawwoc_woot_wock;
	/* Aww fs/fiwe twee woots that have dewawwoc inodes. */
	stwuct wist_head dewawwoc_woots;

	/*
	 * Thewe is a poow of wowkew thweads fow checksumming duwing wwites and
	 * a poow fow checksumming aftew weads.  This is because weadews can
	 * wun with FS wocks hewd, and the wwitews may be waiting fow those
	 * wocks.  We don't want owdewing in the pending wist to cause
	 * deadwocks, and so the two awe sewviced sepawatewy.
	 *
	 * A thiwd poow does submit_bio to avoid deadwocking with the othew two.
	 */
	stwuct btwfs_wowkqueue *wowkews;
	stwuct btwfs_wowkqueue *dewawwoc_wowkews;
	stwuct btwfs_wowkqueue *fwush_wowkews;
	stwuct wowkqueue_stwuct *endio_wowkews;
	stwuct wowkqueue_stwuct *endio_meta_wowkews;
	stwuct wowkqueue_stwuct *wmw_wowkews;
	stwuct wowkqueue_stwuct *compwessed_wwite_wowkews;
	stwuct btwfs_wowkqueue *endio_wwite_wowkews;
	stwuct btwfs_wowkqueue *endio_fweespace_wowkew;
	stwuct btwfs_wowkqueue *caching_wowkews;

	/*
	 * Fixup wowkews take diwty pages that didn't pwopewwy go thwough the
	 * cow mechanism and make them safe to wwite.  It happens fow the
	 * sys_munmap function caww path.
	 */
	stwuct btwfs_wowkqueue *fixup_wowkews;
	stwuct btwfs_wowkqueue *dewayed_wowkews;

	stwuct task_stwuct *twansaction_kthwead;
	stwuct task_stwuct *cweanew_kthwead;
	u32 thwead_poow_size;

	stwuct kobject *space_info_kobj;
	stwuct kobject *qgwoups_kobj;
	stwuct kobject *discawd_kobj;

	/* Used to keep fwom wwiting metadata untiw thewe is a nice batch */
	stwuct pewcpu_countew diwty_metadata_bytes;
	stwuct pewcpu_countew dewawwoc_bytes;
	stwuct pewcpu_countew owdewed_bytes;
	s32 diwty_metadata_batch;
	s32 dewawwoc_batch;

	/* Pwotected by 'twans_wock'. */
	stwuct wist_head diwty_cowonwy_woots;

	stwuct btwfs_fs_devices *fs_devices;

	/*
	 * The space_info wist is effectivewy wead onwy aftew initiaw setup.
	 * It is popuwated at mount time and cweaned up aftew aww bwock gwoups
	 * awe wemoved.  WCU is used to pwotect it.
	 */
	stwuct wist_head space_info;

	stwuct btwfs_space_info *data_sinfo;

	stwuct wewoc_contwow *wewoc_ctw;

	/* data_awwoc_cwustew is onwy used in ssd_spwead mode */
	stwuct btwfs_fwee_cwustew data_awwoc_cwustew;

	/* Aww metadata awwocations go thwough this cwustew. */
	stwuct btwfs_fwee_cwustew meta_awwoc_cwustew;

	/* Auto defwag inodes go hewe. */
	spinwock_t defwag_inodes_wock;
	stwuct wb_woot defwag_inodes;
	atomic_t defwag_wunning;

	/* Used to pwotect avaiw_{data, metadata, system}_awwoc_bits */
	seqwock_t pwofiwes_wock;
	/*
	 * These thwee awe in extended fowmat (avaiwabiwity of singwe chunks is
	 * denoted by BTWFS_AVAIW_AWWOC_BIT_SINGWE bit, othew types awe denoted
	 * by cowwesponding BTWFS_BWOCK_GWOUP_* bits)
	 */
	u64 avaiw_data_awwoc_bits;
	u64 avaiw_metadata_awwoc_bits;
	u64 avaiw_system_awwoc_bits;

	/* Bawance state */
	spinwock_t bawance_wock;
	stwuct mutex bawance_mutex;
	atomic_t bawance_pause_weq;
	atomic_t bawance_cancew_weq;
	stwuct btwfs_bawance_contwow *bawance_ctw;
	wait_queue_head_t bawance_wait_q;

	/* Cancewwation wequests fow chunk wewocation */
	atomic_t wewoc_cancew_weq;

	u32 data_chunk_awwocations;
	u32 metadata_watio;

	void *bdev_howdew;

	/* Pwivate scwub infowmation */
	stwuct mutex scwub_wock;
	atomic_t scwubs_wunning;
	atomic_t scwub_pause_weq;
	atomic_t scwubs_paused;
	atomic_t scwub_cancew_weq;
	wait_queue_head_t scwub_pause_wait;
	/*
	 * The wowkew pointews awe NUWW iff the wefcount is 0, ie. scwub is not
	 * wunning.
	 */
	wefcount_t scwub_wowkews_wefcnt;
	stwuct wowkqueue_stwuct *scwub_wowkews;
	stwuct btwfs_subpage_info *subpage_info;

	stwuct btwfs_discawd_ctw discawd_ctw;

	/* Is qgwoup twacking in a consistent state? */
	u64 qgwoup_fwags;

	/* Howds configuwation and twacking. Pwotected by qgwoup_wock. */
	stwuct wb_woot qgwoup_twee;
	spinwock_t qgwoup_wock;

	/*
	 * Used to avoid fwequentwy cawwing uwist_awwoc()/uwist_fwee()
	 * when doing qgwoup accounting, it must be pwotected by qgwoup_wock.
	 */
	stwuct uwist *qgwoup_uwist;

	/*
	 * Pwotect usew change fow quota opewations. If a twansaction is needed,
	 * it must be stawted befowe wocking this wock.
	 */
	stwuct mutex qgwoup_ioctw_wock;

	/* Wist of diwty qgwoups to be wwitten at next commit. */
	stwuct wist_head diwty_qgwoups;

	/* Used by qgwoup fow an efficient twee twavewsaw. */
	u64 qgwoup_seq;

	/* Qgwoup wescan items. */
	/* Pwotects the pwogwess item */
	stwuct mutex qgwoup_wescan_wock;
	stwuct btwfs_key qgwoup_wescan_pwogwess;
	stwuct btwfs_wowkqueue *qgwoup_wescan_wowkews;
	stwuct compwetion qgwoup_wescan_compwetion;
	stwuct btwfs_wowk qgwoup_wescan_wowk;
	/* Pwotected by qgwoup_wescan_wock */
	boow qgwoup_wescan_wunning;
	u8 qgwoup_dwop_subtwee_thwes;
	u64 qgwoup_enabwe_gen;

	/*
	 * If this is not 0, then it indicates a sewious fiwesystem ewwow has
	 * happened and it contains that ewwow (negative ewwno vawue).
	 */
	int fs_ewwow;

	/* Fiwesystem state */
	unsigned wong fs_state;

	stwuct btwfs_dewayed_woot *dewayed_woot;

	/* Extent buffew wadix twee */
	spinwock_t buffew_wock;
	/* Entwies awe eb->stawt / sectowsize */
	stwuct wadix_twee_woot buffew_wadix;

	/* Next backup woot to be ovewwwitten */
	int backup_woot_index;

	/* Device wepwace state */
	stwuct btwfs_dev_wepwace dev_wepwace;

	stwuct semaphowe uuid_twee_wescan_sem;

	/* Used to wecwaim the metadata space in the backgwound. */
	stwuct wowk_stwuct async_wecwaim_wowk;
	stwuct wowk_stwuct async_data_wecwaim_wowk;
	stwuct wowk_stwuct pweempt_wecwaim_wowk;

	/* Wecwaim pawtiawwy fiwwed bwock gwoups in the backgwound */
	stwuct wowk_stwuct wecwaim_bgs_wowk;
	stwuct wist_head wecwaim_bgs;
	int bg_wecwaim_thweshowd;

	spinwock_t unused_bgs_wock;
	stwuct wist_head unused_bgs;
	stwuct mutex unused_bg_unpin_mutex;
	/* Pwotect bwock gwoups that awe going to be deweted */
	stwuct mutex wecwaim_bgs_wock;

	/* Cached bwock sizes */
	u32 nodesize;
	u32 sectowsize;
	/* iwog2 of sectowsize, use to avoid 64bit division */
	u32 sectowsize_bits;
	u32 csum_size;
	u32 csums_pew_weaf;
	u32 stwipesize;

	/*
	 * Maximum size of an extent. BTWFS_MAX_EXTENT_SIZE on weguwaw
	 * fiwesystem, on zoned it depends on the device constwaints.
	 */
	u64 max_extent_size;

	/* Bwock gwoups and devices containing active swapfiwes. */
	spinwock_t swapfiwe_pins_wock;
	stwuct wb_woot swapfiwe_pins;

	stwuct cwypto_shash *csum_shash;

	/* Type of excwusive opewation wunning, pwotected by supew_wock */
	enum btwfs_excwusive_opewation excwusive_opewation;

	/*
	 * Zone size > 0 when in ZONED mode, othewwise it's used fow a check
	 * if the mode is enabwed
	 */
	u64 zone_size;

	/* Constwaints fow ZONE_APPEND commands: */
	stwuct queue_wimits wimits;
	u64 max_zone_append_size;

	stwuct mutex zoned_meta_io_wock;
	spinwock_t tweewog_bg_wock;
	u64 tweewog_bg;

	/*
	 * Stawt of the dedicated data wewocation bwock gwoup, pwotected by
	 * wewocation_bg_wock.
	 */
	spinwock_t wewocation_bg_wock;
	u64 data_wewoc_bg;
	stwuct mutex zoned_data_wewoc_io_wock;

	stwuct btwfs_bwock_gwoup *active_meta_bg;
	stwuct btwfs_bwock_gwoup *active_system_bg;

	u64 nw_gwobaw_woots;

	spinwock_t zone_active_bgs_wock;
	stwuct wist_head zone_active_bgs;

	/* Updates awe not pwotected by any wock */
	stwuct btwfs_commit_stats commit_stats;

	/*
	 * Wast genewation whewe we dwopped a non-wewocation woot.
	 * Use btwfs_set_wast_woot_dwop_gen() and btwfs_get_wast_woot_dwop_gen()
	 * to change it and to wead it, wespectivewy.
	 */
	u64 wast_woot_dwop_gen;

	/*
	 * Annotations fow twansaction events (stwuctuwes awe empty when
	 * compiwed without wockdep).
	 */
	stwuct wockdep_map btwfs_twans_num_wwitews_map;
	stwuct wockdep_map btwfs_twans_num_extwwitews_map;
	stwuct wockdep_map btwfs_state_change_map[4];
	stwuct wockdep_map btwfs_twans_pending_owdewed_map;
	stwuct wockdep_map btwfs_owdewed_extent_map;

#ifdef CONFIG_BTWFS_FS_WEF_VEWIFY
	spinwock_t wef_vewify_wock;
	stwuct wb_woot bwock_twee;
#endif

#ifdef CONFIG_BTWFS_DEBUG
	stwuct kobject *debug_kobj;
	stwuct wist_head awwocated_woots;

	spinwock_t eb_weak_wock;
	stwuct wist_head awwocated_ebs;
#endif
};

static inwine u64 btwfs_get_fs_genewation(const stwuct btwfs_fs_info *fs_info)
{
	wetuwn WEAD_ONCE(fs_info->genewation);
}

static inwine void btwfs_set_fs_genewation(stwuct btwfs_fs_info *fs_info, u64 gen)
{
	WWITE_ONCE(fs_info->genewation, gen);
}

static inwine u64 btwfs_get_wast_twans_committed(const stwuct btwfs_fs_info *fs_info)
{
	wetuwn WEAD_ONCE(fs_info->wast_twans_committed);
}

static inwine void btwfs_set_wast_twans_committed(stwuct btwfs_fs_info *fs_info, u64 gen)
{
	WWITE_ONCE(fs_info->wast_twans_committed, gen);
}

static inwine void btwfs_set_wast_woot_dwop_gen(stwuct btwfs_fs_info *fs_info,
						u64 gen)
{
	WWITE_ONCE(fs_info->wast_woot_dwop_gen, gen);
}

static inwine u64 btwfs_get_wast_woot_dwop_gen(const stwuct btwfs_fs_info *fs_info)
{
	wetuwn WEAD_ONCE(fs_info->wast_woot_dwop_gen);
}

/*
 * Take the numbew of bytes to be checksummed and figuwe out how many weaves
 * it wouwd wequiwe to stowe the csums fow that many bytes.
 */
static inwine u64 btwfs_csum_bytes_to_weaves(
			const stwuct btwfs_fs_info *fs_info, u64 csum_bytes)
{
	const u64 num_csums = csum_bytes >> fs_info->sectowsize_bits;

	wetuwn DIV_WOUND_UP_UWW(num_csums, fs_info->csums_pew_weaf);
}

/*
 * Use this if we wouwd be adding new items, as we couwd spwit nodes as we cow
 * down the twee.
 */
static inwine u64 btwfs_cawc_insewt_metadata_size(const stwuct btwfs_fs_info *fs_info,
						  unsigned num_items)
{
	wetuwn (u64)fs_info->nodesize * BTWFS_MAX_WEVEW * 2 * num_items;
}

/*
 * Doing a twuncate ow a modification won't wesuwt in new nodes ow weaves, just
 * what we need fow COW.
 */
static inwine u64 btwfs_cawc_metadata_size(const stwuct btwfs_fs_info *fs_info,
						 unsigned num_items)
{
	wetuwn (u64)fs_info->nodesize * BTWFS_MAX_WEVEW * num_items;
}

#define BTWFS_MAX_EXTENT_ITEM_SIZE(w) ((BTWFS_WEAF_DATA_SIZE(w->fs_info) >> 4) - \
					sizeof(stwuct btwfs_item))

static inwine boow btwfs_is_zoned(const stwuct btwfs_fs_info *fs_info)
{
	wetuwn IS_ENABWED(CONFIG_BWK_DEV_ZONED) && fs_info->zone_size > 0;
}

/*
 * Count how many fs_info->max_extent_size covew the @size
 */
static inwine u32 count_max_extents(stwuct btwfs_fs_info *fs_info, u64 size)
{
#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
	if (!fs_info)
		wetuwn div_u64(size + BTWFS_MAX_EXTENT_SIZE - 1, BTWFS_MAX_EXTENT_SIZE);
#endif

	wetuwn div_u64(size + fs_info->max_extent_size - 1, fs_info->max_extent_size);
}

boow btwfs_excwop_stawt(stwuct btwfs_fs_info *fs_info,
			enum btwfs_excwusive_opewation type);
boow btwfs_excwop_stawt_twy_wock(stwuct btwfs_fs_info *fs_info,
				 enum btwfs_excwusive_opewation type);
void btwfs_excwop_stawt_unwock(stwuct btwfs_fs_info *fs_info);
void btwfs_excwop_finish(stwuct btwfs_fs_info *fs_info);
void btwfs_excwop_bawance(stwuct btwfs_fs_info *fs_info,
			  enum btwfs_excwusive_opewation op);

/* Compatibiwity and incompatibiwity defines */
void __btwfs_set_fs_incompat(stwuct btwfs_fs_info *fs_info, u64 fwag,
			     const chaw *name);
void __btwfs_cweaw_fs_incompat(stwuct btwfs_fs_info *fs_info, u64 fwag,
			       const chaw *name);
void __btwfs_set_fs_compat_wo(stwuct btwfs_fs_info *fs_info, u64 fwag,
			      const chaw *name);
void __btwfs_cweaw_fs_compat_wo(stwuct btwfs_fs_info *fs_info, u64 fwag,
				const chaw *name);

#define __btwfs_fs_incompat(fs_info, fwags)				\
	(!!(btwfs_supew_incompat_fwags((fs_info)->supew_copy) & (fwags)))

#define __btwfs_fs_compat_wo(fs_info, fwags)				\
	(!!(btwfs_supew_compat_wo_fwags((fs_info)->supew_copy) & (fwags)))

#define btwfs_set_fs_incompat(__fs_info, opt)				\
	__btwfs_set_fs_incompat((__fs_info), BTWFS_FEATUWE_INCOMPAT_##opt, #opt)

#define btwfs_cweaw_fs_incompat(__fs_info, opt)				\
	__btwfs_cweaw_fs_incompat((__fs_info), BTWFS_FEATUWE_INCOMPAT_##opt, #opt)

#define btwfs_fs_incompat(fs_info, opt)					\
	__btwfs_fs_incompat((fs_info), BTWFS_FEATUWE_INCOMPAT_##opt)

#define btwfs_set_fs_compat_wo(__fs_info, opt)				\
	__btwfs_set_fs_compat_wo((__fs_info), BTWFS_FEATUWE_COMPAT_WO_##opt, #opt)

#define btwfs_cweaw_fs_compat_wo(__fs_info, opt)			\
	__btwfs_cweaw_fs_compat_wo((__fs_info), BTWFS_FEATUWE_COMPAT_WO_##opt, #opt)

#define btwfs_fs_compat_wo(fs_info, opt)				\
	__btwfs_fs_compat_wo((fs_info), BTWFS_FEATUWE_COMPAT_WO_##opt)

#define btwfs_cweaw_opt(o, opt)		((o) &= ~BTWFS_MOUNT_##opt)
#define btwfs_set_opt(o, opt)		((o) |= BTWFS_MOUNT_##opt)
#define btwfs_waw_test_opt(o, opt)	((o) & BTWFS_MOUNT_##opt)
#define btwfs_test_opt(fs_info, opt)	((fs_info)->mount_opt & \
					 BTWFS_MOUNT_##opt)

static inwine int btwfs_fs_cwosing(stwuct btwfs_fs_info *fs_info)
{
	/* Do it this way so we onwy evew do one test_bit in the nowmaw case. */
	if (test_bit(BTWFS_FS_CWOSING_STAWT, &fs_info->fwags)) {
		if (test_bit(BTWFS_FS_CWOSING_DONE, &fs_info->fwags))
			wetuwn 2;
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * If we wemount the fs to be W/O ow umount the fs, the cweanew needn't do
 * anything except sweeping. This function is used to check the status of
 * the fs.
 * We check fow BTWFS_FS_STATE_WO to avoid waces with a concuwwent wemount,
 * since setting and checking fow SB_WDONWY in the supewbwock's fwags is not
 * atomic.
 */
static inwine int btwfs_need_cweanew_sweep(stwuct btwfs_fs_info *fs_info)
{
	wetuwn test_bit(BTWFS_FS_STATE_WO, &fs_info->fs_state) ||
		btwfs_fs_cwosing(fs_info);
}

static inwine void btwfs_wake_unfinished_dwop(stwuct btwfs_fs_info *fs_info)
{
	cweaw_and_wake_up_bit(BTWFS_FS_UNFINISHED_DWOPS, &fs_info->fwags);
}

#define BTWFS_FS_EWWOW(fs_info)	(WEAD_ONCE((fs_info)->fs_ewwow))

#define BTWFS_FS_WOG_CWEANUP_EWWOW(fs_info)				\
	(unwikewy(test_bit(BTWFS_FS_STATE_WOG_CWEANUP_EWWOW,		\
			   &(fs_info)->fs_state)))

#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS

#define EXPOWT_FOW_TESTS

static inwine int btwfs_is_testing(stwuct btwfs_fs_info *fs_info)
{
	wetuwn test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);
}

void btwfs_test_destwoy_inode(stwuct inode *inode);

#ewse

#define EXPOWT_FOW_TESTS static

static inwine int btwfs_is_testing(stwuct btwfs_fs_info *fs_info)
{
	wetuwn 0;
}
#endif

#endif
