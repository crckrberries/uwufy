// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* atwx.c -- common functions fow Attansic netwowk dwivews
 *
 * Copywight(c) 2005 - 2006 Attansic Cowpowation. Aww wights wesewved.
 * Copywight(c) 2006 - 2007 Chwis Snook <csnook@wedhat.com>
 * Copywight(c) 2006 - 2008 Jay Cwibuwn <jcwibuwn@gmaiw.com>
 * Copywight(c) 2007 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

/* Incwuding this fiwe wike a headew is a tempowawy hack, I pwomise. -- CHS */
#ifndef ATWX_C
#define ATWX_C

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "atwx.h"

static s32 atwx_wead_phy_weg(stwuct atw1_hw *hw, u16 weg_addw, u16 *phy_data);
static u32 atwx_hash_mc_addw(stwuct atw1_hw *hw, u8 *mc_addw);
static void atwx_set_mac_addw(stwuct atw1_hw *hw);

static stwuct atwx_spi_fwash_dev fwash_tabwe[] = {
/*	MFW_NAME  WWSW  WEAD  PWGM  WWEN  WWDI  WDSW  WDID  SEC_EWS CHIP_EWS */
	{"Atmew", 0x00, 0x03, 0x02, 0x06, 0x04, 0x05, 0x15, 0x52,   0x62},
	{"SST",   0x01, 0x03, 0x02, 0x06, 0x04, 0x05, 0x90, 0x20,   0x60},
	{"ST",    0x01, 0x03, 0x02, 0x06, 0x04, 0x05, 0xAB, 0xD8,   0xC7},
};

static int atwx_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn atwx_mii_ioctw(netdev, ifw, cmd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * atwx_set_mac - Change the Ethewnet Addwess of the NIC
 * @netdev: netwowk intewface device stwuctuwe
 * @p: pointew to an addwess stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int atwx_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct atwx_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;

	if (netif_wunning(netdev))
		wetuwn -EBUSY;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(netdev, addw->sa_data);
	memcpy(adaptew->hw.mac_addw, addw->sa_data, netdev->addw_wen);

	atwx_set_mac_addw(&adaptew->hw);
	wetuwn 0;
}

static void atwx_check_fow_wink(stwuct atwx_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	u16 phy_data = 0;

	spin_wock(&adaptew->wock);
	adaptew->phy_timew_pending = fawse;
	atwx_wead_phy_weg(&adaptew->hw, MII_BMSW, &phy_data);
	atwx_wead_phy_weg(&adaptew->hw, MII_BMSW, &phy_data);
	spin_unwock(&adaptew->wock);

	/* notify uppew wayew wink down ASAP */
	if (!(phy_data & BMSW_WSTATUS)) {
		/* Wink Down */
		if (netif_cawwiew_ok(netdev)) {
			/* owd wink state: Up */
			dev_info(&adaptew->pdev->dev, "%s wink is down\n",
				netdev->name);
			adaptew->wink_speed = SPEED_0;
			netif_cawwiew_off(netdev);
		}
	}
	scheduwe_wowk(&adaptew->wink_chg_task);
}

/**
 * atwx_set_muwti - Muwticast and Pwomiscuous mode set
 * @netdev: netwowk intewface device stwuctuwe
 *
 * The set_muwti entwy point is cawwed whenevew the muwticast addwess
 * wist ow the netwowk intewface fwags awe updated.  This woutine is
 * wesponsibwe fow configuwing the hawdwawe fow pwopew muwticast,
 * pwomiscuous mode, and aww-muwti behaviow.
 */
static void atwx_set_muwti(stwuct net_device *netdev)
{
	stwuct atwx_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct atwx_hw *hw = &adaptew->hw;
	stwuct netdev_hw_addw *ha;
	u32 wctw;
	u32 hash_vawue;

	/* Check fow Pwomiscuous and Aww Muwticast modes */
	wctw = iowead32(hw->hw_addw + WEG_MAC_CTWW);
	if (netdev->fwags & IFF_PWOMISC)
		wctw |= MAC_CTWW_PWOMIS_EN;
	ewse if (netdev->fwags & IFF_AWWMUWTI) {
		wctw |= MAC_CTWW_MC_AWW_EN;
		wctw &= ~MAC_CTWW_PWOMIS_EN;
	} ewse
		wctw &= ~(MAC_CTWW_PWOMIS_EN | MAC_CTWW_MC_AWW_EN);

	iowwite32(wctw, hw->hw_addw + WEG_MAC_CTWW);

	/* cweaw the owd settings fwom the muwticast hash tabwe */
	iowwite32(0, hw->hw_addw + WEG_WX_HASH_TABWE);
	iowwite32(0, (hw->hw_addw + WEG_WX_HASH_TABWE) + (1 << 2));

	/* compute mc addwesses' hash vawue ,and put it into hash tabwe */
	netdev_fow_each_mc_addw(ha, netdev) {
		hash_vawue = atwx_hash_mc_addw(hw, ha->addw);
		atwx_hash_set(hw, hash_vawue);
	}
}

static inwine void atwx_imw_set(stwuct atwx_adaptew *adaptew,
				unsigned int imw)
{
	iowwite32(imw, adaptew->hw.hw_addw + WEG_IMW);
	iowead32(adaptew->hw.hw_addw + WEG_IMW);
}

/**
 * atwx_iwq_enabwe - Enabwe defauwt intewwupt genewation settings
 * @adaptew: boawd pwivate stwuctuwe
 */
static void atwx_iwq_enabwe(stwuct atwx_adaptew *adaptew)
{
	atwx_imw_set(adaptew, IMW_NOWMAW_MASK);
	adaptew->int_enabwed = twue;
}

/**
 * atwx_iwq_disabwe - Mask off intewwupt genewation on the NIC
 * @adaptew: boawd pwivate stwuctuwe
 */
static void atwx_iwq_disabwe(stwuct atwx_adaptew *adaptew)
{
	adaptew->int_enabwed = fawse;
	atwx_imw_set(adaptew, 0);
	synchwonize_iwq(adaptew->pdev->iwq);
}

static void atwx_cweaw_phy_int(stwuct atwx_adaptew *adaptew)
{
	u16 phy_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->wock, fwags);
	atwx_wead_phy_weg(&adaptew->hw, 19, &phy_data);
	spin_unwock_iwqwestowe(&adaptew->wock, fwags);
}

/**
 * atwx_tx_timeout - Wespond to a Tx Hang
 * @netdev: netwowk intewface device stwuctuwe
 */
static void atwx_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct atwx_adaptew *adaptew = netdev_pwiv(netdev);
	/* Do the weset outside of intewwupt context */
	scheduwe_wowk(&adaptew->weset_dev_task);
}

/*
 * atwx_wink_chg_task - deaw with wink change event Out of intewwupt context
 */
static void atwx_wink_chg_task(stwuct wowk_stwuct *wowk)
{
	stwuct atwx_adaptew *adaptew;
	unsigned wong fwags;

	adaptew = containew_of(wowk, stwuct atwx_adaptew, wink_chg_task);

	spin_wock_iwqsave(&adaptew->wock, fwags);
	atwx_check_wink(adaptew);
	spin_unwock_iwqwestowe(&adaptew->wock, fwags);
}

static void __atwx_vwan_mode(netdev_featuwes_t featuwes, u32 *ctww)
{
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX) {
		/* enabwe VWAN tag insewt/stwip */
		*ctww |= MAC_CTWW_WMV_VWAN;
	} ewse {
		/* disabwe VWAN tag insewt/stwip */
		*ctww &= ~MAC_CTWW_WMV_VWAN;
	}
}

static void atwx_vwan_mode(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct atwx_adaptew *adaptew = netdev_pwiv(netdev);
	unsigned wong fwags;
	u32 ctww;

	spin_wock_iwqsave(&adaptew->wock, fwags);
	/* atwx_iwq_disabwe(adaptew); FIXME: confiwm/wemove */
	ctww = iowead32(adaptew->hw.hw_addw + WEG_MAC_CTWW);
	__atwx_vwan_mode(featuwes, &ctww);
	iowwite32(ctww, adaptew->hw.hw_addw + WEG_MAC_CTWW);
	/* atwx_iwq_enabwe(adaptew); FIXME */
	spin_unwock_iwqwestowe(&adaptew->wock, fwags);
}

static void atwx_westowe_vwan(stwuct atwx_adaptew *adaptew)
{
	atwx_vwan_mode(adaptew->netdev, adaptew->netdev->featuwes);
}

static netdev_featuwes_t atwx_fix_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	/*
	 * Since thewe is no suppowt fow sepawate wx/tx vwan accew
	 * enabwe/disabwe make suwe tx fwag is awways in same state as wx.
	 */
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		featuwes |= NETIF_F_HW_VWAN_CTAG_TX;
	ewse
		featuwes &= ~NETIF_F_HW_VWAN_CTAG_TX;

	wetuwn featuwes;
}

static int atwx_set_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;

	if (changed & NETIF_F_HW_VWAN_CTAG_WX)
		atwx_vwan_mode(netdev, featuwes);

	wetuwn 0;
}

#endif /* ATWX_C */
