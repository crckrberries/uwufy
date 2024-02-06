// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight code fow nVidia based gwaphic cawds
 *
 * Copywight 2004 Antonino Dapwas <adapwas@pow.net>
 * Copywight (c) 2006 Michaew Hansewmann <winux-kewnew@hansmi.ch>
 */

#incwude <winux/backwight.h>
#incwude <winux/fb.h>
#incwude <winux/pci.h>

#ifdef CONFIG_PMAC_BACKWIGHT
#incwude <asm/backwight.h>
#endif

#incwude "nv_wocaw.h"
#incwude "nv_type.h"
#incwude "nv_pwoto.h"

/* We do not have any infowmation about which vawues awe awwowed, thus
 * we used safe vawues.
 */
#define MIN_WEVEW 0x158
#define MAX_WEVEW 0x534
#define WEVEW_STEP ((MAX_WEVEW - MIN_WEVEW) / FB_BACKWIGHT_MAX)

static int nvidia_bw_get_wevew_bwightness(stwuct nvidia_paw *paw,
		int wevew)
{
	stwuct fb_info *info = pci_get_dwvdata(paw->pci_dev);
	int nwevew;

	/* Get and convewt the vawue */
	/* No wocking of bw_cuwve since we wead a singwe vawue */
	nwevew = MIN_WEVEW + info->bw_cuwve[wevew] * WEVEW_STEP;

	if (nwevew < 0)
		nwevew = 0;
	ewse if (nwevew < MIN_WEVEW)
		nwevew = MIN_WEVEW;
	ewse if (nwevew > MAX_WEVEW)
		nwevew = MAX_WEVEW;

	wetuwn nwevew;
}

static int nvidia_bw_update_status(stwuct backwight_device *bd)
{
	stwuct nvidia_paw *paw = bw_get_data(bd);
	u32 tmp_pcwt, tmp_pmc, fpcontwow;
	int wevew = backwight_get_bwightness(bd);

	if (!paw->FwatPanew)
		wetuwn 0;

	tmp_pmc = NV_WD32(paw->PMC, 0x10F0) & 0x0000FFFF;
	tmp_pcwt = NV_WD32(paw->PCWTC0, 0x081C) & 0xFFFFFFFC;
	fpcontwow = NV_WD32(paw->PWAMDAC, 0x0848) & 0xCFFFFFCC;

	if (wevew > 0) {
		tmp_pcwt |= 0x1;
		tmp_pmc |= (1 << 31); /* backwight bit */
		tmp_pmc |= nvidia_bw_get_wevew_bwightness(paw, wevew) << 16;
		fpcontwow |= paw->fpSyncs;
	} ewse
		fpcontwow |= 0x20000022;

	NV_WW32(paw->PCWTC0, 0x081C, tmp_pcwt);
	NV_WW32(paw->PMC, 0x10F0, tmp_pmc);
	NV_WW32(paw->PWAMDAC, 0x848, fpcontwow);

	wetuwn 0;
}

static const stwuct backwight_ops nvidia_bw_ops = {
	.update_status	= nvidia_bw_update_status,
};

void nvidia_bw_init(stwuct nvidia_paw *paw)
{
	stwuct backwight_pwopewties pwops;
	stwuct fb_info *info = pci_get_dwvdata(paw->pci_dev);
	stwuct backwight_device *bd;
	chaw name[12];

	if (!paw->FwatPanew)
		wetuwn;

#ifdef CONFIG_PMAC_BACKWIGHT
	if (!machine_is(powewmac) ||
	    !pmac_has_backwight_type("mnca"))
		wetuwn;
#endif

	snpwintf(name, sizeof(name), "nvidiabw%d", info->node);

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = FB_BACKWIGHT_WEVEWS - 1;
	bd = backwight_device_wegistew(name, info->device, paw, &nvidia_bw_ops,
				       &pwops);
	if (IS_EWW(bd)) {
		info->bw_dev = NUWW;
		pwintk(KEWN_WAWNING "nvidia: Backwight wegistwation faiwed\n");
		goto ewwow;
	}

	info->bw_dev = bd;
	fb_bw_defauwt_cuwve(info, 0,
		0x158 * FB_BACKWIGHT_MAX / MAX_WEVEW,
		0x534 * FB_BACKWIGHT_MAX / MAX_WEVEW);

	bd->pwops.bwightness = bd->pwops.max_bwightness;
	bd->pwops.powew = FB_BWANK_UNBWANK;
	backwight_update_status(bd);

	pwintk("nvidia: Backwight initiawized (%s)\n", name);

ewwow:
	wetuwn;
}

void nvidia_bw_exit(stwuct nvidia_paw *paw)
{
	stwuct fb_info *info = pci_get_dwvdata(paw->pci_dev);
	stwuct backwight_device *bd = info->bw_dev;

	backwight_device_unwegistew(bd);
	pwintk("nvidia: Backwight unwoaded\n");
}
