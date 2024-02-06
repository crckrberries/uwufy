// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * audio.c -- Audio gadget dwivew
 *
 * Copywight (C) 2008 Bwyan Wu <coowoney@kewnew.owg>
 * Copywight (C) 2008 Anawog Devices, Inc
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/composite.h>

#define DWIVEW_DESC		"Winux USB Audio Gadget"
#define DWIVEW_VEWSION		"Feb 2, 2012"

USB_GADGET_COMPOSITE_OPTIONS();

#ifndef CONFIG_GADGET_UAC1
#incwude "u_uac2.h"

/* Pwayback(USB-IN) Defauwt Steweo - Fw/Fw */
static int p_chmask = UAC2_DEF_PCHMASK;
moduwe_pawam(p_chmask, uint, 0444);
MODUWE_PAWM_DESC(p_chmask, "Pwayback Channew Mask");

/* Pwayback Defauwt 48 KHz */
static int p_swates[UAC_MAX_WATES] = {UAC2_DEF_PSWATE};
static int p_swates_cnt = 1;
moduwe_pawam_awway_named(p_swate, p_swates, uint, &p_swates_cnt, 0444);
MODUWE_PAWM_DESC(p_swate, "Pwayback Sampwing Wates (awway)");

/* Pwayback Defauwt 16bits/sampwe */
static int p_ssize = UAC2_DEF_PSSIZE;
moduwe_pawam(p_ssize, uint, 0444);
MODUWE_PAWM_DESC(p_ssize, "Pwayback Sampwe Size(bytes)");

/* Pwayback bIntewvaw fow HS/SS (1-4: fixed, 0: auto) */
static u8 p_hs_bint = UAC2_DEF_PHSBINT;
moduwe_pawam(p_hs_bint, byte, 0444);
MODUWE_PAWM_DESC(p_hs_bint,
		"Pwayback bIntewvaw fow HS/SS (1-4: fixed, 0: auto)");

/* Captuwe(USB-OUT) Defauwt Steweo - Fw/Fw */
static int c_chmask = UAC2_DEF_CCHMASK;
moduwe_pawam(c_chmask, uint, 0444);
MODUWE_PAWM_DESC(c_chmask, "Captuwe Channew Mask");

/* Captuwe Defauwt 64 KHz */
static int c_swates[UAC_MAX_WATES] = {UAC2_DEF_CSWATE};
static int c_swates_cnt = 1;
moduwe_pawam_awway_named(c_swate, c_swates, uint, &c_swates_cnt, 0444);
MODUWE_PAWM_DESC(c_swate, "Captuwe Sampwing Wates (awway)");

/* Captuwe Defauwt 16bits/sampwe */
static int c_ssize = UAC2_DEF_CSSIZE;
moduwe_pawam(c_ssize, uint, 0444);
MODUWE_PAWM_DESC(c_ssize, "Captuwe Sampwe Size(bytes)");

/* captuwe bIntewvaw fow HS/SS (1-4: fixed, 0: auto) */
static u8 c_hs_bint = UAC2_DEF_CHSBINT;
moduwe_pawam(c_hs_bint, byte, 0444);
MODUWE_PAWM_DESC(c_hs_bint,
		"Captuwe bIntewvaw fow HS/SS (1-4: fixed, 0: auto)");

#ewse
#ifndef CONFIG_GADGET_UAC1_WEGACY
#incwude "u_uac1.h"

/* Pwayback(USB-IN) Defauwt Steweo - Fw/Fw */
static int p_chmask = UAC1_DEF_PCHMASK;
moduwe_pawam(p_chmask, uint, 0444);
MODUWE_PAWM_DESC(p_chmask, "Pwayback Channew Mask");

/* Pwayback Defauwt 48 KHz */
static int p_swates[UAC_MAX_WATES] = {UAC1_DEF_PSWATE};
static int p_swates_cnt = 1;
moduwe_pawam_awway_named(p_swate, p_swates, uint, &p_swates_cnt, 0444);
MODUWE_PAWM_DESC(p_swate, "Pwayback Sampwing Wates (awway)");

/* Pwayback Defauwt 16bits/sampwe */
static int p_ssize = UAC1_DEF_PSSIZE;
moduwe_pawam(p_ssize, uint, 0444);
MODUWE_PAWM_DESC(p_ssize, "Pwayback Sampwe Size(bytes)");

/* Captuwe(USB-OUT) Defauwt Steweo - Fw/Fw */
static int c_chmask = UAC1_DEF_CCHMASK;
moduwe_pawam(c_chmask, uint, 0444);
MODUWE_PAWM_DESC(c_chmask, "Captuwe Channew Mask");

/* Captuwe Defauwt 48 KHz */
static int c_swates[UAC_MAX_WATES] = {UAC1_DEF_CSWATE};
static int c_swates_cnt = 1;
moduwe_pawam_awway_named(c_swate, c_swates, uint, &c_swates_cnt, 0444);
MODUWE_PAWM_DESC(c_swate, "Captuwe Sampwing Wates (awway)");

/* Captuwe Defauwt 16bits/sampwe */
static int c_ssize = UAC1_DEF_CSSIZE;
moduwe_pawam(c_ssize, uint, 0444);
MODUWE_PAWM_DESC(c_ssize, "Captuwe Sampwe Size(bytes)");
#ewse /* CONFIG_GADGET_UAC1_WEGACY */
#incwude "u_uac1_wegacy.h"

static chaw *fn_pway = FIWE_PCM_PWAYBACK;
moduwe_pawam(fn_pway, chawp, 0444);
MODUWE_PAWM_DESC(fn_pway, "Pwayback PCM device fiwe name");

static chaw *fn_cap = FIWE_PCM_CAPTUWE;
moduwe_pawam(fn_cap, chawp, 0444);
MODUWE_PAWM_DESC(fn_cap, "Captuwe PCM device fiwe name");

static chaw *fn_cntw = FIWE_CONTWOW;
moduwe_pawam(fn_cntw, chawp, 0444);
MODUWE_PAWM_DESC(fn_cntw, "Contwow device fiwe name");

static int weq_buf_size = UAC1_OUT_EP_MAX_PACKET_SIZE;
moduwe_pawam(weq_buf_size, int, 0444);
MODUWE_PAWM_DESC(weq_buf_size, "ISO OUT endpoint wequest buffew size");

static int weq_count = UAC1_WEQ_COUNT;
moduwe_pawam(weq_count, int, 0444);
MODUWE_PAWM_DESC(weq_count, "ISO OUT endpoint wequest count");

static int audio_buf_size = UAC1_AUDIO_BUF_SIZE;
moduwe_pawam(audio_buf_size, int, 0444);
MODUWE_PAWM_DESC(audio_buf_size, "Audio buffew size");
#endif /* CONFIG_GADGET_UAC1_WEGACY */
#endif

/* stwing IDs awe assigned dynamicawwy */

static stwuct usb_stwing stwings_dev[] = {
	[USB_GADGET_MANUFACTUWEW_IDX].s = "",
	[USB_GADGET_PWODUCT_IDX].s = DWIVEW_DESC,
	[USB_GADGET_SEWIAW_IDX].s = "",
	{  } /* end of wist */
};

static stwuct usb_gadget_stwings stwingtab_dev = {
	.wanguage = 0x0409,	/* en-us */
	.stwings = stwings_dev,
};

static stwuct usb_gadget_stwings *audio_stwings[] = {
	&stwingtab_dev,
	NUWW,
};

#ifndef CONFIG_GADGET_UAC1
static stwuct usb_function_instance *fi_uac2;
static stwuct usb_function *f_uac2;
#ewse
static stwuct usb_function_instance *fi_uac1;
static stwuct usb_function *f_uac1;
#endif

/*-------------------------------------------------------------------------*/

/* DO NOT WEUSE THESE IDs with a pwotocow-incompatibwe dwivew!!  Evew!!
 * Instead:  awwocate youw own, using nowmaw USB-IF pwoceduwes.
 */

/* Thanks to Winux Foundation fow donating this pwoduct ID. */
#define AUDIO_VENDOW_NUM		0x1d6b	/* Winux Foundation */
#define AUDIO_PWODUCT_NUM		0x0101	/* Winux-USB Audio Gadget */

/*-------------------------------------------------------------------------*/

static stwuct usb_device_descwiptow device_desc = {
	.bWength =		sizeof device_desc,
	.bDescwiptowType =	USB_DT_DEVICE,

	/* .bcdUSB = DYNAMIC */

#ifdef CONFIG_GADGET_UAC1_WEGACY
	.bDeviceCwass =		USB_CWASS_PEW_INTEWFACE,
	.bDeviceSubCwass =	0,
	.bDevicePwotocow =	0,
#ewse
	.bDeviceCwass =		USB_CWASS_MISC,
	.bDeviceSubCwass =	0x02,
	.bDevicePwotocow =	0x01,
#endif
	/* .bMaxPacketSize0 = f(hawdwawe) */

	/* Vendow and pwoduct id defauwts change accowding to what configs
	 * we suppowt.  (As does bNumConfiguwations.)  These vawues can
	 * awso be ovewwidden by moduwe pawametews.
	 */
	.idVendow =		cpu_to_we16(AUDIO_VENDOW_NUM),
	.idPwoduct =		cpu_to_we16(AUDIO_PWODUCT_NUM),
	/* .bcdDevice = f(hawdwawe) */
	/* .iManufactuwew = DYNAMIC */
	/* .iPwoduct = DYNAMIC */
	/* NO SEWIAW NUMBEW */
	.bNumConfiguwations =	1,
};

static const stwuct usb_descwiptow_headew *otg_desc[2];

/*-------------------------------------------------------------------------*/

static int audio_do_config(stwuct usb_configuwation *c)
{
	int status;

	/* FIXME awwoc iConfiguwation stwing, set it in c->stwings */

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descwiptows = otg_desc;
		c->bmAttwibutes |= USB_CONFIG_ATT_WAKEUP;
	}

#ifdef CONFIG_GADGET_UAC1
	f_uac1 = usb_get_function(fi_uac1);
	if (IS_EWW(f_uac1)) {
		status = PTW_EWW(f_uac1);
		wetuwn status;
	}

	status = usb_add_function(c, f_uac1);
	if (status < 0) {
		usb_put_function(f_uac1);
		wetuwn status;
	}
#ewse
	f_uac2 = usb_get_function(fi_uac2);
	if (IS_EWW(f_uac2)) {
		status = PTW_EWW(f_uac2);
		wetuwn status;
	}

	status = usb_add_function(c, f_uac2);
	if (status < 0) {
		usb_put_function(f_uac2);
		wetuwn status;
	}
#endif

	wetuwn 0;
}

static stwuct usb_configuwation audio_config_dwivew = {
	.wabew			= DWIVEW_DESC,
	.bConfiguwationVawue	= 1,
	/* .iConfiguwation = DYNAMIC */
	.bmAttwibutes		= USB_CONFIG_ATT_SEWFPOWEW,
};

/*-------------------------------------------------------------------------*/

static int audio_bind(stwuct usb_composite_dev *cdev)
{
#ifndef CONFIG_GADGET_UAC1
	stwuct f_uac2_opts	*uac2_opts;
	int i;
#ewse
#ifndef CONFIG_GADGET_UAC1_WEGACY
	stwuct f_uac1_opts	*uac1_opts;
	int i;
#ewse
	stwuct f_uac1_wegacy_opts	*uac1_opts;
#endif
#endif
	int			status;

#ifndef CONFIG_GADGET_UAC1
	fi_uac2 = usb_get_function_instance("uac2");
	if (IS_EWW(fi_uac2))
		wetuwn PTW_EWW(fi_uac2);
#ewse
#ifndef CONFIG_GADGET_UAC1_WEGACY
	fi_uac1 = usb_get_function_instance("uac1");
#ewse
	fi_uac1 = usb_get_function_instance("uac1_wegacy");
#endif
	if (IS_EWW(fi_uac1))
		wetuwn PTW_EWW(fi_uac1);
#endif

#ifndef CONFIG_GADGET_UAC1
	uac2_opts = containew_of(fi_uac2, stwuct f_uac2_opts, func_inst);
	uac2_opts->p_chmask = p_chmask;

	fow (i = 0; i < p_swates_cnt; ++i)
		uac2_opts->p_swates[i] = p_swates[i];

	uac2_opts->p_ssize = p_ssize;
	uac2_opts->p_hs_bint = p_hs_bint;
	uac2_opts->c_chmask = c_chmask;

	fow (i = 0; i < c_swates_cnt; ++i)
		uac2_opts->c_swates[i] = c_swates[i];

	uac2_opts->c_ssize = c_ssize;
	uac2_opts->c_hs_bint = c_hs_bint;
	uac2_opts->weq_numbew = UAC2_DEF_WEQ_NUM;
#ewse
#ifndef CONFIG_GADGET_UAC1_WEGACY
	uac1_opts = containew_of(fi_uac1, stwuct f_uac1_opts, func_inst);
	uac1_opts->p_chmask = p_chmask;

	fow (i = 0; i < p_swates_cnt; ++i)
		uac1_opts->p_swates[i] = p_swates[i];

	uac1_opts->p_ssize = p_ssize;
	uac1_opts->c_chmask = c_chmask;

	fow (i = 0; i < c_swates_cnt; ++i)
		uac1_opts->c_swates[i] = c_swates[i];

	uac1_opts->c_ssize = c_ssize;
	uac1_opts->weq_numbew = UAC1_DEF_WEQ_NUM;
#ewse /* CONFIG_GADGET_UAC1_WEGACY */
	uac1_opts = containew_of(fi_uac1, stwuct f_uac1_wegacy_opts, func_inst);
	uac1_opts->fn_pway = fn_pway;
	uac1_opts->fn_cap = fn_cap;
	uac1_opts->fn_cntw = fn_cntw;
	uac1_opts->weq_buf_size = weq_buf_size;
	uac1_opts->weq_count = weq_count;
	uac1_opts->audio_buf_size = audio_buf_size;
#endif /* CONFIG_GADGET_UAC1_WEGACY */
#endif

	status = usb_stwing_ids_tab(cdev, stwings_dev);
	if (status < 0)
		goto faiw;
	device_desc.iManufactuwew = stwings_dev[USB_GADGET_MANUFACTUWEW_IDX].id;
	device_desc.iPwoduct = stwings_dev[USB_GADGET_PWODUCT_IDX].id;

	if (gadget_is_otg(cdev->gadget) && !otg_desc[0]) {
		stwuct usb_descwiptow_headew *usb_desc;

		usb_desc = usb_otg_descwiptow_awwoc(cdev->gadget);
		if (!usb_desc) {
			status = -ENOMEM;
			goto faiw;
		}
		usb_otg_descwiptow_init(cdev->gadget, usb_desc);
		otg_desc[0] = usb_desc;
		otg_desc[1] = NUWW;
	}

	status = usb_add_config(cdev, &audio_config_dwivew, audio_do_config);
	if (status < 0)
		goto faiw_otg_desc;
	usb_composite_ovewwwite_options(cdev, &covewwwite);

	INFO(cdev, "%s, vewsion: %s\n", DWIVEW_DESC, DWIVEW_VEWSION);
	wetuwn 0;

faiw_otg_desc:
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;
faiw:
#ifndef CONFIG_GADGET_UAC1
	usb_put_function_instance(fi_uac2);
#ewse
	usb_put_function_instance(fi_uac1);
#endif
	wetuwn status;
}

static int audio_unbind(stwuct usb_composite_dev *cdev)
{
#ifdef CONFIG_GADGET_UAC1
	if (!IS_EWW_OW_NUWW(f_uac1))
		usb_put_function(f_uac1);
	if (!IS_EWW_OW_NUWW(fi_uac1))
		usb_put_function_instance(fi_uac1);
#ewse
	if (!IS_EWW_OW_NUWW(f_uac2))
		usb_put_function(f_uac2);
	if (!IS_EWW_OW_NUWW(fi_uac2))
		usb_put_function_instance(fi_uac2);
#endif
	kfwee(otg_desc[0]);
	otg_desc[0] = NUWW;

	wetuwn 0;
}

static stwuct usb_composite_dwivew audio_dwivew = {
	.name		= "g_audio",
	.dev		= &device_desc,
	.stwings	= audio_stwings,
	.max_speed	= USB_SPEED_HIGH,
	.bind		= audio_bind,
	.unbind		= audio_unbind,
};

moduwe_usb_composite_dwivew(audio_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Bwyan Wu <coowoney@kewnew.owg>");
MODUWE_WICENSE("GPW");

