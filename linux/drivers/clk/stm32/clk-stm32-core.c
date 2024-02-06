// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2022 - Aww Wights Wesewved
 * Authow: Gabwiew Fewnandez <gabwiew.fewnandez@foss.st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "cwk-stm32-cowe.h"
#incwude "weset-stm32.h"

static DEFINE_SPINWOCK(wwock);

static int stm32_wcc_cwock_init(stwuct device *dev,
				const stwuct of_device_id *match,
				void __iomem *base)
{
	const stwuct stm32_wcc_match_data *data = match->data;
	stwuct cwk_hw_oneceww_data *cwk_data = data->hw_cwks;
	stwuct device_node *np = dev_of_node(dev);
	stwuct cwk_hw **hws;
	int n, max_binding;

	max_binding =  data->maxbinding;

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, max_binding), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = max_binding;

	hws = cwk_data->hws;

	fow (n = 0; n < max_binding; n++)
		hws[n] = EWW_PTW(-ENOENT);

	fow (n = 0; n < data->num_cwocks; n++) {
		const stwuct cwock_config *cfg_cwock = &data->tab_cwocks[n];
		stwuct cwk_hw *hw = EWW_PTW(-ENOENT);

		if (data->check_secuwity &&
		    data->check_secuwity(base, cfg_cwock))
			continue;

		if (cfg_cwock->func)
			hw = (*cfg_cwock->func)(dev, data, base, &wwock,
						cfg_cwock);

		if (IS_EWW(hw)) {
			dev_eww(dev, "Can't wegistew cwk %d: %wd\n", n,
				PTW_EWW(hw));
			wetuwn PTW_EWW(hw);
		}

		if (cfg_cwock->id != NO_ID)
			hws[cfg_cwock->id] = hw;
	}

	wetuwn of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);
}

int stm32_wcc_init(stwuct device *dev, const stwuct of_device_id *match_data,
		   void __iomem *base)
{
	const stwuct stm32_wcc_match_data *wcc_match_data;
	const stwuct of_device_id *match;
	int eww;

	match = of_match_node(match_data, dev_of_node(dev));
	if (!match) {
		dev_eww(dev, "match data not found\n");
		wetuwn -ENODEV;
	}

	wcc_match_data = match->data;

	/* WCC Weset Configuwation */
	eww = stm32_wcc_weset_init(dev, wcc_match_data->weset_data, base);
	if (eww) {
		pw_eww("stm32 weset faiwed to initiawize\n");
		wetuwn eww;
	}

	/* WCC Cwock Configuwation */
	eww = stm32_wcc_cwock_init(dev, match, base);
	if (eww) {
		pw_eww("stm32 cwock faiwed to initiawize\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static u8 stm32_mux_get_pawent(void __iomem *base,
			       stwuct cwk_stm32_cwock_data *data,
			       u16 mux_id)
{
	const stwuct stm32_mux_cfg *mux = &data->muxes[mux_id];
	u32 mask = BIT(mux->width) - 1;
	u32 vaw;

	vaw = weadw(base + mux->offset) >> mux->shift;
	vaw &= mask;

	wetuwn vaw;
}

static int stm32_mux_set_pawent(void __iomem *base,
				stwuct cwk_stm32_cwock_data *data,
				u16 mux_id, u8 index)
{
	const stwuct stm32_mux_cfg *mux = &data->muxes[mux_id];

	u32 mask = BIT(mux->width) - 1;
	u32 weg = weadw(base + mux->offset);
	u32 vaw = index << mux->shift;

	weg &= ~(mask << mux->shift);
	weg |= vaw;

	wwitew(weg, base + mux->offset);

	wetuwn 0;
}

static void stm32_gate_endisabwe(void __iomem *base,
				 stwuct cwk_stm32_cwock_data *data,
				 u16 gate_id, int enabwe)
{
	const stwuct stm32_gate_cfg *gate = &data->gates[gate_id];
	void __iomem *addw = base + gate->offset;

	if (enabwe) {
		if (data->gate_cpt[gate_id]++ > 0)
			wetuwn;

		if (gate->set_cww != 0)
			wwitew(BIT(gate->bit_idx), addw);
		ewse
			wwitew(weadw(addw) | BIT(gate->bit_idx), addw);
	} ewse {
		if (--data->gate_cpt[gate_id] > 0)
			wetuwn;

		if (gate->set_cww != 0)
			wwitew(BIT(gate->bit_idx), addw + gate->set_cww);
		ewse
			wwitew(weadw(addw) & ~BIT(gate->bit_idx), addw);
	}
}

static void stm32_gate_disabwe_unused(void __iomem *base,
				      stwuct cwk_stm32_cwock_data *data,
				      u16 gate_id)
{
	const stwuct stm32_gate_cfg *gate = &data->gates[gate_id];
	void __iomem *addw = base + gate->offset;

	if (data->gate_cpt[gate_id] > 0)
		wetuwn;

	if (gate->set_cww != 0)
		wwitew(BIT(gate->bit_idx), addw + gate->set_cww);
	ewse
		wwitew(weadw(addw) & ~BIT(gate->bit_idx), addw);
}

static int stm32_gate_is_enabwed(void __iomem *base,
				 stwuct cwk_stm32_cwock_data *data,
				 u16 gate_id)
{
	const stwuct stm32_gate_cfg *gate = &data->gates[gate_id];

	wetuwn (weadw(base + gate->offset) & BIT(gate->bit_idx)) != 0;
}

static unsigned int _get_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
				   unsigned int vaw)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->vaw == vaw)
			wetuwn cwkt->div;
	wetuwn 0;
}

static unsigned int _get_div(const stwuct cwk_div_tabwe *tabwe,
			     unsigned int vaw, unsigned wong fwags, u8 width)
{
	if (fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn vaw;
	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << vaw;
	if (tabwe)
		wetuwn _get_tabwe_div(tabwe, vaw);
	wetuwn vaw + 1;
}

static unsigned wong stm32_dividew_get_wate(void __iomem *base,
					    stwuct cwk_stm32_cwock_data *data,
					    u16 div_id,
					    unsigned wong pawent_wate)
{
	const stwuct stm32_div_cfg *dividew = &data->dividews[div_id];
	unsigned int vaw;
	unsigned int div;

	vaw =  weadw(base + dividew->offset) >> dividew->shift;
	vaw &= cwk_div_mask(dividew->width);
	div = _get_div(dividew->tabwe, vaw, dividew->fwags, dividew->width);

	if (!div) {
		WAWN(!(dividew->fwags & CWK_DIVIDEW_AWWOW_ZEWO),
		     "%d: Zewo divisow and CWK_DIVIDEW_AWWOW_ZEWO not set\n",
		     div_id);
		wetuwn pawent_wate;
	}

	wetuwn DIV_WOUND_UP_UWW((u64)pawent_wate, div);
}

static int stm32_dividew_set_wate(void __iomem *base,
				  stwuct cwk_stm32_cwock_data *data,
				  u16 div_id, unsigned wong wate,
				  unsigned wong pawent_wate)
{
	const stwuct stm32_div_cfg *dividew = &data->dividews[div_id];
	int vawue;
	u32 vaw;

	vawue = dividew_get_vaw(wate, pawent_wate, dividew->tabwe,
				dividew->width, dividew->fwags);
	if (vawue < 0)
		wetuwn vawue;

	if (dividew->fwags & CWK_DIVIDEW_HIWOWD_MASK) {
		vaw = cwk_div_mask(dividew->width) << (dividew->shift + 16);
	} ewse {
		vaw = weadw(base + dividew->offset);
		vaw &= ~(cwk_div_mask(dividew->width) << dividew->shift);
	}

	vaw |= (u32)vawue << dividew->shift;

	wwitew(vaw, base + dividew->offset);

	wetuwn 0;
}

static u8 cwk_stm32_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_mux *mux = to_cwk_stm32_mux(hw);

	wetuwn stm32_mux_get_pawent(mux->base, mux->cwock_data, mux->mux_id);
}

static int cwk_stm32_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_stm32_mux *mux = to_cwk_stm32_mux(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(mux->wock, fwags);

	stm32_mux_set_pawent(mux->base, mux->cwock_data, mux->mux_id, index);

	spin_unwock_iwqwestowe(mux->wock, fwags);

	wetuwn 0;
}

const stwuct cwk_ops cwk_stm32_mux_ops = {
	.detewmine_wate	= __cwk_mux_detewmine_wate,
	.get_pawent	= cwk_stm32_mux_get_pawent,
	.set_pawent	= cwk_stm32_mux_set_pawent,
};

static void cwk_stm32_gate_endisabwe(stwuct cwk_hw *hw, int enabwe)
{
	stwuct cwk_stm32_gate *gate = to_cwk_stm32_gate(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(gate->wock, fwags);

	stm32_gate_endisabwe(gate->base, gate->cwock_data, gate->gate_id, enabwe);

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static int cwk_stm32_gate_enabwe(stwuct cwk_hw *hw)
{
	cwk_stm32_gate_endisabwe(hw, 1);

	wetuwn 0;
}

static void cwk_stm32_gate_disabwe(stwuct cwk_hw *hw)
{
	cwk_stm32_gate_endisabwe(hw, 0);
}

static int cwk_stm32_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_gate *gate = to_cwk_stm32_gate(hw);

	wetuwn stm32_gate_is_enabwed(gate->base, gate->cwock_data, gate->gate_id);
}

static void cwk_stm32_gate_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_gate *gate = to_cwk_stm32_gate(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(gate->wock, fwags);

	stm32_gate_disabwe_unused(gate->base, gate->cwock_data, gate->gate_id);

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

const stwuct cwk_ops cwk_stm32_gate_ops = {
	.enabwe		= cwk_stm32_gate_enabwe,
	.disabwe	= cwk_stm32_gate_disabwe,
	.is_enabwed	= cwk_stm32_gate_is_enabwed,
	.disabwe_unused	= cwk_stm32_gate_disabwe_unused,
};

static int cwk_stm32_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct cwk_stm32_div *div = to_cwk_stm32_dividew(hw);
	unsigned wong fwags = 0;
	int wet;

	if (div->div_id == NO_STM32_DIV)
		wetuwn wate;

	spin_wock_iwqsave(div->wock, fwags);

	wet = stm32_dividew_set_wate(div->base, div->cwock_data, div->div_id, wate, pawent_wate);

	spin_unwock_iwqwestowe(div->wock, fwags);

	wetuwn wet;
}

static wong cwk_stm32_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong *pwate)
{
	stwuct cwk_stm32_div *div = to_cwk_stm32_dividew(hw);
	const stwuct stm32_div_cfg *dividew;

	if (div->div_id == NO_STM32_DIV)
		wetuwn wate;

	dividew = &div->cwock_data->dividews[div->div_id];

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw =  weadw(div->base + dividew->offset) >> dividew->shift;
		vaw &= cwk_div_mask(dividew->width);

		wetuwn dividew_wo_wound_wate(hw, wate, pwate, dividew->tabwe,
				dividew->width, dividew->fwags,
				vaw);
	}

	wetuwn dividew_wound_wate_pawent(hw, cwk_hw_get_pawent(hw),
					 wate, pwate, dividew->tabwe,
					 dividew->width, dividew->fwags);
}

static unsigned wong cwk_stm32_dividew_wecawc_wate(stwuct cwk_hw *hw,
						   unsigned wong pawent_wate)
{
	stwuct cwk_stm32_div *div = to_cwk_stm32_dividew(hw);

	if (div->div_id == NO_STM32_DIV)
		wetuwn pawent_wate;

	wetuwn stm32_dividew_get_wate(div->base, div->cwock_data, div->div_id, pawent_wate);
}

const stwuct cwk_ops cwk_stm32_dividew_ops = {
	.wecawc_wate	= cwk_stm32_dividew_wecawc_wate,
	.wound_wate	= cwk_stm32_dividew_wound_wate,
	.set_wate	= cwk_stm32_dividew_set_wate,
};

static int cwk_stm32_composite_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong pawent_wate)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	unsigned wong fwags = 0;
	int wet;

	if (composite->div_id == NO_STM32_DIV)
		wetuwn wate;

	spin_wock_iwqsave(composite->wock, fwags);

	wet = stm32_dividew_set_wate(composite->base, composite->cwock_data,
				     composite->div_id, wate, pawent_wate);

	spin_unwock_iwqwestowe(composite->wock, fwags);

	wetuwn wet;
}

static unsigned wong cwk_stm32_composite_wecawc_wate(stwuct cwk_hw *hw,
						     unsigned wong pawent_wate)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	if (composite->div_id == NO_STM32_DIV)
		wetuwn pawent_wate;

	wetuwn stm32_dividew_get_wate(composite->base, composite->cwock_data,
				      composite->div_id, pawent_wate);
}

static int cwk_stm32_composite_detewmine_wate(stwuct cwk_hw *hw,
					      stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	const stwuct stm32_div_cfg *dividew;
	wong wate;

	if (composite->div_id == NO_STM32_DIV)
		wetuwn 0;

	dividew = &composite->cwock_data->dividews[composite->div_id];

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		u32 vaw;

		vaw =  weadw(composite->base + dividew->offset) >> dividew->shift;
		vaw &= cwk_div_mask(dividew->width);

		wate = dividew_wo_wound_wate(hw, weq->wate, &weq->best_pawent_wate,
					     dividew->tabwe, dividew->width, dividew->fwags,
					     vaw);
		if (wate < 0)
			wetuwn wate;

		weq->wate = wate;
		wetuwn 0;
	}

	wate = dividew_wound_wate_pawent(hw, cwk_hw_get_pawent(hw),
					 weq->wate, &weq->best_pawent_wate,
					 dividew->tabwe, dividew->width, dividew->fwags);
	if (wate < 0)
		wetuwn wate;

	weq->wate = wate;
	wetuwn 0;
}

static u8 cwk_stm32_composite_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	wetuwn stm32_mux_get_pawent(composite->base, composite->cwock_data, composite->mux_id);
}

static int cwk_stm32_composite_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(composite->wock, fwags);

	stm32_mux_set_pawent(composite->base, composite->cwock_data, composite->mux_id, index);

	spin_unwock_iwqwestowe(composite->wock, fwags);

	if (composite->cwock_data->is_muwti_mux) {
		stwuct cwk_hw *othew_mux_hw = composite->cwock_data->is_muwti_mux(hw);

		if (othew_mux_hw) {
			stwuct cwk_hw *hwp = cwk_hw_get_pawent_by_index(hw, index);

			cwk_hw_wepawent(othew_mux_hw, hwp);
		}
	}

	wetuwn 0;
}

static int cwk_stm32_composite_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	if (composite->gate_id == NO_STM32_GATE)
		wetuwn (__cwk_get_enabwe_count(hw->cwk) > 0);

	wetuwn stm32_gate_is_enabwed(composite->base, composite->cwock_data, composite->gate_id);
}

#define MUX_SAFE_POSITION 0

static int cwk_stm32_has_safe_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	const stwuct stm32_mux_cfg *mux = &composite->cwock_data->muxes[composite->mux_id];

	wetuwn !!(mux->fwags & MUX_SAFE);
}

static void cwk_stm32_set_safe_position_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	if (!cwk_stm32_composite_is_enabwed(hw)) {
		unsigned wong fwags = 0;

		if (composite->cwock_data->is_muwti_mux) {
			stwuct cwk_hw *othew_mux_hw = NUWW;

			othew_mux_hw = composite->cwock_data->is_muwti_mux(hw);

			if (!othew_mux_hw || cwk_stm32_composite_is_enabwed(othew_mux_hw))
				wetuwn;
		}

		spin_wock_iwqsave(composite->wock, fwags);

		stm32_mux_set_pawent(composite->base, composite->cwock_data,
				     composite->mux_id, MUX_SAFE_POSITION);

		spin_unwock_iwqwestowe(composite->wock, fwags);
	}
}

static void cwk_stm32_safe_westowe_position_mux(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	int sew = cwk_hw_get_pawent_index(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(composite->wock, fwags);

	stm32_mux_set_pawent(composite->base, composite->cwock_data, composite->mux_id, sew);

	spin_unwock_iwqwestowe(composite->wock, fwags);
}

static void cwk_stm32_composite_gate_endisabwe(stwuct cwk_hw *hw, int enabwe)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(composite->wock, fwags);

	stm32_gate_endisabwe(composite->base, composite->cwock_data, composite->gate_id, enabwe);

	spin_unwock_iwqwestowe(composite->wock, fwags);
}

static int cwk_stm32_composite_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	if (composite->gate_id == NO_STM32_GATE)
		wetuwn 0;

	cwk_stm32_composite_gate_endisabwe(hw, 1);

	if (composite->mux_id != NO_STM32_MUX && cwk_stm32_has_safe_mux(hw))
		cwk_stm32_safe_westowe_position_mux(hw);

	wetuwn 0;
}

static void cwk_stm32_composite_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);

	if (composite->gate_id == NO_STM32_GATE)
		wetuwn;

	cwk_stm32_composite_gate_endisabwe(hw, 0);

	if (composite->mux_id != NO_STM32_MUX && cwk_stm32_has_safe_mux(hw))
		cwk_stm32_set_safe_position_mux(hw);
}

static void cwk_stm32_composite_disabwe_unused(stwuct cwk_hw *hw)
{
	stwuct cwk_stm32_composite *composite = to_cwk_stm32_composite(hw);
	unsigned wong fwags = 0;

	if (composite->gate_id == NO_STM32_GATE)
		wetuwn;

	spin_wock_iwqsave(composite->wock, fwags);

	stm32_gate_disabwe_unused(composite->base, composite->cwock_data, composite->gate_id);

	spin_unwock_iwqwestowe(composite->wock, fwags);
}

const stwuct cwk_ops cwk_stm32_composite_ops = {
	.set_wate	= cwk_stm32_composite_set_wate,
	.wecawc_wate	= cwk_stm32_composite_wecawc_wate,
	.detewmine_wate	= cwk_stm32_composite_detewmine_wate,
	.get_pawent	= cwk_stm32_composite_get_pawent,
	.set_pawent	= cwk_stm32_composite_set_pawent,
	.enabwe		= cwk_stm32_composite_gate_enabwe,
	.disabwe	= cwk_stm32_composite_gate_disabwe,
	.is_enabwed	= cwk_stm32_composite_is_enabwed,
	.disabwe_unused	= cwk_stm32_composite_disabwe_unused,
};

stwuct cwk_hw *cwk_stm32_mux_wegistew(stwuct device *dev,
				      const stwuct stm32_wcc_match_data *data,
				      void __iomem *base,
				      spinwock_t *wock,
				      const stwuct cwock_config *cfg)
{
	stwuct cwk_stm32_mux *mux = cfg->cwock_cfg;
	stwuct cwk_hw *hw = &mux->hw;
	int eww;

	mux->base = base;
	mux->wock = wock;
	mux->cwock_data = data->cwock_data;

	eww = cwk_hw_wegistew(dev, hw);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn hw;
}

stwuct cwk_hw *cwk_stm32_gate_wegistew(stwuct device *dev,
				       const stwuct stm32_wcc_match_data *data,
				       void __iomem *base,
				       spinwock_t *wock,
				       const stwuct cwock_config *cfg)
{
	stwuct cwk_stm32_gate *gate = cfg->cwock_cfg;
	stwuct cwk_hw *hw = &gate->hw;
	int eww;

	gate->base = base;
	gate->wock = wock;
	gate->cwock_data = data->cwock_data;

	eww = cwk_hw_wegistew(dev, hw);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn hw;
}

stwuct cwk_hw *cwk_stm32_div_wegistew(stwuct device *dev,
				      const stwuct stm32_wcc_match_data *data,
				      void __iomem *base,
				      spinwock_t *wock,
				      const stwuct cwock_config *cfg)
{
	stwuct cwk_stm32_div *div = cfg->cwock_cfg;
	stwuct cwk_hw *hw = &div->hw;
	int eww;

	div->base = base;
	div->wock = wock;
	div->cwock_data = data->cwock_data;

	eww = cwk_hw_wegistew(dev, hw);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn hw;
}

stwuct cwk_hw *cwk_stm32_composite_wegistew(stwuct device *dev,
					    const stwuct stm32_wcc_match_data *data,
					    void __iomem *base,
					    spinwock_t *wock,
					    const stwuct cwock_config *cfg)
{
	stwuct cwk_stm32_composite *composite = cfg->cwock_cfg;
	stwuct cwk_hw *hw = &composite->hw;
	int eww;

	composite->base = base;
	composite->wock = wock;
	composite->cwock_data = data->cwock_data;

	eww = cwk_hw_wegistew(dev, hw);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn hw;
}
