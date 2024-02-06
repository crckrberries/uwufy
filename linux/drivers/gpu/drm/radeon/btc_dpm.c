/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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

#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>

#incwude "atom.h"
#incwude "btc_dpm.h"
#incwude "btcd.h"
#incwude "cypwess_dpm.h"
#incwude "evewgween.h"
#incwude "w600_dpm.h"
#incwude "wv770.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"

#define MC_CG_AWB_FWEQ_F0           0x0a
#define MC_CG_AWB_FWEQ_F1           0x0b
#define MC_CG_AWB_FWEQ_F2           0x0c
#define MC_CG_AWB_FWEQ_F3           0x0d

#define MC_CG_SEQ_DWAMCONF_S0       0x05
#define MC_CG_SEQ_DWAMCONF_S1       0x06
#define MC_CG_SEQ_YCWK_SUSPEND      0x04
#define MC_CG_SEQ_YCWK_WESUME       0x0a

#define SMC_WAM_END 0x8000

#ifndef BTC_MGCG_SEQUENCE
#define BTC_MGCG_SEQUENCE  300

extewn int ni_mc_woad_micwocode(stwuct wadeon_device *wdev);

//********* BAWTS **************//
static const u32 bawts_cgcg_cgws_defauwt[] =
{
	/* Wegistew,   Vawue,     Mask bits */
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
#define BAWTS_CGCG_CGWS_DEFAUWT_WENGTH sizeof(bawts_cgcg_cgws_defauwt) / (3 * sizeof(u32))

static const u32 bawts_cgcg_cgws_disabwe[] =
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
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
};
#define BAWTS_CGCG_CGWS_DISABWE_WENGTH sizeof(bawts_cgcg_cgws_disabwe) / (3 * sizeof(u32))

static const u32 bawts_cgcg_cgws_enabwe[] =
{
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
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
#define BAWTS_CGCG_CGWS_ENABWE_WENGTH sizeof(bawts_cgcg_cgws_enabwe) / (3 * sizeof(u32))

static const u32 bawts_mgcg_defauwt[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
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
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0xff000100, 0xffffffff,
	0x0000802c, 0x40000000, 0xffffffff,
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
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0x40010000, 0xffffffff,
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
	0x00009294, 0x00000000, 0xffffffff,
	0x0000802c, 0xc0000000, 0xffffffff,
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
#define BAWTS_MGCG_DEFAUWT_WENGTH sizeof(bawts_mgcg_defauwt) / (3 * sizeof(u32))

static const u32 bawts_mgcg_disabwe[] =
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
#define BAWTS_MGCG_DISABWE_WENGTH sizeof(bawts_mgcg_disabwe) / (3 * sizeof(u32))

static const u32 bawts_mgcg_enabwe[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x81944000, 0xffffffff
};
#define BAWTS_MGCG_ENABWE_WENGTH sizeof(bawts_mgcg_enabwe) / (3 * sizeof(u32))

//********* CAICOS **************//
static const u32 caicos_cgcg_cgws_defauwt[] =
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
#define CAICOS_CGCG_CGWS_DEFAUWT_WENGTH sizeof(caicos_cgcg_cgws_defauwt) / (3 * sizeof(u32))

static const u32 caicos_cgcg_cgws_disabwe[] =
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
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
};
#define CAICOS_CGCG_CGWS_DISABWE_WENGTH sizeof(caicos_cgcg_cgws_disabwe) / (3 * sizeof(u32))

static const u32 caicos_cgcg_cgws_enabwe[] =
{
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
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
#define CAICOS_CGCG_CGWS_ENABWE_WENGTH sizeof(caicos_cgcg_cgws_enabwe) / (3 * sizeof(u32))

static const u32 caicos_mgcg_defauwt[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
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
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0xff000100, 0xffffffff,
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
	0x000091e8, 0x00000000, 0xffffffff,
	0x00009294, 0x00000000, 0xffffffff,
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
#define CAICOS_MGCG_DEFAUWT_WENGTH sizeof(caicos_mgcg_defauwt) / (3 * sizeof(u32))

static const u32 caicos_mgcg_disabwe[] =
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
#define CAICOS_MGCG_DISABWE_WENGTH sizeof(caicos_mgcg_disabwe) / (3 * sizeof(u32))

static const u32 caicos_mgcg_enabwe[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x46944040, 0xffffffff
};
#define CAICOS_MGCG_ENABWE_WENGTH sizeof(caicos_mgcg_enabwe) / (3 * sizeof(u32))

//********* TUWKS **************//
static const u32 tuwks_cgcg_cgws_defauwt[] =
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
#define TUWKS_CGCG_CGWS_DEFAUWT_WENGTH  sizeof(tuwks_cgcg_cgws_defauwt) / (3 * sizeof(u32))

static const u32 tuwks_cgcg_cgws_disabwe[] =
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
	0x00000644, 0x000f7912, 0x001f4180,
	0x00000644, 0x000f3812, 0x001f4180
};
#define TUWKS_CGCG_CGWS_DISABWE_WENGTH sizeof(tuwks_cgcg_cgws_disabwe) / (3 * sizeof(u32))

static const u32 tuwks_cgcg_cgws_enabwe[] =
{
	/* 0x0000c124, 0x84180000, 0x00180000, */
	0x00000644, 0x000f7892, 0x001f4080,
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
#define TUWKS_CGCG_CGWS_ENABWE_WENGTH sizeof(tuwks_cgcg_cgws_enabwe) / (3 * sizeof(u32))

// These awe the sequences fow tuwks_mgcg_shws
static const u32 tuwks_mgcg_defauwt[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x00005448, 0x00000100, 0xffffffff,
	0x000055e4, 0x00600100, 0xffffffff,
	0x0000160c, 0x00000100, 0xffffffff,
	0x0000c164, 0x00000100, 0xffffffff,
	0x00008a18, 0x00000100, 0xffffffff,
	0x0000897c, 0x06000100, 0xffffffff,
	0x00008b28, 0x00000100, 0xffffffff,
	0x00009144, 0x00000100, 0xffffffff,
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
	0x0000977c, 0x00000100, 0xffffffff,
	0x00003f80, 0x00000100, 0xffffffff,
	0x0000a210, 0x00000100, 0xffffffff,
	0x0000a214, 0x00000100, 0xffffffff,
	0x000004d8, 0x00000100, 0xffffffff,
	0x00009784, 0x00000100, 0xffffffff,
	0x00009698, 0x00000100, 0xffffffff,
	0x000004d4, 0x00000200, 0xffffffff,
	0x000004d0, 0x00000000, 0xffffffff,
	0x000030cc, 0x00000100, 0xffffffff,
	0x0000d0c0, 0x00000100, 0xffffffff,
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
	0x00009294, 0x00000000, 0xffffffff,
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
#define TUWKS_MGCG_DEFAUWT_WENGTH sizeof(tuwks_mgcg_defauwt) / (3 * sizeof(u32))

static const u32 tuwks_mgcg_disabwe[] =
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
#define TUWKS_MGCG_DISABWE_WENGTH sizeof(tuwks_mgcg_disabwe) / (3 * sizeof(u32))

static const u32 tuwks_mgcg_enabwe[] =
{
	0x0000802c, 0xc0000000, 0xffffffff,
	0x000008f8, 0x00000000, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000001, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000002, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x000008f8, 0x00000003, 0xffffffff,
	0x000008fc, 0x00000000, 0xffffffff,
	0x00009150, 0x6e944000, 0xffffffff
};
#define TUWKS_MGCG_ENABWE_WENGTH sizeof(tuwks_mgcg_enabwe) / (3 * sizeof(u32))

#endif

#ifndef BTC_SYSWS_SEQUENCE
#define BTC_SYSWS_SEQUENCE  100


//********* BAWTS **************//
static const u32 bawts_sysws_defauwt[] =
{
	/* Wegistew,   Vawue,     Mask bits */
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#define BAWTS_SYSWS_DEFAUWT_WENGTH sizeof(bawts_sysws_defauwt) / (3 * sizeof(u32))

static const u32 bawts_sysws_disabwe[] =
{
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
};
#define BAWTS_SYSWS_DISABWE_WENGTH sizeof(bawts_sysws_disabwe) / (3 * sizeof(u32))

static const u32 bawts_sysws_enabwe[] =
{
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#define BAWTS_SYSWS_ENABWE_WENGTH sizeof(bawts_sysws_enabwe) / (3 * sizeof(u32))

//********* CAICOS **************//
static const u32 caicos_sysws_defauwt[] =
{
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#define CAICOS_SYSWS_DEFAUWT_WENGTH sizeof(caicos_sysws_defauwt) / (3 * sizeof(u32))

static const u32 caicos_sysws_disabwe[] =
{
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
};
#define CAICOS_SYSWS_DISABWE_WENGTH sizeof(caicos_sysws_disabwe) / (3 * sizeof(u32))

static const u32 caicos_sysws_enabwe[] =
{
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff
};
#define CAICOS_SYSWS_ENABWE_WENGTH sizeof(caicos_sysws_enabwe) / (3 * sizeof(u32))

//********* TUWKS **************//
static const u32 tuwks_sysws_defauwt[] =
{
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#define TUWKS_SYSWS_DEFAUWT_WENGTH sizeof(tuwks_sysws_defauwt) / (3 * sizeof(u32))

static const u32 tuwks_sysws_disabwe[] =
{
	0x000055e8, 0x00000000, 0xffffffff,
	0x0000d0bc, 0x00000000, 0xffffffff,
	0x000015c0, 0x00041401, 0xffffffff,
	0x0000264c, 0x00040400, 0xffffffff,
	0x00002648, 0x00040400, 0xffffffff,
	0x00002650, 0x00040400, 0xffffffff,
	0x000020b8, 0x00040400, 0xffffffff,
	0x000020bc, 0x00040400, 0xffffffff,
	0x000020c0, 0x00040c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680000, 0xffffffff,
	0x000004c8, 0x00000001, 0xffffffff,
	0x000064ec, 0x00007ffd, 0xffffffff,
	0x00000c7c, 0x0000ff00, 0xffffffff,
	0x00006dfc, 0x0000007f, 0xffffffff
};
#define TUWKS_SYSWS_DISABWE_WENGTH sizeof(tuwks_sysws_disabwe) / (3 * sizeof(u32))

static const u32 tuwks_sysws_enabwe[] =
{
	0x000055e8, 0x00000001, 0xffffffff,
	0x0000d0bc, 0x00000100, 0xffffffff,
	0x000015c0, 0x000c1401, 0xffffffff,
	0x0000264c, 0x000c0400, 0xffffffff,
	0x00002648, 0x000c0400, 0xffffffff,
	0x00002650, 0x000c0400, 0xffffffff,
	0x000020b8, 0x000c0400, 0xffffffff,
	0x000020bc, 0x000c0400, 0xffffffff,
	0x000020c0, 0x000c0c80, 0xffffffff,
	0x0000f4a0, 0x000000c0, 0xffffffff,
	0x0000f4a4, 0x00680fff, 0xffffffff,
	0x000004c8, 0x00000000, 0xffffffff,
	0x000064ec, 0x00000000, 0xffffffff,
	0x00000c7c, 0x00000000, 0xffffffff,
	0x00006dfc, 0x00000000, 0xffffffff
};
#define TUWKS_SYSWS_ENABWE_WENGTH sizeof(tuwks_sysws_enabwe) / (3 * sizeof(u32))

#endif

u32 btc_vawid_scwk[40] =
{
	5000,   10000,  15000,  20000,  25000,  30000,  35000,  40000,  45000,  50000,
	55000,  60000,  65000,  70000,  75000,  80000,  85000,  90000,  95000,  100000,
	105000, 110000, 11500,  120000, 125000, 130000, 135000, 140000, 145000, 150000,
	155000, 160000, 165000, 170000, 175000, 180000, 185000, 190000, 195000, 200000
};

static const stwuct wadeon_bwackwist_cwocks btc_bwackwist_cwocks[] = {
	{ 10000, 30000, WADEON_SCWK_UP },
	{ 15000, 30000, WADEON_SCWK_UP },
	{ 20000, 30000, WADEON_SCWK_UP },
	{ 25000, 30000, WADEON_SCWK_UP }
};

void btc_get_max_cwock_fwom_vowtage_dependency_tabwe(stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe,
						     u32 *max_cwock)
{
	u32 i, cwock = 0;

	if ((tabwe == NUWW) || (tabwe->count == 0)) {
		*max_cwock = cwock;
		wetuwn;
	}

	fow (i = 0; i < tabwe->count; i++) {
		if (cwock < tabwe->entwies[i].cwk)
			cwock = tabwe->entwies[i].cwk;
	}
	*max_cwock = cwock;
}

void btc_appwy_vowtage_dependency_wuwes(stwuct wadeon_cwock_vowtage_dependency_tabwe *tabwe,
					u32 cwock, u16 max_vowtage, u16 *vowtage)
{
	u32 i;

	if ((tabwe == NUWW) || (tabwe->count == 0))
		wetuwn;

	fow (i= 0; i < tabwe->count; i++) {
		if (cwock <= tabwe->entwies[i].cwk) {
			if (*vowtage < tabwe->entwies[i].v)
				*vowtage = (u16)((tabwe->entwies[i].v < max_vowtage) ?
						  tabwe->entwies[i].v : max_vowtage);
			wetuwn;
		}
	}

	*vowtage = (*vowtage > max_vowtage) ? *vowtage : max_vowtage;
}

static u32 btc_find_vawid_cwock(stwuct wadeon_cwock_awway *cwocks,
				u32 max_cwock, u32 wequested_cwock)
{
	unsigned int i;

	if ((cwocks == NUWW) || (cwocks->count == 0))
		wetuwn (wequested_cwock < max_cwock) ? wequested_cwock : max_cwock;

	fow (i = 0; i < cwocks->count; i++) {
		if (cwocks->vawues[i] >= wequested_cwock)
			wetuwn (cwocks->vawues[i] < max_cwock) ? cwocks->vawues[i] : max_cwock;
	}

	wetuwn (cwocks->vawues[cwocks->count - 1] < max_cwock) ?
		cwocks->vawues[cwocks->count - 1] : max_cwock;
}

static u32 btc_get_vawid_mcwk(stwuct wadeon_device *wdev,
			      u32 max_mcwk, u32 wequested_mcwk)
{
	wetuwn btc_find_vawid_cwock(&wdev->pm.dpm.dyn_state.vawid_mcwk_vawues,
				    max_mcwk, wequested_mcwk);
}

static u32 btc_get_vawid_scwk(stwuct wadeon_device *wdev,
			      u32 max_scwk, u32 wequested_scwk)
{
	wetuwn btc_find_vawid_cwock(&wdev->pm.dpm.dyn_state.vawid_scwk_vawues,
				    max_scwk, wequested_scwk);
}

void btc_skip_bwackwist_cwocks(stwuct wadeon_device *wdev,
			       const u32 max_scwk, const u32 max_mcwk,
			       u32 *scwk, u32 *mcwk)
{
	int i, num_bwackwist_cwocks;

	if ((scwk == NUWW) || (mcwk == NUWW))
		wetuwn;

	num_bwackwist_cwocks = AWWAY_SIZE(btc_bwackwist_cwocks);

	fow (i = 0; i < num_bwackwist_cwocks; i++) {
		if ((btc_bwackwist_cwocks[i].scwk == *scwk) &&
		    (btc_bwackwist_cwocks[i].mcwk == *mcwk))
			bweak;
	}

	if (i < num_bwackwist_cwocks) {
		if (btc_bwackwist_cwocks[i].action == WADEON_SCWK_UP) {
			*scwk = btc_get_vawid_scwk(wdev, max_scwk, *scwk + 1);

			if (*scwk < max_scwk)
				btc_skip_bwackwist_cwocks(wdev, max_scwk, max_mcwk, scwk, mcwk);
		}
	}
}

void btc_adjust_cwock_combinations(stwuct wadeon_device *wdev,
				   const stwuct wadeon_cwock_and_vowtage_wimits *max_wimits,
				   stwuct wv7xx_pw *pw)
{

	if ((pw->mcwk == 0) || (pw->scwk == 0))
		wetuwn;

	if (pw->mcwk == pw->scwk)
		wetuwn;

	if (pw->mcwk > pw->scwk) {
		if (((pw->mcwk + (pw->scwk - 1)) / pw->scwk) > wdev->pm.dpm.dyn_state.mcwk_scwk_watio)
			pw->scwk = btc_get_vawid_scwk(wdev,
						      max_wimits->scwk,
						      (pw->mcwk +
						       (wdev->pm.dpm.dyn_state.mcwk_scwk_watio - 1)) /
						      wdev->pm.dpm.dyn_state.mcwk_scwk_watio);
	} ewse {
		if ((pw->scwk - pw->mcwk) > wdev->pm.dpm.dyn_state.scwk_mcwk_dewta)
			pw->mcwk = btc_get_vawid_mcwk(wdev,
						      max_wimits->mcwk,
						      pw->scwk -
						      wdev->pm.dpm.dyn_state.scwk_mcwk_dewta);
	}
}

static u16 btc_find_vowtage(stwuct atom_vowtage_tabwe *tabwe, u16 vowtage)
{
	unsigned int i;

	fow (i = 0; i < tabwe->count; i++) {
		if (vowtage <= tabwe->entwies[i].vawue)
			wetuwn tabwe->entwies[i].vawue;
	}

	wetuwn tabwe->entwies[tabwe->count - 1].vawue;
}

void btc_appwy_vowtage_dewta_wuwes(stwuct wadeon_device *wdev,
				   u16 max_vddc, u16 max_vddci,
				   u16 *vddc, u16 *vddci)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	u16 new_vowtage;

	if ((0 == *vddc) || (0 == *vddci))
		wetuwn;

	if (*vddc > *vddci) {
		if ((*vddc - *vddci) > wdev->pm.dpm.dyn_state.vddc_vddci_dewta) {
			new_vowtage = btc_find_vowtage(&eg_pi->vddci_vowtage_tabwe,
						       (*vddc - wdev->pm.dpm.dyn_state.vddc_vddci_dewta));
			*vddci = (new_vowtage < max_vddci) ? new_vowtage : max_vddci;
		}
	} ewse {
		if ((*vddci - *vddc) > wdev->pm.dpm.dyn_state.vddc_vddci_dewta) {
			new_vowtage = btc_find_vowtage(&eg_pi->vddc_vowtage_tabwe,
						       (*vddci - wdev->pm.dpm.dyn_state.vddc_vddci_dewta));
			*vddc = (new_vowtage < max_vddc) ? new_vowtage : max_vddc;
		}
	}
}

static void btc_enabwe_bif_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					     boow enabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp, bif;

	tmp = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if (enabwe) {
		if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
		    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {
			if (!pi->boot_in_gen2) {
				bif = WWEG32(CG_BIF_WEQ_AND_WSP) & ~CG_CWIENT_WEQ_MASK;
				bif |= CG_CWIENT_WEQ(0xd);
				WWEG32(CG_BIF_WEQ_AND_WSP, bif);

				tmp &= ~WC_HW_VOWTAGE_IF_CONTWOW_MASK;
				tmp |= WC_HW_VOWTAGE_IF_CONTWOW(1);
				tmp |= WC_GEN2_EN_STWAP;

				tmp |= WC_CWW_FAIWED_SPD_CHANGE_CNT;
				WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
				udeway(10);
				tmp &= ~WC_CWW_FAIWED_SPD_CHANGE_CNT;
				WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, tmp);
			}
		}
	} ewse {
		if ((tmp & WC_OTHEW_SIDE_EVEW_SENT_GEN2) ||
		    (tmp & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {
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

static void btc_enabwe_dynamic_pcie_gen2(stwuct wadeon_device *wdev,
					 boow enabwe)
{
	btc_enabwe_bif_dynamic_pcie_gen2(wdev, enabwe);

	if (enabwe)
		WWEG32_P(GENEWAW_PWWMGT, ENABWE_GEN2PCIE, ~ENABWE_GEN2PCIE);
	ewse
		WWEG32_P(GENEWAW_PWWMGT, 0, ~ENABWE_GEN2PCIE);
}

static int btc_disabwe_uwv(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (eg_pi->uwv.suppowted) {
		if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_DisabweUWV) != PPSMC_Wesuwt_OK)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int btc_popuwate_uwv_state(stwuct wadeon_device *wdev,
				  WV770_SMC_STATETABWE *tabwe)
{
	int wet = -EINVAW;
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_pw *uwv_pw = eg_pi->uwv.pw;

	if (uwv_pw->vddc) {
		wet = cypwess_convewt_powew_wevew_to_smc(wdev,
							 uwv_pw,
							 &tabwe->UWVState.wevews[0],
							 PPSMC_DISPWAY_WATEWMAWK_WOW);
		if (wet == 0) {
			tabwe->UWVState.wevews[0].awbVawue = MC_CG_AWB_FWEQ_F0;
			tabwe->UWVState.wevews[0].ACIndex = 1;

			tabwe->UWVState.wevews[1] = tabwe->UWVState.wevews[0];
			tabwe->UWVState.wevews[2] = tabwe->UWVState.wevews[0];

			tabwe->UWVState.fwags |= PPSMC_SWSTATE_FWAG_DC;

			WWEG32(CG_UWV_CONTWOW, BTC_CGUWVCONTWOW_DFWT);
			WWEG32(CG_UWV_PAWAMETEW, BTC_CGUWVPAWAMETEW_DFWT);
		}
	}

	wetuwn wet;
}

static int btc_popuwate_smc_acpi_state(stwuct wadeon_device *wdev,
				       WV770_SMC_STATETABWE *tabwe)
{
	int wet = cypwess_popuwate_smc_acpi_state(wdev, tabwe);

	if (wet == 0) {
		tabwe->ACPIState.wevews[0].ACIndex = 0;
		tabwe->ACPIState.wevews[1].ACIndex = 0;
		tabwe->ACPIState.wevews[2].ACIndex = 0;
	}

	wetuwn wet;
}

void btc_pwogwam_mgcg_hw_sequence(stwuct wadeon_device *wdev,
				  const u32 *sequence, u32 count)
{
	u32 i, wength = count * 3;
	u32 tmp;

	fow (i = 0; i < wength; i+=3) {
		tmp = WWEG32(sequence[i]);
		tmp &= ~sequence[i+2];
		tmp |= sequence[i+1] & sequence[i+2];
		WWEG32(sequence[i], tmp);
	}
}

static void btc_cg_cwock_gating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *p = NUWW;

	if (wdev->famiwy == CHIP_BAWTS) {
		p = (const u32 *)&bawts_cgcg_cgws_defauwt;
		count = BAWTS_CGCG_CGWS_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_TUWKS) {
		p = (const u32 *)&tuwks_cgcg_cgws_defauwt;
		count = TUWKS_CGCG_CGWS_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_CAICOS) {
		p = (const u32 *)&caicos_cgcg_cgws_defauwt;
		count = CAICOS_CGCG_CGWS_DEFAUWT_WENGTH;
	} ewse
		wetuwn;

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

static void btc_cg_cwock_gating_enabwe(stwuct wadeon_device *wdev,
				       boow enabwe)
{
	u32 count;
	const u32 *p = NUWW;

	if (enabwe) {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_cgcg_cgws_enabwe;
			count = BAWTS_CGCG_CGWS_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_cgcg_cgws_enabwe;
			count = TUWKS_CGCG_CGWS_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_cgcg_cgws_enabwe;
			count = CAICOS_CGCG_CGWS_ENABWE_WENGTH;
		} ewse
			wetuwn;
	} ewse {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_cgcg_cgws_disabwe;
			count = BAWTS_CGCG_CGWS_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_cgcg_cgws_disabwe;
			count = TUWKS_CGCG_CGWS_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_cgcg_cgws_disabwe;
			count = CAICOS_CGCG_CGWS_DISABWE_WENGTH;
		} ewse
			wetuwn;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

static void btc_mg_cwock_gating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *p = NUWW;

	if (wdev->famiwy == CHIP_BAWTS) {
		p = (const u32 *)&bawts_mgcg_defauwt;
		count = BAWTS_MGCG_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_TUWKS) {
		p = (const u32 *)&tuwks_mgcg_defauwt;
		count = TUWKS_MGCG_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_CAICOS) {
		p = (const u32 *)&caicos_mgcg_defauwt;
		count = CAICOS_MGCG_DEFAUWT_WENGTH;
	} ewse
		wetuwn;

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

static void btc_mg_cwock_gating_enabwe(stwuct wadeon_device *wdev,
				       boow enabwe)
{
	u32 count;
	const u32 *p = NUWW;

	if (enabwe) {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_mgcg_enabwe;
			count = BAWTS_MGCG_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_mgcg_enabwe;
			count = TUWKS_MGCG_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_mgcg_enabwe;
			count = CAICOS_MGCG_ENABWE_WENGTH;
		} ewse
			wetuwn;
	} ewse {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_mgcg_disabwe[0];
			count = BAWTS_MGCG_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_mgcg_disabwe[0];
			count = TUWKS_MGCG_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_mgcg_disabwe[0];
			count = CAICOS_MGCG_DISABWE_WENGTH;
		} ewse
			wetuwn;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

static void btc_ws_cwock_gating_defauwt(stwuct wadeon_device *wdev)
{
	u32 count;
	const u32 *p = NUWW;

	if (wdev->famiwy == CHIP_BAWTS) {
		p = (const u32 *)&bawts_sysws_defauwt;
		count = BAWTS_SYSWS_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_TUWKS) {
		p = (const u32 *)&tuwks_sysws_defauwt;
		count = TUWKS_SYSWS_DEFAUWT_WENGTH;
	} ewse if (wdev->famiwy == CHIP_CAICOS) {
		p = (const u32 *)&caicos_sysws_defauwt;
		count = CAICOS_SYSWS_DEFAUWT_WENGTH;
	} ewse
		wetuwn;

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

static void btc_ws_cwock_gating_enabwe(stwuct wadeon_device *wdev,
				       boow enabwe)
{
	u32 count;
	const u32 *p = NUWW;

	if (enabwe) {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_sysws_enabwe;
			count = BAWTS_SYSWS_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_sysws_enabwe;
			count = TUWKS_SYSWS_ENABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_sysws_enabwe;
			count = CAICOS_SYSWS_ENABWE_WENGTH;
		} ewse
			wetuwn;
	} ewse {
		if (wdev->famiwy == CHIP_BAWTS) {
			p = (const u32 *)&bawts_sysws_disabwe;
			count = BAWTS_SYSWS_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_TUWKS) {
			p = (const u32 *)&tuwks_sysws_disabwe;
			count = TUWKS_SYSWS_DISABWE_WENGTH;
		} ewse if (wdev->famiwy == CHIP_CAICOS) {
			p = (const u32 *)&caicos_sysws_disabwe;
			count = CAICOS_SYSWS_DISABWE_WENGTH;
		} ewse
			wetuwn;
	}

	btc_pwogwam_mgcg_hw_sequence(wdev, p, count);
}

boow btc_dpm_enabwed(stwuct wadeon_device *wdev)
{
	if (wv770_is_smc_wunning(wdev))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int btc_init_smc_tabwe(stwuct wadeon_device *wdev,
			      stwuct wadeon_ps *wadeon_boot_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	WV770_SMC_STATETABWE *tabwe = &pi->smc_statetabwe;
	int wet;

	memset(tabwe, 0, sizeof(WV770_SMC_STATETABWE));

	cypwess_popuwate_smc_vowtage_tabwes(wdev, tabwe);

	switch (wdev->pm.int_thewmaw_type) {
	case THEWMAW_TYPE_EVEWGWEEN:
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

	wet = cypwess_popuwate_smc_initiaw_state(wdev, wadeon_boot_state, tabwe);
	if (wet)
		wetuwn wet;

	if (eg_pi->scwk_deep_sweep)
		WWEG32_P(SCWK_PSKIP_CNTW, PSKIP_ON_AWWOW_STOP_HI(32),
			 ~PSKIP_ON_AWWOW_STOP_HI_MASK);

	wet = btc_popuwate_smc_acpi_state(wdev, tabwe);
	if (wet)
		wetuwn wet;

	if (eg_pi->uwv.suppowted) {
		wet = btc_popuwate_uwv_state(wdev, tabwe);
		if (wet)
			eg_pi->uwv.suppowted = fawse;
	}

	tabwe->dwivewState = tabwe->initiawState;

	wetuwn wv770_copy_bytes_to_smc(wdev,
				       pi->state_tabwe_stawt,
				       (u8 *)tabwe,
				       sizeof(WV770_SMC_STATETABWE),
				       pi->swam_end);
}

static void btc_set_at_fow_uvd(stwuct wadeon_device *wdev,
			       stwuct wadeon_ps *wadeon_new_state)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int idx = 0;

	if (w600_is_uvd_state(wadeon_new_state->cwass, wadeon_new_state->cwass2))
		idx = 1;

	if ((idx == 1) && !eg_pi->smu_uvd_hs) {
		pi->wwp = 10;
		pi->wmp = 100;
		pi->whp = 100;
		pi->wmp = 10;
	} ewse {
		pi->wwp = eg_pi->ats[idx].wwp;
		pi->wmp = eg_pi->ats[idx].wmp;
		pi->whp = eg_pi->ats[idx].whp;
		pi->wmp = eg_pi->ats[idx].wmp;
	}

}

void btc_notify_uvd_to_smc(stwuct wadeon_device *wdev,
			   stwuct wadeon_ps *wadeon_new_state)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (w600_is_uvd_state(wadeon_new_state->cwass, wadeon_new_state->cwass2)) {
		wv770_wwite_smc_soft_wegistew(wdev,
					      WV770_SMC_SOFT_WEGISTEW_uvd_enabwed, 1);
		eg_pi->uvd_enabwed = twue;
	} ewse {
		wv770_wwite_smc_soft_wegistew(wdev,
					      WV770_SMC_SOFT_WEGISTEW_uvd_enabwed, 0);
		eg_pi->uvd_enabwed = fawse;
	}
}

int btc_weset_to_defauwt(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_WesetToDefauwts) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void btc_stop_smc(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (((WWEG32(WB_SYNC_WESET_SEW) & WB_SYNC_WESET_SEW_MASK) >> WB_SYNC_WESET_SEW_SHIFT) != 1)
			bweak;
		udeway(1);
	}
	udeway(100);

	w7xx_stop_smc(wdev);
}

void btc_wead_awb_wegistews(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct evewgween_awb_wegistews *awb_wegistews =
		&eg_pi->bootup_awb_wegistews;

	awb_wegistews->mc_awb_dwam_timing = WWEG32(MC_AWB_DWAM_TIMING);
	awb_wegistews->mc_awb_dwam_timing2 = WWEG32(MC_AWB_DWAM_TIMING2);
	awb_wegistews->mc_awb_wfsh_wate = WWEG32(MC_AWB_WFSH_WATE);
	awb_wegistews->mc_awb_buwst_time = WWEG32(MC_AWB_BUWST_TIME);
}


static void btc_set_awb0_wegistews(stwuct wadeon_device *wdev,
				   stwuct evewgween_awb_wegistews *awb_wegistews)
{
	u32 vaw;

	WWEG32(MC_AWB_DWAM_TIMING,  awb_wegistews->mc_awb_dwam_timing);
	WWEG32(MC_AWB_DWAM_TIMING2, awb_wegistews->mc_awb_dwam_timing2);

	vaw = (awb_wegistews->mc_awb_wfsh_wate & POWEWMODE0_MASK) >>
		POWEWMODE0_SHIFT;
	WWEG32_P(MC_AWB_WFSH_WATE, POWEWMODE0(vaw), ~POWEWMODE0_MASK);

	vaw = (awb_wegistews->mc_awb_buwst_time & STATE0_MASK) >>
		STATE0_SHIFT;
	WWEG32_P(MC_AWB_BUWST_TIME, STATE0(vaw), ~STATE0_MASK);
}

static void btc_set_boot_state_timing(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (eg_pi->uwv.suppowted)
		btc_set_awb0_wegistews(wdev, &eg_pi->bootup_awb_wegistews);
}

static boow btc_is_state_uwv_compatibwe(stwuct wadeon_device *wdev,
					stwuct wadeon_ps *wadeon_state)
{
	stwuct wv7xx_ps *state = wv770_get_ps(wadeon_state);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_pw *uwv_pw = eg_pi->uwv.pw;

	if (state->wow.mcwk != uwv_pw->mcwk)
		wetuwn fawse;

	if (state->wow.vddci != uwv_pw->vddci)
		wetuwn fawse;

	/* XXX check mincwocks, etc. */

	wetuwn twue;
}


static int btc_set_uwv_dwam_timing(stwuct wadeon_device *wdev)
{
	u32 vaw;
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_pw *uwv_pw = eg_pi->uwv.pw;

	wadeon_atom_set_engine_dwam_timings(wdev,
					    uwv_pw->scwk,
					    uwv_pw->mcwk);

	vaw = wv770_cawcuwate_memowy_wefwesh_wate(wdev, uwv_pw->scwk);
	WWEG32_P(MC_AWB_WFSH_WATE, POWEWMODE0(vaw), ~POWEWMODE0_MASK);

	vaw = cypwess_cawcuwate_buwst_time(wdev, uwv_pw->scwk, uwv_pw->mcwk);
	WWEG32_P(MC_AWB_BUWST_TIME, STATE0(vaw), ~STATE0_MASK);

	wetuwn 0;
}

static int btc_enabwe_uwv(stwuct wadeon_device *wdev)
{
	if (wv770_send_msg_to_smc(wdev, PPSMC_MSG_EnabweUWV) != PPSMC_Wesuwt_OK)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int btc_set_powew_state_conditionawwy_enabwe_uwv(stwuct wadeon_device *wdev,
							stwuct wadeon_ps *wadeon_new_state)
{
	int wet = 0;
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (eg_pi->uwv.suppowted) {
		if (btc_is_state_uwv_compatibwe(wdev, wadeon_new_state)) {
			// Set AWB[0] to wefwect the DWAM timing needed fow UWV.
			wet = btc_set_uwv_dwam_timing(wdev);
			if (wet == 0)
				wet = btc_enabwe_uwv(wdev);
		}
	}

	wetuwn wet;
}

static boow btc_check_s0_mc_weg_index(u16 in_weg, u16 *out_weg)
{
	boow wesuwt = twue;

	switch (in_weg) {
	case MC_SEQ_WAS_TIMING >> 2:
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
	defauwt:
		wesuwt = fawse;
		bweak;
	}

	wetuwn wesuwt;
}

static void btc_set_vawid_fwag(stwuct evewgween_mc_weg_tabwe *tabwe)
{
	u8 i, j;

	fow (i = 0; i < tabwe->wast; i++) {
		fow (j = 1; j < tabwe->num_entwies; j++) {
			if (tabwe->mc_weg_tabwe_entwy[j-1].mc_data[i] !=
			    tabwe->mc_weg_tabwe_entwy[j].mc_data[i]) {
				tabwe->vawid_fwag |= (1 << i);
				bweak;
			}
		}
	}
}

static int btc_set_mc_speciaw_wegistews(stwuct wadeon_device *wdev,
					stwuct evewgween_mc_weg_tabwe *tabwe)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u8 i, j, k;
	u32 tmp;

	fow (i = 0, j = tabwe->wast; i < tabwe->wast; i++) {
		switch (tabwe->mc_weg_addwess[i].s1) {
		case MC_SEQ_MISC1 >> 2:
			tmp = WWEG32(MC_PMG_CMD_EMWS);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_EMWS >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_EMWS_WP >> 2;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					((tmp & 0xffff0000)) |
					((tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0xffff0000) >> 16);
			}
			j++;

			if (j >= SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;

			tmp = WWEG32(MC_PMG_CMD_MWS);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_MWS >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_MWS_WP >> 2;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(tmp & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
				if (!pi->mem_gddw5)
					tabwe->mc_weg_tabwe_entwy[k].mc_data[j] |= 0x100;
			}
			j++;

			if (j >= SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;
			bweak;
		case MC_SEQ_WESEWVE_M >> 2:
			tmp = WWEG32(MC_PMG_CMD_MWS1);
			tabwe->mc_weg_addwess[j].s1 = MC_PMG_CMD_MWS1 >> 2;
			tabwe->mc_weg_addwess[j].s0 = MC_SEQ_PMG_CMD_MWS1_WP >> 2;
			fow (k = 0; k < tabwe->num_entwies; k++) {
				tabwe->mc_weg_tabwe_entwy[k].mc_data[j] =
					(tmp & 0xffff0000) |
					(tabwe->mc_weg_tabwe_entwy[k].mc_data[i] & 0x0000ffff);
			}
			j++;

			if (j >= SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE)
				wetuwn -EINVAW;
			bweak;
		defauwt:
			bweak;
		}
	}

	tabwe->wast = j;

	wetuwn 0;
}

static void btc_set_s0_mc_weg_index(stwuct evewgween_mc_weg_tabwe *tabwe)
{
	u32 i;
	u16 addwess;

	fow (i = 0; i < tabwe->wast; i++) {
		tabwe->mc_weg_addwess[i].s0 =
			btc_check_s0_mc_weg_index(tabwe->mc_weg_addwess[i].s1, &addwess) ?
			addwess : tabwe->mc_weg_addwess[i].s1;
	}
}

static int btc_copy_vbios_mc_weg_tabwe(stwuct atom_mc_weg_tabwe *tabwe,
				       stwuct evewgween_mc_weg_tabwe *eg_tabwe)
{
	u8 i, j;

	if (tabwe->wast > SMC_EVEWGWEEN_MC_WEGISTEW_AWWAY_SIZE)
		wetuwn -EINVAW;

	if (tabwe->num_entwies > MAX_AC_TIMING_ENTWIES)
		wetuwn -EINVAW;

	fow (i = 0; i < tabwe->wast; i++)
		eg_tabwe->mc_weg_addwess[i].s1 = tabwe->mc_weg_addwess[i].s1;
	eg_tabwe->wast = tabwe->wast;

	fow (i = 0; i < tabwe->num_entwies; i++) {
		eg_tabwe->mc_weg_tabwe_entwy[i].mcwk_max =
			tabwe->mc_weg_tabwe_entwy[i].mcwk_max;
		fow(j = 0; j < tabwe->wast; j++)
			eg_tabwe->mc_weg_tabwe_entwy[i].mc_data[j] =
				tabwe->mc_weg_tabwe_entwy[i].mc_data[j];
	}
	eg_tabwe->num_entwies = tabwe->num_entwies;

	wetuwn 0;
}

static int btc_initiawize_mc_weg_tabwe(stwuct wadeon_device *wdev)
{
	int wet;
	stwuct atom_mc_weg_tabwe *tabwe;
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct evewgween_mc_weg_tabwe *eg_tabwe = &eg_pi->mc_weg_tabwe;
	u8 moduwe_index = wv770_get_memowy_moduwe_index(wdev);

	tabwe = kzawwoc(sizeof(stwuct atom_mc_weg_tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	/* Pwogwam additionaw WP wegistews that awe no wongew pwogwammed by VBIOS */
	WWEG32(MC_SEQ_WAS_TIMING_WP, WWEG32(MC_SEQ_WAS_TIMING));
	WWEG32(MC_SEQ_CAS_TIMING_WP, WWEG32(MC_SEQ_CAS_TIMING));
	WWEG32(MC_SEQ_MISC_TIMING_WP, WWEG32(MC_SEQ_MISC_TIMING));
	WWEG32(MC_SEQ_MISC_TIMING2_WP, WWEG32(MC_SEQ_MISC_TIMING2));
	WWEG32(MC_SEQ_WD_CTW_D0_WP, WWEG32(MC_SEQ_WD_CTW_D0));
	WWEG32(MC_SEQ_WD_CTW_D1_WP, WWEG32(MC_SEQ_WD_CTW_D1));
	WWEG32(MC_SEQ_WW_CTW_D0_WP, WWEG32(MC_SEQ_WW_CTW_D0));
	WWEG32(MC_SEQ_WW_CTW_D1_WP, WWEG32(MC_SEQ_WW_CTW_D1));
	WWEG32(MC_SEQ_PMG_CMD_EMWS_WP, WWEG32(MC_PMG_CMD_EMWS));
	WWEG32(MC_SEQ_PMG_CMD_MWS_WP, WWEG32(MC_PMG_CMD_MWS));
	WWEG32(MC_SEQ_PMG_CMD_MWS1_WP, WWEG32(MC_PMG_CMD_MWS1));

	wet = wadeon_atom_init_mc_weg_tabwe(wdev, moduwe_index, tabwe);

	if (wet)
		goto init_mc_done;

	wet = btc_copy_vbios_mc_weg_tabwe(tabwe, eg_tabwe);

	if (wet)
		goto init_mc_done;

	btc_set_s0_mc_weg_index(eg_tabwe);
	wet = btc_set_mc_speciaw_wegistews(wdev, eg_tabwe);

	if (wet)
		goto init_mc_done;

	btc_set_vawid_fwag(eg_tabwe);

init_mc_done:
	kfwee(tabwe);

	wetuwn wet;
}

static void btc_init_stuttew_mode(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 tmp;

	if (pi->mcwk_stuttew_mode_thweshowd) {
		if (pi->mem_gddw5) {
			tmp = WWEG32(MC_PMG_AUTO_CFG);
			if ((0x200 & tmp) == 0) {
				tmp = (tmp & 0xfffffc0b) | 0x204;
				WWEG32(MC_PMG_AUTO_CFG, tmp);
			}
		}
	}
}

boow btc_dpm_vbwank_too_showt(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	u32 vbwank_time = w600_dpm_get_vbwank_time(wdev);
	u32 switch_wimit = pi->mem_gddw5 ? 450 : 100;

	if (vbwank_time < switch_wimit)
		wetuwn twue;
	ewse
		wetuwn fawse;

}

static void btc_appwy_state_adjust_wuwes(stwuct wadeon_device *wdev,
					 stwuct wadeon_ps *wps)
{
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wadeon_cwock_and_vowtage_wimits *max_wimits;
	boow disabwe_mcwk_switching;
	u32 mcwk, scwk;
	u16 vddc, vddci;

	if ((wdev->pm.dpm.new_active_cwtc_count > 1) ||
	    btc_dpm_vbwank_too_showt(wdev))
		disabwe_mcwk_switching = twue;
	ewse
		disabwe_mcwk_switching = fawse;

	if (wdev->pm.dpm.ac_powew)
		max_wimits = &wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;
	ewse
		max_wimits = &wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc;

	if (wdev->pm.dpm.ac_powew == fawse) {
		if (ps->high.mcwk > max_wimits->mcwk)
			ps->high.mcwk = max_wimits->mcwk;
		if (ps->high.scwk > max_wimits->scwk)
			ps->high.scwk = max_wimits->scwk;
		if (ps->high.vddc > max_wimits->vddc)
			ps->high.vddc = max_wimits->vddc;
		if (ps->high.vddci > max_wimits->vddci)
			ps->high.vddci = max_wimits->vddci;

		if (ps->medium.mcwk > max_wimits->mcwk)
			ps->medium.mcwk = max_wimits->mcwk;
		if (ps->medium.scwk > max_wimits->scwk)
			ps->medium.scwk = max_wimits->scwk;
		if (ps->medium.vddc > max_wimits->vddc)
			ps->medium.vddc = max_wimits->vddc;
		if (ps->medium.vddci > max_wimits->vddci)
			ps->medium.vddci = max_wimits->vddci;

		if (ps->wow.mcwk > max_wimits->mcwk)
			ps->wow.mcwk = max_wimits->mcwk;
		if (ps->wow.scwk > max_wimits->scwk)
			ps->wow.scwk = max_wimits->scwk;
		if (ps->wow.vddc > max_wimits->vddc)
			ps->wow.vddc = max_wimits->vddc;
		if (ps->wow.vddci > max_wimits->vddci)
			ps->wow.vddci = max_wimits->vddci;
	}

	/* XXX vawidate the min cwocks wequiwed fow dispway */

	if (disabwe_mcwk_switching) {
		scwk = ps->wow.scwk;
		mcwk = ps->high.mcwk;
		vddc = ps->wow.vddc;
		vddci = ps->high.vddci;
	} ewse {
		scwk = ps->wow.scwk;
		mcwk = ps->wow.mcwk;
		vddc = ps->wow.vddc;
		vddci = ps->wow.vddci;
	}

	/* adjusted wow state */
	ps->wow.scwk = scwk;
	ps->wow.mcwk = mcwk;
	ps->wow.vddc = vddc;
	ps->wow.vddci = vddci;

	btc_skip_bwackwist_cwocks(wdev, max_wimits->scwk, max_wimits->mcwk,
				  &ps->wow.scwk, &ps->wow.mcwk);

	/* adjusted medium, high states */
	if (ps->medium.scwk < ps->wow.scwk)
		ps->medium.scwk = ps->wow.scwk;
	if (ps->medium.vddc < ps->wow.vddc)
		ps->medium.vddc = ps->wow.vddc;
	if (ps->high.scwk < ps->medium.scwk)
		ps->high.scwk = ps->medium.scwk;
	if (ps->high.vddc < ps->medium.vddc)
		ps->high.vddc = ps->medium.vddc;

	if (disabwe_mcwk_switching) {
		mcwk = ps->wow.mcwk;
		if (mcwk < ps->medium.mcwk)
			mcwk = ps->medium.mcwk;
		if (mcwk < ps->high.mcwk)
			mcwk = ps->high.mcwk;
		ps->wow.mcwk = mcwk;
		ps->wow.vddci = vddci;
		ps->medium.mcwk = mcwk;
		ps->medium.vddci = vddci;
		ps->high.mcwk = mcwk;
		ps->high.vddci = vddci;
	} ewse {
		if (ps->medium.mcwk < ps->wow.mcwk)
			ps->medium.mcwk = ps->wow.mcwk;
		if (ps->medium.vddci < ps->wow.vddci)
			ps->medium.vddci = ps->wow.vddci;
		if (ps->high.mcwk < ps->medium.mcwk)
			ps->high.mcwk = ps->medium.mcwk;
		if (ps->high.vddci < ps->medium.vddci)
			ps->high.vddci = ps->medium.vddci;
	}

	btc_skip_bwackwist_cwocks(wdev, max_wimits->scwk, max_wimits->mcwk,
				  &ps->medium.scwk, &ps->medium.mcwk);
	btc_skip_bwackwist_cwocks(wdev, max_wimits->scwk, max_wimits->mcwk,
				  &ps->high.scwk, &ps->high.mcwk);

	btc_adjust_cwock_combinations(wdev, max_wimits, &ps->wow);
	btc_adjust_cwock_combinations(wdev, max_wimits, &ps->medium);
	btc_adjust_cwock_combinations(wdev, max_wimits, &ps->high);

	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
					   ps->wow.scwk, max_wimits->vddc, &ps->wow.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
					   ps->wow.mcwk, max_wimits->vddci, &ps->wow.vddci);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
					   ps->wow.mcwk, max_wimits->vddc, &ps->wow.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk,
					   wdev->cwock.cuwwent_dispcwk, max_wimits->vddc, &ps->wow.vddc);

	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
					   ps->medium.scwk, max_wimits->vddc, &ps->medium.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
					   ps->medium.mcwk, max_wimits->vddci, &ps->medium.vddci);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
					   ps->medium.mcwk, max_wimits->vddc, &ps->medium.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk,
					   wdev->cwock.cuwwent_dispcwk, max_wimits->vddc, &ps->medium.vddc);

	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
					   ps->high.scwk, max_wimits->vddc, &ps->high.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
					   ps->high.mcwk, max_wimits->vddci, &ps->high.vddci);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
					   ps->high.mcwk, max_wimits->vddc, &ps->high.vddc);
	btc_appwy_vowtage_dependency_wuwes(&wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk,
					   wdev->cwock.cuwwent_dispcwk, max_wimits->vddc, &ps->high.vddc);

	btc_appwy_vowtage_dewta_wuwes(wdev, max_wimits->vddc, max_wimits->vddci,
				      &ps->wow.vddc, &ps->wow.vddci);
	btc_appwy_vowtage_dewta_wuwes(wdev, max_wimits->vddc, max_wimits->vddci,
				      &ps->medium.vddc, &ps->medium.vddci);
	btc_appwy_vowtage_dewta_wuwes(wdev, max_wimits->vddc, max_wimits->vddci,
				      &ps->high.vddc, &ps->high.vddci);

	if ((ps->high.vddc <= wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc) &&
	    (ps->medium.vddc <= wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc) &&
	    (ps->wow.vddc <= wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc))
		ps->dc_compatibwe = twue;
	ewse
		ps->dc_compatibwe = fawse;

	if (ps->wow.vddc < wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2)
		ps->wow.fwags &= ~ATOM_PPWIB_W600_FWAGS_PCIEGEN2;
	if (ps->medium.vddc < wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2)
		ps->medium.fwags &= ~ATOM_PPWIB_W600_FWAGS_PCIEGEN2;
	if (ps->high.vddc < wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2)
		ps->high.fwags &= ~ATOM_PPWIB_W600_FWAGS_PCIEGEN2;
}

static void btc_update_cuwwent_ps(stwuct wadeon_device *wdev,
				  stwuct wadeon_ps *wps)
{
	stwuct wv7xx_ps *new_ps = wv770_get_ps(wps);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	eg_pi->cuwwent_wps = *wps;
	eg_pi->cuwwent_ps = *new_ps;
	eg_pi->cuwwent_wps.ps_pwiv = &eg_pi->cuwwent_ps;
}

static void btc_update_wequested_ps(stwuct wadeon_device *wdev,
				    stwuct wadeon_ps *wps)
{
	stwuct wv7xx_ps *new_ps = wv770_get_ps(wps);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	eg_pi->wequested_wps = *wps;
	eg_pi->wequested_ps = *new_ps;
	eg_pi->wequested_wps.ps_pwiv = &eg_pi->wequested_ps;
}

#if 0
void btc_dpm_weset_asic(stwuct wadeon_device *wdev)
{
	wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	btc_disabwe_uwv(wdev);
	btc_set_boot_state_timing(wdev);
	wv770_set_boot_state(wdev);
}
#endif

int btc_dpm_pwe_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps wequested_ps = *wdev->pm.dpm.wequested_ps;
	stwuct wadeon_ps *new_ps = &wequested_ps;

	btc_update_wequested_ps(wdev, new_ps);

	btc_appwy_state_adjust_wuwes(wdev, &eg_pi->wequested_wps);

	wetuwn 0;
}

int btc_dpm_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &eg_pi->wequested_wps;
	stwuct wadeon_ps *owd_ps = &eg_pi->cuwwent_wps;
	int wet;

	wet = btc_disabwe_uwv(wdev);
	btc_set_boot_state_timing(wdev);
	wet = wv770_westwict_pewfowmance_wevews_befowe_switch(wdev);
	if (wet) {
		DWM_EWWOW("wv770_westwict_pewfowmance_wevews_befowe_switch faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_notify_wink_speed_change_befowe_state_change(wdev, new_ps, owd_ps);

	wv770_set_uvd_cwock_befowe_set_eng_cwock(wdev, new_ps, owd_ps);
	wet = wv770_hawt_smc(wdev);
	if (wet) {
		DWM_EWWOW("wv770_hawt_smc faiwed\n");
		wetuwn wet;
	}
	btc_set_at_fow_uvd(wdev, new_ps);
	if (eg_pi->smu_uvd_hs)
		btc_notify_uvd_to_smc(wdev, new_ps);
	wet = cypwess_upwoad_sw_state(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("cypwess_upwoad_sw_state faiwed\n");
		wetuwn wet;
	}
	if (eg_pi->dynamic_ac_timing) {
		wet = cypwess_upwoad_mc_weg_tabwe(wdev, new_ps);
		if (wet) {
			DWM_EWWOW("cypwess_upwoad_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}

	cypwess_pwogwam_memowy_timing_pawametews(wdev, new_ps);

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
	wv770_set_uvd_cwock_aftew_set_eng_cwock(wdev, new_ps, owd_ps);

	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_notify_wink_speed_change_aftew_state_change(wdev, new_ps, owd_ps);

	wet = btc_set_powew_state_conditionawwy_enabwe_uwv(wdev, new_ps);
	if (wet) {
		DWM_EWWOW("btc_set_powew_state_conditionawwy_enabwe_uwv faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

void btc_dpm_post_set_powew_state(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *new_ps = &eg_pi->wequested_wps;

	btc_update_cuwwent_ps(wdev, new_ps);
}

int btc_dpm_enabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *boot_ps = wdev->pm.dpm.boot_ps;
	int wet;

	if (pi->gfx_cwock_gating)
		btc_cg_cwock_gating_defauwt(wdev);

	if (btc_dpm_enabwed(wdev))
		wetuwn -EINVAW;

	if (pi->mg_cwock_gating)
		btc_mg_cwock_gating_defauwt(wdev);

	if (eg_pi->ws_cwock_gating)
		btc_ws_cwock_gating_defauwt(wdev);

	if (pi->vowtage_contwow) {
		wv770_enabwe_vowtage_contwow(wdev, twue);
		wet = cypwess_constwuct_vowtage_tabwes(wdev);
		if (wet) {
			DWM_EWWOW("cypwess_constwuct_vowtage_tabwes faiwed\n");
			wetuwn wet;
		}
	}

	if (pi->mvdd_contwow) {
		wet = cypwess_get_mvdd_configuwation(wdev);
		if (wet) {
			DWM_EWWOW("cypwess_get_mvdd_configuwation faiwed\n");
			wetuwn wet;
		}
	}

	if (eg_pi->dynamic_ac_timing) {
		wet = btc_initiawize_mc_weg_tabwe(wdev);
		if (wet)
			eg_pi->dynamic_ac_timing = fawse;
	}

	if (wdev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS)
		wv770_enabwe_backbias(wdev, twue);

	if (pi->dynamic_ss)
		cypwess_enabwe_spwead_spectwum(wdev, twue);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, twue);

	wv770_setup_bsp(wdev);
	wv770_pwogwam_git(wdev);
	wv770_pwogwam_tp(wdev);
	wv770_pwogwam_tpp(wdev);
	wv770_pwogwam_sstp(wdev);
	wv770_pwogwam_engine_speed_pawametews(wdev);
	cypwess_enabwe_dispway_gap(wdev);
	wv770_pwogwam_vc(wdev);

	if (pi->dynamic_pcie_gen2)
		btc_enabwe_dynamic_pcie_gen2(wdev, twue);

	wet = wv770_upwoad_fiwmwawe(wdev);
	if (wet) {
		DWM_EWWOW("wv770_upwoad_fiwmwawe faiwed\n");
		wetuwn wet;
	}
	wet = cypwess_get_tabwe_wocations(wdev);
	if (wet) {
		DWM_EWWOW("cypwess_get_tabwe_wocations faiwed\n");
		wetuwn wet;
	}
	wet = btc_init_smc_tabwe(wdev, boot_ps);
	if (wet)
		wetuwn wet;

	if (eg_pi->dynamic_ac_timing) {
		wet = cypwess_popuwate_mc_weg_tabwe(wdev, boot_ps);
		if (wet) {
			DWM_EWWOW("cypwess_popuwate_mc_weg_tabwe faiwed\n");
			wetuwn wet;
		}
	}

	cypwess_pwogwam_wesponse_times(wdev);
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
		btc_cg_cwock_gating_enabwe(wdev, twue);

	if (pi->mg_cwock_gating)
		btc_mg_cwock_gating_enabwe(wdev, twue);

	if (eg_pi->ws_cwock_gating)
		btc_ws_cwock_gating_enabwe(wdev, twue);

	wv770_enabwe_auto_thwottwe_souwce(wdev, WADEON_DPM_AUTO_THWOTTWE_SWC_THEWMAW, twue);

	btc_init_stuttew_mode(wdev);

	btc_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);

	wetuwn 0;
};

void btc_dpm_disabwe(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi = wv770_get_pi(wdev);
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);

	if (!btc_dpm_enabwed(wdev))
		wetuwn;

	wv770_cweaw_vc(wdev);

	if (pi->thewmaw_pwotection)
		wv770_enabwe_thewmaw_pwotection(wdev, fawse);

	if (pi->dynamic_pcie_gen2)
		btc_enabwe_dynamic_pcie_gen2(wdev, fawse);

	if (wdev->iwq.instawwed &&
	    w600_is_intewnaw_thewmaw_sensow(wdev->pm.int_thewmaw_type)) {
		wdev->iwq.dpm_thewmaw = fawse;
		wadeon_iwq_set(wdev);
	}

	if (pi->gfx_cwock_gating)
		btc_cg_cwock_gating_enabwe(wdev, fawse);

	if (pi->mg_cwock_gating)
		btc_mg_cwock_gating_enabwe(wdev, fawse);

	if (eg_pi->ws_cwock_gating)
		btc_ws_cwock_gating_enabwe(wdev, fawse);

	wv770_stop_dpm(wdev);
	btc_weset_to_defauwt(wdev);
	btc_stop_smc(wdev);
	cypwess_enabwe_spwead_spectwum(wdev, fawse);

	btc_update_cuwwent_ps(wdev, wdev->pm.dpm.boot_ps);
}

void btc_dpm_setup_asic(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	int w;

	w = ni_mc_woad_micwocode(wdev);
	if (w)
		DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
	wv770_get_memowy_type(wdev);
	wv740_wead_cwock_wegistews(wdev);
	btc_wead_awb_wegistews(wdev);
	wv770_wead_vowtage_smio_wegistews(wdev);

	if (eg_pi->pcie_pewfowmance_wequest)
		cypwess_advewtise_gen2_capabiwity(wdev);

	wv770_get_pcie_gen2_status(wdev);
	wv770_enabwe_acpi_pm(wdev);
}

int btc_dpm_init(stwuct wadeon_device *wdev)
{
	stwuct wv7xx_powew_info *pi;
	stwuct evewgween_powew_info *eg_pi;
	stwuct atom_cwock_dividews dividews;
	int wet;

	eg_pi = kzawwoc(sizeof(stwuct evewgween_powew_info), GFP_KEWNEW);
	if (eg_pi == NUWW)
		wetuwn -ENOMEM;
	wdev->pm.dpm.pwiv = eg_pi;
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

	wet = wv7xx_pawse_powew_tabwe(wdev);
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
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[1].v = 800;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[2].cwk = 54000;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[2].v = 800;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[3].cwk = 72000;
	wdev->pm.dpm.dyn_state.vddc_dependency_on_dispcwk.entwies[3].v = 800;

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

	pi->mcwk_stwobe_mode_thweshowd = 40000;
	pi->mcwk_edc_enabwe_thweshowd = 40000;
	eg_pi->mcwk_edc_ww_enabwe_thweshowd = 40000;

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

	if (wdev->fwags & WADEON_IS_MOBIWITY)
		pi->dcodt = twue;
	ewse
		pi->dcodt = fawse;

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

	if (wdev->famiwy == CHIP_BAWTS)
		eg_pi->dww_defauwt_on = twue;
	ewse
		eg_pi->dww_defauwt_on = fawse;

	eg_pi->scwk_deep_sweep = fawse;
	if (ASIC_IS_WOMBOK(wdev))
		pi->mcwk_stuttew_mode_thweshowd = 30000;
	ewse
		pi->mcwk_stuttew_mode_thweshowd = 0;

	pi->swam_end = SMC_WAM_END;

	wdev->pm.dpm.dyn_state.mcwk_scwk_watio = 4;
	wdev->pm.dpm.dyn_state.vddc_vddci_dewta = 200;
	wdev->pm.dpm.dyn_state.min_vddc_fow_pcie_gen2 = 900;
	wdev->pm.dpm.dyn_state.vawid_scwk_vawues.count = AWWAY_SIZE(btc_vawid_scwk);
	wdev->pm.dpm.dyn_state.vawid_scwk_vawues.vawues = btc_vawid_scwk;
	wdev->pm.dpm.dyn_state.vawid_mcwk_vawues.count = 0;
	wdev->pm.dpm.dyn_state.vawid_mcwk_vawues.vawues = NUWW;

	if (wdev->famiwy == CHIP_TUWKS)
		wdev->pm.dpm.dyn_state.scwk_mcwk_dewta = 15000;
	ewse
		wdev->pm.dpm.dyn_state.scwk_mcwk_dewta = 10000;

	/* make suwe dc wimits awe vawid */
	if ((wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.scwk == 0) ||
	    (wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.mcwk == 0))
		wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc =
			wdev->pm.dpm.dyn_state.max_cwock_vowtage_on_ac;

	wetuwn 0;
}

void btc_dpm_fini(stwuct wadeon_device *wdev)
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

void btc_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(stwuct wadeon_device *wdev,
						     stwuct seq_fiwe *m)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		seq_pwintf(m, "invawid dpm pwofiwe %d\n", cuwwent_index);
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		seq_pwintf(m, "uvd    vcwk: %d dcwk: %d\n", wps->vcwk, wps->dcwk);
		seq_pwintf(m, "powew wevew %d    scwk: %u mcwk: %u vddc: %u vddci: %u\n",
			   cuwwent_index, pw->scwk, pw->mcwk, pw->vddc, pw->vddci);
	}
}

u32 btc_dpm_get_cuwwent_scwk(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		wetuwn 0;
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		wetuwn pw->scwk;
	}
}

u32 btc_dpm_get_cuwwent_mcwk(stwuct wadeon_device *wdev)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wadeon_ps *wps = &eg_pi->cuwwent_wps;
	stwuct wv7xx_ps *ps = wv770_get_ps(wps);
	stwuct wv7xx_pw *pw;
	u32 cuwwent_index =
		(WWEG32(TAWGET_AND_CUWWENT_PWOFIWE_INDEX) & CUWWENT_PWOFIWE_INDEX_MASK) >>
		CUWWENT_PWOFIWE_INDEX_SHIFT;

	if (cuwwent_index > 2) {
		wetuwn 0;
	} ewse {
		if (cuwwent_index == 0)
			pw = &ps->wow;
		ewse if (cuwwent_index == 1)
			pw = &ps->medium;
		ewse /* cuwwent_index == 2 */
			pw = &ps->high;
		wetuwn pw->mcwk;
	}
}

u32 btc_dpm_get_scwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_ps *wequested_state = wv770_get_ps(&eg_pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->wow.scwk;
	ewse
		wetuwn wequested_state->high.scwk;
}

u32 btc_dpm_get_mcwk(stwuct wadeon_device *wdev, boow wow)
{
	stwuct evewgween_powew_info *eg_pi = evewgween_get_pi(wdev);
	stwuct wv7xx_ps *wequested_state = wv770_get_ps(&eg_pi->wequested_wps);

	if (wow)
		wetuwn wequested_state->wow.mcwk;
	ewse
		wetuwn wequested_state->high.mcwk;
}
