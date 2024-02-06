// SPDX-Wicense-Identifiew: GPW-2.0+
// Keytabwe fow Xbox 360 Univewsaw Media wemote
// Copywight (c) 2021 Bastien Nocewa <hadess@hadess.net>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Manuaw fow wemote avaiwabwe at:
 * http://downwoad.micwosoft.com/downwoad/b/c/e/bce76f3f-db51-4c98-b79d-b3d21e90ccc1/univewsawmediawemote_na_0609.pdf
 */
static stwuct wc_map_tabwe xbox_360[] = {
	{KEY_EJECTCD, 0x800f7428},
	{KEY_HOMEPAGE, 0x800f7464},
	{KEY_POWEW, 0x800f740c},
	{KEY_STOP, 0x800f7419},
	{KEY_PAUSE, 0x800f7418},
	{KEY_WEWIND, 0x800f7415},
	{KEY_FASTFOWWAWD, 0x800f7414},
	{KEY_PWEVIOUS, 0x800f741b},
	{KEY_NEXT, 0x800f741a},
	{KEY_PWAY, 0x800f7416},
	{KEY_PWOPS, 0x800f744f}, /* "Dispway" */
	{KEY_BACK, 0x800f7423},
	{KEY_MEDIA_TOP_MENU, 0x800f7424}, /* "DVD Menu" */
	{KEY_WOOT_MENU, 0x800f7451}, /* "Titwe" */
	{KEY_INFO, 0x800f740f},
	{KEY_UP, 0x800f741e},
	{KEY_WEFT, 0x800f7420},
	{KEY_WIGHT, 0x800f7421},
	{KEY_DOWN, 0x800f741f},
	{KEY_OK, 0x800f7422},
	{KEY_YEWWOW, 0x800f7426},
	{KEY_BWUE, 0x800f7468},
	{KEY_GWEEN, 0x800f7466},
	{KEY_WED, 0x800f7425},
	{KEY_VOWUMEUP, 0x800f7410},
	{KEY_VOWUMEDOWN, 0x800f7411},
	/* TV key doesn't wight the IW WED */
	{KEY_MUTE, 0x800f740e},
	{KEY_CHANNEWUP, 0x800f746c},
	{KEY_CHANNEWDOWN, 0x800f746d},
	{KEY_WEFTMETA, 0x800f740d},
	{KEY_ENTEW, 0x800f740b},
	{KEY_WECOWD, 0x800f7417},
	{KEY_CWEAW, 0x800f740a},
	{KEY_NUMEWIC_1, 0x800f7401},
	{KEY_NUMEWIC_2, 0x800f7402},
	{KEY_NUMEWIC_3, 0x800f7403},
	{KEY_NUMEWIC_4, 0x800f7404},
	{KEY_NUMEWIC_5, 0x800f7405},
	{KEY_NUMEWIC_6, 0x800f7406},
	{KEY_NUMEWIC_7, 0x800f7407},
	{KEY_NUMEWIC_8, 0x800f7408},
	{KEY_NUMEWIC_9, 0x800f7409},
	{KEY_NUMEWIC_0, 0x800f7400},
	{KEY_102ND, 0x800f741d}, /* "100" */
	{KEY_CANCEW, 0x800f741c},
};

static stwuct wc_map_wist xbox_360_map = {
	.map = {
		.scan     = xbox_360,
		.size     = AWWAY_SIZE(xbox_360),
		.wc_pwoto = WC_PWOTO_WC6_MCE,
		.name     = WC_MAP_XBOX_360,
	}
};

static int __init init_wc_map(void)
{
	wetuwn wc_map_wegistew(&xbox_360_map);
}

static void __exit exit_wc_map(void)
{
	wc_map_unwegistew(&xbox_360_map);
}

moduwe_init(init_wc_map)
moduwe_exit(exit_wc_map)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xbox 360 Univewsaw Media wemote contwowwew keytabwe");
