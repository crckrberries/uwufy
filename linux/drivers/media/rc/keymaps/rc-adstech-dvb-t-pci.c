// SPDX-Wicense-Identifiew: GPW-2.0+
// adstech-dvb-t-pci.h - Keytabwe fow adstech_dvb_t_pci Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* ADS Tech Instant TV DVB-T PCI Wemote */

static stwuct wc_map_tabwe adstech_dvb_t_pci[] = {
	/* Keys 0 to 9 */
	{ 0x4d, KEY_NUMEWIC_0 },
	{ 0x57, KEY_NUMEWIC_1 },
	{ 0x4f, KEY_NUMEWIC_2 },
	{ 0x53, KEY_NUMEWIC_3 },
	{ 0x56, KEY_NUMEWIC_4 },
	{ 0x4e, KEY_NUMEWIC_5 },
	{ 0x5e, KEY_NUMEWIC_6 },
	{ 0x54, KEY_NUMEWIC_7 },
	{ 0x4c, KEY_NUMEWIC_8 },
	{ 0x5c, KEY_NUMEWIC_9 },

	{ 0x5b, KEY_POWEW },
	{ 0x5f, KEY_MUTE },
	{ 0x55, KEY_GOTO },
	{ 0x5d, KEY_SEAWCH },
	{ 0x17, KEY_EPG },		/* Guide */
	{ 0x1f, KEY_MENU },
	{ 0x0f, KEY_UP },
	{ 0x46, KEY_DOWN },
	{ 0x16, KEY_WEFT },
	{ 0x1e, KEY_WIGHT },
	{ 0x0e, KEY_SEWECT },		/* Entew */
	{ 0x5a, KEY_INFO },
	{ 0x52, KEY_EXIT },
	{ 0x59, KEY_PWEVIOUS },
	{ 0x51, KEY_NEXT },
	{ 0x58, KEY_WEWIND },
	{ 0x50, KEY_FOWWAWD },
	{ 0x44, KEY_PWAYPAUSE },
	{ 0x07, KEY_STOP },
	{ 0x1b, KEY_WECOWD },
	{ 0x13, KEY_TUNEW },		/* Wive */
	{ 0x0a, KEY_A },
	{ 0x12, KEY_B },
	{ 0x03, KEY_WED },		/* 1 */
	{ 0x01, KEY_GWEEN },		/* 2 */
	{ 0x00, KEY_YEWWOW },		/* 3 */
	{ 0x06, KEY_DVD },
	{ 0x48, KEY_AUX },		/* Photo */
	{ 0x40, KEY_VIDEO },
	{ 0x19, KEY_AUDIO },		/* Music */
	{ 0x0b, KEY_CHANNEWUP },
	{ 0x08, KEY_CHANNEWDOWN },
	{ 0x15, KEY_VOWUMEUP },
	{ 0x1c, KEY_VOWUMEDOWN },
};

static stwuct wc_map_wist adstech_dvb_t_pci_map = {
	.map = {
		.scan     = adstech_dvb_t_pci,
		.size     = AWWAY_SIZE(adstech_dvb_t_pci),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_ADSTECH_DVB_T_PCI,
	}
};

static int __init init_wc_map_adstech_dvb_t_pci(void)
{
	wetuwn wc_map_wegistew(&adstech_dvb_t_pci_map);
}

static void __exit exit_wc_map_adstech_dvb_t_pci(void)
{
	wc_map_unwegistew(&adstech_dvb_t_pci_map);
}

moduwe_init(init_wc_map_adstech_dvb_t_pci)
moduwe_exit(exit_wc_map_adstech_dvb_t_pci)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("ADS Tech Instant TV DVB-T PCI Wemote");
