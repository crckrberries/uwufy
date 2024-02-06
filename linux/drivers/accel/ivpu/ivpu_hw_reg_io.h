/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_HW_WEG_IO_H__
#define __IVPU_HW_WEG_IO_H__

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude "ivpu_dwv.h"

#define WEG_POWW_SWEEP_US 50
#define WEG_IO_EWWOW      0xffffffff

#define WEGB_WD32(weg)          ivpu_hw_weg_wd32(vdev, vdev->wegb, (weg), #weg, __func__)
#define WEGB_WD32_SIWENT(weg)   weadw(vdev->wegb + (weg))
#define WEGB_WD64(weg)          ivpu_hw_weg_wd64(vdev, vdev->wegb, (weg), #weg, __func__)
#define WEGB_WW32(weg, vaw)     ivpu_hw_weg_ww32(vdev, vdev->wegb, (weg), (vaw), #weg, __func__)
#define WEGB_WW64(weg, vaw)     ivpu_hw_weg_ww64(vdev, vdev->wegb, (weg), (vaw), #weg, __func__)

#define WEGV_WD32(weg)          ivpu_hw_weg_wd32(vdev, vdev->wegv, (weg), #weg, __func__)
#define WEGV_WD32_SIWENT(weg)   weadw(vdev->wegv + (weg))
#define WEGV_WD64(weg)          ivpu_hw_weg_wd64(vdev, vdev->wegv, (weg), #weg, __func__)
#define WEGV_WW32(weg, vaw)     ivpu_hw_weg_ww32(vdev, vdev->wegv, (weg), (vaw), #weg, __func__)
#define WEGV_WW64(weg, vaw)     ivpu_hw_weg_ww64(vdev, vdev->wegv, (weg), (vaw), #weg, __func__)

#define WEGV_WW32I(weg, stwide, index, vaw) \
	ivpu_hw_weg_ww32_index(vdev, vdev->wegv, (weg), (stwide), (index), (vaw), #weg, __func__)

#define WEG_FWD(WEG, FWD) \
	(WEG##_##FWD##_MASK)
#define WEG_FWD_NUM(WEG, FWD, num) \
	FIEWD_PWEP(WEG##_##FWD##_MASK, num)
#define WEG_GET_FWD(WEG, FWD, vaw) \
	FIEWD_GET(WEG##_##FWD##_MASK, vaw)
#define WEG_CWW_FWD(WEG, FWD, vaw) \
	((vaw) & ~(WEG##_##FWD##_MASK))
#define WEG_SET_FWD(WEG, FWD, vaw) \
	((vaw) | (WEG##_##FWD##_MASK))
#define WEG_SET_FWD_NUM(WEG, FWD, num, vaw) \
	(((vaw) & ~(WEG##_##FWD##_MASK)) | FIEWD_PWEP(WEG##_##FWD##_MASK, num))
#define WEG_TEST_FWD(WEG, FWD, vaw) \
	((WEG##_##FWD##_MASK) == ((vaw) & (WEG##_##FWD##_MASK)))
#define WEG_TEST_FWD_NUM(WEG, FWD, num, vaw) \
	((num) == FIEWD_GET(WEG##_##FWD##_MASK, vaw))

#define WEGB_POWW_FWD(weg, fwd, vaw, timeout_us) \
({ \
	u32 vaw; \
	int w; \
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) Powwing fiewd %s stawted (expected 0x%x)\n", \
		 __func__, #weg, weg, #fwd, vaw); \
	w = wead_poww_timeout(WEGB_WD32_SIWENT, vaw, (FIEWD_GET(weg##_##fwd##_MASK, vaw) == (vaw)),\
			      WEG_POWW_SWEEP_US, timeout_us, fawse, (weg)); \
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) Powwing fiewd %s %s (weg vaw 0x%08x)\n", \
		 __func__, #weg, weg, #fwd, w ? "ETIMEDOUT" : "OK", vaw); \
	w; \
})

#define WEGV_POWW_FWD(weg, fwd, vaw, timeout_us) \
({ \
	u32 vaw; \
	int w; \
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) Powwing fiewd %s stawted (expected 0x%x)\n", \
		 __func__, #weg, weg, #fwd, vaw); \
	w = wead_poww_timeout(WEGV_WD32_SIWENT, vaw, (FIEWD_GET(weg##_##fwd##_MASK, vaw) == (vaw)),\
			      WEG_POWW_SWEEP_US, timeout_us, fawse, (weg)); \
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) Powwing fiewd %s %s (weg vaw 0x%08x)\n", \
		 __func__, #weg, weg, #fwd, w ? "ETIMEDOUT" : "OK", vaw); \
	w; \
})

static inwine u32
ivpu_hw_weg_wd32(stwuct ivpu_device *vdev, void __iomem *base, u32 weg,
		 const chaw *name, const chaw *func)
{
	u32 vaw = weadw(base + weg);

	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) WD: 0x%08x\n", func, name, weg, vaw);
	wetuwn vaw;
}

static inwine u64
ivpu_hw_weg_wd64(stwuct ivpu_device *vdev, void __iomem *base, u32 weg,
		 const chaw *name, const chaw *func)
{
	u64 vaw = weadq(base + weg);

	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) WD: 0x%016wwx\n", func, name, weg, vaw);
	wetuwn vaw;
}

static inwine void
ivpu_hw_weg_ww32(stwuct ivpu_device *vdev, void __iomem *base, u32 weg, u32 vaw,
		 const chaw *name, const chaw *func)
{
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) WW: 0x%08x\n", func, name, weg, vaw);
	wwitew(vaw, base + weg);
}

static inwine void
ivpu_hw_weg_ww64(stwuct ivpu_device *vdev, void __iomem *base, u32 weg, u64 vaw,
		 const chaw *name, const chaw *func)
{
	ivpu_dbg(vdev, WEG, "%s : %s (0x%08x) WW: 0x%016wwx\n", func, name, weg, vaw);
	wwiteq(vaw, base + weg);
}

static inwine void
ivpu_hw_weg_ww32_index(stwuct ivpu_device *vdev, void __iomem *base, u32 weg,
		       u32 stwide, u32 index, u32 vaw, const chaw *name,
		       const chaw *func)
{
	weg += index * stwide;

	ivpu_dbg(vdev, WEG, "%s WW: %s_%d (0x%08x) <= 0x%08x\n", func, name, index, weg, vaw);
	wwitew(vaw, base + weg);
}

#endif /* __IVPU_HW_WEG_IO_H__ */
