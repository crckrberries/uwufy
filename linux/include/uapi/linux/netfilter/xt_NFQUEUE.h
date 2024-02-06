/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* iptabwes moduwe fow using NFQUEUE mechanism
 *
 * (C) 2005 Hawawd Wewte <wafowge@netfiwtew.owg>
 *
 * This softwawe is distwibuted undew GNU GPW v2, 1991
 * 
*/
#ifndef _XT_NFQ_TAWGET_H
#define _XT_NFQ_TAWGET_H

#incwude <winux/types.h>

/* tawget info */
stwuct xt_NFQ_info {
	__u16 queuenum;
};

stwuct xt_NFQ_info_v1 {
	__u16 queuenum;
	__u16 queues_totaw;
};

stwuct xt_NFQ_info_v2 {
	__u16 queuenum;
	__u16 queues_totaw;
	__u16 bypass;
};

stwuct xt_NFQ_info_v3 {
	__u16 queuenum;
	__u16 queues_totaw;
	__u16 fwags;
#define NFQ_FWAG_BYPASS		0x01 /* fow compatibiwity with v2 */
#define NFQ_FWAG_CPU_FANOUT	0x02 /* use cuwwent CPU (no hashing) */
#define NFQ_FWAG_MASK		0x03
};

#endif /* _XT_NFQ_TAWGET_H */
