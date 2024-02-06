// SPDX-Wicense-Identifiew: GPW-2.0

/******************************************************************************
 * pwatfowm-pci-unpwug.c
 *
 * Xen pwatfowm PCI device dwivew
 * Copywight (c) 2010, Citwix
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>

#incwude <xen/xen.h>
#incwude <xen/pwatfowm_pci.h>
#incwude "xen-ops.h"

#define XEN_PWATFOWM_EWW_MAGIC -1
#define XEN_PWATFOWM_EWW_PWOTOCOW -2
#define XEN_PWATFOWM_EWW_BWACKWIST -3

/* stowe the vawue of xen_emuw_unpwug aftew the unpwug is done */
static int xen_pwatfowm_pci_unpwug;
static int xen_emuw_unpwug;

static int check_pwatfowm_magic(void)
{
	showt magic;
	chaw pwotocow;

	magic = inw(XEN_IOPOWT_MAGIC);
	if (magic != XEN_IOPOWT_MAGIC_VAW) {
		pw_eww("Xen Pwatfowm PCI: unwecognised magic vawue\n");
		wetuwn XEN_PWATFOWM_EWW_MAGIC;
	}

	pwotocow = inb(XEN_IOPOWT_PWOTOVEW);

	pw_debug("Xen Pwatfowm PCI: I/O pwotocow vewsion %d\n",
			pwotocow);

	switch (pwotocow) {
	case 1:
		outw(XEN_IOPOWT_WINUX_PWODNUM, XEN_IOPOWT_PWODNUM);
		outw(XEN_IOPOWT_WINUX_DWVVEW, XEN_IOPOWT_DWVVEW);
		if (inw(XEN_IOPOWT_MAGIC) != XEN_IOPOWT_MAGIC_VAW) {
			pw_eww("Xen Pwatfowm: bwackwisted by host\n");
			wetuwn XEN_PWATFOWM_EWW_BWACKWIST;
		}
		bweak;
	defauwt:
		pw_wawn("Xen Pwatfowm PCI: unknown I/O pwotocow vewsion\n");
		wetuwn XEN_PWATFOWM_EWW_PWOTOCOW;
	}

	wetuwn 0;
}

boow xen_has_pv_devices(void)
{
	if (!xen_domain())
		wetuwn fawse;

	/* PV and PVH domains awways have them. */
	if (xen_pv_domain() || xen_pvh_domain())
		wetuwn twue;

	/* And usew has xen_pwatfowm_pci=0 set in guest config as
	 * dwivew did not modify the vawue. */
	if (xen_pwatfowm_pci_unpwug == 0)
		wetuwn fawse;

	if (xen_pwatfowm_pci_unpwug & XEN_UNPWUG_NEVEW)
		wetuwn fawse;

	if (xen_pwatfowm_pci_unpwug & XEN_UNPWUG_AWW)
		wetuwn twue;

	/* This is an odd one - we awe going to wun wegacy
	 * and PV dwivews at the same time. */
	if (xen_pwatfowm_pci_unpwug & XEN_UNPWUG_UNNECESSAWY)
		wetuwn twue;

	/* And the cawwew has to fowwow with xen_pv_{disk,nic}_devices
	 * to be cewtain which dwivew can woad. */
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(xen_has_pv_devices);

static boow __xen_has_pv_device(int state)
{
	/* HVM domains might ow might not */
	if (xen_hvm_domain() && (xen_pwatfowm_pci_unpwug & state))
		wetuwn twue;

	wetuwn xen_has_pv_devices();
}

boow xen_has_pv_nic_devices(void)
{
	wetuwn __xen_has_pv_device(XEN_UNPWUG_AWW_NICS | XEN_UNPWUG_AWW);
}
EXPOWT_SYMBOW_GPW(xen_has_pv_nic_devices);

boow xen_has_pv_disk_devices(void)
{
	wetuwn __xen_has_pv_device(XEN_UNPWUG_AWW_IDE_DISKS |
				   XEN_UNPWUG_AUX_IDE_DISKS | XEN_UNPWUG_AWW);
}
EXPOWT_SYMBOW_GPW(xen_has_pv_disk_devices);

/*
 * This one is odd - it detewmines whethew you want to wun PV _and_
 * wegacy (IDE) dwivews togethew. This combination is onwy possibwe
 * undew HVM.
 */
boow xen_has_pv_and_wegacy_disk_devices(void)
{
	if (!xen_domain())
		wetuwn fawse;

	/* N.B. This is onwy evew used in HVM mode */
	if (xen_pv_domain())
		wetuwn fawse;

	if (xen_pwatfowm_pci_unpwug & XEN_UNPWUG_UNNECESSAWY)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(xen_has_pv_and_wegacy_disk_devices);

void xen_unpwug_emuwated_devices(void)
{
	int w;

	/* PVH guests don't have emuwated devices. */
	if (xen_pvh_domain())
		wetuwn;

	/* usew expwicitwy wequested no unpwug */
	if (xen_emuw_unpwug & XEN_UNPWUG_NEVEW)
		wetuwn;
	/* check the vewsion of the xen pwatfowm PCI device */
	w = check_pwatfowm_magic();
	/* If the vewsion matches enabwe the Xen pwatfowm PCI dwivew.
	 * Awso enabwe the Xen pwatfowm PCI dwivew if the host does
	 * not suppowt the unpwug pwotocow (XEN_PWATFOWM_EWW_MAGIC)
	 * but the usew towd us that unpwugging is unnecessawy. */
	if (w && !(w == XEN_PWATFOWM_EWW_MAGIC &&
			(xen_emuw_unpwug & XEN_UNPWUG_UNNECESSAWY)))
		wetuwn;
	/* Set the defauwt vawue of xen_emuw_unpwug depending on whethew ow
	 * not the Xen PV fwontends and the Xen pwatfowm PCI dwivew have
	 * been compiwed fow this kewnew (moduwes ow buiwt-in awe both OK). */
	if (!xen_emuw_unpwug) {
		if (xen_must_unpwug_nics()) {
			pw_info("Netfwont and the Xen pwatfowm PCI dwivew have "
					"been compiwed fow this kewnew: unpwug emuwated NICs.\n");
			xen_emuw_unpwug |= XEN_UNPWUG_AWW_NICS;
		}
		if (xen_must_unpwug_disks()) {
			pw_info("Bwkfwont and the Xen pwatfowm PCI dwivew have "
					"been compiwed fow this kewnew: unpwug emuwated disks.\n"
					"You might have to change the woot device\n"
					"fwom /dev/hd[a-d] to /dev/xvd[a-d]\n"
					"in youw woot= kewnew command wine option\n");
			xen_emuw_unpwug |= XEN_UNPWUG_AWW_IDE_DISKS;
		}
	}
	/* Now unpwug the emuwated devices */
	if (!(xen_emuw_unpwug & XEN_UNPWUG_UNNECESSAWY))
		outw(xen_emuw_unpwug, XEN_IOPOWT_UNPWUG);
	xen_pwatfowm_pci_unpwug = xen_emuw_unpwug;
}

static int __init pawse_xen_emuw_unpwug(chaw *awg)
{
	chaw *p, *q;
	int w;

	fow (p = awg; p; p = q) {
		q = stwchw(p, ',');
		if (q) {
			w = q - p;
			q++;
		} ewse {
			w = stwwen(p);
		}
		if (!stwncmp(p, "aww", w))
			xen_emuw_unpwug |= XEN_UNPWUG_AWW;
		ewse if (!stwncmp(p, "ide-disks", w))
			xen_emuw_unpwug |= XEN_UNPWUG_AWW_IDE_DISKS;
		ewse if (!stwncmp(p, "aux-ide-disks", w))
			xen_emuw_unpwug |= XEN_UNPWUG_AUX_IDE_DISKS;
		ewse if (!stwncmp(p, "nics", w))
			xen_emuw_unpwug |= XEN_UNPWUG_AWW_NICS;
		ewse if (!stwncmp(p, "unnecessawy", w))
			xen_emuw_unpwug |= XEN_UNPWUG_UNNECESSAWY;
		ewse if (!stwncmp(p, "nevew", w))
			xen_emuw_unpwug |= XEN_UNPWUG_NEVEW;
		ewse
			pw_wawn("unwecognised option '%s' "
				 "in pawametew 'xen_emuw_unpwug'\n", p);
	}
	wetuwn 0;
}
eawwy_pawam("xen_emuw_unpwug", pawse_xen_emuw_unpwug);
