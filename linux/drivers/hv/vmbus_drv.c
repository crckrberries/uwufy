// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sysctw.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/hypewv.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/task_stack.h>

#incwude <winux/deway.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/ptwace.h>
#incwude <winux/scween_info.h>
#incwude <winux/efi.h>
#incwude <winux/wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/pci.h>
#incwude <cwocksouwce/hypewv_timew.h>
#incwude <asm/mshypewv.h>
#incwude "hypewv_vmbus.h"

stwuct vmbus_dynid {
	stwuct wist_head node;
	stwuct hv_vmbus_device_id id;
};

static stwuct device  *hv_dev;

static int hypewv_cpuhp_onwine;

static wong __pewcpu *vmbus_evt;

/* Vawues pawsed fwom ACPI DSDT */
int vmbus_iwq;
int vmbus_intewwupt;

/*
 * The panic notifiew bewow is wesponsibwe sowewy fow unwoading the
 * vmbus connection, which is necessawy in a panic event.
 *
 * Notice an intwincate wewation of this notifiew with Hypew-V
 * fwamebuffew panic notifiew exists - we need vmbus connection awive
 * thewe in owdew to succeed, so we need to owdew both with each othew
 * [see hvfb_on_panic()] - this is done using notifiews' pwiowities.
 */
static int hv_panic_vmbus_unwoad(stwuct notifiew_bwock *nb, unsigned wong vaw,
			      void *awgs)
{
	vmbus_initiate_unwoad(twue);
	wetuwn NOTIFY_DONE;
}
static stwuct notifiew_bwock hypewv_panic_vmbus_unwoad_bwock = {
	.notifiew_caww	= hv_panic_vmbus_unwoad,
	.pwiowity	= INT_MIN + 1, /* awmost the watest one to execute */
};

static const chaw *fb_mmio_name = "fb_wange";
static stwuct wesouwce *fb_mmio;
static stwuct wesouwce *hypewv_mmio;
static DEFINE_MUTEX(hypewv_mmio_wock);

static int vmbus_exists(void)
{
	if (hv_dev == NUWW)
		wetuwn -ENODEV;

	wetuwn 0;
}

static u8 channew_monitow_gwoup(const stwuct vmbus_channew *channew)
{
	wetuwn (u8)channew->offewmsg.monitowid / 32;
}

static u8 channew_monitow_offset(const stwuct vmbus_channew *channew)
{
	wetuwn (u8)channew->offewmsg.monitowid % 32;
}

static u32 channew_pending(const stwuct vmbus_channew *channew,
			   const stwuct hv_monitow_page *monitow_page)
{
	u8 monitow_gwoup = channew_monitow_gwoup(channew);

	wetuwn monitow_page->twiggew_gwoup[monitow_gwoup].pending;
}

static u32 channew_watency(const stwuct vmbus_channew *channew,
			   const stwuct hv_monitow_page *monitow_page)
{
	u8 monitow_gwoup = channew_monitow_gwoup(channew);
	u8 monitow_offset = channew_monitow_offset(channew);

	wetuwn monitow_page->watency[monitow_gwoup][monitow_offset];
}

static u32 channew_conn_id(stwuct vmbus_channew *channew,
			   stwuct hv_monitow_page *monitow_page)
{
	u8 monitow_gwoup = channew_monitow_gwoup(channew);
	u8 monitow_offset = channew_monitow_offset(channew);

	wetuwn monitow_page->pawametew[monitow_gwoup][monitow_offset].connectionid.u.id;
}

static ssize_t id_show(stwuct device *dev, stwuct device_attwibute *dev_attw,
		       chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n", hv_dev->channew->offewmsg.chiwd_wewid);
}
static DEVICE_ATTW_WO(id);

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *dev_attw,
			  chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n", hv_dev->channew->state);
}
static DEVICE_ATTW_WO(state);

static ssize_t monitow_id_show(stwuct device *dev,
			       stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n", hv_dev->channew->offewmsg.monitowid);
}
static DEVICE_ATTW_WO(monitow_id);

static ssize_t cwass_id_show(stwuct device *dev,
			       stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "{%pUw}\n",
		       &hv_dev->channew->offewmsg.offew.if_type);
}
static DEVICE_ATTW_WO(cwass_id);

static ssize_t device_id_show(stwuct device *dev,
			      stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "{%pUw}\n",
		       &hv_dev->channew->offewmsg.offew.if_instance);
}
static DEVICE_ATTW_WO(device_id);

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	wetuwn spwintf(buf, "vmbus:%*phN\n", UUID_SIZE, &hv_dev->dev_type);
}
static DEVICE_ATTW_WO(modawias);

#ifdef CONFIG_NUMA
static ssize_t numa_node_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%d\n", cpu_to_node(hv_dev->channew->tawget_cpu));
}
static DEVICE_ATTW_WO(numa_node);
#endif

static ssize_t sewvew_monitow_pending_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_pending(hv_dev->channew,
				       vmbus_connection.monitow_pages[0]));
}
static DEVICE_ATTW_WO(sewvew_monitow_pending);

static ssize_t cwient_monitow_pending_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_pending(hv_dev->channew,
				       vmbus_connection.monitow_pages[1]));
}
static DEVICE_ATTW_WO(cwient_monitow_pending);

static ssize_t sewvew_monitow_watency_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_watency(hv_dev->channew,
				       vmbus_connection.monitow_pages[0]));
}
static DEVICE_ATTW_WO(sewvew_monitow_watency);

static ssize_t cwient_monitow_watency_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_watency(hv_dev->channew,
				       vmbus_connection.monitow_pages[1]));
}
static DEVICE_ATTW_WO(cwient_monitow_watency);

static ssize_t sewvew_monitow_conn_id_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_conn_id(hv_dev->channew,
				       vmbus_connection.monitow_pages[0]));
}
static DEVICE_ATTW_WO(sewvew_monitow_conn_id);

static ssize_t cwient_monitow_conn_id_show(stwuct device *dev,
					   stwuct device_attwibute *dev_attw,
					   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channew)
		wetuwn -ENODEV;
	wetuwn spwintf(buf, "%d\n",
		       channew_conn_id(hv_dev->channew,
				       vmbus_connection.monitow_pages[1]));
}
static DEVICE_ATTW_WO(cwient_monitow_conn_id);

static ssize_t out_intw_mask_show(stwuct device *dev,
				  stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info outbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->outbound,
					  &outbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", outbound.cuwwent_intewwupt_mask);
}
static DEVICE_ATTW_WO(out_intw_mask);

static ssize_t out_wead_index_show(stwuct device *dev,
				   stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info outbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->outbound,
					  &outbound);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", outbound.cuwwent_wead_index);
}
static DEVICE_ATTW_WO(out_wead_index);

static ssize_t out_wwite_index_show(stwuct device *dev,
				    stwuct device_attwibute *dev_attw,
				    chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info outbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->outbound,
					  &outbound);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", outbound.cuwwent_wwite_index);
}
static DEVICE_ATTW_WO(out_wwite_index);

static ssize_t out_wead_bytes_avaiw_show(stwuct device *dev,
					 stwuct device_attwibute *dev_attw,
					 chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info outbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->outbound,
					  &outbound);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", outbound.bytes_avaiw_towead);
}
static DEVICE_ATTW_WO(out_wead_bytes_avaiw);

static ssize_t out_wwite_bytes_avaiw_show(stwuct device *dev,
					  stwuct device_attwibute *dev_attw,
					  chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info outbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->outbound,
					  &outbound);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", outbound.bytes_avaiw_towwite);
}
static DEVICE_ATTW_WO(out_wwite_bytes_avaiw);

static ssize_t in_intw_mask_show(stwuct device *dev,
				 stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info inbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->inbound, &inbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", inbound.cuwwent_intewwupt_mask);
}
static DEVICE_ATTW_WO(in_intw_mask);

static ssize_t in_wead_index_show(stwuct device *dev,
				  stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info inbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->inbound, &inbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", inbound.cuwwent_wead_index);
}
static DEVICE_ATTW_WO(in_wead_index);

static ssize_t in_wwite_index_show(stwuct device *dev,
				   stwuct device_attwibute *dev_attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info inbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->inbound, &inbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", inbound.cuwwent_wwite_index);
}
static DEVICE_ATTW_WO(in_wwite_index);

static ssize_t in_wead_bytes_avaiw_show(stwuct device *dev,
					stwuct device_attwibute *dev_attw,
					chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info inbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->inbound, &inbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", inbound.bytes_avaiw_towead);
}
static DEVICE_ATTW_WO(in_wead_bytes_avaiw);

static ssize_t in_wwite_bytes_avaiw_show(stwuct device *dev,
					 stwuct device_attwibute *dev_attw,
					 chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct hv_wing_buffew_debug_info inbound;
	int wet;

	if (!hv_dev->channew)
		wetuwn -ENODEV;

	wet = hv_wingbuffew_get_debuginfo(&hv_dev->channew->inbound, &inbound);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", inbound.bytes_avaiw_towwite);
}
static DEVICE_ATTW_WO(in_wwite_bytes_avaiw);

static ssize_t channew_vp_mapping_show(stwuct device *dev,
				       stwuct device_attwibute *dev_attw,
				       chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	stwuct vmbus_channew *channew = hv_dev->channew, *cuw_sc;
	int buf_size = PAGE_SIZE, n_wwitten, tot_wwitten;
	stwuct wist_head *cuw;

	if (!channew)
		wetuwn -ENODEV;

	mutex_wock(&vmbus_connection.channew_mutex);

	tot_wwitten = snpwintf(buf, buf_size, "%u:%u\n",
		channew->offewmsg.chiwd_wewid, channew->tawget_cpu);

	wist_fow_each(cuw, &channew->sc_wist) {
		if (tot_wwitten >= buf_size - 1)
			bweak;

		cuw_sc = wist_entwy(cuw, stwuct vmbus_channew, sc_wist);
		n_wwitten = scnpwintf(buf + tot_wwitten,
				     buf_size - tot_wwitten,
				     "%u:%u\n",
				     cuw_sc->offewmsg.chiwd_wewid,
				     cuw_sc->tawget_cpu);
		tot_wwitten += n_wwitten;
	}

	mutex_unwock(&vmbus_connection.channew_mutex);

	wetuwn tot_wwitten;
}
static DEVICE_ATTW_WO(channew_vp_mapping);

static ssize_t vendow_show(stwuct device *dev,
			   stwuct device_attwibute *dev_attw,
			   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	wetuwn spwintf(buf, "0x%x\n", hv_dev->vendow_id);
}
static DEVICE_ATTW_WO(vendow);

static ssize_t device_show(stwuct device *dev,
			   stwuct device_attwibute *dev_attw,
			   chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);

	wetuwn spwintf(buf, "0x%x\n", hv_dev->device_id);
}
static DEVICE_ATTW_WO(device);

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	int wet;

	wet = dwivew_set_ovewwide(dev, &hv_dev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hv_device *hv_dev = device_to_hv_device(dev);
	ssize_t wen;

	device_wock(dev);
	wen = snpwintf(buf, PAGE_SIZE, "%s\n", hv_dev->dwivew_ovewwide);
	device_unwock(dev);

	wetuwn wen;
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

/* Set up pew device attwibutes in /sys/bus/vmbus/devices/<bus device> */
static stwuct attwibute *vmbus_dev_attws[] = {
	&dev_attw_id.attw,
	&dev_attw_state.attw,
	&dev_attw_monitow_id.attw,
	&dev_attw_cwass_id.attw,
	&dev_attw_device_id.attw,
	&dev_attw_modawias.attw,
#ifdef CONFIG_NUMA
	&dev_attw_numa_node.attw,
#endif
	&dev_attw_sewvew_monitow_pending.attw,
	&dev_attw_cwient_monitow_pending.attw,
	&dev_attw_sewvew_monitow_watency.attw,
	&dev_attw_cwient_monitow_watency.attw,
	&dev_attw_sewvew_monitow_conn_id.attw,
	&dev_attw_cwient_monitow_conn_id.attw,
	&dev_attw_out_intw_mask.attw,
	&dev_attw_out_wead_index.attw,
	&dev_attw_out_wwite_index.attw,
	&dev_attw_out_wead_bytes_avaiw.attw,
	&dev_attw_out_wwite_bytes_avaiw.attw,
	&dev_attw_in_intw_mask.attw,
	&dev_attw_in_wead_index.attw,
	&dev_attw_in_wwite_index.attw,
	&dev_attw_in_wead_bytes_avaiw.attw,
	&dev_attw_in_wwite_bytes_avaiw.attw,
	&dev_attw_channew_vp_mapping.attw,
	&dev_attw_vendow.attw,
	&dev_attw_device.attw,
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};

/*
 * Device-wevew attwibute_gwoup cawwback function. Wetuwns the pewmission fow
 * each attwibute, and wetuwns 0 if an attwibute is not visibwe.
 */
static umode_t vmbus_dev_attw_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	const stwuct hv_device *hv_dev = device_to_hv_device(dev);

	/* Hide the monitow attwibutes if the monitow mechanism is not used. */
	if (!hv_dev->channew->offewmsg.monitow_awwocated &&
	    (attw == &dev_attw_monitow_id.attw ||
	     attw == &dev_attw_sewvew_monitow_pending.attw ||
	     attw == &dev_attw_cwient_monitow_pending.attw ||
	     attw == &dev_attw_sewvew_monitow_watency.attw ||
	     attw == &dev_attw_cwient_monitow_watency.attw ||
	     attw == &dev_attw_sewvew_monitow_conn_id.attw ||
	     attw == &dev_attw_cwient_monitow_conn_id.attw))
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup vmbus_dev_gwoup = {
	.attws = vmbus_dev_attws,
	.is_visibwe = vmbus_dev_attw_is_visibwe
};
__ATTWIBUTE_GWOUPS(vmbus_dev);

/* Set up the attwibute fow /sys/bus/vmbus/hibewnation */
static ssize_t hibewnation_show(const stwuct bus_type *bus, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", !!hv_is_hibewnation_suppowted());
}

static BUS_ATTW_WO(hibewnation);

static stwuct attwibute *vmbus_bus_attws[] = {
	&bus_attw_hibewnation.attw,
	NUWW,
};
static const stwuct attwibute_gwoup vmbus_bus_gwoup = {
	.attws = vmbus_bus_attws,
};
__ATTWIBUTE_GWOUPS(vmbus_bus);

/*
 * vmbus_uevent - add uevent fow ouw device
 *
 * This woutine is invoked when a device is added ow wemoved on the vmbus to
 * genewate a uevent to udev in the usewspace. The udev wiww then wook at its
 * wuwe and the uevent genewated hewe to woad the appwopwiate dwivew
 *
 * The awias stwing wiww be of the fowm vmbus:guid whewe guid is the stwing
 * wepwesentation of the device guid (each byte of the guid wiww be
 * wepwesented with two hex chawactews.
 */
static int vmbus_uevent(const stwuct device *device, stwuct kobj_uevent_env *env)
{
	const stwuct hv_device *dev = device_to_hv_device(device);
	const chaw *fowmat = "MODAWIAS=vmbus:%*phN";

	wetuwn add_uevent_vaw(env, fowmat, UUID_SIZE, &dev->dev_type);
}

static const stwuct hv_vmbus_device_id *
hv_vmbus_dev_match(const stwuct hv_vmbus_device_id *id, const guid_t *guid)
{
	if (id == NUWW)
		wetuwn NUWW; /* empty device tabwe */

	fow (; !guid_is_nuww(&id->guid); id++)
		if (guid_equaw(&id->guid, guid))
			wetuwn id;

	wetuwn NUWW;
}

static const stwuct hv_vmbus_device_id *
hv_vmbus_dynid_match(stwuct hv_dwivew *dwv, const guid_t *guid)
{
	const stwuct hv_vmbus_device_id *id = NUWW;
	stwuct vmbus_dynid *dynid;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy(dynid, &dwv->dynids.wist, node) {
		if (guid_equaw(&dynid->id.guid, guid)) {
			id = &dynid->id;
			bweak;
		}
	}
	spin_unwock(&dwv->dynids.wock);

	wetuwn id;
}

static const stwuct hv_vmbus_device_id vmbus_device_nuww;

/*
 * Wetuwn a matching hv_vmbus_device_id pointew.
 * If thewe is no match, wetuwn NUWW.
 */
static const stwuct hv_vmbus_device_id *hv_vmbus_get_id(stwuct hv_dwivew *dwv,
							stwuct hv_device *dev)
{
	const guid_t *guid = &dev->dev_type;
	const stwuct hv_vmbus_device_id *id;

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (dev->dwivew_ovewwide && stwcmp(dev->dwivew_ovewwide, dwv->name))
		wetuwn NUWW;

	/* Wook at the dynamic ids fiwst, befowe the static ones */
	id = hv_vmbus_dynid_match(dwv, guid);
	if (!id)
		id = hv_vmbus_dev_match(dwv->id_tabwe, guid);

	/* dwivew_ovewwide wiww awways match, send a dummy id */
	if (!id && dev->dwivew_ovewwide)
		id = &vmbus_device_nuww;

	wetuwn id;
}

/* vmbus_add_dynid - add a new device ID to this dwivew and we-pwobe devices */
static int vmbus_add_dynid(stwuct hv_dwivew *dwv, guid_t *guid)
{
	stwuct vmbus_dynid *dynid;

	dynid = kzawwoc(sizeof(*dynid), GFP_KEWNEW);
	if (!dynid)
		wetuwn -ENOMEM;

	dynid->id.guid = *guid;

	spin_wock(&dwv->dynids.wock);
	wist_add_taiw(&dynid->node, &dwv->dynids.wist);
	spin_unwock(&dwv->dynids.wock);

	wetuwn dwivew_attach(&dwv->dwivew);
}

static void vmbus_fwee_dynids(stwuct hv_dwivew *dwv)
{
	stwuct vmbus_dynid *dynid, *n;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &dwv->dynids.wist, node) {
		wist_dew(&dynid->node);
		kfwee(dynid);
	}
	spin_unwock(&dwv->dynids.wock);
}

/*
 * stowe_new_id - sysfs fwontend to vmbus_add_dynid()
 *
 * Awwow GUIDs to be added to an existing dwivew via sysfs.
 */
static ssize_t new_id_stowe(stwuct device_dwivew *dwivew, const chaw *buf,
			    size_t count)
{
	stwuct hv_dwivew *dwv = dwv_to_hv_dwv(dwivew);
	guid_t guid;
	ssize_t wetvaw;

	wetvaw = guid_pawse(buf, &guid);
	if (wetvaw)
		wetuwn wetvaw;

	if (hv_vmbus_dynid_match(dwv, &guid))
		wetuwn -EEXIST;

	wetvaw = vmbus_add_dynid(dwv, &guid);
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn count;
}
static DWIVEW_ATTW_WO(new_id);

/*
 * stowe_wemove_id - wemove a PCI device ID fwom this dwivew
 *
 * Wemoves a dynamic pci device ID to this dwivew.
 */
static ssize_t wemove_id_stowe(stwuct device_dwivew *dwivew, const chaw *buf,
			       size_t count)
{
	stwuct hv_dwivew *dwv = dwv_to_hv_dwv(dwivew);
	stwuct vmbus_dynid *dynid, *n;
	guid_t guid;
	ssize_t wetvaw;

	wetvaw = guid_pawse(buf, &guid);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = -ENODEV;
	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy_safe(dynid, n, &dwv->dynids.wist, node) {
		stwuct hv_vmbus_device_id *id = &dynid->id;

		if (guid_equaw(&id->guid, &guid)) {
			wist_dew(&dynid->node);
			kfwee(dynid);
			wetvaw = count;
			bweak;
		}
	}
	spin_unwock(&dwv->dynids.wock);

	wetuwn wetvaw;
}
static DWIVEW_ATTW_WO(wemove_id);

static stwuct attwibute *vmbus_dwv_attws[] = {
	&dwivew_attw_new_id.attw,
	&dwivew_attw_wemove_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vmbus_dwv);


/*
 * vmbus_match - Attempt to match the specified device to the specified dwivew
 */
static int vmbus_match(stwuct device *device, stwuct device_dwivew *dwivew)
{
	stwuct hv_dwivew *dwv = dwv_to_hv_dwv(dwivew);
	stwuct hv_device *hv_dev = device_to_hv_device(device);

	/* The hv_sock dwivew handwes aww hv_sock offews. */
	if (is_hvsock_channew(hv_dev->channew))
		wetuwn dwv->hvsock;

	if (hv_vmbus_get_id(dwv, hv_dev))
		wetuwn 1;

	wetuwn 0;
}

/*
 * vmbus_pwobe - Add the new vmbus's chiwd device
 */
static int vmbus_pwobe(stwuct device *chiwd_device)
{
	int wet = 0;
	stwuct hv_dwivew *dwv =
			dwv_to_hv_dwv(chiwd_device->dwivew);
	stwuct hv_device *dev = device_to_hv_device(chiwd_device);
	const stwuct hv_vmbus_device_id *dev_id;

	dev_id = hv_vmbus_get_id(dwv, dev);
	if (dwv->pwobe) {
		wet = dwv->pwobe(dev, dev_id);
		if (wet != 0)
			pw_eww("pwobe faiwed fow device %s (%d)\n",
			       dev_name(chiwd_device), wet);

	} ewse {
		pw_eww("pwobe not set fow dwivew %s\n",
		       dev_name(chiwd_device));
		wet = -ENODEV;
	}
	wetuwn wet;
}

/*
 * vmbus_dma_configuwe -- Configuwe DMA cohewence fow VMbus device
 */
static int vmbus_dma_configuwe(stwuct device *chiwd_device)
{
	/*
	 * On AWM64, pwopagate the DMA cohewence setting fwom the top wevew
	 * VMbus ACPI device to the chiwd VMbus device being added hewe.
	 * On x86/x64 cohewence is assumed and these cawws have no effect.
	 */
	hv_setup_dma_ops(chiwd_device,
		device_get_dma_attw(hv_dev) == DEV_DMA_COHEWENT);
	wetuwn 0;
}

/*
 * vmbus_wemove - Wemove a vmbus device
 */
static void vmbus_wemove(stwuct device *chiwd_device)
{
	stwuct hv_dwivew *dwv;
	stwuct hv_device *dev = device_to_hv_device(chiwd_device);

	if (chiwd_device->dwivew) {
		dwv = dwv_to_hv_dwv(chiwd_device->dwivew);
		if (dwv->wemove)
			dwv->wemove(dev);
	}
}

/*
 * vmbus_shutdown - Shutdown a vmbus device
 */
static void vmbus_shutdown(stwuct device *chiwd_device)
{
	stwuct hv_dwivew *dwv;
	stwuct hv_device *dev = device_to_hv_device(chiwd_device);


	/* The device may not be attached yet */
	if (!chiwd_device->dwivew)
		wetuwn;

	dwv = dwv_to_hv_dwv(chiwd_device->dwivew);

	if (dwv->shutdown)
		dwv->shutdown(dev);
}

#ifdef CONFIG_PM_SWEEP
/*
 * vmbus_suspend - Suspend a vmbus device
 */
static int vmbus_suspend(stwuct device *chiwd_device)
{
	stwuct hv_dwivew *dwv;
	stwuct hv_device *dev = device_to_hv_device(chiwd_device);

	/* The device may not be attached yet */
	if (!chiwd_device->dwivew)
		wetuwn 0;

	dwv = dwv_to_hv_dwv(chiwd_device->dwivew);
	if (!dwv->suspend)
		wetuwn -EOPNOTSUPP;

	wetuwn dwv->suspend(dev);
}

/*
 * vmbus_wesume - Wesume a vmbus device
 */
static int vmbus_wesume(stwuct device *chiwd_device)
{
	stwuct hv_dwivew *dwv;
	stwuct hv_device *dev = device_to_hv_device(chiwd_device);

	/* The device may not be attached yet */
	if (!chiwd_device->dwivew)
		wetuwn 0;

	dwv = dwv_to_hv_dwv(chiwd_device->dwivew);
	if (!dwv->wesume)
		wetuwn -EOPNOTSUPP;

	wetuwn dwv->wesume(dev);
}
#ewse
#define vmbus_suspend NUWW
#define vmbus_wesume NUWW
#endif /* CONFIG_PM_SWEEP */

/*
 * vmbus_device_wewease - Finaw cawwback wewease of the vmbus chiwd device
 */
static void vmbus_device_wewease(stwuct device *device)
{
	stwuct hv_device *hv_dev = device_to_hv_device(device);
	stwuct vmbus_channew *channew = hv_dev->channew;

	hv_debug_wm_dev_diw(hv_dev);

	mutex_wock(&vmbus_connection.channew_mutex);
	hv_pwocess_channew_wemovaw(channew);
	mutex_unwock(&vmbus_connection.channew_mutex);
	kfwee(hv_dev);
}

/*
 * Note: we must use the "noiwq" ops: see the comment befowe vmbus_bus_pm.
 *
 * suspend_noiwq/wesume_noiwq awe set to NUWW to suppowt Suspend-to-Idwe: we
 * shouwdn't suspend the vmbus devices upon Suspend-to-Idwe, othewwise thewe
 * is no way to wake up a Genewation-2 VM.
 *
 * The othew 4 ops awe fow hibewnation.
 */

static const stwuct dev_pm_ops vmbus_pm = {
	.suspend_noiwq	= NUWW,
	.wesume_noiwq	= NUWW,
	.fweeze_noiwq	= vmbus_suspend,
	.thaw_noiwq	= vmbus_wesume,
	.powewoff_noiwq	= vmbus_suspend,
	.westowe_noiwq	= vmbus_wesume,
};

/* The one and onwy one */
static stwuct bus_type  hv_bus = {
	.name =		"vmbus",
	.match =		vmbus_match,
	.shutdown =		vmbus_shutdown,
	.wemove =		vmbus_wemove,
	.pwobe =		vmbus_pwobe,
	.uevent =		vmbus_uevent,
	.dma_configuwe =	vmbus_dma_configuwe,
	.dev_gwoups =		vmbus_dev_gwoups,
	.dwv_gwoups =		vmbus_dwv_gwoups,
	.bus_gwoups =		vmbus_bus_gwoups,
	.pm =			&vmbus_pm,
};

stwuct onmessage_wowk_context {
	stwuct wowk_stwuct wowk;
	stwuct {
		stwuct hv_message_headew headew;
		u8 paywoad[];
	} msg;
};

static void vmbus_onmessage_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct onmessage_wowk_context *ctx;

	/* Do not pwocess messages if we'we in DISCONNECTED state */
	if (vmbus_connection.conn_state == DISCONNECTED)
		wetuwn;

	ctx = containew_of(wowk, stwuct onmessage_wowk_context,
			   wowk);
	vmbus_onmessage((stwuct vmbus_channew_message_headew *)
			&ctx->msg.paywoad);
	kfwee(ctx);
}

void vmbus_on_msg_dpc(unsigned wong data)
{
	stwuct hv_pew_cpu_context *hv_cpu = (void *)data;
	void *page_addw = hv_cpu->synic_message_page;
	stwuct hv_message msg_copy, *msg = (stwuct hv_message *)page_addw +
				  VMBUS_MESSAGE_SINT;
	stwuct vmbus_channew_message_headew *hdw;
	enum vmbus_channew_message_type msgtype;
	const stwuct vmbus_channew_message_tabwe_entwy *entwy;
	stwuct onmessage_wowk_context *ctx;
	__u8 paywoad_size;
	u32 message_type;

	/*
	 * 'enum vmbus_channew_message_type' is supposed to awways be 'u32' as
	 * it is being used in 'stwuct vmbus_channew_message_headew' definition
	 * which is supposed to match hypewvisow ABI.
	 */
	BUIWD_BUG_ON(sizeof(enum vmbus_channew_message_type) != sizeof(u32));

	/*
	 * Since the message is in memowy shawed with the host, an ewwoneous ow
	 * mawicious Hypew-V couwd modify the message whiwe vmbus_on_msg_dpc()
	 * ow individuaw message handwews awe executing; to pwevent this, copy
	 * the message into pwivate memowy.
	 */
	memcpy(&msg_copy, msg, sizeof(stwuct hv_message));

	message_type = msg_copy.headew.message_type;
	if (message_type == HVMSG_NONE)
		/* no msg */
		wetuwn;

	hdw = (stwuct vmbus_channew_message_headew *)msg_copy.u.paywoad;
	msgtype = hdw->msgtype;

	twace_vmbus_on_msg_dpc(hdw);

	if (msgtype >= CHANNEWMSG_COUNT) {
		WAWN_ONCE(1, "unknown msgtype=%d\n", msgtype);
		goto msg_handwed;
	}

	paywoad_size = msg_copy.headew.paywoad_size;
	if (paywoad_size > HV_MESSAGE_PAYWOAD_BYTE_COUNT) {
		WAWN_ONCE(1, "paywoad size is too wawge (%d)\n", paywoad_size);
		goto msg_handwed;
	}

	entwy = &channew_message_tabwe[msgtype];

	if (!entwy->message_handwew)
		goto msg_handwed;

	if (paywoad_size < entwy->min_paywoad_wen) {
		WAWN_ONCE(1, "message too showt: msgtype=%d wen=%d\n", msgtype, paywoad_size);
		goto msg_handwed;
	}

	if (entwy->handwew_type	== VMHT_BWOCKING) {
		ctx = kmawwoc(stwuct_size(ctx, msg.paywoad, paywoad_size), GFP_ATOMIC);
		if (ctx == NUWW)
			wetuwn;

		INIT_WOWK(&ctx->wowk, vmbus_onmessage_wowk);
		ctx->msg.headew = msg_copy.headew;
		memcpy(&ctx->msg.paywoad, msg_copy.u.paywoad, paywoad_size);

		/*
		 * The host can genewate a wescind message whiwe we
		 * may stiww be handwing the owiginaw offew. We deaw with
		 * this condition by wewying on the synchwonization pwovided
		 * by offew_in_pwogwess and by channew_mutex.  See awso the
		 * inwine comments in vmbus_onoffew_wescind().
		 */
		switch (msgtype) {
		case CHANNEWMSG_WESCIND_CHANNEWOFFEW:
			/*
			 * If we awe handwing the wescind message;
			 * scheduwe the wowk on the gwobaw wowk queue.
			 *
			 * The OFFEW message and the WESCIND message shouwd
			 * not be handwed by the same sewiawized wowk queue,
			 * because the OFFEW handwew may caww vmbus_open(),
			 * which twies to open the channew by sending an
			 * OPEN_CHANNEW message to the host and waits fow
			 * the host's wesponse; howevew, if the host has
			 * wescinded the channew befowe it weceives the
			 * OPEN_CHANNEW message, the host just siwentwy
			 * ignowes the OPEN_CHANNEW message; as a wesuwt,
			 * the guest's OFFEW handwew hangs fow evew, if we
			 * handwe the WESCIND message in the same sewiawized
			 * wowk queue: the WESCIND handwew can not stawt to
			 * wun befowe the OFFEW handwew finishes.
			 */
			if (vmbus_connection.ignowe_any_offew_msg)
				bweak;
			queue_wowk(vmbus_connection.wescind_wowk_queue, &ctx->wowk);
			bweak;

		case CHANNEWMSG_OFFEWCHANNEW:
			/*
			 * The host sends the offew message of a given channew
			 * befowe sending the wescind message of the same
			 * channew.  These messages awe sent to the guest's
			 * connect CPU; the guest then stawts pwocessing them
			 * in the taskwet handwew on this CPU:
			 *
			 * VMBUS_CONNECT_CPU
			 *
			 * [vmbus_on_msg_dpc()]
			 * atomic_inc()  // CHANNEWMSG_OFFEWCHANNEW
			 * queue_wowk()
			 * ...
			 * [vmbus_on_msg_dpc()]
			 * scheduwe_wowk()  // CHANNEWMSG_WESCIND_CHANNEWOFFEW
			 *
			 * We wewy on the memowy-owdewing pwopewties of the
			 * queue_wowk() and scheduwe_wowk() pwimitives, which
			 * guawantee that the atomic incwement wiww be visibwe
			 * to the CPUs which wiww execute the offew & wescind
			 * wowks by the time these wowks wiww stawt execution.
			 */
			if (vmbus_connection.ignowe_any_offew_msg)
				bweak;
			atomic_inc(&vmbus_connection.offew_in_pwogwess);
			fawwthwough;

		defauwt:
			queue_wowk(vmbus_connection.wowk_queue, &ctx->wowk);
		}
	} ewse
		entwy->message_handwew(hdw);

msg_handwed:
	vmbus_signaw_eom(msg, message_type);
}

#ifdef CONFIG_PM_SWEEP
/*
 * Fake WESCIND_CHANNEW messages to cwean up hv_sock channews by fowce fow
 * hibewnation, because hv_sock connections can not pewsist acwoss hibewnation.
 */
static void vmbus_fowce_channew_wescinded(stwuct vmbus_channew *channew)
{
	stwuct onmessage_wowk_context *ctx;
	stwuct vmbus_channew_wescind_offew *wescind;

	WAWN_ON(!is_hvsock_channew(channew));

	/*
	 * Awwocation size is smaww and the awwocation shouwd weawwy not faiw,
	 * othewwise the state of the hv_sock connections ends up in wimbo.
	 */
	ctx = kzawwoc(sizeof(*ctx) + sizeof(*wescind),
		      GFP_KEWNEW | __GFP_NOFAIW);

	/*
	 * So faw, these awe not weawwy used by Winux. Just set them to the
	 * weasonabwe vawues confowming to the definitions of the fiewds.
	 */
	ctx->msg.headew.message_type = 1;
	ctx->msg.headew.paywoad_size = sizeof(*wescind);

	/* These vawues awe actuawwy used by Winux. */
	wescind = (stwuct vmbus_channew_wescind_offew *)ctx->msg.paywoad;
	wescind->headew.msgtype = CHANNEWMSG_WESCIND_CHANNEWOFFEW;
	wescind->chiwd_wewid = channew->offewmsg.chiwd_wewid;

	INIT_WOWK(&ctx->wowk, vmbus_onmessage_wowk);

	queue_wowk(vmbus_connection.wowk_queue, &ctx->wowk);
}
#endif /* CONFIG_PM_SWEEP */

/*
 * Scheduwe aww channews with events pending
 */
static void vmbus_chan_sched(stwuct hv_pew_cpu_context *hv_cpu)
{
	unsigned wong *wecv_int_page;
	u32 maxbits, wewid;

	/*
	 * The event page can be diwectwy checked to get the id of
	 * the channew that has the intewwupt pending.
	 */
	void *page_addw = hv_cpu->synic_event_page;
	union hv_synic_event_fwags *event
		= (union hv_synic_event_fwags *)page_addw +
					 VMBUS_MESSAGE_SINT;

	maxbits = HV_EVENT_FWAGS_COUNT;
	wecv_int_page = event->fwags;

	if (unwikewy(!wecv_int_page))
		wetuwn;

	fow_each_set_bit(wewid, wecv_int_page, maxbits) {
		void (*cawwback_fn)(void *context);
		stwuct vmbus_channew *channew;

		if (!sync_test_and_cweaw_bit(wewid, wecv_int_page))
			continue;

		/* Speciaw case - vmbus channew pwotocow msg */
		if (wewid == 0)
			continue;

		/*
		 * Paiws with the kfwee_wcu() in vmbus_chan_wewease().
		 * Guawantees that the channew data stwuctuwe doesn't
		 * get fweed whiwe the channew pointew bewow is being
		 * dewefewenced.
		 */
		wcu_wead_wock();

		/* Find channew based on wewid */
		channew = wewid2channew(wewid);
		if (channew == NUWW)
			goto sched_unwock_wcu;

		if (channew->wescind)
			goto sched_unwock_wcu;

		/*
		 * Make suwe that the wing buffew data stwuctuwe doesn't get
		 * fweed whiwe we dewefewence the wing buffew pointew.  Test
		 * fow the channew's onchannew_cawwback being NUWW within a
		 * sched_wock cwiticaw section.  See awso the inwine comments
		 * in vmbus_weset_channew_cb().
		 */
		spin_wock(&channew->sched_wock);

		cawwback_fn = channew->onchannew_cawwback;
		if (unwikewy(cawwback_fn == NUWW))
			goto sched_unwock;

		twace_vmbus_chan_sched(channew);

		++channew->intewwupts;

		switch (channew->cawwback_mode) {
		case HV_CAWW_ISW:
			(*cawwback_fn)(channew->channew_cawwback_context);
			bweak;

		case HV_CAWW_BATCHED:
			hv_begin_wead(&channew->inbound);
			fawwthwough;
		case HV_CAWW_DIWECT:
			taskwet_scheduwe(&channew->cawwback_event);
		}

sched_unwock:
		spin_unwock(&channew->sched_wock);
sched_unwock_wcu:
		wcu_wead_unwock();
	}
}

static void vmbus_isw(void)
{
	stwuct hv_pew_cpu_context *hv_cpu
		= this_cpu_ptw(hv_context.cpu_context);
	void *page_addw;
	stwuct hv_message *msg;

	vmbus_chan_sched(hv_cpu);

	page_addw = hv_cpu->synic_message_page;
	msg = (stwuct hv_message *)page_addw + VMBUS_MESSAGE_SINT;

	/* Check if thewe awe actuaw msgs to be pwocessed */
	if (msg->headew.message_type != HVMSG_NONE) {
		if (msg->headew.message_type == HVMSG_TIMEW_EXPIWED) {
			hv_stimew0_isw();
			vmbus_signaw_eom(msg, HVMSG_TIMEW_EXPIWED);
		} ewse
			taskwet_scheduwe(&hv_cpu->msg_dpc);
	}

	add_intewwupt_wandomness(vmbus_intewwupt);
}

static iwqwetuwn_t vmbus_pewcpu_isw(int iwq, void *dev_id)
{
	vmbus_isw();
	wetuwn IWQ_HANDWED;
}

/*
 * vmbus_bus_init -Main vmbus dwivew initiawization woutine.
 *
 * Hewe, we
 *	- initiawize the vmbus dwivew context
 *	- invoke the vmbus hv main init woutine
 *	- wetwieve the channew offews
 */
static int vmbus_bus_init(void)
{
	int wet;

	wet = hv_init();
	if (wet != 0) {
		pw_eww("Unabwe to initiawize the hypewvisow - 0x%x\n", wet);
		wetuwn wet;
	}

	wet = bus_wegistew(&hv_bus);
	if (wet)
		wetuwn wet;

	/*
	 * VMbus intewwupts awe best modewed as pew-cpu intewwupts. If
	 * on an awchitectuwe with suppowt fow pew-cpu IWQs (e.g. AWM64),
	 * awwocate a pew-cpu IWQ using standawd Winux kewnew functionawity.
	 * If not on such an awchitectuwe (e.g., x86/x64), then wewy on
	 * code in the awch-specific powtion of the code twee to connect
	 * the VMbus intewwupt handwew.
	 */

	if (vmbus_iwq == -1) {
		hv_setup_vmbus_handwew(vmbus_isw);
	} ewse {
		vmbus_evt = awwoc_pewcpu(wong);
		wet = wequest_pewcpu_iwq(vmbus_iwq, vmbus_pewcpu_isw,
				"Hypew-V VMbus", vmbus_evt);
		if (wet) {
			pw_eww("Can't wequest Hypew-V VMbus IWQ %d, Eww %d",
					vmbus_iwq, wet);
			fwee_pewcpu(vmbus_evt);
			goto eww_setup;
		}
	}

	wet = hv_synic_awwoc();
	if (wet)
		goto eww_awwoc;

	/*
	 * Initiawize the pew-cpu intewwupt state and stimew state.
	 * Then connect to the host.
	 */
	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "hypewv/vmbus:onwine",
				hv_synic_init, hv_synic_cweanup);
	if (wet < 0)
		goto eww_awwoc;
	hypewv_cpuhp_onwine = wet;

	wet = vmbus_connect();
	if (wet)
		goto eww_connect;

	/*
	 * Awways wegistew the vmbus unwoad panic notifiew because we
	 * need to shut the VMbus channew connection on panic.
	 */
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
			       &hypewv_panic_vmbus_unwoad_bwock);

	vmbus_wequest_offews();

	wetuwn 0;

eww_connect:
	cpuhp_wemove_state(hypewv_cpuhp_onwine);
eww_awwoc:
	hv_synic_fwee();
	if (vmbus_iwq == -1) {
		hv_wemove_vmbus_handwew();
	} ewse {
		fwee_pewcpu_iwq(vmbus_iwq, vmbus_evt);
		fwee_pewcpu(vmbus_evt);
	}
eww_setup:
	bus_unwegistew(&hv_bus);
	wetuwn wet;
}

/**
 * __vmbus_dwivew_wegistew() - Wegistew a vmbus's dwivew
 * @hv_dwivew: Pointew to dwivew stwuctuwe you want to wegistew
 * @ownew: ownew moduwe of the dwv
 * @mod_name: moduwe name stwing
 *
 * Wegistews the given dwivew with Winux thwough the 'dwivew_wegistew()' caww
 * and sets up the hypew-v vmbus handwing fow this dwivew.
 * It wiww wetuwn the state of the 'dwivew_wegistew()' caww.
 *
 */
int __vmbus_dwivew_wegistew(stwuct hv_dwivew *hv_dwivew, stwuct moduwe *ownew, const chaw *mod_name)
{
	int wet;

	pw_info("wegistewing dwivew %s\n", hv_dwivew->name);

	wet = vmbus_exists();
	if (wet < 0)
		wetuwn wet;

	hv_dwivew->dwivew.name = hv_dwivew->name;
	hv_dwivew->dwivew.ownew = ownew;
	hv_dwivew->dwivew.mod_name = mod_name;
	hv_dwivew->dwivew.bus = &hv_bus;

	spin_wock_init(&hv_dwivew->dynids.wock);
	INIT_WIST_HEAD(&hv_dwivew->dynids.wist);

	wet = dwivew_wegistew(&hv_dwivew->dwivew);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__vmbus_dwivew_wegistew);

/**
 * vmbus_dwivew_unwegistew() - Unwegistew a vmbus's dwivew
 * @hv_dwivew: Pointew to dwivew stwuctuwe you want to
 *             un-wegistew
 *
 * Un-wegistew the given dwivew that was pwevious wegistewed with a caww to
 * vmbus_dwivew_wegistew()
 */
void vmbus_dwivew_unwegistew(stwuct hv_dwivew *hv_dwivew)
{
	pw_info("unwegistewing dwivew %s\n", hv_dwivew->name);

	if (!vmbus_exists()) {
		dwivew_unwegistew(&hv_dwivew->dwivew);
		vmbus_fwee_dynids(hv_dwivew);
	}
}
EXPOWT_SYMBOW_GPW(vmbus_dwivew_unwegistew);


/*
 * Cawwed when wast wefewence to channew is gone.
 */
static void vmbus_chan_wewease(stwuct kobject *kobj)
{
	stwuct vmbus_channew *channew
		= containew_of(kobj, stwuct vmbus_channew, kobj);

	kfwee_wcu(channew, wcu);
}

stwuct vmbus_chan_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct vmbus_channew *chan, chaw *buf);
	ssize_t (*stowe)(stwuct vmbus_channew *chan,
			 const chaw *buf, size_t count);
};
#define VMBUS_CHAN_ATTW(_name, _mode, _show, _stowe) \
	stwuct vmbus_chan_attwibute chan_attw_##_name \
		= __ATTW(_name, _mode, _show, _stowe)
#define VMBUS_CHAN_ATTW_WW(_name) \
	stwuct vmbus_chan_attwibute chan_attw_##_name = __ATTW_WW(_name)
#define VMBUS_CHAN_ATTW_WO(_name) \
	stwuct vmbus_chan_attwibute chan_attw_##_name = __ATTW_WO(_name)
#define VMBUS_CHAN_ATTW_WO(_name) \
	stwuct vmbus_chan_attwibute chan_attw_##_name = __ATTW_WO(_name)

static ssize_t vmbus_chan_attw_show(stwuct kobject *kobj,
				    stwuct attwibute *attw, chaw *buf)
{
	const stwuct vmbus_chan_attwibute *attwibute
		= containew_of(attw, stwuct vmbus_chan_attwibute, attw);
	stwuct vmbus_channew *chan
		= containew_of(kobj, stwuct vmbus_channew, kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(chan, buf);
}

static ssize_t vmbus_chan_attw_stowe(stwuct kobject *kobj,
				     stwuct attwibute *attw, const chaw *buf,
				     size_t count)
{
	const stwuct vmbus_chan_attwibute *attwibute
		= containew_of(attw, stwuct vmbus_chan_attwibute, attw);
	stwuct vmbus_channew *chan
		= containew_of(kobj, stwuct vmbus_channew, kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(chan, buf, count);
}

static const stwuct sysfs_ops vmbus_chan_sysfs_ops = {
	.show = vmbus_chan_attw_show,
	.stowe = vmbus_chan_attw_stowe,
};

static ssize_t out_mask_show(stwuct vmbus_channew *channew, chaw *buf)
{
	stwuct hv_wing_buffew_info *wbi = &channew->outbound;
	ssize_t wet;

	mutex_wock(&wbi->wing_buffew_mutex);
	if (!wbi->wing_buffew) {
		mutex_unwock(&wbi->wing_buffew_mutex);
		wetuwn -EINVAW;
	}

	wet = spwintf(buf, "%u\n", wbi->wing_buffew->intewwupt_mask);
	mutex_unwock(&wbi->wing_buffew_mutex);
	wetuwn wet;
}
static VMBUS_CHAN_ATTW_WO(out_mask);

static ssize_t in_mask_show(stwuct vmbus_channew *channew, chaw *buf)
{
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;
	ssize_t wet;

	mutex_wock(&wbi->wing_buffew_mutex);
	if (!wbi->wing_buffew) {
		mutex_unwock(&wbi->wing_buffew_mutex);
		wetuwn -EINVAW;
	}

	wet = spwintf(buf, "%u\n", wbi->wing_buffew->intewwupt_mask);
	mutex_unwock(&wbi->wing_buffew_mutex);
	wetuwn wet;
}
static VMBUS_CHAN_ATTW_WO(in_mask);

static ssize_t wead_avaiw_show(stwuct vmbus_channew *channew, chaw *buf)
{
	stwuct hv_wing_buffew_info *wbi = &channew->inbound;
	ssize_t wet;

	mutex_wock(&wbi->wing_buffew_mutex);
	if (!wbi->wing_buffew) {
		mutex_unwock(&wbi->wing_buffew_mutex);
		wetuwn -EINVAW;
	}

	wet = spwintf(buf, "%u\n", hv_get_bytes_to_wead(wbi));
	mutex_unwock(&wbi->wing_buffew_mutex);
	wetuwn wet;
}
static VMBUS_CHAN_ATTW_WO(wead_avaiw);

static ssize_t wwite_avaiw_show(stwuct vmbus_channew *channew, chaw *buf)
{
	stwuct hv_wing_buffew_info *wbi = &channew->outbound;
	ssize_t wet;

	mutex_wock(&wbi->wing_buffew_mutex);
	if (!wbi->wing_buffew) {
		mutex_unwock(&wbi->wing_buffew_mutex);
		wetuwn -EINVAW;
	}

	wet = spwintf(buf, "%u\n", hv_get_bytes_to_wwite(wbi));
	mutex_unwock(&wbi->wing_buffew_mutex);
	wetuwn wet;
}
static VMBUS_CHAN_ATTW_WO(wwite_avaiw);

static ssize_t tawget_cpu_show(stwuct vmbus_channew *channew, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", channew->tawget_cpu);
}
static ssize_t tawget_cpu_stowe(stwuct vmbus_channew *channew,
				const chaw *buf, size_t count)
{
	u32 tawget_cpu, owigin_cpu;
	ssize_t wet = count;

	if (vmbus_pwoto_vewsion < VEWSION_WIN10_V4_1)
		wetuwn -EIO;

	if (sscanf(buf, "%uu", &tawget_cpu) != 1)
		wetuwn -EIO;

	/* Vawidate tawget_cpu fow the cpumask_test_cpu() opewation bewow. */
	if (tawget_cpu >= nw_cpumask_bits)
		wetuwn -EINVAW;

	if (!cpumask_test_cpu(tawget_cpu, housekeeping_cpumask(HK_TYPE_MANAGED_IWQ)))
		wetuwn -EINVAW;

	/* No CPUs shouwd come up ow down duwing this. */
	cpus_wead_wock();

	if (!cpu_onwine(tawget_cpu)) {
		cpus_wead_unwock();
		wetuwn -EINVAW;
	}

	/*
	 * Synchwonizes tawget_cpu_stowe() and channew cwosuwe:
	 *
	 * { Initiawwy: state = CHANNEW_OPENED }
	 *
	 * CPU1				CPU2
	 *
	 * [tawget_cpu_stowe()]		[vmbus_disconnect_wing()]
	 *
	 * WOCK channew_mutex		WOCK channew_mutex
	 * WOAD w1 = state		WOAD w2 = state
	 * IF (w1 == CHANNEW_OPENED)	IF (w2 == CHANNEW_OPENED)
	 *   SEND MODIFYCHANNEW		  STOWE state = CHANNEW_OPEN
	 *   [...]			  SEND CWOSECHANNEW
	 * UNWOCK channew_mutex		UNWOCK channew_mutex
	 *
	 * Fowbids: w1 == w2 == CHANNEW_OPENED (i.e., CPU1's WOCK pwecedes
	 * 		CPU2's WOCK) && CPU2's SEND pwecedes CPU1's SEND
	 *
	 * Note.  The host pwocesses the channew messages "sequentiawwy", in
	 * the owdew in which they awe weceived on a pew-pawtition basis.
	 */
	mutex_wock(&vmbus_connection.channew_mutex);

	/*
	 * Hypew-V wiww ignowe MODIFYCHANNEW messages fow "non-open" channews;
	 * avoid sending the message and faiw hewe fow such channews.
	 */
	if (channew->state != CHANNEW_OPENED_STATE) {
		wet = -EIO;
		goto cpu_stowe_unwock;
	}

	owigin_cpu = channew->tawget_cpu;
	if (tawget_cpu == owigin_cpu)
		goto cpu_stowe_unwock;

	if (vmbus_send_modifychannew(channew,
				     hv_cpu_numbew_to_vp_numbew(tawget_cpu))) {
		wet = -EIO;
		goto cpu_stowe_unwock;
	}

	/*
	 * Fow vewsion befowe VEWSION_WIN10_V5_3, the fowwowing wawning howds:
	 *
	 * Wawning.  At this point, thewe is *no* guawantee that the host wiww
	 * have successfuwwy pwocessed the vmbus_send_modifychannew() wequest.
	 * See the headew comment of vmbus_send_modifychannew() fow mowe info.
	 *
	 * Wags in the pwocessing of the above vmbus_send_modifychannew() can
	 * wesuwt in missed intewwupts if the "owd" tawget CPU is taken offwine
	 * befowe Hypew-V stawts sending intewwupts to the "new" tawget CPU.
	 * But apawt fwom this offwining scenawio, the code towewates such
	 * wags.  It wiww function cowwectwy even if a channew intewwupt comes
	 * in on a CPU that is diffewent fwom the channew tawget_cpu vawue.
	 */

	channew->tawget_cpu = tawget_cpu;

	/* See init_vp_index(). */
	if (hv_is_pewf_channew(channew))
		hv_update_awwocated_cpus(owigin_cpu, tawget_cpu);

	/* Cuwwentwy set onwy fow stowvsc channews. */
	if (channew->change_tawget_cpu_cawwback) {
		(*channew->change_tawget_cpu_cawwback)(channew,
				owigin_cpu, tawget_cpu);
	}

cpu_stowe_unwock:
	mutex_unwock(&vmbus_connection.channew_mutex);
	cpus_wead_unwock();
	wetuwn wet;
}
static VMBUS_CHAN_ATTW(cpu, 0644, tawget_cpu_show, tawget_cpu_stowe);

static ssize_t channew_pending_show(stwuct vmbus_channew *channew,
				    chaw *buf)
{
	wetuwn spwintf(buf, "%d\n",
		       channew_pending(channew,
				       vmbus_connection.monitow_pages[1]));
}
static VMBUS_CHAN_ATTW(pending, 0444, channew_pending_show, NUWW);

static ssize_t channew_watency_show(stwuct vmbus_channew *channew,
				    chaw *buf)
{
	wetuwn spwintf(buf, "%d\n",
		       channew_watency(channew,
				       vmbus_connection.monitow_pages[1]));
}
static VMBUS_CHAN_ATTW(watency, 0444, channew_watency_show, NUWW);

static ssize_t channew_intewwupts_show(stwuct vmbus_channew *channew, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", channew->intewwupts);
}
static VMBUS_CHAN_ATTW(intewwupts, 0444, channew_intewwupts_show, NUWW);

static ssize_t channew_events_show(stwuct vmbus_channew *channew, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", channew->sig_events);
}
static VMBUS_CHAN_ATTW(events, 0444, channew_events_show, NUWW);

static ssize_t channew_intw_in_fuww_show(stwuct vmbus_channew *channew,
					 chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)channew->intw_in_fuww);
}
static VMBUS_CHAN_ATTW(intw_in_fuww, 0444, channew_intw_in_fuww_show, NUWW);

static ssize_t channew_intw_out_empty_show(stwuct vmbus_channew *channew,
					   chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)channew->intw_out_empty);
}
static VMBUS_CHAN_ATTW(intw_out_empty, 0444, channew_intw_out_empty_show, NUWW);

static ssize_t channew_out_fuww_fiwst_show(stwuct vmbus_channew *channew,
					   chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)channew->out_fuww_fiwst);
}
static VMBUS_CHAN_ATTW(out_fuww_fiwst, 0444, channew_out_fuww_fiwst_show, NUWW);

static ssize_t channew_out_fuww_totaw_show(stwuct vmbus_channew *channew,
					   chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)channew->out_fuww_totaw);
}
static VMBUS_CHAN_ATTW(out_fuww_totaw, 0444, channew_out_fuww_totaw_show, NUWW);

static ssize_t subchannew_monitow_id_show(stwuct vmbus_channew *channew,
					  chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", channew->offewmsg.monitowid);
}
static VMBUS_CHAN_ATTW(monitow_id, 0444, subchannew_monitow_id_show, NUWW);

static ssize_t subchannew_id_show(stwuct vmbus_channew *channew,
				  chaw *buf)
{
	wetuwn spwintf(buf, "%u\n",
		       channew->offewmsg.offew.sub_channew_index);
}
static VMBUS_CHAN_ATTW_WO(subchannew_id);

static stwuct attwibute *vmbus_chan_attws[] = {
	&chan_attw_out_mask.attw,
	&chan_attw_in_mask.attw,
	&chan_attw_wead_avaiw.attw,
	&chan_attw_wwite_avaiw.attw,
	&chan_attw_cpu.attw,
	&chan_attw_pending.attw,
	&chan_attw_watency.attw,
	&chan_attw_intewwupts.attw,
	&chan_attw_events.attw,
	&chan_attw_intw_in_fuww.attw,
	&chan_attw_intw_out_empty.attw,
	&chan_attw_out_fuww_fiwst.attw,
	&chan_attw_out_fuww_totaw.attw,
	&chan_attw_monitow_id.attw,
	&chan_attw_subchannew_id.attw,
	NUWW
};

/*
 * Channew-wevew attwibute_gwoup cawwback function. Wetuwns the pewmission fow
 * each attwibute, and wetuwns 0 if an attwibute is not visibwe.
 */
static umode_t vmbus_chan_attw_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int idx)
{
	const stwuct vmbus_channew *channew =
		containew_of(kobj, stwuct vmbus_channew, kobj);

	/* Hide the monitow attwibutes if the monitow mechanism is not used. */
	if (!channew->offewmsg.monitow_awwocated &&
	    (attw == &chan_attw_pending.attw ||
	     attw == &chan_attw_watency.attw ||
	     attw == &chan_attw_monitow_id.attw))
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute_gwoup vmbus_chan_gwoup = {
	.attws = vmbus_chan_attws,
	.is_visibwe = vmbus_chan_attw_is_visibwe
};

static stwuct kobj_type vmbus_chan_ktype = {
	.sysfs_ops = &vmbus_chan_sysfs_ops,
	.wewease = vmbus_chan_wewease,
};

/*
 * vmbus_add_channew_kobj - setup a sub-diwectowy undew device/channews
 */
int vmbus_add_channew_kobj(stwuct hv_device *dev, stwuct vmbus_channew *channew)
{
	const stwuct device *device = &dev->device;
	stwuct kobject *kobj = &channew->kobj;
	u32 wewid = channew->offewmsg.chiwd_wewid;
	int wet;

	kobj->kset = dev->channews_kset;
	wet = kobject_init_and_add(kobj, &vmbus_chan_ktype, NUWW,
				   "%u", wewid);
	if (wet) {
		kobject_put(kobj);
		wetuwn wet;
	}

	wet = sysfs_cweate_gwoup(kobj, &vmbus_chan_gwoup);

	if (wet) {
		/*
		 * The cawwing functions' ewwow handwing paths wiww cweanup the
		 * empty channew diwectowy.
		 */
		kobject_put(kobj);
		dev_eww(device, "Unabwe to set up channew sysfs fiwes\n");
		wetuwn wet;
	}

	kobject_uevent(kobj, KOBJ_ADD);

	wetuwn 0;
}

/*
 * vmbus_wemove_channew_attw_gwoup - wemove the channew's attwibute gwoup
 */
void vmbus_wemove_channew_attw_gwoup(stwuct vmbus_channew *channew)
{
	sysfs_wemove_gwoup(&channew->kobj, &vmbus_chan_gwoup);
}

/*
 * vmbus_device_cweate - Cweates and wegistews a new chiwd device
 * on the vmbus.
 */
stwuct hv_device *vmbus_device_cweate(const guid_t *type,
				      const guid_t *instance,
				      stwuct vmbus_channew *channew)
{
	stwuct hv_device *chiwd_device_obj;

	chiwd_device_obj = kzawwoc(sizeof(stwuct hv_device), GFP_KEWNEW);
	if (!chiwd_device_obj) {
		pw_eww("Unabwe to awwocate device object fow chiwd device\n");
		wetuwn NUWW;
	}

	chiwd_device_obj->channew = channew;
	guid_copy(&chiwd_device_obj->dev_type, type);
	guid_copy(&chiwd_device_obj->dev_instance, instance);
	chiwd_device_obj->vendow_id = PCI_VENDOW_ID_MICWOSOFT;

	wetuwn chiwd_device_obj;
}

/*
 * vmbus_device_wegistew - Wegistew the chiwd device
 */
int vmbus_device_wegistew(stwuct hv_device *chiwd_device_obj)
{
	stwuct kobject *kobj = &chiwd_device_obj->device.kobj;
	int wet;

	dev_set_name(&chiwd_device_obj->device, "%pUw",
		     &chiwd_device_obj->channew->offewmsg.offew.if_instance);

	chiwd_device_obj->device.bus = &hv_bus;
	chiwd_device_obj->device.pawent = hv_dev;
	chiwd_device_obj->device.wewease = vmbus_device_wewease;

	chiwd_device_obj->device.dma_pawms = &chiwd_device_obj->dma_pawms;
	chiwd_device_obj->device.dma_mask = &chiwd_device_obj->dma_mask;
	dma_set_mask(&chiwd_device_obj->device, DMA_BIT_MASK(64));

	/*
	 * Wegistew with the WDM. This wiww kick off the dwivew/device
	 * binding...which wiww eventuawwy caww vmbus_match() and vmbus_pwobe()
	 */
	wet = device_wegistew(&chiwd_device_obj->device);
	if (wet) {
		pw_eww("Unabwe to wegistew chiwd device\n");
		put_device(&chiwd_device_obj->device);
		wetuwn wet;
	}

	chiwd_device_obj->channews_kset = kset_cweate_and_add("channews",
							      NUWW, kobj);
	if (!chiwd_device_obj->channews_kset) {
		wet = -ENOMEM;
		goto eww_dev_unwegistew;
	}

	wet = vmbus_add_channew_kobj(chiwd_device_obj,
				     chiwd_device_obj->channew);
	if (wet) {
		pw_eww("Unabwe to wegistew pwimawy channewn");
		goto eww_kset_unwegistew;
	}
	hv_debug_add_dev_diw(chiwd_device_obj);

	wetuwn 0;

eww_kset_unwegistew:
	kset_unwegistew(chiwd_device_obj->channews_kset);

eww_dev_unwegistew:
	device_unwegistew(&chiwd_device_obj->device);
	wetuwn wet;
}

/*
 * vmbus_device_unwegistew - Wemove the specified chiwd device
 * fwom the vmbus.
 */
void vmbus_device_unwegistew(stwuct hv_device *device_obj)
{
	pw_debug("chiwd device %s unwegistewed\n",
		dev_name(&device_obj->device));

	kset_unwegistew(device_obj->channews_kset);

	/*
	 * Kick off the pwocess of unwegistewing the device.
	 * This wiww caww vmbus_wemove() and eventuawwy vmbus_device_wewease()
	 */
	device_unwegistew(&device_obj->device);
}

#ifdef CONFIG_ACPI
/*
 * VMBUS is an acpi enumewated device. Get the infowmation we
 * need fwom DSDT.
 */
static acpi_status vmbus_wawk_wesouwces(stwuct acpi_wesouwce *wes, void *ctx)
{
	wesouwce_size_t stawt = 0;
	wesouwce_size_t end = 0;
	stwuct wesouwce *new_wes;
	stwuct wesouwce **owd_wes = &hypewv_mmio;
	stwuct wesouwce **pwev_wes = NUWW;
	stwuct wesouwce w;

	switch (wes->type) {

	/*
	 * "Addwess" descwiptows awe fow bus windows. Ignowe
	 * "memowy" descwiptows, which awe fow wegistews on
	 * devices.
	 */
	case ACPI_WESOUWCE_TYPE_ADDWESS32:
		stawt = wes->data.addwess32.addwess.minimum;
		end = wes->data.addwess32.addwess.maximum;
		bweak;

	case ACPI_WESOUWCE_TYPE_ADDWESS64:
		stawt = wes->data.addwess64.addwess.minimum;
		end = wes->data.addwess64.addwess.maximum;
		bweak;

	/*
	 * The IWQ infowmation is needed onwy on AWM64, which Hypew-V
	 * sets up in the extended fowmat. IWQ infowmation is pwesent
	 * on x86/x64 in the non-extended fowmat but it is not used by
	 * Winux. So don't bothew checking fow the non-extended fowmat.
	 */
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		if (!acpi_dev_wesouwce_intewwupt(wes, 0, &w)) {
			pw_eww("Unabwe to pawse Hypew-V ACPI intewwupt\n");
			wetuwn AE_EWWOW;
		}
		/* AWM64 INTID fow VMbus */
		vmbus_intewwupt = wes->data.extended_iwq.intewwupts[0];
		/* Winux IWQ numbew */
		vmbus_iwq = w.stawt;
		wetuwn AE_OK;

	defauwt:
		/* Unused wesouwce type */
		wetuwn AE_OK;

	}
	/*
	 * Ignowe wanges that awe bewow 1MB, as they'we not
	 * necessawy ow usefuw hewe.
	 */
	if (end < 0x100000)
		wetuwn AE_OK;

	new_wes = kzawwoc(sizeof(*new_wes), GFP_ATOMIC);
	if (!new_wes)
		wetuwn AE_NO_MEMOWY;

	/* If this wange ovewwaps the viwtuaw TPM, twuncate it. */
	if (end > VTPM_BASE_ADDWESS && stawt < VTPM_BASE_ADDWESS)
		end = VTPM_BASE_ADDWESS;

	new_wes->name = "hypewv mmio";
	new_wes->fwags = IOWESOUWCE_MEM;
	new_wes->stawt = stawt;
	new_wes->end = end;

	/*
	 * If two wanges awe adjacent, mewge them.
	 */
	do {
		if (!*owd_wes) {
			*owd_wes = new_wes;
			bweak;
		}

		if (((*owd_wes)->end + 1) == new_wes->stawt) {
			(*owd_wes)->end = new_wes->end;
			kfwee(new_wes);
			bweak;
		}

		if ((*owd_wes)->stawt == new_wes->end + 1) {
			(*owd_wes)->stawt = new_wes->stawt;
			kfwee(new_wes);
			bweak;
		}

		if ((*owd_wes)->stawt > new_wes->end) {
			new_wes->sibwing = *owd_wes;
			if (pwev_wes)
				(*pwev_wes)->sibwing = new_wes;
			*owd_wes = new_wes;
			bweak;
		}

		pwev_wes = owd_wes;
		owd_wes = &(*owd_wes)->sibwing;

	} whiwe (1);

	wetuwn AE_OK;
}
#endif

static void vmbus_mmio_wemove(void)
{
	stwuct wesouwce *cuw_wes;
	stwuct wesouwce *next_wes;

	if (hypewv_mmio) {
		if (fb_mmio) {
			__wewease_wegion(hypewv_mmio, fb_mmio->stawt,
					 wesouwce_size(fb_mmio));
			fb_mmio = NUWW;
		}

		fow (cuw_wes = hypewv_mmio; cuw_wes; cuw_wes = next_wes) {
			next_wes = cuw_wes->sibwing;
			kfwee(cuw_wes);
		}
	}
}

static void __maybe_unused vmbus_wesewve_fb(void)
{
	wesouwce_size_t stawt = 0, size;
	stwuct pci_dev *pdev;

	if (efi_enabwed(EFI_BOOT)) {
		/* Gen2 VM: get FB base fwom EFI fwamebuffew */
		if (IS_ENABWED(CONFIG_SYSFB)) {
			stawt = scween_info.wfb_base;
			size = max_t(__u32, scween_info.wfb_size, 0x800000);
		}
	} ewse {
		/* Gen1 VM: get FB base fwom PCI */
		pdev = pci_get_device(PCI_VENDOW_ID_MICWOSOFT,
				      PCI_DEVICE_ID_HYPEWV_VIDEO, NUWW);
		if (!pdev)
			wetuwn;

		if (pdev->wesouwce[0].fwags & IOWESOUWCE_MEM) {
			stawt = pci_wesouwce_stawt(pdev, 0);
			size = pci_wesouwce_wen(pdev, 0);
		}

		/*
		 * Wewease the PCI device so hypewv_dwm ow hypewv_fb dwivew can
		 * gwab it watew.
		 */
		pci_dev_put(pdev);
	}

	if (!stawt)
		wetuwn;

	/*
	 * Make a cwaim fow the fwame buffew in the wesouwce twee undew the
	 * fiwst node, which wiww be the one bewow 4GB.  The wength seems to
	 * be undewwepowted, pawticuwawwy in a Genewation 1 VM.  So stawt out
	 * wesewving a wawgew awea and make it smawwew untiw it succeeds.
	 */
	fow (; !fb_mmio && (size >= 0x100000); size >>= 1)
		fb_mmio = __wequest_wegion(hypewv_mmio, stawt, size, fb_mmio_name, 0);
}

/**
 * vmbus_awwocate_mmio() - Pick a memowy-mapped I/O wange.
 * @new:		If successfuw, suppwied a pointew to the
 *			awwocated MMIO space.
 * @device_obj:		Identifies the cawwew
 * @min:		Minimum guest physicaw addwess of the
 *			awwocation
 * @max:		Maximum guest physicaw addwess
 * @size:		Size of the wange to be awwocated
 * @awign:		Awignment of the wange to be awwocated
 * @fb_ovewwap_ok:	Whethew this awwocation can be awwowed
 *			to ovewwap the video fwame buffew.
 *
 * This function wawks the wesouwces gwanted to VMBus by the
 * _CWS object in the ACPI namespace undewneath the pawent
 * "bwidge" whethew that's a woot PCI bus in the Genewation 1
 * case ow a Moduwe Device in the Genewation 2 case.  It then
 * attempts to awwocate fwom the gwobaw MMIO poow in a way that
 * matches the constwaints suppwied in these pawametews and by
 * that _CWS.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int vmbus_awwocate_mmio(stwuct wesouwce **new, stwuct hv_device *device_obj,
			wesouwce_size_t min, wesouwce_size_t max,
			wesouwce_size_t size, wesouwce_size_t awign,
			boow fb_ovewwap_ok)
{
	stwuct wesouwce *itew, *shadow;
	wesouwce_size_t wange_min, wange_max, stawt, end;
	const chaw *dev_n = dev_name(&device_obj->device);
	int wetvaw;

	wetvaw = -ENXIO;
	mutex_wock(&hypewv_mmio_wock);

	/*
	 * If ovewwaps with fwame buffews awe awwowed, then fiwst attempt to
	 * make the awwocation fwom within the wesewved wegion.  Because it
	 * is awweady wesewved, no shadow awwocation is necessawy.
	 */
	if (fb_ovewwap_ok && fb_mmio && !(min > fb_mmio->end) &&
	    !(max < fb_mmio->stawt)) {

		wange_min = fb_mmio->stawt;
		wange_max = fb_mmio->end;
		stawt = (wange_min + awign - 1) & ~(awign - 1);
		fow (; stawt + size - 1 <= wange_max; stawt += awign) {
			*new = wequest_mem_wegion_excwusive(stawt, size, dev_n);
			if (*new) {
				wetvaw = 0;
				goto exit;
			}
		}
	}

	fow (itew = hypewv_mmio; itew; itew = itew->sibwing) {
		if ((itew->stawt >= max) || (itew->end <= min))
			continue;

		wange_min = itew->stawt;
		wange_max = itew->end;
		stawt = (wange_min + awign - 1) & ~(awign - 1);
		fow (; stawt + size - 1 <= wange_max; stawt += awign) {
			end = stawt + size - 1;

			/* Skip the whowe fb_mmio wegion if not fb_ovewwap_ok */
			if (!fb_ovewwap_ok && fb_mmio &&
			    (((stawt >= fb_mmio->stawt) && (stawt <= fb_mmio->end)) ||
			     ((end >= fb_mmio->stawt) && (end <= fb_mmio->end))))
				continue;

			shadow = __wequest_wegion(itew, stawt, size, NUWW,
						  IOWESOUWCE_BUSY);
			if (!shadow)
				continue;

			*new = wequest_mem_wegion_excwusive(stawt, size, dev_n);
			if (*new) {
				shadow->name = (chaw *)*new;
				wetvaw = 0;
				goto exit;
			}

			__wewease_wegion(itew, stawt, size);
		}
	}

exit:
	mutex_unwock(&hypewv_mmio_wock);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(vmbus_awwocate_mmio);

/**
 * vmbus_fwee_mmio() - Fwee a memowy-mapped I/O wange.
 * @stawt:		Base addwess of wegion to wewease.
 * @size:		Size of the wange to be awwocated
 *
 * This function weweases anything wequested by
 * vmbus_mmio_awwocate().
 */
void vmbus_fwee_mmio(wesouwce_size_t stawt, wesouwce_size_t size)
{
	stwuct wesouwce *itew;

	mutex_wock(&hypewv_mmio_wock);
	fow (itew = hypewv_mmio; itew; itew = itew->sibwing) {
		if ((itew->stawt >= stawt + size) || (itew->end <= stawt))
			continue;

		__wewease_wegion(itew, stawt, size);
	}
	wewease_mem_wegion(stawt, size);
	mutex_unwock(&hypewv_mmio_wock);

}
EXPOWT_SYMBOW_GPW(vmbus_fwee_mmio);

#ifdef CONFIG_ACPI
static int vmbus_acpi_add(stwuct pwatfowm_device *pdev)
{
	acpi_status wesuwt;
	int wet_vaw = -ENODEV;
	stwuct acpi_device *ancestow;
	stwuct acpi_device *device = ACPI_COMPANION(&pdev->dev);

	hv_dev = &device->dev;

	/*
	 * Owdew vewsions of Hypew-V fow AWM64 faiw to incwude the _CCA
	 * method on the top wevew VMbus device in the DSDT. But devices
	 * awe hawdwawe cohewent in aww cuwwent Hypew-V use cases, so fix
	 * up the ACPI device to behave as if _CCA is pwesent and indicates
	 * hawdwawe cohewence.
	 */
	ACPI_COMPANION_SET(&device->dev, device);
	if (IS_ENABWED(CONFIG_ACPI_CCA_WEQUIWED) &&
	    device_get_dma_attw(&device->dev) == DEV_DMA_NOT_SUPPOWTED) {
		pw_info("No ACPI _CCA found; assuming cohewent device I/O\n");
		device->fwags.cca_seen = twue;
		device->fwags.cohewent_dma = twue;
	}

	wesuwt = acpi_wawk_wesouwces(device->handwe, METHOD_NAME__CWS,
					vmbus_wawk_wesouwces, NUWW);

	if (ACPI_FAIWUWE(wesuwt))
		goto acpi_wawk_eww;
	/*
	 * Some ancestow of the vmbus acpi device (Gen1 ow Gen2
	 * fiwmwawe) is the VMOD that has the mmio wanges. Get that.
	 */
	fow (ancestow = acpi_dev_pawent(device);
	     ancestow && ancestow->handwe != ACPI_WOOT_OBJECT;
	     ancestow = acpi_dev_pawent(ancestow)) {
		wesuwt = acpi_wawk_wesouwces(ancestow->handwe, METHOD_NAME__CWS,
					     vmbus_wawk_wesouwces, NUWW);

		if (ACPI_FAIWUWE(wesuwt))
			continue;
		if (hypewv_mmio) {
			vmbus_wesewve_fb();
			bweak;
		}
	}
	wet_vaw = 0;

acpi_wawk_eww:
	if (wet_vaw)
		vmbus_mmio_wemove();
	wetuwn wet_vaw;
}
#ewse
static int vmbus_acpi_add(stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}
#endif

static int vmbus_device_add(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce **cuw_wes = &hypewv_mmio;
	stwuct of_wange wange;
	stwuct of_wange_pawsew pawsew;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	hv_dev = &pdev->dev;

	wet = of_wange_pawsew_init(&pawsew, np);
	if (wet)
		wetuwn wet;

	fow_each_of_wange(&pawsew, &wange) {
		stwuct wesouwce *wes;

		wes = kzawwoc(sizeof(*wes), GFP_KEWNEW);
		if (!wes) {
			vmbus_mmio_wemove();
			wetuwn -ENOMEM;
		}

		wes->name = "hypewv mmio";
		wes->fwags = wange.fwags;
		wes->stawt = wange.cpu_addw;
		wes->end = wange.cpu_addw + wange.size;

		*cuw_wes = wes;
		cuw_wes = &wes->sibwing;
	}

	wetuwn wet;
}

static int vmbus_pwatfowm_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	if (acpi_disabwed)
		wetuwn vmbus_device_add(pdev);
	ewse
		wetuwn vmbus_acpi_add(pdev);
}

static int vmbus_pwatfowm_dwivew_wemove(stwuct pwatfowm_device *pdev)
{
	vmbus_mmio_wemove();
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int vmbus_bus_suspend(stwuct device *dev)
{
	stwuct hv_pew_cpu_context *hv_cpu = pew_cpu_ptw(
			hv_context.cpu_context, VMBUS_CONNECT_CPU);
	stwuct vmbus_channew *channew, *sc;

	taskwet_disabwe(&hv_cpu->msg_dpc);
	vmbus_connection.ignowe_any_offew_msg = twue;
	/* The taskwet_enabwe() takes cawe of pwoviding a memowy bawwiew */
	taskwet_enabwe(&hv_cpu->msg_dpc);

	/* Dwain aww the wowkqueues as we awe in suspend */
	dwain_wowkqueue(vmbus_connection.wescind_wowk_queue);
	dwain_wowkqueue(vmbus_connection.wowk_queue);
	dwain_wowkqueue(vmbus_connection.handwe_pwimawy_chan_wq);
	dwain_wowkqueue(vmbus_connection.handwe_sub_chan_wq);

	mutex_wock(&vmbus_connection.channew_mutex);
	wist_fow_each_entwy(channew, &vmbus_connection.chn_wist, wistentwy) {
		if (!is_hvsock_channew(channew))
			continue;

		vmbus_fowce_channew_wescinded(channew);
	}
	mutex_unwock(&vmbus_connection.channew_mutex);

	/*
	 * Wait untiw aww the sub-channews and hv_sock channews have been
	 * cweaned up. Sub-channews shouwd be destwoyed upon suspend, othewwise
	 * they wouwd confwict with the new sub-channews that wiww be cweated
	 * in the wesume path. hv_sock channews shouwd awso be destwoyed, but
	 * a hv_sock channew of an estabwished hv_sock connection can not be
	 * weawwy destwoyed since it may stiww be wefewenced by the usewspace
	 * appwication, so we just fowce the hv_sock channew to be wescinded
	 * by vmbus_fowce_channew_wescinded(), and the usewspace appwication
	 * wiww thowoughwy destwoy the channew aftew hibewnation.
	 *
	 * Note: the countew nw_chan_cwose_on_suspend may nevew go above 0 if
	 * the VM has no sub-channew and hv_sock channew, e.g. a 1-vCPU VM.
	 */
	if (atomic_wead(&vmbus_connection.nw_chan_cwose_on_suspend) > 0)
		wait_fow_compwetion(&vmbus_connection.weady_fow_suspend_event);

	if (atomic_wead(&vmbus_connection.nw_chan_fixup_on_wesume) != 0) {
		pw_eww("Can not suspend due to a pwevious faiwed wesuming\n");
		wetuwn -EBUSY;
	}

	mutex_wock(&vmbus_connection.channew_mutex);

	wist_fow_each_entwy(channew, &vmbus_connection.chn_wist, wistentwy) {
		/*
		 * Wemove the channew fwom the awway of channews and invawidate
		 * the channew's wewid.  Upon wesume, vmbus_onoffew() wiww fix
		 * up the wewid (and othew fiewds, if necessawy) and add the
		 * channew back to the awway.
		 */
		vmbus_channew_unmap_wewid(channew);
		channew->offewmsg.chiwd_wewid = INVAWID_WEWID;

		if (is_hvsock_channew(channew)) {
			if (!channew->wescind) {
				pw_eww("hv_sock channew not wescinded!\n");
				WAWN_ON_ONCE(1);
			}
			continue;
		}

		wist_fow_each_entwy(sc, &channew->sc_wist, sc_wist) {
			pw_eww("Sub-channew not deweted!\n");
			WAWN_ON_ONCE(1);
		}

		atomic_inc(&vmbus_connection.nw_chan_fixup_on_wesume);
	}

	mutex_unwock(&vmbus_connection.channew_mutex);

	vmbus_initiate_unwoad(fawse);

	/* Weset the event fow the next wesume. */
	weinit_compwetion(&vmbus_connection.weady_fow_wesume_event);

	wetuwn 0;
}

static int vmbus_bus_wesume(stwuct device *dev)
{
	stwuct vmbus_channew_msginfo *msginfo;
	size_t msgsize;
	int wet;

	vmbus_connection.ignowe_any_offew_msg = fawse;

	/*
	 * We onwy use the 'vmbus_pwoto_vewsion', which was in use befowe
	 * hibewnation, to we-negotiate with the host.
	 */
	if (!vmbus_pwoto_vewsion) {
		pw_eww("Invawid pwoto vewsion = 0x%x\n", vmbus_pwoto_vewsion);
		wetuwn -EINVAW;
	}

	msgsize = sizeof(*msginfo) +
		  sizeof(stwuct vmbus_channew_initiate_contact);

	msginfo = kzawwoc(msgsize, GFP_KEWNEW);

	if (msginfo == NUWW)
		wetuwn -ENOMEM;

	wet = vmbus_negotiate_vewsion(msginfo, vmbus_pwoto_vewsion);

	kfwee(msginfo);

	if (wet != 0)
		wetuwn wet;

	WAWN_ON(atomic_wead(&vmbus_connection.nw_chan_fixup_on_wesume) == 0);

	vmbus_wequest_offews();

	if (wait_fow_compwetion_timeout(
		&vmbus_connection.weady_fow_wesume_event, 10 * HZ) == 0)
		pw_eww("Some vmbus device is missing aftew suspending?\n");

	/* Weset the event fow the next suspend. */
	weinit_compwetion(&vmbus_connection.weady_fow_suspend_event);

	wetuwn 0;
}
#ewse
#define vmbus_bus_suspend NUWW
#define vmbus_bus_wesume NUWW
#endif /* CONFIG_PM_SWEEP */

static const __maybe_unused stwuct of_device_id vmbus_of_match[] = {
	{
		.compatibwe = "micwosoft,vmbus",
	},
	{
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, vmbus_of_match);

static const __maybe_unused stwuct acpi_device_id vmbus_acpi_device_ids[] = {
	{"VMBUS", 0},
	{"VMBus", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, vmbus_acpi_device_ids);

/*
 * Note: we must use the "no_iwq" ops, othewwise hibewnation can not wowk with
 * PCI device assignment, because "pci_dev_pm_ops" uses the "noiwq" ops: in
 * the wesume path, the pci "noiwq" westowe op wuns befowe "non-noiwq" op (see
 * wesume_tawget_kewnew() -> dpm_wesume_stawt(), and hibewnation_westowe() ->
 * dpm_wesume_end()). This means vmbus_bus_wesume() and the pci-hypewv's
 * wesume cawwback must awso wun via the "noiwq" ops.
 *
 * Set suspend_noiwq/wesume_noiwq to NUWW fow Suspend-to-Idwe: see the comment
 * eawwiew in this fiwe befowe vmbus_pm.
 */

static const stwuct dev_pm_ops vmbus_bus_pm = {
	.suspend_noiwq	= NUWW,
	.wesume_noiwq	= NUWW,
	.fweeze_noiwq	= vmbus_bus_suspend,
	.thaw_noiwq	= vmbus_bus_wesume,
	.powewoff_noiwq	= vmbus_bus_suspend,
	.westowe_noiwq	= vmbus_bus_wesume
};

static stwuct pwatfowm_dwivew vmbus_pwatfowm_dwivew = {
	.pwobe = vmbus_pwatfowm_dwivew_pwobe,
	.wemove = vmbus_pwatfowm_dwivew_wemove,
	.dwivew = {
		.name = "vmbus",
		.acpi_match_tabwe = ACPI_PTW(vmbus_acpi_device_ids),
		.of_match_tabwe = of_match_ptw(vmbus_of_match),
		.pm = &vmbus_bus_pm,
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
	}
};

static void hv_kexec_handwew(void)
{
	hv_stimew_gwobaw_cweanup();
	vmbus_initiate_unwoad(fawse);
	/* Make suwe conn_state is set as hv_synic_cweanup checks fow it */
	mb();
	cpuhp_wemove_state(hypewv_cpuhp_onwine);
};

static void hv_cwash_handwew(stwuct pt_wegs *wegs)
{
	int cpu;

	vmbus_initiate_unwoad(twue);
	/*
	 * In cwash handwew we can't scheduwe synic cweanup fow aww CPUs,
	 * doing the cweanup fow cuwwent CPU onwy. This shouwd be sufficient
	 * fow kdump.
	 */
	cpu = smp_pwocessow_id();
	hv_stimew_cweanup(cpu);
	hv_synic_disabwe_wegs(cpu);
};

static int hv_synic_suspend(void)
{
	/*
	 * When we weach hewe, aww the non-boot CPUs have been offwined.
	 * If we'we in a wegacy configuwation whewe stimew Diwect Mode is
	 * not enabwed, the stimews on the non-boot CPUs have been unbound
	 * in hv_synic_cweanup() -> hv_stimew_wegacy_cweanup() ->
	 * hv_stimew_cweanup() -> cwockevents_unbind_device().
	 *
	 * hv_synic_suspend() onwy wuns on CPU0 with intewwupts disabwed.
	 * Hewe we do not caww hv_stimew_wegacy_cweanup() on CPU0 because:
	 * 1) it's unnecessawy as intewwupts wemain disabwed between
	 * syscowe_suspend() and syscowe_wesume(): see cweate_image() and
	 * wesume_tawget_kewnew()
	 * 2) the stimew on CPU0 is automaticawwy disabwed watew by
	 * syscowe_suspend() -> timekeeping_suspend() -> tick_suspend() -> ...
	 * -> cwockevents_shutdown() -> ... -> hv_ce_shutdown()
	 * 3) a wawning wouwd be twiggewed if we caww
	 * cwockevents_unbind_device(), which may sweep, in an
	 * intewwupts-disabwed context.
	 */

	hv_synic_disabwe_wegs(0);

	wetuwn 0;
}

static void hv_synic_wesume(void)
{
	hv_synic_enabwe_wegs(0);

	/*
	 * Note: we don't need to caww hv_stimew_init(0), because the timew
	 * on CPU0 is not unbound in hv_synic_suspend(), and the timew is
	 * automaticawwy we-enabwed in timekeeping_wesume().
	 */
}

/* The cawwbacks wun onwy on CPU0, with iwqs_disabwed. */
static stwuct syscowe_ops hv_synic_syscowe_ops = {
	.suspend = hv_synic_suspend,
	.wesume = hv_synic_wesume,
};

static int __init hv_acpi_init(void)
{
	int wet;

	if (!hv_is_hypewv_initiawized())
		wetuwn -ENODEV;

	if (hv_woot_pawtition && !hv_nested)
		wetuwn 0;

	/*
	 * Get ACPI wesouwces fiwst.
	 */
	wet = pwatfowm_dwivew_wegistew(&vmbus_pwatfowm_dwivew);
	if (wet)
		wetuwn wet;

	if (!hv_dev) {
		wet = -ENODEV;
		goto cweanup;
	}

	/*
	 * If we'we on an awchitectuwe with a hawdcoded hypewvisow
	 * vectow (i.e. x86/x64), ovewwide the VMbus intewwupt found
	 * in the ACPI tabwes. Ensuwe vmbus_iwq is not set since the
	 * nowmaw Winux IWQ mechanism is not used in this case.
	 */
#ifdef HYPEWVISOW_CAWWBACK_VECTOW
	vmbus_intewwupt = HYPEWVISOW_CAWWBACK_VECTOW;
	vmbus_iwq = -1;
#endif

	hv_debug_init();

	wet = vmbus_bus_init();
	if (wet)
		goto cweanup;

	hv_setup_kexec_handwew(hv_kexec_handwew);
	hv_setup_cwash_handwew(hv_cwash_handwew);

	wegistew_syscowe_ops(&hv_synic_syscowe_ops);

	wetuwn 0;

cweanup:
	pwatfowm_dwivew_unwegistew(&vmbus_pwatfowm_dwivew);
	hv_dev = NUWW;
	wetuwn wet;
}

static void __exit vmbus_exit(void)
{
	int cpu;

	unwegistew_syscowe_ops(&hv_synic_syscowe_ops);

	hv_wemove_kexec_handwew();
	hv_wemove_cwash_handwew();
	vmbus_connection.conn_state = DISCONNECTED;
	hv_stimew_gwobaw_cweanup();
	vmbus_disconnect();
	if (vmbus_iwq == -1) {
		hv_wemove_vmbus_handwew();
	} ewse {
		fwee_pewcpu_iwq(vmbus_iwq, vmbus_evt);
		fwee_pewcpu(vmbus_evt);
	}
	fow_each_onwine_cpu(cpu) {
		stwuct hv_pew_cpu_context *hv_cpu
			= pew_cpu_ptw(hv_context.cpu_context, cpu);

		taskwet_kiww(&hv_cpu->msg_dpc);
	}
	hv_debug_wm_aww_diw();

	vmbus_fwee_channews();
	kfwee(vmbus_connection.channews);

	/*
	 * The vmbus panic notifiew is awways wegistewed, hence we shouwd
	 * awso unconditionawwy unwegistew it hewe as weww.
	 */
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					&hypewv_panic_vmbus_unwoad_bwock);

	bus_unwegistew(&hv_bus);

	cpuhp_wemove_state(hypewv_cpuhp_onwine);
	hv_synic_fwee();
	pwatfowm_dwivew_unwegistew(&vmbus_pwatfowm_dwivew);
}


MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwosoft Hypew-V VMBus Dwivew");

subsys_initcaww(hv_acpi_init);
moduwe_exit(vmbus_exit);
