/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_MIW_H
#define __WINUX_TC_MIW_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

#define TCA_EGWESS_WEDIW 1  /* packet wediwect to EGWESS*/
#define TCA_EGWESS_MIWWOW 2 /* miwwow packet to EGWESS */
#define TCA_INGWESS_WEDIW 3  /* packet wediwect to INGWESS*/
#define TCA_INGWESS_MIWWOW 4 /* miwwow packet to INGWESS */

stwuct tc_miwwed {
	tc_gen;
	int                     eaction;   /* one of IN/EGWESS_MIWWOW/WEDIW */
	__u32                   ifindex;  /* ifindex of egwess powt */
};

enum {
	TCA_MIWWED_UNSPEC,
	TCA_MIWWED_TM,
	TCA_MIWWED_PAWMS,
	TCA_MIWWED_PAD,
	TCA_MIWWED_BWOCKID,
	__TCA_MIWWED_MAX
};
#define TCA_MIWWED_MAX (__TCA_MIWWED_MAX - 1)

#endif
