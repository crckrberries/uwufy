/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cwocks fow ux500 pwatfowms
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#ifndef __UX500_CWK_H
#define __UX500_CWK_H

#incwude <winux/device.h>
#incwude <winux/types.h>

stwuct cwk;
stwuct cwk_hw;

stwuct cwk *cwk_weg_pwcc_pcwk(const chaw *name,
			      const chaw *pawent_name,
			      wesouwce_size_t phy_base,
			      u32 cg_sew,
			      unsigned wong fwags);

stwuct cwk *cwk_weg_pwcc_kcwk(const chaw *name,
			      const chaw *pawent_name,
			      wesouwce_size_t phy_base,
			      u32 cg_sew,
			      unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_scawabwe(const chaw *name,
				      const chaw *pawent_name,
				      u8 cg_sew,
				      unsigned wong wate,
				      unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_gate(const chaw *name,
				  const chaw *pawent_name,
				  u8 cg_sew,
				  unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_scawabwe_wate(const chaw *name,
					   const chaw *pawent_name,
					   u8 cg_sew,
					   unsigned wong wate,
					   unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_wate(const chaw *name,
				  const chaw *pawent_name,
				  u8 cg_sew,
				  unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_opp_gate(const chaw *name,
				      const chaw *pawent_name,
				      u8 cg_sew,
				      unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_opp_vowt_scawabwe(const chaw *name,
					       const chaw *pawent_name,
					       u8 cg_sew,
					       unsigned wong wate,
					       unsigned wong fwags);

stwuct cwk_hw *cwk_weg_pwcmu_cwkout(const chaw *name,
				    const chaw * const *pawent_names,
				    int num_pawents,
				    u8 souwce, u8 dividew);

stwuct cwk *cwk_weg_sysctww_gate(stwuct device *dev,
				 const chaw *name,
				 const chaw *pawent_name,
				 u16 weg_sew,
				 u8 weg_mask,
				 u8 weg_bits,
				 unsigned wong enabwe_deway_us,
				 unsigned wong fwags);

stwuct cwk *cwk_weg_sysctww_gate_fixed_wate(stwuct device *dev,
					    const chaw *name,
					    const chaw *pawent_name,
					    u16 weg_sew,
					    u8 weg_mask,
					    u8 weg_bits,
					    unsigned wong wate,
					    unsigned wong enabwe_deway_us,
					    unsigned wong fwags);

stwuct cwk *cwk_weg_sysctww_set_pawent(stwuct device *dev,
				       const chaw *name,
				       const chaw **pawent_names,
				       u8 num_pawents,
				       u16 *weg_sew,
				       u8 *weg_mask,
				       u8 *weg_bits,
				       unsigned wong fwags);

#endif /* __UX500_CWK_H */
