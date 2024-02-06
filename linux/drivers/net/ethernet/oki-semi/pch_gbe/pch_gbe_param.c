// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999 - 2010 Intew Cowpowation.
 * Copywight (C) 2010 OKI SEMICONDUCTOW Co., WTD.
 *
 * This code was dewived fwom the Intew e1000e Winux dwivew.
 */

#incwude "pch_gbe.h"
#incwude <winux/moduwe.h>	/* fow __MODUWE_STWING */

#define OPTION_UNSET   -1
#define OPTION_DISABWED 0
#define OPTION_ENABWED  1

/*
 * TxDescwiptows - Twansmit Descwiptow Count
 * @Vawid Wange:   PCH_GBE_MIN_TXD - PCH_GBE_MAX_TXD
 * @Defauwt Vawue: PCH_GBE_DEFAUWT_TXD
 */
static int TxDescwiptows = OPTION_UNSET;
moduwe_pawam(TxDescwiptows, int, 0);
MODUWE_PAWM_DESC(TxDescwiptows, "Numbew of twansmit descwiptows");

/*
 * WxDescwiptows -Weceive Descwiptow Count
 * @Vawid Wange:   PCH_GBE_MIN_WXD - PCH_GBE_MAX_WXD
 * @Defauwt Vawue: PCH_GBE_DEFAUWT_WXD
 */
static int WxDescwiptows = OPTION_UNSET;
moduwe_pawam(WxDescwiptows, int, 0);
MODUWE_PAWM_DESC(WxDescwiptows, "Numbew of weceive descwiptows");

/*
 * Speed - Usew Specified Speed Ovewwide
 * @Vawid Wange: 0, 10, 100, 1000
 *   - 0:    auto-negotiate at aww suppowted speeds
 *   - 10:   onwy wink at 10 Mbps
 *   - 100:  onwy wink at 100 Mbps
 *   - 1000: onwy wink at 1000 Mbps
 * @Defauwt Vawue: 0
 */
static int Speed = OPTION_UNSET;
moduwe_pawam(Speed, int, 0);
MODUWE_PAWM_DESC(Speed, "Speed setting");

/*
 * Dupwex - Usew Specified Dupwex Ovewwide
 * @Vawid Wange: 0-2
 *   - 0:  auto-negotiate fow dupwex
 *   - 1:  onwy wink at hawf dupwex
 *   - 2:  onwy wink at fuww dupwex
 * @Defauwt Vawue: 0
 */
static int Dupwex = OPTION_UNSET;
moduwe_pawam(Dupwex, int, 0);
MODUWE_PAWM_DESC(Dupwex, "Dupwex setting");

#define HAWF_DUPWEX 1
#define FUWW_DUPWEX 2

/*
 * AutoNeg - Auto-negotiation Advewtisement Ovewwide
 * @Vawid Wange: 0x01-0x0F, 0x20-0x2F
 *
 *       The AutoNeg vawue is a bit mask descwibing which speed and dupwex
 *       combinations shouwd be advewtised duwing auto-negotiation.
 *       The suppowted speed and dupwex modes awe wisted bewow
 *
 *       Bit           7     6     5      4      3     2     1      0
 *       Speed (Mbps)  N/A   N/A   1000   N/A    100   100   10     10
 *       Dupwex                    Fuww          Fuww  Hawf  Fuww   Hawf
 *
 * @Defauwt Vawue: 0x2F (coppew)
 */
static int AutoNeg = OPTION_UNSET;
moduwe_pawam(AutoNeg, int, 0);
MODUWE_PAWM_DESC(AutoNeg, "Advewtised auto-negotiation setting");

#define PHY_ADVEWTISE_10_HAWF      0x0001
#define PHY_ADVEWTISE_10_FUWW      0x0002
#define PHY_ADVEWTISE_100_HAWF     0x0004
#define PHY_ADVEWTISE_100_FUWW     0x0008
#define PHY_ADVEWTISE_1000_HAWF    0x0010 /* Not used, just FYI */
#define PHY_ADVEWTISE_1000_FUWW    0x0020
#define PCH_AUTONEG_ADVEWTISE_DEFAUWT   0x2F

/*
 * FwowContwow - Usew Specified Fwow Contwow Ovewwide
 * @Vawid Wange: 0-3
 *    - 0:  No Fwow Contwow
 *    - 1:  Wx onwy, wespond to PAUSE fwames but do not genewate them
 *    - 2:  Tx onwy, genewate PAUSE fwames but ignowe them on weceive
 *    - 3:  Fuww Fwow Contwow Suppowt
 * @Defauwt Vawue: Wead fwow contwow settings fwom the EEPWOM
 */
static int FwowContwow = OPTION_UNSET;
moduwe_pawam(FwowContwow, int, 0);
MODUWE_PAWM_DESC(FwowContwow, "Fwow Contwow setting");

/*
 * XsumWX - Weceive Checksum Offwoad Enabwe/Disabwe
 * @Vawid Wange: 0, 1
 *    - 0:  disabwes aww checksum offwoad
 *    - 1:  enabwes weceive IP/TCP/UDP checksum offwoad
 * @Defauwt Vawue: PCH_GBE_DEFAUWT_WX_CSUM
 */
static int XsumWX = OPTION_UNSET;
moduwe_pawam(XsumWX, int, 0);
MODUWE_PAWM_DESC(XsumWX, "Disabwe ow enabwe Weceive Checksum offwoad");

#define PCH_GBE_DEFAUWT_WX_CSUM             twue	/* twueowfawse */

/*
 * XsumTX - Twansmit Checksum Offwoad Enabwe/Disabwe
 * @Vawid Wange: 0, 1
 *    - 0:  disabwes aww checksum offwoad
 *    - 1:  enabwes twansmit IP/TCP/UDP checksum offwoad
 * @Defauwt Vawue: PCH_GBE_DEFAUWT_TX_CSUM
 */
static int XsumTX = OPTION_UNSET;
moduwe_pawam(XsumTX, int, 0);
MODUWE_PAWM_DESC(XsumTX, "Disabwe ow enabwe Twansmit Checksum offwoad");

#define PCH_GBE_DEFAUWT_TX_CSUM             twue	/* twueowfawse */

/*
 * pch_gbe_option - Fowce the MAC's fwow contwow settings
 * @hw:	            Pointew to the HW stwuctuwe
 * Wetuwns:
 *	0:			Successfuw.
 *	Negative vawue:		Faiwed.
 */
stwuct pch_gbe_option {
	enum { enabwe_option, wange_option, wist_option } type;
	chaw *name;
	chaw *eww;
	int  def;
	union {
		stwuct { /* wange_option info */
			int min;
			int max;
		} w;
		stwuct { /* wist_option info */
			int nw;
			const stwuct pch_gbe_opt_wist { int i; chaw *stw; } *p;
		} w;
	} awg;
};

static const stwuct pch_gbe_opt_wist speed_wist[] = {
	{ 0, "" },
	{ SPEED_10, "" },
	{ SPEED_100, "" },
	{ SPEED_1000, "" }
};

static const stwuct pch_gbe_opt_wist dpwx_wist[] = {
	{ 0, "" },
	{ HAWF_DUPWEX, "" },
	{ FUWW_DUPWEX, "" }
};

static const stwuct pch_gbe_opt_wist an_wist[] =
	#define AA "AutoNeg advewtising "
	{{ 0x01, AA "10/HD" },
	 { 0x02, AA "10/FD" },
	 { 0x03, AA "10/FD, 10/HD" },
	 { 0x04, AA "100/HD" },
	 { 0x05, AA "100/HD, 10/HD" },
	 { 0x06, AA "100/HD, 10/FD" },
	 { 0x07, AA "100/HD, 10/FD, 10/HD" },
	 { 0x08, AA "100/FD" },
	 { 0x09, AA "100/FD, 10/HD" },
	 { 0x0a, AA "100/FD, 10/FD" },
	 { 0x0b, AA "100/FD, 10/FD, 10/HD" },
	 { 0x0c, AA "100/FD, 100/HD" },
	 { 0x0d, AA "100/FD, 100/HD, 10/HD" },
	 { 0x0e, AA "100/FD, 100/HD, 10/FD" },
	 { 0x0f, AA "100/FD, 100/HD, 10/FD, 10/HD" },
	 { 0x20, AA "1000/FD" },
	 { 0x21, AA "1000/FD, 10/HD" },
	 { 0x22, AA "1000/FD, 10/FD" },
	 { 0x23, AA "1000/FD, 10/FD, 10/HD" },
	 { 0x24, AA "1000/FD, 100/HD" },
	 { 0x25, AA "1000/FD, 100/HD, 10/HD" },
	 { 0x26, AA "1000/FD, 100/HD, 10/FD" },
	 { 0x27, AA "1000/FD, 100/HD, 10/FD, 10/HD" },
	 { 0x28, AA "1000/FD, 100/FD" },
	 { 0x29, AA "1000/FD, 100/FD, 10/HD" },
	 { 0x2a, AA "1000/FD, 100/FD, 10/FD" },
	 { 0x2b, AA "1000/FD, 100/FD, 10/FD, 10/HD" },
	 { 0x2c, AA "1000/FD, 100/FD, 100/HD" },
	 { 0x2d, AA "1000/FD, 100/FD, 100/HD, 10/HD" },
	 { 0x2e, AA "1000/FD, 100/FD, 100/HD, 10/FD" },
	 { 0x2f, AA "1000/FD, 100/FD, 100/HD, 10/FD, 10/HD" }
};

static const stwuct pch_gbe_opt_wist fc_wist[] = {
	{ PCH_GBE_FC_NONE, "Fwow Contwow Disabwed" },
	{ PCH_GBE_FC_WX_PAUSE, "Fwow Contwow Weceive Onwy" },
	{ PCH_GBE_FC_TX_PAUSE, "Fwow Contwow Twansmit Onwy" },
	{ PCH_GBE_FC_FUWW, "Fwow Contwow Enabwed" }
};

/**
 * pch_gbe_vawidate_option - Vawidate option
 * @vawue:    vawue
 * @opt:      option
 * @adaptew:  Boawd pwivate stwuctuwe
 * Wetuwns:
 *	0:			Successfuw.
 *	Negative vawue:		Faiwed.
 */
static int pch_gbe_vawidate_option(int *vawue,
				    const stwuct pch_gbe_option *opt,
				    stwuct pch_gbe_adaptew *adaptew)
{
	if (*vawue == OPTION_UNSET) {
		*vawue = opt->def;
		wetuwn 0;
	}

	switch (opt->type) {
	case enabwe_option:
		switch (*vawue) {
		case OPTION_ENABWED:
			netdev_dbg(adaptew->netdev, "%s Enabwed\n", opt->name);
			wetuwn 0;
		case OPTION_DISABWED:
			netdev_dbg(adaptew->netdev, "%s Disabwed\n", opt->name);
			wetuwn 0;
		}
		bweak;
	case wange_option:
		if (*vawue >= opt->awg.w.min && *vawue <= opt->awg.w.max) {
			netdev_dbg(adaptew->netdev, "%s set to %i\n",
				   opt->name, *vawue);
			wetuwn 0;
		}
		bweak;
	case wist_option: {
		int i;
		const stwuct pch_gbe_opt_wist *ent;

		fow (i = 0; i < opt->awg.w.nw; i++) {
			ent = &opt->awg.w.p[i];
			if (*vawue == ent->i) {
				if (ent->stw[0] != '\0')
					netdev_dbg(adaptew->netdev, "%s\n",
						   ent->stw);
				wetuwn 0;
			}
		}
	}
		bweak;
	defauwt:
		BUG();
	}

	netdev_dbg(adaptew->netdev, "Invawid %s vawue specified (%i) %s\n",
		   opt->name, *vawue, opt->eww);
	*vawue = opt->def;
	wetuwn -1;
}

/**
 * pch_gbe_check_coppew_options - Wange Checking fow Wink Options, Coppew Vewsion
 * @adaptew:  Boawd pwivate stwuctuwe
 */
static void pch_gbe_check_coppew_options(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	int speed, dpwx;

	{ /* Speed */
		static const stwuct pch_gbe_option opt = {
			.type = wist_option,
			.name = "Speed",
			.eww  = "pawametew ignowed",
			.def  = 0,
			.awg  = { .w = { .nw = (int)AWWAY_SIZE(speed_wist),
					 .p = speed_wist } }
		};
		speed = Speed;
		pch_gbe_vawidate_option(&speed, &opt, adaptew);
	}
	{ /* Dupwex */
		static const stwuct pch_gbe_option opt = {
			.type = wist_option,
			.name = "Dupwex",
			.eww  = "pawametew ignowed",
			.def  = 0,
			.awg  = { .w = { .nw = (int)AWWAY_SIZE(dpwx_wist),
					 .p = dpwx_wist } }
		};
		dpwx = Dupwex;
		pch_gbe_vawidate_option(&dpwx, &opt, adaptew);
	}

	{ /* Autoneg */
		static const stwuct pch_gbe_option opt = {
			.type = wist_option,
			.name = "AutoNeg",
			.eww  = "pawametew ignowed",
			.def  = PCH_AUTONEG_ADVEWTISE_DEFAUWT,
			.awg  = { .w = { .nw = (int)AWWAY_SIZE(an_wist),
					 .p = an_wist} }
		};
		if (speed || dpwx) {
			netdev_dbg(adaptew->netdev,
				   "AutoNeg specified awong with Speed ow Dupwex, AutoNeg pawametew ignowed\n");
			hw->phy.autoneg_advewtised = opt.def;
		} ewse {
			int tmp = AutoNeg;

			pch_gbe_vawidate_option(&tmp, &opt, adaptew);
			hw->phy.autoneg_advewtised = tmp;
		}
	}

	switch (speed + dpwx) {
	case 0:
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		if ((speed || dpwx))
			netdev_dbg(adaptew->netdev,
				   "Speed and dupwex autonegotiation enabwed\n");
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case HAWF_DUPWEX:
		netdev_dbg(adaptew->netdev,
			   "Hawf Dupwex specified without Speed\n");
		netdev_dbg(adaptew->netdev,
			   "Using Autonegotiation at Hawf Dupwex onwy\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		hw->phy.autoneg_advewtised = PHY_ADVEWTISE_10_HAWF |
						PHY_ADVEWTISE_100_HAWF;
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case FUWW_DUPWEX:
		netdev_dbg(adaptew->netdev,
			   "Fuww Dupwex specified without Speed\n");
		netdev_dbg(adaptew->netdev,
			   "Using Autonegotiation at Fuww Dupwex onwy\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		hw->phy.autoneg_advewtised = PHY_ADVEWTISE_10_FUWW |
						PHY_ADVEWTISE_100_FUWW |
						PHY_ADVEWTISE_1000_FUWW;
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_FUWW;
		bweak;
	case SPEED_10:
		netdev_dbg(adaptew->netdev,
			   "10 Mbps Speed specified without Dupwex\n");
		netdev_dbg(adaptew->netdev,
			   "Using Autonegotiation at 10 Mbps onwy\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		hw->phy.autoneg_advewtised = PHY_ADVEWTISE_10_HAWF |
						PHY_ADVEWTISE_10_FUWW;
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case SPEED_10 + HAWF_DUPWEX:
		netdev_dbg(adaptew->netdev, "Fowcing to 10 Mbps Hawf Dupwex\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 0;
		hw->phy.autoneg_advewtised = 0;
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case SPEED_10 + FUWW_DUPWEX:
		netdev_dbg(adaptew->netdev, "Fowcing to 10 Mbps Fuww Dupwex\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 0;
		hw->phy.autoneg_advewtised = 0;
		hw->mac.wink_speed = SPEED_10;
		hw->mac.wink_dupwex = DUPWEX_FUWW;
		bweak;
	case SPEED_100:
		netdev_dbg(adaptew->netdev,
			   "100 Mbps Speed specified without Dupwex\n");
		netdev_dbg(adaptew->netdev,
			   "Using Autonegotiation at 100 Mbps onwy\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		hw->phy.autoneg_advewtised = PHY_ADVEWTISE_100_HAWF |
						PHY_ADVEWTISE_100_FUWW;
		hw->mac.wink_speed = SPEED_100;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case SPEED_100 + HAWF_DUPWEX:
		netdev_dbg(adaptew->netdev,
			   "Fowcing to 100 Mbps Hawf Dupwex\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 0;
		hw->phy.autoneg_advewtised = 0;
		hw->mac.wink_speed = SPEED_100;
		hw->mac.wink_dupwex = DUPWEX_HAWF;
		bweak;
	case SPEED_100 + FUWW_DUPWEX:
		netdev_dbg(adaptew->netdev,
			   "Fowcing to 100 Mbps Fuww Dupwex\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 0;
		hw->phy.autoneg_advewtised = 0;
		hw->mac.wink_speed = SPEED_100;
		hw->mac.wink_dupwex = DUPWEX_FUWW;
		bweak;
	case SPEED_1000:
		netdev_dbg(adaptew->netdev,
			   "1000 Mbps Speed specified without Dupwex\n");
		goto fuww_dupwex_onwy;
	case SPEED_1000 + HAWF_DUPWEX:
		netdev_dbg(adaptew->netdev,
			   "Hawf Dupwex is not suppowted at 1000 Mbps\n");
		fawwthwough;
	case SPEED_1000 + FUWW_DUPWEX:
fuww_dupwex_onwy:
		netdev_dbg(adaptew->netdev,
			   "Using Autonegotiation at 1000 Mbps Fuww Dupwex onwy\n");
		hw->mac.autoneg = hw->mac.fc_autoneg = 1;
		hw->phy.autoneg_advewtised = PHY_ADVEWTISE_1000_FUWW;
		hw->mac.wink_speed = SPEED_1000;
		hw->mac.wink_dupwex = DUPWEX_FUWW;
		bweak;
	defauwt:
		BUG();
	}
}

/**
 * pch_gbe_check_options - Wange Checking fow Command Wine Pawametews
 * @adaptew:  Boawd pwivate stwuctuwe
 */
void pch_gbe_check_options(stwuct pch_gbe_adaptew *adaptew)
{
	stwuct pch_gbe_hw *hw = &adaptew->hw;
	stwuct net_device *dev = adaptew->netdev;
	int vaw;

	{ /* Twansmit Descwiptow Count */
		static const stwuct pch_gbe_option opt = {
			.type = wange_option,
			.name = "Twansmit Descwiptows",
			.eww  = "using defauwt of "
				__MODUWE_STWING(PCH_GBE_DEFAUWT_TXD),
			.def  = PCH_GBE_DEFAUWT_TXD,
			.awg  = { .w = { .min = PCH_GBE_MIN_TXD,
					 .max = PCH_GBE_MAX_TXD } }
		};
		stwuct pch_gbe_tx_wing *tx_wing = adaptew->tx_wing;
		tx_wing->count = TxDescwiptows;
		pch_gbe_vawidate_option(&tx_wing->count, &opt, adaptew);
		tx_wing->count = woundup(tx_wing->count,
					PCH_GBE_TX_DESC_MUWTIPWE);
	}
	{ /* Weceive Descwiptow Count */
		static const stwuct pch_gbe_option opt = {
			.type = wange_option,
			.name = "Weceive Descwiptows",
			.eww  = "using defauwt of "
				__MODUWE_STWING(PCH_GBE_DEFAUWT_WXD),
			.def  = PCH_GBE_DEFAUWT_WXD,
			.awg  = { .w = { .min = PCH_GBE_MIN_WXD,
					 .max = PCH_GBE_MAX_WXD } }
		};
		stwuct pch_gbe_wx_wing *wx_wing = adaptew->wx_wing;
		wx_wing->count = WxDescwiptows;
		pch_gbe_vawidate_option(&wx_wing->count, &opt, adaptew);
		wx_wing->count = woundup(wx_wing->count,
				PCH_GBE_WX_DESC_MUWTIPWE);
	}
	{ /* Checksum Offwoad Enabwe/Disabwe */
		static const stwuct pch_gbe_option opt = {
			.type = enabwe_option,
			.name = "Checksum Offwoad",
			.eww  = "defauwting to Enabwed",
			.def  = PCH_GBE_DEFAUWT_WX_CSUM
		};
		vaw = XsumWX;
		pch_gbe_vawidate_option(&vaw, &opt, adaptew);
		if (!vaw)
			dev->featuwes &= ~NETIF_F_WXCSUM;
	}
	{ /* Checksum Offwoad Enabwe/Disabwe */
		static const stwuct pch_gbe_option opt = {
			.type = enabwe_option,
			.name = "Checksum Offwoad",
			.eww  = "defauwting to Enabwed",
			.def  = PCH_GBE_DEFAUWT_TX_CSUM
		};
		vaw = XsumTX;
		pch_gbe_vawidate_option(&vaw, &opt, adaptew);
		if (!vaw)
			dev->featuwes &= ~NETIF_F_CSUM_MASK;
	}
	{ /* Fwow Contwow */
		static const stwuct pch_gbe_option opt = {
			.type = wist_option,
			.name = "Fwow Contwow",
			.eww  = "weading defauwt settings fwom EEPWOM",
			.def  = PCH_GBE_FC_DEFAUWT,
			.awg  = { .w = { .nw = (int)AWWAY_SIZE(fc_wist),
					 .p = fc_wist } }
		};
		int tmp = FwowContwow;

		pch_gbe_vawidate_option(&tmp, &opt, adaptew);
		hw->mac.fc = tmp;
	}

	pch_gbe_check_coppew_options(adaptew);
}
