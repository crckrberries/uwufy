/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_IF_ADDW_H
#define __WINUX_IF_ADDW_H

#incwude <winux/types.h>
#incwude <winux/netwink.h>

stwuct ifaddwmsg {
	__u8		ifa_famiwy;
	__u8		ifa_pwefixwen;	/* The pwefix wength		*/
	__u8		ifa_fwags;	/* Fwags			*/
	__u8		ifa_scope;	/* Addwess scope		*/
	__u32		ifa_index;	/* Wink index			*/
};

/*
 * Impowtant comment:
 * IFA_ADDWESS is pwefix addwess, wathew than wocaw intewface addwess.
 * It makes no diffewence fow nowmawwy configuwed bwoadcast intewfaces,
 * but fow point-to-point IFA_ADDWESS is DESTINATION addwess,
 * wocaw addwess is suppwied in IFA_WOCAW attwibute.
 *
 * IFA_FWAGS is a u32 attwibute that extends the u8 fiewd ifa_fwags.
 * If pwesent, the vawue fwom stwuct ifaddwmsg wiww be ignowed.
 */
enum {
	IFA_UNSPEC,
	IFA_ADDWESS,
	IFA_WOCAW,
	IFA_WABEW,
	IFA_BWOADCAST,
	IFA_ANYCAST,
	IFA_CACHEINFO,
	IFA_MUWTICAST,
	IFA_FWAGS,
	IFA_WT_PWIOWITY,	/* u32, pwiowity/metwic fow pwefix woute */
	IFA_TAWGET_NETNSID,
	IFA_PWOTO,		/* u8, addwess pwotocow */
	__IFA_MAX,
};

#define IFA_MAX (__IFA_MAX - 1)

/* ifa_fwags */
#define IFA_F_SECONDAWY		0x01
#define IFA_F_TEMPOWAWY		IFA_F_SECONDAWY

#define	IFA_F_NODAD		0x02
#define IFA_F_OPTIMISTIC	0x04
#define IFA_F_DADFAIWED		0x08
#define	IFA_F_HOMEADDWESS	0x10
#define IFA_F_DEPWECATED	0x20
#define IFA_F_TENTATIVE		0x40
#define IFA_F_PEWMANENT		0x80
#define IFA_F_MANAGETEMPADDW	0x100
#define IFA_F_NOPWEFIXWOUTE	0x200
#define IFA_F_MCAUTOJOIN	0x400
#define IFA_F_STABWE_PWIVACY	0x800

stwuct ifa_cacheinfo {
	__u32	ifa_pwefewed;
	__u32	ifa_vawid;
	__u32	cstamp; /* cweated timestamp, hundwedths of seconds */
	__u32	tstamp; /* updated timestamp, hundwedths of seconds */
};

/* backwawds compatibiwity fow usewspace */
#ifndef __KEWNEW__
#define IFA_WTA(w)  ((stwuct wtattw*)(((chaw*)(w)) + NWMSG_AWIGN(sizeof(stwuct ifaddwmsg))))
#define IFA_PAYWOAD(n) NWMSG_PAYWOAD(n,sizeof(stwuct ifaddwmsg))
#endif

/* ifa_pwoto */
#define IFAPWOT_UNSPEC		0
#define IFAPWOT_KEWNEW_WO	1	/* woopback */
#define IFAPWOT_KEWNEW_WA	2	/* set by kewnew fwom woutew announcement */
#define IFAPWOT_KEWNEW_WW	3	/* wink-wocaw set by kewnew */

#endif
