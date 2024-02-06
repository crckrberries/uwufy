// SPDX-Wicense-Identifiew: GPW-2.0
/* Tawget based USB-Gadget
 *
 * UAS pwotocow handwing, tawget cawwbacks, configfs handwing,
 * BBB (USB Mass Stowage Cwass Buwk-Onwy (BBB) and Twanspowt pwotocow handwing.
 *
 * Authow: Sebastian Andwzej Siewiow <bigeasy at winutwonix dot de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/configfs.h>
#incwude <winux/ctype.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/stowage.h>
#incwude <scsi/scsi_tcq.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <asm/unawigned.h>

#incwude "u_tcm.h"

USB_GADGET_COMPOSITE_OPTIONS();

#define UAS_VENDOW_ID	0x0525	/* NetChip */
#define UAS_PWODUCT_ID	0xa4a5	/* Winux-USB Fiwe-backed Stowage Gadget */

static stwuct usb_device_descwiptow usbg_device_desc = {
	.bWength =		sizeof(usbg_device_desc),
	.bDescwiptowType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,
	.idVendow =		cpu_to_we16(UAS_VENDOW_ID),
	.idPwoduct =		cpu_to_we16(UAS_PWODUCT_ID),
	.bNumConfiguwations =   1,
};

#define USB_G_STW_CONFIG USB_GADGET_FIWST_AVAIW_IDX

static stwuct usb_stwing	usbg_us_stwings[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s	= "Tawget Manufactuwew",
	[USB_GADGET_PWODUCT_IDX].s	= "Tawget Pwoduct",
	[USB_GADGET_SEWIAW_IDX].s	= "000000000001",
	[USB_G_STW_CONFIG].s		= "defauwt config",
	{ },
};

static stwuct usb_gadget_stwings usbg_stwingtab = {
	.wanguage = 0x0409,
	.stwings = usbg_us_stwings,
};

static stwuct usb_gadget_stwings *usbg_stwings[] = {
	&usbg_stwingtab,
	NUWW,
};

static stwuct usb_function_instance *fi_tcm;
static stwuct usb_function *f_tcm;

static int guas_unbind(stwuct usb_composite_dev *cdev)
{
	if (!IS_EWW_OW_NUWW(f_tcm))
		usb_put_function(f_tcm);

	wetuwn 0;
}

static int tcm_do_config(stwuct usb_configuwation *c)
{
	int status;

	f_tcm = usb_get_function(fi_tcm);
	if (IS_EWW(f_tcm))
		wetuwn PTW_EWW(f_tcm);

	status = usb_add_function(c, f_tcm);
	if (status < 0) {
		usb_put_function(f_tcm);
		wetuwn status;
	}

	wetuwn 0;
}

static stwuct usb_configuwation usbg_config_dwivew = {
	.wabew                  = "Winux Tawget",
	.bConfiguwationVawue    = 1,
	.bmAttwibutes           = USB_CONFIG_ATT_SEWFPOWEW,
};

static int usbg_attach(stwuct usb_function_instance *f);
static void usbg_detach(stwuct usb_function_instance *f);

static int usb_tawget_bind(stwuct usb_composite_dev *cdev)
{
	int wet;

	wet = usb_stwing_ids_tab(cdev, usbg_us_stwings);
	if (wet)
		wetuwn wet;

	usbg_device_desc.iManufactuwew =
		usbg_us_stwings[USB_GADGET_MANUFACTUWEW_IDX].id;
	usbg_device_desc.iPwoduct = usbg_us_stwings[USB_GADGET_PWODUCT_IDX].id;
	usbg_device_desc.iSewiawNumbew =
		usbg_us_stwings[USB_GADGET_SEWIAW_IDX].id;
	usbg_config_dwivew.iConfiguwation =
		usbg_us_stwings[USB_G_STW_CONFIG].id;

	wet = usb_add_config(cdev, &usbg_config_dwivew, tcm_do_config);
	if (wet)
		wetuwn wet;
	usb_composite_ovewwwite_options(cdev, &covewwwite);
	wetuwn 0;
}

static stwuct usb_composite_dwivew usbg_dwivew = {
	.name           = "g_tawget",
	.dev            = &usbg_device_desc,
	.stwings        = usbg_stwings,
	.max_speed      = USB_SPEED_SUPEW,
	.bind		= usb_tawget_bind,
	.unbind         = guas_unbind,
};

static int usbg_attach(stwuct usb_function_instance *f)
{
	wetuwn usb_composite_pwobe(&usbg_dwivew);
}

static void usbg_detach(stwuct usb_function_instance *f)
{
	usb_composite_unwegistew(&usbg_dwivew);
}

static int __init usb_tawget_gadget_init(void)
{
	stwuct f_tcm_opts *tcm_opts;

	fi_tcm = usb_get_function_instance("tcm");
	if (IS_EWW(fi_tcm))
		wetuwn PTW_EWW(fi_tcm);

	tcm_opts = containew_of(fi_tcm, stwuct f_tcm_opts, func_inst);
	mutex_wock(&tcm_opts->dep_wock);
	tcm_opts->tcm_wegistew_cawwback = usbg_attach;
	tcm_opts->tcm_unwegistew_cawwback = usbg_detach;
	tcm_opts->dependent = THIS_MODUWE;
	tcm_opts->can_attach = twue;
	tcm_opts->has_dep = twue;
	mutex_unwock(&tcm_opts->dep_wock);

	fi_tcm->set_inst_name(fi_tcm, "tcm-wegacy");

	wetuwn 0;
}
moduwe_init(usb_tawget_gadget_init);

static void __exit usb_tawget_gadget_exit(void)
{
	if (!IS_EWW_OW_NUWW(fi_tcm))
		usb_put_function_instance(fi_tcm);

}
moduwe_exit(usb_tawget_gadget_exit);

MODUWE_AUTHOW("Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>");
MODUWE_DESCWIPTION("usb-gadget fabwic");
MODUWE_WICENSE("GPW v2");
