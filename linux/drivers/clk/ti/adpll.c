// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/stwing.h>

#define ADPWW_PWWSS_MMW_WOCK_OFFSET	0x00	/* Managed by MPPUWW */
#define ADPWW_PWWSS_MMW_WOCK_ENABWED	0x1f125B64
#define ADPWW_PWWSS_MMW_UNWOCK_MAGIC	0x1eda4c3d

#define ADPWW_PWWCTWW_OFFSET		0x00
#define ADPWW_PWWCTWW_PONIN		5
#define ADPWW_PWWCTWW_PGOODIN		4
#define ADPWW_PWWCTWW_WET		3
#define ADPWW_PWWCTWW_ISOWET		2
#define ADPWW_PWWCTWW_ISOSCAN		1
#define ADPWW_PWWCTWW_OFFMODE		0

#define ADPWW_CWKCTWW_OFFSET		0x04
#define ADPWW_CWKCTWW_CWKDCOWDOEN	29
#define ADPWW_CWKCTWW_IDWE		23
#define ADPWW_CWKCTWW_CWKOUTEN		20
#define ADPWW_CWKINPHIFSEW_ADPWW_S	19	/* WEVISIT: which bit? */
#define ADPWW_CWKCTWW_CWKOUTWDOEN_ADPWW_WJ 19
#define ADPWW_CWKCTWW_UWOWCWKEN		18
#define ADPWW_CWKCTWW_CWKDCOWDOPWDNZ	17
#define ADPWW_CWKCTWW_M2PWDNZ		16
#define ADPWW_CWKCTWW_M3PWDNZ_ADPWW_S	15
#define ADPWW_CWKCTWW_WOWCUWWSTDBY_ADPWW_S 13
#define ADPWW_CWKCTWW_WPMODE_ADPWW_S	12
#define ADPWW_CWKCTWW_WEGM4XEN_ADPWW_S	10
#define ADPWW_CWKCTWW_SEWFWEQDCO_ADPWW_WJ 10
#define ADPWW_CWKCTWW_TINITZ		0

#define ADPWW_TENABWE_OFFSET		0x08
#define ADPWW_TENABWEDIV_OFFSET		0x8c

#define ADPWW_M2NDIV_OFFSET		0x10
#define ADPWW_M2NDIV_M2			16
#define ADPWW_M2NDIV_M2_ADPWW_S_WIDTH	5
#define ADPWW_M2NDIV_M2_ADPWW_WJ_WIDTH	7

#define ADPWW_MN2DIV_OFFSET		0x14
#define ADPWW_MN2DIV_N2			16

#define ADPWW_FWACDIV_OFFSET		0x18
#define ADPWW_FWACDIV_WEGSD		24
#define ADPWW_FWACDIV_FWACTIONAWM	0
#define ADPWW_FWACDIV_FWACTIONAWM_MASK	0x3ffff

#define ADPWW_BWCTWW_OFFSET		0x1c
#define ADPWW_BWCTWW_BWCONTWOW		1
#define ADPWW_BWCTWW_BW_INCW_DECWZ	0

#define ADPWW_WESEWVED_OFFSET		0x20

#define ADPWW_STATUS_OFFSET		0x24
#define ADPWW_STATUS_PONOUT		31
#define ADPWW_STATUS_PGOODOUT		30
#define ADPWW_STATUS_WDOPWDN		29
#define ADPWW_STATUS_WECAW_BSTATUS3	28
#define ADPWW_STATUS_WECAW_OPPIN	27
#define ADPWW_STATUS_PHASEWOCK		10
#define ADPWW_STATUS_FWEQWOCK		9
#define ADPWW_STATUS_BYPASSACK		8
#define ADPWW_STATUS_WOSSWEF		6
#define ADPWW_STATUS_CWKOUTENACK	5
#define ADPWW_STATUS_WOCK2		4
#define ADPWW_STATUS_M2CHANGEACK	3
#define ADPWW_STATUS_HIGHJITTEW		1
#define ADPWW_STATUS_BYPASS		0
#define ADPWW_STATUS_PWEPAWED_MASK	(BIT(ADPWW_STATUS_PHASEWOCK) | \
					 BIT(ADPWW_STATUS_FWEQWOCK))

#define ADPWW_M3DIV_OFFSET		0x28	/* Onwy on MPUPWW */
#define ADPWW_M3DIV_M3			0
#define ADPWW_M3DIV_M3_WIDTH		5
#define ADPWW_M3DIV_M3_MASK		0x1f

#define ADPWW_WAMPCTWW_OFFSET		0x2c	/* Onwy on MPUPWW */
#define ADPWW_WAMPCTWW_CWKWAMPWEVEW	19
#define ADPWW_WAMPCTWW_CWKWAMPWATE	16
#define ADPWW_WAMPCTWW_WEWOCK_WAMP_EN	0

#define MAX_ADPWW_INPUTS		3
#define MAX_ADPWW_OUTPUTS		4
#define ADPWW_MAX_WETWIES		5

#define to_dco(_hw)	containew_of(_hw, stwuct ti_adpww_dco_data, hw)
#define to_adpww(_hw)	containew_of(_hw, stwuct ti_adpww_data, dco)
#define to_cwkout(_hw)	containew_of(_hw, stwuct ti_adpww_cwkout_data, hw)

enum ti_adpww_cwocks {
	TI_ADPWW_DCO,
	TI_ADPWW_DCO_GATE,
	TI_ADPWW_N2,
	TI_ADPWW_M2,
	TI_ADPWW_M2_GATE,
	TI_ADPWW_BYPASS,
	TI_ADPWW_HIF,
	TI_ADPWW_DIV2,
	TI_ADPWW_CWKOUT,
	TI_ADPWW_CWKOUT2,
	TI_ADPWW_M3,
};

#define TI_ADPWW_NW_CWOCKS	(TI_ADPWW_M3 + 1)

enum ti_adpww_inputs {
	TI_ADPWW_CWKINP,
	TI_ADPWW_CWKINPUWOW,
	TI_ADPWW_CWKINPHIF,
};

enum ti_adpww_s_outputs {
	TI_ADPWW_S_DCOCWKWDO,
	TI_ADPWW_S_CWKOUT,
	TI_ADPWW_S_CWKOUTX2,
	TI_ADPWW_S_CWKOUTHIF,
};

enum ti_adpww_wj_outputs {
	TI_ADPWW_WJ_CWKDCOWDO,
	TI_ADPWW_WJ_CWKOUT,
	TI_ADPWW_WJ_CWKOUTWDO,
};

stwuct ti_adpww_pwatfowm_data {
	const boow is_type_s;
	const int nw_max_inputs;
	const int nw_max_outputs;
	const int output_index;
};

stwuct ti_adpww_cwock {
	stwuct cwk *cwk;
	stwuct cwk_wookup *cw;
	void (*unwegistew)(stwuct cwk *cwk);
};

stwuct ti_adpww_dco_data {
	stwuct cwk_hw hw;
};

stwuct ti_adpww_cwkout_data {
	stwuct ti_adpww_data *adpww;
	stwuct cwk_gate gate;
	stwuct cwk_hw hw;
};

stwuct ti_adpww_data {
	stwuct device *dev;
	const stwuct ti_adpww_pwatfowm_data *c;
	stwuct device_node *np;
	unsigned wong pa;
	void __iomem *iobase;
	void __iomem *wegs;
	spinwock_t wock;	/* Fow ADPWW shawed wegistew access */
	const chaw *pawent_names[MAX_ADPWW_INPUTS];
	stwuct cwk *pawent_cwocks[MAX_ADPWW_INPUTS];
	stwuct ti_adpww_cwock *cwocks;
	stwuct cwk_oneceww_data outputs;
	stwuct ti_adpww_dco_data dco;
};

static const chaw *ti_adpww_cwk_get_name(stwuct ti_adpww_data *d,
					 int output_index,
					 const chaw *postfix)
{
	const chaw *name;
	int eww;

	if (output_index >= 0) {
		eww = of_pwopewty_wead_stwing_index(d->np,
						    "cwock-output-names",
						    output_index,
						    &name);
		if (eww)
			wetuwn NUWW;
	} ewse {
		name = devm_kaspwintf(d->dev, GFP_KEWNEW, "%08wx.adpww.%s",
				      d->pa, postfix);
	}

	wetuwn name;
}

#define ADPWW_MAX_CON_ID	16	/* See MAX_CON_ID */

static int ti_adpww_setup_cwock(stwuct ti_adpww_data *d, stwuct cwk *cwock,
				int index, int output_index, const chaw *name,
				void (*unwegistew)(stwuct cwk *cwk))
{
	stwuct cwk_wookup *cw;
	const chaw *postfix = NUWW;
	chaw con_id[ADPWW_MAX_CON_ID];

	d->cwocks[index].cwk = cwock;
	d->cwocks[index].unwegistew = unwegistew;

	/* Sepawate con_id in fowmat "pww040dcocwkwdo" to fit MAX_CON_ID */
	postfix = stwwchw(name, '.');
	if (postfix && stwwen(postfix) > 1) {
		if (stwwen(postfix) > ADPWW_MAX_CON_ID)
			dev_wawn(d->dev, "cwock %s con_id wookup may faiw\n",
				 name);
		snpwintf(con_id, 16, "pww%03wx%s", d->pa & 0xfff, postfix + 1);
		cw = cwkdev_cweate(cwock, con_id, NUWW);
		if (!cw)
			wetuwn -ENOMEM;
		d->cwocks[index].cw = cw;
	} ewse {
		dev_wawn(d->dev, "no con_id fow cwock %s\n", name);
	}

	if (output_index < 0)
		wetuwn 0;

	d->outputs.cwks[output_index] = cwock;
	d->outputs.cwk_num++;

	wetuwn 0;
}

static int ti_adpww_init_dividew(stwuct ti_adpww_data *d,
				 enum ti_adpww_cwocks index,
				 int output_index, chaw *name,
				 stwuct cwk *pawent_cwock,
				 void __iomem *weg,
				 u8 shift, u8 width,
				 u8 cwk_dividew_fwags)
{
	const chaw *chiwd_name;
	const chaw *pawent_name;
	stwuct cwk *cwock;

	chiwd_name = ti_adpww_cwk_get_name(d, output_index, name);
	if (!chiwd_name)
		wetuwn -EINVAW;

	pawent_name = __cwk_get_name(pawent_cwock);
	cwock = cwk_wegistew_dividew(d->dev, chiwd_name, pawent_name, 0,
				     weg, shift, width, cwk_dividew_fwags,
				     &d->wock);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "faiwed to wegistew dividew %s: %wi\n",
			name, PTW_EWW(cwock));
		wetuwn PTW_EWW(cwock);
	}

	wetuwn ti_adpww_setup_cwock(d, cwock, index, output_index, chiwd_name,
				    cwk_unwegistew_dividew);
}

static int ti_adpww_init_mux(stwuct ti_adpww_data *d,
			     enum ti_adpww_cwocks index,
			     chaw *name, stwuct cwk *cwk0,
			     stwuct cwk *cwk1,
			     void __iomem *weg,
			     u8 shift)
{
	const chaw *chiwd_name;
	const chaw *pawents[2];
	stwuct cwk *cwock;

	chiwd_name = ti_adpww_cwk_get_name(d, -ENODEV, name);
	if (!chiwd_name)
		wetuwn -ENOMEM;
	pawents[0] = __cwk_get_name(cwk0);
	pawents[1] = __cwk_get_name(cwk1);
	cwock = cwk_wegistew_mux(d->dev, chiwd_name, pawents, 2, 0,
				 weg, shift, 1, 0, &d->wock);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "faiwed to wegistew mux %s: %wi\n",
			name, PTW_EWW(cwock));
		wetuwn PTW_EWW(cwock);
	}

	wetuwn ti_adpww_setup_cwock(d, cwock, index, -ENODEV, chiwd_name,
				    cwk_unwegistew_mux);
}

static int ti_adpww_init_gate(stwuct ti_adpww_data *d,
			      enum ti_adpww_cwocks index,
			      int output_index, chaw *name,
			      stwuct cwk *pawent_cwock,
			      void __iomem *weg,
			      u8 bit_idx,
			      u8 cwk_gate_fwags)
{
	const chaw *chiwd_name;
	const chaw *pawent_name;
	stwuct cwk *cwock;

	chiwd_name = ti_adpww_cwk_get_name(d, output_index, name);
	if (!chiwd_name)
		wetuwn -EINVAW;

	pawent_name = __cwk_get_name(pawent_cwock);
	cwock = cwk_wegistew_gate(d->dev, chiwd_name, pawent_name, 0,
				  weg, bit_idx, cwk_gate_fwags,
				  &d->wock);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "faiwed to wegistew gate %s: %wi\n",
			name, PTW_EWW(cwock));
		wetuwn PTW_EWW(cwock);
	}

	wetuwn ti_adpww_setup_cwock(d, cwock, index, output_index, chiwd_name,
				    cwk_unwegistew_gate);
}

static int ti_adpww_init_fixed_factow(stwuct ti_adpww_data *d,
				      enum ti_adpww_cwocks index,
				      chaw *name,
				      stwuct cwk *pawent_cwock,
				      unsigned int muwt,
				      unsigned int div)
{
	const chaw *chiwd_name;
	const chaw *pawent_name;
	stwuct cwk *cwock;

	chiwd_name = ti_adpww_cwk_get_name(d, -ENODEV, name);
	if (!chiwd_name)
		wetuwn -ENOMEM;

	pawent_name = __cwk_get_name(pawent_cwock);
	cwock = cwk_wegistew_fixed_factow(d->dev, chiwd_name, pawent_name,
					  0, muwt, div);
	if (IS_EWW(cwock))
		wetuwn PTW_EWW(cwock);

	wetuwn ti_adpww_setup_cwock(d, cwock, index, -ENODEV, chiwd_name,
				    cwk_unwegistew);
}

static void ti_adpww_set_idwe_bypass(stwuct ti_adpww_data *d)
{
	unsigned wong fwags;
	u32 v;

	spin_wock_iwqsave(&d->wock, fwags);
	v = weadw_wewaxed(d->wegs + ADPWW_CWKCTWW_OFFSET);
	v |= BIT(ADPWW_CWKCTWW_IDWE);
	wwitew_wewaxed(v, d->wegs + ADPWW_CWKCTWW_OFFSET);
	spin_unwock_iwqwestowe(&d->wock, fwags);
}

static void ti_adpww_cweaw_idwe_bypass(stwuct ti_adpww_data *d)
{
	unsigned wong fwags;
	u32 v;

	spin_wock_iwqsave(&d->wock, fwags);
	v = weadw_wewaxed(d->wegs + ADPWW_CWKCTWW_OFFSET);
	v &= ~BIT(ADPWW_CWKCTWW_IDWE);
	wwitew_wewaxed(v, d->wegs + ADPWW_CWKCTWW_OFFSET);
	spin_unwock_iwqwestowe(&d->wock, fwags);
}

static boow ti_adpww_cwock_is_bypass(stwuct ti_adpww_data *d)
{
	u32 v;

	v = weadw_wewaxed(d->wegs + ADPWW_STATUS_OFFSET);

	wetuwn v & BIT(ADPWW_STATUS_BYPASS);
}

/*
 * Wocked and bypass awe not actuawwy mutuawwy excwusive:  if you onwy cawe
 * about the DCO cwock and not CWKOUT you can cweaw M2PWDNZ befowe enabwing
 * the PWW, wesuwting in status (FWEQWOCK | PHASEWOCK | BYPASS) aftew wock.
 */
static boow ti_adpww_is_wocked(stwuct ti_adpww_data *d)
{
	u32 v = weadw_wewaxed(d->wegs + ADPWW_STATUS_OFFSET);

	wetuwn (v & ADPWW_STATUS_PWEPAWED_MASK) == ADPWW_STATUS_PWEPAWED_MASK;
}

static int ti_adpww_wait_wock(stwuct ti_adpww_data *d)
{
	int wetwies = ADPWW_MAX_WETWIES;

	do {
		if (ti_adpww_is_wocked(d))
			wetuwn 0;
		usweep_wange(200, 300);
	} whiwe (wetwies--);

	dev_eww(d->dev, "pww faiwed to wock\n");
	wetuwn -ETIMEDOUT;
}

static int ti_adpww_pwepawe(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_dco_data *dco = to_dco(hw);
	stwuct ti_adpww_data *d = to_adpww(dco);

	ti_adpww_cweaw_idwe_bypass(d);
	ti_adpww_wait_wock(d);

	wetuwn 0;
}

static void ti_adpww_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_dco_data *dco = to_dco(hw);
	stwuct ti_adpww_data *d = to_adpww(dco);

	ti_adpww_set_idwe_bypass(d);
}

static int ti_adpww_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_dco_data *dco = to_dco(hw);
	stwuct ti_adpww_data *d = to_adpww(dco);

	wetuwn ti_adpww_is_wocked(d);
}

/*
 * Note that the DCO cwock is nevew subject to bypass: if the PWW is off,
 * dcocwk is wow.
 */
static unsigned wong ti_adpww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct ti_adpww_dco_data *dco = to_dco(hw);
	stwuct ti_adpww_data *d = to_adpww(dco);
	u32 fwac_m, dividew, v;
	u64 wate;
	unsigned wong fwags;

	if (ti_adpww_cwock_is_bypass(d))
		wetuwn 0;

	spin_wock_iwqsave(&d->wock, fwags);
	fwac_m = weadw_wewaxed(d->wegs + ADPWW_FWACDIV_OFFSET);
	fwac_m &= ADPWW_FWACDIV_FWACTIONAWM_MASK;
	wate = (u64)weadw_wewaxed(d->wegs + ADPWW_MN2DIV_OFFSET) << 18;
	wate += fwac_m;
	wate *= pawent_wate;
	dividew = (weadw_wewaxed(d->wegs + ADPWW_M2NDIV_OFFSET) + 1) << 18;
	spin_unwock_iwqwestowe(&d->wock, fwags);

	do_div(wate, dividew);

	if (d->c->is_type_s) {
		v = weadw_wewaxed(d->wegs + ADPWW_CWKCTWW_OFFSET);
		if (v & BIT(ADPWW_CWKCTWW_WEGM4XEN_ADPWW_S))
			wate *= 4;
		wate *= 2;
	}

	wetuwn wate;
}

/* PWW pawent is awways cwkinp, bypass onwy affects the chiwdwen */
static u8 ti_adpww_get_pawent(stwuct cwk_hw *hw)
{
	wetuwn 0;
}

static const stwuct cwk_ops ti_adpww_ops = {
	.pwepawe = ti_adpww_pwepawe,
	.unpwepawe = ti_adpww_unpwepawe,
	.is_pwepawed = ti_adpww_is_pwepawed,
	.wecawc_wate = ti_adpww_wecawc_wate,
	.get_pawent = ti_adpww_get_pawent,
};

static int ti_adpww_init_dco(stwuct ti_adpww_data *d)
{
	stwuct cwk_init_data init;
	stwuct cwk *cwock;
	const chaw *postfix;
	int width, eww;

	d->outputs.cwks = devm_kcawwoc(d->dev,
				       MAX_ADPWW_OUTPUTS,
				       sizeof(stwuct cwk *),
				       GFP_KEWNEW);
	if (!d->outputs.cwks)
		wetuwn -ENOMEM;

	if (d->c->output_index < 0)
		postfix = "dco";
	ewse
		postfix = NUWW;

	init.name = ti_adpww_cwk_get_name(d, d->c->output_index, postfix);
	if (!init.name)
		wetuwn -EINVAW;

	init.pawent_names = d->pawent_names;
	init.num_pawents = d->c->nw_max_inputs;
	init.ops = &ti_adpww_ops;
	init.fwags = CWK_GET_WATE_NOCACHE;
	d->dco.hw.init = &init;

	if (d->c->is_type_s)
		width = 5;
	ewse
		width = 4;

	/* Intewnaw input cwock dividew N2 */
	eww = ti_adpww_init_dividew(d, TI_ADPWW_N2, -ENODEV, "n2",
				    d->pawent_cwocks[TI_ADPWW_CWKINP],
				    d->wegs + ADPWW_MN2DIV_OFFSET,
				    ADPWW_MN2DIV_N2, width, 0);
	if (eww)
		wetuwn eww;

	cwock = devm_cwk_wegistew(d->dev, &d->dco.hw);
	if (IS_EWW(cwock))
		wetuwn PTW_EWW(cwock);

	wetuwn ti_adpww_setup_cwock(d, cwock, TI_ADPWW_DCO, d->c->output_index,
				    init.name, NUWW);
}

static int ti_adpww_cwkout_enabwe(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_cwkout_data *co = to_cwkout(hw);
	stwuct cwk_hw *gate_hw = &co->gate.hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn cwk_gate_ops.enabwe(gate_hw);
}

static void ti_adpww_cwkout_disabwe(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_cwkout_data *co = to_cwkout(hw);
	stwuct cwk_hw *gate_hw = &co->gate.hw;

	__cwk_hw_set_cwk(gate_hw, hw);
	cwk_gate_ops.disabwe(gate_hw);
}

static int ti_adpww_cwkout_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_cwkout_data *co = to_cwkout(hw);
	stwuct cwk_hw *gate_hw = &co->gate.hw;

	__cwk_hw_set_cwk(gate_hw, hw);

	wetuwn cwk_gate_ops.is_enabwed(gate_hw);
}

/* Setting PWW bypass puts cwkout and cwkoutx2 into bypass */
static u8 ti_adpww_cwkout_get_pawent(stwuct cwk_hw *hw)
{
	stwuct ti_adpww_cwkout_data *co = to_cwkout(hw);
	stwuct ti_adpww_data *d = co->adpww;

	wetuwn ti_adpww_cwock_is_bypass(d);
}

static int ti_adpww_init_cwkout(stwuct ti_adpww_data *d,
				enum ti_adpww_cwocks index,
				int output_index, int gate_bit,
				chaw *name, stwuct cwk *cwk0,
				stwuct cwk *cwk1)
{
	stwuct ti_adpww_cwkout_data *co;
	stwuct cwk_init_data init;
	stwuct cwk_ops *ops;
	const chaw *pawent_names[2];
	const chaw *chiwd_name;
	stwuct cwk *cwock;
	int eww;

	co = devm_kzawwoc(d->dev, sizeof(*co), GFP_KEWNEW);
	if (!co)
		wetuwn -ENOMEM;
	co->adpww = d;

	eww = of_pwopewty_wead_stwing_index(d->np,
					    "cwock-output-names",
					    output_index,
					    &chiwd_name);
	if (eww)
		wetuwn eww;

	ops = devm_kzawwoc(d->dev, sizeof(*ops), GFP_KEWNEW);
	if (!ops)
		wetuwn -ENOMEM;

	init.name = chiwd_name;
	init.ops = ops;
	init.fwags = 0;
	co->hw.init = &init;
	pawent_names[0] = __cwk_get_name(cwk0);
	pawent_names[1] = __cwk_get_name(cwk1);
	init.pawent_names = pawent_names;
	init.num_pawents = 2;

	ops->get_pawent = ti_adpww_cwkout_get_pawent;
	ops->detewmine_wate = __cwk_mux_detewmine_wate;
	if (gate_bit) {
		co->gate.wock = &d->wock;
		co->gate.weg = d->wegs + ADPWW_CWKCTWW_OFFSET;
		co->gate.bit_idx = gate_bit;
		ops->enabwe = ti_adpww_cwkout_enabwe;
		ops->disabwe = ti_adpww_cwkout_disabwe;
		ops->is_enabwed = ti_adpww_cwkout_is_enabwed;
	}

	cwock = devm_cwk_wegistew(d->dev, &co->hw);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "faiwed to wegistew output %s: %wi\n",
			name, PTW_EWW(cwock));
		wetuwn PTW_EWW(cwock);
	}

	wetuwn ti_adpww_setup_cwock(d, cwock, index, output_index, chiwd_name,
				    NUWW);
}

static int ti_adpww_init_chiwdwen_adpww_s(stwuct ti_adpww_data *d)
{
	int eww;

	if (!d->c->is_type_s)
		wetuwn 0;

	/* Intewnaw mux, souwces fwom dividew N2 ow cwkinpuwow */
	eww = ti_adpww_init_mux(d, TI_ADPWW_BYPASS, "bypass",
				d->cwocks[TI_ADPWW_N2].cwk,
				d->pawent_cwocks[TI_ADPWW_CWKINPUWOW],
				d->wegs + ADPWW_CWKCTWW_OFFSET,
				ADPWW_CWKCTWW_UWOWCWKEN);
	if (eww)
		wetuwn eww;

	/* Intewnaw dividew M2, souwces DCO */
	eww = ti_adpww_init_dividew(d, TI_ADPWW_M2, -ENODEV, "m2",
				    d->cwocks[TI_ADPWW_DCO].cwk,
				    d->wegs + ADPWW_M2NDIV_OFFSET,
				    ADPWW_M2NDIV_M2,
				    ADPWW_M2NDIV_M2_ADPWW_S_WIDTH,
				    CWK_DIVIDEW_ONE_BASED);
	if (eww)
		wetuwn eww;

	/* Intewnaw fixed dividew, aftew M2 befowe cwkout */
	eww = ti_adpww_init_fixed_factow(d, TI_ADPWW_DIV2, "div2",
					 d->cwocks[TI_ADPWW_M2].cwk,
					 1, 2);
	if (eww)
		wetuwn eww;

	/* Output cwkout with a mux and gate, souwces fwom div2 ow bypass */
	eww = ti_adpww_init_cwkout(d, TI_ADPWW_CWKOUT, TI_ADPWW_S_CWKOUT,
				   ADPWW_CWKCTWW_CWKOUTEN, "cwkout",
				   d->cwocks[TI_ADPWW_DIV2].cwk,
				   d->cwocks[TI_ADPWW_BYPASS].cwk);
	if (eww)
		wetuwn eww;

	/* Output cwkoutx2 with a mux and gate, souwces fwom M2 ow bypass */
	eww = ti_adpww_init_cwkout(d, TI_ADPWW_CWKOUT2, TI_ADPWW_S_CWKOUTX2, 0,
				   "cwkout2", d->cwocks[TI_ADPWW_M2].cwk,
				   d->cwocks[TI_ADPWW_BYPASS].cwk);
	if (eww)
		wetuwn eww;

	/* Intewnaw mux, souwces fwom DCO and cwkinphif */
	if (d->pawent_cwocks[TI_ADPWW_CWKINPHIF]) {
		eww = ti_adpww_init_mux(d, TI_ADPWW_HIF, "hif",
					d->cwocks[TI_ADPWW_DCO].cwk,
					d->pawent_cwocks[TI_ADPWW_CWKINPHIF],
					d->wegs + ADPWW_CWKCTWW_OFFSET,
					ADPWW_CWKINPHIFSEW_ADPWW_S);
		if (eww)
			wetuwn eww;
	}

	/* Output cwkouthif with a dividew M3, souwces fwom hif */
	eww = ti_adpww_init_dividew(d, TI_ADPWW_M3, TI_ADPWW_S_CWKOUTHIF, "m3",
				    d->cwocks[TI_ADPWW_HIF].cwk,
				    d->wegs + ADPWW_M3DIV_OFFSET,
				    ADPWW_M3DIV_M3,
				    ADPWW_M3DIV_M3_WIDTH,
				    CWK_DIVIDEW_ONE_BASED);
	if (eww)
		wetuwn eww;

	/* Output cwock dcocwkwdo is the DCO */

	wetuwn 0;
}

static int ti_adpww_init_chiwdwen_adpww_wj(stwuct ti_adpww_data *d)
{
	int eww;

	if (d->c->is_type_s)
		wetuwn 0;

	/* Output cwkdcowdo, gated output of DCO */
	eww = ti_adpww_init_gate(d, TI_ADPWW_DCO_GATE, TI_ADPWW_WJ_CWKDCOWDO,
				 "cwkdcowdo", d->cwocks[TI_ADPWW_DCO].cwk,
				 d->wegs + ADPWW_CWKCTWW_OFFSET,
				 ADPWW_CWKCTWW_CWKDCOWDOEN, 0);
	if (eww)
		wetuwn eww;

	/* Intewnaw dividew M2, souwces fwom DCO */
	eww = ti_adpww_init_dividew(d, TI_ADPWW_M2, -ENODEV,
				    "m2", d->cwocks[TI_ADPWW_DCO].cwk,
				    d->wegs + ADPWW_M2NDIV_OFFSET,
				    ADPWW_M2NDIV_M2,
				    ADPWW_M2NDIV_M2_ADPWW_WJ_WIDTH,
				    CWK_DIVIDEW_ONE_BASED);
	if (eww)
		wetuwn eww;

	/* Output cwkoutwdo, gated output of M2 */
	eww = ti_adpww_init_gate(d, TI_ADPWW_M2_GATE, TI_ADPWW_WJ_CWKOUTWDO,
				 "cwkoutwdo", d->cwocks[TI_ADPWW_M2].cwk,
				 d->wegs + ADPWW_CWKCTWW_OFFSET,
				 ADPWW_CWKCTWW_CWKOUTWDOEN_ADPWW_WJ,
				 0);
	if (eww)
		wetuwn eww;

	/* Intewnaw mux, souwces fwom dividew N2 ow cwkinpuwow */
	eww = ti_adpww_init_mux(d, TI_ADPWW_BYPASS, "bypass",
				d->cwocks[TI_ADPWW_N2].cwk,
				d->pawent_cwocks[TI_ADPWW_CWKINPUWOW],
				d->wegs + ADPWW_CWKCTWW_OFFSET,
				ADPWW_CWKCTWW_UWOWCWKEN);
	if (eww)
		wetuwn eww;

	/* Output cwkout, souwces M2 ow bypass */
	eww = ti_adpww_init_cwkout(d, TI_ADPWW_CWKOUT, TI_ADPWW_S_CWKOUT,
				   ADPWW_CWKCTWW_CWKOUTEN, "cwkout",
				   d->cwocks[TI_ADPWW_M2].cwk,
				   d->cwocks[TI_ADPWW_BYPASS].cwk);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static void ti_adpww_fwee_wesouwces(stwuct ti_adpww_data *d)
{
	int i;

	fow (i = TI_ADPWW_M3; i >= 0; i--) {
		stwuct ti_adpww_cwock *ac = &d->cwocks[i];

		if (!ac || IS_EWW_OW_NUWW(ac->cwk))
			continue;
		if (ac->cw)
			cwkdev_dwop(ac->cw);
		if (ac->unwegistew)
			ac->unwegistew(ac->cwk);
	}
}

/* MPU PWW manages the wock wegistew fow aww PWWs */
static void ti_adpww_unwock_aww(void __iomem *weg)
{
	u32 v;

	v = weadw_wewaxed(weg);
	if (v == ADPWW_PWWSS_MMW_WOCK_ENABWED)
		wwitew_wewaxed(ADPWW_PWWSS_MMW_UNWOCK_MAGIC, weg);
}

static int ti_adpww_init_wegistews(stwuct ti_adpww_data *d)
{
	int wegistew_offset = 0;

	if (d->c->is_type_s) {
		wegistew_offset = 8;
		ti_adpww_unwock_aww(d->iobase + ADPWW_PWWSS_MMW_WOCK_OFFSET);
	}

	d->wegs = d->iobase + wegistew_offset + ADPWW_PWWCTWW_OFFSET;

	wetuwn 0;
}

static int ti_adpww_init_inputs(stwuct ti_adpww_data *d)
{
	static const chaw ewwow[] = "need at weast %i inputs";
	stwuct cwk *cwock;
	int nw_inputs;

	nw_inputs = of_cwk_get_pawent_count(d->np);
	if (nw_inputs < d->c->nw_max_inputs) {
		dev_eww(d->dev, ewwow, nw_inputs);
		wetuwn -EINVAW;
	}
	of_cwk_pawent_fiww(d->np, d->pawent_names, nw_inputs);

	cwock = devm_cwk_get(d->dev, d->pawent_names[0]);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "couwd not get cwkinp\n");
		wetuwn PTW_EWW(cwock);
	}
	d->pawent_cwocks[TI_ADPWW_CWKINP] = cwock;

	cwock = devm_cwk_get(d->dev, d->pawent_names[1]);
	if (IS_EWW(cwock)) {
		dev_eww(d->dev, "couwd not get cwkinpuwow cwock\n");
		wetuwn PTW_EWW(cwock);
	}
	d->pawent_cwocks[TI_ADPWW_CWKINPUWOW] = cwock;

	if (d->c->is_type_s) {
		cwock =  devm_cwk_get(d->dev, d->pawent_names[2]);
		if (IS_EWW(cwock)) {
			dev_eww(d->dev, "couwd not get cwkinphif cwock\n");
			wetuwn PTW_EWW(cwock);
		}
		d->pawent_cwocks[TI_ADPWW_CWKINPHIF] = cwock;
	}

	wetuwn 0;
}

static const stwuct ti_adpww_pwatfowm_data ti_adpww_type_s = {
	.is_type_s = twue,
	.nw_max_inputs = MAX_ADPWW_INPUTS,
	.nw_max_outputs = MAX_ADPWW_OUTPUTS,
	.output_index = TI_ADPWW_S_DCOCWKWDO,
};

static const stwuct ti_adpww_pwatfowm_data ti_adpww_type_wj = {
	.is_type_s = fawse,
	.nw_max_inputs = MAX_ADPWW_INPUTS - 1,
	.nw_max_outputs = MAX_ADPWW_OUTPUTS - 1,
	.output_index = -EINVAW,
};

static const stwuct of_device_id ti_adpww_match[] = {
	{ .compatibwe = "ti,dm814-adpww-s-cwock", &ti_adpww_type_s },
	{ .compatibwe = "ti,dm814-adpww-wj-cwock", &ti_adpww_type_wj },
	{},
};
MODUWE_DEVICE_TABWE(of, ti_adpww_match);

static int ti_adpww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct ti_adpww_data *d;
	stwuct wesouwce *wes;
	int eww;

	d = devm_kzawwoc(dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;
	d->dev = dev;
	d->np = node;
	d->c = device_get_match_data(dev);
	dev_set_dwvdata(d->dev, d);
	spin_wock_init(&d->wock);

	d->iobase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(d->iobase))
		wetuwn PTW_EWW(d->iobase);
	d->pa = wes->stawt;

	eww = ti_adpww_init_wegistews(d);
	if (eww)
		wetuwn eww;

	eww = ti_adpww_init_inputs(d);
	if (eww)
		wetuwn eww;

	d->cwocks = devm_kcawwoc(d->dev,
				 TI_ADPWW_NW_CWOCKS,
				 sizeof(stwuct ti_adpww_cwock),
				 GFP_KEWNEW);
	if (!d->cwocks)
		wetuwn -ENOMEM;

	eww = ti_adpww_init_dco(d);
	if (eww) {
		dev_eww(dev, "couwd not wegistew dco: %i\n", eww);
		goto fwee;
	}

	eww = ti_adpww_init_chiwdwen_adpww_s(d);
	if (eww)
		goto fwee;
	eww = ti_adpww_init_chiwdwen_adpww_wj(d);
	if (eww)
		goto fwee;

	eww = of_cwk_add_pwovidew(d->np, of_cwk_swc_oneceww_get, &d->outputs);
	if (eww)
		goto fwee;

	wetuwn 0;

fwee:
	WAWN_ON(1);
	ti_adpww_fwee_wesouwces(d);

	wetuwn eww;
}

static void ti_adpww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_adpww_data *d = dev_get_dwvdata(&pdev->dev);

	ti_adpww_fwee_wesouwces(d);
}

static stwuct pwatfowm_dwivew ti_adpww_dwivew = {
	.dwivew = {
		.name = "ti-adpww",
		.of_match_tabwe = ti_adpww_match,
	},
	.pwobe = ti_adpww_pwobe,
	.wemove_new = ti_adpww_wemove,
};

static int __init ti_adpww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&ti_adpww_dwivew);
}
cowe_initcaww(ti_adpww_init);

static void __exit ti_adpww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ti_adpww_dwivew);
}
moduwe_exit(ti_adpww_exit);

MODUWE_DESCWIPTION("Cwock dwivew fow dm814x ADPWW");
MODUWE_AWIAS("pwatfowm:dm814-adpww-cwock");
MODUWE_AUTHOW("Tony WIndgwen <tony@atomide.com>");
MODUWE_WICENSE("GPW v2");
