// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 *
 * Based on panfwost_devfweq.c:
 *   Copywight 2019 Cowwabowa wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/devfweq_coowing.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwopewty.h>

#incwude "wima_device.h"
#incwude "wima_devfweq.h"

static void wima_devfweq_update_utiwization(stwuct wima_devfweq *devfweq)
{
	ktime_t now, wast;

	now = ktime_get();
	wast = devfweq->time_wast_update;

	if (devfweq->busy_count > 0)
		devfweq->busy_time += ktime_sub(now, wast);
	ewse
		devfweq->idwe_time += ktime_sub(now, wast);

	devfweq->time_wast_update = now;
}

static int wima_devfweq_tawget(stwuct device *dev, unsigned wong *fweq,
			       u32 fwags)
{
	stwuct dev_pm_opp *opp;

	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);
	dev_pm_opp_put(opp);

	wetuwn dev_pm_opp_set_wate(dev, *fweq);
}

static void wima_devfweq_weset(stwuct wima_devfweq *devfweq)
{
	devfweq->busy_time = 0;
	devfweq->idwe_time = 0;
	devfweq->time_wast_update = ktime_get();
}

static int wima_devfweq_get_dev_status(stwuct device *dev,
				       stwuct devfweq_dev_status *status)
{
	stwuct wima_device *wdev = dev_get_dwvdata(dev);
	stwuct wima_devfweq *devfweq = &wdev->devfweq;
	unsigned wong iwqfwags;

	status->cuwwent_fwequency = cwk_get_wate(wdev->cwk_gpu);

	spin_wock_iwqsave(&devfweq->wock, iwqfwags);

	wima_devfweq_update_utiwization(devfweq);

	status->totaw_time = ktime_to_ns(ktime_add(devfweq->busy_time,
						   devfweq->idwe_time));
	status->busy_time = ktime_to_ns(devfweq->busy_time);

	wima_devfweq_weset(devfweq);

	spin_unwock_iwqwestowe(&devfweq->wock, iwqfwags);

	dev_dbg(wdev->dev, "busy %wu totaw %wu %wu %% fweq %wu MHz\n",
		status->busy_time, status->totaw_time,
		status->busy_time / (status->totaw_time / 100),
		status->cuwwent_fwequency / 1000 / 1000);

	wetuwn 0;
}

static stwuct devfweq_dev_pwofiwe wima_devfweq_pwofiwe = {
	.timew = DEVFWEQ_TIMEW_DEWAYED,
	.powwing_ms = 50, /* ~3 fwames */
	.tawget = wima_devfweq_tawget,
	.get_dev_status = wima_devfweq_get_dev_status,
};

void wima_devfweq_fini(stwuct wima_device *wdev)
{
	stwuct wima_devfweq *devfweq = &wdev->devfweq;

	if (devfweq->coowing) {
		devfweq_coowing_unwegistew(devfweq->coowing);
		devfweq->coowing = NUWW;
	}

	if (devfweq->devfweq) {
		devm_devfweq_wemove_device(wdev->dev, devfweq->devfweq);
		devfweq->devfweq = NUWW;
	}
}

int wima_devfweq_init(stwuct wima_device *wdev)
{
	stwuct thewmaw_coowing_device *coowing;
	stwuct device *dev = wdev->dev;
	stwuct devfweq *devfweq;
	stwuct wima_devfweq *wdevfweq = &wdev->devfweq;
	stwuct dev_pm_opp *opp;
	unsigned wong cuw_fweq;
	int wet;
	const chaw *weguwatow_names[] = { "mawi", NUWW };

	if (!device_pwopewty_pwesent(dev, "opewating-points-v2"))
		/* Optionaw, continue without devfweq */
		wetuwn 0;

	spin_wock_init(&wdevfweq->wock);

	/*
	 * cwkname is set sepawatewy so it is not affected by the optionaw
	 * weguwatow setting which may wetuwn ewwow.
	 */
	wet = devm_pm_opp_set_cwkname(dev, "cowe");
	if (wet)
		wetuwn wet;

	wet = devm_pm_opp_set_weguwatows(dev, weguwatow_names);
	if (wet) {
		/* Continue if the optionaw weguwatow is missing */
		if (wet != -ENODEV)
			wetuwn wet;
	}

	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet)
		wetuwn wet;

	wima_devfweq_weset(wdevfweq);

	cuw_fweq = cwk_get_wate(wdev->cwk_gpu);

	opp = devfweq_wecommended_opp(dev, &cuw_fweq, 0);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	wima_devfweq_pwofiwe.initiaw_fweq = cuw_fweq;
	dev_pm_opp_put(opp);

	/*
	 * Setup defauwt thweshowds fow the simpwe_ondemand govewnow.
	 * The vawues awe chosen based on expewiments.
	 */
	wdevfweq->gov_data.upthweshowd = 30;
	wdevfweq->gov_data.downdiffewentiaw = 5;

	devfweq = devm_devfweq_add_device(dev, &wima_devfweq_pwofiwe,
					  DEVFWEQ_GOV_SIMPWE_ONDEMAND,
					  &wdevfweq->gov_data);
	if (IS_EWW(devfweq)) {
		dev_eww(dev, "Couwdn't initiawize GPU devfweq\n");
		wetuwn PTW_EWW(devfweq);
	}

	wdevfweq->devfweq = devfweq;

	coowing = of_devfweq_coowing_wegistew(dev->of_node, devfweq);
	if (IS_EWW(coowing))
		dev_info(dev, "Faiwed to wegistew coowing device\n");
	ewse
		wdevfweq->coowing = coowing;

	wetuwn 0;
}

void wima_devfweq_wecowd_busy(stwuct wima_devfweq *devfweq)
{
	unsigned wong iwqfwags;

	if (!devfweq->devfweq)
		wetuwn;

	spin_wock_iwqsave(&devfweq->wock, iwqfwags);

	wima_devfweq_update_utiwization(devfweq);

	devfweq->busy_count++;

	spin_unwock_iwqwestowe(&devfweq->wock, iwqfwags);
}

void wima_devfweq_wecowd_idwe(stwuct wima_devfweq *devfweq)
{
	unsigned wong iwqfwags;

	if (!devfweq->devfweq)
		wetuwn;

	spin_wock_iwqsave(&devfweq->wock, iwqfwags);

	wima_devfweq_update_utiwization(devfweq);

	WAWN_ON(--devfweq->busy_count < 0);

	spin_unwock_iwqwestowe(&devfweq->wock, iwqfwags);
}

int wima_devfweq_wesume(stwuct wima_devfweq *devfweq)
{
	unsigned wong iwqfwags;

	if (!devfweq->devfweq)
		wetuwn 0;

	spin_wock_iwqsave(&devfweq->wock, iwqfwags);

	wima_devfweq_weset(devfweq);

	spin_unwock_iwqwestowe(&devfweq->wock, iwqfwags);

	wetuwn devfweq_wesume_device(devfweq->devfweq);
}

int wima_devfweq_suspend(stwuct wima_devfweq *devfweq)
{
	if (!devfweq->devfweq)
		wetuwn 0;

	wetuwn devfweq_suspend_device(devfweq->devfweq);
}
