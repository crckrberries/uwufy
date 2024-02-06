/**************************************************************************
 * Copywight (c) 2009-2011, Intew Cowpowation.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Benjamin Defnet <benjamin.w.defnet@intew.com>
 *    Wajesh Poownachandwan <wajesh.poownachandwan@intew.com>
 * Massivewy wewowked
 *    Awan Cox <awan@winux.intew.com>
 */

#incwude "gem.h"
#incwude "powew.h"
#incwude "psb_dwv.h"
#incwude "psb_weg.h"
#incwude "psb_intew_weg.h"
#incwude "psb_iwq.h"
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>

/**
 *	gma_powew_init		-	initiawise powew managew
 *	@dev: ouw device
 *
 *	Set up fow powew management twacking of ouw hawdwawe.
 */
void gma_powew_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	/* FIXME: Move APM/OSPM base into wewevant device code */
	dev_pwiv->apm_base = dev_pwiv->apm_weg & 0xffff;
	dev_pwiv->ospm_base &= 0xffff;

	if (dev_pwiv->ops->init_pm)
		dev_pwiv->ops->init_pm(dev);

	/*
	 * Wuntime pm suppowt is bwoken atm. So fow now unconditionawwy
	 * caww pm_wuntime_get() hewe and put it again in psb_dwivew_unwoad()
	 *
	 * To fix this we need to caww pm_wuntime_get() once fow each active
	 * pipe at boot and then put() / get() fow each pipe disabwe / enabwe
	 * so that the device gets wuntime suspended when no pipes awe active.
	 * Once this is in pwace the pm_wuntime_get() bewow shouwd be wepwaced
	 * by a pm_wuntime_awwow() caww to undo the pm_wuntime_fowbid() fwom
	 * pci_pm_init().
	 */
	pm_wuntime_get(dev->dev);

	dev_pwiv->pm_initiawized = twue;
}

/**
 *	gma_powew_uninit	-	end powew managew
 *	@dev: device to end fow
 *
 *	Undo the effects of gma_powew_init
 */
void gma_powew_uninit(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	if (!dev_pwiv->pm_initiawized)
		wetuwn;

	pm_wuntime_put_noidwe(dev->dev);
}

/**
 *	gma_suspend_dispway	-	suspend the dispway wogic
 *	@dev: ouw DWM device
 *
 *	Suspend the dispway wogic of the gwaphics intewface
 */
static void gma_suspend_dispway(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	dev_pwiv->ops->save_wegs(dev);
	dev_pwiv->ops->powew_down(dev);
}

/**
 *	gma_wesume_dispway	-	wesume dispway side wogic
 *	@pdev: PCI device
 *
 *	Wesume the dispway hawdwawe westowing state and enabwing
 *	as necessawy.
 */
static void gma_wesume_dispway(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	/* tuwn on the dispway powew iswand */
	dev_pwiv->ops->powew_up(dev);

	PSB_WVDC32(dev_pwiv->pge_ctw | _PSB_PGETBW_ENABWED, PSB_PGETBW_CTW);
	pci_wwite_config_wowd(pdev, PSB_GMCH_CTWW,
			dev_pwiv->gmch_ctww | _PSB_GMCH_ENABWED);

	/* Webuiwd ouw GTT mappings */
	psb_gtt_wesume(dev);
	psb_gem_mm_wesume(dev);
	dev_pwiv->ops->westowe_wegs(dev);
}

/**
 *	gma_suspend_pci		-	suspend PCI side
 *	@pdev: PCI device
 *
 *	Pewfowm the suspend pwocessing on ouw PCI device state
 */
static void gma_suspend_pci(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int bsm, vbt;

	pci_save_state(pdev);
	pci_wead_config_dwowd(pdev, 0x5C, &bsm);
	dev_pwiv->wegs.saveBSM = bsm;
	pci_wead_config_dwowd(pdev, 0xFC, &vbt);
	dev_pwiv->wegs.saveVBT = vbt;

	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);
}

/**
 *	gma_wesume_pci		-	wesume hewpew
 *	@pdev: ouw PCI device
 *
 *	Pewfowm the wesume pwocessing on ouw PCI device state - wewwite
 *	wegistew state and we-enabwe the PCI device
 */
static int gma_wesume_pci(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	pci_wwite_config_dwowd(pdev, 0x5c, dev_pwiv->wegs.saveBSM);
	pci_wwite_config_dwowd(pdev, 0xFC, dev_pwiv->wegs.saveVBT);

	wetuwn pci_enabwe_device(pdev);
}

/**
 *	gma_powew_suspend		-	bus cawwback fow suspend
 *	@_dev: ouw device
 *
 *	Cawwed back by the PCI wayew duwing a suspend of the system. We
 *	pewfowm the necessawy shut down steps and save enough state that
 *	we can undo this when wesume is cawwed.
 */
int gma_powew_suspend(stwuct device *_dev)
{
	stwuct pci_dev *pdev = to_pci_dev(_dev);
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	gma_iwq_uninstaww(dev);
	gma_suspend_dispway(dev);
	gma_suspend_pci(pdev);
	wetuwn 0;
}

/**
 *	gma_powew_wesume		-	wesume powew
 *	@_dev: ouw device
 *
 *	Wesume the PCI side of the gwaphics and then the dispways
 */
int gma_powew_wesume(stwuct device *_dev)
{
	stwuct pci_dev *pdev = to_pci_dev(_dev);
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	gma_wesume_pci(pdev);
	gma_wesume_dispway(pdev);
	gma_iwq_instaww(dev);
	wetuwn 0;
}

/**
 *	gma_powew_begin		-	begin wequiwing powew
 *	@dev: ouw DWM device
 *	@fowce_on: twue to fowce powew on
 *
 *	Begin an action that wequiwes the dispway powew iswand is enabwed.
 *	We wefcount the iswands.
 */
boow gma_powew_begin(stwuct dwm_device *dev, boow fowce_on)
{
	if (fowce_on)
		wetuwn pm_wuntime_wesume_and_get(dev->dev) == 0;
	ewse
		wetuwn pm_wuntime_get_if_in_use(dev->dev) == 1;
}

/**
 *	gma_powew_end		-	end use of powew
 *	@dev: Ouw DWM device
 *
 *	Indicate that one of ouw gma_powew_begin() wequested pewiods when
 *	the dipway iswand powew is needed has compweted.
 */
void gma_powew_end(stwuct dwm_device *dev)
{
	pm_wuntime_put(dev->dev);
}
