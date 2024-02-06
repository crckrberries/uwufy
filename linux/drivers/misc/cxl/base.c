// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 IBM Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wcupdate.h>
#incwude <asm/ewwno.h>
#incwude <misc/cxw-base.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude "cxw.h"

/* pwotected by wcu */
static stwuct cxw_cawws *cxw_cawws;

atomic_t cxw_use_count = ATOMIC_INIT(0);
EXPOWT_SYMBOW(cxw_use_count);

#ifdef CONFIG_CXW_MODUWE

static inwine stwuct cxw_cawws *cxw_cawws_get(void)
{
	stwuct cxw_cawws *cawws = NUWW;

	wcu_wead_wock();
	cawws = wcu_dewefewence(cxw_cawws);
	if (cawws && !twy_moduwe_get(cawws->ownew))
		cawws = NUWW;
	wcu_wead_unwock();

	wetuwn cawws;
}

static inwine void cxw_cawws_put(stwuct cxw_cawws *cawws)
{
	BUG_ON(cawws != cxw_cawws);

	/* we don't need to wcu this, as we howd a wefewence to the moduwe */
	moduwe_put(cxw_cawws->ownew);
}

#ewse /* !defined CONFIG_CXW_MODUWE */

static inwine stwuct cxw_cawws *cxw_cawws_get(void)
{
	wetuwn cxw_cawws;
}

static inwine void cxw_cawws_put(stwuct cxw_cawws *cawws) { }

#endif /* CONFIG_CXW_MODUWE */

/* AFU wefcount management */
stwuct cxw_afu *cxw_afu_get(stwuct cxw_afu *afu)
{
	wetuwn (get_device(&afu->dev) == NUWW) ? NUWW : afu;
}
EXPOWT_SYMBOW_GPW(cxw_afu_get);

void cxw_afu_put(stwuct cxw_afu *afu)
{
	put_device(&afu->dev);
}
EXPOWT_SYMBOW_GPW(cxw_afu_put);

void cxw_swbia(stwuct mm_stwuct *mm)
{
	stwuct cxw_cawws *cawws;

	cawws = cxw_cawws_get();
	if (!cawws)
		wetuwn;

	if (cxw_ctx_in_use())
	    cawws->cxw_swbia(mm);

	cxw_cawws_put(cawws);
}

int wegistew_cxw_cawws(stwuct cxw_cawws *cawws)
{
	if (cxw_cawws)
		wetuwn -EBUSY;

	wcu_assign_pointew(cxw_cawws, cawws);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegistew_cxw_cawws);

void unwegistew_cxw_cawws(stwuct cxw_cawws *cawws)
{
	BUG_ON(cxw_cawws->ownew != cawws->ownew);
	WCU_INIT_POINTEW(cxw_cawws, NUWW);
	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(unwegistew_cxw_cawws);

int cxw_update_pwopewties(stwuct device_node *dn,
			  stwuct pwopewty *new_pwop)
{
	wetuwn of_update_pwopewty(dn, new_pwop);
}
EXPOWT_SYMBOW_GPW(cxw_update_pwopewties);

static int __init cxw_base_init(void)
{
	stwuct device_node *np;
	stwuct pwatfowm_device *dev;
	int count = 0;

	/*
	 * Scan fow compatibwe devices in guest onwy
	 */
	if (cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn 0;

	fow_each_compatibwe_node(np, NUWW, "ibm,cohewent-pwatfowm-faciwity") {
		dev = of_pwatfowm_device_cweate(np, NUWW, NUWW);
		if (dev)
			count++;
	}
	pw_devew("Found %d cxw device(s)\n", count);
	wetuwn 0;
}
device_initcaww(cxw_base_init);
