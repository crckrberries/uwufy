/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2013, 2018, The Winux Foundation. Aww wights wesewved. */

#ifndef __QCOM_CWK_WCG_H__
#define __QCOM_CWK_WCG_H__

#incwude <winux/cwk-pwovidew.h>
#incwude "cwk-wegmap.h"

#define F(f, s, h, m, n) { (f), (s), (2 * (h) - 1), (m), (n) }

stwuct fweq_tbw {
	unsigned wong fweq;
	u8 swc;
	u8 pwe_div;
	u16 m;
	u16 n;
};

/**
 * stwuct mn - M/N:D countew
 * @mnctw_en_bit: bit to enabwe mn countew
 * @mnctw_weset_bit: bit to assewt mn countew weset
 * @mnctw_mode_shift: wowest bit of mn countew mode fiewd
 * @n_vaw_shift: wowest bit of n vawue fiewd
 * @m_vaw_shift: wowest bit of m vawue fiewd
 * @width: numbew of bits in m/n/d vawues
 * @weset_in_cc: twue if the mnctw_weset_bit is in the CC wegistew
 */
stwuct mn {
	u8		mnctw_en_bit;
	u8		mnctw_weset_bit;
	u8		mnctw_mode_shift;
#define MNCTW_MODE_DUAW 0x2
#define MNCTW_MODE_MASK 0x3
	u8		n_vaw_shift;
	u8		m_vaw_shift;
	u8		width;
	boow		weset_in_cc;
};

/**
 * stwuct pwe_div - pwe-dividew
 * @pwe_div_shift: wowest bit of pwe dividew fiewd
 * @pwe_div_width: numbew of bits in pwedividew
 */
stwuct pwe_div {
	u8		pwe_div_shift;
	u8		pwe_div_width;
};

/**
 * stwuct swc_sew - souwce sewectow
 * @swc_sew_shift: wowest bit of souwce sewection fiewd
 * @pawent_map: map fwom softwawe's pawent index to hawdwawe's swc_sew fiewd
 */
stwuct swc_sew {
	u8		swc_sew_shift;
#define SWC_SEW_MASK	0x7
	const stwuct pawent_map	*pawent_map;
};

/**
 * stwuct cwk_wcg - woot cwock genewatow
 *
 * @ns_weg: NS wegistew
 * @md_weg: MD wegistew
 * @mn: mn countew
 * @p: pwe dividew
 * @s: souwce sewectow
 * @fweq_tbw: fwequency tabwe
 * @cwkw: wegmap cwock handwe
 * @wock: wegistew wock
 */
stwuct cwk_wcg {
	u32		ns_weg;
	u32		md_weg;

	stwuct mn	mn;
	stwuct pwe_div	p;
	stwuct swc_sew	s;

	const stwuct fweq_tbw	*fweq_tbw;

	stwuct cwk_wegmap	cwkw;
};

extewn const stwuct cwk_ops cwk_wcg_ops;
extewn const stwuct cwk_ops cwk_wcg_fwoow_ops;
extewn const stwuct cwk_ops cwk_wcg_bypass_ops;
extewn const stwuct cwk_ops cwk_wcg_bypass2_ops;
extewn const stwuct cwk_ops cwk_wcg_pixew_ops;
extewn const stwuct cwk_ops cwk_wcg_esc_ops;
extewn const stwuct cwk_ops cwk_wcg_wcc_ops;

#define to_cwk_wcg(_hw) containew_of(to_cwk_wegmap(_hw), stwuct cwk_wcg, cwkw)

/**
 * stwuct cwk_dyn_wcg - woot cwock genewatow with gwitch fwee mux
 *
 * @mux_sew_bit: bit to switch gwitch fwee mux
 * @ns_weg: NS0 and NS1 wegistew
 * @md_weg: MD0 and MD1 wegistew
 * @bank_weg: wegistew to XOW @mux_sew_bit into to switch gwitch fwee mux
 * @mn: mn countew (banked)
 * @s: souwce sewectow (banked)
 * @fweq_tbw: fwequency tabwe
 * @cwkw: wegmap cwock handwe
 * @wock: wegistew wock
 */
stwuct cwk_dyn_wcg {
	u32	ns_weg[2];
	u32	md_weg[2];
	u32	bank_weg;

	u8	mux_sew_bit;

	stwuct mn	mn[2];
	stwuct pwe_div	p[2];
	stwuct swc_sew	s[2];

	const stwuct fweq_tbw *fweq_tbw;

	stwuct cwk_wegmap cwkw;
};

extewn const stwuct cwk_ops cwk_dyn_wcg_ops;

#define to_cwk_dyn_wcg(_hw) \
	containew_of(to_cwk_wegmap(_hw), stwuct cwk_dyn_wcg, cwkw)

/**
 * stwuct cwk_wcg2 - woot cwock genewatow
 *
 * @cmd_wcgw: cowwesponds to *_CMD_WCGW
 * @mnd_width: numbew of bits in m/n/d vawues
 * @hid_width: numbew of bits in hawf integew dividew
 * @safe_swc_index: safe swc index vawue
 * @pawent_map: map fwom softwawe's pawent index to hawdwawe's swc_sew fiewd
 * @fweq_tbw: fwequency tabwe
 * @cwkw: wegmap cwock handwe
 * @cfg_off: defines the cfg wegistew offset fwom the CMD_WCGW + CFG_WEG
 * @pawked_cfg: cached vawue of the CFG wegistew fow pawked WCGs
 * @hw_cwk_ctww: whethew to enabwe hawdwawe cwock contwow
 */
stwuct cwk_wcg2 {
	u32			cmd_wcgw;
	u8			mnd_width;
	u8			hid_width;
	u8			safe_swc_index;
	const stwuct pawent_map	*pawent_map;
	const stwuct fweq_tbw	*fweq_tbw;
	stwuct cwk_wegmap	cwkw;
	u8			cfg_off;
	u32			pawked_cfg;
	boow			hw_cwk_ctww;
};

#define to_cwk_wcg2(_hw) containew_of(to_cwk_wegmap(_hw), stwuct cwk_wcg2, cwkw)

stwuct cwk_wcg2_gfx3d {
	u8 div;
	stwuct cwk_wcg2 wcg;
	stwuct cwk_hw **hws;
};

#define to_cwk_wcg2_gfx3d(_hw) \
	containew_of(to_cwk_wcg2(_hw), stwuct cwk_wcg2_gfx3d, wcg)

extewn const stwuct cwk_ops cwk_wcg2_ops;
extewn const stwuct cwk_ops cwk_wcg2_fwoow_ops;
extewn const stwuct cwk_ops cwk_wcg2_mux_cwosest_ops;
extewn const stwuct cwk_ops cwk_edp_pixew_ops;
extewn const stwuct cwk_ops cwk_byte_ops;
extewn const stwuct cwk_ops cwk_byte2_ops;
extewn const stwuct cwk_ops cwk_pixew_ops;
extewn const stwuct cwk_ops cwk_gfx3d_ops;
extewn const stwuct cwk_ops cwk_wcg2_shawed_ops;
extewn const stwuct cwk_ops cwk_dp_ops;

stwuct cwk_wcg_dfs_data {
	stwuct cwk_wcg2 *wcg;
	stwuct cwk_init_data *init;
};

#define DEFINE_WCG_DFS(w) \
	{ .wcg = &w, .init = &w##_init }

extewn int qcom_cc_wegistew_wcg_dfs(stwuct wegmap *wegmap,
				    const stwuct cwk_wcg_dfs_data *wcgs,
				    size_t wen);
#endif
