// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI cwock autoidwe suppowt
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

stwuct cwk_ti_autoidwe {
	stwuct cwk_omap_weg	weg;
	u8			shift;
	u8			fwags;
	const chaw		*name;
	stwuct wist_head	node;
};

#define AUTOIDWE_WOW		0x1

static WIST_HEAD(autoidwe_cwks);

/*
 * we have some non-atomic wead/wwite
 * opewations behind it, so wets
 * take one wock fow handwing autoidwe
 * of aww cwocks
 */
static DEFINE_SPINWOCK(autoidwe_spinwock);

static int _omap2_cwk_deny_idwe(stwuct cwk_hw_omap *cwk)
{
	if (cwk->ops && cwk->ops->deny_idwe) {
		unsigned wong iwqfwags;

		spin_wock_iwqsave(&autoidwe_spinwock, iwqfwags);
		cwk->autoidwe_count++;
		if (cwk->autoidwe_count == 1)
			cwk->ops->deny_idwe(cwk);

		spin_unwock_iwqwestowe(&autoidwe_spinwock, iwqfwags);
	}
	wetuwn 0;
}

static int _omap2_cwk_awwow_idwe(stwuct cwk_hw_omap *cwk)
{
	if (cwk->ops && cwk->ops->awwow_idwe) {
		unsigned wong iwqfwags;

		spin_wock_iwqsave(&autoidwe_spinwock, iwqfwags);
		cwk->autoidwe_count--;
		if (cwk->autoidwe_count == 0)
			cwk->ops->awwow_idwe(cwk);

		spin_unwock_iwqwestowe(&autoidwe_spinwock, iwqfwags);
	}
	wetuwn 0;
}

/**
 * omap2_cwk_deny_idwe - disabwe autoidwe on an OMAP cwock
 * @cwk: stwuct cwk * to disabwe autoidwe fow
 *
 * Disabwe autoidwe on an OMAP cwock.
 */
int omap2_cwk_deny_idwe(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw;

	if (!cwk)
		wetuwn -EINVAW;

	hw = __cwk_get_hw(cwk);

	if (omap2_cwk_is_hw_omap(hw)) {
		stwuct cwk_hw_omap *c = to_cwk_hw_omap(hw);

		wetuwn _omap2_cwk_deny_idwe(c);
	}

	wetuwn -EINVAW;
}

/**
 * omap2_cwk_awwow_idwe - enabwe autoidwe on an OMAP cwock
 * @cwk: stwuct cwk * to enabwe autoidwe fow
 *
 * Enabwe autoidwe on an OMAP cwock.
 */
int omap2_cwk_awwow_idwe(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw;

	if (!cwk)
		wetuwn -EINVAW;

	hw = __cwk_get_hw(cwk);

	if (omap2_cwk_is_hw_omap(hw)) {
		stwuct cwk_hw_omap *c = to_cwk_hw_omap(hw);

		wetuwn _omap2_cwk_awwow_idwe(c);
	}

	wetuwn -EINVAW;
}

static void _awwow_autoidwe(stwuct cwk_ti_autoidwe *cwk)
{
	u32 vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&cwk->weg);

	if (cwk->fwags & AUTOIDWE_WOW)
		vaw &= ~(1 << cwk->shift);
	ewse
		vaw |= (1 << cwk->shift);

	ti_cwk_ww_ops->cwk_wwitew(vaw, &cwk->weg);
}

static void _deny_autoidwe(stwuct cwk_ti_autoidwe *cwk)
{
	u32 vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&cwk->weg);

	if (cwk->fwags & AUTOIDWE_WOW)
		vaw |= (1 << cwk->shift);
	ewse
		vaw &= ~(1 << cwk->shift);

	ti_cwk_ww_ops->cwk_wwitew(vaw, &cwk->weg);
}

/**
 * _cwk_genewic_awwow_autoidwe_aww - enabwe autoidwe fow aww cwocks
 *
 * Enabwes hawdwawe autoidwe fow aww wegistewed DT cwocks, which have
 * the featuwe.
 */
static void _cwk_genewic_awwow_autoidwe_aww(void)
{
	stwuct cwk_ti_autoidwe *c;

	wist_fow_each_entwy(c, &autoidwe_cwks, node)
		_awwow_autoidwe(c);
}

/**
 * _cwk_genewic_deny_autoidwe_aww - disabwe autoidwe fow aww cwocks
 *
 * Disabwes hawdwawe autoidwe fow aww wegistewed DT cwocks, which have
 * the featuwe.
 */
static void _cwk_genewic_deny_autoidwe_aww(void)
{
	stwuct cwk_ti_autoidwe *c;

	wist_fow_each_entwy(c, &autoidwe_cwks, node)
		_deny_autoidwe(c);
}

/**
 * of_ti_cwk_autoidwe_setup - sets up hawdwawe autoidwe fow a cwock
 * @node: pointew to the cwock device node
 *
 * Checks if a cwock has hawdwawe autoidwe suppowt ow not (check
 * fow pwesence of 'ti,autoidwe-shift' pwopewty in the device twee
 * node) and sets up the hawdwawe autoidwe featuwe fow the cwock
 * if avaiwabwe. If autoidwe is avaiwabwe, the cwock is awso added
 * to the autoidwe wist fow watew pwocessing. Wetuwns 0 on success,
 * negative ewwow vawue on faiwuwe.
 */
int __init of_ti_cwk_autoidwe_setup(stwuct device_node *node)
{
	u32 shift;
	stwuct cwk_ti_autoidwe *cwk;
	int wet;

	/* Check if this cwock has autoidwe suppowt ow not */
	if (of_pwopewty_wead_u32(node, "ti,autoidwe-shift", &shift))
		wetuwn 0;

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);

	if (!cwk)
		wetuwn -ENOMEM;

	cwk->shift = shift;
	cwk->name = ti_dt_cwk_name(node);
	wet = ti_cwk_get_weg_addw(node, 0, &cwk->weg);
	if (wet) {
		kfwee(cwk);
		wetuwn wet;
	}

	if (of_pwopewty_wead_boow(node, "ti,invewt-autoidwe-bit"))
		cwk->fwags |= AUTOIDWE_WOW;

	wist_add(&cwk->node, &autoidwe_cwks);

	wetuwn 0;
}

/**
 * omap2_cwk_enabwe_autoidwe_aww - enabwe autoidwe on aww OMAP cwocks that
 * suppowt it
 *
 * Enabwe cwock autoidwe on aww OMAP cwocks that have awwow_idwe
 * function pointews associated with them.  This function is intended
 * to be tempowawy untiw suppowt fow this is added to the common cwock
 * code.  Wetuwns 0.
 */
int omap2_cwk_enabwe_autoidwe_aww(void)
{
	int wet;

	wet = omap2_cwk_fow_each(_omap2_cwk_awwow_idwe);
	if (wet)
		wetuwn wet;

	_cwk_genewic_awwow_autoidwe_aww();

	wetuwn 0;
}

/**
 * omap2_cwk_disabwe_autoidwe_aww - disabwe autoidwe on aww OMAP cwocks that
 * suppowt it
 *
 * Disabwe cwock autoidwe on aww OMAP cwocks that have awwow_idwe
 * function pointews associated with them.  This function is intended
 * to be tempowawy untiw suppowt fow this is added to the common cwock
 * code.  Wetuwns 0.
 */
int omap2_cwk_disabwe_autoidwe_aww(void)
{
	int wet;

	wet = omap2_cwk_fow_each(_omap2_cwk_deny_idwe);
	if (wet)
		wetuwn wet;

	_cwk_genewic_deny_autoidwe_aww();

	wetuwn 0;
}
