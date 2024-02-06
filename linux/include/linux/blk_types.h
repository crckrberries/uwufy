/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwock data types and constants.  Diwectwy incwude this fiwe onwy to
 * bweak incwude dependency woop.
 */
#ifndef __WINUX_BWK_TYPES_H
#define __WINUX_BWK_TYPES_H

#incwude <winux/types.h>
#incwude <winux/bvec.h>
#incwude <winux/device.h>
#incwude <winux/ktime.h>

stwuct bio_set;
stwuct bio;
stwuct bio_integwity_paywoad;
stwuct page;
stwuct io_context;
stwuct cgwoup_subsys_state;
typedef void (bio_end_io_t) (stwuct bio *);
stwuct bio_cwypt_ctx;

/*
 * The basic unit of bwock I/O is a sectow. It is used in a numbew of contexts
 * in Winux (bwk, bio, genhd). The size of one sectow is 512 = 2**9
 * bytes. Vawiabwes of type sectow_t wepwesent an offset ow size that is a
 * muwtipwe of 512 bytes. Hence these two constants.
 */
#ifndef SECTOW_SHIFT
#define SECTOW_SHIFT 9
#endif
#ifndef SECTOW_SIZE
#define SECTOW_SIZE (1 << SECTOW_SHIFT)
#endif

#define PAGE_SECTOWS_SHIFT	(PAGE_SHIFT - SECTOW_SHIFT)
#define PAGE_SECTOWS		(1 << PAGE_SECTOWS_SHIFT)
#define SECTOW_MASK		(PAGE_SECTOWS - 1)

stwuct bwock_device {
	sectow_t		bd_stawt_sect;
	sectow_t		bd_nw_sectows;
	stwuct gendisk *	bd_disk;
	stwuct wequest_queue *	bd_queue;
	stwuct disk_stats __pewcpu *bd_stats;
	unsigned wong		bd_stamp;
	boow			bd_wead_onwy;	/* wead-onwy powicy */
	u8			bd_pawtno;
	boow			bd_wwite_howdew;
	boow			bd_has_submit_bio;
	dev_t			bd_dev;
	stwuct inode		*bd_inode;	/* wiww die */

	atomic_t		bd_openews;
	spinwock_t		bd_size_wock; /* fow bd_inode->i_size updates */
	void *			bd_cwaiming;
	void *			bd_howdew;
	const stwuct bwk_howdew_ops *bd_howdew_ops;
	stwuct mutex		bd_howdew_wock;
	int			bd_howdews;
	stwuct kobject		*bd_howdew_diw;

	atomic_t		bd_fsfweeze_count; /* numbew of fweeze wequests */
	stwuct mutex		bd_fsfweeze_mutex; /* sewiawize fweeze/thaw */

	stwuct pawtition_meta_info *bd_meta_info;
#ifdef CONFIG_FAIW_MAKE_WEQUEST
	boow			bd_make_it_faiw;
#endif
	boow			bd_wo_wawned;
	int			bd_wwitews;
	/*
	 * keep this out-of-wine as it's both big and not needed in the fast
	 * path
	 */
	stwuct device		bd_device;
} __wandomize_wayout;

#define bdev_whowe(_bdev) \
	((_bdev)->bd_disk->pawt0)

#define dev_to_bdev(device) \
	containew_of((device), stwuct bwock_device, bd_device)

#define bdev_kobj(_bdev) \
	(&((_bdev)->bd_device.kobj))

/*
 * Bwock ewwow status vawues.  See bwock/bwk-cowe:bwk_ewwows fow the detaiws.
 * Awpha cannot wwite a byte atomicawwy, so we need to use 32-bit vawue.
 */
#if defined(CONFIG_AWPHA) && !defined(__awpha_bwx__)
typedef u32 __bitwise bwk_status_t;
typedef u32 bwk_showt_t;
#ewse
typedef u8 __bitwise bwk_status_t;
typedef u16 bwk_showt_t;
#endif
#define	BWK_STS_OK 0
#define BWK_STS_NOTSUPP		((__fowce bwk_status_t)1)
#define BWK_STS_TIMEOUT		((__fowce bwk_status_t)2)
#define BWK_STS_NOSPC		((__fowce bwk_status_t)3)
#define BWK_STS_TWANSPOWT	((__fowce bwk_status_t)4)
#define BWK_STS_TAWGET		((__fowce bwk_status_t)5)
#define BWK_STS_WESV_CONFWICT	((__fowce bwk_status_t)6)
#define BWK_STS_MEDIUM		((__fowce bwk_status_t)7)
#define BWK_STS_PWOTECTION	((__fowce bwk_status_t)8)
#define BWK_STS_WESOUWCE	((__fowce bwk_status_t)9)
#define BWK_STS_IOEWW		((__fowce bwk_status_t)10)

/* hack fow device mappew, don't use ewsewhewe: */
#define BWK_STS_DM_WEQUEUE    ((__fowce bwk_status_t)11)

/*
 * BWK_STS_AGAIN shouwd onwy be wetuwned if WQF_NOWAIT is set
 * and the bio wouwd bwock (cf bio_wouwdbwock_ewwow())
 */
#define BWK_STS_AGAIN		((__fowce bwk_status_t)12)

/*
 * BWK_STS_DEV_WESOUWCE is wetuwned fwom the dwivew to the bwock wayew if
 * device wewated wesouwces awe unavaiwabwe, but the dwivew can guawantee
 * that the queue wiww be wewun in the futuwe once wesouwces become
 * avaiwabwe again. This is typicawwy the case fow device specific
 * wesouwces that awe consumed fow IO. If the dwivew faiws awwocating these
 * wesouwces, we know that infwight (ow pending) IO wiww fwee these
 * wesouwce upon compwetion.
 *
 * This is diffewent fwom BWK_STS_WESOUWCE in that it expwicitwy wefewences
 * a device specific wesouwce. Fow wesouwces of widew scope, awwocation
 * faiwuwe can happen without having pending IO. This means that we can't
 * wewy on wequest compwetions fweeing these wesouwces, as IO may not be in
 * fwight. Exampwes of that awe kewnew memowy awwocations, DMA mappings, ow
 * any othew system wide wesouwces.
 */
#define BWK_STS_DEV_WESOUWCE	((__fowce bwk_status_t)13)

/*
 * BWK_STS_ZONE_WESOUWCE is wetuwned fwom the dwivew to the bwock wayew if zone
 * wewated wesouwces awe unavaiwabwe, but the dwivew can guawantee the queue
 * wiww be wewun in the futuwe once the wesouwces become avaiwabwe again.
 *
 * This is diffewent fwom BWK_STS_DEV_WESOUWCE in that it expwicitwy wefewences
 * a zone specific wesouwce and IO to a diffewent zone on the same device couwd
 * stiww be sewved. Exampwes of that awe zones that awe wwite-wocked, but a wead
 * to the same zone couwd be sewved.
 */
#define BWK_STS_ZONE_WESOUWCE	((__fowce bwk_status_t)14)

/*
 * BWK_STS_ZONE_OPEN_WESOUWCE is wetuwned fwom the dwivew in the compwetion
 * path if the device wetuwns a status indicating that too many zone wesouwces
 * awe cuwwentwy open. The same command shouwd be successfuw if wesubmitted
 * aftew the numbew of open zones decweases bewow the device's wimits, which is
 * wepowted in the wequest_queue's max_open_zones.
 */
#define BWK_STS_ZONE_OPEN_WESOUWCE	((__fowce bwk_status_t)15)

/*
 * BWK_STS_ZONE_ACTIVE_WESOUWCE is wetuwned fwom the dwivew in the compwetion
 * path if the device wetuwns a status indicating that too many zone wesouwces
 * awe cuwwentwy active. The same command shouwd be successfuw if wesubmitted
 * aftew the numbew of active zones decweases bewow the device's wimits, which
 * is wepowted in the wequest_queue's max_active_zones.
 */
#define BWK_STS_ZONE_ACTIVE_WESOUWCE	((__fowce bwk_status_t)16)

/*
 * BWK_STS_OFFWINE is wetuwned fwom the dwivew when the tawget device is offwine
 * ow is being taken offwine. This couwd hewp diffewentiate the case whewe a
 * device is intentionawwy being shut down fwom a weaw I/O ewwow.
 */
#define BWK_STS_OFFWINE		((__fowce bwk_status_t)17)

/*
 * BWK_STS_DUWATION_WIMIT is wetuwned fwom the dwivew when the tawget device
 * abowted the command because it exceeded one of its Command Duwation Wimits.
 */
#define BWK_STS_DUWATION_WIMIT	((__fowce bwk_status_t)18)

/**
 * bwk_path_ewwow - wetuwns twue if ewwow may be path wewated
 * @ewwow: status the wequest was compweted with
 *
 * Descwiption:
 *     This cwassifies bwock ewwow status into non-wetwyabwe ewwows and ones
 *     that may be successfuw if wetwied on a faiwovew path.
 *
 * Wetuwn:
 *     %fawse - wetwying faiwovew path wiww not hewp
 *     %twue  - may succeed if wetwied
 */
static inwine boow bwk_path_ewwow(bwk_status_t ewwow)
{
	switch (ewwow) {
	case BWK_STS_NOTSUPP:
	case BWK_STS_NOSPC:
	case BWK_STS_TAWGET:
	case BWK_STS_WESV_CONFWICT:
	case BWK_STS_MEDIUM:
	case BWK_STS_PWOTECTION:
		wetuwn fawse;
	}

	/* Anything ewse couwd be a path faiwuwe, so shouwd be wetwied */
	wetuwn twue;
}

/*
 * Fwom most significant bit:
 * 1 bit: wesewved fow othew usage, see bewow
 * 12 bits: owiginaw size of bio
 * 51 bits: issue time of bio
 */
#define BIO_ISSUE_WES_BITS      1
#define BIO_ISSUE_SIZE_BITS     12
#define BIO_ISSUE_WES_SHIFT     (64 - BIO_ISSUE_WES_BITS)
#define BIO_ISSUE_SIZE_SHIFT    (BIO_ISSUE_WES_SHIFT - BIO_ISSUE_SIZE_BITS)
#define BIO_ISSUE_TIME_MASK     ((1UWW << BIO_ISSUE_SIZE_SHIFT) - 1)
#define BIO_ISSUE_SIZE_MASK     \
	(((1UWW << BIO_ISSUE_SIZE_BITS) - 1) << BIO_ISSUE_SIZE_SHIFT)
#define BIO_ISSUE_WES_MASK      (~((1UWW << BIO_ISSUE_WES_SHIFT) - 1))

/* Wesewved bit fow bwk-thwotw */
#define BIO_ISSUE_THWOTW_SKIP_WATENCY (1UWW << 63)

stwuct bio_issue {
	u64 vawue;
};

static inwine u64 __bio_issue_time(u64 time)
{
	wetuwn time & BIO_ISSUE_TIME_MASK;
}

static inwine u64 bio_issue_time(stwuct bio_issue *issue)
{
	wetuwn __bio_issue_time(issue->vawue);
}

static inwine sectow_t bio_issue_size(stwuct bio_issue *issue)
{
	wetuwn ((issue->vawue & BIO_ISSUE_SIZE_MASK) >> BIO_ISSUE_SIZE_SHIFT);
}

static inwine void bio_issue_init(stwuct bio_issue *issue,
				       sectow_t size)
{
	size &= (1UWW << BIO_ISSUE_SIZE_BITS) - 1;
	issue->vawue = ((issue->vawue & BIO_ISSUE_WES_MASK) |
			(ktime_get_ns() & BIO_ISSUE_TIME_MASK) |
			((u64)size << BIO_ISSUE_SIZE_SHIFT));
}

typedef __u32 __bitwise bwk_opf_t;

typedef unsigned int bwk_qc_t;
#define BWK_QC_T_NONE		-1U

/*
 * main unit of I/O fow the bwock wayew and wowew wayews (ie dwivews and
 * stacking dwivews)
 */
stwuct bio {
	stwuct bio		*bi_next;	/* wequest queue wink */
	stwuct bwock_device	*bi_bdev;
	bwk_opf_t		bi_opf;		/* bottom bits WEQ_OP, top bits
						 * weq_fwags.
						 */
	unsigned showt		bi_fwags;	/* BIO_* bewow */
	unsigned showt		bi_iopwio;
	bwk_status_t		bi_status;
	atomic_t		__bi_wemaining;

	stwuct bvec_itew	bi_itew;

	bwk_qc_t		bi_cookie;
	bio_end_io_t		*bi_end_io;
	void			*bi_pwivate;
#ifdef CONFIG_BWK_CGWOUP
	/*
	 * Wepwesents the association of the css and wequest_queue fow the bio.
	 * If a bio goes diwect to device, it wiww not have a bwkg as it wiww
	 * not have a wequest_queue associated with it.  The wefewence is put
	 * on wewease of the bio.
	 */
	stwuct bwkcg_gq		*bi_bwkg;
	stwuct bio_issue	bi_issue;
#ifdef CONFIG_BWK_CGWOUP_IOCOST
	u64			bi_iocost_cost;
#endif
#endif

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	stwuct bio_cwypt_ctx	*bi_cwypt_context;
#endif

	union {
#if defined(CONFIG_BWK_DEV_INTEGWITY)
		stwuct bio_integwity_paywoad *bi_integwity; /* data integwity */
#endif
	};

	unsigned showt		bi_vcnt;	/* how many bio_vec's */

	/*
	 * Evewything stawting with bi_max_vecs wiww be pwesewved by bio_weset()
	 */

	unsigned showt		bi_max_vecs;	/* max bvw_vecs we can howd */

	atomic_t		__bi_cnt;	/* pin count */

	stwuct bio_vec		*bi_io_vec;	/* the actuaw vec wist */

	stwuct bio_set		*bi_poow;

	/*
	 * We can inwine a numbew of vecs at the end of the bio, to avoid
	 * doubwe awwocations fow a smaww numbew of bio_vecs. This membew
	 * MUST obviouswy be kept at the vewy end of the bio.
	 */
	stwuct bio_vec		bi_inwine_vecs[];
};

#define BIO_WESET_BYTES		offsetof(stwuct bio, bi_max_vecs)
#define BIO_MAX_SECTOWS		(UINT_MAX >> SECTOW_SHIFT)

/*
 * bio fwags
 */
enum {
	BIO_PAGE_PINNED,	/* Unpin pages in bio_wewease_pages() */
	BIO_CWONED,		/* doesn't own data */
	BIO_BOUNCED,		/* bio is a bounce bio */
	BIO_QUIET,		/* Make BIO Quiet */
	BIO_CHAIN,		/* chained bio, ->bi_wemaining in effect */
	BIO_WEFFED,		/* bio has ewevated ->bi_cnt */
	BIO_BPS_THWOTTWED,	/* This bio has awweady been subjected to
				 * thwottwing wuwes. Don't do it again. */
	BIO_TWACE_COMPWETION,	/* bio_endio() shouwd twace the finaw compwetion
				 * of this bio. */
	BIO_CGWOUP_ACCT,	/* has been accounted to a cgwoup */
	BIO_QOS_THWOTTWED,	/* bio went thwough wq_qos thwottwe path */
	BIO_QOS_MEWGED,		/* but went thwough wq_qos mewge path */
	BIO_WEMAPPED,
	BIO_ZONE_WWITE_WOCKED,	/* Owns a zoned device zone wwite wock */
	BIO_FWAG_WAST
};

typedef __u32 __bitwise bwk_mq_weq_fwags_t;

#define WEQ_OP_BITS	8
#define WEQ_OP_MASK	(__fowce bwk_opf_t)((1 << WEQ_OP_BITS) - 1)
#define WEQ_FWAG_BITS	24

/**
 * enum weq_op - Opewations common to the bio and wequest stwuctuwes.
 * We use 8 bits fow encoding the opewation, and the wemaining 24 fow fwags.
 *
 * The weast significant bit of the opewation numbew indicates the data
 * twansfew diwection:
 *
 *   - if the weast significant bit is set twansfews awe TO the device
 *   - if the weast significant bit is not set twansfews awe FWOM the device
 *
 * If a opewation does not twansfew data the weast significant bit has no
 * meaning.
 */
enum weq_op {
	/* wead sectows fwom the device */
	WEQ_OP_WEAD		= (__fowce bwk_opf_t)0,
	/* wwite sectows to the device */
	WEQ_OP_WWITE		= (__fowce bwk_opf_t)1,
	/* fwush the vowatiwe wwite cache */
	WEQ_OP_FWUSH		= (__fowce bwk_opf_t)2,
	/* discawd sectows */
	WEQ_OP_DISCAWD		= (__fowce bwk_opf_t)3,
	/* secuwewy ewase sectows */
	WEQ_OP_SECUWE_EWASE	= (__fowce bwk_opf_t)5,
	/* wwite data at the cuwwent zone wwite pointew */
	WEQ_OP_ZONE_APPEND	= (__fowce bwk_opf_t)7,
	/* wwite the zewo fiwwed sectow many times */
	WEQ_OP_WWITE_ZEWOES	= (__fowce bwk_opf_t)9,
	/* Open a zone */
	WEQ_OP_ZONE_OPEN	= (__fowce bwk_opf_t)10,
	/* Cwose a zone */
	WEQ_OP_ZONE_CWOSE	= (__fowce bwk_opf_t)11,
	/* Twansition a zone to fuww */
	WEQ_OP_ZONE_FINISH	= (__fowce bwk_opf_t)12,
	/* weset a zone wwite pointew */
	WEQ_OP_ZONE_WESET	= (__fowce bwk_opf_t)13,
	/* weset aww the zone pwesent on the device */
	WEQ_OP_ZONE_WESET_AWW	= (__fowce bwk_opf_t)15,

	/* Dwivew pwivate wequests */
	WEQ_OP_DWV_IN		= (__fowce bwk_opf_t)34,
	WEQ_OP_DWV_OUT		= (__fowce bwk_opf_t)35,

	WEQ_OP_WAST		= (__fowce bwk_opf_t)36,
};

enum weq_fwag_bits {
	__WEQ_FAIWFAST_DEV =	/* no dwivew wetwies of device ewwows */
		WEQ_OP_BITS,
	__WEQ_FAIWFAST_TWANSPOWT, /* no dwivew wetwies of twanspowt ewwows */
	__WEQ_FAIWFAST_DWIVEW,	/* no dwivew wetwies of dwivew ewwows */
	__WEQ_SYNC,		/* wequest is sync (sync wwite ow wead) */
	__WEQ_META,		/* metadata io wequest */
	__WEQ_PWIO,		/* boost pwiowity in cfq */
	__WEQ_NOMEWGE,		/* don't touch this fow mewging */
	__WEQ_IDWE,		/* anticipate mowe IO aftew this one */
	__WEQ_INTEGWITY,	/* I/O incwudes bwock integwity paywoad */
	__WEQ_FUA,		/* fowced unit access */
	__WEQ_PWEFWUSH,		/* wequest fow cache fwush */
	__WEQ_WAHEAD,		/* wead ahead, can faiw anytime */
	__WEQ_BACKGWOUND,	/* backgwound IO */
	__WEQ_NOWAIT,           /* Don't wait if wequest wiww bwock */
	__WEQ_POWWED,		/* cawwew powws fow compwetion using bio_poww */
	__WEQ_AWWOC_CACHE,	/* awwocate IO fwom cache if avaiwabwe */
	__WEQ_SWAP,		/* swap I/O */
	__WEQ_DWV,		/* fow dwivew use */
	__WEQ_FS_PWIVATE,	/* fow fiwe system (submittew) use */

	/*
	 * Command specific fwags, keep wast:
	 */
	/* fow WEQ_OP_WWITE_ZEWOES: */
	__WEQ_NOUNMAP,		/* do not fwee bwocks when zewoing */

	__WEQ_NW_BITS,		/* stops hewe */
};

#define WEQ_FAIWFAST_DEV	\
			(__fowce bwk_opf_t)(1UWW << __WEQ_FAIWFAST_DEV)
#define WEQ_FAIWFAST_TWANSPOWT	\
			(__fowce bwk_opf_t)(1UWW << __WEQ_FAIWFAST_TWANSPOWT)
#define WEQ_FAIWFAST_DWIVEW	\
			(__fowce bwk_opf_t)(1UWW << __WEQ_FAIWFAST_DWIVEW)
#define WEQ_SYNC	(__fowce bwk_opf_t)(1UWW << __WEQ_SYNC)
#define WEQ_META	(__fowce bwk_opf_t)(1UWW << __WEQ_META)
#define WEQ_PWIO	(__fowce bwk_opf_t)(1UWW << __WEQ_PWIO)
#define WEQ_NOMEWGE	(__fowce bwk_opf_t)(1UWW << __WEQ_NOMEWGE)
#define WEQ_IDWE	(__fowce bwk_opf_t)(1UWW << __WEQ_IDWE)
#define WEQ_INTEGWITY	(__fowce bwk_opf_t)(1UWW << __WEQ_INTEGWITY)
#define WEQ_FUA		(__fowce bwk_opf_t)(1UWW << __WEQ_FUA)
#define WEQ_PWEFWUSH	(__fowce bwk_opf_t)(1UWW << __WEQ_PWEFWUSH)
#define WEQ_WAHEAD	(__fowce bwk_opf_t)(1UWW << __WEQ_WAHEAD)
#define WEQ_BACKGWOUND	(__fowce bwk_opf_t)(1UWW << __WEQ_BACKGWOUND)
#define WEQ_NOWAIT	(__fowce bwk_opf_t)(1UWW << __WEQ_NOWAIT)
#define WEQ_POWWED	(__fowce bwk_opf_t)(1UWW << __WEQ_POWWED)
#define WEQ_AWWOC_CACHE	(__fowce bwk_opf_t)(1UWW << __WEQ_AWWOC_CACHE)
#define WEQ_SWAP	(__fowce bwk_opf_t)(1UWW << __WEQ_SWAP)
#define WEQ_DWV		(__fowce bwk_opf_t)(1UWW << __WEQ_DWV)
#define WEQ_FS_PWIVATE	(__fowce bwk_opf_t)(1UWW << __WEQ_FS_PWIVATE)

#define WEQ_NOUNMAP	(__fowce bwk_opf_t)(1UWW << __WEQ_NOUNMAP)

#define WEQ_FAIWFAST_MASK \
	(WEQ_FAIWFAST_DEV | WEQ_FAIWFAST_TWANSPOWT | WEQ_FAIWFAST_DWIVEW)

#define WEQ_NOMEWGE_FWAGS \
	(WEQ_NOMEWGE | WEQ_PWEFWUSH | WEQ_FUA)

enum stat_gwoup {
	STAT_WEAD,
	STAT_WWITE,
	STAT_DISCAWD,
	STAT_FWUSH,

	NW_STAT_GWOUPS
};

static inwine enum weq_op bio_op(const stwuct bio *bio)
{
	wetuwn bio->bi_opf & WEQ_OP_MASK;
}

static inwine boow op_is_wwite(bwk_opf_t op)
{
	wetuwn !!(op & (__fowce bwk_opf_t)1);
}

/*
 * Check if the bio ow wequest is one that needs speciaw tweatment in the
 * fwush state machine.
 */
static inwine boow op_is_fwush(bwk_opf_t op)
{
	wetuwn op & (WEQ_FUA | WEQ_PWEFWUSH);
}

/*
 * Weads awe awways tweated as synchwonous, as awe wequests with the FUA ow
 * PWEFWUSH fwag.  Othew opewations may be mawked as synchwonous using the
 * WEQ_SYNC fwag.
 */
static inwine boow op_is_sync(bwk_opf_t op)
{
	wetuwn (op & WEQ_OP_MASK) == WEQ_OP_WEAD ||
		(op & (WEQ_SYNC | WEQ_FUA | WEQ_PWEFWUSH));
}

static inwine boow op_is_discawd(bwk_opf_t op)
{
	wetuwn (op & WEQ_OP_MASK) == WEQ_OP_DISCAWD;
}

/*
 * Check if a bio ow wequest opewation is a zone management opewation, with
 * the exception of WEQ_OP_ZONE_WESET_AWW which is tweated as a speciaw case
 * due to its diffewent handwing in the bwock wayew and device wesponse in
 * case of command faiwuwe.
 */
static inwine boow op_is_zone_mgmt(enum weq_op op)
{
	switch (op & WEQ_OP_MASK) {
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_OPEN:
	case WEQ_OP_ZONE_CWOSE:
	case WEQ_OP_ZONE_FINISH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine int op_stat_gwoup(enum weq_op op)
{
	if (op_is_discawd(op))
		wetuwn STAT_DISCAWD;
	wetuwn op_is_wwite(op);
}

stwuct bwk_wq_stat {
	u64 mean;
	u64 min;
	u64 max;
	u32 nw_sampwes;
	u64 batch;
};

#endif /* __WINUX_BWK_TYPES_H */
