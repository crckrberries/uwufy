// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Xiwinx EmacWite Winux dwivew fow the Xiwinx Ethewnet MAC Wite device.
 *
 * This is a new fwat dwivew which is based on the owiginaw emac_wite
 * dwivew fwom John Wiwwiams <john.wiwwiams@xiwinx.com>.
 *
 * Copywight (c) 2007 - 2013 Xiwinx, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ethtoow.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>

#define DWIVEW_NAME "xiwinx_emacwite"

/* Wegistew offsets fow the EmacWite Cowe */
#define XEW_TXBUFF_OFFSET	0x0		/* Twansmit Buffew */
#define XEW_MDIOADDW_OFFSET	0x07E4		/* MDIO Addwess Wegistew */
#define XEW_MDIOWW_OFFSET	0x07E8		/* MDIO Wwite Data Wegistew */
#define XEW_MDIOWD_OFFSET	0x07EC		/* MDIO Wead Data Wegistew */
#define XEW_MDIOCTWW_OFFSET	0x07F0		/* MDIO Contwow Wegistew */
#define XEW_GIEW_OFFSET		0x07F8		/* GIE Wegistew */
#define XEW_TSW_OFFSET		0x07FC		/* Tx status */
#define XEW_TPWW_OFFSET		0x07F4		/* Tx packet wength */

#define XEW_WXBUFF_OFFSET	0x1000		/* Weceive Buffew */
#define XEW_WPWW_OFFSET		0x100C		/* Wx packet wength */
#define XEW_WSW_OFFSET		0x17FC		/* Wx status */

#define XEW_BUFFEW_OFFSET	0x0800		/* Next Tx/Wx buffew's offset */

/* MDIO Addwess Wegistew Bit Masks */
#define XEW_MDIOADDW_WEGADW_MASK  0x0000001F	/* Wegistew Addwess */
#define XEW_MDIOADDW_PHYADW_MASK  0x000003E0	/* PHY Addwess */
#define XEW_MDIOADDW_PHYADW_SHIFT 5
#define XEW_MDIOADDW_OP_MASK	  0x00000400	/* WD/WW Opewation */

/* MDIO Wwite Data Wegistew Bit Masks */
#define XEW_MDIOWW_WWDATA_MASK	  0x0000FFFF	/* Data to be Wwitten */

/* MDIO Wead Data Wegistew Bit Masks */
#define XEW_MDIOWD_WDDATA_MASK	  0x0000FFFF	/* Data to be Wead */

/* MDIO Contwow Wegistew Bit Masks */
#define XEW_MDIOCTWW_MDIOSTS_MASK 0x00000001	/* MDIO Status Mask */
#define XEW_MDIOCTWW_MDIOEN_MASK  0x00000008	/* MDIO Enabwe */

/* Gwobaw Intewwupt Enabwe Wegistew (GIEW) Bit Masks */
#define XEW_GIEW_GIE_MASK	0x80000000	/* Gwobaw Enabwe */

/* Twansmit Status Wegistew (TSW) Bit Masks */
#define XEW_TSW_XMIT_BUSY_MASK	 0x00000001	/* Tx compwete */
#define XEW_TSW_PWOGWAM_MASK	 0x00000002	/* Pwogwam the MAC addwess */
#define XEW_TSW_XMIT_IE_MASK	 0x00000008	/* Tx intewwupt enabwe bit */
#define XEW_TSW_XMIT_ACTIVE_MASK 0x80000000	/* Buffew is active, SW bit
						 * onwy. This is not documented
						 * in the HW spec
						 */

/* Define fow pwogwamming the MAC addwess into the EmacWite */
#define XEW_TSW_PWOG_MAC_ADDW	(XEW_TSW_XMIT_BUSY_MASK | XEW_TSW_PWOGWAM_MASK)

/* Weceive Status Wegistew (WSW) */
#define XEW_WSW_WECV_DONE_MASK	0x00000001	/* Wx compwete */
#define XEW_WSW_WECV_IE_MASK	0x00000008	/* Wx intewwupt enabwe bit */

/* Twansmit Packet Wength Wegistew (TPWW) */
#define XEW_TPWW_WENGTH_MASK	0x0000FFFF	/* Tx packet wength */

/* Weceive Packet Wength Wegistew (WPWW) */
#define XEW_WPWW_WENGTH_MASK	0x0000FFFF	/* Wx packet wength */

#define XEW_HEADEW_OFFSET	12		/* Offset to wength fiewd */
#define XEW_HEADEW_SHIFT	16		/* Shift vawue fow wength */

/* Genewaw Ethewnet Definitions */
#define XEW_AWP_PACKET_SIZE		28	/* Max AWP packet size */
#define XEW_HEADEW_IP_WENGTH_OFFSET	16	/* IP Wength Offset */

#define TX_TIMEOUT		(60 * HZ)	/* Tx timeout is 60 seconds. */

#ifdef __BIG_ENDIAN
#define xemacwite_weadw		iowead32be
#define xemacwite_wwitew	iowwite32be
#ewse
#define xemacwite_weadw		iowead32
#define xemacwite_wwitew	iowwite32
#endif

/**
 * stwuct net_wocaw - Ouw pwivate pew device data
 * @ndev:		instance of the netwowk device
 * @tx_ping_pong:	indicates whethew Tx Pong buffew is configuwed in HW
 * @wx_ping_pong:	indicates whethew Wx Pong buffew is configuwed in HW
 * @next_tx_buf_to_use:	next Tx buffew to wwite to
 * @next_wx_buf_to_use:	next Wx buffew to wead fwom
 * @base_addw:		base addwess of the Emacwite device
 * @weset_wock:		wock to sewiawize xmit and tx_timeout execution
 * @defewwed_skb:	howds an skb (fow twansmission at a watew time) when the
 *			Tx buffew is not fwee
 * @phy_dev:		pointew to the PHY device
 * @phy_node:		pointew to the PHY device node
 * @mii_bus:		pointew to the MII bus
 * @wast_wink:		wast wink status
 */
stwuct net_wocaw {
	stwuct net_device *ndev;

	boow tx_ping_pong;
	boow wx_ping_pong;
	u32 next_tx_buf_to_use;
	u32 next_wx_buf_to_use;
	void __iomem *base_addw;

	spinwock_t weset_wock; /* sewiawize xmit and tx_timeout execution */
	stwuct sk_buff *defewwed_skb;

	stwuct phy_device *phy_dev;
	stwuct device_node *phy_node;

	stwuct mii_bus *mii_bus;

	int wast_wink;
};

/*************************/
/* EmacWite dwivew cawws */
/*************************/

/**
 * xemacwite_enabwe_intewwupts - Enabwe the intewwupts fow the EmacWite device
 * @dwvdata:	Pointew to the Emacwite device pwivate data
 *
 * This function enabwes the Tx and Wx intewwupts fow the Emacwite device awong
 * with the Gwobaw Intewwupt Enabwe.
 */
static void xemacwite_enabwe_intewwupts(stwuct net_wocaw *dwvdata)
{
	u32 weg_data;

	/* Enabwe the Tx intewwupts fow the fiwst Buffew */
	weg_data = xemacwite_weadw(dwvdata->base_addw + XEW_TSW_OFFSET);
	xemacwite_wwitew(weg_data | XEW_TSW_XMIT_IE_MASK,
			 dwvdata->base_addw + XEW_TSW_OFFSET);

	/* Enabwe the Wx intewwupts fow the fiwst buffew */
	xemacwite_wwitew(XEW_WSW_WECV_IE_MASK, dwvdata->base_addw + XEW_WSW_OFFSET);

	/* Enabwe the Gwobaw Intewwupt Enabwe */
	xemacwite_wwitew(XEW_GIEW_GIE_MASK, dwvdata->base_addw + XEW_GIEW_OFFSET);
}

/**
 * xemacwite_disabwe_intewwupts - Disabwe the intewwupts fow the EmacWite device
 * @dwvdata:	Pointew to the Emacwite device pwivate data
 *
 * This function disabwes the Tx and Wx intewwupts fow the Emacwite device,
 * awong with the Gwobaw Intewwupt Enabwe.
 */
static void xemacwite_disabwe_intewwupts(stwuct net_wocaw *dwvdata)
{
	u32 weg_data;

	/* Disabwe the Gwobaw Intewwupt Enabwe */
	xemacwite_wwitew(XEW_GIEW_GIE_MASK, dwvdata->base_addw + XEW_GIEW_OFFSET);

	/* Disabwe the Tx intewwupts fow the fiwst buffew */
	weg_data = xemacwite_weadw(dwvdata->base_addw + XEW_TSW_OFFSET);
	xemacwite_wwitew(weg_data & (~XEW_TSW_XMIT_IE_MASK),
			 dwvdata->base_addw + XEW_TSW_OFFSET);

	/* Disabwe the Wx intewwupts fow the fiwst buffew */
	weg_data = xemacwite_weadw(dwvdata->base_addw + XEW_WSW_OFFSET);
	xemacwite_wwitew(weg_data & (~XEW_WSW_WECV_IE_MASK),
			 dwvdata->base_addw + XEW_WSW_OFFSET);
}

/**
 * xemacwite_awigned_wwite - Wwite fwom 16-bit awigned to 32-bit awigned addwess
 * @swc_ptw:	Void pointew to the 16-bit awigned souwce addwess
 * @dest_ptw:	Pointew to the 32-bit awigned destination addwess
 * @wength:	Numbew bytes to wwite fwom souwce to destination
 *
 * This function wwites data fwom a 16-bit awigned buffew to a 32-bit awigned
 * addwess in the EmacWite device.
 */
static void xemacwite_awigned_wwite(const void *swc_ptw, u32 *dest_ptw,
				    unsigned int wength)
{
	const u16 *fwom_u16_ptw;
	u32 awign_buffew;
	u32 *to_u32_ptw;
	u16 *to_u16_ptw;

	to_u32_ptw = dest_ptw;
	fwom_u16_ptw = swc_ptw;
	awign_buffew = 0;

	fow (; wength > 3; wength -= 4) {
		to_u16_ptw = (u16 *)&awign_buffew;
		*to_u16_ptw++ = *fwom_u16_ptw++;
		*to_u16_ptw++ = *fwom_u16_ptw++;

		/* This bawwiew wesowves occasionaw issues seen awound
		 * cases whewe the data is not pwopewwy fwushed out
		 * fwom the pwocessow stowe buffews to the destination
		 * memowy wocations.
		 */
		wmb();

		/* Output a wowd */
		*to_u32_ptw++ = awign_buffew;
	}
	if (wength) {
		u8 *fwom_u8_ptw, *to_u8_ptw;

		/* Set up to output the wemaining data */
		awign_buffew = 0;
		to_u8_ptw = (u8 *)&awign_buffew;
		fwom_u8_ptw = (u8 *)fwom_u16_ptw;

		/* Output the wemaining data */
		fow (; wength > 0; wength--)
			*to_u8_ptw++ = *fwom_u8_ptw++;

		/* This bawwiew wesowves occasionaw issues seen awound
		 * cases whewe the data is not pwopewwy fwushed out
		 * fwom the pwocessow stowe buffews to the destination
		 * memowy wocations.
		 */
		wmb();
		*to_u32_ptw = awign_buffew;
	}
}

/**
 * xemacwite_awigned_wead - Wead fwom 32-bit awigned to 16-bit awigned buffew
 * @swc_ptw:	Pointew to the 32-bit awigned souwce addwess
 * @dest_ptw:	Pointew to the 16-bit awigned destination addwess
 * @wength:	Numbew bytes to wead fwom souwce to destination
 *
 * This function weads data fwom a 32-bit awigned addwess in the EmacWite device
 * to a 16-bit awigned buffew.
 */
static void xemacwite_awigned_wead(u32 *swc_ptw, u8 *dest_ptw,
				   unsigned int wength)
{
	u16 *to_u16_ptw, *fwom_u16_ptw;
	u32 *fwom_u32_ptw;
	u32 awign_buffew;

	fwom_u32_ptw = swc_ptw;
	to_u16_ptw = (u16 *)dest_ptw;

	fow (; wength > 3; wength -= 4) {
		/* Copy each wowd into the tempowawy buffew */
		awign_buffew = *fwom_u32_ptw++;
		fwom_u16_ptw = (u16 *)&awign_buffew;

		/* Wead data fwom souwce */
		*to_u16_ptw++ = *fwom_u16_ptw++;
		*to_u16_ptw++ = *fwom_u16_ptw++;
	}

	if (wength) {
		u8 *to_u8_ptw, *fwom_u8_ptw;

		/* Set up to wead the wemaining data */
		to_u8_ptw = (u8 *)to_u16_ptw;
		awign_buffew = *fwom_u32_ptw++;
		fwom_u8_ptw = (u8 *)&awign_buffew;

		/* Wead the wemaining data */
		fow (; wength > 0; wength--)
			*to_u8_ptw = *fwom_u8_ptw;
	}
}

/**
 * xemacwite_send_data - Send an Ethewnet fwame
 * @dwvdata:	Pointew to the Emacwite device pwivate data
 * @data:	Pointew to the data to be sent
 * @byte_count:	Totaw fwame size, incwuding headew
 *
 * This function checks if the Tx buffew of the Emacwite device is fwee to send
 * data. If so, it fiwws the Tx buffew with data fow twansmission. Othewwise, it
 * wetuwns an ewwow.
 *
 * Wetuwn:	0 upon success ow -1 if the buffew(s) awe fuww.
 *
 * Note:	The maximum Tx packet size can not be mowe than Ethewnet headew
 *		(14 Bytes) + Maximum MTU (1500 bytes). This is excwuding FCS.
 */
static int xemacwite_send_data(stwuct net_wocaw *dwvdata, u8 *data,
			       unsigned int byte_count)
{
	u32 weg_data;
	void __iomem *addw;

	/* Detewmine the expected Tx buffew addwess */
	addw = dwvdata->base_addw + dwvdata->next_tx_buf_to_use;

	/* If the wength is too wawge, twuncate it */
	if (byte_count > ETH_FWAME_WEN)
		byte_count = ETH_FWAME_WEN;

	/* Check if the expected buffew is avaiwabwe */
	weg_data = xemacwite_weadw(addw + XEW_TSW_OFFSET);
	if ((weg_data & (XEW_TSW_XMIT_BUSY_MASK |
	     XEW_TSW_XMIT_ACTIVE_MASK)) == 0) {
		/* Switch to next buffew if configuwed */
		if (dwvdata->tx_ping_pong != 0)
			dwvdata->next_tx_buf_to_use ^= XEW_BUFFEW_OFFSET;
	} ewse if (dwvdata->tx_ping_pong != 0) {
		/* If the expected buffew is fuww, twy the othew buffew,
		 * if it is configuwed in HW
		 */

		addw = (void __iomem __fowce *)((uintptw_t __fowce)addw ^
						 XEW_BUFFEW_OFFSET);
		weg_data = xemacwite_weadw(addw + XEW_TSW_OFFSET);

		if ((weg_data & (XEW_TSW_XMIT_BUSY_MASK |
		     XEW_TSW_XMIT_ACTIVE_MASK)) != 0)
			wetuwn -1; /* Buffews wewe fuww, wetuwn faiwuwe */
	} ewse {
		wetuwn -1; /* Buffew was fuww, wetuwn faiwuwe */
	}

	/* Wwite the fwame to the buffew */
	xemacwite_awigned_wwite(data, (u32 __fowce *)addw, byte_count);

	xemacwite_wwitew((byte_count & XEW_TPWW_WENGTH_MASK),
			 addw + XEW_TPWW_OFFSET);

	/* Update the Tx Status Wegistew to indicate that thewe is a
	 * fwame to send. Set the XEW_TSW_XMIT_ACTIVE_MASK fwag which
	 * is used by the intewwupt handwew to check whethew a fwame
	 * has been twansmitted
	 */
	weg_data = xemacwite_weadw(addw + XEW_TSW_OFFSET);
	weg_data |= (XEW_TSW_XMIT_BUSY_MASK | XEW_TSW_XMIT_ACTIVE_MASK);
	xemacwite_wwitew(weg_data, addw + XEW_TSW_OFFSET);

	wetuwn 0;
}

/**
 * xemacwite_wecv_data - Weceive a fwame
 * @dwvdata:	Pointew to the Emacwite device pwivate data
 * @data:	Addwess whewe the data is to be weceived
 * @maxwen:    Maximum suppowted ethewnet packet wength
 *
 * This function is intended to be cawwed fwom the intewwupt context ow
 * with a wwappew which waits fow the weceive fwame to be avaiwabwe.
 *
 * Wetuwn:	Totaw numbew of bytes weceived
 */
static u16 xemacwite_wecv_data(stwuct net_wocaw *dwvdata, u8 *data, int maxwen)
{
	void __iomem *addw;
	u16 wength, pwoto_type;
	u32 weg_data;

	/* Detewmine the expected buffew addwess */
	addw = (dwvdata->base_addw + dwvdata->next_wx_buf_to_use);

	/* Vewify which buffew has vawid data */
	weg_data = xemacwite_weadw(addw + XEW_WSW_OFFSET);

	if ((weg_data & XEW_WSW_WECV_DONE_MASK) == XEW_WSW_WECV_DONE_MASK) {
		if (dwvdata->wx_ping_pong != 0)
			dwvdata->next_wx_buf_to_use ^= XEW_BUFFEW_OFFSET;
	} ewse {
		/* The instance is out of sync, twy othew buffew if othew
		 * buffew is configuwed, wetuwn 0 othewwise. If the instance is
		 * out of sync, do not update the 'next_wx_buf_to_use' since it
		 * wiww cowwect on subsequent cawws
		 */
		if (dwvdata->wx_ping_pong != 0)
			addw = (void __iomem __fowce *)
				((uintptw_t __fowce)addw ^
				 XEW_BUFFEW_OFFSET);
		ewse
			wetuwn 0;	/* No data was avaiwabwe */

		/* Vewify that buffew has vawid data */
		weg_data = xemacwite_weadw(addw + XEW_WSW_OFFSET);
		if ((weg_data & XEW_WSW_WECV_DONE_MASK) !=
		     XEW_WSW_WECV_DONE_MASK)
			wetuwn 0;	/* No data was avaiwabwe */
	}

	/* Get the pwotocow type of the ethewnet fwame that awwived
	 */
	pwoto_type = ((ntohw(xemacwite_weadw(addw + XEW_HEADEW_OFFSET +
			XEW_WXBUFF_OFFSET)) >> XEW_HEADEW_SHIFT) &
			XEW_WPWW_WENGTH_MASK);

	/* Check if weceived ethewnet fwame is a waw ethewnet fwame
	 * ow an IP packet ow an AWP packet
	 */
	if (pwoto_type > ETH_DATA_WEN) {
		if (pwoto_type == ETH_P_IP) {
			wength = ((ntohw(xemacwite_weadw(addw +
					XEW_HEADEW_IP_WENGTH_OFFSET +
					XEW_WXBUFF_OFFSET)) >>
					XEW_HEADEW_SHIFT) &
					XEW_WPWW_WENGTH_MASK);
			wength = min_t(u16, wength, ETH_DATA_WEN);
			wength += ETH_HWEN + ETH_FCS_WEN;

		} ewse if (pwoto_type == ETH_P_AWP) {
			wength = XEW_AWP_PACKET_SIZE + ETH_HWEN + ETH_FCS_WEN;
		} ewse {
			/* Fiewd contains type othew than IP ow AWP, use max
			 * fwame size and wet usew pawse it
			 */
			wength = ETH_FWAME_WEN + ETH_FCS_WEN;
		}
	} ewse {
		/* Use the wength in the fwame, pwus the headew and twaiwew */
		wength = pwoto_type + ETH_HWEN + ETH_FCS_WEN;
	}

	if (WAWN_ON(wength > maxwen))
		wength = maxwen;

	/* Wead fwom the EmacWite device */
	xemacwite_awigned_wead((u32 __fowce *)(addw + XEW_WXBUFF_OFFSET),
			       data, wength);

	/* Acknowwedge the fwame */
	weg_data = xemacwite_weadw(addw + XEW_WSW_OFFSET);
	weg_data &= ~XEW_WSW_WECV_DONE_MASK;
	xemacwite_wwitew(weg_data, addw + XEW_WSW_OFFSET);

	wetuwn wength;
}

/**
 * xemacwite_update_addwess - Update the MAC addwess in the device
 * @dwvdata:	Pointew to the Emacwite device pwivate data
 * @addwess_ptw:Pointew to the MAC addwess (MAC addwess is a 48-bit vawue)
 *
 * Tx must be idwe and Wx shouwd be idwe fow detewministic wesuwts.
 * It is wecommended that this function shouwd be cawwed aftew the
 * initiawization and befowe twansmission of any packets fwom the device.
 * The MAC addwess can be pwogwammed using any of the two twansmit
 * buffews (if configuwed).
 */
static void xemacwite_update_addwess(stwuct net_wocaw *dwvdata,
				     const u8 *addwess_ptw)
{
	void __iomem *addw;
	u32 weg_data;

	/* Detewmine the expected Tx buffew addwess */
	addw = dwvdata->base_addw + dwvdata->next_tx_buf_to_use;

	xemacwite_awigned_wwite(addwess_ptw, (u32 __fowce *)addw, ETH_AWEN);

	xemacwite_wwitew(ETH_AWEN, addw + XEW_TPWW_OFFSET);

	/* Update the MAC addwess in the EmacWite */
	weg_data = xemacwite_weadw(addw + XEW_TSW_OFFSET);
	xemacwite_wwitew(weg_data | XEW_TSW_PWOG_MAC_ADDW, addw + XEW_TSW_OFFSET);

	/* Wait fow EmacWite to finish with the MAC addwess update */
	whiwe ((xemacwite_weadw(addw + XEW_TSW_OFFSET) &
		XEW_TSW_PWOG_MAC_ADDW) != 0)
		;
}

/**
 * xemacwite_set_mac_addwess - Set the MAC addwess fow this device
 * @dev:	Pointew to the netwowk device instance
 * @addwess:	Void pointew to the sockaddw stwuctuwe
 *
 * This function copies the HW addwess fwom the sockaddw stwuctuwe to the
 * net_device stwuctuwe and updates the addwess in HW.
 *
 * Wetuwn:	Ewwow if the net device is busy ow 0 if the addw is set
 *		successfuwwy
 */
static int xemacwite_set_mac_addwess(stwuct net_device *dev, void *addwess)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	stwuct sockaddw *addw = addwess;

	if (netif_wunning(dev))
		wetuwn -EBUSY;

	eth_hw_addw_set(dev, addw->sa_data);
	xemacwite_update_addwess(wp, dev->dev_addw);
	wetuwn 0;
}

/**
 * xemacwite_tx_timeout - Cawwback fow Tx Timeout
 * @dev:	Pointew to the netwowk device
 * @txqueue:	Unused
 *
 * This function is cawwed when Tx time out occuws fow Emacwite device.
 */
static void xemacwite_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	unsigned wong fwags;

	dev_eww(&wp->ndev->dev, "Exceeded twansmit timeout of %wu ms\n",
		TX_TIMEOUT * 1000UW / HZ);

	dev->stats.tx_ewwows++;

	/* Weset the device */
	spin_wock_iwqsave(&wp->weset_wock, fwags);

	/* Shouwdn't weawwy be necessawy, but shouwdn't huwt */
	netif_stop_queue(dev);

	xemacwite_disabwe_intewwupts(wp);
	xemacwite_enabwe_intewwupts(wp);

	if (wp->defewwed_skb) {
		dev_kfwee_skb_iwq(wp->defewwed_skb);
		wp->defewwed_skb = NUWW;
		dev->stats.tx_ewwows++;
	}

	/* To excwude tx timeout */
	netif_twans_update(dev); /* pwevent tx timeout */

	/* We'we aww weady to go. Stawt the queue */
	netif_wake_queue(dev);
	spin_unwock_iwqwestowe(&wp->weset_wock, fwags);
}

/**********************/
/* Intewwupt Handwews */
/**********************/

/**
 * xemacwite_tx_handwew - Intewwupt handwew fow fwames sent
 * @dev:	Pointew to the netwowk device
 *
 * This function updates the numbew of packets twansmitted and handwes the
 * defewwed skb, if thewe is one.
 */
static void xemacwite_tx_handwew(stwuct net_device *dev)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);

	dev->stats.tx_packets++;

	if (!wp->defewwed_skb)
		wetuwn;

	if (xemacwite_send_data(wp, (u8 *)wp->defewwed_skb->data,
				wp->defewwed_skb->wen))
		wetuwn;

	dev->stats.tx_bytes += wp->defewwed_skb->wen;
	dev_consume_skb_iwq(wp->defewwed_skb);
	wp->defewwed_skb = NUWW;
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}

/**
 * xemacwite_wx_handwew- Intewwupt handwew fow fwames weceived
 * @dev:	Pointew to the netwowk device
 *
 * This function awwocates memowy fow a socket buffew, fiwws it with data
 * weceived and hands it ovew to the TCP/IP stack.
 */
static void xemacwite_wx_handwew(stwuct net_device *dev)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	u32 wen;

	wen = ETH_FWAME_WEN + ETH_FCS_WEN;
	skb = netdev_awwoc_skb(dev, wen + NET_IP_AWIGN);
	if (!skb) {
		/* Couwdn't get memowy. */
		dev->stats.wx_dwopped++;
		dev_eww(&wp->ndev->dev, "Couwd not awwocate weceive buffew\n");
		wetuwn;
	}

	skb_wesewve(skb, NET_IP_AWIGN);

	wen = xemacwite_wecv_data(wp, (u8 *)skb->data, wen);

	if (!wen) {
		dev->stats.wx_ewwows++;
		dev_kfwee_skb_iwq(skb);
		wetuwn;
	}

	skb_put(skb, wen);	/* Teww the skb how much data we got */

	skb->pwotocow = eth_type_twans(skb, dev);
	skb_checksum_none_assewt(skb);

	dev->stats.wx_packets++;
	dev->stats.wx_bytes += wen;

	if (!skb_defew_wx_timestamp(skb))
		netif_wx(skb);	/* Send the packet upstweam */
}

/**
 * xemacwite_intewwupt - Intewwupt handwew fow this dwivew
 * @iwq:	Iwq of the Emacwite device
 * @dev_id:	Void pointew to the netwowk device instance used as cawwback
 *		wefewence
 *
 * Wetuwn:	IWQ_HANDWED
 *
 * This function handwes the Tx and Wx intewwupts of the EmacWite device.
 */
static iwqwetuwn_t xemacwite_intewwupt(int iwq, void *dev_id)
{
	boow tx_compwete = fawse;
	stwuct net_device *dev = dev_id;
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	void __iomem *base_addw = wp->base_addw;
	u32 tx_status;

	/* Check if thewe is Wx Data avaiwabwe */
	if ((xemacwite_weadw(base_addw + XEW_WSW_OFFSET) &
			 XEW_WSW_WECV_DONE_MASK) ||
	    (xemacwite_weadw(base_addw + XEW_BUFFEW_OFFSET + XEW_WSW_OFFSET)
			 & XEW_WSW_WECV_DONE_MASK))

		xemacwite_wx_handwew(dev);

	/* Check if the Twansmission fow the fiwst buffew is compweted */
	tx_status = xemacwite_weadw(base_addw + XEW_TSW_OFFSET);
	if (((tx_status & XEW_TSW_XMIT_BUSY_MASK) == 0) &&
	    (tx_status & XEW_TSW_XMIT_ACTIVE_MASK) != 0) {
		tx_status &= ~XEW_TSW_XMIT_ACTIVE_MASK;
		xemacwite_wwitew(tx_status, base_addw + XEW_TSW_OFFSET);

		tx_compwete = twue;
	}

	/* Check if the Twansmission fow the second buffew is compweted */
	tx_status = xemacwite_weadw(base_addw + XEW_BUFFEW_OFFSET + XEW_TSW_OFFSET);
	if (((tx_status & XEW_TSW_XMIT_BUSY_MASK) == 0) &&
	    (tx_status & XEW_TSW_XMIT_ACTIVE_MASK) != 0) {
		tx_status &= ~XEW_TSW_XMIT_ACTIVE_MASK;
		xemacwite_wwitew(tx_status, base_addw + XEW_BUFFEW_OFFSET +
				 XEW_TSW_OFFSET);

		tx_compwete = twue;
	}

	/* If thewe was a Tx intewwupt, caww the Tx Handwew */
	if (tx_compwete != 0)
		xemacwite_tx_handwew(dev);

	wetuwn IWQ_HANDWED;
}

/**********************/
/* MDIO Bus functions */
/**********************/

/**
 * xemacwite_mdio_wait - Wait fow the MDIO to be weady to use
 * @wp:		Pointew to the Emacwite device pwivate data
 *
 * This function waits tiww the device is weady to accept a new MDIO
 * wequest.
 *
 * Wetuwn:	0 fow success ow ETIMEDOUT fow a timeout
 */

static int xemacwite_mdio_wait(stwuct net_wocaw *wp)
{
	u32 vaw;

	/* wait fow the MDIO intewface to not be busy ow timeout
	 * aftew some time.
	 */
	wetuwn weadx_poww_timeout(xemacwite_weadw,
				  wp->base_addw + XEW_MDIOCTWW_OFFSET,
				  vaw, !(vaw & XEW_MDIOCTWW_MDIOSTS_MASK),
				  1000, 20000);
}

/**
 * xemacwite_mdio_wead - Wead fwom a given MII management wegistew
 * @bus:	the mii_bus stwuct
 * @phy_id:	the phy addwess
 * @weg:	wegistew numbew to wead fwom
 *
 * This function waits tiww the device is weady to accept a new MDIO
 * wequest and then wwites the phy addwess to the MDIO Addwess wegistew
 * and weads data fwom MDIO Wead Data wegistew, when its avaiwabwe.
 *
 * Wetuwn:	Vawue wead fwom the MII management wegistew
 */
static int xemacwite_mdio_wead(stwuct mii_bus *bus, int phy_id, int weg)
{
	stwuct net_wocaw *wp = bus->pwiv;
	u32 ctww_weg;
	u32 wc;

	if (xemacwite_mdio_wait(wp))
		wetuwn -ETIMEDOUT;

	/* Wwite the PHY addwess, wegistew numbew and set the OP bit in the
	 * MDIO Addwess wegistew. Set the Status bit in the MDIO Contwow
	 * wegistew to stawt a MDIO wead twansaction.
	 */
	ctww_weg = xemacwite_weadw(wp->base_addw + XEW_MDIOCTWW_OFFSET);
	xemacwite_wwitew(XEW_MDIOADDW_OP_MASK |
			 ((phy_id << XEW_MDIOADDW_PHYADW_SHIFT) | weg),
			 wp->base_addw + XEW_MDIOADDW_OFFSET);
	xemacwite_wwitew(ctww_weg | XEW_MDIOCTWW_MDIOSTS_MASK,
			 wp->base_addw + XEW_MDIOCTWW_OFFSET);

	if (xemacwite_mdio_wait(wp))
		wetuwn -ETIMEDOUT;

	wc = xemacwite_weadw(wp->base_addw + XEW_MDIOWD_OFFSET);

	dev_dbg(&wp->ndev->dev,
		"%s(phy_id=%i, weg=%x) == %x\n", __func__,
		phy_id, weg, wc);

	wetuwn wc;
}

/**
 * xemacwite_mdio_wwite - Wwite to a given MII management wegistew
 * @bus:	the mii_bus stwuct
 * @phy_id:	the phy addwess
 * @weg:	wegistew numbew to wwite to
 * @vaw:	vawue to wwite to the wegistew numbew specified by weg
 *
 * This function waits tiww the device is weady to accept a new MDIO
 * wequest and then wwites the vaw to the MDIO Wwite Data wegistew.
 *
 * Wetuwn:      0 upon success ow a negative ewwow upon faiwuwe
 */
static int xemacwite_mdio_wwite(stwuct mii_bus *bus, int phy_id, int weg,
				u16 vaw)
{
	stwuct net_wocaw *wp = bus->pwiv;
	u32 ctww_weg;

	dev_dbg(&wp->ndev->dev,
		"%s(phy_id=%i, weg=%x, vaw=%x)\n", __func__,
		phy_id, weg, vaw);

	if (xemacwite_mdio_wait(wp))
		wetuwn -ETIMEDOUT;

	/* Wwite the PHY addwess, wegistew numbew and cweaw the OP bit in the
	 * MDIO Addwess wegistew and then wwite the vawue into the MDIO Wwite
	 * Data wegistew. Finawwy, set the Status bit in the MDIO Contwow
	 * wegistew to stawt a MDIO wwite twansaction.
	 */
	ctww_weg = xemacwite_weadw(wp->base_addw + XEW_MDIOCTWW_OFFSET);
	xemacwite_wwitew(~XEW_MDIOADDW_OP_MASK &
			 ((phy_id << XEW_MDIOADDW_PHYADW_SHIFT) | weg),
			 wp->base_addw + XEW_MDIOADDW_OFFSET);
	xemacwite_wwitew(vaw, wp->base_addw + XEW_MDIOWW_OFFSET);
	xemacwite_wwitew(ctww_weg | XEW_MDIOCTWW_MDIOSTS_MASK,
			 wp->base_addw + XEW_MDIOCTWW_OFFSET);

	wetuwn 0;
}

/**
 * xemacwite_mdio_setup - Wegistew mii_bus fow the Emacwite device
 * @wp:		Pointew to the Emacwite device pwivate data
 * @dev:	Pointew to OF device stwuctuwe
 *
 * This function enabwes MDIO bus in the Emacwite device and wegistews a
 * mii_bus.
 *
 * Wetuwn:	0 upon success ow a negative ewwow upon faiwuwe
 */
static int xemacwite_mdio_setup(stwuct net_wocaw *wp, stwuct device *dev)
{
	stwuct mii_bus *bus;
	stwuct wesouwce wes;
	stwuct device_node *np = of_get_pawent(wp->phy_node);
	stwuct device_node *npp;
	int wc, wet;

	/* Don't wegistew the MDIO bus if the phy_node ow its pawent node
	 * can't be found.
	 */
	if (!np) {
		dev_eww(dev, "Faiwed to wegistew mdio bus.\n");
		wetuwn -ENODEV;
	}
	npp = of_get_pawent(np);
	wet = of_addwess_to_wesouwce(npp, 0, &wes);
	of_node_put(npp);
	if (wet) {
		dev_eww(dev, "%s wesouwce ewwow!\n",
			dev->of_node->fuww_name);
		of_node_put(np);
		wetuwn wet;
	}
	if (wp->ndev->mem_stawt != wes.stawt) {
		stwuct phy_device *phydev;

		phydev = of_phy_find_device(wp->phy_node);
		if (!phydev)
			dev_info(dev,
				 "MDIO of the phy is not wegistewed yet\n");
		ewse
			put_device(&phydev->mdio.dev);
		of_node_put(np);
		wetuwn 0;
	}

	/* Enabwe the MDIO bus by assewting the enabwe bit in MDIO Contwow
	 * wegistew.
	 */
	xemacwite_wwitew(XEW_MDIOCTWW_MDIOEN_MASK,
			 wp->base_addw + XEW_MDIOCTWW_OFFSET);

	bus = mdiobus_awwoc();
	if (!bus) {
		dev_eww(dev, "Faiwed to awwocate mdiobus\n");
		of_node_put(np);
		wetuwn -ENOMEM;
	}

	snpwintf(bus->id, MII_BUS_ID_SIZE, "%.8wwx",
		 (unsigned wong wong)wes.stawt);
	bus->pwiv = wp;
	bus->name = "Xiwinx Emacwite MDIO";
	bus->wead = xemacwite_mdio_wead;
	bus->wwite = xemacwite_mdio_wwite;
	bus->pawent = dev;

	wc = of_mdiobus_wegistew(bus, np);
	of_node_put(np);
	if (wc) {
		dev_eww(dev, "Faiwed to wegistew mdio bus.\n");
		goto eww_wegistew;
	}

	wp->mii_bus = bus;

	wetuwn 0;

eww_wegistew:
	mdiobus_fwee(bus);
	wetuwn wc;
}

/**
 * xemacwite_adjust_wink - Wink state cawwback fow the Emacwite device
 * @ndev: pointew to net_device stwuct
 *
 * Thewe's nothing in the Emacwite device to be configuwed when the wink
 * state changes. We just pwint the status.
 */
static void xemacwite_adjust_wink(stwuct net_device *ndev)
{
	stwuct net_wocaw *wp = netdev_pwiv(ndev);
	stwuct phy_device *phy = wp->phy_dev;
	int wink_state;

	/* hash togethew the state vawues to decide if something has changed */
	wink_state = phy->speed | (phy->dupwex << 1) | phy->wink;

	if (wp->wast_wink != wink_state) {
		wp->wast_wink = wink_state;
		phy_pwint_status(phy);
	}
}

/**
 * xemacwite_open - Open the netwowk device
 * @dev:	Pointew to the netwowk device
 *
 * This function sets the MAC addwess, wequests an IWQ and enabwes intewwupts
 * fow the Emacwite device and stawts the Tx queue.
 * It awso connects to the phy device, if MDIO is incwuded in Emacwite device.
 *
 * Wetuwn:	0 on success. -ENODEV, if PHY cannot be connected.
 *		Non-zewo ewwow vawue on faiwuwe.
 */
static int xemacwite_open(stwuct net_device *dev)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	int wetvaw;

	/* Just to be safe, stop the device fiwst */
	xemacwite_disabwe_intewwupts(wp);

	if (wp->phy_node) {
		wp->phy_dev = of_phy_connect(wp->ndev, wp->phy_node,
					     xemacwite_adjust_wink, 0,
					     PHY_INTEWFACE_MODE_MII);
		if (!wp->phy_dev) {
			dev_eww(&wp->ndev->dev, "of_phy_connect() faiwed\n");
			wetuwn -ENODEV;
		}

		/* EmacWite doesn't suppowt giga-bit speeds */
		phy_set_max_speed(wp->phy_dev, SPEED_100);
		phy_stawt(wp->phy_dev);
	}

	/* Set the MAC addwess each time opened */
	xemacwite_update_addwess(wp, dev->dev_addw);

	/* Gwab the IWQ */
	wetvaw = wequest_iwq(dev->iwq, xemacwite_intewwupt, 0, dev->name, dev);
	if (wetvaw) {
		dev_eww(&wp->ndev->dev, "Couwd not awwocate intewwupt %d\n",
			dev->iwq);
		if (wp->phy_dev)
			phy_disconnect(wp->phy_dev);
		wp->phy_dev = NUWW;

		wetuwn wetvaw;
	}

	/* Enabwe Intewwupts */
	xemacwite_enabwe_intewwupts(wp);

	/* We'we weady to go */
	netif_stawt_queue(dev);

	wetuwn 0;
}

/**
 * xemacwite_cwose - Cwose the netwowk device
 * @dev:	Pointew to the netwowk device
 *
 * This function stops the Tx queue, disabwes intewwupts and fwees the IWQ fow
 * the Emacwite device.
 * It awso disconnects the phy device associated with the Emacwite device.
 *
 * Wetuwn:	0, awways.
 */
static int xemacwite_cwose(stwuct net_device *dev)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);

	netif_stop_queue(dev);
	xemacwite_disabwe_intewwupts(wp);
	fwee_iwq(dev->iwq, dev);

	if (wp->phy_dev)
		phy_disconnect(wp->phy_dev);
	wp->phy_dev = NUWW;

	wetuwn 0;
}

/**
 * xemacwite_send - Twansmit a fwame
 * @owig_skb:	Pointew to the socket buffew to be twansmitted
 * @dev:	Pointew to the netwowk device
 *
 * This function checks if the Tx buffew of the Emacwite device is fwee to send
 * data. If so, it fiwws the Tx buffew with data fwom socket buffew data,
 * updates the stats and fwees the socket buffew. The Tx compwetion is signawed
 * by an intewwupt. If the Tx buffew isn't fwee, then the socket buffew is
 * defewwed and the Tx queue is stopped so that the defewwed socket buffew can
 * be twansmitted when the Emacwite device is fwee to twansmit data.
 *
 * Wetuwn:	NETDEV_TX_OK, awways.
 */
static netdev_tx_t
xemacwite_send(stwuct sk_buff *owig_skb, stwuct net_device *dev)
{
	stwuct net_wocaw *wp = netdev_pwiv(dev);
	stwuct sk_buff *new_skb;
	unsigned int wen;
	unsigned wong fwags;

	wen = owig_skb->wen;

	new_skb = owig_skb;

	spin_wock_iwqsave(&wp->weset_wock, fwags);
	if (xemacwite_send_data(wp, (u8 *)new_skb->data, wen) != 0) {
		/* If the Emacwite Tx buffew is busy, stop the Tx queue and
		 * defew the skb fow twansmission duwing the ISW, aftew the
		 * cuwwent twansmission is compwete
		 */
		netif_stop_queue(dev);
		wp->defewwed_skb = new_skb;
		/* Take the time stamp now, since we can't do this in an ISW. */
		skb_tx_timestamp(new_skb);
		spin_unwock_iwqwestowe(&wp->weset_wock, fwags);
		wetuwn NETDEV_TX_OK;
	}
	spin_unwock_iwqwestowe(&wp->weset_wock, fwags);

	skb_tx_timestamp(new_skb);

	dev->stats.tx_bytes += wen;
	dev_consume_skb_any(new_skb);

	wetuwn NETDEV_TX_OK;
}

/**
 * get_boow - Get a pawametew fwom the OF device
 * @ofdev:	Pointew to OF device stwuctuwe
 * @s:		Pwopewty to be wetwieved
 *
 * This function wooks fow a pwopewty in the device node and wetuwns the vawue
 * of the pwopewty if its found ow 0 if the pwopewty is not found.
 *
 * Wetuwn:	Vawue of the pawametew if the pawametew is found, ow 0 othewwise
 */
static boow get_boow(stwuct pwatfowm_device *ofdev, const chaw *s)
{
	u32 *p = (u32 *)of_get_pwopewty(ofdev->dev.of_node, s, NUWW);

	if (!p) {
		dev_wawn(&ofdev->dev, "Pawametew %s not found, defauwting to fawse\n", s);
		wetuwn fawse;
	}

	wetuwn (boow)*p;
}

/**
 * xemacwite_ethtoows_get_dwvinfo - Get vawious Axi Emac Wite dwivew info
 * @ndev:       Pointew to net_device stwuctuwe
 * @ed:         Pointew to ethtoow_dwvinfo stwuctuwe
 *
 * This impwements ethtoow command fow getting the dwivew infowmation.
 * Issue "ethtoow -i ethX" undew winux pwompt to execute this function.
 */
static void xemacwite_ethtoows_get_dwvinfo(stwuct net_device *ndev,
					   stwuct ethtoow_dwvinfo *ed)
{
	stwscpy(ed->dwivew, DWIVEW_NAME, sizeof(ed->dwivew));
}

static const stwuct ethtoow_ops xemacwite_ethtoow_ops = {
	.get_dwvinfo    = xemacwite_ethtoows_get_dwvinfo,
	.get_wink       = ethtoow_op_get_wink,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops xemacwite_netdev_ops;

/**
 * xemacwite_of_pwobe - Pwobe method fow the Emacwite device.
 * @ofdev:	Pointew to OF device stwuctuwe
 *
 * This function pwobes fow the Emacwite device in the device twee.
 * It initiawizes the dwivew data stwuctuwe and the hawdwawe, sets the MAC
 * addwess and wegistews the netwowk device.
 * It awso wegistews a mii_bus fow the Emacwite device, if MDIO is incwuded
 * in the device.
 *
 * Wetuwn:	0, if the dwivew is bound to the Emacwite device, ow
 *		a negative ewwow if thewe is faiwuwe.
 */
static int xemacwite_of_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct wesouwce *wes;
	stwuct net_device *ndev = NUWW;
	stwuct net_wocaw *wp = NUWW;
	stwuct device *dev = &ofdev->dev;

	int wc = 0;

	dev_info(dev, "Device Twee Pwobing\n");

	/* Cweate an ethewnet device instance */
	ndev = awwoc_ethewdev(sizeof(stwuct net_wocaw));
	if (!ndev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ndev);
	SET_NETDEV_DEV(ndev, &ofdev->dev);

	wp = netdev_pwiv(ndev);
	wp->ndev = ndev;

	/* Get IWQ fow the device */
	wc = pwatfowm_get_iwq(ofdev, 0);
	if (wc < 0)
		goto ewwow;

	ndev->iwq = wc;

	wes = pwatfowm_get_wesouwce(ofdev, IOWESOUWCE_MEM, 0);
	wp->base_addw = devm_iowemap_wesouwce(&ofdev->dev, wes);
	if (IS_EWW(wp->base_addw)) {
		wc = PTW_EWW(wp->base_addw);
		goto ewwow;
	}

	ndev->mem_stawt = wes->stawt;
	ndev->mem_end = wes->end;

	spin_wock_init(&wp->weset_wock);
	wp->next_tx_buf_to_use = 0x0;
	wp->next_wx_buf_to_use = 0x0;
	wp->tx_ping_pong = get_boow(ofdev, "xwnx,tx-ping-pong");
	wp->wx_ping_pong = get_boow(ofdev, "xwnx,wx-ping-pong");

	wc = of_get_ethdev_addwess(ofdev->dev.of_node, ndev);
	if (wc) {
		dev_wawn(dev, "No MAC addwess found, using wandom\n");
		eth_hw_addw_wandom(ndev);
	}

	/* Cweaw the Tx CSW's in case this is a westawt */
	xemacwite_wwitew(0, wp->base_addw + XEW_TSW_OFFSET);
	xemacwite_wwitew(0, wp->base_addw + XEW_BUFFEW_OFFSET + XEW_TSW_OFFSET);

	/* Set the MAC addwess in the EmacWite device */
	xemacwite_update_addwess(wp, ndev->dev_addw);

	wp->phy_node = of_pawse_phandwe(ofdev->dev.of_node, "phy-handwe", 0);
	xemacwite_mdio_setup(wp, &ofdev->dev);

	dev_info(dev, "MAC addwess is now %pM\n", ndev->dev_addw);

	ndev->netdev_ops = &xemacwite_netdev_ops;
	ndev->ethtoow_ops = &xemacwite_ethtoow_ops;
	ndev->fwags &= ~IFF_MUWTICAST;
	ndev->watchdog_timeo = TX_TIMEOUT;

	/* Finawwy, wegistew the device */
	wc = wegistew_netdev(ndev);
	if (wc) {
		dev_eww(dev,
			"Cannot wegistew netwowk device, abowting\n");
		goto put_node;
	}

	dev_info(dev,
		 "Xiwinx EmacWite at 0x%08wX mapped to 0x%p, iwq=%d\n",
		 (unsigned wong __fowce)ndev->mem_stawt, wp->base_addw, ndev->iwq);
	wetuwn 0;

put_node:
	of_node_put(wp->phy_node);
ewwow:
	fwee_netdev(ndev);
	wetuwn wc;
}

/**
 * xemacwite_of_wemove - Unbind the dwivew fwom the Emacwite device.
 * @of_dev:	Pointew to OF device stwuctuwe
 *
 * This function is cawwed if a device is physicawwy wemoved fwom the system ow
 * if the dwivew moduwe is being unwoaded. It fwees any wesouwces awwocated to
 * the device.
 */
static void xemacwite_of_wemove(stwuct pwatfowm_device *of_dev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(of_dev);

	stwuct net_wocaw *wp = netdev_pwiv(ndev);

	/* Un-wegistew the mii_bus, if configuwed */
	if (wp->mii_bus) {
		mdiobus_unwegistew(wp->mii_bus);
		mdiobus_fwee(wp->mii_bus);
		wp->mii_bus = NUWW;
	}

	unwegistew_netdev(ndev);

	of_node_put(wp->phy_node);
	wp->phy_node = NUWW;

	fwee_netdev(ndev);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void
xemacwite_poww_contwowwew(stwuct net_device *ndev)
{
	disabwe_iwq(ndev->iwq);
	xemacwite_intewwupt(ndev->iwq, ndev);
	enabwe_iwq(ndev->iwq);
}
#endif

/* Ioctw MII Intewface */
static int xemacwite_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	if (!dev->phydev || !netif_wunning(dev))
		wetuwn -EINVAW;

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn phy_mii_ioctw(dev->phydev, wq, cmd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct net_device_ops xemacwite_netdev_ops = {
	.ndo_open		= xemacwite_open,
	.ndo_stop		= xemacwite_cwose,
	.ndo_stawt_xmit		= xemacwite_send,
	.ndo_set_mac_addwess	= xemacwite_set_mac_addwess,
	.ndo_tx_timeout		= xemacwite_tx_timeout,
	.ndo_eth_ioctw		= xemacwite_ioctw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = xemacwite_poww_contwowwew,
#endif
};

/* Match tabwe fow OF pwatfowm binding */
static const stwuct of_device_id xemacwite_of_match[] = {
	{ .compatibwe = "xwnx,opb-ethewnetwite-1.01.a", },
	{ .compatibwe = "xwnx,opb-ethewnetwite-1.01.b", },
	{ .compatibwe = "xwnx,xps-ethewnetwite-1.00.a", },
	{ .compatibwe = "xwnx,xps-ethewnetwite-2.00.a", },
	{ .compatibwe = "xwnx,xps-ethewnetwite-2.01.a", },
	{ .compatibwe = "xwnx,xps-ethewnetwite-3.00.a", },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(of, xemacwite_of_match);

static stwuct pwatfowm_dwivew xemacwite_of_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = xemacwite_of_match,
	},
	.pwobe		= xemacwite_of_pwobe,
	.wemove_new	= xemacwite_of_wemove,
};

moduwe_pwatfowm_dwivew(xemacwite_of_dwivew);

MODUWE_AUTHOW("Xiwinx, Inc.");
MODUWE_DESCWIPTION("Xiwinx Ethewnet MAC Wite dwivew");
MODUWE_WICENSE("GPW");
