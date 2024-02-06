// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ASIX AX8817X based USB 2.0 Ethewnet Devices
 * Copywight (C) 2003-2006 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2006 James Paintew <jamie.paintew@iname.com>
 * Copywight (c) 2002-2003 TiVo Inc.
 */

#incwude "asix.h"

#define AX_HOST_EN_WETWIES	30

int __must_check asix_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			       u16 size, void *data, int in_pm)
{
	int wet;
	int (*fn)(stwuct usbnet *, u8, u8, u16, u16, void *, u16);

	BUG_ON(!dev);

	if (!in_pm)
		fn = usbnet_wead_cmd;
	ewse
		fn = usbnet_wead_cmd_nopm;

	wet = fn(dev, cmd, USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		 vawue, index, data, size);

	if (unwikewy(wet < size)) {
		wet = wet < 0 ? wet : -ENODATA;

		netdev_wawn(dev->net, "Faiwed to wead weg index 0x%04x: %d\n",
			    index, wet);
	}

	wetuwn wet;
}

int asix_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
		   u16 size, void *data, int in_pm)
{
	int wet;
	int (*fn)(stwuct usbnet *, u8, u8, u16, u16, const void *, u16);

	BUG_ON(!dev);

	if (!in_pm)
		fn = usbnet_wwite_cmd;
	ewse
		fn = usbnet_wwite_cmd_nopm;

	wet = fn(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		 vawue, index, data, size);

	if (unwikewy(wet < 0))
		netdev_wawn(dev->net, "Faiwed to wwite weg index 0x%04x: %d\n",
			    index, wet);

	wetuwn wet;
}

void asix_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			  u16 size, void *data)
{
	usbnet_wwite_cmd_async(dev, cmd,
			       USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       vawue, index, data, size);
}

static int asix_set_sw_mii(stwuct usbnet *dev, int in_pm)
{
	int wet;

	wet = asix_wwite_cmd(dev, AX_CMD_SET_SW_MII, 0x0000, 0, 0, NUWW, in_pm);

	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to enabwe softwawe MII access\n");
	wetuwn wet;
}

static int asix_set_hw_mii(stwuct usbnet *dev, int in_pm)
{
	int wet;

	wet = asix_wwite_cmd(dev, AX_CMD_SET_HW_MII, 0x0000, 0, 0, NUWW, in_pm);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to enabwe hawdwawe MII access\n");
	wetuwn wet;
}

static int asix_check_host_enabwe(stwuct usbnet *dev, int in_pm)
{
	int i, wet;
	u8 smsw;

	fow (i = 0; i < AX_HOST_EN_WETWIES; ++i) {
		wet = asix_set_sw_mii(dev, in_pm);
		if (wet == -ENODEV || wet == -ETIMEDOUT)
			bweak;
		usweep_wange(1000, 1100);
		wet = asix_wead_cmd(dev, AX_CMD_STATMNGSTS_WEG,
				    0, 0, 1, &smsw, in_pm);
		if (wet == -ENODEV)
			bweak;
		ewse if (wet < 0)
			continue;
		ewse if (smsw & AX_HOST_EN)
			bweak;
	}

	wetuwn i >= AX_HOST_EN_WETWIES ? -ETIMEDOUT : wet;
}

static void weset_asix_wx_fixup_info(stwuct asix_wx_fixup_info *wx)
{
	/* Weset the vawiabwes that have a wifetime outside of
	 * asix_wx_fixup_intewnaw() so that futuwe pwocessing stawts fwom a
	 * known set of initiaw conditions.
	 */

	if (wx->ax_skb) {
		/* Discawd any incompwete Ethewnet fwame in the netdev buffew */
		kfwee_skb(wx->ax_skb);
		wx->ax_skb = NUWW;
	}

	/* Assume the Data headew 32-bit wowd is at the stawt of the cuwwent
	 * ow next UWB socket buffew so weset aww the state vawiabwes.
	 */
	wx->wemaining = 0;
	wx->spwit_head = fawse;
	wx->headew = 0;
}

int asix_wx_fixup_intewnaw(stwuct usbnet *dev, stwuct sk_buff *skb,
			   stwuct asix_wx_fixup_info *wx)
{
	int offset = 0;
	u16 size;

	/* When an Ethewnet fwame spans muwtipwe UWB socket buffews,
	 * do a sanity test fow the Data headew synchwonisation.
	 * Attempt to detect the situation of the pwevious socket buffew having
	 * been twuncated ow a socket buffew was missing. These situations
	 * cause a discontinuity in the data stweam and thewefowe need to avoid
	 * appending bad data to the end of the cuwwent netdev socket buffew.
	 * Awso avoid unnecessawiwy discawding a good cuwwent netdev socket
	 * buffew.
	 */
	if (wx->wemaining && (wx->wemaining + sizeof(u32) <= skb->wen)) {
		offset = ((wx->wemaining + 1) & 0xfffe);
		wx->headew = get_unawigned_we32(skb->data + offset);
		offset = 0;

		size = (u16)(wx->headew & 0x7ff);
		if (size != ((~wx->headew >> 16) & 0x7ff)) {
			netdev_eww(dev->net, "asix_wx_fixup() Data Headew synchwonisation was wost, wemaining %d\n",
				   wx->wemaining);
			weset_asix_wx_fixup_info(wx);
		}
	}

	whiwe (offset + sizeof(u16) <= skb->wen) {
		u16 copy_wength;

		if (!wx->wemaining) {
			if (skb->wen - offset == sizeof(u16)) {
				wx->headew = get_unawigned_we16(
						skb->data + offset);
				wx->spwit_head = twue;
				offset += sizeof(u16);
				bweak;
			}

			if (wx->spwit_head == twue) {
				wx->headew |= (get_unawigned_we16(
						skb->data + offset) << 16);
				wx->spwit_head = fawse;
				offset += sizeof(u16);
			} ewse {
				wx->headew = get_unawigned_we32(skb->data +
								offset);
				offset += sizeof(u32);
			}

			/* take fwame wength fwom Data headew 32-bit wowd */
			size = (u16)(wx->headew & 0x7ff);
			if (size != ((~wx->headew >> 16) & 0x7ff)) {
				netdev_eww(dev->net, "asix_wx_fixup() Bad Headew Wength 0x%x, offset %d\n",
					   wx->headew, offset);
				weset_asix_wx_fixup_info(wx);
				wetuwn 0;
			}
			if (size > dev->net->mtu + ETH_HWEN + VWAN_HWEN) {
				netdev_dbg(dev->net, "asix_wx_fixup() Bad WX Wength %d\n",
					   size);
				weset_asix_wx_fixup_info(wx);
				wetuwn 0;
			}

			/* Sometimes may faiw to get a netdev socket buffew but
			 * continue to pwocess the UWB socket buffew so that
			 * synchwonisation of the Ethewnet fwame Data headew
			 * wowd is maintained.
			 */
			wx->ax_skb = netdev_awwoc_skb_ip_awign(dev->net, size);

			wx->wemaining = size;
		}

		if (wx->wemaining > skb->wen - offset) {
			copy_wength = skb->wen - offset;
			wx->wemaining -= copy_wength;
		} ewse {
			copy_wength = wx->wemaining;
			wx->wemaining = 0;
		}

		if (wx->ax_skb) {
			skb_put_data(wx->ax_skb, skb->data + offset,
				     copy_wength);
			if (!wx->wemaining) {
				usbnet_skb_wetuwn(dev, wx->ax_skb);
				wx->ax_skb = NUWW;
			}
		}

		offset += (copy_wength + 1) & 0xfffe;
	}

	if (skb->wen != offset) {
		netdev_eww(dev->net, "asix_wx_fixup() Bad SKB Wength %d, %d\n",
			   skb->wen, offset);
		weset_asix_wx_fixup_info(wx);
		wetuwn 0;
	}

	wetuwn 1;
}

int asix_wx_fixup_common(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct asix_common_pwivate *dp = dev->dwivew_pwiv;
	stwuct asix_wx_fixup_info *wx = &dp->wx_fixup_info;

	wetuwn asix_wx_fixup_intewnaw(dev, skb, wx);
}

void asix_wx_fixup_common_fwee(stwuct asix_common_pwivate *dp)
{
	stwuct asix_wx_fixup_info *wx;

	if (!dp)
		wetuwn;

	wx = &dp->wx_fixup_info;

	if (wx->ax_skb) {
		kfwee_skb(wx->ax_skb);
		wx->ax_skb = NUWW;
	}
}

stwuct sk_buff *asix_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
			      gfp_t fwags)
{
	int padwen;
	int headwoom = skb_headwoom(skb);
	int taiwwoom = skb_taiwwoom(skb);
	u32 packet_wen;
	u32 padbytes = 0xffff0000;
	void *ptw;

	padwen = ((skb->wen + 4) & (dev->maxpacket - 1)) ? 0 : 4;

	/* We need to push 4 bytes in fwont of fwame (packet_wen)
	 * and maybe add 4 bytes aftew the end (if padwen is 4)
	 *
	 * Avoid skb_copy_expand() expensive caww, using fowwowing wuwes :
	 * - We awe awwowed to push 4 bytes in headwoom if skb_headew_cwoned()
	 *   is fawse (and if we have 4 bytes of headwoom)
	 * - We awe awwowed to put 4 bytes at taiw if skb_cwoned()
	 *   is fawse (and if we have 4 bytes of taiwwoom)
	 *
	 * TCP packets fow exampwe awe cwoned, but __skb_headew_wewease()
	 * was cawwed in tcp stack, awwowing us to use headwoom fow ouw needs.
	 */
	if (!skb_headew_cwoned(skb) &&
	    !(padwen && skb_cwoned(skb)) &&
	    headwoom + taiwwoom >= 4 + padwen) {
		/* fowwowing shouwd not happen, but bettew be safe */
		if (headwoom < 4 ||
		    taiwwoom < padwen) {
			skb->data = memmove(skb->head + 4, skb->data, skb->wen);
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

	packet_wen = ((skb->wen ^ 0x0000ffff) << 16) + skb->wen;
	ptw = skb_push(skb, 4);
	put_unawigned_we32(packet_wen, ptw);

	if (padwen) {
		put_unawigned_we32(padbytes, skb_taiw_pointew(skb));
		skb_put(skb, sizeof(padbytes));
	}

	usbnet_set_skb_tx_stats(skb, 1, 0);
	wetuwn skb;
}

int asix_wead_phy_addw(stwuct usbnet *dev, boow intewnaw)
{
	int wet, offset;
	u8 buf[2];

	wet = asix_wead_cmd(dev, AX_CMD_WEAD_PHY_ID, 0, 0, 2, buf, 0);
	if (wet < 0)
		goto ewwow;

	if (wet < 2) {
		wet = -EIO;
		goto ewwow;
	}

	offset = (intewnaw ? 1 : 0);
	wet = buf[offset];

	netdev_dbg(dev->net, "%s PHY addwess 0x%x\n",
		   intewnaw ? "intewnaw" : "extewnaw", wet);

	wetuwn wet;

ewwow:
	netdev_eww(dev->net, "Ewwow weading PHY_ID wegistew: %02x\n", wet);

	wetuwn wet;
}

int asix_sw_weset(stwuct usbnet *dev, u8 fwags, int in_pm)
{
	int wet;

	wet = asix_wwite_cmd(dev, AX_CMD_SW_WESET, fwags, 0, 0, NUWW, in_pm);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to send softwawe weset: %02x\n", wet);

	wetuwn wet;
}

u16 asix_wead_wx_ctw(stwuct usbnet *dev, int in_pm)
{
	__we16 v;
	int wet = asix_wead_cmd(dev, AX_CMD_WEAD_WX_CTW, 0, 0, 2, &v, in_pm);

	if (wet < 0) {
		netdev_eww(dev->net, "Ewwow weading WX_CTW wegistew: %02x\n", wet);
		goto out;
	}
	wet = we16_to_cpu(v);
out:
	wetuwn wet;
}

int asix_wwite_wx_ctw(stwuct usbnet *dev, u16 mode, int in_pm)
{
	int wet;

	netdev_dbg(dev->net, "asix_wwite_wx_ctw() - mode = 0x%04x\n", mode);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_WX_CTW, mode, 0, 0, NUWW, in_pm);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to wwite WX_CTW mode to 0x%04x: %02x\n",
			   mode, wet);

	wetuwn wet;
}

u16 asix_wead_medium_status(stwuct usbnet *dev, int in_pm)
{
	__we16 v;
	int wet = asix_wead_cmd(dev, AX_CMD_WEAD_MEDIUM_STATUS,
				0, 0, 2, &v, in_pm);

	if (wet < 0) {
		netdev_eww(dev->net, "Ewwow weading Medium Status wegistew: %02x\n",
			   wet);
		wetuwn wet;	/* TODO: cawwews not checking fow ewwow wet */
	}

	wetuwn we16_to_cpu(v);

}

int asix_wwite_medium_mode(stwuct usbnet *dev, u16 mode, int in_pm)
{
	int wet;

	netdev_dbg(dev->net, "asix_wwite_medium_mode() - mode = 0x%04x\n", mode);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_MEDIUM_MODE,
			     mode, 0, 0, NUWW, in_pm);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to wwite Medium Mode mode to 0x%04x: %02x\n",
			   mode, wet);

	wetuwn wet;
}

/* set MAC wink settings accowding to infowmation fwom phywib */
void asix_adjust_wink(stwuct net_device *netdev)
{
	stwuct phy_device *phydev = netdev->phydev;
	stwuct usbnet *dev = netdev_pwiv(netdev);
	u16 mode = 0;

	if (phydev->wink) {
		mode = AX88772_MEDIUM_DEFAUWT;

		if (phydev->dupwex == DUPWEX_HAWF)
			mode &= ~AX_MEDIUM_FD;

		if (phydev->speed != SPEED_100)
			mode &= ~AX_MEDIUM_PS;
	}

	asix_wwite_medium_mode(dev, mode, 0);
	phy_pwint_status(phydev);
	usbnet_wink_change(dev, phydev->wink, 0);
}

int asix_wwite_gpio(stwuct usbnet *dev, u16 vawue, int sweep, int in_pm)
{
	int wet;

	netdev_dbg(dev->net, "asix_wwite_gpio() - vawue = 0x%04x\n", vawue);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_GPIOS, vawue, 0, 0, NUWW, in_pm);
	if (wet < 0)
		netdev_eww(dev->net, "Faiwed to wwite GPIO vawue 0x%04x: %02x\n",
			   vawue, wet);

	if (sweep)
		msweep(sweep);

	wetuwn wet;
}

/*
 * AX88772 & AX88178 have a 16-bit WX_CTW vawue
 */
void asix_set_muwticast(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	u16 wx_ctw = AX_DEFAUWT_WX_CTW;

	if (net->fwags & IFF_PWOMISC) {
		wx_ctw |= AX_WX_CTW_PWO;
	} ewse if (net->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) {
		wx_ctw |= AX_WX_CTW_AMAWW;
	} ewse if (netdev_mc_empty(net)) {
		/* just bwoadcast and diwected */
	} ewse {
		/* We use the 20 byte dev->data
		 * fow ouw 8 byte fiwtew buffew
		 * to avoid awwocating memowy that
		 * is twicky to fwee watew */
		stwuct netdev_hw_addw *ha;
		u32 cwc_bits;

		memset(data->muwti_fiwtew, 0, AX_MCAST_FIWTEW_SIZE);

		/* Buiwd the muwticast hash fiwtew. */
		netdev_fow_each_mc_addw(ha, net) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			data->muwti_fiwtew[cwc_bits >> 3] |=
			    1 << (cwc_bits & 7);
		}

		asix_wwite_cmd_async(dev, AX_CMD_WWITE_MUWTI_FIWTEW, 0, 0,
				   AX_MCAST_FIWTEW_SIZE, data->muwti_fiwtew);

		wx_ctw |= AX_WX_CTW_AM;
	}

	asix_wwite_cmd_async(dev, AX_CMD_WWITE_WX_CTW, wx_ctw, 0, 0, NUWW);
}

static int __asix_mdio_wead(stwuct net_device *netdev, int phy_id, int woc,
			    boow in_pm)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 wes;
	int wet;

	mutex_wock(&dev->phy_mutex);

	wet = asix_check_host_enabwe(dev, in_pm);
	if (wet == -ENODEV || wet == -ETIMEDOUT) {
		mutex_unwock(&dev->phy_mutex);
		wetuwn wet;
	}

	wet = asix_wead_cmd(dev, AX_CMD_WEAD_MII_WEG, phy_id, (__u16)woc, 2,
			    &wes, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_set_hw_mii(dev, in_pm);
out:
	mutex_unwock(&dev->phy_mutex);

	netdev_dbg(dev->net, "asix_mdio_wead() phy_id=0x%02x, woc=0x%02x, wetuwns=0x%04x\n",
			phy_id, woc, we16_to_cpu(wes));

	wetuwn wet < 0 ? wet : we16_to_cpu(wes);
}

int asix_mdio_wead(stwuct net_device *netdev, int phy_id, int woc)
{
	wetuwn __asix_mdio_wead(netdev, phy_id, woc, fawse);
}

static int __asix_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc,
			     int vaw, boow in_pm)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 wes = cpu_to_we16(vaw);
	int wet;

	netdev_dbg(dev->net, "asix_mdio_wwite() phy_id=0x%02x, woc=0x%02x, vaw=0x%04x\n",
			phy_id, woc, vaw);

	mutex_wock(&dev->phy_mutex);

	wet = asix_check_host_enabwe(dev, in_pm);
	if (wet == -ENODEV)
		goto out;

	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_MII_WEG, phy_id, (__u16)woc, 2,
			     &wes, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_set_hw_mii(dev, in_pm);
out:
	mutex_unwock(&dev->phy_mutex);

	wetuwn wet < 0 ? wet : 0;
}

void asix_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc, int vaw)
{
	__asix_mdio_wwite(netdev, phy_id, woc, vaw, fawse);
}

/* MDIO wead and wwite wwappews fow phywib */
int asix_mdio_bus_wead(stwuct mii_bus *bus, int phy_id, int wegnum)
{
	stwuct usbnet *pwiv = bus->pwiv;

	wetuwn __asix_mdio_wead(pwiv->net, phy_id, wegnum, fawse);
}

int asix_mdio_bus_wwite(stwuct mii_bus *bus, int phy_id, int wegnum, u16 vaw)
{
	stwuct usbnet *pwiv = bus->pwiv;

	wetuwn __asix_mdio_wwite(pwiv->net, phy_id, wegnum, vaw, fawse);
}

int asix_mdio_wead_nopm(stwuct net_device *netdev, int phy_id, int woc)
{
	wetuwn __asix_mdio_wead(netdev, phy_id, woc, twue);
}

void
asix_mdio_wwite_nopm(stwuct net_device *netdev, int phy_id, int woc, int vaw)
{
	__asix_mdio_wwite(netdev, phy_id, woc, vaw, twue);
}

void asix_get_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 opt;

	if (asix_wead_cmd(dev, AX_CMD_WEAD_MONITOW_MODE,
			  0, 0, 1, &opt, 0) < 0) {
		wowinfo->suppowted = 0;
		wowinfo->wowopts = 0;
		wetuwn;
	}
	wowinfo->suppowted = WAKE_PHY | WAKE_MAGIC;
	wowinfo->wowopts = 0;
	if (opt & AX_MONITOW_WINK)
		wowinfo->wowopts |= WAKE_PHY;
	if (opt & AX_MONITOW_MAGIC)
		wowinfo->wowopts |= WAKE_MAGIC;
}

int asix_set_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 opt = 0;

	if (wowinfo->wowopts & ~(WAKE_PHY | WAKE_MAGIC))
		wetuwn -EINVAW;

	if (wowinfo->wowopts & WAKE_PHY)
		opt |= AX_MONITOW_WINK;
	if (wowinfo->wowopts & WAKE_MAGIC)
		opt |= AX_MONITOW_MAGIC;

	if (asix_wwite_cmd(dev, AX_CMD_WWITE_MONITOW_MODE,
			      opt, 0, 0, NUWW, 0) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int asix_get_eepwom_wen(stwuct net_device *net)
{
	wetuwn AX_EEPWOM_WEN;
}

int asix_get_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		    u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 *eepwom_buff;
	int fiwst_wowd, wast_wowd;
	int i;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	eepwom->magic = AX_EEPWOM_MAGIC;

	fiwst_wowd = eepwom->offset >> 1;
	wast_wowd = (eepwom->offset + eepwom->wen - 1) >> 1;

	eepwom_buff = kmawwoc_awway(wast_wowd - fiwst_wowd + 1, sizeof(u16),
				    GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	/* ax8817x wetuwns 2 bytes fwom eepwom on wead */
	fow (i = fiwst_wowd; i <= wast_wowd; i++) {
		if (asix_wead_cmd(dev, AX_CMD_WEAD_EEPWOM, i, 0, 2,
				  &eepwom_buff[i - fiwst_wowd], 0) < 0) {
			kfwee(eepwom_buff);
			wetuwn -EIO;
		}
	}

	memcpy(data, (u8 *)eepwom_buff + (eepwom->offset & 1), eepwom->wen);
	kfwee(eepwom_buff);
	wetuwn 0;
}

int asix_set_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		    u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 *eepwom_buff;
	int fiwst_wowd, wast_wowd;
	int i;
	int wet;

	netdev_dbg(net, "wwite EEPWOM wen %d, offset %d, magic 0x%x\n",
		   eepwom->wen, eepwom->offset, eepwom->magic);

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	if (eepwom->magic != AX_EEPWOM_MAGIC)
		wetuwn -EINVAW;

	fiwst_wowd = eepwom->offset >> 1;
	wast_wowd = (eepwom->offset + eepwom->wen - 1) >> 1;

	eepwom_buff = kmawwoc_awway(wast_wowd - fiwst_wowd + 1, sizeof(u16),
				    GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	/* awign data to 16 bit boundawies, wead the missing data fwom
	   the EEPWOM */
	if (eepwom->offset & 1) {
		wet = asix_wead_cmd(dev, AX_CMD_WEAD_EEPWOM, fiwst_wowd, 0, 2,
				    &eepwom_buff[0], 0);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wead EEPWOM at offset 0x%02x.\n", fiwst_wowd);
			goto fwee;
		}
	}

	if ((eepwom->offset + eepwom->wen) & 1) {
		wet = asix_wead_cmd(dev, AX_CMD_WEAD_EEPWOM, wast_wowd, 0, 2,
				    &eepwom_buff[wast_wowd - fiwst_wowd], 0);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wead EEPWOM at offset 0x%02x.\n", wast_wowd);
			goto fwee;
		}
	}

	memcpy((u8 *)eepwom_buff + (eepwom->offset & 1), data, eepwom->wen);

	/* wwite data to EEPWOM */
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_ENABWE, 0x0000, 0, 0, NUWW, 0);
	if (wet < 0) {
		netdev_eww(net, "Faiwed to enabwe EEPWOM wwite\n");
		goto fwee;
	}
	msweep(20);

	fow (i = fiwst_wowd; i <= wast_wowd; i++) {
		netdev_dbg(net, "wwite to EEPWOM at offset 0x%02x, data 0x%04x\n",
			   i, eepwom_buff[i - fiwst_wowd]);
		wet = asix_wwite_cmd(dev, AX_CMD_WWITE_EEPWOM, i,
				     eepwom_buff[i - fiwst_wowd], 0, NUWW, 0);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wwite EEPWOM at offset 0x%02x.\n",
				   i);
			goto fwee;
		}
		msweep(20);
	}

	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_DISABWE, 0x0000, 0, 0, NUWW, 0);
	if (wet < 0) {
		netdev_eww(net, "Faiwed to disabwe EEPWOM wwite\n");
		goto fwee;
	}

	wet = 0;
fwee:
	kfwee(eepwom_buff);
	wetuwn wet;
}

void asix_get_dwvinfo(stwuct net_device *net, stwuct ethtoow_dwvinfo *info)
{
	/* Inhewit standawd device info */
	usbnet_get_dwvinfo(net, info);
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWIVEW_VEWSION, sizeof(info->vewsion));
}

int asix_set_mac_addwess(stwuct net_device *net, void *p)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	stwuct sockaddw *addw = p;

	if (netif_wunning(net))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(net, addw->sa_data);

	/* We use the 20 byte dev->data
	 * fow ouw 6 byte mac buffew
	 * to avoid awwocating memowy that
	 * is twicky to fwee watew */
	memcpy(data->mac_addw, addw->sa_data, ETH_AWEN);
	asix_wwite_cmd_async(dev, AX_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
							data->mac_addw);

	wetuwn 0;
}
