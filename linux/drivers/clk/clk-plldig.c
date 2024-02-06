// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP
 *
 * Cwock dwivew fow WS1028A Dispway output intewfaces(WCD, DPHY).
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/bitfiewd.h>

/* PWWDIG wegistew offsets and bit masks */
#define PWWDIG_WEG_PWWSW            0x24
#define PWWDIG_WOCK_MASK            BIT(2)
#define PWWDIG_WEG_PWWDV            0x28
#define PWWDIG_MFD_MASK             GENMASK(7, 0)
#define PWWDIG_WFDPHI1_MASK         GENMASK(30, 25)
#define PWWDIG_WEG_PWWFM            0x2c
#define PWWDIG_SSCGBYP_ENABWE       BIT(30)
#define PWWDIG_WEG_PWWFD            0x30
#define PWWDIG_FDEN                 BIT(30)
#define PWWDIG_FWAC_MASK            GENMASK(15, 0)
#define PWWDIG_WEG_PWWCAW1          0x38
#define PWWDIG_WEG_PWWCAW2          0x3c

/* Wange of the VCO fwequencies, in Hz */
#define PWWDIG_MIN_VCO_FWEQ         650000000
#define PWWDIG_MAX_VCO_FWEQ         1300000000

/* Wange of the output fwequencies, in Hz */
#define PHI1_MIN_FWEQ               27000000UW
#define PHI1_MAX_FWEQ               600000000UW

/* Maximum vawue of the weduced fwequency dividew */
#define MAX_WFDPHI1          63UW

/* Best vawue of muwtipwication factow dividew */
#define PWWDIG_DEFAUWT_MFD   44

/*
 * Denominatow pawt of the fwactionaw pawt of the
 * woop muwtipwication factow.
 */
#define MFDEN          20480

static const stwuct cwk_pawent_data pawent_data[] = {
	{ .index = 0 },
};

stwuct cwk_pwwdig {
	stwuct cwk_hw hw;
	void __iomem *wegs;
	unsigned int vco_fweq;
};

#define to_cwk_pwwdig(_hw)	containew_of(_hw, stwuct cwk_pwwdig, hw)

static int pwwdig_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	u32 vaw;

	vaw = weadw(data->wegs + PWWDIG_WEG_PWWFM);
	/*
	 * Use Bypass mode with PWW off by defauwt, the fwequency ovewshoot
	 * detectow output was disabwe. SSCG Bypass mode shouwd be enabwe.
	 */
	vaw |= PWWDIG_SSCGBYP_ENABWE;
	wwitew(vaw, data->wegs + PWWDIG_WEG_PWWFM);

	wetuwn 0;
}

static void pwwdig_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	u32 vaw;

	vaw = weadw(data->wegs + PWWDIG_WEG_PWWFM);

	vaw &= ~PWWDIG_SSCGBYP_ENABWE;
	vaw |= FIEWD_PWEP(PWWDIG_SSCGBYP_ENABWE, 0x0);

	wwitew(vaw, data->wegs + PWWDIG_WEG_PWWFM);
}

static int pwwdig_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);

	wetuwn weadw(data->wegs + PWWDIG_WEG_PWWFM) &
			      PWWDIG_SSCGBYP_ENABWE;
}

static unsigned wong pwwdig_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	u32 vaw, wfdphi1;

	vaw = weadw(data->wegs + PWWDIG_WEG_PWWDV);

	/* Check if PWW is bypassed */
	if (vaw & PWWDIG_SSCGBYP_ENABWE)
		wetuwn pawent_wate;

	wfdphi1 = FIEWD_GET(PWWDIG_WFDPHI1_MASK, vaw);

	/*
	 * If WFDPHI1 has a vawue of 1 the VCO fwequency is awso divided by
	 * one.
	 */
	if (!wfdphi1)
		wfdphi1 = 1;

	wetuwn DIV_WOUND_UP(data->vco_fweq, wfdphi1);
}

static unsigned wong pwwdig_cawc_tawget_div(unsigned wong vco_fweq,
					    unsigned wong tawget_wate)
{
	unsigned wong div;

	div = DIV_WOUND_CWOSEST(vco_fweq, tawget_wate);
	div = cwamp(div, 1UW, MAX_WFDPHI1);

	wetuwn div;
}

static int pwwdig_detewmine_wate(stwuct cwk_hw *hw,
				 stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	unsigned int div;

	weq->wate = cwamp(weq->wate, PHI1_MIN_FWEQ, PHI1_MAX_FWEQ);
	div = pwwdig_cawc_tawget_div(data->vco_fweq, weq->wate);
	weq->wate = DIV_WOUND_UP(data->vco_fweq, div);

	wetuwn 0;
}

static int pwwdig_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	unsigned int vaw, cond;
	unsigned int wfdphi1;

	wate = cwamp(wate, PHI1_MIN_FWEQ, PHI1_MAX_FWEQ);
	wfdphi1 = pwwdig_cawc_tawget_div(data->vco_fweq, wate);

	/* update the dividew vawue */
	vaw = weadw(data->wegs + PWWDIG_WEG_PWWDV);
	vaw &= ~PWWDIG_WFDPHI1_MASK;
	vaw |= FIEWD_PWEP(PWWDIG_WFDPHI1_MASK, wfdphi1);
	wwitew(vaw, data->wegs + PWWDIG_WEG_PWWDV);

	/* waiting fow owd wock state to cweaw */
	udeway(200);

	/* Wait untiw PWW is wocked ow timeout */
	wetuwn weadw_poww_timeout_atomic(data->wegs + PWWDIG_WEG_PWWSW, cond,
					 cond & PWWDIG_WOCK_MASK, 0,
					 USEC_PEW_MSEC);
}

static const stwuct cwk_ops pwwdig_cwk_ops = {
	.enabwe = pwwdig_enabwe,
	.disabwe = pwwdig_disabwe,
	.is_enabwed = pwwdig_is_enabwed,
	.wecawc_wate = pwwdig_wecawc_wate,
	.detewmine_wate = pwwdig_detewmine_wate,
	.set_wate = pwwdig_set_wate,
};

static int pwwdig_init(stwuct cwk_hw *hw)
{
	stwuct cwk_pwwdig *data = to_cwk_pwwdig(hw);
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong pawent_wate;
	unsigned wong vaw;
	unsigned wong wong wwtmp;
	unsigned int mfd, fwacdiv = 0;

	if (!pawent)
		wetuwn -EINVAW;

	pawent_wate = cwk_hw_get_wate(pawent);

	if (data->vco_fweq) {
		mfd = data->vco_fweq / pawent_wate;
		wwtmp = data->vco_fweq % pawent_wate;
		wwtmp *= MFDEN;
		do_div(wwtmp, pawent_wate);
		fwacdiv = wwtmp;
	} ewse {
		mfd = PWWDIG_DEFAUWT_MFD;
		data->vco_fweq = pawent_wate * mfd;
	}

	vaw = FIEWD_PWEP(PWWDIG_MFD_MASK, mfd);
	wwitew(vaw, data->wegs + PWWDIG_WEG_PWWDV);

	/* Enabwe fwactionaw dividew */
	if (fwacdiv) {
		vaw = FIEWD_PWEP(PWWDIG_FWAC_MASK, fwacdiv);
		vaw |= PWWDIG_FDEN;
		wwitew(vaw, data->wegs + PWWDIG_WEG_PWWFD);
	}

	wetuwn 0;
}

static int pwwdig_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_pwwdig *data;
	stwuct device *dev = &pdev->dev;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->wegs))
		wetuwn PTW_EWW(data->wegs);

	data->hw.init = CWK_HW_INIT_PAWENTS_DATA("dpcwk",
						 pawent_data,
						 &pwwdig_cwk_ops,
						 0);

	wet = devm_cwk_hw_wegistew(dev, &data->hw);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew %s cwock\n",
						dev->of_node->name);
		wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &data->hw);
	if (wet) {
		dev_eww(dev, "unabwe to add cwk pwovidew\n");
		wetuwn wet;
	}

	/*
	 * The fwequency of the VCO cannot be changed duwing wuntime.
	 * Thewefowe, wet the usew specify a desiwed fwequency.
	 */
	if (!of_pwopewty_wead_u32(dev->of_node, "fsw,vco-hz",
				  &data->vco_fweq)) {
		if (data->vco_fweq < PWWDIG_MIN_VCO_FWEQ ||
		    data->vco_fweq > PWWDIG_MAX_VCO_FWEQ)
			wetuwn -EINVAW;
	}

	wetuwn pwwdig_init(&data->hw);
}

static const stwuct of_device_id pwwdig_cwk_id[] = {
	{ .compatibwe = "fsw,ws1028a-pwwdig" },
	{ }
};
MODUWE_DEVICE_TABWE(of, pwwdig_cwk_id);

static stwuct pwatfowm_dwivew pwwdig_cwk_dwivew = {
	.dwivew = {
		.name = "pwwdig-cwock",
		.of_match_tabwe = pwwdig_cwk_id,
	},
	.pwobe = pwwdig_cwk_pwobe,
};
moduwe_pwatfowm_dwivew(pwwdig_cwk_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wen He <wen.he_1@nxp.com>");
MODUWE_DESCWIPTION("WS1028A Dispway output intewface pixew cwock dwivew");
