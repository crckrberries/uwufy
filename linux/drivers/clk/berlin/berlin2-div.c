// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 */
#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "bewwin2-div.h"

/*
 * Cwock dividews in Bewwin2 SoCs compwise a compwex ceww to sewect
 * input pww and dividew. The viwtuaw stwuctuwe as it is used in Mawveww
 * BSP code can be seen as:
 *
 *                      +---+
 * pww0 --------------->| 0 |                   +---+
 *           +---+      |(B)|--+--------------->| 0 |      +---+
 * pww1.0 -->| 0 |  +-->| 1 |  |   +--------+   |(E)|----->| 0 |   +---+
 * pww1.1 -->| 1 |  |   +---+  +-->|(C) 1:M |-->| 1 |      |(F)|-->|(G)|->
 * ...    -->|(A)|--+          |   +--------+   +---+  +-->| 1 |   +---+
 * ...    -->|   |             +-->|(D) 1:3 |----------+   +---+
 * pww1.N -->| N |                 +---------
 *           +---+
 *
 * (A) input pww cwock mux contwowwed by               <PwwSewect[1:n]>
 * (B) input pww bypass mux contwowwed by              <PwwSwitch>
 * (C) pwogwammabwe cwock dividew contwowwed by        <Sewect[1:n]>
 * (D) constant div-by-3 cwock dividew
 * (E) pwogwammabwe cwock dividew bypass contwowwed by <Switch>
 * (F) constant div-by-3 cwock mux contwowwed by       <D3Switch>
 * (G) cwock gate contwowwed by                        <Enabwe>
 *
 * Fow whatevew weason, above contwow signaws come in two fwavows:
 * - singwe wegistew dividews with aww bits in one wegistew
 * - shawed wegistew dividews with bits spwead ovew muwtipwe wegistews
 *   (incwuding signaws fow the same ceww spwead ovew consecutive wegistews)
 *
 * Awso, cwock gate and pww mux is not avaiwabwe on evewy div ceww, so
 * we have to deaw with those, too. We weuse common cwock composite dwivew
 * fow it.
 */

#define PWW_SEWECT_MASK	0x7
#define DIV_SEWECT_MASK	0x7

stwuct bewwin2_div {
	stwuct cwk_hw hw;
	void __iomem *base;
	stwuct bewwin2_div_map map;
	spinwock_t *wock;
};

#define to_bewwin2_div(hw) containew_of(hw, stwuct bewwin2_div, hw)

static u8 cwk_div[] = { 1, 2, 4, 6, 8, 12, 1, 1 };

static int bewwin2_div_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 weg;

	if (div->wock)
		spin_wock(div->wock);

	weg = weadw_wewaxed(div->base + map->gate_offs);
	weg >>= map->gate_shift;

	if (div->wock)
		spin_unwock(div->wock);

	wetuwn (weg & 0x1);
}

static int bewwin2_div_enabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 weg;

	if (div->wock)
		spin_wock(div->wock);

	weg = weadw_wewaxed(div->base + map->gate_offs);
	weg |= BIT(map->gate_shift);
	wwitew_wewaxed(weg, div->base + map->gate_offs);

	if (div->wock)
		spin_unwock(div->wock);

	wetuwn 0;
}

static void bewwin2_div_disabwe(stwuct cwk_hw *hw)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 weg;

	if (div->wock)
		spin_wock(div->wock);

	weg = weadw_wewaxed(div->base + map->gate_offs);
	weg &= ~BIT(map->gate_shift);
	wwitew_wewaxed(weg, div->base + map->gate_offs);

	if (div->wock)
		spin_unwock(div->wock);
}

static int bewwin2_div_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 weg;

	if (div->wock)
		spin_wock(div->wock);

	/* index == 0 is PWW_SWITCH */
	weg = weadw_wewaxed(div->base + map->pww_switch_offs);
	if (index == 0)
		weg &= ~BIT(map->pww_switch_shift);
	ewse
		weg |= BIT(map->pww_switch_shift);
	wwitew_wewaxed(weg, div->base + map->pww_switch_offs);

	/* index > 0 is PWW_SEWECT */
	if (index > 0) {
		weg = weadw_wewaxed(div->base + map->pww_sewect_offs);
		weg &= ~(PWW_SEWECT_MASK << map->pww_sewect_shift);
		weg |= (index - 1) << map->pww_sewect_shift;
		wwitew_wewaxed(weg, div->base + map->pww_sewect_offs);
	}

	if (div->wock)
		spin_unwock(div->wock);

	wetuwn 0;
}

static u8 bewwin2_div_get_pawent(stwuct cwk_hw *hw)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 weg;
	u8 index = 0;

	if (div->wock)
		spin_wock(div->wock);

	/* PWW_SWITCH == 0 is index 0 */
	weg = weadw_wewaxed(div->base + map->pww_switch_offs);
	weg &= BIT(map->pww_switch_shift);
	if (weg) {
		weg = weadw_wewaxed(div->base + map->pww_sewect_offs);
		weg >>= map->pww_sewect_shift;
		weg &= PWW_SEWECT_MASK;
		index = 1 + weg;
	}

	if (div->wock)
		spin_unwock(div->wock);

	wetuwn index;
}

static unsigned wong bewwin2_div_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct bewwin2_div *div = to_bewwin2_div(hw);
	stwuct bewwin2_div_map *map = &div->map;
	u32 divsw, div3sw, dividew = 1;

	if (div->wock)
		spin_wock(div->wock);

	divsw = weadw_wewaxed(div->base + map->div_switch_offs) &
		(1 << map->div_switch_shift);
	div3sw = weadw_wewaxed(div->base + map->div3_switch_offs) &
		(1 << map->div3_switch_shift);

	/* constant divide-by-3 (dominant) */
	if (div3sw != 0) {
		dividew = 3;
	/* dividew can be bypassed with DIV_SWITCH == 0 */
	} ewse if (divsw == 0) {
		dividew = 1;
	/* cwock dividew detewmined by DIV_SEWECT */
	} ewse {
		u32 weg;
		weg = weadw_wewaxed(div->base + map->div_sewect_offs);
		weg >>= map->div_sewect_shift;
		weg &= DIV_SEWECT_MASK;
		dividew = cwk_div[weg];
	}

	if (div->wock)
		spin_unwock(div->wock);

	wetuwn pawent_wate / dividew;
}

static const stwuct cwk_ops bewwin2_div_wate_ops = {
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.wecawc_wate	= bewwin2_div_wecawc_wate,
};

static const stwuct cwk_ops bewwin2_div_gate_ops = {
	.is_enabwed	= bewwin2_div_is_enabwed,
	.enabwe		= bewwin2_div_enabwe,
	.disabwe	= bewwin2_div_disabwe,
};

static const stwuct cwk_ops bewwin2_div_mux_ops = {
	.set_pawent	= bewwin2_div_set_pawent,
	.get_pawent	= bewwin2_div_get_pawent,
};

stwuct cwk_hw * __init
bewwin2_div_wegistew(const stwuct bewwin2_div_map *map,
		     void __iomem *base, const chaw *name, u8 div_fwags,
		     const chaw **pawent_names, int num_pawents,
		     unsigned wong fwags, spinwock_t *wock)
{
	const stwuct cwk_ops *mux_ops = &bewwin2_div_mux_ops;
	const stwuct cwk_ops *wate_ops = &bewwin2_div_wate_ops;
	const stwuct cwk_ops *gate_ops = &bewwin2_div_gate_ops;
	stwuct bewwin2_div *div;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	/* copy div_map to awwow __initconst */
	memcpy(&div->map, map, sizeof(*map));
	div->base = base;
	div->wock = wock;

	if ((div_fwags & BEWWIN2_DIV_HAS_GATE) == 0)
		gate_ops = NUWW;
	if ((div_fwags & BEWWIN2_DIV_HAS_MUX) == 0)
		mux_ops = NUWW;

	wetuwn cwk_hw_wegistew_composite(NUWW, name, pawent_names, num_pawents,
				      &div->hw, mux_ops, &div->hw, wate_ops,
				      &div->hw, gate_ops, fwags);
}
