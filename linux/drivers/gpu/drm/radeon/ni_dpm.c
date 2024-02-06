/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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

#incwude <winux/math64.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>

#incwude "atom.h"
#incwude "evewgween.h"
#incwude "ni_dpm.h"
#incwude "nid.h"
#incwude "w600_dpm.h"
#incwude "wv770.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define SMC_WAM_END 0xC000

static const stwuct ni_cac_weights cac_weights_cayman_xt =
{
	0x15,
	0x2,
	0x19,
	0x2,
	0x8,
	0x14,
	0x2,
	0x16,
	0xE,
	0x17,
	0x13,
	0x2B,
	0x10,
	0x7,
	0x5,
	0x5,
	0x5,
	0x2,
	0x3,
	0x9,
	0x10,
	0x10,
	0x2B,
	0xA,
	0x9,
	0x4,
	0xD,
	0xD,
	0x3E,
	0x18,
	0x14,
	0,
	0x3,
	0x3,
	0x5,
	0,
	0x2,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0x1CC,
	0,
	0x164,
	1,
	1,
	1,
	1,
	12,
	12,
	12,
	0x12,
	0x1F,
	132,
	5,
	7,
	0,
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	twue
};

static const stwuct ni_cac_weights cac_weights_cayman_pwo =
{
	0x16,
	0x4,
	0x10,
	0x2,
	0xA,
	0x16,
	0x2,
	0x18,
	0x10,
	0x1A,
	0x16,
	0x2D,
	0x12,
	0xA,
	0x6,
	0x6,
	0x6,
	0x2,
	0x4,
	0xB,
	0x11,
	0x11,
	0x2D,
	0xC,
	0xC,
	0x7,
	0x10,
	0x10,
	0x3F,
	0x1A,
	0x16,
	0,
	0x7,
	0x4,
	0x6,
	1,
	0x2,
	0x1,
	0,
	0,
	0,
	0,
	0,
	0,
	0x30,
	0,
	0x1CF,
	0,
	0x166,
	1,
	1,
	1,
	1,
	12,
	12,
	12,
	0x15,
	0x1F,
	132,
	6,
	6,
	0,
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	twue
};

static const stwuct ni_cac_weights cac_weights_cayman_we =
{
	0x7,
	0xE,
	0x1,
	0xA,
	0x1,
	0x3F,
	0x2,
	0x18,
	0x10,
	0x1A,
	0x1,
	0x3F,
	0x1,
	0xE,
	0x6,
	0x6,
	0x6,
	0x2,
	0x4,
	0x9,
	0x1A,
	0x1A,
	0x2C,
	0xA,
	0x11,
	0x8,
	0x19,
	0x19,
	0x1,
	0x1,
	0x1A,
	0,
	0x8,
	0x5,
	0x8,
	0x1,
	0x3,
	0x1,
	0,
	0,
	0,
	0,
	0,
	0,
	0x38,
	0x38,
	0x239,
	0x3,
	0x18A,
	1,
	1,
	1,
	1,
	12,
	12,
	12,
	0x15,
	0x22,
	132,
	6,
	6,
	0,
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	twue
};

#define NISWANDS_MGCG_SEQUENCE  300

static const u32 cayman_cgcg_cgws_defauwt[] =
{
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
};
#define CAYMAN_CGCG_CGWS_DEFAUWT_WENGTH sizeof(cayman_cgcg_cgws_defauwt) / (3 * sizeof(u32))

static const u32 cayman_cgcg_cgws_disabwe[] =
{
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00000644, 0x000f7902, 0x001f4180,
	0x00000644, 0x000f3802, 0x001f4180
};
#define CAYMAN_CGCG_CGWS_DISABWE_WENGTH sizeof(cayman_cgcg_cgws_disabwe) / (3 * sizeof(u32))

static const u32 cayman_cgcg_cgws_enabwe[] =
{
	0x00000644, 0x000f7882, 0x001f4080,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000020, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000021, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000022, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000023, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000024, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000025, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000026, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000027, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000028, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000029, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002a, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x0000002b, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff
};
#define CAYMAN_CGCG_CGWS_ENABWE_WENGTH  sizeof(cayman_cgcg_cgws_enabwe) / (3 * sizeof(u32))

static const u32 cayman_mgcg_defauwt[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00003fc4, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00000100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x00008984, 0x06000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00800200, 0xffffffff,
	0x00009a60, 0x00000100, 0xffffffff,
	0x00009868, 0x00000100, 0xffffffff,
	0x00008d58, 0x00000100, 0xffffffff,
	0x00009510, 0x00000100, 0xffffffff,
	0x0000949c, 0x00000100, 0xffffffff,
	0x00009654, 0x00000100, 0xffffffff,
	0x00009030, 0x00000100, 0xffffffff,
	0x00009034, 0x00000100, 0xffffffff,
	0x00009038, 0x00000100, 0xffffffff,
	0x0000903c, 0x00000100, 0xffffffff,
	0x00009040, 0x00000100, 0xffffffff,
	0x0000a200, 0x00000100, 0xffffffff,
	0x0000a204, 0x00000100, 0xffffffff,
	0x0000a208, 0x00000100, 0xffffffff,
	0x0000a20c, 0x00000100, 0xffffffff,
	0x00009744, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009664, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000104, 0xffffffff,
	0x0000d0c0, 0x00000100, 0xffffffff,
	0x0000d8c0, 0x00000100, 0xffffffff,
	0x0000802c, 0x40000000, 0xffffffff,
	0x00003fc4, 0x40000000, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009224, 0x00070000, 0xffffffff,
	0x00009228, 0x00030002, 0xffffffff,
	0x0000922c, 0x00050004, 0xffffffff,
	0x00009238, 0x00010006, 0xffffffff,
	0x0000923c, 0x00090008, 0xffffffff,
	0x00009240, 0x00070000, 0xffffffff,
	0x00009244, 0x00030002, 0xffffffff,
	0x00009248, 0x00050004, 0xffffffff,
	0x00009254, 0x00010006, 0xffffffff,
	0x00009258, 0x00090008, 0xffffffff,
	0x0000925c, 0x00070000, 0xffffffff,
	0x00009260, 0x00030002, 0xffffffff,
	0x00009264, 0x00050004, 0xffffffff,
	0x00009270, 0x00010006, 0xffffffff,
	0x00009274, 0x00090008, 0xffffffff,
	0x00009278, 0x00070000, 0xffffffff,
	0x0000927c, 0x00030002, 0xffffffff,
	0x00009280, 0x00050004, 0xffffffff,
	0x0000928c, 0x00010006, 0xffffffff,
	0x00009290, 0x00090008, 0xffffffff,
	0x000092a8, 0x00070000, 0xffffffff,
	0x000092ac, 0x00030002, 0xffffffff,
	0x000092b0, 0x00050004, 0xffffffff,
	0x000092bc, 0x00010006, 0xffffffff,
	0x000092c0, 0x00090008, 0xffffffff,
	0x000092c4, 0x00070000, 0xffffffff,
	0x000092c8, 0x00030002, 0xffffffff,
	0x000092cc, 0x00050004, 0xffffffff,
	0x000092d8, 0x00010006, 0xffffffff,
	0x000092dc, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0x40010000, 0xffffffff,
	0x00003fc4, 0x40010000, 0xffffffff,
	0x0000915c, 0x00010000, 0xffffffff,
	0x00009160, 0x00030002, 0xffffffff,
	0x00009164, 0x00050004, 0xffffffff,
	0x00009168, 0x00070006, 0xffffffff,
	0x00009178, 0x00070000, 0xffffffff,
	0x0000917c, 0x00030002, 0xffffffff,
	0x00009180, 0x00050004, 0xffffffff,
	0x0000918c, 0x00010006, 0xffffffff,
	0x00009190, 0x00090008, 0xffffffff,
	0x00009194, 0x00070000, 0xffffffff,
	0x00009198, 0x00030002, 0xffffffff,
	0x0000919c, 0x00050004, 0xffffffff,
	0x000091a8, 0x00010006, 0xffffffff,
	0x000091ac, 0x00090008, 0xffffffff,
	0x000091b0, 0x00070000, 0xffffffff,
	0x000091b4, 0x00030002, 0xffffffff,
	0x000091b8, 0x00050004, 0xffffffff,
	0x000091c4, 0x00010006, 0xffffffff,
	0x000091c8, 0x00090008, 0xffffffff,
	0x000091cc, 0x00070000, 0xffffffff,
	0x000091d0, 0x00030002, 0xffffffff,
	0x000091d4, 0x00050004, 0xffffffff,
	0x000091e0, 0x00010006, 0xffffffff,
	0x000091e4, 0x00090008, 0xffffffff,
	0x000091e8, 0x00000000, 0xffffffff,
	0x000091ec, 0x00070000, 0xffffffff,
	0x000091f0, 0x00030002, 0xffffffff,
	0x000091f4, 0x00050004, 0xffffffff,
	0x00009200, 0x00010006, 0xffffffff,
	0x00009204, 0x00090008, 0xffffffff,
	0x00009208, 0x00070000, 0xffffffff,
	0x0000920c, 0x00030002, 0xffffffff,
	0x00009210, 0x00050004, 0xffffffff,
	0x0000921c, 0x00010006, 0xffffffff,
	0x00009220, 0x00090008, 0xffffffff,
	0x00009224, 0x00070000, 0xffffffff,
	0x00009228, 0x00030002, 0xffffffff,
	0x0000922c, 0x00050004, 0xffffffff,
	0x00009238, 0x00010006, 0xffffffff,
	0x0000923c, 0x00090008, 0xffffffff,
	0x00009240, 0x00070000, 0xffffffff,
	0x00009244, 0x00030002, 0xffffffff,
	0x00009248, 0x00050004, 0xffffffff,
	0x00009254, 0x00010006, 0xffffffff,
	0x00009258, 0x00090008, 0xffffffff,
	0x0000925c, 0x00070000, 0xffffffff,
	0x00009260, 0x00030002, 0xffffffff,
	0x00009264, 0x00050004, 0xffffffff,
	0x00009270, 0x00010006, 0xffffffff,
	0x00009274, 0x00090008, 0xffffffff,
	0x00009278, 0x00070000, 0xffffffff,
	0x0000927c, 0x00030002, 0xffffffff,
	0x00009280, 0x00050004, 0xffffffff,
	0x0000928c, 0x00010006, 0xffffffff,
	0x00009290, 0x00090008, 0xffffffff,
	0x000092a8, 0x00070000, 0xffffffff,
	0x000092ac, 0x00030002, 0xffffffff,
	0x000092b0, 0x00050004, 0xffffffff,
	0x000092bc, 0x00010006, 0xffffffff,
	0x000092c0, 0x00090008, 0xffffffff,
	0x000092c4, 0x00070000, 0xffffffff,
	0x000092c8, 0x00030002, 0xffffffff,
	0x000092cc, 0x00050004, 0xffffffff,
	0x000092d8, 0x00010006, 0xffffffff,
	0x000092dc, 0x00090008, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00003fc4, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000010, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000011, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000012, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000013, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000014, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000015, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000016, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000017, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000018, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000019, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001a, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x0000001b, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff
};
#define CAYMAN_MGCG_DEFAUWT_WENGTH sizeof(cayman_mgcg_defauwt) / (3 * sizeof(u32))

static const u32 cayman_mgcg_disabwe[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0xffffffff, 0xffffffff,
	0x00009150, 0x00600000, 0xffffffff
};
#define CAYMAN_MGCG_DISABWE_WENGTH   sizeof(cayman_mgcg_disabwe) / (3 * sizeof(u32))

static const u32 cayman_mgcg_enabwe[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00600000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x96944200, 0xffffffff
};

#define CAYMAN_MGCG_ENABWE_WENGTH   sizeof(cayman_mgcg_enabwe) / (3 * sizeof(u32))

#define NISWANDS_SYSWS_SEQUENCE  100

static const u32 cayman_sysws_defauwt[] =
{
	/* Wegistew,   Vawue,     Mask bits */
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x0000d8bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x00002f50, 0x00000404, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00008dfc, 0x00000000, 0xffffffff
};
#define CAYMAN_SYSWS_DEFAUWT_WENGTH sizeof(cayman_sysws_defauwt) / (3 * sizeof(u32))

static const u32 cayman_sysws_disabwe[] =
{
	/* Wegistew,   Vawue,     Mask bits */
	0x0000d0c0, 0x00000000, 0xffffffff,
	0x0000d8c0, 0x00000000, 0xffffffff,
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x0000d8bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x00002f50, 0x00000404, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00008dfc, 0x0000007f, 0xffffffff
};
#define CAYMAN_SYSWS_DISABWE_WENGTH sizeof(cayman_sysws_disabwe) / (3 * sizeof(u32))

static const u32 cayman_sysws_enabwe[] =
{
	/* Wegistew,   Vawue,     Mask bits */
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x0000d8bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x00002f50, 0x00000903, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00008dfc, 0x00000000, 0xffffffff
};
#define CAYMAN_SYSWS_ENABWE_WENGTH sizeof(cayman_sysws_enabwe) / (3 * sizeof(u32))

extewn int ni_mc_woad_micwocode(stwuct wadeon_device *wdev);

stwuct ni_powew_info *ni_get_pi(stwuct wadeon_device *wdev)
{
	stwuct ni_powew_info *pi = wdev->pm.dpm.pwiv;

	wetuwn pi;
}

stwuct ni_ps *ni_get_ps(stwuct wadeon_ps *wps)
{
	stwuct ni_ps *ps = wps->ps_pwiv;

	wetuwn ps;
}

static void ni_cawcuwate_weakage_fow_v_and_t_fowmuwa(const stwuct ni_weakage_coeffients *coeff,
						     u16 v, s32 t,
						     u32 iweakage,
						     u32 *weakage)
{
	s64 kt, kv, weakage_w, i_weakage, vddc, tempewatuwe;

	i_weakage = div64_s64(dwm_int2fixp(iweakage), 1000);
	vddc = div64_s64(dwm_int2fixp(v), 1000);
	tempewatuwe = div64_s64(dwm_int2fixp(t), 1000);

	kt = dwm_fixp_muw(div64_s64(dwm_int2fixp(coeff->at), 1000),
			  dwm_fixp_exp(dwm_fixp_muw(div64_s64(dwm_int2fixp(coeff->bt), 1000), tempewatuwe)));
	kv = dwm_fixp_muw(div64_s64(dwm_int2fixp(coeff->av), 1000),
			  dwm_fixp_exp(dwm_fixp_muw(div64_s64(dwm_int2fixp(coeff->bv), 1000), vddc)));

	weakage_w = dwm_fixp_muw(dwm_fixp_muw(dwm_fixp_muw(i_weakage, kt), kv), vddc);

	*weakage = dwm_fixp2int(weakage_w * 1000);
}

static void ni_cawcuwate_weakage_fow_v_and_t(stwuct wadeon_device *wdev,
					     const stwuct ni_weakage_coeffients *coeff,
					     u16 v,
					     s32 t,
					     u32 i_weakage,
					     u32 *weakage)
{
	ni_cawcuwate_weakage_fow_v_and_t_fowmuwa(coeff, v, t, i_weakage, weakage);
}

boow ni_dpm_vbwank_too_showt(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 vbwank_time = w600_dpm_get_vbwank_time(wdev);
	/* we nevew hit the non-gddw5 wimit so disabwe it */
	u32 switch_wimit = pi->mem_gddw5 ? 450 : 0;

	if (vbwank_time < switch_wimit)
		wetuwn twue;
	ewse
		wetuwn fawse;

}

static void ni_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *wps)
{
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wadeon_cwock_and_vowtage_wimits *max_wimits;
	boow disabwe_mcwk_switching;
	u32 mcwk;
	u16 vddci;
	int i;

	if ((wdev->pm.dpm.new_active_cwtc_count > 1) ||
	    ni_dpm_vbwank_too_showt(wdev))
		disabwe_mcwk_switching = twue;
	ewse
		disabwe_mcwk_switching = fawse;

	if (wdev->pm.dpm.ac_powew)
		max_wimits = &wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;
	ewse
		max_wimits = &wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc;

	if (wdev->pm.dpm.ac_powew == fawse) {
		fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
			if (ps->pewfowmance_wevews[i].mcwk > max_wimits->mcwk)
				ps->pewfowmance_wevews[i].mcwk = max_wimits->mcwk;
			if (ps->pewfowmance_wevews[i].scwk > max_wimits->scwk)
				ps->pewfowmance_wevews[i].scwk = max_wimits->scwk;
			if (ps->pewfowmance_wevews[i].vddc > max_wimits->vddc)
				ps->pewfowmance_wevews[i].vddc = max_wimits->vddc;
			if (ps->pewfowmance_wevews[i].vddci > max_wimits->vddci)
				ps->pewfowmance_wevews[i].vddci = max_wimits->vddci;
		}
	}

	/* XXX vawidate the min cwocks wequiwed fow dispway */

	/* adjust wow state */
	if (disabwe_mcwk_switching) {
		ps->pewfowmance_wevews[0].mcwk =
			ps->pewfowmance_wevews[ps->pewfowmance_wevew_count - 1].mcwk;
		ps->pewfowmance_wevews[0].vddci =
			ps->pewfowmance_wevews[ps->pewfowmance_wevew_count - 1].vddci;
	}

	btc_skip_bwackwist_cwocks(wdev, max_wimits->scwk, max_wimits->mcwk,
				  &ps->pewfowmance_wevews[0].scwk,
				  &ps->pewfowmance_wevews[0].mcwk);

	fow (i = 1; i < ps->pewfowmance_wevew_count; i++) {
		if (ps->pewfowmance_wevews[i].scwk < ps->pewfowmance_wevews[i - 1].scwk)
			ps->pewfowmance_wevews[i].scwk = ps->pewfowmance_wevews[i - 1].scwk;
		if (ps->pewfowmance_wevews[i].vddc < ps->pewfowmance_wevews[i - 1].vddc)
			ps->pewfowmance_wevews[i].vddc = ps->pewfowmance_wevews[i - 1].vddc;
	}

	/* adjust wemaining states */
	if (disabwe_mcwk_switching) {
		mcwk = ps->pewfowmance_wevews[0].mcwk;
		vddci = ps->pewfowmance_wevews[0].vddci;
		fow (i = 1; i < ps->pewfowmance_wevew_count; i++) {
			if (mcwk < ps->pewfowmance_wevews[i].mcwk)
				mcwk = ps->pewfowmance_wevews[i].mcwk;
			if (vddci < ps->pewfowmance_wevews[i].vddci)
				vddci = ps->pewfowmance_wevews[i].vddci;
		}
		fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
			ps->pewfowmance_wevews[i].mcwk = mcwk;
			ps->pewfowmance_wevews[i].vddci = vddci;
		}
	} ewse {
		fow (i = 1; i < ps->pewfowmance_wevew_count; i++) {
			if (ps->pewfowmance_wevews[i].mcwk < ps->pewfowmance_wevews[i - 1].mcwk)
				ps->pewfowmance_wevews[i].mcwk = ps->pewfowmance_wevews[i - 1].mcwk;
			if (ps->pewfowmance_wevews[i].vddci < ps->pewfowmance_wevews[i - 1].vddci)
				ps->pewfowmance_wevews[i].vddci = ps->pewfowmance_wevews[i - 1].vddci;
		}
	}

	fow (i = 1; i < ps->pewfowmance_wevew_count; i++)
		btc_skip_bwackwist_cwocks(wdev, max_wimits->scwk, max_wimits->mcwk,
					  &ps->pewfowmance_wevews[i].scwk,
					  &ps->pewfowmance_wevews[i].mcwk);

	fow (i = 0; i < ps->pewfowmance_wevew_count; i++)
		btc_adjust_cwock_combinations(wdev, max_wimits,
					      &ps->pewfowmance_wevews[i]);

	fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
		btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
						   ps->pewfowmance_wevews[i].scwk,
						   max_wimits->vddc,  &ps->pewfowmance_wevews[i].vddc);
		btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
						   ps->pewfowmance_wevews[i].mcwk,
						   max_wimits->vddci, &ps->pewfowmance_wevews[i].vddci);
		btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
						   ps->pewfowmance_wevews[i].mcwk,
						   max_wimits->vddc,  &ps->pewfowmance_wevews[i].vddc);
		btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk,
						   wdev->cwock.cuwwent_dispcwk,
						   max_wimits->vddc,  &ps->pewfowmance_wevews[i].vddc);
	}

	fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
		btc_appwy_vowtage_dewta_wuwes(wdev,
					      max_wimits->vddc, max_wimits->vddci,
					      &ps->pewfowmance_wevews[i].vddc,
					      &ps->pewfowmance_wevews[i].vddci);
	}

	ps->dc_compatibwe = twue;
	fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
		if (ps->pewfowmance_wevews[i].vddc > wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc)
			ps->dc_compatibwe = fawse;

		if (ps->pewfowmance_wevews[i].vddc < wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2)
			ps->pewfowmance_wevews[i].fwags &= ~ATOM_PPWIB_W600_FWAGS_PCIEGEN2;
	}
}

static void ni_cg_cwockgating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *ps = NUWW;

	ps = (const u32 *)&cayman_cgcg_cgws_defauwt;
	count = CAYMAN_CGCG_CGWS_DEFAUWT_WENGTH;

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);
}

static void ni_gfx_cwockgating_enabwe(stwuct wadeon_device *wdev,
				      boow enabwe)
{
	u32 count;
	const u32 *ps = NUWW;

	if (enabwe) {
		ps = (const u32 *)&cayman_cgcg_cgws_enabwe;
		count = CAYMAN_CGCG_CGWS_ENABWE_WENGTH;
	} ewse {
		ps = (const u32 *)&cayman_cgcg_cgws_disabwe;
		count = CAYMAN_CGCG_CGWS_DISABWE_WENGTH;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);
}

static void ni_mg_cwockgating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *ps = NUWW;

	ps = (const u32 *)&cayman_mgcg_defauwt;
	count = CAYMAN_MGCG_DEFAUWT_WENGTH;

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);
}

static void ni_mg_cwockgating_enabwe(stwuct wadeon_device *wdev,
				     boow enabwe)
{
	u32 count;
	const u32 *ps = NUWW;

	if (enabwe) {
		ps = (const u32 *)&cayman_mgcg_enabwe;
		count = CAYMAN_MGCG_ENABWE_WENGTH;
	} ewse {
		ps = (const u32 *)&cayman_mgcg_disabwe;
		count = CAYMAN_MGCG_DISABWE_WENGTH;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);
}

static void ni_ws_cwockgating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *ps = NUWW;

	ps = (const u32 *)&cayman_sysws_defauwt;
	count = CAYMAN_SYSWS_DEFAUWT_WENGTH;

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);
}

static void ni_ws_cwockgating_enabwe(stwuct wadeon_device *wdev,
				     boow enabwe)
{
	u32 count;
	const u32 *ps = NUWW;

	if (enabwe) {
		ps = (const u32 *)&cayman_sysws_enabwe;
		count = CAYMAN_SYSWS_ENABWE_WENGTH;
	} ewse {
		ps = (const u32 *)&cayman_sysws_disabwe;
		count = CAYMAN_SYSWS_DISABWE_WENGTH;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, ps, count);

}

static int ni_patch_singwe_dependency_tabwe_based_on_weakage(stwuct wadeon_device *wdev,
							     stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 i;

	if (tabwe) {
		fow (i = 0; i < tabwe->count; i++) {
			if (0xff01 == tabwe->entwies[i].v) {
				if (pi->max_vddc == 0)
					wetuwn -EINVAW;
				tabwe->entwies[i].v = pi->max_vddc;
			}
		}
	}
	wetuwn 0;
}

static int ni_patch_dependency_tabwes_based_on_weakage(stwuct wadeon_device *wdev)
{
	int wet = 0;

	wet = ni_patch_singwe_dependency_tabwe_based_on_weakage(wdev,
								&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk);

	wet = ni_patch_singwe_dependency_tabwe_based_on_weakage(wdev,
								&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk);
	wetuwn wet;
}

static void ni_stop_dpm(stwuct wadeon_device *wdev)
{
	WWEG32_P(GENEWAW_PWWMGT, 0, ~GWOBAW_PWWMGT_EN);
}

#if 0
static int ni_notify_hw_of_powew_souwce(stwuct wadeon_device *wdev,
					boow ac_powew)
{
	if (ac_powew)
		wetuwn (wv770_send_msg_to_smc(wdev, PPSMC_MSG_WunningOnAC) == PPSMC_Wesuwt_OK) ?
			0 : -EINVAW;

	wetuwn 0;
}
#endif

static PPSMC_Wesuwt ni_send_msg_to_smc_with_pawametew(stwuct wadeon_device *wdev,
						      PPSMC_Msg msg, u32 pawametew)
{
	WWEG32(SMC_SCWATCH0, pawametew);
	wetuwn wv770_send_msg_to_smc(wdev, msg);
}

static int ni_westwict_pewfowmance_wevews_befowe_switch(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_NoFowcedWevew) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetEnabwedWevews, 1) == PPSMC_Wesuwt_OK) ?
		0 : -EINVAW;
}

int ni_dpm_fowce_pewfowmance_wevew(stwuct wadeon_device *wdev,
				   enum wadeon_dpm_fowced_wevew wevew)
{
	if (wevew == WADEON_DPM_FOWCED_WEVEW_HIGH) {
		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetEnabwedWevews, 0) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;

		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetFowcedWevews, 1) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) {
		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetFowcedWevews, 0) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;

		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetEnabwedWevews, 1) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
	} ewse if (wevew == WADEON_DPM_FOWCED_WEVEW_AUTO) {
		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetFowcedWevews, 0) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;

		if (ni_send_msg_to_smc_with_pawametew(wdev, PPSMC_MSG_SetEnabwedWevews, 0) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
	}

	wdev->pm.dpm.fowced_wevew = wevew;

	wetuwn 0;
}

static void ni_stop_smc(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32(WB_SYNC_WESET_SEW) & WB_SYNC_WESET_SEW_MASK;
		if (tmp != 1)
			bweak;
		udeway(1);
	}

	udeway(100);

	w7xx_stop_smc(wdev);
}

static int ni_pwocess_fiwmwawe_headew(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 tmp;
	int wet;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_stateTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	pi->state_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_softWegistews,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	pi->soft_wegs_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_mcWegistewTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	eg_pi->mc_weg_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_fanTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	ni_pi->fan_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_mcAwbDwamAutoWefweshTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	ni_pi->awb_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_cacTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	ni_pi->cac_tabwe_stawt = (u16)tmp;

	wet = wv770_wead_smc_swam_dwowd(wdev,
					NISWANDS_SMC_FIWMWAWE_HEADEW_WOCATION +
					NISWANDS_SMC_FIWMWAWE_HEADEW_spwwTabwe,
					&tmp, pi->swam_end);

	if (wet)
		wetuwn wet;

	ni_pi->spww_tabwe_stawt = (u16)tmp;


	wetuwn wet;
}

static void ni_wead_cwock_wegistews(stwuct wadeon_device *wdev)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);

	ni_pi->cwock_wegistews.cg_spww_func_cntw = WWEG32(CG_SPWW_FUNC_CNTW);
	ni_pi->cwock_wegistews.cg_spww_func_cntw_2 = WWEG32(CG_SPWW_FUNC_CNTW_2);
	ni_pi->cwock_wegistews.cg_spww_func_cntw_3 = WWEG32(CG_SPWW_FUNC_CNTW_3);
	ni_pi->cwock_wegistews.cg_spww_func_cntw_4 = WWEG32(CG_SPWW_FUNC_CNTW_4);
	ni_pi->cwock_wegistews.cg_spww_spwead_spectwum = WWEG32(CG_SPWW_SPWEAD_SPECTWUM);
	ni_pi->cwock_wegistews.cg_spww_spwead_spectwum_2 = WWEG32(CG_SPWW_SPWEAD_SPECTWUM_2);
	ni_pi->cwock_wegistews.mpww_ad_func_cntw = WWEG32(MPWW_AD_FUNC_CNTW);
	ni_pi->cwock_wegistews.mpww_ad_func_cntw_2 = WWEG32(MPWW_AD_FUNC_CNTW_2);
	ni_pi->cwock_wegistews.mpww_dq_func_cntw = WWEG32(MPWW_DQ_FUNC_CNTW);
	ni_pi->cwock_wegistews.mpww_dq_func_cntw_2 = WWEG32(MPWW_DQ_FUNC_CNTW_2);
	ni_pi->cwock_wegistews.mcwk_pwwmgt_cntw = WWEG32(MCWK_PWWMGT_CNTW);
	ni_pi->cwock_wegistews.dww_cntw = WWEG32(DWW_CNTW);
	ni_pi->cwock_wegistews.mpww_ss1 = WWEG32(MPWW_SS1);
	ni_pi->cwock_wegistews.mpww_ss2 = WWEG32(MPWW_SS2);
}

#if 0
static int ni_entew_uwp_state(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);

	if (pi->gfx_cwock_gating) {
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~DYN_GFX_CWK_OFF_EN);
		WWEG32_P(SCWK_PWWMGT_CNTW, GFX_CWK_FOWCE_ON, ~GFX_CWK_FOWCE_ON);
		WWEG32_P(SCWK_PWWMGT_CNTW, 0, ~GFX_CWK_FOWCE_ON);
		WWEG32(GB_ADDW_CONFIG);
	}

	WWEG32_P(SMC_MSG, HOST_SMC_MSG(PPSMC_MSG_SwitchToMinimumPowew),
		 ~HOST_SMC_MSG_MASK);

	udeway(25000);

	wetuwn 0;
}
#endif

static void ni_pwogwam_wesponse_times(stwuct wadeon_device *wdev)
{
	u32 vowtage_wesponse_time, backbias_wesponse_time, acpi_deway_time, vbi_time_out;
	u32 vddc_dwy, bb_dwy, acpi_dwy, vbi_dwy, mcwk_switch_wimit;
	u32 wefewence_cwock;

	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_mvdd_chg_time, 1);

	vowtage_wesponse_time = (u32)wdev->pm.dpm.vowtage_wesponse_time;
	backbias_wesponse_time = (u32)wdev->pm.dpm.backbias_wesponse_time;

	if (vowtage_wesponse_time == 0)
		vowtage_wesponse_time = 1000;

	if (backbias_wesponse_time == 0)
		backbias_wesponse_time = 1000;

	acpi_deway_time = 15000;
	vbi_time_out = 100000;

	wefewence_cwock = wadeon_get_xcwk(wdev);

	vddc_dwy = (vowtage_wesponse_time  * wefewence_cwock) / 1600;
	bb_dwy   = (backbias_wesponse_time * wefewence_cwock) / 1600;
	acpi_dwy = (acpi_deway_time * wefewence_cwock) / 1600;
	vbi_dwy  = (vbi_time_out * wefewence_cwock) / 1600;

	mcwk_switch_wimit = (460 * wefewence_cwock) / 100;

	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_deway_vweg,  vddc_dwy);
	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_deway_bbias, bb_dwy);
	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_deway_acpi,  acpi_dwy);
	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_mcwk_chg_timeout, vbi_dwy);
	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_mc_bwock_deway, 0xAA);
	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_mcwk_switch_wim, mcwk_switch_wimit);
}

static void ni_popuwate_smc_vowtage_tabwe(stwuct wadeon_device *wdev,
					  stwuct atom_vowtage_tabwe *vowtage_tabwe,
					  NISWANDS_SMC_STATETABWE *tabwe)
{
	unsigned int i;

	fow (i = 0; i < vowtage_tabwe->count; i++) {
		tabwe->highSMIO[i] = 0;
		tabwe->wowSMIO[i] |= cpu_to_be32(vowtage_tabwe->entwies[i].smio_wow);
	}
}

static void ni_popuwate_smc_vowtage_tabwes(stwuct wadeon_device *wdev,
					   NISWANDS_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	unsigned chaw i;

	if (eg_pi->vddc_vowtage_tabwe.count) {
		ni_popuwate_smc_vowtage_tabwe(wdev, &eg_pi->vddc_vowtage_tabwe, tabwe);
		tabwe->vowtageMaskTabwe.highMask[NISWANDS_SMC_VOWTAGEMASK_VDDC] = 0;
		tabwe->vowtageMaskTabwe.wowMask[NISWANDS_SMC_VOWTAGEMASK_VDDC] =
			cpu_to_be32(eg_pi->vddc_vowtage_tabwe.mask_wow);

		fow (i = 0; i < eg_pi->vddc_vowtage_tabwe.count; i++) {
			if (pi->max_vddc_in_tabwe <= eg_pi->vddc_vowtage_tabwe.entwies[i].vawue) {
				tabwe->maxVDDCIndexInPPTabwe = i;
				bweak;
			}
		}
	}

	if (eg_pi->vddci_vowtage_tabwe.count) {
		ni_popuwate_smc_vowtage_tabwe(wdev, &eg_pi->vddci_vowtage_tabwe, tabwe);

		tabwe->vowtageMaskTabwe.highMask[NISWANDS_SMC_VOWTAGEMASK_VDDCI] = 0;
		tabwe->vowtageMaskTabwe.wowMask[NISWANDS_SMC_VOWTAGEMASK_VDDCI] =
			cpu_to_be32(eg_pi->vddci_vowtage_tabwe.mask_wow);
	}
}

static int ni_popuwate_vowtage_vawue(stwuct wadeon_device *wdev,
				     stwuct atom_vowtage_tabwe *tabwe,
				     u16 vawue,
				     NISWANDS_SMC_VOWTAGE_VAWUE *vowtage)
{
	unsigned int i;

	fow (i = 0; i < tabwe->count; i++) {
		if (vawue <= tabwe->entwies[i].vawue) {
			vowtage->index = (u8)i;
			vowtage->vawue = cpu_to_be16(tabwe->entwies[i].vawue);
			bweak;
		}
	}

	if (i >= tabwe->count)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ni_popuwate_mvdd_vawue(stwuct wadeon_device *wdev,
				   u32 mcwk,
				   NISWANDS_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (!pi->mvdd_contwow) {
		vowtage->index = eg_pi->mvdd_high_index;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
		wetuwn;
	}

	if (mcwk <= pi->mvdd_spwit_fwequency) {
		vowtage->index = eg_pi->mvdd_wow_index;
		vowtage->vawue = cpu_to_be16(MVDD_WOW_VAWUE);
	} ewse {
		vowtage->index = eg_pi->mvdd_high_index;
		vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
	}
}

static int ni_get_std_vowtage_vawue(stwuct wadeon_device *wdev,
				    NISWANDS_SMC_VOWTAGE_VAWUE *vowtage,
				    u16 *std_vowtage)
{
	if (wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies &&
	    ((u32)vowtage->index < wdev->pm.dpm.dyn_state.cac_weakage_tabwe.count))
		*std_vowtage = wdev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[vowtage->index].vddc;
	ewse
		*std_vowtage = be16_to_cpu(vowtage->vawue);

	wetuwn 0;
}

static void ni_popuwate_std_vowtage_vawue(stwuct wadeon_device *wdev,
					  u16 vawue, u8 index,
					  NISWANDS_SMC_VOWTAGE_VAWUE *vowtage)
{
	vowtage->index = index;
	vowtage->vawue = cpu_to_be16(vawue);
}

static u32 ni_get_smc_powew_scawing_factow(stwuct wadeon_device *wdev)
{
	u32 xcwk_pewiod;
	u32 xcwk = wadeon_get_xcwk(wdev);
	u32 tmp = WWEG32(CG_CAC_CTWW) & TID_CNT_MASK;

	xcwk_pewiod = (1000000000UW / xcwk);
	xcwk_pewiod /= 10000UW;

	wetuwn tmp * xcwk_pewiod;
}

static u32 ni_scawe_powew_fow_smc(u32 powew_in_watts, u32 scawing_factow)
{
	wetuwn (powew_in_watts * scawing_factow) << 2;
}

static u32 ni_cawcuwate_powew_boost_wimit(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *wadeon_state,
					  u32 neaw_tdp_wimit)
{
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 powew_boost_wimit = 0;
	int wet;

	if (ni_pi->enabwe_powew_containment &&
	    ni_pi->use_powew_boost_wimit) {
		NISWANDS_SMC_VOWTAGE_VAWUE vddc;
		u16 std_vddc_med;
		u16 std_vddc_high;
		u64 tmp, n, d;

		if (state->pewfowmance_wevew_count < 3)
			wetuwn 0;

		wet = ni_popuwate_vowtage_vawue(wdev, &eg_pi->vddc_vowtage_tabwe,
						state->pewfowmance_wevews[state->pewfowmance_wevew_count - 2].vddc,
						&vddc);
		if (wet)
			wetuwn 0;

		wet = ni_get_std_vowtage_vawue(wdev, &vddc, &std_vddc_med);
		if (wet)
			wetuwn 0;

		wet = ni_popuwate_vowtage_vawue(wdev, &eg_pi->vddc_vowtage_tabwe,
						state->pewfowmance_wevews[state->pewfowmance_wevew_count - 1].vddc,
						&vddc);
		if (wet)
			wetuwn 0;

		wet = ni_get_std_vowtage_vawue(wdev, &vddc, &std_vddc_high);
		if (wet)
			wetuwn 0;

		n = ((u64)neaw_tdp_wimit * ((u64)std_vddc_med * (u64)std_vddc_med) * 90);
		d = ((u64)std_vddc_high * (u64)std_vddc_high * 100);
		tmp = div64_u64(n, d);

		if (tmp >> 32)
			wetuwn 0;
		powew_boost_wimit = (u32)tmp;
	}

	wetuwn powew_boost_wimit;
}

static int ni_cawcuwate_adjusted_tdp_wimits(stwuct wadeon_device *wdev,
					    boow adjust_powawity,
					    u32 tdp_adjustment,
					    u32 *tdp_wimit,
					    u32 *neaw_tdp_wimit)
{
	if (tdp_adjustment > (u32)wdev->pm.dpm.tdp_od_wimit)
		wetuwn -EINVAW;

	if (adjust_powawity) {
		*tdp_wimit = ((100 + tdp_adjustment) * wdev->pm.dpm.tdp_wimit) / 100;
		*neaw_tdp_wimit = wdev->pm.dpm.neaw_tdp_wimit + (*tdp_wimit - wdev->pm.dpm.tdp_wimit);
	} ewse {
		*tdp_wimit = ((100 - tdp_adjustment) * wdev->pm.dpm.tdp_wimit) / 100;
		*neaw_tdp_wimit = wdev->pm.dpm.neaw_tdp_wimit - (wdev->pm.dpm.tdp_wimit - *tdp_wimit);
	}

	wetuwn 0;
}

static int ni_popuwate_smc_tdp_wimits(stwuct wadeon_device *wdev,
				      stwuct wadeon_ps *wadeon_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);

	if (ni_pi->enabwe_powew_containment) {
		NISWANDS_SMC_STATETABWE *smc_tabwe = &ni_pi->smc_statetabwe;
		u32 scawing_factow = ni_get_smc_powew_scawing_factow(wdev);
		u32 tdp_wimit;
		u32 neaw_tdp_wimit;
		u32 powew_boost_wimit;
		int wet;

		if (scawing_factow == 0)
			wetuwn -EINVAW;

		memset(smc_tabwe, 0, sizeof(NISWANDS_SMC_STATETABWE));

		wet = ni_cawcuwate_adjusted_tdp_wimits(wdev,
						       fawse, /* ??? */
						       wdev->pm.dpm.tdp_adjustment,
						       &tdp_wimit,
						       &neaw_tdp_wimit);
		if (wet)
			wetuwn wet;

		powew_boost_wimit = ni_cawcuwate_powew_boost_wimit(wdev, wadeon_state,
								   neaw_tdp_wimit);

		smc_tabwe->dpm2Pawams.TDPWimit =
			cpu_to_be32(ni_scawe_powew_fow_smc(tdp_wimit, scawing_factow));
		smc_tabwe->dpm2Pawams.NeawTDPWimit =
			cpu_to_be32(ni_scawe_powew_fow_smc(neaw_tdp_wimit, scawing_factow));
		smc_tabwe->dpm2Pawams.SafePowewWimit =
			cpu_to_be32(ni_scawe_powew_fow_smc((neaw_tdp_wimit * NISWANDS_DPM2_TDP_SAFE_WIMIT_PEWCENT) / 100,
							   scawing_factow));
		smc_tabwe->dpm2Pawams.PowewBoostWimit =
			cpu_to_be32(ni_scawe_powew_fow_smc(powew_boost_wimit, scawing_factow));

		wet = wv770_copy_bytes_to_smc(wdev,
					      (u16)(pi->state_tabwe_stawt + offsetof(NISWANDS_SMC_STATETABWE, dpm2Pawams) +
						    offsetof(PP_NIswands_DPM2Pawametews, TDPWimit)),
					      (u8 *)(&smc_tabwe->dpm2Pawams.TDPWimit),
					      sizeof(u32) * 4, pi->swam_end);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int ni_copy_and_switch_awb_sets(stwuct wadeon_device *wdev,
				u32 awb_fweq_swc, u32 awb_fweq_dest)
{
	u32 mc_awb_dwam_timing;
	u32 mc_awb_dwam_timing2;
	u32 buwst_time;
	u32 mc_cg_config;

	switch (awb_fweq_swc) {
	case MC_CG_AWB_FWEQ_F0:
		mc_awb_dwam_timing  = WWEG32(MC_AWB_DWAM_TIMING);
		mc_awb_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);
		buwst_time = (WWEG32(MC_AWB_BUWST_TIME) & STATE0_MASK) >> STATE0_SHIFT;
		bweak;
	case MC_CG_AWB_FWEQ_F1:
		mc_awb_dwam_timing  = WWEG32(MC_AWB_DWAM_TIMING_1);
		mc_awb_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2_1);
		buwst_time = (WWEG32(MC_AWB_BUWST_TIME) & STATE1_MASK) >> STATE1_SHIFT;
		bweak;
	case MC_CG_AWB_FWEQ_F2:
		mc_awb_dwam_timing  = WWEG32(MC_AWB_DWAM_TIMING_2);
		mc_awb_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2_2);
		buwst_time = (WWEG32(MC_AWB_BUWST_TIME) & STATE2_MASK) >> STATE2_SHIFT;
		bweak;
	case MC_CG_AWB_FWEQ_F3:
		mc_awb_dwam_timing  = WWEG32(MC_AWB_DWAM_TIMING_3);
		mc_awb_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2_3);
		buwst_time = (WWEG32(MC_AWB_BUWST_TIME) & STATE3_MASK) >> STATE3_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (awb_fweq_dest) {
	case MC_CG_AWB_FWEQ_F0:
		WWEG32(MC_AWB_DWAM_TIMING, mc_awb_dwam_timing);
		WWEG32(MC_AWB_DWAM_TIMING2, mc_awb_dwam_timing2);
		WWEG32_P(MC_AWB_BUWST_TIME, STATE0(buwst_time), ~STATE0_MASK);
		bweak;
	case MC_CG_AWB_FWEQ_F1:
		WWEG32(MC_AWB_DWAM_TIMING_1, mc_awb_dwam_timing);
		WWEG32(MC_AWB_DWAM_TIMING2_1, mc_awb_dwam_timing2);
		WWEG32_P(MC_AWB_BUWST_TIME, STATE1(buwst_time), ~STATE1_MASK);
		bweak;
	case MC_CG_AWB_FWEQ_F2:
		WWEG32(MC_AWB_DWAM_TIMING_2, mc_awb_dwam_timing);
		WWEG32(MC_AWB_DWAM_TIMING2_2, mc_awb_dwam_timing2);
		WWEG32_P(MC_AWB_BUWST_TIME, STATE2(buwst_time), ~STATE2_MASK);
		bweak;
	case MC_CG_AWB_FWEQ_F3:
		WWEG32(MC_AWB_DWAM_TIMING_3, mc_awb_dwam_timing);
		WWEG32(MC_AWB_DWAM_TIMING2_3, mc_awb_dwam_timing2);
		WWEG32_P(MC_AWB_BUWST_TIME, STATE3(buwst_time), ~STATE3_MASK);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mc_cg_config = WWEG32(MC_CG_CONFIG) | 0x0000000F;
	WWEG32(MC_CG_CONFIG, mc_cg_config);
	WWEG32_P(MC_AWB_CG, CG_AWB_WEQ(awb_fweq_dest), ~CG_AWB_WEQ_MASK);

	wetuwn 0;
}

static int ni_init_awb_tabwe_index(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 tmp;
	int wet;

	wet = wv770_wead_smc_swam_dwowd(wdev, ni_pi->awb_tabwe_stawt,
					&tmp, pi->swam_end);
	if (wet)
		wetuwn wet;

	tmp &= 0x00FFFFFF;
	tmp |= ((u32)MC_CG_AWB_FWEQ_F1) << 24;

	wetuwn wv770_wwite_smc_swam_dwowd(wdev, ni_pi->awb_tabwe_stawt,
					  tmp, pi->swam_end);
}

static int ni_initiaw_switch_fwom_awb_f0_to_f1(stwuct wadeon_device *wdev)
{
	wetuwn ni_copy_and_switch_awb_sets(wdev, MC_CG_AWB_FWEQ_F0, MC_CG_AWB_FWEQ_F1);
}

static int ni_fowce_switch_to_awb_f0(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 tmp;
	int wet;

	wet = wv770_wead_smc_swam_dwowd(wdev, ni_pi->awb_tabwe_stawt,
					&tmp, pi->swam_end);
	if (wet)
		wetuwn wet;

	tmp = (tmp >> 24) & 0xff;

	if (tmp == MC_CG_AWB_FWEQ_F0)
		wetuwn 0;

	wetuwn ni_copy_and_switch_awb_sets(wdev, tmp, MC_CG_AWB_FWEQ_F0);
}

static int ni_popuwate_memowy_timing_pawametews(stwuct wadeon_device *wdev,
						stwuct wv7xx_pw *pw,
						SMC_NIswands_MCAwbDwamTimingWegistewSet *awb_wegs)
{
	u32 dwam_timing;
	u32 dwam_timing2;

	awb_wegs->mc_awb_wfsh_wate =
		(u8)wv770_cawcuwate_memowy_wefwesh_wate(wdev, pw->scwk);


	wadeon_atom_set_engine_dwam_timings(wdev, pw->scwk, pw->mcwk);

	dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);

	awb_wegs->mc_awb_dwam_timing  = cpu_to_be32(dwam_timing);
	awb_wegs->mc_awb_dwam_timing2 = cpu_to_be32(dwam_timing2);

	wetuwn 0;
}

static int ni_do_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
						  stwuct wadeon_ps *wadeon_state,
						  unsigned int fiwst_awb_set)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	SMC_NIswands_MCAwbDwamTimingWegistewSet awb_wegs = { 0 };
	int i, wet = 0;

	fow (i = 0; i < state->pewfowmance_wevew_count; i++) {
		wet = ni_popuwate_memowy_timing_pawametews(wdev, &state->pewfowmance_wevews[i], &awb_wegs);
		if (wet)
			bweak;

		wet = wv770_copy_bytes_to_smc(wdev,
					      (u16)(ni_pi->awb_tabwe_stawt +
						    offsetof(SMC_NIswands_MCAwbDwamTimingWegistews, data) +
						    sizeof(SMC_NIswands_MCAwbDwamTimingWegistewSet) * (fiwst_awb_set + i)),
					      (u8 *)&awb_wegs,
					      (u16)sizeof(SMC_NIswands_MCAwbDwamTimingWegistewSet),
					      pi->swam_end);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static int ni_pwogwam_memowy_timing_pawametews(stwuct wadeon_device *wdev,
					       stwuct wadeon_ps *wadeon_new_state)
{
	wetuwn ni_do_pwogwam_memowy_timing_pawametews(wdev, wadeon_new_state,
						      NISWANDS_DWIVEW_STATE_AWB_INDEX);
}

static void ni_popuwate_initiaw_mvdd_vawue(stwuct wadeon_device *wdev,
					   stwuct NISWANDS_SMC_VOWTAGE_VAWUE *vowtage)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	vowtage->index = eg_pi->mvdd_high_index;
	vowtage->vawue = cpu_to_be16(MVDD_HIGH_VAWUE);
}

static int ni_popuwate_smc_initiaw_state(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wadeon_initiaw_state,
					 NISWANDS_SMC_STATETABWE *tabwe)
{
	stwuct ni_ps *initiaw_state = ni_get_ps(wadeon_initiaw_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 weg;
	int wet;

	tabwe->initiawState.wevew.mcwk.vMPWW_AD_FUNC_CNTW =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_ad_func_cntw);
	tabwe->initiawState.wevew.mcwk.vMPWW_AD_FUNC_CNTW_2 =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_ad_func_cntw_2);
	tabwe->initiawState.wevew.mcwk.vMPWW_DQ_FUNC_CNTW =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_dq_func_cntw);
	tabwe->initiawState.wevew.mcwk.vMPWW_DQ_FUNC_CNTW_2 =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_dq_func_cntw_2);
	tabwe->initiawState.wevew.mcwk.vMCWK_PWWMGT_CNTW =
		cpu_to_be32(ni_pi->cwock_wegistews.mcwk_pwwmgt_cntw);
	tabwe->initiawState.wevew.mcwk.vDWW_CNTW =
		cpu_to_be32(ni_pi->cwock_wegistews.dww_cntw);
	tabwe->initiawState.wevew.mcwk.vMPWW_SS =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_ss1);
	tabwe->initiawState.wevew.mcwk.vMPWW_SS2 =
		cpu_to_be32(ni_pi->cwock_wegistews.mpww_ss2);
	tabwe->initiawState.wevew.mcwk.mcwk_vawue =
		cpu_to_be32(initiaw_state->pewfowmance_wevews[0].mcwk);

	tabwe->initiawState.wevew.scwk.vCG_SPWW_FUNC_CNTW =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_func_cntw);
	tabwe->initiawState.wevew.scwk.vCG_SPWW_FUNC_CNTW_2 =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_func_cntw_2);
	tabwe->initiawState.wevew.scwk.vCG_SPWW_FUNC_CNTW_3 =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_func_cntw_3);
	tabwe->initiawState.wevew.scwk.vCG_SPWW_FUNC_CNTW_4 =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_func_cntw_4);
	tabwe->initiawState.wevew.scwk.vCG_SPWW_SPWEAD_SPECTWUM =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_spwead_spectwum);
	tabwe->initiawState.wevew.scwk.vCG_SPWW_SPWEAD_SPECTWUM_2 =
		cpu_to_be32(ni_pi->cwock_wegistews.cg_spww_spwead_spectwum_2);
	tabwe->initiawState.wevew.scwk.scwk_vawue =
		cpu_to_be32(initiaw_state->pewfowmance_wevews[0].scwk);
	tabwe->initiawState.wevew.awbWefweshState =
		NISWANDS_INITIAW_STATE_AWB_INDEX;

	tabwe->initiawState.wevew.ACIndex = 0;

	wet = ni_popuwate_vowtage_vawue(wdev, &eg_pi->vddc_vowtage_tabwe,
					initiaw_state->pewfowmance_wevews[0].vddc,
					&tabwe->initiawState.wevew.vddc);
	if (!wet) {
		u16 std_vddc;

		wet = ni_get_std_vowtage_vawue(wdev,
					       &tabwe->initiawState.wevew.vddc,
					       &std_vddc);
		if (!wet)
			ni_popuwate_std_vowtage_vawue(wdev, std_vddc,
						      tabwe->initiawState.wevew.vddc.index,
						      &tabwe->initiawState.wevew.std_vddc);
	}

	if (eg_pi->vddci_contwow)
		ni_popuwate_vowtage_vawue(wdev,
					  &eg_pi->vddci_vowtage_tabwe,
					  initiaw_state->pewfowmance_wevews[0].vddci,
					  &tabwe->initiawState.wevew.vddci);

	ni_popuwate_initiaw_mvdd_vawue(wdev, &tabwe->initiawState.wevew.mvdd);

	weg = CG_W(0xffff) | CG_W(0);
	tabwe->initiawState.wevew.aT = cpu_to_be32(weg);

	tabwe->initiawState.wevew.bSP = cpu_to_be32(pi->dsp);

	if (pi->boot_in_gen2)
		tabwe->initiawState.wevew.gen2PCIE = 1;
	ewse
		tabwe->initiawState.wevew.gen2PCIE = 0;

	if (pi->mem_gddw5) {
		tabwe->initiawState.wevew.stwobeMode =
			cypwess_get_stwobe_mode_settings(wdev,
							 initiaw_state->pewfowmance_wevews[0].mcwk);

		if (initiaw_state->pewfowmance_wevews[0].mcwk > pi->mcwk_edc_enabwe_thweshowd)
			tabwe->initiawState.wevew.mcFwags = NISWANDS_SMC_MC_EDC_WD_FWAG | NISWANDS_SMC_MC_EDC_WW_FWAG;
		ewse
			tabwe->initiawState.wevew.mcFwags =  0;
	}

	tabwe->initiawState.wevewCount = 1;

	tabwe->initiawState.fwags |= PPSMC_SWSTATE_FWAG_DC;

	tabwe->initiawState.wevew.dpm2.MaxPS = 0;
	tabwe->initiawState.wevew.dpm2.NeawTDPDec = 0;
	tabwe->initiawState.wevew.dpm2.AboveSafeInc = 0;
	tabwe->initiawState.wevew.dpm2.BewowSafeInc = 0;

	weg = MIN_POWEW_MASK | MAX_POWEW_MASK;
	tabwe->initiawState.wevew.SQPowewThwottwe = cpu_to_be32(weg);

	weg = MAX_POWEW_DEWTA_MASK | STI_SIZE_MASK | WTI_WATIO_MASK;
	tabwe->initiawState.wevew.SQPowewThwottwe_2 = cpu_to_be32(weg);

	wetuwn 0;
}

static int ni_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				      NISWANDS_SMC_STATETABWE *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 mpww_ad_func_cntw   = ni_pi->cwock_wegistews.mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2 = ni_pi->cwock_wegistews.mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw   = ni_pi->cwock_wegistews.mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2 = ni_pi->cwock_wegistews.mpww_dq_func_cntw_2;
	u32 spww_func_cntw      = ni_pi->cwock_wegistews.cg_spww_func_cntw;
	u32 spww_func_cntw_2    = ni_pi->cwock_wegistews.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3    = ni_pi->cwock_wegistews.cg_spww_func_cntw_3;
	u32 spww_func_cntw_4    = ni_pi->cwock_wegistews.cg_spww_func_cntw_4;
	u32 mcwk_pwwmgt_cntw    = ni_pi->cwock_wegistews.mcwk_pwwmgt_cntw;
	u32 dww_cntw            = ni_pi->cwock_wegistews.dww_cntw;
	u32 weg;
	int wet;

	tabwe->ACPIState = tabwe->initiawState;

	tabwe->ACPIState.fwags &= ~PPSMC_SWSTATE_FWAG_DC;

	if (pi->acpi_vddc) {
		wet = ni_popuwate_vowtage_vawue(wdev,
						&eg_pi->vddc_vowtage_tabwe,
						pi->acpi_vddc, &tabwe->ACPIState.wevew.vddc);
		if (!wet) {
			u16 std_vddc;

			wet = ni_get_std_vowtage_vawue(wdev,
						       &tabwe->ACPIState.wevew.vddc, &std_vddc);
			if (!wet)
				ni_popuwate_std_vowtage_vawue(wdev, std_vddc,
							      tabwe->ACPIState.wevew.vddc.index,
							      &tabwe->ACPIState.wevew.std_vddc);
		}

		if (pi->pcie_gen2) {
			if (pi->acpi_pcie_gen2)
				tabwe->ACPIState.wevew.gen2PCIE = 1;
			ewse
				tabwe->ACPIState.wevew.gen2PCIE = 0;
		} ewse {
			tabwe->ACPIState.wevew.gen2PCIE = 0;
		}
	} ewse {
		wet = ni_popuwate_vowtage_vawue(wdev,
						&eg_pi->vddc_vowtage_tabwe,
						pi->min_vddc_in_tabwe,
						&tabwe->ACPIState.wevew.vddc);
		if (!wet) {
			u16 std_vddc;

			wet = ni_get_std_vowtage_vawue(wdev,
						       &tabwe->ACPIState.wevew.vddc,
						       &std_vddc);
			if (!wet)
				ni_popuwate_std_vowtage_vawue(wdev, std_vddc,
							      tabwe->ACPIState.wevew.vddc.index,
							      &tabwe->ACPIState.wevew.std_vddc);
		}
		tabwe->ACPIState.wevew.gen2PCIE = 0;
	}

	if (eg_pi->acpi_vddci) {
		if (eg_pi->vddci_contwow)
			ni_popuwate_vowtage_vawue(wdev,
						  &eg_pi->vddci_vowtage_tabwe,
						  eg_pi->acpi_vddci,
						  &tabwe->ACPIState.wevew.vddci);
	}


	mpww_ad_func_cntw &= ~PDNB;

	mpww_ad_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN;

	if (pi->mem_gddw5)
		mpww_dq_func_cntw &= ~PDNB;
	mpww_dq_func_cntw_2 |= BIAS_GEN_PDNB | WESET_EN | BYPASS;


	mcwk_pwwmgt_cntw |= (MWDCKA0_WESET |
			     MWDCKA1_WESET |
			     MWDCKB0_WESET |
			     MWDCKB1_WESET |
			     MWDCKC0_WESET |
			     MWDCKC1_WESET |
			     MWDCKD0_WESET |
			     MWDCKD1_WESET);

	mcwk_pwwmgt_cntw &= ~(MWDCKA0_PDNB |
			      MWDCKA1_PDNB |
			      MWDCKB0_PDNB |
			      MWDCKB1_PDNB |
			      MWDCKC0_PDNB |
			      MWDCKC1_PDNB |
			      MWDCKD0_PDNB |
			      MWDCKD1_PDNB);

	dww_cntw |= (MWDCKA0_BYPASS |
		     MWDCKA1_BYPASS |
		     MWDCKB0_BYPASS |
		     MWDCKB1_BYPASS |
		     MWDCKC0_BYPASS |
		     MWDCKC1_BYPASS |
		     MWDCKD0_BYPASS |
		     MWDCKD1_BYPASS);

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(4);

	tabwe->ACPIState.wevew.mcwk.vMPWW_AD_FUNC_CNTW = cpu_to_be32(mpww_ad_func_cntw);
	tabwe->ACPIState.wevew.mcwk.vMPWW_AD_FUNC_CNTW_2 = cpu_to_be32(mpww_ad_func_cntw_2);
	tabwe->ACPIState.wevew.mcwk.vMPWW_DQ_FUNC_CNTW = cpu_to_be32(mpww_dq_func_cntw);
	tabwe->ACPIState.wevew.mcwk.vMPWW_DQ_FUNC_CNTW_2 = cpu_to_be32(mpww_dq_func_cntw_2);
	tabwe->ACPIState.wevew.mcwk.vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	tabwe->ACPIState.wevew.mcwk.vDWW_CNTW = cpu_to_be32(dww_cntw);

	tabwe->ACPIState.wevew.mcwk.mcwk_vawue = 0;

	tabwe->ACPIState.wevew.scwk.vCG_SPWW_FUNC_CNTW = cpu_to_be32(spww_func_cntw);
	tabwe->ACPIState.wevew.scwk.vCG_SPWW_FUNC_CNTW_2 = cpu_to_be32(spww_func_cntw_2);
	tabwe->ACPIState.wevew.scwk.vCG_SPWW_FUNC_CNTW_3 = cpu_to_be32(spww_func_cntw_3);
	tabwe->ACPIState.wevew.scwk.vCG_SPWW_FUNC_CNTW_4 = cpu_to_be32(spww_func_cntw_4);

	tabwe->ACPIState.wevew.scwk.scwk_vawue = 0;

	ni_popuwate_mvdd_vawue(wdev, 0, &tabwe->ACPIState.wevew.mvdd);

	if (eg_pi->dynamic_ac_timing)
		tabwe->ACPIState.wevew.ACIndex = 1;

	tabwe->ACPIState.wevew.dpm2.MaxPS = 0;
	tabwe->ACPIState.wevew.dpm2.NeawTDPDec = 0;
	tabwe->ACPIState.wevew.dpm2.AboveSafeInc = 0;
	tabwe->ACPIState.wevew.dpm2.BewowSafeInc = 0;

	weg = MIN_POWEW_MASK | MAX_POWEW_MASK;
	tabwe->ACPIState.wevew.SQPowewThwottwe = cpu_to_be32(weg);

	weg = MAX_POWEW_DEWTA_MASK | STI_SIZE_MASK | WTI_WATIO_MASK;
	tabwe->ACPIState.wevew.SQPowewThwottwe_2 = cpu_to_be32(weg);

	wetuwn 0;
}

static int ni_init_smc_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	int wet;
	stwuct wadeon_ps *wadeon_boot_state = wdev->pm.dpm.boot_ps;
	NISWANDS_SMC_STATETABWE *tabwe = &ni_pi->smc_statetabwe;

	memset(tabwe, 0, sizeof(NISWANDS_SMC_STATETABWE));

	ni_popuwate_smc_vowtage_tabwes(wdev, tabwe);

	switch (wdev->pm.int_thewmaw_type) {
	case THEWMAW_TYPE_NI:
	case THEWMAW_TYPE_EMC2103_WITH_INTEWNAW:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_INTEWNAW;
		bweak;
	case THEWMAW_TYPE_NONE:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_NONE;
		bweak;
	defauwt:
		tabwe->thewmawPwotectType = PPSMC_THEWMAW_PWOTECT_TYPE_EXTEWNAW;
		bweak;
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_HAWDWAWEDC)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GPIO_DC;

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_WEGUWATOW_HOT)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_WEGUWATOW_HOT;

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_STEPVDDC;

	if (pi->mem_gddw5)
		tabwe->systemFwags |= PPSMC_SYSTEMFWAG_GDDW5;

	wet = ni_popuwate_smc_initiaw_state(wdev, wadeon_boot_state, tabwe);
	if (wet)
		wetuwn wet;

	wet = ni_popuwate_smc_acpi_state(wdev, tabwe);
	if (wet)
		wetuwn wet;

	tabwe->dwivewState.fwags = tabwe->initiawState.fwags;
	tabwe->dwivewState.wevewCount = tabwe->initiawState.wevewCount;
	tabwe->dwivewState.wevews[0] = tabwe->initiawState.wevew;

	tabwe->UWVState = tabwe->initiawState;

	wet = ni_do_pwogwam_memowy_timing_pawametews(wdev, wadeon_boot_state,
						     NISWANDS_INITIAW_STATE_AWB_INDEX);
	if (wet)
		wetuwn wet;

	wetuwn wv770_copy_bytes_to_smc(wdev, pi->state_tabwe_stawt, (u8 *)tabwe,
				       sizeof(NISWANDS_SMC_STATETABWE), pi->swam_end);
}

static int ni_cawcuwate_scwk_pawams(stwuct wadeon_device *wdev,
				    u32 engine_cwock,
				    NISWANDS_SMC_SCWK_VAWUE *scwk)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct atom_cwock_dividews dividews;
	u32 spww_func_cntw = ni_pi->cwock_wegistews.cg_spww_func_cntw;
	u32 spww_func_cntw_2 = ni_pi->cwock_wegistews.cg_spww_func_cntw_2;
	u32 spww_func_cntw_3 = ni_pi->cwock_wegistews.cg_spww_func_cntw_3;
	u32 spww_func_cntw_4 = ni_pi->cwock_wegistews.cg_spww_func_cntw_4;
	u32 cg_spww_spwead_spectwum = ni_pi->cwock_wegistews.cg_spww_spwead_spectwum;
	u32 cg_spww_spwead_spectwum_2 = ni_pi->cwock_wegistews.cg_spww_spwead_spectwum_2;
	u64 tmp;
	u32 wefewence_cwock = wdev->cwock.spww.wefewence_fweq;
	u32 wefewence_dividew;
	u32 fbdiv;
	int wet;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     engine_cwock, fawse, &dividews);
	if (wet)
		wetuwn wet;

	wefewence_dividew = 1 + dividews.wef_div;


	tmp = (u64) engine_cwock * wefewence_dividew * dividews.post_div * 16834;
	do_div(tmp, wefewence_cwock);
	fbdiv = (u32) tmp;

	spww_func_cntw &= ~(SPWW_PDIV_A_MASK | SPWW_WEF_DIV_MASK);
	spww_func_cntw |= SPWW_WEF_DIV(dividews.wef_div);
	spww_func_cntw |= SPWW_PDIV_A(dividews.post_div);

	spww_func_cntw_2 &= ~SCWK_MUX_SEW_MASK;
	spww_func_cntw_2 |= SCWK_MUX_SEW(2);

	spww_func_cntw_3 &= ~SPWW_FB_DIV_MASK;
	spww_func_cntw_3 |= SPWW_FB_DIV(fbdiv);
	spww_func_cntw_3 |= SPWW_DITHEN;

	if (pi->scwk_ss) {
		stwuct wadeon_atom_ss ss;
		u32 vco_fweq = engine_cwock * dividews.post_div;

		if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
						     ASIC_INTEWNAW_ENGINE_SS, vco_fweq)) {
			u32 cwk_s = wefewence_cwock * 5 / (wefewence_dividew * ss.wate);
			u32 cwk_v = 4 * ss.pewcentage * fbdiv / (cwk_s * 10000);

			cg_spww_spwead_spectwum &= ~CWK_S_MASK;
			cg_spww_spwead_spectwum |= CWK_S(cwk_s);
			cg_spww_spwead_spectwum |= SSEN;

			cg_spww_spwead_spectwum_2 &= ~CWK_V_MASK;
			cg_spww_spwead_spectwum_2 |= CWK_V(cwk_v);
		}
	}

	scwk->scwk_vawue = engine_cwock;
	scwk->vCG_SPWW_FUNC_CNTW = spww_func_cntw;
	scwk->vCG_SPWW_FUNC_CNTW_2 = spww_func_cntw_2;
	scwk->vCG_SPWW_FUNC_CNTW_3 = spww_func_cntw_3;
	scwk->vCG_SPWW_FUNC_CNTW_4 = spww_func_cntw_4;
	scwk->vCG_SPWW_SPWEAD_SPECTWUM = cg_spww_spwead_spectwum;
	scwk->vCG_SPWW_SPWEAD_SPECTWUM_2 = cg_spww_spwead_spectwum_2;

	wetuwn 0;
}

static int ni_popuwate_scwk_vawue(stwuct wadeon_device *wdev,
				  u32 engine_cwock,
				  NISWANDS_SMC_SCWK_VAWUE *scwk)
{
	NISWANDS_SMC_SCWK_VAWUE scwk_tmp;
	int wet;

	wet = ni_cawcuwate_scwk_pawams(wdev, engine_cwock, &scwk_tmp);
	if (!wet) {
		scwk->scwk_vawue = cpu_to_be32(scwk_tmp.scwk_vawue);
		scwk->vCG_SPWW_FUNC_CNTW = cpu_to_be32(scwk_tmp.vCG_SPWW_FUNC_CNTW);
		scwk->vCG_SPWW_FUNC_CNTW_2 = cpu_to_be32(scwk_tmp.vCG_SPWW_FUNC_CNTW_2);
		scwk->vCG_SPWW_FUNC_CNTW_3 = cpu_to_be32(scwk_tmp.vCG_SPWW_FUNC_CNTW_3);
		scwk->vCG_SPWW_FUNC_CNTW_4 = cpu_to_be32(scwk_tmp.vCG_SPWW_FUNC_CNTW_4);
		scwk->vCG_SPWW_SPWEAD_SPECTWUM = cpu_to_be32(scwk_tmp.vCG_SPWW_SPWEAD_SPECTWUM);
		scwk->vCG_SPWW_SPWEAD_SPECTWUM_2 = cpu_to_be32(scwk_tmp.vCG_SPWW_SPWEAD_SPECTWUM_2);
	}

	wetuwn wet;
}

static int ni_init_smc_spww_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	SMC_NISWANDS_SPWW_DIV_TABWE *spww_tabwe;
	NISWANDS_SMC_SCWK_VAWUE scwk_pawams;
	u32 fb_div;
	u32 p_div;
	u32 cwk_s;
	u32 cwk_v;
	u32 scwk = 0;
	int i, wet;
	u32 tmp;

	if (ni_pi->spww_tabwe_stawt == 0)
		wetuwn -EINVAW;

	spww_tabwe = kzawwoc(sizeof(SMC_NISWANDS_SPWW_DIV_TABWE), GFP_KEWNEW);
	if (spww_tabwe == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < 256; i++) {
		wet = ni_cawcuwate_scwk_pawams(wdev, scwk, &scwk_pawams);
		if (wet)
			bweak;

		p_div = (scwk_pawams.vCG_SPWW_FUNC_CNTW & SPWW_PDIV_A_MASK) >> SPWW_PDIV_A_SHIFT;
		fb_div = (scwk_pawams.vCG_SPWW_FUNC_CNTW_3 & SPWW_FB_DIV_MASK) >> SPWW_FB_DIV_SHIFT;
		cwk_s = (scwk_pawams.vCG_SPWW_SPWEAD_SPECTWUM & CWK_S_MASK) >> CWK_S_SHIFT;
		cwk_v = (scwk_pawams.vCG_SPWW_SPWEAD_SPECTWUM_2 & CWK_V_MASK) >> CWK_V_SHIFT;

		fb_div &= ~0x00001FFF;
		fb_div >>= 1;
		cwk_v >>= 6;

		if (p_div & ~(SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_MASK >> SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_SHIFT))
			wet = -EINVAW;

		if (cwk_s & ~(SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_MASK >> SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_SHIFT))
			wet = -EINVAW;

		if (fb_div & ~(SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_MASK >> SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_SHIFT))
			wet = -EINVAW;

		if (cwk_v & ~(SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_MASK >> SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_SHIFT))
			wet = -EINVAW;

		if (wet)
			bweak;

		tmp = ((fb_div << SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_SHIFT) & SMC_NISWANDS_SPWW_DIV_TABWE_FBDIV_MASK) |
			((p_div << SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_SHIFT) & SMC_NISWANDS_SPWW_DIV_TABWE_PDIV_MASK);
		spww_tabwe->fweq[i] = cpu_to_be32(tmp);

		tmp = ((cwk_v << SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_SHIFT) & SMC_NISWANDS_SPWW_DIV_TABWE_CWKV_MASK) |
			((cwk_s << SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_SHIFT) & SMC_NISWANDS_SPWW_DIV_TABWE_CWKS_MASK);
		spww_tabwe->ss[i] = cpu_to_be32(tmp);

		scwk += 512;
	}

	if (!wet)
		wet = wv770_copy_bytes_to_smc(wdev, ni_pi->spww_tabwe_stawt, (u8 *)spww_tabwe,
					      sizeof(SMC_NISWANDS_SPWW_DIV_TABWE), pi->swam_end);

	kfwee(spww_tabwe);

	wetuwn wet;
}

static int ni_popuwate_mcwk_vawue(stwuct wadeon_device *wdev,
				  u32 engine_cwock,
				  u32 memowy_cwock,
				  NISWANDS_SMC_MCWK_VAWUE *mcwk,
				  boow stwobe_mode,
				  boow dww_state_on)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 mpww_ad_func_cntw = ni_pi->cwock_wegistews.mpww_ad_func_cntw;
	u32 mpww_ad_func_cntw_2 = ni_pi->cwock_wegistews.mpww_ad_func_cntw_2;
	u32 mpww_dq_func_cntw = ni_pi->cwock_wegistews.mpww_dq_func_cntw;
	u32 mpww_dq_func_cntw_2 = ni_pi->cwock_wegistews.mpww_dq_func_cntw_2;
	u32 mcwk_pwwmgt_cntw = ni_pi->cwock_wegistews.mcwk_pwwmgt_cntw;
	u32 dww_cntw = ni_pi->cwock_wegistews.dww_cntw;
	u32 mpww_ss1 = ni_pi->cwock_wegistews.mpww_ss1;
	u32 mpww_ss2 = ni_pi->cwock_wegistews.mpww_ss2;
	stwuct atom_cwock_dividews dividews;
	u32 ibias;
	u32 dww_speed;
	int wet;
	u32 mc_seq_misc7;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_MEMOWY_PWW_PAWAM,
					     memowy_cwock, stwobe_mode, &dividews);
	if (wet)
		wetuwn wet;

	if (!stwobe_mode) {
		mc_seq_misc7 = WWEG32(MC_SEQ_MISC7);

		if (mc_seq_misc7 & 0x8000000)
			dividews.post_div = 1;
	}

	ibias = cypwess_map_cwkf_to_ibias(wdev, dividews.whowe_fb_div);

	mpww_ad_func_cntw &= ~(CWKW_MASK |
			       YCWK_POST_DIV_MASK |
			       CWKF_MASK |
			       CWKFWAC_MASK |
			       IBIAS_MASK);
	mpww_ad_func_cntw |= CWKW(dividews.wef_div);
	mpww_ad_func_cntw |= YCWK_POST_DIV(dividews.post_div);
	mpww_ad_func_cntw |= CWKF(dividews.whowe_fb_div);
	mpww_ad_func_cntw |= CWKFWAC(dividews.fwac_fb_div);
	mpww_ad_func_cntw |= IBIAS(ibias);

	if (dividews.vco_mode)
		mpww_ad_func_cntw_2 |= VCO_MODE;
	ewse
		mpww_ad_func_cntw_2 &= ~VCO_MODE;

	if (pi->mem_gddw5) {
		mpww_dq_func_cntw &= ~(CWKW_MASK |
				       YCWK_POST_DIV_MASK |
				       CWKF_MASK |
				       CWKFWAC_MASK |
				       IBIAS_MASK);
		mpww_dq_func_cntw |= CWKW(dividews.wef_div);
		mpww_dq_func_cntw |= YCWK_POST_DIV(dividews.post_div);
		mpww_dq_func_cntw |= CWKF(dividews.whowe_fb_div);
		mpww_dq_func_cntw |= CWKFWAC(dividews.fwac_fb_div);
		mpww_dq_func_cntw |= IBIAS(ibias);

		if (stwobe_mode)
			mpww_dq_func_cntw &= ~PDNB;
		ewse
			mpww_dq_func_cntw |= PDNB;

		if (dividews.vco_mode)
			mpww_dq_func_cntw_2 |= VCO_MODE;
		ewse
			mpww_dq_func_cntw_2 &= ~VCO_MODE;
	}

	if (pi->mcwk_ss) {
		stwuct wadeon_atom_ss ss;
		u32 vco_fweq = memowy_cwock * dividews.post_div;

		if (wadeon_atombios_get_asic_ss_info(wdev, &ss,
						     ASIC_INTEWNAW_MEMOWY_SS, vco_fweq)) {
			u32 wefewence_cwock = wdev->cwock.mpww.wefewence_fweq;
			u32 decoded_wef = wv740_get_decoded_wefewence_dividew(dividews.wef_div);
			u32 cwk_s, cwk_v;

			if (!decoded_wef)
				wetuwn -EINVAW;
			cwk_s = wefewence_cwock * 5 / (decoded_wef * ss.wate);
			cwk_v = ss.pewcentage *
				(0x4000 * dividews.whowe_fb_div + 0x800 * dividews.fwac_fb_div) / (cwk_s * 625);

			mpww_ss1 &= ~CWKV_MASK;
			mpww_ss1 |= CWKV(cwk_v);

			mpww_ss2 &= ~CWKS_MASK;
			mpww_ss2 |= CWKS(cwk_s);
		}
	}

	dww_speed = wv740_get_dww_speed(pi->mem_gddw5,
					memowy_cwock);

	mcwk_pwwmgt_cntw &= ~DWW_SPEED_MASK;
	mcwk_pwwmgt_cntw |= DWW_SPEED(dww_speed);
	if (dww_state_on)
		mcwk_pwwmgt_cntw |= (MWDCKA0_PDNB |
				     MWDCKA1_PDNB |
				     MWDCKB0_PDNB |
				     MWDCKB1_PDNB |
				     MWDCKC0_PDNB |
				     MWDCKC1_PDNB |
				     MWDCKD0_PDNB |
				     MWDCKD1_PDNB);
	ewse
		mcwk_pwwmgt_cntw &= ~(MWDCKA0_PDNB |
				      MWDCKA1_PDNB |
				      MWDCKB0_PDNB |
				      MWDCKB1_PDNB |
				      MWDCKC0_PDNB |
				      MWDCKC1_PDNB |
				      MWDCKD0_PDNB |
				      MWDCKD1_PDNB);


	mcwk->mcwk_vawue = cpu_to_be32(memowy_cwock);
	mcwk->vMPWW_AD_FUNC_CNTW = cpu_to_be32(mpww_ad_func_cntw);
	mcwk->vMPWW_AD_FUNC_CNTW_2 = cpu_to_be32(mpww_ad_func_cntw_2);
	mcwk->vMPWW_DQ_FUNC_CNTW = cpu_to_be32(mpww_dq_func_cntw);
	mcwk->vMPWW_DQ_FUNC_CNTW_2 = cpu_to_be32(mpww_dq_func_cntw_2);
	mcwk->vMCWK_PWWMGT_CNTW = cpu_to_be32(mcwk_pwwmgt_cntw);
	mcwk->vDWW_CNTW = cpu_to_be32(dww_cntw);
	mcwk->vMPWW_SS = cpu_to_be32(mpww_ss1);
	mcwk->vMPWW_SS2 = cpu_to_be32(mpww_ss2);

	wetuwn 0;
}

static void ni_popuwate_smc_sp(stwuct wadeon_device *wdev,
			       stwuct wadeon_ps *wadeon_state,
			       NISWANDS_SMC_SWSTATE *smc_state)
{
	stwuct ni_ps *ps = ni_get_ps(wadeon_state);
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	int i;

	fow (i = 0; i < ps->pewfowmance_wevew_count - 1; i++)
		smc_state->wevews[i].bSP = cpu_to_be32(pi->dsp);

	smc_state->wevews[ps->pewfowmance_wevew_count - 1].bSP =
		cpu_to_be32(pi->psp);
}

static int ni_convewt_powew_wevew_to_smc(stwuct wadeon_device *wdev,
					 stwuct wv7xx_pw *pw,
					 NISWANDS_SMC_HW_PEWFOWMANCE_WEVEW *wevew)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	int wet;
	boow dww_state_on;
	u16 std_vddc;
	u32 tmp = WWEG32(DC_STUTTEW_CNTW);

	wevew->gen2PCIE = pi->pcie_gen2 ?
		((pw->fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2) ? 1 : 0) : 0;

	wet = ni_popuwate_scwk_vawue(wdev, pw->scwk, &wevew->scwk);
	if (wet)
		wetuwn wet;

	wevew->mcFwags =  0;
	if (pi->mcwk_stuttew_mode_thweshowd &&
	    (pw->mcwk <= pi->mcwk_stuttew_mode_thweshowd) &&
	    !eg_pi->uvd_enabwed &&
	    (tmp & DC_STUTTEW_ENABWE_A) &&
	    (tmp & DC_STUTTEW_ENABWE_B))
		wevew->mcFwags |= NISWANDS_SMC_MC_STUTTEW_EN;

	if (pi->mem_gddw5) {
		if (pw->mcwk > pi->mcwk_edc_enabwe_thweshowd)
			wevew->mcFwags |= NISWANDS_SMC_MC_EDC_WD_FWAG;
		if (pw->mcwk > eg_pi->mcwk_edc_ww_enabwe_thweshowd)
			wevew->mcFwags |= NISWANDS_SMC_MC_EDC_WW_FWAG;

		wevew->stwobeMode = cypwess_get_stwobe_mode_settings(wdev, pw->mcwk);

		if (wevew->stwobeMode & NISWANDS_SMC_STWOBE_ENABWE) {
			if (cypwess_get_mcwk_fwequency_watio(wdev, pw->mcwk, twue) >=
			    ((WWEG32(MC_SEQ_MISC7) >> 16) & 0xf))
				dww_state_on = ((WWEG32(MC_SEQ_MISC5) >> 1) & 0x1) ? twue : fawse;
			ewse
				dww_state_on = ((WWEG32(MC_SEQ_MISC6) >> 1) & 0x1) ? twue : fawse;
		} ewse {
			dww_state_on = fawse;
			if (pw->mcwk > ni_pi->mcwk_wtt_mode_thweshowd)
				wevew->mcFwags |= NISWANDS_SMC_MC_WTT_ENABWE;
		}

		wet = ni_popuwate_mcwk_vawue(wdev, pw->scwk, pw->mcwk,
					     &wevew->mcwk,
					     (wevew->stwobeMode & NISWANDS_SMC_STWOBE_ENABWE) != 0,
					     dww_state_on);
	} ewse
		wet = ni_popuwate_mcwk_vawue(wdev, pw->scwk, pw->mcwk, &wevew->mcwk, 1, 1);

	if (wet)
		wetuwn wet;

	wet = ni_popuwate_vowtage_vawue(wdev, &eg_pi->vddc_vowtage_tabwe,
					pw->vddc, &wevew->vddc);
	if (wet)
		wetuwn wet;

	wet = ni_get_std_vowtage_vawue(wdev, &wevew->vddc, &std_vddc);
	if (wet)
		wetuwn wet;

	ni_popuwate_std_vowtage_vawue(wdev, std_vddc,
				      wevew->vddc.index, &wevew->std_vddc);

	if (eg_pi->vddci_contwow) {
		wet = ni_popuwate_vowtage_vawue(wdev, &eg_pi->vddci_vowtage_tabwe,
						pw->vddci, &wevew->vddci);
		if (wet)
			wetuwn wet;
	}

	ni_popuwate_mvdd_vawue(wdev, pw->mcwk, &wevew->mvdd);

	wetuwn wet;
}

static int ni_popuwate_smc_t(stwuct wadeon_device *wdev,
			     stwuct wadeon_ps *wadeon_state,
			     NISWANDS_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	u32 a_t;
	u32 t_w, t_h;
	u32 high_bsp;
	int i, wet;

	if (state->pewfowmance_wevew_count >= 9)
		wetuwn -EINVAW;

	if (state->pewfowmance_wevew_count < 2) {
		a_t = CG_W(0xffff) | CG_W(0);
		smc_state->wevews[0].aT = cpu_to_be32(a_t);
		wetuwn 0;
	}

	smc_state->wevews[0].aT = cpu_to_be32(0);

	fow (i = 0; i <= state->pewfowmance_wevew_count - 2; i++) {
		if (eg_pi->uvd_enabwed)
			wet = w600_cawcuwate_at(
				1000 * (i * (eg_pi->smu_uvd_hs ? 2 : 8) + 2),
				100 * W600_AH_DFWT,
				state->pewfowmance_wevews[i + 1].scwk,
				state->pewfowmance_wevews[i].scwk,
				&t_w,
				&t_h);
		ewse
			wet = w600_cawcuwate_at(
				1000 * (i + 1),
				100 * W600_AH_DFWT,
				state->pewfowmance_wevews[i + 1].scwk,
				state->pewfowmance_wevews[i].scwk,
				&t_w,
				&t_h);

		if (wet) {
			t_h = (i + 1) * 1000 - 50 * W600_AH_DFWT;
			t_w = (i + 1) * 1000 + 50 * W600_AH_DFWT;
		}

		a_t = be32_to_cpu(smc_state->wevews[i].aT) & ~CG_W_MASK;
		a_t |= CG_W(t_w * pi->bsp / 20000);
		smc_state->wevews[i].aT = cpu_to_be32(a_t);

		high_bsp = (i == state->pewfowmance_wevew_count - 2) ?
			pi->pbsp : pi->bsp;

		a_t = CG_W(0xffff) | CG_W(t_h * high_bsp / 20000);
		smc_state->wevews[i + 1].aT = cpu_to_be32(a_t);
	}

	wetuwn 0;
}

static int ni_popuwate_powew_containment_vawues(stwuct wadeon_device *wdev,
						stwuct wadeon_ps *wadeon_state,
						NISWANDS_SMC_SWSTATE *smc_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	u32 pwev_scwk;
	u32 max_scwk;
	u32 min_scwk;
	int i, wet;
	u32 tdp_wimit;
	u32 neaw_tdp_wimit;
	u32 powew_boost_wimit;
	u8 max_ps_pewcent;

	if (ni_pi->enabwe_powew_containment == fawse)
		wetuwn 0;

	if (state->pewfowmance_wevew_count == 0)
		wetuwn -EINVAW;

	if (smc_state->wevewCount != state->pewfowmance_wevew_count)
		wetuwn -EINVAW;

	wet = ni_cawcuwate_adjusted_tdp_wimits(wdev,
					       fawse, /* ??? */
					       wdev->pm.dpm.tdp_adjustment,
					       &tdp_wimit,
					       &neaw_tdp_wimit);
	if (wet)
		wetuwn wet;

	powew_boost_wimit = ni_cawcuwate_powew_boost_wimit(wdev, wadeon_state, neaw_tdp_wimit);

	wet = wv770_wwite_smc_swam_dwowd(wdev,
					 pi->state_tabwe_stawt +
					 offsetof(NISWANDS_SMC_STATETABWE, dpm2Pawams) +
					 offsetof(PP_NIswands_DPM2Pawametews, PowewBoostWimit),
					 ni_scawe_powew_fow_smc(powew_boost_wimit, ni_get_smc_powew_scawing_factow(wdev)),
					 pi->swam_end);
	if (wet)
		powew_boost_wimit = 0;

	smc_state->wevews[0].dpm2.MaxPS = 0;
	smc_state->wevews[0].dpm2.NeawTDPDec = 0;
	smc_state->wevews[0].dpm2.AboveSafeInc = 0;
	smc_state->wevews[0].dpm2.BewowSafeInc = 0;
	smc_state->wevews[0].stateFwags |= powew_boost_wimit ? PPSMC_STATEFWAG_POWEWBOOST : 0;

	fow (i = 1; i < state->pewfowmance_wevew_count; i++) {
		pwev_scwk = state->pewfowmance_wevews[i-1].scwk;
		max_scwk  = state->pewfowmance_wevews[i].scwk;
		max_ps_pewcent = (i != (state->pewfowmance_wevew_count - 1)) ?
			NISWANDS_DPM2_MAXPS_PEWCENT_M : NISWANDS_DPM2_MAXPS_PEWCENT_H;

		if (max_scwk < pwev_scwk)
			wetuwn -EINVAW;

		if ((max_ps_pewcent == 0) || (pwev_scwk == max_scwk) || eg_pi->uvd_enabwed)
			min_scwk = max_scwk;
		ewse if (1 == i)
			min_scwk = pwev_scwk;
		ewse
			min_scwk = (pwev_scwk * (u32)max_ps_pewcent) / 100;

		if (min_scwk < state->pewfowmance_wevews[0].scwk)
			min_scwk = state->pewfowmance_wevews[0].scwk;

		if (min_scwk == 0)
			wetuwn -EINVAW;

		smc_state->wevews[i].dpm2.MaxPS =
			(u8)((NISWANDS_DPM2_MAX_PUWSE_SKIP * (max_scwk - min_scwk)) / max_scwk);
		smc_state->wevews[i].dpm2.NeawTDPDec = NISWANDS_DPM2_NEAW_TDP_DEC;
		smc_state->wevews[i].dpm2.AboveSafeInc = NISWANDS_DPM2_ABOVE_SAFE_INC;
		smc_state->wevews[i].dpm2.BewowSafeInc = NISWANDS_DPM2_BEWOW_SAFE_INC;
		smc_state->wevews[i].stateFwags |=
			((i != (state->pewfowmance_wevew_count - 1)) && powew_boost_wimit) ?
			PPSMC_STATEFWAG_POWEWBOOST : 0;
	}

	wetuwn 0;
}

static int ni_popuwate_sq_wamping_vawues(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wadeon_state,
					 NISWANDS_SMC_SWSTATE *smc_state)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	u32 sq_powew_thwottwe;
	u32 sq_powew_thwottwe2;
	boow enabwe_sq_wamping = ni_pi->enabwe_sq_wamping;
	int i;

	if (state->pewfowmance_wevew_count == 0)
		wetuwn -EINVAW;

	if (smc_state->wevewCount != state->pewfowmance_wevew_count)
		wetuwn -EINVAW;

	if (wdev->pm.dpm.sq_wamping_thweshowd == 0)
		wetuwn -EINVAW;

	if (NISWANDS_DPM2_SQ_WAMP_MAX_POWEW > (MAX_POWEW_MASK >> MAX_POWEW_SHIFT))
		enabwe_sq_wamping = fawse;

	if (NISWANDS_DPM2_SQ_WAMP_MIN_POWEW > (MIN_POWEW_MASK >> MIN_POWEW_SHIFT))
		enabwe_sq_wamping = fawse;

	if (NISWANDS_DPM2_SQ_WAMP_MAX_POWEW_DEWTA > (MAX_POWEW_DEWTA_MASK >> MAX_POWEW_DEWTA_SHIFT))
		enabwe_sq_wamping = fawse;

	if (NISWANDS_DPM2_SQ_WAMP_STI_SIZE > (STI_SIZE_MASK >> STI_SIZE_SHIFT))
		enabwe_sq_wamping = fawse;

	if (NISWANDS_DPM2_SQ_WAMP_WTI_WATIO > (WTI_WATIO_MASK >> WTI_WATIO_SHIFT))
		enabwe_sq_wamping = fawse;

	fow (i = 0; i < state->pewfowmance_wevew_count; i++) {
		sq_powew_thwottwe  = 0;
		sq_powew_thwottwe2 = 0;

		if ((state->pewfowmance_wevews[i].scwk >= wdev->pm.dpm.sq_wamping_thweshowd) &&
		    enabwe_sq_wamping) {
			sq_powew_thwottwe |= MAX_POWEW(NISWANDS_DPM2_SQ_WAMP_MAX_POWEW);
			sq_powew_thwottwe |= MIN_POWEW(NISWANDS_DPM2_SQ_WAMP_MIN_POWEW);
			sq_powew_thwottwe2 |= MAX_POWEW_DEWTA(NISWANDS_DPM2_SQ_WAMP_MAX_POWEW_DEWTA);
			sq_powew_thwottwe2 |= STI_SIZE(NISWANDS_DPM2_SQ_WAMP_STI_SIZE);
			sq_powew_thwottwe2 |= WTI_WATIO(NISWANDS_DPM2_SQ_WAMP_WTI_WATIO);
		} ewse {
			sq_powew_thwottwe |= MAX_POWEW_MASK | MIN_POWEW_MASK;
			sq_powew_thwottwe2 |= MAX_POWEW_DEWTA_MASK | STI_SIZE_MASK | WTI_WATIO_MASK;
		}

		smc_state->wevews[i].SQPowewThwottwe   = cpu_to_be32(sq_powew_thwottwe);
		smc_state->wevews[i].SQPowewThwottwe_2 = cpu_to_be32(sq_powew_thwottwe2);
	}

	wetuwn 0;
}

static int ni_enabwe_powew_containment(stwuct wadeon_device *wdev,
				       stwuct wadeon_ps *wadeon_new_state,
				       boow enabwe)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	PPSMC_Wesuwt smc_wesuwt;
	int wet = 0;

	if (ni_pi->enabwe_powew_containment) {
		if (enabwe) {
			if (!w600_is_uvd_state(wadeon_new_state->cwass, wadeon_new_state->cwass2)) {
				smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_TDPCwampingActive);
				if (smc_wesuwt != PPSMC_Wesuwt_OK) {
					wet = -EINVAW;
					ni_pi->pc_enabwed = fawse;
				} ewse {
					ni_pi->pc_enabwed = twue;
				}
			}
		} ewse {
			smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_TDPCwampingInactive);
			if (smc_wesuwt != PPSMC_Wesuwt_OK)
				wet = -EINVAW;
			ni_pi->pc_enabwed = fawse;
		}
	}

	wetuwn wet;
}

static int ni_convewt_powew_state_to_smc(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wadeon_state,
					 NISWANDS_SMC_SWSTATE *smc_state)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	int i, wet;
	u32 thweshowd = state->pewfowmance_wevews[state->pewfowmance_wevew_count - 1].scwk * 100 / 100;

	if (!(wadeon_state->caps & ATOM_PPWIB_DISAWWOW_ON_DC))
		smc_state->fwags |= PPSMC_SWSTATE_FWAG_DC;

	smc_state->wevewCount = 0;

	if (state->pewfowmance_wevew_count > NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE)
		wetuwn -EINVAW;

	fow (i = 0; i < state->pewfowmance_wevew_count; i++) {
		wet = ni_convewt_powew_wevew_to_smc(wdev, &state->pewfowmance_wevews[i],
						    &smc_state->wevews[i]);
		smc_state->wevews[i].awbWefweshState =
			(u8)(NISWANDS_DWIVEW_STATE_AWB_INDEX + i);

		if (wet)
			wetuwn wet;

		if (ni_pi->enabwe_powew_containment)
			smc_state->wevews[i].dispwayWatewmawk =
				(state->pewfowmance_wevews[i].scwk < thweshowd) ?
				PPSMC_DISPWAY_WATEWMAWK_WOW : PPSMC_DISPWAY_WATEWMAWK_HIGH;
		ewse
			smc_state->wevews[i].dispwayWatewmawk = (i < 2) ?
				PPSMC_DISPWAY_WATEWMAWK_WOW : PPSMC_DISPWAY_WATEWMAWK_HIGH;

		if (eg_pi->dynamic_ac_timing)
			smc_state->wevews[i].ACIndex = NISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT + i;
		ewse
			smc_state->wevews[i].ACIndex = 0;

		smc_state->wevewCount++;
	}

	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_watewmawk_thweshowd,
				      cpu_to_be32(thweshowd / 512));

	ni_popuwate_smc_sp(wdev, wadeon_state, smc_state);

	wet = ni_popuwate_powew_containment_vawues(wdev, wadeon_state, smc_state);
	if (wet)
		ni_pi->enabwe_powew_containment = fawse;

	wet = ni_popuwate_sq_wamping_vawues(wdev, wadeon_state, smc_state);
	if (wet)
		ni_pi->enabwe_sq_wamping = fawse;

	wetuwn ni_popuwate_smc_t(wdev, wadeon_state, smc_state);
}

static int ni_upwoad_sw_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u16 addwess = pi->state_tabwe_stawt +
		offsetof(NISWANDS_SMC_STATETABWE, dwivewState);
	NISWANDS_SMC_SWSTATE *smc_state;
	size_t state_size = stwuct_size(smc_state, wevews,
			NISWANDS_MAX_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE);
	int wet;

	smc_state = kzawwoc(state_size, GFP_KEWNEW);
	if (smc_state == NUWW)
		wetuwn -ENOMEM;

	wet = ni_convewt_powew_state_to_smc(wdev, wadeon_new_state, smc_state);
	if (wet)
		goto done;

	wet = wv770_copy_bytes_to_smc(wdev, addwess, (u8 *)smc_state, state_size, pi->swam_end);

done:
	kfwee(smc_state);

	wetuwn wet;
}

static int ni_set_mc_speciaw_wegistews(stwuct wadeon_device *wdev,
				       stwuct ni_mc_weg_tabwe *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 i, j, k;
	u32 temp_weg;

	fow (i = 0, j = tabwe->wast; i < tabwe->wast; i++) {
		switch (tabwe->mc_weg_addwess[i].s1) {
		case MC_SEQ_MISC1 >> 2:
			if (j >= SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;
			temp_weg = WWEG32(MC_PMG_CMD_EMWS);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_EMWS >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_EMWS_WP >> 2;
			fow (k = 0; k < tabwe->num_entwies; k++)
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					((temp_weg & 0xffff0000)) |
					((tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16);
			j++;
			if (j >= SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;

			temp_weg = WWEG32(MC_PMG_CMD_MWS);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_MWS >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_MWS_WP >> 2;
			fow(k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
				if (!pi->mem_gddw5)
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] |= 0x100;
			}
			j++;
			bweak;
		case MC_SEQ_WESEWVE_M >> 2:
			if (j >= SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;
			temp_weg = WWEG32(MC_PMG_CMD_MWS1);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_MWS1 >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_MWS1_WP >> 2;
			fow (k = 0; k < tabwe->num_entwies; k++)
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(temp_weg & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
			j++;
			bweak;
		defauwt:
			bweak;
		}
	}

	tabwe->wast = j;

	wetuwn 0;
}

static boow ni_check_s0_mc_weg_index(u16 in_weg, u16 *out_weg)
{
	boow wesuwt = twue;

	switch (in_weg) {
	case  MC_SEQ_WAS_TIMING >> 2:
		*out_weg = MC_SEQ_WAS_TIMING_WP >> 2;
		bweak;
	case MC_SEQ_CAS_TIMING >> 2:
		*out_weg = MC_SEQ_CAS_TIMING_WP >> 2;
		bweak;
	case MC_SEQ_MISC_TIMING >> 2:
		*out_weg = MC_SEQ_MISC_TIMING_WP >> 2;
		bweak;
	case MC_SEQ_MISC_TIMING2 >> 2:
		*out_weg = MC_SEQ_MISC_TIMING2_WP >> 2;
		bweak;
	case MC_SEQ_WD_CTW_D0 >> 2:
		*out_weg = MC_SEQ_WD_CTW_D0_WP >> 2;
		bweak;
	case MC_SEQ_WD_CTW_D1 >> 2:
		*out_weg = MC_SEQ_WD_CTW_D1_WP >> 2;
		bweak;
	case MC_SEQ_WW_CTW_D0 >> 2:
		*out_weg = MC_SEQ_WW_CTW_D0_WP >> 2;
		bweak;
	case MC_SEQ_WW_CTW_D1 >> 2:
		*out_weg = MC_SEQ_WW_CTW_D1_WP >> 2;
		bweak;
	case MC_PMG_CMD_EMWS >> 2:
		*out_weg = MC_SEQ_PMG_CMD_EMWS_WP >> 2;
		bweak;
	case MC_PMG_CMD_MWS >> 2:
		*out_weg = MC_SEQ_PMG_CMD_MWS_WP >> 2;
		bweak;
	case MC_PMG_CMD_MWS1 >> 2:
		*out_weg = MC_SEQ_PMG_CMD_MWS1_WP >> 2;
		bweak;
	case MC_SEQ_PMG_TIMING >> 2:
		*out_weg = MC_SEQ_PMG_TIMING_WP >> 2;
		bweak;
	case MC_PMG_CMD_MWS2 >> 2:
		*out_weg = MC_SEQ_PMG_CMD_MWS2_WP >> 2;
		bweak;
	defauwt:
		wesuwt = fawse;
		bweak;
	}

	wetuwn wesuwt;
}

static void ni_set_vawid_fwag(stwuct ni_mc_weg_tabwe *tabwe)
{
	u8 i, j;

	fow (i = 0; i < tabwe->wast; i++) {
		fow (j = 1; j < tabwe->num_entwies; j++) {
			if (tabwe->mc_weg_tabwe_entwy[j-1].mc_data[i] != tabwe->mc_weg_tabwe_entwy[j].mc_data[i]) {
				tabwe->vawid_fwag |= 1 << i;
				bweak;
			}
		}
	}
}

static void ni_set_s0_mc_weg_index(stwuct ni_mc_weg_tabwe *tabwe)
{
	u32 i;
	u16 addwess;

	fow (i = 0; i < tabwe->wast; i++)
		tabwe->mc_weg_addwess[i].s0 =
			ni_check_s0_mc_weg_index(tabwe->mc_weg_addwess[i].s1, &addwess) ?
			addwess : tabwe->mc_weg_addwess[i].s1;
}

static int ni_copy_vbios_mc_weg_tabwe(stwuct atom_mc_weg_tabwe *tabwe,
				      stwuct ni_mc_weg_tabwe *ni_tabwe)
{
	u8 i, j;

	if (tabwe->wast > SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE)
		wetuwn -EINVAW;
	if (tabwe->num_entwies > MAX_AC_TIMING_ENTWIES)
		wetuwn -EINVAW;

	fow (i = 0; i < tabwe->wast; i++)
		ni_tabwe->mc_weg_addwess[i].s1 = tabwe->mc_weg_addwess[i].s1;
	ni_tabwe->wast = tabwe->wast;

	fow (i = 0; i < tabwe->num_entwies; i++) {
		ni_tabwe->mc_weg_tabwe_entwy[i].mcwk_max =
			tabwe->mc_weg_tabwe_entwy[i].mcwk_max;
		fow (j = 0; j < tabwe->wast; j++)
			ni_tabwe->mc_weg_tabwe_entwy[i].mc_data[j] =
				tabwe->mc_weg_tabwe_entwy[i].mc_data[j];
	}
	ni_tabwe->num_entwies = tabwe->num_entwies;

	wetuwn 0;
}

static int ni_initiawize_mc_weg_tabwe(stwuct wadeon_device *wdev)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	int wet;
	stwuct atom_mc_weg_tabwe *tabwe;
	stwuct ni_mc_weg_tabwe *ni_tabwe = &ni_pi->mc_weg_tabwe;
	u8 moduwe_index = wv770_get_memowy_moduwe_index(wdev);

	tabwe = kzawwoc(sizeof(stwuct atom_mc_weg_tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	WWEG32(MC_SEQ_WAS_TIMING_WP, WWEG32(MC_SEQ_WAS_TIMING));
	WWEG32(MC_SEQ_CAS_TIMING_WP, WWEG32(MC_SEQ_CAS_TIMING));
	WWEG32(MC_SEQ_MISC_TIMING_WP, WWEG32(MC_SEQ_MISC_TIMING));
	WWEG32(MC_SEQ_MISC_TIMING2_WP, WWEG32(MC_SEQ_MISC_TIMING2));
	WWEG32(MC_SEQ_PMG_CMD_EMWS_WP, WWEG32(MC_PMG_CMD_EMWS));
	WWEG32(MC_SEQ_PMG_CMD_MWS_WP, WWEG32(MC_PMG_CMD_MWS));
	WWEG32(MC_SEQ_PMG_CMD_MWS1_WP, WWEG32(MC_PMG_CMD_MWS1));
	WWEG32(MC_SEQ_WW_CTW_D0_WP, WWEG32(MC_SEQ_WW_CTW_D0));
	WWEG32(MC_SEQ_WW_CTW_D1_WP, WWEG32(MC_SEQ_WW_CTW_D1));
	WWEG32(MC_SEQ_WD_CTW_D0_WP, WWEG32(MC_SEQ_WD_CTW_D0));
	WWEG32(MC_SEQ_WD_CTW_D1_WP, WWEG32(MC_SEQ_WD_CTW_D1));
	WWEG32(MC_SEQ_PMG_TIMING_WP, WWEG32(MC_SEQ_PMG_TIMING));
	WWEG32(MC_SEQ_PMG_CMD_MWS2_WP, WWEG32(MC_PMG_CMD_MWS2));

	wet = wadeon_atom_init_mc_weg_tabwe(wdev, moduwe_index, tabwe);

	if (wet)
		goto init_mc_done;

	wet = ni_copy_vbios_mc_weg_tabwe(tabwe, ni_tabwe);

	if (wet)
		goto init_mc_done;

	ni_set_s0_mc_weg_index(ni_tabwe);

	wet = ni_set_mc_speciaw_wegistews(wdev, ni_tabwe);

	if (wet)
		goto init_mc_done;

	ni_set_vawid_fwag(ni_tabwe);

init_mc_done:
	kfwee(tabwe);

	wetuwn wet;
}

static void ni_popuwate_mc_weg_addwesses(stwuct wadeon_device *wdev,
					 SMC_NIswands_MCWegistews *mc_weg_tabwe)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 i, j;

	fow (i = 0, j = 0; j < ni_pi->mc_weg_tabwe.wast; j++) {
		if (ni_pi->mc_weg_tabwe.vawid_fwag & (1 << j)) {
			if (i >= SMC_NISWANDS_MC_WEGISTEW_AWWAY_SIZE)
				bweak;
			mc_weg_tabwe->addwess[i].s0 =
				cpu_to_be16(ni_pi->mc_weg_tabwe.mc_weg_addwess[j].s0);
			mc_weg_tabwe->addwess[i].s1 =
				cpu_to_be16(ni_pi->mc_weg_tabwe.mc_weg_addwess[j].s1);
			i++;
		}
	}
	mc_weg_tabwe->wast = (u8)i;
}


static void ni_convewt_mc_wegistews(stwuct ni_mc_weg_entwy *entwy,
				    SMC_NIswands_MCWegistewSet *data,
				    u32 num_entwies, u32 vawid_fwag)
{
	u32 i, j;

	fow (i = 0, j = 0; j < num_entwies; j++) {
		if (vawid_fwag & (1 << j)) {
			data->vawue[i] = cpu_to_be32(entwy->mc_data[j]);
			i++;
		}
	}
}

static void ni_convewt_mc_weg_tabwe_entwy_to_smc(stwuct wadeon_device *wdev,
						 stwuct wv7xx_pw *pw,
						 SMC_NIswands_MCWegistewSet *mc_weg_tabwe_data)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 i = 0;

	fow (i = 0; i < ni_pi->mc_weg_tabwe.num_entwies; i++) {
		if (pw->mcwk <= ni_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i].mcwk_max)
			bweak;
	}

	if ((i == ni_pi->mc_weg_tabwe.num_entwies) && (i > 0))
		--i;

	ni_convewt_mc_wegistews(&ni_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[i],
				mc_weg_tabwe_data,
				ni_pi->mc_weg_tabwe.wast,
				ni_pi->mc_weg_tabwe.vawid_fwag);
}

static void ni_convewt_mc_weg_tabwe_to_smc(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *wadeon_state,
					   SMC_NIswands_MCWegistews *mc_weg_tabwe)
{
	stwuct ni_ps *state = ni_get_ps(wadeon_state);
	int i;

	fow (i = 0; i < state->pewfowmance_wevew_count; i++) {
		ni_convewt_mc_weg_tabwe_entwy_to_smc(wdev,
						     &state->pewfowmance_wevews[i],
						     &mc_weg_tabwe->data[NISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT + i]);
	}
}

static int ni_popuwate_mc_weg_tabwe(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *boot_state = ni_get_ps(wadeon_boot_state);
	SMC_NIswands_MCWegistews *mc_weg_tabwe = &ni_pi->smc_mc_weg_tabwe;

	memset(mc_weg_tabwe, 0, sizeof(SMC_NIswands_MCWegistews));

	wv770_wwite_smc_soft_wegistew(wdev, NI_SMC_SOFT_WEGISTEW_seq_index, 1);

	ni_popuwate_mc_weg_addwesses(wdev, mc_weg_tabwe);

	ni_convewt_mc_weg_tabwe_entwy_to_smc(wdev, &boot_state->pewfowmance_wevews[0],
					     &mc_weg_tabwe->data[0]);

	ni_convewt_mc_wegistews(&ni_pi->mc_weg_tabwe.mc_weg_tabwe_entwy[0],
				&mc_weg_tabwe->data[1],
				ni_pi->mc_weg_tabwe.wast,
				ni_pi->mc_weg_tabwe.vawid_fwag);

	ni_convewt_mc_weg_tabwe_to_smc(wdev, wadeon_boot_state, mc_weg_tabwe);

	wetuwn wv770_copy_bytes_to_smc(wdev, eg_pi->mc_weg_tabwe_stawt,
				       (u8 *)mc_weg_tabwe,
				       sizeof(SMC_NIswands_MCWegistews),
				       pi->swam_end);
}

static int ni_upwoad_mc_weg_tabwe(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct ni_ps *ni_new_state = ni_get_ps(wadeon_new_state);
	SMC_NIswands_MCWegistews *mc_weg_tabwe = &ni_pi->smc_mc_weg_tabwe;
	u16 addwess;

	memset(mc_weg_tabwe, 0, sizeof(SMC_NIswands_MCWegistews));

	ni_convewt_mc_weg_tabwe_to_smc(wdev, wadeon_new_state, mc_weg_tabwe);

	addwess = eg_pi->mc_weg_tabwe_stawt +
		(u16)offsetof(SMC_NIswands_MCWegistews, data[NISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT]);

	wetuwn wv770_copy_bytes_to_smc(wdev, addwess,
				       (u8 *)&mc_weg_tabwe->data[NISWANDS_MCWEGISTEWTABWE_FIWST_DWIVEWSTATE_SWOT],
				       sizeof(SMC_NIswands_MCWegistewSet) * ni_new_state->pewfowmance_wevew_count,
				       pi->swam_end);
}

static int ni_init_dwivew_cawcuwated_weakage_tabwe(stwuct wadeon_device *wdev,
						   PP_NIswands_CACTABWES *cac_tabwes)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u32 weakage = 0;
	unsigned int i, j, tabwe_size;
	s32 t;
	u32 smc_weakage, max_weakage = 0;
	u32 scawing_factow;

	tabwe_size = eg_pi->vddc_vowtage_tabwe.count;

	if (SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES < tabwe_size)
		tabwe_size = SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES;

	scawing_factow = ni_get_smc_powew_scawing_factow(wdev);

	fow (i = 0; i < SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES; i++) {
		fow (j = 0; j < tabwe_size; j++) {
			t = (1000 * ((i + 1) * 8));

			if (t < ni_pi->cac_data.weakage_minimum_tempewatuwe)
				t = ni_pi->cac_data.weakage_minimum_tempewatuwe;

			ni_cawcuwate_weakage_fow_v_and_t(wdev,
							 &ni_pi->cac_data.weakage_coefficients,
							 eg_pi->vddc_vowtage_tabwe.entwies[j].vawue,
							 t,
							 ni_pi->cac_data.i_weakage,
							 &weakage);

			smc_weakage = ni_scawe_powew_fow_smc(weakage, scawing_factow) / 1000;
			if (smc_weakage > max_weakage)
				max_weakage = smc_weakage;

			cac_tabwes->cac_wkge_wut[i][j] = cpu_to_be32(smc_weakage);
		}
	}

	fow (j = tabwe_size; j < SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES; j++) {
		fow (i = 0; i < SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES; i++)
			cac_tabwes->cac_wkge_wut[i][j] = cpu_to_be32(max_weakage);
	}
	wetuwn 0;
}

static int ni_init_simpwified_weakage_tabwe(stwuct wadeon_device *wdev,
					    PP_NIswands_CACTABWES *cac_tabwes)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_cac_weakage_tabwe *weakage_tabwe =
		&wdev->pm.dpm.dyn_state.cac_weakage_tabwe;
	u32 i, j, tabwe_size;
	u32 smc_weakage, max_weakage = 0;
	u32 scawing_factow;

	if (!weakage_tabwe)
		wetuwn -EINVAW;

	tabwe_size = weakage_tabwe->count;

	if (eg_pi->vddc_vowtage_tabwe.count != tabwe_size)
		tabwe_size = (eg_pi->vddc_vowtage_tabwe.count < weakage_tabwe->count) ?
			eg_pi->vddc_vowtage_tabwe.count : weakage_tabwe->count;

	if (SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES < tabwe_size)
		tabwe_size = SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES;

	if (tabwe_size == 0)
		wetuwn -EINVAW;

	scawing_factow = ni_get_smc_powew_scawing_factow(wdev);

	fow (j = 0; j < tabwe_size; j++) {
		smc_weakage = weakage_tabwe->entwies[j].weakage;

		if (smc_weakage > max_weakage)
			max_weakage = smc_weakage;

		fow (i = 0; i < SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES; i++)
			cac_tabwes->cac_wkge_wut[i][j] =
				cpu_to_be32(ni_scawe_powew_fow_smc(smc_weakage, scawing_factow));
	}

	fow (j = tabwe_size; j < SMC_NISWANDS_WKGE_WUT_NUM_OF_VOWT_ENTWIES; j++) {
		fow (i = 0; i < SMC_NISWANDS_WKGE_WUT_NUM_OF_TEMP_ENTWIES; i++)
			cac_tabwes->cac_wkge_wut[i][j] =
				cpu_to_be32(ni_scawe_powew_fow_smc(max_weakage, scawing_factow));
	}
	wetuwn 0;
}

static int ni_initiawize_smc_cac_tabwes(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	PP_NIswands_CACTABWES *cac_tabwes = NUWW;
	int i, wet;
	u32 weg;

	if (ni_pi->enabwe_cac == fawse)
		wetuwn 0;

	cac_tabwes = kzawwoc(sizeof(PP_NIswands_CACTABWES), GFP_KEWNEW);
	if (!cac_tabwes)
		wetuwn -ENOMEM;

	weg = WWEG32(CG_CAC_CTWW) & ~(TID_CNT_MASK | TID_UNIT_MASK);
	weg |= (TID_CNT(ni_pi->cac_weights->tid_cnt) |
		TID_UNIT(ni_pi->cac_weights->tid_unit));
	WWEG32(CG_CAC_CTWW, weg);

	fow (i = 0; i < NISWANDS_DCCAC_MAX_WEVEWS; i++)
		ni_pi->dc_cac_tabwe[i] = ni_pi->cac_weights->dc_cac[i];

	fow (i = 0; i < SMC_NISWANDS_BIF_WUT_NUM_OF_ENTWIES; i++)
		cac_tabwes->cac_bif_wut[i] = ni_pi->cac_weights->pcie_cac[i];

	ni_pi->cac_data.i_weakage = wdev->pm.dpm.cac_weakage;
	ni_pi->cac_data.pww_const = 0;
	ni_pi->cac_data.dc_cac_vawue = ni_pi->dc_cac_tabwe[NISWANDS_DCCAC_WEVEW_0];
	ni_pi->cac_data.bif_cac_vawue = 0;
	ni_pi->cac_data.mc_ww_weight = ni_pi->cac_weights->mc_wwite_weight;
	ni_pi->cac_data.mc_wd_weight = ni_pi->cac_weights->mc_wead_weight;
	ni_pi->cac_data.awwow_ovwfww = 0;
	ni_pi->cac_data.w2num_win_tdp = ni_pi->wta_window_size;
	ni_pi->cac_data.num_win_tdp = 0;
	ni_pi->cac_data.wts_twuncate_n = ni_pi->wts_twuncate;

	if (ni_pi->dwivew_cawcuwate_cac_weakage)
		wet = ni_init_dwivew_cawcuwated_weakage_tabwe(wdev, cac_tabwes);
	ewse
		wet = ni_init_simpwified_weakage_tabwe(wdev, cac_tabwes);

	if (wet)
		goto done_fwee;

	cac_tabwes->pww_const      = cpu_to_be32(ni_pi->cac_data.pww_const);
	cac_tabwes->dc_cacVawue    = cpu_to_be32(ni_pi->cac_data.dc_cac_vawue);
	cac_tabwes->bif_cacVawue   = cpu_to_be32(ni_pi->cac_data.bif_cac_vawue);
	cac_tabwes->AwwowOvwfww    = ni_pi->cac_data.awwow_ovwfww;
	cac_tabwes->MCWwWeight     = ni_pi->cac_data.mc_ww_weight;
	cac_tabwes->MCWdWeight     = ni_pi->cac_data.mc_wd_weight;
	cac_tabwes->numWin_TDP     = ni_pi->cac_data.num_win_tdp;
	cac_tabwes->w2numWin_TDP   = ni_pi->cac_data.w2num_win_tdp;
	cac_tabwes->wts_twuncate_n = ni_pi->cac_data.wts_twuncate_n;

	wet = wv770_copy_bytes_to_smc(wdev, ni_pi->cac_tabwe_stawt, (u8 *)cac_tabwes,
				      sizeof(PP_NIswands_CACTABWES), pi->swam_end);

done_fwee:
	if (wet) {
		ni_pi->enabwe_cac = fawse;
		ni_pi->enabwe_powew_containment = fawse;
	}

	kfwee(cac_tabwes);

	wetuwn 0;
}

static int ni_initiawize_hawdwawe_cac_managew(stwuct wadeon_device *wdev)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	u32 weg;

	if (!ni_pi->enabwe_cac ||
	    !ni_pi->cac_configuwation_wequiwed)
		wetuwn 0;

	if (ni_pi->cac_weights == NUWW)
		wetuwn -EINVAW;

	weg = WWEG32_CG(CG_CAC_WEGION_1_WEIGHT_0) & ~(WEIGHT_TCP_SIG0_MASK |
						      WEIGHT_TCP_SIG1_MASK |
						      WEIGHT_TA_SIG_MASK);
	weg |= (WEIGHT_TCP_SIG0(ni_pi->cac_weights->weight_tcp_sig0) |
		WEIGHT_TCP_SIG1(ni_pi->cac_weights->weight_tcp_sig1) |
		WEIGHT_TA_SIG(ni_pi->cac_weights->weight_ta_sig));
	WWEG32_CG(CG_CAC_WEGION_1_WEIGHT_0, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_1_WEIGHT_1) & ~(WEIGHT_TCC_EN0_MASK |
						      WEIGHT_TCC_EN1_MASK |
						      WEIGHT_TCC_EN2_MASK);
	weg |= (WEIGHT_TCC_EN0(ni_pi->cac_weights->weight_tcc_en0) |
		WEIGHT_TCC_EN1(ni_pi->cac_weights->weight_tcc_en1) |
		WEIGHT_TCC_EN2(ni_pi->cac_weights->weight_tcc_en2));
	WWEG32_CG(CG_CAC_WEGION_1_WEIGHT_1, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_0) & ~(WEIGHT_CB_EN0_MASK |
						      WEIGHT_CB_EN1_MASK |
						      WEIGHT_CB_EN2_MASK |
						      WEIGHT_CB_EN3_MASK);
	weg |= (WEIGHT_CB_EN0(ni_pi->cac_weights->weight_cb_en0) |
		WEIGHT_CB_EN1(ni_pi->cac_weights->weight_cb_en1) |
		WEIGHT_CB_EN2(ni_pi->cac_weights->weight_cb_en2) |
		WEIGHT_CB_EN3(ni_pi->cac_weights->weight_cb_en3));
	WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_0, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_1) & ~(WEIGHT_DB_SIG0_MASK |
						      WEIGHT_DB_SIG1_MASK |
						      WEIGHT_DB_SIG2_MASK |
						      WEIGHT_DB_SIG3_MASK);
	weg |= (WEIGHT_DB_SIG0(ni_pi->cac_weights->weight_db_sig0) |
		WEIGHT_DB_SIG1(ni_pi->cac_weights->weight_db_sig1) |
		WEIGHT_DB_SIG2(ni_pi->cac_weights->weight_db_sig2) |
		WEIGHT_DB_SIG3(ni_pi->cac_weights->weight_db_sig3));
	WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_1, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_2) & ~(WEIGHT_SXM_SIG0_MASK |
						      WEIGHT_SXM_SIG1_MASK |
						      WEIGHT_SXM_SIG2_MASK |
						      WEIGHT_SXS_SIG0_MASK |
						      WEIGHT_SXS_SIG1_MASK);
	weg |= (WEIGHT_SXM_SIG0(ni_pi->cac_weights->weight_sxm_sig0) |
		WEIGHT_SXM_SIG1(ni_pi->cac_weights->weight_sxm_sig1) |
		WEIGHT_SXM_SIG2(ni_pi->cac_weights->weight_sxm_sig2) |
		WEIGHT_SXS_SIG0(ni_pi->cac_weights->weight_sxs_sig0) |
		WEIGHT_SXS_SIG1(ni_pi->cac_weights->weight_sxs_sig1));
	WWEG32_CG(CG_CAC_WEGION_2_WEIGHT_2, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_3_WEIGHT_0) & ~(WEIGHT_XBW_0_MASK |
						      WEIGHT_XBW_1_MASK |
						      WEIGHT_XBW_2_MASK |
						      WEIGHT_SPI_SIG0_MASK);
	weg |= (WEIGHT_XBW_0(ni_pi->cac_weights->weight_xbw_0) |
		WEIGHT_XBW_1(ni_pi->cac_weights->weight_xbw_1) |
		WEIGHT_XBW_2(ni_pi->cac_weights->weight_xbw_2) |
		WEIGHT_SPI_SIG0(ni_pi->cac_weights->weight_spi_sig0));
	WWEG32_CG(CG_CAC_WEGION_3_WEIGHT_0, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_3_WEIGHT_1) & ~(WEIGHT_SPI_SIG1_MASK |
						      WEIGHT_SPI_SIG2_MASK |
						      WEIGHT_SPI_SIG3_MASK |
						      WEIGHT_SPI_SIG4_MASK |
						      WEIGHT_SPI_SIG5_MASK);
	weg |= (WEIGHT_SPI_SIG1(ni_pi->cac_weights->weight_spi_sig1) |
		WEIGHT_SPI_SIG2(ni_pi->cac_weights->weight_spi_sig2) |
		WEIGHT_SPI_SIG3(ni_pi->cac_weights->weight_spi_sig3) |
		WEIGHT_SPI_SIG4(ni_pi->cac_weights->weight_spi_sig4) |
		WEIGHT_SPI_SIG5(ni_pi->cac_weights->weight_spi_sig5));
	WWEG32_CG(CG_CAC_WEGION_3_WEIGHT_1, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_0) & ~(WEIGHT_WDS_SIG0_MASK |
						      WEIGHT_WDS_SIG1_MASK |
						      WEIGHT_SC_MASK);
	weg |= (WEIGHT_WDS_SIG0(ni_pi->cac_weights->weight_wds_sig0) |
		WEIGHT_WDS_SIG1(ni_pi->cac_weights->weight_wds_sig1) |
		WEIGHT_SC(ni_pi->cac_weights->weight_sc));
	WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_0, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_1) & ~(WEIGHT_BIF_MASK |
						      WEIGHT_CP_MASK |
						      WEIGHT_PA_SIG0_MASK |
						      WEIGHT_PA_SIG1_MASK |
						      WEIGHT_VGT_SIG0_MASK);
	weg |= (WEIGHT_BIF(ni_pi->cac_weights->weight_bif) |
		WEIGHT_CP(ni_pi->cac_weights->weight_cp) |
		WEIGHT_PA_SIG0(ni_pi->cac_weights->weight_pa_sig0) |
		WEIGHT_PA_SIG1(ni_pi->cac_weights->weight_pa_sig1) |
		WEIGHT_VGT_SIG0(ni_pi->cac_weights->weight_vgt_sig0));
	WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_1, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_2) & ~(WEIGHT_VGT_SIG1_MASK |
						      WEIGHT_VGT_SIG2_MASK |
						      WEIGHT_DC_SIG0_MASK |
						      WEIGHT_DC_SIG1_MASK |
						      WEIGHT_DC_SIG2_MASK);
	weg |= (WEIGHT_VGT_SIG1(ni_pi->cac_weights->weight_vgt_sig1) |
		WEIGHT_VGT_SIG2(ni_pi->cac_weights->weight_vgt_sig2) |
		WEIGHT_DC_SIG0(ni_pi->cac_weights->weight_dc_sig0) |
		WEIGHT_DC_SIG1(ni_pi->cac_weights->weight_dc_sig1) |
		WEIGHT_DC_SIG2(ni_pi->cac_weights->weight_dc_sig2));
	WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_2, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_3) & ~(WEIGHT_DC_SIG3_MASK |
						      WEIGHT_UVD_SIG0_MASK |
						      WEIGHT_UVD_SIG1_MASK |
						      WEIGHT_SPAWE0_MASK |
						      WEIGHT_SPAWE1_MASK);
	weg |= (WEIGHT_DC_SIG3(ni_pi->cac_weights->weight_dc_sig3) |
		WEIGHT_UVD_SIG0(ni_pi->cac_weights->weight_uvd_sig0) |
		WEIGHT_UVD_SIG1(ni_pi->cac_weights->weight_uvd_sig1) |
		WEIGHT_SPAWE0(ni_pi->cac_weights->weight_spawe0) |
		WEIGHT_SPAWE1(ni_pi->cac_weights->weight_spawe1));
	WWEG32_CG(CG_CAC_WEGION_4_WEIGHT_3, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_5_WEIGHT_0) & ~(WEIGHT_SQ_VSP_MASK |
						      WEIGHT_SQ_VSP0_MASK);
	weg |= (WEIGHT_SQ_VSP(ni_pi->cac_weights->weight_sq_vsp) |
		WEIGHT_SQ_VSP0(ni_pi->cac_weights->weight_sq_vsp0));
	WWEG32_CG(CG_CAC_WEGION_5_WEIGHT_0, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_5_WEIGHT_1) & ~(WEIGHT_SQ_GPW_MASK);
	weg |= WEIGHT_SQ_GPW(ni_pi->cac_weights->weight_sq_gpw);
	WWEG32_CG(CG_CAC_WEGION_5_WEIGHT_1, weg);

	weg = WWEG32_CG(CG_CAC_WEGION_4_OVEWWIDE_4) & ~(OVW_MODE_SPAWE_0_MASK |
							OVW_VAW_SPAWE_0_MASK |
							OVW_MODE_SPAWE_1_MASK |
							OVW_VAW_SPAWE_1_MASK);
	weg |= (OVW_MODE_SPAWE_0(ni_pi->cac_weights->ovw_mode_spawe_0) |
		OVW_VAW_SPAWE_0(ni_pi->cac_weights->ovw_vaw_spawe_0) |
		OVW_MODE_SPAWE_1(ni_pi->cac_weights->ovw_mode_spawe_1) |
		OVW_VAW_SPAWE_1(ni_pi->cac_weights->ovw_vaw_spawe_1));
	WWEG32_CG(CG_CAC_WEGION_4_OVEWWIDE_4, weg);

	weg = WWEG32(SQ_CAC_THWESHOWD) & ~(VSP_MASK |
					   VSP0_MASK |
					   GPW_MASK);
	weg |= (VSP(ni_pi->cac_weights->vsp) |
		VSP0(ni_pi->cac_weights->vsp0) |
		GPW(ni_pi->cac_weights->gpw));
	WWEG32(SQ_CAC_THWESHOWD, weg);

	weg = (MCDW_WW_ENABWE |
	       MCDX_WW_ENABWE |
	       MCDY_WW_ENABWE |
	       MCDZ_WW_ENABWE |
	       INDEX(0x09D4));
	WWEG32(MC_CG_CONFIG, weg);

	weg = (WEAD_WEIGHT(ni_pi->cac_weights->mc_wead_weight) |
	       WWITE_WEIGHT(ni_pi->cac_weights->mc_wwite_weight) |
	       AWWOW_OVEWFWOW);
	WWEG32(MC_CG_DATAPOWT, weg);

	wetuwn 0;
}

static int ni_enabwe_smc_cac(stwuct wadeon_device *wdev,
			     stwuct wadeon_ps *wadeon_new_state,
			     boow enabwe)
{
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);
	int wet = 0;
	PPSMC_Wesuwt smc_wesuwt;

	if (ni_pi->enabwe_cac) {
		if (enabwe) {
			if (!w600_is_uvd_state(wadeon_new_state->cwass, wadeon_new_state->cwass2)) {
				smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_CowwectCAC_PowewCowwewn);

				if (ni_pi->suppowt_cac_wong_tewm_avewage) {
					smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_CACWongTewmAvgEnabwe);
					if (PPSMC_Wesuwt_OK != smc_wesuwt)
						ni_pi->suppowt_cac_wong_tewm_avewage = fawse;
				}

				smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_EnabweCac);
				if (PPSMC_Wesuwt_OK != smc_wesuwt)
					wet = -EINVAW;

				ni_pi->cac_enabwed = (PPSMC_Wesuwt_OK == smc_wesuwt) ? twue : fawse;
			}
		} ewse if (ni_pi->cac_enabwed) {
			smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_MSG_DisabweCac);

			ni_pi->cac_enabwed = fawse;

			if (ni_pi->suppowt_cac_wong_tewm_avewage) {
				smc_wesuwt = wv770_send_msg_to_smc(wdev, PPSMC_CACWongTewmAvgDisabwe);
				if (PPSMC_Wesuwt_OK != smc_wesuwt)
					ni_pi->suppowt_cac_wong_tewm_avewage = fawse;
			}
		}
	}

	wetuwn wet;
}

static int ni_pcie_pewfowmance_wequest(stwuct wadeon_device *wdev,
				       u8 pewf_weq, boow advewtise)
{
#if defined(CONFIG_ACPI)
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if ((pewf_weq == PCIE_PEWF_WEQ_PECI_GEN1) ||
	    (pewf_weq == PCIE_PEWF_WEQ_PECI_GEN2)) {
		if (eg_pi->pcie_pewfowmance_wequest_wegistewed == fawse)
			wadeon_acpi_pcie_notify_device_weady(wdev);
		eg_pi->pcie_pewfowmance_wequest_wegistewed = twue;
		wetuwn wadeon_acpi_pcie_pewfowmance_wequest(wdev, pewf_weq, advewtise);
	} ewse if ((pewf_weq == PCIE_PEWF_WEQ_WEMOVE_WEGISTWY) &&
		    eg_pi->pcie_pewfowmance_wequest_wegistewed) {
		eg_pi->pcie_pewfowmance_wequest_wegistewed = fawse;
		wetuwn wadeon_acpi_pcie_pewfowmance_wequest(wdev, pewf_weq, advewtise);
	}
#endif
	wetuwn 0;
}

static int ni_advewtise_gen2_capabiwity(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);

	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2))
		pi->pcie_gen2 = twue;
	ewse
		pi->pcie_gen2 = fawse;

	if (!pi->pcie_gen2)
		ni_pcie_pewfowmance_wequest(wdev, PCIE_PEWF_WEQ_PECI_GEN2, twue);

	wetuwn 0;
}

static void ni_enabwe_bif_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					    boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp, bif;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);

	if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {
		if (enabwe) {
			if (!pi->boot_in_gen2) {
				bif = WWEG32(CG_BIF_WEQ_AND_WSP) & ~CG_CWIENT_WEQ_MASK;
				bif |= CG_CWIENT_WEQ(0xd);
				WWEG32(CG_BIF_WEQ_AND_WSP, bif);
			}
			tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
			tmp |= WC_HW_VOWTAGE_IF_CONTWOW(1);
			tmp |= WC_GEN2_EN_STWAP;

			tmp |= WC_CWW_FAIWED_SPD_CHANGE_CNT;
			WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
			udeway(10);
			tmp &= ~WC_CWW_FAIWED_SPD_CHANGE_CNT;
			WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
		} ewse {
			if (!pi->boot_in_gen2) {
				bif = WWEG32(CG_BIF_WEQ_AND_WSP) & ~CG_CWIENT_WEQ_MASK;
				bif |= CG_CWIENT_WEQ(0xd);
				WWEG32(CG_BIF_WEQ_AND_WSP, bif);

				tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
				tmp &= ~WC_GEN2_EN_STWAP;
			}
			WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
		}
	}
}

static void ni_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					boow enabwe)
{
	ni_enabwe_bif_dynamic_pcie_gen2(wdev, enabwe);

	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, ENABWE_GEN2PCIE, ~ENABWE_GEN2PCIE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~ENABWE_GEN2PCIE);
}

void ni_set_uvd_cwock_befowe_set_eng_cwock(stwuct wadeon_device *wdev,
					   stwuct wadeon_ps *new_ps,
					   stwuct wadeon_ps *owd_ps)
{
	stwuct ni_ps *new_state = ni_get_ps(new_ps);
	stwuct ni_ps *cuwwent_state = ni_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->pewfowmance_wevews[new_state->pewfowmance_wevew_count - 1].scwk >=
	    cuwwent_state->pewfowmance_wevews[cuwwent_state->pewfowmance_wevew_count - 1].scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

void ni_set_uvd_cwock_aftew_set_eng_cwock(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *new_ps,
					  stwuct wadeon_ps *owd_ps)
{
	stwuct ni_ps *new_state = ni_get_ps(new_ps);
	stwuct ni_ps *cuwwent_state = ni_get_ps(owd_ps);

	if ((new_ps->vcwk == owd_ps->vcwk) &&
	    (new_ps->dcwk == owd_ps->dcwk))
		wetuwn;

	if (new_state->pewfowmance_wevews[new_state->pewfowmance_wevew_count - 1].scwk <
	    cuwwent_state->pewfowmance_wevews[cuwwent_state->pewfowmance_wevew_count - 1].scwk)
		wetuwn;

	wadeon_set_uvd_cwocks(wdev, new_ps->vcwk, new_ps->dcwk);
}

void ni_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int w;

	w = ni_mc_woad_micwocode(wdev);
	if (w)
		DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
	ni_wead_cwock_wegistews(wdev);
	btc_wead_awb_wegistews(wdev);
	wv770_get_memowy_type(wdev);
	if (eg_pi->pcie_pewfowmance_wequest)
		ni_advewtise_gen2_capabiwity(wdev);
	wv770_get_pcie_gen2_status(wdev);
	wv770_enabwe_acpi_pm(wdev);
}

void ni_update_cuwwent_ps(stwuct wadeon_device *wdev,
			  stwuct wadeon_ps *wps)
{
	stwuct ni_ps *new_ps = ni_get_ps(wps);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);

	eg_pi->cuwwent_wps = *wps;
	ni_pi->cuwwent_ps = *new_ps;
	eg_pi->cuwwent_wps.ps_pwiv = &ni_pi->cuwwent_ps;
}

void ni_update_wequested_ps(stwuct wadeon_device *wdev,
			    stwuct wadeon_ps *wps)
{
	stwuct ni_ps *new_ps = ni_get_ps(wps);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_powew_info *ni_pi = ni_get_pi(wdev);

	eg_pi->wequested_wps = *wps;
	ni_pi->wequested_ps = *new_ps;
	eg_pi->wequested_wps.ps_pwiv = &ni_pi->wequested_ps;
}

int ni_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;
	int wet;

	if (pi->gfx_cwock_gating)
		ni_cg_cwockgating_defauwt(wdev);
	if (btc_dpm_enabwed(wdev))
		wetuwn -EINVAW;
	if (pi->mg_cwock_gating)
		ni_mg_cwockgating_defauwt(wdev);
	if (eg_pi->ws_cwock_gating)
		ni_ws_cwockgating_defauwt(wdev);
	if (pi->vowtage_contwow) {
		wv770_enabwe_vowtage_contwow(wdev, twue);
		wet = cypwess_constwuct_vowtage_tabwes(wdev);
		if (wet) {
			DWM_EWWOW("cypwess_constwuct_vowtage_tabwes faiwed\n");
			wetuwn wet;
		}
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = ni_initiawize_mc_weg_tabwe(wdev);
		if (wet)
			eg_pi->dynamic_ac_timing = fawse;
	}
	if (pi->dynamic_ss)
		cypwess_enabwe_spwead_spectwum(wdev, twue);
	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, twue);
	wv770_setup_bsp(wdev);
	wv770_pwogwam_git(wdev);
	wv770_pwogwam_tp(wdev);
	wv770_pwogwam_tpp(wdev);
	wv770_pwogwam_sstp(wdev);
	cypwess_enabwe_dispway_gap(wdev);
	wv770_pwogwam_vc(wdev);
	if (pi->dynamic_pcie_gen2)
		ni_enabwe_dynamic_pcie_gen2(wdev, twue);
	wet = wv770_upwoad_fiwmwawe(wdev);
	if (wet) {
		DWM_EWWOW("wv770_upwoad_fiwmwawe faiwed\n");
		wetuwn wet;
	}
	wet = ni_pwocess_fiwmwawe_headew(wdev);
	if (wet) {
		DWM_EWWOW("ni_pwocess_fiwmwawe_headew faiwed\n");
		wetuwn wet;
	}
	wet = ni_initiaw_switch_fwom_awb_f0_to_f1(wdev);
	if (wet) {
		DWM_EWWOW("ni_initiaw_switch_fwom_awb_f0_to_f1 faiwed\n");
		wetuwn wet;
	}
	wet = ni_init_smc_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("ni_init_smc_tabwe faiwed\n");
		wetuwn wet;
	}
	wet = ni_init_smc_spww_tabwe(wdev);
	if (wet) {
		DWM_EWWOW("ni_init_smc_spww_tabwe faiwed\n");
		wetuwn wet;
	}
	wet = ni_init_awb_tabwe_index(wdev);
	if (wet) {
		DWM_EWWOW("ni_init_awb_tabwe_index faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = ni_popuwate_mc_weg_tabwe(wdev, boot_ps);
		if (wet) {
			DWM_EWWOW("ni_popuwate_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}
	wet = ni_initiawize_smc_cac_tabwes(wdev);
	if (wet) {
		DWM_EWWOW("ni_initiawize_smc_cac_tabwes faiwed\n");
		wetuwn wet;
	}
	wet = ni_initiawize_hawdwawe_cac_managew(wdev);
	if (wet) {
		DWM_EWWOW("ni_initiawize_hawdwawe_cac_managew faiwed\n");
		wetuwn wet;
	}
	wet = ni_popuwate_smc_tdp_wimits(wdev, boot_ps);
	if (wet) {
		DWM_EWWOW("ni_popuwate_smc_tdp_wimits faiwed\n");
		wetuwn wet;
	}
	ni_pwogwam_wesponse_times(wdev);
	w7xx_stawt_smc(wdev);
	wet = cypwess_notify_smc_dispway_change(wdev, fawse);
	if (wet) {
		DWM_EWWOW("cypwess_notify_smc_dispway_change faiwed\n");
		wetuwn wet;
	}
	cypwess_enabwe_scwk_contwow(wdev, twue);
	if (eg_pi->memowy_twansition)
		cypwess_enabwe_mcwk_contwow(wdev, twue);
	cypwess_stawt_dpm(wdev);
	if (pi->gfx_cwock_gating)
		ni_gfx_cwockgating_enabwe(wdev, twue);
	if (pi->mg_cwock_gating)
		ni_mg_cwockgating_enabwe(wdev, twue);
	if (eg_pi->ws_cwock_gating)
		ni_ws_cwockgating_enabwe(wdev, twue);

	wv770_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, twue);

	ni_update_cuwwent_ps(wdev, boot_ps);

	wetuwn 0;
}

void ni_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;

	if (!btc_dpm_enabwed(wdev))
		wetuwn;
	wv770_cweaw_vc(wdev);
	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, fawse);
	ni_enabwe_powew_containment(wdev, boot_ps, fawse);
	ni_enabwe_smc_cac(wdev, boot_ps, fawse);
	cypwess_enabwe_spwead_spectwum(wdev, fawse);
	wv770_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, fawse);
	if (pi->dynamic_pcie_gen2)
		ni_enabwe_dynamic_pcie_gen2(wdev, fawse);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	if (pi->gfx_cwock_gating)
		ni_gfx_cwockgating_enabwe(wdev, fawse);
	if (pi->mg_cwock_gating)
		ni_mg_cwockgating_enabwe(wdev, fawse);
	if (eg_pi->ws_cwock_gating)
		ni_ws_cwockgating_enabwe(wdev, fawse);
	ni_stop_dpm(wdev);
	btc_weset_to_defauwt(wdev);
	ni_stop_smc(wdev);
	ni_fowce_switch_to_awb_f0(wdev);

	ni_update_cuwwent_ps(wdev, boot_ps);
}

static int ni_powew_contwow_set_wevew(stwuct wadeon_device *wdev)
{
	stwuct wadeon_ps *new_ps = wdev->pm.dpm.wequested_ps;
	int wet;

	wet = ni_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (wet)
		wetuwn wet;
	wet = wv770_hawt_smc(wdev);
	if (wet)
		wetuwn wet;
	wet = ni_popuwate_smc_tdp_wimits(wdev, new_ps);
	if (wet)
		wetuwn wet;
	wet = wv770_wesume_smc(wdev);
	if (wet)
		wetuwn wet;
	wet = wv770_set_sw_state(wdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int ni_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps wequested_ps = *wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *new_ps = &wequested_ps;

	ni_update_wequested_ps(wdev, new_ps);

	ni_appwy_state_adjust_wuwes(wdev, &eg_pi->wequested_wps);

	wetuwn 0;
}

int ni_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &eg_pi->wequested_wps;
	stwuct wadeon_ps *owd_ps = &eg_pi->cuwwent_wps;
	int wet;

	wet = ni_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (wet) {
		DWM_EWWOW("ni_westwict_pewfowmance_wevews_befowe_switch faiwed\n");
		wetuwn wet;
	}
	ni_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);
	wet = ni_enabwe_powew_containment(wdev, new_ps, fawse);
	if (wet) {
		DWM_EWWOW("ni_enabwe_powew_containment faiwed\n");
		wetuwn wet;
	}
	wet = ni_enabwe_smc_cac(wdev, new_ps, fawse);
	if (wet) {
		DWM_EWWOW("ni_enabwe_smc_cac faiwed\n");
		wetuwn wet;
	}
	wet = wv770_hawt_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_hawt_smc faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->smu_uvd_hs)
		btc_notify_uvd_to_smc(wdev, new_ps);
	wet = ni_upwoad_sw_state(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("ni_upwoad_sw_state faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = ni_upwoad_mc_weg_tabwe(wdev, new_ps);
		if (wet) {
			DWM_EWWOW("ni_upwoad_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}
	wet = ni_pwogwam_memowy_timing_pawametews(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("ni_pwogwam_memowy_timing_pawametews faiwed\n");
		wetuwn wet;
	}
	wet = wv770_wesume_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_wesume_smc faiwed\n");
		wetuwn wet;
	}
	wet = wv770_set_sw_state(wdev);
	if (wet) {
		DWM_EWWOW("wv770_set_sw_state faiwed\n");
		wetuwn wet;
	}
	ni_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);
	wet = ni_enabwe_smc_cac(wdev, new_ps, twue);
	if (wet) {
		DWM_EWWOW("ni_enabwe_smc_cac faiwed\n");
		wetuwn wet;
	}
	wet = ni_enabwe_powew_containment(wdev, new_ps, twue);
	if (wet) {
		DWM_EWWOW("ni_enabwe_powew_containment faiwed\n");
		wetuwn wet;
	}

	/* update tdp */
	wet = ni_powew_contwow_set_wevew(wdev);
	if (wet) {
		DWM_EWWOW("ni_powew_contwow_set_wevew faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

void ni_dpm_post_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &eg_pi->wequested_wps;

	ni_update_cuwwent_ps(wdev, new_ps);
}

#if 0
void ni_dpm_weset_asic(stwuct wadeon_device *wdev)
{
	ni_westwict_pewfowmance_wevews_befowe_switch(wdev);
	wv770_set_boot_state(wdev);
}
#endif

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
};

union ppwib_cwock_info {
	stwuct _ATOM_PPWIB_W600_CWOCK_INFO w600;
	stwuct _ATOM_PPWIB_WS780_CWOCK_INFO ws780;
	stwuct _ATOM_PPWIB_EVEWGWEEN_CWOCK_INFO evewgween;
	stwuct _ATOM_PPWIB_SUMO_CWOCK_INFO sumo;
};

union ppwib_powew_state {
	stwuct _ATOM_PPWIB_STATE v1;
	stwuct _ATOM_PPWIB_STATE_V2 v2;
};

static void ni_pawse_ppwib_non_cwock_info(stwuct wadeon_device *wdev,
					  stwuct wadeon_ps *wps,
					  stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info,
					  u8 tabwe_wev)
{
	wps->caps = we32_to_cpu(non_cwock_info->uwCapsAndSettings);
	wps->cwass = we16_to_cpu(non_cwock_info->usCwassification);
	wps->cwass2 = we16_to_cpu(non_cwock_info->usCwassification2);

	if (ATOM_PPWIB_NONCWOCKINFO_VEW1 < tabwe_wev) {
		wps->vcwk = we32_to_cpu(non_cwock_info->uwVCWK);
		wps->dcwk = we32_to_cpu(non_cwock_info->uwDCWK);
	} ewse if (w600_is_uvd_state(wps->cwass, wps->cwass2)) {
		wps->vcwk = WV770_DEFAUWT_VCWK_FWEQ;
		wps->dcwk = WV770_DEFAUWT_DCWK_FWEQ;
	} ewse {
		wps->vcwk = 0;
		wps->dcwk = 0;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wdev->pm.dpm.boot_ps = wps;
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wdev->pm.dpm.uvd_ps = wps;
}

static void ni_pawse_ppwib_cwock_info(stwuct wadeon_device *wdev,
				      stwuct wadeon_ps *wps, int index,
				      union ppwib_cwock_info *cwock_info)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wv7xx_pw *pw = &ps->pewfowmance_wevews[index];

	ps->pewfowmance_wevew_count = index + 1;

	pw->scwk = we16_to_cpu(cwock_info->evewgween.usEngineCwockWow);
	pw->scwk |= cwock_info->evewgween.ucEngineCwockHigh << 16;
	pw->mcwk = we16_to_cpu(cwock_info->evewgween.usMemowyCwockWow);
	pw->mcwk |= cwock_info->evewgween.ucMemowyCwockHigh << 16;

	pw->vddc = we16_to_cpu(cwock_info->evewgween.usVDDC);
	pw->vddci = we16_to_cpu(cwock_info->evewgween.usVDDCI);
	pw->fwags = we32_to_cpu(cwock_info->evewgween.uwFwags);

	/* patch up vddc if necessawy */
	if (pw->vddc == 0xff01) {
		if (pi->max_vddc)
			pw->vddc = pi->max_vddc;
	}

	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_ACPI) {
		pi->acpi_vddc = pw->vddc;
		eg_pi->acpi_vddci = pw->vddci;
		if (ps->pewfowmance_wevews[0].fwags & ATOM_PPWIB_W600_FWAGS_PCIEGEN2)
			pi->acpi_pcie_gen2 = twue;
		ewse
			pi->acpi_pcie_gen2 = fawse;
	}

	if (wps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV) {
		eg_pi->uwv.suppowted = twue;
		eg_pi->uwv.pw = pw;
	}

	if (pi->min_vddc_in_tabwe > pw->vddc)
		pi->min_vddc_in_tabwe = pw->vddc;

	if (pi->max_vddc_in_tabwe < pw->vddc)
		pi->max_vddc_in_tabwe = pw->vddc;

	/* patch up boot state */
	if (wps->cwass & ATOM_PPWIB_CWASSIFICATION_BOOT) {
		u16 vddc, vddci, mvdd;
		wadeon_atombios_get_defauwt_vowtages(wdev, &vddc, &vddci, &mvdd);
		pw->mcwk = wdev->cwock.defauwt_mcwk;
		pw->scwk = wdev->cwock.defauwt_scwk;
		pw->vddc = vddc;
		pw->vddci = vddci;
	}

	if ((wps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) ==
	    ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE) {
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.scwk = pw->scwk;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.mcwk = pw->mcwk;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.vddc = pw->vddc;
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac.vddci = pw->vddci;
	}
}

static int ni_pawse_powew_tabwe(stwuct wadeon_device *wdev)
{
	stwuct wadeon_mode_info *mode_info = &wdev->mode_info;
	stwuct _ATOM_PPWIB_NONCWOCK_INFO *non_cwock_info;
	union ppwib_powew_state *powew_state;
	int i, j;
	union ppwib_cwock_info *cwock_info;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	stwuct ni_ps *ps;

	if (!atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	wdev->pm.dpm.ps = kcawwoc(powew_info->ppwib.ucNumStates,
				  sizeof(stwuct wadeon_ps),
				  GFP_KEWNEW);
	if (!wdev->pm.dpm.ps)
		wetuwn -ENOMEM;

	fow (i = 0; i < powew_info->ppwib.ucNumStates; i++) {
		powew_state = (union ppwib_powew_state *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib.usStateAwwayOffset) +
			 i * powew_info->ppwib.ucStateEntwySize);
		non_cwock_info = (stwuct _ATOM_PPWIB_NONCWOCK_INFO *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib.usNonCwockInfoAwwayOffset) +
			 (powew_state->v1.ucNonCwockStateIndex *
			  powew_info->ppwib.ucNonCwockSize));
		if (powew_info->ppwib.ucStateEntwySize - 1) {
			u8 *idx;
			ps = kzawwoc(sizeof(stwuct ni_ps), GFP_KEWNEW);
			if (ps == NUWW) {
				kfwee(wdev->pm.dpm.ps);
				wetuwn -ENOMEM;
			}
			wdev->pm.dpm.ps[i].ps_pwiv = ps;
			ni_pawse_ppwib_non_cwock_info(wdev, &wdev->pm.dpm.ps[i],
							 non_cwock_info,
							 powew_info->ppwib.ucNonCwockSize);
			idx = (u8 *)&powew_state->v1.ucCwockStateIndices[0];
			fow (j = 0; j < (powew_info->ppwib.ucStateEntwySize - 1); j++) {
				cwock_info = (union ppwib_cwock_info *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(powew_info->ppwib.usCwockInfoAwwayOffset) +
					 (idx[j] * powew_info->ppwib.ucCwockInfoSize));
				ni_pawse_ppwib_cwock_info(wdev,
							  &wdev->pm.dpm.ps[i], j,
							  cwock_info);
			}
		}
	}
	wdev->pm.dpm.num_ps = powew_info->ppwib.ucNumStates;
	wetuwn 0;
}

int ni_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi;
	stwuct evewgween_powew_info *eg_pi;
	stwuct ni_powew_info *ni_pi;
	stwuct atom_cwock_dividews dividews;
	int wet;

	ni_pi = kzawwoc(sizeof(stwuct ni_powew_info), GFP_KEWNEW);
	if (ni_pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = ni_pi;
	eg_pi = &ni_pi->eg;
	pi = &eg_pi->wv7xx;

	wv770_get_max_vddc(wdev);

	eg_pi->uwv.suppowted = fawse;
	pi->acpi_vddc = 0;
	eg_pi->acpi_vddci = 0;
	pi->min_vddc_in_tabwe = 0;
	pi->max_vddc_in_tabwe = 0;

	wet = w600_get_pwatfowm_caps(wdev);
	if (wet)
		wetuwn wet;

	wet = ni_pawse_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;
	wet = w600_pawse_extended_powew_tabwe(wdev);
	if (wet)
		wetuwn wet;

	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies =
		kcawwoc(4,
			sizeof(stwuct wadeon_cwock_vowtage_dependency_entwy),
			GFP_KEWNEW);
	if (!wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies) {
		w600_fwee_extended_powew_tabwe(wdev);
		wetuwn -ENOMEM;
	}
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.count = 4;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[0].cwk = 0;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[0].v = 0;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[1].cwk = 36000;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[1].v = 720;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[2].cwk = 54000;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[2].v = 810;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[3].cwk = 72000;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[3].v = 900;

	ni_patch_dependency_tabwes_based_on_weakage(wdev);

	if (wdev->pm.dpm.vowtage_wesponse_time == 0)
		wdev->pm.dpm.vowtage_wesponse_time = W600_VOWTAGEWESPONSETIME_DFWT;
	if (wdev->pm.dpm.backbias_wesponse_time == 0)
		wdev->pm.dpm.backbias_wesponse_time = W600_BACKBIASWESPONSETIME_DFWT;

	wet = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					     0, fawse, &dividews);
	if (wet)
		pi->wef_div = dividews.wef_div + 1;
	ewse
		pi->wef_div = W600_WEFEWENCEDIVIDEW_DFWT;

	pi->wwp = WV770_WWP_DFWT;
	pi->wmp = WV770_WMP_DFWT;
	pi->whp = WV770_WHP_DFWT;
	pi->wmp = WV770_WMP_DFWT;

	eg_pi->ats[0].wwp = WV770_WWP_DFWT;
	eg_pi->ats[0].wmp = WV770_WMP_DFWT;
	eg_pi->ats[0].whp = WV770_WHP_DFWT;
	eg_pi->ats[0].wmp = WV770_WMP_DFWT;

	eg_pi->ats[1].wwp = BTC_WWP_UVD_DFWT;
	eg_pi->ats[1].wmp = BTC_WMP_UVD_DFWT;
	eg_pi->ats[1].whp = BTC_WHP_UVD_DFWT;
	eg_pi->ats[1].wmp = BTC_WMP_UVD_DFWT;

	eg_pi->smu_uvd_hs = twue;

	if (wdev->pdev->device == 0x6707) {
		pi->mcwk_stwobe_mode_thweshowd = 55000;
		pi->mcwk_edc_enabwe_thweshowd = 55000;
		eg_pi->mcwk_edc_ww_enabwe_thweshowd = 55000;
	} ewse {
		pi->mcwk_stwobe_mode_thweshowd = 40000;
		pi->mcwk_edc_enabwe_thweshowd = 40000;
		eg_pi->mcwk_edc_ww_enabwe_thweshowd = 40000;
	}
	ni_pi->mcwk_wtt_mode_thweshowd = eg_pi->mcwk_edc_ww_enabwe_thweshowd;

	pi->vowtage_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDC, 0);

	pi->mvdd_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_MVDDC, 0);

	eg_pi->vddci_contwow =
		wadeon_atom_is_vowtage_gpio(wdev, SET_VOWTAGE_TYPE_ASIC_VDDCI, 0);

	wv770_get_engine_memowy_ss(wdev);

	pi->asi = WV770_ASI_DFWT;
	pi->pasi = CYPWESS_HASI_DFWT;
	pi->vwc = CYPWESS_VWC_DFWT;

	pi->powew_gating = fawse;

	pi->gfx_cwock_gating = twue;

	pi->mg_cwock_gating = twue;
	pi->mgcgtssm = twue;
	eg_pi->ws_cwock_gating = fawse;
	eg_pi->scwk_deep_sweep = fawse;

	pi->dynamic_pcie_gen2 = twue;

	if (wdev->pm.int_thewmaw_type != THEWMAW_TYPE_NONE)
		pi->thewmaw_pwotection = twue;
	ewse
		pi->thewmaw_pwotection = fawse;

	pi->dispway_gap = twue;

	pi->dcodt = twue;

	pi->uwps = twue;

	eg_pi->dynamic_ac_timing = twue;
	eg_pi->abm = twue;
	eg_pi->mcws = twue;
	eg_pi->wight_sweep = twue;
	eg_pi->memowy_twansition = twue;
#if defined(CONFIG_ACPI)
	eg_pi->pcie_pewfowmance_wequest =
		wadeon_acpi_is_pcie_pewfowmance_wequest_suppowted(wdev);
#ewse
	eg_pi->pcie_pewfowmance_wequest = fawse;
#endif

	eg_pi->dww_defauwt_on = fawse;

	eg_pi->scwk_deep_sweep = fawse;

	pi->mcwk_stuttew_mode_thweshowd = 0;

	pi->swam_end = SMC_WAM_END;

	wdev->pm.dpm.dyn_state.mcwk_scwk_watio = 3;
	wdev->pm.dpm.dyn_state.vddc_vddci_dewta = 200;
	wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2 = 900;
	wdev->pm.dpm.dyn_state.vawid_scwk_vawues.count = AWWAY_SIZE(btc_vawid_scwk);
	wdev->pm.dpm.dyn_state.vawid_scwk_vawues.vawues = btc_vawid_scwk;
	wdev->pm.dpm.dyn_state.vawid_mcwk_vawues.count = 0;
	wdev->pm.dpm.dyn_state.vawid_mcwk_vawues.vawues = NUWW;
	wdev->pm.dpm.dyn_state.scwk_mcwk_dewta = 12500;

	ni_pi->cac_data.weakage_coefficients.at = 516;
	ni_pi->cac_data.weakage_coefficients.bt = 18;
	ni_pi->cac_data.weakage_coefficients.av = 51;
	ni_pi->cac_data.weakage_coefficients.bv = 2957;

	switch (wdev->pdev->device) {
	case 0x6700:
	case 0x6701:
	case 0x6702:
	case 0x6703:
	case 0x6718:
		ni_pi->cac_weights = &cac_weights_cayman_xt;
		bweak;
	case 0x6705:
	case 0x6719:
	case 0x671D:
	case 0x671C:
	defauwt:
		ni_pi->cac_weights = &cac_weights_cayman_pwo;
		bweak;
	case 0x6704:
	case 0x6706:
	case 0x6707:
	case 0x6708:
	case 0x6709:
		ni_pi->cac_weights = &cac_weights_cayman_we;
		bweak;
	}

	if (ni_pi->cac_weights->enabwe_powew_containment_by_defauwt) {
		ni_pi->enabwe_powew_containment = twue;
		ni_pi->enabwe_cac = twue;
		ni_pi->enabwe_sq_wamping = twue;
	} ewse {
		ni_pi->enabwe_powew_containment = fawse;
		ni_pi->enabwe_cac = fawse;
		ni_pi->enabwe_sq_wamping = fawse;
	}

	ni_pi->dwivew_cawcuwate_cac_weakage = fawse;
	ni_pi->cac_configuwation_wequiwed = twue;

	if (ni_pi->cac_configuwation_wequiwed) {
		ni_pi->suppowt_cac_wong_tewm_avewage = twue;
		ni_pi->wta_window_size = ni_pi->cac_weights->w2_wta_window_size;
		ni_pi->wts_twuncate = ni_pi->cac_weights->wts_twuncate;
	} ewse {
		ni_pi->suppowt_cac_wong_tewm_avewage = fawse;
		ni_pi->wta_window_size = 0;
		ni_pi->wts_twuncate = 0;
	}

	ni_pi->use_powew_boost_wimit = twue;

	/* make suwe dc wimits awe vawid */
	if ((wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.scwk == 0) ||
	    (wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.mcwk == 0))
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc =
			wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;

	wetuwn 0;
}

void ni_dpm_fini(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		kfwee(wdev->pm.dpm.ps[i].ps_pwiv);
	}
	kfwee(wdev->pm.dpm.ps);
	kfwee(wdev->pm.dpm.pwiv);
	kfwee(wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies);
	w600_fwee_extended_powew_tabwe(wdev);
}

void ni_dpm_pwint_powew_state(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wps)
{
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wv7xx_pw *pw;
	int i;

	w600_dpm_pwint_cwass_info(wps->cwass, wps->cwass2);
	w600_dpm_pwint_cap_info(wps->caps);
	pwintk("\tuvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
	fow (i = 0; i < ps->pewfowmance_wevew_count; i++) {
		pw = &ps->pewfowmance_wevews[i];
		if (wdev->famiwy >= CHIP_TAHITI)
			pwintk("\t\tpowew wevew %d    scwk: %u mcwk: %u vddc: %u vddci: %u pcie gen: %u\n",
			       i, pw->scwk, pw->mcwk, pw->vddc, pw->vddci, pw->pcie_gen + 1);
		ewse
			pwintk("\t\tpowew wevew %d    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
			       i, pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
	}
	w600_dpm_pwint_ps_status(wdev, wps);
}

void ni_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						    stwuct seq_fiwe *m)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_INDEX_MASK) >>
		CUWWENT_STATE_INDEX_SHIFT;

	if (cuwwent_index >= ps->pewfowmance_wevew_count) {
		seq_pwintf(m, "invawid dpm pwofiwe %d\n", cuwwent_index);
	} ewse {
		pw = &ps->pewfowmance_wevews[cuwwent_index];
		seq_pwintf(m, "uvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
		seq_pwintf(m, "powew wevew %d    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
			   cuwwent_index, pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
	}
}

u32 ni_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_INDEX_MASK) >>
		CUWWENT_STATE_INDEX_SHIFT;

	if (cuwwent_index >= ps->pewfowmance_wevew_count) {
		wetuwn 0;
	} ewse {
		pw = &ps->pewfowmance_wevews[cuwwent_index];
		wetuwn pw->scwk;
	}
}

u32 ni_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct ni_ps *ps = ni_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_STATE_INDEX_MASK) >>
		CUWWENT_STATE_INDEX_SHIFT;

	if (cuwwent_index >= ps->pewfowmance_wevew_count) {
		wetuwn 0;
	} ewse {
		pw = &ps->pewfowmance_wevews[cuwwent_index];
		wetuwn pw->mcwk;
	}
}

u32 ni_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_ps *wequested_state = ni_get_ps(&eg_pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->pewfowmance_wevews[0].scwk;
	ewse
		wetuwn wequested_state->pewfowmance_wevews[wequested_state->pewfowmance_wevew_count - 1].scwk;
}

u32 ni_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct ni_ps *wequested_state = ni_get_ps(&eg_pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->pewfowmance_wevews[0].mcwk;
	ewse
		wetuwn wequested_state->pewfowmance_wevews[wequested_state->pewfowmance_wevew_count - 1].mcwk;
}

