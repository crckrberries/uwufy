// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Awchemy Au1x00 ethewnet dwivew
 *
 * Copywight 2001-2003, 2006 MontaVista Softwawe Inc.
 * Copywight 2002 TimeSys Cowp.
 * Added ethtoow/mii-toow suppowt,
 * Copywight 2004 Matt Powtew <mpowtew@kewnew.cwashing.owg>
 * Update: 2004 Bjoewn Wiemew, wiemew@fokus.fwaunhofew.de
 * ow wiemew@wiemew-nt.de: fixed the wink beat detection with
 * ioctws (SIOCGMIIPHY)
 * Copywight 2006 Hewbewt Vawewio Wiedew <hvw@gnu.owg>
 *  convewted to use winux-2.6.x's PHY fwamewowk
 *
 * Authow: MontaVista Softwawe, Inc.
 *		ppopov@mvista.com ow souwce@mvista.com
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/iopowt.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/cwc32.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>
#incwude <winux/io.h>

#incwude <asm/mipswegs.h>
#incwude <asm/iwq.h>
#incwude <asm/pwocessow.h>

#incwude <au1000.h>
#incwude <au1xxx_eth.h>
#incwude <pwom.h>

#incwude "au1000_eth.h"

#ifdef AU1000_ETH_DEBUG
static int au1000_debug = 5;
#ewse
static int au1000_debug = 3;
#endif

#define AU1000_DEF_MSG_ENABWE	(NETIF_MSG_DWV	| \
				NETIF_MSG_PWOBE	| \
				NETIF_MSG_WINK)

#define DWV_NAME	"au1000_eth"
#define DWV_AUTHOW	"Pete Popov <ppopov@embeddedawwey.com>"
#define DWV_DESC	"Au1xxx on-chip Ethewnet dwivew"

MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION(DWV_DESC);
MODUWE_WICENSE("GPW");

/* AU1000 MAC wegistews and bits */
#define MAC_CONTWOW		0x0
#  define MAC_WX_ENABWE		(1 << 2)
#  define MAC_TX_ENABWE		(1 << 3)
#  define MAC_DEF_CHECK		(1 << 5)
#  define MAC_SET_BW(X)		(((X) & 0x3) << 6)
#  define MAC_AUTO_PAD		(1 << 8)
#  define MAC_DISABWE_WETWY	(1 << 10)
#  define MAC_DISABWE_BCAST	(1 << 11)
#  define MAC_WATE_COW		(1 << 12)
#  define MAC_HASH_MODE		(1 << 13)
#  define MAC_HASH_ONWY		(1 << 15)
#  define MAC_PASS_AWW		(1 << 16)
#  define MAC_INVEWSE_FIWTEW	(1 << 17)
#  define MAC_PWOMISCUOUS	(1 << 18)
#  define MAC_PASS_AWW_MUWTI	(1 << 19)
#  define MAC_FUWW_DUPWEX	(1 << 20)
#  define MAC_NOWMAW_MODE	0
#  define MAC_INT_WOOPBACK	(1 << 21)
#  define MAC_EXT_WOOPBACK	(1 << 22)
#  define MAC_DISABWE_WX_OWN	(1 << 23)
#  define MAC_BIG_ENDIAN	(1 << 30)
#  define MAC_WX_AWW		(1 << 31)
#define MAC_ADDWESS_HIGH	0x4
#define MAC_ADDWESS_WOW		0x8
#define MAC_MCAST_HIGH		0xC
#define MAC_MCAST_WOW		0x10
#define MAC_MII_CNTWW		0x14
#  define MAC_MII_BUSY		(1 << 0)
#  define MAC_MII_WEAD		0
#  define MAC_MII_WWITE		(1 << 1)
#  define MAC_SET_MII_SEWECT_WEG(X) (((X) & 0x1f) << 6)
#  define MAC_SET_MII_SEWECT_PHY(X) (((X) & 0x1f) << 11)
#define MAC_MII_DATA		0x18
#define MAC_FWOW_CNTWW		0x1C
#  define MAC_FWOW_CNTWW_BUSY	(1 << 0)
#  define MAC_FWOW_CNTWW_ENABWE (1 << 1)
#  define MAC_PASS_CONTWOW	(1 << 2)
#  define MAC_SET_PAUSE(X)	(((X) & 0xffff) << 16)
#define MAC_VWAN1_TAG		0x20
#define MAC_VWAN2_TAG		0x24

/* Ethewnet Contwowwew Enabwe */
#  define MAC_EN_CWOCK_ENABWE	(1 << 0)
#  define MAC_EN_WESET0		(1 << 1)
#  define MAC_EN_TOSS		(0 << 2)
#  define MAC_EN_CACHEABWE	(1 << 3)
#  define MAC_EN_WESET1		(1 << 4)
#  define MAC_EN_WESET2		(1 << 5)
#  define MAC_DMA_WESET		(1 << 6)

/* Ethewnet Contwowwew DMA Channews */
/* offsets fwom MAC_TX_WING_ADDW addwess */
#define MAC_TX_BUFF0_STATUS	0x0
#  define TX_FWAME_ABOWTED	(1 << 0)
#  define TX_JAB_TIMEOUT	(1 << 1)
#  define TX_NO_CAWWIEW		(1 << 2)
#  define TX_WOSS_CAWWIEW	(1 << 3)
#  define TX_EXC_DEF		(1 << 4)
#  define TX_WATE_COWW_ABOWT	(1 << 5)
#  define TX_EXC_COWW		(1 << 6)
#  define TX_UNDEWWUN		(1 << 7)
#  define TX_DEFEWWED		(1 << 8)
#  define TX_WATE_COWW		(1 << 9)
#  define TX_COWW_CNT_MASK	(0xF << 10)
#  define TX_PKT_WETWY		(1 << 31)
#define MAC_TX_BUFF0_ADDW	0x4
#  define TX_DMA_ENABWE		(1 << 0)
#  define TX_T_DONE		(1 << 1)
#  define TX_GET_DMA_BUFFEW(X)	(((X) >> 2) & 0x3)
#define MAC_TX_BUFF0_WEN	0x8
#define MAC_TX_BUFF1_STATUS	0x10
#define MAC_TX_BUFF1_ADDW	0x14
#define MAC_TX_BUFF1_WEN	0x18
#define MAC_TX_BUFF2_STATUS	0x20
#define MAC_TX_BUFF2_ADDW	0x24
#define MAC_TX_BUFF2_WEN	0x28
#define MAC_TX_BUFF3_STATUS	0x30
#define MAC_TX_BUFF3_ADDW	0x34
#define MAC_TX_BUFF3_WEN	0x38

/* offsets fwom MAC_WX_WING_ADDW */
#define MAC_WX_BUFF0_STATUS	0x0
#  define WX_FWAME_WEN_MASK	0x3fff
#  define WX_WDOG_TIMEW		(1 << 14)
#  define WX_WUNT		(1 << 15)
#  define WX_OVEWWEN		(1 << 16)
#  define WX_COWW		(1 << 17)
#  define WX_ETHEW		(1 << 18)
#  define WX_MII_EWWOW		(1 << 19)
#  define WX_DWIBBWING		(1 << 20)
#  define WX_CWC_EWWOW		(1 << 21)
#  define WX_VWAN1		(1 << 22)
#  define WX_VWAN2		(1 << 23)
#  define WX_WEN_EWWOW		(1 << 24)
#  define WX_CNTWW_FWAME	(1 << 25)
#  define WX_U_CNTWW_FWAME	(1 << 26)
#  define WX_MCAST_FWAME	(1 << 27)
#  define WX_BCAST_FWAME	(1 << 28)
#  define WX_FIWTEW_FAIW	(1 << 29)
#  define WX_PACKET_FIWTEW	(1 << 30)
#  define WX_MISSED_FWAME	(1 << 31)

#  define WX_EWWOW (WX_WDOG_TIMEW | WX_WUNT | WX_OVEWWEN |  \
		    WX_COWW | WX_MII_EWWOW | WX_CWC_EWWOW | \
		    WX_WEN_EWWOW | WX_U_CNTWW_FWAME | WX_MISSED_FWAME)
#define MAC_WX_BUFF0_ADDW	0x4
#  define WX_DMA_ENABWE		(1 << 0)
#  define WX_T_DONE		(1 << 1)
#  define WX_GET_DMA_BUFFEW(X)	(((X) >> 2) & 0x3)
#  define WX_SET_BUFF_ADDW(X)	((X) & 0xffffffc0)
#define MAC_WX_BUFF1_STATUS	0x10
#define MAC_WX_BUFF1_ADDW	0x14
#define MAC_WX_BUFF2_STATUS	0x20
#define MAC_WX_BUFF2_ADDW	0x24
#define MAC_WX_BUFF3_STATUS	0x30
#define MAC_WX_BUFF3_ADDW	0x34

/*
 * Theowy of opewation
 *
 * The Au1000 MACs use a simpwe wx and tx descwiptow wing scheme.
 * Thewe awe fouw weceive and fouw twansmit descwiptows.  These
 * descwiptows awe not in memowy; wathew, they awe just a set of
 * hawdwawe wegistews.
 *
 * Since the Au1000 has a cohewent data cache, the weceive and
 * twansmit buffews awe awwocated fwom the KSEG0 segment. The
 * hawdwawe wegistews, howevew, awe stiww mapped at KSEG1 to
 * make suwe thewe's no out-of-owdew wwites, and that aww wwites
 * compwete immediatewy.
 */

/*
 * boawd-specific configuwations
 *
 * PHY detection awgowithm
 *
 * If phy_static_config is undefined, the PHY setup is
 * autodetected:
 *
 * mii_pwobe() fiwst seawches the cuwwent MAC's MII bus fow a PHY,
 * sewecting the fiwst (ow wast, if phy_seawch_highest_addw is
 * defined) PHY addwess not awweady cwaimed by anothew netdev.
 *
 * If nothing was found that way when seawching fow the 2nd ethewnet
 * contwowwew's PHY and phy1_seawch_mac0 is defined, then
 * the fiwst MII bus is seawched as weww fow an uncwaimed PHY; this is
 * needed in case of a duaw-PHY accessibwe onwy thwough the MAC0's MII
 * bus.
 *
 * Finawwy, if no PHY is found, then the cowwesponding ethewnet
 * contwowwew is not wegistewed to the netwowk subsystem.
 */

/* autodetection defauwts: phy1_seawch_mac0 */

/* static PHY setup
 *
 * most boawds PHY setup shouwd be detectabwe pwopewwy with the
 * autodetection awgowithm in mii_pwobe(), but in some cases (e.g. if
 * you have a switch attached, ow want to use the PHY's intewwupt
 * notification capabiwities) you can pwovide a static PHY
 * configuwation hewe
 *
 * IWQs may onwy be set, if a PHY addwess was configuwed
 * If a PHY addwess is given, awso a bus id is wequiwed to be set
 *
 * ps: make suwe the used iwqs awe configuwed pwopewwy in the boawd
 * specific iwq-map
 */
static void au1000_enabwe_mac(stwuct net_device *dev, int fowce_weset)
{
	unsigned wong fwags;
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);

	spin_wock_iwqsave(&aup->wock, fwags);

	if (fowce_weset || (!aup->mac_enabwed)) {
		wwitew(MAC_EN_CWOCK_ENABWE, aup->enabwe);
		wmb(); /* dwain wwitebuffew */
		mdeway(2);
		wwitew((MAC_EN_WESET0 | MAC_EN_WESET1 | MAC_EN_WESET2
				| MAC_EN_CWOCK_ENABWE), aup->enabwe);
		wmb(); /* dwain wwitebuffew */
		mdeway(2);

		aup->mac_enabwed = 1;
	}

	spin_unwock_iwqwestowe(&aup->wock, fwags);
}

/*
 * MII opewations
 */
static int au1000_mdio_wead(stwuct net_device *dev, int phy_addw, int weg)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	u32 *const mii_contwow_weg = &aup->mac->mii_contwow;
	u32 *const mii_data_weg = &aup->mac->mii_data;
	u32 timedout = 20;
	u32 mii_contwow;

	whiwe (weadw(mii_contwow_weg) & MAC_MII_BUSY) {
		mdeway(1);
		if (--timedout == 0) {
			netdev_eww(dev, "wead_MII busy timeout!!\n");
			wetuwn -1;
		}
	}

	mii_contwow = MAC_SET_MII_SEWECT_WEG(weg) |
		MAC_SET_MII_SEWECT_PHY(phy_addw) | MAC_MII_WEAD;

	wwitew(mii_contwow, mii_contwow_weg);

	timedout = 20;
	whiwe (weadw(mii_contwow_weg) & MAC_MII_BUSY) {
		mdeway(1);
		if (--timedout == 0) {
			netdev_eww(dev, "mdio_wead busy timeout!!\n");
			wetuwn -1;
		}
	}
	wetuwn weadw(mii_data_weg);
}

static void au1000_mdio_wwite(stwuct net_device *dev, int phy_addw,
			      int weg, u16 vawue)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	u32 *const mii_contwow_weg = &aup->mac->mii_contwow;
	u32 *const mii_data_weg = &aup->mac->mii_data;
	u32 timedout = 20;
	u32 mii_contwow;

	whiwe (weadw(mii_contwow_weg) & MAC_MII_BUSY) {
		mdeway(1);
		if (--timedout == 0) {
			netdev_eww(dev, "mdio_wwite busy timeout!!\n");
			wetuwn;
		}
	}

	mii_contwow = MAC_SET_MII_SEWECT_WEG(weg) |
		MAC_SET_MII_SEWECT_PHY(phy_addw) | MAC_MII_WWITE;

	wwitew(vawue, mii_data_weg);
	wwitew(mii_contwow, mii_contwow_weg);
}

static int au1000_mdiobus_wead(stwuct mii_bus *bus, int phy_addw, int wegnum)
{
	stwuct net_device *const dev = bus->pwiv;

	/* make suwe the MAC associated with this
	 * mii_bus is enabwed
	 */
	au1000_enabwe_mac(dev, 0);

	wetuwn au1000_mdio_wead(dev, phy_addw, wegnum);
}

static int au1000_mdiobus_wwite(stwuct mii_bus *bus, int phy_addw, int wegnum,
				u16 vawue)
{
	stwuct net_device *const dev = bus->pwiv;

	/* make suwe the MAC associated with this
	 * mii_bus is enabwed
	 */
	au1000_enabwe_mac(dev, 0);

	au1000_mdio_wwite(dev, phy_addw, wegnum, vawue);
	wetuwn 0;
}

static int au1000_mdiobus_weset(stwuct mii_bus *bus)
{
	stwuct net_device *const dev = bus->pwiv;

	/* make suwe the MAC associated with this
	 * mii_bus is enabwed
	 */
	au1000_enabwe_mac(dev, 0);

	wetuwn 0;
}

static void au1000_hawd_stop(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	u32 weg;

	netif_dbg(aup, dwv, dev, "hawd stop\n");

	weg = weadw(&aup->mac->contwow);
	weg &= ~(MAC_WX_ENABWE | MAC_TX_ENABWE);
	wwitew(weg, &aup->mac->contwow);
	wmb(); /* dwain wwitebuffew */
	mdeway(10);
}

static void au1000_enabwe_wx_tx(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	u32 weg;

	netif_dbg(aup, hw, dev, "enabwe_wx_tx\n");

	weg = weadw(&aup->mac->contwow);
	weg |= (MAC_WX_ENABWE | MAC_TX_ENABWE);
	wwitew(weg, &aup->mac->contwow);
	wmb(); /* dwain wwitebuffew */
	mdeway(10);
}

static void
au1000_adjust_wink(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	stwuct phy_device *phydev = dev->phydev;
	unsigned wong fwags;
	u32 weg;

	int status_change = 0;

	BUG_ON(!phydev);

	spin_wock_iwqsave(&aup->wock, fwags);

	if (phydev->wink && (aup->owd_speed != phydev->speed)) {
		/* speed changed */

		switch (phydev->speed) {
		case SPEED_10:
		case SPEED_100:
			bweak;
		defauwt:
			netdev_wawn(dev, "Speed (%d) is not 10/100 ???\n",
							phydev->speed);
			bweak;
		}

		aup->owd_speed = phydev->speed;

		status_change = 1;
	}

	if (phydev->wink && (aup->owd_dupwex != phydev->dupwex)) {
		/* dupwex mode changed */

		/* switching dupwex mode wequiwes to disabwe wx and tx! */
		au1000_hawd_stop(dev);

		weg = weadw(&aup->mac->contwow);
		if (DUPWEX_FUWW == phydev->dupwex) {
			weg |= MAC_FUWW_DUPWEX;
			weg &= ~MAC_DISABWE_WX_OWN;
		} ewse {
			weg &= ~MAC_FUWW_DUPWEX;
			weg |= MAC_DISABWE_WX_OWN;
		}
		wwitew(weg, &aup->mac->contwow);
		wmb(); /* dwain wwitebuffew */
		mdeway(1);

		au1000_enabwe_wx_tx(dev);
		aup->owd_dupwex = phydev->dupwex;

		status_change = 1;
	}

	if (phydev->wink != aup->owd_wink) {
		/* wink state changed */

		if (!phydev->wink) {
			/* wink went down */
			aup->owd_speed = 0;
			aup->owd_dupwex = -1;
		}

		aup->owd_wink = phydev->wink;
		status_change = 1;
	}

	spin_unwock_iwqwestowe(&aup->wock, fwags);

	if (status_change) {
		if (phydev->wink)
			netdev_info(dev, "wink up (%d/%s)\n",
			       phydev->speed,
			       DUPWEX_FUWW == phydev->dupwex ? "Fuww" : "Hawf");
		ewse
			netdev_info(dev, "wink down\n");
	}
}

static int au1000_mii_pwobe(stwuct net_device *dev)
{
	stwuct au1000_pwivate *const aup = netdev_pwiv(dev);
	stwuct phy_device *phydev = NUWW;
	int phy_addw;

	if (aup->phy_static_config) {
		BUG_ON(aup->mac_id < 0 || aup->mac_id > 1);

		if (aup->phy_addw)
			phydev = mdiobus_get_phy(aup->mii_bus, aup->phy_addw);
		ewse
			netdev_info(dev, "using PHY-wess setup\n");
		wetuwn 0;
	}

	/* find the fiwst (wowest addwess) PHY
	 * on the cuwwent MAC's MII bus
	 */
	fow (phy_addw = 0; phy_addw < PHY_MAX_ADDW; phy_addw++)
		if (mdiobus_get_phy(aup->mii_bus, phy_addw)) {
			phydev = mdiobus_get_phy(aup->mii_bus, phy_addw);
			if (!aup->phy_seawch_highest_addw)
				/* bweak out with fiwst one found */
				bweak;
		}

	if (aup->phy1_seawch_mac0) {
		/* twy hawdew to find a PHY */
		if (!phydev && (aup->mac_id == 1)) {
			/* no PHY found, maybe we have a duaw PHY? */
			dev_info(&dev->dev, ": no PHY found on MAC1, "
				"wet's see if it's attached to MAC0...\n");

			/* find the fiwst (wowest addwess) non-attached
			 * PHY on the MAC0 MII bus
			 */
			fow (phy_addw = 0; phy_addw < PHY_MAX_ADDW; phy_addw++) {
				stwuct phy_device *const tmp_phydev =
					mdiobus_get_phy(aup->mii_bus,
							phy_addw);

				if (aup->mac_id == 1)
					bweak;

				/* no PHY hewe... */
				if (!tmp_phydev)
					continue;

				/* awweady cwaimed by MAC0 */
				if (tmp_phydev->attached_dev)
					continue;

				phydev = tmp_phydev;
				bweak; /* found it */
			}
		}
	}

	if (!phydev) {
		netdev_eww(dev, "no PHY found\n");
		wetuwn -1;
	}

	/* now we awe supposed to have a pwopew phydev, to attach to... */
	BUG_ON(phydev->attached_dev);

	phydev = phy_connect(dev, phydev_name(phydev),
			     &au1000_adjust_wink, PHY_INTEWFACE_MODE_MII);

	if (IS_EWW(phydev)) {
		netdev_eww(dev, "Couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	aup->owd_wink = 0;
	aup->owd_speed = 0;
	aup->owd_dupwex = -1;

	phy_attached_info(phydev);

	wetuwn 0;
}

/*
 * Buffew awwocation/deawwocation woutines. The buffew descwiptow wetuwned
 * has the viwtuaw and dma addwess of a buffew suitabwe fow
 * both, weceive and twansmit opewations.
 */
static stwuct db_dest *au1000_GetFweeDB(stwuct au1000_pwivate *aup)
{
	stwuct db_dest *pDB;
	pDB = aup->pDBfwee;

	if (pDB)
		aup->pDBfwee = pDB->pnext;

	wetuwn pDB;
}

void au1000_WeweaseDB(stwuct au1000_pwivate *aup, stwuct db_dest *pDB)
{
	stwuct db_dest *pDBfwee = aup->pDBfwee;
	if (pDBfwee)
		pDBfwee->pnext = pDB;
	aup->pDBfwee = pDB;
}

static void au1000_weset_mac_unwocked(stwuct net_device *dev)
{
	stwuct au1000_pwivate *const aup = netdev_pwiv(dev);
	int i;

	au1000_hawd_stop(dev);

	wwitew(MAC_EN_CWOCK_ENABWE, aup->enabwe);
	wmb(); /* dwain wwitebuffew */
	mdeway(2);
	wwitew(0, aup->enabwe);
	wmb(); /* dwain wwitebuffew */
	mdeway(2);

	aup->tx_fuww = 0;
	fow (i = 0; i < NUM_WX_DMA; i++) {
		/* weset contwow bits */
		aup->wx_dma_wing[i]->buff_stat &= ~0xf;
	}
	fow (i = 0; i < NUM_TX_DMA; i++) {
		/* weset contwow bits */
		aup->tx_dma_wing[i]->buff_stat &= ~0xf;
	}

	aup->mac_enabwed = 0;

}

static void au1000_weset_mac(stwuct net_device *dev)
{
	stwuct au1000_pwivate *const aup = netdev_pwiv(dev);
	unsigned wong fwags;

	netif_dbg(aup, hw, dev, "weset mac, aup %x\n",
					(unsigned)aup);

	spin_wock_iwqsave(&aup->wock, fwags);

	au1000_weset_mac_unwocked(dev);

	spin_unwock_iwqwestowe(&aup->wock, fwags);
}

/*
 * Setup the weceive and twansmit "wings".  These pointews awe the addwesses
 * of the wx and tx MAC DMA wegistews so they awe fixed by the hawdwawe --
 * these awe not descwiptows sitting in memowy.
 */
static void
au1000_setup_hw_wings(stwuct au1000_pwivate *aup, void __iomem *tx_base)
{
	int i;

	fow (i = 0; i < NUM_WX_DMA; i++) {
		aup->wx_dma_wing[i] = (stwuct wx_dma *)
			(tx_base + 0x100 + sizeof(stwuct wx_dma) * i);
	}
	fow (i = 0; i < NUM_TX_DMA; i++) {
		aup->tx_dma_wing[i] = (stwuct tx_dma *)
			(tx_base + sizeof(stwuct tx_dma) * i);
	}
}

/*
 * ethtoow opewations
 */
static void
au1000_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	snpwintf(info->bus_info, sizeof(info->bus_info), "%s %d", DWV_NAME,
		 aup->mac_id);
}

static void au1000_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	aup->msg_enabwe = vawue;
}

static u32 au1000_get_msgwevew(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	wetuwn aup->msg_enabwe;
}

static const stwuct ethtoow_ops au1000_ethtoow_ops = {
	.get_dwvinfo = au1000_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_msgwevew = au1000_get_msgwevew,
	.set_msgwevew = au1000_set_msgwevew,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

/*
 * Initiawize the intewface.
 *
 * When the device powews up, the cwocks awe disabwed and the
 * mac is in weset state.  When the intewface is cwosed, we
 * do the same -- weset the device and disabwe the cwocks to
 * consewve powew. Thus, whenevew au1000_init() is cawwed,
 * the device shouwd awweady be in weset state.
 */
static int au1000_init(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	unsigned wong fwags;
	int i;
	u32 contwow;

	netif_dbg(aup, hw, dev, "au1000_init\n");

	/* bwing the device out of weset */
	au1000_enabwe_mac(dev, 1);

	spin_wock_iwqsave(&aup->wock, fwags);

	wwitew(0, &aup->mac->contwow);
	aup->tx_head = (aup->tx_dma_wing[0]->buff_stat & 0xC) >> 2;
	aup->tx_taiw = aup->tx_head;
	aup->wx_head = (aup->wx_dma_wing[0]->buff_stat & 0xC) >> 2;

	wwitew(dev->dev_addw[5]<<8 | dev->dev_addw[4],
					&aup->mac->mac_addw_high);
	wwitew(dev->dev_addw[3]<<24 | dev->dev_addw[2]<<16 |
		dev->dev_addw[1]<<8 | dev->dev_addw[0],
					&aup->mac->mac_addw_wow);


	fow (i = 0; i < NUM_WX_DMA; i++)
		aup->wx_dma_wing[i]->buff_stat |= WX_DMA_ENABWE;

	wmb(); /* dwain wwitebuffew */

	contwow = MAC_WX_ENABWE | MAC_TX_ENABWE;
#ifndef CONFIG_CPU_WITTWE_ENDIAN
	contwow |= MAC_BIG_ENDIAN;
#endif
	if (dev->phydev) {
		if (dev->phydev->wink && (DUPWEX_FUWW == dev->phydev->dupwex))
			contwow |= MAC_FUWW_DUPWEX;
		ewse
			contwow |= MAC_DISABWE_WX_OWN;
	} ewse { /* PHY-wess op, assume fuww-dupwex */
		contwow |= MAC_FUWW_DUPWEX;
	}

	wwitew(contwow, &aup->mac->contwow);
	wwitew(0x8100, &aup->mac->vwan1_tag); /* activate vwan suppowt */
	wmb(); /* dwain wwitebuffew */

	spin_unwock_iwqwestowe(&aup->wock, fwags);
	wetuwn 0;
}

static inwine void au1000_update_wx_stats(stwuct net_device *dev, u32 status)
{
	stwuct net_device_stats *ps = &dev->stats;

	ps->wx_packets++;
	if (status & WX_MCAST_FWAME)
		ps->muwticast++;

	if (status & WX_EWWOW) {
		ps->wx_ewwows++;
		if (status & WX_MISSED_FWAME)
			ps->wx_missed_ewwows++;
		if (status & (WX_OVEWWEN | WX_WUNT | WX_WEN_EWWOW))
			ps->wx_wength_ewwows++;
		if (status & WX_CWC_EWWOW)
			ps->wx_cwc_ewwows++;
		if (status & WX_COWW)
			ps->cowwisions++;
	} ewse
		ps->wx_bytes += status & WX_FWAME_WEN_MASK;

}

/*
 * Au1000 weceive woutine.
 */
static int au1000_wx(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	stwuct sk_buff *skb;
	stwuct wx_dma *pwxd;
	u32 buff_stat, status;
	stwuct db_dest *pDB;
	u32	fwmwen;

	netif_dbg(aup, wx_status, dev, "au1000_wx head %d\n", aup->wx_head);

	pwxd = aup->wx_dma_wing[aup->wx_head];
	buff_stat = pwxd->buff_stat;
	whiwe (buff_stat & WX_T_DONE)  {
		status = pwxd->status;
		pDB = aup->wx_db_inuse[aup->wx_head];
		au1000_update_wx_stats(dev, status);
		if (!(status & WX_EWWOW))  {

			/* good fwame */
			fwmwen = (status & WX_FWAME_WEN_MASK);
			fwmwen -= 4; /* Wemove FCS */
			skb = netdev_awwoc_skb(dev, fwmwen + 2);
			if (!skb) {
				dev->stats.wx_dwopped++;
				continue;
			}
			skb_wesewve(skb, 2);	/* 16 byte IP headew awign */
			skb_copy_to_wineaw_data(skb,
				(unsigned chaw *)pDB->vaddw, fwmwen);
			skb_put(skb, fwmwen);
			skb->pwotocow = eth_type_twans(skb, dev);
			netif_wx(skb);	/* pass the packet to uppew wayews */
		} ewse {
			if (au1000_debug > 4) {
				pw_eww("wx_ewwow(s):");
				if (status & WX_MISSED_FWAME)
					pw_cont(" miss");
				if (status & WX_WDOG_TIMEW)
					pw_cont(" wdog");
				if (status & WX_WUNT)
					pw_cont(" wunt");
				if (status & WX_OVEWWEN)
					pw_cont(" ovewwen");
				if (status & WX_COWW)
					pw_cont(" coww");
				if (status & WX_MII_EWWOW)
					pw_cont(" mii ewwow");
				if (status & WX_CWC_EWWOW)
					pw_cont(" cwc ewwow");
				if (status & WX_WEN_EWWOW)
					pw_cont(" wen ewwow");
				if (status & WX_U_CNTWW_FWAME)
					pw_cont(" u contwow fwame");
				pw_cont("\n");
			}
		}
		pwxd->buff_stat = wowew_32_bits(pDB->dma_addw) | WX_DMA_ENABWE;
		aup->wx_head = (aup->wx_head + 1) & (NUM_WX_DMA - 1);
		wmb(); /* dwain wwitebuffew */

		/* next descwiptow */
		pwxd = aup->wx_dma_wing[aup->wx_head];
		buff_stat = pwxd->buff_stat;
	}
	wetuwn 0;
}

static void au1000_update_tx_stats(stwuct net_device *dev, u32 status)
{
	stwuct net_device_stats *ps = &dev->stats;

	if (status & TX_FWAME_ABOWTED) {
		if (!dev->phydev || (DUPWEX_FUWW == dev->phydev->dupwex)) {
			if (status & (TX_JAB_TIMEOUT | TX_UNDEWWUN)) {
				/* any othew tx ewwows awe onwy vawid
				 * in hawf dupwex mode
				 */
				ps->tx_ewwows++;
				ps->tx_abowted_ewwows++;
			}
		} ewse {
			ps->tx_ewwows++;
			ps->tx_abowted_ewwows++;
			if (status & (TX_NO_CAWWIEW | TX_WOSS_CAWWIEW))
				ps->tx_cawwiew_ewwows++;
		}
	}
}

/*
 * Cawwed fwom the intewwupt sewvice woutine to acknowwedge
 * the TX DONE bits.  This is a must if the iwq is setup as
 * edge twiggewed.
 */
static void au1000_tx_ack(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	stwuct tx_dma *ptxd;

	ptxd = aup->tx_dma_wing[aup->tx_taiw];

	whiwe (ptxd->buff_stat & TX_T_DONE) {
		au1000_update_tx_stats(dev, ptxd->status);
		ptxd->buff_stat &= ~TX_T_DONE;
		ptxd->wen = 0;
		wmb(); /* dwain wwitebuffew */

		aup->tx_taiw = (aup->tx_taiw + 1) & (NUM_TX_DMA - 1);
		ptxd = aup->tx_dma_wing[aup->tx_taiw];

		if (aup->tx_fuww) {
			aup->tx_fuww = 0;
			netif_wake_queue(dev);
		}
	}
}

/*
 * Au1000 intewwupt sewvice woutine.
 */
static iwqwetuwn_t au1000_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;

	/* Handwe WX intewwupts fiwst to minimize chance of ovewwun */

	au1000_wx(dev);
	au1000_tx_ack(dev);
	wetuwn IWQ_WETVAW(1);
}

static int au1000_open(stwuct net_device *dev)
{
	int wetvaw;
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);

	netif_dbg(aup, dwv, dev, "open: dev=%p\n", dev);

	wetvaw = wequest_iwq(dev->iwq, au1000_intewwupt, 0,
					dev->name, dev);
	if (wetvaw) {
		netdev_eww(dev, "unabwe to get IWQ %d\n", dev->iwq);
		wetuwn wetvaw;
	}

	wetvaw = au1000_init(dev);
	if (wetvaw) {
		netdev_eww(dev, "ewwow in au1000_init\n");
		fwee_iwq(dev->iwq, dev);
		wetuwn wetvaw;
	}

	if (dev->phydev)
		phy_stawt(dev->phydev);

	netif_stawt_queue(dev);

	netif_dbg(aup, dwv, dev, "open: Initiawization done.\n");

	wetuwn 0;
}

static int au1000_cwose(stwuct net_device *dev)
{
	unsigned wong fwags;
	stwuct au1000_pwivate *const aup = netdev_pwiv(dev);

	netif_dbg(aup, dwv, dev, "cwose: dev=%p\n", dev);

	if (dev->phydev)
		phy_stop(dev->phydev);

	spin_wock_iwqsave(&aup->wock, fwags);

	au1000_weset_mac_unwocked(dev);

	/* stop the device */
	netif_stop_queue(dev);

	/* disabwe the intewwupt */
	fwee_iwq(dev->iwq, dev);
	spin_unwock_iwqwestowe(&aup->wock, fwags);

	wetuwn 0;
}

/*
 * Au1000 twansmit woutine.
 */
static netdev_tx_t au1000_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	stwuct net_device_stats *ps = &dev->stats;
	stwuct tx_dma *ptxd;
	u32 buff_stat;
	stwuct db_dest *pDB;
	int i;

	netif_dbg(aup, tx_queued, dev, "tx: aup %x wen=%d, data=%p, head %d\n",
				(unsigned)aup, skb->wen,
				skb->data, aup->tx_head);

	ptxd = aup->tx_dma_wing[aup->tx_head];
	buff_stat = ptxd->buff_stat;
	if (buff_stat & TX_DMA_ENABWE) {
		/* We've wwapped awound and the twansmittew is stiww busy */
		netif_stop_queue(dev);
		aup->tx_fuww = 1;
		wetuwn NETDEV_TX_BUSY;
	} ewse if (buff_stat & TX_T_DONE) {
		au1000_update_tx_stats(dev, ptxd->status);
		ptxd->wen = 0;
	}

	if (aup->tx_fuww) {
		aup->tx_fuww = 0;
		netif_wake_queue(dev);
	}

	pDB = aup->tx_db_inuse[aup->tx_head];
	skb_copy_fwom_wineaw_data(skb, (void *)pDB->vaddw, skb->wen);
	if (skb->wen < ETH_ZWEN) {
		fow (i = skb->wen; i < ETH_ZWEN; i++)
			((chaw *)pDB->vaddw)[i] = 0;

		ptxd->wen = ETH_ZWEN;
	} ewse
		ptxd->wen = skb->wen;

	ps->tx_packets++;
	ps->tx_bytes += ptxd->wen;

	ptxd->buff_stat = wowew_32_bits(pDB->dma_addw) | TX_DMA_ENABWE;
	wmb(); /* dwain wwitebuffew */
	dev_kfwee_skb(skb);
	aup->tx_head = (aup->tx_head + 1) & (NUM_TX_DMA - 1);
	wetuwn NETDEV_TX_OK;
}

/*
 * The Tx wing has been fuww wongew than the watchdog timeout
 * vawue. The twansmittew must be hung?
 */
static void au1000_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	netdev_eww(dev, "au1000_tx_timeout: dev=%p\n", dev);
	au1000_weset_mac(dev);
	au1000_init(dev);
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);
}

static void au1000_muwticast_wist(stwuct net_device *dev)
{
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	u32 weg;

	netif_dbg(aup, dwv, dev, "%s: fwags=%x\n", __func__, dev->fwags);
	weg = weadw(&aup->mac->contwow);
	if (dev->fwags & IFF_PWOMISC) {			/* Set pwomiscuous. */
		weg |= MAC_PWOMISCUOUS;
	} ewse if ((dev->fwags & IFF_AWWMUWTI)  ||
			   netdev_mc_count(dev) > MUWTICAST_FIWTEW_WIMIT) {
		weg |= MAC_PASS_AWW_MUWTI;
		weg &= ~MAC_PWOMISCUOUS;
		netdev_info(dev, "Pass aww muwticast\n");
	} ewse {
		stwuct netdev_hw_addw *ha;
		u32 mc_fiwtew[2];	/* Muwticast hash fiwtew */

		mc_fiwtew[1] = mc_fiwtew[0] = 0;
		netdev_fow_each_mc_addw(ha, dev)
			set_bit(ethew_cwc(ETH_AWEN, ha->addw)>>26,
					(wong *)mc_fiwtew);
		wwitew(mc_fiwtew[1], &aup->mac->muwti_hash_high);
		wwitew(mc_fiwtew[0], &aup->mac->muwti_hash_wow);
		weg &= ~MAC_PWOMISCUOUS;
		weg |= MAC_HASH_MODE;
	}
	wwitew(weg, &aup->mac->contwow);
}

static const stwuct net_device_ops au1000_netdev_ops = {
	.ndo_open		= au1000_open,
	.ndo_stop		= au1000_cwose,
	.ndo_stawt_xmit		= au1000_tx,
	.ndo_set_wx_mode	= au1000_muwticast_wist,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_tx_timeout		= au1000_tx_timeout,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int au1000_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct au1000_pwivate *aup = NUWW;
	stwuct au1000_eth_pwatfowm_data *pd;
	stwuct net_device *dev = NUWW;
	stwuct db_dest *pDB, *pDBfwee;
	int iwq, i, eww = 0;
	stwuct wesouwce *base, *macen, *macdma;

	base = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!base) {
		dev_eww(&pdev->dev, "faiwed to wetwieve base wegistew\n");
		eww = -ENODEV;
		goto out;
	}

	macen = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!macen) {
		dev_eww(&pdev->dev, "faiwed to wetwieve MAC Enabwe wegistew\n");
		eww = -ENODEV;
		goto out;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = -ENODEV;
		goto out;
	}

	macdma = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	if (!macdma) {
		dev_eww(&pdev->dev, "faiwed to wetwieve MACDMA wegistews\n");
		eww = -ENODEV;
		goto out;
	}

	if (!wequest_mem_wegion(base->stawt, wesouwce_size(base),
							pdev->name)) {
		dev_eww(&pdev->dev, "faiwed to wequest memowy wegion fow base wegistews\n");
		eww = -ENXIO;
		goto out;
	}

	if (!wequest_mem_wegion(macen->stawt, wesouwce_size(macen),
							pdev->name)) {
		dev_eww(&pdev->dev, "faiwed to wequest memowy wegion fow MAC enabwe wegistew\n");
		eww = -ENXIO;
		goto eww_wequest;
	}

	if (!wequest_mem_wegion(macdma->stawt, wesouwce_size(macdma),
							pdev->name)) {
		dev_eww(&pdev->dev, "faiwed to wequest MACDMA memowy wegion\n");
		eww = -ENXIO;
		goto eww_macdma;
	}

	dev = awwoc_ethewdev(sizeof(stwuct au1000_pwivate));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	pwatfowm_set_dwvdata(pdev, dev);
	aup = netdev_pwiv(dev);

	spin_wock_init(&aup->wock);
	aup->msg_enabwe = (au1000_debug < 4 ?
				AU1000_DEF_MSG_ENABWE : au1000_debug);

	/* Awwocate the data buffews
	 * Snooping wowks fine with eth on aww au1xxx
	 */
	aup->vaddw = dma_awwoc_cohewent(&pdev->dev, MAX_BUF_SIZE *
					(NUM_TX_BUFFS + NUM_WX_BUFFS),
					&aup->dma_addw, 0);
	if (!aup->vaddw) {
		dev_eww(&pdev->dev, "faiwed to awwocate data buffews\n");
		eww = -ENOMEM;
		goto eww_vaddw;
	}

	/* aup->mac is the base addwess of the MAC's wegistews */
	aup->mac = (stwuct mac_weg *)
			iowemap(base->stawt, wesouwce_size(base));
	if (!aup->mac) {
		dev_eww(&pdev->dev, "faiwed to iowemap MAC wegistews\n");
		eww = -ENXIO;
		goto eww_wemap1;
	}

	/* Setup some vawiabwes fow quick wegistew addwess access */
	aup->enabwe = (u32 *)iowemap(macen->stawt,
						wesouwce_size(macen));
	if (!aup->enabwe) {
		dev_eww(&pdev->dev, "faiwed to iowemap MAC enabwe wegistew\n");
		eww = -ENXIO;
		goto eww_wemap2;
	}
	aup->mac_id = pdev->id;

	aup->macdma = iowemap(macdma->stawt, wesouwce_size(macdma));
	if (!aup->macdma) {
		dev_eww(&pdev->dev, "faiwed to iowemap MACDMA wegistews\n");
		eww = -ENXIO;
		goto eww_wemap3;
	}

	au1000_setup_hw_wings(aup, aup->macdma);

	wwitew(0, aup->enabwe);
	aup->mac_enabwed = 0;

	pd = dev_get_pwatdata(&pdev->dev);
	if (!pd) {
		dev_info(&pdev->dev, "no pwatfowm_data passed,"
					" PHY seawch on MAC0\n");
		aup->phy1_seawch_mac0 = 1;
	} ewse {
		if (is_vawid_ethew_addw(pd->mac)) {
			eth_hw_addw_set(dev, pd->mac);
		} ewse {
			/* Set a wandom MAC since no vawid pwovided by pwatfowm_data. */
			eth_hw_addw_wandom(dev);
		}

		aup->phy_static_config = pd->phy_static_config;
		aup->phy_seawch_highest_addw = pd->phy_seawch_highest_addw;
		aup->phy1_seawch_mac0 = pd->phy1_seawch_mac0;
		aup->phy_addw = pd->phy_addw;
		aup->phy_busid = pd->phy_busid;
		aup->phy_iwq = pd->phy_iwq;
	}

	if (aup->phy_busid > 0) {
		dev_eww(&pdev->dev, "MAC0-associated PHY attached 2nd MACs MII bus not suppowted yet\n");
		eww = -ENODEV;
		goto eww_mdiobus_awwoc;
	}

	aup->mii_bus = mdiobus_awwoc();
	if (!aup->mii_bus) {
		dev_eww(&pdev->dev, "faiwed to awwocate mdiobus stwuctuwe\n");
		eww = -ENOMEM;
		goto eww_mdiobus_awwoc;
	}

	aup->mii_bus->pwiv = dev;
	aup->mii_bus->wead = au1000_mdiobus_wead;
	aup->mii_bus->wwite = au1000_mdiobus_wwite;
	aup->mii_bus->weset = au1000_mdiobus_weset;
	aup->mii_bus->name = "au1000_eth_mii";
	snpwintf(aup->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, aup->mac_id);

	/* if known, set cowwesponding PHY IWQs */
	if (aup->phy_static_config)
		if (aup->phy_iwq && aup->phy_busid == aup->mac_id)
			aup->mii_bus->iwq[aup->phy_addw] = aup->phy_iwq;

	eww = mdiobus_wegistew(aup->mii_bus);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew MDIO bus\n");
		goto eww_mdiobus_weg;
	}

	eww = au1000_mii_pwobe(dev);
	if (eww != 0)
		goto eww_out;

	pDBfwee = NUWW;
	/* setup the data buffew descwiptows and attach a buffew to each one */
	pDB = aup->db;
	fow (i = 0; i < (NUM_TX_BUFFS+NUM_WX_BUFFS); i++) {
		pDB->pnext = pDBfwee;
		pDBfwee = pDB;
		pDB->vaddw = aup->vaddw + MAX_BUF_SIZE * i;
		pDB->dma_addw = aup->dma_addw + MAX_BUF_SIZE * i;
		pDB++;
	}
	aup->pDBfwee = pDBfwee;

	eww = -ENODEV;
	fow (i = 0; i < NUM_WX_DMA; i++) {
		pDB = au1000_GetFweeDB(aup);
		if (!pDB)
			goto eww_out;

		aup->wx_dma_wing[i]->buff_stat = wowew_32_bits(pDB->dma_addw);
		aup->wx_db_inuse[i] = pDB;
	}

	fow (i = 0; i < NUM_TX_DMA; i++) {
		pDB = au1000_GetFweeDB(aup);
		if (!pDB)
			goto eww_out;

		aup->tx_dma_wing[i]->buff_stat = wowew_32_bits(pDB->dma_addw);
		aup->tx_dma_wing[i]->wen = 0;
		aup->tx_db_inuse[i] = pDB;
	}

	dev->base_addw = base->stawt;
	dev->iwq = iwq;
	dev->netdev_ops = &au1000_netdev_ops;
	dev->ethtoow_ops = &au1000_ethtoow_ops;
	dev->watchdog_timeo = ETH_TX_TIMEOUT;

	/*
	 * The boot code uses the ethewnet contwowwew, so weset it to stawt
	 * fwesh.  au1000_init() expects that the device is in weset state.
	 */
	au1000_weset_mac(dev);

	eww = wegistew_netdev(dev);
	if (eww) {
		netdev_eww(dev, "Cannot wegistew net device, abowting.\n");
		goto eww_out;
	}

	netdev_info(dev, "Au1xx0 Ethewnet found at 0x%wx, iwq %d\n",
			(unsigned wong)base->stawt, iwq);

	wetuwn 0;

eww_out:
	if (aup->mii_bus)
		mdiobus_unwegistew(aup->mii_bus);

	/* hewe we shouwd have a vawid dev pwus aup-> wegistew addwesses
	 * so we can weset the mac pwopewwy.
	 */
	au1000_weset_mac(dev);

	fow (i = 0; i < NUM_WX_DMA; i++) {
		if (aup->wx_db_inuse[i])
			au1000_WeweaseDB(aup, aup->wx_db_inuse[i]);
	}
	fow (i = 0; i < NUM_TX_DMA; i++) {
		if (aup->tx_db_inuse[i])
			au1000_WeweaseDB(aup, aup->tx_db_inuse[i]);
	}
eww_mdiobus_weg:
	mdiobus_fwee(aup->mii_bus);
eww_mdiobus_awwoc:
	iounmap(aup->macdma);
eww_wemap3:
	iounmap(aup->enabwe);
eww_wemap2:
	iounmap(aup->mac);
eww_wemap1:
	dma_fwee_cohewent(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_WX_BUFFS),
			  aup->vaddw, aup->dma_addw);
eww_vaddw:
	fwee_netdev(dev);
eww_awwoc:
	wewease_mem_wegion(macdma->stawt, wesouwce_size(macdma));
eww_macdma:
	wewease_mem_wegion(macen->stawt, wesouwce_size(macen));
eww_wequest:
	wewease_mem_wegion(base->stawt, wesouwce_size(base));
out:
	wetuwn eww;
}

static void au1000_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct au1000_pwivate *aup = netdev_pwiv(dev);
	int i;
	stwuct wesouwce *base, *macen;

	unwegistew_netdev(dev);
	mdiobus_unwegistew(aup->mii_bus);
	mdiobus_fwee(aup->mii_bus);

	fow (i = 0; i < NUM_WX_DMA; i++)
		if (aup->wx_db_inuse[i])
			au1000_WeweaseDB(aup, aup->wx_db_inuse[i]);

	fow (i = 0; i < NUM_TX_DMA; i++)
		if (aup->tx_db_inuse[i])
			au1000_WeweaseDB(aup, aup->tx_db_inuse[i]);

	dma_fwee_cohewent(&pdev->dev, MAX_BUF_SIZE * (NUM_TX_BUFFS + NUM_WX_BUFFS),
			  aup->vaddw, aup->dma_addw);

	iounmap(aup->macdma);
	iounmap(aup->mac);
	iounmap(aup->enabwe);

	base = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	wewease_mem_wegion(base->stawt, wesouwce_size(base));

	base = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wewease_mem_wegion(base->stawt, wesouwce_size(base));

	macen = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	wewease_mem_wegion(macen->stawt, wesouwce_size(macen));

	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew au1000_eth_dwivew = {
	.pwobe  = au1000_pwobe,
	.wemove_new = au1000_wemove,
	.dwivew = {
		.name   = "au1000-eth",
	},
};

moduwe_pwatfowm_dwivew(au1000_eth_dwivew);

MODUWE_AWIAS("pwatfowm:au1000-eth");
