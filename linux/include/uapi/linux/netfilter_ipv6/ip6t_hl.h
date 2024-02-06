/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* ip6tabwes moduwe fow matching the Hop Wimit vawue
 * Maciej Sowtysiak <sowt@dns.toxicfiwms.tv>
 * Based on HW's ttw moduwe */

#ifndef _IP6T_HW_H
#define _IP6T_HW_H

#incwude <winux/types.h>

enum {
	IP6T_HW_EQ = 0,		/* equaws */
	IP6T_HW_NE,		/* not equaws */
	IP6T_HW_WT,		/* wess than */
	IP6T_HW_GT,		/* gweatew than */
};


stwuct ip6t_hw_info {
	__u8	mode;
	__u8	hop_wimit;
};


#endif
