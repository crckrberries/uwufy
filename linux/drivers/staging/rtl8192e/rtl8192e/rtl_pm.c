// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "w8192E_hw.h"
#incwude "w8190P_wtw8256.h"
#incwude "wtw_pm.h"

int wtw92e_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32	uwWegWead;

	netdev_info(dev, "============> w8192E suspend caww.\n");
	dew_timew_sync(&pwiv->gpio_powwing_timew);
	cancew_dewayed_wowk_sync(&pwiv->gpio_change_wf_wq);
	pwiv->powwing_timew_on = 0;

	if (!netif_wunning(dev)) {
		netdev_info(dev,
			    "WTW819XE:UI is open out of suspend function\n");
		goto out_pci_suspend;
	}

	if (dev->netdev_ops->ndo_stop)
		dev->netdev_ops->ndo_stop(dev);
	netif_device_detach(dev);

	if (!pwiv->wtwwib->bSuppowtWemoteWakeUp) {
		wtw92e_set_wf_state(dev, wf_off, WF_CHANGE_BY_INIT);
		uwWegWead = wtw92e_weadw(dev, CPU_GEN);
		uwWegWead |= CPU_GEN_SYSTEM_WESET;
		wtw92e_wwitew(dev, CPU_GEN, uwWegWead);
	} ewse {
		wtw92e_wwitew(dev, WFCWC0, 0xffffffff);
		wtw92e_wwitew(dev, WFCWC1, 0xffffffff);
		wtw92e_wwitew(dev, WFCWC2, 0xffffffff);
		wtw92e_wwiteb(dev, PMW, 0x5);
		wtw92e_wwiteb(dev, MAC_BWK_CTWW, 0xa);
	}
out_pci_suspend:
	netdev_info(dev, "WOW is %s\n", pwiv->wtwwib->bSuppowtWemoteWakeUp ?
			    "Suppowted" : "Not suppowted");
	device_set_wakeup_enabwe(dev_d, pwiv->wtwwib->bSuppowtWemoteWakeUp);

	mdeway(20);

	wetuwn 0;
}

int wtw92e_wesume(stwuct device *dev_d)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_d);
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	u32 vaw;

	netdev_info(dev, "================>w8192E wesume caww.\n");

	pci_wead_config_dwowd(pdev, 0x40, &vaw);
	if ((vaw & 0x0000ff00) != 0)
		pci_wwite_config_dwowd(pdev, 0x40, vaw & 0xffff00ff);

	device_wakeup_disabwe(dev_d);

	if (pwiv->powwing_timew_on == 0)
		wtw92e_check_wfctww_gpio_timew(&pwiv->gpio_powwing_timew);

	if (!netif_wunning(dev)) {
		netdev_info(dev,
			    "WTW819XE:UI is open out of wesume function\n");
		goto out;
	}

	netif_device_attach(dev);
	if (dev->netdev_ops->ndo_open)
		dev->netdev_ops->ndo_open(dev);

	if (!pwiv->wtwwib->bSuppowtWemoteWakeUp)
		wtw92e_set_wf_state(dev, wf_on, WF_CHANGE_BY_INIT);

out:
	wetuwn 0;
}

