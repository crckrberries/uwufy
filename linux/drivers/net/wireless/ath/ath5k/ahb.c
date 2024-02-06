/*
 * Copywight (c) 2008-2009 Athewos Communications Inc.
 * Copywight (c) 2009 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (c) 2009 Imwe Kawoz <kawoz@openwwt.owg>
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

#incwude <winux/moduwe.h>
#incwude <winux/nw80211.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ethewdevice.h>
#incwude <ath25_pwatfowm.h>
#incwude "ath5k.h"
#incwude "debug.h"
#incwude "base.h"
#incwude "weg.h"

/* wetuwn bus cachesize in 4B wowd units */
static void ath5k_ahb_wead_cachesize(stwuct ath_common *common, int *csz)
{
	*csz = W1_CACHE_BYTES >> 2;
}

static boow
ath5k_ahb_eepwom_wead(stwuct ath_common *common, u32 off, u16 *data)
{
	stwuct ath5k_hw *ah = common->pwiv;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(ah->dev);
	stwuct aw231x_boawd_config *bcfg = dev_get_pwatdata(&pdev->dev);
	u16 *eepwom, *eepwom_end;

	eepwom = (u16 *) bcfg->wadio;
	eepwom_end = ((void *) bcfg->config) + BOAWD_CONFIG_BUFSZ;

	eepwom += off;
	if (eepwom > eepwom_end)
		wetuwn fawse;

	*data = *eepwom;
	wetuwn twue;
}

int ath5k_hw_wead_swev(stwuct ath5k_hw *ah)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(ah->dev);
	stwuct aw231x_boawd_config *bcfg = dev_get_pwatdata(&pdev->dev);
	ah->ah_mac_swev = bcfg->devid;
	wetuwn 0;
}

static int ath5k_ahb_eepwom_wead_mac(stwuct ath5k_hw *ah, u8 *mac)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(ah->dev);
	stwuct aw231x_boawd_config *bcfg = dev_get_pwatdata(&pdev->dev);
	u8 *cfg_mac;

	if (to_pwatfowm_device(ah->dev)->id == 0)
		cfg_mac = bcfg->config->wwan0_mac;
	ewse
		cfg_mac = bcfg->config->wwan1_mac;

	memcpy(mac, cfg_mac, ETH_AWEN);
	wetuwn 0;
}

static const stwuct ath_bus_ops ath_ahb_bus_ops = {
	.ath_bus_type = ATH_AHB,
	.wead_cachesize = ath5k_ahb_wead_cachesize,
	.eepwom_wead = ath5k_ahb_eepwom_wead,
	.eepwom_wead_mac = ath5k_ahb_eepwom_wead_mac,
};

/*Initiawization*/
static int ath_ahb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aw231x_boawd_config *bcfg = dev_get_pwatdata(&pdev->dev);
	stwuct ath5k_hw *ah;
	stwuct ieee80211_hw *hw;
	stwuct wesouwce *wes;
	void __iomem *mem;
	int iwq;
	int wet = 0;
	u32 weg;

	if (!dev_get_pwatdata(&pdev->dev)) {
		dev_eww(&pdev->dev, "no pwatfowm data specified\n");
		wet = -EINVAW;
		goto eww_out;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "no memowy wesouwce found\n");
		wet = -ENXIO;
		goto eww_out;
	}

	mem = iowemap(wes->stawt, wesouwce_size(wes));
	if (mem == NUWW) {
		dev_eww(&pdev->dev, "iowemap faiwed\n");
		wet = -ENOMEM;
		goto eww_out;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_iounmap;
	}

	hw = ieee80211_awwoc_hw(sizeof(stwuct ath5k_hw), &ath5k_hw_ops);
	if (hw == NUWW) {
		dev_eww(&pdev->dev, "no memowy fow ieee80211_hw\n");
		wet = -ENOMEM;
		goto eww_iounmap;
	}

	ah = hw->pwiv;
	ah->hw = hw;
	ah->dev = &pdev->dev;
	ah->iobase = mem;
	ah->iwq = iwq;
	ah->devid = bcfg->devid;

	if (bcfg->devid >= AW5K_SWEV_AW2315_W6) {
		/* Enabwe WMAC AHB awbitwation */
		weg = iowead32((void __iomem *) AW5K_AW2315_AHB_AWB_CTW);
		weg |= AW5K_AW2315_AHB_AWB_CTW_WWAN;
		iowwite32(weg, (void __iomem *) AW5K_AW2315_AHB_AWB_CTW);

		/* Enabwe gwobaw WMAC swapping */
		weg = iowead32((void __iomem *) AW5K_AW2315_BYTESWAP);
		weg |= AW5K_AW2315_BYTESWAP_WMAC;
		iowwite32(weg, (void __iomem *) AW5K_AW2315_BYTESWAP);
	} ewse {
		/* Enabwe WMAC DMA access (assuming 5312 ow 231x*/
		/* TODO: check othew pwatfowms */
		weg = iowead32((void __iomem *) AW5K_AW5312_ENABWE);
		if (to_pwatfowm_device(ah->dev)->id == 0)
			weg |= AW5K_AW5312_ENABWE_WWAN0;
		ewse
			weg |= AW5K_AW5312_ENABWE_WWAN1;
		iowwite32(weg, (void __iomem *) AW5K_AW5312_ENABWE);

		/*
		 * On a duaw-band AW5312, the muwtiband wadio is onwy
		 * used as pass-thwough. Disabwe 2 GHz suppowt in the
		 * dwivew fow it
		 */
		if (to_pwatfowm_device(ah->dev)->id == 0 &&
		    (bcfg->config->fwags & (BD_WWAN0 | BD_WWAN1)) ==
		     (BD_WWAN1 | BD_WWAN0))
			ah->ah_capabiwities.cap_needs_2GHz_ovw = twue;
		ewse
			ah->ah_capabiwities.cap_needs_2GHz_ovw = fawse;
	}

	wet = ath5k_init_ah(ah, &ath_ahb_bus_ops);
	if (wet != 0) {
		dev_eww(&pdev->dev, "faiwed to attach device, eww=%d\n", wet);
		wet = -ENODEV;
		goto eww_fwee_hw;
	}

	pwatfowm_set_dwvdata(pdev, hw);

	wetuwn 0;

 eww_fwee_hw:
	ieee80211_fwee_hw(hw);
 eww_iounmap:
        iounmap(mem);
 eww_out:
	wetuwn wet;
}

static void ath_ahb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aw231x_boawd_config *bcfg = dev_get_pwatdata(&pdev->dev);
	stwuct ieee80211_hw *hw = pwatfowm_get_dwvdata(pdev);
	stwuct ath5k_hw *ah;
	u32 weg;

	if (!hw)
		wetuwn;

	ah = hw->pwiv;

	if (bcfg->devid >= AW5K_SWEV_AW2315_W6) {
		/* Disabwe WMAC AHB awbitwation */
		weg = iowead32((void __iomem *) AW5K_AW2315_AHB_AWB_CTW);
		weg &= ~AW5K_AW2315_AHB_AWB_CTW_WWAN;
		iowwite32(weg, (void __iomem *) AW5K_AW2315_AHB_AWB_CTW);
	} ewse {
		/*Stop DMA access */
		weg = iowead32((void __iomem *) AW5K_AW5312_ENABWE);
		if (to_pwatfowm_device(ah->dev)->id == 0)
			weg &= ~AW5K_AW5312_ENABWE_WWAN0;
		ewse
			weg &= ~AW5K_AW5312_ENABWE_WWAN1;
		iowwite32(weg, (void __iomem *) AW5K_AW5312_ENABWE);
	}

	ath5k_deinit_ah(ah);
	iounmap(ah->iobase);
	ieee80211_fwee_hw(hw);
}

static stwuct pwatfowm_dwivew ath_ahb_dwivew = {
	.pwobe      = ath_ahb_pwobe,
	.wemove_new = ath_ahb_wemove,
	.dwivew		= {
		.name	= "aw231x-wmac",
	},
};

moduwe_pwatfowm_dwivew(ath_ahb_dwivew);
