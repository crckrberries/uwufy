// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 STMicwoewectwonics
 *
 * STMicwoewectwonics PHY dwivew MiPHY28wp (fow SoC STiH407).
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>
#incwude <winux/phy/phy.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude <dt-bindings/phy/phy.h>

/* MiPHY wegistews */
#define MIPHY_CONF_WESET		0x00
#define WST_APPWI_SW		BIT(0)
#define WST_CONF_SW		BIT(1)
#define WST_MACWO_SW		BIT(2)

#define MIPHY_WESET			0x01
#define WST_PWW_SW		BIT(0)
#define WST_COMP_SW		BIT(2)

#define MIPHY_STATUS_1			0x02
#define PHY_WDY			BIT(0)
#define HFC_WDY			BIT(1)
#define HFC_PWW			BIT(2)

#define MIPHY_CONTWOW			0x04
#define TEWM_EN_SW		BIT(2)
#define DIS_WINK_WST		BIT(3)
#define AUTO_WST_WX		BIT(4)
#define PX_WX_POW		BIT(5)

#define MIPHY_BOUNDAWY_SEW		0x0a
#define TX_SEW			BIT(6)
#define SSC_SEW			BIT(4)
#define GENSEW_SEW		BIT(0)

#define MIPHY_BOUNDAWY_1		0x0b
#define MIPHY_BOUNDAWY_2		0x0c
#define SSC_EN_SW		BIT(2)

#define MIPHY_PWW_CWKWEF_FWEQ		0x0d
#define MIPHY_SPEED			0x0e
#define TX_SPDSEW_80DEC		0
#define TX_SPDSEW_40DEC		1
#define TX_SPDSEW_20DEC		2
#define WX_SPDSEW_80DEC		0
#define WX_SPDSEW_40DEC		(1 << 2)
#define WX_SPDSEW_20DEC		(2 << 2)

#define MIPHY_CONF			0x0f
#define MIPHY_CTWW_TEST_SEW		0x20
#define MIPHY_CTWW_TEST_1		0x21
#define MIPHY_CTWW_TEST_2		0x22
#define MIPHY_CTWW_TEST_3		0x23
#define MIPHY_CTWW_TEST_4		0x24
#define MIPHY_FEEDBACK_TEST		0x25
#define MIPHY_DEBUG_BUS			0x26
#define MIPHY_DEBUG_STATUS_MSB		0x27
#define MIPHY_DEBUG_STATUS_WSB		0x28
#define MIPHY_PWW_WAIW_1		0x29
#define MIPHY_PWW_WAIW_2		0x2a
#define MIPHY_SYNCHAW_CONTWOW		0x30

#define MIPHY_COMP_FSM_1		0x3a
#define COMP_STAWT		BIT(6)

#define MIPHY_COMP_FSM_6		0x3f
#define COMP_DONE		BIT(7)

#define MIPHY_COMP_POSTP		0x42
#define MIPHY_TX_CTWW_1			0x49
#define TX_WEG_STEP_0V		0
#define TX_WEG_STEP_P_25MV	1
#define TX_WEG_STEP_P_50MV	2
#define TX_WEG_STEP_N_25MV	7
#define TX_WEG_STEP_N_50MV	6
#define TX_WEG_STEP_N_75MV	5

#define MIPHY_TX_CTWW_2			0x4a
#define TX_SWEW_SW_40_PS	0
#define TX_SWEW_SW_80_PS	1
#define TX_SWEW_SW_120_PS	2

#define MIPHY_TX_CTWW_3			0x4b
#define MIPHY_TX_CAW_MAN		0x4e
#define TX_SWEW_CAW_MAN_EN	BIT(0)

#define MIPHY_TST_BIAS_BOOST_2		0x62
#define MIPHY_BIAS_BOOST_1		0x63
#define MIPHY_BIAS_BOOST_2		0x64
#define MIPHY_WX_DESBUFF_FDB_2		0x67
#define MIPHY_WX_DESBUFF_FDB_3		0x68
#define MIPHY_SIGDET_COMPENS1		0x69
#define MIPHY_SIGDET_COMPENS2		0x6a
#define MIPHY_JITTEW_PEWIOD		0x6b
#define MIPHY_JITTEW_AMPWITUDE_1	0x6c
#define MIPHY_JITTEW_AMPWITUDE_2	0x6d
#define MIPHY_JITTEW_AMPWITUDE_3	0x6e
#define MIPHY_WX_K_GAIN			0x78
#define MIPHY_WX_BUFFEW_CTWW		0x7a
#define VGA_GAIN		BIT(0)
#define EQ_DC_GAIN		BIT(2)
#define EQ_BOOST_GAIN		BIT(3)

#define MIPHY_WX_VGA_GAIN		0x7b
#define MIPHY_WX_EQU_GAIN_1		0x7f
#define MIPHY_WX_EQU_GAIN_2		0x80
#define MIPHY_WX_EQU_GAIN_3		0x81
#define MIPHY_WX_CAW_CTWW_1		0x97
#define MIPHY_WX_CAW_CTWW_2		0x98

#define MIPHY_WX_CAW_OFFSET_CTWW	0x99
#define CAW_OFFSET_VGA_64	(0x03 << 0)
#define CAW_OFFSET_THWESHOWD_64	(0x03 << 2)
#define VGA_OFFSET_POWAWITY	BIT(4)
#define OFFSET_COMPENSATION_EN	BIT(6)

#define MIPHY_WX_CAW_VGA_STEP		0x9a
#define MIPHY_WX_CAW_EYE_MIN		0x9d
#define MIPHY_WX_CAW_OPT_WENGTH		0x9f
#define MIPHY_WX_WOCK_CTWW_1		0xc1
#define MIPHY_WX_WOCK_SETTINGS_OPT	0xc2
#define MIPHY_WX_WOCK_STEP		0xc4

#define MIPHY_WX_SIGDET_SWEEP_OA	0xc9
#define MIPHY_WX_SIGDET_SWEEP_SEW	0xca
#define MIPHY_WX_SIGDET_WAIT_SEW	0xcb
#define MIPHY_WX_SIGDET_DATA_SEW	0xcc
#define EN_UWTWA_WOW_POWEW	BIT(0)
#define EN_FIWST_HAWF		BIT(1)
#define EN_SECOND_HAWF		BIT(2)
#define EN_DIGIT_SIGNAW_CHECK	BIT(3)

#define MIPHY_WX_POWEW_CTWW_1		0xcd
#define MIPHY_WX_POWEW_CTWW_2		0xce
#define MIPHY_PWW_CAWSET_CTWW		0xd3
#define MIPHY_PWW_CAWSET_1		0xd4
#define MIPHY_PWW_CAWSET_2		0xd5
#define MIPHY_PWW_CAWSET_3		0xd6
#define MIPHY_PWW_CAWSET_4		0xd7
#define MIPHY_PWW_SBW_1			0xe3
#define SET_NEW_CHANGE		BIT(1)

#define MIPHY_PWW_SBW_2			0xe4
#define MIPHY_PWW_SBW_3			0xe5
#define MIPHY_PWW_SBW_4			0xe6
#define MIPHY_PWW_COMMON_MISC_2		0xe9
#define STAWT_ACT_FIWT		BIT(6)

#define MIPHY_PWW_SPAWEIN		0xeb

/*
 * On STiH407 the gwue wogic can be diffewent among MiPHY devices; fow exampwe:
 * MiPHY0: OSC_FOWCE_EXT means:
 *  0: 30MHz cwystaw cwk - 1: 100MHz ext cwk wouted thwough MiPHY1
 * MiPHY1: OSC_FOWCE_EXT means:
 *  1: 30MHz cwystaw cwk - 0: 100MHz ext cwk wouted thwough MiPHY1
 * Some devices have not the possibiwity to check if the osc is weady.
 */
#define MIPHY_OSC_FOWCE_EXT	BIT(3)
#define MIPHY_OSC_WDY		BIT(5)

#define MIPHY_CTWW_MASK		0x0f
#define MIPHY_CTWW_DEFAUWT	0
#define MIPHY_CTWW_SYNC_D_EN	BIT(2)

/* SATA / PCIe defines */
#define SATA_CTWW_MASK		0x07
#define PCIE_CTWW_MASK		0xff
#define SATA_CTWW_SEWECT_SATA	1
#define SATA_CTWW_SEWECT_PCIE	0
#define SYSCFG_PCIE_PCIE_VAW	0x80
#define SATA_SPDMODE		1

#define MIPHY_SATA_BANK_NB	3
#define MIPHY_PCIE_BANK_NB	2

enum {
	SYSCFG_CTWW,
	SYSCFG_STATUS,
	SYSCFG_PCI,
	SYSCFG_SATA,
	SYSCFG_WEG_MAX,
};

stwuct miphy28wp_phy {
	stwuct phy *phy;
	stwuct miphy28wp_dev *phydev;
	void __iomem *base;
	void __iomem *pipebase;

	boow osc_fowce_ext;
	boow osc_wdy;
	boow px_wx_pow_inv;
	boow ssc;
	boow tx_impedance;

	stwuct weset_contwow *miphy_wst;

	u32 sata_gen;

	/* Sysconfig wegistews offsets needed to configuwe the device */
	u32 syscfg_weg[SYSCFG_WEG_MAX];
	u8 type;
};

stwuct miphy28wp_dev {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex miphy_mutex;
	stwuct miphy28wp_phy **phys;
	int nphys;
};

stwuct miphy_initvaw {
	u16 weg;
	u16 vaw;
};

enum miphy_sata_gen { SATA_GEN1, SATA_GEN2, SATA_GEN3 };

static chaw *PHY_TYPE_name[] = { "sata-up", "pcie-up", "", "usb3-up" };

stwuct pww_watio {
	int cwk_wef;
	int cawset_1;
	int cawset_2;
	int cawset_3;
	int cawset_4;
	int caw_ctww;
};

static stwuct pww_watio sata_pww_watio = {
	.cwk_wef = 0x1e,
	.cawset_1 = 0xc8,
	.cawset_2 = 0x00,
	.cawset_3 = 0x00,
	.cawset_4 = 0x00,
	.caw_ctww = 0x00,
};

static stwuct pww_watio pcie_pww_watio = {
	.cwk_wef = 0x1e,
	.cawset_1 = 0xa6,
	.cawset_2 = 0xaa,
	.cawset_3 = 0xaa,
	.cawset_4 = 0x00,
	.caw_ctww = 0x00,
};

static stwuct pww_watio usb3_pww_watio = {
	.cwk_wef = 0x1e,
	.cawset_1 = 0xa6,
	.cawset_2 = 0xaa,
	.cawset_3 = 0xaa,
	.cawset_4 = 0x04,
	.caw_ctww = 0x00,
};

stwuct miphy28wp_pww_gen {
	int bank;
	int speed;
	int bias_boost_1;
	int bias_boost_2;
	int tx_ctww_1;
	int tx_ctww_2;
	int tx_ctww_3;
	int wx_k_gain;
	int wx_vga_gain;
	int wx_equ_gain_1;
	int wx_equ_gain_2;
	int wx_equ_gain_3;
	int wx_buff_ctww;
};

static stwuct miphy28wp_pww_gen sata_pww_gen[] = {
	{
		.bank		= 0x00,
		.speed		= TX_SPDSEW_80DEC | WX_SPDSEW_80DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctww_2	= 0x53,
		.tx_ctww_3	= 0x00,
		.wx_buff_ctww	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.wx_vga_gain	= 0x00,
		.wx_equ_gain_1	= 0x7d,
		.wx_equ_gain_2	= 0x56,
		.wx_equ_gain_3	= 0x00,
	},
	{
		.bank		= 0x01,
		.speed		= TX_SPDSEW_40DEC | WX_SPDSEW_40DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctww_2	= 0x72,
		.tx_ctww_3	= 0x20,
		.wx_buff_ctww	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.wx_vga_gain	= 0x00,
		.wx_equ_gain_1	= 0x7d,
		.wx_equ_gain_2	= 0x56,
		.wx_equ_gain_3	= 0x00,
	},
	{
		.bank		= 0x02,
		.speed		= TX_SPDSEW_20DEC | WX_SPDSEW_20DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xae,
		.tx_ctww_2	= 0xc0,
		.tx_ctww_3	= 0x20,
		.wx_buff_ctww	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.wx_vga_gain	= 0x00,
		.wx_equ_gain_1	= 0x7d,
		.wx_equ_gain_2	= 0x56,
		.wx_equ_gain_3	= 0x00,
	},
};

static stwuct miphy28wp_pww_gen pcie_pww_gen[] = {
	{
		.bank		= 0x00,
		.speed		= TX_SPDSEW_40DEC | WX_SPDSEW_40DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xa5,
		.tx_ctww_1	= TX_WEG_STEP_N_25MV,
		.tx_ctww_2	= 0x71,
		.tx_ctww_3	= 0x60,
		.wx_k_gain	= 0x98,
		.wx_buff_ctww	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.wx_vga_gain	= 0x00,
		.wx_equ_gain_1	= 0x79,
		.wx_equ_gain_2	= 0x56,
	},
	{
		.bank		= 0x01,
		.speed		= TX_SPDSEW_20DEC | WX_SPDSEW_20DEC,
		.bias_boost_1	= 0x00,
		.bias_boost_2	= 0xa5,
		.tx_ctww_1	= TX_WEG_STEP_N_25MV,
		.tx_ctww_2	= 0x70,
		.tx_ctww_3	= 0x60,
		.wx_k_gain	= 0xcc,
		.wx_buff_ctww	= EQ_BOOST_GAIN | EQ_DC_GAIN | VGA_GAIN,
		.wx_vga_gain	= 0x00,
		.wx_equ_gain_1	= 0x78,
		.wx_equ_gain_2	= 0x07,
	},
};

static inwine void miphy28wp_set_weset(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* Putting Macwo in weset */
	wwiteb_wewaxed(WST_APPWI_SW, base + MIPHY_CONF_WESET);

	vaw = WST_APPWI_SW | WST_CONF_SW;
	wwiteb_wewaxed(vaw, base + MIPHY_CONF_WESET);

	wwiteb_wewaxed(WST_APPWI_SW, base + MIPHY_CONF_WESET);

	/* Bwinging the MIPHY-CPU wegistews out of weset */
	if (miphy_phy->type == PHY_TYPE_PCIE) {
		vaw = AUTO_WST_WX | TEWM_EN_SW;
		wwiteb_wewaxed(vaw, base + MIPHY_CONTWOW);
	} ewse {
		vaw = AUTO_WST_WX | TEWM_EN_SW | DIS_WINK_WST;
		wwiteb_wewaxed(vaw, base + MIPHY_CONTWOW);
	}
}

static inwine void miphy28wp_pww_cawibwation(stwuct miphy28wp_phy *miphy_phy,
		stwuct pww_watio *pww_watio)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* Appwying PWW Settings */
	wwiteb_wewaxed(0x1d, base + MIPHY_PWW_SPAWEIN);
	wwiteb_wewaxed(pww_watio->cwk_wef, base + MIPHY_PWW_CWKWEF_FWEQ);

	/* PWW Watio */
	wwiteb_wewaxed(pww_watio->cawset_1, base + MIPHY_PWW_CAWSET_1);
	wwiteb_wewaxed(pww_watio->cawset_2, base + MIPHY_PWW_CAWSET_2);
	wwiteb_wewaxed(pww_watio->cawset_3, base + MIPHY_PWW_CAWSET_3);
	wwiteb_wewaxed(pww_watio->cawset_4, base + MIPHY_PWW_CAWSET_4);
	wwiteb_wewaxed(pww_watio->caw_ctww, base + MIPHY_PWW_CAWSET_CTWW);

	wwiteb_wewaxed(TX_SEW, base + MIPHY_BOUNDAWY_SEW);

	vaw = (0x68 << 1) | TX_SWEW_CAW_MAN_EN;
	wwiteb_wewaxed(vaw, base + MIPHY_TX_CAW_MAN);

	vaw = VGA_OFFSET_POWAWITY | CAW_OFFSET_THWESHOWD_64 | CAW_OFFSET_VGA_64;

	if (miphy_phy->type != PHY_TYPE_SATA)
		vaw |= OFFSET_COMPENSATION_EN;

	wwiteb_wewaxed(vaw, base + MIPHY_WX_CAW_OFFSET_CTWW);

	if (miphy_phy->type == PHY_TYPE_USB3) {
		wwiteb_wewaxed(0x00, base + MIPHY_CONF);
		wwiteb_wewaxed(0x70, base + MIPHY_WX_WOCK_STEP);
		wwiteb_wewaxed(EN_FIWST_HAWF, base + MIPHY_WX_SIGDET_SWEEP_OA);
		wwiteb_wewaxed(EN_FIWST_HAWF, base + MIPHY_WX_SIGDET_SWEEP_SEW);
		wwiteb_wewaxed(EN_FIWST_HAWF, base + MIPHY_WX_SIGDET_WAIT_SEW);

		vaw = EN_DIGIT_SIGNAW_CHECK | EN_FIWST_HAWF;
		wwiteb_wewaxed(vaw, base + MIPHY_WX_SIGDET_DATA_SEW);
	}

}

static inwine void miphy28wp_sata_config_gen(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sata_pww_gen); i++) {
		stwuct miphy28wp_pww_gen *gen = &sata_pww_gen[i];

		/* Banked settings */
		wwiteb_wewaxed(gen->bank, base + MIPHY_CONF);
		wwiteb_wewaxed(gen->speed, base + MIPHY_SPEED);
		wwiteb_wewaxed(gen->bias_boost_1, base + MIPHY_BIAS_BOOST_1);
		wwiteb_wewaxed(gen->bias_boost_2, base + MIPHY_BIAS_BOOST_2);

		/* TX buffew Settings */
		wwiteb_wewaxed(gen->tx_ctww_2, base + MIPHY_TX_CTWW_2);
		wwiteb_wewaxed(gen->tx_ctww_3, base + MIPHY_TX_CTWW_3);

		/* WX Buffew Settings */
		wwiteb_wewaxed(gen->wx_buff_ctww, base + MIPHY_WX_BUFFEW_CTWW);
		wwiteb_wewaxed(gen->wx_vga_gain, base + MIPHY_WX_VGA_GAIN);
		wwiteb_wewaxed(gen->wx_equ_gain_1, base + MIPHY_WX_EQU_GAIN_1);
		wwiteb_wewaxed(gen->wx_equ_gain_2, base + MIPHY_WX_EQU_GAIN_2);
		wwiteb_wewaxed(gen->wx_equ_gain_3, base + MIPHY_WX_EQU_GAIN_3);
	}
}

static inwine void miphy28wp_pcie_config_gen(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pcie_pww_gen); i++) {
		stwuct miphy28wp_pww_gen *gen = &pcie_pww_gen[i];

		/* Banked settings */
		wwiteb_wewaxed(gen->bank, base + MIPHY_CONF);
		wwiteb_wewaxed(gen->speed, base + MIPHY_SPEED);
		wwiteb_wewaxed(gen->bias_boost_1, base + MIPHY_BIAS_BOOST_1);
		wwiteb_wewaxed(gen->bias_boost_2, base + MIPHY_BIAS_BOOST_2);

		/* TX buffew Settings */
		wwiteb_wewaxed(gen->tx_ctww_1, base + MIPHY_TX_CTWW_1);
		wwiteb_wewaxed(gen->tx_ctww_2, base + MIPHY_TX_CTWW_2);
		wwiteb_wewaxed(gen->tx_ctww_3, base + MIPHY_TX_CTWW_3);

		wwiteb_wewaxed(gen->wx_k_gain, base + MIPHY_WX_K_GAIN);

		/* WX Buffew Settings */
		wwiteb_wewaxed(gen->wx_buff_ctww, base + MIPHY_WX_BUFFEW_CTWW);
		wwiteb_wewaxed(gen->wx_vga_gain, base + MIPHY_WX_VGA_GAIN);
		wwiteb_wewaxed(gen->wx_equ_gain_1, base + MIPHY_WX_EQU_GAIN_1);
		wwiteb_wewaxed(gen->wx_equ_gain_2, base + MIPHY_WX_EQU_GAIN_2);
	}
}

static inwine int miphy28wp_wait_compensation(stwuct miphy28wp_phy *miphy_phy)
{
	u8 vaw;

	/* Waiting fow Compensation to compwete */
	wetuwn weadb_wewaxed_poww_timeout(miphy_phy->base + MIPHY_COMP_FSM_6,
					  vaw, vaw & COMP_DONE, 1, 5 * USEC_PEW_SEC);
}


static inwine int miphy28wp_compensation(stwuct miphy28wp_phy *miphy_phy,
		stwuct pww_watio *pww_watio)
{
	void __iomem *base = miphy_phy->base;

	/* Poww fow HFC weady aftew weset wewease */
	/* Compensation measuwement */
	wwiteb_wewaxed(WST_PWW_SW | WST_COMP_SW, base + MIPHY_WESET);

	wwiteb_wewaxed(0x00, base + MIPHY_PWW_COMMON_MISC_2);
	wwiteb_wewaxed(pww_watio->cwk_wef, base + MIPHY_PWW_CWKWEF_FWEQ);
	wwiteb_wewaxed(COMP_STAWT, base + MIPHY_COMP_FSM_1);

	if (miphy_phy->type == PHY_TYPE_PCIE)
		wwiteb_wewaxed(WST_PWW_SW, base + MIPHY_WESET);

	wwiteb_wewaxed(0x00, base + MIPHY_WESET);
	wwiteb_wewaxed(STAWT_ACT_FIWT, base + MIPHY_PWW_COMMON_MISC_2);
	wwiteb_wewaxed(SET_NEW_CHANGE, base + MIPHY_PWW_SBW_1);

	/* TX compensation offset to we-centew TX impedance */
	wwiteb_wewaxed(0x00, base + MIPHY_COMP_POSTP);

	if (miphy_phy->type == PHY_TYPE_PCIE)
		wetuwn miphy28wp_wait_compensation(miphy_phy);

	wetuwn 0;
}

static inwine void miphy28_usb3_miphy_weset(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* MIPHY Weset */
	wwiteb_wewaxed(WST_APPWI_SW, base + MIPHY_CONF_WESET);
	wwiteb_wewaxed(0x00, base + MIPHY_CONF_WESET);
	wwiteb_wewaxed(WST_COMP_SW, base + MIPHY_WESET);

	vaw = WST_COMP_SW | WST_PWW_SW;
	wwiteb_wewaxed(vaw, base + MIPHY_WESET);

	wwiteb_wewaxed(0x00, base + MIPHY_PWW_COMMON_MISC_2);
	wwiteb_wewaxed(0x1e, base + MIPHY_PWW_CWKWEF_FWEQ);
	wwiteb_wewaxed(COMP_STAWT, base + MIPHY_COMP_FSM_1);
	wwiteb_wewaxed(WST_PWW_SW, base + MIPHY_WESET);
	wwiteb_wewaxed(0x00, base + MIPHY_WESET);
	wwiteb_wewaxed(STAWT_ACT_FIWT, base + MIPHY_PWW_COMMON_MISC_2);
	wwiteb_wewaxed(0x00, base + MIPHY_CONF);
	wwiteb_wewaxed(0x00, base + MIPHY_BOUNDAWY_1);
	wwiteb_wewaxed(0x00, base + MIPHY_TST_BIAS_BOOST_2);
	wwiteb_wewaxed(0x00, base + MIPHY_CONF);
	wwiteb_wewaxed(SET_NEW_CHANGE, base + MIPHY_PWW_SBW_1);
	wwiteb_wewaxed(0xa5, base + MIPHY_DEBUG_BUS);
	wwiteb_wewaxed(0x00, base + MIPHY_CONF);
}

static void miphy_sata_tune_ssc(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* Compensate Tx impedance to avoid out of wange vawues */
	/*
	 * Enabwe the SSC on PWW fow aww banks
	 * SSC Moduwation @ 31 KHz and 4000 ppm moduwation amp
	 */
	vaw = weadb_wewaxed(base + MIPHY_BOUNDAWY_2);
	vaw |= SSC_EN_SW;
	wwiteb_wewaxed(vaw, base + MIPHY_BOUNDAWY_2);

	vaw = weadb_wewaxed(base + MIPHY_BOUNDAWY_SEW);
	vaw |= SSC_SEW;
	wwiteb_wewaxed(vaw, base + MIPHY_BOUNDAWY_SEW);

	fow (vaw = 0; vaw < MIPHY_SATA_BANK_NB; vaw++) {
		wwiteb_wewaxed(vaw, base + MIPHY_CONF);

		/* Add vawue to each wefewence cwock cycwe  */
		/* and define the pewiod wength of the SSC */
		wwiteb_wewaxed(0x3c, base + MIPHY_PWW_SBW_2);
		wwiteb_wewaxed(0x6c, base + MIPHY_PWW_SBW_3);
		wwiteb_wewaxed(0x81, base + MIPHY_PWW_SBW_4);

		/* Cweaw any pwevious wequest */
		wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);

		/* wequests the PWW to take in account new pawametews */
		wwiteb_wewaxed(SET_NEW_CHANGE, base + MIPHY_PWW_SBW_1);

		/* To be suwe thewe is no othew pending wequests */
		wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);
	}
}

static void miphy_pcie_tune_ssc(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* Compensate Tx impedance to avoid out of wange vawues */
	/*
	 * Enabwe the SSC on PWW fow aww banks
	 * SSC Moduwation @ 31 KHz and 4000 ppm moduwation amp
	 */
	vaw = weadb_wewaxed(base + MIPHY_BOUNDAWY_2);
	vaw |= SSC_EN_SW;
	wwiteb_wewaxed(vaw, base + MIPHY_BOUNDAWY_2);

	vaw = weadb_wewaxed(base + MIPHY_BOUNDAWY_SEW);
	vaw |= SSC_SEW;
	wwiteb_wewaxed(vaw, base + MIPHY_BOUNDAWY_SEW);

	fow (vaw = 0; vaw < MIPHY_PCIE_BANK_NB; vaw++) {
		wwiteb_wewaxed(vaw, base + MIPHY_CONF);

		/* Vawidate Step component */
		wwiteb_wewaxed(0x69, base + MIPHY_PWW_SBW_3);
		wwiteb_wewaxed(0x21, base + MIPHY_PWW_SBW_4);

		/* Vawidate Pewiod component */
		wwiteb_wewaxed(0x3c, base + MIPHY_PWW_SBW_2);
		wwiteb_wewaxed(0x21, base + MIPHY_PWW_SBW_4);

		/* Cweaw any pwevious wequest */
		wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);

		/* wequests the PWW to take in account new pawametews */
		wwiteb_wewaxed(SET_NEW_CHANGE, base + MIPHY_PWW_SBW_1);

		/* To be suwe thewe is no othew pending wequests */
		wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);
	}
}

static inwine void miphy_tune_tx_impedance(stwuct miphy28wp_phy *miphy_phy)
{
	/* Compensate Tx impedance to avoid out of wange vawues */
	wwiteb_wewaxed(0x02, miphy_phy->base + MIPHY_COMP_POSTP);
}

static inwine int miphy28wp_configuwe_sata(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	int eww;
	u8 vaw;

	/* Putting Macwo in weset */
	miphy28wp_set_weset(miphy_phy);

	/* PWW cawibwation */
	miphy28wp_pww_cawibwation(miphy_phy, &sata_pww_watio);

	/* Banked settings Gen1/Gen2/Gen3 */
	miphy28wp_sata_config_gen(miphy_phy);

	/* Powew contwow */
	/* Input bwidge enabwe, manuaw input bwidge contwow */
	wwiteb_wewaxed(0x21, base + MIPHY_WX_POWEW_CTWW_1);

	/* Macwo out of weset */
	wwiteb_wewaxed(0x00, base + MIPHY_CONF_WESET);

	/* Poww fow HFC weady aftew weset wewease */
	/* Compensation measuwement */
	eww = miphy28wp_compensation(miphy_phy, &sata_pww_watio);
	if (eww)
		wetuwn eww;

	if (miphy_phy->px_wx_pow_inv) {
		/* Invewt Wx powawity */
		vaw = weadb_wewaxed(miphy_phy->base + MIPHY_CONTWOW);
		vaw |= PX_WX_POW;
		wwiteb_wewaxed(vaw, miphy_phy->base + MIPHY_CONTWOW);
	}

	if (miphy_phy->ssc)
		miphy_sata_tune_ssc(miphy_phy);

	if (miphy_phy->tx_impedance)
		miphy_tune_tx_impedance(miphy_phy);

	wetuwn 0;
}

static inwine int miphy28wp_configuwe_pcie(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	int eww;

	/* Putting Macwo in weset */
	miphy28wp_set_weset(miphy_phy);

	/* PWW cawibwation */
	miphy28wp_pww_cawibwation(miphy_phy, &pcie_pww_watio);

	/* Banked settings Gen1/Gen2 */
	miphy28wp_pcie_config_gen(miphy_phy);

	/* Powew contwow */
	/* Input bwidge enabwe, manuaw input bwidge contwow */
	wwiteb_wewaxed(0x21, base + MIPHY_WX_POWEW_CTWW_1);

	/* Macwo out of weset */
	wwiteb_wewaxed(0x00, base + MIPHY_CONF_WESET);

	/* Poww fow HFC weady aftew weset wewease */
	/* Compensation measuwement */
	eww = miphy28wp_compensation(miphy_phy, &pcie_pww_watio);
	if (eww)
		wetuwn eww;

	if (miphy_phy->ssc)
		miphy_pcie_tune_ssc(miphy_phy);

	if (miphy_phy->tx_impedance)
		miphy_tune_tx_impedance(miphy_phy);

	wetuwn 0;
}


static inwine void miphy28wp_configuwe_usb3(stwuct miphy28wp_phy *miphy_phy)
{
	void __iomem *base = miphy_phy->base;
	u8 vaw;

	/* Putting Macwo in weset */
	miphy28wp_set_weset(miphy_phy);

	/* PWW cawibwation */
	miphy28wp_pww_cawibwation(miphy_phy, &usb3_pww_watio);

	/* Wwiting The Speed Wate */
	wwiteb_wewaxed(0x00, base + MIPHY_CONF);

	vaw = WX_SPDSEW_20DEC | TX_SPDSEW_20DEC;
	wwiteb_wewaxed(vaw, base + MIPHY_SPEED);

	/* WX Channew compensation and cawibwation */
	wwiteb_wewaxed(0x1c, base + MIPHY_WX_WOCK_SETTINGS_OPT);
	wwiteb_wewaxed(0x51, base + MIPHY_WX_CAW_CTWW_1);
	wwiteb_wewaxed(0x70, base + MIPHY_WX_CAW_CTWW_2);

	vaw = OFFSET_COMPENSATION_EN | VGA_OFFSET_POWAWITY |
	      CAW_OFFSET_THWESHOWD_64 | CAW_OFFSET_VGA_64;
	wwiteb_wewaxed(vaw, base + MIPHY_WX_CAW_OFFSET_CTWW);
	wwiteb_wewaxed(0x22, base + MIPHY_WX_CAW_VGA_STEP);
	wwiteb_wewaxed(0x0e, base + MIPHY_WX_CAW_OPT_WENGTH);

	vaw = EQ_DC_GAIN | VGA_GAIN;
	wwiteb_wewaxed(vaw, base + MIPHY_WX_BUFFEW_CTWW);
	wwiteb_wewaxed(0x78, base + MIPHY_WX_EQU_GAIN_1);
	wwiteb_wewaxed(0x1b, base + MIPHY_SYNCHAW_CONTWOW);

	/* TX compensation offset to we-centew TX impedance */
	wwiteb_wewaxed(0x02, base + MIPHY_COMP_POSTP);

	/* Enabwe GENSEW_SEW and SSC */
	/* TX_SEW=0 swing pweemp fowced by pipe wegistwes */
	vaw = SSC_SEW | GENSEW_SEW;
	wwiteb_wewaxed(vaw, base + MIPHY_BOUNDAWY_SEW);

	/* MIPHY Bias boost */
	wwiteb_wewaxed(0x00, base + MIPHY_BIAS_BOOST_1);
	wwiteb_wewaxed(0xa7, base + MIPHY_BIAS_BOOST_2);

	/* SSC moduwation */
	wwiteb_wewaxed(SSC_EN_SW, base + MIPHY_BOUNDAWY_2);

	/* MIPHY TX contwow */
	wwiteb_wewaxed(0x00, base + MIPHY_CONF);

	/* Vawidate Step component */
	wwiteb_wewaxed(0x5a, base + MIPHY_PWW_SBW_3);
	wwiteb_wewaxed(0xa0, base + MIPHY_PWW_SBW_4);

	/* Vawidate Pewiod component */
	wwiteb_wewaxed(0x3c, base + MIPHY_PWW_SBW_2);
	wwiteb_wewaxed(0xa1, base + MIPHY_PWW_SBW_4);

	/* Cweaw any pwevious wequest */
	wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);

	/* wequests the PWW to take in account new pawametews */
	wwiteb_wewaxed(0x02, base + MIPHY_PWW_SBW_1);

	/* To be suwe thewe is no othew pending wequests */
	wwiteb_wewaxed(0x00, base + MIPHY_PWW_SBW_1);

	/* Wx PI contwowwew settings */
	wwiteb_wewaxed(0xca, base + MIPHY_WX_K_GAIN);

	/* MIPHY WX input bwidge contwow */
	/* INPUT_BWIDGE_EN_SW=1, manuaw input bwidge contwow[0]=1 */
	wwiteb_wewaxed(0x21, base + MIPHY_WX_POWEW_CTWW_1);
	wwiteb_wewaxed(0x29, base + MIPHY_WX_POWEW_CTWW_1);
	wwiteb_wewaxed(0x1a, base + MIPHY_WX_POWEW_CTWW_2);

	/* MIPHY Weset fow usb3 */
	miphy28_usb3_miphy_weset(miphy_phy);
}

static inwine int miphy_is_weady(stwuct miphy28wp_phy *miphy_phy)
{
	u8 mask = HFC_PWW | HFC_WDY;
	u8 vaw;

	/*
	 * Fow PCIe and USB3 check onwy that PWW and HFC awe weady
	 * Fow SATA check awso that phy is weady!
	 */
	if (miphy_phy->type == PHY_TYPE_SATA)
		mask |= PHY_WDY;

	wetuwn weadb_wewaxed_poww_timeout(miphy_phy->base + MIPHY_STATUS_1,
					  vaw, (vaw & mask) == mask, 1,
					  5 * USEC_PEW_SEC);
}

static int miphy_osc_is_weady(stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	u32 vaw;

	if (!miphy_phy->osc_wdy)
		wetuwn 0;

	if (!miphy_phy->syscfg_weg[SYSCFG_STATUS])
		wetuwn -EINVAW;

	wetuwn wegmap_wead_poww_timeout(miphy_dev->wegmap,
					miphy_phy->syscfg_weg[SYSCFG_STATUS],
					vaw, vaw & MIPHY_OSC_WDY, 1,
					5 * USEC_PEW_SEC);
}

static int miphy28wp_get_wesouwce_byname(stwuct device_node *chiwd,
					  chaw *wname, stwuct wesouwce *wes)
{
	int index;

	index = of_pwopewty_match_stwing(chiwd, "weg-names", wname);
	if (index < 0)
		wetuwn -ENODEV;

	wetuwn of_addwess_to_wesouwce(chiwd, index, wes);
}

static int miphy28wp_get_one_addw(stwuct device *dev,
				  stwuct device_node *chiwd, chaw *wname,
				  void __iomem **base)
{
	stwuct wesouwce wes;
	int wet;

	wet = miphy28wp_get_wesouwce_byname(chiwd, wname, &wes);
	if (!wet) {
		*base = devm_iowemap(dev, wes.stawt, wesouwce_size(&wes));
		if (!*base) {
			dev_eww(dev, "faiwed to iowemap %s addwess wegion\n"
					, wname);
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}

/* MiPHY weset and sysconf setup */
static int miphy28wp_setup(stwuct miphy28wp_phy *miphy_phy, u32 miphy_vaw)
{
	int eww;
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;

	if (!miphy_phy->syscfg_weg[SYSCFG_CTWW])
		wetuwn -EINVAW;

	eww = weset_contwow_assewt(miphy_phy->miphy_wst);
	if (eww) {
		dev_eww(miphy_dev->dev, "unabwe to bwing out of miphy weset\n");
		wetuwn eww;
	}

	if (miphy_phy->osc_fowce_ext)
		miphy_vaw |= MIPHY_OSC_FOWCE_EXT;

	wegmap_update_bits(miphy_dev->wegmap,
			   miphy_phy->syscfg_weg[SYSCFG_CTWW],
			   MIPHY_CTWW_MASK, miphy_vaw);

	eww = weset_contwow_deassewt(miphy_phy->miphy_wst);
	if (eww) {
		dev_eww(miphy_dev->dev, "unabwe to bwing out of miphy weset\n");
		wetuwn eww;
	}

	wetuwn miphy_osc_is_weady(miphy_phy);
}

static int miphy28wp_init_sata(stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	int eww, sata_conf = SATA_CTWW_SEWECT_SATA;

	if ((!miphy_phy->syscfg_weg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_weg[SYSCFG_PCI]) ||
			(!miphy_phy->base))
		wetuwn -EINVAW;

	dev_info(miphy_dev->dev, "sata-up mode, addw 0x%p\n", miphy_phy->base);

	/* Configuwe the gwue-wogic */
	sata_conf |= ((miphy_phy->sata_gen - SATA_GEN1) << SATA_SPDMODE);

	wegmap_update_bits(miphy_dev->wegmap,
			   miphy_phy->syscfg_weg[SYSCFG_SATA],
			   SATA_CTWW_MASK, sata_conf);

	wegmap_update_bits(miphy_dev->wegmap, miphy_phy->syscfg_weg[SYSCFG_PCI],
			   PCIE_CTWW_MASK, SATA_CTWW_SEWECT_PCIE);

	/* MiPHY path and cwocking init */
	eww = miphy28wp_setup(miphy_phy, MIPHY_CTWW_DEFAUWT);

	if (eww) {
		dev_eww(miphy_dev->dev, "SATA phy setup faiwed\n");
		wetuwn eww;
	}

	/* initiawize miphy */
	miphy28wp_configuwe_sata(miphy_phy);

	wetuwn miphy_is_weady(miphy_phy);
}

static int miphy28wp_init_pcie(stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	int eww;

	if ((!miphy_phy->syscfg_weg[SYSCFG_SATA]) ||
			(!miphy_phy->syscfg_weg[SYSCFG_PCI])
		|| (!miphy_phy->base) || (!miphy_phy->pipebase))
		wetuwn -EINVAW;

	dev_info(miphy_dev->dev, "pcie-up mode, addw 0x%p\n", miphy_phy->base);

	/* Configuwe the gwue-wogic */
	wegmap_update_bits(miphy_dev->wegmap,
			   miphy_phy->syscfg_weg[SYSCFG_SATA],
			   SATA_CTWW_MASK, SATA_CTWW_SEWECT_PCIE);

	wegmap_update_bits(miphy_dev->wegmap, miphy_phy->syscfg_weg[SYSCFG_PCI],
			   PCIE_CTWW_MASK, SYSCFG_PCIE_PCIE_VAW);

	/* MiPHY path and cwocking init */
	eww = miphy28wp_setup(miphy_phy, MIPHY_CTWW_DEFAUWT);

	if (eww) {
		dev_eww(miphy_dev->dev, "PCIe phy setup faiwed\n");
		wetuwn eww;
	}

	/* initiawize miphy */
	eww = miphy28wp_configuwe_pcie(miphy_phy);
	if (eww)
		wetuwn eww;

	/* PIPE Wwappew Configuwation */
	wwiteb_wewaxed(0x68, miphy_phy->pipebase + 0x104); /* Wise_0 */
	wwiteb_wewaxed(0x61, miphy_phy->pipebase + 0x105); /* Wise_1 */
	wwiteb_wewaxed(0x68, miphy_phy->pipebase + 0x108); /* Faww_0 */
	wwiteb_wewaxed(0x61, miphy_phy->pipebase + 0x109); /* Faww-1 */
	wwiteb_wewaxed(0x68, miphy_phy->pipebase + 0x10c); /* Thweshowd_0 */
	wwiteb_wewaxed(0x60, miphy_phy->pipebase + 0x10d); /* Thweshowd_1 */

	/* Wait fow phy_weady */
	wetuwn miphy_is_weady(miphy_phy);
}

static int miphy28wp_init_usb3(stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	int eww;

	if ((!miphy_phy->base) || (!miphy_phy->pipebase))
		wetuwn -EINVAW;

	dev_info(miphy_dev->dev, "usb3-up mode, addw 0x%p\n", miphy_phy->base);

	/* MiPHY path and cwocking init */
	eww = miphy28wp_setup(miphy_phy, MIPHY_CTWW_SYNC_D_EN);
	if (eww) {
		dev_eww(miphy_dev->dev, "USB3 phy setup faiwed\n");
		wetuwn eww;
	}

	/* initiawize miphy */
	miphy28wp_configuwe_usb3(miphy_phy);

	/* PIPE Wwappew Configuwation */
	wwiteb_wewaxed(0x68, miphy_phy->pipebase + 0x23);
	wwiteb_wewaxed(0x61, miphy_phy->pipebase + 0x24);
	wwiteb_wewaxed(0x68, miphy_phy->pipebase + 0x26);
	wwiteb_wewaxed(0x61, miphy_phy->pipebase + 0x27);
	wwiteb_wewaxed(0x18, miphy_phy->pipebase + 0x29);
	wwiteb_wewaxed(0x61, miphy_phy->pipebase + 0x2a);

	/* pipe Wwappew usb3 TX swing de-emph mawgin PWEEMPH[7:4], SWING[3:0] */
	wwiteb_wewaxed(0X67, miphy_phy->pipebase + 0x68);
	wwiteb_wewaxed(0x0d, miphy_phy->pipebase + 0x69);
	wwiteb_wewaxed(0X67, miphy_phy->pipebase + 0x6a);
	wwiteb_wewaxed(0X0d, miphy_phy->pipebase + 0x6b);
	wwiteb_wewaxed(0X67, miphy_phy->pipebase + 0x6c);
	wwiteb_wewaxed(0X0d, miphy_phy->pipebase + 0x6d);
	wwiteb_wewaxed(0X67, miphy_phy->pipebase + 0x6e);
	wwiteb_wewaxed(0X0d, miphy_phy->pipebase + 0x6f);

	wetuwn miphy_is_weady(miphy_phy);
}

static int miphy28wp_init(stwuct phy *phy)
{
	stwuct miphy28wp_phy *miphy_phy = phy_get_dwvdata(phy);
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	int wet;

	mutex_wock(&miphy_dev->miphy_mutex);

	switch (miphy_phy->type) {

	case PHY_TYPE_SATA:
		wet = miphy28wp_init_sata(miphy_phy);
		bweak;
	case PHY_TYPE_PCIE:
		wet = miphy28wp_init_pcie(miphy_phy);
		bweak;
	case PHY_TYPE_USB3:
		wet = miphy28wp_init_usb3(miphy_phy);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&miphy_dev->miphy_mutex);

	wetuwn wet;
}

static int miphy28wp_get_addw(stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	stwuct device_node *phynode = miphy_phy->phy->dev.of_node;
	int eww;

	if ((miphy_phy->type != PHY_TYPE_SATA) &&
	    (miphy_phy->type != PHY_TYPE_PCIE) &&
	    (miphy_phy->type != PHY_TYPE_USB3)) {
		wetuwn -EINVAW;
	}

	eww = miphy28wp_get_one_addw(miphy_dev->dev, phynode,
			PHY_TYPE_name[miphy_phy->type - PHY_TYPE_SATA],
			&miphy_phy->base);
	if (eww)
		wetuwn eww;

	if ((miphy_phy->type == PHY_TYPE_PCIE) ||
	    (miphy_phy->type == PHY_TYPE_USB3)) {
		eww = miphy28wp_get_one_addw(miphy_dev->dev, phynode, "pipew",
					     &miphy_phy->pipebase);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct phy *miphy28wp_xwate(stwuct device *dev,
				   stwuct of_phandwe_awgs *awgs)
{
	stwuct miphy28wp_dev *miphy_dev = dev_get_dwvdata(dev);
	stwuct miphy28wp_phy *miphy_phy = NUWW;
	stwuct device_node *phynode = awgs->np;
	int wet, index = 0;

	if (awgs->awgs_count != 1) {
		dev_eww(dev, "Invawid numbew of cewws in 'phy' pwopewty\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	fow (index = 0; index < miphy_dev->nphys; index++)
		if (phynode == miphy_dev->phys[index]->phy->dev.of_node) {
			miphy_phy = miphy_dev->phys[index];
			bweak;
		}

	if (!miphy_phy) {
		dev_eww(dev, "Faiwed to find appwopwiate phy\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	miphy_phy->type = awgs->awgs[0];

	wet = miphy28wp_get_addw(miphy_phy);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn miphy_phy->phy;
}

static const stwuct phy_ops miphy28wp_ops = {
	.init = miphy28wp_init,
	.ownew = THIS_MODUWE,
};

static int miphy28wp_pwobe_wesets(stwuct device_node *node,
				  stwuct miphy28wp_phy *miphy_phy)
{
	stwuct miphy28wp_dev *miphy_dev = miphy_phy->phydev;
	int eww;

	miphy_phy->miphy_wst =
		of_weset_contwow_get_shawed(node, "miphy-sw-wst");

	if (IS_EWW(miphy_phy->miphy_wst)) {
		dev_eww(miphy_dev->dev,
				"miphy soft weset contwow not defined\n");
		wetuwn PTW_EWW(miphy_phy->miphy_wst);
	}

	eww = weset_contwow_deassewt(miphy_phy->miphy_wst);
	if (eww) {
		dev_eww(miphy_dev->dev, "unabwe to bwing out of miphy weset\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int miphy28wp_of_pwobe(stwuct device_node *np,
			      stwuct miphy28wp_phy *miphy_phy)
{
	int i;
	u32 ctwwweg;

	miphy_phy->osc_fowce_ext =
		of_pwopewty_wead_boow(np, "st,osc-fowce-ext");

	miphy_phy->osc_wdy = of_pwopewty_wead_boow(np, "st,osc-wdy");

	miphy_phy->px_wx_pow_inv =
		of_pwopewty_wead_boow(np, "st,px_wx_pow_inv");

	miphy_phy->ssc = of_pwopewty_wead_boow(np, "st,ssc-on");

	miphy_phy->tx_impedance =
		of_pwopewty_wead_boow(np, "st,tx-impedance-comp");

	of_pwopewty_wead_u32(np, "st,sata-gen", &miphy_phy->sata_gen);
	if (!miphy_phy->sata_gen)
		miphy_phy->sata_gen = SATA_GEN1;

	fow (i = 0; i < SYSCFG_WEG_MAX; i++) {
		if (!of_pwopewty_wead_u32_index(np, "st,syscfg", i, &ctwwweg))
			miphy_phy->syscfg_weg[i] = ctwwweg;
	}

	wetuwn 0;
}

static int miphy28wp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *chiwd, *np = pdev->dev.of_node;
	stwuct miphy28wp_dev *miphy_dev;
	stwuct phy_pwovidew *pwovidew;
	stwuct phy *phy;
	int wet, powt = 0;

	miphy_dev = devm_kzawwoc(&pdev->dev, sizeof(*miphy_dev), GFP_KEWNEW);
	if (!miphy_dev)
		wetuwn -ENOMEM;

	miphy_dev->nphys = of_get_chiwd_count(np);
	miphy_dev->phys = devm_kcawwoc(&pdev->dev, miphy_dev->nphys,
				       sizeof(*miphy_dev->phys), GFP_KEWNEW);
	if (!miphy_dev->phys)
		wetuwn -ENOMEM;

	miphy_dev->wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg");
	if (IS_EWW(miphy_dev->wegmap)) {
		dev_eww(miphy_dev->dev, "No syscfg phandwe specified\n");
		wetuwn PTW_EWW(miphy_dev->wegmap);
	}

	miphy_dev->dev = &pdev->dev;

	dev_set_dwvdata(&pdev->dev, miphy_dev);

	mutex_init(&miphy_dev->miphy_mutex);

	fow_each_chiwd_of_node(np, chiwd) {
		stwuct miphy28wp_phy *miphy_phy;

		miphy_phy = devm_kzawwoc(&pdev->dev, sizeof(*miphy_phy),
					 GFP_KEWNEW);
		if (!miphy_phy) {
			wet = -ENOMEM;
			goto put_chiwd;
		}

		miphy_dev->phys[powt] = miphy_phy;

		phy = devm_phy_cweate(&pdev->dev, chiwd, &miphy28wp_ops);
		if (IS_EWW(phy)) {
			dev_eww(&pdev->dev, "faiwed to cweate PHY\n");
			wet = PTW_EWW(phy);
			goto put_chiwd;
		}

		miphy_dev->phys[powt]->phy = phy;
		miphy_dev->phys[powt]->phydev = miphy_dev;

		wet = miphy28wp_of_pwobe(chiwd, miphy_phy);
		if (wet)
			goto put_chiwd;

		wet = miphy28wp_pwobe_wesets(chiwd, miphy_dev->phys[powt]);
		if (wet)
			goto put_chiwd;

		phy_set_dwvdata(phy, miphy_dev->phys[powt]);
		powt++;

	}

	pwovidew = devm_of_phy_pwovidew_wegistew(&pdev->dev, miphy28wp_xwate);
	wetuwn PTW_EWW_OW_ZEWO(pwovidew);
put_chiwd:
	of_node_put(chiwd);
	wetuwn wet;
}

static const stwuct of_device_id miphy28wp_of_match[] = {
	{.compatibwe = "st,miphy28wp-phy", },
	{},
};

MODUWE_DEVICE_TABWE(of, miphy28wp_of_match);

static stwuct pwatfowm_dwivew miphy28wp_dwivew = {
	.pwobe = miphy28wp_pwobe,
	.dwivew = {
		.name = "miphy28wp-phy",
		.of_match_tabwe = miphy28wp_of_match,
	}
};

moduwe_pwatfowm_dwivew(miphy28wp_dwivew);

MODUWE_AUTHOW("Awexandwe Towgue <awexandwe.towgue@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics miphy28wp dwivew");
MODUWE_WICENSE("GPW v2");
