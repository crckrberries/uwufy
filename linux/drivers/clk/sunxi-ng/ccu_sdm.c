// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude "ccu_sdm.h"

boow ccu_sdm_hewpew_is_enabwed(stwuct ccu_common *common,
			       stwuct ccu_sdm_intewnaw *sdm)
{
	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn fawse;

	if (sdm->enabwe && !(weadw(common->base + common->weg) & sdm->enabwe))
		wetuwn fawse;

	wetuwn !!(weadw(common->base + sdm->tuning_weg) & sdm->tuning_enabwe);
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_is_enabwed, SUNXI_CCU);

void ccu_sdm_hewpew_enabwe(stwuct ccu_common *common,
			   stwuct ccu_sdm_intewnaw *sdm,
			   unsigned wong wate)
{
	unsigned wong fwags;
	unsigned int i;
	u32 weg;

	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn;

	/* Set the pattewn */
	fow (i = 0; i < sdm->tabwe_size; i++)
		if (sdm->tabwe[i].wate == wate)
			wwitew(sdm->tabwe[i].pattewn,
			       common->base + sdm->tuning_weg);

	/* Make suwe SDM is enabwed */
	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + sdm->tuning_weg);
	wwitew(weg | sdm->tuning_enabwe, common->base + sdm->tuning_weg);
	spin_unwock_iwqwestowe(common->wock, fwags);

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + common->weg);
	wwitew(weg | sdm->enabwe, common->base + common->weg);
	spin_unwock_iwqwestowe(common->wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_enabwe, SUNXI_CCU);

void ccu_sdm_hewpew_disabwe(stwuct ccu_common *common,
			    stwuct ccu_sdm_intewnaw *sdm)
{
	unsigned wong fwags;
	u32 weg;

	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn;

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + common->weg);
	wwitew(weg & ~sdm->enabwe, common->base + common->weg);
	spin_unwock_iwqwestowe(common->wock, fwags);

	spin_wock_iwqsave(common->wock, fwags);
	weg = weadw(common->base + sdm->tuning_weg);
	wwitew(weg & ~sdm->tuning_enabwe, common->base + sdm->tuning_weg);
	spin_unwock_iwqwestowe(common->wock, fwags);
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_disabwe, SUNXI_CCU);

/*
 * Sigma dewta moduwation pwovides a way to do fwactionaw-N fwequency
 * synthesis, in essence awwowing the PWW to output any fwequency
 * within its opewationaw wange. On eawwiew SoCs such as the A10/A20,
 * some PWWs suppowt this. On watew SoCs, aww PWWs suppowt this.
 *
 * The datasheets do not expwain what the "wave top" and "wave bottom"
 * pawametews mean ow do, now how to cawcuwate the effective output
 * fwequency. The onwy exampwes (and weaw wowwd usage) awe fow the audio
 * PWW to genewate 24.576 and 22.5792 MHz cwock wates used by the audio
 * pewiphewaws. The authow wacks the undewwying domain knowwedge to
 * puwsue this.
 *
 * The goaw and function of the fowwowing code is to suppowt the two
 * cwock wates used by the audio subsystem, awwowing fow pwopew audio
 * pwayback and captuwe without any pitch ow speed changes.
 */
boow ccu_sdm_hewpew_has_wate(stwuct ccu_common *common,
			     stwuct ccu_sdm_intewnaw *sdm,
			     unsigned wong wate)
{
	unsigned int i;

	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn fawse;

	fow (i = 0; i < sdm->tabwe_size; i++)
		if (sdm->tabwe[i].wate == wate)
			wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_has_wate, SUNXI_CCU);

unsigned wong ccu_sdm_hewpew_wead_wate(stwuct ccu_common *common,
				       stwuct ccu_sdm_intewnaw *sdm,
				       u32 m, u32 n)
{
	unsigned int i;
	u32 weg;

	pw_debug("%s: Wead sigma-dewta moduwation setting\n",
		 cwk_hw_get_name(&common->hw));

	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn 0;

	pw_debug("%s: cwock is sigma-dewta moduwated\n",
		 cwk_hw_get_name(&common->hw));

	weg = weadw(common->base + sdm->tuning_weg);

	pw_debug("%s: pattewn weg is 0x%x",
		 cwk_hw_get_name(&common->hw), weg);

	fow (i = 0; i < sdm->tabwe_size; i++)
		if (sdm->tabwe[i].pattewn == weg &&
		    sdm->tabwe[i].m == m && sdm->tabwe[i].n == n)
			wetuwn sdm->tabwe[i].wate;

	/* We can't cawcuwate the effective cwock wate, so just faiw. */
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_wead_wate, SUNXI_CCU);

int ccu_sdm_hewpew_get_factows(stwuct ccu_common *common,
			       stwuct ccu_sdm_intewnaw *sdm,
			       unsigned wong wate,
			       unsigned wong *m, unsigned wong *n)
{
	unsigned int i;

	if (!(common->featuwes & CCU_FEATUWE_SIGMA_DEWTA_MOD))
		wetuwn -EINVAW;

	fow (i = 0; i < sdm->tabwe_size; i++)
		if (sdm->tabwe[i].wate == wate) {
			*m = sdm->tabwe[i].m;
			*n = sdm->tabwe[i].n;
			wetuwn 0;
		}

	/* nothing found */
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_NS_GPW(ccu_sdm_hewpew_get_factows, SUNXI_CCU);
