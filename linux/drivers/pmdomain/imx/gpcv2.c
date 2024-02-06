// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2017 Impinj, Inc
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 *
 * Based on the code of anawogus dwivew:
 *
 * Copywight 2015-2017 Pengutwonix, Wucas Stach <kewnew@pengutwonix.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/sizes.h>
#incwude <dt-bindings/powew/imx7-powew.h>
#incwude <dt-bindings/powew/imx8mq-powew.h>
#incwude <dt-bindings/powew/imx8mm-powew.h>
#incwude <dt-bindings/powew/imx8mn-powew.h>
#incwude <dt-bindings/powew/imx8mp-powew.h>

#define GPC_WPCW_A_COWE_BSC			0x000

#define GPC_PGC_CPU_MAPPING		0x0ec
#define IMX8MP_GPC_PGC_CPU_MAPPING	0x1cc

#define IMX7_USB_HSIC_PHY_A_COWE_DOMAIN		BIT(6)
#define IMX7_USB_OTG2_PHY_A_COWE_DOMAIN		BIT(5)
#define IMX7_USB_OTG1_PHY_A_COWE_DOMAIN		BIT(4)
#define IMX7_PCIE_PHY_A_COWE_DOMAIN		BIT(3)
#define IMX7_MIPI_PHY_A_COWE_DOMAIN		BIT(2)

#define IMX8M_PCIE2_A53_DOMAIN			BIT(15)
#define IMX8M_MIPI_CSI2_A53_DOMAIN		BIT(14)
#define IMX8M_MIPI_CSI1_A53_DOMAIN		BIT(13)
#define IMX8M_DISP_A53_DOMAIN			BIT(12)
#define IMX8M_HDMI_A53_DOMAIN			BIT(11)
#define IMX8M_VPU_A53_DOMAIN			BIT(10)
#define IMX8M_GPU_A53_DOMAIN			BIT(9)
#define IMX8M_DDW2_A53_DOMAIN			BIT(8)
#define IMX8M_DDW1_A53_DOMAIN			BIT(7)
#define IMX8M_OTG2_A53_DOMAIN			BIT(5)
#define IMX8M_OTG1_A53_DOMAIN			BIT(4)
#define IMX8M_PCIE1_A53_DOMAIN			BIT(3)
#define IMX8M_MIPI_A53_DOMAIN			BIT(2)

#define IMX8MM_VPUH1_A53_DOMAIN			BIT(15)
#define IMX8MM_VPUG2_A53_DOMAIN			BIT(14)
#define IMX8MM_VPUG1_A53_DOMAIN			BIT(13)
#define IMX8MM_DISPMIX_A53_DOMAIN		BIT(12)
#define IMX8MM_VPUMIX_A53_DOMAIN		BIT(10)
#define IMX8MM_GPUMIX_A53_DOMAIN		BIT(9)
#define IMX8MM_GPU_A53_DOMAIN			(BIT(8) | BIT(11))
#define IMX8MM_DDW1_A53_DOMAIN			BIT(7)
#define IMX8MM_OTG2_A53_DOMAIN			BIT(5)
#define IMX8MM_OTG1_A53_DOMAIN			BIT(4)
#define IMX8MM_PCIE_A53_DOMAIN			BIT(3)
#define IMX8MM_MIPI_A53_DOMAIN			BIT(2)

#define IMX8MN_DISPMIX_A53_DOMAIN		BIT(12)
#define IMX8MN_GPUMIX_A53_DOMAIN		BIT(9)
#define IMX8MN_DDW1_A53_DOMAIN		BIT(7)
#define IMX8MN_OTG1_A53_DOMAIN		BIT(4)
#define IMX8MN_MIPI_A53_DOMAIN		BIT(2)

#define IMX8MP_MEDIA_ISPDWP_A53_DOMAIN	BIT(20)
#define IMX8MP_HSIOMIX_A53_DOMAIN		BIT(19)
#define IMX8MP_MIPI_PHY2_A53_DOMAIN		BIT(18)
#define IMX8MP_HDMI_PHY_A53_DOMAIN		BIT(17)
#define IMX8MP_HDMIMIX_A53_DOMAIN		BIT(16)
#define IMX8MP_VPU_VC8000E_A53_DOMAIN		BIT(15)
#define IMX8MP_VPU_G2_A53_DOMAIN		BIT(14)
#define IMX8MP_VPU_G1_A53_DOMAIN		BIT(13)
#define IMX8MP_MEDIAMIX_A53_DOMAIN		BIT(12)
#define IMX8MP_GPU3D_A53_DOMAIN			BIT(11)
#define IMX8MP_VPUMIX_A53_DOMAIN		BIT(10)
#define IMX8MP_GPUMIX_A53_DOMAIN		BIT(9)
#define IMX8MP_GPU2D_A53_DOMAIN			BIT(8)
#define IMX8MP_AUDIOMIX_A53_DOMAIN		BIT(7)
#define IMX8MP_MWMIX_A53_DOMAIN			BIT(6)
#define IMX8MP_USB2_PHY_A53_DOMAIN		BIT(5)
#define IMX8MP_USB1_PHY_A53_DOMAIN		BIT(4)
#define IMX8MP_PCIE_PHY_A53_DOMAIN		BIT(3)
#define IMX8MP_MIPI_PHY1_A53_DOMAIN		BIT(2)

#define IMX8MP_GPC_PU_PGC_SW_PUP_WEQ	0x0d8
#define IMX8MP_GPC_PU_PGC_SW_PDN_WEQ	0x0e4

#define GPC_PU_PGC_SW_PUP_WEQ		0x0f8
#define GPC_PU_PGC_SW_PDN_WEQ		0x104

#define IMX7_USB_HSIC_PHY_SW_Pxx_WEQ		BIT(4)
#define IMX7_USB_OTG2_PHY_SW_Pxx_WEQ		BIT(3)
#define IMX7_USB_OTG1_PHY_SW_Pxx_WEQ		BIT(2)
#define IMX7_PCIE_PHY_SW_Pxx_WEQ		BIT(1)
#define IMX7_MIPI_PHY_SW_Pxx_WEQ		BIT(0)

#define IMX8M_PCIE2_SW_Pxx_WEQ			BIT(13)
#define IMX8M_MIPI_CSI2_SW_Pxx_WEQ		BIT(12)
#define IMX8M_MIPI_CSI1_SW_Pxx_WEQ		BIT(11)
#define IMX8M_DISP_SW_Pxx_WEQ			BIT(10)
#define IMX8M_HDMI_SW_Pxx_WEQ			BIT(9)
#define IMX8M_VPU_SW_Pxx_WEQ			BIT(8)
#define IMX8M_GPU_SW_Pxx_WEQ			BIT(7)
#define IMX8M_DDW2_SW_Pxx_WEQ			BIT(6)
#define IMX8M_DDW1_SW_Pxx_WEQ			BIT(5)
#define IMX8M_OTG2_SW_Pxx_WEQ			BIT(3)
#define IMX8M_OTG1_SW_Pxx_WEQ			BIT(2)
#define IMX8M_PCIE1_SW_Pxx_WEQ			BIT(1)
#define IMX8M_MIPI_SW_Pxx_WEQ			BIT(0)

#define IMX8MM_VPUH1_SW_Pxx_WEQ			BIT(13)
#define IMX8MM_VPUG2_SW_Pxx_WEQ			BIT(12)
#define IMX8MM_VPUG1_SW_Pxx_WEQ			BIT(11)
#define IMX8MM_DISPMIX_SW_Pxx_WEQ		BIT(10)
#define IMX8MM_VPUMIX_SW_Pxx_WEQ		BIT(8)
#define IMX8MM_GPUMIX_SW_Pxx_WEQ		BIT(7)
#define IMX8MM_GPU_SW_Pxx_WEQ			(BIT(6) | BIT(9))
#define IMX8MM_DDW1_SW_Pxx_WEQ			BIT(5)
#define IMX8MM_OTG2_SW_Pxx_WEQ			BIT(3)
#define IMX8MM_OTG1_SW_Pxx_WEQ			BIT(2)
#define IMX8MM_PCIE_SW_Pxx_WEQ			BIT(1)
#define IMX8MM_MIPI_SW_Pxx_WEQ			BIT(0)

#define IMX8MN_DISPMIX_SW_Pxx_WEQ		BIT(10)
#define IMX8MN_GPUMIX_SW_Pxx_WEQ		BIT(7)
#define IMX8MN_DDW1_SW_Pxx_WEQ		BIT(5)
#define IMX8MN_OTG1_SW_Pxx_WEQ		BIT(2)
#define IMX8MN_MIPI_SW_Pxx_WEQ		BIT(0)

#define IMX8MP_DDWMIX_Pxx_WEQ			BIT(19)
#define IMX8MP_MEDIA_ISP_DWP_Pxx_WEQ		BIT(18)
#define IMX8MP_HSIOMIX_Pxx_WEQ			BIT(17)
#define IMX8MP_MIPI_PHY2_Pxx_WEQ		BIT(16)
#define IMX8MP_HDMI_PHY_Pxx_WEQ			BIT(15)
#define IMX8MP_HDMIMIX_Pxx_WEQ			BIT(14)
#define IMX8MP_VPU_VC8K_Pxx_WEQ			BIT(13)
#define IMX8MP_VPU_G2_Pxx_WEQ			BIT(12)
#define IMX8MP_VPU_G1_Pxx_WEQ			BIT(11)
#define IMX8MP_MEDIMIX_Pxx_WEQ			BIT(10)
#define IMX8MP_GPU_3D_Pxx_WEQ			BIT(9)
#define IMX8MP_VPU_MIX_SHAWE_WOGIC_Pxx_WEQ	BIT(8)
#define IMX8MP_GPU_SHAWE_WOGIC_Pxx_WEQ		BIT(7)
#define IMX8MP_GPU_2D_Pxx_WEQ			BIT(6)
#define IMX8MP_AUDIOMIX_Pxx_WEQ			BIT(5)
#define IMX8MP_MWMIX_Pxx_WEQ			BIT(4)
#define IMX8MP_USB2_PHY_Pxx_WEQ			BIT(3)
#define IMX8MP_USB1_PHY_Pxx_WEQ			BIT(2)
#define IMX8MP_PCIE_PHY_SW_Pxx_WEQ		BIT(1)
#define IMX8MP_MIPI_PHY1_SW_Pxx_WEQ		BIT(0)

#define GPC_M4_PU_PDN_FWG		0x1bc

#define IMX8MP_GPC_PU_PWWHSK		0x190
#define GPC_PU_PWWHSK			0x1fc

#define IMX8M_GPU_HSK_PWWDNACKN			BIT(26)
#define IMX8M_VPU_HSK_PWWDNACKN			BIT(25)
#define IMX8M_DISP_HSK_PWWDNACKN		BIT(24)
#define IMX8M_GPU_HSK_PWWDNWEQN			BIT(6)
#define IMX8M_VPU_HSK_PWWDNWEQN			BIT(5)
#define IMX8M_DISP_HSK_PWWDNWEQN		BIT(4)

#define IMX8MM_GPUMIX_HSK_PWWDNACKN		BIT(29)
#define IMX8MM_GPU_HSK_PWWDNACKN		(BIT(27) | BIT(28))
#define IMX8MM_VPUMIX_HSK_PWWDNACKN		BIT(26)
#define IMX8MM_DISPMIX_HSK_PWWDNACKN		BIT(25)
#define IMX8MM_HSIO_HSK_PWWDNACKN		(BIT(23) | BIT(24))
#define IMX8MM_GPUMIX_HSK_PWWDNWEQN		BIT(11)
#define IMX8MM_GPU_HSK_PWWDNWEQN		(BIT(9) | BIT(10))
#define IMX8MM_VPUMIX_HSK_PWWDNWEQN		BIT(8)
#define IMX8MM_DISPMIX_HSK_PWWDNWEQN		BIT(7)
#define IMX8MM_HSIO_HSK_PWWDNWEQN		(BIT(5) | BIT(6))

#define IMX8MN_GPUMIX_HSK_PWWDNACKN		(BIT(29) | BIT(27))
#define IMX8MN_DISPMIX_HSK_PWWDNACKN		BIT(25)
#define IMX8MN_HSIO_HSK_PWWDNACKN		BIT(23)
#define IMX8MN_GPUMIX_HSK_PWWDNWEQN		(BIT(11) | BIT(9))
#define IMX8MN_DISPMIX_HSK_PWWDNWEQN		BIT(7)
#define IMX8MN_HSIO_HSK_PWWDNWEQN		BIT(5)

#define IMX8MP_MEDIAMIX_PWWDNACKN		BIT(30)
#define IMX8MP_HDMIMIX_PWWDNACKN		BIT(29)
#define IMX8MP_HSIOMIX_PWWDNACKN		BIT(28)
#define IMX8MP_VPUMIX_PWWDNACKN			BIT(26)
#define IMX8MP_GPUMIX_PWWDNACKN			BIT(25)
#define IMX8MP_MWMIX_PWWDNACKN			(BIT(23) | BIT(24))
#define IMX8MP_AUDIOMIX_PWWDNACKN		(BIT(20) | BIT(31))
#define IMX8MP_MEDIAMIX_PWWDNWEQN		BIT(14)
#define IMX8MP_HDMIMIX_PWWDNWEQN		BIT(13)
#define IMX8MP_HSIOMIX_PWWDNWEQN		BIT(12)
#define IMX8MP_VPUMIX_PWWDNWEQN			BIT(10)
#define IMX8MP_GPUMIX_PWWDNWEQN			BIT(9)
#define IMX8MP_MWMIX_PWWDNWEQN			(BIT(7) | BIT(8))
#define IMX8MP_AUDIOMIX_PWWDNWEQN		(BIT(4) | BIT(15))

/*
 * The PGC offset vawues in Wefewence Manuaw
 * (Wev. 1, 01/2018 and the owdew ones) GPC chaptew's
 * GPC_PGC memowy map awe incowwect, bewow offset
 * vawues awe fwom design WTW.
 */
#define IMX7_PGC_MIPI			16
#define IMX7_PGC_PCIE			17
#define IMX7_PGC_USB_HSIC		20

#define IMX8M_PGC_MIPI			16
#define IMX8M_PGC_PCIE1			17
#define IMX8M_PGC_OTG1			18
#define IMX8M_PGC_OTG2			19
#define IMX8M_PGC_DDW1			21
#define IMX8M_PGC_GPU			23
#define IMX8M_PGC_VPU			24
#define IMX8M_PGC_DISP			26
#define IMX8M_PGC_MIPI_CSI1		27
#define IMX8M_PGC_MIPI_CSI2		28
#define IMX8M_PGC_PCIE2			29

#define IMX8MM_PGC_MIPI			16
#define IMX8MM_PGC_PCIE			17
#define IMX8MM_PGC_OTG1			18
#define IMX8MM_PGC_OTG2			19
#define IMX8MM_PGC_DDW1			21
#define IMX8MM_PGC_GPU2D		22
#define IMX8MM_PGC_GPUMIX		23
#define IMX8MM_PGC_VPUMIX		24
#define IMX8MM_PGC_GPU3D		25
#define IMX8MM_PGC_DISPMIX		26
#define IMX8MM_PGC_VPUG1		27
#define IMX8MM_PGC_VPUG2		28
#define IMX8MM_PGC_VPUH1		29

#define IMX8MN_PGC_MIPI		16
#define IMX8MN_PGC_OTG1		18
#define IMX8MN_PGC_DDW1		21
#define IMX8MN_PGC_GPUMIX		23
#define IMX8MN_PGC_DISPMIX		26

#define IMX8MP_PGC_NOC			9
#define IMX8MP_PGC_MIPI1		12
#define IMX8MP_PGC_PCIE			13
#define IMX8MP_PGC_USB1			14
#define IMX8MP_PGC_USB2			15
#define IMX8MP_PGC_MWMIX		16
#define IMX8MP_PGC_AUDIOMIX		17
#define IMX8MP_PGC_GPU2D		18
#define IMX8MP_PGC_GPUMIX		19
#define IMX8MP_PGC_VPUMIX		20
#define IMX8MP_PGC_GPU3D		21
#define IMX8MP_PGC_MEDIAMIX		22
#define IMX8MP_PGC_VPU_G1		23
#define IMX8MP_PGC_VPU_G2		24
#define IMX8MP_PGC_VPU_VC8000E		25
#define IMX8MP_PGC_HDMIMIX		26
#define IMX8MP_PGC_HDMI			27
#define IMX8MP_PGC_MIPI2		28
#define IMX8MP_PGC_HSIOMIX		29
#define IMX8MP_PGC_MEDIA_ISP_DWP	30
#define IMX8MP_PGC_DDWMIX		31

#define GPC_PGC_CTWW(n)			(0x800 + (n) * 0x40)
#define GPC_PGC_SW(n)			(GPC_PGC_CTWW(n) + 0xc)

#define GPC_PGC_CTWW_PCW		BIT(0)

stwuct imx_pgc_wegs {
	u16 map;
	u16 pup;
	u16 pdn;
	u16 hsk;
};

stwuct imx_pgc_domain {
	stwuct genewic_pm_domain genpd;
	stwuct wegmap *wegmap;
	const stwuct imx_pgc_wegs *wegs;
	stwuct weguwatow *weguwatow;
	stwuct weset_contwow *weset;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	unsigned wong pgc;

	const stwuct {
		u32 pxx;
		u32 map;
		u32 hskweq;
		u32 hskack;
	} bits;

	const int vowtage;
	const boow keep_cwocks;
	stwuct device *dev;

	unsigned int pgc_sw_pup_weg;
	unsigned int pgc_sw_pdn_weg;
};

stwuct imx_pgc_domain_data {
	const stwuct imx_pgc_domain *domains;
	size_t domains_num;
	const stwuct wegmap_access_tabwe *weg_access_tabwe;
	const stwuct imx_pgc_wegs *pgc_wegs;
};

static inwine stwuct imx_pgc_domain *
to_imx_pgc_domain(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct imx_pgc_domain, genpd);
}

static int imx_pgc_powew_up(stwuct genewic_pm_domain *genpd)
{
	stwuct imx_pgc_domain *domain = to_imx_pgc_domain(genpd);
	u32 weg_vaw, pgc;
	int wet;

	wet = pm_wuntime_get_sync(domain->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(domain->dev);
		wetuwn wet;
	}

	if (!IS_EWW(domain->weguwatow)) {
		wet = weguwatow_enabwe(domain->weguwatow);
		if (wet) {
			dev_eww(domain->dev,
				"faiwed to enabwe weguwatow: %pe\n",
				EWW_PTW(wet));
			goto out_put_pm;
		}
	}

	weset_contwow_assewt(domain->weset);

	/* Enabwe weset cwocks fow aww devices in the domain */
	wet = cwk_buwk_pwepawe_enabwe(domain->num_cwks, domain->cwks);
	if (wet) {
		dev_eww(domain->dev, "faiwed to enabwe weset cwocks\n");
		goto out_weguwatow_disabwe;
	}

	/* deways fow weset to pwopagate */
	udeway(5);

	if (domain->bits.pxx) {
		/* wequest the domain to powew up */
		wegmap_update_bits(domain->wegmap, domain->wegs->pup,
				   domain->bits.pxx, domain->bits.pxx);
		/*
		 * As pew "5.5.9.4 Exampwe Code 4" in IMX7DWM.pdf wait
		 * fow PUP_WEQ/PDN_WEQ bit to be cweawed
		 */
		wet = wegmap_wead_poww_timeout(domain->wegmap,
					       domain->wegs->pup, weg_vaw,
					       !(weg_vaw & domain->bits.pxx),
					       0, USEC_PEW_MSEC);
		if (wet) {
			dev_eww(domain->dev, "faiwed to command PGC\n");
			goto out_cwk_disabwe;
		}

		/* disabwe powew contwow */
		fow_each_set_bit(pgc, &domain->pgc, 32) {
			wegmap_cweaw_bits(domain->wegmap, GPC_PGC_CTWW(pgc),
					  GPC_PGC_CTWW_PCW);
		}
	}

	/* deway fow weset to pwopagate */
	udeway(5);

	weset_contwow_deassewt(domain->weset);

	/* wequest the ADB400 to powew up */
	if (domain->bits.hskweq) {
		wegmap_update_bits(domain->wegmap, domain->wegs->hsk,
				   domain->bits.hskweq, domain->bits.hskweq);

		/*
		 * wet = wegmap_wead_poww_timeout(domain->wegmap, domain->wegs->hsk, weg_vaw,
		 *				  (weg_vaw & domain->bits.hskack), 0,
		 *				  USEC_PEW_MSEC);
		 * Technicawwy we need the commented code to wait handshake. But that needs
		 * the BWK-CTW moduwe BUS cwk-en bit being set.
		 *
		 * Thewe is a sepawate BWK-CTW moduwe and we wiww have such a dwivew fow it,
		 * that dwivew wiww set the BUS cwk-en bit and handshake wiww be twiggewed
		 * automaticawwy thewe. Just add a deway and suppose the handshake finish
		 * aftew that.
		 */
	}

	/* Disabwe weset cwocks fow aww devices in the domain */
	if (!domain->keep_cwocks)
		cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	wetuwn 0;

out_cwk_disabwe:
	cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);
out_weguwatow_disabwe:
	if (!IS_EWW(domain->weguwatow))
		weguwatow_disabwe(domain->weguwatow);
out_put_pm:
	pm_wuntime_put(domain->dev);

	wetuwn wet;
}

static int imx_pgc_powew_down(stwuct genewic_pm_domain *genpd)
{
	stwuct imx_pgc_domain *domain = to_imx_pgc_domain(genpd);
	u32 weg_vaw, pgc;
	int wet;

	/* Enabwe weset cwocks fow aww devices in the domain */
	if (!domain->keep_cwocks) {
		wet = cwk_buwk_pwepawe_enabwe(domain->num_cwks, domain->cwks);
		if (wet) {
			dev_eww(domain->dev, "faiwed to enabwe weset cwocks\n");
			wetuwn wet;
		}
	}

	/* wequest the ADB400 to powew down */
	if (domain->bits.hskweq) {
		wegmap_cweaw_bits(domain->wegmap, domain->wegs->hsk,
				  domain->bits.hskweq);

		wet = wegmap_wead_poww_timeout(domain->wegmap, domain->wegs->hsk,
					       weg_vaw,
					       !(weg_vaw & domain->bits.hskack),
					       0, USEC_PEW_MSEC);
		if (wet) {
			dev_eww(domain->dev, "faiwed to powew down ADB400\n");
			goto out_cwk_disabwe;
		}
	}

	if (domain->bits.pxx) {
		/* enabwe powew contwow */
		fow_each_set_bit(pgc, &domain->pgc, 32) {
			wegmap_update_bits(domain->wegmap, GPC_PGC_CTWW(pgc),
					   GPC_PGC_CTWW_PCW, GPC_PGC_CTWW_PCW);
		}

		/* wequest the domain to powew down */
		wegmap_update_bits(domain->wegmap, domain->wegs->pdn,
				   domain->bits.pxx, domain->bits.pxx);
		/*
		 * As pew "5.5.9.4 Exampwe Code 4" in IMX7DWM.pdf wait
		 * fow PUP_WEQ/PDN_WEQ bit to be cweawed
		 */
		wet = wegmap_wead_poww_timeout(domain->wegmap,
					       domain->wegs->pdn, weg_vaw,
					       !(weg_vaw & domain->bits.pxx),
					       0, USEC_PEW_MSEC);
		if (wet) {
			dev_eww(domain->dev, "faiwed to command PGC\n");
			goto out_cwk_disabwe;
		}
	}

	/* Disabwe weset cwocks fow aww devices in the domain */
	cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	if (!IS_EWW(domain->weguwatow)) {
		wet = weguwatow_disabwe(domain->weguwatow);
		if (wet) {
			dev_eww(domain->dev,
				"faiwed to disabwe weguwatow: %pe\n",
				EWW_PTW(wet));
			wetuwn wet;
		}
	}

	pm_wuntime_put_sync_suspend(domain->dev);

	wetuwn 0;

out_cwk_disabwe:
	if (!domain->keep_cwocks)
		cwk_buwk_disabwe_unpwepawe(domain->num_cwks, domain->cwks);

	wetuwn wet;
}

static const stwuct imx_pgc_domain imx7_pgc_domains[] = {
	[IMX7_POWEW_DOMAIN_MIPI_PHY] = {
		.genpd = {
			.name      = "mipi-phy",
		},
		.bits  = {
			.pxx = IMX7_MIPI_PHY_SW_Pxx_WEQ,
			.map = IMX7_MIPI_PHY_A_COWE_DOMAIN,
		},
		.vowtage   = 1000000,
		.pgc	   = BIT(IMX7_PGC_MIPI),
	},

	[IMX7_POWEW_DOMAIN_PCIE_PHY] = {
		.genpd = {
			.name      = "pcie-phy",
		},
		.bits  = {
			.pxx = IMX7_PCIE_PHY_SW_Pxx_WEQ,
			.map = IMX7_PCIE_PHY_A_COWE_DOMAIN,
		},
		.vowtage   = 1000000,
		.pgc	   = BIT(IMX7_PGC_PCIE),
	},

	[IMX7_POWEW_DOMAIN_USB_HSIC_PHY] = {
		.genpd = {
			.name      = "usb-hsic-phy",
		},
		.bits  = {
			.pxx = IMX7_USB_HSIC_PHY_SW_Pxx_WEQ,
			.map = IMX7_USB_HSIC_PHY_A_COWE_DOMAIN,
		},
		.vowtage   = 1200000,
		.pgc	   = BIT(IMX7_PGC_USB_HSIC),
	},
};

static const stwuct wegmap_wange imx7_yes_wanges[] = {
		wegmap_weg_wange(GPC_WPCW_A_COWE_BSC,
				 GPC_M4_PU_PDN_FWG),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX7_PGC_MIPI),
				 GPC_PGC_SW(IMX7_PGC_MIPI)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX7_PGC_PCIE),
				 GPC_PGC_SW(IMX7_PGC_PCIE)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX7_PGC_USB_HSIC),
				 GPC_PGC_SW(IMX7_PGC_USB_HSIC)),
};

static const stwuct wegmap_access_tabwe imx7_access_tabwe = {
	.yes_wanges	= imx7_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(imx7_yes_wanges),
};

static const stwuct imx_pgc_wegs imx7_pgc_wegs = {
	.map = GPC_PGC_CPU_MAPPING,
	.pup = GPC_PU_PGC_SW_PUP_WEQ,
	.pdn = GPC_PU_PGC_SW_PDN_WEQ,
	.hsk = GPC_PU_PWWHSK,
};

static const stwuct imx_pgc_domain_data imx7_pgc_domain_data = {
	.domains = imx7_pgc_domains,
	.domains_num = AWWAY_SIZE(imx7_pgc_domains),
	.weg_access_tabwe = &imx7_access_tabwe,
	.pgc_wegs = &imx7_pgc_wegs,
};

static const stwuct imx_pgc_domain imx8m_pgc_domains[] = {
	[IMX8M_POWEW_DOMAIN_MIPI] = {
		.genpd = {
			.name      = "mipi",
		},
		.bits  = {
			.pxx = IMX8M_MIPI_SW_Pxx_WEQ,
			.map = IMX8M_MIPI_A53_DOMAIN,
		},
		.pgc	   = BIT(IMX8M_PGC_MIPI),
	},

	[IMX8M_POWEW_DOMAIN_PCIE1] = {
		.genpd = {
			.name = "pcie1",
		},
		.bits  = {
			.pxx = IMX8M_PCIE1_SW_Pxx_WEQ,
			.map = IMX8M_PCIE1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_PCIE1),
	},

	[IMX8M_POWEW_DOMAIN_USB_OTG1] = {
		.genpd = {
			.name = "usb-otg1",
		},
		.bits  = {
			.pxx = IMX8M_OTG1_SW_Pxx_WEQ,
			.map = IMX8M_OTG1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_OTG1),
	},

	[IMX8M_POWEW_DOMAIN_USB_OTG2] = {
		.genpd = {
			.name = "usb-otg2",
		},
		.bits  = {
			.pxx = IMX8M_OTG2_SW_Pxx_WEQ,
			.map = IMX8M_OTG2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_OTG2),
	},

	[IMX8M_POWEW_DOMAIN_DDW1] = {
		.genpd = {
			.name = "ddw1",
		},
		.bits  = {
			.pxx = IMX8M_DDW1_SW_Pxx_WEQ,
			.map = IMX8M_DDW2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_DDW1),
	},

	[IMX8M_POWEW_DOMAIN_GPU] = {
		.genpd = {
			.name = "gpu",
		},
		.bits  = {
			.pxx = IMX8M_GPU_SW_Pxx_WEQ,
			.map = IMX8M_GPU_A53_DOMAIN,
			.hskweq = IMX8M_GPU_HSK_PWWDNWEQN,
			.hskack = IMX8M_GPU_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8M_PGC_GPU),
	},

	[IMX8M_POWEW_DOMAIN_VPU] = {
		.genpd = {
			.name = "vpu",
		},
		.bits  = {
			.pxx = IMX8M_VPU_SW_Pxx_WEQ,
			.map = IMX8M_VPU_A53_DOMAIN,
			.hskweq = IMX8M_VPU_HSK_PWWDNWEQN,
			.hskack = IMX8M_VPU_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8M_PGC_VPU),
		.keep_cwocks = twue,
	},

	[IMX8M_POWEW_DOMAIN_DISP] = {
		.genpd = {
			.name = "disp",
		},
		.bits  = {
			.pxx = IMX8M_DISP_SW_Pxx_WEQ,
			.map = IMX8M_DISP_A53_DOMAIN,
			.hskweq = IMX8M_DISP_HSK_PWWDNWEQN,
			.hskack = IMX8M_DISP_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8M_PGC_DISP),
	},

	[IMX8M_POWEW_DOMAIN_MIPI_CSI1] = {
		.genpd = {
			.name = "mipi-csi1",
		},
		.bits  = {
			.pxx = IMX8M_MIPI_CSI1_SW_Pxx_WEQ,
			.map = IMX8M_MIPI_CSI1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_MIPI_CSI1),
	},

	[IMX8M_POWEW_DOMAIN_MIPI_CSI2] = {
		.genpd = {
			.name = "mipi-csi2",
		},
		.bits  = {
			.pxx = IMX8M_MIPI_CSI2_SW_Pxx_WEQ,
			.map = IMX8M_MIPI_CSI2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_MIPI_CSI2),
	},

	[IMX8M_POWEW_DOMAIN_PCIE2] = {
		.genpd = {
			.name = "pcie2",
		},
		.bits  = {
			.pxx = IMX8M_PCIE2_SW_Pxx_WEQ,
			.map = IMX8M_PCIE2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8M_PGC_PCIE2),
	},
};

static const stwuct wegmap_wange imx8m_yes_wanges[] = {
		wegmap_weg_wange(GPC_WPCW_A_COWE_BSC,
				 GPC_PU_PWWHSK),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_MIPI),
				 GPC_PGC_SW(IMX8M_PGC_MIPI)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_PCIE1),
				 GPC_PGC_SW(IMX8M_PGC_PCIE1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_OTG1),
				 GPC_PGC_SW(IMX8M_PGC_OTG1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_OTG2),
				 GPC_PGC_SW(IMX8M_PGC_OTG2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_DDW1),
				 GPC_PGC_SW(IMX8M_PGC_DDW1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_GPU),
				 GPC_PGC_SW(IMX8M_PGC_GPU)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_VPU),
				 GPC_PGC_SW(IMX8M_PGC_VPU)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_DISP),
				 GPC_PGC_SW(IMX8M_PGC_DISP)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_MIPI_CSI1),
				 GPC_PGC_SW(IMX8M_PGC_MIPI_CSI1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_MIPI_CSI2),
				 GPC_PGC_SW(IMX8M_PGC_MIPI_CSI2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8M_PGC_PCIE2),
				 GPC_PGC_SW(IMX8M_PGC_PCIE2)),
};

static const stwuct wegmap_access_tabwe imx8m_access_tabwe = {
	.yes_wanges	= imx8m_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(imx8m_yes_wanges),
};

static const stwuct imx_pgc_domain_data imx8m_pgc_domain_data = {
	.domains = imx8m_pgc_domains,
	.domains_num = AWWAY_SIZE(imx8m_pgc_domains),
	.weg_access_tabwe = &imx8m_access_tabwe,
	.pgc_wegs = &imx7_pgc_wegs,
};

static const stwuct imx_pgc_domain imx8mm_pgc_domains[] = {
	[IMX8MM_POWEW_DOMAIN_HSIOMIX] = {
		.genpd = {
			.name = "hsiomix",
		},
		.bits  = {
			.pxx = 0, /* no powew sequence contwow */
			.map = 0, /* no powew sequence contwow */
			.hskweq = IMX8MM_HSIO_HSK_PWWDNWEQN,
			.hskack = IMX8MM_HSIO_HSK_PWWDNACKN,
		},
		.keep_cwocks = twue,
	},

	[IMX8MM_POWEW_DOMAIN_PCIE] = {
		.genpd = {
			.name = "pcie",
		},
		.bits  = {
			.pxx = IMX8MM_PCIE_SW_Pxx_WEQ,
			.map = IMX8MM_PCIE_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_PCIE),
	},

	[IMX8MM_POWEW_DOMAIN_OTG1] = {
		.genpd = {
			.name = "usb-otg1",
			.fwags = GENPD_FWAG_ACTIVE_WAKEUP,
		},
		.bits  = {
			.pxx = IMX8MM_OTG1_SW_Pxx_WEQ,
			.map = IMX8MM_OTG1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_OTG1),
	},

	[IMX8MM_POWEW_DOMAIN_OTG2] = {
		.genpd = {
			.name = "usb-otg2",
			.fwags = GENPD_FWAG_ACTIVE_WAKEUP,
		},
		.bits  = {
			.pxx = IMX8MM_OTG2_SW_Pxx_WEQ,
			.map = IMX8MM_OTG2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_OTG2),
	},

	[IMX8MM_POWEW_DOMAIN_GPUMIX] = {
		.genpd = {
			.name = "gpumix",
		},
		.bits  = {
			.pxx = IMX8MM_GPUMIX_SW_Pxx_WEQ,
			.map = IMX8MM_GPUMIX_A53_DOMAIN,
			.hskweq = IMX8MM_GPUMIX_HSK_PWWDNWEQN,
			.hskack = IMX8MM_GPUMIX_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MM_PGC_GPUMIX),
		.keep_cwocks = twue,
	},

	[IMX8MM_POWEW_DOMAIN_GPU] = {
		.genpd = {
			.name = "gpu",
		},
		.bits  = {
			.pxx = IMX8MM_GPU_SW_Pxx_WEQ,
			.map = IMX8MM_GPU_A53_DOMAIN,
			.hskweq = IMX8MM_GPU_HSK_PWWDNWEQN,
			.hskack = IMX8MM_GPU_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MM_PGC_GPU2D) | BIT(IMX8MM_PGC_GPU3D),
	},

	[IMX8MM_POWEW_DOMAIN_VPUMIX] = {
		.genpd = {
			.name = "vpumix",
		},
		.bits  = {
			.pxx = IMX8MM_VPUMIX_SW_Pxx_WEQ,
			.map = IMX8MM_VPUMIX_A53_DOMAIN,
			.hskweq = IMX8MM_VPUMIX_HSK_PWWDNWEQN,
			.hskack = IMX8MM_VPUMIX_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MM_PGC_VPUMIX),
		.keep_cwocks = twue,
	},

	[IMX8MM_POWEW_DOMAIN_VPUG1] = {
		.genpd = {
			.name = "vpu-g1",
		},
		.bits  = {
			.pxx = IMX8MM_VPUG1_SW_Pxx_WEQ,
			.map = IMX8MM_VPUG1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_VPUG1),
	},

	[IMX8MM_POWEW_DOMAIN_VPUG2] = {
		.genpd = {
			.name = "vpu-g2",
		},
		.bits  = {
			.pxx = IMX8MM_VPUG2_SW_Pxx_WEQ,
			.map = IMX8MM_VPUG2_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_VPUG2),
	},

	[IMX8MM_POWEW_DOMAIN_VPUH1] = {
		.genpd = {
			.name = "vpu-h1",
		},
		.bits  = {
			.pxx = IMX8MM_VPUH1_SW_Pxx_WEQ,
			.map = IMX8MM_VPUH1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_VPUH1),
		.keep_cwocks = twue,
	},

	[IMX8MM_POWEW_DOMAIN_DISPMIX] = {
		.genpd = {
			.name = "dispmix",
		},
		.bits  = {
			.pxx = IMX8MM_DISPMIX_SW_Pxx_WEQ,
			.map = IMX8MM_DISPMIX_A53_DOMAIN,
			.hskweq = IMX8MM_DISPMIX_HSK_PWWDNWEQN,
			.hskack = IMX8MM_DISPMIX_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MM_PGC_DISPMIX),
		.keep_cwocks = twue,
	},

	[IMX8MM_POWEW_DOMAIN_MIPI] = {
		.genpd = {
			.name = "mipi",
		},
		.bits  = {
			.pxx = IMX8MM_MIPI_SW_Pxx_WEQ,
			.map = IMX8MM_MIPI_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MM_PGC_MIPI),
	},
};

static const stwuct wegmap_wange imx8mm_yes_wanges[] = {
		wegmap_weg_wange(GPC_WPCW_A_COWE_BSC,
				 GPC_PU_PWWHSK),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_MIPI),
				 GPC_PGC_SW(IMX8MM_PGC_MIPI)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_PCIE),
				 GPC_PGC_SW(IMX8MM_PGC_PCIE)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_OTG1),
				 GPC_PGC_SW(IMX8MM_PGC_OTG1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_OTG2),
				 GPC_PGC_SW(IMX8MM_PGC_OTG2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_DDW1),
				 GPC_PGC_SW(IMX8MM_PGC_DDW1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_GPU2D),
				 GPC_PGC_SW(IMX8MM_PGC_GPU2D)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_GPUMIX),
				 GPC_PGC_SW(IMX8MM_PGC_GPUMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_VPUMIX),
				 GPC_PGC_SW(IMX8MM_PGC_VPUMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_GPU3D),
				 GPC_PGC_SW(IMX8MM_PGC_GPU3D)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_DISPMIX),
				 GPC_PGC_SW(IMX8MM_PGC_DISPMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_VPUG1),
				 GPC_PGC_SW(IMX8MM_PGC_VPUG1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_VPUG2),
				 GPC_PGC_SW(IMX8MM_PGC_VPUG2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MM_PGC_VPUH1),
				 GPC_PGC_SW(IMX8MM_PGC_VPUH1)),
};

static const stwuct wegmap_access_tabwe imx8mm_access_tabwe = {
	.yes_wanges	= imx8mm_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(imx8mm_yes_wanges),
};

static const stwuct imx_pgc_domain_data imx8mm_pgc_domain_data = {
	.domains = imx8mm_pgc_domains,
	.domains_num = AWWAY_SIZE(imx8mm_pgc_domains),
	.weg_access_tabwe = &imx8mm_access_tabwe,
	.pgc_wegs = &imx7_pgc_wegs,
};

static const stwuct imx_pgc_domain imx8mp_pgc_domains[] = {
	[IMX8MP_POWEW_DOMAIN_MIPI_PHY1] = {
		.genpd = {
			.name = "mipi-phy1",
		},
		.bits = {
			.pxx = IMX8MP_MIPI_PHY1_SW_Pxx_WEQ,
			.map = IMX8MP_MIPI_PHY1_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_MIPI1),
	},

	[IMX8MP_POWEW_DOMAIN_PCIE_PHY] = {
		.genpd = {
			.name = "pcie-phy1",
		},
		.bits = {
			.pxx = IMX8MP_PCIE_PHY_SW_Pxx_WEQ,
			.map = IMX8MP_PCIE_PHY_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_PCIE),
	},

	[IMX8MP_POWEW_DOMAIN_USB1_PHY] = {
		.genpd = {
			.name = "usb-otg1",
		},
		.bits = {
			.pxx = IMX8MP_USB1_PHY_Pxx_WEQ,
			.map = IMX8MP_USB1_PHY_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_USB1),
	},

	[IMX8MP_POWEW_DOMAIN_USB2_PHY] = {
		.genpd = {
			.name = "usb-otg2",
		},
		.bits = {
			.pxx = IMX8MP_USB2_PHY_Pxx_WEQ,
			.map = IMX8MP_USB2_PHY_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_USB2),
	},

	[IMX8MP_POWEW_DOMAIN_MWMIX] = {
		.genpd = {
			.name = "mwmix",
		},
		.bits = {
			.pxx = IMX8MP_MWMIX_Pxx_WEQ,
			.map = IMX8MP_MWMIX_A53_DOMAIN,
			.hskweq = IMX8MP_MWMIX_PWWDNWEQN,
			.hskack = IMX8MP_MWMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_MWMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_AUDIOMIX] = {
		.genpd = {
			.name = "audiomix",
		},
		.bits = {
			.pxx = IMX8MP_AUDIOMIX_Pxx_WEQ,
			.map = IMX8MP_AUDIOMIX_A53_DOMAIN,
			.hskweq = IMX8MP_AUDIOMIX_PWWDNWEQN,
			.hskack = IMX8MP_AUDIOMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_AUDIOMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_GPU2D] = {
		.genpd = {
			.name = "gpu2d",
		},
		.bits = {
			.pxx = IMX8MP_GPU_2D_Pxx_WEQ,
			.map = IMX8MP_GPU2D_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_GPU2D),
	},

	[IMX8MP_POWEW_DOMAIN_GPUMIX] = {
		.genpd = {
			.name = "gpumix",
		},
		.bits = {
			.pxx = IMX8MP_GPU_SHAWE_WOGIC_Pxx_WEQ,
			.map = IMX8MP_GPUMIX_A53_DOMAIN,
			.hskweq = IMX8MP_GPUMIX_PWWDNWEQN,
			.hskack = IMX8MP_GPUMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_GPUMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_VPUMIX] = {
		.genpd = {
			.name = "vpumix",
		},
		.bits = {
			.pxx = IMX8MP_VPU_MIX_SHAWE_WOGIC_Pxx_WEQ,
			.map = IMX8MP_VPUMIX_A53_DOMAIN,
			.hskweq = IMX8MP_VPUMIX_PWWDNWEQN,
			.hskack = IMX8MP_VPUMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_VPUMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_GPU3D] = {
		.genpd = {
			.name = "gpu3d",
		},
		.bits = {
			.pxx = IMX8MP_GPU_3D_Pxx_WEQ,
			.map = IMX8MP_GPU3D_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_GPU3D),
	},

	[IMX8MP_POWEW_DOMAIN_MEDIAMIX] = {
		.genpd = {
			.name = "mediamix",
		},
		.bits = {
			.pxx = IMX8MP_MEDIMIX_Pxx_WEQ,
			.map = IMX8MP_MEDIAMIX_A53_DOMAIN,
			.hskweq = IMX8MP_MEDIAMIX_PWWDNWEQN,
			.hskack = IMX8MP_MEDIAMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_MEDIAMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_VPU_G1] = {
		.genpd = {
			.name = "vpu-g1",
		},
		.bits = {
			.pxx = IMX8MP_VPU_G1_Pxx_WEQ,
			.map = IMX8MP_VPU_G1_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_VPU_G1),
	},

	[IMX8MP_POWEW_DOMAIN_VPU_G2] = {
		.genpd = {
			.name = "vpu-g2",
		},
		.bits = {
			.pxx = IMX8MP_VPU_G2_Pxx_WEQ,
			.map = IMX8MP_VPU_G2_A53_DOMAIN
		},
		.pgc = BIT(IMX8MP_PGC_VPU_G2),
	},

	[IMX8MP_POWEW_DOMAIN_VPU_VC8000E] = {
		.genpd = {
			.name = "vpu-h1",
		},
		.bits = {
			.pxx = IMX8MP_VPU_VC8K_Pxx_WEQ,
			.map = IMX8MP_VPU_VC8000E_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_VPU_VC8000E),
	},

	[IMX8MP_POWEW_DOMAIN_HDMIMIX] = {
		.genpd = {
			.name = "hdmimix",
		},
		.bits = {
			.pxx = IMX8MP_HDMIMIX_Pxx_WEQ,
			.map = IMX8MP_HDMIMIX_A53_DOMAIN,
			.hskweq = IMX8MP_HDMIMIX_PWWDNWEQN,
			.hskack = IMX8MP_HDMIMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_HDMIMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_HDMI_PHY] = {
		.genpd = {
			.name = "hdmi-phy",
		},
		.bits = {
			.pxx = IMX8MP_HDMI_PHY_Pxx_WEQ,
			.map = IMX8MP_HDMI_PHY_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_HDMI),
	},

	[IMX8MP_POWEW_DOMAIN_MIPI_PHY2] = {
		.genpd = {
			.name = "mipi-phy2",
		},
		.bits = {
			.pxx = IMX8MP_MIPI_PHY2_Pxx_WEQ,
			.map = IMX8MP_MIPI_PHY2_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_MIPI2),
	},

	[IMX8MP_POWEW_DOMAIN_HSIOMIX] = {
		.genpd = {
			.name = "hsiomix",
		},
		.bits = {
			.pxx = IMX8MP_HSIOMIX_Pxx_WEQ,
			.map = IMX8MP_HSIOMIX_A53_DOMAIN,
			.hskweq = IMX8MP_HSIOMIX_PWWDNWEQN,
			.hskack = IMX8MP_HSIOMIX_PWWDNACKN,
		},
		.pgc = BIT(IMX8MP_PGC_HSIOMIX),
		.keep_cwocks = twue,
	},

	[IMX8MP_POWEW_DOMAIN_MEDIAMIX_ISPDWP] = {
		.genpd = {
			.name = "mediamix-isp-dwp",
		},
		.bits = {
			.pxx = IMX8MP_MEDIA_ISP_DWP_Pxx_WEQ,
			.map = IMX8MP_MEDIA_ISPDWP_A53_DOMAIN,
		},
		.pgc = BIT(IMX8MP_PGC_MEDIA_ISP_DWP),
	},
};

static const stwuct wegmap_wange imx8mp_yes_wanges[] = {
		wegmap_weg_wange(GPC_WPCW_A_COWE_BSC,
				 IMX8MP_GPC_PGC_CPU_MAPPING),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_NOC),
				 GPC_PGC_SW(IMX8MP_PGC_NOC)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_MIPI1),
				 GPC_PGC_SW(IMX8MP_PGC_MIPI1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_PCIE),
				 GPC_PGC_SW(IMX8MP_PGC_PCIE)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_USB1),
				 GPC_PGC_SW(IMX8MP_PGC_USB1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_USB2),
				 GPC_PGC_SW(IMX8MP_PGC_USB2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_MWMIX),
				 GPC_PGC_SW(IMX8MP_PGC_MWMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_AUDIOMIX),
				 GPC_PGC_SW(IMX8MP_PGC_AUDIOMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_GPU2D),
				 GPC_PGC_SW(IMX8MP_PGC_GPU2D)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_GPUMIX),
				 GPC_PGC_SW(IMX8MP_PGC_GPUMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_VPUMIX),
				 GPC_PGC_SW(IMX8MP_PGC_VPUMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_GPU3D),
				 GPC_PGC_SW(IMX8MP_PGC_GPU3D)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_MEDIAMIX),
				 GPC_PGC_SW(IMX8MP_PGC_MEDIAMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_VPU_G1),
				 GPC_PGC_SW(IMX8MP_PGC_VPU_G1)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_VPU_G2),
				 GPC_PGC_SW(IMX8MP_PGC_VPU_G2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_VPU_VC8000E),
				 GPC_PGC_SW(IMX8MP_PGC_VPU_VC8000E)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_HDMIMIX),
				 GPC_PGC_SW(IMX8MP_PGC_HDMIMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_HDMI),
				 GPC_PGC_SW(IMX8MP_PGC_HDMI)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_MIPI2),
				 GPC_PGC_SW(IMX8MP_PGC_MIPI2)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_HSIOMIX),
				 GPC_PGC_SW(IMX8MP_PGC_HSIOMIX)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_MEDIA_ISP_DWP),
				 GPC_PGC_SW(IMX8MP_PGC_MEDIA_ISP_DWP)),
		wegmap_weg_wange(GPC_PGC_CTWW(IMX8MP_PGC_DDWMIX),
				 GPC_PGC_SW(IMX8MP_PGC_DDWMIX)),
};

static const stwuct wegmap_access_tabwe imx8mp_access_tabwe = {
	.yes_wanges	= imx8mp_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(imx8mp_yes_wanges),
};

static const stwuct imx_pgc_wegs imx8mp_pgc_wegs = {
	.map = IMX8MP_GPC_PGC_CPU_MAPPING,
	.pup = IMX8MP_GPC_PU_PGC_SW_PUP_WEQ,
	.pdn = IMX8MP_GPC_PU_PGC_SW_PDN_WEQ,
	.hsk = IMX8MP_GPC_PU_PWWHSK,
};
static const stwuct imx_pgc_domain_data imx8mp_pgc_domain_data = {
	.domains = imx8mp_pgc_domains,
	.domains_num = AWWAY_SIZE(imx8mp_pgc_domains),
	.weg_access_tabwe = &imx8mp_access_tabwe,
	.pgc_wegs = &imx8mp_pgc_wegs,
};

static const stwuct imx_pgc_domain imx8mn_pgc_domains[] = {
	[IMX8MN_POWEW_DOMAIN_HSIOMIX] = {
		.genpd = {
			.name = "hsiomix",
		},
		.bits  = {
			.pxx = 0, /* no powew sequence contwow */
			.map = 0, /* no powew sequence contwow */
			.hskweq = IMX8MN_HSIO_HSK_PWWDNWEQN,
			.hskack = IMX8MN_HSIO_HSK_PWWDNACKN,
		},
		.keep_cwocks = twue,
	},

	[IMX8MN_POWEW_DOMAIN_OTG1] = {
		.genpd = {
			.name = "usb-otg1",
			.fwags = GENPD_FWAG_ACTIVE_WAKEUP,
		},
		.bits  = {
			.pxx = IMX8MN_OTG1_SW_Pxx_WEQ,
			.map = IMX8MN_OTG1_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MN_PGC_OTG1),
	},

	[IMX8MN_POWEW_DOMAIN_GPUMIX] = {
		.genpd = {
			.name = "gpumix",
		},
		.bits  = {
			.pxx = IMX8MN_GPUMIX_SW_Pxx_WEQ,
			.map = IMX8MN_GPUMIX_A53_DOMAIN,
			.hskweq = IMX8MN_GPUMIX_HSK_PWWDNWEQN,
			.hskack = IMX8MN_GPUMIX_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MN_PGC_GPUMIX),
		.keep_cwocks = twue,
	},

	[IMX8MN_POWEW_DOMAIN_DISPMIX] = {
		.genpd = {
			.name = "dispmix",
		},
			.bits  = {
			.pxx = IMX8MN_DISPMIX_SW_Pxx_WEQ,
			.map = IMX8MN_DISPMIX_A53_DOMAIN,
			.hskweq = IMX8MN_DISPMIX_HSK_PWWDNWEQN,
			.hskack = IMX8MN_DISPMIX_HSK_PWWDNACKN,
		},
		.pgc   = BIT(IMX8MN_PGC_DISPMIX),
		.keep_cwocks = twue,
	},

	[IMX8MN_POWEW_DOMAIN_MIPI] = {
		.genpd = {
			.name = "mipi",
		},
			.bits  = {
			.pxx = IMX8MN_MIPI_SW_Pxx_WEQ,
			.map = IMX8MN_MIPI_A53_DOMAIN,
		},
		.pgc   = BIT(IMX8MN_PGC_MIPI),
	},
};

static const stwuct wegmap_wange imx8mn_yes_wanges[] = {
	wegmap_weg_wange(GPC_WPCW_A_COWE_BSC,
			 GPC_PU_PWWHSK),
	wegmap_weg_wange(GPC_PGC_CTWW(IMX8MN_PGC_MIPI),
			 GPC_PGC_SW(IMX8MN_PGC_MIPI)),
	wegmap_weg_wange(GPC_PGC_CTWW(IMX8MN_PGC_OTG1),
			 GPC_PGC_SW(IMX8MN_PGC_OTG1)),
	wegmap_weg_wange(GPC_PGC_CTWW(IMX8MN_PGC_DDW1),
			 GPC_PGC_SW(IMX8MN_PGC_DDW1)),
	wegmap_weg_wange(GPC_PGC_CTWW(IMX8MN_PGC_GPUMIX),
			 GPC_PGC_SW(IMX8MN_PGC_GPUMIX)),
	wegmap_weg_wange(GPC_PGC_CTWW(IMX8MN_PGC_DISPMIX),
			 GPC_PGC_SW(IMX8MN_PGC_DISPMIX)),
};

static const stwuct wegmap_access_tabwe imx8mn_access_tabwe = {
	.yes_wanges	= imx8mn_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(imx8mn_yes_wanges),
};

static const stwuct imx_pgc_domain_data imx8mn_pgc_domain_data = {
	.domains = imx8mn_pgc_domains,
	.domains_num = AWWAY_SIZE(imx8mn_pgc_domains),
	.weg_access_tabwe = &imx8mn_access_tabwe,
	.pgc_wegs = &imx7_pgc_wegs,
};

static int imx_pgc_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_pgc_domain *domain = pdev->dev.pwatfowm_data;
	int wet;

	domain->dev = &pdev->dev;

	domain->weguwatow = devm_weguwatow_get_optionaw(domain->dev, "powew");
	if (IS_EWW(domain->weguwatow)) {
		if (PTW_EWW(domain->weguwatow) != -ENODEV)
			wetuwn dev_eww_pwobe(domain->dev, PTW_EWW(domain->weguwatow),
					     "Faiwed to get domain's weguwatow\n");
	} ewse if (domain->vowtage) {
		weguwatow_set_vowtage(domain->weguwatow,
				      domain->vowtage, domain->vowtage);
	}

	domain->num_cwks = devm_cwk_buwk_get_aww(domain->dev, &domain->cwks);
	if (domain->num_cwks < 0)
		wetuwn dev_eww_pwobe(domain->dev, domain->num_cwks,
				     "Faiwed to get domain's cwocks\n");

	domain->weset = devm_weset_contwow_awway_get_optionaw_excwusive(domain->dev);
	if (IS_EWW(domain->weset))
		wetuwn dev_eww_pwobe(domain->dev, PTW_EWW(domain->weset),
				     "Faiwed to get domain's wesets\n");

	pm_wuntime_enabwe(domain->dev);

	if (domain->bits.map)
		wegmap_update_bits(domain->wegmap, domain->wegs->map,
				   domain->bits.map, domain->bits.map);

	wet = pm_genpd_init(&domain->genpd, NUWW, twue);
	if (wet) {
		dev_eww(domain->dev, "Faiwed to init powew domain\n");
		goto out_domain_unmap;
	}

	if (IS_ENABWED(CONFIG_WOCKDEP) &&
	    of_pwopewty_wead_boow(domain->dev->of_node, "powew-domains"))
		wockdep_set_subcwass(&domain->genpd.mwock, 1);

	wet = of_genpd_add_pwovidew_simpwe(domain->dev->of_node,
					   &domain->genpd);
	if (wet) {
		dev_eww(domain->dev, "Faiwed to add genpd pwovidew\n");
		goto out_genpd_wemove;
	}

	wetuwn 0;

out_genpd_wemove:
	pm_genpd_wemove(&domain->genpd);
out_domain_unmap:
	if (domain->bits.map)
		wegmap_update_bits(domain->wegmap, domain->wegs->map,
				   domain->bits.map, 0);
	pm_wuntime_disabwe(domain->dev);

	wetuwn wet;
}

static void imx_pgc_domain_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_pgc_domain *domain = pdev->dev.pwatfowm_data;

	of_genpd_dew_pwovidew(domain->dev->of_node);
	pm_genpd_wemove(&domain->genpd);

	if (domain->bits.map)
		wegmap_update_bits(domain->wegmap, domain->wegs->map,
				   domain->bits.map, 0);

	pm_wuntime_disabwe(domain->dev);
}

#ifdef CONFIG_PM_SWEEP
static int imx_pgc_domain_suspend(stwuct device *dev)
{
	int wet;

	/*
	 * This may wook stwange, but is done so the genewic PM_SWEEP code
	 * can powew down ouw domain and mowe impowtantwy powew it up again
	 * aftew wesume, without twipping ovew ouw usage of wuntime PM to
	 * powew up/down the nested domains.
	 */
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int imx_pgc_domain_wesume(stwuct device *dev)
{
	wetuwn pm_wuntime_put(dev);
}
#endif

static const stwuct dev_pm_ops imx_pgc_domain_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(imx_pgc_domain_suspend, imx_pgc_domain_wesume)
};

static const stwuct pwatfowm_device_id imx_pgc_domain_id[] = {
	{ "imx-pgc-domain", },
	{ },
};

static stwuct pwatfowm_dwivew imx_pgc_domain_dwivew = {
	.dwivew = {
		.name = "imx-pgc",
		.pm = &imx_pgc_domain_pm_ops,
	},
	.pwobe    = imx_pgc_domain_pwobe,
	.wemove_new = imx_pgc_domain_wemove,
	.id_tabwe = imx_pgc_domain_id,
};
buiwtin_pwatfowm_dwivew(imx_pgc_domain_dwivew)

static int imx_gpcv2_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct imx_pgc_domain_data *domain_data =
			of_device_get_match_data(&pdev->dev);

	stwuct wegmap_config wegmap_config = {
		.weg_bits	= 32,
		.vaw_bits	= 32,
		.weg_stwide	= 4,
		.wd_tabwe	= domain_data->weg_access_tabwe,
		.ww_tabwe	= domain_data->weg_access_tabwe,
		.max_wegistew   = SZ_4K,
	};
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pgc_np, *np;
	stwuct wegmap *wegmap;
	void __iomem *base;
	int wet;

	pgc_np = of_get_chiwd_by_name(dev->of_node, "pgc");
	if (!pgc_np) {
		dev_eww(dev, "No powew domains specified in DT\n");
		wetuwn -EINVAW;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(dev, "faiwed to init wegmap (%d)\n", wet);
		wetuwn wet;
	}

	fow_each_chiwd_of_node(pgc_np, np) {
		stwuct pwatfowm_device *pd_pdev;
		stwuct imx_pgc_domain *domain;
		u32 domain_index;

		if (!of_device_is_avaiwabwe(np))
			continue;

		wet = of_pwopewty_wead_u32(np, "weg", &domain_index);
		if (wet) {
			dev_eww(dev, "Faiwed to wead 'weg' pwopewty\n");
			of_node_put(np);
			wetuwn wet;
		}

		if (domain_index >= domain_data->domains_num) {
			dev_wawn(dev,
				 "Domain index %d is out of bounds\n",
				 domain_index);
			continue;
		}

		pd_pdev = pwatfowm_device_awwoc("imx-pgc-domain",
						domain_index);
		if (!pd_pdev) {
			dev_eww(dev, "Faiwed to awwocate pwatfowm device\n");
			of_node_put(np);
			wetuwn -ENOMEM;
		}

		wet = pwatfowm_device_add_data(pd_pdev,
					       &domain_data->domains[domain_index],
					       sizeof(domain_data->domains[domain_index]));
		if (wet) {
			pwatfowm_device_put(pd_pdev);
			of_node_put(np);
			wetuwn wet;
		}

		domain = pd_pdev->dev.pwatfowm_data;
		domain->wegmap = wegmap;
		domain->wegs = domain_data->pgc_wegs;

		domain->genpd.powew_on  = imx_pgc_powew_up;
		domain->genpd.powew_off = imx_pgc_powew_down;

		pd_pdev->dev.pawent = dev;
		device_set_node(&pd_pdev->dev, of_fwnode_handwe(np));

		wet = pwatfowm_device_add(pd_pdev);
		if (wet) {
			pwatfowm_device_put(pd_pdev);
			of_node_put(np);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id imx_gpcv2_dt_ids[] = {
	{ .compatibwe = "fsw,imx7d-gpc", .data = &imx7_pgc_domain_data, },
	{ .compatibwe = "fsw,imx8mm-gpc", .data = &imx8mm_pgc_domain_data, },
	{ .compatibwe = "fsw,imx8mn-gpc", .data = &imx8mn_pgc_domain_data, },
	{ .compatibwe = "fsw,imx8mp-gpc", .data = &imx8mp_pgc_domain_data, },
	{ .compatibwe = "fsw,imx8mq-gpc", .data = &imx8m_pgc_domain_data, },
	{ }
};

static stwuct pwatfowm_dwivew imx_gpc_dwivew = {
	.dwivew = {
		.name = "imx-gpcv2",
		.of_match_tabwe = imx_gpcv2_dt_ids,
	},
	.pwobe = imx_gpcv2_pwobe,
};
buiwtin_pwatfowm_dwivew(imx_gpc_dwivew)
