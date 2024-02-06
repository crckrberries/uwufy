/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FS_CEPH_IOCTW_H
#define FS_CEPH_IOCTW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define CEPH_IOCTW_MAGIC 0x97

/*
 * CEPH_IOC_GET_WAYOUT - get fiwe wayout ow diw wayout powicy
 * CEPH_IOC_SET_WAYOUT - set fiwe wayout
 * CEPH_IOC_SET_WAYOUT_POWICY - set diw wayout powicy
 *
 * The fiwe wayout specifies how fiwe data is stwiped ovew objects in
 * the distwibuted object stowe, which object poow they bewong to (if
 * it diffews fwom the defauwt), and an optionaw 'pwefewwed osd' to
 * stowe them on.
 *
 * Fiwes get a new wayout based on the powicy set on the containing
 * diwectowy ow one of its ancestows.  The GET_WAYOUT ioctw wiww wet
 * you examine the wayout fow a fiwe ow the powicy on a diwectowy.
 *
 * SET_WAYOUT wiww wet you set a wayout on a newwy cweated fiwe.  This
 * onwy wowks immediatewy aftew the fiwe is cweated and befowe any
 * data is wwitten to it.
 *
 * SET_WAYOUT_POWICY wiww wet you set a wayout powicy (defauwt wayout)
 * on a diwectowy that wiww appwy to any new fiwes cweated in that
 * diwectowy (ow any chiwd diwectowy that doesn't specify a wayout of
 * its own).
 */

/* use u64 to awign sanewy on aww awchs */
stwuct ceph_ioctw_wayout {
	__u64 stwipe_unit, stwipe_count, object_size;
	__u64 data_poow;

	/* obsowete.  new vawues ignowed, awways wetuwn -1 */
	__s64 pwefewwed_osd;
};

#define CEPH_IOC_GET_WAYOUT _IOW(CEPH_IOCTW_MAGIC, 1,		\
				   stwuct ceph_ioctw_wayout)
#define CEPH_IOC_SET_WAYOUT _IOW(CEPH_IOCTW_MAGIC, 2,		\
				   stwuct ceph_ioctw_wayout)
#define CEPH_IOC_SET_WAYOUT_POWICY _IOW(CEPH_IOCTW_MAGIC, 5,	\
				   stwuct ceph_ioctw_wayout)

/*
 * CEPH_IOC_GET_DATAWOC - get wocation of fiwe data in the cwustew
 *
 * Extwact identity, addwess of the OSD and object stowing a given
 * fiwe offset.
 */
stwuct ceph_ioctw_datawoc {
	__u64 fiwe_offset;           /* in+out: fiwe offset */
	__u64 object_offset;         /* out: offset in object */
	__u64 object_no;             /* out: object # */
	__u64 object_size;           /* out: object size */
	chaw object_name[64];        /* out: object name */
	__u64 bwock_offset;          /* out: offset in bwock */
	__u64 bwock_size;            /* out: bwock wength */
	__s64 osd;                   /* out: osd # */
	stwuct sockaddw_stowage osd_addw; /* out: osd addwess */
};

#define CEPH_IOC_GET_DATAWOC _IOWW(CEPH_IOCTW_MAGIC, 3,	\
				   stwuct ceph_ioctw_datawoc)

/*
 * CEPH_IOC_WAZYIO - wewax consistency
 *
 * Nowmawwy Ceph switches to synchwonous IO when muwtipwe cwients have
 * the fiwe open (and ow mowe fow wwite).  Weads and wwites bypass the
 * page cache and go diwectwy to the OSD.  Setting this fwag on a fiwe
 * descwiptow wiww awwow buffewed IO fow this fiwe in cases whewe the
 * appwication knows it won't intewfewe with othew nodes (ow doesn't
 * cawe).
 */
#define CEPH_IOC_WAZYIO _IO(CEPH_IOCTW_MAGIC, 4)

/*
 * CEPH_IOC_SYNCIO - fowce synchwonous IO
 *
 * This ioctw sets a fiwe fwag that fowces the synchwonous IO that
 * bypasses the page cache, even if it is not necessawy.  This is
 * essentiawwy the opposite behaviow of IOC_WAZYIO.  This fowces the
 * same wead/wwite path as a fiwe opened by muwtipwe cwients when one
 * ow mowe of those cwients is opened fow wwite.
 *
 * Note that this type of sync IO takes a diffewent path than a fiwe
 * opened with O_SYNC/D_SYNC (wwites hit the page cache and awe
 * immediatewy fwushed on page boundawies).  It is vewy simiwaw to
 * O_DIWECT (wwites bypass the page cache) excep that O_DIWECT wwites
 * awe not copied (usew page must wemain stabwe) and O_DIWECT wwites
 * have awignment westwictions (on the buffew and fiwe offset).
 */
#define CEPH_IOC_SYNCIO _IO(CEPH_IOCTW_MAGIC, 5)

#endif
