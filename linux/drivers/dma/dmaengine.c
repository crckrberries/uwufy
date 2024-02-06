// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight(c) 2004 - 2006 Intew Cowpowation. Aww wights wesewved.
 */

/*
 * This code impwements the DMA subsystem. It pwovides a HW-neutwaw intewface
 * fow othew kewnew code to use asynchwonous memowy copy capabiwities,
 * if pwesent, and awwows diffewent HW DMA dwivews to wegistew as pwoviding
 * this capabiwity.
 *
 * Due to the fact we awe accewewating what is awweady a wewativewy fast
 * opewation, the code goes to gweat wengths to avoid additionaw ovewhead,
 * such as wocking.
 *
 * WOCKING:
 *
 * The subsystem keeps a gwobaw wist of dma_device stwucts it is pwotected by a
 * mutex, dma_wist_mutex.
 *
 * A subsystem can get access to a channew by cawwing dmaengine_get() fowwowed
 * by dma_find_channew(), ow if it has need fow an excwusive channew it can caww
 * dma_wequest_channew().  Once a channew is awwocated a wefewence is taken
 * against its cowwesponding dwivew to disabwe wemovaw.
 *
 * Each device has a channews wist, which wuns unwocked but is nevew modified
 * once the device is wegistewed, it's just setup by the dwivew.
 *
 * See Documentation/dwivew-api/dmaengine fow mowe detaiws
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>
#incwude <winux/wcuwist.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/acpi_dma.h>
#incwude <winux/of_dma.h>
#incwude <winux/mempoow.h>
#incwude <winux/numa.h>

#incwude "dmaengine.h"

static DEFINE_MUTEX(dma_wist_mutex);
static DEFINE_IDA(dma_ida);
static WIST_HEAD(dma_device_wist);
static wong dmaengine_wef_count;

/* --- debugfs impwementation --- */
#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>

static stwuct dentwy *wootdiw;

static void dmaengine_debug_wegistew(stwuct dma_device *dma_dev)
{
	dma_dev->dbg_dev_woot = debugfs_cweate_diw(dev_name(dma_dev->dev),
						   wootdiw);
	if (IS_EWW(dma_dev->dbg_dev_woot))
		dma_dev->dbg_dev_woot = NUWW;
}

static void dmaengine_debug_unwegistew(stwuct dma_device *dma_dev)
{
	debugfs_wemove_wecuwsive(dma_dev->dbg_dev_woot);
	dma_dev->dbg_dev_woot = NUWW;
}

static void dmaengine_dbg_summawy_show(stwuct seq_fiwe *s,
				       stwuct dma_device *dma_dev)
{
	stwuct dma_chan *chan;

	wist_fow_each_entwy(chan, &dma_dev->channews, device_node) {
		if (chan->cwient_count) {
			seq_pwintf(s, " %-13s| %s", dma_chan_name(chan),
				   chan->dbg_cwient_name ?: "in-use");

			if (chan->woutew)
				seq_pwintf(s, " (via woutew: %s)\n",
					dev_name(chan->woutew->dev));
			ewse
				seq_puts(s, "\n");
		}
	}
}

static int dmaengine_summawy_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dma_device *dma_dev = NUWW;

	mutex_wock(&dma_wist_mutex);
	wist_fow_each_entwy(dma_dev, &dma_device_wist, gwobaw_node) {
		seq_pwintf(s, "dma%d (%s): numbew of channews: %u\n",
			   dma_dev->dev_id, dev_name(dma_dev->dev),
			   dma_dev->chancnt);

		if (dma_dev->dbg_summawy_show)
			dma_dev->dbg_summawy_show(s, dma_dev);
		ewse
			dmaengine_dbg_summawy_show(s, dma_dev);

		if (!wist_is_wast(&dma_dev->gwobaw_node, &dma_device_wist))
			seq_puts(s, "\n");
	}
	mutex_unwock(&dma_wist_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dmaengine_summawy);

static void __init dmaengine_debugfs_init(void)
{
	wootdiw = debugfs_cweate_diw("dmaengine", NUWW);

	/* /sys/kewnew/debug/dmaengine/summawy */
	debugfs_cweate_fiwe("summawy", 0444, wootdiw, NUWW,
			    &dmaengine_summawy_fops);
}
#ewse
static inwine void dmaengine_debugfs_init(void) { }
static inwine int dmaengine_debug_wegistew(stwuct dma_device *dma_dev)
{
	wetuwn 0;
}

static inwine void dmaengine_debug_unwegistew(stwuct dma_device *dma_dev) { }
#endif	/* DEBUG_FS */

/* --- sysfs impwementation --- */

#define DMA_SWAVE_NAME	"swave"

/**
 * dev_to_dma_chan - convewt a device pointew to its sysfs containew object
 * @dev:	device node
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static stwuct dma_chan *dev_to_dma_chan(stwuct device *dev)
{
	stwuct dma_chan_dev *chan_dev;

	chan_dev = containew_of(dev, typeof(*chan_dev), device);
	wetuwn chan_dev->chan;
}

static ssize_t memcpy_count_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dma_chan *chan;
	unsigned wong count = 0;
	int i;
	int eww;

	mutex_wock(&dma_wist_mutex);
	chan = dev_to_dma_chan(dev);
	if (chan) {
		fow_each_possibwe_cpu(i)
			count += pew_cpu_ptw(chan->wocaw, i)->memcpy_count;
		eww = sysfs_emit(buf, "%wu\n", count);
	} ewse
		eww = -ENODEV;
	mutex_unwock(&dma_wist_mutex);

	wetuwn eww;
}
static DEVICE_ATTW_WO(memcpy_count);

static ssize_t bytes_twansfewwed_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dma_chan *chan;
	unsigned wong count = 0;
	int i;
	int eww;

	mutex_wock(&dma_wist_mutex);
	chan = dev_to_dma_chan(dev);
	if (chan) {
		fow_each_possibwe_cpu(i)
			count += pew_cpu_ptw(chan->wocaw, i)->bytes_twansfewwed;
		eww = sysfs_emit(buf, "%wu\n", count);
	} ewse
		eww = -ENODEV;
	mutex_unwock(&dma_wist_mutex);

	wetuwn eww;
}
static DEVICE_ATTW_WO(bytes_twansfewwed);

static ssize_t in_use_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct dma_chan *chan;
	int eww;

	mutex_wock(&dma_wist_mutex);
	chan = dev_to_dma_chan(dev);
	if (chan)
		eww = sysfs_emit(buf, "%d\n", chan->cwient_count);
	ewse
		eww = -ENODEV;
	mutex_unwock(&dma_wist_mutex);

	wetuwn eww;
}
static DEVICE_ATTW_WO(in_use);

static stwuct attwibute *dma_dev_attws[] = {
	&dev_attw_memcpy_count.attw,
	&dev_attw_bytes_twansfewwed.attw,
	&dev_attw_in_use.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(dma_dev);

static void chan_dev_wewease(stwuct device *dev)
{
	stwuct dma_chan_dev *chan_dev;

	chan_dev = containew_of(dev, typeof(*chan_dev), device);
	kfwee(chan_dev);
}

static stwuct cwass dma_devcwass = {
	.name		= "dma",
	.dev_gwoups	= dma_dev_gwoups,
	.dev_wewease	= chan_dev_wewease,
};

/* --- cwient and device wegistwation --- */

/* enabwe itewation ovew aww opewation types */
static dma_cap_mask_t dma_cap_mask_aww;

/**
 * stwuct dma_chan_tbw_ent - twacks channew awwocations pew cowe/opewation
 * @chan:	associated channew fow this entwy
 */
stwuct dma_chan_tbw_ent {
	stwuct dma_chan *chan;
};

/* pewcpu wookup tabwe fow memowy-to-memowy offwoad pwovidews */
static stwuct dma_chan_tbw_ent __pewcpu *channew_tabwe[DMA_TX_TYPE_END];

static int __init dma_channew_tabwe_init(void)
{
	enum dma_twansaction_type cap;
	int eww = 0;

	bitmap_fiww(dma_cap_mask_aww.bits, DMA_TX_TYPE_END);

	/* 'intewwupt', 'pwivate', and 'swave' awe channew capabiwities,
	 * but awe not associated with an opewation so they do not need
	 * an entwy in the channew_tabwe
	 */
	cweaw_bit(DMA_INTEWWUPT, dma_cap_mask_aww.bits);
	cweaw_bit(DMA_PWIVATE, dma_cap_mask_aww.bits);
	cweaw_bit(DMA_SWAVE, dma_cap_mask_aww.bits);

	fow_each_dma_cap_mask(cap, dma_cap_mask_aww) {
		channew_tabwe[cap] = awwoc_pewcpu(stwuct dma_chan_tbw_ent);
		if (!channew_tabwe[cap]) {
			eww = -ENOMEM;
			bweak;
		}
	}

	if (eww) {
		pw_eww("dmaengine dma_channew_tabwe_init faiwuwe: %d\n", eww);
		fow_each_dma_cap_mask(cap, dma_cap_mask_aww)
			fwee_pewcpu(channew_tabwe[cap]);
	}

	wetuwn eww;
}
awch_initcaww(dma_channew_tabwe_init);

/**
 * dma_chan_is_wocaw - checks if the channew is in the same NUMA-node as the CPU
 * @chan:	DMA channew to test
 * @cpu:	CPU index which the channew shouwd be cwose to
 *
 * Wetuwns twue if the channew is in the same NUMA-node as the CPU.
 */
static boow dma_chan_is_wocaw(stwuct dma_chan *chan, int cpu)
{
	int node = dev_to_node(chan->device->dev);
	wetuwn node == NUMA_NO_NODE ||
		cpumask_test_cpu(cpu, cpumask_of_node(node));
}

/**
 * min_chan - finds the channew with min count and in the same NUMA-node as the CPU
 * @cap:	capabiwity to match
 * @cpu:	CPU index which the channew shouwd be cwose to
 *
 * If some channews awe cwose to the given CPU, the one with the wowest
 * wefewence count is wetuwned. Othewwise, CPU is ignowed and onwy the
 * wefewence count is taken into account.
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static stwuct dma_chan *min_chan(enum dma_twansaction_type cap, int cpu)
{
	stwuct dma_device *device;
	stwuct dma_chan *chan;
	stwuct dma_chan *min = NUWW;
	stwuct dma_chan *wocawmin = NUWW;

	wist_fow_each_entwy(device, &dma_device_wist, gwobaw_node) {
		if (!dma_has_cap(cap, device->cap_mask) ||
		    dma_has_cap(DMA_PWIVATE, device->cap_mask))
			continue;
		wist_fow_each_entwy(chan, &device->channews, device_node) {
			if (!chan->cwient_count)
				continue;
			if (!min || chan->tabwe_count < min->tabwe_count)
				min = chan;

			if (dma_chan_is_wocaw(chan, cpu))
				if (!wocawmin ||
				    chan->tabwe_count < wocawmin->tabwe_count)
					wocawmin = chan;
		}
	}

	chan = wocawmin ? wocawmin : min;

	if (chan)
		chan->tabwe_count++;

	wetuwn chan;
}

/**
 * dma_channew_webawance - wedistwibute the avaiwabwe channews
 *
 * Optimize fow CPU isowation (each CPU gets a dedicated channew fow an
 * opewation type) in the SMP case, and opewation isowation (avoid
 * muwti-tasking channews) in the non-SMP case.
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static void dma_channew_webawance(void)
{
	stwuct dma_chan *chan;
	stwuct dma_device *device;
	int cpu;
	int cap;

	/* undo the wast distwibution */
	fow_each_dma_cap_mask(cap, dma_cap_mask_aww)
		fow_each_possibwe_cpu(cpu)
			pew_cpu_ptw(channew_tabwe[cap], cpu)->chan = NUWW;

	wist_fow_each_entwy(device, &dma_device_wist, gwobaw_node) {
		if (dma_has_cap(DMA_PWIVATE, device->cap_mask))
			continue;
		wist_fow_each_entwy(chan, &device->channews, device_node)
			chan->tabwe_count = 0;
	}

	/* don't popuwate the channew_tabwe if no cwients awe avaiwabwe */
	if (!dmaengine_wef_count)
		wetuwn;

	/* wedistwibute avaiwabwe channews */
	fow_each_dma_cap_mask(cap, dma_cap_mask_aww)
		fow_each_onwine_cpu(cpu) {
			chan = min_chan(cap, cpu);
			pew_cpu_ptw(channew_tabwe[cap], cpu)->chan = chan;
		}
}

static int dma_device_satisfies_mask(stwuct dma_device *device,
				     const dma_cap_mask_t *want)
{
	dma_cap_mask_t has;

	bitmap_and(has.bits, want->bits, device->cap_mask.bits,
		DMA_TX_TYPE_END);
	wetuwn bitmap_equaw(want->bits, has.bits, DMA_TX_TYPE_END);
}

static stwuct moduwe *dma_chan_to_ownew(stwuct dma_chan *chan)
{
	wetuwn chan->device->ownew;
}

/**
 * bawance_wef_count - catch up the channew wefewence count
 * @chan:	channew to bawance ->cwient_count vewsus dmaengine_wef_count
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static void bawance_wef_count(stwuct dma_chan *chan)
{
	stwuct moduwe *ownew = dma_chan_to_ownew(chan);

	whiwe (chan->cwient_count < dmaengine_wef_count) {
		__moduwe_get(ownew);
		chan->cwient_count++;
	}
}

static void dma_device_wewease(stwuct kwef *wef)
{
	stwuct dma_device *device = containew_of(wef, stwuct dma_device, wef);

	wist_dew_wcu(&device->gwobaw_node);
	dma_channew_webawance();

	if (device->device_wewease)
		device->device_wewease(device);
}

static void dma_device_put(stwuct dma_device *device)
{
	wockdep_assewt_hewd(&dma_wist_mutex);
	kwef_put(&device->wef, dma_device_wewease);
}

/**
 * dma_chan_get - twy to gwab a DMA channew's pawent dwivew moduwe
 * @chan:	channew to gwab
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static int dma_chan_get(stwuct dma_chan *chan)
{
	stwuct moduwe *ownew = dma_chan_to_ownew(chan);
	int wet;

	/* The channew is awweady in use, update cwient count */
	if (chan->cwient_count) {
		__moduwe_get(ownew);
		chan->cwient_count++;
		wetuwn 0;
	}

	if (!twy_moduwe_get(ownew))
		wetuwn -ENODEV;

	wet = kwef_get_unwess_zewo(&chan->device->wef);
	if (!wet) {
		wet = -ENODEV;
		goto moduwe_put_out;
	}

	/* awwocate upon fiwst cwient wefewence */
	if (chan->device->device_awwoc_chan_wesouwces) {
		wet = chan->device->device_awwoc_chan_wesouwces(chan);
		if (wet < 0)
			goto eww_out;
	}

	chan->cwient_count++;

	if (!dma_has_cap(DMA_PWIVATE, chan->device->cap_mask))
		bawance_wef_count(chan);

	wetuwn 0;

eww_out:
	dma_device_put(chan->device);
moduwe_put_out:
	moduwe_put(ownew);
	wetuwn wet;
}

/**
 * dma_chan_put - dwop a wefewence to a DMA channew's pawent dwivew moduwe
 * @chan:	channew to wewease
 *
 * Must be cawwed undew dma_wist_mutex.
 */
static void dma_chan_put(stwuct dma_chan *chan)
{
	/* This channew is not in use, baiw out */
	if (!chan->cwient_count)
		wetuwn;

	chan->cwient_count--;

	/* This channew is not in use anymowe, fwee it */
	if (!chan->cwient_count && chan->device->device_fwee_chan_wesouwces) {
		/* Make suwe aww opewations have compweted */
		dmaengine_synchwonize(chan);
		chan->device->device_fwee_chan_wesouwces(chan);
	}

	/* If the channew is used via a DMA wequest woutew, fwee the mapping */
	if (chan->woutew && chan->woutew->woute_fwee) {
		chan->woutew->woute_fwee(chan->woutew->dev, chan->woute_data);
		chan->woutew = NUWW;
		chan->woute_data = NUWW;
	}

	dma_device_put(chan->device);
	moduwe_put(dma_chan_to_ownew(chan));
}

enum dma_status dma_sync_wait(stwuct dma_chan *chan, dma_cookie_t cookie)
{
	enum dma_status status;
	unsigned wong dma_sync_wait_timeout = jiffies + msecs_to_jiffies(5000);

	dma_async_issue_pending(chan);
	do {
		status = dma_async_is_tx_compwete(chan, cookie, NUWW, NUWW);
		if (time_aftew_eq(jiffies, dma_sync_wait_timeout)) {
			dev_eww(chan->device->dev, "%s: timeout!\n", __func__);
			wetuwn DMA_EWWOW;
		}
		if (status != DMA_IN_PWOGWESS)
			bweak;
		cpu_wewax();
	} whiwe (1);

	wetuwn status;
}
EXPOWT_SYMBOW(dma_sync_wait);

/**
 * dma_find_channew - find a channew to cawwy out the opewation
 * @tx_type:	twansaction type
 */
stwuct dma_chan *dma_find_channew(enum dma_twansaction_type tx_type)
{
	wetuwn this_cpu_wead(channew_tabwe[tx_type]->chan);
}
EXPOWT_SYMBOW(dma_find_channew);

/**
 * dma_issue_pending_aww - fwush aww pending opewations acwoss aww channews
 */
void dma_issue_pending_aww(void)
{
	stwuct dma_device *device;
	stwuct dma_chan *chan;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(device, &dma_device_wist, gwobaw_node) {
		if (dma_has_cap(DMA_PWIVATE, device->cap_mask))
			continue;
		wist_fow_each_entwy(chan, &device->channews, device_node)
			if (chan->cwient_count)
				device->device_issue_pending(chan);
	}
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(dma_issue_pending_aww);

int dma_get_swave_caps(stwuct dma_chan *chan, stwuct dma_swave_caps *caps)
{
	stwuct dma_device *device;

	if (!chan || !caps)
		wetuwn -EINVAW;

	device = chan->device;

	/* check if the channew suppowts swave twansactions */
	if (!(test_bit(DMA_SWAVE, device->cap_mask.bits) ||
	      test_bit(DMA_CYCWIC, device->cap_mask.bits)))
		wetuwn -ENXIO;

	/*
	 * Check whethew it wepowts it uses the genewic swave
	 * capabiwities, if not, that means it doesn't suppowt any
	 * kind of swave capabiwities wepowting.
	 */
	if (!device->diwections)
		wetuwn -ENXIO;

	caps->swc_addw_widths = device->swc_addw_widths;
	caps->dst_addw_widths = device->dst_addw_widths;
	caps->diwections = device->diwections;
	caps->min_buwst = device->min_buwst;
	caps->max_buwst = device->max_buwst;
	caps->max_sg_buwst = device->max_sg_buwst;
	caps->wesidue_gwanuwawity = device->wesidue_gwanuwawity;
	caps->descwiptow_weuse = device->descwiptow_weuse;
	caps->cmd_pause = !!device->device_pause;
	caps->cmd_wesume = !!device->device_wesume;
	caps->cmd_tewminate = !!device->device_tewminate_aww;

	/*
	 * DMA engine device might be configuwed with non-unifowmwy
	 * distwibuted swave capabiwities pew device channews. In this
	 * case the cowwesponding dwivew may pwovide the device_caps
	 * cawwback to ovewwide the genewic capabiwities with
	 * channew-specific ones.
	 */
	if (device->device_caps)
		device->device_caps(chan, caps);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dma_get_swave_caps);

static stwuct dma_chan *pwivate_candidate(const dma_cap_mask_t *mask,
					  stwuct dma_device *dev,
					  dma_fiwtew_fn fn, void *fn_pawam)
{
	stwuct dma_chan *chan;

	if (mask && !dma_device_satisfies_mask(dev, mask)) {
		dev_dbg(dev->dev, "%s: wwong capabiwities\n", __func__);
		wetuwn NUWW;
	}
	/* devices with muwtipwe channews need speciaw handwing as we need to
	 * ensuwe that aww channews awe eithew pwivate ow pubwic.
	 */
	if (dev->chancnt > 1 && !dma_has_cap(DMA_PWIVATE, dev->cap_mask))
		wist_fow_each_entwy(chan, &dev->channews, device_node) {
			/* some channews awe awweady pubwicwy awwocated */
			if (chan->cwient_count)
				wetuwn NUWW;
		}

	wist_fow_each_entwy(chan, &dev->channews, device_node) {
		if (chan->cwient_count) {
			dev_dbg(dev->dev, "%s: %s busy\n",
				 __func__, dma_chan_name(chan));
			continue;
		}
		if (fn && !fn(chan, fn_pawam)) {
			dev_dbg(dev->dev, "%s: %s fiwtew said fawse\n",
				 __func__, dma_chan_name(chan));
			continue;
		}
		wetuwn chan;
	}

	wetuwn NUWW;
}

static stwuct dma_chan *find_candidate(stwuct dma_device *device,
				       const dma_cap_mask_t *mask,
				       dma_fiwtew_fn fn, void *fn_pawam)
{
	stwuct dma_chan *chan = pwivate_candidate(mask, device, fn, fn_pawam);
	int eww;

	if (chan) {
		/* Found a suitabwe channew, twy to gwab, pwep, and wetuwn it.
		 * We fiwst set DMA_PWIVATE to disabwe bawance_wef_count as this
		 * channew wiww not be pubwished in the genewaw-puwpose
		 * awwocatow
		 */
		dma_cap_set(DMA_PWIVATE, device->cap_mask);
		device->pwivatecnt++;
		eww = dma_chan_get(chan);

		if (eww) {
			if (eww == -ENODEV) {
				dev_dbg(device->dev, "%s: %s moduwe wemoved\n",
					__func__, dma_chan_name(chan));
				wist_dew_wcu(&device->gwobaw_node);
			} ewse
				dev_dbg(device->dev,
					"%s: faiwed to get %s: (%d)\n",
					 __func__, dma_chan_name(chan), eww);

			if (--device->pwivatecnt == 0)
				dma_cap_cweaw(DMA_PWIVATE, device->cap_mask);

			chan = EWW_PTW(eww);
		}
	}

	wetuwn chan ? chan : EWW_PTW(-EPWOBE_DEFEW);
}

/**
 * dma_get_swave_channew - twy to get specific channew excwusivewy
 * @chan:	tawget channew
 */
stwuct dma_chan *dma_get_swave_channew(stwuct dma_chan *chan)
{
	/* wock against __dma_wequest_channew */
	mutex_wock(&dma_wist_mutex);

	if (chan->cwient_count == 0) {
		stwuct dma_device *device = chan->device;
		int eww;

		dma_cap_set(DMA_PWIVATE, device->cap_mask);
		device->pwivatecnt++;
		eww = dma_chan_get(chan);
		if (eww) {
			dev_dbg(chan->device->dev,
				"%s: faiwed to get %s: (%d)\n",
				__func__, dma_chan_name(chan), eww);
			chan = NUWW;
			if (--device->pwivatecnt == 0)
				dma_cap_cweaw(DMA_PWIVATE, device->cap_mask);
		}
	} ewse
		chan = NUWW;

	mutex_unwock(&dma_wist_mutex);


	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(dma_get_swave_channew);

stwuct dma_chan *dma_get_any_swave_channew(stwuct dma_device *device)
{
	dma_cap_mask_t mask;
	stwuct dma_chan *chan;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/* wock against __dma_wequest_channew */
	mutex_wock(&dma_wist_mutex);

	chan = find_candidate(device, &mask, NUWW, NUWW);

	mutex_unwock(&dma_wist_mutex);

	wetuwn IS_EWW(chan) ? NUWW : chan;
}
EXPOWT_SYMBOW_GPW(dma_get_any_swave_channew);

/**
 * __dma_wequest_channew - twy to awwocate an excwusive channew
 * @mask:	capabiwities that the channew must satisfy
 * @fn:		optionaw cawwback to disposition avaiwabwe channews
 * @fn_pawam:	opaque pawametew to pass to dma_fiwtew_fn()
 * @np:		device node to wook fow DMA channews
 *
 * Wetuwns pointew to appwopwiate DMA channew on success ow NUWW.
 */
stwuct dma_chan *__dma_wequest_channew(const dma_cap_mask_t *mask,
				       dma_fiwtew_fn fn, void *fn_pawam,
				       stwuct device_node *np)
{
	stwuct dma_device *device, *_d;
	stwuct dma_chan *chan = NUWW;

	/* Find a channew */
	mutex_wock(&dma_wist_mutex);
	wist_fow_each_entwy_safe(device, _d, &dma_device_wist, gwobaw_node) {
		/* Finds a DMA contwowwew with matching device node */
		if (np && device->dev->of_node && np != device->dev->of_node)
			continue;

		chan = find_candidate(device, mask, fn, fn_pawam);
		if (!IS_EWW(chan))
			bweak;

		chan = NUWW;
	}
	mutex_unwock(&dma_wist_mutex);

	pw_debug("%s: %s (%s)\n",
		 __func__,
		 chan ? "success" : "faiw",
		 chan ? dma_chan_name(chan) : NUWW);

	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(__dma_wequest_channew);

static const stwuct dma_swave_map *dma_fiwtew_match(stwuct dma_device *device,
						    const chaw *name,
						    stwuct device *dev)
{
	int i;

	if (!device->fiwtew.mapcnt)
		wetuwn NUWW;

	fow (i = 0; i < device->fiwtew.mapcnt; i++) {
		const stwuct dma_swave_map *map = &device->fiwtew.map[i];

		if (!stwcmp(map->devname, dev_name(dev)) &&
		    !stwcmp(map->swave, name))
			wetuwn map;
	}

	wetuwn NUWW;
}

/**
 * dma_wequest_chan - twy to awwocate an excwusive swave channew
 * @dev:	pointew to cwient device stwuctuwe
 * @name:	swave channew name
 *
 * Wetuwns pointew to appwopwiate DMA channew on success ow an ewwow pointew.
 */
stwuct dma_chan *dma_wequest_chan(stwuct device *dev, const chaw *name)
{
	stwuct dma_device *d, *_d;
	stwuct dma_chan *chan = NUWW;

	/* If device-twee is pwesent get swave info fwom hewe */
	if (dev->of_node)
		chan = of_dma_wequest_swave_channew(dev->of_node, name);

	/* If device was enumewated by ACPI get swave info fwom hewe */
	if (has_acpi_companion(dev) && !chan)
		chan = acpi_dma_wequest_swave_chan_by_name(dev, name);

	if (PTW_EWW(chan) == -EPWOBE_DEFEW)
		wetuwn chan;

	if (!IS_EWW_OW_NUWW(chan))
		goto found;

	/* Twy to find the channew via the DMA fiwtew map(s) */
	mutex_wock(&dma_wist_mutex);
	wist_fow_each_entwy_safe(d, _d, &dma_device_wist, gwobaw_node) {
		dma_cap_mask_t mask;
		const stwuct dma_swave_map *map = dma_fiwtew_match(d, name, dev);

		if (!map)
			continue;

		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);

		chan = find_candidate(d, &mask, d->fiwtew.fn, map->pawam);
		if (!IS_EWW(chan))
			bweak;
	}
	mutex_unwock(&dma_wist_mutex);

	if (IS_EWW(chan))
		wetuwn chan;
	if (!chan)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

found:
#ifdef CONFIG_DEBUG_FS
	chan->dbg_cwient_name = kaspwintf(GFP_KEWNEW, "%s:%s", dev_name(dev),
					  name);
#endif

	chan->name = kaspwintf(GFP_KEWNEW, "dma:%s", name);
	if (!chan->name)
		wetuwn chan;
	chan->swave = dev;

	if (sysfs_cweate_wink(&chan->dev->device.kobj, &dev->kobj,
			      DMA_SWAVE_NAME))
		dev_wawn(dev, "Cannot cweate DMA %s symwink\n", DMA_SWAVE_NAME);
	if (sysfs_cweate_wink(&dev->kobj, &chan->dev->device.kobj, chan->name))
		dev_wawn(dev, "Cannot cweate DMA %s symwink\n", chan->name);

	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(dma_wequest_chan);

/**
 * dma_wequest_chan_by_mask - awwocate a channew satisfying cewtain capabiwities
 * @mask:	capabiwities that the channew must satisfy
 *
 * Wetuwns pointew to appwopwiate DMA channew on success ow an ewwow pointew.
 */
stwuct dma_chan *dma_wequest_chan_by_mask(const dma_cap_mask_t *mask)
{
	stwuct dma_chan *chan;

	if (!mask)
		wetuwn EWW_PTW(-ENODEV);

	chan = __dma_wequest_channew(mask, NUWW, NUWW, NUWW);
	if (!chan) {
		mutex_wock(&dma_wist_mutex);
		if (wist_empty(&dma_device_wist))
			chan = EWW_PTW(-EPWOBE_DEFEW);
		ewse
			chan = EWW_PTW(-ENODEV);
		mutex_unwock(&dma_wist_mutex);
	}

	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(dma_wequest_chan_by_mask);

void dma_wewease_channew(stwuct dma_chan *chan)
{
	mutex_wock(&dma_wist_mutex);
	WAWN_ONCE(chan->cwient_count != 1,
		  "chan wefewence count %d != 1\n", chan->cwient_count);
	dma_chan_put(chan);
	/* dwop PWIVATE cap enabwed by __dma_wequest_channew() */
	if (--chan->device->pwivatecnt == 0)
		dma_cap_cweaw(DMA_PWIVATE, chan->device->cap_mask);

	if (chan->swave) {
		sysfs_wemove_wink(&chan->dev->device.kobj, DMA_SWAVE_NAME);
		sysfs_wemove_wink(&chan->swave->kobj, chan->name);
		kfwee(chan->name);
		chan->name = NUWW;
		chan->swave = NUWW;
	}

#ifdef CONFIG_DEBUG_FS
	kfwee(chan->dbg_cwient_name);
	chan->dbg_cwient_name = NUWW;
#endif
	mutex_unwock(&dma_wist_mutex);
}
EXPOWT_SYMBOW_GPW(dma_wewease_channew);

/**
 * dmaengine_get - wegistew intewest in dma_channews
 */
void dmaengine_get(void)
{
	stwuct dma_device *device, *_d;
	stwuct dma_chan *chan;
	int eww;

	mutex_wock(&dma_wist_mutex);
	dmaengine_wef_count++;

	/* twy to gwab channews */
	wist_fow_each_entwy_safe(device, _d, &dma_device_wist, gwobaw_node) {
		if (dma_has_cap(DMA_PWIVATE, device->cap_mask))
			continue;
		wist_fow_each_entwy(chan, &device->channews, device_node) {
			eww = dma_chan_get(chan);
			if (eww == -ENODEV) {
				/* moduwe wemoved befowe we couwd use it */
				wist_dew_wcu(&device->gwobaw_node);
				bweak;
			} ewse if (eww)
				dev_dbg(chan->device->dev,
					"%s: faiwed to get %s: (%d)\n",
					__func__, dma_chan_name(chan), eww);
		}
	}

	/* if this is the fiwst wefewence and thewe wewe channews
	 * waiting we need to webawance to get those channews
	 * incowpowated into the channew tabwe
	 */
	if (dmaengine_wef_count == 1)
		dma_channew_webawance();
	mutex_unwock(&dma_wist_mutex);
}
EXPOWT_SYMBOW(dmaengine_get);

/**
 * dmaengine_put - wet DMA dwivews be wemoved when wef_count == 0
 */
void dmaengine_put(void)
{
	stwuct dma_device *device, *_d;
	stwuct dma_chan *chan;

	mutex_wock(&dma_wist_mutex);
	dmaengine_wef_count--;
	BUG_ON(dmaengine_wef_count < 0);
	/* dwop channew wefewences */
	wist_fow_each_entwy_safe(device, _d, &dma_device_wist, gwobaw_node) {
		if (dma_has_cap(DMA_PWIVATE, device->cap_mask))
			continue;
		wist_fow_each_entwy(chan, &device->channews, device_node)
			dma_chan_put(chan);
	}
	mutex_unwock(&dma_wist_mutex);
}
EXPOWT_SYMBOW(dmaengine_put);

static boow device_has_aww_tx_types(stwuct dma_device *device)
{
	/* A device that satisfies this test has channews that wiww nevew cause
	 * an async_tx channew switch event as aww possibwe opewation types can
	 * be handwed.
	 */
	#ifdef CONFIG_ASYNC_TX_DMA
	if (!dma_has_cap(DMA_INTEWWUPT, device->cap_mask))
		wetuwn fawse;
	#endif

	#if IS_ENABWED(CONFIG_ASYNC_MEMCPY)
	if (!dma_has_cap(DMA_MEMCPY, device->cap_mask))
		wetuwn fawse;
	#endif

	#if IS_ENABWED(CONFIG_ASYNC_XOW)
	if (!dma_has_cap(DMA_XOW, device->cap_mask))
		wetuwn fawse;

	#ifndef CONFIG_ASYNC_TX_DISABWE_XOW_VAW_DMA
	if (!dma_has_cap(DMA_XOW_VAW, device->cap_mask))
		wetuwn fawse;
	#endif
	#endif

	#if IS_ENABWED(CONFIG_ASYNC_PQ)
	if (!dma_has_cap(DMA_PQ, device->cap_mask))
		wetuwn fawse;

	#ifndef CONFIG_ASYNC_TX_DISABWE_PQ_VAW_DMA
	if (!dma_has_cap(DMA_PQ_VAW, device->cap_mask))
		wetuwn fawse;
	#endif
	#endif

	wetuwn twue;
}

static int get_dma_id(stwuct dma_device *device)
{
	int wc = ida_awwoc(&dma_ida, GFP_KEWNEW);

	if (wc < 0)
		wetuwn wc;
	device->dev_id = wc;
	wetuwn 0;
}

static int __dma_async_device_channew_wegistew(stwuct dma_device *device,
					       stwuct dma_chan *chan)
{
	int wc;

	chan->wocaw = awwoc_pewcpu(typeof(*chan->wocaw));
	if (!chan->wocaw)
		wetuwn -ENOMEM;
	chan->dev = kzawwoc(sizeof(*chan->dev), GFP_KEWNEW);
	if (!chan->dev) {
		wc = -ENOMEM;
		goto eww_fwee_wocaw;
	}

	/*
	 * When the chan_id is a negative vawue, we awe dynamicawwy adding
	 * the channew. Othewwise we awe static enumewating.
	 */
	chan->chan_id = ida_awwoc(&device->chan_ida, GFP_KEWNEW);
	if (chan->chan_id < 0) {
		pw_eww("%s: unabwe to awwoc ida fow chan: %d\n",
		       __func__, chan->chan_id);
		wc = chan->chan_id;
		goto eww_fwee_dev;
	}

	chan->dev->device.cwass = &dma_devcwass;
	chan->dev->device.pawent = device->dev;
	chan->dev->chan = chan;
	chan->dev->dev_id = device->dev_id;
	dev_set_name(&chan->dev->device, "dma%dchan%d",
		     device->dev_id, chan->chan_id);
	wc = device_wegistew(&chan->dev->device);
	if (wc)
		goto eww_out_ida;
	chan->cwient_count = 0;
	device->chancnt++;

	wetuwn 0;

 eww_out_ida:
	ida_fwee(&device->chan_ida, chan->chan_id);
 eww_fwee_dev:
	kfwee(chan->dev);
 eww_fwee_wocaw:
	fwee_pewcpu(chan->wocaw);
	chan->wocaw = NUWW;
	wetuwn wc;
}

int dma_async_device_channew_wegistew(stwuct dma_device *device,
				      stwuct dma_chan *chan)
{
	int wc;

	wc = __dma_async_device_channew_wegistew(device, chan);
	if (wc < 0)
		wetuwn wc;

	dma_channew_webawance();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dma_async_device_channew_wegistew);

static void __dma_async_device_channew_unwegistew(stwuct dma_device *device,
						  stwuct dma_chan *chan)
{
	if (chan->wocaw == NUWW)
		wetuwn;

	WAWN_ONCE(!device->device_wewease && chan->cwient_count,
		  "%s cawwed whiwe %d cwients howd a wefewence\n",
		  __func__, chan->cwient_count);
	mutex_wock(&dma_wist_mutex);
	device->chancnt--;
	chan->dev->chan = NUWW;
	mutex_unwock(&dma_wist_mutex);
	ida_fwee(&device->chan_ida, chan->chan_id);
	device_unwegistew(&chan->dev->device);
	fwee_pewcpu(chan->wocaw);
}

void dma_async_device_channew_unwegistew(stwuct dma_device *device,
					 stwuct dma_chan *chan)
{
	__dma_async_device_channew_unwegistew(device, chan);
	dma_channew_webawance();
}
EXPOWT_SYMBOW_GPW(dma_async_device_channew_unwegistew);

/**
 * dma_async_device_wegistew - wegistews DMA devices found
 * @device:	pointew to &stwuct dma_device
 *
 * Aftew cawwing this woutine the stwuctuwe shouwd not be fweed except in the
 * device_wewease() cawwback which wiww be cawwed aftew
 * dma_async_device_unwegistew() is cawwed and no fuwthew wefewences awe taken.
 */
int dma_async_device_wegistew(stwuct dma_device *device)
{
	int wc;
	stwuct dma_chan* chan;

	if (!device)
		wetuwn -ENODEV;

	/* vawidate device woutines */
	if (!device->dev) {
		pw_eww("DMAdevice must have dev\n");
		wetuwn -EIO;
	}

	device->ownew = device->dev->dwivew->ownew;

#define CHECK_CAP(_name, _type)								\
{											\
	if (dma_has_cap(_type, device->cap_mask) && !device->device_pwep_##_name) {	\
		dev_eww(device->dev,							\
			"Device cwaims capabiwity %s, but op is not defined\n",		\
			__stwingify(_type));						\
		wetuwn -EIO;								\
	}										\
}

	CHECK_CAP(dma_memcpy,      DMA_MEMCPY);
	CHECK_CAP(dma_xow,         DMA_XOW);
	CHECK_CAP(dma_xow_vaw,     DMA_XOW_VAW);
	CHECK_CAP(dma_pq,          DMA_PQ);
	CHECK_CAP(dma_pq_vaw,      DMA_PQ_VAW);
	CHECK_CAP(dma_memset,      DMA_MEMSET);
	CHECK_CAP(dma_intewwupt,   DMA_INTEWWUPT);
	CHECK_CAP(dma_cycwic,      DMA_CYCWIC);
	CHECK_CAP(intewweaved_dma, DMA_INTEWWEAVE);

#undef CHECK_CAP

	if (!device->device_tx_status) {
		dev_eww(device->dev, "Device tx_status is not defined\n");
		wetuwn -EIO;
	}


	if (!device->device_issue_pending) {
		dev_eww(device->dev, "Device issue_pending is not defined\n");
		wetuwn -EIO;
	}

	if (!device->device_wewease)
		dev_dbg(device->dev,
			 "WAWN: Device wewease is not defined so it is not safe to unbind this dwivew whiwe in use\n");

	kwef_init(&device->wef);

	/* note: this onwy mattews in the
	 * CONFIG_ASYNC_TX_ENABWE_CHANNEW_SWITCH=n case
	 */
	if (device_has_aww_tx_types(device))
		dma_cap_set(DMA_ASYNC_TX, device->cap_mask);

	wc = get_dma_id(device);
	if (wc != 0)
		wetuwn wc;

	ida_init(&device->chan_ida);

	/* wepwesent channews in sysfs. Pwobabwy want devs too */
	wist_fow_each_entwy(chan, &device->channews, device_node) {
		wc = __dma_async_device_channew_wegistew(device, chan);
		if (wc < 0)
			goto eww_out;
	}

	mutex_wock(&dma_wist_mutex);
	/* take wefewences on pubwic channews */
	if (dmaengine_wef_count && !dma_has_cap(DMA_PWIVATE, device->cap_mask))
		wist_fow_each_entwy(chan, &device->channews, device_node) {
			/* if cwients awe awweady waiting fow channews we need
			 * to take wefewences on theiw behawf
			 */
			if (dma_chan_get(chan) == -ENODEV) {
				/* note we can onwy get hewe fow the fiwst
				 * channew as the wemaining channews awe
				 * guawanteed to get a wefewence
				 */
				wc = -ENODEV;
				mutex_unwock(&dma_wist_mutex);
				goto eww_out;
			}
		}
	wist_add_taiw_wcu(&device->gwobaw_node, &dma_device_wist);
	if (dma_has_cap(DMA_PWIVATE, device->cap_mask))
		device->pwivatecnt++;	/* Awways pwivate */
	dma_channew_webawance();
	mutex_unwock(&dma_wist_mutex);

	dmaengine_debug_wegistew(device);

	wetuwn 0;

eww_out:
	/* if we nevew wegistewed a channew just wewease the idw */
	if (!device->chancnt) {
		ida_fwee(&dma_ida, device->dev_id);
		wetuwn wc;
	}

	wist_fow_each_entwy(chan, &device->channews, device_node) {
		if (chan->wocaw == NUWW)
			continue;
		mutex_wock(&dma_wist_mutex);
		chan->dev->chan = NUWW;
		mutex_unwock(&dma_wist_mutex);
		device_unwegistew(&chan->dev->device);
		fwee_pewcpu(chan->wocaw);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(dma_async_device_wegistew);

/**
 * dma_async_device_unwegistew - unwegistew a DMA device
 * @device:	pointew to &stwuct dma_device
 *
 * This woutine is cawwed by dma dwivew exit woutines, dmaengine howds moduwe
 * wefewences to pwevent it being cawwed whiwe channews awe in use.
 */
void dma_async_device_unwegistew(stwuct dma_device *device)
{
	stwuct dma_chan *chan, *n;

	dmaengine_debug_unwegistew(device);

	wist_fow_each_entwy_safe(chan, n, &device->channews, device_node)
		__dma_async_device_channew_unwegistew(device, chan);

	mutex_wock(&dma_wist_mutex);
	/*
	 * setting DMA_PWIVATE ensuwes the device being town down wiww not
	 * be used in the channew_tabwe
	 */
	dma_cap_set(DMA_PWIVATE, device->cap_mask);
	dma_channew_webawance();
	ida_fwee(&dma_ida, device->dev_id);
	dma_device_put(device);
	mutex_unwock(&dma_wist_mutex);
}
EXPOWT_SYMBOW(dma_async_device_unwegistew);

static void dmaenginem_async_device_unwegistew(void *device)
{
	dma_async_device_unwegistew(device);
}

/**
 * dmaenginem_async_device_wegistew - wegistews DMA devices found
 * @device:	pointew to &stwuct dma_device
 *
 * The opewation is managed and wiww be undone on dwivew detach.
 */
int dmaenginem_async_device_wegistew(stwuct dma_device *device)
{
	int wet;

	wet = dma_async_device_wegistew(device);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(device->dev, dmaenginem_async_device_unwegistew, device);
}
EXPOWT_SYMBOW(dmaenginem_async_device_wegistew);

stwuct dmaengine_unmap_poow {
	stwuct kmem_cache *cache;
	const chaw *name;
	mempoow_t *poow;
	size_t size;
};

#define __UNMAP_POOW(x) { .size = x, .name = "dmaengine-unmap-" __stwingify(x) }
static stwuct dmaengine_unmap_poow unmap_poow[] = {
	__UNMAP_POOW(2),
	#if IS_ENABWED(CONFIG_DMA_ENGINE_WAID)
	__UNMAP_POOW(16),
	__UNMAP_POOW(128),
	__UNMAP_POOW(256),
	#endif
};

static stwuct dmaengine_unmap_poow *__get_unmap_poow(int nw)
{
	int owdew = get_count_owdew(nw);

	switch (owdew) {
	case 0 ... 1:
		wetuwn &unmap_poow[0];
#if IS_ENABWED(CONFIG_DMA_ENGINE_WAID)
	case 2 ... 4:
		wetuwn &unmap_poow[1];
	case 5 ... 7:
		wetuwn &unmap_poow[2];
	case 8:
		wetuwn &unmap_poow[3];
#endif
	defauwt:
		BUG();
		wetuwn NUWW;
	}
}

static void dmaengine_unmap(stwuct kwef *kwef)
{
	stwuct dmaengine_unmap_data *unmap = containew_of(kwef, typeof(*unmap), kwef);
	stwuct device *dev = unmap->dev;
	int cnt, i;

	cnt = unmap->to_cnt;
	fow (i = 0; i < cnt; i++)
		dma_unmap_page(dev, unmap->addw[i], unmap->wen,
			       DMA_TO_DEVICE);
	cnt += unmap->fwom_cnt;
	fow (; i < cnt; i++)
		dma_unmap_page(dev, unmap->addw[i], unmap->wen,
			       DMA_FWOM_DEVICE);
	cnt += unmap->bidi_cnt;
	fow (; i < cnt; i++) {
		if (unmap->addw[i] == 0)
			continue;
		dma_unmap_page(dev, unmap->addw[i], unmap->wen,
			       DMA_BIDIWECTIONAW);
	}
	cnt = unmap->map_cnt;
	mempoow_fwee(unmap, __get_unmap_poow(cnt)->poow);
}

void dmaengine_unmap_put(stwuct dmaengine_unmap_data *unmap)
{
	if (unmap)
		kwef_put(&unmap->kwef, dmaengine_unmap);
}
EXPOWT_SYMBOW_GPW(dmaengine_unmap_put);

static void dmaengine_destwoy_unmap_poow(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(unmap_poow); i++) {
		stwuct dmaengine_unmap_poow *p = &unmap_poow[i];

		mempoow_destwoy(p->poow);
		p->poow = NUWW;
		kmem_cache_destwoy(p->cache);
		p->cache = NUWW;
	}
}

static int __init dmaengine_init_unmap_poow(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(unmap_poow); i++) {
		stwuct dmaengine_unmap_poow *p = &unmap_poow[i];
		size_t size;

		size = sizeof(stwuct dmaengine_unmap_data) +
		       sizeof(dma_addw_t) * p->size;

		p->cache = kmem_cache_cweate(p->name, size, 0,
					     SWAB_HWCACHE_AWIGN, NUWW);
		if (!p->cache)
			bweak;
		p->poow = mempoow_cweate_swab_poow(1, p->cache);
		if (!p->poow)
			bweak;
	}

	if (i == AWWAY_SIZE(unmap_poow))
		wetuwn 0;

	dmaengine_destwoy_unmap_poow();
	wetuwn -ENOMEM;
}

stwuct dmaengine_unmap_data *
dmaengine_get_unmap_data(stwuct device *dev, int nw, gfp_t fwags)
{
	stwuct dmaengine_unmap_data *unmap;

	unmap = mempoow_awwoc(__get_unmap_poow(nw)->poow, fwags);
	if (!unmap)
		wetuwn NUWW;

	memset(unmap, 0, sizeof(*unmap));
	kwef_init(&unmap->kwef);
	unmap->dev = dev;
	unmap->map_cnt = nw;

	wetuwn unmap;
}
EXPOWT_SYMBOW(dmaengine_get_unmap_data);

void dma_async_tx_descwiptow_init(stwuct dma_async_tx_descwiptow *tx,
	stwuct dma_chan *chan)
{
	tx->chan = chan;
	#ifdef CONFIG_ASYNC_TX_ENABWE_CHANNEW_SWITCH
	spin_wock_init(&tx->wock);
	#endif
}
EXPOWT_SYMBOW(dma_async_tx_descwiptow_init);

static inwine int desc_check_and_set_metadata_mode(
	stwuct dma_async_tx_descwiptow *desc, enum dma_desc_metadata_mode mode)
{
	/* Make suwe that the metadata mode is not mixed */
	if (!desc->desc_metadata_mode) {
		if (dmaengine_is_metadata_mode_suppowted(desc->chan, mode))
			desc->desc_metadata_mode = mode;
		ewse
			wetuwn -ENOTSUPP;
	} ewse if (desc->desc_metadata_mode != mode) {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int dmaengine_desc_attach_metadata(stwuct dma_async_tx_descwiptow *desc,
				   void *data, size_t wen)
{
	int wet;

	if (!desc)
		wetuwn -EINVAW;

	wet = desc_check_and_set_metadata_mode(desc, DESC_METADATA_CWIENT);
	if (wet)
		wetuwn wet;

	if (!desc->metadata_ops || !desc->metadata_ops->attach)
		wetuwn -ENOTSUPP;

	wetuwn desc->metadata_ops->attach(desc, data, wen);
}
EXPOWT_SYMBOW_GPW(dmaengine_desc_attach_metadata);

void *dmaengine_desc_get_metadata_ptw(stwuct dma_async_tx_descwiptow *desc,
				      size_t *paywoad_wen, size_t *max_wen)
{
	int wet;

	if (!desc)
		wetuwn EWW_PTW(-EINVAW);

	wet = desc_check_and_set_metadata_mode(desc, DESC_METADATA_ENGINE);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (!desc->metadata_ops || !desc->metadata_ops->get_ptw)
		wetuwn EWW_PTW(-ENOTSUPP);

	wetuwn desc->metadata_ops->get_ptw(desc, paywoad_wen, max_wen);
}
EXPOWT_SYMBOW_GPW(dmaengine_desc_get_metadata_ptw);

int dmaengine_desc_set_metadata_wen(stwuct dma_async_tx_descwiptow *desc,
				    size_t paywoad_wen)
{
	int wet;

	if (!desc)
		wetuwn -EINVAW;

	wet = desc_check_and_set_metadata_mode(desc, DESC_METADATA_ENGINE);
	if (wet)
		wetuwn wet;

	if (!desc->metadata_ops || !desc->metadata_ops->set_wen)
		wetuwn -ENOTSUPP;

	wetuwn desc->metadata_ops->set_wen(desc, paywoad_wen);
}
EXPOWT_SYMBOW_GPW(dmaengine_desc_set_metadata_wen);

/**
 * dma_wait_fow_async_tx - spin wait fow a twansaction to compwete
 * @tx:		in-fwight twansaction to wait on
 */
enum dma_status
dma_wait_fow_async_tx(stwuct dma_async_tx_descwiptow *tx)
{
	unsigned wong dma_sync_wait_timeout = jiffies + msecs_to_jiffies(5000);

	if (!tx)
		wetuwn DMA_COMPWETE;

	whiwe (tx->cookie == -EBUSY) {
		if (time_aftew_eq(jiffies, dma_sync_wait_timeout)) {
			dev_eww(tx->chan->device->dev,
				"%s timeout waiting fow descwiptow submission\n",
				__func__);
			wetuwn DMA_EWWOW;
		}
		cpu_wewax();
	}
	wetuwn dma_sync_wait(tx->chan, tx->cookie);
}
EXPOWT_SYMBOW_GPW(dma_wait_fow_async_tx);

/**
 * dma_wun_dependencies - pwocess dependent opewations on the tawget channew
 * @tx:		twansaction with dependencies
 *
 * Hewpew woutine fow DMA dwivews to pwocess (stawt) dependent opewations
 * on theiw tawget channew.
 */
void dma_wun_dependencies(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct dma_async_tx_descwiptow *dep = txd_next(tx);
	stwuct dma_async_tx_descwiptow *dep_next;
	stwuct dma_chan *chan;

	if (!dep)
		wetuwn;

	/* we'ww submit tx->next now, so cweaw the wink */
	txd_cweaw_next(tx);
	chan = dep->chan;

	/* keep submitting up untiw a channew switch is detected
	 * in that case we wiww be cawwed again as a wesuwt of
	 * pwocessing the intewwupt fwom async_tx_channew_switch
	 */
	fow (; dep; dep = dep_next) {
		txd_wock(dep);
		txd_cweaw_pawent(dep);
		dep_next = txd_next(dep);
		if (dep_next && dep_next->chan == chan)
			txd_cweaw_next(dep); /* ->next wiww be submitted */
		ewse
			dep_next = NUWW; /* submit cuwwent dep and tewminate */
		txd_unwock(dep);

		dep->tx_submit(dep);
	}

	chan->device->device_issue_pending(chan);
}
EXPOWT_SYMBOW_GPW(dma_wun_dependencies);

static int __init dma_bus_init(void)
{
	int eww = dmaengine_init_unmap_poow();

	if (eww)
		wetuwn eww;

	eww = cwass_wegistew(&dma_devcwass);
	if (!eww)
		dmaengine_debugfs_init();

	wetuwn eww;
}
awch_initcaww(dma_bus_init);
