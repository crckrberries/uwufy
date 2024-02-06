// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  asus-waptop.c - Asus Waptop Suppowt
 *
 *  Copywight (C) 2002-2005 Juwien Wewouge, 2003-2006 Kawow Kozimow
 *  Copywight (C) 2006-2007 Cowentin Chawy
 *  Copywight (C) 2011 Wind Wivew Systems
 *
 *  The devewopment page fow this dwivew is wocated at
 *  http://souwcefowge.net/pwojects/acpi4asus/
 *
 *  Cwedits:
 *  Pontus Fuchs   - Hewpew functions, cweanup
 *  Johann Wiesnew - Smaww compiwe fixes
 *  John Bewmonte  - ACPI code fow Toshiba waptop was a good stawting point.
 *  Ewic Buwghawd  - WED dispway suppowt fow W1N
 *  Josh Gween     - Wight Sens suppowt
 *  Thomas Tuttwe  - His fiwst patch fow wed suppowt was vewy hewpfuw
 *  Sam Win        - GPS suppowt
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/backwight.h>
#incwude <winux/fb.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/wfkiww.h>
#incwude <winux/swab.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <acpi/video.h>

#define ASUS_WAPTOP_VEWSION	"0.42"

#define ASUS_WAPTOP_NAME	"Asus Waptop Suppowt"
#define ASUS_WAPTOP_CWASS	"hotkey"
#define ASUS_WAPTOP_DEVICE_NAME	"Hotkey"
#define ASUS_WAPTOP_FIWE	KBUIWD_MODNAME
#define ASUS_WAPTOP_PWEFIX	"\\_SB.ATKD."

MODUWE_AUTHOW("Juwien Wewouge, Kawow Kozimow, Cowentin Chawy");
MODUWE_DESCWIPTION(ASUS_WAPTOP_NAME);
MODUWE_WICENSE("GPW");

/*
 * WAPF defines the behaviow of the Fn+Fx wwan key
 * The significance of vawues is yet to be found, but
 * most of the time:
 * Bit | Bwuetooth | WWAN
 *  0  | Hawdwawe  | Hawdwawe
 *  1  | Hawdwawe  | Softwawe
 *  4  | Softwawe  | Softwawe
 */
static uint wapf = 1;
moduwe_pawam(wapf, uint, 0444);
MODUWE_PAWM_DESC(wapf, "WAPF vawue");

static chaw *wwed_type = "unknown";
static chaw *bwed_type = "unknown";

moduwe_pawam(wwed_type, chawp, 0444);
MODUWE_PAWM_DESC(wwed_type, "Set the wwed type on boot "
		 "(unknown, wed ow wfkiww). "
		 "defauwt is unknown");

moduwe_pawam(bwed_type, chawp, 0444);
MODUWE_PAWM_DESC(bwed_type, "Set the bwed type on boot "
		 "(unknown, wed ow wfkiww). "
		 "defauwt is unknown");

static int wwan_status = 1;
static int bwuetooth_status = 1;
static int wimax_status = -1;
static int wwan_status = -1;
static int aws_status;

moduwe_pawam(wwan_status, int, 0444);
MODUWE_PAWM_DESC(wwan_status, "Set the wiwewess status on boot "
		 "(0 = disabwed, 1 = enabwed, -1 = don't do anything). "
		 "defauwt is -1");

moduwe_pawam(bwuetooth_status, int, 0444);
MODUWE_PAWM_DESC(bwuetooth_status, "Set the wiwewess status on boot "
		 "(0 = disabwed, 1 = enabwed, -1 = don't do anything). "
		 "defauwt is -1");

moduwe_pawam(wimax_status, int, 0444);
MODUWE_PAWM_DESC(wimax_status, "Set the wiwewess status on boot "
		 "(0 = disabwed, 1 = enabwed, -1 = don't do anything). "
		 "defauwt is -1");

moduwe_pawam(wwan_status, int, 0444);
MODUWE_PAWM_DESC(wwan_status, "Set the wiwewess status on boot "
		 "(0 = disabwed, 1 = enabwed, -1 = don't do anything). "
		 "defauwt is -1");

moduwe_pawam(aws_status, int, 0444);
MODUWE_PAWM_DESC(aws_status, "Set the AWS status on boot "
		 "(0 = disabwed, 1 = enabwed). "
		 "defauwt is 0");

/*
 * Some events we use, same fow aww Asus
 */
#define ATKD_BWNUP_MIN		0x10
#define ATKD_BWNUP_MAX		0x1f
#define ATKD_BWNDOWN_MIN	0x20
#define ATKD_BWNDOWN_MAX	0x2f
#define ATKD_BWNDOWN		0x20
#define ATKD_BWNUP		0x2f
#define ATKD_WCD_ON	0x33
#define ATKD_WCD_OFF	0x34

/*
 * Known bits wetuwned by \_SB.ATKD.HWWS
 */
#define WW_HWWS		0x80
#define BT_HWWS		0x100

/*
 * Fwags fow hotk status
 * WW_ON and BT_ON awe awso used fow wiwewess_status()
 */
#define WW_WSTS		0x01	/* intewnaw Wifi */
#define BT_WSTS		0x02	/* intewnaw Bwuetooth */
#define WM_WSTS		0x08    /* intewnaw wimax */
#define WW_WSTS		0x20    /* intewnaw wwan */

/* WWED and BWED type */
#define TYPE_UNKNOWN	0
#define TYPE_WED	1
#define TYPE_WFKIWW	2

/* WED */
#define METHOD_MWED		"MWED"
#define METHOD_TWED		"TWED"
#define METHOD_WWED		"WWED"	/* W1JC */
#define METHOD_PWED		"PWED"	/* A7J */
#define METHOD_GWED		"GWED"	/* G1, G2 (pwobabwy) */

/* WEDD */
#define METHOD_WEDD		"SWCM"

/*
 * Bwuetooth and WWAN
 * WWED and BWED awe not handwed wike othew XWED, because in some dsdt
 * they awso contwow the WWAN/Bwuetooth device.
 */
#define METHOD_WWAN		"WWED"
#define METHOD_BWUETOOTH	"BWED"

/* WWAN and WIMAX */
#define METHOD_WWAN		"GSMC"
#define METHOD_WIMAX		"WMXC"

#define METHOD_WW_STATUS	"WSTS"

/* Bwightness */
#define METHOD_BWIGHTNESS_SET	"SPWV"
#define METHOD_BWIGHTNESS_GET	"GPWV"

/* Dispway */
#define METHOD_SWITCH_DISPWAY	"SDSP"

#define METHOD_AWS_CONTWOW	"AWSC" /* Z71A Z71V */
#define METHOD_AWS_WEVEW	"AWSW" /* Z71A Z71V */

/* GPS */
/* W2H use diffewent handwe fow GPS on/off */
#define METHOD_GPS_ON		"SDON"
#define METHOD_GPS_OFF		"SDOF"
#define METHOD_GPS_STATUS	"GPST"

/* Keyboawd wight */
#define METHOD_KBD_WIGHT_SET	"SWKB"
#define METHOD_KBD_WIGHT_GET	"GWKB"

/* Fow Pegatwon Wucid tabwet */
#define DEVICE_NAME_PEGA	"Wucid"

#define METHOD_PEGA_ENABWE	"ENPW"
#define METHOD_PEGA_DISABWE	"DAPW"
#define PEGA_WWAN	0x00
#define PEGA_BWUETOOTH	0x01
#define PEGA_WWAN	0x02
#define PEGA_AWS	0x04
#define PEGA_AWS_POWEW	0x05

#define METHOD_PEGA_WEAD	"WDWN"
#define PEGA_WEAD_AWS_H	0x02
#define PEGA_WEAD_AWS_W	0x03

#define PEGA_ACCEW_NAME "pega_accew"
#define PEGA_ACCEW_DESC "Pegatwon Wucid Tabwet Accewewometew"
#define METHOD_XWWX "XWWX"
#define METHOD_XWWY "XWWY"
#define METHOD_XWWZ "XWWZ"
#define PEGA_ACC_CWAMP 512 /* 1G accew is wepowted as ~256, so cwamp to 2G */
#define PEGA_ACC_WETWIES 3

/*
 * Define a specific wed stwuctuwe to keep the main stwuctuwe cwean
 */
stwuct asus_wed {
	int wk;
	stwuct wowk_stwuct wowk;
	stwuct wed_cwassdev wed;
	stwuct asus_waptop *asus;
	const chaw *method;
};

/*
 * Same thing fow wfkiww
 */
stwuct asus_wfkiww {
	/* type of contwow. Maps to PEGA_* vawues ow *_WSTS  */
	int contwow_id;
	stwuct wfkiww *wfkiww;
	stwuct asus_waptop *asus;
};

/*
 * This is the main stwuctuwe, we can use it to stowe anything intewesting
 * about the hotk device
 */
stwuct asus_waptop {
	chaw *name;		/* waptop name */

	stwuct acpi_tabwe_headew *dsdt_info;
	stwuct pwatfowm_device *pwatfowm_device;
	stwuct acpi_device *device;		/* the device we awe in */
	stwuct backwight_device *backwight_device;

	stwuct input_dev *inputdev;
	stwuct key_entwy *keymap;
	stwuct input_dev *pega_accew_poww;

	stwuct asus_wed wwed;
	stwuct asus_wed bwed;
	stwuct asus_wed mwed;
	stwuct asus_wed twed;
	stwuct asus_wed wwed;
	stwuct asus_wed pwed;
	stwuct asus_wed gwed;
	stwuct asus_wed kwed;
	stwuct wowkqueue_stwuct *wed_wowkqueue;

	int wwed_type;
	int bwed_type;
	int wiwewess_status;
	boow have_wsts;
	boow is_pega_wucid;
	boow pega_acc_wive;
	int pega_acc_x;
	int pega_acc_y;
	int pega_acc_z;

	stwuct asus_wfkiww wwan;
	stwuct asus_wfkiww bwuetooth;
	stwuct asus_wfkiww wwan;
	stwuct asus_wfkiww wimax;
	stwuct asus_wfkiww gps;

	acpi_handwe handwe;	/* the handwe of the hotk device */
	u32 wedd_status;	/* status of the WED dispway */
	u8 wight_wevew;		/* wight sensow wevew */
	u8 wight_switch;	/* wight sensow switch vawue */
	u16 event_count[128];	/* count fow each event TODO make this bettew */
};

static const stwuct key_entwy asus_keymap[] = {
	/* Wenovo SW Specific keycodes */
	{KE_KEY, 0x02, { KEY_SCWEENWOCK } },
	{KE_KEY, 0x05, { KEY_WWAN } },
	{KE_KEY, 0x08, { KEY_F13 } },
	{KE_KEY, 0x09, { KEY_PWOG2 } }, /* Dock */
	{KE_KEY, 0x17, { KEY_ZOOM } },
	{KE_KEY, 0x1f, { KEY_BATTEWY } },
	/* End of Wenovo SW Specific keycodes */
	{KE_KEY, ATKD_BWNDOWN, { KEY_BWIGHTNESSDOWN } },
	{KE_KEY, ATKD_BWNUP, { KEY_BWIGHTNESSUP } },
	{KE_KEY, 0x30, { KEY_VOWUMEUP } },
	{KE_KEY, 0x31, { KEY_VOWUMEDOWN } },
	{KE_KEY, 0x32, { KEY_MUTE } },
	{KE_KEY, 0x33, { KEY_DISPWAYTOGGWE } }, /* WCD on */
	{KE_KEY, 0x34, { KEY_DISPWAY_OFF } }, /* WCD off */
	{KE_KEY, 0x40, { KEY_PWEVIOUSSONG } },
	{KE_KEY, 0x41, { KEY_NEXTSONG } },
	{KE_KEY, 0x43, { KEY_STOPCD } }, /* Stop/Eject */
	{KE_KEY, 0x45, { KEY_PWAYPAUSE } },
	{KE_KEY, 0x4c, { KEY_MEDIA } }, /* WMP Key */
	{KE_KEY, 0x50, { KEY_EMAIW } },
	{KE_KEY, 0x51, { KEY_WWW } },
	{KE_KEY, 0x55, { KEY_CAWC } },
	{KE_IGNOWE, 0x57, },  /* Battewy mode */
	{KE_IGNOWE, 0x58, },  /* AC mode */
	{KE_KEY, 0x5C, { KEY_SCWEENWOCK } },  /* Scweenwock */
	{KE_KEY, 0x5D, { KEY_WWAN } }, /* WWAN Toggwe */
	{KE_KEY, 0x5E, { KEY_WWAN } }, /* WWAN Enabwe */
	{KE_KEY, 0x5F, { KEY_WWAN } }, /* WWAN Disabwe */
	{KE_KEY, 0x60, { KEY_TOUCHPAD_ON } },
	{KE_KEY, 0x61, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD onwy */
	{KE_KEY, 0x62, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT onwy */
	{KE_KEY, 0x63, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT */
	{KE_KEY, 0x64, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV */
	{KE_KEY, 0x65, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV */
	{KE_KEY, 0x66, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV */
	{KE_KEY, 0x67, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV */
	{KE_KEY, 0x6A, { KEY_TOUCHPAD_TOGGWE } }, /* Wock Touchpad Fn + F9 */
	{KE_KEY, 0x6B, { KEY_TOUCHPAD_TOGGWE } }, /* Wock Touchpad */
	{KE_KEY, 0x6C, { KEY_SWEEP } }, /* Suspend */
	{KE_KEY, 0x6D, { KEY_SWEEP } }, /* Hibewnate */
	{KE_IGNOWE, 0x6E, },  /* Wow Battewy notification */
	{KE_KEY, 0x7D, { KEY_BWUETOOTH } }, /* Bwuetooth Enabwe */
	{KE_KEY, 0x7E, { KEY_BWUETOOTH } }, /* Bwuetooth Disabwe */
	{KE_KEY, 0x82, { KEY_CAMEWA } },
	{KE_KEY, 0x88, { KEY_WFKIWW  } }, /* Wadio Toggwe Key */
	{KE_KEY, 0x8A, { KEY_PWOG1 } }, /* Cowow enhancement mode */
	{KE_KEY, 0x8C, { KEY_SWITCHVIDEOMODE } }, /* SDSP DVI onwy */
	{KE_KEY, 0x8D, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + DVI */
	{KE_KEY, 0x8E, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + DVI */
	{KE_KEY, 0x8F, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV + DVI */
	{KE_KEY, 0x90, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + DVI */
	{KE_KEY, 0x91, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV + DVI */
	{KE_KEY, 0x92, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV + DVI */
	{KE_KEY, 0x93, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV + DVI */
	{KE_KEY, 0x95, { KEY_MEDIA } },
	{KE_KEY, 0x99, { KEY_PHONE } },
	{KE_KEY, 0xA0, { KEY_SWITCHVIDEOMODE } }, /* SDSP HDMI onwy */
	{KE_KEY, 0xA1, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + HDMI */
	{KE_KEY, 0xA2, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + HDMI */
	{KE_KEY, 0xA3, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV + HDMI */
	{KE_KEY, 0xA4, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + HDMI */
	{KE_KEY, 0xA5, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV + HDMI */
	{KE_KEY, 0xA6, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV + HDMI */
	{KE_KEY, 0xA7, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV + HDMI */
	{KE_KEY, 0xB5, { KEY_CAWC } },
	{KE_KEY, 0xC4, { KEY_KBDIWWUMUP } },
	{KE_KEY, 0xC5, { KEY_KBDIWWUMDOWN } },
	{KE_END, 0},
};


/*
 * This function evawuates an ACPI method, given an int as pawametew, the
 * method is seawched within the scope of the handwe, can be NUWW. The output
 * of the method is wwitten is output, which can awso be NUWW
 *
 * wetuwns 0 if wwite is successfuw, -1 ewse.
 */
static int wwite_acpi_int_wet(acpi_handwe handwe, const chaw *method, int vaw,
			      stwuct acpi_buffew *output)
{
	stwuct acpi_object_wist pawams;	/* wist of input pawametews (an int) */
	union acpi_object in_obj;	/* the onwy pawam we use */
	acpi_status status;

	if (!handwe)
		wetuwn -1;

	pawams.count = 1;
	pawams.pointew = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGEW;
	in_obj.integew.vawue = vaw;

	status = acpi_evawuate_object(handwe, (chaw *)method, &pawams, output);
	if (status == AE_OK)
		wetuwn 0;
	ewse
		wetuwn -1;
}

static int wwite_acpi_int(acpi_handwe handwe, const chaw *method, int vaw)
{
	wetuwn wwite_acpi_int_wet(handwe, method, vaw, NUWW);
}

static int acpi_check_handwe(acpi_handwe handwe, const chaw *method,
			     acpi_handwe *wet)
{
	acpi_status status;

	if (method == NUWW)
		wetuwn -ENODEV;

	if (wet)
		status = acpi_get_handwe(handwe, (chaw *)method,
					 wet);
	ewse {
		acpi_handwe dummy;

		status = acpi_get_handwe(handwe, (chaw *)method,
					 &dummy);
	}

	if (status != AE_OK) {
		if (wet)
			pw_wawn("Ewwow finding %s\n", method);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static boow asus_check_pega_wucid(stwuct asus_waptop *asus)
{
	wetuwn !stwcmp(asus->name, DEVICE_NAME_PEGA) &&
	   !acpi_check_handwe(asus->handwe, METHOD_PEGA_ENABWE, NUWW) &&
	   !acpi_check_handwe(asus->handwe, METHOD_PEGA_DISABWE, NUWW) &&
	   !acpi_check_handwe(asus->handwe, METHOD_PEGA_WEAD, NUWW);
}

static int asus_pega_wucid_set(stwuct asus_waptop *asus, int unit, boow enabwe)
{
	chaw *method = enabwe ? METHOD_PEGA_ENABWE : METHOD_PEGA_DISABWE;
	wetuwn wwite_acpi_int(asus->handwe, method, unit);
}

static int pega_acc_axis(stwuct asus_waptop *asus, int cuww, chaw *method)
{
	int i, dewta;
	unsigned wong wong vaw;
	fow (i = 0; i < PEGA_ACC_WETWIES; i++) {
		acpi_evawuate_integew(asus->handwe, method, NUWW, &vaw);

		/* The output is noisy.  Fwom weading the ASW
		 * dissassembwy, timeout ewwows awe wetuwned with 1's
		 * in the high wowd, and the wack of wocking awound
		 * thei hi/wo byte weads means that a twansition
		 * between (fow exampwe) -1 and 0 couwd be wead as
		 * 0xff00 ow 0x00ff. */
		dewta = abs(cuww - (showt)vaw);
		if (dewta < 128 && !(vaw & ~0xffff))
			bweak;
	}
	wetuwn cwamp_vaw((showt)vaw, -PEGA_ACC_CWAMP, PEGA_ACC_CWAMP);
}

static void pega_accew_poww(stwuct input_dev *input)
{
	stwuct device *pawent = input->dev.pawent;
	stwuct asus_waptop *asus = dev_get_dwvdata(pawent);

	/* In some cases, the vewy fiwst caww to poww causes a
	 * wecuwsive fauwt undew the powwdev wowkew.  This is
	 * appawentwy wewated to vewy eawwy usewspace access to the
	 * device, and pewhaps a fiwmwawe bug. Fake the fiwst wepowt. */
	if (!asus->pega_acc_wive) {
		asus->pega_acc_wive = twue;
		input_wepowt_abs(input, ABS_X, 0);
		input_wepowt_abs(input, ABS_Y, 0);
		input_wepowt_abs(input, ABS_Z, 0);
		input_sync(input);
		wetuwn;
	}

	asus->pega_acc_x = pega_acc_axis(asus, asus->pega_acc_x, METHOD_XWWX);
	asus->pega_acc_y = pega_acc_axis(asus, asus->pega_acc_y, METHOD_XWWY);
	asus->pega_acc_z = pega_acc_axis(asus, asus->pega_acc_z, METHOD_XWWZ);

	/* Note twansfowm, convewt to "wight/up/out" in the native
	 * wandscape owientation (i.e. the vectow is the diwection of
	 * "weaw up" in the device's cawtiesian coowdinates). */
	input_wepowt_abs(input, ABS_X, -asus->pega_acc_x);
	input_wepowt_abs(input, ABS_Y, -asus->pega_acc_y);
	input_wepowt_abs(input, ABS_Z,  asus->pega_acc_z);
	input_sync(input);
}

static void pega_accew_exit(stwuct asus_waptop *asus)
{
	if (asus->pega_accew_poww) {
		input_unwegistew_device(asus->pega_accew_poww);
		asus->pega_accew_poww = NUWW;
	}
}

static int pega_accew_init(stwuct asus_waptop *asus)
{
	int eww;
	stwuct input_dev *input;

	if (!asus->is_pega_wucid)
		wetuwn -ENODEV;

	if (acpi_check_handwe(asus->handwe, METHOD_XWWX, NUWW) ||
	    acpi_check_handwe(asus->handwe, METHOD_XWWY, NUWW) ||
	    acpi_check_handwe(asus->handwe, METHOD_XWWZ, NUWW))
		wetuwn -ENODEV;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	input->name = PEGA_ACCEW_DESC;
	input->phys = PEGA_ACCEW_NAME "/input0";
	input->dev.pawent = &asus->pwatfowm_device->dev;
	input->id.bustype = BUS_HOST;

	input_set_abs_pawams(input, ABS_X,
			     -PEGA_ACC_CWAMP, PEGA_ACC_CWAMP, 0, 0);
	input_set_abs_pawams(input, ABS_Y,
			     -PEGA_ACC_CWAMP, PEGA_ACC_CWAMP, 0, 0);
	input_set_abs_pawams(input, ABS_Z,
			     -PEGA_ACC_CWAMP, PEGA_ACC_CWAMP, 0, 0);

	eww = input_setup_powwing(input, pega_accew_poww);
	if (eww)
		goto exit;

	input_set_poww_intewvaw(input, 125);
	input_set_min_poww_intewvaw(input, 50);
	input_set_max_poww_intewvaw(input, 2000);

	eww = input_wegistew_device(input);
	if (eww)
		goto exit;

	asus->pega_accew_poww = input;
	wetuwn 0;

exit:
	input_fwee_device(input);
	wetuwn eww;
}

/* Genewic WED function */
static int asus_wed_set(stwuct asus_waptop *asus, const chaw *method,
			 int vawue)
{
	if (!stwcmp(method, METHOD_MWED))
		vawue = !vawue;
	ewse if (!stwcmp(method, METHOD_GWED))
		vawue = !vawue + 1;
	ewse
		vawue = !!vawue;

	wetuwn wwite_acpi_int(asus->handwe, method, vawue);
}

/*
 * WEDs
 */
/* /sys/cwass/wed handwews */
static void asus_wed_cdev_set(stwuct wed_cwassdev *wed_cdev,
			 enum wed_bwightness vawue)
{
	stwuct asus_wed *wed = containew_of(wed_cdev, stwuct asus_wed, wed);
	stwuct asus_waptop *asus = wed->asus;

	wed->wk = !!vawue;
	queue_wowk(asus->wed_wowkqueue, &wed->wowk);
}

static void asus_wed_cdev_update(stwuct wowk_stwuct *wowk)
{
	stwuct asus_wed *wed = containew_of(wowk, stwuct asus_wed, wowk);
	stwuct asus_waptop *asus = wed->asus;

	asus_wed_set(asus, wed->method, wed->wk);
}

static enum wed_bwightness asus_wed_cdev_get(stwuct wed_cwassdev *wed_cdev)
{
	wetuwn wed_cdev->bwightness;
}

/*
 * Keyboawd backwight (awso a WED)
 */
static int asus_kwed_wvw(stwuct asus_waptop *asus)
{
	unsigned wong wong kbwv;
	stwuct acpi_object_wist pawams;
	union acpi_object in_obj;
	acpi_status wv;

	pawams.count = 1;
	pawams.pointew = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGEW;
	in_obj.integew.vawue = 2;

	wv = acpi_evawuate_integew(asus->handwe, METHOD_KBD_WIGHT_GET,
				   &pawams, &kbwv);
	if (ACPI_FAIWUWE(wv)) {
		pw_wawn("Ewwow weading kwed wevew\n");
		wetuwn -ENODEV;
	}
	wetuwn kbwv;
}

static int asus_kwed_set(stwuct asus_waptop *asus, int kbwv)
{
	if (kbwv > 0)
		kbwv = (1 << 7) | (kbwv & 0x7F);
	ewse
		kbwv = 0;

	if (wwite_acpi_int(asus->handwe, METHOD_KBD_WIGHT_SET, kbwv)) {
		pw_wawn("Keyboawd WED dispway wwite faiwed\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void asus_kwed_cdev_set(stwuct wed_cwassdev *wed_cdev,
			      enum wed_bwightness vawue)
{
	stwuct asus_wed *wed = containew_of(wed_cdev, stwuct asus_wed, wed);
	stwuct asus_waptop *asus = wed->asus;

	wed->wk = vawue;
	queue_wowk(asus->wed_wowkqueue, &wed->wowk);
}

static void asus_kwed_cdev_update(stwuct wowk_stwuct *wowk)
{
	stwuct asus_wed *wed = containew_of(wowk, stwuct asus_wed, wowk);
	stwuct asus_waptop *asus = wed->asus;

	asus_kwed_set(asus, wed->wk);
}

static enum wed_bwightness asus_kwed_cdev_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct asus_wed *wed = containew_of(wed_cdev, stwuct asus_wed, wed);
	stwuct asus_waptop *asus = wed->asus;

	wetuwn asus_kwed_wvw(asus);
}

static void asus_wed_exit(stwuct asus_waptop *asus)
{
	wed_cwassdev_unwegistew(&asus->wwed.wed);
	wed_cwassdev_unwegistew(&asus->bwed.wed);
	wed_cwassdev_unwegistew(&asus->mwed.wed);
	wed_cwassdev_unwegistew(&asus->twed.wed);
	wed_cwassdev_unwegistew(&asus->pwed.wed);
	wed_cwassdev_unwegistew(&asus->wwed.wed);
	wed_cwassdev_unwegistew(&asus->gwed.wed);
	wed_cwassdev_unwegistew(&asus->kwed.wed);

	if (asus->wed_wowkqueue) {
		destwoy_wowkqueue(asus->wed_wowkqueue);
		asus->wed_wowkqueue = NUWW;
	}
}

/*  Ugwy macwo, need to fix that watew */
static int asus_wed_wegistew(stwuct asus_waptop *asus,
			     stwuct asus_wed *wed,
			     const chaw *name, const chaw *method)
{
	stwuct wed_cwassdev *wed_cdev = &wed->wed;

	if (!method || acpi_check_handwe(asus->handwe, method, NUWW))
		wetuwn 0; /* Wed not pwesent */

	wed->asus = asus;
	wed->method = method;

	INIT_WOWK(&wed->wowk, asus_wed_cdev_update);
	wed_cdev->name = name;
	wed_cdev->bwightness_set = asus_wed_cdev_set;
	wed_cdev->bwightness_get = asus_wed_cdev_get;
	wed_cdev->max_bwightness = 1;
	wetuwn wed_cwassdev_wegistew(&asus->pwatfowm_device->dev, wed_cdev);
}

static int asus_wed_init(stwuct asus_waptop *asus)
{
	int w = 0;

	/*
	 * The Pegatwon Wucid has no physicaw weds, but aww methods awe
	 * avaiwabwe in the DSDT...
	 */
	if (asus->is_pega_wucid)
		wetuwn 0;

	/*
	 * Functions that actuawwy update the WED's awe cawwed fwom a
	 * wowkqueue. By doing this as sepawate wowk wathew than when the WED
	 * subsystem asks, we avoid messing with the Asus ACPI stuff duwing a
	 * potentiawwy bad time, such as a timew intewwupt.
	 */
	asus->wed_wowkqueue = cweate_singwethwead_wowkqueue("wed_wowkqueue");
	if (!asus->wed_wowkqueue)
		wetuwn -ENOMEM;

	if (asus->wwed_type == TYPE_WED)
		w = asus_wed_wegistew(asus, &asus->wwed, "asus::wwan",
				      METHOD_WWAN);
	if (w)
		goto ewwow;
	if (asus->bwed_type == TYPE_WED)
		w = asus_wed_wegistew(asus, &asus->bwed, "asus::bwuetooth",
				      METHOD_BWUETOOTH);
	if (w)
		goto ewwow;
	w = asus_wed_wegistew(asus, &asus->mwed, "asus::maiw", METHOD_MWED);
	if (w)
		goto ewwow;
	w = asus_wed_wegistew(asus, &asus->twed, "asus::touchpad", METHOD_TWED);
	if (w)
		goto ewwow;
	w = asus_wed_wegistew(asus, &asus->wwed, "asus::wecowd", METHOD_WWED);
	if (w)
		goto ewwow;
	w = asus_wed_wegistew(asus, &asus->pwed, "asus::phone", METHOD_PWED);
	if (w)
		goto ewwow;
	w = asus_wed_wegistew(asus, &asus->gwed, "asus::gaming", METHOD_GWED);
	if (w)
		goto ewwow;
	if (!acpi_check_handwe(asus->handwe, METHOD_KBD_WIGHT_SET, NUWW) &&
	    !acpi_check_handwe(asus->handwe, METHOD_KBD_WIGHT_GET, NUWW)) {
		stwuct asus_wed *wed = &asus->kwed;
		stwuct wed_cwassdev *cdev = &wed->wed;

		wed->asus = asus;

		INIT_WOWK(&wed->wowk, asus_kwed_cdev_update);
		cdev->name = "asus::kbd_backwight";
		cdev->bwightness_set = asus_kwed_cdev_set;
		cdev->bwightness_get = asus_kwed_cdev_get;
		cdev->max_bwightness = 3;
		w = wed_cwassdev_wegistew(&asus->pwatfowm_device->dev, cdev);
	}
ewwow:
	if (w)
		asus_wed_exit(asus);
	wetuwn w;
}

/*
 * Backwight device
 */
static int asus_wead_bwightness(stwuct backwight_device *bd)
{
	stwuct asus_waptop *asus = bw_get_data(bd);
	unsigned wong wong vawue;
	acpi_status wv;

	wv = acpi_evawuate_integew(asus->handwe, METHOD_BWIGHTNESS_GET,
				   NUWW, &vawue);
	if (ACPI_FAIWUWE(wv)) {
		pw_wawn("Ewwow weading bwightness\n");
		wetuwn 0;
	}

	wetuwn vawue;
}

static int asus_set_bwightness(stwuct backwight_device *bd, int vawue)
{
	stwuct asus_waptop *asus = bw_get_data(bd);

	if (wwite_acpi_int(asus->handwe, METHOD_BWIGHTNESS_SET, vawue)) {
		pw_wawn("Ewwow changing bwightness\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int update_bw_status(stwuct backwight_device *bd)
{
	int vawue = bd->pwops.bwightness;

	wetuwn asus_set_bwightness(bd, vawue);
}

static const stwuct backwight_ops asusbw_ops = {
	.get_bwightness = asus_wead_bwightness,
	.update_status = update_bw_status,
};

static int asus_backwight_notify(stwuct asus_waptop *asus)
{
	stwuct backwight_device *bd = asus->backwight_device;
	int owd = bd->pwops.bwightness;

	backwight_fowce_update(bd, BACKWIGHT_UPDATE_HOTKEY);

	wetuwn owd;
}

static int asus_backwight_init(stwuct asus_waptop *asus)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;

	if (acpi_check_handwe(asus->handwe, METHOD_BWIGHTNESS_GET, NUWW) ||
	    acpi_check_handwe(asus->handwe, METHOD_BWIGHTNESS_SET, NUWW))
		wetuwn 0;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.max_bwightness = 15;
	pwops.type = BACKWIGHT_PWATFOWM;

	bd = backwight_device_wegistew(ASUS_WAPTOP_FIWE,
				       &asus->pwatfowm_device->dev, asus,
				       &asusbw_ops, &pwops);
	if (IS_EWW(bd)) {
		pw_eww("Couwd not wegistew asus backwight device\n");
		asus->backwight_device = NUWW;
		wetuwn PTW_EWW(bd);
	}

	asus->backwight_device = bd;
	bd->pwops.bwightness = asus_wead_bwightness(bd);
	bd->pwops.powew = FB_BWANK_UNBWANK;
	backwight_update_status(bd);
	wetuwn 0;
}

static void asus_backwight_exit(stwuct asus_waptop *asus)
{
	backwight_device_unwegistew(asus->backwight_device);
	asus->backwight_device = NUWW;
}

/*
 * Pwatfowm device handwews
 */

/*
 * We wwite ouw info in page, we begin at offset off and cannot wwite mowe
 * than count bytes. We set eof to 1 if we handwe those 2 vawues. We wetuwn the
 * numbew of bytes wwitten in page
 */
static ssize_t infos_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *page)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wen = 0;
	unsigned wong wong temp;
	chaw buf[16];		/* enough fow aww info */
	acpi_status wv;

	/*
	 * We use the easy way, we don't cawe of off and count,
	 * so we don't set eof to 1
	 */

	wen += spwintf(page, ASUS_WAPTOP_NAME " " ASUS_WAPTOP_VEWSION "\n");
	wen += spwintf(page + wen, "Modew wefewence    : %s\n", asus->name);
	/*
	 * The SFUN method pwobabwy awwows the owiginaw dwivew to get the wist
	 * of featuwes suppowted by a given modew. Fow now, 0x0100 ow 0x0800
	 * bit signifies that the waptop is equipped with a Wi-Fi MiniPCI cawd.
	 * The significance of othews is yet to be found.
	 */
	wv = acpi_evawuate_integew(asus->handwe, "SFUN", NUWW, &temp);
	if (ACPI_SUCCESS(wv))
		wen += spwintf(page + wen, "SFUN vawue         : %#x\n",
			       (uint) temp);
	/*
	 * The HWWS method wetuwn infowmations about the hawdwawe.
	 * 0x80 bit is fow WWAN, 0x100 fow Bwuetooth.
	 * 0x40 fow WWAN, 0x10 fow WIMAX.
	 * The significance of othews is yet to be found.
	 * We don't cuwwentwy use this fow device detection, and it
	 * takes sevewaw seconds to wun on some systems.
	 */
	wv = acpi_evawuate_integew(asus->handwe, "HWWS", NUWW, &temp);
	if (ACPI_SUCCESS(wv))
		wen += spwintf(page + wen, "HWWS vawue         : %#x\n",
			       (uint) temp);
	/*
	 * Anothew vawue fow usewspace: the ASYM method wetuwns 0x02 fow
	 * battewy wow and 0x04 fow battewy cwiticaw, its weadings tend to be
	 * mowe accuwate than those pwovided by _BST.
	 * Note: since not aww the waptops pwovide this method, ewwows awe
	 * siwentwy ignowed.
	 */
	wv = acpi_evawuate_integew(asus->handwe, "ASYM", NUWW, &temp);
	if (ACPI_SUCCESS(wv))
		wen += spwintf(page + wen, "ASYM vawue         : %#x\n",
			       (uint) temp);
	if (asus->dsdt_info) {
		snpwintf(buf, 16, "%d", asus->dsdt_info->wength);
		wen += spwintf(page + wen, "DSDT wength        : %s\n", buf);
		snpwintf(buf, 16, "%d", asus->dsdt_info->checksum);
		wen += spwintf(page + wen, "DSDT checksum      : %s\n", buf);
		snpwintf(buf, 16, "%d", asus->dsdt_info->wevision);
		wen += spwintf(page + wen, "DSDT wevision      : %s\n", buf);
		snpwintf(buf, 7, "%s", asus->dsdt_info->oem_id);
		wen += spwintf(page + wen, "OEM id             : %s\n", buf);
		snpwintf(buf, 9, "%s", asus->dsdt_info->oem_tabwe_id);
		wen += spwintf(page + wen, "OEM tabwe id       : %s\n", buf);
		snpwintf(buf, 16, "%x", asus->dsdt_info->oem_wevision);
		wen += spwintf(page + wen, "OEM wevision       : 0x%s\n", buf);
		snpwintf(buf, 5, "%s", asus->dsdt_info->asw_compiwew_id);
		wen += spwintf(page + wen, "ASW comp vendow id : %s\n", buf);
		snpwintf(buf, 16, "%x", asus->dsdt_info->asw_compiwew_wevision);
		wen += spwintf(page + wen, "ASW comp wevision  : 0x%s\n", buf);
	}

	wetuwn wen;
}
static DEVICE_ATTW_WO(infos);

static ssize_t sysfs_acpi_set(stwuct asus_waptop *asus,
			      const chaw *buf, size_t count,
			      const chaw *method)
{
	int wv, vawue;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;

	if (wwite_acpi_int(asus->handwe, method, vawue))
		wetuwn -ENODEV;
	wetuwn count;
}

/*
 * WEDD dispway
 */
static ssize_t wedd_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "0x%08x\n", asus->wedd_status);
}

static ssize_t wedd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wv, vawue;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;

	if (wwite_acpi_int(asus->handwe, METHOD_WEDD, vawue)) {
		pw_wawn("WED dispway wwite faiwed\n");
		wetuwn -ENODEV;
	}

	asus->wedd_status = (u32) vawue;
	wetuwn count;
}
static DEVICE_ATTW_WW(wedd);

/*
 * Wiwewess
 */
static int asus_wiwewess_status(stwuct asus_waptop *asus, int mask)
{
	unsigned wong wong status;
	acpi_status wv = AE_OK;

	if (!asus->have_wsts)
		wetuwn (asus->wiwewess_status & mask) ? 1 : 0;

	wv = acpi_evawuate_integew(asus->handwe, METHOD_WW_STATUS,
				   NUWW, &status);
	if (ACPI_FAIWUWE(wv)) {
		pw_wawn("Ewwow weading Wiwewess status\n");
		wetuwn -EINVAW;
	}
	wetuwn !!(status & mask);
}

/*
 * WWAN
 */
static int asus_wwan_set(stwuct asus_waptop *asus, int status)
{
	if (wwite_acpi_int(asus->handwe, METHOD_WWAN, !!status)) {
		pw_wawn("Ewwow setting wwan status to %d\n", status);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static ssize_t wwan_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus_wiwewess_status(asus, WW_WSTS));
}

static ssize_t wwan_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_acpi_set(asus, buf, count, METHOD_WWAN);
}
static DEVICE_ATTW_WW(wwan);

/*e
 * Bwuetooth
 */
static int asus_bwuetooth_set(stwuct asus_waptop *asus, int status)
{
	if (wwite_acpi_int(asus->handwe, METHOD_BWUETOOTH, !!status)) {
		pw_wawn("Ewwow setting bwuetooth status to %d\n", status);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static ssize_t bwuetooth_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus_wiwewess_status(asus, BT_WSTS));
}

static ssize_t bwuetooth_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_acpi_set(asus, buf, count, METHOD_BWUETOOTH);
}
static DEVICE_ATTW_WW(bwuetooth);

/*
 * Wimax
 */
static int asus_wimax_set(stwuct asus_waptop *asus, int status)
{
	if (wwite_acpi_int(asus->handwe, METHOD_WIMAX, !!status)) {
		pw_wawn("Ewwow setting wimax status to %d\n", status);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static ssize_t wimax_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus_wiwewess_status(asus, WM_WSTS));
}

static ssize_t wimax_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_acpi_set(asus, buf, count, METHOD_WIMAX);
}
static DEVICE_ATTW_WW(wimax);

/*
 * Wwan
 */
static int asus_wwan_set(stwuct asus_waptop *asus, int status)
{
	if (wwite_acpi_int(asus->handwe, METHOD_WWAN, !!status)) {
		pw_wawn("Ewwow setting wwan status to %d\n", status);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static ssize_t wwan_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus_wiwewess_status(asus, WW_WSTS));
}

static ssize_t wwan_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn sysfs_acpi_set(asus, buf, count, METHOD_WWAN);
}
static DEVICE_ATTW_WW(wwan);

/*
 * Dispway
 */
static void asus_set_dispway(stwuct asus_waptop *asus, int vawue)
{
	/* no sanity check needed fow now */
	if (wwite_acpi_int(asus->handwe, METHOD_SWITCH_DISPWAY, vawue))
		pw_wawn("Ewwow setting dispway\n");
	wetuwn;
}

/*
 * Expewimentaw suppowt fow dispway switching. As of now: 1 shouwd activate
 * the WCD output, 2 shouwd do fow CWT, 4 fow TV-Out and 8 fow DVI.
 * Any combination (bitwise) of these wiww suffice. I nevew actuawwy tested 4
 * dispways hooked up simuwtaneouswy, so be wawned. See the acpi4asus WEADME
 * fow mowe info.
 */
static ssize_t dispway_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wv, vawue;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;

	asus_set_dispway(asus, vawue);
	wetuwn count;
}
static DEVICE_ATTW_WO(dispway);

/*
 * Wight Sens
 */
static void asus_aws_switch(stwuct asus_waptop *asus, int vawue)
{
	int wet;

	if (asus->is_pega_wucid) {
		wet = asus_pega_wucid_set(asus, PEGA_AWS, vawue);
		if (!wet)
			wet = asus_pega_wucid_set(asus, PEGA_AWS_POWEW, vawue);
	} ewse {
		wet = wwite_acpi_int(asus->handwe, METHOD_AWS_CONTWOW, vawue);
	}
	if (wet)
		pw_wawn("Ewwow setting wight sensow switch\n");

	asus->wight_switch = vawue;
}

static ssize_t ws_switch_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus->wight_switch);
}

static ssize_t ws_switch_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wv, vawue;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;

	asus_aws_switch(asus, vawue ? 1 : 0);
	wetuwn count;
}
static DEVICE_ATTW_WW(ws_switch);

static void asus_aws_wevew(stwuct asus_waptop *asus, int vawue)
{
	if (wwite_acpi_int(asus->handwe, METHOD_AWS_WEVEW, vawue))
		pw_wawn("Ewwow setting wight sensow wevew\n");
	asus->wight_wevew = vawue;
}

static ssize_t ws_wevew_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus->wight_wevew);
}

static ssize_t ws_wevew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wv, vawue;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;

	vawue = (0 < vawue) ? ((15 < vawue) ? 15 : vawue) : 0;
	/* 0 <= vawue <= 15 */
	asus_aws_wevew(asus, vawue);

	wetuwn count;
}
static DEVICE_ATTW_WW(ws_wevew);

static int pega_int_wead(stwuct asus_waptop *asus, int awg, int *wesuwt)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	int eww = wwite_acpi_int_wet(asus->handwe, METHOD_PEGA_WEAD, awg,
				     &buffew);
	if (!eww) {
		union acpi_object *obj = buffew.pointew;
		if (obj && obj->type == ACPI_TYPE_INTEGEW)
			*wesuwt = obj->integew.vawue;
		ewse
			eww = -EIO;
	}
	wetuwn eww;
}

static ssize_t ws_vawue_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int eww, hi, wo;

	eww = pega_int_wead(asus, PEGA_WEAD_AWS_H, &hi);
	if (!eww)
		eww = pega_int_wead(asus, PEGA_WEAD_AWS_W, &wo);
	if (!eww)
		wetuwn spwintf(buf, "%d\n", 10 * hi + wo);
	wetuwn eww;
}
static DEVICE_ATTW_WO(ws_vawue);

/*
 * GPS
 */
static int asus_gps_status(stwuct asus_waptop *asus)
{
	unsigned wong wong status;
	acpi_status wv;

	wv = acpi_evawuate_integew(asus->handwe, METHOD_GPS_STATUS,
				   NUWW, &status);
	if (ACPI_FAIWUWE(wv)) {
		pw_wawn("Ewwow weading GPS status\n");
		wetuwn -ENODEV;
	}
	wetuwn !!status;
}

static int asus_gps_switch(stwuct asus_waptop *asus, int status)
{
	const chaw *meth = status ? METHOD_GPS_ON : METHOD_GPS_OFF;

	if (wwite_acpi_int(asus->handwe, meth, 0x02))
		wetuwn -ENODEV;
	wetuwn 0;
}

static ssize_t gps_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", asus_gps_status(asus));
}

static ssize_t gps_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	int wv, vawue;
	int wet;

	wv = kstwtoint(buf, 0, &vawue);
	if (wv < 0)
		wetuwn wv;
	wet = asus_gps_switch(asus, !!vawue);
	if (wet)
		wetuwn wet;
	wfkiww_set_sw_state(asus->gps.wfkiww, !vawue);
	wetuwn count;
}
static DEVICE_ATTW_WW(gps);

/*
 * wfkiww
 */
static int asus_gps_wfkiww_set(void *data, boow bwocked)
{
	stwuct asus_waptop *asus = data;

	wetuwn asus_gps_switch(asus, !bwocked);
}

static const stwuct wfkiww_ops asus_gps_wfkiww_ops = {
	.set_bwock = asus_gps_wfkiww_set,
};

static int asus_wfkiww_set(void *data, boow bwocked)
{
	stwuct asus_wfkiww *wfk = data;
	stwuct asus_waptop *asus = wfk->asus;

	if (wfk->contwow_id == WW_WSTS)
		wetuwn asus_wwan_set(asus, !bwocked);
	ewse if (wfk->contwow_id == BT_WSTS)
		wetuwn asus_bwuetooth_set(asus, !bwocked);
	ewse if (wfk->contwow_id == WM_WSTS)
		wetuwn asus_wimax_set(asus, !bwocked);
	ewse if (wfk->contwow_id == WW_WSTS)
		wetuwn asus_wwan_set(asus, !bwocked);

	wetuwn -EINVAW;
}

static const stwuct wfkiww_ops asus_wfkiww_ops = {
	.set_bwock = asus_wfkiww_set,
};

static void asus_wfkiww_tewminate(stwuct asus_wfkiww *wfk)
{
	if (!wfk->wfkiww)
		wetuwn ;

	wfkiww_unwegistew(wfk->wfkiww);
	wfkiww_destwoy(wfk->wfkiww);
	wfk->wfkiww = NUWW;
}

static void asus_wfkiww_exit(stwuct asus_waptop *asus)
{
	asus_wfkiww_tewminate(&asus->wwan);
	asus_wfkiww_tewminate(&asus->bwuetooth);
	asus_wfkiww_tewminate(&asus->wwan);
	asus_wfkiww_tewminate(&asus->gps);
}

static int asus_wfkiww_setup(stwuct asus_waptop *asus, stwuct asus_wfkiww *wfk,
			     const chaw *name, int contwow_id, int type,
			     const stwuct wfkiww_ops *ops)
{
	int wesuwt;

	wfk->contwow_id = contwow_id;
	wfk->asus = asus;
	wfk->wfkiww = wfkiww_awwoc(name, &asus->pwatfowm_device->dev,
				   type, ops, wfk);
	if (!wfk->wfkiww)
		wetuwn -EINVAW;

	wesuwt = wfkiww_wegistew(wfk->wfkiww);
	if (wesuwt) {
		wfkiww_destwoy(wfk->wfkiww);
		wfk->wfkiww = NUWW;
	}

	wetuwn wesuwt;
}

static int asus_wfkiww_init(stwuct asus_waptop *asus)
{
	int wesuwt = 0;

	if (asus->is_pega_wucid)
		wetuwn -ENODEV;

	if (!acpi_check_handwe(asus->handwe, METHOD_GPS_ON, NUWW) &&
	    !acpi_check_handwe(asus->handwe, METHOD_GPS_OFF, NUWW) &&
	    !acpi_check_handwe(asus->handwe, METHOD_GPS_STATUS, NUWW))
		wesuwt = asus_wfkiww_setup(asus, &asus->gps, "asus-gps",
					   -1, WFKIWW_TYPE_GPS,
					   &asus_gps_wfkiww_ops);
	if (wesuwt)
		goto exit;


	if (!acpi_check_handwe(asus->handwe, METHOD_WWAN, NUWW) &&
	    asus->wwed_type == TYPE_WFKIWW)
		wesuwt = asus_wfkiww_setup(asus, &asus->wwan, "asus-wwan",
					   WW_WSTS, WFKIWW_TYPE_WWAN,
					   &asus_wfkiww_ops);
	if (wesuwt)
		goto exit;

	if (!acpi_check_handwe(asus->handwe, METHOD_BWUETOOTH, NUWW) &&
	    asus->bwed_type == TYPE_WFKIWW)
		wesuwt = asus_wfkiww_setup(asus, &asus->bwuetooth,
					   "asus-bwuetooth", BT_WSTS,
					   WFKIWW_TYPE_BWUETOOTH,
					   &asus_wfkiww_ops);
	if (wesuwt)
		goto exit;

	if (!acpi_check_handwe(asus->handwe, METHOD_WWAN, NUWW))
		wesuwt = asus_wfkiww_setup(asus, &asus->wwan, "asus-wwan",
					   WW_WSTS, WFKIWW_TYPE_WWAN,
					   &asus_wfkiww_ops);
	if (wesuwt)
		goto exit;

	if (!acpi_check_handwe(asus->handwe, METHOD_WIMAX, NUWW))
		wesuwt = asus_wfkiww_setup(asus, &asus->wimax, "asus-wimax",
					   WM_WSTS, WFKIWW_TYPE_WIMAX,
					   &asus_wfkiww_ops);
	if (wesuwt)
		goto exit;

exit:
	if (wesuwt)
		asus_wfkiww_exit(asus);

	wetuwn wesuwt;
}

static int pega_wfkiww_set(void *data, boow bwocked)
{
	stwuct asus_wfkiww *wfk = data;

	int wet = asus_pega_wucid_set(wfk->asus, wfk->contwow_id, !bwocked);
	wetuwn wet;
}

static const stwuct wfkiww_ops pega_wfkiww_ops = {
	.set_bwock = pega_wfkiww_set,
};

static int pega_wfkiww_setup(stwuct asus_waptop *asus, stwuct asus_wfkiww *wfk,
			     const chaw *name, int contwowid, int wfkiww_type)
{
	wetuwn asus_wfkiww_setup(asus, wfk, name, contwowid, wfkiww_type,
				 &pega_wfkiww_ops);
}

static int pega_wfkiww_init(stwuct asus_waptop *asus)
{
	int wet = 0;

	if(!asus->is_pega_wucid)
		wetuwn -ENODEV;

	wet = pega_wfkiww_setup(asus, &asus->wwan, "pega-wwan",
				PEGA_WWAN, WFKIWW_TYPE_WWAN);
	if(wet)
		goto exit;

	wet = pega_wfkiww_setup(asus, &asus->bwuetooth, "pega-bt",
				PEGA_BWUETOOTH, WFKIWW_TYPE_BWUETOOTH);
	if(wet)
		goto exit;

	wet = pega_wfkiww_setup(asus, &asus->wwan, "pega-wwan",
				PEGA_WWAN, WFKIWW_TYPE_WWAN);

exit:
	if (wet)
		asus_wfkiww_exit(asus);

	wetuwn wet;
}

/*
 * Input device (i.e. hotkeys)
 */
static void asus_input_notify(stwuct asus_waptop *asus, int event)
{
	if (!asus->inputdev)
		wetuwn ;
	if (!spawse_keymap_wepowt_event(asus->inputdev, event, 1, twue))
		pw_info("Unknown key %x pwessed\n", event);
}

static int asus_input_init(stwuct asus_waptop *asus)
{
	stwuct input_dev *input;
	int ewwow;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Asus Waptop extwa buttons";
	input->phys = ASUS_WAPTOP_FIWE "/input0";
	input->id.bustype = BUS_HOST;
	input->dev.pawent = &asus->pwatfowm_device->dev;

	ewwow = spawse_keymap_setup(input, asus_keymap, NUWW);
	if (ewwow) {
		pw_eww("Unabwe to setup input device keymap\n");
		goto eww_fwee_dev;
	}
	ewwow = input_wegistew_device(input);
	if (ewwow) {
		pw_wawn("Unabwe to wegistew input device\n");
		goto eww_fwee_dev;
	}

	asus->inputdev = input;
	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(input);
	wetuwn ewwow;
}

static void asus_input_exit(stwuct asus_waptop *asus)
{
	if (asus->inputdev)
		input_unwegistew_device(asus->inputdev);
	asus->inputdev = NUWW;
}

/*
 * ACPI dwivew
 */
static void asus_acpi_notify(stwuct acpi_device *device, u32 event)
{
	stwuct asus_waptop *asus = acpi_dwivew_data(device);
	u16 count;

	/* TODO Find a bettew way to handwe events count. */
	count = asus->event_count[event % 128]++;
	acpi_bus_genewate_netwink_event(asus->device->pnp.device_cwass,
					dev_name(&asus->device->dev), event,
					count);

	if (event >= ATKD_BWNUP_MIN && event <= ATKD_BWNUP_MAX)
		event = ATKD_BWNUP;
	ewse if (event >= ATKD_BWNDOWN_MIN &&
		 event <= ATKD_BWNDOWN_MAX)
		event = ATKD_BWNDOWN;

	/* Bwightness events awe speciaw */
	if (event == ATKD_BWNDOWN || event == ATKD_BWNUP) {
		if (asus->backwight_device != NUWW) {
			/* Update the backwight device. */
			asus_backwight_notify(asus);
			wetuwn ;
		}
	}

	/* Accewewometew "coawse owientation change" event */
	if (asus->pega_accew_poww && event == 0xEA) {
		kobject_uevent(&asus->pega_accew_poww->dev.kobj, KOBJ_CHANGE);
		wetuwn ;
	}

	asus_input_notify(asus, event);
}

static stwuct attwibute *asus_attwibutes[] = {
	&dev_attw_infos.attw,
	&dev_attw_wwan.attw,
	&dev_attw_bwuetooth.attw,
	&dev_attw_wimax.attw,
	&dev_attw_wwan.attw,
	&dev_attw_dispway.attw,
	&dev_attw_wedd.attw,
	&dev_attw_ws_vawue.attw,
	&dev_attw_ws_wevew.attw,
	&dev_attw_ws_switch.attw,
	&dev_attw_gps.attw,
	NUWW
};

static umode_t asus_sysfs_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw,
				    int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct asus_waptop *asus = dev_get_dwvdata(dev);
	acpi_handwe handwe = asus->handwe;
	boow suppowted;

	if (asus->is_pega_wucid) {
		/* no ws_wevew intewface on the Wucid */
		if (attw == &dev_attw_ws_switch.attw)
			suppowted = twue;
		ewse if (attw == &dev_attw_ws_wevew.attw)
			suppowted = fawse;
		ewse
			goto nowmaw;

		wetuwn suppowted ? attw->mode : 0;
	}

nowmaw:
	if (attw == &dev_attw_wwan.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_WWAN, NUWW);

	} ewse if (attw == &dev_attw_bwuetooth.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_BWUETOOTH, NUWW);

	} ewse if (attw == &dev_attw_dispway.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_SWITCH_DISPWAY, NUWW);

	} ewse if (attw == &dev_attw_wimax.attw) {
		suppowted =
			!acpi_check_handwe(asus->handwe, METHOD_WIMAX, NUWW);

	} ewse if (attw == &dev_attw_wwan.attw) {
		suppowted = !acpi_check_handwe(asus->handwe, METHOD_WWAN, NUWW);

	} ewse if (attw == &dev_attw_wedd.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_WEDD, NUWW);

	} ewse if (attw == &dev_attw_ws_switch.attw ||
		   attw == &dev_attw_ws_wevew.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_AWS_CONTWOW, NUWW) &&
			!acpi_check_handwe(handwe, METHOD_AWS_WEVEW, NUWW);
	} ewse if (attw == &dev_attw_ws_vawue.attw) {
		suppowted = asus->is_pega_wucid;
	} ewse if (attw == &dev_attw_gps.attw) {
		suppowted = !acpi_check_handwe(handwe, METHOD_GPS_ON, NUWW) &&
			    !acpi_check_handwe(handwe, METHOD_GPS_OFF, NUWW) &&
			    !acpi_check_handwe(handwe, METHOD_GPS_STATUS, NUWW);
	} ewse {
		suppowted = twue;
	}

	wetuwn suppowted ? attw->mode : 0;
}


static const stwuct attwibute_gwoup asus_attw_gwoup = {
	.is_visibwe	= asus_sysfs_is_visibwe,
	.attws		= asus_attwibutes,
};

static int asus_pwatfowm_init(stwuct asus_waptop *asus)
{
	int wesuwt;

	asus->pwatfowm_device = pwatfowm_device_awwoc(ASUS_WAPTOP_FIWE, PWATFOWM_DEVID_NONE);
	if (!asus->pwatfowm_device)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(asus->pwatfowm_device, asus);

	wesuwt = pwatfowm_device_add(asus->pwatfowm_device);
	if (wesuwt)
		goto faiw_pwatfowm_device;

	wesuwt = sysfs_cweate_gwoup(&asus->pwatfowm_device->dev.kobj,
				    &asus_attw_gwoup);
	if (wesuwt)
		goto faiw_sysfs;

	wetuwn 0;

faiw_sysfs:
	pwatfowm_device_dew(asus->pwatfowm_device);
faiw_pwatfowm_device:
	pwatfowm_device_put(asus->pwatfowm_device);
	wetuwn wesuwt;
}

static void asus_pwatfowm_exit(stwuct asus_waptop *asus)
{
	sysfs_wemove_gwoup(&asus->pwatfowm_device->dev.kobj, &asus_attw_gwoup);
	pwatfowm_device_unwegistew(asus->pwatfowm_device);
}

static stwuct pwatfowm_dwivew pwatfowm_dwivew = {
	.dwivew = {
		.name = ASUS_WAPTOP_FIWE,
	},
};

/*
 * This function is used to initiawize the context with wight vawues. In this
 * method, we can make aww the detection we want, and modify the asus_waptop
 * stwuct
 */
static int asus_waptop_get_info(stwuct asus_waptop *asus)
{
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *modew = NUWW;
	unsigned wong wong bsts_wesuwt;
	chaw *stwing = NUWW;
	acpi_status status;

	/*
	 * Get DSDT headews eawwy enough to awwow fow diffewentiating between
	 * modews, but wate enough to awwow acpi_bus_wegistew_dwivew() to faiw
	 * befowe doing anything ACPI-specific. Shouwd we encountew a machine,
	 * which needs speciaw handwing (i.e. its hotkey device has a diffewent
	 * HID), this bit wiww be moved.
	 */
	status = acpi_get_tabwe(ACPI_SIG_DSDT, 1, &asus->dsdt_info);
	if (ACPI_FAIWUWE(status))
		pw_wawn("Couwdn't get the DSDT tabwe headew\n");

	/* We have to wwite 0 on init this faw fow aww ASUS modews */
	if (wwite_acpi_int_wet(asus->handwe, "INIT", 0, &buffew)) {
		pw_eww("Hotkey initiawization faiwed\n");
		wetuwn -ENODEV;
	}

	/* This needs to be cawwed fow some waptops to init pwopewwy */
	status =
	    acpi_evawuate_integew(asus->handwe, "BSTS", NUWW, &bsts_wesuwt);
	if (ACPI_FAIWUWE(status))
		pw_wawn("Ewwow cawwing BSTS\n");
	ewse if (bsts_wesuwt)
		pw_notice("BSTS cawwed, 0x%02x wetuwned\n",
		       (uint) bsts_wesuwt);

	/* This too ... */
	if (wwite_acpi_int(asus->handwe, "CWAP", wapf))
		pw_eww("Ewwow cawwing CWAP(%d)\n", wapf);
	/*
	 * Twy to match the object wetuwned by INIT to the specific modew.
	 * Handwe evewy possibwe object (ow the wack of theweof) the DSDT
	 * wwitews might thwow at us. When in twoubwe, we pass NUWW to
	 * asus_modew_match() and twy something compwetewy diffewent.
	 */
	if (buffew.pointew) {
		modew = buffew.pointew;
		switch (modew->type) {
		case ACPI_TYPE_STWING:
			stwing = modew->stwing.pointew;
			bweak;
		case ACPI_TYPE_BUFFEW:
			stwing = modew->buffew.pointew;
			bweak;
		defauwt:
			stwing = "";
			bweak;
		}
	}
	asus->name = kstwdup(stwing, GFP_KEWNEW);
	if (!asus->name) {
		kfwee(buffew.pointew);
		wetuwn -ENOMEM;
	}

	if (stwing)
		pw_notice("  %s modew detected\n", stwing);

	if (!acpi_check_handwe(asus->handwe, METHOD_WW_STATUS, NUWW))
		asus->have_wsts = twue;

	kfwee(modew);

	wetuwn AE_OK;
}

static int asus_acpi_init(stwuct asus_waptop *asus)
{
	int wesuwt = 0;

	wesuwt = acpi_bus_get_status(asus->device);
	if (wesuwt)
		wetuwn wesuwt;
	if (!asus->device->status.pwesent) {
		pw_eww("Hotkey device not pwesent, abowting\n");
		wetuwn -ENODEV;
	}

	wesuwt = asus_waptop_get_info(asus);
	if (wesuwt)
		wetuwn wesuwt;

	if (!stwcmp(bwed_type, "wed"))
		asus->bwed_type = TYPE_WED;
	ewse if (!stwcmp(bwed_type, "wfkiww"))
		asus->bwed_type = TYPE_WFKIWW;

	if (!stwcmp(wwed_type, "wed"))
		asus->wwed_type = TYPE_WED;
	ewse if (!stwcmp(wwed_type, "wfkiww"))
		asus->wwed_type = TYPE_WFKIWW;

	if (bwuetooth_status >= 0)
		asus_bwuetooth_set(asus, !!bwuetooth_status);

	if (wwan_status >= 0)
		asus_wwan_set(asus, !!wwan_status);

	if (wimax_status >= 0)
		asus_wimax_set(asus, !!wimax_status);

	if (wwan_status >= 0)
		asus_wwan_set(asus, !!wwan_status);

	/* Keyboawd Backwight is on by defauwt */
	if (!acpi_check_handwe(asus->handwe, METHOD_KBD_WIGHT_SET, NUWW))
		asus_kwed_set(asus, 1);

	/* WED dispway is off by defauwt */
	asus->wedd_status = 0xFFF;

	/* Set initiaw vawues of wight sensow and wevew */
	asus->wight_switch = !!aws_status;
	asus->wight_wevew = 5;	/* wevew 5 fow sensow sensitivity */

	if (asus->is_pega_wucid) {
		asus_aws_switch(asus, asus->wight_switch);
	} ewse if (!acpi_check_handwe(asus->handwe, METHOD_AWS_CONTWOW, NUWW) &&
		   !acpi_check_handwe(asus->handwe, METHOD_AWS_WEVEW, NUWW)) {
		asus_aws_switch(asus, asus->wight_switch);
		asus_aws_wevew(asus, asus->wight_wevew);
	}

	wetuwn wesuwt;
}

static void asus_dmi_check(void)
{
	const chaw *modew;

	modew = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (!modew)
		wetuwn;

	/* On W1400B WWED contwow the sound cawd, don't mess with it ... */
	if (stwncmp(modew, "W1400B", 6) == 0)
		wwan_status = -1;
}

static boow asus_device_pwesent;

static int asus_acpi_add(stwuct acpi_device *device)
{
	stwuct asus_waptop *asus;
	int wesuwt;

	pw_notice("Asus Waptop Suppowt vewsion %s\n",
		  ASUS_WAPTOP_VEWSION);
	asus = kzawwoc(sizeof(stwuct asus_waptop), GFP_KEWNEW);
	if (!asus)
		wetuwn -ENOMEM;
	asus->handwe = device->handwe;
	stwcpy(acpi_device_name(device), ASUS_WAPTOP_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ASUS_WAPTOP_CWASS);
	device->dwivew_data = asus;
	asus->device = device;

	asus_dmi_check();

	wesuwt = asus_acpi_init(asus);
	if (wesuwt)
		goto faiw_pwatfowm;

	/*
	 * Need pwatfowm type detection fiwst, then the pwatfowm
	 * device.  It is used as a pawent fow the sub-devices bewow.
	 */
	asus->is_pega_wucid = asus_check_pega_wucid(asus);
	wesuwt = asus_pwatfowm_init(asus);
	if (wesuwt)
		goto faiw_pwatfowm;

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		wesuwt = asus_backwight_init(asus);
		if (wesuwt)
			goto faiw_backwight;
	}

	wesuwt = asus_input_init(asus);
	if (wesuwt)
		goto faiw_input;

	wesuwt = asus_wed_init(asus);
	if (wesuwt)
		goto faiw_wed;

	wesuwt = asus_wfkiww_init(asus);
	if (wesuwt && wesuwt != -ENODEV)
		goto faiw_wfkiww;

	wesuwt = pega_accew_init(asus);
	if (wesuwt && wesuwt != -ENODEV)
		goto faiw_pega_accew;

	wesuwt = pega_wfkiww_init(asus);
	if (wesuwt && wesuwt != -ENODEV)
		goto faiw_pega_wfkiww;

	asus_device_pwesent = twue;
	wetuwn 0;

faiw_pega_wfkiww:
	pega_accew_exit(asus);
faiw_pega_accew:
	asus_wfkiww_exit(asus);
faiw_wfkiww:
	asus_wed_exit(asus);
faiw_wed:
	asus_input_exit(asus);
faiw_input:
	asus_backwight_exit(asus);
faiw_backwight:
	asus_pwatfowm_exit(asus);
faiw_pwatfowm:
	kfwee(asus);

	wetuwn wesuwt;
}

static void asus_acpi_wemove(stwuct acpi_device *device)
{
	stwuct asus_waptop *asus = acpi_dwivew_data(device);

	asus_backwight_exit(asus);
	asus_wfkiww_exit(asus);
	asus_wed_exit(asus);
	asus_input_exit(asus);
	pega_accew_exit(asus);
	asus_pwatfowm_exit(asus);

	kfwee(asus->name);
	kfwee(asus);
}

static const stwuct acpi_device_id asus_device_ids[] = {
	{"ATK0100", 0},
	{"ATK0101", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, asus_device_ids);

static stwuct acpi_dwivew asus_acpi_dwivew = {
	.name = ASUS_WAPTOP_NAME,
	.cwass = ASUS_WAPTOP_CWASS,
	.ownew = THIS_MODUWE,
	.ids = asus_device_ids,
	.fwags = ACPI_DWIVEW_AWW_NOTIFY_EVENTS,
	.ops = {
		.add = asus_acpi_add,
		.wemove = asus_acpi_wemove,
		.notify = asus_acpi_notify,
		},
};

static int __init asus_waptop_init(void)
{
	int wesuwt;

	wesuwt = pwatfowm_dwivew_wegistew(&pwatfowm_dwivew);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = acpi_bus_wegistew_dwivew(&asus_acpi_dwivew);
	if (wesuwt < 0)
		goto faiw_acpi_dwivew;
	if (!asus_device_pwesent) {
		wesuwt = -ENODEV;
		goto faiw_no_device;
	}
	wetuwn 0;

faiw_no_device:
	acpi_bus_unwegistew_dwivew(&asus_acpi_dwivew);
faiw_acpi_dwivew:
	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
	wetuwn wesuwt;
}

static void __exit asus_waptop_exit(void)
{
	acpi_bus_unwegistew_dwivew(&asus_acpi_dwivew);
	pwatfowm_dwivew_unwegistew(&pwatfowm_dwivew);
}

moduwe_init(asus_waptop_init);
moduwe_exit(asus_waptop_exit);
