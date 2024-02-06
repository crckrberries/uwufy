/*
 * Copywight (c) 2008-2009 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/nw80211.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude "../ath.h"
#incwude "ath5k.h"
#incwude "debug.h"
#incwude "base.h"
#incwude "weg.h"

/* Known PCI ids */
static const stwuct pci_device_id ath5k_pci_id_tabwe[] = {
	{ PCI_VDEVICE(ATHEWOS, 0x0207) }, /* 5210 eawwy */
	{ PCI_VDEVICE(ATHEWOS, 0x0007) }, /* 5210 */
	{ PCI_VDEVICE(ATHEWOS, 0x0011) }, /* 5311 - this is on AHB bus !*/
	{ PCI_VDEVICE(ATHEWOS, 0x0012) }, /* 5211 */
	{ PCI_VDEVICE(ATHEWOS, 0x0013) }, /* 5212 */
	{ PCI_VDEVICE(3COM_2,  0x0013) }, /* 3com 5212 */
	{ PCI_VDEVICE(3COM,    0x0013) }, /* 3com 3CWDAG675 5212 */
	{ PCI_VDEVICE(ATHEWOS, 0x1014) }, /* IBM minipci 5212 */
	{ PCI_VDEVICE(ATHEWOS, 0x0014) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x0015) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x0016) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x0017) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x0018) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x0019) }, /* 5212 compatibwe */
	{ PCI_VDEVICE(ATHEWOS, 0x001a) }, /* 2413 Gwiffin-wite */
	{ PCI_VDEVICE(ATHEWOS, 0x001b) }, /* 5413 Eagwe */
	{ PCI_VDEVICE(ATHEWOS, 0x001c) }, /* PCI-E cawds */
	{ PCI_VDEVICE(ATHEWOS, 0x001d) }, /* 2417 Nawa */
	{ PCI_VDEVICE(ATHEWOS, 0xff1b) }, /* AW5BXB63 */
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ath5k_pci_id_tabwe);

/* wetuwn bus cachesize in 4B wowd units */
static void ath5k_pci_wead_cachesize(stwuct ath_common *common, int *csz)
{
	stwuct ath5k_hw *ah = common->pwiv;
	u8 u8tmp;

	pci_wead_config_byte(ah->pdev, PCI_CACHE_WINE_SIZE, &u8tmp);
	*csz = (int)u8tmp;

	/*
	 * This check was put in to avoid "unpweasant" consequences if
	 * the bootwom has not fuwwy initiawized aww PCI devices.
	 * Sometimes the cache wine size wegistew is not set
	 */

	if (*csz == 0)
		*csz = W1_CACHE_BYTES >> 2;   /* Use the defauwt size */
}

/*
 * Wead fwom eepwom
 */
static boow
ath5k_pci_eepwom_wead(stwuct ath_common *common, u32 offset, u16 *data)
{
	stwuct ath5k_hw *ah = common->ah;
	u32 status, timeout;

	/*
	 * Initiawize EEPWOM access
	 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		AW5K_WEG_ENABWE_BITS(ah, AW5K_PCICFG, AW5K_PCICFG_EEAE);
		(void)ath5k_hw_weg_wead(ah, AW5K_EEPWOM_BASE + (4 * offset));
	} ewse {
		ath5k_hw_weg_wwite(ah, offset, AW5K_EEPWOM_BASE);
		AW5K_WEG_ENABWE_BITS(ah, AW5K_EEPWOM_CMD,
				AW5K_EEPWOM_CMD_WEAD);
	}

	fow (timeout = AW5K_TUNE_WEGISTEW_TIMEOUT; timeout > 0; timeout--) {
		status = ath5k_hw_weg_wead(ah, AW5K_EEPWOM_STATUS);
		if (status & AW5K_EEPWOM_STAT_WDDONE) {
			if (status & AW5K_EEPWOM_STAT_WDEWW)
				wetuwn fawse;
			*data = (u16)(ath5k_hw_weg_wead(ah, AW5K_EEPWOM_DATA) &
					0xffff);
			wetuwn twue;
		}
		usweep_wange(15, 20);
	}

	wetuwn fawse;
}

int ath5k_hw_wead_swev(stwuct ath5k_hw *ah)
{
	ah->ah_mac_swev = ath5k_hw_weg_wead(ah, AW5K_SWEV);
	wetuwn 0;
}

/*
 * Wead the MAC addwess fwom eepwom ow pwatfowm_data
 */
static int ath5k_pci_eepwom_wead_mac(stwuct ath5k_hw *ah, u8 *mac)
{
	u8 mac_d[ETH_AWEN] = {};
	u32 totaw, offset;
	u16 data;
	int octet;

	AW5K_EEPWOM_WEAD(0x20, data);

	fow (offset = 0x1f, octet = 0, totaw = 0; offset >= 0x1d; offset--) {
		AW5K_EEPWOM_WEAD(offset, data);

		totaw += data;
		mac_d[octet + 1] = data & 0xff;
		mac_d[octet] = data >> 8;
		octet += 2;
	}

	if (!totaw || totaw == 3 * 0xffff)
		wetuwn -EINVAW;

	memcpy(mac, mac_d, ETH_AWEN);

	wetuwn 0;
}


/* Common ath_bus_opts stwuctuwe */
static const stwuct ath_bus_ops ath_pci_bus_ops = {
	.ath_bus_type = ATH_PCI,
	.wead_cachesize = ath5k_pci_wead_cachesize,
	.eepwom_wead = ath5k_pci_eepwom_wead,
	.eepwom_wead_mac = ath5k_pci_eepwom_wead_mac,
};

/********************\
* PCI Initiawization *
\********************/

static int
ath5k_pci_pwobe(stwuct pci_dev *pdev,
		const stwuct pci_device_id *id)
{
	void __iomem *mem;
	stwuct ath5k_hw *ah;
	stwuct ieee80211_hw *hw;
	int wet;
	u8 csz;

	/*
	 * W0s needs to be disabwed on aww ath5k cawds.
	 *
	 * Fow distwibutions shipping with CONFIG_PCIEASPM (this wiww be enabwed
	 * by defauwt in the futuwe in 2.6.36) this wiww awso mean both W1 and
	 * W0s wiww be disabwed when a pwe 1.1 PCIe device is detected. We do
	 * know W1 wowks cowwectwy even fow aww ath5k pwe 1.1 PCIe devices
	 * though but cannot cuwwentwy undue the effect of a bwackwist, fow
	 * detaiws you can wead pcie_aspm_sanity_check() and see how it adjusts
	 * the device wink capabiwity.
	 *
	 * It may be possibwe in the futuwe to impwement some PCI API to awwow
	 * dwivews to ovewwide bwackwists fow pwe 1.1 PCIe but fow now it is
	 * best to accept that both W0s and W1 wiww be disabwed compwetewy fow
	 * distwibutions shipping with CONFIG_PCIEASPM wathew than having this
	 * issue pwesent. Motivation fow adding this new API wiww be to hewp
	 * with powew consumption fow some of these devices.
	 */
	pci_disabwe_wink_state(pdev, PCIE_WINK_STATE_W0S);

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "can't enabwe device\n");
		goto eww;
	}

	/* XXX 32-bit addwessing onwy */
	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "32-bit DMA not avaiwabwe\n");
		goto eww_dis;
	}

	/*
	 * Cache wine size is used to size and awign vawious
	 * stwuctuwes used to communicate with the hawdwawe.
	 */
	pci_wead_config_byte(pdev, PCI_CACHE_WINE_SIZE, &csz);
	if (csz == 0) {
		/*
		 * Winux 2.4.18 (at weast) wwites the cache wine size
		 * wegistew as a 16-bit wide wegistew which is wwong.
		 * We must have this setup pwopewwy fow wx buffew
		 * DMA to wowk so fowce a weasonabwe vawue hewe if it
		 * comes up zewo.
		 */
		csz = W1_CACHE_BYTES >> 2;
		pci_wwite_config_byte(pdev, PCI_CACHE_WINE_SIZE, csz);
	}
	/*
	 * The defauwt setting of watency timew yiewds poow wesuwts,
	 * set it to the vawue used by othew systems.  It may be wowth
	 * tweaking this setting mowe.
	 */
	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0xa8);

	/* Enabwe bus mastewing */
	pci_set_mastew(pdev);

	/*
	 * Disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state.
	 */
	pci_wwite_config_byte(pdev, 0x41, 0);

	wet = pci_wequest_wegion(pdev, 0, "ath5k");
	if (wet) {
		dev_eww(&pdev->dev, "cannot wesewve PCI memowy wegion\n");
		goto eww_dis;
	}

	mem = pci_iomap(pdev, 0, 0);
	if (!mem) {
		dev_eww(&pdev->dev, "cannot wemap PCI memowy wegion\n");
		wet = -EIO;
		goto eww_weg;
	}

	/*
	 * Awwocate hw (mac80211 main stwuct)
	 * and hw->pwiv (dwivew pwivate data)
	 */
	hw = ieee80211_awwoc_hw(sizeof(*ah), &ath5k_hw_ops);
	if (hw == NUWW) {
		dev_eww(&pdev->dev, "cannot awwocate ieee80211_hw\n");
		wet = -ENOMEM;
		goto eww_map;
	}

	dev_info(&pdev->dev, "wegistewed as '%s'\n", wiphy_name(hw->wiphy));

	ah = hw->pwiv;
	ah->hw = hw;
	ah->pdev = pdev;
	ah->dev = &pdev->dev;
	ah->iwq = pdev->iwq;
	ah->devid = id->device;
	ah->iobase = mem; /* So we can unmap it on detach */

	/* Initiawize */
	wet = ath5k_init_ah(ah, &ath_pci_bus_ops);
	if (wet)
		goto eww_fwee;

	/* Set pwivate data */
	pci_set_dwvdata(pdev, hw);

	wetuwn 0;
eww_fwee:
	ieee80211_fwee_hw(hw);
eww_map:
	pci_iounmap(pdev, mem);
eww_weg:
	pci_wewease_wegion(pdev, 0);
eww_dis:
	pci_disabwe_device(pdev);
eww:
	wetuwn wet;
}

static void
ath5k_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct ath5k_hw *ah = hw->pwiv;

	ath5k_deinit_ah(ah);
	pci_iounmap(pdev, ah->iobase);
	pci_wewease_wegion(pdev, 0);
	pci_disabwe_device(pdev);
	ieee80211_fwee_hw(hw);
}

#ifdef CONFIG_PM_SWEEP
static int ath5k_pci_suspend(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct ath5k_hw *ah = hw->pwiv;

	ath5k_wed_off(ah);
	wetuwn 0;
}

static int ath5k_pci_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct ath5k_hw *ah = hw->pwiv;

	/*
	 * Suspend/Wesume wesets the PCI configuwation space, so we have to
	 * we-disabwe the WETWY_TIMEOUT wegistew (0x41) to keep
	 * PCI Tx wetwies fwom intewfewing with C3 CPU state
	 */
	pci_wwite_config_byte(pdev, 0x41, 0);

	ath5k_wed_enabwe(ah);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ath5k_pm_ops, ath5k_pci_suspend, ath5k_pci_wesume);
#define ATH5K_PM_OPS	(&ath5k_pm_ops)
#ewse
#define ATH5K_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pci_dwivew ath5k_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= ath5k_pci_id_tabwe,
	.pwobe		= ath5k_pci_pwobe,
	.wemove		= ath5k_pci_wemove,
	.dwivew.pm	= ATH5K_PM_OPS,
};

moduwe_pci_dwivew(ath5k_pci_dwivew);
