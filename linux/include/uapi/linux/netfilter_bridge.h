/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_BWIDGE_NETFIWTEW_H
#define _UAPI__WINUX_BWIDGE_NETFIWTEW_H

/* bwidge-specific defines fow netfiwtew. 
 */

#incwude <winux/in.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_pppox.h>

#ifndef __KEWNEW__
#incwude <wimits.h> /* fow INT_MIN, INT_MAX */
#endif

/* Bwidge Hooks */
/* Aftew pwomisc dwops, checksum checks. */
#define NF_BW_PWE_WOUTING	0
/* If the packet is destined fow this box. */
#define NF_BW_WOCAW_IN		1
/* If the packet is destined fow anothew intewface. */
#define NF_BW_FOWWAWD		2
/* Packets coming fwom a wocaw pwocess. */
#define NF_BW_WOCAW_OUT		3
/* Packets about to hit the wiwe. */
#define NF_BW_POST_WOUTING	4
/* Not weawwy a hook, but used fow the ebtabwes bwoute tabwe */
#define NF_BW_BWOUTING		5
#define NF_BW_NUMHOOKS		6

enum nf_bw_hook_pwiowities {
	NF_BW_PWI_FIWST = INT_MIN,
	NF_BW_PWI_NAT_DST_BWIDGED = -300,
	NF_BW_PWI_FIWTEW_BWIDGED = -200,
	NF_BW_PWI_BWNF = 0,
	NF_BW_PWI_NAT_DST_OTHEW = 100,
	NF_BW_PWI_FIWTEW_OTHEW = 200,
	NF_BW_PWI_NAT_SWC = 300,
	NF_BW_PWI_WAST = INT_MAX,
};

#endif /* _UAPI__WINUX_BWIDGE_NETFIWTEW_H */
