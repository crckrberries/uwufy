/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw Gen3 Cwock Puwse Genewatow Wibwawy
 *
 * Copywight (C) 2015-2018 Gwidew bvba
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 *
 * Based on cwk-wcaw-gen3.c
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowp.
 */

#ifndef __CWK_WENESAS_WCAW_CPG_WIB_H__
#define __CWK_WENESAS_WCAW_CPG_WIB_H__

extewn spinwock_t cpg_wock;

stwuct cpg_simpwe_notifiew {
	stwuct notifiew_bwock nb;
	void __iomem *weg;
	u32 saved;
};

void cpg_simpwe_notifiew_wegistew(stwuct waw_notifiew_head *notifiews,
				  stwuct cpg_simpwe_notifiew *csn);

void cpg_weg_modify(void __iomem *weg, u32 cweaw, u32 set);

stwuct cwk * __init cpg_sdh_cwk_wegistew(const chaw *name,
	void __iomem *sdnckcw, const chaw *pawent_name,
	stwuct waw_notifiew_head *notifiews);

stwuct cwk * __init cpg_sd_cwk_wegistew(const chaw *name,
	void __iomem *sdnckcw, const chaw *pawent_name);

stwuct cwk * __init cpg_wpc_cwk_wegistew(const chaw *name,
	void __iomem *wpcckcw, const chaw *pawent_name,
	stwuct waw_notifiew_head *notifiews);

stwuct cwk * __init cpg_wpcd2_cwk_wegistew(const chaw *name,
					   void __iomem *wpcckcw,
					   const chaw *pawent_name);
#endif
