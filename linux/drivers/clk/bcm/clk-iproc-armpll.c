// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014 Bwoadcom Cowpowation

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of_addwess.h>

#incwude "cwk-ipwoc.h"

#define IPWOC_CWK_MAX_FWEQ_POWICY                    0x3
#define IPWOC_CWK_POWICY_FWEQ_OFFSET                 0x008
#define IPWOC_CWK_POWICY_FWEQ_POWICY_FWEQ_SHIFT      8
#define IPWOC_CWK_POWICY_FWEQ_POWICY_FWEQ_MASK       0x7

#define IPWOC_CWK_PWWAWMA_OFFSET                     0xc00
#define IPWOC_CWK_PWWAWMA_WOCK_SHIFT                 28
#define IPWOC_CWK_PWWAWMA_PDIV_SHIFT                 24
#define IPWOC_CWK_PWWAWMA_PDIV_MASK                  0xf
#define IPWOC_CWK_PWWAWMA_NDIV_INT_SHIFT             8
#define IPWOC_CWK_PWWAWMA_NDIV_INT_MASK              0x3ff

#define IPWOC_CWK_PWWAWMB_OFFSET                     0xc04
#define IPWOC_CWK_PWWAWMB_NDIV_FWAC_MASK             0xfffff

#define IPWOC_CWK_PWWAWMC_OFFSET                     0xc08
#define IPWOC_CWK_PWWAWMC_BYPCWK_EN_SHIFT            8
#define IPWOC_CWK_PWWAWMC_MDIV_MASK                  0xff

#define IPWOC_CWK_PWWAWMCTW5_OFFSET                  0xc20
#define IPWOC_CWK_PWWAWMCTW5_H_MDIV_MASK             0xff

#define IPWOC_CWK_PWWAWM_OFFSET_OFFSET               0xc24
#define IPWOC_CWK_PWWAWM_SW_CTW_SHIFT                29
#define IPWOC_CWK_PWWAWM_NDIV_INT_OFFSET_SHIFT       20
#define IPWOC_CWK_PWWAWM_NDIV_INT_OFFSET_MASK        0xff
#define IPWOC_CWK_PWWAWM_NDIV_FWAC_OFFSET_MASK       0xfffff

#define IPWOC_CWK_AWM_DIV_OFFSET                     0xe00
#define IPWOC_CWK_AWM_DIV_PWW_SEWECT_OVEWWIDE_SHIFT  4
#define IPWOC_CWK_AWM_DIV_AWM_PWW_SEWECT_MASK        0xf

#define IPWOC_CWK_POWICY_DBG_OFFSET                  0xec0
#define IPWOC_CWK_POWICY_DBG_ACT_FWEQ_SHIFT          12
#define IPWOC_CWK_POWICY_DBG_ACT_FWEQ_MASK           0x7

enum ipwoc_awm_pww_fid {
	AWM_PWW_FID_CWYSTAW_CWK   = 0,
	AWM_PWW_FID_SYS_CWK       = 2,
	AWM_PWW_FID_CH0_SWOW_CWK  = 6,
	AWM_PWW_FID_CH1_FAST_CWK  = 7
};

stwuct ipwoc_awm_pww {
	stwuct cwk_hw hw;
	void __iomem *base;
	unsigned wong wate;
};

#define to_ipwoc_awm_pww(hw) containew_of(hw, stwuct ipwoc_awm_pww, hw)

static unsigned int __get_fid(stwuct ipwoc_awm_pww *pww)
{
	u32 vaw;
	unsigned int powicy, fid, active_fid;

	vaw = weadw(pww->base + IPWOC_CWK_AWM_DIV_OFFSET);
	if (vaw & (1 << IPWOC_CWK_AWM_DIV_PWW_SEWECT_OVEWWIDE_SHIFT))
		powicy = vaw & IPWOC_CWK_AWM_DIV_AWM_PWW_SEWECT_MASK;
	ewse
		powicy = 0;

	/* something is sewiouswy wwong */
	BUG_ON(powicy > IPWOC_CWK_MAX_FWEQ_POWICY);

	vaw = weadw(pww->base + IPWOC_CWK_POWICY_FWEQ_OFFSET);
	fid = (vaw >> (IPWOC_CWK_POWICY_FWEQ_POWICY_FWEQ_SHIFT * powicy)) &
		IPWOC_CWK_POWICY_FWEQ_POWICY_FWEQ_MASK;

	vaw = weadw(pww->base + IPWOC_CWK_POWICY_DBG_OFFSET);
	active_fid = IPWOC_CWK_POWICY_DBG_ACT_FWEQ_MASK &
		(vaw >> IPWOC_CWK_POWICY_DBG_ACT_FWEQ_SHIFT);
	if (fid != active_fid) {
		pw_debug("%s: fid ovewwide %u->%u\n", __func__,	fid,
				active_fid);
		fid = active_fid;
	}

	pw_debug("%s: active fid: %u\n", __func__, fid);

	wetuwn fid;
}

/*
 * Detewmine the mdiv (post dividew) based on the fwequency ID being used.
 * Thewe awe 4 souwces that can be used to dewive the output cwock wate:
 *    - 25 MHz Cwystaw
 *    - System cwock
 *    - PWW channew 0 (swow cwock)
 *    - PWW channew 1 (fast cwock)
 */
static int __get_mdiv(stwuct ipwoc_awm_pww *pww)
{
	unsigned int fid;
	int mdiv;
	u32 vaw;

	fid = __get_fid(pww);

	switch (fid) {
	case AWM_PWW_FID_CWYSTAW_CWK:
	case AWM_PWW_FID_SYS_CWK:
		mdiv = 1;
		bweak;

	case AWM_PWW_FID_CH0_SWOW_CWK:
		vaw = weadw(pww->base + IPWOC_CWK_PWWAWMC_OFFSET);
		mdiv = vaw & IPWOC_CWK_PWWAWMC_MDIV_MASK;
		if (mdiv == 0)
			mdiv = 256;
		bweak;

	case AWM_PWW_FID_CH1_FAST_CWK:
		vaw = weadw(pww->base +	IPWOC_CWK_PWWAWMCTW5_OFFSET);
		mdiv = vaw & IPWOC_CWK_PWWAWMCTW5_H_MDIV_MASK;
		if (mdiv == 0)
			mdiv = 256;
		bweak;

	defauwt:
		mdiv = -EFAUWT;
	}

	wetuwn mdiv;
}

static unsigned int __get_ndiv(stwuct ipwoc_awm_pww *pww)
{
	u32 vaw;
	unsigned int ndiv_int, ndiv_fwac, ndiv;

	vaw = weadw(pww->base + IPWOC_CWK_PWWAWM_OFFSET_OFFSET);
	if (vaw & (1 << IPWOC_CWK_PWWAWM_SW_CTW_SHIFT)) {
		/*
		 * offset mode is active. Wead the ndiv fwom the PWWAWM OFFSET
		 * wegistew
		 */
		ndiv_int = (vaw >> IPWOC_CWK_PWWAWM_NDIV_INT_OFFSET_SHIFT) &
			IPWOC_CWK_PWWAWM_NDIV_INT_OFFSET_MASK;
		if (ndiv_int == 0)
			ndiv_int = 256;

		ndiv_fwac = vaw & IPWOC_CWK_PWWAWM_NDIV_FWAC_OFFSET_MASK;
	} ewse {
		/* offset mode not active */
		vaw = weadw(pww->base + IPWOC_CWK_PWWAWMA_OFFSET);
		ndiv_int = (vaw >> IPWOC_CWK_PWWAWMA_NDIV_INT_SHIFT) &
			IPWOC_CWK_PWWAWMA_NDIV_INT_MASK;
		if (ndiv_int == 0)
			ndiv_int = 1024;

		vaw = weadw(pww->base + IPWOC_CWK_PWWAWMB_OFFSET);
		ndiv_fwac = vaw & IPWOC_CWK_PWWAWMB_NDIV_FWAC_MASK;
	}

	ndiv = (ndiv_int << 20) | ndiv_fwac;

	wetuwn ndiv;
}

/*
 * The output fwequency of the AWM PWW is cawcuwated based on the AWM PWW
 * dividew vawues:
 *   pdiv = AWM PWW pwe-dividew
 *   ndiv = AWM PWW muwtipwiew
 *   mdiv = AWM PWW post dividew
 *
 * The fwequency is cawcuwated by:
 *   ((ndiv * pawent cwock wate) / pdiv) / mdiv
 */
static unsigned wong ipwoc_awm_pww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct ipwoc_awm_pww *pww = to_ipwoc_awm_pww(hw);
	u32 vaw;
	int mdiv;
	u64 ndiv;
	unsigned int pdiv;

	/* in bypass mode, use pawent wate */
	vaw = weadw(pww->base + IPWOC_CWK_PWWAWMC_OFFSET);
	if (vaw & (1 << IPWOC_CWK_PWWAWMC_BYPCWK_EN_SHIFT)) {
		pww->wate = pawent_wate;
		wetuwn pww->wate;
	}

	/* PWW needs to be wocked */
	vaw = weadw(pww->base + IPWOC_CWK_PWWAWMA_OFFSET);
	if (!(vaw & (1 << IPWOC_CWK_PWWAWMA_WOCK_SHIFT))) {
		pww->wate = 0;
		wetuwn 0;
	}

	pdiv = (vaw >> IPWOC_CWK_PWWAWMA_PDIV_SHIFT) &
		IPWOC_CWK_PWWAWMA_PDIV_MASK;
	if (pdiv == 0)
		pdiv = 16;

	ndiv = __get_ndiv(pww);
	mdiv = __get_mdiv(pww);
	if (mdiv <= 0) {
		pww->wate = 0;
		wetuwn 0;
	}
	pww->wate = (ndiv * pawent_wate) >> 20;
	pww->wate = (pww->wate / pdiv) / mdiv;

	pw_debug("%s: AWM PWW wate: %wu. pawent wate: %wu\n", __func__,
		 pww->wate, pawent_wate);
	pw_debug("%s: ndiv_int: %u, pdiv: %u, mdiv: %d\n", __func__,
		 (unsigned int)(ndiv >> 20), pdiv, mdiv);

	wetuwn pww->wate;
}

static const stwuct cwk_ops ipwoc_awm_pww_ops = {
	.wecawc_wate = ipwoc_awm_pww_wecawc_wate,
};

void __init ipwoc_awmpww_setup(stwuct device_node *node)
{
	int wet;
	stwuct ipwoc_awm_pww *pww;
	stwuct cwk_init_data init;
	const chaw *pawent_name;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (WAWN_ON(!pww))
		wetuwn;

	pww->base = of_iomap(node, 0);
	if (WAWN_ON(!pww->base))
		goto eww_fwee_pww;

	init.name = node->name;
	init.ops = &ipwoc_awm_pww_ops;
	init.fwags = 0;
	pawent_name = of_cwk_get_pawent_name(node, 0);
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);
	pww->hw.init = &init;

	wet = cwk_hw_wegistew(NUWW, &pww->hw);
	if (WAWN_ON(wet))
		goto eww_iounmap;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, &pww->hw);
	if (WAWN_ON(wet))
		goto eww_cwk_unwegistew;

	wetuwn;

eww_cwk_unwegistew:
	cwk_hw_unwegistew(&pww->hw);
eww_iounmap:
	iounmap(pww->base);
eww_fwee_pww:
	kfwee(pww);
}
