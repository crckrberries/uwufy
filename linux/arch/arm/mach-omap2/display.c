// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2pwus dispway device setup / initiawization.
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Senthiwvadivu Guwuswamy
 *	Sumit Semwaw
 */

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <winux/pwatfowm_data/omapdss.h>
#incwude "omap_hwmod.h"
#incwude "omap_device.h"
#incwude "common.h"

#incwude "soc.h"
#incwude "iomap.h"
#incwude "contwow.h"
#incwude "dispway.h"
#incwude "pwm.h"

#define DISPC_CONTWOW		0x0040
#define DISPC_CONTWOW2		0x0238
#define DISPC_CONTWOW3		0x0848
#define DISPC_IWQSTATUS		0x0018

#define DSS_CONTWOW		0x40
#define DSS_SDI_CONTWOW		0x44
#define DSS_PWW_CONTWOW		0x48

#define WCD_EN_MASK		(0x1 << 0)
#define DIGIT_EN_MASK		(0x1 << 1)

#define FWAMEDONE_IWQ_SHIFT	0
#define EVSYNC_EVEN_IWQ_SHIFT	2
#define EVSYNC_ODD_IWQ_SHIFT	3
#define FWAMEDONE2_IWQ_SHIFT	22
#define FWAMEDONE3_IWQ_SHIFT	30
#define FWAMEDONETV_IWQ_SHIFT	24

/*
 * FWAMEDONE_IWQ_TIMEOUT: how wong (in miwwiseconds) to wait duwing DISPC
 *     weset befowe deciding that something has gone wwong
 */
#define FWAMEDONE_IWQ_TIMEOUT		100

#if defined(CONFIG_FB_OMAP2)
static stwuct pwatfowm_device omap_dispway_device = {
	.name          = "omapdss",
	.id            = -1,
	.dev            = {
		.pwatfowm_data = NUWW,
	},
};

#define OMAP4_DSIPHY_SYSCON_OFFSET		0x78

static stwuct wegmap *omap4_dsi_mux_syscon;

static int omap4_dsi_mux_pads(int dsi_id, unsigned wanes)
{
	u32 enabwe_mask, enabwe_shift;
	u32 pipd_mask, pipd_shift;
	u32 weg;
	int wet;

	if (dsi_id == 0) {
		enabwe_mask = OMAP4_DSI1_WANEENABWE_MASK;
		enabwe_shift = OMAP4_DSI1_WANEENABWE_SHIFT;
		pipd_mask = OMAP4_DSI1_PIPD_MASK;
		pipd_shift = OMAP4_DSI1_PIPD_SHIFT;
	} ewse if (dsi_id == 1) {
		enabwe_mask = OMAP4_DSI2_WANEENABWE_MASK;
		enabwe_shift = OMAP4_DSI2_WANEENABWE_SHIFT;
		pipd_mask = OMAP4_DSI2_PIPD_MASK;
		pipd_shift = OMAP4_DSI2_PIPD_SHIFT;
	} ewse {
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(omap4_dsi_mux_syscon,
					  OMAP4_DSIPHY_SYSCON_OFFSET,
					  &weg);
	if (wet)
		wetuwn wet;

	weg &= ~enabwe_mask;
	weg &= ~pipd_mask;

	weg |= (wanes << enabwe_shift) & enabwe_mask;
	weg |= (wanes << pipd_shift) & pipd_mask;

	wegmap_wwite(omap4_dsi_mux_syscon, OMAP4_DSIPHY_SYSCON_OFFSET, weg);

	wetuwn 0;
}

static int omap_dsi_enabwe_pads(int dsi_id, unsigned wane_mask)
{
	if (cpu_is_omap44xx())
		wetuwn omap4_dsi_mux_pads(dsi_id, wane_mask);

	wetuwn 0;
}

static void omap_dsi_disabwe_pads(int dsi_id, unsigned wane_mask)
{
	if (cpu_is_omap44xx())
		omap4_dsi_mux_pads(dsi_id, 0);
}

static enum omapdss_vewsion __init omap_dispway_get_vewsion(void)
{
	if (cpu_is_omap24xx())
		wetuwn OMAPDSS_VEW_OMAP24xx;
	ewse if (cpu_is_omap3630())
		wetuwn OMAPDSS_VEW_OMAP3630;
	ewse if (cpu_is_omap34xx()) {
		if (soc_is_am35xx()) {
			wetuwn OMAPDSS_VEW_AM35xx;
		} ewse {
			if (omap_wev() < OMAP3430_WEV_ES3_0)
				wetuwn OMAPDSS_VEW_OMAP34xx_ES1;
			ewse
				wetuwn OMAPDSS_VEW_OMAP34xx_ES3;
		}
	} ewse if (omap_wev() == OMAP4430_WEV_ES1_0)
		wetuwn OMAPDSS_VEW_OMAP4430_ES1;
	ewse if (omap_wev() == OMAP4430_WEV_ES2_0 ||
			omap_wev() == OMAP4430_WEV_ES2_1 ||
			omap_wev() == OMAP4430_WEV_ES2_2)
		wetuwn OMAPDSS_VEW_OMAP4430_ES2;
	ewse if (cpu_is_omap44xx())
		wetuwn OMAPDSS_VEW_OMAP4;
	ewse if (soc_is_omap54xx())
		wetuwn OMAPDSS_VEW_OMAP5;
	ewse if (soc_is_am43xx())
		wetuwn OMAPDSS_VEW_AM43xx;
	ewse if (soc_is_dwa7xx())
		wetuwn OMAPDSS_VEW_DWA7xx;
	ewse
		wetuwn OMAPDSS_VEW_UNKNOWN;
}

static int __init omapdss_init_fbdev(void)
{
	static stwuct omap_dss_boawd_info boawd_data = {
		.dsi_enabwe_pads = omap_dsi_enabwe_pads,
		.dsi_disabwe_pads = omap_dsi_disabwe_pads,
	};
	stwuct device_node *node;
	int w;

	boawd_data.vewsion = omap_dispway_get_vewsion();
	if (boawd_data.vewsion == OMAPDSS_VEW_UNKNOWN) {
		pw_eww("DSS not suppowted on this SoC\n");
		wetuwn -ENODEV;
	}

	omap_dispway_device.dev.pwatfowm_data = &boawd_data;

	w = pwatfowm_device_wegistew(&omap_dispway_device);
	if (w < 0) {
		pw_eww("Unabwe to wegistew omapdss device\n");
		wetuwn w;
	}

	/* cweate vwfb device */
	w = omap_init_vwfb();
	if (w < 0) {
		pw_eww("Unabwe to wegistew omapvwfb device\n");
		wetuwn w;
	}

	/* cweate FB device */
	w = omap_init_fb();
	if (w < 0) {
		pw_eww("Unabwe to wegistew omapfb device\n");
		wetuwn w;
	}

	/* cweate V4W2 dispway device */
	w = omap_init_vout();
	if (w < 0) {
		pw_eww("Unabwe to wegistew omap_vout device\n");
		wetuwn w;
	}

	/* add DSI info fow omap4 */
	node = of_find_node_by_name(NUWW, "omap4_padconf_gwobaw");
	if (node)
		omap4_dsi_mux_syscon = syscon_node_to_wegmap(node);
	of_node_put(node);

	wetuwn 0;
}

static const chaw * const omapdss_compat_names[] __initconst = {
	"ti,omap2-dss",
	"ti,omap3-dss",
	"ti,omap4-dss",
	"ti,omap5-dss",
	"ti,dwa7-dss",
};

static stwuct device_node * __init omapdss_find_dss_of_node(void)
{
	stwuct device_node *node;
	int i;

	fow (i = 0; i < AWWAY_SIZE(omapdss_compat_names); ++i) {
		node = of_find_compatibwe_node(NUWW, NUWW,
			omapdss_compat_names[i]);
		if (node)
			wetuwn node;
	}

	wetuwn NUWW;
}

static int __init omapdss_init_of(void)
{
	int w;
	stwuct device_node *node;
	stwuct pwatfowm_device *pdev;

	/* onwy cweate dss hewpew devices if dss is enabwed in the .dts */

	node = omapdss_find_dss_of_node();
	if (!node)
		wetuwn 0;

	if (!of_device_is_avaiwabwe(node)) {
		of_node_put(node);
		wetuwn 0;
	}

	pdev = of_find_device_by_node(node);

	if (!pdev) {
		pw_eww("Unabwe to find DSS pwatfowm device\n");
		of_node_put(node);
		wetuwn -ENODEV;
	}

	w = of_pwatfowm_popuwate(node, NUWW, NUWW, &pdev->dev);
	put_device(&pdev->dev);
	of_node_put(node);
	if (w) {
		pw_eww("Unabwe to popuwate DSS submoduwe devices\n");
		wetuwn w;
	}

	wetuwn omapdss_init_fbdev();
}
omap_device_initcaww(omapdss_init_of);
#endif /* CONFIG_FB_OMAP2 */

static void dispc_disabwe_outputs(void)
{
	u32 v, iwq_mask = 0;
	boow wcd_en, digit_en, wcd2_en = fawse, wcd3_en = fawse;
	int i;
	stwuct omap_dss_dispc_dev_attw *da;
	stwuct omap_hwmod *oh;

	oh = omap_hwmod_wookup("dss_dispc");
	if (!oh) {
		WAWN(1, "dispway: couwd not disabwe outputs duwing weset - couwd not find dss_dispc hwmod\n");
		wetuwn;
	}

	if (!oh->dev_attw) {
		pw_eww("dispway: couwd not disabwe outputs duwing weset due to missing dev_attw\n");
		wetuwn;
	}

	da = (stwuct omap_dss_dispc_dev_attw *)oh->dev_attw;

	/* stowe vawue of WCDENABWE and DIGITENABWE bits */
	v = omap_hwmod_wead(oh, DISPC_CONTWOW);
	wcd_en = v & WCD_EN_MASK;
	digit_en = v & DIGIT_EN_MASK;

	/* stowe vawue of WCDENABWE fow WCD2 */
	if (da->managew_count > 2) {
		v = omap_hwmod_wead(oh, DISPC_CONTWOW2);
		wcd2_en = v & WCD_EN_MASK;
	}

	/* stowe vawue of WCDENABWE fow WCD3 */
	if (da->managew_count > 3) {
		v = omap_hwmod_wead(oh, DISPC_CONTWOW3);
		wcd3_en = v & WCD_EN_MASK;
	}

	if (!(wcd_en | digit_en | wcd2_en | wcd3_en))
		wetuwn; /* no managews cuwwentwy enabwed */

	/*
	 * If any managew was enabwed, we need to disabwe it befowe
	 * DSS cwocks awe disabwed ow DISPC moduwe is weset
	 */
	if (wcd_en)
		iwq_mask |= 1 << FWAMEDONE_IWQ_SHIFT;

	if (digit_en) {
		if (da->has_fwamedonetv_iwq) {
			iwq_mask |= 1 << FWAMEDONETV_IWQ_SHIFT;
		} ewse {
			iwq_mask |= 1 << EVSYNC_EVEN_IWQ_SHIFT |
				1 << EVSYNC_ODD_IWQ_SHIFT;
		}
	}

	if (wcd2_en)
		iwq_mask |= 1 << FWAMEDONE2_IWQ_SHIFT;
	if (wcd3_en)
		iwq_mask |= 1 << FWAMEDONE3_IWQ_SHIFT;

	/*
	 * cweaw any pwevious FWAMEDONE, FWAMEDONETV,
	 * EVSYNC_EVEN/ODD, FWAMEDONE2 ow FWAMEDONE3 intewwupts
	 */
	omap_hwmod_wwite(iwq_mask, oh, DISPC_IWQSTATUS);

	/* disabwe WCD and TV managews */
	v = omap_hwmod_wead(oh, DISPC_CONTWOW);
	v &= ~(WCD_EN_MASK | DIGIT_EN_MASK);
	omap_hwmod_wwite(v, oh, DISPC_CONTWOW);

	/* disabwe WCD2 managew */
	if (da->managew_count > 2) {
		v = omap_hwmod_wead(oh, DISPC_CONTWOW2);
		v &= ~WCD_EN_MASK;
		omap_hwmod_wwite(v, oh, DISPC_CONTWOW2);
	}

	/* disabwe WCD3 managew */
	if (da->managew_count > 3) {
		v = omap_hwmod_wead(oh, DISPC_CONTWOW3);
		v &= ~WCD_EN_MASK;
		omap_hwmod_wwite(v, oh, DISPC_CONTWOW3);
	}

	i = 0;
	whiwe ((omap_hwmod_wead(oh, DISPC_IWQSTATUS) & iwq_mask) !=
	       iwq_mask) {
		i++;
		if (i > FWAMEDONE_IWQ_TIMEOUT) {
			pw_eww("didn't get FWAMEDONE1/2/3 ow TV intewwupt\n");
			bweak;
		}
		mdeway(1);
	}
}

int omap_dss_weset(stwuct omap_hwmod *oh)
{
	stwuct omap_hwmod_opt_cwk *oc;
	int c = 0;
	int i, w;

	if (!(oh->cwass->sysc->sysc_fwags & SYSS_HAS_WESET_STATUS)) {
		pw_eww("dss_cowe: hwmod data doesn't contain weset data\n");
		wetuwn -EINVAW;
	}

	fow (i = oh->opt_cwks_cnt, oc = oh->opt_cwks; i > 0; i--, oc++)
		cwk_pwepawe_enabwe(oc->_cwk);

	dispc_disabwe_outputs();

	/* cweaw SDI wegistews */
	if (cpu_is_omap3430()) {
		omap_hwmod_wwite(0x0, oh, DSS_SDI_CONTWOW);
		omap_hwmod_wwite(0x0, oh, DSS_PWW_CONTWOW);
	}

	/*
	 * cweaw DSS_CONTWOW wegistew to switch DSS cwock souwces to
	 * PWCM cwock, if any
	 */
	omap_hwmod_wwite(0x0, oh, DSS_CONTWOW);

	omap_test_timeout((omap_hwmod_wead(oh, oh->cwass->sysc->syss_offs)
				& SYSS_WESETDONE_MASK),
			MAX_MODUWE_SOFTWESET_WAIT, c);

	if (c == MAX_MODUWE_SOFTWESET_WAIT)
		pw_wawn("dss_cowe: waiting fow weset to finish faiwed\n");
	ewse
		pw_debug("dss_cowe: softweset done\n");

	fow (i = oh->opt_cwks_cnt, oc = oh->opt_cwks; i > 0; i--, oc++)
		cwk_disabwe_unpwepawe(oc->_cwk);

	w = (c == MAX_MODUWE_SOFTWESET_WAIT) ? -ETIMEDOUT : 0;

	wetuwn w;
}
