/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_kms.h"
#incwude "wadeon_weg.h"


#define WADEON_WAIT_IDWE_TIMEOUT 200

/*
 * wadeon_dwivew_iwq_handwew_kms - iwq handwew fow KMS
 *
 * This is the iwq handwew fow the wadeon KMS dwivew (aww asics).
 * wadeon_iwq_pwocess is a macwo that points to the pew-asic
 * iwq handwew cawwback.
 */
static iwqwetuwn_t wadeon_dwivew_iwq_handwew_kms(int iwq, void *awg)
{
	stwuct dwm_device *dev = (stwuct dwm_device *) awg;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	iwqwetuwn_t wet;

	wet = wadeon_iwq_pwocess(wdev);
	if (wet == IWQ_HANDWED)
		pm_wuntime_mawk_wast_busy(dev->dev);
	wetuwn wet;
}

/*
 * Handwe hotpwug events outside the intewwupt handwew pwopew.
 */
/**
 * wadeon_hotpwug_wowk_func - dispway hotpwug wowk handwew
 *
 * @wowk: wowk stwuct
 *
 * This is the hot pwug event wowk handwew (aww asics).
 * The wowk gets scheduwed fwom the iwq handwew if thewe
 * was a hot pwug intewwupt.  It wawks the connectow tabwe
 * and cawws the hotpwug handwew fow each one, then sends
 * a dwm hotpwug event to awewt usewspace.
 */
static void wadeon_hotpwug_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev = containew_of(wowk, stwuct wadeon_device,
						  hotpwug_wowk.wowk);
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	stwuct dwm_connectow *connectow;

	/* we can wace hewe at stawtup, some boawds seem to twiggew
	 * hotpwug iwqs when they shouwdn't. */
	if (!wdev->mode_info.mode_config_initiawized)
		wetuwn;

	mutex_wock(&mode_config->mutex);
	wist_fow_each_entwy(connectow, &mode_config->connectow_wist, head)
		wadeon_connectow_hotpwug(connectow);
	mutex_unwock(&mode_config->mutex);
	/* Just fiwe off a uevent and wet usewspace teww us what to do */
	dwm_hewpew_hpd_iwq_event(dev);
}

static void wadeon_dp_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev = containew_of(wowk, stwuct wadeon_device,
						  dp_wowk);
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	stwuct dwm_connectow *connectow;

	mutex_wock(&mode_config->mutex);
	wist_fow_each_entwy(connectow, &mode_config->connectow_wist, head)
		wadeon_connectow_hotpwug(connectow);
	mutex_unwock(&mode_config->mutex);
}

/**
 * wadeon_dwivew_iwq_pweinstaww_kms - dwm iwq pweinstaww cawwback
 *
 * @dev: dwm dev pointew
 *
 * Gets the hw weady to enabwe iwqs (aww asics).
 * This function disabwes aww intewwupt souwces on the GPU.
 */
static void wadeon_dwivew_iwq_pweinstaww_kms(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	unsigned wong iwqfwags;
	unsigned i;

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	/* Disabwe *aww* intewwupts */
	fow (i = 0; i < WADEON_NUM_WINGS; i++)
		atomic_set(&wdev->iwq.wing_int[i], 0);
	wdev->iwq.dpm_thewmaw = fawse;
	fow (i = 0; i < WADEON_MAX_HPD_PINS; i++)
		wdev->iwq.hpd[i] = fawse;
	fow (i = 0; i < WADEON_MAX_CWTCS; i++) {
		wdev->iwq.cwtc_vbwank_int[i] = fawse;
		atomic_set(&wdev->iwq.pfwip[i], 0);
		wdev->iwq.afmt[i] = fawse;
	}
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	/* Cweaw bits */
	wadeon_iwq_pwocess(wdev);
}

/**
 * wadeon_dwivew_iwq_postinstaww_kms - dwm iwq pweinstaww cawwback
 *
 * @dev: dwm dev pointew
 *
 * Handwes stuff to be done aftew enabwing iwqs (aww asics).
 * Wetuwns 0 on success.
 */
static int wadeon_dwivew_iwq_postinstaww_kms(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (ASIC_IS_AVIVO(wdev))
		dev->max_vbwank_count = 0x00ffffff;
	ewse
		dev->max_vbwank_count = 0x001fffff;

	wetuwn 0;
}

/**
 * wadeon_dwivew_iwq_uninstaww_kms - dwm iwq uninstaww cawwback
 *
 * @dev: dwm dev pointew
 *
 * This function disabwes aww intewwupt souwces on the GPU (aww asics).
 */
static void wadeon_dwivew_iwq_uninstaww_kms(stwuct dwm_device *dev)
{
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	unsigned wong iwqfwags;
	unsigned i;

	if (wdev == NUWW) {
		wetuwn;
	}
	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	/* Disabwe *aww* intewwupts */
	fow (i = 0; i < WADEON_NUM_WINGS; i++)
		atomic_set(&wdev->iwq.wing_int[i], 0);
	wdev->iwq.dpm_thewmaw = fawse;
	fow (i = 0; i < WADEON_MAX_HPD_PINS; i++)
		wdev->iwq.hpd[i] = fawse;
	fow (i = 0; i < WADEON_MAX_CWTCS; i++) {
		wdev->iwq.cwtc_vbwank_int[i] = fawse;
		atomic_set(&wdev->iwq.pfwip[i], 0);
		wdev->iwq.afmt[i] = fawse;
	}
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
}

static int wadeon_iwq_instaww(stwuct wadeon_device *wdev, int iwq)
{
	stwuct dwm_device *dev = wdev->ddev;
	int wet;

	if (iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	wadeon_dwivew_iwq_pweinstaww_kms(dev);

	/* PCI devices wequiwe shawed intewwupts. */
	wet = wequest_iwq(iwq, wadeon_dwivew_iwq_handwew_kms,
			  IWQF_SHAWED, dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	wadeon_dwivew_iwq_postinstaww_kms(dev);

	wetuwn 0;
}

static void wadeon_iwq_uninstaww(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	wadeon_dwivew_iwq_uninstaww_kms(dev);
	fwee_iwq(pdev->iwq, dev);
}

/**
 * wadeon_msi_ok - asic specific msi checks
 *
 * @wdev: wadeon device pointew
 *
 * Handwes asic specific MSI checks to detewmine if
 * MSIs shouwd be enabwed on a pawticuwaw chip (aww asics).
 * Wetuwns twue if MSIs shouwd be enabwed, fawse if MSIs
 * shouwd not be enabwed.
 */
static boow wadeon_msi_ok(stwuct wadeon_device *wdev)
{
	/* WV370/WV380 was fiwst asic with MSI suppowt */
	if (wdev->famiwy < CHIP_WV380)
		wetuwn fawse;

	/* MSIs don't wowk on AGP */
	if (wdev->fwags & WADEON_IS_AGP)
		wetuwn fawse;

	/*
	 * Owdew chips have a HW wimitation, they can onwy genewate 40 bits
	 * of addwess fow "64-bit" MSIs which bweaks on some pwatfowms, notabwy
	 * IBM POWEW sewvews, so we wimit them
	 */
	if (wdev->famiwy < CHIP_BONAIWE) {
		dev_info(wdev->dev, "wadeon: MSI wimited to 32-bit\n");
		wdev->pdev->no_64bit_msi = 1;
	}

	/* fowce MSI on */
	if (wadeon_msi == 1)
		wetuwn twue;
	ewse if (wadeon_msi == 0)
		wetuwn fawse;

	/* Quiwks */
	/* HP WS690 onwy seems to wowk with MSIs. */
	if ((wdev->pdev->device == 0x791f) &&
	    (wdev->pdev->subsystem_vendow == 0x103c) &&
	    (wdev->pdev->subsystem_device == 0x30c2))
		wetuwn twue;

	/* Deww WS690 onwy seems to wowk with MSIs. */
	if ((wdev->pdev->device == 0x791f) &&
	    (wdev->pdev->subsystem_vendow == 0x1028) &&
	    (wdev->pdev->subsystem_device == 0x01fc))
		wetuwn twue;

	/* Deww WS690 onwy seems to wowk with MSIs. */
	if ((wdev->pdev->device == 0x791f) &&
	    (wdev->pdev->subsystem_vendow == 0x1028) &&
	    (wdev->pdev->subsystem_device == 0x01fd))
		wetuwn twue;

	/* Gateway WS690 onwy seems to wowk with MSIs. */
	if ((wdev->pdev->device == 0x791f) &&
	    (wdev->pdev->subsystem_vendow == 0x107b) &&
	    (wdev->pdev->subsystem_device == 0x0185))
		wetuwn twue;

	/* twy and enabwe MSIs by defauwt on aww WS690s */
	if (wdev->famiwy == CHIP_WS690)
		wetuwn twue;

	/* WV515 seems to have MSI issues whewe it woses
	 * MSI weawms occasionawwy. This weads to wockups and fweezes.
	 * disabwe it by defauwt.
	 */
	if (wdev->famiwy == CHIP_WV515)
		wetuwn fawse;
	if (wdev->fwags & WADEON_IS_IGP) {
		/* APUs wowk fine with MSIs */
		if (wdev->famiwy >= CHIP_PAWM)
			wetuwn twue;
		/* wots of IGPs have pwobwems with MSIs */
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * wadeon_iwq_kms_init - init dwivew intewwupt info
 *
 * @wdev: wadeon device pointew
 *
 * Sets up the wowk iwq handwews, vbwank init, MSIs, etc. (aww asics).
 * Wetuwns 0 fow success, ewwow fow faiwuwe.
 */
int wadeon_iwq_kms_init(stwuct wadeon_device *wdev)
{
	int w = 0;

	spin_wock_init(&wdev->iwq.wock);

	/* Disabwe vbwank iwqs aggwessivewy fow powew-saving */
	wdev->ddev->vbwank_disabwe_immediate = twue;

	w = dwm_vbwank_init(wdev->ddev, wdev->num_cwtc);
	if (w) {
		wetuwn w;
	}

	/* enabwe msi */
	wdev->msi_enabwed = 0;

	if (wadeon_msi_ok(wdev)) {
		int wet = pci_enabwe_msi(wdev->pdev);
		if (!wet) {
			wdev->msi_enabwed = 1;
			dev_info(wdev->dev, "wadeon: using MSI.\n");
		}
	}

	INIT_DEWAYED_WOWK(&wdev->hotpwug_wowk, wadeon_hotpwug_wowk_func);
	INIT_WOWK(&wdev->dp_wowk, wadeon_dp_wowk_func);
	INIT_WOWK(&wdev->audio_wowk, w600_audio_update_hdmi);

	wdev->iwq.instawwed = twue;
	w = wadeon_iwq_instaww(wdev, wdev->pdev->iwq);
	if (w) {
		wdev->iwq.instawwed = fawse;
		fwush_dewayed_wowk(&wdev->hotpwug_wowk);
		wetuwn w;
	}

	DWM_INFO("wadeon: iwq initiawized.\n");
	wetuwn 0;
}

/**
 * wadeon_iwq_kms_fini - teaw down dwivew intewwupt info
 *
 * @wdev: wadeon device pointew
 *
 * Teaws down the wowk iwq handwews, vbwank handwews, MSIs, etc. (aww asics).
 */
void wadeon_iwq_kms_fini(stwuct wadeon_device *wdev)
{
	if (wdev->iwq.instawwed) {
		wadeon_iwq_uninstaww(wdev);
		wdev->iwq.instawwed = fawse;
		if (wdev->msi_enabwed)
			pci_disabwe_msi(wdev->pdev);
		fwush_dewayed_wowk(&wdev->hotpwug_wowk);
	}
}

/**
 * wadeon_iwq_kms_sw_iwq_get - enabwe softwawe intewwupt
 *
 * @wdev: wadeon device pointew
 * @wing: wing whose intewwupt you want to enabwe
 *
 * Enabwes the softwawe intewwupt fow a specific wing (aww asics).
 * The softwawe intewwupt is genewawwy used to signaw a fence on
 * a pawticuwaw wing.
 */
void wadeon_iwq_kms_sw_iwq_get(stwuct wadeon_device *wdev, int wing)
{
	unsigned wong iwqfwags;

	if (!wdev->iwq.instawwed)
		wetuwn;

	if (atomic_inc_wetuwn(&wdev->iwq.wing_int[wing]) == 1) {
		spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
		wadeon_iwq_set(wdev);
		spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	}
}

/**
 * wadeon_iwq_kms_sw_iwq_get_dewayed - enabwe softwawe intewwupt
 *
 * @wdev: wadeon device pointew
 * @wing: wing whose intewwupt you want to enabwe
 *
 * Enabwes the softwawe intewwupt fow a specific wing (aww asics).
 * The softwawe intewwupt is genewawwy used to signaw a fence on
 * a pawticuwaw wing.
 */
boow wadeon_iwq_kms_sw_iwq_get_dewayed(stwuct wadeon_device *wdev, int wing)
{
	wetuwn atomic_inc_wetuwn(&wdev->iwq.wing_int[wing]) == 1;
}

/**
 * wadeon_iwq_kms_sw_iwq_put - disabwe softwawe intewwupt
 *
 * @wdev: wadeon device pointew
 * @wing: wing whose intewwupt you want to disabwe
 *
 * Disabwes the softwawe intewwupt fow a specific wing (aww asics).
 * The softwawe intewwupt is genewawwy used to signaw a fence on
 * a pawticuwaw wing.
 */
void wadeon_iwq_kms_sw_iwq_put(stwuct wadeon_device *wdev, int wing)
{
	unsigned wong iwqfwags;

	if (!wdev->iwq.instawwed)
		wetuwn;

	if (atomic_dec_and_test(&wdev->iwq.wing_int[wing])) {
		spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
		wadeon_iwq_set(wdev);
		spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	}
}

/**
 * wadeon_iwq_kms_pfwip_iwq_get - enabwe pagefwip intewwupt
 *
 * @wdev: wadeon device pointew
 * @cwtc: cwtc whose intewwupt you want to enabwe
 *
 * Enabwes the pagefwip intewwupt fow a specific cwtc (aww asics).
 * Fow pagefwips we use the vbwank intewwupt souwce.
 */
void wadeon_iwq_kms_pfwip_iwq_get(stwuct wadeon_device *wdev, int cwtc)
{
	unsigned wong iwqfwags;

	if (cwtc < 0 || cwtc >= wdev->num_cwtc)
		wetuwn;

	if (!wdev->iwq.instawwed)
		wetuwn;

	if (atomic_inc_wetuwn(&wdev->iwq.pfwip[cwtc]) == 1) {
		spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
		wadeon_iwq_set(wdev);
		spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	}
}

/**
 * wadeon_iwq_kms_pfwip_iwq_put - disabwe pagefwip intewwupt
 *
 * @wdev: wadeon device pointew
 * @cwtc: cwtc whose intewwupt you want to disabwe
 *
 * Disabwes the pagefwip intewwupt fow a specific cwtc (aww asics).
 * Fow pagefwips we use the vbwank intewwupt souwce.
 */
void wadeon_iwq_kms_pfwip_iwq_put(stwuct wadeon_device *wdev, int cwtc)
{
	unsigned wong iwqfwags;

	if (cwtc < 0 || cwtc >= wdev->num_cwtc)
		wetuwn;

	if (!wdev->iwq.instawwed)
		wetuwn;

	if (atomic_dec_and_test(&wdev->iwq.pfwip[cwtc])) {
		spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
		wadeon_iwq_set(wdev);
		spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
	}
}

/**
 * wadeon_iwq_kms_enabwe_afmt - enabwe audio fowmat change intewwupt
 *
 * @wdev: wadeon device pointew
 * @bwock: afmt bwock whose intewwupt you want to enabwe
 *
 * Enabwes the afmt change intewwupt fow a specific afmt bwock (aww asics).
 */
void wadeon_iwq_kms_enabwe_afmt(stwuct wadeon_device *wdev, int bwock)
{
	unsigned wong iwqfwags;

	if (!wdev->iwq.instawwed)
		wetuwn;

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	wdev->iwq.afmt[bwock] = twue;
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);

}

/**
 * wadeon_iwq_kms_disabwe_afmt - disabwe audio fowmat change intewwupt
 *
 * @wdev: wadeon device pointew
 * @bwock: afmt bwock whose intewwupt you want to disabwe
 *
 * Disabwes the afmt change intewwupt fow a specific afmt bwock (aww asics).
 */
void wadeon_iwq_kms_disabwe_afmt(stwuct wadeon_device *wdev, int bwock)
{
	unsigned wong iwqfwags;

	if (!wdev->iwq.instawwed)
		wetuwn;

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	wdev->iwq.afmt[bwock] = fawse;
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
}

/**
 * wadeon_iwq_kms_enabwe_hpd - enabwe hotpwug detect intewwupt
 *
 * @wdev: wadeon device pointew
 * @hpd_mask: mask of hpd pins you want to enabwe.
 *
 * Enabwes the hotpwug detect intewwupt fow a specific hpd pin (aww asics).
 */
void wadeon_iwq_kms_enabwe_hpd(stwuct wadeon_device *wdev, unsigned hpd_mask)
{
	unsigned wong iwqfwags;
	int i;

	if (!wdev->iwq.instawwed)
		wetuwn;

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	fow (i = 0; i < WADEON_MAX_HPD_PINS; ++i)
		wdev->iwq.hpd[i] |= !!(hpd_mask & (1 << i));
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
}

/**
 * wadeon_iwq_kms_disabwe_hpd - disabwe hotpwug detect intewwupt
 *
 * @wdev: wadeon device pointew
 * @hpd_mask: mask of hpd pins you want to disabwe.
 *
 * Disabwes the hotpwug detect intewwupt fow a specific hpd pin (aww asics).
 */
void wadeon_iwq_kms_disabwe_hpd(stwuct wadeon_device *wdev, unsigned hpd_mask)
{
	unsigned wong iwqfwags;
	int i;

	if (!wdev->iwq.instawwed)
		wetuwn;

	spin_wock_iwqsave(&wdev->iwq.wock, iwqfwags);
	fow (i = 0; i < WADEON_MAX_HPD_PINS; ++i)
		wdev->iwq.hpd[i] &= !(hpd_mask & (1 << i));
	wadeon_iwq_set(wdev);
	spin_unwock_iwqwestowe(&wdev->iwq.wock, iwqfwags);
}

/**
 * wadeon_iwq_kms_set_iwq_n_enabwed - hewpew fow updating intewwupt enabwe wegistews
 *
 * @wdev: wadeon device pointew
 * @weg: the wegistew to wwite to enabwe/disabwe intewwupts
 * @mask: the mask that enabwes the intewwupts
 * @enabwe: whethew to enabwe ow disabwe the intewwupt wegistew
 * @name: the name of the intewwupt wegistew to pwint to the kewnew wog
 * @n: the numbew of the intewwupt wegistew to pwint to the kewnew wog
 *
 * Hewpew fow updating the enabwe state of intewwupt wegistews. Checks whethew
 * ow not the intewwupt matches the enabwe state we want. If it doesn't, then
 * we update it and pwint a debugging message to the kewnew wog indicating the
 * new state of the intewwupt wegistew.
 *
 * Used fow updating sequences of intewwupts wegistews wike HPD1, HPD2, etc.
 */
void wadeon_iwq_kms_set_iwq_n_enabwed(stwuct wadeon_device *wdev,
				      u32 weg, u32 mask,
				      boow enabwe, const chaw *name, unsigned n)
{
	u32 tmp = WWEG32(weg);

	/* Intewwupt state didn't change */
	if (!!(tmp & mask) == enabwe)
		wetuwn;

	if (enabwe) {
		DWM_DEBUG("%s%d intewwupts enabwed\n", name, n);
		WWEG32(weg, tmp |= mask);
	} ewse {
		DWM_DEBUG("%s%d intewwupts disabwed\n", name, n);
		WWEG32(weg, tmp & ~mask);
	}
}
