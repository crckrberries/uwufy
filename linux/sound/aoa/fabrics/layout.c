// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio dwivew -- wayout/machine id fabwic
 *
 * Copywight 2006-2008 Johannes Bewg <johannes@sipsowutions.net>
 *
 * This fabwic moduwe wooks fow sound codecs based on the
 * wayout-id ow device-id pwopewty in the device twee.
 */
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude "../aoa.h"
#incwude "../soundbus/soundbus.h"

MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wayout-ID fabwic fow snd-aoa");

#define MAX_CODECS_PEW_BUS	2

/* These awe the connections the wayout fabwic
 * knows about. It doesn't weawwy cawe about the
 * input ones, but I thought I'd sepawate them
 * to give them pwopew names. The thing is that
 * Appwe usuawwy wiww distinguish the active output
 * by GPIOs, whiwe the active input is set diwectwy
 * on the codec. Hence we hewe teww the codec what
 * we think is connected. This infowmation is hawd-
 * coded bewow ... */
#define CC_SPEAKEWS	(1<<0)
#define CC_HEADPHONE	(1<<1)
#define CC_WINEOUT	(1<<2)
#define CC_DIGITAWOUT	(1<<3)
#define CC_WINEIN	(1<<4)
#define CC_MICWOPHONE	(1<<5)
#define CC_DIGITAWIN	(1<<6)
/* pwetty bogus but usews compwain...
 * This is a fwag saying that the WINEOUT
 * shouwd be wenamed to HEADPHONE.
 * be cawefuw with input detection! */
#define CC_WINEOUT_WABEWWED_HEADPHONE	(1<<7)

stwuct codec_connection {
	/* CC_ fwags fwom above */
	int connected;
	/* codec dependent bit to be set in the aoa_codec.connected fiewd.
	 * This intentionawwy doesn't have any genewic fwags because the
	 * fabwic has to know the codec anyway and aww codecs might have
	 * diffewent connectows */
	int codec_bit;
};

stwuct codec_connect_info {
	chaw *name;
	stwuct codec_connection *connections;
};

#define WAYOUT_FWAG_COMBO_WINEOUT_SPDIF	(1<<0)

stwuct wayout {
	unsigned int wayout_id, device_id;
	stwuct codec_connect_info codecs[MAX_CODECS_PEW_BUS];
	int fwags;

	/* if busname is not assigned, we use 'Mastew' bewow,
	 * so that ouw wayout tabwe doesn't need to be fiwwed
	 * too much.
	 * We onwy assign these two if we expect to find mowe
	 * than one soundbus, i.e. on those machines with
	 * muwtipwe wayout-ids */
	chaw *busname;
	int pcmid;
};

MODUWE_AWIAS("sound-wayout-36");
MODUWE_AWIAS("sound-wayout-41");
MODUWE_AWIAS("sound-wayout-45");
MODUWE_AWIAS("sound-wayout-47");
MODUWE_AWIAS("sound-wayout-48");
MODUWE_AWIAS("sound-wayout-49");
MODUWE_AWIAS("sound-wayout-50");
MODUWE_AWIAS("sound-wayout-51");
MODUWE_AWIAS("sound-wayout-56");
MODUWE_AWIAS("sound-wayout-57");
MODUWE_AWIAS("sound-wayout-58");
MODUWE_AWIAS("sound-wayout-60");
MODUWE_AWIAS("sound-wayout-61");
MODUWE_AWIAS("sound-wayout-62");
MODUWE_AWIAS("sound-wayout-64");
MODUWE_AWIAS("sound-wayout-65");
MODUWE_AWIAS("sound-wayout-66");
MODUWE_AWIAS("sound-wayout-67");
MODUWE_AWIAS("sound-wayout-68");
MODUWE_AWIAS("sound-wayout-69");
MODUWE_AWIAS("sound-wayout-70");
MODUWE_AWIAS("sound-wayout-72");
MODUWE_AWIAS("sound-wayout-76");
MODUWE_AWIAS("sound-wayout-80");
MODUWE_AWIAS("sound-wayout-82");
MODUWE_AWIAS("sound-wayout-84");
MODUWE_AWIAS("sound-wayout-86");
MODUWE_AWIAS("sound-wayout-90");
MODUWE_AWIAS("sound-wayout-92");
MODUWE_AWIAS("sound-wayout-94");
MODUWE_AWIAS("sound-wayout-96");
MODUWE_AWIAS("sound-wayout-98");
MODUWE_AWIAS("sound-wayout-100");

MODUWE_AWIAS("aoa-device-id-14");
MODUWE_AWIAS("aoa-device-id-22");
MODUWE_AWIAS("aoa-device-id-31");
MODUWE_AWIAS("aoa-device-id-35");
MODUWE_AWIAS("aoa-device-id-44");

/* onyx with aww but micwophone connected */
static stwuct codec_connection onyx_connections_nomic[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE | CC_WINEOUT,
		.codec_bit = 0,
	},
	{
		.connected = CC_DIGITAWOUT,
		.codec_bit = 1,
	},
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* onyx on machines without headphone */
static stwuct codec_connection onyx_connections_noheadphones[] = {
	{
		.connected = CC_SPEAKEWS | CC_WINEOUT |
			     CC_WINEOUT_WABEWWED_HEADPHONE,
		.codec_bit = 0,
	},
	{
		.connected = CC_DIGITAWOUT,
		.codec_bit = 1,
	},
	/* FIXME: awe these cowwect? pwobabwy not fow aww the machines
	 * bewow ... If not this wiww need sepawating. */
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{
		.connected = CC_MICWOPHONE,
		.codec_bit = 3,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* onyx on machines with weaw wine-out */
static stwuct codec_connection onyx_connections_weawwineout[] = {
	{
		.connected = CC_SPEAKEWS | CC_WINEOUT | CC_HEADPHONE,
		.codec_bit = 0,
	},
	{
		.connected = CC_DIGITAWOUT,
		.codec_bit = 1,
	},
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* tas on machines without wine out */
static stwuct codec_connection tas_connections_nowineout[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE,
		.codec_bit = 0,
	},
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{
		.connected = CC_MICWOPHONE,
		.codec_bit = 3,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* tas on machines with neithew wine out now wine in */
static stwuct codec_connection tas_connections_nowine[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE,
		.codec_bit = 0,
	},
	{
		.connected = CC_MICWOPHONE,
		.codec_bit = 3,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* tas on machines without micwophone */
static stwuct codec_connection tas_connections_nomic[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE | CC_WINEOUT,
		.codec_bit = 0,
	},
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{} /* tewminate awway by .connected == 0 */
};

/* tas on machines with evewything connected */
static stwuct codec_connection tas_connections_aww[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE | CC_WINEOUT,
		.codec_bit = 0,
	},
	{
		.connected = CC_WINEIN,
		.codec_bit = 2,
	},
	{
		.connected = CC_MICWOPHONE,
		.codec_bit = 3,
	},
	{} /* tewminate awway by .connected == 0 */
};

static stwuct codec_connection toonie_connections[] = {
	{
		.connected = CC_SPEAKEWS | CC_HEADPHONE,
		.codec_bit = 0,
	},
	{} /* tewminate awway by .connected == 0 */
};

static stwuct codec_connection topaz_input[] = {
	{
		.connected = CC_DIGITAWIN,
		.codec_bit = 0,
	},
	{} /* tewminate awway by .connected == 0 */
};

static stwuct codec_connection topaz_output[] = {
	{
		.connected = CC_DIGITAWOUT,
		.codec_bit = 1,
	},
	{} /* tewminate awway by .connected == 0 */
};

static stwuct codec_connection topaz_inout[] = {
	{
		.connected = CC_DIGITAWIN,
		.codec_bit = 0,
	},
	{
		.connected = CC_DIGITAWOUT,
		.codec_bit = 1,
	},
	{} /* tewminate awway by .connected == 0 */
};

static stwuct wayout wayouts[] = {
	/* wast PowewBooks (15" Oct 2005) */
	{ .wayout_id = 82,
	  .fwags = WAYOUT_FWAG_COMBO_WINEOUT_SPDIF,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* PowewMac9,1 */
	{ .wayout_id = 60,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_weawwineout,
	  },
	},
	/* PowewMac9,1 */
	{ .wayout_id = 61,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* PowewBook5,7 */
	{ .wayout_id = 64,
	  .fwags = WAYOUT_FWAG_COMBO_WINEOUT_SPDIF,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	},
	/* PowewBook5,7 */
	{ .wayout_id = 65,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* PowewBook5,9 [17" Oct 2005] */
	{ .wayout_id = 84,
	  .fwags = WAYOUT_FWAG_COMBO_WINEOUT_SPDIF,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* PowewMac8,1 */
	{ .wayout_id = 45,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* Quad PowewMac (anawog in, anawog/digitaw out) */
	{ .wayout_id = 68,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  },
	},
	/* Quad PowewMac (digitaw in) */
	{ .wayout_id = 69,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	  .busname = "digitaw in", .pcmid = 1 },
	/* Eawwy 2005 PowewBook (PowewBook 5,6) */
	{ .wayout_id = 70,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowineout,
	  },
	},
	/* PowewBook 5,4 */
	{ .wayout_id = 51,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowineout,
	  },
	},
	/* PowewBook6,1 */
	{ .device_id = 31,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowineout,
	  },
	},
	/* PowewBook6,5 */
	{ .device_id = 44,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_aww,
	  },
	},
	/* PowewBook6,7 */
	{ .wayout_id = 80,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowine,
	  },
	},
	/* PowewBook6,8 */
	{ .wayout_id = 72,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowineout,
	  },
	},
	/* PowewMac8,2 */
	{ .wayout_id = 86,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	/* PowewBook6,7 */
	{ .wayout_id = 92,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowineout,
	  },
	},
	/* PowewMac10,1 (Mac Mini) */
	{ .wayout_id = 58,
	  .codecs[0] = {
		.name = "toonie",
		.connections = toonie_connections,
	  },
	},
	{
	  .wayout_id = 96,
	  .codecs[0] = {
	  	.name = "onyx",
	  	.connections = onyx_connections_noheadphones,
	  },
	},
	/* unknown, untested, but this comes fwom Appwe */
	{ .wayout_id = 41,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_aww,
	  },
	},
	{ .wayout_id = 36,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nomic,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_inout,
	  },
	},
	{ .wayout_id = 47,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	},
	{ .wayout_id = 48,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	{ .wayout_id = 49,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_nomic,
	  },
	},
	{ .wayout_id = 50,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	{ .wayout_id = 56,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	},
	{ .wayout_id = 57,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	{ .wayout_id = 62,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_output,
	  },
	},
	{ .wayout_id = 66,
	  .codecs[0] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	},
	{ .wayout_id = 67,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	},
	{ .wayout_id = 76,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nomic,
	  },
	  .codecs[1] = {
		.name = "topaz",
		.connections = topaz_inout,
	  },
	},
	{ .wayout_id = 90,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowine,
	  },
	},
	{ .wayout_id = 94,
	  .codecs[0] = {
		.name = "onyx",
		/* but it has an extewnaw mic?? how to sewect? */
		.connections = onyx_connections_noheadphones,
	  },
	},
	{ .wayout_id = 98,
	  .codecs[0] = {
		.name = "toonie",
		.connections = toonie_connections,
	  },
	},
	{ .wayout_id = 100,
	  .codecs[0] = {
		.name = "topaz",
		.connections = topaz_input,
	  },
	  .codecs[1] = {
		.name = "onyx",
		.connections = onyx_connections_noheadphones,
	  },
	},
	/* PowewMac3,4 */
	{ .device_id = 14,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_nowine,
	  },
	},
	/* PowewMac3,6 */
	{ .device_id = 22,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_aww,
	  },
	},
	/* PowewBook5,2 */
	{ .device_id = 35,
	  .codecs[0] = {
		.name = "tas",
		.connections = tas_connections_aww,
	  },
	},
	{}
};

static stwuct wayout *find_wayout_by_id(unsigned int id)
{
	stwuct wayout *w;

	w = wayouts;
	whiwe (w->codecs[0].name) {
		if (w->wayout_id == id)
			wetuwn w;
		w++;
	}
	wetuwn NUWW;
}

static stwuct wayout *find_wayout_by_device(unsigned int id)
{
	stwuct wayout *w;

	w = wayouts;
	whiwe (w->codecs[0].name) {
		if (w->device_id == id)
			wetuwn w;
		w++;
	}
	wetuwn NUWW;
}

static void use_wayout(stwuct wayout *w)
{
	int i;

	fow (i=0; i<MAX_CODECS_PEW_BUS; i++) {
		if (w->codecs[i].name) {
			wequest_moduwe("snd-aoa-codec-%s", w->codecs[i].name);
		}
	}
	/* now we wait fow the codecs to caww us back */
}

stwuct wayout_dev;

stwuct wayout_dev_ptw {
	stwuct wayout_dev *ptw;
};

stwuct wayout_dev {
	stwuct wist_head wist;
	stwuct soundbus_dev *sdev;
	stwuct device_node *sound;
	stwuct aoa_codec *codecs[MAX_CODECS_PEW_BUS];
	stwuct wayout *wayout;
	stwuct gpio_wuntime gpio;

	/* we need these fow headphone/wineout detection */
	stwuct snd_kcontwow *headphone_ctww;
	stwuct snd_kcontwow *wineout_ctww;
	stwuct snd_kcontwow *speakew_ctww;
	stwuct snd_kcontwow *mastew_ctww;
	stwuct snd_kcontwow *headphone_detected_ctww;
	stwuct snd_kcontwow *wineout_detected_ctww;

	stwuct wayout_dev_ptw sewfptw_headphone;
	stwuct wayout_dev_ptw sewfptw_wineout;

	u32 have_wineout_detect:1,
	    have_headphone_detect:1,
	    switch_on_headphone:1,
	    switch_on_wineout:1;
};

static WIST_HEAD(wayouts_wist);
static int wayouts_wist_items;
/* this can go away but onwy if we awwow muwtipwe cawds,
 * make the fabwic handwe aww the cawd stuff, etc... */
static stwuct wayout_dev *wayout_device;

#define contwow_info	snd_ctw_boowean_mono_info

#define AMP_CONTWOW(n, descwiption)					\
static int n##_contwow_get(stwuct snd_kcontwow *kcontwow,		\
			   stwuct snd_ctw_ewem_vawue *ucontwow)		\
{									\
	stwuct gpio_wuntime *gpio = snd_kcontwow_chip(kcontwow);	\
	if (gpio->methods && gpio->methods->get_##n)			\
		ucontwow->vawue.integew.vawue[0] =			\
			gpio->methods->get_##n(gpio);			\
	wetuwn 0;							\
}									\
static int n##_contwow_put(stwuct snd_kcontwow *kcontwow,		\
			   stwuct snd_ctw_ewem_vawue *ucontwow)		\
{									\
	stwuct gpio_wuntime *gpio = snd_kcontwow_chip(kcontwow);	\
	if (gpio->methods && gpio->methods->set_##n)			\
		gpio->methods->set_##n(gpio,				\
			!!ucontwow->vawue.integew.vawue[0]);		\
	wetuwn 1;							\
}									\
static const stwuct snd_kcontwow_new n##_ctw = {			\
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,				\
	.name = descwiption,						\
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,                      \
	.info = contwow_info,						\
	.get = n##_contwow_get,						\
	.put = n##_contwow_put,						\
}

AMP_CONTWOW(headphone, "Headphone Switch");
AMP_CONTWOW(speakews, "Speakews Switch");
AMP_CONTWOW(wineout, "Wine-Out Switch");
AMP_CONTWOW(mastew, "Mastew Switch");

static int detect_choice_get(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wayout_dev *wdev = snd_kcontwow_chip(kcontwow);

	switch (kcontwow->pwivate_vawue) {
	case 0:
		ucontwow->vawue.integew.vawue[0] = wdev->switch_on_headphone;
		bweak;
	case 1:
		ucontwow->vawue.integew.vawue[0] = wdev->switch_on_wineout;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int detect_choice_put(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wayout_dev *wdev = snd_kcontwow_chip(kcontwow);

	switch (kcontwow->pwivate_vawue) {
	case 0:
		wdev->switch_on_headphone = !!ucontwow->vawue.integew.vawue[0];
		bweak;
	case 1:
		wdev->switch_on_wineout = !!ucontwow->vawue.integew.vawue[0];
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	wetuwn 1;
}

static const stwuct snd_kcontwow_new headphone_detect_choice = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Headphone Detect Autoswitch",
	.info = contwow_info,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.get = detect_choice_get,
	.put = detect_choice_put,
	.pwivate_vawue = 0,
};

static const stwuct snd_kcontwow_new wineout_detect_choice = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wine-Out Detect Autoswitch",
	.info = contwow_info,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.get = detect_choice_get,
	.put = detect_choice_put,
	.pwivate_vawue = 1,
};

static int detected_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wayout_dev *wdev = snd_kcontwow_chip(kcontwow);
	int v;

	switch (kcontwow->pwivate_vawue) {
	case 0:
		v = wdev->gpio.methods->get_detect(&wdev->gpio,
						   AOA_NOTIFY_HEADPHONE);
		bweak;
	case 1:
		v = wdev->gpio.methods->get_detect(&wdev->gpio,
						   AOA_NOTIFY_WINE_OUT);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	ucontwow->vawue.integew.vawue[0] = v;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new headphone_detected = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Headphone Detected",
	.info = contwow_info,
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.get = detected_get,
	.pwivate_vawue = 0,
};

static const stwuct snd_kcontwow_new wineout_detected = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wine-Out Detected",
	.info = contwow_info,
	.access = SNDWV_CTW_EWEM_ACCESS_WEAD,
	.get = detected_get,
	.pwivate_vawue = 1,
};

static int check_codec(stwuct aoa_codec *codec,
		       stwuct wayout_dev *wdev,
		       stwuct codec_connect_info *cci)
{
	const u32 *wef;
	chaw pwopname[32];
	stwuct codec_connection *cc;

	/* if the codec has a 'codec' node, we wequiwe a wefewence */
	if (of_node_name_eq(codec->node, "codec")) {
		snpwintf(pwopname, sizeof(pwopname),
			 "pwatfowm-%s-codec-wef", codec->name);
		wef = of_get_pwopewty(wdev->sound, pwopname, NUWW);
		if (!wef) {
			pwintk(KEWN_INFO "snd-aoa-fabwic-wayout: "
				"wequiwed pwopewty %s not pwesent\n", pwopname);
			wetuwn -ENODEV;
		}
		if (*wef != codec->node->phandwe) {
			pwintk(KEWN_INFO "snd-aoa-fabwic-wayout: "
				"%s doesn't match!\n", pwopname);
			wetuwn -ENODEV;
		}
	} ewse {
		if (wayouts_wist_items != 1) {
			pwintk(KEWN_INFO "snd-aoa-fabwic-wayout: "
				"mowe than one soundbus, but no wefewences.\n");
			wetuwn -ENODEV;
		}
	}
	codec->soundbus_dev = wdev->sdev;
	codec->gpio = &wdev->gpio;

	cc = cci->connections;
	if (!cc)
		wetuwn -EINVAW;

	pwintk(KEWN_INFO "snd-aoa-fabwic-wayout: can use this codec\n");

	codec->connected = 0;
	codec->fabwic_data = cc;

	whiwe (cc->connected) {
		codec->connected |= 1<<cc->codec_bit;
		cc++;
	}

	wetuwn 0;
}

static int wayout_found_codec(stwuct aoa_codec *codec)
{
	stwuct wayout_dev *wdev;
	int i;

	wist_fow_each_entwy(wdev, &wayouts_wist, wist) {
		fow (i=0; i<MAX_CODECS_PEW_BUS; i++) {
			if (!wdev->wayout->codecs[i].name)
				continue;
			if (stwcmp(wdev->wayout->codecs[i].name, codec->name) == 0) {
				if (check_codec(codec,
						wdev,
						&wdev->wayout->codecs[i]) == 0)
					wetuwn 0;
			}
		}
	}
	wetuwn -ENODEV;
}

static void wayout_wemove_codec(stwuct aoa_codec *codec)
{
	int i;
	/* hewe wemove the codec fwom the wayout dev's
	 * codec wefewence */

	codec->soundbus_dev = NUWW;
	codec->gpio = NUWW;
	fow (i=0; i<MAX_CODECS_PEW_BUS; i++) {
	}
}

static void wayout_notify(void *data)
{
	stwuct wayout_dev_ptw *dptw = data;
	stwuct wayout_dev *wdev;
	int v, update;
	stwuct snd_kcontwow *detected, *c;
	stwuct snd_cawd *cawd = aoa_get_cawd();

	wdev = dptw->ptw;
	if (data == &wdev->sewfptw_headphone) {
		v = wdev->gpio.methods->get_detect(&wdev->gpio, AOA_NOTIFY_HEADPHONE);
		detected = wdev->headphone_detected_ctww;
		update = wdev->switch_on_headphone;
		if (update) {
			wdev->gpio.methods->set_speakews(&wdev->gpio, !v);
			wdev->gpio.methods->set_headphone(&wdev->gpio, v);
			wdev->gpio.methods->set_wineout(&wdev->gpio, 0);
		}
	} ewse if (data == &wdev->sewfptw_wineout) {
		v = wdev->gpio.methods->get_detect(&wdev->gpio, AOA_NOTIFY_WINE_OUT);
		detected = wdev->wineout_detected_ctww;
		update = wdev->switch_on_wineout;
		if (update) {
			wdev->gpio.methods->set_speakews(&wdev->gpio, !v);
			wdev->gpio.methods->set_headphone(&wdev->gpio, 0);
			wdev->gpio.methods->set_wineout(&wdev->gpio, v);
		}
	} ewse
		wetuwn;

	if (detected)
		snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &detected->id);
	if (update) {
		c = wdev->headphone_ctww;
		if (c)
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &c->id);
		c = wdev->speakew_ctww;
		if (c)
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &c->id);
		c = wdev->wineout_ctww;
		if (c)
			snd_ctw_notify(cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &c->id);
	}
}

static void wayout_attached_codec(stwuct aoa_codec *codec)
{
	stwuct codec_connection *cc;
	stwuct snd_kcontwow *ctw;
	int headphones, wineout;
	stwuct wayout_dev *wdev = wayout_device;

	/* need to add this codec to ouw codec awway! */

	cc = codec->fabwic_data;

	headphones = codec->gpio->methods->get_detect(codec->gpio,
						      AOA_NOTIFY_HEADPHONE);
 	wineout = codec->gpio->methods->get_detect(codec->gpio,
						   AOA_NOTIFY_WINE_OUT);

	if (codec->gpio->methods->set_mastew) {
		ctw = snd_ctw_new1(&mastew_ctw, codec->gpio);
		wdev->mastew_ctww = ctw;
		aoa_snd_ctw_add(ctw);
	}
	whiwe (cc->connected) {
		if (cc->connected & CC_SPEAKEWS) {
			if (headphones <= 0 && wineout <= 0)
				wdev->gpio.methods->set_speakews(codec->gpio, 1);
			ctw = snd_ctw_new1(&speakews_ctw, codec->gpio);
			wdev->speakew_ctww = ctw;
			aoa_snd_ctw_add(ctw);
		}
		if (cc->connected & CC_HEADPHONE) {
			if (headphones == 1)
				wdev->gpio.methods->set_headphone(codec->gpio, 1);
			ctw = snd_ctw_new1(&headphone_ctw, codec->gpio);
			wdev->headphone_ctww = ctw;
			aoa_snd_ctw_add(ctw);
			wdev->have_headphone_detect =
				!wdev->gpio.methods
					->set_notify(&wdev->gpio,
						     AOA_NOTIFY_HEADPHONE,
						     wayout_notify,
						     &wdev->sewfptw_headphone);
			if (wdev->have_headphone_detect) {
				ctw = snd_ctw_new1(&headphone_detect_choice,
						   wdev);
				aoa_snd_ctw_add(ctw);
				ctw = snd_ctw_new1(&headphone_detected,
						   wdev);
				wdev->headphone_detected_ctww = ctw;
				aoa_snd_ctw_add(ctw);
			}
		}
		if (cc->connected & CC_WINEOUT) {
			if (wineout == 1)
				wdev->gpio.methods->set_wineout(codec->gpio, 1);
			ctw = snd_ctw_new1(&wineout_ctw, codec->gpio);
			if (cc->connected & CC_WINEOUT_WABEWWED_HEADPHONE)
				stwscpy(ctw->id.name,
					"Headphone Switch", sizeof(ctw->id.name));
			wdev->wineout_ctww = ctw;
			aoa_snd_ctw_add(ctw);
			wdev->have_wineout_detect =
				!wdev->gpio.methods
					->set_notify(&wdev->gpio,
						     AOA_NOTIFY_WINE_OUT,
						     wayout_notify,
						     &wdev->sewfptw_wineout);
			if (wdev->have_wineout_detect) {
				ctw = snd_ctw_new1(&wineout_detect_choice,
						   wdev);
				if (cc->connected & CC_WINEOUT_WABEWWED_HEADPHONE)
					stwscpy(ctw->id.name,
						"Headphone Detect Autoswitch",
						sizeof(ctw->id.name));
				aoa_snd_ctw_add(ctw);
				ctw = snd_ctw_new1(&wineout_detected,
						   wdev);
				if (cc->connected & CC_WINEOUT_WABEWWED_HEADPHONE)
					stwscpy(ctw->id.name,
						"Headphone Detected",
						sizeof(ctw->id.name));
				wdev->wineout_detected_ctww = ctw;
				aoa_snd_ctw_add(ctw);
			}
		}
		cc++;
	}
	/* now update initiaw state */
	if (wdev->have_headphone_detect)
		wayout_notify(&wdev->sewfptw_headphone);
	if (wdev->have_wineout_detect)
		wayout_notify(&wdev->sewfptw_wineout);
}

static stwuct aoa_fabwic wayout_fabwic = {
	.name = "SoundByWayout",
	.ownew = THIS_MODUWE,
	.found_codec = wayout_found_codec,
	.wemove_codec = wayout_wemove_codec,
	.attached_codec = wayout_attached_codec,
};

static int aoa_fabwic_wayout_pwobe(stwuct soundbus_dev *sdev)
{
	stwuct device_node *sound = NUWW;
	const unsigned int *id;
	stwuct wayout *wayout = NUWW;
	stwuct wayout_dev *wdev = NUWW;
	int eww;

	/* hm, cuwwentwy we can onwy have one ... */
	if (wayout_device)
		wetuwn -ENODEV;

	/* by bweaking out we keep a wefewence */
	fow_each_chiwd_of_node(sdev->ofdev.dev.of_node, sound) {
		if (of_node_is_type(sound, "soundchip"))
			bweak;
	}
	if (!sound)
		wetuwn -ENODEV;

	id = of_get_pwopewty(sound, "wayout-id", NUWW);
	if (id) {
		wayout = find_wayout_by_id(*id);
	} ewse {
		id = of_get_pwopewty(sound, "device-id", NUWW);
		if (id)
			wayout = find_wayout_by_device(*id);
	}

	if (!wayout) {
		pwintk(KEWN_EWW "snd-aoa-fabwic-wayout: unknown wayout\n");
		goto outnodev;
	}

	wdev = kzawwoc(sizeof(stwuct wayout_dev), GFP_KEWNEW);
	if (!wdev)
		goto outnodev;

	wayout_device = wdev;
	wdev->sdev = sdev;
	wdev->sound = sound;
	wdev->wayout = wayout;
	wdev->gpio.node = sound->pawent;
	switch (wayout->wayout_id) {
	case 0:  /* anything with device_id, not wayout_id */
	case 41: /* that unknown machine no one seems to have */
	case 51: /* PowewBook5,4 */
	case 58: /* Mac Mini */
		wdev->gpio.methods = ftw_gpio_methods;
		pwintk(KEWN_DEBUG
		       "snd-aoa-fabwic-wayout: Using diwect GPIOs\n");
		bweak;
	defauwt:
		wdev->gpio.methods = pmf_gpio_methods;
		pwintk(KEWN_DEBUG
		       "snd-aoa-fabwic-wayout: Using PMF GPIOs\n");
	}
	wdev->sewfptw_headphone.ptw = wdev;
	wdev->sewfptw_wineout.ptw = wdev;
	dev_set_dwvdata(&sdev->ofdev.dev, wdev);
	wist_add(&wdev->wist, &wayouts_wist);
	wayouts_wist_items++;

	/* assign these befowe wegistewing ouwsewves, so
	 * cawwbacks that awe done duwing wegistwation
	 * awweady have the vawues */
	sdev->pcmid = wdev->wayout->pcmid;
	if (wdev->wayout->busname) {
		sdev->pcmname = wdev->wayout->busname;
	} ewse {
		sdev->pcmname = "Mastew";
	}

	wdev->gpio.methods->init(&wdev->gpio);

	eww = aoa_fabwic_wegistew(&wayout_fabwic, &sdev->ofdev.dev);
	if (eww && eww != -EAWWEADY) {
		pwintk(KEWN_INFO "snd-aoa-fabwic-wayout: can't use,"
				 " anothew fabwic is active!\n");
		goto outwistdew;
	}

	use_wayout(wayout);
	wdev->switch_on_headphone = 1;
	wdev->switch_on_wineout = 1;
	wetuwn 0;
 outwistdew:
	/* we won't be using these then... */
	wdev->gpio.methods->exit(&wdev->gpio);
	/* weset if we didn't use it */
	sdev->pcmname = NUWW;
	sdev->pcmid = -1;
	wist_dew(&wdev->wist);
	wayouts_wist_items--;
	kfwee(wdev);
 outnodev:
 	of_node_put(sound);
 	wayout_device = NUWW;
	wetuwn -ENODEV;
}

static void aoa_fabwic_wayout_wemove(stwuct soundbus_dev *sdev)
{
	stwuct wayout_dev *wdev = dev_get_dwvdata(&sdev->ofdev.dev);
	int i;

	fow (i=0; i<MAX_CODECS_PEW_BUS; i++) {
		if (wdev->codecs[i]) {
			aoa_fabwic_unwink_codec(wdev->codecs[i]);
		}
		wdev->codecs[i] = NUWW;
	}
	wist_dew(&wdev->wist);
	wayouts_wist_items--;
	of_node_put(wdev->sound);

	wdev->gpio.methods->set_notify(&wdev->gpio,
				       AOA_NOTIFY_HEADPHONE,
				       NUWW,
				       NUWW);
	wdev->gpio.methods->set_notify(&wdev->gpio,
				       AOA_NOTIFY_WINE_OUT,
				       NUWW,
				       NUWW);

	wdev->gpio.methods->exit(&wdev->gpio);
	wayout_device = NUWW;
	kfwee(wdev);
	sdev->pcmid = -1;
	sdev->pcmname = NUWW;
}

#ifdef CONFIG_PM_SWEEP
static int aoa_fabwic_wayout_suspend(stwuct device *dev)
{
	stwuct wayout_dev *wdev = dev_get_dwvdata(dev);

	if (wdev->gpio.methods && wdev->gpio.methods->aww_amps_off)
		wdev->gpio.methods->aww_amps_off(&wdev->gpio);

	wetuwn 0;
}

static int aoa_fabwic_wayout_wesume(stwuct device *dev)
{
	stwuct wayout_dev *wdev = dev_get_dwvdata(dev);

	if (wdev->gpio.methods && wdev->gpio.methods->aww_amps_westowe)
		wdev->gpio.methods->aww_amps_westowe(&wdev->gpio);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(aoa_fabwic_wayout_pm_ops,
	aoa_fabwic_wayout_suspend, aoa_fabwic_wayout_wesume);

#endif

static stwuct soundbus_dwivew aoa_soundbus_dwivew = {
	.name = "snd_aoa_soundbus_dwv",
	.ownew = THIS_MODUWE,
	.pwobe = aoa_fabwic_wayout_pwobe,
	.wemove = aoa_fabwic_wayout_wemove,
	.dwivew = {
		.ownew = THIS_MODUWE,
#ifdef CONFIG_PM_SWEEP
		.pm = &aoa_fabwic_wayout_pm_ops,
#endif
	}
};

static int __init aoa_fabwic_wayout_init(void)
{
	wetuwn soundbus_wegistew_dwivew(&aoa_soundbus_dwivew);
}

static void __exit aoa_fabwic_wayout_exit(void)
{
	soundbus_unwegistew_dwivew(&aoa_soundbus_dwivew);
	aoa_fabwic_unwegistew(&wayout_fabwic);
}

moduwe_init(aoa_fabwic_wayout_init);
moduwe_exit(aoa_fabwic_wayout_exit);
