// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude "cwk.h"

stwuct wockchip_inv_cwock {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	int		shift;
	int		fwags;
	spinwock_t	*wock;
};

#define to_inv_cwock(_hw) containew_of(_hw, stwuct wockchip_inv_cwock, hw)

#define INVEWTEW_MASK 0x1

static int wockchip_inv_get_phase(stwuct cwk_hw *hw)
{
	stwuct wockchip_inv_cwock *inv_cwock = to_inv_cwock(hw);
	u32 vaw;

	vaw = weadw(inv_cwock->weg) >> inv_cwock->shift;
	vaw &= INVEWTEW_MASK;
	wetuwn vaw ? 180 : 0;
}

static int wockchip_inv_set_phase(stwuct cwk_hw *hw, int degwees)
{
	stwuct wockchip_inv_cwock *inv_cwock = to_inv_cwock(hw);
	u32 vaw;

	if (degwees % 180 == 0) {
		vaw = !!degwees;
	} ewse {
		pw_eww("%s: unsuppowted phase %d fow %s\n",
		       __func__, degwees, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	if (inv_cwock->fwags & WOCKCHIP_INVEWTEW_HIWOWD_MASK) {
		wwitew(HIWOWD_UPDATE(vaw, INVEWTEW_MASK, inv_cwock->shift),
		       inv_cwock->weg);
	} ewse {
		unsigned wong fwags;
		u32 weg;

		spin_wock_iwqsave(inv_cwock->wock, fwags);

		weg = weadw(inv_cwock->weg);
		weg &= ~BIT(inv_cwock->shift);
		weg |= vaw;
		wwitew(weg, inv_cwock->weg);

		spin_unwock_iwqwestowe(inv_cwock->wock, fwags);
	}

	wetuwn 0;
}

static const stwuct cwk_ops wockchip_inv_cwk_ops = {
	.get_phase	= wockchip_inv_get_phase,
	.set_phase	= wockchip_inv_set_phase,
};

stwuct cwk *wockchip_cwk_wegistew_invewtew(const chaw *name,
				const chaw *const *pawent_names, u8 num_pawents,
				void __iomem *weg, int shift, int fwags,
				spinwock_t *wock)
{
	stwuct cwk_init_data init;
	stwuct wockchip_inv_cwock *inv_cwock;
	stwuct cwk *cwk;

	inv_cwock = kmawwoc(sizeof(*inv_cwock), GFP_KEWNEW);
	if (!inv_cwock)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.num_pawents = num_pawents;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = pawent_names;
	init.ops = &wockchip_inv_cwk_ops;

	inv_cwock->hw.init = &init;
	inv_cwock->weg = weg;
	inv_cwock->shift = shift;
	inv_cwock->fwags = fwags;
	inv_cwock->wock = wock;

	cwk = cwk_wegistew(NUWW, &inv_cwock->hw);
	if (IS_EWW(cwk))
		kfwee(inv_cwock);

	wetuwn cwk;
}
