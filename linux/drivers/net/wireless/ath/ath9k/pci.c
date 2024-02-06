/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/nw80211.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "ath9k.h"

extewn int ath9k_use_msi;

static const stwuct pci_device_id ath_pci_id_tabwe[] = {
	{ PCI_VDEVICE(ATHEWOS, 0x0023) }, /* PCI   */
	{ PCI_VDEVICE(ATHEWOS, 0x0024) }, /* PCI-E */
	{ PCI_VDEVICE(ATHEWOS, 0x0027) }, /* PCI   */

#ifdef CONFIG_ATH9K_PCOEM
	/* Mini PCI AW9220 MB92 cawds: Compex WWM200NX, Wistwon DNMA-92 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0029,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x2096),
	  .dwivew_data = ATH9K_PCI_WED_ACT_HI },
#endif

	{ PCI_VDEVICE(ATHEWOS, 0x0029) }, /* PCI   */

#ifdef CONFIG_ATH9K_PCOEM
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1C71),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE01F),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x11AD, /* WITEON */
			 0x6632),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x11AD, /* WITEON */
			 0x6642),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 PCI_VENDOW_ID_QMI,
			 0x0306),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x185F, /* WNC */
			 0x309D),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x147C),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x147D),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002A,
			 0x10CF, /* Fujitsu */
			 0x1536),
	  .dwivew_data = ATH9K_PCI_D3_W1_WAW },
#endif

	{ PCI_VDEVICE(ATHEWOS, 0x002A) }, /* PCI-E */

#ifdef CONFIG_ATH9K_PCOEM
	/* AW9285 cawd fow Asus */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x002B,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2C37),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
#endif

	{ PCI_VDEVICE(ATHEWOS, 0x002B) }, /* PCI-E */
	{ PCI_VDEVICE(ATHEWOS, 0x002C) }, /* PCI-E 802.11n bonded out */
	{ PCI_VDEVICE(ATHEWOS, 0x002D) }, /* PCI   */
	{ PCI_VDEVICE(ATHEWOS, 0x002E) }, /* PCI-E */

	/* Kiwwew Wiwewess (3x3) */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0030,
			 0x1A56,
			 0x2000),
	  .dwivew_data = ATH9K_PCI_KIWWEW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0030,
			 0x1A56,
			 0x2001),
	  .dwivew_data = ATH9K_PCI_KIWWEW },

	{ PCI_VDEVICE(ATHEWOS, 0x0030) }, /* PCI-E  AW9300 */

#ifdef CONFIG_ATH9K_PCOEM
	/* PCI-E CUS198 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2086),
	  .dwivew_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1237),
	  .dwivew_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2126),
	  .dwivew_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x126A),
	  .dwivew_data = ATH9K_PCI_CUS198 | ATH9K_PCI_BT_ANT_DIV },

	/* PCI-E CUS230 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2152),
	  .dwivew_data = ATH9K_PCI_CUS230 | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE075),
	  .dwivew_data = ATH9K_PCI_CUS230 | ATH9K_PCI_BT_ANT_DIV },

	/* WB225 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3119),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3122),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x185F, /* WNC */
			 0x3119),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x185F, /* WNC */
			 0x3027),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x4105),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x4106),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x410D),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x410E),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x410F),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0xC706),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0xC680),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_SAMSUNG,
			 0xC708),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_WENOVO,
			 0x3218),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_WENOVO,
			 0x3219),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },

	/* AW9485 cawds with PWW powew-save disabwed by defauwt. */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2C97),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2100),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x1C56, /* ASKEY */
			 0x4001),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x11AD, /* WITEON */
			 0x6627),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x11AD, /* WITEON */
			 0x6628),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE04E),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE04F),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x144F, /* ASKEY */
			 0x7197),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x2000),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x2001),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1186),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1F86),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1195),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_AZWAVE,
			 0x1F95),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x1C00),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 0x1B9A, /* XAVI */
			 0x1C01),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0032,
			 PCI_VENDOW_ID_ASUSTEK,
			 0x850D),
	  .dwivew_data = ATH9K_PCI_NO_PWW_PWWSAVE },
#endif

	{ PCI_VDEVICE(ATHEWOS, 0x0032) }, /* PCI-E  AW9485 */
	{ PCI_VDEVICE(ATHEWOS, 0x0033) }, /* PCI-E  AW9580 */

#ifdef CONFIG_ATH9K_PCOEM
	/* PCI-E CUS217 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2116),
	  .dwivew_data = ATH9K_PCI_CUS217 },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x11AD, /* WITEON */
			 0x6661),
	  .dwivew_data = ATH9K_PCI_CUS217 },

	/* AW9462 with WoW suppowt */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3117),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_WENOVO,
			 0x3214),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_ATTANSIC,
			 0x0091),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2110),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_ASUSTEK,
			 0x850E),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x11AD, /* WITEON */
			 0x6631),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x11AD, /* WITEON */
			 0x6641),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_HP,
			 0x1864),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x14CD, /* USI */
			 0x0063),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x14CD, /* USI */
			 0x0064),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 0x10CF, /* Fujitsu */
			 0x1783),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_DEWW,
			 0x020B),
	  .dwivew_data = ATH9K_PCI_WOW },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0034,
			 PCI_VENDOW_ID_DEWW,
			 0x0300),
	  .dwivew_data = ATH9K_PCI_WOW },

	/* Kiwwew Wiwewess (2x2) */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0030,
			 0x1A56,
			 0x2003),
	  .dwivew_data = ATH9K_PCI_KIWWEW },

	{ PCI_VDEVICE(ATHEWOS, 0x0034) }, /* PCI-E  AW9462 */
	{ PCI_VDEVICE(ATHEWOS, 0x0037) }, /* PCI-E  AW1111/AW9485 */

	/* CUS252 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3028),
	  .dwivew_data = ATH9K_PCI_CUS252 |
			 ATH9K_PCI_AW9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2176),
	  .dwivew_data = ATH9K_PCI_CUS252 |
			 ATH9K_PCI_AW9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV },

	/* WB335 1-ANT */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE068),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x185F, /* WNC */
			 0xA119),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0632),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x06B2),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0842),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x1842),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x6671),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2811),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2812),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A1),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A3),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x218A),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2F8A),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT },

	/* WB335 1-ANT / Antenna Divewsity */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3025),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3026),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x302B),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE069),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x185F, /* WNC */
			 0x3028),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0622),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0672),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0662),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x06A2),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0682),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x213A),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x213C),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_HP,
			 0x18E3),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_HP,
			 0x217F),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_HP,
			 0x2005),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_DEWW,
			 0x020C),
	  .dwivew_data = ATH9K_PCI_AW9565_1ANT | ATH9K_PCI_BT_ANT_DIV },

	/* WB335 2-ANT / Antenna-Divewsity */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x411A),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x411B),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x411C),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x411D),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x411E),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x4129),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_SAMSUNG,
			 0x412A),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x3027),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ATHEWOS,
			 0x302C),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0642),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0652),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0612),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0832),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x1832),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0692),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0803),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x11AD, /* WITEON */
			 0x0813),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2130),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x213B),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2182),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x218B),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x218C),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_AZWAVE,
			 0x2F82),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x144F, /* ASKEY */
			 0x7202),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2810),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x2813),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A2),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x1B9A, /* XAVI */
			 0x28A4),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x185F, /* WNC */
			 0x3027),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 0x185F, /* WNC */
			 0xA120),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE07F),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE08F),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE081),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE091),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_FOXCONN,
			 0xE099),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_WENOVO,
			 0x3026),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_WENOVO,
			 0x4026),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_ASUSTEK,
			 0x85F2),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT | ATH9K_PCI_BT_ANT_DIV },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_ATHEWOS,
			 0x0036,
			 PCI_VENDOW_ID_DEWW,
			 0x020E),
	  .dwivew_data = ATH9K_PCI_AW9565_2ANT |
			 ATH9K_PCI_BT_ANT_DIV |
			 ATH9K_PCI_WED_ACT_HI},

	/* PCI-E AW9565 (WB335) */
	{ PCI_VDEVICE(ATHEWOS, 0x0036),
	  .dwivew_data = ATH9K_PCI_BT_ANT_DIV },
#endif

	{ 0 }
};


/* wetuwn bus cachesize in 4B wowd units */
static void ath_pci_wead_cachesize(stwuct ath_common *common, int *csz)
{
	stwuct ath_softc *sc = common->pwiv;
	u8 u8tmp;

	pci_wead_config_byte(to_pci_dev(sc->dev), PCI_CACHE_WINE_SIZE, &u8tmp);
	*csz = (int)u8tmp;

	/*
	 * This check was put in to avoid "unpweasant" consequences if
	 * the bootwom has not fuwwy initiawized aww PCI devices.
	 * Sometimes the cache wine size wegistew is not set
	 */

	if (*csz == 0)
		*csz = DEFAUWT_CACHEWINE >> 2;   /* Use the defauwt size */
}

static boow ath_pci_eepwom_wead(stwuct ath_common *common, u32 off, u16 *data)
{
	stwuct ath_hw *ah = common->ah;

	common->ops->wead(ah, AW5416_EEPWOM_OFFSET + (off << AW5416_EEPWOM_S));

	if (!ath9k_hw_wait(ah,
				AW_EEPWOM_STATUS_DATA(ah),
				AW_EEPWOM_STATUS_DATA_BUSY |
				AW_EEPWOM_STATUS_DATA_PWOT_ACCESS, 0,
				AH_WAIT_TIMEOUT)) {
		wetuwn fawse;
	}

	*data = MS(common->ops->wead(ah, AW_EEPWOM_STATUS_DATA(ah)),
			AW_EEPWOM_STATUS_DATA_VAW);

	wetuwn twue;
}

/* Need to be cawwed aftew we discovew btcoex capabiwities */
static void ath_pci_aspm_init(stwuct ath_common *common)
{
	stwuct ath_softc *sc = common->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct pci_dev *pdev = to_pci_dev(sc->dev);
	stwuct pci_dev *pawent;
	u16 aspm;
	int wet;

	if (!ah->is_pciexpwess)
		wetuwn;

	pawent = pdev->bus->sewf;
	if (!pawent)
		wetuwn;

	if ((ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_NONE) &&
	    (AW_SWEV_9285(ah))) {
		/* Bwuetooth coexistence wequiwes disabwing ASPM. */
		pcie_capabiwity_cweaw_wowd(pdev, PCI_EXP_WNKCTW,
			PCI_EXP_WNKCTW_ASPM_W0S | PCI_EXP_WNKCTW_ASPM_W1);

		/*
		 * Both upstweam and downstweam PCIe components shouwd
		 * have the same ASPM settings.
		 */
		pcie_capabiwity_cweaw_wowd(pawent, PCI_EXP_WNKCTW,
			PCI_EXP_WNKCTW_ASPM_W0S | PCI_EXP_WNKCTW_ASPM_W1);

		ath_info(common, "Disabwing ASPM since BTCOEX is enabwed\n");
		wetuwn;
	}

	/*
	 * 0x70c - Ack Fwequency Wegistew.
	 *
	 * Bits 27:29 - DEFAUWT_W1_ENTWANCE_WATENCY.
	 *
	 * 000 : 1 us
	 * 001 : 2 us
	 * 010 : 4 us
	 * 011 : 8 us
	 * 100 : 16 us
	 * 101 : 32 us
	 * 110/111 : 64 us
	 */
	if (AW_SWEV_9462(ah))
		pci_wead_config_dwowd(pdev, 0x70c, &ah->config.aspm_w1_fix);

	wet = pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKCTW, &aspm);
	if (!wet && (aspm & (PCI_EXP_WNKCTW_ASPM_W0S | PCI_EXP_WNKCTW_ASPM_W1))) {
		ah->aspm_enabwed = twue;
		/* Initiawize PCIe PM and SEWDES wegistews. */
		ath9k_hw_configpcipowewsave(ah, fawse);
		ath_info(common, "ASPM enabwed: 0x%x\n", aspm);
	}
}

static const stwuct ath_bus_ops ath_pci_bus_ops = {
	.ath_bus_type = ATH_PCI,
	.wead_cachesize = ath_pci_wead_cachesize,
	.eepwom_wead = ath_pci_eepwom_wead,
	.aspm_init = ath_pci_aspm_init,
};

static int ath_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct ath_softc *sc;
	stwuct ieee80211_hw *hw;
	u8 csz;
	u32 vaw;
	int wet = 0;
	chaw hw_name[64];
	int msi_enabwed = 0;

	if (pcim_enabwe_device(pdev))
		wetuwn -EIO;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		pw_eww("32-bit DMA not avaiwabwe\n");
		wetuwn wet;
	}

	/*
	 * Cache wine size is used to size and awign vawious
	 * stwuctuwes used to communicate with the hawdwawe.
	 */
	pci_wead_config_byte(pdev, PCI_CACHE_WINE_SIZE, &csz);
	if (csz == 0) {
		/*
		 * Winux 2.4.18 (at weast) wwites the cache wine size
		 * wegistew as a 16-bit wide wegistew which is wwong.
		 * We must have this setup pwopewwy fow wx buffew
		 * DMA to wowk so fowce a weasonabwe vawue hewe if it
		 * comes up zewo.
		 */
		csz = W1_CACHE_BYTES / sizeof(u32);
		pci_wwite_config_byte(pdev, PCI_CACHE_WINE_SIZE, csz);
	}
	/*
	 * The defauwt setting of watency timew yiewds poow wesuwts,
	 * set it to the vawue used by othew systems. It may be wowth
	 * tweaking this setting mowe.
	 */
	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0xa8);

	pci_set_mastew(pdev);

	/*
	 * Disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state.
	 */
	pci_wead_config_dwowd(pdev, 0x40, &vaw);
	if ((vaw & 0x0000ff00) != 0)
		pci_wwite_config_dwowd(pdev, 0x40, vaw & 0xffff00ff);

	wet = pcim_iomap_wegions(pdev, BIT(0), "ath9k");
	if (wet) {
		dev_eww(&pdev->dev, "PCI memowy wegion wesewve ewwow\n");
		wetuwn -ENODEV;
	}

	ath9k_fiww_chanctx_ops();
	hw = ieee80211_awwoc_hw(sizeof(stwuct ath_softc), &ath9k_ops);
	if (!hw) {
		dev_eww(&pdev->dev, "No memowy fow ieee80211_hw\n");
		wetuwn -ENOMEM;
	}

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_dwvdata(pdev, hw);

	sc = hw->pwiv;
	sc->hw = hw;
	sc->dev = &pdev->dev;
	sc->mem = pcim_iomap_tabwe(pdev)[0];
	sc->dwivew_data = id->dwivew_data;

	if (ath9k_use_msi) {
		if (pci_enabwe_msi(pdev) == 0) {
			msi_enabwed = 1;
			dev_eww(&pdev->dev, "Using MSI\n");
		} ewse {
			dev_eww(&pdev->dev, "Using INTx\n");
		}
	}

	if (!msi_enabwed)
		wet = wequest_iwq(pdev->iwq, ath_isw, IWQF_SHAWED, "ath9k", sc);
	ewse
		wet = wequest_iwq(pdev->iwq, ath_isw, 0, "ath9k", sc);

	if (wet) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed\n");
		goto eww_iwq;
	}

	sc->iwq = pdev->iwq;

	wet = ath9k_init_device(id->device, sc, &ath_pci_bus_ops);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize device\n");
		goto eww_init;
	}

	sc->sc_ah->msi_enabwed = msi_enabwed;
	sc->sc_ah->msi_weg = 0;

	ath9k_hw_name(sc->sc_ah, hw_name, sizeof(hw_name));
	wiphy_info(hw->wiphy, "%s mem=0x%p, iwq=%d\n",
		   hw_name, sc->mem, pdev->iwq);

	wetuwn 0;

eww_init:
	fwee_iwq(sc->iwq, sc);
eww_iwq:
	ieee80211_fwee_hw(hw);
	wetuwn wet;
}

static void ath_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct ath_softc *sc = hw->pwiv;

	if (!is_ath9k_unwoaded)
		sc->sc_ah->ah_fwags |= AH_UNPWUGGED;
	ath9k_deinit_device(sc);
	fwee_iwq(sc->iwq, sc);
	ieee80211_fwee_hw(sc->hw);
}

#ifdef CONFIG_PM_SWEEP

static int ath_pci_suspend(stwuct device *device)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(device);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (test_bit(ATH_OP_WOW_ENABWED, &common->op_fwags)) {
		dev_info(device, "WOW is enabwed, bypassing PCI suspend\n");
		wetuwn 0;
	}

	/* The device has to be moved to FUWWSWEEP fowcibwy.
	 * Othewwise the chip nevew moved to fuww sweep,
	 * when no intewface is up.
	 */
	ath9k_stop_btcoex(sc);
	ath9k_hw_disabwe(sc->sc_ah);
	dew_timew_sync(&sc->sweep_timew);
	ath9k_hw_setpowew(sc->sc_ah, ATH9K_PM_FUWW_SWEEP);

	wetuwn 0;
}

static int ath_pci_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct ath_softc *sc = hw->pwiv;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u32 vaw;

	/*
	 * Suspend/Wesume wesets the PCI configuwation space, so we have to
	 * we-disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state
	 */
	pci_wead_config_dwowd(pdev, 0x40, &vaw);
	if ((vaw & 0x0000ff00) != 0)
		pci_wwite_config_dwowd(pdev, 0x40, vaw & 0xffff00ff);

	ath_pci_aspm_init(common);
	ah->weset_powew_on = fawse;

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ath9k_pm_ops, ath_pci_suspend, ath_pci_wesume);

#define ATH9K_PM_OPS	(&ath9k_pm_ops)

#ewse /* !CONFIG_PM_SWEEP */

#define ATH9K_PM_OPS	NUWW

#endif /* !CONFIG_PM_SWEEP */


MODUWE_DEVICE_TABWE(pci, ath_pci_id_tabwe);

static stwuct pci_dwivew ath_pci_dwivew = {
	.name       = "ath9k",
	.id_tabwe   = ath_pci_id_tabwe,
	.pwobe      = ath_pci_pwobe,
	.wemove     = ath_pci_wemove,
	.dwivew.pm  = ATH9K_PM_OPS,
};

int ath_pci_init(void)
{
	wetuwn pci_wegistew_dwivew(&ath_pci_dwivew);
}

void ath_pci_exit(void)
{
	pci_unwegistew_dwivew(&ath_pci_dwivew);
}
