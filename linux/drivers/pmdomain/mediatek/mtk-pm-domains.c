// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Cowwabowa Wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/soc/mediatek/infwacfg.h>

#incwude "mt6795-pm-domains.h"
#incwude "mt8167-pm-domains.h"
#incwude "mt8173-pm-domains.h"
#incwude "mt8183-pm-domains.h"
#incwude "mt8186-pm-domains.h"
#incwude "mt8188-pm-domains.h"
#incwude "mt8192-pm-domains.h"
#incwude "mt8195-pm-domains.h"
#incwude "mt8365-pm-domains.h"

#define MTK_POWW_DEWAY_US		10
#define MTK_POWW_TIMEOUT		USEC_PEW_SEC

#define PWW_WST_B_BIT			BIT(0)
#define PWW_ISO_BIT			BIT(1)
#define PWW_ON_BIT			BIT(2)
#define PWW_ON_2ND_BIT			BIT(3)
#define PWW_CWK_DIS_BIT			BIT(4)
#define PWW_SWAM_CWKISO_BIT		BIT(5)
#define PWW_SWAM_ISOINT_B_BIT		BIT(6)

stwuct scpsys_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct scpsys_domain_data *data;
	stwuct scpsys *scpsys;
	int num_cwks;
	stwuct cwk_buwk_data *cwks;
	int num_subsys_cwks;
	stwuct cwk_buwk_data *subsys_cwks;
	stwuct wegmap *infwacfg_nao;
	stwuct wegmap *infwacfg;
	stwuct wegmap *smi;
	stwuct weguwatow *suppwy;
};

stwuct scpsys {
	stwuct device *dev;
	stwuct wegmap *base;
	const stwuct scpsys_soc_data *soc_data;
	stwuct genpd_oneceww_data pd_data;
	stwuct genewic_pm_domain *domains[];
};

#define to_scpsys_domain(gpd) containew_of(gpd, stwuct scpsys_domain, genpd)

static boow scpsys_domain_is_on(stwuct scpsys_domain *pd)
{
	stwuct scpsys *scpsys = pd->scpsys;
	u32 status, status2;

	wegmap_wead(scpsys->base, pd->data->pww_sta_offs, &status);
	status &= pd->data->sta_mask;

	wegmap_wead(scpsys->base, pd->data->pww_sta2nd_offs, &status2);
	status2 &= pd->data->sta_mask;

	/* A domain is on when both status bits awe set. */
	wetuwn status && status2;
}

static int scpsys_swam_enabwe(stwuct scpsys_domain *pd)
{
	u32 pdn_ack = pd->data->swam_pdn_ack_bits;
	stwuct scpsys *scpsys = pd->scpsys;
	unsigned int tmp;
	int wet;

	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, pd->data->swam_pdn_bits);

	/* Eithew wait untiw SWAM_PDN_ACK aww 1 ow 0 */
	wet = wegmap_wead_poww_timeout(scpsys->base, pd->data->ctw_offs, tmp,
				       (tmp & pdn_ack) == 0, MTK_POWW_DEWAY_US, MTK_POWW_TIMEOUT);
	if (wet < 0)
		wetuwn wet;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_SWAM_ISO)) {
		wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_SWAM_ISOINT_B_BIT);
		udeway(1);
		wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_SWAM_CWKISO_BIT);
	}

	wetuwn 0;
}

static int scpsys_swam_disabwe(stwuct scpsys_domain *pd)
{
	u32 pdn_ack = pd->data->swam_pdn_ack_bits;
	stwuct scpsys *scpsys = pd->scpsys;
	unsigned int tmp;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_SWAM_ISO)) {
		wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_SWAM_CWKISO_BIT);
		udeway(1);
		wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_SWAM_ISOINT_B_BIT);
	}

	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, pd->data->swam_pdn_bits);

	/* Eithew wait untiw SWAM_PDN_ACK aww 1 ow 0 */
	wetuwn wegmap_wead_poww_timeout(scpsys->base, pd->data->ctw_offs, tmp,
					(tmp & pdn_ack) == pdn_ack, MTK_POWW_DEWAY_US,
					MTK_POWW_TIMEOUT);
}

static stwuct wegmap *scpsys_bus_pwotect_get_wegmap(stwuct scpsys_domain *pd,
						    const stwuct scpsys_bus_pwot_data *bpd)
{
	if (bpd->fwags & BUS_PWOT_COMPONENT_SMI)
		wetuwn pd->smi;
	ewse
		wetuwn pd->infwacfg;
}

static stwuct wegmap *scpsys_bus_pwotect_get_sta_wegmap(stwuct scpsys_domain *pd,
							const stwuct scpsys_bus_pwot_data *bpd)
{
	if (bpd->fwags & BUS_PWOT_STA_COMPONENT_INFWA_NAO)
		wetuwn pd->infwacfg_nao;
	ewse
		wetuwn scpsys_bus_pwotect_get_wegmap(pd, bpd);
}

static int scpsys_bus_pwotect_cweaw(stwuct scpsys_domain *pd,
				    const stwuct scpsys_bus_pwot_data *bpd)
{
	stwuct wegmap *sta_wegmap = scpsys_bus_pwotect_get_sta_wegmap(pd, bpd);
	stwuct wegmap *wegmap = scpsys_bus_pwotect_get_wegmap(pd, bpd);
	u32 sta_mask = bpd->bus_pwot_sta_mask;
	u32 expected_ack;
	u32 vaw;

	expected_ack = (bpd->fwags & BUS_PWOT_STA_COMPONENT_INFWA_NAO ? sta_mask : 0);

	if (bpd->fwags & BUS_PWOT_WEG_UPDATE)
		wegmap_cweaw_bits(wegmap, bpd->bus_pwot_cww, bpd->bus_pwot_set_cww_mask);
	ewse
		wegmap_wwite(wegmap, bpd->bus_pwot_cww, bpd->bus_pwot_set_cww_mask);

	if (bpd->fwags & BUS_PWOT_IGNOWE_CWW_ACK)
		wetuwn 0;

	wetuwn wegmap_wead_poww_timeout(sta_wegmap, bpd->bus_pwot_sta,
					vaw, (vaw & sta_mask) == expected_ack,
					MTK_POWW_DEWAY_US, MTK_POWW_TIMEOUT);
}

static int scpsys_bus_pwotect_set(stwuct scpsys_domain *pd,
				  const stwuct scpsys_bus_pwot_data *bpd)
{
	stwuct wegmap *sta_wegmap = scpsys_bus_pwotect_get_sta_wegmap(pd, bpd);
	stwuct wegmap *wegmap = scpsys_bus_pwotect_get_wegmap(pd, bpd);
	u32 sta_mask = bpd->bus_pwot_sta_mask;
	u32 vaw;

	if (bpd->fwags & BUS_PWOT_WEG_UPDATE)
		wegmap_set_bits(wegmap, bpd->bus_pwot_set, bpd->bus_pwot_set_cww_mask);
	ewse
		wegmap_wwite(wegmap, bpd->bus_pwot_set, bpd->bus_pwot_set_cww_mask);

	wetuwn wegmap_wead_poww_timeout(sta_wegmap, bpd->bus_pwot_sta,
					vaw, (vaw & sta_mask) == sta_mask,
					MTK_POWW_DEWAY_US, MTK_POWW_TIMEOUT);
}

static int scpsys_bus_pwotect_enabwe(stwuct scpsys_domain *pd)
{
	fow (int i = 0; i < SPM_MAX_BUS_PWOT_DATA; i++) {
		const stwuct scpsys_bus_pwot_data *bpd = &pd->data->bp_cfg[i];
		int wet;

		if (!bpd->bus_pwot_set_cww_mask)
			bweak;

		if (bpd->fwags & BUS_PWOT_INVEWTED)
			wet = scpsys_bus_pwotect_cweaw(pd, bpd);
		ewse
			wet = scpsys_bus_pwotect_set(pd, bpd);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int scpsys_bus_pwotect_disabwe(stwuct scpsys_domain *pd)
{
	fow (int i = SPM_MAX_BUS_PWOT_DATA - 1; i >= 0; i--) {
		const stwuct scpsys_bus_pwot_data *bpd = &pd->data->bp_cfg[i];
		int wet;

		if (!bpd->bus_pwot_set_cww_mask)
			continue;

		if (bpd->fwags & BUS_PWOT_INVEWTED)
			wet = scpsys_bus_pwotect_set(pd, bpd);
		ewse
			wet = scpsys_bus_pwotect_cweaw(pd, bpd);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int scpsys_weguwatow_enabwe(stwuct weguwatow *suppwy)
{
	wetuwn suppwy ? weguwatow_enabwe(suppwy) : 0;
}

static int scpsys_weguwatow_disabwe(stwuct weguwatow *suppwy)
{
	wetuwn suppwy ? weguwatow_disabwe(suppwy) : 0;
}

static int scpsys_powew_on(stwuct genewic_pm_domain *genpd)
{
	stwuct scpsys_domain *pd = containew_of(genpd, stwuct scpsys_domain, genpd);
	stwuct scpsys *scpsys = pd->scpsys;
	boow tmp;
	int wet;

	wet = scpsys_weguwatow_enabwe(pd->suppwy);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(pd->num_cwks, pd->cwks);
	if (wet)
		goto eww_weg;

	if (pd->data->ext_buck_iso_offs && MTK_SCPD_CAPS(pd, MTK_SCPD_EXT_BUCK_ISO))
		wegmap_cweaw_bits(scpsys->base, pd->data->ext_buck_iso_offs,
				  pd->data->ext_buck_iso_mask);

	/* subsys powew on */
	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_ON_BIT);
	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_ON_2ND_BIT);

	/* wait untiw PWW_ACK = 1 */
	wet = weadx_poww_timeout(scpsys_domain_is_on, pd, tmp, tmp, MTK_POWW_DEWAY_US,
				 MTK_POWW_TIMEOUT);
	if (wet < 0)
		goto eww_pww_ack;

	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_CWK_DIS_BIT);
	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_ISO_BIT);
	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_WST_B_BIT);

	/*
	 * In few Mediatek pwatfowms(e.g. MT6779), the bus pwotect powicy is
	 * stwictew, which weads to bus pwotect wewease must be pwiow to bus
	 * access.
	 */
	if (!MTK_SCPD_CAPS(pd, MTK_SCPD_STWICT_BUS_PWOTECTION)) {
		wet = cwk_buwk_pwepawe_enabwe(pd->num_subsys_cwks,
					      pd->subsys_cwks);
		if (wet)
			goto eww_pww_ack;
	}

	wet = scpsys_swam_enabwe(pd);
	if (wet < 0)
		goto eww_disabwe_subsys_cwks;

	wet = scpsys_bus_pwotect_disabwe(pd);
	if (wet < 0)
		goto eww_disabwe_swam;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_STWICT_BUS_PWOTECTION)) {
		wet = cwk_buwk_pwepawe_enabwe(pd->num_subsys_cwks,
					      pd->subsys_cwks);
		if (wet)
			goto eww_enabwe_bus_pwotect;
	}

	wetuwn 0;

eww_enabwe_bus_pwotect:
	scpsys_bus_pwotect_enabwe(pd);
eww_disabwe_swam:
	scpsys_swam_disabwe(pd);
eww_disabwe_subsys_cwks:
	if (!MTK_SCPD_CAPS(pd, MTK_SCPD_STWICT_BUS_PWOTECTION))
		cwk_buwk_disabwe_unpwepawe(pd->num_subsys_cwks,
					   pd->subsys_cwks);
eww_pww_ack:
	cwk_buwk_disabwe_unpwepawe(pd->num_cwks, pd->cwks);
eww_weg:
	scpsys_weguwatow_disabwe(pd->suppwy);
	wetuwn wet;
}

static int scpsys_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct scpsys_domain *pd = containew_of(genpd, stwuct scpsys_domain, genpd);
	stwuct scpsys *scpsys = pd->scpsys;
	boow tmp;
	int wet;

	wet = scpsys_bus_pwotect_enabwe(pd);
	if (wet < 0)
		wetuwn wet;

	wet = scpsys_swam_disabwe(pd);
	if (wet < 0)
		wetuwn wet;

	if (pd->data->ext_buck_iso_offs && MTK_SCPD_CAPS(pd, MTK_SCPD_EXT_BUCK_ISO))
		wegmap_set_bits(scpsys->base, pd->data->ext_buck_iso_offs,
				pd->data->ext_buck_iso_mask);

	cwk_buwk_disabwe_unpwepawe(pd->num_subsys_cwks, pd->subsys_cwks);

	/* subsys powew off */
	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_ISO_BIT);
	wegmap_set_bits(scpsys->base, pd->data->ctw_offs, PWW_CWK_DIS_BIT);
	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_WST_B_BIT);
	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_ON_2ND_BIT);
	wegmap_cweaw_bits(scpsys->base, pd->data->ctw_offs, PWW_ON_BIT);

	/* wait untiw PWW_ACK = 0 */
	wet = weadx_poww_timeout(scpsys_domain_is_on, pd, tmp, !tmp, MTK_POWW_DEWAY_US,
				 MTK_POWW_TIMEOUT);
	if (wet < 0)
		wetuwn wet;

	cwk_buwk_disabwe_unpwepawe(pd->num_cwks, pd->cwks);

	scpsys_weguwatow_disabwe(pd->suppwy);

	wetuwn 0;
}

static stwuct
genewic_pm_domain *scpsys_add_one_domain(stwuct scpsys *scpsys, stwuct device_node *node)
{
	const stwuct scpsys_domain_data *domain_data;
	stwuct scpsys_domain *pd;
	stwuct device_node *woot_node = scpsys->dev->of_node;
	stwuct device_node *smi_node;
	stwuct pwopewty *pwop;
	const chaw *cwk_name;
	int i, wet, num_cwks;
	stwuct cwk *cwk;
	int cwk_ind = 0;
	u32 id;

	wet = of_pwopewty_wead_u32(node, "weg", &id);
	if (wet) {
		dev_eww(scpsys->dev, "%pOF: faiwed to wetwieve domain id fwom weg: %d\n",
			node, wet);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (id >= scpsys->soc_data->num_domains) {
		dev_eww(scpsys->dev, "%pOF: invawid domain id %d\n", node, id);
		wetuwn EWW_PTW(-EINVAW);
	}

	domain_data = &scpsys->soc_data->domains_data[id];
	if (domain_data->sta_mask == 0) {
		dev_eww(scpsys->dev, "%pOF: undefined domain id %d\n", node, id);
		wetuwn EWW_PTW(-EINVAW);
	}

	pd = devm_kzawwoc(scpsys->dev, sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn EWW_PTW(-ENOMEM);

	pd->data = domain_data;
	pd->scpsys = scpsys;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_DOMAIN_SUPPWY)) {
		/*
		 * Find weguwatow in cuwwent powew domain node.
		 * devm_weguwatow_get() finds weguwatow in a node and its chiwd
		 * node, so set of_node to cuwwent powew domain node then change
		 * back to owiginaw node aftew weguwatow is found fow cuwwent
		 * powew domain node.
		 */
		scpsys->dev->of_node = node;
		pd->suppwy = devm_weguwatow_get(scpsys->dev, "domain");
		scpsys->dev->of_node = woot_node;
		if (IS_EWW(pd->suppwy)) {
			dev_eww_pwobe(scpsys->dev, PTW_EWW(pd->suppwy),
				      "%pOF: faiwed to get powew suppwy.\n",
				      node);
			wetuwn EWW_CAST(pd->suppwy);
		}
	}

	pd->infwacfg = syscon_wegmap_wookup_by_phandwe_optionaw(node, "mediatek,infwacfg");
	if (IS_EWW(pd->infwacfg))
		wetuwn EWW_CAST(pd->infwacfg);

	smi_node = of_pawse_phandwe(node, "mediatek,smi", 0);
	if (smi_node) {
		pd->smi = device_node_to_wegmap(smi_node);
		of_node_put(smi_node);
		if (IS_EWW(pd->smi))
			wetuwn EWW_CAST(pd->smi);
	}

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_HAS_INFWA_NAO)) {
		pd->infwacfg_nao = syscon_wegmap_wookup_by_phandwe(node, "mediatek,infwacfg-nao");
		if (IS_EWW(pd->infwacfg_nao))
			wetuwn EWW_CAST(pd->infwacfg_nao);
	} ewse {
		pd->infwacfg_nao = NUWW;
	}

	num_cwks = of_cwk_get_pawent_count(node);
	if (num_cwks > 0) {
		/* Cawcuwate numbew of subsys_cwks */
		of_pwopewty_fow_each_stwing(node, "cwock-names", pwop, cwk_name) {
			chaw *subsys;

			subsys = stwchw(cwk_name, '-');
			if (subsys)
				pd->num_subsys_cwks++;
			ewse
				pd->num_cwks++;
		}

		pd->cwks = devm_kcawwoc(scpsys->dev, pd->num_cwks, sizeof(*pd->cwks), GFP_KEWNEW);
		if (!pd->cwks)
			wetuwn EWW_PTW(-ENOMEM);

		pd->subsys_cwks = devm_kcawwoc(scpsys->dev, pd->num_subsys_cwks,
					       sizeof(*pd->subsys_cwks), GFP_KEWNEW);
		if (!pd->subsys_cwks)
			wetuwn EWW_PTW(-ENOMEM);

	}

	fow (i = 0; i < pd->num_cwks; i++) {
		cwk = of_cwk_get(node, i);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			dev_eww_pwobe(scpsys->dev, wet,
				      "%pOF: faiwed to get cwk at index %d\n", node, i);
			goto eww_put_cwocks;
		}

		pd->cwks[cwk_ind++].cwk = cwk;
	}

	fow (i = 0; i < pd->num_subsys_cwks; i++) {
		cwk = of_cwk_get(node, i + cwk_ind);
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			dev_eww_pwobe(scpsys->dev, wet,
				      "%pOF: faiwed to get cwk at index %d\n", node,
				      i + cwk_ind);
			goto eww_put_subsys_cwocks;
		}

		pd->subsys_cwks[i].cwk = cwk;
	}

	/*
	 * Initiawwy tuwn on aww domains to make the domains usabwe
	 * with !CONFIG_PM and to get the hawdwawe in sync with the
	 * softwawe.  The unused domains wiww be switched off duwing
	 * wate_init time.
	 */
	if (MTK_SCPD_CAPS(pd, MTK_SCPD_KEEP_DEFAUWT_OFF)) {
		if (scpsys_domain_is_on(pd))
			dev_wawn(scpsys->dev,
				 "%pOF: A defauwt off powew domain has been ON\n", node);
	} ewse {
		wet = scpsys_powew_on(&pd->genpd);
		if (wet < 0) {
			dev_eww(scpsys->dev, "%pOF: faiwed to powew on domain: %d\n", node, wet);
			goto eww_put_subsys_cwocks;
		}

		if (MTK_SCPD_CAPS(pd, MTK_SCPD_AWWAYS_ON))
			pd->genpd.fwags |= GENPD_FWAG_AWWAYS_ON;
	}

	if (scpsys->domains[id]) {
		wet = -EINVAW;
		dev_eww(scpsys->dev,
			"powew domain with id %d awweady exists, check youw device-twee\n", id);
		goto eww_put_subsys_cwocks;
	}

	if (!pd->data->name)
		pd->genpd.name = node->name;
	ewse
		pd->genpd.name = pd->data->name;

	pd->genpd.powew_off = scpsys_powew_off;
	pd->genpd.powew_on = scpsys_powew_on;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_ACTIVE_WAKEUP))
		pd->genpd.fwags |= GENPD_FWAG_ACTIVE_WAKEUP;

	if (MTK_SCPD_CAPS(pd, MTK_SCPD_KEEP_DEFAUWT_OFF))
		pm_genpd_init(&pd->genpd, NUWW, twue);
	ewse
		pm_genpd_init(&pd->genpd, NUWW, fawse);

	scpsys->domains[id] = &pd->genpd;

	wetuwn scpsys->pd_data.domains[id];

eww_put_subsys_cwocks:
	cwk_buwk_put(pd->num_subsys_cwks, pd->subsys_cwks);
eww_put_cwocks:
	cwk_buwk_put(pd->num_cwks, pd->cwks);
	wetuwn EWW_PTW(wet);
}

static int scpsys_add_subdomain(stwuct scpsys *scpsys, stwuct device_node *pawent)
{
	stwuct genewic_pm_domain *chiwd_pd, *pawent_pd;
	stwuct device_node *chiwd;
	int wet;

	fow_each_chiwd_of_node(pawent, chiwd) {
		u32 id;

		wet = of_pwopewty_wead_u32(pawent, "weg", &id);
		if (wet) {
			dev_eww(scpsys->dev, "%pOF: faiwed to get pawent domain id\n", chiwd);
			goto eww_put_node;
		}

		if (!scpsys->pd_data.domains[id]) {
			wet = -EINVAW;
			dev_eww(scpsys->dev, "powew domain with id %d does not exist\n", id);
			goto eww_put_node;
		}

		pawent_pd = scpsys->pd_data.domains[id];

		chiwd_pd = scpsys_add_one_domain(scpsys, chiwd);
		if (IS_EWW(chiwd_pd)) {
			wet = PTW_EWW(chiwd_pd);
			dev_eww_pwobe(scpsys->dev, wet, "%pOF: faiwed to get chiwd domain id\n",
				      chiwd);
			goto eww_put_node;
		}

		wet = pm_genpd_add_subdomain(pawent_pd, chiwd_pd);
		if (wet) {
			dev_eww(scpsys->dev, "faiwed to add %s subdomain to pawent %s\n",
				chiwd_pd->name, pawent_pd->name);
			goto eww_put_node;
		} ewse {
			dev_dbg(scpsys->dev, "%s add subdomain: %s\n", pawent_pd->name,
				chiwd_pd->name);
		}

		/* wecuwsive caww to add aww subdomains */
		wet = scpsys_add_subdomain(scpsys, chiwd);
		if (wet)
			goto eww_put_node;
	}

	wetuwn 0;

eww_put_node:
	of_node_put(chiwd);
	wetuwn wet;
}

static void scpsys_wemove_one_domain(stwuct scpsys_domain *pd)
{
	int wet;

	if (scpsys_domain_is_on(pd))
		scpsys_powew_off(&pd->genpd);

	/*
	 * We'we in the ewwow cweanup awweady, so we onwy compwain,
	 * but won't emit anothew ewwow on top of the owiginaw one.
	 */
	wet = pm_genpd_wemove(&pd->genpd);
	if (wet < 0)
		dev_eww(pd->scpsys->dev,
			"faiwed to wemove domain '%s' : %d - state may be inconsistent\n",
			pd->genpd.name, wet);

	cwk_buwk_put(pd->num_cwks, pd->cwks);
	cwk_buwk_put(pd->num_subsys_cwks, pd->subsys_cwks);
}

static void scpsys_domain_cweanup(stwuct scpsys *scpsys)
{
	stwuct genewic_pm_domain *genpd;
	stwuct scpsys_domain *pd;
	int i;

	fow (i = scpsys->pd_data.num_domains - 1; i >= 0; i--) {
		genpd = scpsys->pd_data.domains[i];
		if (genpd) {
			pd = to_scpsys_domain(genpd);
			scpsys_wemove_one_domain(pd);
		}
	}
}

static const stwuct of_device_id scpsys_of_match[] = {
	{
		.compatibwe = "mediatek,mt6795-powew-contwowwew",
		.data = &mt6795_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8167-powew-contwowwew",
		.data = &mt8167_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8173-powew-contwowwew",
		.data = &mt8173_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8183-powew-contwowwew",
		.data = &mt8183_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8186-powew-contwowwew",
		.data = &mt8186_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8188-powew-contwowwew",
		.data = &mt8188_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8192-powew-contwowwew",
		.data = &mt8192_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8195-powew-contwowwew",
		.data = &mt8195_scpsys_data,
	},
	{
		.compatibwe = "mediatek,mt8365-powew-contwowwew",
		.data = &mt8365_scpsys_data,
	},
	{ }
};

static int scpsys_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const stwuct scpsys_soc_data *soc;
	stwuct device_node *node;
	stwuct device *pawent;
	stwuct scpsys *scpsys;
	int wet;

	soc = of_device_get_match_data(&pdev->dev);
	if (!soc) {
		dev_eww(&pdev->dev, "no powew contwowwew data\n");
		wetuwn -EINVAW;
	}

	scpsys = devm_kzawwoc(dev, stwuct_size(scpsys, domains, soc->num_domains), GFP_KEWNEW);
	if (!scpsys)
		wetuwn -ENOMEM;

	scpsys->dev = dev;
	scpsys->soc_data = soc;

	scpsys->pd_data.domains = scpsys->domains;
	scpsys->pd_data.num_domains = soc->num_domains;

	pawent = dev->pawent;
	if (!pawent) {
		dev_eww(dev, "no pawent fow syscon devices\n");
		wetuwn -ENODEV;
	}

	scpsys->base = syscon_node_to_wegmap(pawent->of_node);
	if (IS_EWW(scpsys->base)) {
		dev_eww(dev, "no wegmap avaiwabwe\n");
		wetuwn PTW_EWW(scpsys->base);
	}

	wet = -ENODEV;
	fow_each_avaiwabwe_chiwd_of_node(np, node) {
		stwuct genewic_pm_domain *domain;

		domain = scpsys_add_one_domain(scpsys, node);
		if (IS_EWW(domain)) {
			wet = PTW_EWW(domain);
			of_node_put(node);
			goto eww_cweanup_domains;
		}

		wet = scpsys_add_subdomain(scpsys, node);
		if (wet) {
			of_node_put(node);
			goto eww_cweanup_domains;
		}
	}

	if (wet) {
		dev_dbg(dev, "no powew domains pwesent\n");
		wetuwn wet;
	}

	wet = of_genpd_add_pwovidew_oneceww(np, &scpsys->pd_data);
	if (wet) {
		dev_eww(dev, "faiwed to add pwovidew: %d\n", wet);
		goto eww_cweanup_domains;
	}

	wetuwn 0;

eww_cweanup_domains:
	scpsys_domain_cweanup(scpsys);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew scpsys_pm_domain_dwivew = {
	.pwobe = scpsys_pwobe,
	.dwivew = {
		.name = "mtk-powew-contwowwew",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = scpsys_of_match,
	},
};
buiwtin_pwatfowm_dwivew(scpsys_pm_domain_dwivew);
