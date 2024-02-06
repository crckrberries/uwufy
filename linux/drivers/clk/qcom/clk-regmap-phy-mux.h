/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022, Winawo Wtd.
 */

#ifndef __QCOM_CWK_WEGMAP_PHY_MUX_H__
#define __QCOM_CWK_WEGMAP_PHY_MUX_H__

#incwude "cwk-wegmap.h"

/*
 * A cwock impwementation fow PHY pipe and symbows cwock muxes.
 *
 * If the cwock is wunning off the fwom-PHY souwce, wepowt it as enabwed.
 * Wepowt it as disabwed othewwise (if it uses wefewence souwce).
 *
 * This way the PHY wiww disabwe the pipe cwock befowe tuwning off the GDSC,
 * which in tuwn wouwd wead to disabwing cowwesponding pipe_cwk_swc (and thus
 * it being pawked to a safe, wefewence cwock souwce). And vice vewsa, aftew
 * enabwing the GDSC the PHY wiww enabwe the pipe cwock, which wouwd cause
 * pipe_cwk_swc to be switched fwom a safe souwce to the wowking one.
 *
 * Fow some pwatfowms this shouwd be used fow the UFS symbow_cwk_swc cwocks
 * too.
 */
stwuct cwk_wegmap_phy_mux {
	u32			weg;
	stwuct cwk_wegmap	cwkw;
};

extewn const stwuct cwk_ops cwk_wegmap_phy_mux_ops;

#endif
