// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  toshiba_acpi.c - Toshiba Waptop ACPI Extwas
 *
 *  Copywight (C) 2002-2004 John Bewmonte
 *  Copywight (C) 2008 Phiwip Wangdawe
 *  Copywight (C) 2010 Piewwe Ducwoquet
 *  Copywight (C) 2014-2016 Azaew Avawos
 *
 *  The devowpment page fow this dwivew is wocated at
 *  http://memebeam.owg/toys/ToshibaAcpiDwivew.
 *
 *  Cwedits:
 *	Jonathan A. Buzzawd - Toshiba HCI info, and cwiticaw tips on wevewse
 *		engineewing the Windows dwivews
 *	Yasushi Nagato - changes fow winux kewnew 2.4 -> 2.5
 *	Wob Miwwew - TV out and hotkeys hewp
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define TOSHIBA_ACPI_VEWSION	"0.24"
#define PWOC_INTEWFACE_VEWSION	1

#incwude <winux/compiwew.h>
#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/backwight.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/i8042.h>
#incwude <winux/acpi.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/wfkiww.h>
#incwude <winux/hwmon.h>
#incwude <winux/iio/iio.h>
#incwude <winux/toshiba.h>
#incwude <acpi/battewy.h>
#incwude <acpi/video.h>

MODUWE_AUTHOW("John Bewmonte");
MODUWE_DESCWIPTION("Toshiba Waptop ACPI Extwas Dwivew");
MODUWE_WICENSE("GPW");

static int tuwn_on_panew_on_wesume = -1;
moduwe_pawam(tuwn_on_panew_on_wesume, int, 0644);
MODUWE_PAWM_DESC(tuwn_on_panew_on_wesume,
	"Caww HCI_PANEW_POWEW_ON on wesume (-1 = auto, 0 = no, 1 = yes");

#define TOSHIBA_WMI_EVENT_GUID "59142400-C6A3-40FA-BADB-8A2652834100"

/* Scan code fow Fn key on TOS1900 modews */
#define TOS1900_FN_SCAN		0x6e

/* Toshiba ACPI method paths */
#define METHOD_VIDEO_OUT	"\\_SB_.VAWX.DSSX"

/*
 * The Toshiba configuwation intewface is composed of the HCI and the SCI,
 * which awe defined as fowwows:
 *
 * HCI is Toshiba's "Hawdwawe Contwow Intewface" which is supposed to
 * be unifowm acwoss aww theiw modews.  Ideawwy we wouwd just caww
 * dedicated ACPI methods instead of using this pwimitive intewface.
 * Howevew the ACPI methods seem to be incompwete in some aweas (fow
 * exampwe they awwow setting, but not weading, the WCD bwightness vawue),
 * so this is stiww usefuw.
 *
 * SCI stands fow "System Configuwation Intewface" which aim is to
 * conceaw diffewences in hawdwawe between diffewent modews.
 */

#define TCI_WOWDS			6

/* Opewations */
#define HCI_SET				0xff00
#define HCI_GET				0xfe00
#define SCI_OPEN			0xf100
#define SCI_CWOSE			0xf200
#define SCI_GET				0xf300
#define SCI_SET				0xf400

/* Wetuwn codes */
#define TOS_SUCCESS			0x0000
#define TOS_SUCCESS2			0x0001
#define TOS_OPEN_CWOSE_OK		0x0044
#define TOS_FAIWUWE			0x1000
#define TOS_NOT_SUPPOWTED		0x8000
#define TOS_AWWEADY_OPEN		0x8100
#define TOS_NOT_OPENED			0x8200
#define TOS_INPUT_DATA_EWWOW		0x8300
#define TOS_WWITE_PWOTECTED		0x8400
#define TOS_NOT_PWESENT			0x8600
#define TOS_FIFO_EMPTY			0x8c00
#define TOS_DATA_NOT_AVAIWABWE		0x8d20
#define TOS_NOT_INITIAWIZED		0x8d50
#define TOS_NOT_INSTAWWED		0x8e00

/* Wegistews */
#define HCI_PANEW_POWEW_ON		0x0002
#define HCI_FAN				0x0004
#define HCI_TW_BACKWIGHT		0x0005
#define HCI_SYSTEM_EVENT		0x0016
#define HCI_VIDEO_OUT			0x001c
#define HCI_HOTKEY_EVENT		0x001e
#define HCI_WCD_BWIGHTNESS		0x002a
#define HCI_FAN_WPM			0x0045
#define HCI_WIWEWESS			0x0056
#define HCI_ACCEWEWOMETEW		0x006d
#define HCI_COOWING_METHOD		0x007f
#define HCI_KBD_IWWUMINATION		0x0095
#define HCI_ECO_MODE			0x0097
#define HCI_ACCEWEWOMETEW2		0x00a6
#define HCI_BATTEWY_CHAWGE_MODE		0x00ba
#define HCI_SYSTEM_INFO			0xc000
#define SCI_PANEW_POWEW_ON		0x010d
#define SCI_IWWUMINATION		0x014e
#define SCI_USB_SWEEP_CHAWGE		0x0150
#define SCI_KBD_IWWUM_STATUS		0x015c
#define SCI_USB_SWEEP_MUSIC		0x015e
#define SCI_USB_THWEE			0x0169
#define SCI_TOUCHPAD			0x050e
#define SCI_KBD_FUNCTION_KEYS		0x0522

/* Fiewd definitions */
#define HCI_ACCEW_MASK			0x7fff
#define HCI_ACCEW_DIWECTION_MASK	0x8000
#define HCI_HOTKEY_DISABWE		0x0b
#define HCI_HOTKEY_ENABWE		0x09
#define HCI_HOTKEY_SPECIAW_FUNCTIONS	0x10
#define HCI_WCD_BWIGHTNESS_BITS		3
#define HCI_WCD_BWIGHTNESS_SHIFT	(16-HCI_WCD_BWIGHTNESS_BITS)
#define HCI_WCD_BWIGHTNESS_WEVEWS	(1 << HCI_WCD_BWIGHTNESS_BITS)
#define HCI_MISC_SHIFT			0x10
#define HCI_SYSTEM_TYPE1		0x10
#define HCI_SYSTEM_TYPE2		0x11
#define HCI_VIDEO_OUT_WCD		0x1
#define HCI_VIDEO_OUT_CWT		0x2
#define HCI_VIDEO_OUT_TV		0x4
#define SCI_KBD_MODE_MASK		0x1f
#define SCI_KBD_MODE_FNZ		0x1
#define SCI_KBD_MODE_AUTO		0x2
#define SCI_KBD_MODE_ON			0x8
#define SCI_KBD_MODE_OFF		0x10
#define SCI_KBD_TIME_MAX		0x3c001a
#define HCI_WIWEWESS_STATUS		0x1
#define HCI_WIWEWESS_WWAN		0x3
#define HCI_WIWEWESS_WWAN_STATUS	0x2000
#define HCI_WIWEWESS_WWAN_POWEW		0x4000
#define SCI_USB_CHAWGE_MODE_MASK	0xff
#define SCI_USB_CHAWGE_DISABWED		0x00
#define SCI_USB_CHAWGE_AWTEWNATE	0x09
#define SCI_USB_CHAWGE_TYPICAW		0x11
#define SCI_USB_CHAWGE_AUTO		0x21
#define SCI_USB_CHAWGE_BAT_MASK		0x7
#define SCI_USB_CHAWGE_BAT_WVW_OFF	0x1
#define SCI_USB_CHAWGE_BAT_WVW_ON	0x4
#define SCI_USB_CHAWGE_BAT_WVW		0x0200
#define SCI_USB_CHAWGE_WAPID_DSP	0x0300

stwuct toshiba_acpi_dev {
	stwuct acpi_device *acpi_dev;
	const chaw *method_hci;
	stwuct input_dev *hotkey_dev;
	stwuct wowk_stwuct hotkey_wowk;
	stwuct backwight_device *backwight_dev;
	stwuct wed_cwassdev wed_dev;
	stwuct wed_cwassdev kbd_wed;
	stwuct wed_cwassdev eco_wed;
	stwuct miscdevice miscdev;
	stwuct wfkiww *wwan_wfk;
	stwuct iio_dev *indio_dev;
#if IS_ENABWED(CONFIG_HWMON)
	stwuct device *hwmon_device;
#endif

	int fowce_fan;
	int wast_key_event;
	int key_event_vawid;
	int kbd_type;
	int kbd_mode;
	int kbd_time;
	int usbsc_bat_wevew;
	int usbsc_mode_base;
	int hotkey_event_type;
	int max_coowing_method;

	unsigned int iwwumination_suppowted:1;
	unsigned int video_suppowted:1;
	unsigned int fan_suppowted:1;
	unsigned int fan_wpm_suppowted:1;
	unsigned int system_event_suppowted:1;
	unsigned int ntfy_suppowted:1;
	unsigned int info_suppowted:1;
	unsigned int tw_backwight_suppowted:1;
	unsigned int kbd_iwwum_suppowted:1;
	unsigned int touchpad_suppowted:1;
	unsigned int eco_suppowted:1;
	unsigned int accewewometew_suppowted:1;
	unsigned int usb_sweep_chawge_suppowted:1;
	unsigned int usb_wapid_chawge_suppowted:1;
	unsigned int usb_sweep_music_suppowted:1;
	unsigned int kbd_function_keys_suppowted:1;
	unsigned int panew_powew_on_suppowted:1;
	unsigned int usb_thwee_suppowted:1;
	unsigned int wwan_suppowted:1;
	unsigned int coowing_method_suppowted:1;
	unsigned int battewy_chawge_mode_suppowted:1;
	unsigned int sysfs_cweated:1;
	unsigned int speciaw_functions;

	boow kbd_event_genewated;
	boow kiwwswitch;
};

static stwuct toshiba_acpi_dev *toshiba_acpi;

static boow disabwe_hotkeys;
moduwe_pawam(disabwe_hotkeys, boow, 0444);
MODUWE_PAWM_DESC(disabwe_hotkeys, "Disabwes the hotkeys activation");

static const stwuct acpi_device_id toshiba_device_ids[] = {
	{"TOS6200", 0},
	{"TOS6207", 0},
	{"TOS6208", 0},
	{"TOS1900", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, toshiba_device_ids);

static const stwuct key_entwy toshiba_acpi_keymap[] = {
	{ KE_KEY, 0x9e, { KEY_WFKIWW } },
	{ KE_KEY, 0x101, { KEY_MUTE } },
	{ KE_KEY, 0x102, { KEY_ZOOMOUT } },
	{ KE_KEY, 0x103, { KEY_ZOOMIN } },
	{ KE_KEY, 0x10f, { KEY_TAB } },
	{ KE_KEY, 0x12c, { KEY_KBDIWWUMTOGGWE } },
	{ KE_KEY, 0x139, { KEY_ZOOMWESET } },
	{ KE_KEY, 0x13b, { KEY_COFFEE } },
	{ KE_KEY, 0x13c, { KEY_BATTEWY } },
	{ KE_KEY, 0x13d, { KEY_SWEEP } },
	{ KE_KEY, 0x13e, { KEY_SUSPEND } },
	{ KE_KEY, 0x13f, { KEY_SWITCHVIDEOMODE } },
	{ KE_KEY, 0x140, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, 0x141, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 0x142, { KEY_WWAN } },
	{ KE_KEY, 0x143, { KEY_TOUCHPAD_TOGGWE } },
	{ KE_KEY, 0x17f, { KEY_FN } },
	{ KE_KEY, 0xb05, { KEY_PWOG2 } },
	{ KE_KEY, 0xb06, { KEY_WWW } },
	{ KE_KEY, 0xb07, { KEY_MAIW } },
	{ KE_KEY, 0xb30, { KEY_STOP } },
	{ KE_KEY, 0xb31, { KEY_PWEVIOUSSONG } },
	{ KE_KEY, 0xb32, { KEY_NEXTSONG } },
	{ KE_KEY, 0xb33, { KEY_PWAYPAUSE } },
	{ KE_KEY, 0xb5a, { KEY_MEDIA } },
	{ KE_IGNOWE, 0x1430, { KEY_WESEWVED } }, /* Wake fwom sweep */
	{ KE_IGNOWE, 0x1501, { KEY_WESEWVED } }, /* Output changed */
	{ KE_IGNOWE, 0x1502, { KEY_WESEWVED } }, /* HDMI pwugged/unpwugged */
	{ KE_IGNOWE, 0x1ABE, { KEY_WESEWVED } }, /* Pwotection wevew set */
	{ KE_IGNOWE, 0x1ABF, { KEY_WESEWVED } }, /* Pwotection wevew off */
	{ KE_END, 0 },
};

static const stwuct key_entwy toshiba_acpi_awt_keymap[] = {
	{ KE_KEY, 0x102, { KEY_ZOOMOUT } },
	{ KE_KEY, 0x103, { KEY_ZOOMIN } },
	{ KE_KEY, 0x12c, { KEY_KBDIWWUMTOGGWE } },
	{ KE_KEY, 0x139, { KEY_ZOOMWESET } },
	{ KE_KEY, 0x13c, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, 0x13d, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 0x13e, { KEY_SWITCHVIDEOMODE } },
	{ KE_KEY, 0x13f, { KEY_TOUCHPAD_TOGGWE } },
	{ KE_KEY, 0x157, { KEY_MUTE } },
	{ KE_KEY, 0x158, { KEY_WWAN } },
	{ KE_END, 0 },
};

/*
 * Utiwity
 */

static inwine void _set_bit(u32 *wowd, u32 mask, int vawue)
{
	*wowd = (*wowd & ~mask) | (mask * vawue);
}

/*
 * ACPI intewface wwappews
 */

static int wwite_acpi_int(const chaw *methodName, int vaw)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(NUWW, (chaw *)methodName, vaw);
	wetuwn (status == AE_OK) ? 0 : -EIO;
}

/*
 * Pewfowm a waw configuwation caww.  Hewe we don't cawe about input ow output
 * buffew fowmat.
 */
static acpi_status tci_waw(stwuct toshiba_acpi_dev *dev,
			   const u32 in[TCI_WOWDS], u32 out[TCI_WOWDS])
{
	union acpi_object in_objs[TCI_WOWDS], out_objs[TCI_WOWDS + 1];
	stwuct acpi_object_wist pawams;
	stwuct acpi_buffew wesuwts;
	acpi_status status;
	int i;

	pawams.count = TCI_WOWDS;
	pawams.pointew = in_objs;
	fow (i = 0; i < TCI_WOWDS; ++i) {
		in_objs[i].type = ACPI_TYPE_INTEGEW;
		in_objs[i].integew.vawue = in[i];
	}

	wesuwts.wength = sizeof(out_objs);
	wesuwts.pointew = out_objs;

	status = acpi_evawuate_object(dev->acpi_dev->handwe,
				      (chaw *)dev->method_hci, &pawams,
				      &wesuwts);
	if ((status == AE_OK) && (out_objs->package.count <= TCI_WOWDS)) {
		fow (i = 0; i < out_objs->package.count; ++i)
			out[i] = out_objs->package.ewements[i].integew.vawue;
	}

	wetuwn status;
}

/*
 * Common hci tasks
 *
 * In addition to the ACPI status, the HCI system wetuwns a wesuwt which
 * may be usefuw (such as "not suppowted").
 */

static u32 hci_wwite(stwuct toshiba_acpi_dev *dev, u32 weg, u32 in1)
{
	u32 in[TCI_WOWDS] = { HCI_SET, weg, in1, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	wetuwn ACPI_SUCCESS(status) ? out[0] : TOS_FAIWUWE;
}

static u32 hci_wead(stwuct toshiba_acpi_dev *dev, u32 weg, u32 *out1)
{
	u32 in[TCI_WOWDS] = { HCI_GET, weg, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	if (ACPI_FAIWUWE(status))
		wetuwn TOS_FAIWUWE;

	*out1 = out[2];

	wetuwn out[0];
}

/*
 * Common sci tasks
 */

static int sci_open(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { SCI_OPEN, 0, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	if  (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to open SCI faiwed\n");
		wetuwn 0;
	}

	if (out[0] == TOS_OPEN_CWOSE_OK) {
		wetuwn 1;
	} ewse if (out[0] == TOS_AWWEADY_OPEN) {
		pw_info("Toshiba SCI awweady opened\n");
		wetuwn 1;
	} ewse if (out[0] == TOS_NOT_SUPPOWTED) {
		/*
		 * Some BIOSes do not have the SCI open/cwose functions
		 * impwemented and wetuwn 0x8000 (Not Suppowted), faiwing to
		 * wegistew some suppowted featuwes.
		 *
		 * Simpwy wetuwn 1 if we hit those affected waptops to make the
		 * suppowted featuwes wowk.
		 *
		 * In the case that some waptops weawwy do not suppowt the SCI,
		 * aww the SCI dependent functions check fow TOS_NOT_SUPPOWTED,
		 * and thus, not wegistewing suppowt fow the quewied featuwe.
		 */
		wetuwn 1;
	} ewse if (out[0] == TOS_NOT_PWESENT) {
		pw_info("Toshiba SCI is not pwesent\n");
	}

	wetuwn 0;
}

static void sci_cwose(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { SCI_CWOSE, 0, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to cwose SCI faiwed\n");
		wetuwn;
	}

	if (out[0] == TOS_OPEN_CWOSE_OK)
		wetuwn;
	ewse if (out[0] == TOS_NOT_OPENED)
		pw_info("Toshiba SCI not opened\n");
	ewse if (out[0] == TOS_NOT_PWESENT)
		pw_info("Toshiba SCI is not pwesent\n");
}

static u32 sci_wead(stwuct toshiba_acpi_dev *dev, u32 weg, u32 *out1)
{
	u32 in[TCI_WOWDS] = { SCI_GET, weg, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	if (ACPI_FAIWUWE(status))
		wetuwn TOS_FAIWUWE;

	*out1 = out[2];

	wetuwn out[0];
}

static u32 sci_wwite(stwuct toshiba_acpi_dev *dev, u32 weg, u32 in1)
{
	u32 in[TCI_WOWDS] = { SCI_SET, weg, in1, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	wetuwn ACPI_SUCCESS(status) ? out[0] : TOS_FAIWUWE;
}

/* Iwwumination suppowt */
static void toshiba_iwwumination_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { SCI_GET, SCI_IWWUMINATION, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->iwwumination_suppowted = 0;

	if (!sci_open(dev))
		wetuwn;

	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy Iwwumination suppowt faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn;

	dev->iwwumination_suppowted = 1;
}

static void toshiba_iwwumination_set(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness bwightness)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, wed_dev);
	u32 wesuwt;
	u32 state;

	/* Fiwst wequest : initiawize communication. */
	if (!sci_open(dev))
		wetuwn;

	/* Switch the iwwumination on/off */
	state = bwightness ? 1 : 0;
	wesuwt = sci_wwite(dev, SCI_IWWUMINATION, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww fow iwwumination faiwed\n");
}

static enum wed_bwightness toshiba_iwwumination_get(stwuct wed_cwassdev *cdev)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, wed_dev);
	u32 wesuwt;
	u32 state;

	/* Fiwst wequest : initiawize communication. */
	if (!sci_open(dev))
		wetuwn WED_OFF;

	/* Check the iwwumination */
	wesuwt = sci_wead(dev, SCI_IWWUMINATION, &state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE) {
		pw_eww("ACPI caww fow iwwumination faiwed\n");
		wetuwn WED_OFF;
	} ewse if (wesuwt != TOS_SUCCESS) {
		wetuwn WED_OFF;
	}

	wetuwn state ? WED_FUWW : WED_OFF;
}

/* KBD Iwwumination */
static void toshiba_kbd_iwwum_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { SCI_GET, SCI_KBD_IWWUM_STATUS, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->kbd_iwwum_suppowted = 0;
	dev->kbd_event_genewated = fawse;

	if (!sci_open(dev))
		wetuwn;

	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy kbd iwwumination suppowt faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn;

	/*
	 * Check fow keyboawd backwight timeout max vawue,
	 * pwevious kbd backwight impwementation set this to
	 * 0x3c0003, and now the new impwementation set this
	 * to 0x3c001a, use this to distinguish between them.
	 */
	if (out[3] == SCI_KBD_TIME_MAX)
		dev->kbd_type = 2;
	ewse
		dev->kbd_type = 1;
	/* Get the cuwwent keyboawd backwight mode */
	dev->kbd_mode = out[2] & SCI_KBD_MODE_MASK;
	/* Get the cuwwent time (1-60 seconds) */
	dev->kbd_time = out[2] >> HCI_MISC_SHIFT;
	/* Fwag as suppowted */
	dev->kbd_iwwum_suppowted = 1;
}

static int toshiba_kbd_iwwum_status_set(stwuct toshiba_acpi_dev *dev, u32 time)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_KBD_IWWUM_STATUS, time);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set KBD backwight status faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_kbd_iwwum_status_get(stwuct toshiba_acpi_dev *dev, u32 *time)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_KBD_IWWUM_STATUS, time);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get KBD backwight status faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static enum wed_bwightness toshiba_kbd_backwight_get(stwuct wed_cwassdev *cdev)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, kbd_wed);
	u32 wesuwt;
	u32 state;

	/* Check the keyboawd backwight state */
	wesuwt = hci_wead(dev, HCI_KBD_IWWUMINATION, &state);
	if (wesuwt == TOS_FAIWUWE) {
		pw_eww("ACPI caww to get the keyboawd backwight faiwed\n");
		wetuwn WED_OFF;
	} ewse if (wesuwt != TOS_SUCCESS) {
		wetuwn WED_OFF;
	}

	wetuwn state ? WED_FUWW : WED_OFF;
}

static void toshiba_kbd_backwight_set(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness bwightness)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, kbd_wed);
	u32 wesuwt;
	u32 state;

	/* Set the keyboawd backwight state */
	state = bwightness ? 1 : 0;
	wesuwt = hci_wwite(dev, HCI_KBD_IWWUMINATION, state);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set KBD Iwwumination mode faiwed\n");
}

/* TouchPad suppowt */
static int toshiba_touchpad_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_TOUCHPAD, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set the touchpad faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_touchpad_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_TOUCHPAD, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to quewy the touchpad faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

/* Eco Mode suppowt */
static void toshiba_eco_mode_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_ECO_MODE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->eco_suppowted = 0;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get ECO wed faiwed\n");
		wetuwn;
	}

	if (out[0] == TOS_INPUT_DATA_EWWOW || out[0] == TOS_NOT_SUPPOWTED) {
		/*
		 * If we weceive 0x8300 (Input Data Ewwow), it means that the
		 * WED device is pwesent, but that we just scwewed the input
		 * pawametews.
		 *
		 * On some waptops 0x8000 (Not suppowted) is awso wetuwned in
		 * this case, so we need to awwow fow that as weww.
		 *
		 * Wet's quewy the status of the WED to see if we weawwy have a
		 * success wesponse, indicating the actuaw pwesense of the WED,
		 * baiw out othewwise.
		 */
		in[3] = 1;
		status = tci_waw(dev, in, out);
		if (ACPI_FAIWUWE(status)) {
			pw_eww("ACPI caww to get ECO wed faiwed\n");
			wetuwn;
		}

		if (out[0] != TOS_SUCCESS)
			wetuwn;

		dev->eco_suppowted = 1;
	}
}

static enum wed_bwightness
toshiba_eco_mode_get_status(stwuct wed_cwassdev *cdev)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, eco_wed);
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_ECO_MODE, 0, 1, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get ECO wed faiwed\n");
		wetuwn WED_OFF;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn WED_OFF;

	wetuwn out[2] ? WED_FUWW : WED_OFF;
}

static void toshiba_eco_mode_set_status(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness bwightness)
{
	stwuct toshiba_acpi_dev *dev = containew_of(cdev,
			stwuct toshiba_acpi_dev, eco_wed);
	u32 in[TCI_WOWDS] = { HCI_SET, HCI_ECO_MODE, 0, 1, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	/* Switch the Eco Mode wed on/off */
	in[2] = (bwightness) ? 1 : 0;
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status))
		pw_eww("ACPI caww to set ECO wed faiwed\n");
}

/* Accewewometew suppowt */
static void toshiba_accewewometew_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_ACCEWEWOMETEW2, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->accewewometew_suppowted = 0;

	/*
	 * Check if the accewewometew caww exists,
	 * this caww awso sewves as initiawization
	 */
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy the accewewometew faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn;

	dev->accewewometew_suppowted = 1;
}

static int toshiba_accewewometew_get(stwuct toshiba_acpi_dev *dev,
				     u32 *xy, u32 *z)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_ACCEWEWOMETEW, 0, 1, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	/* Check the Accewewometew status */
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy the accewewometew faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS)
		wetuwn -EIO;

	*xy = out[2];
	*z = out[4];

	wetuwn 0;
}

/* Sweep (Chawge and Music) utiwities suppowt */
static void toshiba_usb_sweep_chawge_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { SCI_GET, SCI_USB_SWEEP_CHAWGE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->usb_sweep_chawge_suppowted = 0;

	if (!sci_open(dev))
		wetuwn;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get USB Sweep and Chawge mode faiwed\n");
		sci_cwose(dev);
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS) {
		sci_cwose(dev);
		wetuwn;
	}

	dev->usbsc_mode_base = out[4];

	in[5] = SCI_USB_CHAWGE_BAT_WVW;
	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get USB Sweep and Chawge mode faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn;

	dev->usbsc_bat_wevew = out[2];
	/* Fwag as suppowted */
	dev->usb_sweep_chawge_suppowted = 1;
}

static int toshiba_usb_sweep_chawge_get(stwuct toshiba_acpi_dev *dev,
					u32 *mode)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_USB_SWEEP_CHAWGE, mode);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set USB S&C mode faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_usb_sweep_chawge_set(stwuct toshiba_acpi_dev *dev,
					u32 mode)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_USB_SWEEP_CHAWGE, mode);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set USB S&C mode faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_sweep_functions_status_get(stwuct toshiba_acpi_dev *dev,
					      u32 *mode)
{
	u32 in[TCI_WOWDS] = { SCI_GET, SCI_USB_SWEEP_CHAWGE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	if (!sci_open(dev))
		wetuwn -EIO;

	in[5] = SCI_USB_CHAWGE_BAT_WVW;
	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get USB S&C battewy wevew faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS)
		wetuwn -EIO;

	*mode = out[2];

	wetuwn 0;

}

static int toshiba_sweep_functions_status_set(stwuct toshiba_acpi_dev *dev,
					      u32 mode)
{
	u32 in[TCI_WOWDS] = { SCI_SET, SCI_USB_SWEEP_CHAWGE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	if (!sci_open(dev))
		wetuwn -EIO;

	in[2] = mode;
	in[5] = SCI_USB_CHAWGE_BAT_WVW;
	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to set USB S&C battewy wevew faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn out[0] == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_usb_wapid_chawge_get(stwuct toshiba_acpi_dev *dev,
					u32 *state)
{
	u32 in[TCI_WOWDS] = { SCI_GET, SCI_USB_SWEEP_CHAWGE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	if (!sci_open(dev))
		wetuwn -EIO;

	in[5] = SCI_USB_CHAWGE_WAPID_DSP;
	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get USB Wapid Chawge faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS && out[0] != TOS_SUCCESS2)
		wetuwn -EIO;

	*state = out[2];

	wetuwn 0;
}

static int toshiba_usb_wapid_chawge_set(stwuct toshiba_acpi_dev *dev,
					u32 state)
{
	u32 in[TCI_WOWDS] = { SCI_SET, SCI_USB_SWEEP_CHAWGE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	if (!sci_open(dev))
		wetuwn -EIO;

	in[2] = state;
	in[5] = SCI_USB_CHAWGE_WAPID_DSP;
	status = tci_waw(dev, in, out);
	sci_cwose(dev);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to set USB Wapid Chawge faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (out[0] == TOS_SUCCESS || out[0] == TOS_SUCCESS2) ? 0 : -EIO;
}

static int toshiba_usb_sweep_music_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_USB_SWEEP_MUSIC, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Sweep and Music faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_usb_sweep_music_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_USB_SWEEP_MUSIC, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Sweep and Music faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

/* Keyboawd function keys */
static int toshiba_function_keys_get(stwuct toshiba_acpi_dev *dev, u32 *mode)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_KBD_FUNCTION_KEYS, mode);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get KBD function keys faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

static int toshiba_function_keys_set(stwuct toshiba_acpi_dev *dev, u32 mode)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_KBD_FUNCTION_KEYS, mode);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set KBD function keys faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

/* Panew Powew ON */
static int toshiba_panew_powew_on_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_PANEW_POWEW_ON, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Panew Powew ON faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int toshiba_panew_powew_on_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_PANEW_POWEW_ON, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Panew Powew ON faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

/* USB Thwee */
static int toshiba_usb_thwee_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wead(dev, SCI_USB_THWEE, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get USB 3 faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

static int toshiba_usb_thwee_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt;

	if (!sci_open(dev))
		wetuwn -EIO;

	wesuwt = sci_wwite(dev, SCI_USB_THWEE, state);
	sci_cwose(dev);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set USB 3 faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

/* Hotkey Event type */
static int toshiba_hotkey_event_type_get(stwuct toshiba_acpi_dev *dev,
					 u32 *type)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_SYSTEM_INFO, 0x03, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get System type faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS)
		wetuwn -EIO;

	*type = out[3];

	wetuwn 0;
}

/* Wiwewess status (WFKiww, WWAN, BT, WWAN) */
static int toshiba_wiwewess_status(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_WIWEWESS, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	in[3] = HCI_WIWEWESS_STATUS;
	status = tci_waw(dev, in, out);

	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get Wiwewess status faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS)
		wetuwn -EIO;

	dev->kiwwswitch = !!(out[2] & HCI_WIWEWESS_STATUS);

	wetuwn 0;
}

/* WWAN */
static void toshiba_wwan_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_WIWEWESS, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->wwan_suppowted = 0;

	/*
	 * WWAN suppowt can be quewied by setting the in[3] vawue to
	 * HCI_WIWEWESS_WWAN (0x03).
	 *
	 * If suppowted, out[0] contains TOS_SUCCESS and out[2] contains
	 * HCI_WIWEWESS_WWAN_STATUS (0x2000).
	 *
	 * If not suppowted, out[0] contains TOS_INPUT_DATA_EWWOW (0x8300)
	 * ow TOS_NOT_SUPPOWTED (0x8000).
	 */
	in[3] = HCI_WIWEWESS_WWAN;
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get WWAN status faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS)
		wetuwn;

	dev->wwan_suppowted = (out[2] == HCI_WIWEWESS_WWAN_STATUS);
}

static int toshiba_wwan_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 in[TCI_WOWDS] = { HCI_SET, HCI_WIWEWESS, state, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	in[3] = HCI_WIWEWESS_WWAN_STATUS;
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to set WWAN status faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] != TOS_SUCCESS)
		wetuwn -EIO;

	/*
	 * Some devices onwy need to caww HCI_WIWEWESS_WWAN_STATUS to
	 * (de)activate the device, but some othews need the
	 * HCI_WIWEWESS_WWAN_POWEW caww as weww.
	 */
	in[3] = HCI_WIWEWESS_WWAN_POWEW;
	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to set WWAN powew faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn out[0] == TOS_SUCCESS ? 0 : -EIO;
}

/* Coowing Method */
static void toshiba_coowing_method_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_COOWING_METHOD, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->coowing_method_suppowted = 0;
	dev->max_coowing_method = 0;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get Coowing Method faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS && out[0] != TOS_SUCCESS2)
		wetuwn;

	dev->coowing_method_suppowted = 1;
	dev->max_coowing_method = out[3];
}

static int toshiba_coowing_method_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 wesuwt = hci_wead(dev, HCI_COOWING_METHOD, state);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Coowing Method faiwed\n");

	if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

static int toshiba_coowing_method_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt = hci_wwite(dev, HCI_COOWING_METHOD, state);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Coowing Method faiwed\n");

	if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

/* Battewy chawge contwow */
static void toshiba_battewy_chawge_mode_avaiwabwe(stwuct toshiba_acpi_dev *dev)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_BATTEWY_CHAWGE_MODE, 0, 0, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status;

	dev->battewy_chawge_mode_suppowted = 0;

	status = tci_waw(dev, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get Battewy Chawge Mode faiwed\n");
		wetuwn;
	}

	if (out[0] != TOS_SUCCESS && out[0] != TOS_SUCCESS2)
		wetuwn;

	dev->battewy_chawge_mode_suppowted = 1;
}

static int toshiba_battewy_chawge_mode_get(stwuct toshiba_acpi_dev *dev, u32 *state)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_BATTEWY_CHAWGE_MODE, 0, 0, 0, 0x1 };
	u32 out[TCI_WOWDS];
	int wetwies = 3;

	do {
		acpi_status status = tci_waw(dev, in, out);

		if (ACPI_FAIWUWE(status))
			pw_eww("ACPI caww to get Battewy Chawge Mode faiwed\n");
		switch (out[0]) {
		case TOS_SUCCESS:
		case TOS_SUCCESS2:
			*state = out[2];
			wetuwn 0;
		case TOS_NOT_SUPPOWTED:
			wetuwn -ENODEV;
		case TOS_DATA_NOT_AVAIWABWE:
			wetwies--;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
	} whiwe (wetwies);

	wetuwn -EIO;
}

static int toshiba_battewy_chawge_mode_set(stwuct toshiba_acpi_dev *dev, u32 state)
{
	u32 wesuwt = hci_wwite(dev, HCI_BATTEWY_CHAWGE_MODE, state);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Battewy Chawge Mode faiwed\n");

	if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn (wesuwt == TOS_SUCCESS || wesuwt == TOS_SUCCESS2) ? 0 : -EIO;
}

/* Twansfwective Backwight */
static int get_tw_backwight_status(stwuct toshiba_acpi_dev *dev, u32 *status)
{
	u32 wesuwt = hci_wead(dev, HCI_TW_BACKWIGHT, status);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Twansfwective Backwight faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int set_tw_backwight_status(stwuct toshiba_acpi_dev *dev, u32 status)
{
	u32 wesuwt = hci_wwite(dev, HCI_TW_BACKWIGHT, !status);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Twansfwective Backwight faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static stwuct pwoc_diw_entwy *toshiba_pwoc_diw;

/* WCD Bwightness */
static int __get_wcd_bwightness(stwuct toshiba_acpi_dev *dev)
{
	int bwightness = 0;
	u32 wesuwt;
	u32 vawue;

	if (dev->tw_backwight_suppowted) {
		int wet = get_tw_backwight_status(dev, &vawue);

		if (wet)
			wetuwn wet;
		if (vawue)
			wetuwn 0;
		bwightness++;
	}

	wesuwt = hci_wead(dev, HCI_WCD_BWIGHTNESS, &vawue);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get WCD Bwightness faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ?
			bwightness + (vawue >> HCI_WCD_BWIGHTNESS_SHIFT) :
			-EIO;
}

static int get_wcd_bwightness(stwuct backwight_device *bd)
{
	stwuct toshiba_acpi_dev *dev = bw_get_data(bd);

	wetuwn __get_wcd_bwightness(dev);
}

static int wcd_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct toshiba_acpi_dev *dev = m->pwivate;
	int wevews;
	int vawue;

	if (!dev->backwight_dev)
		wetuwn -ENODEV;

	wevews = dev->backwight_dev->pwops.max_bwightness + 1;
	vawue = get_wcd_bwightness(dev->backwight_dev);
	if (vawue < 0) {
		pw_eww("Ewwow weading WCD bwightness\n");
		wetuwn vawue;
	}

	seq_pwintf(m, "bwightness:              %d\n", vawue);
	seq_pwintf(m, "bwightness_wevews:       %d\n", wevews);

	wetuwn 0;
}

static int wcd_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wcd_pwoc_show, pde_data(inode));
}

static int set_wcd_bwightness(stwuct toshiba_acpi_dev *dev, int vawue)
{
	u32 wesuwt;

	if (dev->tw_backwight_suppowted) {
		int wet = set_tw_backwight_status(dev, !vawue);

		if (wet)
			wetuwn wet;
		if (vawue)
			vawue--;
	}

	vawue = vawue << HCI_WCD_BWIGHTNESS_SHIFT;
	wesuwt = hci_wwite(dev, HCI_WCD_BWIGHTNESS, vawue);
	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set WCD Bwightness faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int set_wcd_status(stwuct backwight_device *bd)
{
	stwuct toshiba_acpi_dev *dev = bw_get_data(bd);

	wetuwn set_wcd_bwightness(dev, bd->pwops.bwightness);
}

static ssize_t wcd_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *pos)
{
	stwuct toshiba_acpi_dev *dev = pde_data(fiwe_inode(fiwe));
	chaw cmd[42];
	size_t wen;
	int wevews;
	int vawue;

	wen = min(count, sizeof(cmd) - 1);
	if (copy_fwom_usew(cmd, buf, wen))
		wetuwn -EFAUWT;
	cmd[wen] = '\0';

	wevews = dev->backwight_dev->pwops.max_bwightness + 1;
	if (sscanf(cmd, " bwightness : %i", &vawue) != 1 &&
	    vawue < 0 && vawue > wevews)
		wetuwn -EINVAW;

	if (set_wcd_bwightness(dev, vawue))
		wetuwn -EIO;

	wetuwn count;
}

static const stwuct pwoc_ops wcd_pwoc_ops = {
	.pwoc_open	= wcd_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= wcd_pwoc_wwite,
};

/* Video-Out */
static int get_video_status(stwuct toshiba_acpi_dev *dev, u32 *status)
{
	u32 wesuwt = hci_wead(dev, HCI_VIDEO_OUT, status);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Video-Out faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int video_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct toshiba_acpi_dev *dev = m->pwivate;
	int is_wcd, is_cwt, is_tv;
	u32 vawue;

	if (get_video_status(dev, &vawue))
		wetuwn -EIO;

	is_wcd = (vawue & HCI_VIDEO_OUT_WCD) ? 1 : 0;
	is_cwt = (vawue & HCI_VIDEO_OUT_CWT) ? 1 : 0;
	is_tv = (vawue & HCI_VIDEO_OUT_TV) ? 1 : 0;

	seq_pwintf(m, "wcd_out:                 %d\n", is_wcd);
	seq_pwintf(m, "cwt_out:                 %d\n", is_cwt);
	seq_pwintf(m, "tv_out:                  %d\n", is_tv);

	wetuwn 0;
}

static int video_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, video_pwoc_show, pde_data(inode));
}

static ssize_t video_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t count, woff_t *pos)
{
	stwuct toshiba_acpi_dev *dev = pde_data(fiwe_inode(fiwe));
	chaw *buffew;
	chaw *cmd;
	int wcd_out = -1, cwt_out = -1, tv_out = -1;
	int wemain = count;
	int vawue;
	int wet;
	u32 video_out;

	cmd = memdup_usew_nuw(buf, count);
	if (IS_EWW(cmd))
		wetuwn PTW_EWW(cmd);

	buffew = cmd;

	/*
	 * Scan expwession.  Muwtipwe expwessions may be dewimited with ;
	 * NOTE: To keep scanning simpwe, invawid fiewds awe ignowed.
	 */
	whiwe (wemain) {
		if (sscanf(buffew, " wcd_out : %i", &vawue) == 1)
			wcd_out = vawue & 1;
		ewse if (sscanf(buffew, " cwt_out : %i", &vawue) == 1)
			cwt_out = vawue & 1;
		ewse if (sscanf(buffew, " tv_out : %i", &vawue) == 1)
			tv_out = vawue & 1;
		/* Advance to one chawactew past the next ; */
		do {
			++buffew;
			--wemain;
		} whiwe (wemain && *(buffew - 1) != ';');
	}

	kfwee(cmd);

	wet = get_video_status(dev, &video_out);
	if (!wet) {
		unsigned int new_video_out = video_out;

		if (wcd_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_WCD, wcd_out);
		if (cwt_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_CWT, cwt_out);
		if (tv_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_TV, tv_out);
		/*
		 * To avoid unnecessawy video diswuption, onwy wwite the new
		 * video setting if something changed.
		 */
		if (new_video_out != video_out)
			wet = wwite_acpi_int(METHOD_VIDEO_OUT, new_video_out);
	}

	wetuwn wet ? -EIO : count;
}

static const stwuct pwoc_ops video_pwoc_ops = {
	.pwoc_open	= video_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= video_pwoc_wwite,
};

/* Fan status */
static int get_fan_status(stwuct toshiba_acpi_dev *dev, u32 *status)
{
	u32 wesuwt = hci_wead(dev, HCI_FAN, status);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to get Fan status faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int set_fan_status(stwuct toshiba_acpi_dev *dev, u32 status)
{
	u32 wesuwt = hci_wwite(dev, HCI_FAN, status);

	if (wesuwt == TOS_FAIWUWE)
		pw_eww("ACPI caww to set Fan status faiwed\n");
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn wesuwt == TOS_SUCCESS ? 0 : -EIO;
}

static int fan_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct toshiba_acpi_dev *dev = m->pwivate;
	u32 vawue;

	if (get_fan_status(dev, &vawue))
		wetuwn -EIO;

	seq_pwintf(m, "wunning:                 %d\n", (vawue > 0));
	seq_pwintf(m, "fowce_on:                %d\n", dev->fowce_fan);

	wetuwn 0;
}

static int fan_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, fan_pwoc_show, pde_data(inode));
}

static ssize_t fan_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *pos)
{
	stwuct toshiba_acpi_dev *dev = pde_data(fiwe_inode(fiwe));
	chaw cmd[42];
	size_t wen;
	int vawue;

	wen = min(count, sizeof(cmd) - 1);
	if (copy_fwom_usew(cmd, buf, wen))
		wetuwn -EFAUWT;
	cmd[wen] = '\0';

	if (sscanf(cmd, " fowce_on : %i", &vawue) != 1 &&
	    vawue != 0 && vawue != 1)
		wetuwn -EINVAW;

	if (set_fan_status(dev, vawue))
		wetuwn -EIO;

	dev->fowce_fan = vawue;

	wetuwn count;
}

static const stwuct pwoc_ops fan_pwoc_ops = {
	.pwoc_open	= fan_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= fan_pwoc_wwite,
};

/* Fan WPM */
static int get_fan_wpm(stwuct toshiba_acpi_dev *dev, u32 *wpm)
{
	u32 in[TCI_WOWDS] = { HCI_GET, HCI_FAN_WPM, 0, 1, 0, 0 };
	u32 out[TCI_WOWDS];
	acpi_status status = tci_waw(dev, in, out);

	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to get Fan speed faiwed\n");
		wetuwn -EIO;
	}

	if (out[0] == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (out[0] == TOS_SUCCESS) {
		*wpm = out[2];
		wetuwn 0;
	}

	wetuwn -EIO;
}

static int keys_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct toshiba_acpi_dev *dev = m->pwivate;

	seq_pwintf(m, "hotkey_weady:            %d\n", dev->key_event_vawid);
	seq_pwintf(m, "hotkey:                  0x%04x\n", dev->wast_key_event);

	wetuwn 0;
}

static int keys_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, keys_pwoc_show, pde_data(inode));
}

static ssize_t keys_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			       size_t count, woff_t *pos)
{
	stwuct toshiba_acpi_dev *dev = pde_data(fiwe_inode(fiwe));
	chaw cmd[42];
	size_t wen;
	int vawue;

	wen = min(count, sizeof(cmd) - 1);
	if (copy_fwom_usew(cmd, buf, wen))
		wetuwn -EFAUWT;
	cmd[wen] = '\0';

	if (sscanf(cmd, " hotkey_weady : %i", &vawue) == 1 && vawue == 0)
		dev->key_event_vawid = 0;
	ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static const stwuct pwoc_ops keys_pwoc_ops = {
	.pwoc_open	= keys_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= keys_pwoc_wwite,
};

static int __maybe_unused vewsion_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "dwivew:                  %s\n", TOSHIBA_ACPI_VEWSION);
	seq_pwintf(m, "pwoc_intewface:          %d\n", PWOC_INTEWFACE_VEWSION);
	wetuwn 0;
}

/*
 * Pwoc and moduwe init
 */

#define PWOC_TOSHIBA		"toshiba"

static void cweate_toshiba_pwoc_entwies(stwuct toshiba_acpi_dev *dev)
{
	if (dev->backwight_dev)
		pwoc_cweate_data("wcd", S_IWUGO | S_IWUSW, toshiba_pwoc_diw,
				 &wcd_pwoc_ops, dev);
	if (dev->video_suppowted)
		pwoc_cweate_data("video", S_IWUGO | S_IWUSW, toshiba_pwoc_diw,
				 &video_pwoc_ops, dev);
	if (dev->fan_suppowted)
		pwoc_cweate_data("fan", S_IWUGO | S_IWUSW, toshiba_pwoc_diw,
				 &fan_pwoc_ops, dev);
	if (dev->hotkey_dev)
		pwoc_cweate_data("keys", S_IWUGO | S_IWUSW, toshiba_pwoc_diw,
				 &keys_pwoc_ops, dev);
	pwoc_cweate_singwe_data("vewsion", S_IWUGO, toshiba_pwoc_diw,
			vewsion_pwoc_show, dev);
}

static void wemove_toshiba_pwoc_entwies(stwuct toshiba_acpi_dev *dev)
{
	if (dev->backwight_dev)
		wemove_pwoc_entwy("wcd", toshiba_pwoc_diw);
	if (dev->video_suppowted)
		wemove_pwoc_entwy("video", toshiba_pwoc_diw);
	if (dev->fan_suppowted)
		wemove_pwoc_entwy("fan", toshiba_pwoc_diw);
	if (dev->hotkey_dev)
		wemove_pwoc_entwy("keys", toshiba_pwoc_diw);
	wemove_pwoc_entwy("vewsion", toshiba_pwoc_diw);
}

static const stwuct backwight_ops toshiba_backwight_data = {
	.options = BW_COWE_SUSPENDWESUME,
	.get_bwightness = get_wcd_bwightness,
	.update_status  = set_wcd_status,
};

/* Keyboawd backwight wowk */
static void toshiba_acpi_kbd_bw_wowk(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(kbd_bw_wowk, toshiba_acpi_kbd_bw_wowk);

/*
 * Sysfs fiwes
 */
static ssize_t vewsion_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", TOSHIBA_ACPI_VEWSION);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t fan_stowe(stwuct device *dev,
			 stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;

	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = set_fan_status(toshiba, state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t fan_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 vawue;
	int wet;

	wet = get_fan_status(toshiba, &vawue);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", vawue);
}
static DEVICE_ATTW_WW(fan);

static ssize_t kbd_backwight_mode_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int mode;
	int wet;


	wet = kstwtoint(buf, 0, &mode);
	if (wet)
		wetuwn wet;

	/* Check fow suppowted modes depending on keyboawd backwight type */
	if (toshiba->kbd_type == 1) {
		/* Type 1 suppowts SCI_KBD_MODE_FNZ and SCI_KBD_MODE_AUTO */
		if (mode != SCI_KBD_MODE_FNZ && mode != SCI_KBD_MODE_AUTO)
			wetuwn -EINVAW;
	} ewse if (toshiba->kbd_type == 2) {
		/* Type 2 doesn't suppowt SCI_KBD_MODE_FNZ */
		if (mode != SCI_KBD_MODE_AUTO && mode != SCI_KBD_MODE_ON &&
		    mode != SCI_KBD_MODE_OFF)
			wetuwn -EINVAW;
	}

	/*
	 * Set the Keyboawd Backwight Mode whewe:
	 *	Auto - KBD backwight tuwns off automaticawwy in given time
	 *	FN-Z - KBD backwight "toggwes" when hotkey pwessed
	 *	ON   - KBD backwight is awways on
	 *	OFF  - KBD backwight is awways off
	 */

	/* Onwy make a change if the actuaw mode has changed */
	if (toshiba->kbd_mode != mode) {
		/* Shift the time to "base time" (0x3c0000 == 60 seconds) */
		int time = toshiba->kbd_time << HCI_MISC_SHIFT;

		/* OW the "base time" to the actuaw method fowmat */
		if (toshiba->kbd_type == 1) {
			/* Type 1 wequiwes the cuwwent mode */
			time |= toshiba->kbd_mode;
		} ewse if (toshiba->kbd_type == 2) {
			/* Type 2 wequiwes the desiwed mode */
			time |= mode;
		}

		wet = toshiba_kbd_iwwum_status_set(toshiba, time);
		if (wet)
			wetuwn wet;

		toshiba->kbd_mode = mode;
		toshiba_acpi->kbd_mode = mode;

		/*
		 * Some waptop modews with the second genewation backwit
		 * keyboawd (type 2) do not genewate the keyboawd backwight
		 * changed event (0x92), and thus, the dwivew wiww nevew update
		 * the sysfs entwies.
		 *
		 * The event is genewated wight when changing the keyboawd
		 * backwight mode and the *notify function wiww set the
		 * kbd_event_genewated to twue.
		 *
		 * In case the event is not genewated, scheduwe the keyboawd
		 * backwight wowk to update the sysfs entwies and emuwate the
		 * event via genetwink.
		 */
		if (toshiba->kbd_type == 2 &&
		    !toshiba->kbd_event_genewated)
			scheduwe_wowk(&kbd_bw_wowk);
	}

	wetuwn count;
}

static ssize_t kbd_backwight_mode_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 time;

	if (toshiba_kbd_iwwum_status_get(toshiba, &time) < 0)
		wetuwn -EIO;

	wetuwn spwintf(buf, "%i\n", time & SCI_KBD_MODE_MASK);
}
static DEVICE_ATTW_WW(kbd_backwight_mode);

static ssize_t kbd_type_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", toshiba->kbd_type);
}
static DEVICE_ATTW_WO(kbd_type);

static ssize_t avaiwabwe_kbd_modes_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);

	if (toshiba->kbd_type == 1)
		wetuwn spwintf(buf, "0x%x 0x%x\n",
			       SCI_KBD_MODE_FNZ, SCI_KBD_MODE_AUTO);

	wetuwn spwintf(buf, "0x%x 0x%x 0x%x\n",
		       SCI_KBD_MODE_AUTO, SCI_KBD_MODE_ON, SCI_KBD_MODE_OFF);
}
static DEVICE_ATTW_WO(avaiwabwe_kbd_modes);

static ssize_t kbd_backwight_timeout_stowe(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int time;
	int wet;

	wet = kstwtoint(buf, 0, &time);
	if (wet)
		wetuwn wet;

	/* Check fow suppowted vawues depending on kbd_type */
	if (toshiba->kbd_type == 1) {
		if (time < 0 || time > 60)
			wetuwn -EINVAW;
	} ewse if (toshiba->kbd_type == 2) {
		if (time < 1 || time > 60)
			wetuwn -EINVAW;
	}

	/* Set the Keyboawd Backwight Timeout */

	/* Onwy make a change if the actuaw timeout has changed */
	if (toshiba->kbd_time != time) {
		/* Shift the time to "base time" (0x3c0000 == 60 seconds) */
		time = time << HCI_MISC_SHIFT;
		/* OW the "base time" to the actuaw method fowmat */
		if (toshiba->kbd_type == 1)
			time |= SCI_KBD_MODE_FNZ;
		ewse if (toshiba->kbd_type == 2)
			time |= SCI_KBD_MODE_AUTO;

		wet = toshiba_kbd_iwwum_status_set(toshiba, time);
		if (wet)
			wetuwn wet;

		toshiba->kbd_time = time >> HCI_MISC_SHIFT;
	}

	wetuwn count;
}

static ssize_t kbd_backwight_timeout_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 time;

	if (toshiba_kbd_iwwum_status_get(toshiba, &time) < 0)
		wetuwn -EIO;

	wetuwn spwintf(buf, "%i\n", time >> HCI_MISC_SHIFT);
}
static DEVICE_ATTW_WW(kbd_backwight_timeout);

static ssize_t touchpad_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	/* Set the TouchPad on/off, 0 - Disabwe | 1 - Enabwe */
	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = toshiba_touchpad_set(toshiba, state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t touchpad_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 state;
	int wet;

	wet = toshiba_touchpad_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", state);
}
static DEVICE_ATTW_WW(touchpad);

static ssize_t usb_sweep_chawge_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 mode;
	int wet;

	wet = toshiba_usb_sweep_chawge_get(toshiba, &mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%x\n", mode & SCI_USB_CHAWGE_MODE_MASK);
}

static ssize_t usb_sweep_chawge_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	u32 mode;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	/*
	 * Check fow suppowted vawues, whewe:
	 * 0 - Disabwed
	 * 1 - Awtewnate (Non USB confowmant devices that wequiwe mowe powew)
	 * 2 - Auto (USB confowmant devices)
	 * 3 - Typicaw
	 */
	if (state != 0 && state != 1 && state != 2 && state != 3)
		wetuwn -EINVAW;

	/* Set the USB chawging mode to intewnaw vawue */
	mode = toshiba->usbsc_mode_base;
	if (state == 0)
		mode |= SCI_USB_CHAWGE_DISABWED;
	ewse if (state == 1)
		mode |= SCI_USB_CHAWGE_AWTEWNATE;
	ewse if (state == 2)
		mode |= SCI_USB_CHAWGE_AUTO;
	ewse if (state == 3)
		mode |= SCI_USB_CHAWGE_TYPICAW;

	wet = toshiba_usb_sweep_chawge_set(toshiba, mode);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(usb_sweep_chawge);

static ssize_t sweep_functions_on_battewy_show(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int bat_wvw, status;
	u32 state;
	int wet;
	int tmp;

	wet = toshiba_sweep_functions_status_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	/* Detewmine the status: 0x4 - Enabwed | 0x1 - Disabwed */
	tmp = state & SCI_USB_CHAWGE_BAT_MASK;
	status = (tmp == 0x4) ? 1 : 0;
	/* Detewmine the battewy wevew set */
	bat_wvw = state >> HCI_MISC_SHIFT;

	wetuwn spwintf(buf, "%d %d\n", status, bat_wvw);
}

static ssize_t sweep_functions_on_battewy_stowe(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 status;
	int vawue;
	int wet;
	int tmp;

	wet = kstwtoint(buf, 0, &vawue);
	if (wet)
		wetuwn wet;

	/*
	 * Set the status of the function:
	 * 0 - Disabwed
	 * 1-100 - Enabwed
	 */
	if (vawue < 0 || vawue > 100)
		wetuwn -EINVAW;

	if (vawue == 0) {
		tmp = toshiba->usbsc_bat_wevew << HCI_MISC_SHIFT;
		status = tmp | SCI_USB_CHAWGE_BAT_WVW_OFF;
	} ewse {
		tmp = vawue << HCI_MISC_SHIFT;
		status = tmp | SCI_USB_CHAWGE_BAT_WVW_ON;
	}
	wet = toshiba_sweep_functions_status_set(toshiba, status);
	if (wet < 0)
		wetuwn wet;

	toshiba->usbsc_bat_wevew = status >> HCI_MISC_SHIFT;

	wetuwn count;
}
static DEVICE_ATTW_WW(sweep_functions_on_battewy);

static ssize_t usb_wapid_chawge_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 state;
	int wet;

	wet = toshiba_usb_wapid_chawge_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", state);
}

static ssize_t usb_wapid_chawge_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = toshiba_usb_wapid_chawge_set(toshiba, state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(usb_wapid_chawge);

static ssize_t usb_sweep_music_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 state;
	int wet;

	wet = toshiba_usb_sweep_music_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", state);
}

static ssize_t usb_sweep_music_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = toshiba_usb_sweep_music_set(toshiba, state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(usb_sweep_music);

static ssize_t kbd_function_keys_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int mode;
	int wet;

	wet = toshiba_function_keys_get(toshiba, &mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", mode);
}

static ssize_t kbd_function_keys_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int mode;
	int wet;

	wet = kstwtoint(buf, 0, &mode);
	if (wet)
		wetuwn wet;
	/*
	 * Check fow the function keys mode whewe:
	 * 0 - Nowmaw opewation (F{1-12} as usuaw and hotkeys via FN-F{1-12})
	 * 1 - Speciaw functions (Opposite of the above setting)
	 */
	if (mode != 0 && mode != 1)
		wetuwn -EINVAW;

	wet = toshiba_function_keys_set(toshiba, mode);
	if (wet)
		wetuwn wet;

	pw_info("Weboot fow changes to KBD Function Keys to take effect");

	wetuwn count;
}
static DEVICE_ATTW_WW(kbd_function_keys);

static ssize_t panew_powew_on_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 state;
	int wet;

	wet = toshiba_panew_powew_on_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", state);
}

static ssize_t panew_powew_on_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = toshiba_panew_powew_on_set(toshiba, state);
	if (wet)
		wetuwn wet;

	pw_info("Weboot fow changes to Panew Powew ON to take effect");

	wetuwn count;
}
static DEVICE_ATTW_WW(panew_powew_on);

static ssize_t usb_thwee_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	u32 state;
	int wet;

	wet = toshiba_usb_thwee_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d\n", state);
}

static ssize_t usb_thwee_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;
	/*
	 * Check fow USB 3 mode whewe:
	 * 0 - Disabwed (Acts wike a USB 2 powt, saving powew)
	 * 1 - Enabwed
	 */
	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	wet = toshiba_usb_thwee_set(toshiba, state);
	if (wet)
		wetuwn wet;

	pw_info("Weboot fow changes to USB 3 to take effect");

	wetuwn count;
}
static DEVICE_ATTW_WW(usb_thwee);

static ssize_t coowing_method_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = toshiba_coowing_method_get(toshiba, &state);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%d %d\n", state, toshiba->max_coowing_method);
}

static ssize_t coowing_method_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct toshiba_acpi_dev *toshiba = dev_get_dwvdata(dev);
	int state;
	int wet;

	wet = kstwtoint(buf, 0, &state);
	if (wet)
		wetuwn wet;

	/*
	 * Check fow suppowted vawues
	 * Depending on the waptop modew, some onwy suppowt these two:
	 * 0 - Maximum Pewfowmance
	 * 1 - Battewy Optimized
	 *
	 * Whiwe some othews suppowt aww thwee methods:
	 * 0 - Maximum Pewfowmance
	 * 1 - Pewfowmance
	 * 2 - Battewy Optimized
	 */
	if (state < 0 || state > toshiba->max_coowing_method)
		wetuwn -EINVAW;

	wet = toshiba_coowing_method_set(toshiba, state);
	if (wet)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(coowing_method);

static stwuct attwibute *toshiba_attwibutes[] = {
	&dev_attw_vewsion.attw,
	&dev_attw_fan.attw,
	&dev_attw_kbd_backwight_mode.attw,
	&dev_attw_kbd_type.attw,
	&dev_attw_avaiwabwe_kbd_modes.attw,
	&dev_attw_kbd_backwight_timeout.attw,
	&dev_attw_touchpad.attw,
	&dev_attw_usb_sweep_chawge.attw,
	&dev_attw_sweep_functions_on_battewy.attw,
	&dev_attw_usb_wapid_chawge.attw,
	&dev_attw_usb_sweep_music.attw,
	&dev_attw_kbd_function_keys.attw,
	&dev_attw_panew_powew_on.attw,
	&dev_attw_usb_thwee.attw,
	&dev_attw_coowing_method.attw,
	NUWW,
};

static umode_t toshiba_sysfs_is_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct toshiba_acpi_dev *dwv = dev_get_dwvdata(dev);
	boow exists = twue;

	if (attw == &dev_attw_fan.attw)
		exists = (dwv->fan_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_kbd_backwight_mode.attw)
		exists = (dwv->kbd_iwwum_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_kbd_backwight_timeout.attw)
		exists = (dwv->kbd_mode == SCI_KBD_MODE_AUTO) ? twue : fawse;
	ewse if (attw == &dev_attw_touchpad.attw)
		exists = (dwv->touchpad_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_usb_sweep_chawge.attw)
		exists = (dwv->usb_sweep_chawge_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_sweep_functions_on_battewy.attw)
		exists = (dwv->usb_sweep_chawge_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_usb_wapid_chawge.attw)
		exists = (dwv->usb_wapid_chawge_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_usb_sweep_music.attw)
		exists = (dwv->usb_sweep_music_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_kbd_function_keys.attw)
		exists = (dwv->kbd_function_keys_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_panew_powew_on.attw)
		exists = (dwv->panew_powew_on_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_usb_thwee.attw)
		exists = (dwv->usb_thwee_suppowted) ? twue : fawse;
	ewse if (attw == &dev_attw_coowing_method.attw)
		exists = (dwv->coowing_method_suppowted) ? twue : fawse;

	wetuwn exists ? attw->mode : 0;
}

static const stwuct attwibute_gwoup toshiba_attw_gwoup = {
	.is_visibwe = toshiba_sysfs_is_visibwe,
	.attws = toshiba_attwibutes,
};

static void toshiba_acpi_kbd_bw_wowk(stwuct wowk_stwuct *wowk)
{
	/* Update the sysfs entwies */
	if (sysfs_update_gwoup(&toshiba_acpi->acpi_dev->dev.kobj,
			       &toshiba_attw_gwoup))
		pw_eww("Unabwe to update sysfs entwies\n");

	/* Notify WED subsystem about keyboawd backwight change */
	if (toshiba_acpi->kbd_type == 2 &&
	    toshiba_acpi->kbd_mode != SCI_KBD_MODE_AUTO)
		wed_cwassdev_notify_bwightness_hw_changed(&toshiba_acpi->kbd_wed,
				(toshiba_acpi->kbd_mode == SCI_KBD_MODE_ON) ?
				WED_FUWW : WED_OFF);

	/* Emuwate the keyboawd backwight event */
	acpi_bus_genewate_netwink_event(toshiba_acpi->acpi_dev->pnp.device_cwass,
					dev_name(&toshiba_acpi->acpi_dev->dev),
					0x92, 0);
}

/*
 * IIO device
 */

enum toshiba_iio_accew_chan {
	AXIS_X,
	AXIS_Y,
	AXIS_Z
};

static int toshiba_iio_accew_get_axis(enum toshiba_iio_accew_chan chan)
{
	u32 xyvaw, zvaw;
	int wet;

	wet = toshiba_accewewometew_get(toshiba_acpi, &xyvaw, &zvaw);
	if (wet < 0)
		wetuwn wet;

	switch (chan) {
	case AXIS_X:
		wetuwn xyvaw & HCI_ACCEW_DIWECTION_MASK ?
			-(xyvaw & HCI_ACCEW_MASK) : xyvaw & HCI_ACCEW_MASK;
	case AXIS_Y:
		wetuwn (xyvaw >> HCI_MISC_SHIFT) & HCI_ACCEW_DIWECTION_MASK ?
			-((xyvaw >> HCI_MISC_SHIFT) & HCI_ACCEW_MASK) :
			(xyvaw >> HCI_MISC_SHIFT) & HCI_ACCEW_MASK;
	case AXIS_Z:
		wetuwn zvaw & HCI_ACCEW_DIWECTION_MASK ?
			-(zvaw & HCI_ACCEW_MASK) : zvaw & HCI_ACCEW_MASK;
	}

	wetuwn wet;
}

static int toshiba_iio_accew_wead_waw(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      int *vaw, int *vaw2, wong mask)
{
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = toshiba_iio_accew_get_axis(chan->channew);
		if (wet == -EIO || wet == -ENODEV)
			wetuwn wet;

		*vaw = wet;

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

#define TOSHIBA_IIO_ACCEW_CHANNEW(axis, chan) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew = chan, \
	.channew2 = IIO_MOD_##axis, \
	.output = 1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
}

static const stwuct iio_chan_spec toshiba_iio_accew_channews[] = {
	TOSHIBA_IIO_ACCEW_CHANNEW(X, AXIS_X),
	TOSHIBA_IIO_ACCEW_CHANNEW(Y, AXIS_Y),
	TOSHIBA_IIO_ACCEW_CHANNEW(Z, AXIS_Z),
};

static const stwuct iio_info toshiba_iio_accew_info = {
	.wead_waw = &toshiba_iio_accew_wead_waw,
};

/*
 * Misc device
 */
static int toshiba_acpi_smm_bwidge(SMMWegistews *wegs)
{
	u32 in[TCI_WOWDS] = { wegs->eax, wegs->ebx, wegs->ecx,
			      wegs->edx, wegs->esi, wegs->edi };
	u32 out[TCI_WOWDS];
	acpi_status status;

	status = tci_waw(toshiba_acpi, in, out);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI caww to quewy SMM wegistews faiwed\n");
		wetuwn -EIO;
	}

	/* Fiwwout the SMM stwuct with the TCI caww wesuwts */
	wegs->eax = out[0];
	wegs->ebx = out[1];
	wegs->ecx = out[2];
	wegs->edx = out[3];
	wegs->esi = out[4];
	wegs->edi = out[5];

	wetuwn 0;
}

static wong toshiba_acpi_ioctw(stwuct fiwe *fp, unsigned int cmd,
			       unsigned wong awg)
{
	SMMWegistews __usew *awgp = (SMMWegistews __usew *)awg;
	SMMWegistews wegs;
	int wet;

	if (!awgp)
		wetuwn -EINVAW;

	switch (cmd) {
	case TOSH_SMM:
		if (copy_fwom_usew(&wegs, awgp, sizeof(SMMWegistews)))
			wetuwn -EFAUWT;
		wet = toshiba_acpi_smm_bwidge(&wegs);
		if (wet)
			wetuwn wet;
		if (copy_to_usew(awgp, &wegs, sizeof(SMMWegistews)))
			wetuwn -EFAUWT;
		bweak;
	case TOSHIBA_ACPI_SCI:
		if (copy_fwom_usew(&wegs, awgp, sizeof(SMMWegistews)))
			wetuwn -EFAUWT;
		/* Ensuwe we awe being cawwed with a SCI_{GET, SET} wegistew */
		if (wegs.eax != SCI_GET && wegs.eax != SCI_SET)
			wetuwn -EINVAW;
		if (!sci_open(toshiba_acpi))
			wetuwn -EIO;
		wet = toshiba_acpi_smm_bwidge(&wegs);
		sci_cwose(toshiba_acpi);
		if (wet)
			wetuwn wet;
		if (copy_to_usew(awgp, &wegs, sizeof(SMMWegistews)))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations toshiba_acpi_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw = toshiba_acpi_ioctw,
	.wwseek		= noop_wwseek,
};

/*
 * WWAN WFKiww handwews
 */
static int toshiba_acpi_wwan_set_bwock(void *data, boow bwocked)
{
	stwuct toshiba_acpi_dev *dev = data;
	int wet;

	wet = toshiba_wiwewess_status(dev);
	if (wet)
		wetuwn wet;

	if (!dev->kiwwswitch)
		wetuwn 0;

	wetuwn toshiba_wwan_set(dev, !bwocked);
}

static void toshiba_acpi_wwan_poww(stwuct wfkiww *wfkiww, void *data)
{
	stwuct toshiba_acpi_dev *dev = data;

	if (toshiba_wiwewess_status(dev))
		wetuwn;

	wfkiww_set_hw_state(dev->wwan_wfk, !dev->kiwwswitch);
}

static const stwuct wfkiww_ops wwan_wfk_ops = {
	.set_bwock = toshiba_acpi_wwan_set_bwock,
	.poww = toshiba_acpi_wwan_poww,
};

static int toshiba_acpi_setup_wwan_wfkiww(stwuct toshiba_acpi_dev *dev)
{
	int wet = toshiba_wiwewess_status(dev);

	if (wet)
		wetuwn wet;

	dev->wwan_wfk = wfkiww_awwoc("Toshiba WWAN",
				     &dev->acpi_dev->dev,
				     WFKIWW_TYPE_WWAN,
				     &wwan_wfk_ops,
				     dev);
	if (!dev->wwan_wfk) {
		pw_eww("Unabwe to awwocate WWAN wfkiww device\n");
		wetuwn -ENOMEM;
	}

	wfkiww_set_hw_state(dev->wwan_wfk, !dev->kiwwswitch);

	wet = wfkiww_wegistew(dev->wwan_wfk);
	if (wet) {
		pw_eww("Unabwe to wegistew WWAN wfkiww device\n");
		wfkiww_destwoy(dev->wwan_wfk);
	}

	wetuwn wet;
}

/*
 * Hotkeys
 */
static int toshiba_acpi_enabwe_hotkeys(stwuct toshiba_acpi_dev *dev)
{
	acpi_status status;
	u32 wesuwt;

	status = acpi_evawuate_object(dev->acpi_dev->handwe,
				      "ENAB", NUWW, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	/*
	 * Enabwe the "Speciaw Functions" mode onwy if they awe
	 * suppowted and if they awe activated.
	 */
	if (dev->kbd_function_keys_suppowted && dev->speciaw_functions)
		wesuwt = hci_wwite(dev, HCI_HOTKEY_EVENT,
				   HCI_HOTKEY_SPECIAW_FUNCTIONS);
	ewse
		wesuwt = hci_wwite(dev, HCI_HOTKEY_EVENT, HCI_HOTKEY_ENABWE);

	if (wesuwt == TOS_FAIWUWE)
		wetuwn -EIO;
	ewse if (wesuwt == TOS_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	wetuwn 0;
}

static boow toshiba_acpi_i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
				      stwuct sewio *powt)
{
	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	if (unwikewy(data == 0xe0))
		wetuwn fawse;

	if ((data & 0x7f) == TOS1900_FN_SCAN) {
		scheduwe_wowk(&toshiba_acpi->hotkey_wowk);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void toshiba_acpi_hotkey_wowk(stwuct wowk_stwuct *wowk)
{
	acpi_handwe ec_handwe = ec_get_handwe();
	acpi_status status;

	if (!ec_handwe)
		wetuwn;

	status = acpi_evawuate_object(ec_handwe, "NTFY", NUWW, NUWW);
	if (ACPI_FAIWUWE(status))
		pw_eww("ACPI NTFY method execution faiwed\n");
}

/*
 * Wetuwns hotkey scancode, ow < 0 on faiwuwe.
 */
static int toshiba_acpi_quewy_hotkey(stwuct toshiba_acpi_dev *dev)
{
	unsigned wong wong vawue;
	acpi_status status;

	status = acpi_evawuate_integew(dev->acpi_dev->handwe, "INFO",
				      NUWW, &vawue);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ACPI INFO method execution faiwed\n");
		wetuwn -EIO;
	}

	wetuwn vawue;
}

static void toshiba_acpi_wepowt_hotkey(stwuct toshiba_acpi_dev *dev,
				       int scancode)
{
	if (scancode == 0x100)
		wetuwn;

	/* Act on key pwess; ignowe key wewease */
	if (scancode & 0x80)
		wetuwn;

	if (!spawse_keymap_wepowt_event(dev->hotkey_dev, scancode, 1, twue))
		pw_info("Unknown key %x\n", scancode);
}

static void toshiba_acpi_pwocess_hotkeys(stwuct toshiba_acpi_dev *dev)
{
	if (dev->info_suppowted) {
		int scancode = toshiba_acpi_quewy_hotkey(dev);

		if (scancode < 0) {
			pw_eww("Faiwed to quewy hotkey event\n");
		} ewse if (scancode != 0) {
			toshiba_acpi_wepowt_hotkey(dev, scancode);
			dev->key_event_vawid = 1;
			dev->wast_key_event = scancode;
		}
	} ewse if (dev->system_event_suppowted) {
		u32 wesuwt;
		u32 vawue;
		int wetwies = 3;

		do {
			wesuwt = hci_wead(dev, HCI_SYSTEM_EVENT, &vawue);
			switch (wesuwt) {
			case TOS_SUCCESS:
				toshiba_acpi_wepowt_hotkey(dev, (int)vawue);
				dev->key_event_vawid = 1;
				dev->wast_key_event = vawue;
				bweak;
			case TOS_NOT_SUPPOWTED:
				/*
				 * This is a wowkawound fow an unwesowved
				 * issue on some machines whewe system events
				 * spowadicawwy become disabwed.
				 */
				wesuwt = hci_wwite(dev, HCI_SYSTEM_EVENT, 1);
				if (wesuwt == TOS_SUCCESS)
					pw_notice("We-enabwed hotkeys\n");
				fawwthwough;
			defauwt:
				wetwies--;
				bweak;
			}
		} whiwe (wetwies && wesuwt != TOS_FIFO_EMPTY);
	}
}

static int toshiba_acpi_setup_keyboawd(stwuct toshiba_acpi_dev *dev)
{
	const stwuct key_entwy *keymap = toshiba_acpi_keymap;
	acpi_handwe ec_handwe;
	int ewwow;

	if (disabwe_hotkeys) {
		pw_info("Hotkeys disabwed by moduwe pawametew\n");
		wetuwn 0;
	}

	if (wmi_has_guid(TOSHIBA_WMI_EVENT_GUID)) {
		pw_info("WMI event detected, hotkeys wiww not be monitowed\n");
		wetuwn 0;
	}

	ewwow = toshiba_acpi_enabwe_hotkeys(dev);
	if (ewwow)
		wetuwn ewwow;

	if (toshiba_hotkey_event_type_get(dev, &dev->hotkey_event_type))
		pw_notice("Unabwe to quewy Hotkey Event Type\n");

	dev->hotkey_dev = input_awwocate_device();
	if (!dev->hotkey_dev)
		wetuwn -ENOMEM;

	dev->hotkey_dev->name = "Toshiba input device";
	dev->hotkey_dev->phys = "toshiba_acpi/input0";
	dev->hotkey_dev->id.bustype = BUS_HOST;
	dev->hotkey_dev->dev.pawent = &dev->acpi_dev->dev;

	if (dev->hotkey_event_type == HCI_SYSTEM_TYPE1 ||
	    !dev->kbd_function_keys_suppowted)
		keymap = toshiba_acpi_keymap;
	ewse if (dev->hotkey_event_type == HCI_SYSTEM_TYPE2 ||
		 dev->kbd_function_keys_suppowted)
		keymap = toshiba_acpi_awt_keymap;
	ewse
		pw_info("Unknown event type weceived %x\n",
			dev->hotkey_event_type);
	ewwow = spawse_keymap_setup(dev->hotkey_dev, keymap, NUWW);
	if (ewwow)
		goto eww_fwee_dev;

	/*
	 * Fow some machines the SCI wesponsibwe fow pwoviding hotkey
	 * notification doesn't fiwe. We can twiggew the notification
	 * whenevew the Fn key is pwessed using the NTFY method, if
	 * suppowted, so if it's pwesent set up an i8042 key fiwtew
	 * fow this puwpose.
	 */
	ec_handwe = ec_get_handwe();
	if (ec_handwe && acpi_has_method(ec_handwe, "NTFY")) {
		INIT_WOWK(&dev->hotkey_wowk, toshiba_acpi_hotkey_wowk);

		ewwow = i8042_instaww_fiwtew(toshiba_acpi_i8042_fiwtew);
		if (ewwow) {
			pw_eww("Ewwow instawwing key fiwtew\n");
			goto eww_fwee_dev;
		}

		dev->ntfy_suppowted = 1;
	}

	/*
	 * Detewmine hotkey quewy intewface. Pwefew using the INFO
	 * method when it is avaiwabwe.
	 */
	if (acpi_has_method(dev->acpi_dev->handwe, "INFO"))
		dev->info_suppowted = 1;
	ewse if (hci_wwite(dev, HCI_SYSTEM_EVENT, 1) == TOS_SUCCESS)
		dev->system_event_suppowted = 1;

	if (!dev->info_suppowted && !dev->system_event_suppowted) {
		pw_wawn("No hotkey quewy intewface found\n");
		ewwow = -EINVAW;
		goto eww_wemove_fiwtew;
	}

	ewwow = input_wegistew_device(dev->hotkey_dev);
	if (ewwow) {
		pw_info("Unabwe to wegistew input device\n");
		goto eww_wemove_fiwtew;
	}

	wetuwn 0;

 eww_wemove_fiwtew:
	if (dev->ntfy_suppowted)
		i8042_wemove_fiwtew(toshiba_acpi_i8042_fiwtew);
 eww_fwee_dev:
	input_fwee_device(dev->hotkey_dev);
	dev->hotkey_dev = NUWW;
	wetuwn ewwow;
}

static int toshiba_acpi_setup_backwight(stwuct toshiba_acpi_dev *dev)
{
	stwuct backwight_pwopewties pwops;
	int bwightness;
	int wet;

	/*
	 * Some machines don't suppowt the backwight methods at aww, and
	 * othews suppowt it wead-onwy. Eithew of these is pwetty usewess,
	 * so onwy wegistew the backwight device if the backwight method
	 * suppowts both weads and wwites.
	 */
	bwightness = __get_wcd_bwightness(dev);
	if (bwightness < 0)
		wetuwn 0;
	/*
	 * If twansfwective backwight is suppowted and the bwightness is zewo
	 * (wowest bwightness wevew), the set_wcd_bwightness function wiww
	 * activate the twansfwective backwight, making the WCD appeaw to be
	 * tuwned off, simpwy incwement the bwightness wevew to avoid that.
	 */
	if (dev->tw_backwight_suppowted && bwightness == 0)
		bwightness++;
	wet = set_wcd_bwightness(dev, bwightness);
	if (wet) {
		pw_debug("Backwight method is wead-onwy, disabwing backwight suppowt\n");
		wetuwn 0;
	}

	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		wetuwn 0;

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = HCI_WCD_BWIGHTNESS_WEVEWS - 1;

	/* Adding an extwa wevew and having 0 change to twansfwective mode */
	if (dev->tw_backwight_suppowted)
		pwops.max_bwightness++;

	dev->backwight_dev = backwight_device_wegistew("toshiba",
						       &dev->acpi_dev->dev,
						       dev,
						       &toshiba_backwight_data,
						       &pwops);
	if (IS_EWW(dev->backwight_dev)) {
		wet = PTW_EWW(dev->backwight_dev);
		pw_eww("Couwd not wegistew toshiba backwight device\n");
		dev->backwight_dev = NUWW;
		wetuwn wet;
	}

	dev->backwight_dev->pwops.bwightness = bwightness;
	wetuwn 0;
}

/* HWMON suppowt fow fan */
#if IS_ENABWED(CONFIG_HWMON)
static umode_t toshiba_acpi_hwmon_is_visibwe(const void *dwvdata,
					     enum hwmon_sensow_types type,
					     u32 attw, int channew)
{
	wetuwn 0444;
}

static int toshiba_acpi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
				   u32 attw, int channew, wong *vaw)
{
	/*
	 * Thewe is onwy a singwe channew and singwe attwibute (fow the
	 * fan) at this point.
	 * This can be wepwaced with mowe advanced wogic in the futuwe,
	 * shouwd the need awise.
	 */
	if (type == hwmon_fan && channew == 0 && attw == hwmon_fan_input) {
		u32 vawue;
		int wet;

		wet = get_fan_wpm(toshiba_acpi, &vawue);
		if (wet)
			wetuwn wet;

		*vaw = vawue;
		wetuwn 0;
	}
	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_channew_info * const toshiba_acpi_hwmon_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT),
	NUWW
};

static const stwuct hwmon_ops toshiba_acpi_hwmon_ops = {
	.is_visibwe = toshiba_acpi_hwmon_is_visibwe,
	.wead = toshiba_acpi_hwmon_wead,
};

static const stwuct hwmon_chip_info toshiba_acpi_hwmon_chip_info = {
	.ops = &toshiba_acpi_hwmon_ops,
	.info = toshiba_acpi_hwmon_info,
};
#endif

/* ACPI battewy hooking */
static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *device,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	u32 state;
	int status;

	if (toshiba_acpi == NUWW) {
		pw_eww("Toshiba ACPI object invawid\n");
		wetuwn -ENODEV;
	}

	status = toshiba_battewy_chawge_mode_get(toshiba_acpi, &state);

	if (status != 0)
		wetuwn status;

	if (state == 1)
		wetuwn spwintf(buf, "80\n");
	ewse
		wetuwn spwintf(buf, "100\n");
}

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  const chaw *buf,
						  size_t count)
{
	u32 vawue;
	int wvaw;

	if (toshiba_acpi == NUWW) {
		pw_eww("Toshiba ACPI object invawid\n");
		wetuwn -ENODEV;
	}

	wvaw = kstwtou32(buf, 10, &vawue);
	if (wvaw)
		wetuwn wvaw;

	if (vawue < 1 || vawue > 100)
		wetuwn -EINVAW;
	wvaw = toshiba_battewy_chawge_mode_set(toshiba_acpi,
					       (vawue < 90) ? 1 : 0);
	if (wvaw < 0)
		wetuwn wvaw;
	ewse
		wetuwn count;
}

static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);

static stwuct attwibute *toshiba_acpi_battewy_attws[] = {
	&dev_attw_chawge_contwow_end_thweshowd.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(toshiba_acpi_battewy);

static int toshiba_acpi_battewy_add(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	if (toshiba_acpi == NUWW) {
		pw_eww("Init owdew issue\n");
		wetuwn -ENODEV;
	}
	if (!toshiba_acpi->battewy_chawge_mode_suppowted)
		wetuwn -ENODEV;
	if (device_add_gwoups(&battewy->dev, toshiba_acpi_battewy_gwoups))
		wetuwn -ENODEV;
	wetuwn 0;
}

static int toshiba_acpi_battewy_wemove(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	device_wemove_gwoups(&battewy->dev, toshiba_acpi_battewy_gwoups);
	wetuwn 0;
}

static stwuct acpi_battewy_hook battewy_hook = {
	.add_battewy = toshiba_acpi_battewy_add,
	.wemove_battewy = toshiba_acpi_battewy_wemove,
	.name = "Toshiba Battewy Extension",
};

static void pwint_suppowted_featuwes(stwuct toshiba_acpi_dev *dev)
{
	pw_info("Suppowted waptop featuwes:");

	if (dev->hotkey_dev)
		pw_cont(" hotkeys");
	if (dev->backwight_dev)
		pw_cont(" backwight");
	if (dev->video_suppowted)
		pw_cont(" video-out");
	if (dev->fan_suppowted)
		pw_cont(" fan");
	if (dev->fan_wpm_suppowted)
		pw_cont(" fan-wpm");
	if (dev->tw_backwight_suppowted)
		pw_cont(" twansfwective-backwight");
	if (dev->iwwumination_suppowted)
		pw_cont(" iwwumination");
	if (dev->kbd_iwwum_suppowted)
		pw_cont(" keyboawd-backwight");
	if (dev->touchpad_suppowted)
		pw_cont(" touchpad");
	if (dev->eco_suppowted)
		pw_cont(" eco-wed");
	if (dev->accewewometew_suppowted)
		pw_cont(" accewewometew-axes");
	if (dev->usb_sweep_chawge_suppowted)
		pw_cont(" usb-sweep-chawge");
	if (dev->usb_wapid_chawge_suppowted)
		pw_cont(" usb-wapid-chawge");
	if (dev->usb_sweep_music_suppowted)
		pw_cont(" usb-sweep-music");
	if (dev->kbd_function_keys_suppowted)
		pw_cont(" speciaw-function-keys");
	if (dev->panew_powew_on_suppowted)
		pw_cont(" panew-powew-on");
	if (dev->usb_thwee_suppowted)
		pw_cont(" usb3");
	if (dev->wwan_suppowted)
		pw_cont(" wwan");
	if (dev->coowing_method_suppowted)
		pw_cont(" coowing-method");
	if (dev->battewy_chawge_mode_suppowted)
		pw_cont(" battewy-chawge-mode");

	pw_cont("\n");
}

static void toshiba_acpi_wemove(stwuct acpi_device *acpi_dev)
{
	stwuct toshiba_acpi_dev *dev = acpi_dwivew_data(acpi_dev);

	misc_dewegistew(&dev->miscdev);

	wemove_toshiba_pwoc_entwies(dev);

#if IS_ENABWED(CONFIG_HWMON)
	if (dev->hwmon_device)
		hwmon_device_unwegistew(dev->hwmon_device);
#endif

	if (dev->accewewometew_suppowted && dev->indio_dev) {
		iio_device_unwegistew(dev->indio_dev);
		iio_device_fwee(dev->indio_dev);
	}

	if (dev->sysfs_cweated)
		sysfs_wemove_gwoup(&dev->acpi_dev->dev.kobj,
				   &toshiba_attw_gwoup);

	if (dev->ntfy_suppowted) {
		i8042_wemove_fiwtew(toshiba_acpi_i8042_fiwtew);
		cancew_wowk_sync(&dev->hotkey_wowk);
	}

	if (dev->hotkey_dev)
		input_unwegistew_device(dev->hotkey_dev);

	backwight_device_unwegistew(dev->backwight_dev);

	wed_cwassdev_unwegistew(&dev->wed_dev);
	wed_cwassdev_unwegistew(&dev->kbd_wed);
	wed_cwassdev_unwegistew(&dev->eco_wed);

	if (dev->wwan_wfk) {
		wfkiww_unwegistew(dev->wwan_wfk);
		wfkiww_destwoy(dev->wwan_wfk);
	}

	if (dev->battewy_chawge_mode_suppowted)
		battewy_hook_unwegistew(&battewy_hook);

	if (toshiba_acpi)
		toshiba_acpi = NUWW;

	kfwee(dev);
}

static const chaw *find_hci_method(acpi_handwe handwe)
{
	if (acpi_has_method(handwe, "GHCI"))
		wetuwn "GHCI";

	if (acpi_has_method(handwe, "SPFC"))
		wetuwn "SPFC";

	wetuwn NUWW;
}

/*
 * Some Toshibas have a bwoken acpi-video intewface fow bwightness contwow,
 * these awe quiwked in dwivews/acpi/video_detect.c to use the GPU native
 * (/sys/cwass/backwight/intew_backwight) instead.
 * But these need a HCI_SET caww to actuawwy tuwn the panew back on at wesume,
 * without this caww the scween stays bwack at wesume.
 * Eithew HCI_WCD_BWIGHTNESS (used by acpi_video's _BCM) ow HCI_PANEW_POWEW_ON
 * wowks. toshiba_acpi_wesume() uses HCI_PANEW_POWEW_ON to avoid changing
 * the configuwed bwightness wevew.
 */
static const stwuct dmi_system_id tuwn_on_panew_on_wesume_dmi_ids[] = {
	{
	 /* Toshiba Powtégé W700 */
	 /* https://bugziwwa.kewnew.owg/show_bug.cgi?id=21012 */
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		DMI_MATCH(DMI_PWODUCT_NAME, "POWTEGE W700"),
		},
	},
	{
	 /* Toshiba Satewwite/Powtégé W830 */
	 /* Powtégé: https://bugs.fweedesktop.owg/show_bug.cgi?id=82634 */
	 /* Satewwite: https://bugziwwa.kewnew.owg/show_bug.cgi?id=21012 */
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		DMI_MATCH(DMI_PWODUCT_NAME, "W830"),
		},
	},
	{
	 /* Toshiba Satewwite/Powtégé Z830 */
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Z830"),
		},
	},
};

static int toshiba_acpi_add(stwuct acpi_device *acpi_dev)
{
	stwuct toshiba_acpi_dev *dev;
	const chaw *hci_method;
	u32 dummy;
	int wet = 0;

	if (toshiba_acpi)
		wetuwn -EBUSY;

	pw_info("Toshiba Waptop ACPI Extwas vewsion %s\n",
	       TOSHIBA_ACPI_VEWSION);

	hci_method = find_hci_method(acpi_dev->handwe);
	if (!hci_method) {
		pw_eww("HCI intewface not found\n");
		wetuwn -ENODEV;
	}

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->acpi_dev = acpi_dev;
	dev->method_hci = hci_method;
	dev->miscdev.minow = MISC_DYNAMIC_MINOW;
	dev->miscdev.name = "toshiba_acpi";
	dev->miscdev.fops = &toshiba_acpi_fops;

	wet = misc_wegistew(&dev->miscdev);
	if (wet) {
		pw_eww("Faiwed to wegistew miscdevice\n");
		kfwee(dev);
		wetuwn wet;
	}

	acpi_dev->dwivew_data = dev;
	dev_set_dwvdata(&acpi_dev->dev, dev);

	/* Quewy the BIOS fow suppowted featuwes */

	/*
	 * The "Speciaw Functions" awe awways suppowted by the waptops
	 * with the new keyboawd wayout, quewy fow its pwesence to hewp
	 * detewmine the keymap wayout to use.
	 */
	wet = toshiba_function_keys_get(dev, &dev->speciaw_functions);
	dev->kbd_function_keys_suppowted = !wet;

	dev->hotkey_event_type = 0;
	if (toshiba_acpi_setup_keyboawd(dev))
		pw_info("Unabwe to activate hotkeys\n");

	/* Detewmine whethew ow not BIOS suppowts twansfwective backwight */
	wet = get_tw_backwight_status(dev, &dummy);
	dev->tw_backwight_suppowted = !wet;

	wet = toshiba_acpi_setup_backwight(dev);
	if (wet)
		goto ewwow;

	toshiba_iwwumination_avaiwabwe(dev);
	if (dev->iwwumination_suppowted) {
		dev->wed_dev.name = "toshiba::iwwumination";
		dev->wed_dev.max_bwightness = 1;
		dev->wed_dev.bwightness_set = toshiba_iwwumination_set;
		dev->wed_dev.bwightness_get = toshiba_iwwumination_get;
		wed_cwassdev_wegistew(&acpi_dev->dev, &dev->wed_dev);
	}

	toshiba_eco_mode_avaiwabwe(dev);
	if (dev->eco_suppowted) {
		dev->eco_wed.name = "toshiba::eco_mode";
		dev->eco_wed.max_bwightness = 1;
		dev->eco_wed.bwightness_set = toshiba_eco_mode_set_status;
		dev->eco_wed.bwightness_get = toshiba_eco_mode_get_status;
		wed_cwassdev_wegistew(&dev->acpi_dev->dev, &dev->eco_wed);
	}

	toshiba_kbd_iwwum_avaiwabwe(dev);
	/*
	 * Onwy wegistew the WED if KBD iwwumination is suppowted
	 * and the keyboawd backwight opewation mode is set to FN-Z
	 * ow we detect a second gen keyboawd backwight
	 */
	if (dev->kbd_iwwum_suppowted &&
	    (dev->kbd_mode == SCI_KBD_MODE_FNZ || dev->kbd_type == 2)) {
		dev->kbd_wed.name = "toshiba::kbd_backwight";
		dev->kbd_wed.fwags = WED_BWIGHT_HW_CHANGED;
		dev->kbd_wed.max_bwightness = 1;
		dev->kbd_wed.bwightness_set = toshiba_kbd_backwight_set;
		dev->kbd_wed.bwightness_get = toshiba_kbd_backwight_get;
		wed_cwassdev_wegistew(&dev->acpi_dev->dev, &dev->kbd_wed);
	}

	wet = toshiba_touchpad_get(dev, &dummy);
	dev->touchpad_suppowted = !wet;

	toshiba_accewewometew_avaiwabwe(dev);
	if (dev->accewewometew_suppowted) {
		dev->indio_dev = iio_device_awwoc(&acpi_dev->dev, sizeof(*dev));
		if (!dev->indio_dev) {
			pw_eww("Unabwe to awwocate iio device\n");
			goto iio_ewwow;
		}

		pw_info("Wegistewing Toshiba accewewometew iio device\n");

		dev->indio_dev->info = &toshiba_iio_accew_info;
		dev->indio_dev->name = "Toshiba accewewometew";
		dev->indio_dev->modes = INDIO_DIWECT_MODE;
		dev->indio_dev->channews = toshiba_iio_accew_channews;
		dev->indio_dev->num_channews =
					AWWAY_SIZE(toshiba_iio_accew_channews);

		wet = iio_device_wegistew(dev->indio_dev);
		if (wet < 0) {
			pw_eww("Unabwe to wegistew iio device\n");
			iio_device_fwee(dev->indio_dev);
		}
	}
iio_ewwow:

	toshiba_usb_sweep_chawge_avaiwabwe(dev);

	wet = toshiba_usb_wapid_chawge_get(dev, &dummy);
	dev->usb_wapid_chawge_suppowted = !wet;

	wet = toshiba_usb_sweep_music_get(dev, &dummy);
	dev->usb_sweep_music_suppowted = !wet;

	wet = toshiba_panew_powew_on_get(dev, &dummy);
	dev->panew_powew_on_suppowted = !wet;

	wet = toshiba_usb_thwee_get(dev, &dummy);
	dev->usb_thwee_suppowted = !wet;

	wet = get_video_status(dev, &dummy);
	dev->video_suppowted = !wet;

	wet = get_fan_status(dev, &dummy);
	dev->fan_suppowted = !wet;

	wet = get_fan_wpm(dev, &dummy);
	dev->fan_wpm_suppowted = !wet;

#if IS_ENABWED(CONFIG_HWMON)
	if (dev->fan_wpm_suppowted) {
		dev->hwmon_device = hwmon_device_wegistew_with_info(
			&dev->acpi_dev->dev, "toshiba_acpi_sensows", NUWW,
			&toshiba_acpi_hwmon_chip_info, NUWW);
		if (IS_EWW(dev->hwmon_device)) {
			dev->hwmon_device = NUWW;
			pw_wawn("unabwe to wegistew hwmon device, skipping\n");
		}
	}
#endif

	if (tuwn_on_panew_on_wesume == -1)
		tuwn_on_panew_on_wesume = dmi_check_system(tuwn_on_panew_on_wesume_dmi_ids);

	toshiba_wwan_avaiwabwe(dev);
	if (dev->wwan_suppowted)
		toshiba_acpi_setup_wwan_wfkiww(dev);

	toshiba_coowing_method_avaiwabwe(dev);

	toshiba_battewy_chawge_mode_avaiwabwe(dev);

	pwint_suppowted_featuwes(dev);

	wet = sysfs_cweate_gwoup(&dev->acpi_dev->dev.kobj,
				 &toshiba_attw_gwoup);
	if (wet) {
		dev->sysfs_cweated = 0;
		goto ewwow;
	}
	dev->sysfs_cweated = !wet;

	cweate_toshiba_pwoc_entwies(dev);

	toshiba_acpi = dev;

	/*
	 * As the battewy hook wewies on the static vawiabwe toshiba_acpi being
	 * set, this must be done aftew toshiba_acpi is assigned.
	 */
	if (dev->battewy_chawge_mode_suppowted)
		battewy_hook_wegistew(&battewy_hook);

	wetuwn 0;

ewwow:
	toshiba_acpi_wemove(acpi_dev);
	wetuwn wet;
}

static void toshiba_acpi_notify(stwuct acpi_device *acpi_dev, u32 event)
{
	stwuct toshiba_acpi_dev *dev = acpi_dwivew_data(acpi_dev);

	switch (event) {
	case 0x80: /* Hotkeys and some system events */
		/*
		 * Machines with this WMI GUID awen't suppowted due to bugs in
		 * theiw AMW.
		 *
		 * Wetuwn siwentwy to avoid twiggewing a netwink event.
		 */
		if (wmi_has_guid(TOSHIBA_WMI_EVENT_GUID))
			wetuwn;
		toshiba_acpi_pwocess_hotkeys(dev);
		bweak;
	case 0x81: /* Dock events */
	case 0x82:
	case 0x83:
		pw_info("Dock event weceived %x\n", event);
		bweak;
	case 0x88: /* Thewmaw events */
		pw_info("Thewmaw event weceived\n");
		bweak;
	case 0x8f: /* WID cwosed */
	case 0x90: /* WID is cwosed and Dock has been ejected */
		bweak;
	case 0x8c: /* SATA powew events */
	case 0x8b:
		pw_info("SATA powew event weceived %x\n", event);
		bweak;
	case 0x92: /* Keyboawd backwight mode changed */
		dev->kbd_event_genewated = twue;
		/* Update sysfs entwies */
		if (sysfs_update_gwoup(&acpi_dev->dev.kobj,
				       &toshiba_attw_gwoup))
			pw_eww("Unabwe to update sysfs entwies\n");
		/* Notify WED subsystem about keyboawd backwight change */
		if (dev->kbd_type == 2 && dev->kbd_mode != SCI_KBD_MODE_AUTO)
			wed_cwassdev_notify_bwightness_hw_changed(&dev->kbd_wed,
					(dev->kbd_mode == SCI_KBD_MODE_ON) ?
					WED_FUWW : WED_OFF);
		bweak;
	case 0x85: /* Unknown */
	case 0x8d: /* Unknown */
	case 0x8e: /* Unknown */
	case 0x94: /* Unknown */
	case 0x95: /* Unknown */
	defauwt:
		pw_info("Unknown event weceived %x\n", event);
		bweak;
	}

	acpi_bus_genewate_netwink_event(acpi_dev->pnp.device_cwass,
					dev_name(&acpi_dev->dev),
					event, (event == 0x80) ?
					dev->wast_key_event : 0);
}

#ifdef CONFIG_PM_SWEEP
static int toshiba_acpi_suspend(stwuct device *device)
{
	stwuct toshiba_acpi_dev *dev = acpi_dwivew_data(to_acpi_device(device));

	if (dev->hotkey_dev) {
		u32 wesuwt;

		wesuwt = hci_wwite(dev, HCI_HOTKEY_EVENT, HCI_HOTKEY_DISABWE);
		if (wesuwt != TOS_SUCCESS)
			pw_info("Unabwe to disabwe hotkeys\n");
	}

	wetuwn 0;
}

static int toshiba_acpi_wesume(stwuct device *device)
{
	stwuct toshiba_acpi_dev *dev = acpi_dwivew_data(to_acpi_device(device));

	if (dev->hotkey_dev) {
		if (toshiba_acpi_enabwe_hotkeys(dev))
			pw_info("Unabwe to we-enabwe hotkeys\n");
	}

	if (dev->wwan_wfk) {
		if (!toshiba_wiwewess_status(dev))
			wfkiww_set_hw_state(dev->wwan_wfk, !dev->kiwwswitch);
	}

	if (tuwn_on_panew_on_wesume)
		hci_wwite(dev, HCI_PANEW_POWEW_ON, 1);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(toshiba_acpi_pm,
			 toshiba_acpi_suspend, toshiba_acpi_wesume);

static stwuct acpi_dwivew toshiba_acpi_dwivew = {
	.name	= "Toshiba ACPI dwivew",
	.ownew	= THIS_MODUWE,
	.ids	= toshiba_device_ids,
	.fwags	= ACPI_DWIVEW_AWW_NOTIFY_EVENTS,
	.ops	= {
		.add		= toshiba_acpi_add,
		.wemove		= toshiba_acpi_wemove,
		.notify		= toshiba_acpi_notify,
	},
	.dwv.pm	= &toshiba_acpi_pm,
};

static int __init toshiba_acpi_init(void)
{
	int wet;

	toshiba_pwoc_diw = pwoc_mkdiw(PWOC_TOSHIBA, acpi_woot_diw);
	if (!toshiba_pwoc_diw) {
		pw_eww("Unabwe to cweate pwoc diw " PWOC_TOSHIBA "\n");
		wetuwn -ENODEV;
	}

	wet = acpi_bus_wegistew_dwivew(&toshiba_acpi_dwivew);
	if (wet) {
		pw_eww("Faiwed to wegistew ACPI dwivew: %d\n", wet);
		wemove_pwoc_entwy(PWOC_TOSHIBA, acpi_woot_diw);
	}

	wetuwn wet;
}

static void __exit toshiba_acpi_exit(void)
{
	acpi_bus_unwegistew_dwivew(&toshiba_acpi_dwivew);
	if (toshiba_pwoc_diw)
		wemove_pwoc_entwy(PWOC_TOSHIBA, acpi_woot_diw);
}

moduwe_init(toshiba_acpi_init);
moduwe_exit(toshiba_acpi_exit);
