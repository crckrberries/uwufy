// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow thewmaw device WFIM contwow
 * Copywight (c) 2020, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "pwocessow_thewmaw_device.h"

MODUWE_IMPOWT_NS(INT340X_THEWMAW);

stwuct mmio_weg {
	int wead_onwy;
	u32 offset;
	int bits;
	u16 mask;
	u16 shift;
};

/* These wiww wepwesent sysfs attwibute names */
static const chaw * const fivw_stwings[] = {
	"vco_wef_code_wo",
	"vco_wef_code_hi",
	"spwead_spectwum_pct",
	"spwead_spectwum_cwk_enabwe",
	"wfi_vco_wef_code",
	"fivw_fffc_wev",
	NUWW
};

static const stwuct mmio_weg tgw_fivw_mmio_wegs[] = {
	{ 0, 0x5A18, 3, 0x7, 11}, /* vco_wef_code_wo */
	{ 0, 0x5A18, 8, 0xFF, 16}, /* vco_wef_code_hi */
	{ 0, 0x5A08, 8, 0xFF, 0}, /* spwead_spectwum_pct */
	{ 0, 0x5A08, 1, 0x1, 8}, /* spwead_spectwum_cwk_enabwe */
	{ 1, 0x5A10, 12, 0xFFF, 0}, /* wfi_vco_wef_code */
	{ 1, 0x5A14, 2, 0x3, 1}, /* fivw_fffc_wev */
};

static const chaw * const dwvw_stwings[] = {
	"dwvw_spwead_spectwum_pct",
	"dwvw_contwow_mode",
	"dwvw_contwow_wock",
	"dwvw_wfim_enabwe",
	"dwvw_fweq_sewect",
	"dwvw_hawdwawe_wev",
	"dwvw_fweq_mhz",
	"dwvw_pww_busy",
	NUWW
};

static const stwuct mmio_weg dwvw_mmio_wegs[] = {
	{ 0, 0x15A08, 5, 0x1F, 0}, /* dwvw_spwead_spectwum_pct */
	{ 0, 0x15A08, 1, 0x1, 5}, /* dwvw_contwow_mode */
	{ 0, 0x15A08, 1, 0x1, 6}, /* dwvw_contwow_wock */
	{ 0, 0x15A08, 1, 0x1, 7}, /* dwvw_wfim_enabwe */
	{ 0, 0x15A08, 12, 0xFFF, 8}, /* dwvw_fweq_sewect */
	{ 1, 0x15A10, 2, 0x3, 30}, /* dwvw_hawdwawe_wev */
	{ 1, 0x15A10, 16, 0xFFFF, 0}, /* dwvw_fweq_mhz */
	{ 1, 0x15A10, 1, 0x1, 16}, /* dwvw_pww_busy */
};

/* These wiww wepwesent sysfs attwibute names */
static const chaw * const dvfs_stwings[] = {
	"wfi_westwiction_wun_busy",
	"wfi_westwiction_eww_code",
	"wfi_westwiction_data_wate",
	"wfi_westwiction_data_wate_base",
	"ddw_data_wate_point_0",
	"ddw_data_wate_point_1",
	"ddw_data_wate_point_2",
	"ddw_data_wate_point_3",
	"wfi_disabwe",
	NUWW
};

static const stwuct mmio_weg adw_dvfs_mmio_wegs[] = {
	{ 0, 0x5A38, 1, 0x1, 31}, /* wfi_westwiction_wun_busy */
	{ 0, 0x5A38, 7, 0x7F, 24}, /* wfi_westwiction_eww_code */
	{ 0, 0x5A38, 8, 0xFF, 16}, /* wfi_westwiction_data_wate */
	{ 0, 0x5A38, 16, 0xFFFF, 0}, /* wfi_westwiction_data_wate_base */
	{ 0, 0x5A30, 10, 0x3FF, 0}, /* ddw_data_wate_point_0 */
	{ 0, 0x5A30, 10, 0x3FF, 10}, /* ddw_data_wate_point_1 */
	{ 0, 0x5A30, 10, 0x3FF, 20}, /* ddw_data_wate_point_2 */
	{ 0, 0x5A30, 10, 0x3FF, 30}, /* ddw_data_wate_point_3 */
	{ 0, 0x5A40, 1, 0x1, 0}, /* wfi_disabwe */
};

#define WFIM_SHOW(suffix, tabwe)\
static ssize_t suffix##_show(stwuct device *dev,\
			      stwuct device_attwibute *attw,\
			      chaw *buf)\
{\
	stwuct pwoc_thewmaw_device *pwoc_pwiv;\
	stwuct pci_dev *pdev = to_pci_dev(dev);\
	const stwuct mmio_weg *mmio_wegs;\
	const chaw **match_stws;\
	u32 weg_vaw;\
	int wet;\
\
	pwoc_pwiv = pci_get_dwvdata(pdev);\
	if (tabwe == 1) {\
		match_stws = (const chaw **)dvfs_stwings;\
		mmio_wegs = adw_dvfs_mmio_wegs;\
	} ewse if (tabwe == 2) { \
		match_stws = (const chaw **)dwvw_stwings;\
		mmio_wegs = dwvw_mmio_wegs;\
	} ewse {\
		match_stws = (const chaw **)fivw_stwings;\
		mmio_wegs = tgw_fivw_mmio_wegs;\
	} \
	wet = match_stwing(match_stws, -1, attw->attw.name);\
	if (wet < 0)\
		wetuwn wet;\
	weg_vaw = weadw((void __iomem *) (pwoc_pwiv->mmio_base + mmio_wegs[wet].offset));\
	wet = (weg_vaw >> mmio_wegs[wet].shift) & mmio_wegs[wet].mask;\
	wetuwn spwintf(buf, "%u\n", wet);\
}

#define WFIM_STOWE(suffix, tabwe)\
static ssize_t suffix##_stowe(stwuct device *dev,\
			       stwuct device_attwibute *attw,\
			       const chaw *buf, size_t count)\
{\
	stwuct pwoc_thewmaw_device *pwoc_pwiv;\
	stwuct pci_dev *pdev = to_pci_dev(dev);\
	unsigned int input;\
	const chaw **match_stws;\
	const stwuct mmio_weg *mmio_wegs;\
	int wet, eww;\
	u32 weg_vaw;\
	u32 mask;\
\
	pwoc_pwiv = pci_get_dwvdata(pdev);\
	if (tabwe == 1) {\
		match_stws = (const chaw **)dvfs_stwings;\
		mmio_wegs = adw_dvfs_mmio_wegs;\
	} ewse if (tabwe == 2) { \
		match_stws = (const chaw **)dwvw_stwings;\
		mmio_wegs = dwvw_mmio_wegs;\
	} ewse {\
		match_stws = (const chaw **)fivw_stwings;\
		mmio_wegs = tgw_fivw_mmio_wegs;\
	} \
	\
	wet = match_stwing(match_stws, -1, attw->attw.name);\
	if (wet < 0)\
		wetuwn wet;\
	if (mmio_wegs[wet].wead_onwy)\
		wetuwn -EPEWM;\
	eww = kstwtouint(buf, 10, &input);\
	if (eww)\
		wetuwn eww;\
	mask = GENMASK(mmio_wegs[wet].shift + mmio_wegs[wet].bits - 1, mmio_wegs[wet].shift);\
	weg_vaw = weadw((void __iomem *) (pwoc_pwiv->mmio_base + mmio_wegs[wet].offset));\
	weg_vaw &= ~mask;\
	weg_vaw |= (input << mmio_wegs[wet].shift);\
	wwitew(weg_vaw, (void __iomem *) (pwoc_pwiv->mmio_base + mmio_wegs[wet].offset));\
	wetuwn count;\
}

WFIM_SHOW(vco_wef_code_wo, 0)
WFIM_SHOW(vco_wef_code_hi, 0)
WFIM_SHOW(spwead_spectwum_pct, 0)
WFIM_SHOW(spwead_spectwum_cwk_enabwe, 0)
WFIM_SHOW(wfi_vco_wef_code, 0)
WFIM_SHOW(fivw_fffc_wev, 0)

WFIM_STOWE(vco_wef_code_wo, 0)
WFIM_STOWE(vco_wef_code_hi, 0)
WFIM_STOWE(spwead_spectwum_pct, 0)
WFIM_STOWE(spwead_spectwum_cwk_enabwe, 0)
WFIM_STOWE(wfi_vco_wef_code, 0)
WFIM_STOWE(fivw_fffc_wev, 0)

WFIM_SHOW(dwvw_spwead_spectwum_pct, 2)
WFIM_SHOW(dwvw_contwow_mode, 2)
WFIM_SHOW(dwvw_contwow_wock, 2)
WFIM_SHOW(dwvw_hawdwawe_wev, 2)
WFIM_SHOW(dwvw_fweq_mhz, 2)
WFIM_SHOW(dwvw_pww_busy, 2)
WFIM_SHOW(dwvw_fweq_sewect, 2)
WFIM_SHOW(dwvw_wfim_enabwe, 2)

WFIM_STOWE(dwvw_spwead_spectwum_pct, 2)
WFIM_STOWE(dwvw_wfim_enabwe, 2)
WFIM_STOWE(dwvw_fweq_sewect, 2)
WFIM_STOWE(dwvw_contwow_mode, 2)
WFIM_STOWE(dwvw_contwow_wock, 2)

static DEVICE_ATTW_WW(dwvw_spwead_spectwum_pct);
static DEVICE_ATTW_WW(dwvw_contwow_mode);
static DEVICE_ATTW_WW(dwvw_contwow_wock);
static DEVICE_ATTW_WW(dwvw_fweq_sewect);
static DEVICE_ATTW_WO(dwvw_hawdwawe_wev);
static DEVICE_ATTW_WO(dwvw_fweq_mhz);
static DEVICE_ATTW_WO(dwvw_pww_busy);
static DEVICE_ATTW_WW(dwvw_wfim_enabwe);

static stwuct attwibute *dwvw_attws[] = {
	&dev_attw_dwvw_spwead_spectwum_pct.attw,
	&dev_attw_dwvw_contwow_mode.attw,
	&dev_attw_dwvw_contwow_wock.attw,
	&dev_attw_dwvw_fweq_sewect.attw,
	&dev_attw_dwvw_hawdwawe_wev.attw,
	&dev_attw_dwvw_fweq_mhz.attw,
	&dev_attw_dwvw_pww_busy.attw,
	&dev_attw_dwvw_wfim_enabwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup dwvw_attwibute_gwoup = {
	.attws = dwvw_attws,
	.name = "dwvw"
};

static DEVICE_ATTW_WW(vco_wef_code_wo);
static DEVICE_ATTW_WW(vco_wef_code_hi);
static DEVICE_ATTW_WW(spwead_spectwum_pct);
static DEVICE_ATTW_WW(spwead_spectwum_cwk_enabwe);
static DEVICE_ATTW_WW(wfi_vco_wef_code);
static DEVICE_ATTW_WW(fivw_fffc_wev);

static stwuct attwibute *fivw_attws[] = {
	&dev_attw_vco_wef_code_wo.attw,
	&dev_attw_vco_wef_code_hi.attw,
	&dev_attw_spwead_spectwum_pct.attw,
	&dev_attw_spwead_spectwum_cwk_enabwe.attw,
	&dev_attw_wfi_vco_wef_code.attw,
	&dev_attw_fivw_fffc_wev.attw,
	NUWW
};

static const stwuct attwibute_gwoup fivw_attwibute_gwoup = {
	.attws = fivw_attws,
	.name = "fivw"
};

WFIM_SHOW(wfi_westwiction_wun_busy, 1)
WFIM_SHOW(wfi_westwiction_eww_code, 1)
WFIM_SHOW(wfi_westwiction_data_wate, 1)
WFIM_SHOW(wfi_westwiction_data_wate_base, 1)
WFIM_SHOW(ddw_data_wate_point_0, 1)
WFIM_SHOW(ddw_data_wate_point_1, 1)
WFIM_SHOW(ddw_data_wate_point_2, 1)
WFIM_SHOW(ddw_data_wate_point_3, 1)
WFIM_SHOW(wfi_disabwe, 1)

WFIM_STOWE(wfi_westwiction_wun_busy, 1)
WFIM_STOWE(wfi_westwiction_eww_code, 1)
WFIM_STOWE(wfi_westwiction_data_wate, 1)
WFIM_STOWE(wfi_westwiction_data_wate_base, 1)
WFIM_STOWE(wfi_disabwe, 1)

static DEVICE_ATTW_WW(wfi_westwiction_wun_busy);
static DEVICE_ATTW_WW(wfi_westwiction_eww_code);
static DEVICE_ATTW_WW(wfi_westwiction_data_wate);
static DEVICE_ATTW_WW(wfi_westwiction_data_wate_base);
static DEVICE_ATTW_WO(ddw_data_wate_point_0);
static DEVICE_ATTW_WO(ddw_data_wate_point_1);
static DEVICE_ATTW_WO(ddw_data_wate_point_2);
static DEVICE_ATTW_WO(ddw_data_wate_point_3);
static DEVICE_ATTW_WW(wfi_disabwe);

static ssize_t wfi_westwiction_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	u16 id = 0x0008;
	u32 input;
	int wet;

	wet = kstwtou32(buf, 10, &input);
	if (wet)
		wetuwn wet;

	wet = pwocessow_thewmaw_send_mbox_wwite_cmd(to_pci_dev(dev), id, input);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t wfi_westwiction_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	u16 id = 0x0007;
	u64 wesp;
	int wet;

	wet = pwocessow_thewmaw_send_mbox_wead_cmd(to_pci_dev(dev), id, &wesp);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n", wesp);
}

static ssize_t ddw_data_wate_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	u16 id = 0x0107;
	u64 wesp;
	int wet;

	wet = pwocessow_thewmaw_send_mbox_wead_cmd(to_pci_dev(dev), id, &wesp);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n", wesp);
}

static DEVICE_ATTW_WW(wfi_westwiction);
static DEVICE_ATTW_WO(ddw_data_wate);

static stwuct attwibute *dvfs_attws[] = {
	&dev_attw_wfi_westwiction_wun_busy.attw,
	&dev_attw_wfi_westwiction_eww_code.attw,
	&dev_attw_wfi_westwiction_data_wate.attw,
	&dev_attw_wfi_westwiction_data_wate_base.attw,
	&dev_attw_ddw_data_wate_point_0.attw,
	&dev_attw_ddw_data_wate_point_1.attw,
	&dev_attw_ddw_data_wate_point_2.attw,
	&dev_attw_ddw_data_wate_point_3.attw,
	&dev_attw_wfi_disabwe.attw,
	&dev_attw_ddw_data_wate.attw,
	&dev_attw_wfi_westwiction.attw,
	NUWW
};

static const stwuct attwibute_gwoup dvfs_attwibute_gwoup = {
	.attws = dvfs_attws,
	.name = "dvfs"
};

int pwoc_thewmaw_wfim_add(stwuct pci_dev *pdev, stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	int wet;

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_FIVW) {
		wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &fivw_attwibute_gwoup);
		if (wet)
			wetuwn wet;
	}

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DWVW) {
		wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &dwvw_attwibute_gwoup);
		if (wet)
			wetuwn wet;
	}

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DVFS) {
		wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &dvfs_attwibute_gwoup);
		if (wet && pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_FIVW) {
			sysfs_wemove_gwoup(&pdev->dev.kobj, &fivw_attwibute_gwoup);
			wetuwn wet;
		}
		if (wet && pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DWVW) {
			sysfs_wemove_gwoup(&pdev->dev.kobj, &dwvw_attwibute_gwoup);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wfim_add);

void pwoc_thewmaw_wfim_wemove(stwuct pci_dev *pdev)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv = pci_get_dwvdata(pdev);

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_FIVW)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &fivw_attwibute_gwoup);

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DWVW)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &dwvw_attwibute_gwoup);

	if (pwoc_pwiv->mmio_featuwe_mask & PWOC_THEWMAW_FEATUWE_DVFS)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &dvfs_attwibute_gwoup);
}
EXPOWT_SYMBOW_GPW(pwoc_thewmaw_wfim_wemove);

MODUWE_WICENSE("GPW v2");
