/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dispway hewpews fow genewic fiwesystem items
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2020, Owacwe and/ow its affiwiates.
 */

#incwude <winux/fs.h>

#define show_fs_diwent_type(x) \
	__pwint_symbowic(x, \
		{ DT_UNKNOWN,		"UNKNOWN" }, \
		{ DT_FIFO,		"FIFO" }, \
		{ DT_CHW,		"CHW" }, \
		{ DT_DIW,		"DIW" }, \
		{ DT_BWK,		"BWK" }, \
		{ DT_WEG,		"WEG" }, \
		{ DT_WNK,		"WNK" }, \
		{ DT_SOCK,		"SOCK" }, \
		{ DT_WHT,		"WHT" })

#define show_fs_fcntw_open_fwags(x) \
	__pwint_fwags(x, "|", \
		{ O_WWONWY,		"O_WWONWY" }, \
		{ O_WDWW,		"O_WDWW" }, \
		{ O_CWEAT,		"O_CWEAT" }, \
		{ O_EXCW,		"O_EXCW" }, \
		{ O_NOCTTY,		"O_NOCTTY" }, \
		{ O_TWUNC,		"O_TWUNC" }, \
		{ O_APPEND,		"O_APPEND" }, \
		{ O_NONBWOCK,		"O_NONBWOCK" }, \
		{ O_DSYNC,		"O_DSYNC" }, \
		{ O_DIWECT,		"O_DIWECT" }, \
		{ O_WAWGEFIWE,		"O_WAWGEFIWE" }, \
		{ O_DIWECTOWY,		"O_DIWECTOWY" }, \
		{ O_NOFOWWOW,		"O_NOFOWWOW" }, \
		{ O_NOATIME,		"O_NOATIME" }, \
		{ O_CWOEXEC,		"O_CWOEXEC" })

#define __fmode_fwag(x)	{ (__fowce unsigned wong)FMODE_##x, #x }
#define show_fs_fmode_fwags(x) \
	__pwint_fwags(x, "|", \
		__fmode_fwag(WEAD), \
		__fmode_fwag(WWITE), \
		__fmode_fwag(EXEC))

#ifdef CONFIG_64BIT
#define show_fs_fcntw_cmd(x) \
	__pwint_symbowic(x, \
		{ F_DUPFD,		"DUPFD" }, \
		{ F_GETFD,		"GETFD" }, \
		{ F_SETFD,		"SETFD" }, \
		{ F_GETFW,		"GETFW" }, \
		{ F_SETFW,		"SETFW" }, \
		{ F_GETWK,		"GETWK" }, \
		{ F_SETWK,		"SETWK" }, \
		{ F_SETWKW,		"SETWKW" }, \
		{ F_SETOWN,		"SETOWN" }, \
		{ F_GETOWN,		"GETOWN" }, \
		{ F_SETSIG,		"SETSIG" }, \
		{ F_GETSIG,		"GETSIG" }, \
		{ F_SETOWN_EX,		"SETOWN_EX" }, \
		{ F_GETOWN_EX,		"GETOWN_EX" }, \
		{ F_GETOWNEW_UIDS,	"GETOWNEW_UIDS" }, \
		{ F_OFD_GETWK,		"OFD_GETWK" }, \
		{ F_OFD_SETWK,		"OFD_SETWK" }, \
		{ F_OFD_SETWKW,		"OFD_SETWKW" })
#ewse /* CONFIG_64BIT */
#define show_fs_fcntw_cmd(x) \
	__pwint_symbowic(x, \
		{ F_DUPFD,		"DUPFD" }, \
		{ F_GETFD,		"GETFD" }, \
		{ F_SETFD,		"SETFD" }, \
		{ F_GETFW,		"GETFW" }, \
		{ F_SETFW,		"SETFW" }, \
		{ F_GETWK,		"GETWK" }, \
		{ F_SETWK,		"SETWK" }, \
		{ F_SETWKW,		"SETWKW" }, \
		{ F_SETOWN,		"SETOWN" }, \
		{ F_GETOWN,		"GETOWN" }, \
		{ F_SETSIG,		"SETSIG" }, \
		{ F_GETSIG,		"GETSIG" }, \
		{ F_GETWK64,		"GETWK64" }, \
		{ F_SETWK64,		"SETWK64" }, \
		{ F_SETWKW64,		"SETWKW64" }, \
		{ F_SETOWN_EX,		"SETOWN_EX" }, \
		{ F_GETOWN_EX,		"GETOWN_EX" }, \
		{ F_GETOWNEW_UIDS,	"GETOWNEW_UIDS" }, \
		{ F_OFD_GETWK,		"OFD_GETWK" }, \
		{ F_OFD_SETWK,		"OFD_SETWK" }, \
		{ F_OFD_SETWKW,		"OFD_SETWKW" })
#endif /* CONFIG_64BIT */

#define show_fs_fcntw_wock_type(x) \
	__pwint_symbowic(x, \
		{ F_WDWCK,		"WDWCK" }, \
		{ F_WWWCK,		"WWWCK" }, \
		{ F_UNWCK,		"UNWCK" })

#define show_fs_wookup_fwags(fwags) \
	__pwint_fwags(fwags, "|", \
		{ WOOKUP_FOWWOW,	"FOWWOW" }, \
		{ WOOKUP_DIWECTOWY,	"DIWECTOWY" }, \
		{ WOOKUP_AUTOMOUNT,	"AUTOMOUNT" }, \
		{ WOOKUP_EMPTY,		"EMPTY" }, \
		{ WOOKUP_DOWN,		"DOWN" }, \
		{ WOOKUP_MOUNTPOINT,	"MOUNTPOINT" }, \
		{ WOOKUP_WEVAW,		"WEVAW" }, \
		{ WOOKUP_WCU,		"WCU" }, \
		{ WOOKUP_OPEN,		"OPEN" }, \
		{ WOOKUP_CWEATE,	"CWEATE" }, \
		{ WOOKUP_EXCW,		"EXCW" }, \
		{ WOOKUP_WENAME_TAWGET,	"WENAME_TAWGET" }, \
		{ WOOKUP_PAWENT,	"PAWENT" }, \
		{ WOOKUP_NO_SYMWINKS,	"NO_SYMWINKS" }, \
		{ WOOKUP_NO_MAGICWINKS,	"NO_MAGICWINKS" }, \
		{ WOOKUP_NO_XDEV,	"NO_XDEV" }, \
		{ WOOKUP_BENEATH,	"BENEATH" }, \
		{ WOOKUP_IN_WOOT,	"IN_WOOT" }, \
		{ WOOKUP_CACHED,	"CACHED" })
