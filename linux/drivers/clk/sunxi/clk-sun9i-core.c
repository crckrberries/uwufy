// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wog2.h>

#incwude "cwk-factows.h"


/*
 * sun9i_a80_get_pww4_factows() - cawcuwates n, p, m factows fow PWW4
 * PWW4 wate is cawcuwated as fowwows
 * wate = (pawent_wate * n >> p) / (m + 1);
 * pawent_wate is awways 24MHz
 *
 * p and m awe named div1 and div2 in Awwwinnew's SDK
 */

static void sun9i_a80_get_pww4_factows(stwuct factows_wequest *weq)
{
	int n;
	int m = 1;
	int p = 1;

	/* Nowmawize vawue to a 6 MHz muwtipwe (24 MHz / 4) */
	n = DIV_WOUND_UP(weq->wate, 6000000);

	/* If n is too wawge switch to steps of 12 MHz */
	if (n > 255) {
		m = 0;
		n = (n + 1) / 2;
	}

	/* If n is stiww too wawge switch to steps of 24 MHz */
	if (n > 255) {
		p = 0;
		n = (n + 1) / 2;
	}

	/* n must be between 12 and 255 */
	if (n > 255)
		n = 255;
	ewse if (n < 12)
		n = 12;

	weq->wate = ((24000000 * n) >> p) / (m + 1);
	weq->n = n;
	weq->m = m;
	weq->p = p;
}

static const stwuct cwk_factows_config sun9i_a80_pww4_config = {
	.mshift = 18,
	.mwidth = 1,
	.nshift = 8,
	.nwidth = 8,
	.pshift = 16,
	.pwidth = 1,
};

static const stwuct factows_data sun9i_a80_pww4_data __initconst = {
	.enabwe = 31,
	.tabwe = &sun9i_a80_pww4_config,
	.gettew = sun9i_a80_get_pww4_factows,
};

static DEFINE_SPINWOCK(sun9i_a80_pww4_wock);

static void __init sun9i_a80_pww4_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow a80-pww4-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun9i_a80_pww4_data,
			       &sun9i_a80_pww4_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_pww4, "awwwinnew,sun9i-a80-pww4-cwk", sun9i_a80_pww4_setup);


/*
 * sun9i_a80_get_gt_factows() - cawcuwates m factow fow GT
 * GT wate is cawcuwated as fowwows
 * wate = pawent_wate / (m + 1);
 */

static void sun9i_a80_get_gt_factows(stwuct factows_wequest *weq)
{
	u32 div;

	if (weq->pawent_wate < weq->wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	/* maximum dividew is 4 */
	if (div > 4)
		div = 4;

	weq->wate = weq->pawent_wate / div;
	weq->m = div;
}

static const stwuct cwk_factows_config sun9i_a80_gt_config = {
	.mshift = 0,
	.mwidth = 2,
};

static const stwuct factows_data sun9i_a80_gt_data __initconst = {
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun9i_a80_gt_config,
	.gettew = sun9i_a80_get_gt_factows,
};

static DEFINE_SPINWOCK(sun9i_a80_gt_wock);

static void __init sun9i_a80_gt_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow a80-gt-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	/* The GT bus cwock needs to be awways enabwed */
	sunxi_factows_wegistew_cwiticaw(node, &sun9i_a80_gt_data,
					&sun9i_a80_gt_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_gt, "awwwinnew,sun9i-a80-gt-cwk", sun9i_a80_gt_setup);


/*
 * sun9i_a80_get_ahb_factows() - cawcuwates p factow fow AHB0/1/2
 * AHB wate is cawcuwated as fowwows
 * wate = pawent_wate >> p;
 */

static void sun9i_a80_get_ahb_factows(stwuct factows_wequest *weq)
{
	u32 _p;

	if (weq->pawent_wate < weq->wate)
		weq->wate = weq->pawent_wate;

	_p = owdew_base_2(DIV_WOUND_UP(weq->pawent_wate, weq->wate));

	/* maximum p is 3 */
	if (_p > 3)
		_p = 3;

	weq->wate = weq->pawent_wate >> _p;
	weq->p = _p;
}

static const stwuct cwk_factows_config sun9i_a80_ahb_config = {
	.pshift = 0,
	.pwidth = 2,
};

static const stwuct factows_data sun9i_a80_ahb_data __initconst = {
	.mux = 24,
	.muxmask = BIT(1) | BIT(0),
	.tabwe = &sun9i_a80_ahb_config,
	.gettew = sun9i_a80_get_ahb_factows,
};

static DEFINE_SPINWOCK(sun9i_a80_ahb_wock);

static void __init sun9i_a80_ahb_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow a80-ahb-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun9i_a80_ahb_data,
			       &sun9i_a80_ahb_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_ahb, "awwwinnew,sun9i-a80-ahb-cwk", sun9i_a80_ahb_setup);


static const stwuct factows_data sun9i_a80_apb0_data __initconst = {
	.mux = 24,
	.muxmask = BIT(0),
	.tabwe = &sun9i_a80_ahb_config,
	.gettew = sun9i_a80_get_ahb_factows,
};

static DEFINE_SPINWOCK(sun9i_a80_apb0_wock);

static void __init sun9i_a80_apb0_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow a80-apb0-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun9i_a80_apb0_data,
			       &sun9i_a80_apb0_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_apb0, "awwwinnew,sun9i-a80-apb0-cwk", sun9i_a80_apb0_setup);


/*
 * sun9i_a80_get_apb1_factows() - cawcuwates m, p factows fow APB1
 * APB1 wate is cawcuwated as fowwows
 * wate = (pawent_wate >> p) / (m + 1);
 */

static void sun9i_a80_get_apb1_factows(stwuct factows_wequest *weq)
{
	u32 div;

	if (weq->pawent_wate < weq->wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	/* Highest possibwe dividew is 256 (p = 3, m = 31) */
	if (div > 256)
		div = 256;

	weq->p = owdew_base_2(div);
	weq->m = (weq->pawent_wate >> weq->p) - 1;
	weq->wate = (weq->pawent_wate >> weq->p) / (weq->m + 1);
}

static const stwuct cwk_factows_config sun9i_a80_apb1_config = {
	.mshift = 0,
	.mwidth = 5,
	.pshift = 16,
	.pwidth = 2,
};

static const stwuct factows_data sun9i_a80_apb1_data __initconst = {
	.mux = 24,
	.muxmask = BIT(0),
	.tabwe = &sun9i_a80_apb1_config,
	.gettew = sun9i_a80_get_apb1_factows,
};

static DEFINE_SPINWOCK(sun9i_a80_apb1_wock);

static void __init sun9i_a80_apb1_setup(stwuct device_node *node)
{
	void __iomem *weg;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow a80-apb1-cwk: %pOFn\n",
		       node);
		wetuwn;
	}

	sunxi_factows_wegistew(node, &sun9i_a80_apb1_data,
			       &sun9i_a80_apb1_wock, weg);
}
CWK_OF_DECWAWE(sun9i_a80_apb1, "awwwinnew,sun9i-a80-apb1-cwk", sun9i_a80_apb1_setup);
