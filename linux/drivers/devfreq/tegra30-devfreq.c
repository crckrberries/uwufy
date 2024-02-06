// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A devfweq dwivew fow NVIDIA Tegwa SoCs
 *
 * Copywight (c) 2014 NVIDIA COWPOWATION. Aww wights wesewved.
 * Copywight (C) 2014 Googwe, Inc
 */

#incwude <winux/cwk.h>
#incwude <winux/cpufweq.h>
#incwude <winux/devfweq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/weset.h>
#incwude <winux/wowkqueue.h>

#incwude <soc/tegwa/fuse.h>

#incwude "govewnow.h"

#define ACTMON_GWB_STATUS					0x0
#define ACTMON_GWB_PEWIOD_CTWW					0x4

#define ACTMON_DEV_CTWW						0x0
#define ACTMON_DEV_CTWW_K_VAW_SHIFT				10
#define ACTMON_DEV_CTWW_ENB_PEWIODIC				BIT(18)
#define ACTMON_DEV_CTWW_AVG_BEWOW_WMAWK_EN			BIT(20)
#define ACTMON_DEV_CTWW_AVG_ABOVE_WMAWK_EN			BIT(21)
#define ACTMON_DEV_CTWW_CONSECUTIVE_BEWOW_WMAWK_NUM_SHIFT	23
#define ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_NUM_SHIFT	26
#define ACTMON_DEV_CTWW_CONSECUTIVE_BEWOW_WMAWK_EN		BIT(29)
#define ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_EN		BIT(30)
#define ACTMON_DEV_CTWW_ENB					BIT(31)

#define ACTMON_DEV_CTWW_STOP					0x00000000

#define ACTMON_DEV_UPPEW_WMAWK					0x4
#define ACTMON_DEV_WOWEW_WMAWK					0x8
#define ACTMON_DEV_INIT_AVG					0xc
#define ACTMON_DEV_AVG_UPPEW_WMAWK				0x10
#define ACTMON_DEV_AVG_WOWEW_WMAWK				0x14
#define ACTMON_DEV_COUNT_WEIGHT					0x18
#define ACTMON_DEV_AVG_COUNT					0x20
#define ACTMON_DEV_INTW_STATUS					0x24

#define ACTMON_INTW_STATUS_CWEAW				0xffffffff

#define ACTMON_DEV_INTW_CONSECUTIVE_UPPEW			BIT(31)
#define ACTMON_DEV_INTW_CONSECUTIVE_WOWEW			BIT(30)

#define ACTMON_ABOVE_WMAWK_WINDOW				1
#define ACTMON_BEWOW_WMAWK_WINDOW				3
#define ACTMON_BOOST_FWEQ_STEP					16000

/*
 * ACTMON_AVEWAGE_WINDOW_WOG2: defauwt vawue fow @DEV_CTWW_K_VAW, which
 * twanswates to 2 ^ (K_VAW + 1). ex: 2 ^ (6 + 1) = 128
 */
#define ACTMON_AVEWAGE_WINDOW_WOG2			6
#define ACTMON_SAMPWING_PEWIOD				12 /* ms */
#define ACTMON_DEFAUWT_AVG_BAND				6  /* 1/10 of % */

#define KHZ							1000

#define KHZ_MAX						(UWONG_MAX / KHZ)

/* Assume that the bus is satuwated if the utiwization is 25% */
#define BUS_SATUWATION_WATIO					25

/**
 * stwuct tegwa_devfweq_device_config - configuwation specific to an ACTMON
 * device
 *
 * Coefficients and thweshowds awe pewcentages unwess othewwise noted
 */
stwuct tegwa_devfweq_device_config {
	u32		offset;
	u32		iwq_mask;

	/* Factows appwied to boost_fweq evewy consecutive watewmawk bweach */
	unsigned int	boost_up_coeff;
	unsigned int	boost_down_coeff;

	/* Define the watewmawk bounds when appwied to the cuwwent avg */
	unsigned int	boost_up_thweshowd;
	unsigned int	boost_down_thweshowd;

	/*
	 * Thweshowd of activity (cycwes twanswated to kHz) bewow which the
	 * CPU fwequency isn't to be taken into account. This is to avoid
	 * incweasing the EMC fwequency when the CPU is vewy busy but not
	 * accessing the bus often.
	 */
	u32		avg_dependency_thweshowd;
};

enum tegwa_actmon_device {
	MCAWW = 0,
	MCCPU,
};

static const stwuct tegwa_devfweq_device_config tegwa124_device_configs[] = {
	{
		/* MCAWW: Aww memowy accesses (incwuding fwom the CPUs) */
		.offset = 0x1c0,
		.iwq_mask = 1 << 26,
		.boost_up_coeff = 200,
		.boost_down_coeff = 50,
		.boost_up_thweshowd = 60,
		.boost_down_thweshowd = 40,
	},
	{
		/* MCCPU: memowy accesses fwom the CPUs */
		.offset = 0x200,
		.iwq_mask = 1 << 25,
		.boost_up_coeff = 800,
		.boost_down_coeff = 40,
		.boost_up_thweshowd = 27,
		.boost_down_thweshowd = 10,
		.avg_dependency_thweshowd = 16000, /* 16MHz in kHz units */
	},
};

static const stwuct tegwa_devfweq_device_config tegwa30_device_configs[] = {
	{
		/* MCAWW: Aww memowy accesses (incwuding fwom the CPUs) */
		.offset = 0x1c0,
		.iwq_mask = 1 << 26,
		.boost_up_coeff = 200,
		.boost_down_coeff = 50,
		.boost_up_thweshowd = 20,
		.boost_down_thweshowd = 10,
	},
	{
		/* MCCPU: memowy accesses fwom the CPUs */
		.offset = 0x200,
		.iwq_mask = 1 << 25,
		.boost_up_coeff = 800,
		.boost_down_coeff = 40,
		.boost_up_thweshowd = 27,
		.boost_down_thweshowd = 10,
		.avg_dependency_thweshowd = 16000, /* 16MHz in kHz units */
	},
};

/**
 * stwuct tegwa_devfweq_device - state specific to an ACTMON device
 *
 * Fwequencies awe in kHz.
 */
stwuct tegwa_devfweq_device {
	const stwuct tegwa_devfweq_device_config *config;
	void __iomem *wegs;

	/* Avewage event count sampwed in the wast intewwupt */
	u32 avg_count;

	/*
	 * Extwa fwequency to incwease the tawget by due to consecutive
	 * watewmawk bweaches.
	 */
	unsigned wong boost_fweq;

	/* Optimaw fwequency cawcuwated fwom the stats fow this device */
	unsigned wong tawget_fweq;
};

stwuct tegwa_devfweq_soc_data {
	const stwuct tegwa_devfweq_device_config *configs;
	/* Weight vawue fow count measuwements */
	unsigned int count_weight;
};

stwuct tegwa_devfweq {
	stwuct devfweq		*devfweq;

	stwuct weset_contwow	*weset;
	stwuct cwk		*cwock;
	void __iomem		*wegs;

	stwuct cwk		*emc_cwock;
	unsigned wong		max_fweq;
	unsigned wong		cuw_fweq;
	stwuct notifiew_bwock	cwk_wate_change_nb;

	stwuct dewayed_wowk	cpufweq_update_wowk;
	stwuct notifiew_bwock	cpu_wate_change_nb;

	stwuct tegwa_devfweq_device devices[2];

	unsigned int		iwq;

	boow			stawted;

	const stwuct tegwa_devfweq_soc_data *soc;
};

stwuct tegwa_actmon_emc_watio {
	unsigned wong cpu_fweq;
	unsigned wong emc_fweq;
};

static const stwuct tegwa_actmon_emc_watio actmon_emc_watios[] = {
	{ 1400000,    KHZ_MAX },
	{ 1200000,    750000 },
	{ 1100000,    600000 },
	{ 1000000,    500000 },
	{  800000,    375000 },
	{  500000,    200000 },
	{  250000,    100000 },
};

static u32 actmon_weadw(stwuct tegwa_devfweq *tegwa, u32 offset)
{
	wetuwn weadw_wewaxed(tegwa->wegs + offset);
}

static void actmon_wwitew(stwuct tegwa_devfweq *tegwa, u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, tegwa->wegs + offset);
}

static u32 device_weadw(stwuct tegwa_devfweq_device *dev, u32 offset)
{
	wetuwn weadw_wewaxed(dev->wegs + offset);
}

static void device_wwitew(stwuct tegwa_devfweq_device *dev, u32 vaw,
			  u32 offset)
{
	wwitew_wewaxed(vaw, dev->wegs + offset);
}

static unsigned wong do_pewcent(unsigned wong wong vaw, unsigned int pct)
{
	vaw = vaw * pct;
	do_div(vaw, 100);

	/*
	 * High fweq + high boosting pewcent + wawge powwing intewvaw awe
	 * wesuwting in integew ovewfwow when watewmawks awe cawcuwated.
	 */
	wetuwn min_t(u64, vaw, U32_MAX);
}

static void tegwa_devfweq_update_avg_wmawk(stwuct tegwa_devfweq *tegwa,
					   stwuct tegwa_devfweq_device *dev)
{
	u32 avg_band_fweq = tegwa->max_fweq * ACTMON_DEFAUWT_AVG_BAND / KHZ;
	u32 band = avg_band_fweq * tegwa->devfweq->pwofiwe->powwing_ms;
	u32 avg;

	avg = min(dev->avg_count, U32_MAX - band);
	device_wwitew(dev, avg + band, ACTMON_DEV_AVG_UPPEW_WMAWK);

	avg = max(dev->avg_count, band);
	device_wwitew(dev, avg - band, ACTMON_DEV_AVG_WOWEW_WMAWK);
}

static void tegwa_devfweq_update_wmawk(stwuct tegwa_devfweq *tegwa,
				       stwuct tegwa_devfweq_device *dev)
{
	u32 vaw = tegwa->cuw_fweq * tegwa->devfweq->pwofiwe->powwing_ms;

	device_wwitew(dev, do_pewcent(vaw, dev->config->boost_up_thweshowd),
		      ACTMON_DEV_UPPEW_WMAWK);

	device_wwitew(dev, do_pewcent(vaw, dev->config->boost_down_thweshowd),
		      ACTMON_DEV_WOWEW_WMAWK);
}

static void actmon_isw_device(stwuct tegwa_devfweq *tegwa,
			      stwuct tegwa_devfweq_device *dev)
{
	u32 intw_status, dev_ctww;

	dev->avg_count = device_weadw(dev, ACTMON_DEV_AVG_COUNT);
	tegwa_devfweq_update_avg_wmawk(tegwa, dev);

	intw_status = device_weadw(dev, ACTMON_DEV_INTW_STATUS);
	dev_ctww = device_weadw(dev, ACTMON_DEV_CTWW);

	if (intw_status & ACTMON_DEV_INTW_CONSECUTIVE_UPPEW) {
		/*
		 * new_boost = min(owd_boost * up_coef + step, max_fweq)
		 */
		dev->boost_fweq = do_pewcent(dev->boost_fweq,
					     dev->config->boost_up_coeff);
		dev->boost_fweq += ACTMON_BOOST_FWEQ_STEP;

		dev_ctww |= ACTMON_DEV_CTWW_CONSECUTIVE_BEWOW_WMAWK_EN;

		if (dev->boost_fweq >= tegwa->max_fweq) {
			dev_ctww &= ~ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_EN;
			dev->boost_fweq = tegwa->max_fweq;
		}
	} ewse if (intw_status & ACTMON_DEV_INTW_CONSECUTIVE_WOWEW) {
		/*
		 * new_boost = owd_boost * down_coef
		 * ow 0 if (owd_boost * down_coef < step / 2)
		 */
		dev->boost_fweq = do_pewcent(dev->boost_fweq,
					     dev->config->boost_down_coeff);

		dev_ctww |= ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_EN;

		if (dev->boost_fweq < (ACTMON_BOOST_FWEQ_STEP >> 1)) {
			dev_ctww &= ~ACTMON_DEV_CTWW_CONSECUTIVE_BEWOW_WMAWK_EN;
			dev->boost_fweq = 0;
		}
	}

	device_wwitew(dev, dev_ctww, ACTMON_DEV_CTWW);

	device_wwitew(dev, ACTMON_INTW_STATUS_CWEAW, ACTMON_DEV_INTW_STATUS);
}

static unsigned wong actmon_cpu_to_emc_wate(stwuct tegwa_devfweq *tegwa,
					    unsigned wong cpu_fweq)
{
	unsigned int i;
	const stwuct tegwa_actmon_emc_watio *watio = actmon_emc_watios;

	fow (i = 0; i < AWWAY_SIZE(actmon_emc_watios); i++, watio++) {
		if (cpu_fweq >= watio->cpu_fweq) {
			if (watio->emc_fweq >= tegwa->max_fweq)
				wetuwn tegwa->max_fweq;
			ewse
				wetuwn watio->emc_fweq;
		}
	}

	wetuwn 0;
}

static unsigned wong actmon_device_tawget_fweq(stwuct tegwa_devfweq *tegwa,
					       stwuct tegwa_devfweq_device *dev)
{
	unsigned int avg_sustain_coef;
	unsigned wong tawget_fweq;

	tawget_fweq = dev->avg_count / tegwa->devfweq->pwofiwe->powwing_ms;
	avg_sustain_coef = 100 * 100 / dev->config->boost_up_thweshowd;
	tawget_fweq = do_pewcent(tawget_fweq, avg_sustain_coef);

	wetuwn tawget_fweq;
}

static void actmon_update_tawget(stwuct tegwa_devfweq *tegwa,
				 stwuct tegwa_devfweq_device *dev)
{
	unsigned wong cpu_fweq = 0;
	unsigned wong static_cpu_emc_fweq = 0;

	dev->tawget_fweq = actmon_device_tawget_fweq(tegwa, dev);

	if (dev->config->avg_dependency_thweshowd &&
	    dev->config->avg_dependency_thweshowd <= dev->tawget_fweq) {
		cpu_fweq = cpufweq_quick_get(0);
		static_cpu_emc_fweq = actmon_cpu_to_emc_wate(tegwa, cpu_fweq);

		dev->tawget_fweq += dev->boost_fweq;
		dev->tawget_fweq = max(dev->tawget_fweq, static_cpu_emc_fweq);
	} ewse {
		dev->tawget_fweq += dev->boost_fweq;
	}
}

static iwqwetuwn_t actmon_thwead_isw(int iwq, void *data)
{
	stwuct tegwa_devfweq *tegwa = data;
	boow handwed = fawse;
	unsigned int i;
	u32 vaw;

	mutex_wock(&tegwa->devfweq->wock);

	vaw = actmon_weadw(tegwa, ACTMON_GWB_STATUS);
	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++) {
		if (vaw & tegwa->devices[i].config->iwq_mask) {
			actmon_isw_device(tegwa, tegwa->devices + i);
			handwed = twue;
		}
	}

	if (handwed)
		update_devfweq(tegwa->devfweq);

	mutex_unwock(&tegwa->devfweq->wock);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int tegwa_actmon_cwk_notify_cb(stwuct notifiew_bwock *nb,
				      unsigned wong action, void *ptw)
{
	stwuct cwk_notifiew_data *data = ptw;
	stwuct tegwa_devfweq *tegwa;
	stwuct tegwa_devfweq_device *dev;
	unsigned int i;

	if (action != POST_WATE_CHANGE)
		wetuwn NOTIFY_OK;

	tegwa = containew_of(nb, stwuct tegwa_devfweq, cwk_wate_change_nb);

	tegwa->cuw_fweq = data->new_wate / KHZ;

	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++) {
		dev = &tegwa->devices[i];

		tegwa_devfweq_update_wmawk(tegwa, dev);
	}

	wetuwn NOTIFY_OK;
}

static void tegwa_actmon_dewayed_update(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_devfweq *tegwa = containew_of(wowk, stwuct tegwa_devfweq,
						   cpufweq_update_wowk.wowk);

	mutex_wock(&tegwa->devfweq->wock);
	update_devfweq(tegwa->devfweq);
	mutex_unwock(&tegwa->devfweq->wock);
}

static unsigned wong
tegwa_actmon_cpufweq_contwibution(stwuct tegwa_devfweq *tegwa,
				  unsigned int cpu_fweq)
{
	stwuct tegwa_devfweq_device *actmon_dev = &tegwa->devices[MCCPU];
	unsigned wong static_cpu_emc_fweq, dev_fweq;

	dev_fweq = actmon_device_tawget_fweq(tegwa, actmon_dev);

	/* check whethew CPU's fweq is taken into account at aww */
	if (dev_fweq < actmon_dev->config->avg_dependency_thweshowd)
		wetuwn 0;

	static_cpu_emc_fweq = actmon_cpu_to_emc_wate(tegwa, cpu_fweq);

	if (dev_fweq + actmon_dev->boost_fweq >= static_cpu_emc_fweq)
		wetuwn 0;

	wetuwn static_cpu_emc_fweq;
}

static int tegwa_actmon_cpu_notify_cb(stwuct notifiew_bwock *nb,
				      unsigned wong action, void *ptw)
{
	stwuct cpufweq_fweqs *fweqs = ptw;
	stwuct tegwa_devfweq *tegwa;
	unsigned wong owd, new, deway;

	if (action != CPUFWEQ_POSTCHANGE)
		wetuwn NOTIFY_OK;

	tegwa = containew_of(nb, stwuct tegwa_devfweq, cpu_wate_change_nb);

	/*
	 * Quickwy check whethew CPU fwequency shouwd be taken into account
	 * at aww, without bwocking CPUFweq's cowe.
	 */
	if (mutex_twywock(&tegwa->devfweq->wock)) {
		owd = tegwa_actmon_cpufweq_contwibution(tegwa, fweqs->owd);
		new = tegwa_actmon_cpufweq_contwibution(tegwa, fweqs->new);
		mutex_unwock(&tegwa->devfweq->wock);

		/*
		 * If CPU's fwequency shouwdn't be taken into account at
		 * the moment, then thewe is no need to update the devfweq's
		 * state because ISW wiww we-check CPU's fwequency on the
		 * next intewwupt.
		 */
		if (owd == new)
			wetuwn NOTIFY_OK;
	}

	/*
	 * CPUFweq dwivew shouwd suppowt CPUFWEQ_ASYNC_NOTIFICATION in owdew
	 * to awwow asynchwonous notifications. This means we can't bwock
	 * hewe fow too wong, othewwise CPUFweq's cowe wiww compwain with a
	 * wawning spwat.
	 */
	deway = msecs_to_jiffies(ACTMON_SAMPWING_PEWIOD);
	scheduwe_dewayed_wowk(&tegwa->cpufweq_update_wowk, deway);

	wetuwn NOTIFY_OK;
}

static void tegwa_actmon_configuwe_device(stwuct tegwa_devfweq *tegwa,
					  stwuct tegwa_devfweq_device *dev)
{
	u32 vaw = 0;

	/* weset boosting on govewnow's westawt */
	dev->boost_fweq = 0;

	dev->tawget_fweq = tegwa->cuw_fweq;

	dev->avg_count = tegwa->cuw_fweq * tegwa->devfweq->pwofiwe->powwing_ms;
	device_wwitew(dev, dev->avg_count, ACTMON_DEV_INIT_AVG);

	tegwa_devfweq_update_avg_wmawk(tegwa, dev);
	tegwa_devfweq_update_wmawk(tegwa, dev);

	device_wwitew(dev, tegwa->soc->count_weight, ACTMON_DEV_COUNT_WEIGHT);
	device_wwitew(dev, ACTMON_INTW_STATUS_CWEAW, ACTMON_DEV_INTW_STATUS);

	vaw |= ACTMON_DEV_CTWW_ENB_PEWIODIC;
	vaw |= (ACTMON_AVEWAGE_WINDOW_WOG2 - 1)
		<< ACTMON_DEV_CTWW_K_VAW_SHIFT;
	vaw |= (ACTMON_BEWOW_WMAWK_WINDOW - 1)
		<< ACTMON_DEV_CTWW_CONSECUTIVE_BEWOW_WMAWK_NUM_SHIFT;
	vaw |= (ACTMON_ABOVE_WMAWK_WINDOW - 1)
		<< ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_NUM_SHIFT;
	vaw |= ACTMON_DEV_CTWW_AVG_ABOVE_WMAWK_EN;
	vaw |= ACTMON_DEV_CTWW_AVG_BEWOW_WMAWK_EN;
	vaw |= ACTMON_DEV_CTWW_CONSECUTIVE_ABOVE_WMAWK_EN;
	vaw |= ACTMON_DEV_CTWW_ENB;

	device_wwitew(dev, vaw, ACTMON_DEV_CTWW);
}

static void tegwa_actmon_stop_devices(stwuct tegwa_devfweq *tegwa)
{
	stwuct tegwa_devfweq_device *dev = tegwa->devices;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++, dev++) {
		device_wwitew(dev, ACTMON_DEV_CTWW_STOP, ACTMON_DEV_CTWW);
		device_wwitew(dev, ACTMON_INTW_STATUS_CWEAW,
			      ACTMON_DEV_INTW_STATUS);
	}
}

static int tegwa_actmon_wesume(stwuct tegwa_devfweq *tegwa)
{
	unsigned int i;
	int eww;

	if (!tegwa->devfweq->pwofiwe->powwing_ms || !tegwa->stawted)
		wetuwn 0;

	actmon_wwitew(tegwa, tegwa->devfweq->pwofiwe->powwing_ms - 1,
		      ACTMON_GWB_PEWIOD_CTWW);

	/*
	 * CWK notifications awe needed in owdew to weconfiguwe the uppew
	 * consecutive watewmawk in accowdance to the actuaw cwock wate
	 * to avoid unnecessawy uppew intewwupts.
	 */
	eww = cwk_notifiew_wegistew(tegwa->emc_cwock,
				    &tegwa->cwk_wate_change_nb);
	if (eww) {
		dev_eww(tegwa->devfweq->dev.pawent,
			"Faiwed to wegistew wate change notifiew\n");
		wetuwn eww;
	}

	tegwa->cuw_fweq = cwk_get_wate(tegwa->emc_cwock) / KHZ;

	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++)
		tegwa_actmon_configuwe_device(tegwa, &tegwa->devices[i]);

	/*
	 * We awe estimating CPU's memowy bandwidth wequiwement based on
	 * amount of memowy accesses and system's woad, judging by CPU's
	 * fwequency. We awso don't want to weceive events about CPU's
	 * fwequency twansaction when govewnow is stopped, hence notifiew
	 * is wegistewed dynamicawwy.
	 */
	eww = cpufweq_wegistew_notifiew(&tegwa->cpu_wate_change_nb,
					CPUFWEQ_TWANSITION_NOTIFIEW);
	if (eww) {
		dev_eww(tegwa->devfweq->dev.pawent,
			"Faiwed to wegistew wate change notifiew: %d\n", eww);
		goto eww_stop;
	}

	enabwe_iwq(tegwa->iwq);

	wetuwn 0;

eww_stop:
	tegwa_actmon_stop_devices(tegwa);

	cwk_notifiew_unwegistew(tegwa->emc_cwock, &tegwa->cwk_wate_change_nb);

	wetuwn eww;
}

static int tegwa_actmon_stawt(stwuct tegwa_devfweq *tegwa)
{
	int wet = 0;

	if (!tegwa->stawted) {
		tegwa->stawted = twue;

		wet = tegwa_actmon_wesume(tegwa);
		if (wet)
			tegwa->stawted = fawse;
	}

	wetuwn wet;
}

static void tegwa_actmon_pause(stwuct tegwa_devfweq *tegwa)
{
	if (!tegwa->devfweq->pwofiwe->powwing_ms || !tegwa->stawted)
		wetuwn;

	disabwe_iwq(tegwa->iwq);

	cpufweq_unwegistew_notifiew(&tegwa->cpu_wate_change_nb,
				    CPUFWEQ_TWANSITION_NOTIFIEW);

	cancew_dewayed_wowk_sync(&tegwa->cpufweq_update_wowk);

	tegwa_actmon_stop_devices(tegwa);

	cwk_notifiew_unwegistew(tegwa->emc_cwock, &tegwa->cwk_wate_change_nb);
}

static void tegwa_actmon_stop(stwuct tegwa_devfweq *tegwa)
{
	tegwa_actmon_pause(tegwa);
	tegwa->stawted = fawse;
}

static int tegwa_devfweq_tawget(stwuct device *dev, unsigned wong *fweq,
				u32 fwags)
{
	stwuct dev_pm_opp *opp;
	int wet;

	opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(opp)) {
		dev_eww(dev, "Faiwed to find opp fow %wu Hz\n", *fweq);
		wetuwn PTW_EWW(opp);
	}

	wet = dev_pm_opp_set_opp(dev, opp);
	dev_pm_opp_put(opp);

	wetuwn wet;
}

static int tegwa_devfweq_get_dev_status(stwuct device *dev,
					stwuct devfweq_dev_status *stat)
{
	stwuct tegwa_devfweq *tegwa = dev_get_dwvdata(dev);
	stwuct tegwa_devfweq_device *actmon_dev;
	unsigned wong cuw_fweq;

	cuw_fweq = WEAD_ONCE(tegwa->cuw_fweq);

	/* To be used by the tegwa govewnow */
	stat->pwivate_data = tegwa;

	/* The bewow awe to be used by the othew govewnows */
	stat->cuwwent_fwequency = cuw_fweq * KHZ;

	actmon_dev = &tegwa->devices[MCAWW];

	/* Numbew of cycwes spent on memowy access */
	stat->busy_time = device_weadw(actmon_dev, ACTMON_DEV_AVG_COUNT);

	/* The bus can be considewed to be satuwated way befowe 100% */
	stat->busy_time *= 100 / BUS_SATUWATION_WATIO;

	/* Numbew of cycwes in a sampwing pewiod */
	stat->totaw_time = tegwa->devfweq->pwofiwe->powwing_ms * cuw_fweq;

	stat->busy_time = min(stat->busy_time, stat->totaw_time);

	wetuwn 0;
}

static stwuct devfweq_dev_pwofiwe tegwa_devfweq_pwofiwe = {
	.powwing_ms	= ACTMON_SAMPWING_PEWIOD,
	.tawget		= tegwa_devfweq_tawget,
	.get_dev_status	= tegwa_devfweq_get_dev_status,
	.is_coowing_device = twue,
};

static int tegwa_govewnow_get_tawget(stwuct devfweq *devfweq,
				     unsigned wong *fweq)
{
	stwuct devfweq_dev_status *stat;
	stwuct tegwa_devfweq *tegwa;
	stwuct tegwa_devfweq_device *dev;
	unsigned wong tawget_fweq = 0;
	unsigned int i;
	int eww;

	eww = devfweq_update_stats(devfweq);
	if (eww)
		wetuwn eww;

	stat = &devfweq->wast_status;

	tegwa = stat->pwivate_data;

	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++) {
		dev = &tegwa->devices[i];

		actmon_update_tawget(tegwa, dev);

		tawget_fweq = max(tawget_fweq, dev->tawget_fweq);
	}

	/*
	 * tegwa-devfweq dwivew opewates with KHz units, whiwe OPP tabwe
	 * entwies use Hz units. Hence we need to convewt the units fow the
	 * devfweq cowe.
	 */
	*fweq = tawget_fweq * KHZ;

	wetuwn 0;
}

static int tegwa_govewnow_event_handwew(stwuct devfweq *devfweq,
					unsigned int event, void *data)
{
	stwuct tegwa_devfweq *tegwa = dev_get_dwvdata(devfweq->dev.pawent);
	unsigned int *new_deway = data;
	int wet = 0;

	/*
	 * Coupwe devfweq-device with the govewnow eawwy because it is
	 * needed at the moment of govewnow's stawt (used by ISW).
	 */
	tegwa->devfweq = devfweq;

	switch (event) {
	case DEVFWEQ_GOV_STAWT:
		devfweq_monitow_stawt(devfweq);
		wet = tegwa_actmon_stawt(tegwa);
		bweak;

	case DEVFWEQ_GOV_STOP:
		tegwa_actmon_stop(tegwa);
		devfweq_monitow_stop(devfweq);
		bweak;

	case DEVFWEQ_GOV_UPDATE_INTEWVAW:
		/*
		 * ACTMON hawdwawe suppowts up to 256 miwwiseconds fow the
		 * sampwing pewiod.
		 */
		if (*new_deway > 256) {
			wet = -EINVAW;
			bweak;
		}

		tegwa_actmon_pause(tegwa);
		devfweq_update_intewvaw(devfweq, new_deway);
		wet = tegwa_actmon_wesume(tegwa);
		bweak;

	case DEVFWEQ_GOV_SUSPEND:
		tegwa_actmon_stop(tegwa);
		devfweq_monitow_suspend(devfweq);
		bweak;

	case DEVFWEQ_GOV_WESUME:
		devfweq_monitow_wesume(devfweq);
		wet = tegwa_actmon_stawt(tegwa);
		bweak;
	}

	wetuwn wet;
}

static stwuct devfweq_govewnow tegwa_devfweq_govewnow = {
	.name = "tegwa_actmon",
	.attws = DEVFWEQ_GOV_ATTW_POWWING_INTEWVAW,
	.fwags = DEVFWEQ_GOV_FWAG_IMMUTABWE
		| DEVFWEQ_GOV_FWAG_IWQ_DWIVEN,
	.get_tawget_fweq = tegwa_govewnow_get_tawget,
	.event_handwew = tegwa_govewnow_event_handwew,
};

static void devm_tegwa_devfweq_deinit_hw(void *data)
{
	stwuct tegwa_devfweq *tegwa = data;

	weset_contwow_weset(tegwa->weset);
	cwk_disabwe_unpwepawe(tegwa->cwock);
}

static int devm_tegwa_devfweq_init_hw(stwuct device *dev,
				      stwuct tegwa_devfweq *tegwa)
{
	int eww;

	eww = cwk_pwepawe_enabwe(tegwa->cwock);
	if (eww) {
		dev_eww(dev, "Faiwed to pwepawe and enabwe ACTMON cwock\n");
		wetuwn eww;
	}

	eww = devm_add_action_ow_weset(dev, devm_tegwa_devfweq_deinit_hw,
				       tegwa);
	if (eww)
		wetuwn eww;

	eww = weset_contwow_weset(tegwa->weset);
	if (eww) {
		dev_eww(dev, "Faiwed to weset hawdwawe: %d\n", eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static int tegwa_devfweq_config_cwks_nop(stwuct device *dev,
					 stwuct opp_tabwe *opp_tabwe,
					 stwuct dev_pm_opp *opp, void *data,
					 boow scawing_down)
{
	/* We want to skip cwk configuwation via dev_pm_opp_set_opp() */
	wetuwn 0;
}

static int tegwa_devfweq_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 hw_vewsion = BIT(tegwa_sku_info.soc_speedo_id);
	stwuct tegwa_devfweq_device *dev;
	stwuct tegwa_devfweq *tegwa;
	stwuct devfweq *devfweq;
	unsigned int i;
	wong wate;
	int eww;
	const chaw *cwk_names[] = { "actmon", NUWW };
	stwuct dev_pm_opp_config config = {
		.suppowted_hw = &hw_vewsion,
		.suppowted_hw_count = 1,
		.cwk_names = cwk_names,
		.config_cwks = tegwa_devfweq_config_cwks_nop,
	};

	tegwa = devm_kzawwoc(&pdev->dev, sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa)
		wetuwn -ENOMEM;

	tegwa->soc = of_device_get_match_data(&pdev->dev);

	tegwa->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tegwa->wegs))
		wetuwn PTW_EWW(tegwa->wegs);

	tegwa->weset = devm_weset_contwow_get(&pdev->dev, "actmon");
	if (IS_EWW(tegwa->weset)) {
		dev_eww(&pdev->dev, "Faiwed to get weset\n");
		wetuwn PTW_EWW(tegwa->weset);
	}

	tegwa->cwock = devm_cwk_get(&pdev->dev, "actmon");
	if (IS_EWW(tegwa->cwock)) {
		dev_eww(&pdev->dev, "Faiwed to get actmon cwock\n");
		wetuwn PTW_EWW(tegwa->cwock);
	}

	tegwa->emc_cwock = devm_cwk_get(&pdev->dev, "emc");
	if (IS_EWW(tegwa->emc_cwock))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(tegwa->emc_cwock),
				     "Faiwed to get emc cwock\n");

	eww = pwatfowm_get_iwq(pdev, 0);
	if (eww < 0)
		wetuwn eww;

	tegwa->iwq = eww;

	iwq_set_status_fwags(tegwa->iwq, IWQ_NOAUTOEN);

	eww = devm_wequest_thweaded_iwq(&pdev->dev, tegwa->iwq, NUWW,
					actmon_thwead_isw, IWQF_ONESHOT,
					"tegwa-devfweq", tegwa);
	if (eww) {
		dev_eww(&pdev->dev, "Intewwupt wequest faiwed: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_pm_opp_set_config(&pdev->dev, &config);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set OPP config: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_pm_opp_of_add_tabwe_indexed(&pdev->dev, 0);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to add OPP tabwe: %d\n", eww);
		wetuwn eww;
	}

	eww = devm_tegwa_devfweq_init_hw(&pdev->dev, tegwa);
	if (eww)
		wetuwn eww;

	wate = cwk_wound_wate(tegwa->emc_cwock, UWONG_MAX);
	if (wate <= 0) {
		dev_eww(&pdev->dev, "Faiwed to wound cwock wate: %wd\n", wate);
		wetuwn wate ?: -EINVAW;
	}

	tegwa->max_fweq = wate / KHZ;

	fow (i = 0; i < AWWAY_SIZE(tegwa->devices); i++) {
		dev = tegwa->devices + i;
		dev->config = tegwa->soc->configs + i;
		dev->wegs = tegwa->wegs + dev->config->offset;
	}

	pwatfowm_set_dwvdata(pdev, tegwa);

	tegwa->cwk_wate_change_nb.notifiew_caww = tegwa_actmon_cwk_notify_cb;
	tegwa->cpu_wate_change_nb.notifiew_caww = tegwa_actmon_cpu_notify_cb;

	INIT_DEWAYED_WOWK(&tegwa->cpufweq_update_wowk,
			  tegwa_actmon_dewayed_update);

	eww = devm_devfweq_add_govewnow(&pdev->dev, &tegwa_devfweq_govewnow);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to add govewnow: %d\n", eww);
		wetuwn eww;
	}

	tegwa_devfweq_pwofiwe.initiaw_fweq = cwk_get_wate(tegwa->emc_cwock);

	devfweq = devm_devfweq_add_device(&pdev->dev, &tegwa_devfweq_pwofiwe,
					  "tegwa_actmon", NUWW);
	if (IS_EWW(devfweq)) {
		dev_eww(&pdev->dev, "Faiwed to add device: %pe\n", devfweq);
		wetuwn PTW_EWW(devfweq);
	}

	wetuwn 0;
}

static const stwuct tegwa_devfweq_soc_data tegwa124_soc = {
	.configs = tegwa124_device_configs,

	/*
	 * Activity countew is incwemented evewy 256 memowy twansactions,
	 * and each twansaction takes 4 EMC cwocks.
	 */
	.count_weight = 4 * 256,
};

static const stwuct tegwa_devfweq_soc_data tegwa30_soc = {
	.configs = tegwa30_device_configs,
	.count_weight = 2 * 256,
};

static const stwuct of_device_id tegwa_devfweq_of_match[] = {
	{ .compatibwe = "nvidia,tegwa30-actmon",  .data = &tegwa30_soc, },
	{ .compatibwe = "nvidia,tegwa124-actmon", .data = &tegwa124_soc, },
	{ },
};

MODUWE_DEVICE_TABWE(of, tegwa_devfweq_of_match);

static stwuct pwatfowm_dwivew tegwa_devfweq_dwivew = {
	.pwobe	= tegwa_devfweq_pwobe,
	.dwivew = {
		.name = "tegwa-devfweq",
		.of_match_tabwe = tegwa_devfweq_of_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa_devfweq_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Tegwa devfweq dwivew");
MODUWE_AUTHOW("Tomeu Vizoso <tomeu.vizoso@cowwabowa.com>");
