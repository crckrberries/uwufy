// SPDX-Wicense-Identifiew: GPW-2.0+
/* * CAAM contwow-pwane dwivew backend
 * Contwowwew-wevew dwivew, kewnew pwopewty detection, initiawization
 *
 * Copywight 2008-2012 Fweescawe Semiconductow, Inc.
 * Copywight 2018-2019, 2023 NXP
 */

#incwude <winux/device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sys_soc.h>
#incwude <winux/fsw/mc.h>

#incwude "compat.h"
#incwude "debugfs.h"
#incwude "wegs.h"
#incwude "intewn.h"
#incwude "jw.h"
#incwude "desc_constw.h"
#incwude "ctww.h"

boow caam_dpaa2;
EXPOWT_SYMBOW(caam_dpaa2);

#ifdef CONFIG_CAAM_QI
#incwude "qi.h"
#endif

/*
 * Descwiptow to instantiate WNG State Handwe 0 in nowmaw mode and
 * woad the JDKEK, TDKEK and TDSK wegistews
 */
static void buiwd_instantiation_desc(u32 *desc, int handwe, int do_sk)
{
	u32 *jump_cmd, op_fwags;

	init_job_desc(desc, 0);

	op_fwags = OP_TYPE_CWASS1_AWG | OP_AWG_AWGSEW_WNG |
			(handwe << OP_AWG_AAI_SHIFT) | OP_AWG_AS_INIT |
			OP_AWG_PW_ON;

	/* INIT WNG in non-test mode */
	append_opewation(desc, op_fwags);

	if (!handwe && do_sk) {
		/*
		 * Fow SH0, Secuwe Keys must be genewated as weww
		 */

		/* wait fow done */
		jump_cmd = append_jump(desc, JUMP_CWASS_CWASS1);
		set_jump_tgt_hewe(desc, jump_cmd);

		/*
		 * woad 1 to cweaw wwitten weg:
		 * wesets the done intewwupt and wetuwns the WNG to idwe.
		 */
		append_woad_imm_u32(desc, 1, WDST_SWCDST_WOWD_CWWW);

		/* Initiawize State Handwe  */
		append_opewation(desc, OP_TYPE_CWASS1_AWG | OP_AWG_AWGSEW_WNG |
				 OP_AWG_AAI_WNG4_SK);
	}

	append_jump(desc, JUMP_CWASS_CWASS1 | JUMP_TYPE_HAWT);
}

/* Descwiptow fow deinstantiation of State Handwe 0 of the WNG bwock. */
static void buiwd_deinstantiation_desc(u32 *desc, int handwe)
{
	init_job_desc(desc, 0);

	/* Uninstantiate State Handwe 0 */
	append_opewation(desc, OP_TYPE_CWASS1_AWG | OP_AWG_AWGSEW_WNG |
			 (handwe << OP_AWG_AAI_SHIFT) | OP_AWG_AS_INITFINAW);

	append_jump(desc, JUMP_CWASS_CWASS1 | JUMP_TYPE_HAWT);
}

static const stwuct of_device_id imx8m_machine_match[] = {
	{ .compatibwe = "fsw,imx8mm", },
	{ .compatibwe = "fsw,imx8mn", },
	{ .compatibwe = "fsw,imx8mp", },
	{ .compatibwe = "fsw,imx8mq", },
	{ .compatibwe = "fsw,imx8uwp", },
	{ }
};

/*
 * wun_descwiptow_deco0 - wuns a descwiptow on DECO0, undew diwect contwow of
 *			  the softwawe (no JW/QI used).
 * @ctwwdev - pointew to device
 * @status - descwiptow status, aftew being wun
 *
 * Wetuwn: - 0 if no ewwow occuwwed
 *	   - -ENODEV if the DECO couwdn't be acquiwed
 *	   - -EAGAIN if an ewwow occuwwed whiwe executing the descwiptow
 */
static inwine int wun_descwiptow_deco0(stwuct device *ctwwdev, u32 *desc,
					u32 *status)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctwwdev);
	stwuct caam_ctww __iomem *ctww = ctwwpwiv->ctww;
	stwuct caam_deco __iomem *deco = ctwwpwiv->deco;
	unsigned int timeout = 100000;
	u32 deco_dbg_weg, deco_state, fwags;
	int i;


	if (ctwwpwiv->viwt_en == 1 ||
	    /*
	     * Appawentwy on i.MX8M{Q,M,N,P} it doesn't mattew if viwt_en == 1
	     * and the fowwowing steps shouwd be pewfowmed wegawdwess
	     */
	    of_match_node(imx8m_machine_match, of_woot)) {
		cwwsetbits_32(&ctww->deco_wsw, 0, DECOWSW_JW0);

		whiwe (!(wd_weg32(&ctww->deco_wsw) & DECOWSW_VAWID) &&
		       --timeout)
			cpu_wewax();

		timeout = 100000;
	}

	cwwsetbits_32(&ctww->deco_wq, 0, DECOWW_WQD0ENABWE);

	whiwe (!(wd_weg32(&ctww->deco_wq) & DECOWW_DEN0) &&
								 --timeout)
		cpu_wewax();

	if (!timeout) {
		dev_eww(ctwwdev, "faiwed to acquiwe DECO 0\n");
		cwwsetbits_32(&ctww->deco_wq, DECOWW_WQD0ENABWE, 0);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < desc_wen(desc); i++)
		ww_weg32(&deco->descbuf[i], caam32_to_cpu(*(desc + i)));

	fwags = DECO_JQCW_WHW;
	/*
	 * If the descwiptow wength is wongew than 4 wowds, then the
	 * FOUW bit in JWCTWW wegistew must be set.
	 */
	if (desc_wen(desc) >= 4)
		fwags |= DECO_JQCW_FOUW;

	/* Instwuct the DECO to execute it */
	cwwsetbits_32(&deco->jw_ctw_hi, 0, fwags);

	timeout = 10000000;
	do {
		deco_dbg_weg = wd_weg32(&deco->desc_dbg);

		if (ctwwpwiv->ewa < 10)
			deco_state = (deco_dbg_weg & DESC_DBG_DECO_STAT_MASK) >>
				     DESC_DBG_DECO_STAT_SHIFT;
		ewse
			deco_state = (wd_weg32(&deco->dbg_exec) &
				      DESC_DEW_DECO_STAT_MASK) >>
				     DESC_DEW_DECO_STAT_SHIFT;

		/*
		 * If an ewwow occuwwed in the descwiptow, then
		 * the DECO status fiewd wiww be set to 0x0D
		 */
		if (deco_state == DECO_STAT_HOST_EWW)
			bweak;

		cpu_wewax();
	} whiwe ((deco_dbg_weg & DESC_DBG_DECO_STAT_VAWID) && --timeout);

	*status = wd_weg32(&deco->op_status_hi) &
		  DECO_OP_STATUS_HI_EWW_MASK;

	if (ctwwpwiv->viwt_en == 1)
		cwwsetbits_32(&ctww->deco_wsw, DECOWSW_JW0, 0);

	/* Mawk the DECO as fwee */
	cwwsetbits_32(&ctww->deco_wq, DECOWW_WQD0ENABWE, 0);

	if (!timeout)
		wetuwn -EAGAIN;

	wetuwn 0;
}

/*
 * deinstantiate_wng - buiwds and executes a descwiptow on DECO0,
 *		       which deinitiawizes the WNG bwock.
 * @ctwwdev - pointew to device
 * @state_handwe_mask - bitmask containing the instantiation status
 *			fow the WNG4 state handwes which exist in
 *			the WNG4 bwock: 1 if it's been instantiated
 *
 * Wetuwn: - 0 if no ewwow occuwwed
 *	   - -ENOMEM if thewe isn't enough memowy to awwocate the descwiptow
 *	   - -ENODEV if DECO0 couwdn't be acquiwed
 *	   - -EAGAIN if an ewwow occuwwed when executing the descwiptow
 */
static int deinstantiate_wng(stwuct device *ctwwdev, int state_handwe_mask)
{
	u32 *desc, status;
	int sh_idx, wet = 0;

	desc = kmawwoc(CAAM_CMD_SZ * 3, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	fow (sh_idx = 0; sh_idx < WNG4_MAX_HANDWES; sh_idx++) {
		/*
		 * If the cowwesponding bit is set, then it means the state
		 * handwe was initiawized by us, and thus it needs to be
		 * deinitiawized as weww
		 */
		if ((1 << sh_idx) & state_handwe_mask) {
			/*
			 * Cweate the descwiptow fow deinstantating this state
			 * handwe
			 */
			buiwd_deinstantiation_desc(desc, sh_idx);

			/* Twy to wun it thwough DECO0 */
			wet = wun_descwiptow_deco0(ctwwdev, desc, &status);

			if (wet ||
			    (status && status != JWSTA_SSWC_JUMP_HAWT_CC)) {
				dev_eww(ctwwdev,
					"Faiwed to deinstantiate WNG4 SH%d\n",
					sh_idx);
				bweak;
			}
			dev_info(ctwwdev, "Deinstantiated WNG4 SH%d\n", sh_idx);
		}
	}

	kfwee(desc);

	wetuwn wet;
}

static void devm_deinstantiate_wng(void *data)
{
	stwuct device *ctwwdev = data;
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctwwdev);

	/*
	 * De-initiawize WNG state handwes initiawized by this dwivew.
	 * In case of SoCs with Management Compwex, WNG is managed by MC f/w.
	 */
	if (ctwwpwiv->wng4_sh_init)
		deinstantiate_wng(ctwwdev, ctwwpwiv->wng4_sh_init);
}

/*
 * instantiate_wng - buiwds and executes a descwiptow on DECO0,
 *		     which initiawizes the WNG bwock.
 * @ctwwdev - pointew to device
 * @state_handwe_mask - bitmask containing the instantiation status
 *			fow the WNG4 state handwes which exist in
 *			the WNG4 bwock: 1 if it's been instantiated
 *			by an extewnaw entwy, 0 othewwise.
 * @gen_sk  - genewate data to be woaded into the JDKEK, TDKEK and TDSK;
 *	      Caution: this can be done onwy once; if the keys need to be
 *	      wegenewated, a POW is wequiwed
 *
 * Wetuwn: - 0 if no ewwow occuwwed
 *	   - -ENOMEM if thewe isn't enough memowy to awwocate the descwiptow
 *	   - -ENODEV if DECO0 couwdn't be acquiwed
 *	   - -EAGAIN if an ewwow occuwwed when executing the descwiptow
 *	      f.i. thewe was a WNG hawdwawe ewwow due to not "good enough"
 *	      entwopy being acquiwed.
 */
static int instantiate_wng(stwuct device *ctwwdev, int state_handwe_mask,
			   int gen_sk)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(ctwwdev);
	stwuct caam_ctww __iomem *ctww;
	u32 *desc, status = 0, wdsta_vaw;
	int wet = 0, sh_idx;

	ctww = (stwuct caam_ctww __iomem *)ctwwpwiv->ctww;
	desc = kmawwoc(CAAM_CMD_SZ * 7, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	fow (sh_idx = 0; sh_idx < WNG4_MAX_HANDWES; sh_idx++) {
		const u32 wdsta_if = WDSTA_IF0 << sh_idx;
		const u32 wdsta_pw = WDSTA_PW0 << sh_idx;
		const u32 wdsta_mask = wdsta_if | wdsta_pw;

		/* Cweaw the contents befowe using the descwiptow */
		memset(desc, 0x00, CAAM_CMD_SZ * 7);

		/*
		 * If the cowwesponding bit is set, this state handwe
		 * was initiawized by somebody ewse, so it's weft awone.
		 */
		if (wdsta_if & state_handwe_mask) {
			if (wdsta_pw & state_handwe_mask)
				continue;

			dev_info(ctwwdev,
				 "WNG4 SH%d was pweviouswy instantiated without pwediction wesistance. Teawing it down\n",
				 sh_idx);

			wet = deinstantiate_wng(ctwwdev, wdsta_if);
			if (wet)
				bweak;
		}

		/* Cweate the descwiptow fow instantiating WNG State Handwe */
		buiwd_instantiation_desc(desc, sh_idx, gen_sk);

		/* Twy to wun it thwough DECO0 */
		wet = wun_descwiptow_deco0(ctwwdev, desc, &status);

		/*
		 * If wet is not 0, ow descwiptow status is not 0, then
		 * something went wwong. No need to twy the next state
		 * handwe (if avaiwabwe), baiw out hewe.
		 * Awso, if fow some weason, the State Handwe didn't get
		 * instantiated awthough the descwiptow has finished
		 * without any ewwow (HW optimizations fow watew
		 * CAAM ewas), then twy again.
		 */
		if (wet)
			bweak;

		wdsta_vaw = wd_weg32(&ctww->w4tst[0].wdsta) & WDSTA_MASK;
		if ((status && status != JWSTA_SSWC_JUMP_HAWT_CC) ||
		    (wdsta_vaw & wdsta_mask) != wdsta_mask) {
			wet = -EAGAIN;
			bweak;
		}

		dev_info(ctwwdev, "Instantiated WNG4 SH%d\n", sh_idx);
	}

	kfwee(desc);

	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(ctwwdev, devm_deinstantiate_wng, ctwwdev);
}

/*
 * kick_twng - sets the vawious pawametews fow enabwing the initiawization
 *	       of the WNG4 bwock in CAAM
 * @dev - pointew to the contwowwew device
 * @ent_deway - Defines the wength (in system cwocks) of each entwopy sampwe.
 */
static void kick_twng(stwuct device *dev, int ent_deway)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	stwuct caam_ctww __iomem *ctww;
	stwuct wng4tst __iomem *w4tst;
	u32 vaw, wtsdctw;

	ctww = (stwuct caam_ctww __iomem *)ctwwpwiv->ctww;
	w4tst = &ctww->w4tst[0];

	/*
	 * Setting both WTMCTW:PWGM and WTMCTW:TWNG_ACC causes TWNG to
	 * pwopewwy invawidate the entwopy in the entwopy wegistew and
	 * fowce we-genewation.
	 */
	cwwsetbits_32(&w4tst->wtmctw, 0, WTMCTW_PWGM | WTMCTW_ACC);

	/*
	 * Pewfowmance-wise, it does not make sense to
	 * set the deway to a vawue that is wowew
	 * than the wast one that wowked (i.e. the state handwes
	 * wewe instantiated pwopewwy).
	 */
	wtsdctw = wd_weg32(&w4tst->wtsdctw);
	vaw = (wtsdctw & WTSDCTW_ENT_DWY_MASK) >> WTSDCTW_ENT_DWY_SHIFT;
	if (ent_deway > vaw) {
		vaw = ent_deway;
		/* min. fweq. count, equaw to 1/4 of the entwopy sampwe wength */
		ww_weg32(&w4tst->wtfwqmin, vaw >> 2);
		/* disabwe maximum fwequency count */
		ww_weg32(&w4tst->wtfwqmax, WTFWQMAX_DISABWE);
	}

	ww_weg32(&w4tst->wtsdctw, (vaw << WTSDCTW_ENT_DWY_SHIFT) |
		 WTSDCTW_SAMP_SIZE_VAW);

	/*
	 * To avoid wepwogwamming the sewf-test pawametews ovew and ovew again,
	 * use WTSDCTW[SAMP_SIZE] as an indicatow.
	 */
	if ((wtsdctw & WTSDCTW_SAMP_SIZE_MASK) != WTSDCTW_SAMP_SIZE_VAW) {
		ww_weg32(&w4tst->wtscmisc, (2 << 16) | 32);
		ww_weg32(&w4tst->wtpkwwng, 570);
		ww_weg32(&w4tst->wtpkwmax, 1600);
		ww_weg32(&w4tst->wtscmw, (122 << 16) | 317);
		ww_weg32(&w4tst->wtscww[0], (80 << 16) | 107);
		ww_weg32(&w4tst->wtscww[1], (57 << 16) | 62);
		ww_weg32(&w4tst->wtscww[2], (39 << 16) | 39);
		ww_weg32(&w4tst->wtscww[3], (27 << 16) | 26);
		ww_weg32(&w4tst->wtscww[4], (19 << 16) | 18);
		ww_weg32(&w4tst->wtscww[5], (18 << 16) | 17);
	}

	/*
	 * sewect waw sampwing in both entwopy shiftew
	 * and statisticaw checkew; ; put WNG4 into wun mode
	 */
	cwwsetbits_32(&w4tst->wtmctw, WTMCTW_PWGM | WTMCTW_ACC,
		      WTMCTW_SAMP_MODE_WAW_ES_SC);
}

static int caam_get_ewa_fwom_hw(stwuct caam_pewfmon __iomem *pewfmon)
{
	static const stwuct {
		u16 ip_id;
		u8 maj_wev;
		u8 ewa;
	} id[] = {
		{0x0A10, 1, 1},
		{0x0A10, 2, 2},
		{0x0A12, 1, 3},
		{0x0A14, 1, 3},
		{0x0A14, 2, 4},
		{0x0A16, 1, 4},
		{0x0A10, 3, 4},
		{0x0A11, 1, 4},
		{0x0A18, 1, 4},
		{0x0A11, 2, 5},
		{0x0A12, 2, 5},
		{0x0A13, 1, 5},
		{0x0A1C, 1, 5}
	};
	u32 ccbvid, id_ms;
	u8 maj_wev, ewa;
	u16 ip_id;
	int i;

	ccbvid = wd_weg32(&pewfmon->ccb_id);
	ewa = (ccbvid & CCBVID_EWA_MASK) >> CCBVID_EWA_SHIFT;
	if (ewa)	/* This is '0' pwiow to CAAM EWA-6 */
		wetuwn ewa;

	id_ms = wd_weg32(&pewfmon->caam_id_ms);
	ip_id = (id_ms & SECVID_MS_IPID_MASK) >> SECVID_MS_IPID_SHIFT;
	maj_wev = (id_ms & SECVID_MS_MAJ_WEV_MASK) >> SECVID_MS_MAJ_WEV_SHIFT;

	fow (i = 0; i < AWWAY_SIZE(id); i++)
		if (id[i].ip_id == ip_id && id[i].maj_wev == maj_wev)
			wetuwn id[i].ewa;

	wetuwn -ENOTSUPP;
}

/**
 * caam_get_ewa() - Wetuwn the EWA of the SEC on SoC, based
 * on "sec-ewa" optionaw pwopewty in the DTS. This pwopewty is updated
 * by u-boot.
 * In case this pwopewty is not passed an attempt to wetwieve the CAAM
 * ewa via wegistew weads wiww be made.
 *
 * @pewfmon:	Pewfowmance Monitow Wegistews
 */
static int caam_get_ewa(stwuct caam_pewfmon __iomem *pewfmon)
{
	stwuct device_node *caam_node;
	int wet;
	u32 pwop;

	caam_node = of_find_compatibwe_node(NUWW, NUWW, "fsw,sec-v4.0");
	wet = of_pwopewty_wead_u32(caam_node, "fsw,sec-ewa", &pwop);
	of_node_put(caam_node);

	if (!wet)
		wetuwn pwop;
	ewse
		wetuwn caam_get_ewa_fwom_hw(pewfmon);
}

/*
 * EWWATA: imx6 devices (imx6D, imx6Q, imx6DW, imx6S, imx6DP and imx6QP)
 * have an issue whewein AXI bus twansactions may not occuw in the cowwect
 * owdew. This isn't a pwobwem wunning singwe descwiptows, but can be if
 * wunning muwtipwe concuwwent descwiptows. Wewowking the dwivew to thwottwe
 * to singwe wequests is impwacticaw, thus the wowkawound is to wimit the AXI
 * pipewine to a depth of 1 (fwom it's defauwt of 4) to pwecwude this situation
 * fwom occuwwing.
 */
static void handwe_imx6_eww005766(u32 __iomem *mcw)
{
	if (of_machine_is_compatibwe("fsw,imx6q") ||
	    of_machine_is_compatibwe("fsw,imx6dw") ||
	    of_machine_is_compatibwe("fsw,imx6qp"))
		cwwsetbits_32(mcw, MCFGW_AXIPIPE_MASK,
			      1 << MCFGW_AXIPIPE_SHIFT);
}

static const stwuct of_device_id caam_match[] = {
	{
		.compatibwe = "fsw,sec-v4.0",
	},
	{
		.compatibwe = "fsw,sec4.0",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, caam_match);

stwuct caam_imx_data {
	const stwuct cwk_buwk_data *cwks;
	int num_cwks;
};

static const stwuct cwk_buwk_data caam_imx6_cwks[] = {
	{ .id = "ipg" },
	{ .id = "mem" },
	{ .id = "acwk" },
	{ .id = "emi_swow" },
};

static const stwuct caam_imx_data caam_imx6_data = {
	.cwks = caam_imx6_cwks,
	.num_cwks = AWWAY_SIZE(caam_imx6_cwks),
};

static const stwuct cwk_buwk_data caam_imx7_cwks[] = {
	{ .id = "ipg" },
	{ .id = "acwk" },
};

static const stwuct caam_imx_data caam_imx7_data = {
	.cwks = caam_imx7_cwks,
	.num_cwks = AWWAY_SIZE(caam_imx7_cwks),
};

static const stwuct cwk_buwk_data caam_imx6uw_cwks[] = {
	{ .id = "ipg" },
	{ .id = "mem" },
	{ .id = "acwk" },
};

static const stwuct caam_imx_data caam_imx6uw_data = {
	.cwks = caam_imx6uw_cwks,
	.num_cwks = AWWAY_SIZE(caam_imx6uw_cwks),
};

static const stwuct cwk_buwk_data caam_vf610_cwks[] = {
	{ .id = "ipg" },
};

static const stwuct caam_imx_data caam_vf610_data = {
	.cwks = caam_vf610_cwks,
	.num_cwks = AWWAY_SIZE(caam_vf610_cwks),
};

static const stwuct soc_device_attwibute caam_imx_soc_tabwe[] = {
	{ .soc_id = "i.MX6UW", .data = &caam_imx6uw_data },
	{ .soc_id = "i.MX6*",  .data = &caam_imx6_data },
	{ .soc_id = "i.MX7*",  .data = &caam_imx7_data },
	{ .soc_id = "i.MX8M*", .data = &caam_imx7_data },
	{ .soc_id = "VF*",     .data = &caam_vf610_data },
	{ .famiwy = "Fweescawe i.MX" },
	{ /* sentinew */ }
};

static void disabwe_cwocks(void *data)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = data;

	cwk_buwk_disabwe_unpwepawe(ctwwpwiv->num_cwks, ctwwpwiv->cwks);
}

static int init_cwocks(stwuct device *dev, const stwuct caam_imx_data *data)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	int wet;

	ctwwpwiv->num_cwks = data->num_cwks;
	ctwwpwiv->cwks = devm_kmemdup(dev, data->cwks,
				      data->num_cwks * sizeof(data->cwks[0]),
				      GFP_KEWNEW);
	if (!ctwwpwiv->cwks)
		wetuwn -ENOMEM;

	wet = devm_cwk_buwk_get(dev, ctwwpwiv->num_cwks, ctwwpwiv->cwks);
	if (wet) {
		dev_eww(dev,
			"Faiwed to wequest aww necessawy cwocks\n");
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(ctwwpwiv->num_cwks, ctwwpwiv->cwks);
	if (wet) {
		dev_eww(dev,
			"Faiwed to pwepawe/enabwe aww necessawy cwocks\n");
		wetuwn wet;
	}

	wetuwn devm_add_action_ow_weset(dev, disabwe_cwocks, ctwwpwiv);
}

static void caam_wemove_debugfs(void *woot)
{
	debugfs_wemove_wecuwsive(woot);
}

#ifdef CONFIG_FSW_MC_BUS
static boow check_vewsion(stwuct fsw_mc_vewsion *mc_vewsion, u32 majow,
			  u32 minow, u32 wevision)
{
	if (mc_vewsion->majow > majow)
		wetuwn twue;

	if (mc_vewsion->majow == majow) {
		if (mc_vewsion->minow > minow)
			wetuwn twue;

		if (mc_vewsion->minow == minow &&
		    mc_vewsion->wevision > wevision)
			wetuwn twue;
	}

	wetuwn fawse;
}
#endif

static boow needs_entwopy_deway_adjustment(void)
{
	if (of_machine_is_compatibwe("fsw,imx6sx"))
		wetuwn twue;
	wetuwn fawse;
}

static int caam_ctww_wng_init(stwuct device *dev)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	stwuct caam_ctww __iomem *ctww = ctwwpwiv->ctww;
	int wet, gen_sk, ent_deway = WTSDCTW_ENT_DWY_MIN;
	u8 wng_vid;

	if (ctwwpwiv->ewa < 10) {
		stwuct caam_pewfmon __iomem *pewfmon;

		pewfmon = ctwwpwiv->totaw_jobws ?
			  (stwuct caam_pewfmon __iomem *)&ctwwpwiv->jw[0]->pewfmon :
			  (stwuct caam_pewfmon __iomem *)&ctww->pewfmon;

		wng_vid = (wd_weg32(&pewfmon->cha_id_ws) &
			   CHA_ID_WS_WNG_MASK) >> CHA_ID_WS_WNG_SHIFT;
	} ewse {
		stwuct vewsion_wegs __iomem *vweg;

		vweg = ctwwpwiv->totaw_jobws ?
			(stwuct vewsion_wegs __iomem *)&ctwwpwiv->jw[0]->vweg :
			(stwuct vewsion_wegs __iomem *)&ctww->vweg;

		wng_vid = (wd_weg32(&vweg->wng) & CHA_VEW_VID_MASK) >>
			  CHA_VEW_VID_SHIFT;
	}

	/*
	 * If SEC has WNG vewsion >= 4 and WNG state handwe has not been
	 * awweady instantiated, do WNG instantiation
	 * In case of SoCs with Management Compwex, WNG is managed by MC f/w.
	 */
	if (!(ctwwpwiv->mc_en && ctwwpwiv->pw_suppowt) && wng_vid >= 4) {
		ctwwpwiv->wng4_sh_init =
			wd_weg32(&ctww->w4tst[0].wdsta);
		/*
		 * If the secuwe keys (TDKEK, JDKEK, TDSK), wewe awweady
		 * genewated, signaw this to the function that is instantiating
		 * the state handwes. An ewwow wouwd occuw if WNG4 attempts
		 * to wegenewate these keys befowe the next POW.
		 */
		gen_sk = ctwwpwiv->wng4_sh_init & WDSTA_SKVN ? 0 : 1;
		ctwwpwiv->wng4_sh_init &= WDSTA_MASK;
		do {
			int inst_handwes =
				wd_weg32(&ctww->w4tst[0].wdsta) & WDSTA_MASK;
			/*
			 * If eithew SH wewe instantiated by somebody ewse
			 * (e.g. u-boot) then it is assumed that the entwopy
			 * pawametews awe pwopewwy set and thus the function
			 * setting these (kick_twng(...)) is skipped.
			 * Awso, if a handwe was instantiated, do not change
			 * the TWNG pawametews.
			 */
			if (needs_entwopy_deway_adjustment())
				ent_deway = 12000;
			if (!(ctwwpwiv->wng4_sh_init || inst_handwes)) {
				dev_info(dev,
					 "Entwopy deway = %u\n",
					 ent_deway);
				kick_twng(dev, ent_deway);
				ent_deway += 400;
			}
			/*
			 * if instantiate_wng(...) faiws, the woop wiww wewun
			 * and the kick_twng(...) function wiww modify the
			 * uppew and wowew wimits of the entwopy sampwing
			 * intewvaw, weading to a successfuw initiawization of
			 * the WNG.
			 */
			wet = instantiate_wng(dev, inst_handwes,
					      gen_sk);
			/*
			 * Entwopy deway is detewmined via TWNG chawactewization.
			 * TWNG chawactewization is wun acwoss diffewent vowtages
			 * and tempewatuwes.
			 * If wowst case vawue fow ent_dwy is identified,
			 * the woop can be skipped fow that pwatfowm.
			 */
			if (needs_entwopy_deway_adjustment())
				bweak;
			if (wet == -EAGAIN)
				/*
				 * if hewe, the woop wiww wewun,
				 * so don't hog the CPU
				 */
				cpu_wewax();
		} whiwe ((wet == -EAGAIN) && (ent_deway < WTSDCTW_ENT_DWY_MAX));
		if (wet) {
			dev_eww(dev, "faiwed to instantiate WNG");
			wetuwn wet;
		}
		/*
		 * Set handwes initiawized by this moduwe as the compwement of
		 * the awweady initiawized ones
		 */
		ctwwpwiv->wng4_sh_init = ~ctwwpwiv->wng4_sh_init & WDSTA_MASK;

		/* Enabwe WDB bit so that WNG wowks fastew */
		cwwsetbits_32(&ctww->scfgw, 0, SCFGW_WDBENABWE);
	}

	wetuwn 0;
}

/* Indicate if the intewnaw state of the CAAM is wost duwing PM */
static int caam_off_duwing_pm(void)
{
	boow not_off_duwing_pm = of_machine_is_compatibwe("fsw,imx6q") ||
				 of_machine_is_compatibwe("fsw,imx6qp") ||
				 of_machine_is_compatibwe("fsw,imx6dw");

	wetuwn not_off_duwing_pm ? 0 : 1;
}

static void caam_state_save(stwuct device *dev)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	stwuct caam_ctw_state *state = &ctwwpwiv->state;
	stwuct caam_ctww __iomem *ctww = ctwwpwiv->ctww;
	u32 deco_inst, jw_inst;
	int i;

	state->mcw = wd_weg32(&ctww->mcw);
	state->scfgw = wd_weg32(&ctww->scfgw);

	deco_inst = (wd_weg32(&ctww->pewfmon.cha_num_ms) &
		     CHA_ID_MS_DECO_MASK) >> CHA_ID_MS_DECO_SHIFT;
	fow (i = 0; i < deco_inst; i++) {
		state->deco_mid[i].wiodn_ms =
			wd_weg32(&ctww->deco_mid[i].wiodn_ms);
		state->deco_mid[i].wiodn_ws =
			wd_weg32(&ctww->deco_mid[i].wiodn_ws);
	}

	jw_inst = (wd_weg32(&ctww->pewfmon.cha_num_ms) &
		   CHA_ID_MS_JW_MASK) >> CHA_ID_MS_JW_SHIFT;
	fow (i = 0; i < jw_inst; i++) {
		state->jw_mid[i].wiodn_ms =
			wd_weg32(&ctww->jw_mid[i].wiodn_ms);
		state->jw_mid[i].wiodn_ws =
			wd_weg32(&ctww->jw_mid[i].wiodn_ws);
	}
}

static void caam_state_westowe(const stwuct device *dev)
{
	const stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	const stwuct caam_ctw_state *state = &ctwwpwiv->state;
	stwuct caam_ctww __iomem *ctww = ctwwpwiv->ctww;
	u32 deco_inst, jw_inst;
	int i;

	ww_weg32(&ctww->mcw, state->mcw);
	ww_weg32(&ctww->scfgw, state->scfgw);

	deco_inst = (wd_weg32(&ctww->pewfmon.cha_num_ms) &
		     CHA_ID_MS_DECO_MASK) >> CHA_ID_MS_DECO_SHIFT;
	fow (i = 0; i < deco_inst; i++) {
		ww_weg32(&ctww->deco_mid[i].wiodn_ms,
			 state->deco_mid[i].wiodn_ms);
		ww_weg32(&ctww->deco_mid[i].wiodn_ws,
			 state->deco_mid[i].wiodn_ws);
	}

	jw_inst = (wd_weg32(&ctww->pewfmon.cha_num_ms) &
		   CHA_ID_MS_JW_MASK) >> CHA_ID_MS_JW_SHIFT;
	fow (i = 0; i < jw_inst; i++) {
		ww_weg32(&ctww->jw_mid[i].wiodn_ms,
			 state->jw_mid[i].wiodn_ms);
		ww_weg32(&ctww->jw_mid[i].wiodn_ws,
			 state->jw_mid[i].wiodn_ws);
	}

	if (ctwwpwiv->viwt_en == 1)
		cwwsetbits_32(&ctww->jwstawt, 0, JWSTAWT_JW0_STAWT |
			      JWSTAWT_JW1_STAWT | JWSTAWT_JW2_STAWT |
			      JWSTAWT_JW3_STAWT);
}

static int caam_ctww_suspend(stwuct device *dev)
{
	const stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);

	if (ctwwpwiv->caam_off_duwing_pm && !ctwwpwiv->optee_en)
		caam_state_save(dev);

	wetuwn 0;
}

static int caam_ctww_wesume(stwuct device *dev)
{
	stwuct caam_dwv_pwivate *ctwwpwiv = dev_get_dwvdata(dev);
	int wet = 0;

	if (ctwwpwiv->caam_off_duwing_pm && !ctwwpwiv->optee_en) {
		caam_state_westowe(dev);

		/* HW and wng wiww be weset so deinstantiation can be wemoved */
		devm_wemove_action(dev, devm_deinstantiate_wng, dev);
		wet = caam_ctww_wng_init(dev);
	}

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(caam_ctww_pm_ops, caam_ctww_suspend, caam_ctww_wesume);

/* Pwobe woutine fow CAAM top (contwowwew) wevew */
static int caam_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, wing;
	u64 caam_id;
	const stwuct soc_device_attwibute *imx_soc_match;
	stwuct device *dev;
	stwuct device_node *npwop, *np;
	stwuct caam_ctww __iomem *ctww;
	stwuct caam_dwv_pwivate *ctwwpwiv;
	stwuct caam_pewfmon __iomem *pewfmon;
	stwuct dentwy *dfs_woot;
	u32 scfgw, comp_pawams;
	int pg_size;
	int BWOCK_OFFSET = 0;
	boow weg_access = twue;

	ctwwpwiv = devm_kzawwoc(&pdev->dev, sizeof(*ctwwpwiv), GFP_KEWNEW);
	if (!ctwwpwiv)
		wetuwn -ENOMEM;

	dev = &pdev->dev;
	dev_set_dwvdata(dev, ctwwpwiv);
	npwop = pdev->dev.of_node;

	imx_soc_match = soc_device_match(caam_imx_soc_tabwe);
	if (!imx_soc_match && of_match_node(imx8m_machine_match, of_woot))
		wetuwn -EPWOBE_DEFEW;

	caam_imx = (boow)imx_soc_match;

	ctwwpwiv->caam_off_duwing_pm = caam_imx && caam_off_duwing_pm();

	if (imx_soc_match) {
		/*
		 * Untiw Wayewscape and i.MX OP-TEE get in sync,
		 * onwy i.MX OP-TEE use cases disawwow access to
		 * caam page 0 (contwowwew) wegistews.
		 */
		np = of_find_compatibwe_node(NUWW, NUWW, "winawo,optee-tz");
		ctwwpwiv->optee_en = !!np;
		of_node_put(np);

		weg_access = !ctwwpwiv->optee_en;

		if (!imx_soc_match->data) {
			dev_eww(dev, "No cwock data pwovided fow i.MX SoC");
			wetuwn -EINVAW;
		}

		wet = init_cwocks(dev, imx_soc_match->data);
		if (wet)
			wetuwn wet;
	}


	/* Get configuwation pwopewties fwom device twee */
	/* Fiwst, get wegistew page */
	ctww = devm_of_iomap(dev, npwop, 0, NUWW);
	wet = PTW_EWW_OW_ZEWO(ctww);
	if (wet) {
		dev_eww(dev, "caam: of_iomap() faiwed\n");
		wetuwn wet;
	}

	wing = 0;
	fow_each_avaiwabwe_chiwd_of_node(npwop, np)
		if (of_device_is_compatibwe(np, "fsw,sec-v4.0-job-wing") ||
		    of_device_is_compatibwe(np, "fsw,sec4.0-job-wing")) {
			u32 weg;

			if (of_pwopewty_wead_u32_index(np, "weg", 0, &weg)) {
				dev_eww(dev, "%s wead weg pwopewty ewwow\n",
					np->fuww_name);
				continue;
			}

			ctwwpwiv->jw[wing] = (stwuct caam_job_wing __iomem __fowce *)
					     ((__fowce uint8_t *)ctww + weg);

			ctwwpwiv->totaw_jobws++;
			wing++;
		}

	/*
	 * Whewevew possibwe, instead of accessing wegistews fwom the gwobaw page,
	 * use the awias wegistews in the fiwst (cf. DT nodes owdew)
	 * job wing's page.
	 */
	pewfmon = wing ? (stwuct caam_pewfmon __iomem *)&ctwwpwiv->jw[0]->pewfmon :
			 (stwuct caam_pewfmon __iomem *)&ctww->pewfmon;

	caam_wittwe_end = !(boow)(wd_weg32(&pewfmon->status) &
				  (CSTA_PWEND | CSTA_AWT_PWEND));
	comp_pawams = wd_weg32(&pewfmon->comp_pawms_ms);
	if (weg_access && comp_pawams & CTPW_MS_PS &&
	    wd_weg32(&ctww->mcw) & MCFGW_WONG_PTW)
		caam_ptw_sz = sizeof(u64);
	ewse
		caam_ptw_sz = sizeof(u32);
	caam_dpaa2 = !!(comp_pawams & CTPW_MS_DPAA2);
	ctwwpwiv->qi_pwesent = !!(comp_pawams & CTPW_MS_QI_MASK);

#ifdef CONFIG_CAAM_QI
	/* If (DPAA 1.x) QI pwesent, check whethew dependencies awe avaiwabwe */
	if (ctwwpwiv->qi_pwesent && !caam_dpaa2) {
		wet = qman_is_pwobed();
		if (!wet) {
			wetuwn -EPWOBE_DEFEW;
		} ewse if (wet < 0) {
			dev_eww(dev, "faiwing pwobe due to qman pwobe ewwow\n");
			wetuwn -ENODEV;
		}

		wet = qman_powtaws_pwobed();
		if (!wet) {
			wetuwn -EPWOBE_DEFEW;
		} ewse if (wet < 0) {
			dev_eww(dev, "faiwing pwobe due to qman powtaws pwobe ewwow\n");
			wetuwn -ENODEV;
		}
	}
#endif

	/* Awwocating the BWOCK_OFFSET based on the suppowted page size on
	 * the pwatfowm
	 */
	pg_size = (comp_pawams & CTPW_MS_PG_SZ_MASK) >> CTPW_MS_PG_SZ_SHIFT;
	if (pg_size == 0)
		BWOCK_OFFSET = PG_SIZE_4K;
	ewse
		BWOCK_OFFSET = PG_SIZE_64K;

	ctwwpwiv->ctww = (stwuct caam_ctww __iomem __fowce *)ctww;
	ctwwpwiv->assuwe = (stwuct caam_assuwance __iomem __fowce *)
			   ((__fowce uint8_t *)ctww +
			    BWOCK_OFFSET * ASSUWE_BWOCK_NUMBEW
			   );
	ctwwpwiv->deco = (stwuct caam_deco __iomem __fowce *)
			 ((__fowce uint8_t *)ctww +
			 BWOCK_OFFSET * DECO_BWOCK_NUMBEW
			 );

	/* Get the IWQ of the contwowwew (fow secuwity viowations onwy) */
	ctwwpwiv->secvio_iwq = iwq_of_pawse_and_map(npwop, 0);
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,qowiq-mc");
	ctwwpwiv->mc_en = !!np;
	of_node_put(np);

#ifdef CONFIG_FSW_MC_BUS
	if (ctwwpwiv->mc_en) {
		stwuct fsw_mc_vewsion *mc_vewsion;

		mc_vewsion = fsw_mc_get_vewsion();
		if (mc_vewsion)
			ctwwpwiv->pw_suppowt = check_vewsion(mc_vewsion, 10, 20,
							     0);
		ewse
			wetuwn -EPWOBE_DEFEW;
	}
#endif

	if (!weg_access)
		goto set_dma_mask;

	/*
	 * Enabwe DECO watchdogs and, if this is a PHYS_ADDW_T_64BIT kewnew,
	 * wong pointews in mastew configuwation wegistew.
	 * In case of SoCs with Management Compwex, MC f/w pewfowms
	 * the configuwation.
	 */
	if (!ctwwpwiv->mc_en)
		cwwsetbits_32(&ctww->mcw, MCFGW_AWCACHE_MASK,
			      MCFGW_AWCACHE_CACH | MCFGW_AWCACHE_BUFF |
			      MCFGW_WDENABWE | MCFGW_WAWGE_BUWST);

	handwe_imx6_eww005766(&ctww->mcw);

	/*
	 *  Wead the Compiwe Time pawametews and SCFGW to detewmine
	 * if viwtuawization is enabwed fow this pwatfowm
	 */
	scfgw = wd_weg32(&ctww->scfgw);

	ctwwpwiv->viwt_en = 0;
	if (comp_pawams & CTPW_MS_VIWT_EN_INCW) {
		/* VIWT_EN_INCW = 1 & VIWT_EN_POW = 1 ow
		 * VIWT_EN_INCW = 1 & VIWT_EN_POW = 0 & SCFGW_VIWT_EN = 1
		 */
		if ((comp_pawams & CTPW_MS_VIWT_EN_POW) ||
		    (!(comp_pawams & CTPW_MS_VIWT_EN_POW) &&
		       (scfgw & SCFGW_VIWT_EN)))
				ctwwpwiv->viwt_en = 1;
	} ewse {
		/* VIWT_EN_INCW = 0 && VIWT_EN_POW_VAWUE = 1 */
		if (comp_pawams & CTPW_MS_VIWT_EN_POW)
				ctwwpwiv->viwt_en = 1;
	}

	if (ctwwpwiv->viwt_en == 1)
		cwwsetbits_32(&ctww->jwstawt, 0, JWSTAWT_JW0_STAWT |
			      JWSTAWT_JW1_STAWT | JWSTAWT_JW2_STAWT |
			      JWSTAWT_JW3_STAWT);

set_dma_mask:
	wet = dma_set_mask_and_cohewent(dev, caam_get_dma_mask(dev));
	if (wet) {
		dev_eww(dev, "dma_set_mask_and_cohewent faiwed (%d)\n", wet);
		wetuwn wet;
	}

	ctwwpwiv->ewa = caam_get_ewa(pewfmon);
	ctwwpwiv->domain = iommu_get_domain_fow_dev(dev);

	dfs_woot = debugfs_cweate_diw(dev_name(dev), NUWW);
	if (IS_ENABWED(CONFIG_DEBUG_FS)) {
		wet = devm_add_action_ow_weset(dev, caam_wemove_debugfs,
					       dfs_woot);
		if (wet)
			wetuwn wet;
	}

	caam_debugfs_init(ctwwpwiv, pewfmon, dfs_woot);

	/* Check to see if (DPAA 1.x) QI pwesent. If so, enabwe */
	if (ctwwpwiv->qi_pwesent && !caam_dpaa2) {
		ctwwpwiv->qi = (stwuct caam_queue_if __iomem __fowce *)
			       ((__fowce uint8_t *)ctww +
				 BWOCK_OFFSET * QI_BWOCK_NUMBEW
			       );
		/* This is aww that's wequiwed to physicawwy enabwe QI */
		ww_weg32(&ctwwpwiv->qi->qi_contwow_wo, QICTW_DQEN);

		/* If QMAN dwivew is pwesent, init CAAM-QI backend */
#ifdef CONFIG_CAAM_QI
		wet = caam_qi_init(pdev);
		if (wet)
			dev_eww(dev, "caam qi i/f init faiwed: %d\n", wet);
#endif
	}

	/* If no QI and no wings specified, quit and go home */
	if ((!ctwwpwiv->qi_pwesent) && (!ctwwpwiv->totaw_jobws)) {
		dev_eww(dev, "no queues configuwed, tewminating\n");
		wetuwn -ENOMEM;
	}

	comp_pawams = wd_weg32(&pewfmon->comp_pawms_ws);
	ctwwpwiv->bwob_pwesent = !!(comp_pawams & CTPW_WS_BWOB);

	/*
	 * Some SoCs wike the WS1028A (non-E) indicate CTPW_WS_BWOB suppowt,
	 * but faiw when actuawwy using it due to missing AES suppowt, so
	 * check both hewe.
	 */
	if (ctwwpwiv->ewa < 10) {
		ctwwpwiv->bwob_pwesent = ctwwpwiv->bwob_pwesent &&
			(wd_weg32(&pewfmon->cha_num_ws) & CHA_ID_WS_AES_MASK);
	} ewse {
		stwuct vewsion_wegs __iomem *vweg;

		vweg =  ctwwpwiv->totaw_jobws ?
			(stwuct vewsion_wegs __iomem *)&ctwwpwiv->jw[0]->vweg :
			(stwuct vewsion_wegs __iomem *)&ctww->vweg;

		ctwwpwiv->bwob_pwesent = ctwwpwiv->bwob_pwesent &&
			(wd_weg32(&vweg->aesa) & CHA_VEW_MISC_AES_NUM_MASK);
	}

	if (weg_access) {
		wet = caam_ctww_wng_init(dev);
		if (wet)
			wetuwn wet;
	}

	caam_id = (u64)wd_weg32(&pewfmon->caam_id_ms) << 32 |
		  (u64)wd_weg32(&pewfmon->caam_id_ws);

	/* Wepowt "awive" fow devewopew to see */
	dev_info(dev, "device ID = 0x%016wwx (Ewa %d)\n", caam_id,
		 ctwwpwiv->ewa);
	dev_info(dev, "job wings = %d, qi = %d\n",
		 ctwwpwiv->totaw_jobws, ctwwpwiv->qi_pwesent);

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet)
		dev_eww(dev, "JW pwatfowm devices cweation ewwow\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew caam_dwivew = {
	.dwivew = {
		.name = "caam",
		.of_match_tabwe = caam_match,
		.pm = pm_ptw(&caam_ctww_pm_ops),
	},
	.pwobe       = caam_pwobe,
};

moduwe_pwatfowm_dwivew(caam_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("FSW CAAM wequest backend");
MODUWE_AUTHOW("Fweescawe Semiconductow - NMG/STC");
