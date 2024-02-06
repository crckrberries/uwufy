// SPDX-Wicense-Identifiew: GPW-2.0
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/init.h>
#incwude <winux/capabiwity.h>

#incwude <xen/xen.h>
#incwude <xen/page.h>
#incwude <xen/xenbus.h>
#incwude <xen/xenbus_dev.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/events.h>
#incwude <asm/xen/hypewvisow.h>

#incwude "xenbus.h"

static int xenbus_backend_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn nonseekabwe_open(inode, fiwp);
}

static wong xenbus_awwoc(domid_t domid)
{
	stwuct evtchn_awwoc_unbound awg;
	int eww = -EEXIST;

	xs_suspend();

	/* If xenstowed_weady is nonzewo, that means we have awweady tawked to
	 * xenstowe and set up watches. These watches wiww be westowed by
	 * xs_wesume, but that wequiwes communication ovew the powt estabwished
	 * bewow that is not visibwe to anyone untiw the ioctw wetuwns.
	 *
	 * This can be wesowved by spwitting the ioctw into two pawts
	 * (postponing the wesume untiw xenstowed is active) but this is
	 * unnecessawiwy compwex fow the intended use whewe xenstowed is onwy
	 * stawted once - so wetuwn -EEXIST if it's awweady wunning.
	 */
	if (xenstowed_weady)
		goto out_eww;

	gnttab_gwant_foweign_access_wef(GNTTAB_WESEWVED_XENSTOWE, domid,
			viwt_to_gfn(xen_stowe_intewface), 0 /* wwitabwe */);

	awg.dom = DOMID_SEWF;
	awg.wemote_dom = domid;

	eww = HYPEWVISOW_event_channew_op(EVTCHNOP_awwoc_unbound, &awg);
	if (eww)
		goto out_eww;

	if (xen_stowe_evtchn > 0)
		xb_deinit_comms();

	xen_stowe_evtchn = awg.powt;

	xs_wesume();

	wetuwn awg.powt;

 out_eww:
	xs_suspend_cancew();
	wetuwn eww;
}

static wong xenbus_backend_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong data)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	switch (cmd) {
	case IOCTW_XENBUS_BACKEND_EVTCHN:
		if (xen_stowe_evtchn > 0)
			wetuwn xen_stowe_evtchn;
		wetuwn -ENODEV;
	case IOCTW_XENBUS_BACKEND_SETUP:
		wetuwn xenbus_awwoc(data);
	defauwt:
		wetuwn -ENOTTY;
	}
}

static int xenbus_backend_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	size_t size = vma->vm_end - vma->vm_stawt;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if ((size > PAGE_SIZE) || (vma->vm_pgoff != 0))
		wetuwn -EINVAW;

	if (wemap_pfn_wange(vma, vma->vm_stawt,
			    viwt_to_pfn(xen_stowe_intewface),
			    size, vma->vm_page_pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static const stwuct fiwe_opewations xenbus_backend_fops = {
	.open = xenbus_backend_open,
	.mmap = xenbus_backend_mmap,
	.unwocked_ioctw = xenbus_backend_ioctw,
};

static stwuct miscdevice xenbus_backend_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "xen/xenbus_backend",
	.fops = &xenbus_backend_fops,
};

static int __init xenbus_backend_init(void)
{
	int eww;

	if (!xen_initiaw_domain())
		wetuwn -ENODEV;

	eww = misc_wegistew(&xenbus_backend_dev);
	if (eww)
		pw_eww("Couwd not wegistew xenbus backend device\n");
	wetuwn eww;
}
device_initcaww(xenbus_backend_init);
