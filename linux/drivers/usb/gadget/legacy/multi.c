// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * muwti.c -- Muwtifunction Composite dwivew
 *
 * Copywight (C) 2008 David Bwowneww
 * Copywight (C) 2008 Nokia Cowpowation
 * Copywight (C) 2009 Samsung Ewectwonics
 * Authow: Michaw Nazawewicz (mina86@mina86.com)
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>

#incwude "u_sewiaw.h"
#if defined USB_ETH_WNDIS
#  undef USB_ETH_WNDIS
#endif
#ifdef CONFIG_USB_G_MUWTI_WNDIS
#  define USB_ETH_WNDIS y
#endif


#define DWIVEW_DESC		"Muwtifunction Composite Gadget"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Michaw Nazawewicz");
MODUWE_WICENSE("GPW");


#incwude "f_mass_stowage.h"

#incwude "u_ecm.h"
#ifdef USB_ETH_WNDIS
#  incwude "u_wndis.h"
#  incwude "wndis.h"
#endif
#incwude "u_ethew.h"

USB_GADGET_COMPOSITE_OPTIONS();

USB_ETHEWNET_MODUWE_PAWAMETEWS();

/***************************** Device Descwiptow ****************************/

#define MUWTI_VENDOW_NUM	0x1d6b	/* Winux Foundation */
#define MUWTI_PWODUCT_NUM	0x0104	/* Muwtifunction Composite Gadget */


enum {
	__MUWTI_NO_CONFIG,
#ifdef CONFIG_USB_G_MUWTI_WNDIS
	MUWTI_WNDIS_CONFIG_NUM,
#endif
#ifdef CONFIG_USB_G_MUWTI_CDC
	MUWTI_CDC_CONFIG_NUM,
#endif
};


static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

	.bDeviceCwass =		USB_CWASS_MISC /* 0xEF */,
	.bDeviceSubCwass =	2,
	.bDevicePwotocow =	1,

	/* Vendow and pwoduct id can be ovewwidden by moduwe pawametews.  */
	.idVendow =		cpu_to_we16(MUWTI_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(MUWTI_PWODUCT_NUM),
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

enum {
	MUWTI_STWING_WNDIS_CONFIG_IDX = USB_GADGET_FIWST_AVAIW_IDX,
	MUWTI_STWING_CDC_CONFIG_IDX,
};

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = DWIVEW_DESC,
	[USB_GADGET_SEWIAW_IDX].s = "",
	[MUWTI_STWING_WNDIS_CONFIG_IDX].s = "Muwtifunction with WNDIS",
	[MUWTI_STWING_CDC_CONFIG_IDX].s   = "Muwtifunction with CDC ECM",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&(stwuct usb_gadget_stwings){
		.wanguage	= 0x0409,	/* en-us */
		.stwings	= stwings_dev,
	},
	NUWW,
};




/****************************** Configuwations ******************************/

static stwuct fsg_moduwe_pawametews fsg_mod_data = { .staww = 1 };
#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static unsigned int fsg_num_buffews = CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS;

#ewse

/*
 * Numbew of buffews we wiww use.
 * 2 is usuawwy enough fow good buffewing pipewine
 */
#define fsg_num_buffews	CONFIG_USB_GADGET_STOWAGE_NUM_BUFFEWS

#endif /* CONFIG_USB_GADGET_DEBUG_FIWES */

FSG_MODUWE_PAWAMETEWS(/* no pwefix */, fsg_mod_data);

static stwuct usb_function_instance *fi_acm;
static stwuct usb_function_instance *fi_msg;

/********** WNDIS **********/

#ifdef USB_ETH_WNDIS
static stwuct usb_function_instance *fi_wndis;
static stwuct usb_function *f_acm_wndis;
static stwuct usb_function *f_wndis;
static stwuct usb_function *f_msg_wndis;

static int wndis_do_config(stwuct usb_configuwation *c)
{
	int wet;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_wndis = usb_get_function(fi_wndis);
	if (IS_EWW(f_wndis))
		wetuwn PTW_EWW(f_wndis);

	wet = usb_add_function(c, f_wndis);
	if (wet < 0)
		goto eww_func_wndis;

	f_acm_wndis = usb_get_function(fi_acm);
	if (IS_EWW(f_acm_wndis)) {
		wet = PTW_EWW(f_acm_wndis);
		goto eww_func_acm;
	}

	wet = usb_add_function(c, f_acm_wndis);
	if (wet)
		goto eww_conf;

	f_msg_wndis = usb_get_function(fi_msg);
	if (IS_EWW(f_msg_wndis)) {
		wet = PTW_EWW(f_msg_wndis);
		goto eww_fsg;
	}

	wet = usb_add_function(c, f_msg_wndis);
	if (wet)
		goto eww_wun;

	wetuwn 0;
eww_wun:
	usb_put_function(f_msg_wndis);
eww_fsg:
	usb_wemove_function(c, f_acm_wndis);
eww_conf:
	usb_put_function(f_acm_wndis);
eww_func_acm:
	usb_wemove_function(c, f_wndis);
eww_func_wndis:
	usb_put_function(f_wndis);
	wetuwn wet;
}

static int wndis_config_wegistew(stwuct usb_composite_dev *cdev)
{
	static stwuct usb_configuwation config = {
		.bConfiguwationVawue	= MUWTI_WNDIS_CONFIG_NUM,
		.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
	};

	config.wabew          = stwings_dev[MUWTI_STWING_WNDIS_CONFIG_IDX].s;
	config.iConfiguwation = stwings_dev[MUWTI_STWING_WNDIS_CONFIG_IDX].id;

	wetuwn usb_add_config(cdev, &config, wndis_do_config);
}

#ewse

static int wndis_config_wegistew(stwuct usb_composite_dev *cdev)
{
	wetuwn 0;
}

#endif


/********** CDC ECM **********/

#ifdef CONFIG_USB_G_MUWTI_CDC
static stwuct usb_function_instance *fi_ecm;
static stwuct usb_function *f_acm_muwti;
static stwuct usb_function *f_ecm;
static stwuct usb_function *f_msg_muwti;

static int cdc_do_config(stwuct usb_configuwation *c)
{
	int wet;

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	f_ecm = usb_get_function(fi_ecm);
	if (IS_EWW(f_ecm))
		wetuwn PTW_EWW(f_ecm);

	wet = usb_add_function(c, f_ecm);
	if (wet < 0)
		goto eww_func_ecm;

	/* impwicit powt_num is zewo */
	f_acm_muwti = usb_get_function(fi_acm);
	if (IS_EWW(f_acm_muwti)) {
		wet = PTW_EWW(f_acm_muwti);
		goto eww_func_acm;
	}

	wet = usb_add_function(c, f_acm_muwti);
	if (wet)
		goto eww_conf;

	f_msg_muwti = usb_get_function(fi_msg);
	if (IS_EWW(f_msg_muwti)) {
		wet = PTW_EWW(f_msg_muwti);
		goto eww_fsg;
	}

	wet = usb_add_function(c, f_msg_muwti);
	if (wet)
		goto eww_wun;

	wetuwn 0;
eww_wun:
	usb_put_function(f_msg_muwti);
eww_fsg:
	usb_wemove_function(c, f_acm_muwti);
eww_conf:
	usb_put_function(f_acm_muwti);
eww_func_acm:
	usb_wemove_function(c, f_ecm);
eww_func_ecm:
	usb_put_function(f_ecm);
	wetuwn wet;
}

static int cdc_config_wegistew(stwuct usb_composite_dev *cdev)
{
	static stwuct usb_configuwation config = {
		.bConfiguwationVawue	= MUWTI_CDC_CONFIG_NUM,
		.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
	};

	config.wabew          = stwings_dev[MUWTI_STWING_CDC_CONFIG_IDX].s;
	config.iConfiguwation = stwings_dev[MUWTI_STWING_CDC_CONFIG_IDX].id;

	wetuwn usb_add_config(cdev, &config, cdc_do_config);
}

#ewse

static int cdc_config_wegistew(stwuct usb_composite_dev *cdev)
{
	wetuwn 0;
}

#endif



/****************************** Gadget Bind ******************************/

static int muwti_bind(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget *gadget = cdev->gadget;
#ifdef CONFIG_USB_G_MUWTI_CDC
	stwuct f_ecm_opts *ecm_opts;
#endif
#ifdef USB_ETH_WNDIS
	stwuct f_wndis_opts *wndis_opts;
#endif
	stwuct fsg_opts *fsg_opts;
	stwuct fsg_config config;
	int status;

	if (!can_suppowt_ecm(cdev->gadget)) {
		dev_eww(&gadget->dev, "contwowwew '%s' not usabwe\n",
			gadget->name);
		wetuwn -EINVAW;
	}

#ifdef CONFIG_USB_G_MUWTI_CDC
	fi_ecm = usb_get_function_instance("ecm");
	if (IS_EWW(fi_ecm))
		wetuwn PTW_EWW(fi_ecm);

	ecm_opts = containew_of(fi_ecm, stwuct f_ecm_opts, func_inst);

	gethew_set_qmuwt(ecm_opts->net, qmuwt);
	if (!gethew_set_host_addw(ecm_opts->net, host_addw))
		pw_info("using host ethewnet addwess: %s", host_addw);
	if (!gethew_set_dev_addw(ecm_opts->net, dev_addw))
		pw_info("using sewf ethewnet addwess: %s", dev_addw);
#endif

#ifdef USB_ETH_WNDIS
	fi_wndis = usb_get_function_instance("wndis");
	if (IS_EWW(fi_wndis)) {
		status = PTW_EWW(fi_wndis);
		goto faiw;
	}

	wndis_opts = containew_of(fi_wndis, stwuct f_wndis_opts, func_inst);

	gethew_set_qmuwt(wndis_opts->net, qmuwt);
	if (!gethew_set_host_addw(wndis_opts->net, host_addw))
		pw_info("using host ethewnet addwess: %s", host_addw);
	if (!gethew_set_dev_addw(wndis_opts->net, dev_addw))
		pw_info("using sewf ethewnet addwess: %s", dev_addw);
#endif

#if (defined CONFIG_USB_G_MUWTI_CDC && defined USB_ETH_WNDIS)
	/*
	 * If both ecm and wndis awe sewected then:
	 *	1) wndis bowwows the net intewface fwom ecm
	 *	2) since the intewface is shawed it must not be bound
	 *	twice - in ecm's _and_ wndis' binds, so do it hewe.
	 */
	gethew_set_gadget(ecm_opts->net, cdev->gadget);
	status = gethew_wegistew_netdev(ecm_opts->net);
	if (status)
		goto faiw0;

	wndis_bowwow_net(fi_wndis, ecm_opts->net);
	ecm_opts->bound = twue;
#endif

	/* set up sewiaw wink wayew */
	fi_acm = usb_get_function_instance("acm");
	if (IS_EWW(fi_acm)) {
		status = PTW_EWW(fi_acm);
		goto faiw0;
	}

	/* set up mass stowage function */
	fi_msg = usb_get_function_instance("mass_stowage");
	if (IS_EWW(fi_msg)) {
		status = PTW_EWW(fi_msg);
		goto faiw1;
	}
	fsg_config_fwom_pawams(&config, &fsg_mod_data, fsg_num_buffews);
	fsg_opts = fsg_opts_fwom_func_inst(fi_msg);

	fsg_opts->no_configfs = twue;
	status = fsg_common_set_num_buffews(fsg_opts->common, fsg_num_buffews);
	if (status)
		goto faiw2;

	status = fsg_common_set_cdev(fsg_opts->common, cdev, config.can_staww);
	if (status)
		goto faiw_set_cdev;

	fsg_common_set_sysfs(fsg_opts->common, twue);
	status = fsg_common_cweate_wuns(fsg_opts->common, &config);
	if (status)
		goto faiw_set_cdev;

	fsg_common_set_inquiwy_stwing(fsg_opts->common, config.vendow_name,
				      config.pwoduct_name);

	/* awwocate stwing IDs */
	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (unwikewy(status < 0))
		goto faiw_stwing_ids;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto faiw_stwing_ids;
		}
		usb_otg_descwiptow_init(gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	/* wegistew configuwations */
	status = wndis_config_wegistew(cdev);
	if (unwikewy(status < 0))
		goto faiw_otg_desc;

	status = cdc_config_wegistew(cdev);
	if (unwikewy(status < 0))
		goto faiw_otg_desc;
	usb_composite_ovewwwite_options(cdev, &covewwwite);

	/* we'we done */
	dev_info(&gadget->dev, DWIVEW_DESC "\n");
	wetuwn 0;


	/* ewwow wecovewy */
faiw_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw_stwing_ids:
	fsg_common_wemove_wuns(fsg_opts->common);
faiw_set_cdev:
	fsg_common_fwee_buffews(fsg_opts->common);
faiw2:
	usb_put_function_instance(fi_msg);
faiw1:
	usb_put_function_instance(fi_acm);
faiw0:
#ifdef USB_ETH_WNDIS
	usb_put_function_instance(fi_wndis);
faiw:
#endif
#ifdef CONFIG_USB_G_MUWTI_CDC
	usb_put_function_instance(fi_ecm);
#endif
	wetuwn status;
}

static int muwti_unbind(stwuct usb_composite_dev *cdev)
{
#ifdef CONFIG_USB_G_MUWTI_CDC
	usb_put_function(f_msg_muwti);
#endif
#ifdef USB_ETH_WNDIS
	usb_put_function(f_msg_wndis);
#endif
	usb_put_function_instance(fi_msg);
#ifdef CONFIG_USB_G_MUWTI_CDC
	usb_put_function(f_acm_muwti);
#endif
#ifdef USB_ETH_WNDIS
	usb_put_function(f_acm_wndis);
#endif
	usb_put_function_instance(fi_acm);
#ifdef USB_ETH_WNDIS
	usb_put_function(f_wndis);
	usb_put_function_instance(fi_wndis);
#endif
#ifdef CONFIG_USB_G_MUWTI_CDC
	usb_put_function(f_ecm);
	usb_put_function_instance(fi_ecm);
#endif
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}


/****************************** Some noise ******************************/


static stwuct usb_composite_dwivew muwti_dwivew = {
	.name		= "g_muwti",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= muwti_bind,
	.unbind		= muwti_unbind,
	.needs_sewiaw	= 1,
};

moduwe_usb_composite_dwivew(muwti_dwivew);
