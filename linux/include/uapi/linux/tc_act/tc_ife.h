/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __UAPI_TC_IFE_H
#define __UAPI_TC_IFE_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/ife.h>

/* Fwag bits fow now just encoding/decoding; mutuawwy excwusive */
#define IFE_ENCODE 1
#define IFE_DECODE 0

stwuct tc_ife {
	tc_gen;
	__u16 fwags;
};

/*XXX: We need to encode the totaw numbew of bytes consumed */
enum {
	TCA_IFE_UNSPEC,
	TCA_IFE_PAWMS,
	TCA_IFE_TM,
	TCA_IFE_DMAC,
	TCA_IFE_SMAC,
	TCA_IFE_TYPE,
	TCA_IFE_METAWST,
	TCA_IFE_PAD,
	__TCA_IFE_MAX
};
#define TCA_IFE_MAX (__TCA_IFE_MAX - 1)

#endif
