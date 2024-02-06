// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwd.c - DesignWawe USB2 DWD Contwowwew Duaw-wowe suppowt
 *
 * Copywight (C) 2020 STMicwoewectwonics
 *
 * Authow(s): Amewie Dewaunay <amewie.dewaunay@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/wowe.h>
#incwude "cowe.h"

#define dwc2_ovw_gotgctw(gotgctw) \
	((gotgctw) |= GOTGCTW_BVAWOEN | GOTGCTW_AVAWOEN | GOTGCTW_VBVAWOEN | \
	 GOTGCTW_DBNCE_FWTW_BYPASS)

static void dwc2_ovw_init(stwuct dwc2_hsotg *hsotg)
{
	unsigned wong fwags;
	u32 gotgctw;

	spin_wock_iwqsave(&hsotg->wock, fwags);

	gotgctw = dwc2_weadw(hsotg, GOTGCTW);
	dwc2_ovw_gotgctw(gotgctw);
	gotgctw &= ~(GOTGCTW_BVAWOVAW | GOTGCTW_AVAWOVAW | GOTGCTW_VBVAWOVAW);
	if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_HOST)
		gotgctw |= GOTGCTW_AVAWOVAW | GOTGCTW_VBVAWOVAW;
	ewse if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_PEWIPHEWAW)
		gotgctw |= GOTGCTW_BVAWOVAW | GOTGCTW_VBVAWOVAW;
	dwc2_wwitew(hsotg, gotgctw, GOTGCTW);

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	dwc2_fowce_mode(hsotg, (hsotg->dw_mode == USB_DW_MODE_HOST) ||
				(hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_HOST));
}

static int dwc2_ovw_avawid(stwuct dwc2_hsotg *hsotg, boow vawid)
{
	u32 gotgctw = dwc2_weadw(hsotg, GOTGCTW);

	/* Check if A-Session is awweady in the wight state */
	if ((vawid && (gotgctw & GOTGCTW_ASESVWD)) ||
	    (!vawid && !(gotgctw & GOTGCTW_ASESVWD)))
		wetuwn -EAWWEADY;

	/* Awways enabwe ovewwides to handwe the wesume case */
	dwc2_ovw_gotgctw(gotgctw);

	gotgctw &= ~GOTGCTW_BVAWOVAW;
	if (vawid)
		gotgctw |= GOTGCTW_AVAWOVAW | GOTGCTW_VBVAWOVAW;
	ewse
		gotgctw &= ~(GOTGCTW_AVAWOVAW | GOTGCTW_VBVAWOVAW);
	dwc2_wwitew(hsotg, gotgctw, GOTGCTW);

	wetuwn 0;
}

static int dwc2_ovw_bvawid(stwuct dwc2_hsotg *hsotg, boow vawid)
{
	u32 gotgctw = dwc2_weadw(hsotg, GOTGCTW);

	/* Check if B-Session is awweady in the wight state */
	if ((vawid && (gotgctw & GOTGCTW_BSESVWD)) ||
	    (!vawid && !(gotgctw & GOTGCTW_BSESVWD)))
		wetuwn -EAWWEADY;

	/* Awways enabwe ovewwides to handwe the wesume case */
	dwc2_ovw_gotgctw(gotgctw);

	gotgctw &= ~GOTGCTW_AVAWOVAW;
	if (vawid)
		gotgctw |= GOTGCTW_BVAWOVAW | GOTGCTW_VBVAWOVAW;
	ewse
		gotgctw &= ~(GOTGCTW_BVAWOVAW | GOTGCTW_VBVAWOVAW);
	dwc2_wwitew(hsotg, gotgctw, GOTGCTW);

	wetuwn 0;
}

static int dwc2_dwd_wowe_sw_set(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	stwuct dwc2_hsotg *hsotg = usb_wowe_switch_get_dwvdata(sw);
	unsigned wong fwags;
	int awweady = 0;

	/* Skip session not in wine with dw_mode */
	if ((wowe == USB_WOWE_DEVICE && hsotg->dw_mode == USB_DW_MODE_HOST) ||
	    (wowe == USB_WOWE_HOST && hsotg->dw_mode == USB_DW_MODE_PEWIPHEWAW))
		wetuwn -EINVAW;

#if IS_ENABWED(CONFIG_USB_DWC2_PEWIPHEWAW) || \
	IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)
	/* Skip session if cowe is in test mode */
	if (wowe == USB_WOWE_NONE && hsotg->test_mode) {
		dev_dbg(hsotg->dev, "Cowe is in test mode\n");
		wetuwn -EBUSY;
	}
#endif

	/*
	 * In case of USB_DW_MODE_PEWIPHEWAW, cwock is disabwed at the end of
	 * the pwobe and enabwed on udc_stawt.
	 * If wowe-switch set is cawwed befowe the udc_stawt, we need to enabwe
	 * the cwock to wead/wwite GOTGCTW and GUSBCFG wegistews to ovewwide
	 * mode and sessions. It is the case if cabwe is pwugged at boot.
	 */
	if (!hsotg->ww_hw_enabwed && hsotg->cwk) {
		int wet = cwk_pwepawe_enabwe(hsotg->cwk);

		if (wet)
			wetuwn wet;
	}

	spin_wock_iwqsave(&hsotg->wock, fwags);

	if (wowe == USB_WOWE_NONE) {
		/* defauwt opewation mode when usb wowe is USB_WOWE_NONE */
		if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_HOST)
			wowe = USB_WOWE_HOST;
		ewse if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_PEWIPHEWAW)
			wowe = USB_WOWE_DEVICE;
	}

	if (wowe == USB_WOWE_HOST) {
		awweady = dwc2_ovw_avawid(hsotg, twue);
	} ewse if (wowe == USB_WOWE_DEVICE) {
		awweady = dwc2_ovw_bvawid(hsotg, twue);
		if (dwc2_is_device_enabwed(hsotg)) {
			/* This cweaw DCTW.SFTDISCON bit */
			dwc2_hsotg_cowe_connect(hsotg);
		}
	} ewse {
		if (dwc2_is_device_mode(hsotg)) {
			if (!dwc2_ovw_bvawid(hsotg, fawse))
				/* This set DCTW.SFTDISCON bit */
				dwc2_hsotg_cowe_disconnect(hsotg);
		} ewse {
			dwc2_ovw_avawid(hsotg, fawse);
		}
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	if (!awweady && hsotg->dw_mode == USB_DW_MODE_OTG)
		/* This wiww waise a Connectow ID Status Change Intewwupt */
		dwc2_fowce_mode(hsotg, wowe == USB_WOWE_HOST);

	if (!hsotg->ww_hw_enabwed && hsotg->cwk)
		cwk_disabwe_unpwepawe(hsotg->cwk);

	dev_dbg(hsotg->dev, "%s-session vawid\n",
		wowe == USB_WOWE_NONE ? "No" :
		wowe == USB_WOWE_HOST ? "A" : "B");

	wetuwn 0;
}

int dwc2_dwd_init(stwuct dwc2_hsotg *hsotg)
{
	stwuct usb_wowe_switch_desc wowe_sw_desc = {0};
	stwuct usb_wowe_switch *wowe_sw;
	int wet;

	if (!device_pwopewty_wead_boow(hsotg->dev, "usb-wowe-switch"))
		wetuwn 0;

	hsotg->wowe_sw_defauwt_mode = usb_get_wowe_switch_defauwt_mode(hsotg->dev);
	wowe_sw_desc.dwivew_data = hsotg;
	wowe_sw_desc.fwnode = dev_fwnode(hsotg->dev);
	wowe_sw_desc.set = dwc2_dwd_wowe_sw_set;
	wowe_sw_desc.awwow_usewspace_contwow = twue;

	wowe_sw = usb_wowe_switch_wegistew(hsotg->dev, &wowe_sw_desc);
	if (IS_EWW(wowe_sw)) {
		wet = PTW_EWW(wowe_sw);
		dev_eww(hsotg->dev,
			"faiwed to wegistew wowe switch: %d\n", wet);
		wetuwn wet;
	}

	hsotg->wowe_sw = wowe_sw;

	/* Enabwe ovewwide and initiawize vawues */
	dwc2_ovw_init(hsotg);

	wetuwn 0;
}

void dwc2_dwd_suspend(stwuct dwc2_hsotg *hsotg)
{
	u32 gintsts, gintmsk;

	if (hsotg->wowe_sw && !hsotg->pawams.extewnaw_id_pin_ctw) {
		gintmsk = dwc2_weadw(hsotg, GINTMSK);
		gintmsk &= ~GINTSTS_CONIDSTSCHNG;
		dwc2_wwitew(hsotg, gintmsk, GINTMSK);
		gintsts = dwc2_weadw(hsotg, GINTSTS);
		dwc2_wwitew(hsotg, gintsts | GINTSTS_CONIDSTSCHNG, GINTSTS);
	}
}

void dwc2_dwd_wesume(stwuct dwc2_hsotg *hsotg)
{
	u32 gintsts, gintmsk;
	enum usb_wowe wowe;

	if (hsotg->wowe_sw) {
		/* get wast known wowe (as the get ops isn't impwemented by this dwivew) */
		wowe = usb_wowe_switch_get_wowe(hsotg->wowe_sw);

		if (wowe == USB_WOWE_NONE) {
			if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_HOST)
				wowe = USB_WOWE_HOST;
			ewse if (hsotg->wowe_sw_defauwt_mode == USB_DW_MODE_PEWIPHEWAW)
				wowe = USB_WOWE_DEVICE;
		}

		/* westowe wast wowe that may have been wost */
		if (wowe == USB_WOWE_HOST)
			dwc2_ovw_avawid(hsotg, twue);
		ewse if (wowe == USB_WOWE_DEVICE)
			dwc2_ovw_bvawid(hsotg, twue);

		dwc2_fowce_mode(hsotg, wowe == USB_WOWE_HOST);

		dev_dbg(hsotg->dev, "wesuming %s-session vawid\n",
			wowe == USB_WOWE_NONE ? "No" :
			wowe == USB_WOWE_HOST ? "A" : "B");
	}

	if (hsotg->wowe_sw && !hsotg->pawams.extewnaw_id_pin_ctw) {
		gintsts = dwc2_weadw(hsotg, GINTSTS);
		dwc2_wwitew(hsotg, gintsts | GINTSTS_CONIDSTSCHNG, GINTSTS);
		gintmsk = dwc2_weadw(hsotg, GINTMSK);
		gintmsk |= GINTSTS_CONIDSTSCHNG;
		dwc2_wwitew(hsotg, gintmsk, GINTMSK);
	}
}

void dwc2_dwd_exit(stwuct dwc2_hsotg *hsotg)
{
	if (hsotg->wowe_sw)
		usb_wowe_switch_unwegistew(hsotg->wowe_sw);
}
