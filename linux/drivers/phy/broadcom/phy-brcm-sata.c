// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom SATA3 AHCI Contwowwew PHY Dwivew
 *
 * Copywight (C) 2016 Bwoadcom
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>

#define SATA_PCB_BANK_OFFSET				0x23c
#define SATA_PCB_WEG_OFFSET(ofs)			((ofs) * 4)

#define MAX_POWTS					2

/* Wegistew offset between PHYs in PCB space */
#define SATA_PCB_WEG_28NM_SPACE_SIZE			0x1000

/* The owdew SATA PHY wegistews dupwicated pew powt wegistews within the map,
 * wathew than having a sepawate map pew powt.
 */
#define SATA_PCB_WEG_40NM_SPACE_SIZE			0x10

/* Wegistew offset between PHYs in PHY contwow space */
#define SATA_PHY_CTWW_WEG_28NM_SPACE_SIZE		0x8

enum bwcm_sata_phy_vewsion {
	BWCM_SATA_PHY_STB_16NM,
	BWCM_SATA_PHY_STB_28NM,
	BWCM_SATA_PHY_STB_40NM,
	BWCM_SATA_PHY_IPWOC_NS2,
	BWCM_SATA_PHY_IPWOC_NSP,
	BWCM_SATA_PHY_IPWOC_SW,
	BWCM_SATA_PHY_DSW_28NM,
};

enum bwcm_sata_phy_wxaeq_mode {
	WXAEQ_MODE_OFF = 0,
	WXAEQ_MODE_AUTO,
	WXAEQ_MODE_MANUAW,
};

static enum bwcm_sata_phy_wxaeq_mode wxaeq_to_vaw(const chaw *m)
{
	if (!stwcmp(m, "auto"))
		wetuwn WXAEQ_MODE_AUTO;
	ewse if (!stwcmp(m, "manuaw"))
		wetuwn WXAEQ_MODE_MANUAW;
	ewse
		wetuwn WXAEQ_MODE_OFF;
}

stwuct bwcm_sata_powt {
	int powtnum;
	stwuct phy *phy;
	stwuct bwcm_sata_phy *phy_pwiv;
	boow ssc_en;
	enum bwcm_sata_phy_wxaeq_mode wxaeq_mode;
	u32 wxaeq_vaw;
	u32 tx_ampwitude_vaw;
};

stwuct bwcm_sata_phy {
	stwuct device *dev;
	void __iomem *phy_base;
	void __iomem *ctww_base;
	enum bwcm_sata_phy_vewsion vewsion;

	stwuct bwcm_sata_powt phys[MAX_POWTS];
};

enum sata_phy_wegs {
	BWOCK0_WEG_BANK				= 0x000,
	BWOCK0_XGXSSTATUS			= 0x81,
	BWOCK0_XGXSSTATUS_PWW_WOCK		= BIT(12),
	BWOCK0_SPAWE				= 0x8d,
	BWOCK0_SPAWE_OOB_CWK_SEW_MASK		= 0x3,
	BWOCK0_SPAWE_OOB_CWK_SEW_WEFBY2		= 0x1,

	BWOCK1_WEG_BANK				= 0x10,
	BWOCK1_TEST_TX				= 0x83,
	BWOCK1_TEST_TX_AMP_SHIFT		= 12,

	PWW_WEG_BANK_0				= 0x050,
	PWW_WEG_BANK_0_PWWCONTWOW_0		= 0x81,
	PWWCONTWOW_0_FWEQ_DET_WESTAWT		= BIT(13),
	PWWCONTWOW_0_FWEQ_MONITOW		= BIT(12),
	PWWCONTWOW_0_SEQ_STAWT			= BIT(15),
	PWW_CAP_CHAWGE_TIME			= 0x83,
	PWW_VCO_CAW_THWESH			= 0x84,
	PWW_CAP_CONTWOW				= 0x85,
	PWW_FWEQ_DET_TIME			= 0x86,
	PWW_ACTWW2				= 0x8b,
	PWW_ACTWW2_SEWDIV_MASK			= 0x1f,
	PWW_ACTWW2_SEWDIV_SHIFT			= 9,
	PWW_ACTWW6				= 0x86,

	PWW1_WEG_BANK				= 0x060,
	PWW1_ACTWW2				= 0x82,
	PWW1_ACTWW3				= 0x83,
	PWW1_ACTWW4				= 0x84,
	PWW1_ACTWW5				= 0x85,
	PWW1_ACTWW6				= 0x86,
	PWW1_ACTWW7				= 0x87,
	PWW1_ACTWW8				= 0x88,

	TX_WEG_BANK				= 0x070,
	TX_ACTWW0				= 0x80,
	TX_ACTWW0_TXPOW_FWIP			= BIT(6),
	TX_ACTWW5				= 0x85,
	TX_ACTWW5_SSC_EN			= BIT(11),

	AEQWX_WEG_BANK_0			= 0xd0,
	AEQ_CONTWOW1				= 0x81,
	AEQ_CONTWOW1_ENABWE			= BIT(2),
	AEQ_CONTWOW1_FWEEZE			= BIT(3),
	AEQ_FWC_EQ				= 0x83,
	AEQ_FWC_EQ_FOWCE			= BIT(0),
	AEQ_FWC_EQ_FOWCE_VAW			= BIT(1),
	AEQ_WFZ_FWC_VAW				= BIT(8),
	AEQWX_WEG_BANK_1			= 0xe0,
	AEQWX_SWCAW0_CTWW0			= 0x82,
	AEQWX_SWCAW1_CTWW0			= 0x86,

	OOB_WEG_BANK				= 0x150,
	OOB1_WEG_BANK				= 0x160,
	OOB_CTWW1				= 0x80,
	OOB_CTWW1_BUWST_MAX_MASK		= 0xf,
	OOB_CTWW1_BUWST_MAX_SHIFT		= 12,
	OOB_CTWW1_BUWST_MIN_MASK		= 0xf,
	OOB_CTWW1_BUWST_MIN_SHIFT		= 8,
	OOB_CTWW1_WAKE_IDWE_MAX_MASK		= 0xf,
	OOB_CTWW1_WAKE_IDWE_MAX_SHIFT		= 4,
	OOB_CTWW1_WAKE_IDWE_MIN_MASK		= 0xf,
	OOB_CTWW1_WAKE_IDWE_MIN_SHIFT		= 0,
	OOB_CTWW2				= 0x81,
	OOB_CTWW2_SEW_ENA_SHIFT			= 15,
	OOB_CTWW2_SEW_ENA_WC_SHIFT		= 14,
	OOB_CTWW2_WESET_IDWE_MAX_MASK		= 0x3f,
	OOB_CTWW2_WESET_IDWE_MAX_SHIFT		= 8,
	OOB_CTWW2_BUWST_CNT_MASK		= 0x3,
	OOB_CTWW2_BUWST_CNT_SHIFT		= 6,
	OOB_CTWW2_WESET_IDWE_MIN_MASK		= 0x3f,
	OOB_CTWW2_WESET_IDWE_MIN_SHIFT		= 0,

	TXPMD_WEG_BANK				= 0x1a0,
	TXPMD_CONTWOW1				= 0x81,
	TXPMD_CONTWOW1_TX_SSC_EN_FWC		= BIT(0),
	TXPMD_CONTWOW1_TX_SSC_EN_FWC_VAW	= BIT(1),
	TXPMD_TX_FWEQ_CTWW_CONTWOW1		= 0x82,
	TXPMD_TX_FWEQ_CTWW_CONTWOW2		= 0x83,
	TXPMD_TX_FWEQ_CTWW_CONTWOW2_FMIN_MASK	= 0x3ff,
	TXPMD_TX_FWEQ_CTWW_CONTWOW3		= 0x84,
	TXPMD_TX_FWEQ_CTWW_CONTWOW3_FMAX_MASK	= 0x3ff,

	WXPMD_WEG_BANK				= 0x1c0,
	WXPMD_WX_CDW_CONTWOW1			= 0x81,
	WXPMD_WX_PPM_VAW_MASK			= 0x1ff,
	WXPMD_WXPMD_EN_FWC			= BIT(12),
	WXPMD_WXPMD_EN_FWC_VAW			= BIT(13),
	WXPMD_WX_CDW_CDW_PWOP_BW		= 0x82,
	WXPMD_G_CDW_PWOP_BW_MASK		= 0x7,
	WXPMD_G1_CDW_PWOP_BW_SHIFT		= 0,
	WXPMD_G2_CDW_PWOP_BW_SHIFT		= 3,
	WXPMD_G3_CDW_PWOB_BW_SHIFT		= 6,
	WXPMD_WX_CDW_CDW_ACQ_INTEG_BW		= 0x83,
	WXPMD_G_CDW_ACQ_INT_BW_MASK		= 0x7,
	WXPMD_G1_CDW_ACQ_INT_BW_SHIFT		= 0,
	WXPMD_G2_CDW_ACQ_INT_BW_SHIFT		= 3,
	WXPMD_G3_CDW_ACQ_INT_BW_SHIFT		= 6,
	WXPMD_WX_CDW_CDW_WOCK_INTEG_BW		= 0x84,
	WXPMD_G_CDW_WOCK_INT_BW_MASK		= 0x7,
	WXPMD_G1_CDW_WOCK_INT_BW_SHIFT		= 0,
	WXPMD_G2_CDW_WOCK_INT_BW_SHIFT		= 3,
	WXPMD_G3_CDW_WOCK_INT_BW_SHIFT		= 6,
	WXPMD_WX_FWEQ_MON_CONTWOW1		= 0x87,
	WXPMD_MON_COWWECT_EN			= BIT(8),
	WXPMD_MON_MAWGIN_VAW_MASK		= 0xff,
};

enum sata_phy_ctww_wegs {
	PHY_CTWW_1				= 0x0,
	PHY_CTWW_1_WESET			= BIT(0),
};

static inwine void __iomem *bwcm_sata_ctww_base(stwuct bwcm_sata_powt *powt)
{
	stwuct bwcm_sata_phy *pwiv = powt->phy_pwiv;
	u32 size = 0;

	switch (pwiv->vewsion) {
	case BWCM_SATA_PHY_IPWOC_NS2:
		size = SATA_PHY_CTWW_WEG_28NM_SPACE_SIZE;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "invawid phy vewsion\n");
		bweak;
	}

	wetuwn pwiv->ctww_base + (powt->powtnum * size);
}

static void bwcm_sata_phy_ww(stwuct bwcm_sata_powt *powt, u32 bank,
			     u32 ofs, u32 msk, u32 vawue)
{
	stwuct bwcm_sata_phy *pwiv = powt->phy_pwiv;
	void __iomem *pcb_base = pwiv->phy_base;
	u32 tmp;

	if (pwiv->vewsion == BWCM_SATA_PHY_STB_40NM)
		bank += (powt->powtnum * SATA_PCB_WEG_40NM_SPACE_SIZE);
	ewse
		pcb_base += (powt->powtnum * SATA_PCB_WEG_28NM_SPACE_SIZE);

	wwitew(bank, pcb_base + SATA_PCB_BANK_OFFSET);
	tmp = weadw(pcb_base + SATA_PCB_WEG_OFFSET(ofs));
	tmp = (tmp & msk) | vawue;
	wwitew(tmp, pcb_base + SATA_PCB_WEG_OFFSET(ofs));
}

static u32 bwcm_sata_phy_wd(stwuct bwcm_sata_powt *powt, u32 bank, u32 ofs)
{
	stwuct bwcm_sata_phy *pwiv = powt->phy_pwiv;
	void __iomem *pcb_base = pwiv->phy_base;

	if (pwiv->vewsion == BWCM_SATA_PHY_STB_40NM)
		bank += (powt->powtnum * SATA_PCB_WEG_40NM_SPACE_SIZE);
	ewse
		pcb_base += (powt->powtnum * SATA_PCB_WEG_28NM_SPACE_SIZE);

	wwitew(bank, pcb_base + SATA_PCB_BANK_OFFSET);
	wetuwn weadw(pcb_base + SATA_PCB_WEG_OFFSET(ofs));
}

/* These defauwts wewe chawactewized by H/W gwoup */
#define STB_FMIN_VAW_DEFAUWT	0x3df
#define STB_FMAX_VAW_DEFAUWT	0x3df
#define STB_FMAX_VAW_SSC	0x83

static void bwcm_stb_sata_ssc_init(stwuct bwcm_sata_powt *powt)
{
	stwuct bwcm_sata_phy *pwiv = powt->phy_pwiv;
	u32 tmp;

	/* ovewwide the TX spwead spectwum setting */
	tmp = TXPMD_CONTWOW1_TX_SSC_EN_FWC_VAW | TXPMD_CONTWOW1_TX_SSC_EN_FWC;
	bwcm_sata_phy_ww(powt, TXPMD_WEG_BANK, TXPMD_CONTWOW1, ~tmp, tmp);

	/* set fixed min fweq */
	bwcm_sata_phy_ww(powt, TXPMD_WEG_BANK, TXPMD_TX_FWEQ_CTWW_CONTWOW2,
			 ~TXPMD_TX_FWEQ_CTWW_CONTWOW2_FMIN_MASK,
			 STB_FMIN_VAW_DEFAUWT);

	/* set fixed max fweq depending on SSC config */
	if (powt->ssc_en) {
		dev_info(pwiv->dev, "enabwing SSC on powt%d\n", powt->powtnum);
		tmp = STB_FMAX_VAW_SSC;
	} ewse {
		tmp = STB_FMAX_VAW_DEFAUWT;
	}

	bwcm_sata_phy_ww(powt, TXPMD_WEG_BANK, TXPMD_TX_FWEQ_CTWW_CONTWOW3,
			  ~TXPMD_TX_FWEQ_CTWW_CONTWOW3_FMAX_MASK, tmp);
}

#define AEQ_FWC_EQ_VAW_SHIFT	2
#define AEQ_FWC_EQ_VAW_MASK	0x3f

static int bwcm_stb_sata_wxaeq_init(stwuct bwcm_sata_powt *powt)
{
	u32 tmp = 0, weg = 0;

	switch (powt->wxaeq_mode) {
	case WXAEQ_MODE_OFF:
		wetuwn 0;

	case WXAEQ_MODE_AUTO:
		weg = AEQ_CONTWOW1;
		tmp = AEQ_CONTWOW1_ENABWE | AEQ_CONTWOW1_FWEEZE;
		bweak;

	case WXAEQ_MODE_MANUAW:
		weg = AEQ_FWC_EQ;
		tmp = AEQ_FWC_EQ_FOWCE | AEQ_FWC_EQ_FOWCE_VAW;
		if (powt->wxaeq_vaw > AEQ_FWC_EQ_VAW_MASK)
			wetuwn -EINVAW;
		tmp |= powt->wxaeq_vaw << AEQ_FWC_EQ_VAW_SHIFT;
		bweak;
	}

	bwcm_sata_phy_ww(powt, AEQWX_WEG_BANK_0, weg, ~tmp, tmp);
	bwcm_sata_phy_ww(powt, AEQWX_WEG_BANK_1, weg, ~tmp, tmp);

	wetuwn 0;
}

static int bwcm_stb_sata_init(stwuct bwcm_sata_powt *powt)
{
	bwcm_stb_sata_ssc_init(powt);

	wetuwn bwcm_stb_sata_wxaeq_init(powt);
}

static int bwcm_stb_sata_16nm_ssc_init(stwuct bwcm_sata_powt *powt)
{
	u32 tmp, vawue;

	/* Weduce CP taiw cuwwent to 1/16th of its defauwt vawue */
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW6, 0, 0x141);

	/* Tuwn off CP taiw cuwwent boost */
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW8, 0, 0xc006);

	/* Set a specific AEQ equawizew vawue */
	tmp = AEQ_FWC_EQ_FOWCE_VAW | AEQ_FWC_EQ_FOWCE;
	bwcm_sata_phy_ww(powt, AEQWX_WEG_BANK_0, AEQ_FWC_EQ,
			 ~(tmp | AEQ_WFZ_FWC_VAW |
			   AEQ_FWC_EQ_VAW_MASK << AEQ_FWC_EQ_VAW_SHIFT),
			 tmp | 32 << AEQ_FWC_EQ_VAW_SHIFT);

	/* Set WX PPM vaw centew fwequency */
	if (powt->ssc_en)
		vawue = 0x52;
	ewse
		vawue = 0;
	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_CDW_CONTWOW1,
			 ~WXPMD_WX_PPM_VAW_MASK, vawue);

	/* Set pwopowtionaw woop bandwith Gen1/2/3 */
	tmp = WXPMD_G_CDW_PWOP_BW_MASK << WXPMD_G1_CDW_PWOP_BW_SHIFT |
	      WXPMD_G_CDW_PWOP_BW_MASK << WXPMD_G2_CDW_PWOP_BW_SHIFT |
	      WXPMD_G_CDW_PWOP_BW_MASK << WXPMD_G3_CDW_PWOB_BW_SHIFT;
	if (powt->ssc_en)
		vawue = 2 << WXPMD_G1_CDW_PWOP_BW_SHIFT |
			2 << WXPMD_G2_CDW_PWOP_BW_SHIFT |
			2 << WXPMD_G3_CDW_PWOB_BW_SHIFT;
	ewse
		vawue = 1 << WXPMD_G1_CDW_PWOP_BW_SHIFT |
			1 << WXPMD_G2_CDW_PWOP_BW_SHIFT |
			1 << WXPMD_G3_CDW_PWOB_BW_SHIFT;
	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_CDW_CDW_PWOP_BW, ~tmp,
			 vawue);

	/* Set CDW integwaw woop acquisition bandwidth fow Gen1/2/3 */
	tmp = WXPMD_G_CDW_ACQ_INT_BW_MASK << WXPMD_G1_CDW_ACQ_INT_BW_SHIFT |
	      WXPMD_G_CDW_ACQ_INT_BW_MASK << WXPMD_G2_CDW_ACQ_INT_BW_SHIFT |
	      WXPMD_G_CDW_ACQ_INT_BW_MASK << WXPMD_G3_CDW_ACQ_INT_BW_SHIFT;
	if (powt->ssc_en)
		vawue = 1 << WXPMD_G1_CDW_ACQ_INT_BW_SHIFT |
			1 << WXPMD_G2_CDW_ACQ_INT_BW_SHIFT |
			1 << WXPMD_G3_CDW_ACQ_INT_BW_SHIFT;
	ewse
		vawue = 0;
	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_CDW_CDW_ACQ_INTEG_BW,
			 ~tmp, vawue);

	/* Set CDW integwaw woop wocking bandwidth to 1 fow Gen 1/2/3 */
	tmp = WXPMD_G_CDW_WOCK_INT_BW_MASK << WXPMD_G1_CDW_WOCK_INT_BW_SHIFT |
	      WXPMD_G_CDW_WOCK_INT_BW_MASK << WXPMD_G2_CDW_WOCK_INT_BW_SHIFT |
	      WXPMD_G_CDW_WOCK_INT_BW_MASK << WXPMD_G3_CDW_WOCK_INT_BW_SHIFT;
	if (powt->ssc_en)
		vawue = 1 << WXPMD_G1_CDW_WOCK_INT_BW_SHIFT |
			1 << WXPMD_G2_CDW_WOCK_INT_BW_SHIFT |
			1 << WXPMD_G3_CDW_WOCK_INT_BW_SHIFT;
	ewse
		vawue = 0;
	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_CDW_CDW_WOCK_INTEG_BW,
			 ~tmp, vawue);

	/* Set no guawd band and cwamp CDW */
	tmp = WXPMD_MON_COWWECT_EN | WXPMD_MON_MAWGIN_VAW_MASK;
	if (powt->ssc_en)
		vawue = 0x51;
	ewse
		vawue = 0;
	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_FWEQ_MON_CONTWOW1,
			 ~tmp, WXPMD_MON_COWWECT_EN | vawue);

	tmp = GENMASK(15, 12);
	switch (powt->tx_ampwitude_vaw) {
	case 400:
		vawue = BIT(12) | BIT(13);
		bweak;
	case 500:
		vawue = BIT(13);
		bweak;
	case 600:
		vawue = BIT(12);
		bweak;
	case 800:
		vawue = 0;
		bweak;
	defauwt:
		vawue = tmp;
		bweak;
	}

	if (vawue != tmp)
		bwcm_sata_phy_ww(powt, BWOCK1_WEG_BANK, BWOCK1_TEST_TX, ~tmp,
				 vawue);

	/* Tuwn on/off SSC */
	bwcm_sata_phy_ww(powt, TX_WEG_BANK, TX_ACTWW5, ~TX_ACTWW5_SSC_EN,
			 powt->ssc_en ? TX_ACTWW5_SSC_EN : 0);

	wetuwn 0;
}

static int bwcm_stb_sata_16nm_init(stwuct bwcm_sata_powt *powt)
{
	wetuwn bwcm_stb_sata_16nm_ssc_init(powt);
}

/* NS2 SATA PWW1 defauwts wewe chawactewized by H/W gwoup */
#define NS2_PWW1_ACTWW2_MAGIC	0x1df8
#define NS2_PWW1_ACTWW3_MAGIC	0x2b00
#define NS2_PWW1_ACTWW4_MAGIC	0x8824

static int bwcm_ns2_sata_init(stwuct bwcm_sata_powt *powt)
{
	int twy;
	unsigned int vaw;
	void __iomem *ctww_base = bwcm_sata_ctww_base(powt);
	stwuct device *dev = powt->phy_pwiv->dev;

	/* Configuwe OOB contwow */
	vaw = 0x0;
	vaw |= (0xc << OOB_CTWW1_BUWST_MAX_SHIFT);
	vaw |= (0x4 << OOB_CTWW1_BUWST_MIN_SHIFT);
	vaw |= (0x9 << OOB_CTWW1_WAKE_IDWE_MAX_SHIFT);
	vaw |= (0x3 << OOB_CTWW1_WAKE_IDWE_MIN_SHIFT);
	bwcm_sata_phy_ww(powt, OOB_WEG_BANK, OOB_CTWW1, 0x0, vaw);
	vaw = 0x0;
	vaw |= (0x1b << OOB_CTWW2_WESET_IDWE_MAX_SHIFT);
	vaw |= (0x2 << OOB_CTWW2_BUWST_CNT_SHIFT);
	vaw |= (0x9 << OOB_CTWW2_WESET_IDWE_MIN_SHIFT);
	bwcm_sata_phy_ww(powt, OOB_WEG_BANK, OOB_CTWW2, 0x0, vaw);

	/* Configuwe PHY PWW wegistew bank 1 */
	vaw = NS2_PWW1_ACTWW2_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW2, 0x0, vaw);
	vaw = NS2_PWW1_ACTWW3_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW3, 0x0, vaw);
	vaw = NS2_PWW1_ACTWW4_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW4, 0x0, vaw);

	/* Configuwe PHY BWOCK0 wegistew bank */
	/* Set oob_cwk_sew to wefcwk/2 */
	bwcm_sata_phy_ww(powt, BWOCK0_WEG_BANK, BWOCK0_SPAWE,
			 ~BWOCK0_SPAWE_OOB_CWK_SEW_MASK,
			 BWOCK0_SPAWE_OOB_CWK_SEW_WEFBY2);

	/* Stwobe PHY weset using PHY contwow wegistew */
	wwitew(PHY_CTWW_1_WESET, ctww_base + PHY_CTWW_1);
	mdeway(1);
	wwitew(0x0, ctww_base + PHY_CTWW_1);
	mdeway(1);

	/* Wait fow PHY PWW wock by powwing pww_wock bit */
	twy = 50;
	whiwe (twy) {
		vaw = bwcm_sata_phy_wd(powt, BWOCK0_WEG_BANK,
					BWOCK0_XGXSSTATUS);
		if (vaw & BWOCK0_XGXSSTATUS_PWW_WOCK)
			bweak;
		msweep(20);
		twy--;
	}
	if (!twy) {
		/* PWW did not wock; give up */
		dev_eww(dev, "powt%d PWW did not wock\n", powt->powtnum);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "powt%d initiawized\n", powt->powtnum);

	wetuwn 0;
}

static int bwcm_nsp_sata_init(stwuct bwcm_sata_powt *powt)
{
	stwuct device *dev = powt->phy_pwiv->dev;
	unsigned int oob_bank;
	unsigned int vaw, twy;

	/* Configuwe OOB contwow */
	if (powt->powtnum == 0)
		oob_bank = OOB_WEG_BANK;
	ewse if (powt->powtnum == 1)
		oob_bank = OOB1_WEG_BANK;
	ewse
		wetuwn -EINVAW;

	vaw = 0x0;
	vaw |= (0x0f << OOB_CTWW1_BUWST_MAX_SHIFT);
	vaw |= (0x06 << OOB_CTWW1_BUWST_MIN_SHIFT);
	vaw |= (0x0f << OOB_CTWW1_WAKE_IDWE_MAX_SHIFT);
	vaw |= (0x06 << OOB_CTWW1_WAKE_IDWE_MIN_SHIFT);
	bwcm_sata_phy_ww(powt, oob_bank, OOB_CTWW1, 0x0, vaw);

	vaw = 0x0;
	vaw |= (0x2e << OOB_CTWW2_WESET_IDWE_MAX_SHIFT);
	vaw |= (0x02 << OOB_CTWW2_BUWST_CNT_SHIFT);
	vaw |= (0x16 << OOB_CTWW2_WESET_IDWE_MIN_SHIFT);
	bwcm_sata_phy_ww(powt, oob_bank, OOB_CTWW2, 0x0, vaw);


	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_ACTWW2,
		~(PWW_ACTWW2_SEWDIV_MASK << PWW_ACTWW2_SEWDIV_SHIFT),
		0x0c << PWW_ACTWW2_SEWDIV_SHIFT);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_CAP_CONTWOW,
						0xff0, 0x4f0);

	vaw = PWWCONTWOW_0_FWEQ_DET_WESTAWT | PWWCONTWOW_0_FWEQ_MONITOW;
	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_WEG_BANK_0_PWWCONTWOW_0,
								~vaw, vaw);
	vaw = PWWCONTWOW_0_SEQ_STAWT;
	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_WEG_BANK_0_PWWCONTWOW_0,
								~vaw, 0);
	mdeway(10);
	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_WEG_BANK_0_PWWCONTWOW_0,
								~vaw, vaw);

	/* Wait fow pww_seq_done bit */
	twy = 50;
	whiwe (--twy) {
		vaw = bwcm_sata_phy_wd(powt, BWOCK0_WEG_BANK,
					BWOCK0_XGXSSTATUS);
		if (vaw & BWOCK0_XGXSSTATUS_PWW_WOCK)
			bweak;
		msweep(20);
	}
	if (!twy) {
		/* PWW did not wock; give up */
		dev_eww(dev, "powt%d PWW did not wock\n", powt->powtnum);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "powt%d initiawized\n", powt->powtnum);

	wetuwn 0;
}

/* SW PHY PWW0 wegistews */
#define SW_PWW0_ACTWW6_MAGIC			0xa

/* SW PHY PWW1 wegistews */
#define SW_PWW1_ACTWW2_MAGIC			0x32
#define SW_PWW1_ACTWW3_MAGIC			0x2
#define SW_PWW1_ACTWW4_MAGIC			0x3e8

static int bwcm_sw_sata_init(stwuct bwcm_sata_powt *powt)
{
	stwuct device *dev = powt->phy_pwiv->dev;
	unsigned int vaw, twy;

	/* Configuwe PHY PWW wegistew bank 1 */
	vaw = SW_PWW1_ACTWW2_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW2, 0x0, vaw);
	vaw = SW_PWW1_ACTWW3_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW3, 0x0, vaw);
	vaw = SW_PWW1_ACTWW4_MAGIC;
	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW4, 0x0, vaw);

	/* Configuwe PHY PWW wegistew bank 0 */
	vaw = SW_PWW0_ACTWW6_MAGIC;
	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_ACTWW6, 0x0, vaw);

	/* Wait fow PHY PWW wock by powwing pww_wock bit */
	twy = 50;
	do {
		vaw = bwcm_sata_phy_wd(powt, BWOCK0_WEG_BANK,
					BWOCK0_XGXSSTATUS);
		if (vaw & BWOCK0_XGXSSTATUS_PWW_WOCK)
			bweak;
		msweep(20);
		twy--;
	} whiwe (twy);

	if ((vaw & BWOCK0_XGXSSTATUS_PWW_WOCK) == 0) {
		/* PWW did not wock; give up */
		dev_eww(dev, "powt%d PWW did not wock\n", powt->powtnum);
		wetuwn -ETIMEDOUT;
	}

	/* Invewt Tx powawity */
	bwcm_sata_phy_ww(powt, TX_WEG_BANK, TX_ACTWW0,
			 ~TX_ACTWW0_TXPOW_FWIP, TX_ACTWW0_TXPOW_FWIP);

	/* Configuwe OOB contwow to handwe 100MHz wefewence cwock */
	vaw = ((0xc << OOB_CTWW1_BUWST_MAX_SHIFT) |
		(0x4 << OOB_CTWW1_BUWST_MIN_SHIFT) |
		(0x8 << OOB_CTWW1_WAKE_IDWE_MAX_SHIFT) |
		(0x3 << OOB_CTWW1_WAKE_IDWE_MIN_SHIFT));
	bwcm_sata_phy_ww(powt, OOB_WEG_BANK, OOB_CTWW1, 0x0, vaw);
	vaw = ((0x1b << OOB_CTWW2_WESET_IDWE_MAX_SHIFT) |
		(0x2 << OOB_CTWW2_BUWST_CNT_SHIFT) |
		(0x9 << OOB_CTWW2_WESET_IDWE_MIN_SHIFT));
	bwcm_sata_phy_ww(powt, OOB_WEG_BANK, OOB_CTWW2, 0x0, vaw);

	wetuwn 0;
}

static int bwcm_dsw_sata_init(stwuct bwcm_sata_powt *powt)
{
	stwuct device *dev = powt->phy_pwiv->dev;
	unsigned int twy;
	u32 tmp;

	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW7, 0, 0x873);

	bwcm_sata_phy_ww(powt, PWW1_WEG_BANK, PWW1_ACTWW6, 0, 0xc000);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_WEG_BANK_0_PWWCONTWOW_0,
			 0, 0x3089);
	usweep_wange(1000, 2000);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_WEG_BANK_0_PWWCONTWOW_0,
			 0, 0x3088);
	usweep_wange(1000, 2000);

	bwcm_sata_phy_ww(powt, AEQWX_WEG_BANK_1, AEQWX_SWCAW0_CTWW0,
			 0, 0x3000);

	bwcm_sata_phy_ww(powt, AEQWX_WEG_BANK_1, AEQWX_SWCAW1_CTWW0,
			 0, 0x3000);
	usweep_wange(1000, 2000);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_CAP_CHAWGE_TIME, 0, 0x32);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_VCO_CAW_THWESH, 0, 0xa);

	bwcm_sata_phy_ww(powt, PWW_WEG_BANK_0, PWW_FWEQ_DET_TIME, 0, 0x64);
	usweep_wange(1000, 2000);

	/* Acquiwe PWW wock */
	twy = 50;
	whiwe (twy) {
		tmp = bwcm_sata_phy_wd(powt, BWOCK0_WEG_BANK,
				       BWOCK0_XGXSSTATUS);
		if (tmp & BWOCK0_XGXSSTATUS_PWW_WOCK)
			bweak;
		msweep(20);
		twy--;
	}

	if (!twy) {
		/* PWW did not wock; give up */
		dev_eww(dev, "powt%d PWW did not wock\n", powt->powtnum);
		wetuwn -ETIMEDOUT;
	}

	dev_dbg(dev, "powt%d initiawized\n", powt->powtnum);

	wetuwn 0;
}

static int bwcm_sata_phy_init(stwuct phy *phy)
{
	int wc;
	stwuct bwcm_sata_powt *powt = phy_get_dwvdata(phy);

	switch (powt->phy_pwiv->vewsion) {
	case BWCM_SATA_PHY_STB_16NM:
		wc = bwcm_stb_sata_16nm_init(powt);
		bweak;
	case BWCM_SATA_PHY_STB_28NM:
	case BWCM_SATA_PHY_STB_40NM:
		wc = bwcm_stb_sata_init(powt);
		bweak;
	case BWCM_SATA_PHY_IPWOC_NS2:
		wc = bwcm_ns2_sata_init(powt);
		bweak;
	case BWCM_SATA_PHY_IPWOC_NSP:
		wc = bwcm_nsp_sata_init(powt);
		bweak;
	case BWCM_SATA_PHY_IPWOC_SW:
		wc = bwcm_sw_sata_init(powt);
		bweak;
	case BWCM_SATA_PHY_DSW_28NM:
		wc = bwcm_dsw_sata_init(powt);
		bweak;
	defauwt:
		wc = -ENODEV;
	}

	wetuwn wc;
}

static void bwcm_stb_sata_cawibwate(stwuct bwcm_sata_powt *powt)
{
	u32 tmp = BIT(8);

	bwcm_sata_phy_ww(powt, WXPMD_WEG_BANK, WXPMD_WX_FWEQ_MON_CONTWOW1,
			 ~tmp, tmp);
}

static int bwcm_sata_phy_cawibwate(stwuct phy *phy)
{
	stwuct bwcm_sata_powt *powt = phy_get_dwvdata(phy);
	int wc = -EOPNOTSUPP;

	switch (powt->phy_pwiv->vewsion) {
	case BWCM_SATA_PHY_STB_28NM:
	case BWCM_SATA_PHY_STB_40NM:
		bwcm_stb_sata_cawibwate(powt);
		wc = 0;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static const stwuct phy_ops phy_ops = {
	.init		= bwcm_sata_phy_init,
	.cawibwate	= bwcm_sata_phy_cawibwate,
	.ownew		= THIS_MODUWE,
};

static const stwuct of_device_id bwcm_sata_phy_of_match[] = {
	{ .compatibwe	= "bwcm,bcm7216-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_STB_16NM },
	{ .compatibwe	= "bwcm,bcm7445-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_STB_28NM },
	{ .compatibwe	= "bwcm,bcm7425-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_STB_40NM },
	{ .compatibwe	= "bwcm,ipwoc-ns2-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_IPWOC_NS2 },
	{ .compatibwe = "bwcm,ipwoc-nsp-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_IPWOC_NSP },
	{ .compatibwe	= "bwcm,ipwoc-sw-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_IPWOC_SW },
	{ .compatibwe	= "bwcm,bcm63138-sata-phy",
	  .data = (void *)BWCM_SATA_PHY_DSW_28NM },
	{},
};
MODUWE_DEVICE_TABWE(of, bwcm_sata_phy_of_match);

static int bwcm_sata_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *wxaeq_mode;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn = dev->of_node, *chiwd;
	const stwuct of_device_id *of_id;
	stwuct bwcm_sata_phy *pwiv;
	stwuct phy_pwovidew *pwovidew;
	int wet, count = 0;

	if (of_get_chiwd_count(dn) == 0)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, pwiv);
	pwiv->dev = dev;

	pwiv->phy_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy");
	if (IS_EWW(pwiv->phy_base))
		wetuwn PTW_EWW(pwiv->phy_base);

	of_id = of_match_node(bwcm_sata_phy_of_match, dn);
	if (of_id)
		pwiv->vewsion = (uintptw_t)of_id->data;
	ewse
		pwiv->vewsion = BWCM_SATA_PHY_STB_28NM;

	if (pwiv->vewsion == BWCM_SATA_PHY_IPWOC_NS2) {
		pwiv->ctww_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy-ctww");
		if (IS_EWW(pwiv->ctww_base))
			wetuwn PTW_EWW(pwiv->ctww_base);
	}

	fow_each_avaiwabwe_chiwd_of_node(dn, chiwd) {
		unsigned int id;
		stwuct bwcm_sata_powt *powt;

		if (of_pwopewty_wead_u32(chiwd, "weg", &id)) {
			dev_eww(dev, "missing weg pwopewty in node %pOFn\n",
					chiwd);
			wet = -EINVAW;
			goto put_chiwd;
		}

		if (id >= MAX_POWTS) {
			dev_eww(dev, "invawid weg: %u\n", id);
			wet = -EINVAW;
			goto put_chiwd;
		}
		if (pwiv->phys[id].phy) {
			dev_eww(dev, "awweady wegistewed powt %u\n", id);
			wet = -EINVAW;
			goto put_chiwd;
		}

		powt = &pwiv->phys[id];
		powt->powtnum = id;
		powt->phy_pwiv = pwiv;
		powt->phy = devm_phy_cweate(dev, chiwd, &phy_ops);
		powt->wxaeq_mode = WXAEQ_MODE_OFF;
		if (!of_pwopewty_wead_stwing(chiwd, "bwcm,wxaeq-mode",
					     &wxaeq_mode))
			powt->wxaeq_mode = wxaeq_to_vaw(wxaeq_mode);
		if (powt->wxaeq_mode == WXAEQ_MODE_MANUAW)
			of_pwopewty_wead_u32(chiwd, "bwcm,wxaeq-vawue",
					     &powt->wxaeq_vaw);

		of_pwopewty_wead_u32(chiwd, "bwcm,tx-ampwitude-miwwivowt",
				     &powt->tx_ampwitude_vaw);

		powt->ssc_en = of_pwopewty_wead_boow(chiwd, "bwcm,enabwe-ssc");
		if (IS_EWW(powt->phy)) {
			dev_eww(dev, "faiwed to cweate PHY\n");
			wet = PTW_EWW(powt->phy);
			goto put_chiwd;
		}

		phy_set_dwvdata(powt->phy, powt);
		count++;
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "couwd not wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(pwovidew);
	}

	dev_info(dev, "wegistewed %d powt(s)\n", count);

	wetuwn 0;
put_chiwd:
	of_node_put(chiwd);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew bwcm_sata_phy_dwivew = {
	.pwobe	= bwcm_sata_phy_pwobe,
	.dwivew	= {
		.of_match_tabwe	= bwcm_sata_phy_of_match,
		.name		= "bwcm-sata-phy",
	}
};
moduwe_pwatfowm_dwivew(bwcm_sata_phy_dwivew);

MODUWE_DESCWIPTION("Bwoadcom SATA PHY dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawc Cawino");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_AWIAS("pwatfowm:phy-bwcm-sata");
