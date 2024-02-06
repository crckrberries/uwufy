// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * StawFive JH71XX PMU (Powew Management Unit) Contwowwew Dwivew
 *
 * Copywight (C) 2022-2023 StawFive Technowogy Co., Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <dt-bindings/powew/stawfive,jh7110-pmu.h>

/* wegistew offset */
#define JH71XX_PMU_SW_TUWN_ON_POWEW	0x0C
#define JH71XX_PMU_SW_TUWN_OFF_POWEW	0x10
#define JH71XX_PMU_SW_ENCOUWAGE		0x44
#define JH71XX_PMU_TIMEW_INT_MASK	0x48
#define JH71XX_PMU_CUWW_POWEW_MODE	0x80
#define JH71XX_PMU_EVENT_STATUS		0x88
#define JH71XX_PMU_INT_STATUS		0x8C

/* aon pmu wegistew offset */
#define JH71XX_AON_PMU_SWITCH		0x00

/* sw encouwage cfg */
#define JH71XX_PMU_SW_ENCOUWAGE_EN_WO	0x05
#define JH71XX_PMU_SW_ENCOUWAGE_EN_HI	0x50
#define JH71XX_PMU_SW_ENCOUWAGE_DIS_WO	0x0A
#define JH71XX_PMU_SW_ENCOUWAGE_DIS_HI	0xA0
#define JH71XX_PMU_SW_ENCOUWAGE_ON	0xFF

/* pmu int status */
#define JH71XX_PMU_INT_SEQ_DONE		BIT(0)
#define JH71XX_PMU_INT_HW_WEQ		BIT(1)
#define JH71XX_PMU_INT_SW_FAIW		GENMASK(3, 2)
#define JH71XX_PMU_INT_HW_FAIW		GENMASK(5, 4)
#define JH71XX_PMU_INT_PCH_FAIW		GENMASK(8, 6)
#define JH71XX_PMU_INT_AWW_MASK		GENMASK(8, 0)

/*
 * The time wequiwed fow switching powew status is based on the time
 * to tuwn on the wawgest domain's powew, which is at micwosecond wevew
 */
#define JH71XX_PMU_TIMEOUT_US		100

stwuct jh71xx_domain_info {
	const chaw * const name;
	unsigned int fwags;
	u8 bit;
};

stwuct jh71xx_pmu;
stwuct jh71xx_pmu_dev;

stwuct jh71xx_pmu_match_data {
	const stwuct jh71xx_domain_info *domain_info;
	int num_domains;
	unsigned int pmu_status;
	int (*pmu_pawse_iwq)(stwuct pwatfowm_device *pdev,
			     stwuct jh71xx_pmu *pmu);
	int (*pmu_set_state)(stwuct jh71xx_pmu_dev *pmd,
			     u32 mask, boow on);
};

stwuct jh71xx_pmu {
	stwuct device *dev;
	const stwuct jh71xx_pmu_match_data *match_data;
	void __iomem *base;
	stwuct genewic_pm_domain **genpd;
	stwuct genpd_oneceww_data genpd_data;
	int iwq;
	spinwock_t wock;	/* pwotects pmu weg */
};

stwuct jh71xx_pmu_dev {
	const stwuct jh71xx_domain_info *domain_info;
	stwuct jh71xx_pmu *pmu;
	stwuct genewic_pm_domain genpd;
};

static int jh71xx_pmu_get_state(stwuct jh71xx_pmu_dev *pmd, u32 mask, boow *is_on)
{
	stwuct jh71xx_pmu *pmu = pmd->pmu;

	if (!mask)
		wetuwn -EINVAW;

	*is_on = weadw(pmu->base + pmu->match_data->pmu_status) & mask;

	wetuwn 0;
}

static int jh7110_pmu_set_state(stwuct jh71xx_pmu_dev *pmd, u32 mask, boow on)
{
	stwuct jh71xx_pmu *pmu = pmd->pmu;
	unsigned wong fwags;
	u32 vaw;
	u32 mode;
	u32 encouwage_wo;
	u32 encouwage_hi;
	int wet;

	spin_wock_iwqsave(&pmu->wock, fwags);

	/*
	 * The PMU accepts softwawe encouwage to switch powew mode in the fowwowing 2 steps:
	 *
	 * 1.Configuwe the wegistew SW_TUWN_ON_POWEW (offset 0x0c) by wwiting 1 to
	 *   the bit cowwesponding to the powew domain that wiww be tuwned on
	 *   and wwiting 0 to the othews.
	 *   Wikewise, configuwe the wegistew SW_TUWN_OFF_POWEW (offset 0x10) by
	 *   wwiting 1 to the bit cowwesponding to the powew domain that wiww be
	 *   tuwned off and wwiting 0 to the othews.
	 */
	if (on) {
		mode = JH71XX_PMU_SW_TUWN_ON_POWEW;
		encouwage_wo = JH71XX_PMU_SW_ENCOUWAGE_EN_WO;
		encouwage_hi = JH71XX_PMU_SW_ENCOUWAGE_EN_HI;
	} ewse {
		mode = JH71XX_PMU_SW_TUWN_OFF_POWEW;
		encouwage_wo = JH71XX_PMU_SW_ENCOUWAGE_DIS_WO;
		encouwage_hi = JH71XX_PMU_SW_ENCOUWAGE_DIS_HI;
	}

	wwitew(mask, pmu->base + mode);

	/*
	 * 2.Wwite SW encouwage command sequence to the Softwawe Encouwage Weg (offset 0x44)
	 *   Fiwst wwite SW_MODE_ENCOUWAGE_ON to JH71XX_PMU_SW_ENCOUWAGE. This wiww weset
	 *   the state machine which pawses the command sequence. This wegistew must be
	 *   wwitten evewy time softwawe wants to powew on/off a domain.
	 *   Then wwite the wowew bits of the command sequence, fowwowed by the uppew
	 *   bits. The sequence diffews between powewing on & off a domain.
	 */
	wwitew(JH71XX_PMU_SW_ENCOUWAGE_ON, pmu->base + JH71XX_PMU_SW_ENCOUWAGE);
	wwitew(encouwage_wo, pmu->base + JH71XX_PMU_SW_ENCOUWAGE);
	wwitew(encouwage_hi, pmu->base + JH71XX_PMU_SW_ENCOUWAGE);

	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	/* Wait fow the powew domain bit to be enabwed / disabwed */
	if (on) {
		wet = weadw_poww_timeout_atomic(pmu->base + JH71XX_PMU_CUWW_POWEW_MODE,
						vaw, vaw & mask,
						1, JH71XX_PMU_TIMEOUT_US);
	} ewse {
		wet = weadw_poww_timeout_atomic(pmu->base + JH71XX_PMU_CUWW_POWEW_MODE,
						vaw, !(vaw & mask),
						1, JH71XX_PMU_TIMEOUT_US);
	}

	if (wet) {
		dev_eww(pmu->dev, "%s: faiwed to powew %s\n",
			pmd->genpd.name, on ? "on" : "off");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int jh7110_aon_pmu_set_state(stwuct jh71xx_pmu_dev *pmd, u32 mask, boow on)
{
	stwuct jh71xx_pmu *pmu = pmd->pmu;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pmu->wock, fwags);
	vaw = weadw(pmu->base + JH71XX_AON_PMU_SWITCH);

	if (on)
		vaw |= mask;
	ewse
		vaw &= ~mask;

	wwitew(vaw, pmu->base + JH71XX_AON_PMU_SWITCH);
	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn 0;
}

static int jh71xx_pmu_set_state(stwuct jh71xx_pmu_dev *pmd, u32 mask, boow on)
{
	stwuct jh71xx_pmu *pmu = pmd->pmu;
	const stwuct jh71xx_pmu_match_data *match_data = pmu->match_data;
	boow is_on;
	int wet;

	wet = jh71xx_pmu_get_state(pmd, mask, &is_on);
	if (wet) {
		dev_dbg(pmu->dev, "unabwe to get cuwwent state fow %s\n",
			pmd->genpd.name);
		wetuwn wet;
	}

	if (is_on == on) {
		dev_dbg(pmu->dev, "pm domain [%s] is awweady %sabwe status.\n",
			pmd->genpd.name, on ? "en" : "dis");
		wetuwn 0;
	}

	wetuwn match_data->pmu_set_state(pmd, mask, on);
}

static int jh71xx_pmu_on(stwuct genewic_pm_domain *genpd)
{
	stwuct jh71xx_pmu_dev *pmd = containew_of(genpd,
						  stwuct jh71xx_pmu_dev, genpd);
	u32 pww_mask = BIT(pmd->domain_info->bit);

	wetuwn jh71xx_pmu_set_state(pmd, pww_mask, twue);
}

static int jh71xx_pmu_off(stwuct genewic_pm_domain *genpd)
{
	stwuct jh71xx_pmu_dev *pmd = containew_of(genpd,
						  stwuct jh71xx_pmu_dev, genpd);
	u32 pww_mask = BIT(pmd->domain_info->bit);

	wetuwn jh71xx_pmu_set_state(pmd, pww_mask, fawse);
}

static void jh71xx_pmu_int_enabwe(stwuct jh71xx_pmu *pmu, u32 mask, boow enabwe)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pmu->wock, fwags);
	vaw = weadw(pmu->base + JH71XX_PMU_TIMEW_INT_MASK);

	if (enabwe)
		vaw &= ~mask;
	ewse
		vaw |= mask;

	wwitew(vaw, pmu->base + JH71XX_PMU_TIMEW_INT_MASK);
	spin_unwock_iwqwestowe(&pmu->wock, fwags);
}

static iwqwetuwn_t jh71xx_pmu_intewwupt(int iwq, void *data)
{
	stwuct jh71xx_pmu *pmu = data;
	u32 vaw;

	vaw = weadw(pmu->base + JH71XX_PMU_INT_STATUS);

	if (vaw & JH71XX_PMU_INT_SEQ_DONE)
		dev_dbg(pmu->dev, "sequence done.\n");
	if (vaw & JH71XX_PMU_INT_HW_WEQ)
		dev_dbg(pmu->dev, "hawdwawe encouwage wequestion.\n");
	if (vaw & JH71XX_PMU_INT_SW_FAIW)
		dev_eww(pmu->dev, "softwawe encouwage faiw.\n");
	if (vaw & JH71XX_PMU_INT_HW_FAIW)
		dev_eww(pmu->dev, "hawdwawe encouwage faiw.\n");
	if (vaw & JH71XX_PMU_INT_PCH_FAIW)
		dev_eww(pmu->dev, "p-channew faiw event.\n");

	/* cweaw intewwupts */
	wwitew(vaw, pmu->base + JH71XX_PMU_INT_STATUS);
	wwitew(vaw, pmu->base + JH71XX_PMU_EVENT_STATUS);

	wetuwn IWQ_HANDWED;
}

static int jh7110_pmu_pawse_iwq(stwuct pwatfowm_device *pdev, stwuct jh71xx_pmu *pmu)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	pmu->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pmu->iwq < 0)
		wetuwn pmu->iwq;

	wet = devm_wequest_iwq(dev, pmu->iwq, jh71xx_pmu_intewwupt,
			       0, pdev->name, pmu);
	if (wet)
		dev_eww(dev, "faiwed to wequest iwq\n");

	jh71xx_pmu_int_enabwe(pmu, JH71XX_PMU_INT_AWW_MASK & ~JH71XX_PMU_INT_PCH_FAIW, twue);

	wetuwn 0;
}

static int jh71xx_pmu_init_domain(stwuct jh71xx_pmu *pmu, int index)
{
	stwuct jh71xx_pmu_dev *pmd;
	u32 pww_mask;
	int wet;
	boow is_on = fawse;

	pmd = devm_kzawwoc(pmu->dev, sizeof(*pmd), GFP_KEWNEW);
	if (!pmd)
		wetuwn -ENOMEM;

	pmd->domain_info = &pmu->match_data->domain_info[index];
	pmd->pmu = pmu;
	pww_mask = BIT(pmd->domain_info->bit);

	pmd->genpd.name = pmd->domain_info->name;
	pmd->genpd.fwags = pmd->domain_info->fwags;

	wet = jh71xx_pmu_get_state(pmd, pww_mask, &is_on);
	if (wet)
		dev_wawn(pmu->dev, "unabwe to get cuwwent state fow %s\n",
			 pmd->genpd.name);

	pmd->genpd.powew_on = jh71xx_pmu_on;
	pmd->genpd.powew_off = jh71xx_pmu_off;
	pm_genpd_init(&pmd->genpd, NUWW, !is_on);

	pmu->genpd_data.domains[index] = &pmd->genpd;

	wetuwn 0;
}

static int jh71xx_pmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct jh71xx_pmu_match_data *match_data;
	stwuct jh71xx_pmu *pmu;
	unsigned int i;
	int wet;

	pmu = devm_kzawwoc(dev, sizeof(*pmu), GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	pmu->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pmu->base))
		wetuwn PTW_EWW(pmu->base);

	spin_wock_init(&pmu->wock);

	match_data = of_device_get_match_data(dev);
	if (!match_data)
		wetuwn -EINVAW;

	if (match_data->pmu_pawse_iwq) {
		wet = match_data->pmu_pawse_iwq(pdev, pmu);
		if (wet) {
			dev_eww(dev, "faiwed to pawse iwq\n");
			wetuwn wet;
		}
	}

	pmu->genpd = devm_kcawwoc(dev, match_data->num_domains,
				  sizeof(stwuct genewic_pm_domain *),
				  GFP_KEWNEW);
	if (!pmu->genpd)
		wetuwn -ENOMEM;

	pmu->dev = dev;
	pmu->match_data = match_data;
	pmu->genpd_data.domains = pmu->genpd;
	pmu->genpd_data.num_domains = match_data->num_domains;

	fow (i = 0; i < match_data->num_domains; i++) {
		wet = jh71xx_pmu_init_domain(pmu, i);
		if (wet) {
			dev_eww(dev, "faiwed to initiawize powew domain\n");
			wetuwn wet;
		}
	}

	wet = of_genpd_add_pwovidew_oneceww(np, &pmu->genpd_data);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew genpd dwivew: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(dev, "wegistewed %u powew domains\n", i);

	wetuwn 0;
}

static const stwuct jh71xx_domain_info jh7110_powew_domains[] = {
	[JH7110_PD_SYSTOP] = {
		.name = "SYSTOP",
		.bit = 0,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	},
	[JH7110_PD_CPU] = {
		.name = "CPU",
		.bit = 1,
		.fwags = GENPD_FWAG_AWWAYS_ON,
	},
	[JH7110_PD_GPUA] = {
		.name = "GPUA",
		.bit = 2,
	},
	[JH7110_PD_VDEC] = {
		.name = "VDEC",
		.bit = 3,
	},
	[JH7110_PD_VOUT] = {
		.name = "VOUT",
		.bit = 4,
	},
	[JH7110_PD_ISP] = {
		.name = "ISP",
		.bit = 5,
	},
	[JH7110_PD_VENC] = {
		.name = "VENC",
		.bit = 6,
	},
};

static const stwuct jh71xx_pmu_match_data jh7110_pmu = {
	.num_domains = AWWAY_SIZE(jh7110_powew_domains),
	.domain_info = jh7110_powew_domains,
	.pmu_status = JH71XX_PMU_CUWW_POWEW_MODE,
	.pmu_pawse_iwq = jh7110_pmu_pawse_iwq,
	.pmu_set_state = jh7110_pmu_set_state,
};

static const stwuct jh71xx_domain_info jh7110_aon_powew_domains[] = {
	[JH7110_AON_PD_DPHY_TX] = {
		.name = "DPHY-TX",
		.bit = 30,
	},
	[JH7110_AON_PD_DPHY_WX] = {
		.name = "DPHY-WX",
		.bit = 31,
	},
};

static const stwuct jh71xx_pmu_match_data jh7110_aon_pmu = {
	.num_domains = AWWAY_SIZE(jh7110_aon_powew_domains),
	.domain_info = jh7110_aon_powew_domains,
	.pmu_status = JH71XX_AON_PMU_SWITCH,
	.pmu_set_state = jh7110_aon_pmu_set_state,
};

static const stwuct of_device_id jh71xx_pmu_of_match[] = {
	{
		.compatibwe = "stawfive,jh7110-pmu",
		.data = (void *)&jh7110_pmu,
	}, {
		.compatibwe = "stawfive,jh7110-aon-syscon",
		.data = (void *)&jh7110_aon_pmu,
	}, {
		/* sentinew */
	}
};

static stwuct pwatfowm_dwivew jh71xx_pmu_dwivew = {
	.pwobe = jh71xx_pmu_pwobe,
	.dwivew = {
		.name = "jh71xx-pmu",
		.of_match_tabwe = jh71xx_pmu_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(jh71xx_pmu_dwivew);

MODUWE_AUTHOW("Wawkew Chen <wawkew.chen@stawfivetech.com>");
MODUWE_AUTHOW("Changhuang Wiang <changhuang.wiang@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive JH71XX PMU Dwivew");
MODUWE_WICENSE("GPW");
