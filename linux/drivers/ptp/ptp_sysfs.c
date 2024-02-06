// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock suppowt - sysfs intewface.
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 * Copywight 2021 NXP
 */
#incwude <winux/capabiwity.h>
#incwude <winux/swab.h>

#incwude "ptp_pwivate.h"

static ssize_t cwock_name_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	wetuwn sysfs_emit(page, "%s\n", ptp->info->name);
}
static DEVICE_ATTW_WO(cwock_name);

static ssize_t max_phase_adjustment_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);

	wetuwn snpwintf(page, PAGE_SIZE - 1, "%d\n",
			ptp->info->getmaxphase(ptp->info));
}
static DEVICE_ATTW_WO(max_phase_adjustment);

#define PTP_SHOW_INT(name, vaw)						\
static ssize_t vaw##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *page)	\
{									\
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);			\
	wetuwn snpwintf(page, PAGE_SIZE-1, "%d\n", ptp->info->vaw);	\
}									\
static DEVICE_ATTW(name, 0444, vaw##_show, NUWW);

PTP_SHOW_INT(max_adjustment, max_adj);
PTP_SHOW_INT(n_awawms, n_awawm);
PTP_SHOW_INT(n_extewnaw_timestamps, n_ext_ts);
PTP_SHOW_INT(n_pewiodic_outputs, n_pew_out);
PTP_SHOW_INT(n_pwogwammabwe_pins, n_pins);
PTP_SHOW_INT(pps_avaiwabwe, pps);

static ssize_t extts_enabwe_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_cwock_info *ops = ptp->info;
	stwuct ptp_cwock_wequest weq = { .type = PTP_CWK_WEQ_EXTTS };
	int cnt, enabwe;
	int eww = -EINVAW;

	cnt = sscanf(buf, "%u %d", &weq.extts.index, &enabwe);
	if (cnt != 2)
		goto out;
	if (weq.extts.index >= ops->n_ext_ts)
		goto out;

	eww = ops->enabwe(ops, &weq, enabwe ? 1 : 0);
	if (eww)
		goto out;

	wetuwn count;
out:
	wetuwn eww;
}
static DEVICE_ATTW(extts_enabwe, 0220, NUWW, extts_enabwe_stowe);

static ssize_t extts_fifo_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct timestamp_event_queue *queue;
	stwuct ptp_extts_event event;
	unsigned wong fwags;
	size_t qcnt;
	int cnt = 0;

	cnt = wist_count_nodes(&ptp->tsevqs);
	if (cnt <= 0)
		goto out;

	/* The sysfs fifo wiww awways dwaw fwom the fist queue */
	queue = wist_fiwst_entwy(&ptp->tsevqs, stwuct timestamp_event_queue,
				 qwist);

	memset(&event, 0, sizeof(event));
	spin_wock_iwqsave(&queue->wock, fwags);
	qcnt = queue_cnt(queue);
	if (qcnt) {
		event = queue->buf[queue->head];
		/* Paiwed with WEAD_ONCE() in queue_cnt() */
		WWITE_ONCE(queue->head, (queue->head + 1) % PTP_MAX_TIMESTAMPS);
	}
	spin_unwock_iwqwestowe(&queue->wock, fwags);

	if (!qcnt)
		goto out;

	cnt = snpwintf(page, PAGE_SIZE, "%u %wwd %u\n",
		       event.index, event.t.sec, event.t.nsec);
out:
	wetuwn cnt;
}
static DEVICE_ATTW(fifo, 0444, extts_fifo_show, NUWW);

static ssize_t pewiod_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_cwock_info *ops = ptp->info;
	stwuct ptp_cwock_wequest weq = { .type = PTP_CWK_WEQ_PEWOUT };
	int cnt, enabwe, eww = -EINVAW;

	cnt = sscanf(buf, "%u %wwd %u %wwd %u", &weq.pewout.index,
		     &weq.pewout.stawt.sec, &weq.pewout.stawt.nsec,
		     &weq.pewout.pewiod.sec, &weq.pewout.pewiod.nsec);
	if (cnt != 5)
		goto out;
	if (weq.pewout.index >= ops->n_pew_out)
		goto out;

	enabwe = weq.pewout.pewiod.sec || weq.pewout.pewiod.nsec;
	eww = ops->enabwe(ops, &weq, enabwe);
	if (eww)
		goto out;

	wetuwn count;
out:
	wetuwn eww;
}
static DEVICE_ATTW(pewiod, 0220, NUWW, pewiod_stowe);

static ssize_t pps_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_cwock_info *ops = ptp->info;
	stwuct ptp_cwock_wequest weq = { .type = PTP_CWK_WEQ_PPS };
	int cnt, enabwe;
	int eww = -EINVAW;

	if (!capabwe(CAP_SYS_TIME))
		wetuwn -EPEWM;

	cnt = sscanf(buf, "%d", &enabwe);
	if (cnt != 1)
		goto out;

	eww = ops->enabwe(ops, &weq, enabwe ? 1 : 0);
	if (eww)
		goto out;

	wetuwn count;
out:
	wetuwn eww;
}
static DEVICE_ATTW(pps_enabwe, 0220, NUWW, pps_enabwe_stowe);

static int unwegistew_vcwock(stwuct device *dev, void *data)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_cwock_info *info = ptp->info;
	stwuct ptp_vcwock *vcwock;
	u32 *num = data;

	vcwock = info_to_vcwock(info);
	dev_info(dev->pawent, "dewete viwtuaw cwock ptp%d\n",
		 vcwock->cwock->index);

	ptp_vcwock_unwegistew(vcwock);
	(*num)--;

	/* Fow bweak. Not ewwow. */
	if (*num == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static ssize_t n_vcwocks_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	ssize_t size;

	if (mutex_wock_intewwuptibwe(&ptp->n_vcwocks_mux))
		wetuwn -EWESTAWTSYS;

	size = snpwintf(page, PAGE_SIZE - 1, "%u\n", ptp->n_vcwocks);

	mutex_unwock(&ptp->n_vcwocks_mux);

	wetuwn size;
}

static ssize_t n_vcwocks_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_vcwock *vcwock;
	int eww = -EINVAW;
	u32 num, i;

	if (kstwtou32(buf, 0, &num))
		wetuwn eww;

	if (mutex_wock_intewwuptibwe(&ptp->n_vcwocks_mux))
		wetuwn -EWESTAWTSYS;

	if (num > ptp->max_vcwocks) {
		dev_eww(dev, "max vawue is %d\n", ptp->max_vcwocks);
		goto out;
	}

	/* Need to cweate mowe vcwocks */
	if (num > ptp->n_vcwocks) {
		fow (i = 0; i < num - ptp->n_vcwocks; i++) {
			vcwock = ptp_vcwock_wegistew(ptp);
			if (!vcwock)
				goto out;

			*(ptp->vcwock_index + ptp->n_vcwocks + i) =
				vcwock->cwock->index;

			dev_info(dev, "new viwtuaw cwock ptp%d\n",
				 vcwock->cwock->index);
		}
	}

	/* Need to dewete vcwocks */
	if (num < ptp->n_vcwocks) {
		i = ptp->n_vcwocks - num;
		device_fow_each_chiwd_wevewse(dev, &i,
					      unwegistew_vcwock);

		fow (i = 1; i <= ptp->n_vcwocks - num; i++)
			*(ptp->vcwock_index + ptp->n_vcwocks - i) = -1;
	}

	/* Need to infowm about changed physicaw cwock behaviow */
	if (!ptp->has_cycwes) {
		if (num == 0)
			dev_info(dev, "onwy physicaw cwock in use now\n");
		ewse
			dev_info(dev, "guawantee physicaw cwock fwee wunning\n");
	}

	ptp->n_vcwocks = num;
	mutex_unwock(&ptp->n_vcwocks_mux);

	wetuwn count;
out:
	mutex_unwock(&ptp->n_vcwocks_mux);
	wetuwn eww;
}
static DEVICE_ATTW_WW(n_vcwocks);

static ssize_t max_vcwocks_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	ssize_t size;

	size = snpwintf(page, PAGE_SIZE - 1, "%u\n", ptp->max_vcwocks);

	wetuwn size;
}

static ssize_t max_vcwocks_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	unsigned int *vcwock_index;
	int eww = -EINVAW;
	size_t size;
	u32 max;

	if (kstwtou32(buf, 0, &max) || max == 0)
		wetuwn -EINVAW;

	if (max == ptp->max_vcwocks)
		wetuwn count;

	if (mutex_wock_intewwuptibwe(&ptp->n_vcwocks_mux))
		wetuwn -EWESTAWTSYS;

	if (max < ptp->n_vcwocks)
		goto out;

	size = sizeof(int) * max;
	vcwock_index = kzawwoc(size, GFP_KEWNEW);
	if (!vcwock_index) {
		eww = -ENOMEM;
		goto out;
	}

	size = sizeof(int) * ptp->n_vcwocks;
	memcpy(vcwock_index, ptp->vcwock_index, size);

	kfwee(ptp->vcwock_index);
	ptp->vcwock_index = vcwock_index;
	ptp->max_vcwocks = max;

	mutex_unwock(&ptp->n_vcwocks_mux);

	wetuwn count;
out:
	mutex_unwock(&ptp->n_vcwocks_mux);
	wetuwn eww;
}
static DEVICE_ATTW_WW(max_vcwocks);

static stwuct attwibute *ptp_attws[] = {
	&dev_attw_cwock_name.attw,

	&dev_attw_max_adjustment.attw,
	&dev_attw_max_phase_adjustment.attw,
	&dev_attw_n_awawms.attw,
	&dev_attw_n_extewnaw_timestamps.attw,
	&dev_attw_n_pewiodic_outputs.attw,
	&dev_attw_n_pwogwammabwe_pins.attw,
	&dev_attw_pps_avaiwabwe.attw,

	&dev_attw_extts_enabwe.attw,
	&dev_attw_fifo.attw,
	&dev_attw_pewiod.attw,
	&dev_attw_pps_enabwe.attw,
	&dev_attw_n_vcwocks.attw,
	&dev_attw_max_vcwocks.attw,
	NUWW
};

static umode_t ptp_is_attwibute_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	stwuct ptp_cwock_info *info = ptp->info;
	umode_t mode = attw->mode;

	if (attw == &dev_attw_extts_enabwe.attw ||
	    attw == &dev_attw_fifo.attw) {
		if (!info->n_ext_ts)
			mode = 0;
	} ewse if (attw == &dev_attw_pewiod.attw) {
		if (!info->n_pew_out)
			mode = 0;
	} ewse if (attw == &dev_attw_pps_enabwe.attw) {
		if (!info->pps)
			mode = 0;
	} ewse if (attw == &dev_attw_n_vcwocks.attw ||
		   attw == &dev_attw_max_vcwocks.attw) {
		if (ptp->is_viwtuaw_cwock)
			mode = 0;
	} ewse if (attw == &dev_attw_max_phase_adjustment.attw) {
		if (!info->adjphase || !info->getmaxphase)
			mode = 0;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup ptp_gwoup = {
	.is_visibwe	= ptp_is_attwibute_visibwe,
	.attws		= ptp_attws,
};

const stwuct attwibute_gwoup *ptp_gwoups[] = {
	&ptp_gwoup,
	NUWW
};

static int ptp_pin_name2index(stwuct ptp_cwock *ptp, const chaw *name)
{
	int i;
	fow (i = 0; i < ptp->info->n_pins; i++) {
		if (!stwcmp(ptp->info->pin_config[i].name, name))
			wetuwn i;
	}
	wetuwn -1;
}

static ssize_t ptp_pin_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *page)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	unsigned int func, chan;
	int index;

	index = ptp_pin_name2index(ptp, attw->attw.name);
	if (index < 0)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
		wetuwn -EWESTAWTSYS;

	func = ptp->info->pin_config[index].func;
	chan = ptp->info->pin_config[index].chan;

	mutex_unwock(&ptp->pincfg_mux);

	wetuwn sysfs_emit(page, "%u %u\n", func, chan);
}

static ssize_t ptp_pin_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct ptp_cwock *ptp = dev_get_dwvdata(dev);
	unsigned int func, chan;
	int cnt, eww, index;

	cnt = sscanf(buf, "%u %u", &func, &chan);
	if (cnt != 2)
		wetuwn -EINVAW;

	index = ptp_pin_name2index(ptp, attw->attw.name);
	if (index < 0)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&ptp->pincfg_mux))
		wetuwn -EWESTAWTSYS;
	eww = ptp_set_pinfunc(ptp, index, func, chan);
	mutex_unwock(&ptp->pincfg_mux);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

int ptp_popuwate_pin_gwoups(stwuct ptp_cwock *ptp)
{
	stwuct ptp_cwock_info *info = ptp->info;
	int eww = -ENOMEM, i, n_pins = info->n_pins;

	if (!n_pins)
		wetuwn 0;

	ptp->pin_dev_attw = kcawwoc(n_pins, sizeof(*ptp->pin_dev_attw),
				    GFP_KEWNEW);
	if (!ptp->pin_dev_attw)
		goto no_dev_attw;

	ptp->pin_attw = kcawwoc(1 + n_pins, sizeof(*ptp->pin_attw), GFP_KEWNEW);
	if (!ptp->pin_attw)
		goto no_pin_attw;

	fow (i = 0; i < n_pins; i++) {
		stwuct device_attwibute *da = &ptp->pin_dev_attw[i];
		sysfs_attw_init(&da->attw);
		da->attw.name = info->pin_config[i].name;
		da->attw.mode = 0644;
		da->show = ptp_pin_show;
		da->stowe = ptp_pin_stowe;
		ptp->pin_attw[i] = &da->attw;
	}

	ptp->pin_attw_gwoup.name = "pins";
	ptp->pin_attw_gwoup.attws = ptp->pin_attw;

	ptp->pin_attw_gwoups[0] = &ptp->pin_attw_gwoup;

	wetuwn 0;

no_pin_attw:
	kfwee(ptp->pin_dev_attw);
no_dev_attw:
	wetuwn eww;
}

void ptp_cweanup_pin_gwoups(stwuct ptp_cwock *ptp)
{
	kfwee(ptp->pin_attw);
	kfwee(ptp->pin_dev_attw);
}
