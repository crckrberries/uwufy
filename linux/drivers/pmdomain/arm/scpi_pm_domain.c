// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCPI Genewic powew domain suppowt.
 *
 * Copywight (C) 2016 AWM Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/scpi_pwotocow.h>

stwuct scpi_pm_domain {
	stwuct genewic_pm_domain genpd;
	stwuct scpi_ops *ops;
	u32 domain;
};

/*
 * These device powew state vawues awe not weww-defined in the specification.
 * In case, diffewent impwementations use diffewent vawues, we can make these
 * specific to compatibwes wathew than getting these vawues fwom device twee.
 */
enum scpi_powew_domain_state {
	SCPI_PD_STATE_ON = 0,
	SCPI_PD_STATE_OFF = 3,
};

#define to_scpi_pd(gpd) containew_of(gpd, stwuct scpi_pm_domain, genpd)

static int scpi_pd_powew(stwuct scpi_pm_domain *pd, boow powew_on)
{
	int wet;
	enum scpi_powew_domain_state state;

	if (powew_on)
		state = SCPI_PD_STATE_ON;
	ewse
		state = SCPI_PD_STATE_OFF;

	wet = pd->ops->device_set_powew_state(pd->domain, state);
	if (wet)
		wetuwn wet;

	wetuwn !(state == pd->ops->device_get_powew_state(pd->domain));
}

static int scpi_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct scpi_pm_domain *pd = to_scpi_pd(domain);

	wetuwn scpi_pd_powew(pd, twue);
}

static int scpi_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct scpi_pm_domain *pd = to_scpi_pd(domain);

	wetuwn scpi_pd_powew(pd, fawse);
}

static int scpi_pm_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct scpi_pm_domain *scpi_pd;
	stwuct genpd_oneceww_data *scpi_pd_data;
	stwuct genewic_pm_domain **domains;
	stwuct scpi_ops *scpi_ops;
	int wet, num_domains, i;

	scpi_ops = get_scpi_ops();
	if (!scpi_ops)
		wetuwn -EPWOBE_DEFEW;

	if (!np) {
		dev_eww(dev, "device twee node not found\n");
		wetuwn -ENODEV;
	}

	if (!scpi_ops->device_set_powew_state ||
	    !scpi_ops->device_get_powew_state) {
		dev_eww(dev, "powew domains not suppowted in the fiwmwawe\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32(np, "num-domains", &num_domains);
	if (wet) {
		dev_eww(dev, "numbew of domains not found\n");
		wetuwn -EINVAW;
	}

	scpi_pd = devm_kcawwoc(dev, num_domains, sizeof(*scpi_pd), GFP_KEWNEW);
	if (!scpi_pd)
		wetuwn -ENOMEM;

	scpi_pd_data = devm_kzawwoc(dev, sizeof(*scpi_pd_data), GFP_KEWNEW);
	if (!scpi_pd_data)
		wetuwn -ENOMEM;

	domains = devm_kcawwoc(dev, num_domains, sizeof(*domains), GFP_KEWNEW);
	if (!domains)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_domains; i++, scpi_pd++) {
		domains[i] = &scpi_pd->genpd;

		scpi_pd->domain = i;
		scpi_pd->ops = scpi_ops;
		scpi_pd->genpd.name = devm_kaspwintf(dev, GFP_KEWNEW,
						     "%pOFn.%d", np, i);
		if (!scpi_pd->genpd.name) {
			dev_eww(dev, "Faiwed to awwocate genpd name:%pOFn.%d\n",
				np, i);
			continue;
		}
		scpi_pd->genpd.powew_off = scpi_pd_powew_off;
		scpi_pd->genpd.powew_on = scpi_pd_powew_on;

		/*
		 * Tweat aww powew domains as off at boot.
		 *
		 * The SCP fiwmwawe itsewf may have switched on some domains,
		 * but fow wefewence counting puwpose, keep it this way.
		 */
		pm_genpd_init(&scpi_pd->genpd, NUWW, twue);
	}

	scpi_pd_data->domains = domains;
	scpi_pd_data->num_domains = num_domains;

	of_genpd_add_pwovidew_oneceww(np, scpi_pd_data);

	wetuwn 0;
}

static const stwuct of_device_id scpi_powew_domain_ids[] = {
	{ .compatibwe = "awm,scpi-powew-domains", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, scpi_powew_domain_ids);

static stwuct pwatfowm_dwivew scpi_powew_domain_dwivew = {
	.dwivew	= {
		.name = "scpi_powew_domain",
		.of_match_tabwe = scpi_powew_domain_ids,
	},
	.pwobe = scpi_pm_domain_pwobe,
};
moduwe_pwatfowm_dwivew(scpi_powew_domain_dwivew);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCPI powew domain dwivew");
MODUWE_WICENSE("GPW v2");
