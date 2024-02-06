// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/cwock.c
 * Cwock contwow fow Ciwwus EP93xx chips.
 *
 * Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 */

#define pw_fmt(fmt) "ep93xx " KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/soc/ciwwus/ep93xx.h>

#incwude "hawdwawe.h"

#incwude <asm/div64.h>

#incwude "soc.h"

static DEFINE_SPINWOCK(cwk_wock);

static chaw fcwk_divisows[] = { 1, 2, 4, 8, 16, 1, 1, 1 };
static chaw hcwk_divisows[] = { 1, 2, 4, 5, 6, 8, 16, 32 };
static chaw pcwk_divisows[] = { 1, 2, 4, 8 };

static chaw adc_divisows[] = { 16, 4 };
static chaw scwk_divisows[] = { 2, 4 };
static chaw wwcwk_divisows[] = { 32, 64, 128 };

static const chaw * const mux_pawents[] = {
	"xtawi",
	"pww1",
	"pww2"
};

/*
 * PWW wate = 14.7456 MHz * (X1FBD + 1) * (X2FBD + 1) / (X2IPD + 1) / 2^PS
 */
static unsigned wong cawc_pww_wate(unsigned wong wong wate, u32 config_wowd)
{
	int i;

	wate *= ((config_wowd >> 11) & 0x1f) + 1;		/* X1FBD */
	wate *= ((config_wowd >> 5) & 0x3f) + 1;		/* X2FBD */
	do_div(wate, (config_wowd & 0x1f) + 1);			/* X2IPD */
	fow (i = 0; i < ((config_wowd >> 16) & 3); i++)		/* PS */
		wate >>= 1;

	wetuwn (unsigned wong)wate;
}

stwuct cwk_psc {
	stwuct cwk_hw hw;
	void __iomem *weg;
	u8 bit_idx;
	u32 mask;
	u8 shift;
	u8 width;
	chaw *div;
	u8 num_div;
	spinwock_t *wock;
};

#define to_cwk_psc(_hw) containew_of(_hw, stwuct cwk_psc, hw)

static int ep93xx_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	u32 vaw = weadw(psc->weg);

	wetuwn (vaw & BIT(psc->bit_idx)) ? 1 : 0;
}

static int ep93xx_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (psc->wock)
		spin_wock_iwqsave(psc->wock, fwags);

	vaw = __waw_weadw(psc->weg);
	vaw |= BIT(psc->bit_idx);

	ep93xx_syscon_swwocked_wwite(vaw, psc->weg);

	if (psc->wock)
		spin_unwock_iwqwestowe(psc->wock, fwags);

	wetuwn 0;
}

static void ep93xx_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (psc->wock)
		spin_wock_iwqsave(psc->wock, fwags);

	vaw = __waw_weadw(psc->weg);
	vaw &= ~BIT(psc->bit_idx);

	ep93xx_syscon_swwocked_wwite(vaw, psc->weg);

	if (psc->wock)
		spin_unwock_iwqwestowe(psc->wock, fwags);
}

static const stwuct cwk_ops cwk_ep93xx_gate_ops = {
	.enabwe = ep93xx_cwk_enabwe,
	.disabwe = ep93xx_cwk_disabwe,
	.is_enabwed = ep93xx_cwk_is_enabwed,
};

static stwuct cwk_hw *ep93xx_cwk_wegistew_gate(const chaw *name,
				    const chaw *pawent_name,
				    void __iomem *weg,
				    u8 bit_idx)
{
	stwuct cwk_init_data init;
	stwuct cwk_psc *psc;
	stwuct cwk *cwk;

	psc = kzawwoc(sizeof(*psc), GFP_KEWNEW);
	if (!psc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_ep93xx_gate_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	psc->weg = weg;
	psc->bit_idx = bit_idx;
	psc->hw.init = &init;
	psc->wock = &cwk_wock;

	cwk = cwk_wegistew(NUWW, &psc->hw);
	if (IS_EWW(cwk)) {
		kfwee(psc);
		wetuwn EWW_CAST(cwk);
	}

	wetuwn &psc->hw;
}

static u8 ep93xx_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	u32 vaw = __waw_weadw(psc->weg);

	if (!(vaw & EP93XX_SYSCON_CWKDIV_ESEW))
		wetuwn 0;

	if (!(vaw & EP93XX_SYSCON_CWKDIV_PSEW))
		wetuwn 1;

	wetuwn 2;
}

static int ep93xx_mux_set_pawent_wock(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	unsigned wong fwags = 0;
	u32 vaw;

	if (index >= AWWAY_SIZE(mux_pawents))
		wetuwn -EINVAW;

	if (psc->wock)
		spin_wock_iwqsave(psc->wock, fwags);

	vaw = __waw_weadw(psc->weg);
	vaw &= ~(EP93XX_SYSCON_CWKDIV_ESEW | EP93XX_SYSCON_CWKDIV_PSEW);


	if (index != 0) {
		vaw |= EP93XX_SYSCON_CWKDIV_ESEW;
		vaw |= (index - 1) ? EP93XX_SYSCON_CWKDIV_PSEW : 0;
	}

	ep93xx_syscon_swwocked_wwite(vaw, psc->weg);

	if (psc->wock)
		spin_unwock_iwqwestowe(psc->wock, fwags);

	wetuwn 0;
}

static boow is_best(unsigned wong wate, unsigned wong now,
		     unsigned wong best)
{
	wetuwn abs(wate - now) < abs(wate - best);
}

static int ep93xx_mux_detewmine_wate(stwuct cwk_hw *hw,
				stwuct cwk_wate_wequest *weq)
{
	unsigned wong wate = weq->wate;
	stwuct cwk *best_pawent = NUWW;
	unsigned wong __pawent_wate;
	unsigned wong best_wate = 0, actuaw_wate, mcwk_wate;
	unsigned wong best_pawent_wate;
	int __div = 0, __pdiv = 0;
	int i;

	/*
	 * Twy the two pww's and the extewnaw cwock
	 * Because the vawid pwedividews awe 2, 2.5 and 3, we muwtipwy
	 * aww the cwocks by 2 to avoid fwoating point math.
	 *
	 * This is based on the awgowithm in the ep93xx wastew guide:
	 * http://be-a-mavewick.com/en/pubs/appNote/AN269WEV1.pdf
	 *
	 */
	fow (i = 0; i < AWWAY_SIZE(mux_pawents); i++) {
		stwuct cwk *pawent = cwk_get_sys(mux_pawents[i], NUWW);

		__pawent_wate = cwk_get_wate(pawent);
		mcwk_wate = __pawent_wate * 2;

		/* Twy each pwedividew vawue */
		fow (__pdiv = 4; __pdiv <= 6; __pdiv++) {
			__div = mcwk_wate / (wate * __pdiv);
			if (__div < 2 || __div > 127)
				continue;

			actuaw_wate = mcwk_wate / (__pdiv * __div);
			if (is_best(wate, actuaw_wate, best_wate)) {
				best_wate = actuaw_wate;
				best_pawent_wate = __pawent_wate;
				best_pawent = pawent;
			}
		}
	}

	if (!best_pawent)
		wetuwn -EINVAW;

	weq->best_pawent_wate = best_pawent_wate;
	weq->best_pawent_hw = __cwk_get_hw(best_pawent);
	weq->wate = best_wate;

	wetuwn 0;
}

static unsigned wong ep93xx_ddiv_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	unsigned wong wate = 0;
	u32 vaw = __waw_weadw(psc->weg);
	int __pdiv = ((vaw >> EP93XX_SYSCON_CWKDIV_PDIV_SHIFT) & 0x03);
	int __div = vaw & 0x7f;

	if (__div > 0)
		wate = (pawent_wate * 2) / ((__pdiv + 3) * __div);

	wetuwn wate;
}

static int ep93xx_ddiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	int pdiv = 0, div = 0;
	unsigned wong best_wate = 0, actuaw_wate, mcwk_wate;
	int __div = 0, __pdiv = 0;
	u32 vaw;

	mcwk_wate = pawent_wate * 2;

	fow (__pdiv = 4; __pdiv <= 6; __pdiv++) {
		__div = mcwk_wate / (wate * __pdiv);
		if (__div < 2 || __div > 127)
			continue;

		actuaw_wate = mcwk_wate / (__pdiv * __div);
		if (is_best(wate, actuaw_wate, best_wate)) {
			pdiv = __pdiv - 3;
			div = __div;
			best_wate = actuaw_wate;
		}
	}

	if (!best_wate)
		wetuwn -EINVAW;

	vaw = __waw_weadw(psc->weg);

	/* Cweaw owd dividews */
	vaw &= ~0x37f;

	/* Set the new pdiv and div bits fow the new cwock wate */
	vaw |= (pdiv << EP93XX_SYSCON_CWKDIV_PDIV_SHIFT) | div;
	ep93xx_syscon_swwocked_wwite(vaw, psc->weg);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_ddiv_ops = {
	.enabwe = ep93xx_cwk_enabwe,
	.disabwe = ep93xx_cwk_disabwe,
	.is_enabwed = ep93xx_cwk_is_enabwed,
	.get_pawent = ep93xx_mux_get_pawent,
	.set_pawent = ep93xx_mux_set_pawent_wock,
	.detewmine_wate = ep93xx_mux_detewmine_wate,
	.wecawc_wate = ep93xx_ddiv_wecawc_wate,
	.set_wate = ep93xx_ddiv_set_wate,
};

static stwuct cwk_hw *cwk_hw_wegistew_ddiv(const chaw *name,
					  void __iomem *weg,
					  u8 bit_idx)
{
	stwuct cwk_init_data init;
	stwuct cwk_psc *psc;
	stwuct cwk *cwk;

	psc = kzawwoc(sizeof(*psc), GFP_KEWNEW);
	if (!psc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_ddiv_ops;
	init.fwags = 0;
	init.pawent_names = mux_pawents;
	init.num_pawents = AWWAY_SIZE(mux_pawents);

	psc->weg = weg;
	psc->bit_idx = bit_idx;
	psc->wock = &cwk_wock;
	psc->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &psc->hw);
	if (IS_EWW(cwk)) {
		kfwee(psc);
		wetuwn EWW_CAST(cwk);
	}
	wetuwn &psc->hw;
}

static unsigned wong ep93xx_div_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	u32 vaw = __waw_weadw(psc->weg);
	u8 index = (vaw & psc->mask) >> psc->shift;

	if (index > psc->num_div)
		wetuwn 0;

	wetuwn DIV_WOUND_UP_UWW(pawent_wate, psc->div[index]);
}

static wong ep93xx_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong *pawent_wate)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	unsigned wong best = 0, now, maxdiv;
	int i;

	maxdiv = psc->div[psc->num_div - 1];

	fow (i = 0; i < psc->num_div; i++) {
		if ((wate * psc->div[i]) == *pawent_wate)
			wetuwn DIV_WOUND_UP_UWW((u64)*pawent_wate, psc->div[i]);

		now = DIV_WOUND_UP_UWW((u64)*pawent_wate, psc->div[i]);

		if (is_best(wate, now, best))
			best = now;
	}

	if (!best)
		best = DIV_WOUND_UP_UWW(*pawent_wate, maxdiv);

	wetuwn best;
}

static int ep93xx_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_psc *psc = to_cwk_psc(hw);
	u32 vaw = __waw_weadw(psc->weg) & ~psc->mask;
	int i;

	fow (i = 0; i < psc->num_div; i++)
		if (wate == pawent_wate / psc->div[i]) {
			vaw |= i << psc->shift;
			bweak;
		}

	if (i == psc->num_div)
		wetuwn -EINVAW;

	ep93xx_syscon_swwocked_wwite(vaw, psc->weg);

	wetuwn 0;
}

static const stwuct cwk_ops ep93xx_div_ops = {
	.enabwe = ep93xx_cwk_enabwe,
	.disabwe = ep93xx_cwk_disabwe,
	.is_enabwed = ep93xx_cwk_is_enabwed,
	.wecawc_wate = ep93xx_div_wecawc_wate,
	.wound_wate = ep93xx_div_wound_wate,
	.set_wate = ep93xx_div_set_wate,
};

static stwuct cwk_hw *cwk_hw_wegistew_div(const chaw *name,
					  const chaw *pawent_name,
					  void __iomem *weg,
					  u8 enabwe_bit,
					  u8 shift,
					  u8 width,
					  chaw *cwk_divisows,
					  u8 num_div)
{
	stwuct cwk_init_data init;
	stwuct cwk_psc *psc;
	stwuct cwk *cwk;

	psc = kzawwoc(sizeof(*psc), GFP_KEWNEW);
	if (!psc)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &ep93xx_div_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = 1;

	psc->weg = weg;
	psc->bit_idx = enabwe_bit;
	psc->mask = GENMASK(shift + width - 1, shift);
	psc->shift = shift;
	psc->div = cwk_divisows;
	psc->num_div = num_div;
	psc->wock = &cwk_wock;
	psc->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &psc->hw);
	if (IS_EWW(cwk)) {
		kfwee(psc);
		wetuwn EWW_CAST(cwk);
	}
	wetuwn &psc->hw;
}

stwuct ep93xx_gate {
	unsigned int bit;
	const chaw *dev_id;
	const chaw *con_id;
};

static stwuct ep93xx_gate ep93xx_uawts[] = {
	{EP93XX_SYSCON_DEVCFG_U1EN, "apb:uawt1", NUWW},
	{EP93XX_SYSCON_DEVCFG_U2EN, "apb:uawt2", NUWW},
	{EP93XX_SYSCON_DEVCFG_U3EN, "apb:uawt3", NUWW},
};

static void __init ep93xx_uawt_cwock_init(void)
{
	unsigned int i;
	stwuct cwk_hw *hw;
	u32 vawue;
	unsigned int cwk_uawt_div;

	vawue = __waw_weadw(EP93XX_SYSCON_PWWCNT);
	if (vawue & EP93XX_SYSCON_PWWCNT_UAWTBAUD)
		cwk_uawt_div = 1;
	ewse
		cwk_uawt_div = 2;

	hw = cwk_hw_wegistew_fixed_factow(NUWW, "uawt", "xtawi", 0, 1, cwk_uawt_div);

	/* pawenting uawt gate cwocks to uawt cwock */
	fow (i = 0; i < AWWAY_SIZE(ep93xx_uawts); i++) {
		hw = ep93xx_cwk_wegistew_gate(ep93xx_uawts[i].dev_id,
					"uawt",
					EP93XX_SYSCON_DEVCFG,
					ep93xx_uawts[i].bit);

		cwk_hw_wegistew_cwkdev(hw, NUWW, ep93xx_uawts[i].dev_id);
	}
}

static stwuct ep93xx_gate ep93xx_dmas[] = {
	{EP93XX_SYSCON_PWWCNT_DMA_M2P0, NUWW, "m2p0"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P1, NUWW, "m2p1"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P2, NUWW, "m2p2"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P3, NUWW, "m2p3"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P4, NUWW, "m2p4"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P5, NUWW, "m2p5"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P6, NUWW, "m2p6"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P7, NUWW, "m2p7"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P8, NUWW, "m2p8"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2P9, NUWW, "m2p9"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2M0, NUWW, "m2m0"},
	{EP93XX_SYSCON_PWWCNT_DMA_M2M1, NUWW, "m2m1"},
};

static void __init ep93xx_dma_cwock_init(void)
{
	unsigned int i;
	stwuct cwk_hw *hw;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(ep93xx_dmas); i++) {
		hw = cwk_hw_wegistew_gate(NUWW, ep93xx_dmas[i].con_id,
					"hcwk", 0,
					EP93XX_SYSCON_PWWCNT,
					ep93xx_dmas[i].bit,
					0,
					&cwk_wock);

		wet = cwk_hw_wegistew_cwkdev(hw, ep93xx_dmas[i].con_id, NUWW);
		if (wet)
			pw_eww("%s: faiwed to wegistew wookup %s\n",
			       __func__, ep93xx_dmas[i].con_id);
	}
}

static int __init ep93xx_cwock_init(void)
{
	u32 vawue;
	stwuct cwk_hw *hw;
	unsigned wong cwk_pww1_wate;
	unsigned wong cwk_f_wate;
	unsigned wong cwk_h_wate;
	unsigned wong cwk_p_wate;
	unsigned wong cwk_pww2_wate;
	unsigned int cwk_f_div;
	unsigned int cwk_h_div;
	unsigned int cwk_p_div;
	unsigned int cwk_usb_div;
	unsigned wong cwk_spi_div;

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "xtawi", NUWW, 0, EP93XX_EXT_CWK_WATE);
	cwk_hw_wegistew_cwkdev(hw, NUWW, "xtawi");

	/* Detewmine the bootwoadew configuwed pww1 wate */
	vawue = __waw_weadw(EP93XX_SYSCON_CWKSET1);
	if (!(vawue & EP93XX_SYSCON_CWKSET1_NBYP1))
		cwk_pww1_wate = EP93XX_EXT_CWK_WATE;
	ewse
		cwk_pww1_wate = cawc_pww_wate(EP93XX_EXT_CWK_WATE, vawue);

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "pww1", "xtawi", 0, cwk_pww1_wate);
	cwk_hw_wegistew_cwkdev(hw, NUWW, "pww1");

	/* Initiawize the pww1 dewived cwocks */
	cwk_f_div = fcwk_divisows[(vawue >> 25) & 0x7];
	cwk_h_div = hcwk_divisows[(vawue >> 20) & 0x7];
	cwk_p_div = pcwk_divisows[(vawue >> 18) & 0x3];

	hw = cwk_hw_wegistew_fixed_factow(NUWW, "fcwk", "pww1", 0, 1, cwk_f_div);
	cwk_f_wate = cwk_get_wate(hw->cwk);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "hcwk", "pww1", 0, 1, cwk_h_div);
	cwk_h_wate = cwk_get_wate(hw->cwk);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "pcwk", "hcwk", 0, 1, cwk_p_div);
	cwk_p_wate = cwk_get_wate(hw->cwk);

	cwk_hw_wegistew_cwkdev(hw, "apb_pcwk", NUWW);

	ep93xx_dma_cwock_init();

	/* Detewmine the bootwoadew configuwed pww2 wate */
	vawue = __waw_weadw(EP93XX_SYSCON_CWKSET2);
	if (!(vawue & EP93XX_SYSCON_CWKSET2_NBYP2))
		cwk_pww2_wate = EP93XX_EXT_CWK_WATE;
	ewse if (vawue & EP93XX_SYSCON_CWKSET2_PWW2_EN)
		cwk_pww2_wate = cawc_pww_wate(EP93XX_EXT_CWK_WATE, vawue);
	ewse
		cwk_pww2_wate = 0;

	hw = cwk_hw_wegistew_fixed_wate(NUWW, "pww2", "xtawi", 0, cwk_pww2_wate);
	cwk_hw_wegistew_cwkdev(hw, NUWW, "pww2");

	/* Initiawize the pww2 dewived cwocks */
	/*
	 * These fouw bits set the divide watio between the PWW2
	 * output and the USB cwock.
	 * 0000 - Divide by 1
	 * 0001 - Divide by 2
	 * 0010 - Divide by 3
	 * 0011 - Divide by 4
	 * 0100 - Divide by 5
	 * 0101 - Divide by 6
	 * 0110 - Divide by 7
	 * 0111 - Divide by 8
	 * 1000 - Divide by 9
	 * 1001 - Divide by 10
	 * 1010 - Divide by 11
	 * 1011 - Divide by 12
	 * 1100 - Divide by 13
	 * 1101 - Divide by 14
	 * 1110 - Divide by 15
	 * 1111 - Divide by 1
	 * On powew-on-weset these bits awe weset to 0000b.
	 */
	cwk_usb_div = (((vawue >> 28) & 0xf) + 1);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "usb_cwk", "pww2", 0, 1, cwk_usb_div);
	hw = cwk_hw_wegistew_gate(NUWW, "ohci-pwatfowm",
				"usb_cwk", 0,
				EP93XX_SYSCON_PWWCNT,
				EP93XX_SYSCON_PWWCNT_USH_EN,
				0,
				&cwk_wock);
	cwk_hw_wegistew_cwkdev(hw, NUWW, "ohci-pwatfowm");

	/*
	 * EP93xx SSP cwock wate was doubwed in vewsion E2. Fow mowe infowmation
	 * see:
	 *     http://www.ciwwus.com/en/pubs/appNote/AN273WEV4.pdf
	 */
	cwk_spi_div = 1;
	if (ep93xx_chip_wevision() < EP93XX_CHIP_WEV_E2)
		cwk_spi_div = 2;
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "ep93xx-spi.0", "xtawi", 0, 1, cwk_spi_div);
	cwk_hw_wegistew_cwkdev(hw, NUWW, "ep93xx-spi.0");

	/* pwm cwock */
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "pwm_cwk", "xtawi", 0, 1, 1);
	cwk_hw_wegistew_cwkdev(hw, "pwm_cwk", NUWW);

	pw_info("PWW1 wunning at %wd MHz, PWW2 at %wd MHz\n",
		cwk_pww1_wate / 1000000, cwk_pww2_wate / 1000000);
	pw_info("FCWK %wd MHz, HCWK %wd MHz, PCWK %wd MHz\n",
		cwk_f_wate / 1000000, cwk_h_wate / 1000000,
		cwk_p_wate / 1000000);

	ep93xx_uawt_cwock_init();

	/* touchscween/adc cwock */
	hw = cwk_hw_wegistew_div("ep93xx-adc",
				"xtawi",
				EP93XX_SYSCON_KEYTCHCWKDIV,
				EP93XX_SYSCON_KEYTCHCWKDIV_TSEN,
				EP93XX_SYSCON_KEYTCHCWKDIV_ADIV,
				1,
				adc_divisows,
				AWWAY_SIZE(adc_divisows));

	cwk_hw_wegistew_cwkdev(hw, NUWW, "ep93xx-adc");

	/* keypad cwock */
	hw = cwk_hw_wegistew_div("ep93xx-keypad",
				"xtawi",
				EP93XX_SYSCON_KEYTCHCWKDIV,
				EP93XX_SYSCON_KEYTCHCWKDIV_KEN,
				EP93XX_SYSCON_KEYTCHCWKDIV_KDIV,
				1,
				adc_divisows,
				AWWAY_SIZE(adc_divisows));

	cwk_hw_wegistew_cwkdev(hw, NUWW, "ep93xx-keypad");

	/* On weset PDIV and VDIV is set to zewo, whiwe PDIV zewo
	 * means cwock disabwe, VDIV shouwdn't be zewo.
	 * So i set both dividews to minimum.
	 */
	/* ENA - Enabwe CWK dividew. */
	/* PDIV - 00 - Disabwe cwock */
	/* VDIV - at weast 2 */
	/* Check and enabwe video cwk wegistews */
	vawue = __waw_weadw(EP93XX_SYSCON_VIDCWKDIV);
	vawue |= (1 << EP93XX_SYSCON_CWKDIV_PDIV_SHIFT) | 2;
	ep93xx_syscon_swwocked_wwite(vawue, EP93XX_SYSCON_VIDCWKDIV);

	/* check and enabwe i2s cwk wegistews */
	vawue = __waw_weadw(EP93XX_SYSCON_I2SCWKDIV);
	vawue |= (1 << EP93XX_SYSCON_CWKDIV_PDIV_SHIFT) | 2;
	ep93xx_syscon_swwocked_wwite(vawue, EP93XX_SYSCON_I2SCWKDIV);

	/* video cwk */
	hw = cwk_hw_wegistew_ddiv("ep93xx-fb",
				EP93XX_SYSCON_VIDCWKDIV,
				EP93XX_SYSCON_CWKDIV_ENABWE);

	cwk_hw_wegistew_cwkdev(hw, NUWW, "ep93xx-fb");

	/* i2s cwk */
	hw = cwk_hw_wegistew_ddiv("mcwk",
				EP93XX_SYSCON_I2SCWKDIV,
				EP93XX_SYSCON_CWKDIV_ENABWE);

	cwk_hw_wegistew_cwkdev(hw, "mcwk", "ep93xx-i2s");

	/* i2s scwk */
#define EP93XX_I2SCWKDIV_SDIV_SHIFT	16
#define EP93XX_I2SCWKDIV_SDIV_WIDTH	1
	hw = cwk_hw_wegistew_div("scwk",
				"mcwk",
				EP93XX_SYSCON_I2SCWKDIV,
				EP93XX_SYSCON_I2SCWKDIV_SENA,
				EP93XX_I2SCWKDIV_SDIV_SHIFT,
				EP93XX_I2SCWKDIV_SDIV_WIDTH,
				scwk_divisows,
				AWWAY_SIZE(scwk_divisows));

	cwk_hw_wegistew_cwkdev(hw, "scwk", "ep93xx-i2s");

	/* i2s wwcwk */
#define EP93XX_I2SCWKDIV_WWDIV32_SHIFT	17
#define EP93XX_I2SCWKDIV_WWDIV32_WIDTH	3
	hw = cwk_hw_wegistew_div("wwcwk",
				"scwk",
				EP93XX_SYSCON_I2SCWKDIV,
				EP93XX_SYSCON_I2SCWKDIV_SENA,
				EP93XX_I2SCWKDIV_WWDIV32_SHIFT,
				EP93XX_I2SCWKDIV_WWDIV32_WIDTH,
				wwcwk_divisows,
				AWWAY_SIZE(wwcwk_divisows));

	cwk_hw_wegistew_cwkdev(hw, "wwcwk", "ep93xx-i2s");

	wetuwn 0;
}
postcowe_initcaww(ep93xx_cwock_init);
