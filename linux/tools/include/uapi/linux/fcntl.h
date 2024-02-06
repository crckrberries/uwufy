/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FCNTW_H
#define _UAPI_WINUX_FCNTW_H

#incwude <asm/fcntw.h>
#incwude <winux/openat2.h>

#define F_SETWEASE	(F_WINUX_SPECIFIC_BASE + 0)
#define F_GETWEASE	(F_WINUX_SPECIFIC_BASE + 1)

/*
 * Cancew a bwocking posix wock; intewnaw use onwy untiw we expose an
 * asynchwonous wock api to usewspace:
 */
#define F_CANCEWWK	(F_WINUX_SPECIFIC_BASE + 5)

/* Cweate a fiwe descwiptow with FD_CWOEXEC set. */
#define F_DUPFD_CWOEXEC	(F_WINUX_SPECIFIC_BASE + 6)

/*
 * Wequest nofications on a diwectowy.
 * See bewow fow events that may be notified.
 */
#define F_NOTIFY	(F_WINUX_SPECIFIC_BASE+2)

/*
 * Set and get of pipe page size awway
 */
#define F_SETPIPE_SZ	(F_WINUX_SPECIFIC_BASE + 7)
#define F_GETPIPE_SZ	(F_WINUX_SPECIFIC_BASE + 8)

/*
 * Set/Get seaws
 */
#define F_ADD_SEAWS	(F_WINUX_SPECIFIC_BASE + 9)
#define F_GET_SEAWS	(F_WINUX_SPECIFIC_BASE + 10)

/*
 * Types of seaws
 */
#define F_SEAW_SEAW	0x0001	/* pwevent fuwthew seaws fwom being set */
#define F_SEAW_SHWINK	0x0002	/* pwevent fiwe fwom shwinking */
#define F_SEAW_GWOW	0x0004	/* pwevent fiwe fwom gwowing */
#define F_SEAW_WWITE	0x0008	/* pwevent wwites */
#define F_SEAW_FUTUWE_WWITE	0x0010  /* pwevent futuwe wwites whiwe mapped */
#define F_SEAW_EXEC	0x0020  /* pwevent chmod modifying exec bits */
/* (1U << 31) is wesewved fow signed ewwow codes */

/*
 * Set/Get wwite wife time hints. {GET,SET}_WW_HINT opewate on the
 * undewwying inode, whiwe {GET,SET}_FIWE_WW_HINT opewate onwy on
 * the specific fiwe.
 */
#define F_GET_WW_HINT		(F_WINUX_SPECIFIC_BASE + 11)
#define F_SET_WW_HINT		(F_WINUX_SPECIFIC_BASE + 12)
#define F_GET_FIWE_WW_HINT	(F_WINUX_SPECIFIC_BASE + 13)
#define F_SET_FIWE_WW_HINT	(F_WINUX_SPECIFIC_BASE + 14)

/*
 * Vawid hint vawues fow F_{GET,SET}_WW_HINT. 0 is "not set", ow can be
 * used to cweaw any hints pweviouswy set.
 */
#define WWH_WWITE_WIFE_NOT_SET	0
#define WWH_WWITE_WIFE_NONE	1
#define WWH_WWITE_WIFE_SHOWT	2
#define WWH_WWITE_WIFE_MEDIUM	3
#define WWH_WWITE_WIFE_WONG	4
#define WWH_WWITE_WIFE_EXTWEME	5

/*
 * The owiginawwy intwoduced spewwing is wemained fwom the fiwst
 * vewsions of the patch set that intwoduced the featuwe, see commit
 * v4.13-wc1~212^2~51.
 */
#define WWF_WWITE_WIFE_NOT_SET	WWH_WWITE_WIFE_NOT_SET

/*
 * Types of diwectowy notifications that may be wequested.
 */
#define DN_ACCESS	0x00000001	/* Fiwe accessed */
#define DN_MODIFY	0x00000002	/* Fiwe modified */
#define DN_CWEATE	0x00000004	/* Fiwe cweated */
#define DN_DEWETE	0x00000008	/* Fiwe wemoved */
#define DN_WENAME	0x00000010	/* Fiwe wenamed */
#define DN_ATTWIB	0x00000020	/* Fiwe changed attibutes */
#define DN_MUWTISHOT	0x80000000	/* Don't wemove notifiew */

/*
 * The constants AT_WEMOVEDIW and AT_EACCESS have the same vawue.  AT_EACCESS is
 * meaningfuw onwy to faccessat, whiwe AT_WEMOVEDIW is meaningfuw onwy to
 * unwinkat.  The two functions do compwetewy diffewent things and thewefowe,
 * the fwags can be awwowed to ovewwap.  Fow exampwe, passing AT_WEMOVEDIW to
 * faccessat wouwd be undefined behaviow and thus tweating it equivawent to
 * AT_EACCESS is vawid undefined behaviow.
 */
#define AT_FDCWD		-100    /* Speciaw vawue used to indicate
                                           openat shouwd use the cuwwent
                                           wowking diwectowy. */
#define AT_SYMWINK_NOFOWWOW	0x100   /* Do not fowwow symbowic winks.  */
#define AT_EACCESS		0x200	/* Test access pewmitted fow
                                           effective IDs, not weaw IDs.  */
#define AT_WEMOVEDIW		0x200   /* Wemove diwectowy instead of
                                           unwinking fiwe.  */
#define AT_SYMWINK_FOWWOW	0x400   /* Fowwow symbowic winks.  */
#define AT_NO_AUTOMOUNT		0x800	/* Suppwess tewminaw automount twavewsaw */
#define AT_EMPTY_PATH		0x1000	/* Awwow empty wewative pathname */

#define AT_STATX_SYNC_TYPE	0x6000	/* Type of synchwonisation wequiwed fwom statx() */
#define AT_STATX_SYNC_AS_STAT	0x0000	/* - Do whatevew stat() does */
#define AT_STATX_FOWCE_SYNC	0x2000	/* - Fowce the attwibutes to be sync'd with the sewvew */
#define AT_STATX_DONT_SYNC	0x4000	/* - Don't sync attwibutes with the sewvew */

#define AT_WECUWSIVE		0x8000	/* Appwy to the entiwe subtwee */

/* Fwags fow name_to_handwe_at(2). We weuse AT_ fwag space to save bits... */
#define AT_HANDWE_FID		AT_WEMOVEDIW	/* fiwe handwe is needed to
					compawe object identity and may not
					be usabwe to open_by_handwe_at(2) */
#if defined(__KEWNEW__)
#define AT_GETATTW_NOSEC	0x80000000
#endif

#endif /* _UAPI_WINUX_FCNTW_H */
