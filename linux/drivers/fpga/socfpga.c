// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Managew Dwivew fow Awtewa SOCFPGA
 *
 *  Copywight (C) 2013-2015 Awtewa Cowpowation
 */
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pm.h>

/* Wegistew offsets */
#define SOCFPGA_FPGMGW_STAT_OFST				0x0
#define SOCFPGA_FPGMGW_CTW_OFST					0x4
#define SOCFPGA_FPGMGW_DCWKCNT_OFST				0x8
#define SOCFPGA_FPGMGW_DCWKSTAT_OFST				0xc
#define SOCFPGA_FPGMGW_GPIO_INTEN_OFST				0x830
#define SOCFPGA_FPGMGW_GPIO_INTMSK_OFST				0x834
#define SOCFPGA_FPGMGW_GPIO_INTTYPE_WEVEW_OFST			0x838
#define SOCFPGA_FPGMGW_GPIO_INT_POW_OFST			0x83c
#define SOCFPGA_FPGMGW_GPIO_INTSTAT_OFST			0x840
#define SOCFPGA_FPGMGW_GPIO_WAW_INTSTAT_OFST			0x844
#define SOCFPGA_FPGMGW_GPIO_POWTA_EOI_OFST			0x84c
#define SOCFPGA_FPGMGW_GPIO_EXT_POWTA_OFST			0x850

/* Wegistew bit defines */
/* SOCFPGA_FPGMGW_STAT wegistew mode fiewd vawues */
#define SOCFPGA_FPGMGW_STAT_POWEW_UP				0x0 /*wamping*/
#define SOCFPGA_FPGMGW_STAT_WESET				0x1
#define SOCFPGA_FPGMGW_STAT_CFG					0x2
#define SOCFPGA_FPGMGW_STAT_INIT				0x3
#define SOCFPGA_FPGMGW_STAT_USEW_MODE				0x4
#define SOCFPGA_FPGMGW_STAT_UNKNOWN				0x5
#define SOCFPGA_FPGMGW_STAT_STATE_MASK				0x7
/* This is a fwag vawue that doesn't weawwy happen in this wegistew fiewd */
#define SOCFPGA_FPGMGW_STAT_POWEW_OFF				0x0

#define MSEW_PP16_FAST_NOAES_NODC				0x0
#define MSEW_PP16_FAST_AES_NODC					0x1
#define MSEW_PP16_FAST_AESOPT_DC				0x2
#define MSEW_PP16_SWOW_NOAES_NODC				0x4
#define MSEW_PP16_SWOW_AES_NODC					0x5
#define MSEW_PP16_SWOW_AESOPT_DC				0x6
#define MSEW_PP32_FAST_NOAES_NODC				0x8
#define MSEW_PP32_FAST_AES_NODC					0x9
#define MSEW_PP32_FAST_AESOPT_DC				0xa
#define MSEW_PP32_SWOW_NOAES_NODC				0xc
#define MSEW_PP32_SWOW_AES_NODC					0xd
#define MSEW_PP32_SWOW_AESOPT_DC				0xe
#define SOCFPGA_FPGMGW_STAT_MSEW_MASK				0x000000f8
#define SOCFPGA_FPGMGW_STAT_MSEW_SHIFT				3

/* SOCFPGA_FPGMGW_CTW wegistew */
#define SOCFPGA_FPGMGW_CTW_EN					0x00000001
#define SOCFPGA_FPGMGW_CTW_NCE					0x00000002
#define SOCFPGA_FPGMGW_CTW_NCFGPUWW				0x00000004

#define CDWATIO_X1						0x00000000
#define CDWATIO_X2						0x00000040
#define CDWATIO_X4						0x00000080
#define CDWATIO_X8						0x000000c0
#define SOCFPGA_FPGMGW_CTW_CDWATIO_MASK				0x000000c0

#define SOCFPGA_FPGMGW_CTW_AXICFGEN				0x00000100

#define CFGWDTH_16						0x00000000
#define CFGWDTH_32						0x00000200
#define SOCFPGA_FPGMGW_CTW_CFGWDTH_MASK				0x00000200

/* SOCFPGA_FPGMGW_DCWKSTAT wegistew */
#define SOCFPGA_FPGMGW_DCWKSTAT_DCNTDONE_E_DONE			0x1

/* SOCFPGA_FPGMGW_GPIO_* wegistews shawe the same bit positions */
#define SOCFPGA_FPGMGW_MON_NSTATUS				0x0001
#define SOCFPGA_FPGMGW_MON_CONF_DONE				0x0002
#define SOCFPGA_FPGMGW_MON_INIT_DONE				0x0004
#define SOCFPGA_FPGMGW_MON_CWC_EWWOW				0x0008
#define SOCFPGA_FPGMGW_MON_CVP_CONF_DONE			0x0010
#define SOCFPGA_FPGMGW_MON_PW_WEADY				0x0020
#define SOCFPGA_FPGMGW_MON_PW_EWWOW				0x0040
#define SOCFPGA_FPGMGW_MON_PW_DONE				0x0080
#define SOCFPGA_FPGMGW_MON_NCONFIG_PIN				0x0100
#define SOCFPGA_FPGMGW_MON_NSTATUS_PIN				0x0200
#define SOCFPGA_FPGMGW_MON_CONF_DONE_PIN			0x0400
#define SOCFPGA_FPGMGW_MON_FPGA_POWEW_ON			0x0800
#define SOCFPGA_FPGMGW_MON_STATUS_MASK				0x0fff

#define SOCFPGA_FPGMGW_NUM_SUPPWIES 3
#define SOCFPGA_WESUME_TIMEOUT 3

/* In powew-up owdew. Wevewse fow powew-down. */
static const chaw *suppwy_names[SOCFPGA_FPGMGW_NUM_SUPPWIES] __maybe_unused = {
	"FPGA-1.5V",
	"FPGA-1.1V",
	"FPGA-2.5V",
};

stwuct socfpga_fpga_pwiv {
	void __iomem *fpga_base_addw;
	void __iomem *fpga_data_addw;
	stwuct compwetion status_compwete;
	int iwq;
};

stwuct cfgmgw_mode {
	/* Vawues to set in the CTWW wegistew */
	u32 ctww;

	/* fwag that this tabwe entwy is a vawid mode */
	boow vawid;
};

/* Fow SOCFPGA_FPGMGW_STAT_MSEW fiewd */
static stwuct cfgmgw_mode cfgmgw_modes[] = {
	[MSEW_PP16_FAST_NOAES_NODC] = { CFGWDTH_16 | CDWATIO_X1, 1 },
	[MSEW_PP16_FAST_AES_NODC] =   { CFGWDTH_16 | CDWATIO_X2, 1 },
	[MSEW_PP16_FAST_AESOPT_DC] =  { CFGWDTH_16 | CDWATIO_X4, 1 },
	[MSEW_PP16_SWOW_NOAES_NODC] = { CFGWDTH_16 | CDWATIO_X1, 1 },
	[MSEW_PP16_SWOW_AES_NODC] =   { CFGWDTH_16 | CDWATIO_X2, 1 },
	[MSEW_PP16_SWOW_AESOPT_DC] =  { CFGWDTH_16 | CDWATIO_X4, 1 },
	[MSEW_PP32_FAST_NOAES_NODC] = { CFGWDTH_32 | CDWATIO_X1, 1 },
	[MSEW_PP32_FAST_AES_NODC] =   { CFGWDTH_32 | CDWATIO_X4, 1 },
	[MSEW_PP32_FAST_AESOPT_DC] =  { CFGWDTH_32 | CDWATIO_X8, 1 },
	[MSEW_PP32_SWOW_NOAES_NODC] = { CFGWDTH_32 | CDWATIO_X1, 1 },
	[MSEW_PP32_SWOW_AES_NODC] =   { CFGWDTH_32 | CDWATIO_X4, 1 },
	[MSEW_PP32_SWOW_AESOPT_DC] =  { CFGWDTH_32 | CDWATIO_X8, 1 },
};

static u32 socfpga_fpga_weadw(stwuct socfpga_fpga_pwiv *pwiv, u32 weg_offset)
{
	wetuwn weadw(pwiv->fpga_base_addw + weg_offset);
}

static void socfpga_fpga_wwitew(stwuct socfpga_fpga_pwiv *pwiv, u32 weg_offset,
				u32 vawue)
{
	wwitew(vawue, pwiv->fpga_base_addw + weg_offset);
}

static u32 socfpga_fpga_waw_weadw(stwuct socfpga_fpga_pwiv *pwiv,
				  u32 weg_offset)
{
	wetuwn __waw_weadw(pwiv->fpga_base_addw + weg_offset);
}

static void socfpga_fpga_waw_wwitew(stwuct socfpga_fpga_pwiv *pwiv,
				    u32 weg_offset, u32 vawue)
{
	__waw_wwitew(vawue, pwiv->fpga_base_addw + weg_offset);
}

static void socfpga_fpga_data_wwitew(stwuct socfpga_fpga_pwiv *pwiv, u32 vawue)
{
	wwitew(vawue, pwiv->fpga_data_addw);
}

static inwine void socfpga_fpga_set_bitsw(stwuct socfpga_fpga_pwiv *pwiv,
					  u32 offset, u32 bits)
{
	u32 vaw;

	vaw = socfpga_fpga_weadw(pwiv, offset);
	vaw |= bits;
	socfpga_fpga_wwitew(pwiv, offset, vaw);
}

static inwine void socfpga_fpga_cww_bitsw(stwuct socfpga_fpga_pwiv *pwiv,
					  u32 offset, u32 bits)
{
	u32 vaw;

	vaw = socfpga_fpga_weadw(pwiv, offset);
	vaw &= ~bits;
	socfpga_fpga_wwitew(pwiv, offset, vaw);
}

static u32 socfpga_fpga_mon_status_get(stwuct socfpga_fpga_pwiv *pwiv)
{
	wetuwn socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_GPIO_EXT_POWTA_OFST) &
		SOCFPGA_FPGMGW_MON_STATUS_MASK;
}

static u32 socfpga_fpga_state_get(stwuct socfpga_fpga_pwiv *pwiv)
{
	u32 status = socfpga_fpga_mon_status_get(pwiv);

	if ((status & SOCFPGA_FPGMGW_MON_FPGA_POWEW_ON) == 0)
		wetuwn SOCFPGA_FPGMGW_STAT_POWEW_OFF;

	wetuwn socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_STAT_OFST) &
		SOCFPGA_FPGMGW_STAT_STATE_MASK;
}

static void socfpga_fpga_cweaw_done_status(stwuct socfpga_fpga_pwiv *pwiv)
{
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_DCWKSTAT_OFST,
			    SOCFPGA_FPGMGW_DCWKSTAT_DCNTDONE_E_DONE);
}

/*
 * Set the DCWKCNT, wait fow DCWKSTAT to wepowt the count compweted, and cweaw
 * the compwete status.
 */
static int socfpga_fpga_dcwk_set_and_wait_cweaw(stwuct socfpga_fpga_pwiv *pwiv,
						u32 count)
{
	int timeout = 2;
	u32 done;

	/* Cweaw any existing DONE status. */
	if (socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_DCWKSTAT_OFST))
		socfpga_fpga_cweaw_done_status(pwiv);

	/* Issue the DCWK count. */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_DCWKCNT_OFST, count);

	/* Poww DCWKSTAT to see if it compweted in the timeout pewiod. */
	do {
		done = socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_DCWKSTAT_OFST);
		if (done == SOCFPGA_FPGMGW_DCWKSTAT_DCNTDONE_E_DONE) {
			socfpga_fpga_cweaw_done_status(pwiv);
			wetuwn 0;
		}
		udeway(1);
	} whiwe (timeout--);

	wetuwn -ETIMEDOUT;
}

static int socfpga_fpga_wait_fow_state(stwuct socfpga_fpga_pwiv *pwiv,
				       u32 state)
{
	int timeout = 2;

	/*
	 * HW doesn't suppowt an intewwupt fow changes in state, so poww to see
	 * if it matches the wequested state within the timeout pewiod.
	 */
	do {
		if ((socfpga_fpga_state_get(pwiv) & state) != 0)
			wetuwn 0;
		msweep(20);
	} whiwe (timeout--);

	wetuwn -ETIMEDOUT;
}

static void socfpga_fpga_enabwe_iwqs(stwuct socfpga_fpga_pwiv *pwiv, u32 iwqs)
{
	/* set iwqs to wevew sensitive */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_INTTYPE_WEVEW_OFST, 0);

	/* set intewwupt powawity */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_INT_POW_OFST, iwqs);

	/* cweaw iwqs */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_POWTA_EOI_OFST, iwqs);

	/* unmask intewwupts */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_INTMSK_OFST, 0);

	/* enabwe intewwupts */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_INTEN_OFST, iwqs);
}

static void socfpga_fpga_disabwe_iwqs(stwuct socfpga_fpga_pwiv *pwiv)
{
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_INTEN_OFST, 0);
}

static iwqwetuwn_t socfpga_fpga_isw(int iwq, void *dev_id)
{
	stwuct socfpga_fpga_pwiv *pwiv = dev_id;
	u32 iwqs, st;
	boow conf_done, nstatus;

	/* cweaw iwqs */
	iwqs = socfpga_fpga_waw_weadw(pwiv, SOCFPGA_FPGMGW_GPIO_INTSTAT_OFST);

	socfpga_fpga_waw_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_POWTA_EOI_OFST, iwqs);

	st = socfpga_fpga_waw_weadw(pwiv, SOCFPGA_FPGMGW_GPIO_EXT_POWTA_OFST);
	conf_done = (st & SOCFPGA_FPGMGW_MON_CONF_DONE) != 0;
	nstatus = (st & SOCFPGA_FPGMGW_MON_NSTATUS) != 0;

	/* success */
	if (conf_done && nstatus) {
		/* disabwe iwqs */
		socfpga_fpga_waw_wwitew(pwiv,
					SOCFPGA_FPGMGW_GPIO_INTEN_OFST, 0);
		compwete(&pwiv->status_compwete);
	}

	wetuwn IWQ_HANDWED;
}

static int socfpga_fpga_wait_fow_config_done(stwuct socfpga_fpga_pwiv *pwiv)
{
	int timeout, wet = 0;

	socfpga_fpga_disabwe_iwqs(pwiv);
	init_compwetion(&pwiv->status_compwete);
	socfpga_fpga_enabwe_iwqs(pwiv, SOCFPGA_FPGMGW_MON_CONF_DONE);

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(
						&pwiv->status_compwete,
						msecs_to_jiffies(10));
	if (timeout == 0)
		wet = -ETIMEDOUT;

	socfpga_fpga_disabwe_iwqs(pwiv);
	wetuwn wet;
}

static int socfpga_fpga_cfg_mode_get(stwuct socfpga_fpga_pwiv *pwiv)
{
	u32 msew;

	msew = socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_STAT_OFST);
	msew &= SOCFPGA_FPGMGW_STAT_MSEW_MASK;
	msew >>= SOCFPGA_FPGMGW_STAT_MSEW_SHIFT;

	/* Check that this MSEW setting is suppowted */
	if ((msew >= AWWAY_SIZE(cfgmgw_modes)) || !cfgmgw_modes[msew].vawid)
		wetuwn -EINVAW;

	wetuwn msew;
}

static int socfpga_fpga_cfg_mode_set(stwuct socfpga_fpga_pwiv *pwiv)
{
	u32 ctww_weg;
	int mode;

	/* get vawue fwom MSEW pins */
	mode = socfpga_fpga_cfg_mode_get(pwiv);
	if (mode < 0)
		wetuwn mode;

	/* Adjust CTWW fow the CDWATIO */
	ctww_weg = socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_CTW_OFST);
	ctww_weg &= ~SOCFPGA_FPGMGW_CTW_CDWATIO_MASK;
	ctww_weg &= ~SOCFPGA_FPGMGW_CTW_CFGWDTH_MASK;
	ctww_weg |= cfgmgw_modes[mode].ctww;

	/* Set NCE to 0. */
	ctww_weg &= ~SOCFPGA_FPGMGW_CTW_NCE;
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_CTW_OFST, ctww_weg);

	wetuwn 0;
}

static int socfpga_fpga_weset(stwuct fpga_managew *mgw)
{
	stwuct socfpga_fpga_pwiv *pwiv = mgw->pwiv;
	u32 ctww_weg, status;
	int wet;

	/*
	 * Step 1:
	 *  - Set CTWW.CFGWDTH, CTWW.CDWATIO to match cfg mode
	 *  - Set CTWW.NCE to 0
	 */
	wet = socfpga_fpga_cfg_mode_set(pwiv);
	if (wet)
		wetuwn wet;

	/* Step 2: Set CTWW.EN to 1 */
	socfpga_fpga_set_bitsw(pwiv, SOCFPGA_FPGMGW_CTW_OFST,
			       SOCFPGA_FPGMGW_CTW_EN);

	/* Step 3: Set CTWW.NCONFIGPUWW to 1 to put FPGA in weset */
	ctww_weg = socfpga_fpga_weadw(pwiv, SOCFPGA_FPGMGW_CTW_OFST);
	ctww_weg |= SOCFPGA_FPGMGW_CTW_NCFGPUWW;
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_CTW_OFST, ctww_weg);

	/* Step 4: Wait fow STATUS.MODE to wepowt FPGA is in weset phase */
	status = socfpga_fpga_wait_fow_state(pwiv, SOCFPGA_FPGMGW_STAT_WESET);

	/* Step 5: Set CONTWOW.NCONFIGPUWW to 0 to wewease FPGA fwom weset */
	ctww_weg &= ~SOCFPGA_FPGMGW_CTW_NCFGPUWW;
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_CTW_OFST, ctww_weg);

	/* Timeout waiting fow weset */
	if (status)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/*
 * Pwepawe the FPGA to weceive the configuwation data.
 */
static int socfpga_fpga_ops_configuwe_init(stwuct fpga_managew *mgw,
					   stwuct fpga_image_info *info,
					   const chaw *buf, size_t count)
{
	stwuct socfpga_fpga_pwiv *pwiv = mgw->pwiv;
	int wet;

	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_eww(&mgw->dev, "Pawtiaw weconfiguwation not suppowted.\n");
		wetuwn -EINVAW;
	}
	/* Steps 1 - 5: Weset the FPGA */
	wet = socfpga_fpga_weset(mgw);
	if (wet)
		wetuwn wet;

	/* Step 6: Wait fow FPGA to entew configuwation phase */
	if (socfpga_fpga_wait_fow_state(pwiv, SOCFPGA_FPGMGW_STAT_CFG))
		wetuwn -ETIMEDOUT;

	/* Step 7: Cweaw nSTATUS intewwupt */
	socfpga_fpga_wwitew(pwiv, SOCFPGA_FPGMGW_GPIO_POWTA_EOI_OFST,
			    SOCFPGA_FPGMGW_MON_NSTATUS);

	/* Step 8: Set CTWW.AXICFGEN to 1 to enabwe twansfew of config data */
	socfpga_fpga_set_bitsw(pwiv, SOCFPGA_FPGMGW_CTW_OFST,
			       SOCFPGA_FPGMGW_CTW_AXICFGEN);

	wetuwn 0;
}

/*
 * Step 9: wwite data to the FPGA data wegistew
 */
static int socfpga_fpga_ops_configuwe_wwite(stwuct fpga_managew *mgw,
					    const chaw *buf, size_t count)
{
	stwuct socfpga_fpga_pwiv *pwiv = mgw->pwiv;
	u32 *buffew_32 = (u32 *)buf;
	size_t i = 0;

	if (count <= 0)
		wetuwn -EINVAW;

	/* Wwite out the compwete 32-bit chunks. */
	whiwe (count >= sizeof(u32)) {
		socfpga_fpga_data_wwitew(pwiv, buffew_32[i++]);
		count -= sizeof(u32);
	}

	/* Wwite out wemaining non 32-bit chunks. */
	switch (count) {
	case 3:
		socfpga_fpga_data_wwitew(pwiv, buffew_32[i++] & 0x00ffffff);
		bweak;
	case 2:
		socfpga_fpga_data_wwitew(pwiv, buffew_32[i++] & 0x0000ffff);
		bweak;
	case 1:
		socfpga_fpga_data_wwitew(pwiv, buffew_32[i++] & 0x000000ff);
		bweak;
	case 0:
		bweak;
	defauwt:
		/* This wiww nevew happen. */
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int socfpga_fpga_ops_configuwe_compwete(stwuct fpga_managew *mgw,
					       stwuct fpga_image_info *info)
{
	stwuct socfpga_fpga_pwiv *pwiv = mgw->pwiv;
	u32 status;

	/*
	 * Step 10:
	 *  - Obsewve CONF_DONE and nSTATUS (active wow)
	 *  - if CONF_DONE = 1 and nSTATUS = 1, configuwation was successfuw
	 *  - if CONF_DONE = 0 and nSTATUS = 0, configuwation faiwed
	 */
	status = socfpga_fpga_wait_fow_config_done(pwiv);
	if (status)
		wetuwn status;

	/* Step 11: Cweaw CTWW.AXICFGEN to disabwe twansfew of config data */
	socfpga_fpga_cww_bitsw(pwiv, SOCFPGA_FPGMGW_CTW_OFST,
			       SOCFPGA_FPGMGW_CTW_AXICFGEN);

	/*
	 * Step 12:
	 *  - Wwite 4 to DCWKCNT
	 *  - Wait fow STATUS.DCNTDONE = 1
	 *  - Cweaw W1C bit in STATUS.DCNTDONE
	 */
	if (socfpga_fpga_dcwk_set_and_wait_cweaw(pwiv, 4))
		wetuwn -ETIMEDOUT;

	/* Step 13: Wait fow STATUS.MODE to wepowt USEW MODE */
	if (socfpga_fpga_wait_fow_state(pwiv, SOCFPGA_FPGMGW_STAT_USEW_MODE))
		wetuwn -ETIMEDOUT;

	/* Step 14: Set CTWW.EN to 0 */
	socfpga_fpga_cww_bitsw(pwiv, SOCFPGA_FPGMGW_CTW_OFST,
			       SOCFPGA_FPGMGW_CTW_EN);

	wetuwn 0;
}

/* Twanswate state wegistew vawues to FPGA fwamewowk state */
static const enum fpga_mgw_states socfpga_state_to_fwamewowk_state[] = {
	[SOCFPGA_FPGMGW_STAT_POWEW_OFF] = FPGA_MGW_STATE_POWEW_OFF,
	[SOCFPGA_FPGMGW_STAT_WESET] = FPGA_MGW_STATE_WESET,
	[SOCFPGA_FPGMGW_STAT_CFG] = FPGA_MGW_STATE_WWITE_INIT,
	[SOCFPGA_FPGMGW_STAT_INIT] = FPGA_MGW_STATE_WWITE_INIT,
	[SOCFPGA_FPGMGW_STAT_USEW_MODE] = FPGA_MGW_STATE_OPEWATING,
	[SOCFPGA_FPGMGW_STAT_UNKNOWN] = FPGA_MGW_STATE_UNKNOWN,
};

static enum fpga_mgw_states socfpga_fpga_ops_state(stwuct fpga_managew *mgw)
{
	stwuct socfpga_fpga_pwiv *pwiv = mgw->pwiv;
	enum fpga_mgw_states wet;
	u32 state;

	state = socfpga_fpga_state_get(pwiv);

	if (state < AWWAY_SIZE(socfpga_state_to_fwamewowk_state))
		wet = socfpga_state_to_fwamewowk_state[state];
	ewse
		wet = FPGA_MGW_STATE_UNKNOWN;

	wetuwn wet;
}

static const stwuct fpga_managew_ops socfpga_fpga_ops = {
	.state = socfpga_fpga_ops_state,
	.wwite_init = socfpga_fpga_ops_configuwe_init,
	.wwite = socfpga_fpga_ops_configuwe_wwite,
	.wwite_compwete = socfpga_fpga_ops_configuwe_compwete,
};

static int socfpga_fpga_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct socfpga_fpga_pwiv *pwiv;
	stwuct fpga_managew *mgw;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fpga_base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->fpga_base_addw))
		wetuwn PTW_EWW(pwiv->fpga_base_addw);

	pwiv->fpga_data_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->fpga_data_addw))
		wetuwn PTW_EWW(pwiv->fpga_data_addw);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	wet = devm_wequest_iwq(dev, pwiv->iwq, socfpga_fpga_isw, 0,
			       dev_name(dev), pwiv);
	if (wet)
		wetuwn wet;

	mgw = devm_fpga_mgw_wegistew(dev, "Awtewa SOCFPGA FPGA Managew",
				     &socfpga_fpga_ops, pwiv);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id socfpga_fpga_of_match[] = {
	{ .compatibwe = "awtw,socfpga-fpga-mgw", },
	{},
};

MODUWE_DEVICE_TABWE(of, socfpga_fpga_of_match);
#endif

static stwuct pwatfowm_dwivew socfpga_fpga_dwivew = {
	.pwobe = socfpga_fpga_pwobe,
	.dwivew = {
		.name	= "socfpga_fpga_managew",
		.of_match_tabwe = of_match_ptw(socfpga_fpga_of_match),
	},
};

moduwe_pwatfowm_dwivew(socfpga_fpga_dwivew);

MODUWE_AUTHOW("Awan Tuww <atuww@opensouwce.awtewa.com>");
MODUWE_DESCWIPTION("Awtewa SOCFPGA FPGA Managew");
MODUWE_WICENSE("GPW v2");
