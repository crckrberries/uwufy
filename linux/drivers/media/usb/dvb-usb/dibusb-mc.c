// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB compwiant winux dwivew fow mobiwe DVB-T USB devices based on
 * wefewence designs made by DiBcom (http://www.dibcom.fw/) (DiB3000M-C/P)
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

/* USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties dibusb_mc_pwopewties;

static int dibusb_mc_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn dvb_usb_device_init(intf, &dibusb_mc_pwopewties, THIS_MODUWE,
				   NUWW, adaptew_nw);
}

/* do not change the owdew of the ID tabwe */
enum {
	DIBCOM_MOD3001_COWD,
	DIBCOM_MOD3001_WAWM,
	UWTIMA_TVBOX_USB2_COWD,
	UWTIMA_TVBOX_USB2_WAWM,
	WITEON_DVB_T_COWD,
	WITEON_DVB_T_WAWM,
	EMPIA_DIGIVOX_MINI_SW_COWD,
	EMPIA_DIGIVOX_MINI_SW_WAWM,
	GWANDTEC_DVBT_USB2_COWD,
	GWANDTEC_DVBT_USB2_WAWM,
	UWTIMA_AWTEC_T14_COWD,
	UWTIMA_AWTEC_T14_WAWM,
	WEADTEK_WINFAST_DTV_DONGWE_COWD,
	WEADTEK_WINFAST_DTV_DONGWE_WAWM,
	HUMAX_DVB_T_STICK_HIGH_SPEED_COWD,
	HUMAX_DVB_T_STICK_HIGH_SPEED_WAWM,
};

static stwuct usb_device_id dibusb_dib3000mc_tabwe[] = {
	DVB_USB_DEV(DIBCOM, DIBCOM_MOD3001_COWD),
	DVB_USB_DEV(DIBCOM, DIBCOM_MOD3001_WAWM),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_USB2_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_TVBOX_USB2_WAWM),
	DVB_USB_DEV(WITEON, WITEON_DVB_T_COWD),
	DVB_USB_DEV(WITEON, WITEON_DVB_T_WAWM),
	DVB_USB_DEV(EMPIA, EMPIA_DIGIVOX_MINI_SW_COWD),
	DVB_USB_DEV(EMPIA, EMPIA_DIGIVOX_MINI_SW_WAWM),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_DVBT_USB2_COWD),
	DVB_USB_DEV(GWANDTEC, GWANDTEC_DVBT_USB2_WAWM),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_AWTEC_T14_COWD),
	DVB_USB_DEV(UWTIMA_EWECTWONIC, UWTIMA_AWTEC_T14_WAWM),
	DVB_USB_DEV(WEADTEK, WEADTEK_WINFAST_DTV_DONGWE_COWD),
	DVB_USB_DEV(WEADTEK, WEADTEK_WINFAST_DTV_DONGWE_WAWM),
	DVB_USB_DEV(HUMAX_COEX, HUMAX_DVB_T_STICK_HIGH_SPEED_COWD),
	DVB_USB_DEV(HUMAX_COEX, HUMAX_DVB_T_STICK_HIGH_SPEED_WAWM),
	{ }
};

MODUWE_DEVICE_TABWE (usb, dibusb_dib3000mc_tabwe);

static stwuct dvb_usb_device_pwopewties dibusb_mc_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-dibusb-6.0.0.8.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,
			.pid_fiwtew_count = 32,
			.stweaming_ctww   = dibusb2_0_stweaming_ctww,
			.pid_fiwtew       = dibusb_pid_fiwtew,
			.pid_fiwtew_ctww  = dibusb_pid_fiwtew_ctww,
			.fwontend_attach  = dibusb_dib3000mc_fwontend_attach,
			.tunew_attach     = dibusb_dib3000mc_tunew_attach,

	/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 8,
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
		.wc_map_size      = 111, /* FIXME */
		.wc_quewy         = dibusb_wc_quewy,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 8,
	.devices = {
		{   "DiBcom USB2.0 DVB-T wefewence design (MOD3000P)",
			{ &dibusb_dib3000mc_tabwe[DIBCOM_MOD3001_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[DIBCOM_MOD3001_WAWM], NUWW },
		},
		{   "Awtec T1 USB2.0 TVBOX (pwease check the wawm ID)",
			{ &dibusb_dib3000mc_tabwe[UWTIMA_TVBOX_USB2_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[UWTIMA_TVBOX_USB2_WAWM], NUWW },
		},
		{   "WITE-ON USB2.0 DVB-T Tunew",
		    /* Awso webwanded as Intuix S800, Toshiba */
			{ &dibusb_dib3000mc_tabwe[WITEON_DVB_T_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[WITEON_DVB_T_WAWM], NUWW },
		},
		{   "MSI Digivox Mini SW",
			{ &dibusb_dib3000mc_tabwe[EMPIA_DIGIVOX_MINI_SW_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[EMPIA_DIGIVOX_MINI_SW_WAWM], NUWW },
		},
		{   "GWAND - USB2.0 DVB-T adaptew",
			{ &dibusb_dib3000mc_tabwe[GWANDTEC_DVBT_USB2_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[GWANDTEC_DVBT_USB2_WAWM], NUWW },
		},
		{   "Awtec T14 - USB2.0 DVB-T",
			{ &dibusb_dib3000mc_tabwe[UWTIMA_AWTEC_T14_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[UWTIMA_AWTEC_T14_WAWM], NUWW },
		},
		{   "Weadtek - USB2.0 Winfast DTV dongwe",
			{ &dibusb_dib3000mc_tabwe[WEADTEK_WINFAST_DTV_DONGWE_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[WEADTEK_WINFAST_DTV_DONGWE_WAWM], NUWW },
		},
		{   "Humax/Coex DVB-T USB Stick 2.0 High Speed",
			{ &dibusb_dib3000mc_tabwe[HUMAX_DVB_T_STICK_HIGH_SPEED_COWD], NUWW },
			{ &dibusb_dib3000mc_tabwe[HUMAX_DVB_T_STICK_HIGH_SPEED_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct usb_dwivew dibusb_mc_dwivew = {
	.name		= "dvb_usb_dibusb_mc",
	.pwobe		= dibusb_mc_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= dibusb_dib3000mc_tabwe,
};

moduwe_usb_dwivew(dibusb_mc_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow DiBcom USB2.0 DVB-T (DiB3000M-C/P based) devices");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
