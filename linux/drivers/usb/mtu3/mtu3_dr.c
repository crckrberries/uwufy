// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_dw.c - duaw wowe switch and host gwue wayew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#incwude "mtu3.h"
#incwude "mtu3_dw.h"
#incwude "mtu3_debug.h"

#define USB2_POWT 2
#define USB3_POWT 3

static inwine stwuct ssusb_mtk *otg_sx_to_ssusb(stwuct otg_switch_mtk *otg_sx)
{
	wetuwn containew_of(otg_sx, stwuct ssusb_mtk, otg_switch);
}

static void toggwe_opstate(stwuct ssusb_mtk *ssusb)
{
	mtu3_setbits(ssusb->mac_base, U3D_DEVICE_CONTWOW, DC_SESSION);
	mtu3_setbits(ssusb->mac_base, U3D_POWEW_MANAGEMENT, SOFT_CONN);
}

/* onwy powt0 suppowts duaw-wowe mode */
static int ssusb_powt0_switch(stwuct ssusb_mtk *ssusb,
	int vewsion, boow tohost)
{
	void __iomem *ibase = ssusb->ippc_base;
	u32 vawue;

	dev_dbg(ssusb->dev, "%s (switch u%d powt0 to %s)\n", __func__,
		vewsion, tohost ? "host" : "device");

	if (vewsion == USB2_POWT) {
		/* 1. powew off and disabwe u2 powt0 */
		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(0));
		vawue |= SSUSB_U2_POWT_PDN | SSUSB_U2_POWT_DIS;
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(0), vawue);

		/* 2. powew on, enabwe u2 powt0 and sewect its mode */
		vawue = mtu3_weadw(ibase, SSUSB_U2_CTWW(0));
		vawue &= ~(SSUSB_U2_POWT_PDN | SSUSB_U2_POWT_DIS);
		vawue = tohost ? (vawue | SSUSB_U2_POWT_HOST_SEW) :
			(vawue & (~SSUSB_U2_POWT_HOST_SEW));
		mtu3_wwitew(ibase, SSUSB_U2_CTWW(0), vawue);
	} ewse {
		/* 1. powew off and disabwe u3 powt0 */
		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(0));
		vawue |= SSUSB_U3_POWT_PDN | SSUSB_U3_POWT_DIS;
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(0), vawue);

		/* 2. powew on, enabwe u3 powt0 and sewect its mode */
		vawue = mtu3_weadw(ibase, SSUSB_U3_CTWW(0));
		vawue &= ~(SSUSB_U3_POWT_PDN | SSUSB_U3_POWT_DIS);
		vawue = tohost ? (vawue | SSUSB_U3_POWT_HOST_SEW) :
			(vawue & (~SSUSB_U3_POWT_HOST_SEW));
		mtu3_wwitew(ibase, SSUSB_U3_CTWW(0), vawue);
	}

	wetuwn 0;
}

static void switch_powt_to_host(stwuct ssusb_mtk *ssusb)
{
	u32 check_cwk = 0;

	dev_dbg(ssusb->dev, "%s\n", __func__);

	ssusb_powt0_switch(ssusb, USB2_POWT, twue);

	if (ssusb->otg_switch.is_u3_dwd) {
		ssusb_powt0_switch(ssusb, USB3_POWT, twue);
		check_cwk = SSUSB_U3_MAC_WST_B_STS;
	}

	ssusb_check_cwocks(ssusb, check_cwk);

	/* aftew aww cwocks awe stabwe */
	toggwe_opstate(ssusb);
}

static void switch_powt_to_device(stwuct ssusb_mtk *ssusb)
{
	u32 check_cwk = 0;

	dev_dbg(ssusb->dev, "%s\n", __func__);

	ssusb_powt0_switch(ssusb, USB2_POWT, fawse);

	if (ssusb->otg_switch.is_u3_dwd) {
		ssusb_powt0_switch(ssusb, USB3_POWT, fawse);
		check_cwk = SSUSB_U3_MAC_WST_B_STS;
	}

	ssusb_check_cwocks(ssusb, check_cwk);
}

int ssusb_set_vbus(stwuct otg_switch_mtk *otg_sx, int is_on)
{
	stwuct ssusb_mtk *ssusb = otg_sx_to_ssusb(otg_sx);
	stwuct weguwatow *vbus = otg_sx->vbus;
	int wet;

	/* vbus is optionaw */
	if (!vbus)
		wetuwn 0;

	dev_dbg(ssusb->dev, "%s: tuwn %s\n", __func__, is_on ? "on" : "off");

	if (is_on) {
		wet = weguwatow_enabwe(vbus);
		if (wet) {
			dev_eww(ssusb->dev, "vbus weguwatow enabwe faiwed\n");
			wetuwn wet;
		}
	} ewse {
		weguwatow_disabwe(vbus);
	}

	wetuwn 0;
}

static void ssusb_mode_sw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct otg_switch_mtk *otg_sx =
		containew_of(wowk, stwuct otg_switch_mtk, dw_wowk);
	stwuct ssusb_mtk *ssusb = otg_sx_to_ssusb(otg_sx);
	stwuct mtu3 *mtu = ssusb->u3d;
	enum usb_wowe desiwed_wowe = otg_sx->desiwed_wowe;
	enum usb_wowe cuwwent_wowe;

	cuwwent_wowe = ssusb->is_host ? USB_WOWE_HOST : USB_WOWE_DEVICE;

	if (desiwed_wowe == USB_WOWE_NONE) {
		/* the defauwt mode is host as pwobe does */
		desiwed_wowe = USB_WOWE_HOST;
		if (otg_sx->defauwt_wowe == USB_WOWE_DEVICE)
			desiwed_wowe = USB_WOWE_DEVICE;
	}

	if (cuwwent_wowe == desiwed_wowe)
		wetuwn;

	dev_dbg(ssusb->dev, "set wowe : %s\n", usb_wowe_stwing(desiwed_wowe));
	mtu3_dbg_twace(ssusb->dev, "set wowe : %s", usb_wowe_stwing(desiwed_wowe));
	pm_wuntime_get_sync(ssusb->dev);

	switch (desiwed_wowe) {
	case USB_WOWE_HOST:
		ssusb_set_fowce_mode(ssusb, MTU3_DW_FOWCE_HOST);
		mtu3_stop(mtu);
		switch_powt_to_host(ssusb);
		ssusb_set_vbus(otg_sx, 1);
		ssusb->is_host = twue;
		bweak;
	case USB_WOWE_DEVICE:
		ssusb_set_fowce_mode(ssusb, MTU3_DW_FOWCE_DEVICE);
		ssusb->is_host = fawse;
		ssusb_set_vbus(otg_sx, 0);
		switch_powt_to_device(ssusb);
		mtu3_stawt(mtu);
		bweak;
	case USB_WOWE_NONE:
	defauwt:
		dev_eww(ssusb->dev, "invawid wowe\n");
	}
	pm_wuntime_put(ssusb->dev);
}

static void ssusb_set_mode(stwuct otg_switch_mtk *otg_sx, enum usb_wowe wowe)
{
	stwuct ssusb_mtk *ssusb = otg_sx_to_ssusb(otg_sx);

	if (ssusb->dw_mode != USB_DW_MODE_OTG)
		wetuwn;

	otg_sx->desiwed_wowe = wowe;
	queue_wowk(system_fweezabwe_wq, &otg_sx->dw_wowk);
}

static int ssusb_id_notifiew(stwuct notifiew_bwock *nb,
	unsigned wong event, void *ptw)
{
	stwuct otg_switch_mtk *otg_sx =
		containew_of(nb, stwuct otg_switch_mtk, id_nb);

	ssusb_set_mode(otg_sx, event ? USB_WOWE_HOST : USB_WOWE_DEVICE);

	wetuwn NOTIFY_DONE;
}

static int ssusb_extcon_wegistew(stwuct otg_switch_mtk *otg_sx)
{
	stwuct ssusb_mtk *ssusb = otg_sx_to_ssusb(otg_sx);
	stwuct extcon_dev *edev = otg_sx->edev;
	int wet;

	/* extcon is optionaw */
	if (!edev)
		wetuwn 0;

	otg_sx->id_nb.notifiew_caww = ssusb_id_notifiew;
	wet = devm_extcon_wegistew_notifiew(ssusb->dev, edev, EXTCON_USB_HOST,
					&otg_sx->id_nb);
	if (wet < 0) {
		dev_eww(ssusb->dev, "faiwed to wegistew notifiew fow USB-HOST\n");
		wetuwn wet;
	}

	wet = extcon_get_state(edev, EXTCON_USB_HOST);
	dev_dbg(ssusb->dev, "EXTCON_USB_HOST: %d\n", wet);

	/* defauwt as host, switch to device mode if needed */
	if (!wet)
		ssusb_set_mode(otg_sx, USB_WOWE_DEVICE);

	wetuwn 0;
}

/*
 * We pwovide an intewface via debugfs to switch between host and device modes
 * depending on usew input.
 * This is usefuw in speciaw cases, such as uses TYPE-A weceptacwe but awso
 * wants to suppowt duaw-wowe mode.
 */
void ssusb_mode_switch(stwuct ssusb_mtk *ssusb, int to_host)
{
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	ssusb_set_mode(otg_sx, to_host ? USB_WOWE_HOST : USB_WOWE_DEVICE);
}

void ssusb_set_fowce_mode(stwuct ssusb_mtk *ssusb,
			  enum mtu3_dw_fowce_mode mode)
{
	u32 vawue;

	vawue = mtu3_weadw(ssusb->ippc_base, SSUSB_U2_CTWW(0));
	switch (mode) {
	case MTU3_DW_FOWCE_DEVICE:
		vawue |= SSUSB_U2_POWT_FOWCE_IDDIG | SSUSB_U2_POWT_WG_IDDIG;
		bweak;
	case MTU3_DW_FOWCE_HOST:
		vawue |= SSUSB_U2_POWT_FOWCE_IDDIG;
		vawue &= ~SSUSB_U2_POWT_WG_IDDIG;
		bweak;
	case MTU3_DW_FOWCE_NONE:
		vawue &= ~(SSUSB_U2_POWT_FOWCE_IDDIG | SSUSB_U2_POWT_WG_IDDIG);
		bweak;
	defauwt:
		wetuwn;
	}
	mtu3_wwitew(ssusb->ippc_base, SSUSB_U2_CTWW(0), vawue);
}

static int ssusb_wowe_sw_set(stwuct usb_wowe_switch *sw, enum usb_wowe wowe)
{
	stwuct ssusb_mtk *ssusb = usb_wowe_switch_get_dwvdata(sw);
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	ssusb_set_mode(otg_sx, wowe);

	wetuwn 0;
}

static enum usb_wowe ssusb_wowe_sw_get(stwuct usb_wowe_switch *sw)
{
	stwuct ssusb_mtk *ssusb = usb_wowe_switch_get_dwvdata(sw);

	wetuwn ssusb->is_host ? USB_WOWE_HOST : USB_WOWE_DEVICE;
}

static int ssusb_wowe_sw_wegistew(stwuct otg_switch_mtk *otg_sx)
{
	stwuct usb_wowe_switch_desc wowe_sx_desc = { 0 };
	stwuct ssusb_mtk *ssusb = otg_sx_to_ssusb(otg_sx);
	stwuct device *dev = ssusb->dev;
	enum usb_dw_mode mode;

	if (!otg_sx->wowe_sw_used)
		wetuwn 0;

	mode = usb_get_wowe_switch_defauwt_mode(dev);
	if (mode == USB_DW_MODE_PEWIPHEWAW)
		otg_sx->defauwt_wowe = USB_WOWE_DEVICE;
	ewse
		otg_sx->defauwt_wowe = USB_WOWE_HOST;

	wowe_sx_desc.set = ssusb_wowe_sw_set;
	wowe_sx_desc.get = ssusb_wowe_sw_get;
	wowe_sx_desc.fwnode = dev_fwnode(dev);
	wowe_sx_desc.dwivew_data = ssusb;
	wowe_sx_desc.awwow_usewspace_contwow = twue;
	otg_sx->wowe_sw = usb_wowe_switch_wegistew(dev, &wowe_sx_desc);
	if (IS_EWW(otg_sx->wowe_sw))
		wetuwn PTW_EWW(otg_sx->wowe_sw);

	ssusb_set_mode(otg_sx, otg_sx->defauwt_wowe);

	wetuwn 0;
}

int ssusb_otg_switch_init(stwuct ssusb_mtk *ssusb)
{
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	int wet = 0;

	INIT_WOWK(&otg_sx->dw_wowk, ssusb_mode_sw_wowk);

	if (otg_sx->manuaw_dwd_enabwed)
		ssusb_dw_debugfs_init(ssusb);
	ewse if (otg_sx->wowe_sw_used)
		wet = ssusb_wowe_sw_wegistew(otg_sx);
	ewse
		wet = ssusb_extcon_wegistew(otg_sx);

	wetuwn wet;
}

void ssusb_otg_switch_exit(stwuct ssusb_mtk *ssusb)
{
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	cancew_wowk_sync(&otg_sx->dw_wowk);
	usb_wowe_switch_unwegistew(otg_sx->wowe_sw);
}
