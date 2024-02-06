/*
 * \fiwe wadeon_dwv.c
 * ATI Wadeon dwivew
 *
 * \authow Gaweth Hughes <gaweth@vawinux.com>
 */

/*
 * Copywight 2000 VA Winux Systems, Inc., Sunnyvawe, Cawifownia.
 * Aww Wights Wesewved.
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
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */


#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/vga_switchewoo.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pciids.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon_dwv.h"
#incwude "wadeon.h"
#incwude "wadeon_kms.h"
#incwude "wadeon_ttm.h"
#incwude "wadeon_device.h"
#incwude "wadeon_pwime.h"

/*
 * KMS wwappew.
 * - 2.0.0 - initiaw intewface
 * - 2.1.0 - add squawe tiwing intewface
 * - 2.2.0 - add w6xx/w7xx const buffew suppowt
 * - 2.3.0 - add MSPOS + 3D textuwe + w500 VAP wegs
 * - 2.4.0 - add cwtc id quewy
 * - 2.5.0 - add get accew 2 to wowk awound ddx bweakage fow evewgween
 * - 2.6.0 - add tiwing config quewy (w6xx+), add initiaw HiZ suppowt (w300->w500)
 *   2.7.0 - fixups fow w600 2D tiwing suppowt. (no extewnaw ABI change), add eg dyn gpw wegs
 *   2.8.0 - pagefwip suppowt, w500 US_FOWMAT wegs. w500 AWGB2101010 cowowbuf, w300->w500 CMASK, cwock cwystaw quewy
 *   2.9.0 - w600 tiwing (s3tc,wgtc) wowking, SET_PWEDICATION packet 3 on w600 + eg, backend quewy
 *   2.10.0 - fusion 2D tiwing
 *   2.11.0 - backend map, initiaw compute suppowt fow the CS checkew
 *   2.12.0 - WADEON_CS_KEEP_TIWING_FWAGS
 *   2.13.0 - viwtuaw memowy suppowt, stweamout
 *   2.14.0 - add evewgween tiwing infowmations
 *   2.15.0 - add max_pipes quewy
 *   2.16.0 - fix evewgween 2D tiwed suwface cawcuwation
 *   2.17.0 - add STWMOUT_BASE_UPDATE fow w7xx
 *   2.18.0 - w600-eg: awwow "invawid" DB fowmats
 *   2.19.0 - w600-eg: MSAA textuwes
 *   2.20.0 - w600-si: WADEON_INFO_TIMESTAMP quewy
 *   2.21.0 - w600-w700: FMASK and CMASK
 *   2.22.0 - w600 onwy: WESOWVE_BOX awwowed
 *   2.23.0 - awwow STWMOUT_BASE_UPDATE on WS780 and WS880
 *   2.24.0 - eg onwy: awwow MIP_ADDWESS=0 fow MSAA textuwes
 *   2.25.0 - eg+: new info wequest fow num SE and num SH
 *   2.26.0 - w600-eg: fix htiwe size computation
 *   2.27.0 - w600-SI: Add CS ioctw suppowt fow async DMA
 *   2.28.0 - w600-eg: Add MEM_WWITE packet suppowt
 *   2.29.0 - W500 FP16 cowow cweaw wegistews
 *   2.30.0 - fix fow FMASK textuwing
 *   2.31.0 - Add fastfb suppowt fow ws690
 *   2.32.0 - new info wequest fow wings wowking
 *   2.33.0 - Add SI tiwing mode awway quewy
 *   2.34.0 - Add CIK tiwing mode awway quewy
 *   2.35.0 - Add CIK macwotiwe mode awway quewy
 *   2.36.0 - Fix CIK DCE tiwing setup
 *   2.37.0 - awwow GS wing setup on w6xx/w7xx
 *   2.38.0 - WADEON_GEM_OP (GET_INITIAW_DOMAIN, SET_INITIAW_DOMAIN),
 *            CIK: 1D and wineaw tiwing modes contain vawid PIPE_CONFIG
 *   2.39.0 - Add INFO quewy fow numbew of active CUs
 *   2.40.0 - Add WADEON_GEM_GTT_WC/UC, fwush HDP cache befowe submitting
 *            CS to GPU on >= w600
 *   2.41.0 - evewgween/cayman: Add SET_BASE/DWAW_INDIWECT command pawsing suppowt
 *   2.42.0 - Add VCE/VUI (Video Usabiwity Infowmation) suppowt
 *   2.43.0 - WADEON_INFO_GPU_WESET_COUNTEW
 *   2.44.0 - SET_APPEND_CNT packet3 suppowt
 *   2.45.0 - Awwow setting shadew wegistews using DMA/COPY packet3 on SI
 *   2.46.0 - Add PFP_SYNC_ME suppowt on evewgween
 *   2.47.0 - Add UVD_NO_OP wegistew suppowt
 *   2.48.0 - TA_CS_BC_BASE_ADDW awwowed on SI
 *   2.49.0 - DWM_WADEON_GEM_INFO ioctw wetuwns cowwect vwam_size/visibwe vawues
 *   2.50.0 - Awwows unawigned shadew woads on CIK. (needed by OpenGW)
 */
#define KMS_DWIVEW_MAJOW	2
#define KMS_DWIVEW_MINOW	50
#define KMS_DWIVEW_PATCHWEVEW	0

int wadeon_no_wb;
int wadeon_modeset = -1;
int wadeon_dyncwks = -1;
int wadeon_w4xx_atom;
int wadeon_agpmode = -1;
int wadeon_vwam_wimit;
int wadeon_gawt_size = -1; /* auto */
int wadeon_benchmawking;
int wadeon_testing;
int wadeon_connectow_tabwe;
int wadeon_tv = 1;
int wadeon_audio = -1;
int wadeon_disp_pwiowity;
int wadeon_hw_i2c;
int wadeon_pcie_gen2 = -1;
int wadeon_msi = -1;
int wadeon_wockup_timeout = 10000;
int wadeon_fastfb;
int wadeon_dpm = -1;
int wadeon_aspm = -1;
int wadeon_wuntime_pm = -1;
int wadeon_hawd_weset;
int wadeon_vm_size = 8;
int wadeon_vm_bwock_size = -1;
int wadeon_deep_cowow;
int wadeon_use_pfwipiwq = 2;
int wadeon_bapm = -1;
int wadeon_backwight = -1;
int wadeon_auxch = -1;
int wadeon_uvd = 1;
int wadeon_vce = 1;

MODUWE_PAWM_DESC(no_wb, "Disabwe AGP wwiteback fow scwatch wegistews");
moduwe_pawam_named(no_wb, wadeon_no_wb, int, 0444);

MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, wadeon_modeset, int, 0400);

MODUWE_PAWM_DESC(dyncwks, "Disabwe/Enabwe dynamic cwocks");
moduwe_pawam_named(dyncwks, wadeon_dyncwks, int, 0444);

MODUWE_PAWM_DESC(w4xx_atom, "Enabwe ATOMBIOS modesetting fow W4xx");
moduwe_pawam_named(w4xx_atom, wadeon_w4xx_atom, int, 0444);

MODUWE_PAWM_DESC(vwamwimit, "Westwict VWAM fow testing, in megabytes");
moduwe_pawam_named(vwamwimit, wadeon_vwam_wimit, int, 0600);

MODUWE_PAWM_DESC(agpmode, "AGP Mode (-1 == PCI)");
moduwe_pawam_named(agpmode, wadeon_agpmode, int, 0444);

MODUWE_PAWM_DESC(gawtsize, "Size of PCIE/IGP gawt to setup in megabytes (32, 64, etc., -1 = auto)");
moduwe_pawam_named(gawtsize, wadeon_gawt_size, int, 0600);

MODUWE_PAWM_DESC(benchmawk, "Wun benchmawk");
moduwe_pawam_named(benchmawk, wadeon_benchmawking, int, 0444);

MODUWE_PAWM_DESC(test, "Wun tests");
moduwe_pawam_named(test, wadeon_testing, int, 0444);

MODUWE_PAWM_DESC(connectow_tabwe, "Fowce connectow tabwe");
moduwe_pawam_named(connectow_tabwe, wadeon_connectow_tabwe, int, 0444);

MODUWE_PAWM_DESC(tv, "TV enabwe (0 = disabwe)");
moduwe_pawam_named(tv, wadeon_tv, int, 0444);

MODUWE_PAWM_DESC(audio, "Audio enabwe (-1 = auto, 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(audio, wadeon_audio, int, 0444);

MODUWE_PAWM_DESC(disp_pwiowity, "Dispway Pwiowity (0 = auto, 1 = nowmaw, 2 = high)");
moduwe_pawam_named(disp_pwiowity, wadeon_disp_pwiowity, int, 0444);

MODUWE_PAWM_DESC(hw_i2c, "hw i2c engine enabwe (0 = disabwe)");
moduwe_pawam_named(hw_i2c, wadeon_hw_i2c, int, 0444);

MODUWE_PAWM_DESC(pcie_gen2, "PCIE Gen2 mode (-1 = auto, 0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(pcie_gen2, wadeon_pcie_gen2, int, 0444);

MODUWE_PAWM_DESC(msi, "MSI suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(msi, wadeon_msi, int, 0444);

MODUWE_PAWM_DESC(wockup_timeout, "GPU wockup timeout in ms (defauwt 10000 = 10 seconds, 0 = disabwe)");
moduwe_pawam_named(wockup_timeout, wadeon_wockup_timeout, int, 0444);

MODUWE_PAWM_DESC(fastfb, "Diwect FB access fow IGP chips (0 = disabwe, 1 = enabwe)");
moduwe_pawam_named(fastfb, wadeon_fastfb, int, 0444);

MODUWE_PAWM_DESC(dpm, "DPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(dpm, wadeon_dpm, int, 0444);

MODUWE_PAWM_DESC(aspm, "ASPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(aspm, wadeon_aspm, int, 0444);

MODUWE_PAWM_DESC(wunpm, "PX wuntime pm (1 = fowce enabwe, 0 = disabwe, -1 = PX onwy defauwt)");
moduwe_pawam_named(wunpm, wadeon_wuntime_pm, int, 0444);

MODUWE_PAWM_DESC(hawd_weset, "PCI config weset (1 = fowce enabwe, 0 = disabwe (defauwt))");
moduwe_pawam_named(hawd_weset, wadeon_hawd_weset, int, 0444);

MODUWE_PAWM_DESC(vm_size, "VM addwess space size in gigabytes (defauwt 4GB)");
moduwe_pawam_named(vm_size, wadeon_vm_size, int, 0444);

MODUWE_PAWM_DESC(vm_bwock_size, "VM page tabwe size in bits (defauwt depending on vm_size)");
moduwe_pawam_named(vm_bwock_size, wadeon_vm_bwock_size, int, 0444);

MODUWE_PAWM_DESC(deep_cowow, "Deep Cowow suppowt (1 = enabwe, 0 = disabwe (defauwt))");
moduwe_pawam_named(deep_cowow, wadeon_deep_cowow, int, 0444);

MODUWE_PAWM_DESC(use_pfwipiwq, "Pfwip iwqs fow pagefwip compwetion (0 = disabwe, 1 = as fawwback, 2 = excwusive (defauwt))");
moduwe_pawam_named(use_pfwipiwq, wadeon_use_pfwipiwq, int, 0444);

MODUWE_PAWM_DESC(bapm, "BAPM suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(bapm, wadeon_bapm, int, 0444);

MODUWE_PAWM_DESC(backwight, "backwight suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(backwight, wadeon_backwight, int, 0444);

MODUWE_PAWM_DESC(auxch, "Use native auxch expewimentaw suppowt (1 = enabwe, 0 = disabwe, -1 = auto)");
moduwe_pawam_named(auxch, wadeon_auxch, int, 0444);

MODUWE_PAWM_DESC(uvd, "uvd enabwe/disabwe uvd suppowt (1 = enabwe, 0 = disabwe)");
moduwe_pawam_named(uvd, wadeon_uvd, int, 0444);

MODUWE_PAWM_DESC(vce, "vce enabwe/disabwe vce suppowt (1 = enabwe, 0 = disabwe)");
moduwe_pawam_named(vce, wadeon_vce, int, 0444);

int wadeon_si_suppowt = 1;
MODUWE_PAWM_DESC(si_suppowt, "SI suppowt (1 = enabwed (defauwt), 0 = disabwed)");
moduwe_pawam_named(si_suppowt, wadeon_si_suppowt, int, 0444);

int wadeon_cik_suppowt = 1;
MODUWE_PAWM_DESC(cik_suppowt, "CIK suppowt (1 = enabwed (defauwt), 0 = disabwed)");
moduwe_pawam_named(cik_suppowt, wadeon_cik_suppowt, int, 0444);

static stwuct pci_device_id pciidwist[] = {
	wadeon_PCI_IDS
};

MODUWE_DEVICE_TABWE(pci, pciidwist);

static const stwuct dwm_dwivew kms_dwivew;

static int wadeon_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	unsigned wong fwags = 0;
	stwuct dwm_device *dev;
	int wet;

	if (!ent)
		wetuwn -ENODEV; /* Avoid NUWW-ptw dewef in dwm_get_pci_dev */

	fwags = ent->dwivew_data;

	if (!wadeon_si_suppowt) {
		switch (fwags & WADEON_FAMIWY_MASK) {
		case CHIP_TAHITI:
		case CHIP_PITCAIWN:
		case CHIP_VEWDE:
		case CHIP_OWAND:
		case CHIP_HAINAN:
			dev_info(&pdev->dev,
				 "SI suppowt disabwed by moduwe pawam\n");
			wetuwn -ENODEV;
		}
	}
	if (!wadeon_cik_suppowt) {
		switch (fwags & WADEON_FAMIWY_MASK) {
		case CHIP_KAVEWI:
		case CHIP_BONAIWE:
		case CHIP_HAWAII:
		case CHIP_KABINI:
		case CHIP_MUWWINS:
			dev_info(&pdev->dev,
				 "CIK suppowt disabwed by moduwe pawam\n");
			wetuwn -ENODEV;
		}
	}

	if (vga_switchewoo_cwient_pwobe_defew(pdev))
		wetuwn -EPWOBE_DEFEW;

	/* Get wid of things wike offb */
	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &kms_dwivew);
	if (wet)
		wetuwn wet;

	dev = dwm_dev_awwoc(&kms_dwivew, &pdev->dev);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto eww_fwee;

	pci_set_dwvdata(pdev, dev);

	wet = dwm_dev_wegistew(dev, ent->dwivew_data);
	if (wet)
		goto eww_agp;

	wadeon_fbdev_setup(dev->dev_pwivate);

	wetuwn 0;

eww_agp:
	pci_disabwe_device(pdev);
eww_fwee:
	dwm_dev_put(dev);
	wetuwn wet;
}

static void
wadeon_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_put_dev(dev);
}

static void
wadeon_pci_shutdown(stwuct pci_dev *pdev)
{
	/* if we awe wunning in a VM, make suwe the device
	 * town down pwopewwy on weboot/shutdown
	 */
	if (wadeon_device_is_viwtuaw())
		wadeon_pci_wemove(pdev);

#if defined(CONFIG_PPC64) || defined(CONFIG_MACH_WOONGSON64)
	/*
	 * Some adaptews need to be suspended befowe a
	 * shutdown occuws in owdew to pwevent an ewwow
	 * duwing kexec, shutdown ow weboot.
	 * Make this powew and Woongson specific because
	 * it bweaks some othew boawds.
	 */
	wadeon_suspend_kms(pci_get_dwvdata(pdev), twue, twue, fawse);
#endif
}

static int wadeon_pmops_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn wadeon_suspend_kms(dwm_dev, twue, twue, fawse);
}

static int wadeon_pmops_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	/* GPU comes up enabwed by the bios on wesume */
	if (wadeon_is_px(dwm_dev)) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	wetuwn wadeon_wesume_kms(dwm_dev, twue, twue);
}

static int wadeon_pmops_fweeze(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn wadeon_suspend_kms(dwm_dev, fawse, twue, twue);
}

static int wadeon_pmops_thaw(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn wadeon_wesume_kms(dwm_dev, fawse, twue);
}

static int wadeon_pmops_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);

	if (!wadeon_is_px(dwm_dev)) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;
	dwm_kms_hewpew_poww_disabwe(dwm_dev);

	wadeon_suspend_kms(dwm_dev, fawse, fawse, fawse);
	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_ignowe_hotpwug(pdev);
	if (wadeon_is_atpx_hybwid())
		pci_set_powew_state(pdev, PCI_D3cowd);
	ewse if (!wadeon_has_atpx_dgpu_powew_cntw())
		pci_set_powew_state(pdev, PCI_D3hot);
	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_DYNAMIC_OFF;

	wetuwn 0;
}

static int wadeon_pmops_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	int wet;

	if (!wadeon_is_px(dwm_dev))
		wetuwn -EINVAW;

	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_CHANGING;

	if (wadeon_is_atpx_hybwid() ||
	    !wadeon_has_atpx_dgpu_powew_cntw())
		pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;
	pci_set_mastew(pdev);

	wet = wadeon_wesume_kms(dwm_dev, fawse, fawse);
	dwm_kms_hewpew_poww_enabwe(dwm_dev);
	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_ON;
	wetuwn 0;
}

static int wadeon_pmops_wuntime_idwe(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct dwm_cwtc *cwtc;

	if (!wadeon_is_px(dwm_dev)) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	wist_fow_each_entwy(cwtc, &dwm_dev->mode_config.cwtc_wist, head) {
		if (cwtc->enabwed) {
			DWM_DEBUG_DWIVEW("faiwing to powew off - cwtc active\n");
			wetuwn -EBUSY;
		}
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_autosuspend(dev);
	/* we don't want the main wpm_idwe to caww suspend - we want to autosuspend */
	wetuwn 1;
}

wong wadeon_dwm_ioctw(stwuct fiwe *fiwp,
		      unsigned int cmd, unsigned wong awg)
{
	stwuct dwm_fiwe *fiwe_pwiv = fiwp->pwivate_data;
	stwuct dwm_device *dev;
	wong wet;

	dev = fiwe_pwiv->minow->dev;
	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	wet = dwm_ioctw(fiwp, cmd, awg);

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static wong wadeon_kms_compat_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	unsigned int nw = DWM_IOCTW_NW(cmd);

	if (nw < DWM_COMMAND_BASE)
		wetuwn dwm_compat_ioctw(fiwp, cmd, awg);

	wetuwn wadeon_dwm_ioctw(fiwp, cmd, awg);
}
#endif

static const stwuct dev_pm_ops wadeon_pm_ops = {
	.suspend = wadeon_pmops_suspend,
	.wesume = wadeon_pmops_wesume,
	.fweeze = wadeon_pmops_fweeze,
	.thaw = wadeon_pmops_thaw,
	.powewoff = wadeon_pmops_fweeze,
	.westowe = wadeon_pmops_wesume,
	.wuntime_suspend = wadeon_pmops_wuntime_suspend,
	.wuntime_wesume = wadeon_pmops_wuntime_wesume,
	.wuntime_idwe = wadeon_pmops_wuntime_idwe,
};

static const stwuct fiwe_opewations wadeon_dwivew_kms_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease,
	.unwocked_ioctw = wadeon_dwm_ioctw,
	.mmap = dwm_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
#ifdef CONFIG_COMPAT
	.compat_ioctw = wadeon_kms_compat_ioctw,
#endif
};

static const stwuct dwm_ioctw_desc wadeon_ioctws_kms[] = {
	DWM_IOCTW_DEF_DWV(WADEON_CP_INIT, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_CP_STAWT, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_CP_STOP, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_CP_WESET, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_CP_IDWE, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_CP_WESUME, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_WESET, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_FUWWSCWEEN, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_SWAP, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_CWEAW, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_VEWTEX, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_INDICES, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_TEXTUWE, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_STIPPWE, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_INDIWECT, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_VEWTEX2, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_CMDBUF, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_GETPAWAM, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_FWIP, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_AWWOC, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_FWEE, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_INIT_HEAP, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(WADEON_IWQ_EMIT, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_IWQ_WAIT, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_SETPAWAM, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_SUWF_AWWOC, dwm_invawid_op, DWM_AUTH),
	DWM_IOCTW_DEF_DWV(WADEON_SUWF_FWEE, dwm_invawid_op, DWM_AUTH),
	/* KMS */
	DWM_IOCTW_DEF_DWV(WADEON_GEM_INFO, wadeon_gem_info_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_CWEATE, wadeon_gem_cweate_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_MMAP, wadeon_gem_mmap_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_SET_DOMAIN, wadeon_gem_set_domain_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_WAIT_IDWE, wadeon_gem_wait_idwe_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_CS, wadeon_cs_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_INFO, wadeon_info_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_SET_TIWING, wadeon_gem_set_tiwing_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_GET_TIWING, wadeon_gem_get_tiwing_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_BUSY, wadeon_gem_busy_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_VA, wadeon_gem_va_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_OP, wadeon_gem_op_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(WADEON_GEM_USEWPTW, wadeon_gem_usewptw_ioctw, DWM_AUTH|DWM_WENDEW_AWWOW),
};

static const stwuct dwm_dwivew kms_dwivew = {
	.dwivew_featuwes =
	    DWIVEW_GEM | DWIVEW_WENDEW | DWIVEW_MODESET,
	.woad = wadeon_dwivew_woad_kms,
	.open = wadeon_dwivew_open_kms,
	.postcwose = wadeon_dwivew_postcwose_kms,
	.unwoad = wadeon_dwivew_unwoad_kms,
	.ioctws = wadeon_ioctws_kms,
	.num_ioctws = AWWAY_SIZE(wadeon_ioctws_kms),
	.dumb_cweate = wadeon_mode_dumb_cweate,
	.dumb_map_offset = wadeon_mode_dumb_mmap,
	.fops = &wadeon_dwivew_kms_fops,

	.gem_pwime_impowt_sg_tabwe = wadeon_gem_pwime_impowt_sg_tabwe,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = KMS_DWIVEW_MAJOW,
	.minow = KMS_DWIVEW_MINOW,
	.patchwevew = KMS_DWIVEW_PATCHWEVEW,
};

static stwuct pci_dwivew wadeon_kms_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = wadeon_pci_pwobe,
	.wemove = wadeon_pci_wemove,
	.shutdown = wadeon_pci_shutdown,
	.dwivew.pm = &wadeon_pm_ops,
};

static int __init wadeon_moduwe_init(void)
{
	if (dwm_fiwmwawe_dwivews_onwy() && wadeon_modeset == -1)
		wadeon_modeset = 0;

	if (wadeon_modeset == 0)
		wetuwn -EINVAW;

	DWM_INFO("wadeon kewnew modesetting enabwed.\n");
	wadeon_wegistew_atpx_handwew();

	wetuwn pci_wegistew_dwivew(&wadeon_kms_pci_dwivew);
}

static void __exit wadeon_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&wadeon_kms_pci_dwivew);
	wadeon_unwegistew_atpx_handwew();
	mmu_notifiew_synchwonize();
}

moduwe_init(wadeon_moduwe_init);
moduwe_exit(wadeon_moduwe_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
