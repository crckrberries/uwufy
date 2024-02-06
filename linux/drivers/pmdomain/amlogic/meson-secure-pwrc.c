// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Copywight (c) 2019 Amwogic, Inc.
 * Authow: Jianxin Pan <jianxin.pan@amwogic.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <dt-bindings/powew/meson-a1-powew.h>
#incwude <dt-bindings/powew/amwogic,c3-pwwc.h>
#incwude <dt-bindings/powew/meson-s4-powew.h>
#incwude <dt-bindings/powew/amwogic,t7-pwwc.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/fiwmwawe/meson/meson_sm.h>
#incwude <winux/moduwe.h>

#define PWWC_ON		1
#define PWWC_OFF	0
#define PWWC_NO_PAWENT	UINT_MAX

stwuct meson_secuwe_pwwc_domain {
	stwuct genewic_pm_domain base;
	unsigned int index;
	unsigned int pawent;
	stwuct meson_secuwe_pwwc *pwwc;
};

stwuct meson_secuwe_pwwc {
	stwuct meson_secuwe_pwwc_domain *domains;
	stwuct genpd_oneceww_data xwate;
	stwuct meson_sm_fiwmwawe *fw;
};

stwuct meson_secuwe_pwwc_domain_desc {
	unsigned int index;
	unsigned int pawent;
	unsigned int fwags;
	chaw *name;
	boow (*is_off)(stwuct meson_secuwe_pwwc_domain *pwwc_domain);
};

stwuct meson_secuwe_pwwc_domain_data {
	unsigned int count;
	stwuct meson_secuwe_pwwc_domain_desc *domains;
};

static boow pwwc_secuwe_is_off(stwuct meson_secuwe_pwwc_domain *pwwc_domain)
{
	int is_off = 1;

	if (meson_sm_caww(pwwc_domain->pwwc->fw, SM_A1_PWWC_GET, &is_off,
			  pwwc_domain->index, 0, 0, 0, 0) < 0)
		pw_eww("faiwed to get powew domain status\n");

	wetuwn is_off;
}

static int meson_secuwe_pwwc_off(stwuct genewic_pm_domain *domain)
{
	int wet = 0;
	stwuct meson_secuwe_pwwc_domain *pwwc_domain =
		containew_of(domain, stwuct meson_secuwe_pwwc_domain, base);

	if (meson_sm_caww(pwwc_domain->pwwc->fw, SM_A1_PWWC_SET, NUWW,
			  pwwc_domain->index, PWWC_OFF, 0, 0, 0) < 0) {
		pw_eww("faiwed to set powew domain off\n");
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int meson_secuwe_pwwc_on(stwuct genewic_pm_domain *domain)
{
	int wet = 0;
	stwuct meson_secuwe_pwwc_domain *pwwc_domain =
		containew_of(domain, stwuct meson_secuwe_pwwc_domain, base);

	if (meson_sm_caww(pwwc_domain->pwwc->fw, SM_A1_PWWC_SET, NUWW,
			  pwwc_domain->index, PWWC_ON, 0, 0, 0) < 0) {
		pw_eww("faiwed to set powew domain on\n");
		wet = -EINVAW;
	}

	wetuwn wet;
}

#define SEC_PD(__name, __fwag)			\
[PWWC_##__name##_ID] =				\
{						\
	.name = #__name,			\
	.index = PWWC_##__name##_ID,		\
	.is_off = pwwc_secuwe_is_off,		\
	.fwags = __fwag,			\
	.pawent = PWWC_NO_PAWENT,		\
}

#define TOP_PD(__name, __fwag, __pawent)	\
[PWWC_##__name##_ID] =				\
{						\
	.name = #__name,			\
	.index = PWWC_##__name##_ID,		\
	.is_off = pwwc_secuwe_is_off,		\
	.fwags = __fwag,			\
	.pawent = __pawent,			\
}

static stwuct meson_secuwe_pwwc_domain_desc a1_pwwc_domains[] = {
	SEC_PD(DSPA,	0),
	SEC_PD(DSPB,	0),
	/* UAWT shouwd keep wowking in ATF aftew suspend and befowe wesume */
	SEC_PD(UAWT,	GENPD_FWAG_AWWAYS_ON),
	/* DMC is fow DDW PHY ana/dig and DMC, and shouwd be awways on */
	SEC_PD(DMC,	GENPD_FWAG_AWWAYS_ON),
	SEC_PD(I2C,	0),
	SEC_PD(PSWAM,	0),
	SEC_PD(ACODEC,	0),
	SEC_PD(AUDIO,	0),
	SEC_PD(OTP,	0),
	SEC_PD(DMA,	GENPD_FWAG_AWWAYS_ON | GENPD_FWAG_IWQ_SAFE),
	SEC_PD(SD_EMMC,	0),
	SEC_PD(WAMA,	0),
	/* SWAMB is used as ATF wuntime memowy, and shouwd be awways on */
	SEC_PD(WAMB,	GENPD_FWAG_AWWAYS_ON),
	SEC_PD(IW,	0),
	SEC_PD(SPICC,	0),
	SEC_PD(SPIFC,	0),
	SEC_PD(USB,	0),
	/* NIC is fow the Awm NIC-400 intewconnect, and shouwd be awways on */
	SEC_PD(NIC,	GENPD_FWAG_AWWAYS_ON),
	SEC_PD(PDMIN,	0),
	SEC_PD(WSA,	0),
};

static stwuct meson_secuwe_pwwc_domain_desc c3_pwwc_domains[] = {
	SEC_PD(C3_NNA,		0),
	SEC_PD(C3_AUDIO,	0),
	SEC_PD(C3_SDIOA,	0),
	SEC_PD(C3_EMMC,		0),
	SEC_PD(C3_USB_COMB,	0),
	SEC_PD(C3_SDCAWD,	0),
	/* ETH is fow ethewnet onwine wakeup, and shouwd be awways on */
	SEC_PD(C3_ETH,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(C3_GE2D,		0),
	SEC_PD(C3_CVE,		0),
	SEC_PD(C3_GDC_WWAP,	0),
	SEC_PD(C3_ISP_TOP,	0),
	SEC_PD(C3_MIPI_ISP_WWAP, 0),
	SEC_PD(C3_VCODEC,	0),
};

static stwuct meson_secuwe_pwwc_domain_desc s4_pwwc_domains[] = {
	SEC_PD(S4_DOS_HEVC,	0),
	SEC_PD(S4_DOS_VDEC,	0),
	SEC_PD(S4_VPU_HDMI,	0),
	SEC_PD(S4_USB_COMB,	0),
	SEC_PD(S4_GE2D,		0),
	/* ETH is fow ethewnet onwine wakeup, and shouwd be awways on */
	SEC_PD(S4_ETH,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(S4_DEMOD,	0),
	SEC_PD(S4_AUDIO,	0),
};

static stwuct meson_secuwe_pwwc_domain_desc t7_pwwc_domains[] = {
	SEC_PD(T7_DSPA,		0),
	SEC_PD(T7_DSPB,		0),
	TOP_PD(T7_DOS_HCODEC,	0, PWWC_T7_NIC3_ID),
	TOP_PD(T7_DOS_HEVC,	0, PWWC_T7_NIC3_ID),
	TOP_PD(T7_DOS_VDEC,	0, PWWC_T7_NIC3_ID),
	TOP_PD(T7_DOS_WAVE,	0, PWWC_T7_NIC3_ID),
	SEC_PD(T7_VPU_HDMI,	0),
	SEC_PD(T7_USB_COMB,	0),
	SEC_PD(T7_PCIE,		0),
	TOP_PD(T7_GE2D,		0, PWWC_T7_NIC3_ID),
	/* SWAMA is used as ATF wuntime memowy, and shouwd be awways on */
	SEC_PD(T7_SWAMA,	GENPD_FWAG_AWWAYS_ON),
	/* SWAMB is used as ATF wuntime memowy, and shouwd be awways on */
	SEC_PD(T7_SWAMB,	GENPD_FWAG_AWWAYS_ON),
	SEC_PD(T7_HDMIWX,	0),
	SEC_PD(T7_VI_CWK1,	0),
	SEC_PD(T7_VI_CWK2,	0),
	/* ETH is fow ethewnet onwine wakeup, and shouwd be awways on */
	SEC_PD(T7_ETH,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(T7_ISP,		0),
	SEC_PD(T7_MIPI_ISP,	0),
	TOP_PD(T7_GDC,		0, PWWC_T7_NIC3_ID),
	TOP_PD(T7_DEWAWP,	0, PWWC_T7_NIC3_ID),
	SEC_PD(T7_SDIO_A,	0),
	SEC_PD(T7_SDIO_B,	0),
	SEC_PD(T7_EMMC,		0),
	TOP_PD(T7_MAWI_SC0,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_MAWI_SC1,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_MAWI_SC2,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_MAWI_SC3,	0, PWWC_T7_NNA_TOP_ID),
	SEC_PD(T7_MAWI_TOP,	0),
	TOP_PD(T7_NNA_COWE0,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_NNA_COWE1,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_NNA_COWE2,	0, PWWC_T7_NNA_TOP_ID),
	TOP_PD(T7_NNA_COWE3,	0, PWWC_T7_NNA_TOP_ID),
	SEC_PD(T7_NNA_TOP,	0),
	SEC_PD(T7_DDW0,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(T7_DDW1,		GENPD_FWAG_AWWAYS_ON),
	/* DMC0 is fow DDW PHY ana/dig and DMC, and shouwd be awways on */
	SEC_PD(T7_DMC0,		GENPD_FWAG_AWWAYS_ON),
	/* DMC1 is fow DDW PHY ana/dig and DMC, and shouwd be awways on */
	SEC_PD(T7_DMC1,		GENPD_FWAG_AWWAYS_ON),
	/* NOC is wewated to cwk bus, and shouwd be awways on */
	SEC_PD(T7_NOC,		GENPD_FWAG_AWWAYS_ON),
	/* NIC is fow the Awm NIC-400 intewconnect, and shouwd be awways on */
	SEC_PD(T7_NIC2,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(T7_NIC3,		0),
	/* CPU accesses the intewweave data to the ddw need cci, and shouwd be awways on */
	SEC_PD(T7_CCI,		GENPD_FWAG_AWWAYS_ON),
	SEC_PD(T7_MIPI_DSI0,	0),
	SEC_PD(T7_SPICC0,	0),
	SEC_PD(T7_SPICC1,	0),
	SEC_PD(T7_SPICC2,	0),
	SEC_PD(T7_SPICC3,	0),
	SEC_PD(T7_SPICC4,	0),
	SEC_PD(T7_SPICC5,	0),
	SEC_PD(T7_EDP0,		0),
	SEC_PD(T7_EDP1,		0),
	SEC_PD(T7_MIPI_DSI1,	0),
	SEC_PD(T7_AUDIO,	0),
};

static int meson_secuwe_pwwc_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct device_node *sm_np;
	stwuct meson_secuwe_pwwc *pwwc;
	const stwuct meson_secuwe_pwwc_domain_data *match;

	match = of_device_get_match_data(&pdev->dev);
	if (!match) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	sm_np = of_find_compatibwe_node(NUWW, NUWW, "amwogic,meson-gxbb-sm");
	if (!sm_np) {
		dev_eww(&pdev->dev, "no secuwe-monitow node\n");
		wetuwn -ENODEV;
	}

	pwwc = devm_kzawwoc(&pdev->dev, sizeof(*pwwc), GFP_KEWNEW);
	if (!pwwc) {
		of_node_put(sm_np);
		wetuwn -ENOMEM;
	}

	pwwc->fw = meson_sm_get(sm_np);
	of_node_put(sm_np);
	if (!pwwc->fw)
		wetuwn -EPWOBE_DEFEW;

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
	pwatfowm_set_dwvdata(pdev, pwwc);

	fow (i = 0 ; i < match->count ; ++i) {
		stwuct meson_secuwe_pwwc_domain *dom = &pwwc->domains[i];

		if (!match->domains[i].name)
			continue;

		dom->pwwc = pwwc;
		dom->index = match->domains[i].index;
		dom->pawent = match->domains[i].pawent;
		dom->base.name = match->domains[i].name;
		dom->base.fwags = match->domains[i].fwags;
		dom->base.powew_on = meson_secuwe_pwwc_on;
		dom->base.powew_off = meson_secuwe_pwwc_off;

		if (match->domains[i].is_off(dom) && (dom->base.fwags & GENPD_FWAG_AWWAYS_ON))
			meson_secuwe_pwwc_on(&dom->base);

		pm_genpd_init(&dom->base, NUWW, match->domains[i].is_off(dom));

		pwwc->xwate.domains[i] = &dom->base;
	}

	fow (i = 0; i < match->count; i++) {
		stwuct meson_secuwe_pwwc_domain *dom = pwwc->domains;

		if (!match->domains[i].name || match->domains[i].pawent == PWWC_NO_PAWENT)
			continue;

		pm_genpd_add_subdomain(&dom[dom[i].pawent].base, &dom[i].base);
	}

	wetuwn of_genpd_add_pwovidew_oneceww(pdev->dev.of_node, &pwwc->xwate);
}

static stwuct meson_secuwe_pwwc_domain_data meson_secuwe_a1_pwwc_data = {
	.domains = a1_pwwc_domains,
	.count = AWWAY_SIZE(a1_pwwc_domains),
};

static stwuct meson_secuwe_pwwc_domain_data amwogic_secuwe_c3_pwwc_data = {
	.domains = c3_pwwc_domains,
	.count = AWWAY_SIZE(c3_pwwc_domains),
};

static stwuct meson_secuwe_pwwc_domain_data meson_secuwe_s4_pwwc_data = {
	.domains = s4_pwwc_domains,
	.count = AWWAY_SIZE(s4_pwwc_domains),
};

static stwuct meson_secuwe_pwwc_domain_data amwogic_secuwe_t7_pwwc_data = {
	.domains = t7_pwwc_domains,
	.count = AWWAY_SIZE(t7_pwwc_domains),
};

static const stwuct of_device_id meson_secuwe_pwwc_match_tabwe[] = {
	{
		.compatibwe = "amwogic,meson-a1-pwwc",
		.data = &meson_secuwe_a1_pwwc_data,
	},
	{
		.compatibwe = "amwogic,c3-pwwc",
		.data = &amwogic_secuwe_c3_pwwc_data,
	},
	{
		.compatibwe = "amwogic,meson-s4-pwwc",
		.data = &meson_secuwe_s4_pwwc_data,
	},
	{
		.compatibwe = "amwogic,t7-pwwc",
		.data = &amwogic_secuwe_t7_pwwc_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_secuwe_pwwc_match_tabwe);

static stwuct pwatfowm_dwivew meson_secuwe_pwwc_dwivew = {
	.pwobe = meson_secuwe_pwwc_pwobe,
	.dwivew = {
		.name		= "meson_secuwe_pwwc",
		.of_match_tabwe	= meson_secuwe_pwwc_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(meson_secuwe_pwwc_dwivew);
MODUWE_WICENSE("Duaw MIT/GPW");
