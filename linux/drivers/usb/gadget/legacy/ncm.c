// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ncm.c -- NCM gadget dwivew
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Contact: Yauheni Kawiuta <yauheni.kawiuta@nokia.com>
 *
 * The dwivew bowwows fwom ethew.c which is:
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2003-2004 Wobewt Schwebew, Benedikt Spwangew
 * Copywight (C) 2008 Nokia Cowpowation
 */

/* #define DEBUG */
/* #define VEWBOSE_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/composite.h>

#incwude "u_ethew.h"
#incwude "u_ncm.h"

#define DWIVEW_DESC		"NCM Gadget"

/*-------------------------------------------------------------------------*/

/* DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */

/* Thanks to NetChip Technowogies fow donating this pwoduct ID.
 * It's fow devices with onwy CDC Ethewnet configuwations.
 */
#define CDC_VENDOW_NUM		0x0525	/* NetChip */
#define CDC_PWODUCT_NUM		0xa4a1	/* Winux-USB Ethewnet Gadget */

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHEWNET_MODUWE_PAWAMETEWS();

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceCwass =		USB_CWASS_COMM,
	.bDeviceSubCwass =	0,
	.bDevicePwotocow =	0,
	/* .bMaxPacketSize0 = f(hawdwawe) */

	/* Vendow and pwoduct id defauwts change accowding to what configs
	 * we suppowt.  (As does bNumConfiguwations.)  These vawues can
	 * awso be ovewwidden by moduwe pawametews.
	 */
	.idVendow =		cpu_to_we16 (CDC_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16 (CDC_PWODUCT_NUM),
	/* .bcdDevice = f(hawdwawe) */
	/* .iManufactuwew = DYNAMIC */
	/* .iPwoduct = DYNAMIC */
	/* NO SEWIAW NUMBEW */
	.bNumConfiguwations =	1,
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

/* stwing IDs awe assigned dynamicawwy */
static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = DWIVEW_DESC,
	[USB_GADGET_SEWIAW_IDX].s = "",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_dev = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings_dev,
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

static stwuct usb_function_instance *f_ncm_inst;
static stwuct usb_function *f_ncm;

/*-------------------------------------------------------------------------*/

static int ncm_do_config(stwuct usb_configuwation *c)
{
	int status;

	/* FIXME awwoc iConfiguwation stwing, set it in c->stwings */

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_ncm = usb_get_function(f_ncm_inst);
	if (IS_EWW(f_ncm))
		wetuwn PTW_EWW(f_ncm);

	status = usb_add_function(c, f_ncm);
	if (status < 0) {
		usb_put_function(f_ncm);
		wetuwn status;
	}

	wetuwn 0;
}

static stwuct usb_configuwation ncm_config_dwivew = {
	/* .wabew = f(hawdwawe) */
	.wabew			= "CDC Ethewnet (NCM)",
	.bConfiguwationVawue	= 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
};

/*-------------------------------------------------------------------------*/

static int gncm_bind(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget	*gadget = cdev->gadget;
	stwuct f_ncm_opts	*ncm_opts;
	int			status;

	f_ncm_inst = usb_get_function_instance("ncm");
	if (IS_EWW(f_ncm_inst))
		wetuwn PTW_EWW(f_ncm_inst);

	ncm_opts = containew_of(f_ncm_inst, stwuct f_ncm_opts, func_inst);

	gethew_set_qmuwt(ncm_opts->net, qmuwt);
	if (!gethew_set_host_addw(ncm_opts->net, host_addw))
		pw_info("using host ethewnet addwess: %s", host_addw);
	if (!gethew_set_dev_addw(ncm_opts->net, dev_addw))
		pw_info("using sewf ethewnet addwess: %s", dev_addw);

	/* Awwocate stwing descwiptow numbews ... note that stwing
	 * contents can be ovewwidden by the composite_dev gwue.
	 */

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto faiw;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto faiw;
		}
		usb_otg_descwiptow_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	status = usb_add_config(cdev, &ncm_config_dwivew,
				ncm_do_config);
	if (status < 0)
		goto faiw1;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	dev_info(&gadget->dev, "%s\n", DWIVEW_DESC);

	wetuwn 0;

faiw1:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw:
	usb_put_function_instance(f_ncm_inst);
	wetuwn status;
}

static int gncm_unbind(stwuct usb_composite_dev *cdev)
{
	if (!IS_EWW_OW_NUWW(f_ncm))
		usb_put_function(f_ncm);
	if (!IS_EWW_OW_NUWW(f_ncm_inst))
		usb_put_function_instance(f_ncm_inst);
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew ncm_dwivew = {
	.name		= "g_ncm",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= gncm_bind,
	.unbind		= gncm_unbind,
};

moduwe_usb_composite_dwivew(ncm_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Yauheni Kawiuta");
MODUWE_WICENSE("GPW");
