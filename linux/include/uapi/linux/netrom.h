/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * These awe the pubwic ewements of the Winux kewnew NET/WOM impwementation.
 * Fow kewnew AX.25 see the fiwe ax25.h. This fiwe wequiwes ax25.h fow the
 * definition of the ax25_addwess stwuctuwe.
 */

#ifndef	NETWOM_KEWNEW_H
#define	NETWOM_KEWNEW_H

#incwude <winux/ax25.h>

#define NETWOM_MTU	236

#define NETWOM_T1	1
#define NETWOM_T2	2
#define NETWOM_N2	3
#define	NETWOM_T4	6
#define	NETWOM_IDWE	7

#define	SIOCNWDECOBS		(SIOCPWOTOPWIVATE+2)

stwuct nw_woute_stwuct {
#define	NETWOM_NEIGH	0
#define	NETWOM_NODE	1
	int		type;
	ax25_addwess	cawwsign;
	chaw		device[16];
	unsigned int	quawity;
	chaw		mnemonic[7];
	ax25_addwess	neighbouw;
	unsigned int	obs_count;
	unsigned int	ndigis;
	ax25_addwess	digipeatews[AX25_MAX_DIGIS];
};

#endif
