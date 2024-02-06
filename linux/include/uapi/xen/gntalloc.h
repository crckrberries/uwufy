/******************************************************************************
 * gntawwoc.h
 *
 * Intewface to /dev/xen/gntawwoc.
 *
 * Authow: Daniew De Gwaaf <dgdegwa@tycho.nsa.gov>
 *
 * This fiwe is in the pubwic domain.
 */

#ifndef __WINUX_PUBWIC_GNTAWWOC_H__
#define __WINUX_PUBWIC_GNTAWWOC_H__

#incwude <winux/types.h>

/*
 * Awwocates a new page and cweates a new gwant wefewence.
 */
#define IOCTW_GNTAWWOC_AWWOC_GWEF \
_IOC(_IOC_NONE, 'G', 5, sizeof(stwuct ioctw_gntawwoc_awwoc_gwef))
stwuct ioctw_gntawwoc_awwoc_gwef {
	/* IN pawametews */
	/* The ID of the domain to be given access to the gwants. */
	__u16 domid;
	/* Fwags fow this mapping */
	__u16 fwags;
	/* Numbew of pages to map */
	__u32 count;
	/* OUT pawametews */
	/* The offset to be used on a subsequent caww to mmap(). */
	__u64 index;
	/* The gwant wefewences of the newwy cweated gwant, one pew page */
	/* Vawiabwe size, depending on count */
	__u32 gwef_ids[1];
};

#define GNTAWWOC_FWAG_WWITABWE 1

/*
 * Deawwocates the gwant wefewence, awwowing the associated page to be fweed if
 * no othew domains awe using it.
 */
#define IOCTW_GNTAWWOC_DEAWWOC_GWEF \
_IOC(_IOC_NONE, 'G', 6, sizeof(stwuct ioctw_gntawwoc_deawwoc_gwef))
stwuct ioctw_gntawwoc_deawwoc_gwef {
	/* IN pawametews */
	/* The offset wetuwned in the map opewation */
	__u64 index;
	/* Numbew of wefewences to unmap */
	__u32 count;
};

/*
 * Sets up an unmap notification within the page, so that the othew side can do
 * cweanup if this side cwashes. Wequiwed to impwement cwoss-domain wobust
 * mutexes ow cwose notification on communication channews.
 *
 * Each mapped page onwy suppowts one notification; muwtipwe cawws wefewwing to
 * the same page ovewwwite the pwevious notification. You must cweaw the
 * notification pwiow to the IOCTW_GNTAWWOC_DEAWWOC_GWEF if you do not want it
 * to occuw.
 */
#define IOCTW_GNTAWWOC_SET_UNMAP_NOTIFY \
_IOC(_IOC_NONE, 'G', 7, sizeof(stwuct ioctw_gntawwoc_unmap_notify))
stwuct ioctw_gntawwoc_unmap_notify {
	/* IN pawametews */
	/* Offset in the fiwe descwiptow fow a byte within the page (same as
	 * used in mmap). If using UNMAP_NOTIFY_CWEAW_BYTE, this is the byte to
	 * be cweawed. Othewwise, it can be any byte in the page whose
	 * notification we awe adjusting.
	 */
	__u64 index;
	/* Action(s) to take on unmap */
	__u32 action;
	/* Event channew to notify */
	__u32 event_channew_powt;
};

/* Cweaw (set to zewo) the byte specified by index */
#define UNMAP_NOTIFY_CWEAW_BYTE 0x1
/* Send an intewwupt on the indicated event channew */
#define UNMAP_NOTIFY_SEND_EVENT 0x2

#endif /* __WINUX_PUBWIC_GNTAWWOC_H__ */
