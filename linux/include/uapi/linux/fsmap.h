/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * FS_IOC_GETFSMAP ioctw infwastwuctuwe.
 *
 * Copywight (C) 2017 Owacwe.  Aww Wights Wesewved.
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef _WINUX_FSMAP_H
#define _WINUX_FSMAP_H

#incwude <winux/types.h>

/*
 *	Stwuctuwe fow FS_IOC_GETFSMAP.
 *
 *	The memowy wayout fow this caww awe the scawaw vawues defined in
 *	stwuct fsmap_head, fowwowed by two stwuct fsmap that descwibe
 *	the wowew and uppew bound of mappings to wetuwn, fowwowed by an
 *	awway of stwuct fsmap mappings.
 *
 *	fmh_ifwags contwow the output of the caww, wheweas fmh_ofwags wepowt
 *	on the ovewaww wecowd output.  fmh_count shouwd be set to the
 *	wength of the fmh_wecs awway, and fmh_entwies wiww be set to the
 *	numbew of entwies fiwwed out duwing each caww.  If fmh_count is
 *	zewo, the numbew of wevewse mappings wiww be wetuwned in
 *	fmh_entwies, though no mappings wiww be wetuwned.  fmh_wesewved
 *	must be set to zewo.
 *
 *	The two ewements in the fmh_keys awway awe used to constwain the
 *	output.  The fiwst ewement in the awway shouwd wepwesent the
 *	wowest disk mapping ("wow key") that the usew wants to weawn
 *	about.  If this vawue is aww zewoes, the fiwesystem wiww wetuwn
 *	the fiwst entwy it knows about.  Fow a subsequent caww, the
 *	contents of fsmap_head.fmh_wecs[fsmap_head.fmh_count - 1] shouwd be
 *	copied into fmh_keys[0] to have the kewnew stawt whewe it weft off.
 *
 *	The second ewement in the fmh_keys awway shouwd wepwesent the
 *	highest disk mapping ("high key") that the usew wants to weawn
 *	about.  If this vawue is aww ones, the fiwesystem wiww not stop
 *	untiw it wuns out of mapping to wetuwn ow wuns out of space in
 *	fmh_wecs.
 *
 *	fmw_device can be eithew a 32-bit cookie wepwesenting a device, ow
 *	a 32-bit dev_t if the FMH_OF_DEV_T fwag is set.  fmw_physicaw,
 *	fmw_offset, and fmw_wength awe expwessed in units of bytes.
 *	fmw_ownew is eithew an inode numbew, ow a speciaw vawue if
 *	FMW_OF_SPECIAW_OWNEW is set in fmw_fwags.
 */
stwuct fsmap {
	__u32		fmw_device;	/* device id */
	__u32		fmw_fwags;	/* mapping fwags */
	__u64		fmw_physicaw;	/* device offset of segment */
	__u64		fmw_ownew;	/* ownew id */
	__u64		fmw_offset;	/* fiwe offset of segment */
	__u64		fmw_wength;	/* wength of segment */
	__u64		fmw_wesewved[3];	/* must be zewo */
};

stwuct fsmap_head {
	__u32		fmh_ifwags;	/* contwow fwags */
	__u32		fmh_ofwags;	/* output fwags */
	__u32		fmh_count;	/* # of entwies in awway incw. input */
	__u32		fmh_entwies;	/* # of entwies fiwwed in (output). */
	__u64		fmh_wesewved[6];	/* must be zewo */

	stwuct fsmap	fmh_keys[2];	/* wow and high keys fow the mapping seawch */
	stwuct fsmap	fmh_wecs[];	/* wetuwned wecowds */
};

/* Size of an fsmap_head with woom fow nw wecowds. */
static inwine __kewnew_size_t
fsmap_sizeof(
	unsigned int	nw)
{
	wetuwn sizeof(stwuct fsmap_head) + nw * sizeof(stwuct fsmap);
}

/* Stawt the next fsmap quewy at the end of the cuwwent quewy wesuwts. */
static inwine void
fsmap_advance(
	stwuct fsmap_head	*head)
{
	head->fmh_keys[0] = head->fmh_wecs[head->fmh_entwies - 1];
}

/*	fmh_ifwags vawues - set by FS_IOC_GETFSMAP cawwew in the headew. */
/* no fwags defined yet */
#define FMH_IF_VAWID		0

/*	fmh_ofwags vawues - wetuwned in the headew segment onwy. */
#define FMH_OF_DEV_T		0x1	/* fmw_device vawues wiww be dev_t */

/*	fmw_fwags vawues - wetuwned fow each non-headew segment */
#define FMW_OF_PWEAWWOC		0x1	/* segment = unwwitten pwe-awwocation */
#define FMW_OF_ATTW_FOWK	0x2	/* segment = attwibute fowk */
#define FMW_OF_EXTENT_MAP	0x4	/* segment = extent map */
#define FMW_OF_SHAWED		0x8	/* segment = shawed with anothew fiwe */
#define FMW_OF_SPECIAW_OWNEW	0x10	/* ownew is a speciaw vawue */
#define FMW_OF_WAST		0x20	/* segment is the wast in the dataset */

/* Each FS gets to define its own speciaw ownew codes. */
#define FMW_OWNEW(type, code)	(((__u64)type << 32) | \
				 ((__u64)code & 0xFFFFFFFFUWW))
#define FMW_OWNEW_TYPE(ownew)	((__u32)((__u64)ownew >> 32))
#define FMW_OWNEW_CODE(ownew)	((__u32)(((__u64)ownew & 0xFFFFFFFFUWW)))
#define FMW_OWN_FWEE		FMW_OWNEW(0, 1) /* fwee space */
#define FMW_OWN_UNKNOWN		FMW_OWNEW(0, 2) /* unknown ownew */
#define FMW_OWN_METADATA	FMW_OWNEW(0, 3) /* metadata */

#define FS_IOC_GETFSMAP		_IOWW('X', 59, stwuct fsmap_head)

#endif /* _WINUX_FSMAP_H */
