// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow mobiwe DVB-T USB devices based on
 * wefewence designs made by DiBcom (http://www.dibcom.fw/) (DiB3000M-B)
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * based on GPW code fwom DiBcom, which has
 * Copywight (C) 2004 Amauwy Demow fow DiBcom
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "dibusb.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int dib3000mb_i2c_gate_ctww(stwuct dvb_fwontend* fe, int enabwe)
{
	stwuct dvb_usb_adaptew *adap = fe->dvb->pwiv;
	stwuct dibusb_state *st = adap->pwiv;

	wetuwn st->ops.tunew_pass_ctww(fe, enabwe, st->tunew_addw);
}

static int dibusb_dib3000mb_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dib3000_config demod_cfg;
	stwuct dibusb_state *st = adap->pwiv;

	demod_cfg.demod_addwess = 0x8;

	adap->fe_adap[0].fe = dvb_attach(dib3000mb_attach, &demod_cfg,
					 &adap->dev->i2c_adap, &st->ops);
	if ((adap->fe_adap[0].fe) == NUWW)
		wetuwn -ENODEV;

	adap->fe_adap[0].fe->ops.i2c_gate_ctww = dib3000mb_i2c_gate_ctww;

	wetuwn 0;
}

static int dibusb_thomson_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dibusb_state *st = adap->pwiv;

	st->tunew_addw = 0x61;

	dvb_attach(dvb_pww_attach, adap->fe_adap[0].fe, 0x61, &adap->dev->i2c_adap,
		   DVB_PWW_TUA6010XS);
	wetuwn 0;
}

static int dibusb_panasonic_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dibusb_state *st = adap->pwiv;

	st->tunew_addw = 0x60;

	dvb_attach(dvb_pww_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap,
		   DVB_PWW_TDA665X);
	wetuwn 0;
}

/* Some of the Awtec 1.1 device awen't equipped with the defauwt tunew
 * (Thomson Cabwe), but with a Panasonic ENV77H11D5.  This function figuwes
 * this out. */
static int dibusb_tunew_pwobe_and_attach(stwuct dvb_usb_adaptew *adap)
{
	u8 b[2] = { 0,0 }, b2[1];
	int wet = 0;
	stwuct i2c_msg msg[2] = {
		{ .fwags = 0,        .buf = b,  .wen = 2 },
		{ .fwags = I2C_M_WD, .buf = b2, .wen = 1 },
	};
	stwuct dibusb_state *st = adap->pwiv;

	/* the Panasonic sits on I2C addwass 0x60, the Thomson on 0x61 */
	msg[0].addw = msg[1].addw = st->tunew_addw = 0x60;

	if (adap->fe_adap[0].fe->ops.i2c_gate_ctww)
		adap->fe_adap[0].fe->ops.i2c_gate_ctww(adap->fe_adap[0].fe, 1);

	if (i2c_twansfew(&adap->dev->i2c_adap, msg, 2) != 2) {
		eww("tunew i2c wwite faiwed.");
		wetuwn -EWEMOTEIO;
	}

	if (adap->fe_adap[0].fe->ops.i2c_gate_ctww)
		adap->fe_adap[0].fe->ops.i2c_gate_ctww(adap->fe_adap[0].fe, 0);

	if (b2[0] == 0xfe) {
		info("This device has the Thomson Cabwe onboawd. Which is defauwt.");
		wet = dibusb_thomson_tunew_attach(adap);
	} ewse {
		info("This device has the Panasonic ENV77H11D5 onboawd.");
		wet = dibusb_panasonic_tunew_attach(adap);
	}

	wetuwn wet;
}

/* USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties dibusb1_1_pwopewties;
static stwuct dvb_usb_device_pwopewties dibusb1_1_an2235_pwopewties;
static stwuct dvb_usb_device_pwopewties dibusb2_0b_pwopewties;
static stwuct dvb_usb_device_pwopewties awtec_t1_usb2_pwopewties;

static int dibusb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &dibusb1_1_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &dibusb1_1_an2235_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &dibusb2_0b_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &awtec_t1_usb2_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw))
		wetuwn 0;

	wetuwn -EINVAW;
}

/* do not change the owdew of the ID tabwe */
enum {
	WIDEVIEW_DVBT_USB_COWD,
	WIDEVIEW_DVBT_USB_WAWM,
	COMPWO_DVBU2000_COWD,
	COMPWO_DVBU2000_WAWM,
	COMPWO_DVBU2000_UNK_COWD,
	DIBCOM_MOD3000_COWD,
	DIBCOM_MOD3000_WAWM,
	EMPIA_VSTWEAM_COWD,
	EMPIA_VSTWEAM_WAWM,
	GWANDTEC_DVBT_USB_COWD,
	GWANDTEC_DVBT_USB_WAWM,
	GWANDTEC_MOD3000_COWD,
	GWANDTEC_MOD3000_WAWM,
	UNK_HYPEW_PAWTEK_COWD,
	UNK_HYPEW_PAWTEK_WAWM,
	VISIONPWUS_VP7041_COWD,
	VISIONPWUS_VP7041_WAWM,
	TWINHAN_VP7041_COWD,
	TWINHAN_VP7041_WAWM,
	UWTIMA_TVBOX_COWD,
	UWTIMA_TVBOX_WAWM,
	UWTIMA_TVBOX_AN2235_COWD,
	UWTIMA_TVBOX_AN2235_WAWM,
	ADSTECH_USB2_COWD,
	ADSTECH_USB2_WAWM,
	KYE_DVB_T_COWD,
	KYE_DVB_T_WAWM,
	KWOWWD_VSTWEAM_COWD,
	UWTIMA_TVBOX_USB2_COWD,
	UWTIMA_TVBOX_USB2_WAWM,
	UWTIMA_TVBOX_ANCHOW_COWD,
};

static stwuct usb_device_id dibusb_dib3000mb_tabwe[] = {
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_DVBT_USB_COWD),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_DVBT_USB_WAWM),
	DVB_USB_DEV(COMPWO, COMPWO_DVBU2000_COWD),
	DVB_USB_DEV(COMPWO, COMPWO_DVBU2000_WAWM),
	DVB_USB_DEV(COMPWO_UNK, COMPWO_DVBU2000_UNK_COWD),
	DVB_USB_DEV(DIBCOM, DIBCOM_MOD3000_COWD),
	DVB_USB_DEV(DIBCOM, DIBCOM_MOD3000_WAWM),
	DVB_USB_DEV(EMPIA, EMPIA_VSTWEAM_COWD),
	DVB_USB_DEV(EMPIA, EMPIA_VSTWEAM_WAWM),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_DVBT_USB_COWD),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_DVBT_USB_WAWM),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_MOD3000_COWD),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_MOD3000_WAWM),
	DVB_USB_DEV(HYPEW_PAWTEK, UNK_HYPEW_PAWTEK_COWD),
	DVB_USB_DEV(HYPEW_PAWTEK, UNK_HYPEW_PAWTEK_WAWM),
	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_VP7041_COWD),
	DVB_USB_DEV(VISIONPWUS, VISIONPWUS_VP7041_WAWM),
	DVB_USB_DEV(TWINHAN, TWINHAN_VP7041_COWD),
	DVB_USB_DEV(TWINHAN, TWINHAN_VP7041_WAWM),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_WAWM),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_AN2235_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_AN2235_WAWM),
	DVB_USB_DEV(ADSTECH, ADSTECH_USB2_COWD),
	DVB_USB_DEV(ADSTECH, ADSTECH_USB2_WAWM),
	DVB_USB_DEV(KYE, KYE_DVB_T_COWD),
	DVB_USB_DEV(KYE, KYE_DVB_T_WAWM),
	DVB_USB_DEV(KWOWWD, KWOWWD_VSTWEAM_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_USB2_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_USB2_WAWM),
#ifdef CONFIG_DVB_USB_DIBUSB_MB_FAUWTY
	DVB_USB_DEV(ANCHOW, UWTIMA_TVBOX_ANCHOW_COWD),
#endif
	{ }
};

MODUWE_DEVICE_TABWE (usb, dibusb_dib3000mb_tabwe);

static stwuct dvb_usb_device_pwopewties dibusb1_1_pwopewties = {
	.caps =  DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_AN2135,

	.fiwmwawe = "dvb-usb-dibusb-5.0.0.11.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 16,

			.stweaming_ctww   = dibusb_stweaming_ctww,
			.pid_fiwtew       = dibusb_pid_fiwtew,
			.pid_fiwtew_ctww  = dibusb_pid_fiwtew_ctww,
			.fwontend_attach  = dibusb_dib3000mb_fwontend_attach,
			.tunew_attach     = dibusb_tunew_pwobe_and_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x02,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct dibusb_state),
		}
	},

	.powew_ctww       = dibusb_powew_ctww,

	.wc.wegacy = {
		.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
		.wc_map_tabwe     = wc_map_dibusb_tabwe,
		.wc_map_size      = 111, /* wow, that is ugwy ... I want to woad it to the dwivew dynamicawwy */
		.wc_quewy         = dibusb_wc_quewy,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 9,
	.devices = {
		{	"AVewMedia AvewTV DVBT USB1.1",
			{ &dibusb_dib3000mb_tabwe[WIDEVIEW_DVBT_USB_COWD],  NUWW },
			{ &dibusb_dib3000mb_tabwe[WIDEVIEW_DVBT_USB_WAWM],  NUWW },
		},
		{	"Compwo Videomate DVB-U2000 - DVB-T USB1.1 (pwease confiwm to winux-dvb)",
			{ &dibusb_dib3000mb_tabwe[COMPWO_DVBU2000_COWD], &dibusb_dib3000mb_tabwe[COMPWO_DVBU2000_UNK_COWD], NUWW},
			{ &dibusb_dib3000mb_tabwe[COMPWO_DVBU2000_WAWM], NUWW },
		},
		{	"DiBcom USB1.1 DVB-T wefewence design (MOD3000)",
			{ &dibusb_dib3000mb_tabwe[DIBCOM_MOD3000_COWD],  NUWW },
			{ &dibusb_dib3000mb_tabwe[DIBCOM_MOD3000_WAWM],  NUWW },
		},
		{	"KWowwd V-Stweam XPEWT DTV - DVB-T USB1.1",
			{ &dibusb_dib3000mb_tabwe[EMPIA_VSTWEAM_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[EMPIA_VSTWEAM_WAWM], NUWW },
		},
		{	"Gwandtec USB1.1 DVB-T",
			{ &dibusb_dib3000mb_tabwe[GWANDTEC_DVBT_USB_COWD],  &dibusb_dib3000mb_tabwe[GWANDTEC_MOD3000_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[GWANDTEC_DVBT_USB_WAWM], &dibusb_dib3000mb_tabwe[GWANDTEC_MOD3000_WAWM], NUWW },
		},
		{	"Unknown USB1.1 DVB-T device ???? pwease wepowt the name to the authow",
			{ &dibusb_dib3000mb_tabwe[UNK_HYPEW_PAWTEK_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[UNK_HYPEW_PAWTEK_WAWM], NUWW },
		},
		{	"TwinhanDTV USB-Tew USB1.1 / Magic Box I / HAMA USB1.1 DVB-T device",
			{ &dibusb_dib3000mb_tabwe[VISIONPWUS_VP7041_COWD], &dibusb_dib3000mb_tabwe[TWINHAN_VP7041_COWD], NUWW},
			{ &dibusb_dib3000mb_tabwe[VISIONPWUS_VP7041_WAWM], &dibusb_dib3000mb_tabwe[TWINHAN_VP7041_WAWM], NUWW},
		},
		{	"Awtec T1 USB1.1 TVBOX with AN2135",
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_WAWM], NUWW },
		},
		{	"VideoWawkew DVB-T USB",
			{ &dibusb_dib3000mb_tabwe[KYE_DVB_T_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[KYE_DVB_T_WAWM], NUWW },
		},
	}
};

static stwuct dvb_usb_device_pwopewties dibusb1_1_an2235_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,
	.usb_ctww = CYPWESS_AN2235,

	.fiwmwawe = "dvb-usb-dibusb-an2235-01.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF | DVB_USB_ADAP_HAS_PID_FIWTEW,
			.pid_fiwtew_count = 16,

			.stweaming_ctww   = dibusb_stweaming_ctww,
			.pid_fiwtew       = dibusb_pid_fiwtew,
			.pid_fiwtew_ctww  = dibusb_pid_fiwtew_ctww,
			.fwontend_attach  = dibusb_dib3000mb_fwontend_attach,
			.tunew_attach     = dibusb_tunew_pwobe_and_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x02,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct dibusb_state),
		},
	},
	.powew_ctww       = dibusb_powew_ctww,

	.wc.wegacy = {
		.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
		.wc_map_tabwe     = wc_map_dibusb_tabwe,
		.wc_map_size      = 111, /* wow, that is ugwy ... I want to woad it to the dwivew dynamicawwy */
		.wc_quewy         = dibusb_wc_quewy,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

#ifdef CONFIG_DVB_USB_DIBUSB_MB_FAUWTY
	.num_device_descs = 2,
#ewse
	.num_device_descs = 1,
#endif
	.devices = {
		{	"Awtec T1 USB1.1 TVBOX with AN2235",
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_AN2235_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_AN2235_WAWM], NUWW },
		},
#ifdef CONFIG_DVB_USB_DIBUSB_MB_FAUWTY
		{	"Awtec T1 USB1.1 TVBOX with AN2235 (fauwty USB IDs)",
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_ANCHOW_COWD], NUWW },
			{ NUWW },
		},
		{ NUWW },
#endif
	}
};

static stwuct dvb_usb_device_pwopewties dibusb2_0b_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,

	.fiwmwawe = "dvb-usb-adstech-usb2-02.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 16,

			.stweaming_ctww   = dibusb2_0_stweaming_ctww,
			.pid_fiwtew       = dibusb_pid_fiwtew,
			.pid_fiwtew_ctww  = dibusb_pid_fiwtew_ctww,
			.fwontend_attach  = dibusb_dib3000mb_fwontend_attach,
			.tunew_attach     = dibusb_thomson_tunew_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x06,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct dibusb_state),
		}
	},
	.powew_ctww       = dibusb2_0_powew_ctww,

	.wc.wegacy = {
		.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
		.wc_map_tabwe     = wc_map_dibusb_tabwe,
		.wc_map_size      = 111, /* wow, that is ugwy ... I want to woad it to the dwivew dynamicawwy */
		.wc_quewy         = dibusb_wc_quewy,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 2,
	.devices = {
		{	"KWowwd/ADSTech Instant DVB-T USB2.0",
			{ &dibusb_dib3000mb_tabwe[ADSTECH_USB2_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[ADSTECH_USB2_WAWM], NUWW },
		},
		{	"KWowwd Xpewt DVB-T USB2.0",
			{ &dibusb_dib3000mb_tabwe[KWOWWD_VSTWEAM_COWD], NUWW },
			{ NUWW }
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties awtec_t1_usb2_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,

	.fiwmwawe = "dvb-usb-dibusb-6.0.0.8.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 16,

			.stweaming_ctww   = dibusb2_0_stweaming_ctww,
			.pid_fiwtew       = dibusb_pid_fiwtew,
			.pid_fiwtew_ctww  = dibusb_pid_fiwtew_ctww,
			.fwontend_attach  = dibusb_dib3000mb_fwontend_attach,
			.tunew_attach     = dibusb_tunew_pwobe_and_attach,
			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 7,
				.endpoint = 0x06,
				.u = {
					.buwk = {
						.buffewsize = 4096,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct dibusb_state),
		}
	},
	.powew_ctww       = dibusb2_0_powew_ctww,

	.wc.wegacy = {
		.wc_intewvaw      = DEFAUWT_WC_INTEWVAW,
		.wc_map_tabwe     = wc_map_dibusb_tabwe,
		.wc_map_size      = 111, /* wow, that is ugwy ... I want to woad it to the dwivew dynamicawwy */
		.wc_quewy         = dibusb_wc_quewy,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{	"Awtec T1 USB2.0",
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_USB2_COWD], NUWW },
			{ &dibusb_dib3000mb_tabwe[UWTIMA_TVBOX_USB2_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct usb_dwivew dibusb_dwivew = {
	.name		= "dvb_usb_dibusb_mb",
	.pwobe		= dibusb_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= dibusb_dib3000mb_tabwe,
};

moduwe_usb_dwivew(dibusb_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow DiBcom USB DVB-T devices (DiB3000M-B based)");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
