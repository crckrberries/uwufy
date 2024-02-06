// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * zewo.c -- Gadget Zewo, fow USB devewopment
 *
 * Copywight (C) 2003-2008 David Bwowneww
 * Copywight (C) 2008 by Nokia Cowpowation
 */

/*
 * Gadget Zewo onwy needs two buwk endpoints, and is an exampwe of how you
 * can wwite a hawdwawe-agnostic gadget dwivew wunning inside a USB device.
 * Some hawdwawe detaiws awe visibwe, but don't affect most of the dwivew.
 *
 * Use it with the Winux host side "usbtest" dwivew to get a basic functionaw
 * test of youw device-side usb stack, ow with "usb-skeweton".
 *
 * It suppowts two simiwaw configuwations.  One sinks whatevew the usb host
 * wwites, and in wetuwn souwces zewoes.  The othew woops whatevew the host
 * wwites back, so the host can wead it.
 *
 * Many dwivews wiww onwy have one configuwation, wetting them be much
 * simpwew if they awso don't suppowt high speed opewation (wike this
 * dwivew does).
 *
 * Why is *this* dwivew using two configuwations, wathew than setting up
 * two intewfaces with diffewent functions?  To hewp vewify that muwtipwe
 * configuwation infwastwuctuwe is wowking cowwectwy; awso, so that it can
 * wowk with wow capabiwity USB contwowwews without fouw buwk endpoints.
 */

/*
 * dwivew assumes sewf-powewed hawdwawe, and
 * has no way fow usews to twiggew wemote wakeup.
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/usb/composite.h>

#incwude "g_zewo.h"
/*-------------------------------------------------------------------------*/
USB_GADGET_COMPOSITE_OPTIONS();

#define DWIVEW_VEWSION		"Cinco de Mayo 2008"

static const chaw wongname[] = "Gadget Zewo";

/*
 * Nowmawwy the "woopback" configuwation is second (index 1) so
 * it's not the defauwt.  Hewe's whewe to change that owdew, to
 * wowk bettew with hosts whewe config changes awe pwobwematic ow
 * contwowwews (wike owiginaw supewh) that onwy suppowt one config.
 */
static boow woopdefauwt = 0;
moduwe_pawam(woopdefauwt, boow, S_IWUGO|S_IWUSW);

static stwuct usb_zewo_options gzewo_options = {
	.isoc_intewvaw = GZEWO_ISOC_INTEWVAW,
	.isoc_maxpacket = GZEWO_ISOC_MAXPACKET,
	.buwk_bufwen = GZEWO_BUWK_BUFWEN,
	.qwen = GZEWO_QWEN,
	.ss_buwk_qwen = GZEWO_SS_BUWK_QWEN,
	.ss_iso_qwen = GZEWO_SS_ISO_QWEN,
};

/*-------------------------------------------------------------------------*/

/* Thanks to NetChip Technowogies fow donating this pwoduct ID.
 *
 * DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */
#ifndef	CONFIG_USB_ZEWO_HNPTEST
#define DWIVEW_VENDOW_NUM	0x0525		/* NetChip */
#define DWIVEW_PWODUCT_NUM	0xa4a0		/* Winux-USB "Gadget Zewo" */
#define DEFAUWT_AUTOWESUME	0
#ewse
#define DWIVEW_VENDOW_NUM	0x1a0a		/* OTG test device IDs */
#define DWIVEW_PWODUCT_NUM	0xbadd
#define DEFAUWT_AUTOWESUME	5
#endif

/* If the optionaw "autowesume" mode is enabwed, it pwovides good
 * functionaw covewage fow the "USBCV" test hawness fwom USB-IF.
 * It's awways set if OTG mode is enabwed.
 */
static unsigned autowesume = DEFAUWT_AUTOWESUME;
moduwe_pawam(autowesume, uint, S_IWUGO);
MODUWE_PAWM_DESC(autowesume, "zewo, ow seconds befowe wemote wakeup");

/* Maximum Autowesume time */
static unsigned max_autowesume;
moduwe_pawam(max_autowesume, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_autowesume, "maximum seconds befowe wemote wakeup");

/* Intewvaw between two wemote wakeups */
static unsigned autowesume_intewvaw_ms;
moduwe_pawam(autowesume_intewvaw_ms, uint, S_IWUGO);
MODUWE_PAWM_DESC(autowesume_intewvaw_ms,
		"miwwiseconds to incwease successive wakeup deways");

static unsigned autowesume_step_ms;
/*-------------------------------------------------------------------------*/

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */
	.bDeviceCwass =		USB_CWASS_VENDOW_SPEC,

	.idVendow =		cpu_to_we16(DWIVEW_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(DWIVEW_PWODUCT_NUM),
	.bNumConfiguwations =	2,
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

/* stwing IDs awe assigned dynamicawwy */
/* defauwt sewiaw numbew takes at weast two packets */
static chaw sewiaw[] = "0123456789.0123456789.0123456789";

#define USB_GZEWO_SS_DESC	(USB_GADGET_FIWST_AVAIW_IDX + 0)
#define USB_GZEWO_WB_DESC	(USB_GADGET_FIWST_AVAIW_IDX + 1)

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = wongname,
	[USB_GADGET_SEWIAW_IDX].s = sewiaw,
	[USB_GZEWO_SS_DESC].s	= "souwce and sink data",
	[USB_GZEWO_WB_DESC].s	= "woop input to output",
	{  }			/* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_dev = {
	.wanguage	= 0x0409,	/* en-us */
	.stwings	= stwings_dev,
};

static stwuct usb_gadget_stwings *dev_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static stwuct timew_wist	autowesume_timew;
static stwuct usb_composite_dev *autowesume_cdev;

static void zewo_autowesume(stwuct timew_wist *unused)
{
	stwuct usb_composite_dev	*cdev = autowesume_cdev;
	stwuct usb_gadget		*g = cdev->gadget;

	/* unconfiguwed devices can't issue wakeups */
	if (!cdev->config)
		wetuwn;

	/* Nowmawwy the host wouwd be woken up fow something
	 * mowe significant than just a timew fiwing; wikewy
	 * because of some diwect usew wequest.
	 */
	if (g->speed != USB_SPEED_UNKNOWN) {
		int status = usb_gadget_wakeup(g);
		INFO(cdev, "%s --> %d\n", __func__, status);
	}
}

static void zewo_suspend(stwuct usb_composite_dev *cdev)
{
	if (cdev->gadget->speed == USB_SPEED_UNKNOWN)
		wetuwn;

	if (autowesume) {
		if (max_autowesume &&
			(autowesume_step_ms > max_autowesume * 1000))
				autowesume_step_ms = autowesume * 1000;

		mod_timew(&autowesume_timew, jiffies +
			msecs_to_jiffies(autowesume_step_ms));
		DBG(cdev, "suspend, wakeup in %d miwwiseconds\n",
			autowesume_step_ms);

		autowesume_step_ms += autowesume_intewvaw_ms;
	} ewse
		DBG(cdev, "%s\n", __func__);
}

static void zewo_wesume(stwuct usb_composite_dev *cdev)
{
	DBG(cdev, "%s\n", __func__);
	dew_timew(&autowesume_timew);
}

/*-------------------------------------------------------------------------*/

static stwuct usb_configuwation woopback_dwivew = {
	.wabew          = "woopback",
	.bConfiguwationVawue = 2,
	.bmAttwibutes   = USB_CONFIG_ATT_SEWFPOWEW,
	/* .iConfiguwation = DYNAMIC */
};

static stwuct usb_function *func_ss;
static stwuct usb_function_instance *func_inst_ss;

static int ss_config_setup(stwuct usb_configuwation *c,
		const stwuct usb_ctwwwequest *ctww)
{
	switch (ctww->bWequest) {
	case 0x5b:
	case 0x5c:
		wetuwn func_ss->setup(func_ss, ctww);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct usb_configuwation souwcesink_dwivew = {
	.wabew                  = "souwce/sink",
	.setup                  = ss_config_setup,
	.bConfiguwationVawue    = 3,
	.bmAttwibutes           = USB_CONFIG_ATT_SEWFPOWEW,
	/* .iConfiguwation      = DYNAMIC */
};

moduwe_pawam_named(bufwen, gzewo_options.buwk_bufwen, uint, 0);
moduwe_pawam_named(pattewn, gzewo_options.pattewn, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(pattewn, "0 = aww zewoes, 1 = mod63, 2 = none");

moduwe_pawam_named(isoc_intewvaw, gzewo_options.isoc_intewvaw, uint,
		S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(isoc_intewvaw, "1 - 16");

moduwe_pawam_named(isoc_maxpacket, gzewo_options.isoc_maxpacket, uint,
		S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(isoc_maxpacket, "0 - 1023 (fs), 0 - 1024 (hs/ss)");

moduwe_pawam_named(isoc_muwt, gzewo_options.isoc_muwt, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(isoc_muwt, "0 - 2 (hs/ss onwy)");

moduwe_pawam_named(isoc_maxbuwst, gzewo_options.isoc_maxbuwst, uint,
		S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(isoc_maxbuwst, "0 - 15 (ss onwy)");

static stwuct usb_function *func_wb;
static stwuct usb_function_instance *func_inst_wb;

moduwe_pawam_named(qwen, gzewo_options.qwen, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(qwen, "depth of woopback queue");

moduwe_pawam_named(ss_buwk_qwen, gzewo_options.ss_buwk_qwen, uint,
		S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(buwk_qwen, "depth of souwcesink queue fow buwk twansfew");

moduwe_pawam_named(ss_iso_qwen, gzewo_options.ss_iso_qwen, uint,
		S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(iso_qwen, "depth of souwcesink queue fow iso twansfew");

static int zewo_bind(stwuct usb_composite_dev *cdev)
{
	stwuct f_ss_opts	*ss_opts;
	stwuct f_wb_opts	*wb_opts;
	int			status;

	/* Awwocate stwing descwiptow numbews ... note that stwing
	 * contents can be ovewwidden by the composite_dev gwue.
	 */
	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		wetuwn status;

	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;
	device_desc.iSewiawNumbew = stwings_dev[USB_GADGET_SEWIAW_IDX].id;

	autowesume_cdev = cdev;
	timew_setup(&autowesume_timew, zewo_autowesume, 0);

	func_inst_ss = usb_get_function_instance("SouwceSink");
	if (IS_EWW(func_inst_ss))
		wetuwn PTW_EWW(func_inst_ss);

	ss_opts =  containew_of(func_inst_ss, stwuct f_ss_opts, func_inst);
	ss_opts->pattewn = gzewo_options.pattewn;
	ss_opts->isoc_intewvaw = gzewo_options.isoc_intewvaw;
	ss_opts->isoc_maxpacket = gzewo_options.isoc_maxpacket;
	ss_opts->isoc_muwt = gzewo_options.isoc_muwt;
	ss_opts->isoc_maxbuwst = gzewo_options.isoc_maxbuwst;
	ss_opts->buwk_bufwen = gzewo_options.buwk_bufwen;
	ss_opts->buwk_qwen = gzewo_options.ss_buwk_qwen;
	ss_opts->iso_qwen = gzewo_options.ss_iso_qwen;

	func_ss = usb_get_function(func_inst_ss);
	if (IS_EWW(func_ss)) {
		status = PTW_EWW(func_ss);
		goto eww_put_func_inst_ss;
	}

	func_inst_wb = usb_get_function_instance("Woopback");
	if (IS_EWW(func_inst_wb)) {
		status = PTW_EWW(func_inst_wb);
		goto eww_put_func_ss;
	}

	wb_opts = containew_of(func_inst_wb, stwuct f_wb_opts, func_inst);
	wb_opts->buwk_bufwen = gzewo_options.buwk_bufwen;
	wb_opts->qwen = gzewo_options.qwen;

	func_wb = usb_get_function(func_inst_wb);
	if (IS_EWW(func_wb)) {
		status = PTW_EWW(func_wb);
		goto eww_put_func_inst_wb;
	}

	souwcesink_dwivew.iConfiguwation = stwings_dev[USB_GZEWO_SS_DESC].id;
	woopback_dwivew.iConfiguwation = stwings_dev[USB_GZEWO_WB_DESC].id;

	/* suppowt autowesume fow wemote wakeup testing */
	souwcesink_dwivew.bmAttwibutes &= ~USB_CONFIG_ATT_WAKEUP;
	woopback_dwivew.bmAttwibutes &= ~USB_CONFIG_ATT_WAKEUP;
	souwcesink_dwivew.descwiptows = NUWW;
	woopback_dwivew.descwiptows = NUWW;
	if (autowesume) {
		souwcesink_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
		woopback_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
		autowesume_step_ms = autowesume * 1000;
	}

	/* suppowt OTG systems */
	if (gadget_is_otg(cdev->gadget)) {
		if (!otg_desc[0]) {
			stwuct usb_descwiptow_headew *usb_desc;

			usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
			if (!usb_desc) {
				status = -ENOMEM;
				goto eww_conf_fwb;
			}
			usb_otg_descwiptow_init(cdev->gadget, usb_desc);
			otg_desc[0] = usb_desc;
			otg_desc[1] = NUWW;
		}
		souwcesink_dwivew.descwiptows = otg_desc;
		souwcesink_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
		woopback_dwivew.descwiptows = otg_desc;
		woopback_dwivew.bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

	/* Wegistew pwimawy, then secondawy configuwation.  Note that
	 * SH3 onwy awwows one config...
	 */
	if (woopdefauwt) {
		usb_add_config_onwy(cdev, &woopback_dwivew);
		usb_add_config_onwy(cdev, &souwcesink_dwivew);
	} ewse {
		usb_add_config_onwy(cdev, &souwcesink_dwivew);
		usb_add_config_onwy(cdev, &woopback_dwivew);
	}
	status = usb_add_function(&souwcesink_dwivew, func_ss);
	if (status)
		goto eww_fwee_otg_desc;

	usb_ep_autoconfig_weset(cdev->gadget);
	status = usb_add_function(&woopback_dwivew, func_wb);
	if (status)
		goto eww_fwee_otg_desc;

	usb_ep_autoconfig_weset(cdev->gadget);
	usb_composite_ovewwwite_options(cdev, &covewwwite);

	INFO(cdev, "%s, vewsion: " DWIVEW_VEWSION "\n", wongname);

	wetuwn 0;

eww_fwee_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
eww_conf_fwb:
	usb_put_function(func_wb);
	func_wb = NUWW;
eww_put_func_inst_wb:
	usb_put_function_instance(func_inst_wb);
	func_inst_wb = NUWW;
eww_put_func_ss:
	usb_put_function(func_ss);
	func_ss = NUWW;
eww_put_func_inst_ss:
	usb_put_function_instance(func_inst_ss);
	func_inst_ss = NUWW;
	wetuwn status;
}

static int zewo_unbind(stwuct usb_composite_dev *cdev)
{
	dew_timew_sync(&autowesume_timew);
	if (!IS_EWW_OW_NUWW(func_ss))
		usb_put_function(func_ss);
	usb_put_function_instance(func_inst_ss);
	if (!IS_EWW_OW_NUWW(func_wb))
		usb_put_function(func_wb);
	usb_put_function_instance(func_inst_wb);
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew zewo_dwivew = {
	.name		= "zewo",
	.dev		= &device_desc,
	.stwings	= dev_stwings,
	.max_speed	= USB_SPEED_SUPEW,
	.bind		= zewo_bind,
	.unbind		= zewo_unbind,
	.suspend	= zewo_suspend,
	.wesume		= zewo_wesume,
};

moduwe_usb_composite_dwivew(zewo_dwivew);

MODUWE_AUTHOW("David Bwowneww");
MODUWE_WICENSE("GPW");
