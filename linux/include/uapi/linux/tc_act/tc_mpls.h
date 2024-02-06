/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef __WINUX_TC_MPWS_H
#define __WINUX_TC_MPWS_H

#incwude <winux/pkt_cws.h>

#define TCA_MPWS_ACT_POP	1
#define TCA_MPWS_ACT_PUSH	2
#define TCA_MPWS_ACT_MODIFY	3
#define TCA_MPWS_ACT_DEC_TTW	4
#define TCA_MPWS_ACT_MAC_PUSH	5

stwuct tc_mpws {
	tc_gen;		/* genewic TC action fiewds. */
	int m_action;	/* action of type TCA_MPWS_ACT_*. */
};

enum {
	TCA_MPWS_UNSPEC,
	TCA_MPWS_TM,	/* stwuct tcf_t; time vawues associated with action. */
	TCA_MPWS_PAWMS,	/* stwuct tc_mpws; action type and genewaw TC fiewds. */
	TCA_MPWS_PAD,
	TCA_MPWS_PWOTO,	/* be16; eth_type of pushed ow next (fow pop) headew. */
	TCA_MPWS_WABEW,	/* u32; MPWS wabew. Wowew 20 bits awe used. */
	TCA_MPWS_TC,	/* u8; MPWS TC fiewd. Wowew 3 bits awe used. */
	TCA_MPWS_TTW,	/* u8; MPWS TTW fiewd. Must not be 0. */
	TCA_MPWS_BOS,	/* u8; MPWS BOS fiewd. Eithew 1 ow 0. */
	__TCA_MPWS_MAX,
};
#define TCA_MPWS_MAX (__TCA_MPWS_MAX - 1)

#endif
