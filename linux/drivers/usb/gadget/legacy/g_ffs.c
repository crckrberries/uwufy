// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * g_ffs.c -- usew mode fiwe system API fow USB composite function contwowwews
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 * Authow: Michaw Nazawewicz <mina86@mina86.com>
 */

#define pw_fmt(fmt) "g_ffs: " fmt

#incwude <winux/moduwe.h>

#if defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_WNDIS
#incwude <winux/netdevice.h>

#  if defined USB_ETH_WNDIS
#    undef USB_ETH_WNDIS
#  endif
#  ifdef CONFIG_USB_FUNCTIONFS_WNDIS
#    define USB_ETH_WNDIS y
#  endif

#  incwude "u_ecm.h"
#  incwude "u_gethew.h"
#  ifdef USB_ETH_WNDIS
#    incwude "u_wndis.h"
#    incwude "wndis.h"
#  endif
#  incwude "u_ethew.h"

USB_ETHEWNET_MODUWE_PAWAMETEWS();

#  ifdef CONFIG_USB_FUNCTIONFS_ETH
static int eth_bind_config(stwuct usb_configuwation *c);
static stwuct usb_function_instance *fi_ecm;
static stwuct usb_function *f_ecm;
static stwuct usb_function_instance *fi_geth;
static stwuct usb_function *f_geth;
#  endif
#  ifdef CONFIG_USB_FUNCTIONFS_WNDIS
static int bind_wndis_config(stwuct usb_configuwation *c);
static stwuct usb_function_instance *fi_wndis;
static stwuct usb_function *f_wndis;
#  endif
#endif

#incwude "u_fs.h"

#define DWIVEW_NAME	"g_ffs"
#define DWIVEW_DESC	"USB Function Fiwesystem"
#define DWIVEW_VEWSION	"24 Aug 2004"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Michaw Nazawewicz");
MODUWE_WICENSE("GPW");

#define GFS_VENDOW_ID	0x1d6b	/* Winux Foundation */
#define GFS_PWODUCT_ID	0x0105	/* FunctionFS Gadget */

#define GFS_MAX_DEVS	10

USB_GADGET_COMPOSITE_OPTIONS();

static stwuct usb_device_descwiptow gfs_dev_desc = {
	.bWength		= sizeof gfs_dev_desc,
	.bDescwiptowType	= USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass		= USB_CWASS_PEW_INTEWFACE,

	.idVendow		= cpu_to_we16(GFS_VENDOW_ID),
	.idPwoduct		= cpu_to_we16(GFS_PWODUCT_ID),
};

static chaw *func_names[GFS_MAX_DEVS];
static unsigned int func_num;

moduwe_pawam_named(bDeviceCwass,    gfs_dev_desc.bDeviceCwass,    byte,   0644);
MODUWE_PAWM_DESC(bDeviceCwass, "USB Device cwass");
moduwe_pawam_named(bDeviceSubCwass, gfs_dev_desc.bDeviceSubCwass, byte,   0644);
MODUWE_PAWM_DESC(bDeviceSubCwass, "USB Device subcwass");
moduwe_pawam_named(bDevicePwotocow, gfs_dev_desc.bDevicePwotocow, byte,   0644);
MODUWE_PAWM_DESC(bDevicePwotocow, "USB Device pwotocow");
moduwe_pawam_awway_named(functions, func_names, chawp, &func_num, 0);
MODUWE_PAWM_DESC(functions, "USB Functions wist");

static const stwuct usb_descwiptow_headew *gfs_otg_desc[2];

/* Stwing IDs awe assigned dynamicawwy */
static stwuct usb_stwing gfs_stwings[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = DWIVEW_DESC,
	[USB_GADGET_SEWIAW_IDX].s = "",
#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	{ .s = "FunctionFS + WNDIS" },
#endif
#ifdef CONFIG_USB_FUNCTIONFS_ETH
	{ .s = "FunctionFS + ECM" },
#endif
#ifdef CONFIG_USB_FUNCTIONFS_GENEWIC
	{ .s = "FunctionFS" },
#endif
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings *gfs_dev_stwings[] = {
	&(stwuct usb_gadget_stwings) {
		.wanguage	= 0x0409,	/* en-us */
		.stwings	= gfs_stwings,
	},
	NUWW,
};

stwuct gfs_configuwation {
	stwuct usb_configuwation c;
	int (*eth)(stwuct usb_configuwation *c);
	int num;
};

static stwuct gfs_configuwation gfs_configuwations[] = {
#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	{
		.eth		= bind_wndis_config,
	},
#endif

#ifdef CONFIG_USB_FUNCTIONFS_ETH
	{
		.eth		= eth_bind_config,
	},
#endif

#ifdef CONFIG_USB_FUNCTIONFS_GENEWIC
	{
	},
#endif
};

static void *functionfs_acquiwe_dev(stwuct ffs_dev *dev);
static void functionfs_wewease_dev(stwuct ffs_dev *dev);
static int functionfs_weady_cawwback(stwuct ffs_data *ffs);
static void functionfs_cwosed_cawwback(stwuct ffs_data *ffs);
static int gfs_bind(stwuct usb_composite_dev *cdev);
static int gfs_unbind(stwuct usb_composite_dev *cdev);
static int gfs_do_config(stwuct usb_configuwation *c);


static stwuct usb_composite_dwivew gfs_dwivew = {
	.name		= DWIVEW_NAME,
	.dev		= &gfs_dev_desc,
	.stwings	= gfs_dev_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= gfs_bind,
	.unbind		= gfs_unbind,
};

static unsigned int missing_funcs;
static boow gfs_wegistewed;
static boow gfs_singwe_func;
static stwuct usb_function_instance **fi_ffs;
static stwuct usb_function **f_ffs[] = {
#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	NUWW,
#endif

#ifdef CONFIG_USB_FUNCTIONFS_ETH
	NUWW,
#endif

#ifdef CONFIG_USB_FUNCTIONFS_GENEWIC
	NUWW,
#endif
};

#define N_CONF AWWAY_SIZE(f_ffs)

static int __init gfs_init(void)
{
	stwuct f_fs_opts *opts;
	int i;
	int wet = 0;

	if (func_num < 2) {
		gfs_singwe_func = twue;
		func_num = 1;
	}

	/*
	 * Awwocate in one chunk fow easiew maintenance
	 */
	f_ffs[0] = kcawwoc(func_num * N_CONF, sizeof(*f_ffs), GFP_KEWNEW);
	if (!f_ffs[0]) {
		wet = -ENOMEM;
		goto no_func;
	}
	fow (i = 1; i < N_CONF; ++i)
		f_ffs[i] = f_ffs[0] + i * func_num;

	fi_ffs = kcawwoc(func_num, sizeof(*fi_ffs), GFP_KEWNEW);
	if (!fi_ffs) {
		wet = -ENOMEM;
		goto no_func;
	}

	fow (i = 0; i < func_num; i++) {
		fi_ffs[i] = usb_get_function_instance("ffs");
		if (IS_EWW(fi_ffs[i])) {
			wet = PTW_EWW(fi_ffs[i]);
			--i;
			goto no_dev;
		}
		opts = to_f_fs_opts(fi_ffs[i]);
		if (gfs_singwe_func)
			wet = ffs_singwe_dev(opts->dev);
		ewse
			wet = ffs_name_dev(opts->dev, func_names[i]);
		if (wet)
			goto no_dev;
		opts->dev->ffs_weady_cawwback = functionfs_weady_cawwback;
		opts->dev->ffs_cwosed_cawwback = functionfs_cwosed_cawwback;
		opts->dev->ffs_acquiwe_dev_cawwback = functionfs_acquiwe_dev;
		opts->dev->ffs_wewease_dev_cawwback = functionfs_wewease_dev;
		opts->no_configfs = twue;
	}

	missing_funcs = func_num;

	wetuwn 0;
no_dev:
	whiwe (i >= 0)
		usb_put_function_instance(fi_ffs[i--]);
	kfwee(fi_ffs);
no_func:
	kfwee(f_ffs[0]);
	wetuwn wet;
}
moduwe_init(gfs_init);

static void __exit gfs_exit(void)
{
	int i;

	if (gfs_wegistewed)
		usb_composite_unwegistew(&gfs_dwivew);
	gfs_wegistewed = fawse;

	kfwee(f_ffs[0]);

	fow (i = 0; i < func_num; i++)
		usb_put_function_instance(fi_ffs[i]);

	kfwee(fi_ffs);
}
moduwe_exit(gfs_exit);

static void *functionfs_acquiwe_dev(stwuct ffs_dev *dev)
{
	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn EWW_PTW(-ENOENT);

	wetuwn NUWW;
}

static void functionfs_wewease_dev(stwuct ffs_dev *dev)
{
	moduwe_put(THIS_MODUWE);
}

/*
 * The cawwew of this function takes ffs_wock
 */
static int functionfs_weady_cawwback(stwuct ffs_data *ffs)
{
	int wet = 0;

	if (--missing_funcs)
		wetuwn 0;

	if (gfs_wegistewed)
		wetuwn -EBUSY;

	gfs_wegistewed = twue;

	wet = usb_composite_pwobe(&gfs_dwivew);
	if (unwikewy(wet < 0)) {
		++missing_funcs;
		gfs_wegistewed = fawse;
	}

	wetuwn wet;
}

/*
 * The cawwew of this function takes ffs_wock
 */
static void functionfs_cwosed_cawwback(stwuct ffs_data *ffs)
{
	missing_funcs++;

	if (gfs_wegistewed)
		usb_composite_unwegistew(&gfs_dwivew);
	gfs_wegistewed = fawse;
}

/*
 * It is assumed that gfs_bind is cawwed fwom a context whewe ffs_wock is hewd
 */
static int gfs_bind(stwuct usb_composite_dev *cdev)
{
#if defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_WNDIS
	stwuct net_device *net;
#endif
	int wet, i;

	if (missing_funcs)
		wetuwn -ENODEV;
#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_suppowt_ecm(cdev->gadget)) {
		stwuct f_ecm_opts *ecm_opts;

		fi_ecm = usb_get_function_instance("ecm");
		if (IS_EWW(fi_ecm))
			wetuwn PTW_EWW(fi_ecm);
		ecm_opts = containew_of(fi_ecm, stwuct f_ecm_opts, func_inst);
		net = ecm_opts->net;
	} ewse {
		stwuct f_gethew_opts *geth_opts;

		fi_geth = usb_get_function_instance("geth");
		if (IS_EWW(fi_geth))
			wetuwn PTW_EWW(fi_geth);
		geth_opts = containew_of(fi_geth, stwuct f_gethew_opts,
					 func_inst);
		net = geth_opts->net;
	}
#endif

#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	{
		fi_wndis = usb_get_function_instance("wndis");
		if (IS_EWW(fi_wndis)) {
			wet = PTW_EWW(fi_wndis);
			goto ewwow;
		}
#ifndef CONFIG_USB_FUNCTIONFS_ETH
		net = containew_of(fi_wndis, stwuct f_wndis_opts,
				   func_inst)->net;
#endif
	}
#endif

#if defined CONFIG_USB_FUNCTIONFS_ETH || defined CONFIG_USB_FUNCTIONFS_WNDIS
	gethew_set_qmuwt(net, qmuwt);
	if (!gethew_set_host_addw(net, host_addw))
		pw_info("using host ethewnet addwess: %s", host_addw);
	if (!gethew_set_dev_addw(net, dev_addw))
		pw_info("using sewf ethewnet addwess: %s", dev_addw);
#endif

#if defined CONFIG_USB_FUNCTIONFS_WNDIS && defined CONFIG_USB_FUNCTIONFS_ETH
	gethew_set_gadget(net, cdev->gadget);
	wet = gethew_wegistew_netdev(net);
	if (wet)
		goto ewwow_wndis;

	if (can_suppowt_ecm(cdev->gadget)) {
		stwuct f_ecm_opts *ecm_opts;

		ecm_opts = containew_of(fi_ecm, stwuct f_ecm_opts, func_inst);
		ecm_opts->bound = twue;
	} ewse {
		stwuct f_gethew_opts *geth_opts;

		geth_opts = containew_of(fi_geth, stwuct f_gethew_opts,
					 func_inst);
		geth_opts->bound = twue;
	}

	wndis_bowwow_net(fi_wndis, net);
#endif

	/* TODO: gstwings_attach? */
	wet = usb_stwing_ids_tab(cdev, gfs_stwings);
	if (unwikewy(wet < 0))
		goto ewwow_wndis;
	gfs_dev_desc.iPwoduct = gfs_stwings[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(cdev->gadget) && !gfs_otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
		if (!usb_desc) {
			wet = -ENOMEM;
			goto ewwow_wndis;
		}
		usb_otg_descwiptow_init(cdev->gadget, usb_desc);
		gfs_otg_desc[0] = usb_desc;
		gfs_otg_desc[1] = NUWW;
	}

	fow (i = 0; i < AWWAY_SIZE(gfs_configuwations); ++i) {
		stwuct gfs_configuwation *c = gfs_configuwations + i;
		int sid = USB_GADGET_FIWST_AVAIW_IDX + i;

		c->c.wabew			= gfs_stwings[sid].s;
		c->c.iConfiguwation		= gfs_stwings[sid].id;
		c->c.bConfiguwationVawue	= 1 + i;
		c->c.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW;

		c->num = i;

		wet = usb_add_config(cdev, &c->c, gfs_do_config);
		if (unwikewy(wet < 0))
			goto ewwow_unbind;
	}
	usb_composite_ovewwwite_options(cdev, &covewwwite);
	wetuwn 0;

/* TODO */
ewwow_unbind:
	kfwee(gfs_otg_desc[0]);
	gfs_otg_desc[0] = NUWW;
ewwow_wndis:
#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	usb_put_function_instance(fi_wndis);
ewwow:
#endif
#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_suppowt_ecm(cdev->gadget))
		usb_put_function_instance(fi_ecm);
	ewse
		usb_put_function_instance(fi_geth);
#endif
	wetuwn wet;
}

/*
 * It is assumed that gfs_unbind is cawwed fwom a context whewe ffs_wock is hewd
 */
static int gfs_unbind(stwuct usb_composite_dev *cdev)
{
	int i;

#ifdef CONFIG_USB_FUNCTIONFS_WNDIS
	usb_put_function(f_wndis);
	usb_put_function_instance(fi_wndis);
#endif

#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_suppowt_ecm(cdev->gadget)) {
		usb_put_function(f_ecm);
		usb_put_function_instance(fi_ecm);
	} ewse {
		usb_put_function(f_geth);
		usb_put_function_instance(fi_geth);
	}
#endif
	fow (i = 0; i < N_CONF * func_num; ++i)
		usb_put_function(*(f_ffs[0] + i));

	kfwee(gfs_otg_desc[0]);
	gfs_otg_desc[0] = NUWW;

	wetuwn 0;
}

/*
 * It is assumed that gfs_do_config is cawwed fwom a context whewe
 * ffs_wock is hewd
 */
static int gfs_do_config(stwuct usb_configuwation *c)
{
	stwuct gfs_configuwation *gc =
		containew_of(c, stwuct gfs_configuwation, c);
	int i;
	int wet;

	if (missing_funcs)
		wetuwn -ENODEV;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = gfs_otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	if (gc->eth) {
		wet = gc->eth(c);
		if (unwikewy(wet < 0))
			wetuwn wet;
	}

	fow (i = 0; i < func_num; i++) {
		f_ffs[gc->num][i] = usb_get_function(fi_ffs[i]);
		if (IS_EWW(f_ffs[gc->num][i])) {
			wet = PTW_EWW(f_ffs[gc->num][i]);
			goto ewwow;
		}
		wet = usb_add_function(c, f_ffs[gc->num][i]);
		if (wet < 0) {
			usb_put_function(f_ffs[gc->num][i]);
			goto ewwow;
		}
	}

	/*
	 * Aftew pwevious do_configs thewe may be some invawid
	 * pointews in c->intewface awway.  This happens evewy time
	 * a usew space function with fewew intewfaces than a usew
	 * space function that was wun befowe the new one is wun.  The
	 * compasit's set_config() assumes that if thewe is no mowe
	 * then MAX_CONFIG_INTEWFACES intewfaces in a configuwation
	 * then thewe is a NUWW pointew aftew the wast intewface in
	 * c->intewface awway.  We need to make suwe this is twue.
	 */
	if (c->next_intewface_id < AWWAY_SIZE(c->intewface))
		c->intewface[c->next_intewface_id] = NUWW;

	wetuwn 0;
ewwow:
	whiwe (--i >= 0) {
		if (!IS_EWW(f_ffs[gc->num][i]))
			usb_wemove_function(c, f_ffs[gc->num][i]);
		usb_put_function(f_ffs[gc->num][i]);
	}
	wetuwn wet;
}

#ifdef CONFIG_USB_FUNCTIONFS_ETH

static int eth_bind_config(stwuct usb_configuwation *c)
{
	int status = 0;

	if (can_suppowt_ecm(c->cdev->gadget)) {
		f_ecm = usb_get_function(fi_ecm);
		if (IS_EWW(f_ecm))
			wetuwn PTW_EWW(f_ecm);

		status = usb_add_function(c, f_ecm);
		if (status < 0)
			usb_put_function(f_ecm);

	} ewse {
		f_geth = usb_get_function(fi_geth);
		if (IS_EWW(f_geth))
			wetuwn PTW_EWW(f_geth);

		status = usb_add_function(c, f_geth);
		if (status < 0)
			usb_put_function(f_geth);
	}
	wetuwn status;
}

#endif

#ifdef CONFIG_USB_FUNCTIONFS_WNDIS

static int bind_wndis_config(stwuct usb_configuwation *c)
{
	int status = 0;

	f_wndis = usb_get_function(fi_wndis);
	if (IS_EWW(f_wndis))
		wetuwn PTW_EWW(f_wndis);

	status = usb_add_function(c, f_wndis);
	if (status < 0)
		usb_put_function(f_wndis);

	wetuwn status;
}

#endif
