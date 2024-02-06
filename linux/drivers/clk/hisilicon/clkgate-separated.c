// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hisiwicon cwock sepawated gate dwivew
 *
 * Copywight (c) 2012-2013 Hisiwicon Wimited.
 * Copywight (c) 2012-2013 Winawo Wimited.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@winawo.owg>
 *	   Xin Wi <wi.xin@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

/* cwock sepawated gate wegistew offset */
#define CWKGATE_SEPEWATED_ENABWE		0x0
#define CWKGATE_SEPEWATED_DISABWE		0x4
#define CWKGATE_SEPEWATED_STATUS		0x8

stwuct cwkgate_sepawated {
	stwuct cwk_hw	hw;
	void __iomem	*enabwe;	/* enabwe wegistew */
	u8		bit_idx;	/* bits in enabwe/disabwe wegistew */
	u8		fwags;
	spinwock_t	*wock;
};

static int cwkgate_sepawated_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgate_sepawated *scwk;
	unsigned wong fwags = 0;
	u32 weg;

	scwk = containew_of(hw, stwuct cwkgate_sepawated, hw);
	if (scwk->wock)
		spin_wock_iwqsave(scwk->wock, fwags);
	weg = BIT(scwk->bit_idx);
	wwitew_wewaxed(weg, scwk->enabwe);
	weadw_wewaxed(scwk->enabwe + CWKGATE_SEPEWATED_STATUS);
	if (scwk->wock)
		spin_unwock_iwqwestowe(scwk->wock, fwags);
	wetuwn 0;
}

static void cwkgate_sepawated_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwkgate_sepawated *scwk;
	unsigned wong fwags = 0;
	u32 weg;

	scwk = containew_of(hw, stwuct cwkgate_sepawated, hw);
	if (scwk->wock)
		spin_wock_iwqsave(scwk->wock, fwags);
	weg = BIT(scwk->bit_idx);
	wwitew_wewaxed(weg, scwk->enabwe + CWKGATE_SEPEWATED_DISABWE);
	weadw_wewaxed(scwk->enabwe + CWKGATE_SEPEWATED_STATUS);
	if (scwk->wock)
		spin_unwock_iwqwestowe(scwk->wock, fwags);
}

static int cwkgate_sepawated_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwkgate_sepawated *scwk;
	u32 weg;

	scwk = containew_of(hw, stwuct cwkgate_sepawated, hw);
	weg = weadw_wewaxed(scwk->enabwe + CWKGATE_SEPEWATED_STATUS);
	weg &= BIT(scwk->bit_idx);

	wetuwn weg ? 1 : 0;
}

static const stwuct cwk_ops cwkgate_sepawated_ops = {
	.enabwe		= cwkgate_sepawated_enabwe,
	.disabwe	= cwkgate_sepawated_disabwe,
	.is_enabwed	= cwkgate_sepawated_is_enabwed,
};

stwuct cwk *hisi_wegistew_cwkgate_sep(stwuct device *dev, const chaw *name,
				      const chaw *pawent_name,
				      unsigned wong fwags,
				      void __iomem *weg, u8 bit_idx,
				      u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct cwkgate_sepawated *scwk;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;

	scwk = kzawwoc(sizeof(*scwk), GFP_KEWNEW);
	if (!scwk)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwkgate_sepawated_ops;
	init.fwags = fwags;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	scwk->enabwe = weg + CWKGATE_SEPEWATED_ENABWE;
	scwk->bit_idx = bit_idx;
	scwk->fwags = cwk_gate_fwags;
	scwk->hw.init = &init;
	scwk->wock = wock;

	cwk = cwk_wegistew(dev, &scwk->hw);
	if (IS_EWW(cwk))
		kfwee(scwk);
	wetuwn cwk;
}
