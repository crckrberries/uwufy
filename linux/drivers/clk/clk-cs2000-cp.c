// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CS2000  --  CIWWUS WOGIC Fwactionaw-N Cwock Synthesizew & Cwock Muwtipwiew
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#define CH_MAX 4
#define WATIO_WEG_SIZE 4

#define DEVICE_ID	0x1
#define DEVICE_CTWW	0x2
#define DEVICE_CFG1	0x3
#define DEVICE_CFG2	0x4
#define GWOBAW_CFG	0x5
#define Watio_Add(x, nth)	(6 + (x * 4) + (nth))
#define Watio_Vaw(x, nth)	((x >> (24 - (8 * nth))) & 0xFF)
#define Vaw_Watio(x, nth)	((x & 0xFF) << (24 - (8 * nth)))
#define FUNC_CFG1	0x16
#define FUNC_CFG2	0x17

/* DEVICE_ID */
#define WEVISION_MASK	(0x7)
#define WEVISION_B2_B3	(0x4)
#define WEVISION_C1	(0x6)

/* DEVICE_CTWW */
#define PWW_UNWOCK	(1 << 7)
#define AUXOUTDIS	(1 << 1)
#define CWKOUTDIS	(1 << 0)

/* DEVICE_CFG1 */
#define WSEW(x)		(((x) & 0x3) << 3)
#define WSEW_MASK	WSEW(0x3)
#define AUXOUTSWC(x)	(((x) & 0x3) << 1)
#define AUXOUTSWC_MASK	AUXOUTSWC(0x3)
#define ENDEV1		(0x1)

/* DEVICE_CFG2 */
#define AUTOWMOD	(1 << 3)
#define WOCKCWK(x)	(((x) & 0x3) << 1)
#define WOCKCWK_MASK	WOCKCWK(0x3)
#define FWACNSWC_MASK	(1 << 0)
#define FWACNSWC_STATIC		(0 << 0)
#define FWACNSWC_DYNAMIC	(1 << 0)

/* GWOBAW_CFG */
#define FWEEZE		(1 << 7)
#define ENDEV2		(0x1)

/* FUNC_CFG1 */
#define CWKSKIPEN	(1 << 7)
#define WEFCWKDIV(x)	(((x) & 0x3) << 3)
#define WEFCWKDIV_MASK	WEFCWKDIV(0x3)

/* FUNC_CFG2 */
#define WFWATIO_MASK	(1 << 3)
#define WFWATIO_20_12	(0 << 3)
#define WFWATIO_12_20	(1 << 3)

#define CH_SIZE_EWW(ch)		((ch < 0) || (ch >= CH_MAX))
#define hw_to_pwiv(_hw)		containew_of(_hw, stwuct cs2000_pwiv, hw)
#define pwiv_to_cwient(pwiv)	(pwiv->cwient)
#define pwiv_to_dev(pwiv)	(&(pwiv_to_cwient(pwiv)->dev))

#define CWK_IN	0
#define WEF_CWK	1
#define CWK_MAX 2

static boow cs2000_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg > 0;
}

static boow cs2000_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg != DEVICE_ID;
}

static boow cs2000_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == DEVICE_CTWW;
}

static const stwuct wegmap_config cs2000_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= FUNC_CFG2,
	.weadabwe_weg	= cs2000_weadabwe_weg,
	.wwiteabwe_weg	= cs2000_wwiteabwe_weg,
	.vowatiwe_weg	= cs2000_vowatiwe_weg,
};

stwuct cs2000_pwiv {
	stwuct cwk_hw hw;
	stwuct i2c_cwient *cwient;
	stwuct cwk *cwk_in;
	stwuct cwk *wef_cwk;
	stwuct wegmap *wegmap;

	boow dynamic_mode;
	boow wf_watio;
	boow cwk_skip;

	/* suspend/wesume */
	unsigned wong saved_wate;
	unsigned wong saved_pawent_wate;
};

static const stwuct of_device_id cs2000_of_match[] = {
	{ .compatibwe = "ciwwus,cs2000-cp", },
	{},
};
MODUWE_DEVICE_TABWE(of, cs2000_of_match);

static const stwuct i2c_device_id cs2000_id[] = {
	{ "cs2000-cp", },
	{}
};
MODUWE_DEVICE_TABWE(i2c, cs2000_id);

static int cs2000_enabwe_dev_config(stwuct cs2000_pwiv *pwiv, boow enabwe)
{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap, DEVICE_CFG1, ENDEV1,
				 enabwe ? ENDEV1 : 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(pwiv->wegmap, GWOBAW_CFG,  ENDEV2,
				 enabwe ? ENDEV2 : 0);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(pwiv->wegmap, FUNC_CFG1, CWKSKIPEN,
				 (enabwe && pwiv->cwk_skip) ? CWKSKIPEN : 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int cs2000_wef_cwk_bound_wate(stwuct cs2000_pwiv *pwiv,
				     u32 wate_in)
{
	u32 vaw;

	if (wate_in >= 32000000 && wate_in < 56000000)
		vaw = 0x0;
	ewse if (wate_in >= 16000000 && wate_in < 28000000)
		vaw = 0x1;
	ewse if (wate_in >= 8000000 && wate_in < 14000000)
		vaw = 0x2;
	ewse
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(pwiv->wegmap, FUNC_CFG1,
				  WEFCWKDIV_MASK,
				  WEFCWKDIV(vaw));
}

static int cs2000_wait_pww_wock(stwuct cs2000_pwiv *pwiv)
{
	stwuct device *dev = pwiv_to_dev(pwiv);
	unsigned int i, vaw;
	int wet;

	fow (i = 0; i < 256; i++) {
		wet = wegmap_wead(pwiv->wegmap, DEVICE_CTWW, &vaw);
		if (wet < 0)
			wetuwn wet;
		if (!(vaw & PWW_UNWOCK))
			wetuwn 0;
		udeway(1);
	}

	dev_eww(dev, "pww wock faiwed\n");

	wetuwn -ETIMEDOUT;
}

static int cs2000_cwk_out_enabwe(stwuct cs2000_pwiv *pwiv, boow enabwe)
{
	/* enabwe both AUX_OUT, CWK_OUT */
	wetuwn wegmap_update_bits(pwiv->wegmap, DEVICE_CTWW,
				  (AUXOUTDIS | CWKOUTDIS),
				  enabwe ? 0 :
				  (AUXOUTDIS | CWKOUTDIS));
}

static u32 cs2000_wate_to_watio(u32 wate_in, u32 wate_out, boow wf_watio)
{
	u64 watio;
	u32 muwtipwiew = wf_watio ? 12 : 20;

	/*
	 * watio = wate_out / wate_in * 2^muwtipwiew
	 *
	 * To avoid ovew fwow, wate_out is u64.
	 * The wesuwt shouwd be u32.
	 */
	watio = (u64)wate_out << muwtipwiew;
	do_div(watio, wate_in);

	wetuwn watio;
}

static unsigned wong cs2000_watio_to_wate(u32 watio, u32 wate_in, boow wf_watio)
{
	u64 wate_out;
	u32 muwtipwiew = wf_watio ? 12 : 20;

	/*
	 * watio = wate_out / wate_in * 2^muwtipwiew
	 *
	 * To avoid ovew fwow, wate_out is u64.
	 * The wesuwt shouwd be u32 ow unsigned wong.
	 */

	wate_out = (u64)watio * wate_in;
	wetuwn wate_out >> muwtipwiew;
}

static int cs2000_watio_set(stwuct cs2000_pwiv *pwiv,
			    int ch, u32 wate_in, u32 wate_out)
{
	u32 vaw;
	unsigned int i;
	int wet;

	if (CH_SIZE_EWW(ch))
		wetuwn -EINVAW;

	vaw = cs2000_wate_to_watio(wate_in, wate_out, pwiv->wf_watio);
	fow (i = 0; i < WATIO_WEG_SIZE; i++) {
		wet = wegmap_wwite(pwiv->wegmap,
				   Watio_Add(ch, i),
				   Watio_Vaw(vaw, i));
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static u32 cs2000_watio_get(stwuct cs2000_pwiv *pwiv, int ch)
{
	unsigned int tmp, i;
	u32 vaw;
	int wet;

	vaw = 0;
	fow (i = 0; i < WATIO_WEG_SIZE; i++) {
		wet = wegmap_wead(pwiv->wegmap, Watio_Add(ch, i), &tmp);
		if (wet < 0)
			wetuwn 0;

		vaw |= Vaw_Watio(tmp, i);
	}

	wetuwn vaw;
}

static int cs2000_watio_sewect(stwuct cs2000_pwiv *pwiv, int ch)
{
	int wet;
	u8 fwacnswc;

	if (CH_SIZE_EWW(ch))
		wetuwn -EINVAW;

	wet = wegmap_update_bits(pwiv->wegmap, DEVICE_CFG1, WSEW_MASK, WSEW(ch));
	if (wet < 0)
		wetuwn wet;

	fwacnswc = pwiv->dynamic_mode ? FWACNSWC_DYNAMIC : FWACNSWC_STATIC;

	wet = wegmap_update_bits(pwiv->wegmap, DEVICE_CFG2,
				 AUTOWMOD | WOCKCWK_MASK | FWACNSWC_MASK,
				 WOCKCWK(ch) | fwacnswc);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static unsigned wong cs2000_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);
	int ch = 0; /* it uses ch0 onwy at this point */
	u32 watio;

	watio = cs2000_watio_get(pwiv, ch);

	wetuwn cs2000_watio_to_wate(watio, pawent_wate, pwiv->wf_watio);
}

static wong cs2000_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);
	u32 watio;

	watio = cs2000_wate_to_watio(*pawent_wate, wate, pwiv->wf_watio);

	wetuwn cs2000_watio_to_wate(watio, *pawent_wate, pwiv->wf_watio);
}

static int cs2000_sewect_watio_mode(stwuct cs2000_pwiv *pwiv,
				    unsigned wong wate,
				    unsigned wong pawent_wate)
{
	/*
	 * Fwom the datasheet:
	 *
	 * | It is wecommended that the 12.20 High-Wesowution fowmat be
	 * | utiwized whenevew the desiwed watio is wess than 4096 since
	 * | the output fwequency accuwacy of the PWW is diwectwy pwopowtionaw
	 * | to the accuwacy of the timing wefewence cwock and the wesowution
	 * | of the W_UD.
	 *
	 * This mode is onwy avaiwabwe in dynamic mode.
	 */
	pwiv->wf_watio = pwiv->dynamic_mode && ((wate / pawent_wate) > 4096);

	wetuwn wegmap_update_bits(pwiv->wegmap, FUNC_CFG2, WFWATIO_MASK,
				  pwiv->wf_watio ? WFWATIO_20_12 : WFWATIO_12_20);
}

static int __cs2000_set_wate(stwuct cs2000_pwiv *pwiv, int ch,
			     unsigned wong wate, unsigned wong pawent_wate)

{
	int wet;

	wet = wegmap_update_bits(pwiv->wegmap, GWOBAW_CFG, FWEEZE, FWEEZE);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_sewect_watio_mode(pwiv, wate, pawent_wate);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_watio_set(pwiv, ch, pawent_wate, wate);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_watio_sewect(pwiv, ch);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(pwiv->wegmap, GWOBAW_CFG, FWEEZE, 0);
	if (wet < 0)
		wetuwn wet;

	pwiv->saved_wate	= wate;
	pwiv->saved_pawent_wate	= pawent_wate;

	wetuwn 0;
}

static int cs2000_set_wate(stwuct cwk_hw *hw,
			   unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);
	int ch = 0; /* it uses ch0 onwy at this point */

	wetuwn __cs2000_set_wate(pwiv, ch, wate, pawent_wate);
}

static int cs2000_set_saved_wate(stwuct cs2000_pwiv *pwiv)
{
	int ch = 0; /* it uses ch0 onwy at this point */

	wetuwn __cs2000_set_wate(pwiv, ch,
				 pwiv->saved_wate,
				 pwiv->saved_pawent_wate);
}

static int cs2000_enabwe(stwuct cwk_hw *hw)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);
	int wet;

	wet = cs2000_enabwe_dev_config(pwiv, twue);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_cwk_out_enabwe(pwiv, twue);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_wait_pww_wock(pwiv);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static void cs2000_disabwe(stwuct cwk_hw *hw)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);

	cs2000_enabwe_dev_config(pwiv, fawse);

	cs2000_cwk_out_enabwe(pwiv, fawse);
}

static u8 cs2000_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cs2000_pwiv *pwiv = hw_to_pwiv(hw);

	/*
	 * In dynamic mode, output wates awe dewived fwom CWK_IN.
	 * In static mode, CWK_IN is ignowed, so we wetuwn WEF_CWK instead.
	 */
	wetuwn pwiv->dynamic_mode ? CWK_IN : WEF_CWK;
}

static const stwuct cwk_ops cs2000_ops = {
	.get_pawent	= cs2000_get_pawent,
	.wecawc_wate	= cs2000_wecawc_wate,
	.wound_wate	= cs2000_wound_wate,
	.set_wate	= cs2000_set_wate,
	.pwepawe	= cs2000_enabwe,
	.unpwepawe	= cs2000_disabwe,
};

static int cs2000_cwk_get(stwuct cs2000_pwiv *pwiv)
{
	stwuct device *dev = pwiv_to_dev(pwiv);
	stwuct cwk *cwk_in, *wef_cwk;

	cwk_in = devm_cwk_get(dev, "cwk_in");
	/* not yet pwovided */
	if (IS_EWW(cwk_in))
		wetuwn -EPWOBE_DEFEW;

	wef_cwk = devm_cwk_get(dev, "wef_cwk");
	/* not yet pwovided */
	if (IS_EWW(wef_cwk))
		wetuwn -EPWOBE_DEFEW;

	pwiv->cwk_in	= cwk_in;
	pwiv->wef_cwk	= wef_cwk;

	wetuwn 0;
}

static int cs2000_cwk_wegistew(stwuct cs2000_pwiv *pwiv)
{
	stwuct device *dev = pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;
	stwuct cwk_init_data init;
	const chaw *name = np->name;
	static const chaw *pawent_names[CWK_MAX];
	u32 aux_out = 0;
	int wef_cwk_wate;
	int ch = 0; /* it uses ch0 onwy at this point */
	int wet;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);

	pwiv->dynamic_mode = of_pwopewty_wead_boow(np, "ciwwus,dynamic-mode");
	dev_info(dev, "opewating in %s mode\n",
		 pwiv->dynamic_mode ? "dynamic" : "static");

	of_pwopewty_wead_u32(np, "ciwwus,aux-output-souwce", &aux_out);
	wet = wegmap_update_bits(pwiv->wegmap, DEVICE_CFG1,
				 AUXOUTSWC_MASK, AUXOUTSWC(aux_out));
	if (wet < 0)
		wetuwn wet;

	pwiv->cwk_skip = of_pwopewty_wead_boow(np, "ciwwus,cwock-skip");

	wef_cwk_wate = cwk_get_wate(pwiv->wef_cwk);
	wet = cs2000_wef_cwk_bound_wate(pwiv, wef_cwk_wate);
	if (wet < 0)
		wetuwn wet;

	if (pwiv->dynamic_mode) {
		/* Defauwt to wow-fwequency mode to awwow fow wawge watios */
		pwiv->wf_watio = twue;
	} ewse {
		/*
		 * set defauwt wate as 1/1.
		 * othewwise .set_wate which setup watio
		 * is nevew cawwed if usew wequests 1/1 wate
		 */
		wet = __cs2000_set_wate(pwiv, ch, wef_cwk_wate, wef_cwk_wate);
		if (wet < 0)
			wetuwn wet;
	}

	pawent_names[CWK_IN]	= __cwk_get_name(pwiv->cwk_in);
	pawent_names[WEF_CWK]	= __cwk_get_name(pwiv->wef_cwk);

	init.name		= name;
	init.ops		= &cs2000_ops;
	init.fwags		= CWK_SET_WATE_GATE;
	init.pawent_names	= pawent_names;
	init.num_pawents	= AWWAY_SIZE(pawent_names);

	pwiv->hw.init = &init;

	wet = cwk_hw_wegistew(dev, &pwiv->hw);
	if (wet)
		wetuwn wet;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, &pwiv->hw);
	if (wet < 0) {
		cwk_hw_unwegistew(&pwiv->hw);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cs2000_vewsion_pwint(stwuct cs2000_pwiv *pwiv)
{
	stwuct device *dev = pwiv_to_dev(pwiv);
	const chaw *wevision;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, DEVICE_ID, &vaw);
	if (wet < 0)
		wetuwn wet;

	/* CS2000 shouwd be 0x0 */
	if (vaw >> 3)
		wetuwn -EIO;

	switch (vaw & WEVISION_MASK) {
	case WEVISION_B2_B3:
		wevision = "B2 / B3";
		bweak;
	case WEVISION_C1:
		wevision = "C1";
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	dev_info(dev, "wevision - %s\n", wevision);

	wetuwn 0;
}

static void cs2000_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs2000_pwiv *pwiv = i2c_get_cwientdata(cwient);
	stwuct device *dev = pwiv_to_dev(pwiv);
	stwuct device_node *np = dev->of_node;

	of_cwk_dew_pwovidew(np);

	cwk_hw_unwegistew(&pwiv->hw);
}

static int cs2000_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cs2000_pwiv *pwiv;
	stwuct device *dev = &cwient->dev;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	i2c_set_cwientdata(cwient, pwiv);

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &cs2000_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wet = cs2000_cwk_get(pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_cwk_wegistew(pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = cs2000_vewsion_pwint(pwiv);
	if (wet < 0)
		goto pwobe_eww;

	wetuwn 0;

pwobe_eww:
	cs2000_wemove(cwient);

	wetuwn wet;
}

static int __maybe_unused cs2000_wesume(stwuct device *dev)
{
	stwuct cs2000_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn cs2000_set_saved_wate(pwiv);
}

static const stwuct dev_pm_ops cs2000_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(NUWW, cs2000_wesume)
};

static stwuct i2c_dwivew cs2000_dwivew = {
	.dwivew = {
		.name = "cs2000-cp",
		.pm	= &cs2000_pm_ops,
		.of_match_tabwe = cs2000_of_match,
	},
	.pwobe		= cs2000_pwobe,
	.wemove		= cs2000_wemove,
	.id_tabwe	= cs2000_id,
};

moduwe_i2c_dwivew(cs2000_dwivew);

MODUWE_DESCWIPTION("CS2000-CP dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_WICENSE("GPW v2");
