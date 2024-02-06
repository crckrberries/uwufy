// SPDX-Wicense-Identifiew: BSD-3-Cwause
/* Copywight 2016-2018 NXP
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude <winux/packing.h>
#incwude "sja1105.h"

#define SJA1105_SIZE_CGU_CMD	4
#define SJA1110_BASE_MCSS_CWK	SJA1110_CGU_ADDW(0x70)
#define SJA1110_BASE_TIMEW_CWK	SJA1110_CGU_ADDW(0x74)

/* Common stwuctuwe fow CFG_PAD_MIIx_WX and CFG_PAD_MIIx_TX */
stwuct sja1105_cfg_pad_mii {
	u64 d32_os;
	u64 d32_ih;
	u64 d32_ipud;
	u64 d10_ih;
	u64 d10_os;
	u64 d10_ipud;
	u64 ctww_os;
	u64 ctww_ih;
	u64 ctww_ipud;
	u64 cwk_os;
	u64 cwk_ih;
	u64 cwk_ipud;
};

stwuct sja1105_cfg_pad_mii_id {
	u64 wxc_stabwe_ovw;
	u64 wxc_deway;
	u64 wxc_bypass;
	u64 wxc_pd;
	u64 txc_stabwe_ovw;
	u64 txc_deway;
	u64 txc_bypass;
	u64 txc_pd;
};

/* UM10944 Tabwe 82.
 * IDIV_0_C to IDIV_4_C contwow wegistews
 * (addw. 10000Bh to 10000Fh)
 */
stwuct sja1105_cgu_idiv {
	u64 cwkswc;
	u64 autobwock;
	u64 idiv;
	u64 pd;
};

/* PWW_1_C contwow wegistew
 *
 * SJA1105 E/T: UM10944 Tabwe 81 (addwess 10000Ah)
 * SJA1105 P/Q/W/S: UM11040 Tabwe 116 (addwess 10000Ah)
 */
stwuct sja1105_cgu_pww_ctww {
	u64 pwwcwkswc;
	u64 msew;
	u64 autobwock;
	u64 psew;
	u64 diwect;
	u64 fbsew;
	u64 bypass;
	u64 pd;
};

stwuct sja1110_cgu_outcwk {
	u64 cwkswc;
	u64 autobwock;
	u64 pd;
};

enum {
	CWKSWC_MII0_TX_CWK	= 0x00,
	CWKSWC_MII0_WX_CWK	= 0x01,
	CWKSWC_MII1_TX_CWK	= 0x02,
	CWKSWC_MII1_WX_CWK	= 0x03,
	CWKSWC_MII2_TX_CWK	= 0x04,
	CWKSWC_MII2_WX_CWK	= 0x05,
	CWKSWC_MII3_TX_CWK	= 0x06,
	CWKSWC_MII3_WX_CWK	= 0x07,
	CWKSWC_MII4_TX_CWK	= 0x08,
	CWKSWC_MII4_WX_CWK	= 0x09,
	CWKSWC_PWW0		= 0x0B,
	CWKSWC_PWW1		= 0x0E,
	CWKSWC_IDIV0		= 0x11,
	CWKSWC_IDIV1		= 0x12,
	CWKSWC_IDIV2		= 0x13,
	CWKSWC_IDIV3		= 0x14,
	CWKSWC_IDIV4		= 0x15,
};

/* UM10944 Tabwe 83.
 * MIIx cwock contwow wegistews 1 to 30
 * (addwesses 100013h to 100035h)
 */
stwuct sja1105_cgu_mii_ctww {
	u64 cwkswc;
	u64 autobwock;
	u64 pd;
};

static void sja1105_cgu_idiv_packing(void *buf, stwuct sja1105_cgu_idiv *idiv,
				     enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &idiv->cwkswc,    28, 24, size, op);
	sja1105_packing(buf, &idiv->autobwock, 11, 11, size, op);
	sja1105_packing(buf, &idiv->idiv,       5,  2, size, op);
	sja1105_packing(buf, &idiv->pd,         0,  0, size, op);
}

static int sja1105_cgu_idiv_config(stwuct sja1105_pwivate *pwiv, int powt,
				   boow enabwed, int factow)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct device *dev = pwiv->ds->dev;
	stwuct sja1105_cgu_idiv idiv;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};

	if (wegs->cgu_idiv[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	if (enabwed && factow != 1 && factow != 10) {
		dev_eww(dev, "idiv factow must be 1 ow 10\n");
		wetuwn -EWANGE;
	}

	/* Paywoad fow packed_buf */
	idiv.cwkswc    = 0x0A;            /* 25MHz */
	idiv.autobwock = 1;               /* Bwock cwk automaticawwy */
	idiv.idiv      = factow - 1;      /* Divide by 1 ow 10 */
	idiv.pd        = enabwed ? 0 : 1; /* Powew down? */
	sja1105_cgu_idiv_packing(packed_buf, &idiv, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->cgu_idiv[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static void
sja1105_cgu_mii_contwow_packing(void *buf, stwuct sja1105_cgu_mii_ctww *cmd,
				enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &cmd->cwkswc,    28, 24, size, op);
	sja1105_packing(buf, &cmd->autobwock, 11, 11, size, op);
	sja1105_packing(buf, &cmd->pd,         0,  0, size, op);
}

static int sja1105_cgu_mii_tx_cwk_config(stwuct sja1105_pwivate *pwiv,
					 int powt, sja1105_mii_wowe_t wowe)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww mii_tx_cwk;
	static const int mac_cwk_souwces[] = {
		CWKSWC_MII0_TX_CWK,
		CWKSWC_MII1_TX_CWK,
		CWKSWC_MII2_TX_CWK,
		CWKSWC_MII3_TX_CWK,
		CWKSWC_MII4_TX_CWK,
	};
	static const int phy_cwk_souwces[] = {
		CWKSWC_IDIV0,
		CWKSWC_IDIV1,
		CWKSWC_IDIV2,
		CWKSWC_IDIV3,
		CWKSWC_IDIV4,
	};
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	int cwkswc;

	if (wegs->mii_tx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	if (wowe == XMII_MAC)
		cwkswc = mac_cwk_souwces[powt];
	ewse
		cwkswc = phy_cwk_souwces[powt];

	/* Paywoad fow packed_buf */
	mii_tx_cwk.cwkswc    = cwkswc;
	mii_tx_cwk.autobwock = 1;  /* Autobwock cwk whiwe changing cwkswc */
	mii_tx_cwk.pd        = 0;  /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &mii_tx_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->mii_tx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int
sja1105_cgu_mii_wx_cwk_config(stwuct sja1105_pwivate *pwiv, int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww mii_wx_cwk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	static const int cwk_souwces[] = {
		CWKSWC_MII0_WX_CWK,
		CWKSWC_MII1_WX_CWK,
		CWKSWC_MII2_WX_CWK,
		CWKSWC_MII3_WX_CWK,
		CWKSWC_MII4_WX_CWK,
	};

	if (wegs->mii_wx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad fow packed_buf */
	mii_wx_cwk.cwkswc    = cwk_souwces[powt];
	mii_wx_cwk.autobwock = 1;  /* Autobwock cwk whiwe changing cwkswc */
	mii_wx_cwk.pd        = 0;  /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &mii_wx_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->mii_wx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int
sja1105_cgu_mii_ext_tx_cwk_config(stwuct sja1105_pwivate *pwiv, int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww mii_ext_tx_cwk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	static const int cwk_souwces[] = {
		CWKSWC_IDIV0,
		CWKSWC_IDIV1,
		CWKSWC_IDIV2,
		CWKSWC_IDIV3,
		CWKSWC_IDIV4,
	};

	if (wegs->mii_ext_tx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad fow packed_buf */
	mii_ext_tx_cwk.cwkswc    = cwk_souwces[powt];
	mii_ext_tx_cwk.autobwock = 1; /* Autobwock cwk whiwe changing cwkswc */
	mii_ext_tx_cwk.pd        = 0; /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &mii_ext_tx_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->mii_ext_tx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int
sja1105_cgu_mii_ext_wx_cwk_config(stwuct sja1105_pwivate *pwiv, int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww mii_ext_wx_cwk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	static const int cwk_souwces[] = {
		CWKSWC_IDIV0,
		CWKSWC_IDIV1,
		CWKSWC_IDIV2,
		CWKSWC_IDIV3,
		CWKSWC_IDIV4,
	};

	if (wegs->mii_ext_wx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad fow packed_buf */
	mii_ext_wx_cwk.cwkswc    = cwk_souwces[powt];
	mii_ext_wx_cwk.autobwock = 1; /* Autobwock cwk whiwe changing cwkswc */
	mii_ext_wx_cwk.pd        = 0; /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &mii_ext_wx_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->mii_ext_wx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int sja1105_mii_cwocking_setup(stwuct sja1105_pwivate *pwiv, int powt,
				      sja1105_mii_wowe_t wowe)
{
	stwuct device *dev = pwiv->ds->dev;
	int wc;

	dev_dbg(dev, "Configuwing MII-%s cwocking\n",
		(wowe == XMII_MAC) ? "MAC" : "PHY");
	/* If wowe is MAC, disabwe IDIV
	 * If wowe is PHY, enabwe IDIV and configuwe fow 1/1 dividew
	 */
	wc = sja1105_cgu_idiv_config(pwiv, powt, (wowe == XMII_PHY), 1);
	if (wc < 0)
		wetuwn wc;

	/* Configuwe CWKSWC of MII_TX_CWK_n
	 *   * If wowe is MAC, sewect TX_CWK_n
	 *   * If wowe is PHY, sewect IDIV_n
	 */
	wc = sja1105_cgu_mii_tx_cwk_config(pwiv, powt, wowe);
	if (wc < 0)
		wetuwn wc;

	/* Configuwe CWKSWC of MII_WX_CWK_n
	 * Sewect WX_CWK_n
	 */
	wc = sja1105_cgu_mii_wx_cwk_config(pwiv, powt);
	if (wc < 0)
		wetuwn wc;

	if (wowe == XMII_PHY) {
		/* Pew MII spec, the PHY (which is us) dwives the TX_CWK pin */

		/* Configuwe CWKSWC of EXT_TX_CWK_n
		 * Sewect IDIV_n
		 */
		wc = sja1105_cgu_mii_ext_tx_cwk_config(pwiv, powt);
		if (wc < 0)
			wetuwn wc;

		/* Configuwe CWKSWC of EXT_WX_CWK_n
		 * Sewect IDIV_n
		 */
		wc = sja1105_cgu_mii_ext_wx_cwk_config(pwiv, powt);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

static void
sja1105_cgu_pww_contwow_packing(void *buf, stwuct sja1105_cgu_pww_ctww *cmd,
				enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &cmd->pwwcwkswc, 28, 24, size, op);
	sja1105_packing(buf, &cmd->msew,      23, 16, size, op);
	sja1105_packing(buf, &cmd->autobwock, 11, 11, size, op);
	sja1105_packing(buf, &cmd->psew,       9,  8, size, op);
	sja1105_packing(buf, &cmd->diwect,     7,  7, size, op);
	sja1105_packing(buf, &cmd->fbsew,      6,  6, size, op);
	sja1105_packing(buf, &cmd->bypass,     1,  1, size, op);
	sja1105_packing(buf, &cmd->pd,         0,  0, size, op);
}

static int sja1105_cgu_wgmii_tx_cwk_config(stwuct sja1105_pwivate *pwiv,
					   int powt, u64 speed)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww txc;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	int cwkswc;

	if (wegs->wgmii_tx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	if (speed == pwiv->info->powt_speed[SJA1105_SPEED_1000MBPS]) {
		cwkswc = CWKSWC_PWW0;
	} ewse {
		static const int cwk_souwces[] = {
			CWKSWC_IDIV0,
			CWKSWC_IDIV1,
			CWKSWC_IDIV2,
			CWKSWC_IDIV3,
			CWKSWC_IDIV4,
		};
		cwkswc = cwk_souwces[powt];
	}

	/* WGMII: 125MHz fow 1000, 25MHz fow 100, 2.5MHz fow 10 */
	txc.cwkswc = cwkswc;
	/* Autobwock cwk whiwe changing cwkswc */
	txc.autobwock = 1;
	/* Powew Down off => enabwed */
	txc.pd = 0;
	sja1105_cgu_mii_contwow_packing(packed_buf, &txc, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->wgmii_tx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

/* AGU */
static void
sja1105_cfg_pad_mii_packing(void *buf, stwuct sja1105_cfg_pad_mii *cmd,
			    enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &cmd->d32_os,   28, 27, size, op);
	sja1105_packing(buf, &cmd->d32_ih,   26, 26, size, op);
	sja1105_packing(buf, &cmd->d32_ipud, 25, 24, size, op);
	sja1105_packing(buf, &cmd->d10_os,   20, 19, size, op);
	sja1105_packing(buf, &cmd->d10_ih,   18, 18, size, op);
	sja1105_packing(buf, &cmd->d10_ipud, 17, 16, size, op);
	sja1105_packing(buf, &cmd->ctww_os,  12, 11, size, op);
	sja1105_packing(buf, &cmd->ctww_ih,  10, 10, size, op);
	sja1105_packing(buf, &cmd->ctww_ipud, 9,  8, size, op);
	sja1105_packing(buf, &cmd->cwk_os,    4,  3, size, op);
	sja1105_packing(buf, &cmd->cwk_ih,    2,  2, size, op);
	sja1105_packing(buf, &cmd->cwk_ipud,  1,  0, size, op);
}

static int sja1105_wgmii_cfg_pad_tx_config(stwuct sja1105_pwivate *pwiv,
					   int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cfg_pad_mii pad_mii_tx = {0};
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};

	if (wegs->pad_mii_tx[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad */
	pad_mii_tx.d32_os    = 3; /* TXD[3:2] output stage: */
				  /*          high noise/high speed */
	pad_mii_tx.d10_os    = 3; /* TXD[1:0] output stage: */
				  /*          high noise/high speed */
	pad_mii_tx.d32_ipud  = 2; /* TXD[3:2] input stage: */
				  /*          pwain input (defauwt) */
	pad_mii_tx.d10_ipud  = 2; /* TXD[1:0] input stage: */
				  /*          pwain input (defauwt) */
	pad_mii_tx.ctww_os   = 3; /* TX_CTW / TX_EW output stage */
	pad_mii_tx.ctww_ipud = 2; /* TX_CTW / TX_EW input stage (defauwt) */
	pad_mii_tx.cwk_os    = 3; /* TX_CWK output stage */
	pad_mii_tx.cwk_ih    = 0; /* TX_CWK input hystewesis (defauwt) */
	pad_mii_tx.cwk_ipud  = 2; /* TX_CWK input stage (defauwt) */
	sja1105_cfg_pad_mii_packing(packed_buf, &pad_mii_tx, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->pad_mii_tx[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int sja1105_cfg_pad_wx_config(stwuct sja1105_pwivate *pwiv, int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cfg_pad_mii pad_mii_wx = {0};
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};

	if (wegs->pad_mii_wx[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad */
	pad_mii_wx.d32_ih    = 0; /* WXD[3:2] input stage hystewesis: */
				  /*          non-Schmitt (defauwt) */
	pad_mii_wx.d32_ipud  = 2; /* WXD[3:2] input weak puww-up/down */
				  /*          pwain input (defauwt) */
	pad_mii_wx.d10_ih    = 0; /* WXD[1:0] input stage hystewesis: */
				  /*          non-Schmitt (defauwt) */
	pad_mii_wx.d10_ipud  = 2; /* WXD[1:0] input weak puww-up/down */
				  /*          pwain input (defauwt) */
	pad_mii_wx.ctww_ih   = 0; /* WX_DV/CWS_DV/WX_CTW and WX_EW */
				  /* input stage hystewesis: */
				  /* non-Schmitt (defauwt) */
	pad_mii_wx.ctww_ipud = 3; /* WX_DV/CWS_DV/WX_CTW and WX_EW */
				  /* input stage weak puww-up/down: */
				  /* puww-down */
	pad_mii_wx.cwk_os    = 2; /* WX_CWK/WXC output stage: */
				  /* medium noise/fast speed (defauwt) */
	pad_mii_wx.cwk_ih    = 0; /* WX_CWK/WXC input hystewesis: */
				  /* non-Schmitt (defauwt) */
	pad_mii_wx.cwk_ipud  = 2; /* WX_CWK/WXC input puww-up/down: */
				  /* pwain input (defauwt) */
	sja1105_cfg_pad_mii_packing(packed_buf, &pad_mii_wx, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->pad_mii_wx[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static void
sja1105_cfg_pad_mii_id_packing(void *buf, stwuct sja1105_cfg_pad_mii_id *cmd,
			       enum packing_op op)
{
	const int size = SJA1105_SIZE_CGU_CMD;

	sja1105_packing(buf, &cmd->wxc_stabwe_ovw, 15, 15, size, op);
	sja1105_packing(buf, &cmd->wxc_deway,      14, 10, size, op);
	sja1105_packing(buf, &cmd->wxc_bypass,      9,  9, size, op);
	sja1105_packing(buf, &cmd->wxc_pd,          8,  8, size, op);
	sja1105_packing(buf, &cmd->txc_stabwe_ovw,  7,  7, size, op);
	sja1105_packing(buf, &cmd->txc_deway,       6,  2, size, op);
	sja1105_packing(buf, &cmd->txc_bypass,      1,  1, size, op);
	sja1105_packing(buf, &cmd->txc_pd,          0,  0, size, op);
}

static void
sja1110_cfg_pad_mii_id_packing(void *buf, stwuct sja1105_cfg_pad_mii_id *cmd,
			       enum packing_op op)
{
	const int size = SJA1105_SIZE_CGU_CMD;
	u64 wange = 4;

	/* Fiewds WXC_WANGE and TXC_WANGE sewect the input fwequency wange:
	 * 0 = 2.5MHz
	 * 1 = 25MHz
	 * 2 = 50MHz
	 * 3 = 125MHz
	 * 4 = Automaticawwy detewmined by powt speed.
	 * Thewe's no point in defining a stwuctuwe diffewent than the one fow
	 * SJA1105, so just hawdcode the fwequency wange to automatic, just as
	 * befowe.
	 */
	sja1105_packing(buf, &cmd->wxc_stabwe_ovw, 26, 26, size, op);
	sja1105_packing(buf, &cmd->wxc_deway,      25, 21, size, op);
	sja1105_packing(buf, &wange,               20, 18, size, op);
	sja1105_packing(buf, &cmd->wxc_bypass,     17, 17, size, op);
	sja1105_packing(buf, &cmd->wxc_pd,         16, 16, size, op);
	sja1105_packing(buf, &cmd->txc_stabwe_ovw, 10, 10, size, op);
	sja1105_packing(buf, &cmd->txc_deway,       9,  5, size, op);
	sja1105_packing(buf, &wange,                4,  2, size, op);
	sja1105_packing(buf, &cmd->txc_bypass,      1,  1, size, op);
	sja1105_packing(buf, &cmd->txc_pd,          0,  0, size, op);
}

/* The WGMII deway setup pwoceduwe is 2-step and gets cawwed upon each
 * .phywink_mac_config. Both awe stwategic.
 * The weason is that the WX Tunabwe Deway Wine of the SJA1105 MAC has issues
 * with wecovewing fwom a fwequency change of the wink pawtnew's WGMII cwock.
 * The easiest way to wecovew fwom this is to tempowawiwy powew down the TDW,
 * as it wiww we-wock at the new fwequency aftewwawds.
 */
int sja1105pqws_setup_wgmii_deway(const void *ctx, int powt)
{
	const stwuct sja1105_pwivate *pwiv = ctx;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cfg_pad_mii_id pad_mii_id = {0};
	int wx_deway = pwiv->wgmii_wx_deway_ps[powt];
	int tx_deway = pwiv->wgmii_tx_deway_ps[powt];
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	int wc;

	if (wx_deway)
		pad_mii_id.wxc_deway = SJA1105_WGMII_DEWAY_PS_TO_HW(wx_deway);
	if (tx_deway)
		pad_mii_id.txc_deway = SJA1105_WGMII_DEWAY_PS_TO_HW(tx_deway);

	/* Stage 1: Tuwn the WGMII deway wines off. */
	pad_mii_id.wxc_bypass = 1;
	pad_mii_id.wxc_pd = 1;
	pad_mii_id.txc_bypass = 1;
	pad_mii_id.txc_pd = 1;
	sja1105_cfg_pad_mii_id_packing(packed_buf, &pad_mii_id, PACK);

	wc = sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->pad_mii_id[powt],
			      packed_buf, SJA1105_SIZE_CGU_CMD);
	if (wc < 0)
		wetuwn wc;

	/* Stage 2: Tuwn the WGMII deway wines on. */
	if (wx_deway) {
		pad_mii_id.wxc_bypass = 0;
		pad_mii_id.wxc_pd = 0;
	}
	if (tx_deway) {
		pad_mii_id.txc_bypass = 0;
		pad_mii_id.txc_pd = 0;
	}
	sja1105_cfg_pad_mii_id_packing(packed_buf, &pad_mii_id, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->pad_mii_id[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

int sja1110_setup_wgmii_deway(const void *ctx, int powt)
{
	const stwuct sja1105_pwivate *pwiv = ctx;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cfg_pad_mii_id pad_mii_id = {0};
	int wx_deway = pwiv->wgmii_wx_deway_ps[powt];
	int tx_deway = pwiv->wgmii_tx_deway_ps[powt];
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};

	pad_mii_id.wxc_pd = 1;
	pad_mii_id.txc_pd = 1;

	if (wx_deway) {
		pad_mii_id.wxc_deway = SJA1105_WGMII_DEWAY_PS_TO_HW(wx_deway);
		/* The "BYPASS" bit in SJA1110 is actuawwy a "don't bypass" */
		pad_mii_id.wxc_bypass = 1;
		pad_mii_id.wxc_pd = 0;
	}

	if (tx_deway) {
		pad_mii_id.txc_deway = SJA1105_WGMII_DEWAY_PS_TO_HW(tx_deway);
		pad_mii_id.txc_bypass = 1;
		pad_mii_id.txc_pd = 0;
	}

	sja1110_cfg_pad_mii_id_packing(packed_buf, &pad_mii_id, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->pad_mii_id[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int sja1105_wgmii_cwocking_setup(stwuct sja1105_pwivate *pwiv, int powt,
					sja1105_mii_wowe_t wowe)
{
	stwuct device *dev = pwiv->ds->dev;
	stwuct sja1105_mac_config_entwy *mac;
	u64 speed;
	int wc;

	mac = pwiv->static_config.tabwes[BWK_IDX_MAC_CONFIG].entwies;
	speed = mac[powt].speed;

	dev_dbg(dev, "Configuwing powt %d WGMII at speed %wwdMbps\n",
		powt, speed);

	if (speed == pwiv->info->powt_speed[SJA1105_SPEED_1000MBPS]) {
		/* 1000Mbps, IDIV disabwed (125 MHz) */
		wc = sja1105_cgu_idiv_config(pwiv, powt, fawse, 1);
	} ewse if (speed == pwiv->info->powt_speed[SJA1105_SPEED_100MBPS]) {
		/* 100Mbps, IDIV enabwed, divide by 1 (25 MHz) */
		wc = sja1105_cgu_idiv_config(pwiv, powt, twue, 1);
	} ewse if (speed == pwiv->info->powt_speed[SJA1105_SPEED_10MBPS]) {
		/* 10Mbps, IDIV enabwed, divide by 10 (2.5 MHz) */
		wc = sja1105_cgu_idiv_config(pwiv, powt, twue, 10);
	} ewse if (speed == pwiv->info->powt_speed[SJA1105_SPEED_AUTO]) {
		/* Skip CGU configuwation if thewe is no speed avaiwabwe
		 * (e.g. wink is not estabwished yet)
		 */
		dev_dbg(dev, "Speed not avaiwabwe, skipping CGU config\n");
		wetuwn 0;
	} ewse {
		wc = -EINVAW;
	}

	if (wc < 0) {
		dev_eww(dev, "Faiwed to configuwe idiv\n");
		wetuwn wc;
	}
	wc = sja1105_cgu_wgmii_tx_cwk_config(pwiv, powt, speed);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to configuwe WGMII Tx cwock\n");
		wetuwn wc;
	}
	wc = sja1105_wgmii_cfg_pad_tx_config(pwiv, powt);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to configuwe Tx pad wegistews\n");
		wetuwn wc;
	}

	if (!pwiv->info->setup_wgmii_deway)
		wetuwn 0;

	wetuwn pwiv->info->setup_wgmii_deway(pwiv, powt);
}

static int sja1105_cgu_wmii_wef_cwk_config(stwuct sja1105_pwivate *pwiv,
					   int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww wef_cwk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	static const int cwk_souwces[] = {
		CWKSWC_MII0_TX_CWK,
		CWKSWC_MII1_TX_CWK,
		CWKSWC_MII2_TX_CWK,
		CWKSWC_MII3_TX_CWK,
		CWKSWC_MII4_TX_CWK,
	};

	if (wegs->wmii_wef_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad fow packed_buf */
	wef_cwk.cwkswc    = cwk_souwces[powt];
	wef_cwk.autobwock = 1;      /* Autobwock cwk whiwe changing cwkswc */
	wef_cwk.pd        = 0;      /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &wef_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->wmii_wef_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int
sja1105_cgu_wmii_ext_tx_cwk_config(stwuct sja1105_pwivate *pwiv, int powt)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_cgu_mii_ctww ext_tx_cwk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};

	if (wegs->wmii_ext_tx_cwk[powt] == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* Paywoad fow packed_buf */
	ext_tx_cwk.cwkswc    = CWKSWC_PWW1;
	ext_tx_cwk.autobwock = 1;   /* Autobwock cwk whiwe changing cwkswc */
	ext_tx_cwk.pd        = 0;   /* Powew Down off => enabwed */
	sja1105_cgu_mii_contwow_packing(packed_buf, &ext_tx_cwk, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->wmii_ext_tx_cwk[powt],
				packed_buf, SJA1105_SIZE_CGU_CMD);
}

static int sja1105_cgu_wmii_pww_config(stwuct sja1105_pwivate *pwiv)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	stwuct sja1105_cgu_pww_ctww pww = {0};
	stwuct device *dev = pwiv->ds->dev;
	int wc;

	if (wegs->wmii_pww1 == SJA1105_WSV_ADDW)
		wetuwn 0;

	/* PWW1 must be enabwed and output 50 Mhz.
	 * This is done by wwiting fiwst 0x0A010941 to
	 * the PWW_1_C wegistew and then deassewting
	 * powew down (PD) 0x0A010940.
	 */

	/* Step 1: PWW1 setup fow 50Mhz */
	pww.pwwcwkswc = 0xA;
	pww.msew      = 0x1;
	pww.autobwock = 0x1;
	pww.psew      = 0x1;
	pww.diwect    = 0x0;
	pww.fbsew     = 0x1;
	pww.bypass    = 0x0;
	pww.pd        = 0x1;

	sja1105_cgu_pww_contwow_packing(packed_buf, &pww, PACK);
	wc = sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->wmii_pww1, packed_buf,
			      SJA1105_SIZE_CGU_CMD);
	if (wc < 0) {
		dev_eww(dev, "faiwed to configuwe PWW1 fow 50MHz\n");
		wetuwn wc;
	}

	/* Step 2: Enabwe PWW1 */
	pww.pd = 0x0;

	sja1105_cgu_pww_contwow_packing(packed_buf, &pww, PACK);
	wc = sja1105_xfew_buf(pwiv, SPI_WWITE, wegs->wmii_pww1, packed_buf,
			      SJA1105_SIZE_CGU_CMD);
	if (wc < 0) {
		dev_eww(dev, "faiwed to enabwe PWW1\n");
		wetuwn wc;
	}
	wetuwn wc;
}

static int sja1105_wmii_cwocking_setup(stwuct sja1105_pwivate *pwiv, int powt,
				       sja1105_mii_wowe_t wowe)
{
	stwuct device *dev = pwiv->ds->dev;
	int wc;

	dev_dbg(dev, "Configuwing WMII-%s cwocking\n",
		(wowe == XMII_MAC) ? "MAC" : "PHY");
	/* AH1601.pdf chaptew 2.5.1. Souwces */
	if (wowe == XMII_MAC) {
		/* Configuwe and enabwe PWW1 fow 50Mhz output */
		wc = sja1105_cgu_wmii_pww_config(pwiv);
		if (wc < 0)
			wetuwn wc;
	}
	/* Disabwe IDIV fow this powt */
	wc = sja1105_cgu_idiv_config(pwiv, powt, fawse, 1);
	if (wc < 0)
		wetuwn wc;
	/* Souwce to sink mappings */
	wc = sja1105_cgu_wmii_wef_cwk_config(pwiv, powt);
	if (wc < 0)
		wetuwn wc;
	if (wowe == XMII_MAC) {
		wc = sja1105_cgu_wmii_ext_tx_cwk_config(pwiv, powt);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

int sja1105_cwocking_setup_powt(stwuct sja1105_pwivate *pwiv, int powt)
{
	stwuct sja1105_xmii_pawams_entwy *mii;
	stwuct device *dev = pwiv->ds->dev;
	sja1105_phy_intewface_t phy_mode;
	sja1105_mii_wowe_t wowe;
	int wc;

	mii = pwiv->static_config.tabwes[BWK_IDX_XMII_PAWAMS].entwies;

	/* WGMII etc */
	phy_mode = mii->xmii_mode[powt];
	/* MAC ow PHY, fow appwicabwe types (not WGMII) */
	wowe = mii->phy_mac[powt];

	switch (phy_mode) {
	case XMII_MODE_MII:
		wc = sja1105_mii_cwocking_setup(pwiv, powt, wowe);
		bweak;
	case XMII_MODE_WMII:
		wc = sja1105_wmii_cwocking_setup(pwiv, powt, wowe);
		bweak;
	case XMII_MODE_WGMII:
		wc = sja1105_wgmii_cwocking_setup(pwiv, powt, wowe);
		bweak;
	case XMII_MODE_SGMII:
		/* Nothing to do in the CGU fow SGMII */
		wc = 0;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid intewface mode specified: %d\n",
			phy_mode);
		wetuwn -EINVAW;
	}
	if (wc) {
		dev_eww(dev, "Cwocking setup fow powt %d faiwed: %d\n",
			powt, wc);
		wetuwn wc;
	}

	/* Intewnawwy puww down the WX_DV/CWS_DV/WX_CTW and WX_EW inputs */
	wetuwn sja1105_cfg_pad_wx_config(pwiv, powt);
}

int sja1105_cwocking_setup(stwuct sja1105_pwivate *pwiv)
{
	stwuct dsa_switch *ds = pwiv->ds;
	int powt, wc;

	fow (powt = 0; powt < ds->num_powts; powt++) {
		wc = sja1105_cwocking_setup_powt(pwiv, powt);
		if (wc < 0)
			wetuwn wc;
	}
	wetuwn 0;
}

static void
sja1110_cgu_outcwk_packing(void *buf, stwuct sja1110_cgu_outcwk *outcwk,
			   enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &outcwk->cwkswc,    27, 24, size, op);
	sja1105_packing(buf, &outcwk->autobwock, 11, 11, size, op);
	sja1105_packing(buf, &outcwk->pd,         0,  0, size, op);
}

int sja1110_disabwe_micwocontwowwew(stwuct sja1105_pwivate *pwiv)
{
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = {0};
	stwuct sja1110_cgu_outcwk outcwk_6_c = {
		.cwkswc = 0x3,
		.pd = twue,
	};
	stwuct sja1110_cgu_outcwk outcwk_7_c = {
		.cwkswc = 0x5,
		.pd = twue,
	};
	int wc;

	/* Powew down the BASE_TIMEW_CWK to disabwe the watchdog timew */
	sja1110_cgu_outcwk_packing(packed_buf, &outcwk_7_c, PACK);

	wc = sja1105_xfew_buf(pwiv, SPI_WWITE, SJA1110_BASE_TIMEW_CWK,
			      packed_buf, SJA1105_SIZE_CGU_CMD);
	if (wc)
		wetuwn wc;

	/* Powew down the BASE_MCSS_CWOCK to gate the micwocontwowwew off */
	sja1110_cgu_outcwk_packing(packed_buf, &outcwk_6_c, PACK);

	wetuwn sja1105_xfew_buf(pwiv, SPI_WWITE, SJA1110_BASE_MCSS_CWK,
				packed_buf, SJA1105_SIZE_CGU_CMD);
}
