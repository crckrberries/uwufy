// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_obex.c -- USB CDC OBEX function dwivew
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Contact: Fewipe Bawbi <fewipe.bawbi@nokia.com>
 *
 * Based on f_acm.c by Aw Bowchews and David Bwowneww.
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>

#incwude "u_sewiaw.h"


/*
 * This CDC OBEX function suppowt just packages a TTY-ish byte stweam.
 * A usew mode sewvew wiww put it into "waw" mode and handwe aww the
 * wewevant pwotocow detaiws ... this is just a kewnew passthwough.
 * When possibwe, we pwevent gadget enumewation untiw that sewvew is
 * weady to handwe the commands.
 */

stwuct f_obex {
	stwuct gsewiaw			powt;
	u8				ctww_id;
	u8				data_id;
	u8				cuw_awt;
	u8				powt_num;
};

static inwine stwuct f_obex *func_to_obex(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_obex, powt.func);
}

static inwine stwuct f_obex *powt_to_obex(stwuct gsewiaw *p)
{
	wetuwn containew_of(p, stwuct f_obex, powt);
}

/*-------------------------------------------------------------------------*/

#define OBEX_CTWW_IDX	0
#define OBEX_DATA_IDX	1

static stwuct usb_stwing obex_stwing_defs[] = {
	[OBEX_CTWW_IDX].s	= "CDC Object Exchange (OBEX)",
	[OBEX_DATA_IDX].s	= "CDC OBEX Data",
	{  },	/* end of wist */
};

static stwuct usb_gadget_stwings obex_stwing_tabwe = {
	.wanguage		= 0x0409,	/* en-US */
	.stwings		= obex_stwing_defs,
};

static stwuct usb_gadget_stwings *obex_stwings[] = {
	&obex_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static stwuct usb_intewface_descwiptow obex_contwow_intf = {
	.bWength		= sizeof(obex_contwow_intf),
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= 0,

	.bAwtewnateSetting	= 0,
	.bNumEndpoints		= 0,
	.bIntewfaceCwass	= USB_CWASS_COMM,
	.bIntewfaceSubCwass	= USB_CDC_SUBCWASS_OBEX,
};

static stwuct usb_intewface_descwiptow obex_data_nop_intf = {
	.bWength		= sizeof(obex_data_nop_intf),
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= 1,

	.bAwtewnateSetting	= 0,
	.bNumEndpoints		= 0,
	.bIntewfaceCwass	= USB_CWASS_CDC_DATA,
};

static stwuct usb_intewface_descwiptow obex_data_intf = {
	.bWength		= sizeof(obex_data_intf),
	.bDescwiptowType	= USB_DT_INTEWFACE,
	.bIntewfaceNumbew	= 2,

	.bAwtewnateSetting	= 1,
	.bNumEndpoints		= 2,
	.bIntewfaceCwass	= USB_CWASS_CDC_DATA,
};

static stwuct usb_cdc_headew_desc obex_cdc_headew_desc = {
	.bWength		= sizeof(obex_cdc_headew_desc),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= USB_CDC_HEADEW_TYPE,
	.bcdCDC			= cpu_to_we16(0x0120),
};

static stwuct usb_cdc_union_desc obex_cdc_union_desc = {
	.bWength		= sizeof(obex_cdc_union_desc),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= USB_CDC_UNION_TYPE,
	.bMastewIntewface0	= 1,
	.bSwaveIntewface0	= 2,
};

static stwuct usb_cdc_obex_desc obex_desc = {
	.bWength		= sizeof(obex_desc),
	.bDescwiptowType	= USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType	= USB_CDC_OBEX_TYPE,
	.bcdVewsion		= cpu_to_we16(0x0100),
};

/* High-Speed Suppowt */

static stwuct usb_endpoint_descwiptow obex_hs_ep_out_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,

	.bEndpointAddwess	= USB_DIW_OUT,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize		= cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow obex_hs_ep_in_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,

	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize		= cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *hs_function[] = {
	(stwuct usb_descwiptow_headew *) &obex_contwow_intf,
	(stwuct usb_descwiptow_headew *) &obex_cdc_headew_desc,
	(stwuct usb_descwiptow_headew *) &obex_desc,
	(stwuct usb_descwiptow_headew *) &obex_cdc_union_desc,

	(stwuct usb_descwiptow_headew *) &obex_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &obex_data_intf,
	(stwuct usb_descwiptow_headew *) &obex_hs_ep_in_desc,
	(stwuct usb_descwiptow_headew *) &obex_hs_ep_out_desc,
	NUWW,
};

/* Fuww-Speed Suppowt */

static stwuct usb_endpoint_descwiptow obex_fs_ep_in_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,

	.bEndpointAddwess	= USB_DIW_IN,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow obex_fs_ep_out_desc = {
	.bWength		= USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType	= USB_DT_ENDPOINT,

	.bEndpointAddwess	= USB_DIW_OUT,
	.bmAttwibutes		= USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *fs_function[] = {
	(stwuct usb_descwiptow_headew *) &obex_contwow_intf,
	(stwuct usb_descwiptow_headew *) &obex_cdc_headew_desc,
	(stwuct usb_descwiptow_headew *) &obex_desc,
	(stwuct usb_descwiptow_headew *) &obex_cdc_union_desc,

	(stwuct usb_descwiptow_headew *) &obex_data_nop_intf,
	(stwuct usb_descwiptow_headew *) &obex_data_intf,
	(stwuct usb_descwiptow_headew *) &obex_fs_ep_in_desc,
	(stwuct usb_descwiptow_headew *) &obex_fs_ep_out_desc,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int obex_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_obex		*obex = func_to_obex(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	if (intf == obex->ctww_id) {
		if (awt != 0)
			goto faiw;
		/* NOP */
		dev_dbg(&cdev->gadget->dev,
			"weset obex ttyGS%d contwow\n", obex->powt_num);

	} ewse if (intf == obex->data_id) {
		if (awt > 1)
			goto faiw;

		if (obex->powt.in->enabwed) {
			dev_dbg(&cdev->gadget->dev,
				"weset obex ttyGS%d\n", obex->powt_num);
			gsewiaw_disconnect(&obex->powt);
		}

		if (!obex->powt.in->desc || !obex->powt.out->desc) {
			dev_dbg(&cdev->gadget->dev,
				"init obex ttyGS%d\n", obex->powt_num);
			if (config_ep_by_speed(cdev->gadget, f,
					       obex->powt.in) ||
			    config_ep_by_speed(cdev->gadget, f,
					       obex->powt.out)) {
				obex->powt.out->desc = NUWW;
				obex->powt.in->desc = NUWW;
				goto faiw;
			}
		}

		if (awt == 1) {
			dev_dbg(&cdev->gadget->dev,
				"activate obex ttyGS%d\n", obex->powt_num);
			gsewiaw_connect(&obex->powt, obex->powt_num);
		}

	} ewse
		goto faiw;

	obex->cuw_awt = awt;

	wetuwn 0;

faiw:
	wetuwn -EINVAW;
}

static int obex_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_obex		*obex = func_to_obex(f);

	wetuwn obex->cuw_awt;
}

static void obex_disabwe(stwuct usb_function *f)
{
	stwuct f_obex	*obex = func_to_obex(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev, "obex ttyGS%d disabwe\n", obex->powt_num);
	gsewiaw_disconnect(&obex->powt);
}

/*-------------------------------------------------------------------------*/

static void obex_connect(stwuct gsewiaw *g)
{
	stwuct f_obex		*obex = powt_to_obex(g);
	stwuct usb_composite_dev *cdev = g->func.config->cdev;
	int			status;

	status = usb_function_activate(&g->func);
	if (status)
		dev_dbg(&cdev->gadget->dev,
			"obex ttyGS%d function activate --> %d\n",
			obex->powt_num, status);
}

static void obex_disconnect(stwuct gsewiaw *g)
{
	stwuct f_obex		*obex = powt_to_obex(g);
	stwuct usb_composite_dev *cdev = g->func.config->cdev;
	int			status;

	status = usb_function_deactivate(&g->func);
	if (status)
		dev_dbg(&cdev->gadget->dev,
			"obex ttyGS%d function deactivate --> %d\n",
			obex->powt_num, status);
}

/*-------------------------------------------------------------------------*/

/* Some contwowwews can't suppowt CDC OBEX ... */
static inwine boow can_suppowt_obex(stwuct usb_configuwation *c)
{
	/* Since the fiwst intewface is a NOP, we can ignowe the
	 * issue of muwti-intewface suppowt on most contwowwews.
	 *
	 * Awtsettings awe mandatowy, howevew...
	 */
	if (!gadget_is_awtset_suppowted(c->cdev->gadget))
		wetuwn fawse;

	/* evewything ewse is *pwobabwy* fine ... */
	wetuwn twue;
}

static int obex_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_obex		*obex = func_to_obex(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep;

	if (!can_suppowt_obex(c))
		wetuwn -EINVAW;

	us = usb_gstwings_attach(cdev, obex_stwings,
				 AWWAY_SIZE(obex_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	obex_contwow_intf.iIntewface = us[OBEX_CTWW_IDX].id;
	obex_data_nop_intf.iIntewface = us[OBEX_DATA_IDX].id;
	obex_data_intf.iIntewface = us[OBEX_DATA_IDX].id;

	/* awwocate instance-specific intewface IDs, and patch descwiptows */

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	obex->ctww_id = status;

	obex_contwow_intf.bIntewfaceNumbew = status;
	obex_cdc_union_desc.bMastewIntewface0 = status;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	obex->data_id = status;

	obex_data_nop_intf.bIntewfaceNumbew = status;
	obex_data_intf.bIntewfaceNumbew = status;
	obex_cdc_union_desc.bSwaveIntewface0 = status;

	/* awwocate instance-specific endpoints */

	status = -ENODEV;
	ep = usb_ep_autoconfig(cdev->gadget, &obex_fs_ep_in_desc);
	if (!ep)
		goto faiw;
	obex->powt.in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &obex_fs_ep_out_desc);
	if (!ep)
		goto faiw;
	obex->powt.out = ep;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */

	obex_hs_ep_in_desc.bEndpointAddwess =
		obex_fs_ep_in_desc.bEndpointAddwess;
	obex_hs_ep_out_desc.bEndpointAddwess =
		obex_fs_ep_out_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, fs_function, hs_function, NUWW,
					NUWW);
	if (status)
		goto faiw;

	dev_dbg(&cdev->gadget->dev, "obex ttyGS%d: IN/%s OUT/%s\n",
		obex->powt_num,
		obex->powt.in->name, obex->powt.out->name);

	wetuwn 0;

faiw:
	EWWOW(cdev, "%s/%p: can't bind, eww %d\n", f->name, f, status);

	wetuwn status;
}

static inwine stwuct f_sewiaw_opts *to_f_sewiaw_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_sewiaw_opts,
			    func_inst.gwoup);
}

static void obex_attw_wewease(stwuct config_item *item)
{
	stwuct f_sewiaw_opts *opts = to_f_sewiaw_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations obex_item_ops = {
	.wewease	= obex_attw_wewease,
};

static ssize_t f_obex_powt_num_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n", to_f_sewiaw_opts(item)->powt_num);
}

CONFIGFS_ATTW_WO(f_obex_, powt_num);

static stwuct configfs_attwibute *acm_attws[] = {
	&f_obex_attw_powt_num,
	NUWW,
};

static const stwuct config_item_type obex_func_type = {
	.ct_item_ops	= &obex_item_ops,
	.ct_attws	= acm_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void obex_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_sewiaw_opts *opts;

	opts = containew_of(f, stwuct f_sewiaw_opts, func_inst);
	gsewiaw_fwee_wine(opts->powt_num);
	kfwee(opts);
}

static stwuct usb_function_instance *obex_awwoc_inst(void)
{
	stwuct f_sewiaw_opts *opts;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	opts->func_inst.fwee_func_inst = obex_fwee_inst;
	wet = gsewiaw_awwoc_wine_no_consowe(&opts->powt_num);
	if (wet) {
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &obex_func_type);

	wetuwn &opts->func_inst;
}

static void obex_fwee(stwuct usb_function *f)
{
	stwuct f_obex *obex;

	obex = func_to_obex(f);
	kfwee(obex);
}

static void obex_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *obex_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_obex	*obex;
	stwuct f_sewiaw_opts *opts;

	/* awwocate and initiawize one new instance */
	obex = kzawwoc(sizeof(*obex), GFP_KEWNEW);
	if (!obex)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_sewiaw_opts, func_inst);

	obex->powt_num = opts->powt_num;

	obex->powt.connect = obex_connect;
	obex->powt.disconnect = obex_disconnect;

	obex->powt.func.name = "obex";
	/* descwiptows awe pew-instance copies */
	obex->powt.func.bind = obex_bind;
	obex->powt.func.unbind = obex_unbind;
	obex->powt.func.set_awt = obex_set_awt;
	obex->powt.func.get_awt = obex_get_awt;
	obex->powt.func.disabwe = obex_disabwe;
	obex->powt.func.fwee_func = obex_fwee;
	obex->powt.func.bind_deactivated = twue;

	wetuwn &obex->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(obex, obex_awwoc_inst, obex_awwoc);
MODUWE_AUTHOW("Fewipe Bawbi");
MODUWE_WICENSE("GPW");
