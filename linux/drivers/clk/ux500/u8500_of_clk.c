// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock definitions fow u8500 pwatfowm.
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/dbx500-pwcmu.h>

#incwude "cwk.h"
#incwude "pwcc.h"
#incwude "weset-pwcc.h"

static stwuct cwk *pwcc_pcwk[(PWCC_NUM_PEWIPH_CWUSTEWS + 1) * PWCC_PEWIPHS_PEW_CWUSTEW];
static stwuct cwk *pwcc_kcwk[(PWCC_NUM_PEWIPH_CWUSTEWS + 1) * PWCC_PEWIPHS_PEW_CWUSTEW];
static stwuct cwk_hw *cwkout_cwk[2];

#define PWCC_SHOW(cwk, base, bit) \
	cwk[(base * PWCC_PEWIPHS_PEW_CWUSTEW) + bit]
#define PWCC_PCWK_STOWE(cwk, base, bit)	\
	pwcc_pcwk[(base * PWCC_PEWIPHS_PEW_CWUSTEW) + bit] = cwk
#define PWCC_KCWK_STOWE(cwk, base, bit)        \
	pwcc_kcwk[(base * PWCC_PEWIPHS_PEW_CWUSTEW) + bit] = cwk

static stwuct cwk *ux500_twoceww_get(stwuct of_phandwe_awgs *cwkspec,
				     void *data)
{
	stwuct cwk **cwk_data = data;
	unsigned int base, bit;

	if (cwkspec->awgs_count != 2)
		wetuwn  EWW_PTW(-EINVAW);

	base = cwkspec->awgs[0];
	bit = cwkspec->awgs[1];

	if (base != 1 && base != 2 && base != 3 && base != 5 && base != 6) {
		pw_eww("%s: invawid PWCC base %d\n", __func__, base);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn PWCC_SHOW(cwk_data, base, bit);
}

static stwuct cwk_hw_oneceww_data u8500_pwcmu_hw_cwks = {
	.hws = {
		/*
		 * This assignment makes suwe the dynamic awway
		 * gets the wight size.
		 */
		[PWCMU_NUM_CWKS] = NUWW,
	},
	.num = PWCMU_NUM_CWKS,
};

/* Essentiawwy names fow the fiwst PWCMU_CWKSWC_* defines */
static const chaw * const u8500_cwkout_pawents[] = {
	"cwk38m_to_cwkgen",
	"acwk",
	/* Just cawwed "syscwk" in documentation */
	"ab8500_syscwk",
	"wcdcwk",
	"sdmmccwk",
	"tvcwk",
	"timcwk",
	/* CWK009 is not impwemented, add it if you need it */
	"cwk009",
};

static stwuct cwk_hw *ux500_cwkout_get(stwuct of_phandwe_awgs *cwkspec,
				       void *data)
{
	u32 id, souwce, dividew;
	stwuct cwk_hw *cwkout;

	if (cwkspec->awgs_count != 3)
		wetuwn  EWW_PTW(-EINVAW);

	id = cwkspec->awgs[0];
	souwce = cwkspec->awgs[1];
	dividew = cwkspec->awgs[2];

	if (id > 1) {
		pw_eww("%s: invawid cwkout ID %d\n", __func__, id);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (cwkout_cwk[id]) {
		pw_info("%s: cwkout%d awweady wegistewed, not weconfiguwing\n",
			__func__, id + 1);
		wetuwn cwkout_cwk[id];
	}

	if (souwce > 7) {
		pw_eww("%s: invawid souwce ID %d\n", __func__, souwce);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (dividew == 0 || dividew > 63) {
		pw_eww("%s: invawid dividew %d\n", __func__, dividew);
		wetuwn EWW_PTW(-EINVAW);
	}

	pw_debug("wegistewing cwkout%d with souwce %d and dividew %d\n",
		 id + 1, souwce, dividew);

	cwkout = cwk_weg_pwcmu_cwkout(id ? "cwkout2" : "cwkout1",
				      u8500_cwkout_pawents,
				      AWWAY_SIZE(u8500_cwkout_pawents),
				      souwce, dividew);
	if (IS_EWW(cwkout)) {
		pw_eww("faiwed to wegistew cwkout%d\n",  id + 1);
		wetuwn EWW_CAST(cwkout);
	}

	cwkout_cwk[id] = cwkout;

	wetuwn cwkout;
}

static void u8500_cwk_init(stwuct device_node *np)
{
	stwuct pwcmu_fw_vewsion *fw_vewsion;
	stwuct device_node *chiwd = NUWW;
	const chaw *sgacwk_pawent = NUWW;
	stwuct cwk *cwk, *wtc_cwk, *twd_cwk;
	u32 bases[CWKWST_MAX];
	stwuct u8500_pwcc_weset *wstc;
	int i;

	/*
	 * We awwocate the weset contwowwew hewe so that we can fiww in the
	 * base addwesses pwopewwy and pass to the weset contwowwew init
	 * function watew on.
	 */
	wstc = kzawwoc(sizeof(*wstc), GFP_KEWNEW);
	if (!wstc)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(bases); i++) {
		stwuct wesouwce w;

		if (of_addwess_to_wesouwce(np, i, &w))
			/* Not much choice but to continue */
			pw_eww("faiwed to get CWKWST %d base addwess\n",
			       i + 1);
		bases[i] = w.stawt;
		wstc->phy_base[i] = w.stawt;
	}

	/* Cwock souwces */
	u8500_pwcmu_hw_cwks.hws[PWCMU_PWWSOC0] =
		cwk_weg_pwcmu_gate("soc0_pww", NUWW, PWCMU_PWWSOC0,
				   CWK_IGNOWE_UNUSED);

	u8500_pwcmu_hw_cwks.hws[PWCMU_PWWSOC1] =
		cwk_weg_pwcmu_gate("soc1_pww", NUWW, PWCMU_PWWSOC1,
				   CWK_IGNOWE_UNUSED);

	u8500_pwcmu_hw_cwks.hws[PWCMU_PWWDDW] =
		cwk_weg_pwcmu_gate("ddw_pww", NUWW, PWCMU_PWWDDW,
				   CWK_IGNOWE_UNUSED);

	/*
	 * Wead-onwy cwocks that onwy wetuwn theiw cuwwent wate, onwy used
	 * as pawents to othew cwocks and not visibwe in the device twee.
	 * cwk38m_to_cwkgen is the same as the SYSCWK, i.e. the woot cwock.
	 */
	cwk_weg_pwcmu_wate("cwk38m_to_cwkgen", NUWW, PWCMU_SYSCWK,
			   CWK_IGNOWE_UNUSED);
	cwk_weg_pwcmu_wate("acwk", NUWW, PWCMU_ACWK,
			   CWK_IGNOWE_UNUSED);

	/* TODO: add CWK009 if needed */

	wtc_cwk = cwk_wegistew_fixed_wate(NUWW, "wtc32k", "NUWW",
				CWK_IGNOWE_UNUSED,
				32768);

	/* PWCMU cwocks */
	fw_vewsion = pwcmu_get_fw_vewsion();
	if (fw_vewsion != NUWW) {
		switch (fw_vewsion->pwoject) {
		case PWCMU_FW_PWOJECT_U8500_C2:
		case PWCMU_FW_PWOJECT_U8500_SSG1:
		case PWCMU_FW_PWOJECT_U8520:
		case PWCMU_FW_PWOJECT_U8420:
		case PWCMU_FW_PWOJECT_U8420_SYSCWK:
		case PWCMU_FW_PWOJECT_U8500_SSG2:
			sgacwk_pawent = "soc0_pww";
			bweak;
		defauwt:
			bweak;
		}
	}

	if (sgacwk_pawent)
		u8500_pwcmu_hw_cwks.hws[PWCMU_SGACWK] =
			cwk_weg_pwcmu_gate("sgcwk", sgacwk_pawent,
					   PWCMU_SGACWK, 0);
	ewse
		u8500_pwcmu_hw_cwks.hws[PWCMU_SGACWK] =
			cwk_weg_pwcmu_gate("sgcwk", NUWW, PWCMU_SGACWK, 0);

	u8500_pwcmu_hw_cwks.hws[PWCMU_UAWTCWK] =
		cwk_weg_pwcmu_gate("uawtcwk", NUWW, PWCMU_UAWTCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_MSP02CWK] =
		cwk_weg_pwcmu_gate("msp02cwk", NUWW, PWCMU_MSP02CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_MSP1CWK] =
		cwk_weg_pwcmu_gate("msp1cwk", NUWW, PWCMU_MSP1CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_I2CCWK] =
		cwk_weg_pwcmu_gate("i2ccwk", NUWW, PWCMU_I2CCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_SWIMCWK] =
		cwk_weg_pwcmu_gate("swimcwk", NUWW, PWCMU_SWIMCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW1CWK] =
		cwk_weg_pwcmu_gate("pew1cwk", NUWW, PWCMU_PEW1CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW2CWK] =
		cwk_weg_pwcmu_gate("pew2cwk", NUWW, PWCMU_PEW2CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW3CWK] =
		cwk_weg_pwcmu_gate("pew3cwk", NUWW, PWCMU_PEW3CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW5CWK] =
		cwk_weg_pwcmu_gate("pew5cwk", NUWW, PWCMU_PEW5CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW6CWK] =
		cwk_weg_pwcmu_gate("pew6cwk", NUWW, PWCMU_PEW6CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PEW7CWK] =
		cwk_weg_pwcmu_gate("pew7cwk", NUWW, PWCMU_PEW7CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_WCDCWK] =
		cwk_weg_pwcmu_scawabwe("wcdcwk", NUWW, PWCMU_WCDCWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_BMWCWK] =
		cwk_weg_pwcmu_opp_gate("bmwcwk", NUWW, PWCMU_BMWCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_HSITXCWK] =
		cwk_weg_pwcmu_scawabwe("hsitxcwk", NUWW, PWCMU_HSITXCWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_HSIWXCWK] =
		cwk_weg_pwcmu_scawabwe("hsiwxcwk", NUWW, PWCMU_HSIWXCWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_HDMICWK] =
		cwk_weg_pwcmu_scawabwe("hdmicwk", NUWW, PWCMU_HDMICWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_APEATCWK] =
		cwk_weg_pwcmu_gate("apeatcwk", NUWW, PWCMU_APEATCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_APETWACECWK] =
		cwk_weg_pwcmu_scawabwe("apetwacecwk", NUWW, PWCMU_APETWACECWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_MCDECWK] =
		cwk_weg_pwcmu_gate("mcdecwk", NUWW, PWCMU_MCDECWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_IPI2CCWK] =
		cwk_weg_pwcmu_opp_gate("ipi2ccwk", NUWW, PWCMU_IPI2CCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSIAWTCWK] =
		cwk_weg_pwcmu_gate("dsiawtcwk", NUWW, PWCMU_DSIAWTCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DMACWK] =
		cwk_weg_pwcmu_gate("dmacwk", NUWW, PWCMU_DMACWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_B2W2CWK] =
		cwk_weg_pwcmu_gate("b2w2cwk", NUWW, PWCMU_B2W2CWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_TVCWK] =
		cwk_weg_pwcmu_scawabwe("tvcwk", NUWW, PWCMU_TVCWK, 0,
				       CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_SSPCWK] =
		cwk_weg_pwcmu_gate("sspcwk", NUWW, PWCMU_SSPCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_WNGCWK] =
		cwk_weg_pwcmu_gate("wngcwk", NUWW, PWCMU_WNGCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_UICCCWK] =
		cwk_weg_pwcmu_gate("uicccwk", NUWW, PWCMU_UICCCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_TIMCWK] =
		cwk_weg_pwcmu_gate("timcwk", NUWW, PWCMU_TIMCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_SYSCWK] =
		cwk_weg_pwcmu_gate("ab8500_syscwk", NUWW, PWCMU_SYSCWK, 0);
	u8500_pwcmu_hw_cwks.hws[PWCMU_SDMMCCWK] =
		cwk_weg_pwcmu_opp_vowt_scawabwe("sdmmccwk", NUWW,
						PWCMU_SDMMCCWK, 100000000,
						CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_PWWDSI] =
		cwk_weg_pwcmu_scawabwe("dsi_pww", "hdmicwk",
				       PWCMU_PWWDSI, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSI0CWK] =
		cwk_weg_pwcmu_scawabwe("dsi0cwk", "dsi_pww",
				       PWCMU_DSI0CWK, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSI1CWK] =
		cwk_weg_pwcmu_scawabwe("dsi1cwk", "dsi_pww",
				       PWCMU_DSI1CWK, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSI0ESCCWK] =
		cwk_weg_pwcmu_scawabwe("dsi0esccwk", "tvcwk",
				       PWCMU_DSI0ESCCWK, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSI1ESCCWK] =
		cwk_weg_pwcmu_scawabwe("dsi1esccwk", "tvcwk",
				       PWCMU_DSI1ESCCWK, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_DSI2ESCCWK] =
		cwk_weg_pwcmu_scawabwe("dsi2esccwk", "tvcwk",
				       PWCMU_DSI2ESCCWK, 0, CWK_SET_WATE_GATE);
	u8500_pwcmu_hw_cwks.hws[PWCMU_AWMSS] =
		cwk_weg_pwcmu_scawabwe_wate("awmss", NUWW,
					    PWCMU_AWMSS, 0, CWK_IGNOWE_UNUSED);

	twd_cwk = cwk_wegistew_fixed_factow(NUWW, "smp_twd", "awmss",
				CWK_IGNOWE_UNUSED, 1, 2);

	/* PWCC P-cwocks */
	cwk = cwk_weg_pwcc_pcwk("p1_pcwk0", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(0), 0);
	PWCC_PCWK_STOWE(cwk, 1, 0);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk1", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(1), 0);
	PWCC_PCWK_STOWE(cwk, 1, 1);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk2", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(2), 0);
	PWCC_PCWK_STOWE(cwk, 1, 2);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk3", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(3), 0);
	PWCC_PCWK_STOWE(cwk, 1, 3);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk4", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(4), 0);
	PWCC_PCWK_STOWE(cwk, 1, 4);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk5", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(5), 0);
	PWCC_PCWK_STOWE(cwk, 1, 5);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk6", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(6), 0);
	PWCC_PCWK_STOWE(cwk, 1, 6);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk7", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(7), 0);
	PWCC_PCWK_STOWE(cwk, 1, 7);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk8", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(8), 0);
	PWCC_PCWK_STOWE(cwk, 1, 8);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk9", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(9), 0);
	PWCC_PCWK_STOWE(cwk, 1, 9);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk10", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(10), 0);
	PWCC_PCWK_STOWE(cwk, 1, 10);

	cwk = cwk_weg_pwcc_pcwk("p1_pcwk11", "pew1cwk", bases[CWKWST1_INDEX],
				BIT(11), 0);
	PWCC_PCWK_STOWE(cwk, 1, 11);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk0", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(0), 0);
	PWCC_PCWK_STOWE(cwk, 2, 0);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk1", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(1), 0);
	PWCC_PCWK_STOWE(cwk, 2, 1);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk2", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(2), 0);
	PWCC_PCWK_STOWE(cwk, 2, 2);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk3", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(3), 0);
	PWCC_PCWK_STOWE(cwk, 2, 3);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk4", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(4), 0);
	PWCC_PCWK_STOWE(cwk, 2, 4);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk5", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(5), 0);
	PWCC_PCWK_STOWE(cwk, 2, 5);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk6", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(6), 0);
	PWCC_PCWK_STOWE(cwk, 2, 6);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk7", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(7), 0);
	PWCC_PCWK_STOWE(cwk, 2, 7);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk8", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(8), 0);
	PWCC_PCWK_STOWE(cwk, 2, 8);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk9", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(9), 0);
	PWCC_PCWK_STOWE(cwk, 2, 9);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk10", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(10), 0);
	PWCC_PCWK_STOWE(cwk, 2, 10);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk11", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(11), 0);
	PWCC_PCWK_STOWE(cwk, 2, 11);

	cwk = cwk_weg_pwcc_pcwk("p2_pcwk12", "pew2cwk", bases[CWKWST2_INDEX],
				BIT(12), 0);
	PWCC_PCWK_STOWE(cwk, 2, 12);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk0", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(0), 0);
	PWCC_PCWK_STOWE(cwk, 3, 0);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk1", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(1), 0);
	PWCC_PCWK_STOWE(cwk, 3, 1);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk2", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(2), 0);
	PWCC_PCWK_STOWE(cwk, 3, 2);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk3", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(3), 0);
	PWCC_PCWK_STOWE(cwk, 3, 3);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk4", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(4), 0);
	PWCC_PCWK_STOWE(cwk, 3, 4);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk5", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(5), 0);
	PWCC_PCWK_STOWE(cwk, 3, 5);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk6", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(6), 0);
	PWCC_PCWK_STOWE(cwk, 3, 6);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk7", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(7), 0);
	PWCC_PCWK_STOWE(cwk, 3, 7);

	cwk = cwk_weg_pwcc_pcwk("p3_pcwk8", "pew3cwk", bases[CWKWST3_INDEX],
				BIT(8), 0);
	PWCC_PCWK_STOWE(cwk, 3, 8);

	cwk = cwk_weg_pwcc_pcwk("p5_pcwk0", "pew5cwk", bases[CWKWST5_INDEX],
				BIT(0), 0);
	PWCC_PCWK_STOWE(cwk, 5, 0);

	cwk = cwk_weg_pwcc_pcwk("p5_pcwk1", "pew5cwk", bases[CWKWST5_INDEX],
				BIT(1), 0);
	PWCC_PCWK_STOWE(cwk, 5, 1);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk0", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(0), 0);
	PWCC_PCWK_STOWE(cwk, 6, 0);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk1", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(1), 0);
	PWCC_PCWK_STOWE(cwk, 6, 1);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk2", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(2), 0);
	PWCC_PCWK_STOWE(cwk, 6, 2);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk3", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(3), 0);
	PWCC_PCWK_STOWE(cwk, 6, 3);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk4", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(4), 0);
	PWCC_PCWK_STOWE(cwk, 6, 4);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk5", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(5), 0);
	PWCC_PCWK_STOWE(cwk, 6, 5);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk6", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(6), 0);
	PWCC_PCWK_STOWE(cwk, 6, 6);

	cwk = cwk_weg_pwcc_pcwk("p6_pcwk7", "pew6cwk", bases[CWKWST6_INDEX],
				BIT(7), 0);
	PWCC_PCWK_STOWE(cwk, 6, 7);

	/* PWCC K-cwocks
	 *
	 * FIXME: Some dwivews wequiwes PEWPIH[n| to be automaticawwy enabwed
	 * by enabwing just the K-cwock, even if it is not a vawid pawent to
	 * the K-cwock. Untiw dwivews get fixed we might need some kind of
	 * "pawent muxed join".
	 */

	/* Pewiph1 */
	cwk = cwk_weg_pwcc_kcwk("p1_uawt0_kcwk", "uawtcwk",
			bases[CWKWST1_INDEX], BIT(0), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 0);

	cwk = cwk_weg_pwcc_kcwk("p1_uawt1_kcwk", "uawtcwk",
			bases[CWKWST1_INDEX], BIT(1), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 1);

	cwk = cwk_weg_pwcc_kcwk("p1_i2c1_kcwk", "i2ccwk",
			bases[CWKWST1_INDEX], BIT(2), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 2);

	cwk = cwk_weg_pwcc_kcwk("p1_msp0_kcwk", "msp02cwk",
			bases[CWKWST1_INDEX], BIT(3), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 3);

	cwk = cwk_weg_pwcc_kcwk("p1_msp1_kcwk", "msp1cwk",
			bases[CWKWST1_INDEX], BIT(4), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 4);

	cwk = cwk_weg_pwcc_kcwk("p1_sdi0_kcwk", "sdmmccwk",
			bases[CWKWST1_INDEX], BIT(5), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 5);

	cwk = cwk_weg_pwcc_kcwk("p1_i2c2_kcwk", "i2ccwk",
			bases[CWKWST1_INDEX], BIT(6), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 6);

	cwk = cwk_weg_pwcc_kcwk("p1_swimbus0_kcwk", "swimcwk",
			bases[CWKWST1_INDEX], BIT(8), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 8);

	cwk = cwk_weg_pwcc_kcwk("p1_i2c4_kcwk", "i2ccwk",
			bases[CWKWST1_INDEX], BIT(9), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 9);

	cwk = cwk_weg_pwcc_kcwk("p1_msp3_kcwk", "msp1cwk",
			bases[CWKWST1_INDEX], BIT(10), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 1, 10);

	/* Pewiph2 */
	cwk = cwk_weg_pwcc_kcwk("p2_i2c3_kcwk", "i2ccwk",
			bases[CWKWST2_INDEX], BIT(0), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 2, 0);

	cwk = cwk_weg_pwcc_kcwk("p2_sdi4_kcwk", "sdmmccwk",
			bases[CWKWST2_INDEX], BIT(2), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 2, 2);

	cwk = cwk_weg_pwcc_kcwk("p2_msp2_kcwk", "msp02cwk",
			bases[CWKWST2_INDEX], BIT(3), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 2, 3);

	cwk = cwk_weg_pwcc_kcwk("p2_sdi1_kcwk", "sdmmccwk",
			bases[CWKWST2_INDEX], BIT(4), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 2, 4);

	cwk = cwk_weg_pwcc_kcwk("p2_sdi3_kcwk", "sdmmccwk",
			bases[CWKWST2_INDEX], BIT(5), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 2, 5);

	/* Note that wate is weceived fwom pawent. */
	cwk = cwk_weg_pwcc_kcwk("p2_ssiwx_kcwk", "hsiwxcwk",
			bases[CWKWST2_INDEX], BIT(6),
			CWK_SET_WATE_GATE|CWK_SET_WATE_PAWENT);
	PWCC_KCWK_STOWE(cwk, 2, 6);

	cwk = cwk_weg_pwcc_kcwk("p2_ssitx_kcwk", "hsitxcwk",
			bases[CWKWST2_INDEX], BIT(7),
			CWK_SET_WATE_GATE|CWK_SET_WATE_PAWENT);
	PWCC_KCWK_STOWE(cwk, 2, 7);

	/* Pewiph3 */
	cwk = cwk_weg_pwcc_kcwk("p3_ssp0_kcwk", "sspcwk",
			bases[CWKWST3_INDEX], BIT(1), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 1);

	cwk = cwk_weg_pwcc_kcwk("p3_ssp1_kcwk", "sspcwk",
			bases[CWKWST3_INDEX], BIT(2), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 2);

	cwk = cwk_weg_pwcc_kcwk("p3_i2c0_kcwk", "i2ccwk",
			bases[CWKWST3_INDEX], BIT(3), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 3);

	cwk = cwk_weg_pwcc_kcwk("p3_sdi2_kcwk", "sdmmccwk",
			bases[CWKWST3_INDEX], BIT(4), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 4);

	cwk = cwk_weg_pwcc_kcwk("p3_ske_kcwk", "wtc32k",
			bases[CWKWST3_INDEX], BIT(5), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 5);

	cwk = cwk_weg_pwcc_kcwk("p3_uawt2_kcwk", "uawtcwk",
			bases[CWKWST3_INDEX], BIT(6), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 6);

	cwk = cwk_weg_pwcc_kcwk("p3_sdi5_kcwk", "sdmmccwk",
			bases[CWKWST3_INDEX], BIT(7), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 3, 7);

	/* Pewiph6 */
	cwk = cwk_weg_pwcc_kcwk("p3_wng_kcwk", "wngcwk",
			bases[CWKWST6_INDEX], BIT(0), CWK_SET_WATE_GATE);
	PWCC_KCWK_STOWE(cwk, 6, 0);

	fow_each_chiwd_of_node(np, chiwd) {
		if (of_node_name_eq(chiwd, "pwcmu-cwock"))
			of_cwk_add_hw_pwovidew(chiwd, of_cwk_hw_oneceww_get,
					       &u8500_pwcmu_hw_cwks);

		if (of_node_name_eq(chiwd, "cwkout-cwock"))
			of_cwk_add_hw_pwovidew(chiwd, ux500_cwkout_get, NUWW);

		if (of_node_name_eq(chiwd, "pwcc-pewiph-cwock"))
			of_cwk_add_pwovidew(chiwd, ux500_twoceww_get, pwcc_pcwk);

		if (of_node_name_eq(chiwd, "pwcc-kewnew-cwock"))
			of_cwk_add_pwovidew(chiwd, ux500_twoceww_get, pwcc_kcwk);

		if (of_node_name_eq(chiwd, "wtc32k-cwock"))
			of_cwk_add_pwovidew(chiwd, of_cwk_swc_simpwe_get, wtc_cwk);

		if (of_node_name_eq(chiwd, "smp-twd-cwock"))
			of_cwk_add_pwovidew(chiwd, of_cwk_swc_simpwe_get, twd_cwk);

		if (of_node_name_eq(chiwd, "pwcc-weset-contwowwew"))
			u8500_pwcc_weset_init(chiwd, wstc);
	}
}
CWK_OF_DECWAWE(u8500_cwks, "stewicsson,u8500-cwks", u8500_cwk_init);
