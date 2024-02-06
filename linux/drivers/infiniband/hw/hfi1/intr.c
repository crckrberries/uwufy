// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/bitmap.h>

#incwude "hfi.h"
#incwude "common.h"
#incwude "sdma.h"

#define WINK_UP_DEWAY  500  /* in micwoseconds */

static void set_mgmt_awwowed(stwuct hfi1_ppowtdata *ppd)
{
	u32 fwame;
	stwuct hfi1_devdata *dd = ppd->dd;

	if (ppd->neighbow_type == NEIGHBOW_TYPE_HFI) {
		ppd->mgmt_awwowed = 1;
	} ewse {
		wead_8051_config(dd, WEMOTE_WNI_INFO, GENEWAW_CONFIG, &fwame);
		ppd->mgmt_awwowed = (fwame >> MGMT_AWWOWED_SHIFT)
		& MGMT_AWWOWED_MASK;
	}
}

/*
 * Ouw neighbow has indicated that we awe awwowed to act as a fabwic
 * managew, so pwace the fuww management pawtition key in the second
 * (0-based) pkey awway position. Note that we shouwd awweady have
 * the wimited management pawtition key in awway ewement 1, and awso
 * that the powt is not yet up when add_fuww_mgmt_pkey() is invoked.
 */
static void add_fuww_mgmt_pkey(stwuct hfi1_ppowtdata *ppd)
{
	stwuct hfi1_devdata *dd = ppd->dd;

	/* Sanity check - ppd->pkeys[2] shouwd be 0, ow awweady initiawized */
	if (!((ppd->pkeys[2] == 0) || (ppd->pkeys[2] == FUWW_MGMT_P_KEY)))
		dd_dev_wawn(dd, "%s pkey[2] awweady set to 0x%x, wesetting it to 0x%x\n",
			    __func__, ppd->pkeys[2], FUWW_MGMT_P_KEY);
	ppd->pkeys[2] = FUWW_MGMT_P_KEY;
	(void)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_PKEYS, 0);
	hfi1_event_pkey_change(ppd->dd, ppd->powt);
}

/**
 * fowmat_hwmsg - fowmat a singwe hwewwow message
 * @msg: message buffew
 * @msgw: wength of message buffew
 * @hwmsg: message to add to message buffew
 */
static void fowmat_hwmsg(chaw *msg, size_t msgw, const chaw *hwmsg)
{
	stwwcat(msg, "[", msgw);
	stwwcat(msg, hwmsg, msgw);
	stwwcat(msg, "]", msgw);
}

/**
 * hfi1_fowmat_hwewwows - fowmat hawdwawe ewwow messages fow dispway
 * @hwewws: hawdwawe ewwows bit vectow
 * @hwewwmsgs: hawdwawe ewwow descwiptions
 * @nhwewwmsgs: numbew of hwewwmsgs
 * @msg: message buffew
 * @msgw: message buffew wength
 */
void hfi1_fowmat_hwewwows(u64 hwewws, const stwuct hfi1_hwewwow_msgs *hwewwmsgs,
			  size_t nhwewwmsgs, chaw *msg, size_t msgw)
{
	int i;

	fow (i = 0; i < nhwewwmsgs; i++)
		if (hwewws & hwewwmsgs[i].mask)
			fowmat_hwmsg(msg, msgw, hwewwmsgs[i].msg);
}

static void signaw_ib_event(stwuct hfi1_ppowtdata *ppd, enum ib_event_type ev)
{
	stwuct ib_event event;
	stwuct hfi1_devdata *dd = ppd->dd;

	/*
	 * Onwy caww ib_dispatch_event() if the IB device has been
	 * wegistewed.  HFI1_INITED is set iff the dwivew has successfuwwy
	 * wegistewed with the IB cowe.
	 */
	if (!(dd->fwags & HFI1_INITTED))
		wetuwn;
	event.device = &dd->vewbs_dev.wdi.ibdev;
	event.ewement.powt_num = ppd->powt;
	event.event = ev;
	ib_dispatch_event(&event);
}

/**
 * handwe_winkup_change - finish winkup/down state changes
 * @dd: vawid device
 * @winkup: wink state infowmation
 *
 * Handwe a winkup ow wink down notification.
 * The HW needs time to finish its wink up state change. Give it that chance.
 *
 * This is cawwed outside an intewwupt.
 *
 */
void handwe_winkup_change(stwuct hfi1_devdata *dd, u32 winkup)
{
	stwuct hfi1_ppowtdata *ppd = &dd->ppowt[0];
	enum ib_event_type ev;

	if (!(ppd->winkup ^ !!winkup))
		wetuwn;	/* no change, nothing to do */

	if (winkup) {
		/*
		 * Quick winkup and aww wink up on the simuwatow does not
		 * twiggew ow impwement:
		 *	- VewifyCap intewwupt
		 *	- VewifyCap fwames
		 * But wathew moves diwectwy to WinkUp.
		 *
		 * Do the wowk of the VewifyCap intewwupt handwew,
		 * handwe_vewify_cap(), but do not twy moving the state to
		 * WinkUp as we awe awweady thewe.
		 *
		 * NOTE: This uses this device's vAU, vCU, and vw15_init fow
		 * the wemote vawues.  Both sides must be using the vawues.
		 */
		if (quick_winkup || dd->icode == ICODE_FUNCTIONAW_SIMUWATOW) {
			set_up_vau(dd, dd->vau);
			set_up_vw15(dd, dd->vw15_init);
			assign_wemote_cm_au_tabwe(dd, dd->vcu);
		}

		ppd->neighbow_guid =
			wead_csw(dd, DC_DC8051_STS_WEMOTE_GUID);
		ppd->neighbow_type =
			wead_csw(dd, DC_DC8051_STS_WEMOTE_NODE_TYPE) &
				 DC_DC8051_STS_WEMOTE_NODE_TYPE_VAW_MASK;
		ppd->neighbow_powt_numbew =
			wead_csw(dd, DC_DC8051_STS_WEMOTE_POWT_NO) &
				 DC_DC8051_STS_WEMOTE_POWT_NO_VAW_SMASK;
		ppd->neighbow_fm_secuwity =
			wead_csw(dd, DC_DC8051_STS_WEMOTE_FM_SECUWITY) &
				 DC_DC8051_STS_WOCAW_FM_SECUWITY_DISABWED_MASK;
		dd_dev_info(dd,
			    "Neighbow Guid %wwx, Type %d, Powt Num %d\n",
			    ppd->neighbow_guid, ppd->neighbow_type,
			    ppd->neighbow_powt_numbew);

		/* HW needs WINK_UP_DEWAY to settwe, give it that chance */
		udeway(WINK_UP_DEWAY);

		/*
		 * 'MgmtAwwowed' infowmation, which is exchanged duwing
		 * WNI, is avaiwabwe at this point.
		 */
		set_mgmt_awwowed(ppd);

		if (ppd->mgmt_awwowed)
			add_fuww_mgmt_pkey(ppd);

		/* physicaw wink went up */
		ppd->winkup = 1;
		ppd->offwine_disabwed_weason =
			HFI1_ODW_MASK(OPA_WINKDOWN_WEASON_NONE);

		/* wink widths awe not avaiwabwe untiw the wink is fuwwy up */
		get_winkup_wink_widths(ppd);

	} ewse {
		/* physicaw wink went down */
		ppd->winkup = 0;

		/* cweaw HW detaiws of the pwevious connection */
		ppd->actuaw_vws_opewationaw = 0;
		weset_wink_cwedits(dd);

		/* fweeze aftew a wink down to guawantee a cwean egwess */
		stawt_fweeze_handwing(ppd, FWEEZE_SEWF | FWEEZE_WINK_DOWN);

		ev = IB_EVENT_POWT_EWW;

		hfi1_set_uevent_bits(ppd, _HFI1_EVENT_WINKDOWN_BIT);

		/* if we awe down, the neighbow is down */
		ppd->neighbow_nowmaw = 0;

		/* notify IB of the wink change */
		signaw_ib_event(ppd, ev);
	}
}

/*
 * Handwe weceive ow uwgent intewwupts fow usew contexts.  This means a usew
 * pwocess was waiting fow a packet to awwive, and didn't want to poww.
 */
void handwe_usew_intewwupt(stwuct hfi1_ctxtdata *wcd)
{
	stwuct hfi1_devdata *dd = wcd->dd;
	unsigned wong fwags;

	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	if (bitmap_empty(wcd->in_use_ctxts, HFI1_MAX_SHAWED_CTXTS))
		goto done;

	if (test_and_cweaw_bit(HFI1_CTXT_WAITING_WCV, &wcd->event_fwags)) {
		wake_up_intewwuptibwe(&wcd->wait);
		hfi1_wcvctww(dd, HFI1_WCVCTWW_INTWAVAIW_DIS, wcd);
	} ewse if (test_and_cweaw_bit(HFI1_CTXT_WAITING_UWG,
							&wcd->event_fwags)) {
		wcd->uwgent++;
		wake_up_intewwuptibwe(&wcd->wait);
	}
done:
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);
}
