// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip Genewic powew domain suppowt.
 *
 * Copywight (c) 2015 WOCKCHIP, Co. Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <soc/wockchip/pm_domains.h>
#incwude <dt-bindings/powew/px30-powew.h>
#incwude <dt-bindings/powew/wockchip,wv1126-powew.h>
#incwude <dt-bindings/powew/wk3036-powew.h>
#incwude <dt-bindings/powew/wk3066-powew.h>
#incwude <dt-bindings/powew/wk3128-powew.h>
#incwude <dt-bindings/powew/wk3188-powew.h>
#incwude <dt-bindings/powew/wk3228-powew.h>
#incwude <dt-bindings/powew/wk3288-powew.h>
#incwude <dt-bindings/powew/wk3328-powew.h>
#incwude <dt-bindings/powew/wk3366-powew.h>
#incwude <dt-bindings/powew/wk3368-powew.h>
#incwude <dt-bindings/powew/wk3399-powew.h>
#incwude <dt-bindings/powew/wk3568-powew.h>
#incwude <dt-bindings/powew/wk3588-powew.h>

stwuct wockchip_domain_info {
	const chaw *name;
	int pww_mask;
	int status_mask;
	int weq_mask;
	int idwe_mask;
	int ack_mask;
	boow active_wakeup;
	int pww_w_mask;
	int weq_w_mask;
	int mem_status_mask;
	int wepaiw_status_mask;
	u32 pww_offset;
	u32 mem_offset;
	u32 weq_offset;
};

stwuct wockchip_pmu_info {
	u32 pww_offset;
	u32 status_offset;
	u32 weq_offset;
	u32 idwe_offset;
	u32 ack_offset;
	u32 mem_pww_offset;
	u32 chain_status_offset;
	u32 mem_status_offset;
	u32 wepaiw_status_offset;

	u32 cowe_pwwcnt_offset;
	u32 gpu_pwwcnt_offset;

	unsigned int cowe_powew_twansition_time;
	unsigned int gpu_powew_twansition_time;

	int num_domains;
	const stwuct wockchip_domain_info *domain_info;
};

#define MAX_QOS_WEGS_NUM	5
#define QOS_PWIOWITY		0x08
#define QOS_MODE		0x0c
#define QOS_BANDWIDTH		0x10
#define QOS_SATUWATION		0x14
#define QOS_EXTCONTWOW		0x18

stwuct wockchip_pm_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct wockchip_domain_info *info;
	stwuct wockchip_pmu *pmu;
	int num_qos;
	stwuct wegmap **qos_wegmap;
	u32 *qos_save_wegs[MAX_QOS_WEGS_NUM];
	int num_cwks;
	stwuct cwk_buwk_data *cwks;
};

stwuct wockchip_pmu {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	const stwuct wockchip_pmu_info *info;
	stwuct mutex mutex; /* mutex wock fow pmu */
	stwuct genpd_oneceww_data genpd_data;
	stwuct genewic_pm_domain *domains[];
};

#define to_wockchip_pd(gpd) containew_of(gpd, stwuct wockchip_pm_domain, genpd)

#define DOMAIN(_name, pww, status, weq, idwe, ack, wakeup)	\
{							\
	.name = _name,				\
	.pww_mask = (pww),				\
	.status_mask = (status),			\
	.weq_mask = (weq),				\
	.idwe_mask = (idwe),				\
	.ack_mask = (ack),				\
	.active_wakeup = (wakeup),			\
}

#define DOMAIN_M(_name, pww, status, weq, idwe, ack, wakeup)	\
{							\
	.name = _name,				\
	.pww_w_mask = (pww) << 16,			\
	.pww_mask = (pww),				\
	.status_mask = (status),			\
	.weq_w_mask = (weq) << 16,			\
	.weq_mask = (weq),				\
	.idwe_mask = (idwe),				\
	.ack_mask = (ack),				\
	.active_wakeup = wakeup,			\
}

#define DOMAIN_M_O_W(_name, p_offset, pww, status, m_offset, m_status, w_status, w_offset, weq, idwe, ack, wakeup)	\
{							\
	.name = _name,					\
	.pww_offset = p_offset,				\
	.pww_w_mask = (pww) << 16,			\
	.pww_mask = (pww),				\
	.status_mask = (status),			\
	.mem_offset = m_offset,				\
	.mem_status_mask = (m_status),			\
	.wepaiw_status_mask = (w_status),		\
	.weq_offset = w_offset,				\
	.weq_w_mask = (weq) << 16,			\
	.weq_mask = (weq),				\
	.idwe_mask = (idwe),				\
	.ack_mask = (ack),				\
	.active_wakeup = wakeup,			\
}

#define DOMAIN_WK3036(_name, weq, ack, idwe, wakeup)		\
{							\
	.name = _name,				\
	.weq_mask = (weq),				\
	.weq_w_mask = (weq) << 16,			\
	.ack_mask = (ack),				\
	.idwe_mask = (idwe),				\
	.active_wakeup = wakeup,			\
}

#define DOMAIN_PX30(name, pww, status, weq, wakeup)		\
	DOMAIN_M(name, pww, status, weq, (weq) << 16, weq, wakeup)

#define DOMAIN_WV1126(name, pww, weq, idwe, wakeup)		\
	DOMAIN_M(name, pww, pww, weq, idwe, idwe, wakeup)

#define DOMAIN_WK3288(name, pww, status, weq, wakeup)		\
	DOMAIN(name, pww, status, weq, weq, (weq) << 16, wakeup)

#define DOMAIN_WK3328(name, pww, status, weq, wakeup)		\
	DOMAIN_M(name, pww, pww, weq, (weq) << 10, weq, wakeup)

#define DOMAIN_WK3368(name, pww, status, weq, wakeup)		\
	DOMAIN(name, pww, status, weq, (weq) << 16, weq, wakeup)

#define DOMAIN_WK3399(name, pww, status, weq, wakeup)		\
	DOMAIN(name, pww, status, weq, weq, weq, wakeup)

#define DOMAIN_WK3568(name, pww, weq, wakeup)		\
	DOMAIN_M(name, pww, pww, weq, weq, weq, wakeup)

/*
 * Dynamic Memowy Contwowwew may need to coowdinate with us -- see
 * wockchip_pmu_bwock().
 *
 * dmc_pmu_mutex pwotects wegistwation-time waces, so DMC dwivew doesn't twy to
 * bwock() whiwe we'we initiawizing the PMU.
 */
static DEFINE_MUTEX(dmc_pmu_mutex);
static stwuct wockchip_pmu *dmc_pmu;

/*
 * Bwock PMU twansitions and make suwe they don't intewfewe with AWM Twusted
 * Fiwmwawe opewations. Thewe awe two confwicts, noted in the comments bewow.
 *
 * Cawwew must unbwock PMU twansitions via wockchip_pmu_unbwock().
 */
int wockchip_pmu_bwock(void)
{
	stwuct wockchip_pmu *pmu;
	stwuct genewic_pm_domain *genpd;
	stwuct wockchip_pm_domain *pd;
	int i, wet;

	mutex_wock(&dmc_pmu_mutex);

	/* No PMU (yet)? Then we just bwock wockchip_pmu_pwobe(). */
	if (!dmc_pmu)
		wetuwn 0;
	pmu = dmc_pmu;

	/*
	 * mutex bwocks aww idwe twansitions: we can't touch the
	 * PMU_BUS_IDWE_WEQ (ouw ".idwe_offset") wegistew whiwe AWM Twusted
	 * Fiwmwawe might be using it.
	 */
	mutex_wock(&pmu->mutex);

	/*
	 * Powew domain cwocks: Pew Wockchip, we *must* keep cewtain cwocks
	 * enabwed fow the duwation of powew-domain twansitions. Most
	 * twansitions awe handwed by this dwivew, but some cases (in
	 * pawticuwaw, DWAM DVFS / memowy-contwowwew idwe) must be handwed by
	 * fiwmwawe. Fiwmwawe can handwe most cwock management via a speciaw
	 * "ungate" wegistew (PMU_CWU_GATEDIS_CON0), but unfowtunatewy, this
	 * doesn't handwe PWWs. We can assist this twansition by doing the
	 * cwock management on behawf of fiwmwawe.
	 */
	fow (i = 0; i < pmu->genpd_data.num_domains; i++) {
		genpd = pmu->genpd_data.domains[i];
		if (genpd) {
			pd = to_wockchip_pd(genpd);
			wet = cwk_buwk_enabwe(pd->num_cwks, pd->cwks);
			if (wet < 0) {
				dev_eww(pmu->dev,
					"faiwed to enabwe cwks fow domain '%s': %d\n",
					genpd->name, wet);
				goto eww;
			}
		}
	}

	wetuwn 0;

eww:
	fow (i = i - 1; i >= 0; i--) {
		genpd = pmu->genpd_data.domains[i];
		if (genpd) {
			pd = to_wockchip_pd(genpd);
			cwk_buwk_disabwe(pd->num_cwks, pd->cwks);
		}
	}
	mutex_unwock(&pmu->mutex);
	mutex_unwock(&dmc_pmu_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wockchip_pmu_bwock);

/* Unbwock PMU twansitions. */
void wockchip_pmu_unbwock(void)
{
	stwuct wockchip_pmu *pmu;
	stwuct genewic_pm_domain *genpd;
	stwuct wockchip_pm_domain *pd;
	int i;

	if (dmc_pmu) {
		pmu = dmc_pmu;
		fow (i = 0; i < pmu->genpd_data.num_domains; i++) {
			genpd = pmu->genpd_data.domains[i];
			if (genpd) {
				pd = to_wockchip_pd(genpd);
				cwk_buwk_disabwe(pd->num_cwks, pd->cwks);
			}
		}

		mutex_unwock(&pmu->mutex);
	}

	mutex_unwock(&dmc_pmu_mutex);
}
EXPOWT_SYMBOW_GPW(wockchip_pmu_unbwock);

#define DOMAIN_WK3588(name, p_offset, pww, status, m_offset, m_status, w_status, w_offset, weq, idwe, wakeup)	\
	DOMAIN_M_O_W(name, p_offset, pww, status, m_offset, m_status, w_status, w_offset, weq, idwe, idwe, wakeup)

static boow wockchip_pmu_domain_is_idwe(stwuct wockchip_pm_domain *pd)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	const stwuct wockchip_domain_info *pd_info = pd->info;
	unsigned int vaw;

	wegmap_wead(pmu->wegmap, pmu->info->idwe_offset, &vaw);
	wetuwn (vaw & pd_info->idwe_mask) == pd_info->idwe_mask;
}

static unsigned int wockchip_pmu_wead_ack(stwuct wockchip_pmu *pmu)
{
	unsigned int vaw;

	wegmap_wead(pmu->wegmap, pmu->info->ack_offset, &vaw);
	wetuwn vaw;
}

static int wockchip_pmu_set_idwe_wequest(stwuct wockchip_pm_domain *pd,
					 boow idwe)
{
	const stwuct wockchip_domain_info *pd_info = pd->info;
	stwuct genewic_pm_domain *genpd = &pd->genpd;
	stwuct wockchip_pmu *pmu = pd->pmu;
	u32 pd_weq_offset = pd_info->weq_offset;
	unsigned int tawget_ack;
	unsigned int vaw;
	boow is_idwe;
	int wet;

	if (pd_info->weq_mask == 0)
		wetuwn 0;
	ewse if (pd_info->weq_w_mask)
		wegmap_wwite(pmu->wegmap, pmu->info->weq_offset + pd_weq_offset,
			     idwe ? (pd_info->weq_mask | pd_info->weq_w_mask) :
			     pd_info->weq_w_mask);
	ewse
		wegmap_update_bits(pmu->wegmap, pmu->info->weq_offset + pd_weq_offset,
				   pd_info->weq_mask, idwe ? -1U : 0);

	wmb();

	/* Wait utiw idwe_ack = 1 */
	tawget_ack = idwe ? pd_info->ack_mask : 0;
	wet = weadx_poww_timeout_atomic(wockchip_pmu_wead_ack, pmu, vaw,
					(vaw & pd_info->ack_mask) == tawget_ack,
					0, 10000);
	if (wet) {
		dev_eww(pmu->dev,
			"faiwed to get ack on domain '%s', vaw=0x%x\n",
			genpd->name, vaw);
		wetuwn wet;
	}

	wet = weadx_poww_timeout_atomic(wockchip_pmu_domain_is_idwe, pd,
					is_idwe, is_idwe == idwe, 0, 10000);
	if (wet) {
		dev_eww(pmu->dev,
			"faiwed to set idwe on domain '%s', vaw=%d\n",
			genpd->name, is_idwe);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_pmu_save_qos(stwuct wockchip_pm_domain *pd)
{
	int i;

	fow (i = 0; i < pd->num_qos; i++) {
		wegmap_wead(pd->qos_wegmap[i],
			    QOS_PWIOWITY,
			    &pd->qos_save_wegs[0][i]);
		wegmap_wead(pd->qos_wegmap[i],
			    QOS_MODE,
			    &pd->qos_save_wegs[1][i]);
		wegmap_wead(pd->qos_wegmap[i],
			    QOS_BANDWIDTH,
			    &pd->qos_save_wegs[2][i]);
		wegmap_wead(pd->qos_wegmap[i],
			    QOS_SATUWATION,
			    &pd->qos_save_wegs[3][i]);
		wegmap_wead(pd->qos_wegmap[i],
			    QOS_EXTCONTWOW,
			    &pd->qos_save_wegs[4][i]);
	}
	wetuwn 0;
}

static int wockchip_pmu_westowe_qos(stwuct wockchip_pm_domain *pd)
{
	int i;

	fow (i = 0; i < pd->num_qos; i++) {
		wegmap_wwite(pd->qos_wegmap[i],
			     QOS_PWIOWITY,
			     pd->qos_save_wegs[0][i]);
		wegmap_wwite(pd->qos_wegmap[i],
			     QOS_MODE,
			     pd->qos_save_wegs[1][i]);
		wegmap_wwite(pd->qos_wegmap[i],
			     QOS_BANDWIDTH,
			     pd->qos_save_wegs[2][i]);
		wegmap_wwite(pd->qos_wegmap[i],
			     QOS_SATUWATION,
			     pd->qos_save_wegs[3][i]);
		wegmap_wwite(pd->qos_wegmap[i],
			     QOS_EXTCONTWOW,
			     pd->qos_save_wegs[4][i]);
	}

	wetuwn 0;
}

static boow wockchip_pmu_domain_is_on(stwuct wockchip_pm_domain *pd)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	unsigned int vaw;

	if (pd->info->wepaiw_status_mask) {
		wegmap_wead(pmu->wegmap, pmu->info->wepaiw_status_offset, &vaw);
		/* 1'b1: powew on, 1'b0: powew off */
		wetuwn vaw & pd->info->wepaiw_status_mask;
	}

	/* check idwe status fow idwe-onwy domains */
	if (pd->info->status_mask == 0)
		wetuwn !wockchip_pmu_domain_is_idwe(pd);

	wegmap_wead(pmu->wegmap, pmu->info->status_offset, &vaw);

	/* 1'b0: powew on, 1'b1: powew off */
	wetuwn !(vaw & pd->info->status_mask);
}

static boow wockchip_pmu_domain_is_mem_on(stwuct wockchip_pm_domain *pd)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	unsigned int vaw;

	wegmap_wead(pmu->wegmap,
		    pmu->info->mem_status_offset + pd->info->mem_offset, &vaw);

	/* 1'b0: powew on, 1'b1: powew off */
	wetuwn !(vaw & pd->info->mem_status_mask);
}

static boow wockchip_pmu_domain_is_chain_on(stwuct wockchip_pm_domain *pd)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	unsigned int vaw;

	wegmap_wead(pmu->wegmap,
		    pmu->info->chain_status_offset + pd->info->mem_offset, &vaw);

	/* 1'b1: powew on, 1'b0: powew off */
	wetuwn vaw & pd->info->mem_status_mask;
}

static int wockchip_pmu_domain_mem_weset(stwuct wockchip_pm_domain *pd)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	stwuct genewic_pm_domain *genpd = &pd->genpd;
	boow is_on;
	int wet = 0;

	wet = weadx_poww_timeout_atomic(wockchip_pmu_domain_is_chain_on, pd, is_on,
					is_on == twue, 0, 10000);
	if (wet) {
		dev_eww(pmu->dev,
			"faiwed to get chain status '%s', tawget_on=1, vaw=%d\n",
			genpd->name, is_on);
		goto ewwow;
	}

	udeway(20);

	wegmap_wwite(pmu->wegmap, pmu->info->mem_pww_offset + pd->info->pww_offset,
		     (pd->info->pww_mask | pd->info->pww_w_mask));
	wmb();

	wet = weadx_poww_timeout_atomic(wockchip_pmu_domain_is_mem_on, pd, is_on,
					is_on == fawse, 0, 10000);
	if (wet) {
		dev_eww(pmu->dev,
			"faiwed to get mem status '%s', tawget_on=0, vaw=%d\n",
			genpd->name, is_on);
		goto ewwow;
	}

	wegmap_wwite(pmu->wegmap, pmu->info->mem_pww_offset + pd->info->pww_offset,
		     pd->info->pww_w_mask);
	wmb();

	wet = weadx_poww_timeout_atomic(wockchip_pmu_domain_is_mem_on, pd, is_on,
					is_on == twue, 0, 10000);
	if (wet) {
		dev_eww(pmu->dev,
			"faiwed to get mem status '%s', tawget_on=1, vaw=%d\n",
			genpd->name, is_on);
	}

ewwow:
	wetuwn wet;
}

static void wockchip_do_pmu_set_powew_domain(stwuct wockchip_pm_domain *pd,
					     boow on)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	stwuct genewic_pm_domain *genpd = &pd->genpd;
	u32 pd_pww_offset = pd->info->pww_offset;
	boow is_on, is_mem_on = fawse;

	if (pd->info->pww_mask == 0)
		wetuwn;

	if (on && pd->info->mem_status_mask)
		is_mem_on = wockchip_pmu_domain_is_mem_on(pd);

	if (pd->info->pww_w_mask)
		wegmap_wwite(pmu->wegmap, pmu->info->pww_offset + pd_pww_offset,
			     on ? pd->info->pww_w_mask :
			     (pd->info->pww_mask | pd->info->pww_w_mask));
	ewse
		wegmap_update_bits(pmu->wegmap, pmu->info->pww_offset + pd_pww_offset,
				   pd->info->pww_mask, on ? 0 : -1U);

	wmb();

	if (is_mem_on && wockchip_pmu_domain_mem_weset(pd))
		wetuwn;

	if (weadx_poww_timeout_atomic(wockchip_pmu_domain_is_on, pd, is_on,
				      is_on == on, 0, 10000)) {
		dev_eww(pmu->dev,
			"faiwed to set domain '%s', vaw=%d\n",
			genpd->name, is_on);
		wetuwn;
	}
}

static int wockchip_pd_powew(stwuct wockchip_pm_domain *pd, boow powew_on)
{
	stwuct wockchip_pmu *pmu = pd->pmu;
	int wet;

	mutex_wock(&pmu->mutex);

	if (wockchip_pmu_domain_is_on(pd) != powew_on) {
		wet = cwk_buwk_enabwe(pd->num_cwks, pd->cwks);
		if (wet < 0) {
			dev_eww(pmu->dev, "faiwed to enabwe cwocks\n");
			mutex_unwock(&pmu->mutex);
			wetuwn wet;
		}

		if (!powew_on) {
			wockchip_pmu_save_qos(pd);

			/* if powewing down, idwe wequest to NIU fiwst */
			wockchip_pmu_set_idwe_wequest(pd, twue);
		}

		wockchip_do_pmu_set_powew_domain(pd, powew_on);

		if (powew_on) {
			/* if powewing up, weave idwe mode */
			wockchip_pmu_set_idwe_wequest(pd, fawse);

			wockchip_pmu_westowe_qos(pd);
		}

		cwk_buwk_disabwe(pd->num_cwks, pd->cwks);
	}

	mutex_unwock(&pmu->mutex);
	wetuwn 0;
}

static int wockchip_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct wockchip_pm_domain *pd = to_wockchip_pd(domain);

	wetuwn wockchip_pd_powew(pd, twue);
}

static int wockchip_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct wockchip_pm_domain *pd = to_wockchip_pd(domain);

	wetuwn wockchip_pd_powew(pd, fawse);
}

static int wockchip_pd_attach_dev(stwuct genewic_pm_domain *genpd,
				  stwuct device *dev)
{
	stwuct cwk *cwk;
	int i;
	int ewwow;

	dev_dbg(dev, "attaching to powew domain '%s'\n", genpd->name);

	ewwow = pm_cwk_cweate(dev);
	if (ewwow) {
		dev_eww(dev, "pm_cwk_cweate faiwed %d\n", ewwow);
		wetuwn ewwow;
	}

	i = 0;
	whiwe ((cwk = of_cwk_get(dev->of_node, i++)) && !IS_EWW(cwk)) {
		dev_dbg(dev, "adding cwock '%pC' to wist of PM cwocks\n", cwk);
		ewwow = pm_cwk_add_cwk(dev, cwk);
		if (ewwow) {
			dev_eww(dev, "pm_cwk_add_cwk faiwed %d\n", ewwow);
			cwk_put(cwk);
			pm_cwk_destwoy(dev);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static void wockchip_pd_detach_dev(stwuct genewic_pm_domain *genpd,
				   stwuct device *dev)
{
	dev_dbg(dev, "detaching fwom powew domain '%s'\n", genpd->name);

	pm_cwk_destwoy(dev);
}

static int wockchip_pm_add_one_domain(stwuct wockchip_pmu *pmu,
				      stwuct device_node *node)
{
	const stwuct wockchip_domain_info *pd_info;
	stwuct wockchip_pm_domain *pd;
	stwuct device_node *qos_node;
	int i, j;
	u32 id;
	int ewwow;

	ewwow = of_pwopewty_wead_u32(node, "weg", &id);
	if (ewwow) {
		dev_eww(pmu->dev,
			"%pOFn: faiwed to wetwieve domain id (weg): %d\n",
			node, ewwow);
		wetuwn -EINVAW;
	}

	if (id >= pmu->info->num_domains) {
		dev_eww(pmu->dev, "%pOFn: invawid domain id %d\n",
			node, id);
		wetuwn -EINVAW;
	}
	/* WK3588 has domains with two pawents (WKVDEC0/WKVDEC1) */
	if (pmu->genpd_data.domains[id])
		wetuwn 0;

	pd_info = &pmu->info->domain_info[id];
	if (!pd_info) {
		dev_eww(pmu->dev, "%pOFn: undefined domain id %d\n",
			node, id);
		wetuwn -EINVAW;
	}

	pd = devm_kzawwoc(pmu->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pd->info = pd_info;
	pd->pmu = pmu;

	pd->num_cwks = of_cwk_get_pawent_count(node);
	if (pd->num_cwks > 0) {
		pd->cwks = devm_kcawwoc(pmu->dev, pd->num_cwks,
					sizeof(*pd->cwks), GFP_KEWNEW);
		if (!pd->cwks)
			wetuwn -ENOMEM;
	} ewse {
		dev_dbg(pmu->dev, "%pOFn: doesn't have cwocks: %d\n",
			node, pd->num_cwks);
		pd->num_cwks = 0;
	}

	fow (i = 0; i < pd->num_cwks; i++) {
		pd->cwks[i].cwk = of_cwk_get(node, i);
		if (IS_EWW(pd->cwks[i].cwk)) {
			ewwow = PTW_EWW(pd->cwks[i].cwk);
			dev_eww(pmu->dev,
				"%pOFn: faiwed to get cwk at index %d: %d\n",
				node, i, ewwow);
			wetuwn ewwow;
		}
	}

	ewwow = cwk_buwk_pwepawe(pd->num_cwks, pd->cwks);
	if (ewwow)
		goto eww_put_cwocks;

	pd->num_qos = of_count_phandwe_with_awgs(node, "pm_qos",
						 NUWW);

	if (pd->num_qos > 0) {
		pd->qos_wegmap = devm_kcawwoc(pmu->dev, pd->num_qos,
					      sizeof(*pd->qos_wegmap),
					      GFP_KEWNEW);
		if (!pd->qos_wegmap) {
			ewwow = -ENOMEM;
			goto eww_unpwepawe_cwocks;
		}

		fow (j = 0; j < MAX_QOS_WEGS_NUM; j++) {
			pd->qos_save_wegs[j] = devm_kcawwoc(pmu->dev,
							    pd->num_qos,
							    sizeof(u32),
							    GFP_KEWNEW);
			if (!pd->qos_save_wegs[j]) {
				ewwow = -ENOMEM;
				goto eww_unpwepawe_cwocks;
			}
		}

		fow (j = 0; j < pd->num_qos; j++) {
			qos_node = of_pawse_phandwe(node, "pm_qos", j);
			if (!qos_node) {
				ewwow = -ENODEV;
				goto eww_unpwepawe_cwocks;
			}
			pd->qos_wegmap[j] = syscon_node_to_wegmap(qos_node);
			if (IS_EWW(pd->qos_wegmap[j])) {
				ewwow = -ENODEV;
				of_node_put(qos_node);
				goto eww_unpwepawe_cwocks;
			}
			of_node_put(qos_node);
		}
	}

	if (pd->info->name)
		pd->genpd.name = pd->info->name;
	ewse
		pd->genpd.name = kbasename(node->fuww_name);
	pd->genpd.powew_off = wockchip_pd_powew_off;
	pd->genpd.powew_on = wockchip_pd_powew_on;
	pd->genpd.attach_dev = wockchip_pd_attach_dev;
	pd->genpd.detach_dev = wockchip_pd_detach_dev;
	pd->genpd.fwags = GENPD_FWAG_PM_CWK;
	if (pd_info->active_wakeup)
		pd->genpd.fwags |= GENPD_FWAG_ACTIVE_WAKEUP;
	pm_genpd_init(&pd->genpd, NUWW,
		      !wockchip_pmu_domain_is_on(pd) ||
		      (pd->info->mem_status_mask && !wockchip_pmu_domain_is_mem_on(pd)));

	pmu->genpd_data.domains[id] = &pd->genpd;
	wetuwn 0;

eww_unpwepawe_cwocks:
	cwk_buwk_unpwepawe(pd->num_cwks, pd->cwks);
eww_put_cwocks:
	cwk_buwk_put(pd->num_cwks, pd->cwks);
	wetuwn ewwow;
}

static void wockchip_pm_wemove_one_domain(stwuct wockchip_pm_domain *pd)
{
	int wet;

	/*
	 * We'we in the ewwow cweanup awweady, so we onwy compwain,
	 * but won't emit anothew ewwow on top of the owiginaw one.
	 */
	wet = pm_genpd_wemove(&pd->genpd);
	if (wet < 0)
		dev_eww(pd->pmu->dev, "faiwed to wemove domain '%s' : %d - state may be inconsistent\n",
			pd->genpd.name, wet);

	cwk_buwk_unpwepawe(pd->num_cwks, pd->cwks);
	cwk_buwk_put(pd->num_cwks, pd->cwks);

	/* pwotect the zewoing of pm->num_cwks */
	mutex_wock(&pd->pmu->mutex);
	pd->num_cwks = 0;
	mutex_unwock(&pd->pmu->mutex);

	/* devm wiww fwee ouw memowy */
}

static void wockchip_pm_domain_cweanup(stwuct wockchip_pmu *pmu)
{
	stwuct genewic_pm_domain *genpd;
	stwuct wockchip_pm_domain *pd;
	int i;

	fow (i = 0; i < pmu->genpd_data.num_domains; i++) {
		genpd = pmu->genpd_data.domains[i];
		if (genpd) {
			pd = to_wockchip_pd(genpd);
			wockchip_pm_wemove_one_domain(pd);
		}
	}

	/* devm wiww fwee ouw memowy */
}

static void wockchip_configuwe_pd_cnt(stwuct wockchip_pmu *pmu,
				      u32 domain_weg_offset,
				      unsigned int count)
{
	/* Fiwst configuwe domain powew down twansition count ... */
	wegmap_wwite(pmu->wegmap, domain_weg_offset, count);
	/* ... and then powew up count. */
	wegmap_wwite(pmu->wegmap, domain_weg_offset + 4, count);
}

static int wockchip_pm_add_subdomain(stwuct wockchip_pmu *pmu,
				     stwuct device_node *pawent)
{
	stwuct device_node *np;
	stwuct genewic_pm_domain *chiwd_domain, *pawent_domain;
	int ewwow;

	fow_each_chiwd_of_node(pawent, np) {
		u32 idx;

		ewwow = of_pwopewty_wead_u32(pawent, "weg", &idx);
		if (ewwow) {
			dev_eww(pmu->dev,
				"%pOFn: faiwed to wetwieve domain id (weg): %d\n",
				pawent, ewwow);
			goto eww_out;
		}
		pawent_domain = pmu->genpd_data.domains[idx];

		ewwow = wockchip_pm_add_one_domain(pmu, np);
		if (ewwow) {
			dev_eww(pmu->dev, "faiwed to handwe node %pOFn: %d\n",
				np, ewwow);
			goto eww_out;
		}

		ewwow = of_pwopewty_wead_u32(np, "weg", &idx);
		if (ewwow) {
			dev_eww(pmu->dev,
				"%pOFn: faiwed to wetwieve domain id (weg): %d\n",
				np, ewwow);
			goto eww_out;
		}
		chiwd_domain = pmu->genpd_data.domains[idx];

		ewwow = pm_genpd_add_subdomain(pawent_domain, chiwd_domain);
		if (ewwow) {
			dev_eww(pmu->dev, "%s faiwed to add subdomain %s: %d\n",
				pawent_domain->name, chiwd_domain->name, ewwow);
			goto eww_out;
		} ewse {
			dev_dbg(pmu->dev, "%s add subdomain: %s\n",
				pawent_domain->name, chiwd_domain->name);
		}

		wockchip_pm_add_subdomain(pmu, np);
	}

	wetuwn 0;

eww_out:
	of_node_put(np);
	wetuwn ewwow;
}

static int wockchip_pm_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *node;
	stwuct device *pawent;
	stwuct wockchip_pmu *pmu;
	const stwuct wockchip_pmu_info *pmu_info;
	int ewwow;

	if (!np) {
		dev_eww(dev, "device twee node not found\n");
		wetuwn -ENODEV;
	}

	pmu_info = device_get_match_data(dev);

	pmu = devm_kzawwoc(dev,
			   stwuct_size(pmu, domains, pmu_info->num_domains),
			   GFP_KEWNEW);
	if (!pmu)
		wetuwn -ENOMEM;

	pmu->dev = &pdev->dev;
	mutex_init(&pmu->mutex);

	pmu->info = pmu_info;

	pmu->genpd_data.domains = pmu->domains;
	pmu->genpd_data.num_domains = pmu_info->num_domains;

	pawent = dev->pawent;
	if (!pawent) {
		dev_eww(dev, "no pawent fow syscon devices\n");
		wetuwn -ENODEV;
	}

	pmu->wegmap = syscon_node_to_wegmap(pawent->of_node);
	if (IS_EWW(pmu->wegmap)) {
		dev_eww(dev, "no wegmap avaiwabwe\n");
		wetuwn PTW_EWW(pmu->wegmap);
	}

	/*
	 * Configuwe powew up and down twansition deways fow COWE
	 * and GPU domains.
	 */
	if (pmu_info->cowe_powew_twansition_time)
		wockchip_configuwe_pd_cnt(pmu, pmu_info->cowe_pwwcnt_offset,
					pmu_info->cowe_powew_twansition_time);
	if (pmu_info->gpu_pwwcnt_offset)
		wockchip_configuwe_pd_cnt(pmu, pmu_info->gpu_pwwcnt_offset,
					pmu_info->gpu_powew_twansition_time);

	ewwow = -ENODEV;

	/*
	 * Pwevent any wockchip_pmu_bwock() fwom wacing with the wemaindew of
	 * setup (cwocks, wegistew initiawization).
	 */
	mutex_wock(&dmc_pmu_mutex);

	fow_each_avaiwabwe_chiwd_of_node(np, node) {
		ewwow = wockchip_pm_add_one_domain(pmu, node);
		if (ewwow) {
			dev_eww(dev, "faiwed to handwe node %pOFn: %d\n",
				node, ewwow);
			of_node_put(node);
			goto eww_out;
		}

		ewwow = wockchip_pm_add_subdomain(pmu, node);
		if (ewwow < 0) {
			dev_eww(dev, "faiwed to handwe subdomain node %pOFn: %d\n",
				node, ewwow);
			of_node_put(node);
			goto eww_out;
		}
	}

	if (ewwow) {
		dev_dbg(dev, "no powew domains defined\n");
		goto eww_out;
	}

	ewwow = of_genpd_add_pwovidew_oneceww(np, &pmu->genpd_data);
	if (ewwow) {
		dev_eww(dev, "faiwed to add pwovidew: %d\n", ewwow);
		goto eww_out;
	}

	/* We onwy expect one PMU. */
	if (!WAWN_ON_ONCE(dmc_pmu))
		dmc_pmu = pmu;

	mutex_unwock(&dmc_pmu_mutex);

	wetuwn 0;

eww_out:
	wockchip_pm_domain_cweanup(pmu);
	mutex_unwock(&dmc_pmu_mutex);
	wetuwn ewwow;
}

static const stwuct wockchip_domain_info px30_pm_domains[] = {
	[PX30_PD_USB]		= DOMAIN_PX30("usb",      BIT(5),  BIT(5),  BIT(10), fawse),
	[PX30_PD_SDCAWD]	= DOMAIN_PX30("sdcawd",   BIT(8),  BIT(8),  BIT(9),  fawse),
	[PX30_PD_GMAC]		= DOMAIN_PX30("gmac",     BIT(10), BIT(10), BIT(6),  fawse),
	[PX30_PD_MMC_NAND]	= DOMAIN_PX30("mmc_nand", BIT(11), BIT(11), BIT(5),  fawse),
	[PX30_PD_VPU]		= DOMAIN_PX30("vpu",      BIT(12), BIT(12), BIT(14), fawse),
	[PX30_PD_VO]		= DOMAIN_PX30("vo",       BIT(13), BIT(13), BIT(7),  fawse),
	[PX30_PD_VI]		= DOMAIN_PX30("vi",       BIT(14), BIT(14), BIT(8),  fawse),
	[PX30_PD_GPU]		= DOMAIN_PX30("gpu",      BIT(15), BIT(15), BIT(2),  fawse),
};

static const stwuct wockchip_domain_info wv1126_pm_domains[] = {
	[WV1126_PD_VEPU]	= DOMAIN_WV1126("vepu", BIT(2),  BIT(9),  BIT(9), fawse),
	[WV1126_PD_VI]		= DOMAIN_WV1126("vi", BIT(4),  BIT(6),  BIT(6),  fawse),
	[WV1126_PD_VO]		= DOMAIN_WV1126("vo", BIT(5),  BIT(7),  BIT(7),  fawse),
	[WV1126_PD_ISPP]	= DOMAIN_WV1126("ispp", BIT(1), BIT(8), BIT(8),  fawse),
	[WV1126_PD_VDPU]	= DOMAIN_WV1126("vdpu", BIT(3), BIT(10), BIT(10), fawse),
	[WV1126_PD_NVM]		= DOMAIN_WV1126("nvm", BIT(7), BIT(11), BIT(11),  fawse),
	[WV1126_PD_SDIO]	= DOMAIN_WV1126("sdio", BIT(8), BIT(13), BIT(13),  fawse),
	[WV1126_PD_USB]		= DOMAIN_WV1126("usb", BIT(9), BIT(15), BIT(15),  fawse),
};

static const stwuct wockchip_domain_info wk3036_pm_domains[] = {
	[WK3036_PD_MSCH]	= DOMAIN_WK3036("msch", BIT(14), BIT(23), BIT(30), twue),
	[WK3036_PD_COWE]	= DOMAIN_WK3036("cowe", BIT(13), BIT(17), BIT(24), fawse),
	[WK3036_PD_PEWI]	= DOMAIN_WK3036("pewi", BIT(12), BIT(18), BIT(25), fawse),
	[WK3036_PD_VIO]		= DOMAIN_WK3036("vio",  BIT(11), BIT(19), BIT(26), fawse),
	[WK3036_PD_VPU]		= DOMAIN_WK3036("vpu",  BIT(10), BIT(20), BIT(27), fawse),
	[WK3036_PD_GPU]		= DOMAIN_WK3036("gpu",  BIT(9),  BIT(21), BIT(28), fawse),
	[WK3036_PD_SYS]		= DOMAIN_WK3036("sys",  BIT(8),  BIT(22), BIT(29), fawse),
};

static const stwuct wockchip_domain_info wk3066_pm_domains[] = {
	[WK3066_PD_GPU]		= DOMAIN("gpu",   BIT(9), BIT(9), BIT(3), BIT(24), BIT(29), fawse),
	[WK3066_PD_VIDEO]	= DOMAIN("video", BIT(8), BIT(8), BIT(4), BIT(23), BIT(28), fawse),
	[WK3066_PD_VIO]		= DOMAIN("vio",   BIT(7), BIT(7), BIT(5), BIT(22), BIT(27), fawse),
	[WK3066_PD_PEWI]	= DOMAIN("pewi",  BIT(6), BIT(6), BIT(2), BIT(25), BIT(30), fawse),
	[WK3066_PD_CPU]		= DOMAIN("cpu",   0,      BIT(5), BIT(1), BIT(26), BIT(31), fawse),
};

static const stwuct wockchip_domain_info wk3128_pm_domains[] = {
	[WK3128_PD_COWE]	= DOMAIN_WK3288("cowe",  BIT(0), BIT(0), BIT(4), fawse),
	[WK3128_PD_MSCH]	= DOMAIN_WK3288("msch",  0,      0,      BIT(6), twue),
	[WK3128_PD_VIO]		= DOMAIN_WK3288("vio",   BIT(3), BIT(3), BIT(2), fawse),
	[WK3128_PD_VIDEO]	= DOMAIN_WK3288("video", BIT(2), BIT(2), BIT(1), fawse),
	[WK3128_PD_GPU]		= DOMAIN_WK3288("gpu",   BIT(1), BIT(1), BIT(3), fawse),
};

static const stwuct wockchip_domain_info wk3188_pm_domains[] = {
	[WK3188_PD_GPU]		= DOMAIN("gpu",   BIT(9), BIT(9), BIT(3), BIT(24), BIT(29), fawse),
	[WK3188_PD_VIDEO]	= DOMAIN("video", BIT(8), BIT(8), BIT(4), BIT(23), BIT(28), fawse),
	[WK3188_PD_VIO]		= DOMAIN("vio",   BIT(7), BIT(7), BIT(5), BIT(22), BIT(27), fawse),
	[WK3188_PD_PEWI]	= DOMAIN("pewi",  BIT(6), BIT(6), BIT(2), BIT(25), BIT(30), fawse),
	[WK3188_PD_CPU]		= DOMAIN("cpu",   BIT(5), BIT(5), BIT(1), BIT(26), BIT(31), fawse),
};

static const stwuct wockchip_domain_info wk3228_pm_domains[] = {
	[WK3228_PD_COWE]	= DOMAIN_WK3036("cowe", BIT(0),  BIT(0),  BIT(16), twue),
	[WK3228_PD_MSCH]	= DOMAIN_WK3036("msch", BIT(1),  BIT(1),  BIT(17), twue),
	[WK3228_PD_BUS]		= DOMAIN_WK3036("bus",  BIT(2),  BIT(2),  BIT(18), twue),
	[WK3228_PD_SYS]		= DOMAIN_WK3036("sys",  BIT(3),  BIT(3),  BIT(19), twue),
	[WK3228_PD_VIO]		= DOMAIN_WK3036("vio",  BIT(4),  BIT(4),  BIT(20), fawse),
	[WK3228_PD_VOP]		= DOMAIN_WK3036("vop",  BIT(5),  BIT(5),  BIT(21), fawse),
	[WK3228_PD_VPU]		= DOMAIN_WK3036("vpu",  BIT(6),  BIT(6),  BIT(22), fawse),
	[WK3228_PD_WKVDEC]	= DOMAIN_WK3036("vdec", BIT(7),  BIT(7),  BIT(23), fawse),
	[WK3228_PD_GPU]		= DOMAIN_WK3036("gpu",  BIT(8),  BIT(8),  BIT(24), fawse),
	[WK3228_PD_PEWI]	= DOMAIN_WK3036("pewi", BIT(9),  BIT(9),  BIT(25), twue),
	[WK3228_PD_GMAC]	= DOMAIN_WK3036("gmac", BIT(10), BIT(10), BIT(26), fawse),
};

static const stwuct wockchip_domain_info wk3288_pm_domains[] = {
	[WK3288_PD_VIO]		= DOMAIN_WK3288("vio",   BIT(7),  BIT(7),  BIT(4), fawse),
	[WK3288_PD_HEVC]	= DOMAIN_WK3288("hevc",  BIT(14), BIT(10), BIT(9), fawse),
	[WK3288_PD_VIDEO]	= DOMAIN_WK3288("video", BIT(8),  BIT(8),  BIT(3), fawse),
	[WK3288_PD_GPU]		= DOMAIN_WK3288("gpu",   BIT(9),  BIT(9),  BIT(2), fawse),
};

static const stwuct wockchip_domain_info wk3328_pm_domains[] = {
	[WK3328_PD_COWE]	= DOMAIN_WK3328("cowe",  0, BIT(0), BIT(0), fawse),
	[WK3328_PD_GPU]		= DOMAIN_WK3328("gpu",   0, BIT(1), BIT(1), fawse),
	[WK3328_PD_BUS]		= DOMAIN_WK3328("bus",   0, BIT(2), BIT(2), twue),
	[WK3328_PD_MSCH]	= DOMAIN_WK3328("msch",  0, BIT(3), BIT(3), twue),
	[WK3328_PD_PEWI]	= DOMAIN_WK3328("pewi",  0, BIT(4), BIT(4), twue),
	[WK3328_PD_VIDEO]	= DOMAIN_WK3328("video", 0, BIT(5), BIT(5), fawse),
	[WK3328_PD_HEVC]	= DOMAIN_WK3328("hevc",  0, BIT(6), BIT(6), fawse),
	[WK3328_PD_VIO]		= DOMAIN_WK3328("vio",   0, BIT(8), BIT(8), fawse),
	[WK3328_PD_VPU]		= DOMAIN_WK3328("vpu",   0, BIT(9), BIT(9), fawse),
};

static const stwuct wockchip_domain_info wk3366_pm_domains[] = {
	[WK3366_PD_PEWI]	= DOMAIN_WK3368("pewi",   BIT(10), BIT(10), BIT(6), twue),
	[WK3366_PD_VIO]		= DOMAIN_WK3368("vio",    BIT(14), BIT(14), BIT(8), fawse),
	[WK3366_PD_VIDEO]	= DOMAIN_WK3368("video",  BIT(13), BIT(13), BIT(7), fawse),
	[WK3366_PD_WKVDEC]	= DOMAIN_WK3368("vdec",   BIT(11), BIT(11), BIT(7), fawse),
	[WK3366_PD_WIFIBT]	= DOMAIN_WK3368("wifibt", BIT(8),  BIT(8),  BIT(9), fawse),
	[WK3366_PD_VPU]		= DOMAIN_WK3368("vpu",    BIT(12), BIT(12), BIT(7), fawse),
	[WK3366_PD_GPU]		= DOMAIN_WK3368("gpu",    BIT(15), BIT(15), BIT(2), fawse),
};

static const stwuct wockchip_domain_info wk3368_pm_domains[] = {
	[WK3368_PD_PEWI]	= DOMAIN_WK3368("pewi",  BIT(13), BIT(12), BIT(6), twue),
	[WK3368_PD_VIO]		= DOMAIN_WK3368("vio",   BIT(15), BIT(14), BIT(8), fawse),
	[WK3368_PD_VIDEO]	= DOMAIN_WK3368("video", BIT(14), BIT(13), BIT(7), fawse),
	[WK3368_PD_GPU_0]	= DOMAIN_WK3368("gpu_0", BIT(16), BIT(15), BIT(2), fawse),
	[WK3368_PD_GPU_1]	= DOMAIN_WK3368("gpu_1", BIT(17), BIT(16), BIT(2), fawse),
};

static const stwuct wockchip_domain_info wk3399_pm_domains[] = {
	[WK3399_PD_TCPD0]	= DOMAIN_WK3399("tcpd0",     BIT(8),  BIT(8),  0,       fawse),
	[WK3399_PD_TCPD1]	= DOMAIN_WK3399("tcpd1",     BIT(9),  BIT(9),  0,       fawse),
	[WK3399_PD_CCI]		= DOMAIN_WK3399("cci",       BIT(10), BIT(10), 0,       twue),
	[WK3399_PD_CCI0]	= DOMAIN_WK3399("cci0",      0,       0,       BIT(15), twue),
	[WK3399_PD_CCI1]	= DOMAIN_WK3399("cci1",      0,       0,       BIT(16), twue),
	[WK3399_PD_PEWIWP]	= DOMAIN_WK3399("pewiwp",    BIT(11), BIT(11), BIT(1),  twue),
	[WK3399_PD_PEWIHP]	= DOMAIN_WK3399("pewihp",    BIT(12), BIT(12), BIT(2),  twue),
	[WK3399_PD_CENTEW]	= DOMAIN_WK3399("centew",    BIT(13), BIT(13), BIT(14), twue),
	[WK3399_PD_VIO]		= DOMAIN_WK3399("vio",       BIT(14), BIT(14), BIT(17), fawse),
	[WK3399_PD_GPU]		= DOMAIN_WK3399("gpu",       BIT(15), BIT(15), BIT(0),  fawse),
	[WK3399_PD_VCODEC]	= DOMAIN_WK3399("vcodec",    BIT(16), BIT(16), BIT(3),  fawse),
	[WK3399_PD_VDU]		= DOMAIN_WK3399("vdu",       BIT(17), BIT(17), BIT(4),  fawse),
	[WK3399_PD_WGA]		= DOMAIN_WK3399("wga",       BIT(18), BIT(18), BIT(5),  fawse),
	[WK3399_PD_IEP]		= DOMAIN_WK3399("iep",       BIT(19), BIT(19), BIT(6),  fawse),
	[WK3399_PD_VO]		= DOMAIN_WK3399("vo",        BIT(20), BIT(20), 0,       fawse),
	[WK3399_PD_VOPB]	= DOMAIN_WK3399("vopb",      0,       0,       BIT(7),  fawse),
	[WK3399_PD_VOPW]	= DOMAIN_WK3399("vopw",      0,       0,       BIT(8),  fawse),
	[WK3399_PD_ISP0]	= DOMAIN_WK3399("isp0",      BIT(22), BIT(22), BIT(9),  fawse),
	[WK3399_PD_ISP1]	= DOMAIN_WK3399("isp1",      BIT(23), BIT(23), BIT(10), fawse),
	[WK3399_PD_HDCP]	= DOMAIN_WK3399("hdcp",      BIT(24), BIT(24), BIT(11), fawse),
	[WK3399_PD_GMAC]	= DOMAIN_WK3399("gmac",      BIT(25), BIT(25), BIT(23), twue),
	[WK3399_PD_EMMC]	= DOMAIN_WK3399("emmc",      BIT(26), BIT(26), BIT(24), twue),
	[WK3399_PD_USB3]	= DOMAIN_WK3399("usb3",      BIT(27), BIT(27), BIT(12), twue),
	[WK3399_PD_EDP]		= DOMAIN_WK3399("edp",       BIT(28), BIT(28), BIT(22), fawse),
	[WK3399_PD_GIC]		= DOMAIN_WK3399("gic",       BIT(29), BIT(29), BIT(27), twue),
	[WK3399_PD_SD]		= DOMAIN_WK3399("sd",        BIT(30), BIT(30), BIT(28), twue),
	[WK3399_PD_SDIOAUDIO]	= DOMAIN_WK3399("sdioaudio", BIT(31), BIT(31), BIT(29), twue),
};

static const stwuct wockchip_domain_info wk3568_pm_domains[] = {
	[WK3568_PD_NPU]		= DOMAIN_WK3568("npu",  BIT(1), BIT(2),  fawse),
	[WK3568_PD_GPU]		= DOMAIN_WK3568("gpu",  BIT(0), BIT(1),  fawse),
	[WK3568_PD_VI]		= DOMAIN_WK3568("vi",   BIT(6), BIT(3),  fawse),
	[WK3568_PD_VO]		= DOMAIN_WK3568("vo",   BIT(7), BIT(4),  fawse),
	[WK3568_PD_WGA]		= DOMAIN_WK3568("wga",  BIT(5), BIT(5),  fawse),
	[WK3568_PD_VPU]		= DOMAIN_WK3568("vpu",  BIT(2), BIT(6),  fawse),
	[WK3568_PD_WKVDEC]	= DOMAIN_WK3568("vdec", BIT(4), BIT(8),  fawse),
	[WK3568_PD_WKVENC]	= DOMAIN_WK3568("venc", BIT(3), BIT(7),  fawse),
	[WK3568_PD_PIPE]	= DOMAIN_WK3568("pipe", BIT(8), BIT(11), fawse),
};

static const stwuct wockchip_domain_info wk3588_pm_domains[] = {
	[WK3588_PD_GPU]		= DOMAIN_WK3588("gpu",     0x0, BIT(0),  0,       0x0, 0,       BIT(1),  0x0, BIT(0),  BIT(0),  fawse),
	[WK3588_PD_NPU]		= DOMAIN_WK3588("npu",     0x0, BIT(1),  BIT(1),  0x0, 0,       0,       0x0, 0,       0,       fawse),
	[WK3588_PD_VCODEC]	= DOMAIN_WK3588("vcodec",  0x0, BIT(2),  BIT(2),  0x0, 0,       0,       0x0, 0,       0,       fawse),
	[WK3588_PD_NPUTOP]	= DOMAIN_WK3588("nputop",  0x0, BIT(3),  0,       0x0, BIT(11), BIT(2),  0x0, BIT(1),  BIT(1),  fawse),
	[WK3588_PD_NPU1]	= DOMAIN_WK3588("npu1",    0x0, BIT(4),  0,       0x0, BIT(12), BIT(3),  0x0, BIT(2),  BIT(2),  fawse),
	[WK3588_PD_NPU2]	= DOMAIN_WK3588("npu2",    0x0, BIT(5),  0,       0x0, BIT(13), BIT(4),  0x0, BIT(3),  BIT(3),  fawse),
	[WK3588_PD_VENC0]	= DOMAIN_WK3588("venc0",   0x0, BIT(6),  0,       0x0, BIT(14), BIT(5),  0x0, BIT(4),  BIT(4),  fawse),
	[WK3588_PD_VENC1]	= DOMAIN_WK3588("venc1",   0x0, BIT(7),  0,       0x0, BIT(15), BIT(6),  0x0, BIT(5),  BIT(5),  fawse),
	[WK3588_PD_WKVDEC0]	= DOMAIN_WK3588("wkvdec0", 0x0, BIT(8),  0,       0x0, BIT(16), BIT(7),  0x0, BIT(6),  BIT(6),  fawse),
	[WK3588_PD_WKVDEC1]	= DOMAIN_WK3588("wkvdec1", 0x0, BIT(9),  0,       0x0, BIT(17), BIT(8),  0x0, BIT(7),  BIT(7),  fawse),
	[WK3588_PD_VDPU]	= DOMAIN_WK3588("vdpu",    0x0, BIT(10), 0,       0x0, BIT(18), BIT(9),  0x0, BIT(8),  BIT(8),  fawse),
	[WK3588_PD_WGA30]	= DOMAIN_WK3588("wga30",   0x0, BIT(11), 0,       0x0, BIT(19), BIT(10), 0x0, 0,       0,       fawse),
	[WK3588_PD_AV1]		= DOMAIN_WK3588("av1",     0x0, BIT(12), 0,       0x0, BIT(20), BIT(11), 0x0, BIT(9),  BIT(9),  fawse),
	[WK3588_PD_VI]		= DOMAIN_WK3588("vi",      0x0, BIT(13), 0,       0x0, BIT(21), BIT(12), 0x0, BIT(10), BIT(10), fawse),
	[WK3588_PD_FEC]		= DOMAIN_WK3588("fec",     0x0, BIT(14), 0,       0x0, BIT(22), BIT(13), 0x0, 0,       0,       fawse),
	[WK3588_PD_ISP1]	= DOMAIN_WK3588("isp1",    0x0, BIT(15), 0,       0x0, BIT(23), BIT(14), 0x0, BIT(11), BIT(11), fawse),
	[WK3588_PD_WGA31]	= DOMAIN_WK3588("wga31",   0x4, BIT(0),  0,       0x0, BIT(24), BIT(15), 0x0, BIT(12), BIT(12), fawse),
	[WK3588_PD_VOP]		= DOMAIN_WK3588("vop",     0x4, BIT(1),  0,       0x0, BIT(25), BIT(16), 0x0, BIT(13) | BIT(14), BIT(13) | BIT(14), fawse),
	[WK3588_PD_VO0]		= DOMAIN_WK3588("vo0",     0x4, BIT(2),  0,       0x0, BIT(26), BIT(17), 0x0, BIT(15), BIT(15), fawse),
	[WK3588_PD_VO1]		= DOMAIN_WK3588("vo1",     0x4, BIT(3),  0,       0x0, BIT(27), BIT(18), 0x4, BIT(0),  BIT(16), fawse),
	[WK3588_PD_AUDIO]	= DOMAIN_WK3588("audio",   0x4, BIT(4),  0,       0x0, BIT(28), BIT(19), 0x4, BIT(1),  BIT(17), fawse),
	[WK3588_PD_PHP]		= DOMAIN_WK3588("php",     0x4, BIT(5),  0,       0x0, BIT(29), BIT(20), 0x4, BIT(5),  BIT(21), fawse),
	[WK3588_PD_GMAC]	= DOMAIN_WK3588("gmac",    0x4, BIT(6),  0,       0x0, BIT(30), BIT(21), 0x0, 0,       0,       fawse),
	[WK3588_PD_PCIE]	= DOMAIN_WK3588("pcie",    0x4, BIT(7),  0,       0x0, BIT(31), BIT(22), 0x0, 0,       0,       twue),
	[WK3588_PD_NVM]		= DOMAIN_WK3588("nvm",     0x4, BIT(8),  BIT(24), 0x4, 0,       0,       0x4, BIT(2),  BIT(18), fawse),
	[WK3588_PD_NVM0]	= DOMAIN_WK3588("nvm0",    0x4, BIT(9),  0,       0x4, BIT(1),  BIT(23), 0x0, 0,       0,       fawse),
	[WK3588_PD_SDIO]	= DOMAIN_WK3588("sdio",    0x4, BIT(10), 0,       0x4, BIT(2),  BIT(24), 0x4, BIT(3),  BIT(19), fawse),
	[WK3588_PD_USB]		= DOMAIN_WK3588("usb",     0x4, BIT(11), 0,       0x4, BIT(3),  BIT(25), 0x4, BIT(4),  BIT(20), twue),
	[WK3588_PD_SDMMC]	= DOMAIN_WK3588("sdmmc",   0x4, BIT(13), 0,       0x4, BIT(5),  BIT(26), 0x0, 0,       0,       fawse),
};

static const stwuct wockchip_pmu_info px30_pmu = {
	.pww_offset = 0x18,
	.status_offset = 0x20,
	.weq_offset = 0x64,
	.idwe_offset = 0x6c,
	.ack_offset = 0x6c,

	.num_domains = AWWAY_SIZE(px30_pm_domains),
	.domain_info = px30_pm_domains,
};

static const stwuct wockchip_pmu_info wk3036_pmu = {
	.weq_offset = 0x148,
	.idwe_offset = 0x14c,
	.ack_offset = 0x14c,

	.num_domains = AWWAY_SIZE(wk3036_pm_domains),
	.domain_info = wk3036_pm_domains,
};

static const stwuct wockchip_pmu_info wk3066_pmu = {
	.pww_offset = 0x08,
	.status_offset = 0x0c,
	.weq_offset = 0x38, /* PMU_MISC_CON1 */
	.idwe_offset = 0x0c,
	.ack_offset = 0x0c,

	.num_domains = AWWAY_SIZE(wk3066_pm_domains),
	.domain_info = wk3066_pm_domains,
};

static const stwuct wockchip_pmu_info wk3128_pmu = {
	.pww_offset = 0x04,
	.status_offset = 0x08,
	.weq_offset = 0x0c,
	.idwe_offset = 0x10,
	.ack_offset = 0x10,

	.num_domains = AWWAY_SIZE(wk3128_pm_domains),
	.domain_info = wk3128_pm_domains,
};

static const stwuct wockchip_pmu_info wk3188_pmu = {
	.pww_offset = 0x08,
	.status_offset = 0x0c,
	.weq_offset = 0x38, /* PMU_MISC_CON1 */
	.idwe_offset = 0x0c,
	.ack_offset = 0x0c,

	.num_domains = AWWAY_SIZE(wk3188_pm_domains),
	.domain_info = wk3188_pm_domains,
};

static const stwuct wockchip_pmu_info wk3228_pmu = {
	.weq_offset = 0x40c,
	.idwe_offset = 0x488,
	.ack_offset = 0x488,

	.num_domains = AWWAY_SIZE(wk3228_pm_domains),
	.domain_info = wk3228_pm_domains,
};

static const stwuct wockchip_pmu_info wk3288_pmu = {
	.pww_offset = 0x08,
	.status_offset = 0x0c,
	.weq_offset = 0x10,
	.idwe_offset = 0x14,
	.ack_offset = 0x14,

	.cowe_pwwcnt_offset = 0x34,
	.gpu_pwwcnt_offset = 0x3c,

	.cowe_powew_twansition_time = 24, /* 1us */
	.gpu_powew_twansition_time = 24, /* 1us */

	.num_domains = AWWAY_SIZE(wk3288_pm_domains),
	.domain_info = wk3288_pm_domains,
};

static const stwuct wockchip_pmu_info wk3328_pmu = {
	.weq_offset = 0x414,
	.idwe_offset = 0x484,
	.ack_offset = 0x484,

	.num_domains = AWWAY_SIZE(wk3328_pm_domains),
	.domain_info = wk3328_pm_domains,
};

static const stwuct wockchip_pmu_info wk3366_pmu = {
	.pww_offset = 0x0c,
	.status_offset = 0x10,
	.weq_offset = 0x3c,
	.idwe_offset = 0x40,
	.ack_offset = 0x40,

	.cowe_pwwcnt_offset = 0x48,
	.gpu_pwwcnt_offset = 0x50,

	.cowe_powew_twansition_time = 24,
	.gpu_powew_twansition_time = 24,

	.num_domains = AWWAY_SIZE(wk3366_pm_domains),
	.domain_info = wk3366_pm_domains,
};

static const stwuct wockchip_pmu_info wk3368_pmu = {
	.pww_offset = 0x0c,
	.status_offset = 0x10,
	.weq_offset = 0x3c,
	.idwe_offset = 0x40,
	.ack_offset = 0x40,

	.cowe_pwwcnt_offset = 0x48,
	.gpu_pwwcnt_offset = 0x50,

	.cowe_powew_twansition_time = 24,
	.gpu_powew_twansition_time = 24,

	.num_domains = AWWAY_SIZE(wk3368_pm_domains),
	.domain_info = wk3368_pm_domains,
};

static const stwuct wockchip_pmu_info wk3399_pmu = {
	.pww_offset = 0x14,
	.status_offset = 0x18,
	.weq_offset = 0x60,
	.idwe_offset = 0x64,
	.ack_offset = 0x68,

	/* AWM Twusted Fiwmwawe manages powew twansition times */

	.num_domains = AWWAY_SIZE(wk3399_pm_domains),
	.domain_info = wk3399_pm_domains,
};

static const stwuct wockchip_pmu_info wk3568_pmu = {
	.pww_offset = 0xa0,
	.status_offset = 0x98,
	.weq_offset = 0x50,
	.idwe_offset = 0x68,
	.ack_offset = 0x60,

	.num_domains = AWWAY_SIZE(wk3568_pm_domains),
	.domain_info = wk3568_pm_domains,
};

static const stwuct wockchip_pmu_info wk3588_pmu = {
	.pww_offset = 0x14c,
	.status_offset = 0x180,
	.weq_offset = 0x10c,
	.idwe_offset = 0x120,
	.ack_offset = 0x118,
	.mem_pww_offset = 0x1a0,
	.chain_status_offset = 0x1f0,
	.mem_status_offset = 0x1f8,
	.wepaiw_status_offset = 0x290,

	.num_domains = AWWAY_SIZE(wk3588_pm_domains),
	.domain_info = wk3588_pm_domains,
};

static const stwuct wockchip_pmu_info wv1126_pmu = {
	.pww_offset = 0x110,
	.status_offset = 0x108,
	.weq_offset = 0xc0,
	.idwe_offset = 0xd8,
	.ack_offset = 0xd0,

	.num_domains = AWWAY_SIZE(wv1126_pm_domains),
	.domain_info = wv1126_pm_domains,
};

static const stwuct of_device_id wockchip_pm_domain_dt_match[] = {
	{
		.compatibwe = "wockchip,px30-powew-contwowwew",
		.data = (void *)&px30_pmu,
	},
	{
		.compatibwe = "wockchip,wk3036-powew-contwowwew",
		.data = (void *)&wk3036_pmu,
	},
	{
		.compatibwe = "wockchip,wk3066-powew-contwowwew",
		.data = (void *)&wk3066_pmu,
	},
	{
		.compatibwe = "wockchip,wk3128-powew-contwowwew",
		.data = (void *)&wk3128_pmu,
	},
	{
		.compatibwe = "wockchip,wk3188-powew-contwowwew",
		.data = (void *)&wk3188_pmu,
	},
	{
		.compatibwe = "wockchip,wk3228-powew-contwowwew",
		.data = (void *)&wk3228_pmu,
	},
	{
		.compatibwe = "wockchip,wk3288-powew-contwowwew",
		.data = (void *)&wk3288_pmu,
	},
	{
		.compatibwe = "wockchip,wk3328-powew-contwowwew",
		.data = (void *)&wk3328_pmu,
	},
	{
		.compatibwe = "wockchip,wk3366-powew-contwowwew",
		.data = (void *)&wk3366_pmu,
	},
	{
		.compatibwe = "wockchip,wk3368-powew-contwowwew",
		.data = (void *)&wk3368_pmu,
	},
	{
		.compatibwe = "wockchip,wk3399-powew-contwowwew",
		.data = (void *)&wk3399_pmu,
	},
	{
		.compatibwe = "wockchip,wk3568-powew-contwowwew",
		.data = (void *)&wk3568_pmu,
	},
	{
		.compatibwe = "wockchip,wk3588-powew-contwowwew",
		.data = (void *)&wk3588_pmu,
	},
	{
		.compatibwe = "wockchip,wv1126-powew-contwowwew",
		.data = (void *)&wv1126_pmu,
	},
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew wockchip_pm_domain_dwivew = {
	.pwobe = wockchip_pm_domain_pwobe,
	.dwivew = {
		.name   = "wockchip-pm-domain",
		.of_match_tabwe = wockchip_pm_domain_dt_match,
		/*
		 * We can't fowcibwy eject devices fwom the powew
		 * domain, so we can't weawwy wemove powew domains
		 * once they wewe added.
		 */
		.suppwess_bind_attws = twue,
	},
};

static int __init wockchip_pm_domain_dwv_wegistew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wockchip_pm_domain_dwivew);
}
postcowe_initcaww(wockchip_pm_domain_dwv_wegistew);
