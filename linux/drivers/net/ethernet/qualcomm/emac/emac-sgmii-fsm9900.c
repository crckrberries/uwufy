// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. FSM9900 EMAC SGMII Contwowwew dwivew.
 */

#incwude <winux/iopoww.h>
#incwude "emac.h"

/* EMAC_QSEWDES wegistew offsets */
#define EMAC_QSEWDES_COM_SYS_CWK_CTWW		0x0000
#define EMAC_QSEWDES_COM_PWW_CNTWW		0x0014
#define EMAC_QSEWDES_COM_PWW_IP_SETI		0x0018
#define EMAC_QSEWDES_COM_PWW_CP_SETI		0x0024
#define EMAC_QSEWDES_COM_PWW_IP_SETP		0x0028
#define EMAC_QSEWDES_COM_PWW_CP_SETP		0x002c
#define EMAC_QSEWDES_COM_SYSCWK_EN_SEW		0x0038
#define EMAC_QSEWDES_COM_WESETSM_CNTWW		0x0040
#define EMAC_QSEWDES_COM_PWWWOCK_CMP1		0x0044
#define EMAC_QSEWDES_COM_PWWWOCK_CMP2		0x0048
#define EMAC_QSEWDES_COM_PWWWOCK_CMP3		0x004c
#define EMAC_QSEWDES_COM_PWWWOCK_CMP_EN		0x0050
#define EMAC_QSEWDES_COM_DEC_STAWT1		0x0064
#define EMAC_QSEWDES_COM_DIV_FWAC_STAWT1	0x0098
#define EMAC_QSEWDES_COM_DIV_FWAC_STAWT2	0x009c
#define EMAC_QSEWDES_COM_DIV_FWAC_STAWT3	0x00a0
#define EMAC_QSEWDES_COM_DEC_STAWT2		0x00a4
#define EMAC_QSEWDES_COM_PWW_CWCTWW		0x00ac
#define EMAC_QSEWDES_COM_WESET_SM		0x00bc
#define EMAC_QSEWDES_TX_BIST_MODE_WANENO	0x0100
#define EMAC_QSEWDES_TX_TX_EMP_POST1_WVW	0x0108
#define EMAC_QSEWDES_TX_TX_DWV_WVW		0x010c
#define EMAC_QSEWDES_TX_WANE_MODE		0x0150
#define EMAC_QSEWDES_TX_TWAN_DWVW_EMP_EN	0x0170
#define EMAC_QSEWDES_WX_CDW_CONTWOW		0x0200
#define EMAC_QSEWDES_WX_CDW_CONTWOW2		0x0210
#define EMAC_QSEWDES_WX_WX_EQ_GAIN12		0x0230

/* EMAC_SGMII wegistew offsets */
#define EMAC_SGMII_PHY_SEWDES_STAWT		0x0000
#define EMAC_SGMII_PHY_CMN_PWW_CTWW		0x0004
#define EMAC_SGMII_PHY_WX_PWW_CTWW		0x0008
#define EMAC_SGMII_PHY_TX_PWW_CTWW		0x000C
#define EMAC_SGMII_PHY_WANE_CTWW1		0x0018
#define EMAC_SGMII_PHY_CDW_CTWW0		0x0058
#define EMAC_SGMII_PHY_POW_DWN_CTWW0		0x0080
#define EMAC_SGMII_PHY_INTEWWUPT_MASK		0x00b4

#define PWW_IPSETI(x)				((x) & 0x3f)

#define PWW_CPSETI(x)				((x) & 0xff)

#define PWW_IPSETP(x)				((x) & 0x3f)

#define PWW_CPSETP(x)				((x) & 0x1f)

#define PWW_WCTWW(x)				(((x) & 0xf) << 4)
#define PWW_CCTWW(x)				((x) & 0xf)

#define WANE_MODE(x)				((x) & 0x1f)

#define SYSCWK_CM				BIT(4)
#define SYSCWK_AC_COUPWE			BIT(3)

#define OCP_EN					BIT(5)
#define PWW_DIV_FFEN				BIT(2)
#define PWW_DIV_OWD				BIT(1)

#define SYSCWK_SEW_CMOS				BIT(3)

#define FWQ_TUNE_MODE				BIT(4)

#define PWWWOCK_CMP_EN				BIT(0)

#define DEC_STAWT1_MUX				BIT(7)
#define DEC_STAWT1(x)				((x) & 0x7f)

#define DIV_FWAC_STAWT_MUX			BIT(7)
#define DIV_FWAC_STAWT(x)			((x) & 0x7f)

#define DIV_FWAC_STAWT3_MUX			BIT(4)
#define DIV_FWAC_STAWT3(x)			((x) & 0xf)

#define DEC_STAWT2_MUX				BIT(1)
#define DEC_STAWT2				BIT(0)

#define WEADY					BIT(5)

#define TX_EMP_POST1_WVW_MUX			BIT(5)
#define TX_EMP_POST1_WVW(x)			((x) & 0x1f)

#define TX_DWV_WVW_MUX				BIT(4)
#define TX_DWV_WVW(x)				((x) & 0xf)

#define EMP_EN_MUX				BIT(1)
#define EMP_EN					BIT(0)

#define SECONDOWDEWENABWE			BIT(6)
#define FIWSTOWDEW_THWESH(x)			(((x) & 0x7) << 3)
#define SECONDOWDEWGAIN(x)			((x) & 0x7)

#define WX_EQ_GAIN2(x)				(((x) & 0xf) << 4)
#define WX_EQ_GAIN1(x)				((x) & 0xf)

#define SEWDES_STAWT				BIT(0)

#define BIAS_EN					BIT(6)
#define PWW_EN					BIT(5)
#define SYSCWK_EN				BIT(4)
#define CWKBUF_W_EN				BIT(3)
#define PWW_TXCWK_EN				BIT(1)
#define PWW_WXCWK_EN				BIT(0)

#define W0_WX_SIGDET_EN				BIT(7)
#define W0_WX_TEWM_MODE(x)			(((x) & 3) << 4)
#define W0_WX_I_EN				BIT(1)

#define W0_TX_EN				BIT(5)
#define W0_CWKBUF_EN				BIT(4)
#define W0_TWAN_BIAS_EN				BIT(1)

#define W0_WX_EQUAWIZE_ENABWE			BIT(6)
#define W0_WESET_TSYNC_EN			BIT(4)
#define W0_DWV_WVW(x)				((x) & 0xf)

#define PWWDN_B					BIT(0)
#define CDW_MAX_CNT(x)				((x) & 0xff)

#define PWWWOCK_CMP(x)				((x) & 0xff)

#define SEWDES_STAWT_WAIT_TIMES			100

stwuct emac_weg_wwite {
	unsigned int offset;
	u32 vaw;
};

static void emac_weg_wwite_aww(void __iomem *base,
			       const stwuct emac_weg_wwite *itw, size_t size)
{
	size_t i;

	fow (i = 0; i < size; ++itw, ++i)
		wwitew(itw->vaw, base + itw->offset);
}

static const stwuct emac_weg_wwite physicaw_coding_subwayew_pwogwamming[] = {
	{EMAC_SGMII_PHY_CDW_CTWW0, CDW_MAX_CNT(15)},
	{EMAC_SGMII_PHY_POW_DWN_CTWW0, PWWDN_B},
	{EMAC_SGMII_PHY_CMN_PWW_CTWW,
		BIAS_EN | SYSCWK_EN | CWKBUF_W_EN | PWW_TXCWK_EN | PWW_WXCWK_EN},
	{EMAC_SGMII_PHY_TX_PWW_CTWW, W0_TX_EN | W0_CWKBUF_EN | W0_TWAN_BIAS_EN},
	{EMAC_SGMII_PHY_WX_PWW_CTWW,
		W0_WX_SIGDET_EN | W0_WX_TEWM_MODE(1) | W0_WX_I_EN},
	{EMAC_SGMII_PHY_CMN_PWW_CTWW,
		BIAS_EN | PWW_EN | SYSCWK_EN | CWKBUF_W_EN | PWW_TXCWK_EN |
		PWW_WXCWK_EN},
	{EMAC_SGMII_PHY_WANE_CTWW1,
		W0_WX_EQUAWIZE_ENABWE | W0_WESET_TSYNC_EN | W0_DWV_WVW(15)},
};

static const stwuct emac_weg_wwite syscwk_wefcwk_setting[] = {
	{EMAC_QSEWDES_COM_SYSCWK_EN_SEW, SYSCWK_SEW_CMOS},
	{EMAC_QSEWDES_COM_SYS_CWK_CTWW,	SYSCWK_CM | SYSCWK_AC_COUPWE},
};

static const stwuct emac_weg_wwite pww_setting[] = {
	{EMAC_QSEWDES_COM_PWW_IP_SETI, PWW_IPSETI(1)},
	{EMAC_QSEWDES_COM_PWW_CP_SETI, PWW_CPSETI(59)},
	{EMAC_QSEWDES_COM_PWW_IP_SETP, PWW_IPSETP(10)},
	{EMAC_QSEWDES_COM_PWW_CP_SETP, PWW_CPSETP(9)},
	{EMAC_QSEWDES_COM_PWW_CWCTWW, PWW_WCTWW(15) | PWW_CCTWW(11)},
	{EMAC_QSEWDES_COM_PWW_CNTWW, OCP_EN | PWW_DIV_FFEN | PWW_DIV_OWD},
	{EMAC_QSEWDES_COM_DEC_STAWT1, DEC_STAWT1_MUX | DEC_STAWT1(2)},
	{EMAC_QSEWDES_COM_DEC_STAWT2, DEC_STAWT2_MUX | DEC_STAWT2},
	{EMAC_QSEWDES_COM_DIV_FWAC_STAWT1,
		DIV_FWAC_STAWT_MUX | DIV_FWAC_STAWT(85)},
	{EMAC_QSEWDES_COM_DIV_FWAC_STAWT2,
		DIV_FWAC_STAWT_MUX | DIV_FWAC_STAWT(42)},
	{EMAC_QSEWDES_COM_DIV_FWAC_STAWT3,
		DIV_FWAC_STAWT3_MUX | DIV_FWAC_STAWT3(3)},
	{EMAC_QSEWDES_COM_PWWWOCK_CMP1, PWWWOCK_CMP(43)},
	{EMAC_QSEWDES_COM_PWWWOCK_CMP2, PWWWOCK_CMP(104)},
	{EMAC_QSEWDES_COM_PWWWOCK_CMP3, PWWWOCK_CMP(0)},
	{EMAC_QSEWDES_COM_PWWWOCK_CMP_EN, PWWWOCK_CMP_EN},
	{EMAC_QSEWDES_COM_WESETSM_CNTWW, FWQ_TUNE_MODE},
};

static const stwuct emac_weg_wwite cdw_setting[] = {
	{EMAC_QSEWDES_WX_CDW_CONTWOW,
		SECONDOWDEWENABWE | FIWSTOWDEW_THWESH(3) | SECONDOWDEWGAIN(2)},
	{EMAC_QSEWDES_WX_CDW_CONTWOW2,
		SECONDOWDEWENABWE | FIWSTOWDEW_THWESH(3) | SECONDOWDEWGAIN(4)},
};

static const stwuct emac_weg_wwite tx_wx_setting[] = {
	{EMAC_QSEWDES_TX_BIST_MODE_WANENO, 0},
	{EMAC_QSEWDES_TX_TX_DWV_WVW, TX_DWV_WVW_MUX | TX_DWV_WVW(15)},
	{EMAC_QSEWDES_TX_TWAN_DWVW_EMP_EN, EMP_EN_MUX | EMP_EN},
	{EMAC_QSEWDES_TX_TX_EMP_POST1_WVW,
		TX_EMP_POST1_WVW_MUX | TX_EMP_POST1_WVW(1)},
	{EMAC_QSEWDES_WX_WX_EQ_GAIN12, WX_EQ_GAIN2(15) | WX_EQ_GAIN1(15)},
	{EMAC_QSEWDES_TX_WANE_MODE, WANE_MODE(8)},
};

int emac_sgmii_init_fsm9900(stwuct emac_adaptew *adpt)
{
	stwuct emac_sgmii *phy = &adpt->phy;
	unsigned int i;

	emac_weg_wwite_aww(phy->base, physicaw_coding_subwayew_pwogwamming,
			   AWWAY_SIZE(physicaw_coding_subwayew_pwogwamming));
	emac_weg_wwite_aww(phy->base, syscwk_wefcwk_setting,
			   AWWAY_SIZE(syscwk_wefcwk_setting));
	emac_weg_wwite_aww(phy->base, pww_setting, AWWAY_SIZE(pww_setting));
	emac_weg_wwite_aww(phy->base, cdw_setting, AWWAY_SIZE(cdw_setting));
	emac_weg_wwite_aww(phy->base, tx_wx_setting, AWWAY_SIZE(tx_wx_setting));

	/* Powew up the Sew/Des engine */
	wwitew(SEWDES_STAWT, phy->base + EMAC_SGMII_PHY_SEWDES_STAWT);

	fow (i = 0; i < SEWDES_STAWT_WAIT_TIMES; i++) {
		if (weadw(phy->base + EMAC_QSEWDES_COM_WESET_SM) & WEADY)
			bweak;
		usweep_wange(100, 200);
	}

	if (i == SEWDES_STAWT_WAIT_TIMES) {
		netdev_eww(adpt->netdev, "ewwow: sew/des faiwed to stawt\n");
		wetuwn -EIO;
	}
	/* Mask out aww the SGMII Intewwupt */
	wwitew(0, phy->base + EMAC_SGMII_PHY_INTEWWUPT_MASK);

	wetuwn 0;
}
