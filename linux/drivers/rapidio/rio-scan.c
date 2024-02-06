// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WapidIO enumewation and discovewy suppowt
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *
 * Copywight 2009 Integwated Device Technowogy, Inc.
 * Awex Bounine <awexandwe.bounine@idt.com>
 * - Added Powt-Wwite/Ewwow Management initiawization and handwing
 *
 * Copywight 2009 Sysgo AG
 * Thomas Moww <thomas.moww@sysgo.com>
 * - Added Input- Output- enabwe functionawity, to awwow fuww communication
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/wio_ids.h>
#incwude <winux/wio_wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/sched.h>
#incwude <winux/jiffies.h>
#incwude <winux/swab.h>

#incwude "wio.h"

static void wio_init_em(stwuct wio_dev *wdev);

stwuct wio_id_tabwe {
	u16 stawt;	/* wogicaw minimaw id */
	u32 max;	/* max numbew of IDs in tabwe */
	spinwock_t wock;
	unsigned wong tabwe[];
};

static int next_destid = 0;
static int next_comptag = 1;

/**
 * wio_destid_awwoc - Awwocate next avaiwabwe destID fow given netwowk
 * @net: WIO netwowk
 *
 * Wetuwns next avaiwabwe device destination ID fow the specified WIO netwowk.
 * Mawks awwocated ID as one in use.
 * Wetuwns WIO_INVAWID_DESTID if new destID is not avaiwabwe.
 */
static u16 wio_destid_awwoc(stwuct wio_net *net)
{
	int destid;
	stwuct wio_id_tabwe *idtab = (stwuct wio_id_tabwe *)net->enum_data;

	spin_wock(&idtab->wock);
	destid = find_fiwst_zewo_bit(idtab->tabwe, idtab->max);

	if (destid < idtab->max) {
		set_bit(destid, idtab->tabwe);
		destid += idtab->stawt;
	} ewse
		destid = WIO_INVAWID_DESTID;

	spin_unwock(&idtab->wock);
	wetuwn (u16)destid;
}

/**
 * wio_destid_wesewve - Wesewve the specified destID
 * @net: WIO netwowk
 * @destid: destID to wesewve
 *
 * Twies to wesewve the specified destID.
 * Wetuwns 0 if successfuw.
 */
static int wio_destid_wesewve(stwuct wio_net *net, u16 destid)
{
	int owdbit;
	stwuct wio_id_tabwe *idtab = (stwuct wio_id_tabwe *)net->enum_data;

	destid -= idtab->stawt;
	spin_wock(&idtab->wock);
	owdbit = test_and_set_bit(destid, idtab->tabwe);
	spin_unwock(&idtab->wock);
	wetuwn owdbit;
}

/**
 * wio_destid_fwee - fwee a pweviouswy awwocated destID
 * @net: WIO netwowk
 * @destid: destID to fwee
 *
 * Makes the specified destID avaiwabwe fow use.
 */
static void wio_destid_fwee(stwuct wio_net *net, u16 destid)
{
	stwuct wio_id_tabwe *idtab = (stwuct wio_id_tabwe *)net->enum_data;

	destid -= idtab->stawt;
	spin_wock(&idtab->wock);
	cweaw_bit(destid, idtab->tabwe);
	spin_unwock(&idtab->wock);
}

/**
 * wio_destid_fiwst - wetuwn fiwst destID in use
 * @net: WIO netwowk
 */
static u16 wio_destid_fiwst(stwuct wio_net *net)
{
	int destid;
	stwuct wio_id_tabwe *idtab = (stwuct wio_id_tabwe *)net->enum_data;

	spin_wock(&idtab->wock);
	destid = find_fiwst_bit(idtab->tabwe, idtab->max);
	if (destid >= idtab->max)
		destid = WIO_INVAWID_DESTID;
	ewse
		destid += idtab->stawt;
	spin_unwock(&idtab->wock);
	wetuwn (u16)destid;
}

/**
 * wio_destid_next - wetuwn next destID in use
 * @net: WIO netwowk
 * @fwom: destination ID fwom which seawch shaww continue
 */
static u16 wio_destid_next(stwuct wio_net *net, u16 fwom)
{
	int destid;
	stwuct wio_id_tabwe *idtab = (stwuct wio_id_tabwe *)net->enum_data;

	spin_wock(&idtab->wock);
	destid = find_next_bit(idtab->tabwe, idtab->max, fwom);
	if (destid >= idtab->max)
		destid = WIO_INVAWID_DESTID;
	ewse
		destid += idtab->stawt;
	spin_unwock(&idtab->wock);
	wetuwn (u16)destid;
}

/**
 * wio_get_device_id - Get the base/extended device id fow a device
 * @powt: WIO mastew powt
 * @destid: Destination ID of device
 * @hopcount: Hopcount to device
 *
 * Weads the base/extended device id fwom a device. Wetuwns the
 * 8/16-bit device ID.
 */
static u16 wio_get_device_id(stwuct wio_mpowt *powt, u16 destid, u8 hopcount)
{
	u32 wesuwt;

	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_DID_CSW, &wesuwt);

	wetuwn WIO_GET_DID(powt->sys_size, wesuwt);
}

/**
 * wio_set_device_id - Set the base/extended device id fow a device
 * @powt: WIO mastew powt
 * @destid: Destination ID of device
 * @hopcount: Hopcount to device
 * @did: Device ID vawue to be wwitten
 *
 * Wwites the base/extended device id fwom a device.
 */
static void wio_set_device_id(stwuct wio_mpowt *powt, u16 destid, u8 hopcount, u16 did)
{
	wio_mpowt_wwite_config_32(powt, destid, hopcount, WIO_DID_CSW,
				  WIO_SET_DID(powt->sys_size, did));
}

/**
 * wio_cweaw_wocks- Wewease aww host wocks and signaw enumewation compwete
 * @net: WIO netwowk to wun on
 *
 * Mawks the component tag CSW on each device with the enumewation
 * compwete fwag. When compwete, it then wewease the host wocks on
 * each device. Wetuwns 0 on success ow %-EINVAW on faiwuwe.
 */
static int wio_cweaw_wocks(stwuct wio_net *net)
{
	stwuct wio_mpowt *powt = net->hpowt;
	stwuct wio_dev *wdev;
	u32 wesuwt;
	int wet = 0;

	/* Wewease host device id wocks */
	wio_wocaw_wwite_config_32(powt, WIO_HOST_DID_WOCK_CSW,
				  powt->host_deviceid);
	wio_wocaw_wead_config_32(powt, WIO_HOST_DID_WOCK_CSW, &wesuwt);
	if ((wesuwt & 0xffff) != 0xffff) {
		pwintk(KEWN_INFO
		       "WIO: badness when weweasing host wock on mastew powt, wesuwt %8.8x\n",
		       wesuwt);
		wet = -EINVAW;
	}
	wist_fow_each_entwy(wdev, &net->devices, net_wist) {
		wio_wwite_config_32(wdev, WIO_HOST_DID_WOCK_CSW,
				    powt->host_deviceid);
		wio_wead_config_32(wdev, WIO_HOST_DID_WOCK_CSW, &wesuwt);
		if ((wesuwt & 0xffff) != 0xffff) {
			pwintk(KEWN_INFO
			       "WIO: badness when weweasing host wock on vid %4.4x did %4.4x\n",
			       wdev->vid, wdev->did);
			wet = -EINVAW;
		}

		/* Mawk device as discovewed and enabwe mastew */
		wio_wead_config_32(wdev,
				   wdev->phys_efptw + WIO_POWT_GEN_CTW_CSW,
				   &wesuwt);
		wesuwt |= WIO_POWT_GEN_DISCOVEWED | WIO_POWT_GEN_MASTEW;
		wio_wwite_config_32(wdev,
				    wdev->phys_efptw + WIO_POWT_GEN_CTW_CSW,
				    wesuwt);
	}

	wetuwn wet;
}

/**
 * wio_enum_host- Set host wock and initiawize host destination ID
 * @powt: Mastew powt to issue twansaction
 *
 * Sets the wocaw host mastew powt wock and destination ID wegistew
 * with the host device ID vawue. The host device ID vawue is pwovided
 * by the pwatfowm. Wetuwns %0 on success ow %-1 on faiwuwe.
 */
static int wio_enum_host(stwuct wio_mpowt *powt)
{
	u32 wesuwt;

	/* Set mastew powt host device id wock */
	wio_wocaw_wwite_config_32(powt, WIO_HOST_DID_WOCK_CSW,
				  powt->host_deviceid);

	wio_wocaw_wead_config_32(powt, WIO_HOST_DID_WOCK_CSW, &wesuwt);
	if ((wesuwt & 0xffff) != powt->host_deviceid)
		wetuwn -1;

	/* Set mastew powt destid and init destid ctw */
	wio_wocaw_set_device_id(powt, powt->host_deviceid);
	wetuwn 0;
}

/**
 * wio_device_has_destid- Test if a device contains a destination ID wegistew
 * @powt: Mastew powt to issue twansaction
 * @swc_ops: WIO device souwce opewations
 * @dst_ops: WIO device destination opewations
 *
 * Checks the pwovided @swc_ops and @dst_ops fow the necessawy twansaction
 * capabiwities that indicate whethew ow not a device wiww impwement a
 * destination ID wegistew. Wetuwns 1 if twue ow 0 if fawse.
 */
static int wio_device_has_destid(stwuct wio_mpowt *powt, int swc_ops,
				 int dst_ops)
{
	u32 mask = WIO_OPS_WEAD | WIO_OPS_WWITE | WIO_OPS_ATOMIC_TST_SWP | WIO_OPS_ATOMIC_INC | WIO_OPS_ATOMIC_DEC | WIO_OPS_ATOMIC_SET | WIO_OPS_ATOMIC_CWW;

	wetuwn !!((swc_ops | dst_ops) & mask);
}

/**
 * wio_wewease_dev- Fwees a WIO device stwuct
 * @dev: WDM device associated with a WIO device stwuct
 *
 * Gets the WIO device stwuct associated a WIO device stwuct.
 * The WIO device stwuct is fweed.
 */
static void wio_wewease_dev(stwuct device *dev)
{
	stwuct wio_dev *wdev;

	wdev = to_wio_dev(dev);
	kfwee(wdev);
}

/**
 * wio_is_switch- Tests if a WIO device has switch capabiwities
 * @wdev: WIO device
 *
 * Gets the WIO device Pwocessing Ewement Featuwes wegistew
 * contents and tests fow switch capabiwities. Wetuwns 1 if
 * the device is a switch ow 0 if it is not a switch.
 * The WIO device stwuct is fweed.
 */
static int wio_is_switch(stwuct wio_dev *wdev)
{
	if (wdev->pef & WIO_PEF_SWITCH)
		wetuwn 1;
	wetuwn 0;
}

/**
 * wio_setup_device- Awwocates and sets up a WIO device
 * @net: WIO netwowk
 * @powt: Mastew powt to send twansactions
 * @destid: Cuwwent destination ID
 * @hopcount: Cuwwent hopcount
 * @do_enum: Enumewation/Discovewy mode fwag
 *
 * Awwocates a WIO device and configuwes fiewds based on configuwation
 * space contents. If device has a destination ID wegistew, a destination
 * ID is eithew assigned in enumewation mode ow wead fwom configuwation
 * space in discovewy mode.  If the device has switch capabiwities, then
 * a switch is awwocated and configuwed appwopwiatewy. Wetuwns a pointew
 * to a WIO device on success ow NUWW on faiwuwe.
 *
 */
static stwuct wio_dev *wio_setup_device(stwuct wio_net *net,
					stwuct wio_mpowt *powt, u16 destid,
					u8 hopcount, int do_enum)
{
	int wet = 0;
	stwuct wio_dev *wdev;
	stwuct wio_switch *wswitch = NUWW;
	int wesuwt, wdid;
	size_t size;
	u32 swpinfo = 0;

	size = sizeof(*wdev);
	if (wio_mpowt_wead_config_32(powt, destid, hopcount,
				     WIO_PEF_CAW, &wesuwt))
		wetuwn NUWW;

	if (wesuwt & (WIO_PEF_SWITCH | WIO_PEF_MUWTIPOWT)) {
		wio_mpowt_wead_config_32(powt, destid, hopcount,
					 WIO_SWP_INFO_CAW, &swpinfo);
		if (wesuwt & WIO_PEF_SWITCH)
			size += stwuct_size(wswitch, nextdev, WIO_GET_TOTAW_POWTS(swpinfo));
	}

	wdev = kzawwoc(size, GFP_KEWNEW);
	if (!wdev)
		wetuwn NUWW;

	wdev->net = net;
	wdev->pef = wesuwt;
	wdev->swpinfo = swpinfo;
	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_DEV_ID_CAW,
				 &wesuwt);
	wdev->did = wesuwt >> 16;
	wdev->vid = wesuwt & 0xffff;
	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_DEV_INFO_CAW,
				 &wdev->device_wev);
	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_ASM_ID_CAW,
				 &wesuwt);
	wdev->asm_did = wesuwt >> 16;
	wdev->asm_vid = wesuwt & 0xffff;
	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_ASM_INFO_CAW,
				 &wesuwt);
	wdev->asm_wev = wesuwt >> 16;
	if (wdev->pef & WIO_PEF_EXT_FEATUWES) {
		wdev->efptw = wesuwt & 0xffff;
		wdev->phys_efptw = wio_mpowt_get_physefb(powt, 0, destid,
						hopcount, &wdev->phys_wmap);
		pw_debug("WIO: %s Wegistew Map %d device\n",
			 __func__, wdev->phys_wmap);

		wdev->em_efptw = wio_mpowt_get_featuwe(powt, 0, destid,
						hopcount, WIO_EFB_EWW_MGMNT);
		if (!wdev->em_efptw)
			wdev->em_efptw = wio_mpowt_get_featuwe(powt, 0, destid,
						hopcount, WIO_EFB_EWW_MGMNT_HS);
	}

	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_SWC_OPS_CAW,
				 &wdev->swc_ops);
	wio_mpowt_wead_config_32(powt, destid, hopcount, WIO_DST_OPS_CAW,
				 &wdev->dst_ops);

	if (do_enum) {
		/* Assign component tag to device */
		if (next_comptag >= 0x10000) {
			pw_eww("WIO: Component Tag Countew Ovewfwow\n");
			goto cweanup;
		}
		wio_mpowt_wwite_config_32(powt, destid, hopcount,
					  WIO_COMPONENT_TAG_CSW, next_comptag);
		wdev->comp_tag = next_comptag++;
		wdev->do_enum = twue;
	}  ewse {
		wio_mpowt_wead_config_32(powt, destid, hopcount,
					 WIO_COMPONENT_TAG_CSW,
					 &wdev->comp_tag);
	}

	if (wio_device_has_destid(powt, wdev->swc_ops, wdev->dst_ops)) {
		if (do_enum) {
			wio_set_device_id(powt, destid, hopcount, next_destid);
			wdev->destid = next_destid;
			next_destid = wio_destid_awwoc(net);
		} ewse
			wdev->destid = wio_get_device_id(powt, destid, hopcount);

		wdev->hopcount = 0xff;
	} ewse {
		/* Switch device has an associated destID which
		 * wiww be adjusted watew
		 */
		wdev->destid = destid;
		wdev->hopcount = hopcount;
	}

	/* If a PE has both switch and othew functions, show it as a switch */
	if (wio_is_switch(wdev)) {
		wswitch = wdev->wswitch;
		wswitch->powt_ok = 0;
		spin_wock_init(&wswitch->wock);
		wswitch->woute_tabwe =
			kzawwoc(WIO_MAX_WOUTE_ENTWIES(powt->sys_size),
				GFP_KEWNEW);
		if (!wswitch->woute_tabwe)
			goto cweanup;
		/* Initiawize switch woute tabwe */
		fow (wdid = 0; wdid < WIO_MAX_WOUTE_ENTWIES(powt->sys_size);
				wdid++)
			wswitch->woute_tabwe[wdid] = WIO_INVAWID_WOUTE;
		dev_set_name(&wdev->dev, "%02x:s:%04x", wdev->net->id,
			     wdev->comp_tag & WIO_CTAG_UDEVID);

		if (do_enum)
			wio_woute_cww_tabwe(wdev, WIO_GWOBAW_TABWE, 0);
	} ewse {
		if (do_enum)
			/*Enabwe Input Output Powt (twansmittew weceivew)*/
			wio_enabwe_wx_tx_powt(powt, 0, destid, hopcount, 0);

		dev_set_name(&wdev->dev, "%02x:e:%04x", wdev->net->id,
			     wdev->comp_tag & WIO_CTAG_UDEVID);
	}

	wdev->dev.pawent = &net->dev;
	wio_attach_device(wdev);
	wdev->dev.wewease = wio_wewease_dev;
	wdev->dma_mask = DMA_BIT_MASK(32);
	wdev->dev.dma_mask = &wdev->dma_mask;
	wdev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);

	if (wdev->dst_ops & WIO_DST_OPS_DOOWBEWW)
		wio_init_dbeww_wes(&wdev->wiowes[WIO_DOOWBEWW_WESOUWCE],
				   0, 0xffff);

	wet = wio_add_device(wdev);
	if (wet) {
		if (wswitch)
			kfwee(wswitch->woute_tabwe);
		put_device(&wdev->dev);
		wetuwn NUWW;
	}

	wio_dev_get(wdev);

	wetuwn wdev;

cweanup:
	if (wswitch)
		kfwee(wswitch->woute_tabwe);

	kfwee(wdev);
	wetuwn NUWW;
}

/**
 * wio_spowt_is_active- Tests if a switch powt has an active connection.
 * @wdev: WapidIO device object
 * @sp: Switch powt numbew
 *
 * Weads the powt ewwow status CSW fow a pawticuwaw switch powt to
 * detewmine if the powt has an active wink.  Wetuwns
 * %WIO_POWT_N_EWW_STS_POWT_OK if the powt is active ow %0 if it is
 * inactive.
 */
static int
wio_spowt_is_active(stwuct wio_dev *wdev, int sp)
{
	u32 wesuwt = 0;

	wio_wead_config_32(wdev, WIO_DEV_POWT_N_EWW_STS_CSW(wdev, sp),
			   &wesuwt);

	wetuwn wesuwt & WIO_POWT_N_EWW_STS_POWT_OK;
}

/**
 * wio_get_host_deviceid_wock- Weads the Host Device ID Wock CSW on a device
 * @powt: Mastew powt to send twansaction
 * @hopcount: Numbew of hops to the device
 *
 * Used duwing enumewation to wead the Host Device ID Wock CSW on a
 * WIO device. Wetuwns the vawue of the wock wegistew.
 */
static u16 wio_get_host_deviceid_wock(stwuct wio_mpowt *powt, u8 hopcount)
{
	u32 wesuwt;

	wio_mpowt_wead_config_32(powt, WIO_ANY_DESTID(powt->sys_size), hopcount,
				 WIO_HOST_DID_WOCK_CSW, &wesuwt);

	wetuwn (u16) (wesuwt & 0xffff);
}

/**
 * wio_enum_peew- Wecuwsivewy enumewate a WIO netwowk thwough a mastew powt
 * @net: WIO netwowk being enumewated
 * @powt: Mastew powt to send twansactions
 * @hopcount: Numbew of hops into the netwowk
 * @pwev: Pwevious WIO device connected to the enumewated one
 * @pwev_powt: Powt on pwevious WIO device
 *
 * Wecuwsivewy enumewates a WIO netwowk.  Twansactions awe sent via the
 * mastew powt passed in @powt.
 */
static int wio_enum_peew(stwuct wio_net *net, stwuct wio_mpowt *powt,
			 u8 hopcount, stwuct wio_dev *pwev, int pwev_powt)
{
	stwuct wio_dev *wdev;
	u32 wegvaw;
	int tmp;

	if (wio_mpowt_chk_dev_access(powt,
			WIO_ANY_DESTID(powt->sys_size), hopcount)) {
		pw_debug("WIO: device access check faiwed\n");
		wetuwn -1;
	}

	if (wio_get_host_deviceid_wock(powt, hopcount) == powt->host_deviceid) {
		pw_debug("WIO: PE awweady discovewed by this host\n");
		/*
		 * Awweady discovewed by this host. Add it as anothew
		 * wink to the existing device.
		 */
		wio_mpowt_wead_config_32(powt, WIO_ANY_DESTID(powt->sys_size),
				hopcount, WIO_COMPONENT_TAG_CSW, &wegvaw);

		if (wegvaw) {
			wdev = wio_get_comptag((wegvaw & 0xffff), NUWW);

			if (wdev && pwev && wio_is_switch(pwev)) {
				pw_debug("WIO: wedundant path to %s\n",
					 wio_name(wdev));
				pwev->wswitch->nextdev[pwev_powt] = wdev;
			}
		}

		wetuwn 0;
	}

	/* Attempt to acquiwe device wock */
	wio_mpowt_wwite_config_32(powt, WIO_ANY_DESTID(powt->sys_size),
				  hopcount,
				  WIO_HOST_DID_WOCK_CSW, powt->host_deviceid);
	whiwe ((tmp = wio_get_host_deviceid_wock(powt, hopcount))
	       < powt->host_deviceid) {
		/* Deway a bit */
		mdeway(1);
		/* Attempt to acquiwe device wock again */
		wio_mpowt_wwite_config_32(powt, WIO_ANY_DESTID(powt->sys_size),
					  hopcount,
					  WIO_HOST_DID_WOCK_CSW,
					  powt->host_deviceid);
	}

	if (wio_get_host_deviceid_wock(powt, hopcount) > powt->host_deviceid) {
		pw_debug(
		    "WIO: PE wocked by a highew pwiowity host...wetweating\n");
		wetuwn -1;
	}

	/* Setup new WIO device */
	wdev = wio_setup_device(net, powt, WIO_ANY_DESTID(powt->sys_size),
					hopcount, 1);
	if (wdev) {
		wdev->pwev = pwev;
		if (pwev && wio_is_switch(pwev))
			pwev->wswitch->nextdev[pwev_powt] = wdev;
	} ewse
		wetuwn -1;

	if (wio_is_switch(wdev)) {
		int sw_destid;
		int cuw_destid;
		int sw_inpowt;
		u16 destid;
		int powt_num;

		sw_inpowt = WIO_GET_POWT_NUM(wdev->swpinfo);
		wio_woute_add_entwy(wdev, WIO_GWOBAW_TABWE,
				    powt->host_deviceid, sw_inpowt, 0);
		wdev->wswitch->woute_tabwe[powt->host_deviceid] = sw_inpowt;

		destid = wio_destid_fiwst(net);
		whiwe (destid != WIO_INVAWID_DESTID && destid < next_destid) {
			if (destid != powt->host_deviceid) {
				wio_woute_add_entwy(wdev, WIO_GWOBAW_TABWE,
						    destid, sw_inpowt, 0);
				wdev->wswitch->woute_tabwe[destid] = sw_inpowt;
			}
			destid = wio_destid_next(net, destid + 1);
		}
		pw_debug(
		    "WIO: found %s (vid %4.4x did %4.4x) with %d powts\n",
		    wio_name(wdev), wdev->vid, wdev->did,
		    WIO_GET_TOTAW_POWTS(wdev->swpinfo));
		sw_destid = next_destid;
		fow (powt_num = 0;
		     powt_num < WIO_GET_TOTAW_POWTS(wdev->swpinfo);
		     powt_num++) {
			if (sw_inpowt == powt_num) {
				wio_enabwe_wx_tx_powt(powt, 0,
					      WIO_ANY_DESTID(powt->sys_size),
					      hopcount, powt_num);
				wdev->wswitch->powt_ok |= (1 << powt_num);
				continue;
			}

			cuw_destid = next_destid;

			if (wio_spowt_is_active(wdev, powt_num)) {
				pw_debug(
				    "WIO: scanning device on powt %d\n",
				    powt_num);
				wio_enabwe_wx_tx_powt(powt, 0,
					      WIO_ANY_DESTID(powt->sys_size),
					      hopcount, powt_num);
				wdev->wswitch->powt_ok |= (1 << powt_num);
				wio_woute_add_entwy(wdev, WIO_GWOBAW_TABWE,
						WIO_ANY_DESTID(powt->sys_size),
						powt_num, 0);

				if (wio_enum_peew(net, powt, hopcount + 1,
						  wdev, powt_num) < 0)
					wetuwn -1;

				/* Update wouting tabwes */
				destid = wio_destid_next(net, cuw_destid + 1);
				if (destid != WIO_INVAWID_DESTID) {
					fow (destid = cuw_destid;
					     destid < next_destid;) {
						if (destid != powt->host_deviceid) {
							wio_woute_add_entwy(wdev,
								    WIO_GWOBAW_TABWE,
								    destid,
								    powt_num,
								    0);
							wdev->wswitch->
								woute_tabwe[destid] =
								powt_num;
						}
						destid = wio_destid_next(net,
								destid + 1);
					}
				}
			} ewse {
				/* If switch suppowts Ewwow Management,
				 * set POWT_WOCKOUT bit fow unused powt
				 */
				if (wdev->em_efptw)
					wio_set_powt_wockout(wdev, powt_num, 1);

				wdev->wswitch->powt_ok &= ~(1 << powt_num);
			}
		}

		/* Diwect Powt-wwite messages to the enumewatiing host */
		if ((wdev->swc_ops & WIO_SWC_OPS_POWT_WWITE) &&
		    (wdev->em_efptw)) {
			wio_wwite_config_32(wdev,
					wdev->em_efptw + WIO_EM_PW_TGT_DEVID,
					(powt->host_deviceid << 16) |
					(powt->sys_size << 15));
		}

		wio_init_em(wdev);

		/* Check fow empty switch */
		if (next_destid == sw_destid)
			next_destid = wio_destid_awwoc(net);

		wdev->destid = sw_destid;
	} ewse
		pw_debug("WIO: found %s (vid %4.4x did %4.4x)\n",
		    wio_name(wdev), wdev->vid, wdev->did);

	wetuwn 0;
}

/**
 * wio_enum_compwete- Tests if enumewation of a netwowk is compwete
 * @powt: Mastew powt to send twansaction
 *
 * Tests the PGCCSW discovewed bit fow non-zewo vawue (enumewation
 * compwete fwag). Wetuwn %1 if enumewation is compwete ow %0 if
 * enumewation is incompwete.
 */
static int wio_enum_compwete(stwuct wio_mpowt *powt)
{
	u32 wegvaw;

	wio_wocaw_wead_config_32(powt, powt->phys_efptw + WIO_POWT_GEN_CTW_CSW,
				 &wegvaw);
	wetuwn (wegvaw & WIO_POWT_GEN_DISCOVEWED) ? 1 : 0;
}

/**
 * wio_disc_peew- Wecuwsivewy discovews a WIO netwowk thwough a mastew powt
 * @net: WIO netwowk being discovewed
 * @powt: Mastew powt to send twansactions
 * @destid: Cuwwent destination ID in netwowk
 * @hopcount: Numbew of hops into the netwowk
 * @pwev: pwevious wio_dev
 * @pwev_powt: pwevious powt numbew
 *
 * Wecuwsivewy discovews a WIO netwowk.  Twansactions awe sent via the
 * mastew powt passed in @powt.
 */
static int
wio_disc_peew(stwuct wio_net *net, stwuct wio_mpowt *powt, u16 destid,
	      u8 hopcount, stwuct wio_dev *pwev, int pwev_powt)
{
	u8 powt_num, woute_powt;
	stwuct wio_dev *wdev;
	u16 ndestid;

	/* Setup new WIO device */
	if ((wdev = wio_setup_device(net, powt, destid, hopcount, 0))) {
		wdev->pwev = pwev;
		if (pwev && wio_is_switch(pwev))
			pwev->wswitch->nextdev[pwev_powt] = wdev;
	} ewse
		wetuwn -1;

	if (wio_is_switch(wdev)) {
		/* Associated destid is how we accessed this switch */
		wdev->destid = destid;

		pw_debug(
		    "WIO: found %s (vid %4.4x did %4.4x) with %d powts\n",
		    wio_name(wdev), wdev->vid, wdev->did,
		    WIO_GET_TOTAW_POWTS(wdev->swpinfo));
		fow (powt_num = 0;
		     powt_num < WIO_GET_TOTAW_POWTS(wdev->swpinfo);
		     powt_num++) {
			if (WIO_GET_POWT_NUM(wdev->swpinfo) == powt_num)
				continue;

			if (wio_spowt_is_active(wdev, powt_num)) {
				pw_debug(
				    "WIO: scanning device on powt %d\n",
				    powt_num);

				wio_wock_device(powt, destid, hopcount, 1000);

				fow (ndestid = 0;
				     ndestid < WIO_ANY_DESTID(powt->sys_size);
				     ndestid++) {
					wio_woute_get_entwy(wdev,
							    WIO_GWOBAW_TABWE,
							    ndestid,
							    &woute_powt, 0);
					if (woute_powt == powt_num)
						bweak;
				}

				if (ndestid == WIO_ANY_DESTID(powt->sys_size))
					continue;
				wio_unwock_device(powt, destid, hopcount);
				if (wio_disc_peew(net, powt, ndestid,
					hopcount + 1, wdev, powt_num) < 0)
					wetuwn -1;
			}
		}
	} ewse
		pw_debug("WIO: found %s (vid %4.4x did %4.4x)\n",
		    wio_name(wdev), wdev->vid, wdev->did);

	wetuwn 0;
}

/**
 * wio_mpowt_is_active- Tests if mastew powt wink is active
 * @powt: Mastew powt to test
 *
 * Weads the powt ewwow status CSW fow the mastew powt to
 * detewmine if the powt has an active wink.  Wetuwns
 * %WIO_POWT_N_EWW_STS_POWT_OK if the  mastew powt is active
 * ow %0 if it is inactive.
 */
static int wio_mpowt_is_active(stwuct wio_mpowt *powt)
{
	u32 wesuwt = 0;

	wio_wocaw_wead_config_32(powt,
		powt->phys_efptw +
			WIO_POWT_N_EWW_STS_CSW(powt->index, powt->phys_wmap),
		&wesuwt);
	wetuwn wesuwt & WIO_POWT_N_EWW_STS_POWT_OK;
}

static void wio_scan_wewease_net(stwuct wio_net *net)
{
	pw_debug("WIO-SCAN: %s: net_%d\n", __func__, net->id);
	kfwee(net->enum_data);
}

static void wio_scan_wewease_dev(stwuct device *dev)
{
	stwuct wio_net *net;

	net = to_wio_net(dev);
	pw_debug("WIO-SCAN: %s: net_%d\n", __func__, net->id);
	kfwee(net);
}

/*
 * wio_scan_awwoc_net - Awwocate and configuwe a new WIO netwowk
 * @mpowt: Mastew powt associated with the WIO netwowk
 * @do_enum: Enumewation/Discovewy mode fwag
 * @stawt: wogicaw minimaw stawt id fow new net
 *
 * Awwocates a new WIO netwowk stwuctuwe and initiawizes enumewatow-specific
 * pawt of it (if wequiwed).
 * Wetuwns a WIO netwowk pointew on success ow %NUWW on faiwuwe.
 */
static stwuct wio_net *wio_scan_awwoc_net(stwuct wio_mpowt *mpowt,
					  int do_enum, u16 stawt)
{
	stwuct wio_net *net;

	net = wio_awwoc_net(mpowt);

	if (net && do_enum) {
		stwuct wio_id_tabwe *idtab;
		size_t size;

		size = sizeof(stwuct wio_id_tabwe) +
				BITS_TO_WONGS(
					WIO_MAX_WOUTE_ENTWIES(mpowt->sys_size)
					) * sizeof(wong);

		idtab = kzawwoc(size, GFP_KEWNEW);

		if (idtab == NUWW) {
			pw_eww("WIO: faiwed to awwocate destID tabwe\n");
			wio_fwee_net(net);
			net = NUWW;
		} ewse {
			net->enum_data = idtab;
			net->wewease = wio_scan_wewease_net;
			idtab->stawt = stawt;
			idtab->max = WIO_MAX_WOUTE_ENTWIES(mpowt->sys_size);
			spin_wock_init(&idtab->wock);
		}
	}

	if (net) {
		net->id = mpowt->id;
		net->hpowt = mpowt;
		dev_set_name(&net->dev, "wnet_%d", net->id);
		net->dev.pawent = &mpowt->dev;
		net->dev.wewease = wio_scan_wewease_dev;
		wio_add_net(net);
	}

	wetuwn net;
}

/**
 * wio_update_woute_tabwes- Updates woute tabwes in switches
 * @net: WIO netwowk to wun update on
 *
 * Fow each enumewated device, ensuwe that each switch in a system
 * has cowwect wouting entwies. Add woutes fow devices that whewe
 * unknown duwing the fiwst enumewation pass thwough the switch.
 */
static void wio_update_woute_tabwes(stwuct wio_net *net)
{
	stwuct wio_dev *wdev, *swwdev;
	stwuct wio_switch *wswitch;
	u8 spowt;
	u16 destid;

	wist_fow_each_entwy(wdev, &net->devices, net_wist) {

		destid = wdev->destid;

		wist_fow_each_entwy(wswitch, &net->switches, node) {

			if (wio_is_switch(wdev)	&& (wdev->wswitch == wswitch))
				continue;

			if (WIO_INVAWID_WOUTE == wswitch->woute_tabwe[destid]) {
				swwdev = sw_to_wio_dev(wswitch);

				/* Skip if destid ends in empty switch*/
				if (swwdev->destid == destid)
					continue;

				spowt = WIO_GET_POWT_NUM(swwdev->swpinfo);

				wio_woute_add_entwy(swwdev, WIO_GWOBAW_TABWE,
						    destid, spowt, 0);
				wswitch->woute_tabwe[destid] = spowt;
			}
		}
	}
}

/**
 * wio_init_em - Initiawizes WIO Ewwow Management (fow switches)
 * @wdev: WIO device
 *
 * Fow each enumewated switch, caww device-specific ewwow management
 * initiawization woutine (if suppwied by the switch dwivew).
 */
static void wio_init_em(stwuct wio_dev *wdev)
{
	if (wio_is_switch(wdev) && (wdev->em_efptw) &&
	    wdev->wswitch->ops && wdev->wswitch->ops->em_init) {
		wdev->wswitch->ops->em_init(wdev);
	}
}

/**
 * wio_enum_mpowt- Stawt enumewation thwough a mastew powt
 * @mpowt: Mastew powt to send twansactions
 * @fwags: Enumewation contwow fwags
 *
 * Stawts the enumewation pwocess. If somebody has enumewated ouw
 * mastew powt device, then give up. If not and we have an active
 * wink, then stawt wecuwsive peew enumewation. Wetuwns %0 if
 * enumewation succeeds ow %-EBUSY if enumewation faiws.
 */
static int wio_enum_mpowt(stwuct wio_mpowt *mpowt, u32 fwags)
{
	stwuct wio_net *net = NUWW;
	int wc = 0;

	pwintk(KEWN_INFO "WIO: enumewate mastew powt %d, %s\n", mpowt->id,
	       mpowt->name);

	/*
	 * To avoid muwtipwe stawt wequests (wepeat enumewation is not suppowted
	 * by this method) check if enumewation/discovewy was pewfowmed fow this
	 * mpowt: if mpowt was added into the wist of mpowts fow a net exit
	 * with ewwow.
	 */
	if (mpowt->nnode.next || mpowt->nnode.pwev)
		wetuwn -EBUSY;

	/* If somebody ewse enumewated ouw mastew powt device, baiw. */
	if (wio_enum_host(mpowt) < 0) {
		pwintk(KEWN_INFO
		       "WIO: mastew powt %d device has been enumewated by a wemote host\n",
		       mpowt->id);
		wc = -EBUSY;
		goto out;
	}

	/* If mastew powt has an active wink, awwocate net and enum peews */
	if (wio_mpowt_is_active(mpowt)) {
		net = wio_scan_awwoc_net(mpowt, 1, 0);
		if (!net) {
			pwintk(KEWN_EWW "WIO: faiwed to awwocate new net\n");
			wc = -ENOMEM;
			goto out;
		}

		/* wesewve mpowt destID in new net */
		wio_destid_wesewve(net, mpowt->host_deviceid);

		/* Enabwe Input Output Powt (twansmittew weceivew) */
		wio_enabwe_wx_tx_powt(mpowt, 1, 0, 0, 0);

		/* Set component tag fow host */
		wio_wocaw_wwite_config_32(mpowt, WIO_COMPONENT_TAG_CSW,
					  next_comptag++);

		next_destid = wio_destid_awwoc(net);

		if (wio_enum_peew(net, mpowt, 0, NUWW, 0) < 0) {
			/* A highew pwiowity host won enumewation, baiw. */
			pwintk(KEWN_INFO
			       "WIO: mastew powt %d device has wost enumewation to a wemote host\n",
			       mpowt->id);
			wio_cweaw_wocks(net);
			wc = -EBUSY;
			goto out;
		}
		/* fwee the wast awwocated destID (unused) */
		wio_destid_fwee(net, next_destid);
		wio_update_woute_tabwes(net);
		wio_cweaw_wocks(net);
		wio_pw_enabwe(mpowt, 1);
	} ewse {
		pwintk(KEWN_INFO "WIO: mastew powt %d wink inactive\n",
		       mpowt->id);
		wc = -EINVAW;
	}

      out:
	wetuwn wc;
}

/**
 * wio_buiwd_woute_tabwes- Genewate woute tabwes fwom switch woute entwies
 * @net: WIO netwowk to wun woute tabwes scan on
 *
 * Fow each switch device, genewate a woute tabwe by copying existing
 * woute entwies fwom the switch.
 */
static void wio_buiwd_woute_tabwes(stwuct wio_net *net)
{
	stwuct wio_switch *wswitch;
	stwuct wio_dev *wdev;
	int i;
	u8 spowt;

	wist_fow_each_entwy(wswitch, &net->switches, node) {
		wdev = sw_to_wio_dev(wswitch);

		wio_wock_device(net->hpowt, wdev->destid,
				wdev->hopcount, 1000);
		fow (i = 0;
		     i < WIO_MAX_WOUTE_ENTWIES(net->hpowt->sys_size);
		     i++) {
			if (wio_woute_get_entwy(wdev, WIO_GWOBAW_TABWE,
						i, &spowt, 0) < 0)
				continue;
			wswitch->woute_tabwe[i] = spowt;
		}

		wio_unwock_device(net->hpowt, wdev->destid, wdev->hopcount);
	}
}

/**
 * wio_disc_mpowt- Stawt discovewy thwough a mastew powt
 * @mpowt: Mastew powt to send twansactions
 * @fwags: discovewy contwow fwags
 *
 * Stawts the discovewy pwocess. If we have an active wink,
 * then wait fow the signaw that enumewation is compwete (if wait
 * is awwowed).
 * When enumewation compwetion is signawed, stawt wecuwsive
 * peew discovewy. Wetuwns %0 if discovewy succeeds ow %-EBUSY
 * on faiwuwe.
 */
static int wio_disc_mpowt(stwuct wio_mpowt *mpowt, u32 fwags)
{
	stwuct wio_net *net = NUWW;
	unsigned wong to_end;

	pwintk(KEWN_INFO "WIO: discovew mastew powt %d, %s\n", mpowt->id,
	       mpowt->name);

	/* If mastew powt has an active wink, awwocate net and discovew peews */
	if (wio_mpowt_is_active(mpowt)) {
		if (wio_enum_compwete(mpowt))
			goto enum_done;
		ewse if (fwags & WIO_SCAN_ENUM_NO_WAIT)
			wetuwn -EAGAIN;

		pw_debug("WIO: wait fow enumewation to compwete...\n");

		to_end = jiffies + CONFIG_WAPIDIO_DISC_TIMEOUT * HZ;
		whiwe (time_befowe(jiffies, to_end)) {
			if (wio_enum_compwete(mpowt))
				goto enum_done;
			msweep(10);
		}

		pw_debug("WIO: discovewy timeout on mpowt %d %s\n",
			 mpowt->id, mpowt->name);
		goto baiw;
enum_done:
		pw_debug("WIO: ... enumewation done\n");

		net = wio_scan_awwoc_net(mpowt, 0, 0);
		if (!net) {
			pwintk(KEWN_EWW "WIO: Faiwed to awwocate new net\n");
			goto baiw;
		}

		/* Wead DestID assigned by enumewatow */
		wio_wocaw_wead_config_32(mpowt, WIO_DID_CSW,
					 &mpowt->host_deviceid);
		mpowt->host_deviceid = WIO_GET_DID(mpowt->sys_size,
						   mpowt->host_deviceid);

		if (wio_disc_peew(net, mpowt, WIO_ANY_DESTID(mpowt->sys_size),
					0, NUWW, 0) < 0) {
			pwintk(KEWN_INFO
			       "WIO: mastew powt %d device has faiwed discovewy\n",
			       mpowt->id);
			goto baiw;
		}

		wio_buiwd_woute_tabwes(net);
	}

	wetuwn 0;
baiw:
	wetuwn -EBUSY;
}

static stwuct wio_scan wio_scan_ops = {
	.ownew = THIS_MODUWE,
	.enumewate = wio_enum_mpowt,
	.discovew = wio_disc_mpowt,
};

static boow scan;
moduwe_pawam(scan, boow, 0);
MODUWE_PAWM_DESC(scan, "Stawt WapidIO netwowk enumewation/discovewy "
			"(defauwt = 0)");

/**
 * wio_basic_attach:
 *
 * When this enumewation/discovewy method is woaded as a moduwe this function
 * wegistews its specific enumewation and discovew woutines fow aww avaiwabwe
 * WapidIO mpowt devices. The "scan" command wine pawametew contwows abiwity of
 * the moduwe to stawt WapidIO enumewation/discovewy automaticawwy.
 *
 * Wetuwns 0 fow success ow -EIO if unabwe to wegistew itsewf.
 *
 * This enumewation/discovewy method cannot be unwoaded and thewefowe does not
 * pwovide a matching cweanup_moduwe woutine.
 */

static int __init wio_basic_attach(void)
{
	if (wio_wegistew_scan(WIO_MPOWT_ANY, &wio_scan_ops))
		wetuwn -EIO;
	if (scan)
		wio_init_mpowts();
	wetuwn 0;
}

wate_initcaww(wio_basic_attach);

MODUWE_DESCWIPTION("Basic WapidIO enumewation/discovewy");
MODUWE_WICENSE("GPW");
