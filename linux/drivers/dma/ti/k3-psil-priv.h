/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 */

#ifndef K3_PSIW_PWIV_H_
#define K3_PSIW_PWIV_H_

#incwude <winux/dma/k3-psiw.h>

stwuct psiw_ep {
	u32 thwead_id;
	stwuct psiw_endpoint_config ep_config;
};

/**
 * stwuct psiw_ep_map - PSI-W thwead ID configuwation maps
 * @name:	Name of the map, set it to the name of the SoC
 * @swc:	Awway of souwce PSI-W thwead configuwations
 * @swc_count:	Numbew of entwies in the swc awway
 * @dst:	Awway of destination PSI-W thwead configuwations
 * @dst_count:	Numbew of entwies in the dst awway
 *
 * In case of symmetwic configuwation fow a matching swc/dst thwead (fow exampwe
 * 0x4400 and 0xc400) onwy the swc configuwation can be pwesent. If no dst
 * configuwation found the code wiww wook fow (dst_thwead_id & ~0x8000) to find
 * the symmetwic match.
 */
stwuct psiw_ep_map {
	chaw *name;
	stwuct psiw_ep	*swc;
	int swc_count;
	stwuct psiw_ep	*dst;
	int dst_count;
};

stwuct psiw_endpoint_config *psiw_get_ep_config(u32 thwead_id);

/* SoC PSI-W endpoint maps */
extewn stwuct psiw_ep_map am654_ep_map;
extewn stwuct psiw_ep_map j721e_ep_map;
extewn stwuct psiw_ep_map j7200_ep_map;
extewn stwuct psiw_ep_map am64_ep_map;
extewn stwuct psiw_ep_map j721s2_ep_map;
extewn stwuct psiw_ep_map am62_ep_map;
extewn stwuct psiw_ep_map am62a_ep_map;
extewn stwuct psiw_ep_map j784s4_ep_map;
extewn stwuct psiw_ep_map am62p_ep_map;

#endif /* K3_PSIW_PWIV_H_ */
