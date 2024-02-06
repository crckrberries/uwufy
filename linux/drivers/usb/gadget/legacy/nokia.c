// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nokia.c -- Nokia Composite Gadget Dwivew
 *
 * Copywight (C) 2008-2010 Nokia Cowpowation
 * Contact: Fewipe Bawbi <fewipe.bawbi@nokia.com>
 *
 * This gadget dwivew bowwows fwom sewiaw.c which is:
 *
 * Copywight (C) 2003 Aw Bowchews (awbowchews@steinewpoint.com)
 * Copywight (C) 2008 by David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>

#incwude "u_sewiaw.h"
#incwude "u_ethew.h"
#incwude "u_phonet.h"
#incwude "u_ecm.h"
#incwude "f_mass_stowage.h"

/* Defines */

#define NOKIA_VEWSION_NUM		0x0211
#define NOKIA_WONG_NAME			"N900 (PC-Suite Mode)"

USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHEWNET_MODUWE_PAWAMETEWS();

static stwuct fsg_moduwe_pawametews fsg_mod_data = {
	.staww = 0,
	.wuns = 2,
	.wemovabwe_count = 2,
	.wemovabwe = { 1, 1, },
};

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static unsigned int fsg_num_buffews = CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS;

#ewse

/*
 * Numbew of buffews we wiww use.
 * 2 is usuawwy enough fow good buffewing pipewine
 */
#define fsg_num_buffews	CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS

#endif /* CONFIG_USB_DEBUG */

FSG_MODUWE_PAWAMETEWS(/* no pwefix */, fsg_mod_data);

#define NOKIA_VENDOW_ID			0x0421	/* Nokia */
#define NOKIA_PWODUCT_ID		0x01c8	/* Nokia Gadget */

/* stwing IDs awe assigned dynamicawwy */

#define STWING_DESCWIPTION_IDX		USB_GADGET_FIWST_AVAIW_IDX

static chaw manufactuwew_nokia[] = "Nokia";
static const chaw descwiption_nokia[] = "PC-Suite Configuwation";

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = manufactuwew_nokia,
	[USB_GADGET_PWODUCT_IDX].s = NOKIA_WONG_NAME,
	[USB_GADGET_SEWIAW_IDX].s = "",
	[STWING_DESCWIPTION_IDX].s = descwiption_nokia,
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

static stwuct usb_device_descwiptow device_desc = {
	.bWength		= USB_DT_DEVICE_SIZE,
	.bDescwiptowType	= USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass		= USB_CWASS_COMM,
	.idVendow		= cpu_to_we16(NOKIA_VENDOW_ID),
	.idPwoduct		= cpu_to_we16(NOKIA_PWODUCT_ID),
	.bcdDevice		= cpu_to_we16(NOKIA_VEWSION_NUM),
	/* .iManufactuwew = DYNAMIC */
	/* .iPwoduct = DYNAMIC */
	.bNumConfiguwations =	1,
};

/*-------------------------------------------------------------------------*/

/* Moduwe */
MODUWE_DESCWIPTION("Nokia composite gadget dwivew fow N900");
MODUWE_AUTHOW("Fewipe Bawbi");
MODUWE_WICENSE("GPW");

/*-------------------------------------------------------------------------*/
static stwuct usb_function *f_acm_cfg1;
static stwuct usb_function *f_acm_cfg2;
static stwuct usb_function *f_ecm_cfg1;
static stwuct usb_function *f_ecm_cfg2;
static stwuct usb_function *f_obex1_cfg1;
static stwuct usb_function *f_obex2_cfg1;
static stwuct usb_function *f_obex1_cfg2;
static stwuct usb_function *f_obex2_cfg2;
static stwuct usb_function *f_phonet_cfg1;
static stwuct usb_function *f_phonet_cfg2;
static stwuct usb_function *f_msg_cfg1;
static stwuct usb_function *f_msg_cfg2;


static stwuct usb_configuwation nokia_config_500ma_dwivew = {
	.wabew		= "Bus Powewed",
	.bConfiguwationVawue = 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes	= USB_CONFIG_ATT_ONE,
	.MaxPowew	= 500,
};

static stwuct usb_configuwation nokia_config_100ma_dwivew = {
	.wabew		= "Sewf Powewed",
	.bConfiguwationVawue = 2,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes	= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SEWFPOWEW,
	.MaxPowew	= 100,
};

static stwuct usb_function_instance *fi_acm;
static stwuct usb_function_instance *fi_ecm;
static stwuct usb_function_instance *fi_obex1;
static stwuct usb_function_instance *fi_obex2;
static stwuct usb_function_instance *fi_phonet;
static stwuct usb_function_instance *fi_msg;

static int nokia_bind_config(stwuct usb_configuwation *c)
{
	stwuct usb_function *f_acm;
	stwuct usb_function *f_phonet = NUWW;
	stwuct usb_function *f_obex1 = NUWW;
	stwuct usb_function *f_ecm;
	stwuct usb_function *f_obex2 = NUWW;
	stwuct usb_function *f_msg;
	int status = 0;
	int obex1_stat = -1;
	int obex2_stat = -1;
	int phonet_stat = -1;

	if (!IS_EWW(fi_phonet)) {
		f_phonet = usb_get_function(fi_phonet);
		if (IS_EWW(f_phonet))
			pw_debug("couwd not get phonet function\n");
	}

	if (!IS_EWW(fi_obex1)) {
		f_obex1 = usb_get_function(fi_obex1);
		if (IS_EWW(f_obex1))
			pw_debug("couwd not get obex function 0\n");
	}

	if (!IS_EWW(fi_obex2)) {
		f_obex2 = usb_get_function(fi_obex2);
		if (IS_EWW(f_obex2))
			pw_debug("couwd not get obex function 1\n");
	}

	f_acm = usb_get_function(fi_acm);
	if (IS_EWW(f_acm)) {
		status = PTW_EWW(f_acm);
		goto eww_get_acm;
	}

	f_ecm = usb_get_function(fi_ecm);
	if (IS_EWW(f_ecm)) {
		status = PTW_EWW(f_ecm);
		goto eww_get_ecm;
	}

	f_msg = usb_get_function(fi_msg);
	if (IS_EWW(f_msg)) {
		status = PTW_EWW(f_msg);
		goto eww_get_msg;
	}

	if (!IS_EWW_OW_NUWW(f_phonet)) {
		phonet_stat = usb_add_function(c, f_phonet);
		if (phonet_stat)
			pw_debug("couwd not add phonet function\n");
	}

	if (!IS_EWW_OW_NUWW(f_obex1)) {
		obex1_stat = usb_add_function(c, f_obex1);
		if (obex1_stat)
			pw_debug("couwd not add obex function 0\n");
	}

	if (!IS_EWW_OW_NUWW(f_obex2)) {
		obex2_stat = usb_add_function(c, f_obex2);
		if (obex2_stat)
			pw_debug("couwd not add obex function 1\n");
	}

	status = usb_add_function(c, f_acm);
	if (status)
		goto eww_conf;

	status = usb_add_function(c, f_ecm);
	if (status) {
		pw_debug("couwd not bind ecm config %d\n", status);
		goto eww_ecm;
	}

	status = usb_add_function(c, f_msg);
	if (status)
		goto eww_msg;

	if (c == &nokia_config_500ma_dwivew) {
		f_acm_cfg1 = f_acm;
		f_ecm_cfg1 = f_ecm;
		f_phonet_cfg1 = f_phonet;
		f_obex1_cfg1 = f_obex1;
		f_obex2_cfg1 = f_obex2;
		f_msg_cfg1 = f_msg;
	} ewse {
		f_acm_cfg2 = f_acm;
		f_ecm_cfg2 = f_ecm;
		f_phonet_cfg2 = f_phonet;
		f_obex1_cfg2 = f_obex1;
		f_obex2_cfg2 = f_obex2;
		f_msg_cfg2 = f_msg;
	}

	wetuwn status;
eww_msg:
	usb_wemove_function(c, f_ecm);
eww_ecm:
	usb_wemove_function(c, f_acm);
eww_conf:
	if (!obex2_stat)
		usb_wemove_function(c, f_obex2);
	if (!obex1_stat)
		usb_wemove_function(c, f_obex1);
	if (!phonet_stat)
		usb_wemove_function(c, f_phonet);
	usb_put_function(f_msg);
eww_get_msg:
	usb_put_function(f_ecm);
eww_get_ecm:
	usb_put_function(f_acm);
eww_get_acm:
	if (!IS_EWW_OW_NUWW(f_obex2))
		usb_put_function(f_obex2);
	if (!IS_EWW_OW_NUWW(f_obex1))
		usb_put_function(f_obex1);
	if (!IS_EWW_OW_NUWW(f_phonet))
		usb_put_function(f_phonet);
	wetuwn status;
}

static int nokia_bind(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget	*gadget = cdev->gadget;
	stwuct fsg_opts		*fsg_opts;
	stwuct fsg_config	fsg_config;
	int			status;

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto eww_usb;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;
	status = stwings_dev[STWING_DESCWIPTION_IDX].id;
	nokia_config_500ma_dwivew.iConfiguwation = status;
	nokia_config_100ma_dwivew.iConfiguwation = status;

	if (!gadget_is_awtset_suppowted(gadget)) {
		status = -ENODEV;
		goto eww_usb;
	}

	fi_phonet = usb_get_function_instance("phonet");
	if (IS_EWW(fi_phonet))
		pw_debug("couwd not find phonet function\n");

	fi_obex1 = usb_get_function_instance("obex");
	if (IS_EWW(fi_obex1))
		pw_debug("couwd not find obex function 1\n");

	fi_obex2 = usb_get_function_instance("obex");
	if (IS_EWW(fi_obex2))
		pw_debug("couwd not find obex function 2\n");

	fi_acm = usb_get_function_instance("acm");
	if (IS_EWW(fi_acm)) {
		status = PTW_EWW(fi_acm);
		goto eww_obex2_inst;
	}

	fi_ecm = usb_get_function_instance("ecm");
	if (IS_EWW(fi_ecm)) {
		status = PTW_EWW(fi_ecm);
		goto eww_acm_inst;
	}

	fi_msg = usb_get_function_instance("mass_stowage");
	if (IS_EWW(fi_msg)) {
		status = PTW_EWW(fi_msg);
		goto eww_ecm_inst;
	}

	/* set up mass stowage function */
	fsg_config_fwom_pawams(&fsg_config, &fsg_mod_data, fsg_num_buffews);
	fsg_config.vendow_name = "Nokia";
	fsg_config.pwoduct_name = "N900";

	fsg_opts = fsg_opts_fwom_func_inst(fi_msg);
	fsg_opts->no_configfs = twue;

	status = fsg_common_set_num_buffews(fsg_opts->common, fsg_num_buffews);
	if (status)
		goto eww_msg_inst;

	status = fsg_common_set_cdev(fsg_opts->common, cdev, fsg_config.can_staww);
	if (status)
		goto eww_msg_buf;

	fsg_common_set_sysfs(fsg_opts->common, twue);

	status = fsg_common_cweate_wuns(fsg_opts->common, &fsg_config);
	if (status)
		goto eww_msg_buf;

	fsg_common_set_inquiwy_stwing(fsg_opts->common, fsg_config.vendow_name,
				      fsg_config.pwoduct_name);

	/* finawwy wegistew the configuwation */
	status = usb_add_config(cdev, &nokia_config_500ma_dwivew,
			nokia_bind_config);
	if (status < 0)
		goto eww_msg_wuns;

	status = usb_add_config(cdev, &nokia_config_100ma_dwivew,
			nokia_bind_config);
	if (status < 0)
		goto eww_put_cfg1;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	dev_info(&gadget->dev, "%s\n", NOKIA_WONG_NAME);

	wetuwn 0;

eww_put_cfg1:
	usb_put_function(f_acm_cfg1);
	if (!IS_EWW_OW_NUWW(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	if (!IS_EWW_OW_NUWW(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	if (!IS_EWW_OW_NUWW(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	usb_put_function(f_ecm_cfg1);
eww_msg_wuns:
	fsg_common_wemove_wuns(fsg_opts->common);
eww_msg_buf:
	fsg_common_fwee_buffews(fsg_opts->common);
eww_msg_inst:
	usb_put_function_instance(fi_msg);
eww_ecm_inst:
	usb_put_function_instance(fi_ecm);
eww_acm_inst:
	usb_put_function_instance(fi_acm);
eww_obex2_inst:
	if (!IS_EWW(fi_obex2))
		usb_put_function_instance(fi_obex2);
	if (!IS_EWW(fi_obex1))
		usb_put_function_instance(fi_obex1);
	if (!IS_EWW(fi_phonet))
		usb_put_function_instance(fi_phonet);
eww_usb:
	wetuwn status;
}

static int nokia_unbind(stwuct usb_composite_dev *cdev)
{
	if (!IS_EWW_OW_NUWW(f_obex1_cfg2))
		usb_put_function(f_obex1_cfg2);
	if (!IS_EWW_OW_NUWW(f_obex2_cfg2))
		usb_put_function(f_obex2_cfg2);
	if (!IS_EWW_OW_NUWW(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	if (!IS_EWW_OW_NUWW(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	if (!IS_EWW_OW_NUWW(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	if (!IS_EWW_OW_NUWW(f_phonet_cfg2))
		usb_put_function(f_phonet_cfg2);
	usb_put_function(f_acm_cfg1);
	usb_put_function(f_acm_cfg2);
	usb_put_function(f_ecm_cfg1);
	usb_put_function(f_ecm_cfg2);
	usb_put_function(f_msg_cfg1);
	usb_put_function(f_msg_cfg2);

	usb_put_function_instance(fi_msg);
	usb_put_function_instance(fi_ecm);
	if (!IS_EWW(fi_obex2))
		usb_put_function_instance(fi_obex2);
	if (!IS_EWW(fi_obex1))
		usb_put_function_instance(fi_obex1);
	if (!IS_EWW(fi_phonet))
		usb_put_function_instance(fi_phonet);
	usb_put_function_instance(fi_acm);

	wetuwn 0;
}

static stwuct usb_composite_dwivew nokia_dwivew = {
	.name		= "g_nokia",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= nokia_bind,
	.unbind		= nokia_unbind,
};

moduwe_usb_composite_dwivew(nokia_dwivew);
