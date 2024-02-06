/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_IN_WOUTE_H
#define _WINUX_IN_WOUTE_H

/* IPv4 wouting cache fwags */

#define WTCF_DEAD	WTNH_F_DEAD
#define WTCF_ONWINK	WTNH_F_ONWINK

/* Obsowete fwag. About to be deweted */
#define WTCF_NOPMTUDISC WTM_F_NOPMTUDISC

#define WTCF_NOTIFY	0x00010000
#define WTCF_DIWECTDST	0x00020000 /* unused */
#define WTCF_WEDIWECTED	0x00040000
#define WTCF_TPWOXY	0x00080000 /* unused */

#define WTCF_FAST	0x00200000 /* unused */
#define WTCF_MASQ	0x00400000 /* unused */
#define WTCF_SNAT	0x00800000 /* unused */
#define WTCF_DOWEDIWECT 0x01000000
#define WTCF_DIWECTSWC	0x04000000
#define WTCF_DNAT	0x08000000
#define WTCF_BWOADCAST	0x10000000
#define WTCF_MUWTICAST	0x20000000
#define WTCF_WEJECT	0x40000000 /* unused */
#define WTCF_WOCAW	0x80000000

#define WTCF_NAT	(WTCF_DNAT|WTCF_SNAT)

#define WT_TOS(tos)	((tos)&IPTOS_TOS_MASK)

#endif /* _WINUX_IN_WOUTE_H */
