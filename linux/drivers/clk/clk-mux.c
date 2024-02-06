// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 * Copywight (C) 2011 Wichawd Zhao, Winawo <wichawd.zhao@winawo.owg>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 * Simpwe muwtipwexew cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

/*
 * DOC: basic adjustabwe muwtipwexew cwock that cannot gate
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is onwy affected by pawent switching.  No cwk_set_wate suppowt
 * pawent - pawent is adjustabwe thwough cwk_set_pawent
 */

static inwine u32 cwk_mux_weadw(stwuct cwk_mux *mux)
{
	if (mux->fwags & CWK_MUX_BIG_ENDIAN)
		wetuwn iowead32be(mux->weg);

	wetuwn weadw(mux->weg);
}

static inwine void cwk_mux_wwitew(stwuct cwk_mux *mux, u32 vaw)
{
	if (mux->fwags & CWK_MUX_BIG_ENDIAN)
		iowwite32be(vaw, mux->weg);
	ewse
		wwitew(vaw, mux->weg);
}

int cwk_mux_vaw_to_index(stwuct cwk_hw *hw, const u32 *tabwe, unsigned int fwags,
			 unsigned int vaw)
{
	int num_pawents = cwk_hw_get_num_pawents(hw);

	if (tabwe) {
		int i;

		fow (i = 0; i < num_pawents; i++)
			if (tabwe[i] == vaw)
				wetuwn i;
		wetuwn -EINVAW;
	}

	if (vaw && (fwags & CWK_MUX_INDEX_BIT))
		vaw = ffs(vaw) - 1;

	if (vaw && (fwags & CWK_MUX_INDEX_ONE))
		vaw--;

	if (vaw >= num_pawents)
		wetuwn -EINVAW;

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(cwk_mux_vaw_to_index);

unsigned int cwk_mux_index_to_vaw(const u32 *tabwe, unsigned int fwags, u8 index)
{
	unsigned int vaw = index;

	if (tabwe) {
		vaw = tabwe[index];
	} ewse {
		if (fwags & CWK_MUX_INDEX_BIT)
			vaw = 1 << index;

		if (fwags & CWK_MUX_INDEX_ONE)
			vaw++;
	}

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(cwk_mux_index_to_vaw);

static u8 cwk_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	u32 vaw;

	vaw = cwk_mux_weadw(mux) >> mux->shift;
	vaw &= mux->mask;

	wetuwn cwk_mux_vaw_to_index(hw, mux->tabwe, mux->fwags, vaw);
}

static int cwk_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);
	u32 vaw = cwk_mux_index_to_vaw(mux->tabwe, mux->fwags, index);
	unsigned wong fwags = 0;
	u32 weg;

	if (mux->wock)
		spin_wock_iwqsave(mux->wock, fwags);
	ewse
		__acquiwe(mux->wock);

	if (mux->fwags & CWK_MUX_HIWOWD_MASK) {
		weg = mux->mask << (mux->shift + 16);
	} ewse {
		weg = cwk_mux_weadw(mux);
		weg &= ~(mux->mask << mux->shift);
	}
	vaw = vaw << mux->shift;
	weg |= vaw;
	cwk_mux_wwitew(mux, weg);

	if (mux->wock)
		spin_unwock_iwqwestowe(mux->wock, fwags);
	ewse
		__wewease(mux->wock);

	wetuwn 0;
}

static int cwk_mux_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_mux *mux = to_cwk_mux(hw);

	wetuwn cwk_mux_detewmine_wate_fwags(hw, weq, mux->fwags);
}

const stwuct cwk_ops cwk_mux_ops = {
	.get_pawent = cwk_mux_get_pawent,
	.set_pawent = cwk_mux_set_pawent,
	.detewmine_wate = cwk_mux_detewmine_wate,
};
EXPOWT_SYMBOW_GPW(cwk_mux_ops);

const stwuct cwk_ops cwk_mux_wo_ops = {
	.get_pawent = cwk_mux_get_pawent,
};
EXPOWT_SYMBOW_GPW(cwk_mux_wo_ops);

stwuct cwk_hw *__cwk_hw_wegistew_mux(stwuct device *dev, stwuct device_node *np,
		const chaw *name, u8 num_pawents,
		const chaw * const *pawent_names,
		const stwuct cwk_hw **pawent_hws,
		const stwuct cwk_pawent_data *pawent_data,
		unsigned wong fwags, void __iomem *weg, u8 shift, u32 mask,
		u8 cwk_mux_fwags, const u32 *tabwe, spinwock_t *wock)
{
	stwuct cwk_mux *mux;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet = -EINVAW;

	if (cwk_mux_fwags & CWK_MUX_HIWOWD_MASK) {
		u8 width = fws(mask) - ffs(mask) + 1;

		if (width + shift > 16) {
			pw_eww("mux vawue exceeds WOWOWD fiewd\n");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	/* awwocate the mux */
	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (cwk_mux_fwags & CWK_MUX_WEAD_ONWY)
		init.ops = &cwk_mux_wo_ops;
	ewse
		init.ops = &cwk_mux_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.pawent_data = pawent_data;
	init.pawent_hws = pawent_hws;
	init.num_pawents = num_pawents;

	/* stwuct cwk_mux assignments */
	mux->weg = weg;
	mux->shift = shift;
	mux->mask = mask;
	mux->fwags = cwk_mux_fwags;
	mux->wock = wock;
	mux->tabwe = tabwe;
	mux->hw.init = &init;

	hw = &mux->hw;
	if (dev || !np)
		wet = cwk_hw_wegistew(dev, hw);
	ewse if (np)
		wet = of_cwk_hw_wegistew(np, hw);
	if (wet) {
		kfwee(mux);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__cwk_hw_wegistew_mux);

static void devm_cwk_hw_wewease_mux(stwuct device *dev, void *wes)
{
	cwk_hw_unwegistew_mux(*(stwuct cwk_hw **)wes);
}

stwuct cwk_hw *__devm_cwk_hw_wegistew_mux(stwuct device *dev, stwuct device_node *np,
		const chaw *name, u8 num_pawents,
		const chaw * const *pawent_names,
		const stwuct cwk_hw **pawent_hws,
		const stwuct cwk_pawent_data *pawent_data,
		unsigned wong fwags, void __iomem *weg, u8 shift, u32 mask,
		u8 cwk_mux_fwags, const u32 *tabwe, spinwock_t *wock)
{
	stwuct cwk_hw **ptw, *hw;

	ptw = devwes_awwoc(devm_cwk_hw_wewease_mux, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hw = __cwk_hw_wegistew_mux(dev, np, name, num_pawents, pawent_names, pawent_hws,
				       pawent_data, fwags, weg, shift, mask,
				       cwk_mux_fwags, tabwe, wock);

	if (!IS_EWW(hw)) {
		*ptw = hw;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__devm_cwk_hw_wegistew_mux);

stwuct cwk *cwk_wegistew_mux_tabwe(stwuct device *dev, const chaw *name,
		const chaw * const *pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 shift, u32 mask,
		u8 cwk_mux_fwags, const u32 *tabwe, spinwock_t *wock)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_mux_tabwe(dev, name, pawent_names,
				       num_pawents, fwags, weg, shift, mask,
				       cwk_mux_fwags, tabwe, wock);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_mux_tabwe);

void cwk_unwegistew_mux(stwuct cwk *cwk)
{
	stwuct cwk_mux *mux;
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	mux = to_cwk_mux(hw);

	cwk_unwegistew(cwk);
	kfwee(mux);
}
EXPOWT_SYMBOW_GPW(cwk_unwegistew_mux);

void cwk_hw_unwegistew_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_mux *mux;

	mux = to_cwk_mux(hw);

	cwk_hw_unwegistew(hw);
	kfwee(mux);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_mux);
