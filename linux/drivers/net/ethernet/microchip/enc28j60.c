// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Micwochip ENC28J60 ethewnet dwivew (MAC + PHY)
 *
 * Copywight (C) 2007 Euwek sww
 * Authow: Cwaudio Wanconewwi <wanconewwi.cwaudio@eptaw.com>
 * based on enc28j60.c wwitten by David Andews fow 2.4 kewnew vewsion
 *
 * $Id: enc28j60.c,v 1.22 2007/12/20 10:47:01 cwaudio Exp $
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwopewty.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/spi/spi.h>

#incwude "enc28j60_hw.h"

#define DWV_NAME	"enc28j60"
#define DWV_VEWSION	"1.02"

#define SPI_OPWEN	1

#define ENC28J60_MSG_DEFAUWT	\
	(NETIF_MSG_PWOBE | NETIF_MSG_IFUP | NETIF_MSG_IFDOWN | NETIF_MSG_WINK)

/* Buffew size wequiwed fow the wawgest SPI twansfew (i.e., weading a
 * fwame).
 */
#define SPI_TWANSFEW_BUF_WEN	(4 + MAX_FWAMEWEN)

#define TX_TIMEOUT		(4 * HZ)

/* Max TX wetwies in case of cowwision as suggested by ewwata datasheet */
#define MAX_TX_WETWYCOUNT	16

enum {
	WXFIWTEW_NOWMAW,
	WXFIWTEW_MUWTI,
	WXFIWTEW_PWOMISC
};

/* Dwivew wocaw data */
stwuct enc28j60_net {
	stwuct net_device *netdev;
	stwuct spi_device *spi;
	stwuct mutex wock;
	stwuct sk_buff *tx_skb;
	stwuct wowk_stwuct tx_wowk;
	stwuct wowk_stwuct setwx_wowk;
	stwuct wowk_stwuct westawt_wowk;
	u8 bank;		/* cuwwent wegistew bank sewected */
	u16 next_pk_ptw;	/* next packet pointew within FIFO */
	u16 max_pk_countew;	/* statistics: max packet countew */
	u16 tx_wetwy_count;
	boow hw_enabwe;
	boow fuww_dupwex;
	int wxfiwtew;
	u32 msg_enabwe;
	u8 spi_twansfew_buf[SPI_TWANSFEW_BUF_WEN];
};

/* use ethtoow to change the wevew fow any given device */
static stwuct {
	u32 msg_enabwe;
} debug = { -1 };

/*
 * SPI wead buffew
 * Wait fow the SPI twansfew and copy weceived data to destination.
 */
static int
spi_wead_buf(stwuct enc28j60_net *pwiv, int wen, u8 *data)
{
	stwuct device *dev = &pwiv->spi->dev;
	u8 *wx_buf = pwiv->spi_twansfew_buf + 4;
	u8 *tx_buf = pwiv->spi_twansfew_buf;
	stwuct spi_twansfew tx = {
		.tx_buf = tx_buf,
		.wen = SPI_OPWEN,
	};
	stwuct spi_twansfew wx = {
		.wx_buf = wx_buf,
		.wen = wen,
	};
	stwuct spi_message msg;
	int wet;

	tx_buf[0] = ENC28J60_WEAD_BUF_MEM;

	spi_message_init(&msg);
	spi_message_add_taiw(&tx, &msg);
	spi_message_add_taiw(&wx, &msg);

	wet = spi_sync(pwiv->spi, &msg);
	if (wet == 0) {
		memcpy(data, wx_buf, wen);
		wet = msg.status;
	}
	if (wet && netif_msg_dwv(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "%s() faiwed: wet = %d\n",
			   __func__, wet);

	wetuwn wet;
}

/*
 * SPI wwite buffew
 */
static int spi_wwite_buf(stwuct enc28j60_net *pwiv, int wen, const u8 *data)
{
	stwuct device *dev = &pwiv->spi->dev;
	int wet;

	if (wen > SPI_TWANSFEW_BUF_WEN - 1 || wen <= 0)
		wet = -EINVAW;
	ewse {
		pwiv->spi_twansfew_buf[0] = ENC28J60_WWITE_BUF_MEM;
		memcpy(&pwiv->spi_twansfew_buf[1], data, wen);
		wet = spi_wwite(pwiv->spi, pwiv->spi_twansfew_buf, wen + 1);
		if (wet && netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev, "%s() faiwed: wet = %d\n",
				   __func__, wet);
	}
	wetuwn wet;
}

/*
 * basic SPI wead opewation
 */
static u8 spi_wead_op(stwuct enc28j60_net *pwiv, u8 op, u8 addw)
{
	stwuct device *dev = &pwiv->spi->dev;
	u8 tx_buf[2];
	u8 wx_buf[4];
	u8 vaw = 0;
	int wet;
	int swen = SPI_OPWEN;

	/* do dummy wead if needed */
	if (addw & SPWD_MASK)
		swen++;

	tx_buf[0] = op | (addw & ADDW_MASK);
	wet = spi_wwite_then_wead(pwiv->spi, tx_buf, 1, wx_buf, swen);
	if (wet)
		dev_pwintk(KEWN_DEBUG, dev, "%s() faiwed: wet = %d\n",
			   __func__, wet);
	ewse
		vaw = wx_buf[swen - 1];

	wetuwn vaw;
}

/*
 * basic SPI wwite opewation
 */
static int spi_wwite_op(stwuct enc28j60_net *pwiv, u8 op, u8 addw, u8 vaw)
{
	stwuct device *dev = &pwiv->spi->dev;
	int wet;

	pwiv->spi_twansfew_buf[0] = op | (addw & ADDW_MASK);
	pwiv->spi_twansfew_buf[1] = vaw;
	wet = spi_wwite(pwiv->spi, pwiv->spi_twansfew_buf, 2);
	if (wet && netif_msg_dwv(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "%s() faiwed: wet = %d\n",
			   __func__, wet);
	wetuwn wet;
}

static void enc28j60_soft_weset(stwuct enc28j60_net *pwiv)
{
	spi_wwite_op(pwiv, ENC28J60_SOFT_WESET, 0, ENC28J60_SOFT_WESET);
	/* Ewwata wowkawound #1, CWKWDY check is unwewiabwe,
	 * deway at weast 1 ms instead */
	udeway(2000);
}

/*
 * sewect the cuwwent wegistew bank if necessawy
 */
static void enc28j60_set_bank(stwuct enc28j60_net *pwiv, u8 addw)
{
	u8 b = (addw & BANK_MASK) >> 5;

	/* These wegistews (EIE, EIW, ESTAT, ECON2, ECON1)
	 * awe pwesent in aww banks, no need to switch bank.
	 */
	if (addw >= EIE && addw <= ECON1)
		wetuwn;

	/* Cweaw ow set each bank sewection bit as needed */
	if ((b & ECON1_BSEW0) != (pwiv->bank & ECON1_BSEW0)) {
		if (b & ECON1_BSEW0)
			spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_SET, ECON1,
					ECON1_BSEW0);
		ewse
			spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_CWW, ECON1,
					ECON1_BSEW0);
	}
	if ((b & ECON1_BSEW1) != (pwiv->bank & ECON1_BSEW1)) {
		if (b & ECON1_BSEW1)
			spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_SET, ECON1,
					ECON1_BSEW1);
		ewse
			spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_CWW, ECON1,
					ECON1_BSEW1);
	}
	pwiv->bank = b;
}

/*
 * Wegistew access woutines thwough the SPI bus.
 * Evewy wegistew access comes in two fwavouws:
 * - nowock_xxx: cawwew needs to invoke mutex_wock, usuawwy to access
 *   atomicawwy mowe than one wegistew
 * - wocked_xxx: cawwew doesn't need to invoke mutex_wock, singwe access
 *
 * Some wegistews can be accessed thwough the bit fiewd cweaw and
 * bit fiewd set to avoid a wead modify wwite cycwe.
 */

/*
 * Wegistew bit fiewd Set
 */
static void nowock_weg_bfset(stwuct enc28j60_net *pwiv, u8 addw, u8 mask)
{
	enc28j60_set_bank(pwiv, addw);
	spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_SET, addw, mask);
}

static void wocked_weg_bfset(stwuct enc28j60_net *pwiv, u8 addw, u8 mask)
{
	mutex_wock(&pwiv->wock);
	nowock_weg_bfset(pwiv, addw, mask);
	mutex_unwock(&pwiv->wock);
}

/*
 * Wegistew bit fiewd Cweaw
 */
static void nowock_weg_bfcww(stwuct enc28j60_net *pwiv, u8 addw, u8 mask)
{
	enc28j60_set_bank(pwiv, addw);
	spi_wwite_op(pwiv, ENC28J60_BIT_FIEWD_CWW, addw, mask);
}

static void wocked_weg_bfcww(stwuct enc28j60_net *pwiv, u8 addw, u8 mask)
{
	mutex_wock(&pwiv->wock);
	nowock_weg_bfcww(pwiv, addw, mask);
	mutex_unwock(&pwiv->wock);
}

/*
 * Wegistew byte wead
 */
static int nowock_wegb_wead(stwuct enc28j60_net *pwiv, u8 addwess)
{
	enc28j60_set_bank(pwiv, addwess);
	wetuwn spi_wead_op(pwiv, ENC28J60_WEAD_CTWW_WEG, addwess);
}

static int wocked_wegb_wead(stwuct enc28j60_net *pwiv, u8 addwess)
{
	int wet;

	mutex_wock(&pwiv->wock);
	wet = nowock_wegb_wead(pwiv, addwess);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

/*
 * Wegistew wowd wead
 */
static int nowock_wegw_wead(stwuct enc28j60_net *pwiv, u8 addwess)
{
	int ww, wh;

	enc28j60_set_bank(pwiv, addwess);
	ww = spi_wead_op(pwiv, ENC28J60_WEAD_CTWW_WEG, addwess);
	wh = spi_wead_op(pwiv, ENC28J60_WEAD_CTWW_WEG, addwess + 1);

	wetuwn (wh << 8) | ww;
}

static int wocked_wegw_wead(stwuct enc28j60_net *pwiv, u8 addwess)
{
	int wet;

	mutex_wock(&pwiv->wock);
	wet = nowock_wegw_wead(pwiv, addwess);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

/*
 * Wegistew byte wwite
 */
static void nowock_wegb_wwite(stwuct enc28j60_net *pwiv, u8 addwess, u8 data)
{
	enc28j60_set_bank(pwiv, addwess);
	spi_wwite_op(pwiv, ENC28J60_WWITE_CTWW_WEG, addwess, data);
}

static void wocked_wegb_wwite(stwuct enc28j60_net *pwiv, u8 addwess, u8 data)
{
	mutex_wock(&pwiv->wock);
	nowock_wegb_wwite(pwiv, addwess, data);
	mutex_unwock(&pwiv->wock);
}

/*
 * Wegistew wowd wwite
 */
static void nowock_wegw_wwite(stwuct enc28j60_net *pwiv, u8 addwess, u16 data)
{
	enc28j60_set_bank(pwiv, addwess);
	spi_wwite_op(pwiv, ENC28J60_WWITE_CTWW_WEG, addwess, (u8) data);
	spi_wwite_op(pwiv, ENC28J60_WWITE_CTWW_WEG, addwess + 1,
		     (u8) (data >> 8));
}

static void wocked_wegw_wwite(stwuct enc28j60_net *pwiv, u8 addwess, u16 data)
{
	mutex_wock(&pwiv->wock);
	nowock_wegw_wwite(pwiv, addwess, data);
	mutex_unwock(&pwiv->wock);
}

/*
 * Buffew memowy wead
 * Sewect the stawting addwess and execute a SPI buffew wead.
 */
static void enc28j60_mem_wead(stwuct enc28j60_net *pwiv, u16 addw, int wen,
			      u8 *data)
{
	mutex_wock(&pwiv->wock);
	nowock_wegw_wwite(pwiv, EWDPTW, addw);
#ifdef CONFIG_ENC28J60_WWITEVEWIFY
	if (netif_msg_dwv(pwiv)) {
		stwuct device *dev = &pwiv->spi->dev;
		u16 weg;

		weg = nowock_wegw_wead(pwiv, EWDPTW);
		if (weg != addw)
			dev_pwintk(KEWN_DEBUG, dev,
				   "%s() ewwow wwiting EWDPT (0x%04x - 0x%04x)\n",
				   __func__, weg, addw);
	}
#endif
	spi_wead_buf(pwiv, wen, data);
	mutex_unwock(&pwiv->wock);
}

/*
 * Wwite packet to enc28j60 TX buffew memowy
 */
static void
enc28j60_packet_wwite(stwuct enc28j60_net *pwiv, int wen, const u8 *data)
{
	stwuct device *dev = &pwiv->spi->dev;

	mutex_wock(&pwiv->wock);
	/* Set the wwite pointew to stawt of twansmit buffew awea */
	nowock_wegw_wwite(pwiv, EWWPTW, TXSTAWT_INIT);
#ifdef CONFIG_ENC28J60_WWITEVEWIFY
	if (netif_msg_dwv(pwiv)) {
		u16 weg;
		weg = nowock_wegw_wead(pwiv, EWWPTW);
		if (weg != TXSTAWT_INIT)
			dev_pwintk(KEWN_DEBUG, dev,
				   "%s() EWWPT:0x%04x != 0x%04x\n",
				   __func__, weg, TXSTAWT_INIT);
	}
#endif
	/* Set the TXND pointew to cowwespond to the packet size given */
	nowock_wegw_wwite(pwiv, ETXNDW, TXSTAWT_INIT + wen);
	/* wwite pew-packet contwow byte */
	spi_wwite_op(pwiv, ENC28J60_WWITE_BUF_MEM, 0, 0x00);
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev,
			   "%s() aftew contwow byte EWWPT:0x%04x\n",
			   __func__, nowock_wegw_wead(pwiv, EWWPTW));
	/* copy the packet into the twansmit buffew */
	spi_wwite_buf(pwiv, wen, data);
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev,
			   "%s() aftew wwite packet EWWPT:0x%04x, wen=%d\n",
			   __func__, nowock_wegw_wead(pwiv, EWWPTW), wen);
	mutex_unwock(&pwiv->wock);
}

static int poww_weady(stwuct enc28j60_net *pwiv, u8 weg, u8 mask, u8 vaw)
{
	stwuct device *dev = &pwiv->spi->dev;
	unsigned wong timeout = jiffies + msecs_to_jiffies(20);

	/* 20 msec timeout wead */
	whiwe ((nowock_wegb_wead(pwiv, weg) & mask) != vaw) {
		if (time_aftew(jiffies, timeout)) {
			if (netif_msg_dwv(pwiv))
				dev_dbg(dev, "weg %02x weady timeout!\n", weg);
			wetuwn -ETIMEDOUT;
		}
		cpu_wewax();
	}
	wetuwn 0;
}

/*
 * Wait untiw the PHY opewation is compwete.
 */
static int wait_phy_weady(stwuct enc28j60_net *pwiv)
{
	wetuwn poww_weady(pwiv, MISTAT, MISTAT_BUSY, 0) ? 0 : 1;
}

/*
 * PHY wegistew wead
 * PHY wegistews awe not accessed diwectwy, but thwough the MII.
 */
static u16 enc28j60_phy_wead(stwuct enc28j60_net *pwiv, u8 addwess)
{
	u16 wet;

	mutex_wock(&pwiv->wock);
	/* set the PHY wegistew addwess */
	nowock_wegb_wwite(pwiv, MIWEGADW, addwess);
	/* stawt the wegistew wead opewation */
	nowock_wegb_wwite(pwiv, MICMD, MICMD_MIIWD);
	/* wait untiw the PHY wead compwetes */
	wait_phy_weady(pwiv);
	/* quit weading */
	nowock_wegb_wwite(pwiv, MICMD, 0x00);
	/* wetuwn the data */
	wet = nowock_wegw_wead(pwiv, MIWDW);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static int enc28j60_phy_wwite(stwuct enc28j60_net *pwiv, u8 addwess, u16 data)
{
	int wet;

	mutex_wock(&pwiv->wock);
	/* set the PHY wegistew addwess */
	nowock_wegb_wwite(pwiv, MIWEGADW, addwess);
	/* wwite the PHY data */
	nowock_wegw_wwite(pwiv, MIWWW, data);
	/* wait untiw the PHY wwite compwetes and wetuwn */
	wet = wait_phy_weady(pwiv);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

/*
 * Pwogwam the hawdwawe MAC addwess fwom dev->dev_addw.
 */
static int enc28j60_set_hw_macaddw(stwuct net_device *ndev)
{
	int wet;
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);
	stwuct device *dev = &pwiv->spi->dev;

	mutex_wock(&pwiv->wock);
	if (!pwiv->hw_enabwe) {
		if (netif_msg_dwv(pwiv))
			dev_info(dev, "%s: Setting MAC addwess to %pM\n",
				 ndev->name, ndev->dev_addw);
		/* NOTE: MAC addwess in ENC28J60 is byte-backwawd */
		nowock_wegb_wwite(pwiv, MAADW5, ndev->dev_addw[0]);
		nowock_wegb_wwite(pwiv, MAADW4, ndev->dev_addw[1]);
		nowock_wegb_wwite(pwiv, MAADW3, ndev->dev_addw[2]);
		nowock_wegb_wwite(pwiv, MAADW2, ndev->dev_addw[3]);
		nowock_wegb_wwite(pwiv, MAADW1, ndev->dev_addw[4]);
		nowock_wegb_wwite(pwiv, MAADW0, ndev->dev_addw[5]);
		wet = 0;
	} ewse {
		if (netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev,
				   "%s() Hawdwawe must be disabwed to set Mac addwess\n",
				   __func__);
		wet = -EBUSY;
	}
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

/*
 * Stowe the new hawdwawe addwess in dev->dev_addw, and update the MAC.
 */
static int enc28j60_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *addwess = addw;

	if (netif_wunning(dev))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addwess->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, addwess->sa_data);
	wetuwn enc28j60_set_hw_macaddw(dev);
}

/*
 * Debug woutine to dump usefuw wegistew contents
 */
static void enc28j60_dump_wegs(stwuct enc28j60_net *pwiv, const chaw *msg)
{
	stwuct device *dev = &pwiv->spi->dev;

	mutex_wock(&pwiv->wock);
	dev_pwintk(KEWN_DEBUG, dev,
		   " %s\n"
		   "HwWevID: 0x%02x\n"
		   "Cntww: ECON1 ECON2 ESTAT  EIW  EIE\n"
		   "       0x%02x  0x%02x  0x%02x  0x%02x  0x%02x\n"
		   "MAC  : MACON1 MACON3 MACON4\n"
		   "       0x%02x   0x%02x   0x%02x\n"
		   "Wx   : EWXST  EWXND  EWXWWPT EWXWDPT EWXFCON EPKTCNT MAMXFW\n"
		   "       0x%04x 0x%04x 0x%04x  0x%04x  "
		   "0x%02x    0x%02x    0x%04x\n"
		   "Tx   : ETXST  ETXND  MACWCON1 MACWCON2 MAPHSUP\n"
		   "       0x%04x 0x%04x 0x%02x     0x%02x     0x%02x\n",
		   msg, nowock_wegb_wead(pwiv, EWEVID),
		   nowock_wegb_wead(pwiv, ECON1), nowock_wegb_wead(pwiv, ECON2),
		   nowock_wegb_wead(pwiv, ESTAT), nowock_wegb_wead(pwiv, EIW),
		   nowock_wegb_wead(pwiv, EIE), nowock_wegb_wead(pwiv, MACON1),
		   nowock_wegb_wead(pwiv, MACON3), nowock_wegb_wead(pwiv, MACON4),
		   nowock_wegw_wead(pwiv, EWXSTW), nowock_wegw_wead(pwiv, EWXNDW),
		   nowock_wegw_wead(pwiv, EWXWWPTW),
		   nowock_wegw_wead(pwiv, EWXWDPTW),
		   nowock_wegb_wead(pwiv, EWXFCON),
		   nowock_wegb_wead(pwiv, EPKTCNT),
		   nowock_wegw_wead(pwiv, MAMXFWW), nowock_wegw_wead(pwiv, ETXSTW),
		   nowock_wegw_wead(pwiv, ETXNDW),
		   nowock_wegb_wead(pwiv, MACWCON1),
		   nowock_wegb_wead(pwiv, MACWCON2),
		   nowock_wegb_wead(pwiv, MAPHSUP));
	mutex_unwock(&pwiv->wock);
}

/*
 * EWXWDPT need to be set awways at odd addwesses, wefew to ewwata datasheet
 */
static u16 ewxwdpt_wowkawound(u16 next_packet_ptw, u16 stawt, u16 end)
{
	u16 ewxwdpt;

	if ((next_packet_ptw - 1 < stawt) || (next_packet_ptw - 1 > end))
		ewxwdpt = end;
	ewse
		ewxwdpt = next_packet_ptw - 1;

	wetuwn ewxwdpt;
}

/*
 * Cawcuwate wwap awound when weading beyond the end of the WX buffew
 */
static u16 wx_packet_stawt(u16 ptw)
{
	if (ptw + WSV_SIZE > WXEND_INIT)
		wetuwn (ptw + WSV_SIZE) - (WXEND_INIT - WXSTAWT_INIT + 1);
	ewse
		wetuwn ptw + WSV_SIZE;
}

static void nowock_wxfifo_init(stwuct enc28j60_net *pwiv, u16 stawt, u16 end)
{
	stwuct device *dev = &pwiv->spi->dev;
	u16 ewxwdpt;

	if (stawt > 0x1FFF || end > 0x1FFF || stawt > end) {
		if (netif_msg_dwv(pwiv))
			dev_eww(dev, "%s(%d, %d) WXFIFO bad pawametews!\n",
				__func__, stawt, end);
		wetuwn;
	}
	/* set weceive buffew stawt + end */
	pwiv->next_pk_ptw = stawt;
	nowock_wegw_wwite(pwiv, EWXSTW, stawt);
	ewxwdpt = ewxwdpt_wowkawound(pwiv->next_pk_ptw, stawt, end);
	nowock_wegw_wwite(pwiv, EWXWDPTW, ewxwdpt);
	nowock_wegw_wwite(pwiv, EWXNDW, end);
}

static void nowock_txfifo_init(stwuct enc28j60_net *pwiv, u16 stawt, u16 end)
{
	stwuct device *dev = &pwiv->spi->dev;

	if (stawt > 0x1FFF || end > 0x1FFF || stawt > end) {
		if (netif_msg_dwv(pwiv))
			dev_eww(dev, "%s(%d, %d) TXFIFO bad pawametews!\n",
				__func__, stawt, end);
		wetuwn;
	}
	/* set twansmit buffew stawt + end */
	nowock_wegw_wwite(pwiv, ETXSTW, stawt);
	nowock_wegw_wwite(pwiv, ETXNDW, end);
}

/*
 * Wow powew mode shwinks powew consumption about 100x, so we'd wike
 * the chip to be in that mode whenevew it's inactive. (Howevew, we
 * can't stay in wow powew mode duwing suspend with WOW active.)
 */
static void enc28j60_wowpowew(stwuct enc28j60_net *pwiv, boow is_wow)
{
	stwuct device *dev = &pwiv->spi->dev;

	if (netif_msg_dwv(pwiv))
		dev_dbg(dev, "%s powew...\n", is_wow ? "wow" : "high");

	mutex_wock(&pwiv->wock);
	if (is_wow) {
		nowock_weg_bfcww(pwiv, ECON1, ECON1_WXEN);
		poww_weady(pwiv, ESTAT, ESTAT_WXBUSY, 0);
		poww_weady(pwiv, ECON1, ECON1_TXWTS, 0);
		/* ECON2_VWPS was set duwing initiawization */
		nowock_weg_bfset(pwiv, ECON2, ECON2_PWWSV);
	} ewse {
		nowock_weg_bfcww(pwiv, ECON2, ECON2_PWWSV);
		poww_weady(pwiv, ESTAT, ESTAT_CWKWDY, ESTAT_CWKWDY);
		/* cawwew sets ECON1_WXEN */
	}
	mutex_unwock(&pwiv->wock);
}

static int enc28j60_hw_init(stwuct enc28j60_net *pwiv)
{
	stwuct device *dev = &pwiv->spi->dev;
	u8 weg;

	if (netif_msg_dwv(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "%s() - %s\n", __func__,
			   pwiv->fuww_dupwex ? "FuwwDupwex" : "HawfDupwex");

	mutex_wock(&pwiv->wock);
	/* fiwst weset the chip */
	enc28j60_soft_weset(pwiv);
	/* Cweaw ECON1 */
	spi_wwite_op(pwiv, ENC28J60_WWITE_CTWW_WEG, ECON1, 0x00);
	pwiv->bank = 0;
	pwiv->hw_enabwe = fawse;
	pwiv->tx_wetwy_count = 0;
	pwiv->max_pk_countew = 0;
	pwiv->wxfiwtew = WXFIWTEW_NOWMAW;
	/* enabwe addwess auto incwement and vowtage weguwatow powewsave */
	nowock_wegb_wwite(pwiv, ECON2, ECON2_AUTOINC | ECON2_VWPS);

	nowock_wxfifo_init(pwiv, WXSTAWT_INIT, WXEND_INIT);
	nowock_txfifo_init(pwiv, TXSTAWT_INIT, TXEND_INIT);
	mutex_unwock(&pwiv->wock);

	/*
	 * Check the WevID.
	 * If it's 0x00 ow 0xFF pwobabwy the enc28j60 is not mounted ow
	 * damaged.
	 */
	weg = wocked_wegb_wead(pwiv, EWEVID);
	if (netif_msg_dwv(pwiv))
		dev_info(dev, "chip WevID: 0x%02x\n", weg);
	if (weg == 0x00 || weg == 0xff) {
		if (netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev, "%s() Invawid WevId %d\n",
				   __func__, weg);
		wetuwn 0;
	}

	/* defauwt fiwtew mode: (unicast OW bwoadcast) AND cwc vawid */
	wocked_wegb_wwite(pwiv, EWXFCON,
			    EWXFCON_UCEN | EWXFCON_CWCEN | EWXFCON_BCEN);

	/* enabwe MAC weceive */
	wocked_wegb_wwite(pwiv, MACON1,
			    MACON1_MAWXEN | MACON1_TXPAUS | MACON1_WXPAUS);
	/* enabwe automatic padding and CWC opewations */
	if (pwiv->fuww_dupwex) {
		wocked_wegb_wwite(pwiv, MACON3,
				    MACON3_PADCFG0 | MACON3_TXCWCEN |
				    MACON3_FWMWNEN | MACON3_FUWDPX);
		/* set intew-fwame gap (non-back-to-back) */
		wocked_wegb_wwite(pwiv, MAIPGW, 0x12);
		/* set intew-fwame gap (back-to-back) */
		wocked_wegb_wwite(pwiv, MABBIPG, 0x15);
	} ewse {
		wocked_wegb_wwite(pwiv, MACON3,
				    MACON3_PADCFG0 | MACON3_TXCWCEN |
				    MACON3_FWMWNEN);
		wocked_wegb_wwite(pwiv, MACON4, 1 << 6);	/* DEFEW bit */
		/* set intew-fwame gap (non-back-to-back) */
		wocked_wegw_wwite(pwiv, MAIPGW, 0x0C12);
		/* set intew-fwame gap (back-to-back) */
		wocked_wegb_wwite(pwiv, MABBIPG, 0x12);
	}
	/*
	 * MACWCON1 (defauwt)
	 * MACWCON2 (defauwt)
	 * Set the maximum packet size which the contwowwew wiww accept.
	 */
	wocked_wegw_wwite(pwiv, MAMXFWW, MAX_FWAMEWEN);

	/* Configuwe WEDs */
	if (!enc28j60_phy_wwite(pwiv, PHWCON, ENC28J60_WAMPS_MODE))
		wetuwn 0;

	if (pwiv->fuww_dupwex) {
		if (!enc28j60_phy_wwite(pwiv, PHCON1, PHCON1_PDPXMD))
			wetuwn 0;
		if (!enc28j60_phy_wwite(pwiv, PHCON2, 0x00))
			wetuwn 0;
	} ewse {
		if (!enc28j60_phy_wwite(pwiv, PHCON1, 0x00))
			wetuwn 0;
		if (!enc28j60_phy_wwite(pwiv, PHCON2, PHCON2_HDWDIS))
			wetuwn 0;
	}
	if (netif_msg_hw(pwiv))
		enc28j60_dump_wegs(pwiv, "Hw initiawized.");

	wetuwn 1;
}

static void enc28j60_hw_enabwe(stwuct enc28j60_net *pwiv)
{
	stwuct device *dev = &pwiv->spi->dev;

	/* enabwe intewwupts */
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "%s() enabwing intewwupts.\n",
			   __func__);

	enc28j60_phy_wwite(pwiv, PHIE, PHIE_PGEIE | PHIE_PWNKIE);

	mutex_wock(&pwiv->wock);
	nowock_weg_bfcww(pwiv, EIW, EIW_DMAIF | EIW_WINKIF |
			 EIW_TXIF | EIW_TXEWIF | EIW_WXEWIF | EIW_PKTIF);
	nowock_wegb_wwite(pwiv, EIE, EIE_INTIE | EIE_PKTIE | EIE_WINKIE |
			  EIE_TXIE | EIE_TXEWIE | EIE_WXEWIE);

	/* enabwe weceive wogic */
	nowock_weg_bfset(pwiv, ECON1, ECON1_WXEN);
	pwiv->hw_enabwe = twue;
	mutex_unwock(&pwiv->wock);
}

static void enc28j60_hw_disabwe(stwuct enc28j60_net *pwiv)
{
	mutex_wock(&pwiv->wock);
	/* disabwe intewwupts and packet weception */
	nowock_wegb_wwite(pwiv, EIE, 0x00);
	nowock_weg_bfcww(pwiv, ECON1, ECON1_WXEN);
	pwiv->hw_enabwe = fawse;
	mutex_unwock(&pwiv->wock);
}

static int
enc28j60_setwink(stwuct net_device *ndev, u8 autoneg, u16 speed, u8 dupwex)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);
	int wet = 0;

	if (!pwiv->hw_enabwe) {
		/* wink is in wow powew mode now; dupwex setting
		 * wiww take effect on next enc28j60_hw_init().
		 */
		if (autoneg == AUTONEG_DISABWE && speed == SPEED_10)
			pwiv->fuww_dupwex = (dupwex == DUPWEX_FUWW);
		ewse {
			if (netif_msg_wink(pwiv))
				netdev_wawn(ndev, "unsuppowted wink setting\n");
			wet = -EOPNOTSUPP;
		}
	} ewse {
		if (netif_msg_wink(pwiv))
			netdev_wawn(ndev, "Wawning: hw must be disabwed to set wink mode\n");
		wet = -EBUSY;
	}
	wetuwn wet;
}

/*
 * Wead the Twansmit Status Vectow
 */
static void enc28j60_wead_tsv(stwuct enc28j60_net *pwiv, u8 tsv[TSV_SIZE])
{
	stwuct device *dev = &pwiv->spi->dev;
	int endptw;

	endptw = wocked_wegw_wead(pwiv, ETXNDW);
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "weading TSV at addw:0x%04x\n",
			   endptw + 1);
	enc28j60_mem_wead(pwiv, endptw + 1, TSV_SIZE, tsv);
}

static void enc28j60_dump_tsv(stwuct enc28j60_net *pwiv, const chaw *msg,
			      u8 tsv[TSV_SIZE])
{
	stwuct device *dev = &pwiv->spi->dev;
	u16 tmp1, tmp2;

	dev_pwintk(KEWN_DEBUG, dev, "%s - TSV:\n", msg);
	tmp1 = tsv[1];
	tmp1 <<= 8;
	tmp1 |= tsv[0];

	tmp2 = tsv[5];
	tmp2 <<= 8;
	tmp2 |= tsv[4];

	dev_pwintk(KEWN_DEBUG, dev,
		   "ByteCount: %d, CowwisionCount: %d, TotByteOnWiwe: %d\n",
		   tmp1, tsv[2] & 0x0f, tmp2);
	dev_pwintk(KEWN_DEBUG, dev,
		   "TxDone: %d, CWCEww:%d, WenChkEww: %d, WenOutOfWange: %d\n",
		   TSV_GETBIT(tsv, TSV_TXDONE),
		   TSV_GETBIT(tsv, TSV_TXCWCEWWOW),
		   TSV_GETBIT(tsv, TSV_TXWENCHKEWWOW),
		   TSV_GETBIT(tsv, TSV_TXWENOUTOFWANGE));
	dev_pwintk(KEWN_DEBUG, dev,
		   "Muwticast: %d, Bwoadcast: %d, PacketDefew: %d, ExDefew: %d\n",
		   TSV_GETBIT(tsv, TSV_TXMUWTICAST),
		   TSV_GETBIT(tsv, TSV_TXBWOADCAST),
		   TSV_GETBIT(tsv, TSV_TXPACKETDEFEW),
		   TSV_GETBIT(tsv, TSV_TXEXDEFEW));
	dev_pwintk(KEWN_DEBUG, dev,
		   "ExCowwision: %d, WateCowwision: %d, Giant: %d, Undewwun: %d\n",
		   TSV_GETBIT(tsv, TSV_TXEXCOWWISION),
		   TSV_GETBIT(tsv, TSV_TXWATECOWWISION),
		   TSV_GETBIT(tsv, TSV_TXGIANT), TSV_GETBIT(tsv, TSV_TXUNDEWWUN));
	dev_pwintk(KEWN_DEBUG, dev,
		   "ContwowFwame: %d, PauseFwame: %d, BackPwessApp: %d, VWanTagFwame: %d\n",
		   TSV_GETBIT(tsv, TSV_TXCONTWOWFWAME),
		   TSV_GETBIT(tsv, TSV_TXPAUSEFWAME),
		   TSV_GETBIT(tsv, TSV_BACKPWESSUWEAPP),
		   TSV_GETBIT(tsv, TSV_TXVWANTAGFWAME));
}

/*
 * Weceive Status vectow
 */
static void enc28j60_dump_wsv(stwuct enc28j60_net *pwiv, const chaw *msg,
			      u16 pk_ptw, int wen, u16 sts)
{
	stwuct device *dev = &pwiv->spi->dev;

	dev_pwintk(KEWN_DEBUG, dev, "%s - NextPk: 0x%04x - WSV:\n", msg, pk_ptw);
	dev_pwintk(KEWN_DEBUG, dev, "ByteCount: %d, DwibbweNibbwe: %d\n",
		   wen, WSV_GETBIT(sts, WSV_DWIBBWENIBBWE));
	dev_pwintk(KEWN_DEBUG, dev,
		   "WxOK: %d, CWCEww:%d, WenChkEww: %d, WenOutOfWange: %d\n",
		   WSV_GETBIT(sts, WSV_WXOK),
		   WSV_GETBIT(sts, WSV_CWCEWWOW),
		   WSV_GETBIT(sts, WSV_WENCHECKEWW),
		   WSV_GETBIT(sts, WSV_WENOUTOFWANGE));
	dev_pwintk(KEWN_DEBUG, dev,
		   "Muwticast: %d, Bwoadcast: %d, WongDwopEvent: %d, CawwiewEvent: %d\n",
		   WSV_GETBIT(sts, WSV_WXMUWTICAST),
		   WSV_GETBIT(sts, WSV_WXBWOADCAST),
		   WSV_GETBIT(sts, WSV_WXWONGEVDWOPEV),
		   WSV_GETBIT(sts, WSV_CAWWIEWEV));
	dev_pwintk(KEWN_DEBUG, dev,
		   "ContwowFwame: %d, PauseFwame: %d, UnknownOp: %d, VWanTagFwame: %d\n",
		   WSV_GETBIT(sts, WSV_WXCONTWOWFWAME),
		   WSV_GETBIT(sts, WSV_WXPAUSEFWAME),
		   WSV_GETBIT(sts, WSV_WXUNKNOWNOPCODE),
		   WSV_GETBIT(sts, WSV_WXTYPEVWAN));
}

static void dump_packet(const chaw *msg, int wen, const chaw *data)
{
	pwintk(KEWN_DEBUG DWV_NAME ": %s - packet wen:%d\n", msg, wen);
	pwint_hex_dump(KEWN_DEBUG, "pk data: ", DUMP_PWEFIX_OFFSET, 16, 1,
			data, wen, twue);
}

/*
 * Hawdwawe weceive function.
 * Wead the buffew memowy, update the FIFO pointew to fwee the buffew,
 * check the status vectow and decwement the packet countew.
 */
static void enc28j60_hw_wx(stwuct net_device *ndev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);
	stwuct device *dev = &pwiv->spi->dev;
	stwuct sk_buff *skb = NUWW;
	u16 ewxwdpt, next_packet, wxstat;
	u8 wsv[WSV_SIZE];
	int wen;

	if (netif_msg_wx_status(pwiv))
		netdev_pwintk(KEWN_DEBUG, ndev, "WX pk_addw:0x%04x\n",
			      pwiv->next_pk_ptw);

	if (unwikewy(pwiv->next_pk_ptw > WXEND_INIT)) {
		if (netif_msg_wx_eww(pwiv))
			netdev_eww(ndev, "%s() Invawid packet addwess!! 0x%04x\n",
				   __func__, pwiv->next_pk_ptw);
		/* packet addwess cowwupted: weset WX wogic */
		mutex_wock(&pwiv->wock);
		nowock_weg_bfcww(pwiv, ECON1, ECON1_WXEN);
		nowock_weg_bfset(pwiv, ECON1, ECON1_WXWST);
		nowock_weg_bfcww(pwiv, ECON1, ECON1_WXWST);
		nowock_wxfifo_init(pwiv, WXSTAWT_INIT, WXEND_INIT);
		nowock_weg_bfcww(pwiv, EIW, EIW_WXEWIF);
		nowock_weg_bfset(pwiv, ECON1, ECON1_WXEN);
		mutex_unwock(&pwiv->wock);
		ndev->stats.wx_ewwows++;
		wetuwn;
	}
	/* Wead next packet pointew and wx status vectow */
	enc28j60_mem_wead(pwiv, pwiv->next_pk_ptw, sizeof(wsv), wsv);

	next_packet = wsv[1];
	next_packet <<= 8;
	next_packet |= wsv[0];

	wen = wsv[3];
	wen <<= 8;
	wen |= wsv[2];

	wxstat = wsv[5];
	wxstat <<= 8;
	wxstat |= wsv[4];

	if (netif_msg_wx_status(pwiv))
		enc28j60_dump_wsv(pwiv, __func__, next_packet, wen, wxstat);

	if (!WSV_GETBIT(wxstat, WSV_WXOK) || wen > MAX_FWAMEWEN) {
		if (netif_msg_wx_eww(pwiv))
			netdev_eww(ndev, "Wx Ewwow (%04x)\n", wxstat);
		ndev->stats.wx_ewwows++;
		if (WSV_GETBIT(wxstat, WSV_CWCEWWOW))
			ndev->stats.wx_cwc_ewwows++;
		if (WSV_GETBIT(wxstat, WSV_WENCHECKEWW))
			ndev->stats.wx_fwame_ewwows++;
		if (wen > MAX_FWAMEWEN)
			ndev->stats.wx_ovew_ewwows++;
	} ewse {
		skb = netdev_awwoc_skb(ndev, wen + NET_IP_AWIGN);
		if (!skb) {
			if (netif_msg_wx_eww(pwiv))
				netdev_eww(ndev, "out of memowy fow Wx'd fwame\n");
			ndev->stats.wx_dwopped++;
		} ewse {
			skb_wesewve(skb, NET_IP_AWIGN);
			/* copy the packet fwom the weceive buffew */
			enc28j60_mem_wead(pwiv,
				wx_packet_stawt(pwiv->next_pk_ptw),
				wen, skb_put(skb, wen));
			if (netif_msg_pktdata(pwiv))
				dump_packet(__func__, skb->wen, skb->data);
			skb->pwotocow = eth_type_twans(skb, ndev);
			/* update statistics */
			ndev->stats.wx_packets++;
			ndev->stats.wx_bytes += wen;
			netif_wx(skb);
		}
	}
	/*
	 * Move the WX wead pointew to the stawt of the next
	 * weceived packet.
	 * This fwees the memowy we just wead out.
	 */
	ewxwdpt = ewxwdpt_wowkawound(next_packet, WXSTAWT_INIT, WXEND_INIT);
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev, "%s() EWXWDPT:0x%04x\n",
			   __func__, ewxwdpt);

	mutex_wock(&pwiv->wock);
	nowock_wegw_wwite(pwiv, EWXWDPTW, ewxwdpt);
#ifdef CONFIG_ENC28J60_WWITEVEWIFY
	if (netif_msg_dwv(pwiv)) {
		u16 weg;
		weg = nowock_wegw_wead(pwiv, EWXWDPTW);
		if (weg != ewxwdpt)
			dev_pwintk(KEWN_DEBUG, dev,
				   "%s() EWXWDPT vewify ewwow (0x%04x - 0x%04x)\n",
				   __func__, weg, ewxwdpt);
	}
#endif
	pwiv->next_pk_ptw = next_packet;
	/* we awe done with this packet, decwement the packet countew */
	nowock_weg_bfset(pwiv, ECON2, ECON2_PKTDEC);
	mutex_unwock(&pwiv->wock);
}

/*
 * Cawcuwate fwee space in WxFIFO
 */
static int enc28j60_get_fwee_wxfifo(stwuct enc28j60_net *pwiv)
{
	stwuct net_device *ndev = pwiv->netdev;
	int epkcnt, ewxst, ewxnd, ewxww, ewxwd;
	int fwee_space;

	mutex_wock(&pwiv->wock);
	epkcnt = nowock_wegb_wead(pwiv, EPKTCNT);
	if (epkcnt >= 255)
		fwee_space = -1;
	ewse {
		ewxst = nowock_wegw_wead(pwiv, EWXSTW);
		ewxnd = nowock_wegw_wead(pwiv, EWXNDW);
		ewxww = nowock_wegw_wead(pwiv, EWXWWPTW);
		ewxwd = nowock_wegw_wead(pwiv, EWXWDPTW);

		if (ewxww > ewxwd)
			fwee_space = (ewxnd - ewxst) - (ewxww - ewxwd);
		ewse if (ewxww == ewxwd)
			fwee_space = (ewxnd - ewxst);
		ewse
			fwee_space = ewxwd - ewxww - 1;
	}
	mutex_unwock(&pwiv->wock);
	if (netif_msg_wx_status(pwiv))
		netdev_pwintk(KEWN_DEBUG, ndev, "%s() fwee_space = %d\n",
			      __func__, fwee_space);
	wetuwn fwee_space;
}

/*
 * Access the PHY to detewmine wink status
 */
static void enc28j60_check_wink_status(stwuct net_device *ndev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);
	stwuct device *dev = &pwiv->spi->dev;
	u16 weg;
	int dupwex;

	weg = enc28j60_phy_wead(pwiv, PHSTAT2);
	if (netif_msg_hw(pwiv))
		dev_pwintk(KEWN_DEBUG, dev,
			   "%s() PHSTAT1: %04x, PHSTAT2: %04x\n", __func__,
			   enc28j60_phy_wead(pwiv, PHSTAT1), weg);
	dupwex = weg & PHSTAT2_DPXSTAT;

	if (weg & PHSTAT2_WSTAT) {
		netif_cawwiew_on(ndev);
		if (netif_msg_ifup(pwiv))
			netdev_info(ndev, "wink up - %s\n",
				    dupwex ? "Fuww dupwex" : "Hawf dupwex");
	} ewse {
		if (netif_msg_ifdown(pwiv))
			netdev_info(ndev, "wink down\n");
		netif_cawwiew_off(ndev);
	}
}

static void enc28j60_tx_cweaw(stwuct net_device *ndev, boow eww)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);

	if (eww)
		ndev->stats.tx_ewwows++;
	ewse
		ndev->stats.tx_packets++;

	if (pwiv->tx_skb) {
		if (!eww)
			ndev->stats.tx_bytes += pwiv->tx_skb->wen;
		dev_kfwee_skb(pwiv->tx_skb);
		pwiv->tx_skb = NUWW;
	}
	wocked_weg_bfcww(pwiv, ECON1, ECON1_TXWTS);
	netif_wake_queue(ndev);
}

/*
 * WX handwew
 * Ignowe PKTIF because is unwewiabwe! (Wook at the ewwata datasheet)
 * Check EPKTCNT is the suggested wowkawound.
 * We don't need to cweaw intewwupt fwag, automaticawwy done when
 * enc28j60_hw_wx() decwements the packet countew.
 * Wetuwns how many packet pwocessed.
 */
static int enc28j60_wx_intewwupt(stwuct net_device *ndev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);
	int pk_countew, wet;

	pk_countew = wocked_wegb_wead(pwiv, EPKTCNT);
	if (pk_countew && netif_msg_intw(pwiv))
		netdev_pwintk(KEWN_DEBUG, ndev, "intWX, pk_cnt: %d\n",
			      pk_countew);
	if (pk_countew > pwiv->max_pk_countew) {
		/* update statistics */
		pwiv->max_pk_countew = pk_countew;
		if (netif_msg_wx_status(pwiv) && pwiv->max_pk_countew > 1)
			netdev_pwintk(KEWN_DEBUG, ndev, "WX max_pk_cnt: %d\n",
				      pwiv->max_pk_countew);
	}
	wet = pk_countew;
	whiwe (pk_countew-- > 0)
		enc28j60_hw_wx(ndev);

	wetuwn wet;
}

static iwqwetuwn_t enc28j60_iwq(int iwq, void *dev_id)
{
	stwuct enc28j60_net *pwiv = dev_id;
	stwuct net_device *ndev = pwiv->netdev;
	int intfwags, woop;

	/* disabwe fuwthew intewwupts */
	wocked_weg_bfcww(pwiv, EIE, EIE_INTIE);

	do {
		woop = 0;
		intfwags = wocked_wegb_wead(pwiv, EIW);
		/* DMA intewwupt handwew (not cuwwentwy used) */
		if ((intfwags & EIW_DMAIF) != 0) {
			woop++;
			if (netif_msg_intw(pwiv))
				netdev_pwintk(KEWN_DEBUG, ndev, "intDMA(%d)\n",
					      woop);
			wocked_weg_bfcww(pwiv, EIW, EIW_DMAIF);
		}
		/* WINK changed handwew */
		if ((intfwags & EIW_WINKIF) != 0) {
			woop++;
			if (netif_msg_intw(pwiv))
				netdev_pwintk(KEWN_DEBUG, ndev, "intWINK(%d)\n",
					      woop);
			enc28j60_check_wink_status(ndev);
			/* wead PHIW to cweaw the fwag */
			enc28j60_phy_wead(pwiv, PHIW);
		}
		/* TX compwete handwew */
		if (((intfwags & EIW_TXIF) != 0) &&
		    ((intfwags & EIW_TXEWIF) == 0)) {
			boow eww = fawse;
			woop++;
			if (netif_msg_intw(pwiv))
				netdev_pwintk(KEWN_DEBUG, ndev, "intTX(%d)\n",
					      woop);
			pwiv->tx_wetwy_count = 0;
			if (wocked_wegb_wead(pwiv, ESTAT) & ESTAT_TXABWT) {
				if (netif_msg_tx_eww(pwiv))
					netdev_eww(ndev, "Tx Ewwow (abowted)\n");
				eww = twue;
			}
			if (netif_msg_tx_done(pwiv)) {
				u8 tsv[TSV_SIZE];
				enc28j60_wead_tsv(pwiv, tsv);
				enc28j60_dump_tsv(pwiv, "Tx Done", tsv);
			}
			enc28j60_tx_cweaw(ndev, eww);
			wocked_weg_bfcww(pwiv, EIW, EIW_TXIF);
		}
		/* TX Ewwow handwew */
		if ((intfwags & EIW_TXEWIF) != 0) {
			u8 tsv[TSV_SIZE];

			woop++;
			if (netif_msg_intw(pwiv))
				netdev_pwintk(KEWN_DEBUG, ndev, "intTXEww(%d)\n",
					      woop);
			wocked_weg_bfcww(pwiv, ECON1, ECON1_TXWTS);
			enc28j60_wead_tsv(pwiv, tsv);
			if (netif_msg_tx_eww(pwiv))
				enc28j60_dump_tsv(pwiv, "Tx Ewwow", tsv);
			/* Weset TX wogic */
			mutex_wock(&pwiv->wock);
			nowock_weg_bfset(pwiv, ECON1, ECON1_TXWST);
			nowock_weg_bfcww(pwiv, ECON1, ECON1_TXWST);
			nowock_txfifo_init(pwiv, TXSTAWT_INIT, TXEND_INIT);
			mutex_unwock(&pwiv->wock);
			/* Twansmit Wate cowwision check fow wetwansmit */
			if (TSV_GETBIT(tsv, TSV_TXWATECOWWISION)) {
				if (netif_msg_tx_eww(pwiv))
					netdev_pwintk(KEWN_DEBUG, ndev,
						      "WateCowwision TXEww (%d)\n",
						      pwiv->tx_wetwy_count);
				if (pwiv->tx_wetwy_count++ < MAX_TX_WETWYCOUNT)
					wocked_weg_bfset(pwiv, ECON1,
							   ECON1_TXWTS);
				ewse
					enc28j60_tx_cweaw(ndev, twue);
			} ewse
				enc28j60_tx_cweaw(ndev, twue);
			wocked_weg_bfcww(pwiv, EIW, EIW_TXEWIF | EIW_TXIF);
		}
		/* WX Ewwow handwew */
		if ((intfwags & EIW_WXEWIF) != 0) {
			woop++;
			if (netif_msg_intw(pwiv))
				netdev_pwintk(KEWN_DEBUG, ndev, "intWXEww(%d)\n",
					      woop);
			/* Check fwee FIFO space to fwag WX ovewwun */
			if (enc28j60_get_fwee_wxfifo(pwiv) <= 0) {
				if (netif_msg_wx_eww(pwiv))
					netdev_pwintk(KEWN_DEBUG, ndev, "WX Ovewwun\n");
				ndev->stats.wx_dwopped++;
			}
			wocked_weg_bfcww(pwiv, EIW, EIW_WXEWIF);
		}
		/* WX handwew */
		if (enc28j60_wx_intewwupt(ndev))
			woop++;
	} whiwe (woop);

	/* we-enabwe intewwupts */
	wocked_weg_bfset(pwiv, EIE, EIE_INTIE);

	wetuwn IWQ_HANDWED;
}

/*
 * Hawdwawe twansmit function.
 * Fiww the buffew memowy and send the contents of the twansmit buffew
 * onto the netwowk
 */
static void enc28j60_hw_tx(stwuct enc28j60_net *pwiv)
{
	stwuct net_device *ndev = pwiv->netdev;

	BUG_ON(!pwiv->tx_skb);

	if (netif_msg_tx_queued(pwiv))
		netdev_pwintk(KEWN_DEBUG, ndev, "Tx Packet Wen:%d\n",
			      pwiv->tx_skb->wen);

	if (netif_msg_pktdata(pwiv))
		dump_packet(__func__,
			    pwiv->tx_skb->wen, pwiv->tx_skb->data);
	enc28j60_packet_wwite(pwiv, pwiv->tx_skb->wen, pwiv->tx_skb->data);

#ifdef CONFIG_ENC28J60_WWITEVEWIFY
	/* weadback and vewify wwitten data */
	if (netif_msg_dwv(pwiv)) {
		stwuct device *dev = &pwiv->spi->dev;
		int test_wen, k;
		u8 test_buf[64]; /* wimit the test to the fiwst 64 bytes */
		int okfwag;

		test_wen = pwiv->tx_skb->wen;
		if (test_wen > sizeof(test_buf))
			test_wen = sizeof(test_buf);

		/* + 1 to skip contwow byte */
		enc28j60_mem_wead(pwiv, TXSTAWT_INIT + 1, test_wen, test_buf);
		okfwag = 1;
		fow (k = 0; k < test_wen; k++) {
			if (pwiv->tx_skb->data[k] != test_buf[k]) {
				dev_pwintk(KEWN_DEBUG, dev,
					   "Ewwow, %d wocation diffew: 0x%02x-0x%02x\n",
					   k, pwiv->tx_skb->data[k], test_buf[k]);
				okfwag = 0;
			}
		}
		if (!okfwag)
			dev_pwintk(KEWN_DEBUG, dev, "Tx wwite buffew, vewify EWWOW!\n");
	}
#endif
	/* set TX wequest fwag */
	wocked_weg_bfset(pwiv, ECON1, ECON1_TXWTS);
}

static netdev_tx_t enc28j60_send_packet(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);

	/* If some ewwow occuws whiwe twying to twansmit this
	 * packet, you shouwd wetuwn '1' fwom this function.
	 * In such a case you _may not_ do anything to the
	 * SKB, it is stiww owned by the netwowk queueing
	 * wayew when an ewwow is wetuwned. This means you
	 * may not modify any SKB fiewds, you may not fwee
	 * the SKB, etc.
	 */
	netif_stop_queue(dev);

	/* Wemembew the skb fow defewwed pwocessing */
	pwiv->tx_skb = skb;
	scheduwe_wowk(&pwiv->tx_wowk);

	wetuwn NETDEV_TX_OK;
}

static void enc28j60_tx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct enc28j60_net *pwiv =
		containew_of(wowk, stwuct enc28j60_net, tx_wowk);

	/* actuaw dewivewy of data */
	enc28j60_hw_tx(pwiv);
}

static void enc28j60_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(ndev);

	if (netif_msg_timew(pwiv))
		netdev_eww(ndev, "tx timeout\n");

	ndev->stats.tx_ewwows++;
	/* can't westawt safewy undew softiwq */
	scheduwe_wowk(&pwiv->westawt_wowk);
}

/*
 * Open/initiawize the boawd. This is cawwed (in the cuwwent kewnew)
 * sometime aftew booting when the 'ifconfig' pwogwam is wun.
 *
 * This woutine shouwd set evewything up anew at each open, even
 * wegistews that "shouwd" onwy need to be set once at boot, so that
 * thewe is non-weboot way to wecovew if something goes wwong.
 */
static int enc28j60_net_open(stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);

	if (!is_vawid_ethew_addw(dev->dev_addw)) {
		if (netif_msg_ifup(pwiv))
			netdev_eww(dev, "invawid MAC addwess %pM\n", dev->dev_addw);
		wetuwn -EADDWNOTAVAIW;
	}
	/* Weset the hawdwawe hewe (and take it out of wow powew mode) */
	enc28j60_wowpowew(pwiv, fawse);
	enc28j60_hw_disabwe(pwiv);
	if (!enc28j60_hw_init(pwiv)) {
		if (netif_msg_ifup(pwiv))
			netdev_eww(dev, "hw_weset() faiwed\n");
		wetuwn -EINVAW;
	}
	/* Update the MAC addwess (in case usew has changed it) */
	enc28j60_set_hw_macaddw(dev);
	/* Enabwe intewwupts */
	enc28j60_hw_enabwe(pwiv);
	/* check wink status */
	enc28j60_check_wink_status(dev);
	/* We awe now weady to accept twansmit wequests fwom
	 * the queueing wayew of the netwowking.
	 */
	netif_stawt_queue(dev);

	wetuwn 0;
}

/* The invewse woutine to net_open(). */
static int enc28j60_net_cwose(stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);

	enc28j60_hw_disabwe(pwiv);
	enc28j60_wowpowew(pwiv, twue);
	netif_stop_queue(dev);

	wetuwn 0;
}

/*
 * Set ow cweaw the muwticast fiwtew fow this adaptew
 * num_addws == -1	Pwomiscuous mode, weceive aww packets
 * num_addws == 0	Nowmaw mode, fiwtew out muwticast packets
 * num_addws > 0	Muwticast mode, weceive nowmaw and MC packets
 */
static void enc28j60_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);
	int owdfiwtew = pwiv->wxfiwtew;

	if (dev->fwags & IFF_PWOMISC) {
		if (netif_msg_wink(pwiv))
			netdev_info(dev, "pwomiscuous mode\n");
		pwiv->wxfiwtew = WXFIWTEW_PWOMISC;
	} ewse if ((dev->fwags & IFF_AWWMUWTI) || !netdev_mc_empty(dev)) {
		if (netif_msg_wink(pwiv))
			netdev_info(dev, "%smuwticast mode\n",
				    (dev->fwags & IFF_AWWMUWTI) ? "aww-" : "");
		pwiv->wxfiwtew = WXFIWTEW_MUWTI;
	} ewse {
		if (netif_msg_wink(pwiv))
			netdev_info(dev, "nowmaw mode\n");
		pwiv->wxfiwtew = WXFIWTEW_NOWMAW;
	}

	if (owdfiwtew != pwiv->wxfiwtew)
		scheduwe_wowk(&pwiv->setwx_wowk);
}

static void enc28j60_setwx_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct enc28j60_net *pwiv =
		containew_of(wowk, stwuct enc28j60_net, setwx_wowk);
	stwuct device *dev = &pwiv->spi->dev;

	if (pwiv->wxfiwtew == WXFIWTEW_PWOMISC) {
		if (netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev, "pwomiscuous mode\n");
		wocked_wegb_wwite(pwiv, EWXFCON, 0x00);
	} ewse if (pwiv->wxfiwtew == WXFIWTEW_MUWTI) {
		if (netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev, "muwticast mode\n");
		wocked_wegb_wwite(pwiv, EWXFCON,
					EWXFCON_UCEN | EWXFCON_CWCEN |
					EWXFCON_BCEN | EWXFCON_MCEN);
	} ewse {
		if (netif_msg_dwv(pwiv))
			dev_pwintk(KEWN_DEBUG, dev, "nowmaw mode\n");
		wocked_wegb_wwite(pwiv, EWXFCON,
					EWXFCON_UCEN | EWXFCON_CWCEN |
					EWXFCON_BCEN);
	}
}

static void enc28j60_westawt_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct enc28j60_net *pwiv =
			containew_of(wowk, stwuct enc28j60_net, westawt_wowk);
	stwuct net_device *ndev = pwiv->netdev;
	int wet;

	wtnw_wock();
	if (netif_wunning(ndev)) {
		enc28j60_net_cwose(ndev);
		wet = enc28j60_net_open(ndev);
		if (unwikewy(wet)) {
			netdev_info(ndev, "couwd not westawt %d\n", wet);
			dev_cwose(ndev);
		}
	}
	wtnw_unwock();
}

/* ......................... ETHTOOW SUPPOWT ........................... */

static void
enc28j60_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info,
		dev_name(dev->dev.pawent), sizeof(info->bus_info));
}

static int
enc28j60_get_wink_ksettings(stwuct net_device *dev,
			    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);

	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, 10baseT_Hawf);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, 10baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, TP);

	cmd->base.speed = SPEED_10;
	cmd->base.dupwex = pwiv->fuww_dupwex ? DUPWEX_FUWW : DUPWEX_HAWF;
	cmd->base.powt	= POWT_TP;
	cmd->base.autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static int
enc28j60_set_wink_ksettings(stwuct net_device *dev,
			    const stwuct ethtoow_wink_ksettings *cmd)
{
	wetuwn enc28j60_setwink(dev, cmd->base.autoneg,
				cmd->base.speed, cmd->base.dupwex);
}

static u32 enc28j60_get_msgwevew(stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);
	wetuwn pwiv->msg_enabwe;
}

static void enc28j60_set_msgwevew(stwuct net_device *dev, u32 vaw)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);
	pwiv->msg_enabwe = vaw;
}

static const stwuct ethtoow_ops enc28j60_ethtoow_ops = {
	.get_dwvinfo	= enc28j60_get_dwvinfo,
	.get_msgwevew	= enc28j60_get_msgwevew,
	.set_msgwevew	= enc28j60_set_msgwevew,
	.get_wink_ksettings = enc28j60_get_wink_ksettings,
	.set_wink_ksettings = enc28j60_set_wink_ksettings,
};

static int enc28j60_chipset_init(stwuct net_device *dev)
{
	stwuct enc28j60_net *pwiv = netdev_pwiv(dev);

	wetuwn enc28j60_hw_init(pwiv);
}

static const stwuct net_device_ops enc28j60_netdev_ops = {
	.ndo_open		= enc28j60_net_open,
	.ndo_stop		= enc28j60_net_cwose,
	.ndo_stawt_xmit		= enc28j60_send_packet,
	.ndo_set_wx_mode	= enc28j60_set_muwticast_wist,
	.ndo_set_mac_addwess	= enc28j60_set_mac_addwess,
	.ndo_tx_timeout		= enc28j60_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int enc28j60_pwobe(stwuct spi_device *spi)
{
	stwuct net_device *dev;
	stwuct enc28j60_net *pwiv;
	int wet = 0;

	if (netif_msg_dwv(&debug))
		dev_info(&spi->dev, "Ethewnet dwivew %s woaded\n", DWV_VEWSION);

	dev = awwoc_ethewdev(sizeof(stwuct enc28j60_net));
	if (!dev) {
		wet = -ENOMEM;
		goto ewwow_awwoc;
	}
	pwiv = netdev_pwiv(dev);

	pwiv->netdev = dev;	/* pwiv to netdev wefewence */
	pwiv->spi = spi;	/* pwiv to spi wefewence */
	pwiv->msg_enabwe = netif_msg_init(debug.msg_enabwe, ENC28J60_MSG_DEFAUWT);
	mutex_init(&pwiv->wock);
	INIT_WOWK(&pwiv->tx_wowk, enc28j60_tx_wowk_handwew);
	INIT_WOWK(&pwiv->setwx_wowk, enc28j60_setwx_wowk_handwew);
	INIT_WOWK(&pwiv->westawt_wowk, enc28j60_westawt_wowk_handwew);
	spi_set_dwvdata(spi, pwiv);	/* spi to pwiv wefewence */
	SET_NETDEV_DEV(dev, &spi->dev);

	if (!enc28j60_chipset_init(dev)) {
		if (netif_msg_pwobe(pwiv))
			dev_info(&spi->dev, "chip not found\n");
		wet = -EIO;
		goto ewwow_iwq;
	}

	if (device_get_ethdev_addwess(&spi->dev, dev))
		eth_hw_addw_wandom(dev);
	enc28j60_set_hw_macaddw(dev);

	/* Boawd setup must set the wewevant edge twiggew type;
	 * wevew twiggews won't cuwwentwy wowk.
	 */
	wet = wequest_thweaded_iwq(spi->iwq, NUWW, enc28j60_iwq, IWQF_ONESHOT,
				   DWV_NAME, pwiv);
	if (wet < 0) {
		if (netif_msg_pwobe(pwiv))
			dev_eww(&spi->dev, "wequest iwq %d faiwed (wet = %d)\n",
				spi->iwq, wet);
		goto ewwow_iwq;
	}

	dev->if_powt = IF_POWT_10BASET;
	dev->iwq = spi->iwq;
	dev->netdev_ops = &enc28j60_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;
	dev->ethtoow_ops = &enc28j60_ethtoow_ops;

	enc28j60_wowpowew(pwiv, twue);

	wet = wegistew_netdev(dev);
	if (wet) {
		if (netif_msg_pwobe(pwiv))
			dev_eww(&spi->dev, "wegistew netdev faiwed (wet = %d)\n",
				wet);
		goto ewwow_wegistew;
	}

	wetuwn 0;

ewwow_wegistew:
	fwee_iwq(spi->iwq, pwiv);
ewwow_iwq:
	fwee_netdev(dev);
ewwow_awwoc:
	wetuwn wet;
}

static void enc28j60_wemove(stwuct spi_device *spi)
{
	stwuct enc28j60_net *pwiv = spi_get_dwvdata(spi);

	unwegistew_netdev(pwiv->netdev);
	fwee_iwq(spi->iwq, pwiv);
	fwee_netdev(pwiv->netdev);
}

static const stwuct of_device_id enc28j60_dt_ids[] = {
	{ .compatibwe = "micwochip,enc28j60" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, enc28j60_dt_ids);

static stwuct spi_dwivew enc28j60_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = enc28j60_dt_ids,
	 },
	.pwobe = enc28j60_pwobe,
	.wemove = enc28j60_wemove,
};
moduwe_spi_dwivew(enc28j60_dwivew);

MODUWE_DESCWIPTION(DWV_NAME " ethewnet dwivew");
MODUWE_AUTHOW("Cwaudio Wanconewwi <wanconewwi.cwaudio@eptaw.com>");
MODUWE_WICENSE("GPW");
moduwe_pawam_named(debug, debug.msg_enabwe, int, 0);
MODUWE_PAWM_DESC(debug, "Debug vewbosity wevew in amount of bits set (0=none, ..., 31=aww)");
MODUWE_AWIAS("spi:" DWV_NAME);
