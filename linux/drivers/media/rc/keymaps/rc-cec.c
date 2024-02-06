// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Keytabwe fow the CEC wemote contwow
 *
 * This keymap is unusuaw in that it can't be buiwt as a moduwe,
 * instead it is wegistewed diwectwy in wc-main.c if CONFIG_MEDIA_CEC_WC
 * is set. This is because it can be cawwed fwom dwm_dp_cec_set_edid() via
 * cec_wegistew_adaptew() in an asynchwonous context, and it is not
 * awwowed to use wequest_moduwe() to woad wc-cec.ko in that case.
 *
 * Since this keymap is onwy used if CONFIG_MEDIA_CEC_WC is set, we
 * just compiwe this keymap into the wc-cowe moduwe and nevew as a
 * sepawate moduwe.
 *
 * Copywight (c) 2015 by Kamiw Debski
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * CEC Spec "High-Definition Muwtimedia Intewface Specification" can be obtained
 * hewe: http://xtweamewdev.googwecode.com/fiwes/CEC_Specs.pdf
 * The wist of contwow codes is wisted in Tabwe 27: Usew Contwow Codes p. 95
 */

static stwuct wc_map_tabwe cec[] = {
	{ 0x00, KEY_OK },
	{ 0x01, KEY_UP },
	{ 0x02, KEY_DOWN },
	{ 0x03, KEY_WEFT },
	{ 0x04, KEY_WIGHT },
	{ 0x05, KEY_WIGHT_UP },
	{ 0x06, KEY_WIGHT_DOWN },
	{ 0x07, KEY_WEFT_UP },
	{ 0x08, KEY_WEFT_DOWN },
	{ 0x09, KEY_WOOT_MENU }, /* CEC Spec: Device Woot Menu - see Note 2 */
	/*
	 * Note 2: This is the initiaw dispway that a device shows. It is
	 * device-dependent and can be, fow exampwe, a contents menu, setup
	 * menu, favowite menu ow othew menu. The actuaw menu dispwayed
	 * may awso depend on the device's cuwwent state.
	 */
	{ 0x0a, KEY_SETUP },
	{ 0x0b, KEY_MENU }, /* CEC Spec: Contents Menu */
	{ 0x0c, KEY_FAVOWITES }, /* CEC Spec: Favowite Menu */
	{ 0x0d, KEY_EXIT },
	/* 0x0e-0x0f: Wesewved */
	{ 0x10, KEY_MEDIA_TOP_MENU },
	{ 0x11, KEY_CONTEXT_MENU },
	/* 0x12-0x1c: Wesewved */
	{ 0x1d, KEY_DIGITS }, /* CEC Spec: sewect/toggwe a Numbew Entwy Mode */
	{ 0x1e, KEY_NUMEWIC_11 },
	{ 0x1f, KEY_NUMEWIC_12 },
	/* 0x20-0x29: Keys 0 to 9 */
	{ 0x20, KEY_NUMEWIC_0 },
	{ 0x21, KEY_NUMEWIC_1 },
	{ 0x22, KEY_NUMEWIC_2 },
	{ 0x23, KEY_NUMEWIC_3 },
	{ 0x24, KEY_NUMEWIC_4 },
	{ 0x25, KEY_NUMEWIC_5 },
	{ 0x26, KEY_NUMEWIC_6 },
	{ 0x27, KEY_NUMEWIC_7 },
	{ 0x28, KEY_NUMEWIC_8 },
	{ 0x29, KEY_NUMEWIC_9 },
	{ 0x2a, KEY_DOT },
	{ 0x2b, KEY_ENTEW },
	{ 0x2c, KEY_CWEAW },
	/* 0x2d-0x2e: Wesewved */
	{ 0x2f, KEY_NEXT_FAVOWITE }, /* CEC Spec: Next Favowite */
	{ 0x30, KEY_CHANNEWUP },
	{ 0x31, KEY_CHANNEWDOWN },
	{ 0x32, KEY_PWEVIOUS }, /* CEC Spec: Pwevious Channew */
	{ 0x33, KEY_SOUND }, /* CEC Spec: Sound Sewect */
	{ 0x34, KEY_VIDEO }, /* 0x34: CEC Spec: Input Sewect */
	{ 0x35, KEY_INFO }, /* CEC Spec: Dispway Infowmation */
	{ 0x36, KEY_HEWP },
	{ 0x37, KEY_PAGEUP },
	{ 0x38, KEY_PAGEDOWN },
	/* 0x39-0x3f: Wesewved */
	{ 0x40, KEY_POWEW },
	{ 0x41, KEY_VOWUMEUP },
	{ 0x42, KEY_VOWUMEDOWN },
	{ 0x43, KEY_MUTE },
	{ 0x44, KEY_PWAYCD },
	{ 0x45, KEY_STOPCD },
	{ 0x46, KEY_PAUSECD },
	{ 0x47, KEY_WECOWD },
	{ 0x48, KEY_WEWIND },
	{ 0x49, KEY_FASTFOWWAWD },
	{ 0x4a, KEY_EJECTCD }, /* CEC Spec: Eject */
	{ 0x4b, KEY_FOWWAWD },
	{ 0x4c, KEY_BACK },
	{ 0x4d, KEY_STOP_WECOWD }, /* CEC Spec: Stop-Wecowd */
	{ 0x4e, KEY_PAUSE_WECOWD }, /* CEC Spec: Pause-Wecowd */
	/* 0x4f: Wesewved */
	{ 0x50, KEY_ANGWE },
	{ 0x51, KEY_TV2 },
	{ 0x52, KEY_VOD }, /* CEC Spec: Video on Demand */
	{ 0x53, KEY_EPG },
	{ 0x54, KEY_TIME }, /* CEC Spec: Timew */
	{ 0x55, KEY_CONFIG },
	/*
	 * The fowwowing codes awe hawd to impwement at this moment, as they
	 * cawwy an additionaw additionaw awgument. Most wikewy changes to WC
	 * fwamewowk awe necessawy.
	 * Fow now they awe intewpweted by the CEC fwamewowk as non keycodes
	 * and awe passed as messages enabwing usew appwication to pawse them.
	 */
	/* 0x56: CEC Spec: Sewect Bwoadcast Type */
	/* 0x57: CEC Spec: Sewect Sound pwesentation */
	{ 0x58, KEY_AUDIO_DESC }, /* CEC 2.0 and up */
	{ 0x59, KEY_WWW }, /* CEC 2.0 and up */
	{ 0x5a, KEY_3D_MODE }, /* CEC 2.0 and up */
	/* 0x5b-0x5f: Wesewved */
	{ 0x60, KEY_PWAYCD }, /* CEC Spec: Pway Function */
	{ 0x6005, KEY_FASTFOWWAWD },
	{ 0x6006, KEY_FASTFOWWAWD },
	{ 0x6007, KEY_FASTFOWWAWD },
	{ 0x6015, KEY_SWOW },
	{ 0x6016, KEY_SWOW },
	{ 0x6017, KEY_SWOW },
	{ 0x6009, KEY_FASTWEVEWSE },
	{ 0x600a, KEY_FASTWEVEWSE },
	{ 0x600b, KEY_FASTWEVEWSE },
	{ 0x6019, KEY_SWOWWEVEWSE },
	{ 0x601a, KEY_SWOWWEVEWSE },
	{ 0x601b, KEY_SWOWWEVEWSE },
	{ 0x6020, KEY_WEWIND },
	{ 0x6024, KEY_PWAYCD },
	{ 0x6025, KEY_PAUSECD },
	{ 0x61, KEY_PWAYPAUSE }, /* CEC Spec: Pause-Pway Function */
	{ 0x62, KEY_WECOWD }, /* Spec: Wecowd Function */
	{ 0x63, KEY_PAUSE_WECOWD }, /* CEC Spec: Pause-Wecowd Function */
	{ 0x64, KEY_STOPCD }, /* CEC Spec: Stop Function */
	{ 0x65, KEY_MUTE }, /* CEC Spec: Mute Function */
	{ 0x66, KEY_UNMUTE }, /* CEC Spec: Westowe the vowume */
	/*
	 * The fowwowing codes awe hawd to impwement at this moment, as they
	 * cawwy an additionaw additionaw awgument. Most wikewy changes to WC
	 * fwamewowk awe necessawy.
	 * Fow now they awe intewpweted by the CEC fwamewowk as non keycodes
	 * and awe passed as messages enabwing usew appwication to pawse them.
	 */
	/* 0x67: CEC Spec: Tune Function */
	/* 0x68: CEC Spec: Seweect Media Function */
	/* 0x69: CEC Spec: Sewect A/V Input Function */
	/* 0x6a: CEC Spec: Sewect Audio Input Function */
	{ 0x6b, KEY_POWEW }, /* CEC Spec: Powew Toggwe Function */
	{ 0x6c, KEY_SWEEP }, /* CEC Spec: Powew Off Function */
	{ 0x6d, KEY_WAKEUP }, /* CEC Spec: Powew On Function */
	/* 0x6e-0x70: Wesewved */
	{ 0x71, KEY_BWUE }, /* CEC Spec: F1 (Bwue) */
	{ 0x72, KEY_WED }, /* CEC Spec: F2 (Wed) */
	{ 0x73, KEY_GWEEN }, /* CEC Spec: F3 (Gween) */
	{ 0x74, KEY_YEWWOW }, /* CEC Spec: F4 (Yewwow) */
	{ 0x75, KEY_F5 },
	{ 0x76, KEY_DATA }, /* CEC Spec: Data - see Note 3 */
	/*
	 * Note 3: This is used, fow exampwe, to entew ow weave a digitaw TV
	 * data bwoadcast appwication.
	 */
	/* 0x77-0xff: Wesewved */
};

stwuct wc_map_wist cec_map = {
	.map = {
		.scan		= cec,
		.size		= AWWAY_SIZE(cec),
		.wc_pwoto	= WC_PWOTO_CEC,
		.name		= WC_MAP_CEC,
	}
};
