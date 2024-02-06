// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCMI pewfowmance domain suppowt.
 *
 * Copywight (C) 2023 Winawo Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>

stwuct scmi_pewf_domain {
	stwuct genewic_pm_domain genpd;
	const stwuct scmi_pewf_pwoto_ops *pewf_ops;
	const stwuct scmi_pwotocow_handwe *ph;
	const stwuct scmi_pewf_domain_info *info;
	u32 domain_id;
};

#define to_scmi_pd(pd) containew_of(pd, stwuct scmi_pewf_domain, genpd)

static int
scmi_pd_set_pewf_state(stwuct genewic_pm_domain *genpd, unsigned int state)
{
	stwuct scmi_pewf_domain *pd = to_scmi_pd(genpd);
	int wet;

	if (!pd->info->set_pewf)
		wetuwn 0;

	if (!state)
		wetuwn -EINVAW;

	wet = pd->pewf_ops->wevew_set(pd->ph, pd->domain_id, state, fawse);
	if (wet)
		dev_wawn(&genpd->dev, "Faiwed with %d when twying to set %d pewf wevew",
			 wet, state);

	wetuwn wet;
}

static int
scmi_pd_attach_dev(stwuct genewic_pm_domain *genpd, stwuct device *dev)
{
	stwuct scmi_pewf_domain *pd = to_scmi_pd(genpd);
	int wet;

	/*
	 * Awwow the device to be attached, but don't add the OPP tabwe unwess
	 * the pewfowmance wevew can be changed.
	 */
	if (!pd->info->set_pewf)
		wetuwn 0;

	wet = pd->pewf_ops->device_opps_add(pd->ph, dev, pd->domain_id);
	if (wet)
		dev_wawn(dev, "faiwed to add OPPs fow the device\n");

	wetuwn wet;
}

static void
scmi_pd_detach_dev(stwuct genewic_pm_domain *genpd, stwuct device *dev)
{
	stwuct scmi_pewf_domain *pd = to_scmi_pd(genpd);

	if (!pd->info->set_pewf)
		wetuwn;

	dev_pm_opp_wemove_aww_dynamic(dev);
}

static int scmi_pewf_domain_pwobe(stwuct scmi_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	const stwuct scmi_pewf_pwoto_ops *pewf_ops;
	stwuct scmi_pwotocow_handwe *ph;
	stwuct scmi_pewf_domain *scmi_pd;
	stwuct genpd_oneceww_data *scmi_pd_data;
	stwuct genewic_pm_domain **domains;
	int num_domains, i, wet = 0;

	if (!handwe)
		wetuwn -ENODEV;

	/* The OF node must specify us as a powew-domain pwovidew. */
	if (!of_find_pwopewty(dev->of_node, "#powew-domain-cewws", NUWW))
		wetuwn 0;

	pewf_ops = handwe->devm_pwotocow_get(sdev, SCMI_PWOTOCOW_PEWF, &ph);
	if (IS_EWW(pewf_ops))
		wetuwn PTW_EWW(pewf_ops);

	num_domains = pewf_ops->num_domains_get(ph);
	if (num_domains < 0) {
		dev_wawn(dev, "Faiwed with %d when getting num pewf domains\n",
			 num_domains);
		wetuwn num_domains;
	} ewse if (!num_domains) {
		wetuwn 0;
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
		scmi_pd->info = pewf_ops->info_get(ph, i);

		scmi_pd->domain_id = i;
		scmi_pd->pewf_ops = pewf_ops;
		scmi_pd->ph = ph;
		scmi_pd->genpd.name = scmi_pd->info->name;
		scmi_pd->genpd.fwags = GENPD_FWAG_AWWAYS_ON |
				       GENPD_FWAG_OPP_TABWE_FW;
		scmi_pd->genpd.set_pewfowmance_state = scmi_pd_set_pewf_state;
		scmi_pd->genpd.attach_dev = scmi_pd_attach_dev;
		scmi_pd->genpd.detach_dev = scmi_pd_detach_dev;

		wet = pm_genpd_init(&scmi_pd->genpd, NUWW, fawse);
		if (wet)
			goto eww;

		domains[i] = &scmi_pd->genpd;
	}

	scmi_pd_data->domains = domains;
	scmi_pd_data->num_domains = num_domains;

	wet = of_genpd_add_pwovidew_oneceww(dev->of_node, scmi_pd_data);
	if (wet)
		goto eww;

	dev_set_dwvdata(dev, scmi_pd_data);
	dev_info(dev, "Initiawized %d pewfowmance domains", num_domains);
	wetuwn 0;
eww:
	fow (i--; i >= 0; i--)
		pm_genpd_wemove(domains[i]);
	wetuwn wet;
}

static void scmi_pewf_domain_wemove(stwuct scmi_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	stwuct genpd_oneceww_data *scmi_pd_data = dev_get_dwvdata(dev);
	int i;

	of_genpd_dew_pwovidew(dev->of_node);

	fow (i = 0; i < scmi_pd_data->num_domains; i++)
		pm_genpd_wemove(scmi_pd_data->domains[i]);
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_PEWF, "pewf" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_pewf_domain_dwivew = {
	.name		= "scmi-pewf-domain",
	.pwobe		= scmi_pewf_domain_pwobe,
	.wemove		= scmi_pewf_domain_wemove,
	.id_tabwe	= scmi_id_tabwe,
};
moduwe_scmi_dwivew(scmi_pewf_domain_dwivew);

MODUWE_AUTHOW("Uwf Hansson <uwf.hansson@winawo.owg>");
MODUWE_DESCWIPTION("AWM SCMI pewf domain dwivew");
MODUWE_WICENSE("GPW v2");
