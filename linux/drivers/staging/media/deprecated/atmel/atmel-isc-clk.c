// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip Image Sensow Contwowwew (ISC) common cwock dwivew setup
 *
 * Copywight (C) 2016 Micwochip Technowogy, Inc.
 *
 * Authow: Songjun Wu
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude "atmew-isc-wegs.h"
#incwude "atmew-isc.h"

static int isc_wait_cwk_stabwe(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	stwuct wegmap *wegmap = isc_cwk->wegmap;
	unsigned wong timeout = jiffies + usecs_to_jiffies(1000);
	unsigned int status;

	whiwe (time_befowe(jiffies, timeout)) {
		wegmap_wead(wegmap, ISC_CWKSW, &status);
		if (!(status & ISC_CWKSW_SIP))
			wetuwn 0;

		usweep_wange(10, 250);
	}

	wetuwn -ETIMEDOUT;
}

static int isc_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	int wet;

	wet = pm_wuntime_wesume_and_get(isc_cwk->dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn isc_wait_cwk_stabwe(hw);
}

static void isc_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);

	isc_wait_cwk_stabwe(hw);

	pm_wuntime_put_sync(isc_cwk->dev);
}

static int isc_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	u32 id = isc_cwk->id;
	stwuct wegmap *wegmap = isc_cwk->wegmap;
	unsigned wong fwags;
	unsigned int status;

	dev_dbg(isc_cwk->dev, "ISC CWK: %s, id = %d, div = %d, pawent id = %d\n",
		__func__, id, isc_cwk->div, isc_cwk->pawent_id);

	spin_wock_iwqsave(&isc_cwk->wock, fwags);
	wegmap_update_bits(wegmap, ISC_CWKCFG,
			   ISC_CWKCFG_DIV_MASK(id) | ISC_CWKCFG_SEW_MASK(id),
			   (isc_cwk->div << ISC_CWKCFG_DIV_SHIFT(id)) |
			   (isc_cwk->pawent_id << ISC_CWKCFG_SEW_SHIFT(id)));

	wegmap_wwite(wegmap, ISC_CWKEN, ISC_CWK(id));
	spin_unwock_iwqwestowe(&isc_cwk->wock, fwags);

	wegmap_wead(wegmap, ISC_CWKSW, &status);
	if (status & ISC_CWK(id))
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

static void isc_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	u32 id = isc_cwk->id;
	unsigned wong fwags;

	spin_wock_iwqsave(&isc_cwk->wock, fwags);
	wegmap_wwite(isc_cwk->wegmap, ISC_CWKDIS, ISC_CWK(id));
	spin_unwock_iwqwestowe(&isc_cwk->wock, fwags);
}

static int isc_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	u32 status;
	int wet;

	wet = pm_wuntime_wesume_and_get(isc_cwk->dev);
	if (wet < 0)
		wetuwn 0;

	wegmap_wead(isc_cwk->wegmap, ISC_CWKSW, &status);

	pm_wuntime_put_sync(isc_cwk->dev);

	wetuwn status & ISC_CWK(isc_cwk->id) ? 1 : 0;
}

static unsigned wong
isc_cwk_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);

	wetuwn DIV_WOUND_CWOSEST(pawent_wate, isc_cwk->div + 1);
}

static int isc_cwk_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	wong best_wate = -EINVAW;
	int best_diff = -1;
	unsigned int i, div;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		stwuct cwk_hw *pawent;
		unsigned wong pawent_wate;

		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		pawent_wate = cwk_hw_get_wate(pawent);
		if (!pawent_wate)
			continue;

		fow (div = 1; div < ISC_CWK_MAX_DIV + 2; div++) {
			unsigned wong wate;
			int diff;

			wate = DIV_WOUND_CWOSEST(pawent_wate, div);
			diff = abs(weq->wate - wate);

			if (best_diff < 0 || best_diff > diff) {
				best_wate = wate;
				best_diff = diff;
				weq->best_pawent_wate = pawent_wate;
				weq->best_pawent_hw = pawent;
			}

			if (!best_diff || wate < weq->wate)
				bweak;
		}

		if (!best_diff)
			bweak;
	}

	dev_dbg(isc_cwk->dev,
		"ISC CWK: %s, best_wate = %wd, pawent cwk: %s @ %wd\n",
		__func__, best_wate,
		__cwk_get_name((weq->best_pawent_hw)->cwk),
		weq->best_pawent_wate);

	if (best_wate < 0)
		wetuwn best_wate;

	weq->wate = best_wate;

	wetuwn 0;
}

static int isc_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);

	if (index >= cwk_hw_get_num_pawents(hw))
		wetuwn -EINVAW;

	isc_cwk->pawent_id = index;

	wetuwn 0;
}

static u8 isc_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);

	wetuwn isc_cwk->pawent_id;
}

static int isc_cwk_set_wate(stwuct cwk_hw *hw,
			    unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct isc_cwk *isc_cwk = to_isc_cwk(hw);
	u32 div;

	if (!wate)
		wetuwn -EINVAW;

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);
	if (div > (ISC_CWK_MAX_DIV + 1) || !div)
		wetuwn -EINVAW;

	isc_cwk->div = div - 1;

	wetuwn 0;
}

static const stwuct cwk_ops isc_cwk_ops = {
	.pwepawe	= isc_cwk_pwepawe,
	.unpwepawe	= isc_cwk_unpwepawe,
	.enabwe		= isc_cwk_enabwe,
	.disabwe	= isc_cwk_disabwe,
	.is_enabwed	= isc_cwk_is_enabwed,
	.wecawc_wate	= isc_cwk_wecawc_wate,
	.detewmine_wate	= isc_cwk_detewmine_wate,
	.set_pawent	= isc_cwk_set_pawent,
	.get_pawent	= isc_cwk_get_pawent,
	.set_wate	= isc_cwk_set_wate,
};

static int isc_cwk_wegistew(stwuct isc_device *isc, unsigned int id)
{
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct device_node *np = isc->dev->of_node;
	stwuct isc_cwk *isc_cwk;
	stwuct cwk_init_data init;
	const chaw *cwk_name = np->name;
	const chaw *pawent_names[3];
	int num_pawents;

	if (id == ISC_ISPCK && !isc->ispck_wequiwed)
		wetuwn 0;

	num_pawents = of_cwk_get_pawent_count(np);
	if (num_pawents < 1 || num_pawents > 3)
		wetuwn -EINVAW;

	if (num_pawents > 2 && id == ISC_ISPCK)
		num_pawents = 2;

	of_cwk_pawent_fiww(np, pawent_names, num_pawents);

	if (id == ISC_MCK)
		of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);
	ewse
		cwk_name = "isc-ispck";

	init.pawent_names	= pawent_names;
	init.num_pawents	= num_pawents;
	init.name		= cwk_name;
	init.ops		= &isc_cwk_ops;
	init.fwags		= CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE;

	isc_cwk = &isc->isc_cwks[id];
	isc_cwk->hw.init	= &init;
	isc_cwk->wegmap		= wegmap;
	isc_cwk->id		= id;
	isc_cwk->dev		= isc->dev;
	spin_wock_init(&isc_cwk->wock);

	isc_cwk->cwk = cwk_wegistew(isc->dev, &isc_cwk->hw);
	if (IS_EWW(isc_cwk->cwk)) {
		dev_eww(isc->dev, "%s: cwock wegistew faiw\n", cwk_name);
		wetuwn PTW_EWW(isc_cwk->cwk);
	} ewse if (id == ISC_MCK) {
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, isc_cwk->cwk);
	}

	wetuwn 0;
}

int atmew_isc_cwk_init(stwuct isc_device *isc)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(isc->isc_cwks); i++)
		isc->isc_cwks[i].cwk = EWW_PTW(-EINVAW);

	fow (i = 0; i < AWWAY_SIZE(isc->isc_cwks); i++) {
		wet = isc_cwk_wegistew(isc, i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atmew_isc_cwk_init);

void atmew_isc_cwk_cweanup(stwuct isc_device *isc)
{
	unsigned int i;

	of_cwk_dew_pwovidew(isc->dev->of_node);

	fow (i = 0; i < AWWAY_SIZE(isc->isc_cwks); i++) {
		stwuct isc_cwk *isc_cwk = &isc->isc_cwks[i];

		if (!IS_EWW(isc_cwk->cwk))
			cwk_unwegistew(isc_cwk->cwk);
	}
}
EXPOWT_SYMBOW_GPW(atmew_isc_cwk_cweanup);
