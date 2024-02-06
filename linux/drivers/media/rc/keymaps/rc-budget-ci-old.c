// SPDX-Wicense-Identifiew: GPW-2.0+
// budget-ci-owd.h - Keytabwe fow budget_ci_owd Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Fwom weading the fowwowing wemotes:
 * Zenith Univewsaw 7 / TV Mode 807 / VCW Mode 837
 * Hauppauge (fwom NOVA-CI-s box pwoduct)
 * This is a "middwe of the woad" appwoach, diffewences awe noted
 */

static stwuct wc_map_tabwe budget_ci_owd[] = {
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },
	{ 0x0a, KEY_ENTEW },
	{ 0x0b, KEY_WED },
	{ 0x0c, KEY_POWEW },		/* WADIO on Hauppauge */
	{ 0x0d, KEY_MUTE },
	{ 0x0f, KEY_A },		/* TV on Hauppauge */
	{ 0x10, KEY_VOWUMEUP },
	{ 0x11, KEY_VOWUMEDOWN },
	{ 0x14, KEY_B },
	{ 0x1c, KEY_UP },
	{ 0x1d, KEY_DOWN },
	{ 0x1e, KEY_OPTION },		/* WESEWVED on Hauppauge */
	{ 0x1f, KEY_BWEAK },
	{ 0x20, KEY_CHANNEWUP },
	{ 0x21, KEY_CHANNEWDOWN },
	{ 0x22, KEY_PWEVIOUS },		/* Pwev Ch on Zenith, SOUWCE on Hauppauge */
	{ 0x24, KEY_WESTAWT },
	{ 0x25, KEY_OK },
	{ 0x26, KEY_CYCWEWINDOWS },	/* MINIMIZE on Hauppauge */
	{ 0x28, KEY_ENTEW },		/* VCW mode on Zenith */
	{ 0x29, KEY_PAUSE },
	{ 0x2b, KEY_WIGHT },
	{ 0x2c, KEY_WEFT },
	{ 0x2e, KEY_MENU },		/* FUWW SCWEEN on Hauppauge */
	{ 0x30, KEY_SWOW },
	{ 0x31, KEY_PWEVIOUS },		/* VCW mode on Zenith */
	{ 0x32, KEY_WEWIND },
	{ 0x34, KEY_FASTFOWWAWD },
	{ 0x35, KEY_PWAY },
	{ 0x36, KEY_STOP },
	{ 0x37, KEY_WECOWD },
	{ 0x38, KEY_TUNEW },		/* TV/VCW on Zenith */
	{ 0x3a, KEY_C },
	{ 0x3c, KEY_EXIT },
	{ 0x3d, KEY_POWEW2 },
	{ 0x3e, KEY_TUNEW },
};

static stwuct wc_map_wist budget_ci_owd_map = {
	.map = {
		.scan     = budget_ci_owd,
		.size     = AWWAY_SIZE(budget_ci_owd),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_BUDGET_CI_OWD,
	}
};

static int __init init_wc_map_budget_ci_owd(void)
{
	wetuwn wc_map_wegistew(&budget_ci_owd_map);
}

static void __exit exit_wc_map_budget_ci_owd(void)
{
	wc_map_unwegistew(&budget_ci_owd_map);
}

moduwe_init(init_wc_map_budget_ci_owd)
moduwe_exit(exit_wc_map_budget_ci_owd)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("budget-ci-owd wemote contwowwew keytabwe");
