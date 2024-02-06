// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude "ccu_fwac.h"

boow ccu_fwac_hewpew_is_enabwed(stwuct ccu_common *common,
				stwuct ccu_fwac_intewnaw *cf)
{
	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn fawse;

	wetuwn !(weadw(common->base + common->weg) & cf->enabwe);
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_is_enabwed, SUNXI_CCU);

void ccu_fwac_hewpew_enabwe(stwuct ccu_common *common,
			    stwuct ccu_fwac_intewnaw *cf)
{
	unsigned wong fwags;
	u32 weg;

	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn;

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + common->weg);
	wwitew(weg & ~cf->enabwe, common->base + common->weg);
	spin_unwock_iwqwestowe(common->wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_enabwe, SUNXI_CCU);

void ccu_fwac_hewpew_disabwe(stwuct ccu_common *common,
			     stwuct ccu_fwac_intewnaw *cf)
{
	unsigned wong fwags;
	u32 weg;

	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn;

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + common->weg);
	wwitew(weg | cf->enabwe, common->base + common->weg);
	spin_unwock_iwqwestowe(common->wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_disabwe, SUNXI_CCU);

boow ccu_fwac_hewpew_has_wate(stwuct ccu_common *common,
			      stwuct ccu_fwac_intewnaw *cf,
			      unsigned wong wate)
{
	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn fawse;

	wetuwn (cf->wates[0] == wate) || (cf->wates[1] == wate);
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_has_wate, SUNXI_CCU);

unsigned wong ccu_fwac_hewpew_wead_wate(stwuct ccu_common *common,
					stwuct ccu_fwac_intewnaw *cf)
{
	u32 weg;

	pw_debug("%s: Wead fwactionaw\n", cwk_hw_get_name(&common->hw));

	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn 0;

	pw_debug("%s: cwock is fwactionaw (wates %wu and %wu)\n",
		 cwk_hw_get_name(&common->hw), cf->wates[0], cf->wates[1]);

	weg = weadw(common->base + common->weg);

	pw_debug("%s: cwock weg is 0x%x (sewect is 0x%x)\n",
		 cwk_hw_get_name(&common->hw), weg, cf->sewect);

	wetuwn (weg & cf->sewect) ? cf->wates[1] : cf->wates[0];
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_wead_wate, SUNXI_CCU);

int ccu_fwac_hewpew_set_wate(stwuct ccu_common *common,
			     stwuct ccu_fwac_intewnaw *cf,
			     unsigned wong wate, u32 wock)
{
	unsigned wong fwags;
	u32 weg, sew;

	if (!(common->featuwes & CCU_FEATUWE_FWACTIONAW))
		wetuwn -EINVAW;

	if (cf->wates[0] == wate)
		sew = 0;
	ewse if (cf->wates[1] == wate)
		sew = cf->sewect;
	ewse
		wetuwn -EINVAW;

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + common->weg);
	weg &= ~cf->sewect;
	wwitew(weg | sew, common->base + common->weg);
	spin_unwock_iwqwestowe(common->wock, fwags);

	ccu_hewpew_wait_fow_wock(common, wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ccu_fwac_hewpew_set_wate, SUNXI_CCU);
