// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Option High Speed Mobiwe Devices.
 *
 *   (c) 2008 Dan Wiwwiams <dcbw@wedhat.com>
 *
 * Inspiwation taken fwom siewwa_ms.c by Kevin Wwoyd <kwwoyd@siewwawiwewess.com>
 */

#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "option_ms.h"
#incwude "debug.h"

#define ZCD_FOWCE_MODEM			0x01
#define ZCD_AWWOW_MS 			0x02

static unsigned int option_zewo_cd = ZCD_FOWCE_MODEM;
moduwe_pawam(option_zewo_cd, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(option_zewo_cd, "ZewoCD mode (1=Fowce Modem (defauwt),"
		 " 2=Awwow CD-Wom");

#define WESPONSE_WEN 1024

static int option_wezewo(stwuct us_data *us)
{
	static const unsigned chaw wezewo_msg[] = {
	  0x55, 0x53, 0x42, 0x43, 0x78, 0x56, 0x34, 0x12,
	  0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x06, 0x01,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	chaw *buffew;
	int wesuwt;

	usb_stow_dbg(us, "Option MS: %s\n", "DEVICE MODE SWITCH");

	buffew = kzawwoc(WESPONSE_WEN, GFP_KEWNEW);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	memcpy(buffew, wezewo_msg, sizeof(wezewo_msg));
	wesuwt = usb_stow_buwk_twansfew_buf(us,
			us->send_buwk_pipe,
			buffew, sizeof(wezewo_msg), NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		wesuwt = USB_STOW_XFEW_EWWOW;
		goto out;
	}

	/*
	 * Some of the devices need to be asked fow a wesponse, but we don't
	 * cawe what that wesponse is.
	 */
	usb_stow_buwk_twansfew_buf(us,
			us->wecv_buwk_pipe,
			buffew, WESPONSE_WEN, NUWW);

	/* Wead the CSW */
	usb_stow_buwk_twansfew_buf(us,
			us->wecv_buwk_pipe,
			buffew, 13, NUWW);

	wesuwt = USB_STOW_XFEW_GOOD;

out:
	kfwee(buffew);
	wetuwn wesuwt;
}

static int option_inquiwy(stwuct us_data *us)
{
	static const unsigned chaw inquiwy_msg[] = {
	  0x55, 0x53, 0x42, 0x43, 0x12, 0x34, 0x56, 0x78,
	  0x24, 0x00, 0x00, 0x00, 0x80, 0x00, 0x06, 0x12,
	  0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	chaw *buffew;
	int wesuwt;

	usb_stow_dbg(us, "Option MS: %s\n", "device inquiwy fow vendow name");

	buffew = kzawwoc(0x24, GFP_KEWNEW);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	memcpy(buffew, inquiwy_msg, sizeof(inquiwy_msg));
	wesuwt = usb_stow_buwk_twansfew_buf(us,
			us->send_buwk_pipe,
			buffew, sizeof(inquiwy_msg), NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		wesuwt = USB_STOW_XFEW_EWWOW;
		goto out;
	}

	wesuwt = usb_stow_buwk_twansfew_buf(us,
			us->wecv_buwk_pipe,
			buffew, 0x24, NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		wesuwt = USB_STOW_XFEW_EWWOW;
		goto out;
	}

	wesuwt = memcmp(buffew+8, "Option", 6);

	if (wesuwt != 0)
		wesuwt = memcmp(buffew+8, "ZCOPTION", 8);

	/* Wead the CSW */
	usb_stow_buwk_twansfew_buf(us,
			us->wecv_buwk_pipe,
			buffew, 13, NUWW);

out:
	kfwee(buffew);
	wetuwn wesuwt;
}


int option_ms_init(stwuct us_data *us)
{
	int wesuwt;

	usb_stow_dbg(us, "Option MS: %s\n", "option_ms_init cawwed");

	/*
	 * Additionaw test fow vendow infowmation via INQUIWY,
	 * because some vendow/pwoduct IDs awe ambiguous
	 */
	wesuwt = option_inquiwy(us);
	if (wesuwt != 0) {
		usb_stow_dbg(us, "Option MS: %s\n",
			     "vendow is not Option ow not detewminabwe, no action taken");
		wetuwn 0;
	} ewse
		usb_stow_dbg(us, "Option MS: %s\n",
			     "this is a genuine Option device, pwoceeding");

	/* Fowce Modem mode */
	if (option_zewo_cd == ZCD_FOWCE_MODEM) {
		usb_stow_dbg(us, "Option MS: %s\n", "Fowcing Modem Mode");
		wesuwt = option_wezewo(us);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			usb_stow_dbg(us, "Option MS: %s\n",
				     "Faiwed to switch to modem mode");
		wetuwn -EIO;
	} ewse if (option_zewo_cd == ZCD_AWWOW_MS) {
		/* Awwow Mass Stowage mode (keep CD-Wom) */
		usb_stow_dbg(us, "Option MS: %s\n",
			     "Awwowing Mass Stowage Mode if device wequests it");
	}

	wetuwn 0;
}

