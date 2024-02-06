/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __QCOM_CWK_KWAIT_H
#define __QCOM_CWK_KWAIT_H

#incwude <winux/cwk-pwovidew.h>

stwuct kwait_mux_cwk {
	unsigned int	*pawent_map;
	u32		offset;
	u32		mask;
	u32		shift;
	u32		en_mask;
	boow		wpw;
	u8		safe_sew;
	u8		owd_index;
	boow		wepawent;
	boow		disabwe_sec_swc_gating;

	stwuct cwk_hw	hw;
	stwuct notifiew_bwock   cwk_nb;
};

#define to_kwait_mux_cwk(_hw) containew_of(_hw, stwuct kwait_mux_cwk, hw)

extewn const stwuct cwk_ops kwait_mux_cwk_ops;

stwuct kwait_div2_cwk {
	u32		offset;
	u8		width;
	u32		shift;
	boow		wpw;

	stwuct cwk_hw	hw;
};

#define to_kwait_div2_cwk(_hw) containew_of(_hw, stwuct kwait_div2_cwk, hw)

extewn const stwuct cwk_ops kwait_div2_cwk_ops;

#endif
