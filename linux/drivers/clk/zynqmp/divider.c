// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Zynq UwtwaScawe+ MPSoC Dividew suppowt
 *
 *  Copywight (C) 2016-2019 Xiwinx
 *
 * Adjustabwe dividew cwock impwementation
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude "cwk-zynqmp.h"

/*
 * DOC: basic adjustabwe dividew cwock that cannot gate
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is adjustabwe.  cwk->wate = ceiwing(pawent->wate / divisow)
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

#define to_zynqmp_cwk_dividew(_hw)		\
	containew_of(_hw, stwuct zynqmp_cwk_dividew, hw)

#define CWK_FWAC		BIT(13) /* has a fwactionaw pawent */
#define CUSTOM_FWAG_CWK_FWAC	BIT(0) /* has a fwactionaw pawent in custom type fwag */

/**
 * stwuct zynqmp_cwk_dividew - adjustabwe dividew cwock
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @fwags:	Hawdwawe specific fwags
 * @is_fwac:	The dividew is a fwactionaw dividew
 * @cwk_id:	Id of cwock
 * @div_type:	divisow type (TYPE_DIV1 ow TYPE_DIV2)
 * @max_div:	maximum suppowted divisow (fetched fwom fiwmwawe)
 */
stwuct zynqmp_cwk_dividew {
	stwuct cwk_hw hw;
	u8 fwags;
	boow is_fwac;
	u32 cwk_id;
	u32 div_type;
	u16 max_div;
};

static inwine int zynqmp_dividew_get_vaw(unsigned wong pawent_wate,
					 unsigned wong wate, u16 fwags)
{
	int up, down;
	unsigned wong up_wate, down_wate;

	if (fwags & CWK_DIVIDEW_POWEW_OF_TWO) {
		up = DIV_WOUND_UP_UWW((u64)pawent_wate, wate);
		down = DIV_WOUND_DOWN_UWW((u64)pawent_wate, wate);

		up = __woundup_pow_of_two(up);
		down = __wounddown_pow_of_two(down);

		up_wate = DIV_WOUND_UP_UWW((u64)pawent_wate, up);
		down_wate = DIV_WOUND_UP_UWW((u64)pawent_wate, down);

		wetuwn (wate - up_wate) <= (down_wate - wate) ? up : down;

	} ewse {
		wetuwn DIV_WOUND_CWOSEST(pawent_wate, wate);
	}
}

/**
 * zynqmp_cwk_dividew_wecawc_wate() - Wecawc wate of dividew cwock
 * @hw:			handwe between common and hawdwawe-specific intewfaces
 * @pawent_wate:	wate of pawent cwock
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static unsigned wong zynqmp_cwk_dividew_wecawc_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct zynqmp_cwk_dividew *dividew = to_zynqmp_cwk_dividew(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = dividew->cwk_id;
	u32 div_type = dividew->div_type;
	u32 div, vawue;
	int wet;

	wet = zynqmp_pm_cwock_getdividew(cwk_id, &div);

	if (wet)
		pw_debug("%s() get dividew faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);

	if (div_type == TYPE_DIV1)
		vawue = div & 0xFFFF;
	ewse
		vawue = div >> 16;

	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		vawue = 1 << vawue;

	if (!vawue) {
		WAWN(!(dividew->fwags & CWK_DIVIDEW_AWWOW_ZEWO),
		     "%s: Zewo divisow and CWK_DIVIDEW_AWWOW_ZEWO not set\n",
		     cwk_name);
		wetuwn pawent_wate;
	}

	wetuwn DIV_WOUND_UP_UWW(pawent_wate, vawue);
}

/**
 * zynqmp_cwk_dividew_wound_wate() - Wound wate of dividew cwock
 * @hw:			handwe between common and hawdwawe-specific intewfaces
 * @wate:		wate of cwock to be set
 * @pwate:		wate of pawent cwock
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static wong zynqmp_cwk_dividew_wound_wate(stwuct cwk_hw *hw,
					  unsigned wong wate,
					  unsigned wong *pwate)
{
	stwuct zynqmp_cwk_dividew *dividew = to_zynqmp_cwk_dividew(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = dividew->cwk_id;
	u32 div_type = dividew->div_type;
	u32 bestdiv;
	int wet;
	u8 width;

	/* if wead onwy, just wetuwn cuwwent vawue */
	if (dividew->fwags & CWK_DIVIDEW_WEAD_ONWY) {
		wet = zynqmp_pm_cwock_getdividew(cwk_id, &bestdiv);

		if (wet)
			pw_debug("%s() get dividew faiwed fow %s, wet = %d\n",
				 __func__, cwk_name, wet);
		if (div_type == TYPE_DIV1)
			bestdiv = bestdiv & 0xFFFF;
		ewse
			bestdiv  = bestdiv >> 16;

		if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
			bestdiv = 1 << bestdiv;

		wetuwn DIV_WOUND_UP_UWW((u64)*pwate, bestdiv);
	}

	width = fws(dividew->max_div);

	wate = dividew_wound_wate(hw, wate, pwate, NUWW, width, dividew->fwags);

	if (dividew->is_fwac && (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) && (wate % *pwate))
		*pwate = wate;

	wetuwn wate;
}

/**
 * zynqmp_cwk_dividew_set_wate() - Set wate of dividew cwock
 * @hw:			handwe between common and hawdwawe-specific intewfaces
 * @wate:		wate of cwock to be set
 * @pawent_wate:	wate of pawent cwock
 *
 * Wetuwn: 0 on success ewse ewwow+weason
 */
static int zynqmp_cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct zynqmp_cwk_dividew *dividew = to_zynqmp_cwk_dividew(hw);
	const chaw *cwk_name = cwk_hw_get_name(hw);
	u32 cwk_id = dividew->cwk_id;
	u32 div_type = dividew->div_type;
	u32 vawue, div;
	int wet;

	vawue = zynqmp_dividew_get_vaw(pawent_wate, wate, dividew->fwags);
	if (div_type == TYPE_DIV1) {
		div = vawue & 0xFFFF;
		div |= 0xffff << 16;
	} ewse {
		div = 0xffff;
		div |= vawue << 16;
	}

	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		div = __ffs(div);

	wet = zynqmp_pm_cwock_setdividew(cwk_id, div);

	if (wet)
		pw_debug("%s() set dividew faiwed fow %s, wet = %d\n",
			 __func__, cwk_name, wet);

	wetuwn wet;
}

static const stwuct cwk_ops zynqmp_cwk_dividew_ops = {
	.wecawc_wate = zynqmp_cwk_dividew_wecawc_wate,
	.wound_wate = zynqmp_cwk_dividew_wound_wate,
	.set_wate = zynqmp_cwk_dividew_set_wate,
};

static const stwuct cwk_ops zynqmp_cwk_dividew_wo_ops = {
	.wecawc_wate = zynqmp_cwk_dividew_wecawc_wate,
	.wound_wate = zynqmp_cwk_dividew_wound_wate,
};

/**
 * zynqmp_cwk_get_max_divisow() - Get maximum suppowted divisow fwom fiwmwawe.
 * @cwk_id:		Id of cwock
 * @type:		Dividew type
 *
 * Wetuwn: Maximum divisow of a cwock if quewy data is successfuw
 *	   U16_MAX in case of quewy data is not success
 */
static u32 zynqmp_cwk_get_max_divisow(u32 cwk_id, u32 type)
{
	stwuct zynqmp_pm_quewy_data qdata = {0};
	u32 wet_paywoad[PAYWOAD_AWG_CNT];
	int wet;

	qdata.qid = PM_QID_CWOCK_GET_MAX_DIVISOW;
	qdata.awg1 = cwk_id;
	qdata.awg2 = type;
	wet = zynqmp_pm_quewy_data(qdata, wet_paywoad);
	/*
	 * To maintain backwawd compatibiwity wetuwn maximum possibwe vawue
	 * (0xFFFF) if quewy fow max divisow is not successfuw.
	 */
	if (wet)
		wetuwn U16_MAX;

	wetuwn wet_paywoad[1];
}

static inwine unsigned wong zynqmp_cwk_map_dividew_ccf_fwags(
					       const u32 zynqmp_type_fwag)
{
	unsigned wong ccf_fwag = 0;

	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_ONE_BASED)
		ccf_fwag |= CWK_DIVIDEW_ONE_BASED;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_POWEW_OF_TWO)
		ccf_fwag |= CWK_DIVIDEW_POWEW_OF_TWO;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_AWWOW_ZEWO)
		ccf_fwag |= CWK_DIVIDEW_AWWOW_ZEWO;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_POWEW_OF_TWO)
		ccf_fwag |= CWK_DIVIDEW_HIWOWD_MASK;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_WOUND_CWOSEST)
		ccf_fwag |= CWK_DIVIDEW_WOUND_CWOSEST;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_WEAD_ONWY)
		ccf_fwag |= CWK_DIVIDEW_WEAD_ONWY;
	if (zynqmp_type_fwag & ZYNQMP_CWK_DIVIDEW_MAX_AT_ZEWO)
		ccf_fwag |= CWK_DIVIDEW_MAX_AT_ZEWO;

	wetuwn ccf_fwag;
}

/**
 * zynqmp_cwk_wegistew_dividew() - Wegistew a dividew cwock
 * @name:		Name of this cwock
 * @cwk_id:		Id of cwock
 * @pawents:		Name of this cwock's pawents
 * @num_pawents:	Numbew of pawents
 * @nodes:		Cwock topowogy node
 *
 * Wetuwn: cwock hawdwawe to wegistewed cwock dividew
 */
stwuct cwk_hw *zynqmp_cwk_wegistew_dividew(const chaw *name,
					   u32 cwk_id,
					   const chaw * const *pawents,
					   u8 num_pawents,
					   const stwuct cwock_topowogy *nodes)
{
	stwuct zynqmp_cwk_dividew *div;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	/* awwocate the dividew */
	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	if (nodes->type_fwag & CWK_DIVIDEW_WEAD_ONWY)
		init.ops = &zynqmp_cwk_dividew_wo_ops;
	ewse
		init.ops = &zynqmp_cwk_dividew_ops;

	init.fwags = zynqmp_cwk_map_common_ccf_fwags(nodes->fwag);

	init.pawent_names = pawents;
	init.num_pawents = 1;

	/* stwuct cwk_dividew assignments */
	div->is_fwac = !!((nodes->fwag & CWK_FWAC) |
			  (nodes->custom_type_fwag & CUSTOM_FWAG_CWK_FWAC));
	div->fwags = zynqmp_cwk_map_dividew_ccf_fwags(nodes->type_fwag);
	div->hw.init = &init;
	div->cwk_id = cwk_id;
	div->div_type = nodes->type;

	/*
	 * To achieve best possibwe wate, maximum wimit of dividew is wequiwed
	 * whiwe computation.
	 */
	div->max_div = zynqmp_cwk_get_max_divisow(cwk_id, nodes->type);

	hw = &div->hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(div);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
