// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTW8XXXU mac80211 USB dwivew - 8192e specific subdwivew
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

static const stwuct wtw8xxxu_weg8vaw wtw8192e_mac_init_tabwe[] = {
	{0x011, 0xeb}, {0x012, 0x07}, {0x014, 0x75}, {0x303, 0xa7},
	{0x428, 0x0a}, {0x429, 0x10}, {0x430, 0x00}, {0x431, 0x00},
	{0x432, 0x00}, {0x433, 0x01}, {0x434, 0x04}, {0x435, 0x05},
	{0x436, 0x07}, {0x437, 0x08}, {0x43c, 0x04}, {0x43d, 0x05},
	{0x43e, 0x07}, {0x43f, 0x08}, {0x440, 0x5d}, {0x441, 0x01},
	{0x442, 0x00}, {0x444, 0x10}, {0x445, 0x00}, {0x446, 0x00},
	{0x447, 0x00}, {0x448, 0x00}, {0x449, 0xf0}, {0x44a, 0x0f},
	{0x44b, 0x3e}, {0x44c, 0x10}, {0x44d, 0x00}, {0x44e, 0x00},
	{0x44f, 0x00}, {0x450, 0x00}, {0x451, 0xf0}, {0x452, 0x0f},
	{0x453, 0x00}, {0x456, 0x5e}, {0x460, 0x66}, {0x461, 0x66},
	{0x4c8, 0xff}, {0x4c9, 0x08}, {0x4cc, 0xff}, {0x4cd, 0xff},
	{0x4ce, 0x01}, {0x500, 0x26}, {0x501, 0xa2}, {0x502, 0x2f},
	{0x503, 0x00}, {0x504, 0x28}, {0x505, 0xa3}, {0x506, 0x5e},
	{0x507, 0x00}, {0x508, 0x2b}, {0x509, 0xa4}, {0x50a, 0x5e},
	{0x50b, 0x00}, {0x50c, 0x4f}, {0x50d, 0xa4}, {0x50e, 0x00},
	{0x50f, 0x00}, {0x512, 0x1c}, {0x514, 0x0a}, {0x516, 0x0a},
	{0x525, 0x4f}, {0x540, 0x12}, {0x541, 0x64}, {0x550, 0x10},
	{0x551, 0x10}, {0x559, 0x02}, {0x55c, 0x50}, {0x55d, 0xff},
	{0x605, 0x30}, {0x608, 0x0e}, {0x609, 0x2a}, {0x620, 0xff},
	{0x621, 0xff}, {0x622, 0xff}, {0x623, 0xff}, {0x624, 0xff},
	{0x625, 0xff}, {0x626, 0xff}, {0x627, 0xff}, {0x638, 0x50},
	{0x63c, 0x0a}, {0x63d, 0x0a}, {0x63e, 0x0e}, {0x63f, 0x0e},
	{0x640, 0x40}, {0x642, 0x40}, {0x643, 0x00}, {0x652, 0xc8},
	{0x66e, 0x05}, {0x700, 0x21}, {0x701, 0x43}, {0x702, 0x65},
	{0x703, 0x87}, {0x708, 0x21}, {0x709, 0x43}, {0x70a, 0x65},
	{0x70b, 0x87},
	{0xffff, 0xff},
};

static const stwuct wtw8xxxu_weg32vaw wtw8192eu_phy_init_tabwe[] = {
	{0x800, 0x80040000}, {0x804, 0x00000003},
	{0x808, 0x0000fc00}, {0x80c, 0x0000000a},
	{0x810, 0x10001331}, {0x814, 0x020c3d10},
	{0x818, 0x02220385}, {0x81c, 0x00000000},
	{0x820, 0x01000100}, {0x824, 0x00390204},
	{0x828, 0x01000100}, {0x82c, 0x00390204},
	{0x830, 0x32323232}, {0x834, 0x30303030},
	{0x838, 0x30303030}, {0x83c, 0x30303030},
	{0x840, 0x00010000}, {0x844, 0x00010000},
	{0x848, 0x28282828}, {0x84c, 0x28282828},
	{0x850, 0x00000000}, {0x854, 0x00000000},
	{0x858, 0x009a009a}, {0x85c, 0x01000014},
	{0x860, 0x66f60000}, {0x864, 0x061f0000},
	{0x868, 0x30303030}, {0x86c, 0x30303030},
	{0x870, 0x00000000}, {0x874, 0x55004200},
	{0x878, 0x08080808}, {0x87c, 0x00000000},
	{0x880, 0xb0000c1c}, {0x884, 0x00000001},
	{0x888, 0x00000000}, {0x88c, 0xcc0000c0},
	{0x890, 0x00000800}, {0x894, 0xfffffffe},
	{0x898, 0x40302010}, {0x900, 0x00000000},
	{0x904, 0x00000023}, {0x908, 0x00000000},
	{0x90c, 0x81121313}, {0x910, 0x806c0001},
	{0x914, 0x00000001}, {0x918, 0x00000000},
	{0x91c, 0x00010000}, {0x924, 0x00000001},
	{0x928, 0x00000000}, {0x92c, 0x00000000},
	{0x930, 0x00000000}, {0x934, 0x00000000},
	{0x938, 0x00000000}, {0x93c, 0x00000000},
	{0x940, 0x00000000}, {0x944, 0x00000000},
	{0x94c, 0x00000008}, {0xa00, 0x00d0c7c8},
	{0xa04, 0x81ff000c}, {0xa08, 0x8c838300},
	{0xa0c, 0x2e68120f}, {0xa10, 0x95009b78},
	{0xa14, 0x1114d028}, {0xa18, 0x00881117},
	{0xa1c, 0x89140f00}, {0xa20, 0x1a1b0000},
	{0xa24, 0x090e1317}, {0xa28, 0x00000204},
	{0xa2c, 0x00d30000}, {0xa70, 0x101fff00},
	{0xa74, 0x00000007}, {0xa78, 0x00000900},
	{0xa7c, 0x225b0606}, {0xa80, 0x218075b1},
	{0xb38, 0x00000000}, {0xc00, 0x48071d40},
	{0xc04, 0x03a05633}, {0xc08, 0x000000e4},
	{0xc0c, 0x6c6c6c6c}, {0xc10, 0x08800000},
	{0xc14, 0x40000100}, {0xc18, 0x08800000},
	{0xc1c, 0x40000100}, {0xc20, 0x00000000},
	{0xc24, 0x00000000}, {0xc28, 0x00000000},
	{0xc2c, 0x00000000}, {0xc30, 0x69e9ac47},
	{0xc34, 0x469652af}, {0xc38, 0x49795994},
	{0xc3c, 0x0a97971c}, {0xc40, 0x1f7c403f},
	{0xc44, 0x000100b7}, {0xc48, 0xec020107},
	{0xc4c, 0x007f037f},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0xc50, 0x00340220},
#ewse
	{0xc50, 0x00340020},
#endif
	{0xc54, 0x0080801f},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0xc58, 0x00000220},
#ewse
	{0xc58, 0x00000020},
#endif
	{0xc5c, 0x00248492}, {0xc60, 0x00000000},
	{0xc64, 0x7112848b}, {0xc68, 0x47c00bff},
	{0xc6c, 0x00000036}, {0xc70, 0x00000600},
	{0xc74, 0x02013169}, {0xc78, 0x0000001f},
	{0xc7c, 0x00b91612},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0xc80, 0x2d4000b5},
#ewse
	{0xc80, 0x40000100},
#endif
	{0xc84, 0x21f60000},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0xc88, 0x2d4000b5},
#ewse
	{0xc88, 0x40000100},
#endif
	{0xc8c, 0xa0e40000}, {0xc90, 0x00121820},
	{0xc94, 0x00000000}, {0xc98, 0x00121820},
	{0xc9c, 0x00007f7f}, {0xca0, 0x00000000},
	{0xca4, 0x000300a0}, {0xca8, 0x00000000},
	{0xcac, 0x00000000}, {0xcb0, 0x00000000},
	{0xcb4, 0x00000000}, {0xcb8, 0x00000000},
	{0xcbc, 0x28000000}, {0xcc0, 0x00000000},
	{0xcc4, 0x00000000}, {0xcc8, 0x00000000},
	{0xccc, 0x00000000}, {0xcd0, 0x00000000},
	{0xcd4, 0x00000000}, {0xcd8, 0x64b22427},
	{0xcdc, 0x00766932}, {0xce0, 0x00222222},
	{0xce4, 0x00040000}, {0xce8, 0x77644302},
	{0xcec, 0x2f97d40c}, {0xd00, 0x00080740},
	{0xd04, 0x00020403}, {0xd08, 0x0000907f},
	{0xd0c, 0x20010201}, {0xd10, 0xa0633333},
	{0xd14, 0x3333bc43}, {0xd18, 0x7a8f5b6b},
	{0xd1c, 0x0000007f}, {0xd2c, 0xcc979975},
	{0xd30, 0x00000000}, {0xd34, 0x80608000},
	{0xd38, 0x00000000}, {0xd3c, 0x00127353},
	{0xd40, 0x00000000}, {0xd44, 0x00000000},
	{0xd48, 0x00000000}, {0xd4c, 0x00000000},
	{0xd50, 0x6437140a}, {0xd54, 0x00000000},
	{0xd58, 0x00000282}, {0xd5c, 0x30032064},
	{0xd60, 0x4653de68}, {0xd64, 0x04518a3c},
	{0xd68, 0x00002101}, {0xd6c, 0x2a201c16},
	{0xd70, 0x1812362e}, {0xd74, 0x322c2220},
	{0xd78, 0x000e3c24}, {0xd80, 0x01081008},
	{0xd84, 0x00000800}, {0xd88, 0xf0b50000},
	{0xe00, 0x30303030}, {0xe04, 0x30303030},
	{0xe08, 0x03903030}, {0xe10, 0x30303030},
	{0xe14, 0x30303030}, {0xe18, 0x30303030},
	{0xe1c, 0x30303030}, {0xe28, 0x00000000},
	{0xe30, 0x1000dc1f}, {0xe34, 0x10008c1f},
	{0xe38, 0x02140102}, {0xe3c, 0x681604c2},
	{0xe40, 0x01007c00}, {0xe44, 0x01004800},
	{0xe48, 0xfb000000}, {0xe4c, 0x000028d1},
	{0xe50, 0x1000dc1f}, {0xe54, 0x10008c1f},
	{0xe58, 0x02140102}, {0xe5c, 0x28160d05},
	{0xe60, 0x00000008}, {0xe68, 0x0fc05656},
	{0xe6c, 0x03c09696}, {0xe70, 0x03c09696},
	{0xe74, 0x0c005656}, {0xe78, 0x0c005656},
	{0xe7c, 0x0c005656}, {0xe80, 0x0c005656},
	{0xe84, 0x03c09696}, {0xe88, 0x0c005656},
	{0xe8c, 0x03c09696}, {0xed0, 0x03c09696},
	{0xed4, 0x03c09696}, {0xed8, 0x03c09696},
	{0xedc, 0x0000d6d6}, {0xee0, 0x0000d6d6},
	{0xeec, 0x0fc01616}, {0xee4, 0xb0000c1c},
	{0xee8, 0x00000001}, {0xf14, 0x00000003},
	{0xf4c, 0x00000000}, {0xf00, 0x00000300},
	{0xffff, 0xffffffff},
};

static const stwuct wtw8xxxu_weg32vaw wtw8xxx_agc_8192eu_std_tabwe[] = {
	{0xc78, 0xfb000001}, {0xc78, 0xfb010001},
	{0xc78, 0xfb020001}, {0xc78, 0xfb030001},
	{0xc78, 0xfb040001}, {0xc78, 0xfb050001},
	{0xc78, 0xfa060001}, {0xc78, 0xf9070001},
	{0xc78, 0xf8080001}, {0xc78, 0xf7090001},
	{0xc78, 0xf60a0001}, {0xc78, 0xf50b0001},
	{0xc78, 0xf40c0001}, {0xc78, 0xf30d0001},
	{0xc78, 0xf20e0001}, {0xc78, 0xf10f0001},
	{0xc78, 0xf0100001}, {0xc78, 0xef110001},
	{0xc78, 0xee120001}, {0xc78, 0xed130001},
	{0xc78, 0xec140001}, {0xc78, 0xeb150001},
	{0xc78, 0xea160001}, {0xc78, 0xe9170001},
	{0xc78, 0xe8180001}, {0xc78, 0xe7190001},
	{0xc78, 0xc81a0001}, {0xc78, 0xc71b0001},
	{0xc78, 0xc61c0001}, {0xc78, 0x071d0001},
	{0xc78, 0x061e0001}, {0xc78, 0x051f0001},
	{0xc78, 0x04200001}, {0xc78, 0x03210001},
	{0xc78, 0xaa220001}, {0xc78, 0xa9230001},
	{0xc78, 0xa8240001}, {0xc78, 0xa7250001},
	{0xc78, 0xa6260001}, {0xc78, 0x85270001},
	{0xc78, 0x84280001}, {0xc78, 0x83290001},
	{0xc78, 0x252a0001}, {0xc78, 0x242b0001},
	{0xc78, 0x232c0001}, {0xc78, 0x222d0001},
	{0xc78, 0x672e0001}, {0xc78, 0x662f0001},
	{0xc78, 0x65300001}, {0xc78, 0x64310001},
	{0xc78, 0x63320001}, {0xc78, 0x62330001},
	{0xc78, 0x61340001}, {0xc78, 0x45350001},
	{0xc78, 0x44360001}, {0xc78, 0x43370001},
	{0xc78, 0x42380001}, {0xc78, 0x41390001},
	{0xc78, 0x403a0001}, {0xc78, 0x403b0001},
	{0xc78, 0x403c0001}, {0xc78, 0x403d0001},
	{0xc78, 0x403e0001}, {0xc78, 0x403f0001},
	{0xc78, 0xfb400001}, {0xc78, 0xfb410001},
	{0xc78, 0xfb420001}, {0xc78, 0xfb430001},
	{0xc78, 0xfb440001}, {0xc78, 0xfb450001},
	{0xc78, 0xfa460001}, {0xc78, 0xf9470001},
	{0xc78, 0xf8480001}, {0xc78, 0xf7490001},
	{0xc78, 0xf64a0001}, {0xc78, 0xf54b0001},
	{0xc78, 0xf44c0001}, {0xc78, 0xf34d0001},
	{0xc78, 0xf24e0001}, {0xc78, 0xf14f0001},
	{0xc78, 0xf0500001}, {0xc78, 0xef510001},
	{0xc78, 0xee520001}, {0xc78, 0xed530001},
	{0xc78, 0xec540001}, {0xc78, 0xeb550001},
	{0xc78, 0xea560001}, {0xc78, 0xe9570001},
	{0xc78, 0xe8580001}, {0xc78, 0xe7590001},
	{0xc78, 0xe65a0001}, {0xc78, 0xe55b0001},
	{0xc78, 0xe45c0001}, {0xc78, 0xe35d0001},
	{0xc78, 0xe25e0001}, {0xc78, 0xe15f0001},
	{0xc78, 0x8a600001}, {0xc78, 0x89610001},
	{0xc78, 0x88620001}, {0xc78, 0x87630001},
	{0xc78, 0x86640001}, {0xc78, 0x85650001},
	{0xc78, 0x84660001}, {0xc78, 0x83670001},
	{0xc78, 0x82680001}, {0xc78, 0x6b690001},
	{0xc78, 0x6a6a0001}, {0xc78, 0x696b0001},
	{0xc78, 0x686c0001}, {0xc78, 0x676d0001},
	{0xc78, 0x666e0001}, {0xc78, 0x656f0001},
	{0xc78, 0x64700001}, {0xc78, 0x63710001},
	{0xc78, 0x62720001}, {0xc78, 0x61730001},
	{0xc78, 0x49740001}, {0xc78, 0x48750001},
	{0xc78, 0x47760001}, {0xc78, 0x46770001},
	{0xc78, 0x45780001}, {0xc78, 0x44790001},
	{0xc78, 0x437a0001}, {0xc78, 0x427b0001},
	{0xc78, 0x417c0001}, {0xc78, 0x407d0001},
	{0xc78, 0x407e0001}, {0xc78, 0x407f0001},
	{0xc50, 0x00040022}, {0xc50, 0x00040020},
	{0xffff, 0xffffffff}
};

static const stwuct wtw8xxxu_weg32vaw wtw8xxx_agc_8192eu_highpa_tabwe[] = {
	{0xc78, 0xfa000001}, {0xc78, 0xf9010001},
	{0xc78, 0xf8020001}, {0xc78, 0xf7030001},
	{0xc78, 0xf6040001}, {0xc78, 0xf5050001},
	{0xc78, 0xf4060001}, {0xc78, 0xf3070001},
	{0xc78, 0xf2080001}, {0xc78, 0xf1090001},
	{0xc78, 0xf00a0001}, {0xc78, 0xef0b0001},
	{0xc78, 0xee0c0001}, {0xc78, 0xed0d0001},
	{0xc78, 0xec0e0001}, {0xc78, 0xeb0f0001},
	{0xc78, 0xea100001}, {0xc78, 0xe9110001},
	{0xc78, 0xe8120001}, {0xc78, 0xe7130001},
	{0xc78, 0xe6140001}, {0xc78, 0xe5150001},
	{0xc78, 0xe4160001}, {0xc78, 0xe3170001},
	{0xc78, 0xe2180001}, {0xc78, 0xe1190001},
	{0xc78, 0x8a1a0001}, {0xc78, 0x891b0001},
	{0xc78, 0x881c0001}, {0xc78, 0x871d0001},
	{0xc78, 0x861e0001}, {0xc78, 0x851f0001},
	{0xc78, 0x84200001}, {0xc78, 0x83210001},
	{0xc78, 0x82220001}, {0xc78, 0x6a230001},
	{0xc78, 0x69240001}, {0xc78, 0x68250001},
	{0xc78, 0x67260001}, {0xc78, 0x66270001},
	{0xc78, 0x65280001}, {0xc78, 0x64290001},
	{0xc78, 0x632a0001}, {0xc78, 0x622b0001},
	{0xc78, 0x612c0001}, {0xc78, 0x602d0001},
	{0xc78, 0x472e0001}, {0xc78, 0x462f0001},
	{0xc78, 0x45300001}, {0xc78, 0x44310001},
	{0xc78, 0x43320001}, {0xc78, 0x42330001},
	{0xc78, 0x41340001}, {0xc78, 0x40350001},
	{0xc78, 0x40360001}, {0xc78, 0x40370001},
	{0xc78, 0x40380001}, {0xc78, 0x40390001},
	{0xc78, 0x403a0001}, {0xc78, 0x403b0001},
	{0xc78, 0x403c0001}, {0xc78, 0x403d0001},
	{0xc78, 0x403e0001}, {0xc78, 0x403f0001},
	{0xc78, 0xfa400001}, {0xc78, 0xf9410001},
	{0xc78, 0xf8420001}, {0xc78, 0xf7430001},
	{0xc78, 0xf6440001}, {0xc78, 0xf5450001},
	{0xc78, 0xf4460001}, {0xc78, 0xf3470001},
	{0xc78, 0xf2480001}, {0xc78, 0xf1490001},
	{0xc78, 0xf04a0001}, {0xc78, 0xef4b0001},
	{0xc78, 0xee4c0001}, {0xc78, 0xed4d0001},
	{0xc78, 0xec4e0001}, {0xc78, 0xeb4f0001},
	{0xc78, 0xea500001}, {0xc78, 0xe9510001},
	{0xc78, 0xe8520001}, {0xc78, 0xe7530001},
	{0xc78, 0xe6540001}, {0xc78, 0xe5550001},
	{0xc78, 0xe4560001}, {0xc78, 0xe3570001},
	{0xc78, 0xe2580001}, {0xc78, 0xe1590001},
	{0xc78, 0x8a5a0001}, {0xc78, 0x895b0001},
	{0xc78, 0x885c0001}, {0xc78, 0x875d0001},
	{0xc78, 0x865e0001}, {0xc78, 0x855f0001},
	{0xc78, 0x84600001}, {0xc78, 0x83610001},
	{0xc78, 0x82620001}, {0xc78, 0x6a630001},
	{0xc78, 0x69640001}, {0xc78, 0x68650001},
	{0xc78, 0x67660001}, {0xc78, 0x66670001},
	{0xc78, 0x65680001}, {0xc78, 0x64690001},
	{0xc78, 0x636a0001}, {0xc78, 0x626b0001},
	{0xc78, 0x616c0001}, {0xc78, 0x606d0001},
	{0xc78, 0x476e0001}, {0xc78, 0x466f0001},
	{0xc78, 0x45700001}, {0xc78, 0x44710001},
	{0xc78, 0x43720001}, {0xc78, 0x42730001},
	{0xc78, 0x41740001}, {0xc78, 0x40750001},
	{0xc78, 0x40760001}, {0xc78, 0x40770001},
	{0xc78, 0x40780001}, {0xc78, 0x40790001},
	{0xc78, 0x407a0001}, {0xc78, 0x407b0001},
	{0xc78, 0x407c0001}, {0xc78, 0x407d0001},
	{0xc78, 0x407e0001}, {0xc78, 0x407f0001},
	{0xc50, 0x00040222}, {0xc50, 0x00040220},
	{0xffff, 0xffffffff}
};

static const stwuct wtw8xxxu_wfwegvaw wtw8192eu_wadioa_init_tabwe[] = {
	{0x7f, 0x00000082}, {0x81, 0x0003fc00},
	{0x00, 0x00030000}, {0x08, 0x00008400},
	{0x18, 0x00000407}, {0x19, 0x00000012},
	{0x1b, 0x00000064}, {0x1e, 0x00080009},
	{0x1f, 0x00000880}, {0x2f, 0x0001a060},
	{0x3f, 0x00000000}, {0x42, 0x000060c0},
	{0x57, 0x000d0000}, {0x58, 0x000be180},
	{0x67, 0x00001552}, {0x83, 0x00000000},
	{0xb0, 0x000ff9f1}, {0xb1, 0x00055418},
	{0xb2, 0x0008cc00}, {0xb4, 0x00043083},
	{0xb5, 0x00008166}, {0xb6, 0x0000803e},
	{0xb7, 0x0001c69f}, {0xb8, 0x0000407f},
	{0xb9, 0x00080001}, {0xba, 0x00040001},
	{0xbb, 0x00000400}, {0xbf, 0x000c0000},
	{0xc2, 0x00002400}, {0xc3, 0x00000009},
	{0xc4, 0x00040c91}, {0xc5, 0x00099999},
	{0xc6, 0x000000a3}, {0xc7, 0x00088820},
	{0xc8, 0x00076c06}, {0xc9, 0x00000000},
	{0xca, 0x00080000}, {0xdf, 0x00000180},
	{0xef, 0x000001a0}, {0x51, 0x00069545},
	{0x52, 0x0007e45e}, {0x53, 0x00000071},
	{0x56, 0x00051ff3}, {0x35, 0x000000a8},
	{0x35, 0x000001e2}, {0x35, 0x000002a8},
	{0x36, 0x00001c24}, {0x36, 0x00009c24},
	{0x36, 0x00011c24}, {0x36, 0x00019c24},
	{0x18, 0x00000c07}, {0x5a, 0x00048000},
	{0x19, 0x000739d0},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x34, 0x0000a093}, {0x34, 0x0000908f},
	{0x34, 0x0000808c}, {0x34, 0x0000704d},
	{0x34, 0x0000604a}, {0x34, 0x00005047},
	{0x34, 0x0000400a}, {0x34, 0x00003007},
	{0x34, 0x00002004}, {0x34, 0x00001001},
	{0x34, 0x00000000},
#ewse
	/* Weguwaw */
	{0x34, 0x0000add7}, {0x34, 0x00009dd4},
	{0x34, 0x00008dd1}, {0x34, 0x00007dce},
	{0x34, 0x00006dcb}, {0x34, 0x00005dc8},
	{0x34, 0x00004dc5}, {0x34, 0x000034cc},
	{0x34, 0x0000244f}, {0x34, 0x0000144c},
	{0x34, 0x00000014},
#endif
	{0x00, 0x00030159},
	{0x84, 0x00068180},
	{0x86, 0x0000014e},
	{0x87, 0x00048e00},
	{0x8e, 0x00065540},
	{0x8f, 0x00088000},
	{0xef, 0x000020a0},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x3b, 0x000f07b0},
#ewse
	{0x3b, 0x000f02b0},
#endif
	{0x3b, 0x000ef7b0}, {0x3b, 0x000d4fb0},
	{0x3b, 0x000cf060}, {0x3b, 0x000b0090},
	{0x3b, 0x000a0080}, {0x3b, 0x00090080},
	{0x3b, 0x0008f780},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x3b, 0x000787b0},
#ewse
	{0x3b, 0x00078730},
#endif
	{0x3b, 0x00060fb0}, {0x3b, 0x0005ffa0},
	{0x3b, 0x00040620}, {0x3b, 0x00037090},
	{0x3b, 0x00020080}, {0x3b, 0x0001f060},
	{0x3b, 0x0000ffb0}, {0xef, 0x000000a0},
	{0xfe, 0x00000000}, {0x18, 0x0000fc07},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0x1e, 0x00000001}, {0x1f, 0x00080000},
	{0x00, 0x00033e70},
	{0xff, 0xffffffff}
};

static const stwuct wtw8xxxu_wfwegvaw wtw8192eu_wadiob_init_tabwe[] = {
	{0x7f, 0x00000082}, {0x81, 0x0003fc00},
	{0x00, 0x00030000}, {0x08, 0x00008400},
	{0x18, 0x00000407}, {0x19, 0x00000012},
	{0x1b, 0x00000064}, {0x1e, 0x00080009},
	{0x1f, 0x00000880}, {0x2f, 0x0001a060},
	{0x3f, 0x00000000}, {0x42, 0x000060c0},
	{0x57, 0x000d0000}, {0x58, 0x000be180},
	{0x67, 0x00001552}, {0x7f, 0x00000082},
	{0x81, 0x0003f000}, {0x83, 0x00000000},
	{0xdf, 0x00000180}, {0xef, 0x000001a0},
	{0x51, 0x00069545}, {0x52, 0x0007e42e},
	{0x53, 0x00000071}, {0x56, 0x00051ff3},
	{0x35, 0x000000a8}, {0x35, 0x000001e0},
	{0x35, 0x000002a8}, {0x36, 0x00001ca8},
	{0x36, 0x00009c24}, {0x36, 0x00011c24},
	{0x36, 0x00019c24}, {0x18, 0x00000c07},
	{0x5a, 0x00048000}, {0x19, 0x000739d0},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x34, 0x0000a093}, {0x34, 0x0000908f},
	{0x34, 0x0000808c}, {0x34, 0x0000704d},
	{0x34, 0x0000604a}, {0x34, 0x00005047},
	{0x34, 0x0000400a}, {0x34, 0x00003007},
	{0x34, 0x00002004}, {0x34, 0x00001001},
	{0x34, 0x00000000},
#ewse
	{0x34, 0x0000add7}, {0x34, 0x00009dd4},
	{0x34, 0x00008dd1}, {0x34, 0x00007dce},
	{0x34, 0x00006dcb}, {0x34, 0x00005dc8},
	{0x34, 0x00004dc5}, {0x34, 0x000034cc},
	{0x34, 0x0000244f}, {0x34, 0x0000144c},
	{0x34, 0x00000014},
#endif
	{0x00, 0x00030159}, {0x84, 0x00068180},
	{0x86, 0x000000ce}, {0x87, 0x00048a00},
	{0x8e, 0x00065540}, {0x8f, 0x00088000},
	{0xef, 0x000020a0},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x3b, 0x000f07b0},
#ewse
	{0x3b, 0x000f02b0},
#endif

	{0x3b, 0x000ef7b0}, {0x3b, 0x000d4fb0},
	{0x3b, 0x000cf060}, {0x3b, 0x000b0090},
	{0x3b, 0x000a0080}, {0x3b, 0x00090080},
	{0x3b, 0x0008f780},
#ifdef EXT_PA_8192EU
	/* Extewnaw PA ow extewnaw WNA */
	{0x3b, 0x000787b0},
#ewse
	{0x3b, 0x00078730},
#endif
	{0x3b, 0x00060fb0}, {0x3b, 0x0005ffa0},
	{0x3b, 0x00040620}, {0x3b, 0x00037090},
	{0x3b, 0x00020080}, {0x3b, 0x0001f060},
	{0x3b, 0x0000ffb0}, {0xef, 0x000000a0},
	{0x00, 0x00010159}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0xfe, 0x00000000},
	{0xfe, 0x00000000}, {0x1e, 0x00000001},
	{0x1f, 0x00080000}, {0x00, 0x00033e70},
	{0xff, 0xffffffff}
};

static int wtw8192eu_identify_chip(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	u32 vaw32, bonding, sys_cfg, vendow;
	int wet = 0;

	sys_cfg = wtw8xxxu_wead32(pwiv, WEG_SYS_CFG);
	pwiv->chip_cut = u32_get_bits(sys_cfg, SYS_CFG_CHIP_VEWSION_MASK);
	if (sys_cfg & SYS_CFG_TWP_VAUX_EN) {
		dev_info(dev, "Unsuppowted test chip\n");
		wet = -ENOTSUPP;
		goto out;
	}

	bonding = wtw8xxxu_wead32(pwiv, WEG_HPON_FSM);
	bonding &= HPON_FSM_BONDING_MASK;
	if (bonding == HPON_FSM_BONDING_1T2W) {
		stwscpy(pwiv->chip_name, "8191EU", sizeof(pwiv->chip_name));
		pwiv->tx_paths = 1;
		pwiv->wtw_chip = WTW8191E;
	} ewse {
		stwscpy(pwiv->chip_name, "8192EU", sizeof(pwiv->chip_name));
		pwiv->tx_paths = 2;
		pwiv->wtw_chip = WTW8192E;
	}
	pwiv->wf_paths = 2;
	pwiv->wx_paths = 2;
	pwiv->has_wifi = 1;

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

static void
wtw8192e_set_tx_powew(stwuct wtw8xxxu_pwiv *pwiv, int channew, boow ht40)
{
	u32 vaw32, ofdm, mcs;
	u8 cck, ofdmbase, mcsbase;
	int gwoup, tx_idx;

	tx_idx = 0;
	gwoup = wtw8xxxu_gen2_channew_to_gwoup(channew);

	cck = pwiv->cck_tx_powew_index_A[gwoup];

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_A_CCK1_MCS32);
	vaw32 &= 0xffff00ff;
	vaw32 |= (cck << 8);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_CCK1_MCS32, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11);
	vaw32 &= 0xff;
	vaw32 |= ((cck << 8) | (cck << 16) | (cck << 24));
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11, vaw32);

	ofdmbase = pwiv->ht40_1s_tx_powew_index_A[gwoup];
	ofdmbase += pwiv->ofdm_tx_powew_diff[tx_idx].a;
	ofdm = ofdmbase | ofdmbase << 8 | ofdmbase << 16 | ofdmbase << 24;

	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_WATE18_06, ofdm);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_WATE54_24, ofdm);

	mcsbase = pwiv->ht40_1s_tx_powew_index_A[gwoup];
	if (ht40)
		mcsbase += pwiv->ht40_tx_powew_diff[tx_idx++].a;
	ewse
		mcsbase += pwiv->ht20_tx_powew_diff[tx_idx++].a;
	mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS03_MCS00, mcs);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS07_MCS04, mcs);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS11_MCS08, mcs);
	wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_A_MCS15_MCS12, mcs);

	if (pwiv->tx_paths > 1) {
		cck = pwiv->cck_tx_powew_index_B[gwoup];

		vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_B_CCK1_55_MCS32);
		vaw32 &= 0xff;
		vaw32 |= ((cck << 8) | (cck << 16) | (cck << 24));
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_CCK1_55_MCS32, vaw32);

		vaw32 = wtw8xxxu_wead32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11);
		vaw32 &= 0xffffff00;
		vaw32 |= cck;
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_CCK11_A_CCK2_11, vaw32);

		ofdmbase = pwiv->ht40_1s_tx_powew_index_B[gwoup];
		ofdmbase += pwiv->ofdm_tx_powew_diff[tx_idx].b;
		ofdm = ofdmbase | ofdmbase << 8 |
			ofdmbase << 16 | ofdmbase << 24;

		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_WATE18_06, ofdm);
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_WATE54_24, ofdm);

		mcsbase = pwiv->ht40_1s_tx_powew_index_B[gwoup];
		if (ht40)
			mcsbase += pwiv->ht40_tx_powew_diff[tx_idx++].b;
		ewse
			mcsbase += pwiv->ht20_tx_powew_diff[tx_idx++].b;
		mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_MCS03_MCS00, mcs);
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_MCS07_MCS04, mcs);
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_MCS11_MCS08, mcs);
		wtw8xxxu_wwite32(pwiv, WEG_TX_AGC_B_MCS15_MCS12, mcs);
	}
}

static int wtw8192eu_pawse_efuse(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct wtw8192eu_efuse *efuse = &pwiv->efuse_wifi.efuse8192eu;
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

	pwiv->defauwt_cwystaw_cap = pwiv->efuse_wifi.efuse8192eu.xtaw_k & 0x3f;

	wetuwn 0;
}

static int wtw8192eu_woad_fiwmwawe(stwuct wtw8xxxu_pwiv *pwiv)
{
	const chaw *fw_name;
	int wet;

	fw_name = "wtwwifi/wtw8192eu_nic.bin";

	wet = wtw8xxxu_woad_fiwmwawe(pwiv, fw_name);

	wetuwn wet;
}

static void wtw8192eu_init_phy_bb(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 |= SYS_FUNC_BB_GWB_WSTN | SYS_FUNC_BBWSTB | SYS_FUNC_DIO_WF;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);

	/* 6. 0x1f[7:0] = 0x07 */
	vaw8 = WF_ENABWE | WF_WSTB | WF_SDMWSTB;
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, vaw8);

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 |= (SYS_FUNC_USBA | SYS_FUNC_USBD | SYS_FUNC_DIO_WF |
		  SYS_FUNC_BB_GWB_WSTN | SYS_FUNC_BBWSTB);
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);
	vaw8 = WF_ENABWE | WF_WSTB | WF_SDMWSTB;
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, vaw8);
	wtw8xxxu_init_phy_wegs(pwiv, wtw8192eu_phy_init_tabwe);

	if (pwiv->hi_pa)
		wtw8xxxu_init_phy_wegs(pwiv, wtw8xxx_agc_8192eu_highpa_tabwe);
	ewse
		wtw8xxxu_init_phy_wegs(pwiv, wtw8xxx_agc_8192eu_std_tabwe);
}

static int wtw8192eu_init_phy_wf(stwuct wtw8xxxu_pwiv *pwiv)
{
	int wet;

	wet = wtw8xxxu_init_phy_wf(pwiv, wtw8192eu_wadioa_init_tabwe, WF_A);
	if (wet)
		goto exit;

	wet = wtw8xxxu_init_phy_wf(pwiv, wtw8192eu_wadiob_init_tabwe, WF_B);

exit:
	wetuwn wet;
}

static int wtw8192eu_iqk_path_a(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_eac, weg_e94, weg_e9c;
	int wesuwt = 0;

	/*
	 * TX IQK
	 * PA/PAD contwowwed by 0x0
	 */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x00180);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x20000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0x07f77);

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* Path A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x82140303);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x68160000);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x00462911);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(10);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_e94 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_A);
	weg_e9c = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_A);

	if (!(weg_eac & BIT(28)) &&
	    ((weg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((weg_e9c & 0x03ff0000) != 0x00420000))
		wesuwt |= 0x01;

	wetuwn wesuwt;
}

static int wtw8192eu_wx_iqk_path_a(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_ea4, weg_eac, weg_e94, weg_e9c, vaw32;
	int wesuwt = 0;

	/* Weave IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00);

	/* Enabwe path A PA in TX IQK mode */
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf1173);

	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G2, 0xf1173);

	/* PA/PAD contwow by 0x56, and set = 0x0 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x00980);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_PAD_TXG, 0x511e0);

	/* Entew IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* TX IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* path-A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x8216031f);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x6816031f);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a911);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(10);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_e94 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_A);
	weg_e9c = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_A);

	if (!(weg_eac & BIT(28)) &&
	    ((weg_e94 & 0x03ff0000) != 0x01420000) &&
	    ((weg_e9c & 0x03ff0000) != 0x00420000)) {
		wesuwt |= 0x01;
	} ewse {
		/* PA/PAD contwowwed by 0x0 */
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
		wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x180);
		goto out;
	}

	vaw32 = 0x80007c00 |
		(weg_e94 & 0x03ff0000) | ((weg_e9c >> 16) & 0x03ff);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, vaw32);

	/* Modify WX IQK mode tabwe */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf7ff2);

	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G2, 0xf7ff2);

	/* PA/PAD contwow by 0x56, and set = 0x0 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x00980);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_PAD_TXG, 0x510e0);

	/* Entew IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* Path A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x821608ff);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x281608ff);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a891);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf9000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(10);

	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_ea4 = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_BEFOWE_IQK_A_2);

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_GAIN_CCA, 0x180);

	if (!(weg_eac & BIT(27)) &&
	    ((weg_ea4 & 0x03ff0000) != 0x01320000) &&
	    ((weg_eac & 0x03ff0000) != 0x00360000))
		wesuwt |= 0x02;
	ewse
		dev_wawn(&pwiv->udev->dev, "%s: Path A WX IQK faiwed!\n",
			 __func__);

out:
	wetuwn wesuwt;
}

static int wtw8192eu_iqk_path_b(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_eac, weg_eb4, weg_ebc;
	int wesuwt = 0;

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_GAIN_CCA, 0x00180);

	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WCK_OS, 0x20000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G2, 0x07f77);

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* Path B IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_B, 0x82140303);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_B, 0x68160000);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x00462911);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xfa000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(1);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_eb4 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_B);
	weg_ebc = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_B);

	if (!(weg_eac & BIT(31)) &&
	    ((weg_eb4 & 0x03ff0000) != 0x01420000) &&
	    ((weg_ebc & 0x03ff0000) != 0x00420000))
		wesuwt |= 0x01;
	ewse
		dev_wawn(&pwiv->udev->dev, "%s: Path B IQK faiwed!\n",
			 __func__);

	wetuwn wesuwt;
}

static int wtw8192eu_wx_iqk_path_b(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 weg_eac, weg_eb4, weg_ebc, weg_ec4, weg_ecc, vaw32;
	int wesuwt = 0;

	/* Weave IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);

	/* Enabwe path A PA in TX IQK mode */
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G2, 0xf1173);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf1173);

	/* PA/PAD contwow by 0x56, and set = 0x0 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_GAIN_CCA, 0x00980);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_PAD_TXG, 0x511e0);

	/* Entew IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* TX IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* path-A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x18008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x38008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_B, 0x8216031f);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_B, 0x6816031f);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a911);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xfa000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(10);

	/* Check faiwed */
	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_eb4 = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_BEFOWE_IQK_B);
	weg_ebc = wtw8xxxu_wead32(pwiv, WEG_TX_POWEW_AFTEW_IQK_B);

	if (!(weg_eac & BIT(31)) &&
	    ((weg_eb4 & 0x03ff0000) != 0x01420000) &&
	    ((weg_ebc & 0x03ff0000) != 0x00420000)) {
		wesuwt |= 0x01;
	} ewse {
		/*
		 * PA/PAD contwowwed by 0x0
		 * Vendow dwivew westowes WF_A hewe which I bewieve is a bug
		 */
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
		wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_GAIN_CCA, 0x180);
		goto out;
	}

	vaw32 = 0x80007c00 |
		(weg_eb4 & 0x03ff0000) | ((weg_ebc >> 16) & 0x03ff);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, vaw32);

	/* Modify WX IQK mode tabwe */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);

	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_TXPA_G2, 0xf7ff2);

	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WE_WUT, 0x800a0);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_WCK_OS, 0x30000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G1, 0x0000f);
	wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_TXPA_G2, 0xf7ff2);

	/* PA/PAD contwow by 0x56, and set = 0x0 */
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_GAIN_CCA, 0x00980);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_PAD_TXG, 0x510e0);

	/* Entew IQK mode */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

	/* IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	/* Path A IQK setting */
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_A, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_TONE_B, 0x38008c1c);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_TONE_B, 0x18008c1c);

	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK_PI_A, 0x821608ff);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK_PI_A, 0x281608ff);

	/* WO cawibwation setting */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_WSP, 0x0046a891);

	/* One shot, path A WOK & IQK */
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xfa000000);
	wtw8xxxu_wwite32(pwiv, WEG_IQK_AGC_PTS, 0xf8000000);

	mdeway(10);

	weg_eac = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_A_2);
	weg_ec4 = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_BEFOWE_IQK_B_2);
	weg_ecc = wtw8xxxu_wead32(pwiv, WEG_WX_POWEW_AFTEW_IQK_B_2);

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
	wtw8xxxu_wwite_wfweg(pwiv, WF_B, WF6052_WEG_GAIN_CCA, 0x180);

	if (!(weg_eac & BIT(30)) &&
	    ((weg_ec4 & 0x03ff0000) != 0x01320000) &&
	    ((weg_ecc & 0x03ff0000) != 0x00360000))
		wesuwt |= 0x02;
	ewse
		dev_wawn(&pwiv->udev->dev, "%s: Path B WX IQK faiwed!\n",
			 __func__);

out:
	wetuwn wesuwt;
}

static void wtw8192eu_phy_iqcawibwate(stwuct wtw8xxxu_pwiv *pwiv,
				      int wesuwt[][8], int t)
{
	stwuct device *dev = &pwiv->udev->dev;
	u32 i, vaw32;
	int path_a_ok, path_b_ok;
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
		WEG_FPGA0_XB_WF_INT_OE, WEG_CCK0_AFE_SETTING
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
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_XCD_WF_SW_CTWW, 0x22208200);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_XAB_WF_SW_CTWW);
	vaw32 |= (FPGA0_WF_PAPE | (FPGA0_WF_PAPE << FPGA0_WF_BD_CTWW_SHIFT));
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_XAB_WF_SW_CTWW, vaw32);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_XA_WF_INT_OE);
	vaw32 |= BIT(10);
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_XA_WF_INT_OE, vaw32);
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_FPGA0_XB_WF_INT_OE);
	vaw32 |= BIT(10);
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_XB_WF_INT_OE, vaw32);

	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);
	wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
	wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

	fow (i = 0; i < wetwy; i++) {
		path_a_ok = wtw8192eu_iqk_path_a(pwiv);
		if (path_a_ok == 0x01) {
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
		path_a_ok = wtw8192eu_wx_iqk_path_a(pwiv);
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

	if (pwiv->wf_paths > 1) {
		/* Path A into standby */
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);
		wtw8xxxu_wwite_wfweg(pwiv, WF_A, WF6052_WEG_AC, 0x10000);
		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);

		/* Tuwn Path B ADDA on */
		wtw8xxxu_path_adda_on(pwiv, adda_wegs, fawse);

		wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x80800000);
		wtw8xxxu_wwite32(pwiv, WEG_TX_IQK, 0x01007c00);
		wtw8xxxu_wwite32(pwiv, WEG_WX_IQK, 0x01004800);

		fow (i = 0; i < wetwy; i++) {
			path_b_ok = wtw8192eu_iqk_path_b(pwiv);
			if (path_b_ok == 0x01) {
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
			path_b_ok = wtw8192eu_wx_iqk_path_b(pwiv);
			if (path_b_ok == 0x03) {
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
	}

	/* Back to BB mode, woad owiginaw vawue */
	wtw8xxxu_wwite32(pwiv, WEG_FPGA0_IQK, 0x00000000);

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

		if (pwiv->wf_paths > 1) {
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

static void wtw8192eu_phy_iq_cawibwate(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	int wesuwt[4][8];	/* wast is finaw wesuwt */
	int i, candidate;
	boow path_a_ok, path_b_ok;
	u32 weg_e94, weg_e9c, weg_ea4, weg_eac;
	u32 weg_eb4, weg_ebc, weg_ec4, weg_ecc;
	boow simu;

	memset(wesuwt, 0, sizeof(wesuwt));
	candidate = -1;

	path_a_ok = fawse;
	path_b_ok = fawse;

	fow (i = 0; i < 3; i++) {
		wtw8192eu_phy_iqcawibwate(pwiv, wesuwt, i);

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
			if (simu)
				candidate = 1;
			ewse
				candidate = 3;
		}
	}

	fow (i = 0; i < 4; i++) {
		weg_e94 = wesuwt[i][0];
		weg_e9c = wesuwt[i][1];
		weg_ea4 = wesuwt[i][2];
		weg_eb4 = wesuwt[i][4];
		weg_ebc = wesuwt[i][5];
		weg_ec4 = wesuwt[i][6];
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

	if (pwiv->wf_paths > 1)
		wtw8xxxu_fiww_iqk_matwix_b(pwiv, path_b_ok, wesuwt,
					   candidate, (weg_ec4 == 0));

	wtw8xxxu_save_wegs(pwiv, wtw8xxxu_iqk_phy_iq_bb_weg,
			   pwiv->bb_wecovewy_backup, WTW8XXXU_BB_WEGS);
}

/*
 * This is needed fow 8723bu as weww, pwesumabwe
 */
static void wtw8192e_cwystaw_afe_adjust(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u32 vaw32;

	/*
	 * 40Mhz cwystaw souwce, MAC 0x28[2]=0
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_AFE_PWW_CTWW);
	vaw8 &= 0xfb;
	wtw8xxxu_wwite8(pwiv, WEG_AFE_PWW_CTWW, vaw8);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_AFE_CTWW4);
	vaw32 &= 0xfffffc7f;
	wtw8xxxu_wwite32(pwiv, WEG_AFE_CTWW4, vaw32);

	/*
	 * 92e AFE pawametew
	 * AFE PWW KVCO sewection, MAC 0x28[6]=1
	 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_AFE_PWW_CTWW);
	vaw8 &= 0xbf;
	wtw8xxxu_wwite8(pwiv, WEG_AFE_PWW_CTWW, vaw8);

	/*
	 * AFE PWW KVCO sewection, MAC 0x78[21]=0
	 */
	vaw32 = wtw8xxxu_wead32(pwiv, WEG_AFE_CTWW4);
	vaw32 &= 0xffdfffff;
	wtw8xxxu_wwite32(pwiv, WEG_AFE_CTWW4, vaw32);
}

static void wtw8192e_disabwed_to_emu(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;

	/* Cweaw suspend enabwe and powew down enabwe*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~(BIT(3) | BIT(4));
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);
}

static int wtw8192e_emu_to_active(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u32 vaw32;
	int count, wet = 0;

	/* disabwe HWPDN 0x04[15]=0*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~BIT(7);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* disabwe SW WPS 0x04[10]= 0 */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~BIT(2);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* disabwe WW suspend*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~(BIT(3) | BIT(4));
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	/* wait tiww 0x04[17] = 1 powew weady*/
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

	/* wewease WWON weset 0x04[16]= 1*/
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 2);
	vaw8 |= BIT(0);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 2, vaw8);

	/* set, then poww untiw 0 */
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

exit:
	wetuwn wet;
}

static int wtw8192eu_active_to_wps(stwuct wtw8xxxu_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->udev->dev;
	u8 vaw8;
	u16 vaw16;
	u32 vaw32;
	int wetwy, wetvaw;

	wtw8xxxu_wwite8(pwiv, WEG_TXPAUSE, 0xff);

	wetwy = 100;
	wetvaw = -EBUSY;
	/*
	 * Poww 32 bit wide 0x05f8 fow 0x00000000 to ensuwe no TX is pending.
	 */
	do {
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_SCH_TX_CMD);
		if (!vaw32) {
			wetvaw = 0;
			bweak;
		}
	} whiwe (wetwy--);

	if (!wetwy) {
		dev_wawn(dev, "Faiwed to fwush TX queue\n");
		wetvaw = -EBUSY;
		goto out;
	}

	/* Disabwe CCK and OFDM, cwock gated */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_SYS_FUNC);
	vaw8 &= ~SYS_FUNC_BBWSTB;
	wtw8xxxu_wwite8(pwiv, WEG_SYS_FUNC, vaw8);

	udeway(2);

	/* Weset whowe BB */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_SYS_FUNC);
	vaw8 &= ~SYS_FUNC_BB_GWB_WSTN;
	wtw8xxxu_wwite8(pwiv, WEG_SYS_FUNC, vaw8);

	/* Weset MAC TWX */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_CW);
	vaw16 &= 0xff00;
	vaw16 |= (CW_HCI_TXDMA_ENABWE | CW_HCI_WXDMA_ENABWE);
	wtw8xxxu_wwite16(pwiv, WEG_CW, vaw16);

	vaw16 = wtw8xxxu_wead16(pwiv, WEG_CW);
	vaw16 &= ~CW_SECUWITY_ENABWE;
	wtw8xxxu_wwite16(pwiv, WEG_CW, vaw16);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_DUAW_TSF_WST);
	vaw8 |= DUAW_TSF_TX_OK;
	wtw8xxxu_wwite8(pwiv, WEG_DUAW_TSF_WST, vaw8);

out:
	wetuwn wetvaw;
}

static int wtw8192eu_active_to_emu(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	int count, wet = 0;

	/* Tuwn off WF */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WF_CTWW);
	vaw8 &= ~WF_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, vaw8);

	/* Switch DPDT_SEW_P output fwom wegistew 0x65[2] */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_WEDCFG2);
	vaw8 &= ~WEDCFG2_DPDT_SEWECT;
	wtw8xxxu_wwite8(pwiv, WEG_WEDCFG2, vaw8);

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

exit:
	wetuwn wet;
}

static int wtw8192eu_emu_to_disabwed(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;

	/* 0x04[12:11] = 01 enabwe WW suspend */
	vaw8 = wtw8xxxu_wead8(pwiv, WEG_APS_FSMCO + 1);
	vaw8 &= ~(BIT(3) | BIT(4));
	vaw8 |= BIT(3);
	wtw8xxxu_wwite8(pwiv, WEG_APS_FSMCO + 1, vaw8);

	wetuwn 0;
}

static int wtw8192eu_powew_on(stwuct wtw8xxxu_pwiv *pwiv)
{
	u16 vaw16;
	u32 vaw32;
	int wet;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_SYS_CFG);
	if (vaw32 & SYS_CFG_SPS_WDO_SEW) {
		wtw8xxxu_wwite8(pwiv, WEG_WDO_SW_CTWW, 0xc3);
	} ewse {
		/*
		 * Waise 1.2V vowtage
		 */
		vaw32 = wtw8xxxu_wead32(pwiv, WEG_8192E_WDOV12_CTWW);
		vaw32 &= 0xff0fffff;
		vaw32 |= 0x00500000;
		wtw8xxxu_wwite32(pwiv, WEG_8192E_WDOV12_CTWW, vaw32);
		wtw8xxxu_wwite8(pwiv, WEG_WDO_SW_CTWW, 0x83);
	}

	/*
	 * Adjust AFE befowe enabwing PWW
	 */
	wtw8192e_cwystaw_afe_adjust(pwiv);
	wtw8192e_disabwed_to_emu(pwiv);

	wet = wtw8192e_emu_to_active(pwiv);
	if (wet)
		goto exit;

	wtw8xxxu_wwite16(pwiv, WEG_CW, 0x0000);

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

exit:
	wetuwn wet;
}

static void wtw8192eu_powew_off(stwuct wtw8xxxu_pwiv *pwiv)
{
	u8 vaw8;
	u16 vaw16;

	wtw8xxxu_fwush_fifo(pwiv);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_TX_WEPOWT_CTWW);
	vaw8 &= ~TX_WEPOWT_CTWW_TIMEW_ENABWE;
	wtw8xxxu_wwite8(pwiv, WEG_TX_WEPOWT_CTWW, vaw8);

	/* Tuwn off WF */
	wtw8xxxu_wwite8(pwiv, WEG_WF_CTWW, 0x00);

	wtw8192eu_active_to_wps(pwiv);

	/* Weset Fiwmwawe if wunning in WAM */
	if (wtw8xxxu_wead8(pwiv, WEG_MCU_FW_DW) & MCU_FW_WAM_SEW)
		wtw8xxxu_fiwmwawe_sewf_weset(pwiv);

	/* Weset MCU */
	vaw16 = wtw8xxxu_wead16(pwiv, WEG_SYS_FUNC);
	vaw16 &= ~SYS_FUNC_CPU_ENABWE;
	wtw8xxxu_wwite16(pwiv, WEG_SYS_FUNC, vaw16);

	/* Weset MCU weady status */
	wtw8xxxu_wwite8(pwiv, WEG_MCU_FW_DW, 0x00);

	wtw8xxxu_weset_8051(pwiv);

	wtw8192eu_active_to_emu(pwiv);
	wtw8192eu_emu_to_disabwed(pwiv);
}

static void wtw8192e_enabwe_wf(stwuct wtw8xxxu_pwiv *pwiv)
{
	u32 vaw32;
	u8 vaw8;

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_WX_WAIT_CCA);
	vaw32 |= (BIT(22) | BIT(23));
	wtw8xxxu_wwite32(pwiv, WEG_WX_WAIT_CCA, vaw32);

	vaw8 = wtw8xxxu_wead8(pwiv, WEG_GPIO_MUXCFG);
	vaw8 |= BIT(5);
	wtw8xxxu_wwite8(pwiv, WEG_GPIO_MUXCFG, vaw8);

	/*
	 * WWAN action by PTA
	 */
	wtw8xxxu_wwite8(pwiv, WEG_WWAN_ACT_CONTWOW_8723B, 0x04);

	vaw32 = wtw8xxxu_wead32(pwiv, WEG_PWW_DATA);
	vaw32 |= PWW_DATA_EEPWPAD_WFE_CTWW_EN;
	wtw8xxxu_wwite32(pwiv, WEG_PWW_DATA, vaw32);

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

	/*
	 * Fix twansmission faiwuwe of wtw8192e.
	 */
	wtw8xxxu_wwite8(pwiv, WEG_TXPAUSE, 0x00);
}

static s8 wtw8192e_cck_wssi(stwuct wtw8xxxu_pwiv *pwiv, stwuct wtw8723au_phy_stats *phy_stats)
{
	static const s8 wna_gain_tabwe_0[8] = {15, 9, -10, -21, -23, -27, -43, -44};
	static const s8 wna_gain_tabwe_1[8] = {24, 18, 13, -4, -11, -18, -31, -36};

	u8 cck_agc_wpt = phy_stats->cck_agc_wpt_ofdm_cfosho_a;
	s8 wx_pww_aww = 0x00;
	u8 vga_idx, wna_idx;
	s8 wna_gain = 0;

	wna_idx = u8_get_bits(cck_agc_wpt, CCK_AGC_WPT_WNA_IDX_MASK);
	vga_idx = u8_get_bits(cck_agc_wpt, CCK_AGC_WPT_VGA_IDX_MASK);

	if (pwiv->cck_agc_wepowt_type == 0)
		wna_gain = wna_gain_tabwe_0[wna_idx];
	ewse
		wna_gain = wna_gain_tabwe_1[wna_idx];

	wx_pww_aww = wna_gain - (2 * vga_idx);

	wetuwn wx_pww_aww;
}

static int wtw8192eu_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness bwightness)
{
	stwuct wtw8xxxu_pwiv *pwiv = containew_of(wed_cdev,
						  stwuct wtw8xxxu_pwiv,
						  wed_cdev);
	u8 wedcfg = wtw8xxxu_wead8(pwiv, WEG_WEDCFG1);

	if (bwightness == WED_OFF) {
		wedcfg &= ~WEDCFG1_HW_WED_CONTWOW;
		wedcfg |= WEDCFG1_WED_DISABWE;
	} ewse if (bwightness == WED_ON) {
		wedcfg &= ~(WEDCFG1_HW_WED_CONTWOW | WEDCFG1_WED_DISABWE);
	} ewse if (bwightness == WTW8XXXU_HW_WED_CONTWOW) {
		wedcfg &= ~WEDCFG1_WED_DISABWE;
		wedcfg |= WEDCFG1_HW_WED_CONTWOW;
	}

	wtw8xxxu_wwite8(pwiv, WEG_WEDCFG1, wedcfg);

	wetuwn 0;
}

stwuct wtw8xxxu_fiweops wtw8192eu_fops = {
	.identify_chip = wtw8192eu_identify_chip,
	.pawse_efuse = wtw8192eu_pawse_efuse,
	.woad_fiwmwawe = wtw8192eu_woad_fiwmwawe,
	.powew_on = wtw8192eu_powew_on,
	.powew_off = wtw8192eu_powew_off,
	.wead_efuse = wtw8xxxu_wead_efuse,
	.weset_8051 = wtw8xxxu_weset_8051,
	.wwt_init = wtw8xxxu_auto_wwt_tabwe,
	.init_phy_bb = wtw8192eu_init_phy_bb,
	.init_phy_wf = wtw8192eu_init_phy_wf,
	.phy_wc_cawibwate = wtw8723a_phy_wc_cawibwate,
	.phy_iq_cawibwate = wtw8192eu_phy_iq_cawibwate,
	.config_channew = wtw8xxxu_gen2_config_channew,
	.pawse_wx_desc = wtw8xxxu_pawse_wxdesc24,
	.pawse_phystats = wtw8723au_wx_pawse_phystats,
	.enabwe_wf = wtw8192e_enabwe_wf,
	.disabwe_wf = wtw8xxxu_gen2_disabwe_wf,
	.usb_quiwks = wtw8xxxu_gen2_usb_quiwks,
	.set_tx_powew = wtw8192e_set_tx_powew,
	.update_wate_mask = wtw8xxxu_gen2_update_wate_mask,
	.wepowt_connect = wtw8xxxu_gen2_wepowt_connect,
	.wepowt_wssi = wtw8xxxu_gen2_wepowt_wssi,
	.fiww_txdesc = wtw8xxxu_fiww_txdesc_v2,
	.set_cwystaw_cap = wtw8723a_set_cwystaw_cap,
	.cck_wssi = wtw8192e_cck_wssi,
	.wed_cwassdev_bwightness_set = wtw8192eu_wed_bwightness_set,
	.wwiteN_bwock_size = 128,
	.tx_desc_size = sizeof(stwuct wtw8xxxu_txdesc40),
	.wx_desc_size = sizeof(stwuct wtw8xxxu_wxdesc24),
	.has_s0s1 = 0,
	.gen2_thewmaw_metew = 1,
	.needs_fuww_init = 1,
	.suppowts_ap = 1,
	.max_macid_num = 128,
	.adda_1t_init = 0x0fc01616,
	.adda_1t_path_on = 0x0fc01616,
	.adda_2t_path_on_a = 0x0fc01616,
	.adda_2t_path_on_b = 0x0fc01616,
	.twxff_boundawy = 0x3cff,
	.mactabwe = wtw8192e_mac_init_tabwe,
	.totaw_page_num = TX_TOTAW_PAGE_NUM_8192E,
	.page_num_hi = TX_PAGE_NUM_HI_PQ_8192E,
	.page_num_wo = TX_PAGE_NUM_WO_PQ_8192E,
	.page_num_nowm = TX_PAGE_NUM_NOWM_PQ_8192E,
};
