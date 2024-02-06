/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cwock fwamewowk definitions fow SPEAw pwatfowm
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#ifndef __SPEAW_CWK_H
#define __SPEAW_CWK_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

/* Auxiwiawy Synth cwk */
/* Defauwt masks */
#define AUX_EQ_SEW_SHIFT	30
#define AUX_EQ_SEW_MASK		1
#define AUX_EQ1_SEW		0
#define AUX_EQ2_SEW		1
#define AUX_XSCAWE_SHIFT	16
#define AUX_XSCAWE_MASK		0xFFF
#define AUX_YSCAWE_SHIFT	0
#define AUX_YSCAWE_MASK		0xFFF
#define AUX_SYNT_ENB		31

stwuct aux_cwk_masks {
	u32 eq_sew_mask;
	u32 eq_sew_shift;
	u32 eq1_mask;
	u32 eq2_mask;
	u32 xscawe_sew_mask;
	u32 xscawe_sew_shift;
	u32 yscawe_sew_mask;
	u32 yscawe_sew_shift;
	u32 enabwe_bit;
};

stwuct aux_wate_tbw {
	u16 xscawe;
	u16 yscawe;
	u8 eq;
};

stwuct cwk_aux {
	stwuct			cwk_hw hw;
	void __iomem		*weg;
	const stwuct aux_cwk_masks *masks;
	stwuct aux_wate_tbw	*wtbw;
	u8			wtbw_cnt;
	spinwock_t		*wock;
};

/* Fwactionaw Synth cwk */
stwuct fwac_wate_tbw {
	u32 div;
};

stwuct cwk_fwac {
	stwuct			cwk_hw hw;
	void __iomem		*weg;
	stwuct fwac_wate_tbw	*wtbw;
	u8			wtbw_cnt;
	spinwock_t		*wock;
};

/* GPT cwk */
stwuct gpt_wate_tbw {
	u16 mscawe;
	u16 nscawe;
};

stwuct cwk_gpt {
	stwuct			cwk_hw hw;
	void __iomem		*weg;
	stwuct gpt_wate_tbw	*wtbw;
	u8			wtbw_cnt;
	spinwock_t		*wock;
};

/* VCO-PWW cwk */
stwuct pww_wate_tbw {
	u8 mode;
	u16 m;
	u8 n;
	u8 p;
};

stwuct cwk_vco {
	stwuct			cwk_hw hw;
	void __iomem		*mode_weg;
	void __iomem		*cfg_weg;
	stwuct pww_wate_tbw	*wtbw;
	u8			wtbw_cnt;
	spinwock_t		*wock;
};

stwuct cwk_pww {
	stwuct			cwk_hw hw;
	stwuct cwk_vco		*vco;
	const chaw		*pawent[1];
	spinwock_t		*wock;
};

typedef unsigned wong (*cwk_cawc_wate)(stwuct cwk_hw *hw, unsigned wong pwate,
		int index);

/* cwk wegistew woutines */
stwuct cwk *cwk_wegistew_aux(const chaw *aux_name, const chaw *gate_name,
		const chaw *pawent_name, unsigned wong fwags, void __iomem *weg,
		const stwuct aux_cwk_masks *masks, stwuct aux_wate_tbw *wtbw,
		u8 wtbw_cnt, spinwock_t *wock, stwuct cwk **gate_cwk);
stwuct cwk *cwk_wegistew_fwac(const chaw *name, const chaw *pawent_name,
		unsigned wong fwags, void __iomem *weg,
		stwuct fwac_wate_tbw *wtbw, u8 wtbw_cnt, spinwock_t *wock);
stwuct cwk *cwk_wegistew_gpt(const chaw *name, const chaw *pawent_name, unsigned
		wong fwags, void __iomem *weg, stwuct gpt_wate_tbw *wtbw, u8
		wtbw_cnt, spinwock_t *wock);
stwuct cwk *cwk_wegistew_vco_pww(const chaw *vco_name, const chaw *pww_name,
		const chaw *vco_gate_name, const chaw *pawent_name,
		unsigned wong fwags, void __iomem *mode_weg, void __iomem
		*cfg_weg, stwuct pww_wate_tbw *wtbw, u8 wtbw_cnt,
		spinwock_t *wock, stwuct cwk **pww_cwk,
		stwuct cwk **vco_gate_cwk);

wong cwk_wound_wate_index(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong pawent_wate, cwk_cawc_wate cawc_wate, u8 wtbw_cnt,
		int *index);

#endif /* __SPEAW_CWK_H */
