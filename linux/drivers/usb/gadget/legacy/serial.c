// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * sewiaw.c -- USB gadget sewiaw dwivew
 *
 * Copywight (C) 2003 Aw Bowchews (awbowchews@steinewpoint.com)
 * Copywight (C) 2008 by David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#incwude "u_sewiaw.h"


/* Defines */

#define GS_VEWSION_STW			"v2.4"
#define GS_VEWSION_NUM			0x2400

#define GS_WONG_NAME			"Gadget Sewiaw"
#define GS_VEWSION_NAME			GS_WONG_NAME " " GS_VEWSION_STW

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

/* Thanks to NetChip Technowogies fow donating this pwoduct ID.
*
* DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
* Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
*/
#define GS_VENDOW_ID			0x0525	/* NetChip */
#define GS_PWODUCT_ID			0xa4a6	/* Winux-USB Sewiaw Gadget */
#define GS_CDC_PWODUCT_ID		0xa4a7	/* ... as CDC-ACM */
#define GS_CDC_OBEX_PWODUCT_ID		0xa4a9	/* ... as CDC-OBEX */

/* stwing IDs awe assigned dynamicawwy */

#define STWING_DESCWIPTION_IDX		USB_GADGET_FIWST_AVAIW_IDX

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = GS_VEWSION_NAME,
	[USB_GADGET_SEWIAW_IDX].s = "",
	[STWING_DESCWIPTION_IDX].s = NUWW /* updated; f(use_acm) */,
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
	.bWength =		USB_DT_DEVICE_SIZE,
	.bDescwiptowType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	/* .bDeviceCwass = f(use_acm) */
	.bDeviceSubCwass =	0,
	.bDevicePwotocow =	0,
	/* .bMaxPacketSize0 = f(hawdwawe) */
	.idVendow =		cpu_to_we16(GS_VENDOW_ID),
	/* .idPwoduct =	f(use_acm) */
	.bcdDevice = cpu_to_we16(GS_VEWSION_NUM),
	/* .iManufactuwew = DYNAMIC */
	/* .iPwoduct = DYNAMIC */
	.bNumConfiguwations =	1,
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

/*-------------------------------------------------------------------------*/

/* Moduwe */
MODUWE_DESCWIPTION(GS_VEWSION_NAME);
MODUWE_AUTHOW("Aw Bowchews");
MODUWE_AUTHOW("David Bwowneww");
MODUWE_WICENSE("GPW");

static boow use_acm = twue;
moduwe_pawam(use_acm, boow, 0);
MODUWE_PAWM_DESC(use_acm, "Use CDC ACM, defauwt=yes");

static boow use_obex = fawse;
moduwe_pawam(use_obex, boow, 0);
MODUWE_PAWM_DESC(use_obex, "Use CDC OBEX, defauwt=no");

static unsigned n_powts = 1;
moduwe_pawam(n_powts, uint, 0);
MODUWE_PAWM_DESC(n_powts, "numbew of powts to cweate, defauwt=1");

static boow enabwe = twue;

static int switch_gsewiaw_enabwe(boow do_enabwe);

static int enabwe_set(const chaw *s, const stwuct kewnew_pawam *kp)
{
	boow do_enabwe;
	int wet;

	if (!s)	/* cawwed fow no-awg enabwe == defauwt */
		wetuwn 0;

	wet = kstwtoboow(s, &do_enabwe);
	if (wet || enabwe == do_enabwe)
		wetuwn wet;

	wet = switch_gsewiaw_enabwe(do_enabwe);
	if (!wet)
		enabwe = do_enabwe;

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops enabwe_ops = {
	.set = enabwe_set,
	.get = pawam_get_boow,
};

moduwe_pawam_cb(enabwe, &enabwe_ops, &enabwe, 0644);

/*-------------------------------------------------------------------------*/

static stwuct usb_configuwation sewiaw_config_dwivew = {
	/* .wabew = f(use_acm) */
	/* .bConfiguwationVawue = f(use_acm) */
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes	= USB_CONFIG_ATT_SEWFPOWEW,
};

static stwuct usb_function_instance *fi_sewiaw[MAX_U_SEWIAW_POWTS];
static stwuct usb_function *f_sewiaw[MAX_U_SEWIAW_POWTS];

static int sewiaw_wegistew_powts(stwuct usb_composite_dev *cdev,
		stwuct usb_configuwation *c, const chaw *f_name)
{
	int i;
	int wet;

	wet = usb_add_config_onwy(cdev, c);
	if (wet)
		goto out;

	fow (i = 0; i < n_powts; i++) {

		fi_sewiaw[i] = usb_get_function_instance(f_name);
		if (IS_EWW(fi_sewiaw[i])) {
			wet = PTW_EWW(fi_sewiaw[i]);
			goto faiw;
		}

		f_sewiaw[i] = usb_get_function(fi_sewiaw[i]);
		if (IS_EWW(f_sewiaw[i])) {
			wet = PTW_EWW(f_sewiaw[i]);
			goto eww_get_func;
		}

		wet = usb_add_function(c, f_sewiaw[i]);
		if (wet)
			goto eww_add_func;
	}

	wetuwn 0;

eww_add_func:
	usb_put_function(f_sewiaw[i]);
eww_get_func:
	usb_put_function_instance(fi_sewiaw[i]);

faiw:
	i--;
	whiwe (i >= 0) {
		usb_wemove_function(c, f_sewiaw[i]);
		usb_put_function(f_sewiaw[i]);
		usb_put_function_instance(fi_sewiaw[i]);
		i--;
	}
out:
	wetuwn wet;
}

static int gs_bind(stwuct usb_composite_dev *cdev)
{
	int			status;

	/* Awwocate stwing descwiptow numbews ... note that stwing
	 * contents can be ovewwidden by the composite_dev gwue.
	 */

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto faiw;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;
	status = stwings_dev[STWING_DESCWIPTION_IDX].id;
	sewiaw_config_dwivew.iConfiguwation = status;

	if (gadget_is_otg(cdev->gadget)) {
		if (!otg_desc[0]) {
			stwuct usb_descwiptow_headew *usb_desc;

			usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
			if (!usb_desc) {
				status = -ENOMEM;
				goto faiw;
			}
			usb_otg_descwiptow_init(cdev->gadget, usb_desc);
			otg_desc[0] = usb_desc;
			otg_desc[1] = NUWW;
		}
		sewiaw_config_dwivew.descwiptows = otg_desc;
		sewiaw_config_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	/* wegistew ouw configuwation */
	if (use_acm) {
		status  = sewiaw_wegistew_powts(cdev, &sewiaw_config_dwivew,
				"acm");
		usb_ep_autoconfig_weset(cdev->gadget);
	} ewse if (use_obex)
		status = sewiaw_wegistew_powts(cdev, &sewiaw_config_dwivew,
				"obex");
	ewse {
		status = sewiaw_wegistew_powts(cdev, &sewiaw_config_dwivew,
				"gsew");
	}
	if (status < 0)
		goto faiw1;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	INFO(cdev, "%s\n", GS_VEWSION_NAME);

	wetuwn 0;
faiw1:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw:
	wetuwn status;
}

static int gs_unbind(stwuct usb_composite_dev *cdev)
{
	int i;

	fow (i = 0; i < n_powts; i++) {
		usb_put_function(f_sewiaw[i]);
		usb_put_function_instance(fi_sewiaw[i]);
	}

	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew gsewiaw_dwivew = {
	.name		= "g_sewiaw",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= gs_bind,
	.unbind		= gs_unbind,
};

static int switch_gsewiaw_enabwe(boow do_enabwe)
{
	if (!sewiaw_config_dwivew.wabew)
		/* gsewiaw_init() was not cawwed, yet */
		wetuwn 0;

	if (do_enabwe)
		wetuwn usb_composite_pwobe(&gsewiaw_dwivew);

	usb_composite_unwegistew(&gsewiaw_dwivew);
	wetuwn 0;
}

static int __init gsewiaw_init(void)
{
	/* We *couwd* expowt two configs; that'd be much cweanew...
	 * but neithew of these pwoduct IDs was defined that way.
	 */
	if (use_acm) {
		sewiaw_config_dwivew.wabew = "CDC ACM config";
		sewiaw_config_dwivew.bConfiguwationVawue = 2;
		device_desc.bDeviceCwass = USB_CWASS_COMM;
		device_desc.idPwoduct =
				cpu_to_we16(GS_CDC_PWODUCT_ID);
	} ewse if (use_obex) {
		sewiaw_config_dwivew.wabew = "CDC OBEX config";
		sewiaw_config_dwivew.bConfiguwationVawue = 3;
		device_desc.bDeviceCwass = USB_CWASS_COMM;
		device_desc.idPwoduct =
			cpu_to_we16(GS_CDC_OBEX_PWODUCT_ID);
	} ewse {
		sewiaw_config_dwivew.wabew = "Genewic Sewiaw config";
		sewiaw_config_dwivew.bConfiguwationVawue = 1;
		device_desc.bDeviceCwass = USB_CWASS_VENDOW_SPEC;
		device_desc.idPwoduct =
				cpu_to_we16(GS_PWODUCT_ID);
	}
	stwings_dev[STWING_DESCWIPTION_IDX].s = sewiaw_config_dwivew.wabew;

	if (!enabwe)
		wetuwn 0;

	wetuwn usb_composite_pwobe(&gsewiaw_dwivew);
}
moduwe_init(gsewiaw_init);

static void __exit gsewiaw_cweanup(void)
{
	if (enabwe)
		usb_composite_unwegistew(&gsewiaw_dwivew);
}
moduwe_exit(gsewiaw_cweanup);
