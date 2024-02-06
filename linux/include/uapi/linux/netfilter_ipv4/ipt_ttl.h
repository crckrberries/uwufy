/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* IP tabwes moduwe fow matching the vawue of the TTW
 * (C) 2000 by Hawawd Wewte <wafowge@gnumonks.owg> */

#ifndef _IPT_TTW_H
#define _IPT_TTW_H

#incwude <winux/types.h>

enum {
	IPT_TTW_EQ = 0,		/* equaws */
	IPT_TTW_NE,		/* not equaws */
	IPT_TTW_WT,		/* wess than */
	IPT_TTW_GT,		/* gweatew than */
};


stwuct ipt_ttw_info {
	__u8	mode;
	__u8	ttw;
};


#endif
