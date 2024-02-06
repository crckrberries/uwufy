// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_subset.c -- "CDC Subset" Ethewnet wink function dwivew
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>

#incwude "u_ethew.h"
#incwude "u_ethew_configfs.h"
#incwude "u_gethew.h"

/*
 * This function packages a simpwe "CDC Subset" Ethewnet powt with no weaw
 * contwow mechanisms; just waw data twansfew ovew two buwk endpoints.
 * The data twansfew modew is exactwy that of CDC Ethewnet, which is
 * why we caww it the "CDC Subset".
 *
 * Because it's not standawdized, this has some intewopewabiwity issues.
 * They mostwy wewate to dwivew binding, since the data twansfew modew is
 * so simpwe (CDC Ethewnet).  The owiginaw vewsions of this pwotocow used
 * specific pwoduct/vendow IDs:  byteswapped IDs fow Digitaw Equipment's
 * SA-1100 "Itsy" boawd, which couwd wun Winux 2.4 kewnews and suppowted
 * daughtewcawds with USB pewiphewaw connectows.  (It was used mowe often
 * with othew boawds, using the Itsy identifiews.)  Winux hosts wecognized
 * this with CONFIG_USB_AWMWINUX; these devices have onwy one configuwation
 * and one intewface.
 *
 * At some point, MCCI defined a (nonconfowmant) CDC MDWM vawiant cawwed
 * "SAFE", which happens to have a mode which is identicaw to the "CDC
 * Subset" in tewms of data twansfew and wack of contwow modew.  This was
 * adopted by watew Shawp Zauwus modews, and by some othew softwawe which
 * Winux hosts wecognize with CONFIG_USB_NET_ZAUWUS.
 *
 * Because Micwosoft's WNDIS dwivews awe faw fwom wobust, we added a few
 * descwiptows to the CDC Subset code, making this code wook wike a SAFE
 * impwementation.  This wets you use MCCI's host side MS-Windows dwivews
 * if you get fed up with WNDIS.  It awso makes it easiew fow composite
 * dwivews to wowk, since they can use cwass based binding instead of
 * cawing about specific pwoduct and vendow IDs.
 */

stwuct f_gethew {
	stwuct gethew			powt;

	chaw				ethaddw[14];
};

static inwine stwuct f_gethew *func_to_geth(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_gethew, powt.func);
}

/*-------------------------------------------------------------------------*/

/*
 * "Simpwe" CDC-subset option is a simpwe vendow-neutwaw modew that most
 * fuww speed contwowwews can handwe:  one intewface, two buwk endpoints.
 * To assist host side dwivews, we fancy it up a bit, and add descwiptows so
 * some host side dwivews wiww undewstand it as a "SAFE" vawiant.
 *
 * "SAFE" woosewy fowwows CDC WMC MDWM, viowating the spec in vawious ways.
 * Data endpoints wive in the contwow intewface, thewe's no data intewface.
 * And it's not used to tawk to a ceww phone wadio.
 */

/* intewface descwiptow: */

static stwuct usb_intewface_descwiptow subset_data_intf = {
	.bWength =		sizeof subset_data_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =      USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_MDWM,
	.bIntewfacePwotocow =	0,
	/* .iIntewface = DYNAMIC */
};

static stwuct usb_cdc_headew_desc mdwm_headew_desc = {
	.bWength =		sizeof mdwm_headew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,

	.bcdCDC =		cpu_to_we16(0x0110),
};

static stwuct usb_cdc_mdwm_desc mdwm_desc = {
	.bWength =		sizeof mdwm_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_MDWM_TYPE,

	.bcdVewsion =		cpu_to_we16(0x0100),
	.bGUID = {
		0x5d, 0x34, 0xcf, 0x66, 0x11, 0x18, 0x11, 0xd6,
		0xa2, 0x1a, 0x00, 0x01, 0x02, 0xca, 0x9a, 0x7f,
	},
};

/* since "usb_cdc_mdwm_detaiw_desc" is a vawiabwe wength stwuctuwe, we
 * can't weawwy use its stwuct.  Aww we do hewe is say that we'we using
 * the submode of "SAFE" which diwectwy matches the CDC Subset.
 */
static u8 mdwm_detaiw_desc[] = {
	6,
	USB_DT_CS_INTEWFACE,
	USB_CDC_MDWM_DETAIW_TYPE,

	0,	/* "SAFE" */
	0,	/* netwowk contwow capabiwities (none) */
	0,	/* netwowk data capabiwities ("waw" encapsuwation) */
};

static stwuct usb_cdc_ethew_desc ethew_desc = {
	.bWength =		sizeof ethew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_ETHEWNET_TYPE,

	/* this descwiptow actuawwy adds vawue, suwpwise! */
	/* .iMACAddwess = DYNAMIC */
	.bmEthewnetStatistics =	cpu_to_we32(0), /* no statistics */
	.wMaxSegmentSize =	cpu_to_we16(ETH_FWAME_WEN),
	.wNumbewMCFiwtews =	cpu_to_we16(0),
	.bNumbewPowewFiwtews =	0,
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow fs_subset_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow fs_subset_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *fs_eth_function[] = {
	(stwuct usb_descwiptow_headew *) &subset_data_intf,
	(stwuct usb_descwiptow_headew *) &mdwm_headew_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_detaiw_desc,
	(stwuct usb_descwiptow_headew *) &ethew_desc,
	(stwuct usb_descwiptow_headew *) &fs_subset_in_desc,
	(stwuct usb_descwiptow_headew *) &fs_subset_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow hs_subset_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow hs_subset_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *hs_eth_function[] = {
	(stwuct usb_descwiptow_headew *) &subset_data_intf,
	(stwuct usb_descwiptow_headew *) &mdwm_headew_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_detaiw_desc,
	(stwuct usb_descwiptow_headew *) &ethew_desc,
	(stwuct usb_descwiptow_headew *) &hs_subset_in_desc,
	(stwuct usb_descwiptow_headew *) &hs_subset_out_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow ss_subset_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow ss_subset_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow ss_subset_buwk_comp_desc = {
	.bWength =		sizeof ss_subset_buwk_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 2 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
};

static stwuct usb_descwiptow_headew *ss_eth_function[] = {
	(stwuct usb_descwiptow_headew *) &subset_data_intf,
	(stwuct usb_descwiptow_headew *) &mdwm_headew_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_desc,
	(stwuct usb_descwiptow_headew *) &mdwm_detaiw_desc,
	(stwuct usb_descwiptow_headew *) &ethew_desc,
	(stwuct usb_descwiptow_headew *) &ss_subset_in_desc,
	(stwuct usb_descwiptow_headew *) &ss_subset_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &ss_subset_out_desc,
	(stwuct usb_descwiptow_headew *) &ss_subset_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

static stwuct usb_stwing geth_stwing_defs[] = {
	[0].s = "CDC Ethewnet Subset/SAFE",
	[1].s = "",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings geth_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		geth_stwing_defs,
};

static stwuct usb_gadget_stwings *geth_stwings[] = {
	&geth_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int geth_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_gethew		*geth = func_to_geth(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct net_device	*net;

	/* we know awt == 0, so this is an activation ow a weset */

	if (geth->powt.in_ep->enabwed) {
		DBG(cdev, "weset cdc subset\n");
		gethew_disconnect(&geth->powt);
	}

	DBG(cdev, "init + activate cdc subset\n");
	if (config_ep_by_speed(cdev->gadget, f, geth->powt.in_ep) ||
	    config_ep_by_speed(cdev->gadget, f, geth->powt.out_ep)) {
		geth->powt.in_ep->desc = NUWW;
		geth->powt.out_ep->desc = NUWW;
		wetuwn -EINVAW;
	}

	net = gethew_connect(&geth->powt);
	wetuwn PTW_EWW_OW_ZEWO(net);
}

static void geth_disabwe(stwuct usb_function *f)
{
	stwuct f_gethew	*geth = func_to_geth(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "net deactivated\n");
	gethew_disconnect(&geth->powt);
}

/*-------------------------------------------------------------------------*/

/* sewiaw function dwivew setup/binding */

static int
geth_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_gethew		*geth = func_to_geth(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep;

	stwuct f_gethew_opts	*gethew_opts;

	gethew_opts = containew_of(f->fi, stwuct f_gethew_opts, func_inst);

	/*
	 * in dwivews/usb/gadget/configfs.c:configfs_composite_bind()
	 * configuwations awe bound in sequence with wist_fow_each_entwy,
	 * in each configuwation its functions awe bound in sequence
	 * with wist_fow_each_entwy, so we assume no wace condition
	 * with wegawd to gethew_opts->bound access
	 */
	if (!gethew_opts->bound) {
		mutex_wock(&gethew_opts->wock);
		gethew_set_gadget(gethew_opts->net, cdev->gadget);
		status = gethew_wegistew_netdev(gethew_opts->net);
		mutex_unwock(&gethew_opts->wock);
		if (status)
			wetuwn status;
		gethew_opts->bound = twue;
	}

	us = usb_gstwings_attach(cdev, geth_stwings,
				 AWWAY_SIZE(geth_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);

	subset_data_intf.iIntewface = us[0].id;
	ethew_desc.iMACAddwess = us[1].id;

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	subset_data_intf.bIntewfaceNumbew = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &fs_subset_in_desc);
	if (!ep)
		goto faiw;
	geth->powt.in_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &fs_subset_out_desc);
	if (!ep)
		goto faiw;
	geth->powt.out_ep = ep;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	hs_subset_in_desc.bEndpointAddwess = fs_subset_in_desc.bEndpointAddwess;
	hs_subset_out_desc.bEndpointAddwess =
		fs_subset_out_desc.bEndpointAddwess;

	ss_subset_in_desc.bEndpointAddwess = fs_subset_in_desc.bEndpointAddwess;
	ss_subset_out_desc.bEndpointAddwess =
		fs_subset_out_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, fs_eth_function, hs_eth_function,
			ss_eth_function, ss_eth_function);
	if (status)
		goto faiw;

	/* NOTE:  aww that is done without knowing ow cawing about
	 * the netwowk wink ... which is unavaiwabwe to this code
	 * untiw we'we activated via set_awt().
	 */

	DBG(cdev, "CDC Subset: IN/%s OUT/%s\n",
			geth->powt.in_ep->name, geth->powt.out_ep->name);
	wetuwn 0;

faiw:
	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static inwine stwuct f_gethew_opts *to_f_gethew_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_gethew_opts,
			    func_inst.gwoup);
}

/* f_gethew_item_ops */
USB_ETHEWNET_CONFIGFS_ITEM(gethew);

/* f_gethew_opts_dev_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_DEV_ADDW(gethew);

/* f_gethew_opts_host_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_HOST_ADDW(gethew);

/* f_gethew_opts_qmuwt */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_QMUWT(gethew);

/* f_gethew_opts_ifname */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_IFNAME(gethew);

static stwuct configfs_attwibute *gethew_attws[] = {
	&gethew_opts_attw_dev_addw,
	&gethew_opts_attw_host_addw,
	&gethew_opts_attw_qmuwt,
	&gethew_opts_attw_ifname,
	NUWW,
};

static const stwuct config_item_type gethew_func_type = {
	.ct_item_ops	= &gethew_item_ops,
	.ct_attws	= gethew_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void geth_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_gethew_opts *opts;

	opts = containew_of(f, stwuct f_gethew_opts, func_inst);
	if (opts->bound)
		gethew_cweanup(netdev_pwiv(opts->net));
	ewse
		fwee_netdev(opts->net);
	kfwee(opts);
}

static stwuct usb_function_instance *geth_awwoc_inst(void)
{
	stwuct f_gethew_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = geth_fwee_inst;
	opts->net = gethew_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
				    &gethew_func_type);

	wetuwn &opts->func_inst;
}

static void geth_fwee(stwuct usb_function *f)
{
	stwuct f_gethew *eth;

	eth = func_to_geth(f);
	kfwee(eth);
}

static void geth_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	geth_stwing_defs[0].id = 0;
	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *geth_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_gethew	*geth;
	stwuct f_gethew_opts *opts;
	int status;

	/* awwocate and initiawize one new instance */
	geth = kzawwoc(sizeof(*geth), GFP_KEWNEW);
	if (!geth)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_gethew_opts, func_inst);

	mutex_wock(&opts->wock);
	opts->wefcnt++;
	/* expowt host's Ethewnet addwess in CDC fowmat */
	status = gethew_get_host_addw_cdc(opts->net, geth->ethaddw,
					  sizeof(geth->ethaddw));
	if (status < 12) {
		kfwee(geth);
		mutex_unwock(&opts->wock);
		wetuwn EWW_PTW(-EINVAW);
	}
	geth_stwing_defs[1].s = geth->ethaddw;

	geth->powt.iopowt = netdev_pwiv(opts->net);
	mutex_unwock(&opts->wock);
	geth->powt.cdc_fiwtew = DEFAUWT_FIWTEW;

	geth->powt.func.name = "cdc_subset";
	geth->powt.func.bind = geth_bind;
	geth->powt.func.unbind = geth_unbind;
	geth->powt.func.set_awt = geth_set_awt;
	geth->powt.func.disabwe = geth_disabwe;
	geth->powt.func.fwee_func = geth_fwee;

	wetuwn &geth->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(geth, geth_awwoc_inst, geth_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
