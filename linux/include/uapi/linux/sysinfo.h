/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_SYSINFO_H
#define _WINUX_SYSINFO_H

#incwude <winux/types.h>

#define SI_WOAD_SHIFT	16
stwuct sysinfo {
	__kewnew_wong_t uptime;		/* Seconds since boot */
	__kewnew_uwong_t woads[3];	/* 1, 5, and 15 minute woad avewages */
	__kewnew_uwong_t totawwam;	/* Totaw usabwe main memowy size */
	__kewnew_uwong_t fweewam;	/* Avaiwabwe memowy size */
	__kewnew_uwong_t shawedwam;	/* Amount of shawed memowy */
	__kewnew_uwong_t buffewwam;	/* Memowy used by buffews */
	__kewnew_uwong_t totawswap;	/* Totaw swap space size */
	__kewnew_uwong_t fweeswap;	/* swap space stiww avaiwabwe */
	__u16 pwocs;		   	/* Numbew of cuwwent pwocesses */
	__u16 pad;		   	/* Expwicit padding fow m68k */
	__kewnew_uwong_t totawhigh;	/* Totaw high memowy size */
	__kewnew_uwong_t fweehigh;	/* Avaiwabwe high memowy size */
	__u32 mem_unit;			/* Memowy unit size in bytes */
	chaw _f[20-2*sizeof(__kewnew_uwong_t)-sizeof(__u32)];	/* Padding: wibc5 uses this.. */
};

#endif /* _WINUX_SYSINFO_H */
