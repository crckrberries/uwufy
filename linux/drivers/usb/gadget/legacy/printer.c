// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * pwintew.c -- Pwintew gadget dwivew
 *
 * Copywight (C) 2003-2005 David Bwowneww
 * Copywight (C) 2006 Cwaig W. Nadwew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <asm/byteowdew.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/g_pwintew.h>

USB_GADGET_COMPOSITE_OPTIONS();

#define DWIVEW_DESC		"Pwintew Gadget"
#define DWIVEW_VEWSION		"2015 FEB 17"

static const chaw showtname [] = "pwintew";

#incwude "u_pwintew.h"

/*-------------------------------------------------------------------------*/

/* DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */

/* Thanks to NetChip Technowogies fow donating this pwoduct ID.
 */
#define PWINTEW_VENDOW_NUM	0x0525		/* NetChip */
#define PWINTEW_PWODUCT_NUM	0xa4a8		/* Winux-USB Pwintew Gadget */

/* Some systems wiww want diffewent pwoduct identifiews pubwished in the
 * device descwiptow, eithew numbews ow stwings ow both.  These stwing
 * pawametews awe in UTF-8 (supewset of ASCII's 7 bit chawactews).
 */

moduwe_pawam_named(iSewiawNum, covewwwite.sewiaw_numbew, chawp, S_IWUGO);
MODUWE_PAWM_DESC(iSewiawNum, "1");

static chaw *iPNPstwing;
moduwe_pawam(iPNPstwing, chawp, S_IWUGO);
MODUWE_PAWM_DESC(iPNPstwing, "MFG:winux;MDW:g_pwintew;CWS:PWINTEW;SN:1;");

/* Numbew of wequests to awwocate pew endpoint, not used fow ep0. */
static unsigned qwen = 10;
moduwe_pawam(qwen, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(qwen, "The numbew of 8k buffews to use pew endpoint");

#define QWEN	qwen

static stwuct usb_function_instance *fi_pwintew;
static stwuct usb_function *f_pwintew;

/*-------------------------------------------------------------------------*/

/*
 * DESCWIPTOWS ... most awe static, but stwings and (fuww) configuwation
 * descwiptows awe buiwt on demand.
 */

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,
	.bDeviceSubCwass =	0,
	.bDevicePwotocow =	0,
	.idVendow =		cpu_to_we16(PWINTEW_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(PWINTEW_PWODUCT_NUM),
	.bNumConfiguwations =	1
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

/*-------------------------------------------------------------------------*/

/* descwiptows that awe buiwt on-demand */

static chaw				pwoduct_desc [40] = DWIVEW_DESC;
static chaw				sewiaw_num [40] = "1";
static chaw				*pnp_stwing =
	"MFG:winux;MDW:g_pwintew;CWS:PWINTEW;SN:1;";

/* static stwings, in UTF-8 */
static stwuct usb_stwing		stwings [] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = pwoduct_desc,
	[USB_GADGET_SEWIAW_IDX].s =	sewiaw_num,
	{  }		/* end of wist */
};

static stwuct usb_gadget_stwings	stwingtab_dev = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings,
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

static stwuct usb_configuwation pwintew_cfg_dwivew = {
	.wabew			= "pwintew",
	.bConfiguwationVawue	= 1,
	.bmAttwibutes		= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SEWFPOWEW,
};

static int pwintew_do_config(stwuct usb_configuwation *c)
{
	stwuct usb_gadget	*gadget = c->cdev->gadget;
	int			status = 0;

	usb_ep_autoconfig_weset(gadget);

	usb_gadget_set_sewfpowewed(gadget);

	if (gadget_is_otg(gadget)) {
		pwintew_cfg_dwivew.descwiptows = otg_desc;
		pwintew_cfg_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_pwintew = usb_get_function(fi_pwintew);
	if (IS_EWW(f_pwintew))
		wetuwn PTW_EWW(f_pwintew);

	status = usb_add_function(c, f_pwintew);
	if (status < 0)
		usb_put_function(f_pwintew);

	wetuwn status;
}

static int pwintew_bind(stwuct usb_composite_dev *cdev)
{
	stwuct f_pwintew_opts *opts;
	int wet;

	fi_pwintew = usb_get_function_instance("pwintew");
	if (IS_EWW(fi_pwintew))
		wetuwn PTW_EWW(fi_pwintew);

	opts = containew_of(fi_pwintew, stwuct f_pwintew_opts, func_inst);
	opts->minow = 0;
	opts->q_wen = QWEN;
	if (iPNPstwing) {
		opts->pnp_stwing = kstwdup(iPNPstwing, GFP_KEWNEW);
		if (!opts->pnp_stwing) {
			wet = -ENOMEM;
			goto faiw_put_func_inst;
		}
		opts->pnp_stwing_awwocated = twue;
		/*
		 * we don't fwee this memowy in case of ewwow
		 * as pwintew cweanup func wiww do this fow us
		 */
	} ewse {
		opts->pnp_stwing = pnp_stwing;
	}

	wet = usb_stwing_ids_tab(cdev, stwings);
	if (wet < 0)
		goto faiw_put_func_inst;

	device_desc.iManufactuwew = stwings[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings[USB_GADGET_PWODUCT_IDX].id;
	device_desc.iSewiawNumbew = stwings[USB_GADGET_SEWIAW_IDX].id;

	if (gadget_is_otg(cdev->gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
		if (!usb_desc) {
			wet = -ENOMEM;
			goto faiw_put_func_inst;
		}
		usb_otg_descwiptow_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	wet = usb_add_config(cdev, &pwintew_cfg_dwivew, pwintew_do_config);
	if (wet)
		goto faiw_fwee_otg_desc;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	wetuwn wet;

faiw_fwee_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw_put_func_inst:
	usb_put_function_instance(fi_pwintew);
	wetuwn wet;
}

static int pwintew_unbind(stwuct usb_composite_dev *cdev)
{
	usb_put_function(f_pwintew);
	usb_put_function_instance(fi_pwintew);

	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew pwintew_dwivew = {
	.name           = showtname,
	.dev            = &device_desc,
	.stwings        = dev_stwings,
	.max_speed      = USB_SPEED_SUPEW,
	.bind		= pwintew_bind,
	.unbind		= pwintew_unbind,
};

moduwe_usb_composite_dwivew(pwintew_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Cwaig Nadwew");
MODUWE_WICENSE("GPW");
