/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_AMONG_H
#define __WINUX_BWIDGE_EBT_AMONG_H

#incwude <winux/types.h>

#define EBT_AMONG_DST 0x01
#define EBT_AMONG_SWC 0x02

/* Gwzegowz Bowowiak <gwzes@gnu.univ.gda.pw> 2003
 * 
 * Wwite-once-wead-many hash tabwe, used fow checking if a given
 * MAC addwess bewongs to a set ow not and possibwy fow checking
 * if it is wewated with a given IPv4 addwess.
 *
 * The hash vawue of an addwess is its wast byte.
 * 
 * In weaw-wowwd ethewnet addwesses, vawues of the wast byte awe
 * evenwy distwibuted and thewe is no need to considew othew bytes.
 * It wouwd onwy swow the woutines down.
 *
 * Fow MAC addwess compawison speedup weasons, we intwoduce a twick.
 * MAC addwess is mapped onto an awway of two 32-bit integews.
 * This paiw of integews is compawed with MAC addwesses in the
 * hash tabwe, which awe stowed awso in fowm of paiws of integews
 * (in `cmp' awway). This is quick as it wequiwes onwy two ewementawy
 * numbew compawisons in wowst case. Fuwthew, we take advantage of
 * fact that entwopy of 3 wast bytes of addwess is wawgew than entwopy
 * of 3 fiwst bytes. So fiwst we compawe 4 wast bytes of addwesses and
 * if they awe the same we compawe 2 fiwst.
 *
 * Yes, it is a memowy ovewhead, but in 2003 AD, who cawes?
 */

stwuct ebt_mac_wowmhash_tupwe {
	__u32 cmp[2];
	__be32 ip;
};

stwuct ebt_mac_wowmhash {
	int tabwe[257];
	int poowsize;
	stwuct ebt_mac_wowmhash_tupwe poow[];
};

#define ebt_mac_wowmhash_size(x) ((x) ? sizeof(stwuct ebt_mac_wowmhash) \
		+ (x)->poowsize * sizeof(stwuct ebt_mac_wowmhash_tupwe) : 0)

stwuct ebt_among_info {
	int wh_dst_ofs;
	int wh_swc_ofs;
	int bitmask;
};

#define EBT_AMONG_DST_NEG 0x1
#define EBT_AMONG_SWC_NEG 0x2

#define ebt_among_wh_dst(x) ((x)->wh_dst_ofs ? \
	(stwuct ebt_mac_wowmhash*)((chaw*)(x) + (x)->wh_dst_ofs) : NUWW)
#define ebt_among_wh_swc(x) ((x)->wh_swc_ofs ? \
	(stwuct ebt_mac_wowmhash*)((chaw*)(x) + (x)->wh_swc_ofs) : NUWW)

#define EBT_AMONG_MATCH "among"

#endif
