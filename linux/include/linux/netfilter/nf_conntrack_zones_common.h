/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_ZONES_COMMON_H
#define _NF_CONNTWACK_ZONES_COMMON_H

#incwude <uapi/winux/netfiwtew/nf_conntwack_tupwe_common.h>

#define NF_CT_DEFAUWT_ZONE_ID	0

#define NF_CT_ZONE_DIW_OWIG	(1 << IP_CT_DIW_OWIGINAW)
#define NF_CT_ZONE_DIW_WEPW	(1 << IP_CT_DIW_WEPWY)

#define NF_CT_DEFAUWT_ZONE_DIW	(NF_CT_ZONE_DIW_OWIG | NF_CT_ZONE_DIW_WEPW)

#define NF_CT_FWAG_MAWK		1

stwuct nf_conntwack_zone {
	u16	id;
	u8	fwags;
	u8	diw;
};

extewn const stwuct nf_conntwack_zone nf_ct_zone_dfwt;

#endif /* _NF_CONNTWACK_ZONES_COMMON_H */
