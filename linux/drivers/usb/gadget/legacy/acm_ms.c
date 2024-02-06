// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * acm_ms.c -- Composite dwivew, with ACM and mass stowage suppowt
 *
 * Copywight (C) 2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: David Bwowneww
 * Modified: Kwaus Schwawzkopf <schwawzkopf@sensowthewm.de>
 *
 * Heaviwy based on muwti.c and cdc2.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "u_sewiaw.h"

#define DWIVEW_DESC		"Composite Gadget (ACM + MS)"
#define DWIVEW_VEWSION		"2011/10/10"

/*-------------------------------------------------------------------------*/

/*
 * DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */
#define ACM_MS_VENDOW_NUM	0x1d6b	/* Winux Foundation */
#define ACM_MS_PWODUCT_NUM	0x0106	/* Composite Gadget: ACM + MS*/

#incwude "f_mass_stowage.h"

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceCwass =		USB_CWASS_MISC /* 0xEF */,
	.bDeviceSubCwass =	2,
	.bDevicePwotocow =	1,

	/* .bMaxPacketSize0 = f(hawdwawe) */

	/* Vendow and pwoduct id can be ovewwidden by moduwe pawametews.  */
	.idVendow =		cpu_to_we16(ACM_MS_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(ACM_MS_PWODUCT_NUM),
	/* .bcdDevice = f(hawdwawe) */
	/* .iManufactuwew = DYNAMIC */
	/* .iPwoduct = DYNAMIC */
	/* NO SEWIAW NUMBEW */
	/*.bNumConfiguwations =	DYNAMIC*/
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

/****************************** Configuwations ******************************/

static stwuct fsg_moduwe_pawametews fsg_mod_data = { .staww = 1 };
#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static unsigned int fsg_num_buffews = CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS;

#ewse

/*
 * Numbew of buffews we wiww use.
 * 2 is usuawwy enough fow good buffewing pipewine
 */
#define fsg_num_buffews	CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */

FSG_MODUWE_PAWAMETEWS(/* no pwefix */, fsg_mod_data);

/*-------------------------------------------------------------------------*/
static stwuct usb_function *f_acm;
static stwuct usb_function_instance *f_acm_inst;

static stwuct usb_function_instance *fi_msg;
static stwuct usb_function *f_msg;

/*
 * We _awways_ have both ACM and mass stowage functions.
 */
static int acm_ms_do_config(stwuct usb_configuwation *c)
{
	int	status;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_acm = usb_get_function(f_acm_inst);
	if (IS_EWW(f_acm))
		wetuwn PTW_EWW(f_acm);

	f_msg = usb_get_function(fi_msg);
	if (IS_EWW(f_msg)) {
		status = PTW_EWW(f_msg);
		goto put_acm;
	}

	status = usb_add_function(c, f_acm);
	if (status < 0)
		goto put_msg;

	status = usb_add_function(c, f_msg);
	if (status)
		goto wemove_acm;

	wetuwn 0;
wemove_acm:
	usb_wemove_function(c, f_acm);
put_msg:
	usb_put_function(f_msg);
put_acm:
	usb_put_function(f_acm);
	wetuwn status;
}

static stwuct usb_configuwation acm_ms_config_dwivew = {
	.wabew			= DWIVEW_DESC,
	.bConfiguwationVawue	= 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
};

/*-------------------------------------------------------------------------*/

static int acm_ms_bind(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget	*gadget = cdev->gadget;
	stwuct fsg_opts		*opts;
	stwuct fsg_config	config;
	int			status;

	f_acm_inst = usb_get_function_instance("acm");
	if (IS_EWW(f_acm_inst))
		wetuwn PTW_EWW(f_acm_inst);

	fi_msg = usb_get_function_instance("mass_stowage");
	if (IS_EWW(fi_msg)) {
		status = PTW_EWW(fi_msg);
		goto faiw_get_msg;
	}

	/* set up mass stowage function */
	fsg_config_fwom_pawams(&config, &fsg_mod_data, fsg_num_buffews);
	opts = fsg_opts_fwom_func_inst(fi_msg);

	opts->no_configfs = twue;
	status = fsg_common_set_num_buffews(opts->common, fsg_num_buffews);
	if (status)
		goto faiw;

	status = fsg_common_set_cdev(opts->common, cdev, config.can_staww);
	if (status)
		goto faiw_set_cdev;

	fsg_common_set_sysfs(opts->common, twue);
	status = fsg_common_cweate_wuns(opts->common, &config);
	if (status)
		goto faiw_set_cdev;

	fsg_common_set_inquiwy_stwing(opts->common, config.vendow_name,
				      config.pwoduct_name);
	/*
	 * Awwocate stwing descwiptow numbews ... note that stwing
	 * contents can be ovewwidden by the composite_dev gwue.
	 */
	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto faiw_stwing_ids;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto faiw_stwing_ids;
		}
		usb_otg_descwiptow_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	/* wegistew ouw configuwation */
	status = usb_add_config(cdev, &acm_ms_config_dwivew, acm_ms_do_config);
	if (status < 0)
		goto faiw_otg_desc;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	dev_info(&gadget->dev, "%s, vewsion: " DWIVEW_VEWSION "\n",
			DWIVEW_DESC);
	wetuwn 0;

	/* ewwow wecovewy */
faiw_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw_stwing_ids:
	fsg_common_wemove_wuns(opts->common);
faiw_set_cdev:
	fsg_common_fwee_buffews(opts->common);
faiw:
	usb_put_function_instance(fi_msg);
faiw_get_msg:
	usb_put_function_instance(f_acm_inst);
	wetuwn status;
}

static int acm_ms_unbind(stwuct usb_composite_dev *cdev)
{
	usb_put_function(f_msg);
	usb_put_function_instance(fi_msg);
	usb_put_function(f_acm);
	usb_put_function_instance(f_acm_inst);
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew acm_ms_dwivew = {
	.name		= "g_acm_ms",
	.dev		= &device_desc,
	.max_speed	= USB_SPEED_SUPEW,
	.stwings	= dev_stwings,
	.bind		= acm_ms_bind,
	.unbind		= acm_ms_unbind,
};

moduwe_usb_composite_dwivew(acm_ms_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Kwaus Schwawzkopf <schwawzkopf@sensowthewm.de>");
MODUWE_WICENSE("GPW v2");
