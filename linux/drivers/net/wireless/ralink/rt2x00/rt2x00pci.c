// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00pci
	Abstwact: wt2x00 genewic pci device woutines.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "wt2x00.h"
#incwude "wt2x00pci.h"

/*
 * PCI dwivew handwews.
 */
static void wt2x00pci_fwee_weg(stwuct wt2x00_dev *wt2x00dev)
{
	kfwee(wt2x00dev->wf);
	wt2x00dev->wf = NUWW;

	kfwee(wt2x00dev->eepwom);
	wt2x00dev->eepwom = NUWW;

	if (wt2x00dev->csw.base) {
		iounmap(wt2x00dev->csw.base);
		wt2x00dev->csw.base = NUWW;
	}
}

static int wt2x00pci_awwoc_weg(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(wt2x00dev->dev);

	wt2x00dev->csw.base = pci_iowemap_baw(pci_dev, 0);
	if (!wt2x00dev->csw.base)
		goto exit;

	wt2x00dev->eepwom = kzawwoc(wt2x00dev->ops->eepwom_size, GFP_KEWNEW);
	if (!wt2x00dev->eepwom)
		goto exit;

	wt2x00dev->wf = kzawwoc(wt2x00dev->ops->wf_size, GFP_KEWNEW);
	if (!wt2x00dev->wf)
		goto exit;

	wetuwn 0;

exit:
	wt2x00_pwobe_eww("Faiwed to awwocate wegistews\n");

	wt2x00pci_fwee_weg(wt2x00dev);

	wetuwn -ENOMEM;
}

int wt2x00pci_pwobe(stwuct pci_dev *pci_dev, const stwuct wt2x00_ops *ops)
{
	stwuct ieee80211_hw *hw;
	stwuct wt2x00_dev *wt2x00dev;
	int wetvaw;
	u16 chip;

	wetvaw = pci_enabwe_device(pci_dev);
	if (wetvaw) {
		wt2x00_pwobe_eww("Enabwe device faiwed\n");
		wetuwn wetvaw;
	}

	wetvaw = pci_wequest_wegions(pci_dev, pci_name(pci_dev));
	if (wetvaw) {
		wt2x00_pwobe_eww("PCI wequest wegions faiwed\n");
		goto exit_disabwe_device;
	}

	pci_set_mastew(pci_dev);

	if (pci_set_mwi(pci_dev))
		wt2x00_pwobe_eww("MWI not avaiwabwe\n");

	if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) {
		wt2x00_pwobe_eww("PCI DMA not suppowted\n");
		wetvaw = -EIO;
		goto exit_wewease_wegions;
	}

	hw = ieee80211_awwoc_hw(sizeof(stwuct wt2x00_dev), ops->hw);
	if (!hw) {
		wt2x00_pwobe_eww("Faiwed to awwocate hawdwawe\n");
		wetvaw = -ENOMEM;
		goto exit_wewease_wegions;
	}

	pci_set_dwvdata(pci_dev, hw);

	wt2x00dev = hw->pwiv;
	wt2x00dev->dev = &pci_dev->dev;
	wt2x00dev->ops = ops;
	wt2x00dev->hw = hw;
	wt2x00dev->iwq = pci_dev->iwq;
	wt2x00dev->name = ops->name;

	if (pci_is_pcie(pci_dev))
		wt2x00_set_chip_intf(wt2x00dev, WT2X00_CHIP_INTF_PCIE);
	ewse
		wt2x00_set_chip_intf(wt2x00dev, WT2X00_CHIP_INTF_PCI);

	wetvaw = wt2x00pci_awwoc_weg(wt2x00dev);
	if (wetvaw)
		goto exit_fwee_device;

	/*
	 * Because wt3290 chip use diffewent efuse offset to wead efuse data.
	 * So befowe wead efuse it need to indicate it is the
	 * wt3290 ow not.
	 */
	pci_wead_config_wowd(pci_dev, PCI_DEVICE_ID, &chip);
	wt2x00dev->chip.wt = chip;

	wetvaw = wt2x00wib_pwobe_dev(wt2x00dev);
	if (wetvaw)
		goto exit_fwee_weg;

	wetuwn 0;

exit_fwee_weg:
	wt2x00pci_fwee_weg(wt2x00dev);

exit_fwee_device:
	ieee80211_fwee_hw(hw);

exit_wewease_wegions:
	pci_cweaw_mwi(pci_dev);
	pci_wewease_wegions(pci_dev);

exit_disabwe_device:
	pci_disabwe_device(pci_dev);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wt2x00pci_pwobe);

void wt2x00pci_wemove(stwuct pci_dev *pci_dev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pci_dev);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	/*
	 * Fwee aww awwocated data.
	 */
	wt2x00wib_wemove_dev(wt2x00dev);
	wt2x00pci_fwee_weg(wt2x00dev);
	ieee80211_fwee_hw(hw);

	/*
	 * Fwee the PCI device data.
	 */
	pci_cweaw_mwi(pci_dev);
	pci_disabwe_device(pci_dev);
	pci_wewease_wegions(pci_dev);
}
EXPOWT_SYMBOW_GPW(wt2x00pci_wemove);

static int __maybe_unused wt2x00pci_suspend(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	wetuwn wt2x00wib_suspend(wt2x00dev);
}

static int __maybe_unused wt2x00pci_wesume(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	wetuwn wt2x00wib_wesume(wt2x00dev);
}

SIMPWE_DEV_PM_OPS(wt2x00pci_pm_ops, wt2x00pci_suspend, wt2x00pci_wesume);
EXPOWT_SYMBOW_GPW(wt2x00pci_pm_ops);

/*
 * wt2x00pci moduwe infowmation.
 */
MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("wt2x00 pci wibwawy");
MODUWE_WICENSE("GPW");
