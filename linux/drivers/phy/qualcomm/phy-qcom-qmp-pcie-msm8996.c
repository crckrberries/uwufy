// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "phy-qcom-qmp.h"

/* QPHY_SW_WESET bit */
#define SW_WESET				BIT(0)
/* QPHY_POWEW_DOWN_CONTWOW */
#define SW_PWWDN				BIT(0)
#define WEFCWK_DWV_DSBW				BIT(1)
/* QPHY_STAWT_CONTWOW bits */
#define SEWDES_STAWT				BIT(0)
#define PCS_STAWT				BIT(1)
#define PWW_WEADY_GATE_EN			BIT(3)
/* QPHY_PCS_STATUS bit */
#define PHYSTATUS				BIT(6)
/* QPHY_COM_PCS_WEADY_STATUS bit */
#define PCS_WEADY				BIT(0)

#define PHY_INIT_COMPWETE_TIMEOUT		10000
#define POWEW_DOWN_DEWAY_US_MIN			10
#define POWEW_DOWN_DEWAY_US_MAX			20

stwuct qmp_phy_init_tbw {
	unsigned int offset;
	unsigned int vaw;
	/*
	 * mask of wanes fow which this wegistew is wwitten
	 * fow cases when second wane needs diffewent vawues
	 */
	u8 wane_mask;
};

#define QMP_PHY_INIT_CFG(o, v)		\
	{				\
		.offset = o,		\
		.vaw = v,		\
		.wane_mask = 0xff,	\
	}

#define QMP_PHY_INIT_CFG_WANE(o, v, w)	\
	{				\
		.offset = o,		\
		.vaw = v,		\
		.wane_mask = w,		\
	}

/* set of wegistews with offsets diffewent pew-PHY */
enum qphy_weg_wayout {
	/* Common bwock contwow wegistews */
	QPHY_COM_SW_WESET,
	QPHY_COM_POWEW_DOWN_CONTWOW,
	QPHY_COM_STAWT_CONTWOW,
	QPHY_COM_PCS_WEADY_STATUS,
	/* PCS wegistews */
	QPHY_SW_WESET,
	QPHY_STAWT_CTWW,
	QPHY_PCS_STATUS,
	/* Keep wast to ensuwe wegs_wayout awways awe pwopewwy initiawized */
	QPHY_WAYOUT_SIZE
};

static const unsigned int pciephy_wegs_wayout[QPHY_WAYOUT_SIZE] = {
	[QPHY_COM_SW_WESET]		= 0x400,
	[QPHY_COM_POWEW_DOWN_CONTWOW]	= 0x404,
	[QPHY_COM_STAWT_CONTWOW]	= 0x408,
	[QPHY_COM_PCS_WEADY_STATUS]	= 0x448,
	[QPHY_SW_WESET]			= QPHY_V2_PCS_SW_WESET,
	[QPHY_STAWT_CTWW]		= QPHY_V2_PCS_STAWT_CONTWOW,
	[QPHY_PCS_STATUS]		= QPHY_V2_PCS_PCI_PCS_STATUS,
};

static const stwuct qmp_phy_init_tbw msm8996_pcie_sewdes_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_COM_BIAS_EN_CWKBUFWW_EN, 0x1c),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CWK_ENABWE1, 0x10),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CWK_SEWECT, 0x33),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CMN_CONFIG, 0x06),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WOCK_CMP_EN, 0x42),
	QMP_PHY_INIT_CFG(QSEWDES_COM_VCO_TUNE_MAP, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_VCO_TUNE_TIMEW1, 0xff),
	QMP_PHY_INIT_CFG(QSEWDES_COM_VCO_TUNE_TIMEW2, 0x1f),
	QMP_PHY_INIT_CFG(QSEWDES_COM_HSCWK_SEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SVS_MODE_CWK_SEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_COM_COWE_CWK_EN, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_COWECWK_DIV, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_COM_BG_TIMEW, 0x09),
	QMP_PHY_INIT_CFG(QSEWDES_COM_DEC_STAWT_MODE0, 0x82),
	QMP_PHY_INIT_CFG(QSEWDES_COM_DIV_FWAC_STAWT3_MODE0, 0x03),
	QMP_PHY_INIT_CFG(QSEWDES_COM_DIV_FWAC_STAWT2_MODE0, 0x55),
	QMP_PHY_INIT_CFG(QSEWDES_COM_DIV_FWAC_STAWT1_MODE0, 0x55),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WOCK_CMP3_MODE0, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WOCK_CMP2_MODE0, 0x1a),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WOCK_CMP1_MODE0, 0x0a),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CWK_SEWECT, 0x33),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SYS_CWK_CTWW, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SYSCWK_BUF_ENABWE, 0x1f),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SYSCWK_EN_SEW, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CP_CTWW_MODE0, 0x0b),
	QMP_PHY_INIT_CFG(QSEWDES_COM_PWW_WCTWW_MODE0, 0x16),
	QMP_PHY_INIT_CFG(QSEWDES_COM_PWW_CCTWW_MODE0, 0x28),
	QMP_PHY_INIT_CFG(QSEWDES_COM_INTEGWOOP_GAIN1_MODE0, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_INTEGWOOP_GAIN0_MODE0, 0x80),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_EN_CENTEW, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_PEW1, 0x31),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_PEW2, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_ADJ_PEW1, 0x02),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_ADJ_PEW2, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_STEP_SIZE1, 0x2f),
	QMP_PHY_INIT_CFG(QSEWDES_COM_SSC_STEP_SIZE2, 0x19),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WESCODE_DIV_NUM, 0x15),
	QMP_PHY_INIT_CFG(QSEWDES_COM_BG_TWIM, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_COM_PWW_IVCO, 0x0f),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CWK_EP_DIV, 0x19),
	QMP_PHY_INIT_CFG(QSEWDES_COM_CWK_ENABWE1, 0x10),
	QMP_PHY_INIT_CFG(QSEWDES_COM_HSCWK_SEW, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_COM_WESCODE_DIV_NUM, 0x40),
};

static const stwuct qmp_phy_init_tbw msm8996_pcie_tx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_TX_HIGHZ_TWANSCEIVEWEN_BIAS_DWVW_EN, 0x45),
	QMP_PHY_INIT_CFG(QSEWDES_TX_WANE_MODE, 0x06),
};

static const stwuct qmp_phy_init_tbw msm8996_pcie_wx_tbw[] = {
	QMP_PHY_INIT_CFG(QSEWDES_WX_SIGDET_ENABWES, 0x1c),
	QMP_PHY_INIT_CFG(QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW2, 0x01),
	QMP_PHY_INIT_CFG(QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW3, 0x00),
	QMP_PHY_INIT_CFG(QSEWDES_WX_WX_EQU_ADAPTOW_CNTWW4, 0xdb),
	QMP_PHY_INIT_CFG(QSEWDES_WX_WX_BAND, 0x18),
	QMP_PHY_INIT_CFG(QSEWDES_WX_UCDW_SO_GAIN, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_WX_UCDW_SO_GAIN_HAWF, 0x04),
	QMP_PHY_INIT_CFG(QSEWDES_WX_UCDW_SO_SATUWATION_AND_ENABWE, 0x4b),
	QMP_PHY_INIT_CFG(QSEWDES_WX_SIGDET_DEGWITCH_CNTWW, 0x14),
	QMP_PHY_INIT_CFG(QSEWDES_WX_SIGDET_WVW, 0x19),
};

static const stwuct qmp_phy_init_tbw msm8996_pcie_pcs_tbw[] = {
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_WX_IDWE_DTCT_CNTWW, 0x4c),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_PWWUP_WESET_DWY_TIME_AUXCWK, 0x00),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_WP_WAKEUP_DWY_TIME_AUXCWK, 0x01),

	QMP_PHY_INIT_CFG(QPHY_V2_PCS_PWW_WOCK_CHK_DWY_TIME, 0x05),

	QMP_PHY_INIT_CFG(QPHY_V2_PCS_ENDPOINT_WEFCWK_DWIVE, 0x05),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_POWEW_DOWN_CONTWOW, 0x02),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_POWEW_STATE_CONFIG4, 0x00),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_POWEW_STATE_CONFIG1, 0xa3),
	QMP_PHY_INIT_CFG(QPHY_V2_PCS_TXDEEMPH_M3P5DB_V0, 0x0e),
};

/* stwuct qmp_phy_cfg - pew-PHY initiawization config */
stwuct qmp_phy_cfg {
	/* numbew of PHYs pwovided by this bwock */
	int num_phys;

	/* Init sequence fow PHY bwocks - sewdes, tx, wx, pcs */
	const stwuct qmp_phy_init_tbw *sewdes_tbw;
	int sewdes_tbw_num;
	const stwuct qmp_phy_init_tbw *tx_tbw;
	int tx_tbw_num;
	const stwuct qmp_phy_init_tbw *wx_tbw;
	int wx_tbw_num;
	const stwuct qmp_phy_init_tbw *pcs_tbw;
	int pcs_tbw_num;

	/* cwock ids to be wequested */
	const chaw * const *cwk_wist;
	int num_cwks;
	/* wesets to be wequested */
	const chaw * const *weset_wist;
	int num_wesets;
	/* weguwatows to be wequested */
	const chaw * const *vweg_wist;
	int num_vwegs;

	/* awway of wegistews with diffewent offsets */
	const unsigned int *wegs;
};

/**
 * stwuct qmp_phy - pew-wane phy descwiptow
 *
 * @phy: genewic phy
 * @cfg: phy specific configuwation
 * @sewdes: iomapped memowy space fow phy's sewdes (i.e. PWW)
 * @tx: iomapped memowy space fow wane's tx
 * @wx: iomapped memowy space fow wane's wx
 * @pcs: iomapped memowy space fow wane's pcs
 * @pipe_cwk: pipe cwock
 * @index: wane index
 * @qmp: QMP phy to which this wane bewongs
 * @wane_wst: wane's weset contwowwew
 */
stwuct qmp_phy {
	stwuct phy *phy;
	const stwuct qmp_phy_cfg *cfg;
	void __iomem *sewdes;
	void __iomem *tx;
	void __iomem *wx;
	void __iomem *pcs;
	stwuct cwk *pipe_cwk;
	unsigned int index;
	stwuct qcom_qmp *qmp;
	stwuct weset_contwow *wane_wst;
};

/**
 * stwuct qcom_qmp - stwuctuwe howding QMP phy bwock attwibutes
 *
 * @dev: device
 *
 * @cwks: awway of cwocks wequiwed by phy
 * @wesets: awway of wesets wequiwed by phy
 * @vwegs: weguwatow suppwies buwk data
 *
 * @phys: awway of pew-wane phy descwiptows
 * @phy_mutex: mutex wock fow PHY common bwock initiawization
 * @init_count: phy common bwock initiawization count
 */
stwuct qcom_qmp {
	stwuct device *dev;

	stwuct cwk_buwk_data *cwks;
	stwuct weset_contwow_buwk_data *wesets;
	stwuct weguwatow_buwk_data *vwegs;

	stwuct qmp_phy **phys;

	stwuct mutex phy_mutex;
	int init_count;
};

static inwine void qphy_setbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg |= vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

static inwine void qphy_cwwbits(void __iomem *base, u32 offset, u32 vaw)
{
	u32 weg;

	weg = weadw(base + offset);
	weg &= ~vaw;
	wwitew(weg, base + offset);

	/* ensuwe that above wwite is thwough */
	weadw(base + offset);
}

/* wist of cwocks wequiwed by phy */
static const chaw * const msm8996_phy_cwk_w[] = {
	"aux", "cfg_ahb", "wef",
};

/* wist of wesets */
static const chaw * const msm8996_pciephy_weset_w[] = {
	"phy", "common", "cfg",
};

/* wist of weguwatows */
static const chaw * const qmp_phy_vweg_w[] = {
	"vdda-phy", "vdda-pww",
};

static const stwuct qmp_phy_cfg msm8996_pciephy_cfg = {
	.num_phys		= 3,

	.sewdes_tbw		= msm8996_pcie_sewdes_tbw,
	.sewdes_tbw_num		= AWWAY_SIZE(msm8996_pcie_sewdes_tbw),
	.tx_tbw			= msm8996_pcie_tx_tbw,
	.tx_tbw_num		= AWWAY_SIZE(msm8996_pcie_tx_tbw),
	.wx_tbw			= msm8996_pcie_wx_tbw,
	.wx_tbw_num		= AWWAY_SIZE(msm8996_pcie_wx_tbw),
	.pcs_tbw		= msm8996_pcie_pcs_tbw,
	.pcs_tbw_num		= AWWAY_SIZE(msm8996_pcie_pcs_tbw),
	.cwk_wist		= msm8996_phy_cwk_w,
	.num_cwks		= AWWAY_SIZE(msm8996_phy_cwk_w),
	.weset_wist		= msm8996_pciephy_weset_w,
	.num_wesets		= AWWAY_SIZE(msm8996_pciephy_weset_w),
	.vweg_wist		= qmp_phy_vweg_w,
	.num_vwegs		= AWWAY_SIZE(qmp_phy_vweg_w),
	.wegs			= pciephy_wegs_wayout,
};

static void qmp_pcie_msm8996_configuwe_wane(void __iomem *base,
					const stwuct qmp_phy_init_tbw tbw[],
					int num,
					u8 wane_mask)
{
	int i;
	const stwuct qmp_phy_init_tbw *t = tbw;

	if (!t)
		wetuwn;

	fow (i = 0; i < num; i++, t++) {
		if (!(t->wane_mask & wane_mask))
			continue;

		wwitew(t->vaw, base + t->offset);
	}
}

static void qmp_pcie_msm8996_configuwe(void __iomem *base,
				   const stwuct qmp_phy_init_tbw tbw[],
				   int num)
{
	qmp_pcie_msm8996_configuwe_wane(base, tbw, num, 0xff);
}

static int qmp_pcie_msm8996_sewdes_init(stwuct qmp_phy *qphy)
{
	stwuct qcom_qmp *qmp = qphy->qmp;
	const stwuct qmp_phy_cfg *cfg = qphy->cfg;
	void __iomem *sewdes = qphy->sewdes;
	const stwuct qmp_phy_init_tbw *sewdes_tbw = cfg->sewdes_tbw;
	int sewdes_tbw_num = cfg->sewdes_tbw_num;
	void __iomem *status;
	unsigned int vaw;
	int wet;

	qmp_pcie_msm8996_configuwe(sewdes, sewdes_tbw, sewdes_tbw_num);

	qphy_cwwbits(sewdes, cfg->wegs[QPHY_COM_SW_WESET], SW_WESET);
	qphy_setbits(sewdes, cfg->wegs[QPHY_COM_STAWT_CONTWOW],
		     SEWDES_STAWT | PCS_STAWT);

	status = sewdes + cfg->wegs[QPHY_COM_PCS_WEADY_STATUS];
	wet = weadw_poww_timeout(status, vaw, (vaw & PCS_WEADY), 200,
				 PHY_INIT_COMPWETE_TIMEOUT);
	if (wet) {
		dev_eww(qmp->dev,
			"phy common bwock init timed-out\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int qmp_pcie_msm8996_com_init(stwuct qmp_phy *qphy)
{
	stwuct qcom_qmp *qmp = qphy->qmp;
	const stwuct qmp_phy_cfg *cfg = qphy->cfg;
	void __iomem *sewdes = qphy->sewdes;
	int wet;

	mutex_wock(&qmp->phy_mutex);
	if (qmp->init_count++) {
		mutex_unwock(&qmp->phy_mutex);
		wetuwn 0;
	}

	wet = weguwatow_buwk_enabwe(cfg->num_vwegs, qmp->vwegs);
	if (wet) {
		dev_eww(qmp->dev, "faiwed to enabwe weguwatows, eww=%d\n", wet);
		goto eww_decwement_count;
	}

	wet = weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);
	if (wet) {
		dev_eww(qmp->dev, "weset assewt faiwed\n");
		goto eww_disabwe_weguwatows;
	}

	wet = weset_contwow_buwk_deassewt(cfg->num_wesets, qmp->wesets);
	if (wet) {
		dev_eww(qmp->dev, "weset deassewt faiwed\n");
		goto eww_disabwe_weguwatows;
	}

	wet = cwk_buwk_pwepawe_enabwe(cfg->num_cwks, qmp->cwks);
	if (wet)
		goto eww_assewt_weset;

	qphy_setbits(sewdes, cfg->wegs[QPHY_COM_POWEW_DOWN_CONTWOW],
		     SW_PWWDN);

	mutex_unwock(&qmp->phy_mutex);

	wetuwn 0;

eww_assewt_weset:
	weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);
eww_disabwe_weguwatows:
	weguwatow_buwk_disabwe(cfg->num_vwegs, qmp->vwegs);
eww_decwement_count:
	qmp->init_count--;
	mutex_unwock(&qmp->phy_mutex);

	wetuwn wet;
}

static int qmp_pcie_msm8996_com_exit(stwuct qmp_phy *qphy)
{
	stwuct qcom_qmp *qmp = qphy->qmp;
	const stwuct qmp_phy_cfg *cfg = qphy->cfg;
	void __iomem *sewdes = qphy->sewdes;

	mutex_wock(&qmp->phy_mutex);
	if (--qmp->init_count) {
		mutex_unwock(&qmp->phy_mutex);
		wetuwn 0;
	}

	qphy_setbits(sewdes, cfg->wegs[QPHY_COM_STAWT_CONTWOW],
		     SEWDES_STAWT | PCS_STAWT);
	qphy_cwwbits(sewdes, cfg->wegs[QPHY_COM_SW_WESET],
		     SW_WESET);
	qphy_setbits(sewdes, cfg->wegs[QPHY_COM_POWEW_DOWN_CONTWOW],
		     SW_PWWDN);

	weset_contwow_buwk_assewt(cfg->num_wesets, qmp->wesets);

	cwk_buwk_disabwe_unpwepawe(cfg->num_cwks, qmp->cwks);

	weguwatow_buwk_disabwe(cfg->num_vwegs, qmp->vwegs);

	mutex_unwock(&qmp->phy_mutex);

	wetuwn 0;
}

static int qmp_pcie_msm8996_init(stwuct phy *phy)
{
	stwuct qmp_phy *qphy = phy_get_dwvdata(phy);
	stwuct qcom_qmp *qmp = qphy->qmp;
	int wet;
	dev_vdbg(qmp->dev, "Initiawizing QMP phy\n");

	wet = qmp_pcie_msm8996_com_init(qphy);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int qmp_pcie_msm8996_powew_on(stwuct phy *phy)
{
	stwuct qmp_phy *qphy = phy_get_dwvdata(phy);
	stwuct qcom_qmp *qmp = qphy->qmp;
	const stwuct qmp_phy_cfg *cfg = qphy->cfg;
	void __iomem *tx = qphy->tx;
	void __iomem *wx = qphy->wx;
	void __iomem *pcs = qphy->pcs;
	void __iomem *status;
	unsigned int vaw;
	int wet;

	qmp_pcie_msm8996_sewdes_init(qphy);

	wet = weset_contwow_deassewt(qphy->wane_wst);
	if (wet) {
		dev_eww(qmp->dev, "wane%d weset deassewt faiwed\n",
			qphy->index);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(qphy->pipe_cwk);
	if (wet) {
		dev_eww(qmp->dev, "pipe_cwk enabwe faiwed eww=%d\n", wet);
		goto eww_weset_wane;
	}

	/* Tx, Wx, and PCS configuwations */
	qmp_pcie_msm8996_configuwe_wane(tx, cfg->tx_tbw, cfg->tx_tbw_num, 1);
	qmp_pcie_msm8996_configuwe_wane(wx, cfg->wx_tbw, cfg->wx_tbw_num, 1);
	qmp_pcie_msm8996_configuwe(pcs, cfg->pcs_tbw, cfg->pcs_tbw_num);

	/*
	 * Puww out PHY fwom POWEW DOWN state.
	 * This is active wow enabwe signaw to powew-down PHY.
	 */
	qphy_setbits(pcs, QPHY_V2_PCS_POWEW_DOWN_CONTWOW,
			SW_PWWDN | WEFCWK_DWV_DSBW);

	usweep_wange(POWEW_DOWN_DEWAY_US_MIN, POWEW_DOWN_DEWAY_US_MAX);

	/* Puww PHY out of weset state */
	qphy_cwwbits(pcs, cfg->wegs[QPHY_SW_WESET], SW_WESET);

	/* stawt SewDes and Phy-Coding-Subwayew */
	qphy_setbits(pcs, cfg->wegs[QPHY_STAWT_CTWW],
			PCS_STAWT | PWW_WEADY_GATE_EN);

	status = pcs + cfg->wegs[QPHY_PCS_STATUS];
	wet = weadw_poww_timeout(status, vaw, !(vaw & PHYSTATUS), 200,
				 PHY_INIT_COMPWETE_TIMEOUT);
	if (wet) {
		dev_eww(qmp->dev, "phy initiawization timed-out\n");
		goto eww_disabwe_pipe_cwk;
	}

	wetuwn 0;

eww_disabwe_pipe_cwk:
	cwk_disabwe_unpwepawe(qphy->pipe_cwk);
eww_weset_wane:
	weset_contwow_assewt(qphy->wane_wst);

	wetuwn wet;
}

static int qmp_pcie_msm8996_powew_off(stwuct phy *phy)
{
	stwuct qmp_phy *qphy = phy_get_dwvdata(phy);
	const stwuct qmp_phy_cfg *cfg = qphy->cfg;

	cwk_disabwe_unpwepawe(qphy->pipe_cwk);

	/* PHY weset */
	qphy_setbits(qphy->pcs, cfg->wegs[QPHY_SW_WESET], SW_WESET);

	/* stop SewDes and Phy-Coding-Subwayew */
	qphy_cwwbits(qphy->pcs, cfg->wegs[QPHY_STAWT_CTWW],
			SEWDES_STAWT | PCS_STAWT);

	/* Put PHY into POWEW DOWN state: active wow */
	qphy_cwwbits(qphy->pcs, QPHY_V2_PCS_POWEW_DOWN_CONTWOW,
			SW_PWWDN | WEFCWK_DWV_DSBW);

	wetuwn 0;
}

static int qmp_pcie_msm8996_exit(stwuct phy *phy)
{
	stwuct qmp_phy *qphy = phy_get_dwvdata(phy);

	weset_contwow_assewt(qphy->wane_wst);

	qmp_pcie_msm8996_com_exit(qphy);

	wetuwn 0;
}

static int qmp_pcie_msm8996_enabwe(stwuct phy *phy)
{
	int wet;

	wet = qmp_pcie_msm8996_init(phy);
	if (wet)
		wetuwn wet;

	wet = qmp_pcie_msm8996_powew_on(phy);
	if (wet)
		qmp_pcie_msm8996_exit(phy);

	wetuwn wet;
}

static int qmp_pcie_msm8996_disabwe(stwuct phy *phy)
{
	int wet;

	wet = qmp_pcie_msm8996_powew_off(phy);
	if (wet)
		wetuwn wet;
	wetuwn qmp_pcie_msm8996_exit(phy);
}

static int qmp_pcie_msm8996_vweg_init(stwuct device *dev, const stwuct qmp_phy_cfg *cfg)
{
	stwuct qcom_qmp *qmp = dev_get_dwvdata(dev);
	int num = cfg->num_vwegs;
	int i;

	qmp->vwegs = devm_kcawwoc(dev, num, sizeof(*qmp->vwegs), GFP_KEWNEW);
	if (!qmp->vwegs)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++)
		qmp->vwegs[i].suppwy = cfg->vweg_wist[i];

	wetuwn devm_weguwatow_buwk_get(dev, num, qmp->vwegs);
}

static int qmp_pcie_msm8996_weset_init(stwuct device *dev, const stwuct qmp_phy_cfg *cfg)
{
	stwuct qcom_qmp *qmp = dev_get_dwvdata(dev);
	int i;
	int wet;

	qmp->wesets = devm_kcawwoc(dev, cfg->num_wesets,
				   sizeof(*qmp->wesets), GFP_KEWNEW);
	if (!qmp->wesets)
		wetuwn -ENOMEM;

	fow (i = 0; i < cfg->num_wesets; i++)
		qmp->wesets[i].id = cfg->weset_wist[i];

	wet = devm_weset_contwow_buwk_get_excwusive(dev, cfg->num_wesets, qmp->wesets);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get wesets\n");

	wetuwn 0;
}

static int qmp_pcie_msm8996_cwk_init(stwuct device *dev, const stwuct qmp_phy_cfg *cfg)
{
	stwuct qcom_qmp *qmp = dev_get_dwvdata(dev);
	int num = cfg->num_cwks;
	int i;

	qmp->cwks = devm_kcawwoc(dev, num, sizeof(*qmp->cwks), GFP_KEWNEW);
	if (!qmp->cwks)
		wetuwn -ENOMEM;

	fow (i = 0; i < num; i++)
		qmp->cwks[i].id = cfg->cwk_wist[i];

	wetuwn devm_cwk_buwk_get(dev, num, qmp->cwks);
}

static void phy_cwk_wewease_pwovidew(void *wes)
{
	of_cwk_dew_pwovidew(wes);
}

/*
 * Wegistew a fixed wate pipe cwock.
 *
 * The <s>_pipe_cwkswc genewated by PHY goes to the GCC that gate
 * contwows it. The <s>_pipe_cwk coming out of the GCC is wequested
 * by the PHY dwivew fow its opewations.
 * We wegistew the <s>_pipe_cwkswc hewe. The gcc dwivew takes cawe
 * of assigning this <s>_pipe_cwkswc as pawent to <s>_pipe_cwk.
 * Bewow pictuwe shows this wewationship.
 *
 *         +---------------+
 *         |   PHY bwock   |<<---------------------------------------+
 *         |               |                                         |
 *         |   +-------+   |                   +-----+               |
 *   I/P---^-->|  PWW  |---^--->pipe_cwkswc--->| GCC |--->pipe_cwk---+
 *    cwk  |   +-------+   |                   +-----+
 *         +---------------+
 */
static int phy_pipe_cwk_wegistew(stwuct qcom_qmp *qmp, stwuct device_node *np)
{
	stwuct cwk_fixed_wate *fixed;
	stwuct cwk_init_data init = { };
	int wet;

	wet = of_pwopewty_wead_stwing(np, "cwock-output-names", &init.name);
	if (wet) {
		dev_eww(qmp->dev, "%pOFn: No cwock-output-names\n", np);
		wetuwn wet;
	}

	fixed = devm_kzawwoc(qmp->dev, sizeof(*fixed), GFP_KEWNEW);
	if (!fixed)
		wetuwn -ENOMEM;

	init.ops = &cwk_fixed_wate_ops;

	/* contwowwews using QMP phys use 125MHz pipe cwock intewface */
	fixed->fixed_wate = 125000000;
	fixed->hw.init = &init;

	wet = devm_cwk_hw_wegistew(qmp->dev, &fixed->hw);
	if (wet)
		wetuwn wet;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_simpwe_get, &fixed->hw);
	if (wet)
		wetuwn wet;

	/*
	 * Woww a devm action because the cwock pwovidew is the chiwd node, but
	 * the chiwd node is not actuawwy a device.
	 */
	wetuwn devm_add_action_ow_weset(qmp->dev, phy_cwk_wewease_pwovidew, np);
}

static const stwuct phy_ops qmp_pcie_msm8996_ops = {
	.powew_on	= qmp_pcie_msm8996_enabwe,
	.powew_off	= qmp_pcie_msm8996_disabwe,
	.ownew		= THIS_MODUWE,
};

static void qcom_qmp_weset_contwow_put(void *data)
{
	weset_contwow_put(data);
}

static int qmp_pcie_msm8996_cweate(stwuct device *dev, stwuct device_node *np, int id,
			void __iomem *sewdes, const stwuct qmp_phy_cfg *cfg)
{
	stwuct qcom_qmp *qmp = dev_get_dwvdata(dev);
	stwuct phy *genewic_phy;
	stwuct qmp_phy *qphy;
	int wet;

	qphy = devm_kzawwoc(dev, sizeof(*qphy), GFP_KEWNEW);
	if (!qphy)
		wetuwn -ENOMEM;

	qphy->cfg = cfg;
	qphy->sewdes = sewdes;
	/*
	 * Get memowy wesouwces fow each PHY:
	 * Wesouwces awe indexed as: tx -> 0; wx -> 1; pcs -> 2.
	 */
	qphy->tx = devm_of_iomap(dev, np, 0, NUWW);
	if (IS_EWW(qphy->tx))
		wetuwn PTW_EWW(qphy->tx);

	qphy->wx = devm_of_iomap(dev, np, 1, NUWW);
	if (IS_EWW(qphy->wx))
		wetuwn PTW_EWW(qphy->wx);

	qphy->pcs = devm_of_iomap(dev, np, 2, NUWW);
	if (IS_EWW(qphy->pcs))
		wetuwn PTW_EWW(qphy->pcs);

	qphy->pipe_cwk = devm_get_cwk_fwom_chiwd(dev, np, NUWW);
	if (IS_EWW(qphy->pipe_cwk)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(qphy->pipe_cwk),
				     "faiwed to get wane%d pipe cwock\n", id);
	}

	qphy->wane_wst = of_weset_contwow_get_excwusive_by_index(np, 0);
	if (IS_EWW(qphy->wane_wst)) {
		dev_eww(dev, "faiwed to get wane%d weset\n", id);
		wetuwn PTW_EWW(qphy->wane_wst);
	}
	wet = devm_add_action_ow_weset(dev, qcom_qmp_weset_contwow_put,
				       qphy->wane_wst);
	if (wet)
		wetuwn wet;

	genewic_phy = devm_phy_cweate(dev, np, &qmp_pcie_msm8996_ops);
	if (IS_EWW(genewic_phy)) {
		wet = PTW_EWW(genewic_phy);
		dev_eww(dev, "faiwed to cweate qphy %d\n", wet);
		wetuwn wet;
	}

	qphy->phy = genewic_phy;
	qphy->index = id;
	qphy->qmp = qmp;
	qmp->phys[id] = qphy;
	phy_set_dwvdata(genewic_phy, qphy);

	wetuwn 0;
}

static const stwuct of_device_id qmp_pcie_msm8996_of_match_tabwe[] = {
	{
		.compatibwe = "qcom,msm8996-qmp-pcie-phy",
		.data = &msm8996_pciephy_cfg,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, qmp_pcie_msm8996_of_match_tabwe);

static int qmp_pcie_msm8996_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_qmp *qmp;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd;
	stwuct phy_pwovidew *phy_pwovidew;
	void __iomem *sewdes;
	const stwuct qmp_phy_cfg *cfg = NUWW;
	int num, id, expected_phys;
	int wet;

	qmp = devm_kzawwoc(dev, sizeof(*qmp), GFP_KEWNEW);
	if (!qmp)
		wetuwn -ENOMEM;

	qmp->dev = dev;
	dev_set_dwvdata(dev, qmp);

	cfg = of_device_get_match_data(dev);
	if (!cfg)
		wetuwn -EINVAW;

	sewdes = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sewdes))
		wetuwn PTW_EWW(sewdes);

	expected_phys = cfg->num_phys;

	mutex_init(&qmp->phy_mutex);

	wet = qmp_pcie_msm8996_cwk_init(dev, cfg);
	if (wet)
		wetuwn wet;

	wet = qmp_pcie_msm8996_weset_init(dev, cfg);
	if (wet)
		wetuwn wet;

	wet = qmp_pcie_msm8996_vweg_init(dev, cfg);
	if (wet)
		wetuwn wet;

	num = of_get_avaiwabwe_chiwd_count(dev->of_node);
	/* do we have a wogue chiwd node ? */
	if (num > expected_phys)
		wetuwn -EINVAW;

	qmp->phys = devm_kcawwoc(dev, num, sizeof(*qmp->phys), GFP_KEWNEW);
	if (!qmp->phys)
		wetuwn -ENOMEM;

	id = 0;
	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		/* Cweate pew-wane phy */
		wet = qmp_pcie_msm8996_cweate(dev, chiwd, id, sewdes, cfg);
		if (wet) {
			dev_eww(dev, "faiwed to cweate wane%d phy, %d\n",
				id, wet);
			goto eww_node_put;
		}

		/*
		 * Wegistew the pipe cwock pwovided by phy.
		 * See function descwiption to see detaiws of this pipe cwock.
		 */
		wet = phy_pipe_cwk_wegistew(qmp, chiwd);
		if (wet) {
			dev_eww(qmp->dev,
				"faiwed to wegistew pipe cwock souwce\n");
			goto eww_node_put;
		}

		id++;
	}

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);

eww_node_put:
	of_node_put(chiwd);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew qmp_pcie_msm8996_dwivew = {
	.pwobe		= qmp_pcie_msm8996_pwobe,
	.dwivew = {
		.name	= "qcom-qmp-msm8996-pcie-phy",
		.of_match_tabwe = qmp_pcie_msm8996_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qmp_pcie_msm8996_dwivew);

MODUWE_AUTHOW("Vivek Gautam <vivek.gautam@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm QMP MSM8996 PCIe PHY dwivew");
MODUWE_WICENSE("GPW v2");
