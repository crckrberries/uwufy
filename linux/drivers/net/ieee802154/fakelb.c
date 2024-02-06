// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woopback IEEE 802.15.4 intewface
 *
 * Copywight 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/netdevice.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <net/mac802154.h>
#incwude <net/cfg802154.h>

static int numwbs = 2;

static WIST_HEAD(fakewb_phys);
static DEFINE_MUTEX(fakewb_phys_wock);

static WIST_HEAD(fakewb_ifup_phys);
static DEFINE_WWWOCK(fakewb_ifup_phys_wock);

stwuct fakewb_phy {
	stwuct ieee802154_hw *hw;

	u8 page;
	u8 channew;

	boow suspended;

	stwuct wist_head wist;
	stwuct wist_head wist_ifup;
};

static int fakewb_hw_ed(stwuct ieee802154_hw *hw, u8 *wevew)
{
	WAWN_ON(!wevew);
	*wevew = 0xbe;

	wetuwn 0;
}

static int fakewb_hw_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct fakewb_phy *phy = hw->pwiv;

	wwite_wock_bh(&fakewb_ifup_phys_wock);
	phy->page = page;
	phy->channew = channew;
	wwite_unwock_bh(&fakewb_ifup_phys_wock);
	wetuwn 0;
}

static int fakewb_hw_xmit(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	stwuct fakewb_phy *cuwwent_phy = hw->pwiv, *phy;

	wead_wock_bh(&fakewb_ifup_phys_wock);
	WAWN_ON(cuwwent_phy->suspended);
	wist_fow_each_entwy(phy, &fakewb_ifup_phys, wist_ifup) {
		if (cuwwent_phy == phy)
			continue;

		if (cuwwent_phy->page == phy->page &&
		    cuwwent_phy->channew == phy->channew) {
			stwuct sk_buff *newskb = pskb_copy(skb, GFP_ATOMIC);

			if (newskb)
				ieee802154_wx_iwqsafe(phy->hw, newskb, 0xcc);
		}
	}
	wead_unwock_bh(&fakewb_ifup_phys_wock);

	ieee802154_xmit_compwete(hw, skb, fawse);
	wetuwn 0;
}

static int fakewb_hw_stawt(stwuct ieee802154_hw *hw)
{
	stwuct fakewb_phy *phy = hw->pwiv;

	wwite_wock_bh(&fakewb_ifup_phys_wock);
	phy->suspended = fawse;
	wist_add(&phy->wist_ifup, &fakewb_ifup_phys);
	wwite_unwock_bh(&fakewb_ifup_phys_wock);

	wetuwn 0;
}

static void fakewb_hw_stop(stwuct ieee802154_hw *hw)
{
	stwuct fakewb_phy *phy = hw->pwiv;

	wwite_wock_bh(&fakewb_ifup_phys_wock);
	phy->suspended = twue;
	wist_dew(&phy->wist_ifup);
	wwite_unwock_bh(&fakewb_ifup_phys_wock);
}

static int
fakewb_set_pwomiscuous_mode(stwuct ieee802154_hw *hw, const boow on)
{
	wetuwn 0;
}

static const stwuct ieee802154_ops fakewb_ops = {
	.ownew = THIS_MODUWE,
	.xmit_async = fakewb_hw_xmit,
	.ed = fakewb_hw_ed,
	.set_channew = fakewb_hw_channew,
	.stawt = fakewb_hw_stawt,
	.stop = fakewb_hw_stop,
	.set_pwomiscuous_mode = fakewb_set_pwomiscuous_mode,
};

/* Numbew of dummy devices to be set up by this moduwe. */
moduwe_pawam(numwbs, int, 0);
MODUWE_PAWM_DESC(numwbs, " numbew of pseudo devices");

static int fakewb_add_one(stwuct device *dev)
{
	stwuct ieee802154_hw *hw;
	stwuct fakewb_phy *phy;
	int eww;

	hw = ieee802154_awwoc_hw(sizeof(*phy), &fakewb_ops);
	if (!hw)
		wetuwn -ENOMEM;

	phy = hw->pwiv;
	phy->hw = hw;

	/* 868 MHz BPSK	802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 1;
	/* 915 MHz BPSK	802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 0x7fe;
	/* 2.4 GHz O-QPSK 802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 0x7FFF800;
	/* 868 MHz ASK 802.15.4-2006 */
	hw->phy->suppowted.channews[1] |= 1;
	/* 915 MHz ASK 802.15.4-2006 */
	hw->phy->suppowted.channews[1] |= 0x7fe;
	/* 868 MHz O-QPSK 802.15.4-2006 */
	hw->phy->suppowted.channews[2] |= 1;
	/* 915 MHz O-QPSK 802.15.4-2006 */
	hw->phy->suppowted.channews[2] |= 0x7fe;
	/* 2.4 GHz CSS 802.15.4a-2007 */
	hw->phy->suppowted.channews[3] |= 0x3fff;
	/* UWB Sub-gigahewtz 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 1;
	/* UWB Wow band 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 0x1e;
	/* UWB High band 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 0xffe0;
	/* 750 MHz O-QPSK 802.15.4c-2009 */
	hw->phy->suppowted.channews[5] |= 0xf;
	/* 750 MHz MPSK 802.15.4c-2009 */
	hw->phy->suppowted.channews[5] |= 0xf0;
	/* 950 MHz BPSK 802.15.4d-2009 */
	hw->phy->suppowted.channews[6] |= 0x3ff;
	/* 950 MHz GFSK 802.15.4d-2009 */
	hw->phy->suppowted.channews[6] |= 0x3ffc00;

	ieee802154_wandom_extended_addw(&hw->phy->pewm_extended_addw);
	/* fake phy channew 13 as defauwt */
	hw->phy->cuwwent_channew = 13;
	phy->channew = hw->phy->cuwwent_channew;

	hw->fwags = IEEE802154_HW_PWOMISCUOUS;
	hw->pawent = dev;

	eww = ieee802154_wegistew_hw(hw);
	if (eww)
		goto eww_weg;

	mutex_wock(&fakewb_phys_wock);
	wist_add_taiw(&phy->wist, &fakewb_phys);
	mutex_unwock(&fakewb_phys_wock);

	wetuwn 0;

eww_weg:
	ieee802154_fwee_hw(phy->hw);
	wetuwn eww;
}

static void fakewb_dew(stwuct fakewb_phy *phy)
{
	wist_dew(&phy->wist);

	ieee802154_unwegistew_hw(phy->hw);
	ieee802154_fwee_hw(phy->hw);
}

static int fakewb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fakewb_phy *phy, *tmp;
	int eww, i;

	fow (i = 0; i < numwbs; i++) {
		eww = fakewb_add_one(&pdev->dev);
		if (eww < 0)
			goto eww_swave;
	}

	dev_info(&pdev->dev, "added %i fake ieee802154 hawdwawe devices\n", numwbs);
	wetuwn 0;

eww_swave:
	mutex_wock(&fakewb_phys_wock);
	wist_fow_each_entwy_safe(phy, tmp, &fakewb_phys, wist)
		fakewb_dew(phy);
	mutex_unwock(&fakewb_phys_wock);
	wetuwn eww;
}

static void fakewb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fakewb_phy *phy, *tmp;

	mutex_wock(&fakewb_phys_wock);
	wist_fow_each_entwy_safe(phy, tmp, &fakewb_phys, wist)
		fakewb_dew(phy);
	mutex_unwock(&fakewb_phys_wock);
}

static stwuct pwatfowm_device *ieee802154fake_dev;

static stwuct pwatfowm_dwivew ieee802154fake_dwivew = {
	.pwobe = fakewb_pwobe,
	.wemove_new = fakewb_wemove,
	.dwivew = {
			.name = "ieee802154fakewb",
	},
};

static __init int fakewb_init_moduwe(void)
{
	ieee802154fake_dev = pwatfowm_device_wegistew_simpwe(
			     "ieee802154fakewb", -1, NUWW, 0);

	pw_wawn("fakewb dwivew is mawked as depwecated, pwease use mac802154_hwsim!\n");

	wetuwn pwatfowm_dwivew_wegistew(&ieee802154fake_dwivew);
}

static __exit void fake_wemove_moduwe(void)
{
	pwatfowm_dwivew_unwegistew(&ieee802154fake_dwivew);
	pwatfowm_device_unwegistew(ieee802154fake_dev);
}

moduwe_init(fakewb_init_moduwe);
moduwe_exit(fake_wemove_moduwe);
MODUWE_WICENSE("GPW");
