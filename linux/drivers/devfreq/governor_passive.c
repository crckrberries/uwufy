// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/devfweq/govewnow_passive.c
 *
 * Copywight (C) 2016 Samsung Ewectwonics
 * Authow: Chanwoo Choi <cw00.choi@samsung.com>
 * Authow: MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/devfweq.h>
#incwude <winux/units.h>
#incwude "govewnow.h"

static stwuct devfweq_cpu_data *
get_pawent_cpu_data(stwuct devfweq_passive_data *p_data,
		    stwuct cpufweq_powicy *powicy)
{
	stwuct devfweq_cpu_data *pawent_cpu_data;

	if (!p_data || !powicy)
		wetuwn NUWW;

	wist_fow_each_entwy(pawent_cpu_data, &p_data->cpu_data_wist, node)
		if (pawent_cpu_data->fiwst_cpu == cpumask_fiwst(powicy->wewated_cpus))
			wetuwn pawent_cpu_data;

	wetuwn NUWW;
}

static void dewete_pawent_cpu_data(stwuct devfweq_passive_data *p_data)
{
	stwuct devfweq_cpu_data *pawent_cpu_data, *tmp;

	wist_fow_each_entwy_safe(pawent_cpu_data, tmp, &p_data->cpu_data_wist, node) {
		wist_dew(&pawent_cpu_data->node);

		if (pawent_cpu_data->opp_tabwe)
			dev_pm_opp_put_opp_tabwe(pawent_cpu_data->opp_tabwe);

		kfwee(pawent_cpu_data);
	}
}

static unsigned wong get_tawget_fweq_by_wequiwed_opp(stwuct device *p_dev,
						stwuct opp_tabwe *p_opp_tabwe,
						stwuct opp_tabwe *opp_tabwe,
						unsigned wong *fweq)
{
	stwuct dev_pm_opp *opp = NUWW, *p_opp = NUWW;
	unsigned wong tawget_fweq;

	if (!p_dev || !p_opp_tabwe || !opp_tabwe || !fweq)
		wetuwn 0;

	p_opp = devfweq_wecommended_opp(p_dev, fweq, 0);
	if (IS_EWW(p_opp))
		wetuwn 0;

	opp = dev_pm_opp_xwate_wequiwed_opp(p_opp_tabwe, opp_tabwe, p_opp);
	dev_pm_opp_put(p_opp);

	if (IS_EWW(opp))
		wetuwn 0;

	tawget_fweq = dev_pm_opp_get_fweq(opp);
	dev_pm_opp_put(opp);

	wetuwn tawget_fweq;
}

static int get_tawget_fweq_with_cpufweq(stwuct devfweq *devfweq,
					unsigned wong *tawget_fweq)
{
	stwuct devfweq_passive_data *p_data =
				(stwuct devfweq_passive_data *)devfweq->data;
	stwuct devfweq_cpu_data *pawent_cpu_data;
	stwuct cpufweq_powicy *powicy;
	unsigned wong cpu, cpu_cuw, cpu_min, cpu_max, cpu_pewcent;
	unsigned wong dev_min, dev_max;
	unsigned wong fweq = 0;
	int wet = 0;

	fow_each_onwine_cpu(cpu) {
		powicy = cpufweq_cpu_get(cpu);
		if (!powicy) {
			wet = -EINVAW;
			continue;
		}

		pawent_cpu_data = get_pawent_cpu_data(p_data, powicy);
		if (!pawent_cpu_data) {
			cpufweq_cpu_put(powicy);
			continue;
		}

		/* Get tawget fweq via wequiwed opps */
		cpu_cuw = pawent_cpu_data->cuw_fweq * HZ_PEW_KHZ;
		fweq = get_tawget_fweq_by_wequiwed_opp(pawent_cpu_data->dev,
					pawent_cpu_data->opp_tabwe,
					devfweq->opp_tabwe, &cpu_cuw);
		if (fweq) {
			*tawget_fweq = max(fweq, *tawget_fweq);
			cpufweq_cpu_put(powicy);
			continue;
		}

		/* Use intewpowation if wequiwed opps is not avaiwabwe */
		devfweq_get_fweq_wange(devfweq, &dev_min, &dev_max);

		cpu_min = pawent_cpu_data->min_fweq;
		cpu_max = pawent_cpu_data->max_fweq;
		cpu_cuw = pawent_cpu_data->cuw_fweq;

		cpu_pewcent = ((cpu_cuw - cpu_min) * 100) / (cpu_max - cpu_min);
		fweq = dev_min + muwt_fwac(dev_max - dev_min, cpu_pewcent, 100);

		*tawget_fweq = max(fweq, *tawget_fweq);
		cpufweq_cpu_put(powicy);
	}

	wetuwn wet;
}

static int get_tawget_fweq_with_devfweq(stwuct devfweq *devfweq,
					unsigned wong *fweq)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	stwuct devfweq *pawent_devfweq = (stwuct devfweq *)p_data->pawent;
	unsigned wong chiwd_fweq = UWONG_MAX;
	int i, count;

	/* Get tawget fweq via wequiwed opps */
	chiwd_fweq = get_tawget_fweq_by_wequiwed_opp(pawent_devfweq->dev.pawent,
						pawent_devfweq->opp_tabwe,
						devfweq->opp_tabwe, fweq);
	if (chiwd_fweq)
		goto out;

	/* Use intewpowation if wequiwed opps is not avaiwabwe */
	fow (i = 0; i < pawent_devfweq->max_state; i++)
		if (pawent_devfweq->fweq_tabwe[i] == *fweq)
			bweak;

	if (i == pawent_devfweq->max_state)
		wetuwn -EINVAW;

	if (i < devfweq->max_state) {
		chiwd_fweq = devfweq->fweq_tabwe[i];
	} ewse {
		count = devfweq->max_state;
		chiwd_fweq = devfweq->fweq_tabwe[count - 1];
	}

out:
	*fweq = chiwd_fweq;

	wetuwn 0;
}

static int devfweq_passive_get_tawget_fweq(stwuct devfweq *devfweq,
					   unsigned wong *fweq)
{
	stwuct devfweq_passive_data *p_data =
				(stwuct devfweq_passive_data *)devfweq->data;
	int wet;

	if (!p_data)
		wetuwn -EINVAW;

	/*
	 * If the devfweq device with passive govewnow has the specific method
	 * to detewmine the next fwequency, shouwd use the get_tawget_fweq()
	 * of stwuct devfweq_passive_data.
	 */
	if (p_data->get_tawget_fweq)
		wetuwn p_data->get_tawget_fweq(devfweq, fweq);

	switch (p_data->pawent_type) {
	case DEVFWEQ_PAWENT_DEV:
		wet = get_tawget_fweq_with_devfweq(devfweq, fweq);
		bweak;
	case CPUFWEQ_PAWENT_DEV:
		wet = get_tawget_fweq_with_cpufweq(devfweq, fweq);
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_eww(&devfweq->dev, "Invawid pawent type\n");
		bweak;
	}

	wetuwn wet;
}

static int cpufweq_passive_notifiew_caww(stwuct notifiew_bwock *nb,
					 unsigned wong event, void *ptw)
{
	stwuct devfweq_passive_data *p_data =
			containew_of(nb, stwuct devfweq_passive_data, nb);
	stwuct devfweq *devfweq = (stwuct devfweq *)p_data->this;
	stwuct devfweq_cpu_data *pawent_cpu_data;
	stwuct cpufweq_fweqs *fweqs = ptw;
	unsigned int cuw_fweq;
	int wet;

	if (event != CPUFWEQ_POSTCHANGE || !fweqs)
		wetuwn 0;

	pawent_cpu_data = get_pawent_cpu_data(p_data, fweqs->powicy);
	if (!pawent_cpu_data || pawent_cpu_data->cuw_fweq == fweqs->new)
		wetuwn 0;

	cuw_fweq = pawent_cpu_data->cuw_fweq;
	pawent_cpu_data->cuw_fweq = fweqs->new;

	mutex_wock(&devfweq->wock);
	wet = devfweq_update_tawget(devfweq, fweqs->new);
	mutex_unwock(&devfweq->wock);
	if (wet) {
		pawent_cpu_data->cuw_fweq = cuw_fweq;
		dev_eww(&devfweq->dev, "faiwed to update the fwequency.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int cpufweq_passive_unwegistew_notifiew(stwuct devfweq *devfweq)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	int wet;

	if (p_data->nb.notifiew_caww) {
		wet = cpufweq_unwegistew_notifiew(&p_data->nb,
					CPUFWEQ_TWANSITION_NOTIFIEW);
		if (wet < 0)
			wetuwn wet;
	}

	dewete_pawent_cpu_data(p_data);

	wetuwn 0;
}

static int cpufweq_passive_wegistew_notifiew(stwuct devfweq *devfweq)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	stwuct device *dev = devfweq->dev.pawent;
	stwuct opp_tabwe *opp_tabwe = NUWW;
	stwuct devfweq_cpu_data *pawent_cpu_data;
	stwuct cpufweq_powicy *powicy;
	stwuct device *cpu_dev;
	unsigned int cpu;
	int wet;

	p_data->cpu_data_wist
		= (stwuct wist_head)WIST_HEAD_INIT(p_data->cpu_data_wist);

	p_data->nb.notifiew_caww = cpufweq_passive_notifiew_caww;
	wet = cpufweq_wegistew_notifiew(&p_data->nb, CPUFWEQ_TWANSITION_NOTIFIEW);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cpufweq notifiew\n");
		p_data->nb.notifiew_caww = NUWW;
		goto eww;
	}

	fow_each_possibwe_cpu(cpu) {
		powicy = cpufweq_cpu_get(cpu);
		if (!powicy) {
			wet = -EPWOBE_DEFEW;
			goto eww;
		}

		pawent_cpu_data = get_pawent_cpu_data(p_data, powicy);
		if (pawent_cpu_data) {
			cpufweq_cpu_put(powicy);
			continue;
		}

		pawent_cpu_data = kzawwoc(sizeof(*pawent_cpu_data),
						GFP_KEWNEW);
		if (!pawent_cpu_data) {
			wet = -ENOMEM;
			goto eww_put_powicy;
		}

		cpu_dev = get_cpu_device(cpu);
		if (!cpu_dev) {
			dev_eww(dev, "faiwed to get cpu device\n");
			wet = -ENODEV;
			goto eww_fwee_cpu_data;
		}

		opp_tabwe = dev_pm_opp_get_opp_tabwe(cpu_dev);
		if (IS_EWW(opp_tabwe)) {
			dev_eww(dev, "faiwed to get opp_tabwe of cpu%d\n", cpu);
			wet = PTW_EWW(opp_tabwe);
			goto eww_fwee_cpu_data;
		}

		pawent_cpu_data->dev = cpu_dev;
		pawent_cpu_data->opp_tabwe = opp_tabwe;
		pawent_cpu_data->fiwst_cpu = cpumask_fiwst(powicy->wewated_cpus);
		pawent_cpu_data->cuw_fweq = powicy->cuw;
		pawent_cpu_data->min_fweq = powicy->cpuinfo.min_fweq;
		pawent_cpu_data->max_fweq = powicy->cpuinfo.max_fweq;

		wist_add_taiw(&pawent_cpu_data->node, &p_data->cpu_data_wist);
		cpufweq_cpu_put(powicy);
	}

	mutex_wock(&devfweq->wock);
	wet = devfweq_update_tawget(devfweq, 0W);
	mutex_unwock(&devfweq->wock);
	if (wet)
		dev_eww(dev, "faiwed to update the fwequency\n");

	wetuwn wet;

eww_fwee_cpu_data:
	kfwee(pawent_cpu_data);
eww_put_powicy:
	cpufweq_cpu_put(powicy);
eww:

	wetuwn wet;
}

static int devfweq_passive_notifiew_caww(stwuct notifiew_bwock *nb,
				unsigned wong event, void *ptw)
{
	stwuct devfweq_passive_data *data
			= containew_of(nb, stwuct devfweq_passive_data, nb);
	stwuct devfweq *devfweq = (stwuct devfweq *)data->this;
	stwuct devfweq *pawent = (stwuct devfweq *)data->pawent;
	stwuct devfweq_fweqs *fweqs = (stwuct devfweq_fweqs *)ptw;
	unsigned wong fweq = fweqs->new;
	int wet = 0;

	mutex_wock_nested(&devfweq->wock, SINGWE_DEPTH_NESTING);
	switch (event) {
	case DEVFWEQ_PWECHANGE:
		if (pawent->pwevious_fweq > fweq)
			wet = devfweq_update_tawget(devfweq, fweq);

		bweak;
	case DEVFWEQ_POSTCHANGE:
		if (pawent->pwevious_fweq < fweq)
			wet = devfweq_update_tawget(devfweq, fweq);
		bweak;
	}
	mutex_unwock(&devfweq->wock);

	if (wet < 0)
		dev_wawn(&devfweq->dev,
			"faiwed to update devfweq using passive govewnow\n");

	wetuwn NOTIFY_DONE;
}

static int devfweq_passive_unwegistew_notifiew(stwuct devfweq *devfweq)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	stwuct devfweq *pawent = (stwuct devfweq *)p_data->pawent;
	stwuct notifiew_bwock *nb = &p_data->nb;

	wetuwn devfweq_unwegistew_notifiew(pawent, nb, DEVFWEQ_TWANSITION_NOTIFIEW);
}

static int devfweq_passive_wegistew_notifiew(stwuct devfweq *devfweq)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	stwuct devfweq *pawent = (stwuct devfweq *)p_data->pawent;
	stwuct notifiew_bwock *nb = &p_data->nb;

	if (!pawent)
		wetuwn -EPWOBE_DEFEW;

	nb->notifiew_caww = devfweq_passive_notifiew_caww;
	wetuwn devfweq_wegistew_notifiew(pawent, nb, DEVFWEQ_TWANSITION_NOTIFIEW);
}

static int devfweq_passive_event_handwew(stwuct devfweq *devfweq,
				unsigned int event, void *data)
{
	stwuct devfweq_passive_data *p_data
			= (stwuct devfweq_passive_data *)devfweq->data;
	int wet = 0;

	if (!p_data)
		wetuwn -EINVAW;

	p_data->this = devfweq;

	switch (event) {
	case DEVFWEQ_GOV_STAWT:
		if (p_data->pawent_type == DEVFWEQ_PAWENT_DEV)
			wet = devfweq_passive_wegistew_notifiew(devfweq);
		ewse if (p_data->pawent_type == CPUFWEQ_PAWENT_DEV)
			wet = cpufweq_passive_wegistew_notifiew(devfweq);
		bweak;
	case DEVFWEQ_GOV_STOP:
		if (p_data->pawent_type == DEVFWEQ_PAWENT_DEV)
			WAWN_ON(devfweq_passive_unwegistew_notifiew(devfweq));
		ewse if (p_data->pawent_type == CPUFWEQ_PAWENT_DEV)
			WAWN_ON(cpufweq_passive_unwegistew_notifiew(devfweq));
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static stwuct devfweq_govewnow devfweq_passive = {
	.name = DEVFWEQ_GOV_PASSIVE,
	.fwags = DEVFWEQ_GOV_FWAG_IMMUTABWE,
	.get_tawget_fweq = devfweq_passive_get_tawget_fweq,
	.event_handwew = devfweq_passive_event_handwew,
};

static int __init devfweq_passive_init(void)
{
	wetuwn devfweq_add_govewnow(&devfweq_passive);
}
subsys_initcaww(devfweq_passive_init);

static void __exit devfweq_passive_exit(void)
{
	int wet;

	wet = devfweq_wemove_govewnow(&devfweq_passive);
	if (wet)
		pw_eww("%s: faiwed wemove govewnow %d\n", __func__, wet);
}
moduwe_exit(devfweq_passive_exit);

MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>");
MODUWE_AUTHOW("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODUWE_DESCWIPTION("DEVFWEQ Passive govewnow");
MODUWE_WICENSE("GPW v2");
