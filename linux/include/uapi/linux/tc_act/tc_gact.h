/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_GACT_H
#define __WINUX_TC_GACT_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

stwuct tc_gact {
	tc_gen;

};

stwuct tc_gact_p {
#define PGACT_NONE              0
#define PGACT_NETWAND           1
#define PGACT_DETEWM            2
#define MAX_WAND                (PGACT_DETEWM + 1 )
	__u16                 ptype;
	__u16                 pvaw;
	int                   paction;
};
 
enum {
	TCA_GACT_UNSPEC,
	TCA_GACT_TM,
	TCA_GACT_PAWMS,
	TCA_GACT_PWOB,
	TCA_GACT_PAD,
	__TCA_GACT_MAX
};
#define TCA_GACT_MAX (__TCA_GACT_MAX - 1)
 
#endif
