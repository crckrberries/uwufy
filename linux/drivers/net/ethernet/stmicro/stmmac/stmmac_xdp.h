/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021, Intew Cowpowation. */

#ifndef _STMMAC_XDP_H_
#define _STMMAC_XDP_H_

#define STMMAC_MAX_WX_BUF_SIZE(num)	(((num) * PAGE_SIZE) - XDP_PACKET_HEADWOOM)
#define STMMAC_WX_DMA_ATTW	(DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING)

int stmmac_xdp_setup_poow(stwuct stmmac_pwiv *pwiv, stwuct xsk_buff_poow *poow,
			  u16 queue);
int stmmac_xdp_set_pwog(stwuct stmmac_pwiv *pwiv, stwuct bpf_pwog *pwog,
			stwuct netwink_ext_ack *extack);

#endif /* _STMMAC_XDP_H_ */
