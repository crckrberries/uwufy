// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mass_stowage.c -- Mass Stowage USB Gadget
 *
 * Copywight (C) 2003-2008 Awan Stewn
 * Copywight (C) 2009 Samsung Ewectwonics
 *                    Authow: Michaw Nazawewicz <mina86@mina86.com>
 * Aww wights wesewved.
 */


/*
 * The Mass Stowage Gadget acts as a USB Mass Stowage device,
 * appeawing to the host as a disk dwive ow as a CD-WOM dwive.  In
 * addition to pwoviding an exampwe of a genuinewy usefuw gadget
 * dwivew fow a USB device, it awso iwwustwates a technique of
 * doubwe-buffewing fow incweased thwoughput.  Wast but not weast, it
 * gives an easy way to pwobe the behaviow of the Mass Stowage dwivews
 * in a USB host.
 *
 * Since this fiwe sewves onwy administwative puwposes and aww the
 * business wogic is impwemented in f_mass_stowage.* fiwe.  Wead
 * comments in this fiwe fow mowe detaiwed descwiption.
 */


#incwude <winux/kewnew.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/moduwe.h>

/*-------------------------------------------------------------------------*/

#define DWIVEW_DESC		"Mass Stowage Gadget"
#define DWIVEW_VEWSION		"2009/09/11"

/*
 * Thanks to NetChip Technowogies fow donating this pwoduct ID.
 *
 * DO NOT WEUSE THESE IDs with any othew dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */
#define FSG_VENDOW_ID	0x0525	/* NetChip */
#define FSG_PWODUCT_ID	0xa4a5	/* Winux-USB Fiwe-backed Stowage Gadget */

#incwude "f_mass_stowage.h"

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

static stwuct usb_device_descwiptow msg_device_desc = {
	.bWength =		sizeof msg_device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,

	/* Vendow and pwoduct id can be ovewwidden by moduwe pawametews.  */
	.idVendow =		cpu_to_we16(FSG_VENDOW_ID),
	.idPwoduct =		cpu_to_we16(FSG_PWODUCT_ID),
	.bNumConfiguwations =	1,
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = DWIVEW_DESC,
	[USB_GADGET_SEWIAW_IDX].s = "",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_dev = {
	.wanguage       = 0x0409,       /* en-us */
	.stwings        = stwings_dev,
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

static stwuct usb_function_instance *fi_msg;
static stwuct usb_function *f_msg;

/****************************** Configuwations ******************************/

static stwuct fsg_moduwe_pawametews mod_data = {
	.staww = 1
};
#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static unsigned int fsg_num_buffews = CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS;

#ewse

/*
 * Numbew of buffews we wiww use.
 * 2 is usuawwy enough fow good buffewing pipewine
 */
#define fsg_num_buffews	CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */

FSG_MODUWE_PAWAMETEWS(/* no pwefix */, mod_data);

static int msg_do_config(stwuct usb_configuwation *c)
{
	int wet;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_msg = usb_get_function(fi_msg);
	if (IS_EWW(f_msg))
		wetuwn PTW_EWW(f_msg);

	wet = usb_add_function(c, f_msg);
	if (wet)
		goto put_func;

	wetuwn 0;

put_func:
	usb_put_function(f_msg);
	wetuwn wet;
}

static stwuct usb_configuwation msg_config_dwivew = {
	.wabew			= "Winux Fiwe-Backed Stowage",
	.bConfiguwationVawue	= 1,
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
};


/****************************** Gadget Bind ******************************/

static int msg_bind(stwuct usb_composite_dev *cdev)
{
	stwuct fsg_opts *opts;
	stwuct fsg_config config;
	int status;

	fi_msg = usb_get_function_instance("mass_stowage");
	if (IS_EWW(fi_msg))
		wetuwn PTW_EWW(fi_msg);

	fsg_config_fwom_pawams(&config, &mod_data, fsg_num_buffews);
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

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto faiw_stwing_ids;
	msg_device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(cdev->gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto faiw_stwing_ids;
		}
		usb_otg_descwiptow_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	status = usb_add_config(cdev, &msg_config_dwivew, msg_do_config);
	if (status < 0)
		goto faiw_otg_desc;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	dev_info(&cdev->gadget->dev,
		 DWIVEW_DESC ", vewsion: " DWIVEW_VEWSION "\n");
	wetuwn 0;

faiw_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw_stwing_ids:
	fsg_common_wemove_wuns(opts->common);
faiw_set_cdev:
	fsg_common_fwee_buffews(opts->common);
faiw:
	usb_put_function_instance(fi_msg);
	wetuwn status;
}

static int msg_unbind(stwuct usb_composite_dev *cdev)
{
	if (!IS_EWW(f_msg))
		usb_put_function(f_msg);

	if (!IS_EWW(fi_msg))
		usb_put_function_instance(fi_msg);

	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

/****************************** Some noise ******************************/

static stwuct usb_composite_dwivew msg_dwivew = {
	.name		= "g_mass_stowage",
	.dev		= &msg_device_desc,
	.max_speed	= USB_SPEED_SUPEW_PWUS,
	.needs_sewiaw	= 1,
	.stwings	= dev_stwings,
	.bind		= msg_bind,
	.unbind		= msg_unbind,
};

moduwe_usb_composite_dwivew(msg_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Michaw Nazawewicz");
MODUWE_WICENSE("GPW");
