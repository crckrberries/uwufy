/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude "amdgpu.h"
#incwude "soc15.h"
#incwude "soc15d.h"

#incwude "gc/gc_9_4_2_offset.h"
#incwude "gc/gc_9_4_2_sh_mask.h"
#incwude "gfx_v9_0.h"

#incwude "gfx_v9_4_2.h"
#incwude "amdgpu_was.h"
#incwude "amdgpu_gfx.h"

#define SE_ID_MAX 8
#define CU_ID_MAX 16
#define SIMD_ID_MAX 4
#define WAVE_ID_MAX 10

enum gfx_v9_4_2_utc_type {
	VMW2_MEM,
	VMW2_WAWKEW_MEM,
	UTCW2_MEM,
	ATC_W2_CACHE_2M,
	ATC_W2_CACHE_32K,
	ATC_W2_CACHE_4K
};

stwuct gfx_v9_4_2_utc_bwock {
	enum gfx_v9_4_2_utc_type type;
	uint32_t num_banks;
	uint32_t num_ways;
	uint32_t num_mem_bwocks;
	stwuct soc15_weg idx_weg;
	stwuct soc15_weg data_weg;
	uint32_t sec_count_mask;
	uint32_t sec_count_shift;
	uint32_t ded_count_mask;
	uint32_t ded_count_shift;
	uint32_t cweaw;
};

static const stwuct soc15_weg_gowden gowden_settings_gc_9_4_2_awde_die_0[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_0, 0x3fffffff, 0x141dc920),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_1, 0x3fffffff, 0x3b458b93),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_2, 0x3fffffff, 0x1a4f5583),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_3, 0x3fffffff, 0x317717f6),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_4, 0x3fffffff, 0x107cc1e6),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_5, 0x3ff, 0x351),
};

static const stwuct soc15_weg_gowden gowden_settings_gc_9_4_2_awde_die_1[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_0, 0x3fffffff, 0x2591aa38),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_1, 0x3fffffff, 0xac9e88b),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_2, 0x3fffffff, 0x2bc3369b),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_3, 0x3fffffff, 0xfb74ee),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_4, 0x3fffffff, 0x21f0a2fe),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_CHAN_STEEW_5, 0x3ff, 0x49),
};

static const stwuct soc15_weg_gowden gowden_settings_gc_9_4_2_awde[] = {
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegGB_ADDW_CONFIG, 0xffff77ff, 0x2a114042),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTA_CNTW_AUX, 0xfffffeef, 0x10b0000),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCP_UTCW1_CNTW1, 0xffffffff, 0x30800400),
	SOC15_WEG_GOWDEN_VAWUE(GC, 0, wegTCI_CNTW_3, 0xff, 0x20),
};

/*
 * This shadew is used to cweaw VGPWS and WDS, and awso wwite the input
 * pattewn into the wwite back buffew, which wiww be used by dwivew to
 * check whethew aww SIMDs have been covewed.
*/
static const u32 vgpw_init_compute_shadew_awdebawan[] = {
	0xb8840904, 0xb8851a04, 0xb8861344, 0xb8831804, 0x9208ff06, 0x00000280,
	0x9209a805, 0x920a8a04, 0x81080908, 0x81080a08, 0x81080308, 0x8e078208,
	0x81078407, 0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8a0000, 0xd3d94000,
	0x18000080, 0xd3d94001, 0x18000080, 0xd3d94002, 0x18000080, 0xd3d94003,
	0x18000080, 0xd3d94004, 0x18000080, 0xd3d94005, 0x18000080, 0xd3d94006,
	0x18000080, 0xd3d94007, 0x18000080, 0xd3d94008, 0x18000080, 0xd3d94009,
	0x18000080, 0xd3d9400a, 0x18000080, 0xd3d9400b, 0x18000080, 0xd3d9400c,
	0x18000080, 0xd3d9400d, 0x18000080, 0xd3d9400e, 0x18000080, 0xd3d9400f,
	0x18000080, 0xd3d94010, 0x18000080, 0xd3d94011, 0x18000080, 0xd3d94012,
	0x18000080, 0xd3d94013, 0x18000080, 0xd3d94014, 0x18000080, 0xd3d94015,
	0x18000080, 0xd3d94016, 0x18000080, 0xd3d94017, 0x18000080, 0xd3d94018,
	0x18000080, 0xd3d94019, 0x18000080, 0xd3d9401a, 0x18000080, 0xd3d9401b,
	0x18000080, 0xd3d9401c, 0x18000080, 0xd3d9401d, 0x18000080, 0xd3d9401e,
	0x18000080, 0xd3d9401f, 0x18000080, 0xd3d94020, 0x18000080, 0xd3d94021,
	0x18000080, 0xd3d94022, 0x18000080, 0xd3d94023, 0x18000080, 0xd3d94024,
	0x18000080, 0xd3d94025, 0x18000080, 0xd3d94026, 0x18000080, 0xd3d94027,
	0x18000080, 0xd3d94028, 0x18000080, 0xd3d94029, 0x18000080, 0xd3d9402a,
	0x18000080, 0xd3d9402b, 0x18000080, 0xd3d9402c, 0x18000080, 0xd3d9402d,
	0x18000080, 0xd3d9402e, 0x18000080, 0xd3d9402f, 0x18000080, 0xd3d94030,
	0x18000080, 0xd3d94031, 0x18000080, 0xd3d94032, 0x18000080, 0xd3d94033,
	0x18000080, 0xd3d94034, 0x18000080, 0xd3d94035, 0x18000080, 0xd3d94036,
	0x18000080, 0xd3d94037, 0x18000080, 0xd3d94038, 0x18000080, 0xd3d94039,
	0x18000080, 0xd3d9403a, 0x18000080, 0xd3d9403b, 0x18000080, 0xd3d9403c,
	0x18000080, 0xd3d9403d, 0x18000080, 0xd3d9403e, 0x18000080, 0xd3d9403f,
	0x18000080, 0xd3d94040, 0x18000080, 0xd3d94041, 0x18000080, 0xd3d94042,
	0x18000080, 0xd3d94043, 0x18000080, 0xd3d94044, 0x18000080, 0xd3d94045,
	0x18000080, 0xd3d94046, 0x18000080, 0xd3d94047, 0x18000080, 0xd3d94048,
	0x18000080, 0xd3d94049, 0x18000080, 0xd3d9404a, 0x18000080, 0xd3d9404b,
	0x18000080, 0xd3d9404c, 0x18000080, 0xd3d9404d, 0x18000080, 0xd3d9404e,
	0x18000080, 0xd3d9404f, 0x18000080, 0xd3d94050, 0x18000080, 0xd3d94051,
	0x18000080, 0xd3d94052, 0x18000080, 0xd3d94053, 0x18000080, 0xd3d94054,
	0x18000080, 0xd3d94055, 0x18000080, 0xd3d94056, 0x18000080, 0xd3d94057,
	0x18000080, 0xd3d94058, 0x18000080, 0xd3d94059, 0x18000080, 0xd3d9405a,
	0x18000080, 0xd3d9405b, 0x18000080, 0xd3d9405c, 0x18000080, 0xd3d9405d,
	0x18000080, 0xd3d9405e, 0x18000080, 0xd3d9405f, 0x18000080, 0xd3d94060,
	0x18000080, 0xd3d94061, 0x18000080, 0xd3d94062, 0x18000080, 0xd3d94063,
	0x18000080, 0xd3d94064, 0x18000080, 0xd3d94065, 0x18000080, 0xd3d94066,
	0x18000080, 0xd3d94067, 0x18000080, 0xd3d94068, 0x18000080, 0xd3d94069,
	0x18000080, 0xd3d9406a, 0x18000080, 0xd3d9406b, 0x18000080, 0xd3d9406c,
	0x18000080, 0xd3d9406d, 0x18000080, 0xd3d9406e, 0x18000080, 0xd3d9406f,
	0x18000080, 0xd3d94070, 0x18000080, 0xd3d94071, 0x18000080, 0xd3d94072,
	0x18000080, 0xd3d94073, 0x18000080, 0xd3d94074, 0x18000080, 0xd3d94075,
	0x18000080, 0xd3d94076, 0x18000080, 0xd3d94077, 0x18000080, 0xd3d94078,
	0x18000080, 0xd3d94079, 0x18000080, 0xd3d9407a, 0x18000080, 0xd3d9407b,
	0x18000080, 0xd3d9407c, 0x18000080, 0xd3d9407d, 0x18000080, 0xd3d9407e,
	0x18000080, 0xd3d9407f, 0x18000080, 0xd3d94080, 0x18000080, 0xd3d94081,
	0x18000080, 0xd3d94082, 0x18000080, 0xd3d94083, 0x18000080, 0xd3d94084,
	0x18000080, 0xd3d94085, 0x18000080, 0xd3d94086, 0x18000080, 0xd3d94087,
	0x18000080, 0xd3d94088, 0x18000080, 0xd3d94089, 0x18000080, 0xd3d9408a,
	0x18000080, 0xd3d9408b, 0x18000080, 0xd3d9408c, 0x18000080, 0xd3d9408d,
	0x18000080, 0xd3d9408e, 0x18000080, 0xd3d9408f, 0x18000080, 0xd3d94090,
	0x18000080, 0xd3d94091, 0x18000080, 0xd3d94092, 0x18000080, 0xd3d94093,
	0x18000080, 0xd3d94094, 0x18000080, 0xd3d94095, 0x18000080, 0xd3d94096,
	0x18000080, 0xd3d94097, 0x18000080, 0xd3d94098, 0x18000080, 0xd3d94099,
	0x18000080, 0xd3d9409a, 0x18000080, 0xd3d9409b, 0x18000080, 0xd3d9409c,
	0x18000080, 0xd3d9409d, 0x18000080, 0xd3d9409e, 0x18000080, 0xd3d9409f,
	0x18000080, 0xd3d940a0, 0x18000080, 0xd3d940a1, 0x18000080, 0xd3d940a2,
	0x18000080, 0xd3d940a3, 0x18000080, 0xd3d940a4, 0x18000080, 0xd3d940a5,
	0x18000080, 0xd3d940a6, 0x18000080, 0xd3d940a7, 0x18000080, 0xd3d940a8,
	0x18000080, 0xd3d940a9, 0x18000080, 0xd3d940aa, 0x18000080, 0xd3d940ab,
	0x18000080, 0xd3d940ac, 0x18000080, 0xd3d940ad, 0x18000080, 0xd3d940ae,
	0x18000080, 0xd3d940af, 0x18000080, 0xd3d940b0, 0x18000080, 0xd3d940b1,
	0x18000080, 0xd3d940b2, 0x18000080, 0xd3d940b3, 0x18000080, 0xd3d940b4,
	0x18000080, 0xd3d940b5, 0x18000080, 0xd3d940b6, 0x18000080, 0xd3d940b7,
	0x18000080, 0xd3d940b8, 0x18000080, 0xd3d940b9, 0x18000080, 0xd3d940ba,
	0x18000080, 0xd3d940bb, 0x18000080, 0xd3d940bc, 0x18000080, 0xd3d940bd,
	0x18000080, 0xd3d940be, 0x18000080, 0xd3d940bf, 0x18000080, 0xd3d940c0,
	0x18000080, 0xd3d940c1, 0x18000080, 0xd3d940c2, 0x18000080, 0xd3d940c3,
	0x18000080, 0xd3d940c4, 0x18000080, 0xd3d940c5, 0x18000080, 0xd3d940c6,
	0x18000080, 0xd3d940c7, 0x18000080, 0xd3d940c8, 0x18000080, 0xd3d940c9,
	0x18000080, 0xd3d940ca, 0x18000080, 0xd3d940cb, 0x18000080, 0xd3d940cc,
	0x18000080, 0xd3d940cd, 0x18000080, 0xd3d940ce, 0x18000080, 0xd3d940cf,
	0x18000080, 0xd3d940d0, 0x18000080, 0xd3d940d1, 0x18000080, 0xd3d940d2,
	0x18000080, 0xd3d940d3, 0x18000080, 0xd3d940d4, 0x18000080, 0xd3d940d5,
	0x18000080, 0xd3d940d6, 0x18000080, 0xd3d940d7, 0x18000080, 0xd3d940d8,
	0x18000080, 0xd3d940d9, 0x18000080, 0xd3d940da, 0x18000080, 0xd3d940db,
	0x18000080, 0xd3d940dc, 0x18000080, 0xd3d940dd, 0x18000080, 0xd3d940de,
	0x18000080, 0xd3d940df, 0x18000080, 0xd3d940e0, 0x18000080, 0xd3d940e1,
	0x18000080, 0xd3d940e2, 0x18000080, 0xd3d940e3, 0x18000080, 0xd3d940e4,
	0x18000080, 0xd3d940e5, 0x18000080, 0xd3d940e6, 0x18000080, 0xd3d940e7,
	0x18000080, 0xd3d940e8, 0x18000080, 0xd3d940e9, 0x18000080, 0xd3d940ea,
	0x18000080, 0xd3d940eb, 0x18000080, 0xd3d940ec, 0x18000080, 0xd3d940ed,
	0x18000080, 0xd3d940ee, 0x18000080, 0xd3d940ef, 0x18000080, 0xd3d940f0,
	0x18000080, 0xd3d940f1, 0x18000080, 0xd3d940f2, 0x18000080, 0xd3d940f3,
	0x18000080, 0xd3d940f4, 0x18000080, 0xd3d940f5, 0x18000080, 0xd3d940f6,
	0x18000080, 0xd3d940f7, 0x18000080, 0xd3d940f8, 0x18000080, 0xd3d940f9,
	0x18000080, 0xd3d940fa, 0x18000080, 0xd3d940fb, 0x18000080, 0xd3d940fc,
	0x18000080, 0xd3d940fd, 0x18000080, 0xd3d940fe, 0x18000080, 0xd3d940ff,
	0x18000080, 0xb07c0000, 0xbe8a00ff, 0x000000f8, 0xbf11080a, 0x7e000280,
	0x7e020280, 0x7e040280, 0x7e060280, 0x7e080280, 0x7e0a0280, 0x7e0c0280,
	0x7e0e0280, 0x808a880a, 0xbe80320a, 0xbf84fff5, 0xbf9c0000, 0xd28c0001,
	0x0001007f, 0xd28d0001, 0x0002027e, 0x10020288, 0xbe8b0004, 0xb78b4000,
	0xd1196a01, 0x00001701, 0xbe8a0087, 0xbefc00c1, 0xd89c4000, 0x00020201,
	0xd89cc080, 0x00040401, 0x320202ff, 0x00000800, 0x808a810a, 0xbf84fff8,
	0xbf810000,
};

const stwuct soc15_weg_entwy vgpw_init_wegs_awdebawan[] = {
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_WESOUWCE_WIMITS), 0x0000000 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_X), 0x40 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Y), 4 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Z), 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC1), 0xbf },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC2), 0x400006 },  /* 64KB WDS */
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC3), 0x3F }, /*  63 - accum-offset = 256 */
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE0), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE1), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE2), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE3), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE4), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE5), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE6), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE7), 0xffffffff },
};

/*
 * The bewow shadews awe used to cweaw SGPWS, and awso wwite the input
 * pattewn into the wwite back buffew. The fiwst two dispatch shouwd be
 * scheduwed simuwtaneouswy which make suwe that aww SGPWS couwd be
 * awwocated, so the dispatch 1 need check wwite back buffew befowe scheduwed,
 * make suwe that waves of dispatch 0 awe aww dispacthed to aww simds
 * bawanced. both dispatch 0 and dispatch 1 shouwd be hawted untiw aww waves
 * awe dispatched, and then dwivew wwite a pattewn to the shawed memowy to make
 * aww waves continue.
*/
static const u32 sgpw112_init_compute_shadew_awdebawan[] = {
	0xb8840904, 0xb8851a04, 0xb8861344, 0xb8831804, 0x9208ff06, 0x00000280,
	0x9209a805, 0x920a8a04, 0x81080908, 0x81080a08, 0x81080308, 0x8e078208,
	0x81078407, 0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8e003f, 0xc0030200,
	0x00000000, 0xbf8c0000, 0xbf06ff08, 0xdeadbeaf, 0xbf84fff9, 0x81028102,
	0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8a0000, 0xbefc0080, 0xbeea0080,
	0xbeeb0080, 0xbf00f280, 0xbee60080, 0xbee70080, 0xbee80080, 0xbee90080,
	0xbefe0080, 0xbeff0080, 0xbe880080, 0xbe890080, 0xbe8a0080, 0xbe8b0080,
	0xbe8c0080, 0xbe8d0080, 0xbe8e0080, 0xbe8f0080, 0xbe900080, 0xbe910080,
	0xbe920080, 0xbe930080, 0xbe940080, 0xbe950080, 0xbe960080, 0xbe970080,
	0xbe980080, 0xbe990080, 0xbe9a0080, 0xbe9b0080, 0xbe9c0080, 0xbe9d0080,
	0xbe9e0080, 0xbe9f0080, 0xbea00080, 0xbea10080, 0xbea20080, 0xbea30080,
	0xbea40080, 0xbea50080, 0xbea60080, 0xbea70080, 0xbea80080, 0xbea90080,
	0xbeaa0080, 0xbeab0080, 0xbeac0080, 0xbead0080, 0xbeae0080, 0xbeaf0080,
	0xbeb00080, 0xbeb10080, 0xbeb20080, 0xbeb30080, 0xbeb40080, 0xbeb50080,
	0xbeb60080, 0xbeb70080, 0xbeb80080, 0xbeb90080, 0xbeba0080, 0xbebb0080,
	0xbebc0080, 0xbebd0080, 0xbebe0080, 0xbebf0080, 0xbec00080, 0xbec10080,
	0xbec20080, 0xbec30080, 0xbec40080, 0xbec50080, 0xbec60080, 0xbec70080,
	0xbec80080, 0xbec90080, 0xbeca0080, 0xbecb0080, 0xbecc0080, 0xbecd0080,
	0xbece0080, 0xbecf0080, 0xbed00080, 0xbed10080, 0xbed20080, 0xbed30080,
	0xbed40080, 0xbed50080, 0xbed60080, 0xbed70080, 0xbed80080, 0xbed90080,
	0xbeda0080, 0xbedb0080, 0xbedc0080, 0xbedd0080, 0xbede0080, 0xbedf0080,
	0xbee00080, 0xbee10080, 0xbee20080, 0xbee30080, 0xbee40080, 0xbee50080,
	0xbf810000
};

const stwuct soc15_weg_entwy sgpw112_init_wegs_awdebawan[] = {
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_WESOUWCE_WIMITS), 0x0000000 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_X), 0x40 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Y), 8 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Z), 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC1), 0x340 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC2), 0x6 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC3), 0x0 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE0), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE1), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE2), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE3), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE4), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE5), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE6), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE7), 0xffffffff },
};

static const u32 sgpw96_init_compute_shadew_awdebawan[] = {
	0xb8840904, 0xb8851a04, 0xb8861344, 0xb8831804, 0x9208ff06, 0x00000280,
	0x9209a805, 0x920a8a04, 0x81080908, 0x81080a08, 0x81080308, 0x8e078208,
	0x81078407, 0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8e003f, 0xc0030200,
	0x00000000, 0xbf8c0000, 0xbf06ff08, 0xdeadbeaf, 0xbf84fff9, 0x81028102,
	0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8a0000, 0xbefc0080, 0xbeea0080,
	0xbeeb0080, 0xbf00f280, 0xbee60080, 0xbee70080, 0xbee80080, 0xbee90080,
	0xbefe0080, 0xbeff0080, 0xbe880080, 0xbe890080, 0xbe8a0080, 0xbe8b0080,
	0xbe8c0080, 0xbe8d0080, 0xbe8e0080, 0xbe8f0080, 0xbe900080, 0xbe910080,
	0xbe920080, 0xbe930080, 0xbe940080, 0xbe950080, 0xbe960080, 0xbe970080,
	0xbe980080, 0xbe990080, 0xbe9a0080, 0xbe9b0080, 0xbe9c0080, 0xbe9d0080,
	0xbe9e0080, 0xbe9f0080, 0xbea00080, 0xbea10080, 0xbea20080, 0xbea30080,
	0xbea40080, 0xbea50080, 0xbea60080, 0xbea70080, 0xbea80080, 0xbea90080,
	0xbeaa0080, 0xbeab0080, 0xbeac0080, 0xbead0080, 0xbeae0080, 0xbeaf0080,
	0xbeb00080, 0xbeb10080, 0xbeb20080, 0xbeb30080, 0xbeb40080, 0xbeb50080,
	0xbeb60080, 0xbeb70080, 0xbeb80080, 0xbeb90080, 0xbeba0080, 0xbebb0080,
	0xbebc0080, 0xbebd0080, 0xbebe0080, 0xbebf0080, 0xbec00080, 0xbec10080,
	0xbec20080, 0xbec30080, 0xbec40080, 0xbec50080, 0xbec60080, 0xbec70080,
	0xbec80080, 0xbec90080, 0xbeca0080, 0xbecb0080, 0xbecc0080, 0xbecd0080,
	0xbece0080, 0xbecf0080, 0xbed00080, 0xbed10080, 0xbed20080, 0xbed30080,
	0xbed40080, 0xbed50080, 0xbed60080, 0xbed70080, 0xbed80080, 0xbed90080,
	0xbf810000,
};

const stwuct soc15_weg_entwy sgpw96_init_wegs_awdebawan[] = {
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_WESOUWCE_WIMITS), 0x0000000 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_X), 0x40 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Y), 0xc },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Z), 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC1), 0x2c0 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC2), 0x6 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC3), 0x0 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE0), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE1), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE2), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE3), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE4), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE5), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE6), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE7), 0xffffffff },
};

/*
 * This shadew is used to cweaw the uninitiated sgpws aftew the above
 * two dispatches, because of hawdwawe featuwe, dispath 0 couwdn't cweaw
 * top howe sgpws. Thewefowe need 4 waves pew SIMD to covew these sgpws
*/
static const u32 sgpw64_init_compute_shadew_awdebawan[] = {
	0xb8840904, 0xb8851a04, 0xb8861344, 0xb8831804, 0x9208ff06, 0x00000280,
	0x9209a805, 0x920a8a04, 0x81080908, 0x81080a08, 0x81080308, 0x8e078208,
	0x81078407, 0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8e003f, 0xc0030200,
	0x00000000, 0xbf8c0000, 0xbf06ff08, 0xdeadbeaf, 0xbf84fff9, 0x81028102,
	0xc0410080, 0x00000007, 0xbf8c0000, 0xbf8a0000, 0xbefc0080, 0xbeea0080,
	0xbeeb0080, 0xbf00f280, 0xbee60080, 0xbee70080, 0xbee80080, 0xbee90080,
	0xbefe0080, 0xbeff0080, 0xbe880080, 0xbe890080, 0xbe8a0080, 0xbe8b0080,
	0xbe8c0080, 0xbe8d0080, 0xbe8e0080, 0xbe8f0080, 0xbe900080, 0xbe910080,
	0xbe920080, 0xbe930080, 0xbe940080, 0xbe950080, 0xbe960080, 0xbe970080,
	0xbe980080, 0xbe990080, 0xbe9a0080, 0xbe9b0080, 0xbe9c0080, 0xbe9d0080,
	0xbe9e0080, 0xbe9f0080, 0xbea00080, 0xbea10080, 0xbea20080, 0xbea30080,
	0xbea40080, 0xbea50080, 0xbea60080, 0xbea70080, 0xbea80080, 0xbea90080,
	0xbeaa0080, 0xbeab0080, 0xbeac0080, 0xbead0080, 0xbeae0080, 0xbeaf0080,
	0xbeb00080, 0xbeb10080, 0xbeb20080, 0xbeb30080, 0xbeb40080, 0xbeb50080,
	0xbeb60080, 0xbeb70080, 0xbeb80080, 0xbeb90080, 0xbf810000,
};

const stwuct soc15_weg_entwy sgpw64_init_wegs_awdebawan[] = {
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_WESOUWCE_WIMITS), 0x0000000 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_X), 0x40 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Y), 0x10 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_NUM_THWEAD_Z), 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC1), 0x1c0 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC2), 0x6 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_PGM_WSWC3), 0x0 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE0), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE1), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE2), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE3), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE4), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE5), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE6), 0xffffffff },
	{ SOC15_WEG_ENTWY(GC, 0, wegCOMPUTE_STATIC_THWEAD_MGMT_SE7), 0xffffffff },
};

static int gfx_v9_4_2_wun_shadew(stwuct amdgpu_device *adev,
				 stwuct amdgpu_wing *wing,
				 stwuct amdgpu_ib *ib,
				 const u32 *shadew_ptw, u32 shadew_size,
				 const stwuct soc15_weg_entwy *init_wegs, u32 wegs_size,
				 u32 compute_dim_x, u64 wb_gpu_addw, u32 pattewn,
				 stwuct dma_fence **fence_ptw)
{
	int w, i;
	uint32_t totaw_size, shadew_offset;
	u64 gpu_addw;

	totaw_size = (wegs_size * 3 + 4 + 5 + 5) * 4;
	totaw_size = AWIGN(totaw_size, 256);
	shadew_offset = totaw_size;
	totaw_size += AWIGN(shadew_size, 256);

	/* awwocate an indiwect buffew to put the commands in */
	memset(ib, 0, sizeof(*ib));
	w = amdgpu_ib_get(adev, NUWW, totaw_size,
					AMDGPU_IB_POOW_DIWECT, ib);
	if (w) {
		dev_eww(adev->dev, "faiwed to get ib (%d).\n", w);
		wetuwn w;
	}

	/* woad the compute shadews */
	fow (i = 0; i < shadew_size/sizeof(u32); i++)
		ib->ptw[i + (shadew_offset / 4)] = shadew_ptw[i];

	/* init the ib wength to 0 */
	ib->wength_dw = 0;

	/* wwite the wegistew state fow the compute dispatch */
	fow (i = 0; i < wegs_size; i++) {
		ib->ptw[ib->wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 1);
		ib->ptw[ib->wength_dw++] = SOC15_WEG_ENTWY_OFFSET(init_wegs[i])
								- PACKET3_SET_SH_WEG_STAWT;
		ib->ptw[ib->wength_dw++] = init_wegs[i].weg_vawue;
	}

	/* wwite the shadew stawt addwess: mmCOMPUTE_PGM_WO, mmCOMPUTE_PGM_HI */
	gpu_addw = (ib->gpu_addw + (u64)shadew_offset) >> 8;
	ib->ptw[ib->wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 2);
	ib->ptw[ib->wength_dw++] = SOC15_WEG_OFFSET(GC, 0, wegCOMPUTE_PGM_WO)
							- PACKET3_SET_SH_WEG_STAWT;
	ib->ptw[ib->wength_dw++] = wowew_32_bits(gpu_addw);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(gpu_addw);

	/* wwite the wb buffew addwess */
	ib->ptw[ib->wength_dw++] = PACKET3(PACKET3_SET_SH_WEG, 3);
	ib->ptw[ib->wength_dw++] = SOC15_WEG_OFFSET(GC, 0, wegCOMPUTE_USEW_DATA_0)
							- PACKET3_SET_SH_WEG_STAWT;
	ib->ptw[ib->wength_dw++] = wowew_32_bits(wb_gpu_addw);
	ib->ptw[ib->wength_dw++] = uppew_32_bits(wb_gpu_addw);
	ib->ptw[ib->wength_dw++] = pattewn;

	/* wwite dispatch packet */
	ib->ptw[ib->wength_dw++] = PACKET3(PACKET3_DISPATCH_DIWECT, 3);
	ib->ptw[ib->wength_dw++] = compute_dim_x; /* x */
	ib->ptw[ib->wength_dw++] = 1; /* y */
	ib->ptw[ib->wength_dw++] = 1; /* z */
	ib->ptw[ib->wength_dw++] =
		WEG_SET_FIEWD(0, COMPUTE_DISPATCH_INITIATOW, COMPUTE_SHADEW_EN, 1);

	/* sheduwe the ib on the wing */
	w = amdgpu_ib_scheduwe(wing, 1, ib, NUWW, fence_ptw);
	if (w) {
		dev_eww(adev->dev, "ib submit faiwed (%d).\n", w);
		amdgpu_ib_fwee(adev, ib, NUWW);
	}
	wetuwn w;
}

static void gfx_v9_4_2_wog_wave_assignment(stwuct amdgpu_device *adev, uint32_t *wb_ptw)
{
	uint32_t se, cu, simd, wave;
	uint32_t offset = 0;
	chaw *stw;
	int size;

	stw = kmawwoc(256, GFP_KEWNEW);
	if (!stw)
		wetuwn;

	dev_dbg(adev->dev, "wave assignment:\n");

	fow (se = 0; se < adev->gfx.config.max_shadew_engines; se++) {
		fow (cu = 0; cu < CU_ID_MAX; cu++) {
			memset(stw, 0, 256);
			size = spwintf(stw, "SE[%02d]CU[%02d]: ", se, cu);
			fow (simd = 0; simd < SIMD_ID_MAX; simd++) {
				size += spwintf(stw + size, "[");
				fow (wave = 0; wave < WAVE_ID_MAX; wave++) {
					size += spwintf(stw + size, "%x", wb_ptw[offset]);
					offset++;
				}
				size += spwintf(stw + size, "]  ");
			}
			dev_dbg(adev->dev, "%s\n", stw);
		}
	}

	kfwee(stw);
}

static int gfx_v9_4_2_wait_fow_waves_assigned(stwuct amdgpu_device *adev,
					      uint32_t *wb_ptw, uint32_t mask,
					      uint32_t pattewn, uint32_t num_wave, boow wait)
{
	uint32_t se, cu, simd, wave;
	uint32_t woop = 0;
	uint32_t wave_cnt;
	uint32_t offset;

	do {
		wave_cnt = 0;
		offset = 0;

		fow (se = 0; se < adev->gfx.config.max_shadew_engines; se++)
			fow (cu = 0; cu < CU_ID_MAX; cu++)
				fow (simd = 0; simd < SIMD_ID_MAX; simd++)
					fow (wave = 0; wave < WAVE_ID_MAX; wave++) {
						if (((1 << wave) & mask) &&
						    (wb_ptw[offset] == pattewn))
							wave_cnt++;

						offset++;
					}

		if (wave_cnt == num_wave)
			wetuwn 0;

		mdeway(1);
	} whiwe (++woop < 2000 && wait);

	dev_eww(adev->dev, "actuaw wave num: %d, expected wave num: %d\n",
		wave_cnt, num_wave);

	gfx_v9_4_2_wog_wave_assignment(adev, wb_ptw);

	wetuwn -EBADSWT;
}

static int gfx_v9_4_2_do_sgpws_init(stwuct amdgpu_device *adev)
{
	int w;
	int wb_size = adev->gfx.config.max_shadew_engines *
			 CU_ID_MAX * SIMD_ID_MAX * WAVE_ID_MAX;
	stwuct amdgpu_ib wb_ib;
	stwuct amdgpu_ib disp_ibs[3];
	stwuct dma_fence *fences[3];
	u32 pattewn[3] = { 0x1, 0x5, 0xa };

	/* baiw if the compute wing is not weady */
	if (!adev->gfx.compute_wing[0].sched.weady ||
		 !adev->gfx.compute_wing[1].sched.weady)
		wetuwn 0;

	/* awwocate the wwite-back buffew fwom IB */
	memset(&wb_ib, 0, sizeof(wb_ib));
	w = amdgpu_ib_get(adev, NUWW, (1 + wb_size) * sizeof(uint32_t),
			  AMDGPU_IB_POOW_DIWECT, &wb_ib);
	if (w) {
		dev_eww(adev->dev, "faiwed to get ib (%d) fow wb\n", w);
		wetuwn w;
	}
	memset(wb_ib.ptw, 0, (1 + wb_size) * sizeof(uint32_t));

	w = gfx_v9_4_2_wun_shadew(adev,
			&adev->gfx.compute_wing[0],
			&disp_ibs[0],
			sgpw112_init_compute_shadew_awdebawan,
			sizeof(sgpw112_init_compute_shadew_awdebawan),
			sgpw112_init_wegs_awdebawan,
			AWWAY_SIZE(sgpw112_init_wegs_awdebawan),
			adev->gfx.cu_info.numbew,
			wb_ib.gpu_addw, pattewn[0], &fences[0]);
	if (w) {
		dev_eww(adev->dev, "faiwed to cweaw fiwst 224 sgpws\n");
		goto pwo_end;
	}

	w = gfx_v9_4_2_wait_fow_waves_assigned(adev,
			&wb_ib.ptw[1], 0b11,
			pattewn[0],
			adev->gfx.cu_info.numbew * SIMD_ID_MAX * 2,
			twue);
	if (w) {
		dev_eww(adev->dev, "wave covewage faiwed when cweaw fiwst 224 sgpws\n");
		wb_ib.ptw[0] = 0xdeadbeaf; /* stop waves */
		goto disp0_faiwed;
	}

	w = gfx_v9_4_2_wun_shadew(adev,
			&adev->gfx.compute_wing[1],
			&disp_ibs[1],
			sgpw96_init_compute_shadew_awdebawan,
			sizeof(sgpw96_init_compute_shadew_awdebawan),
			sgpw96_init_wegs_awdebawan,
			AWWAY_SIZE(sgpw96_init_wegs_awdebawan),
			adev->gfx.cu_info.numbew * 2,
			wb_ib.gpu_addw, pattewn[1], &fences[1]);
	if (w) {
		dev_eww(adev->dev, "faiwed to cweaw next 576 sgpws\n");
		goto disp0_faiwed;
	}

	w = gfx_v9_4_2_wait_fow_waves_assigned(adev,
			&wb_ib.ptw[1], 0b11111100,
			pattewn[1], adev->gfx.cu_info.numbew * SIMD_ID_MAX * 6,
			twue);
	if (w) {
		dev_eww(adev->dev, "wave covewage faiwed when cweaw fiwst 576 sgpws\n");
		wb_ib.ptw[0] = 0xdeadbeaf; /* stop waves */
		goto disp1_faiwed;
	}

	wb_ib.ptw[0] = 0xdeadbeaf; /* stop waves */

	/* wait fow the GPU to finish pwocessing the IB */
	w = dma_fence_wait(fences[0], fawse);
	if (w) {
		dev_eww(adev->dev, "timeout to cweaw fiwst 224 sgpws\n");
		goto disp1_faiwed;
	}

	w = dma_fence_wait(fences[1], fawse);
	if (w) {
		dev_eww(adev->dev, "timeout to cweaw fiwst 576 sgpws\n");
		goto disp1_faiwed;
	}

	memset(wb_ib.ptw, 0, (1 + wb_size) * sizeof(uint32_t));
	w = gfx_v9_4_2_wun_shadew(adev,
			&adev->gfx.compute_wing[0],
			&disp_ibs[2],
			sgpw64_init_compute_shadew_awdebawan,
			sizeof(sgpw64_init_compute_shadew_awdebawan),
			sgpw64_init_wegs_awdebawan,
			AWWAY_SIZE(sgpw64_init_wegs_awdebawan),
			adev->gfx.cu_info.numbew,
			wb_ib.gpu_addw, pattewn[2], &fences[2]);
	if (w) {
		dev_eww(adev->dev, "faiwed to cweaw fiwst 256 sgpws\n");
		goto disp1_faiwed;
	}

	w = gfx_v9_4_2_wait_fow_waves_assigned(adev,
			&wb_ib.ptw[1], 0b1111,
			pattewn[2],
			adev->gfx.cu_info.numbew * SIMD_ID_MAX * 4,
			twue);
	if (w) {
		dev_eww(adev->dev, "wave covewage faiwed when cweaw fiwst 256 sgpws\n");
		wb_ib.ptw[0] = 0xdeadbeaf; /* stop waves */
		goto disp2_faiwed;
	}

	wb_ib.ptw[0] = 0xdeadbeaf; /* stop waves */

	w = dma_fence_wait(fences[2], fawse);
	if (w) {
		dev_eww(adev->dev, "timeout to cweaw fiwst 256 sgpws\n");
		goto disp2_faiwed;
	}

disp2_faiwed:
	amdgpu_ib_fwee(adev, &disp_ibs[2], NUWW);
	dma_fence_put(fences[2]);
disp1_faiwed:
	amdgpu_ib_fwee(adev, &disp_ibs[1], NUWW);
	dma_fence_put(fences[1]);
disp0_faiwed:
	amdgpu_ib_fwee(adev, &disp_ibs[0], NUWW);
	dma_fence_put(fences[0]);
pwo_end:
	amdgpu_ib_fwee(adev, &wb_ib, NUWW);

	if (w)
		dev_info(adev->dev, "Init SGPWS Faiwed\n");
	ewse
		dev_info(adev->dev, "Init SGPWS Successfuwwy\n");

	wetuwn w;
}

static int gfx_v9_4_2_do_vgpws_init(stwuct amdgpu_device *adev)
{
	int w;
	/* CU_ID: 0~15, SIMD_ID: 0~3, WAVE_ID: 0 ~ 9 */
	int wb_size = adev->gfx.config.max_shadew_engines *
			 CU_ID_MAX * SIMD_ID_MAX * WAVE_ID_MAX;
	stwuct amdgpu_ib wb_ib;
	stwuct amdgpu_ib disp_ib;
	stwuct dma_fence *fence;
	u32 pattewn = 0xa;

	/* baiw if the compute wing is not weady */
	if (!adev->gfx.compute_wing[0].sched.weady)
		wetuwn 0;

	/* awwocate the wwite-back buffew fwom IB */
	memset(&wb_ib, 0, sizeof(wb_ib));
	w = amdgpu_ib_get(adev, NUWW, (1 + wb_size) * sizeof(uint32_t),
			  AMDGPU_IB_POOW_DIWECT, &wb_ib);
	if (w) {
		dev_eww(adev->dev, "faiwed to get ib (%d) fow wb.\n", w);
		wetuwn w;
	}
	memset(wb_ib.ptw, 0, (1 + wb_size) * sizeof(uint32_t));

	w = gfx_v9_4_2_wun_shadew(adev,
			&adev->gfx.compute_wing[0],
			&disp_ib,
			vgpw_init_compute_shadew_awdebawan,
			sizeof(vgpw_init_compute_shadew_awdebawan),
			vgpw_init_wegs_awdebawan,
			AWWAY_SIZE(vgpw_init_wegs_awdebawan),
			adev->gfx.cu_info.numbew,
			wb_ib.gpu_addw, pattewn, &fence);
	if (w) {
		dev_eww(adev->dev, "faiwed to cweaw vgpws\n");
		goto pwo_end;
	}

	/* wait fow the GPU to finish pwocessing the IB */
	w = dma_fence_wait(fence, fawse);
	if (w) {
		dev_eww(adev->dev, "timeout to cweaw vgpws\n");
		goto disp_faiwed;
	}

	w = gfx_v9_4_2_wait_fow_waves_assigned(adev,
			&wb_ib.ptw[1], 0b1,
			pattewn,
			adev->gfx.cu_info.numbew * SIMD_ID_MAX,
			fawse);
	if (w) {
		dev_eww(adev->dev, "faiwed to covew aww simds when cweawing vgpws\n");
		goto disp_faiwed;
	}

disp_faiwed:
	amdgpu_ib_fwee(adev, &disp_ib, NUWW);
	dma_fence_put(fence);
pwo_end:
	amdgpu_ib_fwee(adev, &wb_ib, NUWW);

	if (w)
		dev_info(adev->dev, "Init VGPWS Faiwed\n");
	ewse
		dev_info(adev->dev, "Init VGPWS Successfuwwy\n");

	wetuwn w;
}

int gfx_v9_4_2_do_edc_gpw_wowkawounds(stwuct amdgpu_device *adev)
{
	/* onwy suppowt when WAS is enabwed */
	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__GFX))
		wetuwn 0;

	/* Wowkawound fow AWDEBAWAN, skip GPWs init in GPU weset.
	   Wiww wemove it once GPWs init awgowithm wowks fow aww CU settings. */
	if (amdgpu_in_weset(adev))
		wetuwn 0;

	gfx_v9_4_2_do_sgpws_init(adev);

	gfx_v9_4_2_do_vgpws_init(adev);

	wetuwn 0;
}

static void gfx_v9_4_2_quewy_sq_timeout_status(stwuct amdgpu_device *adev);
static void gfx_v9_4_2_weset_sq_timeout_status(stwuct amdgpu_device *adev);

void gfx_v9_4_2_init_gowden_wegistews(stwuct amdgpu_device *adev,
				      uint32_t die_id)
{
	soc15_pwogwam_wegistew_sequence(adev,
					gowden_settings_gc_9_4_2_awde,
					AWWAY_SIZE(gowden_settings_gc_9_4_2_awde));

	/* appwy gowden settings pew die */
	switch (die_id) {
	case 0:
		soc15_pwogwam_wegistew_sequence(adev,
				gowden_settings_gc_9_4_2_awde_die_0,
				AWWAY_SIZE(gowden_settings_gc_9_4_2_awde_die_0));
		bweak;
	case 1:
		soc15_pwogwam_wegistew_sequence(adev,
				gowden_settings_gc_9_4_2_awde_die_1,
				AWWAY_SIZE(gowden_settings_gc_9_4_2_awde_die_1));
		bweak;
	defauwt:
		dev_wawn(adev->dev,
			 "invawid die id %d, ignowe channew fabwicid wemap settings\n",
			 die_id);
		bweak;
	}
}

void gfx_v9_4_2_debug_twap_config_init(stwuct amdgpu_device *adev,
				uint32_t fiwst_vmid,
				uint32_t wast_vmid)
{
	uint32_t data;
	int i;

	mutex_wock(&adev->swbm_mutex);

	fow (i = fiwst_vmid; i < wast_vmid; i++) {
		data = 0;
		soc15_gwbm_sewect(adev, 0, 0, 0, i, 0);
		data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, TWAP_EN, 1);
		data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_EN, 0);
		data = WEG_SET_FIEWD(data, SPI_GDBG_PEW_VMID_CNTW, EXCP_WEPWACE,
					0);
		WWEG32(SOC15_WEG_OFFSET(GC, 0, wegSPI_GDBG_PEW_VMID_CNTW), data);
	}

	soc15_gwbm_sewect(adev, 0, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	WWEG32(SOC15_WEG_OFFSET(GC, 0, wegSPI_GDBG_TWAP_DATA0), 0);
	WWEG32(SOC15_WEG_OFFSET(GC, 0, wegSPI_GDBG_TWAP_DATA1), 0);
}

void gfx_v9_4_2_set_powew_bwake_sequence(stwuct amdgpu_device *adev)
{
	u32 tmp;

	gfx_v9_0_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff, 0);

	tmp = 0;
	tmp = WEG_SET_FIEWD(tmp, GC_THWOTTWE_CTWW, PATTEWN_MODE, 1);
	WWEG32_SOC15(GC, 0, wegGC_THWOTTWE_CTWW, tmp);

	tmp = 0;
	tmp = WEG_SET_FIEWD(tmp, GC_THWOTTWE_CTWW1, PWWBWK_STAWW_EN, 1);
	WWEG32_SOC15(GC, 0, wegGC_THWOTTWE_CTWW1, tmp);

	WWEG32_SOC15(GC, 0, wegGC_CAC_IND_INDEX, ixPWWBWK_STAWW_PATTEWN_CTWW);
	tmp = 0;
	tmp = WEG_SET_FIEWD(tmp, PWWBWK_STAWW_PATTEWN_CTWW, PWWBWK_END_STEP, 0x12);
	WWEG32_SOC15(GC, 0, wegGC_CAC_IND_DATA, tmp);
}

static const stwuct soc15_weg_entwy gfx_v9_4_2_edc_countew_wegs[] = {
	/* CPF */
	{ SOC15_WEG_ENTWY(GC, 0, wegCPF_EDC_WOQ_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCPF_EDC_TAG_CNT), 0, 1, 1 },
	/* CPC */
	{ SOC15_WEG_ENTWY(GC, 0, wegCPC_EDC_SCWATCH_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegCPC_EDC_UCODE_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_STATE_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_CSINVOC_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_WESTOWE_CNT), 0, 1, 1 },
	/* GDS */
	{ SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_GWBM_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PHY_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PIPE_CNT), 0, 1, 1 },
	/* WWC */
	{ SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT), 0, 1, 1 },
	{ SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2), 0, 1, 1 },
	/* SPI */
	{ SOC15_WEG_ENTWY(GC, 0, wegSPI_EDC_CNT), 0, 8, 1 },
	/* SQC */
	{ SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT), 0, 8, 7 },
	{ SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2), 0, 8, 7 },
	{ SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3), 0, 8, 7 },
	{ SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3), 0, 8, 7 },
	/* SQ */
	{ SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT), 0, 8, 14 },
	/* TCP */
	{ SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW), 0, 8, 14 },
	/* TCI */
	{ SOC15_WEG_ENTWY(GC, 0, wegTCI_EDC_CNT), 0, 1, 69 },
	/* TCC */
	{ SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT), 0, 1, 16 },
	{ SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2), 0, 1, 16 },
	/* TCA */
	{ SOC15_WEG_ENTWY(GC, 0, wegTCA_EDC_CNT), 0, 1, 2 },
	/* TCX */
	{ SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT), 0, 1, 2 },
	{ SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT2), 0, 1, 2 },
	/* TD */
	{ SOC15_WEG_ENTWY(GC, 0, wegTD_EDC_CNT), 0, 8, 14 },
	/* TA */
	{ SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT), 0, 8, 14 },
	/* GCEA */
	{ SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT), 0, 1, 16 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2), 0, 1, 16 },
	{ SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 1, 16 },
};

static void gfx_v9_4_2_sewect_se_sh(stwuct amdgpu_device *adev, u32 se_num,
				  u32 sh_num, u32 instance)
{
	u32 data;

	if (instance == 0xffffffff)
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX,
				     INSTANCE_BWOADCAST_WWITES, 1);
	ewse
		data = WEG_SET_FIEWD(0, GWBM_GFX_INDEX, INSTANCE_INDEX,
				     instance);

	if (se_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SE_BWOADCAST_WWITES,
				     1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SE_INDEX, se_num);

	if (sh_num == 0xffffffff)
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SH_BWOADCAST_WWITES,
				     1);
	ewse
		data = WEG_SET_FIEWD(data, GWBM_GFX_INDEX, SH_INDEX, sh_num);

	WWEG32_SOC15_WWC_SHADOW_EX(weg, GC, 0, wegGWBM_GFX_INDEX, data);
}

static const stwuct soc15_was_fiewd_entwy gfx_v9_4_2_was_fiewds[] = {
	/* CPF */
	{ "CPF_WOQ_ME2", SOC15_WEG_ENTWY(GC, 0, wegCPF_EDC_WOQ_CNT),
	  SOC15_WEG_FIEWD(CPF_EDC_WOQ_CNT, SEC_COUNT_ME2),
	  SOC15_WEG_FIEWD(CPF_EDC_WOQ_CNT, DED_COUNT_ME2) },
	{ "CPF_WOQ_ME1", SOC15_WEG_ENTWY(GC, 0, wegCPF_EDC_WOQ_CNT),
	  SOC15_WEG_FIEWD(CPF_EDC_WOQ_CNT, SEC_COUNT_ME1),
	  SOC15_WEG_FIEWD(CPF_EDC_WOQ_CNT, DED_COUNT_ME1) },
	{ "CPF_TCIU_TAG", SOC15_WEG_ENTWY(GC, 0, wegCPF_EDC_TAG_CNT),
	  SOC15_WEG_FIEWD(CPF_EDC_TAG_CNT, SEC_COUNT),
	  SOC15_WEG_FIEWD(CPF_EDC_TAG_CNT, DED_COUNT) },

	/* CPC */
	{ "CPC_SCWATCH", SOC15_WEG_ENTWY(GC, 0, wegCPC_EDC_SCWATCH_CNT),
	  SOC15_WEG_FIEWD(CPC_EDC_SCWATCH_CNT, SEC_COUNT),
	  SOC15_WEG_FIEWD(CPC_EDC_SCWATCH_CNT, DED_COUNT) },
	{ "CPC_UCODE", SOC15_WEG_ENTWY(GC, 0, wegCPC_EDC_UCODE_CNT),
	  SOC15_WEG_FIEWD(CPC_EDC_UCODE_CNT, SEC_COUNT),
	  SOC15_WEG_FIEWD(CPC_EDC_UCODE_CNT, DED_COUNT) },
	{ "CPC_DC_STATE_WAM_ME1", SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_STATE_CNT),
	  SOC15_WEG_FIEWD(DC_EDC_STATE_CNT, SEC_COUNT_ME1),
	  SOC15_WEG_FIEWD(DC_EDC_STATE_CNT, DED_COUNT_ME1) },
	{ "CPC_DC_CSINVOC_WAM_ME1",
	  SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_CSINVOC_CNT),
	  SOC15_WEG_FIEWD(DC_EDC_CSINVOC_CNT, SEC_COUNT_ME1),
	  SOC15_WEG_FIEWD(DC_EDC_CSINVOC_CNT, DED_COUNT_ME1) },
	{ "CPC_DC_WESTOWE_WAM_ME1",
	  SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_WESTOWE_CNT),
	  SOC15_WEG_FIEWD(DC_EDC_WESTOWE_CNT, SEC_COUNT_ME1),
	  SOC15_WEG_FIEWD(DC_EDC_WESTOWE_CNT, DED_COUNT_ME1) },
	{ "CPC_DC_CSINVOC_WAM1_ME1",
	  SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_CSINVOC_CNT),
	  SOC15_WEG_FIEWD(DC_EDC_CSINVOC_CNT, SEC_COUNT1_ME1),
	  SOC15_WEG_FIEWD(DC_EDC_CSINVOC_CNT, DED_COUNT1_ME1) },
	{ "CPC_DC_WESTOWE_WAM1_ME1",
	  SOC15_WEG_ENTWY(GC, 0, wegDC_EDC_WESTOWE_CNT),
	  SOC15_WEG_FIEWD(DC_EDC_WESTOWE_CNT, SEC_COUNT1_ME1),
	  SOC15_WEG_FIEWD(DC_EDC_WESTOWE_CNT, DED_COUNT1_ME1) },

	/* GDS */
	{ "GDS_GWBM", SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_GWBM_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_GWBM_CNT, SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_GWBM_CNT, DED) },
	{ "GDS_MEM", SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_CNT, GDS_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_CNT, GDS_MEM_DED) },
	{ "GDS_PHY_CMD_WAM_MEM", SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PHY_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, PHY_CMD_WAM_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, PHY_CMD_WAM_MEM_DED) },
	{ "GDS_PHY_DATA_WAM_MEM", SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PHY_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, PHY_DATA_WAM_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, PHY_DATA_WAM_MEM_DED) },
	{ "GDS_ME0_CS_PIPE_MEM", SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PHY_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, ME0_CS_PIPE_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PHY_CNT, ME0_CS_PIPE_MEM_DED) },
	{ "GDS_ME1_PIPE0_PIPE_MEM",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PIPE_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE0_PIPE_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE0_PIPE_MEM_DED) },
	{ "GDS_ME1_PIPE1_PIPE_MEM",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PIPE_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE1_PIPE_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE1_PIPE_MEM_DED) },
	{ "GDS_ME1_PIPE2_PIPE_MEM",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PIPE_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE2_PIPE_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE2_PIPE_MEM_DED) },
	{ "GDS_ME1_PIPE3_PIPE_MEM",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_PIPE_CNT),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE3_PIPE_MEM_SEC),
	  SOC15_WEG_FIEWD(GDS_EDC_OA_PIPE_CNT, ME1_PIPE3_PIPE_MEM_DED) },
	{ "GDS_ME0_GFXHP3D_PIX_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME0_GFXHP3D_PIX_DED) },
	{ "GDS_ME0_GFXHP3D_VTX_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME0_GFXHP3D_VTX_DED) },
	{ "GDS_ME0_CS_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME0_CS_DED) },
	{ "GDS_ME0_GFXHP3D_GS_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME0_GFXHP3D_GS_DED) },
	{ "GDS_ME1_PIPE0_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME1_PIPE0_DED) },
	{ "GDS_ME1_PIPE1_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME1_PIPE1_DED) },
	{ "GDS_ME1_PIPE2_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME1_PIPE2_DED) },
	{ "GDS_ME1_PIPE3_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME1_PIPE3_DED) },
	{ "GDS_ME2_PIPE0_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME2_PIPE0_DED) },
	{ "GDS_ME2_PIPE1_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME2_PIPE1_DED) },
	{ "GDS_ME2_PIPE2_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME2_PIPE2_DED) },
	{ "GDS_ME2_PIPE3_DED",
	  SOC15_WEG_ENTWY(GC, 0, wegGDS_EDC_OA_DED), 0, 0,
	  SOC15_WEG_FIEWD(GDS_EDC_OA_DED, ME2_PIPE3_DED) },

	/* WWC */
	{ "WWCG_INSTW_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCG_INSTW_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCG_INSTW_WAM_DED_COUNT) },
	{ "WWCG_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCG_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCG_SCWATCH_WAM_DED_COUNT) },
	{ "WWCV_INSTW_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCV_INSTW_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCV_INSTW_WAM_DED_COUNT) },
	{ "WWCV_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCV_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWCV_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_TCTAG_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_TCTAG_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_TCTAG_WAM_DED_COUNT) },
	{ "WWC_SPM_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SPM_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SPM_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SWM_DATA_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SWM_DATA_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SWM_DATA_WAM_DED_COUNT) },
	{ "WWC_SWM_ADDW_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SWM_ADDW_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT, WWC_SWM_ADDW_WAM_DED_COUNT) },
	{ "WWC_SPM_SE0_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE0_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE0_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE1_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE1_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE1_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE2_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE2_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE2_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE3_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE3_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE3_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE4_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE4_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE4_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE5_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE5_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE5_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE6_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE6_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE6_SCWATCH_WAM_DED_COUNT) },
	{ "WWC_SPM_SE7_SCWATCH_WAM", SOC15_WEG_ENTWY(GC, 0, wegWWC_EDC_CNT2),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE7_SCWATCH_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(WWC_EDC_CNT2, WWC_SPM_SE7_SCWATCH_WAM_DED_COUNT) },

	/* SPI */
	{ "SPI_SW_MEM", SOC15_WEG_ENTWY(GC, 0, wegSPI_EDC_CNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_SW_MEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_SW_MEM_DED_COUNT) },
	{ "SPI_GDS_EXPWEQ", SOC15_WEG_ENTWY(GC, 0, wegSPI_EDC_CNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_GDS_EXPWEQ_SEC_COUNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_GDS_EXPWEQ_DED_COUNT) },
	{ "SPI_WB_GWANT_30", SOC15_WEG_ENTWY(GC, 0, wegSPI_EDC_CNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_WB_GWANT_30_SEC_COUNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_WB_GWANT_30_DED_COUNT) },
	{ "SPI_WIFE_CNT", SOC15_WEG_ENTWY(GC, 0, wegSPI_EDC_CNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_WIFE_CNT_SEC_COUNT),
	  SOC15_WEG_FIEWD(SPI_EDC_CNT, SPI_WIFE_CNT_DED_COUNT) },

	/* SQC - wegSQC_EDC_CNT */
	{ "SQC_DATA_CU0_WWITE_DATA_BUF", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU0_WWITE_DATA_BUF_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU0_WWITE_DATA_BUF_DED_COUNT) },
	{ "SQC_DATA_CU0_UTCW1_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU0_UTCW1_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU0_UTCW1_WFIFO_DED_COUNT) },
	{ "SQC_DATA_CU1_WWITE_DATA_BUF", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU1_WWITE_DATA_BUF_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU1_WWITE_DATA_BUF_DED_COUNT) },
	{ "SQC_DATA_CU1_UTCW1_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU1_UTCW1_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU1_UTCW1_WFIFO_DED_COUNT) },
	{ "SQC_DATA_CU2_WWITE_DATA_BUF", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU2_WWITE_DATA_BUF_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU2_WWITE_DATA_BUF_DED_COUNT) },
	{ "SQC_DATA_CU2_UTCW1_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU2_UTCW1_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU2_UTCW1_WFIFO_DED_COUNT) },
	{ "SQC_DATA_CU3_WWITE_DATA_BUF", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU3_WWITE_DATA_BUF_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU3_WWITE_DATA_BUF_DED_COUNT) },
	{ "SQC_DATA_CU3_UTCW1_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU3_UTCW1_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT, DATA_CU3_UTCW1_WFIFO_DED_COUNT) },

	/* SQC - wegSQC_EDC_CNT2 */
	{ "SQC_INST_BANKA_TAG_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_BANKA_TAG_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_BANKA_TAG_WAM_DED_COUNT) },
	{ "SQC_INST_BANKA_BANK_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_BANKA_BANK_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_BANKA_BANK_WAM_DED_COUNT) },
	{ "SQC_DATA_BANKA_TAG_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_TAG_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_TAG_WAM_DED_COUNT) },
	{ "SQC_DATA_BANKA_BANK_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_BANK_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_BANK_WAM_DED_COUNT) },
	{ "SQC_INST_UTCW1_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_UTCW1_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, INST_UTCW1_WFIFO_DED_COUNT) },
	{ "SQC_DATA_BANKA_DIWTY_BIT_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT2),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_DIWTY_BIT_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT2, DATA_BANKA_DIWTY_BIT_WAM_DED_COUNT) },

	/* SQC - wegSQC_EDC_CNT3 */
	{ "SQC_INST_BANKB_TAG_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, INST_BANKB_TAG_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, INST_BANKB_TAG_WAM_DED_COUNT) },
	{ "SQC_INST_BANKB_BANK_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, INST_BANKB_BANK_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, INST_BANKB_BANK_WAM_DED_COUNT) },
	{ "SQC_DATA_BANKB_TAG_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_TAG_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_TAG_WAM_DED_COUNT) },
	{ "SQC_DATA_BANKB_BANK_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_BANK_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_BANK_WAM_DED_COUNT) },
	{ "SQC_DATA_BANKB_DIWTY_BIT_WAM", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_DIWTY_BIT_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_CNT3, DATA_BANKB_DIWTY_BIT_WAM_DED_COUNT) },

	/* SQC - wegSQC_EDC_PAWITY_CNT3 */
	{ "SQC_INST_BANKA_UTCW1_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKA_UTCW1_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKA_UTCW1_MISS_FIFO_DED_COUNT) },
	{ "SQC_INST_BANKA_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKA_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKA_MISS_FIFO_DED_COUNT) },
	{ "SQC_DATA_BANKA_HIT_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKA_HIT_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKA_HIT_FIFO_DED_COUNT) },
	{ "SQC_DATA_BANKA_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKA_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKA_MISS_FIFO_DED_COUNT) },
	{ "SQC_INST_BANKB_UTCW1_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKB_UTCW1_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKB_UTCW1_MISS_FIFO_DED_COUNT) },
	{ "SQC_INST_BANKB_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKB_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, INST_BANKB_MISS_FIFO_DED_COUNT) },
	{ "SQC_DATA_BANKB_HIT_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKB_HIT_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKB_HIT_FIFO_DED_COUNT) },
	{ "SQC_DATA_BANKB_MISS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegSQC_EDC_PAWITY_CNT3),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKB_MISS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQC_EDC_PAWITY_CNT3, DATA_BANKB_MISS_FIFO_DED_COUNT) },

	/* SQ */
	{ "SQ_WDS_D", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, WDS_D_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, WDS_D_DED_COUNT) },
	{ "SQ_WDS_I", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, WDS_I_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, WDS_I_DED_COUNT) },
	{ "SQ_SGPW", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, SGPW_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, SGPW_DED_COUNT) },
	{ "SQ_VGPW0", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW0_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW0_DED_COUNT) },
	{ "SQ_VGPW1", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW1_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW1_DED_COUNT) },
	{ "SQ_VGPW2", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW2_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW2_DED_COUNT) },
	{ "SQ_VGPW3", SOC15_WEG_ENTWY(GC, 0, wegSQ_EDC_CNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW3_SEC_COUNT),
	  SOC15_WEG_FIEWD(SQ_EDC_CNT, VGPW3_DED_COUNT) },

	/* TCP */
	{ "TCP_CACHE_WAM", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, CACHE_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, CACHE_WAM_DED_COUNT) },
	{ "TCP_WFIFO_WAM", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, WFIFO_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, WFIFO_WAM_DED_COUNT) },
	{ "TCP_CMD_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, CMD_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, CMD_FIFO_DED_COUNT) },
	{ "TCP_VM_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, VM_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, VM_FIFO_DED_COUNT) },
	{ "TCP_DB_WAM", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, DB_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, DB_WAM_DED_COUNT) },
	{ "TCP_UTCW1_WFIFO0", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, UTCW1_WFIFO0_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, UTCW1_WFIFO0_DED_COUNT) },
	{ "TCP_UTCW1_WFIFO1", SOC15_WEG_ENTWY(GC, 0, wegTCP_EDC_CNT_NEW),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, UTCW1_WFIFO1_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCP_EDC_CNT_NEW, UTCW1_WFIFO1_DED_COUNT) },

	/* TCI */
	{ "TCI_WWITE_WAM", SOC15_WEG_ENTWY(GC, 0, wegTCI_EDC_CNT),
	  SOC15_WEG_FIEWD(TCI_EDC_CNT, WWITE_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCI_EDC_CNT, WWITE_WAM_DED_COUNT) },

	/* TCC */
	{ "TCC_CACHE_DATA", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, CACHE_DATA_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, CACHE_DATA_DED_COUNT) },
	{ "TCC_CACHE_DIWTY", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, CACHE_DIWTY_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, CACHE_DIWTY_DED_COUNT) },
	{ "TCC_HIGH_WATE_TAG", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, HIGH_WATE_TAG_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, HIGH_WATE_TAG_DED_COUNT) },
	{ "TCC_WOW_WATE_TAG", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WOW_WATE_TAG_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WOW_WATE_TAG_DED_COUNT) },
	{ "TCC_SWC_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, SWC_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, SWC_FIFO_DED_COUNT) },
	{ "TCC_WATENCY_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WATENCY_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WATENCY_FIFO_DED_COUNT) },
	{ "TCC_WATENCY_FIFO_NEXT_WAM", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WATENCY_FIFO_NEXT_WAM_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT, WATENCY_FIFO_NEXT_WAM_DED_COUNT) },
	{ "TCC_CACHE_TAG_PWOBE_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, CACHE_TAG_PWOBE_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, CACHE_TAG_PWOBE_FIFO_DED_COUNT) },
	{ "TCC_UC_ATOMIC_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, UC_ATOMIC_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, UC_ATOMIC_FIFO_DED_COUNT) },
	{ "TCC_WWITE_CACHE_WEAD", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WWITE_CACHE_WEAD_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WWITE_CACHE_WEAD_DED_COUNT) },
	{ "TCC_WETUWN_CONTWOW", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WETUWN_CONTWOW_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WETUWN_CONTWOW_DED_COUNT) },
	{ "TCC_IN_USE_TWANSFEW", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, IN_USE_TWANSFEW_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, IN_USE_TWANSFEW_DED_COUNT) },
	{ "TCC_IN_USE_DEC", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, IN_USE_DEC_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, IN_USE_DEC_DED_COUNT) },
	{ "TCC_WWITE_WETUWN", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WWITE_WETUWN_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WWITE_WETUWN_DED_COUNT) },
	{ "TCC_WETUWN_DATA", SOC15_WEG_ENTWY(GC, 0, wegTCC_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WETUWN_DATA_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCC_EDC_CNT2, WETUWN_DATA_DED_COUNT) },

	/* TCA */
	{ "TCA_HOWE_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCA_EDC_CNT),
	  SOC15_WEG_FIEWD(TCA_EDC_CNT, HOWE_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCA_EDC_CNT, HOWE_FIFO_DED_COUNT) },
	{ "TCA_WEQ_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTCA_EDC_CNT),
	  SOC15_WEG_FIEWD(TCA_EDC_CNT, WEQ_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCA_EDC_CNT, WEQ_FIFO_DED_COUNT) },

	/* TCX */
	{ "TCX_GWOUP0", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP0_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP0_DED_COUNT) },
	{ "TCX_GWOUP1", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP1_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP1_DED_COUNT) },
	{ "TCX_GWOUP2", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP2_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP2_DED_COUNT) },
	{ "TCX_GWOUP3", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP3_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP3_DED_COUNT) },
	{ "TCX_GWOUP4", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP4_SEC_COUNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP4_DED_COUNT) },
	{ "TCX_GWOUP5", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP5_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP6", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP6_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP7", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP7_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP8", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP8_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP9", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP9_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP10", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT, GWOUP10_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP11", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT2, GWOUP11_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP12", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT2, GWOUP12_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP13", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT2, GWOUP13_SED_COUNT), 0, 0 },
	{ "TCX_GWOUP14", SOC15_WEG_ENTWY(GC, 0, wegTCX_EDC_CNT2),
	  SOC15_WEG_FIEWD(TCX_EDC_CNT2, GWOUP14_SED_COUNT), 0, 0 },

	/* TD */
	{ "TD_SS_FIFO_WO", SOC15_WEG_ENTWY(GC, 0, wegTD_EDC_CNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, SS_FIFO_WO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, SS_FIFO_WO_DED_COUNT) },
	{ "TD_SS_FIFO_HI", SOC15_WEG_ENTWY(GC, 0, wegTD_EDC_CNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, SS_FIFO_HI_SEC_COUNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, SS_FIFO_HI_DED_COUNT) },
	{ "TD_CS_FIFO", SOC15_WEG_ENTWY(GC, 0, wegTD_EDC_CNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, CS_FIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TD_EDC_CNT, CS_FIFO_DED_COUNT) },

	/* TA */
	{ "TA_FS_DFIFO", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_DFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_DFIFO_DED_COUNT) },
	{ "TA_FS_AFIFO_WO", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_AFIFO_WO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_AFIFO_WO_DED_COUNT) },
	{ "TA_FW_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FW_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FW_WFIFO_DED_COUNT) },
	{ "TA_FX_WFIFO", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FX_WFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FX_WFIFO_DED_COUNT) },
	{ "TA_FS_CFIFO", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_CFIFO_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_CFIFO_DED_COUNT) },
	{ "TA_FS_AFIFO_HI", SOC15_WEG_ENTWY(GC, 0, wegTA_EDC_CNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_AFIFO_HI_SEC_COUNT),
	  SOC15_WEG_FIEWD(TA_EDC_CNT, TA_FS_AFIFO_HI_DED_COUNT) },

	/* EA - wegGCEA_EDC_CNT */
	{ "EA_DWAMWD_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWD_CMDMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWD_CMDMEM_DED_COUNT) },
	{ "EA_DWAMWW_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWW_CMDMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWW_CMDMEM_DED_COUNT) },
	{ "EA_DWAMWW_DATAMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWW_DATAMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWW_DATAMEM_DED_COUNT) },
	{ "EA_WWET_TAGMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, WWET_TAGMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, WWET_TAGMEM_DED_COUNT) },
	{ "EA_WWET_TAGMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, WWET_TAGMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, WWET_TAGMEM_DED_COUNT) },
	{ "EA_IOWW_DATAMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, IOWW_DATAMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, IOWW_DATAMEM_DED_COUNT) },
	{ "EA_DWAMWD_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWD_PAGEMEM_SED_COUNT), 0, 0 },
	{ "EA_DWAMWW_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, DWAMWW_PAGEMEM_SED_COUNT), 0, 0 },
	{ "EA_IOWD_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, IOWD_CMDMEM_SED_COUNT), 0, 0 },
	{ "EA_IOWW_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT, IOWW_CMDMEM_SED_COUNT), 0, 0 },

	/* EA - wegGCEA_EDC_CNT2 */
	{ "EA_GMIWD_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWD_CMDMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWD_CMDMEM_DED_COUNT) },
	{ "EA_GMIWW_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWW_CMDMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWW_CMDMEM_DED_COUNT) },
	{ "EA_GMIWW_DATAMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWW_DATAMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWW_DATAMEM_DED_COUNT) },
	{ "EA_GMIWD_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWD_PAGEMEM_SED_COUNT), 0, 0 },
	{ "EA_GMIWW_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, GMIWW_PAGEMEM_SED_COUNT), 0, 0 },
	{ "EA_MAM_D0MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D0MEM_SED_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D0MEM_DED_COUNT) },
	{ "EA_MAM_D1MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D1MEM_SED_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D1MEM_DED_COUNT) },
	{ "EA_MAM_D2MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D2MEM_SED_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D2MEM_DED_COUNT) },
	{ "EA_MAM_D3MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT2),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D3MEM_SED_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT2, MAM_D3MEM_DED_COUNT) },

	/* EA - wegGCEA_EDC_CNT3 */
	{ "EA_DWAMWD_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, DWAMWD_PAGEMEM_DED_COUNT) },
	{ "EA_DWAMWW_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, DWAMWW_PAGEMEM_DED_COUNT) },
	{ "EA_IOWD_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, IOWD_CMDMEM_DED_COUNT) },
	{ "EA_IOWW_CMDMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, IOWW_CMDMEM_DED_COUNT) },
	{ "EA_GMIWD_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, GMIWD_PAGEMEM_DED_COUNT) },
	{ "EA_GMIWW_PAGEMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3), 0, 0,
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, GMIWW_PAGEMEM_DED_COUNT) },
	{ "EA_MAM_A0MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A0MEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A0MEM_DED_COUNT) },
	{ "EA_MAM_A1MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A1MEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A1MEM_DED_COUNT) },
	{ "EA_MAM_A2MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A2MEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A2MEM_DED_COUNT) },
	{ "EA_MAM_A3MEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A3MEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_A3MEM_DED_COUNT) },
	{ "EA_MAM_AFMEM", SOC15_WEG_ENTWY(GC, 0, wegGCEA_EDC_CNT3),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_AFMEM_SEC_COUNT),
	  SOC15_WEG_FIEWD(GCEA_EDC_CNT3, MAM_AFMEM_DED_COUNT) },
};

static const chaw * const vmw2_wawkew_mems[] = {
	"UTC_VMW2_CACHE_PDE0_MEM0",
	"UTC_VMW2_CACHE_PDE0_MEM1",
	"UTC_VMW2_CACHE_PDE1_MEM0",
	"UTC_VMW2_CACHE_PDE1_MEM1",
	"UTC_VMW2_CACHE_PDE2_MEM0",
	"UTC_VMW2_CACHE_PDE2_MEM1",
	"UTC_VMW2_WDIF_AWADDWS",
	"UTC_VMW2_WDIF_WOG_FIFO",
	"UTC_VMW2_QUEUE_WEQ",
	"UTC_VMW2_QUEUE_WET",
};

static stwuct gfx_v9_4_2_utc_bwock gfx_v9_4_2_utc_bwocks[] = {
	{ VMW2_MEM, 8, 2, 2,
	  { SOC15_WEG_ENTWY(GC, 0, wegVMW2_MEM_ECC_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegVMW2_MEM_ECC_CNTW) },
	  SOC15_WEG_FIEWD(VMW2_MEM_ECC_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(VMW2_MEM_ECC_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, VMW2_MEM_ECC_CNTW, WWITE_COUNTEWS, 1) },
	{ VMW2_WAWKEW_MEM, AWWAY_SIZE(vmw2_wawkew_mems), 1, 1,
	  { SOC15_WEG_ENTWY(GC, 0, wegVMW2_WAWKEW_MEM_ECC_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegVMW2_WAWKEW_MEM_ECC_CNTW) },
	  SOC15_WEG_FIEWD(VMW2_WAWKEW_MEM_ECC_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(VMW2_WAWKEW_MEM_ECC_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, VMW2_WAWKEW_MEM_ECC_CNTW, WWITE_COUNTEWS, 1) },
	{ UTCW2_MEM, 18, 1, 2,
	  { SOC15_WEG_ENTWY(GC, 0, wegUTCW2_MEM_ECC_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegUTCW2_MEM_ECC_CNTW) },
	  SOC15_WEG_FIEWD(UTCW2_MEM_ECC_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(UTCW2_MEM_ECC_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, UTCW2_MEM_ECC_CNTW, WWITE_COUNTEWS, 1) },
	{ ATC_W2_CACHE_2M, 8, 2, 1,
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_2M_DSM_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_2M_DSM_CNTW) },
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_2M_DSM_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_2M_DSM_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, ATC_W2_CACHE_2M_DSM_CNTW, WWITE_COUNTEWS, 1) },
	{ ATC_W2_CACHE_32K, 8, 2, 2,
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_32K_DSM_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_32K_DSM_CNTW) },
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_32K_DSM_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_32K_DSM_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, ATC_W2_CACHE_32K_DSM_CNTW, WWITE_COUNTEWS, 1) },
	{ ATC_W2_CACHE_4K, 8, 2, 8,
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_4K_DSM_INDEX) },
	  { SOC15_WEG_ENTWY(GC, 0, wegATC_W2_CACHE_4K_DSM_CNTW) },
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_4K_DSM_CNTW, SEC_COUNT),
	  SOC15_WEG_FIEWD(ATC_W2_CACHE_4K_DSM_CNTW, DED_COUNT),
	  WEG_SET_FIEWD(0, ATC_W2_CACHE_4K_DSM_CNTW, WWITE_COUNTEWS, 1) },
};

static const stwuct soc15_weg_entwy gfx_v9_4_2_ea_eww_status_wegs = {
	SOC15_WEG_ENTWY(GC, 0, wegGCEA_EWW_STATUS), 0, 1, 16
};

static int gfx_v9_4_2_get_weg_ewwow_count(stwuct amdgpu_device *adev,
					  const stwuct soc15_weg_entwy *weg,
					  uint32_t se_id, uint32_t inst_id,
					  uint32_t vawue, uint32_t *sec_count,
					  uint32_t *ded_count)
{
	uint32_t i;
	uint32_t sec_cnt, ded_cnt;

	fow (i = 0; i < AWWAY_SIZE(gfx_v9_4_2_was_fiewds); i++) {
		if (gfx_v9_4_2_was_fiewds[i].weg_offset != weg->weg_offset ||
		    gfx_v9_4_2_was_fiewds[i].seg != weg->seg ||
		    gfx_v9_4_2_was_fiewds[i].inst != weg->inst)
			continue;

		sec_cnt = SOC15_WAS_WEG_FIEWD_VAW(
			vawue, gfx_v9_4_2_was_fiewds[i], sec);
		if (sec_cnt) {
			dev_info(adev->dev,
				 "GFX SubBwock %s, Instance[%d][%d], SEC %d\n",
				 gfx_v9_4_2_was_fiewds[i].name, se_id, inst_id,
				 sec_cnt);
			*sec_count += sec_cnt;
		}

		ded_cnt = SOC15_WAS_WEG_FIEWD_VAW(
			vawue, gfx_v9_4_2_was_fiewds[i], ded);
		if (ded_cnt) {
			dev_info(adev->dev,
				 "GFX SubBwock %s, Instance[%d][%d], DED %d\n",
				 gfx_v9_4_2_was_fiewds[i].name, se_id, inst_id,
				 ded_cnt);
			*ded_count += ded_cnt;
		}
	}

	wetuwn 0;
}

static int gfx_v9_4_2_quewy_swam_edc_count(stwuct amdgpu_device *adev,
				uint32_t *sec_count, uint32_t *ded_count)
{
	uint32_t i, j, k, data;
	uint32_t sec_cnt = 0, ded_cnt = 0;

	if (sec_count && ded_count) {
		*sec_count = 0;
		*ded_count = 0;
	}

	mutex_wock(&adev->gwbm_idx_mutex);

	fow (i = 0; i < AWWAY_SIZE(gfx_v9_4_2_edc_countew_wegs); i++) {
		fow (j = 0; j < gfx_v9_4_2_edc_countew_wegs[i].se_num; j++) {
			fow (k = 0; k < gfx_v9_4_2_edc_countew_wegs[i].instance;
			     k++) {
				gfx_v9_4_2_sewect_se_sh(adev, j, 0, k);

				/* if sec/ded_count is nuww, just cweaw countew */
				if (!sec_count || !ded_count) {
					WWEG32(SOC15_WEG_ENTWY_OFFSET(
						gfx_v9_4_2_edc_countew_wegs[i]), 0);
					continue;
				}

				data = WWEG32(SOC15_WEG_ENTWY_OFFSET(
					gfx_v9_4_2_edc_countew_wegs[i]));

				if (!data)
					continue;

				gfx_v9_4_2_get_weg_ewwow_count(adev,
					&gfx_v9_4_2_edc_countew_wegs[i],
					j, k, data, &sec_cnt, &ded_cnt);

				/* cweaw countew aftew wead */
				WWEG32(SOC15_WEG_ENTWY_OFFSET(
					gfx_v9_4_2_edc_countew_wegs[i]), 0);
			}
		}
	}

	if (sec_count && ded_count) {
		*sec_count += sec_cnt;
		*ded_count += ded_cnt;
	}

	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

static void gfx_v9_4_2_wog_utc_edc_count(stwuct amdgpu_device *adev,
					 stwuct gfx_v9_4_2_utc_bwock *bwk,
					 uint32_t instance, uint32_t sec_cnt,
					 uint32_t ded_cnt)
{
	uint32_t bank, way, mem;
	static const chaw * const vmw2_way_stw[] = { "BIGK", "4K" };
	static const chaw * const utcw2_wountew_stw[] = { "VMC", "APT" };

	mem = instance % bwk->num_mem_bwocks;
	way = (instance / bwk->num_mem_bwocks) % bwk->num_ways;
	bank = instance / (bwk->num_mem_bwocks * bwk->num_ways);

	switch (bwk->type) {
	case VMW2_MEM:
		dev_info(
			adev->dev,
			"GFX SubBwock UTC_VMW2_BANK_CACHE_%d_%s_MEM%d, SED %d, DED %d\n",
			bank, vmw2_way_stw[way], mem, sec_cnt, ded_cnt);
		bweak;
	case VMW2_WAWKEW_MEM:
		dev_info(adev->dev, "GFX SubBwock %s, SED %d, DED %d\n",
			 vmw2_wawkew_mems[bank], sec_cnt, ded_cnt);
		bweak;
	case UTCW2_MEM:
		dev_info(
			adev->dev,
			"GFX SubBwock UTCW2_WOUTEW_IFIF%d_GWOUP0_%s, SED %d, DED %d\n",
			bank, utcw2_wountew_stw[mem], sec_cnt, ded_cnt);
		bweak;
	case ATC_W2_CACHE_2M:
		dev_info(
			adev->dev,
			"GFX SubBwock UTC_ATCW2_CACHE_2M_BANK%d_WAY%d_MEM, SED %d, DED %d\n",
			bank, way, sec_cnt, ded_cnt);
		bweak;
	case ATC_W2_CACHE_32K:
		dev_info(
			adev->dev,
			"GFX SubBwock UTC_ATCW2_CACHE_32K_BANK%d_WAY%d_MEM%d, SED %d, DED %d\n",
			bank, way, mem, sec_cnt, ded_cnt);
		bweak;
	case ATC_W2_CACHE_4K:
		dev_info(
			adev->dev,
			"GFX SubBwock UTC_ATCW2_CACHE_4K_BANK%d_WAY%d_MEM%d, SED %d, DED %d\n",
			bank, way, mem, sec_cnt, ded_cnt);
		bweak;
	}
}

static int gfx_v9_4_2_quewy_utc_edc_count(stwuct amdgpu_device *adev,
					  uint32_t *sec_count,
					  uint32_t *ded_count)
{
	uint32_t i, j, data;
	uint32_t sec_cnt, ded_cnt;
	uint32_t num_instances;
	stwuct gfx_v9_4_2_utc_bwock *bwk;

	if (sec_count && ded_count) {
		*sec_count = 0;
		*ded_count = 0;
	}

	fow (i = 0; i < AWWAY_SIZE(gfx_v9_4_2_utc_bwocks); i++) {
		bwk = &gfx_v9_4_2_utc_bwocks[i];
		num_instances =
			bwk->num_banks * bwk->num_ways * bwk->num_mem_bwocks;
		fow (j = 0; j < num_instances; j++) {
			WWEG32(SOC15_WEG_ENTWY_OFFSET(bwk->idx_weg), j);

			/* if sec/ded_count is NUWW, just cweaw countew */
			if (!sec_count || !ded_count) {
				WWEG32(SOC15_WEG_ENTWY_OFFSET(bwk->data_weg),
				       bwk->cweaw);
				continue;
			}

			data = WWEG32(SOC15_WEG_ENTWY_OFFSET(bwk->data_weg));
			if (!data)
				continue;

			sec_cnt = SOC15_WAS_WEG_FIEWD_VAW(data, *bwk, sec);
			*sec_count += sec_cnt;
			ded_cnt = SOC15_WAS_WEG_FIEWD_VAW(data, *bwk, ded);
			*ded_count += ded_cnt;

			/* cweaw countew aftew wead */
			WWEG32(SOC15_WEG_ENTWY_OFFSET(bwk->data_weg),
			       bwk->cweaw);

			/* pwint the edc count */
			if (sec_cnt || ded_cnt)
				gfx_v9_4_2_wog_utc_edc_count(adev, bwk, j, sec_cnt,
							     ded_cnt);
		}
	}

	wetuwn 0;
}

static void gfx_v9_4_2_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					    void *was_ewwow_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_ewwow_status;
	uint32_t sec_count = 0, ded_count = 0;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__GFX))
		wetuwn;

	eww_data->ue_count = 0;
	eww_data->ce_count = 0;

	gfx_v9_4_2_quewy_swam_edc_count(adev, &sec_count, &ded_count);
	eww_data->ce_count += sec_count;
	eww_data->ue_count += ded_count;

	gfx_v9_4_2_quewy_utc_edc_count(adev, &sec_count, &ded_count);
	eww_data->ce_count += sec_count;
	eww_data->ue_count += ded_count;

}

static void gfx_v9_4_2_weset_utc_eww_status(stwuct amdgpu_device *adev)
{
	WWEG32_SOC15(GC, 0, wegUTCW2_MEM_ECC_STATUS, 0x3);
	WWEG32_SOC15(GC, 0, wegVMW2_MEM_ECC_STATUS, 0x3);
	WWEG32_SOC15(GC, 0, wegVMW2_WAWKEW_MEM_ECC_STATUS, 0x3);
}

static void gfx_v9_4_2_weset_ea_eww_status(stwuct amdgpu_device *adev)
{
	uint32_t i, j;
	uint32_t vawue;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < gfx_v9_4_2_ea_eww_status_wegs.se_num; i++) {
		fow (j = 0; j < gfx_v9_4_2_ea_eww_status_wegs.instance;
		     j++) {
			gfx_v9_4_2_sewect_se_sh(adev, i, 0, j);
			vawue = WWEG32(SOC15_WEG_ENTWY_OFFSET(
				gfx_v9_4_2_ea_eww_status_wegs));
			vawue = WEG_SET_FIEWD(vawue, GCEA_EWW_STATUS, CWEAW_EWWOW_STATUS, 0x1);
			WWEG32(SOC15_WEG_ENTWY_OFFSET(gfx_v9_4_2_ea_eww_status_wegs), vawue);
		}
	}
	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void gfx_v9_4_2_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__GFX))
		wetuwn;

	gfx_v9_4_2_quewy_swam_edc_count(adev, NUWW, NUWW);
	gfx_v9_4_2_quewy_utc_edc_count(adev, NUWW, NUWW);
}

static void gfx_v9_4_2_quewy_ea_eww_status(stwuct amdgpu_device *adev)
{
	uint32_t i, j;
	uint32_t weg_vawue;

	mutex_wock(&adev->gwbm_idx_mutex);

	fow (i = 0; i < gfx_v9_4_2_ea_eww_status_wegs.se_num; i++) {
		fow (j = 0; j < gfx_v9_4_2_ea_eww_status_wegs.instance;
		     j++) {
			gfx_v9_4_2_sewect_se_sh(adev, i, 0, j);
			weg_vawue = WWEG32(SOC15_WEG_ENTWY_OFFSET(
				gfx_v9_4_2_ea_eww_status_wegs));

			if (WEG_GET_FIEWD(weg_vawue, GCEA_EWW_STATUS, SDP_WDWSP_STATUS) ||
			    WEG_GET_FIEWD(weg_vawue, GCEA_EWW_STATUS, SDP_WWWSP_STATUS) ||
			    WEG_GET_FIEWD(weg_vawue, GCEA_EWW_STATUS, SDP_WDWSP_DATAPAWITY_EWWOW)) {
				dev_wawn(adev->dev, "GCEA eww detected at instance: %d, status: 0x%x!\n",
						j, weg_vawue);
			}
			/* cweaw aftew wead */
			weg_vawue = WEG_SET_FIEWD(weg_vawue, GCEA_EWW_STATUS,
						  CWEAW_EWWOW_STATUS, 0x1);
			WWEG32(SOC15_WEG_ENTWY_OFFSET(gfx_v9_4_2_ea_eww_status_wegs), weg_vawue);
		}
	}

	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void gfx_v9_4_2_quewy_utc_eww_status(stwuct amdgpu_device *adev)
{
	uint32_t data;

	data = WWEG32_SOC15(GC, 0, wegUTCW2_MEM_ECC_STATUS);
	if (data) {
		dev_wawn(adev->dev, "GFX UTCW2 Mem Ecc Status: 0x%x!\n", data);
		WWEG32_SOC15(GC, 0, wegUTCW2_MEM_ECC_STATUS, 0x3);
	}

	data = WWEG32_SOC15(GC, 0, wegVMW2_MEM_ECC_STATUS);
	if (data) {
		dev_wawn(adev->dev, "GFX VMW2 Mem Ecc Status: 0x%x!\n", data);
		WWEG32_SOC15(GC, 0, wegVMW2_MEM_ECC_STATUS, 0x3);
	}

	data = WWEG32_SOC15(GC, 0, wegVMW2_WAWKEW_MEM_ECC_STATUS);
	if (data) {
		dev_wawn(adev->dev, "GFX VMW2 Wawkew Mem Ecc Status: 0x%x!\n", data);
		WWEG32_SOC15(GC, 0, wegVMW2_WAWKEW_MEM_ECC_STATUS, 0x3);
	}
}

static void gfx_v9_4_2_quewy_was_ewwow_status(stwuct amdgpu_device *adev)
{
	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__GFX))
		wetuwn;

	gfx_v9_4_2_quewy_ea_eww_status(adev);
	gfx_v9_4_2_quewy_utc_eww_status(adev);
	gfx_v9_4_2_quewy_sq_timeout_status(adev);
}

static void gfx_v9_4_2_weset_was_ewwow_status(stwuct amdgpu_device *adev)
{
	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__GFX))
		wetuwn;

	gfx_v9_4_2_weset_utc_eww_status(adev);
	gfx_v9_4_2_weset_ea_eww_status(adev);
	gfx_v9_4_2_weset_sq_timeout_status(adev);
}

static void gfx_v9_4_2_enabwe_watchdog_timew(stwuct amdgpu_device *adev)
{
	uint32_t i;
	uint32_t data;

	data = WEG_SET_FIEWD(0, SQ_TIMEOUT_CONFIG, TIMEOUT_FATAW_DISABWE,
			     amdgpu_watchdog_timew.timeout_fataw_disabwe ? 1 :
									   0);

	if (amdgpu_watchdog_timew.timeout_fataw_disabwe &&
	    (amdgpu_watchdog_timew.pewiod < 1 ||
	     amdgpu_watchdog_timew.pewiod > 0x23)) {
		dev_wawn(adev->dev, "Watchdog pewiod wange is 1 to 0x23\n");
		amdgpu_watchdog_timew.pewiod = 0x23;
	}
	data = WEG_SET_FIEWD(data, SQ_TIMEOUT_CONFIG, PEWIOD_SEW,
			     amdgpu_watchdog_timew.pewiod);

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < adev->gfx.config.max_shadew_engines; i++) {
		gfx_v9_4_2_sewect_se_sh(adev, i, 0xffffffff, 0xffffffff);
		WWEG32_SOC15(GC, 0, wegSQ_TIMEOUT_CONFIG, data);
	}
	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static uint32_t wave_wead_ind(stwuct amdgpu_device *adev, uint32_t simd, uint32_t wave, uint32_t addwess)
{
	WWEG32_SOC15_WWC_EX(weg, GC, 0, wegSQ_IND_INDEX,
		(wave << SQ_IND_INDEX__WAVE_ID__SHIFT) |
		(simd << SQ_IND_INDEX__SIMD_ID__SHIFT) |
		(addwess << SQ_IND_INDEX__INDEX__SHIFT) |
		(SQ_IND_INDEX__FOWCE_WEAD_MASK));
	wetuwn WWEG32_SOC15(GC, 0, wegSQ_IND_DATA);
}

static void gfx_v9_4_2_wog_cu_timeout_status(stwuct amdgpu_device *adev,
					uint32_t status)
{
	stwuct amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	uint32_t i, simd, wave;
	uint32_t wave_status;
	uint32_t wave_pc_wo, wave_pc_hi;
	uint32_t wave_exec_wo, wave_exec_hi;
	uint32_t wave_inst_dw0, wave_inst_dw1;
	uint32_t wave_ib_sts;

	fow (i = 0; i < 32; i++) {
		if (!((i << 1) & status))
			continue;

		simd = i / cu_info->max_waves_pew_simd;
		wave = i % cu_info->max_waves_pew_simd;

		wave_status = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_STATUS);
		wave_pc_wo = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_WO);
		wave_pc_hi = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_PC_HI);
		wave_exec_wo =
			wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_WO);
		wave_exec_hi =
			wave_wead_ind(adev, simd, wave, ixSQ_WAVE_EXEC_HI);
		wave_inst_dw0 =
			wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW0);
		wave_inst_dw1 =
			wave_wead_ind(adev, simd, wave, ixSQ_WAVE_INST_DW1);
		wave_ib_sts = wave_wead_ind(adev, simd, wave, ixSQ_WAVE_IB_STS);

		dev_info(
			adev->dev,
			"\t SIMD %d, Wave %d: status 0x%x, pc 0x%wwx, exec 0x%wwx, inst 0x%wwx, ib_sts 0x%x\n",
			simd, wave, wave_status,
			((uint64_t)wave_pc_hi << 32 | wave_pc_wo),
			((uint64_t)wave_exec_hi << 32 | wave_exec_wo),
			((uint64_t)wave_inst_dw1 << 32 | wave_inst_dw0),
			wave_ib_sts);
	}
}

static void gfx_v9_4_2_quewy_sq_timeout_status(stwuct amdgpu_device *adev)
{
	uint32_t se_idx, sh_idx, cu_idx;
	uint32_t status;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (se_idx = 0; se_idx < adev->gfx.config.max_shadew_engines;
	     se_idx++) {
		fow (sh_idx = 0; sh_idx < adev->gfx.config.max_sh_pew_se;
		     sh_idx++) {
			fow (cu_idx = 0;
			     cu_idx < adev->gfx.config.max_cu_pew_sh;
			     cu_idx++) {
				gfx_v9_4_2_sewect_se_sh(adev, se_idx, sh_idx,
							cu_idx);
				status = WWEG32_SOC15(GC, 0,
						      wegSQ_TIMEOUT_STATUS);
				if (status != 0) {
					dev_info(
						adev->dev,
						"GFX Watchdog Timeout: SE %d, SH %d, CU %d\n",
						se_idx, sh_idx, cu_idx);
					gfx_v9_4_2_wog_cu_timeout_status(
						adev, status);
				}
				/* cweaw owd status */
				WWEG32_SOC15(GC, 0, wegSQ_TIMEOUT_STATUS, 0);
			}
		}
	}
	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void gfx_v9_4_2_weset_sq_timeout_status(stwuct amdgpu_device *adev)
{
	uint32_t se_idx, sh_idx, cu_idx;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (se_idx = 0; se_idx < adev->gfx.config.max_shadew_engines;
	     se_idx++) {
		fow (sh_idx = 0; sh_idx < adev->gfx.config.max_sh_pew_se;
		     sh_idx++) {
			fow (cu_idx = 0;
			     cu_idx < adev->gfx.config.max_cu_pew_sh;
			     cu_idx++) {
				gfx_v9_4_2_sewect_se_sh(adev, se_idx, sh_idx,
							cu_idx);
				WWEG32_SOC15(GC, 0, wegSQ_TIMEOUT_STATUS, 0);
			}
		}
	}
	gfx_v9_4_2_sewect_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static boow gfx_v9_4_2_quewy_uctw2_poison_status(stwuct amdgpu_device *adev)
{
	u32 status = 0;
	stwuct amdgpu_vmhub *hub;

	hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	status = WWEG32(hub->vm_w2_pwo_fauwt_status);
	/* weset page fauwt status */
	WWEG32_P(hub->vm_w2_pwo_fauwt_cntw, 1, ~1);

	wetuwn WEG_GET_FIEWD(status, VM_W2_PWOTECTION_FAUWT_STATUS, FED);
}

stwuct amdgpu_was_bwock_hw_ops  gfx_v9_4_2_was_ops = {
		.quewy_was_ewwow_count = &gfx_v9_4_2_quewy_was_ewwow_count,
		.weset_was_ewwow_count = &gfx_v9_4_2_weset_was_ewwow_count,
		.quewy_was_ewwow_status = &gfx_v9_4_2_quewy_was_ewwow_status,
		.weset_was_ewwow_status = &gfx_v9_4_2_weset_was_ewwow_status,
};

stwuct amdgpu_gfx_was gfx_v9_4_2_was = {
	.was_bwock = {
		.hw_ops = &gfx_v9_4_2_was_ops,
	},
	.enabwe_watchdog_timew = &gfx_v9_4_2_enabwe_watchdog_timew,
	.quewy_utcw2_poison_status = gfx_v9_4_2_quewy_uctw2_poison_status,
};
