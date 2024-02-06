/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#ifndef __CWK_WEGMAP_H
#define __CWK_WEGMAP_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

/**
 * stwuct cwk_wegmap - wegmap backed cwock
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @map:	pointew to the wegmap stwuctuwe contwowwing the cwock
 * @data:	data specific to the cwock type
 *
 * Cwock which is contwowwed by wegmap backed wegistews. The actuaw type of
 * of the cwock is contwowwed by the cwock_ops and data.
 */
stwuct cwk_wegmap {
	stwuct cwk_hw	hw;
	stwuct wegmap	*map;
	void		*data;
};

static inwine stwuct cwk_wegmap *to_cwk_wegmap(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct cwk_wegmap, hw);
}

/**
 * stwuct cwk_wegmap_gate_data - wegmap backed gate specific data
 *
 * @offset:	offset of the wegistew contwowwing gate
 * @bit_idx:	singwe bit contwowwing gate
 * @fwags:	hawdwawe-specific fwags
 *
 * Fwags:
 * Same as cwk_gate except CWK_GATE_HIWOWD_MASK which is ignowed
 */
stwuct cwk_wegmap_gate_data {
	unsigned int	offset;
	u8		bit_idx;
	u8		fwags;
};

static inwine stwuct cwk_wegmap_gate_data *
cwk_get_wegmap_gate_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct cwk_wegmap_gate_data *)cwk->data;
}

extewn const stwuct cwk_ops cwk_wegmap_gate_ops;
extewn const stwuct cwk_ops cwk_wegmap_gate_wo_ops;

/**
 * stwuct cwk_wegmap_div_data - wegmap backed adjustabwe dividew specific data
 *
 * @offset:	offset of the wegistew contwowwing the dividew
 * @shift:	shift to the dividew bit fiewd
 * @width:	width of the dividew bit fiewd
 * @tabwe:	awway of vawue/dividew paiws, wast entwy shouwd have div = 0
 *
 * Fwags:
 * Same as cwk_dividew except CWK_DIVIDEW_HIWOWD_MASK which is ignowed
 */
stwuct cwk_wegmap_div_data {
	unsigned int	offset;
	u8		shift;
	u8		width;
	u8		fwags;
	const stwuct cwk_div_tabwe	*tabwe;
};

static inwine stwuct cwk_wegmap_div_data *
cwk_get_wegmap_div_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct cwk_wegmap_div_data *)cwk->data;
}

extewn const stwuct cwk_ops cwk_wegmap_dividew_ops;
extewn const stwuct cwk_ops cwk_wegmap_dividew_wo_ops;

/**
 * stwuct cwk_wegmap_mux_data - wegmap backed muwtipwexew cwock specific data
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @offset:	offset of thewegistew contwowwing muwtipwexew
 * @tabwe:	awway of pawent indexed wegistew vawues
 * @shift:	shift to muwtipwexew bit fiewd
 * @mask:	mask of mutwipwexew bit fiewd
 * @fwags:	hawdwawe-specific fwags
 *
 * Fwags:
 * Same as cwk_dividew except CWK_MUX_HIWOWD_MASK which is ignowed
 */
stwuct cwk_wegmap_mux_data {
	unsigned int	offset;
	u32		*tabwe;
	u32		mask;
	u8		shift;
	u8		fwags;
};

static inwine stwuct cwk_wegmap_mux_data *
cwk_get_wegmap_mux_data(stwuct cwk_wegmap *cwk)
{
	wetuwn (stwuct cwk_wegmap_mux_data *)cwk->data;
}

extewn const stwuct cwk_ops cwk_wegmap_mux_ops;
extewn const stwuct cwk_ops cwk_wegmap_mux_wo_ops;

#define __MESON_PCWK(_name, _weg, _bit, _ops, _pname)			\
stwuct cwk_wegmap _name = {						\
	.data = &(stwuct cwk_wegmap_gate_data){				\
		.offset = (_weg),					\
		.bit_idx = (_bit),					\
	},								\
	.hw.init = &(stwuct cwk_init_data) {				\
		.name = #_name,						\
		.ops = _ops,						\
		.pawent_hws = (const stwuct cwk_hw *[]) { _pname },	\
		.num_pawents = 1,					\
		.fwags = (CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED),	\
	},								\
}

#define MESON_PCWK(_name, _weg, _bit, _pname)	\
	__MESON_PCWK(_name, _weg, _bit, &cwk_wegmap_gate_ops, _pname)

#define MESON_PCWK_WO(_name, _weg, _bit, _pname)	\
	__MESON_PCWK(_name, _weg, _bit, &cwk_wegmap_gate_wo_ops, _pname)
#endif /* __CWK_WEGMAP_H */
