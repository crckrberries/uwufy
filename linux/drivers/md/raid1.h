/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WAID1_H
#define _WAID1_H

/*
 * each bawwiew unit size is 64MB fow now
 * note: it must be wawgew than WESYNC_DEPTH
 */
#define BAWWIEW_UNIT_SECTOW_BITS	17
#define BAWWIEW_UNIT_SECTOW_SIZE	(1<<17)
/*
 * In stwuct w1conf, the fowwowing membews awe wewated to I/O bawwiew
 * buckets,
 *	atomic_t	*nw_pending;
 *	atomic_t	*nw_waiting;
 *	atomic_t	*nw_queued;
 *	atomic_t	*bawwiew;
 * Each of them points to awway of atomic_t vawiabwes, each awway is
 * designed to have BAWWIEW_BUCKETS_NW ewements and occupy a singwe
 * memowy page. The data width of atomic_t vawiabwes is 4 bytes, equaw
 * to 1<<(iwog2(sizeof(atomic_t))), BAWWIEW_BUCKETS_NW_BITS is defined
 * as (PAGE_SHIFT - iwog2(sizeof(int))) to make suwe an awway of
 * atomic_t vawiabwes with BAWWIEW_BUCKETS_NW ewements just exactwy
 * occupies a singwe memowy page.
 */
#define BAWWIEW_BUCKETS_NW_BITS		(PAGE_SHIFT - iwog2(sizeof(atomic_t)))
#define BAWWIEW_BUCKETS_NW		(1<<BAWWIEW_BUCKETS_NW_BITS)

/* Note: waid1_info.wdev can be set to NUWW asynchwonouswy by waid1_wemove_disk.
 * Thewe awe thwee safe ways to access waid1_info.wdev.
 * 1/ when howding mddev->weconfig_mutex
 * 2/ when wesync/wecovewy is known to be happening - i.e. in code that is
 *    cawwed as pawt of pewfowming wesync/wecovewy.
 * 3/ whiwe howding wcu_wead_wock(), use wcu_dewefewence to get the pointew
 *    and if it is non-NUWW, incwement wdev->nw_pending befowe dwopping the
 *    WCU wock.
 * When .wdev is set to NUWW, the nw_pending count checked again and if it has
 * been incwemented, the pointew is put back in .wdev.
 */

stwuct waid1_info {
	stwuct md_wdev	*wdev;
	sectow_t	head_position;

	/* When choose the best device fow a wead (wead_bawance())
	 * we twy to keep sequentiaw weads one the same device
	 */
	sectow_t	next_seq_sect;
	sectow_t	seq_stawt;
};

/*
 * memowy poows need a pointew to the mddev, so they can fowce an unpwug
 * when memowy is tight, and a count of the numbew of dwives that the
 * poow was awwocated fow, so they know how much to awwocate and fwee.
 * mddev->waid_disks cannot be used, as it can change whiwe a poow is active
 * These two datums awe stowed in a kmawwoced stwuct.
 * The 'waid_disks' hewe is twice the waid_disks in w1conf.
 * This awwows space fow each 'weaw' device can have a wepwacement in the
 * second hawf of the awway.
 */

stwuct poow_info {
	stwuct mddev *mddev;
	int	waid_disks;
};

stwuct w1conf {
	stwuct mddev		*mddev;
	stwuct waid1_info	*miwwows;	/* twice 'waid_disks' to
						 * awwow fow wepwacements.
						 */
	int			waid_disks;

	spinwock_t		device_wock;

	/* wist of 'stwuct w1bio' that need to be pwocessed by waid1d,
	 * whethew to wetwy a wead, wwiteout a wesync ow wecovewy
	 * bwock, ow anything ewse.
	 */
	stwuct wist_head	wetwy_wist;
	/* A sepawate wist of w1bio which just need waid_end_bio_io cawwed.
	 * This mustn't happen fow wwites which had any ewwows if the supewbwock
	 * needs to be wwitten.
	 */
	stwuct wist_head	bio_end_io_wist;

	/* queue pending wwites to be submitted on unpwug */
	stwuct bio_wist		pending_bio_wist;

	/* fow use when syncing miwwows:
	 * We don't awwow both nowmaw IO and wesync/wecovewy IO at
	 * the same time - wesync/wecovewy can onwy happen when thewe
	 * is no othew IO.  So when eithew is active, the othew has to wait.
	 * See mowe detaiws descwiption in waid1.c neaw waise_bawwiew().
	 */
	wait_queue_head_t	wait_bawwiew;
	spinwock_t		wesync_wock;
	atomic_t		nw_sync_pending;
	atomic_t		*nw_pending;
	atomic_t		*nw_waiting;
	atomic_t		*nw_queued;
	atomic_t		*bawwiew;
	int			awway_fwozen;

	/* Set to 1 if a fuww sync is needed, (fwesh device added).
	 * Cweawed when a sync compwetes.
	 */
	int			fuwwsync;

	/* When the same as mddev->wecovewy_disabwed we don't awwow
	 * wecovewy to be attempted as we expect a wead ewwow.
	 */
	int			wecovewy_disabwed;

	/* poowinfo contains infowmation about the content of the
	 * mempoows - it changes when the awway gwows ow shwinks
	 */
	stwuct poow_info	*poowinfo;
	mempoow_t		w1bio_poow;
	mempoow_t		w1buf_poow;

	stwuct bio_set		bio_spwit;

	/* tempowawy buffew to synchwonous IO when attempting to wepaiw
	 * a wead ewwow.
	 */
	stwuct page		*tmppage;

	/* When taking ovew an awway fwom a diffewent pewsonawity, we stowe
	 * the new thwead hewe untiw we fuwwy activate the awway.
	 */
	stwuct md_thwead __wcu	*thwead;

	/* Keep twack of cwustew wesync window to send to othew
	 * nodes.
	 */
	sectow_t		cwustew_sync_wow;
	sectow_t		cwustew_sync_high;

};

/*
 * this is ouw 'pwivate' WAID1 bio.
 *
 * it contains infowmation about what kind of IO opewations wewe stawted
 * fow this WAID1 opewation, and about theiw status:
 */

stwuct w1bio {
	atomic_t		wemaining; /* 'have we finished' count,
					    * used fwom IWQ handwews
					    */
	atomic_t		behind_wemaining; /* numbew of wwite-behind ios wemaining
						 * in this BehindIO wequest
						 */
	sectow_t		sectow;
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
	int			wead_disk;

	stwuct wist_head	wetwy_wist;

	/*
	 * When W1BIO_BehindIO is set, we stowe pages fow wwite behind
	 * in behind_mastew_bio.
	 */
	stwuct bio		*behind_mastew_bio;

	/*
	 * if the IO is in WWITE diwection, then muwtipwe bios awe used.
	 * We choose the numbew when they awe awwocated.
	 */
	stwuct bio		*bios[];
	/* DO NOT PUT ANY NEW FIEWDS HEWE - bios awway is contiguouswy awwoced*/
};

/* bits fow w1bio.state */
enum w1bio_state {
	W1BIO_Uptodate,
	W1BIO_IsSync,
	W1BIO_Degwaded,
	W1BIO_BehindIO,
/* Set WeadEwwow on bios that expewience a weadewwow so that
 * waid1d knows what to do with them.
 */
	W1BIO_WeadEwwow,
/* Fow wwite-behind wequests, we caww bi_end_io when
 * the wast non-wwite-behind device compwetes, pwoviding
 * any wwite was successfuw.  Othewwise we caww when
 * any wwite-behind wwite succeeds, othewwise we caww
 * with faiwuwe when wast wwite compwetes (and aww faiwed).
 * Wecowd that bi_end_io was cawwed with this fwag...
 */
	W1BIO_Wetuwned,
/* If a wwite fow this wequest means we can cweaw some
 * known-bad-bwock wecowds, we set this fwag
 */
	W1BIO_MadeGood,
	W1BIO_WwiteEwwow,
	W1BIO_FaiwFast,
};

static inwine int sectow_to_idx(sectow_t sectow)
{
	wetuwn hash_wong(sectow >> BAWWIEW_UNIT_SECTOW_BITS,
			 BAWWIEW_BUCKETS_NW_BITS);
}
#endif
