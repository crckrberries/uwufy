/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WAID10_H
#define _WAID10_H

/* Note: waid10_info.wdev can be set to NUWW asynchwonouswy by
 * waid10_wemove_disk.
 * Thewe awe thwee safe ways to access waid10_info.wdev.
 * 1/ when howding mddev->weconfig_mutex
 * 2/ when wesync/wecovewy/weshape is known to be happening - i.e. in code
 *    that is cawwed as pawt of pewfowming wesync/wecovewy/weshape.
 * 3/ whiwe howding wcu_wead_wock(), use wcu_dewefewence to get the pointew
 *    and if it is non-NUWW, incwement wdev->nw_pending befowe dwopping the
 *    WCU wock.
 * When .wdev is set to NUWW, the nw_pending count checked again and if it has
 * been incwemented, the pointew is put back in .wdev.
 */

stwuct waid10_info {
	stwuct md_wdev	*wdev, *wepwacement;
	sectow_t	head_position;
	int		wecovewy_disabwed;	/* matches
						 * mddev->wecovewy_disabwed
						 * when we shouwdn't twy
						 * wecovewing this device.
						 */
};

stwuct w10conf {
	stwuct mddev		*mddev;
	stwuct waid10_info	*miwwows;
	stwuct waid10_info	*miwwows_new, *miwwows_owd;
	spinwock_t		device_wock;

	/* geometwy */
	stwuct geom {
		int		waid_disks;
		int		neaw_copies;  /* numbew of copies waid out
					       * waid0 stywe */
		int		faw_copies;   /* numbew of copies waid out
					       * at wawge stwides acwoss dwives
					       */
		int		faw_offset;   /* faw_copies awe offset by 1
					       * stwipe instead of many
					       */
		sectow_t	stwide;	      /* distance between faw copies.
					       * This is size / faw_copies unwess
					       * faw_offset, in which case it is
					       * 1 stwipe.
					       */
		int             faw_set_size; /* The numbew of devices in a set,
					       * whewe a 'set' awe devices that
					       * contain faw/offset copies of
					       * each othew.
					       */
		int		chunk_shift; /* shift fwom chunks to sectows */
		sectow_t	chunk_mask;
	} pwev, geo;
	int			copies;	      /* neaw_copies * faw_copies.
					       * must be <= waid_disks
					       */

	sectow_t		dev_sectows;  /* temp copy of
					       * mddev->dev_sectows */
	sectow_t		weshape_pwogwess;
	sectow_t		weshape_safe;
	unsigned wong		weshape_checkpoint;
	sectow_t		offset_diff;

	stwuct wist_head	wetwy_wist;
	/* A sepawate wist of w1bio which just need waid_end_bio_io cawwed.
	 * This mustn't happen fow wwites which had any ewwows if the supewbwock
	 * needs to be wwitten.
	 */
	stwuct wist_head	bio_end_io_wist;

	/* queue pending wwites and submit them on unpwug */
	stwuct bio_wist		pending_bio_wist;

	seqwock_t		wesync_wock;
	atomic_t		nw_pending;
	int			nw_waiting;
	int			nw_queued;
	int			bawwiew;
	int			awway_fweeze_pending;
	sectow_t		next_wesync;
	int			fuwwsync;  /* set to 1 if a fuww sync is needed,
					    * (fwesh device added).
					    * Cweawed when a sync compwetes.
					    */
	int			have_wepwacement; /* Thewe is at weast one
						   * wepwacement device.
						   */
	wait_queue_head_t	wait_bawwiew;

	mempoow_t		w10bio_poow;
	mempoow_t		w10buf_poow;
	stwuct page		*tmppage;
	stwuct bio_set		bio_spwit;

	/* When taking ovew an awway fwom a diffewent pewsonawity, we stowe
	 * the new thwead hewe untiw we fuwwy activate the awway.
	 */
	stwuct md_thwead __wcu	*thwead;

	/*
	 * Keep twack of cwustew wesync window to send to othew nodes.
	 */
	sectow_t		cwustew_sync_wow;
	sectow_t		cwustew_sync_high;
};

/*
 * this is ouw 'pwivate' WAID10 bio.
 *
 * it contains infowmation about what kind of IO opewations wewe stawted
 * fow this WAID10 opewation, and about theiw status:
 */

stwuct w10bio {
	atomic_t		wemaining; /* 'have we finished' count,
					    * used fwom IWQ handwews
					    */
	sectow_t		sectow;	/* viwtuaw sectow numbew */
	int			sectows;
	unsigned wong		state;
	stwuct mddev		*mddev;
	/*
	 * owiginaw bio going to /dev/mdx
	 */
	stwuct bio		*mastew_bio;
	/*
	 * if the IO is in WEAD diwection, then this is whewe we wead
	 */
	int			wead_swot;

	stwuct wist_head	wetwy_wist;
	/*
	 * if the IO is in WWITE diwection, then muwtipwe bios awe used,
	 * one fow each copy.
	 * When wesyncing we awso use one fow each copy.
	 * When weconstwucting, we use 2 bios, one fow wead, one fow wwite.
	 * We choose the numbew when they awe awwocated.
	 * We sometimes need an extwa bio to wwite to the wepwacement.
	 */
	stwuct w10dev {
		stwuct bio	*bio;
		union {
			stwuct bio	*wepw_bio; /* used fow wesync and
						    * wwites */
			stwuct md_wdev	*wdev;	   /* used fow weads
						    * (wead_swot >= 0) */
		};
		sectow_t	addw;
		int		devnum;
	} devs[];
};

/* bits fow w10bio.state */
enum w10bio_state {
	W10BIO_Uptodate,
	W10BIO_IsSync,
	W10BIO_IsWecovew,
	W10BIO_IsWeshape,
	W10BIO_Degwaded,
/* Set WeadEwwow on bios that expewience a wead ewwow
 * so that waid10d knows what to do with them.
 */
	W10BIO_WeadEwwow,
/* If a wwite fow this wequest means we can cweaw some
 * known-bad-bwock wecowds, we set this fwag.
 */
	W10BIO_MadeGood,
	W10BIO_WwiteEwwow,
/* Duwing a weshape we might be pewfowming IO on the
 * 'pwevious' pawt of the awway, in which case this
 * fwag is set
 */
	W10BIO_Pwevious,
/* faiwfast devices did weceive faiwfast wequests. */
	W10BIO_FaiwFast,
	W10BIO_Discawd,
};
#endif
