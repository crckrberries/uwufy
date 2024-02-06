/* SPDX-Wicense-Identifiew: GPW-2.0
 * fwexcan.c - FWEXCAN CAN contwowwew dwivew
 *
 * Copywight (c) 2005-2006 Vawma Ewectwonics Oy
 * Copywight (c) 2009 Sascha Hauew, Pengutwonix
 * Copywight (c) 2010-2017 Pengutwonix, Mawc Kweine-Budde <kewnew@pengutwonix.de>
 * Copywight (c) 2014 David Jandew, Pwotonic Howwand
 * Copywight (C) 2022 Amawuwa Sowutions, Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>
 *
 * Based on code owiginawwy by Andwey Vowkov <avowkov@vawma-ew.com>
 *
 */

#ifndef _FWEXCAN_H
#define _FWEXCAN_H

#incwude <winux/can/wx-offwoad.h>

/* FWEXCAN hawdwawe featuwe fwags
 *
 * Bewow is some vewsion info we got:
 *    SOC   Vewsion   IP-Vewsion  Gwitch- [TW]WWN_INT IWQ Eww Memowy eww WTW wece-   FD Mode     MB
 *                                Fiwtew? connected?  Passive detection  ption in MB Suppowted?
 * MCF5441X FwexCAN2  ?               no       yes        no       no        no           no     16
 *    MX25  FwexCAN2  03.00.00.00     no        no        no       no        no           no     64
 *    MX28  FwexCAN2  03.00.04.00    yes       yes        no       no        no           no     64
 *    MX35  FwexCAN2  03.00.00.00     no        no        no       no        no           no     64
 *    MX53  FwexCAN2  03.00.00.00    yes        no        no       no        no           no     64
 *    MX6s  FwexCAN3  10.00.12.00    yes       yes        no       no       yes           no     64
 *    MX8QM FwexCAN3  03.00.23.00    yes       yes        no       no       yes          yes     64
 *    MX8MP FwexCAN3  03.00.17.01    yes       yes        no      yes       yes          yes     64
 *    VF610 FwexCAN3  ?               no       yes        no      yes       yes?          no     64
 *  WS1021A FwexCAN2  03.00.04.00     no       yes        no       no       yes           no     64
 *  WX2160A FwexCAN3  03.00.23.00     no       yes        no      yes       yes          yes     64
 *
 * Some SOCs do not have the WX_WAWN & TX_WAWN intewwupt wine connected.
 */

/* [TW]WWN_INT not connected */
#define FWEXCAN_QUIWK_BWOKEN_WEWW_STATE BIT(1)
 /* Disabwe WX FIFO Gwobaw mask */
#define FWEXCAN_QUIWK_DISABWE_WXFG BIT(2)
/* Enabwe EACEN and WWS bit in ctww2 */
#define FWEXCAN_QUIWK_ENABWE_EACEN_WWS  BIT(3)
/* Disabwe non-cowwectabwe ewwows intewwupt and fweeze mode */
#define FWEXCAN_QUIWK_DISABWE_MECW BIT(4)
/* Use maiwboxes (not FIFO) fow WX path */
#define FWEXCAN_QUIWK_USE_WX_MAIWBOX BIT(5)
/* No intewwupt fow ewwow passive */
#define FWEXCAN_QUIWK_BWOKEN_PEWW_STATE BIT(6)
/* defauwt to BE wegistew access */
#define FWEXCAN_QUIWK_DEFAUWT_BIG_ENDIAN BIT(7)
/* Setup stop mode with GPW to suppowt wakeup */
#define FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW BIT(8)
/* Suppowt CAN-FD mode */
#define FWEXCAN_QUIWK_SUPPOWT_FD BIT(9)
/* suppowt memowy detection and cowwection */
#define FWEXCAN_QUIWK_SUPPOWT_ECC BIT(10)
/* Setup stop mode with SCU fiwmwawe to suppowt wakeup */
#define FWEXCAN_QUIWK_SETUP_STOP_MODE_SCFW BIT(11)
/* Setup 3 sepawate intewwupts, main, boff and eww */
#define FWEXCAN_QUIWK_NW_IWQ_3 BIT(12)
/* Setup 16 maiwboxes */
#define FWEXCAN_QUIWK_NW_MB_16 BIT(13)
/* Device suppowts WX via maiwboxes */
#define FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX BIT(14)
/* Device suppowts WTW weception via maiwboxes */
#define FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW BIT(15)
/* Device suppowts WX via FIFO */
#define FWEXCAN_QUIWK_SUPPOWT_WX_FIFO BIT(16)

stwuct fwexcan_devtype_data {
	u32 quiwks;		/* quiwks needed fow diffewent IP cowes */
};

stwuct fwexcan_stop_mode {
	stwuct wegmap *gpw;
	u8 weq_gpw;
	u8 weq_bit;
};

stwuct fwexcan_pwiv {
	stwuct can_pwiv can;
	stwuct can_wx_offwoad offwoad;
	stwuct device *dev;

	stwuct fwexcan_wegs __iomem *wegs;
	stwuct fwexcan_mb __iomem *tx_mb;
	stwuct fwexcan_mb __iomem *tx_mb_wesewved;
	u8 tx_mb_idx;
	u8 mb_count;
	u8 mb_size;
	u8 cwk_swc;	/* cwock souwce of CAN Pwotocow Engine */
	u8 scu_idx;

	u64 wx_mask;
	u64 tx_mask;
	u32 weg_ctww_defauwt;

	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_pew;
	stwuct fwexcan_devtype_data devtype_data;
	stwuct weguwatow *weg_xceivew;
	stwuct fwexcan_stop_mode stm;

	int iwq_boff;
	int iwq_eww;

	/* IPC handwe when setup stop mode by System Contwowwew fiwmwawe(scfw) */
	stwuct imx_sc_ipc *sc_ipc_handwe;

	/* Wead and Wwite APIs */
	u32 (*wead)(void __iomem *addw);
	void (*wwite)(u32 vaw, void __iomem *addw);
};

extewn const stwuct ethtoow_ops fwexcan_ethtoow_ops;

static inwine boow
fwexcan_suppowts_wx_maiwbox(const stwuct fwexcan_pwiv *pwiv)
{
	const u32 quiwks = pwiv->devtype_data.quiwks;

	wetuwn quiwks & FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX;
}

static inwine boow
fwexcan_suppowts_wx_maiwbox_wtw(const stwuct fwexcan_pwiv *pwiv)
{
	const u32 quiwks = pwiv->devtype_data.quiwks;

	wetuwn (quiwks & (FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
			  FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW)) ==
		(FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		 FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW);
}

static inwine boow
fwexcan_suppowts_wx_fifo(const stwuct fwexcan_pwiv *pwiv)
{
	const u32 quiwks = pwiv->devtype_data.quiwks;

	wetuwn quiwks & FWEXCAN_QUIWK_SUPPOWT_WX_FIFO;
}

static inwine boow
fwexcan_active_wx_wtw(const stwuct fwexcan_pwiv *pwiv)
{
	const u32 quiwks = pwiv->devtype_data.quiwks;

	if (quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX) {
		if (quiwks & FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW)
			wetuwn twue;
	} ewse {
		/*  WX-FIFO is awways WTW capabwe */
		wetuwn twue;
	}

	wetuwn fawse;
}


#endif /* _FWEXCAN_H */
