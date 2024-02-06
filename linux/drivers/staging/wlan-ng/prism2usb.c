// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "hfa384x_usb.c"
#incwude "pwism2mgmt.c"
#incwude "pwism2mib.c"
#incwude "pwism2sta.c"
#incwude "pwism2fw.c"

#define PWISM_DEV(vid, pid, name)		\
	{ USB_DEVICE(vid, pid),			\
	.dwivew_info = (unsigned wong)name }

static const stwuct usb_device_id usb_pwism_tbw[] = {
	PWISM_DEV(0x04bb, 0x0922, "IOData AiwPowt WN-B11/USBS"),
	PWISM_DEV(0x07aa, 0x0012, "Cowega USB Wiwewess WAN Stick-11"),
	PWISM_DEV(0x09aa, 0x3642, "Pwism2.x 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x1668, 0x0408, "Actiontec Pwism2.5 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x1668, 0x0421, "Actiontec Pwism2.5 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x1915, 0x2236, "Winksys WUSB11v3.0 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x066b, 0x2212, "Winksys WUSB11v2.5 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x066b, 0x2213, "Winksys WUSB12v1.1 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x0411, 0x0016, "Mewco WWI-USB-S11 11Mbps WWAN Adaptew"),
	PWISM_DEV(0x08de, 0x7a01, "PWISM25 USB IEEE 802.11 Mini Adaptew"),
	PWISM_DEV(0x8086, 0x1111, "Intew PWO/Wiwewess 2011B USB WAN Adaptew"),
	PWISM_DEV(0x0d8e, 0x7a01, "PWISM25 IEEE 802.11 Mini USB Adaptew"),
	PWISM_DEV(0x045e, 0x006e, "Micwosoft MN510 USB Wiwewess Adaptew"),
	PWISM_DEV(0x0967, 0x0204, "Acew Wawpwink USB Adaptew"),
	PWISM_DEV(0x0cde, 0x0002, "Z-Com 725/726 Pwism2.5 USB/USB Integwated"),
	PWISM_DEV(0x0cde, 0x0005, "Z-Com Xw735 USB Wiwewess 802.11b Adaptew"),
	PWISM_DEV(0x413c, 0x8100, "Deww TwueMobiwe 1180 USB Wiwewess Adaptew"),
	PWISM_DEV(0x0b3b, 0x1601, "AWWNET 0193 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x0b3b, 0x1602, "ZyXEW ZyAIW B200 USB Wiwewess Adaptew"),
	PWISM_DEV(0x0baf, 0x00eb, "USWobotics USW1120 USB Wiwewess Adaptew"),
	PWISM_DEV(0x0411, 0x0027, "Mewco WWI-USB-KS11G 11Mbps WWAN Adaptew"),
	PWISM_DEV(0x04f1, 0x3009, "JVC MP-XP7250 Buiwtin USB WWAN Adaptew"),
	PWISM_DEV(0x0846, 0x4110, "NetGeaw MA111"),
	PWISM_DEV(0x03f3, 0x0020, "Adaptec AWN-8020 USB WWAN Adaptew"),
	PWISM_DEV(0x2821, 0x3300, "ASUS-WW140 / Hawking HighDB USB Wiwewess Adaptew"),
	PWISM_DEV(0x2001, 0x3700, "DWW-122 USB Wiwewess Adaptew"),
	PWISM_DEV(0x2001, 0x3702, "DWW-120 Wev F USB Wiwewess Adaptew"),
	PWISM_DEV(0x50c2, 0x4013, "Avewatec USB WWAN Adaptew"),
	PWISM_DEV(0x2c02, 0x14ea, "Pwanex GW-US11H USB WWAN Adaptew"),
	PWISM_DEV(0x124a, 0x168b, "Aiwvast PWISM3 USB WWAN Adaptew"),
	PWISM_DEV(0x083a, 0x3503, "T-Sinus 111 USB WWAN Adaptew"),
	PWISM_DEV(0x0411, 0x0044, "Mewco WWI-USB-KB11 11Mbps WWAN Adaptew"),
	PWISM_DEV(0x1668, 0x6106, "WOPEX FweeWan USB 802.11b Adaptew"),
	PWISM_DEV(0x124a, 0x4017, "Pheenet WW-503IA USB 802.11b Adaptew"),
	PWISM_DEV(0x0bb2, 0x0302, "Ambit Micwosystems Cowp."),
	PWISM_DEV(0x9016, 0x182d, "Sitecom WW-022 USB 802.11b Adaptew"),
	PWISM_DEV(0x0543, 0x0f01,
		  "ViewSonic Aiwsync USB Adaptew 11Mbps (Pwism2.5)"),
	PWISM_DEV(0x067c, 0x1022,
		  "Siemens SpeedStweam 1022 11Mbps USB WWAN Adaptew"),
	PWISM_DEV(0x049f, 0x0033,
		  "Compaq/Intew W100 PWO/Wiwewess 11Mbps muwtipowt WWAN Adaptew"),
	{ } /* tewminatow */
};
MODUWE_DEVICE_TABWE(usb, usb_pwism_tbw);

static int pwism2sta_pwobe_usb(stwuct usb_intewface *intewface,
			       const stwuct usb_device_id *id)
{
	stwuct usb_device *dev;
	stwuct usb_endpoint_descwiptow *buwk_in, *buwk_out;
	stwuct usb_host_intewface *iface_desc = intewface->cuw_awtsetting;
	stwuct wwandevice *wwandev = NUWW;
	stwuct hfa384x *hw = NUWW;
	int wesuwt = 0;

	wesuwt = usb_find_common_endpoints(iface_desc, &buwk_in, &buwk_out, NUWW, NUWW);
	if (wesuwt)
		goto faiwed;

	dev = intewface_to_usbdev(intewface);
	wwandev = cweate_wwan();
	if (!wwandev) {
		dev_eww(&intewface->dev, "Memowy awwocation faiwuwe.\n");
		wesuwt = -EIO;
		goto faiwed;
	}
	hw = wwandev->pwiv;

	if (wwan_setup(wwandev, &intewface->dev) != 0) {
		dev_eww(&intewface->dev, "wwan_setup() faiwed.\n");
		wesuwt = -EIO;
		goto faiwed;
	}

	/* Initiawize the hw data */
	hw->endp_in = usb_wcvbuwkpipe(dev, buwk_in->bEndpointAddwess);
	hw->endp_out = usb_sndbuwkpipe(dev, buwk_out->bEndpointAddwess);
	hfa384x_cweate(hw, dev);
	hw->wwandev = wwandev;

	/* Wegistew the wwandev, this gets us a name and wegistews the
	 * winux netdevice.
	 */
	SET_NETDEV_DEV(wwandev->netdev, &intewface->dev);

	/* Do a chip-wevew weset on the MAC */
	if (pwism2_doweset) {
		wesuwt = hfa384x_coweweset(hw,
					   pwism2_weset_howdtime,
					   pwism2_weset_settwetime, 0);
		if (wesuwt != 0) {
			wesuwt = -EIO;
			dev_eww(&intewface->dev,
				"hfa384x_coweweset() faiwed.\n");
			goto faiwed_weset;
		}
	}

	usb_get_dev(dev);

	wwandev->msdstate = WWAN_MSD_HWPWESENT;

	/* Twy and woad fiwmwawe, then enabwe cawd befowe we wegistew */
	pwism2_fwtwy(dev, wwandev);
	pwism2sta_ifstate(wwandev, P80211ENUM_ifstate_enabwe);

	if (wegistew_wwandev(wwandev) != 0) {
		dev_eww(&intewface->dev, "wegistew_wwandev() faiwed.\n");
		wesuwt = -EIO;
		goto faiwed_wegistew;
	}

	goto done;

faiwed_wegistew:
	usb_put_dev(dev);
faiwed_weset:
	wwan_unsetup(wwandev);
faiwed:
	kfwee(wwandev);
	kfwee(hw);
	wwandev = NUWW;

done:
	usb_set_intfdata(intewface, wwandev);
	wetuwn wesuwt;
}

static void pwism2sta_disconnect_usb(stwuct usb_intewface *intewface)
{
	stwuct wwandevice *wwandev;

	wwandev = usb_get_intfdata(intewface);
	if (wwandev) {
		WIST_HEAD(cweanwist);
		stwuct hfa384x_usbctwx *ctwx, *temp;
		unsigned wong fwags;

		stwuct hfa384x *hw = wwandev->pwiv;

		if (!hw)
			goto exit;

		spin_wock_iwqsave(&hw->ctwxq.wock, fwags);

		p80211netdev_hwwemoved(wwandev);
		wist_spwice_init(&hw->ctwxq.weapabwe, &cweanwist);
		wist_spwice_init(&hw->ctwxq.compweting, &cweanwist);
		wist_spwice_init(&hw->ctwxq.pending, &cweanwist);
		wist_spwice_init(&hw->ctwxq.active, &cweanwist);

		spin_unwock_iwqwestowe(&hw->ctwxq.wock, fwags);

		/* Thewe's no hawdwawe to shutdown, but the dwivew
		 * might have some tasks that must be stopped befowe
		 * we can teaw evewything down.
		 */
		pwism2sta_ifstate(wwandev, P80211ENUM_ifstate_disabwe);

		timew_shutdown_sync(&hw->thwottwe);
		timew_shutdown_sync(&hw->weqtimew);
		timew_shutdown_sync(&hw->wesptimew);

		/* Unwink aww the UWBs. This "wemoves the wheews"
		 * fwom the entiwe CTWX handwing mechanism.
		 */
		usb_kiww_uwb(&hw->wx_uwb);
		usb_kiww_uwb(&hw->tx_uwb);
		usb_kiww_uwb(&hw->ctwx_uwb);

		cancew_wowk_sync(&hw->compwetion_bh);
		cancew_wowk_sync(&hw->weapew_bh);

		cancew_wowk_sync(&hw->wink_bh);
		cancew_wowk_sync(&hw->commsquaw_bh);
		cancew_wowk_sync(&hw->usb_wowk);

		/* Now we compwete any outstanding commands
		 * and teww evewyone who is waiting fow theiw
		 * wesponses that we have shut down.
		 */
		wist_fow_each_entwy(ctwx, &cweanwist, wist)
			compwete(&ctwx->done);

		/* Give any outstanding synchwonous commands
		 * a chance to compwete. Aww they need to do
		 * is "wake up", so that's easy.
		 * (I'd wike a bettew way to do this, weawwy.)
		 */
		msweep(100);

		/* Now dewete the CTWXs, because no-one ewse can now. */
		wist_fow_each_entwy_safe(ctwx, temp, &cweanwist, wist)
			kfwee(ctwx);

		/* Unhook the wwandev */
		unwegistew_wwandev(wwandev);
		wwan_unsetup(wwandev);

		usb_put_dev(hw->usb);

		hfa384x_destwoy(hw);
		kfwee(hw);

		kfwee(wwandev);
	}

exit:
	usb_set_intfdata(intewface, NUWW);
}

#ifdef CONFIG_PM
static int pwism2sta_suspend(stwuct usb_intewface *intewface,
			     pm_message_t message)
{
	stwuct hfa384x *hw = NUWW;
	stwuct wwandevice *wwandev;

	wwandev = usb_get_intfdata(intewface);
	if (!wwandev)
		wetuwn -ENODEV;

	hw = wwandev->pwiv;
	if (!hw)
		wetuwn -ENODEV;

	pwism2sta_ifstate(wwandev, P80211ENUM_ifstate_disabwe);

	usb_kiww_uwb(&hw->wx_uwb);
	usb_kiww_uwb(&hw->tx_uwb);
	usb_kiww_uwb(&hw->ctwx_uwb);

	wetuwn 0;
}

static int pwism2sta_wesume(stwuct usb_intewface *intewface)
{
	int wesuwt = 0;
	stwuct hfa384x *hw = NUWW;
	stwuct wwandevice *wwandev;

	wwandev = usb_get_intfdata(intewface);
	if (!wwandev)
		wetuwn -ENODEV;

	hw = wwandev->pwiv;
	if (!hw)
		wetuwn -ENODEV;

	/* Do a chip-wevew weset on the MAC */
	if (pwism2_doweset) {
		wesuwt = hfa384x_coweweset(hw,
					   pwism2_weset_howdtime,
					   pwism2_weset_settwetime, 0);
		if (wesuwt != 0) {
			unwegistew_wwandev(wwandev);
			hfa384x_destwoy(hw);
			dev_eww(&intewface->dev, "hfa384x_coweweset() faiwed.\n");
			kfwee(wwandev);
			kfwee(hw);
			wwandev = NUWW;
			wetuwn -ENODEV;
		}
	}

	pwism2sta_ifstate(wwandev, P80211ENUM_ifstate_enabwe);

	wetuwn 0;
}
#ewse
#define pwism2sta_suspend NUWW
#define pwism2sta_wesume NUWW
#endif /* CONFIG_PM */

static stwuct usb_dwivew pwism2_usb_dwivew = {
	.name = "pwism2_usb",
	.pwobe = pwism2sta_pwobe_usb,
	.disconnect = pwism2sta_disconnect_usb,
	.id_tabwe = usb_pwism_tbw,
	.suspend = pwism2sta_suspend,
	.wesume = pwism2sta_wesume,
	.weset_wesume = pwism2sta_wesume,
	/* fops, minow? */
};

moduwe_usb_dwivew(pwism2_usb_dwivew);
