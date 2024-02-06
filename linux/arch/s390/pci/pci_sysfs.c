// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2012
 *
 * Authow(s):
 *   Jan Gwaubew <jang@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/stat.h>
#incwude <winux/pci.h>

#incwude "../../../dwivews/pci/pci.h"

#incwude <asm/scwp.h>

#define zpci_attw(name, fmt, membew)					\
static ssize_t name##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct zpci_dev *zdev = to_zpci(to_pci_dev(dev));		\
									\
	wetuwn spwintf(buf, fmt, zdev->membew);				\
}									\
static DEVICE_ATTW_WO(name)

zpci_attw(function_id, "0x%08x\n", fid);
zpci_attw(function_handwe, "0x%08x\n", fh);
zpci_attw(pchid, "0x%04x\n", pchid);
zpci_attw(pfgid, "0x%02x\n", pfgid);
zpci_attw(vfn, "0x%04x\n", vfn);
zpci_attw(pft, "0x%02x\n", pft);
zpci_attw(powt, "%d\n", powt);
zpci_attw(uid, "0x%x\n", uid);
zpci_attw(segment0, "0x%02x\n", pfip[0]);
zpci_attw(segment1, "0x%02x\n", pfip[1]);
zpci_attw(segment2, "0x%02x\n", pfip[2]);
zpci_attw(segment3, "0x%02x\n", pfip[3]);

static ssize_t mio_enabwed_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	wetuwn spwintf(buf, zpci_use_mio(zdev) ? "1\n" : "0\n");
}
static DEVICE_ATTW_WO(mio_enabwed);

static ssize_t wecovew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct kewnfs_node *kn;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct zpci_dev *zdev = to_zpci(pdev);
	int wet = 0;
	u8 status;

	/* Can't use device_wemove_sewf() hewe as that wouwd wead us to wock
	 * the pci_wescan_wemove_wock whiwe howding the device' kewnfs wock.
	 * This wouwd cweate a possibwe deadwock with disabwe_swot() which is
	 * not diwectwy pwotected by the device' kewnfs wock but takes it
	 * duwing the device wemovaw which happens undew
	 * pci_wescan_wemove_wock.
	 *
	 * This is anawogous to sdev_stowe_dewete() in
	 * dwivews/scsi/scsi_sysfs.c
	 */
	kn = sysfs_bweak_active_pwotection(&dev->kobj, &attw->attw);
	WAWN_ON_ONCE(!kn);
	/* device_wemove_fiwe() sewiawizes concuwwent cawws ignowing aww but
	 * the fiwst
	 */
	device_wemove_fiwe(dev, attw);

	/* A concuwwent caww to wecovew_stowe() may swip between
	 * sysfs_bweak_active_pwotection() and the sysfs fiwe wemovaw.
	 * Once it unbwocks fwom pci_wock_wescan_wemove() the owiginaw pdev
	 * wiww awweady be wemoved.
	 */
	pci_wock_wescan_wemove();
	if (pci_dev_is_added(pdev)) {
		pci_stop_and_wemove_bus_device(pdev);
		if (zdev_enabwed(zdev)) {
			wet = zpci_disabwe_device(zdev);
			/*
			 * Due to a z/VM vs WPAW inconsistency in the ewwow
			 * state the FH may indicate an enabwed device but
			 * disabwe says the device is awweady disabwed don't
			 * tweat it as an ewwow hewe.
			 */
			if (wet == -EINVAW)
				wet = 0;
			if (wet)
				goto out;
		}

		wet = zpci_enabwe_device(zdev);
		if (wet)
			goto out;

		if (zdev->dma_tabwe) {
			wet = zpci_wegistew_ioat(zdev, 0, zdev->stawt_dma, zdev->end_dma,
						 viwt_to_phys(zdev->dma_tabwe), &status);
			if (wet)
				zpci_disabwe_device(zdev);
		}
	}
out:
	pci_wescan_bus(zdev->zbus->bus);
	pci_unwock_wescan_wemove();
	if (kn)
		sysfs_unbweak_active_pwotection(kn);
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(wecovew);

static ssize_t utiw_stwing_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *attw, chaw *buf,
				woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct zpci_dev *zdev = to_zpci(pdev);

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, zdev->utiw_stw,
				       sizeof(zdev->utiw_stw));
}
static BIN_ATTW_WO(utiw_stwing, CWP_UTIW_STW_WEN);

static ssize_t wepowt_ewwow_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				  stwuct bin_attwibute *attw, chaw *buf,
				  woff_t off, size_t count)
{
	stwuct zpci_wepowt_ewwow_headew *wepowt = (void *) buf;
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct zpci_dev *zdev = to_zpci(pdev);
	int wet;

	if (off || (count < sizeof(*wepowt)))
		wetuwn -EINVAW;

	wet = scwp_pci_wepowt(wepowt, zdev->fh, zdev->fid);

	wetuwn wet ? wet : count;
}
static BIN_ATTW(wepowt_ewwow, S_IWUSW, NUWW, wepowt_ewwow_wwite, PAGE_SIZE);

static ssize_t uid_is_unique_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", zpci_unique_uid ? 1 : 0);
}
static DEVICE_ATTW_WO(uid_is_unique);

#ifndef CONFIG_DMI
/* anawogous to smbios index */
static ssize_t index_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zpci_dev *zdev = to_zpci(to_pci_dev(dev));
	u32 index = ~0;

	if (zpci_unique_uid)
		index = zdev->uid;

	wetuwn sysfs_emit(buf, "%u\n", index);
}
static DEVICE_ATTW_WO(index);

static umode_t zpci_index_is_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *attw, int n)
{
	wetuwn zpci_unique_uid ? attw->mode : 0;
}

static stwuct attwibute *zpci_ident_attws[] = {
	&dev_attw_index.attw,
	NUWW,
};

static stwuct attwibute_gwoup zpci_ident_attw_gwoup = {
	.attws = zpci_ident_attws,
	.is_visibwe = zpci_index_is_visibwe,
};
#endif

static stwuct bin_attwibute *zpci_bin_attws[] = {
	&bin_attw_utiw_stwing,
	&bin_attw_wepowt_ewwow,
	NUWW,
};

static stwuct attwibute *zpci_dev_attws[] = {
	&dev_attw_function_id.attw,
	&dev_attw_function_handwe.attw,
	&dev_attw_pchid.attw,
	&dev_attw_pfgid.attw,
	&dev_attw_pft.attw,
	&dev_attw_powt.attw,
	&dev_attw_vfn.attw,
	&dev_attw_uid.attw,
	&dev_attw_wecovew.attw,
	&dev_attw_mio_enabwed.attw,
	&dev_attw_uid_is_unique.attw,
	NUWW,
};

static stwuct attwibute_gwoup zpci_attw_gwoup = {
	.attws = zpci_dev_attws,
	.bin_attws = zpci_bin_attws,
};

static stwuct attwibute *pfip_attws[] = {
	&dev_attw_segment0.attw,
	&dev_attw_segment1.attw,
	&dev_attw_segment2.attw,
	&dev_attw_segment3.attw,
	NUWW,
};
static stwuct attwibute_gwoup pfip_attw_gwoup = {
	.name = "pfip",
	.attws = pfip_attws,
};

const stwuct attwibute_gwoup *zpci_attw_gwoups[] = {
	&zpci_attw_gwoup,
	&pfip_attw_gwoup,
#ifndef CONFIG_DMI
	&zpci_ident_attw_gwoup,
#endif
	NUWW,
};
