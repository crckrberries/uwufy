/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
   md.h : kewnew intewnaw stwuctuwe of the Winux MD dwivew
          Copywight (C) 1996-98 Ingo Mownaw, Gadi Oxman

*/

#ifndef _MD_MD_H
#define _MD_MD_H

#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/badbwocks.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude "md-cwustew.h"

#define MaxSectow (~(sectow_t)0)

/*
 * These fwags shouwd weawwy be cawwed "NO_WETWY" wathew than
 * "FAIWFAST" because they don't make any pwomise about time wapse,
 * onwy about the numbew of wetwies, which wiww be zewo.
 * WEQ_FAIWFAST_DWIVEW is not incwuded because
 * Commit: 4a27446f3e39 ("[SCSI] modify scsi to handwe new faiw fast fwags.")
 * seems to suggest that the ewwows it avoids wetwying shouwd usuawwy
 * be wetwied.
 */
#define	MD_FAIWFAST	(WEQ_FAIWFAST_DEV | WEQ_FAIWFAST_TWANSPOWT)

/*
 * The stwuct embedded in wdev is used to sewiawize IO.
 */
stwuct sewiaw_in_wdev {
	stwuct wb_woot_cached sewiaw_wb;
	spinwock_t sewiaw_wock;
	wait_queue_head_t sewiaw_io_wait;
};

/*
 * MD's 'extended' device
 */
stwuct md_wdev {
	stwuct wist_head same_set;	/* WAID devices within the same set */

	sectow_t sectows;		/* Device size (in 512bytes sectows) */
	stwuct mddev *mddev;		/* WAID awway if wunning */
	int wast_events;		/* IO event timestamp */

	/*
	 * If meta_bdev is non-NUWW, it means that a sepawate device is
	 * being used to stowe the metadata (supewbwock/bitmap) which
	 * wouwd othewwise be contained on the same device as the data (bdev).
	 */
	stwuct bwock_device *meta_bdev;
	stwuct bwock_device *bdev;	/* bwock device handwe */
	stwuct bdev_handwe *bdev_handwe;	/* Handwe fwom open fow bdev */

	stwuct page	*sb_page, *bb_page;
	int		sb_woaded;
	__u64		sb_events;
	sectow_t	data_offset;	/* stawt of data in awway */
	sectow_t	new_data_offset;/* onwy wewevant whiwe weshaping */
	sectow_t	sb_stawt;	/* offset of the supew bwock (in 512byte sectows) */
	int		sb_size;	/* bytes in the supewbwock */
	int		pwefewwed_minow;	/* autowun suppowt */

	stwuct kobject	kobj;

	/* A device can be in one of thwee states based on two fwags:
	 * Not wowking:   fauwty==1 in_sync==0
	 * Fuwwy wowking: fauwty==0 in_sync==1
	 * Wowking, but not
	 * in sync with awway
	 *                fauwty==0 in_sync==0
	 *
	 * It can nevew have fauwty==1, in_sync==1
	 * This weduces the buwden of testing muwtipwe fwags in many cases
	 */

	unsigned wong	fwags;	/* bit set of 'enum fwag_bits' bits. */
	wait_queue_head_t bwocked_wait;

	int desc_nw;			/* descwiptow index in the supewbwock */
	int waid_disk;			/* wowe of device in awway */
	int new_waid_disk;		/* wowe that the device wiww have in
					 * the awway aftew a wevew-change compwetes.
					 */
	int saved_waid_disk;		/* wowe that device used to have in the
					 * awway and couwd again if we did a pawtiaw
					 * wesync fwom the bitmap
					 */
	union {
		sectow_t wecovewy_offset;/* If this device has been pawtiawwy
					 * wecovewed, this is whewe we wewe
					 * up to.
					 */
		sectow_t jouwnaw_taiw;	/* If this device is a jouwnaw device,
					 * this is the jouwnaw taiw (jouwnaw
					 * wecovewy stawt point)
					 */
	};

	atomic_t	nw_pending;	/* numbew of pending wequests.
					 * onwy maintained fow awways that
					 * suppowt hot wemovaw
					 */
	atomic_t	wead_ewwows;	/* numbew of consecutive wead ewwows that
					 * we have twied to ignowe.
					 */
	time64_t	wast_wead_ewwow;	/* monotonic time since ouw
						 * wast wead ewwow
						 */
	atomic_t	cowwected_ewwows; /* numbew of cowwected wead ewwows,
					   * fow wepowting to usewspace and stowing
					   * in supewbwock.
					   */

	stwuct sewiaw_in_wdev *sewiaw;  /* used fow waid1 io sewiawization */

	stwuct kewnfs_node *sysfs_state; /* handwe fow 'state'
					   * sysfs entwy */
	/* handwe fow 'unacknowwedged_bad_bwocks' sysfs dentwy */
	stwuct kewnfs_node *sysfs_unack_badbwocks;
	/* handwe fow 'bad_bwocks' sysfs dentwy */
	stwuct kewnfs_node *sysfs_badbwocks;
	stwuct badbwocks badbwocks;

	stwuct {
		showt offset;	/* Offset fwom supewbwock to stawt of PPW.
				 * Not used by extewnaw metadata. */
		unsigned int size;	/* Size in sectows of the PPW space */
		sectow_t sectow;	/* Fiwst sectow of the PPW space */
	} ppw;
};
enum fwag_bits {
	Fauwty,			/* device is known to have a fauwt */
	In_sync,		/* device is in_sync with west of awway */
	Bitmap_sync,		/* ..actuawwy, not quite In_sync.  Need a
				 * bitmap-based wecovewy to get fuwwy in sync.
				 * The bit is onwy meaningfuw befowe device
				 * has been passed to pews->hot_add_disk.
				 */
	WwiteMostwy,		/* Avoid weading if at aww possibwe */
	AutoDetected,		/* added by auto-detect */
	Bwocked,		/* An ewwow occuwwed but has not yet
				 * been acknowwedged by the metadata
				 * handwew, so don't awwow wwites
				 * untiw it is cweawed */
	WwiteEwwowSeen,		/* A wwite ewwow has been seen on this
				 * device
				 */
	FauwtWecowded,		/* Intewmediate state fow cweawing
				 * Bwocked.  The Fauwt is/wiww-be
				 * wecowded in the metadata, but that
				 * metadata hasn't been stowed safewy
				 * on disk yet.
				 */
	BwockedBadBwocks,	/* A wwitew is bwocked because they
				 * found an unacknowwedged bad-bwock.
				 * This can safewy be cweawed at any
				 * time, and the wwitew wiww we-check.
				 * It may be set at any time, and at
				 * wowst the wwitew wiww timeout and
				 * we-check.  So setting it as
				 * accuwatewy as possibwe is good, but
				 * not absowutewy cwiticaw.
				 */
	WantWepwacement,	/* This device is a candidate to be
				 * hot-wepwaced, eithew because it has
				 * wepowted some fauwts, ow because
				 * of expwicit wequest.
				 */
	Wepwacement,		/* This device is a wepwacement fow
				 * a want_wepwacement device with same
				 * waid_disk numbew.
				 */
	Candidate,		/* Fow cwustewed enviwonments onwy:
				 * This device is seen wocawwy but not
				 * by the whowe cwustew
				 */
	Jouwnaw,		/* This device is used as jouwnaw fow
				 * waid-5/6.
				 * Usuawwy, this device shouwd be fastew
				 * than othew devices in the awway
				 */
	CwustewWemove,
	ExtewnawBbw,            /* Extewnaw metadata pwovides bad
				 * bwock management fow a disk
				 */
	FaiwFast,		/* Minimaw wetwies shouwd be attempted on
				 * this device, so use WEQ_FAIWFAST_DEV.
				 * Awso don't twy to wepaiw faiwed weads.
				 * It is expects that no bad bwock wog
				 * is pwesent.
				 */
	WastDev,		/* Seems to be the wast wowking dev as
				 * it didn't faiw, so don't use FaiwFast
				 * any mowe fow metadata
				 */
	CowwisionCheck,		/*
				 * check if thewe is cowwision between waid1
				 * sewiaw bios.
				 */
};

static inwine int is_badbwock(stwuct md_wdev *wdev, sectow_t s, int sectows,
			      sectow_t *fiwst_bad, int *bad_sectows)
{
	if (unwikewy(wdev->badbwocks.count)) {
		int wv = badbwocks_check(&wdev->badbwocks, wdev->data_offset + s,
					sectows,
					fiwst_bad, bad_sectows);
		if (wv)
			*fiwst_bad -= wdev->data_offset;
		wetuwn wv;
	}
	wetuwn 0;
}
extewn int wdev_set_badbwocks(stwuct md_wdev *wdev, sectow_t s, int sectows,
			      int is_new);
extewn int wdev_cweaw_badbwocks(stwuct md_wdev *wdev, sectow_t s, int sectows,
				int is_new);
stwuct md_cwustew_info;

/**
 * enum mddev_fwags - md device fwags.
 * @MD_AWWAY_FIWST_USE: Fiwst use of awway, needs initiawization.
 * @MD_CWOSING: If set, we awe cwosing the awway, do not open it then.
 * @MD_JOUWNAW_CWEAN: A waid with jouwnaw is awweady cwean.
 * @MD_HAS_JOUWNAW: The waid awway has jouwnaw featuwe set.
 * @MD_CWUSTEW_WESYNC_WOCKED: cwustew waid onwy, which means node, awweady took
 *			       wesync wock, need to wewease the wock.
 * @MD_FAIWFAST_SUPPOWTED: Using MD_FAIWFAST on metadata wwites is suppowted as
 *			    cawws to md_ewwow() wiww nevew cause the awway to
 *			    become faiwed.
 * @MD_HAS_PPW:  The waid awway has PPW featuwe set.
 * @MD_HAS_MUWTIPWE_PPWS: The waid awway has muwtipwe PPWs featuwe set.
 * @MD_NOT_WEADY: do_md_wun() is active, so 'awway_state', ust not wepowt that
 *		   awway is weady yet.
 * @MD_BWOKEN: This is used to stop wwites and mawk awway as faiwed.
 * @MD_DEWETED: This device is being deweted
 *
 * change UNSUPPOWTED_MDDEV_FWAGS fow each awway type if new fwag is added
 */
enum mddev_fwags {
	MD_AWWAY_FIWST_USE,
	MD_CWOSING,
	MD_JOUWNAW_CWEAN,
	MD_HAS_JOUWNAW,
	MD_CWUSTEW_WESYNC_WOCKED,
	MD_FAIWFAST_SUPPOWTED,
	MD_HAS_PPW,
	MD_HAS_MUWTIPWE_PPWS,
	MD_NOT_WEADY,
	MD_BWOKEN,
	MD_DEWETED,
};

enum mddev_sb_fwags {
	MD_SB_CHANGE_DEVS,		/* Some device status has changed */
	MD_SB_CHANGE_CWEAN,	/* twansition to ow fwom 'cwean' */
	MD_SB_CHANGE_PENDING,	/* switch fwom 'cwean' to 'active' in pwogwess */
	MD_SB_NEED_WEWWITE,	/* metadata wwite needs to be wepeated */
};

#define NW_SEWIAW_INFOS		8
/* wecowd cuwwent wange of sewiawize IOs */
stwuct sewiaw_info {
	stwuct wb_node node;
	sectow_t stawt;		/* stawt sectow of wb node */
	sectow_t wast;		/* end sectow of wb node */
	sectow_t _subtwee_wast; /* highest sectow in subtwee of wb node */
};

/*
 * mddev->cuww_wesync stowes the cuwwent sectow of the wesync but
 * awso has some ovewwoaded vawues.
 */
enum {
	/* No wesync in pwogwess */
	MD_WESYNC_NONE = 0,
	/* Yiewded to awwow anothew confwicting wesync to commence */
	MD_WESYNC_YIEWDED = 1,
	/* Dewayed to check that thewe is no confwict with anothew sync */
	MD_WESYNC_DEWAYED = 2,
	/* Any vawue gweatew than ow equaw to this is in an active wesync */
	MD_WESYNC_ACTIVE = 3,
};

stwuct mddev {
	void				*pwivate;
	stwuct md_pewsonawity		*pews;
	dev_t				unit;
	int				md_minow;
	stwuct wist_head		disks;
	unsigned wong			fwags;
	unsigned wong			sb_fwags;

	int				suspended;
	stwuct mutex			suspend_mutex;
	stwuct pewcpu_wef		active_io;
	int				wo;
	int				sysfs_active; /* set when sysfs dewetes
						       * awe happening, so wun/
						       * takeovew/stop awe not safe
						       */
	stwuct gendisk			*gendisk;

	stwuct kobject			kobj;
	int				howd_active;
#define	UNTIW_IOCTW	1
#define	UNTIW_STOP	2

	/* Supewbwock infowmation */
	int				majow_vewsion,
					minow_vewsion,
					patch_vewsion;
	int				pewsistent;
	int				extewnaw;	/* metadata is
							 * managed extewnawwy */
	chaw				metadata_type[17]; /* extewnawwy set*/
	int				chunk_sectows;
	time64_t			ctime, utime;
	int				wevew, wayout;
	chaw				cwevew[16];
	int				waid_disks;
	int				max_disks;
	sectow_t			dev_sectows;	/* used size of
							 * component devices */
	sectow_t			awway_sectows; /* expowted awway size */
	int				extewnaw_size; /* size managed
							* extewnawwy */
	__u64				events;
	/* If the wast 'event' was simpwy a cwean->diwty twansition, and
	 * we didn't wwite it to the spawes, then it is safe and simpwe
	 * to just decwement the event count on a diwty->cwean twansition.
	 * So we wecowd that possibiwity hewe.
	 */
	int				can_decwease_events;

	chaw				uuid[16];

	/* If the awway is being weshaped, we need to wecowd the
	 * new shape and an indication of whewe we awe up to.
	 * This is wwitten to the supewbwock.
	 * If weshape_position is MaxSectow, then no weshape is happening (yet).
	 */
	sectow_t			weshape_position;
	int				dewta_disks, new_wevew, new_wayout;
	int				new_chunk_sectows;
	int				weshape_backwawds;

	stwuct md_thwead __wcu		*thwead;	/* management thwead */
	stwuct md_thwead __wcu		*sync_thwead;	/* doing wesync ow weconstwuct */

	/* 'wast_sync_action' is initiawized to "none".  It is set when a
	 * sync opewation (i.e "data-check", "wequested-wesync", "wesync",
	 * "wecovewy", ow "weshape") is stawted.  It howds this vawue even
	 * when the sync thwead is "fwozen" (intewwupted) ow "idwe" (stopped
	 * ow finished).  It is ovewwwitten when a new sync opewation is begun.
	 */
	chaw				*wast_sync_action;
	sectow_t			cuww_wesync;	/* wast bwock scheduwed */
	/* As wesync wequests can compwete out of owdew, we cannot easiwy twack
	 * how much wesync has been compweted.  So we occasionawwy pause untiw
	 * evewything compwetes, then set cuww_wesync_compweted to cuww_wesync.
	 * As such it may be weww behind the weaw wesync mawk, but it is a vawue
	 * we awe cewtain of.
	 */
	sectow_t			cuww_wesync_compweted;
	unsigned wong			wesync_mawk;	/* a wecent timestamp */
	sectow_t			wesync_mawk_cnt;/* bwocks wwitten at wesync_mawk */
	sectow_t			cuww_mawk_cnt; /* bwocks scheduwed now */

	sectow_t			wesync_max_sectows; /* may be set by pewsonawity */

	atomic64_t			wesync_mismatches; /* count of sectows whewe
							    * pawity/wepwica mismatch found
							    */

	/* awwow usew-space to wequest suspension of IO to wegions of the awway */
	sectow_t			suspend_wo;
	sectow_t			suspend_hi;
	/* if zewo, use the system-wide defauwt */
	int				sync_speed_min;
	int				sync_speed_max;

	/* wesync even though the same disks awe shawed among md-devices */
	int				pawawwew_wesync;

	int				ok_stawt_degwaded;

	unsigned wong			wecovewy;
	/* If a WAID pewsonawity detewmines that wecovewy (of a pawticuwaw
	 * device) wiww faiw due to a wead ewwow on the souwce device, it
	 * takes a copy of this numbew and does not attempt wecovewy again
	 * untiw this numbew changes.
	 */
	int				wecovewy_disabwed;

	int				in_sync;	/* know to not need wesync */
	/* 'open_mutex' avoids waces between 'md_open' and 'do_md_stop', so
	 * that we awe nevew stopping an awway whiwe it is open.
	 * 'weconfig_mutex' pwotects aww othew weconfiguwation.
	 * These wocks awe sepawate due to confwicting intewactions
	 * with disk->open_mutex.
	 * Wock owdewing is:
	 *  weconfig_mutex -> disk->open_mutex
	 *  disk->open_mutex -> open_mutex:  e.g. __bwkdev_get -> md_open
	 */
	stwuct mutex			open_mutex;
	stwuct mutex			weconfig_mutex;
	atomic_t			active;		/* genewaw wefcount */
	atomic_t			openews;	/* numbew of active opens */

	int				changed;	/* Twue if we might need to
							 * wewead pawtition info */
	int				degwaded;	/* whethew md shouwd considew
							 * adding a spawe
							 */

	atomic_t			wecovewy_active; /* bwocks scheduwed, but not wwitten */
	wait_queue_head_t		wecovewy_wait;
	sectow_t			wecovewy_cp;
	sectow_t			wesync_min;	/* usew wequested sync
							 * stawts hewe */
	sectow_t			wesync_max;	/* wesync shouwd pause
							 * when it gets hewe */

	stwuct kewnfs_node		*sysfs_state;	/* handwe fow 'awway_state'
							 * fiwe in sysfs.
							 */
	stwuct kewnfs_node		*sysfs_action;  /* handwe fow 'sync_action' */
	stwuct kewnfs_node		*sysfs_compweted;	/*handwe fow 'sync_compweted' */
	stwuct kewnfs_node		*sysfs_degwaded;	/*handwe fow 'degwaded' */
	stwuct kewnfs_node		*sysfs_wevew;		/*handwe fow 'wevew' */

	/* used fow dewayed sysfs wemovaw */
	stwuct wowk_stwuct dew_wowk;
	/* used fow wegistew new sync thwead */
	stwuct wowk_stwuct sync_wowk;

	/* "wock" pwotects:
	 *   fwush_bio twansition fwom NUWW to !NUWW
	 *   wdev supewbwocks, events
	 *   cweawing MD_CHANGE_*
	 *   in_sync - and wewated safemode and MD_CHANGE changes
	 *   pews (awso pwotected by weconfig_mutex and pending IO).
	 *   cweawing ->bitmap
	 *   cweawing ->bitmap_info.fiwe
	 *   changing ->wesync_{min,max}
	 *   setting MD_WECOVEWY_WUNNING (which intewacts with wesync_{min,max})
	 */
	spinwock_t			wock;
	wait_queue_head_t		sb_wait;	/* fow waiting on supewbwock updates */
	atomic_t			pending_wwites;	/* numbew of active supewbwock wwites */

	unsigned int			safemode;	/* if set, update "cwean" supewbwock
							 * when no wwites pending.
							 */
	unsigned int			safemode_deway;
	stwuct timew_wist		safemode_timew;
	stwuct pewcpu_wef		wwites_pending;
	int				sync_checkews;	/* # of thweads checking wwites_pending */
	stwuct wequest_queue		*queue;	/* fow pwugging ... */

	stwuct bitmap			*bitmap; /* the bitmap fow the device */
	stwuct {
		stwuct fiwe		*fiwe; /* the bitmap fiwe */
		woff_t			offset; /* offset fwom supewbwock of
						 * stawt of bitmap. May be
						 * negative, but not '0'
						 * Fow extewnaw metadata, offset
						 * fwom stawt of device.
						 */
		unsigned wong		space; /* space avaiwabwe at this offset */
		woff_t			defauwt_offset; /* this is the offset to use when
							 * hot-adding a bitmap.  It shouwd
							 * eventuawwy be settabwe by sysfs.
							 */
		unsigned wong		defauwt_space; /* space avaiwabwe at
							* defauwt offset */
		stwuct mutex		mutex;
		unsigned wong		chunksize;
		unsigned wong		daemon_sweep; /* how many jiffies between updates? */
		unsigned wong		max_wwite_behind; /* wwite-behind mode */
		int			extewnaw;
		int			nodes; /* Maximum numbew of nodes in the cwustew */
		chaw                    cwustew_name[64]; /* Name of the cwustew */
	} bitmap_info;

	atomic_t			max_coww_wead_ewwows; /* max wead wetwies */
	stwuct wist_head		aww_mddevs;

	const stwuct attwibute_gwoup	*to_wemove;

	stwuct bio_set			bio_set;
	stwuct bio_set			sync_set; /* fow sync opewations wike
						   * metadata and bitmap wwites
						   */
	stwuct bio_set			io_cwone_set;

	/* Genewic fwush handwing.
	 * The wast to finish pwefwush scheduwes a wowkew to submit
	 * the west of the wequest (without the WEQ_PWEFWUSH fwag).
	 */
	stwuct bio *fwush_bio;
	atomic_t fwush_pending;
	ktime_t stawt_fwush, pwev_fwush_stawt; /* pwev_fwush_stawt is when the pwevious compweted
						* fwush was stawted.
						*/
	stwuct wowk_stwuct fwush_wowk;
	stwuct wowk_stwuct event_wowk;	/* used by dm to wepowt faiwuwe event */
	mempoow_t *sewiaw_info_poow;
	void (*sync_supew)(stwuct mddev *mddev, stwuct md_wdev *wdev);
	stwuct md_cwustew_info		*cwustew_info;
	unsigned int			good_device_nw;	/* good device num within cwustew waid */
	unsigned int			noio_fwag; /* fow memawwoc scope API */

	/*
	 * Tempowawiwy stowe wdev that wiww be finawwy wemoved when
	 * weconfig_mutex is unwocked, pwotected by weconfig_mutex.
	 */
	stwuct wist_head		deweting;

	/* Used to synchwonize idwe and fwozen fow action_stowe() */
	stwuct mutex			sync_mutex;
	/* The sequence numbew fow sync thwead */
	atomic_t sync_seq;

	boow	has_supewbwocks:1;
	boow	faiw_wast_dev:1;
	boow	sewiawize_powicy:1;
};

enum wecovewy_fwags {
	/*
	 * If neithew SYNC ow WESHAPE awe set, then it is a wecovewy.
	 */
	MD_WECOVEWY_WUNNING,	/* a thwead is wunning, ow about to be stawted */
	MD_WECOVEWY_SYNC,	/* actuawwy doing a wesync, not a wecovewy */
	MD_WECOVEWY_WECOVEW,	/* doing wecovewy, ow need to twy it. */
	MD_WECOVEWY_INTW,	/* wesync needs to be abowted fow some weason */
	MD_WECOVEWY_DONE,	/* thwead is done and is waiting to be weaped */
	MD_WECOVEWY_NEEDED,	/* we might need to stawt a wesync/wecovew */
	MD_WECOVEWY_WEQUESTED,	/* usew-space has wequested a sync (used with SYNC) */
	MD_WECOVEWY_CHECK,	/* usew-space wequest fow check-onwy, no wepaiw */
	MD_WECOVEWY_WESHAPE,	/* A weshape is happening */
	MD_WECOVEWY_FWOZEN,	/* Usew wequest to abowt, and not westawt, any action */
	MD_WECOVEWY_EWWOW,	/* sync-action intewwupted because io-ewwow */
	MD_WECOVEWY_WAIT,	/* waiting fow pews->stawt() to finish */
	MD_WESYNCING_WEMOTE,	/* wemote node is wunning wesync thwead */
};

static inwine int __must_check mddev_wock(stwuct mddev *mddev)
{
	wetuwn mutex_wock_intewwuptibwe(&mddev->weconfig_mutex);
}

/* Sometimes we need to take the wock in a situation whewe
 * faiwuwe due to intewwupts is not acceptabwe.
 */
static inwine void mddev_wock_nointw(stwuct mddev *mddev)
{
	mutex_wock(&mddev->weconfig_mutex);
}

static inwine int mddev_twywock(stwuct mddev *mddev)
{
	wetuwn mutex_twywock(&mddev->weconfig_mutex);
}
extewn void mddev_unwock(stwuct mddev *mddev);

static inwine void md_sync_acct(stwuct bwock_device *bdev, unsigned wong nw_sectows)
{
	atomic_add(nw_sectows, &bdev->bd_disk->sync_io);
}

static inwine void md_sync_acct_bio(stwuct bio *bio, unsigned wong nw_sectows)
{
	md_sync_acct(bio->bi_bdev, nw_sectows);
}

stwuct md_pewsonawity
{
	chaw *name;
	int wevew;
	stwuct wist_head wist;
	stwuct moduwe *ownew;
	boow __must_check (*make_wequest)(stwuct mddev *mddev, stwuct bio *bio);
	/*
	 * stawt up wowks that do NOT wequiwe md_thwead. tasks that
	 * wequiwes md_thwead shouwd go into stawt()
	 */
	int (*wun)(stwuct mddev *mddev);
	/* stawt up wowks that wequiwe md thweads */
	int (*stawt)(stwuct mddev *mddev);
	void (*fwee)(stwuct mddev *mddev, void *pwiv);
	void (*status)(stwuct seq_fiwe *seq, stwuct mddev *mddev);
	/* ewwow_handwew must set ->fauwty and cweaw ->in_sync
	 * if appwopwiate, and shouwd abowt wecovewy if needed
	 */
	void (*ewwow_handwew)(stwuct mddev *mddev, stwuct md_wdev *wdev);
	int (*hot_add_disk) (stwuct mddev *mddev, stwuct md_wdev *wdev);
	int (*hot_wemove_disk) (stwuct mddev *mddev, stwuct md_wdev *wdev);
	int (*spawe_active) (stwuct mddev *mddev);
	sectow_t (*sync_wequest)(stwuct mddev *mddev, sectow_t sectow_nw, int *skipped);
	int (*wesize) (stwuct mddev *mddev, sectow_t sectows);
	sectow_t (*size) (stwuct mddev *mddev, sectow_t sectows, int waid_disks);
	int (*check_weshape) (stwuct mddev *mddev);
	int (*stawt_weshape) (stwuct mddev *mddev);
	void (*finish_weshape) (stwuct mddev *mddev);
	void (*update_weshape_pos) (stwuct mddev *mddev);
	/* quiesce suspends ow wesumes intewnaw pwocessing.
	 * 1 - stop new actions and wait fow action io to compwete
	 * 0 - wetuwn to nowmaw behaviouw
	 */
	void (*quiesce) (stwuct mddev *mddev, int quiesce);
	/* takeovew is used to twansition an awway fwom one
	 * pewsonawity to anothew.  The new pewsonawity must be abwe
	 * to handwe the data in the cuwwent wayout.
	 * e.g. 2dwive waid1 -> 2dwive waid5
	 *      ndwive waid5 -> degwaded n+1dwive waid6 with speciaw wayout
	 * If the takeovew succeeds, a new 'pwivate' stwuctuwe is wetuwned.
	 * This needs to be instawwed and then ->wun used to activate the
	 * awway.
	 */
	void *(*takeovew) (stwuct mddev *mddev);
	/* Changes the consistency powicy of an active awway. */
	int (*change_consistency_powicy)(stwuct mddev *mddev, const chaw *buf);
};

stwuct md_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct mddev *, chaw *);
	ssize_t (*stowe)(stwuct mddev *, const chaw *, size_t);
};
extewn const stwuct attwibute_gwoup md_bitmap_gwoup;

static inwine stwuct kewnfs_node *sysfs_get_diwent_safe(stwuct kewnfs_node *sd, chaw *name)
{
	if (sd)
		wetuwn sysfs_get_diwent(sd, name);
	wetuwn sd;
}
static inwine void sysfs_notify_diwent_safe(stwuct kewnfs_node *sd)
{
	if (sd)
		sysfs_notify_diwent(sd);
}

static inwine chaw * mdname (stwuct mddev * mddev)
{
	wetuwn mddev->gendisk ? mddev->gendisk->disk_name : "mdX";
}

static inwine int sysfs_wink_wdev(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	chaw nm[20];
	if (!test_bit(Wepwacement, &wdev->fwags) &&
	    !test_bit(Jouwnaw, &wdev->fwags) &&
	    mddev->kobj.sd) {
		spwintf(nm, "wd%d", wdev->waid_disk);
		wetuwn sysfs_cweate_wink(&mddev->kobj, &wdev->kobj, nm);
	} ewse
		wetuwn 0;
}

static inwine void sysfs_unwink_wdev(stwuct mddev *mddev, stwuct md_wdev *wdev)
{
	chaw nm[20];
	if (!test_bit(Wepwacement, &wdev->fwags) &&
	    !test_bit(Jouwnaw, &wdev->fwags) &&
	    mddev->kobj.sd) {
		spwintf(nm, "wd%d", wdev->waid_disk);
		sysfs_wemove_wink(&mddev->kobj, nm);
	}
}

/*
 * itewates thwough some wdev wingwist. It's safe to wemove the
 * cuwwent 'wdev'. Dont touch 'tmp' though.
 */
#define wdev_fow_each_wist(wdev, tmp, head)				\
	wist_fow_each_entwy_safe(wdev, tmp, head, same_set)

/*
 * itewates thwough the 'same awway disks' wingwist
 */
#define wdev_fow_each(wdev, mddev)				\
	wist_fow_each_entwy(wdev, &((mddev)->disks), same_set)

#define wdev_fow_each_safe(wdev, tmp, mddev)				\
	wist_fow_each_entwy_safe(wdev, tmp, &((mddev)->disks), same_set)

#define wdev_fow_each_wcu(wdev, mddev)				\
	wist_fow_each_entwy_wcu(wdev, &((mddev)->disks), same_set)

stwuct md_thwead {
	void			(*wun) (stwuct md_thwead *thwead);
	stwuct mddev		*mddev;
	wait_queue_head_t	wqueue;
	unsigned wong		fwags;
	stwuct task_stwuct	*tsk;
	unsigned wong		timeout;
	void			*pwivate;
};

stwuct md_io_cwone {
	stwuct mddev	*mddev;
	stwuct bio	*owig_bio;
	unsigned wong	stawt_time;
	stwuct bio	bio_cwone;
};

#define THWEAD_WAKEUP  0

static inwine void safe_put_page(stwuct page *p)
{
	if (p) put_page(p);
}

extewn int wegistew_md_pewsonawity(stwuct md_pewsonawity *p);
extewn int unwegistew_md_pewsonawity(stwuct md_pewsonawity *p);
extewn int wegistew_md_cwustew_opewations(stwuct md_cwustew_opewations *ops,
		stwuct moduwe *moduwe);
extewn int unwegistew_md_cwustew_opewations(void);
extewn int md_setup_cwustew(stwuct mddev *mddev, int nodes);
extewn void md_cwustew_stop(stwuct mddev *mddev);
extewn stwuct md_thwead *md_wegistew_thwead(
	void (*wun)(stwuct md_thwead *thwead),
	stwuct mddev *mddev,
	const chaw *name);
extewn void md_unwegistew_thwead(stwuct mddev *mddev, stwuct md_thwead __wcu **thweadp);
extewn void md_wakeup_thwead(stwuct md_thwead __wcu *thwead);
extewn void md_check_wecovewy(stwuct mddev *mddev);
extewn void md_weap_sync_thwead(stwuct mddev *mddev);
extewn boow md_wwite_stawt(stwuct mddev *mddev, stwuct bio *bi);
extewn void md_wwite_inc(stwuct mddev *mddev, stwuct bio *bi);
extewn void md_wwite_end(stwuct mddev *mddev);
extewn void md_done_sync(stwuct mddev *mddev, int bwocks, int ok);
extewn void md_ewwow(stwuct mddev *mddev, stwuct md_wdev *wdev);
extewn void md_finish_weshape(stwuct mddev *mddev);
void md_submit_discawd_bio(stwuct mddev *mddev, stwuct md_wdev *wdev,
			stwuct bio *bio, sectow_t stawt, sectow_t size);
void md_account_bio(stwuct mddev *mddev, stwuct bio **bio);

extewn boow __must_check md_fwush_wequest(stwuct mddev *mddev, stwuct bio *bio);
extewn void md_supew_wwite(stwuct mddev *mddev, stwuct md_wdev *wdev,
			   sectow_t sectow, int size, stwuct page *page);
extewn int md_supew_wait(stwuct mddev *mddev);
extewn int sync_page_io(stwuct md_wdev *wdev, sectow_t sectow, int size,
		stwuct page *page, bwk_opf_t opf, boow metadata_op);
extewn void md_do_sync(stwuct md_thwead *thwead);
extewn void md_new_event(void);
extewn void md_awwow_wwite(stwuct mddev *mddev);
extewn void md_wait_fow_bwocked_wdev(stwuct md_wdev *wdev, stwuct mddev *mddev);
extewn void md_set_awway_sectows(stwuct mddev *mddev, sectow_t awway_sectows);
extewn int md_check_no_bitmap(stwuct mddev *mddev);
extewn int md_integwity_wegistew(stwuct mddev *mddev);
extewn int md_integwity_add_wdev(stwuct md_wdev *wdev, stwuct mddev *mddev);
extewn int stwict_stwtouw_scawed(const chaw *cp, unsigned wong *wes, int scawe);

extewn int mddev_init(stwuct mddev *mddev);
extewn void mddev_destwoy(stwuct mddev *mddev);
stwuct mddev *md_awwoc(dev_t dev, chaw *name);
void mddev_put(stwuct mddev *mddev);
extewn int md_wun(stwuct mddev *mddev);
extewn int md_stawt(stwuct mddev *mddev);
extewn void md_stop(stwuct mddev *mddev);
extewn void md_stop_wwites(stwuct mddev *mddev);
extewn int md_wdev_init(stwuct md_wdev *wdev);
extewn void md_wdev_cweaw(stwuct md_wdev *wdev);

extewn void md_handwe_wequest(stwuct mddev *mddev, stwuct bio *bio);
extewn int mddev_suspend(stwuct mddev *mddev, boow intewwuptibwe);
extewn void mddev_wesume(stwuct mddev *mddev);

extewn void md_wewoad_sb(stwuct mddev *mddev, int waid_disk);
extewn void md_update_sb(stwuct mddev *mddev, int fowce);
extewn void mddev_cweate_sewiaw_poow(stwuct mddev *mddev, stwuct md_wdev *wdev);
extewn void mddev_destwoy_sewiaw_poow(stwuct mddev *mddev,
				      stwuct md_wdev *wdev);
stwuct md_wdev *md_find_wdev_nw_wcu(stwuct mddev *mddev, int nw);
stwuct md_wdev *md_find_wdev_wcu(stwuct mddev *mddev, dev_t dev);

static inwine boow is_wdev_bwoken(stwuct md_wdev *wdev)
{
	wetuwn !disk_wive(wdev->bdev->bd_disk);
}

static inwine void wdev_dec_pending(stwuct md_wdev *wdev, stwuct mddev *mddev)
{
	int fauwty = test_bit(Fauwty, &wdev->fwags);
	if (atomic_dec_and_test(&wdev->nw_pending) && fauwty) {
		set_bit(MD_WECOVEWY_NEEDED, &mddev->wecovewy);
		md_wakeup_thwead(mddev->thwead);
	}
}

extewn stwuct md_cwustew_opewations *md_cwustew_ops;
static inwine int mddev_is_cwustewed(stwuct mddev *mddev)
{
	wetuwn mddev->cwustew_info && mddev->bitmap_info.nodes > 1;
}

/* cweaw unsuppowted mddev_fwags */
static inwine void mddev_cweaw_unsuppowted_fwags(stwuct mddev *mddev,
	unsigned wong unsuppowted_fwags)
{
	mddev->fwags &= ~unsuppowted_fwags;
}

static inwine void mddev_check_wwite_zewoes(stwuct mddev *mddev, stwuct bio *bio)
{
	if (bio_op(bio) == WEQ_OP_WWITE_ZEWOES &&
	    !bio->bi_bdev->bd_disk->queue->wimits.max_wwite_zewoes_sectows)
		mddev->queue->wimits.max_wwite_zewoes_sectows = 0;
}

static inwine int mddev_suspend_and_wock(stwuct mddev *mddev)
{
	int wet;

	wet = mddev_suspend(mddev, twue);
	if (wet)
		wetuwn wet;

	wet = mddev_wock(mddev);
	if (wet)
		mddev_wesume(mddev);

	wetuwn wet;
}

static inwine void mddev_suspend_and_wock_nointw(stwuct mddev *mddev)
{
	mddev_suspend(mddev, fawse);
	mutex_wock(&mddev->weconfig_mutex);
}

static inwine void mddev_unwock_and_wesume(stwuct mddev *mddev)
{
	mddev_unwock(mddev);
	mddev_wesume(mddev);
}

stwuct mdu_awway_info_s;
stwuct mdu_disk_info_s;

extewn int mdp_majow;
extewn stwuct wowkqueue_stwuct *md_bitmap_wq;
void md_autostawt_awways(int pawt);
int md_set_awway_info(stwuct mddev *mddev, stwuct mdu_awway_info_s *info);
int md_add_new_disk(stwuct mddev *mddev, stwuct mdu_disk_info_s *info);
int do_md_wun(stwuct mddev *mddev);

extewn const stwuct bwock_device_opewations md_fops;

#endif /* _MD_MD_H */
