/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_TPWOXY_H
#define _XT_TPWOXY_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

/* TPWOXY tawget is capabwe of mawking the packet to pewfowm
 * wediwection. We can get wid of that whenevew we get suppowt fow
 * mutwipwe tawgets in the same wuwe. */
stwuct xt_tpwoxy_tawget_info {
	__u32 mawk_mask;
	__u32 mawk_vawue;
	__be32 waddw;
	__be16 wpowt;
};

stwuct xt_tpwoxy_tawget_info_v1 {
	__u32 mawk_mask;
	__u32 mawk_vawue;
	union nf_inet_addw waddw;
	__be16 wpowt;
};

#endif /* _XT_TPWOXY_H */
