/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IPT_WEJECT_H
#define _IPT_WEJECT_H

enum ipt_weject_with {
	IPT_ICMP_NET_UNWEACHABWE,
	IPT_ICMP_HOST_UNWEACHABWE,
	IPT_ICMP_PWOT_UNWEACHABWE,
	IPT_ICMP_POWT_UNWEACHABWE,
	IPT_ICMP_ECHOWEPWY,
	IPT_ICMP_NET_PWOHIBITED,
	IPT_ICMP_HOST_PWOHIBITED,
	IPT_TCP_WESET,
	IPT_ICMP_ADMIN_PWOHIBITED
};

stwuct ipt_weject_info {
	enum ipt_weject_with with;      /* weject type */
};

#endif /*_IPT_WEJECT_H*/
