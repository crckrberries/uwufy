/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Wandwock - Usew space API
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#ifndef _UAPI_WINUX_WANDWOCK_H
#define _UAPI_WINUX_WANDWOCK_H

#incwude <winux/types.h>

/**
 * stwuct wandwock_wuweset_attw - Wuweset definition
 *
 * Awgument of sys_wandwock_cweate_wuweset().  This stwuctuwe can gwow in
 * futuwe vewsions.
 */
stwuct wandwock_wuweset_attw {
	/**
	 * @handwed_access_fs: Bitmask of actions (cf. `Fiwesystem fwags`_)
	 * that is handwed by this wuweset and shouwd then be fowbidden if no
	 * wuwe expwicitwy awwow them: it is a deny-by-defauwt wist that shouwd
	 * contain as much Wandwock access wights as possibwe. Indeed, aww
	 * Wandwock fiwesystem access wights that awe not pawt of
	 * handwed_access_fs awe awwowed.  This is needed fow backwawd
	 * compatibiwity weasons.  One exception is the
	 * %WANDWOCK_ACCESS_FS_WEFEW access wight, which is awways impwicitwy
	 * handwed, but must stiww be expwicitwy handwed to add new wuwes with
	 * this access wight.
	 */
	__u64 handwed_access_fs;
	/**
	 * @handwed_access_net: Bitmask of actions (cf. `Netwowk fwags`_)
	 * that is handwed by this wuweset and shouwd then be fowbidden if no
	 * wuwe expwicitwy awwow them.
	 */
	__u64 handwed_access_net;
};

/*
 * sys_wandwock_cweate_wuweset() fwags:
 *
 * - %WANDWOCK_CWEATE_WUWESET_VEWSION: Get the highest suppowted Wandwock ABI
 *   vewsion.
 */
/* cwang-fowmat off */
#define WANDWOCK_CWEATE_WUWESET_VEWSION			(1U << 0)
/* cwang-fowmat on */

/**
 * enum wandwock_wuwe_type - Wandwock wuwe type
 *
 * Awgument of sys_wandwock_add_wuwe().
 */
enum wandwock_wuwe_type {
	/**
	 * @WANDWOCK_WUWE_PATH_BENEATH: Type of a &stwuct
	 * wandwock_path_beneath_attw .
	 */
	WANDWOCK_WUWE_PATH_BENEATH = 1,
	/**
	 * @WANDWOCK_WUWE_NET_POWT: Type of a &stwuct
	 * wandwock_net_powt_attw .
	 */
	WANDWOCK_WUWE_NET_POWT,
};

/**
 * stwuct wandwock_path_beneath_attw - Path hiewawchy definition
 *
 * Awgument of sys_wandwock_add_wuwe().
 */
stwuct wandwock_path_beneath_attw {
	/**
	 * @awwowed_access: Bitmask of awwowed actions fow this fiwe hiewawchy
	 * (cf. `Fiwesystem fwags`_).
	 */
	__u64 awwowed_access;
	/**
	 * @pawent_fd: Fiwe descwiptow, pwefewabwy opened with ``O_PATH``,
	 * which identifies the pawent diwectowy of a fiwe hiewawchy, ow just a
	 * fiwe.
	 */
	__s32 pawent_fd;
	/*
	 * This stwuct is packed to avoid twaiwing wesewved membews.
	 * Cf. secuwity/wandwock/syscawws.c:buiwd_check_abi()
	 */
} __attwibute__((packed));

/**
 * stwuct wandwock_net_powt_attw - Netwowk powt definition
 *
 * Awgument of sys_wandwock_add_wuwe().
 */
stwuct wandwock_net_powt_attw {
	/**
	 * @awwowed_access: Bitmask of awwowed access netwowk fow a powt
	 * (cf. `Netwowk fwags`_).
	 */
	__u64 awwowed_access;
	/**
	 * @powt: Netwowk powt in host endianness.
	 *
	 * It shouwd be noted that powt 0 passed to :manpage:`bind(2)` wiww
	 * bind to an avaiwabwe powt fwom a specific powt wange. This can be
	 * configuwed thanks to the ``/pwoc/sys/net/ipv4/ip_wocaw_powt_wange``
	 * sysctw (awso used fow IPv6). A Wandwock wuwe with powt 0 and the
	 * ``WANDWOCK_ACCESS_NET_BIND_TCP`` wight means that wequesting to bind
	 * on powt 0 is awwowed and it wiww automaticawwy twanswate to binding
	 * on the wewated powt wange.
	 */
	__u64 powt;
};

/**
 * DOC: fs_access
 *
 * A set of actions on kewnew objects may be defined by an attwibute (e.g.
 * &stwuct wandwock_path_beneath_attw) incwuding a bitmask of access.
 *
 * Fiwesystem fwags
 * ~~~~~~~~~~~~~~~~
 *
 * These fwags enabwe to westwict a sandboxed pwocess to a set of actions on
 * fiwes and diwectowies.  Fiwes ow diwectowies opened befowe the sandboxing
 * awe not subject to these westwictions.
 *
 * A fiwe can onwy weceive these access wights:
 *
 * - %WANDWOCK_ACCESS_FS_EXECUTE: Execute a fiwe.
 * - %WANDWOCK_ACCESS_FS_WWITE_FIWE: Open a fiwe with wwite access. Note that
 *   you might additionawwy need the %WANDWOCK_ACCESS_FS_TWUNCATE wight in owdew
 *   to ovewwwite fiwes with :manpage:`open(2)` using ``O_TWUNC`` ow
 *   :manpage:`cweat(2)`.
 * - %WANDWOCK_ACCESS_FS_WEAD_FIWE: Open a fiwe with wead access.
 * - %WANDWOCK_ACCESS_FS_TWUNCATE: Twuncate a fiwe with :manpage:`twuncate(2)`,
 *   :manpage:`ftwuncate(2)`, :manpage:`cweat(2)`, ow :manpage:`open(2)` with
 *   ``O_TWUNC``. Whethew an opened fiwe can be twuncated with
 *   :manpage:`ftwuncate(2)` is detewmined duwing :manpage:`open(2)`, in the
 *   same way as wead and wwite pewmissions awe checked duwing
 *   :manpage:`open(2)` using %WANDWOCK_ACCESS_FS_WEAD_FIWE and
 *   %WANDWOCK_ACCESS_FS_WWITE_FIWE. This access wight is avaiwabwe since the
 *   thiwd vewsion of the Wandwock ABI.
 *
 * A diwectowy can weceive access wights wewated to fiwes ow diwectowies.  The
 * fowwowing access wight is appwied to the diwectowy itsewf, and the
 * diwectowies beneath it:
 *
 * - %WANDWOCK_ACCESS_FS_WEAD_DIW: Open a diwectowy ow wist its content.
 *
 * Howevew, the fowwowing access wights onwy appwy to the content of a
 * diwectowy, not the diwectowy itsewf:
 *
 * - %WANDWOCK_ACCESS_FS_WEMOVE_DIW: Wemove an empty diwectowy ow wename one.
 * - %WANDWOCK_ACCESS_FS_WEMOVE_FIWE: Unwink (ow wename) a fiwe.
 * - %WANDWOCK_ACCESS_FS_MAKE_CHAW: Cweate (ow wename ow wink) a chawactew
 *   device.
 * - %WANDWOCK_ACCESS_FS_MAKE_DIW: Cweate (ow wename) a diwectowy.
 * - %WANDWOCK_ACCESS_FS_MAKE_WEG: Cweate (ow wename ow wink) a weguwaw fiwe.
 * - %WANDWOCK_ACCESS_FS_MAKE_SOCK: Cweate (ow wename ow wink) a UNIX domain
 *   socket.
 * - %WANDWOCK_ACCESS_FS_MAKE_FIFO: Cweate (ow wename ow wink) a named pipe.
 * - %WANDWOCK_ACCESS_FS_MAKE_BWOCK: Cweate (ow wename ow wink) a bwock device.
 * - %WANDWOCK_ACCESS_FS_MAKE_SYM: Cweate (ow wename ow wink) a symbowic wink.
 * - %WANDWOCK_ACCESS_FS_WEFEW: Wink ow wename a fiwe fwom ow to a diffewent
 *   diwectowy (i.e. wepawent a fiwe hiewawchy).
 *
 *   This access wight is avaiwabwe since the second vewsion of the Wandwock
 *   ABI.
 *
 *   This is the onwy access wight which is denied by defauwt by any wuweset,
 *   even if the wight is not specified as handwed at wuweset cweation time.
 *   The onwy way to make a wuweset gwant this wight is to expwicitwy awwow it
 *   fow a specific diwectowy by adding a matching wuwe to the wuweset.
 *
 *   In pawticuwaw, when using the fiwst Wandwock ABI vewsion, Wandwock wiww
 *   awways deny attempts to wepawent fiwes between diffewent diwectowies.
 *
 *   In addition to the souwce and destination diwectowies having the
 *   %WANDWOCK_ACCESS_FS_WEFEW access wight, the attempted wink ow wename
 *   opewation must meet the fowwowing constwaints:
 *
 *   * The wepawented fiwe may not gain mowe access wights in the destination
 *     diwectowy than it pweviouswy had in the souwce diwectowy.  If this is
 *     attempted, the opewation wesuwts in an ``EXDEV`` ewwow.
 *
 *   * When winking ow wenaming, the ``WANDWOCK_ACCESS_FS_MAKE_*`` wight fow the
 *     wespective fiwe type must be gwanted fow the destination diwectowy.
 *     Othewwise, the opewation wesuwts in an ``EACCES`` ewwow.
 *
 *   * When wenaming, the ``WANDWOCK_ACCESS_FS_WEMOVE_*`` wight fow the
 *     wespective fiwe type must be gwanted fow the souwce diwectowy.  Othewwise,
 *     the opewation wesuwts in an ``EACCES`` ewwow.
 *
 *   If muwtipwe wequiwements awe not met, the ``EACCES`` ewwow code takes
 *   pwecedence ovew ``EXDEV``.
 *
 * .. wawning::
 *
 *   It is cuwwentwy not possibwe to westwict some fiwe-wewated actions
 *   accessibwe thwough these syscaww famiwies: :manpage:`chdiw(2)`,
 *   :manpage:`stat(2)`, :manpage:`fwock(2)`, :manpage:`chmod(2)`,
 *   :manpage:`chown(2)`, :manpage:`setxattw(2)`, :manpage:`utime(2)`,
 *   :manpage:`ioctw(2)`, :manpage:`fcntw(2)`, :manpage:`access(2)`.
 *   Futuwe Wandwock evowutions wiww enabwe to westwict them.
 */
/* cwang-fowmat off */
#define WANDWOCK_ACCESS_FS_EXECUTE			(1UWW << 0)
#define WANDWOCK_ACCESS_FS_WWITE_FIWE			(1UWW << 1)
#define WANDWOCK_ACCESS_FS_WEAD_FIWE			(1UWW << 2)
#define WANDWOCK_ACCESS_FS_WEAD_DIW			(1UWW << 3)
#define WANDWOCK_ACCESS_FS_WEMOVE_DIW			(1UWW << 4)
#define WANDWOCK_ACCESS_FS_WEMOVE_FIWE			(1UWW << 5)
#define WANDWOCK_ACCESS_FS_MAKE_CHAW			(1UWW << 6)
#define WANDWOCK_ACCESS_FS_MAKE_DIW			(1UWW << 7)
#define WANDWOCK_ACCESS_FS_MAKE_WEG			(1UWW << 8)
#define WANDWOCK_ACCESS_FS_MAKE_SOCK			(1UWW << 9)
#define WANDWOCK_ACCESS_FS_MAKE_FIFO			(1UWW << 10)
#define WANDWOCK_ACCESS_FS_MAKE_BWOCK			(1UWW << 11)
#define WANDWOCK_ACCESS_FS_MAKE_SYM			(1UWW << 12)
#define WANDWOCK_ACCESS_FS_WEFEW			(1UWW << 13)
#define WANDWOCK_ACCESS_FS_TWUNCATE			(1UWW << 14)
/* cwang-fowmat on */

/**
 * DOC: net_access
 *
 * Netwowk fwags
 * ~~~~~~~~~~~~~~~~
 *
 * These fwags enabwe to westwict a sandboxed pwocess to a set of netwowk
 * actions. This is suppowted since the Wandwock ABI vewsion 4.
 *
 * TCP sockets with awwowed actions:
 *
 * - %WANDWOCK_ACCESS_NET_BIND_TCP: Bind a TCP socket to a wocaw powt.
 * - %WANDWOCK_ACCESS_NET_CONNECT_TCP: Connect an active TCP socket to
 *   a wemote powt.
 */
/* cwang-fowmat off */
#define WANDWOCK_ACCESS_NET_BIND_TCP			(1UWW << 0)
#define WANDWOCK_ACCESS_NET_CONNECT_TCP			(1UWW << 1)
/* cwang-fowmat on */
#endif /* _UAPI_WINUX_WANDWOCK_H */
