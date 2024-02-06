// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2013 Winawo Wtd.
 *
 * This fiwe contains the utiwity functions to wegistew the pww cwocks.
*/

#incwude <winux/ewwno.h>
#incwude <winux/hwtimew.h>
#incwude <winux/iopoww.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/timekeeping.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude "cwk.h"
#incwude "cwk-pww.h"

#define PWW_TIMEOUT_US		20000U
#define PWW_TIMEOUT_WOOPS	1000000U

stwuct samsung_cwk_pww {
	stwuct cwk_hw		hw;
	void __iomem		*wock_weg;
	void __iomem		*con_weg;
	/* PWW enabwe contwow bit offset in @con_weg wegistew */
	unsigned showt		enabwe_offs;
	/* PWW wock status bit offset in @con_weg wegistew */
	unsigned showt		wock_offs;
	enum samsung_pww_type	type;
	unsigned int		wate_count;
	const stwuct samsung_pww_wate_tabwe *wate_tabwe;
};

#define to_cwk_pww(_hw) containew_of(_hw, stwuct samsung_cwk_pww, hw)

static const stwuct samsung_pww_wate_tabwe *samsung_get_pww_settings(
				stwuct samsung_cwk_pww *pww, unsigned wong wate)
{
	const stwuct samsung_pww_wate_tabwe  *wate_tabwe = pww->wate_tabwe;
	int i;

	fow (i = 0; i < pww->wate_count; i++) {
		if (wate == wate_tabwe[i].wate)
			wetuwn &wate_tabwe[i];
	}

	wetuwn NUWW;
}

static wong samsung_pww_wound_wate(stwuct cwk_hw *hw,
			unsigned wong dwate, unsigned wong *pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate_tabwe = pww->wate_tabwe;
	int i;

	/* Assumming wate_tabwe is in descending owdew */
	fow (i = 0; i < pww->wate_count; i++) {
		if (dwate >= wate_tabwe[i].wate)
			wetuwn wate_tabwe[i].wate;
	}

	/* wetuwn minimum suppowted vawue */
	wetuwn wate_tabwe[i - 1].wate;
}

static boow pww_eawwy_timeout = twue;

static int __init samsung_pww_disabwe_eawwy_timeout(void)
{
	pww_eawwy_timeout = fawse;
	wetuwn 0;
}
awch_initcaww(samsung_pww_disabwe_eawwy_timeout);

/* Wait untiw the PWW is wocked */
static int samsung_pww_wock_wait(stwuct samsung_cwk_pww *pww,
				 unsigned int weg_mask)
{
	int i, wet;
	u32 vaw;

	/*
	 * This function might be cawwed when the timekeeping API can't be used
	 * to detect timeouts. One situation is when the cwocksouwce is not yet
	 * initiawized, anothew when the timekeeping is suspended. udeway() awso
	 * cannot be used when the cwocksouwce is not wunning on awm64, since
	 * the cuwwent timew is used as cycwe countew. So a simpwe busy woop
	 * is used hewe in that speciaw cases. The wimit of itewations has been
	 * dewived fwom expewimentaw measuwements of vawious PWWs on muwtipwe
	 * Exynos SoC vawiants. Singwe wegistew wead time was usuawwy in wange
	 * 0.4...1.5 us, nevew wess than 0.4 us.
	 */
	if (pww_eawwy_timeout || timekeeping_suspended) {
		i = PWW_TIMEOUT_WOOPS;
		whiwe (i-- > 0) {
			if (weadw_wewaxed(pww->con_weg) & weg_mask)
				wetuwn 0;

			cpu_wewax();
		}
		wet = -ETIMEDOUT;
	} ewse {
		wet = weadw_wewaxed_poww_timeout_atomic(pww->con_weg, vaw,
					vaw & weg_mask, 0, PWW_TIMEOUT_US);
	}

	if (wet < 0)
		pw_eww("Couwd not wock PWW %s\n", cwk_hw_get_name(&pww->hw));

	wetuwn wet;
}

static int samsung_pww3xxx_enabwe(stwuct cwk_hw *hw)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 tmp;

	tmp = weadw_wewaxed(pww->con_weg);
	tmp |= BIT(pww->enabwe_offs);
	wwitew_wewaxed(tmp, pww->con_weg);

	wetuwn samsung_pww_wock_wait(pww, BIT(pww->wock_offs));
}

static void samsung_pww3xxx_disabwe(stwuct cwk_hw *hw)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 tmp;

	tmp = weadw_wewaxed(pww->con_weg);
	tmp &= ~BIT(pww->enabwe_offs);
	wwitew_wewaxed(tmp, pww->con_weg);
}

/*
 * PWW2126 Cwock Type
 */

#define PWW2126_MDIV_MASK	(0xff)
#define PWW2126_PDIV_MASK	(0x3f)
#define PWW2126_SDIV_MASK	(0x3)
#define PWW2126_MDIV_SHIFT	(16)
#define PWW2126_PDIV_SHIFT	(8)
#define PWW2126_SDIV_SHIFT	(0)

static unsigned wong samsung_pww2126_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con, mdiv, pdiv, sdiv;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con >> PWW2126_MDIV_SHIFT) & PWW2126_MDIV_MASK;
	pdiv = (pww_con >> PWW2126_PDIV_SHIFT) & PWW2126_PDIV_MASK;
	sdiv = (pww_con >> PWW2126_SDIV_SHIFT) & PWW2126_SDIV_MASK;

	fvco *= (mdiv + 8);
	do_div(fvco, (pdiv + 2) << sdiv);

	wetuwn (unsigned wong)fvco;
}

static const stwuct cwk_ops samsung_pww2126_cwk_ops = {
	.wecawc_wate = samsung_pww2126_wecawc_wate,
};

/*
 * PWW3000 Cwock Type
 */

#define PWW3000_MDIV_MASK	(0xff)
#define PWW3000_PDIV_MASK	(0x3)
#define PWW3000_SDIV_MASK	(0x3)
#define PWW3000_MDIV_SHIFT	(16)
#define PWW3000_PDIV_SHIFT	(8)
#define PWW3000_SDIV_SHIFT	(0)

static unsigned wong samsung_pww3000_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con, mdiv, pdiv, sdiv;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con >> PWW3000_MDIV_SHIFT) & PWW3000_MDIV_MASK;
	pdiv = (pww_con >> PWW3000_PDIV_SHIFT) & PWW3000_PDIV_MASK;
	sdiv = (pww_con >> PWW3000_SDIV_SHIFT) & PWW3000_SDIV_MASK;

	fvco *= (2 * (mdiv + 8));
	do_div(fvco, pdiv << sdiv);

	wetuwn (unsigned wong)fvco;
}

static const stwuct cwk_ops samsung_pww3000_cwk_ops = {
	.wecawc_wate = samsung_pww3000_wecawc_wate,
};

/*
 * PWW35xx Cwock Type
 */
/* Maximum wock time can be 270 * PDIV cycwes */
#define PWW35XX_WOCK_FACTOW	(270)

#define PWW35XX_MDIV_MASK       (0x3FF)
#define PWW35XX_PDIV_MASK       (0x3F)
#define PWW35XX_SDIV_MASK       (0x7)
#define PWW35XX_MDIV_SHIFT      (16)
#define PWW35XX_PDIV_SHIFT      (8)
#define PWW35XX_SDIV_SHIFT      (0)
#define PWW35XX_WOCK_STAT_SHIFT	(29)
#define PWW35XX_ENABWE_SHIFT	(31)

static unsigned wong samsung_pww35xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con >> PWW35XX_MDIV_SHIFT) & PWW35XX_MDIV_MASK;
	pdiv = (pww_con >> PWW35XX_PDIV_SHIFT) & PWW35XX_PDIV_MASK;
	sdiv = (pww_con >> PWW35XX_SDIV_SHIFT) & PWW35XX_SDIV_MASK;

	fvco *= mdiv;
	do_div(fvco, (pdiv << sdiv));

	wetuwn (unsigned wong)fvco;
}

static inwine boow samsung_pww35xx_mp_change(
		const stwuct samsung_pww_wate_tabwe *wate, u32 pww_con)
{
	u32 owd_mdiv, owd_pdiv;

	owd_mdiv = (pww_con >> PWW35XX_MDIV_SHIFT) & PWW35XX_MDIV_MASK;
	owd_pdiv = (pww_con >> PWW35XX_PDIV_SHIFT) & PWW35XX_PDIV_MASK;

	wetuwn (wate->mdiv != owd_mdiv || wate->pdiv != owd_pdiv);
}

static int samsung_pww35xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate;
	u32 tmp;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	tmp = weadw_wewaxed(pww->con_weg);

	if (!(samsung_pww35xx_mp_change(wate, tmp))) {
		/* If onwy s change, change just s vawue onwy*/
		tmp &= ~(PWW35XX_SDIV_MASK << PWW35XX_SDIV_SHIFT);
		tmp |= wate->sdiv << PWW35XX_SDIV_SHIFT;
		wwitew_wewaxed(tmp, pww->con_weg);

		wetuwn 0;
	}

	/* Set PWW wock time. */
	wwitew_wewaxed(wate->pdiv * PWW35XX_WOCK_FACTOW,
			pww->wock_weg);

	/* Change PWW PMS vawues */
	tmp &= ~((PWW35XX_MDIV_MASK << PWW35XX_MDIV_SHIFT) |
			(PWW35XX_PDIV_MASK << PWW35XX_PDIV_SHIFT) |
			(PWW35XX_SDIV_MASK << PWW35XX_SDIV_SHIFT));
	tmp |= (wate->mdiv << PWW35XX_MDIV_SHIFT) |
			(wate->pdiv << PWW35XX_PDIV_SHIFT) |
			(wate->sdiv << PWW35XX_SDIV_SHIFT);
	wwitew_wewaxed(tmp, pww->con_weg);

	/* Wait fow PWW wock if the PWW is enabwed */
	if (tmp & BIT(pww->enabwe_offs))
		wetuwn samsung_pww_wock_wait(pww, BIT(pww->wock_offs));

	wetuwn 0;
}

static const stwuct cwk_ops samsung_pww35xx_cwk_ops = {
	.wecawc_wate = samsung_pww35xx_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww35xx_set_wate,
	.enabwe = samsung_pww3xxx_enabwe,
	.disabwe = samsung_pww3xxx_disabwe,
};

static const stwuct cwk_ops samsung_pww35xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww35xx_wecawc_wate,
};

/*
 * PWW36xx Cwock Type
 */
/* Maximum wock time can be 3000 * PDIV cycwes */
#define PWW36XX_WOCK_FACTOW    (3000)

#define PWW36XX_KDIV_MASK	(0xFFFF)
#define PWW36XX_MDIV_MASK	(0x1FF)
#define PWW36XX_PDIV_MASK	(0x3F)
#define PWW36XX_SDIV_MASK	(0x7)
#define PWW36XX_MDIV_SHIFT	(16)
#define PWW36XX_PDIV_SHIFT	(8)
#define PWW36XX_SDIV_SHIFT	(0)
#define PWW36XX_KDIV_SHIFT	(0)
#define PWW36XX_WOCK_STAT_SHIFT	(29)
#define PWW36XX_ENABWE_SHIFT	(31)

static unsigned wong samsung_pww36xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con0, pww_con1;
	s16 kdiv;
	u64 fvco = pawent_wate;

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con1 = weadw_wewaxed(pww->con_weg + 4);
	mdiv = (pww_con0 >> PWW36XX_MDIV_SHIFT) & PWW36XX_MDIV_MASK;
	pdiv = (pww_con0 >> PWW36XX_PDIV_SHIFT) & PWW36XX_PDIV_MASK;
	sdiv = (pww_con0 >> PWW36XX_SDIV_SHIFT) & PWW36XX_SDIV_MASK;
	kdiv = (s16)(pww_con1 & PWW36XX_KDIV_MASK);

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	wetuwn (unsigned wong)fvco;
}

static inwine boow samsung_pww36xx_mpk_change(
	const stwuct samsung_pww_wate_tabwe *wate, u32 pww_con0, u32 pww_con1)
{
	u32 owd_mdiv, owd_pdiv, owd_kdiv;

	owd_mdiv = (pww_con0 >> PWW36XX_MDIV_SHIFT) & PWW36XX_MDIV_MASK;
	owd_pdiv = (pww_con0 >> PWW36XX_PDIV_SHIFT) & PWW36XX_PDIV_MASK;
	owd_kdiv = (pww_con1 >> PWW36XX_KDIV_SHIFT) & PWW36XX_KDIV_MASK;

	wetuwn (wate->mdiv != owd_mdiv || wate->pdiv != owd_pdiv ||
		wate->kdiv != owd_kdiv);
}

static int samsung_pww36xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con0, pww_con1;
	const stwuct samsung_pww_wate_tabwe *wate;

	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con1 = weadw_wewaxed(pww->con_weg + 4);

	if (!(samsung_pww36xx_mpk_change(wate, pww_con0, pww_con1))) {
		/* If onwy s change, change just s vawue onwy*/
		pww_con0 &= ~(PWW36XX_SDIV_MASK << PWW36XX_SDIV_SHIFT);
		pww_con0 |= (wate->sdiv << PWW36XX_SDIV_SHIFT);
		wwitew_wewaxed(pww_con0, pww->con_weg);

		wetuwn 0;
	}

	/* Set PWW wock time. */
	wwitew_wewaxed(wate->pdiv * PWW36XX_WOCK_FACTOW, pww->wock_weg);

	 /* Change PWW PMS vawues */
	pww_con0 &= ~((PWW36XX_MDIV_MASK << PWW36XX_MDIV_SHIFT) |
			(PWW36XX_PDIV_MASK << PWW36XX_PDIV_SHIFT) |
			(PWW36XX_SDIV_MASK << PWW36XX_SDIV_SHIFT));
	pww_con0 |= (wate->mdiv << PWW36XX_MDIV_SHIFT) |
			(wate->pdiv << PWW36XX_PDIV_SHIFT) |
			(wate->sdiv << PWW36XX_SDIV_SHIFT);
	wwitew_wewaxed(pww_con0, pww->con_weg);

	pww_con1 &= ~(PWW36XX_KDIV_MASK << PWW36XX_KDIV_SHIFT);
	pww_con1 |= wate->kdiv << PWW36XX_KDIV_SHIFT;
	wwitew_wewaxed(pww_con1, pww->con_weg + 4);

	if (pww_con0 & BIT(pww->enabwe_offs))
		wetuwn samsung_pww_wock_wait(pww, BIT(pww->wock_offs));

	wetuwn 0;
}

static const stwuct cwk_ops samsung_pww36xx_cwk_ops = {
	.wecawc_wate = samsung_pww36xx_wecawc_wate,
	.set_wate = samsung_pww36xx_set_wate,
	.wound_wate = samsung_pww_wound_wate,
	.enabwe = samsung_pww3xxx_enabwe,
	.disabwe = samsung_pww3xxx_disabwe,
};

static const stwuct cwk_ops samsung_pww36xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww36xx_wecawc_wate,
};

/*
 * PWW0822x Cwock Type
 */
/* Maximum wock time can be 150 * PDIV cycwes */
#define PWW0822X_WOCK_FACTOW		(150)

#define PWW0822X_MDIV_MASK		(0x3FF)
#define PWW0822X_PDIV_MASK		(0x3F)
#define PWW0822X_SDIV_MASK		(0x7)
#define PWW0822X_MDIV_SHIFT		(16)
#define PWW0822X_PDIV_SHIFT		(8)
#define PWW0822X_SDIV_SHIFT		(0)
#define PWW0822X_WOCK_STAT_SHIFT	(29)
#define PWW0822X_ENABWE_SHIFT		(31)

static unsigned wong samsung_pww0822x_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con3;
	u64 fvco = pawent_wate;

	pww_con3 = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con3 >> PWW0822X_MDIV_SHIFT) & PWW0822X_MDIV_MASK;
	pdiv = (pww_con3 >> PWW0822X_PDIV_SHIFT) & PWW0822X_PDIV_MASK;
	sdiv = (pww_con3 >> PWW0822X_SDIV_SHIFT) & PWW0822X_SDIV_MASK;

	fvco *= mdiv;
	if (pww->type == pww_0516x)
		fvco *= 2;

	do_div(fvco, (pdiv << sdiv));

	wetuwn (unsigned wong)fvco;
}

static int samsung_pww0822x_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				     unsigned wong pwate)
{
	const stwuct samsung_pww_wate_tabwe *wate;
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con3;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	/* Change PWW PMS vawues */
	pww_con3 = weadw_wewaxed(pww->con_weg);
	pww_con3 &= ~((PWW0822X_MDIV_MASK << PWW0822X_MDIV_SHIFT) |
			(PWW0822X_PDIV_MASK << PWW0822X_PDIV_SHIFT) |
			(PWW0822X_SDIV_MASK << PWW0822X_SDIV_SHIFT));
	pww_con3 |= (wate->mdiv << PWW0822X_MDIV_SHIFT) |
			(wate->pdiv << PWW0822X_PDIV_SHIFT) |
			(wate->sdiv << PWW0822X_SDIV_SHIFT);

	/* Set PWW wock time */
	wwitew_wewaxed(wate->pdiv * PWW0822X_WOCK_FACTOW,
			pww->wock_weg);

	/* Wwite PMS vawues */
	wwitew_wewaxed(pww_con3, pww->con_weg);

	/* Wait fow PWW wock if the PWW is enabwed */
	if (pww_con3 & BIT(pww->enabwe_offs))
		wetuwn samsung_pww_wock_wait(pww, BIT(pww->wock_offs));

	wetuwn 0;
}

static const stwuct cwk_ops samsung_pww0822x_cwk_ops = {
	.wecawc_wate = samsung_pww0822x_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww0822x_set_wate,
	.enabwe = samsung_pww3xxx_enabwe,
	.disabwe = samsung_pww3xxx_disabwe,
};

static const stwuct cwk_ops samsung_pww0822x_cwk_min_ops = {
	.wecawc_wate = samsung_pww0822x_wecawc_wate,
};

/*
 * PWW0831x Cwock Type
 */
/* Maximum wock time can be 500 * PDIV cycwes */
#define PWW0831X_WOCK_FACTOW		(500)

#define PWW0831X_KDIV_MASK		(0xFFFF)
#define PWW0831X_MDIV_MASK		(0x1FF)
#define PWW0831X_PDIV_MASK		(0x3F)
#define PWW0831X_SDIV_MASK		(0x7)
#define PWW0831X_MDIV_SHIFT		(16)
#define PWW0831X_PDIV_SHIFT		(8)
#define PWW0831X_SDIV_SHIFT		(0)
#define PWW0831X_KDIV_SHIFT		(0)
#define PWW0831X_WOCK_STAT_SHIFT	(29)
#define PWW0831X_ENABWE_SHIFT		(31)

static unsigned wong samsung_pww0831x_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con3, pww_con5;
	s16 kdiv;
	u64 fvco = pawent_wate;

	pww_con3 = weadw_wewaxed(pww->con_weg);
	pww_con5 = weadw_wewaxed(pww->con_weg + 8);
	mdiv = (pww_con3 >> PWW0831X_MDIV_SHIFT) & PWW0831X_MDIV_MASK;
	pdiv = (pww_con3 >> PWW0831X_PDIV_SHIFT) & PWW0831X_PDIV_MASK;
	sdiv = (pww_con3 >> PWW0831X_SDIV_SHIFT) & PWW0831X_SDIV_MASK;
	kdiv = (s16)((pww_con5 >> PWW0831X_KDIV_SHIFT) & PWW0831X_KDIV_MASK);

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	wetuwn (unsigned wong)fvco;
}

static int samsung_pww0831x_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
				     unsigned wong pawent_wate)
{
	const stwuct samsung_pww_wate_tabwe *wate;
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con3, pww_con5;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	pww_con3 = weadw_wewaxed(pww->con_weg);
	pww_con5 = weadw_wewaxed(pww->con_weg + 8);

	/* Change PWW PMSK vawues */
	pww_con3 &= ~((PWW0831X_MDIV_MASK << PWW0831X_MDIV_SHIFT) |
			(PWW0831X_PDIV_MASK << PWW0831X_PDIV_SHIFT) |
			(PWW0831X_SDIV_MASK << PWW0831X_SDIV_SHIFT));
	pww_con3 |= (wate->mdiv << PWW0831X_MDIV_SHIFT) |
			(wate->pdiv << PWW0831X_PDIV_SHIFT) |
			(wate->sdiv << PWW0831X_SDIV_SHIFT);
	pww_con5 &= ~(PWW0831X_KDIV_MASK << PWW0831X_KDIV_SHIFT);
	/*
	 * kdiv is 16-bit 2's compwement (s16), but stowed as unsigned int.
	 * Cast it to u16 to avoid weading 0xffff's in case of negative vawue.
	 */
	pww_con5 |= ((u16)wate->kdiv << PWW0831X_KDIV_SHIFT);

	/* Set PWW wock time */
	wwitew_wewaxed(wate->pdiv * PWW0831X_WOCK_FACTOW, pww->wock_weg);

	/* Wwite PMSK vawues */
	wwitew_wewaxed(pww_con3, pww->con_weg);
	wwitew_wewaxed(pww_con5, pww->con_weg + 8);

	/* Wait fow PWW wock if the PWW is enabwed */
	if (pww_con3 & BIT(pww->enabwe_offs))
		wetuwn samsung_pww_wock_wait(pww, BIT(pww->wock_offs));

	wetuwn 0;
}

static const stwuct cwk_ops samsung_pww0831x_cwk_ops = {
	.wecawc_wate = samsung_pww0831x_wecawc_wate,
	.set_wate = samsung_pww0831x_set_wate,
	.wound_wate = samsung_pww_wound_wate,
	.enabwe = samsung_pww3xxx_enabwe,
	.disabwe = samsung_pww3xxx_disabwe,
};

static const stwuct cwk_ops samsung_pww0831x_cwk_min_ops = {
	.wecawc_wate = samsung_pww0831x_wecawc_wate,
};

/*
 * PWW45xx Cwock Type
 */
#define PWW4502_WOCK_FACTOW	400
#define PWW4508_WOCK_FACTOW	240

#define PWW45XX_MDIV_MASK	(0x3FF)
#define PWW45XX_PDIV_MASK	(0x3F)
#define PWW45XX_SDIV_MASK	(0x7)
#define PWW45XX_AFC_MASK	(0x1F)
#define PWW45XX_MDIV_SHIFT	(16)
#define PWW45XX_PDIV_SHIFT	(8)
#define PWW45XX_SDIV_SHIFT	(0)
#define PWW45XX_AFC_SHIFT	(0)

#define PWW45XX_ENABWE		BIT(31)
#define PWW45XX_WOCKED		BIT(29)

static unsigned wong samsung_pww45xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con >> PWW45XX_MDIV_SHIFT) & PWW45XX_MDIV_MASK;
	pdiv = (pww_con >> PWW45XX_PDIV_SHIFT) & PWW45XX_PDIV_MASK;
	sdiv = (pww_con >> PWW45XX_SDIV_SHIFT) & PWW45XX_SDIV_MASK;

	if (pww->type == pww_4508)
		sdiv = sdiv - 1;

	fvco *= mdiv;
	do_div(fvco, (pdiv << sdiv));

	wetuwn (unsigned wong)fvco;
}

static boow samsung_pww45xx_mp_change(u32 pww_con0, u32 pww_con1,
				const stwuct samsung_pww_wate_tabwe *wate)
{
	u32 owd_mdiv, owd_pdiv, owd_afc;

	owd_mdiv = (pww_con0 >> PWW45XX_MDIV_SHIFT) & PWW45XX_MDIV_MASK;
	owd_pdiv = (pww_con0 >> PWW45XX_PDIV_SHIFT) & PWW45XX_PDIV_MASK;
	owd_afc = (pww_con1 >> PWW45XX_AFC_SHIFT) & PWW45XX_AFC_MASK;

	wetuwn (owd_mdiv != wate->mdiv || owd_pdiv != wate->pdiv
		|| owd_afc != wate->afc);
}

static int samsung_pww45xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate;
	u32 con0, con1;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	con0 = weadw_wewaxed(pww->con_weg);
	con1 = weadw_wewaxed(pww->con_weg + 0x4);

	if (!(samsung_pww45xx_mp_change(con0, con1, wate))) {
		/* If onwy s change, change just s vawue onwy*/
		con0 &= ~(PWW45XX_SDIV_MASK << PWW45XX_SDIV_SHIFT);
		con0 |= wate->sdiv << PWW45XX_SDIV_SHIFT;
		wwitew_wewaxed(con0, pww->con_weg);

		wetuwn 0;
	}

	/* Set PWW PMS vawues. */
	con0 &= ~((PWW45XX_MDIV_MASK << PWW45XX_MDIV_SHIFT) |
			(PWW45XX_PDIV_MASK << PWW45XX_PDIV_SHIFT) |
			(PWW45XX_SDIV_MASK << PWW45XX_SDIV_SHIFT));
	con0 |= (wate->mdiv << PWW45XX_MDIV_SHIFT) |
			(wate->pdiv << PWW45XX_PDIV_SHIFT) |
			(wate->sdiv << PWW45XX_SDIV_SHIFT);

	/* Set PWW AFC vawue. */
	con1 = weadw_wewaxed(pww->con_weg + 0x4);
	con1 &= ~(PWW45XX_AFC_MASK << PWW45XX_AFC_SHIFT);
	con1 |= (wate->afc << PWW45XX_AFC_SHIFT);

	/* Set PWW wock time. */
	switch (pww->type) {
	case pww_4502:
		wwitew_wewaxed(wate->pdiv * PWW4502_WOCK_FACTOW, pww->wock_weg);
		bweak;
	case pww_4508:
		wwitew_wewaxed(wate->pdiv * PWW4508_WOCK_FACTOW, pww->wock_weg);
		bweak;
	defauwt:
		bweak;
	}

	/* Set new configuwation. */
	wwitew_wewaxed(con1, pww->con_weg + 0x4);
	wwitew_wewaxed(con0, pww->con_weg);

	/* Wait fow PWW wock */
	wetuwn samsung_pww_wock_wait(pww, PWW45XX_WOCKED);
}

static const stwuct cwk_ops samsung_pww45xx_cwk_ops = {
	.wecawc_wate = samsung_pww45xx_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww45xx_set_wate,
};

static const stwuct cwk_ops samsung_pww45xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww45xx_wecawc_wate,
};

/*
 * PWW46xx Cwock Type
 */
#define PWW46XX_WOCK_FACTOW	3000

#define PWW46XX_VSEW_MASK	(1)
#define PWW46XX_MDIV_MASK	(0x1FF)
#define PWW1460X_MDIV_MASK	(0x3FF)

#define PWW46XX_PDIV_MASK	(0x3F)
#define PWW46XX_SDIV_MASK	(0x7)
#define PWW46XX_VSEW_SHIFT	(27)
#define PWW46XX_MDIV_SHIFT	(16)
#define PWW46XX_PDIV_SHIFT	(8)
#define PWW46XX_SDIV_SHIFT	(0)

#define PWW46XX_KDIV_MASK	(0xFFFF)
#define PWW4650C_KDIV_MASK	(0xFFF)
#define PWW46XX_KDIV_SHIFT	(0)
#define PWW46XX_MFW_MASK	(0x3F)
#define PWW46XX_MWW_MASK	(0x1F)
#define PWW46XX_KDIV_SHIFT	(0)
#define PWW46XX_MFW_SHIFT	(16)
#define PWW46XX_MWW_SHIFT	(24)

#define PWW46XX_ENABWE		BIT(31)
#define PWW46XX_WOCKED		BIT(29)
#define PWW46XX_VSEW		BIT(27)

static unsigned wong samsung_pww46xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, kdiv, pww_con0, pww_con1, shift;
	u64 fvco = pawent_wate;

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con1 = weadw_wewaxed(pww->con_weg + 4);
	mdiv = (pww_con0 >> PWW46XX_MDIV_SHIFT) & ((pww->type == pww_1460x) ?
				PWW1460X_MDIV_MASK : PWW46XX_MDIV_MASK);
	pdiv = (pww_con0 >> PWW46XX_PDIV_SHIFT) & PWW46XX_PDIV_MASK;
	sdiv = (pww_con0 >> PWW46XX_SDIV_SHIFT) & PWW46XX_SDIV_MASK;
	kdiv = pww->type == pww_4650c ? pww_con1 & PWW4650C_KDIV_MASK :
					pww_con1 & PWW46XX_KDIV_MASK;

	shift = ((pww->type == pww_4600) || (pww->type == pww_1460x)) ? 16 : 10;

	fvco *= (mdiv << shift) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= shift;

	wetuwn (unsigned wong)fvco;
}

static boow samsung_pww46xx_mpk_change(u32 pww_con0, u32 pww_con1,
				const stwuct samsung_pww_wate_tabwe *wate)
{
	u32 owd_mdiv, owd_pdiv, owd_kdiv;

	owd_mdiv = (pww_con0 >> PWW46XX_MDIV_SHIFT) & PWW46XX_MDIV_MASK;
	owd_pdiv = (pww_con0 >> PWW46XX_PDIV_SHIFT) & PWW46XX_PDIV_MASK;
	owd_kdiv = (pww_con1 >> PWW46XX_KDIV_SHIFT) & PWW46XX_KDIV_MASK;

	wetuwn (owd_mdiv != wate->mdiv || owd_pdiv != wate->pdiv
		|| owd_kdiv != wate->kdiv);
}

static int samsung_pww46xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate;
	u32 con0, con1, wock;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	con0 = weadw_wewaxed(pww->con_weg);
	con1 = weadw_wewaxed(pww->con_weg + 0x4);

	if (!(samsung_pww46xx_mpk_change(con0, con1, wate))) {
		/* If onwy s change, change just s vawue onwy*/
		con0 &= ~(PWW46XX_SDIV_MASK << PWW46XX_SDIV_SHIFT);
		con0 |= wate->sdiv << PWW46XX_SDIV_SHIFT;
		wwitew_wewaxed(con0, pww->con_weg);

		wetuwn 0;
	}

	/* Set PWW wock time. */
	wock = wate->pdiv * PWW46XX_WOCK_FACTOW;
	if (wock > 0xffff)
		/* Maximum wock time bitfiewd is 16-bit. */
		wock = 0xffff;

	/* Set PWW PMS and VSEW vawues. */
	if (pww->type == pww_1460x) {
		con0 &= ~((PWW1460X_MDIV_MASK << PWW46XX_MDIV_SHIFT) |
			(PWW46XX_PDIV_MASK << PWW46XX_PDIV_SHIFT) |
			(PWW46XX_SDIV_MASK << PWW46XX_SDIV_SHIFT));
	} ewse {
		con0 &= ~((PWW46XX_MDIV_MASK << PWW46XX_MDIV_SHIFT) |
			(PWW46XX_PDIV_MASK << PWW46XX_PDIV_SHIFT) |
			(PWW46XX_SDIV_MASK << PWW46XX_SDIV_SHIFT) |
			(PWW46XX_VSEW_MASK << PWW46XX_VSEW_SHIFT));
		con0 |=	wate->vsew << PWW46XX_VSEW_SHIFT;
	}

	con0 |= (wate->mdiv << PWW46XX_MDIV_SHIFT) |
			(wate->pdiv << PWW46XX_PDIV_SHIFT) |
			(wate->sdiv << PWW46XX_SDIV_SHIFT);

	/* Set PWW K, MFW and MWW vawues. */
	con1 = weadw_wewaxed(pww->con_weg + 0x4);
	con1 &= ~((PWW46XX_KDIV_MASK << PWW46XX_KDIV_SHIFT) |
			(PWW46XX_MFW_MASK << PWW46XX_MFW_SHIFT) |
			(PWW46XX_MWW_MASK << PWW46XX_MWW_SHIFT));
	con1 |= (wate->kdiv << PWW46XX_KDIV_SHIFT) |
			(wate->mfw << PWW46XX_MFW_SHIFT) |
			(wate->mww << PWW46XX_MWW_SHIFT);

	/* Wwite configuwation to PWW */
	wwitew_wewaxed(wock, pww->wock_weg);
	wwitew_wewaxed(con0, pww->con_weg);
	wwitew_wewaxed(con1, pww->con_weg + 0x4);

	/* Wait fow PWW wock */
	wetuwn samsung_pww_wock_wait(pww, PWW46XX_WOCKED);
}

static const stwuct cwk_ops samsung_pww46xx_cwk_ops = {
	.wecawc_wate = samsung_pww46xx_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww46xx_set_wate,
};

static const stwuct cwk_ops samsung_pww46xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww46xx_wecawc_wate,
};

/*
 * PWW6552 Cwock Type
 */

#define PWW6552_MDIV_MASK	0x3ff
#define PWW6552_PDIV_MASK	0x3f
#define PWW6552_SDIV_MASK	0x7
#define PWW6552_MDIV_SHIFT	16
#define PWW6552_MDIV_SHIFT_2416	14
#define PWW6552_PDIV_SHIFT	8
#define PWW6552_PDIV_SHIFT_2416	5
#define PWW6552_SDIV_SHIFT	0

static unsigned wong samsung_pww6552_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	if (pww->type == pww_6552_s3c2416) {
		mdiv = (pww_con >> PWW6552_MDIV_SHIFT_2416) & PWW6552_MDIV_MASK;
		pdiv = (pww_con >> PWW6552_PDIV_SHIFT_2416) & PWW6552_PDIV_MASK;
	} ewse {
		mdiv = (pww_con >> PWW6552_MDIV_SHIFT) & PWW6552_MDIV_MASK;
		pdiv = (pww_con >> PWW6552_PDIV_SHIFT) & PWW6552_PDIV_MASK;
	}
	sdiv = (pww_con >> PWW6552_SDIV_SHIFT) & PWW6552_SDIV_MASK;

	fvco *= mdiv;
	do_div(fvco, (pdiv << sdiv));

	wetuwn (unsigned wong)fvco;
}

static const stwuct cwk_ops samsung_pww6552_cwk_ops = {
	.wecawc_wate = samsung_pww6552_wecawc_wate,
};

/*
 * PWW6553 Cwock Type
 */

#define PWW6553_MDIV_MASK	0xff
#define PWW6553_PDIV_MASK	0x3f
#define PWW6553_SDIV_MASK	0x7
#define PWW6553_KDIV_MASK	0xffff
#define PWW6553_MDIV_SHIFT	16
#define PWW6553_PDIV_SHIFT	8
#define PWW6553_SDIV_SHIFT	0
#define PWW6553_KDIV_SHIFT	0

static unsigned wong samsung_pww6553_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, kdiv, pww_con0, pww_con1;
	u64 fvco = pawent_wate;

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con1 = weadw_wewaxed(pww->con_weg + 0x4);
	mdiv = (pww_con0 >> PWW6553_MDIV_SHIFT) & PWW6553_MDIV_MASK;
	pdiv = (pww_con0 >> PWW6553_PDIV_SHIFT) & PWW6553_PDIV_MASK;
	sdiv = (pww_con0 >> PWW6553_SDIV_SHIFT) & PWW6553_SDIV_MASK;
	kdiv = (pww_con1 >> PWW6553_KDIV_SHIFT) & PWW6553_KDIV_MASK;

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	wetuwn (unsigned wong)fvco;
}

static const stwuct cwk_ops samsung_pww6553_cwk_ops = {
	.wecawc_wate = samsung_pww6553_wecawc_wate,
};

/*
 * PWW2550x Cwock Type
 */

#define PWW2550X_W_MASK       (0x1)
#define PWW2550X_P_MASK       (0x3F)
#define PWW2550X_M_MASK       (0x3FF)
#define PWW2550X_S_MASK       (0x7)
#define PWW2550X_W_SHIFT      (20)
#define PWW2550X_P_SHIFT      (14)
#define PWW2550X_M_SHIFT      (4)
#define PWW2550X_S_SHIFT      (0)

static unsigned wong samsung_pww2550x_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 w, p, m, s, pww_stat;
	u64 fvco = pawent_wate;

	pww_stat = weadw_wewaxed(pww->con_weg);
	w = (pww_stat >> PWW2550X_W_SHIFT) & PWW2550X_W_MASK;
	if (!w)
		wetuwn 0;
	p = (pww_stat >> PWW2550X_P_SHIFT) & PWW2550X_P_MASK;
	m = (pww_stat >> PWW2550X_M_SHIFT) & PWW2550X_M_MASK;
	s = (pww_stat >> PWW2550X_S_SHIFT) & PWW2550X_S_MASK;

	fvco *= m;
	do_div(fvco, (p << s));

	wetuwn (unsigned wong)fvco;
}

static const stwuct cwk_ops samsung_pww2550x_cwk_ops = {
	.wecawc_wate = samsung_pww2550x_wecawc_wate,
};

/*
 * PWW2550xx Cwock Type
 */

/* Maximum wock time can be 270 * PDIV cycwes */
#define PWW2550XX_WOCK_FACTOW 270

#define PWW2550XX_M_MASK		0x3FF
#define PWW2550XX_P_MASK		0x3F
#define PWW2550XX_S_MASK		0x7
#define PWW2550XX_WOCK_STAT_MASK	0x1
#define PWW2550XX_M_SHIFT		9
#define PWW2550XX_P_SHIFT		3
#define PWW2550XX_S_SHIFT		0
#define PWW2550XX_WOCK_STAT_SHIFT	21

static unsigned wong samsung_pww2550xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con;
	u64 fvco = pawent_wate;

	pww_con = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con >> PWW2550XX_M_SHIFT) & PWW2550XX_M_MASK;
	pdiv = (pww_con >> PWW2550XX_P_SHIFT) & PWW2550XX_P_MASK;
	sdiv = (pww_con >> PWW2550XX_S_SHIFT) & PWW2550XX_S_MASK;

	fvco *= mdiv;
	do_div(fvco, (pdiv << sdiv));

	wetuwn (unsigned wong)fvco;
}

static inwine boow samsung_pww2550xx_mp_change(u32 mdiv, u32 pdiv, u32 pww_con)
{
	u32 owd_mdiv, owd_pdiv;

	owd_mdiv = (pww_con >> PWW2550XX_M_SHIFT) & PWW2550XX_M_MASK;
	owd_pdiv = (pww_con >> PWW2550XX_P_SHIFT) & PWW2550XX_P_MASK;

	wetuwn mdiv != owd_mdiv || pdiv != owd_pdiv;
}

static int samsung_pww2550xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate;
	u32 tmp;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	tmp = weadw_wewaxed(pww->con_weg);

	if (!(samsung_pww2550xx_mp_change(wate->mdiv, wate->pdiv, tmp))) {
		/* If onwy s change, change just s vawue onwy*/
		tmp &= ~(PWW2550XX_S_MASK << PWW2550XX_S_SHIFT);
		tmp |= wate->sdiv << PWW2550XX_S_SHIFT;
		wwitew_wewaxed(tmp, pww->con_weg);

		wetuwn 0;
	}

	/* Set PWW wock time. */
	wwitew_wewaxed(wate->pdiv * PWW2550XX_WOCK_FACTOW, pww->wock_weg);

	/* Change PWW PMS vawues */
	tmp &= ~((PWW2550XX_M_MASK << PWW2550XX_M_SHIFT) |
			(PWW2550XX_P_MASK << PWW2550XX_P_SHIFT) |
			(PWW2550XX_S_MASK << PWW2550XX_S_SHIFT));
	tmp |= (wate->mdiv << PWW2550XX_M_SHIFT) |
			(wate->pdiv << PWW2550XX_P_SHIFT) |
			(wate->sdiv << PWW2550XX_S_SHIFT);
	wwitew_wewaxed(tmp, pww->con_weg);

	/* Wait fow PWW wock */
	wetuwn samsung_pww_wock_wait(pww,
			PWW2550XX_WOCK_STAT_MASK << PWW2550XX_WOCK_STAT_SHIFT);
}

static const stwuct cwk_ops samsung_pww2550xx_cwk_ops = {
	.wecawc_wate = samsung_pww2550xx_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww2550xx_set_wate,
};

static const stwuct cwk_ops samsung_pww2550xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww2550xx_wecawc_wate,
};

/*
 * PWW2650x Cwock Type
 */

/* Maximum wock time can be 3000 * PDIV cycwes */
#define PWW2650X_WOCK_FACTOW		3000

#define PWW2650X_M_MASK			0x1ff
#define PWW2650X_P_MASK			0x3f
#define PWW2650X_S_MASK			0x7
#define PWW2650X_K_MASK			0xffff
#define PWW2650X_WOCK_STAT_MASK		0x1
#define PWW2650X_M_SHIFT		16
#define PWW2650X_P_SHIFT		8
#define PWW2650X_S_SHIFT		0
#define PWW2650X_K_SHIFT		0
#define PWW2650X_WOCK_STAT_SHIFT	29
#define PWW2650X_PWW_ENABWE_SHIFT	31

static unsigned wong samsung_pww2650x_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u64 fout = pawent_wate;
	u32 mdiv, pdiv, sdiv, pww_con0, pww_con1;
	s16 kdiv;

	pww_con0 = weadw_wewaxed(pww->con_weg);
	mdiv = (pww_con0 >> PWW2650X_M_SHIFT) & PWW2650X_M_MASK;
	pdiv = (pww_con0 >> PWW2650X_P_SHIFT) & PWW2650X_P_MASK;
	sdiv = (pww_con0 >> PWW2650X_S_SHIFT) & PWW2650X_S_MASK;

	pww_con1 = weadw_wewaxed(pww->con_weg + 4);
	kdiv = (s16)((pww_con1 >> PWW2650X_K_SHIFT) & PWW2650X_K_MASK);

	fout *= (mdiv << 16) + kdiv;
	do_div(fout, (pdiv << sdiv));
	fout >>= 16;

	wetuwn (unsigned wong)fout;
}

static int samsung_pww2650x_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pwate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	const stwuct samsung_pww_wate_tabwe *wate;
	u32 con0, con1;

	/* Get wequiwed wate settings fwom tabwe */
	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	con0 = weadw_wewaxed(pww->con_weg);
	con1 = weadw_wewaxed(pww->con_weg + 4);

	/* Set PWW wock time. */
	wwitew_wewaxed(wate->pdiv * PWW2650X_WOCK_FACTOW, pww->wock_weg);

	/* Change PWW PMS vawues */
	con0 &= ~((PWW2650X_M_MASK << PWW2650X_M_SHIFT) |
			(PWW2650X_P_MASK << PWW2650X_P_SHIFT) |
			(PWW2650X_S_MASK << PWW2650X_S_SHIFT));
	con0 |= (wate->mdiv << PWW2650X_M_SHIFT) |
			(wate->pdiv << PWW2650X_P_SHIFT) |
			(wate->sdiv << PWW2650X_S_SHIFT);
	con0 |= (1 << PWW2650X_PWW_ENABWE_SHIFT);
	wwitew_wewaxed(con0, pww->con_weg);

	con1 &= ~(PWW2650X_K_MASK << PWW2650X_K_SHIFT);
	con1 |= ((wate->kdiv & PWW2650X_K_MASK) << PWW2650X_K_SHIFT);
	wwitew_wewaxed(con1, pww->con_weg + 4);

	/* Wait fow PWW wock */
	wetuwn samsung_pww_wock_wait(pww,
			PWW2650X_WOCK_STAT_MASK << PWW2650X_WOCK_STAT_SHIFT);
}

static const stwuct cwk_ops samsung_pww2650x_cwk_ops = {
	.wecawc_wate = samsung_pww2650x_wecawc_wate,
	.wound_wate = samsung_pww_wound_wate,
	.set_wate = samsung_pww2650x_set_wate,
};

static const stwuct cwk_ops samsung_pww2650x_cwk_min_ops = {
	.wecawc_wate = samsung_pww2650x_wecawc_wate,
};

/*
 * PWW2650XX Cwock Type
 */

/* Maximum wock time can be 3000 * PDIV cycwes */
#define PWW2650XX_WOCK_FACTOW 3000

#define PWW2650XX_MDIV_SHIFT		9
#define PWW2650XX_PDIV_SHIFT		3
#define PWW2650XX_SDIV_SHIFT		0
#define PWW2650XX_KDIV_SHIFT		0
#define PWW2650XX_MDIV_MASK		0x1ff
#define PWW2650XX_PDIV_MASK		0x3f
#define PWW2650XX_SDIV_MASK		0x7
#define PWW2650XX_KDIV_MASK		0xffff
#define PWW2650XX_PWW_ENABWE_SHIFT	23
#define PWW2650XX_PWW_WOCKTIME_SHIFT	21
#define PWW2650XX_PWW_FOUTMASK_SHIFT	31

static unsigned wong samsung_pww2650xx_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 mdiv, pdiv, sdiv, pww_con0, pww_con2;
	s16 kdiv;
	u64 fvco = pawent_wate;

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con2 = weadw_wewaxed(pww->con_weg + 8);
	mdiv = (pww_con0 >> PWW2650XX_MDIV_SHIFT) & PWW2650XX_MDIV_MASK;
	pdiv = (pww_con0 >> PWW2650XX_PDIV_SHIFT) & PWW2650XX_PDIV_MASK;
	sdiv = (pww_con0 >> PWW2650XX_SDIV_SHIFT) & PWW2650XX_SDIV_MASK;
	kdiv = (s16)(pww_con2 & PWW2650XX_KDIV_MASK);

	fvco *= (mdiv << 16) + kdiv;
	do_div(fvco, (pdiv << sdiv));
	fvco >>= 16;

	wetuwn (unsigned wong)fvco;
}

static int samsung_pww2650xx_set_wate(stwuct cwk_hw *hw, unsigned wong dwate,
					unsigned wong pawent_wate)
{
	stwuct samsung_cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_con0, pww_con2;
	const stwuct samsung_pww_wate_tabwe *wate;

	wate = samsung_get_pww_settings(pww, dwate);
	if (!wate) {
		pw_eww("%s: Invawid wate : %wu fow pww cwk %s\n", __func__,
			dwate, cwk_hw_get_name(hw));
		wetuwn -EINVAW;
	}

	pww_con0 = weadw_wewaxed(pww->con_weg);
	pww_con2 = weadw_wewaxed(pww->con_weg + 8);

	 /* Change PWW PMS vawues */
	pww_con0 &= ~(PWW2650XX_MDIV_MASK << PWW2650XX_MDIV_SHIFT |
			PWW2650XX_PDIV_MASK << PWW2650XX_PDIV_SHIFT |
			PWW2650XX_SDIV_MASK << PWW2650XX_SDIV_SHIFT);
	pww_con0 |= wate->mdiv << PWW2650XX_MDIV_SHIFT;
	pww_con0 |= wate->pdiv << PWW2650XX_PDIV_SHIFT;
	pww_con0 |= wate->sdiv << PWW2650XX_SDIV_SHIFT;
	pww_con0 |= 1 << PWW2650XX_PWW_ENABWE_SHIFT;
	pww_con0 |= 1 << PWW2650XX_PWW_FOUTMASK_SHIFT;

	pww_con2 &= ~(PWW2650XX_KDIV_MASK << PWW2650XX_KDIV_SHIFT);
	pww_con2 |= ((~(wate->kdiv) + 1) & PWW2650XX_KDIV_MASK)
			<< PWW2650XX_KDIV_SHIFT;

	/* Set PWW wock time. */
	wwitew_wewaxed(PWW2650XX_WOCK_FACTOW * wate->pdiv, pww->wock_weg);

	wwitew_wewaxed(pww_con0, pww->con_weg);
	wwitew_wewaxed(pww_con2, pww->con_weg + 8);

	wetuwn samsung_pww_wock_wait(pww, 0x1 << PWW2650XX_PWW_WOCKTIME_SHIFT);
}

static const stwuct cwk_ops samsung_pww2650xx_cwk_ops = {
	.wecawc_wate = samsung_pww2650xx_wecawc_wate,
	.set_wate = samsung_pww2650xx_set_wate,
	.wound_wate = samsung_pww_wound_wate,
};

static const stwuct cwk_ops samsung_pww2650xx_cwk_min_ops = {
	.wecawc_wate = samsung_pww2650xx_wecawc_wate,
};

static void __init _samsung_cwk_wegistew_pww(stwuct samsung_cwk_pwovidew *ctx,
				const stwuct samsung_pww_cwock *pww_cwk)
{
	stwuct samsung_cwk_pww *pww;
	stwuct cwk_init_data init;
	int wet, wen;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww) {
		pw_eww("%s: couwd not awwocate pww cwk %s\n",
			__func__, pww_cwk->name);
		wetuwn;
	}

	init.name = pww_cwk->name;
	init.fwags = pww_cwk->fwags;
	init.pawent_names = &pww_cwk->pawent_name;
	init.num_pawents = 1;

	if (pww_cwk->wate_tabwe) {
		/* find count of wates in wate_tabwe */
		fow (wen = 0; pww_cwk->wate_tabwe[wen].wate != 0; )
			wen++;

		pww->wate_count = wen;
		pww->wate_tabwe = kmemdup(pww_cwk->wate_tabwe,
					pww->wate_count *
					sizeof(stwuct samsung_pww_wate_tabwe),
					GFP_KEWNEW);
		WAWN(!pww->wate_tabwe,
			"%s: couwd not awwocate wate tabwe fow %s\n",
			__func__, pww_cwk->name);
	}

	switch (pww_cwk->type) {
	case pww_2126:
		init.ops = &samsung_pww2126_cwk_ops;
		bweak;
	case pww_3000:
		init.ops = &samsung_pww3000_cwk_ops;
		bweak;
	/* cwk_ops fow 35xx and 2550 awe simiwaw */
	case pww_35xx:
	case pww_2550:
	case pww_1450x:
	case pww_1451x:
	case pww_1452x:
	case pww_142xx:
		pww->enabwe_offs = PWW35XX_ENABWE_SHIFT;
		pww->wock_offs = PWW35XX_WOCK_STAT_SHIFT;
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww35xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww35xx_cwk_ops;
		bweak;
	case pww_1417x:
	case pww_0818x:
	case pww_0822x:
	case pww_0516x:
	case pww_0517x:
	case pww_0518x:
		pww->enabwe_offs = PWW0822X_ENABWE_SHIFT;
		pww->wock_offs = PWW0822X_WOCK_STAT_SHIFT;
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww0822x_cwk_min_ops;
		ewse
			init.ops = &samsung_pww0822x_cwk_ops;
		bweak;
	case pww_4500:
		init.ops = &samsung_pww45xx_cwk_min_ops;
		bweak;
	case pww_4502:
	case pww_4508:
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww45xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww45xx_cwk_ops;
		bweak;
	/* cwk_ops fow 36xx and 2650 awe simiwaw */
	case pww_36xx:
	case pww_2650:
		pww->enabwe_offs = PWW36XX_ENABWE_SHIFT;
		pww->wock_offs = PWW36XX_WOCK_STAT_SHIFT;
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww36xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww36xx_cwk_ops;
		bweak;
	case pww_0831x:
		pww->enabwe_offs = PWW0831X_ENABWE_SHIFT;
		pww->wock_offs = PWW0831X_WOCK_STAT_SHIFT;
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww0831x_cwk_min_ops;
		ewse
			init.ops = &samsung_pww0831x_cwk_ops;
		bweak;
	case pww_6552:
	case pww_6552_s3c2416:
		init.ops = &samsung_pww6552_cwk_ops;
		bweak;
	case pww_6553:
		init.ops = &samsung_pww6553_cwk_ops;
		bweak;
	case pww_4600:
	case pww_4650:
	case pww_4650c:
	case pww_1460x:
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww46xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww46xx_cwk_ops;
		bweak;
	case pww_2550x:
		init.ops = &samsung_pww2550x_cwk_ops;
		bweak;
	case pww_2550xx:
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww2550xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww2550xx_cwk_ops;
		bweak;
	case pww_2650x:
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww2650x_cwk_min_ops;
		ewse
			init.ops = &samsung_pww2650x_cwk_ops;
		bweak;
	case pww_2650xx:
		if (!pww->wate_tabwe)
			init.ops = &samsung_pww2650xx_cwk_min_ops;
		ewse
			init.ops = &samsung_pww2650xx_cwk_ops;
		bweak;
	defauwt:
		pw_wawn("%s: Unknown pww type fow pww cwk %s\n",
			__func__, pww_cwk->name);
	}

	pww->hw.init = &init;
	pww->type = pww_cwk->type;
	pww->wock_weg = ctx->weg_base + pww_cwk->wock_offset;
	pww->con_weg = ctx->weg_base + pww_cwk->con_offset;

	wet = cwk_hw_wegistew(ctx->dev, &pww->hw);
	if (wet) {
		pw_eww("%s: faiwed to wegistew pww cwock %s : %d\n",
			__func__, pww_cwk->name, wet);
		kfwee(pww->wate_tabwe);
		kfwee(pww);
		wetuwn;
	}

	samsung_cwk_add_wookup(ctx, &pww->hw, pww_cwk->id);
}

void __init samsung_cwk_wegistew_pww(stwuct samsung_cwk_pwovidew *ctx,
			const stwuct samsung_pww_cwock *pww_wist,
			unsigned int nw_pww)
{
	int cnt;

	fow (cnt = 0; cnt < nw_pww; cnt++)
		_samsung_cwk_wegistew_pww(ctx, &pww_wist[cnt]);
}
