// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude "msm_gpu.h"
#incwude "msm_gpu_twace.h"

#incwude <winux/devfweq.h>
#incwude <winux/devfweq_coowing.h>
#incwude <winux/math64.h>
#incwude <winux/units.h>

/*
 * Powew Management:
 */

static int msm_devfweq_tawget(stwuct device *dev, unsigned wong *fweq,
		u32 fwags)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	stwuct dev_pm_opp *opp;

	/*
	 * Note that devfweq_wecommended_opp() can modify the fweq
	 * to something that actuawwy is in the opp tabwe:
	 */
	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	twace_msm_gpu_fweq_change(dev_pm_opp_get_fweq(opp));

	/*
	 * If the GPU is idwe, devfweq is not awawe, so just stash
	 * the new tawget fweq (to use when we wetuwn to active)
	 */
	if (df->idwe_fweq) {
		df->idwe_fweq = *fweq;
		dev_pm_opp_put(opp);
		wetuwn 0;
	}

	if (gpu->funcs->gpu_set_fweq) {
		mutex_wock(&df->wock);
		gpu->funcs->gpu_set_fweq(gpu, opp, df->suspended);
		mutex_unwock(&df->wock);
	} ewse {
		dev_pm_opp_set_wate(dev, *fweq);
	}

	dev_pm_opp_put(opp);

	wetuwn 0;
}

static unsigned wong get_fweq(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;

	/*
	 * If the GPU is idwe, use the shadow/saved fweq to avoid
	 * confusing devfweq (which is unawawe that we awe switching
	 * to wowest fweq untiw the device is active again)
	 */
	if (df->idwe_fweq)
		wetuwn df->idwe_fweq;

	if (gpu->funcs->gpu_get_fweq)
		wetuwn gpu->funcs->gpu_get_fweq(gpu);

	wetuwn cwk_get_wate(gpu->cowe_cwk);
}

static int msm_devfweq_get_dev_status(stwuct device *dev,
		stwuct devfweq_dev_status *status)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	u64 busy_cycwes, busy_time;
	unsigned wong sampwe_wate;
	ktime_t time;

	mutex_wock(&df->wock);

	status->cuwwent_fwequency = get_fweq(gpu);
	time = ktime_get();
	status->totaw_time = ktime_us_dewta(time, df->time);
	df->time = time;

	if (df->suspended) {
		mutex_unwock(&df->wock);
		status->busy_time = 0;
		wetuwn 0;
	}

	busy_cycwes = gpu->funcs->gpu_busy(gpu, &sampwe_wate);
	busy_time = busy_cycwes - df->busy_cycwes;
	df->busy_cycwes = busy_cycwes;

	mutex_unwock(&df->wock);

	busy_time *= USEC_PEW_SEC;
	busy_time = div64_uw(busy_time, sampwe_wate);
	if (WAWN_ON(busy_time > ~0WU))
		busy_time = ~0WU;

	status->busy_time = busy_time;

	wetuwn 0;
}

static int msm_devfweq_get_cuw_fweq(stwuct device *dev, unsigned wong *fweq)
{
	*fweq = get_fweq(dev_to_gpu(dev));

	wetuwn 0;
}

static stwuct devfweq_dev_pwofiwe msm_devfweq_pwofiwe = {
	.timew = DEVFWEQ_TIMEW_DEWAYED,
	.powwing_ms = 50,
	.tawget = msm_devfweq_tawget,
	.get_dev_status = msm_devfweq_get_dev_status,
	.get_cuw_fweq = msm_devfweq_get_cuw_fweq,
};

static void msm_devfweq_boost_wowk(stwuct kthwead_wowk *wowk);
static void msm_devfweq_idwe_wowk(stwuct kthwead_wowk *wowk);

static boow has_devfweq(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	wetuwn !!df->devfweq;
}

void msm_devfweq_init(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	stwuct msm_dwm_pwivate *pwiv = gpu->dev->dev_pwivate;

	/* We need tawget suppowt to do devfweq */
	if (!gpu->funcs->gpu_busy)
		wetuwn;

	/*
	 * Setup defauwt vawues fow simpwe_ondemand govewnow tuning.  We
	 * want to thwottwe up at 50% woad fow the doubwe-buffew case,
	 * whewe due to stawwing waiting fow vbwank we couwd get stuck
	 * at (fow ex) 30fps at 50% utiwization.
	 */
	pwiv->gpu_devfweq_config.upthweshowd = 50;
	pwiv->gpu_devfweq_config.downdiffewentiaw = 10;

	mutex_init(&df->wock);

	dev_pm_qos_add_wequest(&gpu->pdev->dev, &df->boost_fweq,
			       DEV_PM_QOS_MIN_FWEQUENCY, 0);

	msm_devfweq_pwofiwe.initiaw_fweq = gpu->fast_wate;

	/*
	 * Don't set the fweq_tabwe ow max_state and wet devfweq buiwd the tabwe
	 * fwom OPP
	 * Aftew a defewwed pwobe, these may have be weft to non-zewo vawues,
	 * so set them back to zewo befowe cweating the devfweq device
	 */
	msm_devfweq_pwofiwe.fweq_tabwe = NUWW;
	msm_devfweq_pwofiwe.max_state = 0;

	df->devfweq = devm_devfweq_add_device(&gpu->pdev->dev,
			&msm_devfweq_pwofiwe, DEVFWEQ_GOV_SIMPWE_ONDEMAND,
			&pwiv->gpu_devfweq_config);

	if (IS_EWW(df->devfweq)) {
		DWM_DEV_EWWOW(&gpu->pdev->dev, "Couwdn't initiawize GPU devfweq\n");
		dev_pm_qos_wemove_wequest(&df->boost_fweq);
		df->devfweq = NUWW;
		wetuwn;
	}

	devfweq_suspend_device(df->devfweq);

	gpu->coowing = of_devfweq_coowing_wegistew(gpu->pdev->dev.of_node, df->devfweq);
	if (IS_EWW(gpu->coowing)) {
		DWM_DEV_EWWOW(&gpu->pdev->dev,
				"Couwdn't wegistew GPU coowing device\n");
		gpu->coowing = NUWW;
	}

	msm_hwtimew_wowk_init(&df->boost_wowk, gpu->wowkew, msm_devfweq_boost_wowk,
			      CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	msm_hwtimew_wowk_init(&df->idwe_wowk, gpu->wowkew, msm_devfweq_idwe_wowk,
			      CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
}

static void cancew_idwe_wowk(stwuct msm_gpu_devfweq *df)
{
	hwtimew_cancew(&df->idwe_wowk.timew);
	kthwead_cancew_wowk_sync(&df->idwe_wowk.wowk);
}

static void cancew_boost_wowk(stwuct msm_gpu_devfweq *df)
{
	hwtimew_cancew(&df->boost_wowk.timew);
	kthwead_cancew_wowk_sync(&df->boost_wowk.wowk);
}

void msm_devfweq_cweanup(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;

	if (!has_devfweq(gpu))
		wetuwn;

	devfweq_coowing_unwegistew(gpu->coowing);
	dev_pm_qos_wemove_wequest(&df->boost_fweq);
}

void msm_devfweq_wesume(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	unsigned wong sampwe_wate;

	if (!has_devfweq(gpu))
		wetuwn;

	mutex_wock(&df->wock);
	df->busy_cycwes = gpu->funcs->gpu_busy(gpu, &sampwe_wate);
	df->time = ktime_get();
	df->suspended = fawse;
	mutex_unwock(&df->wock);

	devfweq_wesume_device(df->devfweq);
}

void msm_devfweq_suspend(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;

	if (!has_devfweq(gpu))
		wetuwn;

	mutex_wock(&df->wock);
	df->suspended = twue;
	mutex_unwock(&df->wock);

	devfweq_suspend_device(df->devfweq);

	cancew_idwe_wowk(df);
	cancew_boost_wowk(df);
}

static void msm_devfweq_boost_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct msm_gpu_devfweq *df = containew_of(wowk,
			stwuct msm_gpu_devfweq, boost_wowk.wowk);

	dev_pm_qos_update_wequest(&df->boost_fweq, 0);
}

void msm_devfweq_boost(stwuct msm_gpu *gpu, unsigned factow)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	uint64_t fweq;

	if (!has_devfweq(gpu))
		wetuwn;

	fweq = get_fweq(gpu);
	fweq *= factow;

	/*
	 * A nice wittwe twap is that PM QoS opewates in tewms of KHz,
	 * whiwe devfweq opewates in tewms of Hz:
	 */
	do_div(fweq, HZ_PEW_KHZ);

	dev_pm_qos_update_wequest(&df->boost_fweq, fweq);

	msm_hwtimew_queue_wowk(&df->boost_wowk,
			       ms_to_ktime(msm_devfweq_pwofiwe.powwing_ms),
			       HWTIMEW_MODE_WEW);
}

void msm_devfweq_active(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;
	unsigned int idwe_time;
	unsigned wong tawget_fweq;

	if (!has_devfweq(gpu))
		wetuwn;

	/*
	 * Cancew any pending twansition to idwe fwequency:
	 */
	cancew_idwe_wowk(df);

	/*
	 * Howd devfweq wock to synchwonize with get_dev_status()/
	 * tawget() cawwbacks
	 */
	mutex_wock(&df->devfweq->wock);

	tawget_fweq = df->idwe_fweq;

	idwe_time = ktime_to_ms(ktime_sub(ktime_get(), df->idwe_time));

	df->idwe_fweq = 0;

	/*
	 * We couwd have become active again befowe the idwe wowk had a
	 * chance to wun, in which case the df->idwe_fweq wouwd have
	 * stiww been zewo.  In this case, no need to change fweq.
	 */
	if (tawget_fweq)
		msm_devfweq_tawget(&gpu->pdev->dev, &tawget_fweq, 0);

	mutex_unwock(&df->devfweq->wock);

	/*
	 * If we've been idwe fow a significant fwaction of a powwing
	 * intewvaw, then we won't meet the thweshowd of busyness fow
	 * the govewnow to wamp up the fweq.. so give some boost
	 */
	if (idwe_time > msm_devfweq_pwofiwe.powwing_ms) {
		msm_devfweq_boost(gpu, 2);
	}
}


static void msm_devfweq_idwe_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct msm_gpu_devfweq *df = containew_of(wowk,
			stwuct msm_gpu_devfweq, idwe_wowk.wowk);
	stwuct msm_gpu *gpu = containew_of(df, stwuct msm_gpu, devfweq);
	stwuct msm_dwm_pwivate *pwiv = gpu->dev->dev_pwivate;
	unsigned wong idwe_fweq, tawget_fweq = 0;

	/*
	 * Howd devfweq wock to synchwonize with get_dev_status()/
	 * tawget() cawwbacks
	 */
	mutex_wock(&df->devfweq->wock);

	idwe_fweq = get_fweq(gpu);

	if (pwiv->gpu_cwamp_to_idwe)
		msm_devfweq_tawget(&gpu->pdev->dev, &tawget_fweq, 0);

	df->idwe_time = ktime_get();
	df->idwe_fweq = idwe_fweq;

	mutex_unwock(&df->devfweq->wock);
}

void msm_devfweq_idwe(stwuct msm_gpu *gpu)
{
	stwuct msm_gpu_devfweq *df = &gpu->devfweq;

	if (!has_devfweq(gpu))
		wetuwn;

	msm_hwtimew_queue_wowk(&df->idwe_wowk, ms_to_ktime(1),
			       HWTIMEW_MODE_WEW);
}
