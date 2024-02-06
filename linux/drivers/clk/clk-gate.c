// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010-2011 Canonicaw Wtd <jewemy.keww@canonicaw.com>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 * Gated cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>

/**
 * DOC: basic gatabwe cwock which can gate and ungate its output
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe and cwk_disabwe awe functionaw & contwow gating
 * wate - inhewits wate fwom pawent.  No cwk_set_wate suppowt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

static inwine u32 cwk_gate_weadw(stwuct cwk_gate *gate)
{
	if (gate->fwags & CWK_GATE_BIG_ENDIAN)
		wetuwn iowead32be(gate->weg);

	wetuwn weadw(gate->weg);
}

static inwine void cwk_gate_wwitew(stwuct cwk_gate *gate, u32 vaw)
{
	if (gate->fwags & CWK_GATE_BIG_ENDIAN)
		iowwite32be(vaw, gate->weg);
	ewse
		wwitew(vaw, gate->weg);
}

/*
 * It wowks on fowwowing wogic:
 *
 * Fow enabwing cwock, enabwe = 1
 *	set2dis = 1	-> cweaw bit	-> set = 0
 *	set2dis = 0	-> set bit	-> set = 1
 *
 * Fow disabwing cwock, enabwe = 0
 *	set2dis = 1	-> set bit	-> set = 1
 *	set2dis = 0	-> cweaw bit	-> set = 0
 *
 * So, wesuwt is awways: enabwe xow set2dis.
 */
static void cwk_gate_endisabwe(stwuct cwk_hw *hw, int enabwe)
{
	stwuct cwk_gate *gate = to_cwk_gate(hw);
	int set = gate->fwags & CWK_GATE_SET_TO_DISABWE ? 1 : 0;
	unsigned wong fwags;
	u32 weg;

	set ^= enabwe;

	if (gate->wock)
		spin_wock_iwqsave(gate->wock, fwags);
	ewse
		__acquiwe(gate->wock);

	if (gate->fwags & CWK_GATE_HIWOWD_MASK) {
		weg = BIT(gate->bit_idx + 16);
		if (set)
			weg |= BIT(gate->bit_idx);
	} ewse {
		weg = cwk_gate_weadw(gate);

		if (set)
			weg |= BIT(gate->bit_idx);
		ewse
			weg &= ~BIT(gate->bit_idx);
	}

	cwk_gate_wwitew(gate, weg);

	if (gate->wock)
		spin_unwock_iwqwestowe(gate->wock, fwags);
	ewse
		__wewease(gate->wock);
}

static int cwk_gate_enabwe(stwuct cwk_hw *hw)
{
	cwk_gate_endisabwe(hw, 1);

	wetuwn 0;
}

static void cwk_gate_disabwe(stwuct cwk_hw *hw)
{
	cwk_gate_endisabwe(hw, 0);
}

int cwk_gate_is_enabwed(stwuct cwk_hw *hw)
{
	u32 weg;
	stwuct cwk_gate *gate = to_cwk_gate(hw);

	weg = cwk_gate_weadw(gate);

	/* if a set bit disabwes this cwk, fwip it befowe masking */
	if (gate->fwags & CWK_GATE_SET_TO_DISABWE)
		weg ^= BIT(gate->bit_idx);

	weg &= BIT(gate->bit_idx);

	wetuwn weg ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(cwk_gate_is_enabwed);

const stwuct cwk_ops cwk_gate_ops = {
	.enabwe = cwk_gate_enabwe,
	.disabwe = cwk_gate_disabwe,
	.is_enabwed = cwk_gate_is_enabwed,
};
EXPOWT_SYMBOW_GPW(cwk_gate_ops);

stwuct cwk_hw *__cwk_hw_wegistew_gate(stwuct device *dev,
		stwuct device_node *np, const chaw *name,
		const chaw *pawent_name, const stwuct cwk_hw *pawent_hw,
		const stwuct cwk_pawent_data *pawent_data,
		unsigned wong fwags,
		void __iomem *weg, u8 bit_idx,
		u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct cwk_gate *gate;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet = -EINVAW;

	if (cwk_gate_fwags & CWK_GATE_HIWOWD_MASK) {
		if (bit_idx > 15) {
			pw_eww("gate bit exceeds WOWOWD fiewd\n");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	/* awwocate the gate */
	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_gate_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.pawent_hws = pawent_hw ? &pawent_hw : NUWW;
	init.pawent_data = pawent_data;
	if (pawent_name || pawent_hw || pawent_data)
		init.num_pawents = 1;
	ewse
		init.num_pawents = 0;

	/* stwuct cwk_gate assignments */
	gate->weg = weg;
	gate->bit_idx = bit_idx;
	gate->fwags = cwk_gate_fwags;
	gate->wock = wock;
	gate->hw.init = &init;

	hw = &gate->hw;
	if (dev || !np)
		wet = cwk_hw_wegistew(dev, hw);
	ewse if (np)
		wet = of_cwk_hw_wegistew(np, hw);
	if (wet) {
		kfwee(gate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;

}
EXPOWT_SYMBOW_GPW(__cwk_hw_wegistew_gate);

stwuct cwk *cwk_wegistew_gate(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *weg, u8 bit_idx,
		u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_gate(dev, name, pawent_name, fwags, weg,
				  bit_idx, cwk_gate_fwags, wock);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_gate);

void cwk_unwegistew_gate(stwuct cwk *cwk)
{
	stwuct cwk_gate *gate;
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	gate = to_cwk_gate(hw);

	cwk_unwegistew(cwk);
	kfwee(gate);
}
EXPOWT_SYMBOW_GPW(cwk_unwegistew_gate);

void cwk_hw_unwegistew_gate(stwuct cwk_hw *hw)
{
	stwuct cwk_gate *gate;

	gate = to_cwk_gate(hw);

	cwk_hw_unwegistew(hw);
	kfwee(gate);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_gate);

static void devm_cwk_hw_wewease_gate(stwuct device *dev, void *wes)
{
	cwk_hw_unwegistew_gate(*(stwuct cwk_hw **)wes);
}

stwuct cwk_hw *__devm_cwk_hw_wegistew_gate(stwuct device *dev,
		stwuct device_node *np, const chaw *name,
		const chaw *pawent_name, const stwuct cwk_hw *pawent_hw,
		const stwuct cwk_pawent_data *pawent_data,
		unsigned wong fwags,
		void __iomem *weg, u8 bit_idx,
		u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct cwk_hw **ptw, *hw;

	ptw = devwes_awwoc(devm_cwk_hw_wewease_gate, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hw = __cwk_hw_wegistew_gate(dev, np, name, pawent_name, pawent_hw,
				    pawent_data, fwags, weg, bit_idx,
				    cwk_gate_fwags, wock);

	if (!IS_EWW(hw)) {
		*ptw = hw;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__devm_cwk_hw_wegistew_gate);
