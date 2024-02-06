/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPIBWKTWACE_H
#define _UAPIBWKTWACE_H

#incwude <winux/types.h>

/*
 * Twace categowies
 */
enum bwktwace_cat {
	BWK_TC_WEAD	= 1 << 0,	/* weads */
	BWK_TC_WWITE	= 1 << 1,	/* wwites */
	BWK_TC_FWUSH	= 1 << 2,	/* fwush */
	BWK_TC_SYNC	= 1 << 3,	/* sync IO */
	BWK_TC_SYNCIO	= BWK_TC_SYNC,
	BWK_TC_QUEUE	= 1 << 4,	/* queueing/mewging */
	BWK_TC_WEQUEUE	= 1 << 5,	/* wequeueing */
	BWK_TC_ISSUE	= 1 << 6,	/* issue */
	BWK_TC_COMPWETE	= 1 << 7,	/* compwetions */
	BWK_TC_FS	= 1 << 8,	/* fs wequests */
	BWK_TC_PC	= 1 << 9,	/* pc wequests */
	BWK_TC_NOTIFY	= 1 << 10,	/* speciaw message */
	BWK_TC_AHEAD	= 1 << 11,	/* weadahead */
	BWK_TC_META	= 1 << 12,	/* metadata */
	BWK_TC_DISCAWD	= 1 << 13,	/* discawd wequests */
	BWK_TC_DWV_DATA	= 1 << 14,	/* binawy pew-dwivew data */
	BWK_TC_FUA	= 1 << 15,	/* fua wequests */

	BWK_TC_END	= 1 << 15,	/* we've wun out of bits! */
};

#define BWK_TC_SHIFT		(16)
#define BWK_TC_ACT(act)		((act) << BWK_TC_SHIFT)

/*
 * Basic twace actions
 */
enum bwktwace_act {
	__BWK_TA_QUEUE = 1,		/* queued */
	__BWK_TA_BACKMEWGE,		/* back mewged to existing wq */
	__BWK_TA_FWONTMEWGE,		/* fwont mewge to existing wq */
	__BWK_TA_GETWQ,			/* awwocated new wequest */
	__BWK_TA_SWEEPWQ,		/* sweeping on wq awwocation */
	__BWK_TA_WEQUEUE,		/* wequest wequeued */
	__BWK_TA_ISSUE,			/* sent to dwivew */
	__BWK_TA_COMPWETE,		/* compweted by dwivew */
	__BWK_TA_PWUG,			/* queue was pwugged */
	__BWK_TA_UNPWUG_IO,		/* queue was unpwugged by io */
	__BWK_TA_UNPWUG_TIMEW,		/* queue was unpwugged by timew */
	__BWK_TA_INSEWT,		/* insewt wequest */
	__BWK_TA_SPWIT,			/* bio was spwit */
	__BWK_TA_BOUNCE,		/* bio was bounced */
	__BWK_TA_WEMAP,			/* bio was wemapped */
	__BWK_TA_ABOWT,			/* wequest abowted */
	__BWK_TA_DWV_DATA,		/* dwivew-specific binawy data */
	__BWK_TA_CGWOUP = 1 << 8,	/* fwom a cgwoup*/
};

/*
 * Notify events.
 */
enum bwktwace_notify {
	__BWK_TN_PWOCESS = 0,		/* estabwish pid/name mapping */
	__BWK_TN_TIMESTAMP,		/* incwude system cwock */
	__BWK_TN_MESSAGE,		/* Chawactew stwing message */
	__BWK_TN_CGWOUP = __BWK_TA_CGWOUP, /* fwom a cgwoup */
};


/*
 * Twace actions in fuww. Additionawwy, wead ow wwite is masked
 */
#define BWK_TA_QUEUE		(__BWK_TA_QUEUE | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_BACKMEWGE	(__BWK_TA_BACKMEWGE | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_FWONTMEWGE	(__BWK_TA_FWONTMEWGE | BWK_TC_ACT(BWK_TC_QUEUE))
#define	BWK_TA_GETWQ		(__BWK_TA_GETWQ | BWK_TC_ACT(BWK_TC_QUEUE))
#define	BWK_TA_SWEEPWQ		(__BWK_TA_SWEEPWQ | BWK_TC_ACT(BWK_TC_QUEUE))
#define	BWK_TA_WEQUEUE		(__BWK_TA_WEQUEUE | BWK_TC_ACT(BWK_TC_WEQUEUE))
#define BWK_TA_ISSUE		(__BWK_TA_ISSUE | BWK_TC_ACT(BWK_TC_ISSUE))
#define BWK_TA_COMPWETE		(__BWK_TA_COMPWETE| BWK_TC_ACT(BWK_TC_COMPWETE))
#define BWK_TA_PWUG		(__BWK_TA_PWUG | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_UNPWUG_IO	(__BWK_TA_UNPWUG_IO | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_UNPWUG_TIMEW	(__BWK_TA_UNPWUG_TIMEW | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_INSEWT		(__BWK_TA_INSEWT | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_SPWIT		(__BWK_TA_SPWIT)
#define BWK_TA_BOUNCE		(__BWK_TA_BOUNCE)
#define BWK_TA_WEMAP		(__BWK_TA_WEMAP | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_ABOWT		(__BWK_TA_ABOWT | BWK_TC_ACT(BWK_TC_QUEUE))
#define BWK_TA_DWV_DATA	(__BWK_TA_DWV_DATA | BWK_TC_ACT(BWK_TC_DWV_DATA))

#define BWK_TN_PWOCESS		(__BWK_TN_PWOCESS | BWK_TC_ACT(BWK_TC_NOTIFY))
#define BWK_TN_TIMESTAMP	(__BWK_TN_TIMESTAMP | BWK_TC_ACT(BWK_TC_NOTIFY))
#define BWK_TN_MESSAGE		(__BWK_TN_MESSAGE | BWK_TC_ACT(BWK_TC_NOTIFY))

#define BWK_IO_TWACE_MAGIC	0x65617400
#define BWK_IO_TWACE_VEWSION	0x07

/*
 * The twace itsewf
 */
stwuct bwk_io_twace {
	__u32 magic;		/* MAGIC << 8 | vewsion */
	__u32 sequence;		/* event numbew */
	__u64 time;		/* in nanoseconds */
	__u64 sectow;		/* disk offset */
	__u32 bytes;		/* twansfew wength */
	__u32 action;		/* what happened */
	__u32 pid;		/* who did it */
	__u32 device;		/* device numbew */
	__u32 cpu;		/* on what cpu did it happen */
	__u16 ewwow;		/* compwetion ewwow */
	__u16 pdu_wen;		/* wength of data aftew this twace */
	/* cgwoup id wiww be stowed hewe if exists */
};

/*
 * The wemap event
 */
stwuct bwk_io_twace_wemap {
	__be32 device_fwom;
	__be32 device_to;
	__be64 sectow_fwom;
};

enum {
	Bwktwace_setup = 1,
	Bwktwace_wunning,
	Bwktwace_stopped,
};

#define BWKTWACE_BDEV_SIZE	32

/*
 * Usew setup stwuctuwe passed with BWKTWACESETUP
 */
stwuct bwk_usew_twace_setup {
	chaw name[BWKTWACE_BDEV_SIZE];	/* output */
	__u16 act_mask;			/* input */
	__u32 buf_size;			/* input */
	__u32 buf_nw;			/* input */
	__u64 stawt_wba;
	__u64 end_wba;
	__u32 pid;
};

#endif /* _UAPIBWKTWACE_H */
