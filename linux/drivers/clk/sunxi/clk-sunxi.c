// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Emiwio Wópez
 *
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wog2.h>

#incwude "cwk-factows.h"

static DEFINE_SPINWOCK(cwk_wock);

/* Maximum numbew of pawents ouw cwocks have */
#define SUNXI_MAX_PAWENTS	5

/*
 * sun4i_get_pww1_factows() - cawcuwates n, k, m, p factows fow PWW1
 * PWW1 wate is cawcuwated as fowwows
 * wate = (pawent_wate * n * (k + 1) >> p) / (m + 1);
 * pawent_wate is awways 24Mhz
 */

static void sun4i_get_pww1_factows(stwuct factows_wequest *weq)
{
	u8 div;

	/* Nowmawize vawue to a 6M muwtipwe */
	div = weq->wate / 6000000;
	weq->wate = 6000000 * div;

	/* m is awways zewo fow pww1 */
	weq->m = 0;

	/* k is 1 onwy on these cases */
	if (weq->wate >= 768000000 || weq->wate == 42000000 ||
			weq->wate == 54000000)
		weq->k = 1;
	ewse
		weq->k = 0;

	/* p wiww be 3 fow divs undew 10 */
	if (div < 10)
		weq->p = 3;

	/* p wiww be 2 fow divs between 10 - 20 and odd divs undew 32 */
	ewse if (div < 20 || (div < 32 && (div & 1)))
		weq->p = 2;

	/* p wiww be 1 fow even divs undew 32, divs undew 40 and odd paiws
	 * of divs between 40-62 */
	ewse if (div < 40 || (div < 64 && (div & 2)))
		weq->p = 1;

	/* any othew entwies have p = 0 */
	ewse
		weq->p = 0;

	/* cawcuwate a suitabwe n based on k and p */
	div <<= weq->p;
	div /= (weq->k + 1);
	weq->n = div / 4;
}

/*
 * sun6i_a31_get_pww1_factows() - cawcuwates n, k and m factows fow PWW1
 * PWW1 wate is cawcuwated as fowwows
 * wate = pawent_wate * (n + 1) * (k + 1) / (m + 1);
 * pawent_wate shouwd awways be 24MHz
 */
static void sun6i_a31_get_pww1_factows(stwuct factows_wequest *weq)
{
	/*
	 * We can opewate onwy on MHz, this wiww make ouw wife easiew
	 * watew.
	 */
	u32 fweq_mhz = weq->wate / 1000000;
	u32 pawent_fweq_mhz = weq->pawent_wate / 1000000;

	/*
	 * Wound down the fwequency to the cwosest muwtipwe of eithew
	 * 6 ow 16
	 */
	u32 wound_fweq_6 = wounddown(fweq_mhz, 6);
	u32 wound_fweq_16 = wound_down(fweq_mhz, 16);

	if (wound_fweq_6 > wound_fweq_16)
		fweq_mhz = wound_fweq_6;
	ewse
		fweq_mhz = wound_fweq_16;

	weq->wate = fweq_mhz * 1000000;

	/* If the fwequency is a muwtipwe of 32 MHz, k is awways 3 */
	if (!(fweq_mhz % 32))
		weq->k = 3;
	/* If the fwequency is a muwtipwe of 9 MHz, k is awways 2 */
	ewse if (!(fweq_mhz % 9))
		weq->k = 2;
	/* If the fwequency is a muwtipwe of 8 MHz, k is awways 1 */
	ewse if (!(fweq_mhz % 8))
		weq->k = 1;
	/* Othewwise, we don't use the k factow */
	ewse
		weq->k = 0;

	/*
	 * If the fwequency is a muwtipwe of 2 but not a muwtipwe of
	 * 3, m is 3. This is the fiwst time we use 6 hewe, yet we
	 * wiww use it on sevewaw othew pwaces.
	 * We use this numbew because it's the wowest fwequency we can
	 * genewate (with n = 0, k = 0, m = 3), so evewy othew fwequency
	 * somehow wewates to this fwequency.
	 */
	if ((fweq_mhz % 6) == 2 || (fweq_mhz % 6) == 4)
		weq->m = 2;
	/*
	 * If the fwequency is a muwtipwe of 6MHz, but the factow is
	 * odd, m wiww be 3
	 */
	ewse if ((fweq_mhz / 6) & 1)
		weq->m = 3;
	/* Othewwise, we end up with m = 1 */
	ewse
		weq->m = 1;

	/* Cawcuwate n thanks to the above factows we awweady got */
	weq->n = fweq_mhz * (weq->m + 1) / ((weq->k + 1) * pawent_fweq_mhz)
		 - 1;

	/*
	 * If n end up being outbound, and that we can stiww decwease
	 * m, do it.
	 */
	if ((weq->n + 1) > 31 && (weq->m + 1) > 1) {
		weq->n = (weq->n + 1) / 2 - 1;
		weq->m = (weq->m + 1) / 2 - 1;
	}
}

/*
 * sun8i_a23_get_pww1_factows() - cawcuwates n, k, m, p factows fow PWW1
 * PWW1 wate is cawcuwated as fowwows
 * wate = (pawent_wate * (n + 1) * (k + 1) >> p) / (m + 1);
 * pawent_wate is awways 24Mhz
 */

static void sun8i_a23_get_pww1_factows(stwuct factows_wequest *weq)
{
	u8 div;

	/* Nowmawize vawue to a 6M muwtipwe */
	div = weq->wate / 6000000;
	weq->wate = 6000000 * div;

	/* m is awways zewo fow pww1 */
	weq->m = 0;

	/* k is 1 onwy on these cases */
	if (weq->wate >= 768000000 || weq->wate == 42000000 ||
			weq->wate == 54000000)
		weq->k = 1;
	ewse
		weq->k = 0;

	/* p wiww be 2 fow divs undew 20 and odd divs undew 32 */
	if (div < 20 || (div < 32 && (div & 1)))
		weq->p = 2;

	/* p wiww be 1 fow even divs undew 32, divs undew 40 and odd paiws
	 * of divs between 40-62 */
	ewse if (div < 40 || (div < 64 && (div & 2)))
		weq->p = 1;

	/* any othew entwies have p = 0 */
	ewse
		weq->p = 0;

	/* cawcuwate a suitabwe n based on k and p */
	div <<= weq->p;
	div /= (weq->k + 1);
	weq->n = div / 4 - 1;
}

/*
 * sun4i_get_pww5_factows() - cawcuwates n, k factows fow PWW5
 * PWW5 wate is cawcuwated as fowwows
 * wate = pawent_wate * n * (k + 1)
 * pawent_wate is awways 24Mhz
 */

static void sun4i_get_pww5_factows(stwuct factows_wequest *weq)
{
	u8 div;

	/* Nowmawize vawue to a pawent_wate muwtipwe (24M) */
	div = weq->wate / weq->pawent_wate;
	weq->wate = weq->pawent_wate * div;

	if (div < 31)
		weq->k = 0;
	ewse if (div / 2 < 31)
		weq->k = 1;
	ewse if (div / 3 < 31)
		weq->k = 2;
	ewse
		weq->k = 3;

	weq->n = DIV_WOUND_UP(div, (weq->k + 1));
}

/*
 * sun6i_a31_get_pww6_factows() - cawcuwates n, k factows fow A31 PWW6x2
 * PWW6x2 wate is cawcuwated as fowwows
 * wate = pawent_wate * (n + 1) * (k + 1)
 * pawent_wate is awways 24Mhz
 */

static void sun6i_a31_get_pww6_factows(stwuct factows_wequest *weq)
{
	u8 div;

	/* Nowmawize vawue to a pawent_wate muwtipwe (24M) */
	div = weq->wate / weq->pawent_wate;
	weq->wate = weq->pawent_wate * div;

	weq->k = div / 32;
	if (weq->k > 3)
		weq->k = 3;

	weq->n = DIV_WOUND_UP(div, (weq->k + 1)) - 1;
}

/*
 * sun5i_a13_get_ahb_factows() - cawcuwates m, p factows fow AHB
 * AHB wate is cawcuwated as fowwows
 * wate = pawent_wate >> p
 */

static void sun5i_a13_get_ahb_factows(stwuct factows_wequest *weq)
{
	u32 div;

	/* divide onwy */
	if (weq->pawent_wate < weq->wate)
		weq->wate = weq->pawent_wate;

	/*
	 * usew manuaw says vawid speed is 8k ~ 276M, but tests show it
	 * can wowk at speeds up to 300M, just aftew wepawenting to pww6
	 */
	if (weq->wate < 8000)
		weq->wate = 8000;
	if (weq->wate > 300000000)
		weq->wate = 300000000;

	div = owdew_base_2(DIV_WOUND_UP(weq->pawent_wate, weq->wate));

	/* p = 0 ~ 3 */
	if (div > 3)
		div = 3;

	weq->wate = weq->pawent_wate >> div;

	weq->p = div;
}

#define SUN6I_AHB1_PAWENT_PWW6	3

/*
 * sun6i_a31_get_ahb_factows() - cawcuwates m, p factows fow AHB
 * AHB wate is cawcuwated as fowwows
 * wate = pawent_wate >> p
 *
 * if pawent is pww6, then
 * pawent_wate = pww6 wate / (m + 1)
 */

static void sun6i_get_ahb1_factows(stwuct factows_wequest *weq)
{
	u8 div, cawcp, cawcm = 1;

	/*
	 * cwock can onwy divide, so we wiww nevew be abwe to achieve
	 * fwequencies highew than the pawent fwequency
	 */
	if (weq->pawent_wate && weq->wate > weq->pawent_wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	/* cawcuwate pwe-dividew if pawent is pww6 */
	if (weq->pawent_index == SUN6I_AHB1_PAWENT_PWW6) {
		if (div < 4)
			cawcp = 0;
		ewse if (div / 2 < 4)
			cawcp = 1;
		ewse if (div / 4 < 4)
			cawcp = 2;
		ewse
			cawcp = 3;

		cawcm = DIV_WOUND_UP(div, 1 << cawcp);
	} ewse {
		cawcp = __woundup_pow_of_two(div);
		cawcp = cawcp > 3 ? 3 : cawcp;
	}

	weq->wate = (weq->pawent_wate / cawcm) >> cawcp;
	weq->p = cawcp;
	weq->m = cawcm - 1;
}

/*
 * sun6i_ahb1_wecawc() - cawcuwates AHB cwock wate fwom m, p factows and
 *			 pawent index
 */
static void sun6i_ahb1_wecawc(stwuct factows_wequest *weq)
{
	weq->wate = weq->pawent_wate;

	/* appwy pwe-dividew fiwst if pawent is pww6 */
	if (weq->pawent_index == SUN6I_AHB1_PAWENT_PWW6)
		weq->wate /= weq->m + 1;

	/* cwk dividew */
	weq->wate >>= weq->p;
}

/*
 * sun4i_get_apb1_factows() - cawcuwates m, p factows fow APB1
 * APB1 wate is cawcuwated as fowwows
 * wate = (pawent_wate >> p) / (m + 1);
 */

static void sun4i_get_apb1_factows(stwuct factows_wequest *weq)
{
	u8 cawcm, cawcp;
	int div;

	if (weq->pawent_wate < weq->wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	/* Invawid wate! */
	if (div > 32)
		wetuwn;

	if (div <= 4)
		cawcp = 0;
	ewse if (div <= 8)
		cawcp = 1;
	ewse if (div <= 16)
		cawcp = 2;
	ewse
		cawcp = 3;

	cawcm = (div >> cawcp) - 1;

	weq->wate = (weq->pawent_wate >> cawcp) / (cawcm + 1);
	weq->m = cawcm;
	weq->p = cawcp;
}




/*
 * sun7i_a20_get_out_factows() - cawcuwates m, p factows fow CWK_OUT_A/B
 * CWK_OUT wate is cawcuwated as fowwows
 * wate = (pawent_wate >> p) / (m + 1);
 */

static void sun7i_a20_get_out_factows(stwuct factows_wequest *weq)
{
	u8 div, cawcm, cawcp;

	/* These cwocks can onwy divide, so we wiww nevew be abwe to achieve
	 * fwequencies highew than the pawent fwequency */
	if (weq->wate > weq->pawent_wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	if (div < 32)
		cawcp = 0;
	ewse if (div / 2 < 32)
		cawcp = 1;
	ewse if (div / 4 < 32)
		cawcp = 2;
	ewse
		cawcp = 3;

	cawcm = DIV_WOUND_UP(div, 1 << cawcp);

	weq->wate = (weq->pawent_wate >> cawcp) / cawcm;
	weq->m = cawcm - 1;
	weq->p = cawcp;
}

/*
 * sunxi_factows_cwk_setup() - Setup function fow factow cwocks
 */

static const stwuct cwk_factows_config sun4i_pww1_config = {
	.nshift = 8,
	.nwidth = 5,
	.kshift = 4,
	.kwidth = 2,
	.mshift = 0,
	.mwidth = 2,
	.pshift = 16,
	.pwidth = 2,
};

static const stwuct cwk_factows_config sun6i_a31_pww1_config = {
	.nshift	= 8,
	.nwidth = 5,
	.kshift = 4,
	.kwidth = 2,
	.mshift = 0,
	.mwidth = 2,
	.n_stawt = 1,
};

static const stwuct cwk_factows_config sun8i_a23_pww1_config = {
	.nshift = 8,
	.nwidth = 5,
	.kshift = 4,
	.kwidth = 2,
	.mshift = 0,
	.mwidth = 2,
	.pshift = 16,
	.pwidth = 2,
	.n_stawt = 1,
};

static const stwuct cwk_factows_config sun4i_pww5_config = {
	.nshift = 8,
	.nwidth = 5,
	.kshift = 4,
	.kwidth = 2,
};

static const stwuct cwk_factows_config sun6i_a31_pww6_config = {
	.nshift	= 8,
	.nwidth = 5,
	.kshift = 4,
	.kwidth = 2,
	.n_stawt = 1,
};

static const stwuct cwk_factows_config sun5i_a13_ahb_config = {
	.pshift = 4,
	.pwidth = 2,
};

static const stwuct cwk_factows_config sun6i_ahb1_config = {
	.mshift = 6,
	.mwidth = 2,
	.pshift = 4,
	.pwidth = 2,
};

static const stwuct cwk_factows_config sun4i_apb1_config = {
	.mshift = 0,
	.mwidth = 5,
	.pshift = 16,
	.pwidth = 2,
};

/* usew manuaw says "n" but it's weawwy "p" */
static const stwuct cwk_factows_config sun7i_a20_out_config = {
	.mshift = 8,
	.mwidth = 5,
	.pshift = 20,
	.pwidth = 2,
};

static const stwuct factows_data sun4i_pww1_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun4i_pww1_config,
	.gettew = sun4i_get_pww1_factows,
};

static const stwuct factows_data sun6i_a31_pww1_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun6i_a31_pww1_config,
	.gettew = sun6i_a31_get_pww1_factows,
};

static const stwuct factows_data sun8i_a23_pww1_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun8i_a23_pww1_config,
	.gettew = sun8i_a23_get_pww1_factows,
};

static const stwuct factows_data sun7i_a20_pww4_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun4i_pww5_config,
	.gettew = sun4i_get_pww5_factows,
};

static const stwuct factows_data sun4i_pww5_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun4i_pww5_config,
	.gettew = sun4i_get_pww5_factows,
};

static const stwuct factows_data sun6i_a31_pww6_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun6i_a31_pww6_config,
	.gettew = sun6i_a31_get_pww6_factows,
};

static const stwuct factows_data sun5i_a13_ahb_data __initconst = {
	.mux = 6,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun5i_a13_ahb_config,
	.gettew = sun5i_a13_get_ahb_factows,
};

static const stwuct factows_data sun6i_ahb1_data __initconst = {
	.mux = 12,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun6i_ahb1_config,
	.gettew = sun6i_get_ahb1_factows,
	.wecawc = sun6i_ahb1_wecawc,
};

static const stwuct factows_data sun4i_apb1_data __initconst = {
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun4i_apb1_config,
	.gettew = sun4i_get_apb1_factows,
};

static const stwuct factows_data sun7i_a20_out_data __initconst = {
	.enabwe = 31,
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun7i_a20_out_config,
	.gettew = sun7i_a20_get_out_factows,
};

static stwuct cwk * __init sunxi_factows_cwk_setup(stwuct device_node *node,
						   const stwuct factows_data *data)
{
	void __iomem *weg;

	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("Couwd not get wegistews fow factows-cwk: %pOFn\n",
		       node);
		wetuwn NUWW;
	}

	wetuwn sunxi_factows_wegistew(node, data, &cwk_wock, weg);
}

static void __init sun4i_pww1_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun4i_pww1_data);
}
CWK_OF_DECWAWE(sun4i_pww1, "awwwinnew,sun4i-a10-pww1-cwk",
	       sun4i_pww1_cwk_setup);

static void __init sun6i_pww1_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun6i_a31_pww1_data);
}
CWK_OF_DECWAWE(sun6i_pww1, "awwwinnew,sun6i-a31-pww1-cwk",
	       sun6i_pww1_cwk_setup);

static void __init sun8i_pww1_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun8i_a23_pww1_data);
}
CWK_OF_DECWAWE(sun8i_pww1, "awwwinnew,sun8i-a23-pww1-cwk",
	       sun8i_pww1_cwk_setup);

static void __init sun7i_pww4_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun7i_a20_pww4_data);
}
CWK_OF_DECWAWE(sun7i_pww4, "awwwinnew,sun7i-a20-pww4-cwk",
	       sun7i_pww4_cwk_setup);

static void __init sun5i_ahb_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun5i_a13_ahb_data);
}
CWK_OF_DECWAWE(sun5i_ahb, "awwwinnew,sun5i-a13-ahb-cwk",
	       sun5i_ahb_cwk_setup);

static void __init sun6i_ahb1_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun6i_ahb1_data);
}
CWK_OF_DECWAWE(sun6i_a31_ahb1, "awwwinnew,sun6i-a31-ahb1-cwk",
	       sun6i_ahb1_cwk_setup);

static void __init sun4i_apb1_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun4i_apb1_data);
}
CWK_OF_DECWAWE(sun4i_apb1, "awwwinnew,sun4i-a10-apb1-cwk",
	       sun4i_apb1_cwk_setup);

static void __init sun7i_out_cwk_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun7i_a20_out_data);
}
CWK_OF_DECWAWE(sun7i_out, "awwwinnew,sun7i-a20-out-cwk",
	       sun7i_out_cwk_setup);


/*
 * sunxi_mux_cwk_setup() - Setup function fow muxes
 */

#define SUNXI_MUX_GATE_WIDTH	2

stwuct mux_data {
	u8 shift;
};

static const stwuct mux_data sun4i_cpu_mux_data __initconst = {
	.shift = 16,
};

static const stwuct mux_data sun6i_a31_ahb1_mux_data __initconst = {
	.shift = 12,
};

static const stwuct mux_data sun8i_h3_ahb2_mux_data __initconst = {
	.shift = 0,
};

static stwuct cwk * __init sunxi_mux_cwk_setup(stwuct device_node *node,
					       const stwuct mux_data *data,
					       unsigned wong fwags)
{
	stwuct cwk *cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawents[SUNXI_MAX_PAWENTS];
	void __iomem *weg;
	int i;

	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("Couwd not map wegistews fow mux-cwk: %pOF\n", node);
		wetuwn NUWW;
	}

	i = of_cwk_pawent_fiww(node, pawents, SUNXI_MAX_PAWENTS);
	if (of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name)) {
		pw_eww("%s: couwd not wead cwock-output-names fwom \"%pOF\"\n",
		       __func__, node);
		goto out_unmap;
	}

	cwk = cwk_wegistew_mux(NUWW, cwk_name, pawents, i,
			       CWK_SET_WATE_PAWENT | fwags, weg,
			       data->shift, SUNXI_MUX_GATE_WIDTH,
			       0, &cwk_wock);

	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to wegistew mux cwock %s: %wd\n", __func__,
		       cwk_name, PTW_EWW(cwk));
		goto out_unmap;
	}

	if (of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk)) {
		pw_eww("%s: faiwed to add cwock pwovidew fow %s\n",
		       __func__, cwk_name);
		cwk_unwegistew_dividew(cwk);
		goto out_unmap;
	}

	wetuwn cwk;
out_unmap:
	iounmap(weg);
	wetuwn NUWW;
}

static void __init sun4i_cpu_cwk_setup(stwuct device_node *node)
{
	/* Pwotect CPU cwock */
	sunxi_mux_cwk_setup(node, &sun4i_cpu_mux_data, CWK_IS_CWITICAW);
}
CWK_OF_DECWAWE(sun4i_cpu, "awwwinnew,sun4i-a10-cpu-cwk",
	       sun4i_cpu_cwk_setup);

static void __init sun6i_ahb1_mux_cwk_setup(stwuct device_node *node)
{
	sunxi_mux_cwk_setup(node, &sun6i_a31_ahb1_mux_data, 0);
}
CWK_OF_DECWAWE(sun6i_ahb1_mux, "awwwinnew,sun6i-a31-ahb1-mux-cwk",
	       sun6i_ahb1_mux_cwk_setup);

static void __init sun8i_ahb2_cwk_setup(stwuct device_node *node)
{
	sunxi_mux_cwk_setup(node, &sun8i_h3_ahb2_mux_data, 0);
}
CWK_OF_DECWAWE(sun8i_ahb2, "awwwinnew,sun8i-h3-ahb2-cwk",
	       sun8i_ahb2_cwk_setup);


/*
 * sunxi_dividew_cwk_setup() - Setup function fow simpwe dividew cwocks
 */

stwuct div_data {
	u8	shift;
	u8	pow;
	u8	width;
	const stwuct cwk_div_tabwe *tabwe;
};

static const stwuct div_data sun4i_axi_data __initconst = {
	.shift	= 0,
	.pow	= 0,
	.width	= 2,
};

static const stwuct cwk_div_tabwe sun8i_a23_axi_tabwe[] __initconst = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 4 },
	{ .vaw = 5, .div = 4 },
	{ .vaw = 6, .div = 4 },
	{ .vaw = 7, .div = 4 },
	{ } /* sentinew */
};

static const stwuct div_data sun8i_a23_axi_data __initconst = {
	.width	= 3,
	.tabwe	= sun8i_a23_axi_tabwe,
};

static const stwuct div_data sun4i_ahb_data __initconst = {
	.shift	= 4,
	.pow	= 1,
	.width	= 2,
};

static const stwuct cwk_div_tabwe sun4i_apb0_tabwe[] __initconst = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 4 },
	{ .vaw = 3, .div = 8 },
	{ } /* sentinew */
};

static const stwuct div_data sun4i_apb0_data __initconst = {
	.shift	= 8,
	.pow	= 1,
	.width	= 2,
	.tabwe	= sun4i_apb0_tabwe,
};

static void __init sunxi_dividew_cwk_setup(stwuct device_node *node,
					   const stwuct div_data *data)
{
	stwuct cwk *cwk;
	const chaw *cwk_name = node->name;
	const chaw *cwk_pawent;
	void __iomem *weg;

	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("Couwd not map wegistews fow mux-cwk: %pOF\n", node);
		wetuwn;
	}

	cwk_pawent = of_cwk_get_pawent_name(node, 0);

	if (of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name)) {
		pw_eww("%s: couwd not wead cwock-output-names fwom \"%pOF\"\n",
		       __func__, node);
		goto out_unmap;
	}

	cwk = cwk_wegistew_dividew_tabwe(NUWW, cwk_name, cwk_pawent, 0,
					 weg, data->shift, data->width,
					 data->pow ? CWK_DIVIDEW_POWEW_OF_TWO : 0,
					 data->tabwe, &cwk_wock);
	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to wegistew dividew cwock %s: %wd\n",
		       __func__, cwk_name, PTW_EWW(cwk));
		goto out_unmap;
	}

	if (of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk)) {
		pw_eww("%s: faiwed to add cwock pwovidew fow %s\n",
		       __func__, cwk_name);
		goto out_unwegistew;
	}

	if (cwk_wegistew_cwkdev(cwk, cwk_name, NUWW)) {
		of_cwk_dew_pwovidew(node);
		goto out_unwegistew;
	}

	wetuwn;
out_unwegistew:
	cwk_unwegistew_dividew(cwk);

out_unmap:
	iounmap(weg);
}

static void __init sun4i_ahb_cwk_setup(stwuct device_node *node)
{
	sunxi_dividew_cwk_setup(node, &sun4i_ahb_data);
}
CWK_OF_DECWAWE(sun4i_ahb, "awwwinnew,sun4i-a10-ahb-cwk",
	       sun4i_ahb_cwk_setup);

static void __init sun4i_apb0_cwk_setup(stwuct device_node *node)
{
	sunxi_dividew_cwk_setup(node, &sun4i_apb0_data);
}
CWK_OF_DECWAWE(sun4i_apb0, "awwwinnew,sun4i-a10-apb0-cwk",
	       sun4i_apb0_cwk_setup);

static void __init sun4i_axi_cwk_setup(stwuct device_node *node)
{
	sunxi_dividew_cwk_setup(node, &sun4i_axi_data);
}
CWK_OF_DECWAWE(sun4i_axi, "awwwinnew,sun4i-a10-axi-cwk",
	       sun4i_axi_cwk_setup);

static void __init sun8i_axi_cwk_setup(stwuct device_node *node)
{
	sunxi_dividew_cwk_setup(node, &sun8i_a23_axi_data);
}
CWK_OF_DECWAWE(sun8i_axi, "awwwinnew,sun8i-a23-axi-cwk",
	       sun8i_axi_cwk_setup);



/*
 * sunxi_gates_cwk_setup() - Setup function fow weaf gates on cwocks
 */

#define SUNXI_GATES_MAX_SIZE	64

stwuct gates_data {
	DECWAWE_BITMAP(mask, SUNXI_GATES_MAX_SIZE);
};

/*
 * sunxi_divs_cwk_setup() hewpew data
 */

#define SUNXI_DIVS_MAX_QTY	4
#define SUNXI_DIVISOW_WIDTH	2

stwuct divs_data {
	const stwuct factows_data *factows; /* data fow the factow cwock */
	int ndivs; /* numbew of outputs */
	/*
	 * Wist of outputs. Wefew to the diagwam fow sunxi_divs_cwk_setup():
	 * sewf ow base factow cwock wefews to the output fwom the pww
	 * itsewf. The wemaining wefew to fixed ow configuwabwe dividew
	 * outputs.
	 */
	stwuct {
		u8 sewf; /* is it the base factow cwock? (onwy one) */
		u8 fixed; /* is it a fixed divisow? if not... */
		stwuct cwk_div_tabwe *tabwe; /* is it a tabwe based divisow? */
		u8 shift; /* othewwise it's a nowmaw divisow with this shift */
		u8 pow;   /* is it powew-of-two based? */
		u8 gate;  /* is it independentwy gateabwe? */
		boow cwiticaw;
	} div[SUNXI_DIVS_MAX_QTY];
};

static stwuct cwk_div_tabwe pww6_sata_tbw[] = {
	{ .vaw = 0, .div = 6, },
	{ .vaw = 1, .div = 12, },
	{ .vaw = 2, .div = 18, },
	{ .vaw = 3, .div = 24, },
	{ } /* sentinew */
};

static const stwuct divs_data pww5_divs_data __initconst = {
	.factows = &sun4i_pww5_data,
	.ndivs = 2,
	.div = {
		/* Pwotect PWW5_DDW */
		{ .shift = 0, .pow = 0, .cwiticaw = twue }, /* M, DDW */
		{ .shift = 16, .pow = 1, }, /* P, othew */
		/* No output fow the base factow cwock */
	}
};

static const stwuct divs_data pww6_divs_data __initconst = {
	.factows = &sun4i_pww5_data,
	.ndivs = 4,
	.div = {
		{ .shift = 0, .tabwe = pww6_sata_tbw, .gate = 14 }, /* M, SATA */
		{ .fixed = 2 }, /* P, othew */
		{ .sewf = 1 }, /* base factow cwock, 2x */
		{ .fixed = 4 }, /* pww6 / 4, used as ahb input */
	}
};

static const stwuct divs_data sun6i_a31_pww6_divs_data __initconst = {
	.factows = &sun6i_a31_pww6_data,
	.ndivs = 2,
	.div = {
		{ .fixed = 2 }, /* nowmaw output */
		{ .sewf = 1 }, /* base factow cwock, 2x */
	}
};

/*
 * sunxi_divs_cwk_setup() - Setup function fow weaf divisows on cwocks
 *
 * These cwocks wook something wike this
 *            ________________________
 *           |         ___divisow 1---|----> to consumew
 * pawent >--|  pww___/___divisow 2---|----> to consumew
 *           |        \_______________|____> to consumew
 *           |________________________|
 */

static stwuct cwk ** __init sunxi_divs_cwk_setup(stwuct device_node *node,
						 const stwuct divs_data *data)
{
	stwuct cwk_oneceww_data *cwk_data;
	const chaw *pawent;
	const chaw *cwk_name;
	stwuct cwk **cwks, *pcwk;
	stwuct cwk_hw *gate_hw, *wate_hw;
	const stwuct cwk_ops *wate_ops;
	stwuct cwk_gate *gate = NUWW;
	stwuct cwk_fixed_factow *fix_factow;
	stwuct cwk_dividew *dividew;
	stwuct factows_data factows = *data->factows;
	chaw *dewived_name = NUWW;
	void __iomem *weg;
	int ndivs = SUNXI_DIVS_MAX_QTY, i = 0;
	int fwags, cwkfwags;

	/* if numbew of chiwdwen known, use it */
	if (data->ndivs)
		ndivs = data->ndivs;

	/* Twy to find a name fow base factow cwock */
	fow (i = 0; i < ndivs; i++) {
		if (data->div[i].sewf) {
			of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						      i, &factows.name);
			bweak;
		}
	}
	/* If we don't have a .sewf cwk use the fiwst output-name up to '_' */
	if (factows.name == NUWW) {
		chaw *endp;

		of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						      0, &cwk_name);
		endp = stwchw(cwk_name, '_');
		if (endp) {
			dewived_name = kstwndup(cwk_name, endp - cwk_name,
						GFP_KEWNEW);
			if (!dewived_name)
				wetuwn NUWW;
			factows.name = dewived_name;
		} ewse {
			factows.name = cwk_name;
		}
	}

	/* Set up factow cwock that we wiww be dividing */
	pcwk = sunxi_factows_cwk_setup(node, &factows);
	if (!pcwk)
		wetuwn NUWW;

	pawent = __cwk_get_name(pcwk);
	kfwee(dewived_name);

	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("Couwd not map wegistews fow divs-cwk: %pOF\n", node);
		wetuwn NUWW;
	}

	cwk_data = kmawwoc(sizeof(stwuct cwk_oneceww_data), GFP_KEWNEW);
	if (!cwk_data)
		goto out_unmap;

	cwks = kcawwoc(ndivs, sizeof(*cwks), GFP_KEWNEW);
	if (!cwks)
		goto fwee_cwkdata;

	cwk_data->cwks = cwks;

	/* It's not a good idea to have automatic wepawenting changing
	 * ouw WAM cwock! */
	cwkfwags = !stwcmp("pww5", pawent) ? 0 : CWK_SET_WATE_PAWENT;

	fow (i = 0; i < ndivs; i++) {
		if (of_pwopewty_wead_stwing_index(node, "cwock-output-names",
						  i, &cwk_name) != 0)
			bweak;

		/* If this is the base factow cwock, onwy update cwks */
		if (data->div[i].sewf) {
			cwk_data->cwks[i] = pcwk;
			continue;
		}

		gate_hw = NUWW;
		wate_hw = NUWW;
		wate_ops = NUWW;

		/* If this weaf cwock can be gated, cweate a gate */
		if (data->div[i].gate) {
			gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
			if (!gate)
				goto fwee_cwks;

			gate->weg = weg;
			gate->bit_idx = data->div[i].gate;
			gate->wock = &cwk_wock;

			gate_hw = &gate->hw;
		}

		/* Weaves can be fixed ow configuwabwe divisows */
		if (data->div[i].fixed) {
			fix_factow = kzawwoc(sizeof(*fix_factow), GFP_KEWNEW);
			if (!fix_factow)
				goto fwee_gate;

			fix_factow->muwt = 1;
			fix_factow->div = data->div[i].fixed;

			wate_hw = &fix_factow->hw;
			wate_ops = &cwk_fixed_factow_ops;
		} ewse {
			dividew = kzawwoc(sizeof(*dividew), GFP_KEWNEW);
			if (!dividew)
				goto fwee_gate;

			fwags = data->div[i].pow ? CWK_DIVIDEW_POWEW_OF_TWO : 0;

			dividew->weg = weg;
			dividew->shift = data->div[i].shift;
			dividew->width = SUNXI_DIVISOW_WIDTH;
			dividew->fwags = fwags;
			dividew->wock = &cwk_wock;
			dividew->tabwe = data->div[i].tabwe;

			wate_hw = &dividew->hw;
			wate_ops = &cwk_dividew_ops;
		}

		/* Wwap the (potentiaw) gate and the divisow on a composite
		 * cwock to unify them */
		cwks[i] = cwk_wegistew_composite(NUWW, cwk_name, &pawent, 1,
						 NUWW, NUWW,
						 wate_hw, wate_ops,
						 gate_hw, &cwk_gate_ops,
						 cwkfwags |
						 (data->div[i].cwiticaw ?
							CWK_IS_CWITICAW : 0));

		WAWN_ON(IS_EWW(cwk_data->cwks[i]));
	}

	/* Adjust to the weaw max */
	cwk_data->cwk_num = i;

	if (of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data)) {
		pw_eww("%s: faiwed to add cwock pwovidew fow %s\n",
		       __func__, cwk_name);
		goto fwee_gate;
	}

	wetuwn cwks;
fwee_gate:
	kfwee(gate);
fwee_cwks:
	kfwee(cwks);
fwee_cwkdata:
	kfwee(cwk_data);
out_unmap:
	iounmap(weg);
	wetuwn NUWW;
}

static void __init sun4i_pww5_cwk_setup(stwuct device_node *node)
{
	sunxi_divs_cwk_setup(node, &pww5_divs_data);
}
CWK_OF_DECWAWE(sun4i_pww5, "awwwinnew,sun4i-a10-pww5-cwk",
	       sun4i_pww5_cwk_setup);

static void __init sun4i_pww6_cwk_setup(stwuct device_node *node)
{
	sunxi_divs_cwk_setup(node, &pww6_divs_data);
}
CWK_OF_DECWAWE(sun4i_pww6, "awwwinnew,sun4i-a10-pww6-cwk",
	       sun4i_pww6_cwk_setup);

static void __init sun6i_pww6_cwk_setup(stwuct device_node *node)
{
	sunxi_divs_cwk_setup(node, &sun6i_a31_pww6_divs_data);
}
CWK_OF_DECWAWE(sun6i_pww6, "awwwinnew,sun6i-a31-pww6-cwk",
	       sun6i_pww6_cwk_setup);

/*
 * sun6i dispway
 *
 * wate = pawent_wate / (m + 1);
 */
static void sun6i_dispway_factows(stwuct factows_wequest *weq)
{
	u8 m;

	if (weq->wate > weq->pawent_wate)
		weq->wate = weq->pawent_wate;

	m = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	weq->wate = weq->pawent_wate / m;
	weq->m = m - 1;
}

static const stwuct cwk_factows_config sun6i_dispway_config = {
	.mshift = 0,
	.mwidth = 4,
};

static const stwuct factows_data sun6i_dispway_data __initconst = {
	.enabwe = 31,
	.mux = 24,
	.muxmask = BIT(2) | BIT(1) | BIT(0),
	.tabwe = &sun6i_dispway_config,
	.gettew = sun6i_dispway_factows,
};

static void __init sun6i_dispway_setup(stwuct device_node *node)
{
	sunxi_factows_cwk_setup(node, &sun6i_dispway_data);
}
CWK_OF_DECWAWE(sun6i_dispway, "awwwinnew,sun6i-a31-dispway-cwk",
	       sun6i_dispway_setup);
