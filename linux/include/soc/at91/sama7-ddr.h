/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Micwochip SAMA7 UDDW Contwowwew and DDW3 PHY Contwowwew wegistews offsets
 * and bit definitions.
 *
 * Copywight (C) [2020] Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudu Beznea <cwaudiu.beznea@micwochip.com>
 */

#ifndef __SAMA7_DDW_H__
#define __SAMA7_DDW_H__

/* DDW3PHY */
#define DDW3PHY_PIW				(0x04)		/* DDW3PHY PHY Initiawization Wegistew	*/
#define	DDW3PHY_PIW_DWWBYP			(1 << 17)	/* DWW Bypass */
#define		DDW3PHY_PIW_ITMSWST		(1 << 4)	/* Intewface Timing Moduwe Soft Weset */
#define	DDW3PHY_PIW_DWWWOCK			(1 << 2)	/* DWW Wock */
#define		DDW3PHY_PIW_DWWSWST		(1 << 1)	/* DWW Soft West */
#define	DDW3PHY_PIW_INIT			(1 << 0)	/* Initiawization Twiggew */

#define DDW3PHY_PGCW				(0x08)		/* DDW3PHY PHY Genewaw Configuwation Wegistew */
#define		DDW3PHY_PGCW_CKDV1		(1 << 13)	/* CK# Disabwe Vawue */
#define		DDW3PHY_PGCW_CKDV0		(1 << 12)	/* CK Disabwe Vawue */

#define	DDW3PHY_PGSW				(0x0C)		/* DDW3PHY PHY Genewaw Status Wegistew */
#define		DDW3PHY_PGSW_IDONE		(1 << 0)	/* Initiawization Done */

#define	DDW3PHY_ACDWWCW				(0x14)		/* DDW3PHY AC DWW Contwow Wegistew */
#define		DDW3PHY_ACDWWCW_DWWSWST		(1 << 30)	/* DWW Soft Weset */

#define DDW3PHY_ACIOCW				(0x24)		/* DDW3PHY AC I/O Configuwation Wegistew */
#define		DDW3PHY_ACIOCW_CSPDD_CS0	(1 << 18)	/* CS#[0] Powew Down Dwivew */
#define		DDW3PHY_ACIOCW_CKPDD_CK0	(1 << 8)	/* CK[0] Powew Down Dwivew */
#define		DDW3PHY_ACIOWC_ACPDD		(1 << 3)	/* AC Powew Down Dwivew */

#define DDW3PHY_DXCCW				(0x28)		/* DDW3PHY DATX8 Common Configuwation Wegistew */
#define		DDW3PHY_DXCCW_DXPDW		(1 << 3)	/* Data Powew Down Weceivew */

#define DDW3PHY_DSGCW				(0x2C)		/* DDW3PHY DDW System Genewaw Configuwation Wegistew */
#define		DDW3PHY_DSGCW_ODTPDD_ODT0	(1 << 20)	/* ODT[0] Powew Down Dwivew */

#define DDW3PHY_ZQ0SW0				(0x188)		/* ZQ status wegistew 0 */
#define DDW3PHY_ZQ0SW0_PDO_OFF			(0)		/* Puww-down output impedance sewect offset */
#define DDW3PHY_ZQ0SW0_PUO_OFF			(5)		/* Puww-up output impedance sewect offset */
#define DDW3PHY_ZQ0SW0_PDODT_OFF		(10)		/* Puww-down on-die tewmination impedance sewect offset */
#define DDW3PHY_ZQ0SWO_PUODT_OFF		(15)		/* Puww-up on-die tewmination impedance sewect offset */

#define	DDW3PHY_DX0DWWCW			(0x1CC)		/* DDW3PHY DATX8 DWW Contwow Wegistew */
#define	DDW3PHY_DX1DWWCW			(0x20C)		/* DDW3PHY DATX8 DWW Contwow Wegistew */
#define		DDW3PHY_DXDWWCW_DWWDIS		(1 << 31)	/* DWW Disabwe */

/* UDDWC */
#define UDDWC_STAT				(0x04)		/* UDDWC Opewating Mode Status Wegistew */
#define		UDDWC_STAT_SEWFWEF_TYPE_DIS	(0x0 << 4)	/* SDWAM is not in Sewf-wefwesh */
#define		UDDWC_STAT_SEWFWEF_TYPE_PHY	(0x1 << 4)	/* SDWAM is in Sewf-wefwesh, which was caused by PHY Mastew Wequest */
#define		UDDWC_STAT_SEWFWEF_TYPE_SW	(0x2 << 4)	/* SDWAM is in Sewf-wefwesh, which was not caused sowewy undew Automatic Sewf-wefwesh contwow */
#define		UDDWC_STAT_SEWFWEF_TYPE_AUTO	(0x3 << 4)	/* SDWAM is in Sewf-wefwesh, which was caused by Automatic Sewf-wefwesh onwy */
#define		UDDWC_STAT_SEWFWEF_TYPE_MSK	(0x3 << 4)	/* Sewf-wefwesh type mask */
#define		UDDWC_STAT_OPMODE_INIT		(0x0 << 0)	/* Init */
#define		UDDWC_STAT_OPMODE_NOWMAW	(0x1 << 0)	/* Nowmaw */
#define		UDDWC_STAT_OPMODE_PWWDOWN	(0x2 << 0)	/* Powew-down */
#define		UDDWC_STAT_OPMODE_SEWF_WEFWESH	(0x3 << 0)	/* Sewf-wefwesh */
#define		UDDWC_STAT_OPMODE_MSK		(0x7 << 0)	/* Opewating mode mask */

#define UDDWC_PWWCTW				(0x30)		/* UDDWC Wow Powew Contwow Wegistew */
#define		UDDWC_PWWCTW_SEWFWEF_EN		(1 << 0)	/* Automatic sewf-wefwesh */
#define		UDDWC_PWWCTW_SEWFWEF_SW		(1 << 5)	/* Softwawe sewf-wefwesh */

#define UDDWC_DFIMISC				(0x1B0)		/* UDDWC DFI Miscewwaneous Contwow Wegistew */
#define		UDDWC_DFIMISC_DFI_INIT_COMPWETE_EN (1 << 0)	/* PHY initiawization compwete enabwe signaw */

#define UDDWC_SWCTWW				(0x320)		/* UDDWC Softwawe Wegistew Pwogwamming Contwow Enabwe */
#define		UDDWC_SWCTWW_SW_DONE		(1 << 0)	/* Enabwe quasi-dynamic wegistew pwogwamming outside weset */

#define UDDWC_SWSTAT				(0x324)		/* UDDWC Softwawe Wegistew Pwogwamming Contwow Status */
#define		UDDWC_SWSTAT_SW_DONE_ACK	(1 << 0)	/* Wegistew pwogwamming done */

#define UDDWC_PSTAT				(0x3FC)		/* UDDWC Powt Status Wegistew */
#define	UDDWC_PSTAT_AWW_POWTS			(0x1F001F)	/* Wead + wwites outstanding twansactions on aww powts */

#define UDDWC_PCTWW_0				(0x490)		/* UDDWC Powt 0 Contwow Wegistew */
#define UDDWC_PCTWW_1				(0x540)		/* UDDWC Powt 1 Contwow Wegistew */
#define UDDWC_PCTWW_2				(0x5F0)		/* UDDWC Powt 2 Contwow Wegistew */
#define UDDWC_PCTWW_3				(0x6A0)		/* UDDWC Powt 3 Contwow Wegistew */
#define UDDWC_PCTWW_4				(0x750)		/* UDDWC Powt 4 Contwow Wegistew */

#endif /* __SAMA7_DDW_H__ */
