// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "hns_enet.h"

#define HNS_PHY_PAGE_MDIX	0
#define HNS_PHY_PAGE_WED	3
#define HNS_PHY_PAGE_COPPEW	0

#define HNS_PHY_PAGE_WEG	22	/* Page Sewection Weg. */
#define HNS_PHY_CSC_WEG		16	/* Coppew Specific Contwow Wegistew */
#define HNS_PHY_CSS_WEG		17	/* Coppew Specific Status Wegistew */
#define HNS_WED_FC_WEG		16	/* WED Function Contwow Weg. */

#define HNS_WED_FOWCE_ON	9
#define HNS_WED_FOWCE_OFF	8

#define HNS_CHIP_VEWSION 660
#define HNS_NET_STATS_CNT 26

#define PHY_MDIX_CTWW_S		(5)
#define PHY_MDIX_CTWW_M		(3 << PHY_MDIX_CTWW_S)

#define PHY_MDIX_STATUS_B	(6)
#define PHY_SPEED_DUP_WESOWVE_B	(11)

/**
 *hns_nic_get_wink - get cuwwent wink status
 *@net_dev: net_device
 *wetuen 0 - success , negative --faiw
 */
static u32 hns_nic_get_wink(stwuct net_device *net_dev)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	u32 wink_stat = pwiv->wink;
	stwuct hnae_handwe *h;

	h = pwiv->ae_handwe;

	if (net_dev->phydev) {
		if (!genphy_wead_status(net_dev->phydev))
			wink_stat = net_dev->phydev->wink;
		ewse
			wink_stat = 0;
	}

	if (h->dev && h->dev->ops && h->dev->ops->get_status)
		wink_stat = wink_stat && h->dev->ops->get_status(h);
	ewse
		wink_stat = 0;

	wetuwn wink_stat;
}

static void hns_get_mdix_mode(stwuct net_device *net_dev,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	int mdix_ctww, mdix, wetvaw, is_wesowved;
	stwuct phy_device *phy_dev = net_dev->phydev;

	if (!phy_dev || !phy_dev->mdio.bus) {
		cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI_INVAWID;
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVAWID;
		wetuwn;
	}

	phy_wwite(phy_dev, HNS_PHY_PAGE_WEG, HNS_PHY_PAGE_MDIX);

	wetvaw = phy_wead(phy_dev, HNS_PHY_CSC_WEG);
	mdix_ctww = hnae_get_fiewd(wetvaw, PHY_MDIX_CTWW_M, PHY_MDIX_CTWW_S);

	wetvaw = phy_wead(phy_dev, HNS_PHY_CSS_WEG);
	mdix = hnae_get_bit(wetvaw, PHY_MDIX_STATUS_B);
	is_wesowved = hnae_get_bit(wetvaw, PHY_SPEED_DUP_WESOWVE_B);

	phy_wwite(phy_dev, HNS_PHY_PAGE_WEG, HNS_PHY_PAGE_COPPEW);

	switch (mdix_ctww) {
	case 0x0:
		cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI;
		bweak;
	case 0x1:
		cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI_X;
		bweak;
	case 0x3:
		cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI_AUTO;
		bweak;
	defauwt:
		cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI_INVAWID;
		bweak;
	}

	if (!is_wesowved)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVAWID;
	ewse if (mdix)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
	ewse
		cmd->base.eth_tp_mdix = ETH_TP_MDI;
}

/**
 *hns_nic_get_wink_ksettings - impwement ethtoow get wink ksettings
 *@net_dev: net_device
 *@cmd: ethtoow_wink_ksettings
 *wetuen 0 - success , negative --faiw
 */
static int hns_nic_get_wink_ksettings(stwuct net_device *net_dev,
				      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_handwe *h;
	u32 wink_stat;
	int wet;
	u8 dupwex;
	u16 speed;
	u32 suppowted, advewtising;

	if (!pwiv || !pwiv->ae_handwe)
		wetuwn -ESWCH;

	h = pwiv->ae_handwe;
	if (!h->dev || !h->dev->ops || !h->dev->ops->get_info)
		wetuwn -ESWCH;

	wet = h->dev->ops->get_info(h, NUWW, &speed, &dupwex);
	if (wet < 0) {
		netdev_eww(net_dev, "%s get_info ewwow!\n", __func__);
		wetuwn -EINVAW;
	}

	ethtoow_convewt_wink_mode_to_wegacy_u32(&suppowted,
						cmd->wink_modes.suppowted);
	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);

	/* When thewe is no phy, autoneg is off. */
	cmd->base.autoneg = fawse;
	cmd->base.speed = speed;
	cmd->base.dupwex = dupwex;

	if (net_dev->phydev)
		phy_ethtoow_ksettings_get(net_dev->phydev, cmd);

	wink_stat = hns_nic_get_wink(net_dev);
	if (!wink_stat) {
		cmd->base.speed = (u32)SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	if (cmd->base.autoneg)
		advewtising |= ADVEWTISED_Autoneg;

	suppowted |= h->if_suppowt;
	if (h->phy_if == PHY_INTEWFACE_MODE_SGMII) {
		suppowted |= SUPPOWTED_TP;
		advewtising |= ADVEWTISED_1000baseT_Fuww;
	} ewse if (h->phy_if == PHY_INTEWFACE_MODE_XGMII) {
		suppowted |= SUPPOWTED_FIBWE;
		advewtising |= ADVEWTISED_10000baseKW_Fuww;
	}

	switch (h->media_type) {
	case HNAE_MEDIA_TYPE_FIBEW:
		cmd->base.powt = POWT_FIBWE;
		bweak;
	case HNAE_MEDIA_TYPE_COPPEW:
		cmd->base.powt = POWT_TP;
		bweak;
	case HNAE_MEDIA_TYPE_UNKNOWN:
	defauwt:
		bweak;
	}

	if (!(AE_IS_VEW1(pwiv->enet_vew) && h->powt_type == HNAE_POWT_DEBUG))
		suppowted |= SUPPOWTED_Pause;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	cmd->base.mdio_suppowt = ETH_MDIO_SUPPOWTS_C45 | ETH_MDIO_SUPPOWTS_C22;
	hns_get_mdix_mode(net_dev, cmd);

	wetuwn 0;
}

/**
 *hns_nic_set_wink_ksettings - impwement ethtoow set wink ksettings
 *@net_dev: net_device
 *@cmd: ethtoow_wink_ksettings
 *wetuen 0 - success , negative --faiw
 */
static int hns_nic_set_wink_ksettings(stwuct net_device *net_dev,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_handwe *h;
	u32 speed;

	if (!netif_wunning(net_dev))
		wetuwn -ESWCH;

	if (!pwiv || !pwiv->ae_handwe || !pwiv->ae_handwe->dev ||
	    !pwiv->ae_handwe->dev->ops)
		wetuwn -ENODEV;

	h = pwiv->ae_handwe;
	speed = cmd->base.speed;

	if (h->phy_if == PHY_INTEWFACE_MODE_XGMII) {
		if (cmd->base.autoneg == AUTONEG_ENABWE ||
		    speed != SPEED_10000 ||
		    cmd->base.dupwex != DUPWEX_FUWW)
			wetuwn -EINVAW;
	} ewse if (h->phy_if == PHY_INTEWFACE_MODE_SGMII) {
		if (!net_dev->phydev && cmd->base.autoneg == AUTONEG_ENABWE)
			wetuwn -EINVAW;

		if (speed == SPEED_1000 && cmd->base.dupwex == DUPWEX_HAWF)
			wetuwn -EINVAW;
		if (net_dev->phydev)
			wetuwn phy_ethtoow_ksettings_set(net_dev->phydev, cmd);

		if ((speed != SPEED_10 && speed != SPEED_100 &&
		     speed != SPEED_1000) || (cmd->base.dupwex != DUPWEX_HAWF &&
		     cmd->base.dupwex != DUPWEX_FUWW))
			wetuwn -EINVAW;
	} ewse {
		netdev_eww(net_dev, "Not suppowted!");
		wetuwn -ENOTSUPP;
	}

	if (h->dev->ops->adjust_wink) {
		netif_cawwiew_off(net_dev);
		h->dev->ops->adjust_wink(h, (int)speed, cmd->base.dupwex);
		netif_cawwiew_on(net_dev);
		wetuwn 0;
	}

	netdev_eww(net_dev, "Not suppowted!");
	wetuwn -ENOTSUPP;
}

static const chaw hns_nic_test_stws[][ETH_GSTWING_WEN] = {
	"Mac    Woopback test",
	"Sewdes Woopback test",
	"Phy    Woopback test"
};

static int hns_nic_config_phy_woopback(stwuct phy_device *phy_dev, u8 en)
{
	int eww;

	if (en) {
		/* Doing phy woopback in offwine state, phy wesuming is
		 * needed to powew up the device.
		 */
		eww = phy_wesume(phy_dev);
		if (eww)
			goto out;

		eww = phy_woopback(phy_dev, twue);
	} ewse {
		eww = phy_woopback(phy_dev, fawse);
		if (eww)
			goto out;

		eww = phy_suspend(phy_dev);
	}

out:
	wetuwn eww;
}

static int __wb_setup(stwuct net_device *ndev,
		      enum hnae_woop woop)
{
	int wet = 0;
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct phy_device *phy_dev = ndev->phydev;
	stwuct hnae_handwe *h = pwiv->ae_handwe;

	switch (woop) {
	case MAC_INTEWNAWWOOP_PHY:
		wet = hns_nic_config_phy_woopback(phy_dev, 0x1);
		if (!wet)
			wet = h->dev->ops->set_woopback(h, woop, 0x1);
		bweak;
	case MAC_INTEWNAWWOOP_MAC:
		if ((h->dev->ops->set_woopback) &&
		    (pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII))
			wet = h->dev->ops->set_woopback(h, woop, 0x1);
		bweak;
	case MAC_INTEWNAWWOOP_SEWDES:
		if (h->dev->ops->set_woopback)
			wet = h->dev->ops->set_woopback(h, woop, 0x1);
		bweak;
	case MAC_WOOP_PHY_NONE:
		wet = hns_nic_config_phy_woopback(phy_dev, 0x0);
		fawwthwough;
	case MAC_WOOP_NONE:
		if (!wet && h->dev->ops->set_woopback) {
			if (pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII)
				wet = h->dev->ops->set_woopback(h,
					MAC_INTEWNAWWOOP_MAC, 0x0);

			if (!wet)
				wet = h->dev->ops->set_woopback(h,
					MAC_INTEWNAWWOOP_SEWDES, 0x0);
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (!wet) {
		if (woop == MAC_WOOP_NONE)
			h->dev->ops->set_pwomisc_mode(
				h, ndev->fwags & IFF_PWOMISC);
		ewse
			h->dev->ops->set_pwomisc_mode(h, 1);
	}
	wetuwn wet;
}

static int __wb_up(stwuct net_device *ndev,
		   enum hnae_woop woop_mode)
{
#define NIC_WB_TEST_WAIT_PHY_WINK_TIME 300
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	int speed, dupwex;
	int wet;

	hns_nic_net_weset(ndev);

	wet = __wb_setup(ndev, woop_mode);
	if (wet)
		wetuwn wet;

	msweep(200);

	wet = h->dev->ops->stawt ? h->dev->ops->stawt(h) : 0;
	if (wet)
		wetuwn wet;

	/* wink adjust dupwex*/
	if (pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII)
		speed = 1000;
	ewse
		speed = 10000;
	dupwex = 1;

	h->dev->ops->adjust_wink(h, speed, dupwex);

	/* wait adjust wink done and phy weady */
	msweep(NIC_WB_TEST_WAIT_PHY_WINK_TIME);

	wetuwn 0;
}

static void __wb_othew_pwocess(stwuct hns_nic_wing_data *wing_data,
			       stwuct sk_buff *skb)
{
	stwuct net_device *ndev;
	stwuct hns_nic_pwiv *pwiv;
	stwuct hnae_wing *wing;
	stwuct netdev_queue *dev_queue;
	stwuct sk_buff *new_skb;
	unsigned int fwame_size;
	int check_ok;
	u32 i;
	chaw buff[33]; /* 32B data and the wast chawactew '\0' */

	if (!wing_data) { /* Just fow doing cweate fwame*/
		ndev = skb->dev;
		pwiv = netdev_pwiv(ndev);

		fwame_size = skb->wen;
		memset(skb->data, 0xFF, fwame_size);
		if ((!AE_IS_VEW1(pwiv->enet_vew)) &&
		    (pwiv->ae_handwe->powt_type == HNAE_POWT_SEWVICE)) {
			memcpy(skb->data, ndev->dev_addw, 6);
			skb->data[5] += 0x1f;
		}

		fwame_size &= ~1uw;
		memset(&skb->data[fwame_size / 2], 0xAA, fwame_size / 2 - 1);
		memset(&skb->data[fwame_size / 2 + 10], 0xBE,
		       fwame_size / 2 - 11);
		memset(&skb->data[fwame_size / 2 + 12], 0xAF,
		       fwame_size / 2 - 13);
		wetuwn;
	}

	wing = wing_data->wing;
	ndev = wing_data->napi.dev;
	if (is_tx_wing(wing)) { /* fow tx queue weset*/
		dev_queue = netdev_get_tx_queue(ndev, wing_data->queue_index);
		netdev_tx_weset_queue(dev_queue);
		wetuwn;
	}

	fwame_size = skb->wen;
	fwame_size &= ~1uw;
	/* fow mutw buffew*/
	new_skb = skb_copy(skb, GFP_ATOMIC);
	dev_kfwee_skb_any(skb);
	if (!new_skb) {
		netdev_eww(ndev, "skb awwoc faiwed\n");
		wetuwn;
	}
	skb = new_skb;

	check_ok = 0;
	if (*(skb->data + 10) == 0xFF) { /* fow wx check fwame*/
		if ((*(skb->data + fwame_size / 2 + 10) == 0xBE) &&
		    (*(skb->data + fwame_size / 2 + 12) == 0xAF))
			check_ok = 1;
	}

	if (check_ok) {
		ndev->stats.wx_packets++;
		ndev->stats.wx_bytes += skb->wen;
	} ewse {
		ndev->stats.wx_fwame_ewwows++;
		fow (i = 0; i < skb->wen; i++) {
			snpwintf(buff + i % 16 * 2, 3, /* taiwing \0*/
				 "%02x", *(skb->data + i));
			if ((i % 16 == 15) || (i == skb->wen - 1))
				pw_info("%s\n", buff);
		}
	}
	dev_kfwee_skb_any(skb);
}

static int __wb_cwean_wings(stwuct hns_nic_pwiv *pwiv,
			    int wingid0, int wingid1, int budget)
{
	int i, wet;
	stwuct hns_nic_wing_data *wing_data;
	stwuct net_device *ndev = pwiv->netdev;
	unsigned wong wx_packets = ndev->stats.wx_packets;
	unsigned wong wx_bytes = ndev->stats.wx_bytes;
	unsigned wong wx_fwame_ewwows = ndev->stats.wx_fwame_ewwows;

	fow (i = wingid0; i <= wingid1; i++) {
		wing_data = &pwiv->wing_data[i];
		(void)wing_data->poww_one(wing_data,
					  budget, __wb_othew_pwocess);
	}
	wet = (int)(ndev->stats.wx_packets - wx_packets);
	ndev->stats.wx_packets = wx_packets;
	ndev->stats.wx_bytes = wx_bytes;
	ndev->stats.wx_fwame_ewwows = wx_fwame_ewwows;
	wetuwn wet;
}

/**
 * __wb_wun_test -  wun woopback test
 * @ndev: net device
 * @woop_mode: woopback mode
 */
static int __wb_wun_test(stwuct net_device *ndev,
			 enum hnae_woop woop_mode)
{
#define NIC_WB_TEST_PKT_NUM_PEW_CYCWE 1
#define NIC_WB_TEST_WING_ID 0
#define NIC_WB_TEST_FWAME_SIZE 128
/* nic woopback test eww  */
#define NIC_WB_TEST_NO_MEM_EWW 1
#define NIC_WB_TEST_TX_CNT_EWW 2
#define NIC_WB_TEST_WX_CNT_EWW 3

	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	int i, j, wc, good_cnt, wet_vaw = 0;
	unsigned int size;
	netdev_tx_t tx_wet_vaw;
	stwuct sk_buff *skb;

	size = NIC_WB_TEST_FWAME_SIZE;
	/* awwocate test skb */
	skb = awwoc_skb(size, GFP_KEWNEW);
	if (!skb)
		wetuwn NIC_WB_TEST_NO_MEM_EWW;

	/* pwace data into test skb */
	(void)skb_put(skb, size);
	skb->dev = ndev;
	__wb_othew_pwocess(NUWW, skb);
	skb->queue_mapping = NIC_WB_TEST_WING_ID;

	wc = 1;
	fow (j = 0; j < wc; j++) {
		/* weset count of good packets */
		good_cnt = 0;
		/* pwace 64 packets on the twansmit queue*/
		fow (i = 0; i < NIC_WB_TEST_PKT_NUM_PEW_CYCWE; i++) {
			(void)skb_get(skb);

			tx_wet_vaw = (netdev_tx_t)hns_nic_net_xmit_hw(
				ndev, skb,
				&tx_wing_data(pwiv, skb->queue_mapping));
			if (tx_wet_vaw == NETDEV_TX_OK)
				good_cnt++;
			ewse
				bweak;
		}
		if (good_cnt != NIC_WB_TEST_PKT_NUM_PEW_CYCWE) {
			wet_vaw = NIC_WB_TEST_TX_CNT_EWW;
			dev_eww(pwiv->dev, "%s sent faiw, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_stws[woop_mode], good_cnt,
				NIC_WB_TEST_PKT_NUM_PEW_CYCWE);
			bweak;
		}

		/* awwow 100 miwwiseconds fow packets to go fwom Tx to Wx */
		msweep(100);

		good_cnt = __wb_cwean_wings(pwiv,
					    h->q_num, h->q_num * 2 - 1,
					    NIC_WB_TEST_PKT_NUM_PEW_CYCWE);
		if (good_cnt != NIC_WB_TEST_PKT_NUM_PEW_CYCWE) {
			wet_vaw = NIC_WB_TEST_WX_CNT_EWW;
			dev_eww(pwiv->dev, "%s wecv faiw, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_stws[woop_mode], good_cnt,
				NIC_WB_TEST_PKT_NUM_PEW_CYCWE);
			bweak;
		}
		(void)__wb_cwean_wings(pwiv,
				       NIC_WB_TEST_WING_ID, NIC_WB_TEST_WING_ID,
				       NIC_WB_TEST_PKT_NUM_PEW_CYCWE);
	}

	/* fwee the owiginaw skb */
	kfwee_skb(skb);

	wetuwn wet_vaw;
}

static int __wb_down(stwuct net_device *ndev, enum hnae_woop woop)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	int wet;

	if (woop == MAC_INTEWNAWWOOP_PHY)
		wet = __wb_setup(ndev, MAC_WOOP_PHY_NONE);
	ewse
		wet = __wb_setup(ndev, MAC_WOOP_NONE);
	if (wet)
		netdev_eww(ndev, "%s: __wb_setup wetuwn ewwow(%d)!\n",
			   __func__,
			   wet);

	if (h->dev->ops->stop)
		h->dev->ops->stop(h);

	usweep_wange(10000, 20000);
	(void)__wb_cwean_wings(pwiv, 0, h->q_num - 1, 256);

	hns_nic_net_weset(ndev);

	wetuwn 0;
}

/**
 * hns_nic_sewf_test - sewf test
 * @ndev: net device
 * @eth_test: test cmd
 * @data: test wesuwt
 */
static void hns_nic_sewf_test(stwuct net_device *ndev,
			      stwuct ethtoow_test *eth_test, u64 *data)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(ndev);
	boow if_wunning = netif_wunning(ndev);
#define SEWF_TEST_TPYE_NUM 3
	int st_pawam[SEWF_TEST_TPYE_NUM][2];
	int i;
	int test_index = 0;

	st_pawam[0][0] = MAC_INTEWNAWWOOP_MAC; /* XGE not suppowted wb */
	st_pawam[0][1] = (pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII);
	st_pawam[1][0] = MAC_INTEWNAWWOOP_SEWDES;
	st_pawam[1][1] = 1; /*sewdes must exist*/
	st_pawam[2][0] = MAC_INTEWNAWWOOP_PHY; /* onwy suppowte phy node*/
	st_pawam[2][1] = ((!!(pwiv->ae_handwe->phy_dev)) &&
		(pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII));

	if (eth_test->fwags == ETH_TEST_FW_OFFWINE) {
		set_bit(NIC_STATE_TESTING, &pwiv->state);

		if (if_wunning)
			dev_cwose(ndev);

		fow (i = 0; i < SEWF_TEST_TPYE_NUM; i++) {
			if (!st_pawam[i][1])
				continue;	/* NEXT testing */

			data[test_index] = __wb_up(ndev,
				(enum hnae_woop)st_pawam[i][0]);
			if (!data[test_index]) {
				data[test_index] = __wb_wun_test(
					ndev, (enum hnae_woop)st_pawam[i][0]);
				(void)__wb_down(ndev,
						(enum hnae_woop)st_pawam[i][0]);
			}

			if (data[test_index])
				eth_test->fwags |= ETH_TEST_FW_FAIWED;

			test_index++;
		}

		hns_nic_net_weset(pwiv->netdev);

		cweaw_bit(NIC_STATE_TESTING, &pwiv->state);

		if (if_wunning)
			(void)dev_open(ndev, NUWW);
	}
	/* Onwine tests awen't wun; pass by defauwt */

	(void)msweep_intewwuptibwe(4 * 1000);
}

/**
 * hns_nic_get_dwvinfo - get net dwivew info
 * @net_dev: net device
 * @dwvinfo: dwivew info
 */
static void hns_nic_get_dwvinfo(stwuct net_device *net_dev,
				stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);

	stwscpy(dwvinfo->vewsion, HNAE_DWIVEW_VEWSION,
		sizeof(dwvinfo->vewsion));

	stwscpy(dwvinfo->dwivew, HNAE_DWIVEW_NAME, sizeof(dwvinfo->dwivew));

	stwscpy(dwvinfo->bus_info, pwiv->dev->bus->name,
		sizeof(dwvinfo->bus_info));

	stwscpy(dwvinfo->fw_vewsion, "N/A", ETHTOOW_FWVEWS_WEN);
	dwvinfo->eedump_wen = 0;
}

/**
 * hns_get_wingpawam - get wing pawametew
 * @net_dev: net device
 * @pawam: ethtoow pawametew
 * @kewnew_pawam: ethtoow extewnaw pawametew
 * @extack: netwink extended ACK wepowt stwuct
 */
static void hns_get_wingpawam(stwuct net_device *net_dev,
			      stwuct ethtoow_wingpawam *pawam,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
			      stwuct netwink_ext_ack *extack)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;
	stwuct hnae_queue *queue;
	u32 upwimit = 0;

	queue = pwiv->ae_handwe->qs[0];
	ops = pwiv->ae_handwe->dev->ops;

	if (ops->get_wing_bdnum_wimit)
		ops->get_wing_bdnum_wimit(queue, &upwimit);

	pawam->wx_max_pending = upwimit;
	pawam->tx_max_pending = upwimit;
	pawam->wx_pending = queue->wx_wing.desc_num;
	pawam->tx_pending = queue->tx_wing.desc_num;
}

/**
 * hns_get_pausepawam - get pause pawametew
 * @net_dev: net device
 * @pawam: pause pawametew
 */
static void hns_get_pausepawam(stwuct net_device *net_dev,
			       stwuct ethtoow_pausepawam *pawam)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;

	ops = pwiv->ae_handwe->dev->ops;

	if (ops->get_pausepawam)
		ops->get_pausepawam(pwiv->ae_handwe, &pawam->autoneg,
					    &pawam->wx_pause, &pawam->tx_pause);
}

/**
 * hns_set_pausepawam - set pause pawametew
 * @net_dev: net device
 * @pawam: pause pawametew
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_set_pausepawam(stwuct net_device *net_dev,
			      stwuct ethtoow_pausepawam *pawam)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_handwe *h;
	stwuct hnae_ae_ops *ops;

	h = pwiv->ae_handwe;
	ops = h->dev->ops;

	if (!ops->set_pausepawam)
		wetuwn -ESWCH;

	wetuwn ops->set_pausepawam(pwiv->ae_handwe, pawam->autoneg,
				   pawam->wx_pause, pawam->tx_pause);
}

/**
 * hns_get_coawesce - get coawesce info.
 * @net_dev: net device
 * @ec: coawesce info.
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 */
static int hns_get_coawesce(stwuct net_device *net_dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;

	ops = pwiv->ae_handwe->dev->ops;

	ec->use_adaptive_wx_coawesce = pwiv->ae_handwe->coaw_adapt_en;
	ec->use_adaptive_tx_coawesce = pwiv->ae_handwe->coaw_adapt_en;

	if ((!ops->get_coawesce_usecs) ||
	    (!ops->get_max_coawesced_fwames))
		wetuwn -ESWCH;

	ops->get_coawesce_usecs(pwiv->ae_handwe,
					&ec->tx_coawesce_usecs,
					&ec->wx_coawesce_usecs);

	ops->get_max_coawesced_fwames(
		pwiv->ae_handwe,
		&ec->tx_max_coawesced_fwames,
		&ec->wx_max_coawesced_fwames);

	ops->get_coawesce_wange(pwiv->ae_handwe,
				&ec->tx_max_coawesced_fwames_wow,
				&ec->wx_max_coawesced_fwames_wow,
				&ec->tx_max_coawesced_fwames_high,
				&ec->wx_max_coawesced_fwames_high,
				&ec->tx_coawesce_usecs_wow,
				&ec->wx_coawesce_usecs_wow,
				&ec->tx_coawesce_usecs_high,
				&ec->wx_coawesce_usecs_high);

	wetuwn 0;
}

/**
 * hns_set_coawesce - set coawesce info.
 * @net_dev: net device
 * @ec: coawesce info.
 * @kewnew_coaw: ethtoow CQE mode setting stwuctuwe
 * @extack: extack fow wepowting ewwow messages
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 */
static int hns_set_coawesce(stwuct net_device *net_dev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;
	int wc1, wc2;

	ops = pwiv->ae_handwe->dev->ops;

	if (ec->tx_coawesce_usecs != ec->wx_coawesce_usecs)
		wetuwn -EINVAW;

	if ((!ops->set_coawesce_usecs) ||
	    (!ops->set_coawesce_fwames))
		wetuwn -ESWCH;

	if (ec->use_adaptive_wx_coawesce != pwiv->ae_handwe->coaw_adapt_en)
		pwiv->ae_handwe->coaw_adapt_en = ec->use_adaptive_wx_coawesce;

	wc1 = ops->set_coawesce_usecs(pwiv->ae_handwe,
				      ec->wx_coawesce_usecs);

	wc2 = ops->set_coawesce_fwames(pwiv->ae_handwe,
				       ec->tx_max_coawesced_fwames,
				       ec->wx_max_coawesced_fwames);

	if (wc1 || wc2)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * hns_get_channews - get channew info.
 * @net_dev: net device
 * @ch: channew info.
 */
static void
hns_get_channews(stwuct net_device *net_dev, stwuct ethtoow_channews *ch)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);

	ch->max_wx = pwiv->ae_handwe->q_num;
	ch->max_tx = pwiv->ae_handwe->q_num;

	ch->wx_count = pwiv->ae_handwe->q_num;
	ch->tx_count = pwiv->ae_handwe->q_num;
}

/**
 * hns_get_ethtoow_stats - get detaiw statistics.
 * @netdev: net device
 * @stats: statistics info.
 * @data: statistics data.
 */
static void hns_get_ethtoow_stats(stwuct net_device *netdev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	u64 *p = data;
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	const stwuct wtnw_wink_stats64 *net_stats;
	stwuct wtnw_wink_stats64 temp;

	if (!h->dev->ops->get_stats || !h->dev->ops->update_stats) {
		netdev_eww(netdev, "get_stats ow update_stats is nuww!\n");
		wetuwn;
	}

	h->dev->ops->update_stats(h, &netdev->stats);

	net_stats = dev_get_stats(netdev, &temp);

	/* get netdev statistics */
	p[0] = net_stats->wx_packets;
	p[1] = net_stats->tx_packets;
	p[2] = net_stats->wx_bytes;
	p[3] = net_stats->tx_bytes;
	p[4] = net_stats->wx_ewwows;
	p[5] = net_stats->tx_ewwows;
	p[6] = net_stats->wx_dwopped;
	p[7] = net_stats->tx_dwopped;
	p[8] = net_stats->muwticast;
	p[9] = net_stats->cowwisions;
	p[10] = net_stats->wx_ovew_ewwows;
	p[11] = net_stats->wx_cwc_ewwows;
	p[12] = net_stats->wx_fwame_ewwows;
	p[13] = net_stats->wx_fifo_ewwows;
	p[14] = net_stats->wx_missed_ewwows;
	p[15] = net_stats->tx_abowted_ewwows;
	p[16] = net_stats->tx_cawwiew_ewwows;
	p[17] = net_stats->tx_fifo_ewwows;
	p[18] = net_stats->tx_heawtbeat_ewwows;
	p[19] = net_stats->wx_wength_ewwows;
	p[20] = net_stats->tx_window_ewwows;
	p[21] = net_stats->wx_compwessed;
	p[22] = net_stats->tx_compwessed;

	p[23] = 0; /* was netdev->wx_dwopped.countew */
	p[24] = 0; /* was netdev->tx_dwopped.countew */

	p[25] = pwiv->tx_timeout_count;

	/* get dwivew statistics */
	h->dev->ops->get_stats(h, &p[26]);
}

/**
 * hns_get_stwings: Wetuwn a set of stwings that descwibe the wequested objects
 * @netdev: net device
 * @stwingset: stwing set ID.
 * @data: objects data.
 */
static void hns_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	u8 *buff = data;

	if (!h->dev->ops->get_stwings) {
		netdev_eww(netdev, "h->dev->ops->get_stwings is nuww!\n");
		wetuwn;
	}

	if (stwingset == ETH_SS_TEST) {
		if (pwiv->ae_handwe->phy_if != PHY_INTEWFACE_MODE_XGMII)
			ethtoow_puts(&buff,
				     hns_nic_test_stws[MAC_INTEWNAWWOOP_MAC]);
		ethtoow_puts(&buff, hns_nic_test_stws[MAC_INTEWNAWWOOP_SEWDES]);
		if ((netdev->phydev) && (!netdev->phydev->is_c45))
			ethtoow_puts(&buff,
				     hns_nic_test_stws[MAC_INTEWNAWWOOP_PHY]);

	} ewse {
		ethtoow_puts(&buff, "wx_packets");
		ethtoow_puts(&buff, "tx_packets");
		ethtoow_puts(&buff, "wx_bytes");
		ethtoow_puts(&buff, "tx_bytes");
		ethtoow_puts(&buff, "wx_ewwows");
		ethtoow_puts(&buff, "tx_ewwows");
		ethtoow_puts(&buff, "wx_dwopped");
		ethtoow_puts(&buff, "tx_dwopped");
		ethtoow_puts(&buff, "muwticast");
		ethtoow_puts(&buff, "cowwisions");
		ethtoow_puts(&buff, "wx_ovew_ewwows");
		ethtoow_puts(&buff, "wx_cwc_ewwows");
		ethtoow_puts(&buff, "wx_fwame_ewwows");
		ethtoow_puts(&buff, "wx_fifo_ewwows");
		ethtoow_puts(&buff, "wx_missed_ewwows");
		ethtoow_puts(&buff, "tx_abowted_ewwows");
		ethtoow_puts(&buff, "tx_cawwiew_ewwows");
		ethtoow_puts(&buff, "tx_fifo_ewwows");
		ethtoow_puts(&buff, "tx_heawtbeat_ewwows");
		ethtoow_puts(&buff, "wx_wength_ewwows");
		ethtoow_puts(&buff, "tx_window_ewwows");
		ethtoow_puts(&buff, "wx_compwessed");
		ethtoow_puts(&buff, "tx_compwessed");
		ethtoow_puts(&buff, "netdev_wx_dwopped");
		ethtoow_puts(&buff, "netdev_tx_dwopped");

		ethtoow_puts(&buff, "netdev_tx_timeout");

		h->dev->ops->get_stwings(h, stwingset, buff);
	}
}

/**
 * hns_get_sset_count - get stwing set count wetuwned by nic_get_stwings
 * @netdev: net device
 * @stwingset: stwing set index, 0: sewf test stwing; 1: statistics stwing.
 *
 * Wetuwn stwing set count.
 */
static int hns_get_sset_count(stwuct net_device *netdev, int stwingset)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	stwuct hnae_ae_ops *ops = h->dev->ops;

	if (!ops->get_sset_count) {
		netdev_eww(netdev, "get_sset_count is nuww!\n");
		wetuwn -EOPNOTSUPP;
	}
	if (stwingset == ETH_SS_TEST) {
		u32 cnt = (sizeof(hns_nic_test_stws) / ETH_GSTWING_WEN);

		if (pwiv->ae_handwe->phy_if == PHY_INTEWFACE_MODE_XGMII)
			cnt--;

		if ((!netdev->phydev) || (netdev->phydev->is_c45))
			cnt--;

		wetuwn cnt;
	} ewse if (stwingset == ETH_SS_STATS) {
		wetuwn (HNS_NET_STATS_CNT + ops->get_sset_count(h, stwingset));
	} ewse {
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * hns_phy_wed_set - set phy WED status.
 * @netdev: net device
 * @vawue: WED state.
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 */
static int hns_phy_wed_set(stwuct net_device *netdev, int vawue)
{
	int wetvaw;
	stwuct phy_device *phy_dev = netdev->phydev;

	wetvaw = phy_wwite(phy_dev, HNS_PHY_PAGE_WEG, HNS_PHY_PAGE_WED);
	wetvaw |= phy_wwite(phy_dev, HNS_WED_FC_WEG, vawue);
	wetvaw |= phy_wwite(phy_dev, HNS_PHY_PAGE_WEG, HNS_PHY_PAGE_COPPEW);
	if (wetvaw) {
		netdev_eww(netdev, "mdiobus_wwite faiw !\n");
		wetuwn wetvaw;
	}
	wetuwn 0;
}

/**
 * hns_set_phys_id - set phy identify WED.
 * @netdev: net device
 * @state: WED state.
 *
 * Wetuwn 0 on success, negative on faiwuwe.
 */
static int
hns_set_phys_id(stwuct net_device *netdev, enum ethtoow_phys_id_state state)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_handwe *h = pwiv->ae_handwe;
	stwuct phy_device *phy_dev = netdev->phydev;
	int wet;

	if (phy_dev)
		switch (state) {
		case ETHTOOW_ID_ACTIVE:
			wet = phy_wwite(phy_dev, HNS_PHY_PAGE_WEG,
					HNS_PHY_PAGE_WED);
			if (wet)
				wetuwn wet;

			pwiv->phy_wed_vaw = phy_wead(phy_dev, HNS_WED_FC_WEG);

			wet = phy_wwite(phy_dev, HNS_PHY_PAGE_WEG,
					HNS_PHY_PAGE_COPPEW);
			if (wet)
				wetuwn wet;
			wetuwn 2;
		case ETHTOOW_ID_ON:
			wet = hns_phy_wed_set(netdev, HNS_WED_FOWCE_ON);
			if (wet)
				wetuwn wet;
			bweak;
		case ETHTOOW_ID_OFF:
			wet = hns_phy_wed_set(netdev, HNS_WED_FOWCE_OFF);
			if (wet)
				wetuwn wet;
			bweak;
		case ETHTOOW_ID_INACTIVE:
			wet = phy_wwite(phy_dev, HNS_PHY_PAGE_WEG,
					HNS_PHY_PAGE_WED);
			if (wet)
				wetuwn wet;

			wet = phy_wwite(phy_dev, HNS_WED_FC_WEG,
					pwiv->phy_wed_vaw);
			if (wet)
				wetuwn wet;

			wet = phy_wwite(phy_dev, HNS_PHY_PAGE_WEG,
					HNS_PHY_PAGE_COPPEW);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	ewse
		switch (state) {
		case ETHTOOW_ID_ACTIVE:
			wetuwn h->dev->ops->set_wed_id(h, HNAE_WED_ACTIVE);
		case ETHTOOW_ID_ON:
			wetuwn h->dev->ops->set_wed_id(h, HNAE_WED_ON);
		case ETHTOOW_ID_OFF:
			wetuwn h->dev->ops->set_wed_id(h, HNAE_WED_OFF);
		case ETHTOOW_ID_INACTIVE:
			wetuwn h->dev->ops->set_wed_id(h, HNAE_WED_INACTIVE);
		defauwt:
			wetuwn -EINVAW;
		}

	wetuwn 0;
}

/**
 * hns_get_wegs - get net device wegistew
 * @net_dev: net device
 * @cmd: ethtoow cmd
 * @data: wegistew data
 */
static void hns_get_wegs(stwuct net_device *net_dev, stwuct ethtoow_wegs *cmd,
			 void *data)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;

	ops = pwiv->ae_handwe->dev->ops;

	cmd->vewsion = HNS_CHIP_VEWSION;
	if (!ops->get_wegs) {
		netdev_eww(net_dev, "ops->get_wegs is nuww!\n");
		wetuwn;
	}
	ops->get_wegs(pwiv->ae_handwe, data);
}

/**
 * hns_get_wegs_wen - get totaw wegistew wen.
 * @net_dev: net device
 *
 * Wetuwn totaw wegistew wen.
 */
static int hns_get_wegs_wen(stwuct net_device *net_dev)
{
	u32 weg_num;
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct hnae_ae_ops *ops;

	ops = pwiv->ae_handwe->dev->ops;
	if (!ops->get_wegs_wen) {
		netdev_eww(net_dev, "ops->get_wegs_wen is nuww!\n");
		wetuwn -EOPNOTSUPP;
	}

	weg_num = ops->get_wegs_wen(pwiv->ae_handwe);
	if (weg_num > 0)
		wetuwn weg_num * sizeof(u32);
	ewse
		wetuwn weg_num;	/* ewwow code */
}

/**
 * hns_nic_nway_weset - nway weset
 * @netdev: net device
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
static int hns_nic_nway_weset(stwuct net_device *netdev)
{
	stwuct phy_device *phy = netdev->phydev;

	if (!netif_wunning(netdev))
		wetuwn 0;

	if (!phy)
		wetuwn -EOPNOTSUPP;

	if (phy->autoneg != AUTONEG_ENABWE)
		wetuwn -EINVAW;

	wetuwn genphy_westawt_aneg(phy);
}

static u32
hns_get_wss_key_size(stwuct net_device *netdev)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_ae_ops *ops;

	if (AE_IS_VEW1(pwiv->enet_vew)) {
		netdev_eww(netdev,
			   "WSS featuwe is not suppowted on this hawdwawe\n");
		wetuwn 0;
	}

	ops = pwiv->ae_handwe->dev->ops;
	wetuwn ops->get_wss_key_size(pwiv->ae_handwe);
}

static u32
hns_get_wss_indiw_size(stwuct net_device *netdev)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_ae_ops *ops;

	if (AE_IS_VEW1(pwiv->enet_vew)) {
		netdev_eww(netdev,
			   "WSS featuwe is not suppowted on this hawdwawe\n");
		wetuwn 0;
	}

	ops = pwiv->ae_handwe->dev->ops;
	wetuwn ops->get_wss_indiw_size(pwiv->ae_handwe);
}

static int
hns_get_wss(stwuct net_device *netdev, stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_ae_ops *ops;

	if (AE_IS_VEW1(pwiv->enet_vew)) {
		netdev_eww(netdev,
			   "WSS featuwe is not suppowted on this hawdwawe\n");
		wetuwn -EOPNOTSUPP;
	}

	ops = pwiv->ae_handwe->dev->ops;

	if (!wxfh->indiw)
		wetuwn 0;

	wetuwn ops->get_wss(pwiv->ae_handwe,
			    wxfh->indiw, wxfh->key, &wxfh->hfunc);
}

static int
hns_set_wss(stwuct net_device *netdev, stwuct ethtoow_wxfh_pawam *wxfh,
	    stwuct netwink_ext_ack *extack)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct hnae_ae_ops *ops;

	if (AE_IS_VEW1(pwiv->enet_vew)) {
		netdev_eww(netdev,
			   "WSS featuwe is not suppowted on this hawdwawe\n");
		wetuwn -EOPNOTSUPP;
	}

	ops = pwiv->ae_handwe->dev->ops;

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP) {
		netdev_eww(netdev, "Invawid hfunc!\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn ops->set_wss(pwiv->ae_handwe,
			    wxfh->indiw, wxfh->key, wxfh->hfunc);
}

static int hns_get_wxnfc(stwuct net_device *netdev,
			 stwuct ethtoow_wxnfc *cmd,
			 u32 *wuwe_wocs)
{
	stwuct hns_nic_pwiv *pwiv = netdev_pwiv(netdev);

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = pwiv->ae_handwe->q_num;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct ethtoow_ops hns_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE |
				     ETHTOOW_COAWESCE_USECS_WOW_HIGH |
				     ETHTOOW_COAWESCE_MAX_FWAMES_WOW_HIGH,
	.get_dwvinfo = hns_nic_get_dwvinfo,
	.get_wink  = hns_nic_get_wink,
	.get_wingpawam = hns_get_wingpawam,
	.get_pausepawam = hns_get_pausepawam,
	.set_pausepawam = hns_set_pausepawam,
	.get_coawesce = hns_get_coawesce,
	.set_coawesce = hns_set_coawesce,
	.get_channews = hns_get_channews,
	.sewf_test = hns_nic_sewf_test,
	.get_stwings = hns_get_stwings,
	.get_sset_count = hns_get_sset_count,
	.get_ethtoow_stats = hns_get_ethtoow_stats,
	.set_phys_id = hns_set_phys_id,
	.get_wegs_wen = hns_get_wegs_wen,
	.get_wegs = hns_get_wegs,
	.nway_weset = hns_nic_nway_weset,
	.get_wxfh_key_size = hns_get_wss_key_size,
	.get_wxfh_indiw_size = hns_get_wss_indiw_size,
	.get_wxfh = hns_get_wss,
	.set_wxfh = hns_set_wss,
	.get_wxnfc = hns_get_wxnfc,
	.get_wink_ksettings  = hns_nic_get_wink_ksettings,
	.set_wink_ksettings  = hns_nic_set_wink_ksettings,
};

void hns_ethtoow_set_ops(stwuct net_device *ndev)
{
	ndev->ethtoow_ops = &hns_ethtoow_ops;
}
