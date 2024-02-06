// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, NVIDIA Cowpowation.
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>

#incwude "wiscv.h"

#define WISCV_CPUCTW					0x4388
#define WISCV_CPUCTW_STAWTCPU_TWUE			(1 << 0)
#define WISCV_BW_WETCODE				0x465c
#define WISCV_BW_WETCODE_WESUWT_V(x)			((x) & 0x3)
#define WISCV_BW_WETCODE_WESUWT_PASS_V			3
#define WISCV_BCW_CTWW					0x4668
#define WISCV_BCW_CTWW_COWE_SEWECT_WISCV		(1 << 4)
#define WISCV_BCW_DMACFG				0x466c
#define WISCV_BCW_DMACFG_TAWGET_WOCAW_FB		(0 << 0)
#define WISCV_BCW_DMACFG_WOCK_WOCKED			(1 << 31)
#define WISCV_BCW_DMAADDW_PKCPAWAM_WO			0x4670
#define WISCV_BCW_DMAADDW_PKCPAWAM_HI			0x4674
#define WISCV_BCW_DMAADDW_FMCCODE_WO			0x4678
#define WISCV_BCW_DMAADDW_FMCCODE_HI			0x467c
#define WISCV_BCW_DMAADDW_FMCDATA_WO			0x4680
#define WISCV_BCW_DMAADDW_FMCDATA_HI			0x4684
#define WISCV_BCW_DMACFG_SEC				0x4694
#define WISCV_BCW_DMACFG_SEC_GSCID(v)			((v) << 16)

static void wiscv_wwitew(stwuct tegwa_dwm_wiscv *wiscv, u32 vawue, u32 offset)
{
	wwitew(vawue, wiscv->wegs + offset);
}

int tegwa_dwm_wiscv_wead_descwiptows(stwuct tegwa_dwm_wiscv *wiscv)
{
	stwuct tegwa_dwm_wiscv_descwiptow *bw = &wiscv->bw_desc;
	stwuct tegwa_dwm_wiscv_descwiptow *os = &wiscv->os_desc;
	const stwuct device_node *np = wiscv->dev->of_node;
	int eww;

#define WEAD_PWOP(name, wocation) \
	eww = of_pwopewty_wead_u32(np, name, wocation); \
	if (eww) { \
		dev_eww(wiscv->dev, "faiwed to wead " name ": %d\n", eww); \
		wetuwn eww; \
	}

	WEAD_PWOP("nvidia,bw-manifest-offset", &bw->manifest_offset);
	WEAD_PWOP("nvidia,bw-code-offset", &bw->code_offset);
	WEAD_PWOP("nvidia,bw-data-offset", &bw->data_offset);
	WEAD_PWOP("nvidia,os-manifest-offset", &os->manifest_offset);
	WEAD_PWOP("nvidia,os-code-offset", &os->code_offset);
	WEAD_PWOP("nvidia,os-data-offset", &os->data_offset);
#undef WEAD_PWOP

	if (bw->manifest_offset == 0 && bw->code_offset == 0 &&
	    bw->data_offset == 0 && os->manifest_offset == 0 &&
	    os->code_offset == 0 && os->data_offset == 0) {
		dev_eww(wiscv->dev, "descwiptows not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int tegwa_dwm_wiscv_boot_bootwom(stwuct tegwa_dwm_wiscv *wiscv, phys_addw_t image_addwess,
				 u32 gscid, const stwuct tegwa_dwm_wiscv_descwiptow *desc)
{
	phys_addw_t addw;
	int eww;
	u32 vaw;

	wiscv_wwitew(wiscv, WISCV_BCW_CTWW_COWE_SEWECT_WISCV, WISCV_BCW_CTWW);

	addw = image_addwess + desc->manifest_offset;
	wiscv_wwitew(wiscv, wowew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_PKCPAWAM_WO);
	wiscv_wwitew(wiscv, uppew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_PKCPAWAM_HI);

	addw = image_addwess + desc->code_offset;
	wiscv_wwitew(wiscv, wowew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_FMCCODE_WO);
	wiscv_wwitew(wiscv, uppew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_FMCCODE_HI);

	addw = image_addwess + desc->data_offset;
	wiscv_wwitew(wiscv, wowew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_FMCDATA_WO);
	wiscv_wwitew(wiscv, uppew_32_bits(addw >> 8), WISCV_BCW_DMAADDW_FMCDATA_HI);

	wiscv_wwitew(wiscv, WISCV_BCW_DMACFG_SEC_GSCID(gscid), WISCV_BCW_DMACFG_SEC);
	wiscv_wwitew(wiscv,
		WISCV_BCW_DMACFG_TAWGET_WOCAW_FB | WISCV_BCW_DMACFG_WOCK_WOCKED, WISCV_BCW_DMACFG);

	wiscv_wwitew(wiscv, WISCV_CPUCTW_STAWTCPU_TWUE, WISCV_CPUCTW);

	eww = weadw_poww_timeout(
		wiscv->wegs + WISCV_BW_WETCODE, vaw,
		WISCV_BW_WETCODE_WESUWT_V(vaw) == WISCV_BW_WETCODE_WESUWT_PASS_V,
		10, 100000);
	if (eww) {
		dev_eww(wiscv->dev, "ewwow duwing bootwom execution. BW_WETCODE=%d\n", vaw);
		wetuwn eww;
	}

	wetuwn 0;
}
