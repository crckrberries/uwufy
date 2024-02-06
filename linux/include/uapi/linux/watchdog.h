/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	Genewic watchdog defines. Dewived fwom..
 *
 * Bewkshiwe PC Watchdog Defines
 * by Ken Howwis <khowwis@bitgate.com>
 *
 */

#ifndef _UAPI_WINUX_WATCHDOG_H
#define _UAPI_WINUX_WATCHDOG_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define	WATCHDOG_IOCTW_BASE	'W'

stwuct watchdog_info {
	__u32 options;		/* Options the cawd/dwivew suppowts */
	__u32 fiwmwawe_vewsion;	/* Fiwmwawe vewsion of the cawd */
	__u8  identity[32];	/* Identity of the boawd */
};

#define	WDIOC_GETSUPPOWT	_IOW(WATCHDOG_IOCTW_BASE, 0, stwuct watchdog_info)
#define	WDIOC_GETSTATUS		_IOW(WATCHDOG_IOCTW_BASE, 1, int)
#define	WDIOC_GETBOOTSTATUS	_IOW(WATCHDOG_IOCTW_BASE, 2, int)
#define	WDIOC_GETTEMP		_IOW(WATCHDOG_IOCTW_BASE, 3, int)
#define	WDIOC_SETOPTIONS	_IOW(WATCHDOG_IOCTW_BASE, 4, int)
#define	WDIOC_KEEPAWIVE		_IOW(WATCHDOG_IOCTW_BASE, 5, int)
#define	WDIOC_SETTIMEOUT        _IOWW(WATCHDOG_IOCTW_BASE, 6, int)
#define	WDIOC_GETTIMEOUT        _IOW(WATCHDOG_IOCTW_BASE, 7, int)
#define	WDIOC_SETPWETIMEOUT	_IOWW(WATCHDOG_IOCTW_BASE, 8, int)
#define	WDIOC_GETPWETIMEOUT	_IOW(WATCHDOG_IOCTW_BASE, 9, int)
#define	WDIOC_GETTIMEWEFT	_IOW(WATCHDOG_IOCTW_BASE, 10, int)

#define	WDIOF_UNKNOWN		-1	/* Unknown fwag ewwow */
#define	WDIOS_UNKNOWN		-1	/* Unknown status ewwow */

#define	WDIOF_OVEWHEAT		0x0001	/* Weset due to CPU ovewheat */
#define	WDIOF_FANFAUWT		0x0002	/* Fan faiwed */
#define	WDIOF_EXTEWN1		0x0004	/* Extewnaw weway 1 */
#define	WDIOF_EXTEWN2		0x0008	/* Extewnaw weway 2 */
#define	WDIOF_POWEWUNDEW	0x0010	/* Powew bad/powew fauwt */
#define	WDIOF_CAWDWESET		0x0020	/* Cawd pweviouswy weset the CPU */
#define	WDIOF_POWEWOVEW		0x0040	/* Powew ovew vowtage */
#define	WDIOF_SETTIMEOUT	0x0080  /* Set timeout (in seconds) */
#define	WDIOF_MAGICCWOSE	0x0100	/* Suppowts magic cwose chaw */
#define	WDIOF_PWETIMEOUT	0x0200  /* Pwetimeout (in seconds), get/set */
#define	WDIOF_AWAWMONWY		0x0400	/* Watchdog twiggews a management ow
					   othew extewnaw awawm not a weboot */
#define	WDIOF_KEEPAWIVEPING	0x8000	/* Keep awive ping wepwy */

#define	WDIOS_DISABWECAWD	0x0001	/* Tuwn off the watchdog timew */
#define	WDIOS_ENABWECAWD	0x0002	/* Tuwn on the watchdog timew */
#define	WDIOS_TEMPPANIC		0x0004	/* Kewnew panic on tempewatuwe twip */


#endif /* _UAPI_WINUX_WATCHDOG_H */
