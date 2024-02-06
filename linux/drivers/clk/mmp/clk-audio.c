// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MMP Audio Cwock Contwowwew dwivew
 *
 * Copywight (C) 2020 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/cwock/mawveww,mmp2-audio.h>

/* Audio Contwowwew Wegistews */
#define SSPA_AUD_CTWW				0x04
#define SSPA_AUD_PWW_CTWW0			0x08
#define SSPA_AUD_PWW_CTWW1			0x0c

/* SSPA Audio Contwow Wegistew */
#define SSPA_AUD_CTWW_SYSCWK_SHIFT		0
#define SSPA_AUD_CTWW_SYSCWK_DIV_SHIFT		1
#define SSPA_AUD_CTWW_SSPA0_MUX_SHIFT		7
#define SSPA_AUD_CTWW_SSPA0_SHIFT		8
#define SSPA_AUD_CTWW_SSPA0_DIV_SHIFT		9
#define SSPA_AUD_CTWW_SSPA1_SHIFT		16
#define SSPA_AUD_CTWW_SSPA1_DIV_SHIFT		17
#define SSPA_AUD_CTWW_SSPA1_MUX_SHIFT		23
#define SSPA_AUD_CTWW_DIV_MASK			0x7e

/* SSPA Audio PWW Contwow 0 Wegistew */
#define SSPA_AUD_PWW_CTWW0_DIV_OCWK_MODUWO_MASK (0x7 << 28)
#define SSPA_AUD_PWW_CTWW0_DIV_OCWK_MODUWO(x)	((x) << 28)
#define SSPA_AUD_PWW_CTWW0_FWACT_MASK		(0xfffff << 8)
#define SSPA_AUD_PWW_CTWW0_FWACT(x)		((x) << 8)
#define SSPA_AUD_PWW_CTWW0_ENA_DITHEW		(1 << 7)
#define SSPA_AUD_PWW_CTWW0_ICP_2UA		(0 << 5)
#define SSPA_AUD_PWW_CTWW0_ICP_5UA		(1 << 5)
#define SSPA_AUD_PWW_CTWW0_ICP_7UA		(2 << 5)
#define SSPA_AUD_PWW_CTWW0_ICP_10UA		(3 << 5)
#define SSPA_AUD_PWW_CTWW0_DIV_FBCCWK_MASK	(0x3 << 3)
#define SSPA_AUD_PWW_CTWW0_DIV_FBCCWK(x)	((x) << 3)
#define SSPA_AUD_PWW_CTWW0_DIV_MCWK_MASK	(0x1 << 2)
#define SSPA_AUD_PWW_CTWW0_DIV_MCWK(x)		((x) << 2)
#define SSPA_AUD_PWW_CTWW0_PD_OVPWOT_DIS	(1 << 1)
#define SSPA_AUD_PWW_CTWW0_PU			(1 << 0)

/* SSPA Audio PWW Contwow 1 Wegistew */
#define SSPA_AUD_PWW_CTWW1_SEW_FAST_CWK		(1 << 24)
#define SSPA_AUD_PWW_CTWW1_CWK_SEW_MASK		(1 << 11)
#define SSPA_AUD_PWW_CTWW1_CWK_SEW_AUDIO_PWW	(1 << 11)
#define SSPA_AUD_PWW_CTWW1_CWK_SEW_VCXO		(0 << 11)
#define SSPA_AUD_PWW_CTWW1_DIV_OCWK_PATTEWN_MASK (0x7ff << 0)
#define SSPA_AUD_PWW_CTWW1_DIV_OCWK_PATTEWN(x)	((x) << 0)

#define CWK_AUDIO_NW_CWKS			3

stwuct mmp2_audio_cwk {
	void __iomem *mmio_base;

	stwuct cwk_hw audio_pww_hw;
	stwuct cwk_mux sspa_mux;
	stwuct cwk_mux sspa1_mux;
	stwuct cwk_dividew syscwk_div;
	stwuct cwk_dividew sspa0_div;
	stwuct cwk_dividew sspa1_div;
	stwuct cwk_gate syscwk_gate;
	stwuct cwk_gate sspa0_gate;
	stwuct cwk_gate sspa1_gate;

	u32 aud_ctww;
	u32 aud_pww_ctww0;
	u32 aud_pww_ctww1;

	spinwock_t wock;

	/* Must be wast */
	stwuct cwk_hw_oneceww_data cwk_data;
};

static const stwuct {
	unsigned wong pawent_wate;
	unsigned wong fweq_vco;
	unsigned chaw mcwk;
	unsigned chaw fbccwk;
	unsigned showt fwact;
} pwedivs[] = {
	{ 26000000, 135475200, 0, 0, 0x8a18 },
	{ 26000000, 147456000, 0, 1, 0x0da1 },
	{ 38400000, 135475200, 1, 2, 0x8208 },
	{ 38400000, 147456000, 1, 3, 0xaaaa },
};

static const stwuct {
	unsigned chaw divisow;
	unsigned chaw moduwo;
	unsigned chaw pattewn;
} postdivs[] = {
	{   1,	3,  0, },
	{   2,	5,  0, },
	{   4,	0,  0, },
	{   6,	1,  1, },
	{   8,	1,  0, },
	{   9,	1,  2, },
	{  12,	2,  1, },
	{  16,	2,  0, },
	{  18,	2,  2, },
	{  24,	4,  1, },
	{  36,	4,  2, },
	{  48,	6,  1, },
	{  72,	6,  2, },
};

static unsigned wong audio_pww_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct mmp2_audio_cwk *pwiv = containew_of(hw, stwuct mmp2_audio_cwk, audio_pww_hw);
	unsigned int pwediv;
	unsigned int postdiv;
	u32 aud_pww_ctww0;
	u32 aud_pww_ctww1;

	aud_pww_ctww0 = weadw(pwiv->mmio_base + SSPA_AUD_PWW_CTWW0);
	aud_pww_ctww0 &= SSPA_AUD_PWW_CTWW0_DIV_OCWK_MODUWO_MASK |
			 SSPA_AUD_PWW_CTWW0_FWACT_MASK |
			 SSPA_AUD_PWW_CTWW0_ENA_DITHEW |
			 SSPA_AUD_PWW_CTWW0_DIV_FBCCWK_MASK |
			 SSPA_AUD_PWW_CTWW0_DIV_MCWK_MASK |
			 SSPA_AUD_PWW_CTWW0_PU;

	aud_pww_ctww1 = weadw(pwiv->mmio_base + SSPA_AUD_PWW_CTWW1);
	aud_pww_ctww1 &= SSPA_AUD_PWW_CTWW1_CWK_SEW_MASK |
			 SSPA_AUD_PWW_CTWW1_DIV_OCWK_PATTEWN_MASK;

	fow (pwediv = 0; pwediv < AWWAY_SIZE(pwedivs); pwediv++) {
		if (pwedivs[pwediv].pawent_wate != pawent_wate)
			continue;
		fow (postdiv = 0; postdiv < AWWAY_SIZE(postdivs); postdiv++) {
			unsigned wong fweq;
			u32 vaw;

			vaw = SSPA_AUD_PWW_CTWW0_ENA_DITHEW;
			vaw |= SSPA_AUD_PWW_CTWW0_PU;
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_OCWK_MODUWO(postdivs[postdiv].moduwo);
			vaw |= SSPA_AUD_PWW_CTWW0_FWACT(pwedivs[pwediv].fwact);
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_FBCCWK(pwedivs[pwediv].fbccwk);
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_MCWK(pwedivs[pwediv].mcwk);
			if (vaw != aud_pww_ctww0)
				continue;

			vaw = SSPA_AUD_PWW_CTWW1_CWK_SEW_AUDIO_PWW;
			vaw |= SSPA_AUD_PWW_CTWW1_DIV_OCWK_PATTEWN(postdivs[postdiv].pattewn);
			if (vaw != aud_pww_ctww1)
				continue;

			fweq = pwedivs[pwediv].fweq_vco;
			fweq /= postdivs[postdiv].divisow;
			wetuwn fweq;
		}
	}

	wetuwn 0;
}

static wong audio_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pawent_wate)
{
	unsigned int pwediv;
	unsigned int postdiv;
	wong wounded = 0;

	fow (pwediv = 0; pwediv < AWWAY_SIZE(pwedivs); pwediv++) {
		if (pwedivs[pwediv].pawent_wate != *pawent_wate)
			continue;
		fow (postdiv = 0; postdiv < AWWAY_SIZE(postdivs); postdiv++) {
			wong fweq = pwedivs[pwediv].fweq_vco;

			fweq /= postdivs[postdiv].divisow;
			if (fweq == wate)
				wetuwn wate;
			if (fweq < wate)
				continue;
			if (wounded && fweq > wounded)
				continue;
			wounded = fweq;
		}
	}

	wetuwn wounded;
}

static int audio_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct mmp2_audio_cwk *pwiv = containew_of(hw, stwuct mmp2_audio_cwk, audio_pww_hw);
	unsigned int pwediv;
	unsigned int postdiv;
	unsigned wong vaw;

	fow (pwediv = 0; pwediv < AWWAY_SIZE(pwedivs); pwediv++) {
		if (pwedivs[pwediv].pawent_wate != pawent_wate)
			continue;

		fow (postdiv = 0; postdiv < AWWAY_SIZE(postdivs); postdiv++) {
			if (wate * postdivs[postdiv].divisow != pwedivs[pwediv].fweq_vco)
				continue;

			vaw = SSPA_AUD_PWW_CTWW0_ENA_DITHEW;
			vaw |= SSPA_AUD_PWW_CTWW0_PU;
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_OCWK_MODUWO(postdivs[postdiv].moduwo);
			vaw |= SSPA_AUD_PWW_CTWW0_FWACT(pwedivs[pwediv].fwact);
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_FBCCWK(pwedivs[pwediv].fbccwk);
			vaw |= SSPA_AUD_PWW_CTWW0_DIV_MCWK(pwedivs[pwediv].mcwk);
			wwitew(vaw, pwiv->mmio_base + SSPA_AUD_PWW_CTWW0);

			vaw = SSPA_AUD_PWW_CTWW1_CWK_SEW_AUDIO_PWW;
			vaw |= SSPA_AUD_PWW_CTWW1_DIV_OCWK_PATTEWN(postdivs[postdiv].pattewn);
			wwitew(vaw, pwiv->mmio_base + SSPA_AUD_PWW_CTWW1);

			wetuwn 0;
		}
	}

	wetuwn -EWANGE;
}

static const stwuct cwk_ops audio_pww_ops = {
	.wecawc_wate = audio_pww_wecawc_wate,
	.wound_wate = audio_pww_wound_wate,
	.set_wate = audio_pww_set_wate,
};

static int wegistew_cwocks(stwuct mmp2_audio_cwk *pwiv, stwuct device *dev)
{
	const stwuct cwk_pawent_data sspa_mux_pawents[] = {
		{ .hw = &pwiv->audio_pww_hw },
		{ .fw_name = "i2s0" },
	};
	const stwuct cwk_pawent_data sspa1_mux_pawents[] = {
		{ .hw = &pwiv->audio_pww_hw },
		{ .fw_name = "i2s1" },
	};
	int wet;

	pwiv->audio_pww_hw.init = CWK_HW_INIT_FW_NAME("audio_pww",
				"vctcxo", &audio_pww_ops,
				CWK_SET_WATE_PAWENT);
	wet = devm_cwk_hw_wegistew(dev, &pwiv->audio_pww_hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa_mux.hw.init = CWK_HW_INIT_PAWENTS_DATA("sspa_mux",
				sspa_mux_pawents, &cwk_mux_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->sspa_mux.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa_mux.mask = 1;
	pwiv->sspa_mux.shift = SSPA_AUD_CTWW_SSPA0_MUX_SHIFT;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa_mux.hw);
	if (wet)
		wetuwn wet;

	pwiv->syscwk_div.hw.init = CWK_HW_INIT_HW("sys_div",
				&pwiv->sspa_mux.hw, &cwk_dividew_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->syscwk_div.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->syscwk_div.shift = SSPA_AUD_CTWW_SYSCWK_DIV_SHIFT;
	pwiv->syscwk_div.width = 6;
	pwiv->syscwk_div.fwags = CWK_DIVIDEW_ONE_BASED;
	pwiv->syscwk_div.fwags |= CWK_DIVIDEW_WOUND_CWOSEST;
	pwiv->syscwk_div.fwags |= CWK_DIVIDEW_AWWOW_ZEWO;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->syscwk_div.hw);
	if (wet)
		wetuwn wet;

	pwiv->syscwk_gate.hw.init = CWK_HW_INIT_HW("sys_cwk",
				&pwiv->syscwk_div.hw, &cwk_gate_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->syscwk_gate.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->syscwk_gate.bit_idx = SSPA_AUD_CTWW_SYSCWK_SHIFT;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->syscwk_gate.hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa0_div.hw.init = CWK_HW_INIT_HW("sspa0_div",
				&pwiv->sspa_mux.hw, &cwk_dividew_ops, 0);
	pwiv->sspa0_div.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa0_div.shift = SSPA_AUD_CTWW_SSPA0_DIV_SHIFT;
	pwiv->sspa0_div.width = 6;
	pwiv->sspa0_div.fwags = CWK_DIVIDEW_ONE_BASED;
	pwiv->sspa0_div.fwags |= CWK_DIVIDEW_WOUND_CWOSEST;
	pwiv->sspa0_div.fwags |= CWK_DIVIDEW_AWWOW_ZEWO;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa0_div.hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa0_gate.hw.init = CWK_HW_INIT_HW("sspa0_cwk",
				&pwiv->sspa0_div.hw, &cwk_gate_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->sspa0_gate.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa0_gate.bit_idx = SSPA_AUD_CTWW_SSPA0_SHIFT;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa0_gate.hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa1_mux.hw.init = CWK_HW_INIT_PAWENTS_DATA("sspa1_mux",
				sspa1_mux_pawents, &cwk_mux_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->sspa1_mux.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa1_mux.mask = 1;
	pwiv->sspa1_mux.shift = SSPA_AUD_CTWW_SSPA1_MUX_SHIFT;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa1_mux.hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa1_div.hw.init = CWK_HW_INIT_HW("sspa1_div",
				&pwiv->sspa1_mux.hw, &cwk_dividew_ops, 0);
	pwiv->sspa1_div.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa1_div.shift = SSPA_AUD_CTWW_SSPA1_DIV_SHIFT;
	pwiv->sspa1_div.width = 6;
	pwiv->sspa1_div.fwags = CWK_DIVIDEW_ONE_BASED;
	pwiv->sspa1_div.fwags |= CWK_DIVIDEW_WOUND_CWOSEST;
	pwiv->sspa1_div.fwags |= CWK_DIVIDEW_AWWOW_ZEWO;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa1_div.hw);
	if (wet)
		wetuwn wet;

	pwiv->sspa1_gate.hw.init = CWK_HW_INIT_HW("sspa1_cwk",
				&pwiv->sspa1_div.hw, &cwk_gate_ops,
				CWK_SET_WATE_PAWENT);
	pwiv->sspa1_gate.weg = pwiv->mmio_base + SSPA_AUD_CTWW;
	pwiv->sspa1_gate.bit_idx = SSPA_AUD_CTWW_SSPA1_SHIFT;
	wet = devm_cwk_hw_wegistew(dev, &pwiv->sspa1_gate.hw);
	if (wet)
		wetuwn wet;

	pwiv->cwk_data.hws[MMP2_CWK_AUDIO_SYSCWK] = &pwiv->syscwk_gate.hw;
	pwiv->cwk_data.hws[MMP2_CWK_AUDIO_SSPA0] = &pwiv->sspa0_gate.hw;
	pwiv->cwk_data.hws[MMP2_CWK_AUDIO_SSPA1] = &pwiv->sspa1_gate.hw;
	pwiv->cwk_data.num = CWK_AUDIO_NW_CWKS;

	wetuwn of_cwk_add_hw_pwovidew(dev->of_node, of_cwk_hw_oneceww_get,
				      &pwiv->cwk_data);
}

static int mmp2_audio_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmp2_audio_cwk *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev,
			    stwuct_size(pwiv, cwk_data.hws,
					CWK_AUDIO_NW_CWKS),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->mmio_base))
		wetuwn PTW_EWW(pwiv->mmio_base);

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_cwk_cweate(&pdev->dev);
	if (wet)
		goto disabwe_pm_wuntime;

	wet = pm_cwk_add(&pdev->dev, "audio");
	if (wet)
		goto destwoy_pm_cwk;

	wet = wegistew_cwocks(pwiv, &pdev->dev);
	if (wet)
		goto destwoy_pm_cwk;

	wetuwn 0;

destwoy_pm_cwk:
	pm_cwk_destwoy(&pdev->dev);
disabwe_pm_wuntime:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void mmp2_audio_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	pm_cwk_destwoy(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM
static int mmp2_audio_cwk_suspend(stwuct device *dev)
{
	stwuct mmp2_audio_cwk *pwiv = dev_get_dwvdata(dev);

	pwiv->aud_ctww = weadw(pwiv->mmio_base + SSPA_AUD_CTWW);
	pwiv->aud_pww_ctww0 = weadw(pwiv->mmio_base + SSPA_AUD_PWW_CTWW0);
	pwiv->aud_pww_ctww1 = weadw(pwiv->mmio_base + SSPA_AUD_PWW_CTWW1);
	pm_cwk_suspend(dev);

	wetuwn 0;
}

static int mmp2_audio_cwk_wesume(stwuct device *dev)
{
	stwuct mmp2_audio_cwk *pwiv = dev_get_dwvdata(dev);

	pm_cwk_wesume(dev);
	wwitew(pwiv->aud_ctww, pwiv->mmio_base + SSPA_AUD_CTWW);
	wwitew(pwiv->aud_pww_ctww0, pwiv->mmio_base + SSPA_AUD_PWW_CTWW0);
	wwitew(pwiv->aud_pww_ctww1, pwiv->mmio_base + SSPA_AUD_PWW_CTWW1);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops mmp2_audio_cwk_pm_ops = {
	SET_WUNTIME_PM_OPS(mmp2_audio_cwk_suspend, mmp2_audio_cwk_wesume, NUWW)
};

static const stwuct of_device_id mmp2_audio_cwk_of_match[] = {
	{ .compatibwe = "mawveww,mmp2-audio-cwock" },
	{}
};

MODUWE_DEVICE_TABWE(of, mmp2_audio_cwk_of_match);

static stwuct pwatfowm_dwivew mmp2_audio_cwk_dwivew = {
	.dwivew = {
		.name = "mmp2-audio-cwock",
		.of_match_tabwe = of_match_ptw(mmp2_audio_cwk_of_match),
		.pm = &mmp2_audio_cwk_pm_ops,
	},
	.pwobe = mmp2_audio_cwk_pwobe,
	.wemove_new = mmp2_audio_cwk_wemove,
};
moduwe_pwatfowm_dwivew(mmp2_audio_cwk_dwivew);

MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>");
MODUWE_DESCWIPTION("Cwock dwivew fow MMP2 Audio subsystem");
MODUWE_WICENSE("GPW");
