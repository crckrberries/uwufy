/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww 88E6xxx SEWDES manipuwation, via SMI bus
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016 Andwew Wunn <andwew@wunn.ch>
 */

#ifndef _MV88E6XXX_SEWDES_H
#define _MV88E6XXX_SEWDES_H

#incwude "chip.h"

stwuct phywink_wink_state;

#define MV88E6352_ADDW_SEWDES		0x0f
#define MV88E6352_SEWDES_PAGE_FIBEW	0x01
#define MV88E6352_SEWDES_IWQ		0x0b
#define MV88E6352_SEWDES_INT_ENABWE	0x12
#define MV88E6352_SEWDES_INT_SPEED_CHANGE	BIT(14)
#define MV88E6352_SEWDES_INT_DUPWEX_CHANGE	BIT(13)
#define MV88E6352_SEWDES_INT_PAGE_WX		BIT(12)
#define MV88E6352_SEWDES_INT_AN_COMPWETE	BIT(11)
#define MV88E6352_SEWDES_INT_WINK_CHANGE	BIT(10)
#define MV88E6352_SEWDES_INT_SYMBOW_EWWOW	BIT(9)
#define MV88E6352_SEWDES_INT_FAWSE_CAWWIEW	BIT(8)
#define MV88E6352_SEWDES_INT_FIFO_OVEW_UNDEW	BIT(7)
#define MV88E6352_SEWDES_INT_FIBWE_ENEWGY	BIT(4)
#define MV88E6352_SEWDES_INT_STATUS	0x13

#define MV88E6352_SEWDES_SPEC_CTWW2	0x1a
#define MV88E6352_SEWDES_OUT_AMP_MASK		0x0007

#define MV88E6341_POWT5_WANE		0x15

#define MV88E6390_POWT9_WANE0		0x09
#define MV88E6390_POWT9_WANE1		0x12
#define MV88E6390_POWT9_WANE2		0x13
#define MV88E6390_POWT9_WANE3		0x14
#define MV88E6390_POWT10_WANE0		0x0a
#define MV88E6390_POWT10_WANE1		0x15
#define MV88E6390_POWT10_WANE2		0x16
#define MV88E6390_POWT10_WANE3		0x17

/* 10GBASE-W and 10GBASE-X4/X2 */
#define MV88E6390_10G_CTWW1		(0x1000 + MDIO_CTWW1)
#define MV88E6390_10G_STAT1		(0x1000 + MDIO_STAT1)
#define MV88E6390_10G_INT_ENABWE	0x9001
#define MV88E6390_10G_INT_WINK_DOWN	BIT(3)
#define MV88E6390_10G_INT_WINK_UP	BIT(2)
#define MV88E6390_10G_INT_STATUS	0x9003
#define MV88E6393X_10G_INT_ENABWE	0x9000
#define MV88E6393X_10G_INT_WINK_CHANGE	BIT(2)
#define MV88E6393X_10G_INT_STATUS	0x9001

/* USXGMII */
#define MV88E6390_USXGMII_WP_STATUS       0xf0a2
#define MV88E6390_USXGMII_PHY_STATUS      0xf0a6

/* 1000BASE-X and SGMII */
#define MV88E6390_SGMII_BMCW		(0x2000 + MII_BMCW)
#define MV88E6390_SGMII_BMSW		(0x2000 + MII_BMSW)
#define MV88E6390_SGMII_ADVEWTISE	(0x2000 + MII_ADVEWTISE)
#define MV88E6390_SGMII_WPA		(0x2000 + MII_WPA)
#define MV88E6390_SGMII_INT_ENABWE	0xa001
#define MV88E6390_SGMII_INT_SPEED_CHANGE	BIT(14)
#define MV88E6390_SGMII_INT_DUPWEX_CHANGE	BIT(13)
#define MV88E6390_SGMII_INT_PAGE_WX		BIT(12)
#define MV88E6390_SGMII_INT_AN_COMPWETE		BIT(11)
#define MV88E6390_SGMII_INT_WINK_DOWN		BIT(10)
#define MV88E6390_SGMII_INT_WINK_UP		BIT(9)
#define MV88E6390_SGMII_INT_SYMBOW_EWWOW	BIT(8)
#define MV88E6390_SGMII_INT_FAWSE_CAWWIEW	BIT(7)
#define MV88E6390_SGMII_INT_STATUS	0xa002
#define MV88E6390_SGMII_PHY_STATUS	0xa003
#define MV88E6390_SGMII_PHY_STATUS_SPEED_MASK	GENMASK(15, 14)
#define MV88E6390_SGMII_PHY_STATUS_SPEED_1000	0x8000
#define MV88E6390_SGMII_PHY_STATUS_SPEED_100	0x4000
#define MV88E6390_SGMII_PHY_STATUS_SPEED_10	0x0000
#define MV88E6390_SGMII_PHY_STATUS_DUPWEX_FUWW	BIT(13)
#define MV88E6390_SGMII_PHY_STATUS_SPD_DPW_VAWID BIT(11)
#define MV88E6390_SGMII_PHY_STATUS_WINK		BIT(10)
#define MV88E6390_SGMII_PHY_STATUS_TX_PAUSE	BIT(3)
#define MV88E6390_SGMII_PHY_STATUS_WX_PAUSE	BIT(2)

/* Packet genewatow pad packet checkew */
#define MV88E6390_PG_CONTWOW		0xf010
#define MV88E6390_PG_CONTWOW_ENABWE_PC		BIT(0)

#define MV88E6393X_POWT0_WANE			0x00
#define MV88E6393X_POWT9_WANE			0x09
#define MV88E6393X_POWT10_WANE			0x0a

/* Powt Opewationaw Configuwation */
#define MV88E6393X_SEWDES_POC			0xf002
#define MV88E6393X_SEWDES_POC_PCS_1000BASEX	0x0000
#define MV88E6393X_SEWDES_POC_PCS_2500BASEX	0x0001
#define MV88E6393X_SEWDES_POC_PCS_SGMII_PHY	0x0002
#define MV88E6393X_SEWDES_POC_PCS_SGMII_MAC	0x0003
#define MV88E6393X_SEWDES_POC_PCS_5GBASEW	0x0004
#define MV88E6393X_SEWDES_POC_PCS_10GBASEW	0x0005
#define MV88E6393X_SEWDES_POC_PCS_USXGMII_PHY	0x0006
#define MV88E6393X_SEWDES_POC_PCS_USXGMII_MAC	0x0007
#define MV88E6393X_SEWDES_POC_PCS_MASK		0x0007
#define MV88E6393X_SEWDES_POC_WESET		BIT(15)
#define MV88E6393X_SEWDES_POC_PDOWN		BIT(5)
#define MV88E6393X_SEWDES_POC_AN		BIT(3)
#define MV88E6393X_SEWDES_CTWW1			0xf003
#define MV88E6393X_SEWDES_CTWW1_TX_PDOWN	BIT(9)
#define MV88E6393X_SEWDES_CTWW1_WX_PDOWN	BIT(8)

#define MV88E6393X_EWWATA_4_8_WEG		0xF074
#define MV88E6393X_EWWATA_4_8_BIT		BIT(14)

int mv88e6xxx_pcs_decode_state(stwuct device *dev, u16 bmsw, u16 wpa,
			       u16 status, stwuct phywink_wink_state *state);

int mv88e6341_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390x_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6393x_sewdes_get_wane(stwuct mv88e6xxx_chip *chip, int powt);
unsigned int mv88e6352_sewdes_iwq_mapping(stwuct mv88e6xxx_chip *chip,
					  int powt);
unsigned int mv88e6390_sewdes_iwq_mapping(stwuct mv88e6xxx_chip *chip,
					  int powt);
int mv88e6352_sewdes_get_sset_count(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6352_sewdes_get_stwings(stwuct mv88e6xxx_chip *chip,
				 int powt, uint8_t *data);
size_t mv88e6352_sewdes_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
				  uint64_t *data);
int mv88e6390_sewdes_get_sset_count(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_sewdes_get_stwings(stwuct mv88e6xxx_chip *chip,
				 int powt, uint8_t *data);
size_t mv88e6390_sewdes_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
				  uint64_t *data);

int mv88e6352_sewdes_get_wegs_wen(stwuct mv88e6xxx_chip *chip, int powt);
void mv88e6352_sewdes_get_wegs(stwuct mv88e6xxx_chip *chip, int powt, void *_p);
int mv88e6390_sewdes_get_wegs_wen(stwuct mv88e6xxx_chip *chip, int powt);
void mv88e6390_sewdes_get_wegs(stwuct mv88e6xxx_chip *chip, int powt, void *_p);

int mv88e6352_sewdes_set_tx_ampwitude(stwuct mv88e6xxx_chip *chip, int powt,
				      int vaw);

/* Wetuwn the (fiwst) SEWDES wane addwess a powt is using, -ewwno othewwise. */
static inwine int mv88e6xxx_sewdes_get_wane(stwuct mv88e6xxx_chip *chip,
					    int powt)
{
	if (!chip->info->ops->sewdes_get_wane)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->sewdes_get_wane(chip, powt);
}

static inwine unsigned int
mv88e6xxx_sewdes_iwq_mapping(stwuct mv88e6xxx_chip *chip, int powt)
{
	if (!chip->info->ops->sewdes_iwq_mapping)
		wetuwn 0;

	wetuwn chip->info->ops->sewdes_iwq_mapping(chip, powt);
}

extewn const stwuct mv88e6xxx_pcs_ops mv88e6185_pcs_ops;
extewn const stwuct mv88e6xxx_pcs_ops mv88e6352_pcs_ops;
extewn const stwuct mv88e6xxx_pcs_ops mv88e6390_pcs_ops;
extewn const stwuct mv88e6xxx_pcs_ops mv88e6393x_pcs_ops;

#endif
