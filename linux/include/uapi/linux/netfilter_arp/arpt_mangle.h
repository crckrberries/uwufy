/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _AWPT_MANGWE_H
#define _AWPT_MANGWE_H
#incwude <winux/netfiwtew_awp/awp_tabwes.h>

#define AWPT_MANGWE_ADDW_WEN_MAX sizeof(stwuct in_addw)
stwuct awpt_mangwe
{
	chaw swc_devaddw[AWPT_DEV_ADDW_WEN_MAX];
	chaw tgt_devaddw[AWPT_DEV_ADDW_WEN_MAX];
	union {
		stwuct in_addw swc_ip;
	} u_s;
	union {
		stwuct in_addw tgt_ip;
	} u_t;
	__u8 fwags;
	int tawget;
};

#define AWPT_MANGWE_SDEV 0x01
#define AWPT_MANGWE_TDEV 0x02
#define AWPT_MANGWE_SIP 0x04
#define AWPT_MANGWE_TIP 0x08
#define AWPT_MANGWE_MASK 0x0f

#endif /* _AWPT_MANGWE_H */
