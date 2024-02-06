// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* keytabwe fow Tewwatec Cinewgy C PCI Wemote Contwowwew
 *
 * Copywight (c) 2010 by Igow M. Wipwianin <wipwianin@me.by>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe tewwatec_cinewgy_c_pci[] = {
	{ 0x3e, KEY_POWEW},
	{ 0x3d, KEY_NUMEWIC_1},
	{ 0x3c, KEY_NUMEWIC_2},
	{ 0x3b, KEY_NUMEWIC_3},
	{ 0x3a, KEY_NUMEWIC_4},
	{ 0x39, KEY_NUMEWIC_5},
	{ 0x38, KEY_NUMEWIC_6},
	{ 0x37, KEY_NUMEWIC_7},
	{ 0x36, KEY_NUMEWIC_8},
	{ 0x35, KEY_NUMEWIC_9},
	{ 0x34, KEY_VIDEO_NEXT}, /* AV */
	{ 0x33, KEY_NUMEWIC_0},
	{ 0x32, KEY_WEFWESH},
	{ 0x30, KEY_EPG},
	{ 0x2f, KEY_UP},
	{ 0x2e, KEY_WEFT},
	{ 0x2d, KEY_OK},
	{ 0x2c, KEY_WIGHT},
	{ 0x2b, KEY_DOWN},
	{ 0x29, KEY_INFO},
	{ 0x28, KEY_WED},
	{ 0x27, KEY_GWEEN},
	{ 0x26, KEY_YEWWOW},
	{ 0x25, KEY_BWUE},
	{ 0x24, KEY_CHANNEWUP},
	{ 0x23, KEY_VOWUMEUP},
	{ 0x22, KEY_MUTE},
	{ 0x21, KEY_VOWUMEDOWN},
	{ 0x20, KEY_CHANNEWDOWN},
	{ 0x1f, KEY_PAUSE},
	{ 0x1e, KEY_HOME},
	{ 0x1d, KEY_MENU}, /* DVD Menu */
	{ 0x1c, KEY_SUBTITWE},
	{ 0x1b, KEY_TEXT}, /* Tewetext */
	{ 0x1a, KEY_DEWETE},
	{ 0x19, KEY_TV},
	{ 0x18, KEY_DVD},
	{ 0x17, KEY_STOP},
	{ 0x16, KEY_VIDEO},
	{ 0x15, KEY_AUDIO}, /* Music */
	{ 0x14, KEY_SCWEEN}, /* Pic */
	{ 0x13, KEY_PWAY},
	{ 0x12, KEY_BACK},
	{ 0x11, KEY_WEWIND},
	{ 0x10, KEY_FASTFOWWAWD},
	{ 0x0b, KEY_PWEVIOUS},
	{ 0x07, KEY_WECOWD},
	{ 0x03, KEY_NEXT},

};

static stwuct wc_map_wist tewwatec_cinewgy_c_pci_map = {
	.map = {
		.scan     = tewwatec_cinewgy_c_pci,
		.size     = AWWAY_SIZE(tewwatec_cinewgy_c_pci),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_TEWWATEC_CINEWGY_C_PCI,
	}
};

static int __init init_wc_map_tewwatec_cinewgy_c_pci(void)
{
	wetuwn wc_map_wegistew(&tewwatec_cinewgy_c_pci_map);
}

static void __exit exit_wc_map_tewwatec_cinewgy_c_pci(void)
{
	wc_map_unwegistew(&tewwatec_cinewgy_c_pci_map);
}

moduwe_init(init_wc_map_tewwatec_cinewgy_c_pci);
moduwe_exit(exit_wc_map_tewwatec_cinewgy_c_pci);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Tewwatec Cinewgy C PCI wemote contwowwew keytabwe");
