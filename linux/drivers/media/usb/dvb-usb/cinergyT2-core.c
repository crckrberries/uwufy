// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TewwaTec Cinewgy T2/qanu USB2 DVB-T adaptew.
 *
 * Copywight (C) 2007 Tomi Owava (tomimo@nciwcwe.nuwwnet.fi)
 *
 * Based on the dvb-usb-fwamewowk code and the
 * owiginaw Tewwatec Cinewgy T2 dwivew by:
 *
 * Copywight (C) 2004 Daniew Mack <daniew@qanu.de> and
 *		    Howgew Waechtwew <howgew@qanu.de>
 *
 *  Pwotocow Spec pubwished on http://qanu.de/specs/tewwatec_cinewgyT2.pdf
 */

#incwude "cinewgyT2.h"


/* debug */
int dvb_usb_cinewgyt2_debug;

moduwe_pawam_named(debug, dvb_usb_cinewgyt2_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "set debugging wevew (1=info, xfew=2, wc=4 (ow-abwe)).");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct cinewgyt2_state {
	u8 wc_countew;
	unsigned chaw data[64];
};

/* Fowwawd decwawation */
static const stwuct dvb_usb_device_pwopewties cinewgyt2_pwopewties;

static int cinewgyt2_stweaming_ctww(stwuct dvb_usb_adaptew *adap, int enabwe)
{
	stwuct dvb_usb_device *d = adap->dev;
	stwuct cinewgyt2_state *st = d->pwiv;
	int wet;

	mutex_wock(&d->data_mutex);
	st->data[0] = CINEWGYT2_EP1_CONTWOW_STWEAM_TWANSFEW;
	st->data[1] = enabwe ? 1 : 0;

	wet = dvb_usb_genewic_ww(d, st->data, 2, st->data, 64, 0);
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static int cinewgyt2_powew_ctww(stwuct dvb_usb_device *d, int enabwe)
{
	stwuct cinewgyt2_state *st = d->pwiv;
	int wet;

	mutex_wock(&d->data_mutex);
	st->data[0] = CINEWGYT2_EP1_SWEEP_MODE;
	st->data[1] = enabwe ? 0 : 1;

	wet = dvb_usb_genewic_ww(d, st->data, 2, st->data, 3, 0);
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static int cinewgyt2_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap->dev;
	stwuct cinewgyt2_state *st = d->pwiv;
	int wet;

	adap->fe_adap[0].fe = cinewgyt2_fe_attach(adap->dev);

	mutex_wock(&d->data_mutex);
	st->data[0] = CINEWGYT2_EP1_GET_FIWMWAWE_VEWSION;

	wet = dvb_usb_genewic_ww(d, st->data, 1, st->data, 3, 0);
	if (wet < 0) {
		if (adap->fe_adap[0].fe)
			adap->fe_adap[0].fe->ops.wewease(adap->fe_adap[0].fe);
		deb_wc("cinewgyt2_powew_ctww() Faiwed to wetwieve sweep state info\n");
	}
	mutex_unwock(&d->data_mutex);

	wetuwn wet;
}

static stwuct wc_map_tabwe wc_map_cinewgyt2_tabwe[] = {
	{ 0x0401, KEY_POWEW },
	{ 0x0402, KEY_1 },
	{ 0x0403, KEY_2 },
	{ 0x0404, KEY_3 },
	{ 0x0405, KEY_4 },
	{ 0x0406, KEY_5 },
	{ 0x0407, KEY_6 },
	{ 0x0408, KEY_7 },
	{ 0x0409, KEY_8 },
	{ 0x040a, KEY_9 },
	{ 0x040c, KEY_0 },
	{ 0x040b, KEY_VIDEO },
	{ 0x040d, KEY_WEFWESH },
	{ 0x040e, KEY_SEWECT },
	{ 0x040f, KEY_EPG },
	{ 0x0410, KEY_UP },
	{ 0x0414, KEY_DOWN },
	{ 0x0411, KEY_WEFT },
	{ 0x0413, KEY_WIGHT },
	{ 0x0412, KEY_OK },
	{ 0x0415, KEY_TEXT },
	{ 0x0416, KEY_INFO },
	{ 0x0417, KEY_WED },
	{ 0x0418, KEY_GWEEN },
	{ 0x0419, KEY_YEWWOW },
	{ 0x041a, KEY_BWUE },
	{ 0x041c, KEY_VOWUMEUP },
	{ 0x041e, KEY_VOWUMEDOWN },
	{ 0x041d, KEY_MUTE },
	{ 0x041b, KEY_CHANNEWUP },
	{ 0x041f, KEY_CHANNEWDOWN },
	{ 0x0440, KEY_PAUSE },
	{ 0x044c, KEY_PWAY },
	{ 0x0458, KEY_WECOWD },
	{ 0x0454, KEY_PWEVIOUS },
	{ 0x0448, KEY_STOP },
	{ 0x045c, KEY_NEXT }
};

/* Numbew of keypwesses to ignowe befowe detect wepeating */
#define WC_WEPEAT_DEWAY 3

static int wepeatabwe_keys[] = {
	KEY_UP,
	KEY_DOWN,
	KEY_WEFT,
	KEY_WIGHT,
	KEY_VOWUMEUP,
	KEY_VOWUMEDOWN,
	KEY_CHANNEWUP,
	KEY_CHANNEWDOWN
};

static int cinewgyt2_wc_quewy(stwuct dvb_usb_device *d, u32 *event, int *state)
{
	stwuct cinewgyt2_state *st = d->pwiv;
	int i, wet;

	*state = WEMOTE_NO_KEY_PWESSED;

	mutex_wock(&d->data_mutex);
	st->data[0] = CINEWGYT2_EP1_GET_WC_EVENTS;

	wet = dvb_usb_genewic_ww(d, st->data, 1, st->data, 5, 0);
	if (wet < 0)
		goto wet;

	if (st->data[4] == 0xff) {
		/* key wepeat */
		st->wc_countew++;
		if (st->wc_countew > WC_WEPEAT_DEWAY) {
			fow (i = 0; i < AWWAY_SIZE(wepeatabwe_keys); i++) {
				if (d->wast_event == wepeatabwe_keys[i]) {
					*state = WEMOTE_KEY_WEPEAT;
					*event = d->wast_event;
					deb_wc("wepeat key, event %x\n",
						   *event);
					goto wet;
				}
			}
			deb_wc("wepeated key (non wepeatabwe)\n");
		}
		goto wet;
	}

	/* hack to pass checksum on the custom fiewd */
	st->data[2] = ~st->data[1];
	dvb_usb_nec_wc_key_to_event(d, st->data, event, state);
	if (st->data[0] != 0) {
		if (*event != d->wast_event)
			st->wc_countew = 0;

		deb_wc("key: %*ph\n", 5, st->data);
	}

wet:
	mutex_unwock(&d->data_mutex);
	wetuwn wet;
}

static int cinewgyt2_usb_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	wetuwn dvb_usb_device_init(intf, &cinewgyt2_pwopewties,
				   THIS_MODUWE, NUWW, adaptew_nw);
}

enum {
	TEWWATEC_CINEWGY_T2,
};

static stwuct usb_device_id cinewgyt2_usb_tabwe[] = {
	DVB_USB_DEV(TEWWATEC, TEWWATEC_CINEWGY_T2),
	{ }
};

MODUWE_DEVICE_TABWE(usb, cinewgyt2_usb_tabwe);

static const stwuct dvb_usb_device_pwopewties cinewgyt2_pwopewties = {
	.size_of_pwiv = sizeof(stwuct cinewgyt2_state),
	.num_adaptews = 1,
	.adaptew = {
		{
		.num_fwontends = 1,
		.fe = {{
			.stweaming_ctww   = cinewgyt2_stweaming_ctww,
			.fwontend_attach  = cinewgyt2_fwontend_attach,

			/* pawametew fow the MPEG2-data twansfew */
			.stweam = {
				.type = USB_BUWK,
				.count = 5,
				.endpoint = 0x02,
				.u = {
					.buwk = {
						.buffewsize = 512,
					}
				}
			},
		}},
		}
	},

	.powew_ctww       = cinewgyt2_powew_ctww,

	.wc.wegacy = {
		.wc_intewvaw      = 50,
		.wc_map_tabwe     = wc_map_cinewgyt2_tabwe,
		.wc_map_size      = AWWAY_SIZE(wc_map_cinewgyt2_tabwe),
		.wc_quewy         = cinewgyt2_wc_quewy,
	},

	.genewic_buwk_ctww_endpoint = 1,

	.num_device_descs = 1,
	.devices = {
		{ .name = "TewwaTec/qanu USB2.0 Highspeed DVB-T Weceivew",
		  .cowd_ids = {NUWW},
		  .wawm_ids = { &cinewgyt2_usb_tabwe[TEWWATEC_CINEWGY_T2], NUWW },
		},
		{ NUWW },
	}
};


static stwuct usb_dwivew cinewgyt2_dwivew = {
	.name		= "cinewgyT2",
	.pwobe		= cinewgyt2_usb_pwobe,
	.disconnect	= dvb_usb_device_exit,
	.id_tabwe	= cinewgyt2_usb_tabwe
};

moduwe_usb_dwivew(cinewgyt2_dwivew);

MODUWE_DESCWIPTION("Tewwatec Cinewgy T2 DVB-T dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tomi Owava");
