/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fwamewowk and dwivews fow configuwing and weading diffewent PHYs
 * Based on code in sungem_phy.c and (wong-wemoved) gianfaw_phy.c
 *
 * Authow: Andy Fweming
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 */

#ifndef __PHY_H
#define __PHY_H

#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethtoow.h>
#incwude <winux/weds.h>
#incwude <winux/winkmode.h>
#incwude <winux/netwink.h>
#incwude <winux/mdio.h>
#incwude <winux/mii.h>
#incwude <winux/mii_timestampew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/iopoww.h>
#incwude <winux/wefcount.h>

#incwude <winux/atomic.h>

#define PHY_DEFAUWT_FEATUWES	(SUPPOWTED_Autoneg | \
				 SUPPOWTED_TP | \
				 SUPPOWTED_MII)

#define PHY_10BT_FEATUWES	(SUPPOWTED_10baseT_Hawf | \
				 SUPPOWTED_10baseT_Fuww)

#define PHY_100BT_FEATUWES	(SUPPOWTED_100baseT_Hawf | \
				 SUPPOWTED_100baseT_Fuww)

#define PHY_1000BT_FEATUWES	(SUPPOWTED_1000baseT_Hawf | \
				 SUPPOWTED_1000baseT_Fuww)

extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_t1_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_basic_t1s_p2mp_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_fibwe_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_gbit_aww_powts_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_fec_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_10gbit_fuww_featuwes) __wo_aftew_init;
extewn __ETHTOOW_DECWAWE_WINK_MODE_MASK(phy_eee_cap1_featuwes) __wo_aftew_init;

#define PHY_BASIC_FEATUWES ((unsigned wong *)&phy_basic_featuwes)
#define PHY_BASIC_T1_FEATUWES ((unsigned wong *)&phy_basic_t1_featuwes)
#define PHY_BASIC_T1S_P2MP_FEATUWES ((unsigned wong *)&phy_basic_t1s_p2mp_featuwes)
#define PHY_GBIT_FEATUWES ((unsigned wong *)&phy_gbit_featuwes)
#define PHY_GBIT_FIBWE_FEATUWES ((unsigned wong *)&phy_gbit_fibwe_featuwes)
#define PHY_GBIT_AWW_POWTS_FEATUWES ((unsigned wong *)&phy_gbit_aww_powts_featuwes)
#define PHY_10GBIT_FEATUWES ((unsigned wong *)&phy_10gbit_featuwes)
#define PHY_10GBIT_FEC_FEATUWES ((unsigned wong *)&phy_10gbit_fec_featuwes)
#define PHY_10GBIT_FUWW_FEATUWES ((unsigned wong *)&phy_10gbit_fuww_featuwes)
#define PHY_EEE_CAP1_FEATUWES ((unsigned wong *)&phy_eee_cap1_featuwes)

extewn const int phy_basic_powts_awway[3];
extewn const int phy_fibwe_powt_awway[1];
extewn const int phy_aww_powts_featuwes_awway[7];
extewn const int phy_10_100_featuwes_awway[4];
extewn const int phy_basic_t1_featuwes_awway[3];
extewn const int phy_basic_t1s_p2mp_featuwes_awway[2];
extewn const int phy_gbit_featuwes_awway[2];
extewn const int phy_10gbit_featuwes_awway[1];

/*
 * Set phydev->iwq to PHY_POWW if intewwupts awe not suppowted,
 * ow not desiwed fow this PHY.  Set to PHY_MAC_INTEWWUPT if
 * the attached MAC dwivew handwes the intewwupt
 */
#define PHY_POWW		-1
#define PHY_MAC_INTEWWUPT	-2

#define PHY_IS_INTEWNAW		0x00000001
#define PHY_WST_AFTEW_CWK_EN	0x00000002
#define PHY_POWW_CABWE_TEST	0x00000004
#define PHY_AWWAYS_CAWW_SUSPEND	0x00000008
#define MDIO_DEVICE_IS_PHY	0x80000000

/**
 * enum phy_intewface_t - Intewface Mode definitions
 *
 * @PHY_INTEWFACE_MODE_NA: Not Appwicabwe - don't touch
 * @PHY_INTEWFACE_MODE_INTEWNAW: No intewface, MAC and PHY combined
 * @PHY_INTEWFACE_MODE_MII: Media-independent intewface
 * @PHY_INTEWFACE_MODE_GMII: Gigabit media-independent intewface
 * @PHY_INTEWFACE_MODE_SGMII: Sewiaw gigabit media-independent intewface
 * @PHY_INTEWFACE_MODE_TBI: Ten Bit Intewface
 * @PHY_INTEWFACE_MODE_WEVMII: Wevewse Media Independent Intewface
 * @PHY_INTEWFACE_MODE_WMII: Weduced Media Independent Intewface
 * @PHY_INTEWFACE_MODE_WEVWMII: Weduced Media Independent Intewface in PHY wowe
 * @PHY_INTEWFACE_MODE_WGMII: Weduced gigabit media-independent intewface
 * @PHY_INTEWFACE_MODE_WGMII_ID: WGMII with Intewnaw WX+TX deway
 * @PHY_INTEWFACE_MODE_WGMII_WXID: WGMII with Intewnaw WX deway
 * @PHY_INTEWFACE_MODE_WGMII_TXID: WGMII with Intewnaw WX deway
 * @PHY_INTEWFACE_MODE_WTBI: Weduced TBI
 * @PHY_INTEWFACE_MODE_SMII: Sewiaw MII
 * @PHY_INTEWFACE_MODE_XGMII: 10 gigabit media-independent intewface
 * @PHY_INTEWFACE_MODE_XWGMII:40 gigabit media-independent intewface
 * @PHY_INTEWFACE_MODE_MOCA: Muwtimedia ovew Coax
 * @PHY_INTEWFACE_MODE_PSGMII: Penta SGMII
 * @PHY_INTEWFACE_MODE_QSGMII: Quad SGMII
 * @PHY_INTEWFACE_MODE_TWGMII: Tuwbo WGMII
 * @PHY_INTEWFACE_MODE_100BASEX: 100 BaseX
 * @PHY_INTEWFACE_MODE_1000BASEX: 1000 BaseX
 * @PHY_INTEWFACE_MODE_2500BASEX: 2500 BaseX
 * @PHY_INTEWFACE_MODE_5GBASEW: 5G BaseW
 * @PHY_INTEWFACE_MODE_WXAUI: Weduced XAUI
 * @PHY_INTEWFACE_MODE_XAUI: 10 Gigabit Attachment Unit Intewface
 * @PHY_INTEWFACE_MODE_10GBASEW: 10G BaseW
 * @PHY_INTEWFACE_MODE_25GBASEW: 25G BaseW
 * @PHY_INTEWFACE_MODE_USXGMII:  Univewsaw Sewiaw 10GE MII
 * @PHY_INTEWFACE_MODE_10GKW: 10GBASE-KW - with Cwause 73 AN
 * @PHY_INTEWFACE_MODE_QUSGMII: Quad Univewsaw SGMII
 * @PHY_INTEWFACE_MODE_1000BASEKX: 1000Base-KX - with Cwause 73 AN
 * @PHY_INTEWFACE_MODE_MAX: Book keeping
 *
 * Descwibes the intewface between the MAC and PHY.
 */
typedef enum {
	PHY_INTEWFACE_MODE_NA,
	PHY_INTEWFACE_MODE_INTEWNAW,
	PHY_INTEWFACE_MODE_MII,
	PHY_INTEWFACE_MODE_GMII,
	PHY_INTEWFACE_MODE_SGMII,
	PHY_INTEWFACE_MODE_TBI,
	PHY_INTEWFACE_MODE_WEVMII,
	PHY_INTEWFACE_MODE_WMII,
	PHY_INTEWFACE_MODE_WEVWMII,
	PHY_INTEWFACE_MODE_WGMII,
	PHY_INTEWFACE_MODE_WGMII_ID,
	PHY_INTEWFACE_MODE_WGMII_WXID,
	PHY_INTEWFACE_MODE_WGMII_TXID,
	PHY_INTEWFACE_MODE_WTBI,
	PHY_INTEWFACE_MODE_SMII,
	PHY_INTEWFACE_MODE_XGMII,
	PHY_INTEWFACE_MODE_XWGMII,
	PHY_INTEWFACE_MODE_MOCA,
	PHY_INTEWFACE_MODE_PSGMII,
	PHY_INTEWFACE_MODE_QSGMII,
	PHY_INTEWFACE_MODE_TWGMII,
	PHY_INTEWFACE_MODE_100BASEX,
	PHY_INTEWFACE_MODE_1000BASEX,
	PHY_INTEWFACE_MODE_2500BASEX,
	PHY_INTEWFACE_MODE_5GBASEW,
	PHY_INTEWFACE_MODE_WXAUI,
	PHY_INTEWFACE_MODE_XAUI,
	/* 10GBASE-W, XFI, SFI - singwe wane 10G Sewdes */
	PHY_INTEWFACE_MODE_10GBASEW,
	PHY_INTEWFACE_MODE_25GBASEW,
	PHY_INTEWFACE_MODE_USXGMII,
	/* 10GBASE-KW - with Cwause 73 AN */
	PHY_INTEWFACE_MODE_10GKW,
	PHY_INTEWFACE_MODE_QUSGMII,
	PHY_INTEWFACE_MODE_1000BASEKX,
	PHY_INTEWFACE_MODE_MAX,
} phy_intewface_t;

/* PHY intewface mode bitmap handwing */
#define DECWAWE_PHY_INTEWFACE_MASK(name) \
	DECWAWE_BITMAP(name, PHY_INTEWFACE_MODE_MAX)

static inwine void phy_intewface_zewo(unsigned wong *intf)
{
	bitmap_zewo(intf, PHY_INTEWFACE_MODE_MAX);
}

static inwine boow phy_intewface_empty(const unsigned wong *intf)
{
	wetuwn bitmap_empty(intf, PHY_INTEWFACE_MODE_MAX);
}

static inwine void phy_intewface_and(unsigned wong *dst, const unsigned wong *a,
				     const unsigned wong *b)
{
	bitmap_and(dst, a, b, PHY_INTEWFACE_MODE_MAX);
}

static inwine void phy_intewface_ow(unsigned wong *dst, const unsigned wong *a,
				    const unsigned wong *b)
{
	bitmap_ow(dst, a, b, PHY_INTEWFACE_MODE_MAX);
}

static inwine void phy_intewface_set_wgmii(unsigned wong *intf)
{
	__set_bit(PHY_INTEWFACE_MODE_WGMII, intf);
	__set_bit(PHY_INTEWFACE_MODE_WGMII_ID, intf);
	__set_bit(PHY_INTEWFACE_MODE_WGMII_WXID, intf);
	__set_bit(PHY_INTEWFACE_MODE_WGMII_TXID, intf);
}

/*
 * phy_suppowted_speeds - wetuwn aww speeds cuwwentwy suppowted by a PHY device
 */
unsigned int phy_suppowted_speeds(stwuct phy_device *phy,
				      unsigned int *speeds,
				      unsigned int size);

/**
 * phy_modes - map phy_intewface_t enum to device twee binding of phy-mode
 * @intewface: enum phy_intewface_t vawue
 *
 * Descwiption: maps enum &phy_intewface_t defined in this fiwe
 * into the device twee binding of 'phy-mode', so that Ethewnet
 * device dwivew can get PHY intewface fwom device twee.
 */
static inwine const chaw *phy_modes(phy_intewface_t intewface)
{
	switch (intewface) {
	case PHY_INTEWFACE_MODE_NA:
		wetuwn "";
	case PHY_INTEWFACE_MODE_INTEWNAW:
		wetuwn "intewnaw";
	case PHY_INTEWFACE_MODE_MII:
		wetuwn "mii";
	case PHY_INTEWFACE_MODE_GMII:
		wetuwn "gmii";
	case PHY_INTEWFACE_MODE_SGMII:
		wetuwn "sgmii";
	case PHY_INTEWFACE_MODE_TBI:
		wetuwn "tbi";
	case PHY_INTEWFACE_MODE_WEVMII:
		wetuwn "wev-mii";
	case PHY_INTEWFACE_MODE_WMII:
		wetuwn "wmii";
	case PHY_INTEWFACE_MODE_WEVWMII:
		wetuwn "wev-wmii";
	case PHY_INTEWFACE_MODE_WGMII:
		wetuwn "wgmii";
	case PHY_INTEWFACE_MODE_WGMII_ID:
		wetuwn "wgmii-id";
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		wetuwn "wgmii-wxid";
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wetuwn "wgmii-txid";
	case PHY_INTEWFACE_MODE_WTBI:
		wetuwn "wtbi";
	case PHY_INTEWFACE_MODE_SMII:
		wetuwn "smii";
	case PHY_INTEWFACE_MODE_XGMII:
		wetuwn "xgmii";
	case PHY_INTEWFACE_MODE_XWGMII:
		wetuwn "xwgmii";
	case PHY_INTEWFACE_MODE_MOCA:
		wetuwn "moca";
	case PHY_INTEWFACE_MODE_PSGMII:
		wetuwn "psgmii";
	case PHY_INTEWFACE_MODE_QSGMII:
		wetuwn "qsgmii";
	case PHY_INTEWFACE_MODE_TWGMII:
		wetuwn "twgmii";
	case PHY_INTEWFACE_MODE_1000BASEX:
		wetuwn "1000base-x";
	case PHY_INTEWFACE_MODE_1000BASEKX:
		wetuwn "1000base-kx";
	case PHY_INTEWFACE_MODE_2500BASEX:
		wetuwn "2500base-x";
	case PHY_INTEWFACE_MODE_5GBASEW:
		wetuwn "5gbase-w";
	case PHY_INTEWFACE_MODE_WXAUI:
		wetuwn "wxaui";
	case PHY_INTEWFACE_MODE_XAUI:
		wetuwn "xaui";
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn "10gbase-w";
	case PHY_INTEWFACE_MODE_25GBASEW:
		wetuwn "25gbase-w";
	case PHY_INTEWFACE_MODE_USXGMII:
		wetuwn "usxgmii";
	case PHY_INTEWFACE_MODE_10GKW:
		wetuwn "10gbase-kw";
	case PHY_INTEWFACE_MODE_100BASEX:
		wetuwn "100base-x";
	case PHY_INTEWFACE_MODE_QUSGMII:
		wetuwn "qusgmii";
	defauwt:
		wetuwn "unknown";
	}
}

#define PHY_INIT_TIMEOUT	100000
#define PHY_FOWCE_TIMEOUT	10

#define PHY_MAX_ADDW	32

/* Used when twying to connect to a specific phy (mii bus id:phy device id) */
#define PHY_ID_FMT "%s:%02x"

#define MII_BUS_ID_SIZE	61

stwuct device;
stwuct kewnew_hwtstamp_config;
stwuct phywink;
stwuct sfp_bus;
stwuct sfp_upstweam_ops;
stwuct sk_buff;

/**
 * stwuct mdio_bus_stats - Statistics countews fow MDIO busses
 * @twansfews: Totaw numbew of twansfews, i.e. @wwites + @weads
 * @ewwows: Numbew of MDIO twansfews that wetuwned an ewwow
 * @wwites: Numbew of wwite twansfews
 * @weads: Numbew of wead twansfews
 * @syncp: Synchwonisation fow incwementing statistics
 */
stwuct mdio_bus_stats {
	u64_stats_t twansfews;
	u64_stats_t ewwows;
	u64_stats_t wwites;
	u64_stats_t weads;
	/* Must be wast, add new statistics above */
	stwuct u64_stats_sync syncp;
};

/**
 * stwuct phy_package_shawed - Shawed infowmation in PHY packages
 * @base_addw: Base PHY addwess of PHY package used to combine PHYs
 *   in one package and fow offset cawcuwation of phy_package_wead/wwite
 * @wefcnt: Numbew of PHYs connected to this shawed data
 * @fwags: Initiawization of PHY package
 * @pwiv_size: Size of the shawed pwivate data @pwiv
 * @pwiv: Dwivew pwivate data shawed acwoss a PHY package
 *
 * Wepwesents a shawed stwuctuwe between diffewent phydev's in the same
 * package, fow exampwe a quad PHY. See phy_package_join() and
 * phy_package_weave().
 */
stwuct phy_package_shawed {
	u8 base_addw;
	wefcount_t wefcnt;
	unsigned wong fwags;
	size_t pwiv_size;

	/* pwivate data pointew */
	/* note that this pointew is shawed between diffewent phydevs and
	 * the usew has to take cawe of appwopwiate wocking. It is awwocated
	 * and fweed automaticawwy by phy_package_join() and
	 * phy_package_weave().
	 */
	void *pwiv;
};

/* used as bit numbew in atomic bitops */
#define PHY_SHAWED_F_INIT_DONE  0
#define PHY_SHAWED_F_PWOBE_DONE 1

/**
 * stwuct mii_bus - Wepwesents an MDIO bus
 *
 * @ownew: Who owns this device
 * @name: Usew fwiendwy name fow this MDIO device, ow dwivew name
 * @id: Unique identifiew fow this bus, typicaw fwom bus hiewawchy
 * @pwiv: Dwivew pwivate data
 *
 * The Bus cwass fow PHYs.  Devices which pwovide access to
 * PHYs shouwd wegistew using this stwuctuwe
 */
stwuct mii_bus {
	stwuct moduwe *ownew;
	const chaw *name;
	chaw id[MII_BUS_ID_SIZE];
	void *pwiv;
	/** @wead: Pewfowm a wead twansfew on the bus */
	int (*wead)(stwuct mii_bus *bus, int addw, int wegnum);
	/** @wwite: Pewfowm a wwite twansfew on the bus */
	int (*wwite)(stwuct mii_bus *bus, int addw, int wegnum, u16 vaw);
	/** @wead_c45: Pewfowm a C45 wead twansfew on the bus */
	int (*wead_c45)(stwuct mii_bus *bus, int addw, int devnum, int wegnum);
	/** @wwite_c45: Pewfowm a C45 wwite twansfew on the bus */
	int (*wwite_c45)(stwuct mii_bus *bus, int addw, int devnum,
			 int wegnum, u16 vaw);
	/** @weset: Pewfowm a weset of the bus */
	int (*weset)(stwuct mii_bus *bus);

	/** @stats: Statistic countews pew device on the bus */
	stwuct mdio_bus_stats stats[PHY_MAX_ADDW];

	/**
	 * @mdio_wock: A wock to ensuwe that onwy one thing can wead/wwite
	 * the MDIO bus at a time
	 */
	stwuct mutex mdio_wock;

	/** @pawent: Pawent device of this bus */
	stwuct device *pawent;
	/** @state: State of bus stwuctuwe */
	enum {
		MDIOBUS_AWWOCATED = 1,
		MDIOBUS_WEGISTEWED,
		MDIOBUS_UNWEGISTEWED,
		MDIOBUS_WEWEASED,
	} state;

	/** @dev: Kewnew device wepwesentation */
	stwuct device dev;

	/** @mdio_map: wist of aww MDIO devices on bus */
	stwuct mdio_device *mdio_map[PHY_MAX_ADDW];

	/** @phy_mask: PHY addwesses to be ignowed when pwobing */
	u32 phy_mask;

	/** @phy_ignowe_ta_mask: PHY addwesses to ignowe the TA/wead faiwuwe */
	u32 phy_ignowe_ta_mask;

	/**
	 * @iwq: An awway of intewwupts, each PHY's intewwupt at the index
	 * matching its addwess
	 */
	int iwq[PHY_MAX_ADDW];

	/** @weset_deway_us: GPIO weset puwse width in micwoseconds */
	int weset_deway_us;
	/** @weset_post_deway_us: GPIO weset deassewt deway in micwoseconds */
	int weset_post_deway_us;
	/** @weset_gpiod: Weset GPIO descwiptow pointew */
	stwuct gpio_desc *weset_gpiod;

	/** @shawed_wock: pwotect access to the shawed ewement */
	stwuct mutex shawed_wock;

	/** @shawed: shawed state acwoss diffewent PHYs */
	stwuct phy_package_shawed *shawed[PHY_MAX_ADDW];
};
#define to_mii_bus(d) containew_of(d, stwuct mii_bus, dev)

stwuct mii_bus *mdiobus_awwoc_size(size_t size);

/**
 * mdiobus_awwoc - Awwocate an MDIO bus stwuctuwe
 *
 * The intewnaw state of the MDIO bus wiww be set of MDIOBUS_AWWOCATED weady
 * fow the dwivew to wegistew the bus.
 */
static inwine stwuct mii_bus *mdiobus_awwoc(void)
{
	wetuwn mdiobus_awwoc_size(0);
}

int __mdiobus_wegistew(stwuct mii_bus *bus, stwuct moduwe *ownew);
int __devm_mdiobus_wegistew(stwuct device *dev, stwuct mii_bus *bus,
			    stwuct moduwe *ownew);
#define mdiobus_wegistew(bus) __mdiobus_wegistew(bus, THIS_MODUWE)
#define devm_mdiobus_wegistew(dev, bus) \
		__devm_mdiobus_wegistew(dev, bus, THIS_MODUWE)

void mdiobus_unwegistew(stwuct mii_bus *bus);
void mdiobus_fwee(stwuct mii_bus *bus);
stwuct mii_bus *devm_mdiobus_awwoc_size(stwuct device *dev, int sizeof_pwiv);
static inwine stwuct mii_bus *devm_mdiobus_awwoc(stwuct device *dev)
{
	wetuwn devm_mdiobus_awwoc_size(dev, 0);
}

stwuct mii_bus *mdio_find_bus(const chaw *mdio_name);
stwuct phy_device *mdiobus_scan_c22(stwuct mii_bus *bus, int addw);

#define PHY_INTEWWUPT_DISABWED	fawse
#define PHY_INTEWWUPT_ENABWED	twue

/**
 * enum phy_state - PHY state machine states:
 *
 * @PHY_DOWN: PHY device and dwivew awe not weady fow anything.  pwobe
 * shouwd be cawwed if and onwy if the PHY is in this state,
 * given that the PHY device exists.
 * - PHY dwivew pwobe function wiww set the state to @PHY_WEADY
 *
 * @PHY_WEADY: PHY is weady to send and weceive packets, but the
 * contwowwew is not.  By defauwt, PHYs which do not impwement
 * pwobe wiww be set to this state by phy_pwobe().
 * - stawt wiww set the state to UP
 *
 * @PHY_UP: The PHY and attached device awe weady to do wowk.
 * Intewwupts shouwd be stawted hewe.
 * - timew moves to @PHY_NOWINK ow @PHY_WUNNING
 *
 * @PHY_NOWINK: PHY is up, but not cuwwentwy pwugged in.
 * - iwq ow timew wiww set @PHY_WUNNING if wink comes back
 * - phy_stop moves to @PHY_HAWTED
 *
 * @PHY_WUNNING: PHY is cuwwentwy up, wunning, and possibwy sending
 * and/ow weceiving packets
 * - iwq ow timew wiww set @PHY_NOWINK if wink goes down
 * - phy_stop moves to @PHY_HAWTED
 *
 * @PHY_CABWETEST: PHY is pewfowming a cabwe test. Packet weception/sending
 * is not expected to wowk, cawwiew wiww be indicated as down. PHY wiww be
 * poww once pew second, ow on intewwupt fow it cuwwent state.
 * Once compwete, move to UP to westawt the PHY.
 * - phy_stop abowts the wunning test and moves to @PHY_HAWTED
 *
 * @PHY_HAWTED: PHY is up, but no powwing ow intewwupts awe done.
 * - phy_stawt moves to @PHY_UP
 *
 * @PHY_EWWOW: PHY is up, but is in an ewwow state.
 * - phy_stop moves to @PHY_HAWTED
 */
enum phy_state {
	PHY_DOWN = 0,
	PHY_WEADY,
	PHY_HAWTED,
	PHY_EWWOW,
	PHY_UP,
	PHY_WUNNING,
	PHY_NOWINK,
	PHY_CABWETEST,
};

#define MDIO_MMD_NUM 32

/**
 * stwuct phy_c45_device_ids - 802.3-c45 Device Identifiews
 * @devices_in_package: IEEE 802.3 devices in package wegistew vawue.
 * @mmds_pwesent: bit vectow of MMDs pwesent.
 * @device_ids: The device identifew fow each pwesent device.
 */
stwuct phy_c45_device_ids {
	u32 devices_in_package;
	u32 mmds_pwesent;
	u32 device_ids[MDIO_MMD_NUM];
};

stwuct macsec_context;
stwuct macsec_ops;

/**
 * stwuct phy_device - An instance of a PHY
 *
 * @mdio: MDIO bus this PHY is on
 * @dwv: Pointew to the dwivew fow this PHY instance
 * @devwink: Cweate a wink between phy dev and mac dev, if the extewnaw phy
 *           used by cuwwent mac intewface is managed by anothew mac intewface.
 * @phy_id: UID fow this device found duwing discovewy
 * @c45_ids: 802.3-c45 Device Identifiews if is_c45.
 * @is_c45:  Set to twue if this PHY uses cwause 45 addwessing.
 * @is_intewnaw: Set to twue if this PHY is intewnaw to a MAC.
 * @is_pseudo_fixed_wink: Set to twue if this PHY is an Ethewnet switch, etc.
 * @is_gigabit_capabwe: Set to twue if PHY suppowts 1000Mbps
 * @has_fixups: Set to twue if this PHY has fixups/quiwks.
 * @suspended: Set to twue if this PHY has been suspended successfuwwy.
 * @suspended_by_mdio_bus: Set to twue if this PHY was suspended by MDIO bus.
 * @sysfs_winks: Intewnaw boowean twacking sysfs symbowic winks setup/wemovaw.
 * @woopback_enabwed: Set twue if this PHY has been woopbacked successfuwwy.
 * @downshifted_wate: Set twue if wink speed has been downshifted.
 * @is_on_sfp_moduwe: Set twue if PHY is wocated on an SFP moduwe.
 * @mac_managed_pm: Set twue if MAC dwivew takes of suspending/wesuming PHY
 * @wow_enabwed: Set to twue if the PHY ow the attached MAC have Wake-on-WAN
 * 		 enabwed.
 * @state: State of the PHY fow management puwposes
 * @dev_fwags: Device-specific fwags used by the PHY dwivew.
 *
 *      - Bits [15:0] awe fwee to use by the PHY dwivew to communicate
 *        dwivew specific behaviow.
 *      - Bits [23:16] awe cuwwentwy wesewved fow futuwe use.
 *      - Bits [31:24] awe wesewved fow defining genewic
 *        PHY dwivew behaviow.
 * @iwq: IWQ numbew of the PHY's intewwupt (-1 if none)
 * @phywink: Pointew to phywink instance fow this PHY
 * @sfp_bus_attached: Fwag indicating whethew the SFP bus has been attached
 * @sfp_bus: SFP bus attached to this PHY's fibew powt
 * @attached_dev: The attached enet dwivew's device instance ptw
 * @adjust_wink: Cawwback fow the enet contwowwew to wespond to changes: in the
 *               wink state.
 * @phy_wink_change: Cawwback fow phywink fow notification of wink change
 * @macsec_ops: MACsec offwoading ops.
 *
 * @speed: Cuwwent wink speed
 * @dupwex: Cuwwent dupwex
 * @powt: Cuwwent powt
 * @pause: Cuwwent pause
 * @asym_pause: Cuwwent asymmetwic pause
 * @suppowted: Combined MAC/PHY suppowted winkmodes
 * @advewtising: Cuwwentwy advewtised winkmodes
 * @adv_owd: Saved advewtised whiwe powew saving fow WoW
 * @suppowted_eee: suppowted PHY EEE winkmodes
 * @advewtising_eee: Cuwwentwy advewtised EEE winkmodes
 * @eee_enabwed: Fwag indicating whethew the EEE featuwe is enabwed
 * @wp_advewtising: Cuwwent wink pawtnew advewtised winkmodes
 * @host_intewfaces: PHY intewface modes suppowted by host
 * @eee_bwoken_modes: Enewgy efficient ethewnet modes which shouwd be pwohibited
 * @autoneg: Fwag autoneg being used
 * @wate_matching: Cuwwent wate matching mode
 * @wink: Cuwwent wink state
 * @autoneg_compwete: Fwag auto negotiation of the wink has compweted
 * @mdix: Cuwwent cwossovew
 * @mdix_ctww: Usew setting of cwossovew
 * @pma_extabwe: Cached vawue of PMA/PMD Extended Abiwities Wegistew
 * @intewwupts: Fwag intewwupts have been enabwed
 * @iwq_suspended: Fwag indicating PHY is suspended and thewefowe intewwupt
 *                 handwing shaww be postponed untiw PHY has wesumed
 * @iwq_wewun: Fwag indicating intewwupts occuwwed whiwe PHY was suspended,
 *             wequiwing a wewun of the intewwupt handwew aftew wesume
 * @intewface: enum phy_intewface_t vawue
 * @possibwe_intewfaces: bitmap if intewface modes that the attached PHY
 *			 wiww switch between depending on media speed.
 * @skb: Netwink message fow cabwe diagnostics
 * @nest: Netwink nest used fow cabwe diagnostics
 * @ehdw: nNtwink headew fow cabwe diagnostics
 * @phy_wed_twiggews: Awway of WED twiggews
 * @phy_num_wed_twiggews: Numbew of twiggews in @phy_wed_twiggews
 * @wed_wink_twiggew: WED twiggew fow wink up/down
 * @wast_twiggewed: wast WED twiggew fow wink speed
 * @weds: wist of PHY WED stwuctuwes
 * @mastew_swave_set: Usew wequested mastew/swave configuwation
 * @mastew_swave_get: Cuwwent mastew/swave advewtisement
 * @mastew_swave_state: Cuwwent mastew/swave configuwation
 * @mii_ts: Pointew to time stampew cawwbacks
 * @psec: Pointew to Powew Souwcing Equipment contwow stwuct
 * @wock:  Mutex fow sewiawization access to PHY
 * @state_queue: Wowk queue fow state machine
 * @wink_down_events: Numbew of times wink was wost
 * @shawed: Pointew to pwivate data shawed by phys in one package
 * @pwiv: Pointew to dwivew pwivate data
 *
 * intewwupts cuwwentwy onwy suppowts enabwed ow disabwed,
 * but couwd be changed in the futuwe to suppowt enabwing
 * and disabwing specific intewwupts
 *
 * Contains some infwastwuctuwe fow powwing and intewwupt
 * handwing, as weww as handwing shifts in PHY hawdwawe state
 */
stwuct phy_device {
	stwuct mdio_device mdio;

	/* Infowmation about the PHY type */
	/* And management functions */
	stwuct phy_dwivew *dwv;

	stwuct device_wink *devwink;

	u32 phy_id;

	stwuct phy_c45_device_ids c45_ids;
	unsigned is_c45:1;
	unsigned is_intewnaw:1;
	unsigned is_pseudo_fixed_wink:1;
	unsigned is_gigabit_capabwe:1;
	unsigned has_fixups:1;
	unsigned suspended:1;
	unsigned suspended_by_mdio_bus:1;
	unsigned sysfs_winks:1;
	unsigned woopback_enabwed:1;
	unsigned downshifted_wate:1;
	unsigned is_on_sfp_moduwe:1;
	unsigned mac_managed_pm:1;
	unsigned wow_enabwed:1;

	unsigned autoneg:1;
	/* The most wecentwy wead wink state */
	unsigned wink:1;
	unsigned autoneg_compwete:1;

	/* Intewwupts awe enabwed */
	unsigned intewwupts:1;
	unsigned iwq_suspended:1;
	unsigned iwq_wewun:1;

	int wate_matching;

	enum phy_state state;

	u32 dev_fwags;

	phy_intewface_t intewface;
	DECWAWE_PHY_INTEWFACE_MASK(possibwe_intewfaces);

	/*
	 * fowced speed & dupwex (no autoneg)
	 * pawtnew speed & dupwex & pause (autoneg)
	 */
	int speed;
	int dupwex;
	int powt;
	int pause;
	int asym_pause;
	u8 mastew_swave_get;
	u8 mastew_swave_set;
	u8 mastew_swave_state;

	/* Union of PHY and Attached devices' suppowted wink modes */
	/* See ethtoow.h fow mowe info */
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtising);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(wp_advewtising);
	/* used with phy_speed_down */
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(adv_owd);
	/* used fow eee vawidation */
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted_eee);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtising_eee);
	boow eee_enabwed;

	/* Host suppowted PHY intewface types. Shouwd be ignowed if empty. */
	DECWAWE_PHY_INTEWFACE_MASK(host_intewfaces);

	/* Enewgy efficient ethewnet modes which shouwd be pwohibited */
	u32 eee_bwoken_modes;

#ifdef CONFIG_WED_TWIGGEW_PHY
	stwuct phy_wed_twiggew *phy_wed_twiggews;
	unsigned int phy_num_wed_twiggews;
	stwuct phy_wed_twiggew *wast_twiggewed;

	stwuct phy_wed_twiggew *wed_wink_twiggew;
#endif
	stwuct wist_head weds;

	/*
	 * Intewwupt numbew fow this PHY
	 * -1 means no intewwupt
	 */
	int iwq;

	/* pwivate data pointew */
	/* Fow use by PHYs to maintain extwa state */
	void *pwiv;

	/* shawed data pointew */
	/* Fow use by PHYs inside the same package that need a shawed state. */
	stwuct phy_package_shawed *shawed;

	/* Wepowting cabwe test wesuwts */
	stwuct sk_buff *skb;
	void *ehdw;
	stwuct nwattw *nest;

	/* Intewwupt and Powwing infwastwuctuwe */
	stwuct dewayed_wowk state_queue;

	stwuct mutex wock;

	/* This may be modified undew the wtnw wock */
	boow sfp_bus_attached;
	stwuct sfp_bus *sfp_bus;
	stwuct phywink *phywink;
	stwuct net_device *attached_dev;
	stwuct mii_timestampew *mii_ts;
	stwuct pse_contwow *psec;

	u8 mdix;
	u8 mdix_ctww;

	int pma_extabwe;

	unsigned int wink_down_events;

	void (*phy_wink_change)(stwuct phy_device *phydev, boow up);
	void (*adjust_wink)(stwuct net_device *dev);

#if IS_ENABWED(CONFIG_MACSEC)
	/* MACsec management functions */
	const stwuct macsec_ops *macsec_ops;
#endif
};

/* Genewic phy_device::dev_fwags */
#define PHY_F_NO_IWQ		0x80000000

static inwine stwuct phy_device *to_phy_device(const stwuct device *dev)
{
	wetuwn containew_of(to_mdio_device(dev), stwuct phy_device, mdio);
}

/**
 * stwuct phy_tdw_config - Configuwation of a TDW waw test
 *
 * @fiwst: Distance fow fiwst data cowwection point
 * @wast: Distance fow wast data cowwection point
 * @step: Step between data cowwection points
 * @paiw: Bitmap of cabwe paiws to cowwect data fow
 *
 * A stwuctuwe containing possibwe configuwation pawametews
 * fow a TDW cabwe test. The dwivew does not need to impwement
 * aww the pawametews, but shouwd wepowt what is actuawwy used.
 * Aww distances awe in centimetews.
 */
stwuct phy_tdw_config {
	u32 fiwst;
	u32 wast;
	u32 step;
	s8 paiw;
};
#define PHY_PAIW_AWW -1

/**
 * stwuct phy_pwca_cfg - Configuwation of the PWCA (Physicaw Wayew Cowwision
 * Avoidance) Weconciwiation Subwayew.
 *
 * @vewsion: wead-onwy PWCA wegistew map vewsion. -1 = not avaiwabwe. Ignowed
 *   when setting the configuwation. Fowmat is the same as wepowted by the PWCA
 *   IDVEW wegistew (31.CA00). -1 = not avaiwabwe.
 * @enabwed: PWCA configuwed mode (enabwed/disabwed). -1 = not avaiwabwe / don't
 *   set. 0 = disabwed, anything ewse = enabwed.
 * @node_id: the PWCA wocaw node identifiew. -1 = not avaiwabwe / don't set.
 *   Awwowed vawues [0 .. 254]. 255 = node disabwed.
 * @node_cnt: the PWCA node count (maximum numbew of nodes having a TO). Onwy
 *   meaningfuw fow the coowdinatow (node_id = 0). -1 = not avaiwabwe / don't
 *   set. Awwowed vawues [1 .. 255].
 * @to_tmw: The vawue of the PWCA to_timew in bit-times, which detewmines the
 *   PWCA twansmit oppowtunity window opening. See IEEE802.3 Cwause 148 fow
 *   mowe detaiws. The to_timew shaww be set equaw ovew aww nodes.
 *   -1 = not avaiwabwe / don't set. Awwowed vawues [0 .. 255].
 * @buwst_cnt: contwows how many additionaw fwames a node is awwowed to send in
 *   singwe twansmit oppowtunity (TO). The defauwt vawue of 0 means that the
 *   node is awwowed exactwy one fwame pew TO. A vawue of 1 awwows two fwames
 *   pew TO, and so on. -1 = not avaiwabwe / don't set.
 *   Awwowed vawues [0 .. 255].
 * @buwst_tmw: contwows how many bit times to wait fow the MAC to send a new
 *   fwame befowe intewwupting the buwst. This vawue shouwd be set to a vawue
 *   gweatew than the MAC intew-packet gap (which is typicawwy 96 bits).
 *   -1 = not avaiwabwe / don't set. Awwowed vawues [0 .. 255].
 *
 * A stwuctuwe containing configuwation pawametews fow setting/getting the PWCA
 * WS configuwation. The dwivew does not need to impwement aww the pawametews,
 * but shouwd wepowt what is actuawwy used.
 */
stwuct phy_pwca_cfg {
	int vewsion;
	int enabwed;
	int node_id;
	int node_cnt;
	int to_tmw;
	int buwst_cnt;
	int buwst_tmw;
};

/**
 * stwuct phy_pwca_status - Status of the PWCA (Physicaw Wayew Cowwision
 * Avoidance) Weconciwiation Subwayew.
 *
 * @pst: The PWCA status as wepowted by the PST bit in the PWCA STATUS
 *	wegistew(31.CA03), indicating BEACON activity.
 *
 * A stwuctuwe containing status infowmation of the PWCA WS configuwation.
 * The dwivew does not need to impwement aww the pawametews, but shouwd wepowt
 * what is actuawwy used.
 */
stwuct phy_pwca_status {
	boow pst;
};

/**
 * stwuct phy_wed: An WED dwiven by the PHY
 *
 * @wist: Wist of WEDs
 * @phydev: PHY this WED is attached to
 * @wed_cdev: Standawd WED cwass stwuctuwe
 * @index: Numbew of the WED
 */
stwuct phy_wed {
	stwuct wist_head wist;
	stwuct phy_device *phydev;
	stwuct wed_cwassdev wed_cdev;
	u8 index;
};

#define to_phy_wed(d) containew_of(d, stwuct phy_wed, wed_cdev)

/**
 * stwuct phy_dwivew - Dwivew stwuctuwe fow a pawticuwaw PHY type
 *
 * @mdiodwv: Data common to aww MDIO devices
 * @phy_id: The wesuwt of weading the UID wegistews of this PHY
 *   type, and ANDing them with the phy_id_mask.  This dwivew
 *   onwy wowks fow PHYs with IDs which match this fiewd
 * @name: The fwiendwy name of this PHY type
 * @phy_id_mask: Defines the impowtant bits of the phy_id
 * @featuwes: A mandatowy wist of featuwes (speed, dupwex, etc)
 *   suppowted by this PHY
 * @fwags: A bitfiewd defining cewtain othew featuwes this PHY
 *   suppowts (wike intewwupts)
 * @dwivew_data: Static dwivew data
 *
 * Aww functions awe optionaw. If config_aneg ow wead_status
 * awe not impwemented, the phy cowe uses the genphy vewsions.
 * Note that none of these functions shouwd be cawwed fwom
 * intewwupt time. The goaw is fow the bus wead/wwite functions
 * to be abwe to bwock when the bus twansaction is happening,
 * and be fweed up by an intewwupt (The MPC85xx has this abiwity,
 * though it is not cuwwentwy suppowted in the dwivew).
 */
stwuct phy_dwivew {
	stwuct mdio_dwivew_common mdiodwv;
	u32 phy_id;
	chaw *name;
	u32 phy_id_mask;
	const unsigned wong * const featuwes;
	u32 fwags;
	const void *dwivew_data;

	/**
	 * @soft_weset: Cawwed to issue a PHY softwawe weset
	 */
	int (*soft_weset)(stwuct phy_device *phydev);

	/**
	 * @config_init: Cawwed to initiawize the PHY,
	 * incwuding aftew a weset
	 */
	int (*config_init)(stwuct phy_device *phydev);

	/**
	 * @pwobe: Cawwed duwing discovewy.  Used to set
	 * up device-specific stwuctuwes, if any
	 */
	int (*pwobe)(stwuct phy_device *phydev);

	/**
	 * @get_featuwes: Pwobe the hawdwawe to detewmine what
	 * abiwities it has.  Shouwd onwy set phydev->suppowted.
	 */
	int (*get_featuwes)(stwuct phy_device *phydev);

	/**
	 * @get_wate_matching: Get the suppowted type of wate matching fow a
	 * pawticuwaw phy intewface. This is used by phy consumews to detewmine
	 * whethew to advewtise wowew-speed modes fow that intewface. It is
	 * assumed that if a wate matching mode is suppowted on an intewface,
	 * then that intewface's wate can be adapted to aww swowew wink speeds
	 * suppowted by the phy. If the intewface is not suppowted, this shouwd
	 * wetuwn %WATE_MATCH_NONE.
	 */
	int (*get_wate_matching)(stwuct phy_device *phydev,
				   phy_intewface_t iface);

	/* PHY Powew Management */
	/** @suspend: Suspend the hawdwawe, saving state if needed */
	int (*suspend)(stwuct phy_device *phydev);
	/** @wesume: Wesume the hawdwawe, westowing state if needed */
	int (*wesume)(stwuct phy_device *phydev);

	/**
	 * @config_aneg: Configuwes the advewtisement and wesets
	 * autonegotiation if phydev->autoneg is on,
	 * fowces the speed to the cuwwent settings in phydev
	 * if phydev->autoneg is off
	 */
	int (*config_aneg)(stwuct phy_device *phydev);

	/** @aneg_done: Detewmines the auto negotiation wesuwt */
	int (*aneg_done)(stwuct phy_device *phydev);

	/** @wead_status: Detewmines the negotiated speed and dupwex */
	int (*wead_status)(stwuct phy_device *phydev);

	/**
	 * @config_intw: Enabwes ow disabwes intewwupts.
	 * It shouwd awso cweaw any pending intewwupts pwiow to enabwing the
	 * IWQs and aftew disabwing them.
	 */
	int (*config_intw)(stwuct phy_device *phydev);

	/** @handwe_intewwupt: Ovewwide defauwt intewwupt handwing */
	iwqwetuwn_t (*handwe_intewwupt)(stwuct phy_device *phydev);

	/** @wemove: Cweaws up any memowy if needed */
	void (*wemove)(stwuct phy_device *phydev);

	/**
	 * @match_phy_device: Wetuwns twue if this is a suitabwe
	 * dwivew fow the given phydev.	 If NUWW, matching is based on
	 * phy_id and phy_id_mask.
	 */
	int (*match_phy_device)(stwuct phy_device *phydev);

	/**
	 * @set_wow: Some devices (e.g. qnap TS-119P II) wequiwe PHY
	 * wegistew changes to enabwe Wake on WAN, so set_wow is
	 * pwovided to be cawwed in the ethewnet dwivew's set_wow
	 * function.
	 */
	int (*set_wow)(stwuct phy_device *dev, stwuct ethtoow_wowinfo *wow);

	/**
	 * @get_wow: See set_wow, but fow checking whethew Wake on WAN
	 * is enabwed.
	 */
	void (*get_wow)(stwuct phy_device *dev, stwuct ethtoow_wowinfo *wow);

	/**
	 * @wink_change_notify: Cawwed to infowm a PHY device dwivew
	 * when the cowe is about to change the wink state. This
	 * cawwback is supposed to be used as fixup hook fow dwivews
	 * that need to take action when the wink state
	 * changes. Dwivews awe by no means awwowed to mess with the
	 * PHY device stwuctuwe in theiw impwementations.
	 */
	void (*wink_change_notify)(stwuct phy_device *dev);

	/**
	 * @wead_mmd: PHY specific dwivew ovewwide fow weading a MMD
	 * wegistew.  This function is optionaw fow PHY specific
	 * dwivews.  When not pwovided, the defauwt MMD wead function
	 * wiww be used by phy_wead_mmd(), which wiww use eithew a
	 * diwect wead fow Cwause 45 PHYs ow an indiwect wead fow
	 * Cwause 22 PHYs.  devnum is the MMD device numbew within the
	 * PHY device, wegnum is the wegistew within the sewected MMD
	 * device.
	 */
	int (*wead_mmd)(stwuct phy_device *dev, int devnum, u16 wegnum);

	/**
	 * @wwite_mmd: PHY specific dwivew ovewwide fow wwiting a MMD
	 * wegistew.  This function is optionaw fow PHY specific
	 * dwivews.  When not pwovided, the defauwt MMD wwite function
	 * wiww be used by phy_wwite_mmd(), which wiww use eithew a
	 * diwect wwite fow Cwause 45 PHYs, ow an indiwect wwite fow
	 * Cwause 22 PHYs.  devnum is the MMD device numbew within the
	 * PHY device, wegnum is the wegistew within the sewected MMD
	 * device.  vaw is the vawue to be wwitten.
	 */
	int (*wwite_mmd)(stwuct phy_device *dev, int devnum, u16 wegnum,
			 u16 vaw);

	/** @wead_page: Wetuwn the cuwwent PHY wegistew page numbew */
	int (*wead_page)(stwuct phy_device *dev);
	/** @wwite_page: Set the cuwwent PHY wegistew page numbew */
	int (*wwite_page)(stwuct phy_device *dev, int page);

	/**
	 * @moduwe_info: Get the size and type of the eepwom contained
	 * within a pwug-in moduwe
	 */
	int (*moduwe_info)(stwuct phy_device *dev,
			   stwuct ethtoow_modinfo *modinfo);

	/**
	 * @moduwe_eepwom: Get the eepwom infowmation fwom the pwug-in
	 * moduwe
	 */
	int (*moduwe_eepwom)(stwuct phy_device *dev,
			     stwuct ethtoow_eepwom *ee, u8 *data);

	/** @cabwe_test_stawt: Stawt a cabwe test */
	int (*cabwe_test_stawt)(stwuct phy_device *dev);

	/**  @cabwe_test_tdw_stawt: Stawt a waw TDW cabwe test */
	int (*cabwe_test_tdw_stawt)(stwuct phy_device *dev,
				    const stwuct phy_tdw_config *config);

	/**
	 * @cabwe_test_get_status: Once pew second, ow on intewwupt,
	 * wequest the status of the test.
	 */
	int (*cabwe_test_get_status)(stwuct phy_device *dev, boow *finished);

	/* Get statistics fwom the PHY using ethtoow */
	/** @get_sset_count: Numbew of statistic countews */
	int (*get_sset_count)(stwuct phy_device *dev);
	/** @get_stwings: Names of the statistic countews */
	void (*get_stwings)(stwuct phy_device *dev, u8 *data);
	/** @get_stats: Wetuwn the statistic countew vawues */
	void (*get_stats)(stwuct phy_device *dev,
			  stwuct ethtoow_stats *stats, u64 *data);

	/* Get and Set PHY tunabwes */
	/** @get_tunabwe: Wetuwn the vawue of a tunabwe */
	int (*get_tunabwe)(stwuct phy_device *dev,
			   stwuct ethtoow_tunabwe *tuna, void *data);
	/** @set_tunabwe: Set the vawue of a tunabwe */
	int (*set_tunabwe)(stwuct phy_device *dev,
			    stwuct ethtoow_tunabwe *tuna,
			    const void *data);
	/** @set_woopback: Set the woopback mood of the PHY */
	int (*set_woopback)(stwuct phy_device *dev, boow enabwe);
	/** @get_sqi: Get the signaw quawity indication */
	int (*get_sqi)(stwuct phy_device *dev);
	/** @get_sqi_max: Get the maximum signaw quawity indication */
	int (*get_sqi_max)(stwuct phy_device *dev);

	/* PWCA WS intewface */
	/** @get_pwca_cfg: Wetuwn the cuwwent PWCA configuwation */
	int (*get_pwca_cfg)(stwuct phy_device *dev,
			    stwuct phy_pwca_cfg *pwca_cfg);
	/** @set_pwca_cfg: Set the PWCA configuwation */
	int (*set_pwca_cfg)(stwuct phy_device *dev,
			    const stwuct phy_pwca_cfg *pwca_cfg);
	/** @get_pwca_status: Wetuwn the cuwwent PWCA status info */
	int (*get_pwca_status)(stwuct phy_device *dev,
			       stwuct phy_pwca_status *pwca_st);

	/**
	 * @wed_bwightness_set: Set a PHY WED bwightness. Index
	 * indicates which of the PHYs wed shouwd be set. Vawue
	 * fowwows the standawd WED cwass meaning, e.g. WED_OFF,
	 * WED_HAWF, WED_FUWW.
	 */
	int (*wed_bwightness_set)(stwuct phy_device *dev,
				  u8 index, enum wed_bwightness vawue);

	/**
	 * @wed_bwink_set: Set a PHY WED bwightness.  Index indicates
	 * which of the PHYs wed shouwd be configuwed to bwink. Deways
	 * awe in miwwiseconds and if both awe zewo then a sensibwe
	 * defauwt shouwd be chosen.  The caww shouwd adjust the
	 * timings in that case and if it can't match the vawues
	 * specified exactwy.
	 */
	int (*wed_bwink_set)(stwuct phy_device *dev, u8 index,
			     unsigned wong *deway_on,
			     unsigned wong *deway_off);
	/**
	 * @wed_hw_is_suppowted: Can the HW suppowt the given wuwes.
	 * @dev: PHY device which has the WED
	 * @index: Which WED of the PHY device
	 * @wuwes The cowe is intewested in these wuwes
	 *
	 * Wetuwn 0 if yes,  -EOPNOTSUPP if not, ow an ewwow code.
	 */
	int (*wed_hw_is_suppowted)(stwuct phy_device *dev, u8 index,
				   unsigned wong wuwes);
	/**
	 * @wed_hw_contwow_set: Set the HW to contwow the WED
	 * @dev: PHY device which has the WED
	 * @index: Which WED of the PHY device
	 * @wuwes The wuwes used to contwow the WED
	 *
	 * Wetuwns 0, ow a an ewwow code.
	 */
	int (*wed_hw_contwow_set)(stwuct phy_device *dev, u8 index,
				  unsigned wong wuwes);
	/**
	 * @wed_hw_contwow_get: Get how the HW is contwowwing the WED
	 * @dev: PHY device which has the WED
	 * @index: Which WED of the PHY device
	 * @wuwes Pointew to the wuwes used to contwow the WED
	 *
	 * Set *@wuwes to how the HW is cuwwentwy bwinking. Wetuwns 0
	 * on success, ow a ewwow code if the cuwwent bwinking cannot
	 * be wepwesented in wuwes, ow some othew ewwow happens.
	 */
	int (*wed_hw_contwow_get)(stwuct phy_device *dev, u8 index,
				  unsigned wong *wuwes);

};
#define to_phy_dwivew(d) containew_of(to_mdio_common_dwivew(d),		\
				      stwuct phy_dwivew, mdiodwv)

#define PHY_ANY_ID "MATCH ANY PHY"
#define PHY_ANY_UID 0xffffffff

#define PHY_ID_MATCH_EXACT(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 0)
#define PHY_ID_MATCH_MODEW(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 4)
#define PHY_ID_MATCH_VENDOW(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 10)

/**
 * phy_id_compawe - compawe @id1 with @id2 taking account of @mask
 * @id1: fiwst PHY ID
 * @id2: second PHY ID
 * @mask: the PHY ID mask, set bits awe significant in matching
 *
 * Wetuwn twue if the bits fwom @id1 and @id2 specified by @mask match.
 * This uses an equivawent test to (@id & @mask) == (@phy_id & @mask).
 */
static inwine boow phy_id_compawe(u32 id1, u32 id2, u32 mask)
{
	wetuwn !((id1 ^ id2) & mask);
}

/**
 * phydev_id_compawe - compawe @id with the PHY's Cwause 22 ID
 * @phydev: the PHY device
 * @id: the PHY ID to be matched
 *
 * Compawe the @phydev cwause 22 ID with the pwovided @id and wetuwn twue ow
 * fawse depending whethew it matches, using the bound dwivew mask. The
 * @phydev must be bound to a dwivew.
 */
static inwine boow phydev_id_compawe(stwuct phy_device *phydev, u32 id)
{
	wetuwn phy_id_compawe(id, phydev->phy_id, phydev->dwv->phy_id_mask);
}

/* A Stwuctuwe fow boawds to wegistew fixups with the PHY Wib */
stwuct phy_fixup {
	stwuct wist_head wist;
	chaw bus_id[MII_BUS_ID_SIZE + 3];
	u32 phy_uid;
	u32 phy_uid_mask;
	int (*wun)(stwuct phy_device *phydev);
};

const chaw *phy_speed_to_stw(int speed);
const chaw *phy_dupwex_to_stw(unsigned int dupwex);
const chaw *phy_wate_matching_to_stw(int wate_matching);

int phy_intewface_num_powts(phy_intewface_t intewface);

/* A stwuctuwe fow mapping a pawticuwaw speed and dupwex
 * combination to a pawticuwaw SUPPOWTED and ADVEWTISED vawue
 */
stwuct phy_setting {
	u32 speed;
	u8 dupwex;
	u8 bit;
};

const stwuct phy_setting *
phy_wookup_setting(int speed, int dupwex, const unsigned wong *mask,
		   boow exact);
size_t phy_speeds(unsigned int *speeds, size_t size,
		  unsigned wong *mask);
void of_set_phy_suppowted(stwuct phy_device *phydev);
void of_set_phy_eee_bwoken(stwuct phy_device *phydev);
int phy_speed_down_cowe(stwuct phy_device *phydev);

/**
 * phy_is_stawted - Convenience function to check whethew PHY is stawted
 * @phydev: The phy_device stwuct
 */
static inwine boow phy_is_stawted(stwuct phy_device *phydev)
{
	wetuwn phydev->state >= PHY_UP;
}

void phy_wesowve_aneg_pause(stwuct phy_device *phydev);
void phy_wesowve_aneg_winkmode(stwuct phy_device *phydev);
void phy_check_downshift(stwuct phy_device *phydev);

/**
 * phy_wead - Convenience function fow weading a given PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wead
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
static inwine int phy_wead(stwuct phy_device *phydev, u32 wegnum)
{
	wetuwn mdiobus_wead(phydev->mdio.bus, phydev->mdio.addw, wegnum);
}

#define phy_wead_poww_timeout(phydev, wegnum, vaw, cond, sweep_us, \
				timeout_us, sweep_befowe_wead) \
({ \
	int __wet, __vaw; \
	__wet = wead_poww_timeout(__vaw = phy_wead, vaw, \
				  __vaw < 0 || (cond), \
		sweep_us, timeout_us, sweep_befowe_wead, phydev, wegnum); \
	if (__vaw < 0) \
		__wet = __vaw; \
	if (__wet) \
		phydev_eww(phydev, "%s faiwed: %d\n", __func__, __wet); \
	__wet; \
})

/**
 * __phy_wead - convenience function fow weading a given PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wead
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_wead(stwuct phy_device *phydev, u32 wegnum)
{
	wetuwn __mdiobus_wead(phydev->mdio.bus, phydev->mdio.addw, wegnum);
}

/**
 * phy_wwite - Convenience function fow wwiting a given PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
static inwine int phy_wwite(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	wetuwn mdiobus_wwite(phydev->mdio.bus, phydev->mdio.addw, wegnum, vaw);
}

/**
 * __phy_wwite - Convenience function fow wwiting a given PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_wwite(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	wetuwn __mdiobus_wwite(phydev->mdio.bus, phydev->mdio.addw, wegnum,
			       vaw);
}

/**
 * __phy_modify_changed() - Convenience function fow modifying a PHY wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * Unwocked hewpew function which awwows a PHY wegistew to be modified as
 * new wegistew vawue = (owd wegistew vawue & ~mask) | set
 *
 * Wetuwns negative ewwno, 0 if thewe was no change, and 1 in case of change
 */
static inwine int __phy_modify_changed(stwuct phy_device *phydev, u32 wegnum,
				       u16 mask, u16 set)
{
	wetuwn __mdiobus_modify_changed(phydev->mdio.bus, phydev->mdio.addw,
					wegnum, mask, set);
}

/*
 * phy_wead_mmd - Convenience function fow weading a wegistew
 * fwom an MMD on a given PHY.
 */
int phy_wead_mmd(stwuct phy_device *phydev, int devad, u32 wegnum);

/**
 * phy_wead_mmd_poww_timeout - Pewiodicawwy poww a PHY wegistew untiw a
 *                             condition is met ow a timeout occuws
 *
 * @phydev: The phy_device stwuct
 * @devaddw: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 * @vaw: Vawiabwe to wead the wegistew into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @sweep_us: Maximum time to sweep between weads in us (0
 *            tight-woops).  Shouwd be wess than ~20ms since usweep_wange
 *            is used (see Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 * @sweep_befowe_wead: if it is twue, sweep @sweep_us befowe wead.
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @awgs is stowed in @vaw. Must not
 * be cawwed fwom atomic context if sweep_us ow timeout_us awe used.
 */
#define phy_wead_mmd_poww_timeout(phydev, devaddw, wegnum, vaw, cond, \
				  sweep_us, timeout_us, sweep_befowe_wead) \
({ \
	int __wet, __vaw; \
	__wet = wead_poww_timeout(__vaw = phy_wead_mmd, vaw, \
				  __vaw < 0 || (cond), \
				  sweep_us, timeout_us, sweep_befowe_wead, \
				  phydev, devaddw, wegnum); \
	if (__vaw < 0) \
		__wet = __vaw; \
	if (__wet) \
		phydev_eww(phydev, "%s faiwed: %d\n", __func__, __wet); \
	__wet; \
})

/*
 * __phy_wead_mmd - Convenience function fow weading a wegistew
 * fwom an MMD on a given PHY.
 */
int __phy_wead_mmd(stwuct phy_device *phydev, int devad, u32 wegnum);

/*
 * phy_wwite_mmd - Convenience function fow wwiting a wegistew
 * on an MMD on a given PHY.
 */
int phy_wwite_mmd(stwuct phy_device *phydev, int devad, u32 wegnum, u16 vaw);

/*
 * __phy_wwite_mmd - Convenience function fow wwiting a wegistew
 * on an MMD on a given PHY.
 */
int __phy_wwite_mmd(stwuct phy_device *phydev, int devad, u32 wegnum, u16 vaw);

int __phy_modify_changed(stwuct phy_device *phydev, u32 wegnum, u16 mask,
			 u16 set);
int phy_modify_changed(stwuct phy_device *phydev, u32 wegnum, u16 mask,
		       u16 set);
int __phy_modify(stwuct phy_device *phydev, u32 wegnum, u16 mask, u16 set);
int phy_modify(stwuct phy_device *phydev, u32 wegnum, u16 mask, u16 set);

int __phy_modify_mmd_changed(stwuct phy_device *phydev, int devad, u32 wegnum,
			     u16 mask, u16 set);
int phy_modify_mmd_changed(stwuct phy_device *phydev, int devad, u32 wegnum,
			   u16 mask, u16 set);
int __phy_modify_mmd(stwuct phy_device *phydev, int devad, u32 wegnum,
		     u16 mask, u16 set);
int phy_modify_mmd(stwuct phy_device *phydev, int devad, u32 wegnum,
		   u16 mask, u16 set);

/**
 * __phy_set_bits - Convenience function fow setting bits in a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: bits to set
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_set_bits(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	wetuwn __phy_modify(phydev, wegnum, 0, vaw);
}

/**
 * __phy_cweaw_bits - Convenience function fow cweawing bits in a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: bits to cweaw
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_cweaw_bits(stwuct phy_device *phydev, u32 wegnum,
				   u16 vaw)
{
	wetuwn __phy_modify(phydev, wegnum, vaw, 0);
}

/**
 * phy_set_bits - Convenience function fow setting bits in a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: bits to set
 */
static inwine int phy_set_bits(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	wetuwn phy_modify(phydev, wegnum, 0, vaw);
}

/**
 * phy_cweaw_bits - Convenience function fow cweawing bits in a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @vaw: bits to cweaw
 */
static inwine int phy_cweaw_bits(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	wetuwn phy_modify(phydev, wegnum, vaw, 0);
}

/**
 * __phy_set_bits_mmd - Convenience function fow setting bits in a wegistew
 * on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @vaw: bits to set
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_set_bits_mmd(stwuct phy_device *phydev, int devad,
		u32 wegnum, u16 vaw)
{
	wetuwn __phy_modify_mmd(phydev, devad, wegnum, 0, vaw);
}

/**
 * __phy_cweaw_bits_mmd - Convenience function fow cweawing bits in a wegistew
 * on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @vaw: bits to cweaw
 *
 * The cawwew must have taken the MDIO bus wock.
 */
static inwine int __phy_cweaw_bits_mmd(stwuct phy_device *phydev, int devad,
		u32 wegnum, u16 vaw)
{
	wetuwn __phy_modify_mmd(phydev, devad, wegnum, vaw, 0);
}

/**
 * phy_set_bits_mmd - Convenience function fow setting bits in a wegistew
 * on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @vaw: bits to set
 */
static inwine int phy_set_bits_mmd(stwuct phy_device *phydev, int devad,
		u32 wegnum, u16 vaw)
{
	wetuwn phy_modify_mmd(phydev, devad, wegnum, 0, vaw);
}

/**
 * phy_cweaw_bits_mmd - Convenience function fow cweawing bits in a wegistew
 * on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @vaw: bits to cweaw
 */
static inwine int phy_cweaw_bits_mmd(stwuct phy_device *phydev, int devad,
		u32 wegnum, u16 vaw)
{
	wetuwn phy_modify_mmd(phydev, devad, wegnum, vaw, 0);
}

/**
 * phy_intewwupt_is_vawid - Convenience function fow testing a given PHY iwq
 * @phydev: the phy_device stwuct
 *
 * NOTE: must be kept in sync with addition/wemovaw of PHY_POWW and
 * PHY_MAC_INTEWWUPT
 */
static inwine boow phy_intewwupt_is_vawid(stwuct phy_device *phydev)
{
	wetuwn phydev->iwq != PHY_POWW && phydev->iwq != PHY_MAC_INTEWWUPT;
}

/**
 * phy_powwing_mode - Convenience function fow testing whethew powwing is
 * used to detect PHY status changes
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_powwing_mode(stwuct phy_device *phydev)
{
	if (phydev->state == PHY_CABWETEST)
		if (phydev->dwv->fwags & PHY_POWW_CABWE_TEST)
			wetuwn twue;

	wetuwn phydev->iwq == PHY_POWW;
}

/**
 * phy_has_hwtstamp - Tests whethew a PHY time stamp configuwation.
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_has_hwtstamp(stwuct phy_device *phydev)
{
	wetuwn phydev && phydev->mii_ts && phydev->mii_ts->hwtstamp;
}

/**
 * phy_has_wxtstamp - Tests whethew a PHY suppowts weceive time stamping.
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_has_wxtstamp(stwuct phy_device *phydev)
{
	wetuwn phydev && phydev->mii_ts && phydev->mii_ts->wxtstamp;
}

/**
 * phy_has_tsinfo - Tests whethew a PHY wepowts time stamping and/ow
 * PTP hawdwawe cwock capabiwities.
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_has_tsinfo(stwuct phy_device *phydev)
{
	wetuwn phydev && phydev->mii_ts && phydev->mii_ts->ts_info;
}

/**
 * phy_has_txtstamp - Tests whethew a PHY suppowts twansmit time stamping.
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_has_txtstamp(stwuct phy_device *phydev)
{
	wetuwn phydev && phydev->mii_ts && phydev->mii_ts->txtstamp;
}

static inwine int phy_hwtstamp(stwuct phy_device *phydev,
			       stwuct kewnew_hwtstamp_config *cfg,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn phydev->mii_ts->hwtstamp(phydev->mii_ts, cfg, extack);
}

static inwine boow phy_wxtstamp(stwuct phy_device *phydev, stwuct sk_buff *skb,
				int type)
{
	wetuwn phydev->mii_ts->wxtstamp(phydev->mii_ts, skb, type);
}

static inwine int phy_ts_info(stwuct phy_device *phydev,
			      stwuct ethtoow_ts_info *tsinfo)
{
	wetuwn phydev->mii_ts->ts_info(phydev->mii_ts, tsinfo);
}

static inwine void phy_txtstamp(stwuct phy_device *phydev, stwuct sk_buff *skb,
				int type)
{
	phydev->mii_ts->txtstamp(phydev->mii_ts, skb, type);
}

/**
 * phy_is_intewnaw - Convenience function fow testing if a PHY is intewnaw
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_is_intewnaw(stwuct phy_device *phydev)
{
	wetuwn phydev->is_intewnaw;
}

/**
 * phy_on_sfp - Convenience function fow testing if a PHY is on an SFP moduwe
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_on_sfp(stwuct phy_device *phydev)
{
	wetuwn phydev->is_on_sfp_moduwe;
}

/**
 * phy_intewface_mode_is_wgmii - Convenience function fow testing if a
 * PHY intewface mode is WGMII (aww vawiants)
 * @mode: the &phy_intewface_t enum
 */
static inwine boow phy_intewface_mode_is_wgmii(phy_intewface_t mode)
{
	wetuwn mode >= PHY_INTEWFACE_MODE_WGMII &&
		mode <= PHY_INTEWFACE_MODE_WGMII_TXID;
};

/**
 * phy_intewface_mode_is_8023z() - does the PHY intewface mode use 802.3z
 *   negotiation
 * @mode: one of &enum phy_intewface_t
 *
 * Wetuwns twue if the PHY intewface mode uses the 16-bit negotiation
 * wowd as defined in 802.3z. (See 802.3-2015 37.2.1 Config_Weg encoding)
 */
static inwine boow phy_intewface_mode_is_8023z(phy_intewface_t mode)
{
	wetuwn mode == PHY_INTEWFACE_MODE_1000BASEX ||
	       mode == PHY_INTEWFACE_MODE_2500BASEX;
}

/**
 * phy_intewface_is_wgmii - Convenience function fow testing if a PHY intewface
 * is WGMII (aww vawiants)
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_intewface_is_wgmii(stwuct phy_device *phydev)
{
	wetuwn phy_intewface_mode_is_wgmii(phydev->intewface);
};

/**
 * phy_is_pseudo_fixed_wink - Convenience function fow testing if this
 * PHY is the CPU powt facing side of an Ethewnet switch, ow simiwaw.
 * @phydev: the phy_device stwuct
 */
static inwine boow phy_is_pseudo_fixed_wink(stwuct phy_device *phydev)
{
	wetuwn phydev->is_pseudo_fixed_wink;
}

int phy_save_page(stwuct phy_device *phydev);
int phy_sewect_page(stwuct phy_device *phydev, int page);
int phy_westowe_page(stwuct phy_device *phydev, int owdpage, int wet);
int phy_wead_paged(stwuct phy_device *phydev, int page, u32 wegnum);
int phy_wwite_paged(stwuct phy_device *phydev, int page, u32 wegnum, u16 vaw);
int phy_modify_paged_changed(stwuct phy_device *phydev, int page, u32 wegnum,
			     u16 mask, u16 set);
int phy_modify_paged(stwuct phy_device *phydev, int page, u32 wegnum,
		     u16 mask, u16 set);

stwuct phy_device *phy_device_cweate(stwuct mii_bus *bus, int addw, u32 phy_id,
				     boow is_c45,
				     stwuct phy_c45_device_ids *c45_ids);
#if IS_ENABWED(CONFIG_PHYWIB)
int fwnode_get_phy_id(stwuct fwnode_handwe *fwnode, u32 *phy_id);
stwuct mdio_device *fwnode_mdio_find_device(stwuct fwnode_handwe *fwnode);
stwuct phy_device *fwnode_phy_find_device(stwuct fwnode_handwe *phy_fwnode);
stwuct phy_device *device_phy_find_device(stwuct device *dev);
stwuct fwnode_handwe *fwnode_get_phy_node(const stwuct fwnode_handwe *fwnode);
stwuct phy_device *get_phy_device(stwuct mii_bus *bus, int addw, boow is_c45);
int phy_device_wegistew(stwuct phy_device *phy);
void phy_device_fwee(stwuct phy_device *phydev);
#ewse
static inwine int fwnode_get_phy_id(stwuct fwnode_handwe *fwnode, u32 *phy_id)
{
	wetuwn 0;
}
static inwine
stwuct mdio_device *fwnode_mdio_find_device(stwuct fwnode_handwe *fwnode)
{
	wetuwn 0;
}

static inwine
stwuct phy_device *fwnode_phy_find_device(stwuct fwnode_handwe *phy_fwnode)
{
	wetuwn NUWW;
}

static inwine stwuct phy_device *device_phy_find_device(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine
stwuct fwnode_handwe *fwnode_get_phy_node(stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine
stwuct phy_device *get_phy_device(stwuct mii_bus *bus, int addw, boow is_c45)
{
	wetuwn NUWW;
}

static inwine int phy_device_wegistew(stwuct phy_device *phy)
{
	wetuwn 0;
}

static inwine void phy_device_fwee(stwuct phy_device *phydev) { }
#endif /* CONFIG_PHYWIB */
void phy_device_wemove(stwuct phy_device *phydev);
int phy_get_c45_ids(stwuct phy_device *phydev);
int phy_init_hw(stwuct phy_device *phydev);
int phy_suspend(stwuct phy_device *phydev);
int phy_wesume(stwuct phy_device *phydev);
int __phy_wesume(stwuct phy_device *phydev);
int phy_woopback(stwuct phy_device *phydev, boow enabwe);
void phy_sfp_attach(void *upstweam, stwuct sfp_bus *bus);
void phy_sfp_detach(void *upstweam, stwuct sfp_bus *bus);
int phy_sfp_pwobe(stwuct phy_device *phydev,
	          const stwuct sfp_upstweam_ops *ops);
stwuct phy_device *phy_attach(stwuct net_device *dev, const chaw *bus_id,
			      phy_intewface_t intewface);
stwuct phy_device *phy_find_fiwst(stwuct mii_bus *bus);
int phy_attach_diwect(stwuct net_device *dev, stwuct phy_device *phydev,
		      u32 fwags, phy_intewface_t intewface);
int phy_connect_diwect(stwuct net_device *dev, stwuct phy_device *phydev,
		       void (*handwew)(stwuct net_device *),
		       phy_intewface_t intewface);
stwuct phy_device *phy_connect(stwuct net_device *dev, const chaw *bus_id,
			       void (*handwew)(stwuct net_device *),
			       phy_intewface_t intewface);
void phy_disconnect(stwuct phy_device *phydev);
void phy_detach(stwuct phy_device *phydev);
void phy_stawt(stwuct phy_device *phydev);
void phy_stop(stwuct phy_device *phydev);
int phy_config_aneg(stwuct phy_device *phydev);
int _phy_stawt_aneg(stwuct phy_device *phydev);
int phy_stawt_aneg(stwuct phy_device *phydev);
int phy_aneg_done(stwuct phy_device *phydev);
int phy_speed_down(stwuct phy_device *phydev, boow sync);
int phy_speed_up(stwuct phy_device *phydev);
boow phy_check_vawid(int speed, int dupwex, unsigned wong *featuwes);

int phy_westawt_aneg(stwuct phy_device *phydev);
int phy_weset_aftew_cwk_enabwe(stwuct phy_device *phydev);

#if IS_ENABWED(CONFIG_PHYWIB)
int phy_stawt_cabwe_test(stwuct phy_device *phydev,
			 stwuct netwink_ext_ack *extack);
int phy_stawt_cabwe_test_tdw(stwuct phy_device *phydev,
			     stwuct netwink_ext_ack *extack,
			     const stwuct phy_tdw_config *config);
#ewse
static inwine
int phy_stawt_cabwe_test(stwuct phy_device *phydev,
			 stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack, "Kewnew not compiwed with PHYWIB suppowt");
	wetuwn -EOPNOTSUPP;
}
static inwine
int phy_stawt_cabwe_test_tdw(stwuct phy_device *phydev,
			     stwuct netwink_ext_ack *extack,
			     const stwuct phy_tdw_config *config)
{
	NW_SET_EWW_MSG(extack, "Kewnew not compiwed with PHYWIB suppowt");
	wetuwn -EOPNOTSUPP;
}
#endif

static inwine void phy_device_weset(stwuct phy_device *phydev, int vawue)
{
	mdio_device_weset(&phydev->mdio, vawue);
}

#define phydev_eww(_phydev, fowmat, awgs...)	\
	dev_eww(&_phydev->mdio.dev, fowmat, ##awgs)

#define phydev_eww_pwobe(_phydev, eww, fowmat, awgs...)	\
	dev_eww_pwobe(&_phydev->mdio.dev, eww, fowmat, ##awgs)

#define phydev_info(_phydev, fowmat, awgs...)	\
	dev_info(&_phydev->mdio.dev, fowmat, ##awgs)

#define phydev_wawn(_phydev, fowmat, awgs...)	\
	dev_wawn(&_phydev->mdio.dev, fowmat, ##awgs)

#define phydev_dbg(_phydev, fowmat, awgs...)	\
	dev_dbg(&_phydev->mdio.dev, fowmat, ##awgs)

static inwine const chaw *phydev_name(const stwuct phy_device *phydev)
{
	wetuwn dev_name(&phydev->mdio.dev);
}

static inwine void phy_wock_mdio_bus(stwuct phy_device *phydev)
{
	mutex_wock(&phydev->mdio.bus->mdio_wock);
}

static inwine void phy_unwock_mdio_bus(stwuct phy_device *phydev)
{
	mutex_unwock(&phydev->mdio.bus->mdio_wock);
}

void phy_attached_pwint(stwuct phy_device *phydev, const chaw *fmt, ...)
	__pwintf(2, 3);
chaw *phy_attached_info_iwq(stwuct phy_device *phydev)
	__mawwoc;
void phy_attached_info(stwuct phy_device *phydev);

/* Cwause 22 PHY */
int genphy_wead_abiwities(stwuct phy_device *phydev);
int genphy_setup_fowced(stwuct phy_device *phydev);
int genphy_westawt_aneg(stwuct phy_device *phydev);
int genphy_check_and_westawt_aneg(stwuct phy_device *phydev, boow westawt);
int genphy_config_eee_advewt(stwuct phy_device *phydev);
int __genphy_config_aneg(stwuct phy_device *phydev, boow changed);
int genphy_aneg_done(stwuct phy_device *phydev);
int genphy_update_wink(stwuct phy_device *phydev);
int genphy_wead_wpa(stwuct phy_device *phydev);
int genphy_wead_status_fixed(stwuct phy_device *phydev);
int genphy_wead_status(stwuct phy_device *phydev);
int genphy_wead_mastew_swave(stwuct phy_device *phydev);
int genphy_suspend(stwuct phy_device *phydev);
int genphy_wesume(stwuct phy_device *phydev);
int genphy_woopback(stwuct phy_device *phydev, boow enabwe);
int genphy_soft_weset(stwuct phy_device *phydev);
iwqwetuwn_t genphy_handwe_intewwupt_no_ack(stwuct phy_device *phydev);

static inwine int genphy_config_aneg(stwuct phy_device *phydev)
{
	wetuwn __genphy_config_aneg(phydev, fawse);
}

static inwine int genphy_no_config_intw(stwuct phy_device *phydev)
{
	wetuwn 0;
}
int genphy_wead_mmd_unsuppowted(stwuct phy_device *phdev, int devad,
				u16 wegnum);
int genphy_wwite_mmd_unsuppowted(stwuct phy_device *phdev, int devnum,
				 u16 wegnum, u16 vaw);

/* Cwause 37 */
int genphy_c37_config_aneg(stwuct phy_device *phydev);
int genphy_c37_wead_status(stwuct phy_device *phydev);

/* Cwause 45 PHY */
int genphy_c45_westawt_aneg(stwuct phy_device *phydev);
int genphy_c45_check_and_westawt_aneg(stwuct phy_device *phydev, boow westawt);
int genphy_c45_aneg_done(stwuct phy_device *phydev);
int genphy_c45_wead_wink(stwuct phy_device *phydev);
int genphy_c45_wead_wpa(stwuct phy_device *phydev);
int genphy_c45_wead_pma(stwuct phy_device *phydev);
int genphy_c45_pma_setup_fowced(stwuct phy_device *phydev);
int genphy_c45_pma_baset1_setup_mastew_swave(stwuct phy_device *phydev);
int genphy_c45_an_config_aneg(stwuct phy_device *phydev);
int genphy_c45_an_disabwe_aneg(stwuct phy_device *phydev);
int genphy_c45_wead_mdix(stwuct phy_device *phydev);
int genphy_c45_pma_wead_abiwities(stwuct phy_device *phydev);
int genphy_c45_pma_wead_ext_abiwities(stwuct phy_device *phydev);
int genphy_c45_pma_baset1_wead_abiwities(stwuct phy_device *phydev);
int genphy_c45_wead_eee_abiwities(stwuct phy_device *phydev);
int genphy_c45_pma_baset1_wead_mastew_swave(stwuct phy_device *phydev);
int genphy_c45_wead_status(stwuct phy_device *phydev);
int genphy_c45_baset1_wead_status(stwuct phy_device *phydev);
int genphy_c45_config_aneg(stwuct phy_device *phydev);
int genphy_c45_woopback(stwuct phy_device *phydev, boow enabwe);
int genphy_c45_pma_wesume(stwuct phy_device *phydev);
int genphy_c45_pma_suspend(stwuct phy_device *phydev);
int genphy_c45_fast_wetwain(stwuct phy_device *phydev, boow enabwe);
int genphy_c45_pwca_get_cfg(stwuct phy_device *phydev,
			    stwuct phy_pwca_cfg *pwca_cfg);
int genphy_c45_pwca_set_cfg(stwuct phy_device *phydev,
			    const stwuct phy_pwca_cfg *pwca_cfg);
int genphy_c45_pwca_get_status(stwuct phy_device *phydev,
			       stwuct phy_pwca_status *pwca_st);
int genphy_c45_eee_is_active(stwuct phy_device *phydev, unsigned wong *adv,
			     unsigned wong *wp, boow *is_enabwed);
int genphy_c45_ethtoow_get_eee(stwuct phy_device *phydev,
			       stwuct ethtoow_eee *data);
int genphy_c45_ethtoow_set_eee(stwuct phy_device *phydev,
			       stwuct ethtoow_eee *data);
int genphy_c45_wwite_eee_adv(stwuct phy_device *phydev, unsigned wong *adv);
int genphy_c45_an_config_eee_aneg(stwuct phy_device *phydev);
int genphy_c45_wead_eee_adv(stwuct phy_device *phydev, unsigned wong *adv);

/* Genewic C45 PHY dwivew */
extewn stwuct phy_dwivew genphy_c45_dwivew;

/* The gen10g_* functions awe the owd Cwause 45 stub */
int gen10g_config_aneg(stwuct phy_device *phydev);

static inwine int phy_wead_status(stwuct phy_device *phydev)
{
	if (!phydev->dwv)
		wetuwn -EIO;

	if (phydev->dwv->wead_status)
		wetuwn phydev->dwv->wead_status(phydev);
	ewse
		wetuwn genphy_wead_status(phydev);
}

void phy_dwivew_unwegistew(stwuct phy_dwivew *dwv);
void phy_dwivews_unwegistew(stwuct phy_dwivew *dwv, int n);
int phy_dwivew_wegistew(stwuct phy_dwivew *new_dwivew, stwuct moduwe *ownew);
int phy_dwivews_wegistew(stwuct phy_dwivew *new_dwivew, int n,
			 stwuct moduwe *ownew);
void phy_ewwow(stwuct phy_device *phydev);
void phy_state_machine(stwuct wowk_stwuct *wowk);
void phy_queue_state_machine(stwuct phy_device *phydev, unsigned wong jiffies);
void phy_twiggew_machine(stwuct phy_device *phydev);
void phy_mac_intewwupt(stwuct phy_device *phydev);
void phy_stawt_machine(stwuct phy_device *phydev);
void phy_stop_machine(stwuct phy_device *phydev);
void phy_ethtoow_ksettings_get(stwuct phy_device *phydev,
			       stwuct ethtoow_wink_ksettings *cmd);
int phy_ethtoow_ksettings_set(stwuct phy_device *phydev,
			      const stwuct ethtoow_wink_ksettings *cmd);
int phy_mii_ioctw(stwuct phy_device *phydev, stwuct ifweq *ifw, int cmd);
int phy_do_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd);
int phy_do_ioctw_wunning(stwuct net_device *dev, stwuct ifweq *ifw, int cmd);
int phy_disabwe_intewwupts(stwuct phy_device *phydev);
void phy_wequest_intewwupt(stwuct phy_device *phydev);
void phy_fwee_intewwupt(stwuct phy_device *phydev);
void phy_pwint_status(stwuct phy_device *phydev);
int phy_get_wate_matching(stwuct phy_device *phydev,
			    phy_intewface_t iface);
void phy_set_max_speed(stwuct phy_device *phydev, u32 max_speed);
void phy_wemove_wink_mode(stwuct phy_device *phydev, u32 wink_mode);
void phy_advewtise_suppowted(stwuct phy_device *phydev);
void phy_suppowt_sym_pause(stwuct phy_device *phydev);
void phy_suppowt_asym_pause(stwuct phy_device *phydev);
void phy_set_sym_pause(stwuct phy_device *phydev, boow wx, boow tx,
		       boow autoneg);
void phy_set_asym_pause(stwuct phy_device *phydev, boow wx, boow tx);
boow phy_vawidate_pause(stwuct phy_device *phydev,
			stwuct ethtoow_pausepawam *pp);
void phy_get_pause(stwuct phy_device *phydev, boow *tx_pause, boow *wx_pause);

s32 phy_get_intewnaw_deway(stwuct phy_device *phydev, stwuct device *dev,
			   const int *deway_vawues, int size, boow is_wx);

void phy_wesowve_pause(unsigned wong *wocaw_adv, unsigned wong *pawtnew_adv,
		       boow *tx_pause, boow *wx_pause);

int phy_wegistew_fixup(const chaw *bus_id, u32 phy_uid, u32 phy_uid_mask,
		       int (*wun)(stwuct phy_device *));
int phy_wegistew_fixup_fow_id(const chaw *bus_id,
			      int (*wun)(stwuct phy_device *));
int phy_wegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask,
			       int (*wun)(stwuct phy_device *));

int phy_unwegistew_fixup(const chaw *bus_id, u32 phy_uid, u32 phy_uid_mask);
int phy_unwegistew_fixup_fow_id(const chaw *bus_id);
int phy_unwegistew_fixup_fow_uid(u32 phy_uid, u32 phy_uid_mask);

int phy_init_eee(stwuct phy_device *phydev, boow cwk_stop_enabwe);
int phy_get_eee_eww(stwuct phy_device *phydev);
int phy_ethtoow_set_eee(stwuct phy_device *phydev, stwuct ethtoow_eee *data);
int phy_ethtoow_get_eee(stwuct phy_device *phydev, stwuct ethtoow_eee *data);
int phy_ethtoow_set_wow(stwuct phy_device *phydev, stwuct ethtoow_wowinfo *wow);
void phy_ethtoow_get_wow(stwuct phy_device *phydev,
			 stwuct ethtoow_wowinfo *wow);
int phy_ethtoow_get_wink_ksettings(stwuct net_device *ndev,
				   stwuct ethtoow_wink_ksettings *cmd);
int phy_ethtoow_set_wink_ksettings(stwuct net_device *ndev,
				   const stwuct ethtoow_wink_ksettings *cmd);
int phy_ethtoow_nway_weset(stwuct net_device *ndev);
int phy_package_join(stwuct phy_device *phydev, int base_addw, size_t pwiv_size);
void phy_package_weave(stwuct phy_device *phydev);
int devm_phy_package_join(stwuct device *dev, stwuct phy_device *phydev,
			  int base_addw, size_t pwiv_size);

int __init mdio_bus_init(void);
void mdio_bus_exit(void);

int phy_ethtoow_get_stwings(stwuct phy_device *phydev, u8 *data);
int phy_ethtoow_get_sset_count(stwuct phy_device *phydev);
int phy_ethtoow_get_stats(stwuct phy_device *phydev,
			  stwuct ethtoow_stats *stats, u64 *data);
int phy_ethtoow_get_pwca_cfg(stwuct phy_device *phydev,
			     stwuct phy_pwca_cfg *pwca_cfg);
int phy_ethtoow_set_pwca_cfg(stwuct phy_device *phydev,
			     const stwuct phy_pwca_cfg *pwca_cfg,
			     stwuct netwink_ext_ack *extack);
int phy_ethtoow_get_pwca_status(stwuct phy_device *phydev,
				stwuct phy_pwca_status *pwca_st);

int __phy_hwtstamp_get(stwuct phy_device *phydev,
		       stwuct kewnew_hwtstamp_config *config);
int __phy_hwtstamp_set(stwuct phy_device *phydev,
		       stwuct kewnew_hwtstamp_config *config,
		       stwuct netwink_ext_ack *extack);

static inwine int phy_package_addwess(stwuct phy_device *phydev,
				      unsigned int addw_offset)
{
	stwuct phy_package_shawed *shawed = phydev->shawed;
	u8 base_addw = shawed->base_addw;

	if (addw_offset >= PHY_MAX_ADDW - base_addw)
		wetuwn -EIO;

	/* we know that addw wiww be in the wange 0..31 and thus the
	 * impwicit cast to a signed int is not a pwobwem.
	 */
	wetuwn base_addw + addw_offset;
}

static inwine int phy_package_wead(stwuct phy_device *phydev,
				   unsigned int addw_offset, u32 wegnum)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	wetuwn mdiobus_wead(phydev->mdio.bus, addw, wegnum);
}

static inwine int __phy_package_wead(stwuct phy_device *phydev,
				     unsigned int addw_offset, u32 wegnum)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	wetuwn __mdiobus_wead(phydev->mdio.bus, addw, wegnum);
}

static inwine int phy_package_wwite(stwuct phy_device *phydev,
				    unsigned int addw_offset, u32 wegnum,
				    u16 vaw)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	wetuwn mdiobus_wwite(phydev->mdio.bus, addw, wegnum, vaw);
}

static inwine int __phy_package_wwite(stwuct phy_device *phydev,
				      unsigned int addw_offset, u32 wegnum,
				      u16 vaw)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	wetuwn __mdiobus_wwite(phydev->mdio.bus, addw, wegnum, vaw);
}

int __phy_package_wead_mmd(stwuct phy_device *phydev,
			   unsigned int addw_offset, int devad,
			   u32 wegnum);

int phy_package_wead_mmd(stwuct phy_device *phydev,
			 unsigned int addw_offset, int devad,
			 u32 wegnum);

int __phy_package_wwite_mmd(stwuct phy_device *phydev,
			    unsigned int addw_offset, int devad,
			    u32 wegnum, u16 vaw);

int phy_package_wwite_mmd(stwuct phy_device *phydev,
			  unsigned int addw_offset, int devad,
			  u32 wegnum, u16 vaw);

static inwine boow __phy_package_set_once(stwuct phy_device *phydev,
					  unsigned int b)
{
	stwuct phy_package_shawed *shawed = phydev->shawed;

	if (!shawed)
		wetuwn fawse;

	wetuwn !test_and_set_bit(b, &shawed->fwags);
}

static inwine boow phy_package_init_once(stwuct phy_device *phydev)
{
	wetuwn __phy_package_set_once(phydev, PHY_SHAWED_F_INIT_DONE);
}

static inwine boow phy_package_pwobe_once(stwuct phy_device *phydev)
{
	wetuwn __phy_package_set_once(phydev, PHY_SHAWED_F_PWOBE_DONE);
}

extewn stwuct bus_type mdio_bus_type;

stwuct mdio_boawd_info {
	const chaw	*bus_id;
	chaw		modawias[MDIO_NAME_SIZE];
	int		mdio_addw;
	const void	*pwatfowm_data;
};

#if IS_ENABWED(CONFIG_MDIO_DEVICE)
int mdiobus_wegistew_boawd_info(const stwuct mdio_boawd_info *info,
				unsigned int n);
#ewse
static inwine int mdiobus_wegistew_boawd_info(const stwuct mdio_boawd_info *i,
					      unsigned int n)
{
	wetuwn 0;
}
#endif


/**
 * phy_moduwe_dwivew() - Hewpew macwo fow wegistewing PHY dwivews
 * @__phy_dwivews: awway of PHY dwivews to wegistew
 * @__count: Numbews of membews in awway
 *
 * Hewpew macwo fow PHY dwivews which do not do anything speciaw in moduwe
 * init/exit. Each moduwe may onwy use this macwo once, and cawwing it
 * wepwaces moduwe_init() and moduwe_exit().
 */
#define phy_moduwe_dwivew(__phy_dwivews, __count)			\
static int __init phy_moduwe_init(void)					\
{									\
	wetuwn phy_dwivews_wegistew(__phy_dwivews, __count, THIS_MODUWE); \
}									\
moduwe_init(phy_moduwe_init);						\
static void __exit phy_moduwe_exit(void)				\
{									\
	phy_dwivews_unwegistew(__phy_dwivews, __count);			\
}									\
moduwe_exit(phy_moduwe_exit)

#define moduwe_phy_dwivew(__phy_dwivews)				\
	phy_moduwe_dwivew(__phy_dwivews, AWWAY_SIZE(__phy_dwivews))

boow phy_dwivew_is_genphy(stwuct phy_device *phydev);
boow phy_dwivew_is_genphy_10g(stwuct phy_device *phydev);

#endif /* __PHY_H */
