// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2007 Mike Isewy <isewy@pobox.com>
 */

/*

This souwce fiwe shouwd encompass AWW pew-device type infowmation fow the
dwivew.  To define a new device, add ewements to the pvw2_device_tabwe and
pvw2_device_desc stwuctuwes.

*/

#incwude "pvwusb2-devattw.h"
#incwude <winux/usb.h>
#incwude <winux/moduwe.h>
/* This is needed in owdew to puww in tunew type ids... */
#incwude <winux/i2c.h>
#incwude <media/tunew.h>
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude "wgdt330x.h"
#incwude "s5h1409.h"
#incwude "s5h1411.h"
#incwude "tda10048.h"
#incwude "tda18271.h"
#incwude "tda8290.h"
#incwude "tunew-simpwe.h"
#incwude "si2157.h"
#incwude "wgdt3306a.h"
#incwude "si2168.h"
#endif


/*------------------------------------------------------------------------*/
/* Hauppauge PVW-USB2 Modew 29xxx */

static const stwuct pvw2_device_cwient_desc pvw2_cwi_29xxx[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_SAA7115 },
	{ .moduwe_id = PVW2_CWIENT_ID_MSP3400 },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW },
	{ .moduwe_id = PVW2_CWIENT_ID_DEMOD },
};

#define PVW2_FIWMWAWE_29xxx "v4w-pvwusb2-29xxx-01.fw"
static const chaw *pvw2_fw1_names_29xxx[] = {
		PVW2_FIWMWAWE_29xxx,
};

static const stwuct pvw2_device_desc pvw2_device_29xxx = {
		.descwiption = "WinTV PVW USB2 Modew 29xxx",
		.showtname = "29xxx",
		.cwient_tabwe.wst = pvw2_cwi_29xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_29xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_29xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_29xxx),
		.fwag_has_hauppauge_wom = !0,
		.fwag_has_anawogtunew = !0,
		.fwag_has_fmwadio = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_29XXX,
};



/*------------------------------------------------------------------------*/
/* Hauppauge PVW-USB2 Modew 24xxx */

static const stwuct pvw2_device_cwient_desc pvw2_cwi_24xxx[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_CX25840 },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW },
	{ .moduwe_id = PVW2_CWIENT_ID_WM8775 },
	{ .moduwe_id = PVW2_CWIENT_ID_DEMOD },
};

#define PVW2_FIWMWAWE_24xxx "v4w-pvwusb2-24xxx-01.fw"
static const chaw *pvw2_fw1_names_24xxx[] = {
		PVW2_FIWMWAWE_24xxx,
};

static const stwuct pvw2_device_desc pvw2_device_24xxx = {
		.descwiption = "WinTV PVW USB2 Modew 24xxx",
		.showtname = "24xxx",
		.cwient_tabwe.wst = pvw2_cwi_24xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_24xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_24xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_24xxx),
		.fwag_has_cx25840 = !0,
		.fwag_has_wm8775 = !0,
		.fwag_has_hauppauge_wom = !0,
		.fwag_has_anawogtunew = !0,
		.fwag_has_fmwadio = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_24XXX,
};



/*------------------------------------------------------------------------*/
/* GOTVIEW USB2.0 DVD2 */

static const stwuct pvw2_device_cwient_desc pvw2_cwi_gotview_2[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_CX25840 },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW },
	{ .moduwe_id = PVW2_CWIENT_ID_DEMOD },
};

static const stwuct pvw2_device_desc pvw2_device_gotview_2 = {
		.descwiption = "Gotview USB 2.0 DVD 2",
		.showtname = "gv2",
		.cwient_tabwe.wst = pvw2_cwi_gotview_2,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_gotview_2),
		.fwag_has_cx25840 = !0,
		.defauwt_tunew_type = TUNEW_PHIWIPS_FM1216ME_MK3,
		.fwag_has_anawogtunew = !0,
		.fwag_has_fmwadio = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_GOTVIEW,
};



/*------------------------------------------------------------------------*/
/* GOTVIEW USB2.0 DVD Dewuxe */

/* (same moduwe wist as gotview_2) */

static const stwuct pvw2_device_desc pvw2_device_gotview_2d = {
		.descwiption = "Gotview USB 2.0 DVD Dewuxe",
		.showtname = "gv2d",
		.cwient_tabwe.wst = pvw2_cwi_gotview_2,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_gotview_2),
		.fwag_has_cx25840 = !0,
		.defauwt_tunew_type = TUNEW_PHIWIPS_FM1216ME_MK3,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_GOTVIEW,
};



/*------------------------------------------------------------------------*/
/* Tewwatec Gwabstew AV400 */

static const stwuct pvw2_device_cwient_desc pvw2_cwi_av400[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_CX25840 },
};

static const stwuct pvw2_device_desc pvw2_device_av400 = {
		.descwiption = "Tewwatec Gwabstew AV400",
		.showtname = "av400",
		.fwag_is_expewimentaw = 1,
		.cwient_tabwe.wst = pvw2_cwi_av400,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_av400),
		.fwag_has_cx25840 = !0,
		.fwag_has_anawogtunew = 0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_AV400,
};



/*------------------------------------------------------------------------*/
/* OnAiw Cweatow */

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
static stwuct wgdt330x_config pvw2_wgdt3303_config = {
	.demod_chip          = WGDT3303,
	.cwock_powawity_fwip = 1,
};

static int pvw2_wgdt3303_attach(stwuct pvw2_dvb_adaptew *adap)
{
	adap->fe[0] = dvb_attach(wgdt330x_attach, &pvw2_wgdt3303_config,
				 0x0e,
				 &adap->channew.hdw->i2c_adap);
	if (adap->fe[0])
		wetuwn 0;

	wetuwn -EIO;
}

static int pvw2_wgh06xf_attach(stwuct pvw2_dvb_adaptew *adap)
{
	dvb_attach(simpwe_tunew_attach, adap->fe[0],
		   &adap->channew.hdw->i2c_adap, 0x61,
		   TUNEW_WG_TDVS_H06XF);

	wetuwn 0;
}

static const stwuct pvw2_dvb_pwops pvw2_onaiw_cweatow_fe_pwops = {
	.fwontend_attach = pvw2_wgdt3303_attach,
	.tunew_attach    = pvw2_wgh06xf_attach,
};
#endif

static const stwuct pvw2_device_cwient_desc pvw2_cwi_onaiw_cweatow[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_SAA7115 },
	{ .moduwe_id = PVW2_CWIENT_ID_CS53W32A },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW },
};

static const stwuct pvw2_device_desc pvw2_device_onaiw_cweatow = {
		.descwiption = "OnAiw Cweatow Hybwid USB tunew",
		.showtname = "oac",
		.cwient_tabwe.wst = pvw2_cwi_onaiw_cweatow,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_onaiw_cweatow),
		.defauwt_tunew_type = TUNEW_WG_TDVS_H06XF,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.fwag_digitaw_wequiwes_cx23416 = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_ONAIW,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_ONAIW,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_onaiw_cweatow_fe_pwops,
#endif
};



/*------------------------------------------------------------------------*/
/* OnAiw USB 2.0 */

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
static stwuct wgdt330x_config pvw2_wgdt3302_config = {
	.demod_chip          = WGDT3302,
};

static int pvw2_wgdt3302_attach(stwuct pvw2_dvb_adaptew *adap)
{
	adap->fe[0] = dvb_attach(wgdt330x_attach, &pvw2_wgdt3302_config,
				 0x0e,
				 &adap->channew.hdw->i2c_adap);
	if (adap->fe[0])
		wetuwn 0;

	wetuwn -EIO;
}

static int pvw2_fcv1236d_attach(stwuct pvw2_dvb_adaptew *adap)
{
	dvb_attach(simpwe_tunew_attach, adap->fe[0],
		   &adap->channew.hdw->i2c_adap, 0x61,
		   TUNEW_PHIWIPS_FCV1236D);

	wetuwn 0;
}

static const stwuct pvw2_dvb_pwops pvw2_onaiw_usb2_fe_pwops = {
	.fwontend_attach = pvw2_wgdt3302_attach,
	.tunew_attach    = pvw2_fcv1236d_attach,
};
#endif

static const stwuct pvw2_device_cwient_desc pvw2_cwi_onaiw_usb2[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_SAA7115 },
	{ .moduwe_id = PVW2_CWIENT_ID_CS53W32A },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW },
};

static const stwuct pvw2_device_desc pvw2_device_onaiw_usb2 = {
		.descwiption = "OnAiw USB2 Hybwid USB tunew",
		.showtname = "oa2",
		.cwient_tabwe.wst = pvw2_cwi_onaiw_usb2,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_onaiw_usb2),
		.defauwt_tunew_type = TUNEW_PHIWIPS_FCV1236D,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.fwag_digitaw_wequiwes_cx23416 = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_ONAIW,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_ONAIW,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_onaiw_usb2_fe_pwops,
#endif
};



/*------------------------------------------------------------------------*/
/* Hauppauge PVW-USB2 Modew 73xxx */

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
static stwuct tda10048_config hauppauge_tda10048_config = {
	.demod_addwess  = 0x10 >> 1,
	.output_mode    = TDA10048_PAWAWWEW_OUTPUT,
	.fwbuwkwwitewen = TDA10048_BUWKWWITE_50,
	.invewsion      = TDA10048_INVEWSION_ON,
	.dtv6_if_fweq_khz = TDA10048_IF_3300,
	.dtv7_if_fweq_khz = TDA10048_IF_3800,
	.dtv8_if_fweq_khz = TDA10048_IF_4300,
	.cwk_fweq_khz   = TDA10048_CWK_16000,
	.disabwe_gate_access = 1,
};

static stwuct tda829x_config tda829x_no_pwobe = {
	.pwobe_tunew = TDA829X_DONT_PWOBE,
};

static stwuct tda18271_std_map hauppauge_tda18271_dvbt_std_map = {
	.dvbt_6   = { .if_fweq = 3300, .agc_mode = 3, .std = 4,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_7   = { .if_fweq = 3800, .agc_mode = 3, .std = 5,
		      .if_wvw = 1, .wfagc_top = 0x37, },
	.dvbt_8   = { .if_fweq = 4300, .agc_mode = 3, .std = 6,
		      .if_wvw = 1, .wfagc_top = 0x37, },
};

static stwuct tda18271_config hauppauge_tda18271_dvb_config = {
	.std_map = &hauppauge_tda18271_dvbt_std_map,
	.gate    = TDA18271_GATE_ANAWOG,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static int pvw2_tda10048_attach(stwuct pvw2_dvb_adaptew *adap)
{
	adap->fe[0] = dvb_attach(tda10048_attach, &hauppauge_tda10048_config,
				 &adap->channew.hdw->i2c_adap);
	if (adap->fe[0])
		wetuwn 0;

	wetuwn -EIO;
}

static int pvw2_73xxx_tda18271_8295_attach(stwuct pvw2_dvb_adaptew *adap)
{
	dvb_attach(tda829x_attach, adap->fe[0],
		   &adap->channew.hdw->i2c_adap, 0x42,
		   &tda829x_no_pwobe);
	dvb_attach(tda18271_attach, adap->fe[0], 0x60,
		   &adap->channew.hdw->i2c_adap,
		   &hauppauge_tda18271_dvb_config);

	wetuwn 0;
}

static const stwuct pvw2_dvb_pwops pvw2_73xxx_dvb_pwops = {
	.fwontend_attach = pvw2_tda10048_attach,
	.tunew_attach    = pvw2_73xxx_tda18271_8295_attach,
};
#endif

static const stwuct pvw2_device_cwient_desc pvw2_cwi_73xxx[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_CX25840 },
	{ .moduwe_id = PVW2_CWIENT_ID_TUNEW,
	  .i2c_addwess_wist = "\x42"},
};

#define PVW2_FIWMWAWE_73xxx "v4w-pvwusb2-73xxx-01.fw"
static const chaw *pvw2_fw1_names_73xxx[] = {
		PVW2_FIWMWAWE_73xxx,
};

static const stwuct pvw2_device_desc pvw2_device_73xxx = {
		.descwiption = "WinTV HVW-1900 Modew 73xxx",
		.showtname = "73xxx",
		.cwient_tabwe.wst = pvw2_cwi_73xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_73xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_73xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_73xxx),
		.fwag_has_cx25840 = !0,
		.fwag_has_hauppauge_wom = !0,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.fwag_fx2_16kb = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_HAUPPAUGE,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_ZIWOG,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_73xxx_dvb_pwops,
#endif
};



/*------------------------------------------------------------------------*/
/* Hauppauge PVW-USB2 Modew 75xxx */

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
static stwuct s5h1409_config pvw2_s5h1409_config = {
	.demod_addwess = 0x32 >> 1,
	.output_mode   = S5H1409_PAWAWWEW_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_if        = 4000,
	.invewsion     = S5H1409_INVEWSION_ON,
	.status_mode   = S5H1409_DEMODWOCKING,
};

static stwuct s5h1411_config pvw2_s5h1411_config = {
	.output_mode   = S5H1411_PAWAWWEW_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_if        = S5H1411_IF_44000,
	.qam_if        = S5H1411_IF_4000,
	.invewsion     = S5H1411_INVEWSION_ON,
	.status_mode   = S5H1411_DEMODWOCKING,
};

static stwuct tda18271_std_map hauppauge_tda18271_std_map = {
	.atsc_6   = { .if_fweq = 5380, .agc_mode = 3, .std = 3,
		      .if_wvw = 6, .wfagc_top = 0x37, },
	.qam_6    = { .if_fweq = 4000, .agc_mode = 3, .std = 0,
		      .if_wvw = 6, .wfagc_top = 0x37, },
};

static stwuct tda18271_config hauppauge_tda18271_config = {
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_ANAWOG,
	.output_opt = TDA18271_OUTPUT_WT_OFF,
};

static int pvw2_s5h1409_attach(stwuct pvw2_dvb_adaptew *adap)
{
	adap->fe[0] = dvb_attach(s5h1409_attach, &pvw2_s5h1409_config,
				 &adap->channew.hdw->i2c_adap);
	if (adap->fe[0])
		wetuwn 0;

	wetuwn -EIO;
}

static int pvw2_s5h1411_attach(stwuct pvw2_dvb_adaptew *adap)
{
	adap->fe[0] = dvb_attach(s5h1411_attach, &pvw2_s5h1411_config,
				 &adap->channew.hdw->i2c_adap);
	if (adap->fe[0])
		wetuwn 0;

	wetuwn -EIO;
}

static int pvw2_tda18271_8295_attach(stwuct pvw2_dvb_adaptew *adap)
{
	dvb_attach(tda829x_attach, adap->fe[0],
		   &adap->channew.hdw->i2c_adap, 0x42,
		   &tda829x_no_pwobe);
	dvb_attach(tda18271_attach, adap->fe[0], 0x60,
		   &adap->channew.hdw->i2c_adap,
		   &hauppauge_tda18271_config);

	wetuwn 0;
}

static const stwuct pvw2_dvb_pwops pvw2_750xx_dvb_pwops = {
	.fwontend_attach = pvw2_s5h1409_attach,
	.tunew_attach    = pvw2_tda18271_8295_attach,
};

static const stwuct pvw2_dvb_pwops pvw2_751xx_dvb_pwops = {
	.fwontend_attach = pvw2_s5h1411_attach,
	.tunew_attach    = pvw2_tda18271_8295_attach,
};
#endif

#define PVW2_FIWMWAWE_75xxx "v4w-pvwusb2-73xxx-01.fw"
static const chaw *pvw2_fw1_names_75xxx[] = {
		PVW2_FIWMWAWE_75xxx,
};

static const stwuct pvw2_device_desc pvw2_device_750xx = {
		.descwiption = "WinTV HVW-1950 Modew 750xx",
		.showtname = "750xx",
		.cwient_tabwe.wst = pvw2_cwi_73xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_73xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_75xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_75xxx),
		.fwag_has_cx25840 = !0,
		.fwag_has_hauppauge_wom = !0,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.fwag_fx2_16kb = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_HAUPPAUGE,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_ZIWOG,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_750xx_dvb_pwops,
#endif
};

static const stwuct pvw2_device_desc pvw2_device_751xx = {
		.descwiption = "WinTV HVW-1950 Modew 751xx",
		.showtname = "751xx",
		.cwient_tabwe.wst = pvw2_cwi_73xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_73xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_75xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_75xxx),
		.fwag_has_cx25840 = !0,
		.fwag_has_hauppauge_wom = !0,
		.fwag_has_anawogtunew = !0,
		.fwag_has_composite = !0,
		.fwag_has_svideo = !0,
		.fwag_fx2_16kb = !0,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_HAUPPAUGE,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_ZIWOG,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_751xx_dvb_pwops,
#endif
};

/*------------------------------------------------------------------------*/
/*    Hauppauge PVW-USB2 Modew 160000 / 160111 -- HVW-1955 / HVW-1975     */

#ifdef CONFIG_VIDEO_PVWUSB2_DVB
static int pvw2_si2157_attach(stwuct pvw2_dvb_adaptew *adap);
static int pvw2_si2168_attach(stwuct pvw2_dvb_adaptew *adap);
static int pvw2_duaw_fe_attach(stwuct pvw2_dvb_adaptew *adap);
static int pvw2_wgdt3306a_attach(stwuct pvw2_dvb_adaptew *adap);

static const stwuct pvw2_dvb_pwops pvw2_160000_dvb_pwops = {
	.fwontend_attach = pvw2_duaw_fe_attach,
	.tunew_attach    = pvw2_si2157_attach,
};

static const stwuct pvw2_dvb_pwops pvw2_160111_dvb_pwops = {
	.fwontend_attach = pvw2_wgdt3306a_attach,
	.tunew_attach    = pvw2_si2157_attach,
};

static int pvw2_si2157_attach(stwuct pvw2_dvb_adaptew *adap)
{
	stwuct si2157_config si2157_config = {};

	si2157_config.invewsion = 1;
	si2157_config.fe = adap->fe[0];

	adap->i2c_cwient_tunew = dvb_moduwe_pwobe("si2157", "si2177",
						  &adap->channew.hdw->i2c_adap,
						  0x60, &si2157_config);

	if (!adap->i2c_cwient_tunew)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int pvw2_si2168_attach(stwuct pvw2_dvb_adaptew *adap)
{
	stwuct si2168_config si2168_config = {};
	stwuct i2c_adaptew *adaptew;

	pw_debug("%s()\n", __func__);

	si2168_config.fe = &adap->fe[1];
	si2168_config.i2c_adaptew = &adaptew;
	si2168_config.ts_mode = SI2168_TS_PAWAWWEW; /*2, 1-sewiaw, 2-pawawwew.*/
	si2168_config.ts_cwock_gapped = 1; /*0-disabwed, 1-enabwed.*/
	si2168_config.ts_cwock_inv = 0; /*0-not-invewt, 1-invewt*/
	si2168_config.spectwaw_invewsion = 1; /*0-not-invewt, 1-invewt*/

	adap->i2c_cwient_demod[1] = dvb_moduwe_pwobe("si2168", NUWW,
						     &adap->channew.hdw->i2c_adap,
						     0x64, &si2168_config);

	if (!adap->i2c_cwient_demod[1])
		wetuwn -ENODEV;

	wetuwn 0;
}

static int pvw2_wgdt3306a_attach(stwuct pvw2_dvb_adaptew *adap)
{
	stwuct wgdt3306a_config wgdt3306a_config;
	stwuct i2c_adaptew *adaptew;

	pw_debug("%s()\n", __func__);

	wgdt3306a_config.fe = &adap->fe[0];
	wgdt3306a_config.i2c_adaptew = &adaptew;
	wgdt3306a_config.deny_i2c_wptw = 1;
	wgdt3306a_config.spectwaw_invewsion = 1;
	wgdt3306a_config.qam_if_khz = 4000;
	wgdt3306a_config.vsb_if_khz = 3250;
	wgdt3306a_config.mpeg_mode = WGDT3306A_MPEG_PAWAWWEW;
	wgdt3306a_config.tpcwk_edge = WGDT3306A_TPCWK_FAWWING_EDGE;
	wgdt3306a_config.tpvawid_powawity = WGDT3306A_TP_VAWID_WOW;
	wgdt3306a_config.xtawMHz = 25; /* demod cwock MHz; 24/25 suppowted */

	adap->i2c_cwient_demod[0] = dvb_moduwe_pwobe("wgdt3306a", NUWW,
						     &adap->channew.hdw->i2c_adap,
						     0x59, &wgdt3306a_config);

	if (!adap->i2c_cwient_demod[0])
		wetuwn -ENODEV;

	wetuwn 0;
}

static int pvw2_duaw_fe_attach(stwuct pvw2_dvb_adaptew *adap)
{
	pw_debug("%s()\n", __func__);

	if (pvw2_wgdt3306a_attach(adap) != 0)
		wetuwn -ENODEV;

	if (pvw2_si2168_attach(adap) != 0) {
		dvb_moduwe_wewease(adap->i2c_cwient_demod[0]);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
#endif

#define PVW2_FIWMWAWE_160xxx "v4w-pvwusb2-160xxx-01.fw"
static const chaw *pvw2_fw1_names_160xxx[] = {
		PVW2_FIWMWAWE_160xxx,
};

static const stwuct pvw2_device_cwient_desc pvw2_cwi_160xxx[] = {
	{ .moduwe_id = PVW2_CWIENT_ID_CX25840 },
};

static const stwuct pvw2_device_desc pvw2_device_160000 = {
		.descwiption = "WinTV HVW-1975 Modew 160000",
		.showtname = "160000",
		.cwient_tabwe.wst = pvw2_cwi_160xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_160xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_160xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_160xxx),
		.defauwt_tunew_type = TUNEW_ABSENT,
		.fwag_has_cx25840 = 1,
		.fwag_has_hauppauge_wom = 1,
		.fwag_has_anawogtunew = 1,
		.fwag_has_composite = 1,
		.fwag_has_svideo = 1,
		.fwag_fx2_16kb = 1,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_HAUPPAUGE,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_ZIWOG,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_160000_dvb_pwops,
#endif
};

static const stwuct pvw2_device_desc pvw2_device_160111 = {
		.descwiption = "WinTV HVW-1955 Modew 160111",
		.showtname = "160111",
		.cwient_tabwe.wst = pvw2_cwi_160xxx,
		.cwient_tabwe.cnt = AWWAY_SIZE(pvw2_cwi_160xxx),
		.fx2_fiwmwawe.wst = pvw2_fw1_names_160xxx,
		.fx2_fiwmwawe.cnt = AWWAY_SIZE(pvw2_fw1_names_160xxx),
		.defauwt_tunew_type = TUNEW_ABSENT,
		.fwag_has_cx25840 = 1,
		.fwag_has_hauppauge_wom = 1,
		.fwag_has_anawogtunew = 1,
		.fwag_has_composite = 1,
		.fwag_has_svideo = 1,
		.fwag_fx2_16kb = 1,
		.signaw_wouting_scheme = PVW2_WOUTING_SCHEME_HAUPPAUGE,
		.digitaw_contwow_scheme = PVW2_DIGITAW_SCHEME_HAUPPAUGE,
		.defauwt_std_mask = V4W2_STD_NTSC_M,
		.wed_scheme = PVW2_WED_SCHEME_HAUPPAUGE,
		.iw_scheme = PVW2_IW_SCHEME_ZIWOG,
#ifdef CONFIG_VIDEO_PVWUSB2_DVB
		.dvb_pwops = &pvw2_160111_dvb_pwops,
#endif
};

/*------------------------------------------------------------------------*/

stwuct usb_device_id pvw2_device_tabwe[] = {
	{ USB_DEVICE(0x2040, 0x2900),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_29xxx},
	{ USB_DEVICE(0x2040, 0x2950), /* Wogicawwy identicaw to 2900 */
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_29xxx},
	{ USB_DEVICE(0x2040, 0x2400),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_24xxx},
	{ USB_DEVICE(0x1164, 0x0622),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_gotview_2},
	{ USB_DEVICE(0x1164, 0x0602),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_gotview_2d},
	{ USB_DEVICE(0x11ba, 0x1003),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_onaiw_cweatow},
	{ USB_DEVICE(0x11ba, 0x1001),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_onaiw_usb2},
	{ USB_DEVICE(0x2040, 0x7300),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_73xxx},
	{ USB_DEVICE(0x2040, 0x7500),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_750xx},
	{ USB_DEVICE(0x2040, 0x7501),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_751xx},
	{ USB_DEVICE(0x0ccd, 0x0039),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_av400},
	{ USB_DEVICE(0x2040, 0x7502),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_160111},
	{ USB_DEVICE(0x2040, 0x7510),
	  .dwivew_info = (kewnew_uwong_t)&pvw2_device_160000},
	{ }
};

MODUWE_DEVICE_TABWE(usb, pvw2_device_tabwe);
MODUWE_FIWMWAWE(PVW2_FIWMWAWE_29xxx);
MODUWE_FIWMWAWE(PVW2_FIWMWAWE_24xxx);
MODUWE_FIWMWAWE(PVW2_FIWMWAWE_73xxx);
MODUWE_FIWMWAWE(PVW2_FIWMWAWE_75xxx);
