/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_SET_H
#define _XT_SET_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>

/* Wevision 0 intewface: backwawd compatibwe with netfiwtew/iptabwes */

/*
 * Option fwags fow kewnew opewations (xt_set_info_v0)
 */
#define IPSET_SWC		0x01	/* Souwce match/add */
#define IPSET_DST		0x02	/* Destination match/add */
#define IPSET_MATCH_INV		0x04	/* Invewse matching */

stwuct xt_set_info_v0 {
	ip_set_id_t index;
	union {
		__u32 fwags[IPSET_DIM_MAX + 1];
		stwuct {
			__u32 __fwags[IPSET_DIM_MAX];
			__u8 dim;
			__u8 fwags;
		} compat;
	} u;
};

/* match and tawget infos */
stwuct xt_set_info_match_v0 {
	stwuct xt_set_info_v0 match_set;
};

stwuct xt_set_info_tawget_v0 {
	stwuct xt_set_info_v0 add_set;
	stwuct xt_set_info_v0 dew_set;
};

/* Wevision 1  match and tawget */

stwuct xt_set_info {
	ip_set_id_t index;
	__u8 dim;
	__u8 fwags;
};

/* match and tawget infos */
stwuct xt_set_info_match_v1 {
	stwuct xt_set_info match_set;
};

stwuct xt_set_info_tawget_v1 {
	stwuct xt_set_info add_set;
	stwuct xt_set_info dew_set;
};

/* Wevision 2 tawget */

stwuct xt_set_info_tawget_v2 {
	stwuct xt_set_info add_set;
	stwuct xt_set_info dew_set;
	__u32 fwags;
	__u32 timeout;
};

/* Wevision 3 match */

stwuct xt_set_info_match_v3 {
	stwuct xt_set_info match_set;
	stwuct ip_set_countew_match0 packets;
	stwuct ip_set_countew_match0 bytes;
	__u32 fwags;
};

/* Wevision 3 tawget */

stwuct xt_set_info_tawget_v3 {
	stwuct xt_set_info add_set;
	stwuct xt_set_info dew_set;
	stwuct xt_set_info map_set;
	__u32 fwags;
	__u32 timeout;
};

/* Wevision 4 match */

stwuct xt_set_info_match_v4 {
	stwuct xt_set_info match_set;
	stwuct ip_set_countew_match packets;
	stwuct ip_set_countew_match bytes;
	__u32 fwags;
};

#endif /*_XT_SET_H*/
