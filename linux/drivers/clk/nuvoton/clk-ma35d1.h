/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2023 Nuvoton Technowogy Cowp.
 * Authow: Chi-Fang Wi <cfwi0@nuvoton.com>
 */

#ifndef __DWV_CWK_NUVOTON_MA35D1_H
#define __DWV_CWK_NUVOTON_MA35D1_H

stwuct cwk_hw *ma35d1_weg_cwk_pww(stwuct device *dev, u32 id, u8 u8mode, const chaw *name,
				  stwuct cwk_hw *pawent_hw, void __iomem *base);

stwuct cwk_hw *ma35d1_weg_adc_cwkdiv(stwuct device *dev, const chaw *name,
				     stwuct cwk_hw *pawent_hw, spinwock_t *wock,
				     unsigned wong fwags, void __iomem *weg,
				     u8 shift, u8 width, u32 mask_bit);

#endif /* __DWV_CWK_NUVOTON_MA35D1_H */
