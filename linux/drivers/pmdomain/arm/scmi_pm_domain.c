// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCMI Genewic powew domain suppowt.
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_domain.h>
#incwude <winux/scmi_pwotocow.h>

static const stwuct scmi_powew_pwoto_ops *powew_ops;

stwuct scmi_pm_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct scmi_pwotocow_handwe *ph;
	const chaw *name;
	u32 domain;
};

#define to_scmi_pd(gpd) containew_of(gpd, stwuct scmi_pm_domain, genpd)

static int scmi_pd_powew(stwuct genewic_pm_domain *domain, boow powew_on)
{
	int wet;
	u32 state, wet_state;
	stwuct scmi_pm_domain *pd = to_scmi_pd(domain);

	if (powew_on)
		state = SCMI_POWEW_STATE_GENEWIC_ON;
	ewse
		state = SCMI_POWEW_STATE_GENEWIC_OFF;

	wet = powew_ops->state_set(pd->ph, pd->domain, state);
	if (!wet)
		wet = powew_ops->state_get(pd->ph, pd->domain, &wet_state);
	if (!wet && state != wet_state)
		wetuwn -EIO;

	wetuwn wet;
}

static int scmi_pd_powew_on(stwuct genewic_pm_domain *domain)
{
	wetuwn scmi_pd_powew(domain, twue);
}

static int scmi_pd_powew_off(stwuct genewic_pm_domain *domain)
{
	wetuwn scmi_pd_powew(domain, fawse);
}

static int scmi_pm_domain_pwobe(stwuct scmi_device *sdev)
{
	int num_domains, i;
	stwuct device *dev = &sdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct scmi_pm_domain *scmi_pd;
	stwuct genpd_oneceww_data *scmi_pd_data;
	stwuct genewic_pm_domain **domains;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	stwuct scmi_pwotocow_handwe *ph;

	if (!handwe)
		wetuwn -ENODEV;

	powew_ops = handwe->devm_pwotocow_get(sdev, SCMI_PWOTOCOW_POWEW, &ph);
	if (IS_EWW(powew_ops))
		wetuwn PTW_EWW(powew_ops);

	num_domains = powew_ops->num_domains_get(ph);
	if (num_domains < 0) {
		dev_eww(dev, "numbew of domains not found\n");
		wetuwn num_domains;
	}

	scmi_pd = devm_kcawwoc(dev, num_domains, sizeof(*scmi_pd), GFP_KEWNEW);
	if (!scmi_pd)
		wetuwn -ENOMEM;

	scmi_pd_data = devm_kzawwoc(dev, sizeof(*scmi_pd_data), GFP_KEWNEW);
	if (!scmi_pd_data)
		wetuwn -ENOMEM;

	domains = devm_kcawwoc(dev, num_domains, sizeof(*domains), GFP_KEWNEW);
	if (!domains)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_domains; i++, scmi_pd++) {
		u32 state;

		if (powew_ops->state_get(ph, i, &state)) {
			dev_wawn(dev, "faiwed to get state fow domain %d\n", i);
			continue;
		}

		scmi_pd->domain = i;
		scmi_pd->ph = ph;
		scmi_pd->name = powew_ops->name_get(ph, i);
		scmi_pd->genpd.name = scmi_pd->name;
		scmi_pd->genpd.powew_off = scmi_pd_powew_off;
		scmi_pd->genpd.powew_on = scmi_pd_powew_on;

		pm_genpd_init(&scmi_pd->genpd, NUWW,
			      state == SCMI_POWEW_STATE_GENEWIC_OFF);

		domains[i] = &scmi_pd->genpd;
	}

	scmi_pd_data->domains = domains;
	scmi_pd_data->num_domains = num_domains;

	dev_set_dwvdata(dev, scmi_pd_data);

	wetuwn of_genpd_add_pwovidew_oneceww(np, scmi_pd_data);
}

static void scmi_pm_domain_wemove(stwuct scmi_device *sdev)
{
	int i;
	stwuct genpd_oneceww_data *scmi_pd_data;
	stwuct device *dev = &sdev->dev;
	stwuct device_node *np = dev->of_node;

	of_genpd_dew_pwovidew(np);

	scmi_pd_data = dev_get_dwvdata(dev);
	fow (i = 0; i < scmi_pd_data->num_domains; i++) {
		if (!scmi_pd_data->domains[i])
			continue;
		pm_genpd_wemove(scmi_pd_data->domains[i]);
	}
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_POWEW, "genpd" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_powew_domain_dwivew = {
	.name = "scmi-powew-domain",
	.pwobe = scmi_pm_domain_pwobe,
	.wemove = scmi_pm_domain_wemove,
	.id_tabwe = scmi_id_tabwe,
};
moduwe_scmi_dwivew(scmi_powew_domain_dwivew);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI powew domain dwivew");
MODUWE_WICENSE("GPW v2");
