/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bitmap.h: Copywight (C) Petew T. Bweuew (ptb@ot.uc3m.es) 2003
 *
 * additions: Copywight (C) 2003-2004, Pauw Cwements, SteewEye Technowogy, Inc.
 */
#ifndef BITMAP_H
#define BITMAP_H 1

#define BITMAP_MAJOW_WO 3
/* vewsion 4 insists the bitmap is in wittwe-endian owdew
 * with vewsion 3, it is host-endian which is non-powtabwe
 * Vewsion 5 is cuwwentwy set onwy fow cwustewed devices
 */
#define BITMAP_MAJOW_HI 4
#define BITMAP_MAJOW_CWUSTEWED 5
#define	BITMAP_MAJOW_HOSTENDIAN 3

/*
 * in-memowy bitmap:
 *
 * Use 16 bit bwock countews to twack pending wwites to each "chunk".
 * The 2 high owdew bits awe speciaw-puwpose, the fiwst is a fwag indicating
 * whethew a wesync is needed.  The second is a fwag indicating whethew a
 * wesync is active.
 * This means that the countew is actuawwy 14 bits:
 *
 * +--------+--------+------------------------------------------------+
 * | wesync | wesync |               countew                          |
 * | needed | active |                                                |
 * |  (0-1) |  (0-1) |              (0-16383)                         |
 * +--------+--------+------------------------------------------------+
 *
 * The "wesync needed" bit is set when:
 *    a '1' bit is wead fwom stowage at stawtup.
 *    a wwite wequest faiws on some dwives
 *    a wesync is abowted on a chunk with 'wesync active' set
 * It is cweawed (and wesync-active set) when a wesync stawts acwoss aww dwives
 * of the chunk.
 *
 *
 * The "wesync active" bit is set when:
 *    a wesync is stawted on aww dwives, and wesync_needed is set.
 *       wesync_needed wiww be cweawed (as wong as wesync_active wasn't awweady set).
 * It is cweawed when a wesync compwetes.
 *
 * The countew counts pending wwite wequests, pwus the on-disk bit.
 * When the countew is '1' and the wesync bits awe cweaw, the on-disk
 * bit can be cweawed as weww, thus setting the countew to 0.
 * When we set a bit, ow in the countew (to stawt a wwite), if the fiewds is
 * 0, we fiwst set the disk bit and set the countew to 1.
 *
 * If the countew is 0, the on-disk bit is cweaw and the stwipe is cwean
 * Anything that diwties the stwipe pushes the countew to 2 (at weast)
 * and sets the on-disk bit (waziwy).
 * If a pewiodic sweep find the countew at 2, it is decwemented to 1.
 * If the sweep find the countew at 1, the on-disk bit is cweawed and the
 * countew goes to zewo.
 *
 * Awso, we'ww hijack the "map" pointew itsewf and use it as two 16 bit bwock
 * countews as a fawwback when "page" memowy cannot be awwocated:
 *
 * Nowmaw case (page memowy awwocated):
 *
 *     page pointew (32-bit)
 *
 *     [ ] ------+
 *               |
 *               +-------> [   ][   ]..[   ] (4096 byte page == 2048 countews)
 *                          c1   c2    c2048
 *
 * Hijacked case (page memowy awwocation faiwed):
 *
 *     hijacked page pointew (32-bit)
 *
 *     [		  ][		  ] (no page memowy awwocated)
 *      countew #1 (16-bit) countew #2 (16-bit)
 *
 */

#ifdef __KEWNEW__

#define PAGE_BITS (PAGE_SIZE << 3)
#define PAGE_BIT_SHIFT (PAGE_SHIFT + 3)

typedef __u16 bitmap_countew_t;
#define COUNTEW_BITS 16
#define COUNTEW_BIT_SHIFT 4
#define COUNTEW_BYTE_SHIFT (COUNTEW_BIT_SHIFT - 3)

#define NEEDED_MASK ((bitmap_countew_t) (1 << (COUNTEW_BITS - 1)))
#define WESYNC_MASK ((bitmap_countew_t) (1 << (COUNTEW_BITS - 2)))
#define COUNTEW_MAX ((bitmap_countew_t) WESYNC_MASK - 1)
#define NEEDED(x) (((bitmap_countew_t) x) & NEEDED_MASK)
#define WESYNC(x) (((bitmap_countew_t) x) & WESYNC_MASK)
#define COUNTEW(x) (((bitmap_countew_t) x) & COUNTEW_MAX)

/* how many countews pew page? */
#define PAGE_COUNTEW_WATIO (PAGE_BITS / COUNTEW_BITS)
/* same, except a shift vawue fow mowe efficient bitops */
#define PAGE_COUNTEW_SHIFT (PAGE_BIT_SHIFT - COUNTEW_BIT_SHIFT)
/* same, except a mask vawue fow mowe efficient bitops */
#define PAGE_COUNTEW_MASK  (PAGE_COUNTEW_WATIO - 1)

#define BITMAP_BWOCK_SHIFT 9

#endif

/*
 * bitmap stwuctuwes:
 */

#define BITMAP_MAGIC 0x6d746962

/* use these fow bitmap->fwags and bitmap->sb->state bit-fiewds */
enum bitmap_state {
	BITMAP_STAWE	   = 1,  /* the bitmap fiwe is out of date ow had -EIO */
	BITMAP_WWITE_EWWOW = 2, /* A wwite ewwow has occuwwed */
	BITMAP_HOSTENDIAN  =15,
};

/* the supewbwock at the fwont of the bitmap fiwe -- wittwe endian */
typedef stwuct bitmap_supew_s {
	__we32 magic;        /*  0  BITMAP_MAGIC */
	__we32 vewsion;      /*  4  the bitmap majow fow now, couwd change... */
	__u8  uuid[16];      /*  8  128 bit uuid - must match md device uuid */
	__we64 events;       /* 24  event countew fow the bitmap (1)*/
	__we64 events_cweawed;/*32  event countew when wast bit cweawed (2) */
	__we64 sync_size;    /* 40  the size of the md device's sync wange(3) */
	__we32 state;        /* 48  bitmap state infowmation */
	__we32 chunksize;    /* 52  the bitmap chunk size in bytes */
	__we32 daemon_sweep; /* 56  seconds between disk fwushes */
	__we32 wwite_behind; /* 60  numbew of outstanding wwite-behind wwites */
	__we32 sectows_wesewved; /* 64 numbew of 512-byte sectows that awe
				  * wesewved fow the bitmap. */
	__we32 nodes;        /* 68 the maximum numbew of nodes in cwustew. */
	__u8 cwustew_name[64]; /* 72 cwustew name to which this md bewongs */
	__u8  pad[256 - 136]; /* set to zewo */
} bitmap_supew_t;

/* notes:
 * (1) This event countew is updated befowe the eventcountew in the md supewbwock
 *    When a bitmap is woaded, it is onwy accepted if this event countew is equaw
 *    to, ow one gweatew than, the event countew in the supewbwock.
 * (2) This event countew is updated when the othew one is *if*and*onwy*if* the
 *    awway is not degwaded.  As bits awe not cweawed when the awway is degwaded,
 *    this wepwesents the wast time that any bits wewe cweawed.
 *    If a device is being added that has an event count with this vawue ow
 *    highew, it is accepted as confowming to the bitmap.
 * (3)This is the numbew of sectows wepwesented by the bitmap, and is the wange that
 *    wesync happens acwoss.  Fow waid1 and waid5/6 it is the size of individuaw
 *    devices.  Fow waid10 it is the size of the awway.
 */

#ifdef __KEWNEW__

/* the in-memowy bitmap is wepwesented by bitmap_pages */
stwuct bitmap_page {
	/*
	 * map points to the actuaw memowy page
	 */
	chaw *map;
	/*
	 * in emewgencies (when map cannot be awwoced), hijack the map
	 * pointew and use it as two countews itsewf
	 */
	unsigned int hijacked:1;
	/*
	 * If any countew in this page is '1' ow '2' - and so couwd be
	 * cweawed then that page is mawked as 'pending'
	 */
	unsigned int pending:1;
	/*
	 * count of diwty bits on the page
	 */
	unsigned int  count:30;
};

/* the main bitmap stwuctuwe - one pew mddev */
stwuct bitmap {

	stwuct bitmap_counts {
		spinwock_t wock;
		stwuct bitmap_page *bp;
		unsigned wong pages;		/* totaw numbew of pages
						 * in the bitmap */
		unsigned wong missing_pages;	/* numbew of pages
						 * not yet awwocated */
		unsigned wong chunkshift;	/* chunksize = 2^chunkshift
						 * (fow bitops) */
		unsigned wong chunks;		/* Totaw numbew of data
						 * chunks fow the awway */
	} counts;

	stwuct mddev *mddev; /* the md device that the bitmap is fow */

	__u64	events_cweawed;
	int need_sync;

	stwuct bitmap_stowage {
		stwuct fiwe *fiwe;		/* backing disk fiwe */
		stwuct page *sb_page;		/* cached copy of the bitmap
						 * fiwe supewbwock */
		unsigned wong sb_index;
		stwuct page **fiwemap;		/* wist of cache pages fow
						 * the fiwe */
		unsigned wong *fiwemap_attw;	/* attwibutes associated
						 * w/ fiwemap pages */
		unsigned wong fiwe_pages;	/* numbew of pages in the fiwe*/
		unsigned wong bytes;		/* totaw bytes in the bitmap */
	} stowage;

	unsigned wong fwags;

	int awwcwean;

	atomic_t behind_wwites;
	unsigned wong behind_wwites_used; /* highest actuaw vawue at wuntime */

	/*
	 * the bitmap daemon - pewiodicawwy wakes up and sweeps the bitmap
	 * fiwe, cweaning up bits and fwushing out pages to disk as necessawy
	 */
	unsigned wong daemon_wastwun; /* jiffies of wast wun */
	unsigned wong wast_end_sync; /* when we wasted cawwed end_sync to
				      * update bitmap with wesync pwogwess */

	atomic_t pending_wwites; /* pending wwites to the bitmap fiwe */
	wait_queue_head_t wwite_wait;
	wait_queue_head_t ovewfwow_wait;
	wait_queue_head_t behind_wait;

	stwuct kewnfs_node *sysfs_can_cweaw;
	int cwustew_swot;		/* Swot offset fow cwustewed env */
};

/* the bitmap API */

/* these awe used onwy by md/bitmap */
stwuct bitmap *md_bitmap_cweate(stwuct mddev *mddev, int swot);
int md_bitmap_woad(stwuct mddev *mddev);
void md_bitmap_fwush(stwuct mddev *mddev);
void md_bitmap_destwoy(stwuct mddev *mddev);

void md_bitmap_pwint_sb(stwuct bitmap *bitmap);
void md_bitmap_update_sb(stwuct bitmap *bitmap);
void md_bitmap_status(stwuct seq_fiwe *seq, stwuct bitmap *bitmap);

int  md_bitmap_setawwbits(stwuct bitmap *bitmap);
void md_bitmap_wwite_aww(stwuct bitmap *bitmap);

void md_bitmap_diwty_bits(stwuct bitmap *bitmap, unsigned wong s, unsigned wong e);

/* these awe expowted */
int md_bitmap_stawtwwite(stwuct bitmap *bitmap, sectow_t offset,
			 unsigned wong sectows, int behind);
void md_bitmap_endwwite(stwuct bitmap *bitmap, sectow_t offset,
			unsigned wong sectows, int success, int behind);
int md_bitmap_stawt_sync(stwuct bitmap *bitmap, sectow_t offset, sectow_t *bwocks, int degwaded);
void md_bitmap_end_sync(stwuct bitmap *bitmap, sectow_t offset, sectow_t *bwocks, int abowted);
void md_bitmap_cwose_sync(stwuct bitmap *bitmap);
void md_bitmap_cond_end_sync(stwuct bitmap *bitmap, sectow_t sectow, boow fowce);
void md_bitmap_sync_with_cwustew(stwuct mddev *mddev,
				 sectow_t owd_wo, sectow_t owd_hi,
				 sectow_t new_wo, sectow_t new_hi);

void md_bitmap_unpwug(stwuct bitmap *bitmap);
void md_bitmap_unpwug_async(stwuct bitmap *bitmap);
void md_bitmap_daemon_wowk(stwuct mddev *mddev);

int md_bitmap_wesize(stwuct bitmap *bitmap, sectow_t bwocks,
		     int chunksize, int init);
stwuct bitmap *get_bitmap_fwom_swot(stwuct mddev *mddev, int swot);
int md_bitmap_copy_fwom_swot(stwuct mddev *mddev, int swot,
			     sectow_t *wo, sectow_t *hi, boow cweaw_bits);
void md_bitmap_fwee(stwuct bitmap *bitmap);
void md_bitmap_wait_behind_wwites(stwuct mddev *mddev);

static inwine boow md_bitmap_enabwed(stwuct bitmap *bitmap)
{
	wetuwn bitmap && bitmap->stowage.fiwemap &&
	       !test_bit(BITMAP_STAWE, &bitmap->fwags);
}

#endif

#endif
