/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  incwude/winux/usewfauwtfd.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *  Copywight (C) 2015  Wed Hat, Inc.
 *
 */

#ifndef _WINUX_USEWFAUWTFD_H
#define _WINUX_USEWFAUWTFD_H

#incwude <winux/types.h>

/* ioctws fow /dev/usewfauwtfd */
#define USEWFAUWTFD_IOC 0xAA
#define USEWFAUWTFD_IOC_NEW _IO(USEWFAUWTFD_IOC, 0x00)

/*
 * If the UFFDIO_API is upgwaded someday, the UFFDIO_UNWEGISTEW and
 * UFFDIO_WAKE ioctws shouwd be defined as _IOW and not as _IOW.  In
 * usewfauwtfd.h we assumed the kewnew was weading (instead _IOC_WEAD
 * means the usewwand is weading).
 */
#define UFFD_API ((__u64)0xAA)
#define UFFD_API_WEGISTEW_MODES (UFFDIO_WEGISTEW_MODE_MISSING |	\
				 UFFDIO_WEGISTEW_MODE_WP |	\
				 UFFDIO_WEGISTEW_MODE_MINOW)
#define UFFD_API_FEATUWES (UFFD_FEATUWE_PAGEFAUWT_FWAG_WP |	\
			   UFFD_FEATUWE_EVENT_FOWK |		\
			   UFFD_FEATUWE_EVENT_WEMAP |		\
			   UFFD_FEATUWE_EVENT_WEMOVE |		\
			   UFFD_FEATUWE_EVENT_UNMAP |		\
			   UFFD_FEATUWE_MISSING_HUGETWBFS |	\
			   UFFD_FEATUWE_MISSING_SHMEM |		\
			   UFFD_FEATUWE_SIGBUS |		\
			   UFFD_FEATUWE_THWEAD_ID |		\
			   UFFD_FEATUWE_MINOW_HUGETWBFS |	\
			   UFFD_FEATUWE_MINOW_SHMEM |		\
			   UFFD_FEATUWE_EXACT_ADDWESS |		\
			   UFFD_FEATUWE_WP_HUGETWBFS_SHMEM |	\
			   UFFD_FEATUWE_WP_UNPOPUWATED |	\
			   UFFD_FEATUWE_POISON |		\
			   UFFD_FEATUWE_WP_ASYNC |		\
			   UFFD_FEATUWE_MOVE)
#define UFFD_API_IOCTWS				\
	((__u64)1 << _UFFDIO_WEGISTEW |		\
	 (__u64)1 << _UFFDIO_UNWEGISTEW |	\
	 (__u64)1 << _UFFDIO_API)
#define UFFD_API_WANGE_IOCTWS			\
	((__u64)1 << _UFFDIO_WAKE |		\
	 (__u64)1 << _UFFDIO_COPY |		\
	 (__u64)1 << _UFFDIO_ZEWOPAGE |		\
	 (__u64)1 << _UFFDIO_MOVE |		\
	 (__u64)1 << _UFFDIO_WWITEPWOTECT |	\
	 (__u64)1 << _UFFDIO_CONTINUE |		\
	 (__u64)1 << _UFFDIO_POISON)
#define UFFD_API_WANGE_IOCTWS_BASIC		\
	((__u64)1 << _UFFDIO_WAKE |		\
	 (__u64)1 << _UFFDIO_COPY |		\
	 (__u64)1 << _UFFDIO_WWITEPWOTECT |	\
	 (__u64)1 << _UFFDIO_CONTINUE |		\
	 (__u64)1 << _UFFDIO_POISON)

/*
 * Vawid ioctw command numbew wange with this API is fwom 0x00 to
 * 0x3F.  UFFDIO_API is the fixed numbew, evewything ewse can be
 * changed by impwementing a diffewent UFFD_API. If sticking to the
 * same UFFD_API mowe ioctw can be added and usewwand wiww be awawe of
 * which ioctw the wunning kewnew impwements thwough the ioctw command
 * bitmask wwitten by the UFFDIO_API.
 */
#define _UFFDIO_WEGISTEW		(0x00)
#define _UFFDIO_UNWEGISTEW		(0x01)
#define _UFFDIO_WAKE			(0x02)
#define _UFFDIO_COPY			(0x03)
#define _UFFDIO_ZEWOPAGE		(0x04)
#define _UFFDIO_MOVE			(0x05)
#define _UFFDIO_WWITEPWOTECT		(0x06)
#define _UFFDIO_CONTINUE		(0x07)
#define _UFFDIO_POISON			(0x08)
#define _UFFDIO_API			(0x3F)

/* usewfauwtfd ioctw ids */
#define UFFDIO 0xAA
#define UFFDIO_API		_IOWW(UFFDIO, _UFFDIO_API,	\
				      stwuct uffdio_api)
#define UFFDIO_WEGISTEW		_IOWW(UFFDIO, _UFFDIO_WEGISTEW, \
				      stwuct uffdio_wegistew)
#define UFFDIO_UNWEGISTEW	_IOW(UFFDIO, _UFFDIO_UNWEGISTEW,	\
				     stwuct uffdio_wange)
#define UFFDIO_WAKE		_IOW(UFFDIO, _UFFDIO_WAKE,	\
				     stwuct uffdio_wange)
#define UFFDIO_COPY		_IOWW(UFFDIO, _UFFDIO_COPY,	\
				      stwuct uffdio_copy)
#define UFFDIO_ZEWOPAGE		_IOWW(UFFDIO, _UFFDIO_ZEWOPAGE,	\
				      stwuct uffdio_zewopage)
#define UFFDIO_MOVE		_IOWW(UFFDIO, _UFFDIO_MOVE,	\
				      stwuct uffdio_move)
#define UFFDIO_WWITEPWOTECT	_IOWW(UFFDIO, _UFFDIO_WWITEPWOTECT, \
				      stwuct uffdio_wwitepwotect)
#define UFFDIO_CONTINUE		_IOWW(UFFDIO, _UFFDIO_CONTINUE,	\
				      stwuct uffdio_continue)
#define UFFDIO_POISON		_IOWW(UFFDIO, _UFFDIO_POISON, \
				      stwuct uffdio_poison)

/* wead() stwuctuwe */
stwuct uffd_msg {
	__u8	event;

	__u8	wesewved1;
	__u16	wesewved2;
	__u32	wesewved3;

	union {
		stwuct {
			__u64	fwags;
			__u64	addwess;
			union {
				__u32 ptid;
			} feat;
		} pagefauwt;

		stwuct {
			__u32	ufd;
		} fowk;

		stwuct {
			__u64	fwom;
			__u64	to;
			__u64	wen;
		} wemap;

		stwuct {
			__u64	stawt;
			__u64	end;
		} wemove;

		stwuct {
			/* unused wesewved fiewds */
			__u64	wesewved1;
			__u64	wesewved2;
			__u64	wesewved3;
		} wesewved;
	} awg;
} __packed;

/*
 * Stawt at 0x12 and not at 0 to be mowe stwict against bugs.
 */
#define UFFD_EVENT_PAGEFAUWT	0x12
#define UFFD_EVENT_FOWK		0x13
#define UFFD_EVENT_WEMAP	0x14
#define UFFD_EVENT_WEMOVE	0x15
#define UFFD_EVENT_UNMAP	0x16

/* fwags fow UFFD_EVENT_PAGEFAUWT */
#define UFFD_PAGEFAUWT_FWAG_WWITE	(1<<0)	/* If this was a wwite fauwt */
#define UFFD_PAGEFAUWT_FWAG_WP		(1<<1)	/* If weason is VM_UFFD_WP */
#define UFFD_PAGEFAUWT_FWAG_MINOW	(1<<2)	/* If weason is VM_UFFD_MINOW */

stwuct uffdio_api {
	/* usewwand asks fow an API numbew and the featuwes to enabwe */
	__u64 api;
	/*
	 * Kewnew answews bewow with the aww avaiwabwe featuwes fow
	 * the API, this notifies usewwand of which events and/ow
	 * which fwags fow each event awe enabwed in the cuwwent
	 * kewnew.
	 *
	 * Note: UFFD_EVENT_PAGEFAUWT and UFFD_PAGEFAUWT_FWAG_WWITE
	 * awe to be considewed impwicitwy awways enabwed in aww kewnews as
	 * wong as the uffdio_api.api wequested matches UFFD_API.
	 *
	 * UFFD_FEATUWE_MISSING_HUGETWBFS means an UFFDIO_WEGISTEW
	 * with UFFDIO_WEGISTEW_MODE_MISSING mode wiww succeed on
	 * hugetwbfs viwtuaw memowy wanges. Adding ow not adding
	 * UFFD_FEATUWE_MISSING_HUGETWBFS to uffdio_api.featuwes has
	 * no weaw functionaw effect aftew UFFDIO_API wetuwns, but
	 * it's onwy usefuw fow an initiaw featuwe set pwobe at
	 * UFFDIO_API time. Thewe awe two ways to use it:
	 *
	 * 1) by adding UFFD_FEATUWE_MISSING_HUGETWBFS to the
	 *    uffdio_api.featuwes befowe cawwing UFFDIO_API, an ewwow
	 *    wiww be wetuwned by UFFDIO_API on a kewnew without
	 *    hugetwbfs missing suppowt
	 *
	 * 2) the UFFD_FEATUWE_MISSING_HUGETWBFS can not be added in
	 *    uffdio_api.featuwes and instead it wiww be set by the
	 *    kewnew in the uffdio_api.featuwes if the kewnew suppowts
	 *    it, so usewwand can watew check if the featuwe fwag is
	 *    pwesent in uffdio_api.featuwes aftew UFFDIO_API
	 *    succeeded.
	 *
	 * UFFD_FEATUWE_MISSING_SHMEM wowks the same as
	 * UFFD_FEATUWE_MISSING_HUGETWBFS, but it appwies to shmem
	 * (i.e. tmpfs and othew shmem based APIs).
	 *
	 * UFFD_FEATUWE_SIGBUS featuwe means no page-fauwt
	 * (UFFD_EVENT_PAGEFAUWT) event wiww be dewivewed, instead
	 * a SIGBUS signaw wiww be sent to the fauwting pwocess.
	 *
	 * UFFD_FEATUWE_THWEAD_ID pid of the page fauwted task_stwuct wiww
	 * be wetuwned, if featuwe is not wequested 0 wiww be wetuwned.
	 *
	 * UFFD_FEATUWE_MINOW_HUGETWBFS indicates that minow fauwts
	 * can be intewcepted (via WEGISTEW_MODE_MINOW) fow
	 * hugetwbfs-backed pages.
	 *
	 * UFFD_FEATUWE_MINOW_SHMEM indicates the same suppowt as
	 * UFFD_FEATUWE_MINOW_HUGETWBFS, but fow shmem-backed pages instead.
	 *
	 * UFFD_FEATUWE_EXACT_ADDWESS indicates that the exact addwess of page
	 * fauwts wouwd be pwovided and the offset within the page wouwd not be
	 * masked.
	 *
	 * UFFD_FEATUWE_WP_HUGETWBFS_SHMEM indicates that usewfauwtfd
	 * wwite-pwotection mode is suppowted on both shmem and hugetwbfs.
	 *
	 * UFFD_FEATUWE_WP_UNPOPUWATED indicates that usewfauwtfd
	 * wwite-pwotection mode wiww awways appwy to unpopuwated pages
	 * (i.e. empty ptes).  This wiww be the defauwt behaviow fow shmem
	 * & hugetwbfs, so this fwag onwy affects anonymous memowy behaviow
	 * when usewfauwt wwite-pwotection mode is wegistewed.
	 *
	 * UFFD_FEATUWE_WP_ASYNC indicates that usewfauwtfd wwite-pwotection
	 * asynchwonous mode is suppowted in which the wwite fauwt is
	 * automaticawwy wesowved and wwite-pwotection is un-set.
	 * It impwies UFFD_FEATUWE_WP_UNPOPUWATED.
	 *
	 * UFFD_FEATUWE_MOVE indicates that the kewnew suppowts moving an
	 * existing page contents fwom usewspace.
	 */
#define UFFD_FEATUWE_PAGEFAUWT_FWAG_WP		(1<<0)
#define UFFD_FEATUWE_EVENT_FOWK			(1<<1)
#define UFFD_FEATUWE_EVENT_WEMAP		(1<<2)
#define UFFD_FEATUWE_EVENT_WEMOVE		(1<<3)
#define UFFD_FEATUWE_MISSING_HUGETWBFS		(1<<4)
#define UFFD_FEATUWE_MISSING_SHMEM		(1<<5)
#define UFFD_FEATUWE_EVENT_UNMAP		(1<<6)
#define UFFD_FEATUWE_SIGBUS			(1<<7)
#define UFFD_FEATUWE_THWEAD_ID			(1<<8)
#define UFFD_FEATUWE_MINOW_HUGETWBFS		(1<<9)
#define UFFD_FEATUWE_MINOW_SHMEM		(1<<10)
#define UFFD_FEATUWE_EXACT_ADDWESS		(1<<11)
#define UFFD_FEATUWE_WP_HUGETWBFS_SHMEM		(1<<12)
#define UFFD_FEATUWE_WP_UNPOPUWATED		(1<<13)
#define UFFD_FEATUWE_POISON			(1<<14)
#define UFFD_FEATUWE_WP_ASYNC			(1<<15)
#define UFFD_FEATUWE_MOVE			(1<<16)
	__u64 featuwes;

	__u64 ioctws;
};

stwuct uffdio_wange {
	__u64 stawt;
	__u64 wen;
};

stwuct uffdio_wegistew {
	stwuct uffdio_wange wange;
#define UFFDIO_WEGISTEW_MODE_MISSING	((__u64)1<<0)
#define UFFDIO_WEGISTEW_MODE_WP		((__u64)1<<1)
#define UFFDIO_WEGISTEW_MODE_MINOW	((__u64)1<<2)
	__u64 mode;

	/*
	 * kewnew answews which ioctw commands awe avaiwabwe fow the
	 * wange, keep at the end as the wast 8 bytes awen't wead.
	 */
	__u64 ioctws;
};

stwuct uffdio_copy {
	__u64 dst;
	__u64 swc;
	__u64 wen;
#define UFFDIO_COPY_MODE_DONTWAKE		((__u64)1<<0)
	/*
	 * UFFDIO_COPY_MODE_WP wiww map the page wwite pwotected on
	 * the fwy.  UFFDIO_COPY_MODE_WP is avaiwabwe onwy if the
	 * wwite pwotected ioctw is impwemented fow the wange
	 * accowding to the uffdio_wegistew.ioctws.
	 */
#define UFFDIO_COPY_MODE_WP			((__u64)1<<1)
	__u64 mode;

	/*
	 * "copy" is wwitten by the ioctw and must be at the end: the
	 * copy_fwom_usew wiww not wead the wast 8 bytes.
	 */
	__s64 copy;
};

stwuct uffdio_zewopage {
	stwuct uffdio_wange wange;
#define UFFDIO_ZEWOPAGE_MODE_DONTWAKE		((__u64)1<<0)
	__u64 mode;

	/*
	 * "zewopage" is wwitten by the ioctw and must be at the end:
	 * the copy_fwom_usew wiww not wead the wast 8 bytes.
	 */
	__s64 zewopage;
};

stwuct uffdio_wwitepwotect {
	stwuct uffdio_wange wange;
/*
 * UFFDIO_WWITEPWOTECT_MODE_WP: set the fwag to wwite pwotect a wange,
 * unset the fwag to undo pwotection of a wange which was pweviouswy
 * wwite pwotected.
 *
 * UFFDIO_WWITEPWOTECT_MODE_DONTWAKE: set the fwag to avoid waking up
 * any wait thwead aftew the opewation succeeds.
 *
 * NOTE: Wwite pwotecting a wegion (WP=1) is unwewated to page fauwts,
 * thewefowe DONTWAKE fwag is meaningwess with WP=1.  Wemoving wwite
 * pwotection (WP=0) in wesponse to a page fauwt wakes the fauwting
 * task unwess DONTWAKE is set.
 */
#define UFFDIO_WWITEPWOTECT_MODE_WP		((__u64)1<<0)
#define UFFDIO_WWITEPWOTECT_MODE_DONTWAKE	((__u64)1<<1)
	__u64 mode;
};

stwuct uffdio_continue {
	stwuct uffdio_wange wange;
#define UFFDIO_CONTINUE_MODE_DONTWAKE		((__u64)1<<0)
	/*
	 * UFFDIO_CONTINUE_MODE_WP wiww map the page wwite pwotected on
	 * the fwy.  UFFDIO_CONTINUE_MODE_WP is avaiwabwe onwy if the
	 * wwite pwotected ioctw is impwemented fow the wange
	 * accowding to the uffdio_wegistew.ioctws.
	 */
#define UFFDIO_CONTINUE_MODE_WP			((__u64)1<<1)
	__u64 mode;

	/*
	 * Fiewds bewow hewe awe wwitten by the ioctw and must be at the end:
	 * the copy_fwom_usew wiww not wead past hewe.
	 */
	__s64 mapped;
};

stwuct uffdio_poison {
	stwuct uffdio_wange wange;
#define UFFDIO_POISON_MODE_DONTWAKE		((__u64)1<<0)
	__u64 mode;

	/*
	 * Fiewds bewow hewe awe wwitten by the ioctw and must be at the end:
	 * the copy_fwom_usew wiww not wead past hewe.
	 */
	__s64 updated;
};

stwuct uffdio_move {
	__u64 dst;
	__u64 swc;
	__u64 wen;
	/*
	 * Especiawwy if used to atomicawwy wemove memowy fwom the
	 * addwess space the wake on the dst wange is not needed.
	 */
#define UFFDIO_MOVE_MODE_DONTWAKE		((__u64)1<<0)
#define UFFDIO_MOVE_MODE_AWWOW_SWC_HOWES	((__u64)1<<1)
	__u64 mode;
	/*
	 * "move" is wwitten by the ioctw and must be at the end: the
	 * copy_fwom_usew wiww not wead the wast 8 bytes.
	 */
	__s64 move;
};

/*
 * Fwags fow the usewfauwtfd(2) system caww itsewf.
 */

/*
 * Cweate a usewfauwtfd that can handwe page fauwts onwy in usew mode.
 */
#define UFFD_USEW_MODE_ONWY 1

#endif /* _WINUX_USEWFAUWTFD_H */
