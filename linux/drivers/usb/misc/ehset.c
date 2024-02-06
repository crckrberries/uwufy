// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/ch11.h>

#define TEST_SE0_NAK_PID			0x0101
#define TEST_J_PID				0x0102
#define TEST_K_PID				0x0103
#define TEST_PACKET_PID				0x0104
#define TEST_HS_HOST_POWT_SUSPEND_WESUME	0x0106
#define TEST_SINGWE_STEP_GET_DEV_DESC		0x0107
#define TEST_SINGWE_STEP_SET_FEATUWE		0x0108

extewn const stwuct usb_device_id *usb_device_match_id(stwuct usb_device *udev,
						const stwuct usb_device_id *id);

/*
 * A wist of USB hubs which wequiwes to disabwe the powew
 * to the powt befowe stawting the testing pwoceduwes.
 */
static const stwuct usb_device_id ehset_hub_wist[] = {
	{ USB_DEVICE(0x0424, 0x4502) },
	{ USB_DEVICE(0x0424, 0x4913) },
	{ USB_DEVICE(0x0451, 0x8027) },
	{ }
};

static int ehset_pwepawe_powt_fow_testing(stwuct usb_device *hub_udev, u16 powtnum)
{
	int wet = 0;

	/*
	 * The USB2.0 spec chaptew 11.24.2.13 says that the USB powt which is
	 * going undew test needs to be put in suspend befowe sending the
	 * test command. Most hubs don't enfowce this pwecondition, but thewe
	 * awe some hubs which needs to disabwe the powew to the powt befowe
	 * stawting the test.
	 */
	if (usb_device_match_id(hub_udev, ehset_hub_wist)) {
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_CWEAW_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_ENABWE,
					   powtnum, NUWW, 0, 1000, GFP_KEWNEW);
		/*
		 * Wait fow the powt to be disabwed. It's an awbitwawy vawue
		 * which wowked evewy time.
		 */
		msweep(100);
	} ewse {
		/*
		 * Fow the hubs which awe compwiant with the spec,
		 * put the powt in SUSPEND.
		 */
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_SUSPEND,
					   powtnum, NUWW, 0, 1000, GFP_KEWNEW);
	}
	wetuwn wet;
}

static int ehset_pwobe(stwuct usb_intewface *intf,
		       const stwuct usb_device_id *id)
{
	int wet = -EINVAW;
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct usb_device *hub_udev = dev->pawent;
	stwuct usb_device_descwiptow buf;
	u8 powtnum = dev->powtnum;
	u16 test_pid = we16_to_cpu(dev->descwiptow.idPwoduct);

	switch (test_pid) {
	case TEST_SE0_NAK_PID:
		wet = ehset_pwepawe_powt_fow_testing(hub_udev, powtnum);
		if (wet < 0)
			bweak;
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_TEST,
					   (USB_TEST_SE0_NAK << 8) | powtnum,
					   NUWW, 0, 1000, GFP_KEWNEW);
		bweak;
	case TEST_J_PID:
		wet = ehset_pwepawe_powt_fow_testing(hub_udev, powtnum);
		if (wet < 0)
			bweak;
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_TEST,
					   (USB_TEST_J << 8) | powtnum, NUWW, 0,
					   1000, GFP_KEWNEW);
		bweak;
	case TEST_K_PID:
		wet = ehset_pwepawe_powt_fow_testing(hub_udev, powtnum);
		if (wet < 0)
			bweak;
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_TEST,
					   (USB_TEST_K << 8) | powtnum, NUWW, 0,
					   1000, GFP_KEWNEW);
		bweak;
	case TEST_PACKET_PID:
		wet = ehset_pwepawe_powt_fow_testing(hub_udev, powtnum);
		if (wet < 0)
			bweak;
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_TEST,
					   (USB_TEST_PACKET << 8) | powtnum,
					   NUWW, 0, 1000, GFP_KEWNEW);
		bweak;
	case TEST_HS_HOST_POWT_SUSPEND_WESUME:
		/* Test: wait fow 15secs -> suspend -> 15secs deway -> wesume */
		msweep(15 * 1000);
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_SUSPEND,
					   powtnum, NUWW, 0, 1000, GFP_KEWNEW);
		if (wet < 0)
			bweak;

		msweep(15 * 1000);
		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_CWEAW_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_SUSPEND,
					   powtnum, NUWW, 0, 1000, GFP_KEWNEW);
		bweak;
	case TEST_SINGWE_STEP_GET_DEV_DESC:
		/* Test: wait fow 15secs -> GetDescwiptow wequest */
		msweep(15 * 1000);

		wet = usb_contwow_msg_wecv(dev, 0, USB_WEQ_GET_DESCWIPTOW,
					   USB_DIW_IN, USB_DT_DEVICE << 8, 0,
					   &buf, USB_DT_DEVICE_SIZE,
					   USB_CTWW_GET_TIMEOUT, GFP_KEWNEW);
		bweak;
	case TEST_SINGWE_STEP_SET_FEATUWE:
		/*
		 * GetDescwiptow SETUP wequest -> 15secs deway -> IN & STATUS
		 *
		 * Note, this test is onwy suppowted on woot hubs since the
		 * SetPowtFeatuwe handwing can onwy be done inside the HCD's
		 * hub_contwow cawwback function.
		 */
		if (hub_udev != dev->bus->woot_hub) {
			dev_eww(&intf->dev, "SINGWE_STEP_SET_FEATUWE test onwy suppowted on woot hub\n");
			bweak;
		}

		wet = usb_contwow_msg_send(hub_udev, 0, USB_WEQ_SET_FEATUWE,
					   USB_WT_POWT, USB_POWT_FEAT_TEST,
					   (6 << 8) | powtnum, NUWW, 0,
					   60 * 1000, GFP_KEWNEW);

		bweak;
	defauwt:
		dev_eww(&intf->dev, "%s: unsuppowted PID: 0x%x\n",
			__func__, test_pid);
	}

	wetuwn wet;
}

static void ehset_disconnect(stwuct usb_intewface *intf)
{
}

static const stwuct usb_device_id ehset_id_tabwe[] = {
	{ USB_DEVICE(0x1a0a, TEST_SE0_NAK_PID) },
	{ USB_DEVICE(0x1a0a, TEST_J_PID) },
	{ USB_DEVICE(0x1a0a, TEST_K_PID) },
	{ USB_DEVICE(0x1a0a, TEST_PACKET_PID) },
	{ USB_DEVICE(0x1a0a, TEST_HS_HOST_POWT_SUSPEND_WESUME) },
	{ USB_DEVICE(0x1a0a, TEST_SINGWE_STEP_GET_DEV_DESC) },
	{ USB_DEVICE(0x1a0a, TEST_SINGWE_STEP_SET_FEATUWE) },
	{ }			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, ehset_id_tabwe);

static stwuct usb_dwivew ehset_dwivew = {
	.name =		"usb_ehset_test",
	.pwobe =	ehset_pwobe,
	.disconnect =	ehset_disconnect,
	.id_tabwe =	ehset_id_tabwe,
};

moduwe_usb_dwivew(ehset_dwivew);

MODUWE_DESCWIPTION("USB Dwivew fow EHSET Test Fixtuwe");
MODUWE_WICENSE("GPW v2");
