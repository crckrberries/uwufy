/*
 * Copywight 2010 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "cayman_bwit_shadews.h"
#incwude "cweawstate_cayman.h"
#incwude "evewgween.h"
#incwude "ni.h"
#incwude "ni_weg.h"
#incwude "nid.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "wadeon_ucode.h"

/*
 * Indiwect wegistews accessow
 */
u32 tn_smc_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	WWEG32(TN_SMC_IND_INDEX_0, (weg));
	w = WWEG32(TN_SMC_IND_DATA_0);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);
	wetuwn w;
}

void tn_smc_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	WWEG32(TN_SMC_IND_INDEX_0, (weg));
	WWEG32(TN_SMC_IND_DATA_0, (v));
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);
}

static const u32 tn_wwc_save_westowe_wegistew_wist[] =
{
	0x98fc,
	0x98f0,
	0x9834,
	0x9838,
	0x9870,
	0x9874,
	0x8a14,
	0x8b24,
	0x8bcc,
	0x8b10,
	0x8c30,
	0x8d00,
	0x8d04,
	0x8c00,
	0x8c04,
	0x8c10,
	0x8c14,
	0x8d8c,
	0x8cf0,
	0x8e38,
	0x9508,
	0x9688,
	0x9608,
	0x960c,
	0x9610,
	0x9614,
	0x88c4,
	0x8978,
	0x88d4,
	0x900c,
	0x9100,
	0x913c,
	0x90e8,
	0x9354,
	0xa008,
	0x98f8,
	0x9148,
	0x914c,
	0x3f94,
	0x98f4,
	0x9b7c,
	0x3f8c,
	0x8950,
	0x8954,
	0x8a18,
	0x8b28,
	0x9144,
	0x3f90,
	0x915c,
	0x9160,
	0x9178,
	0x917c,
	0x9180,
	0x918c,
	0x9190,
	0x9194,
	0x9198,
	0x919c,
	0x91a8,
	0x91ac,
	0x91b0,
	0x91b4,
	0x91b8,
	0x91c4,
	0x91c8,
	0x91cc,
	0x91d0,
	0x91d4,
	0x91e0,
	0x91e4,
	0x91ec,
	0x91f0,
	0x91f4,
	0x9200,
	0x9204,
	0x929c,
	0x8030,
	0x9150,
	0x9a60,
	0x920c,
	0x9210,
	0x9228,
	0x922c,
	0x9244,
	0x9248,
	0x91e8,
	0x9294,
	0x9208,
	0x9224,
	0x9240,
	0x9220,
	0x923c,
	0x9258,
	0x9744,
	0xa200,
	0xa204,
	0xa208,
	0xa20c,
	0x8d58,
	0x9030,
	0x9034,
	0x9038,
	0x903c,
	0x9040,
	0x9654,
	0x897c,
	0xa210,
	0xa214,
	0x9868,
	0xa02c,
	0x9664,
	0x9698,
	0x949c,
	0x8e10,
	0x8e18,
	0x8c50,
	0x8c58,
	0x8c60,
	0x8c68,
	0x89b4,
	0x9830,
	0x802c,
};

/* Fiwmwawe Names */
MODUWE_FIWMWAWE("wadeon/BAWTS_pfp.bin");
MODUWE_FIWMWAWE("wadeon/BAWTS_me.bin");
MODUWE_FIWMWAWE("wadeon/BAWTS_mc.bin");
MODUWE_FIWMWAWE("wadeon/BAWTS_smc.bin");
MODUWE_FIWMWAWE("wadeon/BTC_wwc.bin");
MODUWE_FIWMWAWE("wadeon/TUWKS_pfp.bin");
MODUWE_FIWMWAWE("wadeon/TUWKS_me.bin");
MODUWE_FIWMWAWE("wadeon/TUWKS_mc.bin");
MODUWE_FIWMWAWE("wadeon/TUWKS_smc.bin");
MODUWE_FIWMWAWE("wadeon/CAICOS_pfp.bin");
MODUWE_FIWMWAWE("wadeon/CAICOS_me.bin");
MODUWE_FIWMWAWE("wadeon/CAICOS_mc.bin");
MODUWE_FIWMWAWE("wadeon/CAICOS_smc.bin");
MODUWE_FIWMWAWE("wadeon/CAYMAN_pfp.bin");
MODUWE_FIWMWAWE("wadeon/CAYMAN_me.bin");
MODUWE_FIWMWAWE("wadeon/CAYMAN_mc.bin");
MODUWE_FIWMWAWE("wadeon/CAYMAN_wwc.bin");
MODUWE_FIWMWAWE("wadeon/CAYMAN_smc.bin");
MODUWE_FIWMWAWE("wadeon/AWUBA_pfp.bin");
MODUWE_FIWMWAWE("wadeon/AWUBA_me.bin");
MODUWE_FIWMWAWE("wadeon/AWUBA_wwc.bin");


static const u32 cayman_gowden_wegistews2[] =
{
	0x3e5c, 0xffffffff, 0x00000000,
	0x3e48, 0xffffffff, 0x00000000,
	0x3e4c, 0xffffffff, 0x00000000,
	0x3e64, 0xffffffff, 0x00000000,
	0x3e50, 0xffffffff, 0x00000000,
	0x3e60, 0xffffffff, 0x00000000
};

static const u32 cayman_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x70073777, 0x00011003,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x02011003,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02011003,
	0x98fc, 0xffffffff, 0x76541032,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x42010001,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000000,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000010f, 0x01000100,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88d0, 0xffffffff, 0x0f40df40,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
};

static const u32 dvst_gowden_wegistews2[] =
{
	0x8f8, 0xffffffff, 0,
	0x8fc, 0x00380000, 0,
	0x8f8, 0xffffffff, 1,
	0x8fc, 0x0e000000, 0
};

static const u32 dvst_gowden_wegistews[] =
{
	0x690, 0x3fff3fff, 0x20c00033,
	0x918c, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x9150, 0xffffdfff, 0x6e944040,
	0x917c, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x915c, 0x0fff0fff, 0x00010000,
	0x3f90, 0xffff0001, 0xff000000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9148, 0xffff0001, 0xff000000,
	0x9190, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0x00000fff, 0x00000001,
	0x55e4, 0xff607fff, 0xfc000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0xfffffffe, 0x00000000,
	0xd0c0, 0xff000fff, 0x00000100,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x12010001,
	0x5bb0, 0x000000f0, 0x00000070,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x00030000, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0xa008, 0xffffffff, 0x00010000,
	0x913c, 0xffff03ff, 0x01000100,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0xf700071f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x20ef8, 0x01ff01ff, 0x00000002,
	0x20e98, 0xfffffbff, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x8978, 0x3fffffff, 0x04050140,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
};

static const u32 scwappew_gowden_wegistews[] =
{
	0x690, 0x3fff3fff, 0x20c00033,
	0x918c, 0x0fff0fff, 0x00010006,
	0x918c, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x91a8, 0x0fff0fff, 0x00010006,
	0x9150, 0xffffdfff, 0x6e944040,
	0x9150, 0xffffdfff, 0x6e944040,
	0x917c, 0x0fff0fff, 0x00030002,
	0x917c, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x9198, 0x0fff0fff, 0x00030002,
	0x915c, 0x0fff0fff, 0x00010000,
	0x915c, 0x0fff0fff, 0x00010000,
	0x3f90, 0xffff0001, 0xff000000,
	0x3f90, 0xffff0001, 0xff000000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9178, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9194, 0x0fff0fff, 0x00070000,
	0x9148, 0xffff0001, 0xff000000,
	0x9148, 0xffff0001, 0xff000000,
	0x9190, 0x0fff0fff, 0x00090008,
	0x9190, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x91ac, 0x0fff0fff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0x00000fff, 0x00000001,
	0x929c, 0x00000fff, 0x00000001,
	0x55e4, 0xff607fff, 0xfc000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8a18, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x8b28, 0xff000fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x9144, 0xfffc0fff, 0x00000100,
	0x6ed8, 0x00010101, 0x00010000,
	0x9830, 0xffffffff, 0x00000000,
	0x9830, 0xffffffff, 0x00000000,
	0x9834, 0xf00fffff, 0x00000400,
	0x9834, 0xf00fffff, 0x00000400,
	0x9838, 0xfffffffe, 0x00000000,
	0x9838, 0xfffffffe, 0x00000000,
	0xd0c0, 0xff000fff, 0x00000100,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x73773777, 0x12010001,
	0xd0b8, 0x73773777, 0x12010001,
	0x5bb0, 0x000000f0, 0x00000070,
	0x98f8, 0x73773777, 0x12010001,
	0x98f8, 0x73773777, 0x12010001,
	0x98fc, 0xffffffff, 0x00000010,
	0x98fc, 0xffffffff, 0x00000010,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x9b7c, 0x00ff0000, 0x00fc0000,
	0x8030, 0x00001f0f, 0x0000100a,
	0x8030, 0x00001f0f, 0x0000100a,
	0x2f48, 0x73773777, 0x12010001,
	0x2f48, 0x73773777, 0x12010001,
	0x2408, 0x00030000, 0x000c007f,
	0x8a14, 0xf000003f, 0x00000007,
	0x8a14, 0xf000003f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x4d8, 0x00000fff, 0x00000100,
	0x4d8, 0x00000fff, 0x00000100,
	0xa008, 0xffffffff, 0x00010000,
	0xa008, 0xffffffff, 0x00010000,
	0x913c, 0xffff03ff, 0x01000100,
	0x913c, 0xffff03ff, 0x01000100,
	0x90e8, 0x001fffff, 0x010400c0,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c00, 0x000000ff, 0x00000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c30, 0x0000000f, 0x00040005,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x900c, 0x00ffffff, 0x0017071f,
	0x28350, 0x00000f01, 0x00000000,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0xf700071f, 0x00000002,
	0x9508, 0xf700071f, 0x00000002,
	0x9688, 0x00300000, 0x0017000f,
	0x960c, 0xffffffff, 0x54763210,
	0x960c, 0xffffffff, 0x54763210,
	0x20ef8, 0x01ff01ff, 0x00000002,
	0x20e98, 0xfffffbff, 0x00200000,
	0x2015c, 0xffffffff, 0x00000f40,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x88c4, 0x001f3ae3, 0x00000082,
	0x8978, 0x3fffffff, 0x04050140,
	0x8978, 0x3fffffff, 0x04050140,
	0x88d4, 0x0000001f, 0x00000010,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0x8974, 0xffffffff, 0x00000000
};

static void ni_init_gowden_wegistews(stwuct wadeon_device *wdev)
{
	switch (wdev->famiwy) {
	case CHIP_CAYMAN:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 cayman_gowden_wegistews,
						 (const u32)AWWAY_SIZE(cayman_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 cayman_gowden_wegistews2,
						 (const u32)AWWAY_SIZE(cayman_gowden_wegistews2));
		bweak;
	case CHIP_AWUBA:
		if ((wdev->pdev->device == 0x9900) ||
		    (wdev->pdev->device == 0x9901) ||
		    (wdev->pdev->device == 0x9903) ||
		    (wdev->pdev->device == 0x9904) ||
		    (wdev->pdev->device == 0x9905) ||
		    (wdev->pdev->device == 0x9906) ||
		    (wdev->pdev->device == 0x9907) ||
		    (wdev->pdev->device == 0x9908) ||
		    (wdev->pdev->device == 0x9909) ||
		    (wdev->pdev->device == 0x990A) ||
		    (wdev->pdev->device == 0x990B) ||
		    (wdev->pdev->device == 0x990C) ||
		    (wdev->pdev->device == 0x990D) ||
		    (wdev->pdev->device == 0x990E) ||
		    (wdev->pdev->device == 0x990F) ||
		    (wdev->pdev->device == 0x9910) ||
		    (wdev->pdev->device == 0x9913) ||
		    (wdev->pdev->device == 0x9917) ||
		    (wdev->pdev->device == 0x9918)) {
			wadeon_pwogwam_wegistew_sequence(wdev,
							 dvst_gowden_wegistews,
							 (const u32)AWWAY_SIZE(dvst_gowden_wegistews));
			wadeon_pwogwam_wegistew_sequence(wdev,
							 dvst_gowden_wegistews2,
							 (const u32)AWWAY_SIZE(dvst_gowden_wegistews2));
		} ewse {
			wadeon_pwogwam_wegistew_sequence(wdev,
							 scwappew_gowden_wegistews,
							 (const u32)AWWAY_SIZE(scwappew_gowden_wegistews));
			wadeon_pwogwam_wegistew_sequence(wdev,
							 dvst_gowden_wegistews2,
							 (const u32)AWWAY_SIZE(dvst_gowden_wegistews2));
		}
		bweak;
	defauwt:
		bweak;
	}
}

#define BTC_IO_MC_WEGS_SIZE 29

static const u32 bawts_io_mc_wegs[BTC_IO_MC_WEGS_SIZE][2] = {
	{0x00000077, 0xff010100},
	{0x00000078, 0x00000000},
	{0x00000079, 0x00001434},
	{0x0000007a, 0xcc08ec08},
	{0x0000007b, 0x00040000},
	{0x0000007c, 0x000080c0},
	{0x0000007d, 0x09000000},
	{0x0000007e, 0x00210404},
	{0x00000081, 0x08a8e800},
	{0x00000082, 0x00030444},
	{0x00000083, 0x00000000},
	{0x00000085, 0x00000001},
	{0x00000086, 0x00000002},
	{0x00000087, 0x48490000},
	{0x00000088, 0x20244647},
	{0x00000089, 0x00000005},
	{0x0000008b, 0x66030000},
	{0x0000008c, 0x00006603},
	{0x0000008d, 0x00000100},
	{0x0000008f, 0x00001c0a},
	{0x00000090, 0xff000001},
	{0x00000094, 0x00101101},
	{0x00000095, 0x00000fff},
	{0x00000096, 0x00116fff},
	{0x00000097, 0x60010000},
	{0x00000098, 0x10010000},
	{0x00000099, 0x00006000},
	{0x0000009a, 0x00001000},
	{0x0000009f, 0x00946a00}
};

static const u32 tuwks_io_mc_wegs[BTC_IO_MC_WEGS_SIZE][2] = {
	{0x00000077, 0xff010100},
	{0x00000078, 0x00000000},
	{0x00000079, 0x00001434},
	{0x0000007a, 0xcc08ec08},
	{0x0000007b, 0x00040000},
	{0x0000007c, 0x000080c0},
	{0x0000007d, 0x09000000},
	{0x0000007e, 0x00210404},
	{0x00000081, 0x08a8e800},
	{0x00000082, 0x00030444},
	{0x00000083, 0x00000000},
	{0x00000085, 0x00000001},
	{0x00000086, 0x00000002},
	{0x00000087, 0x48490000},
	{0x00000088, 0x20244647},
	{0x00000089, 0x00000005},
	{0x0000008b, 0x66030000},
	{0x0000008c, 0x00006603},
	{0x0000008d, 0x00000100},
	{0x0000008f, 0x00001c0a},
	{0x00000090, 0xff000001},
	{0x00000094, 0x00101101},
	{0x00000095, 0x00000fff},
	{0x00000096, 0x00116fff},
	{0x00000097, 0x60010000},
	{0x00000098, 0x10010000},
	{0x00000099, 0x00006000},
	{0x0000009a, 0x00001000},
	{0x0000009f, 0x00936a00}
};

static const u32 caicos_io_mc_wegs[BTC_IO_MC_WEGS_SIZE][2] = {
	{0x00000077, 0xff010100},
	{0x00000078, 0x00000000},
	{0x00000079, 0x00001434},
	{0x0000007a, 0xcc08ec08},
	{0x0000007b, 0x00040000},
	{0x0000007c, 0x000080c0},
	{0x0000007d, 0x09000000},
	{0x0000007e, 0x00210404},
	{0x00000081, 0x08a8e800},
	{0x00000082, 0x00030444},
	{0x00000083, 0x00000000},
	{0x00000085, 0x00000001},
	{0x00000086, 0x00000002},
	{0x00000087, 0x48490000},
	{0x00000088, 0x20244647},
	{0x00000089, 0x00000005},
	{0x0000008b, 0x66030000},
	{0x0000008c, 0x00006603},
	{0x0000008d, 0x00000100},
	{0x0000008f, 0x00001c0a},
	{0x00000090, 0xff000001},
	{0x00000094, 0x00101101},
	{0x00000095, 0x00000fff},
	{0x00000096, 0x00116fff},
	{0x00000097, 0x60010000},
	{0x00000098, 0x10010000},
	{0x00000099, 0x00006000},
	{0x0000009a, 0x00001000},
	{0x0000009f, 0x00916a00}
};

static const u32 cayman_io_mc_wegs[BTC_IO_MC_WEGS_SIZE][2] = {
	{0x00000077, 0xff010100},
	{0x00000078, 0x00000000},
	{0x00000079, 0x00001434},
	{0x0000007a, 0xcc08ec08},
	{0x0000007b, 0x00040000},
	{0x0000007c, 0x000080c0},
	{0x0000007d, 0x09000000},
	{0x0000007e, 0x00210404},
	{0x00000081, 0x08a8e800},
	{0x00000082, 0x00030444},
	{0x00000083, 0x00000000},
	{0x00000085, 0x00000001},
	{0x00000086, 0x00000002},
	{0x00000087, 0x48490000},
	{0x00000088, 0x20244647},
	{0x00000089, 0x00000005},
	{0x0000008b, 0x66030000},
	{0x0000008c, 0x00006603},
	{0x0000008d, 0x00000100},
	{0x0000008f, 0x00001c0a},
	{0x00000090, 0xff000001},
	{0x00000094, 0x00101101},
	{0x00000095, 0x00000fff},
	{0x00000096, 0x00116fff},
	{0x00000097, 0x60010000},
	{0x00000098, 0x10010000},
	{0x00000099, 0x00006000},
	{0x0000009a, 0x00001000},
	{0x0000009f, 0x00976b00}
};

int ni_mc_woad_micwocode(stwuct wadeon_device *wdev)
{
	const __be32 *fw_data;
	u32 mem_type, wunning, bwackout = 0;
	u32 *io_mc_wegs;
	int i, ucode_size, wegs_size;

	if (!wdev->mc_fw)
		wetuwn -EINVAW;

	switch (wdev->famiwy) {
	case CHIP_BAWTS:
		io_mc_wegs = (u32 *)&bawts_io_mc_wegs;
		ucode_size = BTC_MC_UCODE_SIZE;
		wegs_size = BTC_IO_MC_WEGS_SIZE;
		bweak;
	case CHIP_TUWKS:
		io_mc_wegs = (u32 *)&tuwks_io_mc_wegs;
		ucode_size = BTC_MC_UCODE_SIZE;
		wegs_size = BTC_IO_MC_WEGS_SIZE;
		bweak;
	case CHIP_CAICOS:
	defauwt:
		io_mc_wegs = (u32 *)&caicos_io_mc_wegs;
		ucode_size = BTC_MC_UCODE_SIZE;
		wegs_size = BTC_IO_MC_WEGS_SIZE;
		bweak;
	case CHIP_CAYMAN:
		io_mc_wegs = (u32 *)&cayman_io_mc_wegs;
		ucode_size = CAYMAN_MC_UCODE_SIZE;
		wegs_size = BTC_IO_MC_WEGS_SIZE;
		bweak;
	}

	mem_type = (WWEG32(MC_SEQ_MISC0) & MC_SEQ_MISC0_GDDW5_MASK) >> MC_SEQ_MISC0_GDDW5_SHIFT;
	wunning = WWEG32(MC_SEQ_SUP_CNTW) & WUN_MASK;

	if ((mem_type == MC_SEQ_MISC0_GDDW5_VAWUE) && (wunning == 0)) {
		if (wunning) {
			bwackout = WWEG32(MC_SHAWED_BWACKOUT_CNTW);
			WWEG32(MC_SHAWED_BWACKOUT_CNTW, 1);
		}

		/* weset the engine and set to wwitabwe */
		WWEG32(MC_SEQ_SUP_CNTW, 0x00000008);
		WWEG32(MC_SEQ_SUP_CNTW, 0x00000010);

		/* woad mc io wegs */
		fow (i = 0; i < wegs_size; i++) {
			WWEG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_wegs[(i << 1)]);
			WWEG32(MC_SEQ_IO_DEBUG_DATA, io_mc_wegs[(i << 1) + 1]);
		}
		/* woad the MC ucode */
		fw_data = (const __be32 *)wdev->mc_fw->data;
		fow (i = 0; i < ucode_size; i++)
			WWEG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));

		/* put the engine back into the active state */
		WWEG32(MC_SEQ_SUP_CNTW, 0x00000008);
		WWEG32(MC_SEQ_SUP_CNTW, 0x00000004);
		WWEG32(MC_SEQ_SUP_CNTW, 0x00000001);

		/* wait fow twaining to compwete */
		fow (i = 0; i < wdev->usec_timeout; i++) {
			if (WWEG32(MC_IO_PAD_CNTW_D0) & MEM_FAWW_OUT_CMD)
				bweak;
			udeway(1);
		}

		if (wunning)
			WWEG32(MC_SHAWED_BWACKOUT_CNTW, bwackout);
	}

	wetuwn 0;
}

int ni_init_micwocode(stwuct wadeon_device *wdev)
{
	const chaw *chip_name;
	const chaw *wwc_chip_name;
	size_t pfp_weq_size, me_weq_size, wwc_weq_size, mc_weq_size;
	size_t smc_weq_size = 0;
	chaw fw_name[30];
	int eww;

	DWM_DEBUG("\n");

	switch (wdev->famiwy) {
	case CHIP_BAWTS:
		chip_name = "BAWTS";
		wwc_chip_name = "BTC";
		pfp_weq_size = EVEWGWEEN_PFP_UCODE_SIZE * 4;
		me_weq_size = EVEWGWEEN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = EVEWGWEEN_WWC_UCODE_SIZE * 4;
		mc_weq_size = BTC_MC_UCODE_SIZE * 4;
		smc_weq_size = AWIGN(BAWTS_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_TUWKS:
		chip_name = "TUWKS";
		wwc_chip_name = "BTC";
		pfp_weq_size = EVEWGWEEN_PFP_UCODE_SIZE * 4;
		me_weq_size = EVEWGWEEN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = EVEWGWEEN_WWC_UCODE_SIZE * 4;
		mc_weq_size = BTC_MC_UCODE_SIZE * 4;
		smc_weq_size = AWIGN(TUWKS_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_CAICOS:
		chip_name = "CAICOS";
		wwc_chip_name = "BTC";
		pfp_weq_size = EVEWGWEEN_PFP_UCODE_SIZE * 4;
		me_weq_size = EVEWGWEEN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = EVEWGWEEN_WWC_UCODE_SIZE * 4;
		mc_weq_size = BTC_MC_UCODE_SIZE * 4;
		smc_weq_size = AWIGN(CAICOS_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_CAYMAN:
		chip_name = "CAYMAN";
		wwc_chip_name = "CAYMAN";
		pfp_weq_size = CAYMAN_PFP_UCODE_SIZE * 4;
		me_weq_size = CAYMAN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = CAYMAN_WWC_UCODE_SIZE * 4;
		mc_weq_size = CAYMAN_MC_UCODE_SIZE * 4;
		smc_weq_size = AWIGN(CAYMAN_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_AWUBA:
		chip_name = "AWUBA";
		wwc_chip_name = "AWUBA";
		/* pfp/me same size as CAYMAN */
		pfp_weq_size = CAYMAN_PFP_UCODE_SIZE * 4;
		me_weq_size = CAYMAN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = AWUBA_WWC_UCODE_SIZE * 4;
		mc_weq_size = 0;
		bweak;
	defauwt: BUG();
	}

	DWM_INFO("Woading %s Micwocode\n", chip_name);

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_pfp.bin", chip_name);
	eww = wequest_fiwmwawe(&wdev->pfp_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->pfp_fw->size != pfp_weq_size) {
		pw_eww("ni_cp: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->pfp_fw->size, fw_name);
		eww = -EINVAW;
		goto out;
	}

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_me.bin", chip_name);
	eww = wequest_fiwmwawe(&wdev->me_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->me_fw->size != me_weq_size) {
		pw_eww("ni_cp: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->me_fw->size, fw_name);
		eww = -EINVAW;
	}

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_wwc.bin", wwc_chip_name);
	eww = wequest_fiwmwawe(&wdev->wwc_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->wwc_fw->size != wwc_weq_size) {
		pw_eww("ni_wwc: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->wwc_fw->size, fw_name);
		eww = -EINVAW;
	}

	/* no MC ucode on TN */
	if (!(wdev->fwags & WADEON_IS_IGP)) {
		snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_mc.bin", chip_name);
		eww = wequest_fiwmwawe(&wdev->mc_fw, fw_name, wdev->dev);
		if (eww)
			goto out;
		if (wdev->mc_fw->size != mc_weq_size) {
			pw_eww("ni_mc: Bogus wength %zu in fiwmwawe \"%s\"\n",
			       wdev->mc_fw->size, fw_name);
			eww = -EINVAW;
		}
	}

	if ((wdev->famiwy >= CHIP_BAWTS) && (wdev->famiwy <= CHIP_CAYMAN)) {
		snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_smc.bin", chip_name);
		eww = wequest_fiwmwawe(&wdev->smc_fw, fw_name, wdev->dev);
		if (eww) {
			pw_eww("smc: ewwow woading fiwmwawe \"%s\"\n", fw_name);
			wewease_fiwmwawe(wdev->smc_fw);
			wdev->smc_fw = NUWW;
			eww = 0;
		} ewse if (wdev->smc_fw->size != smc_weq_size) {
			pw_eww("ni_mc: Bogus wength %zu in fiwmwawe \"%s\"\n",
			       wdev->mc_fw->size, fw_name);
			eww = -EINVAW;
		}
	}

out:
	if (eww) {
		if (eww != -EINVAW)
			pw_eww("ni_cp: Faiwed to woad fiwmwawe \"%s\"\n",
			       fw_name);
		wewease_fiwmwawe(wdev->pfp_fw);
		wdev->pfp_fw = NUWW;
		wewease_fiwmwawe(wdev->me_fw);
		wdev->me_fw = NUWW;
		wewease_fiwmwawe(wdev->wwc_fw);
		wdev->wwc_fw = NUWW;
		wewease_fiwmwawe(wdev->mc_fw);
		wdev->mc_fw = NUWW;
	}
	wetuwn eww;
}

/**
 * cayman_get_awwowed_info_wegistew - fetch the wegistew fow the info ioctw
 *
 * @wdev: wadeon_device pointew
 * @weg: wegistew offset in bytes
 * @vaw: wegistew vawue
 *
 * Wetuwns 0 fow success ow -EINVAW fow an invawid wegistew
 *
 */
int cayman_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				     u32 weg, u32 *vaw)
{
	switch (weg) {
	case GWBM_STATUS:
	case GWBM_STATUS_SE0:
	case GWBM_STATUS_SE1:
	case SWBM_STATUS:
	case SWBM_STATUS2:
	case (DMA_STATUS_WEG + DMA0_WEGISTEW_OFFSET):
	case (DMA_STATUS_WEG + DMA1_WEGISTEW_OFFSET):
	case UVD_STATUS:
		*vaw = WWEG32(weg);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int tn_get_temp(stwuct wadeon_device *wdev)
{
	u32 temp = WWEG32_SMC(TN_CUWWENT_GNB_TEMP) & 0x7ff;
	int actuaw_temp = (temp / 8) - 49;

	wetuwn actuaw_temp * 1000;
}

/*
 * Cowe functions
 */
static void cayman_gpu_init(stwuct wadeon_device *wdev)
{
	u32 gb_addw_config = 0;
	u32 mc_awb_wamcfg;
	u32 cgts_tcc_disabwe;
	u32 sx_debug_1;
	u32 smx_dc_ctw0;
	u32 cgts_sm_ctww_weg;
	u32 hdp_host_path_cntw;
	u32 tmp;
	u32 disabwed_wb_mask;
	int i, j;

	switch (wdev->famiwy) {
	case CHIP_CAYMAN:
		wdev->config.cayman.max_shadew_engines = 2;
		wdev->config.cayman.max_pipes_pew_simd = 4;
		wdev->config.cayman.max_tiwe_pipes = 8;
		wdev->config.cayman.max_simds_pew_se = 12;
		wdev->config.cayman.max_backends_pew_se = 4;
		wdev->config.cayman.max_textuwe_channew_caches = 8;
		wdev->config.cayman.max_gpws = 256;
		wdev->config.cayman.max_thweads = 256;
		wdev->config.cayman.max_gs_thweads = 32;
		wdev->config.cayman.max_stack_entwies = 512;
		wdev->config.cayman.sx_num_of_sets = 8;
		wdev->config.cayman.sx_max_expowt_size = 256;
		wdev->config.cayman.sx_max_expowt_pos_size = 64;
		wdev->config.cayman.sx_max_expowt_smx_size = 192;
		wdev->config.cayman.max_hw_contexts = 8;
		wdev->config.cayman.sq_num_cf_insts = 2;

		wdev->config.cayman.sc_pwim_fifo_size = 0x100;
		wdev->config.cayman.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.cayman.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CAYMAN_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_AWUBA:
	defauwt:
		wdev->config.cayman.max_shadew_engines = 1;
		wdev->config.cayman.max_pipes_pew_simd = 4;
		wdev->config.cayman.max_tiwe_pipes = 2;
		if ((wdev->pdev->device == 0x9900) ||
		    (wdev->pdev->device == 0x9901) ||
		    (wdev->pdev->device == 0x9905) ||
		    (wdev->pdev->device == 0x9906) ||
		    (wdev->pdev->device == 0x9907) ||
		    (wdev->pdev->device == 0x9908) ||
		    (wdev->pdev->device == 0x9909) ||
		    (wdev->pdev->device == 0x990B) ||
		    (wdev->pdev->device == 0x990C) ||
		    (wdev->pdev->device == 0x990F) ||
		    (wdev->pdev->device == 0x9910) ||
		    (wdev->pdev->device == 0x9917) ||
		    (wdev->pdev->device == 0x9999) ||
		    (wdev->pdev->device == 0x999C)) {
			wdev->config.cayman.max_simds_pew_se = 6;
			wdev->config.cayman.max_backends_pew_se = 2;
			wdev->config.cayman.max_hw_contexts = 8;
			wdev->config.cayman.sx_max_expowt_size = 256;
			wdev->config.cayman.sx_max_expowt_pos_size = 64;
			wdev->config.cayman.sx_max_expowt_smx_size = 192;
		} ewse if ((wdev->pdev->device == 0x9903) ||
			   (wdev->pdev->device == 0x9904) ||
			   (wdev->pdev->device == 0x990A) ||
			   (wdev->pdev->device == 0x990D) ||
			   (wdev->pdev->device == 0x990E) ||
			   (wdev->pdev->device == 0x9913) ||
			   (wdev->pdev->device == 0x9918) ||
			   (wdev->pdev->device == 0x999D)) {
			wdev->config.cayman.max_simds_pew_se = 4;
			wdev->config.cayman.max_backends_pew_se = 2;
			wdev->config.cayman.max_hw_contexts = 8;
			wdev->config.cayman.sx_max_expowt_size = 256;
			wdev->config.cayman.sx_max_expowt_pos_size = 64;
			wdev->config.cayman.sx_max_expowt_smx_size = 192;
		} ewse if ((wdev->pdev->device == 0x9919) ||
			   (wdev->pdev->device == 0x9990) ||
			   (wdev->pdev->device == 0x9991) ||
			   (wdev->pdev->device == 0x9994) ||
			   (wdev->pdev->device == 0x9995) ||
			   (wdev->pdev->device == 0x9996) ||
			   (wdev->pdev->device == 0x999A) ||
			   (wdev->pdev->device == 0x99A0)) {
			wdev->config.cayman.max_simds_pew_se = 3;
			wdev->config.cayman.max_backends_pew_se = 1;
			wdev->config.cayman.max_hw_contexts = 4;
			wdev->config.cayman.sx_max_expowt_size = 128;
			wdev->config.cayman.sx_max_expowt_pos_size = 32;
			wdev->config.cayman.sx_max_expowt_smx_size = 96;
		} ewse {
			wdev->config.cayman.max_simds_pew_se = 2;
			wdev->config.cayman.max_backends_pew_se = 1;
			wdev->config.cayman.max_hw_contexts = 4;
			wdev->config.cayman.sx_max_expowt_size = 128;
			wdev->config.cayman.sx_max_expowt_pos_size = 32;
			wdev->config.cayman.sx_max_expowt_smx_size = 96;
		}
		wdev->config.cayman.max_textuwe_channew_caches = 2;
		wdev->config.cayman.max_gpws = 256;
		wdev->config.cayman.max_thweads = 256;
		wdev->config.cayman.max_gs_thweads = 32;
		wdev->config.cayman.max_stack_entwies = 512;
		wdev->config.cayman.sx_num_of_sets = 8;
		wdev->config.cayman.sq_num_cf_insts = 2;

		wdev->config.cayman.sc_pwim_fifo_size = 0x40;
		wdev->config.cayman.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.cayman.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = AWUBA_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	}

	/* Initiawize HDP */
	fow (i = 0, j = 0; i < 32; i++, j += 0x18) {
		WWEG32((0x2c14 + j), 0x00000000);
		WWEG32((0x2c18 + j), 0x00000000);
		WWEG32((0x2c1c + j), 0x00000000);
		WWEG32((0x2c20 + j), 0x00000000);
		WWEG32((0x2c24 + j), 0x00000000);
	}

	WWEG32(GWBM_CNTW, GWBM_WEAD_TIMEOUT(0xff));
	WWEG32(SWBM_INT_CNTW, 0x1);
	WWEG32(SWBM_INT_ACK, 0x1);

	evewgween_fix_pci_max_wead_weq_size(wdev);

	WWEG32(MC_SHAWED_CHMAP);
	mc_awb_wamcfg = WWEG32(MC_AWB_WAMCFG);

	tmp = (mc_awb_wamcfg & NOOFCOWS_MASK) >> NOOFCOWS_SHIFT;
	wdev->config.cayman.mem_wow_size_in_kb = (4 * (1 << (8 + tmp))) / 1024;
	if (wdev->config.cayman.mem_wow_size_in_kb > 4)
		wdev->config.cayman.mem_wow_size_in_kb = 4;
	/* XXX use MC settings? */
	wdev->config.cayman.shadew_engine_tiwe_size = 32;
	wdev->config.cayman.num_gpus = 1;
	wdev->config.cayman.muwti_gpu_tiwe_size = 64;

	tmp = (gb_addw_config & NUM_PIPES_MASK) >> NUM_PIPES_SHIFT;
	wdev->config.cayman.num_tiwe_pipes = (1 << tmp);
	tmp = (gb_addw_config & PIPE_INTEWWEAVE_SIZE_MASK) >> PIPE_INTEWWEAVE_SIZE_SHIFT;
	wdev->config.cayman.mem_max_buwst_wength_bytes = (tmp + 1) * 256;
	tmp = (gb_addw_config & NUM_SHADEW_ENGINES_MASK) >> NUM_SHADEW_ENGINES_SHIFT;
	wdev->config.cayman.num_shadew_engines = tmp + 1;
	tmp = (gb_addw_config & NUM_GPUS_MASK) >> NUM_GPUS_SHIFT;
	wdev->config.cayman.num_gpus = tmp + 1;
	tmp = (gb_addw_config & MUWTI_GPU_TIWE_SIZE_MASK) >> MUWTI_GPU_TIWE_SIZE_SHIFT;
	wdev->config.cayman.muwti_gpu_tiwe_size = 1 << tmp;
	tmp = (gb_addw_config & WOW_SIZE_MASK) >> WOW_SIZE_SHIFT;
	wdev->config.cayman.mem_wow_size_in_kb = 1 << tmp;


	/* setup tiwing info dwowd.  gb_addw_config is not adequate since it does
	 * not have bank info, so cweate a custom tiwing dwowd.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  gwoup_size
	 * bits 15:12 wow_size
	 */
	wdev->config.cayman.tiwe_config = 0;
	switch (wdev->config.cayman.num_tiwe_pipes) {
	case 1:
	defauwt:
		wdev->config.cayman.tiwe_config |= (0 << 0);
		bweak;
	case 2:
		wdev->config.cayman.tiwe_config |= (1 << 0);
		bweak;
	case 4:
		wdev->config.cayman.tiwe_config |= (2 << 0);
		bweak;
	case 8:
		wdev->config.cayman.tiwe_config |= (3 << 0);
		bweak;
	}

	/* num banks is 8 on aww fusion asics. 0 = 4, 1 = 8, 2 = 16 */
	if (wdev->fwags & WADEON_IS_IGP)
		wdev->config.cayman.tiwe_config |= 1 << 4;
	ewse {
		switch ((mc_awb_wamcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) {
		case 0: /* fouw banks */
			wdev->config.cayman.tiwe_config |= 0 << 4;
			bweak;
		case 1: /* eight banks */
			wdev->config.cayman.tiwe_config |= 1 << 4;
			bweak;
		case 2: /* sixteen banks */
		defauwt:
			wdev->config.cayman.tiwe_config |= 2 << 4;
			bweak;
		}
	}
	wdev->config.cayman.tiwe_config |=
		((gb_addw_config & PIPE_INTEWWEAVE_SIZE_MASK) >> PIPE_INTEWWEAVE_SIZE_SHIFT) << 8;
	wdev->config.cayman.tiwe_config |=
		((gb_addw_config & WOW_SIZE_MASK) >> WOW_SIZE_SHIFT) << 12;

	tmp = 0;
	fow (i = (wdev->config.cayman.max_shadew_engines - 1); i >= 0; i--) {
		u32 wb_disabwe_bitmap;

		WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		wb_disabwe_bitmap = (WWEG32(CC_WB_BACKEND_DISABWE) & 0x00ff0000) >> 16;
		tmp <<= 4;
		tmp |= wb_disabwe_bitmap;
	}
	/* enabwed wb awe just the one not disabwed :) */
	disabwed_wb_mask = tmp;
	tmp = 0;
	fow (i = 0; i < (wdev->config.cayman.max_backends_pew_se * wdev->config.cayman.max_shadew_engines); i++)
		tmp |= (1 << i);
	/* if aww the backends awe disabwed, fix it up hewe */
	if ((disabwed_wb_mask & tmp) == tmp) {
		fow (i = 0; i < (wdev->config.cayman.max_backends_pew_se * wdev->config.cayman.max_shadew_engines); i++)
			disabwed_wb_mask &= ~(1 << i);
	}

	fow (i = 0; i < wdev->config.cayman.max_shadew_engines; i++) {
		u32 simd_disabwe_bitmap;

		WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		simd_disabwe_bitmap = (WWEG32(CC_GC_SHADEW_PIPE_CONFIG) & 0xffff0000) >> 16;
		simd_disabwe_bitmap |= 0xffffffff << wdev->config.cayman.max_simds_pew_se;
		tmp <<= 16;
		tmp |= simd_disabwe_bitmap;
	}
	wdev->config.cayman.active_simds = hweight32(~tmp);

	WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_BWOADCAST_WWITES);
	WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_BWOADCAST_WWITES);

	WWEG32(GB_ADDW_CONFIG, gb_addw_config);
	WWEG32(DMIF_ADDW_CONFIG, gb_addw_config);
	if (ASIC_IS_DCE6(wdev))
		WWEG32(DMIF_ADDW_CAWC, gb_addw_config);
	WWEG32(HDP_ADDW_CONFIG, gb_addw_config);
	WWEG32(DMA_TIWING_CONFIG + DMA0_WEGISTEW_OFFSET, gb_addw_config);
	WWEG32(DMA_TIWING_CONFIG + DMA1_WEGISTEW_OFFSET, gb_addw_config);
	WWEG32(UVD_UDEC_ADDW_CONFIG, gb_addw_config);
	WWEG32(UVD_UDEC_DB_ADDW_CONFIG, gb_addw_config);
	WWEG32(UVD_UDEC_DBW_ADDW_CONFIG, gb_addw_config);

	if ((wdev->config.cayman.max_backends_pew_se == 1) &&
	    (wdev->fwags & WADEON_IS_IGP)) {
		if ((disabwed_wb_mask & 3) == 2) {
			/* WB1 disabwed, WB0 enabwed */
			tmp = 0x00000000;
		} ewse {
			/* WB0 disabwed, WB1 enabwed */
			tmp = 0x11111111;
		}
	} ewse {
		tmp = gb_addw_config & NUM_PIPES_MASK;
		tmp = w6xx_wemap_wendew_backend(wdev, tmp,
						wdev->config.cayman.max_backends_pew_se *
						wdev->config.cayman.max_shadew_engines,
						CAYMAN_MAX_BACKENDS, disabwed_wb_mask);
	}
	wdev->config.cayman.backend_map = tmp;
	WWEG32(GB_BACKEND_MAP, tmp);

	cgts_tcc_disabwe = 0xffff0000;
	fow (i = 0; i < wdev->config.cayman.max_textuwe_channew_caches; i++)
		cgts_tcc_disabwe &= ~(1 << (16 + i));
	WWEG32(CGTS_TCC_DISABWE, cgts_tcc_disabwe);
	WWEG32(CGTS_SYS_TCC_DISABWE, cgts_tcc_disabwe);
	WWEG32(CGTS_USEW_SYS_TCC_DISABWE, cgts_tcc_disabwe);
	WWEG32(CGTS_USEW_TCC_DISABWE, cgts_tcc_disabwe);

	/* wepwogwam the shadew compwex */
	cgts_sm_ctww_weg = WWEG32(CGTS_SM_CTWW_WEG);
	fow (i = 0; i < 16; i++)
		WWEG32(CGTS_SM_CTWW_WEG, OVEWWIDE);
	WWEG32(CGTS_SM_CTWW_WEG, cgts_sm_ctww_weg);

	/* set HW defauwts fow 3D engine */
	WWEG32(CP_MEQ_THWESHOWDS, MEQ1_STAWT(0x30) | MEQ2_STAWT(0x60));

	sx_debug_1 = WWEG32(SX_DEBUG_1);
	sx_debug_1 |= ENABWE_NEW_SMX_ADDWESS;
	WWEG32(SX_DEBUG_1, sx_debug_1);

	smx_dc_ctw0 = WWEG32(SMX_DC_CTW0);
	smx_dc_ctw0 &= ~NUMBEW_OF_SETS(0x1ff);
	smx_dc_ctw0 |= NUMBEW_OF_SETS(wdev->config.cayman.sx_num_of_sets);
	WWEG32(SMX_DC_CTW0, smx_dc_ctw0);

	WWEG32(SPI_CONFIG_CNTW_1, VTX_DONE_DEWAY(4) | CWC_SIMD_ID_WADDW_DISABWE);

	/* need to be expwicitwy zewo-ed */
	WWEG32(VGT_OFFCHIP_WDS_BASE, 0);
	WWEG32(SQ_WSTMP_WING_BASE, 0);
	WWEG32(SQ_HSTMP_WING_BASE, 0);
	WWEG32(SQ_ESTMP_WING_BASE, 0);
	WWEG32(SQ_GSTMP_WING_BASE, 0);
	WWEG32(SQ_VSTMP_WING_BASE, 0);
	WWEG32(SQ_PSTMP_WING_BASE, 0);

	WWEG32(TA_CNTW_AUX, DISABWE_CUBE_ANISO);

	WWEG32(SX_EXPOWT_BUFFEW_SIZES, (COWOW_BUFFEW_SIZE((wdev->config.cayman.sx_max_expowt_size / 4) - 1) |
					POSITION_BUFFEW_SIZE((wdev->config.cayman.sx_max_expowt_pos_size / 4) - 1) |
					SMX_BUFFEW_SIZE((wdev->config.cayman.sx_max_expowt_smx_size / 4) - 1)));

	WWEG32(PA_SC_FIFO_SIZE, (SC_PWIM_FIFO_SIZE(wdev->config.cayman.sc_pwim_fifo_size) |
				 SC_HIZ_TIWE_FIFO_SIZE(wdev->config.cayman.sc_hiz_tiwe_fifo_size) |
				 SC_EAWWYZ_TIWE_FIFO_SIZE(wdev->config.cayman.sc_eawwyz_tiwe_fifo_size)));


	WWEG32(VGT_NUM_INSTANCES, 1);

	WWEG32(CP_PEWFMON_CNTW, 0);

	WWEG32(SQ_MS_FIFO_SIZES, (CACHE_FIFO_SIZE(16 * wdev->config.cayman.sq_num_cf_insts) |
				  FETCH_FIFO_HIWATEW(0x4) |
				  DONE_FIFO_HIWATEW(0xe0) |
				  AWU_UPDATE_FIFO_HIWATEW(0x8)));

	WWEG32(SQ_GPW_WESOUWCE_MGMT_1, NUM_CWAUSE_TEMP_GPWS(4));
	WWEG32(SQ_CONFIG, (VC_ENABWE |
			   EXPOWT_SWC_C |
			   GFX_PWIO(0) |
			   CS1_PWIO(0) |
			   CS2_PWIO(1)));
	WWEG32(SQ_DYN_GPW_CNTW_PS_FWUSH_WEQ, DYN_GPW_ENABWE);

	WWEG32(PA_SC_FOWCE_EOV_MAX_CNTS, (FOWCE_EOV_MAX_CWK_CNT(4095) |
					  FOWCE_EOV_MAX_WEZ_CNT(255)));

	WWEG32(VGT_CACHE_INVAWIDATION, CACHE_INVAWIDATION(VC_AND_TC) |
	       AUTO_INVWD_EN(ES_AND_GS_AUTO));

	WWEG32(VGT_GS_VEWTEX_WEUSE, 16);
	WWEG32(PA_SC_WINE_STIPPWE_STATE, 0);

	WWEG32(CB_PEWF_CTW0_SEW_0, 0);
	WWEG32(CB_PEWF_CTW0_SEW_1, 0);
	WWEG32(CB_PEWF_CTW1_SEW_0, 0);
	WWEG32(CB_PEWF_CTW1_SEW_1, 0);
	WWEG32(CB_PEWF_CTW2_SEW_0, 0);
	WWEG32(CB_PEWF_CTW2_SEW_1, 0);
	WWEG32(CB_PEWF_CTW3_SEW_0, 0);
	WWEG32(CB_PEWF_CTW3_SEW_1, 0);

	tmp = WWEG32(HDP_MISC_CNTW);
	tmp |= HDP_FWUSH_INVAWIDATE_CACHE;
	WWEG32(HDP_MISC_CNTW, tmp);

	hdp_host_path_cntw = WWEG32(HDP_HOST_PATH_CNTW);
	WWEG32(HDP_HOST_PATH_CNTW, hdp_host_path_cntw);

	WWEG32(PA_CW_ENHANCE, CWIP_VTX_WEOWDEW_ENA | NUM_CWIP_SEQ(3));

	udeway(50);

	/* set cwockgating gowden vawues on TN */
	if (wdev->famiwy == CHIP_AWUBA) {
		tmp = WWEG32_CG(CG_CGTT_WOCAW_0);
		tmp &= ~0x00380000;
		WWEG32_CG(CG_CGTT_WOCAW_0, tmp);
		tmp = WWEG32_CG(CG_CGTT_WOCAW_1);
		tmp &= ~0x0e000000;
		WWEG32_CG(CG_CGTT_WOCAW_1, tmp);
	}
}

/*
 * GAWT
 */
void cayman_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev)
{
	/* fwush hdp cache */
	WWEG32(HDP_MEM_COHEWENCY_FWUSH_CNTW, 0x1);

	/* bits 0-7 awe the VM contexts0-7 */
	WWEG32(VM_INVAWIDATE_WEQUEST, 1);
}

static int cayman_pcie_gawt_enabwe(stwuct wadeon_device *wdev)
{
	int i, w;

	if (wdev->gawt.wobj == NUWW) {
		dev_eww(wdev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	w = wadeon_gawt_tabwe_vwam_pin(wdev);
	if (w)
		wetuwn w;
	/* Setup TWB contwow */
	WWEG32(MC_VM_MX_W1_TWB_CNTW,
	       (0xA << 7) |
	       ENABWE_W1_TWB |
	       ENABWE_W1_FWAGMENT_PWOCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       ENABWE_ADVANCED_DWIVEW_MODEW |
	       SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU);
	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_CACHE |
	       ENABWE_W2_FWAGMENT_PWOCESSING |
	       ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
	       ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE |
	       EFFECTIVE_W2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WWEG32(VM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS | INVAWIDATE_W2_CACHE);
	WWEG32(VM_W2_CNTW3, W2_CACHE_BIGK_ASSOCIATIVITY |
	       BANK_SEWECT(6) |
	       W2_CACHE_BIGK_FWAGMENT_SIZE(6));
	/* setup context0 */
	WWEG32(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW, wdev->mc.gtt_stawt >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_END_ADDW, wdev->mc.gtt_end >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW, wdev->gawt.tabwe_addw >> 12);
	WWEG32(VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW,
			(u32)(wdev->dummy_page.addw >> 12));
	WWEG32(VM_CONTEXT0_CNTW2, 0);
	WWEG32(VM_CONTEXT0_CNTW, ENABWE_CONTEXT | PAGE_TABWE_DEPTH(0) |
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT);

	WWEG32(0x15D4, 0);
	WWEG32(0x15D8, 0);
	WWEG32(0x15DC, 0);

	/* empty context1-7 */
	/* Assign the pt base to something vawid fow now; the pts used fow
	 * the VMs awe detewmined by the appwication and setup and assigned
	 * on the fwy in the vm pawt of wadeon_gawt.c
	 */
	fow (i = 1; i < 8; i++) {
		WWEG32(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW + (i << 2), 0);
		WWEG32(VM_CONTEXT0_PAGE_TABWE_END_ADDW + (i << 2),
			wdev->vm_managew.max_pfn - 1);
		WWEG32(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (i << 2),
		       wdev->vm_managew.saved_tabwe_addw[i]);
	}

	/* enabwe context1-7 */
	WWEG32(VM_CONTEXT1_PWOTECTION_FAUWT_DEFAUWT_ADDW,
	       (u32)(wdev->dummy_page.addw >> 12));
	WWEG32(VM_CONTEXT1_CNTW2, 4);
	WWEG32(VM_CONTEXT1_CNTW, ENABWE_CONTEXT | PAGE_TABWE_DEPTH(1) |
				PAGE_TABWE_BWOCK_SIZE(wadeon_vm_bwock_size - 9) |
				WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT |
				DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT |
				PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT |
				VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT |
				WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT |
				WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT |
				WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT);

	cayman_pcie_gawt_twb_fwush(wdev);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned)(wdev->mc.gtt_size >> 20),
		 (unsigned wong wong)wdev->gawt.tabwe_addw);
	wdev->gawt.weady = twue;
	wetuwn 0;
}

static void cayman_pcie_gawt_disabwe(stwuct wadeon_device *wdev)
{
	unsigned i;

	fow (i = 1; i < 8; ++i) {
		wdev->vm_managew.saved_tabwe_addw[i] = WWEG32(
			VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (i << 2));
	}

	/* Disabwe aww tabwes */
	WWEG32(VM_CONTEXT0_CNTW, 0);
	WWEG32(VM_CONTEXT1_CNTW, 0);
	/* Setup TWB contwow */
	WWEG32(MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_FWAGMENT_PWOCESSING |
	       SYSTEM_ACCESS_MODE_NOT_IN_SYS |
	       SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU);
	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
	       ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE |
	       EFFECTIVE_W2_QUEUE_SIZE(7) |
	       CONTEXT1_IDENTITY_ACCESS_MODE(1));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, W2_CACHE_BIGK_ASSOCIATIVITY |
	       W2_CACHE_BIGK_FWAGMENT_SIZE(6));
	wadeon_gawt_tabwe_vwam_unpin(wdev);
}

static void cayman_pcie_gawt_fini(stwuct wadeon_device *wdev)
{
	cayman_pcie_gawt_disabwe(wdev);
	wadeon_gawt_tabwe_vwam_fwee(wdev);
	wadeon_gawt_fini(wdev);
}

void cayman_cp_int_cntw_setup(stwuct wadeon_device *wdev,
			      int wing, u32 cp_int_cntw)
{
	WWEG32(SWBM_GFX_CNTW, WINGID(wing));
	WWEG32(CP_INT_CNTW, cp_int_cntw);
}

/*
 * CP.
 */
void cayman_fence_wing_emit(stwuct wadeon_device *wdev,
			    stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	u64 addw = wdev->fence_dwv[fence->wing].gpu_addw;
	u32 cp_cohew_cntw = PACKET3_FUWW_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* fwush wead cache ovew gawt fow this vmid */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
	wadeon_wing_wwite(wing, PACKET3_ENGINE_ME | cp_cohew_cntw);
	wadeon_wing_wwite(wing, 0xFFFFFFFF);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 10); /* poww intewvaw */
	/* EVENT_WWITE_EOP - fwush caches, send int */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
	wadeon_wing_wwite(wing, EVENT_TYPE(CACHE_FWUSH_AND_INV_EVENT_TS) | EVENT_INDEX(5));
	wadeon_wing_wwite(wing, wowew_32_bits(addw));
	wadeon_wing_wwite(wing, (uppew_32_bits(addw) & 0xff) | DATA_SEW(1) | INT_SEW(2));
	wadeon_wing_wwite(wing, fence->seq);
	wadeon_wing_wwite(wing, 0);
}

void cayman_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	unsigned vm_id = ib->vm ? ib->vm->ids[ib->wing].id : 0;
	u32 cp_cohew_cntw = PACKET3_FUWW_CACHE_ENA | PACKET3_TC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	/* set to DX10/11 mode */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_MODE_CONTWOW, 0));
	wadeon_wing_wwite(wing, 1);

	if (wing->wptw_save_weg) {
		uint32_t next_wptw = wing->wptw + 3 + 4 + 8;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		wadeon_wing_wwite(wing, ((wing->wptw_save_weg - 
					  PACKET3_SET_CONFIG_WEG_STAWT) >> 2));
		wadeon_wing_wwite(wing, next_wptw);
	}

	wadeon_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	wadeon_wing_wwite(wing,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addw & 0xFFFFFFFC));
	wadeon_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFF);
	wadeon_wing_wwite(wing, ib->wength_dw | (vm_id << 24));

	/* fwush wead cache ovew gawt fow this vmid */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
	wadeon_wing_wwite(wing, PACKET3_ENGINE_ME | cp_cohew_cntw);
	wadeon_wing_wwite(wing, 0xFFFFFFFF);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, (vm_id << 24) | 10); /* poww intewvaw */
}

static void cayman_cp_enabwe(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe)
		WWEG32(CP_ME_CNTW, 0);
	ewse {
		if (wdev->asic->copy.copy_wing_index == WADEON_WING_TYPE_GFX_INDEX)
			wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);
		WWEG32(CP_ME_CNTW, (CP_ME_HAWT | CP_PFP_HAWT));
		WWEG32(SCWATCH_UMSK, 0);
		wdev->wing[WADEON_WING_TYPE_GFX_INDEX].weady = fawse;
	}
}

u32 cayman_gfx_get_wptw(stwuct wadeon_device *wdev,
			stwuct wadeon_wing *wing)
{
	u32 wptw;

	if (wdev->wb.enabwed)
		wptw = wdev->wb.wb[wing->wptw_offs/4];
	ewse {
		if (wing->idx == WADEON_WING_TYPE_GFX_INDEX)
			wptw = WWEG32(CP_WB0_WPTW);
		ewse if (wing->idx == CAYMAN_WING_TYPE_CP1_INDEX)
			wptw = WWEG32(CP_WB1_WPTW);
		ewse
			wptw = WWEG32(CP_WB2_WPTW);
	}

	wetuwn wptw;
}

u32 cayman_gfx_get_wptw(stwuct wadeon_device *wdev,
			stwuct wadeon_wing *wing)
{
	u32 wptw;

	if (wing->idx == WADEON_WING_TYPE_GFX_INDEX)
		wptw = WWEG32(CP_WB0_WPTW);
	ewse if (wing->idx == CAYMAN_WING_TYPE_CP1_INDEX)
		wptw = WWEG32(CP_WB1_WPTW);
	ewse
		wptw = WWEG32(CP_WB2_WPTW);

	wetuwn wptw;
}

void cayman_gfx_set_wptw(stwuct wadeon_device *wdev,
			 stwuct wadeon_wing *wing)
{
	if (wing->idx == WADEON_WING_TYPE_GFX_INDEX) {
		WWEG32(CP_WB0_WPTW, wing->wptw);
		(void)WWEG32(CP_WB0_WPTW);
	} ewse if (wing->idx == CAYMAN_WING_TYPE_CP1_INDEX) {
		WWEG32(CP_WB1_WPTW, wing->wptw);
		(void)WWEG32(CP_WB1_WPTW);
	} ewse {
		WWEG32(CP_WB2_WPTW, wing->wptw);
		(void)WWEG32(CP_WB2_WPTW);
	}
}

static int cayman_cp_woad_micwocode(stwuct wadeon_device *wdev)
{
	const __be32 *fw_data;
	int i;

	if (!wdev->me_fw || !wdev->pfp_fw)
		wetuwn -EINVAW;

	cayman_cp_enabwe(wdev, fawse);

	fw_data = (const __be32 *)wdev->pfp_fw->data;
	WWEG32(CP_PFP_UCODE_ADDW, 0);
	fow (i = 0; i < CAYMAN_PFP_UCODE_SIZE; i++)
		WWEG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WWEG32(CP_PFP_UCODE_ADDW, 0);

	fw_data = (const __be32 *)wdev->me_fw->data;
	WWEG32(CP_ME_WAM_WADDW, 0);
	fow (i = 0; i < CAYMAN_PM4_UCODE_SIZE; i++)
		WWEG32(CP_ME_WAM_DATA, be32_to_cpup(fw_data++));

	WWEG32(CP_PFP_UCODE_ADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	wetuwn 0;
}

static int cayman_cp_stawt(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	int w, i;

	w = wadeon_wing_wock(wdev, wing, 7);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, PACKET3(PACKET3_ME_INITIAWIZE, 5));
	wadeon_wing_wwite(wing, 0x1);
	wadeon_wing_wwite(wing, 0x0);
	wadeon_wing_wwite(wing, wdev->config.cayman.max_hw_contexts - 1);
	wadeon_wing_wwite(wing, PACKET3_ME_INITIAWIZE_DEVICE_ID(1));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_unwock_commit(wdev, wing, fawse);

	cayman_cp_enabwe(wdev, twue);

	w = wadeon_wing_wock(wdev, wing, cayman_defauwt_size + 19);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}

	/* setup cweaw context state */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	wadeon_wing_wwite(wing, PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	fow (i = 0; i < cayman_defauwt_size; i++)
		wadeon_wing_wwite(wing, cayman_defauwt_state[i]);

	wadeon_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	wadeon_wing_wwite(wing, PACKET3_PWEAMBWE_END_CWEAW_STATE);

	/* set cweaw context state */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_CWEAW_STATE, 0));
	wadeon_wing_wwite(wing, 0);

	/* SQ_VTX_BASE_VTX_WOC */
	wadeon_wing_wwite(wing, 0xc0026f00);
	wadeon_wing_wwite(wing, 0x00000000);
	wadeon_wing_wwite(wing, 0x00000000);
	wadeon_wing_wwite(wing, 0x00000000);

	/* Cweaw consts */
	wadeon_wing_wwite(wing, 0xc0036f00);
	wadeon_wing_wwite(wing, 0x00000bc4);
	wadeon_wing_wwite(wing, 0xffffffff);
	wadeon_wing_wwite(wing, 0xffffffff);
	wadeon_wing_wwite(wing, 0xffffffff);

	wadeon_wing_wwite(wing, 0xc0026900);
	wadeon_wing_wwite(wing, 0x00000316);
	wadeon_wing_wwite(wing, 0x0000000e); /* VGT_VEWTEX_WEUSE_BWOCK_CNTW */
	wadeon_wing_wwite(wing, 0x00000010); /*  */

	wadeon_wing_unwock_commit(wdev, wing, fawse);

	/* XXX init othew wings */

	wetuwn 0;
}

static void cayman_cp_fini(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	cayman_cp_enabwe(wdev, fawse);
	wadeon_wing_fini(wdev, wing);
	wadeon_scwatch_fwee(wdev, wing->wptw_save_weg);
}

static int cayman_cp_wesume(stwuct wadeon_device *wdev)
{
	static const int widx[] = {
		WADEON_WING_TYPE_GFX_INDEX,
		CAYMAN_WING_TYPE_CP1_INDEX,
		CAYMAN_WING_TYPE_CP2_INDEX
	};
	static const unsigned cp_wb_cntw[] = {
		CP_WB0_CNTW,
		CP_WB1_CNTW,
		CP_WB2_CNTW,
	};
	static const unsigned cp_wb_wptw_addw[] = {
		CP_WB0_WPTW_ADDW,
		CP_WB1_WPTW_ADDW,
		CP_WB2_WPTW_ADDW
	};
	static const unsigned cp_wb_wptw_addw_hi[] = {
		CP_WB0_WPTW_ADDW_HI,
		CP_WB1_WPTW_ADDW_HI,
		CP_WB2_WPTW_ADDW_HI
	};
	static const unsigned cp_wb_base[] = {
		CP_WB0_BASE,
		CP_WB1_BASE,
		CP_WB2_BASE
	};
	static const unsigned cp_wb_wptw[] = {
		CP_WB0_WPTW,
		CP_WB1_WPTW,
		CP_WB2_WPTW
	};
	static const unsigned cp_wb_wptw[] = {
		CP_WB0_WPTW,
		CP_WB1_WPTW,
		CP_WB2_WPTW
	};
	stwuct wadeon_wing *wing;
	int i, w;

	/* Weset cp; if cp is weset, then PA, SH, VGT awso need to be weset */
	WWEG32(GWBM_SOFT_WESET, (SOFT_WESET_CP |
				 SOFT_WESET_PA |
				 SOFT_WESET_SH |
				 SOFT_WESET_VGT |
				 SOFT_WESET_SPI |
				 SOFT_WESET_SX));
	WWEG32(GWBM_SOFT_WESET);
	mdeway(15);
	WWEG32(GWBM_SOFT_WESET, 0);
	WWEG32(GWBM_SOFT_WESET);

	WWEG32(CP_SEM_WAIT_TIMEW, 0x0);
	WWEG32(CP_SEM_INCOMPWETE_TIMEW_CNTW, 0x0);

	/* Set the wwite pointew deway */
	WWEG32(CP_WB_WPTW_DEWAY, 0);

	WWEG32(CP_DEBUG, (1 << 27));

	/* set the wb addwess whethew it's enabwed ow not */
	WWEG32(SCWATCH_ADDW, ((wdev->wb.gpu_addw + WADEON_WB_SCWATCH_OFFSET) >> 8) & 0xFFFFFFFF);
	WWEG32(SCWATCH_UMSK, 0xff);

	fow (i = 0; i < 3; ++i) {
		uint32_t wb_cntw;
		uint64_t addw;

		/* Set wing buffew size */
		wing = &wdev->wing[widx[i]];
		wb_cntw = owdew_base_2(wing->wing_size / 8);
		wb_cntw |= owdew_base_2(WADEON_GPU_PAGE_SIZE/8) << 8;
#ifdef __BIG_ENDIAN
		wb_cntw |= BUF_SWAP_32BIT;
#endif
		WWEG32(cp_wb_cntw[i], wb_cntw);

		/* set the wb addwess whethew it's enabwed ow not */
		addw = wdev->wb.gpu_addw + WADEON_WB_CP_WPTW_OFFSET;
		WWEG32(cp_wb_wptw_addw[i], addw & 0xFFFFFFFC);
		WWEG32(cp_wb_wptw_addw_hi[i], uppew_32_bits(addw) & 0xFF);
	}

	/* set the wb base addw, this causes an intewnaw weset of AWW wings */
	fow (i = 0; i < 3; ++i) {
		wing = &wdev->wing[widx[i]];
		WWEG32(cp_wb_base[i], wing->gpu_addw >> 8);
	}

	fow (i = 0; i < 3; ++i) {
		/* Initiawize the wing buffew's wead and wwite pointews */
		wing = &wdev->wing[widx[i]];
		WWEG32_P(cp_wb_cntw[i], WB_WPTW_WW_ENA, ~WB_WPTW_WW_ENA);

		wing->wptw = 0;
		WWEG32(cp_wb_wptw[i], 0);
		WWEG32(cp_wb_wptw[i], wing->wptw);

		mdeway(1);
		WWEG32_P(cp_wb_cntw[i], 0, ~WB_WPTW_WW_ENA);
	}

	/* stawt the wings */
	cayman_cp_stawt(wdev);
	wdev->wing[WADEON_WING_TYPE_GFX_INDEX].weady = twue;
	wdev->wing[CAYMAN_WING_TYPE_CP1_INDEX].weady = fawse;
	wdev->wing[CAYMAN_WING_TYPE_CP2_INDEX].weady = fawse;
	/* this onwy test cp0 */
	w = wadeon_wing_test(wdev, WADEON_WING_TYPE_GFX_INDEX, &wdev->wing[WADEON_WING_TYPE_GFX_INDEX]);
	if (w) {
		wdev->wing[WADEON_WING_TYPE_GFX_INDEX].weady = fawse;
		wdev->wing[CAYMAN_WING_TYPE_CP1_INDEX].weady = fawse;
		wdev->wing[CAYMAN_WING_TYPE_CP2_INDEX].weady = fawse;
		wetuwn w;
	}

	if (wdev->asic->copy.copy_wing_index == WADEON_WING_TYPE_GFX_INDEX)
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.weaw_vwam_size);

	wetuwn 0;
}

u32 cayman_gpu_check_soft_weset(stwuct wadeon_device *wdev)
{
	u32 weset_mask = 0;
	u32 tmp;

	/* GWBM_STATUS */
	tmp = WWEG32(GWBM_STATUS);
	if (tmp & (PA_BUSY | SC_BUSY |
		   SH_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   GDS_BUSY | SPI_BUSY |
		   IA_BUSY | IA_BUSY_NO_DMA))
		weset_mask |= WADEON_WESET_GFX;

	if (tmp & (CF_WQ_PENDING | PF_WQ_PENDING |
		   CP_BUSY | CP_COHEWENCY_BUSY))
		weset_mask |= WADEON_WESET_CP;

	if (tmp & GWBM_EE_BUSY)
		weset_mask |= WADEON_WESET_GWBM | WADEON_WESET_GFX | WADEON_WESET_CP;

	/* DMA_STATUS_WEG 0 */
	tmp = WWEG32(DMA_STATUS_WEG + DMA0_WEGISTEW_OFFSET);
	if (!(tmp & DMA_IDWE))
		weset_mask |= WADEON_WESET_DMA;

	/* DMA_STATUS_WEG 1 */
	tmp = WWEG32(DMA_STATUS_WEG + DMA1_WEGISTEW_OFFSET);
	if (!(tmp & DMA_IDWE))
		weset_mask |= WADEON_WESET_DMA1;

	/* SWBM_STATUS2 */
	tmp = WWEG32(SWBM_STATUS2);
	if (tmp & DMA_BUSY)
		weset_mask |= WADEON_WESET_DMA;

	if (tmp & DMA1_BUSY)
		weset_mask |= WADEON_WESET_DMA1;

	/* SWBM_STATUS */
	tmp = WWEG32(SWBM_STATUS);
	if (tmp & (WWC_WQ_PENDING | WWC_BUSY))
		weset_mask |= WADEON_WESET_WWC;

	if (tmp & IH_BUSY)
		weset_mask |= WADEON_WESET_IH;

	if (tmp & SEM_BUSY)
		weset_mask |= WADEON_WESET_SEM;

	if (tmp & GWBM_WQ_PENDING)
		weset_mask |= WADEON_WESET_GWBM;

	if (tmp & VMC_BUSY)
		weset_mask |= WADEON_WESET_VMC;

	if (tmp & (MCB_BUSY | MCB_NON_DISPWAY_BUSY |
		   MCC_BUSY | MCD_BUSY))
		weset_mask |= WADEON_WESET_MC;

	if (evewgween_is_dispway_hung(wdev))
		weset_mask |= WADEON_WESET_DISPWAY;

	/* VM_W2_STATUS */
	tmp = WWEG32(VM_W2_STATUS);
	if (tmp & W2_BUSY)
		weset_mask |= WADEON_WESET_VMC;

	/* Skip MC weset as it's mostwy wikewy not hung, just busy */
	if (weset_mask & WADEON_WESET_MC) {
		DWM_DEBUG("MC busy: 0x%08X, cweawing.\n", weset_mask);
		weset_mask &= ~WADEON_WESET_MC;
	}

	wetuwn weset_mask;
}

static void cayman_gpu_soft_weset(stwuct wadeon_device *wdev, u32 weset_mask)
{
	stwuct evewgween_mc_save save;
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;

	if (weset_mask == 0)
		wetuwn;

	dev_info(wdev->dev, "GPU softweset: 0x%08X\n", weset_mask);

	evewgween_pwint_gpu_status_wegs(wdev);
	dev_info(wdev->dev, "  VM_CONTEXT0_PWOTECTION_FAUWT_ADDW   0x%08X\n",
		 WWEG32(0x14F8));
	dev_info(wdev->dev, "  VM_CONTEXT0_PWOTECTION_FAUWT_STATUS 0x%08X\n",
		 WWEG32(0x14D8));
	dev_info(wdev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_ADDW   0x%08X\n",
		 WWEG32(0x14FC));
	dev_info(wdev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_STATUS 0x%08X\n",
		 WWEG32(0x14DC));

	/* Disabwe CP pawsing/pwefetching */
	WWEG32(CP_ME_CNTW, CP_ME_HAWT | CP_PFP_HAWT);

	if (weset_mask & WADEON_WESET_DMA) {
		/* dma0 */
		tmp = WWEG32(DMA_WB_CNTW + DMA0_WEGISTEW_OFFSET);
		tmp &= ~DMA_WB_ENABWE;
		WWEG32(DMA_WB_CNTW + DMA0_WEGISTEW_OFFSET, tmp);
	}

	if (weset_mask & WADEON_WESET_DMA1) {
		/* dma1 */
		tmp = WWEG32(DMA_WB_CNTW + DMA1_WEGISTEW_OFFSET);
		tmp &= ~DMA_WB_ENABWE;
		WWEG32(DMA_WB_CNTW + DMA1_WEGISTEW_OFFSET, tmp);
	}

	udeway(50);

	evewgween_mc_stop(wdev, &save);
	if (evewgween_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}

	if (weset_mask & (WADEON_WESET_GFX | WADEON_WESET_COMPUTE)) {
		gwbm_soft_weset = SOFT_WESET_CB |
			SOFT_WESET_DB |
			SOFT_WESET_GDS |
			SOFT_WESET_PA |
			SOFT_WESET_SC |
			SOFT_WESET_SPI |
			SOFT_WESET_SH |
			SOFT_WESET_SX |
			SOFT_WESET_TC |
			SOFT_WESET_TA |
			SOFT_WESET_VGT |
			SOFT_WESET_IA;
	}

	if (weset_mask & WADEON_WESET_CP) {
		gwbm_soft_weset |= SOFT_WESET_CP | SOFT_WESET_VGT;

		swbm_soft_weset |= SOFT_WESET_GWBM;
	}

	if (weset_mask & WADEON_WESET_DMA)
		swbm_soft_weset |= SOFT_WESET_DMA;

	if (weset_mask & WADEON_WESET_DMA1)
		swbm_soft_weset |= SOFT_WESET_DMA1;

	if (weset_mask & WADEON_WESET_DISPWAY)
		swbm_soft_weset |= SOFT_WESET_DC;

	if (weset_mask & WADEON_WESET_WWC)
		swbm_soft_weset |= SOFT_WESET_WWC;

	if (weset_mask & WADEON_WESET_SEM)
		swbm_soft_weset |= SOFT_WESET_SEM;

	if (weset_mask & WADEON_WESET_IH)
		swbm_soft_weset |= SOFT_WESET_IH;

	if (weset_mask & WADEON_WESET_GWBM)
		swbm_soft_weset |= SOFT_WESET_GWBM;

	if (weset_mask & WADEON_WESET_VMC)
		swbm_soft_weset |= SOFT_WESET_VMC;

	if (!(wdev->fwags & WADEON_IS_IGP)) {
		if (weset_mask & WADEON_WESET_MC)
			swbm_soft_weset |= SOFT_WESET_MC;
	}

	if (gwbm_soft_weset) {
		tmp = WWEG32(GWBM_SOFT_WESET);
		tmp |= gwbm_soft_weset;
		dev_info(wdev->dev, "GWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(GWBM_SOFT_WESET, tmp);
		tmp = WWEG32(GWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~gwbm_soft_weset;
		WWEG32(GWBM_SOFT_WESET, tmp);
		tmp = WWEG32(GWBM_SOFT_WESET);
	}

	if (swbm_soft_weset) {
		tmp = WWEG32(SWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(wdev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(SWBM_SOFT_WESET, tmp);
		tmp = WWEG32(SWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(SWBM_SOFT_WESET, tmp);
		tmp = WWEG32(SWBM_SOFT_WESET);
	}

	/* Wait a wittwe fow things to settwe down */
	udeway(50);

	evewgween_mc_wesume(wdev, &save);
	udeway(50);

	evewgween_pwint_gpu_status_wegs(wdev);
}

int cayman_asic_weset(stwuct wadeon_device *wdev, boow hawd)
{
	u32 weset_mask;

	if (hawd) {
		evewgween_gpu_pci_config_weset(wdev);
		wetuwn 0;
	}

	weset_mask = cayman_gpu_check_soft_weset(wdev);

	if (weset_mask)
		w600_set_bios_scwatch_engine_hung(wdev, twue);

	cayman_gpu_soft_weset(wdev, weset_mask);

	weset_mask = cayman_gpu_check_soft_weset(wdev);

	if (weset_mask)
		evewgween_gpu_pci_config_weset(wdev);

	w600_set_bios_scwatch_engine_hung(wdev, fawse);

	wetuwn 0;
}

/**
 * cayman_gfx_is_wockup - Check if the GFX engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the GFX engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow cayman_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = cayman_gpu_check_soft_weset(wdev);

	if (!(weset_mask & (WADEON_WESET_GFX |
			    WADEON_WESET_COMPUTE |
			    WADEON_WESET_CP))) {
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}
	wetuwn wadeon_wing_test_wockup(wdev, wing);
}

static void cayman_uvd_init(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->has_uvd)
		wetuwn;

	w = wadeon_uvd_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed UVD (%d) init.\n", w);
		/*
		 * At this point wdev->uvd.vcpu_bo is NUWW which twickwes down
		 * to eawwy faiws uvd_v2_2_wesume() and thus nothing happens
		 * thewe. So it is pointwess to twy to go thwough that code
		 * hence why we disabwe uvd hewe.
		 */
		wdev->has_uvd = fawse;
		wetuwn;
	}
	wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[W600_WING_TYPE_UVD_INDEX], 4096);
}

static void cayman_uvd_stawt(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->has_uvd)
		wetuwn;

	w = uvd_v2_2_wesume(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed UVD wesume (%d).\n", w);
		goto ewwow;
	}
	w = wadeon_fence_dwivew_stawt_wing(wdev, W600_WING_TYPE_UVD_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD fences (%d).\n", w);
		goto ewwow;
	}
	wetuwn;

ewwow:
	wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_size = 0;
}

static void cayman_uvd_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int w;

	if (!wdev->has_uvd || !wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_size)
		wetuwn;

	wing = &wdev->wing[W600_WING_TYPE_UVD_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, 0, PACKET0(UVD_NO_OP, 0));
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD wing (%d).\n", w);
		wetuwn;
	}
	w = uvd_v1_0_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD (%d).\n", w);
		wetuwn;
	}
}

static void cayman_vce_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Onwy set fow CHIP_AWUBA */
	if (!wdev->has_vce)
		wetuwn;

	w = wadeon_vce_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed VCE (%d) init.\n", w);
		/*
		 * At this point wdev->vce.vcpu_bo is NUWW which twickwes down
		 * to eawwy faiws cayman_vce_stawt() and thus nothing happens
		 * thewe. So it is pointwess to twy to go thwough that code
		 * hence why we disabwe vce hewe.
		 */
		wdev->has_vce = fawse;
		wetuwn;
	}
	wdev->wing[TN_WING_TYPE_VCE1_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[TN_WING_TYPE_VCE1_INDEX], 4096);
	wdev->wing[TN_WING_TYPE_VCE2_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[TN_WING_TYPE_VCE2_INDEX], 4096);
}

static void cayman_vce_stawt(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->has_vce)
		wetuwn;

	w = wadeon_vce_wesume(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed VCE wesume (%d).\n", w);
		goto ewwow;
	}
	w = vce_v1_0_wesume(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed VCE wesume (%d).\n", w);
		goto ewwow;
	}
	w = wadeon_fence_dwivew_stawt_wing(wdev, TN_WING_TYPE_VCE1_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing VCE1 fences (%d).\n", w);
		goto ewwow;
	}
	w = wadeon_fence_dwivew_stawt_wing(wdev, TN_WING_TYPE_VCE2_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing VCE2 fences (%d).\n", w);
		goto ewwow;
	}
	wetuwn;

ewwow:
	wdev->wing[TN_WING_TYPE_VCE1_INDEX].wing_size = 0;
	wdev->wing[TN_WING_TYPE_VCE2_INDEX].wing_size = 0;
}

static void cayman_vce_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int w;

	if (!wdev->has_vce || !wdev->wing[TN_WING_TYPE_VCE1_INDEX].wing_size)
		wetuwn;

	wing = &wdev->wing[TN_WING_TYPE_VCE1_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, 0, 0x0);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing VCE1 wing (%d).\n", w);
		wetuwn;
	}
	wing = &wdev->wing[TN_WING_TYPE_VCE2_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, 0, 0x0);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing VCE1 wing (%d).\n", w);
		wetuwn;
	}
	w = vce_v1_0_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing VCE (%d).\n", w);
		wetuwn;
	}
}

static int cayman_stawtup(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	int w;

	/* enabwe pcie gen2 wink */
	evewgween_pcie_gen2_enabwe(wdev);
	/* enabwe aspm */
	evewgween_pwogwam_aspm(wdev);

	/* scwatch needs to be initiawized befowe MC */
	w = w600_vwam_scwatch_init(wdev);
	if (w)
		wetuwn w;

	evewgween_mc_pwogwam(wdev);

	if (!(wdev->fwags & WADEON_IS_IGP) && !wdev->pm.dpm_enabwed) {
		w = ni_mc_woad_micwocode(wdev);
		if (w) {
			DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
			wetuwn w;
		}
	}

	w = cayman_pcie_gawt_enabwe(wdev);
	if (w)
		wetuwn w;
	cayman_gpu_init(wdev);

	/* awwocate wwc buffews */
	if (wdev->fwags & WADEON_IS_IGP) {
		wdev->wwc.weg_wist = tn_wwc_save_westowe_wegistew_wist;
		wdev->wwc.weg_wist_size =
			(u32)AWWAY_SIZE(tn_wwc_save_westowe_wegistew_wist);
		wdev->wwc.cs_data = cayman_cs_data;
		w = sumo_wwc_init(wdev);
		if (w) {
			DWM_EWWOW("Faiwed to init wwc BOs!\n");
			wetuwn w;
		}
	}

	/* awwocate wb buffew */
	w = wadeon_wb_init(wdev);
	if (w)
		wetuwn w;

	w = wadeon_fence_dwivew_stawt_wing(wdev, WADEON_WING_TYPE_GFX_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	cayman_uvd_stawt(wdev);
	cayman_vce_stawt(wdev);

	w = wadeon_fence_dwivew_stawt_wing(wdev, CAYMAN_WING_TYPE_CP1_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_fence_dwivew_stawt_wing(wdev, CAYMAN_WING_TYPE_CP2_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_fence_dwivew_stawt_wing(wdev, W600_WING_TYPE_DMA_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing DMA fences (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_fence_dwivew_stawt_wing(wdev, CAYMAN_WING_TYPE_DMA1_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing DMA fences (%d).\n", w);
		wetuwn w;
	}

	/* Enabwe IWQ */
	if (!wdev->iwq.instawwed) {
		w = wadeon_iwq_kms_init(wdev);
		if (w)
			wetuwn w;
	}

	w = w600_iwq_init(wdev);
	if (w) {
		DWM_EWWOW("wadeon: IH init faiwed (%d).\n", w);
		wadeon_iwq_kms_fini(wdev);
		wetuwn w;
	}
	evewgween_iwq_set(wdev);

	w = wadeon_wing_init(wdev, wing, wing->wing_size, WADEON_WB_CP_WPTW_OFFSET,
			     WADEON_CP_PACKET2);
	if (w)
		wetuwn w;

	wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, W600_WB_DMA_WPTW_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	if (w)
		wetuwn w;

	wing = &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, CAYMAN_WB_DMA1_WPTW_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	if (w)
		wetuwn w;

	w = cayman_cp_woad_micwocode(wdev);
	if (w)
		wetuwn w;
	w = cayman_cp_wesume(wdev);
	if (w)
		wetuwn w;

	w = cayman_dma_wesume(wdev);
	if (w)
		wetuwn w;

	cayman_uvd_wesume(wdev);
	cayman_vce_wesume(wdev);

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_vm_managew_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "vm managew initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_audio_init(wdev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

int cayman_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Do not weset GPU befowe posting, on wv770 hw unwike on w500 hw,
	 * posting wiww pewfowm necessawy task to bwing back GPU into good
	 * shape.
	 */
	/* post cawd */
	atom_asic_init(wdev->mode_info.atom_context);

	/* init gowden wegistews */
	ni_init_gowden_wegistews(wdev);

	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_wesume(wdev);

	wdev->accew_wowking = twue;
	w = cayman_stawtup(wdev);
	if (w) {
		DWM_EWWOW("cayman stawtup faiwed on wesume\n");
		wdev->accew_wowking = fawse;
		wetuwn w;
	}
	wetuwn w;
}

int cayman_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	wadeon_audio_fini(wdev);
	wadeon_vm_managew_fini(wdev);
	cayman_cp_enabwe(wdev, fawse);
	cayman_dma_stop(wdev);
	if (wdev->has_uvd) {
		wadeon_uvd_suspend(wdev);
		uvd_v1_0_fini(wdev);
	}
	evewgween_iwq_suspend(wdev);
	wadeon_wb_disabwe(wdev);
	cayman_pcie_gawt_disabwe(wdev);
	wetuwn 0;
}

/* Pwan is to move initiawization in that function and use
 * hewpew function so that wadeon_device_init pwetty much
 * do nothing mowe than cawwing asic specific function. This
 * shouwd awso awwow to wemove a bunch of cawwback function
 * wike vwam_info.
 */
int cayman_init(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	int w;

	/* Wead BIOS */
	if (!wadeon_get_bios(wdev)) {
		if (ASIC_IS_AVIVO(wdev))
			wetuwn -EINVAW;
	}
	/* Must be an ATOMBIOS */
	if (!wdev->is_atom_bios) {
		dev_eww(wdev->dev, "Expecting atombios fow cayman GPU\n");
		wetuwn -EINVAW;
	}
	w = wadeon_atombios_init(wdev);
	if (w)
		wetuwn w;

	/* Post cawd if necessawy */
	if (!wadeon_cawd_posted(wdev)) {
		if (!wdev->bios) {
			dev_eww(wdev->dev, "Cawd not posted and no BIOS - ignowing\n");
			wetuwn -EINVAW;
		}
		DWM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(wdev->mode_info.atom_context);
	}
	/* init gowden wegistews */
	ni_init_gowden_wegistews(wdev);
	/* Initiawize scwatch wegistews */
	w600_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* Initiawize cwocks */
	wadeon_get_cwock_info(wdev->ddev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* initiawize memowy contwowwew */
	w = evewgween_mc_init(wdev);
	if (w)
		wetuwn w;
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;

	if (wdev->fwags & WADEON_IS_IGP) {
		if (!wdev->me_fw || !wdev->pfp_fw || !wdev->wwc_fw) {
			w = ni_init_micwocode(wdev);
			if (w) {
				DWM_EWWOW("Faiwed to woad fiwmwawe!\n");
				wetuwn w;
			}
		}
	} ewse {
		if (!wdev->me_fw || !wdev->pfp_fw || !wdev->wwc_fw || !wdev->mc_fw) {
			w = ni_init_micwocode(wdev);
			if (w) {
				DWM_EWWOW("Faiwed to woad fiwmwawe!\n");
				wetuwn w;
			}
		}
	}

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wing->wing_obj = NUWW;
	w600_wing_init(wdev, wing, 1024 * 1024);

	wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
	wing->wing_obj = NUWW;
	w600_wing_init(wdev, wing, 64 * 1024);

	wing = &wdev->wing[CAYMAN_WING_TYPE_DMA1_INDEX];
	wing->wing_obj = NUWW;
	w600_wing_init(wdev, wing, 64 * 1024);

	cayman_uvd_init(wdev);
	cayman_vce_init(wdev);

	wdev->ih.wing_obj = NUWW;
	w600_ih_wing_init(wdev, 64 * 1024);

	w = w600_pcie_gawt_init(wdev);
	if (w)
		wetuwn w;

	wdev->accew_wowking = twue;
	w = cayman_stawtup(wdev);
	if (w) {
		dev_eww(wdev->dev, "disabwing GPU accewewation\n");
		cayman_cp_fini(wdev);
		cayman_dma_fini(wdev);
		w600_iwq_fini(wdev);
		if (wdev->fwags & WADEON_IS_IGP)
			sumo_wwc_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		wadeon_vm_managew_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		cayman_pcie_gawt_fini(wdev);
		wdev->accew_wowking = fawse;
	}

	/* Don't stawt up if the MC ucode is missing.
	 * The defauwt cwocks and vowtages befowe the MC ucode
	 * is woaded awe not suffient fow advanced opewations.
	 *
	 * We can skip this check fow TN, because thewe is no MC
	 * ucode.
	 */
	if (!wdev->mc_fw && !(wdev->fwags & WADEON_IS_IGP)) {
		DWM_EWWOW("wadeon: MC ucode wequiwed fow NI+.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void cayman_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	cayman_cp_fini(wdev);
	cayman_dma_fini(wdev);
	w600_iwq_fini(wdev);
	if (wdev->fwags & WADEON_IS_IGP)
		sumo_wwc_fini(wdev);
	wadeon_wb_fini(wdev);
	wadeon_vm_managew_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	uvd_v1_0_fini(wdev);
	wadeon_uvd_fini(wdev);
	if (wdev->has_vce)
		wadeon_vce_fini(wdev);
	cayman_pcie_gawt_fini(wdev);
	w600_vwam_scwatch_fini(wdev);
	wadeon_gem_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_bo_fini(wdev);
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

/*
 * vm
 */
int cayman_vm_init(stwuct wadeon_device *wdev)
{
	/* numbew of VMs */
	wdev->vm_managew.nvm = 8;
	/* base offset of vwam pages */
	if (wdev->fwags & WADEON_IS_IGP) {
		u64 tmp = WWEG32(FUS_MC_VM_FB_OFFSET);
		tmp <<= 22;
		wdev->vm_managew.vwam_base_offset = tmp;
	} ewse
		wdev->vm_managew.vwam_base_offset = 0;
	wetuwn 0;
}

void cayman_vm_fini(stwuct wadeon_device *wdev)
{
}

/**
 * cayman_vm_decode_fauwt - pwint human weadabwe fauwt info
 *
 * @wdev: wadeon_device pointew
 * @status: VM_CONTEXT1_PWOTECTION_FAUWT_STATUS wegistew vawue
 * @addw: VM_CONTEXT1_PWOTECTION_FAUWT_ADDW wegistew vawue
 *
 * Pwint human weadabwe fauwt infowmation (cayman/TN).
 */
void cayman_vm_decode_fauwt(stwuct wadeon_device *wdev,
			    u32 status, u32 addw)
{
	u32 mc_id = (status & MEMOWY_CWIENT_ID_MASK) >> MEMOWY_CWIENT_ID_SHIFT;
	u32 vmid = (status & FAUWT_VMID_MASK) >> FAUWT_VMID_SHIFT;
	u32 pwotections = (status & PWOTECTIONS_MASK) >> PWOTECTIONS_SHIFT;
	chaw *bwock;

	switch (mc_id) {
	case 32:
	case 16:
	case 96:
	case 80:
	case 160:
	case 144:
	case 224:
	case 208:
		bwock = "CB";
		bweak;
	case 33:
	case 17:
	case 97:
	case 81:
	case 161:
	case 145:
	case 225:
	case 209:
		bwock = "CB_FMASK";
		bweak;
	case 34:
	case 18:
	case 98:
	case 82:
	case 162:
	case 146:
	case 226:
	case 210:
		bwock = "CB_CMASK";
		bweak;
	case 35:
	case 19:
	case 99:
	case 83:
	case 163:
	case 147:
	case 227:
	case 211:
		bwock = "CB_IMMED";
		bweak;
	case 36:
	case 20:
	case 100:
	case 84:
	case 164:
	case 148:
	case 228:
	case 212:
		bwock = "DB";
		bweak;
	case 37:
	case 21:
	case 101:
	case 85:
	case 165:
	case 149:
	case 229:
	case 213:
		bwock = "DB_HTIWE";
		bweak;
	case 38:
	case 22:
	case 102:
	case 86:
	case 166:
	case 150:
	case 230:
	case 214:
		bwock = "SX";
		bweak;
	case 39:
	case 23:
	case 103:
	case 87:
	case 167:
	case 151:
	case 231:
	case 215:
		bwock = "DB_STEN";
		bweak;
	case 40:
	case 24:
	case 104:
	case 88:
	case 232:
	case 216:
	case 168:
	case 152:
		bwock = "TC_TFETCH";
		bweak;
	case 41:
	case 25:
	case 105:
	case 89:
	case 233:
	case 217:
	case 169:
	case 153:
		bwock = "TC_VFETCH";
		bweak;
	case 42:
	case 26:
	case 106:
	case 90:
	case 234:
	case 218:
	case 170:
	case 154:
		bwock = "VC";
		bweak;
	case 112:
		bwock = "CP";
		bweak;
	case 113:
	case 114:
		bwock = "SH";
		bweak;
	case 115:
		bwock = "VGT";
		bweak;
	case 178:
		bwock = "IH";
		bweak;
	case 51:
		bwock = "WWC";
		bweak;
	case 55:
		bwock = "DMA";
		bweak;
	case 56:
		bwock = "HDP";
		bweak;
	defauwt:
		bwock = "unknown";
		bweak;
	}

	pwintk("VM fauwt (0x%02x, vmid %d) at page %u, %s fwom %s (%d)\n",
	       pwotections, vmid, addw,
	       (status & MEMOWY_CWIENT_WW_MASK) ? "wwite" : "wead",
	       bwock, mc_id);
}

/*
 * cayman_vm_fwush - vm fwush using the CP
 *
 * Update the page tabwe base and fwush the VM TWB
 * using the CP (cayman-si).
 */
void cayman_vm_fwush(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing,
		     unsigned vm_id, uint64_t pd_addw)
{
	wadeon_wing_wwite(wing, PACKET0(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW + (vm_id << 2), 0));
	wadeon_wing_wwite(wing, pd_addw >> 12);

	/* fwush hdp cache */
	wadeon_wing_wwite(wing, PACKET0(HDP_MEM_COHEWENCY_FWUSH_CNTW, 0));
	wadeon_wing_wwite(wing, 0x1);

	/* bits 0-7 awe the VM contexts0-7 */
	wadeon_wing_wwite(wing, PACKET0(VM_INVAWIDATE_WEQUEST, 0));
	wadeon_wing_wwite(wing, 1 << vm_id);

	/* wait fow the invawidate to compwete */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_WAIT_WEG_MEM, 5));
	wadeon_wing_wwite(wing, (WAIT_WEG_MEM_FUNCTION(0) |  /* awways */
				 WAIT_WEG_MEM_ENGINE(0))); /* me */
	wadeon_wing_wwite(wing, VM_INVAWIDATE_WEQUEST >> 2);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 0); /* wef */
	wadeon_wing_wwite(wing, 0); /* mask */
	wadeon_wing_wwite(wing, 0x20); /* poww intewvaw */

	/* sync PFP to ME, othewwise we might get invawid PFP weads */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_PFP_SYNC_ME, 0));
	wadeon_wing_wwite(wing, 0x0);
}

int tn_set_vce_cwocks(stwuct wadeon_device *wdev, u32 evcwk, u32 eccwk)
{
	stwuct atom_cwock_dividews dividews;
	int w, i;

	w = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					   eccwk, fawse, &dividews);
	if (w)
		wetuwn w;

	fow (i = 0; i < 100; i++) {
		if (WWEG32(CG_ECWK_STATUS) & ECWK_STATUS)
			bweak;
		mdeway(10);
	}
	if (i == 100)
		wetuwn -ETIMEDOUT;

	WWEG32_P(CG_ECWK_CNTW, dividews.post_div, ~(ECWK_DIW_CNTW_EN|ECWK_DIVIDEW_MASK));

	fow (i = 0; i < 100; i++) {
		if (WWEG32(CG_ECWK_STATUS) & ECWK_STATUS)
			bweak;
		mdeway(10);
	}
	if (i == 100)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}
