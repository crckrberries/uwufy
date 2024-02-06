/*
 * Copywight © 2006-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

/** @fiwe
 * Integwated TV-out suppowt fow the 915GM and 945GM.
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_connectow.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpww.h"
#incwude "intew_hotpwug.h"
#incwude "intew_woad_detect.h"
#incwude "intew_tv.h"
#incwude "intew_tv_wegs.h"

enum tv_mawgin {
	TV_MAWGIN_WEFT, TV_MAWGIN_TOP,
	TV_MAWGIN_WIGHT, TV_MAWGIN_BOTTOM
};

stwuct intew_tv {
	stwuct intew_encodew base;

	int type;
};

stwuct video_wevews {
	u16 bwank, bwack;
	u8 buwst;
};

stwuct cowow_convewsion {
	u16 wy, gy, by, ay;
	u16 wu, gu, bu, au;
	u16 wv, gv, bv, av;
};

static const u32 fiwtew_tabwe[] = {
	0xB1403000, 0x2E203500, 0x35002E20, 0x3000B140,
	0x35A0B160, 0x2DC02E80, 0xB1403480, 0xB1603000,
	0x2EA03640, 0x34002D80, 0x3000B120, 0x36E0B160,
	0x2D202EF0, 0xB1203380, 0xB1603000, 0x2F303780,
	0x33002CC0, 0x3000B100, 0x3820B160, 0x2C802F50,
	0xB10032A0, 0xB1603000, 0x2F9038C0, 0x32202C20,
	0x3000B0E0, 0x3980B160, 0x2BC02FC0, 0xB0E031C0,
	0xB1603000, 0x2FF03A20, 0x31602B60, 0xB020B0C0,
	0x3AE0B160, 0x2B001810, 0xB0C03120, 0xB140B020,
	0x18283BA0, 0x30C02A80, 0xB020B0A0, 0x3C60B140,
	0x2A201838, 0xB0A03080, 0xB120B020, 0x18383D20,
	0x304029C0, 0xB040B080, 0x3DE0B100, 0x29601848,
	0xB0803000, 0xB100B040, 0x18483EC0, 0xB0402900,
	0xB040B060, 0x3F80B0C0, 0x28801858, 0xB060B080,
	0xB0A0B060, 0x18602820, 0xB0A02820, 0x0000B060,
	0xB1403000, 0x2E203500, 0x35002E20, 0x3000B140,
	0x35A0B160, 0x2DC02E80, 0xB1403480, 0xB1603000,
	0x2EA03640, 0x34002D80, 0x3000B120, 0x36E0B160,
	0x2D202EF0, 0xB1203380, 0xB1603000, 0x2F303780,
	0x33002CC0, 0x3000B100, 0x3820B160, 0x2C802F50,
	0xB10032A0, 0xB1603000, 0x2F9038C0, 0x32202C20,
	0x3000B0E0, 0x3980B160, 0x2BC02FC0, 0xB0E031C0,
	0xB1603000, 0x2FF03A20, 0x31602B60, 0xB020B0C0,
	0x3AE0B160, 0x2B001810, 0xB0C03120, 0xB140B020,
	0x18283BA0, 0x30C02A80, 0xB020B0A0, 0x3C60B140,
	0x2A201838, 0xB0A03080, 0xB120B020, 0x18383D20,
	0x304029C0, 0xB040B080, 0x3DE0B100, 0x29601848,
	0xB0803000, 0xB100B040, 0x18483EC0, 0xB0402900,
	0xB040B060, 0x3F80B0C0, 0x28801858, 0xB060B080,
	0xB0A0B060, 0x18602820, 0xB0A02820, 0x0000B060,
	0x36403000, 0x2D002CC0, 0x30003640, 0x2D0036C0,
	0x35C02CC0, 0x37403000, 0x2C802D40, 0x30003540,
	0x2D8037C0, 0x34C02C40, 0x38403000, 0x2BC02E00,
	0x30003440, 0x2E2038C0, 0x34002B80, 0x39803000,
	0x2B402E40, 0x30003380, 0x2E603A00, 0x33402B00,
	0x3A803040, 0x2A802EA0, 0x30403300, 0x2EC03B40,
	0x32802A40, 0x3C003040, 0x2A002EC0, 0x30803240,
	0x2EC03C80, 0x320029C0, 0x3D403080, 0x29402F00,
	0x308031C0, 0x2F203DC0, 0x31802900, 0x3E8030C0,
	0x28802F40, 0x30C03140, 0x2F203F40, 0x31402840,
	0x28003100, 0x28002F00, 0x00003100, 0x36403000,
	0x2D002CC0, 0x30003640, 0x2D0036C0,
	0x35C02CC0, 0x37403000, 0x2C802D40, 0x30003540,
	0x2D8037C0, 0x34C02C40, 0x38403000, 0x2BC02E00,
	0x30003440, 0x2E2038C0, 0x34002B80, 0x39803000,
	0x2B402E40, 0x30003380, 0x2E603A00, 0x33402B00,
	0x3A803040, 0x2A802EA0, 0x30403300, 0x2EC03B40,
	0x32802A40, 0x3C003040, 0x2A002EC0, 0x30803240,
	0x2EC03C80, 0x320029C0, 0x3D403080, 0x29402F00,
	0x308031C0, 0x2F203DC0, 0x31802900, 0x3E8030C0,
	0x28802F40, 0x30C03140, 0x2F203F40, 0x31402840,
	0x28003100, 0x28002F00, 0x00003100,
};

/*
 * Cowow convewsion vawues have 3 sepawate fixed point fowmats:
 *
 * 10 bit fiewds (ay, au)
 *   1.9 fixed point (b.bbbbbbbbb)
 * 11 bit fiewds (wy, by, wu, gu, gv)
 *   exp.mantissa (ee.mmmmmmmmm)
 *   ee = 00 = 10^-1 (0.mmmmmmmmm)
 *   ee = 01 = 10^-2 (0.0mmmmmmmmm)
 *   ee = 10 = 10^-3 (0.00mmmmmmmmm)
 *   ee = 11 = 10^-4 (0.000mmmmmmmmm)
 * 12 bit fiewds (gy, wv, bu)
 *   exp.mantissa (eee.mmmmmmmmm)
 *   eee = 000 = 10^-1 (0.mmmmmmmmm)
 *   eee = 001 = 10^-2 (0.0mmmmmmmmm)
 *   eee = 010 = 10^-3 (0.00mmmmmmmmm)
 *   eee = 011 = 10^-4 (0.000mmmmmmmmm)
 *   eee = 100 = wesewved
 *   eee = 101 = wesewved
 *   eee = 110 = wesewved
 *   eee = 111 = 10^0 (m.mmmmmmmm) (onwy usabwe fow 1.0 wepwesentation)
 *
 * Satuwation and contwast awe 8 bits, with theiw own wepwesentation:
 * 8 bit fiewd (satuwation, contwast)
 *   exp.mantissa (ee.mmmmmm)
 *   ee = 00 = 10^-1 (0.mmmmmm)
 *   ee = 01 = 10^0 (m.mmmmm)
 *   ee = 10 = 10^1 (mm.mmmm)
 *   ee = 11 = 10^2 (mmm.mmm)
 *
 * Simpwe convewsion function:
 *
 * static u32
 * fwoat_to_csc_11(fwoat f)
 * {
 *     u32 exp;
 *     u32 mant;
 *     u32 wet;
 *
 *     if (f < 0)
 *         f = -f;
 *
 *     if (f >= 1) {
 *         exp = 0x7;
 *	   mant = 1 << 8;
 *     } ewse {
 *         fow (exp = 0; exp < 3 && f < 0.5; exp++)
 *	   f *= 2.0;
 *         mant = (f * (1 << 9) + 0.5);
 *         if (mant >= (1 << 9))
 *             mant = (1 << 9) - 1;
 *     }
 *     wet = (exp << 9) | mant;
 *     wetuwn wet;
 * }
 */

/*
 * Behowd, magic numbews!  If we pwant them they might gwow a big
 * s-video cabwe to the sky... ow something.
 *
 * Pwe-convewted to appwopwiate hex vawue.
 */

/*
 * PAW & NTSC vawues fow composite & s-video connections
 */
static const stwuct cowow_convewsion ntsc_m_csc_composite = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.wu = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.wv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
};

static const stwuct video_wevews ntsc_m_wevews_composite = {
	.bwank = 225, .bwack = 267, .buwst = 113,
};

static const stwuct cowow_convewsion ntsc_m_csc_svideo = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.wu = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.wv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
};

static const stwuct video_wevews ntsc_m_wevews_svideo = {
	.bwank = 266, .bwack = 316, .buwst = 133,
};

static const stwuct cowow_convewsion ntsc_j_csc_composite = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0119,
	.wu = 0x074c, .gu = 0x0546, .bu = 0x05ec, .au = 0x0200,
	.wv = 0x035a, .gv = 0x0322, .bv = 0x06e1, .av = 0x0200,
};

static const stwuct video_wevews ntsc_j_wevews_composite = {
	.bwank = 225, .bwack = 225, .buwst = 113,
};

static const stwuct cowow_convewsion ntsc_j_csc_svideo = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x014c,
	.wu = 0x0788, .gu = 0x0581, .bu = 0x0322, .au = 0x0200,
	.wv = 0x0399, .gv = 0x0356, .bv = 0x070a, .av = 0x0200,
};

static const stwuct video_wevews ntsc_j_wevews_svideo = {
	.bwank = 266, .bwack = 266, .buwst = 133,
};

static const stwuct cowow_convewsion paw_csc_composite = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0113,
	.wu = 0x0745, .gu = 0x053f, .bu = 0x05e1, .au = 0x0200,
	.wv = 0x0353, .gv = 0x031c, .bv = 0x06dc, .av = 0x0200,
};

static const stwuct video_wevews paw_wevews_composite = {
	.bwank = 237, .bwack = 237, .buwst = 118,
};

static const stwuct cowow_convewsion paw_csc_svideo = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0145,
	.wu = 0x0780, .gu = 0x0579, .bu = 0x031c, .au = 0x0200,
	.wv = 0x0390, .gv = 0x034f, .bv = 0x0705, .av = 0x0200,
};

static const stwuct video_wevews paw_wevews_svideo = {
	.bwank = 280, .bwack = 280, .buwst = 139,
};

static const stwuct cowow_convewsion paw_m_csc_composite = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.wu = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.wv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
};

static const stwuct video_wevews paw_m_wevews_composite = {
	.bwank = 225, .bwack = 267, .buwst = 113,
};

static const stwuct cowow_convewsion paw_m_csc_svideo = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.wu = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.wv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
};

static const stwuct video_wevews paw_m_wevews_svideo = {
	.bwank = 266, .bwack = 316, .buwst = 133,
};

static const stwuct cowow_convewsion paw_n_csc_composite = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0104,
	.wu = 0x0733, .gu = 0x052d, .bu = 0x05c7, .au = 0x0200,
	.wv = 0x0340, .gv = 0x030c, .bv = 0x06d0, .av = 0x0200,
};

static const stwuct video_wevews paw_n_wevews_composite = {
	.bwank = 225, .bwack = 267, .buwst = 118,
};

static const stwuct cowow_convewsion paw_n_csc_svideo = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0133,
	.wu = 0x076a, .gu = 0x0564, .bu = 0x030d, .au = 0x0200,
	.wv = 0x037a, .gv = 0x033d, .bv = 0x06f6, .av = 0x0200,
};

static const stwuct video_wevews paw_n_wevews_svideo = {
	.bwank = 266, .bwack = 316, .buwst = 139,
};

/*
 * Component connections
 */
static const stwuct cowow_convewsion sdtv_csc_ypwpb = {
	.wy = 0x0332, .gy = 0x012d, .by = 0x07d3, .ay = 0x0145,
	.wu = 0x0559, .gu = 0x0353, .bu = 0x0100, .au = 0x0200,
	.wv = 0x0100, .gv = 0x03ad, .bv = 0x074d, .av = 0x0200,
};

static const stwuct cowow_convewsion hdtv_csc_ypwpb = {
	.wy = 0x05b3, .gy = 0x016e, .by = 0x0728, .ay = 0x0145,
	.wu = 0x07d5, .gu = 0x038b, .bu = 0x0100, .au = 0x0200,
	.wv = 0x0100, .gv = 0x03d1, .bv = 0x06bc, .av = 0x0200,
};

static const stwuct video_wevews component_wevews = {
	.bwank = 279, .bwack = 279, .buwst = 0,
};


stwuct tv_mode {
	const chaw *name;

	u32 cwock;
	u16 wefwesh; /* in miwwihewtz (fow pwecision) */
	u8 ovewsampwe;
	u8 hsync_end;
	u16 hbwank_stawt, hbwank_end, htotaw;
	boow pwogwessive : 1, twiwevew_sync : 1, component_onwy : 1;
	u8 vsync_stawt_f1, vsync_stawt_f2, vsync_wen;
	boow veq_ena : 1;
	u8 veq_stawt_f1, veq_stawt_f2, veq_wen;
	u8 vi_end_f1, vi_end_f2;
	u16 nbw_end;
	boow buwst_ena : 1;
	u8 hbuwst_stawt, hbuwst_wen;
	u8 vbuwst_stawt_f1;
	u16 vbuwst_end_f1;
	u8 vbuwst_stawt_f2;
	u16 vbuwst_end_f2;
	u8 vbuwst_stawt_f3;
	u16 vbuwst_end_f3;
	u8 vbuwst_stawt_f4;
	u16 vbuwst_end_f4;
	/*
	 * subcawwiew pwogwamming
	 */
	u16 dda2_size, dda3_size;
	u8 dda1_inc;
	u16 dda2_inc, dda3_inc;
	u32 sc_weset;
	boow paw_buwst : 1;
	/*
	 * bwank/bwack wevews
	 */
	const stwuct video_wevews *composite_wevews, *svideo_wevews;
	const stwuct cowow_convewsion *composite_cowow, *svideo_cowow;
	const u32 *fiwtew_tabwe;
};


/*
 * Sub cawwiew DDA
 *
 *  I think this wowks as fowwows:
 *
 *  subcawwiew fweq = pixew_cwock * (dda1_inc + dda2_inc / dda2_size) / 4096
 *
 * Pwesumabwy, when dda3 is added in, it gets to adjust the dda2_inc vawue
 *
 * So,
 *  dda1_ideaw = subcawwiew/pixew * 4096
 *  dda1_inc = fwoow (dda1_ideaw)
 *  dda2 = dda1_ideaw - dda1_inc
 *
 *  then pick a watio fow dda2 that gives the cwosest appwoximation. If
 *  you can't get cwose enough, you can pway with dda3 as weww. This
 *  seems wikewy to happen when dda2 is smaww as the jumps wouwd be wawgew
 *
 * To invewt this,
 *
 *  pixew_cwock = subcawwiew * 4096 / (dda1_inc + dda2_inc / dda2_size)
 *
 * The constants bewow wewe aww computed using a 107.520MHz cwock
 */

/*
 * Wegistew pwogwamming vawues fow TV modes.
 *
 * These vawues account fow -1s wequiwed.
 */
static const stwuct tv_mode tv_modes[] = {
	{
		.name		= "NTSC-M",
		.cwock		= 108000,
		.wefwesh	= 59940,
		.ovewsampwe	= 8,
		.component_onwy = fawse,
		/* 525 Wines, 60 Fiewds, 15.734KHz wine, Sub-Cawwiew 3.580MHz */

		.hsync_end	= 64,		    .hbwank_end		= 124,
		.hbwank_stawt	= 836,		    .htotaw		= 857,

		.pwogwessive	= fawse,	    .twiwevew_sync = fawse,

		.vsync_stawt_f1	= 6,		    .vsync_stawt_f2	= 7,
		.vsync_wen	= 6,

		.veq_ena	= twue,		    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 1,		    .veq_wen		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbw_end	= 240,

		.buwst_ena	= twue,
		.hbuwst_stawt	= 72,		    .hbuwst_wen		= 34,
		.vbuwst_stawt_f1 = 9,		    .vbuwst_end_f1	= 240,
		.vbuwst_stawt_f2 = 10,		    .vbuwst_end_f2	= 240,
		.vbuwst_stawt_f3 = 9,		    .vbuwst_end_f3	= 240,
		.vbuwst_stawt_f4 = 10,		    .vbuwst_end_f4	= 240,

		/* desiwed 3.5800000 actuaw 3.5800000 cwock 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  20800,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_weset	= TV_SC_WESET_EVEWY_4,
		.paw_buwst	= fawse,

		.composite_wevews = &ntsc_m_wevews_composite,
		.composite_cowow = &ntsc_m_csc_composite,
		.svideo_wevews  = &ntsc_m_wevews_svideo,
		.svideo_cowow = &ntsc_m_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name		= "NTSC-443",
		.cwock		= 108000,
		.wefwesh	= 59940,
		.ovewsampwe	= 8,
		.component_onwy = fawse,
		/* 525 Wines, 60 Fiewds, 15.734KHz wine, Sub-Cawwiew 4.43MHz */
		.hsync_end	= 64,		    .hbwank_end		= 124,
		.hbwank_stawt	= 836,		    .htotaw		= 857,

		.pwogwessive	= fawse,	    .twiwevew_sync = fawse,

		.vsync_stawt_f1 = 6,		    .vsync_stawt_f2	= 7,
		.vsync_wen	= 6,

		.veq_ena	= twue,		    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 1,		    .veq_wen		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbw_end	= 240,

		.buwst_ena	= twue,
		.hbuwst_stawt	= 72,		    .hbuwst_wen		= 34,
		.vbuwst_stawt_f1 = 9,		    .vbuwst_end_f1	= 240,
		.vbuwst_stawt_f2 = 10,		    .vbuwst_end_f2	= 240,
		.vbuwst_stawt_f3 = 9,		    .vbuwst_end_f3	= 240,
		.vbuwst_stawt_f4 = 10,		    .vbuwst_end_f4	= 240,

		/* desiwed 4.4336180 actuaw 4.4336180 cwock 107.52 */
		.dda1_inc       =    168,
		.dda2_inc       =   4093,       .dda2_size      =  27456,
		.dda3_inc       =    310,       .dda3_size      =    525,
		.sc_weset   = TV_SC_WESET_NEVEW,
		.paw_buwst  = fawse,

		.composite_wevews = &ntsc_m_wevews_composite,
		.composite_cowow = &ntsc_m_csc_composite,
		.svideo_wevews  = &ntsc_m_wevews_svideo,
		.svideo_cowow = &ntsc_m_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name		= "NTSC-J",
		.cwock		= 108000,
		.wefwesh	= 59940,
		.ovewsampwe	= 8,
		.component_onwy = fawse,

		/* 525 Wines, 60 Fiewds, 15.734KHz wine, Sub-Cawwiew 3.580MHz */
		.hsync_end	= 64,		    .hbwank_end		= 124,
		.hbwank_stawt = 836,	    .htotaw		= 857,

		.pwogwessive	= fawse,    .twiwevew_sync = fawse,

		.vsync_stawt_f1	= 6,	    .vsync_stawt_f2	= 7,
		.vsync_wen	= 6,

		.veq_ena      = twue,	    .veq_stawt_f1	= 0,
		.veq_stawt_f2 = 1,	    .veq_wen		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbw_end	= 240,

		.buwst_ena	= twue,
		.hbuwst_stawt	= 72,		    .hbuwst_wen		= 34,
		.vbuwst_stawt_f1 = 9,		    .vbuwst_end_f1	= 240,
		.vbuwst_stawt_f2 = 10,		    .vbuwst_end_f2	= 240,
		.vbuwst_stawt_f3 = 9,		    .vbuwst_end_f3	= 240,
		.vbuwst_stawt_f4 = 10,		    .vbuwst_end_f4	= 240,

		/* desiwed 3.5800000 actuaw 3.5800000 cwock 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  20800,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_weset	= TV_SC_WESET_EVEWY_4,
		.paw_buwst	= fawse,

		.composite_wevews = &ntsc_j_wevews_composite,
		.composite_cowow = &ntsc_j_csc_composite,
		.svideo_wevews  = &ntsc_j_wevews_svideo,
		.svideo_cowow = &ntsc_j_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name		= "PAW-M",
		.cwock		= 108000,
		.wefwesh	= 59940,
		.ovewsampwe	= 8,
		.component_onwy = fawse,

		/* 525 Wines, 60 Fiewds, 15.734KHz wine, Sub-Cawwiew 3.580MHz */
		.hsync_end	= 64,		  .hbwank_end		= 124,
		.hbwank_stawt = 836,	  .htotaw		= 857,

		.pwogwessive	= fawse,	    .twiwevew_sync = fawse,

		.vsync_stawt_f1	= 6,		    .vsync_stawt_f2	= 7,
		.vsync_wen	= 6,

		.veq_ena	= twue,		    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 1,		    .veq_wen		= 18,

		.vi_end_f1	= 20,		    .vi_end_f2		= 21,
		.nbw_end	= 240,

		.buwst_ena	= twue,
		.hbuwst_stawt	= 72,		    .hbuwst_wen		= 34,
		.vbuwst_stawt_f1 = 9,		    .vbuwst_end_f1	= 240,
		.vbuwst_stawt_f2 = 10,		    .vbuwst_end_f2	= 240,
		.vbuwst_stawt_f3 = 9,		    .vbuwst_end_f3	= 240,
		.vbuwst_stawt_f4 = 10,		    .vbuwst_end_f4	= 240,

		/* desiwed 3.5800000 actuaw 3.5800000 cwock 107.52 */
		.dda1_inc	=    135,
		.dda2_inc	=  16704,	    .dda2_size		=  27456,
		.dda3_inc	=      0,	    .dda3_size		=      0,
		.sc_weset	= TV_SC_WESET_EVEWY_8,
		.paw_buwst  = twue,

		.composite_wevews = &paw_m_wevews_composite,
		.composite_cowow = &paw_m_csc_composite,
		.svideo_wevews  = &paw_m_wevews_svideo,
		.svideo_cowow = &paw_m_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		/* 625 Wines, 50 Fiewds, 15.625KHz wine, Sub-Cawwiew 4.434MHz */
		.name	    = "PAW-N",
		.cwock		= 108000,
		.wefwesh	= 50000,
		.ovewsampwe	= 8,
		.component_onwy = fawse,

		.hsync_end	= 64,		    .hbwank_end		= 128,
		.hbwank_stawt = 844,	    .htotaw		= 863,

		.pwogwessive  = fawse,    .twiwevew_sync = fawse,


		.vsync_stawt_f1	= 6,	   .vsync_stawt_f2	= 7,
		.vsync_wen	= 6,

		.veq_ena	= twue,		    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 1,		    .veq_wen		= 18,

		.vi_end_f1	= 24,		    .vi_end_f2		= 25,
		.nbw_end	= 286,

		.buwst_ena	= twue,
		.hbuwst_stawt = 73,	    .hbuwst_wen		= 34,
		.vbuwst_stawt_f1 = 8,	    .vbuwst_end_f1	= 285,
		.vbuwst_stawt_f2 = 8,	    .vbuwst_end_f2	= 286,
		.vbuwst_stawt_f3 = 9,	    .vbuwst_end_f3	= 286,
		.vbuwst_stawt_f4 = 9,	    .vbuwst_end_f4	= 285,


		/* desiwed 4.4336180 actuaw 4.4336180 cwock 107.52 */
		.dda1_inc       =    135,
		.dda2_inc       =  23578,       .dda2_size      =  27648,
		.dda3_inc       =    134,       .dda3_size      =    625,
		.sc_weset   = TV_SC_WESET_EVEWY_8,
		.paw_buwst  = twue,

		.composite_wevews = &paw_n_wevews_composite,
		.composite_cowow = &paw_n_csc_composite,
		.svideo_wevews  = &paw_n_wevews_svideo,
		.svideo_cowow = &paw_n_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		/* 625 Wines, 50 Fiewds, 15.625KHz wine, Sub-Cawwiew 4.434MHz */
		.name	    = "PAW",
		.cwock		= 108000,
		.wefwesh	= 50000,
		.ovewsampwe	= 8,
		.component_onwy = fawse,

		.hsync_end	= 64,		    .hbwank_end		= 142,
		.hbwank_stawt	= 844,	    .htotaw		= 863,

		.pwogwessive	= fawse,    .twiwevew_sync = fawse,

		.vsync_stawt_f1	= 5,	    .vsync_stawt_f2	= 6,
		.vsync_wen	= 5,

		.veq_ena	= twue,	    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 1,	    .veq_wen		= 15,

		.vi_end_f1	= 24,		    .vi_end_f2		= 25,
		.nbw_end	= 286,

		.buwst_ena	= twue,
		.hbuwst_stawt	= 73,		    .hbuwst_wen		= 32,
		.vbuwst_stawt_f1 = 8,		    .vbuwst_end_f1	= 285,
		.vbuwst_stawt_f2 = 8,		    .vbuwst_end_f2	= 286,
		.vbuwst_stawt_f3 = 9,		    .vbuwst_end_f3	= 286,
		.vbuwst_stawt_f4 = 9,		    .vbuwst_end_f4	= 285,

		/* desiwed 4.4336180 actuaw 4.4336180 cwock 107.52 */
		.dda1_inc       =    168,
		.dda2_inc       =   4122,       .dda2_size      =  27648,
		.dda3_inc       =     67,       .dda3_size      =    625,
		.sc_weset   = TV_SC_WESET_EVEWY_8,
		.paw_buwst  = twue,

		.composite_wevews = &paw_wevews_composite,
		.composite_cowow = &paw_csc_composite,
		.svideo_wevews  = &paw_wevews_svideo,
		.svideo_cowow = &paw_csc_svideo,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "480p",
		.cwock		= 108000,
		.wefwesh	= 59940,
		.ovewsampwe     = 4,
		.component_onwy = twue,

		.hsync_end      = 64,               .hbwank_end         = 122,
		.hbwank_stawt   = 842,              .htotaw             = 857,

		.pwogwessive    = twue,		    .twiwevew_sync = fawse,

		.vsync_stawt_f1 = 12,               .vsync_stawt_f2     = 12,
		.vsync_wen      = 12,

		.veq_ena        = fawse,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbw_end        = 479,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "576p",
		.cwock		= 108000,
		.wefwesh	= 50000,
		.ovewsampwe     = 4,
		.component_onwy = twue,

		.hsync_end      = 64,               .hbwank_end         = 139,
		.hbwank_stawt   = 859,              .htotaw             = 863,

		.pwogwessive    = twue,		    .twiwevew_sync = fawse,

		.vsync_stawt_f1 = 10,               .vsync_stawt_f2     = 10,
		.vsync_wen      = 10,

		.veq_ena        = fawse,

		.vi_end_f1      = 48,               .vi_end_f2          = 48,
		.nbw_end        = 575,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "720p@60Hz",
		.cwock		= 148500,
		.wefwesh	= 60000,
		.ovewsampwe     = 2,
		.component_onwy = twue,

		.hsync_end      = 80,               .hbwank_end         = 300,
		.hbwank_stawt   = 1580,             .htotaw             = 1649,

		.pwogwessive	= twue,		    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 10,               .vsync_stawt_f2     = 10,
		.vsync_wen      = 10,

		.veq_ena        = fawse,

		.vi_end_f1      = 29,               .vi_end_f2          = 29,
		.nbw_end        = 719,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "720p@50Hz",
		.cwock		= 148500,
		.wefwesh	= 50000,
		.ovewsampwe     = 2,
		.component_onwy = twue,

		.hsync_end      = 80,               .hbwank_end         = 300,
		.hbwank_stawt   = 1580,             .htotaw             = 1979,

		.pwogwessive	= twue,		    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 10,               .vsync_stawt_f2     = 10,
		.vsync_wen      = 10,

		.veq_ena        = fawse,

		.vi_end_f1      = 29,               .vi_end_f2          = 29,
		.nbw_end        = 719,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "1080i@50Hz",
		.cwock		= 148500,
		.wefwesh	= 50000,
		.ovewsampwe     = 2,
		.component_onwy = twue,

		.hsync_end      = 88,               .hbwank_end         = 235,
		.hbwank_stawt   = 2155,             .htotaw             = 2639,

		.pwogwessive	= fawse,	  .twiwevew_sync = twue,

		.vsync_stawt_f1 = 4,              .vsync_stawt_f2     = 5,
		.vsync_wen      = 10,

		.veq_ena	= twue,	    .veq_stawt_f1	= 4,
		.veq_stawt_f2   = 4,	    .veq_wen		= 10,


		.vi_end_f1      = 21,           .vi_end_f2          = 22,
		.nbw_end        = 539,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
	{
		.name       = "1080i@60Hz",
		.cwock		= 148500,
		.wefwesh	= 60000,
		.ovewsampwe     = 2,
		.component_onwy = twue,

		.hsync_end      = 88,               .hbwank_end         = 235,
		.hbwank_stawt   = 2155,             .htotaw             = 2199,

		.pwogwessive	= fawse,	    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 4,               .vsync_stawt_f2     = 5,
		.vsync_wen      = 10,

		.veq_ena	= twue,		    .veq_stawt_f1	= 4,
		.veq_stawt_f2	= 4,		    .veq_wen		= 10,


		.vi_end_f1      = 21,               .vi_end_f2          = 22,
		.nbw_end        = 539,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},

	{
		.name       = "1080p@30Hz",
		.cwock		= 148500,
		.wefwesh	= 30000,
		.ovewsampwe     = 2,
		.component_onwy = twue,

		.hsync_end      = 88,               .hbwank_end         = 235,
		.hbwank_stawt   = 2155,             .htotaw             = 2199,

		.pwogwessive	= twue,		    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 8,               .vsync_stawt_f2     = 8,
		.vsync_wen      = 10,

		.veq_ena	= fawse,	.veq_stawt_f1	= 0,
		.veq_stawt_f2	= 0,		    .veq_wen		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbw_end        = 1079,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},

	{
		.name       = "1080p@50Hz",
		.cwock		= 148500,
		.wefwesh	= 50000,
		.ovewsampwe     = 1,
		.component_onwy = twue,

		.hsync_end      = 88,               .hbwank_end         = 235,
		.hbwank_stawt   = 2155,             .htotaw             = 2639,

		.pwogwessive	= twue,		    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 8,               .vsync_stawt_f2     = 8,
		.vsync_wen      = 10,

		.veq_ena	= fawse,	.veq_stawt_f1	= 0,
		.veq_stawt_f2	= 0,		    .veq_wen		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbw_end        = 1079,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},

	{
		.name       = "1080p@60Hz",
		.cwock		= 148500,
		.wefwesh	= 60000,
		.ovewsampwe     = 1,
		.component_onwy = twue,

		.hsync_end      = 88,               .hbwank_end         = 235,
		.hbwank_stawt   = 2155,             .htotaw             = 2199,

		.pwogwessive	= twue,		    .twiwevew_sync = twue,

		.vsync_stawt_f1 = 8,               .vsync_stawt_f2     = 8,
		.vsync_wen      = 10,

		.veq_ena	= fawse,		    .veq_stawt_f1	= 0,
		.veq_stawt_f2	= 0,		    .veq_wen		= 0,

		.vi_end_f1      = 44,               .vi_end_f2          = 44,
		.nbw_end        = 1079,

		.buwst_ena      = fawse,

		.fiwtew_tabwe = fiwtew_tabwe,
	},
};

stwuct intew_tv_connectow_state {
	stwuct dwm_connectow_state base;

	/*
	 * May need to ovewwide the usew mawgins fow
	 * gen3 >1024 wide souwce vewticaw centewing.
	 */
	stwuct {
		u16 top, bottom;
	} mawgins;

	boow bypass_vfiwtew;
};

#define to_intew_tv_connectow_state(x) containew_of(x, stwuct intew_tv_connectow_state, base)

static stwuct dwm_connectow_state *
intew_tv_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct intew_tv_connectow_state *state;

	state = kmemdup(connectow->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &state->base);
	wetuwn &state->base;
}

static stwuct intew_tv *enc_to_tv(stwuct intew_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct intew_tv, base);
}

static stwuct intew_tv *intew_attached_tv(stwuct intew_connectow *connectow)
{
	wetuwn enc_to_tv(intew_attached_encodew(connectow));
}

static boow
intew_tv_get_hw_state(stwuct intew_encodew *encodew, enum pipe *pipe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	u32 tmp = intew_de_wead(dev_pwiv, TV_CTW);

	*pipe = (tmp & TV_ENC_PIPE_SEW_MASK) >> TV_ENC_PIPE_SEW_SHIFT;

	wetuwn tmp & TV_ENC_ENABWE;
}

static void
intew_enabwe_tv(stwuct intew_atomic_state *state,
		stwuct intew_encodew *encodew,
		const stwuct intew_cwtc_state *pipe_config,
		const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);

	/* Pwevents vbwank waits fwom timing out in intew_tv_detect_type() */
	intew_cwtc_wait_fow_next_vbwank(to_intew_cwtc(pipe_config->uapi.cwtc));

	intew_de_wmw(dev_pwiv, TV_CTW, 0, TV_ENC_ENABWE);
}

static void
intew_disabwe_tv(stwuct intew_atomic_state *state,
		 stwuct intew_encodew *encodew,
		 const stwuct intew_cwtc_state *owd_cwtc_state,
		 const stwuct dwm_connectow_state *owd_conn_state)
{
	stwuct dwm_device *dev = encodew->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);

	intew_de_wmw(dev_pwiv, TV_CTW, TV_ENC_ENABWE, 0);
}

static const stwuct tv_mode *intew_tv_mode_find(const stwuct dwm_connectow_state *conn_state)
{
	int fowmat = conn_state->tv.mode;

	wetuwn &tv_modes[fowmat];
}

static enum dwm_mode_status
intew_tv_mode_vawid(stwuct dwm_connectow *connectow,
		    stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	const stwuct tv_mode *tv_mode = intew_tv_mode_find(connectow->state);
	int max_dotcwk = i915->max_dotcwk_fweq;
	enum dwm_mode_status status;

	status = intew_cpu_twanscodew_mode_vawid(i915, mode);
	if (status != MODE_OK)
		wetuwn status;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	if (mode->cwock > max_dotcwk)
		wetuwn MODE_CWOCK_HIGH;

	/* Ensuwe TV wefwesh is cwose to desiwed wefwesh */
	if (abs(tv_mode->wefwesh - dwm_mode_vwefwesh(mode) * 1000) >= 1000)
		wetuwn MODE_CWOCK_WANGE;

	wetuwn MODE_OK;
}

static int
intew_tv_mode_vdispway(const stwuct tv_mode *tv_mode)
{
	if (tv_mode->pwogwessive)
		wetuwn tv_mode->nbw_end + 1;
	ewse
		wetuwn 2 * (tv_mode->nbw_end + 1);
}

static void
intew_tv_mode_to_mode(stwuct dwm_dispway_mode *mode,
		      const stwuct tv_mode *tv_mode,
		      int cwock)
{
	mode->cwock = cwock / (tv_mode->ovewsampwe >> !tv_mode->pwogwessive);

	/*
	 * tv_mode howizontaw timings:
	 *
	 * hsync_end
	 *    | hbwank_end
	 *    |    | hbwank_stawt
	 *    |    |       | htotaw
	 *    |     _______    |
	 *     ____/       \___
	 * \__/                \
	 */
	mode->hdispway =
		tv_mode->hbwank_stawt - tv_mode->hbwank_end;
	mode->hsync_stawt = mode->hdispway +
		tv_mode->htotaw - tv_mode->hbwank_stawt;
	mode->hsync_end = mode->hsync_stawt +
		tv_mode->hsync_end;
	mode->htotaw = tv_mode->htotaw + 1;

	/*
	 * tv_mode vewticaw timings:
	 *
	 * vsync_stawt
	 *    | vsync_end
	 *    |  | vi_end nbw_end
	 *    |  |    |       |
	 *    |  |     _______
	 * \__    ____/       \
	 *    \__/
	 */
	mode->vdispway = intew_tv_mode_vdispway(tv_mode);
	if (tv_mode->pwogwessive) {
		mode->vsync_stawt = mode->vdispway +
			tv_mode->vsync_stawt_f1 + 1;
		mode->vsync_end = mode->vsync_stawt +
			tv_mode->vsync_wen;
		mode->vtotaw = mode->vdispway +
			tv_mode->vi_end_f1 + 1;
	} ewse {
		mode->vsync_stawt = mode->vdispway +
			tv_mode->vsync_stawt_f1 + 1 +
			tv_mode->vsync_stawt_f2 + 1;
		mode->vsync_end = mode->vsync_stawt +
			2 * tv_mode->vsync_wen;
		mode->vtotaw = mode->vdispway +
			tv_mode->vi_end_f1 + 1 +
			tv_mode->vi_end_f2 + 1;
	}

	/* TV has it's own notion of sync and othew mode fwags, so cweaw them. */
	mode->fwags = 0;

	snpwintf(mode->name, sizeof(mode->name),
		 "%dx%d%c (%s)",
		 mode->hdispway, mode->vdispway,
		 tv_mode->pwogwessive ? 'p' : 'i',
		 tv_mode->name);
}

static void intew_tv_scawe_mode_howiz(stwuct dwm_dispway_mode *mode,
				      int hdispway, int weft_mawgin,
				      int wight_mawgin)
{
	int hsync_stawt = mode->hsync_stawt - mode->hdispway + wight_mawgin;
	int hsync_end = mode->hsync_end - mode->hdispway + wight_mawgin;
	int new_htotaw = mode->htotaw * hdispway /
		(mode->hdispway - weft_mawgin - wight_mawgin);

	mode->cwock = mode->cwock * new_htotaw / mode->htotaw;

	mode->hdispway = hdispway;
	mode->hsync_stawt = hdispway + hsync_stawt * new_htotaw / mode->htotaw;
	mode->hsync_end = hdispway + hsync_end * new_htotaw / mode->htotaw;
	mode->htotaw = new_htotaw;
}

static void intew_tv_scawe_mode_vewt(stwuct dwm_dispway_mode *mode,
				     int vdispway, int top_mawgin,
				     int bottom_mawgin)
{
	int vsync_stawt = mode->vsync_stawt - mode->vdispway + bottom_mawgin;
	int vsync_end = mode->vsync_end - mode->vdispway + bottom_mawgin;
	int new_vtotaw = mode->vtotaw * vdispway /
		(mode->vdispway - top_mawgin - bottom_mawgin);

	mode->cwock = mode->cwock * new_vtotaw / mode->vtotaw;

	mode->vdispway = vdispway;
	mode->vsync_stawt = vdispway + vsync_stawt * new_vtotaw / mode->vtotaw;
	mode->vsync_end = vdispway + vsync_end * new_vtotaw / mode->vtotaw;
	mode->vtotaw = new_vtotaw;
}

static void
intew_tv_get_config(stwuct intew_encodew *encodew,
		    stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	stwuct dwm_dispway_mode mode = {};
	u32 tv_ctw, hctw1, hctw3, vctw1, vctw2, tmp;
	stwuct tv_mode tv_mode = {};
	int hdispway = adjusted_mode->cwtc_hdispway;
	int vdispway = adjusted_mode->cwtc_vdispway;
	int xsize, ysize, xpos, ypos;

	pipe_config->output_types |= BIT(INTEW_OUTPUT_TVOUT);

	tv_ctw = intew_de_wead(dev_pwiv, TV_CTW);
	hctw1 = intew_de_wead(dev_pwiv, TV_H_CTW_1);
	hctw3 = intew_de_wead(dev_pwiv, TV_H_CTW_3);
	vctw1 = intew_de_wead(dev_pwiv, TV_V_CTW_1);
	vctw2 = intew_de_wead(dev_pwiv, TV_V_CTW_2);

	tv_mode.htotaw = (hctw1 & TV_HTOTAW_MASK) >> TV_HTOTAW_SHIFT;
	tv_mode.hsync_end = (hctw1 & TV_HSYNC_END_MASK) >> TV_HSYNC_END_SHIFT;

	tv_mode.hbwank_stawt = (hctw3 & TV_HBWANK_STAWT_MASK) >> TV_HBWANK_STAWT_SHIFT;
	tv_mode.hbwank_end = (hctw3 & TV_HSYNC_END_MASK) >> TV_HBWANK_END_SHIFT;

	tv_mode.nbw_end = (vctw1 & TV_NBW_END_MASK) >> TV_NBW_END_SHIFT;
	tv_mode.vi_end_f1 = (vctw1 & TV_VI_END_F1_MASK) >> TV_VI_END_F1_SHIFT;
	tv_mode.vi_end_f2 = (vctw1 & TV_VI_END_F2_MASK) >> TV_VI_END_F2_SHIFT;

	tv_mode.vsync_wen = (vctw2 & TV_VSYNC_WEN_MASK) >> TV_VSYNC_WEN_SHIFT;
	tv_mode.vsync_stawt_f1 = (vctw2 & TV_VSYNC_STAWT_F1_MASK) >> TV_VSYNC_STAWT_F1_SHIFT;
	tv_mode.vsync_stawt_f2 = (vctw2 & TV_VSYNC_STAWT_F2_MASK) >> TV_VSYNC_STAWT_F2_SHIFT;

	tv_mode.cwock = pipe_config->powt_cwock;

	tv_mode.pwogwessive = tv_ctw & TV_PWOGWESSIVE;

	switch (tv_ctw & TV_OVEWSAMPWE_MASK) {
	case TV_OVEWSAMPWE_8X:
		tv_mode.ovewsampwe = 8;
		bweak;
	case TV_OVEWSAMPWE_4X:
		tv_mode.ovewsampwe = 4;
		bweak;
	case TV_OVEWSAMPWE_2X:
		tv_mode.ovewsampwe = 2;
		bweak;
	defauwt:
		tv_mode.ovewsampwe = 1;
		bweak;
	}

	tmp = intew_de_wead(dev_pwiv, TV_WIN_POS);
	xpos = tmp >> 16;
	ypos = tmp & 0xffff;

	tmp = intew_de_wead(dev_pwiv, TV_WIN_SIZE);
	xsize = tmp >> 16;
	ysize = tmp & 0xffff;

	intew_tv_mode_to_mode(&mode, &tv_mode, pipe_config->powt_cwock);

	dwm_dbg_kms(&dev_pwiv->dwm, "TV mode: " DWM_MODE_FMT "\n",
		    DWM_MODE_AWG(&mode));

	intew_tv_scawe_mode_howiz(&mode, hdispway,
				  xpos, mode.hdispway - xsize - xpos);
	intew_tv_scawe_mode_vewt(&mode, vdispway,
				 ypos, mode.vdispway - ysize - ypos);

	adjusted_mode->cwtc_cwock = mode.cwock;
	if (adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		adjusted_mode->cwtc_cwock /= 2;

	/* pixew countew doesn't wowk on i965gm TV output */
	if (IS_I965GM(dev_pwiv))
		pipe_config->mode_fwags |=
			I915_MODE_FWAG_USE_SCANWINE_COUNTEW;
}

static boow intew_tv_souwce_too_wide(stwuct dwm_i915_pwivate *dev_pwiv,
				     int hdispway)
{
	wetuwn DISPWAY_VEW(dev_pwiv) == 3 && hdispway > 1024;
}

static boow intew_tv_vewt_scawing(const stwuct dwm_dispway_mode *tv_mode,
				  const stwuct dwm_connectow_state *conn_state,
				  int vdispway)
{
	wetuwn tv_mode->cwtc_vdispway -
		conn_state->tv.mawgins.top -
		conn_state->tv.mawgins.bottom !=
		vdispway;
}

static int
intew_tv_compute_config(stwuct intew_encodew *encodew,
			stwuct intew_cwtc_state *pipe_config,
			stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_atomic_state *state =
		to_intew_atomic_state(pipe_config->uapi.state);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_tv_connectow_state *tv_conn_state =
		to_intew_tv_connectow_state(conn_state);
	const stwuct tv_mode *tv_mode = intew_tv_mode_find(conn_state);
	stwuct dwm_dispway_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	int hdispway = adjusted_mode->cwtc_hdispway;
	int vdispway = adjusted_mode->cwtc_vdispway;
	int wet;

	if (!tv_mode)
		wetuwn -EINVAW;

	if (adjusted_mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn -EINVAW;

	pipe_config->sink_fowmat = INTEW_OUTPUT_FOWMAT_WGB;
	pipe_config->output_fowmat = INTEW_OUTPUT_FOWMAT_WGB;

	dwm_dbg_kms(&dev_pwiv->dwm, "fowcing bpc to 8 fow TV\n");
	pipe_config->pipe_bpp = 8*3;

	pipe_config->powt_cwock = tv_mode->cwock;

	wet = intew_dpww_cwtc_compute_cwock(state, cwtc);
	if (wet)
		wetuwn wet;

	pipe_config->cwock_set = twue;

	intew_tv_mode_to_mode(adjusted_mode, tv_mode, pipe_config->powt_cwock);
	dwm_mode_set_cwtcinfo(adjusted_mode, 0);

	if (intew_tv_souwce_too_wide(dev_pwiv, hdispway) ||
	    !intew_tv_vewt_scawing(adjusted_mode, conn_state, vdispway)) {
		int extwa, top, bottom;

		extwa = adjusted_mode->cwtc_vdispway - vdispway;

		if (extwa < 0) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "No vewticaw scawing fow >1024 pixew wide modes\n");
			wetuwn -EINVAW;
		}

		/* Need to tuwn off the vewticaw fiwtew and centew the image */

		/* Attempt to maintain the wewative sizes of the mawgins */
		top = conn_state->tv.mawgins.top;
		bottom = conn_state->tv.mawgins.bottom;

		if (top + bottom)
			top = extwa * top / (top + bottom);
		ewse
			top = extwa / 2;
		bottom = extwa - top;

		tv_conn_state->mawgins.top = top;
		tv_conn_state->mawgins.bottom = bottom;

		tv_conn_state->bypass_vfiwtew = twue;

		if (!tv_mode->pwogwessive) {
			adjusted_mode->cwock /= 2;
			adjusted_mode->cwtc_cwock /= 2;
			adjusted_mode->fwags |= DWM_MODE_FWAG_INTEWWACE;
		}
	} ewse {
		tv_conn_state->mawgins.top = conn_state->tv.mawgins.top;
		tv_conn_state->mawgins.bottom = conn_state->tv.mawgins.bottom;

		tv_conn_state->bypass_vfiwtew = fawse;
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "TV mode: " DWM_MODE_FMT "\n",
		    DWM_MODE_AWG(adjusted_mode));

	/*
	 * The pipe scanwine countew behaviouw wooks as fowwows when
	 * using the TV encodew:
	 *
	 * time ->
	 *
	 * dsw=vtotaw-1       |             |
	 *                   ||            ||
	 *               ___| |        ___| |
	 *              /     |       /     |
	 *             /      |      /      |
	 * dsw=0   ___/       |_____/       |
	 *        | | |  |  | |
	 *         ^ ^ ^   ^ ^
	 *         | | |   | pipe vbwank/fiwst pawt of tv vbwank
	 *         | | |   bottom mawgin
	 *         | | active
	 *         | top mawgin
	 *         wemaindew of tv vbwank
	 *
	 * When the TV encodew is used the pipe wants to wun fastew
	 * than expected wate. Duwing the active powtion the TV
	 * encodew stawws the pipe evewy few wines to keep it in
	 * check. When the TV encodew weaches the bottom mawgin the
	 * pipe simpwy stops. Once we weach the TV vbwank the pipe is
	 * no wongew stawwed and it wuns at the max wate (appawentwy
	 * ovewsampwe cwock on gen3, cdcwk on gen4). Once the pipe
	 * weaches the pipe vtotaw the pipe stops fow the wemaindew
	 * of the TV vbwank/top mawgin. The pipe stawts up again when
	 * the TV encodew exits the top mawgin.
	 *
	 * To avoid huge hasswes fow vbwank timestamping we scawe
	 * the pipe timings as if the pipe awways wuns at the avewage
	 * wate it maintains duwing the active pewiod. This awso
	 * gives us a weasonabwe guesstimate as to the pixew wate.
	 * Due to the vawiation in the actuaw pipe speed the scanwine
	 * countew wiww give us swightwy ewwoneous wesuwts duwing the
	 * TV vbwank/mawgins. But since vtotaw was sewected such that
	 * it matches the avewage wate of the pipe duwing the active
	 * powtion the ewwow shouwdn't cause any sewious gwief to
	 * vbwank timestamps.
	 *
	 * Fow postewity hewe is the empiwicawwy dewived fowmuwa
	 * that gives us the maximum wength of the pipe vbwank
	 * we can use without causing dispway cowwuption. Fowwowing
	 * this wouwd awwow us to have a ticking scanwine countew
	 * evewywhewe except duwing the bottom mawgin (thewe the
	 * pipe awways stops). Ie. this wouwd ewiminate the second
	 * fwat powtion of the above gwaph. Howevew this wouwd awso
	 * compwicate vbwank timestamping as the pipe vtotaw wouwd
	 * no wongew match the avewage wate the pipe wuns at duwing
	 * the active powtion. Hence fowwowing this fowmuwa seems
	 * mowe twoubwe that it's wowth.
	 *
	 * if (GWAPHICS_VEW(dev_pwiv) == 4) {
	 *	num = cdcwk * (tv_mode->ovewsampwe >> !tv_mode->pwogwessive);
	 *	den = tv_mode->cwock;
	 * } ewse {
	 *	num = tv_mode->ovewsampwe >> !tv_mode->pwogwessive;
	 *	den = 1;
	 * }
	 * max_pipe_vbwank_wen ~=
	 *	(num * tv_htotaw * (tv_vbwank_wen + top_mawgin)) /
	 *	(den * pipe_htotaw);
	 */
	intew_tv_scawe_mode_howiz(adjusted_mode, hdispway,
				  conn_state->tv.mawgins.weft,
				  conn_state->tv.mawgins.wight);
	intew_tv_scawe_mode_vewt(adjusted_mode, vdispway,
				 tv_conn_state->mawgins.top,
				 tv_conn_state->mawgins.bottom);
	dwm_mode_set_cwtcinfo(adjusted_mode, 0);
	adjusted_mode->name[0] = '\0';

	/* pixew countew doesn't wowk on i965gm TV output */
	if (IS_I965GM(dev_pwiv))
		pipe_config->mode_fwags |=
			I915_MODE_FWAG_USE_SCANWINE_COUNTEW;

	wetuwn 0;
}

static void
set_tv_mode_timings(stwuct dwm_i915_pwivate *dev_pwiv,
		    const stwuct tv_mode *tv_mode,
		    boow buwst_ena)
{
	u32 hctw1, hctw2, hctw3;
	u32 vctw1, vctw2, vctw3, vctw4, vctw5, vctw6, vctw7;

	hctw1 = (tv_mode->hsync_end << TV_HSYNC_END_SHIFT) |
		(tv_mode->htotaw << TV_HTOTAW_SHIFT);

	hctw2 = (tv_mode->hbuwst_stawt << 16) |
		(tv_mode->hbuwst_wen << TV_HBUWST_WEN_SHIFT);

	if (buwst_ena)
		hctw2 |= TV_BUWST_ENA;

	hctw3 = (tv_mode->hbwank_stawt << TV_HBWANK_STAWT_SHIFT) |
		(tv_mode->hbwank_end << TV_HBWANK_END_SHIFT);

	vctw1 = (tv_mode->nbw_end << TV_NBW_END_SHIFT) |
		(tv_mode->vi_end_f1 << TV_VI_END_F1_SHIFT) |
		(tv_mode->vi_end_f2 << TV_VI_END_F2_SHIFT);

	vctw2 = (tv_mode->vsync_wen << TV_VSYNC_WEN_SHIFT) |
		(tv_mode->vsync_stawt_f1 << TV_VSYNC_STAWT_F1_SHIFT) |
		(tv_mode->vsync_stawt_f2 << TV_VSYNC_STAWT_F2_SHIFT);

	vctw3 = (tv_mode->veq_wen << TV_VEQ_WEN_SHIFT) |
		(tv_mode->veq_stawt_f1 << TV_VEQ_STAWT_F1_SHIFT) |
		(tv_mode->veq_stawt_f2 << TV_VEQ_STAWT_F2_SHIFT);

	if (tv_mode->veq_ena)
		vctw3 |= TV_EQUAW_ENA;

	vctw4 = (tv_mode->vbuwst_stawt_f1 << TV_VBUWST_STAWT_F1_SHIFT) |
		(tv_mode->vbuwst_end_f1 << TV_VBUWST_END_F1_SHIFT);

	vctw5 = (tv_mode->vbuwst_stawt_f2 << TV_VBUWST_STAWT_F2_SHIFT) |
		(tv_mode->vbuwst_end_f2 << TV_VBUWST_END_F2_SHIFT);

	vctw6 = (tv_mode->vbuwst_stawt_f3 << TV_VBUWST_STAWT_F3_SHIFT) |
		(tv_mode->vbuwst_end_f3 << TV_VBUWST_END_F3_SHIFT);

	vctw7 = (tv_mode->vbuwst_stawt_f4 << TV_VBUWST_STAWT_F4_SHIFT) |
		(tv_mode->vbuwst_end_f4 << TV_VBUWST_END_F4_SHIFT);

	intew_de_wwite(dev_pwiv, TV_H_CTW_1, hctw1);
	intew_de_wwite(dev_pwiv, TV_H_CTW_2, hctw2);
	intew_de_wwite(dev_pwiv, TV_H_CTW_3, hctw3);
	intew_de_wwite(dev_pwiv, TV_V_CTW_1, vctw1);
	intew_de_wwite(dev_pwiv, TV_V_CTW_2, vctw2);
	intew_de_wwite(dev_pwiv, TV_V_CTW_3, vctw3);
	intew_de_wwite(dev_pwiv, TV_V_CTW_4, vctw4);
	intew_de_wwite(dev_pwiv, TV_V_CTW_5, vctw5);
	intew_de_wwite(dev_pwiv, TV_V_CTW_6, vctw6);
	intew_de_wwite(dev_pwiv, TV_V_CTW_7, vctw7);
}

static void set_cowow_convewsion(stwuct dwm_i915_pwivate *dev_pwiv,
				 const stwuct cowow_convewsion *cowow_convewsion)
{
	intew_de_wwite(dev_pwiv, TV_CSC_Y,
		       (cowow_convewsion->wy << 16) | cowow_convewsion->gy);
	intew_de_wwite(dev_pwiv, TV_CSC_Y2,
		       (cowow_convewsion->by << 16) | cowow_convewsion->ay);
	intew_de_wwite(dev_pwiv, TV_CSC_U,
		       (cowow_convewsion->wu << 16) | cowow_convewsion->gu);
	intew_de_wwite(dev_pwiv, TV_CSC_U2,
		       (cowow_convewsion->bu << 16) | cowow_convewsion->au);
	intew_de_wwite(dev_pwiv, TV_CSC_V,
		       (cowow_convewsion->wv << 16) | cowow_convewsion->gv);
	intew_de_wwite(dev_pwiv, TV_CSC_V2,
		       (cowow_convewsion->bv << 16) | cowow_convewsion->av);
}

static void intew_tv_pwe_enabwe(stwuct intew_atomic_state *state,
				stwuct intew_encodew *encodew,
				const stwuct intew_cwtc_state *pipe_config,
				const stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(pipe_config->uapi.cwtc);
	stwuct intew_tv *intew_tv = enc_to_tv(encodew);
	const stwuct intew_tv_connectow_state *tv_conn_state =
		to_intew_tv_connectow_state(conn_state);
	const stwuct tv_mode *tv_mode = intew_tv_mode_find(conn_state);
	u32 tv_ctw, tv_fiwtew_ctw;
	u32 scctw1, scctw2, scctw3;
	int i, j;
	const stwuct video_wevews *video_wevews;
	const stwuct cowow_convewsion *cowow_convewsion;
	boow buwst_ena;
	int xpos, ypos;
	unsigned int xsize, ysize;

	tv_ctw = intew_de_wead(dev_pwiv, TV_CTW);
	tv_ctw &= TV_CTW_SAVE;

	switch (intew_tv->type) {
	defauwt:
	case DWM_MODE_CONNECTOW_Unknown:
	case DWM_MODE_CONNECTOW_Composite:
		tv_ctw |= TV_ENC_OUTPUT_COMPOSITE;
		video_wevews = tv_mode->composite_wevews;
		cowow_convewsion = tv_mode->composite_cowow;
		buwst_ena = tv_mode->buwst_ena;
		bweak;
	case DWM_MODE_CONNECTOW_Component:
		tv_ctw |= TV_ENC_OUTPUT_COMPONENT;
		video_wevews = &component_wevews;
		if (tv_mode->buwst_ena)
			cowow_convewsion = &sdtv_csc_ypwpb;
		ewse
			cowow_convewsion = &hdtv_csc_ypwpb;
		buwst_ena = fawse;
		bweak;
	case DWM_MODE_CONNECTOW_SVIDEO:
		tv_ctw |= TV_ENC_OUTPUT_SVIDEO;
		video_wevews = tv_mode->svideo_wevews;
		cowow_convewsion = tv_mode->svideo_cowow;
		buwst_ena = tv_mode->buwst_ena;
		bweak;
	}

	tv_ctw |= TV_ENC_PIPE_SEW(cwtc->pipe);

	switch (tv_mode->ovewsampwe) {
	case 8:
		tv_ctw |= TV_OVEWSAMPWE_8X;
		bweak;
	case 4:
		tv_ctw |= TV_OVEWSAMPWE_4X;
		bweak;
	case 2:
		tv_ctw |= TV_OVEWSAMPWE_2X;
		bweak;
	defauwt:
		tv_ctw |= TV_OVEWSAMPWE_NONE;
		bweak;
	}

	if (tv_mode->pwogwessive)
		tv_ctw |= TV_PWOGWESSIVE;
	if (tv_mode->twiwevew_sync)
		tv_ctw |= TV_TWIWEVEW_SYNC;
	if (tv_mode->paw_buwst)
		tv_ctw |= TV_PAW_BUWST;

	scctw1 = 0;
	if (tv_mode->dda1_inc)
		scctw1 |= TV_SC_DDA1_EN;
	if (tv_mode->dda2_inc)
		scctw1 |= TV_SC_DDA2_EN;
	if (tv_mode->dda3_inc)
		scctw1 |= TV_SC_DDA3_EN;
	scctw1 |= tv_mode->sc_weset;
	if (video_wevews)
		scctw1 |= video_wevews->buwst << TV_BUWST_WEVEW_SHIFT;
	scctw1 |= tv_mode->dda1_inc << TV_SCDDA1_INC_SHIFT;

	scctw2 = tv_mode->dda2_size << TV_SCDDA2_SIZE_SHIFT |
		tv_mode->dda2_inc << TV_SCDDA2_INC_SHIFT;

	scctw3 = tv_mode->dda3_size << TV_SCDDA3_SIZE_SHIFT |
		tv_mode->dda3_inc << TV_SCDDA3_INC_SHIFT;

	/* Enabwe two fixes fow the chips that need them. */
	if (IS_I915GM(dev_pwiv))
		tv_ctw |= TV_ENC_C0_FIX | TV_ENC_SDP_FIX;

	set_tv_mode_timings(dev_pwiv, tv_mode, buwst_ena);

	intew_de_wwite(dev_pwiv, TV_SC_CTW_1, scctw1);
	intew_de_wwite(dev_pwiv, TV_SC_CTW_2, scctw2);
	intew_de_wwite(dev_pwiv, TV_SC_CTW_3, scctw3);

	set_cowow_convewsion(dev_pwiv, cowow_convewsion);

	if (DISPWAY_VEW(dev_pwiv) >= 4)
		intew_de_wwite(dev_pwiv, TV_CWW_KNOBS, 0x00404000);
	ewse
		intew_de_wwite(dev_pwiv, TV_CWW_KNOBS, 0x00606000);

	if (video_wevews)
		intew_de_wwite(dev_pwiv, TV_CWW_WEVEW,
			       ((video_wevews->bwack << TV_BWACK_WEVEW_SHIFT) | (video_wevews->bwank << TV_BWANK_WEVEW_SHIFT)));

	assewt_twanscodew_disabwed(dev_pwiv, pipe_config->cpu_twanscodew);

	/* Fiwtew ctw must be set befowe TV_WIN_SIZE */
	tv_fiwtew_ctw = TV_AUTO_SCAWE;
	if (tv_conn_state->bypass_vfiwtew)
		tv_fiwtew_ctw |= TV_V_FIWTEW_BYPASS;
	intew_de_wwite(dev_pwiv, TV_FIWTEW_CTW_1, tv_fiwtew_ctw);

	xsize = tv_mode->hbwank_stawt - tv_mode->hbwank_end;
	ysize = intew_tv_mode_vdispway(tv_mode);

	xpos = conn_state->tv.mawgins.weft;
	ypos = tv_conn_state->mawgins.top;
	xsize -= (conn_state->tv.mawgins.weft +
		  conn_state->tv.mawgins.wight);
	ysize -= (tv_conn_state->mawgins.top +
		  tv_conn_state->mawgins.bottom);
	intew_de_wwite(dev_pwiv, TV_WIN_POS, (xpos << 16) | ypos);
	intew_de_wwite(dev_pwiv, TV_WIN_SIZE, (xsize << 16) | ysize);

	j = 0;
	fow (i = 0; i < 60; i++)
		intew_de_wwite(dev_pwiv, TV_H_WUMA(i),
			       tv_mode->fiwtew_tabwe[j++]);
	fow (i = 0; i < 60; i++)
		intew_de_wwite(dev_pwiv, TV_H_CHWOMA(i),
			       tv_mode->fiwtew_tabwe[j++]);
	fow (i = 0; i < 43; i++)
		intew_de_wwite(dev_pwiv, TV_V_WUMA(i),
			       tv_mode->fiwtew_tabwe[j++]);
	fow (i = 0; i < 43; i++)
		intew_de_wwite(dev_pwiv, TV_V_CHWOMA(i),
			       tv_mode->fiwtew_tabwe[j++]);
	intew_de_wwite(dev_pwiv, TV_DAC,
		       intew_de_wead(dev_pwiv, TV_DAC) & TV_DAC_SAVE);
	intew_de_wwite(dev_pwiv, TV_CTW, tv_ctw);
}

static int
intew_tv_detect_type(stwuct intew_tv *intew_tv,
		      stwuct dwm_connectow *connectow)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(connectow->state->cwtc);
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	u32 tv_ctw, save_tv_ctw;
	u32 tv_dac, save_tv_dac;
	int type;

	/* Disabwe TV intewwupts awound woad detect ow we'ww wecuwse */
	if (connectow->powwed & DWM_CONNECTOW_POWW_HPD) {
		spin_wock_iwq(&dev_pwiv->iwq_wock);
		i915_disabwe_pipestat(dev_pwiv, 0,
				      PIPE_HOTPWUG_INTEWWUPT_STATUS |
				      PIPE_HOTPWUG_TV_INTEWWUPT_STATUS);
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
	}

	save_tv_dac = tv_dac = intew_de_wead(dev_pwiv, TV_DAC);
	save_tv_ctw = tv_ctw = intew_de_wead(dev_pwiv, TV_CTW);

	/* Poww fow TV detection */
	tv_ctw &= ~(TV_ENC_ENABWE | TV_ENC_PIPE_SEW_MASK | TV_TEST_MODE_MASK);
	tv_ctw |= TV_TEST_MODE_MONITOW_DETECT;
	tv_ctw |= TV_ENC_PIPE_SEW(cwtc->pipe);

	tv_dac &= ~(TVDAC_SENSE_MASK | DAC_A_MASK | DAC_B_MASK | DAC_C_MASK);
	tv_dac |= (TVDAC_STATE_CHG_EN |
		   TVDAC_A_SENSE_CTW |
		   TVDAC_B_SENSE_CTW |
		   TVDAC_C_SENSE_CTW |
		   DAC_CTW_OVEWWIDE |
		   DAC_A_0_7_V |
		   DAC_B_0_7_V |
		   DAC_C_0_7_V);


	/*
	 * The TV sense state shouwd be cweawed to zewo on cantiga pwatfowm. Othewwise
	 * the TV is misdetected. This is hawdwawe wequiwement.
	 */
	if (IS_GM45(dev_pwiv))
		tv_dac &= ~(TVDAC_STATE_CHG_EN | TVDAC_A_SENSE_CTW |
			    TVDAC_B_SENSE_CTW | TVDAC_C_SENSE_CTW);

	intew_de_wwite(dev_pwiv, TV_CTW, tv_ctw);
	intew_de_wwite(dev_pwiv, TV_DAC, tv_dac);
	intew_de_posting_wead(dev_pwiv, TV_DAC);

	intew_cwtc_wait_fow_next_vbwank(cwtc);

	type = -1;
	tv_dac = intew_de_wead(dev_pwiv, TV_DAC);
	dwm_dbg_kms(&dev_pwiv->dwm, "TV detected: %x, %x\n", tv_ctw, tv_dac);
	/*
	 *  A B C
	 *  0 1 1 Composite
	 *  1 0 X svideo
	 *  0 0 0 Component
	 */
	if ((tv_dac & TVDAC_SENSE_MASK) == (TVDAC_B_SENSE | TVDAC_C_SENSE)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Detected Composite TV connection\n");
		type = DWM_MODE_CONNECTOW_Composite;
	} ewse if ((tv_dac & (TVDAC_A_SENSE|TVDAC_B_SENSE)) == TVDAC_A_SENSE) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Detected S-Video TV connection\n");
		type = DWM_MODE_CONNECTOW_SVIDEO;
	} ewse if ((tv_dac & TVDAC_SENSE_MASK) == 0) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Detected Component TV connection\n");
		type = DWM_MODE_CONNECTOW_Component;
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm, "Unwecognised TV connection\n");
		type = -1;
	}

	intew_de_wwite(dev_pwiv, TV_DAC, save_tv_dac & ~TVDAC_STATE_CHG_EN);
	intew_de_wwite(dev_pwiv, TV_CTW, save_tv_ctw);
	intew_de_posting_wead(dev_pwiv, TV_CTW);

	/* Fow unknown weasons the hw bawfs if we don't do this vbwank wait. */
	intew_cwtc_wait_fow_next_vbwank(cwtc);

	/* Westowe intewwupt config */
	if (connectow->powwed & DWM_CONNECTOW_POWW_HPD) {
		spin_wock_iwq(&dev_pwiv->iwq_wock);
		i915_enabwe_pipestat(dev_pwiv, 0,
				     PIPE_HOTPWUG_INTEWWUPT_STATUS |
				     PIPE_HOTPWUG_TV_INTEWWUPT_STATUS);
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
	}

	wetuwn type;
}

/*
 * Hewe we set accuwate tv fowmat accowding to connectow type
 * i.e Component TV shouwd not be assigned by NTSC ow PAW
 */
static void intew_tv_find_bettew_fowmat(stwuct dwm_connectow *connectow)
{
	stwuct intew_tv *intew_tv = intew_attached_tv(to_intew_connectow(connectow));
	const stwuct tv_mode *tv_mode = intew_tv_mode_find(connectow->state);
	int i;

	/* Component suppowts evewything so we can keep the cuwwent mode */
	if (intew_tv->type == DWM_MODE_CONNECTOW_Component)
		wetuwn;

	/* If the cuwwent mode is fine don't change it */
	if (!tv_mode->component_onwy)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(tv_modes); i++) {
		tv_mode = &tv_modes[i];

		if (!tv_mode->component_onwy)
			bweak;
	}

	connectow->state->tv.mode = i;
}

static int
intew_tv_detect(stwuct dwm_connectow *connectow,
		stwuct dwm_modeset_acquiwe_ctx *ctx,
		boow fowce)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	stwuct intew_tv *intew_tv = intew_attached_tv(to_intew_connectow(connectow));
	enum dwm_connectow_status status;
	int type;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] fowce=%d\n",
		    connectow->base.id, connectow->name, fowce);

	if (!intew_dispway_device_enabwed(i915))
		wetuwn connectow_status_disconnected;

	if (fowce) {
		stwuct dwm_atomic_state *state;

		state = intew_woad_detect_get_pipe(connectow, ctx);
		if (IS_EWW(state))
			wetuwn PTW_EWW(state);

		if (state) {
			type = intew_tv_detect_type(intew_tv, connectow);
			intew_woad_detect_wewease_pipe(connectow, state, ctx);
			status = type < 0 ?
				connectow_status_disconnected :
				connectow_status_connected;
		} ewse {
			status = connectow_status_unknown;
		}

		if (status == connectow_status_connected) {
			intew_tv->type = type;
			intew_tv_find_bettew_fowmat(connectow);
		}

		wetuwn status;
	} ewse
		wetuwn connectow->status;
}

static const stwuct input_wes {
	u16 w, h;
} input_wes_tabwe[] = {
	{ 640, 480 },
	{ 800, 600 },
	{ 1024, 768 },
	{ 1280, 1024 },
	{ 848, 480 },
	{ 1280, 720 },
	{ 1920, 1080 },
};

/* Choose pwefewwed mode accowding to wine numbew of TV fowmat */
static boow
intew_tv_is_pwefewwed_mode(const stwuct dwm_dispway_mode *mode,
			   const stwuct tv_mode *tv_mode)
{
	int vdispway = intew_tv_mode_vdispway(tv_mode);

	/* pwefew 480 wine modes fow aww SD TV modes */
	if (vdispway <= 576)
		vdispway = 480;

	wetuwn vdispway == mode->vdispway;
}

static void
intew_tv_set_mode_type(stwuct dwm_dispway_mode *mode,
		       const stwuct tv_mode *tv_mode)
{
	mode->type = DWM_MODE_TYPE_DWIVEW;

	if (intew_tv_is_pwefewwed_mode(mode, tv_mode))
		mode->type |= DWM_MODE_TYPE_PWEFEWWED;
}

static int
intew_tv_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->dev);
	const stwuct tv_mode *tv_mode = intew_tv_mode_find(connectow->state);
	int i, count = 0;

	fow (i = 0; i < AWWAY_SIZE(input_wes_tabwe); i++) {
		const stwuct input_wes *input = &input_wes_tabwe[i];
		stwuct dwm_dispway_mode *mode;

		if (input->w > 1024 &&
		    !tv_mode->pwogwessive &&
		    !tv_mode->component_onwy)
			continue;

		/* no vewticaw scawing with wide souwces on gen3 */
		if (DISPWAY_VEW(dev_pwiv) == 3 && input->w > 1024 &&
		    input->h > intew_tv_mode_vdispway(tv_mode))
			continue;

		mode = dwm_mode_cweate(connectow->dev);
		if (!mode)
			continue;

		/*
		 * We take the TV mode and scawe it to wook
		 * wike it had the expected h/vdispway. This
		 * pwovides the most infowmation to usewspace
		 * about the actuaw timings of the mode. We
		 * do ignowe the mawgins though.
		 */
		intew_tv_mode_to_mode(mode, tv_mode, tv_mode->cwock);
		if (count == 0) {
			dwm_dbg_kms(&dev_pwiv->dwm, "TV mode: " DWM_MODE_FMT "\n",
				    DWM_MODE_AWG(mode));
		}
		intew_tv_scawe_mode_howiz(mode, input->w, 0, 0);
		intew_tv_scawe_mode_vewt(mode, input->h, 0, 0);
		intew_tv_set_mode_type(mode, tv_mode);

		dwm_mode_set_name(mode);

		dwm_mode_pwobed_add(connectow, mode);
		count++;
	}

	wetuwn count;
}

static const stwuct dwm_connectow_funcs intew_tv_connectow_funcs = {
	.wate_wegistew = intew_connectow_wegistew,
	.eawwy_unwegistew = intew_connectow_unwegistew,
	.destwoy = intew_connectow_destwoy,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.atomic_dupwicate_state = intew_tv_connectow_dupwicate_state,
};

static int intew_tv_atomic_check(stwuct dwm_connectow *connectow,
				 stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *new_state;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_connectow_state *owd_state;

	new_state = dwm_atomic_get_new_connectow_state(state, connectow);
	if (!new_state->cwtc)
		wetuwn 0;

	owd_state = dwm_atomic_get_owd_connectow_state(state, connectow);
	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_state->cwtc);

	if (owd_state->tv.mode != new_state->tv.mode ||
	    owd_state->tv.mawgins.weft != new_state->tv.mawgins.weft ||
	    owd_state->tv.mawgins.wight != new_state->tv.mawgins.wight ||
	    owd_state->tv.mawgins.top != new_state->tv.mawgins.top ||
	    owd_state->tv.mawgins.bottom != new_state->tv.mawgins.bottom) {
		/* Fowce a modeset. */

		new_cwtc_state->connectows_changed = twue;
	}

	wetuwn 0;
}

static const stwuct dwm_connectow_hewpew_funcs intew_tv_connectow_hewpew_funcs = {
	.detect_ctx = intew_tv_detect,
	.mode_vawid = intew_tv_mode_vawid,
	.get_modes = intew_tv_get_modes,
	.atomic_check = intew_tv_atomic_check,
};

static const stwuct dwm_encodew_funcs intew_tv_enc_funcs = {
	.destwoy = intew_encodew_destwoy,
};

static void intew_tv_add_pwopewties(stwuct dwm_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	stwuct dwm_connectow_state *conn_state = connectow->state;
	const chaw *tv_fowmat_names[AWWAY_SIZE(tv_modes)];
	int i;

	/* BIOS mawgin vawues */
	conn_state->tv.mawgins.weft = 54;
	conn_state->tv.mawgins.top = 36;
	conn_state->tv.mawgins.wight = 46;
	conn_state->tv.mawgins.bottom = 37;

	conn_state->tv.mode = 0;

	/* Cweate TV pwopewties then attach cuwwent vawues */
	fow (i = 0; i < AWWAY_SIZE(tv_modes); i++) {
		/* 1080p50/1080p60 not suppowted on gen3 */
		if (DISPWAY_VEW(i915) == 3 && tv_modes[i].ovewsampwe == 1)
			bweak;

		tv_fowmat_names[i] = tv_modes[i].name;
	}
	dwm_mode_cweate_tv_pwopewties_wegacy(&i915->dwm, i, tv_fowmat_names);

	dwm_object_attach_pwopewty(&connectow->base,
				   i915->dwm.mode_config.wegacy_tv_mode_pwopewty,
				   conn_state->tv.mode);
	dwm_object_attach_pwopewty(&connectow->base,
				   i915->dwm.mode_config.tv_weft_mawgin_pwopewty,
				   conn_state->tv.mawgins.weft);
	dwm_object_attach_pwopewty(&connectow->base,
				   i915->dwm.mode_config.tv_top_mawgin_pwopewty,
				   conn_state->tv.mawgins.top);
	dwm_object_attach_pwopewty(&connectow->base,
				   i915->dwm.mode_config.tv_wight_mawgin_pwopewty,
				   conn_state->tv.mawgins.wight);
	dwm_object_attach_pwopewty(&connectow->base,
				   i915->dwm.mode_config.tv_bottom_mawgin_pwopewty,
				   conn_state->tv.mawgins.bottom);
}

void
intew_tv_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_connectow *connectow;
	stwuct intew_tv *intew_tv;
	stwuct intew_encodew *intew_encodew;
	stwuct intew_connectow *intew_connectow;
	u32 tv_dac_on, tv_dac_off, save_tv_dac;

	if ((intew_de_wead(dev_pwiv, TV_CTW) & TV_FUSE_STATE_MASK) == TV_FUSE_STATE_DISABWED)
		wetuwn;

	if (!intew_bios_is_tv_pwesent(dev_pwiv)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Integwated TV is not pwesent.\n");
		wetuwn;
	}

	/*
	 * Sanity check the TV output by checking to see if the
	 * DAC wegistew howds a vawue
	 */
	save_tv_dac = intew_de_wead(dev_pwiv, TV_DAC);

	intew_de_wwite(dev_pwiv, TV_DAC, save_tv_dac | TVDAC_STATE_CHG_EN);
	tv_dac_on = intew_de_wead(dev_pwiv, TV_DAC);

	intew_de_wwite(dev_pwiv, TV_DAC, save_tv_dac & ~TVDAC_STATE_CHG_EN);
	tv_dac_off = intew_de_wead(dev_pwiv, TV_DAC);

	intew_de_wwite(dev_pwiv, TV_DAC, save_tv_dac);

	/*
	 * If the wegistew does not howd the state change enabwe
	 * bit, (eithew as a 0 ow a 1), assume it doesn't weawwy
	 * exist
	 */
	if ((tv_dac_on & TVDAC_STATE_CHG_EN) == 0 ||
	    (tv_dac_off & TVDAC_STATE_CHG_EN) != 0)
		wetuwn;

	intew_tv = kzawwoc(sizeof(*intew_tv), GFP_KEWNEW);
	if (!intew_tv) {
		wetuwn;
	}

	intew_connectow = intew_connectow_awwoc();
	if (!intew_connectow) {
		kfwee(intew_tv);
		wetuwn;
	}

	intew_encodew = &intew_tv->base;
	connectow = &intew_connectow->base;

	/*
	 * The documentation, fow the owdew chipsets at weast, wecommend
	 * using a powwing method wathew than hotpwug detection fow TVs.
	 * This is because in owdew to pewfowm the hotpwug detection, the PWWs
	 * fow the TV must be kept awive incweasing powew dwain and stawving
	 * bandwidth fwom othew encodews. Notabwy fow instance, it causes
	 * pipe undewwuns on Cwestwine when this encodew is supposedwy idwe.
	 *
	 * Mowe wecent chipsets favouw HDMI wathew than integwated S-Video.
	 */
	intew_connectow->powwed = DWM_CONNECTOW_POWW_CONNECT;

	dwm_connectow_init(&dev_pwiv->dwm, connectow, &intew_tv_connectow_funcs,
			   DWM_MODE_CONNECTOW_SVIDEO);

	dwm_encodew_init(&dev_pwiv->dwm, &intew_encodew->base, &intew_tv_enc_funcs,
			 DWM_MODE_ENCODEW_TVDAC, "TV");

	intew_encodew->compute_config = intew_tv_compute_config;
	intew_encodew->get_config = intew_tv_get_config;
	intew_encodew->pwe_enabwe = intew_tv_pwe_enabwe;
	intew_encodew->enabwe = intew_enabwe_tv;
	intew_encodew->disabwe = intew_disabwe_tv;
	intew_encodew->get_hw_state = intew_tv_get_hw_state;
	intew_connectow->get_hw_state = intew_connectow_get_hw_state;

	intew_connectow_attach_encodew(intew_connectow, intew_encodew);

	intew_encodew->type = INTEW_OUTPUT_TVOUT;
	intew_encodew->powew_domain = POWEW_DOMAIN_POWT_OTHEW;
	intew_encodew->powt = POWT_NONE;
	intew_encodew->pipe_mask = ~0;
	intew_encodew->cwoneabwe = 0;
	intew_tv->type = DWM_MODE_CONNECTOW_Unknown;

	dwm_connectow_hewpew_add(connectow, &intew_tv_connectow_hewpew_funcs);

	intew_tv_add_pwopewties(connectow);
}
