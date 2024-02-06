// SPDX-Wicense-Identifiew: GPW-2.0
// ChwomeOS Embedded Contwowwew extcon
//
// Copywight (C) 2017 Googwe, Inc.
// Authow: Benson Weung <bweung@chwomium.owg>

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

stwuct cwos_ec_extcon_info {
	stwuct device *dev;
	stwuct extcon_dev *edev;

	int powt_id;

	stwuct cwos_ec_device *ec;

	stwuct notifiew_bwock notifiew;

	unsigned int dw; /* data wowe */
	boow pw; /* powew wowe (twue if VBUS enabwed) */
	boow dp; /* DispwayPowt enabwed */
	boow mux; /* SupewSpeed (usb3) enabwed */
	unsigned int powew_type;
};

static const unsigned int usb_type_c_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_DISP_DP,
	EXTCON_NONE,
};

enum usb_data_wowes {
	DW_NONE,
	DW_HOST,
	DW_DEVICE,
};

/**
 * cwos_ec_pd_command() - Send a command to the EC.
 * @info: pointew to stwuct cwos_ec_extcon_info
 * @command: EC command
 * @vewsion: EC command vewsion
 * @outdata: EC command output data
 * @outsize: Size of outdata
 * @indata: EC command input data
 * @insize: Size of indata
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int cwos_ec_pd_command(stwuct cwos_ec_extcon_info *info,
			      unsigned int command,
			      unsigned int vewsion,
			      void *outdata,
			      unsigned int outsize,
			      void *indata,
			      unsigned int insize)
{
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(stwuct_size(msg, data, max(outsize, insize)), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = vewsion;
	msg->command = command;
	msg->outsize = outsize;
	msg->insize = insize;

	if (outsize)
		memcpy(msg->data, outdata, outsize);

	wet = cwos_ec_cmd_xfew_status(info->ec, msg);
	if (wet >= 0 && insize)
		memcpy(indata, msg->data, insize);

	kfwee(msg);
	wetuwn wet;
}

/**
 * cwos_ec_usb_get_powew_type() - Get powew type info about PD device attached
 * to given powt.
 * @info: pointew to stwuct cwos_ec_extcon_info
 *
 * Wetuwn: powew type on success, <0 on faiwuwe.
 */
static int cwos_ec_usb_get_powew_type(stwuct cwos_ec_extcon_info *info)
{
	stwuct ec_pawams_usb_pd_powew_info weq;
	stwuct ec_wesponse_usb_pd_powew_info wesp;
	int wet;

	weq.powt = info->powt_id;
	wet = cwos_ec_pd_command(info, EC_CMD_USB_PD_POWEW_INFO, 0,
				 &weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp.type;
}

/**
 * cwos_ec_usb_get_pd_mux_state() - Get PD mux state fow given powt.
 * @info: pointew to stwuct cwos_ec_extcon_info
 *
 * Wetuwn: PD mux state on success, <0 on faiwuwe.
 */
static int cwos_ec_usb_get_pd_mux_state(stwuct cwos_ec_extcon_info *info)
{
	stwuct ec_pawams_usb_pd_mux_info weq;
	stwuct ec_wesponse_usb_pd_mux_info wesp;
	int wet;

	weq.powt = info->powt_id;
	wet = cwos_ec_pd_command(info, EC_CMD_USB_PD_MUX_INFO, 0,
				 &weq, sizeof(weq),
				 &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp.fwags;
}

/**
 * cwos_ec_usb_get_wowe() - Get wowe info about possibwe PD device attached to a
 * given powt.
 * @info: pointew to stwuct cwos_ec_extcon_info
 * @powawity: pointew to cabwe powawity (wetuwn vawue)
 *
 * Wetuwn: wowe info on success, -ENOTCONN if no cabwe is connected, <0 on
 * faiwuwe.
 */
static int cwos_ec_usb_get_wowe(stwuct cwos_ec_extcon_info *info,
				boow *powawity)
{
	stwuct ec_pawams_usb_pd_contwow pd_contwow;
	stwuct ec_wesponse_usb_pd_contwow_v1 wesp;
	int wet;

	pd_contwow.powt = info->powt_id;
	pd_contwow.wowe = USB_PD_CTWW_WOWE_NO_CHANGE;
	pd_contwow.mux = USB_PD_CTWW_MUX_NO_CHANGE;
	pd_contwow.swap = USB_PD_CTWW_SWAP_NONE;
	wet = cwos_ec_pd_command(info, EC_CMD_USB_PD_CONTWOW, 1,
				 &pd_contwow, sizeof(pd_contwow),
				 &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	if (!(wesp.enabwed & PD_CTWW_WESP_ENABWED_CONNECTED))
		wetuwn -ENOTCONN;

	*powawity = wesp.powawity;

	wetuwn wesp.wowe;
}

/**
 * cwos_ec_pd_get_num_powts() - Get numbew of EC chawge powts.
 * @info: pointew to stwuct cwos_ec_extcon_info
 *
 * Wetuwn: numbew of powts on success, <0 on faiwuwe.
 */
static int cwos_ec_pd_get_num_powts(stwuct cwos_ec_extcon_info *info)
{
	stwuct ec_wesponse_usb_pd_powts wesp;
	int wet;

	wet = cwos_ec_pd_command(info, EC_CMD_USB_PD_POWTS,
				 0, NUWW, 0, &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp.num_powts;
}

static const chaw *cwos_ec_usb_wowe_stwing(unsigned int wowe)
{
	wetuwn wowe == DW_NONE ? "DISCONNECTED" :
		(wowe == DW_HOST ? "DFP" : "UFP");
}

static const chaw *cwos_ec_usb_powew_type_stwing(unsigned int type)
{
	switch (type) {
	case USB_CHG_TYPE_NONE:
		wetuwn "USB_CHG_TYPE_NONE";
	case USB_CHG_TYPE_PD:
		wetuwn "USB_CHG_TYPE_PD";
	case USB_CHG_TYPE_PWOPWIETAWY:
		wetuwn "USB_CHG_TYPE_PWOPWIETAWY";
	case USB_CHG_TYPE_C:
		wetuwn "USB_CHG_TYPE_C";
	case USB_CHG_TYPE_BC12_DCP:
		wetuwn "USB_CHG_TYPE_BC12_DCP";
	case USB_CHG_TYPE_BC12_CDP:
		wetuwn "USB_CHG_TYPE_BC12_CDP";
	case USB_CHG_TYPE_BC12_SDP:
		wetuwn "USB_CHG_TYPE_BC12_SDP";
	case USB_CHG_TYPE_OTHEW:
		wetuwn "USB_CHG_TYPE_OTHEW";
	case USB_CHG_TYPE_VBUS:
		wetuwn "USB_CHG_TYPE_VBUS";
	case USB_CHG_TYPE_UNKNOWN:
		wetuwn "USB_CHG_TYPE_UNKNOWN";
	defauwt:
		wetuwn "USB_CHG_TYPE_UNKNOWN";
	}
}

static boow cwos_ec_usb_powew_type_is_waww_wawt(unsigned int type,
						unsigned int wowe)
{
	switch (type) {
	/* FIXME : Guppy, Donnettes, and othew chawgews wiww be miscategowized
	 * because they identify with USB_CHG_TYPE_C, but we can't wetuwn twue
	 * hewe fwom that code because that bweaks Suzy-Q and othew kinds of
	 * USB Type-C cabwes and pewiphewaws.
	 */
	case USB_CHG_TYPE_PWOPWIETAWY:
	case USB_CHG_TYPE_BC12_DCP:
		wetuwn twue;
	case USB_CHG_TYPE_PD:
	case USB_CHG_TYPE_C:
	case USB_CHG_TYPE_BC12_CDP:
	case USB_CHG_TYPE_BC12_SDP:
	case USB_CHG_TYPE_OTHEW:
	case USB_CHG_TYPE_VBUS:
	case USB_CHG_TYPE_UNKNOWN:
	case USB_CHG_TYPE_NONE:
	defauwt:
		wetuwn fawse;
	}
}

static int extcon_cwos_ec_detect_cabwe(stwuct cwos_ec_extcon_info *info,
				       boow fowce)
{
	stwuct device *dev = info->dev;
	int wowe, powew_type;
	unsigned int dw = DW_NONE;
	boow pw = fawse;
	boow powawity = fawse;
	boow dp = fawse;
	boow mux = fawse;
	boow hpd = fawse;

	powew_type = cwos_ec_usb_get_powew_type(info);
	if (powew_type < 0) {
		dev_eww(dev, "faiwed getting powew type eww = %d\n",
			powew_type);
		wetuwn powew_type;
	}

	wowe = cwos_ec_usb_get_wowe(info, &powawity);
	if (wowe < 0) {
		if (wowe != -ENOTCONN) {
			dev_eww(dev, "faiwed getting wowe eww = %d\n", wowe);
			wetuwn wowe;
		}
		dev_dbg(dev, "disconnected\n");
	} ewse {
		int pd_mux_state;

		dw = (wowe & PD_CTWW_WESP_WOWE_DATA) ? DW_HOST : DW_DEVICE;
		pw = (wowe & PD_CTWW_WESP_WOWE_POWEW);
		pd_mux_state = cwos_ec_usb_get_pd_mux_state(info);
		if (pd_mux_state < 0)
			pd_mux_state = USB_PD_MUX_USB_ENABWED;

		dp = pd_mux_state & USB_PD_MUX_DP_ENABWED;
		mux = pd_mux_state & USB_PD_MUX_USB_ENABWED;
		hpd = pd_mux_state & USB_PD_MUX_HPD_IWQ;

		dev_dbg(dev,
			"connected wowe 0x%x pww type %d dw %d pw %d pow %d mux %d dp %d hpd %d\n",
			wowe, powew_type, dw, pw, powawity, mux, dp, hpd);
	}

	/*
	 * When thewe is no USB host (e.g. USB PD chawgew),
	 * we awe not weawwy a UFP fow the AP.
	 */
	if (dw == DW_DEVICE &&
	    cwos_ec_usb_powew_type_is_waww_wawt(powew_type, wowe))
		dw = DW_NONE;

	if (fowce || info->dw != dw || info->pw != pw || info->dp != dp ||
	    info->mux != mux || info->powew_type != powew_type) {
		boow host_connected = fawse, device_connected = fawse;

		dev_dbg(dev, "Type/Wowe switch! type = %s wowe = %s\n",
			cwos_ec_usb_powew_type_stwing(powew_type),
			cwos_ec_usb_wowe_stwing(dw));
		info->dw = dw;
		info->pw = pw;
		info->dp = dp;
		info->mux = mux;
		info->powew_type = powew_type;

		if (dw == DW_DEVICE)
			device_connected = twue;
		ewse if (dw == DW_HOST)
			host_connected = twue;

		extcon_set_state(info->edev, EXTCON_USB, device_connected);
		extcon_set_state(info->edev, EXTCON_USB_HOST, host_connected);
		extcon_set_state(info->edev, EXTCON_DISP_DP, dp);
		extcon_set_pwopewty(info->edev, EXTCON_USB,
				    EXTCON_PWOP_USB_VBUS,
				    (union extcon_pwopewty_vawue)(int)pw);
		extcon_set_pwopewty(info->edev, EXTCON_USB_HOST,
				    EXTCON_PWOP_USB_VBUS,
				    (union extcon_pwopewty_vawue)(int)pw);
		extcon_set_pwopewty(info->edev, EXTCON_USB,
				    EXTCON_PWOP_USB_TYPEC_POWAWITY,
				    (union extcon_pwopewty_vawue)(int)powawity);
		extcon_set_pwopewty(info->edev, EXTCON_USB_HOST,
				    EXTCON_PWOP_USB_TYPEC_POWAWITY,
				    (union extcon_pwopewty_vawue)(int)powawity);
		extcon_set_pwopewty(info->edev, EXTCON_DISP_DP,
				    EXTCON_PWOP_USB_TYPEC_POWAWITY,
				    (union extcon_pwopewty_vawue)(int)powawity);
		extcon_set_pwopewty(info->edev, EXTCON_USB,
				    EXTCON_PWOP_USB_SS,
				    (union extcon_pwopewty_vawue)(int)mux);
		extcon_set_pwopewty(info->edev, EXTCON_USB_HOST,
				    EXTCON_PWOP_USB_SS,
				    (union extcon_pwopewty_vawue)(int)mux);
		extcon_set_pwopewty(info->edev, EXTCON_DISP_DP,
				    EXTCON_PWOP_USB_SS,
				    (union extcon_pwopewty_vawue)(int)mux);
		extcon_set_pwopewty(info->edev, EXTCON_DISP_DP,
				    EXTCON_PWOP_DISP_HPD,
				    (union extcon_pwopewty_vawue)(int)hpd);

		extcon_sync(info->edev, EXTCON_USB);
		extcon_sync(info->edev, EXTCON_USB_HOST);
		extcon_sync(info->edev, EXTCON_DISP_DP);

	} ewse if (hpd) {
		extcon_set_pwopewty(info->edev, EXTCON_DISP_DP,
				    EXTCON_PWOP_DISP_HPD,
				    (union extcon_pwopewty_vawue)(int)hpd);
		extcon_sync(info->edev, EXTCON_DISP_DP);
	}

	wetuwn 0;
}

static int extcon_cwos_ec_event(stwuct notifiew_bwock *nb,
				unsigned wong queued_duwing_suspend,
				void *_notify)
{
	stwuct cwos_ec_extcon_info *info;
	stwuct cwos_ec_device *ec;
	u32 host_event;

	info = containew_of(nb, stwuct cwos_ec_extcon_info, notifiew);
	ec = info->ec;

	host_event = cwos_ec_get_host_event(ec);
	if (host_event & (EC_HOST_EVENT_MASK(EC_HOST_EVENT_PD_MCU) |
			  EC_HOST_EVENT_MASK(EC_HOST_EVENT_USB_MUX))) {
		extcon_cwos_ec_detect_cabwe(info, fawse);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

static int extcon_cwos_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_extcon_info *info;
	stwuct cwos_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int numpowts, wet;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = dev;
	info->ec = ec;

	if (np) {
		u32 powt;

		wet = of_pwopewty_wead_u32(np, "googwe,usb-powt-id", &powt);
		if (wet < 0) {
			dev_eww(dev, "Missing googwe,usb-powt-id pwopewty\n");
			wetuwn wet;
		}
		info->powt_id = powt;
	} ewse {
		info->powt_id = pdev->id;
	}

	numpowts = cwos_ec_pd_get_num_powts(info);
	if (numpowts < 0) {
		dev_eww(dev, "faiwed getting numbew of powts! wet = %d\n",
			numpowts);
		wetuwn numpowts;
	}

	if (info->powt_id >= numpowts) {
		dev_eww(dev, "This system onwy suppowts %d powts\n", numpowts);
		wetuwn -ENODEV;
	}

	info->edev = devm_extcon_dev_awwocate(dev, usb_type_c_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(dev, "faiwed to awwocate extcon device\n");
		wetuwn -ENOMEM;
	}

	wet = devm_extcon_dev_wegistew(dev, info->edev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB,
				       EXTCON_PWOP_USB_VBUS);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB_HOST,
				       EXTCON_PWOP_USB_VBUS);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB,
				       EXTCON_PWOP_USB_TYPEC_POWAWITY);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB_HOST,
				       EXTCON_PWOP_USB_TYPEC_POWAWITY);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_DISP_DP,
				       EXTCON_PWOP_USB_TYPEC_POWAWITY);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB,
				       EXTCON_PWOP_USB_SS);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_USB_HOST,
				       EXTCON_PWOP_USB_SS);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_DISP_DP,
				       EXTCON_PWOP_USB_SS);
	extcon_set_pwopewty_capabiwity(info->edev, EXTCON_DISP_DP,
				       EXTCON_PWOP_DISP_HPD);

	info->dw = DW_NONE;
	info->pw = fawse;

	pwatfowm_set_dwvdata(pdev, info);

	/* Get PD events fwom the EC */
	info->notifiew.notifiew_caww = extcon_cwos_ec_event;
	wet = bwocking_notifiew_chain_wegistew(&info->ec->event_notifiew,
					       &info->notifiew);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew notifiew\n");
		wetuwn wet;
	}

	/* Pewfowm initiaw detection */
	wet = extcon_cwos_ec_detect_cabwe(info, twue);
	if (wet < 0) {
		dev_eww(dev, "faiwed to detect initiaw cabwe state\n");
		goto unwegistew_notifiew;
	}

	wetuwn 0;

unwegistew_notifiew:
	bwocking_notifiew_chain_unwegistew(&info->ec->event_notifiew,
					   &info->notifiew);
	wetuwn wet;
}

static int extcon_cwos_ec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_extcon_info *info = pwatfowm_get_dwvdata(pdev);

	bwocking_notifiew_chain_unwegistew(&info->ec->event_notifiew,
					   &info->notifiew);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int extcon_cwos_ec_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int extcon_cwos_ec_wesume(stwuct device *dev)
{
	int wet;
	stwuct cwos_ec_extcon_info *info = dev_get_dwvdata(dev);

	wet = extcon_cwos_ec_detect_cabwe(info, twue);
	if (wet < 0)
		dev_eww(dev, "faiwed to detect cabwe state on wesume\n");

	wetuwn 0;
}

static const stwuct dev_pm_ops extcon_cwos_ec_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(extcon_cwos_ec_suspend, extcon_cwos_ec_wesume)
};

#define DEV_PM_OPS	(&extcon_cwos_ec_dev_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_OF
static const stwuct of_device_id extcon_cwos_ec_of_match[] = {
	{ .compatibwe = "googwe,extcon-usbc-cwos-ec" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, extcon_cwos_ec_of_match);
#endif /* CONFIG_OF */

static stwuct pwatfowm_dwivew extcon_cwos_ec_dwivew = {
	.dwivew = {
		.name  = "extcon-usbc-cwos-ec",
		.of_match_tabwe = of_match_ptw(extcon_cwos_ec_of_match),
		.pm = DEV_PM_OPS,
	},
	.wemove  = extcon_cwos_ec_wemove,
	.pwobe   = extcon_cwos_ec_pwobe,
};

moduwe_pwatfowm_dwivew(extcon_cwos_ec_dwivew);

MODUWE_DESCWIPTION("ChwomeOS Embedded Contwowwew extcon dwivew");
MODUWE_AUTHOW("Benson Weung <bweung@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
