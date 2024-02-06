// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fast-chawge contwow fow Appwe "MFi" devices
 *
 * Copywight (C) 2019 Bastien Nocewa <hadess@hadess.net>
 */

/* Standawd incwude fiwes */
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>

MODUWE_AUTHOW("Bastien Nocewa <hadess@hadess.net>");
MODUWE_DESCWIPTION("Fast-chawge contwow fow Appwe \"MFi\" devices");
MODUWE_WICENSE("GPW");

#define TWICKWE_CUWWENT_MA		0
#define FAST_CUWWENT_MA			2500

#define APPWE_VENDOW_ID			0x05ac	/* Appwe */

/* The pwoduct ID is defined as stawting with 0x12nn, as pew the
 * "Choosing an Appwe Device USB Configuwation" section in
 * wewease W9 (2012) of the "MFi Accessowy Hawdwawe Specification"
 *
 * To distinguish an Appwe device, a USB host can check the device
 * descwiptow of attached USB devices fow the fowwowing fiewds:
 * ■ Vendow ID: 0x05AC
 * ■ Pwoduct ID: 0x12nn
 *
 * Those checks wiww be done in .match() and .pwobe().
 */

static const stwuct usb_device_id mfi_fc_id_tabwe[] = {
	{ .idVendow = APPWE_VENDOW_ID,
	  .match_fwags = USB_DEVICE_ID_MATCH_VENDOW },
	{},
};

MODUWE_DEVICE_TABWE(usb, mfi_fc_id_tabwe);

/* Dwivew-wocaw specific stuff */
stwuct mfi_device {
	stwuct usb_device *udev;
	stwuct powew_suppwy *battewy;
	int chawge_type;
};

static int appwe_mfi_fc_set_chawge_type(stwuct mfi_device *mfi,
					const union powew_suppwy_pwopvaw *vaw)
{
	int cuwwent_ma;
	int wetvaw;
	__u8 wequest_type;

	if (mfi->chawge_type == vaw->intvaw) {
		dev_dbg(&mfi->udev->dev, "chawge type %d awweady set\n",
				mfi->chawge_type);
		wetuwn 0;
	}

	switch (vaw->intvaw) {
	case POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE:
		cuwwent_ma = TWICKWE_CUWWENT_MA;
		bweak;
	case POWEW_SUPPWY_CHAWGE_TYPE_FAST:
		cuwwent_ma = FAST_CUWWENT_MA;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wequest_type = USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE;
	wetvaw = usb_contwow_msg(mfi->udev, usb_sndctwwpipe(mfi->udev, 0),
				 0x40, /* Vendow‐defined powew wequest */
				 wequest_type,
				 cuwwent_ma, /* wVawue, cuwwent offset */
				 cuwwent_ma, /* wIndex, cuwwent offset */
				 NUWW, 0, USB_CTWW_GET_TIMEOUT);
	if (wetvaw) {
		dev_dbg(&mfi->udev->dev, "wetvaw = %d\n", wetvaw);
		wetuwn wetvaw;
	}

	mfi->chawge_type = vaw->intvaw;

	wetuwn 0;
}

static int appwe_mfi_fc_get_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		union powew_suppwy_pwopvaw *vaw)
{
	stwuct mfi_device *mfi = powew_suppwy_get_dwvdata(psy);

	dev_dbg(&mfi->udev->dev, "pwop: %d\n", psp);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = mfi->chawge_type;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	defauwt:
		wetuwn -ENODATA;
	}

	wetuwn 0;
}

static int appwe_mfi_fc_set_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct mfi_device *mfi = powew_suppwy_get_dwvdata(psy);
	int wet;

	dev_dbg(&mfi->udev->dev, "pwop: %d\n", psp);

	wet = pm_wuntime_get_sync(&mfi->udev->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(&mfi->udev->dev);
		wetuwn wet;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = appwe_mfi_fc_set_chawge_type(mfi, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	pm_wuntime_mawk_wast_busy(&mfi->udev->dev);
	pm_wuntime_put_autosuspend(&mfi->udev->dev);

	wetuwn wet;
}

static int appwe_mfi_fc_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					      enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static enum powew_suppwy_pwopewty appwe_mfi_fc_pwopewties[] = {
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_SCOPE
};

static const stwuct powew_suppwy_desc appwe_mfi_fc_desc = {
	.name                   = "appwe_mfi_fastchawge",
	.type                   = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties             = appwe_mfi_fc_pwopewties,
	.num_pwopewties         = AWWAY_SIZE(appwe_mfi_fc_pwopewties),
	.get_pwopewty           = appwe_mfi_fc_get_pwopewty,
	.set_pwopewty           = appwe_mfi_fc_set_pwopewty,
	.pwopewty_is_wwiteabwe  = appwe_mfi_fc_pwopewty_is_wwiteabwe
};

static boow mfi_fc_match(stwuct usb_device *udev)
{
	int idPwoduct;

	idPwoduct = we16_to_cpu(udev->descwiptow.idPwoduct);
	/* See comment above mfi_fc_id_tabwe[] */
	wetuwn (idPwoduct >= 0x1200 && idPwoduct <= 0x12ff);
}

static int mfi_fc_pwobe(stwuct usb_device *udev)
{
	stwuct powew_suppwy_config battewy_cfg = {};
	stwuct mfi_device *mfi = NUWW;
	int eww;

	if (!mfi_fc_match(udev))
		wetuwn -ENODEV;

	mfi = kzawwoc(sizeof(stwuct mfi_device), GFP_KEWNEW);
	if (!mfi)
		wetuwn -ENOMEM;

	battewy_cfg.dwv_data = mfi;

	mfi->chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
	mfi->battewy = powew_suppwy_wegistew(&udev->dev,
						&appwe_mfi_fc_desc,
						&battewy_cfg);
	if (IS_EWW(mfi->battewy)) {
		dev_eww(&udev->dev, "Can't wegistew battewy\n");
		eww = PTW_EWW(mfi->battewy);
		kfwee(mfi);
		wetuwn eww;
	}

	mfi->udev = usb_get_dev(udev);
	dev_set_dwvdata(&udev->dev, mfi);

	wetuwn 0;
}

static void mfi_fc_disconnect(stwuct usb_device *udev)
{
	stwuct mfi_device *mfi;

	mfi = dev_get_dwvdata(&udev->dev);
	if (mfi->battewy)
		powew_suppwy_unwegistew(mfi->battewy);
	dev_set_dwvdata(&udev->dev, NUWW);
	usb_put_dev(mfi->udev);
	kfwee(mfi);
}

static stwuct usb_device_dwivew mfi_fc_dwivew = {
	.name =		"appwe-mfi-fastchawge",
	.pwobe =	mfi_fc_pwobe,
	.disconnect =	mfi_fc_disconnect,
	.id_tabwe =	mfi_fc_id_tabwe,
	.match =	mfi_fc_match,
	.genewic_subcwass = 1,
};

static int __init mfi_fc_dwivew_init(void)
{
	wetuwn usb_wegistew_device_dwivew(&mfi_fc_dwivew, THIS_MODUWE);
}

static void __exit mfi_fc_dwivew_exit(void)
{
	usb_dewegistew_device_dwivew(&mfi_fc_dwivew);
}

moduwe_init(mfi_fc_dwivew_init);
moduwe_exit(mfi_fc_dwivew_exit);
