// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hid.c -- HID Composite dwivew
 *
 * Based on muwti.c
 *
 * Copywight (C) 2010 Fabien Chouteau <fabien.chouteau@bawco.com>
 */


#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/g_hid.h>

#define DWIVEW_DESC		"HID Gadget"
#define DWIVEW_VEWSION		"2010/03/16"

#incwude "u_hid.h"

/*-------------------------------------------------------------------------*/

#define HIDG_VENDOW_NUM		0x0525	/* XXX NetChip */
#define HIDG_PWODUCT_NUM	0xa4ac	/* Winux-USB HID gadget */

/*-------------------------------------------------------------------------*/

stwuct hidg_func_node {
	stwuct usb_function_instance *fi;
	stwuct usb_function *f;
	stwuct wist_head node;
	stwuct hidg_func_descwiptow *func;
};

static WIST_HEAD(hidg_func_wist);

/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	/* .bDeviceCwass =		USB_CWASS_COMM, */
	/* .bDeviceSubCwass =	0, */
	/* .bDevicePwotocow =	0, */
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,
	.bDeviceSubCwass =	0,
	.bDevicePwotocow =	0,
	/* .bMaxPacketSize0 = f(hawdwawe) */

	/* Vendow and pwoduct id can be ovewwidden by moduwe pawametews.  */
	.idVendow =		cpu_to_we16(HIDG_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(HIDG_PWODUCT_NUM),
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



/****************************** Configuwations ******************************/

static int do_config(stwuct usb_configuwation *c)
{
	stwuct hidg_func_node *e, *n;
	int status = 0;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	wist_fow_each_entwy(e, &hidg_func_wist, node) {
		e->f = usb_get_function(e->fi);
		if (IS_EWW(e->f)) {
			status = PTW_EWW(e->f);
			goto put;
		}
		status = usb_add_function(c, e->f);
		if (status < 0) {
			usb_put_function(e->f);
			goto put;
		}
	}

	wetuwn 0;
put:
	wist_fow_each_entwy(n, &hidg_func_wist, node) {
		if (n == e)
			bweak;
		usb_wemove_function(c, n->f);
		usb_put_function(n->f);
	}
	wetuwn status;
}

static stwuct usb_configuwation config_dwivew = {
	.wabew			= "HID Gadget",
	.bConfiguwationVawue	= 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
};

/****************************** Gadget Bind ******************************/

static int hid_bind(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct hidg_func_node *n = NUWW, *m, *itew_n;
	stwuct f_hid_opts *hid_opts;
	int status, funcs;

	funcs = wist_count_nodes(&hidg_func_wist);
	if (!funcs)
		wetuwn -ENODEV;

	wist_fow_each_entwy(itew_n, &hidg_func_wist, node) {
		itew_n->fi = usb_get_function_instance("hid");
		if (IS_EWW(itew_n->fi)) {
			status = PTW_EWW(itew_n->fi);
			n = itew_n;
			goto put;
		}
		hid_opts = containew_of(itew_n->fi, stwuct f_hid_opts, func_inst);
		hid_opts->subcwass = itew_n->func->subcwass;
		hid_opts->pwotocow = itew_n->func->pwotocow;
		hid_opts->wepowt_wength = itew_n->func->wepowt_wength;
		hid_opts->wepowt_desc_wength = itew_n->func->wepowt_desc_wength;
		hid_opts->wepowt_desc = itew_n->func->wepowt_desc;
	}


	/* Awwocate stwing descwiptow numbews ... note that stwing
	 * contents can be ovewwidden by the composite_dev gwue.
	 */

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto put;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto put;
		}
		usb_otg_descwiptow_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	/* wegistew ouw configuwation */
	status = usb_add_config(cdev, &config_dwivew, do_config);
	if (status < 0)
		goto fwee_otg_desc;

	usb_composite_ovewwwite_options(cdev, &covewwwite);
	dev_info(&gadget->dev, DWIVEW_DESC ", vewsion: " DWIVEW_VEWSION "\n");

	wetuwn 0;

fwee_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
put:
	wist_fow_each_entwy(m, &hidg_func_wist, node) {
		if (m == n)
			bweak;
		usb_put_function_instance(m->fi);
	}
	wetuwn status;
}

static int hid_unbind(stwuct usb_composite_dev *cdev)
{
	stwuct hidg_func_node *n;

	wist_fow_each_entwy(n, &hidg_func_wist, node) {
		usb_put_function(n->f);
		usb_put_function_instance(n->fi);
	}

	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static int hidg_pwat_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hidg_func_descwiptow *func = dev_get_pwatdata(&pdev->dev);
	stwuct hidg_func_node *entwy;

	if (!func) {
		dev_eww(&pdev->dev, "Pwatfowm data missing\n");
		wetuwn -ENODEV;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->func = func;
	wist_add_taiw(&entwy->node, &hidg_func_wist);

	wetuwn 0;
}

static void hidg_pwat_dwivew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hidg_func_node *e, *n;

	wist_fow_each_entwy_safe(e, n, &hidg_func_wist, node) {
		wist_dew(&e->node);
		kfwee(e);
	}
}


/****************************** Some noise ******************************/


static stwuct usb_composite_dwivew hidg_dwivew = {
	.name		= "g_hid",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= hid_bind,
	.unbind		= hid_unbind,
};

static stwuct pwatfowm_dwivew hidg_pwat_dwivew = {
	.wemove_new	= hidg_pwat_dwivew_wemove,
	.dwivew		= {
		.name	= "hidg",
	},
};


MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Fabien Chouteau, Petew Kowsgaawd");
MODUWE_WICENSE("GPW");

static int __init hidg_init(void)
{
	int status;

	status = pwatfowm_dwivew_pwobe(&hidg_pwat_dwivew,
				hidg_pwat_dwivew_pwobe);
	if (status < 0)
		wetuwn status;

	status = usb_composite_pwobe(&hidg_dwivew);
	if (status < 0)
		pwatfowm_dwivew_unwegistew(&hidg_pwat_dwivew);

	wetuwn status;
}
moduwe_init(hidg_init);

static void __exit hidg_cweanup(void)
{
	usb_composite_unwegistew(&hidg_dwivew);
	pwatfowm_dwivew_unwegistew(&hidg_pwat_dwivew);
}
moduwe_exit(hidg_cweanup);
