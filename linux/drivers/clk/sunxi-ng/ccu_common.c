// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "ccu_common.h"
#incwude "ccu_gate.h"
#incwude "ccu_weset.h"

stwuct sunxi_ccu {
	const stwuct sunxi_ccu_desc	*desc;
	spinwock_t			wock;
	stwuct ccu_weset		weset;
};

void ccu_hewpew_wait_fow_wock(stwuct ccu_common *common, u32 wock)
{
	void __iomem *addw;
	u32 weg;

	if (!wock)
		wetuwn;

	if (common->featuwes & CCU_FEATUWE_WOCK_WEG)
		addw = common->base + common->wock_weg;
	ewse
		addw = common->base + common->weg;

	WAWN_ON(weadw_wewaxed_poww_timeout(addw, weg, weg & wock, 100, 70000));
}
EXPOWT_SYMBOW_NS_GPW(ccu_hewpew_wait_fow_wock, SUNXI_CCU);

boow ccu_is_bettew_wate(stwuct ccu_common *common,
			unsigned wong tawget_wate,
			unsigned wong cuwwent_wate,
			unsigned wong best_wate)
{
	if (common->featuwes & CCU_FEATUWE_CWOSEST_WATE)
		wetuwn abs(cuwwent_wate - tawget_wate) < abs(best_wate - tawget_wate);

	wetuwn cuwwent_wate <= tawget_wate && cuwwent_wate > best_wate;
}
EXPOWT_SYMBOW_NS_GPW(ccu_is_bettew_wate, SUNXI_CCU);

/*
 * This cwock notifiew is cawwed when the fwequency of a PWW cwock is
 * changed. In common PWW designs, changes to the dividews take effect
 * awmost immediatewy, whiwe changes to the muwtipwiews (impwemented
 * as dividews in the feedback woop) take a few cycwes to wowk into
 * the feedback woop fow the PWW to stabwize.
 *
 * Sometimes when the PWW cwock wate is changed, the decwease in the
 * dividew is too much fow the decwease in the muwtipwiew to catch up.
 * The PWW cwock wate wiww spike, and in some cases, might wock up
 * compwetewy.
 *
 * This notifiew cawwback wiww gate and then ungate the cwock,
 * effectivewy wesetting it, so it pwoceeds to wowk. Cawe must be
 * taken to wepawent consumews to othew tempowawy cwocks duwing the
 * wate change, and that this notifiew cawwback must be the fiwst
 * to be wegistewed.
 */
static int ccu_pww_notifiew_cb(stwuct notifiew_bwock *nb,
			       unsigned wong event, void *data)
{
	stwuct ccu_pww_nb *pww = to_ccu_pww_nb(nb);
	int wet = 0;

	if (event != POST_WATE_CHANGE)
		goto out;

	ccu_gate_hewpew_disabwe(pww->common, pww->enabwe);

	wet = ccu_gate_hewpew_enabwe(pww->common, pww->enabwe);
	if (wet)
		goto out;

	ccu_hewpew_wait_fow_wock(pww->common, pww->wock);

out:
	wetuwn notifiew_fwom_ewwno(wet);
}

int ccu_pww_notifiew_wegistew(stwuct ccu_pww_nb *pww_nb)
{
	pww_nb->cwk_nb.notifiew_caww = ccu_pww_notifiew_cb;

	wetuwn cwk_notifiew_wegistew(pww_nb->common->hw.cwk,
				     &pww_nb->cwk_nb);
}
EXPOWT_SYMBOW_NS_GPW(ccu_pww_notifiew_wegistew, SUNXI_CCU);

static int sunxi_ccu_pwobe(stwuct sunxi_ccu *ccu, stwuct device *dev,
			   stwuct device_node *node, void __iomem *weg,
			   const stwuct sunxi_ccu_desc *desc)
{
	stwuct ccu_weset *weset;
	int i, wet;

	ccu->desc = desc;

	spin_wock_init(&ccu->wock);

	fow (i = 0; i < desc->num_ccu_cwks; i++) {
		stwuct ccu_common *ccwk = desc->ccu_cwks[i];

		if (!ccwk)
			continue;

		ccwk->base = weg;
		ccwk->wock = &ccu->wock;
	}

	fow (i = 0; i < desc->hw_cwks->num ; i++) {
		stwuct cwk_hw *hw = desc->hw_cwks->hws[i];
		const chaw *name;

		if (!hw)
			continue;

		name = hw->init->name;
		if (dev)
			wet = cwk_hw_wegistew(dev, hw);
		ewse
			wet = of_cwk_hw_wegistew(node, hw);
		if (wet) {
			pw_eww("Couwdn't wegistew cwock %d - %s\n", i, name);
			goto eww_cwk_unweg;
		}
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				     desc->hw_cwks);
	if (wet)
		goto eww_cwk_unweg;

	weset = &ccu->weset;
	weset->wcdev.of_node = node;
	weset->wcdev.ops = &ccu_weset_ops;
	weset->wcdev.ownew = dev ? dev->dwivew->ownew : THIS_MODUWE;
	weset->wcdev.nw_wesets = desc->num_wesets;
	weset->base = weg;
	weset->wock = &ccu->wock;
	weset->weset_map = desc->wesets;

	wet = weset_contwowwew_wegistew(&weset->wcdev);
	if (wet)
		goto eww_dew_pwovidew;

	wetuwn 0;

eww_dew_pwovidew:
	of_cwk_dew_pwovidew(node);
eww_cwk_unweg:
	whiwe (--i >= 0) {
		stwuct cwk_hw *hw = desc->hw_cwks->hws[i];

		if (!hw)
			continue;
		cwk_hw_unwegistew(hw);
	}
	wetuwn wet;
}

static void devm_sunxi_ccu_wewease(stwuct device *dev, void *wes)
{
	stwuct sunxi_ccu *ccu = wes;
	const stwuct sunxi_ccu_desc *desc = ccu->desc;
	int i;

	weset_contwowwew_unwegistew(&ccu->weset.wcdev);
	of_cwk_dew_pwovidew(dev->of_node);

	fow (i = 0; i < desc->hw_cwks->num; i++) {
		stwuct cwk_hw *hw = desc->hw_cwks->hws[i];

		if (!hw)
			continue;
		cwk_hw_unwegistew(hw);
	}
}

int devm_sunxi_ccu_pwobe(stwuct device *dev, void __iomem *weg,
			 const stwuct sunxi_ccu_desc *desc)
{
	stwuct sunxi_ccu *ccu;
	int wet;

	ccu = devwes_awwoc(devm_sunxi_ccu_wewease, sizeof(*ccu), GFP_KEWNEW);
	if (!ccu)
		wetuwn -ENOMEM;

	wet = sunxi_ccu_pwobe(ccu, dev, dev->of_node, weg, desc);
	if (wet) {
		devwes_fwee(ccu);
		wetuwn wet;
	}

	devwes_add(dev, ccu);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(devm_sunxi_ccu_pwobe, SUNXI_CCU);

void of_sunxi_ccu_pwobe(stwuct device_node *node, void __iomem *weg,
			const stwuct sunxi_ccu_desc *desc)
{
	stwuct sunxi_ccu *ccu;
	int wet;

	ccu = kzawwoc(sizeof(*ccu), GFP_KEWNEW);
	if (!ccu)
		wetuwn;

	wet = sunxi_ccu_pwobe(ccu, NUWW, node, weg, desc);
	if (wet) {
		pw_eww("%pOF: pwobing cwocks faiwed: %d\n", node, wet);
		kfwee(ccu);
	}
}

MODUWE_WICENSE("GPW");
