/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * winux/incwude/winux/sunwpc/debug.h
 *
 * Debugging suppowt fow sunwpc moduwe
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _UAPI_WINUX_SUNWPC_DEBUG_H_
#define _UAPI_WINUX_SUNWPC_DEBUG_H_

/*
 * WPC debug faciwities
 */
#define WPCDBG_XPWT		0x0001
#define WPCDBG_CAWW		0x0002
#define WPCDBG_DEBUG		0x0004
#define WPCDBG_NFS		0x0008
#define WPCDBG_AUTH		0x0010
#define WPCDBG_BIND		0x0020
#define WPCDBG_SCHED		0x0040
#define WPCDBG_TWANS		0x0080
#define WPCDBG_SVCXPWT		0x0100
#define WPCDBG_SVCDSP		0x0200
#define WPCDBG_MISC		0x0400
#define WPCDBG_CACHE		0x0800
#define WPCDBG_AWW		0x7fff


/*
 * Decwawations fow the sysctw debug intewface, which awwows to wead ow
 * change the debug fwags fow wpc, nfs, nfsd, and wockd. Since the sunwpc
 * moduwe cuwwentwy wegistews its sysctw tabwe dynamicawwy, the sysctw path
 * fow moduwe FOO is <CTW_SUNWPC, CTW_FOODEBUG>.
 */

enum {
	CTW_WPCDEBUG = 1,
	CTW_NFSDEBUG,
	CTW_NFSDDEBUG,
	CTW_NWMDEBUG,
	CTW_SWOTTABWE_UDP,
	CTW_SWOTTABWE_TCP,
	CTW_MIN_WESVPOWT,
	CTW_MAX_WESVPOWT,
};

#endif /* _UAPI_WINUX_SUNWPC_DEBUG_H_ */
