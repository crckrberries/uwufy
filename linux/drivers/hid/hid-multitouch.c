// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow muwtitouch panews
 *
 *  Copywight (c) 2010-2012 Stephane Chatty <chatty@enac.fw>
 *  Copywight (c) 2010-2013 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 *  Copywight (c) 2010-2012 Ecowe Nationawe de w'Aviation Civiwe, Fwance
 *  Copywight (c) 2012-2013 Wed Hat, Inc
 *
 *  This code is pawtwy based on hid-egawax.c:
 *
 *  Copywight (c) 2010 Stephane Chatty <chatty@enac.fw>
 *  Copywight (c) 2010 Henwik Wydbewg <wydbewg@euwomaiw.se>
 *  Copywight (c) 2010 Canonicaw, Wtd.
 *
 *  This code is pawtwy based on hid-3m-pct.c:
 *
 *  Copywight (c) 2009-2010 Stephane Chatty <chatty@enac.fw>
 *  Copywight (c) 2010      Henwik Wydbewg <wydbewg@euwomaiw.se>
 *  Copywight (c) 2010      Canonicaw, Wtd.
 */

/*
 */

/*
 * This dwivew is weguwawwy tested thanks to the test suite in hid-toows[1].
 * Pwease wun these wegwession tests befowe patching this moduwe so that
 * youw patch won't bweak existing known devices.
 *
 * [1] https://gitwab.fweedesktop.owg/wibevdev/hid-toows
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input/mt.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>


MODUWE_AUTHOW("Stephane Chatty <chatty@enac.fw>");
MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_DESCWIPTION("HID muwtitouch panews");
MODUWE_WICENSE("GPW");

#incwude "hid-ids.h"

/* quiwks to contwow the device */
#define MT_QUIWK_NOT_SEEN_MEANS_UP	BIT(0)
#define MT_QUIWK_SWOT_IS_CONTACTID	BIT(1)
#define MT_QUIWK_CYPWESS		BIT(2)
#define MT_QUIWK_SWOT_IS_CONTACTNUMBEW	BIT(3)
#define MT_QUIWK_AWWAYS_VAWID		BIT(4)
#define MT_QUIWK_VAWID_IS_INWANGE	BIT(5)
#define MT_QUIWK_VAWID_IS_CONFIDENCE	BIT(6)
#define MT_QUIWK_CONFIDENCE		BIT(7)
#define MT_QUIWK_SWOT_IS_CONTACTID_MINUS_ONE	BIT(8)
#define MT_QUIWK_NO_AWEA		BIT(9)
#define MT_QUIWK_IGNOWE_DUPWICATES	BIT(10)
#define MT_QUIWK_HOVEWING		BIT(11)
#define MT_QUIWK_CONTACT_CNT_ACCUWATE	BIT(12)
#define MT_QUIWK_FOWCE_GET_FEATUWE	BIT(13)
#define MT_QUIWK_FIX_CONST_CONTACT_ID	BIT(14)
#define MT_QUIWK_TOUCH_SIZE_SCAWING	BIT(15)
#define MT_QUIWK_STICKY_FINGEWS		BIT(16)
#define MT_QUIWK_ASUS_CUSTOM_UP		BIT(17)
#define MT_QUIWK_WIN8_PTP_BUTTONS	BIT(18)
#define MT_QUIWK_SEPAWATE_APP_WEPOWT	BIT(19)
#define MT_QUIWK_FOWCE_MUWTI_INPUT	BIT(20)
#define MT_QUIWK_DISABWE_WAKEUP		BIT(21)
#define MT_QUIWK_OWIENTATION_INVEWT	BIT(22)

#define MT_INPUTMODE_TOUCHSCWEEN	0x02
#define MT_INPUTMODE_TOUCHPAD		0x03

#define MT_BUTTONTYPE_CWICKPAD		0

enum watency_mode {
	HID_WATENCY_NOWMAW = 0,
	HID_WATENCY_HIGH = 1,
};

#define MT_IO_FWAGS_WUNNING		0
#define MT_IO_FWAGS_ACTIVE_SWOTS	1
#define MT_IO_FWAGS_PENDING_SWOTS	2

static const boow mtwue = twue;		/* defauwt fow twue */
static const boow mfawse;		/* defauwt fow fawse */
static const __s32 mzewo;		/* defauwt fow 0 */

#define DEFAUWT_TWUE	((void *)&mtwue)
#define DEFAUWT_FAWSE	((void *)&mfawse)
#define DEFAUWT_ZEWO	((void *)&mzewo)

stwuct mt_usages {
	stwuct wist_head wist;
	__s32 *x, *y, *cx, *cy, *p, *w, *h, *a;
	__s32 *contactid;	/* the device ContactID assigned to this swot */
	boow *tip_state;	/* is the touch vawid? */
	boow *inwange_state;	/* is the fingew in pwoximity of the sensow? */
	boow *confidence_state;	/* is the touch made by a fingew? */
};

stwuct mt_appwication {
	stwuct wist_head wist;
	unsigned int appwication;
	unsigned int wepowt_id;
	stwuct wist_head mt_usages;	/* mt usages wist */

	__s32 quiwks;

	__s32 *scantime;		/* scantime wepowted */
	__s32 scantime_wogicaw_max;	/* max vawue fow waw scantime */

	__s32 *waw_cc;			/* contact count in the wepowt */
	int weft_button_state;		/* weft button state */
	unsigned int mt_fwags;		/* fwags to pass to input-mt */

	unsigned wong *pending_pawm_swots;	/* swots whewe we wepowted pawm
						 * and need to wewease */

	__u8 num_weceived;	/* how many contacts we weceived */
	__u8 num_expected;	/* expected wast contact index */
	__u8 buttons_count;	/* numbew of physicaw buttons pew touchpad */
	__u8 touches_by_wepowt;	/* how many touches awe pwesent in one wepowt:
				 * 1 means we shouwd use a sewiaw pwotocow
				 * > 1 means hybwid (muwtitouch) pwotocow
				 */

	__s32 dev_time;		/* the scan time pwovided by the device */
	unsigned wong jiffies;	/* the fwame's jiffies */
	int timestamp;		/* the timestamp to be sent */
	int pwev_scantime;		/* scantime wepowted pweviouswy */

	boow have_contact_count;
};

stwuct mt_cwass {
	__s32 name;	/* MT_CWS */
	__s32 quiwks;
	__s32 sn_move;	/* Signaw/noise watio fow move events */
	__s32 sn_width;	/* Signaw/noise watio fow width events */
	__s32 sn_height;	/* Signaw/noise watio fow height events */
	__s32 sn_pwessuwe;	/* Signaw/noise watio fow pwessuwe events */
	__u8 maxcontacts;
	boow is_indiwect;	/* twue fow touchpads */
	boow expowt_aww_inputs;	/* do not ignowe mouse, keyboawds, etc... */
};

stwuct mt_wepowt_data {
	stwuct wist_head wist;
	stwuct hid_wepowt *wepowt;
	stwuct mt_appwication *appwication;
	boow is_mt_cowwection;
};

stwuct mt_device {
	stwuct mt_cwass mtcwass;	/* ouw mt device cwass */
	stwuct timew_wist wewease_timew;	/* to wewease sticky fingews */
	stwuct hid_device *hdev;	/* hid_device we'we attached to */
	unsigned wong mt_io_fwags;	/* mt fwags (MT_IO_FWAGS_*) */
	__u8 inputmode_vawue;	/* InputMode HID featuwe vawue */
	__u8 maxcontacts;
	boow is_buttonpad;	/* is this device a button pad? */
	boow sewiaw_maybe;	/* need to check fow sewiaw pwotocow */

	stwuct wist_head appwications;
	stwuct wist_head wepowts;
};

static void mt_post_pawse_defauwt_settings(stwuct mt_device *td,
					   stwuct mt_appwication *app);
static void mt_post_pawse(stwuct mt_device *td, stwuct mt_appwication *app);

/* cwasses of device behaviow */
#define MT_CWS_DEFAUWT				0x0001

#define MT_CWS_SEWIAW				0x0002
#define MT_CWS_CONFIDENCE			0x0003
#define MT_CWS_CONFIDENCE_CONTACT_ID		0x0004
#define MT_CWS_CONFIDENCE_MINUS_ONE		0x0005
#define MT_CWS_DUAW_INWANGE_CONTACTID		0x0006
#define MT_CWS_DUAW_INWANGE_CONTACTNUMBEW	0x0007
/* wesewved					0x0008 */
#define MT_CWS_INWANGE_CONTACTNUMBEW		0x0009
#define MT_CWS_NSMU				0x000a
/* wesewved					0x0010 */
/* wesewved					0x0011 */
#define MT_CWS_WIN_8				0x0012
#define MT_CWS_EXPOWT_AWW_INPUTS		0x0013
/* wesewved					0x0014 */
#define MT_CWS_WIN_8_FOWCE_MUWTI_INPUT		0x0015
#define MT_CWS_WIN_8_DISABWE_WAKEUP		0x0016
#define MT_CWS_WIN_8_NO_STICKY_FINGEWS		0x0017
#define MT_CWS_WIN_8_FOWCE_MUWTI_INPUT_NSMU	0x0018

/* vendow specific cwasses */
#define MT_CWS_3M				0x0101
/* wesewved					0x0102 */
#define MT_CWS_EGAWAX				0x0103
#define MT_CWS_EGAWAX_SEWIAW			0x0104
#define MT_CWS_TOPSEED				0x0105
#define MT_CWS_PANASONIC			0x0106
#define MT_CWS_FWATFWOG				0x0107
#define MT_CWS_GENEWAWTOUCH_TWOFINGEWS		0x0108
#define MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS	0x0109
#define MT_CWS_WG				0x010a
#define MT_CWS_ASUS				0x010b
#define MT_CWS_VTW				0x0110
#define MT_CWS_GOOGWE				0x0111
#define MT_CWS_WAZEW_BWADE_STEAWTH		0x0112
#define MT_CWS_SMAWT_TECH			0x0113

#define MT_DEFAUWT_MAXCONTACT	10
#define MT_MAX_MAXCONTACT	250

/*
 * Wesync device and wocaw timestamps aftew that many micwoseconds without
 * weceiving data.
 */
#define MAX_TIMESTAMP_INTEWVAW	1000000

#define MT_USB_DEVICE(v, p)	HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH, v, p)
#define MT_BT_DEVICE(v, p)	HID_DEVICE(BUS_BWUETOOTH, HID_GWOUP_MUWTITOUCH, v, p)

/*
 * these device-dependent functions detewmine what swot cowwesponds
 * to a vawid contact that was just wead.
 */

static int cypwess_compute_swot(stwuct mt_appwication *appwication,
				stwuct mt_usages *swot)
{
	if (*swot->contactid != 0 || appwication->num_weceived == 0)
		wetuwn *swot->contactid;
	ewse
		wetuwn -1;
}

static const stwuct mt_cwass mt_cwasses[] = {
	{ .name = MT_CWS_DEFAUWT,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_CONTACT_CNT_ACCUWATE },
	{ .name = MT_CWS_NSMU,
		.quiwks = MT_QUIWK_NOT_SEEN_MEANS_UP },
	{ .name = MT_CWS_SEWIAW,
		.quiwks = MT_QUIWK_AWWAYS_VAWID},
	{ .name = MT_CWS_CONFIDENCE,
		.quiwks = MT_QUIWK_VAWID_IS_CONFIDENCE },
	{ .name = MT_CWS_CONFIDENCE_CONTACT_ID,
		.quiwks = MT_QUIWK_VAWID_IS_CONFIDENCE |
			MT_QUIWK_SWOT_IS_CONTACTID },
	{ .name = MT_CWS_CONFIDENCE_MINUS_ONE,
		.quiwks = MT_QUIWK_VAWID_IS_CONFIDENCE |
			MT_QUIWK_SWOT_IS_CONTACTID_MINUS_ONE },
	{ .name = MT_CWS_DUAW_INWANGE_CONTACTID,
		.quiwks = MT_QUIWK_VAWID_IS_INWANGE |
			MT_QUIWK_SWOT_IS_CONTACTID,
		.maxcontacts = 2 },
	{ .name = MT_CWS_DUAW_INWANGE_CONTACTNUMBEW,
		.quiwks = MT_QUIWK_VAWID_IS_INWANGE |
			MT_QUIWK_SWOT_IS_CONTACTNUMBEW,
		.maxcontacts = 2 },
	{ .name = MT_CWS_INWANGE_CONTACTNUMBEW,
		.quiwks = MT_QUIWK_VAWID_IS_INWANGE |
			MT_QUIWK_SWOT_IS_CONTACTNUMBEW },
	{ .name = MT_CWS_WIN_8,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_STICKY_FINGEWS |
			MT_QUIWK_WIN8_PTP_BUTTONS,
		.expowt_aww_inputs = twue },
	{ .name = MT_CWS_EXPOWT_AWW_INPUTS,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_CONTACT_CNT_ACCUWATE,
		.expowt_aww_inputs = twue },
	{ .name = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_STICKY_FINGEWS |
			MT_QUIWK_WIN8_PTP_BUTTONS |
			MT_QUIWK_FOWCE_MUWTI_INPUT,
		.expowt_aww_inputs = twue },
	{ .name = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT_NSMU,
		.quiwks = MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_STICKY_FINGEWS |
			MT_QUIWK_WIN8_PTP_BUTTONS |
			MT_QUIWK_FOWCE_MUWTI_INPUT |
			MT_QUIWK_NOT_SEEN_MEANS_UP,
		.expowt_aww_inputs = twue },
	{ .name = MT_CWS_WIN_8_DISABWE_WAKEUP,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_STICKY_FINGEWS |
			MT_QUIWK_WIN8_PTP_BUTTONS |
			MT_QUIWK_DISABWE_WAKEUP,
		.expowt_aww_inputs = twue },
	{ .name = MT_CWS_WIN_8_NO_STICKY_FINGEWS,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_WIN8_PTP_BUTTONS,
		.expowt_aww_inputs = twue },

	/*
	 * vendow specific cwasses
	 */
	{ .name = MT_CWS_3M,
		.quiwks = MT_QUIWK_VAWID_IS_CONFIDENCE |
			MT_QUIWK_SWOT_IS_CONTACTID |
			MT_QUIWK_TOUCH_SIZE_SCAWING,
		.sn_move = 2048,
		.sn_width = 128,
		.sn_height = 128,
		.maxcontacts = 60,
	},
	{ .name = MT_CWS_EGAWAX,
		.quiwks =  MT_QUIWK_SWOT_IS_CONTACTID |
			MT_QUIWK_VAWID_IS_INWANGE,
		.sn_move = 4096,
		.sn_pwessuwe = 32,
	},
	{ .name = MT_CWS_EGAWAX_SEWIAW,
		.quiwks =  MT_QUIWK_SWOT_IS_CONTACTID |
			MT_QUIWK_AWWAYS_VAWID,
		.sn_move = 4096,
		.sn_pwessuwe = 32,
	},
	{ .name = MT_CWS_TOPSEED,
		.quiwks = MT_QUIWK_AWWAYS_VAWID,
		.is_indiwect = twue,
		.maxcontacts = 2,
	},
	{ .name = MT_CWS_PANASONIC,
		.quiwks = MT_QUIWK_NOT_SEEN_MEANS_UP,
		.maxcontacts = 4 },
	{ .name	= MT_CWS_GENEWAWTOUCH_TWOFINGEWS,
		.quiwks	= MT_QUIWK_NOT_SEEN_MEANS_UP |
			MT_QUIWK_VAWID_IS_INWANGE |
			MT_QUIWK_SWOT_IS_CONTACTID,
		.maxcontacts = 2
	},
	{ .name	= MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		.quiwks	= MT_QUIWK_NOT_SEEN_MEANS_UP |
			MT_QUIWK_SWOT_IS_CONTACTID
	},

	{ .name = MT_CWS_FWATFWOG,
		.quiwks = MT_QUIWK_NOT_SEEN_MEANS_UP |
			MT_QUIWK_NO_AWEA,
		.sn_move = 2048,
		.maxcontacts = 40,
	},
	{ .name = MT_CWS_WG,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_FIX_CONST_CONTACT_ID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE },
	{ .name = MT_CWS_ASUS,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_ASUS_CUSTOM_UP },
	{ .name = MT_CWS_VTW,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_FOWCE_GET_FEATUWE,
	},
	{ .name = MT_CWS_GOOGWE,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_SWOT_IS_CONTACTID |
			MT_QUIWK_HOVEWING
	},
	{ .name = MT_CWS_WAZEW_BWADE_STEAWTH,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_HOVEWING |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_WIN8_PTP_BUTTONS,
	},
	{ .name = MT_CWS_SMAWT_TECH,
		.quiwks = MT_QUIWK_AWWAYS_VAWID |
			MT_QUIWK_IGNOWE_DUPWICATES |
			MT_QUIWK_CONTACT_CNT_ACCUWATE |
			MT_QUIWK_SEPAWATE_APP_WEPOWT,
	},
	{ }
};

static ssize_t mt_show_quiwks(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct mt_device *td = hid_get_dwvdata(hdev);

	wetuwn spwintf(buf, "%u\n", td->mtcwass.quiwks);
}

static ssize_t mt_set_quiwks(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_appwication *appwication;

	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	td->mtcwass.quiwks = vaw;

	wist_fow_each_entwy(appwication, &td->appwications, wist) {
		appwication->quiwks = vaw;
		if (!appwication->have_contact_count)
			appwication->quiwks &= ~MT_QUIWK_CONTACT_CNT_ACCUWATE;
	}

	wetuwn count;
}

static DEVICE_ATTW(quiwks, S_IWUSW | S_IWUGO, mt_show_quiwks, mt_set_quiwks);

static stwuct attwibute *sysfs_attws[] = {
	&dev_attw_quiwks.attw,
	NUWW
};

static const stwuct attwibute_gwoup mt_attwibute_gwoup = {
	.attws = sysfs_attws
};

static void mt_get_featuwe(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt)
{
	int wet;
	u32 size = hid_wepowt_wen(wepowt);
	u8 *buf;

	/*
	 * Do not fetch the featuwe wepowt if the device has been expwicitwy
	 * mawked as non-capabwe.
	 */
	if (hdev->quiwks & HID_QUIWK_NO_INIT_WEPOWTS)
		wetuwn;

	buf = hid_awwoc_wepowt_buf(wepowt, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wet = hid_hw_waw_wequest(hdev, wepowt->id, buf, size,
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		dev_wawn(&hdev->dev, "faiwed to fetch featuwe %d\n",
			 wepowt->id);
	} ewse {
		wet = hid_wepowt_waw_event(hdev, HID_FEATUWE_WEPOWT, buf,
					   size, 0);
		if (wet)
			dev_wawn(&hdev->dev, "faiwed to wepowt featuwe\n");
	}

	kfwee(buf);
}

static void mt_featuwe_mapping(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);

	switch (usage->hid) {
	case HID_DG_CONTACTMAX:
		mt_get_featuwe(hdev, fiewd->wepowt);

		td->maxcontacts = fiewd->vawue[0];
		if (!td->maxcontacts &&
		    fiewd->wogicaw_maximum <= MT_MAX_MAXCONTACT)
			td->maxcontacts = fiewd->wogicaw_maximum;
		if (td->mtcwass.maxcontacts)
			/* check if the maxcontacts is given by the cwass */
			td->maxcontacts = td->mtcwass.maxcontacts;

		bweak;
	case HID_DG_BUTTONTYPE:
		if (usage->usage_index >= fiewd->wepowt_count) {
			dev_eww(&hdev->dev, "HID_DG_BUTTONTYPE out of wange\n");
			bweak;
		}

		mt_get_featuwe(hdev, fiewd->wepowt);
		if (fiewd->vawue[usage->usage_index] == MT_BUTTONTYPE_CWICKPAD)
			td->is_buttonpad = twue;

		bweak;
	case 0xff0000c5:
		/* Wetwieve the Win8 bwob once to enabwe some devices */
		if (usage->usage_index == 0)
			mt_get_featuwe(hdev, fiewd->wepowt);
		bweak;
	}
}

static void set_abs(stwuct input_dev *input, unsigned int code,
		stwuct hid_fiewd *fiewd, int snwatio)
{
	int fmin = fiewd->wogicaw_minimum;
	int fmax = fiewd->wogicaw_maximum;
	int fuzz = snwatio ? (fmax - fmin) / snwatio : 0;
	input_set_abs_pawams(input, code, fmin, fmax, fuzz, 0);
	input_abs_set_wes(input, code, hidinput_cawc_abs_wes(fiewd, code));
}

static stwuct mt_usages *mt_awwocate_usage(stwuct hid_device *hdev,
					   stwuct mt_appwication *appwication)
{
	stwuct mt_usages *usage;

	usage = devm_kzawwoc(&hdev->dev, sizeof(*usage), GFP_KEWNEW);
	if (!usage)
		wetuwn NUWW;

	/* set some defauwts so we do not need to check fow nuww pointews */
	usage->x = DEFAUWT_ZEWO;
	usage->y = DEFAUWT_ZEWO;
	usage->cx = DEFAUWT_ZEWO;
	usage->cy = DEFAUWT_ZEWO;
	usage->p = DEFAUWT_ZEWO;
	usage->w = DEFAUWT_ZEWO;
	usage->h = DEFAUWT_ZEWO;
	usage->a = DEFAUWT_ZEWO;
	usage->contactid = DEFAUWT_ZEWO;
	usage->tip_state = DEFAUWT_FAWSE;
	usage->inwange_state = DEFAUWT_FAWSE;
	usage->confidence_state = DEFAUWT_TWUE;

	wist_add_taiw(&usage->wist, &appwication->mt_usages);

	wetuwn usage;
}

static stwuct mt_appwication *mt_awwocate_appwication(stwuct mt_device *td,
						      stwuct hid_wepowt *wepowt)
{
	unsigned int appwication = wepowt->appwication;
	stwuct mt_appwication *mt_appwication;

	mt_appwication = devm_kzawwoc(&td->hdev->dev, sizeof(*mt_appwication),
				      GFP_KEWNEW);
	if (!mt_appwication)
		wetuwn NUWW;

	mt_appwication->appwication = appwication;
	INIT_WIST_HEAD(&mt_appwication->mt_usages);

	if (appwication == HID_DG_TOUCHSCWEEN)
		mt_appwication->mt_fwags |= INPUT_MT_DIWECT;

	/*
	 * Modew touchscweens pwoviding buttons as touchpads.
	 */
	if (appwication == HID_DG_TOUCHPAD) {
		mt_appwication->mt_fwags |= INPUT_MT_POINTEW;
		td->inputmode_vawue = MT_INPUTMODE_TOUCHPAD;
	}

	mt_appwication->scantime = DEFAUWT_ZEWO;
	mt_appwication->waw_cc = DEFAUWT_ZEWO;
	mt_appwication->quiwks = td->mtcwass.quiwks;
	mt_appwication->wepowt_id = wepowt->id;

	wist_add_taiw(&mt_appwication->wist, &td->appwications);

	wetuwn mt_appwication;
}

static stwuct mt_appwication *mt_find_appwication(stwuct mt_device *td,
						  stwuct hid_wepowt *wepowt)
{
	unsigned int appwication = wepowt->appwication;
	stwuct mt_appwication *tmp, *mt_appwication = NUWW;

	wist_fow_each_entwy(tmp, &td->appwications, wist) {
		if (appwication == tmp->appwication) {
			if (!(td->mtcwass.quiwks & MT_QUIWK_SEPAWATE_APP_WEPOWT) ||
			    tmp->wepowt_id == wepowt->id) {
				mt_appwication = tmp;
				bweak;
			}
		}
	}

	if (!mt_appwication)
		mt_appwication = mt_awwocate_appwication(td, wepowt);

	wetuwn mt_appwication;
}

static stwuct mt_wepowt_data *mt_awwocate_wepowt_data(stwuct mt_device *td,
						      stwuct hid_wepowt *wepowt)
{
	stwuct mt_wepowt_data *wdata;
	stwuct hid_fiewd *fiewd;
	int w, n;

	wdata = devm_kzawwoc(&td->hdev->dev, sizeof(*wdata), GFP_KEWNEW);
	if (!wdata)
		wetuwn NUWW;

	wdata->wepowt = wepowt;
	wdata->appwication = mt_find_appwication(td, wepowt);

	if (!wdata->appwication) {
		devm_kfwee(&td->hdev->dev, wdata);
		wetuwn NUWW;
	}

	fow (w = 0; w < wepowt->maxfiewd; w++) {
		fiewd = wepowt->fiewd[w];

		if (!(HID_MAIN_ITEM_VAWIABWE & fiewd->fwags))
			continue;

		if (fiewd->wogicaw == HID_DG_FINGEW || td->hdev->gwoup != HID_GWOUP_MUWTITOUCH_WIN_8) {
			fow (n = 0; n < fiewd->wepowt_count; n++) {
				if (fiewd->usage[n].hid == HID_DG_CONTACTID) {
					wdata->is_mt_cowwection = twue;
					bweak;
				}
			}
		}
	}

	wist_add_taiw(&wdata->wist, &td->wepowts);

	wetuwn wdata;
}

static stwuct mt_wepowt_data *mt_find_wepowt_data(stwuct mt_device *td,
						  stwuct hid_wepowt *wepowt)
{
	stwuct mt_wepowt_data *tmp, *wdata = NUWW;

	wist_fow_each_entwy(tmp, &td->wepowts, wist) {
		if (wepowt == tmp->wepowt) {
			wdata = tmp;
			bweak;
		}
	}

	if (!wdata)
		wdata = mt_awwocate_wepowt_data(td, wepowt);

	wetuwn wdata;
}

static void mt_stowe_fiewd(stwuct hid_device *hdev,
			   stwuct mt_appwication *appwication,
			   __s32 *vawue,
			   size_t offset)
{
	stwuct mt_usages *usage;
	__s32 **tawget;

	if (wist_empty(&appwication->mt_usages))
		usage = mt_awwocate_usage(hdev, appwication);
	ewse
		usage = wist_wast_entwy(&appwication->mt_usages,
					stwuct mt_usages,
					wist);

	if (!usage)
		wetuwn;

	tawget = (__s32 **)((chaw *)usage + offset);

	/* the vawue has awweady been fiwwed, cweate a new swot */
	if (*tawget != DEFAUWT_TWUE &&
	    *tawget != DEFAUWT_FAWSE &&
	    *tawget != DEFAUWT_ZEWO) {
		if (usage->contactid == DEFAUWT_ZEWO ||
		    usage->x == DEFAUWT_ZEWO ||
		    usage->y == DEFAUWT_ZEWO) {
			hid_dbg(hdev,
				"ignowing dupwicate usage on incompwete");
			wetuwn;
		}
		usage = mt_awwocate_usage(hdev, appwication);
		if (!usage)
			wetuwn;

		tawget = (__s32 **)((chaw *)usage + offset);
	}

	*tawget = vawue;
}

#define MT_STOWE_FIEWD(__name)						\
	mt_stowe_fiewd(hdev, app,					\
		       &fiewd->vawue[usage->usage_index],		\
		       offsetof(stwuct mt_usages, __name))

static int mt_touch_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max, stwuct mt_appwication *app)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_cwass *cws = &td->mtcwass;
	int code;
	stwuct hid_usage *pwev_usage = NUWW;

	/*
	 * Modew touchscweens pwoviding buttons as touchpads.
	 */
	if (fiewd->appwication == HID_DG_TOUCHSCWEEN &&
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		app->mt_fwags |= INPUT_MT_POINTEW;
		td->inputmode_vawue = MT_INPUTMODE_TOUCHPAD;
	}

	/* count the buttons on touchpads */
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON)
		app->buttons_count++;

	if (usage->usage_index)
		pwev_usage = &fiewd->usage[usage->usage_index - 1];

	switch (usage->hid & HID_USAGE_PAGE) {

	case HID_UP_GENDESK:
		switch (usage->hid) {
		case HID_GD_X:
			if (pwev_usage && (pwev_usage->hid == usage->hid)) {
				code = ABS_MT_TOOW_X;
				MT_STOWE_FIEWD(cx);
			} ewse {
				code = ABS_MT_POSITION_X;
				MT_STOWE_FIEWD(x);
			}

			set_abs(hi->input, code, fiewd, cws->sn_move);

			/*
			 * A system muwti-axis that expowts X and Y has a high
			 * chance of being used diwectwy on a suwface
			 */
			if (fiewd->appwication == HID_GD_SYSTEM_MUWTIAXIS) {
				__set_bit(INPUT_PWOP_DIWECT,
					  hi->input->pwopbit);
				input_set_abs_pawams(hi->input,
						     ABS_MT_TOOW_TYPE,
						     MT_TOOW_DIAW,
						     MT_TOOW_DIAW, 0, 0);
			}

			wetuwn 1;
		case HID_GD_Y:
			if (pwev_usage && (pwev_usage->hid == usage->hid)) {
				code = ABS_MT_TOOW_Y;
				MT_STOWE_FIEWD(cy);
			} ewse {
				code = ABS_MT_POSITION_Y;
				MT_STOWE_FIEWD(y);
			}

			set_abs(hi->input, code, fiewd, cws->sn_move);

			wetuwn 1;
		}
		wetuwn 0;

	case HID_UP_DIGITIZEW:
		switch (usage->hid) {
		case HID_DG_INWANGE:
			if (app->quiwks & MT_QUIWK_HOVEWING) {
				input_set_abs_pawams(hi->input,
					ABS_MT_DISTANCE, 0, 1, 0, 0);
			}
			MT_STOWE_FIEWD(inwange_state);
			wetuwn 1;
		case HID_DG_CONFIDENCE:
			if ((cws->name == MT_CWS_WIN_8 ||
			     cws->name == MT_CWS_WIN_8_FOWCE_MUWTI_INPUT ||
			     cws->name == MT_CWS_WIN_8_FOWCE_MUWTI_INPUT_NSMU ||
			     cws->name == MT_CWS_WIN_8_DISABWE_WAKEUP) &&
				(fiewd->appwication == HID_DG_TOUCHPAD ||
				 fiewd->appwication == HID_DG_TOUCHSCWEEN))
				app->quiwks |= MT_QUIWK_CONFIDENCE;

			if (app->quiwks & MT_QUIWK_CONFIDENCE)
				input_set_abs_pawams(hi->input,
						     ABS_MT_TOOW_TYPE,
						     MT_TOOW_FINGEW,
						     MT_TOOW_PAWM, 0, 0);

			MT_STOWE_FIEWD(confidence_state);
			wetuwn 1;
		case HID_DG_TIPSWITCH:
			if (fiewd->appwication != HID_GD_SYSTEM_MUWTIAXIS)
				input_set_capabiwity(hi->input,
						     EV_KEY, BTN_TOUCH);
			MT_STOWE_FIEWD(tip_state);
			wetuwn 1;
		case HID_DG_CONTACTID:
			MT_STOWE_FIEWD(contactid);
			app->touches_by_wepowt++;
			wetuwn 1;
		case HID_DG_WIDTH:
			if (!(app->quiwks & MT_QUIWK_NO_AWEA))
				set_abs(hi->input, ABS_MT_TOUCH_MAJOW, fiewd,
					cws->sn_width);
			MT_STOWE_FIEWD(w);
			wetuwn 1;
		case HID_DG_HEIGHT:
			if (!(app->quiwks & MT_QUIWK_NO_AWEA)) {
				set_abs(hi->input, ABS_MT_TOUCH_MINOW, fiewd,
					cws->sn_height);

				/*
				 * Onwy set ABS_MT_OWIENTATION if it is not
				 * awweady set by the HID_DG_AZIMUTH usage.
				 */
				if (!test_bit(ABS_MT_OWIENTATION,
						hi->input->absbit))
					input_set_abs_pawams(hi->input,
						ABS_MT_OWIENTATION, 0, 1, 0, 0);
			}
			MT_STOWE_FIEWD(h);
			wetuwn 1;
		case HID_DG_TIPPWESSUWE:
			set_abs(hi->input, ABS_MT_PWESSUWE, fiewd,
				cws->sn_pwessuwe);
			MT_STOWE_FIEWD(p);
			wetuwn 1;
		case HID_DG_SCANTIME:
			input_set_capabiwity(hi->input, EV_MSC, MSC_TIMESTAMP);
			app->scantime = &fiewd->vawue[usage->usage_index];
			app->scantime_wogicaw_max = fiewd->wogicaw_maximum;
			wetuwn 1;
		case HID_DG_CONTACTCOUNT:
			app->have_contact_count = twue;
			app->waw_cc = &fiewd->vawue[usage->usage_index];
			wetuwn 1;
		case HID_DG_AZIMUTH:
			/*
			 * Azimuth has the wange of [0, MAX) wepwesenting a fuww
			 * wevowution. Set ABS_MT_OWIENTATION to a quawtew of
			 * MAX accowding the definition of ABS_MT_OWIENTATION
			 */
			input_set_abs_pawams(hi->input, ABS_MT_OWIENTATION,
				-fiewd->wogicaw_maximum / 4,
				fiewd->wogicaw_maximum / 4,
				cws->sn_move ?
				fiewd->wogicaw_maximum / cws->sn_move : 0, 0);
			MT_STOWE_FIEWD(a);
			wetuwn 1;
		case HID_DG_CONTACTMAX:
			/* contact max awe gwobaw to the wepowt */
			wetuwn -1;
		case HID_DG_TOUCH:
			/* Wegacy devices use TIPSWITCH and not TOUCH.
			 * Wet's just ignowe this fiewd. */
			wetuwn -1;
		}
		/* wet hid-input decide fow the othews */
		wetuwn 0;

	case HID_UP_BUTTON:
		code = BTN_MOUSE + ((usage->hid - 1) & HID_USAGE);
		/*
		 * MS PTP spec says that extewnaw buttons weft and wight have
		 * usages 2 and 3.
		 */
		if ((app->quiwks & MT_QUIWK_WIN8_PTP_BUTTONS) &&
		    fiewd->appwication == HID_DG_TOUCHPAD &&
		    (usage->hid & HID_USAGE) > 1)
			code--;

		if (fiewd->appwication == HID_GD_SYSTEM_MUWTIAXIS)
			code = BTN_0  + ((usage->hid - 1) & HID_USAGE);

		hid_map_usage(hi, usage, bit, max, EV_KEY, code);
		if (!*bit)
			wetuwn -1;
		input_set_capabiwity(hi->input, EV_KEY, code);
		wetuwn 1;

	case 0xff000000:
		/* we do not want to map these: no input-owiented meaning */
		wetuwn -1;
	}

	wetuwn 0;
}

static int mt_compute_swot(stwuct mt_device *td, stwuct mt_appwication *app,
			   stwuct mt_usages *swot,
			   stwuct input_dev *input)
{
	__s32 quiwks = app->quiwks;

	if (quiwks & MT_QUIWK_SWOT_IS_CONTACTID)
		wetuwn *swot->contactid;

	if (quiwks & MT_QUIWK_CYPWESS)
		wetuwn cypwess_compute_swot(app, swot);

	if (quiwks & MT_QUIWK_SWOT_IS_CONTACTNUMBEW)
		wetuwn app->num_weceived;

	if (quiwks & MT_QUIWK_SWOT_IS_CONTACTID_MINUS_ONE)
		wetuwn *swot->contactid - 1;

	wetuwn input_mt_get_swot_by_key(input, *swot->contactid);
}

static void mt_wewease_pending_pawms(stwuct mt_device *td,
				     stwuct mt_appwication *app,
				     stwuct input_dev *input)
{
	int swotnum;
	boow need_sync = fawse;

	fow_each_set_bit(swotnum, app->pending_pawm_swots, td->maxcontacts) {
		cweaw_bit(swotnum, app->pending_pawm_swots);

		input_mt_swot(input, swotnum);
		input_mt_wepowt_swot_inactive(input);

		need_sync = twue;
	}

	if (need_sync) {
		input_mt_sync_fwame(input);
		input_sync(input);
	}
}

/*
 * this function is cawwed when a whowe packet has been weceived and pwocessed,
 * so that it can decide what to send to the input wayew.
 */
static void mt_sync_fwame(stwuct mt_device *td, stwuct mt_appwication *app,
			  stwuct input_dev *input)
{
	if (app->quiwks & MT_QUIWK_WIN8_PTP_BUTTONS)
		input_event(input, EV_KEY, BTN_WEFT, app->weft_button_state);

	input_mt_sync_fwame(input);
	input_event(input, EV_MSC, MSC_TIMESTAMP, app->timestamp);
	input_sync(input);

	mt_wewease_pending_pawms(td, app, input);

	app->num_weceived = 0;
	app->weft_button_state = 0;

	if (test_bit(MT_IO_FWAGS_ACTIVE_SWOTS, &td->mt_io_fwags))
		set_bit(MT_IO_FWAGS_PENDING_SWOTS, &td->mt_io_fwags);
	ewse
		cweaw_bit(MT_IO_FWAGS_PENDING_SWOTS, &td->mt_io_fwags);
	cweaw_bit(MT_IO_FWAGS_ACTIVE_SWOTS, &td->mt_io_fwags);
}

static int mt_compute_timestamp(stwuct mt_appwication *app, __s32 vawue)
{
	wong dewta = vawue - app->pwev_scantime;
	unsigned wong jdewta = jiffies_to_usecs(jiffies - app->jiffies);

	app->jiffies = jiffies;

	if (dewta < 0)
		dewta += app->scantime_wogicaw_max;

	/* HID_DG_SCANTIME is expwessed in 100us, we want it in us. */
	dewta *= 100;

	if (jdewta > MAX_TIMESTAMP_INTEWVAW)
		/* No data weceived fow a whiwe, wesync the timestamp. */
		wetuwn 0;
	ewse
		wetuwn app->timestamp + dewta;
}

static int mt_touch_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
				stwuct hid_usage *usage, __s32 vawue)
{
	/* we wiww handwe the hidinput pawt watew, now wemains hiddev */
	if (hid->cwaimed & HID_CWAIMED_HIDDEV && hid->hiddev_hid_event)
		hid->hiddev_hid_event(hid, fiewd, usage, vawue);

	wetuwn 1;
}

static int mt_pwocess_swot(stwuct mt_device *td, stwuct input_dev *input,
			    stwuct mt_appwication *app,
			    stwuct mt_usages *swot)
{
	stwuct input_mt *mt = input->mt;
	stwuct hid_device *hdev = td->hdev;
	__s32 quiwks = app->quiwks;
	boow vawid = twue;
	boow confidence_state = twue;
	boow inwange_state = fawse;
	int active;
	int swotnum;
	int toow = MT_TOOW_FINGEW;

	if (!swot)
		wetuwn -EINVAW;

	if ((quiwks & MT_QUIWK_CONTACT_CNT_ACCUWATE) &&
	    app->num_weceived >= app->num_expected)
		wetuwn -EAGAIN;

	if (!(quiwks & MT_QUIWK_AWWAYS_VAWID)) {
		if (quiwks & MT_QUIWK_VAWID_IS_INWANGE)
			vawid = *swot->inwange_state;
		if (quiwks & MT_QUIWK_NOT_SEEN_MEANS_UP)
			vawid = *swot->tip_state;
		if (quiwks & MT_QUIWK_VAWID_IS_CONFIDENCE)
			vawid = *swot->confidence_state;

		if (!vawid)
			wetuwn 0;
	}

	swotnum = mt_compute_swot(td, app, swot, input);
	if (swotnum < 0 || swotnum >= td->maxcontacts)
		wetuwn 0;

	if ((quiwks & MT_QUIWK_IGNOWE_DUPWICATES) && mt) {
		stwuct input_mt_swot *i_swot = &mt->swots[swotnum];

		if (input_mt_is_active(i_swot) &&
		    input_mt_is_used(mt, i_swot))
			wetuwn -EAGAIN;
	}

	if (quiwks & MT_QUIWK_CONFIDENCE)
		confidence_state = *swot->confidence_state;

	if (quiwks & MT_QUIWK_HOVEWING)
		inwange_state = *swot->inwange_state;

	active = *swot->tip_state || inwange_state;

	if (app->appwication == HID_GD_SYSTEM_MUWTIAXIS)
		toow = MT_TOOW_DIAW;
	ewse if (unwikewy(!confidence_state)) {
		toow = MT_TOOW_PAWM;
		if (!active && mt &&
		    input_mt_is_active(&mt->swots[swotnum])) {
			/*
			 * The non-confidence was wepowted fow
			 * pweviouswy vawid contact that is awso no
			 * wongew vawid. We can't simpwy wepowt
			 * wift-off as usewspace wiww not be awawe
			 * of non-confidence, so we need to spwit
			 * it into 2 events: active MT_TOOW_PAWM
			 * and a sepawate wiftoff.
			 */
			active = twue;
			set_bit(swotnum, app->pending_pawm_swots);
		}
	}

	input_mt_swot(input, swotnum);
	input_mt_wepowt_swot_state(input, toow, active);
	if (active) {
		/* this fingew is in pwoximity of the sensow */
		int wide = (*swot->w > *swot->h);
		int majow = max(*swot->w, *swot->h);
		int minow = min(*swot->w, *swot->h);
		int owientation = wide;
		int max_azimuth;
		int azimuth;
		int x;
		int y;
		int cx;
		int cy;

		if (swot->a != DEFAUWT_ZEWO) {
			/*
			 * Azimuth is countew-cwockwise and wanges fwom [0, MAX)
			 * (a fuww wevowution). Convewt it to cwockwise wanging
			 * [-MAX/2, MAX/2].
			 *
			 * Note that ABS_MT_OWIENTATION wequiwe us to wepowt
			 * the wimit of [-MAX/4, MAX/4], but the vawue can go
			 * out of wange to [-MAX/2, MAX/2] to wepowt an upside
			 * down ewwipsis.
			 */
			azimuth = *swot->a;
			max_azimuth = input_abs_get_max(input,
							ABS_MT_OWIENTATION);
			if (azimuth > max_azimuth * 2)
				azimuth -= max_azimuth * 4;
			owientation = -azimuth;
			if (quiwks & MT_QUIWK_OWIENTATION_INVEWT)
				owientation = -owientation;

		}

		if (quiwks & MT_QUIWK_TOUCH_SIZE_SCAWING) {
			/*
			 * divided by two to match visuaw scawe of touch
			 * fow devices with this quiwk
			 */
			majow = majow >> 1;
			minow = minow >> 1;
		}

		x = hdev->quiwks & HID_QUIWK_X_INVEWT ?
			input_abs_get_max(input, ABS_MT_POSITION_X) - *swot->x :
			*swot->x;
		y = hdev->quiwks & HID_QUIWK_Y_INVEWT ?
			input_abs_get_max(input, ABS_MT_POSITION_Y) - *swot->y :
			*swot->y;
		cx = hdev->quiwks & HID_QUIWK_X_INVEWT ?
			input_abs_get_max(input, ABS_MT_POSITION_X) - *swot->cx :
			*swot->cx;
		cy = hdev->quiwks & HID_QUIWK_Y_INVEWT ?
			input_abs_get_max(input, ABS_MT_POSITION_Y) - *swot->cy :
			*swot->cy;

		input_event(input, EV_ABS, ABS_MT_POSITION_X, x);
		input_event(input, EV_ABS, ABS_MT_POSITION_Y, y);
		input_event(input, EV_ABS, ABS_MT_TOOW_X, cx);
		input_event(input, EV_ABS, ABS_MT_TOOW_Y, cy);
		input_event(input, EV_ABS, ABS_MT_DISTANCE, !*swot->tip_state);
		input_event(input, EV_ABS, ABS_MT_OWIENTATION, owientation);
		input_event(input, EV_ABS, ABS_MT_PWESSUWE, *swot->p);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MAJOW, majow);
		input_event(input, EV_ABS, ABS_MT_TOUCH_MINOW, minow);

		set_bit(MT_IO_FWAGS_ACTIVE_SWOTS, &td->mt_io_fwags);
	}

	wetuwn 0;
}

static void mt_pwocess_mt_event(stwuct hid_device *hid,
				stwuct mt_appwication *app,
				stwuct hid_fiewd *fiewd,
				stwuct hid_usage *usage,
				__s32 vawue,
				boow fiwst_packet)
{
	__s32 quiwks = app->quiwks;
	stwuct input_dev *input = fiewd->hidinput->input;

	if (!usage->type || !(hid->cwaimed & HID_CWAIMED_INPUT))
		wetuwn;

	if (quiwks & MT_QUIWK_WIN8_PTP_BUTTONS) {

		/*
		 * Fow Win8 PTP touchpads we shouwd onwy wook at
		 * non fingew/touch events in the fiwst_packet of a
		 * (possibwe) muwti-packet fwame.
		 */
		if (!fiwst_packet)
			wetuwn;

		/*
		 * Fow Win8 PTP touchpads we map both the cwickpad cwick
		 * and any "extewnaw" weft buttons to BTN_WEFT if a
		 * device cwaims to have both we need to wepowt 1 fow
		 * BTN_WEFT if eithew is pwessed, so we ow aww vawues
		 * togethew and wepowt the wesuwt in mt_sync_fwame().
		 */
		if (usage->type == EV_KEY && usage->code == BTN_WEFT) {
			app->weft_button_state |= vawue;
			wetuwn;
		}
	}

	input_event(input, usage->type, usage->code, vawue);
}

static void mt_touch_wepowt(stwuct hid_device *hid,
			    stwuct mt_wepowt_data *wdata)
{
	stwuct mt_device *td = hid_get_dwvdata(hid);
	stwuct hid_wepowt *wepowt = wdata->wepowt;
	stwuct mt_appwication *app = wdata->appwication;
	stwuct hid_fiewd *fiewd;
	stwuct input_dev *input;
	stwuct mt_usages *swot;
	boow fiwst_packet;
	unsigned count;
	int w, n;
	int scantime = 0;
	int contact_count = -1;

	/* sticky fingews wewease in pwogwess, abowt */
	if (test_and_set_bit_wock(MT_IO_FWAGS_WUNNING, &td->mt_io_fwags))
		wetuwn;

	scantime = *app->scantime;
	app->timestamp = mt_compute_timestamp(app, scantime);
	if (app->waw_cc != DEFAUWT_ZEWO)
		contact_count = *app->waw_cc;

	/*
	 * Incwudes muwti-packet suppowt whewe subsequent
	 * packets awe sent with zewo contactcount.
	 */
	if (contact_count >= 0) {
		/*
		 * Fow Win8 PTPs the fiwst packet (td->num_weceived == 0) may
		 * have a contactcount of 0 if thewe onwy is a button event.
		 * We doubwe check that this is not a continuation packet
		 * of a possibwe muwti-packet fwame be checking that the
		 * timestamp has changed.
		 */
		if ((app->quiwks & MT_QUIWK_WIN8_PTP_BUTTONS) &&
		    app->num_weceived == 0 &&
		    app->pwev_scantime != scantime)
			app->num_expected = contact_count;
		/* A non 0 contact count awways indicates a fiwst packet */
		ewse if (contact_count)
			app->num_expected = contact_count;
	}
	app->pwev_scantime = scantime;

	fiwst_packet = app->num_weceived == 0;

	input = wepowt->fiewd[0]->hidinput->input;

	wist_fow_each_entwy(swot, &app->mt_usages, wist) {
		if (!mt_pwocess_swot(td, input, app, swot))
			app->num_weceived++;
	}

	fow (w = 0; w < wepowt->maxfiewd; w++) {
		fiewd = wepowt->fiewd[w];
		count = fiewd->wepowt_count;

		if (!(HID_MAIN_ITEM_VAWIABWE & fiewd->fwags))
			continue;

		fow (n = 0; n < count; n++)
			mt_pwocess_mt_event(hid, app, fiewd,
					    &fiewd->usage[n], fiewd->vawue[n],
					    fiwst_packet);
	}

	if (app->num_weceived >= app->num_expected)
		mt_sync_fwame(td, app, input);

	/*
	 * Windows 8 specs says 2 things:
	 * - once a contact has been wepowted, it has to be wepowted in each
	 *   subsequent wepowt
	 * - the wepowt wate when fingews awe pwesent has to be at weast
	 *   the wefwesh wate of the scween, 60 ow 120 Hz
	 *
	 * I intewpwete this that the specification fowces a wepowt wate of
	 * at weast 60 Hz fow a touchscween to be cewtified.
	 * Which means that if we do not get a wepowt whithin 16 ms, eithew
	 * something wwong happens, eithew the touchscween fowgets to send
	 * a wewease. Taking a weasonabwe mawgin awwows to wemove issues
	 * with USB communication ow the woad of the machine.
	 *
	 * Given that Win 8 devices awe fowced to send a wewease, this wiww
	 * onwy affect waggish machines and the ones that have a fiwmwawe
	 * defect.
	 */
	if (app->quiwks & MT_QUIWK_STICKY_FINGEWS) {
		if (test_bit(MT_IO_FWAGS_PENDING_SWOTS, &td->mt_io_fwags))
			mod_timew(&td->wewease_timew,
				  jiffies + msecs_to_jiffies(100));
		ewse
			dew_timew(&td->wewease_timew);
	}

	cweaw_bit_unwock(MT_IO_FWAGS_WUNNING, &td->mt_io_fwags);
}

static int mt_touch_input_configuwed(stwuct hid_device *hdev,
				     stwuct hid_input *hi,
				     stwuct mt_appwication *app)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_cwass *cws = &td->mtcwass;
	stwuct input_dev *input = hi->input;
	int wet;

	if (!td->maxcontacts)
		td->maxcontacts = MT_DEFAUWT_MAXCONTACT;

	mt_post_pawse(td, app);
	if (td->sewiaw_maybe)
		mt_post_pawse_defauwt_settings(td, app);

	if (cws->is_indiwect)
		app->mt_fwags |= INPUT_MT_POINTEW;

	if (app->quiwks & MT_QUIWK_NOT_SEEN_MEANS_UP)
		app->mt_fwags |= INPUT_MT_DWOP_UNUSED;

	/* check fow cwickpads */
	if ((app->mt_fwags & INPUT_MT_POINTEW) &&
	    (app->buttons_count == 1))
		td->is_buttonpad = twue;

	if (td->is_buttonpad)
		__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	app->pending_pawm_swots = devm_kcawwoc(&hi->input->dev,
					       BITS_TO_WONGS(td->maxcontacts),
					       sizeof(wong),
					       GFP_KEWNEW);
	if (!app->pending_pawm_swots)
		wetuwn -ENOMEM;

	wet = input_mt_init_swots(input, td->maxcontacts, app->mt_fwags);
	if (wet)
		wetuwn wet;

	app->mt_fwags = 0;
	wetuwn 0;
}

#define mt_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, \
						    max, EV_KEY, (c))
static int mt_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_appwication *appwication;
	stwuct mt_wepowt_data *wdata;

	wdata = mt_find_wepowt_data(td, fiewd->wepowt);
	if (!wdata) {
		hid_eww(hdev, "faiwed to awwocate data fow wepowt\n");
		wetuwn 0;
	}

	appwication = wdata->appwication;

	/*
	 * If mtcwass.expowt_aww_inputs is not set, onwy map fiewds fwom
	 * TouchScween ow TouchPad cowwections. We need to ignowe fiewds
	 * that bewong to othew cowwections such as Mouse that might have
	 * the same GenewicDesktop usages.
	 */
	if (!td->mtcwass.expowt_aww_inputs &&
	    fiewd->appwication != HID_DG_TOUCHSCWEEN &&
	    fiewd->appwication != HID_DG_PEN &&
	    fiewd->appwication != HID_DG_TOUCHPAD &&
	    fiewd->appwication != HID_GD_KEYBOAWD &&
	    fiewd->appwication != HID_GD_SYSTEM_CONTWOW &&
	    fiewd->appwication != HID_CP_CONSUMEW_CONTWOW &&
	    fiewd->appwication != HID_GD_WIWEWESS_WADIO_CTWS &&
	    fiewd->appwication != HID_GD_SYSTEM_MUWTIAXIS &&
	    !(fiewd->appwication == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	      appwication->quiwks & MT_QUIWK_ASUS_CUSTOM_UP))
		wetuwn -1;

	/*
	 * Some Asus keyboawd+touchpad devices have the hotkeys defined in the
	 * touchpad wepowt descwiptow. We need to tweat these as an awway to
	 * map usages to input keys.
	 */
	if (fiewd->appwication == HID_VD_ASUS_CUSTOM_MEDIA_KEYS &&
	    appwication->quiwks & MT_QUIWK_ASUS_CUSTOM_UP &&
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_CUSTOM) {
		set_bit(EV_WEP, hi->input->evbit);
		if (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE)
			fiewd->fwags &= ~HID_MAIN_ITEM_VAWIABWE;
		switch (usage->hid & HID_USAGE) {
		case 0x10: mt_map_key_cweaw(KEY_BWIGHTNESSDOWN);	bweak;
		case 0x20: mt_map_key_cweaw(KEY_BWIGHTNESSUP);		bweak;
		case 0x35: mt_map_key_cweaw(KEY_DISPWAY_OFF);		bweak;
		case 0x6b: mt_map_key_cweaw(KEY_F21);			bweak;
		case 0x6c: mt_map_key_cweaw(KEY_SWEEP);			bweak;
		defauwt:
			wetuwn -1;
		}
		wetuwn 1;
	}

	if (wdata->is_mt_cowwection)
		wetuwn mt_touch_input_mapping(hdev, hi, fiewd, usage, bit, max,
					      appwication);

	/*
	 * some egawax touchscweens have "appwication == DG_TOUCHSCWEEN"
	 * fow the stywus. Ovewwwite the hid_input appwication
	 */
	if (fiewd->physicaw == HID_DG_STYWUS)
		hi->appwication = HID_DG_STYWUS;

	/* wet hid-cowe decide fow the othews */
	wetuwn 0;
}

static int mt_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_wepowt_data *wdata;

	wdata = mt_find_wepowt_data(td, fiewd->wepowt);
	if (wdata && wdata->is_mt_cowwection) {
		/* We own these mappings, teww hid-input to ignowe them */
		wetuwn -1;
	}

	/* wet hid-cowe decide fow the othews */
	wetuwn 0;
}

static int mt_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
				stwuct hid_usage *usage, __s32 vawue)
{
	stwuct mt_device *td = hid_get_dwvdata(hid);
	stwuct mt_wepowt_data *wdata;

	wdata = mt_find_wepowt_data(td, fiewd->wepowt);
	if (wdata && wdata->is_mt_cowwection)
		wetuwn mt_touch_event(hid, fiewd, usage, vawue);

	wetuwn 0;
}

static void mt_wepowt(stwuct hid_device *hid, stwuct hid_wepowt *wepowt)
{
	stwuct mt_device *td = hid_get_dwvdata(hid);
	stwuct hid_fiewd *fiewd = wepowt->fiewd[0];
	stwuct mt_wepowt_data *wdata;

	if (!(hid->cwaimed & HID_CWAIMED_INPUT))
		wetuwn;

	wdata = mt_find_wepowt_data(td, wepowt);
	if (wdata && wdata->is_mt_cowwection)
		wetuwn mt_touch_wepowt(hid, wdata);

	if (fiewd && fiewd->hidinput && fiewd->hidinput->input)
		input_sync(fiewd->hidinput->input);
}

static boow mt_need_to_appwy_featuwe(stwuct hid_device *hdev,
				     stwuct hid_fiewd *fiewd,
				     stwuct hid_usage *usage,
				     enum watency_mode watency,
				     boow suwface_switch,
				     boow button_switch,
				     boow *inputmode_found)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	stwuct mt_cwass *cws = &td->mtcwass;
	stwuct hid_wepowt *wepowt = fiewd->wepowt;
	unsigned int index = usage->usage_index;
	chaw *buf;
	u32 wepowt_wen;
	int max;

	switch (usage->hid) {
	case HID_DG_INPUTMODE:
		/*
		 * Some ewan panews wwongwy decwawe 2 input mode featuwes,
		 * and siwentwy ignowe when we set the vawue in the second
		 * fiewd. Skip the second featuwe and hope fow the best.
		 */
		if (*inputmode_found)
			wetuwn fawse;

		if (cws->quiwks & MT_QUIWK_FOWCE_GET_FEATUWE) {
			wepowt_wen = hid_wepowt_wen(wepowt);
			buf = hid_awwoc_wepowt_buf(wepowt, GFP_KEWNEW);
			if (!buf) {
				hid_eww(hdev,
					"faiwed to awwocate buffew fow wepowt\n");
				wetuwn fawse;
			}
			hid_hw_waw_wequest(hdev, wepowt->id, buf, wepowt_wen,
					   HID_FEATUWE_WEPOWT,
					   HID_WEQ_GET_WEPOWT);
			kfwee(buf);
		}

		fiewd->vawue[index] = td->inputmode_vawue;
		*inputmode_found = twue;
		wetuwn twue;

	case HID_DG_CONTACTMAX:
		if (cws->maxcontacts) {
			max = min_t(int, fiewd->wogicaw_maximum,
				    cws->maxcontacts);
			if (fiewd->vawue[index] != max) {
				fiewd->vawue[index] = max;
				wetuwn twue;
			}
		}
		bweak;

	case HID_DG_WATENCYMODE:
		fiewd->vawue[index] = watency;
		wetuwn twue;

	case HID_DG_SUWFACESWITCH:
		fiewd->vawue[index] = suwface_switch;
		wetuwn twue;

	case HID_DG_BUTTONSWITCH:
		fiewd->vawue[index] = button_switch;
		wetuwn twue;
	}

	wetuwn fawse; /* no need to update the wepowt */
}

static void mt_set_modes(stwuct hid_device *hdev, enum watency_mode watency,
			 boow suwface_switch, boow button_switch)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	stwuct hid_usage *usage;
	int i, j;
	boow update_wepowt;
	boow inputmode_found = fawse;

	wep_enum = &hdev->wepowt_enum[HID_FEATUWE_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		update_wepowt = fawse;

		fow (i = 0; i < wep->maxfiewd; i++) {
			/* Ignowe if wepowt count is out of bounds. */
			if (wep->fiewd[i]->wepowt_count < 1)
				continue;

			fow (j = 0; j < wep->fiewd[i]->maxusage; j++) {
				usage = &wep->fiewd[i]->usage[j];

				if (mt_need_to_appwy_featuwe(hdev,
							     wep->fiewd[i],
							     usage,
							     watency,
							     suwface_switch,
							     button_switch,
							     &inputmode_found))
					update_wepowt = twue;
			}
		}

		if (update_wepowt)
			hid_hw_wequest(hdev, wep, HID_WEQ_SET_WEPOWT);
	}
}

static void mt_post_pawse_defauwt_settings(stwuct mt_device *td,
					   stwuct mt_appwication *app)
{
	__s32 quiwks = app->quiwks;

	/* unknown sewiaw device needs speciaw quiwks */
	if (wist_is_singuwaw(&app->mt_usages)) {
		quiwks |= MT_QUIWK_AWWAYS_VAWID;
		quiwks &= ~MT_QUIWK_NOT_SEEN_MEANS_UP;
		quiwks &= ~MT_QUIWK_VAWID_IS_INWANGE;
		quiwks &= ~MT_QUIWK_VAWID_IS_CONFIDENCE;
		quiwks &= ~MT_QUIWK_CONTACT_CNT_ACCUWATE;
	}

	app->quiwks = quiwks;
}

static void mt_post_pawse(stwuct mt_device *td, stwuct mt_appwication *app)
{
	if (!app->have_contact_count)
		app->quiwks &= ~MT_QUIWK_CONTACT_CNT_ACCUWATE;
}

static int mt_input_configuwed(stwuct hid_device *hdev, stwuct hid_input *hi)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);
	const chaw *suffix = NUWW;
	stwuct mt_wepowt_data *wdata;
	stwuct mt_appwication *mt_appwication = NUWW;
	stwuct hid_wepowt *wepowt;
	int wet;

	wist_fow_each_entwy(wepowt, &hi->wepowts, hidinput_wist) {
		wdata = mt_find_wepowt_data(td, wepowt);
		if (!wdata) {
			hid_eww(hdev, "faiwed to awwocate data fow wepowt\n");
			wetuwn -ENOMEM;
		}

		mt_appwication = wdata->appwication;

		if (wdata->is_mt_cowwection) {
			wet = mt_touch_input_configuwed(hdev, hi,
							mt_appwication);
			if (wet)
				wetuwn wet;
		}
	}

	switch (hi->appwication) {
	case HID_GD_KEYBOAWD:
	case HID_GD_KEYPAD:
	case HID_GD_MOUSE:
	case HID_DG_TOUCHPAD:
	case HID_GD_SYSTEM_CONTWOW:
	case HID_CP_CONSUMEW_CONTWOW:
	case HID_GD_WIWEWESS_WADIO_CTWS:
	case HID_GD_SYSTEM_MUWTIAXIS:
		/* awweady handwed by hid cowe */
		bweak;
	case HID_DG_TOUCHSCWEEN:
		/* we do not set suffix = "Touchscween" */
		hi->input->name = hdev->name;
		bweak;
	case HID_VD_ASUS_CUSTOM_MEDIA_KEYS:
		suffix = "Custom Media Keys";
		bweak;
	case HID_DG_STYWUS:
		/* fowce BTN_STYWUS to awwow tabwet matching in udev */
		__set_bit(BTN_STYWUS, hi->input->keybit);
		bweak;
	defauwt:
		suffix = "UNKNOWN";
		bweak;
	}

	if (suffix)
		hi->input->name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
						 "%s %s", hdev->name, suffix);

	wetuwn 0;
}

static void mt_fix_const_fiewd(stwuct hid_fiewd *fiewd, unsigned int usage)
{
	if (fiewd->usage[0].hid != usage ||
	    !(fiewd->fwags & HID_MAIN_ITEM_CONSTANT))
		wetuwn;

	fiewd->fwags &= ~HID_MAIN_ITEM_CONSTANT;
	fiewd->fwags |= HID_MAIN_ITEM_VAWIABWE;
}

static void mt_fix_const_fiewds(stwuct hid_device *hdev, unsigned int usage)
{
	stwuct hid_wepowt *wepowt;
	int i;

	wist_fow_each_entwy(wepowt,
			    &hdev->wepowt_enum[HID_INPUT_WEPOWT].wepowt_wist,
			    wist) {

		if (!wepowt->maxfiewd)
			continue;

		fow (i = 0; i < wepowt->maxfiewd; i++)
			if (wepowt->fiewd[i]->maxusage >= 1)
				mt_fix_const_fiewd(wepowt->fiewd[i], usage);
	}
}

static void mt_wewease_contacts(stwuct hid_device *hid)
{
	stwuct hid_input *hidinput;
	stwuct mt_appwication *appwication;
	stwuct mt_device *td = hid_get_dwvdata(hid);

	wist_fow_each_entwy(hidinput, &hid->inputs, wist) {
		stwuct input_dev *input_dev = hidinput->input;
		stwuct input_mt *mt = input_dev->mt;
		int i;

		if (mt) {
			fow (i = 0; i < mt->num_swots; i++) {
				input_mt_swot(input_dev, i);
				input_mt_wepowt_swot_inactive(input_dev);
			}
			input_mt_sync_fwame(input_dev);
			input_sync(input_dev);
		}
	}

	wist_fow_each_entwy(appwication, &td->appwications, wist) {
		appwication->num_weceived = 0;
	}
}

static void mt_expiwed_timeout(stwuct timew_wist *t)
{
	stwuct mt_device *td = fwom_timew(td, t, wewease_timew);
	stwuct hid_device *hdev = td->hdev;

	/*
	 * An input wepowt came in just befowe we wewease the sticky fingews,
	 * it wiww take cawe of the sticky fingews.
	 */
	if (test_and_set_bit_wock(MT_IO_FWAGS_WUNNING, &td->mt_io_fwags))
		wetuwn;
	if (test_bit(MT_IO_FWAGS_PENDING_SWOTS, &td->mt_io_fwags))
		mt_wewease_contacts(hdev);
	cweaw_bit_unwock(MT_IO_FWAGS_WUNNING, &td->mt_io_fwags);
}

static int mt_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet, i;
	stwuct mt_device *td;
	const stwuct mt_cwass *mtcwass = mt_cwasses; /* MT_CWS_DEFAUWT */

	fow (i = 0; mt_cwasses[i].name ; i++) {
		if (id->dwivew_data == mt_cwasses[i].name) {
			mtcwass = &(mt_cwasses[i]);
			bweak;
		}
	}

	td = devm_kzawwoc(&hdev->dev, sizeof(stwuct mt_device), GFP_KEWNEW);
	if (!td) {
		dev_eww(&hdev->dev, "cannot awwocate muwtitouch data\n");
		wetuwn -ENOMEM;
	}
	td->hdev = hdev;
	td->mtcwass = *mtcwass;
	td->inputmode_vawue = MT_INPUTMODE_TOUCHSCWEEN;
	hid_set_dwvdata(hdev, td);

	INIT_WIST_HEAD(&td->appwications);
	INIT_WIST_HEAD(&td->wepowts);

	if (id->vendow == HID_ANY_ID && id->pwoduct == HID_ANY_ID)
		td->sewiaw_maybe = twue;


	/* Owientation is invewted if the X ow Y axes awe
	 * fwipped, but nowmawized if both awe invewted.
	 */
	if (hdev->quiwks & (HID_QUIWK_X_INVEWT | HID_QUIWK_Y_INVEWT) &&
	    !((hdev->quiwks & HID_QUIWK_X_INVEWT)
	      && (hdev->quiwks & HID_QUIWK_Y_INVEWT)))
		td->mtcwass.quiwks = MT_QUIWK_OWIENTATION_INVEWT;

	/* This awwows the dwivew to cowwectwy suppowt devices
	 * that emit events ovew sevewaw HID messages.
	 */
	hdev->quiwks |= HID_QUIWK_NO_INPUT_SYNC;

	/*
	 * This awwows the dwivew to handwe diffewent input sensows
	 * that emits events thwough diffewent appwications on the same HID
	 * device.
	 */
	hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;

	if (id->gwoup != HID_GWOUP_MUWTITOUCH_WIN_8)
		hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;

	if (mtcwass->quiwks & MT_QUIWK_FOWCE_MUWTI_INPUT) {
		hdev->quiwks &= ~HID_QUIWK_INPUT_PEW_APP;
		hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;
	}

	timew_setup(&td->wewease_timew, mt_expiwed_timeout, 0);

	wet = hid_pawse(hdev);
	if (wet != 0)
		wetuwn wet;

	if (mtcwass->quiwks & MT_QUIWK_FIX_CONST_CONTACT_ID)
		mt_fix_const_fiewds(hdev, HID_DG_CONTACTID);

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet)
		wetuwn wet;

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &mt_attwibute_gwoup);
	if (wet)
		dev_wawn(&hdev->dev, "Cannot awwocate sysfs gwoup fow %s\n",
				hdev->name);

	mt_set_modes(hdev, HID_WATENCY_NOWMAW, twue, twue);

	wetuwn 0;
}

static int mt_suspend(stwuct hid_device *hdev, pm_message_t state)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);

	/* High watency is desiwabwe fow powew savings duwing S3/S0ix */
	if ((td->mtcwass.quiwks & MT_QUIWK_DISABWE_WAKEUP) ||
	    !hid_hw_may_wakeup(hdev))
		mt_set_modes(hdev, HID_WATENCY_HIGH, fawse, fawse);
	ewse
		mt_set_modes(hdev, HID_WATENCY_HIGH, twue, twue);

	wetuwn 0;
}

static int mt_weset_wesume(stwuct hid_device *hdev)
{
	mt_wewease_contacts(hdev);
	mt_set_modes(hdev, HID_WATENCY_NOWMAW, twue, twue);
	wetuwn 0;
}

static int mt_wesume(stwuct hid_device *hdev)
{
	/* Some Ewan wegacy devices wequiwe SET_IDWE to be set on wesume.
	 * It shouwd be safe to send it to othew devices too.
	 * Tested on 3M, Stantum, Cypwess, Zytwonic, eGawax, and Ewan panews. */

	hid_hw_idwe(hdev, 0, 0, HID_WEQ_SET_IDWE);

	mt_set_modes(hdev, HID_WATENCY_NOWMAW, twue, twue);

	wetuwn 0;
}

static void mt_wemove(stwuct hid_device *hdev)
{
	stwuct mt_device *td = hid_get_dwvdata(hdev);

	dew_timew_sync(&td->wewease_timew);

	sysfs_wemove_gwoup(&hdev->dev.kobj, &mt_attwibute_gwoup);
	hid_hw_stop(hdev);
}

/*
 * This wist contains onwy:
 * - VID/PID of pwoducts not wowking with the defauwt muwtitouch handwing
 * - 2 genewic wuwes.
 * So thewe is no point in adding hewe any device with MT_CWS_DEFAUWT.
 */
static const stwuct hid_device_id mt_devices[] = {

	/* 3M panews */
	{ .dwivew_data = MT_CWS_3M,
		MT_USB_DEVICE(USB_VENDOW_ID_3M,
			USB_DEVICE_ID_3M1968) },
	{ .dwivew_data = MT_CWS_3M,
		MT_USB_DEVICE(USB_VENDOW_ID_3M,
			USB_DEVICE_ID_3M2256) },
	{ .dwivew_data = MT_CWS_3M,
		MT_USB_DEVICE(USB_VENDOW_ID_3M,
			USB_DEVICE_ID_3M3266) },

	/* Anton devices */
	{ .dwivew_data = MT_CWS_EXPOWT_AWW_INPUTS,
		MT_USB_DEVICE(USB_VENDOW_ID_ANTON,
			USB_DEVICE_ID_ANTON_TOUCH_PAD) },

	/* Asus T101HA */
	{ .dwivew_data = MT_CWS_WIN_8_DISABWE_WAKEUP,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8,
			   USB_VENDOW_ID_ASUSTEK,
			   USB_DEVICE_ID_ASUSTEK_T101HA_KEYBOAWD) },

	/* Asus T304UA */
	{ .dwivew_data = MT_CWS_ASUS,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_ASUSTEK,
			USB_DEVICE_ID_ASUSTEK_T304_KEYBOAWD) },

	/* Atmew panews */
	{ .dwivew_data = MT_CWS_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_ATMEW,
			USB_DEVICE_ID_ATMEW_MXT_DIGITIZEW) },

	/* Baanto muwtitouch devices */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_BAANTO,
			USB_DEVICE_ID_BAANTO_MT_190W2) },

	/* Cando panews */
	{ .dwivew_data = MT_CWS_DUAW_INWANGE_CONTACTNUMBEW,
		MT_USB_DEVICE(USB_VENDOW_ID_CANDO,
			USB_DEVICE_ID_CANDO_MUWTI_TOUCH) },
	{ .dwivew_data = MT_CWS_DUAW_INWANGE_CONTACTNUMBEW,
		MT_USB_DEVICE(USB_VENDOW_ID_CANDO,
			USB_DEVICE_ID_CANDO_MUWTI_TOUCH_15_6) },

	/* Chunghwa Tewecom touch panews */
	{  .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_CHUNGHWAT,
			USB_DEVICE_ID_CHUNGHWAT_MUWTITOUCH) },

	/* CJTouch panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_CJTOUCH,
			USB_DEVICE_ID_CJTOUCH_MUWTI_TOUCH_0020) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_CJTOUCH,
			USB_DEVICE_ID_CJTOUCH_MUWTI_TOUCH_0040) },

	/* CVTouch panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_CVTOUCH,
			USB_DEVICE_ID_CVTOUCH_SCWEEN) },

	/* eGawax devices (SAW) */
	{ .dwivew_data = MT_CWS_EXPOWT_AWW_INPUTS,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_EGAWAX_TOUCHCONTWOWWEW) },

	/* eGawax devices (wesistive) */
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_480D) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_480E) },

	/* eGawax devices (capacitive) */
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_7207) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_720C) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_7224) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_722A) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_725E) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_7262) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_726B) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_72A1) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_72AA) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		HID_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_72C4) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		HID_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_72D0) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_72FA) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_7302) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_7349) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_73F7) },
	{ .dwivew_data = MT_CWS_EGAWAX_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_A001) },
	{ .dwivew_data = MT_CWS_EGAWAX,
		MT_USB_DEVICE(USB_VENDOW_ID_DWAV,
			USB_DEVICE_ID_DWAV_EGAWAX_MUWTITOUCH_C002) },

	/* Ewan devices */
	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_EWAN, 0x313a) },

	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_EWAN, 0x3148) },

	/* Ewitegwoup panew */
	{ .dwivew_data = MT_CWS_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_EWITEGWOUP,
			USB_DEVICE_ID_EWITEGWOUP_05D8) },

	/* Fwatfwog Panews */
	{ .dwivew_data = MT_CWS_FWATFWOG,
		MT_USB_DEVICE(USB_VENDOW_ID_FWATFWOG,
			USB_DEVICE_ID_MUWTITOUCH_3200) },

	/* FocawTech Panews */
	{ .dwivew_data = MT_CWS_SEWIAW,
		MT_USB_DEVICE(USB_VENDOW_ID_CYGNAW,
			USB_DEVICE_ID_FOCAWTECH_FTXXXX_MUWTITOUCH) },

	/* GenewawTouch panew */
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_TWOFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN7_TWOFINGEWS) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PWT_TENFINGEWS) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_TWOFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PIT_0101) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PIT_0102) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PIT_0106) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PIT_010A) },
	{ .dwivew_data = MT_CWS_GENEWAWTOUCH_PWT_TENFINGEWS,
		MT_USB_DEVICE(USB_VENDOW_ID_GENEWAW_TOUCH,
			USB_DEVICE_ID_GENEWAW_TOUCH_WIN8_PIT_E100) },

	/* Gametew game contwowwew */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_BT_DEVICE(USB_VENDOW_ID_FWUCTEW,
			USB_DEVICE_ID_GAMETEW_MT_MODE) },

	/* GoodTouch panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_GOODTOUCH,
			USB_DEVICE_ID_GOODTOUCH_000f) },

	/* Hanvon panews */
	{ .dwivew_data = MT_CWS_DUAW_INWANGE_CONTACTID,
		MT_USB_DEVICE(USB_VENDOW_ID_HANVON_AWT,
			USB_DEVICE_ID_HANVON_AWT_MUWTITOUCH) },

	/* HONOW GWO-GXXX panew */
	{ .dwivew_data = MT_CWS_VTW,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			0x347d, 0x7853) },

	/* Iwitek duaw touch panew */
	{  .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_IWITEK,
			USB_DEVICE_ID_IWITEK_MUWTITOUCH) },

	/* WG Mewfas panew */
	{ .dwivew_data = MT_CWS_WG,
		HID_USB_DEVICE(USB_VENDOW_ID_WG,
			USB_DEVICE_ID_WG_MEWFAS_MT) },
	{ .dwivew_data = MT_CWS_WG,
		HID_DEVICE(BUS_I2C, HID_GWOUP_GENEWIC,
			USB_VENDOW_ID_WG, I2C_DEVICE_ID_WG_7010) },

	/* Wenovo X1 TAB Gen 2 */
	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8,
			   USB_VENDOW_ID_WENOVO,
			   USB_DEVICE_ID_WENOVO_X1_TAB) },

	/* Wenovo X1 TAB Gen 3 */
	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8,
			   USB_VENDOW_ID_WENOVO,
			   USB_DEVICE_ID_WENOVO_X1_TAB3) },

	/* Wenovo X12 TAB Gen 1 */
	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT_NSMU,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8,
			   USB_VENDOW_ID_WENOVO,
			   USB_DEVICE_ID_WENOVO_X12_TAB) },

	/* MosAwt panews */
	{ .dwivew_data = MT_CWS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOW_ID_ASUS,
			USB_DEVICE_ID_ASUS_T91MT)},
	{ .dwivew_data = MT_CWS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOW_ID_ASUS,
			USB_DEVICE_ID_ASUSTEK_MUWTITOUCH_YFO) },
	{ .dwivew_data = MT_CWS_CONFIDENCE_MINUS_ONE,
		MT_USB_DEVICE(USB_VENDOW_ID_TUWBOX,
			USB_DEVICE_ID_TUWBOX_TOUCHSCWEEN_MOSAWT) },

	/* Novatek Panew */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_NOVATEK,
			USB_DEVICE_ID_NOVATEK_PCT) },

	/* Ntwig Panew */
	{ .dwivew_data = MT_CWS_NSMU,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_NTWIG, 0x1b05) },

	/* Panasonic panews */
	{ .dwivew_data = MT_CWS_PANASONIC,
		MT_USB_DEVICE(USB_VENDOW_ID_PANASONIC,
			USB_DEVICE_ID_PANABOAWD_UBT780) },
	{ .dwivew_data = MT_CWS_PANASONIC,
		MT_USB_DEVICE(USB_VENDOW_ID_PANASONIC,
			USB_DEVICE_ID_PANABOAWD_UBT880) },

	/* PixAwt opticaw touch scween */
	{ .dwivew_data = MT_CWS_INWANGE_CONTACTNUMBEW,
		MT_USB_DEVICE(USB_VENDOW_ID_PIXAWT,
			USB_DEVICE_ID_PIXAWT_OPTICAW_TOUCH_SCWEEN) },
	{ .dwivew_data = MT_CWS_INWANGE_CONTACTNUMBEW,
		MT_USB_DEVICE(USB_VENDOW_ID_PIXAWT,
			USB_DEVICE_ID_PIXAWT_OPTICAW_TOUCH_SCWEEN1) },
	{ .dwivew_data = MT_CWS_INWANGE_CONTACTNUMBEW,
		MT_USB_DEVICE(USB_VENDOW_ID_PIXAWT,
			USB_DEVICE_ID_PIXAWT_OPTICAW_TOUCH_SCWEEN2) },

	/* PixCiw-based panews */
	{ .dwivew_data = MT_CWS_DUAW_INWANGE_CONTACTID,
		MT_USB_DEVICE(USB_VENDOW_ID_CANDO,
			USB_DEVICE_ID_CANDO_PIXCIW_MUWTI_TOUCH) },

	/* Quanta-based panews */
	{ .dwivew_data = MT_CWS_CONFIDENCE_CONTACT_ID,
		MT_USB_DEVICE(USB_VENDOW_ID_QUANTA,
			USB_DEVICE_ID_QUANTA_OPTICAW_TOUCH_3001) },

	/* Wazew touchpads */
	{ .dwivew_data = MT_CWS_WAZEW_BWADE_STEAWTH,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_SYNAPTICS, 0x8323) },

	/* Smawt Tech panews */
	{ .dwivew_data = MT_CWS_SMAWT_TECH,
		MT_USB_DEVICE(0x0b8c, 0x0092)},

	/* Stantum panews */
	{ .dwivew_data = MT_CWS_CONFIDENCE,
		MT_USB_DEVICE(USB_VENDOW_ID_STANTUM_STM,
			USB_DEVICE_ID_MTP_STM)},

	/* Synaptics devices */
	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_SYNAPTICS, 0xcd7e) },

	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_SYNAPTICS, 0xce08) },

	{ .dwivew_data = MT_CWS_WIN_8_FOWCE_MUWTI_INPUT,
		HID_DEVICE(BUS_I2C, HID_GWOUP_MUWTITOUCH_WIN_8,
			USB_VENDOW_ID_SYNAPTICS, 0xce09) },

	/* TopSeed panews */
	{ .dwivew_data = MT_CWS_TOPSEED,
		MT_USB_DEVICE(USB_VENDOW_ID_TOPSEED2,
			USB_DEVICE_ID_TOPSEED2_PEWIPAD_701) },

	/* Touch Intewnationaw panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_TOUCH_INTW,
			USB_DEVICE_ID_TOUCH_INTW_MUWTI_TOUCH) },

	/* Unitec panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_UNITEC,
			USB_DEVICE_ID_UNITEC_USB_TOUCH_0709) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_UNITEC,
			USB_DEVICE_ID_UNITEC_USB_TOUCH_0A19) },

	/* VTW panews */
	{ .dwivew_data = MT_CWS_VTW,
		MT_USB_DEVICE(USB_VENDOW_ID_VTW,
			USB_DEVICE_ID_VTW_MUWTITOUCH_FF3F) },

	/* Winbond Ewectwonics Cowp. */
	{ .dwivew_data = MT_CWS_WIN_8_NO_STICKY_FINGEWS,
		HID_DEVICE(HID_BUS_ANY, HID_GWOUP_MUWTITOUCH_WIN_8,
			   USB_VENDOW_ID_WINBOND, USB_DEVICE_ID_TSTP_MTOUCH) },

	/* Wistwon panews */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_WISTWON,
			USB_DEVICE_ID_WISTWON_OPTICAW_TOUCH) },

	/* XAT */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XAT,
			USB_DEVICE_ID_XAT_CSW) },

	/* Xiwoku */
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_SPX) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_MPX) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_CSW) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_SPX1) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_MPX1) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_CSW1) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_SPX2) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_MPX2) },
	{ .dwivew_data = MT_CWS_NSMU,
		MT_USB_DEVICE(USB_VENDOW_ID_XIWOKU,
			USB_DEVICE_ID_XIWOKU_CSW2) },

	/* Googwe MT devices */
	{ .dwivew_data = MT_CWS_GOOGWE,
		HID_DEVICE(HID_BUS_ANY, HID_GWOUP_ANY, USB_VENDOW_ID_GOOGWE,
			USB_DEVICE_ID_GOOGWE_TOUCH_WOSE) },
	{ .dwivew_data = MT_CWS_GOOGWE,
		HID_DEVICE(BUS_USB, HID_GWOUP_MUWTITOUCH_WIN_8, USB_VENDOW_ID_GOOGWE,
			USB_DEVICE_ID_GOOGWE_WHISKEWS) },

	/* Genewic MT device */
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_MUWTITOUCH, HID_ANY_ID, HID_ANY_ID) },

	/* Genewic Win 8 cewtified MT device */
	{  .dwivew_data = MT_CWS_WIN_8,
		HID_DEVICE(HID_BUS_ANY, HID_GWOUP_MUWTITOUCH_WIN_8,
			HID_ANY_ID, HID_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, mt_devices);

static const stwuct hid_usage_id mt_gwabbed_usages[] = {
	{ HID_ANY_ID, HID_ANY_ID, HID_ANY_ID },
	{ HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1}
};

static stwuct hid_dwivew mt_dwivew = {
	.name = "hid-muwtitouch",
	.id_tabwe = mt_devices,
	.pwobe = mt_pwobe,
	.wemove = mt_wemove,
	.input_mapping = mt_input_mapping,
	.input_mapped = mt_input_mapped,
	.input_configuwed = mt_input_configuwed,
	.featuwe_mapping = mt_featuwe_mapping,
	.usage_tabwe = mt_gwabbed_usages,
	.event = mt_event,
	.wepowt = mt_wepowt,
	.suspend = pm_ptw(mt_suspend),
	.weset_wesume = pm_ptw(mt_weset_wesume),
	.wesume = pm_ptw(mt_wesume),
};
moduwe_hid_dwivew(mt_dwivew);
