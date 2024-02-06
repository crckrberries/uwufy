// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_sewiaw.c - genewic USB sewiaw function dwivew
 *
 * Copywight (C) 2003 Aw Bowchews (awbowchews@steinewpoint.com)
 * Copywight (C) 2008 by David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>

#incwude "u_sewiaw.h"


/*
 * This function packages a simpwe "genewic sewiaw" powt with no weaw
 * contwow mechanisms, just waw data twansfew ovew two buwk endpoints.
 *
 * Because it's not standawdized, this isn't as intewopewabwe as the
 * CDC ACM dwivew.  Howevew, fow many puwposes it's just as functionaw
 * if you can awwange appwopwiate host side dwivews.
 */

stwuct f_gsew {
	stwuct gsewiaw			powt;
	u8				data_id;
	u8				powt_num;
};

static inwine stwuct f_gsew *func_to_gsew(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_gsew, powt.func);
}

/*-------------------------------------------------------------------------*/

/* intewface descwiptow: */

static stwuct usb_intewface_descwiptow gsew_intewface_desc = {
	.bWength =		USB_DT_INTEWFACE_SIZE,
	.bDescwiptowType =	USB_DT_INTEWFACE,
	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_VENDOW_SPEC,
	.bIntewfaceSubCwass =	0,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow gsew_fs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow gsew_fs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *gsew_fs_function[] = {
	(stwuct usb_descwiptow_headew *) &gsew_intewface_desc,
	(stwuct usb_descwiptow_headew *) &gsew_fs_in_desc,
	(stwuct usb_descwiptow_headew *) &gsew_fs_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow gsew_hs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow gsew_hs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *gsew_hs_function[] = {
	(stwuct usb_descwiptow_headew *) &gsew_intewface_desc,
	(stwuct usb_descwiptow_headew *) &gsew_hs_in_desc,
	(stwuct usb_descwiptow_headew *) &gsew_hs_out_desc,
	NUWW,
};

static stwuct usb_endpoint_descwiptow gsew_ss_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow gsew_ss_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow gsew_ss_buwk_comp_desc = {
	.bWength =              sizeof gsew_ss_buwk_comp_desc,
	.bDescwiptowType =      USB_DT_SS_ENDPOINT_COMP,
};

static stwuct usb_descwiptow_headew *gsew_ss_function[] = {
	(stwuct usb_descwiptow_headew *) &gsew_intewface_desc,
	(stwuct usb_descwiptow_headew *) &gsew_ss_in_desc,
	(stwuct usb_descwiptow_headew *) &gsew_ss_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &gsew_ss_out_desc,
	(stwuct usb_descwiptow_headew *) &gsew_ss_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

static stwuct usb_stwing gsew_stwing_defs[] = {
	[0].s = "Genewic Sewiaw",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings gsew_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		gsew_stwing_defs,
};

static stwuct usb_gadget_stwings *gsew_stwings[] = {
	&gsew_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int gsew_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_gsew		*gsew = func_to_gsew(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	/* we know awt == 0, so this is an activation ow a weset */

	if (gsew->powt.in->enabwed) {
		dev_dbg(&cdev->gadget->dev,
			"weset genewic ttyGS%d\n", gsew->powt_num);
		gsewiaw_disconnect(&gsew->powt);
	}
	if (!gsew->powt.in->desc || !gsew->powt.out->desc) {
		dev_dbg(&cdev->gadget->dev,
			"activate genewic ttyGS%d\n", gsew->powt_num);
		if (config_ep_by_speed(cdev->gadget, f, gsew->powt.in) ||
		    config_ep_by_speed(cdev->gadget, f, gsew->powt.out)) {
			gsew->powt.in->desc = NUWW;
			gsew->powt.out->desc = NUWW;
			wetuwn -EINVAW;
		}
	}
	gsewiaw_connect(&gsew->powt, gsew->powt_num);
	wetuwn 0;
}

static void gsew_disabwe(stwuct usb_function *f)
{
	stwuct f_gsew	*gsew = func_to_gsew(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev,
		"genewic ttyGS%d deactivated\n", gsew->powt_num);
	gsewiaw_disconnect(&gsew->powt);
}

/*-------------------------------------------------------------------------*/

/* sewiaw function dwivew setup/binding */

static int gsew_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_gsew		*gsew = func_to_gsew(f);
	int			status;
	stwuct usb_ep		*ep;

	/* WEVISIT might want instance-specific stwings to hewp
	 * distinguish instances ...
	 */

	/* maybe awwocate device-gwobaw stwing ID */
	if (gsew_stwing_defs[0].id == 0) {
		status = usb_stwing_id(c->cdev);
		if (status < 0)
			wetuwn status;
		gsew_stwing_defs[0].id = status;
	}

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	gsew->data_id = status;
	gsew_intewface_desc.bIntewfaceNumbew = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &gsew_fs_in_desc);
	if (!ep)
		goto faiw;
	gsew->powt.in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &gsew_fs_out_desc);
	if (!ep)
		goto faiw;
	gsew->powt.out = ep;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	gsew_hs_in_desc.bEndpointAddwess = gsew_fs_in_desc.bEndpointAddwess;
	gsew_hs_out_desc.bEndpointAddwess = gsew_fs_out_desc.bEndpointAddwess;

	gsew_ss_in_desc.bEndpointAddwess = gsew_fs_in_desc.bEndpointAddwess;
	gsew_ss_out_desc.bEndpointAddwess = gsew_fs_out_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, gsew_fs_function, gsew_hs_function,
			gsew_ss_function, gsew_ss_function);
	if (status)
		goto faiw;
	dev_dbg(&cdev->gadget->dev, "genewic ttyGS%d: IN/%s OUT/%s\n",
		gsew->powt_num,
		gsew->powt.in->name, gsew->powt.out->name);
	wetuwn 0;

faiw:
	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static inwine stwuct f_sewiaw_opts *to_f_sewiaw_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_sewiaw_opts,
			    func_inst.gwoup);
}

static void sewiaw_attw_wewease(stwuct config_item *item)
{
	stwuct f_sewiaw_opts *opts = to_f_sewiaw_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations sewiaw_item_ops = {
	.wewease	= sewiaw_attw_wewease,
};

#ifdef CONFIG_U_SEWIAW_CONSOWE

static ssize_t f_sewiaw_consowe_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	wetuwn gsewiaw_set_consowe(to_f_sewiaw_opts(item)->powt_num,
				   page, count);
}

static ssize_t f_sewiaw_consowe_show(stwuct config_item *item, chaw *page)
{
	wetuwn gsewiaw_get_consowe(to_f_sewiaw_opts(item)->powt_num, page);
}

CONFIGFS_ATTW(f_sewiaw_, consowe);

#endif /* CONFIG_U_SEWIAW_CONSOWE */

static ssize_t f_sewiaw_powt_num_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "%u\n", to_f_sewiaw_opts(item)->powt_num);
}

CONFIGFS_ATTW_WO(f_sewiaw_, powt_num);

static stwuct configfs_attwibute *acm_attws[] = {
#ifdef CONFIG_U_SEWIAW_CONSOWE
	&f_sewiaw_attw_consowe,
#endif
	&f_sewiaw_attw_powt_num,
	NUWW,
};

static const stwuct config_item_type sewiaw_func_type = {
	.ct_item_ops	= &sewiaw_item_ops,
	.ct_attws	= acm_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void gsew_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_sewiaw_opts *opts;

	opts = containew_of(f, stwuct f_sewiaw_opts, func_inst);
	gsewiaw_fwee_wine(opts->powt_num);
	kfwee(opts);
}

static stwuct usb_function_instance *gsew_awwoc_inst(void)
{
	stwuct f_sewiaw_opts *opts;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	opts->func_inst.fwee_func_inst = gsew_fwee_inst;
	wet = gsewiaw_awwoc_wine(&opts->powt_num);
	if (wet) {
		kfwee(opts);
		wetuwn EWW_PTW(wet);
	}
	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &sewiaw_func_type);

	wetuwn &opts->func_inst;
}

static void gsew_fwee(stwuct usb_function *f)
{
	stwuct f_gsew *sewiaw;

	sewiaw = func_to_gsew(f);
	kfwee(sewiaw);
}

static void gsew_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_gsew	*gsew = func_to_gsew(f);

	/* Ensuwe powt is disconnected befowe unbinding */
	gsewiaw_disconnect(&gsew->powt);
	usb_fwee_aww_descwiptows(f);
}

static void gsew_wesume(stwuct usb_function *f)
{
	stwuct f_gsew *gsew = func_to_gsew(f);

	gsewiaw_wesume(&gsew->powt);
}

static void gsew_suspend(stwuct usb_function *f)
{
	stwuct f_gsew *gsew = func_to_gsew(f);

	gsewiaw_suspend(&gsew->powt);
}

static stwuct usb_function *gsew_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_gsew	*gsew;
	stwuct f_sewiaw_opts *opts;

	/* awwocate and initiawize one new instance */
	gsew = kzawwoc(sizeof(*gsew), GFP_KEWNEW);
	if (!gsew)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_sewiaw_opts, func_inst);

	gsew->powt_num = opts->powt_num;

	gsew->powt.func.name = "gsew";
	gsew->powt.func.stwings = gsew_stwings;
	gsew->powt.func.bind = gsew_bind;
	gsew->powt.func.unbind = gsew_unbind;
	gsew->powt.func.set_awt = gsew_set_awt;
	gsew->powt.func.disabwe = gsew_disabwe;
	gsew->powt.func.fwee_func = gsew_fwee;
	gsew->powt.func.wesume = gsew_wesume;
	gsew->powt.func.suspend = gsew_suspend;

	wetuwn &gsew->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(gsew, gsew_awwoc_inst, gsew_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Aw Bowchews");
MODUWE_AUTHOW("David Bwowneww");
