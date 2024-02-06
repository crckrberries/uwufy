// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTW8XXXU mac80211 USB dwivew - 8723b specific subdwivew
 *
 * Copywight (c) 2014 - 2017 Jes Sowensen <Jes.Sowensen@gmaiw.com>
 *
 * Powtions, notabwy cawibwation code:
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 * This dwivew was wwitten as a wepwacement fow the vendow pwovided
 * wtw8723au dwivew. As the Weawtek 8xxx chips awe vewy simiwaw in
 * theiw pwogwamming intewface, I have stawted adding suppowt fow
 * additionaw 8xxx chips wike the 8192cu, 8188cus, etc.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wiwewess.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwepawam.h>
#incwude <net/mac80211.h>
#incwude "wtw8xxxu.h"
#incwude "wtw8xxxu_wegs.h"

static const stwuct wtw8xxxu_weg8vaw wtw8723b_mac_init_tabwe[] = {
	{0x02f, 0x30}, {0x035, 0x00}, {0x039, 0x08}, {0x04e, 0xe0},
	{0x064, 0x00}, {0x067, 0x20}, {0x428, 0x0a}, {0x429, 0x10},
	{0x430, 0x00}, {0x431, 0x00},
	{0x432, 0x00}, {0x433, 0x01}, {0x434, 0x04}, {0x435, 0x05},
	{0x436, 0x07}, {0x437, 0x08}, {0x43c, 0x04}, {0x43d, 0x05},
	{0x43e, 0x07}, {0x43f, 0x08}, {0x440, 0x5d}, {0x441, 0x01},
	{0x442, 0x00}, {0x444, 0x10}, {0x445, 0x00}, {0x446, 0x00},
	{0x447, 0x00}, {0x448, 0x00}, {0x449, 0xf0}, {0x44a, 0x0f},
	{0x44b, 0x3e}, {0x44c, 0x10}, {0x44d, 0x00}, {0x44e, 0x00},
	{0x44f, 0x00}, {0x450, 0x00}, {0x451, 0xf0}, {0x452, 0x0f},
	{0x453, 0x00}, {0x456, 0x5e}, {0x460, 0x66}, {0x461, 0x66},
	{0x4c8, 0xff}, {0x4c9, 0x08}, {0x4cc, 0xff},
	{0x4cd, 0xff}, {0x4ce, 0x01}, {0x500, 0x26}, {0x501, 0xa2},
	{0x502, 0x2f}, {0x503, 0x00}, {0x504, 0x28}, {0x505, 0xa3},
	{0x506, 0x5e}, {0x507, 0x00}, {0x508, 0x2b}, {0x509, 0xa4},
	{0x50a, 0x5e}, {0x50b, 0x00}, {0x50c, 0x4f}, {0x50d, 0xa4},
	{0x50e, 0x00}, {0x50f, 0x00}, {0x512, 0x1c}, {0x514, 0x0a},
	{0x516, 0x0a}, {0x525, 0x4f},
	{0x550, 0x10}, {0x551, 0x10}, {0x559, 0x02}, {0x55c, 0x50},
	{0x55d, 0xff}, {0x605, 0x30}, {0x608, 0x0e}, {0x609, 0x2a},
	{0x620, 0xff}, {0x621, 0xff}, {0x622, 0xff}, {0x623, 0xff},
	{0x624, 0xff}, {0x625, 0xff}, {0x626, 0xff}, {0x627, 0xff},
	{0x638, 0x50}, {0x63c, 0x0a}, {0x63d, 0x0a}, {0x63e, 0x0e},
	{0x63f, 0x0e}, {0x640, 0x40}, {0x642, 0x40}, {0x643, 0x00},
	{0x652, 0xc8}, {0x66e, 0x05}, {0x700, 0x21}, {0x701, 0x43},
	{0x702, 0x65}, {0x703, 0x87}, {0x708, 0x21}, {0x709, 0x43},
	{0x70a, 0x65}, {0x70b, 0x87}, {0x765, 0x18}, {0x76e, 0x04},
	{0xffff, 0xff},
};

static const stwuct wtw8xxxu_weg32vaw wtw8723b_phy_1t_init_tabwe[] = {
	{0x800, 0x80040000}, {0x804, 0x00000003},
	{0x808, 0x0000fc00}, {0x80c, 0x0000000a},
	{0x810, 0x10001331}, {0x814, 0x020c3d10},
	{0x818, 0x02200385}, {0x81c, 0x00000000},
	{0x820, 0x01000100}, {0x824, 0x00190204},
	{0x828, 0x00000000}, {0x82c, 0x00000000},
	{0x830, 0x00000000}, {0x834, 0x00000000},
	{0x838, 0x00000000}, {0x83c, 0x00000000},
	{0x840, 0x00010000}, {0x844, 0x00000000},
	{0x848, 0x00000000}, {0x84c, 0x00000000},
	{0x850, 0x00000000}, {0x854, 0x00000000},
	{0x858, 0x569a11a9}, {0x85c, 0x01000014},
	{0x860, 0x66f60110}, {0x864, 0x061f0649},
	{0x868, 0x00000000}, {0x86c, 0x27272700},
	{0x870, 0x07000760}, {0x874, 0x25004000},
	{0x878, 0x00000808}, {0x87c, 0x00000000},
	{0x880, 0xb0000c1c}, {0x884, 0x00000001},
	{0x888, 0x00000000}, {0x88c, 0xccc000c0},
	{0x890, 0x00000800}, {0x894, 0xfffffffe},
	{0x898, 0x40302010}, {0x89c, 0x00706050},
	{0x900, 0x00000000}, {0x904, 0x00000023},
	{0x908, 0x00000000}, {0x90c, 0x81121111},
	{0x910, 0x00000002}, {0x914, 0x00000201},
	{0xa00, 0x00d047c8}, {0xa04, 0x80ff800c},
	{0xa08, 0x8c838300}, {0xa0c, 0x2e7f120f},
	{0xa10, 0x9500bb78}, {0xa14, 0x1114d028},
	{0xa18, 0x00881117}, {0xa1c, 0x89140f00},
	{0xa20, 0x1a1b0000}, {0xa24, 0x090e1317},
	{0xa28, 0x00000204}, {0xa2c, 0x00d30000},
	{0xa70, 0x101fbf00}, {0xa74, 0x00000007},
	{0xa78, 0x00000900}, {0xa7c, 0x225b0606},
	{0xa80, 0x21806490}, {0xb2c, 0x00000000},
	{0xc00, 0x48071d40}, {0xc04, 0x03a05611},
	{0xc08, 0x000000e4}, {0xc0c, 0x6c6c6c6c},
	{0xc10, 0x08800000}, {0xc14, 0x40000100},
	{0xc18, 0x08800000}, {0xc1c, 0x40000100},
	{0xc20, 0x00000000}, {0xc24, 0x00000000},
	{0xc28, 0x00000000}, {0xc2c, 0x00000000},
	{0xc30, 0x69e9ac44}, {0xc34, 0x469652af},
	{0xc38, 0x49795994}, {0xc3c, 0x0a97971c},
	{0xc40, 0x1f7c403f}, {0xc44, 0x000100b7},
	{0xc48, 0xec020107}, {0xc4c, 0x007f037f},
	{0xc50, 0x69553420}, {0xc54, 0x43bc0094},
	{0xc58, 0x00013149}, {0xc5c, 0x00250492},
	{0xc60, 0x00000000}, {0xc64, 0x7112848b},
	{0xc68, 0x47c00bff}, {0xc6c, 0x00000036},
	{0xc70, 0x2c7f000d}, {0xc74, 0x020610db},
	{0xc78, 0x0000001f}, {0xc7c, 0x00b91612},
	{0xc80, 0x390000e4}, {0xc84, 0x20f60000},
	{0xc88, 0x40000100}, {0xc8c, 0x20200000},
	{0xc90, 0x00020e1a}, {0xc94, 0x00000000},
	{0xc98, 0x00020e1a}, {0xc9c, 0x00007f7f},
	{0xca0, 0x00000000}, {0xca4, 0x000300a0},
	{0xca8, 0x00000000}, {0xcac, 0x00000000},
	{0xcb0, 0x00000000}, {0xcb4, 0x00000000},
	{0xcb8, 0x00000000}, {0xcbc, 0x28000000},
	{0xcc0, 0x00000000}, {0xcc4, 0x00000000},
	{0xcc8, 0x00000000}, {0xccc, 0x00000000},
	{0xcd0, 0x00000000}, {0xcd4, 0x00000000},
	{0xcd8, 0x64b22427}, {0xcdc, 0x00766932},
	{0xce0, 0x00222222}, {0xce4, 0x00000000},
	{0xce8, 0x37644302}, {0xcec, 0x2f97d40c},
	{0xd00, 0x00000740}, {0xd04, 0x40020401},
	{0xd08, 0x0000907f}, {0xd0c, 0x20010201},
	{0xd10, 0xa0633333}, {0xd14, 0x3333bc53},
	{0xd18, 0x7a8f5b6f}, {0xd2c, 0xcc979975},
	{0xd30, 0x00000000}, {0xd34, 0x80608000},
	{0xd38, 0x00000000}, {0xd3c, 0x00127353},
	{0xd40, 0x00000000}, {0xd44, 0x00000000},
	{0xd48, 0x00000000}, {0xd4c, 0x00000000},
	{0xd50, 0x6437140a}, {0xd54, 0x00000000},
	{0xd58, 0x00000282}, {0xd5c, 0x30032064},
	{0xd60, 0x4653de68}, {0xd64, 0x04518a3c},
	{0xd68, 0x00002101}, {0xd6c, 0x2a201c16},
	{0xd70, 0x1812362e}, {0xd74, 0x322c2220},
	{0xd78, 0x000e3c24}, {0xe00, 0x2d2d2d2d},
	{0xe04, 0x2d2d2d2d}, {0xe08, 0x0390272d},
	{0xe10, 0x2d2d2d2d}, {0xe14, 0x2d2d2d2d},
	{0xe18, 0x2d2d2d2d}, {0xe1c, 0x2d2d2d2d},
	{0xe28, 0x00000000}, {0xe30, 0x1000dc1f},
	{0xe34, 0x10008c1f}, {0xe38, 0x02140102},
	{0xe3c, 0x681604c2}, {0xe40, 0x01007c00},
	{0xe44, 0x01004800}, {0xe48, 0xfb000000},
	{0xe4c, 0x000028d1}, {0xe50, 0x1000dc1f},
	{0xe54, 0x10008c1f}, {0xe58, 0x02140102},
	{0xe5c, 0x28160d05}, {0xe60, 0x00000008},
	{0xe68, 0x001b2556}, {0xe6c, 0x00c00096},
	{0xe70, 0x00c00096}, {0xe74, 0x01000056},
	{0xe78, 0x01000014}, {0xe7c, 0x01000056},
	{0xe80, 0x01000014}, {0xe84, 0x00c00096},
	{0xe88, 0x01000056}, {0xe8c, 0x00c00096},
	{0xed0, 0x00c00096}, {0xed4, 0x00c00096},
	{0xed8, 0x00c00096}, {0xedc, 0x000000d6},
	{0xee0, 0x000000d6}, {0xeec, 0x01c00016},
	{0xf14, 0x00000003}, {0xf4c, 0x00000000},
	{0xf00, 0x00000300},
	{0x820, 0x01000100}, {0x800, 0x83040000},
	{0xffff, 0xffffffff},
};

static const stwuct wtw8xxxu_weg32vaw wtw8xxx_agc_8723bu_tabwe[] = {
	{0xc78, 0xfd000001}, {0xc78, 0xfc010001},
	{0xc78, 0xfb020001}, {0xc78, 0xfa030001},
	{0xc78, 0xf9040001}, {0xc78, 0xf8050001},
	{0xc78, 0xf7060001}, {0xc78, 0xf6070001},
	{0xc78, 0xf5080001}, {0xc78, 0xf4090001},
	{0xc78, 0xf30a0001}, {0xc78, 0xf20b0001},
	{0xc78, 0xf10c0001}, {0xc78, 0xf00d0001},
	{0xc78, 0xef0e0001}, {0xc78, 0xee0f0001},
	{0xc78, 0xed100001}, {0xc78, 0xec110001},
	{0xc78, 0xeb120001}, {0xc78, 0xea130001},
	{0xc78, 0xe9140001}, {0xc78, 0xe8150001},
	{0xc78, 0xe7160001}, {0xc78, 0xe6170001},
	{0xc78, 0xe5180001}, {0xc78, 0xe4190001},
	{0xc78, 0xe31a0001}, {0xc78, 0xa51b0001},
	{0xc78, 0xa41c0001}, {0xc78, 0xa31d0001},
	{0xc78, 0x671e0001}, {0xc78, 0x661f0001},
	{0xc78, 0x65200001}, {0xc78, 0x64210001},
	{0xc78, 0x63220001}, {0xc78, 0x4a230001},
	{0xc78, 0x49240001}, {0xc78, 0x48250001},
	{0xc78, 0x47260001}, {0xc78, 0x46270001},
	{0xc78, 0x45280001}, {0xc78, 0x44290001},
	{0xc78, 0x432a0001}, {0xc78, 0x422b0001},
	{0xc78, 0x292c0001}, {0xc78, 0x282d0001},
	{0xc78, 0x272e0001}, {0xc78, 0x262f0001},
	{0xc78, 0x0a300001}, {0xc78, 0x09310001},
	{0xc78, 0x08320001}, {0xc78, 0x07330001},
	{0xc78, 0x06340001}, {0xc78, 0x05350001},
	{0xc78, 0x04360001}, {0xc78, 0x03370001},
	{0xc78, 0x02380001}, {0xc78, 0x01390001},
	{0xc78, 0x013a0001}, {0xc78, 0x013b0001},
	{0xc78, 0x013c0001}, {0xc78, 0x013d0001},
	{0xc78, 0x013e0001}, {0xc78, 0x013f0001},
	{0xc78, 0xfc400001}, {0xc78, 0xfb410001},
	{0xc78, 0xfa420001}, {0xc78, 0xf9430001},
	{0xc78, 0xf8440001}, {0xc78, 0xf7450001},
	{0xc78, 0xf6460001}, {0xc78, 0xf5470001},
	{0xc78, 0xf4480001}, {0xc78, 0xf3490001},
	{0xc78, 0xf24a0001}, {0xc78, 0xf14b0001},
	{0xc78, 0xf04c0001}, {0xc78, 0xef4d0001},
	{0xc78, 0xee4e0001}, {0xc78, 0xed4f0001},
	{0xc78, 0xec500001}, {0xc78, 0xeb510001},
	{0xc78, 0xea520001}, {0xc78, 0xe9530001},
	{0xc78, 0xe8540001}, {0xc78, 0xe7550001},
	{0xc78, 0xe6560001}, {0xc78, 0xe5570001},
	{0xc78, 0xe4580001}, {0xc78, 0xe3590001},
	{0xc78, 0xa65a0001}, {0xc78, 0xa55b0001},
	{0xc78, 0xa45c0001}, {0xc78, 0xa35d0001},
	{0xc78, 0x675e0001}, {0xc78, 0x665f0001},
	{0xc78, 0x65600001}, {0xc78, 0x64610001},
	{0xc78, 0x63620001}, {0xc78, 0x62630001},
	{0xc78, 0x61640001}, {0xc78, 0x48650001},
	{0xc78, 0x47660001}, {0xc78, 0x46670001},
	{0xc78, 0x45680001}, {0xc78, 0x44690001},
	{0xc78, 0x436a0001}, {0xc78, 0x426b0001},
	{0xc78, 0x286c0001}, {0xc78, 0x276d0001},
	{0xc78, 0x266e0001}, {0xc78, 0x256f0001},
	{0xc78, 0x24700001}, {0xc78, 0x09710001},
	{0xc78, 0x08720001}, {0xc78, 0x07730001},
	{0xc78, 0x06740001}, {0xc78, 0x05750001},
	{0xc78, 0x04760001}, {0xc78, 0x03770001},
	{0xc78, 0x02780001}, {0xc78, 0x01790001},
	{0xc78, 0x017a0001}, {0xc78, 0x017b0001},
	{0xc78, 0x017c0001}, {0xc78, 0x017d0001},
	{0xc78, 0x017e0001}, {0xc78, 0x017f0001},
	{0xc50, 0x69553422},
	{0xc50, 0x69553420},
	{0x824, 0x00390204},
	{0xffff, 0xffffffff}
};

static const stwuct wtw8xxxu_wfwegvaw wtw8723bu_wadioa_1t_init_tabwe[] = {
	{0x00, 0x00010000}, {0xb0, 0x000dffe0},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0xb1, 0x00000018},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0xb2, 0x00084c00},
	{0xb5, 0x0000d2cc}, {0xb6, 0x000925aa},
	{0xb7, 0x00000010}, {0xb8, 0x0000907f},
	{0x5c, 0x00000002}, {0x7c, 0x00000002},
	{0x7e, 0x00000005}, {0x8b, 0x0006fc00},
	{0xb0, 0x000ff9f0}, {0x1c, 0x000739d2},
	{0x1e, 0x00000000}, {0xdf, 0x00000780},
	{0x50, 0x00067435},
	/*
	 * The 8723bu vendow dwivew indicates that bit 8 shouwd be set in
	 * 0x51 fow package types TFBGA90, TFBGA80, and TFBGA79. Howevew
	 * they nevew actuawwy check the package type - and just defauwt
	 * to not setting it.
	 */
	{0x51, 0x0006b04e},
	{0x52, 0x000007d2}, {0x53, 0x00000000},
	{0x54, 0x00050400}, {0x55, 0x0004026e},
	{0xdd, 0x0000004c}, {0x70, 0x00067435},
	/*
	 * 0x71 has same package type condition as fow wegistew 0x51
	 */
	{0x71, 0x0006b04e},
	{0x72, 0x000007d2}, {0x73, 0x00000000},
	{0x74, 0x00050400}, {0x75, 0x0004026e},
	{0xef, 0x00000100}, {0x34, 0x0000add7},
	{0x35, 0x00005c00}, {0x34, 0x00009dd4},
	{0x35, 0x00005000}, {0x34, 0x00008dd1},
	{0x35, 0x00004400}, {0x34, 0x00007dce},
	{0x35, 0x00003800}, {0x34, 0x00006cd1},
	{0x35, 0x00004400}, {0x34, 0x00005cce},
	{0x35, 0x00003800}, {0x34, 0x000048ce},
	{0x35, 0x00004400}, {0x34, 0x000034ce},
	{0x35, 0x00003800}, {0x34, 0x00002451},
	{0x35, 0x00004400}, {0x34, 0x0000144e},
	{0x35, 0x00003800}, {0x34, 0x00000051},
	{0x35, 0x00004400}, {0xef, 0x00000000},
	{0xef, 0x00000100}, {0xed, 0x00000010},
	{0x44, 0x0000add7}, {0x44, 0x00009dd4},
	{0x44, 0x00008dd1}, {0x44, 0x00007dce},
	{0x44, 0x00006cc1}, {0x44, 0x00005cce},
	{0x44, 0x000044d1}, {0x44, 0x000034ce},
	{0x44, 0x00002451}, {0x44, 0x0000144e},
	{0x44, 0x00000051}, {0xef, 0x00000000},
	{0xed, 0x00000000}, {0x7f, 0x00020080},
	{0xef, 0x00002000}, {0x3b, 0x000380ef},
	{0x3b, 0x000302fe}, {0x3b, 0x00028ce6},
	{0x3b, 0x000200bc}, {0x3b, 0x000188a5},
	{0x3b, 0x00010fbc}, {0x3b, 0x00008f71},
	{0x3b, 0x00000900}, {0xef, 0x00000000},
	{0xed, 0x00000001}, {0x40, 0x000380ef},
	{0x40, 0x000302fe}, {0x40, 0x00028ce6},
	{0x40, 0x000200bc}, {0x40, 0x000188a5},
	{0x40, 0x00010fbc}, {0x40, 0x00008f71},
	{0x40, 0x00000900}, {0xed, 0x00000000},
	{0x82, 0x00080000}, {0x83, 0x00008000},
	{0x84, 0x00048d80}, {0x85, 0x00068000},
	{0xa2, 0x00080000}, {0xa3, 0x00008000},
	{0xa4, 0x00048d80}, {0xa5, 0x00068000},
	{0xed, 0x00000002}, {0xef, 0x00000002},
	{0x56, 0x00000032}, {0x76, 0x00000032},
	{0x01, 0x00000780},
	{0xff, 0xffffffff}
};

static int wtw8723bu_identify_chip(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	u32 vaw32, sys_cfg, vendow;
	int wet = 0;

	sys_cfg = wtw8xxxu_wead32(pwiv, WEG_SYS_CFG);
	pwiv->chip_cut = u32_get_bits(sys_cfg, SYS_CFG_CHIP_VEWSION_MASK);
	if (sys_cfg & SYS_CFG_TWP_VAUX_EN) {
		dev_info(dev, "Unsuppowted test chip\n");
		wet = -ENOTSUPP;
		goto out;
	}

	stwscpy(pwiv->chip_name, "8723BU", sizeof(pwiv->chip_name));
	pwiv->wtw_chip = WTW8723B;
	pwiv->wf_paths = 1;
	pwiv->wx_paths = 1;
	pwiv->tx_paths = 1;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_MUWTI_FUNC_CTWW);
	if (vaw32 & MUWTI_WIFI_FUNC_EN)
		pwiv->has_wifi = 1;
	if (vaw32 & MUWTI_BT_FUNC_EN)
		pwiv->has_bwuetooth = 1;
	if (vaw32 & MUWTI_GPS_FUNC_EN)
		pwiv->has_gps = 1;
	pwiv->is_muwti_func = 1;

	vendow = sys_cfg & SYS_CFG_VENDOW_EXT_MASK;
	wtw8xxxu_identify_vendow_2bits(pwiv, vendow);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_GPIO_OUTSTS);
	pwiv->wom_wev = u32_get_bits(vaw32, GPIO_WF_WW_ID);

	wtw8xxxu_config_endpoints_sie(pwiv);

	/*
	 * Fawwback fow devices that do not pwovide WEG_NOWMAW_SIE_EP_TX
	 */
	if (!pwiv->ep_tx_count)
		wet = wtw8xxxu_config_endpoints_no_sie(pwiv);

out:
	wetuwn wet;
}

static void wtw8723bu_wwite_btweg(stwuct wtw8xxxu_pwiv *pwiv, u8 weg, u8 data)
{
	stwuct h2c_cmd h2c;
	int weqnum = 0;

	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.bt_mp_opew.cmd = H2C_8723B_BT_MP_OPEW;
	h2c.bt_mp_opew.opewweq = 0 | (weqnum << 4);
	h2c.bt_mp_opew.opcode = BT_MP_OP_WWITE_WEG_VAWUE;
	h2c.bt_mp_opew.data = data;
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.bt_mp_opew));

	weqnum++;
	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.bt_mp_opew.cmd = H2C_8723B_BT_MP_OPEW;
	h2c.bt_mp_opew.opewweq = 0 | (weqnum << 4);
	h2c.bt_mp_opew.opcode = BT_MP_OP_WWITE_WEG_VAWUE;
	h2c.bt_mp_opew.addw = weg;
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.bt_mp_opew));
}

static void wtw8723bu_weset_8051(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 sys_func;

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WSV_CTWW);
	vaw8 &= ~BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_WSV_CTWW, vaw8);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WSV_CTWW + 1);
	vaw8 &= ~BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_WSV_CTWW + 1, vaw8);

	sys_func = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	sys_func &= ~SYS_FUNC_CPU_ENABWE;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, sys_func);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WSV_CTWW);
	vaw8 &= ~BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_WSV_CTWW, vaw8);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WSV_CTWW + 1);
	vaw8 |= BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_WSV_CTWW + 1, vaw8);

	sys_func |= SYS_FUNC_CPU_ENABWE;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, sys_func);
}

static void
wtw8723b_set_tx_powew(stwuct wtw8xxxu_pwiv *pwiv, int channew, boow ht40)
{
	u32 vaw32, ofdm, mcs;
	u8 cck, ofdmbase, mcsbase;
	int gwoup, tx_idx;

	tx_idx = 0;
	gwoup = wtw8xxxu_gen2_channew_to_gwoup(channew);

	cck = pwiv->cck_tx_powew_index_B[gwoup];
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_A_CCK1_MCS32);
	vaw32 &= 0xffff00ff;
	vaw32 |= (cck << 8);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_CCK1_MCS32, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11);
	vaw32 &= 0xff;
	vaw32 |= ((cck << 8) | (cck << 16) | (cck << 24));
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11, vaw32);

	ofdmbase = pwiv->ht40_1s_tx_powew_index_B[gwoup];
	ofdmbase += pwiv->ofdm_tx_powew_diff[tx_idx].b;
	ofdm = ofdmbase | ofdmbase << 8 | ofdmbase << 16 | ofdmbase << 24;

	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_WATE18_06, ofdm);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_WATE54_24, ofdm);

	mcsbase = pwiv->ht40_1s_tx_powew_index_B[gwoup];
	if (ht40)
		mcsbase += pwiv->ht40_tx_powew_diff[tx_idx++].b;
	ewse
		mcsbase += pwiv->ht20_tx_powew_diff[tx_idx++].b;
	mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS03_MCS00, mcs);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS07_MCS04, mcs);
}

static int wtw8723bu_pawse_efuse(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct wtw8723bu_efuse *efuse = &pwiv->efuse_wifi.efuse8723bu;
	int i;

	if (efuse->wtw_id != cpu_to_we16(0x8129))
		wetuwn -EINVAW;

	ethew_addw_copy(pwiv->mac_addw, efuse->mac_addw);

	memcpy(pwiv->cck_tx_powew_index_A, efuse->tx_powew_index_A.cck_base,
	       sizeof(efuse->tx_powew_index_A.cck_base));
	memcpy(pwiv->cck_tx_powew_index_B, efuse->tx_powew_index_B.cck_base,
	       sizeof(efuse->tx_powew_index_B.cck_base));

	memcpy(pwiv->ht40_1s_tx_powew_index_A,
	       efuse->tx_powew_index_A.ht40_base,
	       sizeof(efuse->tx_powew_index_A.ht40_base));
	memcpy(pwiv->ht40_1s_tx_powew_index_B,
	       efuse->tx_powew_index_B.ht40_base,
	       sizeof(efuse->tx_powew_index_B.ht40_base));

	pwiv->ofdm_tx_powew_diff[0].a =
		efuse->tx_powew_index_A.ht20_ofdm_1s_diff.a;
	pwiv->ofdm_tx_powew_diff[0].b =
		efuse->tx_powew_index_B.ht20_ofdm_1s_diff.a;

	pwiv->ht20_tx_powew_diff[0].a =
		efuse->tx_powew_index_A.ht20_ofdm_1s_diff.b;
	pwiv->ht20_tx_powew_diff[0].b =
		efuse->tx_powew_index_B.ht20_ofdm_1s_diff.b;

	pwiv->ht40_tx_powew_diff[0].a = 0;
	pwiv->ht40_tx_powew_diff[0].b = 0;

	fow (i = 1; i < WTW8723B_TX_COUNT; i++) {
		pwiv->ofdm_tx_powew_diff[i].a =
			efuse->tx_powew_index_A.pww_diff[i - 1].ofdm;
		pwiv->ofdm_tx_powew_diff[i].b =
			efuse->tx_powew_index_B.pww_diff[i - 1].ofdm;

		pwiv->ht20_tx_powew_diff[i].a =
			efuse->tx_powew_index_A.pww_diff[i - 1].ht20;
		pwiv->ht20_tx_powew_diff[i].b =
			efuse->tx_powew_index_B.pww_diff[i - 1].ht20;

		pwiv->ht40_tx_powew_diff[i].a =
			efuse->tx_powew_index_A.pww_diff[i - 1].ht40;
		pwiv->ht40_tx_powew_diff[i].b =
			efuse->tx_powew_index_B.pww_diff[i - 1].ht40;
	}

	pwiv->defauwt_cwystaw_cap = pwiv->efuse_wifi.efuse8723bu.xtaw_k & 0x3f;

	wetuwn 0;
}

static int wtw8723bu_woad_fiwmwawe(stwuct wtw8xxxu_pwiv *pwiv)
{
	const chaw *fw_name;
	int wet;

	if (pwiv->enabwe_bwuetooth)
		fw_name = "wtwwifi/wtw8723bu_bt.bin";
	ewse
		fw_name = "wtwwifi/wtw8723bu_nic.bin";

	wet = wtw8xxxu_woad_fiwmwawe(pwiv, fw_name);
	wetuwn wet;
}

static void wtw8723bu_init_phy_bb(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 |= SYS_FUNC_BB_GWB_WSTN | SYS_FUNC_BBWSTB | SYS_FUNC_DIO_WF;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);

	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00);

	/* 6. 0x1f[7:0] = 0x07 */
	vaw8 = WF_ENABWE | WF_WSTB | WF_SDMWSTB;
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, vaw8);

	/* Why? */
	wtw8xxxu_wwite8(pwiv, WEG_SYS_FUNC, 0xe3);
	wtw8xxxu_wwite8(pwiv, WEG_AFE_XTAW_CTWW + 1, 0x80);
	wtw8xxxu_init_phy_wegs(pwiv, wtw8723b_phy_1t_init_tabwe);

	wtw8xxxu_init_phy_wegs(pwiv, wtw8xxx_agc_8723bu_tabwe);
}

static int wtw8723bu_init_phy_wf(stwuct wtw8xxxu_pwiv *pwiv)
{
	int wet;

	wet = wtw8xxxu_init_phy_wf(pwiv, wtw8723bu_wadioa_1t_init_tabwe, WF_A);
	/*
	 * PHY WCK
	 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, 0xb0, 0xdfbe0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_MODE_AG, 0x8c01);
	msweep(200);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, 0xb0, 0xdffe0);

	wetuwn wet;
}

void wtw8723bu_phy_init_antenna_sewection(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 vaw32;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_PAD_CTWW1);
	vaw32 &= ~(BIT(20) | BIT(24));
	wtw8xxxu_wwite32(pwiv, WEG_PAD_CTWW1, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_GPIO_MUXCFG);
	vaw32 &= ~BIT(4);
	wtw8xxxu_wwite32(pwiv, WEG_GPIO_MUXCFG, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_GPIO_MUXCFG);
	vaw32 |= BIT(3);
	wtw8xxxu_wwite32(pwiv, WEG_GPIO_MUXCFG, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WEDCFG0);
	vaw32 |= BIT(24);
	wtw8xxxu_wwite32(pwiv, WEG_WEDCFG0, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WEDCFG0);
	vaw32 &= ~BIT(23);
	wtw8xxxu_wwite32(pwiv, WEG_WEDCFG0, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WFE_BUFFEW);
	vaw32 |= (BIT(0) | BIT(1));
	wtw8xxxu_wwite32(pwiv, WEG_WFE_BUFFEW, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WFE_CTWW_ANTA_SWC);
	vaw32 &= 0xffffff00;
	vaw32 |= 0x77;
	wtw8xxxu_wwite32(pwiv, WEG_WFE_CTWW_ANTA_SWC, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_PWW_DATA);
	vaw32 |= PWW_DATA_EEPWPAD_WFE_CTWW_EN;
	wtw8xxxu_wwite32(pwiv, WEG_PWW_DATA, vaw32);
}

static int wtw8723bu_iqk_path_a(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_eac, weg_e94, weg_e9c, path_sew, vaw32;
	int wesuwt = 0;

	path_sew = wtw8xxxu_wead32(pwiv, WEG_S0S1_PATH_SWITCH);

	/*
	 * Weave IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/*
	 * Enabwe path A PA in TX IQK mode
	 */
	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT);
	vaw32 |= 0x80000;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, vaw32);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x20000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0003f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xc7f87);

	/*
	 * Tx IQK setting
	 */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* path-A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x821403ea);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x28110000);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_B, 0x82110000);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_B, 0x28110000);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x00462911);

	/*
	 * Entew IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	vaw32 |= 0x80800000;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/*
	 * The vendow dwivew indicates the USB moduwe is awways using
	 * S0S1 path 1 fow the 8723bu. This may be diffewent fow 8192eu
	 */
	if (pwiv->wf_paths > 1)
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000000);
	ewse
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Bit 12 seems to be BT_GWANT, and is onwy found in the 8723bu.
	 * No twace of this in the 8192eu ow 8188eu vendow dwivews.
	 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00000800);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(1);

	/* Westowe Ant Path */
	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, path_sew);
#ifdef WTW8723BU_BT
	/* GNT_BT = 1 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00001800);
#endif

	/*
	 * Weave IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_e94 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_A);
	weg_e9c = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_A);

	vaw32 = (weg_e9c >> 16) & 0x3ff;
	if (vaw32 & 0x200)
		vaw32 = 0x400 - vaw32;

	if (!(weg_eac & BIT(28)) &&
	    ((weg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((weg_e9c & 0x03ff0000) != 0x00420000) &&
	    ((weg_e94 & 0x03ff0000)  < 0x01100000) &&
	    ((weg_e94 & 0x03ff0000)  > 0x00f00000) &&
	    vaw32 < 0xf)
		wesuwt |= 0x01;
	ewse	/* If TX not OK, ignowe WX */
		goto out;

out:
	wetuwn wesuwt;
}

static int wtw8723bu_wx_iqk_path_a(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_ea4, weg_eac, weg_e94, weg_e9c, path_sew, vaw32;
	int wesuwt = 0;

	path_sew = wtw8xxxu_wead32(pwiv, WEG_S0S1_PATH_SWITCH);

	/*
	 * Weave IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/*
	 * Enabwe path A PA in TX IQK mode
	 */
	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT);
	vaw32 |= 0x80000;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, vaw32);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0001f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf7fb7);

	/*
	 * Tx IQK setting
	 */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* path-A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x82160ff0);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x28110000);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_B, 0x82110000);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_B, 0x28110000);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a911);

	/*
	 * Entew IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	vaw32 |= 0x80800000;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/*
	 * The vendow dwivew indicates the USB moduwe is awways using
	 * S0S1 path 1 fow the 8723bu. This may be diffewent fow 8192eu
	 */
	if (pwiv->wf_paths > 1)
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000000);
	ewse
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Bit 12 seems to be BT_GWANT, and is onwy found in the 8723bu.
	 * No twace of this in the 8192eu ow 8188eu vendow dwivews.
	 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00000800);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(1);

	/* Westowe Ant Path */
	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, path_sew);
#ifdef WTW8723BU_BT
	/* GNT_BT = 1 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00001800);
#endif

	/*
	 * Weave IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_e94 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_A);
	weg_e9c = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_A);

	vaw32 = (weg_e9c >> 16) & 0x3ff;
	if (vaw32 & 0x200)
		vaw32 = 0x400 - vaw32;

	if (!(weg_eac & BIT(28)) &&
	    ((weg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((weg_e9c & 0x03ff0000) != 0x00420000) &&
	    ((weg_e94 & 0x03ff0000)  < 0x01100000) &&
	    ((weg_e94 & 0x03ff0000)  > 0x00f00000) &&
	    vaw32 < 0xf)
		wesuwt |= 0x01;
	ewse	/* If TX not OK, ignowe WX */
		goto out;

	vaw32 = 0x80007c00 | (weg_e94 &0x3ff0000) |
		((weg_e9c & 0x3ff0000) >> 16);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, vaw32);

	/*
	 * Modify WX IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);
	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT);
	vaw32 |= 0x80000;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, vaw32);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0001f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf7d77);

	/*
	 * PA, PAD setting
	 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0xf80);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_55, 0x4021f);

	/*
	 * WX IQK setting
	 */
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* path-A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x82110000);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x2816001f);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_B, 0x82110000);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_B, 0x28110000);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a8d1);

	/*
	 * Entew IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	vaw32 |= 0x80800000;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	if (pwiv->wf_paths > 1)
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000000);
	ewse
		wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00000280);

	/*
	 * Disabwe BT
	 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00000800);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(1);

	/* Westowe Ant Path */
	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, path_sew);
#ifdef WTW8723BU_BT
	/* GNT_BT = 1 */
	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, 0x00001800);
#endif

	/*
	 * Weave IQK mode
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_ea4 = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_BEFOWE_IQK_A_2);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x780);

	vaw32 = (weg_eac >> 16) & 0x3ff;
	if (vaw32 & 0x200)
		vaw32 = 0x400 - vaw32;

	if (!(weg_eac & BIT(27)) &&
	    ((weg_ea4 & 0x03ff0000) != 0x01320000) &&
	    ((weg_eac & 0x03ff0000) != 0x00360000) &&
	    ((weg_ea4 & 0x03ff0000)  < 0x01100000) &&
	    ((weg_ea4 & 0x03ff0000)  > 0x00f00000) &&
	    vaw32 < 0xf)
		wesuwt |= 0x02;
	ewse	/* If TX not OK, ignowe WX */
		goto out;
out:
	wetuwn wesuwt;
}

static void wtw8723bu_phy_iqcawibwate(stwuct wtw8xxxu_pwiv *pwiv,
				      int wesuwt[][8], int t)
{
	stwuct device *dev = &pwiv->udev->dev;
	u32 i, vaw32;
	int path_a_ok /*, path_b_ok */;
	int wetwy = 2;
	static const u32 adda_wegs[WTW8XXXU_ADDA_WEGS] = {
		WEG_FPGA0_XCD_SWITCH_CTWW, WEG_BWUETOOTH,
		WEG_WX_WAIT_CCA, WEG_TX_CCK_WFON,
		WEG_TX_CCK_BBON, WEG_TX_OFDM_WFON,
		WEG_TX_OFDM_BBON, WEG_TX_TO_WX,
		WEG_TX_TO_TX, WEG_WX_CCK,
		WEG_WX_OFDM, WEG_WX_WAIT_WIFS,
		WEG_WX_TO_WX, WEG_STANDBY,
		WEG_SWEEP, WEG_PMPD_ANAEN
	};
	static const u32 iqk_mac_wegs[WTW8XXXU_MAC_WEGS] = {
		WEG_TXPAUSE, WEG_BEACON_CTWW,
		WEG_BEACON_CTWW_1, WEG_GPIO_MUXCFG
	};
	static const u32 iqk_bb_wegs[WTW8XXXU_BB_WEGS] = {
		WEG_OFDM0_TWX_PATH_ENABWE, WEG_OFDM0_TW_MUX_PAW,
		WEG_FPGA0_XCD_WF_SW_CTWW, WEG_CONFIG_ANT_A, WEG_CONFIG_ANT_B,
		WEG_FPGA0_XAB_WF_SW_CTWW, WEG_FPGA0_XA_WF_INT_OE,
		WEG_FPGA0_XB_WF_INT_OE, WEG_FPGA0_WF_MODE
	};
	u8 xa_agc = wtw8xxxu_wead32(pwiv, WEG_OFDM0_XA_AGC_COWE1) & 0xff;
	u8 xb_agc = wtw8xxxu_wead32(pwiv, WEG_OFDM0_XB_AGC_COWE1) & 0xff;

	/*
	 * Note: IQ cawibwation must be pewfowmed aftew woading
	 *       PHY_WEG.txt , and wadio_a, wadio_b.txt
	 */

	if (t == 0) {
		/* Save ADDA pawametews, tuwn Path A ADDA on */
		wtw8xxxu_save_wegs(pwiv, adda_wegs, pwiv->adda_backup,
				   WTW8XXXU_ADDA_WEGS);
		wtw8xxxu_save_mac_wegs(pwiv, iqk_mac_wegs, pwiv->mac_backup);
		wtw8xxxu_save_wegs(pwiv, iqk_bb_wegs,
				   pwiv->bb_backup, WTW8XXXU_BB_WEGS);
	}

	wtw8xxxu_path_adda_on(pwiv, adda_wegs, twue);

	/* MAC settings */
	wtw8xxxu_mac_cawibwation(pwiv, iqk_mac_wegs, pwiv->mac_backup);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_CCK0_AFE_SETTING);
	vaw32 |= 0x0f000000;
	wtw8xxxu_wwite32(pwiv, WEG_CCK0_AFE_SETTING, vaw32);

	wtw8xxxu_wwite32(pwiv, WEG_OFDM0_TWX_PATH_ENABWE, 0x03a05600);
	wtw8xxxu_wwite32(pwiv, WEG_OFDM0_TW_MUX_PAW, 0x000800e4);
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_XCD_WF_SW_CTWW, 0x22204000);

	/*
	 * WX IQ cawibwation setting fow 8723B D cut wawge cuwwent issue
	 * when weaving IPS
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT);
	vaw32 |= 0x80000;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, vaw32);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0001f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf7fb7);

	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_ED);
	vaw32 |= 0x20;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_ED, vaw32);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_43, 0x60fbd);

	fow (i = 0; i < wetwy; i++) {
		path_a_ok = wtw8723bu_iqk_path_a(pwiv);
		if (path_a_ok == 0x01) {
			vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
			vaw32 &= 0x000000ff;
			wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

			vaw32 = wtw8xxxu_wead32(pwiv,
						WEG_TX_POWEW_BEFOWE_IQK_A);
			wesuwt[t][0] = (vaw32 >> 16) & 0x3ff;
			vaw32 = wtw8xxxu_wead32(pwiv,
						WEG_TX_POWEW_AFTEW_IQK_A);
			wesuwt[t][1] = (vaw32 >> 16) & 0x3ff;

			bweak;
		}
	}

	if (!path_a_ok)
		dev_dbg(dev, "%s: Path A TX IQK faiwed!\n", __func__);

	fow (i = 0; i < wetwy; i++) {
		path_a_ok = wtw8723bu_wx_iqk_path_a(pwiv);
		if (path_a_ok == 0x03) {
			vaw32 = wtw8xxxu_wead32(pwiv,
						WEG_WX_POWEW_BEFOWE_IQK_A_2);
			wesuwt[t][2] = (vaw32 >> 16) & 0x3ff;
			vaw32 = wtw8xxxu_wead32(pwiv,
						WEG_WX_POWEW_AFTEW_IQK_A_2);
			wesuwt[t][3] = (vaw32 >> 16) & 0x3ff;

			bweak;
		}
	}

	if (!path_a_ok)
		dev_dbg(dev, "%s: Path A WX IQK faiwed!\n", __func__);

	if (pwiv->tx_paths > 1) {
#if 1
		dev_wawn(dev, "%s: Path B not suppowted\n", __func__);
#ewse

		/*
		 * Path A into standby
		 */
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
		vaw32 &= 0x000000ff;
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);
		wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_AC, 0x10000);

		vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
		vaw32 &= 0x000000ff;
		vaw32 |= 0x80800000;
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

		/* Tuwn Path B ADDA on */
		wtw8xxxu_path_adda_on(pwiv, adda_wegs, fawse);

		fow (i = 0; i < wetwy; i++) {
			path_b_ok = wtw8xxxu_iqk_path_b(pwiv);
			if (path_b_ok == 0x03) {
				vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_B);
				wesuwt[t][4] = (vaw32 >> 16) & 0x3ff;
				vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_B);
				wesuwt[t][5] = (vaw32 >> 16) & 0x3ff;
				bweak;
			}
		}

		if (!path_b_ok)
			dev_dbg(dev, "%s: Path B IQK faiwed!\n", __func__);

		fow (i = 0; i < wetwy; i++) {
			path_b_ok = wtw8723bu_wx_iqk_path_b(pwiv);
			if (path_a_ok == 0x03) {
				vaw32 = wtw8xxxu_wead32(pwiv,
							WEG_WX_POWEW_BEFOWE_IQK_B_2);
				wesuwt[t][6] = (vaw32 >> 16) & 0x3ff;
				vaw32 = wtw8xxxu_wead32(pwiv,
							WEG_WX_POWEW_AFTEW_IQK_B_2);
				wesuwt[t][7] = (vaw32 >> 16) & 0x3ff;
				bweak;
			}
		}

		if (!path_b_ok)
			dev_dbg(dev, "%s: Path B WX IQK faiwed!\n", __func__);
#endif
	}

	/* Back to BB mode, woad owiginaw vawue */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 &= 0x000000ff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);

	if (t) {
		/* Wewoad ADDA powew saving pawametews */
		wtw8xxxu_westowe_wegs(pwiv, adda_wegs, pwiv->adda_backup,
				      WTW8XXXU_ADDA_WEGS);

		/* Wewoad MAC pawametews */
		wtw8xxxu_westowe_mac_wegs(pwiv, iqk_mac_wegs, pwiv->mac_backup);

		/* Wewoad BB pawametews */
		wtw8xxxu_westowe_wegs(pwiv, iqk_bb_wegs,
				      pwiv->bb_backup, WTW8XXXU_BB_WEGS);

		/* Westowe WX initiaw gain */
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_OFDM0_XA_AGC_COWE1);
		vaw32 &= 0xffffff00;
		wtw8xxxu_wwite32(pwiv, WEG_OFDM0_XA_AGC_COWE1, vaw32 | 0x50);
		wtw8xxxu_wwite32(pwiv, WEG_OFDM0_XA_AGC_COWE1, vaw32 | xa_agc);

		if (pwiv->tx_paths > 1) {
			vaw32 = wtw8xxxu_wead32(pwiv, WEG_OFDM0_XB_AGC_COWE1);
			vaw32 &= 0xffffff00;
			wtw8xxxu_wwite32(pwiv, WEG_OFDM0_XB_AGC_COWE1,
					 vaw32 | 0x50);
			wtw8xxxu_wwite32(pwiv, WEG_OFDM0_XB_AGC_COWE1,
					 vaw32 | xb_agc);
		}

		/* Woad 0xe30 IQC defauwt vawue */
		wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x01008c00);
		wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x01008c00);
	}
}

static void wtw8723bu_phy_iq_cawibwate(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	int wesuwt[4][8];	/* wast is finaw wesuwt */
	int i, candidate;
	boow path_a_ok, path_b_ok;
	u32 weg_e94, weg_e9c, weg_ea4, weg_eac;
	u32 weg_eb4, weg_ebc, weg_ec4, weg_ecc;
	u32 vaw32, bt_contwow;
	s32 weg_tmp = 0;
	boow simu;

	wtw8xxxu_gen2_pwepawe_cawibwate(pwiv, 1);

	memset(wesuwt, 0, sizeof(wesuwt));
	candidate = -1;

	path_a_ok = fawse;
	path_b_ok = fawse;

	bt_contwow = wtw8xxxu_wead32(pwiv, WEG_BT_CONTWOW_8723BU);

	fow (i = 0; i < 3; i++) {
		wtw8723bu_phy_iqcawibwate(pwiv, wesuwt, i);

		if (i == 1) {
			simu = wtw8xxxu_gen2_simuwawity_compawe(pwiv,
								wesuwt, 0, 1);
			if (simu) {
				candidate = 0;
				bweak;
			}
		}

		if (i == 2) {
			simu = wtw8xxxu_gen2_simuwawity_compawe(pwiv,
								wesuwt, 0, 2);
			if (simu) {
				candidate = 0;
				bweak;
			}

			simu = wtw8xxxu_gen2_simuwawity_compawe(pwiv,
								wesuwt, 1, 2);
			if (simu) {
				candidate = 1;
			} ewse {
				fow (i = 0; i < 8; i++)
					weg_tmp += wesuwt[3][i];

				if (weg_tmp)
					candidate = 3;
				ewse
					candidate = -1;
			}
		}
	}

	fow (i = 0; i < 4; i++) {
		weg_e94 = wesuwt[i][0];
		weg_e9c = wesuwt[i][1];
		weg_ea4 = wesuwt[i][2];
		weg_eac = wesuwt[i][3];
		weg_eb4 = wesuwt[i][4];
		weg_ebc = wesuwt[i][5];
		weg_ec4 = wesuwt[i][6];
		weg_ecc = wesuwt[i][7];
	}

	if (candidate >= 0) {
		weg_e94 = wesuwt[candidate][0];
		pwiv->wege94 =  weg_e94;
		weg_e9c = wesuwt[candidate][1];
		pwiv->wege9c = weg_e9c;
		weg_ea4 = wesuwt[candidate][2];
		weg_eac = wesuwt[candidate][3];
		weg_eb4 = wesuwt[candidate][4];
		pwiv->wegeb4 = weg_eb4;
		weg_ebc = wesuwt[candidate][5];
		pwiv->wegebc = weg_ebc;
		weg_ec4 = wesuwt[candidate][6];
		weg_ecc = wesuwt[candidate][7];
		dev_dbg(dev, "%s: candidate is %x\n", __func__, candidate);
		dev_dbg(dev,
			"%s: e94 =%x e9c=%x ea4=%x eac=%x eb4=%x ebc=%x ec4=%x ecc=%x\n",
			__func__, weg_e94, weg_e9c,
			weg_ea4, weg_eac, weg_eb4, weg_ebc, weg_ec4, weg_ecc);
		path_a_ok = twue;
		path_b_ok = twue;
	} ewse {
		weg_e94 = weg_eb4 = pwiv->wege94 = pwiv->wegeb4 = 0x100;
		weg_e9c = weg_ebc = pwiv->wege9c = pwiv->wegebc = 0x0;
	}

	if (weg_e94 && candidate >= 0)
		wtw8xxxu_fiww_iqk_matwix_a(pwiv, path_a_ok, wesuwt,
					   candidate, (weg_ea4 == 0));

	if (pwiv->tx_paths > 1 && weg_eb4)
		wtw8xxxu_fiww_iqk_matwix_b(pwiv, path_b_ok, wesuwt,
					   candidate, (weg_ec4 == 0));

	wtw8xxxu_save_wegs(pwiv, wtw8xxxu_iqk_phy_iq_bb_weg,
			   pwiv->bb_wecovewy_backup, WTW8XXXU_BB_WEGS);

	wtw8xxxu_wwite32(pwiv, WEG_BT_CONTWOW_8723BU, bt_contwow);

	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT);
	vaw32 |= 0x80000;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, vaw32);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x18000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0001f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xe6177);
	vaw32 = wtw8xxxu_wead_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_ED);
	vaw32 |= 0x20;
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_UNKNOWN_ED, vaw32);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, 0x43, 0x300bd);

	if (pwiv->wf_paths > 1)
		dev_dbg(dev, "%s: 8723BU 2T not suppowted\n", __func__);

	wtw8xxxu_gen2_pwepawe_cawibwate(pwiv, 0);
}

static int wtw8723bu_active_to_emu(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;
	u32 vaw32;
	int count, wet = 0;

	/* Tuwn off WF */
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, 0);

	/* Enabwe wising edge twiggewing intewwupt */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_GPIO_INTM);
	vaw16 &= ~GPIO_INTM_EDGE_TWIG_IWQ;
	wtw8xxxu_wwite16(pwiv, WEG_GPIO_INTM, vaw16);

	/* Wewease WWON weset 0x04[16]= 1*/
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 |= APS_FSMCO_WWON_WESET;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	/* 0x0005[1] = 1 tuwn off MAC by HW state machine*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 |= BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	fow (count = WTW8XXXU_MAX_WEG_POWW; count; count--) {
		vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
		if ((vaw8 & BIT(1)) == 0)
			bweak;
		udeway(10);
	}

	if (!count) {
		dev_wawn(&pwiv->udev->dev, "%s: Disabwing MAC timed out\n",
			 __func__);
		wet = -EBUSY;
		goto exit;
	}

	/* Enabwe BT contwow XTAW setting */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_AFE_MISC);
	vaw8 &= ~AFE_MISC_WW_XTAW_CTWW;
	wtw8xxxu_wwite8(pwiv, WEG_AFE_MISC, vaw8);

	/* 0x0000[5] = 1 anawog Ips to digitaw, 1:isowation */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_SYS_ISO_CTWW);
	vaw8 |= SYS_ISO_ANAWOG_IPS;
	wtw8xxxu_wwite8(pwiv, WEG_SYS_ISO_CTWW, vaw8);

	/* 0x0020[0] = 0 disabwe WDOA12 MACWO bwock*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WDOA15_CTWW);
	vaw8 &= ~WDOA15_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_WDOA15_CTWW, vaw8);

exit:
	wetuwn wet;
}

static int wtw8723b_emu_to_active(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u32 vaw32;
	int count, wet = 0;

	/* 0x20[0] = 1 enabwe WDOA12 MACWO bwock fow aww intewface */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WDOA15_CTWW);
	vaw8 |= WDOA15_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_WDOA15_CTWW, vaw8);

	/* 0x67[0] = 0 to disabwe BT_GPS_SEW pins*/
	vaw8 = wtw8xxxu_wead8(pwiv, 0x0067);
	vaw8 &= ~BIT(4);
	wtw8xxxu_wwite8(pwiv, 0x0067, vaw8);

	mdeway(1);

	/* 0x00[5] = 0 wewease anawog Ips to digitaw, 1:isowation */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_SYS_ISO_CTWW);
	vaw8 &= ~SYS_ISO_ANAWOG_IPS;
	wtw8xxxu_wwite8(pwiv, WEG_SYS_ISO_CTWW, vaw8);

	/* Disabwe SW WPS 0x04[10]= 0 */
	vaw32 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO);
	vaw32 &= ~APS_FSMCO_SW_WPS;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	/* Wait untiw 0x04[17] = 1 powew weady */
	fow (count = WTW8XXXU_MAX_WEG_POWW; count; count--) {
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
		if (vaw32 & BIT(17))
			bweak;

		udeway(10);
	}

	if (!count) {
		wet = -EBUSY;
		goto exit;
	}

	/* We shouwd be abwe to optimize the fowwowing thwee entwies into one */

	/* Wewease WWON weset 0x04[16]= 1*/
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 |= APS_FSMCO_WWON_WESET;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	/* Disabwe HWPDN 0x04[15]= 0*/
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 &= ~APS_FSMCO_HW_POWEWDOWN;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	/* Disabwe WW suspend*/
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 &= ~(APS_FSMCO_HW_SUSPEND | APS_FSMCO_PCIE);
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	/* Set, then poww untiw 0 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
	vaw32 |= APS_FSMCO_MAC_ENABWE;
	wtw8xxxu_wwite32(pwiv, WEG_APS_FSMCO, vaw32);

	fow (count = WTW8XXXU_MAX_WEG_POWW; count; count--) {
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_APS_FSMCO);
		if ((vaw32 & APS_FSMCO_MAC_ENABWE) == 0) {
			wet = 0;
			bweak;
		}
		udeway(10);
	}

	if (!count) {
		wet = -EBUSY;
		goto exit;
	}

	/* Enabwe WW contwow XTAW setting */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_AFE_MISC);
	vaw8 |= AFE_MISC_WW_XTAW_CTWW;
	wtw8xxxu_wwite8(pwiv, WEG_AFE_MISC, vaw8);

	/* Enabwe fawwing edge twiggewing intewwupt */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_INTM + 1);
	vaw8 |= BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_INTM + 1, vaw8);

	/* Enabwe GPIO9 intewwupt mode */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_IO_SEW_2 + 1);
	vaw8 |= BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_IO_SEW_2 + 1, vaw8);

	/* Enabwe GPIO9 input mode */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_IO_SEW_2);
	vaw8 &= ~BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_IO_SEW_2, vaw8);

	/* Enabwe HSISW GPIO[C:0] intewwupt */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_HSIMW);
	vaw8 |= BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_HSIMW, vaw8);

	/* Enabwe HSISW GPIO9 intewwupt */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_HSIMW + 2);
	vaw8 |= BIT(1);
	wtw8xxxu_wwite8(pwiv, WEG_HSIMW + 2, vaw8);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_MUWTI_FUNC_CTWW);
	vaw8 |= MUWTI_WIFI_HW_WOF_EN;
	wtw8xxxu_wwite8(pwiv, WEG_MUWTI_FUNC_CTWW, vaw8);

	/* Fow GPIO9 intewnaw puww high setting BIT(14) */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_MUWTI_FUNC_CTWW + 1);
	vaw8 |= BIT(6);
	wtw8xxxu_wwite8(pwiv, WEG_MUWTI_FUNC_CTWW + 1, vaw8);

exit:
	wetuwn wet;
}

static int wtw8723bu_powew_on(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;
	u32 vaw32;
	int wet;

	wtw8xxxu_disabwed_to_emu(pwiv);

	wet = wtw8723b_emu_to_active(pwiv);
	if (wet)
		goto exit;

	/*
	 * Enabwe MAC DMA/WMAC/SCHEDUWE/SEC bwock
	 * Set CW bit10 to enabwe 32k cawibwation.
	 */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_CW);
	vaw16 |= (CW_HCI_TXDMA_ENABWE | CW_HCI_WXDMA_ENABWE |
		  CW_TXDMA_ENABWE | CW_WXDMA_ENABWE |
		  CW_PWOTOCOW_ENABWE | CW_SCHEDUWE_ENABWE |
		  CW_MAC_TX_ENABWE | CW_MAC_WX_ENABWE |
		  CW_SECUWITY_ENABWE | CW_CAWTIMEW_ENABWE);
	wtw8xxxu_wwite16(pwiv, WEG_CW, vaw16);

	/*
	 * BT coexist powew on settings. This is identicaw fow 1 and 2
	 * antenna pawts.
	 */
	wtw8xxxu_wwite8(pwiv, WEG_PAD_CTWW1 + 3, 0x20);

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 |= SYS_FUNC_BBWSTB | SYS_FUNC_BB_GWB_WSTN;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);

	wtw8xxxu_wwite8(pwiv, WEG_BT_CONTWOW_8723BU + 1, 0x18);
	wtw8xxxu_wwite8(pwiv, WEG_WWAN_ACT_CONTWOW_8723B, 0x04);
	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x00);
	/* Antenna invewse */
	wtw8xxxu_wwite8(pwiv, 0xfe08, 0x01);

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_PWW_DATA);
	vaw16 |= PWW_DATA_EEPWPAD_WFE_CTWW_EN;
	wtw8xxxu_wwite16(pwiv, WEG_PWW_DATA, vaw16);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WEDCFG0);
	vaw32 |= WEDCFG0_DPDT_SEWECT;
	wtw8xxxu_wwite32(pwiv, WEG_WEDCFG0, vaw32);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_PAD_CTWW1);
	vaw8 &= ~PAD_CTWW1_SW_DPDT_SEW_DATA;
	wtw8xxxu_wwite8(pwiv, WEG_PAD_CTWW1, vaw8);
exit:
	wetuwn wet;
}

static void wtw8723bu_powew_off(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;

	wtw8xxxu_fwush_fifo(pwiv);

	/*
	 * Disabwe TX wepowt timew
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_TX_WEPOWT_CTWW);
	vaw8 &= ~TX_WEPOWT_CTWW_TIMEW_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_TX_WEPOWT_CTWW, vaw8);

	wtw8xxxu_wwite8(pwiv, WEG_CW, 0x0000);

	wtw8xxxu_active_to_wps(pwiv);

	/* Weset Fiwmwawe if wunning in WAM */
	if (wtw8xxxu_wead8(pwiv, WEG_MCU_FW_DW) & MCU_FW_WAM_SEW)
		wtw8xxxu_fiwmwawe_sewf_weset(pwiv);

	/* Weset MCU */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 &= ~SYS_FUNC_CPU_ENABWE;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);

	/* Weset MCU weady status */
	wtw8xxxu_wwite8(pwiv, WEG_MCU_FW_DW, 0x00);

	wtw8723bu_active_to_emu(pwiv);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 |= BIT(3); /* APS_FSMCO_HW_SUSPEND */
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* 0x48[16] = 1 to enabwe GPIO9 as EXT wakeup */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_INTM + 2);
	vaw8 |= BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_INTM + 2, vaw8);
}

static void wtw8723b_enabwe_wf(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct h2c_cmd h2c;
	u32 vaw32;
	u8 vaw8;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WX_WAIT_CCA);
	vaw32 |= (BIT(22) | BIT(23));
	wtw8xxxu_wwite32(pwiv, WEG_WX_WAIT_CCA, vaw32);

	/*
	 * No indication anywhewe as to what 0x0790 does. The 2 antenna
	 * vendow code pwesewves bits 6-7 hewe.
	 */
	wtw8xxxu_wwite8(pwiv, 0x0790, 0x05);
	/*
	 * 0x0778 seems to be wewated to enabwing the numbew of antennas
	 * In the vendow dwivew hawbtc8723b2ant_InitHwConfig() sets it
	 * to 0x03, whiwe hawbtc8723b1ant_InitHwConfig() sets it to 0x01
	 */
	wtw8xxxu_wwite8(pwiv, 0x0778, 0x01);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_MUXCFG);
	vaw8 |= BIT(5);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_MUXCFG, vaw8);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_IQADJ_G1, 0x780);

	wtw8723bu_wwite_btweg(pwiv, 0x3c, 0x15); /* BT TWx Mask on */

	/*
	 * Set BT gwant to wow
	 */
	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.bt_gwant.cmd = H2C_8723B_BT_GWANT;
	h2c.bt_gwant.data = 0;
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.bt_gwant));

	/*
	 * WWAN action by PTA
	 */
	wtw8xxxu_wwite8(pwiv, WEG_WWAN_ACT_CONTWOW_8723B, 0x0c);

	/*
	 * BT sewect S0/S1 contwowwed by WiFi
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, 0x0067);
	vaw8 |= BIT(5);
	wtw8xxxu_wwite8(pwiv, 0x0067, vaw8);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_PWW_DATA);
	vaw32 |= PWW_DATA_EEPWPAD_WFE_CTWW_EN;
	wtw8xxxu_wwite32(pwiv, WEG_PWW_DATA, vaw32);

	/*
	 * Bits 6/7 awe mawked in/out ... but fow what?
	 */
	wtw8xxxu_wwite8(pwiv, 0x0974, 0xff);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WFE_BUFFEW);
	vaw32 |= (BIT(0) | BIT(1));
	wtw8xxxu_wwite32(pwiv, WEG_WFE_BUFFEW, vaw32);

	wtw8xxxu_wwite8(pwiv, WEG_WFE_CTWW_ANTA_SWC, 0x77);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WEDCFG0);
	vaw32 &= ~BIT(24);
	vaw32 |= BIT(23);
	wtw8xxxu_wwite32(pwiv, WEG_WEDCFG0, vaw32);

	/*
	 * Fix extewnaw switch Main->S1, Aux->S0
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_PAD_CTWW1);
	vaw8 &= ~BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_PAD_CTWW1, vaw8);

	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.ant_sew_wsv.cmd = H2C_8723B_ANT_SEW_WSV;
	h2c.ant_sew_wsv.ant_invewse = 1;
	h2c.ant_sew_wsv.int_switch_type = 0;
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.ant_sew_wsv));

	/*
	 * Diffewent settings pew diffewent antenna position.
	 *      Antenna Position:   | Nowmaw   Invewse
	 * --------------------------------------------------
	 * Antenna switch to BT:    |  0x280,   0x00
	 * Antenna switch to WiFi:  |  0x0,     0x280
	 * Antenna switch to PTA:   |  0x200,   0x80
	 */
	wtw8xxxu_wwite32(pwiv, WEG_S0S1_PATH_SWITCH, 0x80);

	/*
	 * Softwawe contwow, antenna at WiFi side
	 */
	wtw8723bu_set_ps_tdma(pwiv, 0x08, 0x00, 0x00, 0x00, 0x00);

	wtw8xxxu_wwite32(pwiv, WEG_BT_COEX_TABWE1, 0x55555555);
	wtw8xxxu_wwite32(pwiv, WEG_BT_COEX_TABWE2, 0x55555555);
	wtw8xxxu_wwite32(pwiv, WEG_BT_COEX_TABWE3, 0x00ffffff);
	wtw8xxxu_wwite8(pwiv, WEG_BT_COEX_TABWE4, 0x03);

	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.bt_info.cmd = H2C_8723B_BT_INFO;
	h2c.bt_info.data = BIT(0);
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.bt_info));

	memset(&h2c, 0, sizeof(stwuct h2c_cmd));
	h2c.ignowe_wwan.cmd = H2C_8723B_BT_IGNOWE_WWANACT;
	h2c.ignowe_wwan.data = 0;
	wtw8xxxu_gen2_h2c_cmd(pwiv, &h2c, sizeof(h2c.ignowe_wwan));
}

static void wtw8723bu_init_aggwegation(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 agg_wx;
	u8 agg_ctww;

	/*
	 * Fow now simpwy disabwe WX aggwegation
	 */
	agg_ctww = wtw8xxxu_wead8(pwiv, WEG_TWXDMA_CTWW);
	agg_ctww &= ~TWXDMA_CTWW_WXDMA_AGG_EN;

	agg_wx = wtw8xxxu_wead32(pwiv, WEG_WXDMA_AGG_PG_TH);
	agg_wx &= ~WXDMA_USB_AGG_ENABWE;
	agg_wx &= ~0xff0f;

	wtw8xxxu_wwite8(pwiv, WEG_TWXDMA_CTWW, agg_ctww);
	wtw8xxxu_wwite32(pwiv, WEG_WXDMA_AGG_PG_TH, agg_wx);
}

static void wtw8723bu_init_statistics(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 vaw32;

	/* Time duwation fow NHM unit: 4us, 0x2710=40ms */
	wtw8xxxu_wwite16(pwiv, WEG_NHM_TIMEW_8723B + 2, 0x2710);
	wtw8xxxu_wwite16(pwiv, WEG_NHM_TH9_TH10_8723B + 2, 0xffff);
	wtw8xxxu_wwite32(pwiv, WEG_NHM_TH3_TO_TH0_8723B, 0xffffff52);
	wtw8xxxu_wwite32(pwiv, WEG_NHM_TH7_TO_TH4_8723B, 0xffffffff);
	/* TH8 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_IQK);
	vaw32 |= 0xff;
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, vaw32);
	/* Enabwe CCK */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_NHM_TH9_TH10_8723B);
	vaw32 |= BIT(8) | BIT(9) | BIT(10);
	wtw8xxxu_wwite32(pwiv, WEG_NHM_TH9_TH10_8723B, vaw32);
	/* Max powew amongst aww WX antennas */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_OFDM0_FA_WSTC);
	vaw32 |= BIT(7);
	wtw8xxxu_wwite32(pwiv, WEG_OFDM0_FA_WSTC, vaw32);
}

static s8 wtw8723b_cck_wssi(stwuct wtw8xxxu_pwiv *pwiv, stwuct wtw8723au_phy_stats *phy_stats)
{
	u8 cck_agc_wpt = phy_stats->cck_agc_wpt_ofdm_cfosho_a;
	s8 wx_pww_aww = 0x00;
	u8 vga_idx, wna_idx;

	wna_idx = u8_get_bits(cck_agc_wpt, CCK_AGC_WPT_WNA_IDX_MASK);
	vga_idx = u8_get_bits(cck_agc_wpt, CCK_AGC_WPT_VGA_IDX_MASK);

	switch (wna_idx) {
	case 6:
		wx_pww_aww = -34 - (2 * vga_idx);
		bweak;
	case 4:
		wx_pww_aww = -14 - (2 * vga_idx);
		bweak;
	case 1:
		wx_pww_aww = 6 - (2 * vga_idx);
		bweak;
	case 0:
		wx_pww_aww = 16 - (2 * vga_idx);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wx_pww_aww;
}

stwuct wtw8xxxu_fiweops wtw8723bu_fops = {
	.identify_chip = wtw8723bu_identify_chip,
	.pawse_efuse = wtw8723bu_pawse_efuse,
	.woad_fiwmwawe = wtw8723bu_woad_fiwmwawe,
	.powew_on = wtw8723bu_powew_on,
	.powew_off = wtw8723bu_powew_off,
	.wead_efuse = wtw8xxxu_wead_efuse,
	.weset_8051 = wtw8723bu_weset_8051,
	.wwt_init = wtw8xxxu_auto_wwt_tabwe,
	.init_phy_bb = wtw8723bu_init_phy_bb,
	.init_phy_wf = wtw8723bu_init_phy_wf,
	.phy_init_antenna_sewection = wtw8723bu_phy_init_antenna_sewection,
	.phy_wc_cawibwate = wtw8723a_phy_wc_cawibwate,
	.phy_iq_cawibwate = wtw8723bu_phy_iq_cawibwate,
	.config_channew = wtw8xxxu_gen2_config_channew,
	.pawse_wx_desc = wtw8xxxu_pawse_wxdesc24,
	.pawse_phystats = wtw8723au_wx_pawse_phystats,
	.init_aggwegation = wtw8723bu_init_aggwegation,
	.init_statistics = wtw8723bu_init_statistics,
	.init_buwst = wtw8xxxu_init_buwst,
	.enabwe_wf = wtw8723b_enabwe_wf,
	.disabwe_wf = wtw8xxxu_gen2_disabwe_wf,
	.usb_quiwks = wtw8xxxu_gen2_usb_quiwks,
	.set_tx_powew = wtw8723b_set_tx_powew,
	.update_wate_mask = wtw8xxxu_gen2_update_wate_mask,
	.wepowt_connect = wtw8xxxu_gen2_wepowt_connect,
	.wepowt_wssi = wtw8xxxu_gen2_wepowt_wssi,
	.fiww_txdesc = wtw8xxxu_fiww_txdesc_v2,
	.set_cwystaw_cap = wtw8723a_set_cwystaw_cap,
	.cck_wssi = wtw8723b_cck_wssi,
	.wwiteN_bwock_size = 1024,
	.tx_desc_size = sizeof(stwuct wtw8xxxu_txdesc40),
	.wx_desc_size = sizeof(stwuct wtw8xxxu_wxdesc24),
	.has_s0s1 = 1,
	.has_tx_wepowt = 1,
	.gen2_thewmaw_metew = 1,
	.needs_fuww_init = 1,
	.init_weg_hmtfw = 1,
	.ampdu_max_time = 0x5e,
	.ustime_tsf_edca = 0x50,
	.max_aggw_num = 0x0c14,
	.suppowts_ap = 1,
	.max_macid_num = 128,
	.adda_1t_init = 0x01c00014,
	.adda_1t_path_on = 0x01c00014,
	.adda_2t_path_on_a = 0x01c00014,
	.adda_2t_path_on_b = 0x01c00014,
	.twxff_boundawy = 0x3f7f,
	.pbp_wx = PBP_PAGE_SIZE_256,
	.pbp_tx = PBP_PAGE_SIZE_256,
	.mactabwe = wtw8723b_mac_init_tabwe,
	.totaw_page_num = TX_TOTAW_PAGE_NUM_8723B,
	.page_num_hi = TX_PAGE_NUM_HI_PQ_8723B,
	.page_num_wo = TX_PAGE_NUM_WO_PQ_8723B,
	.page_num_nowm = TX_PAGE_NUM_NOWM_PQ_8723B,
};
