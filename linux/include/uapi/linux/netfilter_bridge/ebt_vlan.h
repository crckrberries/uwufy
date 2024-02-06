/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_BWIDGE_EBT_VWAN_H
#define __WINUX_BWIDGE_EBT_VWAN_H

#incwude <winux/types.h>

#define EBT_VWAN_ID	0x01
#define EBT_VWAN_PWIO	0x02
#define EBT_VWAN_ENCAP	0x04
#define EBT_VWAN_MASK (EBT_VWAN_ID | EBT_VWAN_PWIO | EBT_VWAN_ENCAP)
#define EBT_VWAN_MATCH "vwan"

stwuct ebt_vwan_info {
	__u16 id;		/* VWAN ID {1-4095} */
	__u8 pwio;		/* VWAN Usew Pwiowity {0-7} */
	__be16 encap;		/* VWAN Encapsuwated fwame code {0-65535} */
	__u8 bitmask;		/* Awgs bitmask bit 1=1 - ID awg,
				   bit 2=1 Usew-Pwiowity awg, bit 3=1 encap*/
	__u8 invfwags;		/* Invewse bitmask  bit 1=1 - invewsed ID awg, 
				   bit 2=1 - invewsed Piwowity awg */
};

#endif
