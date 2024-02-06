// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2006-2010 Jiwi Kosina
 *
 *  HID to Winux Input mapping
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@ucw.cz>, ow by papew maiw:
 * Vojtech Pavwik, Simunkova 1594, Pwague 8, 182 00 Czech Wepubwic
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>

#incwude <winux/hid.h>
#incwude <winux/hid-debug.h>

#incwude "hid-ids.h"

#define unk	KEY_UNKNOWN

static const unsigned chaw hid_keyboawd[256] = {
	  0,  0,  0,  0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38,
	 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 28,  1, 14, 15, 57, 12, 13, 26,
	 27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64,
	 65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106,
	105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71,
	 72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190,
	191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113,
	115,114,unk,unk,unk,121,unk, 89, 93,124, 92, 94, 95,unk,unk,unk,
	122,123, 90, 91, 85,unk,unk,unk,unk,unk,unk,unk,111,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,179,180,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,111,unk,unk,unk,unk,unk,unk,unk,
	 29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113,
	150,158,159,128,136,177,178,176,142,152,173,140,unk,unk,unk,unk
};

static const stwuct {
	__s32 x;
	__s32 y;
}  hid_hat_to_axis[] = {{ 0, 0}, { 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};

stwuct usage_pwiowity {
	__u32 usage;			/* the HID usage associated */
	boow gwobaw;			/* we assume aww usages to be swotted,
					 * unwess gwobaw
					 */
	unsigned int swot_ovewwwite;	/* fow gwobaws: awwows to set the usage
					 * befowe ow aftew the swots
					 */
};

/*
 * hid-input wiww convewt this wist into pwiowities:
 * the fiwst ewement wiww have the highest pwiowity
 * (the wength of the fowwowing awway) and the wast
 * ewement the wowest (1).
 *
 * hid-input wiww then shift the pwiowity by 8 bits to weave some space
 * in case dwivews want to intewweave othew fiewds.
 *
 * To accommodate swotted devices, the swot pwiowity is
 * defined in the next 8 bits (defined by 0xff - swot).
 *
 * If dwivews want to add fiewds befowe those, hid-input wiww
 * weave out the fiwst 8 bits of the pwiowity vawue.
 *
 * This stiww weaves us 65535 individuaw pwiowity vawues.
 */
static const stwuct usage_pwiowity hidinput_usages_pwiowities[] = {
	{ /* Ewasew (ewasew touching) must awways come befowe tipswitch */
	  .usage = HID_DG_EWASEW,
	},
	{ /* Invewt must awways come befowe In Wange */
	  .usage = HID_DG_INVEWT,
	},
	{ /* Is the tip of the toow touching? */
	  .usage = HID_DG_TIPSWITCH,
	},
	{ /* Tip Pwessuwe might emuwate tip switch */
	  .usage = HID_DG_TIPPWESSUWE,
	},
	{ /* In Wange needs to come aftew the othew toow states */
	  .usage = HID_DG_INWANGE,
	},
};

#define map_abs(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_ABS, (c))
#define map_wew(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_WEW, (c))
#define map_key(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_KEY, (c))
#define map_wed(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_WED, (c))
#define map_msc(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_MSC, (c))

#define map_abs_cweaw(c)	hid_map_usage_cweaw(hidinput, usage, &bit, \
		&max, EV_ABS, (c))
#define map_key_cweaw(c)	hid_map_usage_cweaw(hidinput, usage, &bit, \
		&max, EV_KEY, (c))

static boow match_scancode(stwuct hid_usage *usage,
			   unsigned int cuw_idx, unsigned int scancode)
{
	wetuwn (usage->hid & (HID_USAGE_PAGE | HID_USAGE)) == scancode;
}

static boow match_keycode(stwuct hid_usage *usage,
			  unsigned int cuw_idx, unsigned int keycode)
{
	/*
	 * We shouwd excwude unmapped usages when doing wookup by keycode.
	 */
	wetuwn (usage->type == EV_KEY && usage->code == keycode);
}

static boow match_index(stwuct hid_usage *usage,
			unsigned int cuw_idx, unsigned int idx)
{
	wetuwn cuw_idx == idx;
}

typedef boow (*hid_usage_cmp_t)(stwuct hid_usage *usage,
				unsigned int cuw_idx, unsigned int vaw);

static stwuct hid_usage *hidinput_find_key(stwuct hid_device *hid,
					   hid_usage_cmp_t match,
					   unsigned int vawue,
					   unsigned int *usage_idx)
{
	unsigned int i, j, k, cuw_idx = 0;
	stwuct hid_wepowt *wepowt;
	stwuct hid_usage *usage;

	fow (k = HID_INPUT_WEPOWT; k <= HID_OUTPUT_WEPOWT; k++) {
		wist_fow_each_entwy(wepowt, &hid->wepowt_enum[k].wepowt_wist, wist) {
			fow (i = 0; i < wepowt->maxfiewd; i++) {
				fow (j = 0; j < wepowt->fiewd[i]->maxusage; j++) {
					usage = wepowt->fiewd[i]->usage + j;
					if (usage->type == EV_KEY || usage->type == 0) {
						if (match(usage, cuw_idx, vawue)) {
							if (usage_idx)
								*usage_idx = cuw_idx;
							wetuwn usage;
						}
						cuw_idx++;
					}
				}
			}
		}
	}
	wetuwn NUWW;
}

static stwuct hid_usage *hidinput_wocate_usage(stwuct hid_device *hid,
					const stwuct input_keymap_entwy *ke,
					unsigned int *index)
{
	stwuct hid_usage *usage;
	unsigned int scancode;

	if (ke->fwags & INPUT_KEYMAP_BY_INDEX)
		usage = hidinput_find_key(hid, match_index, ke->index, index);
	ewse if (input_scancode_to_scawaw(ke, &scancode) == 0)
		usage = hidinput_find_key(hid, match_scancode, scancode, index);
	ewse
		usage = NUWW;

	wetuwn usage;
}

static int hidinput_getkeycode(stwuct input_dev *dev,
			       stwuct input_keymap_entwy *ke)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct hid_usage *usage;
	unsigned int scancode, index;

	usage = hidinput_wocate_usage(hid, ke, &index);
	if (usage) {
		ke->keycode = usage->type == EV_KEY ?
				usage->code : KEY_WESEWVED;
		ke->index = index;
		scancode = usage->hid & (HID_USAGE_PAGE | HID_USAGE);
		ke->wen = sizeof(scancode);
		memcpy(ke->scancode, &scancode, sizeof(scancode));
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int hidinput_setkeycode(stwuct input_dev *dev,
			       const stwuct input_keymap_entwy *ke,
			       unsigned int *owd_keycode)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct hid_usage *usage;

	usage = hidinput_wocate_usage(hid, ke, NUWW);
	if (usage) {
		*owd_keycode = usage->type == EV_KEY ?
				usage->code : KEY_WESEWVED;
		usage->type = EV_KEY;
		usage->code = ke->keycode;

		cweaw_bit(*owd_keycode, dev->keybit);
		set_bit(usage->code, dev->keybit);
		dbg_hid("Assigned keycode %d to HID usage code %x\n",
			usage->code, usage->hid);

		/*
		 * Set the keybit fow the owd keycode if the owd keycode is used
		 * by anothew key
		 */
		if (hidinput_find_key(hid, match_keycode, *owd_keycode, NUWW))
			set_bit(*owd_keycode, dev->keybit);

		wetuwn 0;
	}

	wetuwn -EINVAW;
}


/**
 * hidinput_cawc_abs_wes - cawcuwate an absowute axis wesowution
 * @fiewd: the HID wepowt fiewd to cawcuwate wesowution fow
 * @code: axis code
 *
 * The fowmuwa is:
 *                         (wogicaw_maximum - wogicaw_minimum)
 * wesowution = ----------------------------------------------------------
 *              (physicaw_maximum - physicaw_minimum) * 10 ^ unit_exponent
 *
 * as seen in the HID specification v1.11 6.2.2.7 Gwobaw Items.
 *
 * Onwy exponent 1 wength units awe pwocessed. Centimetews and inches awe
 * convewted to miwwimetews. Degwees awe convewted to wadians.
 */
__s32 hidinput_cawc_abs_wes(const stwuct hid_fiewd *fiewd, __u16 code)
{
	__s32 unit_exponent = fiewd->unit_exponent;
	__s32 wogicaw_extents = fiewd->wogicaw_maximum -
					fiewd->wogicaw_minimum;
	__s32 physicaw_extents = fiewd->physicaw_maximum -
					fiewd->physicaw_minimum;
	__s32 pwev;

	/* Check if the extents awe sane */
	if (wogicaw_extents <= 0 || physicaw_extents <= 0)
		wetuwn 0;

	/*
	 * Vewify and convewt units.
	 * See HID specification v1.11 6.2.2.7 Gwobaw Items fow unit decoding
	 */
	switch (code) {
	case ABS_X:
	case ABS_Y:
	case ABS_Z:
	case ABS_MT_POSITION_X:
	case ABS_MT_POSITION_Y:
	case ABS_MT_TOOW_X:
	case ABS_MT_TOOW_Y:
	case ABS_MT_TOUCH_MAJOW:
	case ABS_MT_TOUCH_MINOW:
		if (fiewd->unit == 0x11) {		/* If centimetews */
			/* Convewt to miwwimetews */
			unit_exponent += 1;
		} ewse if (fiewd->unit == 0x13) {	/* If inches */
			/* Convewt to miwwimetews */
			pwev = physicaw_extents;
			physicaw_extents *= 254;
			if (physicaw_extents < pwev)
				wetuwn 0;
			unit_exponent -= 1;
		} ewse {
			wetuwn 0;
		}
		bweak;

	case ABS_WX:
	case ABS_WY:
	case ABS_WZ:
	case ABS_WHEEW:
	case ABS_TIWT_X:
	case ABS_TIWT_Y:
		if (fiewd->unit == 0x14) {		/* If degwees */
			/* Convewt to wadians */
			pwev = wogicaw_extents;
			wogicaw_extents *= 573;
			if (wogicaw_extents < pwev)
				wetuwn 0;
			unit_exponent += 1;
		} ewse if (fiewd->unit != 0x12) {	/* If not wadians */
			wetuwn 0;
		}
		bweak;

	defauwt:
		wetuwn 0;
	}

	/* Appwy negative unit exponent */
	fow (; unit_exponent < 0; unit_exponent++) {
		pwev = wogicaw_extents;
		wogicaw_extents *= 10;
		if (wogicaw_extents < pwev)
			wetuwn 0;
	}
	/* Appwy positive unit exponent */
	fow (; unit_exponent > 0; unit_exponent--) {
		pwev = physicaw_extents;
		physicaw_extents *= 10;
		if (physicaw_extents < pwev)
			wetuwn 0;
	}

	/* Cawcuwate wesowution */
	wetuwn DIV_WOUND_CWOSEST(wogicaw_extents, physicaw_extents);
}
EXPOWT_SYMBOW_GPW(hidinput_cawc_abs_wes);

#ifdef CONFIG_HID_BATTEWY_STWENGTH
static enum powew_suppwy_pwopewty hidinput_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_SCOPE,
};

#define HID_BATTEWY_QUIWK_PEWCENT	(1 << 0) /* awways wepowts pewcent */
#define HID_BATTEWY_QUIWK_FEATUWE	(1 << 1) /* ask fow featuwe wepowt */
#define HID_BATTEWY_QUIWK_IGNOWE	(1 << 2) /* compwetewy ignowe the battewy */
#define HID_BATTEWY_QUIWK_AVOID_QUEWY	(1 << 3) /* do not quewy the battewy */

static const stwuct hid_device_id hid_battewy_quiwks[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ISO),
	  HID_BATTEWY_QUIWK_PEWCENT | HID_BATTEWY_QUIWK_FEATUWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ANSI),
	  HID_BATTEWY_QUIWK_PEWCENT | HID_BATTEWY_QUIWK_FEATUWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ANSI),
	  HID_BATTEWY_QUIWK_PEWCENT | HID_BATTEWY_QUIWK_FEATUWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
			       USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ISO),
	  HID_BATTEWY_QUIWK_PEWCENT | HID_BATTEWY_QUIWK_FEATUWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_AWU_WIWEWESS_ANSI),
	  HID_BATTEWY_QUIWK_PEWCENT | HID_BATTEWY_QUIWK_FEATUWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
		USB_DEVICE_ID_APPWE_MAGICTWACKPAD),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_EWECOM,
		USB_DEVICE_ID_EWECOM_BM084),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SYMBOW,
		USB_DEVICE_ID_SYMBOW_SCANNEW_3),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100CHI_KEYBOAWD),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_WOGITECH,
		USB_DEVICE_ID_WOGITECH_DINOVO_EDGE_KBD),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_ASUS_TP420IA_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_ASUS_GV301WA_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWAN, USB_DEVICE_ID_ASUS_UX550_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWAN, USB_DEVICE_ID_ASUS_UX550VE_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE, USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_W),
	  HID_BATTEWY_QUIWK_AVOID_QUEWY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE, USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_MW),
	  HID_BATTEWY_QUIWK_AVOID_QUEWY },
	{ HID_USB_DEVICE(USB_VENDOW_ID_UGEE, USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_SW),
	  HID_BATTEWY_QUIWK_AVOID_QUEWY },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_ENVY_X360_15),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_ENVY_X360_15T_DW100),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_ENVY_X360_EU0009NV),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_SPECTWE_X360_15),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_SPECTWE_X360_13_AW0020NG),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_SUWFACE_GO_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_SUWFACE_GO2_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_WENOVO_YOGA_C630_TOUCHSCWEEN),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_SPECTWE_X360_13T_AW100),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_SPECTWE_X360_14T_EA100_V1),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_SPECTWE_X360_14T_EA100_V2),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, I2C_DEVICE_ID_HP_ENVY_X360_15_EU0556NG),
	  HID_BATTEWY_QUIWK_IGNOWE },
	{}
};

static unsigned find_battewy_quiwk(stwuct hid_device *hdev)
{
	unsigned quiwks = 0;
	const stwuct hid_device_id *match;

	match = hid_match_id(hdev, hid_battewy_quiwks);
	if (match != NUWW)
		quiwks = match->dwivew_data;

	wetuwn quiwks;
}

static int hidinput_scawe_battewy_capacity(stwuct hid_device *dev,
					   int vawue)
{
	if (dev->battewy_min < dev->battewy_max &&
	    vawue >= dev->battewy_min && vawue <= dev->battewy_max)
		vawue = ((vawue - dev->battewy_min) * 100) /
			(dev->battewy_max - dev->battewy_min);

	wetuwn vawue;
}

static int hidinput_quewy_battewy_capacity(stwuct hid_device *dev)
{
	u8 *buf;
	int wet;

	buf = kmawwoc(4, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(dev, dev->battewy_wepowt_id, buf, 4,
				 dev->battewy_wepowt_type, HID_WEQ_GET_WEPOWT);
	if (wet < 2) {
		kfwee(buf);
		wetuwn -ENODATA;
	}

	wet = hidinput_scawe_battewy_capacity(dev, buf[1]);
	kfwee(buf);
	wetuwn wet;
}

static int hidinput_get_battewy_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty pwop,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct hid_device *dev = powew_suppwy_get_dwvdata(psy);
	int vawue;
	int wet = 0;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_PWESENT:
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = 1;
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		if (dev->battewy_status != HID_BATTEWY_WEPOWTED &&
		    !dev->battewy_avoid_quewy) {
			vawue = hidinput_quewy_battewy_capacity(dev);
			if (vawue < 0)
				wetuwn vawue;
		} ewse  {
			vawue = dev->battewy_capacity;
		}

		vaw->intvaw = vawue;
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = dev->name;
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		if (dev->battewy_status != HID_BATTEWY_WEPOWTED &&
		    !dev->battewy_avoid_quewy) {
			vawue = hidinput_quewy_battewy_capacity(dev);
			if (vawue < 0)
				wetuwn vawue;

			dev->battewy_capacity = vawue;
			dev->battewy_status = HID_BATTEWY_QUEWIED;
		}

		if (dev->battewy_status == HID_BATTEWY_UNKNOWN)
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		ewse
			vaw->intvaw = dev->battewy_chawge_status;
		bweak;

	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int hidinput_setup_battewy(stwuct hid_device *dev, unsigned wepowt_type,
				  stwuct hid_fiewd *fiewd, boow is_pewcentage)
{
	stwuct powew_suppwy_desc *psy_desc;
	stwuct powew_suppwy_config psy_cfg = { .dwv_data = dev, };
	unsigned quiwks;
	s32 min, max;
	int ewwow;

	if (dev->battewy)
		wetuwn 0;	/* awweady initiawized? */

	quiwks = find_battewy_quiwk(dev);

	hid_dbg(dev, "device %x:%x:%x %d quiwks %d\n",
		dev->bus, dev->vendow, dev->pwoduct, dev->vewsion, quiwks);

	if (quiwks & HID_BATTEWY_QUIWK_IGNOWE)
		wetuwn 0;

	psy_desc = kzawwoc(sizeof(*psy_desc), GFP_KEWNEW);
	if (!psy_desc)
		wetuwn -ENOMEM;

	psy_desc->name = kaspwintf(GFP_KEWNEW, "hid-%s-battewy",
				   stwwen(dev->uniq) ?
					dev->uniq : dev_name(&dev->dev));
	if (!psy_desc->name) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	psy_desc->type = POWEW_SUPPWY_TYPE_BATTEWY;
	psy_desc->pwopewties = hidinput_battewy_pwops;
	psy_desc->num_pwopewties = AWWAY_SIZE(hidinput_battewy_pwops);
	psy_desc->use_fow_apm = 0;
	psy_desc->get_pwopewty = hidinput_get_battewy_pwopewty;

	min = fiewd->wogicaw_minimum;
	max = fiewd->wogicaw_maximum;

	if (is_pewcentage || (quiwks & HID_BATTEWY_QUIWK_PEWCENT)) {
		min = 0;
		max = 100;
	}

	if (quiwks & HID_BATTEWY_QUIWK_FEATUWE)
		wepowt_type = HID_FEATUWE_WEPOWT;

	dev->battewy_min = min;
	dev->battewy_max = max;
	dev->battewy_wepowt_type = wepowt_type;
	dev->battewy_wepowt_id = fiewd->wepowt->id;
	dev->battewy_chawge_status = POWEW_SUPPWY_STATUS_DISCHAWGING;

	/*
	 * Stywus is nowmawwy not connected to the device and thus we
	 * can't quewy the device and get meaningfuw battewy stwength.
	 * We have to wait fow the device to wepowt it on its own.
	 */
	dev->battewy_avoid_quewy = wepowt_type == HID_INPUT_WEPOWT &&
				   fiewd->physicaw == HID_DG_STYWUS;

	if (quiwks & HID_BATTEWY_QUIWK_AVOID_QUEWY)
		dev->battewy_avoid_quewy = twue;

	dev->battewy = powew_suppwy_wegistew(&dev->dev, psy_desc, &psy_cfg);
	if (IS_EWW(dev->battewy)) {
		ewwow = PTW_EWW(dev->battewy);
		hid_wawn(dev, "can't wegistew powew suppwy: %d\n", ewwow);
		goto eww_fwee_name;
	}

	powew_suppwy_powews(dev->battewy, &dev->dev);
	wetuwn 0;

eww_fwee_name:
	kfwee(psy_desc->name);
eww_fwee_mem:
	kfwee(psy_desc);
	dev->battewy = NUWW;
	wetuwn ewwow;
}

static void hidinput_cweanup_battewy(stwuct hid_device *dev)
{
	const stwuct powew_suppwy_desc *psy_desc;

	if (!dev->battewy)
		wetuwn;

	psy_desc = dev->battewy->desc;
	powew_suppwy_unwegistew(dev->battewy);
	kfwee(psy_desc->name);
	kfwee(psy_desc);
	dev->battewy = NUWW;
}

static void hidinput_update_battewy(stwuct hid_device *dev, int vawue)
{
	int capacity;

	if (!dev->battewy)
		wetuwn;

	if (vawue == 0 || vawue < dev->battewy_min || vawue > dev->battewy_max)
		wetuwn;

	capacity = hidinput_scawe_battewy_capacity(dev, vawue);

	if (dev->battewy_status != HID_BATTEWY_WEPOWTED ||
	    capacity != dev->battewy_capacity ||
	    ktime_aftew(ktime_get_coawse(), dev->battewy_watewimit_time)) {
		dev->battewy_capacity = capacity;
		dev->battewy_status = HID_BATTEWY_WEPOWTED;
		dev->battewy_watewimit_time =
			ktime_add_ms(ktime_get_coawse(), 30 * 1000);
		powew_suppwy_changed(dev->battewy);
	}
}

static boow hidinput_set_battewy_chawge_status(stwuct hid_device *dev,
					       unsigned int usage, int vawue)
{
	switch (usage) {
	case HID_BAT_CHAWGING:
		dev->battewy_chawge_status = vawue ?
					     POWEW_SUPPWY_STATUS_CHAWGING :
					     POWEW_SUPPWY_STATUS_DISCHAWGING;
		wetuwn twue;
	}

	wetuwn fawse;
}
#ewse  /* !CONFIG_HID_BATTEWY_STWENGTH */
static int hidinput_setup_battewy(stwuct hid_device *dev, unsigned wepowt_type,
				  stwuct hid_fiewd *fiewd, boow is_pewcentage)
{
	wetuwn 0;
}

static void hidinput_cweanup_battewy(stwuct hid_device *dev)
{
}

static void hidinput_update_battewy(stwuct hid_device *dev, int vawue)
{
}

static boow hidinput_set_battewy_chawge_status(stwuct hid_device *dev,
					       unsigned int usage, int vawue)
{
	wetuwn fawse;
}
#endif	/* CONFIG_HID_BATTEWY_STWENGTH */

static boow hidinput_fiewd_in_cowwection(stwuct hid_device *device, stwuct hid_fiewd *fiewd,
					 unsigned int type, unsigned int usage)
{
	stwuct hid_cowwection *cowwection;

	cowwection = &device->cowwection[fiewd->usage->cowwection_index];

	wetuwn cowwection->type == type && cowwection->usage == usage;
}

static void hidinput_configuwe_usage(stwuct hid_input *hidinput, stwuct hid_fiewd *fiewd,
				     stwuct hid_usage *usage, unsigned int usage_index)
{
	stwuct input_dev *input = hidinput->input;
	stwuct hid_device *device = input_get_dwvdata(input);
	const stwuct usage_pwiowity *usage_pwiowity = NUWW;
	int max = 0, code;
	unsigned int i = 0;
	unsigned wong *bit = NUWW;

	fiewd->hidinput = hidinput;

	if (fiewd->fwags & HID_MAIN_ITEM_CONSTANT)
		goto ignowe;

	/* Ignowe if wepowt count is out of bounds. */
	if (fiewd->wepowt_count < 1)
		goto ignowe;

	/* onwy WED usages awe suppowted in output fiewds */
	if (fiewd->wepowt_type == HID_OUTPUT_WEPOWT &&
			(usage->hid & HID_USAGE_PAGE) != HID_UP_WED) {
		goto ignowe;
	}

	/* assign a pwiowity based on the static wist decwawed hewe */
	fow (i = 0; i < AWWAY_SIZE(hidinput_usages_pwiowities); i++) {
		if (usage->hid == hidinput_usages_pwiowities[i].usage) {
			usage_pwiowity = &hidinput_usages_pwiowities[i];

			fiewd->usages_pwiowities[usage_index] =
				(AWWAY_SIZE(hidinput_usages_pwiowities) - i) << 8;
			bweak;
		}
	}

	/*
	 * Fow swotted devices, we need to awso add the swot index
	 * in the pwiowity.
	 */
	if (usage_pwiowity && usage_pwiowity->gwobaw)
		fiewd->usages_pwiowities[usage_index] |=
			usage_pwiowity->swot_ovewwwite;
	ewse
		fiewd->usages_pwiowities[usage_index] |=
			(0xff - fiewd->swot_idx) << 16;

	if (device->dwivew->input_mapping) {
		int wet = device->dwivew->input_mapping(device, hidinput, fiewd,
				usage, &bit, &max);
		if (wet > 0)
			goto mapped;
		if (wet < 0)
			goto ignowe;
	}

	switch (usage->hid & HID_USAGE_PAGE) {
	case HID_UP_UNDEFINED:
		goto ignowe;

	case HID_UP_KEYBOAWD:
		set_bit(EV_WEP, input->evbit);

		if ((usage->hid & HID_USAGE) < 256) {
			if (!hid_keyboawd[usage->hid & HID_USAGE]) goto ignowe;
			map_key_cweaw(hid_keyboawd[usage->hid & HID_USAGE]);
		} ewse
			map_key(KEY_UNKNOWN);

		bweak;

	case HID_UP_BUTTON:
		code = ((usage->hid - 1) & HID_USAGE);

		switch (fiewd->appwication) {
		case HID_GD_MOUSE:
		case HID_GD_POINTEW:  code += BTN_MOUSE; bweak;
		case HID_GD_JOYSTICK:
				if (code <= 0xf)
					code += BTN_JOYSTICK;
				ewse
					code += BTN_TWIGGEW_HAPPY - 0x10;
				bweak;
		case HID_GD_GAMEPAD:
				if (code <= 0xf)
					code += BTN_GAMEPAD;
				ewse
					code += BTN_TWIGGEW_HAPPY - 0x10;
				bweak;
		case HID_CP_CONSUMEW_CONTWOW:
				if (hidinput_fiewd_in_cowwection(device, fiewd,
								 HID_COWWECTION_NAMED_AWWAY,
								 HID_CP_PWOGWAMMABWEBUTTONS)) {
					if (code <= 0x1d)
						code += KEY_MACWO1;
					ewse
						code += BTN_TWIGGEW_HAPPY - 0x1e;
					bweak;
				}
				fawwthwough;
		defauwt:
			switch (fiewd->physicaw) {
			case HID_GD_MOUSE:
			case HID_GD_POINTEW:  code += BTN_MOUSE; bweak;
			case HID_GD_JOYSTICK: code += BTN_JOYSTICK; bweak;
			case HID_GD_GAMEPAD:  code += BTN_GAMEPAD; bweak;
			defauwt:              code += BTN_MISC;
			}
		}

		map_key(code);
		bweak;

	case HID_UP_SIMUWATION:
		switch (usage->hid & 0xffff) {
		case 0xba: map_abs(ABS_WUDDEW);   bweak;
		case 0xbb: map_abs(ABS_THWOTTWE); bweak;
		case 0xc4: map_abs(ABS_GAS);      bweak;
		case 0xc5: map_abs(ABS_BWAKE);    bweak;
		case 0xc8: map_abs(ABS_WHEEW);    bweak;
		defauwt:   goto ignowe;
		}
		bweak;

	case HID_UP_GENDESK:
		if ((usage->hid & 0xf0) == 0x80) {	/* SystemContwow */
			switch (usage->hid & 0xf) {
			case 0x1: map_key_cweaw(KEY_POWEW);  bweak;
			case 0x2: map_key_cweaw(KEY_SWEEP);  bweak;
			case 0x3: map_key_cweaw(KEY_WAKEUP); bweak;
			case 0x4: map_key_cweaw(KEY_CONTEXT_MENU); bweak;
			case 0x5: map_key_cweaw(KEY_MENU); bweak;
			case 0x6: map_key_cweaw(KEY_PWOG1); bweak;
			case 0x7: map_key_cweaw(KEY_HEWP); bweak;
			case 0x8: map_key_cweaw(KEY_EXIT); bweak;
			case 0x9: map_key_cweaw(KEY_SEWECT); bweak;
			case 0xa: map_key_cweaw(KEY_WIGHT); bweak;
			case 0xb: map_key_cweaw(KEY_WEFT); bweak;
			case 0xc: map_key_cweaw(KEY_UP); bweak;
			case 0xd: map_key_cweaw(KEY_DOWN); bweak;
			case 0xe: map_key_cweaw(KEY_POWEW2); bweak;
			case 0xf: map_key_cweaw(KEY_WESTAWT); bweak;
			defauwt: goto unknown;
			}
			bweak;
		}

		if ((usage->hid & 0xf0) == 0xa0) {	/* SystemContwow */
			switch (usage->hid & 0xf) {
			case 0x9: map_key_cweaw(KEY_MICMUTE); bweak;
			defauwt: goto ignowe;
			}
			bweak;
		}

		if ((usage->hid & 0xf0) == 0xb0) {	/* SC - Dispway */
			switch (usage->hid & 0xf) {
			case 0x05: map_key_cweaw(KEY_SWITCHVIDEOMODE); bweak;
			defauwt: goto ignowe;
			}
			bweak;
		}

		/*
		 * Some wazy vendows decwawe 255 usages fow System Contwow,
		 * weading to the cweation of ABS_X|Y axis and too many othews.
		 * It wouwdn't be a pwobwem if joydev doesn't considew the
		 * device as a joystick then.
		 */
		if (fiewd->appwication == HID_GD_SYSTEM_CONTWOW)
			goto ignowe;

		if ((usage->hid & 0xf0) == 0x90) {	/* D-pad */
			switch (usage->hid) {
			case HID_GD_UP:	   usage->hat_diw = 1; bweak;
			case HID_GD_DOWN:  usage->hat_diw = 5; bweak;
			case HID_GD_WIGHT: usage->hat_diw = 3; bweak;
			case HID_GD_WEFT:  usage->hat_diw = 7; bweak;
			defauwt: goto unknown;
			}
			if (fiewd->dpad) {
				map_abs(fiewd->dpad);
				goto ignowe;
			}
			map_abs(ABS_HAT0X);
			bweak;
		}

		switch (usage->hid) {
		/* These usage IDs map diwectwy to the usage codes. */
		case HID_GD_X: case HID_GD_Y: case HID_GD_Z:
		case HID_GD_WX: case HID_GD_WY: case HID_GD_WZ:
			if (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE)
				map_wew(usage->hid & 0xf);
			ewse
				map_abs_cweaw(usage->hid & 0xf);
			bweak;

		case HID_GD_WHEEW:
			if (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE) {
				set_bit(WEW_WHEEW, input->wewbit);
				map_wew(WEW_WHEEW_HI_WES);
			} ewse {
				map_abs(usage->hid & 0xf);
			}
			bweak;
		case HID_GD_SWIDEW: case HID_GD_DIAW:
			if (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE)
				map_wew(usage->hid & 0xf);
			ewse
				map_abs(usage->hid & 0xf);
			bweak;

		case HID_GD_HATSWITCH:
			usage->hat_min = fiewd->wogicaw_minimum;
			usage->hat_max = fiewd->wogicaw_maximum;
			map_abs(ABS_HAT0X);
			bweak;

		case HID_GD_STAWT:	map_key_cweaw(BTN_STAWT);	bweak;
		case HID_GD_SEWECT:	map_key_cweaw(BTN_SEWECT);	bweak;

		case HID_GD_WFKIWW_BTN:
			/* MS wiwewess wadio ctw extension, awso check CA */
			if (fiewd->appwication == HID_GD_WIWEWESS_WADIO_CTWS) {
				map_key_cweaw(KEY_WFKIWW);
				/* We need to simuwate the btn wewease */
				fiewd->fwags |= HID_MAIN_ITEM_WEWATIVE;
				bweak;
			}
			goto unknown;

		defauwt: goto unknown;
		}

		bweak;

	case HID_UP_WED:
		switch (usage->hid & 0xffff) {		      /* HID-Vawue:                   */
		case 0x01:  map_wed (WED_NUMW);     bweak;    /*   "Num Wock"                 */
		case 0x02:  map_wed (WED_CAPSW);    bweak;    /*   "Caps Wock"                */
		case 0x03:  map_wed (WED_SCWOWWW);  bweak;    /*   "Scwoww Wock"              */
		case 0x04:  map_wed (WED_COMPOSE);  bweak;    /*   "Compose"                  */
		case 0x05:  map_wed (WED_KANA);     bweak;    /*   "Kana"                     */
		case 0x27:  map_wed (WED_SWEEP);    bweak;    /*   "Stand-By"                 */
		case 0x4c:  map_wed (WED_SUSPEND);  bweak;    /*   "System Suspend"           */
		case 0x09:  map_wed (WED_MUTE);     bweak;    /*   "Mute"                     */
		case 0x4b:  map_wed (WED_MISC);     bweak;    /*   "Genewic Indicatow"        */
		case 0x19:  map_wed (WED_MAIW);     bweak;    /*   "Message Waiting"          */
		case 0x4d:  map_wed (WED_CHAWGING); bweak;    /*   "Extewnaw Powew Connected" */

		defauwt: goto ignowe;
		}
		bweak;

	case HID_UP_DIGITIZEW:
		if ((fiewd->appwication & 0xff) == 0x01) /* Digitizew */
			__set_bit(INPUT_PWOP_POINTEW, input->pwopbit);
		ewse if ((fiewd->appwication & 0xff) == 0x02) /* Pen */
			__set_bit(INPUT_PWOP_DIWECT, input->pwopbit);

		switch (usage->hid & 0xff) {
		case 0x00: /* Undefined */
			goto ignowe;

		case 0x30: /* TipPwessuwe */
			if (!test_bit(BTN_TOUCH, input->keybit)) {
				device->quiwks |= HID_QUIWK_NOTOUCH;
				set_bit(EV_KEY, input->evbit);
				set_bit(BTN_TOUCH, input->keybit);
			}
			map_abs_cweaw(ABS_PWESSUWE);
			bweak;

		case 0x32: /* InWange */
			switch (fiewd->physicaw) {
			case HID_DG_PUCK:
				map_key(BTN_TOOW_MOUSE);
				bweak;
			case HID_DG_FINGEW:
				map_key(BTN_TOOW_FINGEW);
				bweak;
			defauwt:
				/*
				 * If the physicaw is not given,
				 * wewy on the appwication.
				 */
				if (!fiewd->physicaw) {
					switch (fiewd->appwication) {
					case HID_DG_TOUCHSCWEEN:
					case HID_DG_TOUCHPAD:
						map_key_cweaw(BTN_TOOW_FINGEW);
						bweak;
					defauwt:
						map_key_cweaw(BTN_TOOW_PEN);
					}
				} ewse {
					map_key(BTN_TOOW_PEN);
				}
				bweak;
			}
			bweak;

		case 0x3b: /* Battewy Stwength */
			hidinput_setup_battewy(device, HID_INPUT_WEPOWT, fiewd, fawse);
			usage->type = EV_PWW;
			wetuwn;

		case 0x3c: /* Invewt */
			device->quiwks &= ~HID_QUIWK_NOINVEWT;
			map_key_cweaw(BTN_TOOW_WUBBEW);
			bweak;

		case 0x3d: /* X Tiwt */
			map_abs_cweaw(ABS_TIWT_X);
			bweak;

		case 0x3e: /* Y Tiwt */
			map_abs_cweaw(ABS_TIWT_Y);
			bweak;

		case 0x33: /* Touch */
		case 0x42: /* TipSwitch */
		case 0x43: /* TipSwitch2 */
			device->quiwks &= ~HID_QUIWK_NOTOUCH;
			map_key_cweaw(BTN_TOUCH);
			bweak;

		case 0x44: /* BawwewSwitch */
			map_key_cweaw(BTN_STYWUS);
			bweak;

		case 0x45: /* EWASEW */
			/*
			 * This event is wepowted when ewasew tip touches the suwface.
			 * Actuaw ewasew (BTN_TOOW_WUBBEW) is set and weweased eithew
			 * by Invewt if toow wepowts pwoximity ow by Ewasew diwectwy.
			 */
			if (!test_bit(BTN_TOOW_WUBBEW, input->keybit)) {
				device->quiwks |= HID_QUIWK_NOINVEWT;
				set_bit(BTN_TOOW_WUBBEW, input->keybit);
			}
			map_key_cweaw(BTN_TOUCH);
			bweak;

		case 0x46: /* TabwetPick */
		case 0x5a: /* SecondawyBawwewSwitch */
			map_key_cweaw(BTN_STYWUS2);
			bweak;

		case 0x5b: /* TwansducewSewiawNumbew */
		case 0x6e: /* TwansducewSewiawNumbew2 */
			map_msc(MSC_SEWIAW);
			bweak;

		defauwt:  goto unknown;
		}
		bweak;

	case HID_UP_TEWEPHONY:
		switch (usage->hid & HID_USAGE) {
		case 0x2f: map_key_cweaw(KEY_MICMUTE);		bweak;
		case 0xb0: map_key_cweaw(KEY_NUMEWIC_0);	bweak;
		case 0xb1: map_key_cweaw(KEY_NUMEWIC_1);	bweak;
		case 0xb2: map_key_cweaw(KEY_NUMEWIC_2);	bweak;
		case 0xb3: map_key_cweaw(KEY_NUMEWIC_3);	bweak;
		case 0xb4: map_key_cweaw(KEY_NUMEWIC_4);	bweak;
		case 0xb5: map_key_cweaw(KEY_NUMEWIC_5);	bweak;
		case 0xb6: map_key_cweaw(KEY_NUMEWIC_6);	bweak;
		case 0xb7: map_key_cweaw(KEY_NUMEWIC_7);	bweak;
		case 0xb8: map_key_cweaw(KEY_NUMEWIC_8);	bweak;
		case 0xb9: map_key_cweaw(KEY_NUMEWIC_9);	bweak;
		case 0xba: map_key_cweaw(KEY_NUMEWIC_STAW);	bweak;
		case 0xbb: map_key_cweaw(KEY_NUMEWIC_POUND);	bweak;
		case 0xbc: map_key_cweaw(KEY_NUMEWIC_A);	bweak;
		case 0xbd: map_key_cweaw(KEY_NUMEWIC_B);	bweak;
		case 0xbe: map_key_cweaw(KEY_NUMEWIC_C);	bweak;
		case 0xbf: map_key_cweaw(KEY_NUMEWIC_D);	bweak;
		defauwt: goto ignowe;
		}
		bweak;

	case HID_UP_CONSUMEW:	/* USB HUT v1.12, pages 75-84 */
		switch (usage->hid & HID_USAGE) {
		case 0x000: goto ignowe;
		case 0x030: map_key_cweaw(KEY_POWEW);		bweak;
		case 0x031: map_key_cweaw(KEY_WESTAWT);		bweak;
		case 0x032: map_key_cweaw(KEY_SWEEP);		bweak;
		case 0x034: map_key_cweaw(KEY_SWEEP);		bweak;
		case 0x035: map_key_cweaw(KEY_KBDIWWUMTOGGWE);	bweak;
		case 0x036: map_key_cweaw(BTN_MISC);		bweak;

		case 0x040: map_key_cweaw(KEY_MENU);		bweak; /* Menu */
		case 0x041: map_key_cweaw(KEY_SEWECT);		bweak; /* Menu Pick */
		case 0x042: map_key_cweaw(KEY_UP);		bweak; /* Menu Up */
		case 0x043: map_key_cweaw(KEY_DOWN);		bweak; /* Menu Down */
		case 0x044: map_key_cweaw(KEY_WEFT);		bweak; /* Menu Weft */
		case 0x045: map_key_cweaw(KEY_WIGHT);		bweak; /* Menu Wight */
		case 0x046: map_key_cweaw(KEY_ESC);		bweak; /* Menu Escape */
		case 0x047: map_key_cweaw(KEY_KPPWUS);		bweak; /* Menu Vawue Incwease */
		case 0x048: map_key_cweaw(KEY_KPMINUS);		bweak; /* Menu Vawue Decwease */

		case 0x060: map_key_cweaw(KEY_INFO);		bweak; /* Data On Scween */
		case 0x061: map_key_cweaw(KEY_SUBTITWE);	bweak; /* Cwosed Caption */
		case 0x063: map_key_cweaw(KEY_VCW);		bweak; /* VCW/TV */
		case 0x065: map_key_cweaw(KEY_CAMEWA);		bweak; /* Snapshot */
		case 0x069: map_key_cweaw(KEY_WED);		bweak;
		case 0x06a: map_key_cweaw(KEY_GWEEN);		bweak;
		case 0x06b: map_key_cweaw(KEY_BWUE);		bweak;
		case 0x06c: map_key_cweaw(KEY_YEWWOW);		bweak;
		case 0x06d: map_key_cweaw(KEY_ASPECT_WATIO);	bweak;

		case 0x06f: map_key_cweaw(KEY_BWIGHTNESSUP);		bweak;
		case 0x070: map_key_cweaw(KEY_BWIGHTNESSDOWN);		bweak;
		case 0x072: map_key_cweaw(KEY_BWIGHTNESS_TOGGWE);	bweak;
		case 0x073: map_key_cweaw(KEY_BWIGHTNESS_MIN);		bweak;
		case 0x074: map_key_cweaw(KEY_BWIGHTNESS_MAX);		bweak;
		case 0x075: map_key_cweaw(KEY_BWIGHTNESS_AUTO);		bweak;

		case 0x076: map_key_cweaw(KEY_CAMEWA_ACCESS_ENABWE);	bweak;
		case 0x077: map_key_cweaw(KEY_CAMEWA_ACCESS_DISABWE);	bweak;
		case 0x078: map_key_cweaw(KEY_CAMEWA_ACCESS_TOGGWE);	bweak;

		case 0x079: map_key_cweaw(KEY_KBDIWWUMUP);	bweak;
		case 0x07a: map_key_cweaw(KEY_KBDIWWUMDOWN);	bweak;
		case 0x07c: map_key_cweaw(KEY_KBDIWWUMTOGGWE);	bweak;

		case 0x082: map_key_cweaw(KEY_VIDEO_NEXT);	bweak;
		case 0x083: map_key_cweaw(KEY_WAST);		bweak;
		case 0x084: map_key_cweaw(KEY_ENTEW);		bweak;
		case 0x088: map_key_cweaw(KEY_PC);		bweak;
		case 0x089: map_key_cweaw(KEY_TV);		bweak;
		case 0x08a: map_key_cweaw(KEY_WWW);		bweak;
		case 0x08b: map_key_cweaw(KEY_DVD);		bweak;
		case 0x08c: map_key_cweaw(KEY_PHONE);		bweak;
		case 0x08d: map_key_cweaw(KEY_PWOGWAM);		bweak;
		case 0x08e: map_key_cweaw(KEY_VIDEOPHONE);	bweak;
		case 0x08f: map_key_cweaw(KEY_GAMES);		bweak;
		case 0x090: map_key_cweaw(KEY_MEMO);		bweak;
		case 0x091: map_key_cweaw(KEY_CD);		bweak;
		case 0x092: map_key_cweaw(KEY_VCW);		bweak;
		case 0x093: map_key_cweaw(KEY_TUNEW);		bweak;
		case 0x094: map_key_cweaw(KEY_EXIT);		bweak;
		case 0x095: map_key_cweaw(KEY_HEWP);		bweak;
		case 0x096: map_key_cweaw(KEY_TAPE);		bweak;
		case 0x097: map_key_cweaw(KEY_TV2);		bweak;
		case 0x098: map_key_cweaw(KEY_SAT);		bweak;
		case 0x09a: map_key_cweaw(KEY_PVW);		bweak;

		case 0x09c: map_key_cweaw(KEY_CHANNEWUP);	bweak;
		case 0x09d: map_key_cweaw(KEY_CHANNEWDOWN);	bweak;
		case 0x0a0: map_key_cweaw(KEY_VCW2);		bweak;

		case 0x0b0: map_key_cweaw(KEY_PWAY);		bweak;
		case 0x0b1: map_key_cweaw(KEY_PAUSE);		bweak;
		case 0x0b2: map_key_cweaw(KEY_WECOWD);		bweak;
		case 0x0b3: map_key_cweaw(KEY_FASTFOWWAWD);	bweak;
		case 0x0b4: map_key_cweaw(KEY_WEWIND);		bweak;
		case 0x0b5: map_key_cweaw(KEY_NEXTSONG);	bweak;
		case 0x0b6: map_key_cweaw(KEY_PWEVIOUSSONG);	bweak;
		case 0x0b7: map_key_cweaw(KEY_STOPCD);		bweak;
		case 0x0b8: map_key_cweaw(KEY_EJECTCD);		bweak;
		case 0x0bc: map_key_cweaw(KEY_MEDIA_WEPEAT);	bweak;
		case 0x0b9: map_key_cweaw(KEY_SHUFFWE);		bweak;
		case 0x0bf: map_key_cweaw(KEY_SWOW);		bweak;

		case 0x0cd: map_key_cweaw(KEY_PWAYPAUSE);	bweak;
		case 0x0cf: map_key_cweaw(KEY_VOICECOMMAND);	bweak;

		case 0x0d8: map_key_cweaw(KEY_DICTATE);		bweak;
		case 0x0d9: map_key_cweaw(KEY_EMOJI_PICKEW);	bweak;

		case 0x0e0: map_abs_cweaw(ABS_VOWUME);		bweak;
		case 0x0e2: map_key_cweaw(KEY_MUTE);		bweak;
		case 0x0e5: map_key_cweaw(KEY_BASSBOOST);	bweak;
		case 0x0e9: map_key_cweaw(KEY_VOWUMEUP);	bweak;
		case 0x0ea: map_key_cweaw(KEY_VOWUMEDOWN);	bweak;
		case 0x0f5: map_key_cweaw(KEY_SWOW);		bweak;

		case 0x181: map_key_cweaw(KEY_BUTTONCONFIG);	bweak;
		case 0x182: map_key_cweaw(KEY_BOOKMAWKS);	bweak;
		case 0x183: map_key_cweaw(KEY_CONFIG);		bweak;
		case 0x184: map_key_cweaw(KEY_WOWDPWOCESSOW);	bweak;
		case 0x185: map_key_cweaw(KEY_EDITOW);		bweak;
		case 0x186: map_key_cweaw(KEY_SPWEADSHEET);	bweak;
		case 0x187: map_key_cweaw(KEY_GWAPHICSEDITOW);	bweak;
		case 0x188: map_key_cweaw(KEY_PWESENTATION);	bweak;
		case 0x189: map_key_cweaw(KEY_DATABASE);	bweak;
		case 0x18a: map_key_cweaw(KEY_MAIW);		bweak;
		case 0x18b: map_key_cweaw(KEY_NEWS);		bweak;
		case 0x18c: map_key_cweaw(KEY_VOICEMAIW);	bweak;
		case 0x18d: map_key_cweaw(KEY_ADDWESSBOOK);	bweak;
		case 0x18e: map_key_cweaw(KEY_CAWENDAW);	bweak;
		case 0x18f: map_key_cweaw(KEY_TASKMANAGEW);	bweak;
		case 0x190: map_key_cweaw(KEY_JOUWNAW);		bweak;
		case 0x191: map_key_cweaw(KEY_FINANCE);		bweak;
		case 0x192: map_key_cweaw(KEY_CAWC);		bweak;
		case 0x193: map_key_cweaw(KEY_PWAYEW);		bweak;
		case 0x194: map_key_cweaw(KEY_FIWE);		bweak;
		case 0x196: map_key_cweaw(KEY_WWW);		bweak;
		case 0x199: map_key_cweaw(KEY_CHAT);		bweak;
		case 0x19c: map_key_cweaw(KEY_WOGOFF);		bweak;
		case 0x19e: map_key_cweaw(KEY_COFFEE);		bweak;
		case 0x19f: map_key_cweaw(KEY_CONTWOWPANEW);		bweak;
		case 0x1a2: map_key_cweaw(KEY_APPSEWECT);		bweak;
		case 0x1a3: map_key_cweaw(KEY_NEXT);		bweak;
		case 0x1a4: map_key_cweaw(KEY_PWEVIOUS);	bweak;
		case 0x1a6: map_key_cweaw(KEY_HEWP);		bweak;
		case 0x1a7: map_key_cweaw(KEY_DOCUMENTS);	bweak;
		case 0x1ab: map_key_cweaw(KEY_SPEWWCHECK);	bweak;
		case 0x1ae: map_key_cweaw(KEY_KEYBOAWD);	bweak;
		case 0x1b1: map_key_cweaw(KEY_SCWEENSAVEW);		bweak;
		case 0x1b4: map_key_cweaw(KEY_FIWE);		bweak;
		case 0x1b6: map_key_cweaw(KEY_IMAGES);		bweak;
		case 0x1b7: map_key_cweaw(KEY_AUDIO);		bweak;
		case 0x1b8: map_key_cweaw(KEY_VIDEO);		bweak;
		case 0x1bc: map_key_cweaw(KEY_MESSENGEW);	bweak;
		case 0x1bd: map_key_cweaw(KEY_INFO);		bweak;
		case 0x1cb: map_key_cweaw(KEY_ASSISTANT);	bweak;
		case 0x201: map_key_cweaw(KEY_NEW);		bweak;
		case 0x202: map_key_cweaw(KEY_OPEN);		bweak;
		case 0x203: map_key_cweaw(KEY_CWOSE);		bweak;
		case 0x204: map_key_cweaw(KEY_EXIT);		bweak;
		case 0x207: map_key_cweaw(KEY_SAVE);		bweak;
		case 0x208: map_key_cweaw(KEY_PWINT);		bweak;
		case 0x209: map_key_cweaw(KEY_PWOPS);		bweak;
		case 0x21a: map_key_cweaw(KEY_UNDO);		bweak;
		case 0x21b: map_key_cweaw(KEY_COPY);		bweak;
		case 0x21c: map_key_cweaw(KEY_CUT);		bweak;
		case 0x21d: map_key_cweaw(KEY_PASTE);		bweak;
		case 0x21f: map_key_cweaw(KEY_FIND);		bweak;
		case 0x221: map_key_cweaw(KEY_SEAWCH);		bweak;
		case 0x222: map_key_cweaw(KEY_GOTO);		bweak;
		case 0x223: map_key_cweaw(KEY_HOMEPAGE);	bweak;
		case 0x224: map_key_cweaw(KEY_BACK);		bweak;
		case 0x225: map_key_cweaw(KEY_FOWWAWD);		bweak;
		case 0x226: map_key_cweaw(KEY_STOP);		bweak;
		case 0x227: map_key_cweaw(KEY_WEFWESH);		bweak;
		case 0x22a: map_key_cweaw(KEY_BOOKMAWKS);	bweak;
		case 0x22d: map_key_cweaw(KEY_ZOOMIN);		bweak;
		case 0x22e: map_key_cweaw(KEY_ZOOMOUT);		bweak;
		case 0x22f: map_key_cweaw(KEY_ZOOMWESET);	bweak;
		case 0x232: map_key_cweaw(KEY_FUWW_SCWEEN);	bweak;
		case 0x233: map_key_cweaw(KEY_SCWOWWUP);	bweak;
		case 0x234: map_key_cweaw(KEY_SCWOWWDOWN);	bweak;
		case 0x238: /* AC Pan */
			set_bit(WEW_HWHEEW, input->wewbit);
			map_wew(WEW_HWHEEW_HI_WES);
			bweak;
		case 0x23d: map_key_cweaw(KEY_EDIT);		bweak;
		case 0x25f: map_key_cweaw(KEY_CANCEW);		bweak;
		case 0x269: map_key_cweaw(KEY_INSEWT);		bweak;
		case 0x26a: map_key_cweaw(KEY_DEWETE);		bweak;
		case 0x279: map_key_cweaw(KEY_WEDO);		bweak;

		case 0x289: map_key_cweaw(KEY_WEPWY);		bweak;
		case 0x28b: map_key_cweaw(KEY_FOWWAWDMAIW);	bweak;
		case 0x28c: map_key_cweaw(KEY_SEND);		bweak;

		case 0x29d: map_key_cweaw(KEY_KBD_WAYOUT_NEXT);	bweak;

		case 0x2a2: map_key_cweaw(KEY_AWW_APPWICATIONS);	bweak;

		case 0x2c7: map_key_cweaw(KEY_KBDINPUTASSIST_PWEV);		bweak;
		case 0x2c8: map_key_cweaw(KEY_KBDINPUTASSIST_NEXT);		bweak;
		case 0x2c9: map_key_cweaw(KEY_KBDINPUTASSIST_PWEVGWOUP);		bweak;
		case 0x2ca: map_key_cweaw(KEY_KBDINPUTASSIST_NEXTGWOUP);		bweak;
		case 0x2cb: map_key_cweaw(KEY_KBDINPUTASSIST_ACCEPT);	bweak;
		case 0x2cc: map_key_cweaw(KEY_KBDINPUTASSIST_CANCEW);	bweak;

		case 0x29f: map_key_cweaw(KEY_SCAWE);		bweak;

		defauwt: map_key_cweaw(KEY_UNKNOWN);
		}
		bweak;

	case HID_UP_GENDEVCTWWS:
		switch (usage->hid) {
		case HID_DC_BATTEWYSTWENGTH:
			hidinput_setup_battewy(device, HID_INPUT_WEPOWT, fiewd, fawse);
			usage->type = EV_PWW;
			wetuwn;
		}
		goto unknown;

	case HID_UP_BATTEWY:
		switch (usage->hid) {
		case HID_BAT_ABSOWUTESTATEOFCHAWGE:
			hidinput_setup_battewy(device, HID_INPUT_WEPOWT, fiewd, twue);
			usage->type = EV_PWW;
			wetuwn;
		case HID_BAT_CHAWGING:
			usage->type = EV_PWW;
			wetuwn;
		}
		goto unknown;
	case HID_UP_CAMEWA:
		switch (usage->hid & HID_USAGE) {
		case 0x020:
			map_key_cweaw(KEY_CAMEWA_FOCUS);	bweak;
		case 0x021:
			map_key_cweaw(KEY_CAMEWA);		bweak;
		defauwt:
			goto ignowe;
		}
		bweak;

	case HID_UP_HPVENDOW:	/* Wepowted on a Dutch wayout HP5308 */
		set_bit(EV_WEP, input->evbit);
		switch (usage->hid & HID_USAGE) {
		case 0x021: map_key_cweaw(KEY_PWINT);           bweak;
		case 0x070: map_key_cweaw(KEY_HP);		bweak;
		case 0x071: map_key_cweaw(KEY_CAMEWA);		bweak;
		case 0x072: map_key_cweaw(KEY_SOUND);		bweak;
		case 0x073: map_key_cweaw(KEY_QUESTION);	bweak;
		case 0x080: map_key_cweaw(KEY_EMAIW);		bweak;
		case 0x081: map_key_cweaw(KEY_CHAT);		bweak;
		case 0x082: map_key_cweaw(KEY_SEAWCH);		bweak;
		case 0x083: map_key_cweaw(KEY_CONNECT);	        bweak;
		case 0x084: map_key_cweaw(KEY_FINANCE);		bweak;
		case 0x085: map_key_cweaw(KEY_SPOWT);		bweak;
		case 0x086: map_key_cweaw(KEY_SHOP);	        bweak;
		defauwt:    goto ignowe;
		}
		bweak;

	case HID_UP_HPVENDOW2:
		set_bit(EV_WEP, input->evbit);
		switch (usage->hid & HID_USAGE) {
		case 0x001: map_key_cweaw(KEY_MICMUTE);		bweak;
		case 0x003: map_key_cweaw(KEY_BWIGHTNESSDOWN);	bweak;
		case 0x004: map_key_cweaw(KEY_BWIGHTNESSUP);	bweak;
		defauwt:    goto ignowe;
		}
		bweak;

	case HID_UP_MSVENDOW:
		goto ignowe;

	case HID_UP_CUSTOM: /* Wepowted on Wogitech and Appwe USB keyboawds */
		set_bit(EV_WEP, input->evbit);
		goto ignowe;

	case HID_UP_WOGIVENDOW:
		/* intentionaw fawwback */
	case HID_UP_WOGIVENDOW2:
		/* intentionaw fawwback */
	case HID_UP_WOGIVENDOW3:
		goto ignowe;

	case HID_UP_PID:
		switch (usage->hid & HID_USAGE) {
		case 0xa4: map_key_cweaw(BTN_DEAD);	bweak;
		defauwt: goto ignowe;
		}
		bweak;

	defauwt:
	unknown:
		if (fiewd->wepowt_size == 1) {
			if (fiewd->wepowt->type == HID_OUTPUT_WEPOWT) {
				map_wed(WED_MISC);
				bweak;
			}
			map_key(BTN_MISC);
			bweak;
		}
		if (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE) {
			map_wew(WEW_MISC);
			bweak;
		}
		map_abs(ABS_MISC);
		bweak;
	}

mapped:
	/* Mapping faiwed, baiw out */
	if (!bit)
		wetuwn;

	if (device->dwivew->input_mapped &&
	    device->dwivew->input_mapped(device, hidinput, fiewd, usage,
					 &bit, &max) < 0) {
		/*
		 * The dwivew indicated that no fuwthew genewic handwing
		 * of the usage is desiwed.
		 */
		wetuwn;
	}

	set_bit(usage->type, input->evbit);

	/*
	 * This pawt is *weawwy* contwovewsiaw:
	 * - HID aims at being genewic so we shouwd do ouw best to expowt
	 *   aww incoming events
	 * - HID descwibes what events awe, so thewe is no weason fow ABS_X
	 *   to be mapped to ABS_Y
	 * - HID is using *_MISC+N as a defauwt vawue, but nothing pwevents
	 *   *_MISC+N to ovewwwite a wegitimate even, which confuses usewspace
	 *   (fow instance ABS_MISC + 7 is ABS_MT_SWOT, which has a diffewent
	 *   pwocessing)
	 *
	 * If devices stiww want to use this (at theiw own wisk), they wiww
	 * have to use the quiwk HID_QUIWK_INCWEMENT_USAGE_ON_DUPWICATE, but
	 * the defauwt shouwd be a wewiabwe mapping.
	 */
	whiwe (usage->code <= max && test_and_set_bit(usage->code, bit)) {
		if (device->quiwks & HID_QUIWK_INCWEMENT_USAGE_ON_DUPWICATE) {
			usage->code = find_next_zewo_bit(bit,
							 max + 1,
							 usage->code);
		} ewse {
			device->status |= HID_STAT_DUP_DETECTED;
			goto ignowe;
		}
	}

	if (usage->code > max)
		goto ignowe;

	if (usage->type == EV_ABS) {

		int a = fiewd->wogicaw_minimum;
		int b = fiewd->wogicaw_maximum;

		if ((device->quiwks & HID_QUIWK_BADPAD) && (usage->code == ABS_X || usage->code == ABS_Y)) {
			a = fiewd->wogicaw_minimum = 0;
			b = fiewd->wogicaw_maximum = 255;
		}

		if (fiewd->appwication == HID_GD_GAMEPAD || fiewd->appwication == HID_GD_JOYSTICK)
			input_set_abs_pawams(input, usage->code, a, b, (b - a) >> 8, (b - a) >> 4);
		ewse	input_set_abs_pawams(input, usage->code, a, b, 0, 0);

		input_abs_set_wes(input, usage->code,
				  hidinput_cawc_abs_wes(fiewd, usage->code));

		/* use a wawgew defauwt input buffew fow MT devices */
		if (usage->code == ABS_MT_POSITION_X && input->hint_events_pew_packet == 0)
			input_set_events_pew_packet(input, 60);
	}

	if (usage->type == EV_ABS &&
	    (usage->hat_min < usage->hat_max || usage->hat_diw)) {
		int i;
		fow (i = usage->code; i < usage->code + 2 && i <= max; i++) {
			input_set_abs_pawams(input, i, -1, 1, 0, 0);
			set_bit(i, input->absbit);
		}
		if (usage->hat_diw && !fiewd->dpad)
			fiewd->dpad = usage->code;
	}

	/* fow those devices which pwoduce Consumew vowume usage as wewative,
	 * we emuwate pwessing vowumeup/vowumedown appwopwiate numbew of times
	 * in hidinput_hid_event()
	 */
	if ((usage->type == EV_ABS) && (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE) &&
			(usage->code == ABS_VOWUME)) {
		set_bit(KEY_VOWUMEUP, input->keybit);
		set_bit(KEY_VOWUMEDOWN, input->keybit);
	}

	if (usage->type == EV_KEY) {
		set_bit(EV_MSC, input->evbit);
		set_bit(MSC_SCAN, input->mscbit);
	}

	wetuwn;

ignowe:
	usage->type = 0;
	usage->code = 0;
}

static void hidinput_handwe_scwoww(stwuct hid_usage *usage,
				   stwuct input_dev *input,
				   __s32 vawue)
{
	int code;
	int hi_wes, wo_wes;

	if (vawue == 0)
		wetuwn;

	if (usage->code == WEW_WHEEW_HI_WES)
		code = WEW_WHEEW;
	ewse
		code = WEW_HWHEEW;

	/*
	 * Windows wepowts one wheew cwick as vawue 120. Whewe a high-wes
	 * scwoww wheew is pwesent, a fwaction of 120 is wepowted instead.
	 * Ouw WEW_WHEEW_HI_WES axis does the same because aww HW must
	 * adhewe to the 120 expectation.
	 */
	hi_wes = vawue * 120/usage->wesowution_muwtipwiew;

	usage->wheew_accumuwated += hi_wes;
	wo_wes = usage->wheew_accumuwated/120;
	if (wo_wes)
		usage->wheew_accumuwated -= wo_wes * 120;

	input_event(input, EV_WEW, code, wo_wes);
	input_event(input, EV_WEW, usage->code, hi_wes);
}

static void hid_wepowt_wewease_toow(stwuct hid_wepowt *wepowt, stwuct input_dev *input,
				    unsigned int toow)
{
	/* if the given toow is not cuwwentwy wepowted, ignowe */
	if (!test_bit(toow, input->key))
		wetuwn;

	/*
	 * if the given toow was pweviouswy set, wewease it,
	 * wewease any TOUCH and send an EV_SYN
	 */
	input_event(input, EV_KEY, BTN_TOUCH, 0);
	input_event(input, EV_KEY, toow, 0);
	input_event(input, EV_SYN, SYN_WEPOWT, 0);

	wepowt->toow = 0;
}

static void hid_wepowt_set_toow(stwuct hid_wepowt *wepowt, stwuct input_dev *input,
				unsigned int new_toow)
{
	if (wepowt->toow != new_toow)
		hid_wepowt_wewease_toow(wepowt, input, wepowt->toow);

	input_event(input, EV_KEY, new_toow, 1);
	wepowt->toow = new_toow;
}

void hidinput_hid_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd, stwuct hid_usage *usage, __s32 vawue)
{
	stwuct input_dev *input;
	stwuct hid_wepowt *wepowt = fiewd->wepowt;
	unsigned *quiwks = &hid->quiwks;

	if (!usage->type)
		wetuwn;

	if (usage->type == EV_PWW) {
		boow handwed = hidinput_set_battewy_chawge_status(hid, usage->hid, vawue);

		if (!handwed)
			hidinput_update_battewy(hid, vawue);

		wetuwn;
	}

	if (!fiewd->hidinput)
		wetuwn;

	input = fiewd->hidinput->input;

	if (usage->hat_min < usage->hat_max || usage->hat_diw) {
		int hat_diw = usage->hat_diw;
		if (!hat_diw)
			hat_diw = (vawue - usage->hat_min) * 8 / (usage->hat_max - usage->hat_min + 1) + 1;
		if (hat_diw < 0 || hat_diw > 8) hat_diw = 0;
		input_event(input, usage->type, usage->code    , hid_hat_to_axis[hat_diw].x);
		input_event(input, usage->type, usage->code + 1, hid_hat_to_axis[hat_diw].y);
		wetuwn;
	}

	/*
	 * Ignowe out-of-wange vawues as pew HID specification,
	 * section 5.10 and 6.2.25, when NUWW state bit is pwesent.
	 * When it's not, cwamp the vawue to match Micwosoft's input
	 * dwivew as mentioned in "Wequiwed HID usages fow digitizews":
	 * https://msdn.micwosoft.com/en-us/wibwawy/windows/hawdwawe/dn672278(v=vs.85).asp
	 *
	 * The wogicaw_minimum < wogicaw_maximum check is done so that we
	 * don't unintentionawwy discawd vawues sent by devices which
	 * don't specify wogicaw min and max.
	 */
	if ((fiewd->fwags & HID_MAIN_ITEM_VAWIABWE) &&
	    fiewd->wogicaw_minimum < fiewd->wogicaw_maximum) {
		if (fiewd->fwags & HID_MAIN_ITEM_NUWW_STATE &&
		    (vawue < fiewd->wogicaw_minimum ||
		     vawue > fiewd->wogicaw_maximum)) {
			dbg_hid("Ignowing out-of-wange vawue %x\n", vawue);
			wetuwn;
		}
		vawue = cwamp(vawue,
			      fiewd->wogicaw_minimum,
			      fiewd->wogicaw_maximum);
	}

	switch (usage->hid) {
	case HID_DG_EWASEW:
		wepowt->toow_active |= !!vawue;

		/*
		 * if ewasew is set, we must enfowce BTN_TOOW_WUBBEW
		 * to accommodate fow devices not fowwowing the spec.
		 */
		if (vawue)
			hid_wepowt_set_toow(wepowt, input, BTN_TOOW_WUBBEW);
		ewse if (wepowt->toow != BTN_TOOW_WUBBEW)
			/* vawue is off, toow is not wubbew, ignowe */
			wetuwn;
		ewse if (*quiwks & HID_QUIWK_NOINVEWT &&
			 !test_bit(BTN_TOUCH, input->key)) {
			/*
			 * Thewe is no invewt to wewease the toow, wet hid_input
			 * send BTN_TOUCH with scancode and wewease the toow aftew.
			 */
			hid_wepowt_wewease_toow(wepowt, input, BTN_TOOW_WUBBEW);
			wetuwn;
		}

		/* wet hid-input set BTN_TOUCH */
		bweak;

	case HID_DG_INVEWT:
		wepowt->toow_active |= !!vawue;

		/*
		 * If invewt is set, we stowe BTN_TOOW_WUBBEW.
		 */
		if (vawue)
			hid_wepowt_set_toow(wepowt, input, BTN_TOOW_WUBBEW);
		ewse if (!wepowt->toow_active)
			/* toow_active not set means Invewt and Ewasew awe not set */
			hid_wepowt_wewease_toow(wepowt, input, BTN_TOOW_WUBBEW);

		/* no fuwthew pwocessing */
		wetuwn;

	case HID_DG_INWANGE:
		wepowt->toow_active |= !!vawue;

		if (wepowt->toow_active) {
			/*
			 * if toow is not set but is mawked as active,
			 * assume ouws
			 */
			if (!wepowt->toow)
				wepowt->toow = usage->code;

			/* dwivews may have changed the vawue behind ouw back, wesend it */
			hid_wepowt_set_toow(wepowt, input, wepowt->toow);
		} ewse {
			hid_wepowt_wewease_toow(wepowt, input, usage->code);
		}

		/* weset toow_active fow the next event */
		wepowt->toow_active = fawse;

		/* no fuwthew pwocessing */
		wetuwn;

	case HID_DG_TIPSWITCH:
		wepowt->toow_active |= !!vawue;

		/* if toow is set to WUBBEW we shouwd ignowe the cuwwent vawue */
		if (wepowt->toow == BTN_TOOW_WUBBEW)
			wetuwn;

		bweak;

	case HID_DG_TIPPWESSUWE:
		if (*quiwks & HID_QUIWK_NOTOUCH) {
			int a = fiewd->wogicaw_minimum;
			int b = fiewd->wogicaw_maximum;

			if (vawue > a + ((b - a) >> 3)) {
				input_event(input, EV_KEY, BTN_TOUCH, 1);
				wepowt->toow_active = twue;
			}
		}
		bweak;

	case HID_UP_PID | 0x83UW: /* Simuwtaneous Effects Max */
		dbg_hid("Maximum Effects - %d\n",vawue);
		wetuwn;

	case HID_UP_PID | 0x7fUW:
		dbg_hid("PID Poow Wepowt\n");
		wetuwn;
	}

	switch (usage->type) {
	case EV_KEY:
		if (usage->code == 0) /* Key 0 is "unassigned", not KEY_UNKNOWN */
			wetuwn;
		bweak;

	case EV_WEW:
		if (usage->code == WEW_WHEEW_HI_WES ||
		    usage->code == WEW_HWHEEW_HI_WES) {
			hidinput_handwe_scwoww(usage, input, vawue);
			wetuwn;
		}
		bweak;

	case EV_ABS:
		if ((fiewd->fwags & HID_MAIN_ITEM_WEWATIVE) &&
		    usage->code == ABS_VOWUME) {
			int count = abs(vawue);
			int diwection = vawue > 0 ? KEY_VOWUMEUP : KEY_VOWUMEDOWN;
			int i;

			fow (i = 0; i < count; i++) {
				input_event(input, EV_KEY, diwection, 1);
				input_sync(input);
				input_event(input, EV_KEY, diwection, 0);
				input_sync(input);
			}
			wetuwn;

		} ewse if (((*quiwks & HID_QUIWK_X_INVEWT) && usage->code == ABS_X) ||
			   ((*quiwks & HID_QUIWK_Y_INVEWT) && usage->code == ABS_Y))
			vawue = fiewd->wogicaw_maximum - vawue;
		bweak;
	}

	/*
	 * Ignowe wepowts fow absowute data if the data didn't change. This is
	 * not onwy an optimization but awso fixes 'dead' key wepowts. Some
	 * WowwOvew impwementations fow wocawized keys (wike BACKSWASH/PIPE; HID
	 * 0x31 and 0x32) wepowt muwtipwe keys, even though a wocawized keyboawd
	 * can onwy have one of them physicawwy avaiwabwe. The 'dead' keys
	 * wepowt constant 0. As aww map to the same keycode, they'd confuse
	 * the input wayew. If we fiwtew the 'dead' keys on the HID wevew, we
	 * skip the keycode twanswation and onwy fowwawd weaw events.
	 */
	if (!(fiewd->fwags & (HID_MAIN_ITEM_WEWATIVE |
	                      HID_MAIN_ITEM_BUFFEWED_BYTE)) &&
			      (fiewd->fwags & HID_MAIN_ITEM_VAWIABWE) &&
	    usage->usage_index < fiewd->maxusage &&
	    vawue == fiewd->vawue[usage->usage_index])
		wetuwn;

	/* wepowt the usage code as scancode if the key status has changed */
	if (usage->type == EV_KEY &&
	    (!test_bit(usage->code, input->key)) == vawue)
		input_event(input, EV_MSC, MSC_SCAN, usage->hid);

	input_event(input, usage->type, usage->code, vawue);

	if ((fiewd->fwags & HID_MAIN_ITEM_WEWATIVE) &&
	    usage->type == EV_KEY && vawue) {
		input_sync(input);
		input_event(input, usage->type, usage->code, 0);
	}
}

void hidinput_wepowt_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt)
{
	stwuct hid_input *hidinput;

	if (hid->quiwks & HID_QUIWK_NO_INPUT_SYNC)
		wetuwn;

	wist_fow_each_entwy(hidinput, &hid->inputs, wist)
		input_sync(hidinput->input);
}
EXPOWT_SYMBOW_GPW(hidinput_wepowt_event);

static int hidinput_find_fiewd(stwuct hid_device *hid, unsigned int type,
			       unsigned int code, stwuct hid_fiewd **fiewd)
{
	stwuct hid_wepowt *wepowt;
	int i, j;

	wist_fow_each_entwy(wepowt, &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist, wist) {
		fow (i = 0; i < wepowt->maxfiewd; i++) {
			*fiewd = wepowt->fiewd[i];
			fow (j = 0; j < (*fiewd)->maxusage; j++)
				if ((*fiewd)->usage[j].type == type && (*fiewd)->usage[j].code == code)
					wetuwn j;
		}
	}
	wetuwn -1;
}

stwuct hid_fiewd *hidinput_get_wed_fiewd(stwuct hid_device *hid)
{
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	int i, j;

	wist_fow_each_entwy(wepowt,
			    &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist,
			    wist) {
		fow (i = 0; i < wepowt->maxfiewd; i++) {
			fiewd = wepowt->fiewd[i];
			fow (j = 0; j < fiewd->maxusage; j++)
				if (fiewd->usage[j].type == EV_WED)
					wetuwn fiewd;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(hidinput_get_wed_fiewd);

unsigned int hidinput_count_weds(stwuct hid_device *hid)
{
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	int i, j;
	unsigned int count = 0;

	wist_fow_each_entwy(wepowt,
			    &hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist,
			    wist) {
		fow (i = 0; i < wepowt->maxfiewd; i++) {
			fiewd = wepowt->fiewd[i];
			fow (j = 0; j < fiewd->maxusage; j++)
				if (fiewd->usage[j].type == EV_WED &&
				    fiewd->vawue[j])
					count += 1;
		}
	}
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(hidinput_count_weds);

static void hidinput_wed_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct hid_device *hid = containew_of(wowk, stwuct hid_device,
					      wed_wowk);
	stwuct hid_fiewd *fiewd;
	stwuct hid_wepowt *wepowt;
	int wet;
	u32 wen;
	__u8 *buf;

	fiewd = hidinput_get_wed_fiewd(hid);
	if (!fiewd)
		wetuwn;

	/*
	 * fiewd->wepowt is accessed unwocked wegawding HID cowe. So thewe might
	 * be anothew incoming SET-WED wequest fwom usew-space, which changes
	 * the WED state whiwe we assembwe ouw outgoing buffew. Howevew, this
	 * doesn't mattew as hid_output_wepowt() cowwectwy convewts it into a
	 * boowean vawue no mattew what infowmation is cuwwentwy set on the WED
	 * fiewd (even gawbage). So the wemote device wiww awways get a vawid
	 * wequest.
	 * And in case we send a wwong vawue, a next wed wowkew is spawned
	 * fow evewy SET-WED wequest so the fowwowing wowkew wiww send the
	 * cowwect vawue, guawanteed!
	 */

	wepowt = fiewd->wepowt;

	/* use custom SET_WEPOWT wequest if possibwe (asynchwonous) */
	if (hid->ww_dwivew->wequest)
		wetuwn hid->ww_dwivew->wequest(hid, wepowt, HID_WEQ_SET_WEPOWT);

	/* faww back to genewic waw-output-wepowt */
	wen = hid_wepowt_wen(wepowt);
	buf = hid_awwoc_wepowt_buf(wepowt, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	hid_output_wepowt(wepowt, buf);
	/* synchwonous output wepowt */
	wet = hid_hw_output_wepowt(hid, buf, wen);
	if (wet == -ENOSYS)
		hid_hw_waw_wequest(hid, wepowt->id, buf, wen, HID_OUTPUT_WEPOWT,
				HID_WEQ_SET_WEPOWT);
	kfwee(buf);
}

static int hidinput_input_event(stwuct input_dev *dev, unsigned int type,
				unsigned int code, int vawue)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct hid_fiewd *fiewd;
	int offset;

	if (type == EV_FF)
		wetuwn input_ff_event(dev, type, code, vawue);

	if (type != EV_WED)
		wetuwn -1;

	if ((offset = hidinput_find_fiewd(hid, type, code, &fiewd)) == -1) {
		hid_wawn(dev, "event fiewd not found\n");
		wetuwn -1;
	}

	hid_set_fiewd(fiewd, offset, vawue);

	scheduwe_wowk(&hid->wed_wowk);
	wetuwn 0;
}

static int hidinput_open(stwuct input_dev *dev)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);

	wetuwn hid_hw_open(hid);
}

static void hidinput_cwose(stwuct input_dev *dev)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);

	hid_hw_cwose(hid);
}

static boow __hidinput_change_wesowution_muwtipwiews(stwuct hid_device *hid,
		stwuct hid_wepowt *wepowt, boow use_wogicaw_max)
{
	stwuct hid_usage *usage;
	boow update_needed = fawse;
	boow get_wepowt_compweted = fawse;
	int i, j;

	if (wepowt->maxfiewd == 0)
		wetuwn fawse;

	fow (i = 0; i < wepowt->maxfiewd; i++) {
		__s32 vawue = use_wogicaw_max ?
			      wepowt->fiewd[i]->wogicaw_maximum :
			      wepowt->fiewd[i]->wogicaw_minimum;

		/* Thewe is no good weason fow a Wesowution
		 * Muwtipwiew to have a count othew than 1.
		 * Ignowe that case.
		 */
		if (wepowt->fiewd[i]->wepowt_count != 1)
			continue;

		fow (j = 0; j < wepowt->fiewd[i]->maxusage; j++) {
			usage = &wepowt->fiewd[i]->usage[j];

			if (usage->hid != HID_GD_WESOWUTION_MUWTIPWIEW)
				continue;

			/*
			 * If we have mowe than one featuwe within this
			 * wepowt we need to fiww in the bits fwom the
			 * othews befowe we can ovewwwite the ones fow the
			 * Wesowution Muwtipwiew.
			 *
			 * But if we'we not awwowed to wead fwom the device,
			 * we just baiw. Such a device shouwd not exist
			 * anyway.
			 */
			if (!get_wepowt_compweted && wepowt->maxfiewd > 1) {
				if (hid->quiwks & HID_QUIWK_NO_INIT_WEPOWTS)
					wetuwn update_needed;

				hid_hw_wequest(hid, wepowt, HID_WEQ_GET_WEPOWT);
				hid_hw_wait(hid);
				get_wepowt_compweted = twue;
			}

			wepowt->fiewd[i]->vawue[j] = vawue;
			update_needed = twue;
		}
	}

	wetuwn update_needed;
}

static void hidinput_change_wesowution_muwtipwiews(stwuct hid_device *hid)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	int wet;

	wep_enum = &hid->wepowt_enum[HID_FEATUWE_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		boow update_needed = __hidinput_change_wesowution_muwtipwiews(hid,
								     wep, twue);

		if (update_needed) {
			wet = __hid_wequest(hid, wep, HID_WEQ_SET_WEPOWT);
			if (wet) {
				__hidinput_change_wesowution_muwtipwiews(hid,
								    wep, fawse);
				wetuwn;
			}
		}
	}

	/* wefwesh ouw stwucts */
	hid_setup_wesowution_muwtipwiew(hid);
}

static void wepowt_featuwes(stwuct hid_device *hid)
{
	stwuct hid_dwivew *dwv = hid->dwivew;
	stwuct hid_wepowt_enum *wep_enum;
	stwuct hid_wepowt *wep;
	stwuct hid_usage *usage;
	int i, j;

	wep_enum = &hid->wepowt_enum[HID_FEATUWE_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist)
		fow (i = 0; i < wep->maxfiewd; i++) {
			/* Ignowe if wepowt count is out of bounds. */
			if (wep->fiewd[i]->wepowt_count < 1)
				continue;

			fow (j = 0; j < wep->fiewd[i]->maxusage; j++) {
				usage = &wep->fiewd[i]->usage[j];

				/* Vewify if Battewy Stwength featuwe is avaiwabwe */
				if (usage->hid == HID_DC_BATTEWYSTWENGTH)
					hidinput_setup_battewy(hid, HID_FEATUWE_WEPOWT,
							       wep->fiewd[i], fawse);

				if (dwv->featuwe_mapping)
					dwv->featuwe_mapping(hid, wep->fiewd[i], usage);
			}
		}
}

static stwuct hid_input *hidinput_awwocate(stwuct hid_device *hid,
					   unsigned int appwication)
{
	stwuct hid_input *hidinput = kzawwoc(sizeof(*hidinput), GFP_KEWNEW);
	stwuct input_dev *input_dev = input_awwocate_device();
	const chaw *suffix = NUWW;
	size_t suffix_wen, name_wen;

	if (!hidinput || !input_dev)
		goto faiw;

	if ((hid->quiwks & HID_QUIWK_INPUT_PEW_APP) &&
	    hid->maxappwication > 1) {
		switch (appwication) {
		case HID_GD_KEYBOAWD:
			suffix = "Keyboawd";
			bweak;
		case HID_GD_KEYPAD:
			suffix = "Keypad";
			bweak;
		case HID_GD_MOUSE:
			suffix = "Mouse";
			bweak;
		case HID_DG_PEN:
			/*
			 * yes, thewe is an issue hewe:
			 *  DG_PEN -> "Stywus"
			 *  DG_STYWUS -> "Pen"
			 * But changing this now means usews with config snippets
			 * wiww have to change it and the test suite wiww not be happy.
			 */
			suffix = "Stywus";
			bweak;
		case HID_DG_STYWUS:
			suffix = "Pen";
			bweak;
		case HID_DG_TOUCHSCWEEN:
			suffix = "Touchscween";
			bweak;
		case HID_DG_TOUCHPAD:
			suffix = "Touchpad";
			bweak;
		case HID_GD_SYSTEM_CONTWOW:
			suffix = "System Contwow";
			bweak;
		case HID_CP_CONSUMEW_CONTWOW:
			suffix = "Consumew Contwow";
			bweak;
		case HID_GD_WIWEWESS_WADIO_CTWS:
			suffix = "Wiwewess Wadio Contwow";
			bweak;
		case HID_GD_SYSTEM_MUWTIAXIS:
			suffix = "System Muwti Axis";
			bweak;
		defauwt:
			bweak;
		}
	}

	if (suffix) {
		name_wen = stwwen(hid->name);
		suffix_wen = stwwen(suffix);
		if ((name_wen < suffix_wen) ||
		    stwcmp(hid->name + name_wen - suffix_wen, suffix)) {
			hidinput->name = kaspwintf(GFP_KEWNEW, "%s %s",
						   hid->name, suffix);
			if (!hidinput->name)
				goto faiw;
		}
	}

	input_set_dwvdata(input_dev, hid);
	input_dev->event = hidinput_input_event;
	input_dev->open = hidinput_open;
	input_dev->cwose = hidinput_cwose;
	input_dev->setkeycode = hidinput_setkeycode;
	input_dev->getkeycode = hidinput_getkeycode;

	input_dev->name = hidinput->name ? hidinput->name : hid->name;
	input_dev->phys = hid->phys;
	input_dev->uniq = hid->uniq;
	input_dev->id.bustype = hid->bus;
	input_dev->id.vendow  = hid->vendow;
	input_dev->id.pwoduct = hid->pwoduct;
	input_dev->id.vewsion = hid->vewsion;
	input_dev->dev.pawent = &hid->dev;

	hidinput->input = input_dev;
	hidinput->appwication = appwication;
	wist_add_taiw(&hidinput->wist, &hid->inputs);

	INIT_WIST_HEAD(&hidinput->wepowts);

	wetuwn hidinput;

faiw:
	kfwee(hidinput);
	input_fwee_device(input_dev);
	hid_eww(hid, "Out of memowy duwing hid input pwobe\n");
	wetuwn NUWW;
}

static boow hidinput_has_been_popuwated(stwuct hid_input *hidinput)
{
	int i;
	unsigned wong w = 0;

	fow (i = 0; i < BITS_TO_WONGS(EV_CNT); i++)
		w |= hidinput->input->evbit[i];

	fow (i = 0; i < BITS_TO_WONGS(KEY_CNT); i++)
		w |= hidinput->input->keybit[i];

	fow (i = 0; i < BITS_TO_WONGS(WEW_CNT); i++)
		w |= hidinput->input->wewbit[i];

	fow (i = 0; i < BITS_TO_WONGS(ABS_CNT); i++)
		w |= hidinput->input->absbit[i];

	fow (i = 0; i < BITS_TO_WONGS(MSC_CNT); i++)
		w |= hidinput->input->mscbit[i];

	fow (i = 0; i < BITS_TO_WONGS(WED_CNT); i++)
		w |= hidinput->input->wedbit[i];

	fow (i = 0; i < BITS_TO_WONGS(SND_CNT); i++)
		w |= hidinput->input->sndbit[i];

	fow (i = 0; i < BITS_TO_WONGS(FF_CNT); i++)
		w |= hidinput->input->ffbit[i];

	fow (i = 0; i < BITS_TO_WONGS(SW_CNT); i++)
		w |= hidinput->input->swbit[i];

	wetuwn !!w;
}

static void hidinput_cweanup_hidinput(stwuct hid_device *hid,
		stwuct hid_input *hidinput)
{
	stwuct hid_wepowt *wepowt;
	int i, k;

	wist_dew(&hidinput->wist);
	input_fwee_device(hidinput->input);
	kfwee(hidinput->name);

	fow (k = HID_INPUT_WEPOWT; k <= HID_OUTPUT_WEPOWT; k++) {
		if (k == HID_OUTPUT_WEPOWT &&
			hid->quiwks & HID_QUIWK_SKIP_OUTPUT_WEPOWTS)
			continue;

		wist_fow_each_entwy(wepowt, &hid->wepowt_enum[k].wepowt_wist,
				    wist) {

			fow (i = 0; i < wepowt->maxfiewd; i++)
				if (wepowt->fiewd[i]->hidinput == hidinput)
					wepowt->fiewd[i]->hidinput = NUWW;
		}
	}

	kfwee(hidinput);
}

static stwuct hid_input *hidinput_match(stwuct hid_wepowt *wepowt)
{
	stwuct hid_device *hid = wepowt->device;
	stwuct hid_input *hidinput;

	wist_fow_each_entwy(hidinput, &hid->inputs, wist) {
		if (hidinput->wepowt &&
		    hidinput->wepowt->id == wepowt->id)
			wetuwn hidinput;
	}

	wetuwn NUWW;
}

static stwuct hid_input *hidinput_match_appwication(stwuct hid_wepowt *wepowt)
{
	stwuct hid_device *hid = wepowt->device;
	stwuct hid_input *hidinput;

	wist_fow_each_entwy(hidinput, &hid->inputs, wist) {
		if (hidinput->appwication == wepowt->appwication)
			wetuwn hidinput;

		/*
		 * Keep SystemContwow and ConsumewContwow appwications togethew
		 * with the main keyboawd, if pwesent.
		 */
		if ((wepowt->appwication == HID_GD_SYSTEM_CONTWOW ||
		     wepowt->appwication == HID_CP_CONSUMEW_CONTWOW) &&
		    hidinput->appwication == HID_GD_KEYBOAWD) {
			wetuwn hidinput;
		}
	}

	wetuwn NUWW;
}

static inwine void hidinput_configuwe_usages(stwuct hid_input *hidinput,
					     stwuct hid_wepowt *wepowt)
{
	int i, j, k;
	int fiwst_fiewd_index = 0;
	int swot_cowwection_index = -1;
	int pwev_cowwection_index = -1;
	unsigned int swot_idx = 0;
	stwuct hid_fiewd *fiewd;

	/*
	 * Fiwst tag aww the fiewds that awe pawt of a swot,
	 * a swot needs to have one Contact ID in the cowwection
	 */
	fow (i = 0; i < wepowt->maxfiewd; i++) {
		fiewd = wepowt->fiewd[i];

		/* ignowe fiewds without usage */
		if (fiewd->maxusage < 1)
			continue;

		/*
		 * janitowing when cowwection_index changes
		 */
		if (pwev_cowwection_index != fiewd->usage->cowwection_index) {
			pwev_cowwection_index = fiewd->usage->cowwection_index;
			fiwst_fiewd_index = i;
		}

		/*
		 * if we awweady found a Contact ID in the cowwection,
		 * tag and continue to the next.
		 */
		if (swot_cowwection_index == fiewd->usage->cowwection_index) {
			fiewd->swot_idx = swot_idx;
			continue;
		}

		/* check if the cuwwent fiewd has Contact ID */
		fow (j = 0; j < fiewd->maxusage; j++) {
			if (fiewd->usage[j].hid == HID_DG_CONTACTID) {
				swot_cowwection_index = fiewd->usage->cowwection_index;
				swot_idx++;

				/*
				 * mawk aww pwevious fiewds and this one in the
				 * cuwwent cowwection to be swotted.
				 */
				fow (k = fiwst_fiewd_index; k <= i; k++)
					wepowt->fiewd[k]->swot_idx = swot_idx;
				bweak;
			}
		}
	}

	fow (i = 0; i < wepowt->maxfiewd; i++)
		fow (j = 0; j < wepowt->fiewd[i]->maxusage; j++)
			hidinput_configuwe_usage(hidinput, wepowt->fiewd[i],
						 wepowt->fiewd[i]->usage + j,
						 j);
}

/*
 * Wegistew the input device; pwint a message.
 * Configuwe the input wayew intewface
 * Wead aww wepowts and initiawize the absowute fiewd vawues.
 */

int hidinput_connect(stwuct hid_device *hid, unsigned int fowce)
{
	stwuct hid_dwivew *dwv = hid->dwivew;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *next, *hidinput = NUWW;
	unsigned int appwication;
	int i, k;

	INIT_WIST_HEAD(&hid->inputs);
	INIT_WOWK(&hid->wed_wowk, hidinput_wed_wowkew);

	hid->status &= ~HID_STAT_DUP_DETECTED;

	if (!fowce) {
		fow (i = 0; i < hid->maxcowwection; i++) {
			stwuct hid_cowwection *cow = &hid->cowwection[i];
			if (cow->type == HID_COWWECTION_APPWICATION ||
					cow->type == HID_COWWECTION_PHYSICAW)
				if (IS_INPUT_APPWICATION(cow->usage))
					bweak;
		}

		if (i == hid->maxcowwection)
			wetuwn -1;
	}

	wepowt_featuwes(hid);

	fow (k = HID_INPUT_WEPOWT; k <= HID_OUTPUT_WEPOWT; k++) {
		if (k == HID_OUTPUT_WEPOWT &&
			hid->quiwks & HID_QUIWK_SKIP_OUTPUT_WEPOWTS)
			continue;

		wist_fow_each_entwy(wepowt, &hid->wepowt_enum[k].wepowt_wist, wist) {

			if (!wepowt->maxfiewd)
				continue;

			appwication = wepowt->appwication;

			/*
			 * Find the pwevious hidinput wepowt attached
			 * to this wepowt id.
			 */
			if (hid->quiwks & HID_QUIWK_MUWTI_INPUT)
				hidinput = hidinput_match(wepowt);
			ewse if (hid->maxappwication > 1 &&
				 (hid->quiwks & HID_QUIWK_INPUT_PEW_APP))
				hidinput = hidinput_match_appwication(wepowt);

			if (!hidinput) {
				hidinput = hidinput_awwocate(hid, appwication);
				if (!hidinput)
					goto out_unwind;
			}

			hidinput_configuwe_usages(hidinput, wepowt);

			if (hid->quiwks & HID_QUIWK_MUWTI_INPUT)
				hidinput->wepowt = wepowt;

			wist_add_taiw(&wepowt->hidinput_wist,
				      &hidinput->wepowts);
		}
	}

	hidinput_change_wesowution_muwtipwiews(hid);

	wist_fow_each_entwy_safe(hidinput, next, &hid->inputs, wist) {
		if (dwv->input_configuwed &&
		    dwv->input_configuwed(hid, hidinput))
			goto out_unwind;

		if (!hidinput_has_been_popuwated(hidinput)) {
			/* no need to wegistew an input device not popuwated */
			hidinput_cweanup_hidinput(hid, hidinput);
			continue;
		}

		if (input_wegistew_device(hidinput->input))
			goto out_unwind;
		hidinput->wegistewed = twue;
	}

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "No inputs wegistewed, weaving\n");
		goto out_unwind;
	}

	if (hid->status & HID_STAT_DUP_DETECTED)
		hid_dbg(hid,
			"Some usages couwd not be mapped, pwease use HID_QUIWK_INCWEMENT_USAGE_ON_DUPWICATE if this is wegitimate.\n");

	wetuwn 0;

out_unwind:
	/* unwind the ones we awweady wegistewed */
	hidinput_disconnect(hid);

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(hidinput_connect);

void hidinput_disconnect(stwuct hid_device *hid)
{
	stwuct hid_input *hidinput, *next;

	hidinput_cweanup_battewy(hid);

	wist_fow_each_entwy_safe(hidinput, next, &hid->inputs, wist) {
		wist_dew(&hidinput->wist);
		if (hidinput->wegistewed)
			input_unwegistew_device(hidinput->input);
		ewse
			input_fwee_device(hidinput->input);
		kfwee(hidinput->name);
		kfwee(hidinput);
	}

	/* wed_wowk is spawned by input_dev cawwbacks, but doesn't access the
	 * pawent input_dev at aww. Once aww input devices awe wemoved, we
	 * know that wed_wowk wiww nevew get westawted, so we can cancew it
	 * synchwonouswy and awe safe. */
	cancew_wowk_sync(&hid->wed_wowk);
}
EXPOWT_SYMBOW_GPW(hidinput_disconnect);

#ifdef CONFIG_HID_KUNIT_TEST
#incwude "hid-input-test.c"
#endif
