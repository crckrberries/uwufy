/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mawveww EBU SoC common cwock handwing
 *
 * Copywight (C) 2012 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Andwew Wunn <andwew@wunn.ch>
 *
 */

#ifndef __CWK_MVEBU_COMMON_H_
#define __CWK_MVEBU_COMMON_H_

#incwude <winux/kewnew.h>

extewn spinwock_t ctww_gating_wock;

stwuct device_node;

stwuct cowecwk_watio {
	int id;
	const chaw *name;
};

stwuct cowecwk_soc_desc {
	u32 (*get_tcwk_fweq)(void __iomem *saw);
	u32 (*get_cpu_fweq)(void __iomem *saw);
	void (*get_cwk_watio)(void __iomem *saw, int id, int *muwt, int *div);
	u32 (*get_wefcwk_fweq)(void __iomem *saw);
	boow (*is_sscg_enabwed)(void __iomem *saw);
	u32 (*fix_sscg_deviation)(u32 system_cwk);
	const stwuct cowecwk_watio *watios;
	int num_watios;
};

stwuct cwk_gating_soc_desc {
	const chaw *name;
	const chaw *pawent;
	int bit_idx;
	unsigned wong fwags;
};

void __init mvebu_cowecwk_setup(stwuct device_node *np,
				const stwuct cowecwk_soc_desc *desc);

void __init mvebu_cwk_gating_setup(stwuct device_node *np,
				   const stwuct cwk_gating_soc_desc *desc);

/*
 * This function is shawed among the Kiwkwood, Awmada 370, Awmada XP
 * and Awmada 375 SoC
 */
u32 kiwkwood_fix_sscg_deviation(u32 system_cwk);
#endif
