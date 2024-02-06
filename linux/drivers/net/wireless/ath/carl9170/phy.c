/*
 * Athewos CAWW9170 dwivew
 *
 * PHY and WF code
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/bitwev.h>
#incwude "caww9170.h"
#incwude "cmd.h"
#incwude "phy.h"

static int caww9170_init_powew_caw(stwuct aw9170 *aw)
{
	caww9170_wegwwite_begin(aw);

	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE_MAX, 0x7f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE1, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE2, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE3, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE4, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE5, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE6, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE7, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE8, 0x3f3f3f3f);
	caww9170_wegwwite(AW9170_PHY_WEG_POWEW_TX_WATE9, 0x3f3f3f3f);

	caww9170_wegwwite_finish();
	wetuwn caww9170_wegwwite_wesuwt();
}

stwuct caww9170_phy_init {
	u32 weg, _5ghz_20, _5ghz_40, _2ghz_40, _2ghz_20;
};

static stwuct caww9170_phy_init aw5416_phy_init[] = {
	{ 0x1c5800, 0x00000007, 0x00000007, 0x00000007, 0x00000007, },
	{ 0x1c5804, 0x00000300, 0x000003c4, 0x000003c4, 0x00000300, },
	{ 0x1c5808, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c580c, 0xad848e19, 0xad848e19, 0xad848e19, 0xad848e19, },
	{ 0x1c5810, 0x7d14e000, 0x7d14e000, 0x7d14e000, 0x7d14e000, },
	{ 0x1c5814, 0x9c0a9f6b, 0x9c0a9f6b, 0x9c0a9f6b, 0x9c0a9f6b, },
	{ 0x1c5818, 0x00000090, 0x00000090, 0x00000090, 0x00000090, },
	{ 0x1c581c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5820, 0x02020200, 0x02020200, 0x02020200, 0x02020200, },
	{ 0x1c5824, 0x00000e0e, 0x00000e0e, 0x00000e0e, 0x00000e0e, },
	{ 0x1c5828, 0x0a020001, 0x0a020001, 0x0a020001, 0x0a020001, },
	{ 0x1c582c, 0x0000a000, 0x0000a000, 0x0000a000, 0x0000a000, },
	{ 0x1c5830, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5834, 0x00000e0e, 0x00000e0e, 0x00000e0e, 0x00000e0e, },
	{ 0x1c5838, 0x00000007, 0x00000007, 0x00000007, 0x00000007, },
	{ 0x1c583c, 0x00200400, 0x00200400, 0x00200400, 0x00200400, },
	{ 0x1c5840, 0x206a002e, 0x206a002e, 0x206a002e, 0x206a002e, },
	{ 0x1c5844, 0x1372161e, 0x13721c1e, 0x13721c24, 0x137216a4, },
	{ 0x1c5848, 0x001a6a65, 0x001a6a65, 0x00197a68, 0x00197a68, },
	{ 0x1c584c, 0x1284233c, 0x1284233c, 0x1284233c, 0x1284233c, },
	{ 0x1c5850, 0x6c48b4e4, 0x6d48b4e4, 0x6d48b0e4, 0x6c48b0e4, },
	{ 0x1c5854, 0x00000859, 0x00000859, 0x00000859, 0x00000859, },
	{ 0x1c5858, 0x7ec80d2e, 0x7ec80d2e, 0x7ec80d2e, 0x7ec80d2e, },
	{ 0x1c585c, 0x31395c5e, 0x3139605e, 0x3139605e, 0x31395c5e, },
	{ 0x1c5860, 0x0004dd10, 0x0004dd10, 0x0004dd20, 0x0004dd20, },
	{ 0x1c5864, 0x0001c600, 0x0001c600, 0x0001c600, 0x0001c600, },
	{ 0x1c5868, 0x409a4190, 0x409a4190, 0x409a4190, 0x409a4190, },
	{ 0x1c586c, 0x050cb081, 0x050cb081, 0x050cb081, 0x050cb081, },
	{ 0x1c5900, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5904, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5908, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c590c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5914, 0x000007d0, 0x000007d0, 0x00000898, 0x00000898, },
	{ 0x1c5918, 0x00000118, 0x00000230, 0x00000268, 0x00000134, },
	{ 0x1c591c, 0x10000fff, 0x10000fff, 0x10000fff, 0x10000fff, },
	{ 0x1c5920, 0x0510081c, 0x0510081c, 0x0510001c, 0x0510001c, },
	{ 0x1c5924, 0xd0058a15, 0xd0058a15, 0xd0058a15, 0xd0058a15, },
	{ 0x1c5928, 0x00000001, 0x00000001, 0x00000001, 0x00000001, },
	{ 0x1c592c, 0x00000004, 0x00000004, 0x00000004, 0x00000004, },
	{ 0x1c5934, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c5938, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c593c, 0x0000007f, 0x0000007f, 0x0000007f, 0x0000007f, },
	{ 0x1c5944, 0xdfb81020, 0xdfb81020, 0xdfb81020, 0xdfb81020, },
	{ 0x1c5948, 0x9280b212, 0x9280b212, 0x9280b212, 0x9280b212, },
	{ 0x1c594c, 0x00020028, 0x00020028, 0x00020028, 0x00020028, },
	{ 0x1c5954, 0x5d50e188, 0x5d50e188, 0x5d50e188, 0x5d50e188, },
	{ 0x1c5958, 0x00081fff, 0x00081fff, 0x00081fff, 0x00081fff, },
	{ 0x1c5960, 0x00009b40, 0x00009b40, 0x00009b40, 0x00009b40, },
	{ 0x1c5964, 0x00001120, 0x00001120, 0x00001120, 0x00001120, },
	{ 0x1c5970, 0x190fb515, 0x190fb515, 0x190fb515, 0x190fb515, },
	{ 0x1c5974, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5978, 0x00000001, 0x00000001, 0x00000001, 0x00000001, },
	{ 0x1c597c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5980, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5984, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5988, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c598c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5990, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5994, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5998, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c599c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59a0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59a4, 0x00000007, 0x00000007, 0x00000007, 0x00000007, },
	{ 0x1c59a8, 0x001fff00, 0x001fff00, 0x001fff00, 0x001fff00, },
	{ 0x1c59ac, 0x006f00c4, 0x006f00c4, 0x006f00c4, 0x006f00c4, },
	{ 0x1c59b0, 0x03051000, 0x03051000, 0x03051000, 0x03051000, },
	{ 0x1c59b4, 0x00000820, 0x00000820, 0x00000820, 0x00000820, },
	{ 0x1c59bc, 0x00181400, 0x00181400, 0x00181400, 0x00181400, },
	{ 0x1c59c0, 0x038919be, 0x038919be, 0x038919be, 0x038919be, },
	{ 0x1c59c4, 0x06336f77, 0x06336f77, 0x06336f77, 0x06336f77, },
	{ 0x1c59c8, 0x6af6532c, 0x6af6532c, 0x6af6532c, 0x6af6532c, },
	{ 0x1c59cc, 0x08f186c8, 0x08f186c8, 0x08f186c8, 0x08f186c8, },
	{ 0x1c59d0, 0x00046384, 0x00046384, 0x00046384, 0x00046384, },
	{ 0x1c59d4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59d8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59dc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59e0, 0x00000200, 0x00000200, 0x00000200, 0x00000200, },
	{ 0x1c59e4, 0x64646464, 0x64646464, 0x64646464, 0x64646464, },
	{ 0x1c59e8, 0x3c787878, 0x3c787878, 0x3c787878, 0x3c787878, },
	{ 0x1c59ec, 0x000000aa, 0x000000aa, 0x000000aa, 0x000000aa, },
	{ 0x1c59f0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c59fc, 0x00001042, 0x00001042, 0x00001042, 0x00001042, },
	{ 0x1c5a00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5a04, 0x00000040, 0x00000040, 0x00000040, 0x00000040, },
	{ 0x1c5a08, 0x00000080, 0x00000080, 0x00000080, 0x00000080, },
	{ 0x1c5a0c, 0x000001a1, 0x000001a1, 0x00000141, 0x00000141, },
	{ 0x1c5a10, 0x000001e1, 0x000001e1, 0x00000181, 0x00000181, },
	{ 0x1c5a14, 0x00000021, 0x00000021, 0x000001c1, 0x000001c1, },
	{ 0x1c5a18, 0x00000061, 0x00000061, 0x00000001, 0x00000001, },
	{ 0x1c5a1c, 0x00000168, 0x00000168, 0x00000041, 0x00000041, },
	{ 0x1c5a20, 0x000001a8, 0x000001a8, 0x000001a8, 0x000001a8, },
	{ 0x1c5a24, 0x000001e8, 0x000001e8, 0x000001e8, 0x000001e8, },
	{ 0x1c5a28, 0x00000028, 0x00000028, 0x00000028, 0x00000028, },
	{ 0x1c5a2c, 0x00000068, 0x00000068, 0x00000068, 0x00000068, },
	{ 0x1c5a30, 0x00000189, 0x00000189, 0x000000a8, 0x000000a8, },
	{ 0x1c5a34, 0x000001c9, 0x000001c9, 0x00000169, 0x00000169, },
	{ 0x1c5a38, 0x00000009, 0x00000009, 0x000001a9, 0x000001a9, },
	{ 0x1c5a3c, 0x00000049, 0x00000049, 0x000001e9, 0x000001e9, },
	{ 0x1c5a40, 0x00000089, 0x00000089, 0x00000029, 0x00000029, },
	{ 0x1c5a44, 0x00000170, 0x00000170, 0x00000069, 0x00000069, },
	{ 0x1c5a48, 0x000001b0, 0x000001b0, 0x00000190, 0x00000190, },
	{ 0x1c5a4c, 0x000001f0, 0x000001f0, 0x000001d0, 0x000001d0, },
	{ 0x1c5a50, 0x00000030, 0x00000030, 0x00000010, 0x00000010, },
	{ 0x1c5a54, 0x00000070, 0x00000070, 0x00000050, 0x00000050, },
	{ 0x1c5a58, 0x00000191, 0x00000191, 0x00000090, 0x00000090, },
	{ 0x1c5a5c, 0x000001d1, 0x000001d1, 0x00000151, 0x00000151, },
	{ 0x1c5a60, 0x00000011, 0x00000011, 0x00000191, 0x00000191, },
	{ 0x1c5a64, 0x00000051, 0x00000051, 0x000001d1, 0x000001d1, },
	{ 0x1c5a68, 0x00000091, 0x00000091, 0x00000011, 0x00000011, },
	{ 0x1c5a6c, 0x000001b8, 0x000001b8, 0x00000051, 0x00000051, },
	{ 0x1c5a70, 0x000001f8, 0x000001f8, 0x00000198, 0x00000198, },
	{ 0x1c5a74, 0x00000038, 0x00000038, 0x000001d8, 0x000001d8, },
	{ 0x1c5a78, 0x00000078, 0x00000078, 0x00000018, 0x00000018, },
	{ 0x1c5a7c, 0x00000199, 0x00000199, 0x00000058, 0x00000058, },
	{ 0x1c5a80, 0x000001d9, 0x000001d9, 0x00000098, 0x00000098, },
	{ 0x1c5a84, 0x00000019, 0x00000019, 0x00000159, 0x00000159, },
	{ 0x1c5a88, 0x00000059, 0x00000059, 0x00000199, 0x00000199, },
	{ 0x1c5a8c, 0x00000099, 0x00000099, 0x000001d9, 0x000001d9, },
	{ 0x1c5a90, 0x000000d9, 0x000000d9, 0x00000019, 0x00000019, },
	{ 0x1c5a94, 0x000000f9, 0x000000f9, 0x00000059, 0x00000059, },
	{ 0x1c5a98, 0x000000f9, 0x000000f9, 0x00000099, 0x00000099, },
	{ 0x1c5a9c, 0x000000f9, 0x000000f9, 0x000000d9, 0x000000d9, },
	{ 0x1c5aa0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5aa4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5aa8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5aac, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ab0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ab4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ab8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5abc, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ac0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ac4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ac8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5acc, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ad0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ad4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ad8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5adc, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ae0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ae4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5ae8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5aec, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5af0, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5af4, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5af8, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5afc, 0x000000f9, 0x000000f9, 0x000000f9, 0x000000f9, },
	{ 0x1c5b00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5b04, 0x00000001, 0x00000001, 0x00000001, 0x00000001, },
	{ 0x1c5b08, 0x00000002, 0x00000002, 0x00000002, 0x00000002, },
	{ 0x1c5b0c, 0x00000003, 0x00000003, 0x00000003, 0x00000003, },
	{ 0x1c5b10, 0x00000004, 0x00000004, 0x00000004, 0x00000004, },
	{ 0x1c5b14, 0x00000005, 0x00000005, 0x00000005, 0x00000005, },
	{ 0x1c5b18, 0x00000008, 0x00000008, 0x00000008, 0x00000008, },
	{ 0x1c5b1c, 0x00000009, 0x00000009, 0x00000009, 0x00000009, },
	{ 0x1c5b20, 0x0000000a, 0x0000000a, 0x0000000a, 0x0000000a, },
	{ 0x1c5b24, 0x0000000b, 0x0000000b, 0x0000000b, 0x0000000b, },
	{ 0x1c5b28, 0x0000000c, 0x0000000c, 0x0000000c, 0x0000000c, },
	{ 0x1c5b2c, 0x0000000d, 0x0000000d, 0x0000000d, 0x0000000d, },
	{ 0x1c5b30, 0x00000010, 0x00000010, 0x00000010, 0x00000010, },
	{ 0x1c5b34, 0x00000011, 0x00000011, 0x00000011, 0x00000011, },
	{ 0x1c5b38, 0x00000012, 0x00000012, 0x00000012, 0x00000012, },
	{ 0x1c5b3c, 0x00000013, 0x00000013, 0x00000013, 0x00000013, },
	{ 0x1c5b40, 0x00000014, 0x00000014, 0x00000014, 0x00000014, },
	{ 0x1c5b44, 0x00000015, 0x00000015, 0x00000015, 0x00000015, },
	{ 0x1c5b48, 0x00000018, 0x00000018, 0x00000018, 0x00000018, },
	{ 0x1c5b4c, 0x00000019, 0x00000019, 0x00000019, 0x00000019, },
	{ 0x1c5b50, 0x0000001a, 0x0000001a, 0x0000001a, 0x0000001a, },
	{ 0x1c5b54, 0x0000001b, 0x0000001b, 0x0000001b, 0x0000001b, },
	{ 0x1c5b58, 0x0000001c, 0x0000001c, 0x0000001c, 0x0000001c, },
	{ 0x1c5b5c, 0x0000001d, 0x0000001d, 0x0000001d, 0x0000001d, },
	{ 0x1c5b60, 0x00000020, 0x00000020, 0x00000020, 0x00000020, },
	{ 0x1c5b64, 0x00000021, 0x00000021, 0x00000021, 0x00000021, },
	{ 0x1c5b68, 0x00000022, 0x00000022, 0x00000022, 0x00000022, },
	{ 0x1c5b6c, 0x00000023, 0x00000023, 0x00000023, 0x00000023, },
	{ 0x1c5b70, 0x00000024, 0x00000024, 0x00000024, 0x00000024, },
	{ 0x1c5b74, 0x00000025, 0x00000025, 0x00000025, 0x00000025, },
	{ 0x1c5b78, 0x00000028, 0x00000028, 0x00000028, 0x00000028, },
	{ 0x1c5b7c, 0x00000029, 0x00000029, 0x00000029, 0x00000029, },
	{ 0x1c5b80, 0x0000002a, 0x0000002a, 0x0000002a, 0x0000002a, },
	{ 0x1c5b84, 0x0000002b, 0x0000002b, 0x0000002b, 0x0000002b, },
	{ 0x1c5b88, 0x0000002c, 0x0000002c, 0x0000002c, 0x0000002c, },
	{ 0x1c5b8c, 0x0000002d, 0x0000002d, 0x0000002d, 0x0000002d, },
	{ 0x1c5b90, 0x00000030, 0x00000030, 0x00000030, 0x00000030, },
	{ 0x1c5b94, 0x00000031, 0x00000031, 0x00000031, 0x00000031, },
	{ 0x1c5b98, 0x00000032, 0x00000032, 0x00000032, 0x00000032, },
	{ 0x1c5b9c, 0x00000033, 0x00000033, 0x00000033, 0x00000033, },
	{ 0x1c5ba0, 0x00000034, 0x00000034, 0x00000034, 0x00000034, },
	{ 0x1c5ba4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5ba8, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bac, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bb0, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bb4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bb8, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bbc, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bc0, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bc4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bc8, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bcc, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bd0, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bd4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bd8, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bdc, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5be0, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5be4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5be8, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bec, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bf0, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bf4, 0x00000035, 0x00000035, 0x00000035, 0x00000035, },
	{ 0x1c5bf8, 0x00000010, 0x00000010, 0x00000010, 0x00000010, },
	{ 0x1c5bfc, 0x0000001a, 0x0000001a, 0x0000001a, 0x0000001a, },
	{ 0x1c5c00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c0c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c10, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c14, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c18, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c1c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c20, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c24, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c28, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c2c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c30, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c34, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c38, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5c3c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5cf0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5cf4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5cf8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c5cfc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6200, 0x00000008, 0x00000008, 0x0000000e, 0x0000000e, },
	{ 0x1c6204, 0x00000440, 0x00000440, 0x00000440, 0x00000440, },
	{ 0x1c6208, 0xd6be4788, 0xd6be4788, 0xd03e4788, 0xd03e4788, },
	{ 0x1c620c, 0x012e8160, 0x012e8160, 0x012a8160, 0x012a8160, },
	{ 0x1c6210, 0x40806333, 0x40806333, 0x40806333, 0x40806333, },
	{ 0x1c6214, 0x00106c10, 0x00106c10, 0x00106c10, 0x00106c10, },
	{ 0x1c6218, 0x009c4060, 0x009c4060, 0x009c4060, 0x009c4060, },
	{ 0x1c621c, 0x1883800a, 0x1883800a, 0x1883800a, 0x1883800a, },
	{ 0x1c6220, 0x018830c6, 0x018830c6, 0x018830c6, 0x018830c6, },
	{ 0x1c6224, 0x00000400, 0x00000400, 0x00000400, 0x00000400, },
	{ 0x1c6228, 0x000009b5, 0x000009b5, 0x000009b5, 0x000009b5, },
	{ 0x1c622c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6230, 0x00000108, 0x00000210, 0x00000210, 0x00000108, },
	{ 0x1c6234, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c6238, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c623c, 0x13c889af, 0x13c889af, 0x13c889af, 0x13c889af, },
	{ 0x1c6240, 0x38490a20, 0x38490a20, 0x38490a20, 0x38490a20, },
	{ 0x1c6244, 0x00007bb6, 0x00007bb6, 0x00007bb6, 0x00007bb6, },
	{ 0x1c6248, 0x0fff3ffc, 0x0fff3ffc, 0x0fff3ffc, 0x0fff3ffc, },
	{ 0x1c624c, 0x00000001, 0x00000001, 0x00000001, 0x00000001, },
	{ 0x1c6250, 0x0000a000, 0x0000a000, 0x0000a000, 0x0000a000, },
	{ 0x1c6254, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6258, 0x0cc75380, 0x0cc75380, 0x0cc75380, 0x0cc75380, },
	{ 0x1c625c, 0x0f0f0f01, 0x0f0f0f01, 0x0f0f0f01, 0x0f0f0f01, },
	{ 0x1c6260, 0xdfa91f01, 0xdfa91f01, 0xdfa91f01, 0xdfa91f01, },
	{ 0x1c6264, 0x00418a11, 0x00418a11, 0x00418a11, 0x00418a11, },
	{ 0x1c6268, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c626c, 0x09249126, 0x09249126, 0x09249126, 0x09249126, },
	{ 0x1c6274, 0x0a1a9caa, 0x0a1a9caa, 0x0a1a7caa, 0x0a1a7caa, },
	{ 0x1c6278, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, },
	{ 0x1c627c, 0x051701ce, 0x051701ce, 0x051701ce, 0x051701ce, },
	{ 0x1c6300, 0x18010000, 0x18010000, 0x18010000, 0x18010000, },
	{ 0x1c6304, 0x30032602, 0x30032602, 0x2e032402, 0x2e032402, },
	{ 0x1c6308, 0x48073e06, 0x48073e06, 0x4a0a3c06, 0x4a0a3c06, },
	{ 0x1c630c, 0x560b4c0a, 0x560b4c0a, 0x621a540b, 0x621a540b, },
	{ 0x1c6310, 0x641a600f, 0x641a600f, 0x764f6c1b, 0x764f6c1b, },
	{ 0x1c6314, 0x7a4f6e1b, 0x7a4f6e1b, 0x845b7a5a, 0x845b7a5a, },
	{ 0x1c6318, 0x8c5b7e5a, 0x8c5b7e5a, 0x950f8ccf, 0x950f8ccf, },
	{ 0x1c631c, 0x9d0f96cf, 0x9d0f96cf, 0xa5cf9b4f, 0xa5cf9b4f, },
	{ 0x1c6320, 0xb51fa69f, 0xb51fa69f, 0xbddfaf1f, 0xbddfaf1f, },
	{ 0x1c6324, 0xcb3fbd07, 0xcb3fbcbf, 0xd1ffc93f, 0xd1ffc93f, },
	{ 0x1c6328, 0x0000d7bf, 0x0000d7bf, 0x00000000, 0x00000000, },
	{ 0x1c632c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6330, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6334, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6338, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c633c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6340, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6344, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c6348, 0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff, },
	{ 0x1c634c, 0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff, },
	{ 0x1c6350, 0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff, },
	{ 0x1c6354, 0x0003ffff, 0x0003ffff, 0x0003ffff, 0x0003ffff, },
	{ 0x1c6358, 0x79a8aa1f, 0x79a8aa1f, 0x79a8aa1f, 0x79a8aa1f, },
	{ 0x1c6388, 0x08000000, 0x08000000, 0x08000000, 0x08000000, },
	{ 0x1c638c, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c6390, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c6394, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, },
	{ 0x1c6398, 0x000001ce, 0x000001ce, 0x000001ce, 0x000001ce, },
	{ 0x1c639c, 0x00000007, 0x00000007, 0x00000007, 0x00000007, },
	{ 0x1c63a0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63a4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63a8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63ac, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63b0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63b4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63b8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63bc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63c0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63c4, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63c8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63cc, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c63d0, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c63d4, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, 0x3f3f3f3f, },
	{ 0x1c63d8, 0x00000000, 0x00000000, 0x00000000, 0x00000000, },
	{ 0x1c63dc, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, 0x1ce739ce, },
	{ 0x1c63e0, 0x000000c0, 0x000000c0, 0x000000c0, 0x000000c0, },
	{ 0x1c6848, 0x00180a65, 0x00180a65, 0x00180a68, 0x00180a68, },
	{ 0x1c6920, 0x0510001c, 0x0510001c, 0x0510001c, 0x0510001c, },
	{ 0x1c6960, 0x00009b40, 0x00009b40, 0x00009b40, 0x00009b40, },
	{ 0x1c720c, 0x012e8160, 0x012e8160, 0x012a8160, 0x012a8160, },
	{ 0x1c726c, 0x09249126, 0x09249126, 0x09249126, 0x09249126, },
	{ 0x1c7848, 0x00180a65, 0x00180a65, 0x00180a68, 0x00180a68, },
	{ 0x1c7920, 0x0510001c, 0x0510001c, 0x0510001c, 0x0510001c, },
	{ 0x1c7960, 0x00009b40, 0x00009b40, 0x00009b40, 0x00009b40, },
	{ 0x1c820c, 0x012e8160, 0x012e8160, 0x012a8160, 0x012a8160, },
	{ 0x1c826c, 0x09249126, 0x09249126, 0x09249126, 0x09249126, },
/*	{ 0x1c8864, 0x0001ce00, 0x0001ce00, 0x0001ce00, 0x0001ce00, }, */
	{ 0x1c8864, 0x0001c600, 0x0001c600, 0x0001c600, 0x0001c600, },
	{ 0x1c895c, 0x004b6a8e, 0x004b6a8e, 0x004b6a8e, 0x004b6a8e, },
	{ 0x1c8968, 0x000003ce, 0x000003ce, 0x000003ce, 0x000003ce, },
	{ 0x1c89bc, 0x00181400, 0x00181400, 0x00181400, 0x00181400, },
	{ 0x1c9270, 0x00820820, 0x00820820, 0x00820820, 0x00820820, },
	{ 0x1c935c, 0x066c420f, 0x066c420f, 0x066c420f, 0x066c420f, },
	{ 0x1c9360, 0x0f282207, 0x0f282207, 0x0f282207, 0x0f282207, },
	{ 0x1c9364, 0x17601685, 0x17601685, 0x17601685, 0x17601685, },
	{ 0x1c9368, 0x1f801104, 0x1f801104, 0x1f801104, 0x1f801104, },
	{ 0x1c936c, 0x37a00c03, 0x37a00c03, 0x37a00c03, 0x37a00c03, },
	{ 0x1c9370, 0x3fc40883, 0x3fc40883, 0x3fc40883, 0x3fc40883, },
	{ 0x1c9374, 0x57c00803, 0x57c00803, 0x57c00803, 0x57c00803, },
	{ 0x1c9378, 0x5fd80682, 0x5fd80682, 0x5fd80682, 0x5fd80682, },
	{ 0x1c937c, 0x7fe00482, 0x7fe00482, 0x7fe00482, 0x7fe00482, },
	{ 0x1c9380, 0x7f3c7bba, 0x7f3c7bba, 0x7f3c7bba, 0x7f3c7bba, },
	{ 0x1c9384, 0xf3307ff0, 0xf3307ff0, 0xf3307ff0, 0xf3307ff0, }
};

/*
 * wook up a cewtain wegistew in aw5416_phy_init[] and wetuwn the init. vawue
 * fow the band and bandwidth given. Wetuwn 0 if wegistew addwess not found.
 */
static u32 caww9170_def_vaw(u32 weg, boow is_2ghz, boow is_40mhz)
{
	unsigned int i;
	fow (i = 0; i < AWWAY_SIZE(aw5416_phy_init); i++) {
		if (aw5416_phy_init[i].weg != weg)
			continue;

		if (is_2ghz) {
			if (is_40mhz)
				wetuwn aw5416_phy_init[i]._2ghz_40;
			ewse
				wetuwn aw5416_phy_init[i]._2ghz_20;
		} ewse {
			if (is_40mhz)
				wetuwn aw5416_phy_init[i]._5ghz_40;
			ewse
				wetuwn aw5416_phy_init[i]._5ghz_20;
		}
	}
	wetuwn 0;
}

/*
 * initiawize some phy wegs fwom eepwom vawues in modaw_headew[]
 * acc. to band and bandwidth
 */
static int caww9170_init_phy_fwom_eepwom(stwuct aw9170 *aw,
				boow is_2ghz, boow is_40mhz)
{
	static const u8 xpd2pd[16] = {
		0x2, 0x2, 0x2, 0x1, 0x2, 0x2, 0x6, 0x2,
		0x2, 0x3, 0x7, 0x2, 0xb, 0x2, 0x2, 0x2
	};
	/* pointew to the modaw_headew acc. to band */
	stwuct aw9170_eepwom_modaw *m = &aw->eepwom.modaw_headew[is_2ghz];
	u32 vaw;

	caww9170_wegwwite_begin(aw);

	/* ant common contwow (index 0) */
	caww9170_wegwwite(AW9170_PHY_WEG_SWITCH_COM,
		we32_to_cpu(m->antCtwwCommon));

	/* ant contwow chain 0 (index 1) */
	caww9170_wegwwite(AW9170_PHY_WEG_SWITCH_CHAIN_0,
		we32_to_cpu(m->antCtwwChain[0]));

	/* ant contwow chain 2 (index 2) */
	caww9170_wegwwite(AW9170_PHY_WEG_SWITCH_CHAIN_2,
		we32_to_cpu(m->antCtwwChain[1]));

	/* SwSettwe (index 3) */
	if (!is_40mhz) {
		vaw = caww9170_def_vaw(AW9170_PHY_WEG_SETTWING,
				     is_2ghz, is_40mhz);
		SET_VAW(AW9170_PHY_SETTWING_SWITCH, vaw, m->switchSettwing);
		caww9170_wegwwite(AW9170_PHY_WEG_SETTWING, vaw);
	}

	/* adcDesiwed, pdaDesiwed (index 4) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_DESIWED_SZ, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_DESIWED_SZ_PGA, vaw, m->pgaDesiwedSize);
	SET_VAW(AW9170_PHY_DESIWED_SZ_ADC, vaw, m->adcDesiwedSize);
	caww9170_wegwwite(AW9170_PHY_WEG_DESIWED_SZ, vaw);

	/* TxEndToXpaOff, TxFwameToXpaOn (index 5) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_WF_CTW4, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_WF_CTW4_TX_END_XPAB_OFF, vaw, m->txEndToXpaOff);
	SET_VAW(AW9170_PHY_WF_CTW4_TX_END_XPAA_OFF, vaw, m->txEndToXpaOff);
	SET_VAW(AW9170_PHY_WF_CTW4_FWAME_XPAB_ON, vaw, m->txFwameToXpaOn);
	SET_VAW(AW9170_PHY_WF_CTW4_FWAME_XPAA_ON, vaw, m->txFwameToXpaOn);
	caww9170_wegwwite(AW9170_PHY_WEG_WF_CTW4, vaw);

	/* TxEndToWxOn (index 6) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_WF_CTW3, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_WF_CTW3_TX_END_TO_A2_WX_ON, vaw, m->txEndToWxOn);
	caww9170_wegwwite(AW9170_PHY_WEG_WF_CTW3, vaw);

	/* thwesh62 (index 7) */
	vaw = caww9170_def_vaw(0x1c8864, is_2ghz, is_40mhz);
	vaw = (vaw & ~0x7f000) | (m->thwesh62 << 12);
	caww9170_wegwwite(0x1c8864, vaw);

	/* tx/wx attenuation chain 0 (index 8) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_WXGAIN, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_WXGAIN_TXWX_ATTEN, vaw, m->txWxAttenCh[0]);
	caww9170_wegwwite(AW9170_PHY_WEG_WXGAIN, vaw);

	/* tx/wx attenuation chain 2 (index 9) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_WXGAIN_CHAIN_2,
			       is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_WXGAIN_TXWX_ATTEN, vaw, m->txWxAttenCh[1]);
	caww9170_wegwwite(AW9170_PHY_WEG_WXGAIN_CHAIN_2, vaw);

	/* tx/wx mawgin chain 0 (index 10) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_GAIN_2GHZ, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_GAIN_2GHZ_WXTX_MAWGIN, vaw, m->wxTxMawginCh[0]);
	/* bsw mawgin chain 0 fow 5GHz onwy */
	if (!is_2ghz)
		SET_VAW(AW9170_PHY_GAIN_2GHZ_BSW_MAWGIN, vaw, m->bswMawgin[0]);
	caww9170_wegwwite(AW9170_PHY_WEG_GAIN_2GHZ, vaw);

	/* tx/wx mawgin chain 2 (index 11) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_GAIN_2GHZ_CHAIN_2,
			       is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_GAIN_2GHZ_WXTX_MAWGIN, vaw, m->wxTxMawginCh[1]);
	caww9170_wegwwite(AW9170_PHY_WEG_GAIN_2GHZ_CHAIN_2, vaw);

	/* iqCaww, iqCawwq chain 0 (index 12) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_TIMING_CTWW4(0),
			       is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF, vaw, m->iqCawICh[0]);
	SET_VAW(AW9170_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF, vaw, m->iqCawQCh[0]);
	caww9170_wegwwite(AW9170_PHY_WEG_TIMING_CTWW4(0), vaw);

	/* iqCaww, iqCawwq chain 2 (index 13) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_TIMING_CTWW4(2),
			       is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_TIMING_CTWW4_IQCOWW_Q_I_COFF, vaw, m->iqCawICh[1]);
	SET_VAW(AW9170_PHY_TIMING_CTWW4_IQCOWW_Q_Q_COFF, vaw, m->iqCawQCh[1]);
	caww9170_wegwwite(AW9170_PHY_WEG_TIMING_CTWW4(2), vaw);

	/* xpd gain mask (index 14) */
	vaw = caww9170_def_vaw(AW9170_PHY_WEG_TPCWG1, is_2ghz, is_40mhz);
	SET_VAW(AW9170_PHY_TPCWG1_PD_GAIN_1, vaw,
		xpd2pd[m->xpdGain & 0xf] & 3);
	SET_VAW(AW9170_PHY_TPCWG1_PD_GAIN_2, vaw,
		xpd2pd[m->xpdGain & 0xf] >> 2);
	caww9170_wegwwite(AW9170_PHY_WEG_TPCWG1, vaw);

	caww9170_wegwwite(AW9170_PHY_WEG_WX_CHAINMASK, aw->eepwom.wx_mask);
	caww9170_wegwwite(AW9170_PHY_WEG_CAW_CHAINMASK, aw->eepwom.wx_mask);

	caww9170_wegwwite_finish();
	wetuwn caww9170_wegwwite_wesuwt();
}

static int caww9170_init_phy(stwuct aw9170 *aw, enum nw80211_band band)
{
	int i, eww;
	u32 vaw;
	boow is_2ghz = band == NW80211_BAND_2GHZ;
	boow is_40mhz = conf_is_ht40(&aw->hw->conf);

	caww9170_wegwwite_begin(aw);

	fow (i = 0; i < AWWAY_SIZE(aw5416_phy_init); i++) {
		if (is_40mhz) {
			if (is_2ghz)
				vaw = aw5416_phy_init[i]._2ghz_40;
			ewse
				vaw = aw5416_phy_init[i]._5ghz_40;
		} ewse {
			if (is_2ghz)
				vaw = aw5416_phy_init[i]._2ghz_20;
			ewse
				vaw = aw5416_phy_init[i]._5ghz_20;
		}

		caww9170_wegwwite(aw5416_phy_init[i].weg, vaw);
	}

	caww9170_wegwwite_finish();
	eww = caww9170_wegwwite_wesuwt();
	if (eww)
		wetuwn eww;

	eww = caww9170_init_phy_fwom_eepwom(aw, is_2ghz, is_40mhz);
	if (eww)
		wetuwn eww;

	eww = caww9170_init_powew_caw(aw);
	if (eww)
		wetuwn eww;

	if (!aw->fw.hw_countews) {
		eww = caww9170_wwite_weg(aw, AW9170_PWW_WEG_PWW_ADDAC,
					 is_2ghz ? 0x5163 : 0x5143);
	}

	wetuwn eww;
}

stwuct caww9170_wf_initvaws {
	u32 weg, _5ghz, _2ghz;
};

static stwuct caww9170_wf_initvaws caww9170_wf_initvaw[] = {
	/* bank 0 */
	{ 0x1c58b0, 0x1e5795e5, 0x1e5795e5},
	{ 0x1c58e0, 0x02008020, 0x02008020},
	/* bank 1 */
	{ 0x1c58b0, 0x02108421, 0x02108421},
	{ 0x1c58ec, 0x00000008, 0x00000008},
	/* bank 2 */
	{ 0x1c58b0, 0x0e73ff17, 0x0e73ff17},
	{ 0x1c58e0, 0x00000420, 0x00000420},
	/* bank 3 */
	{ 0x1c58f0, 0x01400018, 0x01c00018},
	/* bank 4 */
	{ 0x1c58b0, 0x000001a1, 0x000001a1},
	{ 0x1c58e8, 0x00000001, 0x00000001},
	/* bank 5 */
	{ 0x1c58b0, 0x00000013, 0x00000013},
	{ 0x1c58e4, 0x00000002, 0x00000002},
	/* bank 6 */
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00004000, 0x00004000},
	{ 0x1c58b0, 0x00006c00, 0x00006c00},
	{ 0x1c58b0, 0x00002c00, 0x00002c00},
	{ 0x1c58b0, 0x00004800, 0x00004800},
	{ 0x1c58b0, 0x00004000, 0x00004000},
	{ 0x1c58b0, 0x00006000, 0x00006000},
	{ 0x1c58b0, 0x00001000, 0x00001000},
	{ 0x1c58b0, 0x00004000, 0x00004000},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00087c00, 0x00087c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00005400, 0x00005400},
	{ 0x1c58b0, 0x00000c00, 0x00000c00},
	{ 0x1c58b0, 0x00001800, 0x00001800},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00006c00, 0x00006c00},
	{ 0x1c58b0, 0x00006c00, 0x00006c00},
	{ 0x1c58b0, 0x00007c00, 0x00007c00},
	{ 0x1c58b0, 0x00002c00, 0x00002c00},
	{ 0x1c58b0, 0x00003c00, 0x00003c00},
	{ 0x1c58b0, 0x00003800, 0x00003800},
	{ 0x1c58b0, 0x00001c00, 0x00001c00},
	{ 0x1c58b0, 0x00000800, 0x00000800},
	{ 0x1c58b0, 0x00000408, 0x00000408},
	{ 0x1c58b0, 0x00004c15, 0x00004c15},
	{ 0x1c58b0, 0x00004188, 0x00004188},
	{ 0x1c58b0, 0x0000201e, 0x0000201e},
	{ 0x1c58b0, 0x00010408, 0x00010408},
	{ 0x1c58b0, 0x00000801, 0x00000801},
	{ 0x1c58b0, 0x00000c08, 0x00000c08},
	{ 0x1c58b0, 0x0000181e, 0x0000181e},
	{ 0x1c58b0, 0x00001016, 0x00001016},
	{ 0x1c58b0, 0x00002800, 0x00002800},
	{ 0x1c58b0, 0x00004010, 0x00004010},
	{ 0x1c58b0, 0x0000081c, 0x0000081c},
	{ 0x1c58b0, 0x00000115, 0x00000115},
	{ 0x1c58b0, 0x00000015, 0x00000015},
	{ 0x1c58b0, 0x00000066, 0x00000066},
	{ 0x1c58b0, 0x0000001c, 0x0000001c},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000004, 0x00000004},
	{ 0x1c58b0, 0x00000015, 0x00000015},
	{ 0x1c58b0, 0x0000001f, 0x0000001f},
	{ 0x1c58e0, 0x00000000, 0x00000400},
	/* bank 7 */
	{ 0x1c58b0, 0x000000a0, 0x000000a0},
	{ 0x1c58b0, 0x00000000, 0x00000000},
	{ 0x1c58b0, 0x00000040, 0x00000040},
	{ 0x1c58f0, 0x0000001c, 0x0000001c},
};

static int caww9170_init_wf_banks_0_7(stwuct aw9170 *aw, boow band5ghz)
{
	int eww, i;

	caww9170_wegwwite_begin(aw);

	fow (i = 0; i < AWWAY_SIZE(caww9170_wf_initvaw); i++)
		caww9170_wegwwite(caww9170_wf_initvaw[i].weg,
				  band5ghz ? caww9170_wf_initvaw[i]._5ghz
					   : caww9170_wf_initvaw[i]._2ghz);

	caww9170_wegwwite_finish();
	eww = caww9170_wegwwite_wesuwt();
	if (eww)
		wiphy_eww(aw->hw->wiphy, "wf init faiwed\n");

	wetuwn eww;
}

stwuct caww9170_phy_fweq_pawams {
	u8 coeff_exp;
	u16 coeff_man;
	u8 coeff_exp_shgi;
	u16 coeff_man_shgi;
};

enum caww9170_bw {
	CAWW9170_BW_20,
	CAWW9170_BW_40_BEWOW,
	CAWW9170_BW_40_ABOVE,

	__CAWW9170_NUM_BW,
};

stwuct caww9170_phy_fweq_entwy {
	u16 fweq;
	stwuct caww9170_phy_fweq_pawams pawams[__CAWW9170_NUM_BW];
};

/* NB: must be in sync with channew tabwes in main! */
static const stwuct caww9170_phy_fweq_entwy caww9170_phy_fweq_pawams[] = {
/*
 *	fweq,
 *		20MHz,
 *		40MHz (bewow),
 *		40Mhz (above),
 */
	{ 2412, {
		{ 3, 21737, 3, 19563, },
		{ 3, 21827, 3, 19644, },
		{ 3, 21647, 3, 19482, },
	} },
	{ 2417, {
		{ 3, 21692, 3, 19523, },
		{ 3, 21782, 3, 19604, },
		{ 3, 21602, 3, 19442, },
	} },
	{ 2422, {
		{ 3, 21647, 3, 19482, },
		{ 3, 21737, 3, 19563, },
		{ 3, 21558, 3, 19402, },
	} },
	{ 2427, {
		{ 3, 21602, 3, 19442, },
		{ 3, 21692, 3, 19523, },
		{ 3, 21514, 3, 19362, },
	} },
	{ 2432, {
		{ 3, 21558, 3, 19402, },
		{ 3, 21647, 3, 19482, },
		{ 3, 21470, 3, 19323, },
	} },
	{ 2437, {
		{ 3, 21514, 3, 19362, },
		{ 3, 21602, 3, 19442, },
		{ 3, 21426, 3, 19283, },
	} },
	{ 2442, {
		{ 3, 21470, 3, 19323, },
		{ 3, 21558, 3, 19402, },
		{ 3, 21382, 3, 19244, },
	} },
	{ 2447, {
		{ 3, 21426, 3, 19283, },
		{ 3, 21514, 3, 19362, },
		{ 3, 21339, 3, 19205, },
	} },
	{ 2452, {
		{ 3, 21382, 3, 19244, },
		{ 3, 21470, 3, 19323, },
		{ 3, 21295, 3, 19166, },
	} },
	{ 2457, {
		{ 3, 21339, 3, 19205, },
		{ 3, 21426, 3, 19283, },
		{ 3, 21252, 3, 19127, },
	} },
	{ 2462, {
		{ 3, 21295, 3, 19166, },
		{ 3, 21382, 3, 19244, },
		{ 3, 21209, 3, 19088, },
	} },
	{ 2467, {
		{ 3, 21252, 3, 19127, },
		{ 3, 21339, 3, 19205, },
		{ 3, 21166, 3, 19050, },
	} },
	{ 2472, {
		{ 3, 21209, 3, 19088, },
		{ 3, 21295, 3, 19166, },
		{ 3, 21124, 3, 19011, },
	} },
	{ 2484, {
		{ 3, 21107, 3, 18996, },
		{ 3, 21192, 3, 19073, },
		{ 3, 21022, 3, 18920, },
	} },
	{ 4920, {
		{ 4, 21313, 4, 19181, },
		{ 4, 21356, 4, 19220, },
		{ 4, 21269, 4, 19142, },
	} },
	{ 4940, {
		{ 4, 21226, 4, 19104, },
		{ 4, 21269, 4, 19142, },
		{ 4, 21183, 4, 19065, },
	} },
	{ 4960, {
		{ 4, 21141, 4, 19027, },
		{ 4, 21183, 4, 19065, },
		{ 4, 21098, 4, 18988, },
	} },
	{ 4980, {
		{ 4, 21056, 4, 18950, },
		{ 4, 21098, 4, 18988, },
		{ 4, 21014, 4, 18912, },
	} },
	{ 5040, {
		{ 4, 20805, 4, 18725, },
		{ 4, 20846, 4, 18762, },
		{ 4, 20764, 4, 18687, },
	} },
	{ 5060, {
		{ 4, 20723, 4, 18651, },
		{ 4, 20764, 4, 18687, },
		{ 4, 20682, 4, 18614, },
	} },
	{ 5080, {
		{ 4, 20641, 4, 18577, },
		{ 4, 20682, 4, 18614, },
		{ 4, 20601, 4, 18541, },
	} },
	{ 5180, {
		{ 4, 20243, 4, 18219, },
		{ 4, 20282, 4, 18254, },
		{ 4, 20204, 4, 18183, },
	} },
	{ 5200, {
		{ 4, 20165, 4, 18148, },
		{ 4, 20204, 4, 18183, },
		{ 4, 20126, 4, 18114, },
	} },
	{ 5220, {
		{ 4, 20088, 4, 18079, },
		{ 4, 20126, 4, 18114, },
		{ 4, 20049, 4, 18044, },
	} },
	{ 5240, {
		{ 4, 20011, 4, 18010, },
		{ 4, 20049, 4, 18044, },
		{ 4, 19973, 4, 17976, },
	} },
	{ 5260, {
		{ 4, 19935, 4, 17941, },
		{ 4, 19973, 4, 17976, },
		{ 4, 19897, 4, 17907, },
	} },
	{ 5280, {
		{ 4, 19859, 4, 17873, },
		{ 4, 19897, 4, 17907, },
		{ 4, 19822, 4, 17840, },
	} },
	{ 5300, {
		{ 4, 19784, 4, 17806, },
		{ 4, 19822, 4, 17840, },
		{ 4, 19747, 4, 17772, },
	} },
	{ 5320, {
		{ 4, 19710, 4, 17739, },
		{ 4, 19747, 4, 17772, },
		{ 4, 19673, 4, 17706, },
	} },
	{ 5500, {
		{ 4, 19065, 4, 17159, },
		{ 4, 19100, 4, 17190, },
		{ 4, 19030, 4, 17127, },
	} },
	{ 5520, {
		{ 4, 18996, 4, 17096, },
		{ 4, 19030, 4, 17127, },
		{ 4, 18962, 4, 17065, },
	} },
	{ 5540, {
		{ 4, 18927, 4, 17035, },
		{ 4, 18962, 4, 17065, },
		{ 4, 18893, 4, 17004, },
	} },
	{ 5560, {
		{ 4, 18859, 4, 16973, },
		{ 4, 18893, 4, 17004, },
		{ 4, 18825, 4, 16943, },
	} },
	{ 5580, {
		{ 4, 18792, 4, 16913, },
		{ 4, 18825, 4, 16943, },
		{ 4, 18758, 4, 16882, },
	} },
	{ 5600, {
		{ 4, 18725, 4, 16852, },
		{ 4, 18758, 4, 16882, },
		{ 4, 18691, 4, 16822, },
	} },
	{ 5620, {
		{ 4, 18658, 4, 16792, },
		{ 4, 18691, 4, 16822, },
		{ 4, 18625, 4, 16762, },
	} },
	{ 5640, {
		{ 4, 18592, 4, 16733, },
		{ 4, 18625, 4, 16762, },
		{ 4, 18559, 4, 16703, },
	} },
	{ 5660, {
		{ 4, 18526, 4, 16673, },
		{ 4, 18559, 4, 16703, },
		{ 4, 18493, 4, 16644, },
	} },
	{ 5680, {
		{ 4, 18461, 4, 16615, },
		{ 4, 18493, 4, 16644, },
		{ 4, 18428, 4, 16586, },
	} },
	{ 5700, {
		{ 4, 18396, 4, 16556, },
		{ 4, 18428, 4, 16586, },
		{ 4, 18364, 4, 16527, },
	} },
	{ 5745, {
		{ 4, 18252, 4, 16427, },
		{ 4, 18284, 4, 16455, },
		{ 4, 18220, 4, 16398, },
	} },
	{ 5765, {
		{ 4, 18189, 5, 32740, },
		{ 4, 18220, 4, 16398, },
		{ 4, 18157, 5, 32683, },
	} },
	{ 5785, {
		{ 4, 18126, 5, 32626, },
		{ 4, 18157, 5, 32683, },
		{ 4, 18094, 5, 32570, },
	} },
	{ 5805, {
		{ 4, 18063, 5, 32514, },
		{ 4, 18094, 5, 32570, },
		{ 4, 18032, 5, 32458, },
	} },
	{ 5825, {
		{ 4, 18001, 5, 32402, },
		{ 4, 18032, 5, 32458, },
		{ 4, 17970, 5, 32347, },
	} },
	{ 5170, {
		{ 4, 20282, 4, 18254, },
		{ 4, 20321, 4, 18289, },
		{ 4, 20243, 4, 18219, },
	} },
	{ 5190, {
		{ 4, 20204, 4, 18183, },
		{ 4, 20243, 4, 18219, },
		{ 4, 20165, 4, 18148, },
	} },
	{ 5210, {
		{ 4, 20126, 4, 18114, },
		{ 4, 20165, 4, 18148, },
		{ 4, 20088, 4, 18079, },
	} },
	{ 5230, {
		{ 4, 20049, 4, 18044, },
		{ 4, 20088, 4, 18079, },
		{ 4, 20011, 4, 18010, },
	} },
};

static int caww9170_init_wf_bank4_pww(stwuct aw9170 *aw, boow band5ghz,
				      u32 fweq, enum caww9170_bw bw)
{
	int eww;
	u32 d0, d1, td0, td1, fd0, fd1;
	u8 chansew;
	u8 wefsew0 = 1, wefsew1 = 0;
	u8 wf_synth = 0;

	switch (bw) {
	case CAWW9170_BW_40_ABOVE:
		fweq += 10;
		bweak;
	case CAWW9170_BW_40_BEWOW:
		fweq -= 10;
		bweak;
	case CAWW9170_BW_20:
		bweak;
	defauwt:
		BUG();
		wetuwn -ENOSYS;
	}

	if (band5ghz) {
		if (fweq % 10) {
			chansew = (fweq - 4800) / 5;
		} ewse {
			chansew = ((fweq - 4800) / 10) * 2;
			wefsew0 = 0;
			wefsew1 = 1;
		}
		chansew = bitwev8(chansew);
	} ewse {
		if (fweq == 2484) {
			chansew = 10 + (fweq - 2274) / 5;
			wf_synth = 1;
		} ewse
			chansew = 16 + (fweq - 2272) / 5;
		chansew *= 4;
		chansew = bitwev8(chansew);
	}

	d1 =	chansew;
	d0 =	0x21 |
		wefsew0 << 3 |
		wefsew1 << 2 |
		wf_synth << 1;
	td0 =	d0 & 0x1f;
	td1 =	d1 & 0x1f;
	fd0 =	td1 << 5 | td0;

	td0 =	(d0 >> 5) & 0x7;
	td1 =	(d1 >> 5) & 0x7;
	fd1 =	td1 << 5 | td0;

	caww9170_wegwwite_begin(aw);

	caww9170_wegwwite(0x1c58b0, fd0);
	caww9170_wegwwite(0x1c58e8, fd1);

	caww9170_wegwwite_finish();
	eww = caww9170_wegwwite_wesuwt();
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct caww9170_phy_fweq_pawams *
caww9170_get_hw_dyn_pawams(stwuct ieee80211_channew *channew,
			   enum caww9170_bw bw)
{
	unsigned int chanidx = 0;
	u16 fweq = 2412;

	if (channew) {
		chanidx = channew->hw_vawue;
		fweq = channew->centew_fweq;
	}

	BUG_ON(chanidx >= AWWAY_SIZE(caww9170_phy_fweq_pawams));

	BUIWD_BUG_ON(__CAWW9170_NUM_BW != 3);

	WAWN_ON(caww9170_phy_fweq_pawams[chanidx].fweq != fweq);

	wetuwn &caww9170_phy_fweq_pawams[chanidx].pawams[bw];
}

static int caww9170_find_fweq_idx(int nfweqs, u8 *fweqs, u8 f)
{
	int idx = nfweqs - 2;

	whiwe (idx >= 0) {
		if (f >= fweqs[idx])
			wetuwn idx;
		idx--;
	}

	wetuwn 0;
}

static s32 caww9170_intewpowate_s32(s32 x, s32 x1, s32 y1, s32 x2, s32 y2)
{
	/* nothing to intewpowate, it's howizontaw */
	if (y2 == y1)
		wetuwn y1;

	/* check if we hit one of the edges */
	if (x == x1)
		wetuwn y1;
	if (x == x2)
		wetuwn y2;

	/* x1 == x2 is bad, hopefuwwy == x */
	if (x2 == x1)
		wetuwn y1;

	wetuwn y1 + (((y2 - y1) * (x - x1)) / (x2 - x1));
}

static u8 caww9170_intewpowate_u8(u8 x, u8 x1, u8 y1, u8 x2, u8 y2)
{
#define SHIFT		8
	s32 y;

	y = caww9170_intewpowate_s32(x << SHIFT, x1 << SHIFT,
		y1 << SHIFT, x2 << SHIFT, y2 << SHIFT);

	/*
	 * XXX: unwwap this expwession
	 *	Isn't it just DIV_WOUND_UP(y, 1<<SHIFT)?
	 *	Can we wewy on the compiwew to optimise away the div?
	 */
	wetuwn (y >> SHIFT) + ((y & (1 << (SHIFT - 1))) >> (SHIFT - 1));
#undef SHIFT
}

static u8 caww9170_intewpowate_vaw(u8 x, u8 *x_awway, u8 *y_awway)
{
	int i;

	fow (i = 0; i < 3; i++) {
		if (x <= x_awway[i + 1])
			bweak;
	}

	wetuwn caww9170_intewpowate_u8(x, x_awway[i], y_awway[i],
		x_awway[i + 1], y_awway[i + 1]);
}

static int caww9170_set_fweq_caw_data(stwuct aw9170 *aw,
	stwuct ieee80211_channew *channew)
{
	u8 *caw_fweq_piew;
	u8 vpds[2][AW5416_PD_GAIN_ICEPTS];
	u8 pwws[2][AW5416_PD_GAIN_ICEPTS];
	int chain, idx, i;
	u32 phy_data = 0;
	u8 f, tmp;

	switch (channew->band) {
	case NW80211_BAND_2GHZ:
		f = channew->centew_fweq - 2300;
		caw_fweq_piew = aw->eepwom.caw_fweq_piew_2G;
		i = AW5416_NUM_2G_CAW_PIEWS - 1;
		bweak;

	case NW80211_BAND_5GHZ:
		f = (channew->centew_fweq - 4800) / 5;
		caw_fweq_piew = aw->eepwom.caw_fweq_piew_5G;
		i = AW5416_NUM_5G_CAW_PIEWS - 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	fow (; i >= 0; i--) {
		if (caw_fweq_piew[i] != 0xff)
			bweak;
	}
	if (i < 0)
		wetuwn -EINVAW;

	idx = caww9170_find_fweq_idx(i, caw_fweq_piew, f);

	caww9170_wegwwite_begin(aw);

	fow (chain = 0; chain < AW5416_MAX_CHAINS; chain++) {
		fow (i = 0; i < AW5416_PD_GAIN_ICEPTS; i++) {
			stwuct aw9170_cawibwation_data_pew_fweq *caw_piew_data;
			int j;

			switch (channew->band) {
			case NW80211_BAND_2GHZ:
				caw_piew_data = &aw->eepwom.
					caw_piew_data_2G[chain][idx];
				bweak;

			case NW80211_BAND_5GHZ:
				caw_piew_data = &aw->eepwom.
					caw_piew_data_5G[chain][idx];
				bweak;

			defauwt:
				wetuwn -EINVAW;
			}

			fow (j = 0; j < 2; j++) {
				vpds[j][i] = caww9170_intewpowate_u8(f,
					caw_fweq_piew[idx],
					caw_piew_data->vpd_pdg[j][i],
					caw_fweq_piew[idx + 1],
					caw_piew_data[1].vpd_pdg[j][i]);

				pwws[j][i] = caww9170_intewpowate_u8(f,
					caw_fweq_piew[idx],
					caw_piew_data->pww_pdg[j][i],
					caw_fweq_piew[idx + 1],
					caw_piew_data[1].pww_pdg[j][i]) / 2;
			}
		}

		fow (i = 0; i < 76; i++) {
			if (i < 25) {
				tmp = caww9170_intewpowate_vaw(i, &pwws[0][0],
							       &vpds[0][0]);
			} ewse {
				tmp = caww9170_intewpowate_vaw(i - 12,
							       &pwws[1][0],
							       &vpds[1][0]);
			}

			phy_data |= tmp << ((i & 3) << 3);
			if ((i & 3) == 3) {
				caww9170_wegwwite(0x1c6280 + chain * 0x1000 +
						  (i & ~3), phy_data);
				phy_data = 0;
			}
		}

		fow (i = 19; i < 32; i++)
			caww9170_wegwwite(0x1c6280 + chain * 0x1000 + (i << 2),
					  0x0);
	}

	caww9170_wegwwite_finish();
	wetuwn caww9170_wegwwite_wesuwt();
}

static u8 caww9170_get_max_edge_powew(stwuct aw9170 *aw,
	u32 fweq, stwuct aw9170_cawctw_edges edges[])
{
	int i;
	u8 wc = AW5416_MAX_WATE_POWEW;
	u8 f;
	if (fweq < 3000)
		f = fweq - 2300;
	ewse
		f = (fweq - 4800) / 5;

	fow (i = 0; i < AW5416_NUM_BAND_EDGES; i++) {
		if (edges[i].channew == 0xff)
			bweak;
		if (f == edges[i].channew) {
			/* exact fweq match */
			wc = edges[i].powew_fwags & ~AW9170_CAWCTW_EDGE_FWAGS;
			bweak;
		}
		if (i > 0 && f < edges[i].channew) {
			if (f > edges[i - 1].channew &&
			    edges[i - 1].powew_fwags &
			    AW9170_CAWCTW_EDGE_FWAGS) {
				/* wowew channew has the inband fwag set */
				wc = edges[i - 1].powew_fwags &
					~AW9170_CAWCTW_EDGE_FWAGS;
			}
			bweak;
		}
	}

	if (i == AW5416_NUM_BAND_EDGES) {
		if (f > edges[i - 1].channew &&
		    edges[i - 1].powew_fwags & AW9170_CAWCTW_EDGE_FWAGS) {
			/* wowew channew has the inband fwag set */
			wc = edges[i - 1].powew_fwags &
				~AW9170_CAWCTW_EDGE_FWAGS;
		}
	}
	wetuwn wc;
}

static u8 caww9170_get_heavy_cwip(stwuct aw9170 *aw, u32 fweq,
	enum caww9170_bw bw, stwuct aw9170_cawctw_edges edges[])
{
	u8 f;
	int i;
	u8 wc = 0;

	if (fweq < 3000)
		f = fweq - 2300;
	ewse
		f = (fweq - 4800) / 5;

	if (bw == CAWW9170_BW_40_BEWOW || bw == CAWW9170_BW_40_ABOVE)
		wc |= 0xf0;

	fow (i = 0; i < AW5416_NUM_BAND_EDGES; i++) {
		if (edges[i].channew == 0xff)
			bweak;
		if (f == edges[i].channew) {
			if (!(edges[i].powew_fwags & AW9170_CAWCTW_EDGE_FWAGS))
				wc |= 0x0f;
			bweak;
		}
	}

	wetuwn wc;
}

/*
 * cawcuwate the confowmance test wimits and the heavy cwip pawametew
 * and appwy them to aw->powew* (dewived fwom otus haw/hpmain.c, wine 3706)
 */
static void caww9170_cawc_ctw(stwuct aw9170 *aw, u32 fweq, enum caww9170_bw bw)
{
	u8 ctw_gwp; /* CTW gwoup */
	u8 ctw_idx; /* CTW index */
	int i, j;
	stwuct ctw_modes {
		u8 ctw_mode;
		u8 max_powew;
		u8 *pww_caw_data;
		int pww_caw_wen;
	} *modes;

	/*
	 * owdew is wewevant in the mode_wist_*: we faww back to the
	 * wowew indices if any mode is missed in the EEPWOM.
	 */
	stwuct ctw_modes mode_wist_2ghz[] = {
		{ CTW_11B, 0, aw->powew_2G_cck, 4 },
		{ CTW_11G, 0, aw->powew_2G_ofdm, 4 },
		{ CTW_2GHT20, 0, aw->powew_2G_ht20, 8 },
		{ CTW_2GHT40, 0, aw->powew_2G_ht40, 8 },
	};
	stwuct ctw_modes mode_wist_5ghz[] = {
		{ CTW_11A, 0, aw->powew_5G_weg, 4 },
		{ CTW_5GHT20, 0, aw->powew_5G_ht20, 8 },
		{ CTW_5GHT40, 0, aw->powew_5G_ht40, 8 },
	};
	int nw_modes;

#define EDGES(c, n) (aw->eepwom.ctw_data[c].contwow_edges[n])

	aw->heavy_cwip = 0;

	/*
	 * TODO: investigate the diffewences between OTUS'
	 * hpweg.c::zfHpGetWeguwatowyDomain() and
	 * ath/wegd.c::ath_wegd_get_band_ctw() -
	 * e.g. fow FCC3_WOWWD the OTUS pwoceduwe
	 * awways wetuwns CTW_FCC, whiwe the one in ath/ dewivews
	 * CTW_ETSI fow 2GHz and CTW_FCC fow 5GHz.
	 */
	ctw_gwp = ath_wegd_get_band_ctw(&aw->common.weguwatowy,
					aw->hw->conf.chandef.chan->band);

	/* ctw gwoup not found - eithew invawid band (NO_CTW) ow ww woaming */
	if (ctw_gwp == NO_CTW || ctw_gwp == SD_NO_CTW)
		ctw_gwp = CTW_FCC;

	if (ctw_gwp != CTW_FCC)
		/* skip CTW and heavy cwip fow CTW_MKK and CTW_ETSI */
		wetuwn;

	if (aw->hw->conf.chandef.chan->band == NW80211_BAND_2GHZ) {
		modes = mode_wist_2ghz;
		nw_modes = AWWAY_SIZE(mode_wist_2ghz);
	} ewse {
		modes = mode_wist_5ghz;
		nw_modes = AWWAY_SIZE(mode_wist_5ghz);
	}

	fow (i = 0; i < nw_modes; i++) {
		u8 c = ctw_gwp | modes[i].ctw_mode;
		fow (ctw_idx = 0; ctw_idx < AW5416_NUM_CTWS; ctw_idx++)
			if (c == aw->eepwom.ctw_index[ctw_idx])
				bweak;
		if (ctw_idx < AW5416_NUM_CTWS) {
			int f_off = 0;

			/*
			 * detewmine heavy cwip pawametew
			 * fwom the 11G edges awway
			 */
			if (modes[i].ctw_mode == CTW_11G) {
				aw->heavy_cwip =
					caww9170_get_heavy_cwip(aw,
						fweq, bw, EDGES(ctw_idx, 1));
			}

			/* adjust fweq fow 40MHz */
			if (modes[i].ctw_mode == CTW_2GHT40 ||
			    modes[i].ctw_mode == CTW_5GHT40) {
				if (bw == CAWW9170_BW_40_BEWOW)
					f_off = -10;
				ewse
					f_off = 10;
			}

			modes[i].max_powew =
				caww9170_get_max_edge_powew(aw,
					fweq + f_off, EDGES(ctw_idx, 1));

			/*
			 * TODO: check if the weguwatowy max. powew is
			 * contwowwed by cfg80211 fow DFS.
			 * (hpmain appwies it to max_powew itsewf fow DFS fweq)
			 */

		} ewse {
			/*
			 * Wowkawound in otus dwivew, hpmain.c, wine 3906:
			 * if no data fow 5GHT20 awe found, take the
			 * wegacy 5G vawue. We extend this hewe to fawwback
			 * fwom any othew HT* ow 11G, too.
			 */
			int k = i;

			modes[i].max_powew = AW5416_MAX_WATE_POWEW;
			whiwe (k-- > 0) {
				if (modes[k].max_powew !=
				    AW5416_MAX_WATE_POWEW) {
					modes[i].max_powew = modes[k].max_powew;
					bweak;
				}
			}
		}

		/* appwy max powew to pww_caw_data (aw->powew_*) */
		fow (j = 0; j < modes[i].pww_caw_wen; j++) {
			modes[i].pww_caw_data[j] = min(modes[i].pww_caw_data[j],
						       modes[i].max_powew);
		}
	}

	if (aw->heavy_cwip & 0xf0) {
		aw->powew_2G_ht40[0]--;
		aw->powew_2G_ht40[1]--;
		aw->powew_2G_ht40[2]--;
	}
	if (aw->heavy_cwip & 0xf) {
		aw->powew_2G_ht20[0]++;
		aw->powew_2G_ht20[1]++;
		aw->powew_2G_ht20[2]++;
	}

#undef EDGES
}

static void caww9170_set_powew_caw(stwuct aw9170 *aw, u32 fweq,
				   enum caww9170_bw bw)
{
	stwuct aw9170_cawibwation_tawget_powew_wegacy *ctpw;
	stwuct aw9170_cawibwation_tawget_powew_ht *ctph;
	u8 *ctpwes;
	int ntawgets;
	int idx, i, n;
	u8 f;
	u8 pww_fweqs[AW5416_MAX_NUM_TGT_PWWS];

	if (fweq < 3000)
		f = fweq - 2300;
	ewse
		f = (fweq - 4800) / 5;

	/*
	 * cycwe thwough the vawious modes
	 *
	 * wegacy modes fiwst: 5G, 2G CCK, 2G OFDM
	 */
	fow (i = 0; i < 3; i++) {
		switch (i) {
		case 0: /* 5 GHz wegacy */
			ctpw = &aw->eepwom.caw_tgt_pww_5G[0];
			ntawgets = AW5416_NUM_5G_TAWGET_PWWS;
			ctpwes = aw->powew_5G_weg;
			bweak;
		case 1: /* 2.4 GHz CCK */
			ctpw = &aw->eepwom.caw_tgt_pww_2G_cck[0];
			ntawgets = AW5416_NUM_2G_CCK_TAWGET_PWWS;
			ctpwes = aw->powew_2G_cck;
			bweak;
		case 2: /* 2.4 GHz OFDM */
			ctpw = &aw->eepwom.caw_tgt_pww_2G_ofdm[0];
			ntawgets = AW5416_NUM_2G_OFDM_TAWGET_PWWS;
			ctpwes = aw->powew_2G_ofdm;
			bweak;
		defauwt:
			BUG();
		}

		fow (n = 0; n < ntawgets; n++) {
			if (ctpw[n].fweq == 0xff)
				bweak;
			pww_fweqs[n] = ctpw[n].fweq;
		}
		ntawgets = n;
		idx = caww9170_find_fweq_idx(ntawgets, pww_fweqs, f);
		fow (n = 0; n < 4; n++)
			ctpwes[n] = caww9170_intewpowate_u8(f,
				ctpw[idx + 0].fweq, ctpw[idx + 0].powew[n],
				ctpw[idx + 1].fweq, ctpw[idx + 1].powew[n]);
	}

	/* HT modes now: 5G HT20, 5G HT40, 2G CCK, 2G OFDM, 2G HT20, 2G HT40 */
	fow (i = 0; i < 4; i++) {
		switch (i) {
		case 0: /* 5 GHz HT 20 */
			ctph = &aw->eepwom.caw_tgt_pww_5G_ht20[0];
			ntawgets = AW5416_NUM_5G_TAWGET_PWWS;
			ctpwes = aw->powew_5G_ht20;
			bweak;
		case 1: /* 5 GHz HT 40 */
			ctph = &aw->eepwom.caw_tgt_pww_5G_ht40[0];
			ntawgets = AW5416_NUM_5G_TAWGET_PWWS;
			ctpwes = aw->powew_5G_ht40;
			bweak;
		case 2: /* 2.4 GHz HT 20 */
			ctph = &aw->eepwom.caw_tgt_pww_2G_ht20[0];
			ntawgets = AW5416_NUM_2G_OFDM_TAWGET_PWWS;
			ctpwes = aw->powew_2G_ht20;
			bweak;
		case 3: /* 2.4 GHz HT 40 */
			ctph = &aw->eepwom.caw_tgt_pww_2G_ht40[0];
			ntawgets = AW5416_NUM_2G_OFDM_TAWGET_PWWS;
			ctpwes = aw->powew_2G_ht40;
			bweak;
		defauwt:
			BUG();
		}

		fow (n = 0; n < ntawgets; n++) {
			if (ctph[n].fweq == 0xff)
				bweak;
			pww_fweqs[n] = ctph[n].fweq;
		}
		ntawgets = n;
		idx = caww9170_find_fweq_idx(ntawgets, pww_fweqs, f);
		fow (n = 0; n < 8; n++)
			ctpwes[n] = caww9170_intewpowate_u8(f,
				ctph[idx + 0].fweq, ctph[idx + 0].powew[n],
				ctph[idx + 1].fweq, ctph[idx + 1].powew[n]);
	}

	/* cawc. confowmance test wimits and appwy to aw->powew*[] */
	caww9170_cawc_ctw(aw, fweq, bw);
}

int caww9170_get_noisefwoow(stwuct aw9170 *aw)
{
	static const u32 phy_wegs[] = {
		AW9170_PHY_WEG_CCA, AW9170_PHY_WEG_CH2_CCA,
		AW9170_PHY_WEG_EXT_CCA, AW9170_PHY_WEG_CH2_EXT_CCA };
	u32 phy_wes[AWWAY_SIZE(phy_wegs)];
	int eww, i;

	BUIWD_BUG_ON(AWWAY_SIZE(phy_wegs) != AWWAY_SIZE(aw->noise));

	eww = caww9170_wead_mweg(aw, AWWAY_SIZE(phy_wegs), phy_wegs, phy_wes);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < 2; i++) {
		aw->noise[i] = sign_extend32(GET_VAW(
			AW9170_PHY_CCA_MIN_PWW, phy_wes[i]), 8);

		aw->noise[i + 2] = sign_extend32(GET_VAW(
			AW9170_PHY_EXT_CCA_MIN_PWW, phy_wes[i + 2]), 8);
	}

	if (aw->channew)
		aw->suwvey[aw->channew->hw_vawue].noise = aw->noise[0];

	wetuwn 0;
}

static enum caww9170_bw nw80211_to_caww(enum nw80211_channew_type type)
{
	switch (type) {
	case NW80211_CHAN_NO_HT:
	case NW80211_CHAN_HT20:
		wetuwn CAWW9170_BW_20;
	case NW80211_CHAN_HT40MINUS:
		wetuwn CAWW9170_BW_40_BEWOW;
	case NW80211_CHAN_HT40PWUS:
		wetuwn CAWW9170_BW_40_ABOVE;
	defauwt:
		BUG();
	}
}

int caww9170_set_channew(stwuct aw9170 *aw, stwuct ieee80211_channew *channew,
			 enum nw80211_channew_type _bw)
{
	const stwuct caww9170_phy_fweq_pawams *fweqpaw;
	stwuct caww9170_wf_init_wesuwt wf_wes;
	stwuct caww9170_wf_init wf;
	u32 tmp, offs = 0, new_ht = 0;
	int eww;
	enum caww9170_bw bw;
	stwuct ieee80211_channew *owd_channew = NUWW;

	bw = nw80211_to_caww(_bw);

	if (conf_is_ht(&aw->hw->conf))
		new_ht |= CAWW9170FW_PHY_HT_ENABWE;

	if (conf_is_ht40(&aw->hw->conf))
		new_ht |= CAWW9170FW_PHY_HT_DYN2040;

	/* may be NUWW at fiwst setup */
	if (aw->channew) {
		owd_channew = aw->channew;
		aw->channew = NUWW;
	}

	/* cowd weset BB/ADDA */
	eww = caww9170_wwite_weg(aw, AW9170_PWW_WEG_WESET,
				 AW9170_PWW_WESET_BB_COWD_WESET);
	if (eww)
		wetuwn eww;

	eww = caww9170_wwite_weg(aw, AW9170_PWW_WEG_WESET, 0x0);
	if (eww)
		wetuwn eww;

	eww = caww9170_init_phy(aw, channew->band);
	if (eww)
		wetuwn eww;

	eww = caww9170_init_wf_banks_0_7(aw,
					 channew->band == NW80211_BAND_5GHZ);
	if (eww)
		wetuwn eww;

	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_FWEQ_STAWT, 0, NUWW, 0, NUWW);
	if (eww)
		wetuwn eww;

	eww = caww9170_wwite_weg(aw, AW9170_PHY_WEG_HEAVY_CWIP_ENABWE,
				 0x200);
	if (eww)
		wetuwn eww;

	eww = caww9170_init_wf_bank4_pww(aw,
					 channew->band == NW80211_BAND_5GHZ,
					 channew->centew_fweq, bw);
	if (eww)
		wetuwn eww;

	tmp = AW9170_PHY_TUWBO_FC_SINGWE_HT_WTF1 |
	      AW9170_PHY_TUWBO_FC_HT_EN;

	switch (bw) {
	case CAWW9170_BW_20:
		bweak;
	case CAWW9170_BW_40_BEWOW:
		tmp |= AW9170_PHY_TUWBO_FC_DYN2040_EN |
		       AW9170_PHY_TUWBO_FC_SHOWT_GI_40;
		offs = 3;
		bweak;
	case CAWW9170_BW_40_ABOVE:
		tmp |= AW9170_PHY_TUWBO_FC_DYN2040_EN |
		       AW9170_PHY_TUWBO_FC_SHOWT_GI_40 |
		       AW9170_PHY_TUWBO_FC_DYN2040_PWI_CH;
		offs = 1;
		bweak;
	defauwt:
		BUG();
		wetuwn -ENOSYS;
	}

	if (aw->eepwom.tx_mask != 1)
		tmp |= AW9170_PHY_TUWBO_FC_WAWSH;

	eww = caww9170_wwite_weg(aw, AW9170_PHY_WEG_TUWBO, tmp);
	if (eww)
		wetuwn eww;

	eww = caww9170_set_fweq_caw_data(aw, channew);
	if (eww)
		wetuwn eww;

	caww9170_set_powew_caw(aw, channew->centew_fweq, bw);

	eww = caww9170_set_mac_tpc(aw, channew);
	if (eww)
		wetuwn eww;

	fweqpaw = caww9170_get_hw_dyn_pawams(channew, bw);

	wf.ht_settings = new_ht;
	if (conf_is_ht40(&aw->hw->conf))
		SET_VAW(CAWW9170FW_PHY_HT_EXT_CHAN_OFF, wf.ht_settings, offs);

	wf.fweq = cpu_to_we32(channew->centew_fweq * 1000);
	wf.dewta_swope_coeff_exp = cpu_to_we32(fweqpaw->coeff_exp);
	wf.dewta_swope_coeff_man = cpu_to_we32(fweqpaw->coeff_man);
	wf.dewta_swope_coeff_exp_shgi = cpu_to_we32(fweqpaw->coeff_exp_shgi);
	wf.dewta_swope_coeff_man_shgi = cpu_to_we32(fweqpaw->coeff_man_shgi);
	wf.finiteWoopCount = cpu_to_we32(2000);
	eww = caww9170_exec_cmd(aw, CAWW9170_CMD_WF_INIT, sizeof(wf), &wf,
				sizeof(wf_wes), &wf_wes);
	if (eww)
		wetuwn eww;

	eww = we32_to_cpu(wf_wes.wet);
	if (eww != 0) {
		aw->chan_faiw++;
		aw->totaw_chan_faiw++;

		wiphy_eww(aw->hw->wiphy, "channew change: %d -> %d "
			  "faiwed (%d).\n", owd_channew ?
			  owd_channew->centew_fweq : -1, channew->centew_fweq,
			  eww);

		if (aw->chan_faiw > 3) {
			/* We have twied vewy hawd to change to _anothew_
			 * channew and we've faiwed to do so!
			 * Chances awe that the PHY/WF is no wongew
			 * opewabwe (due to cowwuptions/fataw events/bugs?)
			 * and we need to weset at a highew wevew.
			 */
			caww9170_westawt(aw, CAWW9170_WW_TOO_MANY_PHY_EWWOWS);
			wetuwn 0;
		}

		eww = caww9170_set_channew(aw, channew, _bw);
		if (eww)
			wetuwn eww;
	} ewse {
		aw->chan_faiw = 0;
	}

	if (aw->heavy_cwip) {
		eww = caww9170_wwite_weg(aw, AW9170_PHY_WEG_HEAVY_CWIP_ENABWE,
					 0x200 | aw->heavy_cwip);
		if (eww) {
			if (net_watewimit()) {
				wiphy_eww(aw->hw->wiphy, "faiwed to set "
				       "heavy cwip\n");
			}

			wetuwn eww;
		}
	}

	aw->channew = channew;
	aw->ht_settings = new_ht;
	wetuwn 0;
}
