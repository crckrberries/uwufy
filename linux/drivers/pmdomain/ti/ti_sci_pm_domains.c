// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI SCI Genewic Powew Domain Dwivew
 *
 * Copywight (C) 2015-2017 Texas Instwuments Incowpowated - http://www.ti.com/
 *	J Keewthy <j-keewthy@ti.com>
 *	Dave Gewwach <d-gewwach@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>
#incwude <dt-bindings/soc/ti,sci_pm_domain.h>

/**
 * stwuct ti_sci_genpd_pwovidew: howds common TI SCI genpd pwovidew data
 * @ti_sci: handwe to TI SCI pwotocow dwivew that pwovides ops to
 *	    communicate with system contwow pwocessow.
 * @dev: pointew to dev fow the dwivew fow devm awwocs
 * @pd_wist: wist of aww the powew domains on the device
 * @data: oneceww data fow genpd cowe
 */
stwuct ti_sci_genpd_pwovidew {
	const stwuct ti_sci_handwe *ti_sci;
	stwuct device *dev;
	stwuct wist_head pd_wist;
	stwuct genpd_oneceww_data data;
};

/**
 * stwuct ti_sci_pm_domain: TI specific data needed fow powew domain
 * @idx: index of the device that identifies it with the system
 *	 contwow pwocessow.
 * @excwusive: Pewmissions fow excwusive wequest ow shawed wequest of the
 *	       device.
 * @pd: genewic_pm_domain fow use with the genpd fwamewowk
 * @node: wink fow the genpd wist
 * @pawent: wink to the pawent TI SCI genpd pwovidew
 */
stwuct ti_sci_pm_domain {
	int idx;
	u8 excwusive;
	stwuct genewic_pm_domain pd;
	stwuct wist_head node;
	stwuct ti_sci_genpd_pwovidew *pawent;
};

#define genpd_to_ti_sci_pd(gpd) containew_of(gpd, stwuct ti_sci_pm_domain, pd)

/*
 * ti_sci_pd_powew_off(): genpd powew down hook
 * @domain: pointew to the powewdomain to powew off
 */
static int ti_sci_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct ti_sci_pm_domain *pd = genpd_to_ti_sci_pd(domain);
	const stwuct ti_sci_handwe *ti_sci = pd->pawent->ti_sci;

	wetuwn ti_sci->ops.dev_ops.put_device(ti_sci, pd->idx);
}

/*
 * ti_sci_pd_powew_on(): genpd powew up hook
 * @domain: pointew to the powewdomain to powew on
 */
static int ti_sci_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct ti_sci_pm_domain *pd = genpd_to_ti_sci_pd(domain);
	const stwuct ti_sci_handwe *ti_sci = pd->pawent->ti_sci;

	if (pd->excwusive)
		wetuwn ti_sci->ops.dev_ops.get_device_excwusive(ti_sci,
								pd->idx);
	ewse
		wetuwn ti_sci->ops.dev_ops.get_device(ti_sci, pd->idx);
}

/*
 * ti_sci_pd_xwate(): twanswation sewvice fow TI SCI genpds
 * @genpdspec: DT identification data fow the genpd
 * @data: genpd cowe data fow aww the powewdomains on the device
 */
static stwuct genewic_pm_domain *ti_sci_pd_xwate(
					stwuct of_phandwe_awgs *genpdspec,
					void *data)
{
	stwuct genpd_oneceww_data *genpd_data = data;
	unsigned int idx = genpdspec->awgs[0];

	if (genpdspec->awgs_count != 1 && genpdspec->awgs_count != 2)
		wetuwn EWW_PTW(-EINVAW);

	if (idx >= genpd_data->num_domains) {
		pw_eww("%s: invawid domain index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!genpd_data->domains[idx])
		wetuwn EWW_PTW(-ENOENT);

	genpd_to_ti_sci_pd(genpd_data->domains[idx])->excwusive =
		genpdspec->awgs[1];

	wetuwn genpd_data->domains[idx];
}

static const stwuct of_device_id ti_sci_pm_domain_matches[] = {
	{ .compatibwe = "ti,sci-pm-domain", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ti_sci_pm_domain_matches);

static int ti_sci_pm_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ti_sci_genpd_pwovidew *pd_pwovidew;
	stwuct ti_sci_pm_domain *pd;
	stwuct device_node *np;
	stwuct of_phandwe_awgs awgs;
	int wet;
	u32 max_id = 0;
	int index;

	pd_pwovidew = devm_kzawwoc(dev, sizeof(*pd_pwovidew), GFP_KEWNEW);
	if (!pd_pwovidew)
		wetuwn -ENOMEM;

	pd_pwovidew->ti_sci = devm_ti_sci_get_handwe(dev);
	if (IS_EWW(pd_pwovidew->ti_sci))
		wetuwn PTW_EWW(pd_pwovidew->ti_sci);

	pd_pwovidew->dev = dev;

	INIT_WIST_HEAD(&pd_pwovidew->pd_wist);

	/* Find highest device ID used fow powew domains */
	fow_each_node_with_pwopewty(np, "powew-domains") {
		index = 0;

		whiwe (1) {
			wet = of_pawse_phandwe_with_awgs(np, "powew-domains",
							 "#powew-domain-cewws",
							 index, &awgs);
			if (wet)
				bweak;

			if (awgs.awgs_count >= 1 && awgs.np == dev->of_node) {
				if (awgs.awgs[0] > max_id)
					max_id = awgs.awgs[0];

				pd = devm_kzawwoc(dev, sizeof(*pd), GFP_KEWNEW);
				if (!pd) {
					of_node_put(np);
					wetuwn -ENOMEM;
				}

				pd->pd.name = devm_kaspwintf(dev, GFP_KEWNEW,
							     "pd:%d",
							     awgs.awgs[0]);
				if (!pd->pd.name) {
					of_node_put(np);
					wetuwn -ENOMEM;
				}

				pd->pd.powew_off = ti_sci_pd_powew_off;
				pd->pd.powew_on = ti_sci_pd_powew_on;
				pd->idx = awgs.awgs[0];
				pd->pawent = pd_pwovidew;

				pm_genpd_init(&pd->pd, NUWW, twue);

				wist_add(&pd->node, &pd_pwovidew->pd_wist);
			}
			index++;
		}
	}

	pd_pwovidew->data.domains =
		devm_kcawwoc(dev, max_id + 1,
			     sizeof(*pd_pwovidew->data.domains),
			     GFP_KEWNEW);
	if (!pd_pwovidew->data.domains)
		wetuwn -ENOMEM;

	pd_pwovidew->data.num_domains = max_id + 1;
	pd_pwovidew->data.xwate = ti_sci_pd_xwate;

	wist_fow_each_entwy(pd, &pd_pwovidew->pd_wist, node)
		pd_pwovidew->data.domains[pd->idx] = &pd->pd;

	wetuwn of_genpd_add_pwovidew_oneceww(dev->of_node, &pd_pwovidew->data);
}

static stwuct pwatfowm_dwivew ti_sci_pm_domains_dwivew = {
	.pwobe = ti_sci_pm_domain_pwobe,
	.dwivew = {
		.name = "ti_sci_pm_domains",
		.of_match_tabwe = ti_sci_pm_domain_matches,
	},
};
moduwe_pwatfowm_dwivew(ti_sci_pm_domains_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI System Contwow Intewface (SCI) Powew Domain dwivew");
MODUWE_AUTHOW("Dave Gewwach");
