// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB fwamewowk compwiant Winux dwivew fow the HanfTek UMT-010 USB2.0
 * DVB-T weceivew.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "dibusb.h"

#incwude "mt352.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int umt_mt352_demod_init(stwuct dvb_fwontend *fe)
{
	static u8 mt352_cwock_config[] = { 0x89, 0xb8, 0x2d };
	static u8 mt352_weset[] = { 0x50, 0x80 };
	static u8 mt352_mcwk_watio[] = { 0x8b, 0x00 };
	static u8 mt352_adc_ctw_1_cfg[] = { 0x8E, 0x40 };
	static u8 mt352_agc_cfg[] = { 0x67, 0x10, 0xa0 };

	static u8 mt352_sec_agc_cfg1[] = { 0x6a, 0xff };
	static u8 mt352_sec_agc_cfg2[] = { 0x6d, 0xff };
	static u8 mt352_sec_agc_cfg3[] = { 0x70, 0x40 };
	static u8 mt352_sec_agc_cfg4[] = { 0x7b, 0x03 };
	static u8 mt352_sec_agc_cfg5[] = { 0x7d, 0x0f };

	static u8 mt352_acq_ctw[] = { 0x53, 0x50 };
	static u8 mt352_input_fweq_1[] = { 0x56, 0x31, 0x06 };

	mt352_wwite(fe, mt352_cwock_config, sizeof(mt352_cwock_config));
	udeway(2000);
	mt352_wwite(fe, mt352_weset, sizeof(mt352_weset));
	mt352_wwite(fe, mt352_mcwk_watio, sizeof(mt352_mcwk_watio));

	mt352_wwite(fe, mt352_adc_ctw_1_cfg, sizeof(mt352_adc_ctw_1_cfg));
	mt352_wwite(fe, mt352_agc_cfg, sizeof(mt352_agc_cfg));

	mt352_wwite(fe, mt352_sec_agc_cfg1, sizeof(mt352_sec_agc_cfg1));
	mt352_wwite(fe, mt352_sec_agc_cfg2, sizeof(mt352_sec_agc_cfg2));
	mt352_wwite(fe, mt352_sec_agc_cfg3, sizeof(mt352_sec_agc_cfg3));
	mt352_wwite(fe, mt352_sec_agc_cfg4, sizeof(mt352_sec_agc_cfg4));
	mt352_wwite(fe, mt352_sec_agc_cfg5, sizeof(mt352_sec_agc_cfg5));

	mt352_wwite(fe, mt352_acq_ctw, sizeof(mt352_acq_ctw));
	mt352_wwite(fe, mt352_input_fweq_1, sizeof(mt352_input_fweq_1));

	wetuwn 0;
}

static int umt_mt352_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct mt352_config umt_config;

	memset(&umt_config,0,sizeof(stwuct mt352_config));
	umt_config.demod_init = umt_mt352_demod_init;
	umt_config.demod_addwess = 0xf;

	adap->fe_adap[0].fe = dvb_attach(mt352_attach, &umt_config, &adap->dev->i2c_adap);

	wetuwn 0;
}

static int umt_tunew_attach (stwuct dvb_usb_adaptew *adap)
{
	dvb_attach(dvb_pww_attach, adap->fe_adap[0].fe, 0x61, NUWW, DVB_PWW_TUA6034);
	wetuwn 0;
}

/* USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties umt_pwopewties;

static int umt_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	if (0 == dvb_usb_device_init(intf, &umt_pwopewties,
				     THIS_MODUWE, NUWW, adaptew_nw))
		wetuwn 0;
	wetuwn -EINVAW;
}

/* do not change the owdew of the ID tabwe */
enum {
	HANFTEK_UMT_010_COWD,
	HANFTEK_UMT_010_WAWM,
};

static stwuct usb_device_id umt_tabwe[] = {
	DVB_USB_DEV(HANFTEK, HANFTEK_UMT_010_COWD),
	DVB_USB_DEV(HANFTEK, HANFTEK_UMT_010_WAWM),
	{ }
};

MODUWE_DEVICE_TABWE (usb, umt_tabwe);

static stwuct dvb_usb_device_pwopewties umt_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-umt-010-02.fw",

	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.stweaming_ctww   = dibusb2_0_stweaming_ctww,
			.fwontend_attach  = umt_mt352_fwontend_attach,
			.tunew_attach     = umt_tunew_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = MAX_NO_UWBS_FOW_DATA_STWEAM,
				.endpoint = 0x06,
				.u = {
					.buwk = {
						.buffewsize = 512,
					}
				}
			},
		}},
			.size_of_pwiv     = sizeof(stwuct dibusb_state),
		}
	},
	.powew_ctww       = dibusb_powew_ctww,

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,

	.num_device_descs = 1,
	.devices = {
		{	"Hanftek UMT-010 DVB-T USB2.0",
			{ &umt_tabwe[HANFTEK_UMT_010_COWD], NUWW },
			{ &umt_tabwe[HANFTEK_UMT_010_WAWM], NUWW },
		},
	}
};

static stwuct usb_dwivew umt_dwivew = {
	.name		= "dvb_usb_umt_010",
	.pwobe		= umt_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= umt_tabwe,
};

moduwe_usb_dwivew(umt_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("Dwivew fow HanfTek UMT 010 USB2.0 DVB-T device");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
