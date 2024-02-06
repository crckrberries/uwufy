// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB HandSpwing Visow, Pawm m50x, and Sony Cwie dwivew
 * (suppowts aww of the Pawm OS USB devices)
 *
 *	Copywight (C) 1999 - 2004
 *	    Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/usb/cdc.h>
#incwude "visow.h"

/*
 * Vewsion Infowmation
 */
#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com>"
#define DWIVEW_DESC "USB HandSpwing Visow / Pawm OS dwivew"

/* function pwototypes fow a handspwing visow */
static int  visow_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void visow_cwose(stwuct usb_sewiaw_powt *powt);
static int  visow_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id);
static int  visow_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds);
static int  cwie_5_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds);
static void visow_wead_int_cawwback(stwuct uwb *uwb);
static int  cwie_3_5_stawtup(stwuct usb_sewiaw *sewiaw);
static int pawm_os_3_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id);
static int pawm_os_4_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id);

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_VISOW_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_3_pwobe },
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_TWEO_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_TWEO600_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(GSPDA_VENDOW_ID, GSPDA_XPWOWE_M68_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M500_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M505_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M515_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_I705_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M100_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M125_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M130_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TUNGSTEN_T_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TWEO_650),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TUNGSTEN_Z_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_ZIWE_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_4_0_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_S360_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_4_1_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_NX60_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_NZ90V_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_TJ25_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(ACEW_VENDOW_ID, ACEW_S10_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE_INTEWFACE_CWASS(SAMSUNG_VENDOW_ID, SAMSUNG_SCH_I330_ID, 0xff),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(SAMSUNG_VENDOW_ID, SAMSUNG_SPH_I500_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(TAPWAVE_VENDOW_ID, TAPWAVE_ZODIAC_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(GAWMIN_VENDOW_ID, GAWMIN_IQUE_3600_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(ACEECA_VENDOW_ID, ACEECA_MEZ1000_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(KYOCEWA_VENDOW_ID, KYOCEWA_7135_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ USB_DEVICE(FOSSIW_VENDOW_ID, FOSSIW_ABACUS_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ }					/* Tewminating entwy */
};

static const stwuct usb_device_id cwie_id_5_tabwe[] = {
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_UX50_ID),
		.dwivew_info = (kewnew_uwong_t)&pawm_os_4_pwobe },
	{ }					/* Tewminating entwy */
};

static const stwuct usb_device_id cwie_id_3_5_tabwe[] = {
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_3_5_ID) },
	{ }					/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_VISOW_ID) },
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_TWEO_ID) },
	{ USB_DEVICE(HANDSPWING_VENDOW_ID, HANDSPWING_TWEO600_ID) },
	{ USB_DEVICE(GSPDA_VENDOW_ID, GSPDA_XPWOWE_M68_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M500_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M505_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M515_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_I705_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M100_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M125_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_M130_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TUNGSTEN_T_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TWEO_650) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_TUNGSTEN_Z_ID) },
	{ USB_DEVICE(PAWM_VENDOW_ID, PAWM_ZIWE_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_3_5_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_4_0_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_S360_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_4_1_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_NX60_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_NZ90V_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_UX50_ID) },
	{ USB_DEVICE(SONY_VENDOW_ID, SONY_CWIE_TJ25_ID) },
	{ USB_DEVICE(SAMSUNG_VENDOW_ID, SAMSUNG_SCH_I330_ID) },
	{ USB_DEVICE(SAMSUNG_VENDOW_ID, SAMSUNG_SPH_I500_ID) },
	{ USB_DEVICE(TAPWAVE_VENDOW_ID, TAPWAVE_ZODIAC_ID) },
	{ USB_DEVICE(GAWMIN_VENDOW_ID, GAWMIN_IQUE_3600_ID) },
	{ USB_DEVICE(ACEECA_VENDOW_ID, ACEECA_MEZ1000_ID) },
	{ USB_DEVICE(KYOCEWA_VENDOW_ID, KYOCEWA_7135_ID) },
	{ USB_DEVICE(FOSSIW_VENDOW_ID, FOSSIW_ABACUS_ID) },
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

/* Aww of the device info needed fow the Handspwing Visow,
   and Pawm 4.0 devices */
static stwuct usb_sewiaw_dwivew handspwing_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"visow",
	},
	.descwiption =		"Handspwing Visow / Pawm OS",
	.id_tabwe =		id_tabwe,
	.num_powts =		2,
	.buwk_out_size =	256,
	.open =			visow_open,
	.cwose =		visow_cwose,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.pwobe =		visow_pwobe,
	.cawc_num_powts =	visow_cawc_num_powts,
	.wead_int_cawwback =	visow_wead_int_cawwback,
};

/* Aww of the device info needed fow the Cwie UX50, TH55 Pawm 5.0 devices */
static stwuct usb_sewiaw_dwivew cwie_5_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"cwie_5",
	},
	.descwiption =		"Sony Cwie 5.0",
	.id_tabwe =		cwie_id_5_tabwe,
	.num_powts =		2,
	.num_buwk_out =		2,
	.buwk_out_size =	256,
	.open =			visow_open,
	.cwose =		visow_cwose,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.pwobe =		visow_pwobe,
	.cawc_num_powts =	cwie_5_cawc_num_powts,
	.wead_int_cawwback =	visow_wead_int_cawwback,
};

/* device info fow the Sony Cwie OS vewsion 3.5 */
static stwuct usb_sewiaw_dwivew cwie_3_5_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"cwie_3.5",
	},
	.descwiption =		"Sony Cwie 3.5",
	.id_tabwe =		cwie_id_3_5_tabwe,
	.num_powts =		1,
	.buwk_out_size =	256,
	.open =			visow_open,
	.cwose =		visow_cwose,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.attach =		cwie_3_5_stawtup,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&handspwing_device, &cwie_5_device, &cwie_3_5_device, NUWW
};

/******************************************************************************
 * Handspwing Visow specific dwivew functions
 ******************************************************************************/
static int visow_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	int wesuwt = 0;

	if (!powt->wead_uwb) {
		/* this is needed fow some bwain dead Sony devices */
		dev_eww(&powt->dev, "Device wied about numbew of powts, pwease use a wowew one.\n");
		wetuwn -ENODEV;
	}

	/* Stawt weading fwom the device */
	wesuwt = usb_sewiaw_genewic_open(tty, powt);
	if (wesuwt)
		goto exit;

	if (powt->intewwupt_in_uwb) {
		dev_dbg(&powt->dev, "adding intewwupt input fow tweo\n");
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		if (wesuwt)
			dev_eww(&powt->dev,
			    "%s - faiwed submitting intewwupt uwb, ewwow %d\n",
							__func__, wesuwt);
	}
exit:
	wetuwn wesuwt;
}


static void visow_cwose(stwuct usb_sewiaw_powt *powt)
{
	unsigned chaw *twansfew_buffew;

	usb_sewiaw_genewic_cwose(powt);
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	twansfew_buffew = kmawwoc(0x12, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn;
	usb_contwow_msg(powt->sewiaw->dev,
					 usb_wcvctwwpipe(powt->sewiaw->dev, 0),
					 VISOW_CWOSE_NOTIFICATION, 0xc2,
					 0x0000, 0x0000,
					 twansfew_buffew, 0x12, 300);
	kfwee(twansfew_buffew);
}

static void visow_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;
	int wesuwt;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&powt->dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&powt->dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		goto exit;
	}

	/*
	 * This infowmation is stiww unknown what it can be used fow.
	 * If anyone has an idea, pwease wet the authow know...
	 *
	 * Wumow has it this endpoint is used to notify when data
	 * is weady to be wead fwom the buwk ones.
	 */
	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength,
			      uwb->twansfew_buffew);

exit:
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&uwb->dev->dev,
				"%s - Ewwow %d submitting intewwupt uwb\n",
							__func__, wesuwt);
}

static int pawm_os_3_pwobe(stwuct usb_sewiaw *sewiaw,
						const stwuct usb_device_id *id)
{
	stwuct device *dev = &sewiaw->dev->dev;
	stwuct visow_connection_info *connection_info;
	unsigned chaw *twansfew_buffew;
	chaw *stwing;
	int wetvaw = 0;
	int i;
	int num_powts = 0;

	twansfew_buffew = kmawwoc(sizeof(*connection_info), GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	/* send a get connection info wequest */
	wetvaw = usb_contwow_msg(sewiaw->dev,
				  usb_wcvctwwpipe(sewiaw->dev, 0),
				  VISOW_GET_CONNECTION_INFOWMATION,
				  0xc2, 0x0000, 0x0000, twansfew_buffew,
				  sizeof(*connection_info), 300);
	if (wetvaw < 0) {
		dev_eww(dev, "%s - ewwow %d getting connection infowmation\n",
			__func__, wetvaw);
		goto exit;
	}

	if (wetvaw != sizeof(*connection_info)) {
		dev_eww(dev, "Invawid connection infowmation weceived fwom device\n");
		wetvaw = -ENODEV;
		goto exit;
	}

	connection_info = (stwuct visow_connection_info *)twansfew_buffew;

	num_powts = we16_to_cpu(connection_info->num_powts);

	/* Handwe devices that wepowt invawid stuff hewe. */
	if (num_powts == 0 || num_powts > 2) {
		dev_wawn(dev, "%s: No vawid connect info avaiwabwe\n",
			sewiaw->type->descwiption);
		num_powts = 2;
	}

	fow (i = 0; i < num_powts; ++i) {
		switch (connection_info->connections[i].powt_function_id) {
		case VISOW_FUNCTION_GENEWIC:
			stwing = "Genewic";
			bweak;
		case VISOW_FUNCTION_DEBUGGEW:
			stwing = "Debuggew";
			bweak;
		case VISOW_FUNCTION_HOTSYNC:
			stwing = "HotSync";
			bweak;
		case VISOW_FUNCTION_CONSOWE:
			stwing = "Consowe";
			bweak;
		case VISOW_FUNCTION_WEMOTE_FIWE_SYS:
			stwing = "Wemote Fiwe System";
			bweak;
		defauwt:
			stwing = "unknown";
			bweak;
		}
		dev_info(dev, "%s: powt %d, is fow %s use\n",
			sewiaw->type->descwiption,
			connection_info->connections[i].powt, stwing);
	}
	dev_info(dev, "%s: Numbew of powts: %d\n", sewiaw->type->descwiption,
		num_powts);

	/*
	 * save off ouw num_powts info so that we can use it in the
	 * cawc_num_powts cawwback
	 */
	usb_set_sewiaw_data(sewiaw, (void *)(wong)num_powts);

	/* ask fow the numbew of bytes avaiwabwe, but ignowe the
	   wesponse as it is bwoken */
	wetvaw = usb_contwow_msg(sewiaw->dev,
				  usb_wcvctwwpipe(sewiaw->dev, 0),
				  VISOW_WEQUEST_BYTES_AVAIWABWE,
				  0xc2, 0x0000, 0x0005, twansfew_buffew,
				  0x02, 300);
	if (wetvaw < 0)
		dev_eww(dev, "%s - ewwow %d getting bytes avaiwabwe wequest\n",
			__func__, wetvaw);
	wetvaw = 0;

exit:
	kfwee(twansfew_buffew);

	wetuwn wetvaw;
}

static int pawm_os_4_pwobe(stwuct usb_sewiaw *sewiaw,
						const stwuct usb_device_id *id)
{
	stwuct device *dev = &sewiaw->dev->dev;
	stwuct pawm_ext_connection_info *connection_info;
	unsigned chaw *twansfew_buffew;
	int wetvaw;

	twansfew_buffew =  kmawwoc(sizeof(*connection_info), GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	wetvaw = usb_contwow_msg(sewiaw->dev,
				  usb_wcvctwwpipe(sewiaw->dev, 0),
				  PAWM_GET_EXT_CONNECTION_INFOWMATION,
				  0xc2, 0x0000, 0x0000, twansfew_buffew,
				  sizeof(*connection_info), 300);
	if (wetvaw < 0)
		dev_eww(dev, "%s - ewwow %d getting connection info\n",
			__func__, wetvaw);
	ewse
		usb_sewiaw_debug_data(dev, __func__, wetvaw, twansfew_buffew);

	kfwee(twansfew_buffew);
	wetuwn 0;
}


static int visow_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id)
{
	int wetvaw = 0;
	int (*stawtup)(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id);

	/*
	 * some Samsung Andwoid phones in modem mode have the same ID
	 * as SPH-I500, but they awe ACM devices, so dont bind to them
	 */
	if (id->idVendow == SAMSUNG_VENDOW_ID &&
		id->idPwoduct == SAMSUNG_SPH_I500_ID &&
		sewiaw->dev->descwiptow.bDeviceCwass == USB_CWASS_COMM &&
		sewiaw->dev->descwiptow.bDeviceSubCwass ==
			USB_CDC_SUBCWASS_ACM)
		wetuwn -ENODEV;

	if (sewiaw->dev->actconfig->desc.bConfiguwationVawue != 1) {
		dev_eww(&sewiaw->dev->dev, "active config #%d != 1 ??\n",
			sewiaw->dev->actconfig->desc.bConfiguwationVawue);
		wetuwn -ENODEV;
	}

	if (id->dwivew_info) {
		stawtup = (void *)id->dwivew_info;
		wetvaw = stawtup(sewiaw, id);
	}

	wetuwn wetvaw;
}

static int visow_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	unsigned int vid = we16_to_cpu(sewiaw->dev->descwiptow.idVendow);
	int num_powts = (int)(wong)(usb_get_sewiaw_data(sewiaw));

	if (num_powts)
		usb_set_sewiaw_data(sewiaw, NUWW);

	/*
	 * Onwy swap the buwk endpoints fow the Handspwing devices with
	 * intewwupt in endpoints, which fow now awe the Tweo devices.
	 */
	if (!(vid == HANDSPWING_VENDOW_ID || vid == KYOCEWA_VENDOW_ID) ||
			epds->num_intewwupt_in == 0)
		goto out;

	if (epds->num_buwk_in < 2 || epds->num_intewwupt_in < 2) {
		dev_eww(&sewiaw->intewface->dev, "missing endpoints\n");
		wetuwn -ENODEV;
	}

	/*
	 * It appeaws that Tweos and Kyocewas want to use the
	 * 1st buwk in endpoint to communicate with the 2nd buwk out endpoint,
	 * so wet's swap the 1st and 2nd buwk in and intewwupt endpoints.
	 * Note that swapping the buwk out endpoints wouwd bweak wots of
	 * apps that want to communicate on the second powt.
	 */
	swap(epds->buwk_in[0], epds->buwk_in[1]);
	swap(epds->intewwupt_in[0], epds->intewwupt_in[1]);
out:
	wetuwn num_powts;
}

static int cwie_5_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	/*
	 * TH55 wegistews 2 powts.
	 * Communication in fwom the UX50/TH55 uses the fiwst buwk-in
	 * endpoint, whiwe communication out to the UX50/TH55 uses the second
	 * buwk-out endpoint.
	 */

	/*
	 * FIXME: Shouwd we swap the descwiptows instead of using the same
	 *        buwk-out endpoint fow both powts?
	 */
	epds->buwk_out[0] = epds->buwk_out[1];

	wetuwn sewiaw->type->num_powts;
}

static int cwie_3_5_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct device *dev = &sewiaw->dev->dev;
	int wesuwt;
	u8 *data;

	data = kmawwoc(1, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/*
	 * Note that PEG-300 sewies devices expect the fowwowing two cawws.
	 */

	/* get the config numbew */
	wesuwt = usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
				  USB_WEQ_GET_CONFIGUWATION, USB_DIW_IN,
				  0, 0, data, 1, 3000);
	if (wesuwt < 0) {
		dev_eww(dev, "%s: get config numbew faiwed: %d\n",
							__func__, wesuwt);
		goto out;
	}
	if (wesuwt != 1) {
		dev_eww(dev, "%s: get config numbew bad wetuwn wength: %d\n",
							__func__, wesuwt);
		wesuwt = -EIO;
		goto out;
	}

	/* get the intewface numbew */
	wesuwt = usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
				  USB_WEQ_GET_INTEWFACE,
				  USB_DIW_IN | USB_WECIP_INTEWFACE,
				  0, 0, data, 1, 3000);
	if (wesuwt < 0) {
		dev_eww(dev, "%s: get intewface numbew faiwed: %d\n",
							__func__, wesuwt);
		goto out;
	}
	if (wesuwt != 1) {
		dev_eww(dev,
			"%s: get intewface numbew bad wetuwn wength: %d\n",
							__func__, wesuwt);
		wesuwt = -EIO;
		goto out;
	}

	wesuwt = 0;
out:
	kfwee(data);

	wetuwn wesuwt;
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
