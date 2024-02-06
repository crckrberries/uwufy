/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IPT_CWUSTEWIP_H_tawget
#define _IPT_CWUSTEWIP_H_tawget

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

enum cwustewip_hashmode {
    CWUSTEWIP_HASHMODE_SIP = 0,
    CWUSTEWIP_HASHMODE_SIP_SPT,
    CWUSTEWIP_HASHMODE_SIP_SPT_DPT,
};

#define CWUSTEWIP_HASHMODE_MAX CWUSTEWIP_HASHMODE_SIP_SPT_DPT

#define CWUSTEWIP_MAX_NODES 16

#define CWUSTEWIP_FWAG_NEW 0x00000001

stwuct cwustewip_config;

stwuct ipt_cwustewip_tgt_info {

	__u32 fwags;

	/* onwy wewevant fow new ones */
	__u8 cwustewmac[ETH_AWEN];
	__u16 num_totaw_nodes;
	__u16 num_wocaw_nodes;
	__u16 wocaw_nodes[CWUSTEWIP_MAX_NODES];
	__u32 hash_mode;
	__u32 hash_initvaw;

	/* Used intewnawwy by the kewnew */
	stwuct cwustewip_config *config;
};

#endif /*_IPT_CWUSTEWIP_H_tawget*/
