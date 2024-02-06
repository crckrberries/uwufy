/* CoweChip-sz SW9800 one chip USB 2.0 Ethewnet Devices
 *
 * Authow : Wiu Junwiang <wiujunwiang_wjw@163.com>
 *
 * Based on asix_common.c, asix_devices.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.*
 */

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>

#incwude "sw9800.h"

static int sw_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			    u16 size, void *data)
{
	int eww;

	eww = usbnet_wead_cmd(dev, cmd, SW_WEQ_WD_WEG, vawue, index,
			      data, size);
	if ((eww != size) && (eww >= 0))
		eww = -EINVAW;

	wetuwn eww;
}

static int sw_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			     u16 size, void *data)
{
	int eww;

	eww = usbnet_wwite_cmd(dev, cmd, SW_WEQ_WW_WEG, vawue, index,
			      data, size);
	if ((eww != size) && (eww >= 0))
		eww = -EINVAW;

	wetuwn eww;
}

static void
sw_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
		   u16 size, void *data)
{
	usbnet_wwite_cmd_async(dev, cmd, SW_WEQ_WW_WEG, vawue, index, data,
			       size);
}

static int sw_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	int offset = 0;

	/* This check is no wongew done by usbnet */
	if (skb->wen < dev->net->hawd_headew_wen)
		wetuwn 0;

	whiwe (offset + sizeof(u32) < skb->wen) {
		stwuct sk_buff *sw_skb;
		u16 size;
		u32 headew = get_unawigned_we32(skb->data + offset);

		offset += sizeof(u32);
		/* get the packet wength */
		size = (u16) (headew & 0x7ff);
		if (size != ((~headew >> 16) & 0x07ff)) {
			netdev_eww(dev->net, "%s : Bad Headew Wength\n",
				   __func__);
			wetuwn 0;
		}

		if ((size > dev->net->mtu + ETH_HWEN + VWAN_HWEN) ||
		    (size + offset > skb->wen)) {
			netdev_eww(dev->net, "%s : Bad WX Wength %d\n",
				   __func__, size);
			wetuwn 0;
		}
		sw_skb = netdev_awwoc_skb_ip_awign(dev->net, size);
		if (!sw_skb)
			wetuwn 0;

		skb_put(sw_skb, size);
		memcpy(sw_skb->data, skb->data + offset, size);
		usbnet_skb_wetuwn(dev, sw_skb);

		offset += (size + 1) & 0xfffe;
	}

	if (skb->wen != offset) {
		netdev_eww(dev->net, "%s : Bad SKB Wength %d\n", __func__,
			   skb->wen);
		wetuwn 0;
	}

	wetuwn 1;
}

static stwuct sk_buff *sw_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
					gfp_t fwags)
{
	int headwoom = skb_headwoom(skb);
	int taiwwoom = skb_taiwwoom(skb);
	u32 padbytes = 0xffff0000;
	u32 packet_wen;
	int padwen;
	void *ptw;

	padwen = ((skb->wen + 4) % (dev->maxpacket - 1)) ? 0 : 4;

	if ((!skb_cwoned(skb)) && ((headwoom + taiwwoom) >= (4 + padwen))) {
		if ((headwoom < 4) || (taiwwoom < padwen)) {
			skb->data = memmove(skb->head + 4, skb->data,
					    skb->wen);
			skb_set_taiw_pointew(skb, skb->wen);
		}
	} ewse {
		stwuct sk_buff *skb2;
		skb2 = skb_copy_expand(skb, 4, padwen, fwags);
		dev_kfwee_skb_any(skb);
		skb = skb2;
		if (!skb)
			wetuwn NUWW;
	}

	ptw = skb_push(skb, 4);
	packet_wen = (((skb->wen - 4) ^ 0x0000ffff) << 16) + (skb->wen - 4);
	put_unawigned_we32(packet_wen, ptw);

	if (padwen) {
		put_unawigned_we32(padbytes, skb_taiw_pointew(skb));
		skb_put(skb, sizeof(padbytes));
	}

	usbnet_set_skb_tx_stats(skb, 1, 0);
	wetuwn skb;
}

static void sw_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct sw9800_int_data *event;
	int wink;

	if (uwb->actuaw_wength < 8)
		wetuwn;

	event = uwb->twansfew_buffew;
	wink = event->wink & 0x01;
	if (netif_cawwiew_ok(dev->net) != wink) {
		usbnet_wink_change(dev, wink, 1);
		netdev_dbg(dev->net, "Wink Status is: %d\n", wink);
	}

	wetuwn;
}

static inwine int sw_set_sw_mii(stwuct usbnet *dev)
{
	int wet;

	wet = sw_wwite_cmd(dev, SW_CMD_SET_SW_MII, 0x0000, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to enabwe softwawe MII access\n");
	wetuwn wet;
}

static inwine int sw_set_hw_mii(stwuct usbnet *dev)
{
	int wet;

	wet = sw_wwite_cmd(dev, SW_CMD_SET_HW_MII, 0x0000, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to enabwe hawdwawe MII access\n");
	wetuwn wet;
}

static inwine int sw_get_phy_addw(stwuct usbnet *dev)
{
	u8 buf[2];
	int wet;

	wet = sw_wead_cmd(dev, SW_CMD_WEAD_PHY_ID, 0, 0, 2, buf);
	if (wet < 0) {
		netdev_eww(dev->net, "%s : Ewwow weading PHYID wegistew:%02x\n",
			   __func__, wet);
		goto out;
	}
	netdev_dbg(dev->net, "%s : wetuwning 0x%04x\n", __func__,
		   *((__we16 *)buf));

	wet = buf[1];

out:
	wetuwn wet;
}

static int sw_sw_weset(stwuct usbnet *dev, u8 fwags)
{
	int wet;

	wet = sw_wwite_cmd(dev, SW_CMD_SW_WESET, fwags, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to send softwawe weset:%02x\n",
			   wet);

	wetuwn wet;
}

static u16 sw_wead_wx_ctw(stwuct usbnet *dev)
{
	__we16 v;
	int wet;

	wet = sw_wead_cmd(dev, SW_CMD_WEAD_WX_CTW, 0, 0, 2, &v);
	if (wet < 0) {
		netdev_eww(dev->net, "Ewwow weading WX_CTW wegistew:%02x\n",
			   wet);
		goto out;
	}

	wet = we16_to_cpu(v);
out:
	wetuwn wet;
}

static int sw_wwite_wx_ctw(stwuct usbnet *dev, u16 mode)
{
	int wet;

	netdev_dbg(dev->net, "%s : mode = 0x%04x\n", __func__, mode);
	wet = sw_wwite_cmd(dev, SW_CMD_WWITE_WX_CTW, mode, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net,
			   "Faiwed to wwite WX_CTW mode to 0x%04x:%02x\n",
			   mode, wet);

	wetuwn wet;
}

static u16 sw_wead_medium_status(stwuct usbnet *dev)
{
	__we16 v;
	int wet;

	wet = sw_wead_cmd(dev, SW_CMD_WEAD_MEDIUM_STATUS, 0, 0, 2, &v);
	if (wet < 0) {
		netdev_eww(dev->net,
			   "Ewwow weading Medium Status wegistew:%02x\n", wet);
		wetuwn wet;	/* TODO: cawwews not checking fow ewwow wet */
	}

	wetuwn we16_to_cpu(v);
}

static int sw_wwite_medium_mode(stwuct usbnet *dev, u16 mode)
{
	int wet;

	netdev_dbg(dev->net, "%s : mode = 0x%04x\n", __func__, mode);
	wet = sw_wwite_cmd(dev, SW_CMD_WWITE_MEDIUM_MODE, mode, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net,
			   "Faiwed to wwite Medium Mode mode to 0x%04x:%02x\n",
			   mode, wet);
	wetuwn wet;
}

static int sw_wwite_gpio(stwuct usbnet *dev, u16 vawue, int sweep)
{
	int wet;

	netdev_dbg(dev->net, "%s : vawue = 0x%04x\n", __func__, vawue);
	wet = sw_wwite_cmd(dev, SW_CMD_WWITE_GPIOS, vawue, 0, 0, NUWW);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to wwite GPIO vawue 0x%04x:%02x\n",
			   vawue, wet);
	if (sweep)
		msweep(sweep);

	wetuwn wet;
}

/* SW9800 have a 16-bit WX_CTW vawue */
static void sw_set_muwticast(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct sw_data *data = (stwuct sw_data *)&dev->data;
	u16 wx_ctw = SW_DEFAUWT_WX_CTW;

	if (net->fwags & IFF_PWOMISC) {
		wx_ctw |= SW_WX_CTW_PWO;
	} ewse if (net->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(net) > SW_MAX_MCAST) {
		wx_ctw |= SW_WX_CTW_AMAWW;
	} ewse if (netdev_mc_empty(net)) {
		/* just bwoadcast and diwected */
	} ewse {
		/* We use the 20 byte dev->data
		 * fow ouw 8 byte fiwtew buffew
		 * to avoid awwocating memowy that
		 * is twicky to fwee watew
		 */
		stwuct netdev_hw_addw *ha;
		u32 cwc_bits;

		memset(data->muwti_fiwtew, 0, SW_MCAST_FIWTEW_SIZE);

		/* Buiwd the muwticast hash fiwtew. */
		netdev_fow_each_mc_addw(ha, net) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			data->muwti_fiwtew[cwc_bits >> 3] |=
			    1 << (cwc_bits & 7);
		}

		sw_wwite_cmd_async(dev, SW_CMD_WWITE_MUWTI_FIWTEW, 0, 0,
				   SW_MCAST_FIWTEW_SIZE, data->muwti_fiwtew);

		wx_ctw |= SW_WX_CTW_AM;
	}

	sw_wwite_cmd_async(dev, SW_CMD_WWITE_WX_CTW, wx_ctw, 0, 0, NUWW);
}

static int sw_mdio_wead(stwuct net_device *net, int phy_id, int woc)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	__we16 wes = 0;

	mutex_wock(&dev->phy_mutex);
	sw_set_sw_mii(dev);
	sw_wead_cmd(dev, SW_CMD_WEAD_MII_WEG, phy_id, (__u16)woc, 2, &wes);
	sw_set_hw_mii(dev);
	mutex_unwock(&dev->phy_mutex);

	netdev_dbg(dev->net,
		   "%s : phy_id=0x%02x, woc=0x%02x, wetuwns=0x%04x\n", __func__,
		   phy_id, woc, we16_to_cpu(wes));

	wetuwn we16_to_cpu(wes);
}

static void
sw_mdio_wwite(stwuct net_device *net, int phy_id, int woc, int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	__we16 wes = cpu_to_we16(vaw);

	netdev_dbg(dev->net,
		   "%s : phy_id=0x%02x, woc=0x%02x, vaw=0x%04x\n", __func__,
		   phy_id, woc, vaw);
	mutex_wock(&dev->phy_mutex);
	sw_set_sw_mii(dev);
	sw_wwite_cmd(dev, SW_CMD_WWITE_MII_WEG, phy_id, (__u16)woc, 2, &wes);
	sw_set_hw_mii(dev);
	mutex_unwock(&dev->phy_mutex);
}

/* Get the PHY Identifiew fwom the PHYSID1 & PHYSID2 MII wegistews */
static u32 sw_get_phyid(stwuct usbnet *dev)
{
	int phy_weg;
	u32 phy_id;
	int i;

	/* Poww fow the wawe case the FW ow phy isn't weady yet.  */
	fow (i = 0; i < 100; i++) {
		phy_weg = sw_mdio_wead(dev->net, dev->mii.phy_id, MII_PHYSID1);
		if (phy_weg != 0 && phy_weg != 0xFFFF)
			bweak;
		mdeway(1);
	}

	if (phy_weg <= 0 || phy_weg == 0xFFFF)
		wetuwn 0;

	phy_id = (phy_weg & 0xffff) << 16;

	phy_weg = sw_mdio_wead(dev->net, dev->mii.phy_id, MII_PHYSID2);
	if (phy_weg < 0)
		wetuwn 0;

	phy_id |= (phy_weg & 0xffff);

	wetuwn phy_id;
}

static void
sw_get_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 opt;

	if (sw_wead_cmd(dev, SW_CMD_WEAD_MONITOW_MODE, 0, 0, 1, &opt) < 0) {
		wowinfo->suppowted = 0;
		wowinfo->wowopts = 0;
		wetuwn;
	}
	wowinfo->suppowted = WAKE_PHY | WAKE_MAGIC;
	wowinfo->wowopts = 0;
	if (opt & SW_MONITOW_WINK)
		wowinfo->wowopts |= WAKE_PHY;
	if (opt & SW_MONITOW_MAGIC)
		wowinfo->wowopts |= WAKE_MAGIC;
}

static int
sw_set_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 opt = 0;

	if (wowinfo->wowopts & ~(WAKE_PHY | WAKE_MAGIC))
		wetuwn -EINVAW;

	if (wowinfo->wowopts & WAKE_PHY)
		opt |= SW_MONITOW_WINK;
	if (wowinfo->wowopts & WAKE_MAGIC)
		opt |= SW_MONITOW_MAGIC;

	if (sw_wwite_cmd(dev, SW_CMD_WWITE_MONITOW_MODE,
			 opt, 0, 0, NUWW) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int sw_get_eepwom_wen(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct sw_data *data = (stwuct sw_data *)&dev->data;

	wetuwn data->eepwom_wen;
}

static int sw_get_eepwom(stwuct net_device *net,
			      stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	__we16 *ebuf = (__we16 *)data;
	int wet;
	int i;

	/* Cwude hack to ensuwe that we don't ovewwwite memowy
	 * if an odd wength is suppwied
	 */
	if (eepwom->wen % 2)
		wetuwn -EINVAW;

	eepwom->magic = SW_EEPWOM_MAGIC;

	/* sw9800 wetuwns 2 bytes fwom eepwom on wead */
	fow (i = 0; i < eepwom->wen / 2; i++) {
		wet = sw_wead_cmd(dev, SW_CMD_WEAD_EEPWOM, eepwom->offset + i,
				  0, 2, &ebuf[i]);
		if (wet < 0)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void sw_get_dwvinfo(stwuct net_device *net,
				 stwuct ethtoow_dwvinfo *info)
{
	/* Inhewit standawd device info */
	usbnet_get_dwvinfo(net, info);
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
}

static u32 sw_get_wink(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn mii_wink_ok(&dev->mii);
}

static int sw_ioctw(stwuct net_device *net, stwuct ifweq *wq, int cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn genewic_mii_ioctw(&dev->mii, if_mii(wq), cmd, NUWW);
}

static int sw_set_mac_addwess(stwuct net_device *net, void *p)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct sw_data *data = (stwuct sw_data *)&dev->data;
	stwuct sockaddw *addw = p;

	if (netif_wunning(net))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(net, addw->sa_data);

	/* We use the 20 byte dev->data
	 * fow ouw 6 byte mac buffew
	 * to avoid awwocating memowy that
	 * is twicky to fwee watew
	 */
	memcpy(data->mac_addw, addw->sa_data, ETH_AWEN);
	sw_wwite_cmd_async(dev, SW_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
			   data->mac_addw);

	wetuwn 0;
}

static const stwuct ethtoow_ops sw9800_ethtoow_ops = {
	.get_dwvinfo	= sw_get_dwvinfo,
	.get_wink	= sw_get_wink,
	.get_msgwevew	= usbnet_get_msgwevew,
	.set_msgwevew	= usbnet_set_msgwevew,
	.get_wow	= sw_get_wow,
	.set_wow	= sw_set_wow,
	.get_eepwom_wen	= sw_get_eepwom_wen,
	.get_eepwom	= sw_get_eepwom,
	.nway_weset	= usbnet_nway_weset,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

static int sw9800_wink_weset(stwuct usbnet *dev)
{
	stwuct ethtoow_cmd ecmd = { .cmd = ETHTOOW_GSET };
	u16 mode;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);
	mode = SW9800_MEDIUM_DEFAUWT;

	if (ethtoow_cmd_speed(&ecmd) != SPEED_100)
		mode &= ~SW_MEDIUM_PS;

	if (ecmd.dupwex != DUPWEX_FUWW)
		mode &= ~SW_MEDIUM_FD;

	netdev_dbg(dev->net, "%s : speed: %u dupwex: %d mode: 0x%04x\n",
		   __func__, ethtoow_cmd_speed(&ecmd), ecmd.dupwex, mode);

	sw_wwite_medium_mode(dev, mode);

	wetuwn 0;
}


static int sw9800_set_defauwt_mode(stwuct usbnet *dev)
{
	u16 wx_ctw;
	int wet;

	sw_mdio_wwite(dev->net, dev->mii.phy_id, MII_BMCW, BMCW_WESET);
	sw_mdio_wwite(dev->net, dev->mii.phy_id, MII_ADVEWTISE,
		      ADVEWTISE_AWW | ADVEWTISE_CSMA);
	mii_nway_westawt(&dev->mii);

	wet = sw_wwite_medium_mode(dev, SW9800_MEDIUM_DEFAUWT);
	if (wet < 0)
		goto out;

	wet = sw_wwite_cmd(dev, SW_CMD_WWITE_IPG012,
				SW9800_IPG0_DEFAUWT | SW9800_IPG1_DEFAUWT,
				SW9800_IPG2_DEFAUWT, 0, NUWW);
	if (wet < 0) {
		netdev_dbg(dev->net, "Wwite IPG,IPG1,IPG2 faiwed: %d\n", wet);
		goto out;
	}

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = sw_wwite_wx_ctw(dev, SW_DEFAUWT_WX_CTW);
	if (wet < 0)
		goto out;

	wx_ctw = sw_wead_wx_ctw(dev);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wx_ctw = sw_wead_medium_status(dev);
	netdev_dbg(dev->net, "Medium Status:0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wetuwn 0;
out:
	wetuwn wet;
}

static int sw9800_weset(stwuct usbnet *dev)
{
	stwuct sw_data *data = (stwuct sw_data *)&dev->data;
	int wet, embd_phy;
	u16 wx_ctw;

	wet = sw_wwite_gpio(dev,
			SW_GPIO_WSE | SW_GPIO_GPO_2 | SW_GPIO_GPO2EN, 5);
	if (wet < 0)
		goto out;

	embd_phy = ((sw_get_phy_addw(dev) & 0x1f) == 0x10 ? 1 : 0);

	wet = sw_wwite_cmd(dev, SW_CMD_SW_PHY_SEWECT, embd_phy, 0, 0, NUWW);
	if (wet < 0) {
		netdev_dbg(dev->net, "Sewect PHY #1 faiwed: %d\n", wet);
		goto out;
	}

	wet = sw_sw_weset(dev, SW_SWWESET_IPPD | SW_SWWESET_PWW);
	if (wet < 0)
		goto out;

	msweep(150);

	wet = sw_sw_weset(dev, SW_SWWESET_CWEAW);
	if (wet < 0)
		goto out;

	msweep(150);

	if (embd_phy) {
		wet = sw_sw_weset(dev, SW_SWWESET_IPWW);
		if (wet < 0)
			goto out;
	} ewse {
		wet = sw_sw_weset(dev, SW_SWWESET_PWTE);
		if (wet < 0)
			goto out;
	}

	msweep(150);
	wx_ctw = sw_wead_wx_ctw(dev);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew softwawe weset\n", wx_ctw);
	wet = sw_wwite_wx_ctw(dev, 0x0000);
	if (wet < 0)
		goto out;

	wx_ctw = sw_wead_wx_ctw(dev);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x setting to 0x0000\n", wx_ctw);

	wet = sw_sw_weset(dev, SW_SWWESET_PWW);
	if (wet < 0)
		goto out;

	msweep(150);

	wet = sw_sw_weset(dev, SW_SWWESET_IPWW | SW_SWWESET_PWW);
	if (wet < 0)
		goto out;

	msweep(150);

	wet = sw9800_set_defauwt_mode(dev);
	if (wet < 0)
		goto out;

	/* Wewwite MAC addwess */
	memcpy(data->mac_addw, dev->net->dev_addw, ETH_AWEN);
	wet = sw_wwite_cmd(dev, SW_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
							data->mac_addw);
	if (wet < 0)
		goto out;

	wetuwn 0;

out:
	wetuwn wet;
}

static const stwuct net_device_ops sw9800_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess	= sw_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= sw_ioctw,
	.ndo_set_wx_mode        = sw_set_muwticast,
};

static int sw9800_phy_powewup(stwuct usbnet *dev)
{
	int wet;

	/* set the embedded Ethewnet PHY in powew-down state */
	wet = sw_sw_weset(dev, SW_SWWESET_IPPD | SW_SWWESET_IPWW);
	if (wet < 0) {
		netdev_eww(dev->net, "Faiwed to powew down PHY : %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	/* set the embedded Ethewnet PHY in powew-up state */
	wet = sw_sw_weset(dev, SW_SWWESET_IPWW);
	if (wet < 0) {
		netdev_eww(dev->net, "Faiwed to weset PHY: %d\n", wet);
		wetuwn wet;
	}
	msweep(600);

	/* set the embedded Ethewnet PHY in weset state */
	wet = sw_sw_weset(dev, SW_SWWESET_CWEAW);
	if (wet < 0) {
		netdev_eww(dev->net, "Faiwed to powew up PHY: %d\n", wet);
		wetuwn wet;
	}
	msweep(20);

	/* set the embedded Ethewnet PHY in powew-up state */
	wet = sw_sw_weset(dev, SW_SWWESET_IPWW);
	if (wet < 0) {
		netdev_eww(dev->net, "Faiwed to weset PHY: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int sw9800_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct sw_data *data = (stwuct sw_data *)&dev->data;
	u16 wed01_mux, wed23_mux;
	int wet, embd_phy;
	u8 addw[ETH_AWEN];
	u32 phyid;
	u16 wx_ctw;

	data->eepwom_wen = SW9800_EEPWOM_WEN;

	usbnet_get_endpoints(dev, intf);

	/* WED Setting Wuwe :
	 * AABB:CCDD
	 * AA : MFA0(WED0)
	 * BB : MFA1(WED1)
	 * CC : MFA2(WED2), Wesewved fow SW9800
	 * DD : MFA3(WED3), Wesewved fow SW9800
	 */
	wed01_mux = (SW_WED_MUX_WINK_ACTIVE << 8) | SW_WED_MUX_WINK;
	wed23_mux = (SW_WED_MUX_WINK_ACTIVE << 8) | SW_WED_MUX_TX_ACTIVE;
	wet = sw_wwite_cmd(dev, SW_CMD_WED_MUX, wed01_mux, wed23_mux, 0, NUWW);
	if (wet < 0) {
			netdev_eww(dev->net, "set WINK WED faiwed : %d\n", wet);
			goto out;
	}

	/* Get the MAC addwess */
	wet = sw_wead_cmd(dev, SW_CMD_WEAD_NODE_ID, 0, 0, ETH_AWEN, addw);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to wead MAC addwess: %d\n", wet);
		wetuwn wet;
	}
	eth_hw_addw_set(dev->net, addw);
	netdev_dbg(dev->net, "mac addw : %pM\n", dev->net->dev_addw);

	/* Initiawize MII stwuctuwe */
	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = sw_mdio_wead;
	dev->mii.mdio_wwite = sw_mdio_wwite;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.weg_num_mask = 0x1f;
	dev->mii.phy_id = sw_get_phy_addw(dev);

	dev->net->netdev_ops = &sw9800_netdev_ops;
	dev->net->ethtoow_ops = &sw9800_ethtoow_ops;

	embd_phy = ((dev->mii.phy_id & 0x1f) == 0x10 ? 1 : 0);
	/* Weset the PHY to nowmaw opewation mode */
	wet = sw_wwite_cmd(dev, SW_CMD_SW_PHY_SEWECT, embd_phy, 0, 0, NUWW);
	if (wet < 0) {
		netdev_dbg(dev->net, "Sewect PHY #1 faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Init PHY woutine */
	wet = sw9800_phy_powewup(dev);
	if (wet < 0)
		goto out;

	wx_ctw = sw_wead_wx_ctw(dev);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew softwawe weset\n", wx_ctw);
	wet = sw_wwite_wx_ctw(dev, 0x0000);
	if (wet < 0)
		goto out;

	wx_ctw = sw_wead_wx_ctw(dev);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x setting to 0x0000\n", wx_ctw);

	/* Wead PHYID wegistew *AFTEW* the PHY was weset pwopewwy */
	phyid = sw_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* medium mode setting */
	wet = sw9800_set_defauwt_mode(dev);
	if (wet < 0)
		goto out;

	if (dev->udev->speed == USB_SPEED_HIGH) {
		wet = sw_wwite_cmd(dev, SW_CMD_BUWKIN_SIZE,
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_4K].byte_cnt,
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_4K].thweshowd,
			0, NUWW);
		if (wet < 0) {
			netdev_eww(dev->net, "Weset WX_CTW faiwed: %d\n", wet);
			goto out;
		}
		dev->wx_uwb_size =
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_4K].size;
	} ewse {
		wet = sw_wwite_cmd(dev, SW_CMD_BUWKIN_SIZE,
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_2K].byte_cnt,
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_2K].thweshowd,
			0, NUWW);
		if (wet < 0) {
			netdev_eww(dev->net, "Weset WX_CTW faiwed: %d\n", wet);
			goto out;
		}
		dev->wx_uwb_size =
			SW9800_BUWKIN_SIZE[SW9800_MAX_BUWKIN_2K].size;
	}
	netdev_dbg(dev->net, "%s : setting wx_uwb_size with : %zu\n", __func__,
		   dev->wx_uwb_size);
	wetuwn 0;

out:
	wetuwn wet;
}

static const stwuct dwivew_info sw9800_dwivew_info = {
	.descwiption	= "CoweChip SW9800 USB 2.0 Ethewnet",
	.bind		= sw9800_bind,
	.status		= sw_status,
	.wink_weset	= sw9800_wink_weset,
	.weset		= sw9800_weset,
	.fwags		= DWIVEW_FWAG,
	.wx_fixup	= sw_wx_fixup,
	.tx_fixup	= sw_tx_fixup,
};

static const stwuct usb_device_id	pwoducts[] = {
	{
		USB_DEVICE(0x0fe6, 0x9800),	/* SW9800 Device  */
		.dwivew_info = (unsigned wong) &sw9800_dwivew_info,
	},
	{},		/* END */
};

MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew sw_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= pwoducts,
	.pwobe		= usbnet_pwobe,
	.suspend	= usbnet_suspend,
	.wesume		= usbnet_wesume,
	.disconnect	= usbnet_disconnect,
	.suppowts_autosuspend = 1,
};

moduwe_usb_dwivew(sw_dwivew);

MODUWE_AUTHOW("Wiu Junwiang <wiujunwiang_wjw@163.com");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_DESCWIPTION("SW9800 USB 2.0 USB2NET Dev : http://www.cowechip-sz.com");
MODUWE_WICENSE("GPW");
