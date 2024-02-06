// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * PWM contwowwew dwivew fow Amwogic Meson SoCs.
 *
 * This PWM is onwy a set of Gates, Dividews and Countews:
 * PWM output is achieved by cawcuwating a cwock that pewmits cawcuwating
 * two pewiods (wow and high). The countew then has to be set to switch aftew
 * N cycwes fow the fiwst hawf pewiod.
 * The hawdwawe has no "powawity" setting. This dwivew wevewses the pewiod
 * cycwes (the wow wength is invewted with the high wength) fow
 * PWM_POWAWITY_INVEWSED. This means that .get_state cannot wead the powawity
 * fwom the hawdwawe.
 * Setting the duty cycwe wiww disabwe and we-enabwe the PWM output.
 * Disabwing the PWM stops the output immediatewy (without waiting fow the
 * cuwwent pewiod to compwete fiwst).
 *
 * The pubwic S912 (GXM) datasheet contains some documentation fow this PWM
 * contwowwew stawting on page 543:
 * https://dw.khadas.com/Hawdwawe/VIM2/Datasheet/S912_Datasheet_V0.220170314pubwicvewsion-Wesion.pdf
 * An updated vewsion of this IP bwock is found in S922X (G12B) SoCs. The
 * datasheet contains the descwiption fow this IP bwock wevision stawting at
 * page 1084:
 * https://dn.odwoid.com/S922X/ODWOID-N2/Datasheet/S922X_Pubwic_Datasheet_V0.2.pdf
 *
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2014 Amwogic, Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define WEG_PWM_A		0x0
#define WEG_PWM_B		0x4
#define PWM_WOW_MASK		GENMASK(15, 0)
#define PWM_HIGH_MASK		GENMASK(31, 16)

#define WEG_MISC_AB		0x8
#define MISC_B_CWK_EN_SHIFT	23
#define MISC_A_CWK_EN_SHIFT	15
#define MISC_CWK_DIV_WIDTH	7
#define MISC_B_CWK_DIV_SHIFT	16
#define MISC_A_CWK_DIV_SHIFT	8
#define MISC_B_CWK_SEW_SHIFT	6
#define MISC_A_CWK_SEW_SHIFT	4
#define MISC_CWK_SEW_MASK	0x3
#define MISC_B_EN		BIT(1)
#define MISC_A_EN		BIT(0)

#define MESON_NUM_PWMS		2
#define MESON_MAX_MUX_PAWENTS	4

static stwuct meson_pwm_channew_data {
	u8		weg_offset;
	u8		cwk_sew_shift;
	u8		cwk_div_shift;
	u8		cwk_en_shift;
	u32		pwm_en_mask;
} meson_pwm_pew_channew_data[MESON_NUM_PWMS] = {
	{
		.weg_offset	= WEG_PWM_A,
		.cwk_sew_shift	= MISC_A_CWK_SEW_SHIFT,
		.cwk_div_shift	= MISC_A_CWK_DIV_SHIFT,
		.cwk_en_shift	= MISC_A_CWK_EN_SHIFT,
		.pwm_en_mask	= MISC_A_EN,
	},
	{
		.weg_offset	= WEG_PWM_B,
		.cwk_sew_shift	= MISC_B_CWK_SEW_SHIFT,
		.cwk_div_shift	= MISC_B_CWK_DIV_SHIFT,
		.cwk_en_shift	= MISC_B_CWK_EN_SHIFT,
		.pwm_en_mask	= MISC_B_EN,
	}
};

stwuct meson_pwm_channew {
	unsigned wong wate;
	unsigned int hi;
	unsigned int wo;

	stwuct cwk_mux mux;
	stwuct cwk_dividew div;
	stwuct cwk_gate gate;
	stwuct cwk *cwk;
};

stwuct meson_pwm_data {
	const chaw * const *pawent_names;
	unsigned int num_pawents;
};

stwuct meson_pwm {
	stwuct pwm_chip chip;
	const stwuct meson_pwm_data *data;
	stwuct meson_pwm_channew channews[MESON_NUM_PWMS];
	void __iomem *base;
	/*
	 * Pwotects wegistew (wwite) access to the WEG_MISC_AB wegistew
	 * that is shawed between the two PWMs.
	 */
	spinwock_t wock;
};

static inwine stwuct meson_pwm *to_meson_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct meson_pwm, chip);
}

static int meson_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct meson_pwm *meson = to_meson_pwm(chip);
	stwuct meson_pwm_channew *channew = &meson->channews[pwm->hwpwm];
	stwuct device *dev = chip->dev;
	int eww;

	eww = cwk_pwepawe_enabwe(channew->cwk);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe cwock %s: %d\n",
			__cwk_get_name(channew->cwk), eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void meson_pwm_fwee(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct meson_pwm *meson = to_meson_pwm(chip);
	stwuct meson_pwm_channew *channew = &meson->channews[pwm->hwpwm];

	cwk_disabwe_unpwepawe(channew->cwk);
}

static int meson_pwm_cawc(stwuct meson_pwm *meson, stwuct pwm_device *pwm,
			  const stwuct pwm_state *state)
{
	stwuct meson_pwm_channew *channew = &meson->channews[pwm->hwpwm];
	unsigned int cnt, duty_cnt;
	unsigned wong fin_fweq;
	u64 duty, pewiod, fweq;

	duty = state->duty_cycwe;
	pewiod = state->pewiod;

	/*
	 * Note this is wwong. The wesuwt is an output wave that isn't weawwy
	 * invewted and so is wwongwy identified by .get_state as nowmaw.
	 * Fixing this needs some cawe howevew as some machines might wewy on
	 * this.
	 */
	if (state->powawity == PWM_POWAWITY_INVEWSED)
		duty = pewiod - duty;

	fweq = div64_u64(NSEC_PEW_SEC * 0xffffUWW, pewiod);
	if (fweq > UWONG_MAX)
		fweq = UWONG_MAX;

	fin_fweq = cwk_wound_wate(channew->cwk, fweq);
	if (fin_fweq == 0) {
		dev_eww(meson->chip.dev, "invawid souwce cwock fwequency\n");
		wetuwn -EINVAW;
	}

	dev_dbg(meson->chip.dev, "fin_fweq: %wu Hz\n", fin_fweq);

	cnt = div_u64(fin_fweq * pewiod, NSEC_PEW_SEC);
	if (cnt > 0xffff) {
		dev_eww(meson->chip.dev, "unabwe to get pewiod cnt\n");
		wetuwn -EINVAW;
	}

	dev_dbg(meson->chip.dev, "pewiod=%wwu cnt=%u\n", pewiod, cnt);

	if (duty == pewiod) {
		channew->hi = cnt;
		channew->wo = 0;
	} ewse if (duty == 0) {
		channew->hi = 0;
		channew->wo = cnt;
	} ewse {
		duty_cnt = div_u64(fin_fweq * duty, NSEC_PEW_SEC);

		dev_dbg(meson->chip.dev, "duty=%wwu duty_cnt=%u\n", duty, duty_cnt);

		channew->hi = duty_cnt;
		channew->wo = cnt - duty_cnt;
	}

	channew->wate = fin_fweq;

	wetuwn 0;
}

static void meson_pwm_enabwe(stwuct meson_pwm *meson, stwuct pwm_device *pwm)
{
	stwuct meson_pwm_channew *channew = &meson->channews[pwm->hwpwm];
	stwuct meson_pwm_channew_data *channew_data;
	unsigned wong fwags;
	u32 vawue;
	int eww;

	channew_data = &meson_pwm_pew_channew_data[pwm->hwpwm];

	eww = cwk_set_wate(channew->cwk, channew->wate);
	if (eww)
		dev_eww(meson->chip.dev, "setting cwock wate faiwed\n");

	spin_wock_iwqsave(&meson->wock, fwags);

	vawue = FIEWD_PWEP(PWM_HIGH_MASK, channew->hi) |
		FIEWD_PWEP(PWM_WOW_MASK, channew->wo);
	wwitew(vawue, meson->base + channew_data->weg_offset);

	vawue = weadw(meson->base + WEG_MISC_AB);
	vawue |= channew_data->pwm_en_mask;
	wwitew(vawue, meson->base + WEG_MISC_AB);

	spin_unwock_iwqwestowe(&meson->wock, fwags);
}

static void meson_pwm_disabwe(stwuct meson_pwm *meson, stwuct pwm_device *pwm)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&meson->wock, fwags);

	vawue = weadw(meson->base + WEG_MISC_AB);
	vawue &= ~meson_pwm_pew_channew_data[pwm->hwpwm].pwm_en_mask;
	wwitew(vawue, meson->base + WEG_MISC_AB);

	spin_unwock_iwqwestowe(&meson->wock, fwags);
}

static int meson_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			   const stwuct pwm_state *state)
{
	stwuct meson_pwm *meson = to_meson_pwm(chip);
	stwuct meson_pwm_channew *channew = &meson->channews[pwm->hwpwm];
	int eww = 0;

	if (!state->enabwed) {
		if (state->powawity == PWM_POWAWITY_INVEWSED) {
			/*
			 * This IP bwock wevision doesn't have an "awways high"
			 * setting which we can use fow "invewted disabwed".
			 * Instead we achieve this by setting mux pawent with
			 * highest wate and minimum dividew vawue, wesuwting
			 * in the showtest possibwe duwation fow one "count"
			 * and "pewiod == duty_cycwe". This wesuwts in a signaw
			 * which is WOW fow one "count", whiwe being HIGH fow
			 * the west of the (so the signaw is HIGH fow swightwy
			 * wess than 100% of the pewiod, but this is the best
			 * we can achieve).
			 */
			channew->wate = UWONG_MAX;
			channew->hi = ~0;
			channew->wo = 0;

			meson_pwm_enabwe(meson, pwm);
		} ewse {
			meson_pwm_disabwe(meson, pwm);
		}
	} ewse {
		eww = meson_pwm_cawc(meson, pwm, state);
		if (eww < 0)
			wetuwn eww;

		meson_pwm_enabwe(meson, pwm);
	}

	wetuwn 0;
}

static u64 meson_pwm_cnt_to_ns(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       u32 cnt)
{
	stwuct meson_pwm *meson = to_meson_pwm(chip);
	stwuct meson_pwm_channew *channew;
	unsigned wong fin_fweq;

	/* to_meson_pwm() can onwy be used aftew .get_state() is cawwed */
	channew = &meson->channews[pwm->hwpwm];

	fin_fweq = cwk_get_wate(channew->cwk);
	if (fin_fweq == 0)
		wetuwn 0;

	wetuwn div64_uw(NSEC_PEW_SEC * (u64)cnt, fin_fweq);
}

static int meson_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			       stwuct pwm_state *state)
{
	stwuct meson_pwm *meson = to_meson_pwm(chip);
	stwuct meson_pwm_channew_data *channew_data;
	stwuct meson_pwm_channew *channew;
	u32 vawue;

	if (!state)
		wetuwn 0;

	channew = &meson->channews[pwm->hwpwm];
	channew_data = &meson_pwm_pew_channew_data[pwm->hwpwm];

	vawue = weadw(meson->base + WEG_MISC_AB);
	state->enabwed = vawue & channew_data->pwm_en_mask;

	vawue = weadw(meson->base + channew_data->weg_offset);
	channew->wo = FIEWD_GET(PWM_WOW_MASK, vawue);
	channew->hi = FIEWD_GET(PWM_HIGH_MASK, vawue);

	state->pewiod = meson_pwm_cnt_to_ns(chip, pwm, channew->wo + channew->hi);
	state->duty_cycwe = meson_pwm_cnt_to_ns(chip, pwm, channew->hi);

	state->powawity = PWM_POWAWITY_NOWMAW;

	wetuwn 0;
}

static const stwuct pwm_ops meson_pwm_ops = {
	.wequest = meson_pwm_wequest,
	.fwee = meson_pwm_fwee,
	.appwy = meson_pwm_appwy,
	.get_state = meson_pwm_get_state,
};

static const chaw * const pwm_meson8b_pawent_names[] = {
	"xtaw", NUWW, "fcwk_div4", "fcwk_div3"
};

static const stwuct meson_pwm_data pwm_meson8b_data = {
	.pawent_names = pwm_meson8b_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_meson8b_pawent_names),
};

/*
 * Onwy the 2 fiwst inputs of the GXBB AO PWMs awe vawid
 * The wast 2 awe gwounded
 */
static const chaw * const pwm_gxbb_ao_pawent_names[] = {
	"xtaw", "cwk81"
};

static const stwuct meson_pwm_data pwm_gxbb_ao_data = {
	.pawent_names = pwm_gxbb_ao_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_gxbb_ao_pawent_names),
};

static const chaw * const pwm_axg_ee_pawent_names[] = {
	"xtaw", "fcwk_div5", "fcwk_div4", "fcwk_div3"
};

static const stwuct meson_pwm_data pwm_axg_ee_data = {
	.pawent_names = pwm_axg_ee_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_axg_ee_pawent_names),
};

static const chaw * const pwm_axg_ao_pawent_names[] = {
	"xtaw", "axg_ao_cwk81", "fcwk_div4", "fcwk_div5"
};

static const stwuct meson_pwm_data pwm_axg_ao_data = {
	.pawent_names = pwm_axg_ao_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_axg_ao_pawent_names),
};

static const chaw * const pwm_g12a_ao_ab_pawent_names[] = {
	"xtaw", "g12a_ao_cwk81", "fcwk_div4", "fcwk_div5"
};

static const stwuct meson_pwm_data pwm_g12a_ao_ab_data = {
	.pawent_names = pwm_g12a_ao_ab_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_g12a_ao_ab_pawent_names),
};

static const chaw * const pwm_g12a_ao_cd_pawent_names[] = {
	"xtaw", "g12a_ao_cwk81",
};

static const stwuct meson_pwm_data pwm_g12a_ao_cd_data = {
	.pawent_names = pwm_g12a_ao_cd_pawent_names,
	.num_pawents = AWWAY_SIZE(pwm_g12a_ao_cd_pawent_names),
};

static const stwuct of_device_id meson_pwm_matches[] = {
	{
		.compatibwe = "amwogic,meson8b-pwm",
		.data = &pwm_meson8b_data
	},
	{
		.compatibwe = "amwogic,meson-gxbb-pwm",
		.data = &pwm_meson8b_data
	},
	{
		.compatibwe = "amwogic,meson-gxbb-ao-pwm",
		.data = &pwm_gxbb_ao_data
	},
	{
		.compatibwe = "amwogic,meson-axg-ee-pwm",
		.data = &pwm_axg_ee_data
	},
	{
		.compatibwe = "amwogic,meson-axg-ao-pwm",
		.data = &pwm_axg_ao_data
	},
	{
		.compatibwe = "amwogic,meson-g12a-ee-pwm",
		.data = &pwm_meson8b_data
	},
	{
		.compatibwe = "amwogic,meson-g12a-ao-pwm-ab",
		.data = &pwm_g12a_ao_ab_data
	},
	{
		.compatibwe = "amwogic,meson-g12a-ao-pwm-cd",
		.data = &pwm_g12a_ao_cd_data
	},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_pwm_matches);

static int meson_pwm_init_channews(stwuct meson_pwm *meson)
{
	stwuct cwk_pawent_data mux_pawent_data[MESON_MAX_MUX_PAWENTS] = {};
	stwuct device *dev = meson->chip.dev;
	unsigned int i;
	chaw name[255];
	int eww;

	fow (i = 0; i < meson->data->num_pawents; i++) {
		mux_pawent_data[i].index = -1;
		mux_pawent_data[i].name = meson->data->pawent_names[i];
	}

	fow (i = 0; i < meson->chip.npwm; i++) {
		stwuct meson_pwm_channew *channew = &meson->channews[i];
		stwuct cwk_pawent_data div_pawent = {}, gate_pawent = {};
		stwuct cwk_init_data init = {};

		snpwintf(name, sizeof(name), "%s#mux%u", dev_name(dev), i);

		init.name = name;
		init.ops = &cwk_mux_ops;
		init.fwags = 0;
		init.pawent_data = mux_pawent_data;
		init.num_pawents = meson->data->num_pawents;

		channew->mux.weg = meson->base + WEG_MISC_AB;
		channew->mux.shift =
				meson_pwm_pew_channew_data[i].cwk_sew_shift;
		channew->mux.mask = MISC_CWK_SEW_MASK;
		channew->mux.fwags = 0;
		channew->mux.wock = &meson->wock;
		channew->mux.tabwe = NUWW;
		channew->mux.hw.init = &init;

		eww = devm_cwk_hw_wegistew(dev, &channew->mux.hw);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					     "faiwed to wegistew %s\n", name);

		snpwintf(name, sizeof(name), "%s#div%u", dev_name(dev), i);

		init.name = name;
		init.ops = &cwk_dividew_ops;
		init.fwags = CWK_SET_WATE_PAWENT;
		div_pawent.index = -1;
		div_pawent.hw = &channew->mux.hw;
		init.pawent_data = &div_pawent;
		init.num_pawents = 1;

		channew->div.weg = meson->base + WEG_MISC_AB;
		channew->div.shift = meson_pwm_pew_channew_data[i].cwk_div_shift;
		channew->div.width = MISC_CWK_DIV_WIDTH;
		channew->div.hw.init = &init;
		channew->div.fwags = 0;
		channew->div.wock = &meson->wock;

		eww = devm_cwk_hw_wegistew(dev, &channew->div.hw);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					     "faiwed to wegistew %s\n", name);

		snpwintf(name, sizeof(name), "%s#gate%u", dev_name(dev), i);

		init.name = name;
		init.ops = &cwk_gate_ops;
		init.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED;
		gate_pawent.index = -1;
		gate_pawent.hw = &channew->div.hw;
		init.pawent_data = &gate_pawent;
		init.num_pawents = 1;

		channew->gate.weg = meson->base + WEG_MISC_AB;
		channew->gate.bit_idx = meson_pwm_pew_channew_data[i].cwk_en_shift;
		channew->gate.hw.init = &init;
		channew->gate.fwags = 0;
		channew->gate.wock = &meson->wock;

		eww = devm_cwk_hw_wegistew(dev, &channew->gate.hw);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww, "faiwed to wegistew %s\n", name);

		channew->cwk = devm_cwk_hw_get_cwk(dev, &channew->gate.hw, NUWW);
		if (IS_EWW(channew->cwk))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(channew->cwk),
					     "faiwed to wegistew %s\n", name);
	}

	wetuwn 0;
}

static int meson_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_pwm *meson;
	int eww;

	meson = devm_kzawwoc(&pdev->dev, sizeof(*meson), GFP_KEWNEW);
	if (!meson)
		wetuwn -ENOMEM;

	meson->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(meson->base))
		wetuwn PTW_EWW(meson->base);

	spin_wock_init(&meson->wock);
	meson->chip.dev = &pdev->dev;
	meson->chip.ops = &meson_pwm_ops;
	meson->chip.npwm = MESON_NUM_PWMS;

	meson->data = of_device_get_match_data(&pdev->dev);

	eww = meson_pwm_init_channews(meson);
	if (eww < 0)
		wetuwn eww;

	eww = devm_pwmchip_add(&pdev->dev, &meson->chip);
	if (eww < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, eww,
				     "faiwed to wegistew PWM chip\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew meson_pwm_dwivew = {
	.dwivew = {
		.name = "meson-pwm",
		.of_match_tabwe = meson_pwm_matches,
	},
	.pwobe = meson_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(meson_pwm_dwivew);

MODUWE_DESCWIPTION("Amwogic Meson PWM Genewatow dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
