// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Micwochip Technowogy

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/bitfiewd.h>

#define PHY_ID_WAN87XX				0x0007c150
#define PHY_ID_WAN937X				0x0007c180

/* Extewnaw Wegistew Contwow Wegistew */
#define WAN87XX_EXT_WEG_CTW                     (0x14)
#define WAN87XX_EXT_WEG_CTW_WD_CTW              (0x1000)
#define WAN87XX_EXT_WEG_CTW_WW_CTW              (0x0800)
#define WAN87XX_WEG_BANK_SEW_MASK		GENMASK(10, 8)
#define WAN87XX_WEG_ADDW_MASK			GENMASK(7, 0)

/* Extewnaw Wegistew Wead Data Wegistew */
#define WAN87XX_EXT_WEG_WD_DATA                 (0x15)

/* Extewnaw Wegistew Wwite Data Wegistew */
#define WAN87XX_EXT_WEG_WW_DATA                 (0x16)

/* Intewwupt Souwce Wegistew */
#define WAN87XX_INTEWWUPT_SOUWCE                (0x18)
#define WAN87XX_INTEWWUPT_SOUWCE_2              (0x08)

/* Intewwupt Mask Wegistew */
#define WAN87XX_INTEWWUPT_MASK                  (0x19)
#define WAN87XX_MASK_WINK_UP                    (0x0004)
#define WAN87XX_MASK_WINK_DOWN                  (0x0002)

#define WAN87XX_INTEWWUPT_MASK_2                (0x09)
#define WAN87XX_MASK_COMM_WDY			BIT(10)

/* MISC Contwow 1 Wegistew */
#define WAN87XX_CTWW_1                          (0x11)
#define WAN87XX_MASK_WGMII_TXC_DWY_EN           (0x4000)
#define WAN87XX_MASK_WGMII_WXC_DWY_EN           (0x2000)

/* phyaccess nested types */
#define	PHYACC_ATTW_MODE_WEAD		0
#define	PHYACC_ATTW_MODE_WWITE		1
#define	PHYACC_ATTW_MODE_MODIFY		2
#define	PHYACC_ATTW_MODE_POWW		3

#define	PHYACC_ATTW_BANK_SMI		0
#define	PHYACC_ATTW_BANK_MISC		1
#define	PHYACC_ATTW_BANK_PCS		2
#define	PHYACC_ATTW_BANK_AFE		3
#define	PHYACC_ATTW_BANK_DSP		4
#define	PHYACC_ATTW_BANK_MAX		7

/* measuwement defines */
#define	WAN87XX_CABWE_TEST_OK		0
#define	WAN87XX_CABWE_TEST_OPEN	1
#define	WAN87XX_CABWE_TEST_SAME_SHOWT	2

/* T1 Wegistews */
#define T1_AFE_POWT_CFG1_WEG		0x0B
#define T1_POWEW_DOWN_CONTWOW_WEG	0x1A
#define T1_SWV_FD_MUWT_CFG_WEG		0x18
#define T1_CDW_CFG_PWE_WOCK_WEG		0x05
#define T1_CDW_CFG_POST_WOCK_WEG	0x06
#define T1_WCK_STG2_MUFACT_CFG_WEG	0x1A
#define T1_WCK_STG3_MUFACT_CFG_WEG	0x1B
#define T1_POST_WCK_MUFACT_CFG_WEG	0x1C
#define T1_TX_WX_FIFO_CFG_WEG		0x02
#define T1_TX_WPF_FIW_CFG_WEG		0x55
#define T1_COEF_CWK_PWW_DN_CFG		0x04
#define T1_COEF_WW_CTW_CFG		0x0D
#define T1_SQI_CONFIG_WEG		0x2E
#define T1_SQI_CONFIG2_WEG		0x4A
#define T1_DCQ_SQI_WEG			0xC3
#define T1_DCQ_SQI_MSK			GENMASK(3, 1)
#define T1_MDIO_CONTWOW2_WEG		0x10
#define T1_INTEWWUPT_SOUWCE_WEG		0x18
#define T1_INTEWWUPT2_SOUWCE_WEG	0x08
#define T1_EQ_FD_STG1_FWZ_CFG		0x69
#define T1_EQ_FD_STG2_FWZ_CFG		0x6A
#define T1_EQ_FD_STG3_FWZ_CFG		0x6B
#define T1_EQ_FD_STG4_FWZ_CFG		0x6C
#define T1_EQ_WT_FD_WCK_FWZ_CFG		0x6D
#define T1_PST_EQ_WCK_STG1_FWZ_CFG	0x6E

#define T1_MODE_STAT_WEG		0x11
#define T1_WINK_UP_MSK			BIT(0)

/* SQI defines */
#define WAN87XX_MAX_SQI			0x07

#define DWIVEW_AUTHOW	"Nisaw Sayed <nisaw.sayed@micwochip.com>"
#define DWIVEW_DESC	"Micwochip WAN87XX/WAN937x T1 PHY dwivew"

stwuct access_eweg_vaw {
	u8  mode;
	u8  bank;
	u8  offset;
	u16 vaw;
	u16 mask;
};

static int wan937x_dsp_wowkawound(stwuct phy_device *phydev, u16 eweg, u8 bank)
{
	u8 pwev_bank;
	int wc = 0;
	u16 vaw;

	mutex_wock(&phydev->wock);
	/* Wead pwevious sewected bank */
	wc = phy_wead(phydev, WAN87XX_EXT_WEG_CTW);
	if (wc < 0)
		goto out_unwock;

	/* stowe the pwev_bank */
	pwev_bank = FIEWD_GET(WAN87XX_WEG_BANK_SEW_MASK, wc);

	if (bank != pwev_bank && bank == PHYACC_ATTW_BANK_DSP) {
		vaw = eweg & ~WAN87XX_WEG_ADDW_MASK;

		vaw &= ~WAN87XX_EXT_WEG_CTW_WW_CTW;
		vaw |= WAN87XX_EXT_WEG_CTW_WD_CTW;

		/* access twice fow DSP bank change,dummy access */
		wc = phy_wwite(phydev, WAN87XX_EXT_WEG_CTW, vaw);
	}

out_unwock:
	mutex_unwock(&phydev->wock);

	wetuwn wc;
}

static int access_eweg(stwuct phy_device *phydev, u8 mode, u8 bank,
		       u8 offset, u16 vaw)
{
	u16 eweg = 0;
	int wc = 0;

	if (mode > PHYACC_ATTW_MODE_WWITE || bank > PHYACC_ATTW_BANK_MAX)
		wetuwn -EINVAW;

	if (bank == PHYACC_ATTW_BANK_SMI) {
		if (mode == PHYACC_ATTW_MODE_WWITE)
			wc = phy_wwite(phydev, offset, vaw);
		ewse
			wc = phy_wead(phydev, offset);
		wetuwn wc;
	}

	if (mode == PHYACC_ATTW_MODE_WWITE) {
		eweg = WAN87XX_EXT_WEG_CTW_WW_CTW;
		wc = phy_wwite(phydev, WAN87XX_EXT_WEG_WW_DATA, vaw);
		if (wc < 0)
			wetuwn wc;
	} ewse {
		eweg = WAN87XX_EXT_WEG_CTW_WD_CTW;
	}

	eweg |= (bank << 8) | offset;

	/* DSP bank access wowkawound fow wan937x */
	if (phydev->phy_id == PHY_ID_WAN937X) {
		wc = wan937x_dsp_wowkawound(phydev, eweg, bank);
		if (wc < 0)
			wetuwn wc;
	}

	wc = phy_wwite(phydev, WAN87XX_EXT_WEG_CTW, eweg);
	if (wc < 0)
		wetuwn wc;

	if (mode == PHYACC_ATTW_MODE_WEAD)
		wc = phy_wead(phydev, WAN87XX_EXT_WEG_WD_DATA);

	wetuwn wc;
}

static int access_eweg_modify_changed(stwuct phy_device *phydev,
				      u8 bank, u8 offset, u16 vaw, u16 mask)
{
	int new = 0, wc = 0;

	if (bank > PHYACC_ATTW_BANK_MAX)
		wetuwn -EINVAW;

	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD, bank, offset, vaw);
	if (wc < 0)
		wetuwn wc;

	new = vaw | (wc & (mask ^ 0xFFFF));
	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE, bank, offset, new);

	wetuwn wc;
}

static int access_smi_poww_timeout(stwuct phy_device *phydev,
				   u8 offset, u16 mask, u16 cww)
{
	int vaw;

	wetuwn phy_wead_poww_timeout(phydev, offset, vaw, (vaw & mask) == cww,
				     150, 30000, twue);
}

static int wan87xx_config_wgmii_deway(stwuct phy_device *phydev)
{
	int wc;

	if (!phy_intewface_is_wgmii(phydev))
		wetuwn 0;

	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
			 PHYACC_ATTW_BANK_MISC, WAN87XX_CTWW_1, 0);
	if (wc < 0)
		wetuwn wc;

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		wc &= ~WAN87XX_MASK_WGMII_TXC_DWY_EN;
		wc &= ~WAN87XX_MASK_WGMII_WXC_DWY_EN;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		wc |= WAN87XX_MASK_WGMII_TXC_DWY_EN;
		wc |= WAN87XX_MASK_WGMII_WXC_DWY_EN;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		wc &= ~WAN87XX_MASK_WGMII_TXC_DWY_EN;
		wc |= WAN87XX_MASK_WGMII_WXC_DWY_EN;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wc |= WAN87XX_MASK_WGMII_TXC_DWY_EN;
		wc &= ~WAN87XX_MASK_WGMII_WXC_DWY_EN;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
			   PHYACC_ATTW_BANK_MISC, WAN87XX_CTWW_1, wc);
}

static int wan87xx_phy_init_cmd(stwuct phy_device *phydev,
				const stwuct access_eweg_vaw *cmd_seq, int cnt)
{
	int wet, i;

	fow (i = 0; i < cnt; i++) {
		if (cmd_seq[i].mode == PHYACC_ATTW_MODE_POWW &&
		    cmd_seq[i].bank == PHYACC_ATTW_BANK_SMI) {
			wet = access_smi_poww_timeout(phydev,
						      cmd_seq[i].offset,
						      cmd_seq[i].vaw,
						      cmd_seq[i].mask);
		} ewse {
			wet = access_eweg(phydev, cmd_seq[i].mode,
					  cmd_seq[i].bank, cmd_seq[i].offset,
					  cmd_seq[i].vaw);
		}
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wet;
}

static int wan87xx_phy_init(stwuct phy_device *phydev)
{
	static const stwuct access_eweg_vaw hw_init[] = {
		/* TXPD/TXAMP6 Configs */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_AFE,
		  T1_AFE_POWT_CFG1_WEG,       0x002D,  0 },
		/* HW_Init Hi and Fowce_ED */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_SMI,
		  T1_POWEW_DOWN_CONTWOW_WEG,  0x0308,  0 },
	};

	static const stwuct access_eweg_vaw swave_init[] = {
		/* Equawizew Fuww Dupwex Fweeze - T1 Swave */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_EQ_FD_STG1_FWZ_CFG,     0x0002,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_EQ_FD_STG2_FWZ_CFG,     0x0002,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_EQ_FD_STG3_FWZ_CFG,     0x0002,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_EQ_FD_STG4_FWZ_CFG,     0x0002,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_EQ_WT_FD_WCK_FWZ_CFG,    0x0002,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_PST_EQ_WCK_STG1_FWZ_CFG, 0x0002,  0 },
	};

	static const stwuct access_eweg_vaw phy_init[] = {
		/* Swave Fuww Dupwex Muwti Configs */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_SWV_FD_MUWT_CFG_WEG,     0x0D53,  0 },
		/* CDW Pwe and Post Wock Configs */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_CDW_CFG_PWE_WOCK_WEG,    0x0AB2,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_CDW_CFG_POST_WOCK_WEG,   0x0AB3,  0 },
		/* Wock Stage 2-3 Muwti Factow Config */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_WCK_STG2_MUFACT_CFG_WEG, 0x0AEA,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_WCK_STG3_MUFACT_CFG_WEG, 0x0AEB,  0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_POST_WCK_MUFACT_CFG_WEG, 0x0AEB,  0 },
		/* Pointew deway */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WX_FIFO_CFG_WEG, 0x1C00, 0 },
		/* Tx iiw edits */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1000, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1861, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1061, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1922, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1122, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1983, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1183, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1944, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1144, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x18c5, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x10c5, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1846, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1046, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1807, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1007, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1808, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1008, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1809, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1009, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180A, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100A, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180B, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100B, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180C, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100C, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180D, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100D, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180E, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100E, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x180F, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x100F, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1810, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1010, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1811, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1011, 0 },
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_TX_WPF_FIW_CFG_WEG, 0x1000, 0 },
		/* Setup SQI measuwement */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_COEF_CWK_PWW_DN_CFG,	0x16d6, 0 },
		/* SQI enabwe */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_SQI_CONFIG_WEG,		0x9572, 0 },
		/* SQI sewect mode 5 */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_SQI_CONFIG2_WEG,		0x0001, 0 },
		/* Thwows the fiwst SQI weading */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP,
		  T1_COEF_WW_CTW_CFG,		0x0301,	0 },
		{ PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_DSP,
		  T1_DCQ_SQI_WEG,		0,	0 },
		/* Fwag WPS and WUW as idwe ewwows */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_SMI,
		  T1_MDIO_CONTWOW2_WEG,		0x0014, 0 },
		/* HW_Init toggwe, undo fowce ED, TXPD off */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_SMI,
		  T1_POWEW_DOWN_CONTWOW_WEG,	0x0200, 0 },
		/* Weset PCS to twiggew hawdwawe initiawization */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_SMI,
		  T1_MDIO_CONTWOW2_WEG,		0x0094, 0 },
		/* Poww tiww Hawdwawe is initiawized */
		{ PHYACC_ATTW_MODE_POWW, PHYACC_ATTW_BANK_SMI,
		  T1_MDIO_CONTWOW2_WEG,		0x0080, 0 },
		/* Tx AMP - 0x06  */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_AFE,
		  T1_AFE_POWT_CFG1_WEG,		0x000C, 0 },
		/* Wead INTEWWUPT_SOUWCE Wegistew */
		{ PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_SMI,
		  T1_INTEWWUPT_SOUWCE_WEG,	0,	0 },
		/* Wead INTEWWUPT_SOUWCE Wegistew */
		{ PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_MISC,
		  T1_INTEWWUPT2_SOUWCE_WEG,	0,	0 },
		/* HW_Init Hi */
		{ PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_SMI,
		  T1_POWEW_DOWN_CONTWOW_WEG,	0x0300, 0 },
	};
	int wc;

	/* phy Soft weset */
	wc = genphy_soft_weset(phydev);
	if (wc < 0)
		wetuwn wc;

	/* PHY Initiawization */
	wc = wan87xx_phy_init_cmd(phydev, hw_init, AWWAY_SIZE(hw_init));
	if (wc < 0)
		wetuwn wc;

	wc = genphy_wead_mastew_swave(phydev);
	if (wc)
		wetuwn wc;

	/* The fowwowing squence needs to wun onwy if phydev is in
	 * swave mode.
	 */
	if (phydev->mastew_swave_state == MASTEW_SWAVE_STATE_SWAVE) {
		wc = wan87xx_phy_init_cmd(phydev, swave_init,
					  AWWAY_SIZE(swave_init));
		if (wc < 0)
			wetuwn wc;
	}

	wc = wan87xx_phy_init_cmd(phydev, phy_init, AWWAY_SIZE(phy_init));
	if (wc < 0)
		wetuwn wc;

	wetuwn wan87xx_config_wgmii_deway(phydev);
}

static int wan87xx_phy_config_intw(stwuct phy_device *phydev)
{
	int wc, vaw = 0;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		/* cweaw aww intewwupt */
		wc = phy_wwite(phydev, WAN87XX_INTEWWUPT_MASK, vaw);
		if (wc < 0)
			wetuwn wc;

		wc = phy_wead(phydev, WAN87XX_INTEWWUPT_SOUWCE);
		if (wc < 0)
			wetuwn wc;

		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
				 PHYACC_ATTW_BANK_MISC,
				 WAN87XX_INTEWWUPT_MASK_2, vaw);
		if (wc < 0)
			wetuwn wc;

		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
				 PHYACC_ATTW_BANK_MISC,
				 WAN87XX_INTEWWUPT_SOUWCE_2, 0);
		if (wc < 0)
			wetuwn wc;

		/* enabwe wink down and comm weady intewwupt */
		vaw = WAN87XX_MASK_WINK_DOWN;
		wc = phy_wwite(phydev, WAN87XX_INTEWWUPT_MASK, vaw);
		if (wc < 0)
			wetuwn wc;

		vaw = WAN87XX_MASK_COMM_WDY;
		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
				 PHYACC_ATTW_BANK_MISC,
				 WAN87XX_INTEWWUPT_MASK_2, vaw);
	} ewse {
		wc = phy_wwite(phydev, WAN87XX_INTEWWUPT_MASK, vaw);
		if (wc < 0)
			wetuwn wc;

		wc = phy_wead(phydev, WAN87XX_INTEWWUPT_SOUWCE);
		if (wc < 0)
			wetuwn wc;

		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
				 PHYACC_ATTW_BANK_MISC,
				 WAN87XX_INTEWWUPT_MASK_2, vaw);
		if (wc < 0)
			wetuwn wc;

		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
				 PHYACC_ATTW_BANK_MISC,
				 WAN87XX_INTEWWUPT_SOUWCE_2, 0);
	}

	wetuwn wc < 0 ? wc : 0;
}

static iwqwetuwn_t wan87xx_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status  = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
				  PHYACC_ATTW_BANK_MISC,
				  WAN87XX_INTEWWUPT_SOUWCE_2, 0);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	iwq_status = phy_wead(phydev, WAN87XX_INTEWWUPT_SOUWCE);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (iwq_status == 0)
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int wan87xx_config_init(stwuct phy_device *phydev)
{
	int wc = wan87xx_phy_init(phydev);

	wetuwn wc < 0 ? wc : 0;
}

static int micwochip_cabwe_test_stawt_common(stwuct phy_device *phydev)
{
	int bmcw, bmsw, wet;

	/* If auto-negotiation is enabwed, but not compwete, the cabwe
	 * test nevew compwetes. So disabwe auto-neg.
	 */
	bmcw = phy_wead(phydev, MII_BMCW);
	if (bmcw < 0)
		wetuwn bmcw;

	bmsw = phy_wead(phydev, MII_BMSW);

	if (bmsw < 0)
		wetuwn bmsw;

	if (bmcw & BMCW_ANENABWE) {
		wet =  phy_modify(phydev, MII_BMCW, BMCW_ANENABWE, 0);
		if (wet < 0)
			wetuwn wet;
		wet = genphy_soft_weset(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	/* If the wink is up, awwow it some time to go down */
	if (bmsw & BMSW_WSTATUS)
		msweep(1500);

	wetuwn 0;
}

static int wan87xx_cabwe_test_stawt(stwuct phy_device *phydev)
{
	static const stwuct access_eweg_vaw cabwe_test[] = {
		/* min wait */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 93,
		 0, 0},
		/* max wait */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 94,
		 10, 0},
		/* puwse cycwe */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 95,
		 90, 0},
		/* cabwe diag thwesh */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 92,
		 60, 0},
		/* max gain */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 79,
		 31, 0},
		/* cwock awign fow each itewation */
		{PHYACC_ATTW_MODE_MODIFY, PHYACC_ATTW_BANK_DSP, 55,
		 0, 0x0038},
		/* max cycwe wait config */
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 94,
		 70, 0},
		/* stawt cabwe diag*/
		{PHYACC_ATTW_MODE_WWITE, PHYACC_ATTW_BANK_DSP, 90,
		 1, 0},
	};
	int wc, i;

	wc = micwochip_cabwe_test_stawt_common(phydev);
	if (wc < 0)
		wetuwn wc;

	/* stawt cabwe diag */
	/* check if pawt is awive - if not, wetuwn diagnostic ewwow */
	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_SMI,
			 0x00, 0);
	if (wc < 0)
		wetuwn wc;

	/* mastew/swave specific configs */
	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_SMI,
			 0x0A, 0);
	if (wc < 0)
		wetuwn wc;

	if ((wc & 0x4000) != 0x4000) {
		/* DUT is Swave */
		wc = access_eweg_modify_changed(phydev, PHYACC_ATTW_BANK_AFE,
						0x0E, 0x5, 0x7);
		if (wc < 0)
			wetuwn wc;
		wc = access_eweg_modify_changed(phydev, PHYACC_ATTW_BANK_SMI,
						0x1A, 0x8, 0x8);
		if (wc < 0)
			wetuwn wc;
	} ewse {
		/* DUT is Mastew */
		wc = access_eweg_modify_changed(phydev, PHYACC_ATTW_BANK_SMI,
						0x10, 0x8, 0x40);
		if (wc < 0)
			wetuwn wc;
	}

	fow (i = 0; i < AWWAY_SIZE(cabwe_test); i++) {
		if (cabwe_test[i].mode == PHYACC_ATTW_MODE_MODIFY) {
			wc = access_eweg_modify_changed(phydev,
							cabwe_test[i].bank,
							cabwe_test[i].offset,
							cabwe_test[i].vaw,
							cabwe_test[i].mask);
			/* wait 50ms */
			msweep(50);
		} ewse {
			wc = access_eweg(phydev, cabwe_test[i].mode,
					 cabwe_test[i].bank,
					 cabwe_test[i].offset,
					 cabwe_test[i].vaw);
		}
		if (wc < 0)
			wetuwn wc;
	}
	/* cabwe diag stawted */

	wetuwn 0;
}

static int wan87xx_cabwe_test_wepowt_twans(u32 wesuwt)
{
	switch (wesuwt) {
	case WAN87XX_CABWE_TEST_OK:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OK;
	case WAN87XX_CABWE_TEST_OPEN:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_OPEN;
	case WAN87XX_CABWE_TEST_SAME_SHOWT:
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_SAME_SHOWT;
	defauwt:
		/* DIAGNOSTIC_EWWOW */
		wetuwn ETHTOOW_A_CABWE_WESUWT_CODE_UNSPEC;
	}
}

static int wan87xx_cabwe_test_wepowt(stwuct phy_device *phydev)
{
	int pos_peak_cycwe = 0, pos_peak_in_phases = 0, pos_peak_phase = 0;
	int neg_peak_cycwe = 0, neg_peak_in_phases = 0, neg_peak_phase = 0;
	int noise_mawgin = 20, time_mawgin = 89, jittew_vaw = 30;
	int min_time_diff = 96, max_time_diff = 96 + time_mawgin;
	boow fauwt = fawse, check_a = fawse, check_b = fawse;
	int gain_idx = 0, pos_peak = 0, neg_peak = 0;
	int pos_peak_time = 0, neg_peak_time = 0;
	int pos_peak_in_phases_hybwid = 0;
	int detect = -1;

	gain_idx = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
			       PHYACC_ATTW_BANK_DSP, 151, 0);
	/* wead non-hybwid wesuwts */
	pos_peak = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
			       PHYACC_ATTW_BANK_DSP, 153, 0);
	neg_peak = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
			       PHYACC_ATTW_BANK_DSP, 154, 0);
	pos_peak_time = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
				    PHYACC_ATTW_BANK_DSP, 156, 0);
	neg_peak_time = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
				    PHYACC_ATTW_BANK_DSP, 157, 0);

	pos_peak_cycwe = (pos_peak_time >> 7) & 0x7F;
	/* cawcuwate non-hybwid vawues */
	pos_peak_phase = pos_peak_time & 0x7F;
	pos_peak_in_phases = (pos_peak_cycwe * 96) + pos_peak_phase;
	neg_peak_cycwe = (neg_peak_time >> 7) & 0x7F;
	neg_peak_phase = neg_peak_time & 0x7F;
	neg_peak_in_phases = (neg_peak_cycwe * 96) + neg_peak_phase;

	/* pwocess vawues */
	check_a =
		((pos_peak_in_phases - neg_peak_in_phases) >= min_time_diff) &&
		((pos_peak_in_phases - neg_peak_in_phases) < max_time_diff) &&
		pos_peak_in_phases_hybwid < pos_peak_in_phases &&
		(pos_peak_in_phases_hybwid < (neg_peak_in_phases + jittew_vaw));
	check_b =
		((neg_peak_in_phases - pos_peak_in_phases) >= min_time_diff) &&
		((neg_peak_in_phases - pos_peak_in_phases) < max_time_diff) &&
		pos_peak_in_phases_hybwid < neg_peak_in_phases &&
		(pos_peak_in_phases_hybwid < (pos_peak_in_phases + jittew_vaw));

	if (pos_peak_in_phases > neg_peak_in_phases && check_a)
		detect = 2;
	ewse if ((neg_peak_in_phases > pos_peak_in_phases) && check_b)
		detect = 1;

	if (pos_peak > noise_mawgin && neg_peak > noise_mawgin &&
	    gain_idx >= 0) {
		if (detect == 1 || detect == 2)
			fauwt = twue;
	}

	if (!fauwt)
		detect = 0;

	ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
				wan87xx_cabwe_test_wepowt_twans(detect));

	wetuwn 0;
}

static int wan87xx_cabwe_test_get_status(stwuct phy_device *phydev,
					 boow *finished)
{
	int wc = 0;

	*finished = fawse;

	/* check if cabwe diag was finished */
	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD, PHYACC_ATTW_BANK_DSP,
			 90, 0);
	if (wc < 0)
		wetuwn wc;

	if ((wc & 2) == 2) {
		/* stop cabwe diag*/
		wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
				 PHYACC_ATTW_BANK_DSP,
				 90, 0);
		if (wc < 0)
			wetuwn wc;

		*finished = twue;

		wetuwn wan87xx_cabwe_test_wepowt(phydev);
	}

	wetuwn 0;
}

static int wan87xx_wead_status(stwuct phy_device *phydev)
{
	int wc = 0;

	wc = phy_wead(phydev, T1_MODE_STAT_WEG);
	if (wc < 0)
		wetuwn wc;

	if (wc & T1_WINK_UP_MSK)
		phydev->wink = 1;
	ewse
		phydev->wink = 0;

	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	wc = genphy_wead_mastew_swave(phydev);
	if (wc < 0)
		wetuwn wc;

	wc = genphy_wead_status_fixed(phydev);
	if (wc < 0)
		wetuwn wc;

	wetuwn wc;
}

static int wan87xx_config_aneg(stwuct phy_device *phydev)
{
	u16 ctw = 0;
	int wet;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		ctw |= CTW1000_AS_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		wetuwn 0;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = phy_modify_changed(phydev, MII_CTWW1000, CTW1000_AS_MASTEW, ctw);
	if (wet == 1)
		wetuwn phy_init_hw(phydev);

	wetuwn wet;
}

static int wan87xx_get_sqi(stwuct phy_device *phydev)
{
	u8 sqi_vawue = 0;
	int wc;

	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WWITE,
			 PHYACC_ATTW_BANK_DSP, T1_COEF_WW_CTW_CFG, 0x0301);
	if (wc < 0)
		wetuwn wc;

	wc = access_eweg(phydev, PHYACC_ATTW_MODE_WEAD,
			 PHYACC_ATTW_BANK_DSP, T1_DCQ_SQI_WEG, 0x0);
	if (wc < 0)
		wetuwn wc;

	sqi_vawue = FIEWD_GET(T1_DCQ_SQI_MSK, wc);

	wetuwn sqi_vawue;
}

static int wan87xx_get_sqi_max(stwuct phy_device *phydev)
{
	wetuwn WAN87XX_MAX_SQI;
}

static stwuct phy_dwivew micwochip_t1_phy_dwivew[] = {
	{
		PHY_ID_MATCH_MODEW(PHY_ID_WAN87XX),
		.name           = "Micwochip WAN87xx T1",
		.fwags          = PHY_POWW_CABWE_TEST,
		.featuwes       = PHY_BASIC_T1_FEATUWES,
		.config_init	= wan87xx_config_init,
		.config_intw    = wan87xx_phy_config_intw,
		.handwe_intewwupt = wan87xx_handwe_intewwupt,
		.suspend        = genphy_suspend,
		.wesume         = genphy_wesume,
		.config_aneg    = wan87xx_config_aneg,
		.wead_status	= wan87xx_wead_status,
		.get_sqi	= wan87xx_get_sqi,
		.get_sqi_max	= wan87xx_get_sqi_max,
		.cabwe_test_stawt = wan87xx_cabwe_test_stawt,
		.cabwe_test_get_status = wan87xx_cabwe_test_get_status,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_WAN937X),
		.name		= "Micwochip WAN937x T1",
		.fwags          = PHY_POWW_CABWE_TEST,
		.featuwes	= PHY_BASIC_T1_FEATUWES,
		.config_init	= wan87xx_config_init,
		.config_intw    = wan87xx_phy_config_intw,
		.handwe_intewwupt = wan87xx_handwe_intewwupt,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg    = wan87xx_config_aneg,
		.wead_status	= wan87xx_wead_status,
		.get_sqi	= wan87xx_get_sqi,
		.get_sqi_max	= wan87xx_get_sqi_max,
		.cabwe_test_stawt = wan87xx_cabwe_test_stawt,
		.cabwe_test_get_status = wan87xx_cabwe_test_get_status,
	}
};

moduwe_phy_dwivew(micwochip_t1_phy_dwivew);

static stwuct mdio_device_id __maybe_unused micwochip_t1_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_WAN87XX) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_WAN937X) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, micwochip_t1_tbw);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
