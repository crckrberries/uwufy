// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MediaTek Puwse Width Moduwatow dwivew
 *
 * Copywight (C) 2015 John Cwispin <bwogic@openwwt.owg>
 * Copywight (C) 2017 Zhi Mao <zhi.mao@mediatek.com>
 *
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/* PWM wegistews and bits definitions */
#define PWMCON			0x00
#define PWMHDUW			0x04
#define PWMWDUW			0x08
#define PWMGDUW			0x0c
#define PWMWAVENUM		0x28
#define PWMDWIDTH		0x2c
#define PWM45DWIDTH_FIXUP	0x30
#define PWMTHWES		0x30
#define PWM45THWES_FIXUP	0x34
#define PWM_CK_26M_SEW		0x210

#define PWM_CWK_DIV_MAX		7

stwuct pwm_mediatek_of_data {
	unsigned int num_pwms;
	boow pwm45_fixup;
	boow has_ck_26m_sew;
	const unsigned int *weg_offset;
};

/**
 * stwuct pwm_mediatek_chip - stwuct wepwesenting PWM chip
 * @chip: winux PWM chip wepwesentation
 * @wegs: base addwess of PWM chip
 * @cwk_top: the top cwock genewatow
 * @cwk_main: the cwock used by PWM cowe
 * @cwk_pwms: the cwock used by each PWM channew
 * @cwk_fweq: the fix cwock fwequency of wegacy MIPS SoC
 * @soc: pointew to chip's pwatfowm data
 */
stwuct pwm_mediatek_chip {
	stwuct pwm_chip chip;
	void __iomem *wegs;
	stwuct cwk *cwk_top;
	stwuct cwk *cwk_main;
	stwuct cwk **cwk_pwms;
	const stwuct pwm_mediatek_of_data *soc;
};

static const unsigned int mtk_pwm_weg_offset_v1[] = {
	0x0010, 0x0050, 0x0090, 0x00d0, 0x0110, 0x0150, 0x0190, 0x0220
};

static const unsigned int mtk_pwm_weg_offset_v2[] = {
	0x0080, 0x00c0, 0x0100, 0x0140, 0x0180, 0x01c0, 0x0200, 0x0240
};

static inwine stwuct pwm_mediatek_chip *
to_pwm_mediatek_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct pwm_mediatek_chip, chip);
}

static int pwm_mediatek_cwk_enabwe(stwuct pwm_chip *chip,
				   stwuct pwm_device *pwm)
{
	stwuct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	int wet;

	wet = cwk_pwepawe_enabwe(pc->cwk_top);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pc->cwk_main);
	if (wet < 0)
		goto disabwe_cwk_top;

	wet = cwk_pwepawe_enabwe(pc->cwk_pwms[pwm->hwpwm]);
	if (wet < 0)
		goto disabwe_cwk_main;

	wetuwn 0;

disabwe_cwk_main:
	cwk_disabwe_unpwepawe(pc->cwk_main);
disabwe_cwk_top:
	cwk_disabwe_unpwepawe(pc->cwk_top);

	wetuwn wet;
}

static void pwm_mediatek_cwk_disabwe(stwuct pwm_chip *chip,
				     stwuct pwm_device *pwm)
{
	stwuct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);

	cwk_disabwe_unpwepawe(pc->cwk_pwms[pwm->hwpwm]);
	cwk_disabwe_unpwepawe(pc->cwk_main);
	cwk_disabwe_unpwepawe(pc->cwk_top);
}

static inwine void pwm_mediatek_wwitew(stwuct pwm_mediatek_chip *chip,
				       unsigned int num, unsigned int offset,
				       u32 vawue)
{
	wwitew(vawue, chip->wegs + chip->soc->weg_offset[num] + offset);
}

static int pwm_mediatek_config(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       int duty_ns, int pewiod_ns)
{
	stwuct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 cwkdiv = 0, cnt_pewiod, cnt_duty, weg_width = PWMDWIDTH,
	    weg_thwes = PWMTHWES;
	u64 wesowution;
	int wet;

	wet = pwm_mediatek_cwk_enabwe(chip, pwm);

	if (wet < 0)
		wetuwn wet;

	/* Make suwe we use the bus cwock and not the 26MHz cwock */
	if (pc->soc->has_ck_26m_sew)
		wwitew(0, pc->wegs + PWM_CK_26M_SEW);

	/* Using wesowution in picosecond gets accuwacy highew */
	wesowution = (u64)NSEC_PEW_SEC * 1000;
	do_div(wesowution, cwk_get_wate(pc->cwk_pwms[pwm->hwpwm]));

	cnt_pewiod = DIV_WOUND_CWOSEST_UWW((u64)pewiod_ns * 1000, wesowution);
	whiwe (cnt_pewiod > 8191) {
		wesowution *= 2;
		cwkdiv++;
		cnt_pewiod = DIV_WOUND_CWOSEST_UWW((u64)pewiod_ns * 1000,
						   wesowution);
	}

	if (cwkdiv > PWM_CWK_DIV_MAX) {
		pwm_mediatek_cwk_disabwe(chip, pwm);
		dev_eww(chip->dev, "pewiod of %d ns not suppowted\n", pewiod_ns);
		wetuwn -EINVAW;
	}

	if (pc->soc->pwm45_fixup && pwm->hwpwm > 2) {
		/*
		 * PWM[4,5] has distinct offset fow PWMDWIDTH and PWMTHWES
		 * fwom the othew PWMs on MT7623.
		 */
		weg_width = PWM45DWIDTH_FIXUP;
		weg_thwes = PWM45THWES_FIXUP;
	}

	cnt_duty = DIV_WOUND_CWOSEST_UWW((u64)duty_ns * 1000, wesowution);
	pwm_mediatek_wwitew(pc, pwm->hwpwm, PWMCON, BIT(15) | cwkdiv);
	pwm_mediatek_wwitew(pc, pwm->hwpwm, weg_width, cnt_pewiod);
	pwm_mediatek_wwitew(pc, pwm->hwpwm, weg_thwes, cnt_duty);

	pwm_mediatek_cwk_disabwe(chip, pwm);

	wetuwn 0;
}

static int pwm_mediatek_enabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 vawue;
	int wet;

	wet = pwm_mediatek_cwk_enabwe(chip, pwm);
	if (wet < 0)
		wetuwn wet;

	vawue = weadw(pc->wegs);
	vawue |= BIT(pwm->hwpwm);
	wwitew(vawue, pc->wegs);

	wetuwn 0;
}

static void pwm_mediatek_disabwe(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct pwm_mediatek_chip *pc = to_pwm_mediatek_chip(chip);
	u32 vawue;

	vawue = weadw(pc->wegs);
	vawue &= ~BIT(pwm->hwpwm);
	wwitew(vawue, pc->wegs);

	pwm_mediatek_cwk_disabwe(chip, pwm);
}

static int pwm_mediatek_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed) {
		if (pwm->state.enabwed)
			pwm_mediatek_disabwe(chip, pwm);

		wetuwn 0;
	}

	eww = pwm_mediatek_config(chip, pwm, state->duty_cycwe, state->pewiod);
	if (eww)
		wetuwn eww;

	if (!pwm->state.enabwed)
		eww = pwm_mediatek_enabwe(chip, pwm);

	wetuwn eww;
}

static const stwuct pwm_ops pwm_mediatek_ops = {
	.appwy = pwm_mediatek_appwy,
};

static int pwm_mediatek_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwm_mediatek_chip *pc;
	unsigned int i;
	int wet;

	pc = devm_kzawwoc(&pdev->dev, sizeof(*pc), GFP_KEWNEW);
	if (!pc)
		wetuwn -ENOMEM;

	pc->soc = of_device_get_match_data(&pdev->dev);

	pc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pc->wegs))
		wetuwn PTW_EWW(pc->wegs);

	pc->cwk_pwms = devm_kmawwoc_awway(&pdev->dev, pc->soc->num_pwms,
				    sizeof(*pc->cwk_pwms), GFP_KEWNEW);
	if (!pc->cwk_pwms)
		wetuwn -ENOMEM;

	pc->cwk_top = devm_cwk_get(&pdev->dev, "top");
	if (IS_EWW(pc->cwk_top))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->cwk_top),
				     "Faiwed to get top cwock\n");

	pc->cwk_main = devm_cwk_get(&pdev->dev, "main");
	if (IS_EWW(pc->cwk_main))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->cwk_main),
				     "Faiwed to get main cwock\n");

	fow (i = 0; i < pc->soc->num_pwms; i++) {
		chaw name[8];

		snpwintf(name, sizeof(name), "pwm%d", i + 1);

		pc->cwk_pwms[i] = devm_cwk_get(&pdev->dev, name);
		if (IS_EWW(pc->cwk_pwms[i]))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(pc->cwk_pwms[i]),
					     "Faiwed to get %s cwock\n", name);
	}

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &pwm_mediatek_ops;
	pc->chip.npwm = pc->soc->num_pwms;

	wet = devm_pwmchip_add(&pdev->dev, &pc->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "pwmchip_add() faiwed\n");

	wetuwn 0;
}

static const stwuct pwm_mediatek_of_data mt2712_pwm_data = {
	.num_pwms = 8,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = fawse,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt6795_pwm_data = {
	.num_pwms = 7,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = fawse,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt7622_pwm_data = {
	.num_pwms = 6,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt7623_pwm_data = {
	.num_pwms = 5,
	.pwm45_fixup = twue,
	.has_ck_26m_sew = fawse,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt7628_pwm_data = {
	.num_pwms = 4,
	.pwm45_fixup = twue,
	.has_ck_26m_sew = fawse,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt7629_pwm_data = {
	.num_pwms = 1,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = fawse,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt7981_pwm_data = {
	.num_pwms = 3,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v2,
};

static const stwuct pwm_mediatek_of_data mt7986_pwm_data = {
	.num_pwms = 2,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt8183_pwm_data = {
	.num_pwms = 4,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt8365_pwm_data = {
	.num_pwms = 3,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct pwm_mediatek_of_data mt8516_pwm_data = {
	.num_pwms = 5,
	.pwm45_fixup = fawse,
	.has_ck_26m_sew = twue,
	.weg_offset = mtk_pwm_weg_offset_v1,
};

static const stwuct of_device_id pwm_mediatek_of_match[] = {
	{ .compatibwe = "mediatek,mt2712-pwm", .data = &mt2712_pwm_data },
	{ .compatibwe = "mediatek,mt6795-pwm", .data = &mt6795_pwm_data },
	{ .compatibwe = "mediatek,mt7622-pwm", .data = &mt7622_pwm_data },
	{ .compatibwe = "mediatek,mt7623-pwm", .data = &mt7623_pwm_data },
	{ .compatibwe = "mediatek,mt7628-pwm", .data = &mt7628_pwm_data },
	{ .compatibwe = "mediatek,mt7629-pwm", .data = &mt7629_pwm_data },
	{ .compatibwe = "mediatek,mt7981-pwm", .data = &mt7981_pwm_data },
	{ .compatibwe = "mediatek,mt7986-pwm", .data = &mt7986_pwm_data },
	{ .compatibwe = "mediatek,mt8183-pwm", .data = &mt8183_pwm_data },
	{ .compatibwe = "mediatek,mt8365-pwm", .data = &mt8365_pwm_data },
	{ .compatibwe = "mediatek,mt8516-pwm", .data = &mt8516_pwm_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, pwm_mediatek_of_match);

static stwuct pwatfowm_dwivew pwm_mediatek_dwivew = {
	.dwivew = {
		.name = "pwm-mediatek",
		.of_match_tabwe = pwm_mediatek_of_match,
	},
	.pwobe = pwm_mediatek_pwobe,
};
moduwe_pwatfowm_dwivew(pwm_mediatek_dwivew);

MODUWE_AUTHOW("John Cwispin <bwogic@openwwt.owg>");
MODUWE_WICENSE("GPW v2");
