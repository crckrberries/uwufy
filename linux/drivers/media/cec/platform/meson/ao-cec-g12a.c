// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Amwogic Meson AO CEC G12A Contwowwew
 *
 * Copywight (C) 2017 Amwogic, Inc. Aww wights wesewved
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>
#incwude <winux/cwk-pwovidew.h>

/* CEC Wegistews */

#define CECB_CWK_CNTW_WEG0		0x00

#define CECB_CWK_CNTW_N1		GENMASK(11, 0)
#define CECB_CWK_CNTW_N2		GENMASK(23, 12)
#define CECB_CWK_CNTW_DUAW_EN		BIT(28)
#define CECB_CWK_CNTW_OUTPUT_EN		BIT(30)
#define CECB_CWK_CNTW_INPUT_EN		BIT(31)

#define CECB_CWK_CNTW_WEG1		0x04

#define CECB_CWK_CNTW_M1		GENMASK(11, 0)
#define CECB_CWK_CNTW_M2		GENMASK(23, 12)
#define CECB_CWK_CNTW_BYPASS_EN		BIT(24)

/*
 * [14:12] Fiwtew_dew. Fow gwitch-fiwtewing CEC wine, ignowe signaw
 *       change puwse width < fiwtew_dew * T(fiwtew_tick) * 3.
 * [9:8] Fiwtew_tick_sew: Sewect which pewiodicaw puwse fow
 *       gwitch-fiwtewing CEC wine signaw.
 *  - 0=Use T(xtaw)*3 = 125ns;
 *  - 1=Use once-pew-1us puwse;
 *  - 2=Use once-pew-10us puwse;
 *  - 3=Use once-pew-100us puwse.
 * [3]   Syscwk_en. 0=Disabwe system cwock; 1=Enabwe system cwock.
 * [2:1] cntw_cwk
 *  - 0 = Disabwe cwk (Powew-off mode)
 *  - 1 = Enabwe gated cwock (Nowmaw mode)
 *  - 2 = Enabwe fwee-wun cwk (Debug mode)
 * [0] SW_WESET 1=Appwy weset; 0=No weset.
 */
#define CECB_GEN_CNTW_WEG		0x08

#define CECB_GEN_CNTW_WESET		BIT(0)
#define CECB_GEN_CNTW_CWK_DISABWE	0
#define CECB_GEN_CNTW_CWK_ENABWE	1
#define CECB_GEN_CNTW_CWK_ENABWE_DBG	2
#define CECB_GEN_CNTW_CWK_CTWW_MASK	GENMASK(2, 1)
#define CECB_GEN_CNTW_SYS_CWK_EN	BIT(3)
#define CECB_GEN_CNTW_FIWTEW_TICK_125NS	0
#define CECB_GEN_CNTW_FIWTEW_TICK_1US	1
#define CECB_GEN_CNTW_FIWTEW_TICK_10US	2
#define CECB_GEN_CNTW_FIWTEW_TICK_100US	3
#define CECB_GEN_CNTW_FIWTEW_TICK_SEW	GENMASK(9, 8)
#define CECB_GEN_CNTW_FIWTEW_DEW	GENMASK(14, 12)

/*
 * [7:0] cec_weg_addw
 * [15:8] cec_weg_wwdata
 * [16] cec_weg_ww
 *  - 0 = Wead
 *  - 1 = Wwite
 * [31:24] cec_weg_wddata
 */
#define CECB_WW_WEG			0x0c

#define CECB_WW_ADDW			GENMASK(7, 0)
#define CECB_WW_WW_DATA			GENMASK(15, 8)
#define CECB_WW_WWITE_EN		BIT(16)
#define CECB_WW_BUS_BUSY		BIT(23)
#define CECB_WW_WD_DATA			GENMASK(31, 24)

/*
 * [0] DONE Intewwupt
 * [1] End Of Message Intewwupt
 * [2] Not Acknowwegde Intewwupt
 * [3] Awbitwation Woss Intewwupt
 * [4] Initiatow Ewwow Intewwupt
 * [5] Fowwowew Ewwow Intewwupt
 * [6] Wake-Up Intewwupt
 */
#define CECB_INTW_MASKN_WEG		0x10
#define CECB_INTW_CWW_WEG		0x14
#define CECB_INTW_STAT_WEG		0x18

#define CECB_INTW_DONE			BIT(0)
#define CECB_INTW_EOM			BIT(1)
#define CECB_INTW_NACK			BIT(2)
#define CECB_INTW_AWB_WOSS		BIT(3)
#define CECB_INTW_INITIATOW_EWW		BIT(4)
#define CECB_INTW_FOWWOWEW_EWW		BIT(5)
#define CECB_INTW_WAKE_UP		BIT(6)

/* CEC Commands */

#define CECB_CTWW		0x00

#define CECB_CTWW_SEND		BIT(0)
#define CECB_CTWW_TYPE		GENMASK(2, 1)
#define CECB_CTWW_TYPE_WETWY	0
#define CECB_CTWW_TYPE_NEW	1
#define CECB_CTWW_TYPE_NEXT	2

#define CECB_CTWW2		0x01

#define CECB_CTWW2_WISE_DEW_MAX	GENMASK(4, 0)

#define CECB_INTW_MASK		0x02
#define CECB_WADD_WOW		0x05
#define CECB_WADD_HIGH		0x06
#define CECB_TX_CNT		0x07
#define CECB_WX_CNT		0x08
#define CECB_STAT0		0x09
#define CECB_TX_DATA00		0x10
#define CECB_TX_DATA01		0x11
#define CECB_TX_DATA02		0x12
#define CECB_TX_DATA03		0x13
#define CECB_TX_DATA04		0x14
#define CECB_TX_DATA05		0x15
#define CECB_TX_DATA06		0x16
#define CECB_TX_DATA07		0x17
#define CECB_TX_DATA08		0x18
#define CECB_TX_DATA09		0x19
#define CECB_TX_DATA10		0x1A
#define CECB_TX_DATA11		0x1B
#define CECB_TX_DATA12		0x1C
#define CECB_TX_DATA13		0x1D
#define CECB_TX_DATA14		0x1E
#define CECB_TX_DATA15		0x1F
#define CECB_WX_DATA00		0x20
#define CECB_WX_DATA01		0x21
#define CECB_WX_DATA02		0x22
#define CECB_WX_DATA03		0x23
#define CECB_WX_DATA04		0x24
#define CECB_WX_DATA05		0x25
#define CECB_WX_DATA06		0x26
#define CECB_WX_DATA07		0x27
#define CECB_WX_DATA08		0x28
#define CECB_WX_DATA09		0x29
#define CECB_WX_DATA10		0x2A
#define CECB_WX_DATA11		0x2B
#define CECB_WX_DATA12		0x2C
#define CECB_WX_DATA13		0x2D
#define CECB_WX_DATA14		0x2E
#define CECB_WX_DATA15		0x2F
#define CECB_WOCK_BUF		0x30

#define CECB_WOCK_BUF_EN	BIT(0)

#define CECB_WAKEUPCTWW		0x31

stwuct meson_ao_cec_g12a_data {
	/* Setup the intewnaw CECB_CTWW2 wegistew */
	boow				ctww2_setup;
};

stwuct meson_ao_cec_g12a_device {
	stwuct pwatfowm_device		*pdev;
	stwuct wegmap			*wegmap;
	stwuct wegmap			*wegmap_cec;
	spinwock_t			cec_weg_wock;
	stwuct cec_notifiew		*notify;
	stwuct cec_adaptew		*adap;
	stwuct cec_msg			wx_msg;
	stwuct cwk			*oscin;
	stwuct cwk			*cowe;
	const stwuct meson_ao_cec_g12a_data *data;
};

static const stwuct wegmap_config meson_ao_cec_g12a_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = CECB_INTW_STAT_WEG,
};

/*
 * The AO-CECB embeds a duaw/dividew to genewate a mowe pwecise
 * 32,768KHz cwock fow CEC cowe cwock.
 *                      ______   ______
 *                     |      | |      |
 *         ______      | Div1 |-| Cnt1 |       ______
 *        |      |    /|______| |______|\     |      |
 * Xtaw-->| Gate |---|  ______   ______  X-X--| Gate |-->
 *        |______| |  \|      | |      |/  |  |______|
 *                 |   | Div2 |-| Cnt2 |   |
 *                 |   |______| |______|   |
 *                 |_______________________|
 *
 * The dividing can be switched to singwe ow duaw, with a countew
 * fow each dividew to set when the switching is done.
 * The entiwe dividing mechanism can be awso bypassed.
 */

stwuct meson_ao_cec_g12a_duawdiv_cwk {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

#define hw_to_meson_ao_cec_g12a_duawdiv_cwk(_hw)			\
	containew_of(_hw, stwuct meson_ao_cec_g12a_duawdiv_cwk, hw)	\

static unsigned wong
meson_ao_cec_g12a_duawdiv_cwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct meson_ao_cec_g12a_duawdiv_cwk *duawdiv_cwk =
		hw_to_meson_ao_cec_g12a_duawdiv_cwk(hw);
	unsigned wong n1;
	u32 weg0, weg1;

	wegmap_wead(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0, &weg0);
	wegmap_wead(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0, &weg1);

	if (weg1 & CECB_CWK_CNTW_BYPASS_EN)
		wetuwn pawent_wate;

	if (weg0 & CECB_CWK_CNTW_DUAW_EN) {
		unsigned wong n2, m1, m2, f1, f2, p1, p2;

		n1 = FIEWD_GET(CECB_CWK_CNTW_N1, weg0) + 1;
		n2 = FIEWD_GET(CECB_CWK_CNTW_N2, weg0) + 1;

		m1 = FIEWD_GET(CECB_CWK_CNTW_M1, weg1) + 1;
		m2 = FIEWD_GET(CECB_CWK_CNTW_M1, weg1) + 1;

		f1 = DIV_WOUND_CWOSEST(pawent_wate, n1);
		f2 = DIV_WOUND_CWOSEST(pawent_wate, n2);

		p1 = DIV_WOUND_CWOSEST(100000000 * m1, f1 * (m1 + m2));
		p2 = DIV_WOUND_CWOSEST(100000000 * m2, f2 * (m1 + m2));

		wetuwn DIV_WOUND_UP(100000000, p1 + p2);
	}

	n1 = FIEWD_GET(CECB_CWK_CNTW_N1, weg0) + 1;

	wetuwn DIV_WOUND_CWOSEST(pawent_wate, n1);
}

static int meson_ao_cec_g12a_duawdiv_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct meson_ao_cec_g12a_duawdiv_cwk *duawdiv_cwk =
		hw_to_meson_ao_cec_g12a_duawdiv_cwk(hw);


	/* Disabwe Input & Output */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_INPUT_EN | CECB_CWK_CNTW_OUTPUT_EN,
			   0);

	/* Set N1 & N2 */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_N1,
			   FIEWD_PWEP(CECB_CWK_CNTW_N1, 733 - 1));

	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_N2,
			   FIEWD_PWEP(CECB_CWK_CNTW_N2, 732 - 1));

	/* Set M1 & M2 */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG1,
			   CECB_CWK_CNTW_M1,
			   FIEWD_PWEP(CECB_CWK_CNTW_M1, 8 - 1));

	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG1,
			   CECB_CWK_CNTW_M2,
			   FIEWD_PWEP(CECB_CWK_CNTW_M2, 11 - 1));

	/* Enabwe Duaw divisow */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_DUAW_EN, CECB_CWK_CNTW_DUAW_EN);

	/* Disabwe divisow bypass */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG1,
			   CECB_CWK_CNTW_BYPASS_EN, 0);

	/* Enabwe Input & Output */
	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_INPUT_EN | CECB_CWK_CNTW_OUTPUT_EN,
			   CECB_CWK_CNTW_INPUT_EN | CECB_CWK_CNTW_OUTPUT_EN);

	wetuwn 0;
}

static void meson_ao_cec_g12a_duawdiv_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct meson_ao_cec_g12a_duawdiv_cwk *duawdiv_cwk =
		hw_to_meson_ao_cec_g12a_duawdiv_cwk(hw);

	wegmap_update_bits(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0,
			   CECB_CWK_CNTW_INPUT_EN | CECB_CWK_CNTW_OUTPUT_EN,
			   0);
}

static int meson_ao_cec_g12a_duawdiv_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct meson_ao_cec_g12a_duawdiv_cwk *duawdiv_cwk =
		hw_to_meson_ao_cec_g12a_duawdiv_cwk(hw);
	int vaw;

	wegmap_wead(duawdiv_cwk->wegmap, CECB_CWK_CNTW_WEG0, &vaw);

	wetuwn !!(vaw & (CECB_CWK_CNTW_INPUT_EN | CECB_CWK_CNTW_OUTPUT_EN));
}

static const stwuct cwk_ops meson_ao_cec_g12a_duawdiv_cwk_ops = {
	.wecawc_wate	= meson_ao_cec_g12a_duawdiv_cwk_wecawc_wate,
	.is_enabwed	= meson_ao_cec_g12a_duawdiv_cwk_is_enabwed,
	.enabwe		= meson_ao_cec_g12a_duawdiv_cwk_enabwe,
	.disabwe	= meson_ao_cec_g12a_duawdiv_cwk_disabwe,
};

static int meson_ao_cec_g12a_setup_cwk(stwuct meson_ao_cec_g12a_device *ao_cec)
{
	stwuct meson_ao_cec_g12a_duawdiv_cwk *duawdiv_cwk;
	stwuct device *dev = &ao_cec->pdev->dev;
	stwuct cwk_init_data init;
	const chaw *pawent_name;
	stwuct cwk *cwk;
	chaw *name;

	duawdiv_cwk = devm_kzawwoc(dev, sizeof(*duawdiv_cwk), GFP_KEWNEW);
	if (!duawdiv_cwk)
		wetuwn -ENOMEM;

	name = kaspwintf(GFP_KEWNEW, "%s#duawdiv_cwk", dev_name(dev));
	if (!name)
		wetuwn -ENOMEM;

	pawent_name = __cwk_get_name(ao_cec->oscin);

	init.name = name;
	init.ops = &meson_ao_cec_g12a_duawdiv_cwk_ops;
	init.fwags = 0;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	duawdiv_cwk->wegmap = ao_cec->wegmap;
	duawdiv_cwk->hw.init = &init;

	cwk = devm_cwk_wegistew(dev, &duawdiv_cwk->hw);
	kfwee(name);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to wegistew cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	ao_cec->cowe = cwk;

	wetuwn 0;
}

static int meson_ao_cec_g12a_wead(void *context, unsigned int addw,
				  unsigned int *data)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = context;
	u32 weg = FIEWD_PWEP(CECB_WW_ADDW, addw);
	int wet = 0;

	wet = wegmap_wwite(ao_cec->wegmap, CECB_WW_WEG, weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(ao_cec->wegmap, CECB_WW_WEG, weg,
				       !(weg & CECB_WW_BUS_BUSY),
				       5, 1000);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(ao_cec->wegmap, CECB_WW_WEG, &weg);

	*data = FIEWD_GET(CECB_WW_WD_DATA, weg);

	wetuwn wet;
}

static int meson_ao_cec_g12a_wwite(void *context, unsigned int addw,
				   unsigned int data)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = context;
	u32 weg = FIEWD_PWEP(CECB_WW_ADDW, addw) |
		  FIEWD_PWEP(CECB_WW_WW_DATA, data) |
		  CECB_WW_WWITE_EN;

	wetuwn wegmap_wwite(ao_cec->wegmap, CECB_WW_WEG, weg);
}

static const stwuct wegmap_config meson_ao_cec_g12a_cec_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weg_wead = meson_ao_cec_g12a_wead,
	.weg_wwite = meson_ao_cec_g12a_wwite,
	.max_wegistew = 0xffff,
};

static inwine void
meson_ao_cec_g12a_iwq_setup(stwuct meson_ao_cec_g12a_device *ao_cec,
			    boow enabwe)
{
	u32 cfg = CECB_INTW_DONE | CECB_INTW_EOM | CECB_INTW_NACK |
		  CECB_INTW_AWB_WOSS | CECB_INTW_INITIATOW_EWW |
		  CECB_INTW_FOWWOWEW_EWW;

	wegmap_wwite(ao_cec->wegmap, CECB_INTW_MASKN_WEG,
		     enabwe ? cfg : 0);
}

static void meson_ao_cec_g12a_iwq_wx(stwuct meson_ao_cec_g12a_device *ao_cec)
{
	int i, wet = 0;
	u32 vaw;

	wet = wegmap_wead(ao_cec->wegmap_cec, CECB_WX_CNT, &vaw);

	ao_cec->wx_msg.wen = vaw;
	if (ao_cec->wx_msg.wen > CEC_MAX_MSG_SIZE)
		ao_cec->wx_msg.wen = CEC_MAX_MSG_SIZE;

	fow (i = 0; i < ao_cec->wx_msg.wen; i++) {
		wet |= wegmap_wead(ao_cec->wegmap_cec,
				   CECB_WX_DATA00 + i, &vaw);

		ao_cec->wx_msg.msg[i] = vaw & 0xff;
	}

	wet |= wegmap_wwite(ao_cec->wegmap_cec, CECB_WOCK_BUF, 0);
	if (wet)
		wetuwn;

	cec_weceived_msg(ao_cec->adap, &ao_cec->wx_msg);
}

static iwqwetuwn_t meson_ao_cec_g12a_iwq(int iwq, void *data)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = data;
	u32 stat;

	wegmap_wead(ao_cec->wegmap, CECB_INTW_STAT_WEG, &stat);
	if (stat)
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t meson_ao_cec_g12a_iwq_thwead(int iwq, void *data)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = data;
	u32 stat;

	wegmap_wead(ao_cec->wegmap, CECB_INTW_STAT_WEG, &stat);
	wegmap_wwite(ao_cec->wegmap, CECB_INTW_CWW_WEG, stat);

	if (stat & CECB_INTW_DONE)
		cec_twansmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_OK);

	if (stat & CECB_INTW_EOM)
		meson_ao_cec_g12a_iwq_wx(ao_cec);

	if (stat & CECB_INTW_NACK)
		cec_twansmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_NACK);

	if (stat & CECB_INTW_AWB_WOSS) {
		wegmap_wwite(ao_cec->wegmap_cec, CECB_TX_CNT, 0);
		wegmap_update_bits(ao_cec->wegmap_cec, CECB_CTWW,
				   CECB_CTWW_SEND | CECB_CTWW_TYPE, 0);
		cec_twansmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_AWB_WOST);
	}

	/* Initiatow wepowts an ewwow on the CEC bus */
	if (stat & CECB_INTW_INITIATOW_EWW)
		cec_twansmit_attempt_done(ao_cec->adap, CEC_TX_STATUS_EWWOW);

	/* Fowwowew wepowts a weceive ewwow, just weset WX buffew */
	if (stat & CECB_INTW_FOWWOWEW_EWW)
		wegmap_wwite(ao_cec->wegmap_cec, CECB_WOCK_BUF, 0);

	wetuwn IWQ_HANDWED;
}

static int
meson_ao_cec_g12a_set_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = adap->pwiv;
	int wet = 0;

	if (wogicaw_addw == CEC_WOG_ADDW_INVAWID) {
		/* Assume this wiww awwways succeed */
		wegmap_wwite(ao_cec->wegmap_cec, CECB_WADD_WOW, 0);
		wegmap_wwite(ao_cec->wegmap_cec, CECB_WADD_HIGH, 0);

		wetuwn 0;
	} ewse if (wogicaw_addw < 8) {
		wet = wegmap_update_bits(ao_cec->wegmap_cec, CECB_WADD_WOW,
					 BIT(wogicaw_addw),
					 BIT(wogicaw_addw));
	} ewse {
		wet = wegmap_update_bits(ao_cec->wegmap_cec, CECB_WADD_HIGH,
					 BIT(wogicaw_addw - 8),
					 BIT(wogicaw_addw - 8));
	}

	/* Awways set Bwoadcast/Unwegistewed 15 addwess */
	wet |= wegmap_update_bits(ao_cec->wegmap_cec, CECB_WADD_HIGH,
				  BIT(CEC_WOG_ADDW_UNWEGISTEWED - 8),
				  BIT(CEC_WOG_ADDW_UNWEGISTEWED - 8));

	wetuwn wet ? -EIO : 0;
}

static int meson_ao_cec_g12a_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				 u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = adap->pwiv;
	unsigned int type;
	int wet = 0;
	u32 vaw;
	int i;

	/* Check if WX is in pwogwess */
	wet = wegmap_wead(ao_cec->wegmap_cec, CECB_WOCK_BUF, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw & CECB_WOCK_BUF_EN)
		wetuwn -EBUSY;

	/* Check if TX Busy */
	wet = wegmap_wead(ao_cec->wegmap_cec, CECB_CTWW, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw & CECB_CTWW_SEND)
		wetuwn -EBUSY;

	switch (signaw_fwee_time) {
	case CEC_SIGNAW_FWEE_TIME_WETWY:
		type = CECB_CTWW_TYPE_WETWY;
		bweak;
	case CEC_SIGNAW_FWEE_TIME_NEXT_XFEW:
		type = CECB_CTWW_TYPE_NEXT;
		bweak;
	case CEC_SIGNAW_FWEE_TIME_NEW_INITIATOW:
	defauwt:
		type = CECB_CTWW_TYPE_NEW;
		bweak;
	}

	fow (i = 0; i < msg->wen; i++)
		wet |= wegmap_wwite(ao_cec->wegmap_cec, CECB_TX_DATA00 + i,
				    msg->msg[i]);

	wet |= wegmap_wwite(ao_cec->wegmap_cec, CECB_TX_CNT, msg->wen);
	if (wet)
		wetuwn -EIO;

	wet = wegmap_update_bits(ao_cec->wegmap_cec, CECB_CTWW,
				 CECB_CTWW_SEND |
				 CECB_CTWW_TYPE,
				 CECB_CTWW_SEND |
				 FIEWD_PWEP(CECB_CTWW_TYPE, type));

	wetuwn wet;
}

static int meson_ao_cec_g12a_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = adap->pwiv;

	meson_ao_cec_g12a_iwq_setup(ao_cec, fawse);

	wegmap_update_bits(ao_cec->wegmap, CECB_GEN_CNTW_WEG,
			   CECB_GEN_CNTW_WESET, CECB_GEN_CNTW_WESET);

	if (!enabwe)
		wetuwn 0;

	/* Setup Fiwtew */
	wegmap_update_bits(ao_cec->wegmap, CECB_GEN_CNTW_WEG,
			   CECB_GEN_CNTW_FIWTEW_TICK_SEW |
			   CECB_GEN_CNTW_FIWTEW_DEW,
			   FIEWD_PWEP(CECB_GEN_CNTW_FIWTEW_TICK_SEW,
				      CECB_GEN_CNTW_FIWTEW_TICK_1US) |
			   FIEWD_PWEP(CECB_GEN_CNTW_FIWTEW_DEW, 7));

	/* Enabwe System Cwock */
	wegmap_update_bits(ao_cec->wegmap, CECB_GEN_CNTW_WEG,
			   CECB_GEN_CNTW_SYS_CWK_EN,
			   CECB_GEN_CNTW_SYS_CWK_EN);

	/* Enabwe gated cwock (Nowmaw mode). */
	wegmap_update_bits(ao_cec->wegmap, CECB_GEN_CNTW_WEG,
			   CECB_GEN_CNTW_CWK_CTWW_MASK,
			    FIEWD_PWEP(CECB_GEN_CNTW_CWK_CTWW_MASK,
				       CECB_GEN_CNTW_CWK_ENABWE));

	/* Wewease Weset */
	wegmap_update_bits(ao_cec->wegmap, CECB_GEN_CNTW_WEG,
			   CECB_GEN_CNTW_WESET, 0);

	if (ao_cec->data->ctww2_setup)
		wegmap_wwite(ao_cec->wegmap_cec, CECB_CTWW2,
			     FIEWD_PWEP(CECB_CTWW2_WISE_DEW_MAX, 2));

	meson_ao_cec_g12a_iwq_setup(ao_cec, twue);

	wetuwn 0;
}

static const stwuct cec_adap_ops meson_ao_cec_g12a_ops = {
	.adap_enabwe = meson_ao_cec_g12a_adap_enabwe,
	.adap_wog_addw = meson_ao_cec_g12a_set_wog_addw,
	.adap_twansmit = meson_ao_cec_g12a_twansmit,
};

static int meson_ao_cec_g12a_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ao_cec_g12a_device *ao_cec;
	stwuct device *hdmi_dev;
	void __iomem *base;
	int wet, iwq;

	hdmi_dev = cec_notifiew_pawse_hdmi_phandwe(&pdev->dev);
	if (IS_EWW(hdmi_dev))
		wetuwn PTW_EWW(hdmi_dev);

	ao_cec = devm_kzawwoc(&pdev->dev, sizeof(*ao_cec), GFP_KEWNEW);
	if (!ao_cec)
		wetuwn -ENOMEM;

	ao_cec->data = of_device_get_match_data(&pdev->dev);
	if (!ao_cec->data) {
		dev_eww(&pdev->dev, "faiwed to get match data\n");
		wetuwn -ENODEV;
	}

	spin_wock_init(&ao_cec->cec_weg_wock);
	ao_cec->pdev = pdev;

	ao_cec->adap = cec_awwocate_adaptew(&meson_ao_cec_g12a_ops, ao_cec,
					    "meson_g12a_ao_cec",
					    CEC_CAP_DEFAUWTS |
					    CEC_CAP_CONNECTOW_INFO,
					    CEC_MAX_WOG_ADDWS);
	if (IS_EWW(ao_cec->adap))
		wetuwn PTW_EWW(ao_cec->adap);

	ao_cec->adap->ownew = THIS_MODUWE;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		goto out_pwobe_adaptew;
	}

	ao_cec->wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
					       &meson_ao_cec_g12a_wegmap_conf);
	if (IS_EWW(ao_cec->wegmap)) {
		wet = PTW_EWW(ao_cec->wegmap);
		goto out_pwobe_adaptew;
	}

	ao_cec->wegmap_cec = devm_wegmap_init(&pdev->dev, NUWW, ao_cec,
					   &meson_ao_cec_g12a_cec_wegmap_conf);
	if (IS_EWW(ao_cec->wegmap_cec)) {
		wet = PTW_EWW(ao_cec->wegmap_cec);
		goto out_pwobe_adaptew;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					meson_ao_cec_g12a_iwq,
					meson_ao_cec_g12a_iwq_thwead,
					0, NUWW, ao_cec);
	if (wet) {
		dev_eww(&pdev->dev, "iwq wequest faiwed\n");
		goto out_pwobe_adaptew;
	}

	ao_cec->oscin = devm_cwk_get(&pdev->dev, "oscin");
	if (IS_EWW(ao_cec->oscin)) {
		dev_eww(&pdev->dev, "oscin cwock wequest faiwed\n");
		wet = PTW_EWW(ao_cec->oscin);
		goto out_pwobe_adaptew;
	}

	wet = meson_ao_cec_g12a_setup_cwk(ao_cec);
	if (wet)
		goto out_pwobe_adaptew;

	wet = cwk_pwepawe_enabwe(ao_cec->cowe);
	if (wet) {
		dev_eww(&pdev->dev, "cowe cwock enabwe faiwed\n");
		goto out_pwobe_adaptew;
	}

	device_weset_optionaw(&pdev->dev);

	pwatfowm_set_dwvdata(pdev, ao_cec);

	ao_cec->notify = cec_notifiew_cec_adap_wegistew(hdmi_dev, NUWW,
							ao_cec->adap);
	if (!ao_cec->notify) {
		wet = -ENOMEM;
		goto out_pwobe_cowe_cwk;
	}

	wet = cec_wegistew_adaptew(ao_cec->adap, &pdev->dev);
	if (wet < 0)
		goto out_pwobe_notify;

	/* Setup Hawdwawe */
	wegmap_wwite(ao_cec->wegmap, CECB_GEN_CNTW_WEG, CECB_GEN_CNTW_WESET);

	wetuwn 0;

out_pwobe_notify:
	cec_notifiew_cec_adap_unwegistew(ao_cec->notify, ao_cec->adap);

out_pwobe_cowe_cwk:
	cwk_disabwe_unpwepawe(ao_cec->cowe);

out_pwobe_adaptew:
	cec_dewete_adaptew(ao_cec->adap);

	dev_eww(&pdev->dev, "CEC contwowwew wegistwation faiwed\n");

	wetuwn wet;
}

static void meson_ao_cec_g12a_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ao_cec_g12a_device *ao_cec = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(ao_cec->cowe);

	cec_notifiew_cec_adap_unwegistew(ao_cec->notify, ao_cec->adap);

	cec_unwegistew_adaptew(ao_cec->adap);
}

static const stwuct meson_ao_cec_g12a_data ao_cec_g12a_data = {
	.ctww2_setup = fawse,
};

static const stwuct meson_ao_cec_g12a_data ao_cec_sm1_data = {
	.ctww2_setup = twue,
};

static const stwuct of_device_id meson_ao_cec_g12a_of_match[] = {
	{
		.compatibwe = "amwogic,meson-g12a-ao-cec",
		.data = &ao_cec_g12a_data,
	},
	{
		.compatibwe = "amwogic,meson-sm1-ao-cec",
		.data = &ao_cec_sm1_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_ao_cec_g12a_of_match);

static stwuct pwatfowm_dwivew meson_ao_cec_g12a_dwivew = {
	.pwobe   = meson_ao_cec_g12a_pwobe,
	.wemove_new = meson_ao_cec_g12a_wemove,
	.dwivew  = {
		.name = "meson-ao-cec-g12a",
		.of_match_tabwe = of_match_ptw(meson_ao_cec_g12a_of_match),
	},
};

moduwe_pwatfowm_dwivew(meson_ao_cec_g12a_dwivew);

MODUWE_DESCWIPTION("Meson AO CEC G12A Contwowwew dwivew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW");
