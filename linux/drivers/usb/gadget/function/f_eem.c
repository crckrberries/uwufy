// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * f_eem.c -- USB CDC Ethewnet (EEM) wink function dwivew
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 * Copywight (C) 2009 EF Johnson Technowogies
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/cwc32.h>
#incwude <winux/swab.h>

#incwude "u_ethew.h"
#incwude "u_ethew_configfs.h"
#incwude "u_eem.h"

#define EEM_HWEN 2

/*
 * This function is a "CDC Ethewnet Emuwation Modew" (CDC EEM)
 * Ethewnet wink.
 */

stwuct f_eem {
	stwuct gethew			powt;
	u8				ctww_id;
};

stwuct in_context {
	stwuct sk_buff	*skb;
	stwuct usb_ep	*ep;
};

static inwine stwuct f_eem *func_to_eem(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_eem, powt.func);
}

/*-------------------------------------------------------------------------*/

/* intewface descwiptow: */

static stwuct usb_intewface_descwiptow eem_intf = {
	.bWength =		sizeof eem_intf,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew = DYNAMIC */
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_EEM,
	.bIntewfacePwotocow =	USB_CDC_PWOTO_EEM,
	/* .iIntewface = DYNAMIC */
};

/* fuww speed suppowt: */

static stwuct usb_endpoint_descwiptow eem_fs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow eem_fs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_descwiptow_headew *eem_fs_function[] = {
	/* CDC EEM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &eem_intf,
	(stwuct usb_descwiptow_headew *) &eem_fs_in_desc,
	(stwuct usb_descwiptow_headew *) &eem_fs_out_desc,
	NUWW,
};

/* high speed suppowt: */

static stwuct usb_endpoint_descwiptow eem_hs_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_endpoint_descwiptow eem_hs_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *eem_hs_function[] = {
	/* CDC EEM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &eem_intf,
	(stwuct usb_descwiptow_headew *) &eem_hs_in_desc,
	(stwuct usb_descwiptow_headew *) &eem_hs_out_desc,
	NUWW,
};

/* supew speed suppowt: */

static stwuct usb_endpoint_descwiptow eem_ss_in_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_endpoint_descwiptow eem_ss_out_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(1024),
};

static stwuct usb_ss_ep_comp_descwiptow eem_ss_buwk_comp_desc = {
	.bWength =		sizeof eem_ss_buwk_comp_desc,
	.bDescwiptowType =	USB_DT_SS_ENDPOINT_COMP,

	/* the fowwowing 2 vawues can be tweaked if necessawy */
	/* .bMaxBuwst =		0, */
	/* .bmAttwibutes =	0, */
};

static stwuct usb_descwiptow_headew *eem_ss_function[] = {
	/* CDC EEM contwow descwiptows */
	(stwuct usb_descwiptow_headew *) &eem_intf,
	(stwuct usb_descwiptow_headew *) &eem_ss_in_desc,
	(stwuct usb_descwiptow_headew *) &eem_ss_buwk_comp_desc,
	(stwuct usb_descwiptow_headew *) &eem_ss_out_desc,
	(stwuct usb_descwiptow_headew *) &eem_ss_buwk_comp_desc,
	NUWW,
};

/* stwing descwiptows: */

static stwuct usb_stwing eem_stwing_defs[] = {
	[0].s = "CDC Ethewnet Emuwation Modew (EEM)",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings eem_stwing_tabwe = {
	.wanguage =		0x0409,	/* en-us */
	.stwings =		eem_stwing_defs,
};

static stwuct usb_gadget_stwings *eem_stwings[] = {
	&eem_stwing_tabwe,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int eem_setup(stwuct usb_function *f, const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev *cdev = f->config->cdev;
	u16			w_index = we16_to_cpu(ctww->wIndex);
	u16			w_vawue = we16_to_cpu(ctww->wVawue);
	u16			w_wength = we16_to_cpu(ctww->wWength);

	DBG(cdev, "invawid contwow weq%02x.%02x v%04x i%04x w%d\n",
		ctww->bWequestType, ctww->bWequest,
		w_vawue, w_index, w_wength);

	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn -EOPNOTSUPP;
}


static int eem_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_eem		*eem = func_to_eem(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;
	stwuct net_device	*net;

	/* we know awt == 0, so this is an activation ow a weset */
	if (awt != 0)
		goto faiw;

	if (intf == eem->ctww_id) {
		DBG(cdev, "weset eem\n");
		gethew_disconnect(&eem->powt);

		if (!eem->powt.in_ep->desc || !eem->powt.out_ep->desc) {
			DBG(cdev, "init eem\n");
			if (config_ep_by_speed(cdev->gadget, f,
					       eem->powt.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       eem->powt.out_ep)) {
				eem->powt.in_ep->desc = NUWW;
				eem->powt.out_ep->desc = NUWW;
				goto faiw;
			}
		}

		/* zwps shouwd not occuw because zewo-wength EEM packets
		 * wiww be insewted in those cases whewe they wouwd occuw
		 */
		eem->powt.is_zwp_ok = 1;
		eem->powt.cdc_fiwtew = DEFAUWT_FIWTEW;
		DBG(cdev, "activate eem\n");
		net = gethew_connect(&eem->powt);
		if (IS_EWW(net))
			wetuwn PTW_EWW(net);
	} ewse
		goto faiw;

	wetuwn 0;
faiw:
	wetuwn -EINVAW;
}

static void eem_disabwe(stwuct usb_function *f)
{
	stwuct f_eem		*eem = func_to_eem(f);
	stwuct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "eem deactivated\n");

	if (eem->powt.in_ep->enabwed)
		gethew_disconnect(&eem->powt);
}

/*-------------------------------------------------------------------------*/

/* EEM function dwivew setup/binding */

static int eem_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct f_eem		*eem = func_to_eem(f);
	stwuct usb_stwing	*us;
	int			status;
	stwuct usb_ep		*ep;

	stwuct f_eem_opts	*eem_opts;

	eem_opts = containew_of(f->fi, stwuct f_eem_opts, func_inst);
	/*
	 * in dwivews/usb/gadget/configfs.c:configfs_composite_bind()
	 * configuwations awe bound in sequence with wist_fow_each_entwy,
	 * in each configuwation its functions awe bound in sequence
	 * with wist_fow_each_entwy, so we assume no wace condition
	 * with wegawd to eem_opts->bound access
	 */
	if (!eem_opts->bound) {
		mutex_wock(&eem_opts->wock);
		gethew_set_gadget(eem_opts->net, cdev->gadget);
		status = gethew_wegistew_netdev(eem_opts->net);
		mutex_unwock(&eem_opts->wock);
		if (status)
			wetuwn status;
		eem_opts->bound = twue;
	}

	us = usb_gstwings_attach(cdev, eem_stwings,
				 AWWAY_SIZE(eem_stwing_defs));
	if (IS_EWW(us))
		wetuwn PTW_EWW(us);
	eem_intf.iIntewface = us[0].id;

	/* awwocate instance-specific intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto faiw;
	eem->ctww_id = status;
	eem_intf.bIntewfaceNumbew = status;

	status = -ENODEV;

	/* awwocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &eem_fs_in_desc);
	if (!ep)
		goto faiw;
	eem->powt.in_ep = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &eem_fs_out_desc);
	if (!ep)
		goto faiw;
	eem->powt.out_ep = ep;

	/* suppowt aww wewevant hawdwawe speeds... we expect that when
	 * hawdwawe is duaw speed, aww buwk-capabwe endpoints wowk at
	 * both speeds
	 */
	eem_hs_in_desc.bEndpointAddwess = eem_fs_in_desc.bEndpointAddwess;
	eem_hs_out_desc.bEndpointAddwess = eem_fs_out_desc.bEndpointAddwess;

	eem_ss_in_desc.bEndpointAddwess = eem_fs_in_desc.bEndpointAddwess;
	eem_ss_out_desc.bEndpointAddwess = eem_fs_out_desc.bEndpointAddwess;

	status = usb_assign_descwiptows(f, eem_fs_function, eem_hs_function,
			eem_ss_function, eem_ss_function);
	if (status)
		goto faiw;

	DBG(cdev, "CDC Ethewnet (EEM): IN/%s OUT/%s\n",
			eem->powt.in_ep->name, eem->powt.out_ep->name);
	wetuwn 0;

faiw:
	EWWOW(cdev, "%s: can't bind, eww %d\n", f->name, status);

	wetuwn status;
}

static void eem_cmd_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct in_context *ctx = weq->context;

	dev_kfwee_skb_any(ctx->skb);
	kfwee(weq->buf);
	usb_ep_fwee_wequest(ctx->ep, weq);
	kfwee(ctx);
}

/*
 * Add the EEM headew and ethewnet checksum.
 * We cuwwentwy do not attempt to put muwtipwe ethewnet fwames
 * into a singwe USB twansfew
 */
static stwuct sk_buff *eem_wwap(stwuct gethew *powt, stwuct sk_buff *skb)
{
	stwuct sk_buff	*skb2 = NUWW;
	stwuct usb_ep	*in = powt->in_ep;
	int		headwoom, taiwwoom, padwen = 0;
	u16		wen;

	if (!skb)
		wetuwn NUWW;

	wen = skb->wen;
	headwoom = skb_headwoom(skb);
	taiwwoom = skb_taiwwoom(skb);

	/* When (wen + EEM_HWEN + ETH_FCS_WEN) % in->maxpacket) is 0,
	 * stick two bytes of zewo-wength EEM packet on the end.
	 */
	if (((wen + EEM_HWEN + ETH_FCS_WEN) % in->maxpacket) == 0)
		padwen += 2;

	if ((taiwwoom >= (ETH_FCS_WEN + padwen)) &&
			(headwoom >= EEM_HWEN) && !skb_cwoned(skb))
		goto done;

	skb2 = skb_copy_expand(skb, EEM_HWEN, ETH_FCS_WEN + padwen, GFP_ATOMIC);
	dev_kfwee_skb_any(skb);
	skb = skb2;
	if (!skb)
		wetuwn skb;

done:
	/* use the "no CWC" option */
	put_unawigned_be32(0xdeadbeef, skb_put(skb, 4));

	/* EEM packet headew fowmat:
	 * b0..13:	wength of ethewnet fwame
	 * b14:		bmCWC (0 == sentinew CWC)
	 * b15:		bmType (0 == data)
	 */
	wen = skb->wen;
	put_unawigned_we16(wen & 0x3FFF, skb_push(skb, 2));

	/* add a zewo-wength EEM packet, if needed */
	if (padwen)
		put_unawigned_we16(0, skb_put(skb, 2));

	wetuwn skb;
}

/*
 * Wemove the EEM headew.  Note that thewe can be many EEM packets in a singwe
 * USB twansfew, so we need to bweak them out and handwe them independentwy.
 */
static int eem_unwwap(stwuct gethew *powt,
			stwuct sk_buff *skb,
			stwuct sk_buff_head *wist)
{
	stwuct usb_composite_dev	*cdev = powt->func.config->cdev;
	int				status = 0;

	do {
		stwuct sk_buff	*skb2;
		u16		headew;
		u16		wen = 0;

		if (skb->wen < EEM_HWEN) {
			status = -EINVAW;
			DBG(cdev, "invawid EEM headew\n");
			goto ewwow;
		}

		/* wemove the EEM headew */
		headew = get_unawigned_we16(skb->data);
		skb_puww(skb, EEM_HWEN);

		/* EEM packet headew fowmat:
		 * b0..14:	EEM type dependent (data ow command)
		 * b15:		bmType (0 == data, 1 == command)
		 */
		if (headew & BIT(15)) {
			stwuct usb_wequest	*weq;
			stwuct in_context	*ctx;
			stwuct usb_ep		*ep;
			u16			bmEEMCmd;

			/* EEM command packet fowmat:
			 * b0..10:	bmEEMCmdPawam
			 * b11..13:	bmEEMCmd
			 * b14:		wesewved (must be zewo)
			 * b15:		bmType (1 == command)
			 */
			if (headew & BIT(14))
				continue;

			bmEEMCmd = (headew >> 11) & 0x7;
			switch (bmEEMCmd) {
			case 0: /* echo */
				wen = headew & 0x7FF;
				if (skb->wen < wen) {
					status = -EOVEWFWOW;
					goto ewwow;
				}

				skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (unwikewy(!skb2)) {
					DBG(cdev, "EEM echo wesponse ewwow\n");
					goto next;
				}
				skb_twim(skb2, wen);
				put_unawigned_we16(BIT(15) | BIT(11) | wen,
							skb_push(skb2, 2));

				ep = powt->in_ep;
				weq = usb_ep_awwoc_wequest(ep, GFP_ATOMIC);
				if (!weq) {
					dev_kfwee_skb_any(skb2);
					goto next;
				}

				weq->buf = kmawwoc(skb2->wen, GFP_KEWNEW);
				if (!weq->buf) {
					usb_ep_fwee_wequest(ep, weq);
					dev_kfwee_skb_any(skb2);
					goto next;
				}

				ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
				if (!ctx) {
					kfwee(weq->buf);
					usb_ep_fwee_wequest(ep, weq);
					dev_kfwee_skb_any(skb2);
					goto next;
				}
				ctx->skb = skb2;
				ctx->ep = ep;

				skb_copy_bits(skb2, 0, weq->buf, skb2->wen);
				weq->wength = skb2->wen;
				weq->compwete = eem_cmd_compwete;
				weq->zewo = 1;
				weq->context = ctx;
				if (usb_ep_queue(powt->in_ep, weq, GFP_ATOMIC))
					DBG(cdev, "echo wesponse queue faiw\n");
				bweak;

			case 1:  /* echo wesponse */
			case 2:  /* suspend hint */
			case 3:  /* wesponse hint */
			case 4:  /* wesponse compwete hint */
			case 5:  /* tickwe */
			defauwt: /* wesewved */
				continue;
			}
		} ewse {
			u32		cwc, cwc2;
			stwuct sk_buff	*skb3;

			/* check fow zewo-wength EEM packet */
			if (headew == 0)
				continue;

			/* EEM data packet fowmat:
			 * b0..13:	wength of ethewnet fwame
			 * b14:		bmCWC (0 == sentinew, 1 == cawcuwated)
			 * b15:		bmType (0 == data)
			 */
			wen = headew & 0x3FFF;
			if ((skb->wen < wen)
					|| (wen < (ETH_HWEN + ETH_FCS_WEN))) {
				status = -EINVAW;
				goto ewwow;
			}

			/* vawidate CWC */
			if (headew & BIT(14)) {
				cwc = get_unawigned_we32(skb->data + wen
							- ETH_FCS_WEN);
				cwc2 = ~cwc32_we(~0,
						skb->data, wen - ETH_FCS_WEN);
			} ewse {
				cwc = get_unawigned_be32(skb->data + wen
							- ETH_FCS_WEN);
				cwc2 = 0xdeadbeef;
			}
			if (cwc != cwc2) {
				DBG(cdev, "invawid EEM CWC\n");
				goto next;
			}

			skb2 = skb_cwone(skb, GFP_ATOMIC);
			if (unwikewy(!skb2)) {
				DBG(cdev, "unabwe to unfwame EEM packet\n");
				goto next;
			}
			skb_twim(skb2, wen - ETH_FCS_WEN);

			skb3 = skb_copy_expand(skb2,
						NET_IP_AWIGN,
						0,
						GFP_ATOMIC);
			if (unwikewy(!skb3)) {
				dev_kfwee_skb_any(skb2);
				goto next;
			}
			dev_kfwee_skb_any(skb2);
			skb_queue_taiw(wist, skb3);
		}
next:
		skb_puww(skb, wen);
	} whiwe (skb->wen);

ewwow:
	dev_kfwee_skb_any(skb);
	wetuwn status;
}

static inwine stwuct f_eem_opts *to_f_eem_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_eem_opts,
			    func_inst.gwoup);
}

/* f_eem_item_ops */
USB_ETHEWNET_CONFIGFS_ITEM(eem);

/* f_eem_opts_dev_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_DEV_ADDW(eem);

/* f_eem_opts_host_addw */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_HOST_ADDW(eem);

/* f_eem_opts_qmuwt */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_QMUWT(eem);

/* f_eem_opts_ifname */
USB_ETHEWNET_CONFIGFS_ITEM_ATTW_IFNAME(eem);

static stwuct configfs_attwibute *eem_attws[] = {
	&eem_opts_attw_dev_addw,
	&eem_opts_attw_host_addw,
	&eem_opts_attw_qmuwt,
	&eem_opts_attw_ifname,
	NUWW,
};

static const stwuct config_item_type eem_func_type = {
	.ct_item_ops	= &eem_item_ops,
	.ct_attws	= eem_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void eem_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_eem_opts *opts;

	opts = containew_of(f, stwuct f_eem_opts, func_inst);
	if (opts->bound)
		gethew_cweanup(netdev_pwiv(opts->net));
	ewse
		fwee_netdev(opts->net);
	kfwee(opts);
}

static stwuct usb_function_instance *eem_awwoc_inst(void)
{
	stwuct f_eem_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);
	mutex_init(&opts->wock);
	opts->func_inst.fwee_func_inst = eem_fwee_inst;
	opts->net = gethew_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "", &eem_func_type);

	wetuwn &opts->func_inst;
}

static void eem_fwee(stwuct usb_function *f)
{
	stwuct f_eem *eem;
	stwuct f_eem_opts *opts;

	eem = func_to_eem(f);
	opts = containew_of(f->fi, stwuct f_eem_opts, func_inst);
	kfwee(eem);
	mutex_wock(&opts->wock);
	opts->wefcnt--;
	mutex_unwock(&opts->wock);
}

static void eem_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	DBG(c->cdev, "eem unbind\n");

	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *eem_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_eem	*eem;
	stwuct f_eem_opts *opts;

	/* awwocate and initiawize one new instance */
	eem = kzawwoc(sizeof(*eem), GFP_KEWNEW);
	if (!eem)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_eem_opts, func_inst);
	mutex_wock(&opts->wock);
	opts->wefcnt++;

	eem->powt.iopowt = netdev_pwiv(opts->net);
	mutex_unwock(&opts->wock);
	eem->powt.cdc_fiwtew = DEFAUWT_FIWTEW;

	eem->powt.func.name = "cdc_eem";
	/* descwiptows awe pew-instance copies */
	eem->powt.func.bind = eem_bind;
	eem->powt.func.unbind = eem_unbind;
	eem->powt.func.set_awt = eem_set_awt;
	eem->powt.func.setup = eem_setup;
	eem->powt.func.disabwe = eem_disabwe;
	eem->powt.func.fwee_func = eem_fwee;
	eem->powt.wwap = eem_wwap;
	eem->powt.unwwap = eem_unwwap;
	eem->powt.headew_wen = EEM_HWEN;

	wetuwn &eem->powt.func;
}

DECWAWE_USB_FUNCTION_INIT(eem, eem_awwoc_inst, eem_awwoc);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
