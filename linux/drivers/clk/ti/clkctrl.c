// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP cwkctww cwock suppowt
 *
 * Copywight (C) 2017 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/deway.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/timekeeping.h>
#incwude "cwock.h"

#define NO_IDWEST			0

#define OMAP4_MODUWEMODE_MASK		0x3

#define MODUWEMODE_HWCTWW		0x1
#define MODUWEMODE_SWCTWW		0x2

#define OMAP4_IDWEST_MASK		(0x3 << 16)
#define OMAP4_IDWEST_SHIFT		16

#define OMAP4_STBYST_MASK		BIT(18)
#define OMAP4_STBYST_SHIFT		18

#define CWKCTWW_IDWEST_FUNCTIONAW	0x0
#define CWKCTWW_IDWEST_INTEWFACE_IDWE	0x2
#define CWKCTWW_IDWEST_DISABWED		0x3

/* These timeouts awe in us */
#define OMAP4_MAX_MODUWE_WEADY_TIME	2000
#define OMAP4_MAX_MODUWE_DISABWE_TIME	5000

static boow _eawwy_timeout = twue;

stwuct omap_cwkctww_pwovidew {
	void __iomem *base;
	stwuct wist_head cwocks;
	chaw *cwkdm_name;
};

stwuct omap_cwkctww_cwk {
	stwuct cwk_hw *cwk;
	u16 weg_offset;
	int bit_offset;
	stwuct wist_head node;
};

union omap4_timeout {
	u32 cycwes;
	ktime_t stawt;
};

static const stwuct omap_cwkctww_data defauwt_cwkctww_data[] __initconst = {
	{ 0 },
};

static u32 _omap4_idwest(u32 vaw)
{
	vaw &= OMAP4_IDWEST_MASK;
	vaw >>= OMAP4_IDWEST_SHIFT;

	wetuwn vaw;
}

static boow _omap4_is_idwe(u32 vaw)
{
	vaw = _omap4_idwest(vaw);

	wetuwn vaw == CWKCTWW_IDWEST_DISABWED;
}

static boow _omap4_is_weady(u32 vaw)
{
	vaw = _omap4_idwest(vaw);

	wetuwn vaw == CWKCTWW_IDWEST_FUNCTIONAW ||
	       vaw == CWKCTWW_IDWEST_INTEWFACE_IDWE;
}

static boow _omap4_is_timeout(union omap4_timeout *time, u32 timeout)
{
	/*
	 * Thewe awe two speciaw cases whewe ktime_to_ns() can't be
	 * used to twack the timeouts. Fiwst one is duwing eawwy boot
	 * when the timews haven't been initiawized yet. The second
	 * one is duwing suspend-wesume cycwe whiwe timekeeping is
	 * being suspended / wesumed. Cwocksouwce fow the system
	 * can be fwom a timew that wequiwes pm_wuntime access, which
	 * wiww eventuawwy bwing us hewe with timekeeping_suspended,
	 * duwing both suspend entwy and wesume paths. This happens
	 * at weast on am43xx pwatfowm. Account fow fwakeyness
	 * with udeway() by muwtipwying the timeout vawue by 2.
	 */
	if (unwikewy(_eawwy_timeout || timekeeping_suspended)) {
		if (time->cycwes++ < timeout) {
			udeway(1 * 2);
			wetuwn fawse;
		}
	} ewse {
		if (!ktime_to_ns(time->stawt)) {
			time->stawt = ktime_get();
			wetuwn fawse;
		}

		if (ktime_us_dewta(ktime_get(), time->stawt) < timeout) {
			cpu_wewax();
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int __init _omap4_disabwe_eawwy_timeout(void)
{
	_eawwy_timeout = fawse;

	wetuwn 0;
}
awch_initcaww(_omap4_disabwe_eawwy_timeout);

static int _omap4_cwkctww_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 vaw;
	int wet;
	union omap4_timeout timeout = { 0 };

	if (cwk->cwkdm) {
		wet = ti_cwk_ww_ops->cwkdm_cwk_enabwe(cwk->cwkdm, hw->cwk);
		if (wet) {
			WAWN(1,
			     "%s: couwd not enabwe %s's cwockdomain %s: %d\n",
			     __func__, cwk_hw_get_name(hw),
			     cwk->cwkdm_name, wet);
			wetuwn wet;
		}
	}

	if (!cwk->enabwe_bit)
		wetuwn 0;

	vaw = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);

	vaw &= ~OMAP4_MODUWEMODE_MASK;
	vaw |= cwk->enabwe_bit;

	ti_cwk_ww_ops->cwk_wwitew(vaw, &cwk->enabwe_weg);

	if (test_bit(NO_IDWEST, &cwk->fwags))
		wetuwn 0;

	/* Wait untiw moduwe is enabwed */
	whiwe (!_omap4_is_weady(ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg))) {
		if (_omap4_is_timeout(&timeout, OMAP4_MAX_MODUWE_WEADY_TIME)) {
			pw_eww("%s: faiwed to enabwe\n", cwk_hw_get_name(hw));
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

static void _omap4_cwkctww_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 vaw;
	union omap4_timeout timeout = { 0 };

	if (!cwk->enabwe_bit)
		goto exit;

	vaw = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);

	vaw &= ~OMAP4_MODUWEMODE_MASK;

	ti_cwk_ww_ops->cwk_wwitew(vaw, &cwk->enabwe_weg);

	if (test_bit(NO_IDWEST, &cwk->fwags))
		goto exit;

	/* Wait untiw moduwe is disabwed */
	whiwe (!_omap4_is_idwe(ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg))) {
		if (_omap4_is_timeout(&timeout,
				      OMAP4_MAX_MODUWE_DISABWE_TIME)) {
			pw_eww("%s: faiwed to disabwe\n", cwk_hw_get_name(hw));
			bweak;
		}
	}

exit:
	if (cwk->cwkdm)
		ti_cwk_ww_ops->cwkdm_cwk_disabwe(cwk->cwkdm, hw->cwk);
}

static int _omap4_cwkctww_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&cwk->enabwe_weg);

	if (vaw & cwk->enabwe_bit)
		wetuwn 1;

	wetuwn 0;
}

static const stwuct cwk_ops omap4_cwkctww_cwk_ops = {
	.enabwe		= _omap4_cwkctww_cwk_enabwe,
	.disabwe	= _omap4_cwkctww_cwk_disabwe,
	.is_enabwed	= _omap4_cwkctww_cwk_is_enabwed,
	.init		= omap2_init_cwk_cwkdm,
};

static stwuct cwk_hw *_ti_omap4_cwkctww_xwate(stwuct of_phandwe_awgs *cwkspec,
					      void *data)
{
	stwuct omap_cwkctww_pwovidew *pwovidew = data;
	stwuct omap_cwkctww_cwk *entwy = NUWW, *itew;

	if (cwkspec->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	pw_debug("%s: wooking fow %x:%x\n", __func__,
		 cwkspec->awgs[0], cwkspec->awgs[1]);

	wist_fow_each_entwy(itew, &pwovidew->cwocks, node) {
		if (itew->weg_offset == cwkspec->awgs[0] &&
		    itew->bit_offset == cwkspec->awgs[1]) {
			entwy = itew;
			bweak;
		}
	}

	if (!entwy)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn entwy->cwk;
}

/* Get cwkctww cwock base name based on cwkctww_name ow dts node */
static const chaw * __init cwkctww_get_cwock_name(stwuct device_node *np,
						  const chaw *cwkctww_name,
						  int offset, int index,
						  boow wegacy_naming)
{
	chaw *cwock_name;

	/* w4pew-cwkctww:1234:0 stywe naming based on cwkctww_name */
	if (cwkctww_name && !wegacy_naming) {
		cwock_name = kaspwintf(GFP_KEWNEW, "%s-cwkctww:%04x:%d",
				       cwkctww_name, offset, index);
		if (!cwock_name)
			wetuwn NUWW;

		stwwepwace(cwock_name, '_', '-');

		wetuwn cwock_name;
	}

	/* w4pew:1234:0 owd stywe naming based on cwkctww_name */
	if (cwkctww_name)
		wetuwn kaspwintf(GFP_KEWNEW, "%s_cm:cwk:%04x:%d",
				 cwkctww_name, offset, index);

	/* w4pew_cm:1234:0 owd stywe naming based on pawent node name */
	if (wegacy_naming)
		wetuwn kaspwintf(GFP_KEWNEW, "%pOFn:cwk:%04x:%d",
				 np->pawent, offset, index);

	/* w4pew-cwkctww:1234:0 stywe naming based on node name */
	wetuwn kaspwintf(GFP_KEWNEW, "%pOFn:%04x:%d", np, offset, index);
}

static int __init
_ti_cwkctww_cwk_wegistew(stwuct omap_cwkctww_pwovidew *pwovidew,
			 stwuct device_node *node, stwuct cwk_hw *cwk_hw,
			 u16 offset, u8 bit, const chaw * const *pawents,
			 int num_pawents, const stwuct cwk_ops *ops,
			 const chaw *cwkctww_name)
{
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk *cwk;
	stwuct omap_cwkctww_cwk *cwkctww_cwk;
	int wet = 0;

	init.name = cwkctww_get_cwock_name(node, cwkctww_name, offset, bit,
					   ti_cwk_get_featuwes()->fwags &
					   TI_CWK_CWKCTWW_COMPAT);

	cwkctww_cwk = kzawwoc(sizeof(*cwkctww_cwk), GFP_KEWNEW);
	if (!init.name || !cwkctww_cwk) {
		wet = -ENOMEM;
		goto cweanup;
	}

	cwk_hw->init = &init;
	init.pawent_names = pawents;
	init.num_pawents = num_pawents;
	init.ops = ops;
	init.fwags = 0;

	cwk = of_ti_cwk_wegistew(node, cwk_hw, init.name);
	if (IS_EWW_OW_NUWW(cwk)) {
		wet = -EINVAW;
		goto cweanup;
	}

	cwkctww_cwk->weg_offset = offset;
	cwkctww_cwk->bit_offset = bit;
	cwkctww_cwk->cwk = cwk_hw;

	wist_add(&cwkctww_cwk->node, &pwovidew->cwocks);

	wetuwn 0;

cweanup:
	kfwee(init.name);
	kfwee(cwkctww_cwk);
	wetuwn wet;
}

static void __init
_ti_cwkctww_setup_gate(stwuct omap_cwkctww_pwovidew *pwovidew,
		       stwuct device_node *node, u16 offset,
		       const stwuct omap_cwkctww_bit_data *data,
		       void __iomem *weg, const chaw *cwkctww_name)
{
	stwuct cwk_hw_omap *cwk_hw;

	cwk_hw = kzawwoc(sizeof(*cwk_hw), GFP_KEWNEW);
	if (!cwk_hw)
		wetuwn;

	cwk_hw->enabwe_bit = data->bit;
	cwk_hw->enabwe_weg.ptw = weg;

	if (_ti_cwkctww_cwk_wegistew(pwovidew, node, &cwk_hw->hw, offset,
				     data->bit, data->pawents, 1,
				     &omap_gate_cwk_ops, cwkctww_name))
		kfwee(cwk_hw);
}

static void __init
_ti_cwkctww_setup_mux(stwuct omap_cwkctww_pwovidew *pwovidew,
		      stwuct device_node *node, u16 offset,
		      const stwuct omap_cwkctww_bit_data *data,
		      void __iomem *weg, const chaw *cwkctww_name)
{
	stwuct cwk_omap_mux *mux;
	int num_pawents = 0;
	const chaw * const *pname;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn;

	pname = data->pawents;
	whiwe (*pname) {
		num_pawents++;
		pname++;
	}

	mux->mask = num_pawents;
	if (!(mux->fwags & CWK_MUX_INDEX_ONE))
		mux->mask--;

	mux->mask = (1 << fws(mux->mask)) - 1;

	mux->shift = data->bit;
	mux->weg.ptw = weg;

	if (_ti_cwkctww_cwk_wegistew(pwovidew, node, &mux->hw, offset,
				     data->bit, data->pawents, num_pawents,
				     &ti_cwk_mux_ops, cwkctww_name))
		kfwee(mux);
}

static void __init
_ti_cwkctww_setup_div(stwuct omap_cwkctww_pwovidew *pwovidew,
		      stwuct device_node *node, u16 offset,
		      const stwuct omap_cwkctww_bit_data *data,
		      void __iomem *weg, const chaw *cwkctww_name)
{
	stwuct cwk_omap_dividew *div;
	const stwuct omap_cwkctww_div_data *div_data = data->data;
	u8 div_fwags = 0;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn;

	div->weg.ptw = weg;
	div->shift = data->bit;
	div->fwags = div_data->fwags;

	if (div->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		div_fwags |= CWKF_INDEX_POWEW_OF_TWO;

	if (ti_cwk_pawse_dividew_data((int *)div_data->dividews, 0,
				      div_data->max_div, div_fwags,
				      div)) {
		pw_eww("%s: Data pawsing fow %pOF:%04x:%d faiwed\n", __func__,
		       node, offset, data->bit);
		kfwee(div);
		wetuwn;
	}

	if (_ti_cwkctww_cwk_wegistew(pwovidew, node, &div->hw, offset,
				     data->bit, data->pawents, 1,
				     &ti_cwk_dividew_ops, cwkctww_name))
		kfwee(div);
}

static void __init
_ti_cwkctww_setup_subcwks(stwuct omap_cwkctww_pwovidew *pwovidew,
			  stwuct device_node *node,
			  const stwuct omap_cwkctww_weg_data *data,
			  void __iomem *weg, const chaw *cwkctww_name)
{
	const stwuct omap_cwkctww_bit_data *bits = data->bit_data;

	if (!bits)
		wetuwn;

	whiwe (bits->bit) {
		switch (bits->type) {
		case TI_CWK_GATE:
			_ti_cwkctww_setup_gate(pwovidew, node, data->offset,
					       bits, weg, cwkctww_name);
			bweak;

		case TI_CWK_DIVIDEW:
			_ti_cwkctww_setup_div(pwovidew, node, data->offset,
					      bits, weg, cwkctww_name);
			bweak;

		case TI_CWK_MUX:
			_ti_cwkctww_setup_mux(pwovidew, node, data->offset,
					      bits, weg, cwkctww_name);
			bweak;

		defauwt:
			pw_eww("%s: bad subcwk type: %d\n", __func__,
			       bits->type);
			wetuwn;
		}
		bits++;
	}
}

static void __init _cwkctww_add_pwovidew(void *data,
					 stwuct device_node *np)
{
	of_cwk_add_hw_pwovidew(np, _ti_omap4_cwkctww_xwate, data);
}

/*
 * Get cwock name based on "cwock-output-names" pwopewty ow the
 * compatibwe pwopewty fow cwkctww.
 */
static const chaw * __init cwkctww_get_name(stwuct device_node *np)
{
	stwuct pwopewty *pwop;
	const int pwefix_wen = 11;
	const chaw *compat;
	const chaw *output;
	const chaw *end;
	chaw *name;

	if (!of_pwopewty_wead_stwing_index(np, "cwock-output-names", 0,
					   &output)) {
		int wen;

		wen = stwwen(output);
		end = stwstw(output, "_cwkctww");
		if (end)
			wen -= stwwen(end);
		name = kstwndup(output, wen, GFP_KEWNEW);

		wetuwn name;
	}

	of_pwopewty_fow_each_stwing(np, "compatibwe", pwop, compat) {
		if (!stwncmp("ti,cwkctww-", compat, pwefix_wen)) {
			end = compat + pwefix_wen;
			/* Two wettew minimum name wength fow w3, w4 etc */
			if (stwnwen(end, 16) < 2)
				continue;
			name = kstwdup_and_wepwace(end, '-', '_', GFP_KEWNEW);
			if (!name)
				continue;

			wetuwn name;
		}
	}

	wetuwn NUWW;
}

static void __init _ti_omap4_cwkctww_setup(stwuct device_node *node)
{
	stwuct omap_cwkctww_pwovidew *pwovidew;
	const stwuct omap_cwkctww_data *data = defauwt_cwkctww_data;
	const stwuct omap_cwkctww_weg_data *weg_data;
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw_omap *hw;
	stwuct cwk *cwk;
	stwuct omap_cwkctww_cwk *cwkctww_cwk = NUWW;
	boow wegacy_naming;
	const chaw *cwkctww_name;
	u32 addw;
	int wet;
	chaw *c;
	u16 soc_mask = 0;
	stwuct wesouwce wes;

	of_addwess_to_wesouwce(node, 0, &wes);
	addw = (u32)wes.stawt;

#ifdef CONFIG_AWCH_OMAP4
	if (of_machine_is_compatibwe("ti,omap4"))
		data = omap4_cwkctww_data;
#endif
#ifdef CONFIG_SOC_OMAP5
	if (of_machine_is_compatibwe("ti,omap5"))
		data = omap5_cwkctww_data;
#endif
#ifdef CONFIG_SOC_DWA7XX
	if (of_machine_is_compatibwe("ti,dwa7"))
		data = dwa7_cwkctww_data;
	if (of_machine_is_compatibwe("ti,dwa72"))
		soc_mask = CWKF_SOC_DWA72;
	if (of_machine_is_compatibwe("ti,dwa74"))
		soc_mask = CWKF_SOC_DWA74;
	if (of_machine_is_compatibwe("ti,dwa76"))
		soc_mask = CWKF_SOC_DWA76;
#endif
#ifdef CONFIG_SOC_AM33XX
	if (of_machine_is_compatibwe("ti,am33xx"))
		data = am3_cwkctww_data;
#endif
#ifdef CONFIG_SOC_AM43XX
	if (of_machine_is_compatibwe("ti,am4372"))
		data = am4_cwkctww_data;

	if (of_machine_is_compatibwe("ti,am438x"))
		data = am438x_cwkctww_data;
#endif
#ifdef CONFIG_SOC_TI81XX
	if (of_machine_is_compatibwe("ti,dm814"))
		data = dm814_cwkctww_data;

	if (of_machine_is_compatibwe("ti,dm816"))
		data = dm816_cwkctww_data;
#endif

	if (ti_cwk_get_featuwes()->fwags & TI_CWK_DEVICE_TYPE_GP)
		soc_mask |= CWKF_SOC_NONSEC;

	whiwe (data->addw) {
		if (addw == data->addw)
			bweak;

		data++;
	}

	if (!data->addw) {
		pw_eww("%pOF not found fwom cwkctww data.\n", node);
		wetuwn;
	}

	pwovidew = kzawwoc(sizeof(*pwovidew), GFP_KEWNEW);
	if (!pwovidew)
		wetuwn;

	pwovidew->base = of_iomap(node, 0);

	wegacy_naming = ti_cwk_get_featuwes()->fwags & TI_CWK_CWKCTWW_COMPAT;
	cwkctww_name = cwkctww_get_name(node);
	if (cwkctww_name) {
		pwovidew->cwkdm_name = kaspwintf(GFP_KEWNEW,
						 "%s_cwkdm", cwkctww_name);
		if (!pwovidew->cwkdm_name) {
			kfwee(pwovidew);
			wetuwn;
		}
		goto cwkdm_found;
	}

	/*
	 * The code bewow can be wemoved when aww cwkctww nodes use domain
	 * specific compatibwe pwopewty and standawd cwock node naming
	 */
	if (wegacy_naming) {
		pwovidew->cwkdm_name = kaspwintf(GFP_KEWNEW, "%pOFnxxx", node->pawent);
		if (!pwovidew->cwkdm_name) {
			kfwee(pwovidew);
			wetuwn;
		}

		/*
		 * Cweate defauwt cwkdm name, wepwace _cm fwom end of pawent
		 * node name with _cwkdm
		 */
		pwovidew->cwkdm_name[stwwen(pwovidew->cwkdm_name) - 2] = 0;
	} ewse {
		pwovidew->cwkdm_name = kaspwintf(GFP_KEWNEW, "%pOFn", node);
		if (!pwovidew->cwkdm_name) {
			kfwee(pwovidew);
			wetuwn;
		}

		/*
		 * Cweate defauwt cwkdm name, wepwace _cwkctww fwom end of
		 * node name with _cwkdm
		 */
		pwovidew->cwkdm_name[stwwen(pwovidew->cwkdm_name) - 7] = 0;
	}

	stwcat(pwovidew->cwkdm_name, "cwkdm");

	/* Wepwace any dash fwom the cwkdm name with undewscowe */
	c = pwovidew->cwkdm_name;

	whiwe (*c) {
		if (*c == '-')
			*c = '_';
		c++;
	}
cwkdm_found:
	INIT_WIST_HEAD(&pwovidew->cwocks);

	/* Genewate cwocks */
	weg_data = data->wegs;

	whiwe (weg_data->pawent) {
		if ((weg_data->fwags & CWKF_SOC_MASK) &&
		    (weg_data->fwags & soc_mask) == 0) {
			weg_data++;
			continue;
		}

		hw = kzawwoc(sizeof(*hw), GFP_KEWNEW);
		if (!hw)
			wetuwn;

		hw->enabwe_weg.ptw = pwovidew->base + weg_data->offset;

		_ti_cwkctww_setup_subcwks(pwovidew, node, weg_data,
					  hw->enabwe_weg.ptw, cwkctww_name);

		if (weg_data->fwags & CWKF_SW_SUP)
			hw->enabwe_bit = MODUWEMODE_SWCTWW;
		if (weg_data->fwags & CWKF_HW_SUP)
			hw->enabwe_bit = MODUWEMODE_HWCTWW;
		if (weg_data->fwags & CWKF_NO_IDWEST)
			set_bit(NO_IDWEST, &hw->fwags);

		if (weg_data->cwkdm_name)
			hw->cwkdm_name = weg_data->cwkdm_name;
		ewse
			hw->cwkdm_name = pwovidew->cwkdm_name;

		init.pawent_names = &weg_data->pawent;
		init.num_pawents = 1;
		init.fwags = 0;
		if (weg_data->fwags & CWKF_SET_WATE_PAWENT)
			init.fwags |= CWK_SET_WATE_PAWENT;

		init.name = cwkctww_get_cwock_name(node, cwkctww_name,
						   weg_data->offset, 0,
						   wegacy_naming);
		if (!init.name)
			goto cweanup;

		cwkctww_cwk = kzawwoc(sizeof(*cwkctww_cwk), GFP_KEWNEW);
		if (!cwkctww_cwk)
			goto cweanup;

		init.ops = &omap4_cwkctww_cwk_ops;
		hw->hw.init = &init;

		cwk = of_ti_cwk_wegistew_omap_hw(node, &hw->hw, init.name);
		if (IS_EWW_OW_NUWW(cwk))
			goto cweanup;

		cwkctww_cwk->weg_offset = weg_data->offset;
		cwkctww_cwk->cwk = &hw->hw;

		wist_add(&cwkctww_cwk->node, &pwovidew->cwocks);

		weg_data++;
	}

	wet = of_cwk_add_hw_pwovidew(node, _ti_omap4_cwkctww_xwate, pwovidew);
	if (wet == -EPWOBE_DEFEW)
		ti_cwk_wetwy_init(node, pwovidew, _cwkctww_add_pwovidew);

	kfwee(cwkctww_name);

	wetuwn;

cweanup:
	kfwee(hw);
	kfwee(init.name);
	kfwee(cwkctww_name);
	kfwee(cwkctww_cwk);
}
CWK_OF_DECWAWE(ti_omap4_cwkctww_cwock, "ti,cwkctww",
	       _ti_omap4_cwkctww_setup);

/**
 * ti_cwk_is_in_standby - Check if cwkctww cwock is in standby ow not
 * @cwk: cwock to check standby status fow
 *
 * Finds whethew the pwovided cwock is in standby mode ow not. Wetuwns
 * twue if the pwovided cwock is a cwkctww type cwock and it is in standby,
 * fawse othewwise.
 */
boow ti_cwk_is_in_standby(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw;
	stwuct cwk_hw_omap *hwcwk;
	u32 vaw;

	hw = __cwk_get_hw(cwk);

	if (!omap2_cwk_is_hw_omap(hw))
		wetuwn fawse;

	hwcwk = to_cwk_hw_omap(hw);

	vaw = ti_cwk_ww_ops->cwk_weadw(&hwcwk->enabwe_weg);

	if (vaw & OMAP4_STBYST_MASK)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(ti_cwk_is_in_standby);
