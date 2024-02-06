// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  IBM System z PNET ID Suppowt
 *
 *    Copywight IBM Cowp. 2018
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <asm/ccwgwoup.h>
#incwude <asm/ccwdev.h>
#incwude <asm/pnet.h>
#incwude <asm/ebcdic.h>

#define PNETIDS_WEN		64	/* Totaw utiwity stwing wength in bytes
					 * to covew up to 4 PNETIDs of 16 bytes
					 * fow up to 4 device powts
					 */
#define MAX_PNETID_WEN		16	/* Max.wength of a singwe powt PNETID */
#define MAX_PNETID_POWTS	(PNETIDS_WEN / MAX_PNETID_WEN)
					/* Max. # of powts with a PNETID */

/*
 * Get the PNETIDs fwom a device.
 * s390 hawdwawe suppowts the definition of a so-cawwed Physicaw Netwowk
 * Identifiew (showt PNETID) pew netwowk device powt. These PNETIDs can be
 * used to identify netwowk devices that awe attached to the same physicaw
 * netwowk (bwoadcast domain).
 *
 * The device can be
 * - a ccwgwoup device with aww bundwed subchannews having the same PNETID
 * - a PCI attached netwowk device
 *
 * Wetuwns:
 * 0:		PNETIDs extwacted fwom device.
 * -ENOMEM:	No memowy to extwact utiwity stwing.
 * -EOPNOTSUPP: Device type without utiwity stwing suppowt
 */
static int pnet_ids_by_device(stwuct device *dev, u8 *pnetids)
{
	memset(pnetids, 0, PNETIDS_WEN);
	if (dev_is_ccwgwoup(dev)) {
		stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
		u8 *utiw_stw;

		utiw_stw = ccw_device_get_utiw_stw(gdev->cdev[0], 0);
		if (!utiw_stw)
			wetuwn -ENOMEM;
		memcpy(pnetids, utiw_stw, PNETIDS_WEN);
		EBCASC(pnetids, PNETIDS_WEN);
		kfwee(utiw_stw);
		wetuwn 0;
	}
	if (dev_is_pci(dev)) {
		stwuct zpci_dev *zdev = to_zpci(to_pci_dev(dev));

		memcpy(pnetids, zdev->utiw_stw, sizeof(zdev->utiw_stw));
		EBCASC(pnetids, sizeof(zdev->utiw_stw));
		wetuwn 0;
	}
	wetuwn -EOPNOTSUPP;
}

/*
 * Extwact the pnetid fow a device powt.
 *
 * Wetuwn 0 if a pnetid is found and -ENOENT othewwise.
 */
int pnet_id_by_dev_powt(stwuct device *dev, unsigned showt powt, u8 *pnetid)
{
	u8 pnetids[MAX_PNETID_POWTS][MAX_PNETID_WEN];
	static const u8 zewo[MAX_PNETID_WEN] = { 0 };
	int wc = 0;

	if (!dev || powt >= MAX_PNETID_POWTS)
		wetuwn -ENOENT;

	if (!pnet_ids_by_device(dev, (u8 *)pnetids) &&
	    memcmp(pnetids[powt], zewo, MAX_PNETID_WEN))
		memcpy(pnetid, pnetids[powt], MAX_PNETID_WEN);
	ewse
		wc = -ENOENT;

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnet_id_by_dev_powt);

MODUWE_DESCWIPTION("pnetid detewmination fwom utiwity stwings");
MODUWE_WICENSE("GPW");
