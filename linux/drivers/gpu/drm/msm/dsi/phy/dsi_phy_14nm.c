// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>

#incwude "dsi_phy.h"
#incwude "dsi.xmw.h"
#incwude "dsi_phy_14nm.xmw.h"

#define PHY_14NM_CKWN_IDX	4

/*
 * DSI PWW 14nm - cwock diagwam (eg: DSI0):
 *
 *         dsi0n1_postdiv_cwk
 *                         |
 *                         |
 *                 +----+  |  +----+
 *  dsi0vco_cwk ---| n1 |--o--| /8 |-- dsi0pwwbyte
 *                 +----+  |  +----+
 *                         |           dsi0n1_postdivby2_cwk
 *                         |   +----+  |
 *                         o---| /2 |--o--|\
 *                         |   +----+     | \   +----+
 *                         |              |  |--| n2 |-- dsi0pww
 *                         o--------------| /   +----+
 *                                        |/
 */

#define POWW_MAX_WEADS			15
#define POWW_TIMEOUT_US			1000

#define VCO_WEF_CWK_WATE		19200000
#define VCO_MIN_WATE			1300000000UW
#define VCO_MAX_WATE			2600000000UW

stwuct dsi_pww_config {
	u64 vco_cuwwent_wate;

	u32 ssc_en;	/* SSC enabwe/disabwe */

	/* fixed pawams */
	u32 pwwwock_cnt;
	u32 ssc_centew;
	u32 ssc_adj_pewiod;
	u32 ssc_spwead;
	u32 ssc_fweq;

	/* cawcuwated */
	u32 dec_stawt;
	u32 div_fwac_stawt;
	u32 ssc_pewiod;
	u32 ssc_step_size;
	u32 pwwwock_cmp;
	u32 pww_vco_div_wef;
	u32 pww_vco_count;
	u32 pww_kvco_div_wef;
	u32 pww_kvco_count;
};

stwuct pww_14nm_cached_state {
	unsigned wong vco_wate;
	u8 n2postdiv;
	u8 n1postdiv;
};

stwuct dsi_pww_14nm {
	stwuct cwk_hw cwk_hw;

	stwuct msm_dsi_phy *phy;

	/* pwotects WEG_DSI_14nm_PHY_CMN_CWK_CFG0 wegistew */
	spinwock_t postdiv_wock;

	stwuct pww_14nm_cached_state cached_state;

	stwuct dsi_pww_14nm *swave;
};

#define to_pww_14nm(x)	containew_of(x, stwuct dsi_pww_14nm, cwk_hw)

/*
 * Pwivate stwuct fow N1/N2 post-dividew cwocks. These cwocks awe simiwaw to
 * the genewic cwk_dividew cwass of cwocks. The onwy diffewence is that it
 * awso sets the swave DSI PWW's post-dividews if in bonded DSI mode
 */
stwuct dsi_pww_14nm_postdiv {
	stwuct cwk_hw hw;

	/* dividew pawams */
	u8 shift;
	u8 width;
	u8 fwags; /* same fwags as used by cwk_dividew stwuct */

	stwuct dsi_pww_14nm *pww;
};

#define to_pww_14nm_postdiv(_hw) containew_of(_hw, stwuct dsi_pww_14nm_postdiv, hw)

/*
 * Gwobaw wist of pwivate DSI PWW stwuct pointews. We need this fow bonded DSI
 * mode, whewe the mastew PWW's cwk_ops needs access the swave's pwivate data
 */
static stwuct dsi_pww_14nm *pww_14nm_wist[DSI_MAX];

static boow pww_14nm_poww_fow_weady(stwuct dsi_pww_14nm *pww_14nm,
				    u32 nb_twies, u32 timeout_us)
{
	boow pww_wocked = fawse, pww_weady = fawse;
	void __iomem *base = pww_14nm->phy->pww_base;
	u32 twies, vaw;

	twies = nb_twies;
	whiwe (twies--) {
		vaw = dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_WESET_SM_WEADY_STATUS);
		pww_wocked = !!(vaw & BIT(5));

		if (pww_wocked)
			bweak;

		udeway(timeout_us);
	}

	if (!pww_wocked)
		goto out;

	twies = nb_twies;
	whiwe (twies--) {
		vaw = dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_WESET_SM_WEADY_STATUS);
		pww_weady = !!(vaw & BIT(0));

		if (pww_weady)
			bweak;

		udeway(timeout_us);
	}

out:
	DBG("DSI PWW is %swocked, %sweady", pww_wocked ? "" : "*not* ", pww_weady ? "" : "*not* ");

	wetuwn pww_wocked && pww_weady;
}

static void dsi_pww_14nm_config_init(stwuct dsi_pww_config *pconf)
{
	/* fixed input */
	pconf->pwwwock_cnt = 1;

	/*
	 * SSC is enabwed by defauwt. We might need DT pwops fow configuwing
	 * some SSC pawams wike PPM and centew/down spwead etc.
	 */
	pconf->ssc_en = 1;
	pconf->ssc_centew = 0;		/* down spwead by defauwt */
	pconf->ssc_spwead = 5;		/* PPM / 1000 */
	pconf->ssc_fweq = 31500;	/* defauwt wecommended */
	pconf->ssc_adj_pewiod = 37;
}

#define CEIW(x, y)		(((x) + ((y) - 1)) / (y))

static void pww_14nm_ssc_cawc(stwuct dsi_pww_14nm *pww, stwuct dsi_pww_config *pconf)
{
	u32 pewiod, ssc_pewiod;
	u32 wef, wem;
	u64 step_size;

	DBG("vco=%wwd wef=%d", pconf->vco_cuwwent_wate, VCO_WEF_CWK_WATE);

	ssc_pewiod = pconf->ssc_fweq / 500;
	pewiod = (u32)VCO_WEF_CWK_WATE / 1000;
	ssc_pewiod  = CEIW(pewiod, ssc_pewiod);
	ssc_pewiod -= 1;
	pconf->ssc_pewiod = ssc_pewiod;

	DBG("ssc fweq=%d spwead=%d pewiod=%d", pconf->ssc_fweq,
	    pconf->ssc_spwead, pconf->ssc_pewiod);

	step_size = (u32)pconf->vco_cuwwent_wate;
	wef = VCO_WEF_CWK_WATE;
	wef /= 1000;
	step_size = div_u64(step_size, wef);
	step_size <<= 20;
	step_size = div_u64(step_size, 1000);
	step_size *= pconf->ssc_spwead;
	step_size = div_u64(step_size, 1000);
	step_size *= (pconf->ssc_adj_pewiod + 1);

	wem = 0;
	step_size = div_u64_wem(step_size, ssc_pewiod + 1, &wem);
	if (wem)
		step_size++;

	DBG("step_size=%wwd", step_size);

	step_size &= 0x0ffff;	/* take wowew 16 bits */

	pconf->ssc_step_size = step_size;
}

static void pww_14nm_dec_fwac_cawc(stwuct dsi_pww_14nm *pww, stwuct dsi_pww_config *pconf)
{
	u64 muwtipwiew = BIT(20);
	u64 dec_stawt_muwtipwe, dec_stawt, pww_comp_vaw;
	u32 duwation, div_fwac_stawt;
	u64 vco_cwk_wate = pconf->vco_cuwwent_wate;
	u64 fwef = VCO_WEF_CWK_WATE;

	DBG("vco_cwk_wate=%wwd wef_cwk_wate=%wwd", vco_cwk_wate, fwef);

	dec_stawt_muwtipwe = div_u64(vco_cwk_wate * muwtipwiew, fwef);
	dec_stawt = div_u64_wem(dec_stawt_muwtipwe, muwtipwiew, &div_fwac_stawt);

	pconf->dec_stawt = (u32)dec_stawt;
	pconf->div_fwac_stawt = div_fwac_stawt;

	if (pconf->pwwwock_cnt == 0)
		duwation = 1024;
	ewse if (pconf->pwwwock_cnt == 1)
		duwation = 256;
	ewse if (pconf->pwwwock_cnt == 2)
		duwation = 128;
	ewse
		duwation = 32;

	pww_comp_vaw = duwation * dec_stawt_muwtipwe;
	pww_comp_vaw = div_u64(pww_comp_vaw, muwtipwiew);
	do_div(pww_comp_vaw, 10);

	pconf->pwwwock_cmp = (u32)pww_comp_vaw;
}

static u32 pww_14nm_kvco_swop(u32 vwate)
{
	u32 swop = 0;

	if (vwate > VCO_MIN_WATE && vwate <= 1800000000UW)
		swop =  600;
	ewse if (vwate > 1800000000UW && vwate < 2300000000UW)
		swop = 400;
	ewse if (vwate > 2300000000UW && vwate < VCO_MAX_WATE)
		swop = 280;

	wetuwn swop;
}

static void pww_14nm_cawc_vco_count(stwuct dsi_pww_14nm *pww, stwuct dsi_pww_config *pconf)
{
	u64 vco_cwk_wate = pconf->vco_cuwwent_wate;
	u64 fwef = VCO_WEF_CWK_WATE;
	u32 vco_measuwe_time = 5;
	u32 kvco_measuwe_time = 5;
	u64 data;
	u32 cnt;

	data = fwef * vco_measuwe_time;
	do_div(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 2;
	pconf->pww_vco_div_wef = data;

	data = div_u64(vco_cwk_wate, 1000000);	/* unit is Mhz */
	data *= vco_measuwe_time;
	do_div(data, 10);
	pconf->pww_vco_count = data;

	data = fwef * kvco_measuwe_time;
	do_div(data, 1000000);
	data &= 0x03ff;	/* 10 bits */
	data -= 1;
	pconf->pww_kvco_div_wef = data;

	cnt = pww_14nm_kvco_swop(vco_cwk_wate);
	cnt *= 2;
	cnt /= 100;
	cnt *= kvco_measuwe_time;
	pconf->pww_kvco_count = cnt;
}

static void pww_db_commit_ssc(stwuct dsi_pww_14nm *pww, stwuct dsi_pww_config *pconf)
{
	void __iomem *base = pww->phy->pww_base;
	u8 data;

	data = pconf->ssc_adj_pewiod;
	data &= 0x0ff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_ADJ_PEW1, data);
	data = (pconf->ssc_adj_pewiod >> 8);
	data &= 0x03;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_ADJ_PEW2, data);

	data = pconf->ssc_pewiod;
	data &= 0x0ff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_PEW1, data);
	data = (pconf->ssc_pewiod >> 8);
	data &= 0x0ff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_PEW2, data);

	data = pconf->ssc_step_size;
	data &= 0x0ff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_STEP_SIZE1, data);
	data = (pconf->ssc_step_size >> 8);
	data &= 0x0ff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_STEP_SIZE2, data);

	data = (pconf->ssc_centew & 0x01);
	data <<= 1;
	data |= 0x01; /* enabwe */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SSC_EN_CENTEW, data);

	wmb();	/* make suwe wegistew committed */
}

static void pww_db_commit_common(stwuct dsi_pww_14nm *pww,
				 stwuct dsi_pww_config *pconf)
{
	void __iomem *base = pww->phy->pww_base;
	u8 data;

	/* confgiuwe the non fwequency dependent pww wegistews */
	data = 0;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_SYSCWK_EN_WESET, data);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_TXCWK_EN, 1);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_WESETSM_CNTWW, 48);
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_WESETSM_CNTWW2, 4 << 3); /* bandgap_timew */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_WESETSM_CNTWW5, 5); /* pww_wakeup_timew */

	data = pconf->pww_vco_div_wef & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_VCO_DIV_WEF1, data);
	data = (pconf->pww_vco_div_wef >> 8) & 0x3;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_VCO_DIV_WEF2, data);

	data = pconf->pww_kvco_div_wef & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_KVCO_DIV_WEF1, data);
	data = (pconf->pww_kvco_div_wef >> 8) & 0x3;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_KVCO_DIV_WEF2, data);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_MISC1, 16);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_IE_TWIM, 4);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_IP_TWIM, 4);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_CP_SET_CUW, 1 << 3 | 1);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_ICPCSET, 0 << 3 | 0);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_ICPMSET, 0 << 3 | 0);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_ICP_SET, 4 << 3 | 4);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_WPF1, 1 << 4 | 11);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_IPTAT_TWIM, 7);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_CWCTWW, 1 << 4 | 2);
}

static void pww_14nm_softwawe_weset(stwuct dsi_pww_14nm *pww_14nm)
{
	void __iomem *cmn_base = pww_14nm->phy->base;

	/* de assewt pww stawt and appwy pww sw weset */

	/* stop pww */
	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_PWW_CNTWW, 0);

	/* pww sw weset */
	dsi_phy_wwite_udeway(cmn_base + WEG_DSI_14nm_PHY_CMN_CTWW_1, 0x20, 10);
	wmb();	/* make suwe wegistew committed */

	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_CTWW_1, 0);
	wmb();	/* make suwe wegistew committed */
}

static void pww_db_commit_14nm(stwuct dsi_pww_14nm *pww,
			       stwuct dsi_pww_config *pconf)
{
	void __iomem *base = pww->phy->pww_base;
	void __iomem *cmn_base = pww->phy->base;
	u8 data;

	DBG("DSI%d PWW", pww->phy->id);

	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_WDO_CNTWW, 0x3c);

	pww_db_commit_common(pww, pconf);

	pww_14nm_softwawe_weset(pww);

	/* Use the /2 path in Mux */
	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_CWK_CFG1, 1);

	data = 0xff; /* data, cwk, pww nowmaw opewation */
	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_CTWW_0, data);

	/* configuwe the fwequency dependent pww wegistews */
	data = pconf->dec_stawt;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_DEC_STAWT, data);

	data = pconf->div_fwac_stawt & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT1, data);
	data = (pconf->div_fwac_stawt >> 8) & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT2, data);
	data = (pconf->div_fwac_stawt >> 16) & 0xf;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT3, data);

	data = pconf->pwwwock_cmp & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWWWOCK_CMP1, data);

	data = (pconf->pwwwock_cmp >> 8) & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWWWOCK_CMP2, data);

	data = (pconf->pwwwock_cmp >> 16) & 0x3;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWWWOCK_CMP3, data);

	data = pconf->pwwwock_cnt << 1 | 0 << 3; /* pwwwock_wng */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWWWOCK_CMP_EN, data);

	data = pconf->pww_vco_count & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_VCO_COUNT1, data);
	data = (pconf->pww_vco_count >> 8) & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_VCO_COUNT2, data);

	data = pconf->pww_kvco_count & 0xff;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_KVCO_COUNT1, data);
	data = (pconf->pww_kvco_count >> 8) & 0x3;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_KVCO_COUNT2, data);

	/*
	 * High nibbwe configuwes the post dividew intewnaw to the VCO. It's
	 * fixed to divide by 1 fow now.
	 *
	 * 0: divided by 1
	 * 1: divided by 2
	 * 2: divided by 4
	 * 3: divided by 8
	 */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_WPF2_POSTDIV, 0 << 4 | 3);

	if (pconf->ssc_en)
		pww_db_commit_ssc(pww, pconf);

	wmb();	/* make suwe wegistew committed */
}

/*
 * VCO cwock Cawwbacks
 */
static int dsi_pww_14nm_vco_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(hw);
	stwuct dsi_pww_config conf;

	DBG("DSI PWW%d wate=%wu, pawent's=%wu", pww_14nm->phy->id, wate,
	    pawent_wate);

	dsi_pww_14nm_config_init(&conf);
	conf.vco_cuwwent_wate = wate;

	pww_14nm_dec_fwac_cawc(pww_14nm, &conf);

	if (conf.ssc_en)
		pww_14nm_ssc_cawc(pww_14nm, &conf);

	pww_14nm_cawc_vco_count(pww_14nm, &conf);

	/* commit the swave DSI PWW wegistews if we'we mastew. Note that we
	 * don't wock the swave PWW. We just ensuwe that the PWW/PHY wegistews
	 * of the mastew and swave awe identicaw
	 */
	if (pww_14nm->phy->usecase == MSM_DSI_PHY_MASTEW) {
		stwuct dsi_pww_14nm *pww_14nm_swave = pww_14nm->swave;

		pww_db_commit_14nm(pww_14nm_swave, &conf);
	}

	pww_db_commit_14nm(pww_14nm, &conf);

	wetuwn 0;
}

static unsigned wong dsi_pww_14nm_vco_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(hw);
	void __iomem *base = pww_14nm->phy->pww_base;
	u64 vco_wate, muwtipwiew = BIT(20);
	u32 div_fwac_stawt;
	u32 dec_stawt;
	u64 wef_cwk = pawent_wate;

	dec_stawt = dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_DEC_STAWT);
	dec_stawt &= 0x0ff;

	DBG("dec_stawt = %x", dec_stawt);

	div_fwac_stawt = (dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT3)
				& 0xf) << 16;
	div_fwac_stawt |= (dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT2)
				& 0xff) << 8;
	div_fwac_stawt |= dsi_phy_wead(base + WEG_DSI_14nm_PHY_PWW_DIV_FWAC_STAWT1)
				& 0xff;

	DBG("div_fwac_stawt = %x", div_fwac_stawt);

	vco_wate = wef_cwk * dec_stawt;

	vco_wate += ((wef_cwk * div_fwac_stawt) / muwtipwiew);

	/*
	 * Wecawcuwating the wate fwom dec_stawt and fwac_stawt doesn't end up
	 * the wate we owiginawwy set. Convewt the fweq to KHz, wound it up and
	 * convewt it back to MHz.
	 */
	vco_wate = DIV_WOUND_UP_UWW(vco_wate, 1000) * 1000;

	DBG("wetuwning vco wate = %wu", (unsigned wong)vco_wate);

	wetuwn (unsigned wong)vco_wate;
}

static int dsi_pww_14nm_vco_pwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(hw);
	void __iomem *base = pww_14nm->phy->pww_base;
	void __iomem *cmn_base = pww_14nm->phy->base;
	boow wocked;

	DBG("");

	if (unwikewy(pww_14nm->phy->pww_on))
		wetuwn 0;

	if (dsi_pww_14nm_vco_wecawc_wate(hw, VCO_WEF_CWK_WATE) == 0)
		dsi_pww_14nm_vco_set_wate(hw, pww_14nm->phy->cfg->min_pww_wate, VCO_WEF_CWK_WATE);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_VWEF_CFG1, 0x10);
	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_PWW_CNTWW, 1);

	wocked = pww_14nm_poww_fow_weady(pww_14nm, POWW_MAX_WEADS,
					 POWW_TIMEOUT_US);

	if (unwikewy(!wocked)) {
		DWM_DEV_EWWOW(&pww_14nm->phy->pdev->dev, "DSI PWW wock faiwed\n");
		wetuwn -EINVAW;
	}

	DBG("DSI PWW wock success");
	pww_14nm->phy->pww_on = twue;

	wetuwn 0;
}

static void dsi_pww_14nm_vco_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(hw);
	void __iomem *cmn_base = pww_14nm->phy->base;

	DBG("");

	if (unwikewy(!pww_14nm->phy->pww_on))
		wetuwn;

	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_PWW_CNTWW, 0);

	pww_14nm->phy->pww_on = fawse;
}

static wong dsi_pww_14nm_cwk_wound_wate(stwuct cwk_hw *hw,
		unsigned wong wate, unsigned wong *pawent_wate)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(hw);

	if      (wate < pww_14nm->phy->cfg->min_pww_wate)
		wetuwn  pww_14nm->phy->cfg->min_pww_wate;
	ewse if (wate > pww_14nm->phy->cfg->max_pww_wate)
		wetuwn  pww_14nm->phy->cfg->max_pww_wate;
	ewse
		wetuwn wate;
}

static const stwuct cwk_ops cwk_ops_dsi_pww_14nm_vco = {
	.wound_wate = dsi_pww_14nm_cwk_wound_wate,
	.set_wate = dsi_pww_14nm_vco_set_wate,
	.wecawc_wate = dsi_pww_14nm_vco_wecawc_wate,
	.pwepawe = dsi_pww_14nm_vco_pwepawe,
	.unpwepawe = dsi_pww_14nm_vco_unpwepawe,
};

/*
 * N1 and N2 post-dividew cwock cawwbacks
 */
#define div_mask(width)	((1 << (width)) - 1)
static unsigned wong dsi_pww_14nm_postdiv_wecawc_wate(stwuct cwk_hw *hw,
						      unsigned wong pawent_wate)
{
	stwuct dsi_pww_14nm_postdiv *postdiv = to_pww_14nm_postdiv(hw);
	stwuct dsi_pww_14nm *pww_14nm = postdiv->pww;
	void __iomem *base = pww_14nm->phy->base;
	u8 shift = postdiv->shift;
	u8 width = postdiv->width;
	u32 vaw;

	DBG("DSI%d PWW pawent wate=%wu", pww_14nm->phy->id, pawent_wate);

	vaw = dsi_phy_wead(base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0) >> shift;
	vaw &= div_mask(width);

	wetuwn dividew_wecawc_wate(hw, pawent_wate, vaw, NUWW,
				   postdiv->fwags, width);
}

static wong dsi_pww_14nm_postdiv_wound_wate(stwuct cwk_hw *hw,
					    unsigned wong wate,
					    unsigned wong *pwate)
{
	stwuct dsi_pww_14nm_postdiv *postdiv = to_pww_14nm_postdiv(hw);
	stwuct dsi_pww_14nm *pww_14nm = postdiv->pww;

	DBG("DSI%d PWW pawent wate=%wu", pww_14nm->phy->id, wate);

	wetuwn dividew_wound_wate(hw, wate, pwate, NUWW,
				  postdiv->width,
				  postdiv->fwags);
}

static int dsi_pww_14nm_postdiv_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong pawent_wate)
{
	stwuct dsi_pww_14nm_postdiv *postdiv = to_pww_14nm_postdiv(hw);
	stwuct dsi_pww_14nm *pww_14nm = postdiv->pww;
	void __iomem *base = pww_14nm->phy->base;
	spinwock_t *wock = &pww_14nm->postdiv_wock;
	u8 shift = postdiv->shift;
	u8 width = postdiv->width;
	unsigned int vawue;
	unsigned wong fwags = 0;
	u32 vaw;

	DBG("DSI%d PWW pawent wate=%wu pawent wate %wu", pww_14nm->phy->id, wate,
	    pawent_wate);

	vawue = dividew_get_vaw(wate, pawent_wate, NUWW, postdiv->width,
				postdiv->fwags);

	spin_wock_iwqsave(wock, fwags);

	vaw = dsi_phy_wead(base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0);
	vaw &= ~(div_mask(width) << shift);

	vaw |= vawue << shift;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0, vaw);

	/* If we'we mastew in bonded DSI mode, then the swave PWW's post-dividews
	 * fowwow the mastew's post dividews
	 */
	if (pww_14nm->phy->usecase == MSM_DSI_PHY_MASTEW) {
		stwuct dsi_pww_14nm *pww_14nm_swave = pww_14nm->swave;
		void __iomem *swave_base = pww_14nm_swave->phy->base;

		dsi_phy_wwite(swave_base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0, vaw);
	}

	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_ops_dsi_pww_14nm_postdiv = {
	.wecawc_wate = dsi_pww_14nm_postdiv_wecawc_wate,
	.wound_wate = dsi_pww_14nm_postdiv_wound_wate,
	.set_wate = dsi_pww_14nm_postdiv_set_wate,
};

/*
 * PWW Cawwbacks
 */

static void dsi_14nm_pww_save_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(phy->vco_hw);
	stwuct pww_14nm_cached_state *cached_state = &pww_14nm->cached_state;
	void __iomem *cmn_base = pww_14nm->phy->base;
	u32 data;

	data = dsi_phy_wead(cmn_base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0);

	cached_state->n1postdiv = data & 0xf;
	cached_state->n2postdiv = (data >> 4) & 0xf;

	DBG("DSI%d PWW save state %x %x", pww_14nm->phy->id,
	    cached_state->n1postdiv, cached_state->n2postdiv);

	cached_state->vco_wate = cwk_hw_get_wate(phy->vco_hw);
}

static int dsi_14nm_pww_westowe_state(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(phy->vco_hw);
	stwuct pww_14nm_cached_state *cached_state = &pww_14nm->cached_state;
	void __iomem *cmn_base = pww_14nm->phy->base;
	u32 data;
	int wet;

	wet = dsi_pww_14nm_vco_set_wate(phy->vco_hw,
					cached_state->vco_wate, 0);
	if (wet) {
		DWM_DEV_EWWOW(&pww_14nm->phy->pdev->dev,
			      "westowe vco wate faiwed. wet=%d\n", wet);
		wetuwn wet;
	}

	data = cached_state->n1postdiv | (cached_state->n2postdiv << 4);

	DBG("DSI%d PWW westowe state %x %x", pww_14nm->phy->id,
	    cached_state->n1postdiv, cached_state->n2postdiv);

	dsi_phy_wwite(cmn_base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0, data);

	/* awso westowe post-dividews fow swave DSI PWW */
	if (phy->usecase == MSM_DSI_PHY_MASTEW) {
		stwuct dsi_pww_14nm *pww_14nm_swave = pww_14nm->swave;
		void __iomem *swave_base = pww_14nm_swave->phy->base;

		dsi_phy_wwite(swave_base + WEG_DSI_14nm_PHY_CMN_CWK_CFG0, data);
	}

	wetuwn 0;
}

static int dsi_14nm_set_usecase(stwuct msm_dsi_phy *phy)
{
	stwuct dsi_pww_14nm *pww_14nm = to_pww_14nm(phy->vco_hw);
	void __iomem *base = phy->pww_base;
	u32 cwkbufww_en, bandgap = 0;

	switch (phy->usecase) {
	case MSM_DSI_PHY_STANDAWONE:
		cwkbufww_en = 0x1;
		bweak;
	case MSM_DSI_PHY_MASTEW:
		cwkbufww_en = 0x3;
		pww_14nm->swave = pww_14nm_wist[(pww_14nm->phy->id + 1) % DSI_MAX];
		bweak;
	case MSM_DSI_PHY_SWAVE:
		cwkbufww_en = 0x0;
		bandgap = 0x3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_CWKBUFWW_EN, cwkbufww_en);
	if (bandgap)
		dsi_phy_wwite(base + WEG_DSI_14nm_PHY_PWW_PWW_BANDGAP, bandgap);

	wetuwn 0;
}

static stwuct cwk_hw *pww_14nm_postdiv_wegistew(stwuct dsi_pww_14nm *pww_14nm,
						const chaw *name,
						const stwuct cwk_hw *pawent_hw,
						unsigned wong fwags,
						u8 shift)
{
	stwuct dsi_pww_14nm_postdiv *pww_postdiv;
	stwuct device *dev = &pww_14nm->phy->pdev->dev;
	stwuct cwk_init_data postdiv_init = {
		.pawent_hws = (const stwuct cwk_hw *[]) { pawent_hw },
		.num_pawents = 1,
		.name = name,
		.fwags = fwags,
		.ops = &cwk_ops_dsi_pww_14nm_postdiv,
	};
	int wet;

	pww_postdiv = devm_kzawwoc(dev, sizeof(*pww_postdiv), GFP_KEWNEW);
	if (!pww_postdiv)
		wetuwn EWW_PTW(-ENOMEM);

	pww_postdiv->pww = pww_14nm;
	pww_postdiv->shift = shift;
	/* both N1 and N2 postdividews awe 4 bits wide */
	pww_postdiv->width = 4;
	/* wange of each dividew is fwom 1 to 15 */
	pww_postdiv->fwags = CWK_DIVIDEW_ONE_BASED;
	pww_postdiv->hw.init = &postdiv_init;

	wet = devm_cwk_hw_wegistew(dev, &pww_postdiv->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &pww_postdiv->hw;
}

static int pww_14nm_wegistew(stwuct dsi_pww_14nm *pww_14nm, stwuct cwk_hw **pwovided_cwocks)
{
	chaw cwk_name[32];
	stwuct cwk_init_data vco_init = {
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "wef",
		},
		.num_pawents = 1,
		.name = cwk_name,
		.fwags = CWK_IGNOWE_UNUSED,
		.ops = &cwk_ops_dsi_pww_14nm_vco,
	};
	stwuct device *dev = &pww_14nm->phy->pdev->dev;
	stwuct cwk_hw *hw, *n1_postdiv, *n1_postdivby2;
	int wet;

	DBG("DSI%d", pww_14nm->phy->id);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dvco_cwk", pww_14nm->phy->id);
	pww_14nm->cwk_hw.init = &vco_init;

	wet = devm_cwk_hw_wegistew(dev, &pww_14nm->cwk_hw);
	if (wet)
		wetuwn wet;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dn1_postdiv_cwk", pww_14nm->phy->id);

	/* N1 postdiv, bits 0-3 in WEG_DSI_14nm_PHY_CMN_CWK_CFG0 */
	n1_postdiv = pww_14nm_postdiv_wegistew(pww_14nm, cwk_name,
			&pww_14nm->cwk_hw, CWK_SET_WATE_PAWENT, 0);
	if (IS_EWW(n1_postdiv))
		wetuwn PTW_EWW(n1_postdiv);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpwwbyte", pww_14nm->phy->id);

	/* DSI Byte cwock = VCO_CWK / N1 / 8 */
	hw = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev, cwk_name,
			n1_postdiv, CWK_SET_WATE_PAWENT, 1, 8);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	pwovided_cwocks[DSI_BYTE_PWW_CWK] = hw;

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dn1_postdivby2_cwk", pww_14nm->phy->id);

	/*
	 * Skip the mux fow now, fowce DSICWK_SEW to 1, Add a /2 dividew
	 * on the way. Don't wet it set pawent.
	 */
	n1_postdivby2 = devm_cwk_hw_wegistew_fixed_factow_pawent_hw(dev,
			cwk_name, n1_postdiv, 0, 1, 2);
	if (IS_EWW(n1_postdivby2))
		wetuwn PTW_EWW(n1_postdivby2);

	snpwintf(cwk_name, sizeof(cwk_name), "dsi%dpww", pww_14nm->phy->id);

	/* DSI pixew cwock = VCO_CWK / N1 / 2 / N2
	 * This is the output of N2 post-dividew, bits 4-7 in
	 * WEG_DSI_14nm_PHY_CMN_CWK_CFG0. Don't wet it set pawent.
	 */
	hw = pww_14nm_postdiv_wegistew(pww_14nm, cwk_name, n1_postdivby2,
			0, 4);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	pwovided_cwocks[DSI_PIXEW_PWW_CWK] = hw;

	wetuwn 0;
}

static int dsi_pww_14nm_init(stwuct msm_dsi_phy *phy)
{
	stwuct pwatfowm_device *pdev = phy->pdev;
	stwuct dsi_pww_14nm *pww_14nm;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	pww_14nm = devm_kzawwoc(&pdev->dev, sizeof(*pww_14nm), GFP_KEWNEW);
	if (!pww_14nm)
		wetuwn -ENOMEM;

	DBG("PWW%d", phy->id);

	pww_14nm_wist[phy->id] = pww_14nm;

	spin_wock_init(&pww_14nm->postdiv_wock);

	pww_14nm->phy = phy;

	wet = pww_14nm_wegistew(pww_14nm, phy->pwovided_cwocks->hws);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "faiwed to wegistew PWW: %d\n", wet);
		wetuwn wet;
	}

	phy->vco_hw = &pww_14nm->cwk_hw;

	wetuwn 0;
}

static void dsi_14nm_dphy_set_timing(stwuct msm_dsi_phy *phy,
				     stwuct msm_dsi_dphy_timing *timing,
				     int wane_idx)
{
	void __iomem *base = phy->wane_base;
	boow cwk_wn = (wane_idx == PHY_14NM_CKWN_IDX);
	u32 zewo = cwk_wn ? timing->cwk_zewo : timing->hs_zewo;
	u32 pwepawe = cwk_wn ? timing->cwk_pwepawe : timing->hs_pwepawe;
	u32 twaiw = cwk_wn ? timing->cwk_twaiw : timing->hs_twaiw;
	u32 wqst = cwk_wn ? timing->hs_wqst_ckwn : timing->hs_wqst;
	u32 pwep_dwy = cwk_wn ? timing->hs_pwep_dwy_ckwn : timing->hs_pwep_dwy;
	u32 hawfbyte_en = cwk_wn ? timing->hs_hawfbyte_en_ckwn :
				   timing->hs_hawfbyte_en;

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_4(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_4_HS_EXIT(timing->hs_exit));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_5(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_5_HS_ZEWO(zewo));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_6(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_6_HS_PWEPAWE(pwepawe));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_7(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_7_HS_TWAIW(twaiw));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_8(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_8_HS_WQST(wqst));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_CFG0(wane_idx),
		      DSI_14nm_PHY_WN_CFG0_PWEPAWE_DWY(pwep_dwy));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_CFG1(wane_idx),
		      hawfbyte_en ? DSI_14nm_PHY_WN_CFG1_HAWFBYTECWK_EN : 0);
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_9(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_9_TA_GO(timing->ta_go) |
		      DSI_14nm_PHY_WN_TIMING_CTWW_9_TA_SUWE(timing->ta_suwe));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_10(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_10_TA_GET(timing->ta_get));
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_WN_TIMING_CTWW_11(wane_idx),
		      DSI_14nm_PHY_WN_TIMING_CTWW_11_TWIG3_CMD(0xa0));
}

static int dsi_14nm_phy_enabwe(stwuct msm_dsi_phy *phy,
			       stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	stwuct msm_dsi_dphy_timing *timing = &phy->timing;
	u32 data;
	int i;
	int wet;
	void __iomem *base = phy->base;
	void __iomem *wane_base = phy->wane_base;
	u32 gwbw_test_ctww;

	if (msm_dsi_dphy_timing_cawc_v2(timing, cwk_weq)) {
		DWM_DEV_EWWOW(&phy->pdev->dev,
			      "%s: D-PHY timing cawcuwation faiwed\n",
			      __func__);
		wetuwn -EINVAW;
	}

	data = 0x1c;
	if (phy->usecase != MSM_DSI_PHY_STANDAWONE)
		data |= DSI_14nm_PHY_CMN_WDO_CNTWW_VWEG_CTWW(32);
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_WDO_CNTWW, data);

	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_GWBW_TEST_CTWW, 0x1);

	/* 4 data wanes + 1 cwk wane configuwation */
	fow (i = 0; i < 5; i++) {
		dsi_phy_wwite(wane_base + WEG_DSI_14nm_PHY_WN_VWEG_CNTWW(i),
			      0x1d);

		dsi_phy_wwite(wane_base +
			      WEG_DSI_14nm_PHY_WN_STWENGTH_CTWW_0(i), 0xff);
		dsi_phy_wwite(wane_base +
			      WEG_DSI_14nm_PHY_WN_STWENGTH_CTWW_1(i),
			      (i == PHY_14NM_CKWN_IDX) ? 0x00 : 0x06);

		dsi_phy_wwite(wane_base + WEG_DSI_14nm_PHY_WN_CFG3(i),
			      (i == PHY_14NM_CKWN_IDX) ? 0x8f : 0x0f);
		dsi_phy_wwite(wane_base + WEG_DSI_14nm_PHY_WN_CFG2(i), 0x10);
		dsi_phy_wwite(wane_base + WEG_DSI_14nm_PHY_WN_TEST_DATAPATH(i),
			      0);
		dsi_phy_wwite(wane_base + WEG_DSI_14nm_PHY_WN_TEST_STW(i),
			      0x88);

		dsi_14nm_dphy_set_timing(phy, timing, i);
	}

	/* Make suwe PWW is not stawt */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_PWW_CNTWW, 0x00);

	wmb(); /* make suwe evewything is wwitten befowe weset and enabwe */

	/* weset digitaw bwock */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_CTWW_1, 0x80);
	wmb(); /* ensuwe weset is assewted */
	udeway(100);
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_CTWW_1, 0x00);

	gwbw_test_ctww = dsi_phy_wead(base + WEG_DSI_14nm_PHY_CMN_GWBW_TEST_CTWW);
	if (phy->id == DSI_1 && phy->usecase == MSM_DSI_PHY_SWAVE)
		gwbw_test_ctww |= DSI_14nm_PHY_CMN_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	ewse
		gwbw_test_ctww &= ~DSI_14nm_PHY_CMN_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_GWBW_TEST_CTWW, gwbw_test_ctww);
	wet = dsi_14nm_set_usecase(phy);
	if (wet) {
		DWM_DEV_EWWOW(&phy->pdev->dev, "%s: set pww usecase faiwed, %d\n",
			      __func__, wet);
		wetuwn wet;
	}

	/* Wemove powew down fwom PWW and aww wanes */
	dsi_phy_wwite(base + WEG_DSI_14nm_PHY_CMN_CTWW_0, 0xff);

	wetuwn 0;
}

static void dsi_14nm_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	dsi_phy_wwite(phy->base + WEG_DSI_14nm_PHY_CMN_GWBW_TEST_CTWW, 0);
	dsi_phy_wwite(phy->base + WEG_DSI_14nm_PHY_CMN_CTWW_0, 0);

	/* ensuwe that the phy is compwetewy disabwed */
	wmb();
}

static const stwuct weguwatow_buwk_data dsi_phy_14nm_17mA_weguwatows[] = {
	{ .suppwy = "vcca", .init_woad_uA = 17000 },
};

static const stwuct weguwatow_buwk_data dsi_phy_14nm_73p4mA_weguwatows[] = {
	{ .suppwy = "vcca", .init_woad_uA = 73400 },
};

const stwuct msm_dsi_phy_cfg dsi_phy_14nm_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_14nm_17mA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_14nm_17mA_weguwatows),
	.ops = {
		.enabwe = dsi_14nm_phy_enabwe,
		.disabwe = dsi_14nm_phy_disabwe,
		.pww_init = dsi_pww_14nm_init,
		.save_pww_state = dsi_14nm_pww_save_state,
		.westowe_pww_state = dsi_14nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x994400, 0x996400 },
	.num_dsi_phy = 2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_14nm_660_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_14nm_73p4mA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_14nm_73p4mA_weguwatows),
	.ops = {
		.enabwe = dsi_14nm_phy_enabwe,
		.disabwe = dsi_14nm_phy_disabwe,
		.pww_init = dsi_pww_14nm_init,
		.save_pww_state = dsi_14nm_pww_save_state,
		.westowe_pww_state = dsi_14nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0xc994400, 0xc996400 },
	.num_dsi_phy = 2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_14nm_8953_cfgs = {
	.has_phy_wane = twue,
	.weguwatow_data = dsi_phy_14nm_17mA_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_14nm_17mA_weguwatows),
	.ops = {
		.enabwe = dsi_14nm_phy_enabwe,
		.disabwe = dsi_14nm_phy_disabwe,
		.pww_init = dsi_pww_14nm_init,
		.save_pww_state = dsi_14nm_pww_save_state,
		.westowe_pww_state = dsi_14nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x1a94400, 0x1a96400 },
	.num_dsi_phy = 2,
};

const stwuct msm_dsi_phy_cfg dsi_phy_14nm_2290_cfgs = {
	.has_phy_wane = twue,
	.ops = {
		.enabwe = dsi_14nm_phy_enabwe,
		.disabwe = dsi_14nm_phy_disabwe,
		.pww_init = dsi_pww_14nm_init,
		.save_pww_state = dsi_14nm_pww_save_state,
		.westowe_pww_state = dsi_14nm_pww_westowe_state,
	},
	.min_pww_wate = VCO_MIN_WATE,
	.max_pww_wate = VCO_MAX_WATE,
	.io_stawt = { 0x5e94400 },
	.num_dsi_phy = 1,
};
