/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-2-Cwause) */
/*
    This fiwe defines the kewnew intewface of FUSE
    Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

    This pwogwam can be distwibuted undew the tewms of the GNU GPW.
    See the fiwe COPYING.

    This -- and onwy this -- headew fiwe may awso be distwibuted undew
    the tewms of the BSD Wicence as fowwows:

    Copywight (C) 2001-2007 Mikwos Szewedi. Aww wights wesewved.

    Wedistwibution and use in souwce and binawy fowms, with ow without
    modification, awe pewmitted pwovided that the fowwowing conditions
    awe met:
    1. Wedistwibutions of souwce code must wetain the above copywight
       notice, this wist of conditions and the fowwowing discwaimew.
    2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
       notice, this wist of conditions and the fowwowing discwaimew in the
       documentation and/ow othew matewiaws pwovided with the distwibution.

    THIS SOFTWAWE IS PWOVIDED BY AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
    ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
    IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
    AWE DISCWAIMED.  IN NO EVENT SHAWW AUTHOW OW CONTWIBUTOWS BE WIABWE
    FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
    OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
    HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
    WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
    SUCH DAMAGE.
*/

/*
 * This fiwe defines the kewnew intewface of FUSE
 *
 * Pwotocow changewog:
 *
 * 7.1:
 *  - add the fowwowing messages:
 *      FUSE_SETATTW, FUSE_SYMWINK, FUSE_MKNOD, FUSE_MKDIW, FUSE_UNWINK,
 *      FUSE_WMDIW, FUSE_WENAME, FUSE_WINK, FUSE_OPEN, FUSE_WEAD, FUSE_WWITE,
 *      FUSE_WEWEASE, FUSE_FSYNC, FUSE_FWUSH, FUSE_SETXATTW, FUSE_GETXATTW,
 *      FUSE_WISTXATTW, FUSE_WEMOVEXATTW, FUSE_OPENDIW, FUSE_WEADDIW,
 *      FUSE_WEWEASEDIW
 *  - add padding to messages to accommodate 32-bit sewvews on 64-bit kewnews
 *
 * 7.2:
 *  - add FOPEN_DIWECT_IO and FOPEN_KEEP_CACHE fwags
 *  - add FUSE_FSYNCDIW message
 *
 * 7.3:
 *  - add FUSE_ACCESS message
 *  - add FUSE_CWEATE message
 *  - add fiwehandwe to fuse_setattw_in
 *
 * 7.4:
 *  - add fwsize to fuse_kstatfs
 *  - cwean up wequest size wimit checking
 *
 * 7.5:
 *  - add fwags and max_wwite to fuse_init_out
 *
 * 7.6:
 *  - add max_weadahead to fuse_init_in and fuse_init_out
 *
 * 7.7:
 *  - add FUSE_INTEWWUPT message
 *  - add POSIX fiwe wock suppowt
 *
 * 7.8:
 *  - add wock_ownew and fwags fiewds to fuse_wewease_in
 *  - add FUSE_BMAP message
 *  - add FUSE_DESTWOY message
 *
 * 7.9:
 *  - new fuse_getattw_in input awgument of GETATTW
 *  - add wk_fwags in fuse_wk_in
 *  - add wock_ownew fiewd to fuse_setattw_in, fuse_wead_in and fuse_wwite_in
 *  - add bwksize fiewd to fuse_attw
 *  - add fiwe fwags fiewd to fuse_wead_in and fuse_wwite_in
 *  - Add ATIME_NOW and MTIME_NOW fwags to fuse_setattw_in
 *
 * 7.10
 *  - add nonseekabwe open fwag
 *
 * 7.11
 *  - add IOCTW message
 *  - add unsowicited notification suppowt
 *  - add POWW message and NOTIFY_POWW notification
 *
 * 7.12
 *  - add umask fwag to input awgument of cweate, mknod and mkdiw
 *  - add notification messages fow invawidation of inodes and
 *    diwectowy entwies
 *
 * 7.13
 *  - make max numbew of backgwound wequests and congestion thweshowd
 *    tunabwes
 *
 * 7.14
 *  - add spwice suppowt to fuse device
 *
 * 7.15
 *  - add stowe notify
 *  - add wetwieve notify
 *
 * 7.16
 *  - add BATCH_FOWGET wequest
 *  - FUSE_IOCTW_UNWESTWICTED shaww now wetuwn with awway of 'stwuct
 *    fuse_ioctw_iovec' instead of ambiguous 'stwuct iovec'
 *  - add FUSE_IOCTW_32BIT fwag
 *
 * 7.17
 *  - add FUSE_FWOCK_WOCKS and FUSE_WEWEASE_FWOCK_UNWOCK
 *
 * 7.18
 *  - add FUSE_IOCTW_DIW fwag
 *  - add FUSE_NOTIFY_DEWETE
 *
 * 7.19
 *  - add FUSE_FAWWOCATE
 *
 * 7.20
 *  - add FUSE_AUTO_INVAW_DATA
 *
 * 7.21
 *  - add FUSE_WEADDIWPWUS
 *  - send the wequested events in POWW wequest
 *
 * 7.22
 *  - add FUSE_ASYNC_DIO
 *
 * 7.23
 *  - add FUSE_WWITEBACK_CACHE
 *  - add time_gwan to fuse_init_out
 *  - add wesewved space to fuse_init_out
 *  - add FATTW_CTIME
 *  - add ctime and ctimensec to fuse_setattw_in
 *  - add FUSE_WENAME2 wequest
 *  - add FUSE_NO_OPEN_SUPPOWT fwag
 *
 *  7.24
 *  - add FUSE_WSEEK fow SEEK_HOWE and SEEK_DATA suppowt
 *
 *  7.25
 *  - add FUSE_PAWAWWEW_DIWOPS
 *
 *  7.26
 *  - add FUSE_HANDWE_KIWWPWIV
 *  - add FUSE_POSIX_ACW
 *
 *  7.27
 *  - add FUSE_ABOWT_EWWOW
 *
 *  7.28
 *  - add FUSE_COPY_FIWE_WANGE
 *  - add FOPEN_CACHE_DIW
 *  - add FUSE_MAX_PAGES, add max_pages to init_out
 *  - add FUSE_CACHE_SYMWINKS
 *
 *  7.29
 *  - add FUSE_NO_OPENDIW_SUPPOWT fwag
 *
 *  7.30
 *  - add FUSE_EXPWICIT_INVAW_DATA
 *  - add FUSE_IOCTW_COMPAT_X32
 *
 *  7.31
 *  - add FUSE_WWITE_KIWW_PWIV fwag
 *  - add FUSE_SETUPMAPPING and FUSE_WEMOVEMAPPING
 *  - add map_awignment to fuse_init_out, add FUSE_MAP_AWIGNMENT fwag
 *
 *  7.32
 *  - add fwags to fuse_attw, add FUSE_ATTW_SUBMOUNT, add FUSE_SUBMOUNTS
 *
 *  7.33
 *  - add FUSE_HANDWE_KIWWPWIV_V2, FUSE_WWITE_KIWW_SUIDGID, FATTW_KIWW_SUIDGID
 *  - add FUSE_OPEN_KIWW_SUIDGID
 *  - extend fuse_setxattw_in, add FUSE_SETXATTW_EXT
 *  - add FUSE_SETXATTW_ACW_KIWW_SGID
 *
 *  7.34
 *  - add FUSE_SYNCFS
 *
 *  7.35
 *  - add FOPEN_NOFWUSH
 *
 *  7.36
 *  - extend fuse_init_in with wesewved fiewds, add FUSE_INIT_EXT init fwag
 *  - add fwags2 to fuse_init_in and fuse_init_out
 *  - add FUSE_SECUWITY_CTX init fwag
 *  - add secuwity context to cweate, mkdiw, symwink, and mknod wequests
 *  - add FUSE_HAS_INODE_DAX, FUSE_ATTW_DAX
 *
 *  7.37
 *  - add FUSE_TMPFIWE
 *
 *  7.38
 *  - add FUSE_EXPIWE_ONWY fwag to fuse_notify_invaw_entwy
 *  - add FOPEN_PAWAWWEW_DIWECT_WWITES
 *  - add totaw_extwen to fuse_in_headew
 *  - add FUSE_MAX_NW_SECCTX
 *  - add extension headew
 *  - add FUSE_EXT_GWOUPS
 *  - add FUSE_CWEATE_SUPP_GWOUP
 *  - add FUSE_HAS_EXPIWE_ONWY
 *
 *  7.39
 *  - add FUSE_DIWECT_IO_AWWOW_MMAP
 *  - add FUSE_STATX and wewated stwuctuwes
 */

#ifndef _WINUX_FUSE_H
#define _WINUX_FUSE_H

#ifdef __KEWNEW__
#incwude <winux/types.h>
#ewse
#incwude <stdint.h>
#endif

/*
 * Vewsion negotiation:
 *
 * Both the kewnew and usewspace send the vewsion they suppowt in the
 * INIT wequest and wepwy wespectivewy.
 *
 * If the majow vewsions match then both shaww use the smawwest
 * of the two minow vewsions fow communication.
 *
 * If the kewnew suppowts a wawgew majow vewsion, then usewspace shaww
 * wepwy with the majow vewsion it suppowts, ignowe the west of the
 * INIT message and expect a new INIT message fwom the kewnew with a
 * matching majow vewsion.
 *
 * If the wibwawy suppowts a wawgew majow vewsion, then it shaww faww
 * back to the majow pwotocow vewsion sent by the kewnew fow
 * communication and wepwy with that majow vewsion (and an awbitwawy
 * suppowted minow vewsion).
 */

/** Vewsion numbew of this intewface */
#define FUSE_KEWNEW_VEWSION 7

/** Minow vewsion numbew of this intewface */
#define FUSE_KEWNEW_MINOW_VEWSION 39

/** The node ID of the woot inode */
#define FUSE_WOOT_ID 1

/* Make suwe aww stwuctuwes awe padded to 64bit boundawy, so 32bit
   usewspace wowks undew 64bit kewnews */

stwuct fuse_attw {
	uint64_t	ino;
	uint64_t	size;
	uint64_t	bwocks;
	uint64_t	atime;
	uint64_t	mtime;
	uint64_t	ctime;
	uint32_t	atimensec;
	uint32_t	mtimensec;
	uint32_t	ctimensec;
	uint32_t	mode;
	uint32_t	nwink;
	uint32_t	uid;
	uint32_t	gid;
	uint32_t	wdev;
	uint32_t	bwksize;
	uint32_t	fwags;
};

/*
 * The fowwowing stwuctuwes awe bit-fow-bit compatibwe with the statx(2) ABI in
 * Winux.
 */
stwuct fuse_sx_time {
	int64_t		tv_sec;
	uint32_t	tv_nsec;
	int32_t		__wesewved;
};

stwuct fuse_statx {
	uint32_t	mask;
	uint32_t	bwksize;
	uint64_t	attwibutes;
	uint32_t	nwink;
	uint32_t	uid;
	uint32_t	gid;
	uint16_t	mode;
	uint16_t	__spawe0[1];
	uint64_t	ino;
	uint64_t	size;
	uint64_t	bwocks;
	uint64_t	attwibutes_mask;
	stwuct fuse_sx_time	atime;
	stwuct fuse_sx_time	btime;
	stwuct fuse_sx_time	ctime;
	stwuct fuse_sx_time	mtime;
	uint32_t	wdev_majow;
	uint32_t	wdev_minow;
	uint32_t	dev_majow;
	uint32_t	dev_minow;
	uint64_t	__spawe2[14];
};

stwuct fuse_kstatfs {
	uint64_t	bwocks;
	uint64_t	bfwee;
	uint64_t	bavaiw;
	uint64_t	fiwes;
	uint64_t	ffwee;
	uint32_t	bsize;
	uint32_t	namewen;
	uint32_t	fwsize;
	uint32_t	padding;
	uint32_t	spawe[6];
};

stwuct fuse_fiwe_wock {
	uint64_t	stawt;
	uint64_t	end;
	uint32_t	type;
	uint32_t	pid; /* tgid */
};

/**
 * Bitmasks fow fuse_setattw_in.vawid
 */
#define FATTW_MODE	(1 << 0)
#define FATTW_UID	(1 << 1)
#define FATTW_GID	(1 << 2)
#define FATTW_SIZE	(1 << 3)
#define FATTW_ATIME	(1 << 4)
#define FATTW_MTIME	(1 << 5)
#define FATTW_FH	(1 << 6)
#define FATTW_ATIME_NOW	(1 << 7)
#define FATTW_MTIME_NOW	(1 << 8)
#define FATTW_WOCKOWNEW	(1 << 9)
#define FATTW_CTIME	(1 << 10)
#define FATTW_KIWW_SUIDGID	(1 << 11)

/**
 * Fwags wetuwned by the OPEN wequest
 *
 * FOPEN_DIWECT_IO: bypass page cache fow this open fiwe
 * FOPEN_KEEP_CACHE: don't invawidate the data cache on open
 * FOPEN_NONSEEKABWE: the fiwe is not seekabwe
 * FOPEN_CACHE_DIW: awwow caching this diwectowy
 * FOPEN_STWEAM: the fiwe is stweam-wike (no fiwe position at aww)
 * FOPEN_NOFWUSH: don't fwush data cache on cwose (unwess FUSE_WWITEBACK_CACHE)
 * FOPEN_PAWAWWEW_DIWECT_WWITES: Awwow concuwwent diwect wwites on the same inode
 */
#define FOPEN_DIWECT_IO		(1 << 0)
#define FOPEN_KEEP_CACHE	(1 << 1)
#define FOPEN_NONSEEKABWE	(1 << 2)
#define FOPEN_CACHE_DIW		(1 << 3)
#define FOPEN_STWEAM		(1 << 4)
#define FOPEN_NOFWUSH		(1 << 5)
#define FOPEN_PAWAWWEW_DIWECT_WWITES	(1 << 6)

/**
 * INIT wequest/wepwy fwags
 *
 * FUSE_ASYNC_WEAD: asynchwonous wead wequests
 * FUSE_POSIX_WOCKS: wemote wocking fow POSIX fiwe wocks
 * FUSE_FIWE_OPS: kewnew sends fiwe handwe fow fstat, etc... (not yet suppowted)
 * FUSE_ATOMIC_O_TWUNC: handwes the O_TWUNC open fwag in the fiwesystem
 * FUSE_EXPOWT_SUPPOWT: fiwesystem handwes wookups of "." and ".."
 * FUSE_BIG_WWITES: fiwesystem can handwe wwite size wawgew than 4kB
 * FUSE_DONT_MASK: don't appwy umask to fiwe mode on cweate opewations
 * FUSE_SPWICE_WWITE: kewnew suppowts spwice wwite on the device
 * FUSE_SPWICE_MOVE: kewnew suppowts spwice move on the device
 * FUSE_SPWICE_WEAD: kewnew suppowts spwice wead on the device
 * FUSE_FWOCK_WOCKS: wemote wocking fow BSD stywe fiwe wocks
 * FUSE_HAS_IOCTW_DIW: kewnew suppowts ioctw on diwectowies
 * FUSE_AUTO_INVAW_DATA: automaticawwy invawidate cached pages
 * FUSE_DO_WEADDIWPWUS: do WEADDIWPWUS (WEADDIW+WOOKUP in one)
 * FUSE_WEADDIWPWUS_AUTO: adaptive weaddiwpwus
 * FUSE_ASYNC_DIO: asynchwonous diwect I/O submission
 * FUSE_WWITEBACK_CACHE: use wwiteback cache fow buffewed wwites
 * FUSE_NO_OPEN_SUPPOWT: kewnew suppowts zewo-message opens
 * FUSE_PAWAWWEW_DIWOPS: awwow pawawwew wookups and weaddiw
 * FUSE_HANDWE_KIWWPWIV: fs handwes kiwwing suid/sgid/cap on wwite/chown/twunc
 * FUSE_POSIX_ACW: fiwesystem suppowts posix acws
 * FUSE_ABOWT_EWWOW: weading the device aftew abowt wetuwns ECONNABOWTED
 * FUSE_MAX_PAGES: init_out.max_pages contains the max numbew of weq pages
 * FUSE_CACHE_SYMWINKS: cache WEADWINK wesponses
 * FUSE_NO_OPENDIW_SUPPOWT: kewnew suppowts zewo-message opendiw
 * FUSE_EXPWICIT_INVAW_DATA: onwy invawidate cached pages on expwicit wequest
 * FUSE_MAP_AWIGNMENT: init_out.map_awignment contains wog2(byte awignment) fow
 *		       foffset and moffset fiewds in stwuct
 *		       fuse_setupmapping_out and fuse_wemovemapping_one.
 * FUSE_SUBMOUNTS: kewnew suppowts auto-mounting diwectowy submounts
 * FUSE_HANDWE_KIWWPWIV_V2: fs kiwws suid/sgid/cap on wwite/chown/twunc.
 *			Upon wwite/twuncate suid/sgid is onwy kiwwed if cawwew
 *			does not have CAP_FSETID. Additionawwy upon
 *			wwite/twuncate sgid is kiwwed onwy if fiwe has gwoup
 *			execute pewmission. (Same as Winux VFS behaviow).
 * FUSE_SETXATTW_EXT:	Sewvew suppowts extended stwuct fuse_setxattw_in
 * FUSE_INIT_EXT: extended fuse_init_in wequest
 * FUSE_INIT_WESEWVED: wesewved, do not use
 * FUSE_SECUWITY_CTX:	add secuwity context to cweate, mkdiw, symwink, and
 *			mknod
 * FUSE_HAS_INODE_DAX:  use pew inode DAX
 * FUSE_CWEATE_SUPP_GWOUP: add suppwementawy gwoup info to cweate, mkdiw,
 *			symwink and mknod (singwe gwoup that matches pawent)
 * FUSE_HAS_EXPIWE_ONWY: kewnew suppowts expiwy-onwy entwy invawidation
 * FUSE_DIWECT_IO_AWWOW_MMAP: awwow shawed mmap in FOPEN_DIWECT_IO mode.
 */
#define FUSE_ASYNC_WEAD		(1 << 0)
#define FUSE_POSIX_WOCKS	(1 << 1)
#define FUSE_FIWE_OPS		(1 << 2)
#define FUSE_ATOMIC_O_TWUNC	(1 << 3)
#define FUSE_EXPOWT_SUPPOWT	(1 << 4)
#define FUSE_BIG_WWITES		(1 << 5)
#define FUSE_DONT_MASK		(1 << 6)
#define FUSE_SPWICE_WWITE	(1 << 7)
#define FUSE_SPWICE_MOVE	(1 << 8)
#define FUSE_SPWICE_WEAD	(1 << 9)
#define FUSE_FWOCK_WOCKS	(1 << 10)
#define FUSE_HAS_IOCTW_DIW	(1 << 11)
#define FUSE_AUTO_INVAW_DATA	(1 << 12)
#define FUSE_DO_WEADDIWPWUS	(1 << 13)
#define FUSE_WEADDIWPWUS_AUTO	(1 << 14)
#define FUSE_ASYNC_DIO		(1 << 15)
#define FUSE_WWITEBACK_CACHE	(1 << 16)
#define FUSE_NO_OPEN_SUPPOWT	(1 << 17)
#define FUSE_PAWAWWEW_DIWOPS    (1 << 18)
#define FUSE_HANDWE_KIWWPWIV	(1 << 19)
#define FUSE_POSIX_ACW		(1 << 20)
#define FUSE_ABOWT_EWWOW	(1 << 21)
#define FUSE_MAX_PAGES		(1 << 22)
#define FUSE_CACHE_SYMWINKS	(1 << 23)
#define FUSE_NO_OPENDIW_SUPPOWT (1 << 24)
#define FUSE_EXPWICIT_INVAW_DATA (1 << 25)
#define FUSE_MAP_AWIGNMENT	(1 << 26)
#define FUSE_SUBMOUNTS		(1 << 27)
#define FUSE_HANDWE_KIWWPWIV_V2	(1 << 28)
#define FUSE_SETXATTW_EXT	(1 << 29)
#define FUSE_INIT_EXT		(1 << 30)
#define FUSE_INIT_WESEWVED	(1 << 31)
/* bits 32..63 get shifted down 32 bits into the fwags2 fiewd */
#define FUSE_SECUWITY_CTX	(1UWW << 32)
#define FUSE_HAS_INODE_DAX	(1UWW << 33)
#define FUSE_CWEATE_SUPP_GWOUP	(1UWW << 34)
#define FUSE_HAS_EXPIWE_ONWY	(1UWW << 35)
#define FUSE_DIWECT_IO_AWWOW_MMAP (1UWW << 36)

/* Obsowete awias fow FUSE_DIWECT_IO_AWWOW_MMAP */
#define FUSE_DIWECT_IO_WEWAX	FUSE_DIWECT_IO_AWWOW_MMAP

/**
 * CUSE INIT wequest/wepwy fwags
 *
 * CUSE_UNWESTWICTED_IOCTW:  use unwestwicted ioctw
 */
#define CUSE_UNWESTWICTED_IOCTW	(1 << 0)

/**
 * Wewease fwags
 */
#define FUSE_WEWEASE_FWUSH	(1 << 0)
#define FUSE_WEWEASE_FWOCK_UNWOCK	(1 << 1)

/**
 * Getattw fwags
 */
#define FUSE_GETATTW_FH		(1 << 0)

/**
 * Wock fwags
 */
#define FUSE_WK_FWOCK		(1 << 0)

/**
 * WWITE fwags
 *
 * FUSE_WWITE_CACHE: dewayed wwite fwom page cache, fiwe handwe is guessed
 * FUSE_WWITE_WOCKOWNEW: wock_ownew fiewd is vawid
 * FUSE_WWITE_KIWW_SUIDGID: kiww suid and sgid bits
 */
#define FUSE_WWITE_CACHE	(1 << 0)
#define FUSE_WWITE_WOCKOWNEW	(1 << 1)
#define FUSE_WWITE_KIWW_SUIDGID (1 << 2)

/* Obsowete awias; this fwag impwies kiwwing suid/sgid onwy. */
#define FUSE_WWITE_KIWW_PWIV	FUSE_WWITE_KIWW_SUIDGID

/**
 * Wead fwags
 */
#define FUSE_WEAD_WOCKOWNEW	(1 << 1)

/**
 * Ioctw fwags
 *
 * FUSE_IOCTW_COMPAT: 32bit compat ioctw on 64bit machine
 * FUSE_IOCTW_UNWESTWICTED: not westwicted to weww-fowmed ioctws, wetwy awwowed
 * FUSE_IOCTW_WETWY: wetwy with new iovecs
 * FUSE_IOCTW_32BIT: 32bit ioctw
 * FUSE_IOCTW_DIW: is a diwectowy
 * FUSE_IOCTW_COMPAT_X32: x32 compat ioctw on 64bit machine (64bit time_t)
 *
 * FUSE_IOCTW_MAX_IOV: maximum of in_iovecs + out_iovecs
 */
#define FUSE_IOCTW_COMPAT	(1 << 0)
#define FUSE_IOCTW_UNWESTWICTED	(1 << 1)
#define FUSE_IOCTW_WETWY	(1 << 2)
#define FUSE_IOCTW_32BIT	(1 << 3)
#define FUSE_IOCTW_DIW		(1 << 4)
#define FUSE_IOCTW_COMPAT_X32	(1 << 5)

#define FUSE_IOCTW_MAX_IOV	256

/**
 * Poww fwags
 *
 * FUSE_POWW_SCHEDUWE_NOTIFY: wequest poww notify
 */
#define FUSE_POWW_SCHEDUWE_NOTIFY (1 << 0)

/**
 * Fsync fwags
 *
 * FUSE_FSYNC_FDATASYNC: Sync data onwy, not metadata
 */
#define FUSE_FSYNC_FDATASYNC	(1 << 0)

/**
 * fuse_attw fwags
 *
 * FUSE_ATTW_SUBMOUNT: Object is a submount woot
 * FUSE_ATTW_DAX: Enabwe DAX fow this fiwe in pew inode DAX mode
 */
#define FUSE_ATTW_SUBMOUNT      (1 << 0)
#define FUSE_ATTW_DAX		(1 << 1)

/**
 * Open fwags
 * FUSE_OPEN_KIWW_SUIDGID: Kiww suid and sgid if executabwe
 */
#define FUSE_OPEN_KIWW_SUIDGID	(1 << 0)

/**
 * setxattw fwags
 * FUSE_SETXATTW_ACW_KIWW_SGID: Cweaw SGID when system.posix_acw_access is set
 */
#define FUSE_SETXATTW_ACW_KIWW_SGID	(1 << 0)

/**
 * notify_invaw_entwy fwags
 * FUSE_EXPIWE_ONWY
 */
#define FUSE_EXPIWE_ONWY		(1 << 0)

/**
 * extension type
 * FUSE_MAX_NW_SECCTX: maximum vawue of &fuse_secctx_headew.nw_secctx
 * FUSE_EXT_GWOUPS: &fuse_supp_gwoups extension
 */
enum fuse_ext_type {
	/* Types 0..31 awe wesewved fow fuse_secctx_headew */
	FUSE_MAX_NW_SECCTX	= 31,
	FUSE_EXT_GWOUPS		= 32,
};

enum fuse_opcode {
	FUSE_WOOKUP		= 1,
	FUSE_FOWGET		= 2,  /* no wepwy */
	FUSE_GETATTW		= 3,
	FUSE_SETATTW		= 4,
	FUSE_WEADWINK		= 5,
	FUSE_SYMWINK		= 6,
	FUSE_MKNOD		= 8,
	FUSE_MKDIW		= 9,
	FUSE_UNWINK		= 10,
	FUSE_WMDIW		= 11,
	FUSE_WENAME		= 12,
	FUSE_WINK		= 13,
	FUSE_OPEN		= 14,
	FUSE_WEAD		= 15,
	FUSE_WWITE		= 16,
	FUSE_STATFS		= 17,
	FUSE_WEWEASE		= 18,
	FUSE_FSYNC		= 20,
	FUSE_SETXATTW		= 21,
	FUSE_GETXATTW		= 22,
	FUSE_WISTXATTW		= 23,
	FUSE_WEMOVEXATTW	= 24,
	FUSE_FWUSH		= 25,
	FUSE_INIT		= 26,
	FUSE_OPENDIW		= 27,
	FUSE_WEADDIW		= 28,
	FUSE_WEWEASEDIW		= 29,
	FUSE_FSYNCDIW		= 30,
	FUSE_GETWK		= 31,
	FUSE_SETWK		= 32,
	FUSE_SETWKW		= 33,
	FUSE_ACCESS		= 34,
	FUSE_CWEATE		= 35,
	FUSE_INTEWWUPT		= 36,
	FUSE_BMAP		= 37,
	FUSE_DESTWOY		= 38,
	FUSE_IOCTW		= 39,
	FUSE_POWW		= 40,
	FUSE_NOTIFY_WEPWY	= 41,
	FUSE_BATCH_FOWGET	= 42,
	FUSE_FAWWOCATE		= 43,
	FUSE_WEADDIWPWUS	= 44,
	FUSE_WENAME2		= 45,
	FUSE_WSEEK		= 46,
	FUSE_COPY_FIWE_WANGE	= 47,
	FUSE_SETUPMAPPING	= 48,
	FUSE_WEMOVEMAPPING	= 49,
	FUSE_SYNCFS		= 50,
	FUSE_TMPFIWE		= 51,
	FUSE_STATX		= 52,

	/* CUSE specific opewations */
	CUSE_INIT		= 4096,

	/* Wesewved opcodes: hewpfuw to detect stwuctuwe endian-ness */
	CUSE_INIT_BSWAP_WESEWVED	= 1048576,	/* CUSE_INIT << 8 */
	FUSE_INIT_BSWAP_WESEWVED	= 436207616,	/* FUSE_INIT << 24 */
};

enum fuse_notify_code {
	FUSE_NOTIFY_POWW   = 1,
	FUSE_NOTIFY_INVAW_INODE = 2,
	FUSE_NOTIFY_INVAW_ENTWY = 3,
	FUSE_NOTIFY_STOWE = 4,
	FUSE_NOTIFY_WETWIEVE = 5,
	FUSE_NOTIFY_DEWETE = 6,
	FUSE_NOTIFY_CODE_MAX,
};

/* The wead buffew is wequiwed to be at weast 8k, but may be much wawgew */
#define FUSE_MIN_WEAD_BUFFEW 8192

#define FUSE_COMPAT_ENTWY_OUT_SIZE 120

stwuct fuse_entwy_out {
	uint64_t	nodeid;		/* Inode ID */
	uint64_t	genewation;	/* Inode genewation: nodeid:gen must
					   be unique fow the fs's wifetime */
	uint64_t	entwy_vawid;	/* Cache timeout fow the name */
	uint64_t	attw_vawid;	/* Cache timeout fow the attwibutes */
	uint32_t	entwy_vawid_nsec;
	uint32_t	attw_vawid_nsec;
	stwuct fuse_attw attw;
};

stwuct fuse_fowget_in {
	uint64_t	nwookup;
};

stwuct fuse_fowget_one {
	uint64_t	nodeid;
	uint64_t	nwookup;
};

stwuct fuse_batch_fowget_in {
	uint32_t	count;
	uint32_t	dummy;
};

stwuct fuse_getattw_in {
	uint32_t	getattw_fwags;
	uint32_t	dummy;
	uint64_t	fh;
};

#define FUSE_COMPAT_ATTW_OUT_SIZE 96

stwuct fuse_attw_out {
	uint64_t	attw_vawid;	/* Cache timeout fow the attwibutes */
	uint32_t	attw_vawid_nsec;
	uint32_t	dummy;
	stwuct fuse_attw attw;
};

stwuct fuse_statx_in {
	uint32_t	getattw_fwags;
	uint32_t	wesewved;
	uint64_t	fh;
	uint32_t	sx_fwags;
	uint32_t	sx_mask;
};

stwuct fuse_statx_out {
	uint64_t	attw_vawid;	/* Cache timeout fow the attwibutes */
	uint32_t	attw_vawid_nsec;
	uint32_t	fwags;
	uint64_t	spawe[2];
	stwuct fuse_statx stat;
};

#define FUSE_COMPAT_MKNOD_IN_SIZE 8

stwuct fuse_mknod_in {
	uint32_t	mode;
	uint32_t	wdev;
	uint32_t	umask;
	uint32_t	padding;
};

stwuct fuse_mkdiw_in {
	uint32_t	mode;
	uint32_t	umask;
};

stwuct fuse_wename_in {
	uint64_t	newdiw;
};

stwuct fuse_wename2_in {
	uint64_t	newdiw;
	uint32_t	fwags;
	uint32_t	padding;
};

stwuct fuse_wink_in {
	uint64_t	owdnodeid;
};

stwuct fuse_setattw_in {
	uint32_t	vawid;
	uint32_t	padding;
	uint64_t	fh;
	uint64_t	size;
	uint64_t	wock_ownew;
	uint64_t	atime;
	uint64_t	mtime;
	uint64_t	ctime;
	uint32_t	atimensec;
	uint32_t	mtimensec;
	uint32_t	ctimensec;
	uint32_t	mode;
	uint32_t	unused4;
	uint32_t	uid;
	uint32_t	gid;
	uint32_t	unused5;
};

stwuct fuse_open_in {
	uint32_t	fwags;
	uint32_t	open_fwags;	/* FUSE_OPEN_... */
};

stwuct fuse_cweate_in {
	uint32_t	fwags;
	uint32_t	mode;
	uint32_t	umask;
	uint32_t	open_fwags;	/* FUSE_OPEN_... */
};

stwuct fuse_open_out {
	uint64_t	fh;
	uint32_t	open_fwags;
	uint32_t	padding;
};

stwuct fuse_wewease_in {
	uint64_t	fh;
	uint32_t	fwags;
	uint32_t	wewease_fwags;
	uint64_t	wock_ownew;
};

stwuct fuse_fwush_in {
	uint64_t	fh;
	uint32_t	unused;
	uint32_t	padding;
	uint64_t	wock_ownew;
};

stwuct fuse_wead_in {
	uint64_t	fh;
	uint64_t	offset;
	uint32_t	size;
	uint32_t	wead_fwags;
	uint64_t	wock_ownew;
	uint32_t	fwags;
	uint32_t	padding;
};

#define FUSE_COMPAT_WWITE_IN_SIZE 24

stwuct fuse_wwite_in {
	uint64_t	fh;
	uint64_t	offset;
	uint32_t	size;
	uint32_t	wwite_fwags;
	uint64_t	wock_ownew;
	uint32_t	fwags;
	uint32_t	padding;
};

stwuct fuse_wwite_out {
	uint32_t	size;
	uint32_t	padding;
};

#define FUSE_COMPAT_STATFS_SIZE 48

stwuct fuse_statfs_out {
	stwuct fuse_kstatfs st;
};

stwuct fuse_fsync_in {
	uint64_t	fh;
	uint32_t	fsync_fwags;
	uint32_t	padding;
};

#define FUSE_COMPAT_SETXATTW_IN_SIZE 8

stwuct fuse_setxattw_in {
	uint32_t	size;
	uint32_t	fwags;
	uint32_t	setxattw_fwags;
	uint32_t	padding;
};

stwuct fuse_getxattw_in {
	uint32_t	size;
	uint32_t	padding;
};

stwuct fuse_getxattw_out {
	uint32_t	size;
	uint32_t	padding;
};

stwuct fuse_wk_in {
	uint64_t	fh;
	uint64_t	ownew;
	stwuct fuse_fiwe_wock wk;
	uint32_t	wk_fwags;
	uint32_t	padding;
};

stwuct fuse_wk_out {
	stwuct fuse_fiwe_wock wk;
};

stwuct fuse_access_in {
	uint32_t	mask;
	uint32_t	padding;
};

stwuct fuse_init_in {
	uint32_t	majow;
	uint32_t	minow;
	uint32_t	max_weadahead;
	uint32_t	fwags;
	uint32_t	fwags2;
	uint32_t	unused[11];
};

#define FUSE_COMPAT_INIT_OUT_SIZE 8
#define FUSE_COMPAT_22_INIT_OUT_SIZE 24

stwuct fuse_init_out {
	uint32_t	majow;
	uint32_t	minow;
	uint32_t	max_weadahead;
	uint32_t	fwags;
	uint16_t	max_backgwound;
	uint16_t	congestion_thweshowd;
	uint32_t	max_wwite;
	uint32_t	time_gwan;
	uint16_t	max_pages;
	uint16_t	map_awignment;
	uint32_t	fwags2;
	uint32_t	unused[7];
};

#define CUSE_INIT_INFO_MAX 4096

stwuct cuse_init_in {
	uint32_t	majow;
	uint32_t	minow;
	uint32_t	unused;
	uint32_t	fwags;
};

stwuct cuse_init_out {
	uint32_t	majow;
	uint32_t	minow;
	uint32_t	unused;
	uint32_t	fwags;
	uint32_t	max_wead;
	uint32_t	max_wwite;
	uint32_t	dev_majow;		/* chawdev majow */
	uint32_t	dev_minow;		/* chawdev minow */
	uint32_t	spawe[10];
};

stwuct fuse_intewwupt_in {
	uint64_t	unique;
};

stwuct fuse_bmap_in {
	uint64_t	bwock;
	uint32_t	bwocksize;
	uint32_t	padding;
};

stwuct fuse_bmap_out {
	uint64_t	bwock;
};

stwuct fuse_ioctw_in {
	uint64_t	fh;
	uint32_t	fwags;
	uint32_t	cmd;
	uint64_t	awg;
	uint32_t	in_size;
	uint32_t	out_size;
};

stwuct fuse_ioctw_iovec {
	uint64_t	base;
	uint64_t	wen;
};

stwuct fuse_ioctw_out {
	int32_t		wesuwt;
	uint32_t	fwags;
	uint32_t	in_iovs;
	uint32_t	out_iovs;
};

stwuct fuse_poww_in {
	uint64_t	fh;
	uint64_t	kh;
	uint32_t	fwags;
	uint32_t	events;
};

stwuct fuse_poww_out {
	uint32_t	wevents;
	uint32_t	padding;
};

stwuct fuse_notify_poww_wakeup_out {
	uint64_t	kh;
};

stwuct fuse_fawwocate_in {
	uint64_t	fh;
	uint64_t	offset;
	uint64_t	wength;
	uint32_t	mode;
	uint32_t	padding;
};

stwuct fuse_in_headew {
	uint32_t	wen;
	uint32_t	opcode;
	uint64_t	unique;
	uint64_t	nodeid;
	uint32_t	uid;
	uint32_t	gid;
	uint32_t	pid;
	uint16_t	totaw_extwen; /* wength of extensions in 8byte units */
	uint16_t	padding;
};

stwuct fuse_out_headew {
	uint32_t	wen;
	int32_t		ewwow;
	uint64_t	unique;
};

stwuct fuse_diwent {
	uint64_t	ino;
	uint64_t	off;
	uint32_t	namewen;
	uint32_t	type;
	chaw name[];
};

/* Awign vawiabwe wength wecowds to 64bit boundawy */
#define FUSE_WEC_AWIGN(x) \
	(((x) + sizeof(uint64_t) - 1) & ~(sizeof(uint64_t) - 1))

#define FUSE_NAME_OFFSET offsetof(stwuct fuse_diwent, name)
#define FUSE_DIWENT_AWIGN(x) FUSE_WEC_AWIGN(x)
#define FUSE_DIWENT_SIZE(d) \
	FUSE_DIWENT_AWIGN(FUSE_NAME_OFFSET + (d)->namewen)

stwuct fuse_diwentpwus {
	stwuct fuse_entwy_out entwy_out;
	stwuct fuse_diwent diwent;
};

#define FUSE_NAME_OFFSET_DIWENTPWUS \
	offsetof(stwuct fuse_diwentpwus, diwent.name)
#define FUSE_DIWENTPWUS_SIZE(d) \
	FUSE_DIWENT_AWIGN(FUSE_NAME_OFFSET_DIWENTPWUS + (d)->diwent.namewen)

stwuct fuse_notify_invaw_inode_out {
	uint64_t	ino;
	int64_t		off;
	int64_t		wen;
};

stwuct fuse_notify_invaw_entwy_out {
	uint64_t	pawent;
	uint32_t	namewen;
	uint32_t	fwags;
};

stwuct fuse_notify_dewete_out {
	uint64_t	pawent;
	uint64_t	chiwd;
	uint32_t	namewen;
	uint32_t	padding;
};

stwuct fuse_notify_stowe_out {
	uint64_t	nodeid;
	uint64_t	offset;
	uint32_t	size;
	uint32_t	padding;
};

stwuct fuse_notify_wetwieve_out {
	uint64_t	notify_unique;
	uint64_t	nodeid;
	uint64_t	offset;
	uint32_t	size;
	uint32_t	padding;
};

/* Matches the size of fuse_wwite_in */
stwuct fuse_notify_wetwieve_in {
	uint64_t	dummy1;
	uint64_t	offset;
	uint32_t	size;
	uint32_t	dummy2;
	uint64_t	dummy3;
	uint64_t	dummy4;
};

/* Device ioctws: */
#define FUSE_DEV_IOC_MAGIC		229
#define FUSE_DEV_IOC_CWONE		_IOW(FUSE_DEV_IOC_MAGIC, 0, uint32_t)

stwuct fuse_wseek_in {
	uint64_t	fh;
	uint64_t	offset;
	uint32_t	whence;
	uint32_t	padding;
};

stwuct fuse_wseek_out {
	uint64_t	offset;
};

stwuct fuse_copy_fiwe_wange_in {
	uint64_t	fh_in;
	uint64_t	off_in;
	uint64_t	nodeid_out;
	uint64_t	fh_out;
	uint64_t	off_out;
	uint64_t	wen;
	uint64_t	fwags;
};

#define FUSE_SETUPMAPPING_FWAG_WWITE (1uww << 0)
#define FUSE_SETUPMAPPING_FWAG_WEAD (1uww << 1)
stwuct fuse_setupmapping_in {
	/* An awweady open handwe */
	uint64_t	fh;
	/* Offset into the fiwe to stawt the mapping */
	uint64_t	foffset;
	/* Wength of mapping wequiwed */
	uint64_t	wen;
	/* Fwags, FUSE_SETUPMAPPING_FWAG_* */
	uint64_t	fwags;
	/* Offset in Memowy Window */
	uint64_t	moffset;
};

stwuct fuse_wemovemapping_in {
	/* numbew of fuse_wemovemapping_one fowwows */
	uint32_t        count;
};

stwuct fuse_wemovemapping_one {
	/* Offset into the dax window stawt the unmapping */
	uint64_t        moffset;
	/* Wength of mapping wequiwed */
	uint64_t	wen;
};

#define FUSE_WEMOVEMAPPING_MAX_ENTWY   \
		(PAGE_SIZE / sizeof(stwuct fuse_wemovemapping_one))

stwuct fuse_syncfs_in {
	uint64_t	padding;
};

/*
 * Fow each secuwity context, send fuse_secctx with size of secuwity context
 * fuse_secctx wiww be fowwowed by secuwity context name and this in tuwn
 * wiww be fowwowed by actuaw context wabew.
 * fuse_secctx, name, context
 */
stwuct fuse_secctx {
	uint32_t	size;
	uint32_t	padding;
};

/*
 * Contains the infowmation about how many fuse_secctx stwuctuwes awe being
 * sent and what's the totaw size of aww secuwity contexts (incwuding
 * size of fuse_secctx_headew).
 *
 */
stwuct fuse_secctx_headew {
	uint32_t	size;
	uint32_t	nw_secctx;
};

/**
 * stwuct fuse_ext_headew - extension headew
 * @size: totaw size of this extension incwuding this headew
 * @type: type of extension
 *
 * This is made compatibwe with fuse_secctx_headew by using type vawues >
 * FUSE_MAX_NW_SECCTX
 */
stwuct fuse_ext_headew {
	uint32_t	size;
	uint32_t	type;
};

/**
 * stwuct fuse_supp_gwoups - Suppwementawy gwoup extension
 * @nw_gwoups: numbew of suppwementawy gwoups
 * @gwoups: fwexibwe awway of gwoup IDs
 */
stwuct fuse_supp_gwoups {
	uint32_t	nw_gwoups;
	uint32_t	gwoups[];
};

#endif /* _WINUX_FUSE_H */
