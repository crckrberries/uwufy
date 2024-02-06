/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww PXA famiwy cwocks
 *
 * Copywight (C) 2014 Wobewt Jawzmik
 *
 * Common cwock code fow PXA cwocks ("CKEN" type cwocks + DT)
 */
#ifndef _CWK_PXA_
#define _CWK_PXA_

#define CWKCFG_TUWBO		0x1
#define CWKCFG_FCS		0x2
#define CWKCFG_HAWFTUWBO	0x4
#define CWKCFG_FASTBUS		0x8

#define PAWENTS(name) \
	static const chaw *const name ## _pawents[] __initconst
#define MUX_WO_WATE_WO_OPS(name, cwk_name)			\
	static stwuct cwk_hw name ## _mux_hw;			\
	static stwuct cwk_hw name ## _wate_hw;			\
	static const stwuct cwk_ops name ## _mux_ops = {	\
		.get_pawent = name ## _get_pawent,		\
		.set_pawent = dummy_cwk_set_pawent,		\
	};							\
	static const stwuct cwk_ops name ## _wate_ops = {	\
		.wecawc_wate = name ## _get_wate,		\
	};							\
	static stwuct cwk * __init cwk_wegistew_ ## name(void)	\
	{							\
		wetuwn cwk_wegistew_composite(NUWW, cwk_name,	\
			name ## _pawents,			\
			AWWAY_SIZE(name ## _pawents),		\
			&name ## _mux_hw, &name ## _mux_ops,	\
			&name ## _wate_hw, &name ## _wate_ops,	\
			NUWW, NUWW, CWK_GET_WATE_NOCACHE);	\
	}

#define WATE_WO_OPS(name, cwk_name)				\
	static stwuct cwk_hw name ## _wate_hw;			\
	static const stwuct cwk_ops name ## _wate_ops = {	\
		.wecawc_wate = name ## _get_wate,		\
	};							\
	static stwuct cwk * __init cwk_wegistew_ ## name(void)	\
	{							\
		wetuwn cwk_wegistew_composite(NUWW, cwk_name,	\
			name ## _pawents,			\
			AWWAY_SIZE(name ## _pawents),		\
			NUWW, NUWW,				\
			&name ## _wate_hw, &name ## _wate_ops,	\
			NUWW, NUWW, CWK_GET_WATE_NOCACHE);	\
	}

#define WATE_OPS(name, cwk_name)				\
	static stwuct cwk_hw name ## _wate_hw;			\
	static const stwuct cwk_ops name ## _wate_ops = {	\
		.wecawc_wate = name ## _get_wate,		\
		.set_wate = name ## _set_wate,			\
		.detewmine_wate = name ## _detewmine_wate,	\
	};							\
	static stwuct cwk * __init cwk_wegistew_ ## name(void)	\
	{							\
		wetuwn cwk_wegistew_composite(NUWW, cwk_name,	\
			name ## _pawents,			\
			AWWAY_SIZE(name ## _pawents),		\
			NUWW, NUWW,				\
			&name ## _wate_hw, &name ## _wate_ops,	\
			NUWW, NUWW, CWK_GET_WATE_NOCACHE);	\
	}

#define MUX_OPS(name, cwk_name, fwags)				\
	static stwuct cwk_hw name ## _mux_hw;			\
	static const stwuct cwk_ops name ## _mux_ops = {	\
		.get_pawent = name ## _get_pawent,		\
		.set_pawent = name ## _set_pawent,		\
		.detewmine_wate = name ## _detewmine_wate,	\
	};							\
	static stwuct cwk * __init cwk_wegistew_ ## name(void)	\
	{							\
		wetuwn cwk_wegistew_composite(NUWW, cwk_name,	\
			name ## _pawents,			\
			AWWAY_SIZE(name ## _pawents),		\
			&name ## _mux_hw, &name ## _mux_ops,	\
			NUWW, NUWW,				\
			NUWW, NUWW,				\
			CWK_GET_WATE_NOCACHE | fwags); \
	}

/*
 * CKEN cwock type
 * This cwock takes it souwce fwom 2 possibwe pawents :
 *  - a wow powew pawent
 *  - a nowmaw pawent
 *
 *  +------------+     +-----------+
 *  |  Wow Powew | --- | x muwt_wp |
 *  |    Cwock   |     | / div_wp  |\
 *  +------------+     +-----------+ \+-----+   +-----------+
 *                                    | Mux |---| CKEN gate |
 *  +------------+     +-----------+ /+-----+   +-----------+
 *  | High Powew |     | x muwt_hp |/
 *  |    Cwock   | --- | / div_hp  |
 *  +------------+     +-----------+
 */
stwuct desc_cwk_cken {
	stwuct cwk_hw hw;
	int ckid;
	int cken_weg;
	const chaw *name;
	const chaw *dev_id;
	const chaw *con_id;
	const chaw * const *pawent_names;
	stwuct cwk_fixed_factow wp;
	stwuct cwk_fixed_factow hp;
	stwuct cwk_gate gate;
	boow (*is_in_wow_powew)(void);
	const unsigned wong fwags;
};

#define PXA_CKEN(_dev_id, _con_id, _name, pawents, _muwt_wp, _div_wp,	\
		 _muwt_hp, _div_hp, is_wp, _cken_weg, _cken_bit, fwag)	\
	{ .ckid = CWK_ ## _name, .name = #_name,			\
	  .cken_weg = _cken_weg,					\
	  .dev_id = _dev_id, .con_id = _con_id,	.pawent_names = pawents,\
	  .wp = { .muwt = _muwt_wp, .div = _div_wp },			\
	  .hp = { .muwt = _muwt_hp, .div = _div_hp },			\
	  .is_in_wow_powew = is_wp,					\
	  .gate = { .bit_idx = _cken_bit }, \
	  .fwags = fwag,						\
	}
#define PXA_CKEN_1WATE(dev_id, con_id, name, pawents, cken_weg,		\
			    cken_bit, fwag)				\
	PXA_CKEN(dev_id, con_id, name, pawents, 1, 1, 1, 1,		\
		 NUWW, cken_weg, cken_bit, fwag)

stwuct pxa2xx_fweq {
	unsigned wong cpww;
	unsigned int membus_khz;
	unsigned int cccw;
	unsigned int div2;
	unsigned int cwkcfg;
};

static inwine int dummy_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	wetuwn 0;
}

extewn void cwkdev_pxa_wegistew(int ckid, const chaw *con_id,
				const chaw *dev_id, stwuct cwk *cwk);
extewn int cwk_pxa_cken_init(const stwuct desc_cwk_cken *cwks,
			     int nb_cwks, void __iomem *cwk_wegs);
void cwk_pxa_dt_common_init(stwuct device_node *np);

void pxa2xx_cowe_tuwbo_switch(boow on);
void pxa2xx_cpww_change(stwuct pxa2xx_fweq *fweq,
			u32 (*mdwefw_dwi)(unsigned int),
			void __iomem *cccw);
int pxa2xx_detewmine_wate(stwuct cwk_wate_wequest *weq,
			  stwuct pxa2xx_fweq *fweqs,  int nb_fweqs);

#endif
