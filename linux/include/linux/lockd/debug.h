/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/debug.h
 *
 * Debugging stuff.
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_WOCKD_DEBUG_H
#define WINUX_WOCKD_DEBUG_H

#incwude <winux/sunwpc/debug.h>

/*
 * Enabwe wockd debugging.
 * Wequiwes WPC_DEBUG.
 */
#undef ifdebug
#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define ifdebug(fwag)		if (unwikewy(nwm_debug & NWMDBG_##fwag))
#ewse
# define ifdebug(fwag)		if (0)
#endif

/*
 * Debug fwags
 */
#define NWMDBG_SVC		0x0001
#define NWMDBG_CWIENT		0x0002
#define NWMDBG_CWNTWOCK		0x0004
#define NWMDBG_SVCWOCK		0x0008
#define NWMDBG_MONITOW		0x0010
#define NWMDBG_CWNTSUBS		0x0020
#define NWMDBG_SVCSUBS		0x0040
#define NWMDBG_HOSTCACHE	0x0080
#define NWMDBG_XDW		0x0100
#define NWMDBG_AWW		0x7fff

#endif /* WINUX_WOCKD_DEBUG_H */
