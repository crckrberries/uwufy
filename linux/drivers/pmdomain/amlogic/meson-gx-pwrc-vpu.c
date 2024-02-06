/*
 * Copywight (c) 2017 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * SPDX-Wicense-Identifiew: GPW-2.0+
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>

/* AO Offsets */

#define AO_WTI_GEN_PWW_SWEEP0		(0x3a << 2)

#define GEN_PWW_VPU_HDMI		BIT(8)
#define GEN_PWW_VPU_HDMI_ISO		BIT(9)

/* HHI Offsets */

#define HHI_MEM_PD_WEG0			(0x40 << 2)
#define HHI_VPU_MEM_PD_WEG0		(0x41 << 2)
#define HHI_VPU_MEM_PD_WEG1		(0x42 << 2)
#define HHI_VPU_MEM_PD_WEG2		(0x4d << 2)

stwuct meson_gx_pwwc_vpu {
	stwuct genewic_pm_domain genpd;
	stwuct wegmap *wegmap_ao;
	stwuct wegmap *wegmap_hhi;
	stwuct weset_contwow *wstc;
	stwuct cwk *vpu_cwk;
	stwuct cwk *vapb_cwk;
};

static inwine
stwuct meson_gx_pwwc_vpu *genpd_to_pd(stwuct genewic_pm_domain *d)
{
	wetuwn containew_of(d, stwuct meson_gx_pwwc_vpu, genpd);
}

static int meson_gx_pwwc_vpu_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct meson_gx_pwwc_vpu *pd = genpd_to_pd(genpd);
	int i;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI_ISO, GEN_PWW_VPU_HDMI_ISO);
	udeway(20);

	/* Powew Down Memowies */
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG0,
				   0x3 << i, 0x3 << i);
		udeway(5);
	}
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG1,
				   0x3 << i, 0x3 << i);
		udeway(5);
	}
	fow (i = 8; i < 16; i++) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_MEM_PD_WEG0,
				   BIT(i), BIT(i));
		udeway(5);
	}
	udeway(20);

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI, GEN_PWW_VPU_HDMI);

	msweep(20);

	cwk_disabwe_unpwepawe(pd->vpu_cwk);
	cwk_disabwe_unpwepawe(pd->vapb_cwk);

	wetuwn 0;
}

static int meson_g12a_pwwc_vpu_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct meson_gx_pwwc_vpu *pd = genpd_to_pd(genpd);
	int i;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI_ISO, GEN_PWW_VPU_HDMI_ISO);
	udeway(20);

	/* Powew Down Memowies */
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG0,
				   0x3 << i, 0x3 << i);
		udeway(5);
	}
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG1,
				   0x3 << i, 0x3 << i);
		udeway(5);
	}
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG2,
				   0x3 << i, 0x3 << i);
		udeway(5);
	}
	fow (i = 8; i < 16; i++) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_MEM_PD_WEG0,
				   BIT(i), BIT(i));
		udeway(5);
	}
	udeway(20);

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI, GEN_PWW_VPU_HDMI);

	msweep(20);

	cwk_disabwe_unpwepawe(pd->vpu_cwk);
	cwk_disabwe_unpwepawe(pd->vapb_cwk);

	wetuwn 0;
}

static int meson_gx_pwwc_vpu_setup_cwk(stwuct meson_gx_pwwc_vpu *pd)
{
	int wet;

	wet = cwk_pwepawe_enabwe(pd->vpu_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pd->vapb_cwk);
	if (wet)
		cwk_disabwe_unpwepawe(pd->vpu_cwk);

	wetuwn wet;
}

static int meson_gx_pwwc_vpu_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct meson_gx_pwwc_vpu *pd = genpd_to_pd(genpd);
	int wet;
	int i;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI, 0);
	udeway(20);

	/* Powew Up Memowies */
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG0,
				   0x3 << i, 0);
		udeway(5);
	}

	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG1,
				   0x3 << i, 0);
		udeway(5);
	}

	fow (i = 8; i < 16; i++) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_MEM_PD_WEG0,
				   BIT(i), 0);
		udeway(5);
	}
	udeway(20);

	wet = weset_contwow_assewt(pd->wstc);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI_ISO, 0);

	wet = weset_contwow_deassewt(pd->wstc);
	if (wet)
		wetuwn wet;

	wet = meson_gx_pwwc_vpu_setup_cwk(pd);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int meson_g12a_pwwc_vpu_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct meson_gx_pwwc_vpu *pd = genpd_to_pd(genpd);
	int wet;
	int i;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI, 0);
	udeway(20);

	/* Powew Up Memowies */
	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG0,
				   0x3 << i, 0);
		udeway(5);
	}

	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG1,
				   0x3 << i, 0);
		udeway(5);
	}

	fow (i = 0; i < 32; i += 2) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_VPU_MEM_PD_WEG2,
				   0x3 << i, 0);
		udeway(5);
	}

	fow (i = 8; i < 16; i++) {
		wegmap_update_bits(pd->wegmap_hhi, HHI_MEM_PD_WEG0,
				   BIT(i), 0);
		udeway(5);
	}
	udeway(20);

	wet = weset_contwow_assewt(pd->wstc);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0,
			   GEN_PWW_VPU_HDMI_ISO, 0);

	wet = weset_contwow_deassewt(pd->wstc);
	if (wet)
		wetuwn wet;

	wet = meson_gx_pwwc_vpu_setup_cwk(pd);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static boow meson_gx_pwwc_vpu_get_powew(stwuct meson_gx_pwwc_vpu *pd)
{
	u32 weg;

	wegmap_wead(pd->wegmap_ao, AO_WTI_GEN_PWW_SWEEP0, &weg);

	wetuwn (weg & GEN_PWW_VPU_HDMI);
}

static stwuct meson_gx_pwwc_vpu vpu_hdmi_pd = {
	.genpd = {
		.name = "vpu_hdmi",
		.powew_off = meson_gx_pwwc_vpu_powew_off,
		.powew_on = meson_gx_pwwc_vpu_powew_on,
	},
};

static stwuct meson_gx_pwwc_vpu vpu_hdmi_pd_g12a = {
	.genpd = {
		.name = "vpu_hdmi",
		.powew_off = meson_g12a_pwwc_vpu_powew_off,
		.powew_on = meson_g12a_pwwc_vpu_powew_on,
	},
};

static int meson_gx_pwwc_vpu_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_gx_pwwc_vpu *vpu_pd_match;
	stwuct wegmap *wegmap_ao, *wegmap_hhi;
	stwuct meson_gx_pwwc_vpu *vpu_pd;
	stwuct device_node *pawent_np;
	stwuct weset_contwow *wstc;
	stwuct cwk *vpu_cwk;
	stwuct cwk *vapb_cwk;
	boow powewed_off;
	int wet;

	vpu_pd_match = of_device_get_match_data(&pdev->dev);
	if (!vpu_pd_match) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	vpu_pd = devm_kzawwoc(&pdev->dev, sizeof(*vpu_pd), GFP_KEWNEW);
	if (!vpu_pd)
		wetuwn -ENOMEM;

	memcpy(vpu_pd, vpu_pd_match, sizeof(*vpu_pd));

	pawent_np = of_get_pawent(pdev->dev.of_node);
	wegmap_ao = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap_ao)) {
		dev_eww(&pdev->dev, "faiwed to get wegmap\n");
		wetuwn PTW_EWW(wegmap_ao);
	}

	wegmap_hhi = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						     "amwogic,hhi-sysctww");
	if (IS_EWW(wegmap_hhi)) {
		dev_eww(&pdev->dev, "faiwed to get HHI wegmap\n");
		wetuwn PTW_EWW(wegmap_hhi);
	}

	wstc = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wstc),
				     "faiwed to get weset wines\n");

	vpu_cwk = devm_cwk_get(&pdev->dev, "vpu");
	if (IS_EWW(vpu_cwk)) {
		dev_eww(&pdev->dev, "vpu cwock wequest faiwed\n");
		wetuwn PTW_EWW(vpu_cwk);
	}

	vapb_cwk = devm_cwk_get(&pdev->dev, "vapb");
	if (IS_EWW(vapb_cwk)) {
		dev_eww(&pdev->dev, "vapb cwock wequest faiwed\n");
		wetuwn PTW_EWW(vapb_cwk);
	}

	vpu_pd->wegmap_ao = wegmap_ao;
	vpu_pd->wegmap_hhi = wegmap_hhi;
	vpu_pd->wstc = wstc;
	vpu_pd->vpu_cwk = vpu_cwk;
	vpu_pd->vapb_cwk = vapb_cwk;

	pwatfowm_set_dwvdata(pdev, vpu_pd);

	powewed_off = meson_gx_pwwc_vpu_get_powew(vpu_pd);

	/* If awweady powewed, sync the cwock states */
	if (!powewed_off) {
		wet = meson_gx_pwwc_vpu_setup_cwk(vpu_pd);
		if (wet)
			wetuwn wet;
	}

	vpu_pd->genpd.fwags = GENPD_FWAG_AWWAYS_ON;
	pm_genpd_init(&vpu_pd->genpd, NUWW, powewed_off);

	wetuwn of_genpd_add_pwovidew_simpwe(pdev->dev.of_node,
					    &vpu_pd->genpd);
}

static void meson_gx_pwwc_vpu_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct meson_gx_pwwc_vpu *vpu_pd = pwatfowm_get_dwvdata(pdev);
	boow powewed_off;

	powewed_off = meson_gx_pwwc_vpu_get_powew(vpu_pd);
	if (!powewed_off)
		vpu_pd->genpd.powew_off(&vpu_pd->genpd);
}

static const stwuct of_device_id meson_gx_pwwc_vpu_match_tabwe[] = {
	{ .compatibwe = "amwogic,meson-gx-pwwc-vpu", .data = &vpu_hdmi_pd },
	{
	  .compatibwe = "amwogic,meson-g12a-pwwc-vpu",
	  .data = &vpu_hdmi_pd_g12a
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_gx_pwwc_vpu_match_tabwe);

static stwuct pwatfowm_dwivew meson_gx_pwwc_vpu_dwivew = {
	.pwobe	= meson_gx_pwwc_vpu_pwobe,
	.shutdown = meson_gx_pwwc_vpu_shutdown,
	.dwivew = {
		.name		= "meson_gx_pwwc_vpu",
		.of_match_tabwe	= meson_gx_pwwc_vpu_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_gx_pwwc_vpu_dwivew);
MODUWE_WICENSE("GPW v2");
