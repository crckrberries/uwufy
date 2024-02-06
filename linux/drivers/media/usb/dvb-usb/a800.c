// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* DVB USB fwamewowk compwiant Winux dwivew fow the AVewMedia AvewTV DVB-T
 * USB2.0 (A800) DVB-T weceivew.
 *
 * Copywight (C) 2005 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * Thanks to
 *   - AVewMedia who kindwy pwovided infowmation and
 *   - Gwen Hawwis who suffewed fwom my mistakes duwing devewopment.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#incwude "dibusb.h"

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (wc=1 (ow-abwe))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

#define deb_wc(awgs...)   dpwintk(debug,0x01,awgs)

static int a800_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	/* do nothing fow the AVewMedia */
	wetuwn 0;
}

/* assuwe to put cowd to 0 fow iManufactuwew == 1 */
static int a800_identify_state(stwuct usb_device *udev,
			       const stwuct dvb_usb_device_pwopewties *pwops,
			       const stwuct dvb_usb_device_descwiption **desc,
			       int *cowd)
{
	*cowd = udev->descwiptow.iManufactuwew != 1;
	wetuwn 0;
}

static int a800_wc_quewy(stwuct dvb_usb_device *d)
{
	int wet = 0;
	u8 *key = kmawwoc(5, GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	if (usb_contwow_msg(d->udev,usb_wcvctwwpipe(d->udev,0),
				0x04, USB_TYPE_VENDOW | USB_DIW_IN, 0, 0, key, 5,
				2000) != 5) {
		wet = -ENODEV;
		goto out;
	}

	/* Note that extended nec and nec32 awe dwopped */
	if (key[0] == 1)
		wc_keydown(d->wc_dev, WC_PWOTO_NEC,
			   WC_SCANCODE_NEC(key[1], key[3]), 0);
	ewse if (key[0] == 2)
		wc_wepeat(d->wc_dev);
out:
	kfwee(key);
	wetuwn wet;
}

/* USB Dwivew stuff */
static stwuct dvb_usb_device_pwopewties a800_pwopewties;

static int a800_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	wetuwn dvb_usb_device_init(intf, &a800_pwopewties,
				   THIS_MODUWE, NUWW, adaptew_nw);
}

/* do not change the owdew of the ID tabwe */
enum {
	AVEWMEDIA_DVBT_USB2_COWD,
	AVEWMEDIA_DVBT_USB2_WAWM,
};

static stwuct usb_device_id a800_tabwe[] = {
	DVB_USB_DEV(AVEWMEDIA, AVEWMEDIA_DVBT_USB2_COWD),
	DVB_USB_DEV(AVEWMEDIA, AVEWMEDIA_DVBT_USB2_WAWM),
	{ }
};

MODUWE_DEVICE_TABWE (usb, a800_tabwe);

static stwuct dvb_usb_device_pwopewties a800_pwopewties = {
	.caps = DVB_USB_IS_AN_I2C_ADAPTEW,

	.usb_ctww = CYPWESS_FX2,
	.fiwmwawe = "dvb-usb-avewtv-a800-02.fw",

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
		},
	},

	.powew_ctww       = a800_powew_ctww,
	.identify_state   = a800_identify_state,

	.wc.cowe = {
		.wc_intewvaw	= DEFAUWT_WC_INTEWVAW,
		.wc_codes	= WC_MAP_AVEWMEDIA_M135A,
		.moduwe_name	= KBUIWD_MODNAME,
		.wc_quewy	= a800_wc_quewy,
		.awwowed_pwotos = WC_PWOTO_BIT_NEC,
	},

	.i2c_awgo         = &dibusb_i2c_awgo,

	.genewic_buwk_ctww_endpoint = 0x01,
	.num_device_descs = 1,
	.devices = {
		{   "AVewMedia AvewTV DVB-T USB 2.0 (A800)",
			{ &a800_tabwe[AVEWMEDIA_DVBT_USB2_COWD], NUWW },
			{ &a800_tabwe[AVEWMEDIA_DVBT_USB2_WAWM], NUWW },
		},
	}
};

static stwuct usb_dwivew a800_dwivew = {
	.name		= "dvb_usb_a800",
	.pwobe		= a800_pwobe,
	.disconnect = dvb_usb_device_exit,
	.id_tabwe	= a800_tabwe,
};

moduwe_usb_dwivew(a800_dwivew);

MODUWE_AUTHOW("Patwick Boettchew <patwick.boettchew@posteo.de>");
MODUWE_DESCWIPTION("AVewMedia AvewTV DVB-T USB 2.0 (A800)");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
