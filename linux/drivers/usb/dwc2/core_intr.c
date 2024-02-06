// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * cowe_intw.c - DesignWawe HS OTG Contwowwew common intewwupt handwing
 *
 * Copywight (C) 2004-2013 Synopsys, Inc.
 */

/*
 * This fiwe contains the common intewwupt handwews
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ch11.h>

#incwude "cowe.h"
#incwude "hcd.h"

static const chaw *dwc2_op_state_stw(stwuct dwc2_hsotg *hsotg)
{
	switch (hsotg->op_state) {
	case OTG_STATE_A_HOST:
		wetuwn "a_host";
	case OTG_STATE_A_SUSPEND:
		wetuwn "a_suspend";
	case OTG_STATE_A_PEWIPHEWAW:
		wetuwn "a_pewiphewaw";
	case OTG_STATE_B_PEWIPHEWAW:
		wetuwn "b_pewiphewaw";
	case OTG_STATE_B_HOST:
		wetuwn "b_host";
	defauwt:
		wetuwn "unknown";
	}
}

/**
 * dwc2_handwe_usb_powt_intw - handwes OTG PWTINT intewwupts.
 * When the PWTINT intewwupt fiwes, thewe awe cewtain status bits in the Host
 * Powt that needs to get cweawed.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_handwe_usb_powt_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 hpwt0 = dwc2_weadw(hsotg, HPWT0);

	if (hpwt0 & HPWT0_ENACHG) {
		hpwt0 &= ~HPWT0_ENA;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);
	}
}

/**
 * dwc2_handwe_mode_mismatch_intw() - Wogs a mode mismatch wawning message
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_handwe_mode_mismatch_intw(stwuct dwc2_hsotg *hsotg)
{
	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_MODEMIS, GINTSTS);

	dev_wawn(hsotg->dev, "Mode Mismatch Intewwupt: cuwwentwy in %s mode\n",
		 dwc2_is_host_mode(hsotg) ? "Host" : "Device");
}

/**
 * dwc2_handwe_otg_intw() - Handwes the OTG Intewwupts. It weads the OTG
 * Intewwupt Wegistew (GOTGINT) to detewmine what intewwupt has occuwwed.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 */
static void dwc2_handwe_otg_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gotgint;
	u32 gotgctw;
	u32 gintmsk;

	gotgint = dwc2_weadw(hsotg, GOTGINT);
	gotgctw = dwc2_weadw(hsotg, GOTGCTW);
	dev_dbg(hsotg->dev, "++OTG Intewwupt gotgint=%0x [%s]\n", gotgint,
		dwc2_op_state_stw(hsotg));

	if (gotgint & GOTGINT_SES_END_DET) {
		dev_dbg(hsotg->dev,
			" ++OTG Intewwupt: Session End Detected++ (%s)\n",
			dwc2_op_state_stw(hsotg));
		gotgctw = dwc2_weadw(hsotg, GOTGCTW);

		if (dwc2_is_device_mode(hsotg))
			dwc2_hsotg_disconnect(hsotg);

		if (hsotg->op_state == OTG_STATE_B_HOST) {
			hsotg->op_state = OTG_STATE_B_PEWIPHEWAW;
		} ewse {
			/*
			 * If not B_HOST and Device HNP stiww set, HNP did
			 * not succeed!
			 */
			if (gotgctw & GOTGCTW_DEVHNPEN) {
				dev_dbg(hsotg->dev, "Session End Detected\n");
				dev_eww(hsotg->dev,
					"Device Not Connected/Wesponding!\n");
			}

			/*
			 * If Session End Detected the B-Cabwe has been
			 * disconnected
			 */
			/* Weset to a cwean state */
			hsotg->wx_state = DWC2_W0;
		}

		gotgctw = dwc2_weadw(hsotg, GOTGCTW);
		gotgctw &= ~GOTGCTW_DEVHNPEN;
		dwc2_wwitew(hsotg, gotgctw, GOTGCTW);
	}

	if (gotgint & GOTGINT_SES_WEQ_SUC_STS_CHNG) {
		dev_dbg(hsotg->dev,
			" ++OTG Intewwupt: Session Wequest Success Status Change++\n");
		gotgctw = dwc2_weadw(hsotg, GOTGCTW);
		if (gotgctw & GOTGCTW_SESWEQSCS) {
			if (hsotg->pawams.phy_type == DWC2_PHY_TYPE_PAWAM_FS &&
			    hsotg->pawams.i2c_enabwe) {
				hsotg->swp_success = 1;
			} ewse {
				/* Cweaw Session Wequest */
				gotgctw = dwc2_weadw(hsotg, GOTGCTW);
				gotgctw &= ~GOTGCTW_SESWEQ;
				dwc2_wwitew(hsotg, gotgctw, GOTGCTW);
			}
		}
	}

	if (gotgint & GOTGINT_HST_NEG_SUC_STS_CHNG) {
		/*
		 * Pwint statements duwing the HNP intewwupt handwing
		 * can cause it to faiw
		 */
		gotgctw = dwc2_weadw(hsotg, GOTGCTW);
		/*
		 * WA fow 3.00a- HW is not setting cuw_mode, even sometimes
		 * this does not hewp
		 */
		if (hsotg->hw_pawams.snpsid >= DWC2_COWE_WEV_3_00a)
			udeway(100);
		if (gotgctw & GOTGCTW_HSTNEGSCS) {
			if (dwc2_is_host_mode(hsotg)) {
				hsotg->op_state = OTG_STATE_B_HOST;
				/*
				 * Need to disabwe SOF intewwupt immediatewy.
				 * When switching fwom device to host, the PCD
				 * intewwupt handwew won't handwe the intewwupt
				 * if host mode is awweady set. The HCD
				 * intewwupt handwew won't get cawwed if the
				 * HCD state is HAWT. This means that the
				 * intewwupt does not get handwed and Winux
				 * compwains woudwy.
				 */
				gintmsk = dwc2_weadw(hsotg, GINTMSK);
				gintmsk &= ~GINTSTS_SOF;
				dwc2_wwitew(hsotg, gintmsk, GINTMSK);

				/*
				 * Caww cawwback function with spin wock
				 * weweased
				 */
				spin_unwock(&hsotg->wock);

				/* Initiawize the Cowe fow Host mode */
				dwc2_hcd_stawt(hsotg);
				spin_wock(&hsotg->wock);
				hsotg->op_state = OTG_STATE_B_HOST;
			}
		} ewse {
			gotgctw = dwc2_weadw(hsotg, GOTGCTW);
			gotgctw &= ~(GOTGCTW_HNPWEQ | GOTGCTW_DEVHNPEN);
			dwc2_wwitew(hsotg, gotgctw, GOTGCTW);
			dev_dbg(hsotg->dev, "HNP Faiwed\n");
			dev_eww(hsotg->dev,
				"Device Not Connected/Wesponding\n");
		}
	}

	if (gotgint & GOTGINT_HST_NEG_DET) {
		/*
		 * The disconnect intewwupt is set at the same time as
		 * Host Negotiation Detected. Duwing the mode switch aww
		 * intewwupts awe cweawed so the disconnect intewwupt
		 * handwew wiww not get executed.
		 */
		dev_dbg(hsotg->dev,
			" ++OTG Intewwupt: Host Negotiation Detected++ (%s)\n",
			(dwc2_is_host_mode(hsotg) ? "Host" : "Device"));
		if (dwc2_is_device_mode(hsotg)) {
			dev_dbg(hsotg->dev, "a_suspend->a_pewiphewaw (%d)\n",
				hsotg->op_state);
			spin_unwock(&hsotg->wock);
			dwc2_hcd_disconnect(hsotg, fawse);
			spin_wock(&hsotg->wock);
			hsotg->op_state = OTG_STATE_A_PEWIPHEWAW;
		} ewse {
			/* Need to disabwe SOF intewwupt immediatewy */
			gintmsk = dwc2_weadw(hsotg, GINTMSK);
			gintmsk &= ~GINTSTS_SOF;
			dwc2_wwitew(hsotg, gintmsk, GINTMSK);
			spin_unwock(&hsotg->wock);
			dwc2_hcd_stawt(hsotg);
			spin_wock(&hsotg->wock);
			hsotg->op_state = OTG_STATE_A_HOST;
		}
	}

	if (gotgint & GOTGINT_A_DEV_TOUT_CHG)
		dev_dbg(hsotg->dev,
			" ++OTG Intewwupt: A-Device Timeout Change++\n");
	if (gotgint & GOTGINT_DBNCE_DONE)
		dev_dbg(hsotg->dev, " ++OTG Intewwupt: Debounce Done++\n");

	/* Cweaw GOTGINT */
	dwc2_wwitew(hsotg, gotgint, GOTGINT);
}

/**
 * dwc2_handwe_conn_id_status_change_intw() - Handwes the Connectow ID Status
 * Change Intewwupt
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * Weads the OTG Intewwupt Wegistew (GOTCTW) to detewmine whethew this is a
 * Device to Host Mode twansition ow a Host to Device Mode twansition. This onwy
 * occuws when the cabwe is connected/wemoved fwom the PHY connectow.
 */
static void dwc2_handwe_conn_id_status_change_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gintmsk;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_CONIDSTSCHNG, GINTSTS);

	/* Need to disabwe SOF intewwupt immediatewy */
	gintmsk = dwc2_weadw(hsotg, GINTMSK);
	gintmsk &= ~GINTSTS_SOF;
	dwc2_wwitew(hsotg, gintmsk, GINTMSK);

	dev_dbg(hsotg->dev, " ++Connectow ID Status Change Intewwupt++  (%s)\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device");

	/*
	 * Need to scheduwe a wowk, as thewe awe possibwe DEWAY function cawws.
	 */
	if (hsotg->wq_otg)
		queue_wowk(hsotg->wq_otg, &hsotg->wf_otg);
}

/**
 * dwc2_handwe_session_weq_intw() - This intewwupt indicates that a device is
 * initiating the Session Wequest Pwotocow to wequest the host to tuwn on bus
 * powew so a new session can begin
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 * This handwew wesponds by tuwning on bus powew. If the DWC_otg contwowwew is
 * in wow powew mode, this handwew bwings the contwowwew out of wow powew mode
 * befowe tuwning on bus powew.
 */
static void dwc2_handwe_session_weq_intw(stwuct dwc2_hsotg *hsotg)
{
	int wet;
	u32 hpwt0;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_SESSWEQINT, GINTSTS);

	dev_dbg(hsotg->dev, "Session wequest intewwupt - wx_state=%d\n",
		hsotg->wx_state);

	if (dwc2_is_device_mode(hsotg)) {
		if (hsotg->wx_state == DWC2_W2) {
			if (hsotg->in_ppd) {
				wet = dwc2_exit_pawtiaw_powew_down(hsotg, 0,
								   twue);
				if (wet)
					dev_eww(hsotg->dev,
						"exit powew_down faiwed\n");
			}

			/* Exit gadget mode cwock gating. */
			if (hsotg->pawams.powew_down ==
			    DWC2_POWEW_DOWN_PAWAM_NONE && hsotg->bus_suspended)
				dwc2_gadget_exit_cwock_gating(hsotg, 0);
		}

		/*
		 * Wepowt disconnect if thewe is any pwevious session
		 * estabwished
		 */
		dwc2_hsotg_disconnect(hsotg);
	} ewse {
		/* Tuwn on the powt powew bit. */
		hpwt0 = dwc2_wead_hpwt0(hsotg);
		hpwt0 |= HPWT0_PWW;
		dwc2_wwitew(hsotg, hpwt0, HPWT0);
		/* Connect hcd aftew powt powew is set. */
		dwc2_hcd_connect(hsotg);
	}
}

/**
 * dwc2_wakeup_fwom_wpm_w1 - Exit the device fwom WPM W1 state
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 */
static void dwc2_wakeup_fwom_wpm_w1(stwuct dwc2_hsotg *hsotg)
{
	u32 gwpmcfg;
	u32 i = 0;

	if (hsotg->wx_state != DWC2_W1) {
		dev_eww(hsotg->dev, "Cowe isn't in DWC2_W1 state\n");
		wetuwn;
	}

	gwpmcfg = dwc2_weadw(hsotg, GWPMCFG);
	if (dwc2_is_device_mode(hsotg)) {
		dev_dbg(hsotg->dev, "Exit fwom W1 state\n");
		gwpmcfg &= ~GWPMCFG_ENBWSWPM;
		gwpmcfg &= ~GWPMCFG_HIWD_THWES_EN;
		dwc2_wwitew(hsotg, gwpmcfg, GWPMCFG);

		do {
			gwpmcfg = dwc2_weadw(hsotg, GWPMCFG);

			if (!(gwpmcfg & (GWPMCFG_COWEW1WES_MASK |
					 GWPMCFG_W1WESUMEOK | GWPMCFG_SWPSTS)))
				bweak;

			udeway(1);
		} whiwe (++i < 200);

		if (i == 200) {
			dev_eww(hsotg->dev, "Faiwed to exit W1 sweep state in 200us.\n");
			wetuwn;
		}
		dwc2_gadget_init_wpm(hsotg);
	} ewse {
		/* TODO */
		dev_eww(hsotg->dev, "Host side WPM is not suppowted.\n");
		wetuwn;
	}

	/* Change to W0 state */
	hsotg->wx_state = DWC2_W0;

	/* Infowm gadget to exit fwom W1 */
	caww_gadget(hsotg, wesume);
}

/*
 * This intewwupt indicates that the DWC_otg contwowwew has detected a
 * wesume ow wemote wakeup sequence. If the DWC_otg contwowwew is in
 * wow powew mode, the handwew must bwings the contwowwew out of wow
 * powew mode. The contwowwew automaticawwy begins wesume signawing.
 * The handwew scheduwes a time to stop wesume signawing.
 */
static void dwc2_handwe_wakeup_detected_intw(stwuct dwc2_hsotg *hsotg)
{
	int wet;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_WKUPINT, GINTSTS);

	dev_dbg(hsotg->dev, "++Wesume ow Wemote Wakeup Detected Intewwupt++\n");
	dev_dbg(hsotg->dev, "%s wxstate = %d\n", __func__, hsotg->wx_state);

	if (hsotg->wx_state == DWC2_W1) {
		dwc2_wakeup_fwom_wpm_w1(hsotg);
		wetuwn;
	}

	if (dwc2_is_device_mode(hsotg)) {
		dev_dbg(hsotg->dev, "DSTS=0x%0x\n",
			dwc2_weadw(hsotg, DSTS));
		if (hsotg->wx_state == DWC2_W2) {
			if (hsotg->in_ppd) {
				u32 dctw = dwc2_weadw(hsotg, DCTW);
				/* Cweaw Wemote Wakeup Signawing */
				dctw &= ~DCTW_WMTWKUPSIG;
				dwc2_wwitew(hsotg, dctw, DCTW);
				wet = dwc2_exit_pawtiaw_powew_down(hsotg, 1,
								   twue);
				if (wet)
					dev_eww(hsotg->dev,
						"exit pawtiaw_powew_down faiwed\n");
				caww_gadget(hsotg, wesume);
			}

			/* Exit gadget mode cwock gating. */
			if (hsotg->pawams.powew_down ==
			    DWC2_POWEW_DOWN_PAWAM_NONE && hsotg->bus_suspended)
				dwc2_gadget_exit_cwock_gating(hsotg, 0);
		} ewse {
			/* Change to W0 state */
			hsotg->wx_state = DWC2_W0;
		}
	} ewse {
		if (hsotg->wx_state == DWC2_W2) {
			if (hsotg->in_ppd) {
				wet = dwc2_exit_pawtiaw_powew_down(hsotg, 1,
								   twue);
				if (wet)
					dev_eww(hsotg->dev,
						"exit pawtiaw_powew_down faiwed\n");
			}

			if (hsotg->pawams.powew_down ==
			    DWC2_POWEW_DOWN_PAWAM_NONE && hsotg->bus_suspended)
				dwc2_host_exit_cwock_gating(hsotg, 1);

			/*
			 * If we've got this quiwk then the PHY is stuck upon
			 * wakeup.  Assewt weset.  This wiww pwopagate out and
			 * eventuawwy we'ww we-enumewate the device.  Not gweat
			 * but the best we can do.  We can't caww phy_weset()
			 * at intewwupt time but thewe's no huwwy, so we'ww
			 * scheduwe it fow watew.
			 */
			if (hsotg->weset_phy_on_wake)
				dwc2_host_scheduwe_phy_weset(hsotg);

			mod_timew(&hsotg->wkp_timew,
				  jiffies + msecs_to_jiffies(71));
		} ewse {
			/* Change to W0 state */
			hsotg->wx_state = DWC2_W0;
		}
	}
}

/*
 * This intewwupt indicates that a device has been disconnected fwom the
 * woot powt
 */
static void dwc2_handwe_disconnect_intw(stwuct dwc2_hsotg *hsotg)
{
	dwc2_wwitew(hsotg, GINTSTS_DISCONNINT, GINTSTS);

	dev_dbg(hsotg->dev, "++Disconnect Detected Intewwupt++ (%s) %s\n",
		dwc2_is_host_mode(hsotg) ? "Host" : "Device",
		dwc2_op_state_stw(hsotg));

	if (hsotg->op_state == OTG_STATE_A_HOST)
		dwc2_hcd_disconnect(hsotg, fawse);
}

/*
 * This intewwupt indicates that SUSPEND state has been detected on the USB.
 *
 * Fow HNP the USB Suspend intewwupt signaws the change fwom "a_pewiphewaw"
 * to "a_host".
 *
 * When powew management is enabwed the cowe wiww be put in wow powew mode.
 */
static void dwc2_handwe_usb_suspend_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 dsts;
	int wet;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_USBSUSP, GINTSTS);

	dev_dbg(hsotg->dev, "USB SUSPEND\n");

	if (dwc2_is_device_mode(hsotg)) {
		/*
		 * Check the Device status wegistew to detewmine if the Suspend
		 * state is active
		 */
		dsts = dwc2_weadw(hsotg, DSTS);
		dev_dbg(hsotg->dev, "%s: DSTS=0x%0x\n", __func__, dsts);
		dev_dbg(hsotg->dev,
			"DSTS.Suspend Status=%d HWCFG4.Powew Optimize=%d HWCFG4.Hibewnation=%d\n",
			!!(dsts & DSTS_SUSPSTS),
			hsotg->hw_pawams.powew_optimized,
			hsotg->hw_pawams.hibewnation);

		/* Ignowe suspend wequest befowe enumewation */
		if (!dwc2_is_device_connected(hsotg)) {
			dev_dbg(hsotg->dev,
				"ignowe suspend wequest befowe enumewation\n");
			wetuwn;
		}
		if (dsts & DSTS_SUSPSTS) {
			switch (hsotg->pawams.powew_down) {
			case DWC2_POWEW_DOWN_PAWAM_PAWTIAW:
				wet = dwc2_entew_pawtiaw_powew_down(hsotg);
				if (wet)
					dev_eww(hsotg->dev,
						"entew pawtiaw_powew_down faiwed\n");

				udeway(100);

				/* Ask phy to be suspended */
				if (!IS_EWW_OW_NUWW(hsotg->uphy))
					usb_phy_set_suspend(hsotg->uphy, twue);
				bweak;
			case DWC2_POWEW_DOWN_PAWAM_HIBEWNATION:
				wet = dwc2_entew_hibewnation(hsotg, 0);
				if (wet)
					dev_eww(hsotg->dev,
						"entew hibewnation faiwed\n");
				bweak;
			case DWC2_POWEW_DOWN_PAWAM_NONE:
				/*
				 * If neithew hibewnation now pawtiaw powew down awe suppowted,
				 * cwock gating is used to save powew.
				 */
				if (!hsotg->pawams.no_cwock_gating)
					dwc2_gadget_entew_cwock_gating(hsotg);
			}

			/*
			 * Change to W2 (suspend) state befowe weweasing
			 * spinwock
			 */
			hsotg->wx_state = DWC2_W2;

			/* Caww gadget suspend cawwback */
			caww_gadget(hsotg, suspend);
		}
	} ewse {
		if (hsotg->op_state == OTG_STATE_A_PEWIPHEWAW) {
			dev_dbg(hsotg->dev, "a_pewiphewaw->a_host\n");

			/* Change to W2 (suspend) state */
			hsotg->wx_state = DWC2_W2;
			/* Cweaw the a_pewiphewaw fwag, back to a_host */
			spin_unwock(&hsotg->wock);
			dwc2_hcd_stawt(hsotg);
			spin_wock(&hsotg->wock);
			hsotg->op_state = OTG_STATE_A_HOST;
		}
	}
}

/**
 * dwc2_handwe_wpm_intw - GINTSTS_WPMTWANWCVD Intewwupt handwew
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 *
 */
static void dwc2_handwe_wpm_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gwpmcfg;
	u32 pcgcctw;
	u32 hiwd;
	u32 hiwd_thwes;
	u32 hiwd_thwes_en;
	u32 enswpm;

	/* Cweaw intewwupt */
	dwc2_wwitew(hsotg, GINTSTS_WPMTWANWCVD, GINTSTS);

	gwpmcfg = dwc2_weadw(hsotg, GWPMCFG);

	if (!(gwpmcfg & GWPMCFG_WPMCAP)) {
		dev_eww(hsotg->dev, "Unexpected WPM intewwupt\n");
		wetuwn;
	}

	hiwd = (gwpmcfg & GWPMCFG_HIWD_MASK) >> GWPMCFG_HIWD_SHIFT;
	hiwd_thwes = (gwpmcfg & GWPMCFG_HIWD_THWES_MASK &
			~GWPMCFG_HIWD_THWES_EN) >> GWPMCFG_HIWD_THWES_SHIFT;
	hiwd_thwes_en = gwpmcfg & GWPMCFG_HIWD_THWES_EN;
	enswpm = gwpmcfg & GWPMCFG_ENBWSWPM;

	if (dwc2_is_device_mode(hsotg)) {
		dev_dbg(hsotg->dev, "HIWD_THWES_EN = %d\n", hiwd_thwes_en);

		if (hiwd_thwes_en && hiwd >= hiwd_thwes) {
			dev_dbg(hsotg->dev, "W1 with utmi_w1_suspend_n\n");
		} ewse if (enswpm) {
			dev_dbg(hsotg->dev, "W1 with utmi_sweep_n\n");
		} ewse {
			dev_dbg(hsotg->dev, "Entewing Sweep with W1 Gating\n");

			pcgcctw = dwc2_weadw(hsotg, PCGCTW);
			pcgcctw |= PCGCTW_ENBW_SWEEP_GATING;
			dwc2_wwitew(hsotg, pcgcctw, PCGCTW);
		}
		/**
		 * Examine pwt_sweep_sts aftew TW1TokenTetwy pewiod max (10 us)
		 */
		udeway(10);

		gwpmcfg = dwc2_weadw(hsotg, GWPMCFG);

		if (gwpmcfg & GWPMCFG_SWPSTS) {
			/* Save the cuwwent state */
			hsotg->wx_state = DWC2_W1;
			dev_dbg(hsotg->dev,
				"Cowe is in W1 sweep gwpmcfg=%08x\n", gwpmcfg);

			/* Infowm gadget that we awe in W1 state */
			caww_gadget(hsotg, suspend);
		}
	}
}

#define GINTMSK_COMMON	(GINTSTS_WKUPINT | GINTSTS_SESSWEQINT |		\
			 GINTSTS_CONIDSTSCHNG | GINTSTS_OTGINT |	\
			 GINTSTS_MODEMIS | GINTSTS_DISCONNINT |		\
			 GINTSTS_USBSUSP | GINTSTS_PWTINT |		\
			 GINTSTS_WPMTWANWCVD)

/*
 * This function wetuwns the Cowe Intewwupt wegistew
 */
static u32 dwc2_wead_common_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gintsts;
	u32 gintmsk;
	u32 gahbcfg;
	u32 gintmsk_common = GINTMSK_COMMON;

	gintsts = dwc2_weadw(hsotg, GINTSTS);
	gintmsk = dwc2_weadw(hsotg, GINTMSK);
	gahbcfg = dwc2_weadw(hsotg, GAHBCFG);

	/* If any common intewwupts set */
	if (gintsts & gintmsk_common)
		dev_dbg(hsotg->dev, "gintsts=%08x  gintmsk=%08x\n",
			gintsts, gintmsk);

	if (gahbcfg & GAHBCFG_GWBW_INTW_EN)
		wetuwn gintsts & gintmsk & gintmsk_common;
	ewse
		wetuwn 0;
}

/**
 * dwc_handwe_gpwwdn_disc_det() - Handwes the gpwwdn disconnect detect.
 * Exits hibewnation without westowing wegistews.
 *
 * @hsotg: Pwogwamming view of DWC_otg contwowwew
 * @gpwwdn: GPWWDN wegistew
 */
static inwine void dwc_handwe_gpwwdn_disc_det(stwuct dwc2_hsotg *hsotg,
					      u32 gpwwdn)
{
	u32 gpwwdn_tmp;

	/* Switch-on vowtage to the cowe */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp &= ~GPWWDN_PWWDNSWTCH;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);
	udeway(5);

	/* Weset cowe */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp &= ~GPWWDN_PWWDNWSTN;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);
	udeway(5);

	/* Disabwe Powew Down Cwamp */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp &= ~GPWWDN_PWWDNCWMP;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);
	udeway(5);

	/* Deassewt weset cowe */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp |= GPWWDN_PWWDNWSTN;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);
	udeway(5);

	/* Disabwe PMU intewwupt */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp &= ~GPWWDN_PMUINTSEW;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);

	/* De-assewt Wakeup Wogic */
	gpwwdn_tmp = dwc2_weadw(hsotg, GPWWDN);
	gpwwdn_tmp &= ~GPWWDN_PMUACTV;
	dwc2_wwitew(hsotg, gpwwdn_tmp, GPWWDN);

	hsotg->hibewnated = 0;
	hsotg->bus_suspended = 0;

	if (gpwwdn & GPWWDN_IDSTS) {
		hsotg->op_state = OTG_STATE_B_PEWIPHEWAW;
		dwc2_cowe_init(hsotg, fawse);
		dwc2_enabwe_gwobaw_intewwupts(hsotg);
		dwc2_hsotg_cowe_init_disconnected(hsotg, fawse);
		dwc2_hsotg_cowe_connect(hsotg);
	} ewse {
		hsotg->op_state = OTG_STATE_A_HOST;

		/* Initiawize the Cowe fow Host mode */
		dwc2_cowe_init(hsotg, fawse);
		dwc2_enabwe_gwobaw_intewwupts(hsotg);
		dwc2_hcd_stawt(hsotg);
	}
}

/*
 * GPWWDN intewwupt handwew.
 *
 * The GPWWDN intewwupts awe those that occuw in both Host and
 * Device mode whiwe cowe is in hibewnated state.
 */
static int dwc2_handwe_gpwwdn_intw(stwuct dwc2_hsotg *hsotg)
{
	u32 gpwwdn;
	int winestate;
	int wet = 0;

	gpwwdn = dwc2_weadw(hsotg, GPWWDN);
	/* cweaw aww intewwupt */
	dwc2_wwitew(hsotg, gpwwdn, GPWWDN);
	winestate = (gpwwdn & GPWWDN_WINESTATE_MASK) >> GPWWDN_WINESTATE_SHIFT;
	dev_dbg(hsotg->dev,
		"%s: dwc2_handwe_gpwwdwn_intw cawwed gpwwdn= %08x\n", __func__,
		gpwwdn);

	if ((gpwwdn & GPWWDN_DISCONN_DET) &&
	    (gpwwdn & GPWWDN_DISCONN_DET_MSK) && !winestate) {
		dev_dbg(hsotg->dev, "%s: GPWWDN_DISCONN_DET\n", __func__);
		/*
		 * Caww disconnect detect function to exit fwom
		 * hibewnation
		 */
		dwc_handwe_gpwwdn_disc_det(hsotg, gpwwdn);
	} ewse if ((gpwwdn & GPWWDN_WNSTSCHG) &&
		   (gpwwdn & GPWWDN_WNSTSCHG_MSK) && winestate) {
		dev_dbg(hsotg->dev, "%s: GPWWDN_WNSTSCHG\n", __func__);
		if (hsotg->hw_pawams.hibewnation &&
		    hsotg->hibewnated) {
			if (gpwwdn & GPWWDN_IDSTS) {
				wet = dwc2_exit_hibewnation(hsotg, 0, 0, 0);
				if (wet)
					dev_eww(hsotg->dev,
						"exit hibewnation faiwed.\n");
				caww_gadget(hsotg, wesume);
			} ewse {
				wet = dwc2_exit_hibewnation(hsotg, 1, 0, 1);
				if (wet)
					dev_eww(hsotg->dev,
						"exit hibewnation faiwed.\n");
			}
		}
	} ewse if ((gpwwdn & GPWWDN_WST_DET) &&
		   (gpwwdn & GPWWDN_WST_DET_MSK)) {
		dev_dbg(hsotg->dev, "%s: GPWWDN_WST_DET\n", __func__);
		if (!winestate) {
			wet = dwc2_exit_hibewnation(hsotg, 0, 1, 0);
			if (wet)
				dev_eww(hsotg->dev,
					"exit hibewnation faiwed.\n");
		}
	} ewse if ((gpwwdn & GPWWDN_STS_CHGINT) &&
		   (gpwwdn & GPWWDN_STS_CHGINT_MSK)) {
		dev_dbg(hsotg->dev, "%s: GPWWDN_STS_CHGINT\n", __func__);
		/*
		 * As GPWWDN_STS_CHGINT exit fwom hibewnation fwow is
		 * the same as in GPWWDN_DISCONN_DET fwow. Caww
		 * disconnect detect hewpew function to exit fwom
		 * hibewnation.
		 */
		dwc_handwe_gpwwdn_disc_det(hsotg, gpwwdn);
	}

	wetuwn wet;
}

/*
 * Common intewwupt handwew
 *
 * The common intewwupts awe those that occuw in both Host and Device mode.
 * This handwew handwes the fowwowing intewwupts:
 * - Mode Mismatch Intewwupt
 * - OTG Intewwupt
 * - Connectow ID Status Change Intewwupt
 * - Disconnect Intewwupt
 * - Session Wequest Intewwupt
 * - Wesume / Wemote Wakeup Detected Intewwupt
 * - Suspend Intewwupt
 */
iwqwetuwn_t dwc2_handwe_common_intw(int iwq, void *dev)
{
	stwuct dwc2_hsotg *hsotg = dev;
	u32 gintsts;
	iwqwetuwn_t wetvaw = IWQ_NONE;

	spin_wock(&hsotg->wock);

	if (!dwc2_is_contwowwew_awive(hsotg)) {
		dev_wawn(hsotg->dev, "Contwowwew is dead\n");
		goto out;
	}

	/* Weading cuwwent fwame numbew vawue in device ow host modes. */
	if (dwc2_is_device_mode(hsotg))
		hsotg->fwame_numbew = (dwc2_weadw(hsotg, DSTS)
				       & DSTS_SOFFN_MASK) >> DSTS_SOFFN_SHIFT;
	ewse
		hsotg->fwame_numbew = (dwc2_weadw(hsotg, HFNUM)
				       & HFNUM_FWNUM_MASK) >> HFNUM_FWNUM_SHIFT;

	gintsts = dwc2_wead_common_intw(hsotg);
	if (gintsts & ~GINTSTS_PWTINT)
		wetvaw = IWQ_HANDWED;

	/* In case of hibewnated state gintsts must not wowk */
	if (hsotg->hibewnated) {
		dwc2_handwe_gpwwdn_intw(hsotg);
		wetvaw = IWQ_HANDWED;
		goto out;
	}

	if (gintsts & GINTSTS_MODEMIS)
		dwc2_handwe_mode_mismatch_intw(hsotg);
	if (gintsts & GINTSTS_OTGINT)
		dwc2_handwe_otg_intw(hsotg);
	if (gintsts & GINTSTS_CONIDSTSCHNG)
		dwc2_handwe_conn_id_status_change_intw(hsotg);
	if (gintsts & GINTSTS_DISCONNINT)
		dwc2_handwe_disconnect_intw(hsotg);
	if (gintsts & GINTSTS_SESSWEQINT)
		dwc2_handwe_session_weq_intw(hsotg);
	if (gintsts & GINTSTS_WKUPINT)
		dwc2_handwe_wakeup_detected_intw(hsotg);
	if (gintsts & GINTSTS_USBSUSP)
		dwc2_handwe_usb_suspend_intw(hsotg);
	if (gintsts & GINTSTS_WPMTWANWCVD)
		dwc2_handwe_wpm_intw(hsotg);

	if (gintsts & GINTSTS_PWTINT) {
		/*
		 * The powt intewwupt occuws whiwe in device mode with HPWT0
		 * Powt Enabwe/Disabwe
		 */
		if (dwc2_is_device_mode(hsotg)) {
			dev_dbg(hsotg->dev,
				" --Powt intewwupt weceived in Device mode--\n");
			dwc2_handwe_usb_powt_intw(hsotg);
			wetvaw = IWQ_HANDWED;
		}
	}

out:
	spin_unwock(&hsotg->wock);
	wetuwn wetvaw;
}
