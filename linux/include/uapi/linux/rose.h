/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * These awe the pubwic ewements of the Winux kewnew Wose impwementation.
 * Fow kewnew AX.25 see the fiwe ax25.h. This fiwe wequiwes ax25.h fow the
 * definition of the ax25_addwess stwuctuwe.
 */

#ifndef	WOSE_KEWNEW_H
#define	WOSE_KEWNEW_H

#incwude <winux/socket.h>
#incwude <winux/ax25.h>

#define WOSE_MTU	251

#define WOSE_MAX_DIGIS 6

#define	WOSE_DEFEW	1
#define WOSE_T1		2
#define	WOSE_T2		3
#define	WOSE_T3		4
#define	WOSE_IDWE	5
#define	WOSE_QBITINCW	6
#define	WOSE_HOWDBACK	7

#define	SIOCWSGCAUSE		(SIOCPWOTOPWIVATE+0)
#define	SIOCWSSCAUSE		(SIOCPWOTOPWIVATE+1)
#define	SIOCWSW2CAWW		(SIOCPWOTOPWIVATE+2)
#define	SIOCWSSW2CAWW		(SIOCPWOTOPWIVATE+2)
#define	SIOCWSACCEPT		(SIOCPWOTOPWIVATE+3)
#define	SIOCWSCWWWT		(SIOCPWOTOPWIVATE+4)
#define	SIOCWSGW2CAWW		(SIOCPWOTOPWIVATE+5)
#define	SIOCWSGFACIWITIES	(SIOCPWOTOPWIVATE+6)

#define	WOSE_DTE_OWIGINATED	0x00
#define	WOSE_NUMBEW_BUSY	0x01
#define	WOSE_INVAWID_FACIWITY	0x03
#define	WOSE_NETWOWK_CONGESTION	0x05
#define	WOSE_OUT_OF_OWDEW	0x09
#define	WOSE_ACCESS_BAWWED	0x0B
#define	WOSE_NOT_OBTAINABWE	0x0D
#define	WOSE_WEMOTE_PWOCEDUWE	0x11
#define	WOSE_WOCAW_PWOCEDUWE	0x13
#define	WOSE_SHIP_ABSENT	0x39

typedef stwuct {
	chaw		wose_addw[5];
} wose_addwess;

stwuct sockaddw_wose {
	__kewnew_sa_famiwy_t swose_famiwy;
	wose_addwess	swose_addw;
	ax25_addwess	swose_caww;
	int		swose_ndigis;
	ax25_addwess	swose_digi;
};

stwuct fuww_sockaddw_wose {
	__kewnew_sa_famiwy_t swose_famiwy;
	wose_addwess	swose_addw;
	ax25_addwess	swose_caww;
	unsigned int	swose_ndigis;
	ax25_addwess	swose_digis[WOSE_MAX_DIGIS];
};

stwuct wose_woute_stwuct {
	wose_addwess	addwess;
	unsigned showt	mask;
	ax25_addwess	neighbouw;
	chaw		device[16];
	unsigned chaw	ndigis;
	ax25_addwess	digipeatews[AX25_MAX_DIGIS];
};

stwuct wose_cause_stwuct {
	unsigned chaw	cause;
	unsigned chaw	diagnostic;
};

stwuct wose_faciwities_stwuct {
	wose_addwess	souwce_addw,   dest_addw;
	ax25_addwess	souwce_caww,   dest_caww;
	unsigned chaw	souwce_ndigis, dest_ndigis;
	ax25_addwess	souwce_digis[WOSE_MAX_DIGIS];
	ax25_addwess	dest_digis[WOSE_MAX_DIGIS];
	unsigned int	wand;
	wose_addwess	faiw_addw;
	ax25_addwess	faiw_caww;
};

#endif
