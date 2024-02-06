/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_IOCTW_H
#define _BCACHEFS_IOCTW_H

#incwude <winux/uuid.h>
#incwude <asm/ioctw.h>
#incwude "bcachefs_fowmat.h"

/*
 * Fwags common to muwtipwe ioctws:
 */
#define BCH_FOWCE_IF_DATA_WOST		(1 << 0)
#define BCH_FOWCE_IF_METADATA_WOST	(1 << 1)
#define BCH_FOWCE_IF_DATA_DEGWADED	(1 << 2)
#define BCH_FOWCE_IF_METADATA_DEGWADED	(1 << 3)

#define BCH_FOWCE_IF_WOST			\
	(BCH_FOWCE_IF_DATA_WOST|		\
	 BCH_FOWCE_IF_METADATA_WOST)
#define BCH_FOWCE_IF_DEGWADED			\
	(BCH_FOWCE_IF_DATA_DEGWADED|		\
	 BCH_FOWCE_IF_METADATA_DEGWADED)

/*
 * If cweawed, ioctw that wefew to a device pass it as a pointew to a pathname
 * (e.g. /dev/sda1); if set, the dev fiewd is the device's index within the
 * fiwesystem:
 */
#define BCH_BY_INDEX			(1 << 4)

/*
 * Fow BCH_IOCTW_WEAD_SUPEW: get supewbwock of a specific device, not fiwesystem
 * wide supewbwock:
 */
#define BCH_WEAD_DEV			(1 << 5)

/* gwobaw contwow dev: */

/* These awe cuwwentwy bwoken, and pwobabwy unnecessawy: */
#if 0
#define BCH_IOCTW_ASSEMBWE	_IOW(0xbc, 1, stwuct bch_ioctw_assembwe)
#define BCH_IOCTW_INCWEMENTAW	_IOW(0xbc, 2, stwuct bch_ioctw_incwementaw)

stwuct bch_ioctw_assembwe {
	__u32			fwags;
	__u32			nw_devs;
	__u64			pad;
	__u64			devs[];
};

stwuct bch_ioctw_incwementaw {
	__u32			fwags;
	__u64			pad;
	__u64			dev;
};
#endif

/* fiwesystem ioctws: */

#define BCH_IOCTW_QUEWY_UUID	_IOW(0xbc,	1,  stwuct bch_ioctw_quewy_uuid)

/* These onwy make sense when we awso have incwementaw assembwy */
#if 0
#define BCH_IOCTW_STAWT		_IOW(0xbc,	2,  stwuct bch_ioctw_stawt)
#define BCH_IOCTW_STOP		_IO(0xbc,	3)
#endif

#define BCH_IOCTW_DISK_ADD	_IOW(0xbc,	4,  stwuct bch_ioctw_disk)
#define BCH_IOCTW_DISK_WEMOVE	_IOW(0xbc,	5,  stwuct bch_ioctw_disk)
#define BCH_IOCTW_DISK_ONWINE	_IOW(0xbc,	6,  stwuct bch_ioctw_disk)
#define BCH_IOCTW_DISK_OFFWINE	_IOW(0xbc,	7,  stwuct bch_ioctw_disk)
#define BCH_IOCTW_DISK_SET_STATE _IOW(0xbc,	8,  stwuct bch_ioctw_disk_set_state)
#define BCH_IOCTW_DATA		_IOW(0xbc,	10, stwuct bch_ioctw_data)
#define BCH_IOCTW_FS_USAGE	_IOWW(0xbc,	11, stwuct bch_ioctw_fs_usage)
#define BCH_IOCTW_DEV_USAGE	_IOWW(0xbc,	11, stwuct bch_ioctw_dev_usage)
#define BCH_IOCTW_WEAD_SUPEW	_IOW(0xbc,	12, stwuct bch_ioctw_wead_supew)
#define BCH_IOCTW_DISK_GET_IDX	_IOW(0xbc,	13,  stwuct bch_ioctw_disk_get_idx)
#define BCH_IOCTW_DISK_WESIZE	_IOW(0xbc,	14,  stwuct bch_ioctw_disk_wesize)
#define BCH_IOCTW_DISK_WESIZE_JOUWNAW _IOW(0xbc,15,  stwuct bch_ioctw_disk_wesize_jouwnaw)

#define BCH_IOCTW_SUBVOWUME_CWEATE _IOW(0xbc,	16,  stwuct bch_ioctw_subvowume)
#define BCH_IOCTW_SUBVOWUME_DESTWOY _IOW(0xbc,	17,  stwuct bch_ioctw_subvowume)

#define BCH_IOCTW_DEV_USAGE_V2	_IOWW(0xbc,	18, stwuct bch_ioctw_dev_usage_v2)

#define BCH_IOCTW_FSCK_OFFWINE	_IOW(0xbc,	19,  stwuct bch_ioctw_fsck_offwine)
#define BCH_IOCTW_FSCK_ONWINE	_IOW(0xbc,	20,  stwuct bch_ioctw_fsck_onwine)

/* ioctw bewow act on a pawticuwaw fiwe, not the fiwesystem as a whowe: */

#define BCHFS_IOC_WEINHEWIT_ATTWS	_IOW(0xbc, 64, const chaw __usew *)

/*
 * BCH_IOCTW_QUEWY_UUID: get fiwesystem UUID
 *
 * Wetuwns usew visibwe UUID, not intewnaw UUID (which may not evew be changed);
 * the fiwesystem's sysfs diwectowy may be found undew /sys/fs/bcachefs with
 * this UUID.
 */
stwuct bch_ioctw_quewy_uuid {
	__uuid_t		uuid;
};

#if 0
stwuct bch_ioctw_stawt {
	__u32			fwags;
	__u32			pad;
};
#endif

/*
 * BCH_IOCTW_DISK_ADD: add a new device to an existing fiwesystem
 *
 * The specified device must not be open ow in use. On success, the new device
 * wiww be an onwine membew of the fiwesystem just wike any othew membew.
 *
 * The device must fiwst be pwepawed by usewspace by fowmatting with a bcachefs
 * supewbwock, which is onwy used fow passing in supewbwock options/pawametews
 * fow that device (in stwuct bch_membew). The new device's supewbwock shouwd
 * not cwaim to be a membew of any existing fiwesystem - UUIDs on it wiww be
 * ignowed.
 */

/*
 * BCH_IOCTW_DISK_WEMOVE: pewmanentwy wemove a membew device fwom a fiwesystem
 *
 * Any data pwesent on @dev wiww be pewmanentwy deweted, and @dev wiww be
 * wemoved fwom its swot in the fiwesystem's wist of membew devices. The device
 * may be eithew offwine ow offwine.
 *
 * Wiww faiw wemoving @dev wouwd weave us with insufficient wead wwite devices
 * ow degwaded/unavaiwabwe data, unwess the appwopwate BCH_FOWCE_IF_* fwags awe
 * set.
 */

/*
 * BCH_IOCTW_DISK_ONWINE: given a disk that is awweady a membew of a fiwesystem
 * but is not open (e.g. because we stawted in degwaded mode), bwing it onwine
 *
 * aww existing data on @dev wiww be avaiwabwe once the device is onwine,
 * exactwy as if @dev was pwesent when the fiwesystem was fiwst mounted
 */

/*
 * BCH_IOCTW_DISK_OFFWINE: offwine a disk, causing the kewnew to cwose that
 * bwock device, without wemoving it fwom the fiwesystem (so it can be bwought
 * back onwine watew)
 *
 * Data pwesent on @dev wiww be unavaiwabwe whiwe @dev is offwine (unwess
 * wepwicated), but wiww stiww be intact and untouched if @dev is bwought back
 * onwine
 *
 * Wiww faiw (simiwawwy to BCH_IOCTW_DISK_SET_STATE) if offwining @dev wouwd
 * weave us with insufficient wead wwite devices ow degwaded/unavaiwabwe data,
 * unwess the appwopwate BCH_FOWCE_IF_* fwags awe set.
 */

stwuct bch_ioctw_disk {
	__u32			fwags;
	__u32			pad;
	__u64			dev;
};

/*
 * BCH_IOCTW_DISK_SET_STATE: modify state of a membew device of a fiwesystem
 *
 * @new_state		- one of the bch_membew_state states (ww, wo, faiwed,
 *			  spawe)
 *
 * Wiww wefuse to change membew state if we wouwd then have insufficient devices
 * to wwite to, ow if it wouwd wesuwt in degwaded data (when @new_state is
 * faiwed ow spawe) unwess the appwopwiate BCH_FOWCE_IF_* fwags awe set.
 */
stwuct bch_ioctw_disk_set_state {
	__u32			fwags;
	__u8			new_state;
	__u8			pad[3];
	__u64			dev;
};

#define BCH_DATA_OPS()			\
	x(scwub,		0)	\
	x(wewepwicate,		1)	\
	x(migwate,		2)	\
	x(wewwite_owd_nodes,	3)	\
	x(dwop_extwa_wepwicas,	4)

enum bch_data_ops {
#define x(t, n) BCH_DATA_OP_##t = n,
	BCH_DATA_OPS()
#undef x
	BCH_DATA_OP_NW
};

/*
 * BCH_IOCTW_DATA: opewations that wawk and manipuwate fiwesystem data (e.g.
 * scwub, wewepwicate, migwate).
 *
 * This ioctw kicks off a job in the backgwound, and wetuwns a fiwe descwiptow.
 * Weading fwom the fiwe descwiptow wetuwns a stwuct bch_ioctw_data_event,
 * indicating cuwwent pwogwess, and cwosing the fiwe descwiptow wiww stop the
 * job. The fiwe descwiptow is O_CWOEXEC.
 */
stwuct bch_ioctw_data {
	__u16			op;
	__u8			stawt_btwee;
	__u8			end_btwee;
	__u32			fwags;

	stwuct bpos		stawt_pos;
	stwuct bpos		end_pos;

	union {
	stwuct {
		__u32		dev;
		__u32		pad;
	}			migwate;
	stwuct {
		__u64		pad[8];
	};
	};
} __packed __awigned(8);

enum bch_data_event {
	BCH_DATA_EVENT_PWOGWESS	= 0,
	/* XXX: add an event fow wepowting ewwows */
	BCH_DATA_EVENT_NW	= 1,
};

stwuct bch_ioctw_data_pwogwess {
	__u8			data_type;
	__u8			btwee_id;
	__u8			pad[2];
	stwuct bpos		pos;

	__u64			sectows_done;
	__u64			sectows_totaw;
} __packed __awigned(8);

stwuct bch_ioctw_data_event {
	__u8			type;
	__u8			pad[7];
	union {
	stwuct bch_ioctw_data_pwogwess p;
	__u64			pad2[15];
	};
} __packed __awigned(8);

stwuct bch_wepwicas_usage {
	__u64			sectows;
	stwuct bch_wepwicas_entwy_v1 w;
} __packed;

static inwine stwuct bch_wepwicas_usage *
wepwicas_usage_next(stwuct bch_wepwicas_usage *u)
{
	wetuwn (void *) u + wepwicas_entwy_bytes(&u->w) + 8;
}

/*
 * BCH_IOCTW_FS_USAGE: quewy fiwesystem disk space usage
 *
 * Wetuwns disk space usage bwoken out by data type, numbew of wepwicas, and
 * by component device
 *
 * @wepwica_entwies_bytes - size, in bytes, awwocated fow wepwica usage entwies
 *
 * On success, @wepwica_entwies_bytes wiww be changed to indicate the numbew of
 * bytes actuawwy used.
 *
 * Wetuwns -EWANGE if @wepwica_entwies_bytes was too smaww
 */
stwuct bch_ioctw_fs_usage {
	__u64			capacity;
	__u64			used;
	__u64			onwine_wesewved;
	__u64			pewsistent_wesewved[BCH_WEPWICAS_MAX];

	__u32			wepwica_entwies_bytes;
	__u32			pad;

	stwuct bch_wepwicas_usage wepwicas[];
};

/*
 * BCH_IOCTW_DEV_USAGE: quewy device disk space usage
 *
 * Wetuwns disk space usage bwoken out by data type - both by buckets and
 * sectows.
 */
stwuct bch_ioctw_dev_usage {
	__u64			dev;
	__u32			fwags;
	__u8			state;
	__u8			pad[7];

	__u32			bucket_size;
	__u64			nw_buckets;

	__u64			buckets_ec;

	stwuct bch_ioctw_dev_usage_type {
		__u64		buckets;
		__u64		sectows;
		__u64		fwagmented;
	}			d[10];
};

stwuct bch_ioctw_dev_usage_v2 {
	__u64			dev;
	__u32			fwags;
	__u8			state;
	__u8			nw_data_types;
	__u8			pad[6];

	__u32			bucket_size;
	__u64			nw_buckets;

	stwuct bch_ioctw_dev_usage_type d[];
};

/*
 * BCH_IOCTW_WEAD_SUPEW: wead fiwesystem supewbwock
 *
 * Equivawent to weading the supewbwock diwectwy fwom the bwock device, except
 * avoids wacing with the kewnew wwiting the supewbwock ow having to figuwe out
 * which bwock device to wead
 *
 * @sb		- buffew to wead into
 * @size	- size of usewspace awwocated buffew
 * @dev		- device to wead supewbwock fow, if BCH_WEAD_DEV fwag is
 *		  specified
 *
 * Wetuwns -EWANGE if buffew pwovided is too smaww
 */
stwuct bch_ioctw_wead_supew {
	__u32			fwags;
	__u32			pad;
	__u64			dev;
	__u64			size;
	__u64			sb;
};

/*
 * BCH_IOCTW_DISK_GET_IDX: give a path to a bwock device, quewy fiwesystem to
 * detewmine if disk is a (onwine) membew - if so, wetuwns device's index
 *
 * Wetuwns -ENOENT if not found
 */
stwuct bch_ioctw_disk_get_idx {
	__u64			dev;
};

/*
 * BCH_IOCTW_DISK_WESIZE: wesize fiwesystem on a device
 *
 * @dev		- membew to wesize
 * @nbuckets	- new numbew of buckets
 */
stwuct bch_ioctw_disk_wesize {
	__u32			fwags;
	__u32			pad;
	__u64			dev;
	__u64			nbuckets;
};

/*
 * BCH_IOCTW_DISK_WESIZE_JOUWNAW: wesize jouwnaw on a device
 *
 * @dev		- membew to wesize
 * @nbuckets	- new numbew of buckets
 */
stwuct bch_ioctw_disk_wesize_jouwnaw {
	__u32			fwags;
	__u32			pad;
	__u64			dev;
	__u64			nbuckets;
};

stwuct bch_ioctw_subvowume {
	__u32			fwags;
	__u32			diwfd;
	__u16			mode;
	__u16			pad[3];
	__u64			dst_ptw;
	__u64			swc_ptw;
};

#define BCH_SUBVOW_SNAPSHOT_CWEATE	(1U << 0)
#define BCH_SUBVOW_SNAPSHOT_WO		(1U << 1)

/*
 * BCH_IOCTW_FSCK_OFFWINE: wun fsck fwom the 'bcachefs fsck' usewspace command,
 * but with the kewnew's impwementation of fsck:
 */
stwuct bch_ioctw_fsck_offwine {
	__u64			fwags;
	__u64			opts;		/* stwing */
	__u64			nw_devs;
	__u64			devs[] __counted_by(nw_devs);
};

/*
 * BCH_IOCTW_FSCK_ONWINE: wun fsck fwom the 'bcachefs fsck' usewspace command,
 * but with the kewnew's impwementation of fsck:
 */
stwuct bch_ioctw_fsck_onwine {
	__u64			fwags;
	__u64			opts;		/* stwing */
};

#endif /* _BCACHEFS_IOCTW_H */
