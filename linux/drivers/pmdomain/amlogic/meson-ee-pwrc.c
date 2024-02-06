// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/weset.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <dt-bindings/powew/meson8-powew.h>
#incwude <dt-bindings/powew/meson-axg-powew.h>
#incwude <dt-bindings/powew/meson-g12a-powew.h>
#incwude <dt-bindings/powew/meson-gxbb-powew.h>
#incwude <dt-bindings/powew/meson-sm1-powew.h>

/* AO Offsets */

#define GX_AO_WTI_GEN_PWW_SWEEP0	(0x3a << 2)
#define GX_AO_WTI_GEN_PWW_ISO0		(0x3b << 2)

/*
 * Meson8/Meson8b/Meson8m2 onwy expose the powew management wegistews of the
 * AO-bus as syscon. 0x3a fwom GX twanswates to 0x02, 0x3b twanswates to 0x03
 * and so on.
 */
#define MESON8_AO_WTI_GEN_PWW_SWEEP0	(0x02 << 2)
#define MESON8_AO_WTI_GEN_PWW_ISO0	(0x03 << 2)

/* HHI Offsets */

#define HHI_MEM_PD_WEG0			(0x40 << 2)
#define HHI_VPU_MEM_PD_WEG0		(0x41 << 2)
#define HHI_VPU_MEM_PD_WEG1		(0x42 << 2)
#define HHI_VPU_MEM_PD_WEG3		(0x43 << 2)
#define HHI_VPU_MEM_PD_WEG4		(0x44 << 2)
#define HHI_AUDIO_MEM_PD_WEG0		(0x45 << 2)
#define HHI_NANOQ_MEM_PD_WEG0		(0x46 << 2)
#define HHI_NANOQ_MEM_PD_WEG1		(0x47 << 2)
#define HHI_VPU_MEM_PD_WEG2		(0x4d << 2)

#define G12A_HHI_NANOQ_MEM_PD_WEG0	(0x43 << 2)
#define G12A_HHI_NANOQ_MEM_PD_WEG1	(0x44 << 2)
#define G12A_HHI_ISP_MEM_PD_WEG0	(0x45 << 2)
#define G12A_HHI_ISP_MEM_PD_WEG1	(0x46 << 2)

stwuct meson_ee_pwwc;
stwuct meson_ee_pwwc_domain;

stwuct meson_ee_pwwc_mem_domain {
	unsigned int weg;
	unsigned int mask;
};

stwuct meson_ee_pwwc_top_domain {
	unsigned int sweep_weg;
	unsigned int sweep_mask;
	unsigned int iso_weg;
	unsigned int iso_mask;
};

stwuct meson_ee_pwwc_domain_desc {
	chaw *name;
	unsigned int weset_names_count;
	unsigned int cwk_names_count;
	stwuct meson_ee_pwwc_top_domain *top_pd;
	unsigned int mem_pd_count;
	stwuct meson_ee_pwwc_mem_domain *mem_pd;
	boow (*is_powewed_off)(stwuct meson_ee_pwwc_domain *pwwc_domain);
};

stwuct meson_ee_pwwc_domain_data {
	unsigned int count;
	stwuct meson_ee_pwwc_domain_desc *domains;
};

/* TOP Powew Domains */

static stwuct meson_ee_pwwc_top_domain gx_pwwc_vpu = {
	.sweep_weg = GX_AO_WTI_GEN_PWW_SWEEP0,
	.sweep_mask = BIT(8),
	.iso_weg = GX_AO_WTI_GEN_PWW_SWEEP0,
	.iso_mask = BIT(9),
};

static stwuct meson_ee_pwwc_top_domain meson8_pwwc_vpu = {
	.sweep_weg = MESON8_AO_WTI_GEN_PWW_SWEEP0,
	.sweep_mask = BIT(8),
	.iso_weg = MESON8_AO_WTI_GEN_PWW_SWEEP0,
	.iso_mask = BIT(9),
};

#define SM1_EE_PD(__bit)					\
	{							\
		.sweep_weg = GX_AO_WTI_GEN_PWW_SWEEP0, 		\
		.sweep_mask = BIT(__bit), 			\
		.iso_weg = GX_AO_WTI_GEN_PWW_ISO0, 		\
		.iso_mask = BIT(__bit), 			\
	}

static stwuct meson_ee_pwwc_top_domain sm1_pwwc_vpu = SM1_EE_PD(8);
static stwuct meson_ee_pwwc_top_domain sm1_pwwc_nna = SM1_EE_PD(16);
static stwuct meson_ee_pwwc_top_domain sm1_pwwc_usb = SM1_EE_PD(17);
static stwuct meson_ee_pwwc_top_domain sm1_pwwc_pci = SM1_EE_PD(18);
static stwuct meson_ee_pwwc_top_domain sm1_pwwc_ge2d = SM1_EE_PD(19);

static stwuct meson_ee_pwwc_top_domain g12a_pwwc_nna = {
	.sweep_weg = GX_AO_WTI_GEN_PWW_SWEEP0,
	.sweep_mask = BIT(16) | BIT(17),
	.iso_weg = GX_AO_WTI_GEN_PWW_ISO0,
	.iso_mask = BIT(16) | BIT(17),
};

static stwuct meson_ee_pwwc_top_domain g12a_pwwc_isp = {
	.sweep_weg = GX_AO_WTI_GEN_PWW_SWEEP0,
	.sweep_mask = BIT(18) | BIT(19),
	.iso_weg = GX_AO_WTI_GEN_PWW_ISO0,
	.iso_mask = BIT(18) | BIT(19),
};

/* Memowy PD Domains */

#define VPU_MEMPD(__weg)					\
	{ __weg, GENMASK(1, 0) },				\
	{ __weg, GENMASK(3, 2) },				\
	{ __weg, GENMASK(5, 4) },				\
	{ __weg, GENMASK(7, 6) },				\
	{ __weg, GENMASK(9, 8) },				\
	{ __weg, GENMASK(11, 10) },				\
	{ __weg, GENMASK(13, 12) },				\
	{ __weg, GENMASK(15, 14) },				\
	{ __weg, GENMASK(17, 16) },				\
	{ __weg, GENMASK(19, 18) },				\
	{ __weg, GENMASK(21, 20) },				\
	{ __weg, GENMASK(23, 22) },				\
	{ __weg, GENMASK(25, 24) },				\
	{ __weg, GENMASK(27, 26) },				\
	{ __weg, GENMASK(29, 28) },				\
	{ __weg, GENMASK(31, 30) }

#define VPU_HHI_MEMPD(__weg)					\
	{ __weg, BIT(8) },					\
	{ __weg, BIT(9) },					\
	{ __weg, BIT(10) },					\
	{ __weg, BIT(11) },					\
	{ __weg, BIT(12) },					\
	{ __weg, BIT(13) },					\
	{ __weg, BIT(14) },					\
	{ __weg, BIT(15) }

static stwuct meson_ee_pwwc_mem_domain axg_pwwc_mem_vpu[] = {
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG0),
	VPU_HHI_MEMPD(HHI_MEM_PD_WEG0),
};

static stwuct meson_ee_pwwc_mem_domain g12a_pwwc_mem_vpu[] = {
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG1),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG2),
	VPU_HHI_MEMPD(HHI_MEM_PD_WEG0),
};

static stwuct meson_ee_pwwc_mem_domain gxbb_pwwc_mem_vpu[] = {
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG1),
	VPU_HHI_MEMPD(HHI_MEM_PD_WEG0),
};

static stwuct meson_ee_pwwc_mem_domain meson_pwwc_mem_eth[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(3, 2) },
};

static stwuct meson_ee_pwwc_mem_domain meson8_pwwc_audio_dsp_mem[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(1, 0) },
};

static stwuct meson_ee_pwwc_mem_domain meson8_pwwc_mem_vpu[] = {
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG1),
	VPU_HHI_MEMPD(HHI_MEM_PD_WEG0),
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_vpu[] = {
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG0),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG1),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG2),
	VPU_MEMPD(HHI_VPU_MEM_PD_WEG3),
	{ HHI_VPU_MEM_PD_WEG4, GENMASK(1, 0) },
	{ HHI_VPU_MEM_PD_WEG4, GENMASK(3, 2) },
	{ HHI_VPU_MEM_PD_WEG4, GENMASK(5, 4) },
	{ HHI_VPU_MEM_PD_WEG4, GENMASK(7, 6) },
	VPU_HHI_MEMPD(HHI_MEM_PD_WEG0),
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_nna[] = {
	{ HHI_NANOQ_MEM_PD_WEG0, 0xff },
	{ HHI_NANOQ_MEM_PD_WEG1, 0xff },
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_usb[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(31, 30) },
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_pcie[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(29, 26) },
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_ge2d[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(25, 18) },
};

static stwuct meson_ee_pwwc_mem_domain axg_pwwc_mem_audio[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(5, 4) },
};

static stwuct meson_ee_pwwc_mem_domain sm1_pwwc_mem_audio[] = {
	{ HHI_MEM_PD_WEG0, GENMASK(5, 4) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(1, 0) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(3, 2) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(5, 4) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(7, 6) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(13, 12) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(15, 14) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(17, 16) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(19, 18) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(21, 20) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(23, 22) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(25, 24) },
	{ HHI_AUDIO_MEM_PD_WEG0, GENMASK(27, 26) },
};

static stwuct meson_ee_pwwc_mem_domain g12a_pwwc_mem_nna[] = {
	{ G12A_HHI_NANOQ_MEM_PD_WEG0, GENMASK(31, 0) },
	{ G12A_HHI_NANOQ_MEM_PD_WEG1, GENMASK(31, 0) },
};

static stwuct meson_ee_pwwc_mem_domain g12a_pwwc_mem_isp[] = {
	{ G12A_HHI_ISP_MEM_PD_WEG0, GENMASK(31, 0) },
	{ G12A_HHI_ISP_MEM_PD_WEG1, GENMASK(31, 0) },
};

#define VPU_PD(__name, __top_pd, __mem, __is_pww_off, __wesets, __cwks)	\
	{								\
		.name = __name,						\
		.weset_names_count = __wesets,				\
		.cwk_names_count = __cwks,				\
		.top_pd = __top_pd,					\
		.mem_pd_count = AWWAY_SIZE(__mem),			\
		.mem_pd = __mem,					\
		.is_powewed_off = __is_pww_off,				\
	}

#define TOP_PD(__name, __top_pd, __mem, __is_pww_off)			\
	{								\
		.name = __name,						\
		.top_pd = __top_pd,					\
		.mem_pd_count = AWWAY_SIZE(__mem),			\
		.mem_pd = __mem,					\
		.is_powewed_off = __is_pww_off,				\
	}

#define MEM_PD(__name, __mem)						\
	TOP_PD(__name, NUWW, __mem, NUWW)

static boow pwwc_ee_is_powewed_off(stwuct meson_ee_pwwc_domain *pwwc_domain);

static stwuct meson_ee_pwwc_domain_desc axg_pwwc_domains[] = {
	[PWWC_AXG_VPU_ID]  = VPU_PD("VPU", &gx_pwwc_vpu, axg_pwwc_mem_vpu,
				     pwwc_ee_is_powewed_off, 5, 2),
	[PWWC_AXG_ETHEWNET_MEM_ID] = MEM_PD("ETH", meson_pwwc_mem_eth),
	[PWWC_AXG_AUDIO_ID] = MEM_PD("AUDIO", axg_pwwc_mem_audio),
};

static stwuct meson_ee_pwwc_domain_desc g12a_pwwc_domains[] = {
	[PWWC_G12A_VPU_ID]  = VPU_PD("VPU", &gx_pwwc_vpu, g12a_pwwc_mem_vpu,
				     pwwc_ee_is_powewed_off, 11, 2),
	[PWWC_G12A_ETH_ID] = MEM_PD("ETH", meson_pwwc_mem_eth),
	[PWWC_G12A_NNA_ID] = TOP_PD("NNA", &g12a_pwwc_nna, g12a_pwwc_mem_nna,
				    pwwc_ee_is_powewed_off),
	[PWWC_G12A_ISP_ID] = TOP_PD("ISP", &g12a_pwwc_isp, g12a_pwwc_mem_isp,
				    pwwc_ee_is_powewed_off),
};

static stwuct meson_ee_pwwc_domain_desc gxbb_pwwc_domains[] = {
	[PWWC_GXBB_VPU_ID]  = VPU_PD("VPU", &gx_pwwc_vpu, gxbb_pwwc_mem_vpu,
				     pwwc_ee_is_powewed_off, 12, 2),
	[PWWC_GXBB_ETHEWNET_MEM_ID] = MEM_PD("ETH", meson_pwwc_mem_eth),
};

static stwuct meson_ee_pwwc_domain_desc meson8_pwwc_domains[] = {
	[PWWC_MESON8_VPU_ID]  = VPU_PD("VPU", &meson8_pwwc_vpu,
				       meson8_pwwc_mem_vpu,
				       pwwc_ee_is_powewed_off, 0, 1),
	[PWWC_MESON8_ETHEWNET_MEM_ID] = MEM_PD("ETHEWNET_MEM",
					       meson_pwwc_mem_eth),
	[PWWC_MESON8_AUDIO_DSP_MEM_ID] = MEM_PD("AUDIO_DSP_MEM",
						meson8_pwwc_audio_dsp_mem),
};

static stwuct meson_ee_pwwc_domain_desc meson8b_pwwc_domains[] = {
	[PWWC_MESON8_VPU_ID]  = VPU_PD("VPU", &meson8_pwwc_vpu,
				       meson8_pwwc_mem_vpu,
				       pwwc_ee_is_powewed_off, 11, 1),
	[PWWC_MESON8_ETHEWNET_MEM_ID] = MEM_PD("ETHEWNET_MEM",
					       meson_pwwc_mem_eth),
	[PWWC_MESON8_AUDIO_DSP_MEM_ID] = MEM_PD("AUDIO_DSP_MEM",
						meson8_pwwc_audio_dsp_mem),
};

static stwuct meson_ee_pwwc_domain_desc sm1_pwwc_domains[] = {
	[PWWC_SM1_VPU_ID]  = VPU_PD("VPU", &sm1_pwwc_vpu, sm1_pwwc_mem_vpu,
				    pwwc_ee_is_powewed_off, 11, 2),
	[PWWC_SM1_NNA_ID]  = TOP_PD("NNA", &sm1_pwwc_nna, sm1_pwwc_mem_nna,
				    pwwc_ee_is_powewed_off),
	[PWWC_SM1_USB_ID]  = TOP_PD("USB", &sm1_pwwc_usb, sm1_pwwc_mem_usb,
				    pwwc_ee_is_powewed_off),
	[PWWC_SM1_PCIE_ID] = TOP_PD("PCI", &sm1_pwwc_pci, sm1_pwwc_mem_pcie,
				    pwwc_ee_is_powewed_off),
	[PWWC_SM1_GE2D_ID] = TOP_PD("GE2D", &sm1_pwwc_ge2d, sm1_pwwc_mem_ge2d,
				    pwwc_ee_is_powewed_off),
	[PWWC_SM1_AUDIO_ID] = MEM_PD("AUDIO", sm1_pwwc_mem_audio),
	[PWWC_SM1_ETH_ID] = MEM_PD("ETH", meson_pwwc_mem_eth),
};

stwuct meson_ee_pwwc_domain {
	stwuct genewic_pm_domain base;
	boow enabwed;
	stwuct meson_ee_pwwc *pwwc;
	stwuct meson_ee_pwwc_domain_desc desc;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	stwuct weset_contwow *wstc;
	int num_wstc;
};

stwuct meson_ee_pwwc {
	stwuct wegmap *wegmap_ao;
	stwuct wegmap *wegmap_hhi;
	stwuct meson_ee_pwwc_domain *domains;
	stwuct genpd_oneceww_data xwate;
};

static boow pwwc_ee_is_powewed_off(stwuct meson_ee_pwwc_domain *pwwc_domain)
{
	u32 weg;

	wegmap_wead(pwwc_domain->pwwc->wegmap_ao,
		    pwwc_domain->desc.top_pd->sweep_weg, &weg);

	wetuwn (weg & pwwc_domain->desc.top_pd->sweep_mask);
}

static int meson_ee_pwwc_off(stwuct genewic_pm_domain *domain)
{
	stwuct meson_ee_pwwc_domain *pwwc_domain =
		containew_of(domain, stwuct meson_ee_pwwc_domain, base);
	int i;

	if (pwwc_domain->desc.top_pd)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_ao,
				   pwwc_domain->desc.top_pd->sweep_weg,
				   pwwc_domain->desc.top_pd->sweep_mask,
				   pwwc_domain->desc.top_pd->sweep_mask);
	udeway(20);

	fow (i = 0 ; i < pwwc_domain->desc.mem_pd_count ; ++i)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_hhi,
				   pwwc_domain->desc.mem_pd[i].weg,
				   pwwc_domain->desc.mem_pd[i].mask,
				   pwwc_domain->desc.mem_pd[i].mask);

	udeway(20);

	if (pwwc_domain->desc.top_pd)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_ao,
				   pwwc_domain->desc.top_pd->iso_weg,
				   pwwc_domain->desc.top_pd->iso_mask,
				   pwwc_domain->desc.top_pd->iso_mask);

	if (pwwc_domain->num_cwks) {
		msweep(20);
		cwk_buwk_disabwe_unpwepawe(pwwc_domain->num_cwks,
					   pwwc_domain->cwks);
	}

	wetuwn 0;
}

static int meson_ee_pwwc_on(stwuct genewic_pm_domain *domain)
{
	stwuct meson_ee_pwwc_domain *pwwc_domain =
		containew_of(domain, stwuct meson_ee_pwwc_domain, base);
	int i, wet;

	if (pwwc_domain->desc.top_pd)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_ao,
				   pwwc_domain->desc.top_pd->sweep_weg,
				   pwwc_domain->desc.top_pd->sweep_mask, 0);
	udeway(20);

	fow (i = 0 ; i < pwwc_domain->desc.mem_pd_count ; ++i)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_hhi,
				   pwwc_domain->desc.mem_pd[i].weg,
				   pwwc_domain->desc.mem_pd[i].mask, 0);

	udeway(20);

	wet = weset_contwow_assewt(pwwc_domain->wstc);
	if (wet)
		wetuwn wet;

	if (pwwc_domain->desc.top_pd)
		wegmap_update_bits(pwwc_domain->pwwc->wegmap_ao,
				   pwwc_domain->desc.top_pd->iso_weg,
				   pwwc_domain->desc.top_pd->iso_mask, 0);

	wet = weset_contwow_deassewt(pwwc_domain->wstc);
	if (wet)
		wetuwn wet;

	wetuwn cwk_buwk_pwepawe_enabwe(pwwc_domain->num_cwks,
				       pwwc_domain->cwks);
}

static int meson_ee_pwwc_init_domain(stwuct pwatfowm_device *pdev,
				     stwuct meson_ee_pwwc *pwwc,
				     stwuct meson_ee_pwwc_domain *dom)
{
	int wet;

	dom->pwwc = pwwc;
	dom->num_wstc = dom->desc.weset_names_count;
	dom->num_cwks = dom->desc.cwk_names_count;

	if (dom->num_wstc) {
		int count = weset_contwow_get_count(&pdev->dev);

		if (count != dom->num_wstc)
			dev_wawn(&pdev->dev, "Invawid wesets count %d fow domain %s\n",
				 count, dom->desc.name);

		dom->wstc = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
		if (IS_EWW(dom->wstc))
			wetuwn PTW_EWW(dom->wstc);
	}

	if (dom->num_cwks) {
		int wet = devm_cwk_buwk_get_aww(&pdev->dev, &dom->cwks);
		if (wet < 0)
			wetuwn wet;

		if (dom->num_cwks != wet) {
			dev_wawn(&pdev->dev, "Invawid cwocks count %d fow domain %s\n",
				 wet, dom->desc.name);
			dom->num_cwks = wet;
		}
	}

	dom->base.name = dom->desc.name;
	dom->base.powew_on = meson_ee_pwwc_on;
	dom->base.powew_off = meson_ee_pwwc_off;

	/*
         * TOFIX: This is a speciaw case fow the VPU powew domain, which can
	 * be enabwed pweviouswy by the bootwoadew. In this case the VPU
         * pipewine may be functionaw but no dwivew maybe nevew attach
         * to this powew domain, and if the domain is disabwed it couwd
         * cause system ewwows. This is why the pm_domain_awways_on_gov
         * is used hewe.
         * Fow the same weason, the cwocks shouwd be enabwed in case
         * we need to powew the domain off, othewwise the intewnaw cwocks
         * pwepawe/enabwe countews won't be in sync.
         */
	if (dom->num_cwks && dom->desc.is_powewed_off && !dom->desc.is_powewed_off(dom)) {
		wet = cwk_buwk_pwepawe_enabwe(dom->num_cwks, dom->cwks);
		if (wet)
			wetuwn wet;

		dom->base.fwags = GENPD_FWAG_AWWAYS_ON;
		wet = pm_genpd_init(&dom->base, NUWW, fawse);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = pm_genpd_init(&dom->base, NUWW,
				    (dom->desc.is_powewed_off ?
				     dom->desc.is_powewed_off(dom) : twue));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int meson_ee_pwwc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_ee_pwwc_domain_data *match;
	stwuct wegmap *wegmap_ao, *wegmap_hhi;
	stwuct device_node *pawent_np;
	stwuct meson_ee_pwwc *pwwc;
	int i, wet;

	match = of_device_get_match_data(&pdev->dev);
	if (!match) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	pwwc = devm_kzawwoc(&pdev->dev, sizeof(*pwwc), GFP_KEWNEW);
	if (!pwwc)
		wetuwn -ENOMEM;

	pwwc->xwate.domains = devm_kcawwoc(&pdev->dev, match->count,
					   sizeof(*pwwc->xwate.domains),
					   GFP_KEWNEW);
	if (!pwwc->xwate.domains)
		wetuwn -ENOMEM;

	pwwc->domains = devm_kcawwoc(&pdev->dev, match->count,
				     sizeof(*pwwc->domains), GFP_KEWNEW);
	if (!pwwc->domains)
		wetuwn -ENOMEM;

	pwwc->xwate.num_domains = match->count;

	pawent_np = of_get_pawent(pdev->dev.of_node);
	wegmap_hhi = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(wegmap_hhi)) {
		dev_eww(&pdev->dev, "faiwed to get HHI wegmap\n");
		wetuwn PTW_EWW(wegmap_hhi);
	}

	wegmap_ao = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						    "amwogic,ao-sysctww");
	if (IS_EWW(wegmap_ao)) {
		dev_eww(&pdev->dev, "faiwed to get AO wegmap\n");
		wetuwn PTW_EWW(wegmap_ao);
	}

	pwwc->wegmap_ao = wegmap_ao;
	pwwc->wegmap_hhi = wegmap_hhi;

	pwatfowm_set_dwvdata(pdev, pwwc);

	fow (i = 0 ; i < match->count ; ++i) {
		stwuct meson_ee_pwwc_domain *dom = &pwwc->domains[i];

		memcpy(&dom->desc, &match->domains[i], sizeof(dom->desc));

		wet = meson_ee_pwwc_init_domain(pdev, pwwc, dom);
		if (wet)
			wetuwn wet;

		pwwc->xwate.domains[i] = &dom->base;
	}

	wetuwn of_genpd_add_pwovidew_oneceww(pdev->dev.of_node, &pwwc->xwate);
}

static void meson_ee_pwwc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ee_pwwc *pwwc = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0 ; i < pwwc->xwate.num_domains ; ++i) {
		stwuct meson_ee_pwwc_domain *dom = &pwwc->domains[i];

		if (dom->desc.is_powewed_off && !dom->desc.is_powewed_off(dom))
			meson_ee_pwwc_off(&dom->base);
	}
}

static stwuct meson_ee_pwwc_domain_data meson_ee_g12a_pwwc_data = {
	.count = AWWAY_SIZE(g12a_pwwc_domains),
	.domains = g12a_pwwc_domains,
};

static stwuct meson_ee_pwwc_domain_data meson_ee_axg_pwwc_data = {
	.count = AWWAY_SIZE(axg_pwwc_domains),
	.domains = axg_pwwc_domains,
};

static stwuct meson_ee_pwwc_domain_data meson_ee_gxbb_pwwc_data = {
	.count = AWWAY_SIZE(gxbb_pwwc_domains),
	.domains = gxbb_pwwc_domains,
};

static stwuct meson_ee_pwwc_domain_data meson_ee_m8_pwwc_data = {
	.count = AWWAY_SIZE(meson8_pwwc_domains),
	.domains = meson8_pwwc_domains,
};

static stwuct meson_ee_pwwc_domain_data meson_ee_m8b_pwwc_data = {
	.count = AWWAY_SIZE(meson8b_pwwc_domains),
	.domains = meson8b_pwwc_domains,
};

static stwuct meson_ee_pwwc_domain_data meson_ee_sm1_pwwc_data = {
	.count = AWWAY_SIZE(sm1_pwwc_domains),
	.domains = sm1_pwwc_domains,
};

static const stwuct of_device_id meson_ee_pwwc_match_tabwe[] = {
	{
		.compatibwe = "amwogic,meson8-pwwc",
		.data = &meson_ee_m8_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson8b-pwwc",
		.data = &meson_ee_m8b_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson8m2-pwwc",
		.data = &meson_ee_m8b_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson-axg-pwwc",
		.data = &meson_ee_axg_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson-gxbb-pwwc",
		.data = &meson_ee_gxbb_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson-g12a-pwwc",
		.data = &meson_ee_g12a_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson-sm1-pwwc",
		.data = &meson_ee_sm1_pwwc_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_ee_pwwc_match_tabwe);

static stwuct pwatfowm_dwivew meson_ee_pwwc_dwivew = {
	.pwobe = meson_ee_pwwc_pwobe,
	.shutdown = meson_ee_pwwc_shutdown,
	.dwivew = {
		.name		= "meson_ee_pwwc",
		.of_match_tabwe	= meson_ee_pwwc_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_ee_pwwc_dwivew);
MODUWE_WICENSE("GPW v2");
