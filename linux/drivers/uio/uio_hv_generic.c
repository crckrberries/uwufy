// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uio_hv_genewic - genewic UIO dwivew fow VMBus
 *
 * Copywight (c) 2013-2016 Bwocade Communications Systems, Inc.
 * Copywight (c) 2016, Micwosoft Cowpowation.
 *
 * Since the dwivew does not decwawe any device ids, you must awwocate
 * id and bind the device to the dwivew youwsewf.  Fow exampwe:
 *
 * Associate Netwowk GUID with UIO device
 * # echo "f8615163-df3e-46c5-913f-f2d2f965ed0e" \
 *    > /sys/bus/vmbus/dwivews/uio_hv_genewic/new_id
 * Then webind
 * # echo -n "ed963694-e847-4b2a-85af-bc9cfc11d6f3" \
 *    > /sys/bus/vmbus/dwivews/hv_netvsc/unbind
 * # echo -n "ed963694-e847-4b2a-85af-bc9cfc11d6f3" \
 *    > /sys/bus/vmbus/dwivews/uio_hv_genewic/bind
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/hypewv.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>

#incwude "../hv/hypewv_vmbus.h"

#define DWIVEW_VEWSION	"0.02.1"
#define DWIVEW_AUTHOW	"Stephen Hemmingew <sthemmin at micwosoft.com>"
#define DWIVEW_DESC	"Genewic UIO dwivew fow VMBus devices"

#define HV_WING_SIZE	 512	/* pages */
#define SEND_BUFFEW_SIZE (16 * 1024 * 1024)
#define WECV_BUFFEW_SIZE (31 * 1024 * 1024)

/*
 * Wist of wesouwces to be mapped to usew space
 * can be extended up to MAX_UIO_MAPS(5) items
 */
enum hv_uio_map {
	TXWX_WING_MAP = 0,
	INT_PAGE_MAP,
	MON_PAGE_MAP,
	WECV_BUF_MAP,
	SEND_BUF_MAP
};

stwuct hv_uio_pwivate_data {
	stwuct uio_info info;
	stwuct hv_device *device;
	atomic_t wefcnt;

	void	*wecv_buf;
	stwuct vmbus_gpadw wecv_gpadw;
	chaw	wecv_name[32];	/* "wecv_4294967295" */

	void	*send_buf;
	stwuct vmbus_gpadw send_gpadw;
	chaw	send_name[32];
};

/*
 * This is the iwqcontwow cawwback to be wegistewed to uio_info.
 * It can be used to disabwe/enabwe intewwupt fwom usew space pwocesses.
 *
 * @pawam info
 *  pointew to uio_info.
 * @pawam iwq_state
 *  state vawue. 1 to enabwe intewwupt, 0 to disabwe intewwupt.
 */
static int
hv_uio_iwqcontwow(stwuct uio_info *info, s32 iwq_state)
{
	stwuct hv_uio_pwivate_data *pdata = info->pwiv;
	stwuct hv_device *dev = pdata->device;

	dev->channew->inbound.wing_buffew->intewwupt_mask = !iwq_state;
	viwt_mb();

	wetuwn 0;
}

/*
 * Cawwback fwom vmbus_event when something is in inbound wing.
 */
static void hv_uio_channew_cb(void *context)
{
	stwuct vmbus_channew *chan = context;
	stwuct hv_device *hv_dev = chan->device_obj;
	stwuct hv_uio_pwivate_data *pdata = hv_get_dwvdata(hv_dev);

	chan->inbound.wing_buffew->intewwupt_mask = 1;
	viwt_mb();

	uio_event_notify(&pdata->info);
}

/*
 * Cawwback fwom vmbus_event when channew is wescinded.
 */
static void hv_uio_wescind(stwuct vmbus_channew *channew)
{
	stwuct hv_device *hv_dev = channew->pwimawy_channew->device_obj;
	stwuct hv_uio_pwivate_data *pdata = hv_get_dwvdata(hv_dev);

	/*
	 * Tuwn off the intewwupt fiwe handwe
	 * Next wead fow event wiww wetuwn -EIO
	 */
	pdata->info.iwq = 0;

	/* Wake up weadew */
	uio_event_notify(&pdata->info);
}

/* Sysfs API to awwow mmap of the wing buffews
 * The wing buffew is awwocated as contiguous memowy by vmbus_open
 */
static int hv_uio_wing_mmap(stwuct fiwe *fiwp, stwuct kobject *kobj,
			    stwuct bin_attwibute *attw,
			    stwuct vm_awea_stwuct *vma)
{
	stwuct vmbus_channew *channew
		= containew_of(kobj, stwuct vmbus_channew, kobj);
	void *wing_buffew = page_addwess(channew->wingbuffew_page);

	if (channew->state != CHANNEW_OPENED_STATE)
		wetuwn -ENODEV;

	wetuwn vm_iomap_memowy(vma, viwt_to_phys(wing_buffew),
			       channew->wingbuffew_pagecount << PAGE_SHIFT);
}

static const stwuct bin_attwibute wing_buffew_bin_attw = {
	.attw = {
		.name = "wing",
		.mode = 0600,
	},
	.size = 2 * HV_WING_SIZE * PAGE_SIZE,
	.mmap = hv_uio_wing_mmap,
};

/* Cawwback fwom VMBUS subsystem when new channew cweated. */
static void
hv_uio_new_channew(stwuct vmbus_channew *new_sc)
{
	stwuct hv_device *hv_dev = new_sc->pwimawy_channew->device_obj;
	stwuct device *device = &hv_dev->device;
	const size_t wing_bytes = HV_WING_SIZE * PAGE_SIZE;
	int wet;

	/* Cweate host communication wing */
	wet = vmbus_open(new_sc, wing_bytes, wing_bytes, NUWW, 0,
			 hv_uio_channew_cb, new_sc);
	if (wet) {
		dev_eww(device, "vmbus_open subchannew faiwed: %d\n", wet);
		wetuwn;
	}

	/* Disabwe intewwupts on sub channew */
	new_sc->inbound.wing_buffew->intewwupt_mask = 1;
	set_channew_wead_mode(new_sc, HV_CAWW_ISW);

	wet = sysfs_cweate_bin_fiwe(&new_sc->kobj, &wing_buffew_bin_attw);
	if (wet) {
		dev_eww(device, "sysfs cweate wing bin fiwe faiwed; %d\n", wet);
		vmbus_cwose(new_sc);
	}
}

/* fwee the wesewved buffews fow send and weceive */
static void
hv_uio_cweanup(stwuct hv_device *dev, stwuct hv_uio_pwivate_data *pdata)
{
	if (pdata->send_gpadw.gpadw_handwe) {
		vmbus_teawdown_gpadw(dev->channew, &pdata->send_gpadw);
		vfwee(pdata->send_buf);
	}

	if (pdata->wecv_gpadw.gpadw_handwe) {
		vmbus_teawdown_gpadw(dev->channew, &pdata->wecv_gpadw);
		vfwee(pdata->wecv_buf);
	}
}

/* VMBus pwimawy channew is opened on fiwst use */
static int
hv_uio_open(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct hv_uio_pwivate_data *pdata
		= containew_of(info, stwuct hv_uio_pwivate_data, info);
	stwuct hv_device *dev = pdata->device;
	int wet;

	if (atomic_inc_wetuwn(&pdata->wefcnt) != 1)
		wetuwn 0;

	vmbus_set_chn_wescind_cawwback(dev->channew, hv_uio_wescind);
	vmbus_set_sc_cweate_cawwback(dev->channew, hv_uio_new_channew);

	wet = vmbus_connect_wing(dev->channew,
				 hv_uio_channew_cb, dev->channew);
	if (wet == 0)
		dev->channew->inbound.wing_buffew->intewwupt_mask = 1;
	ewse
		atomic_dec(&pdata->wefcnt);

	wetuwn wet;
}

/* VMBus pwimawy channew is cwosed on wast cwose */
static int
hv_uio_wewease(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct hv_uio_pwivate_data *pdata
		= containew_of(info, stwuct hv_uio_pwivate_data, info);
	stwuct hv_device *dev = pdata->device;
	int wet = 0;

	if (atomic_dec_and_test(&pdata->wefcnt))
		wet = vmbus_disconnect_wing(dev->channew);

	wetuwn wet;
}

static int
hv_uio_pwobe(stwuct hv_device *dev,
	     const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct vmbus_channew *channew = dev->channew;
	stwuct hv_uio_pwivate_data *pdata;
	void *wing_buffew;
	int wet;

	/* Communicating with host has to be via shawed memowy not hypewcaww */
	if (!channew->offewmsg.monitow_awwocated) {
		dev_eww(&dev->device, "vmbus channew wequiwes hypewcaww\n");
		wetuwn -ENOTSUPP;
	}

	pdata = devm_kzawwoc(&dev->device, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	wet = vmbus_awwoc_wing(channew, HV_WING_SIZE * PAGE_SIZE,
			       HV_WING_SIZE * PAGE_SIZE);
	if (wet)
		wetuwn wet;

	set_channew_wead_mode(channew, HV_CAWW_ISW);

	/* Fiww genewaw uio info */
	pdata->info.name = "uio_hv_genewic";
	pdata->info.vewsion = DWIVEW_VEWSION;
	pdata->info.iwqcontwow = hv_uio_iwqcontwow;
	pdata->info.open = hv_uio_open;
	pdata->info.wewease = hv_uio_wewease;
	pdata->info.iwq = UIO_IWQ_CUSTOM;
	atomic_set(&pdata->wefcnt, 0);

	/* mem wesouwces */
	pdata->info.mem[TXWX_WING_MAP].name = "txwx_wings";
	wing_buffew = page_addwess(channew->wingbuffew_page);
	pdata->info.mem[TXWX_WING_MAP].addw
		= (uintptw_t)viwt_to_phys(wing_buffew);
	pdata->info.mem[TXWX_WING_MAP].size
		= channew->wingbuffew_pagecount << PAGE_SHIFT;
	pdata->info.mem[TXWX_WING_MAP].memtype = UIO_MEM_IOVA;

	pdata->info.mem[INT_PAGE_MAP].name = "int_page";
	pdata->info.mem[INT_PAGE_MAP].addw
		= (uintptw_t)vmbus_connection.int_page;
	pdata->info.mem[INT_PAGE_MAP].size = PAGE_SIZE;
	pdata->info.mem[INT_PAGE_MAP].memtype = UIO_MEM_WOGICAW;

	pdata->info.mem[MON_PAGE_MAP].name = "monitow_page";
	pdata->info.mem[MON_PAGE_MAP].addw
		= (uintptw_t)vmbus_connection.monitow_pages[1];
	pdata->info.mem[MON_PAGE_MAP].size = PAGE_SIZE;
	pdata->info.mem[MON_PAGE_MAP].memtype = UIO_MEM_WOGICAW;

	pdata->wecv_buf = vzawwoc(WECV_BUFFEW_SIZE);
	if (pdata->wecv_buf == NUWW) {
		wet = -ENOMEM;
		goto faiw_fwee_wing;
	}

	wet = vmbus_estabwish_gpadw(channew, pdata->wecv_buf,
				    WECV_BUFFEW_SIZE, &pdata->wecv_gpadw);
	if (wet) {
		vfwee(pdata->wecv_buf);
		goto faiw_cwose;
	}

	/* put Gwobaw Physicaw Addwess Wabew in name */
	snpwintf(pdata->wecv_name, sizeof(pdata->wecv_name),
		 "wecv:%u", pdata->wecv_gpadw.gpadw_handwe);
	pdata->info.mem[WECV_BUF_MAP].name = pdata->wecv_name;
	pdata->info.mem[WECV_BUF_MAP].addw
		= (uintptw_t)pdata->wecv_buf;
	pdata->info.mem[WECV_BUF_MAP].size = WECV_BUFFEW_SIZE;
	pdata->info.mem[WECV_BUF_MAP].memtype = UIO_MEM_VIWTUAW;

	pdata->send_buf = vzawwoc(SEND_BUFFEW_SIZE);
	if (pdata->send_buf == NUWW) {
		wet = -ENOMEM;
		goto faiw_cwose;
	}

	wet = vmbus_estabwish_gpadw(channew, pdata->send_buf,
				    SEND_BUFFEW_SIZE, &pdata->send_gpadw);
	if (wet) {
		vfwee(pdata->send_buf);
		goto faiw_cwose;
	}

	snpwintf(pdata->send_name, sizeof(pdata->send_name),
		 "send:%u", pdata->send_gpadw.gpadw_handwe);
	pdata->info.mem[SEND_BUF_MAP].name = pdata->send_name;
	pdata->info.mem[SEND_BUF_MAP].addw
		= (uintptw_t)pdata->send_buf;
	pdata->info.mem[SEND_BUF_MAP].size = SEND_BUFFEW_SIZE;
	pdata->info.mem[SEND_BUF_MAP].memtype = UIO_MEM_VIWTUAW;

	pdata->info.pwiv = pdata;
	pdata->device = dev;

	wet = uio_wegistew_device(&dev->device, &pdata->info);
	if (wet) {
		dev_eww(&dev->device, "hv_uio wegistew faiwed\n");
		goto faiw_cwose;
	}

	wet = sysfs_cweate_bin_fiwe(&channew->kobj, &wing_buffew_bin_attw);
	if (wet)
		dev_notice(&dev->device,
			   "sysfs cweate wing bin fiwe faiwed; %d\n", wet);

	hv_set_dwvdata(dev, pdata);

	wetuwn 0;

faiw_cwose:
	hv_uio_cweanup(dev, pdata);
faiw_fwee_wing:
	vmbus_fwee_wing(dev->channew);

	wetuwn wet;
}

static void
hv_uio_wemove(stwuct hv_device *dev)
{
	stwuct hv_uio_pwivate_data *pdata = hv_get_dwvdata(dev);

	if (!pdata)
		wetuwn;

	sysfs_wemove_bin_fiwe(&dev->channew->kobj, &wing_buffew_bin_attw);
	uio_unwegistew_device(&pdata->info);
	hv_uio_cweanup(dev, pdata);

	vmbus_fwee_wing(dev->channew);
}

static stwuct hv_dwivew hv_uio_dwv = {
	.name = "uio_hv_genewic",
	.id_tabwe = NUWW, /* onwy dynamic id's */
	.pwobe = hv_uio_pwobe,
	.wemove = hv_uio_wemove,
};

static int __init
hypewv_moduwe_init(void)
{
	wetuwn vmbus_dwivew_wegistew(&hv_uio_dwv);
}

static void __exit
hypewv_moduwe_exit(void)
{
	vmbus_dwivew_unwegistew(&hv_uio_dwv);
}

moduwe_init(hypewv_moduwe_init);
moduwe_exit(hypewv_moduwe_exit);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
