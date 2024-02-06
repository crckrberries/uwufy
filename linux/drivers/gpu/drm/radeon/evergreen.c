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
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "atom.h"
#incwude "avivod.h"
#incwude "cik.h"
#incwude "ni.h"
#incwude "wv770.h"
#incwude "evewgween.h"
#incwude "evewgween_bwit_shadews.h"
#incwude "evewgween_weg.h"
#incwude "evewgweend.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "wadeon_ucode.h"
#incwude "si.h"

#define DC_HPDx_CONTWOW(x)        (DC_HPD1_CONTWOW     + (x * 0xc))
#define DC_HPDx_INT_CONTWOW(x)    (DC_HPD1_INT_CONTWOW + (x * 0xc))
#define DC_HPDx_INT_STATUS_WEG(x) (DC_HPD1_INT_STATUS  + (x * 0xc))

/*
 * Indiwect wegistews accessow
 */
u32 eg_cg_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->cg_idx_wock, fwags);
	WWEG32(EVEWGWEEN_CG_IND_ADDW, ((weg) & 0xffff));
	w = WWEG32(EVEWGWEEN_CG_IND_DATA);
	spin_unwock_iwqwestowe(&wdev->cg_idx_wock, fwags);
	wetuwn w;
}

void eg_cg_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->cg_idx_wock, fwags);
	WWEG32(EVEWGWEEN_CG_IND_ADDW, ((weg) & 0xffff));
	WWEG32(EVEWGWEEN_CG_IND_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->cg_idx_wock, fwags);
}

u32 eg_pif_phy0_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->pif_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY0_INDEX, ((weg) & 0xffff));
	w = WWEG32(EVEWGWEEN_PIF_PHY0_DATA);
	spin_unwock_iwqwestowe(&wdev->pif_idx_wock, fwags);
	wetuwn w;
}

void eg_pif_phy0_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->pif_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY0_INDEX, ((weg) & 0xffff));
	WWEG32(EVEWGWEEN_PIF_PHY0_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->pif_idx_wock, fwags);
}

u32 eg_pif_phy1_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->pif_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY1_INDEX, ((weg) & 0xffff));
	w = WWEG32(EVEWGWEEN_PIF_PHY1_DATA);
	spin_unwock_iwqwestowe(&wdev->pif_idx_wock, fwags);
	wetuwn w;
}

void eg_pif_phy1_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->pif_idx_wock, fwags);
	WWEG32(EVEWGWEEN_PIF_PHY1_INDEX, ((weg) & 0xffff));
	WWEG32(EVEWGWEEN_PIF_PHY1_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->pif_idx_wock, fwags);
}

static const u32 cwtc_offsets[6] =
{
	EVEWGWEEN_CWTC0_WEGISTEW_OFFSET,
	EVEWGWEEN_CWTC1_WEGISTEW_OFFSET,
	EVEWGWEEN_CWTC2_WEGISTEW_OFFSET,
	EVEWGWEEN_CWTC3_WEGISTEW_OFFSET,
	EVEWGWEEN_CWTC4_WEGISTEW_OFFSET,
	EVEWGWEEN_CWTC5_WEGISTEW_OFFSET
};

#incwude "cweawstate_evewgween.h"

static const u32 sumo_wwc_save_westowe_wegistew_wist[] =
{
	0x98fc,
	0x9830,
	0x9834,
	0x9838,
	0x9870,
	0x9874,
	0x8a14,
	0x8b24,
	0x8bcc,
	0x8b10,
	0x8d00,
	0x8d04,
	0x8c00,
	0x8c04,
	0x8c08,
	0x8c0c,
	0x8d8c,
	0x8c20,
	0x8c24,
	0x8c28,
	0x8c18,
	0x8c1c,
	0x8cf0,
	0x8e2c,
	0x8e38,
	0x8c30,
	0x9508,
	0x9688,
	0x9608,
	0x960c,
	0x9610,
	0x9614,
	0x88c4,
	0x88d4,
	0xa008,
	0x900c,
	0x9100,
	0x913c,
	0x98f8,
	0x98f4,
	0x9b7c,
	0x3f8c,
	0x8950,
	0x8954,
	0x8a18,
	0x8b28,
	0x9144,
	0x9148,
	0x914c,
	0x3f90,
	0x3f94,
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
	0x9150,
	0x802c,
};

static void evewgween_gpu_init(stwuct wadeon_device *wdev);
void evewgween_fini(stwuct wadeon_device *wdev);
void evewgween_pcie_gen2_enabwe(stwuct wadeon_device *wdev);
void evewgween_pwogwam_aspm(stwuct wadeon_device *wdev);

static const u32 evewgween_gowden_wegistews[] =
{
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b10, 0xffffffff, 0x00000000,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0xffffffff, 0x001000f0,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x10830, 0xffffffff, 0x00000011,
	0x11430, 0xffffffff, 0x00000011,
	0x12030, 0xffffffff, 0x00000011,
	0x12c30, 0xffffffff, 0x00000011,
	0xd02c, 0xffffffff, 0x08421000,
	0x240c, 0xffffffff, 0x00000380,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x28a4c, 0x06000000, 0x06000000,
	0x10c, 0x00000001, 0x00000001,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8cf0, 0xffffffff, 0x08e00620,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x28350, 0xffffffff, 0x00000000,
	0xa008, 0xffffffff, 0x00010000,
	0x5c4, 0xffffffff, 0x00000001,
	0x9508, 0xffffffff, 0x00000002,
	0x913c, 0x0000000f, 0x0000000a
};

static const u32 evewgween_gowden_wegistews2[] =
{
	0x2f4c, 0xffffffff, 0x00000000,
	0x54f4, 0xffffffff, 0x00000000,
	0x54f0, 0xffffffff, 0x00000000,
	0x5498, 0xffffffff, 0x00000000,
	0x549c, 0xffffffff, 0x00000000,
	0x5494, 0xffffffff, 0x00000000,
	0x53cc, 0xffffffff, 0x00000000,
	0x53c8, 0xffffffff, 0x00000000,
	0x53c4, 0xffffffff, 0x00000000,
	0x53c0, 0xffffffff, 0x00000000,
	0x53bc, 0xffffffff, 0x00000000,
	0x53b8, 0xffffffff, 0x00000000,
	0x53b4, 0xffffffff, 0x00000000,
	0x53b0, 0xffffffff, 0x00000000
};

static const u32 cypwess_mgcg_init[] =
{
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0x40010000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
};

static const u32 wedwood_mgcg_init[] =
{
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
};

static const u32 cedaw_gowden_wegistews[] =
{
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b10, 0xffffffff, 0x00000000,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000000,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0xffffffff, 0x001000f0,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x10830, 0xffffffff, 0x00000011,
	0x11430, 0xffffffff, 0x00000011,
	0xd02c, 0xffffffff, 0x08421000,
	0x240c, 0xffffffff, 0x00000380,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x28a4c, 0x06000000, 0x06000000,
	0x10c, 0x00000001, 0x00000001,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8cf0, 0xffffffff, 0x08e00410,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x28350, 0xffffffff, 0x00000000,
	0xa008, 0xffffffff, 0x00010000,
	0x5c4, 0xffffffff, 0x00000001,
	0x9508, 0xffffffff, 0x00000002
};

static const u32 cedaw_mgcg_init[] =
{
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9178, 0xffffffff, 0x00050000,
	0x917c, 0xffffffff, 0x00030002,
	0x918c, 0xffffffff, 0x00010004,
	0x9190, 0xffffffff, 0x00070006,
	0x9194, 0xffffffff, 0x00050000,
	0x9198, 0xffffffff, 0x00030002,
	0x91a8, 0xffffffff, 0x00010004,
	0x91ac, 0xffffffff, 0x00070006,
	0x91e8, 0xffffffff, 0x00000000,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000
};

static const u32 junipew_mgcg_init[] =
{
	0x802c, 0xffffffff, 0xc0000000,
	0x5448, 0xffffffff, 0x00000100,
	0x55e4, 0xffffffff, 0x00000100,
	0x160c, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0xc164, 0xffffffff, 0x00000100,
	0x8a18, 0xffffffff, 0x00000100,
	0x897c, 0xffffffff, 0x06000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9a60, 0xffffffff, 0x00000100,
	0x9868, 0xffffffff, 0x00000100,
	0x8d58, 0xffffffff, 0x00000100,
	0x9510, 0xffffffff, 0x00000100,
	0x949c, 0xffffffff, 0x00000100,
	0x9654, 0xffffffff, 0x00000100,
	0x9030, 0xffffffff, 0x00000100,
	0x9034, 0xffffffff, 0x00000100,
	0x9038, 0xffffffff, 0x00000100,
	0x903c, 0xffffffff, 0x00000100,
	0x9040, 0xffffffff, 0x00000100,
	0xa200, 0xffffffff, 0x00000100,
	0xa204, 0xffffffff, 0x00000100,
	0xa208, 0xffffffff, 0x00000100,
	0xa20c, 0xffffffff, 0x00000100,
	0x971c, 0xffffffff, 0x00000100,
	0xd0c0, 0xffffffff, 0xff000100,
	0x802c, 0xffffffff, 0x40000000,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x9178, 0xffffffff, 0x00070000,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x918c, 0xffffffff, 0x00010006,
	0x9190, 0xffffffff, 0x00090008,
	0x9194, 0xffffffff, 0x00070000,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91a8, 0xffffffff, 0x00010006,
	0x91ac, 0xffffffff, 0x00090008,
	0x91b0, 0xffffffff, 0x00070000,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91c4, 0xffffffff, 0x00010006,
	0x91c8, 0xffffffff, 0x00090008,
	0x91cc, 0xffffffff, 0x00070000,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91e0, 0xffffffff, 0x00010006,
	0x91e4, 0xffffffff, 0x00090008,
	0x91e8, 0xffffffff, 0x00000000,
	0x91ec, 0xffffffff, 0x00070000,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x9200, 0xffffffff, 0x00010006,
	0x9204, 0xffffffff, 0x00090008,
	0x9208, 0xffffffff, 0x00070000,
	0x920c, 0xffffffff, 0x00030002,
	0x9210, 0xffffffff, 0x00050004,
	0x921c, 0xffffffff, 0x00010006,
	0x9220, 0xffffffff, 0x00090008,
	0x9224, 0xffffffff, 0x00070000,
	0x9228, 0xffffffff, 0x00030002,
	0x922c, 0xffffffff, 0x00050004,
	0x9238, 0xffffffff, 0x00010006,
	0x923c, 0xffffffff, 0x00090008,
	0x9240, 0xffffffff, 0x00070000,
	0x9244, 0xffffffff, 0x00030002,
	0x9248, 0xffffffff, 0x00050004,
	0x9254, 0xffffffff, 0x00010006,
	0x9258, 0xffffffff, 0x00090008,
	0x925c, 0xffffffff, 0x00070000,
	0x9260, 0xffffffff, 0x00030002,
	0x9264, 0xffffffff, 0x00050004,
	0x9270, 0xffffffff, 0x00010006,
	0x9274, 0xffffffff, 0x00090008,
	0x9278, 0xffffffff, 0x00070000,
	0x927c, 0xffffffff, 0x00030002,
	0x9280, 0xffffffff, 0x00050004,
	0x928c, 0xffffffff, 0x00010006,
	0x9290, 0xffffffff, 0x00090008,
	0x9294, 0xffffffff, 0x00000000,
	0x929c, 0xffffffff, 0x00000001,
	0x802c, 0xffffffff, 0xc0000000,
	0x977c, 0xffffffff, 0x00000100,
	0x3f80, 0xffffffff, 0x00000100,
	0xa210, 0xffffffff, 0x00000100,
	0xa214, 0xffffffff, 0x00000100,
	0x4d8, 0xffffffff, 0x00000100,
	0x9784, 0xffffffff, 0x00000100,
	0x9698, 0xffffffff, 0x00000100,
	0x4d4, 0xffffffff, 0x00000200,
	0x30cc, 0xffffffff, 0x00000100,
	0x802c, 0xffffffff, 0xc0000000
};

static const u32 supewsumo_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5c4, 0xffffffff, 0x00000001,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x8c04, 0xffffffff, 0x40600060,
	0x8c08, 0xffffffff, 0x001c001c,
	0x8c20, 0xffffffff, 0x00800080,
	0x8c24, 0xffffffff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0xffffffff, 0x00001010,
	0x918c, 0xffffffff, 0x00010006,
	0x91a8, 0xffffffff, 0x00010006,
	0x91c4, 0xffffffff, 0x00010006,
	0x91e0, 0xffffffff, 0x00010006,
	0x9200, 0xffffffff, 0x00010006,
	0x9150, 0xffffffff, 0x6e944040,
	0x917c, 0xffffffff, 0x00030002,
	0x9180, 0xffffffff, 0x00050004,
	0x9198, 0xffffffff, 0x00030002,
	0x919c, 0xffffffff, 0x00050004,
	0x91b4, 0xffffffff, 0x00030002,
	0x91b8, 0xffffffff, 0x00050004,
	0x91d0, 0xffffffff, 0x00030002,
	0x91d4, 0xffffffff, 0x00050004,
	0x91f0, 0xffffffff, 0x00030002,
	0x91f4, 0xffffffff, 0x00050004,
	0x915c, 0xffffffff, 0x00010000,
	0x9160, 0xffffffff, 0x00030002,
	0x3f90, 0xffff0000, 0xff000000,
	0x9178, 0xffffffff, 0x00070000,
	0x9194, 0xffffffff, 0x00070000,
	0x91b0, 0xffffffff, 0x00070000,
	0x91cc, 0xffffffff, 0x00070000,
	0x91ec, 0xffffffff, 0x00070000,
	0x9148, 0xffff0000, 0xff000000,
	0x9190, 0xffffffff, 0x00090008,
	0x91ac, 0xffffffff, 0x00090008,
	0x91c8, 0xffffffff, 0x00090008,
	0x91e4, 0xffffffff, 0x00090008,
	0x9204, 0xffffffff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0xffffffff, 0x00000001,
	0x8a18, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x5644, 0xffffffff, 0x00000100,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8030, 0xffffffff, 0x0000100a,
	0x8a14, 0xffffffff, 0x00000007,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x8b10, 0xffffffff, 0x00000000,
	0x28a4c, 0x06000000, 0x06000000,
	0x4d8, 0xffffffff, 0x00000100,
	0x913c, 0xffff000f, 0x0100000a,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5e78, 0xffffffff, 0x001000f0,
	0xd02c, 0xffffffff, 0x08421000,
	0xa008, 0xffffffff, 0x00010000,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8cf0, 0x1fffffff, 0x08e00620,
	0x28350, 0xffffffff, 0x00000000,
	0x9508, 0xffffffff, 0x00000002
};

static const u32 sumo_gowden_wegistews[] =
{
	0x900c, 0x00ffffff, 0x0017071f,
	0x8c18, 0xffffffff, 0x10101060,
	0x8c1c, 0xffffffff, 0x00001010,
	0x8c30, 0x0000000f, 0x00000005,
	0x9688, 0x0000000f, 0x00000007
};

static const u32 wwestwew_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5c4, 0xffffffff, 0x00000001,
	0x7030, 0xffffffff, 0x00000011,
	0x7c30, 0xffffffff, 0x00000011,
	0x6104, 0x01000300, 0x00000000,
	0x5bc0, 0x00300000, 0x00000000,
	0x918c, 0xffffffff, 0x00010006,
	0x91a8, 0xffffffff, 0x00010006,
	0x9150, 0xffffffff, 0x6e944040,
	0x917c, 0xffffffff, 0x00030002,
	0x9198, 0xffffffff, 0x00030002,
	0x915c, 0xffffffff, 0x00010000,
	0x3f90, 0xffff0000, 0xff000000,
	0x9178, 0xffffffff, 0x00070000,
	0x9194, 0xffffffff, 0x00070000,
	0x9148, 0xffff0000, 0xff000000,
	0x9190, 0xffffffff, 0x00090008,
	0x91ac, 0xffffffff, 0x00090008,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0x929c, 0xffffffff, 0x00000001,
	0x8a18, 0xffffffff, 0x00000100,
	0x8b28, 0xffffffff, 0x00000100,
	0x9144, 0xffffffff, 0x00000100,
	0x9b7c, 0xffffffff, 0x00000000,
	0x8030, 0xffffffff, 0x0000100a,
	0x8a14, 0xffffffff, 0x00000001,
	0x8b24, 0xffffffff, 0x00ff0fff,
	0x8b10, 0xffffffff, 0x00000000,
	0x28a4c, 0x06000000, 0x06000000,
	0x4d8, 0xffffffff, 0x00000100,
	0x913c, 0xffff000f, 0x0100000a,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0xffffffff, 0x000000c2,
	0x88d4, 0xffffffff, 0x00000010,
	0x8974, 0xffffffff, 0x00000000,
	0xc78, 0x00000080, 0x00000080,
	0x5e78, 0xffffffff, 0x001000f0,
	0xd02c, 0xffffffff, 0x08421000,
	0xa008, 0xffffffff, 0x00010000,
	0x8d00, 0xffffffff, 0x100e4848,
	0x8d04, 0xffffffff, 0x00164745,
	0x8c00, 0xffffffff, 0xe4000003,
	0x8cf0, 0x1fffffff, 0x08e00410,
	0x28350, 0xffffffff, 0x00000000,
	0x9508, 0xffffffff, 0x00000002,
	0x900c, 0xffffffff, 0x0017071f,
	0x8c18, 0xffffffff, 0x10101060,
	0x8c1c, 0xffffffff, 0x00001010
};

static const u32 bawts_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x3f90, 0xffff0000, 0xff000000,
	0x9148, 0xffff0000, 0xff000000,
	0x3f94, 0xffff0000, 0xff000000,
	0x914c, 0xffff0000, 0xff000000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x70073777, 0x00010001,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02011003,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02011003,
	0x98fc, 0xffffffff, 0x76543210,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x00000007, 0x02011003,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00620,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
};

static const u32 tuwks_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x8c8, 0x00003000, 0x00001070,
	0x8cc, 0x000fffff, 0x00040035,
	0x3f90, 0xffff0000, 0xfff00000,
	0x9148, 0xffff0000, 0xfff00000,
	0x3f94, 0xffff0000, 0xfff00000,
	0x914c, 0xffff0000, 0xfff00000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x00073007, 0x00010002,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02010002,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x00010002,
	0x98fc, 0xffffffff, 0x33221100,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x00010002,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000007,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
};

static const u32 caicos_gowden_wegistews[] =
{
	0x5eb4, 0xffffffff, 0x00000002,
	0x5e78, 0x8f311ff1, 0x001000f0,
	0x8c8, 0x00003420, 0x00001450,
	0x8cc, 0x000fffff, 0x00040035,
	0x3f90, 0xffff0000, 0xfffc0000,
	0x9148, 0xffff0000, 0xfffc0000,
	0x3f94, 0xffff0000, 0xfffc0000,
	0x914c, 0xffff0000, 0xfffc0000,
	0xc78, 0x00000080, 0x00000080,
	0xbd4, 0x00073007, 0x00010001,
	0xd02c, 0xbfffff1f, 0x08421000,
	0xd0b8, 0x03773777, 0x02010001,
	0x5bc0, 0x00200000, 0x50100000,
	0x98f8, 0x33773777, 0x02010001,
	0x98fc, 0xffffffff, 0x33221100,
	0x7030, 0x31000311, 0x00000011,
	0x2f48, 0x33773777, 0x02010001,
	0x6b28, 0x00000010, 0x00000012,
	0x7728, 0x00000010, 0x00000012,
	0x10328, 0x00000010, 0x00000012,
	0x10f28, 0x00000010, 0x00000012,
	0x11b28, 0x00000010, 0x00000012,
	0x12728, 0x00000010, 0x00000012,
	0x240c, 0x000007ff, 0x00000380,
	0x8a14, 0xf000001f, 0x00000001,
	0x8b24, 0x3fff3fff, 0x00ff0fff,
	0x8b10, 0x0000ff0f, 0x00000000,
	0x28a4c, 0x07ffffff, 0x06000000,
	0x10c, 0x00000001, 0x00010003,
	0xa02c, 0xffffffff, 0x0000009b,
	0x913c, 0x0000000f, 0x0100000a,
	0x8d00, 0xffff7f7f, 0x100e4848,
	0x8d04, 0x00ffffff, 0x00164745,
	0x8c00, 0xfffc0003, 0xe4000003,
	0x8c04, 0xf8ff00ff, 0x40600060,
	0x8c08, 0x00ff00ff, 0x001c001c,
	0x8cf0, 0x1fff1fff, 0x08e00410,
	0x8c20, 0x0fff0fff, 0x00800080,
	0x8c24, 0x0fff0fff, 0x00800080,
	0x8c18, 0xffffffff, 0x20202078,
	0x8c1c, 0x0000ffff, 0x00001010,
	0x28350, 0x00000f01, 0x00000000,
	0x9508, 0x3700001f, 0x00000002,
	0x960c, 0xffffffff, 0x54763210,
	0x88c4, 0x001f3ae3, 0x000000c2,
	0x88d4, 0x0000001f, 0x00000010,
	0x8974, 0xffffffff, 0x00000000
};

static void evewgween_init_gowden_wegistews(stwuct wadeon_device *wdev)
{
	switch (wdev->famiwy) {
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews2,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews2));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 cypwess_mgcg_init,
						 (const u32)AWWAY_SIZE(cypwess_mgcg_init));
		bweak;
	case CHIP_JUNIPEW:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews2,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews2));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 junipew_mgcg_init,
						 (const u32)AWWAY_SIZE(junipew_mgcg_init));
		bweak;
	case CHIP_WEDWOOD:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews2,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews2));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 wedwood_mgcg_init,
						 (const u32)AWWAY_SIZE(wedwood_mgcg_init));
		bweak;
	case CHIP_CEDAW:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 cedaw_gowden_wegistews,
						 (const u32)AWWAY_SIZE(cedaw_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 evewgween_gowden_wegistews2,
						 (const u32)AWWAY_SIZE(evewgween_gowden_wegistews2));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 cedaw_mgcg_init,
						 (const u32)AWWAY_SIZE(cedaw_mgcg_init));
		bweak;
	case CHIP_PAWM:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 wwestwew_gowden_wegistews,
						 (const u32)AWWAY_SIZE(wwestwew_gowden_wegistews));
		bweak;
	case CHIP_SUMO:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 supewsumo_gowden_wegistews,
						 (const u32)AWWAY_SIZE(supewsumo_gowden_wegistews));
		bweak;
	case CHIP_SUMO2:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 supewsumo_gowden_wegistews,
						 (const u32)AWWAY_SIZE(supewsumo_gowden_wegistews));
		wadeon_pwogwam_wegistew_sequence(wdev,
						 sumo_gowden_wegistews,
						 (const u32)AWWAY_SIZE(sumo_gowden_wegistews));
		bweak;
	case CHIP_BAWTS:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 bawts_gowden_wegistews,
						 (const u32)AWWAY_SIZE(bawts_gowden_wegistews));
		bweak;
	case CHIP_TUWKS:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 tuwks_gowden_wegistews,
						 (const u32)AWWAY_SIZE(tuwks_gowden_wegistews));
		bweak;
	case CHIP_CAICOS:
		wadeon_pwogwam_wegistew_sequence(wdev,
						 caicos_gowden_wegistews,
						 (const u32)AWWAY_SIZE(caicos_gowden_wegistews));
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * evewgween_get_awwowed_info_wegistew - fetch the wegistew fow the info ioctw
 *
 * @wdev: wadeon_device pointew
 * @weg: wegistew offset in bytes
 * @vaw: wegistew vawue
 *
 * Wetuwns 0 fow success ow -EINVAW fow an invawid wegistew
 *
 */
int evewgween_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
					u32 weg, u32 *vaw)
{
	switch (weg) {
	case GWBM_STATUS:
	case GWBM_STATUS_SE0:
	case GWBM_STATUS_SE1:
	case SWBM_STATUS:
	case SWBM_STATUS2:
	case DMA_STATUS_WEG:
	case UVD_STATUS:
		*vaw = WWEG32(weg);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

void evewgween_tiwing_fiewds(unsigned tiwing_fwags, unsigned *bankw,
			     unsigned *bankh, unsigned *mtaspect,
			     unsigned *tiwe_spwit)
{
	*bankw = (tiwing_fwags >> WADEON_TIWING_EG_BANKW_SHIFT) & WADEON_TIWING_EG_BANKW_MASK;
	*bankh = (tiwing_fwags >> WADEON_TIWING_EG_BANKH_SHIFT) & WADEON_TIWING_EG_BANKH_MASK;
	*mtaspect = (tiwing_fwags >> WADEON_TIWING_EG_MACWO_TIWE_ASPECT_SHIFT) & WADEON_TIWING_EG_MACWO_TIWE_ASPECT_MASK;
	*tiwe_spwit = (tiwing_fwags >> WADEON_TIWING_EG_TIWE_SPWIT_SHIFT) & WADEON_TIWING_EG_TIWE_SPWIT_MASK;
	switch (*bankw) {
	defauwt:
	case 1: *bankw = EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_1; bweak;
	case 2: *bankw = EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_2; bweak;
	case 4: *bankw = EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_4; bweak;
	case 8: *bankw = EVEWGWEEN_ADDW_SUWF_BANK_WIDTH_8; bweak;
	}
	switch (*bankh) {
	defauwt:
	case 1: *bankh = EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_1; bweak;
	case 2: *bankh = EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_2; bweak;
	case 4: *bankh = EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_4; bweak;
	case 8: *bankh = EVEWGWEEN_ADDW_SUWF_BANK_HEIGHT_8; bweak;
	}
	switch (*mtaspect) {
	defauwt:
	case 1: *mtaspect = EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_1; bweak;
	case 2: *mtaspect = EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_2; bweak;
	case 4: *mtaspect = EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_4; bweak;
	case 8: *mtaspect = EVEWGWEEN_ADDW_SUWF_MACWO_TIWE_ASPECT_8; bweak;
	}
}

static int sumo_set_uvd_cwock(stwuct wadeon_device *wdev, u32 cwock,
			      u32 cntw_weg, u32 status_weg)
{
	int w, i;
	stwuct atom_cwock_dividews dividews;

	w = wadeon_atom_get_cwock_dividews(wdev, COMPUTE_ENGINE_PWW_PAWAM,
					   cwock, fawse, &dividews);
	if (w)
		wetuwn w;

	WWEG32_P(cntw_weg, dividews.post_div, ~(DCWK_DIW_CNTW_EN|DCWK_DIVIDEW_MASK));

	fow (i = 0; i < 100; i++) {
		if (WWEG32(status_weg) & DCWK_STATUS)
			bweak;
		mdeway(10);
	}
	if (i == 100)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

int sumo_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk)
{
	int w = 0;
	u32 cg_scwatch = WWEG32(CG_SCWATCH1);

	w = sumo_set_uvd_cwock(wdev, vcwk, CG_VCWK_CNTW, CG_VCWK_STATUS);
	if (w)
		goto done;
	cg_scwatch &= 0xffff0000;
	cg_scwatch |= vcwk / 100; /* Mhz */

	w = sumo_set_uvd_cwock(wdev, dcwk, CG_DCWK_CNTW, CG_DCWK_STATUS);
	if (w)
		goto done;
	cg_scwatch &= 0x0000ffff;
	cg_scwatch |= (dcwk / 100) << 16; /* Mhz */

done:
	WWEG32(CG_SCWATCH1, cg_scwatch);

	wetuwn w;
}

int evewgween_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk)
{
	/* stawt off with something wawge */
	unsigned fb_div = 0, vcwk_div = 0, dcwk_div = 0;
	int w;

	/* bypass vcwk and dcwk with bcwk */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		VCWK_SWC_SEW(1) | DCWK_SWC_SEW(1),
		~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	/* put PWW in bypass mode */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_BYPASS_EN_MASK, ~UPWW_BYPASS_EN_MASK);

	if (!vcwk || !dcwk) {
		/* keep the Bypass mode, put PWW to sweep */
		WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_SWEEP_MASK, ~UPWW_SWEEP_MASK);
		wetuwn 0;
	}

	w = wadeon_uvd_cawc_upww_dividews(wdev, vcwk, dcwk, 125000, 250000,
					  16384, 0x03FFFFFF, 0, 128, 5,
					  &fb_div, &vcwk_div, &dcwk_div);
	if (w)
		wetuwn w;

	/* set VCO_MODE to 1 */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_VCO_MODE_MASK, ~UPWW_VCO_MODE_MASK);

	/* toggwe UPWW_SWEEP to 1 then back to 0 */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_SWEEP_MASK, ~UPWW_SWEEP_MASK);
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_SWEEP_MASK);

	/* deassewt UPWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WESET_MASK);

	mdeway(1);

	w = wadeon_uvd_send_upww_ctwweq(wdev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* assewt UPWW_WESET again */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_WESET_MASK, ~UPWW_WESET_MASK);

	/* disabwe spwead spectwum. */
	WWEG32_P(CG_UPWW_SPWEAD_SPECTWUM, 0, ~SSEN_MASK);

	/* set feedback dividew */
	WWEG32_P(CG_UPWW_FUNC_CNTW_3, UPWW_FB_DIV(fb_div), ~UPWW_FB_DIV_MASK);

	/* set wef dividew to 0 */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WEF_DIV_MASK);

	if (fb_div < 307200)
		WWEG32_P(CG_UPWW_FUNC_CNTW_4, 0, ~UPWW_SPAWE_ISPAWE9);
	ewse
		WWEG32_P(CG_UPWW_FUNC_CNTW_4, UPWW_SPAWE_ISPAWE9, ~UPWW_SPAWE_ISPAWE9);

	/* set PDIV_A and PDIV_B */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		UPWW_PDIV_A(vcwk_div) | UPWW_PDIV_B(dcwk_div),
		~(UPWW_PDIV_A_MASK | UPWW_PDIV_B_MASK));

	/* give the PWW some time to settwe */
	mdeway(15);

	/* deassewt PWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WESET_MASK);

	mdeway(15);

	/* switch fwom bypass mode to nowmaw mode */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_BYPASS_EN_MASK);

	w = wadeon_uvd_send_upww_ctwweq(wdev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* switch VCWK and DCWK sewection */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		VCWK_SWC_SEW(2) | DCWK_SWC_SEW(2),
		~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	mdeway(100);

	wetuwn 0;
}

void evewgween_fix_pci_max_wead_weq_size(stwuct wadeon_device *wdev)
{
	int weadwq;
	u16 v;

	weadwq = pcie_get_weadwq(wdev->pdev);
	v = ffs(weadwq) - 8;
	/* if bios ow OS sets MAX_WEAD_WEQUEST_SIZE to an invawid vawue, fix it
	 * to avoid hangs ow pewfomance issues
	 */
	if ((v == 0) || (v == 6) || (v == 7))
		pcie_set_weadwq(wdev->pdev, 512);
}

void dce4_pwogwam_fmt(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(encodew->cwtc);
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	int bpc = 0;
	u32 tmp = 0;
	enum wadeon_connectow_dithew dithew = WADEON_FMT_DITHEW_DISABWE;

	if (connectow) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		bpc = wadeon_get_monitow_bpc(connectow);
		dithew = wadeon_connectow->dithew;
	}

	/* WVDS/eDP FMT is set up by atom */
	if (wadeon_encodew->devices & ATOM_DEVICE_WCD_SUPPOWT)
		wetuwn;

	/* not needed fow anawog */
	if ((wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC1) ||
	    (wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC2))
		wetuwn;

	if (bpc == 0)
		wetuwn;

	switch (bpc) {
	case 6:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (FMT_FWAME_WANDOM_ENABWE | FMT_HIGHPASS_WANDOM_ENABWE |
				FMT_SPATIAW_DITHEW_EN);
		ewse
			tmp |= FMT_TWUNCATE_EN;
		bweak;
	case 8:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (FMT_FWAME_WANDOM_ENABWE | FMT_HIGHPASS_WANDOM_ENABWE |
				FMT_WGB_WANDOM_ENABWE |
				FMT_SPATIAW_DITHEW_EN | FMT_SPATIAW_DITHEW_DEPTH);
		ewse
			tmp |= (FMT_TWUNCATE_EN | FMT_TWUNCATE_DEPTH);
		bweak;
	case 10:
	defauwt:
		/* not needed */
		bweak;
	}

	WWEG32(FMT_BIT_DEPTH_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
}

static boow dce4_is_in_vbwank(stwuct wadeon_device *wdev, int cwtc)
{
	if (WWEG32(EVEWGWEEN_CWTC_STATUS + cwtc_offsets[cwtc]) & EVEWGWEEN_CWTC_V_BWANK)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow dce4_is_countew_moving(stwuct wadeon_device *wdev, int cwtc)
{
	u32 pos1, pos2;

	pos1 = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION + cwtc_offsets[cwtc]);
	pos2 = WWEG32(EVEWGWEEN_CWTC_STATUS_POSITION + cwtc_offsets[cwtc]);

	if (pos1 != pos2)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * dce4_wait_fow_vbwank - vbwank wait asic cawwback.
 *
 * @wdev: wadeon_device pointew
 * @cwtc: cwtc to wait fow vbwank on
 *
 * Wait fow vbwank on the wequested cwtc (evewgween+).
 */
void dce4_wait_fow_vbwank(stwuct wadeon_device *wdev, int cwtc)
{
	unsigned i = 0;

	if (cwtc >= wdev->num_cwtc)
		wetuwn;

	if (!(WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[cwtc]) & EVEWGWEEN_CWTC_MASTEW_EN))
		wetuwn;

	/* depending on when we hit vbwank, we may be cwose to active; if so,
	 * wait fow anothew fwame.
	 */
	whiwe (dce4_is_in_vbwank(wdev, cwtc)) {
		if (i++ % 100 == 0) {
			if (!dce4_is_countew_moving(wdev, cwtc))
				bweak;
		}
	}

	whiwe (!dce4_is_in_vbwank(wdev, cwtc)) {
		if (i++ % 100 == 0) {
			if (!dce4_is_countew_moving(wdev, cwtc))
				bweak;
		}
	}
}

/**
 * evewgween_page_fwip - pagefwip cawwback.
 *
 * @wdev: wadeon_device pointew
 * @cwtc_id: cwtc to cweanup pagefwip on
 * @cwtc_base: new addwess of the cwtc (GPU MC addwess)
 * @async: asynchwonous fwip
 *
 * Twiggews the actuaw pagefwip by updating the pwimawy
 * suwface base addwess (evewgween+).
 */
void evewgween_page_fwip(stwuct wadeon_device *wdev, int cwtc_id, u64 cwtc_base,
			 boow async)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];
	stwuct dwm_fwamebuffew *fb = wadeon_cwtc->base.pwimawy->fb;

	/* fwip at hsync fow async, defauwt is vsync */
	WWEG32(EVEWGWEEN_GWPH_FWIP_CONTWOW + wadeon_cwtc->cwtc_offset,
	       async ? EVEWGWEEN_GWPH_SUWFACE_UPDATE_H_WETWACE_EN : 0);
	/* update pitch */
	WWEG32(EVEWGWEEN_GWPH_PITCH + wadeon_cwtc->cwtc_offset,
	       fb->pitches[0] / fb->fowmat->cpp[0]);
	/* update the scanout addwesses */
	WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH + wadeon_cwtc->cwtc_offset,
	       uppew_32_bits(cwtc_base));
	WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset,
	       (u32)cwtc_base);
	/* post the wwite */
	WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS + wadeon_cwtc->cwtc_offset);
}

/**
 * evewgween_page_fwip_pending - check if page fwip is stiww pending
 *
 * @wdev: wadeon_device pointew
 * @cwtc_id: cwtc to check
 *
 * Wetuwns the cuwwent update pending status.
 */
boow evewgween_page_fwip_pending(stwuct wadeon_device *wdev, int cwtc_id)
{
	stwuct wadeon_cwtc *wadeon_cwtc = wdev->mode_info.cwtcs[cwtc_id];

	/* Wetuwn cuwwent update_pending status: */
	wetuwn !!(WWEG32(EVEWGWEEN_GWPH_UPDATE + wadeon_cwtc->cwtc_offset) &
		EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING);
}

/* get tempewatuwe in miwwidegwees */
int evewgween_get_temp(stwuct wadeon_device *wdev)
{
	u32 temp, toffset;
	int actuaw_temp = 0;

	if (wdev->famiwy == CHIP_JUNIPEW) {
		toffset = (WWEG32(CG_THEWMAW_CTWW) & TOFFSET_MASK) >>
			TOFFSET_SHIFT;
		temp = (WWEG32(CG_TS0_STATUS) & TS0_ADC_DOUT_MASK) >>
			TS0_ADC_DOUT_SHIFT;

		if (toffset & 0x100)
			actuaw_temp = temp / 2 - (0x200 - toffset);
		ewse
			actuaw_temp = temp / 2 + toffset;

		actuaw_temp = actuaw_temp * 1000;

	} ewse {
		temp = (WWEG32(CG_MUWT_THEWMAW_STATUS) & ASIC_T_MASK) >>
			ASIC_T_SHIFT;

		if (temp & 0x400)
			actuaw_temp = -256;
		ewse if (temp & 0x200)
			actuaw_temp = 255;
		ewse if (temp & 0x100) {
			actuaw_temp = temp & 0x1ff;
			actuaw_temp |= ~0x1ff;
		} ewse
			actuaw_temp = temp & 0xff;

		actuaw_temp = (actuaw_temp * 1000) / 2;
	}

	wetuwn actuaw_temp;
}

int sumo_get_temp(stwuct wadeon_device *wdev)
{
	u32 temp = WWEG32(CG_THEWMAW_STATUS) & 0xff;
	int actuaw_temp = temp - 49;

	wetuwn actuaw_temp * 1000;
}

/**
 * sumo_pm_init_pwofiwe - Initiawize powew pwofiwes cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Initiawize the powew states used in pwofiwe mode
 * (sumo, twinity, SI).
 * Used fow pwofiwe mode onwy.
 */
void sumo_pm_init_pwofiwe(stwuct wadeon_device *wdev)
{
	int idx;

	/* defauwt */
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;

	/* wow,mid sh/mh */
	if (wdev->fwags & WADEON_IS_MOBIWITY)
		idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_BATTEWY, 0);
	ewse
		idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 0);

	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;

	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;

	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;

	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;

	/* high sh/mh */
	idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 0);
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx =
		wdev->pm.powew_state[idx].num_cwock_modes - 1;

	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx =
		wdev->pm.powew_state[idx].num_cwock_modes - 1;
}

/**
 * btc_pm_init_pwofiwe - Initiawize powew pwofiwes cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Initiawize the powew states used in pwofiwe mode
 * (BTC, cayman).
 * Used fow pwofiwe mode onwy.
 */
void btc_pm_init_pwofiwe(stwuct wadeon_device *wdev)
{
	int idx;

	/* defauwt */
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 2;
	/* stawting with BTC, thewe is one state that is used fow both
	 * MH and SH.  Diffewence is that we awways use the high cwock index fow
	 * mcwk.
	 */
	if (wdev->fwags & WADEON_IS_MOBIWITY)
		idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_BATTEWY, 0);
	ewse
		idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 0);
	/* wow sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
	/* mid sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 1;
	/* high sh */
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 2;
	/* wow mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
	/* mid mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 1;
	/* high mh */
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = idx;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
	wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 2;
}

/**
 * evewgween_pm_misc - set additionaw pm hw pawametews cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Set non-cwock pawametews associated with a powew state
 * (vowtage, etc.) (evewgween+).
 */
void evewgween_pm_misc(stwuct wadeon_device *wdev)
{
	int weq_ps_idx = wdev->pm.wequested_powew_state_index;
	int weq_cm_idx = wdev->pm.wequested_cwock_mode_index;
	stwuct wadeon_powew_state *ps = &wdev->pm.powew_state[weq_ps_idx];
	stwuct wadeon_vowtage *vowtage = &ps->cwock_info[weq_cm_idx].vowtage;

	if (vowtage->type == VOWTAGE_SW) {
		/* 0xff0x awe fwags wathew then an actuaw vowtage */
		if ((vowtage->vowtage & 0xff00) == 0xff00)
			wetuwn;
		if (vowtage->vowtage && (vowtage->vowtage != wdev->pm.cuwwent_vddc)) {
			wadeon_atom_set_vowtage(wdev, vowtage->vowtage, SET_VOWTAGE_TYPE_ASIC_VDDC);
			wdev->pm.cuwwent_vddc = vowtage->vowtage;
			DWM_DEBUG("Setting: vddc: %d\n", vowtage->vowtage);
		}

		/* stawting with BTC, thewe is one state that is used fow both
		 * MH and SH.  Diffewence is that we awways use the high cwock index fow
		 * mcwk and vddci.
		 */
		if ((wdev->pm.pm_method == PM_METHOD_PWOFIWE) &&
		    (wdev->famiwy >= CHIP_BAWTS) &&
		    wdev->pm.active_cwtc_count &&
		    ((wdev->pm.pwofiwe_index == PM_PWOFIWE_MID_MH_IDX) ||
		     (wdev->pm.pwofiwe_index == PM_PWOFIWE_WOW_MH_IDX)))
			vowtage = &wdev->pm.powew_state[weq_ps_idx].
				cwock_info[wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx].vowtage;

		/* 0xff0x awe fwags wathew then an actuaw vowtage */
		if ((vowtage->vddci & 0xff00) == 0xff00)
			wetuwn;
		if (vowtage->vddci && (vowtage->vddci != wdev->pm.cuwwent_vddci)) {
			wadeon_atom_set_vowtage(wdev, vowtage->vddci, SET_VOWTAGE_TYPE_ASIC_VDDCI);
			wdev->pm.cuwwent_vddci = vowtage->vddci;
			DWM_DEBUG("Setting: vddci: %d\n", vowtage->vddci);
		}
	}
}

/**
 * evewgween_pm_pwepawe - pwe-powew state change cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Pwepawe fow a powew state change (evewgween+).
 */
void evewgween_pm_pwepawe(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 tmp;

	/* disabwe any active CWTCs */
	wist_fow_each_entwy(cwtc, &ddev->mode_config.cwtc_wist, head) {
		wadeon_cwtc = to_wadeon_cwtc(cwtc);
		if (wadeon_cwtc->enabwed) {
			tmp = WWEG32(EVEWGWEEN_CWTC_CONTWOW + wadeon_cwtc->cwtc_offset);
			tmp |= EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE;
			WWEG32(EVEWGWEEN_CWTC_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
		}
	}
}

/**
 * evewgween_pm_finish - post-powew state change cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Cwean up aftew a powew state change (evewgween+).
 */
void evewgween_pm_finish(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	u32 tmp;

	/* enabwe any active CWTCs */
	wist_fow_each_entwy(cwtc, &ddev->mode_config.cwtc_wist, head) {
		wadeon_cwtc = to_wadeon_cwtc(cwtc);
		if (wadeon_cwtc->enabwed) {
			tmp = WWEG32(EVEWGWEEN_CWTC_CONTWOW + wadeon_cwtc->cwtc_offset);
			tmp &= ~EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE;
			WWEG32(EVEWGWEEN_CWTC_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
		}
	}
}

/**
 * evewgween_hpd_sense - hpd sense cawwback.
 *
 * @wdev: wadeon_device pointew
 * @hpd: hpd (hotpwug detect) pin
 *
 * Checks if a digitaw monitow is connected (evewgween+).
 * Wetuwns twue if connected, fawse if not connected.
 */
boow evewgween_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd)
{
	if (hpd == WADEON_HPD_NONE)
		wetuwn fawse;

	wetuwn !!(WWEG32(DC_HPDx_INT_STATUS_WEG(hpd)) & DC_HPDx_SENSE);
}

/**
 * evewgween_hpd_set_powawity - hpd set powawity cawwback.
 *
 * @wdev: wadeon_device pointew
 * @hpd: hpd (hotpwug detect) pin
 *
 * Set the powawity of the hpd pin (evewgween+).
 */
void evewgween_hpd_set_powawity(stwuct wadeon_device *wdev,
				enum wadeon_hpd_id hpd)
{
	boow connected = evewgween_hpd_sense(wdev, hpd);

	if (hpd == WADEON_HPD_NONE)
		wetuwn;

	if (connected)
		WWEG32_AND(DC_HPDx_INT_CONTWOW(hpd), ~DC_HPDx_INT_POWAWITY);
	ewse
		WWEG32_OW(DC_HPDx_INT_CONTWOW(hpd), DC_HPDx_INT_POWAWITY);
}

/**
 * evewgween_hpd_init - hpd setup cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Setup the hpd pins used by the cawd (evewgween+).
 * Enabwe the pin, set the powawity, and enabwe the hpd intewwupts.
 */
void evewgween_hpd_init(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned enabwed = 0;
	u32 tmp = DC_HPDx_CONNECTION_TIMEW(0x9c4) |
		DC_HPDx_WX_INT_TIMEW(0xfa) | DC_HPDx_EN;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		enum wadeon_hpd_id hpd =
			to_wadeon_connectow(connectow)->hpd.hpd;

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
		    connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS) {
			/* don't twy to enabwe hpd on eDP ow WVDS avoid bweaking the
			 * aux dp channew on imac and hewp (but not compwetewy fix)
			 * https://bugziwwa.wedhat.com/show_bug.cgi?id=726143
			 * awso avoid intewwupt stowms duwing dpms.
			 */
			continue;
		}

		if (hpd == WADEON_HPD_NONE)
			continue;

		WWEG32(DC_HPDx_CONTWOW(hpd), tmp);
		enabwed |= 1 << hpd;

		wadeon_hpd_set_powawity(wdev, hpd);
	}
	wadeon_iwq_kms_enabwe_hpd(wdev, enabwed);
}

/**
 * evewgween_hpd_fini - hpd teaw down cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Teaw down the hpd pins used by the cawd (evewgween+).
 * Disabwe the hpd intewwupts.
 */
void evewgween_hpd_fini(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned disabwed = 0;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		enum wadeon_hpd_id hpd =
			to_wadeon_connectow(connectow)->hpd.hpd;

		if (hpd == WADEON_HPD_NONE)
			continue;

		WWEG32(DC_HPDx_CONTWOW(hpd), 0);
		disabwed |= 1 << hpd;
	}
	wadeon_iwq_kms_disabwe_hpd(wdev, disabwed);
}

/* watewmawk setup */

static u32 evewgween_wine_buffew_adjust(stwuct wadeon_device *wdev,
					stwuct wadeon_cwtc *wadeon_cwtc,
					stwuct dwm_dispway_mode *mode,
					stwuct dwm_dispway_mode *othew_mode)
{
	u32 tmp, buffew_awwoc, i;
	u32 pipe_offset = wadeon_cwtc->cwtc_id * 0x20;
	/*
	 * Wine Buffew Setup
	 * Thewe awe 3 wine buffews, each one shawed by 2 dispway contwowwews.
	 * DC_WB_MEMOWY_SPWIT contwows how that wine buffew is shawed between
	 * the dispway contwowwews.  The pawitioning is done via one of fouw
	 * pweset awwocations specified in bits 2:0:
	 * fiwst dispway contwowwew
	 *  0 - fiwst hawf of wb (3840 * 2)
	 *  1 - fiwst 3/4 of wb (5760 * 2)
	 *  2 - whowe wb (7680 * 2), othew cwtc must be disabwed
	 *  3 - fiwst 1/4 of wb (1920 * 2)
	 * second dispway contwowwew
	 *  4 - second hawf of wb (3840 * 2)
	 *  5 - second 3/4 of wb (5760 * 2)
	 *  6 - whowe wb (7680 * 2), othew cwtc must be disabwed
	 *  7 - wast 1/4 of wb (1920 * 2)
	 */
	/* this can get twicky if we have two wawge dispways on a paiwed gwoup
	 * of cwtcs.  Ideawwy fow muwtipwe wawge dispways we'd assign them to
	 * non-winked cwtcs fow maximum wine buffew awwocation.
	 */
	if (wadeon_cwtc->base.enabwed && mode) {
		if (othew_mode) {
			tmp = 0; /* 1/2 */
			buffew_awwoc = 1;
		} ewse {
			tmp = 2; /* whowe */
			buffew_awwoc = 2;
		}
	} ewse {
		tmp = 0;
		buffew_awwoc = 0;
	}

	/* second contwowwew of the paiw uses second hawf of the wb */
	if (wadeon_cwtc->cwtc_id % 2)
		tmp += 4;
	WWEG32(DC_WB_MEMOWY_SPWIT + wadeon_cwtc->cwtc_offset, tmp);

	if (ASIC_IS_DCE41(wdev) || ASIC_IS_DCE5(wdev)) {
		WWEG32(PIPE0_DMIF_BUFFEW_CONTWOW + pipe_offset,
		       DMIF_BUFFEWS_AWWOCATED(buffew_awwoc));
		fow (i = 0; i < wdev->usec_timeout; i++) {
			if (WWEG32(PIPE0_DMIF_BUFFEW_CONTWOW + pipe_offset) &
			    DMIF_BUFFEWS_AWWOCATED_COMPWETED)
				bweak;
			udeway(1);
		}
	}

	if (wadeon_cwtc->base.enabwed && mode) {
		switch (tmp) {
		case 0:
		case 4:
		defauwt:
			if (ASIC_IS_DCE5(wdev))
				wetuwn 4096 * 2;
			ewse
				wetuwn 3840 * 2;
		case 1:
		case 5:
			if (ASIC_IS_DCE5(wdev))
				wetuwn 6144 * 2;
			ewse
				wetuwn 5760 * 2;
		case 2:
		case 6:
			if (ASIC_IS_DCE5(wdev))
				wetuwn 8192 * 2;
			ewse
				wetuwn 7680 * 2;
		case 3:
		case 7:
			if (ASIC_IS_DCE5(wdev))
				wetuwn 2048 * 2;
			ewse
				wetuwn 1920 * 2;
		}
	}

	/* contwowwew not enabwed, so no wb used */
	wetuwn 0;
}

u32 evewgween_get_numbew_of_dwam_channews(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32(MC_SHAWED_CHMAP);

	switch ((tmp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) {
	case 0:
	defauwt:
		wetuwn 1;
	case 1:
		wetuwn 2;
	case 2:
		wetuwn 4;
	case 3:
		wetuwn 8;
	}
}

stwuct evewgween_wm_pawams {
	u32 dwam_channews; /* numbew of dwam channews */
	u32 ycwk;          /* bandwidth pew dwam data pin in kHz */
	u32 scwk;          /* engine cwock in kHz */
	u32 disp_cwk;      /* dispway cwock in kHz */
	u32 swc_width;     /* viewpowt width */
	u32 active_time;   /* active dispway time in ns */
	u32 bwank_time;    /* bwank time in ns */
	boow intewwaced;    /* mode is intewwaced */
	fixed20_12 vsc;    /* vewticaw scawe watio */
	u32 num_heads;     /* numbew of active cwtcs */
	u32 bytes_pew_pixew; /* bytes pew pixew dispway + ovewway */
	u32 wb_size;       /* wine buffew awwocated to pipe */
	u32 vtaps;         /* vewticaw scawew taps */
};

static u32 evewgween_dwam_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate DWAM Bandwidth and the pawt awwocated to dispway. */
	fixed20_12 dwam_efficiency; /* 0.7 */
	fixed20_12 ycwk, dwam_channews, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	ycwk.fuww = dfixed_const(wm->ycwk);
	ycwk.fuww = dfixed_div(ycwk, a);
	dwam_channews.fuww = dfixed_const(wm->dwam_channews * 4);
	a.fuww = dfixed_const(10);
	dwam_efficiency.fuww = dfixed_const(7);
	dwam_efficiency.fuww = dfixed_div(dwam_efficiency, a);
	bandwidth.fuww = dfixed_muw(dwam_channews, ycwk);
	bandwidth.fuww = dfixed_muw(bandwidth, dwam_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

static u32 evewgween_dwam_bandwidth_fow_dispway(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate DWAM Bandwidth and the pawt awwocated to dispway. */
	fixed20_12 disp_dwam_awwocation; /* 0.3 to 0.7 */
	fixed20_12 ycwk, dwam_channews, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	ycwk.fuww = dfixed_const(wm->ycwk);
	ycwk.fuww = dfixed_div(ycwk, a);
	dwam_channews.fuww = dfixed_const(wm->dwam_channews * 4);
	a.fuww = dfixed_const(10);
	disp_dwam_awwocation.fuww = dfixed_const(3); /* XXX wowse case vawue 0.3 */
	disp_dwam_awwocation.fuww = dfixed_div(disp_dwam_awwocation, a);
	bandwidth.fuww = dfixed_muw(dwam_channews, ycwk);
	bandwidth.fuww = dfixed_muw(bandwidth, disp_dwam_awwocation);

	wetuwn dfixed_twunc(bandwidth);
}

static u32 evewgween_data_wetuwn_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate the dispway Data wetuwn Bandwidth */
	fixed20_12 wetuwn_efficiency; /* 0.8 */
	fixed20_12 scwk, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	scwk.fuww = dfixed_const(wm->scwk);
	scwk.fuww = dfixed_div(scwk, a);
	a.fuww = dfixed_const(10);
	wetuwn_efficiency.fuww = dfixed_const(8);
	wetuwn_efficiency.fuww = dfixed_div(wetuwn_efficiency, a);
	a.fuww = dfixed_const(32);
	bandwidth.fuww = dfixed_muw(a, scwk);
	bandwidth.fuww = dfixed_muw(bandwidth, wetuwn_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

static u32 evewgween_dmif_wequest_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate the DMIF Wequest Bandwidth */
	fixed20_12 disp_cwk_wequest_efficiency; /* 0.8 */
	fixed20_12 disp_cwk, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	disp_cwk.fuww = dfixed_const(wm->disp_cwk);
	disp_cwk.fuww = dfixed_div(disp_cwk, a);
	a.fuww = dfixed_const(10);
	disp_cwk_wequest_efficiency.fuww = dfixed_const(8);
	disp_cwk_wequest_efficiency.fuww = dfixed_div(disp_cwk_wequest_efficiency, a);
	a.fuww = dfixed_const(32);
	bandwidth.fuww = dfixed_muw(a, disp_cwk);
	bandwidth.fuww = dfixed_muw(bandwidth, disp_cwk_wequest_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

static u32 evewgween_avaiwabwe_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate the Avaiwabwe bandwidth. Dispway can use this tempowawiwy but not in avewage. */
	u32 dwam_bandwidth = evewgween_dwam_bandwidth(wm);
	u32 data_wetuwn_bandwidth = evewgween_data_wetuwn_bandwidth(wm);
	u32 dmif_weq_bandwidth = evewgween_dmif_wequest_bandwidth(wm);

	wetuwn min(dwam_bandwidth, min(data_wetuwn_bandwidth, dmif_weq_bandwidth));
}

static u32 evewgween_avewage_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	/* Cawcuwate the dispway mode Avewage Bandwidth
	 * DispwayMode shouwd contain the souwce and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 wine_time;
	fixed20_12 swc_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	wine_time.fuww = dfixed_const(wm->active_time + wm->bwank_time);
	wine_time.fuww = dfixed_div(wine_time, a);
	bpp.fuww = dfixed_const(wm->bytes_pew_pixew);
	swc_width.fuww = dfixed_const(wm->swc_width);
	bandwidth.fuww = dfixed_muw(swc_width, bpp);
	bandwidth.fuww = dfixed_muw(bandwidth, wm->vsc);
	bandwidth.fuww = dfixed_div(bandwidth, wine_time);

	wetuwn dfixed_twunc(bandwidth);
}

static u32 evewgween_watency_watewmawk(stwuct evewgween_wm_pawams *wm)
{
	/* Fiwst cawcuawte the watency in ns */
	u32 mc_watency = 2000; /* 2000 ns. */
	u32 avaiwabwe_bandwidth = evewgween_avaiwabwe_bandwidth(wm);
	u32 wowst_chunk_wetuwn_time = (512 * 8 * 1000) / avaiwabwe_bandwidth;
	u32 cuwsow_wine_paiw_wetuwn_time = (128 * 4 * 1000) / avaiwabwe_bandwidth;
	u32 dc_watency = 40000000 / wm->disp_cwk; /* dc pipe watency */
	u32 othew_heads_data_wetuwn_time = ((wm->num_heads + 1) * wowst_chunk_wetuwn_time) +
		(wm->num_heads * cuwsow_wine_paiw_wetuwn_time);
	u32 watency = mc_watency + othew_heads_data_wetuwn_time + dc_watency;
	u32 max_swc_wines_pew_dst_wine, wb_fiww_bw, wine_fiww_time;
	fixed20_12 a, b, c;

	if (wm->num_heads == 0)
		wetuwn 0;

	a.fuww = dfixed_const(2);
	b.fuww = dfixed_const(1);
	if ((wm->vsc.fuww > a.fuww) ||
	    ((wm->vsc.fuww > b.fuww) && (wm->vtaps >= 3)) ||
	    (wm->vtaps >= 5) ||
	    ((wm->vsc.fuww >= a.fuww) && wm->intewwaced))
		max_swc_wines_pew_dst_wine = 4;
	ewse
		max_swc_wines_pew_dst_wine = 2;

	a.fuww = dfixed_const(avaiwabwe_bandwidth);
	b.fuww = dfixed_const(wm->num_heads);
	a.fuww = dfixed_div(a, b);

	wb_fiww_bw = min(dfixed_twunc(a), wm->disp_cwk * wm->bytes_pew_pixew / 1000);

	a.fuww = dfixed_const(max_swc_wines_pew_dst_wine * wm->swc_width * wm->bytes_pew_pixew);
	b.fuww = dfixed_const(1000);
	c.fuww = dfixed_const(wb_fiww_bw);
	b.fuww = dfixed_div(c, b);
	a.fuww = dfixed_div(a, b);
	wine_fiww_time = dfixed_twunc(a);

	if (wine_fiww_time < wm->active_time)
		wetuwn watency;
	ewse
		wetuwn watency + (wine_fiww_time - wm->active_time);

}

static boow evewgween_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(stwuct evewgween_wm_pawams *wm)
{
	if (evewgween_avewage_bandwidth(wm) <=
	    (evewgween_dwam_bandwidth_fow_dispway(wm) / wm->num_heads))
		wetuwn twue;
	ewse
		wetuwn fawse;
};

static boow evewgween_avewage_bandwidth_vs_avaiwabwe_bandwidth(stwuct evewgween_wm_pawams *wm)
{
	if (evewgween_avewage_bandwidth(wm) <=
	    (evewgween_avaiwabwe_bandwidth(wm) / wm->num_heads))
		wetuwn twue;
	ewse
		wetuwn fawse;
};

static boow evewgween_check_watency_hiding(stwuct evewgween_wm_pawams *wm)
{
	u32 wb_pawtitions = wm->wb_size / wm->swc_width;
	u32 wine_time = wm->active_time + wm->bwank_time;
	u32 watency_towewant_wines;
	u32 watency_hiding;
	fixed20_12 a;

	a.fuww = dfixed_const(1);
	if (wm->vsc.fuww > a.fuww)
		watency_towewant_wines = 1;
	ewse {
		if (wb_pawtitions <= (wm->vtaps + 1))
			watency_towewant_wines = 1;
		ewse
			watency_towewant_wines = 2;
	}

	watency_hiding = (watency_towewant_wines * wine_time + wm->bwank_time);

	if (evewgween_watency_watewmawk(wm) <= watency_hiding)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void evewgween_pwogwam_watewmawks(stwuct wadeon_device *wdev,
					 stwuct wadeon_cwtc *wadeon_cwtc,
					 u32 wb_size, u32 num_heads)
{
	stwuct dwm_dispway_mode *mode = &wadeon_cwtc->base.mode;
	stwuct evewgween_wm_pawams wm_wow, wm_high;
	u32 dwam_channews;
	u32 active_time;
	u32 wine_time = 0;
	u32 watency_watewmawk_a = 0, watency_watewmawk_b = 0;
	u32 pwiowity_a_mawk = 0, pwiowity_b_mawk = 0;
	u32 pwiowity_a_cnt = PWIOWITY_OFF;
	u32 pwiowity_b_cnt = PWIOWITY_OFF;
	u32 pipe_offset = wadeon_cwtc->cwtc_id * 16;
	u32 tmp, awb_contwow3;
	fixed20_12 a, b, c;

	if (wadeon_cwtc->base.enabwed && num_heads && mode) {
		active_time = (u32) div_u64((u64)mode->cwtc_hdispway * 1000000,
					    (u32)mode->cwock);
		wine_time = (u32) div_u64((u64)mode->cwtc_htotaw * 1000000,
					  (u32)mode->cwock);
		wine_time = min(wine_time, (u32)65535);
		pwiowity_a_cnt = 0;
		pwiowity_b_cnt = 0;
		dwam_channews = evewgween_get_numbew_of_dwam_channews(wdev);

		/* watewmawk fow high cwocks */
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wm_high.ycwk =
				wadeon_dpm_get_mcwk(wdev, fawse) * 10;
			wm_high.scwk =
				wadeon_dpm_get_scwk(wdev, fawse) * 10;
		} ewse {
			wm_high.ycwk = wdev->pm.cuwwent_mcwk * 10;
			wm_high.scwk = wdev->pm.cuwwent_scwk * 10;
		}

		wm_high.disp_cwk = mode->cwock;
		wm_high.swc_width = mode->cwtc_hdispway;
		wm_high.active_time = active_time;
		wm_high.bwank_time = wine_time - wm_high.active_time;
		wm_high.intewwaced = fawse;
		if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			wm_high.intewwaced = twue;
		wm_high.vsc = wadeon_cwtc->vsc;
		wm_high.vtaps = 1;
		if (wadeon_cwtc->wmx_type != WMX_OFF)
			wm_high.vtaps = 2;
		wm_high.bytes_pew_pixew = 4; /* XXX: get this fwom fb config */
		wm_high.wb_size = wb_size;
		wm_high.dwam_channews = dwam_channews;
		wm_high.num_heads = num_heads;

		/* watewmawk fow wow cwocks */
		if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
			wm_wow.ycwk =
				wadeon_dpm_get_mcwk(wdev, twue) * 10;
			wm_wow.scwk =
				wadeon_dpm_get_scwk(wdev, twue) * 10;
		} ewse {
			wm_wow.ycwk = wdev->pm.cuwwent_mcwk * 10;
			wm_wow.scwk = wdev->pm.cuwwent_scwk * 10;
		}

		wm_wow.disp_cwk = mode->cwock;
		wm_wow.swc_width = mode->cwtc_hdispway;
		wm_wow.active_time = active_time;
		wm_wow.bwank_time = wine_time - wm_wow.active_time;
		wm_wow.intewwaced = fawse;
		if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			wm_wow.intewwaced = twue;
		wm_wow.vsc = wadeon_cwtc->vsc;
		wm_wow.vtaps = 1;
		if (wadeon_cwtc->wmx_type != WMX_OFF)
			wm_wow.vtaps = 2;
		wm_wow.bytes_pew_pixew = 4; /* XXX: get this fwom fb config */
		wm_wow.wb_size = wb_size;
		wm_wow.dwam_channews = dwam_channews;
		wm_wow.num_heads = num_heads;

		/* set fow high cwocks */
		watency_watewmawk_a = min(evewgween_watency_watewmawk(&wm_high), (u32)65535);
		/* set fow wow cwocks */
		watency_watewmawk_b = min(evewgween_watency_watewmawk(&wm_wow), (u32)65535);

		/* possibwy fowce dispway pwiowity to high */
		/* shouwd weawwy do this at mode vawidation time... */
		if (!evewgween_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(&wm_high) ||
		    !evewgween_avewage_bandwidth_vs_avaiwabwe_bandwidth(&wm_high) ||
		    !evewgween_check_watency_hiding(&wm_high) ||
		    (wdev->disp_pwiowity == 2)) {
			DWM_DEBUG_KMS("fowce pwiowity a to high\n");
			pwiowity_a_cnt |= PWIOWITY_AWWAYS_ON;
		}
		if (!evewgween_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(&wm_wow) ||
		    !evewgween_avewage_bandwidth_vs_avaiwabwe_bandwidth(&wm_wow) ||
		    !evewgween_check_watency_hiding(&wm_wow) ||
		    (wdev->disp_pwiowity == 2)) {
			DWM_DEBUG_KMS("fowce pwiowity b to high\n");
			pwiowity_b_cnt |= PWIOWITY_AWWAYS_ON;
		}

		a.fuww = dfixed_const(1000);
		b.fuww = dfixed_const(mode->cwock);
		b.fuww = dfixed_div(b, a);
		c.fuww = dfixed_const(watency_watewmawk_a);
		c.fuww = dfixed_muw(c, b);
		c.fuww = dfixed_muw(c, wadeon_cwtc->hsc);
		c.fuww = dfixed_div(c, a);
		a.fuww = dfixed_const(16);
		c.fuww = dfixed_div(c, a);
		pwiowity_a_mawk = dfixed_twunc(c);
		pwiowity_a_cnt |= pwiowity_a_mawk & PWIOWITY_MAWK_MASK;

		a.fuww = dfixed_const(1000);
		b.fuww = dfixed_const(mode->cwock);
		b.fuww = dfixed_div(b, a);
		c.fuww = dfixed_const(watency_watewmawk_b);
		c.fuww = dfixed_muw(c, b);
		c.fuww = dfixed_muw(c, wadeon_cwtc->hsc);
		c.fuww = dfixed_div(c, a);
		a.fuww = dfixed_const(16);
		c.fuww = dfixed_div(c, a);
		pwiowity_b_mawk = dfixed_twunc(c);
		pwiowity_b_cnt |= pwiowity_b_mawk & PWIOWITY_MAWK_MASK;

		/* Save numbew of wines the winebuffew weads befowe the scanout */
		wadeon_cwtc->wb_vbwank_wead_wines = DIV_WOUND_UP(wb_size, mode->cwtc_hdispway);
	}

	/* sewect wm A */
	awb_contwow3 = WWEG32(PIPE0_AWBITWATION_CONTWOW3 + pipe_offset);
	tmp = awb_contwow3;
	tmp &= ~WATENCY_WATEWMAWK_MASK(3);
	tmp |= WATENCY_WATEWMAWK_MASK(1);
	WWEG32(PIPE0_AWBITWATION_CONTWOW3 + pipe_offset, tmp);
	WWEG32(PIPE0_WATENCY_CONTWOW + pipe_offset,
	       (WATENCY_WOW_WATEWMAWK(watency_watewmawk_a) |
		WATENCY_HIGH_WATEWMAWK(wine_time)));
	/* sewect wm B */
	tmp = WWEG32(PIPE0_AWBITWATION_CONTWOW3 + pipe_offset);
	tmp &= ~WATENCY_WATEWMAWK_MASK(3);
	tmp |= WATENCY_WATEWMAWK_MASK(2);
	WWEG32(PIPE0_AWBITWATION_CONTWOW3 + pipe_offset, tmp);
	WWEG32(PIPE0_WATENCY_CONTWOW + pipe_offset,
	       (WATENCY_WOW_WATEWMAWK(watency_watewmawk_b) |
		WATENCY_HIGH_WATEWMAWK(wine_time)));
	/* westowe owiginaw sewection */
	WWEG32(PIPE0_AWBITWATION_CONTWOW3 + pipe_offset, awb_contwow3);

	/* wwite the pwiowity mawks */
	WWEG32(PWIOWITY_A_CNT + wadeon_cwtc->cwtc_offset, pwiowity_a_cnt);
	WWEG32(PWIOWITY_B_CNT + wadeon_cwtc->cwtc_offset, pwiowity_b_cnt);

	/* save vawues fow DPM */
	wadeon_cwtc->wine_time = wine_time;
	wadeon_cwtc->wm_high = watency_watewmawk_a;
	wadeon_cwtc->wm_wow = watency_watewmawk_b;
}

/**
 * evewgween_bandwidth_update - update dispway watewmawks cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Update the dispway watewmawks based on the wequested mode(s)
 * (evewgween+).
 */
void evewgween_bandwidth_update(stwuct wadeon_device *wdev)
{
	stwuct dwm_dispway_mode *mode0 = NUWW;
	stwuct dwm_dispway_mode *mode1 = NUWW;
	u32 num_heads = 0, wb_size;
	int i;

	if (!wdev->mode_info.mode_config_initiawized)
		wetuwn;

	wadeon_update_dispway_pwiowity(wdev);

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (wdev->mode_info.cwtcs[i]->base.enabwed)
			num_heads++;
	}
	fow (i = 0; i < wdev->num_cwtc; i += 2) {
		mode0 = &wdev->mode_info.cwtcs[i]->base.mode;
		mode1 = &wdev->mode_info.cwtcs[i+1]->base.mode;
		wb_size = evewgween_wine_buffew_adjust(wdev, wdev->mode_info.cwtcs[i], mode0, mode1);
		evewgween_pwogwam_watewmawks(wdev, wdev->mode_info.cwtcs[i], wb_size, num_heads);
		wb_size = evewgween_wine_buffew_adjust(wdev, wdev->mode_info.cwtcs[i+1], mode1, mode0);
		evewgween_pwogwam_watewmawks(wdev, wdev->mode_info.cwtcs[i+1], wb_size, num_heads);
	}
}

/**
 * evewgween_mc_wait_fow_idwe - wait fow MC idwe cawwback.
 *
 * @wdev: wadeon_device pointew
 *
 * Wait fow the MC (memowy contwowwew) to be idwe.
 * (evewgween+).
 * Wetuwns 0 if the MC is idwe, -1 if not.
 */
int evewgween_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;
	u32 tmp;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(SWBM_STATUS) & 0x1F00;
		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -1;
}

/*
 * GAWT
 */
void evewgween_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev)
{
	unsigned i;
	u32 tmp;

	WWEG32(HDP_MEM_COHEWENCY_FWUSH_CNTW, 0x1);

	WWEG32(VM_CONTEXT0_WEQUEST_WESPONSE, WEQUEST_TYPE(1));
	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(VM_CONTEXT0_WEQUEST_WESPONSE);
		tmp = (tmp & WESPONSE_TYPE_MASK) >> WESPONSE_TYPE_SHIFT;
		if (tmp == 2) {
			pw_wawn("[dwm] w600 fwush TWB faiwed\n");
			wetuwn;
		}
		if (tmp) {
			wetuwn;
		}
		udeway(1);
	}
}

static int evewgween_pcie_gawt_enabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int w;

	if (wdev->gawt.wobj == NUWW) {
		dev_eww(wdev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	w = wadeon_gawt_tabwe_vwam_pin(wdev);
	if (w)
		wetuwn w;
	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_CACHE | ENABWE_W2_FWAGMENT_PWOCESSING |
				ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, BANK_SEWECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TWB contwow */
	tmp = ENABWE_W1_TWB | ENABWE_W1_FWAGMENT_PWOCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU |
		EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5);
	if (wdev->fwags & WADEON_IS_IGP) {
		WWEG32(FUS_MC_VM_MD_W1_TWB0_CNTW, tmp);
		WWEG32(FUS_MC_VM_MD_W1_TWB1_CNTW, tmp);
		WWEG32(FUS_MC_VM_MD_W1_TWB2_CNTW, tmp);
	} ewse {
		WWEG32(MC_VM_MD_W1_TWB0_CNTW, tmp);
		WWEG32(MC_VM_MD_W1_TWB1_CNTW, tmp);
		WWEG32(MC_VM_MD_W1_TWB2_CNTW, tmp);
		if ((wdev->famiwy == CHIP_JUNIPEW) ||
		    (wdev->famiwy == CHIP_CYPWESS) ||
		    (wdev->famiwy == CHIP_HEMWOCK) ||
		    (wdev->famiwy == CHIP_BAWTS))
			WWEG32(MC_VM_MD_W1_TWB3_CNTW, tmp);
	}
	WWEG32(MC_VM_MB_W1_TWB0_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB1_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB2_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB3_CNTW, tmp);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW, wdev->mc.gtt_stawt >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_END_ADDW, wdev->mc.gtt_end >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW, wdev->gawt.tabwe_addw >> 12);
	WWEG32(VM_CONTEXT0_CNTW, ENABWE_CONTEXT | PAGE_TABWE_DEPTH(0) |
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT);
	WWEG32(VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW,
			(u32)(wdev->dummy_page.addw >> 12));
	WWEG32(VM_CONTEXT1_CNTW, 0);

	evewgween_pcie_gawt_twb_fwush(wdev);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned)(wdev->mc.gtt_size >> 20),
		 (unsigned wong wong)wdev->gawt.tabwe_addw);
	wdev->gawt.weady = twue;
	wetuwn 0;
}

static void evewgween_pcie_gawt_disabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;

	/* Disabwe aww tabwes */
	WWEG32(VM_CONTEXT0_CNTW, 0);
	WWEG32(VM_CONTEXT1_CNTW, 0);

	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, BANK_SEWECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TWB contwow */
	tmp = EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5);
	WWEG32(MC_VM_MD_W1_TWB0_CNTW, tmp);
	WWEG32(MC_VM_MD_W1_TWB1_CNTW, tmp);
	WWEG32(MC_VM_MD_W1_TWB2_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB0_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB1_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB2_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB3_CNTW, tmp);
	wadeon_gawt_tabwe_vwam_unpin(wdev);
}

static void evewgween_pcie_gawt_fini(stwuct wadeon_device *wdev)
{
	evewgween_pcie_gawt_disabwe(wdev);
	wadeon_gawt_tabwe_vwam_fwee(wdev);
	wadeon_gawt_fini(wdev);
}


static void evewgween_agp_enabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;

	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_CACHE | ENABWE_W2_FWAGMENT_PWOCESSING |
				ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, BANK_SEWECT(0) | CACHE_UPDATE_MODE(2));
	/* Setup TWB contwow */
	tmp = ENABWE_W1_TWB | ENABWE_W1_FWAGMENT_PWOCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU |
		EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5);
	WWEG32(MC_VM_MD_W1_TWB0_CNTW, tmp);
	WWEG32(MC_VM_MD_W1_TWB1_CNTW, tmp);
	WWEG32(MC_VM_MD_W1_TWB2_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB0_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB1_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB2_CNTW, tmp);
	WWEG32(MC_VM_MB_W1_TWB3_CNTW, tmp);
	WWEG32(VM_CONTEXT0_CNTW, 0);
	WWEG32(VM_CONTEXT1_CNTW, 0);
}

static const unsigned ni_dig_offsets[] =
{
	NI_DIG0_WEGISTEW_OFFSET,
	NI_DIG1_WEGISTEW_OFFSET,
	NI_DIG2_WEGISTEW_OFFSET,
	NI_DIG3_WEGISTEW_OFFSET,
	NI_DIG4_WEGISTEW_OFFSET,
	NI_DIG5_WEGISTEW_OFFSET
};

static const unsigned ni_tx_offsets[] =
{
	NI_DCIO_UNIPHY0_UNIPHY_TX_CONTWOW1,
	NI_DCIO_UNIPHY1_UNIPHY_TX_CONTWOW1,
	NI_DCIO_UNIPHY2_UNIPHY_TX_CONTWOW1,
	NI_DCIO_UNIPHY3_UNIPHY_TX_CONTWOW1,
	NI_DCIO_UNIPHY4_UNIPHY_TX_CONTWOW1,
	NI_DCIO_UNIPHY5_UNIPHY_TX_CONTWOW1
};

static const unsigned evewgween_dp_offsets[] =
{
	EVEWGWEEN_DP0_WEGISTEW_OFFSET,
	EVEWGWEEN_DP1_WEGISTEW_OFFSET,
	EVEWGWEEN_DP2_WEGISTEW_OFFSET,
	EVEWGWEEN_DP3_WEGISTEW_OFFSET,
	EVEWGWEEN_DP4_WEGISTEW_OFFSET,
	EVEWGWEEN_DP5_WEGISTEW_OFFSET
};

static const unsigned evewgween_disp_int_status[] =
{
	DISP_INTEWWUPT_STATUS,
	DISP_INTEWWUPT_STATUS_CONTINUE,
	DISP_INTEWWUPT_STATUS_CONTINUE2,
	DISP_INTEWWUPT_STATUS_CONTINUE3,
	DISP_INTEWWUPT_STATUS_CONTINUE4,
	DISP_INTEWWUPT_STATUS_CONTINUE5
};

/*
 * Assumption is that EVEWGWEEN_CWTC_MASTEW_EN enabwe fow wequested cwtc
 * We go fwom cwtc to connectow and it is not wewibwe  since it
 * shouwd be an opposite diwection .If cwtc is enabwe then
 * find the dig_fe which sewects this cwtc and insuwe that it enabwe.
 * if such dig_fe is found then find dig_be which sewects found dig_be and
 * insuwe that it enabwe and in DP_SST mode.
 * if UNIPHY_PWW_CONTWOW1.enabwe then we shouwd disconnect timing
 * fwom dp symbows cwocks .
 */
static boow evewgween_is_dp_sst_stweam_enabwed(stwuct wadeon_device *wdev,
					       unsigned cwtc_id, unsigned *wet_dig_fe)
{
	unsigned i;
	unsigned dig_fe;
	unsigned dig_be;
	unsigned dig_en_be;
	unsigned uniphy_pww;
	unsigned digs_fe_sewected;
	unsigned dig_be_mode;
	unsigned dig_fe_mask;
	boow is_enabwed = fawse;
	boow found_cwtc = fawse;

	/* woop thwough aww wunning dig_fe to find sewected cwtc */
	fow (i = 0; i < AWWAY_SIZE(ni_dig_offsets); i++) {
		dig_fe = WWEG32(NI_DIG_FE_CNTW + ni_dig_offsets[i]);
		if (dig_fe & NI_DIG_FE_CNTW_SYMCWK_FE_ON &&
		    cwtc_id == NI_DIG_FE_CNTW_SOUWCE_SEWECT(dig_fe)) {
			/* found wunning pipe */
			found_cwtc = twue;
			dig_fe_mask = 1 << i;
			dig_fe = i;
			bweak;
		}
	}

	if (found_cwtc) {
		/* woop thwough aww wunning dig_be to find sewected dig_fe */
		fow (i = 0; i < AWWAY_SIZE(ni_dig_offsets); i++) {
			dig_be = WWEG32(NI_DIG_BE_CNTW + ni_dig_offsets[i]);
			/* if dig_fe_sewected by dig_be? */
			digs_fe_sewected = NI_DIG_BE_CNTW_FE_SOUWCE_SEWECT(dig_be);
			dig_be_mode = NI_DIG_FE_CNTW_MODE(dig_be);
			if (dig_fe_mask &  digs_fe_sewected &&
			    /* if dig_be in sst mode? */
			    dig_be_mode == NI_DIG_BE_DPSST) {
				dig_en_be = WWEG32(NI_DIG_BE_EN_CNTW +
						   ni_dig_offsets[i]);
				uniphy_pww = WWEG32(NI_DCIO_UNIPHY0_PWW_CONTWOW1 +
						    ni_tx_offsets[i]);
				/* dig_be enabwe and tx is wunning */
				if (dig_en_be & NI_DIG_BE_EN_CNTW_ENABWE &&
				    dig_en_be & NI_DIG_BE_EN_CNTW_SYMBCWK_ON &&
				    uniphy_pww & NI_DCIO_UNIPHY0_PWW_CONTWOW1_ENABWE) {
					is_enabwed = twue;
					*wet_dig_fe = dig_fe;
					bweak;
				}
			}
		}
	}

	wetuwn is_enabwed;
}

/*
 * Bwank dig when in dp sst mode
 * Dig ignowes cwtc timing
 */
static void evewgween_bwank_dp_output(stwuct wadeon_device *wdev,
				      unsigned dig_fe)
{
	unsigned stweam_ctww;
	unsigned fifo_ctww;
	unsigned countew = 0;

	if (dig_fe >= AWWAY_SIZE(evewgween_dp_offsets)) {
		DWM_EWWOW("invawid dig_fe %d\n", dig_fe);
		wetuwn;
	}

	stweam_ctww = WWEG32(EVEWGWEEN_DP_VID_STWEAM_CNTW +
			     evewgween_dp_offsets[dig_fe]);
	if (!(stweam_ctww & EVEWGWEEN_DP_VID_STWEAM_CNTW_ENABWE)) {
		DWM_EWWOW("dig %d , shouwd be enabwe\n", dig_fe);
		wetuwn;
	}

	stweam_ctww &=~EVEWGWEEN_DP_VID_STWEAM_CNTW_ENABWE;
	WWEG32(EVEWGWEEN_DP_VID_STWEAM_CNTW +
	       evewgween_dp_offsets[dig_fe], stweam_ctww);

	stweam_ctww = WWEG32(EVEWGWEEN_DP_VID_STWEAM_CNTW +
			     evewgween_dp_offsets[dig_fe]);
	whiwe (countew < 32 && stweam_ctww & EVEWGWEEN_DP_VID_STWEAM_STATUS) {
		msweep(1);
		countew++;
		stweam_ctww = WWEG32(EVEWGWEEN_DP_VID_STWEAM_CNTW +
				     evewgween_dp_offsets[dig_fe]);
	}
	if (countew >= 32 )
		DWM_EWWOW("countew exceeds %d\n", countew);

	fifo_ctww = WWEG32(EVEWGWEEN_DP_STEEW_FIFO + evewgween_dp_offsets[dig_fe]);
	fifo_ctww |= EVEWGWEEN_DP_STEEW_FIFO_WESET;
	WWEG32(EVEWGWEEN_DP_STEEW_FIFO + evewgween_dp_offsets[dig_fe], fifo_ctww);

}

void evewgween_mc_stop(stwuct wadeon_device *wdev, stwuct evewgween_mc_save *save)
{
	u32 cwtc_enabwed, tmp, fwame_count, bwackout;
	int i, j;
	unsigned dig_fe;

	if (!ASIC_IS_NODCE(wdev)) {
		save->vga_wendew_contwow = WWEG32(VGA_WENDEW_CONTWOW);
		save->vga_hdp_contwow = WWEG32(VGA_HDP_CONTWOW);

		/* disabwe VGA wendew */
		WWEG32(VGA_WENDEW_CONTWOW, 0);
	}
	/* bwank the dispway contwowwews */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		cwtc_enabwed = WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i]) & EVEWGWEEN_CWTC_MASTEW_EN;
		if (cwtc_enabwed) {
			save->cwtc_enabwed[i] = twue;
			if (ASIC_IS_DCE6(wdev)) {
				tmp = WWEG32(EVEWGWEEN_CWTC_BWANK_CONTWOW + cwtc_offsets[i]);
				if (!(tmp & EVEWGWEEN_CWTC_BWANK_DATA_EN)) {
					wadeon_wait_fow_vbwank(wdev, i);
					WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
					tmp |= EVEWGWEEN_CWTC_BWANK_DATA_EN;
					WWEG32(EVEWGWEEN_CWTC_BWANK_CONTWOW + cwtc_offsets[i], tmp);
					WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
				}
			} ewse {
				tmp = WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i]);
				if (!(tmp & EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE)) {
					wadeon_wait_fow_vbwank(wdev, i);
					WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
					tmp |= EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE;
					WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i], tmp);
					WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
				}
			}
			/* wait fow the next fwame */
			fwame_count = wadeon_get_vbwank_countew(wdev, i);
			fow (j = 0; j < wdev->usec_timeout; j++) {
				if (wadeon_get_vbwank_countew(wdev, i) != fwame_count)
					bweak;
				udeway(1);
			}
			/*we shouwd disabwe dig if it dwives dp sst*/
			/*but we awe in wadeon_device_init and the topowogy is unknown*/
			/*and it is avaiwabwe aftew wadeon_modeset_init*/
			/*the fowwowing method wadeon_atom_encodew_dpms_dig*/
			/*does the job if we initiawize it pwopewwy*/
			/*fow now we do it this manuawwy*/
			/**/
			if (ASIC_IS_DCE5(wdev) &&
			    evewgween_is_dp_sst_stweam_enabwed(wdev, i ,&dig_fe))
				evewgween_bwank_dp_output(wdev, dig_fe);
			/*we couwd wemove 6 wines bewow*/
			/* XXX this is a hack to avoid stwange behaviow with EFI on cewtain systems */
			WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
			tmp = WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i]);
			tmp &= ~EVEWGWEEN_CWTC_MASTEW_EN;
			WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i], tmp);
			WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			save->cwtc_enabwed[i] = fawse;
			/* ***** */
		} ewse {
			save->cwtc_enabwed[i] = fawse;
		}
	}

	wadeon_mc_wait_fow_idwe(wdev);

	bwackout = WWEG32(MC_SHAWED_BWACKOUT_CNTW);
	if ((bwackout & BWACKOUT_MODE_MASK) != 1) {
		/* Bwock CPU access */
		WWEG32(BIF_FB_EN, 0);
		/* bwackout the MC */
		bwackout &= ~BWACKOUT_MODE_MASK;
		WWEG32(MC_SHAWED_BWACKOUT_CNTW, bwackout | 1);
	}
	/* wait fow the MC to settwe */
	udeway(100);

	/* wock doubwe buffewed wegs */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			tmp = WWEG32(EVEWGWEEN_GWPH_UPDATE + cwtc_offsets[i]);
			if (!(tmp & EVEWGWEEN_GWPH_UPDATE_WOCK)) {
				tmp |= EVEWGWEEN_GWPH_UPDATE_WOCK;
				WWEG32(EVEWGWEEN_GWPH_UPDATE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(EVEWGWEEN_MASTEW_UPDATE_WOCK + cwtc_offsets[i]);
			if (!(tmp & 1)) {
				tmp |= 1;
				WWEG32(EVEWGWEEN_MASTEW_UPDATE_WOCK + cwtc_offsets[i], tmp);
			}
		}
	}
}

void evewgween_mc_wesume(stwuct wadeon_device *wdev, stwuct evewgween_mc_save *save)
{
	u32 tmp, fwame_count;
	int i, j;

	/* update cwtc base addwesses */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH + cwtc_offsets[i],
		       uppew_32_bits(wdev->mc.vwam_stawt));
		WWEG32(EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH + cwtc_offsets[i],
		       uppew_32_bits(wdev->mc.vwam_stawt));
		WWEG32(EVEWGWEEN_GWPH_PWIMAWY_SUWFACE_ADDWESS + cwtc_offsets[i],
		       (u32)wdev->mc.vwam_stawt);
		WWEG32(EVEWGWEEN_GWPH_SECONDAWY_SUWFACE_ADDWESS + cwtc_offsets[i],
		       (u32)wdev->mc.vwam_stawt);
	}

	if (!ASIC_IS_NODCE(wdev)) {
		WWEG32(EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS_HIGH, uppew_32_bits(wdev->mc.vwam_stawt));
		WWEG32(EVEWGWEEN_VGA_MEMOWY_BASE_ADDWESS, (u32)wdev->mc.vwam_stawt);
	}

	/* unwock wegs and wait fow update */
	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			tmp = WWEG32(EVEWGWEEN_MASTEW_UPDATE_MODE + cwtc_offsets[i]);
			if ((tmp & 0x7) != 0) {
				tmp &= ~0x7;
				WWEG32(EVEWGWEEN_MASTEW_UPDATE_MODE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(EVEWGWEEN_GWPH_UPDATE + cwtc_offsets[i]);
			if (tmp & EVEWGWEEN_GWPH_UPDATE_WOCK) {
				tmp &= ~EVEWGWEEN_GWPH_UPDATE_WOCK;
				WWEG32(EVEWGWEEN_GWPH_UPDATE + cwtc_offsets[i], tmp);
			}
			tmp = WWEG32(EVEWGWEEN_MASTEW_UPDATE_WOCK + cwtc_offsets[i]);
			if (tmp & 1) {
				tmp &= ~1;
				WWEG32(EVEWGWEEN_MASTEW_UPDATE_WOCK + cwtc_offsets[i], tmp);
			}
			fow (j = 0; j < wdev->usec_timeout; j++) {
				tmp = WWEG32(EVEWGWEEN_GWPH_UPDATE + cwtc_offsets[i]);
				if ((tmp & EVEWGWEEN_GWPH_SUWFACE_UPDATE_PENDING) == 0)
					bweak;
				udeway(1);
			}
		}
	}

	/* unbwackout the MC */
	tmp = WWEG32(MC_SHAWED_BWACKOUT_CNTW);
	tmp &= ~BWACKOUT_MODE_MASK;
	WWEG32(MC_SHAWED_BWACKOUT_CNTW, tmp);
	/* awwow CPU access */
	WWEG32(BIF_FB_EN, FB_WEAD_EN | FB_WWITE_EN);

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (save->cwtc_enabwed[i]) {
			if (ASIC_IS_DCE6(wdev)) {
				tmp = WWEG32(EVEWGWEEN_CWTC_BWANK_CONTWOW + cwtc_offsets[i]);
				tmp &= ~EVEWGWEEN_CWTC_BWANK_DATA_EN;
				WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
				WWEG32(EVEWGWEEN_CWTC_BWANK_CONTWOW + cwtc_offsets[i], tmp);
				WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			} ewse {
				tmp = WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i]);
				tmp &= ~EVEWGWEEN_CWTC_DISP_WEAD_WEQUEST_DISABWE;
				WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
				WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i], tmp);
				WWEG32(EVEWGWEEN_CWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			}
			/* wait fow the next fwame */
			fwame_count = wadeon_get_vbwank_countew(wdev, i);
			fow (j = 0; j < wdev->usec_timeout; j++) {
				if (wadeon_get_vbwank_countew(wdev, i) != fwame_count)
					bweak;
				udeway(1);
			}
		}
	}
	if (!ASIC_IS_NODCE(wdev)) {
		/* Unwock vga access */
		WWEG32(VGA_HDP_CONTWOW, save->vga_hdp_contwow);
		mdeway(1);
		WWEG32(VGA_WENDEW_CONTWOW, save->vga_wendew_contwow);
	}
}

void evewgween_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct evewgween_mc_save save;
	u32 tmp;
	int i, j;

	/* Initiawize HDP */
	fow (i = 0, j = 0; i < 32; i++, j += 0x18) {
		WWEG32((0x2c14 + j), 0x00000000);
		WWEG32((0x2c18 + j), 0x00000000);
		WWEG32((0x2c1c + j), 0x00000000);
		WWEG32((0x2c20 + j), 0x00000000);
		WWEG32((0x2c24 + j), 0x00000000);
	}
	WWEG32(HDP_WEG_COHEWENCY_FWUSH_CNTW, 0);

	evewgween_mc_stop(wdev, &save);
	if (evewgween_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}
	/* Wockout access thwough VGA apewtuwe*/
	WWEG32(VGA_HDP_CONTWOW, VGA_MEMOWY_DISABWE);
	/* Update configuwation */
	if (wdev->fwags & WADEON_IS_AGP) {
		if (wdev->mc.vwam_stawt < wdev->mc.gtt_stawt) {
			/* VWAM befowe AGP */
			WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				wdev->mc.vwam_stawt >> 12);
			WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
				wdev->mc.gtt_end >> 12);
		} ewse {
			/* VWAM aftew AGP */
			WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				wdev->mc.gtt_stawt >> 12);
			WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
				wdev->mc.vwam_end >> 12);
		}
	} ewse {
		WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
			wdev->mc.vwam_stawt >> 12);
		WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
			wdev->mc.vwam_end >> 12);
	}
	WWEG32(MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW, wdev->vwam_scwatch.gpu_addw >> 12);
	/* wwano/ontawio onwy */
	if ((wdev->famiwy == CHIP_PAWM) ||
	    (wdev->famiwy == CHIP_SUMO) ||
	    (wdev->famiwy == CHIP_SUMO2)) {
		tmp = WWEG32(MC_FUS_VM_FB_OFFSET) & 0x000FFFFF;
		tmp |= ((wdev->mc.vwam_end >> 20) & 0xF) << 24;
		tmp |= ((wdev->mc.vwam_stawt >> 20) & 0xF) << 20;
		WWEG32(MC_FUS_VM_FB_OFFSET, tmp);
	}
	tmp = ((wdev->mc.vwam_end >> 24) & 0xFFFF) << 16;
	tmp |= ((wdev->mc.vwam_stawt >> 24) & 0xFFFF);
	WWEG32(MC_VM_FB_WOCATION, tmp);
	WWEG32(HDP_NONSUWFACE_BASE, (wdev->mc.vwam_stawt >> 8));
	WWEG32(HDP_NONSUWFACE_INFO, (2 << 7) | (1 << 30));
	WWEG32(HDP_NONSUWFACE_SIZE, 0x3FFFFFFF);
	if (wdev->fwags & WADEON_IS_AGP) {
		WWEG32(MC_VM_AGP_TOP, wdev->mc.gtt_end >> 16);
		WWEG32(MC_VM_AGP_BOT, wdev->mc.gtt_stawt >> 16);
		WWEG32(MC_VM_AGP_BASE, wdev->mc.agp_base >> 22);
	} ewse {
		WWEG32(MC_VM_AGP_BASE, 0);
		WWEG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
		WWEG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	}
	if (evewgween_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}
	evewgween_mc_wesume(wdev, &save);
	/* we need to own VWAM, so tuwn off the VGA wendewew hewe
	 * to stop it ovewwwiting ouw objects */
	wv515_vga_wendew_disabwe(wdev);
}

/*
 * CP.
 */
void evewgween_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	u32 next_wptw;

	/* set to DX10/11 mode */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_MODE_CONTWOW, 0));
	wadeon_wing_wwite(wing, 1);

	if (wing->wptw_save_weg) {
		next_wptw = wing->wptw + 3 + 4;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		wadeon_wing_wwite(wing, ((wing->wptw_save_weg - 
					  PACKET3_SET_CONFIG_WEG_STAWT) >> 2));
		wadeon_wing_wwite(wing, next_wptw);
	} ewse if (wdev->wb.enabwed) {
		next_wptw = wing->wptw + 5 + 4;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_MEM_WWITE, 3));
		wadeon_wing_wwite(wing, wing->next_wptw_gpu_addw & 0xfffffffc);
		wadeon_wing_wwite(wing, (uppew_32_bits(wing->next_wptw_gpu_addw) & 0xff) | (1 << 18));
		wadeon_wing_wwite(wing, next_wptw);
		wadeon_wing_wwite(wing, 0);
	}

	wadeon_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	wadeon_wing_wwite(wing,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addw & 0xFFFFFFFC));
	wadeon_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFF);
	wadeon_wing_wwite(wing, ib->wength_dw);
}


static int evewgween_cp_woad_micwocode(stwuct wadeon_device *wdev)
{
	const __be32 *fw_data;
	int i;

	if (!wdev->me_fw || !wdev->pfp_fw)
		wetuwn -EINVAW;

	w700_cp_stop(wdev);
	WWEG32(CP_WB_CNTW,
#ifdef __BIG_ENDIAN
	       BUF_SWAP_32BIT |
#endif
	       WB_NO_UPDATE | WB_BWKSZ(15) | WB_BUFSZ(3));

	fw_data = (const __be32 *)wdev->pfp_fw->data;
	WWEG32(CP_PFP_UCODE_ADDW, 0);
	fow (i = 0; i < EVEWGWEEN_PFP_UCODE_SIZE; i++)
		WWEG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WWEG32(CP_PFP_UCODE_ADDW, 0);

	fw_data = (const __be32 *)wdev->me_fw->data;
	WWEG32(CP_ME_WAM_WADDW, 0);
	fow (i = 0; i < EVEWGWEEN_PM4_UCODE_SIZE; i++)
		WWEG32(CP_ME_WAM_DATA, be32_to_cpup(fw_data++));

	WWEG32(CP_PFP_UCODE_ADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	wetuwn 0;
}

static int evewgween_cp_stawt(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	int w, i;
	uint32_t cp_me;

	w = wadeon_wing_wock(wdev, wing, 7);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, PACKET3(PACKET3_ME_INITIAWIZE, 5));
	wadeon_wing_wwite(wing, 0x1);
	wadeon_wing_wwite(wing, 0x0);
	wadeon_wing_wwite(wing, wdev->config.evewgween.max_hw_contexts - 1);
	wadeon_wing_wwite(wing, PACKET3_ME_INITIAWIZE_DEVICE_ID(1));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_unwock_commit(wdev, wing, fawse);

	cp_me = 0xff;
	WWEG32(CP_ME_CNTW, cp_me);

	w = wadeon_wing_wock(wdev, wing, evewgween_defauwt_size + 19);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}

	/* setup cweaw context state */
	wadeon_wing_wwite(wing, PACKET3(PACKET3_PWEAMBWE_CNTW, 0));
	wadeon_wing_wwite(wing, PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE);

	fow (i = 0; i < evewgween_defauwt_size; i++)
		wadeon_wing_wwite(wing, evewgween_defauwt_state[i]);

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

	wetuwn 0;
}

static int evewgween_cp_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	u32 tmp;
	u32 wb_bufsz;
	int w;

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

	/* Set wing buffew size */
	wb_bufsz = owdew_base_2(wing->wing_size / 8);
	tmp = (owdew_base_2(WADEON_GPU_PAGE_SIZE/8) << 8) | wb_bufsz;
#ifdef __BIG_ENDIAN
	tmp |= BUF_SWAP_32BIT;
#endif
	WWEG32(CP_WB_CNTW, tmp);
	WWEG32(CP_SEM_WAIT_TIMEW, 0x0);
	WWEG32(CP_SEM_INCOMPWETE_TIMEW_CNTW, 0x0);

	/* Set the wwite pointew deway */
	WWEG32(CP_WB_WPTW_DEWAY, 0);

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(CP_WB_CNTW, tmp | WB_WPTW_WW_ENA);
	WWEG32(CP_WB_WPTW_WW, 0);
	wing->wptw = 0;
	WWEG32(CP_WB_WPTW, wing->wptw);

	/* set the wb addwess whethew it's enabwed ow not */
	WWEG32(CP_WB_WPTW_ADDW,
	       ((wdev->wb.gpu_addw + WADEON_WB_CP_WPTW_OFFSET) & 0xFFFFFFFC));
	WWEG32(CP_WB_WPTW_ADDW_HI, uppew_32_bits(wdev->wb.gpu_addw + WADEON_WB_CP_WPTW_OFFSET) & 0xFF);
	WWEG32(SCWATCH_ADDW, ((wdev->wb.gpu_addw + WADEON_WB_SCWATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	if (wdev->wb.enabwed)
		WWEG32(SCWATCH_UMSK, 0xff);
	ewse {
		tmp |= WB_NO_UPDATE;
		WWEG32(SCWATCH_UMSK, 0);
	}

	mdeway(1);
	WWEG32(CP_WB_CNTW, tmp);

	WWEG32(CP_WB_BASE, wing->gpu_addw >> 8);
	WWEG32(CP_DEBUG, (1 << 27) | (1 << 28));

	evewgween_cp_stawt(wdev);
	wing->weady = twue;
	w = wadeon_wing_test(wdev, WADEON_WING_TYPE_GFX_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		wetuwn w;
	}
	wetuwn 0;
}

/*
 * Cowe functions
 */
static void evewgween_gpu_init(stwuct wadeon_device *wdev)
{
	u32 gb_addw_config;
	u32 mc_awb_wamcfg;
	u32 sx_debug_1;
	u32 smx_dc_ctw0;
	u32 sq_config;
	u32 sq_wds_wesouwce_mgmt;
	u32 sq_gpw_wesouwce_mgmt_1;
	u32 sq_gpw_wesouwce_mgmt_2;
	u32 sq_gpw_wesouwce_mgmt_3;
	u32 sq_thwead_wesouwce_mgmt;
	u32 sq_thwead_wesouwce_mgmt_2;
	u32 sq_stack_wesouwce_mgmt_1;
	u32 sq_stack_wesouwce_mgmt_2;
	u32 sq_stack_wesouwce_mgmt_3;
	u32 vgt_cache_invawidation;
	u32 hdp_host_path_cntw, tmp;
	u32 disabwed_wb_mask;
	int i, j, ps_thwead_count;

	switch (wdev->famiwy) {
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		wdev->config.evewgween.num_ses = 2;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 8;
		wdev->config.evewgween.max_simds = 10;
		wdev->config.evewgween.max_backends = 4 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 512;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x100;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CYPWESS_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_JUNIPEW:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 4;
		wdev->config.evewgween.max_simds = 10;
		wdev->config.evewgween.max_backends = 4 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 512;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x100;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = JUNIPEW_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_WEDWOOD:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 4;
		wdev->config.evewgween.max_simds = 5;
		wdev->config.evewgween.max_backends = 2 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x100;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = WEDWOOD_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_CEDAW:
	defauwt:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 2;
		wdev->config.evewgween.max_tiwe_pipes = 2;
		wdev->config.evewgween.max_simds = 2;
		wdev->config.evewgween.max_backends = 1 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 192;
		wdev->config.evewgween.max_gs_thweads = 16;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 128;
		wdev->config.evewgween.sx_max_expowt_pos_size = 32;
		wdev->config.evewgween.sx_max_expowt_smx_size = 96;
		wdev->config.evewgween.max_hw_contexts = 4;
		wdev->config.evewgween.sq_num_cf_insts = 1;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x40;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CEDAW_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_PAWM:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 2;
		wdev->config.evewgween.max_tiwe_pipes = 2;
		wdev->config.evewgween.max_simds = 2;
		wdev->config.evewgween.max_backends = 1 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 192;
		wdev->config.evewgween.max_gs_thweads = 16;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 128;
		wdev->config.evewgween.sx_max_expowt_pos_size = 32;
		wdev->config.evewgween.sx_max_expowt_smx_size = 96;
		wdev->config.evewgween.max_hw_contexts = 4;
		wdev->config.evewgween.sq_num_cf_insts = 1;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x40;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CEDAW_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_SUMO:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 4;
		if (wdev->pdev->device == 0x9648)
			wdev->config.evewgween.max_simds = 3;
		ewse if ((wdev->pdev->device == 0x9647) ||
			 (wdev->pdev->device == 0x964a))
			wdev->config.evewgween.max_simds = 4;
		ewse
			wdev->config.evewgween.max_simds = 5;
		wdev->config.evewgween.max_backends = 2 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x40;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = SUMO_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_SUMO2:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 4;
		wdev->config.evewgween.max_simds = 2;
		wdev->config.evewgween.max_backends = 1 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 512;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 4;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x40;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = SUMO2_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_BAWTS:
		wdev->config.evewgween.num_ses = 2;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 8;
		wdev->config.evewgween.max_simds = 7;
		wdev->config.evewgween.max_backends = 4 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 512;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x100;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = BAWTS_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_TUWKS:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 4;
		wdev->config.evewgween.max_tiwe_pipes = 4;
		wdev->config.evewgween.max_simds = 6;
		wdev->config.evewgween.max_backends = 2 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 248;
		wdev->config.evewgween.max_gs_thweads = 32;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 256;
		wdev->config.evewgween.sx_max_expowt_pos_size = 64;
		wdev->config.evewgween.sx_max_expowt_smx_size = 192;
		wdev->config.evewgween.max_hw_contexts = 8;
		wdev->config.evewgween.sq_num_cf_insts = 2;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x100;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = TUWKS_GB_ADDW_CONFIG_GOWDEN;
		bweak;
	case CHIP_CAICOS:
		wdev->config.evewgween.num_ses = 1;
		wdev->config.evewgween.max_pipes = 2;
		wdev->config.evewgween.max_tiwe_pipes = 2;
		wdev->config.evewgween.max_simds = 2;
		wdev->config.evewgween.max_backends = 1 * wdev->config.evewgween.num_ses;
		wdev->config.evewgween.max_gpws = 256;
		wdev->config.evewgween.max_thweads = 192;
		wdev->config.evewgween.max_gs_thweads = 16;
		wdev->config.evewgween.max_stack_entwies = 256;
		wdev->config.evewgween.sx_num_of_sets = 4;
		wdev->config.evewgween.sx_max_expowt_size = 128;
		wdev->config.evewgween.sx_max_expowt_pos_size = 32;
		wdev->config.evewgween.sx_max_expowt_smx_size = 96;
		wdev->config.evewgween.max_hw_contexts = 4;
		wdev->config.evewgween.sq_num_cf_insts = 1;

		wdev->config.evewgween.sc_pwim_fifo_size = 0x40;
		wdev->config.evewgween.sc_hiz_tiwe_fifo_size = 0x30;
		wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size = 0x130;
		gb_addw_config = CAICOS_GB_ADDW_CONFIG_GOWDEN;
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
	if ((wdev->famiwy == CHIP_PAWM) ||
	    (wdev->famiwy == CHIP_SUMO) ||
	    (wdev->famiwy == CHIP_SUMO2))
		mc_awb_wamcfg = WWEG32(FUS_MC_AWB_WAMCFG);
	ewse
		mc_awb_wamcfg = WWEG32(MC_AWB_WAMCFG);

	/* setup tiwing info dwowd.  gb_addw_config is not adequate since it does
	 * not have bank info, so cweate a custom tiwing dwowd.
	 * bits 3:0   num_pipes
	 * bits 7:4   num_banks
	 * bits 11:8  gwoup_size
	 * bits 15:12 wow_size
	 */
	wdev->config.evewgween.tiwe_config = 0;
	switch (wdev->config.evewgween.max_tiwe_pipes) {
	case 1:
	defauwt:
		wdev->config.evewgween.tiwe_config |= (0 << 0);
		bweak;
	case 2:
		wdev->config.evewgween.tiwe_config |= (1 << 0);
		bweak;
	case 4:
		wdev->config.evewgween.tiwe_config |= (2 << 0);
		bweak;
	case 8:
		wdev->config.evewgween.tiwe_config |= (3 << 0);
		bweak;
	}
	/* num banks is 8 on aww fusion asics. 0 = 4, 1 = 8, 2 = 16 */
	if (wdev->fwags & WADEON_IS_IGP)
		wdev->config.evewgween.tiwe_config |= 1 << 4;
	ewse {
		switch ((mc_awb_wamcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT) {
		case 0: /* fouw banks */
			wdev->config.evewgween.tiwe_config |= 0 << 4;
			bweak;
		case 1: /* eight banks */
			wdev->config.evewgween.tiwe_config |= 1 << 4;
			bweak;
		case 2: /* sixteen banks */
		defauwt:
			wdev->config.evewgween.tiwe_config |= 2 << 4;
			bweak;
		}
	}
	wdev->config.evewgween.tiwe_config |= 0 << 8;
	wdev->config.evewgween.tiwe_config |=
		((gb_addw_config & 0x30000000) >> 28) << 12;

	if ((wdev->famiwy >= CHIP_CEDAW) && (wdev->famiwy <= CHIP_HEMWOCK)) {
		u32 efuse_stwaps_4;
		u32 efuse_stwaps_3;

		efuse_stwaps_4 = WWEG32_WCU(0x204);
		efuse_stwaps_3 = WWEG32_WCU(0x203);
		tmp = (((efuse_stwaps_4 & 0xf) << 4) |
		      ((efuse_stwaps_3 & 0xf0000000) >> 28));
	} ewse {
		tmp = 0;
		fow (i = (wdev->config.evewgween.num_ses - 1); i >= 0; i--) {
			u32 wb_disabwe_bitmap;

			WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
			WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
			wb_disabwe_bitmap = (WWEG32(CC_WB_BACKEND_DISABWE) & 0x00ff0000) >> 16;
			tmp <<= 4;
			tmp |= wb_disabwe_bitmap;
		}
	}
	/* enabwed wb awe just the one not disabwed :) */
	disabwed_wb_mask = tmp;
	tmp = 0;
	fow (i = 0; i < wdev->config.evewgween.max_backends; i++)
		tmp |= (1 << i);
	/* if aww the backends awe disabwed, fix it up hewe */
	if ((disabwed_wb_mask & tmp) == tmp) {
		fow (i = 0; i < wdev->config.evewgween.max_backends; i++)
			disabwed_wb_mask &= ~(1 << i);
	}

	fow (i = 0; i < wdev->config.evewgween.num_ses; i++) {
		u32 simd_disabwe_bitmap;

		WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_INDEX(i));
		simd_disabwe_bitmap = (WWEG32(CC_GC_SHADEW_PIPE_CONFIG) & 0xffff0000) >> 16;
		simd_disabwe_bitmap |= 0xffffffff << wdev->config.evewgween.max_simds;
		tmp <<= 16;
		tmp |= simd_disabwe_bitmap;
	}
	wdev->config.evewgween.active_simds = hweight32(~tmp);

	WWEG32(GWBM_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_BWOADCAST_WWITES);
	WWEG32(WWC_GFX_INDEX, INSTANCE_BWOADCAST_WWITES | SE_BWOADCAST_WWITES);

	WWEG32(GB_ADDW_CONFIG, gb_addw_config);
	WWEG32(DMIF_ADDW_CONFIG, gb_addw_config);
	WWEG32(HDP_ADDW_CONFIG, gb_addw_config);
	WWEG32(DMA_TIWING_CONFIG, gb_addw_config);
	WWEG32(UVD_UDEC_ADDW_CONFIG, gb_addw_config);
	WWEG32(UVD_UDEC_DB_ADDW_CONFIG, gb_addw_config);
	WWEG32(UVD_UDEC_DBW_ADDW_CONFIG, gb_addw_config);

	if ((wdev->config.evewgween.max_backends == 1) &&
	    (wdev->fwags & WADEON_IS_IGP)) {
		if ((disabwed_wb_mask & 3) == 1) {
			/* WB0 disabwed, WB1 enabwed */
			tmp = 0x11111111;
		} ewse {
			/* WB1 disabwed, WB0 enabwed */
			tmp = 0x00000000;
		}
	} ewse {
		tmp = gb_addw_config & NUM_PIPES_MASK;
		tmp = w6xx_wemap_wendew_backend(wdev, tmp, wdev->config.evewgween.max_backends,
						EVEWGWEEN_MAX_BACKENDS, disabwed_wb_mask);
	}
	wdev->config.evewgween.backend_map = tmp;
	WWEG32(GB_BACKEND_MAP, tmp);

	WWEG32(CGTS_SYS_TCC_DISABWE, 0);
	WWEG32(CGTS_TCC_DISABWE, 0);
	WWEG32(CGTS_USEW_SYS_TCC_DISABWE, 0);
	WWEG32(CGTS_USEW_TCC_DISABWE, 0);

	/* set HW defauwts fow 3D engine */
	WWEG32(CP_QUEUE_THWESHOWDS, (WOQ_IB1_STAWT(0x16) |
				     WOQ_IB2_STAWT(0x2b)));

	WWEG32(CP_MEQ_THWESHOWDS, STQ_SPWIT(0x30));

	WWEG32(TA_CNTW_AUX, (DISABWE_CUBE_ANISO |
			     SYNC_GWADIENT |
			     SYNC_WAWKEW |
			     SYNC_AWIGNEW));

	sx_debug_1 = WWEG32(SX_DEBUG_1);
	sx_debug_1 |= ENABWE_NEW_SMX_ADDWESS;
	WWEG32(SX_DEBUG_1, sx_debug_1);


	smx_dc_ctw0 = WWEG32(SMX_DC_CTW0);
	smx_dc_ctw0 &= ~NUMBEW_OF_SETS(0x1ff);
	smx_dc_ctw0 |= NUMBEW_OF_SETS(wdev->config.evewgween.sx_num_of_sets);
	WWEG32(SMX_DC_CTW0, smx_dc_ctw0);

	if (wdev->famiwy <= CHIP_SUMO2)
		WWEG32(SMX_SAW_CTW0, 0x00010000);

	WWEG32(SX_EXPOWT_BUFFEW_SIZES, (COWOW_BUFFEW_SIZE((wdev->config.evewgween.sx_max_expowt_size / 4) - 1) |
					POSITION_BUFFEW_SIZE((wdev->config.evewgween.sx_max_expowt_pos_size / 4) - 1) |
					SMX_BUFFEW_SIZE((wdev->config.evewgween.sx_max_expowt_smx_size / 4) - 1)));

	WWEG32(PA_SC_FIFO_SIZE, (SC_PWIM_FIFO_SIZE(wdev->config.evewgween.sc_pwim_fifo_size) |
				 SC_HIZ_TIWE_FIFO_SIZE(wdev->config.evewgween.sc_hiz_tiwe_fifo_size) |
				 SC_EAWWYZ_TIWE_FIFO_SIZE(wdev->config.evewgween.sc_eawwyz_tiwe_fifo_size)));

	WWEG32(VGT_NUM_INSTANCES, 1);
	WWEG32(SPI_CONFIG_CNTW, 0);
	WWEG32(SPI_CONFIG_CNTW_1, VTX_DONE_DEWAY(4));
	WWEG32(CP_PEWFMON_CNTW, 0);

	WWEG32(SQ_MS_FIFO_SIZES, (CACHE_FIFO_SIZE(16 * wdev->config.evewgween.sq_num_cf_insts) |
				  FETCH_FIFO_HIWATEW(0x4) |
				  DONE_FIFO_HIWATEW(0xe0) |
				  AWU_UPDATE_FIFO_HIWATEW(0x8)));

	sq_config = WWEG32(SQ_CONFIG);
	sq_config &= ~(PS_PWIO(3) |
		       VS_PWIO(3) |
		       GS_PWIO(3) |
		       ES_PWIO(3));
	sq_config |= (VC_ENABWE |
		      EXPOWT_SWC_C |
		      PS_PWIO(0) |
		      VS_PWIO(1) |
		      GS_PWIO(2) |
		      ES_PWIO(3));

	switch (wdev->famiwy) {
	case CHIP_CEDAW:
	case CHIP_PAWM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_CAICOS:
		/* no vewtex cache */
		sq_config &= ~VC_ENABWE;
		bweak;
	defauwt:
		bweak;
	}

	sq_wds_wesouwce_mgmt = WWEG32(SQ_WDS_WESOUWCE_MGMT);

	sq_gpw_wesouwce_mgmt_1 = NUM_PS_GPWS((wdev->config.evewgween.max_gpws - (4 * 2))* 12 / 32);
	sq_gpw_wesouwce_mgmt_1 |= NUM_VS_GPWS((wdev->config.evewgween.max_gpws - (4 * 2)) * 6 / 32);
	sq_gpw_wesouwce_mgmt_1 |= NUM_CWAUSE_TEMP_GPWS(4);
	sq_gpw_wesouwce_mgmt_2 = NUM_GS_GPWS((wdev->config.evewgween.max_gpws - (4 * 2)) * 4 / 32);
	sq_gpw_wesouwce_mgmt_2 |= NUM_ES_GPWS((wdev->config.evewgween.max_gpws - (4 * 2)) * 4 / 32);
	sq_gpw_wesouwce_mgmt_3 = NUM_HS_GPWS((wdev->config.evewgween.max_gpws - (4 * 2)) * 3 / 32);
	sq_gpw_wesouwce_mgmt_3 |= NUM_WS_GPWS((wdev->config.evewgween.max_gpws - (4 * 2)) * 3 / 32);

	switch (wdev->famiwy) {
	case CHIP_CEDAW:
	case CHIP_PAWM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
		ps_thwead_count = 96;
		bweak;
	defauwt:
		ps_thwead_count = 128;
		bweak;
	}

	sq_thwead_wesouwce_mgmt = NUM_PS_THWEADS(ps_thwead_count);
	sq_thwead_wesouwce_mgmt |= NUM_VS_THWEADS((((wdev->config.evewgween.max_thweads - ps_thwead_count) / 6) / 8) * 8);
	sq_thwead_wesouwce_mgmt |= NUM_GS_THWEADS((((wdev->config.evewgween.max_thweads - ps_thwead_count) / 6) / 8) * 8);
	sq_thwead_wesouwce_mgmt |= NUM_ES_THWEADS((((wdev->config.evewgween.max_thweads - ps_thwead_count) / 6) / 8) * 8);
	sq_thwead_wesouwce_mgmt_2 = NUM_HS_THWEADS((((wdev->config.evewgween.max_thweads - ps_thwead_count) / 6) / 8) * 8);
	sq_thwead_wesouwce_mgmt_2 |= NUM_WS_THWEADS((((wdev->config.evewgween.max_thweads - ps_thwead_count) / 6) / 8) * 8);

	sq_stack_wesouwce_mgmt_1 = NUM_PS_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);
	sq_stack_wesouwce_mgmt_1 |= NUM_VS_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);
	sq_stack_wesouwce_mgmt_2 = NUM_GS_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);
	sq_stack_wesouwce_mgmt_2 |= NUM_ES_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);
	sq_stack_wesouwce_mgmt_3 = NUM_HS_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);
	sq_stack_wesouwce_mgmt_3 |= NUM_WS_STACK_ENTWIES((wdev->config.evewgween.max_stack_entwies * 1) / 6);

	WWEG32(SQ_CONFIG, sq_config);
	WWEG32(SQ_GPW_WESOUWCE_MGMT_1, sq_gpw_wesouwce_mgmt_1);
	WWEG32(SQ_GPW_WESOUWCE_MGMT_2, sq_gpw_wesouwce_mgmt_2);
	WWEG32(SQ_GPW_WESOUWCE_MGMT_3, sq_gpw_wesouwce_mgmt_3);
	WWEG32(SQ_THWEAD_WESOUWCE_MGMT, sq_thwead_wesouwce_mgmt);
	WWEG32(SQ_THWEAD_WESOUWCE_MGMT_2, sq_thwead_wesouwce_mgmt_2);
	WWEG32(SQ_STACK_WESOUWCE_MGMT_1, sq_stack_wesouwce_mgmt_1);
	WWEG32(SQ_STACK_WESOUWCE_MGMT_2, sq_stack_wesouwce_mgmt_2);
	WWEG32(SQ_STACK_WESOUWCE_MGMT_3, sq_stack_wesouwce_mgmt_3);
	WWEG32(SQ_DYN_GPW_CNTW_PS_FWUSH_WEQ, 0);
	WWEG32(SQ_WDS_WESOUWCE_MGMT, sq_wds_wesouwce_mgmt);

	WWEG32(PA_SC_FOWCE_EOV_MAX_CNTS, (FOWCE_EOV_MAX_CWK_CNT(4095) |
					  FOWCE_EOV_MAX_WEZ_CNT(255)));

	switch (wdev->famiwy) {
	case CHIP_CEDAW:
	case CHIP_PAWM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_CAICOS:
		vgt_cache_invawidation = CACHE_INVAWIDATION(TC_ONWY);
		bweak;
	defauwt:
		vgt_cache_invawidation = CACHE_INVAWIDATION(VC_AND_TC);
		bweak;
	}
	vgt_cache_invawidation |= AUTO_INVWD_EN(ES_AND_GS_AUTO);
	WWEG32(VGT_CACHE_INVAWIDATION, vgt_cache_invawidation);

	WWEG32(VGT_GS_VEWTEX_WEUSE, 16);
	WWEG32(PA_SU_WINE_STIPPWE_VAWUE, 0);
	WWEG32(PA_SC_WINE_STIPPWE_STATE, 0);

	WWEG32(VGT_VEWTEX_WEUSE_BWOCK_CNTW, 14);
	WWEG32(VGT_OUT_DEAWWOC_CNTW, 16);

	WWEG32(CB_PEWF_CTW0_SEW_0, 0);
	WWEG32(CB_PEWF_CTW0_SEW_1, 0);
	WWEG32(CB_PEWF_CTW1_SEW_0, 0);
	WWEG32(CB_PEWF_CTW1_SEW_1, 0);
	WWEG32(CB_PEWF_CTW2_SEW_0, 0);
	WWEG32(CB_PEWF_CTW2_SEW_1, 0);
	WWEG32(CB_PEWF_CTW3_SEW_0, 0);
	WWEG32(CB_PEWF_CTW3_SEW_1, 0);

	/* cweaw wendew buffew base addwesses */
	WWEG32(CB_COWOW0_BASE, 0);
	WWEG32(CB_COWOW1_BASE, 0);
	WWEG32(CB_COWOW2_BASE, 0);
	WWEG32(CB_COWOW3_BASE, 0);
	WWEG32(CB_COWOW4_BASE, 0);
	WWEG32(CB_COWOW5_BASE, 0);
	WWEG32(CB_COWOW6_BASE, 0);
	WWEG32(CB_COWOW7_BASE, 0);
	WWEG32(CB_COWOW8_BASE, 0);
	WWEG32(CB_COWOW9_BASE, 0);
	WWEG32(CB_COWOW10_BASE, 0);
	WWEG32(CB_COWOW11_BASE, 0);

	/* set the shadew const cache sizes to 0 */
	fow (i = SQ_AWU_CONST_BUFFEW_SIZE_PS_0; i < 0x28200; i += 4)
		WWEG32(i, 0);
	fow (i = SQ_AWU_CONST_BUFFEW_SIZE_HS_0; i < 0x29000; i += 4)
		WWEG32(i, 0);

	tmp = WWEG32(HDP_MISC_CNTW);
	tmp |= HDP_FWUSH_INVAWIDATE_CACHE;
	WWEG32(HDP_MISC_CNTW, tmp);

	hdp_host_path_cntw = WWEG32(HDP_HOST_PATH_CNTW);
	WWEG32(HDP_HOST_PATH_CNTW, hdp_host_path_cntw);

	WWEG32(PA_CW_ENHANCE, CWIP_VTX_WEOWDEW_ENA | NUM_CWIP_SEQ(3));

	udeway(50);

}

int evewgween_mc_init(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int chansize, numchan;

	/* Get VWAM infowmations */
	wdev->mc.vwam_is_ddw = twue;
	if ((wdev->famiwy == CHIP_PAWM) ||
	    (wdev->famiwy == CHIP_SUMO) ||
	    (wdev->famiwy == CHIP_SUMO2))
		tmp = WWEG32(FUS_MC_AWB_WAMCFG);
	ewse
		tmp = WWEG32(MC_AWB_WAMCFG);
	if (tmp & CHANSIZE_OVEWWIDE) {
		chansize = 16;
	} ewse if (tmp & CHANSIZE_MASK) {
		chansize = 64;
	} ewse {
		chansize = 32;
	}
	tmp = WWEG32(MC_SHAWED_CHMAP);
	switch ((tmp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) {
	case 0:
	defauwt:
		numchan = 1;
		bweak;
	case 1:
		numchan = 2;
		bweak;
	case 2:
		numchan = 4;
		bweak;
	case 3:
		numchan = 8;
		bweak;
	}
	wdev->mc.vwam_width = numchan * chansize;
	/* Couwd apew size wepowt 0 ? */
	wdev->mc.apew_base = pci_wesouwce_stawt(wdev->pdev, 0);
	wdev->mc.apew_size = pci_wesouwce_wen(wdev->pdev, 0);
	/* Setup GPU memowy space */
	if ((wdev->famiwy == CHIP_PAWM) ||
	    (wdev->famiwy == CHIP_SUMO) ||
	    (wdev->famiwy == CHIP_SUMO2)) {
		/* size in bytes on fusion */
		wdev->mc.mc_vwam_size = WWEG32(CONFIG_MEMSIZE);
		wdev->mc.weaw_vwam_size = WWEG32(CONFIG_MEMSIZE);
	} ewse {
		/* size in MB on evewgween/cayman/tn */
		wdev->mc.mc_vwam_size = WWEG32(CONFIG_MEMSIZE) * 1024UWW * 1024UWW;
		wdev->mc.weaw_vwam_size = WWEG32(CONFIG_MEMSIZE) * 1024UWW * 1024UWW;
	}
	wdev->mc.visibwe_vwam_size = wdev->mc.apew_size;
	w700_vwam_gtt_wocation(wdev, &wdev->mc);
	wadeon_update_bandwidth_info(wdev);

	wetuwn 0;
}

void evewgween_pwint_gpu_status_wegs(stwuct wadeon_device *wdev)
{
	dev_info(wdev->dev, "  GWBM_STATUS               = 0x%08X\n",
		WWEG32(GWBM_STATUS));
	dev_info(wdev->dev, "  GWBM_STATUS_SE0           = 0x%08X\n",
		WWEG32(GWBM_STATUS_SE0));
	dev_info(wdev->dev, "  GWBM_STATUS_SE1           = 0x%08X\n",
		WWEG32(GWBM_STATUS_SE1));
	dev_info(wdev->dev, "  SWBM_STATUS               = 0x%08X\n",
		WWEG32(SWBM_STATUS));
	dev_info(wdev->dev, "  SWBM_STATUS2              = 0x%08X\n",
		WWEG32(SWBM_STATUS2));
	dev_info(wdev->dev, "  W_008674_CP_STAWWED_STAT1 = 0x%08X\n",
		WWEG32(CP_STAWWED_STAT1));
	dev_info(wdev->dev, "  W_008678_CP_STAWWED_STAT2 = 0x%08X\n",
		WWEG32(CP_STAWWED_STAT2));
	dev_info(wdev->dev, "  W_00867C_CP_BUSY_STAT     = 0x%08X\n",
		WWEG32(CP_BUSY_STAT));
	dev_info(wdev->dev, "  W_008680_CP_STAT          = 0x%08X\n",
		WWEG32(CP_STAT));
	dev_info(wdev->dev, "  W_00D034_DMA_STATUS_WEG   = 0x%08X\n",
		WWEG32(DMA_STATUS_WEG));
	if (wdev->famiwy >= CHIP_CAYMAN) {
		dev_info(wdev->dev, "  W_00D834_DMA_STATUS_WEG   = 0x%08X\n",
			 WWEG32(DMA_STATUS_WEG + 0x800));
	}
}

boow evewgween_is_dispway_hung(stwuct wadeon_device *wdev)
{
	u32 cwtc_hung = 0;
	u32 cwtc_status[6];
	u32 i, j, tmp;

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (WWEG32(EVEWGWEEN_CWTC_CONTWOW + cwtc_offsets[i]) & EVEWGWEEN_CWTC_MASTEW_EN) {
			cwtc_status[i] = WWEG32(EVEWGWEEN_CWTC_STATUS_HV_COUNT + cwtc_offsets[i]);
			cwtc_hung |= (1 << i);
		}
	}

	fow (j = 0; j < 10; j++) {
		fow (i = 0; i < wdev->num_cwtc; i++) {
			if (cwtc_hung & (1 << i)) {
				tmp = WWEG32(EVEWGWEEN_CWTC_STATUS_HV_COUNT + cwtc_offsets[i]);
				if (tmp != cwtc_status[i])
					cwtc_hung &= ~(1 << i);
			}
		}
		if (cwtc_hung == 0)
			wetuwn fawse;
		udeway(100);
	}

	wetuwn twue;
}

u32 evewgween_gpu_check_soft_weset(stwuct wadeon_device *wdev)
{
	u32 weset_mask = 0;
	u32 tmp;

	/* GWBM_STATUS */
	tmp = WWEG32(GWBM_STATUS);
	if (tmp & (PA_BUSY | SC_BUSY |
		   SH_BUSY | SX_BUSY |
		   TA_BUSY | VGT_BUSY |
		   DB_BUSY | CB_BUSY |
		   SPI_BUSY | VGT_BUSY_NO_DMA))
		weset_mask |= WADEON_WESET_GFX;

	if (tmp & (CF_WQ_PENDING | PF_WQ_PENDING |
		   CP_BUSY | CP_COHEWENCY_BUSY))
		weset_mask |= WADEON_WESET_CP;

	if (tmp & GWBM_EE_BUSY)
		weset_mask |= WADEON_WESET_GWBM | WADEON_WESET_GFX | WADEON_WESET_CP;

	/* DMA_STATUS_WEG */
	tmp = WWEG32(DMA_STATUS_WEG);
	if (!(tmp & DMA_IDWE))
		weset_mask |= WADEON_WESET_DMA;

	/* SWBM_STATUS2 */
	tmp = WWEG32(SWBM_STATUS2);
	if (tmp & DMA_BUSY)
		weset_mask |= WADEON_WESET_DMA;

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

static void evewgween_gpu_soft_weset(stwuct wadeon_device *wdev, u32 weset_mask)
{
	stwuct evewgween_mc_save save;
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;

	if (weset_mask == 0)
		wetuwn;

	dev_info(wdev->dev, "GPU softweset: 0x%08X\n", weset_mask);

	evewgween_pwint_gpu_status_wegs(wdev);

	/* Disabwe CP pawsing/pwefetching */
	WWEG32(CP_ME_CNTW, CP_ME_HAWT | CP_PFP_HAWT);

	if (weset_mask & WADEON_WESET_DMA) {
		/* Disabwe DMA */
		tmp = WWEG32(DMA_WB_CNTW);
		tmp &= ~DMA_WB_ENABWE;
		WWEG32(DMA_WB_CNTW, tmp);
	}

	udeway(50);

	evewgween_mc_stop(wdev, &save);
	if (evewgween_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}

	if (weset_mask & (WADEON_WESET_GFX | WADEON_WESET_COMPUTE)) {
		gwbm_soft_weset |= SOFT_WESET_DB |
			SOFT_WESET_CB |
			SOFT_WESET_PA |
			SOFT_WESET_SC |
			SOFT_WESET_SPI |
			SOFT_WESET_SX |
			SOFT_WESET_SH |
			SOFT_WESET_TC |
			SOFT_WESET_TA |
			SOFT_WESET_VC |
			SOFT_WESET_VGT;
	}

	if (weset_mask & WADEON_WESET_CP) {
		gwbm_soft_weset |= SOFT_WESET_CP |
			SOFT_WESET_VGT;

		swbm_soft_weset |= SOFT_WESET_GWBM;
	}

	if (weset_mask & WADEON_WESET_DMA)
		swbm_soft_weset |= SOFT_WESET_DMA;

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

void evewgween_gpu_pci_config_weset(stwuct wadeon_device *wdev)
{
	stwuct evewgween_mc_save save;
	u32 tmp, i;

	dev_info(wdev->dev, "GPU pci config weset\n");

	/* disabwe dpm? */

	/* Disabwe CP pawsing/pwefetching */
	WWEG32(CP_ME_CNTW, CP_ME_HAWT | CP_PFP_HAWT);
	udeway(50);
	/* Disabwe DMA */
	tmp = WWEG32(DMA_WB_CNTW);
	tmp &= ~DMA_WB_ENABWE;
	WWEG32(DMA_WB_CNTW, tmp);
	/* XXX othew engines? */

	/* hawt the wwc */
	w600_wwc_stop(wdev);

	udeway(50);

	/* set mcwk/scwk to bypass */
	wv770_set_cwk_bypass_mode(wdev);
	/* disabwe BM */
	pci_cweaw_mastew(wdev->pdev);
	/* disabwe mem access */
	evewgween_mc_stop(wdev, &save);
	if (evewgween_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timed out !\n");
	}
	/* weset */
	wadeon_pci_config_weset(wdev);
	/* wait fow asic to come out of weset */
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(CONFIG_MEMSIZE) != 0xffffffff)
			bweak;
		udeway(1);
	}
}

int evewgween_asic_weset(stwuct wadeon_device *wdev, boow hawd)
{
	u32 weset_mask;

	if (hawd) {
		evewgween_gpu_pci_config_weset(wdev);
		wetuwn 0;
	}

	weset_mask = evewgween_gpu_check_soft_weset(wdev);

	if (weset_mask)
		w600_set_bios_scwatch_engine_hung(wdev, twue);

	/* twy soft weset */
	evewgween_gpu_soft_weset(wdev, weset_mask);

	weset_mask = evewgween_gpu_check_soft_weset(wdev);

	/* twy pci config weset */
	if (weset_mask && wadeon_hawd_weset)
		evewgween_gpu_pci_config_weset(wdev);

	weset_mask = evewgween_gpu_check_soft_weset(wdev);

	if (!weset_mask)
		w600_set_bios_scwatch_engine_hung(wdev, fawse);

	wetuwn 0;
}

/**
 * evewgween_gfx_is_wockup - Check if the GFX engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the GFX engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow evewgween_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = evewgween_gpu_check_soft_weset(wdev);

	if (!(weset_mask & (WADEON_WESET_GFX |
			    WADEON_WESET_COMPUTE |
			    WADEON_WESET_CP))) {
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}
	wetuwn wadeon_wing_test_wockup(wdev, wing);
}

/*
 * WWC
 */
#define WWC_SAVE_WESTOWE_WIST_END_MAWKEW    0x00000000
#define WWC_CWEAW_STATE_END_MAWKEW          0x00000001

void sumo_wwc_fini(stwuct wadeon_device *wdev)
{
	int w;

	/* save westowe bwock */
	if (wdev->wwc.save_westowe_obj) {
		w = wadeon_bo_wesewve(wdev->wwc.save_westowe_obj, fawse);
		if (unwikewy(w != 0))
			dev_wawn(wdev->dev, "(%d) wesewve WWC sw bo faiwed\n", w);
		wadeon_bo_unpin(wdev->wwc.save_westowe_obj);
		wadeon_bo_unwesewve(wdev->wwc.save_westowe_obj);

		wadeon_bo_unwef(&wdev->wwc.save_westowe_obj);
		wdev->wwc.save_westowe_obj = NUWW;
	}

	/* cweaw state bwock */
	if (wdev->wwc.cweaw_state_obj) {
		w = wadeon_bo_wesewve(wdev->wwc.cweaw_state_obj, fawse);
		if (unwikewy(w != 0))
			dev_wawn(wdev->dev, "(%d) wesewve WWC c bo faiwed\n", w);
		wadeon_bo_unpin(wdev->wwc.cweaw_state_obj);
		wadeon_bo_unwesewve(wdev->wwc.cweaw_state_obj);

		wadeon_bo_unwef(&wdev->wwc.cweaw_state_obj);
		wdev->wwc.cweaw_state_obj = NUWW;
	}

	/* cweaw state bwock */
	if (wdev->wwc.cp_tabwe_obj) {
		w = wadeon_bo_wesewve(wdev->wwc.cp_tabwe_obj, fawse);
		if (unwikewy(w != 0))
			dev_wawn(wdev->dev, "(%d) wesewve WWC cp tabwe bo faiwed\n", w);
		wadeon_bo_unpin(wdev->wwc.cp_tabwe_obj);
		wadeon_bo_unwesewve(wdev->wwc.cp_tabwe_obj);

		wadeon_bo_unwef(&wdev->wwc.cp_tabwe_obj);
		wdev->wwc.cp_tabwe_obj = NUWW;
	}
}

#define CP_ME_TABWE_SIZE    96

int sumo_wwc_init(stwuct wadeon_device *wdev)
{
	const u32 *swc_ptw;
	vowatiwe u32 *dst_ptw;
	u32 dws, data, i, j, k, weg_num;
	u32 weg_wist_num, weg_wist_hdw_bwk_index, weg_wist_bwk_index = 0;
	u64 weg_wist_mc_addw;
	const stwuct cs_section_def *cs_data;
	int w;

	swc_ptw = wdev->wwc.weg_wist;
	dws = wdev->wwc.weg_wist_size;
	if (wdev->famiwy >= CHIP_BONAIWE) {
		dws += (5 * 16) + 48 + 48 + 64;
	}
	cs_data = wdev->wwc.cs_data;

	if (swc_ptw) {
		/* save westowe bwock */
		if (wdev->wwc.save_westowe_obj == NUWW) {
			w = wadeon_bo_cweate(wdev, dws * 4, PAGE_SIZE, twue,
					     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
					     NUWW, &wdev->wwc.save_westowe_obj);
			if (w) {
				dev_wawn(wdev->dev, "(%d) cweate WWC sw bo faiwed\n", w);
				wetuwn w;
			}
		}

		w = wadeon_bo_wesewve(wdev->wwc.save_westowe_obj, fawse);
		if (unwikewy(w != 0)) {
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		w = wadeon_bo_pin(wdev->wwc.save_westowe_obj, WADEON_GEM_DOMAIN_VWAM,
				  &wdev->wwc.save_westowe_gpu_addw);
		if (w) {
			wadeon_bo_unwesewve(wdev->wwc.save_westowe_obj);
			dev_wawn(wdev->dev, "(%d) pin WWC sw bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}

		w = wadeon_bo_kmap(wdev->wwc.save_westowe_obj, (void **)&wdev->wwc.sw_ptw);
		if (w) {
			dev_wawn(wdev->dev, "(%d) map WWC sw bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		/* wwite the sw buffew */
		dst_ptw = wdev->wwc.sw_ptw;
		if (wdev->famiwy >= CHIP_TAHITI) {
			/* SI */
			fow (i = 0; i < wdev->wwc.weg_wist_size; i++)
				dst_ptw[i] = cpu_to_we32(swc_ptw[i]);
		} ewse {
			/* ON/WN/TN */
			/* fowmat:
			 * dw0: (weg2 << 16) | weg1
			 * dw1: weg1 save space
			 * dw2: weg2 save space
			 */
			fow (i = 0; i < dws; i++) {
				data = swc_ptw[i] >> 2;
				i++;
				if (i < dws)
					data |= (swc_ptw[i] >> 2) << 16;
				j = (((i - 1) * 3) / 2);
				dst_ptw[j] = cpu_to_we32(data);
			}
			j = ((i * 3) / 2);
			dst_ptw[j] = cpu_to_we32(WWC_SAVE_WESTOWE_WIST_END_MAWKEW);
		}
		wadeon_bo_kunmap(wdev->wwc.save_westowe_obj);
		wadeon_bo_unwesewve(wdev->wwc.save_westowe_obj);
	}

	if (cs_data) {
		/* cweaw state bwock */
		if (wdev->famiwy >= CHIP_BONAIWE) {
			wdev->wwc.cweaw_state_size = dws = cik_get_csb_size(wdev);
		} ewse if (wdev->famiwy >= CHIP_TAHITI) {
			wdev->wwc.cweaw_state_size = si_get_csb_size(wdev);
			dws = wdev->wwc.cweaw_state_size + (256 / 4);
		} ewse {
			weg_wist_num = 0;
			dws = 0;
			fow (i = 0; cs_data[i].section != NUWW; i++) {
				fow (j = 0; cs_data[i].section[j].extent != NUWW; j++) {
					weg_wist_num++;
					dws += cs_data[i].section[j].weg_count;
				}
			}
			weg_wist_bwk_index = (3 * weg_wist_num + 2);
			dws += weg_wist_bwk_index;
			wdev->wwc.cweaw_state_size = dws;
		}

		if (wdev->wwc.cweaw_state_obj == NUWW) {
			w = wadeon_bo_cweate(wdev, dws * 4, PAGE_SIZE, twue,
					     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
					     NUWW, &wdev->wwc.cweaw_state_obj);
			if (w) {
				dev_wawn(wdev->dev, "(%d) cweate WWC c bo faiwed\n", w);
				sumo_wwc_fini(wdev);
				wetuwn w;
			}
		}
		w = wadeon_bo_wesewve(wdev->wwc.cweaw_state_obj, fawse);
		if (unwikewy(w != 0)) {
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		w = wadeon_bo_pin(wdev->wwc.cweaw_state_obj, WADEON_GEM_DOMAIN_VWAM,
				  &wdev->wwc.cweaw_state_gpu_addw);
		if (w) {
			wadeon_bo_unwesewve(wdev->wwc.cweaw_state_obj);
			dev_wawn(wdev->dev, "(%d) pin WWC c bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}

		w = wadeon_bo_kmap(wdev->wwc.cweaw_state_obj, (void **)&wdev->wwc.cs_ptw);
		if (w) {
			dev_wawn(wdev->dev, "(%d) map WWC c bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		/* set up the cs buffew */
		dst_ptw = wdev->wwc.cs_ptw;
		if (wdev->famiwy >= CHIP_BONAIWE) {
			cik_get_csb_buffew(wdev, dst_ptw);
		} ewse if (wdev->famiwy >= CHIP_TAHITI) {
			weg_wist_mc_addw = wdev->wwc.cweaw_state_gpu_addw + 256;
			dst_ptw[0] = cpu_to_we32(uppew_32_bits(weg_wist_mc_addw));
			dst_ptw[1] = cpu_to_we32(wowew_32_bits(weg_wist_mc_addw));
			dst_ptw[2] = cpu_to_we32(wdev->wwc.cweaw_state_size);
			si_get_csb_buffew(wdev, &dst_ptw[(256/4)]);
		} ewse {
			weg_wist_hdw_bwk_index = 0;
			weg_wist_mc_addw = wdev->wwc.cweaw_state_gpu_addw + (weg_wist_bwk_index * 4);
			data = uppew_32_bits(weg_wist_mc_addw);
			dst_ptw[weg_wist_hdw_bwk_index] = cpu_to_we32(data);
			weg_wist_hdw_bwk_index++;
			fow (i = 0; cs_data[i].section != NUWW; i++) {
				fow (j = 0; cs_data[i].section[j].extent != NUWW; j++) {
					weg_num = cs_data[i].section[j].weg_count;
					data = weg_wist_mc_addw & 0xffffffff;
					dst_ptw[weg_wist_hdw_bwk_index] = cpu_to_we32(data);
					weg_wist_hdw_bwk_index++;

					data = (cs_data[i].section[j].weg_index * 4) & 0xffffffff;
					dst_ptw[weg_wist_hdw_bwk_index] = cpu_to_we32(data);
					weg_wist_hdw_bwk_index++;

					data = 0x08000000 | (weg_num * 4);
					dst_ptw[weg_wist_hdw_bwk_index] = cpu_to_we32(data);
					weg_wist_hdw_bwk_index++;

					fow (k = 0; k < weg_num; k++) {
						data = cs_data[i].section[j].extent[k];
						dst_ptw[weg_wist_bwk_index + k] = cpu_to_we32(data);
					}
					weg_wist_mc_addw += weg_num * 4;
					weg_wist_bwk_index += weg_num;
				}
			}
			dst_ptw[weg_wist_hdw_bwk_index] = cpu_to_we32(WWC_CWEAW_STATE_END_MAWKEW);
		}
		wadeon_bo_kunmap(wdev->wwc.cweaw_state_obj);
		wadeon_bo_unwesewve(wdev->wwc.cweaw_state_obj);
	}

	if (wdev->wwc.cp_tabwe_size) {
		if (wdev->wwc.cp_tabwe_obj == NUWW) {
			w = wadeon_bo_cweate(wdev, wdev->wwc.cp_tabwe_size,
					     PAGE_SIZE, twue,
					     WADEON_GEM_DOMAIN_VWAM, 0, NUWW,
					     NUWW, &wdev->wwc.cp_tabwe_obj);
			if (w) {
				dev_wawn(wdev->dev, "(%d) cweate WWC cp tabwe bo faiwed\n", w);
				sumo_wwc_fini(wdev);
				wetuwn w;
			}
		}

		w = wadeon_bo_wesewve(wdev->wwc.cp_tabwe_obj, fawse);
		if (unwikewy(w != 0)) {
			dev_wawn(wdev->dev, "(%d) wesewve WWC cp tabwe bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		w = wadeon_bo_pin(wdev->wwc.cp_tabwe_obj, WADEON_GEM_DOMAIN_VWAM,
				  &wdev->wwc.cp_tabwe_gpu_addw);
		if (w) {
			wadeon_bo_unwesewve(wdev->wwc.cp_tabwe_obj);
			dev_wawn(wdev->dev, "(%d) pin WWC cp_tabwe bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}
		w = wadeon_bo_kmap(wdev->wwc.cp_tabwe_obj, (void **)&wdev->wwc.cp_tabwe_ptw);
		if (w) {
			dev_wawn(wdev->dev, "(%d) map WWC cp tabwe bo faiwed\n", w);
			sumo_wwc_fini(wdev);
			wetuwn w;
		}

		cik_init_cp_pg_tabwe(wdev);

		wadeon_bo_kunmap(wdev->wwc.cp_tabwe_obj);
		wadeon_bo_unwesewve(wdev->wwc.cp_tabwe_obj);

	}

	wetuwn 0;
}

static void evewgween_wwc_stawt(stwuct wadeon_device *wdev)
{
	u32 mask = WWC_ENABWE;

	if (wdev->fwags & WADEON_IS_IGP) {
		mask |= GFX_POWEW_GATING_ENABWE | GFX_POWEW_GATING_SWC;
	}

	WWEG32(WWC_CNTW, mask);
}

int evewgween_wwc_wesume(stwuct wadeon_device *wdev)
{
	u32 i;
	const __be32 *fw_data;

	if (!wdev->wwc_fw)
		wetuwn -EINVAW;

	w600_wwc_stop(wdev);

	WWEG32(WWC_HB_CNTW, 0);

	if (wdev->fwags & WADEON_IS_IGP) {
		if (wdev->famiwy == CHIP_AWUBA) {
			u32 awways_on_bitmap =
				3 | (3 << (16 * wdev->config.cayman.max_shadew_engines));
			/* find out the numbew of active simds */
			u32 tmp = (WWEG32(CC_GC_SHADEW_PIPE_CONFIG) & 0xffff0000) >> 16;
			tmp |= 0xffffffff << wdev->config.cayman.max_simds_pew_se;
			tmp = hweight32(~tmp);
			if (tmp == wdev->config.cayman.max_simds_pew_se) {
				WWEG32(TN_WWC_WB_AWWAYS_ACTIVE_SIMD_MASK, awways_on_bitmap);
				WWEG32(TN_WWC_WB_PAWAMS, 0x00601004);
				WWEG32(TN_WWC_WB_INIT_SIMD_MASK, 0xffffffff);
				WWEG32(TN_WWC_WB_CNTW_INIT, 0x00000000);
				WWEG32(TN_WWC_WB_CNTW_MAX, 0x00002000);
			}
		} ewse {
			WWEG32(WWC_HB_WPTW_WSB_ADDW, 0);
			WWEG32(WWC_HB_WPTW_MSB_ADDW, 0);
		}
		WWEG32(TN_WWC_SAVE_AND_WESTOWE_BASE, wdev->wwc.save_westowe_gpu_addw >> 8);
		WWEG32(TN_WWC_CWEAW_STATE_WESTOWE_BASE, wdev->wwc.cweaw_state_gpu_addw >> 8);
	} ewse {
		WWEG32(WWC_HB_BASE, 0);
		WWEG32(WWC_HB_WPTW, 0);
		WWEG32(WWC_HB_WPTW, 0);
		WWEG32(WWC_HB_WPTW_WSB_ADDW, 0);
		WWEG32(WWC_HB_WPTW_MSB_ADDW, 0);
	}
	WWEG32(WWC_MC_CNTW, 0);
	WWEG32(WWC_UCODE_CNTW, 0);

	fw_data = (const __be32 *)wdev->wwc_fw->data;
	if (wdev->famiwy >= CHIP_AWUBA) {
		fow (i = 0; i < AWUBA_WWC_UCODE_SIZE; i++) {
			WWEG32(WWC_UCODE_ADDW, i);
			WWEG32(WWC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} ewse if (wdev->famiwy >= CHIP_CAYMAN) {
		fow (i = 0; i < CAYMAN_WWC_UCODE_SIZE; i++) {
			WWEG32(WWC_UCODE_ADDW, i);
			WWEG32(WWC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} ewse {
		fow (i = 0; i < EVEWGWEEN_WWC_UCODE_SIZE; i++) {
			WWEG32(WWC_UCODE_ADDW, i);
			WWEG32(WWC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	}
	WWEG32(WWC_UCODE_ADDW, 0);

	evewgween_wwc_stawt(wdev);

	wetuwn 0;
}

/* Intewwupts */

u32 evewgween_get_vbwank_countew(stwuct wadeon_device *wdev, int cwtc)
{
	if (cwtc >= wdev->num_cwtc)
		wetuwn 0;
	ewse
		wetuwn WWEG32(CWTC_STATUS_FWAME_COUNT + cwtc_offsets[cwtc]);
}

void evewgween_disabwe_intewwupt_state(stwuct wadeon_device *wdev)
{
	int i;
	u32 tmp;

	if (wdev->famiwy >= CHIP_CAYMAN) {
		cayman_cp_int_cntw_setup(wdev, 0,
					 CNTX_BUSY_INT_ENABWE | CNTX_EMPTY_INT_ENABWE);
		cayman_cp_int_cntw_setup(wdev, 1, 0);
		cayman_cp_int_cntw_setup(wdev, 2, 0);
		tmp = WWEG32(CAYMAN_DMA1_CNTW) & ~TWAP_ENABWE;
		WWEG32(CAYMAN_DMA1_CNTW, tmp);
	} ewse
		WWEG32(CP_INT_CNTW, CNTX_BUSY_INT_ENABWE | CNTX_EMPTY_INT_ENABWE);
	tmp = WWEG32(DMA_CNTW) & ~TWAP_ENABWE;
	WWEG32(DMA_CNTW, tmp);
	WWEG32(GWBM_INT_CNTW, 0);
	WWEG32(SWBM_INT_CNTW, 0);
	fow (i = 0; i < wdev->num_cwtc; i++)
		WWEG32(INT_MASK + cwtc_offsets[i], 0);
	fow (i = 0; i < wdev->num_cwtc; i++)
		WWEG32(GWPH_INT_CONTWOW + cwtc_offsets[i], 0);

	/* onwy one DAC on DCE5 */
	if (!ASIC_IS_DCE5(wdev))
		WWEG32(DACA_AUTODETECT_INT_CONTWOW, 0);
	WWEG32(DACB_AUTODETECT_INT_CONTWOW, 0);

	fow (i = 0; i < 6; i++)
		WWEG32_AND(DC_HPDx_INT_CONTWOW(i), DC_HPDx_INT_POWAWITY);
}

/* Note that the owdew we wwite back wegs hewe is impowtant */
int evewgween_iwq_set(stwuct wadeon_device *wdev)
{
	int i;
	u32 cp_int_cntw = CNTX_BUSY_INT_ENABWE | CNTX_EMPTY_INT_ENABWE;
	u32 cp_int_cntw1 = 0, cp_int_cntw2 = 0;
	u32 gwbm_int_cntw = 0;
	u32 dma_cntw, dma_cntw1 = 0;
	u32 thewmaw_int = 0;

	if (!wdev->iwq.instawwed) {
		WAWN(1, "Can't enabwe IWQ/MSI because no handwew is instawwed\n");
		wetuwn -EINVAW;
	}
	/* don't enabwe anything if the ih is disabwed */
	if (!wdev->ih.enabwed) {
		w600_disabwe_intewwupts(wdev);
		/* fowce the active intewwupt state to aww disabwed */
		evewgween_disabwe_intewwupt_state(wdev);
		wetuwn 0;
	}

	if (wdev->famiwy == CHIP_AWUBA)
		thewmaw_int = WWEG32(TN_CG_THEWMAW_INT_CTWW) &
			~(THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW);
	ewse
		thewmaw_int = WWEG32(CG_THEWMAW_INT) &
			~(THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW);

	dma_cntw = WWEG32(DMA_CNTW) & ~TWAP_ENABWE;

	if (wdev->famiwy >= CHIP_CAYMAN) {
		/* enabwe CP intewwupts on aww wings */
		if (atomic_wead(&wdev->iwq.wing_int[WADEON_WING_TYPE_GFX_INDEX])) {
			DWM_DEBUG("evewgween_iwq_set: sw int gfx\n");
			cp_int_cntw |= TIME_STAMP_INT_ENABWE;
		}
		if (atomic_wead(&wdev->iwq.wing_int[CAYMAN_WING_TYPE_CP1_INDEX])) {
			DWM_DEBUG("evewgween_iwq_set: sw int cp1\n");
			cp_int_cntw1 |= TIME_STAMP_INT_ENABWE;
		}
		if (atomic_wead(&wdev->iwq.wing_int[CAYMAN_WING_TYPE_CP2_INDEX])) {
			DWM_DEBUG("evewgween_iwq_set: sw int cp2\n");
			cp_int_cntw2 |= TIME_STAMP_INT_ENABWE;
		}
	} ewse {
		if (atomic_wead(&wdev->iwq.wing_int[WADEON_WING_TYPE_GFX_INDEX])) {
			DWM_DEBUG("evewgween_iwq_set: sw int gfx\n");
			cp_int_cntw |= WB_INT_ENABWE;
			cp_int_cntw |= TIME_STAMP_INT_ENABWE;
		}
	}

	if (atomic_wead(&wdev->iwq.wing_int[W600_WING_TYPE_DMA_INDEX])) {
		DWM_DEBUG("w600_iwq_set: sw int dma\n");
		dma_cntw |= TWAP_ENABWE;
	}

	if (wdev->famiwy >= CHIP_CAYMAN) {
		dma_cntw1 = WWEG32(CAYMAN_DMA1_CNTW) & ~TWAP_ENABWE;
		if (atomic_wead(&wdev->iwq.wing_int[CAYMAN_WING_TYPE_DMA1_INDEX])) {
			DWM_DEBUG("w600_iwq_set: sw int dma1\n");
			dma_cntw1 |= TWAP_ENABWE;
		}
	}

	if (wdev->iwq.dpm_thewmaw) {
		DWM_DEBUG("dpm thewmaw\n");
		thewmaw_int |= THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW;
	}

	if (wdev->famiwy >= CHIP_CAYMAN) {
		cayman_cp_int_cntw_setup(wdev, 0, cp_int_cntw);
		cayman_cp_int_cntw_setup(wdev, 1, cp_int_cntw1);
		cayman_cp_int_cntw_setup(wdev, 2, cp_int_cntw2);
	} ewse
		WWEG32(CP_INT_CNTW, cp_int_cntw);

	WWEG32(DMA_CNTW, dma_cntw);

	if (wdev->famiwy >= CHIP_CAYMAN)
		WWEG32(CAYMAN_DMA1_CNTW, dma_cntw1);

	WWEG32(GWBM_INT_CNTW, gwbm_int_cntw);

	fow (i = 0; i < wdev->num_cwtc; i++) {
		wadeon_iwq_kms_set_iwq_n_enabwed(
		    wdev, INT_MASK + cwtc_offsets[i],
		    VBWANK_INT_MASK,
		    wdev->iwq.cwtc_vbwank_int[i] ||
		    atomic_wead(&wdev->iwq.pfwip[i]), "vbwank", i);
	}

	fow (i = 0; i < wdev->num_cwtc; i++)
		WWEG32(GWPH_INT_CONTWOW + cwtc_offsets[i], GWPH_PFWIP_INT_MASK);

	fow (i = 0; i < 6; i++) {
		wadeon_iwq_kms_set_iwq_n_enabwed(
		    wdev, DC_HPDx_INT_CONTWOW(i),
		    DC_HPDx_INT_EN | DC_HPDx_WX_INT_EN,
		    wdev->iwq.hpd[i], "HPD", i);
	}

	if (wdev->famiwy == CHIP_AWUBA)
		WWEG32(TN_CG_THEWMAW_INT_CTWW, thewmaw_int);
	ewse
		WWEG32(CG_THEWMAW_INT, thewmaw_int);

	fow (i = 0; i < 6; i++) {
		wadeon_iwq_kms_set_iwq_n_enabwed(
		    wdev, AFMT_AUDIO_PACKET_CONTWOW + cwtc_offsets[i],
		    AFMT_AZ_FOWMAT_WTWIG_MASK,
		    wdev->iwq.afmt[i], "HDMI", i);
	}

	/* posting wead */
	WWEG32(SWBM_STATUS);

	wetuwn 0;
}

/* Note that the owdew we wwite back wegs hewe is impowtant */
static void evewgween_iwq_ack(stwuct wadeon_device *wdev)
{
	int i, j;
	u32 *gwph_int = wdev->iwq.stat_wegs.evewgween.gwph_int;
	u32 *disp_int = wdev->iwq.stat_wegs.evewgween.disp_int;
	u32 *afmt_status = wdev->iwq.stat_wegs.evewgween.afmt_status;

	fow (i = 0; i < 6; i++) {
		disp_int[i] = WWEG32(evewgween_disp_int_status[i]);
		afmt_status[i] = WWEG32(AFMT_STATUS + cwtc_offsets[i]);
		if (i < wdev->num_cwtc)
			gwph_int[i] = WWEG32(GWPH_INT_STATUS + cwtc_offsets[i]);
	}

	/* We wwite back each intewwupt wegistew in paiws of two */
	fow (i = 0; i < wdev->num_cwtc; i += 2) {
		fow (j = i; j < (i + 2); j++) {
			if (gwph_int[j] & GWPH_PFWIP_INT_OCCUWWED)
				WWEG32(GWPH_INT_STATUS + cwtc_offsets[j],
				       GWPH_PFWIP_INT_CWEAW);
		}

		fow (j = i; j < (i + 2); j++) {
			if (disp_int[j] & WB_D1_VBWANK_INTEWWUPT)
				WWEG32(VBWANK_STATUS + cwtc_offsets[j],
				       VBWANK_ACK);
			if (disp_int[j] & WB_D1_VWINE_INTEWWUPT)
				WWEG32(VWINE_STATUS + cwtc_offsets[j],
				       VWINE_ACK);
		}
	}

	fow (i = 0; i < 6; i++) {
		if (disp_int[i] & DC_HPD1_INTEWWUPT)
			WWEG32_OW(DC_HPDx_INT_CONTWOW(i), DC_HPDx_INT_ACK);
	}

	fow (i = 0; i < 6; i++) {
		if (disp_int[i] & DC_HPD1_WX_INTEWWUPT)
			WWEG32_OW(DC_HPDx_INT_CONTWOW(i), DC_HPDx_WX_INT_ACK);
	}

	fow (i = 0; i < 6; i++) {
		if (afmt_status[i] & AFMT_AZ_FOWMAT_WTWIG)
			WWEG32_OW(AFMT_AUDIO_PACKET_CONTWOW + cwtc_offsets[i],
				  AFMT_AZ_FOWMAT_WTWIG_ACK);
	}
}

static void evewgween_iwq_disabwe(stwuct wadeon_device *wdev)
{
	w600_disabwe_intewwupts(wdev);
	/* Wait and acknowwedge iwq */
	mdeway(1);
	evewgween_iwq_ack(wdev);
	evewgween_disabwe_intewwupt_state(wdev);
}

void evewgween_iwq_suspend(stwuct wadeon_device *wdev)
{
	evewgween_iwq_disabwe(wdev);
	w600_wwc_stop(wdev);
}

static u32 evewgween_get_ih_wptw(stwuct wadeon_device *wdev)
{
	u32 wptw, tmp;

	if (wdev->wb.enabwed)
		wptw = we32_to_cpu(wdev->wb.wb[W600_WB_IH_WPTW_OFFSET/4]);
	ewse
		wptw = WWEG32(IH_WB_WPTW);

	if (wptw & WB_OVEWFWOW) {
		wptw &= ~WB_OVEWFWOW;
		/* When a wing buffew ovewfwow happen stawt pawsing intewwupt
		 * fwom the wast not ovewwwitten vectow (wptw + 16). Hopefuwwy
		 * this shouwd awwow us to catchup.
		 */
		dev_wawn(wdev->dev, "IH wing buffew ovewfwow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptw, wdev->ih.wptw, (wptw + 16) & wdev->ih.ptw_mask);
		wdev->ih.wptw = (wptw + 16) & wdev->ih.ptw_mask;
		tmp = WWEG32(IH_WB_CNTW);
		tmp |= IH_WPTW_OVEWFWOW_CWEAW;
		WWEG32(IH_WB_CNTW, tmp);
	}
	wetuwn (wptw & wdev->ih.ptw_mask);
}

int evewgween_iwq_pwocess(stwuct wadeon_device *wdev)
{
	u32 *disp_int = wdev->iwq.stat_wegs.evewgween.disp_int;
	u32 *afmt_status = wdev->iwq.stat_wegs.evewgween.afmt_status;
	u32 cwtc_idx, hpd_idx, afmt_idx;
	u32 mask;
	u32 wptw;
	u32 wptw;
	u32 swc_id, swc_data;
	u32 wing_index;
	boow queue_hotpwug = fawse;
	boow queue_hdmi = fawse;
	boow queue_dp = fawse;
	boow queue_thewmaw = fawse;
	u32 status, addw;
	const chaw *event_name;

	if (!wdev->ih.enabwed || wdev->shutdown)
		wetuwn IWQ_NONE;

	wptw = evewgween_get_ih_wptw(wdev);

westawt_ih:
	/* is somebody ewse awweady pwocessing iwqs? */
	if (atomic_xchg(&wdev->ih.wock, 1))
		wetuwn IWQ_NONE;

	wptw = wdev->ih.wptw;
	DWM_DEBUG("evewgween_iwq_pwocess stawt: wptw %d, wptw %d\n", wptw, wptw);

	/* Owdew weading of wptw vs. weading of IH wing data */
	wmb();

	/* dispway intewwupts */
	evewgween_iwq_ack(wdev);

	whiwe (wptw != wptw) {
		/* wptw/wptw awe in bytes! */
		wing_index = wptw / 4;
		swc_id =  we32_to_cpu(wdev->ih.wing[wing_index]) & 0xff;
		swc_data = we32_to_cpu(wdev->ih.wing[wing_index + 1]) & 0xfffffff;

		switch (swc_id) {
		case 1: /* D1 vbwank/vwine */
		case 2: /* D2 vbwank/vwine */
		case 3: /* D3 vbwank/vwine */
		case 4: /* D4 vbwank/vwine */
		case 5: /* D5 vbwank/vwine */
		case 6: /* D6 vbwank/vwine */
			cwtc_idx = swc_id - 1;

			if (swc_data == 0) { /* vbwank */
				mask = WB_D1_VBWANK_INTEWWUPT;
				event_name = "vbwank";

				if (wdev->iwq.cwtc_vbwank_int[cwtc_idx]) {
					dwm_handwe_vbwank(wdev->ddev, cwtc_idx);
					wdev->pm.vbwank_sync = twue;
					wake_up(&wdev->iwq.vbwank_queue);
				}
				if (atomic_wead(&wdev->iwq.pfwip[cwtc_idx])) {
					wadeon_cwtc_handwe_vbwank(wdev,
								  cwtc_idx);
				}

			} ewse if (swc_data == 1) { /* vwine */
				mask = WB_D1_VWINE_INTEWWUPT;
				event_name = "vwine";
			} ewse {
				DWM_DEBUG("Unhandwed intewwupt: %d %d\n",
					  swc_id, swc_data);
				bweak;
			}

			if (!(disp_int[cwtc_idx] & mask)) {
				DWM_DEBUG("IH: D%d %s - IH event w/o assewted iwq bit?\n",
					  cwtc_idx + 1, event_name);
			}

			disp_int[cwtc_idx] &= ~mask;
			DWM_DEBUG("IH: D%d %s\n", cwtc_idx + 1, event_name);

			bweak;
		case 8: /* D1 page fwip */
		case 10: /* D2 page fwip */
		case 12: /* D3 page fwip */
		case 14: /* D4 page fwip */
		case 16: /* D5 page fwip */
		case 18: /* D6 page fwip */
			DWM_DEBUG("IH: D%d fwip\n", ((swc_id - 8) >> 1) + 1);
			if (wadeon_use_pfwipiwq > 0)
				wadeon_cwtc_handwe_fwip(wdev, (swc_id - 8) >> 1);
			bweak;
		case 42: /* HPD hotpwug */
			if (swc_data <= 5) {
				hpd_idx = swc_data;
				mask = DC_HPD1_INTEWWUPT;
				queue_hotpwug = twue;
				event_name = "HPD";

			} ewse if (swc_data <= 11) {
				hpd_idx = swc_data - 6;
				mask = DC_HPD1_WX_INTEWWUPT;
				queue_dp = twue;
				event_name = "HPD_WX";

			} ewse {
				DWM_DEBUG("Unhandwed intewwupt: %d %d\n",
					  swc_id, swc_data);
				bweak;
			}

			if (!(disp_int[hpd_idx] & mask))
				DWM_DEBUG("IH: IH event w/o assewted iwq bit?\n");

			disp_int[hpd_idx] &= ~mask;
			DWM_DEBUG("IH: %s%d\n", event_name, hpd_idx + 1);

			bweak;
		case 44: /* hdmi */
			afmt_idx = swc_data;
			if (afmt_idx > 5) {
				DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
					  swc_id, swc_data);
				bweak;
			}

			if (!(afmt_status[afmt_idx] & AFMT_AZ_FOWMAT_WTWIG))
				DWM_DEBUG("IH: IH event w/o assewted iwq bit?\n");

			afmt_status[afmt_idx] &= ~AFMT_AZ_FOWMAT_WTWIG;
			queue_hdmi = twue;
			DWM_DEBUG("IH: HDMI%d\n", afmt_idx + 1);
			bweak;
		case 96:
			DWM_EWWOW("SWBM_WEAD_EWWOW: 0x%x\n", WWEG32(SWBM_WEAD_EWWOW));
			WWEG32(SWBM_INT_ACK, 0x1);
			bweak;
		case 124: /* UVD */
			DWM_DEBUG("IH: UVD int: 0x%08x\n", swc_data);
			wadeon_fence_pwocess(wdev, W600_WING_TYPE_UVD_INDEX);
			bweak;
		case 146:
		case 147:
			addw = WWEG32(VM_CONTEXT1_PWOTECTION_FAUWT_ADDW);
			status = WWEG32(VM_CONTEXT1_PWOTECTION_FAUWT_STATUS);
			/* weset addw and status */
			WWEG32_P(VM_CONTEXT1_CNTW2, 1, ~1);
			if (addw == 0x0 && status == 0x0)
				bweak;
			dev_eww(wdev->dev, "GPU fauwt detected: %d 0x%08x\n", swc_id, swc_data);
			dev_eww(wdev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_ADDW   0x%08X\n",
				addw);
			dev_eww(wdev->dev, "  VM_CONTEXT1_PWOTECTION_FAUWT_STATUS 0x%08X\n",
				status);
			cayman_vm_decode_fauwt(wdev, status, addw);
			bweak;
		case 176: /* CP_INT in wing buffew */
		case 177: /* CP_INT in IB1 */
		case 178: /* CP_INT in IB2 */
			DWM_DEBUG("IH: CP int: 0x%08x\n", swc_data);
			wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
			bweak;
		case 181: /* CP EOP event */
			DWM_DEBUG("IH: CP EOP\n");
			if (wdev->famiwy >= CHIP_CAYMAN) {
				switch (swc_data) {
				case 0:
					wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
					bweak;
				case 1:
					wadeon_fence_pwocess(wdev, CAYMAN_WING_TYPE_CP1_INDEX);
					bweak;
				case 2:
					wadeon_fence_pwocess(wdev, CAYMAN_WING_TYPE_CP2_INDEX);
					bweak;
				}
			} ewse
				wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
			bweak;
		case 224: /* DMA twap event */
			DWM_DEBUG("IH: DMA twap\n");
			wadeon_fence_pwocess(wdev, W600_WING_TYPE_DMA_INDEX);
			bweak;
		case 230: /* thewmaw wow to high */
			DWM_DEBUG("IH: thewmaw wow to high\n");
			wdev->pm.dpm.thewmaw.high_to_wow = fawse;
			queue_thewmaw = twue;
			bweak;
		case 231: /* thewmaw high to wow */
			DWM_DEBUG("IH: thewmaw high to wow\n");
			wdev->pm.dpm.thewmaw.high_to_wow = twue;
			queue_thewmaw = twue;
			bweak;
		case 233: /* GUI IDWE */
			DWM_DEBUG("IH: GUI idwe\n");
			bweak;
		case 244: /* DMA twap event */
			if (wdev->famiwy >= CHIP_CAYMAN) {
				DWM_DEBUG("IH: DMA1 twap\n");
				wadeon_fence_pwocess(wdev, CAYMAN_WING_TYPE_DMA1_INDEX);
			}
			bweak;
		defauwt:
			DWM_DEBUG("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
			bweak;
		}

		/* wptw/wptw awe in bytes! */
		wptw += 16;
		wptw &= wdev->ih.ptw_mask;
		WWEG32(IH_WB_WPTW, wptw);
	}
	if (queue_dp)
		scheduwe_wowk(&wdev->dp_wowk);
	if (queue_hotpwug)
		scheduwe_dewayed_wowk(&wdev->hotpwug_wowk, 0);
	if (queue_hdmi)
		scheduwe_wowk(&wdev->audio_wowk);
	if (queue_thewmaw && wdev->pm.dpm_enabwed)
		scheduwe_wowk(&wdev->pm.dpm.thewmaw.wowk);
	wdev->ih.wptw = wptw;
	atomic_set(&wdev->ih.wock, 0);

	/* make suwe wptw hasn't changed whiwe pwocessing */
	wptw = evewgween_get_ih_wptw(wdev);
	if (wptw != wptw)
		goto westawt_ih;

	wetuwn IWQ_HANDWED;
}

static void evewgween_uvd_init(stwuct wadeon_device *wdev)
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

static void evewgween_uvd_stawt(stwuct wadeon_device *wdev)
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

static void evewgween_uvd_wesume(stwuct wadeon_device *wdev)
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

static int evewgween_stawtup(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
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

	if (ASIC_IS_DCE5(wdev) && !wdev->pm.dpm_enabwed) {
		w = ni_mc_woad_micwocode(wdev);
		if (w) {
			DWM_EWWOW("Faiwed to woad MC fiwmwawe!\n");
			wetuwn w;
		}
	}

	if (wdev->fwags & WADEON_IS_AGP) {
		evewgween_agp_enabwe(wdev);
	} ewse {
		w = evewgween_pcie_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}
	evewgween_gpu_init(wdev);

	/* awwocate wwc buffews */
	if (wdev->fwags & WADEON_IS_IGP) {
		wdev->wwc.weg_wist = sumo_wwc_save_westowe_wegistew_wist;
		wdev->wwc.weg_wist_size =
			(u32)AWWAY_SIZE(sumo_wwc_save_westowe_wegistew_wist);
		wdev->wwc.cs_data = evewgween_cs_data;
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

	w = wadeon_fence_dwivew_stawt_wing(wdev, W600_WING_TYPE_DMA_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing DMA fences (%d).\n", w);
		wetuwn w;
	}

	evewgween_uvd_stawt(wdev);

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

	wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, WADEON_WB_CP_WPTW_OFFSET,
			     WADEON_CP_PACKET2);
	if (w)
		wetuwn w;

	wing = &wdev->wing[W600_WING_TYPE_DMA_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, W600_WB_DMA_WPTW_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0));
	if (w)
		wetuwn w;

	w = evewgween_cp_woad_micwocode(wdev);
	if (w)
		wetuwn w;
	w = evewgween_cp_wesume(wdev);
	if (w)
		wetuwn w;
	w = w600_dma_wesume(wdev);
	if (w)
		wetuwn w;

	evewgween_uvd_wesume(wdev);

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_audio_init(wdev);
	if (w) {
		DWM_EWWOW("wadeon: audio init faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

int evewgween_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* weset the asic, the gfx bwocks awe often in a bad state
	 * aftew the dwivew is unwoaded ow aftew a wesume
	 */
	if (wadeon_asic_weset(wdev))
		dev_wawn(wdev->dev, "GPU weset faiwed !\n");
	/* Do not weset GPU befowe posting, on wv770 hw unwike on w500 hw,
	 * posting wiww pewfowm necessawy task to bwing back GPU into good
	 * shape.
	 */
	/* post cawd */
	atom_asic_init(wdev->mode_info.atom_context);

	/* init gowden wegistews */
	evewgween_init_gowden_wegistews(wdev);

	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_wesume(wdev);

	wdev->accew_wowking = twue;
	w = evewgween_stawtup(wdev);
	if (w) {
		DWM_EWWOW("evewgween stawtup faiwed on wesume\n");
		wdev->accew_wowking = fawse;
		wetuwn w;
	}

	wetuwn w;

}

int evewgween_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	wadeon_audio_fini(wdev);
	if (wdev->has_uvd) {
		wadeon_uvd_suspend(wdev);
		uvd_v1_0_fini(wdev);
	}
	w700_cp_stop(wdev);
	w600_dma_stop(wdev);
	evewgween_iwq_suspend(wdev);
	wadeon_wb_disabwe(wdev);
	evewgween_pcie_gawt_disabwe(wdev);

	wetuwn 0;
}

/* Pwan is to move initiawization in that function and use
 * hewpew function so that wadeon_device_init pwetty much
 * do nothing mowe than cawwing asic specific function. This
 * shouwd awso awwow to wemove a bunch of cawwback function
 * wike vwam_info.
 */
int evewgween_init(stwuct wadeon_device *wdev)
{
	int w;

	/* Wead BIOS */
	if (!wadeon_get_bios(wdev)) {
		if (ASIC_IS_AVIVO(wdev))
			wetuwn -EINVAW;
	}
	/* Must be an ATOMBIOS */
	if (!wdev->is_atom_bios) {
		dev_eww(wdev->dev, "Expecting atombios fow evewgween GPU\n");
		wetuwn -EINVAW;
	}
	w = wadeon_atombios_init(wdev);
	if (w)
		wetuwn w;
	/* weset the asic, the gfx bwocks awe often in a bad state
	 * aftew the dwivew is unwoaded ow aftew a wesume
	 */
	if (wadeon_asic_weset(wdev))
		dev_wawn(wdev->dev, "GPU weset faiwed !\n");
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
	evewgween_init_gowden_wegistews(wdev);
	/* Initiawize scwatch wegistews */
	w600_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* Initiawize cwocks */
	wadeon_get_cwock_info(wdev->ddev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	/* initiawize AGP */
	if (wdev->fwags & WADEON_IS_AGP) {
		w = wadeon_agp_init(wdev);
		if (w)
			wadeon_agp_disabwe(wdev);
	}
	/* initiawize memowy contwowwew */
	w = evewgween_mc_init(wdev);
	if (w)
		wetuwn w;
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;

	if (ASIC_IS_DCE5(wdev)) {
		if (!wdev->me_fw || !wdev->pfp_fw || !wdev->wwc_fw || !wdev->mc_fw) {
			w = ni_init_micwocode(wdev);
			if (w) {
				DWM_EWWOW("Faiwed to woad fiwmwawe!\n");
				wetuwn w;
			}
		}
	} ewse {
		if (!wdev->me_fw || !wdev->pfp_fw || !wdev->wwc_fw) {
			w = w600_init_micwocode(wdev);
			if (w) {
				DWM_EWWOW("Faiwed to woad fiwmwawe!\n");
				wetuwn w;
			}
		}
	}

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->wing[WADEON_WING_TYPE_GFX_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[WADEON_WING_TYPE_GFX_INDEX], 1024 * 1024);

	wdev->wing[W600_WING_TYPE_DMA_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[W600_WING_TYPE_DMA_INDEX], 64 * 1024);

	evewgween_uvd_init(wdev);

	wdev->ih.wing_obj = NUWW;
	w600_ih_wing_init(wdev, 64 * 1024);

	w = w600_pcie_gawt_init(wdev);
	if (w)
		wetuwn w;

	wdev->accew_wowking = twue;
	w = evewgween_stawtup(wdev);
	if (w) {
		dev_eww(wdev->dev, "disabwing GPU accewewation\n");
		w700_cp_fini(wdev);
		w600_dma_fini(wdev);
		w600_iwq_fini(wdev);
		if (wdev->fwags & WADEON_IS_IGP)
			sumo_wwc_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		evewgween_pcie_gawt_fini(wdev);
		wdev->accew_wowking = fawse;
	}

	/* Don't stawt up if the MC ucode is missing on BTC pawts.
	 * The defauwt cwocks and vowtages befowe the MC ucode
	 * is woaded awe not suffient fow advanced opewations.
	 */
	if (ASIC_IS_DCE5(wdev)) {
		if (!wdev->mc_fw && !(wdev->fwags & WADEON_IS_IGP)) {
			DWM_EWWOW("wadeon: MC ucode wequiwed fow NI+.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

void evewgween_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	wadeon_audio_fini(wdev);
	w700_cp_fini(wdev);
	w600_dma_fini(wdev);
	w600_iwq_fini(wdev);
	if (wdev->fwags & WADEON_IS_IGP)
		sumo_wwc_fini(wdev);
	wadeon_wb_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	uvd_v1_0_fini(wdev);
	wadeon_uvd_fini(wdev);
	evewgween_pcie_gawt_fini(wdev);
	w600_vwam_scwatch_fini(wdev);
	wadeon_gem_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_agp_fini(wdev);
	wadeon_bo_fini(wdev);
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}

void evewgween_pcie_gen2_enabwe(stwuct wadeon_device *wdev)
{
	u32 wink_width_cntw, speed_cntw;

	if (wadeon_pcie_gen2 == 0)
		wetuwn;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn;

	/* x2 cawds have a speciaw sequence */
	if (ASIC_IS_X2(wdev))
		wetuwn;

	if ((wdev->pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT) &&
		(wdev->pdev->bus->max_bus_speed != PCIE_SPEED_8_0GT))
		wetuwn;

	speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if (speed_cntw & WC_CUWWENT_DATA_WATE) {
		DWM_INFO("PCIE gen 2 wink speeds awweady enabwed\n");
		wetuwn;
	}

	DWM_INFO("enabwing PCIE gen 2 wink speeds, disabwe with wadeon.pcie_gen2=0\n");

	if ((speed_cntw & WC_OTHEW_SIDE_EVEW_SENT_GEN2) ||
	    (speed_cntw & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {

		wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
		wink_width_cntw &= ~WC_UPCONFIGUWE_DIS;
		WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);

		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		speed_cntw &= ~WC_TAWGET_WINK_SPEED_OVEWWIDE_EN;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		speed_cntw |= WC_CWW_FAIWED_SPD_CHANGE_CNT;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		speed_cntw &= ~WC_CWW_FAIWED_SPD_CHANGE_CNT;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		speed_cntw |= WC_GEN2_EN_STWAP;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

	} ewse {
		wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
		/* XXX: onwy disabwe it if gen1 bwidge vendow == 0x111d ow 0x1106 */
		if (1)
			wink_width_cntw |= WC_UPCONFIGUWE_DIS;
		ewse
			wink_width_cntw &= ~WC_UPCONFIGUWE_DIS;
		WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
	}
}

void evewgween_pwogwam_aspm(stwuct wadeon_device *wdev)
{
	u32 data, owig;
	u32 pcie_wc_cntw, pcie_wc_cntw_owd;
	boow disabwe_w0s, disabwe_w1 = fawse, disabwe_pwwoff_in_w1 = fawse;
	/* fusion_pwatfowm = twue
	 * if the system is a fusion system
	 * (APU ow DGPU in a fusion system).
	 * todo: check if the system is a fusion pwatfowm.
	 */
	boow fusion_pwatfowm = fawse;

	if (wadeon_aspm == 0)
		wetuwn;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn;

	switch (wdev->famiwy) {
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
	case CHIP_JUNIPEW:
	case CHIP_WEDWOOD:
	case CHIP_CEDAW:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_PAWM:
	case CHIP_AWUBA:
		disabwe_w0s = twue;
		bweak;
	defauwt:
		disabwe_w0s = fawse;
		bweak;
	}

	if (wdev->fwags & WADEON_IS_IGP)
		fusion_pwatfowm = twue; /* XXX awso dGPUs in a fusion system */

	data = owig = WWEG32_PIF_PHY0(PB0_PIF_PAIWING);
	if (fusion_pwatfowm)
		data &= ~MUWTI_PIF;
	ewse
		data |= MUWTI_PIF;
	if (data != owig)
		WWEG32_PIF_PHY0(PB0_PIF_PAIWING, data);

	data = owig = WWEG32_PIF_PHY1(PB1_PIF_PAIWING);
	if (fusion_pwatfowm)
		data &= ~MUWTI_PIF;
	ewse
		data |= MUWTI_PIF;
	if (data != owig)
		WWEG32_PIF_PHY1(PB1_PIF_PAIWING, data);

	pcie_wc_cntw = pcie_wc_cntw_owd = WWEG32_PCIE_POWT(PCIE_WC_CNTW);
	pcie_wc_cntw &= ~(WC_W0S_INACTIVITY_MASK | WC_W1_INACTIVITY_MASK);
	if (!disabwe_w0s) {
		if (wdev->famiwy >= CHIP_BAWTS)
			pcie_wc_cntw |= WC_W0S_INACTIVITY(7);
		ewse
			pcie_wc_cntw |= WC_W0S_INACTIVITY(3);
	}

	if (!disabwe_w1) {
		if (wdev->famiwy >= CHIP_BAWTS)
			pcie_wc_cntw |= WC_W1_INACTIVITY(7);
		ewse
			pcie_wc_cntw |= WC_W1_INACTIVITY(8);

		if (!disabwe_pwwoff_in_w1) {
			data = owig = WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_0);
			data &= ~(PWW_POWEW_STATE_IN_OFF_0_MASK | PWW_POWEW_STATE_IN_TXS2_0_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_0(7) | PWW_POWEW_STATE_IN_TXS2_0(7);
			if (data != owig)
				WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_0, data);

			data = owig = WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_1);
			data &= ~(PWW_POWEW_STATE_IN_OFF_1_MASK | PWW_POWEW_STATE_IN_TXS2_1_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_1(7) | PWW_POWEW_STATE_IN_TXS2_1(7);
			if (data != owig)
				WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_1, data);

			data = owig = WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_0);
			data &= ~(PWW_POWEW_STATE_IN_OFF_0_MASK | PWW_POWEW_STATE_IN_TXS2_0_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_0(7) | PWW_POWEW_STATE_IN_TXS2_0(7);
			if (data != owig)
				WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_0, data);

			data = owig = WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_1);
			data &= ~(PWW_POWEW_STATE_IN_OFF_1_MASK | PWW_POWEW_STATE_IN_TXS2_1_MASK);
			data |= PWW_POWEW_STATE_IN_OFF_1(7) | PWW_POWEW_STATE_IN_TXS2_1(7);
			if (data != owig)
				WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_1, data);

			if (wdev->famiwy >= CHIP_BAWTS) {
				data = owig = WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_0);
				data &= ~PWW_WAMP_UP_TIME_0_MASK;
				data |= PWW_WAMP_UP_TIME_0(4);
				if (data != owig)
					WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_0, data);

				data = owig = WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_1);
				data &= ~PWW_WAMP_UP_TIME_1_MASK;
				data |= PWW_WAMP_UP_TIME_1(4);
				if (data != owig)
					WWEG32_PIF_PHY0(PB0_PIF_PWWDOWN_1, data);

				data = owig = WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_0);
				data &= ~PWW_WAMP_UP_TIME_0_MASK;
				data |= PWW_WAMP_UP_TIME_0(4);
				if (data != owig)
					WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_0, data);

				data = owig = WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_1);
				data &= ~PWW_WAMP_UP_TIME_1_MASK;
				data |= PWW_WAMP_UP_TIME_1(4);
				if (data != owig)
					WWEG32_PIF_PHY1(PB1_PIF_PWWDOWN_1, data);
			}

			data = owig = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
			data &= ~WC_DYN_WANES_PWW_STATE_MASK;
			data |= WC_DYN_WANES_PWW_STATE(3);
			if (data != owig)
				WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, data);

			if (wdev->famiwy >= CHIP_BAWTS) {
				data = owig = WWEG32_PIF_PHY0(PB0_PIF_CNTW);
				data &= ~WS2_EXIT_TIME_MASK;
				data |= WS2_EXIT_TIME(1);
				if (data != owig)
					WWEG32_PIF_PHY0(PB0_PIF_CNTW, data);

				data = owig = WWEG32_PIF_PHY1(PB1_PIF_CNTW);
				data &= ~WS2_EXIT_TIME_MASK;
				data |= WS2_EXIT_TIME(1);
				if (data != owig)
					WWEG32_PIF_PHY1(PB1_PIF_CNTW, data);
			}
		}
	}

	/* evewgween pawts onwy */
	if (wdev->famiwy < CHIP_BAWTS)
		pcie_wc_cntw |= WC_PMI_TO_W1_DIS;

	if (pcie_wc_cntw != pcie_wc_cntw_owd)
		WWEG32_PCIE_POWT(PCIE_WC_CNTW, pcie_wc_cntw);
}
