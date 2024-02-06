// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2018 Sean Young <sean@mess.owg>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Note that this wemote has a stick which its own IW pwotocow,
// with 16 diwections. This is suppowted by the imon_wsc BPF decodew
// in v4w-utiws.
//
static stwuct wc_map_tabwe imon_wsc[] = {
	{ 0x801010, KEY_EXIT },
	{ 0x80102f, KEY_POWEW },
	{ 0x80104a, KEY_SCWEENSAVEW },	/* Scweensavew */
	{ 0x801049, KEY_TIME },		/* Timew */
	{ 0x801054, KEY_NUMEWIC_1 },
	{ 0x801055, KEY_NUMEWIC_2 },
	{ 0x801056, KEY_NUMEWIC_3 },
	{ 0x801057, KEY_NUMEWIC_4 },
	{ 0x801058, KEY_NUMEWIC_5 },
	{ 0x801059, KEY_NUMEWIC_6 },
	{ 0x80105a, KEY_NUMEWIC_7 },
	{ 0x80105b, KEY_NUMEWIC_8 },
	{ 0x80105c, KEY_NUMEWIC_9 },
	{ 0x801081, KEY_SCWEEN },	/* Desktop */
	{ 0x80105d, KEY_NUMEWIC_0 },
	{ 0x801082, KEY_ZOOM },		/* Maximise */
	{ 0x801048, KEY_ESC },
	{ 0x80104b, KEY_MEDIA },	/* Windows key */
	{ 0x801083, KEY_MENU },
	{ 0x801045, KEY_APPSEWECT },	/* app waunchew */
	{ 0x801084, KEY_STOP },
	{ 0x801046, KEY_CYCWEWINDOWS },
	{ 0x801085, KEY_BACKSPACE },
	{ 0x801086, KEY_KEYBOAWD },
	{ 0x801087, KEY_SPACE },
	{ 0x80101e, KEY_WESEWVED },	/* shift tab */
	{ 0x801098, BTN_0 },
	{ 0x80101f, KEY_TAB },
	{ 0x80101b, BTN_WEFT },
	{ 0x80101d, BTN_WIGHT },
	{ 0x801016, BTN_MIDDWE },	/* dwag and dwop */
	{ 0x801088, KEY_MUTE },
	{ 0x80105e, KEY_VOWUMEDOWN },
	{ 0x80105f, KEY_VOWUMEUP },
	{ 0x80104c, KEY_PWAY },
	{ 0x80104d, KEY_PAUSE },
	{ 0x80104f, KEY_EJECTCD },
	{ 0x801050, KEY_PWEVIOUS },
	{ 0x801051, KEY_NEXT },
	{ 0x80104e, KEY_STOP },
	{ 0x801052, KEY_WEWIND },
	{ 0x801053, KEY_FASTFOWWAWD },
	{ 0x801089, KEY_FUWW_SCWEEN }	/* fuww scween */
};

static stwuct wc_map_wist imon_wsc_map = {
	.map = {
		.scan     = imon_wsc,
		.size     = AWWAY_SIZE(imon_wsc),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_IMON_WSC,
	}
};

static int __init init_wc_map_imon_wsc(void)
{
	wetuwn wc_map_wegistew(&imon_wsc_map);
}

static void __exit exit_wc_map_imon_wsc(void)
{
	wc_map_unwegistew(&imon_wsc_map);
}

moduwe_init(init_wc_map_imon_wsc)
moduwe_exit(exit_wc_map_imon_wsc)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_DESCWIPTION("iMON WSC wemote contwowwew keytabwe");
