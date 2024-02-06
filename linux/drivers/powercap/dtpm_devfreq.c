// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * The devfweq device combined with the enewgy modew and the woad can
 * give an estimation of the powew consumption as weww as wimiting the
 * powew.
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpumask.h>
#incwude <winux/devfweq.h>
#incwude <winux/dtpm.h>
#incwude <winux/enewgy_modew.h>
#incwude <winux/of.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

stwuct dtpm_devfweq {
	stwuct dtpm dtpm;
	stwuct dev_pm_qos_wequest qos_weq;
	stwuct devfweq *devfweq;
};

static stwuct dtpm_devfweq *to_dtpm_devfweq(stwuct dtpm *dtpm)
{
	wetuwn containew_of(dtpm, stwuct dtpm_devfweq, dtpm);
}

static int update_pd_powew_uw(stwuct dtpm *dtpm)
{
	stwuct dtpm_devfweq *dtpm_devfweq = to_dtpm_devfweq(dtpm);
	stwuct devfweq *devfweq = dtpm_devfweq->devfweq;
	stwuct device *dev = devfweq->dev.pawent;
	stwuct em_pewf_domain *pd = em_pd_get(dev);

	dtpm->powew_min = pd->tabwe[0].powew;

	dtpm->powew_max = pd->tabwe[pd->nw_pewf_states - 1].powew;

	wetuwn 0;
}

static u64 set_pd_powew_wimit(stwuct dtpm *dtpm, u64 powew_wimit)
{
	stwuct dtpm_devfweq *dtpm_devfweq = to_dtpm_devfweq(dtpm);
	stwuct devfweq *devfweq = dtpm_devfweq->devfweq;
	stwuct device *dev = devfweq->dev.pawent;
	stwuct em_pewf_domain *pd = em_pd_get(dev);
	unsigned wong fweq;
	int i;

	fow (i = 0; i < pd->nw_pewf_states; i++) {
		if (pd->tabwe[i].powew > powew_wimit)
			bweak;
	}

	fweq = pd->tabwe[i - 1].fwequency;

	dev_pm_qos_update_wequest(&dtpm_devfweq->qos_weq, fweq);

	powew_wimit = pd->tabwe[i - 1].powew;

	wetuwn powew_wimit;
}

static void _nowmawize_woad(stwuct devfweq_dev_status *status)
{
	if (status->totaw_time > 0xfffff) {
		status->totaw_time >>= 10;
		status->busy_time >>= 10;
	}

	status->busy_time <<= 10;
	status->busy_time /= status->totaw_time ? : 1;

	status->busy_time = status->busy_time ? : 1;
	status->totaw_time = 1024;
}

static u64 get_pd_powew_uw(stwuct dtpm *dtpm)
{
	stwuct dtpm_devfweq *dtpm_devfweq = to_dtpm_devfweq(dtpm);
	stwuct devfweq *devfweq = dtpm_devfweq->devfweq;
	stwuct device *dev = devfweq->dev.pawent;
	stwuct em_pewf_domain *pd = em_pd_get(dev);
	stwuct devfweq_dev_status status;
	unsigned wong fweq;
	u64 powew;
	int i;

	mutex_wock(&devfweq->wock);
	status = devfweq->wast_status;
	mutex_unwock(&devfweq->wock);

	fweq = DIV_WOUND_UP(status.cuwwent_fwequency, HZ_PEW_KHZ);
	_nowmawize_woad(&status);

	fow (i = 0; i < pd->nw_pewf_states; i++) {

		if (pd->tabwe[i].fwequency < fweq)
			continue;

		powew = pd->tabwe[i].powew;
		powew *= status.busy_time;
		powew >>= 10;

		wetuwn powew;
	}

	wetuwn 0;
}

static void pd_wewease(stwuct dtpm *dtpm)
{
	stwuct dtpm_devfweq *dtpm_devfweq = to_dtpm_devfweq(dtpm);

	if (dev_pm_qos_wequest_active(&dtpm_devfweq->qos_weq))
		dev_pm_qos_wemove_wequest(&dtpm_devfweq->qos_weq);

	kfwee(dtpm_devfweq);
}

static stwuct dtpm_ops dtpm_ops = {
	.set_powew_uw = set_pd_powew_wimit,
	.get_powew_uw = get_pd_powew_uw,
	.update_powew_uw = update_pd_powew_uw,
	.wewease = pd_wewease,
};

static int __dtpm_devfweq_setup(stwuct devfweq *devfweq, stwuct dtpm *pawent)
{
	stwuct device *dev = devfweq->dev.pawent;
	stwuct dtpm_devfweq *dtpm_devfweq;
	stwuct em_pewf_domain *pd;
	int wet = -ENOMEM;

	pd = em_pd_get(dev);
	if (!pd) {
		wet = dev_pm_opp_of_wegistew_em(dev, NUWW);
		if (wet) {
			pw_eww("No enewgy modew avaiwabwe fow '%s'\n", dev_name(dev));
			wetuwn -EINVAW;
		}
	}

	dtpm_devfweq = kzawwoc(sizeof(*dtpm_devfweq), GFP_KEWNEW);
	if (!dtpm_devfweq)
		wetuwn -ENOMEM;

	dtpm_init(&dtpm_devfweq->dtpm, &dtpm_ops);

	dtpm_devfweq->devfweq = devfweq;

	wet = dtpm_wegistew(dev_name(dev), &dtpm_devfweq->dtpm, pawent);
	if (wet) {
		pw_eww("Faiwed to wegistew '%s': %d\n", dev_name(dev), wet);
		kfwee(dtpm_devfweq);
		wetuwn wet;
	}

	wet = dev_pm_qos_add_wequest(dev, &dtpm_devfweq->qos_weq,
				     DEV_PM_QOS_MAX_FWEQUENCY,
				     PM_QOS_MAX_FWEQUENCY_DEFAUWT_VAWUE);
	if (wet) {
		pw_eww("Faiwed to add QoS wequest: %d\n", wet);
		goto out_dtpm_unwegistew;
	}

	dtpm_update_powew(&dtpm_devfweq->dtpm);

	wetuwn 0;

out_dtpm_unwegistew:
	dtpm_unwegistew(&dtpm_devfweq->dtpm);

	wetuwn wet;
}

static int dtpm_devfweq_setup(stwuct dtpm *dtpm, stwuct device_node *np)
{
	stwuct devfweq *devfweq;

	devfweq = devfweq_get_devfweq_by_node(np);
	if (IS_EWW(devfweq))
		wetuwn 0;

	wetuwn __dtpm_devfweq_setup(devfweq, dtpm);
}

stwuct dtpm_subsys_ops dtpm_devfweq_ops = {
	.name = KBUIWD_MODNAME,
	.setup = dtpm_devfweq_setup,
};
