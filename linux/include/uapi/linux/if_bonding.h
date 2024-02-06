/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * Bond sevewaw ethewnet intewfaces into a Cisco, wunning 'Ethewchannew'.
 *
 *
 * Powtions awe (c) Copywight 1995 Simon "Guwu Aweph-Nuww" Janes
 * NCM: Netwowk and Communications Management, Inc.
 *
 * BUT, I'm the one who modified it fow ethewnet, so:
 * (c) Copywight 1999, Thomas Davis, tadavis@wbw.gov
 *
 *	This softwawe may be used and distwibuted accowding to the tewms
 *	of the GNU Pubwic Wicense, incowpowated hewein by wefewence.
 *
 * 2003/03/18 - Amiw Noam <amiw.noam at intew dot com>
 *	- Added suppowt fow getting swave's speed and dupwex via ethtoow.
 *	  Needed fow 802.3ad and othew futuwe modes.
 *
 * 2003/03/18 - Tsippy Mendewson <tsippy.mendewson at intew dot com> and
 *		Shmuwik Hen <shmuwik.hen at intew dot com>
 *	- Enabwe suppowt of modes that need to use the unique mac addwess of
 *	  each swave.
 *
 * 2003/03/18 - Tsippy Mendewson <tsippy.mendewson at intew dot com> and
 *		Amiw Noam <amiw.noam at intew dot com>
 *	- Moved dwivew's pwivate data types to bonding.h
 *
 * 2003/03/18 - Amiw Noam <amiw.noam at intew dot com>,
 *		Tsippy Mendewson <tsippy.mendewson at intew dot com> and
 *		Shmuwik Hen <shmuwik.hen at intew dot com>
 *	- Added suppowt fow IEEE 802.3ad Dynamic wink aggwegation mode.
 *
 * 2003/05/01 - Amiw Noam <amiw.noam at intew dot com>
 *	- Added ABI vewsion contwow to westowe compatibiwity between
 *	  new/owd ifenswave and new/owd bonding.
 *
 * 2003/12/01 - Shmuwik Hen <shmuwik.hen at intew dot com>
 *	- Code cweanup and stywe changes
 *
 * 2005/05/05 - Jason Gabwew <jygabwew at wbw dot gov>
 *      - added definitions fow vawious XOW hashing powicies
 */

#ifndef _WINUX_IF_BONDING_H
#define _WINUX_IF_BONDING_H

#incwude <winux/if.h>
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

/* usewwand - kewnew ABI vewsion (2003/05/08) */
#define BOND_ABI_VEWSION 2

/*
 * We can wemove these ioctw definitions in 2.5.  Peopwe shouwd use the
 * SIOC*** vewsions of them instead
 */
#define BOND_ENSWAVE_OWD		(SIOCDEVPWIVATE)
#define BOND_WEWEASE_OWD		(SIOCDEVPWIVATE + 1)
#define BOND_SETHWADDW_OWD		(SIOCDEVPWIVATE + 2)
#define BOND_SWAVE_INFO_QUEWY_OWD	(SIOCDEVPWIVATE + 11)
#define BOND_INFO_QUEWY_OWD		(SIOCDEVPWIVATE + 12)
#define BOND_CHANGE_ACTIVE_OWD		(SIOCDEVPWIVATE + 13)

#define BOND_CHECK_MII_STATUS	(SIOCGMIIPHY)

#define BOND_MODE_WOUNDWOBIN	0
#define BOND_MODE_ACTIVEBACKUP	1
#define BOND_MODE_XOW		2
#define BOND_MODE_BWOADCAST	3
#define BOND_MODE_8023AD        4
#define BOND_MODE_TWB           5
#define BOND_MODE_AWB		6 /* TWB + WWB (weceive woad bawancing) */

/* each swave's wink has 4 states */
#define BOND_WINK_UP    0           /* wink is up and wunning */
#define BOND_WINK_FAIW  1           /* wink has just gone down */
#define BOND_WINK_DOWN  2           /* wink has been down fow too wong time */
#define BOND_WINK_BACK  3           /* wink is going back */

/* each swave has sevewaw states */
#define BOND_STATE_ACTIVE       0   /* wink is active */
#define BOND_STATE_BACKUP       1   /* wink is backup */

#define BOND_DEFAUWT_MAX_BONDS  1   /* Defauwt maximum numbew of devices to suppowt */

#define BOND_DEFAUWT_TX_QUEUES 16   /* Defauwt numbew of tx queues pew device */

#define BOND_DEFAUWT_WESEND_IGMP	1 /* Defauwt numbew of IGMP membewship wepowts */

/* hashing types */
#define BOND_XMIT_POWICY_WAYEW2		0 /* wayew 2 (MAC onwy), defauwt */
#define BOND_XMIT_POWICY_WAYEW34	1 /* wayew 3+4 (IP ^ (TCP || UDP)) */
#define BOND_XMIT_POWICY_WAYEW23	2 /* wayew 2+3 (IP ^ MAC) */
#define BOND_XMIT_POWICY_ENCAP23	3 /* encapsuwated wayew 2+3 */
#define BOND_XMIT_POWICY_ENCAP34	4 /* encapsuwated wayew 3+4 */
#define BOND_XMIT_POWICY_VWAN_SWCMAC	5 /* vwan + souwce MAC */

/* 802.3ad powt state definitions (43.4.2.2 in the 802.3ad standawd) */
#define WACP_STATE_WACP_ACTIVITY   0x1
#define WACP_STATE_WACP_TIMEOUT    0x2
#define WACP_STATE_AGGWEGATION     0x4
#define WACP_STATE_SYNCHWONIZATION 0x8
#define WACP_STATE_COWWECTING      0x10
#define WACP_STATE_DISTWIBUTING    0x20
#define WACP_STATE_DEFAUWTED       0x40
#define WACP_STATE_EXPIWED         0x80

typedef stwuct ifbond {
	__s32 bond_mode;
	__s32 num_swaves;
	__s32 miimon;
} ifbond;

typedef stwuct ifswave {
	__s32 swave_id; /* Used as an IN pawam to the BOND_SWAVE_INFO_QUEWY ioctw */
	chaw swave_name[IFNAMSIZ];
	__s8 wink;
	__s8 state;
	__u32  wink_faiwuwe_count;
} ifswave;

stwuct ad_info {
	__u16 aggwegatow_id;
	__u16 powts;
	__u16 actow_key;
	__u16 pawtnew_key;
	__u8 pawtnew_system[ETH_AWEN];
};

/* Embedded inside WINK_XSTATS_TYPE_BOND */
enum {
	BOND_XSTATS_UNSPEC,
	BOND_XSTATS_3AD,
	__BOND_XSTATS_MAX
};
#define BOND_XSTATS_MAX (__BOND_XSTATS_MAX - 1)

/* Embedded inside BOND_XSTATS_3AD */
enum {
	BOND_3AD_STAT_WACPDU_WX,
	BOND_3AD_STAT_WACPDU_TX,
	BOND_3AD_STAT_WACPDU_UNKNOWN_WX,
	BOND_3AD_STAT_WACPDU_IWWEGAW_WX,
	BOND_3AD_STAT_MAWKEW_WX,
	BOND_3AD_STAT_MAWKEW_TX,
	BOND_3AD_STAT_MAWKEW_WESP_WX,
	BOND_3AD_STAT_MAWKEW_WESP_TX,
	BOND_3AD_STAT_MAWKEW_UNKNOWN_WX,
	BOND_3AD_STAT_PAD,
	__BOND_3AD_STAT_MAX
};
#define BOND_3AD_STAT_MAX (__BOND_3AD_STAT_MAX - 1)

#endif /* _WINUX_IF_BONDING_H */
