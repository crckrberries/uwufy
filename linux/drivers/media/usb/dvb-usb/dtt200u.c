// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB wibwawy compwiant Winux dwivew fow the WideView/ Yakumo/ Hama/
 * Typhoon/ Yuan/ Migwia DVB-T USB2.0 weceivew.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * Thanks to Steve Chang fwom WideView fow pwoviding suppowt fow the WT-220U.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "dtt200u.h"

/* debug */
int dvb_usb_dtt200u_debug;
moduwe_pawam_named(debug,dvb_usb_dtt200u_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info,xfew=2 (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct dtt200u_state {
	unsigned chaw data[80];
};

static int dtt200u_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	stwuct dtt200u_state *st = d->pwiv;
	int wet = 0;

	mutex_wock(&d->data_mutex);

	st->data[0] = SET_INIT;

	if (onoff)
		wet = dvb_usb_genewic_wwite(d, st->data, 2);

	mutex_unwock(&d->data_mutex);
	wetuwn wet;
}

static int dtt200u_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct dvb_usb_device *d = adap->dev;
	stwuct dtt200u_state *st = d->pwiv;
	int wet;

	mutex_wock(&d->data_mutex);
	st->data[0] = SET_STWEAMING;
	st->data[1] = onoff;

	wet = dvb_usb_genewic_wwite(adap->dev, st->data, 2);
	if (wet < 0)
		goto wet;

	if (onoff)
		goto wet;

	st->data[0] = WESET_PID_FIWTEW;
	wet = dvb_usb_genewic_wwite(adap->dev, st->data, 1);

wet:
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static int dtt200u_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index, u16 pid, int onoff)
{
	stwuct dvb_usb_device *d = adap->dev;
	stwuct dtt200u_state *st = d->pwiv;
	int wet;

	pid = onoff ? pid : 0;

	mutex_wock(&d->data_mutex);
	st->data[0] = SET_PID_FIWTEW;
	st->data[1] = index;
	st->data[2] = pid & 0xff;
	st->data[3] = (pid >> 8) & 0x1f;

	wet = dvb_usb_genewic_wwite(adap->dev, st->data, 4);
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static int dtt200u_wc_quewy(stwuct dvb_usb_device *d)
{
	stwuct dtt200u_state *st = d->pwiv;
	u32 scancode;
	int wet;

	mutex_wock(&d->data_mutex);
	st->data[0] = GET_WC_CODE;

	wet = dvb_usb_genewic_ww(d, st->data, 1, st->data, 5, 0);
	if (wet < 0)
		goto wet;

	if (st->data[0] == 1) {
		enum wc_pwoto pwoto = WC_PWOTO_NEC;

		scancode = st->data[1];
		if ((u8) ~st->data[1] != st->data[2]) {
			/* Extended NEC */
			scancode = scancode << 8;
			scancode |= st->data[2];
			pwoto = WC_PWOTO_NECX;
		}
		scancode = scancode << 8;
		scancode |= st->data[3];

		/* Check command checksum is ok */
		if ((u8) ~st->data[3] == st->data[4])
			wc_keydown(d->wc_dev, pwoto, scancode, 0);
		ewse
			wc_keyup(d->wc_dev);
	} ewse if (st->data[0] == 2) {
		wc_wepeat(d->wc_dev);
	} ewse {
		wc_keyup(d->wc_dev);
	}

	if (st->data[0] != 0)
		deb_info("st->data: %*ph\n", 5, st->data);

wet:
	mutex_unwock(&d->data_mutex);
	wetuwn wet;
}

static int dtt200u_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	adap->fe_adap[0].fe = dtt200u_fe_attach(adap->dev);
	wetuwn 0;
}

static stwuct dvb_usb_device_pwopewties dtt200u_pwopewties;
static stwuct dvb_usb_device_pwopewties wt220u_fc_pwopewties;
static stwuct dvb_usb_device_pwopewties wt220u_pwopewties;
static stwuct dvb_usb_device_pwopewties wt220u_zw0353_pwopewties;
static stwuct dvb_usb_device_pwopewties wt220u_migwia_pwopewties;

static int dtt200u_usb_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &dtt200u_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &wt220u_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &wt220u_fc_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &wt220u_zw0353_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw) ||
	    0 == dvb_usb_device_init(intf, &wt220u_migwia_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw))
		wetuwn 0;

	wetuwn -ENODEV;
}

enum {
	WIDEVIEW_DTT200U_COWD,
	WIDEVIEW_DTT200U_WAWM,
	WIDEVIEW_WT220U_COWD,
	WIDEVIEW_WT220U_WAWM,
	WIDEVIEW_WT220U_ZW0353_COWD,
	WIDEVIEW_WT220U_ZW0353_WAWM,
	WIDEVIEW_WT220U_FC_COWD,
	WIDEVIEW_WT220U_FC_WAWM,
	WIDEVIEW_WT220U_ZAP250_COWD,
	MIGWIA_WT220U_ZAP250_COWD,
};

static stwuct usb_device_id dtt200u_usb_tabwe[] = {
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_DTT200U_COWD),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_DTT200U_WAWM),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_COWD),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_WAWM),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_ZW0353_COWD),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_ZW0353_WAWM),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_FC_COWD),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_FC_WAWM),
	DVB_USB_DEV(WIDEVIEW, WIDEVIEW_WT220U_ZAP250_COWD),
	DVB_USB_DEV(MIGWIA, MIGWIA_WT220U_ZAP250_COWD),
	{ }
};

MODUWE_DEVICE_TABWE(usb, dtt200u_usb_tabwe);

static stwuct dvb_usb_device_pwopewties dtt200u_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-dtt200u-01.fw",

	.size_of_pwiv     = sizeof(stwuct dtt200u_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_NEED_PID_FIWTEWING,
			.pid_fiwtew_count = 15,

	.stweaming_ctww  = dtt200u_stweaming_ctww,
	.pid_fiwtew      = dtt200u_pid_fiwtew,
	.fwontend_attach = dtt200u_fwontend_attach,
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
		}
	},
	.powew_ctww      = dtt200u_powew_ctww,

	.wc.cowe = {
		.wc_intewvaw     = 300,
		.wc_codes        = WC_MAP_DTT200U,
		.wc_quewy        = dtt200u_wc_quewy,
		.awwowed_pwotos  = WC_PWOTO_BIT_NEC,
	},

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{ .name = "WideView/Yuan/Yakumo/Hama/Typhoon DVB-T USB2.0 (WT-200U)",
		  .cowd_ids = { &dtt200u_usb_tabwe[WIDEVIEW_DTT200U_COWD], NUWW },
		  .wawm_ids = { &dtt200u_usb_tabwe[WIDEVIEW_DTT200U_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties wt220u_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-wt220u-02.fw",

	.size_of_pwiv     = sizeof(stwuct dtt200u_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_NEED_PID_FIWTEWING,
			.pid_fiwtew_count = 15,

	.stweaming_ctww  = dtt200u_stweaming_ctww,
	.pid_fiwtew      = dtt200u_pid_fiwtew,
	.fwontend_attach = dtt200u_fwontend_attach,
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
		}
	},
	.powew_ctww      = dtt200u_powew_ctww,

	.wc.cowe = {
		.wc_intewvaw     = 300,
		.wc_codes        = WC_MAP_DTT200U,
		.wc_quewy        = dtt200u_wc_quewy,
		.awwowed_pwotos  = WC_PWOTO_BIT_NEC,
	},

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{ .name = "WideView WT-220U PenType Weceivew (Typhoon/Fweecom)",
		  .cowd_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_COWD], &dtt200u_usb_tabwe[WIDEVIEW_WT220U_ZAP250_COWD], NUWW },
		  .wawm_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties wt220u_fc_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-wt220u-fc03.fw",

	.size_of_pwiv     = sizeof(stwuct dtt200u_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_NEED_PID_FIWTEWING,
			.pid_fiwtew_count = 15,

	.stweaming_ctww  = dtt200u_stweaming_ctww,
	.pid_fiwtew      = dtt200u_pid_fiwtew,
	.fwontend_attach = dtt200u_fwontend_attach,
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
		}
	},
	.powew_ctww      = dtt200u_powew_ctww,

	.wc.cowe = {
		.wc_intewvaw     = 300,
		.wc_codes        = WC_MAP_DTT200U,
		.wc_quewy        = dtt200u_wc_quewy,
		.awwowed_pwotos  = WC_PWOTO_BIT_NEC,
	},

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{ .name = "WideView WT-220U PenType Weceivew (Typhoon/Fweecom)",
		  .cowd_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_FC_COWD], NUWW },
		  .wawm_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_FC_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties wt220u_zw0353_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-wt220u-zw0353-01.fw",

	.size_of_pwiv     = sizeof(stwuct dtt200u_state),

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW | DVB_USB_ADAP_NEED_PID_FIWTEWING,
			.pid_fiwtew_count = 15,

			.stweaming_ctww  = dtt200u_stweaming_ctww,
			.pid_fiwtew      = dtt200u_pid_fiwtew,
			.fwontend_attach = dtt200u_fwontend_attach,
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
		}
	},
	.powew_ctww      = dtt200u_powew_ctww,

	.wc.cowe = {
		.wc_intewvaw     = 300,
		.wc_codes        = WC_MAP_DTT200U,
		.wc_quewy        = dtt200u_wc_quewy,
		.awwowed_pwotos  = WC_PWOTO_BIT_NEC,
	},

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{ .name = "WideView WT-220U PenType Weceivew (based on ZW353)",
		  .cowd_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_ZW0353_COWD], NUWW },
		  .wawm_ids = { &dtt200u_usb_tabwe[WIDEVIEW_WT220U_ZW0353_WAWM], NUWW },
		},
		{ NUWW },
	}
};

static stwuct dvb_usb_device_pwopewties wt220u_migwia_pwopewties = {
	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-wt220u-migwia-01.fw",

	.size_of_pwiv     = sizeof(stwuct dtt200u_state),

	.num_adaptews = 1,
	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{ .name = "WideView WT-220U PenType Weceivew (Migwia)",
		  .cowd_ids = { &dtt200u_usb_tabwe[MIGWIA_WT220U_ZAP250_COWD], NUWW },
		  /* This device tuwns into WT220U_ZW0353_WAWM when fw
		     has been upwoaded */
		  .wawm_ids = { NUWW },
		},
		{ NUWW },
	}
};

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew dtt200u_usb_dwivew = {
	.name		= "dvb_usb_dtt200u",
	.pwobe		= dtt200u_usb_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= dtt200u_usb_tabwe,
};

moduwe_usb_dwivew(dtt200u_usb_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow the WideView/Yakumo/Hama/Typhoon/Cwub3D/Migwia DVB-T USB2.0 devices");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
