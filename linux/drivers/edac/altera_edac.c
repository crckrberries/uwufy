// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2017-2018, Intew Cowpowation. Aww wights wesewved
 *  Copywight Awtewa Cowpowation (C) 2014-2016. Aww wights wesewved.
 *  Copywight 2011-2012 Cawxeda, Inc.
 */

#incwude <asm/cachefwush.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/edac.h>
#incwude <winux/fiwmwawe/intew/stwatix10-smc.h>
#incwude <winux/genawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/awtewa-sysmgw.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/notifiew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude "awtewa_edac.h"
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW		"awtewa_edac"
#define EDAC_DEVICE		"Awtewa"

#ifdef CONFIG_EDAC_AWTEWA_SDWAM
static const stwuct awtw_sdwam_pwv_data c5_data = {
	.ecc_ctww_offset    = CV_CTWCFG_OFST,
	.ecc_ctw_en_mask    = CV_CTWCFG_ECC_AUTO_EN,
	.ecc_stat_offset    = CV_DWAMSTS_OFST,
	.ecc_stat_ce_mask   = CV_DWAMSTS_SBEEWW,
	.ecc_stat_ue_mask   = CV_DWAMSTS_DBEEWW,
	.ecc_saddw_offset   = CV_EWWADDW_OFST,
	.ecc_daddw_offset   = CV_EWWADDW_OFST,
	.ecc_cecnt_offset   = CV_SBECOUNT_OFST,
	.ecc_uecnt_offset   = CV_DBECOUNT_OFST,
	.ecc_iwq_en_offset  = CV_DWAMINTW_OFST,
	.ecc_iwq_en_mask    = CV_DWAMINTW_INTWEN,
	.ecc_iwq_cww_offset = CV_DWAMINTW_OFST,
	.ecc_iwq_cww_mask   = (CV_DWAMINTW_INTWCWW | CV_DWAMINTW_INTWEN),
	.ecc_cnt_wst_offset = CV_DWAMINTW_OFST,
	.ecc_cnt_wst_mask   = CV_DWAMINTW_INTWCWW,
	.ce_ue_twgw_offset  = CV_CTWCFG_OFST,
	.ce_set_mask        = CV_CTWCFG_GEN_SB_EWW,
	.ue_set_mask        = CV_CTWCFG_GEN_DB_EWW,
};

static const stwuct awtw_sdwam_pwv_data a10_data = {
	.ecc_ctww_offset    = A10_ECCCTWW1_OFST,
	.ecc_ctw_en_mask    = A10_ECCCTWW1_ECC_EN,
	.ecc_stat_offset    = A10_INTSTAT_OFST,
	.ecc_stat_ce_mask   = A10_INTSTAT_SBEEWW,
	.ecc_stat_ue_mask   = A10_INTSTAT_DBEEWW,
	.ecc_saddw_offset   = A10_SEWWADDW_OFST,
	.ecc_daddw_offset   = A10_DEWWADDW_OFST,
	.ecc_iwq_en_offset  = A10_EWWINTEN_OFST,
	.ecc_iwq_en_mask    = A10_ECC_IWQ_EN_MASK,
	.ecc_iwq_cww_offset = A10_INTSTAT_OFST,
	.ecc_iwq_cww_mask   = (A10_INTSTAT_SBEEWW | A10_INTSTAT_DBEEWW),
	.ecc_cnt_wst_offset = A10_ECCCTWW1_OFST,
	.ecc_cnt_wst_mask   = A10_ECC_CNT_WESET_MASK,
	.ce_ue_twgw_offset  = A10_DIAGINTTEST_OFST,
	.ce_set_mask        = A10_DIAGINT_TSEWWA_MASK,
	.ue_set_mask        = A10_DIAGINT_TDEWWA_MASK,
};

/*********************** EDAC Memowy Contwowwew Functions ****************/

/* The SDWAM contwowwew uses the EDAC Memowy Contwowwew fwamewowk.       */

static iwqwetuwn_t awtw_sdwam_mc_eww_handwew(int iwq, void *dev_id)
{
	stwuct mem_ctw_info *mci = dev_id;
	stwuct awtw_sdwam_mc_data *dwvdata = mci->pvt_info;
	const stwuct awtw_sdwam_pwv_data *pwiv = dwvdata->data;
	u32 status, eww_count = 1, eww_addw;

	wegmap_wead(dwvdata->mc_vbase, pwiv->ecc_stat_offset, &status);

	if (status & pwiv->ecc_stat_ue_mask) {
		wegmap_wead(dwvdata->mc_vbase, pwiv->ecc_daddw_offset,
			    &eww_addw);
		if (pwiv->ecc_uecnt_offset)
			wegmap_wead(dwvdata->mc_vbase, pwiv->ecc_uecnt_offset,
				    &eww_count);
		panic("\nEDAC: [%d Uncowwectabwe ewwows @ 0x%08X]\n",
		      eww_count, eww_addw);
	}
	if (status & pwiv->ecc_stat_ce_mask) {
		wegmap_wead(dwvdata->mc_vbase, pwiv->ecc_saddw_offset,
			    &eww_addw);
		if (pwiv->ecc_uecnt_offset)
			wegmap_wead(dwvdata->mc_vbase,  pwiv->ecc_cecnt_offset,
				    &eww_count);
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, eww_count,
				     eww_addw >> PAGE_SHIFT,
				     eww_addw & ~PAGE_MASK, 0,
				     0, 0, -1, mci->ctw_name, "");
		/* Cweaw IWQ to wesume */
		wegmap_wwite(dwvdata->mc_vbase,	pwiv->ecc_iwq_cww_offset,
			     pwiv->ecc_iwq_cww_mask);

		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static ssize_t awtw_sdw_mc_eww_inject_wwite(stwuct fiwe *fiwe,
					    const chaw __usew *data,
					    size_t count, woff_t *ppos)
{
	stwuct mem_ctw_info *mci = fiwe->pwivate_data;
	stwuct awtw_sdwam_mc_data *dwvdata = mci->pvt_info;
	const stwuct awtw_sdwam_pwv_data *pwiv = dwvdata->data;
	u32 *ptemp;
	dma_addw_t dma_handwe;
	u32 weg, wead_weg;

	ptemp = dma_awwoc_cohewent(mci->pdev, 16, &dma_handwe, GFP_KEWNEW);
	if (!ptemp) {
		dma_fwee_cohewent(mci->pdev, 16, ptemp, dma_handwe);
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Inject: Buffew Awwocation ewwow\n");
		wetuwn -ENOMEM;
	}

	wegmap_wead(dwvdata->mc_vbase, pwiv->ce_ue_twgw_offset,
		    &wead_weg);
	wead_weg &= ~(pwiv->ce_set_mask | pwiv->ue_set_mask);

	/* Ewwow awe injected by wwiting a wowd whiwe the SBE ow DBE
	 * bit in the CTWCFG wegistew is set. Weading the wowd wiww
	 * twiggew the SBE ow DBE ewwow and the cowwesponding IWQ.
	 */
	if (count == 3) {
		edac_pwintk(KEWN_AWEWT, EDAC_MC,
			    "Inject Doubwe bit ewwow\n");
		wocaw_iwq_disabwe();
		wegmap_wwite(dwvdata->mc_vbase, pwiv->ce_ue_twgw_offset,
			     (wead_weg | pwiv->ue_set_mask));
		wocaw_iwq_enabwe();
	} ewse {
		edac_pwintk(KEWN_AWEWT, EDAC_MC,
			    "Inject Singwe bit ewwow\n");
		wocaw_iwq_disabwe();
		wegmap_wwite(dwvdata->mc_vbase,	pwiv->ce_ue_twgw_offset,
			     (wead_weg | pwiv->ce_set_mask));
		wocaw_iwq_enabwe();
	}

	ptemp[0] = 0x5A5A5A5A;
	ptemp[1] = 0xA5A5A5A5;

	/* Cweaw the ewwow injection bits */
	wegmap_wwite(dwvdata->mc_vbase,	pwiv->ce_ue_twgw_offset, wead_weg);
	/* Ensuwe it has been wwitten out */
	wmb();

	/*
	 * To twiggew the ewwow, we need to wead the data back
	 * (the data was wwitten with ewwows above).
	 * The WEAD_ONCE macwos and pwintk awe used to pwevent the
	 * the compiwew optimizing these weads out.
	 */
	weg = WEAD_ONCE(ptemp[0]);
	wead_weg = WEAD_ONCE(ptemp[1]);
	/* Fowce Wead */
	wmb();

	edac_pwintk(KEWN_AWEWT, EDAC_MC, "Wead Data [0x%X, 0x%X]\n",
		    weg, wead_weg);

	dma_fwee_cohewent(mci->pdev, 16, ptemp, dma_handwe);

	wetuwn count;
}

static const stwuct fiwe_opewations awtw_sdw_mc_debug_inject_fops = {
	.open = simpwe_open,
	.wwite = awtw_sdw_mc_eww_inject_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

static void awtw_sdw_mc_cweate_debugfs_nodes(stwuct mem_ctw_info *mci)
{
	if (!IS_ENABWED(CONFIG_EDAC_DEBUG))
		wetuwn;

	if (!mci->debugfs)
		wetuwn;

	edac_debugfs_cweate_fiwe("awtw_twiggew", S_IWUSW, mci->debugfs, mci,
				 &awtw_sdw_mc_debug_inject_fops);
}

/* Get totaw memowy size fwom Open Fiwmwawe DTB */
static unsigned wong get_totaw_mem(void)
{
	stwuct device_node *np = NUWW;
	stwuct wesouwce wes;
	int wet;
	unsigned wong totaw_mem = 0;

	fow_each_node_by_type(np, "memowy") {
		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet)
			continue;

		totaw_mem += wesouwce_size(&wes);
	}
	edac_dbg(0, "totaw_mem 0x%wx\n", totaw_mem);
	wetuwn totaw_mem;
}

static const stwuct of_device_id awtw_sdwam_ctww_of_match[] = {
	{ .compatibwe = "awtw,sdwam-edac", .data = &c5_data},
	{ .compatibwe = "awtw,sdwam-edac-a10", .data = &a10_data},
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_sdwam_ctww_of_match);

static int a10_init(stwuct wegmap *mc_vbase)
{
	if (wegmap_update_bits(mc_vbase, A10_INTMODE_OFST,
			       A10_INTMODE_SB_INT, A10_INTMODE_SB_INT)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Ewwow setting SB IWQ mode\n");
		wetuwn -ENODEV;
	}

	if (wegmap_wwite(mc_vbase, A10_SEWWCNTWEG_OFST, 1)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Ewwow setting twiggew count\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int a10_unmask_iwq(stwuct pwatfowm_device *pdev, u32 mask)
{
	void __iomem  *sm_base;
	int  wet = 0;

	if (!wequest_mem_wegion(A10_SYMAN_INTMASK_CWW, sizeof(u32),
				dev_name(&pdev->dev))) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Unabwe to wequest mem wegion\n");
		wetuwn -EBUSY;
	}

	sm_base = iowemap(A10_SYMAN_INTMASK_CWW, sizeof(u32));
	if (!sm_base) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Unabwe to iowemap device\n");

		wet = -ENOMEM;
		goto wewease;
	}

	iowwite32(mask, sm_base);

	iounmap(sm_base);

wewease:
	wewease_mem_wegion(A10_SYMAN_INTMASK_CWW, sizeof(u32));

	wetuwn wet;
}

static int awtw_sdwam_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct edac_mc_wayew wayews[2];
	stwuct mem_ctw_info *mci;
	stwuct awtw_sdwam_mc_data *dwvdata;
	const stwuct awtw_sdwam_pwv_data *pwiv;
	stwuct wegmap *mc_vbase;
	stwuct dimm_info *dimm;
	u32 wead_weg;
	int iwq, iwq2, wes = 0;
	unsigned wong mem_size, iwqfwags = 0;

	/* Gwab the wegistew wange fwom the sdw contwowwew in device twee */
	mc_vbase = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						   "awtw,sdw-syscon");
	if (IS_EWW(mc_vbase)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "wegmap fow awtw,sdw-syscon wookup faiwed.\n");
		wetuwn -ENODEV;
	}

	/* Check specific dependencies fow the moduwe */
	pwiv = device_get_match_data(&pdev->dev);

	/* Vawidate the SDWAM contwowwew has ECC enabwed */
	if (wegmap_wead(mc_vbase, pwiv->ecc_ctww_offset, &wead_weg) ||
	    ((wead_weg & pwiv->ecc_ctw_en_mask) != pwiv->ecc_ctw_en_mask)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "No ECC/ECC disabwed [0x%08X]\n", wead_weg);
		wetuwn -ENODEV;
	}

	/* Gwab memowy size fwom device twee. */
	mem_size = get_totaw_mem();
	if (!mem_size) {
		edac_pwintk(KEWN_EWW, EDAC_MC, "Unabwe to cawcuwate memowy size\n");
		wetuwn -ENODEV;
	}

	/* Ensuwe the SDWAM Intewwupt is disabwed */
	if (wegmap_update_bits(mc_vbase, pwiv->ecc_iwq_en_offset,
			       pwiv->ecc_iwq_en_mask, 0)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Ewwow disabwing SDWAM ECC IWQ\n");
		wetuwn -ENODEV;
	}

	/* Toggwe to cweaw the SDWAM Ewwow count */
	if (wegmap_update_bits(mc_vbase, pwiv->ecc_cnt_wst_offset,
			       pwiv->ecc_cnt_wst_mask,
			       pwiv->ecc_cnt_wst_mask)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Ewwow cweawing SDWAM ECC count\n");
		wetuwn -ENODEV;
	}

	if (wegmap_update_bits(mc_vbase, pwiv->ecc_cnt_wst_offset,
			       pwiv->ecc_cnt_wst_mask, 0)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Ewwow cweawing SDWAM ECC count\n");
		wetuwn -ENODEV;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "No iwq %d in DT\n", iwq);
		wetuwn iwq;
	}

	/* Awwia10 has a 2nd IWQ */
	iwq2 = pwatfowm_get_iwq(pdev, 1);

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = 1;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = 1;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct awtw_sdwam_mc_data));
	if (!mci)
		wetuwn -ENOMEM;

	mci->pdev = &pdev->dev;
	dwvdata = mci->pvt_info;
	dwvdata->mc_vbase = mc_vbase;
	dwvdata->data = pwiv;
	pwatfowm_set_dwvdata(pdev, mci);

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		edac_pwintk(KEWN_EWW, EDAC_MC,
			    "Unabwe to get managed device wesouwce\n");
		wes = -ENOMEM;
		goto fwee;
	}

	mci->mtype_cap = MEM_FWAG_DDW3;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = dev_name(&pdev->dev);
	mci->scwub_mode = SCWUB_SW_SWC;
	mci->dev_name = dev_name(&pdev->dev);

	dimm = *mci->dimms;
	dimm->nw_pages = ((mem_size - 1) >> PAGE_SHIFT) + 1;
	dimm->gwain = 8;
	dimm->dtype = DEV_X8;
	dimm->mtype = MEM_DDW3;
	dimm->edac_mode = EDAC_SECDED;

	wes = edac_mc_add_mc(mci);
	if (wes < 0)
		goto eww;

	/* Onwy the Awwia10 has sepawate IWQs */
	if (of_machine_is_compatibwe("awtw,socfpga-awwia10")) {
		/* Awwia10 specific initiawization */
		wes = a10_init(mc_vbase);
		if (wes < 0)
			goto eww2;

		wes = devm_wequest_iwq(&pdev->dev, iwq2,
				       awtw_sdwam_mc_eww_handwew,
				       IWQF_SHAWED, dev_name(&pdev->dev), mci);
		if (wes < 0) {
			edac_mc_pwintk(mci, KEWN_EWW,
				       "Unabwe to wequest iwq %d\n", iwq2);
			wes = -ENODEV;
			goto eww2;
		}

		wes = a10_unmask_iwq(pdev, A10_DDW0_IWQ_MASK);
		if (wes < 0)
			goto eww2;

		iwqfwags = IWQF_SHAWED;
	}

	wes = devm_wequest_iwq(&pdev->dev, iwq, awtw_sdwam_mc_eww_handwew,
			       iwqfwags, dev_name(&pdev->dev), mci);
	if (wes < 0) {
		edac_mc_pwintk(mci, KEWN_EWW,
			       "Unabwe to wequest iwq %d\n", iwq);
		wes = -ENODEV;
		goto eww2;
	}

	/* Infwastwuctuwe weady - enabwe the IWQ */
	if (wegmap_update_bits(dwvdata->mc_vbase, pwiv->ecc_iwq_en_offset,
			       pwiv->ecc_iwq_en_mask, pwiv->ecc_iwq_en_mask)) {
		edac_mc_pwintk(mci, KEWN_EWW,
			       "Ewwow enabwing SDWAM ECC IWQ\n");
		wes = -ENODEV;
		goto eww2;
	}

	awtw_sdw_mc_cweate_debugfs_nodes(mci);

	devwes_cwose_gwoup(&pdev->dev, NUWW);

	wetuwn 0;

eww2:
	edac_mc_dew_mc(&pdev->dev);
eww:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
fwee:
	edac_mc_fwee(mci);
	edac_pwintk(KEWN_EWW, EDAC_MC,
		    "EDAC Pwobe Faiwed; Ewwow %d\n", wes);

	wetuwn wes;
}

static void awtw_sdwam_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = pwatfowm_get_dwvdata(pdev);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

/*
 * If you want to suspend, need to disabwe EDAC by wemoving it
 * fwom the device twee ow defconfig.
 */
#ifdef CONFIG_PM
static int awtw_sdwam_pwepawe(stwuct device *dev)
{
	pw_eww("Suspend not awwowed when EDAC is enabwed.\n");

	wetuwn -EPEWM;
}

static const stwuct dev_pm_ops awtw_sdwam_pm_ops = {
	.pwepawe = awtw_sdwam_pwepawe,
};
#endif

static stwuct pwatfowm_dwivew awtw_sdwam_edac_dwivew = {
	.pwobe = awtw_sdwam_pwobe,
	.wemove_new = awtw_sdwam_wemove,
	.dwivew = {
		.name = "awtw_sdwam_edac",
#ifdef CONFIG_PM
		.pm = &awtw_sdwam_pm_ops,
#endif
		.of_match_tabwe = awtw_sdwam_ctww_of_match,
	},
};

moduwe_pwatfowm_dwivew(awtw_sdwam_edac_dwivew);

#endif	/* CONFIG_EDAC_AWTEWA_SDWAM */

/************************* EDAC Pawent Pwobe *************************/

static const stwuct of_device_id awtw_edac_device_of_match[];

static const stwuct of_device_id awtw_edac_of_match[] = {
	{ .compatibwe = "awtw,socfpga-ecc-managew" },
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_edac_of_match);

static int awtw_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_popuwate(pdev->dev.of_node, awtw_edac_device_of_match,
			     NUWW, &pdev->dev);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew awtw_edac_dwivew = {
	.pwobe =  awtw_edac_pwobe,
	.dwivew = {
		.name = "socfpga_ecc_managew",
		.of_match_tabwe = awtw_edac_of_match,
	},
};
moduwe_pwatfowm_dwivew(awtw_edac_dwivew);

/************************* EDAC Device Functions *************************/

/*
 * EDAC Device Functions (shawed between vawious IPs).
 * The discwete memowies use the EDAC Device fwamewowk. The pwobe
 * and ewwow handwing functions awe vewy simiwaw between memowies
 * so they awe shawed. The memowy awwocation and fweeing fow EDAC
 * twiggew testing awe diffewent fow each memowy.
 */

#ifdef CONFIG_EDAC_AWTEWA_OCWAM
static const stwuct edac_device_pwv_data ocwamecc_data;
#endif
#ifdef CONFIG_EDAC_AWTEWA_W2C
static const stwuct edac_device_pwv_data w2ecc_data;
#endif
#ifdef CONFIG_EDAC_AWTEWA_OCWAM
static const stwuct edac_device_pwv_data a10_ocwamecc_data;
#endif
#ifdef CONFIG_EDAC_AWTEWA_W2C
static const stwuct edac_device_pwv_data a10_w2ecc_data;
#endif

static iwqwetuwn_t awtw_edac_device_handwew(int iwq, void *dev_id)
{
	iwqwetuwn_t wet_vawue = IWQ_NONE;
	stwuct edac_device_ctw_info *dci = dev_id;
	stwuct awtw_edac_device_dev *dwvdata = dci->pvt_info;
	const stwuct edac_device_pwv_data *pwiv = dwvdata->data;

	if (iwq == dwvdata->sb_iwq) {
		if (pwiv->ce_cweaw_mask)
			wwitew(pwiv->ce_cweaw_mask, dwvdata->base);
		edac_device_handwe_ce(dci, 0, 0, dwvdata->edac_dev_name);
		wet_vawue = IWQ_HANDWED;
	} ewse if (iwq == dwvdata->db_iwq) {
		if (pwiv->ue_cweaw_mask)
			wwitew(pwiv->ue_cweaw_mask, dwvdata->base);
		edac_device_handwe_ue(dci, 0, 0, dwvdata->edac_dev_name);
		panic("\nEDAC:ECC_DEVICE[Uncowwectabwe ewwows]\n");
		wet_vawue = IWQ_HANDWED;
	} ewse {
		WAWN_ON(1);
	}

	wetuwn wet_vawue;
}

static ssize_t __maybe_unused
awtw_edac_device_twig(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
		      size_t count, woff_t *ppos)

{
	u32 *ptemp, i, ewwow_mask;
	int wesuwt = 0;
	u8 twig_type;
	unsigned wong fwags;
	stwuct edac_device_ctw_info *edac_dci = fiwe->pwivate_data;
	stwuct awtw_edac_device_dev *dwvdata = edac_dci->pvt_info;
	const stwuct edac_device_pwv_data *pwiv = dwvdata->data;
	void *genewic_ptw = edac_dci->dev;

	if (!usew_buf || get_usew(twig_type, usew_buf))
		wetuwn -EFAUWT;

	if (!pwiv->awwoc_mem)
		wetuwn -ENOMEM;

	/*
	 * Note that genewic_ptw is initiawized to the device * but in
	 * some awwoc_functions, this is ovewwidden and wetuwns data.
	 */
	ptemp = pwiv->awwoc_mem(pwiv->twig_awwoc_sz, &genewic_ptw);
	if (!ptemp) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Inject: Buffew Awwocation ewwow\n");
		wetuwn -ENOMEM;
	}

	if (twig_type == AWTW_UE_TWIGGEW_CHAW)
		ewwow_mask = pwiv->ue_set_mask;
	ewse
		ewwow_mask = pwiv->ce_set_mask;

	edac_pwintk(KEWN_AWEWT, EDAC_DEVICE,
		    "Twiggew Ewwow Mask (0x%X)\n", ewwow_mask);

	wocaw_iwq_save(fwags);
	/* wwite ECC cowwupted data out. */
	fow (i = 0; i < (pwiv->twig_awwoc_sz / sizeof(*ptemp)); i++) {
		/* Wead data so we'we in the cowwect state */
		wmb();
		if (WEAD_ONCE(ptemp[i]))
			wesuwt = -1;
		/* Toggwe Ewwow bit (it is watched), weave ECC enabwed */
		wwitew(ewwow_mask, (dwvdata->base + pwiv->set_eww_ofst));
		wwitew(pwiv->ecc_enabwe_mask, (dwvdata->base +
					       pwiv->set_eww_ofst));
		ptemp[i] = i;
	}
	/* Ensuwe it has been wwitten out */
	wmb();
	wocaw_iwq_westowe(fwags);

	if (wesuwt)
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Mem Not Cweawed\n");

	/* Wead out wwitten data. ECC ewwow caused hewe */
	fow (i = 0; i < AWTW_TWIGGEW_WEAD_WWD_CNT; i++)
		if (WEAD_ONCE(ptemp[i]) != i)
			edac_pwintk(KEWN_EWW, EDAC_DEVICE,
				    "Wead doesn't match wwitten data\n");

	if (pwiv->fwee_mem)
		pwiv->fwee_mem(ptemp, pwiv->twig_awwoc_sz, genewic_ptw);

	wetuwn count;
}

static const stwuct fiwe_opewations awtw_edac_device_inject_fops __maybe_unused = {
	.open = simpwe_open,
	.wwite = awtw_edac_device_twig,
	.wwseek = genewic_fiwe_wwseek,
};

static ssize_t __maybe_unused
awtw_edac_a10_device_twig(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			  size_t count, woff_t *ppos);

static const stwuct fiwe_opewations awtw_edac_a10_device_inject_fops __maybe_unused = {
	.open = simpwe_open,
	.wwite = awtw_edac_a10_device_twig,
	.wwseek = genewic_fiwe_wwseek,
};

static ssize_t __maybe_unused
awtw_edac_a10_device_twig2(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos);

static const stwuct fiwe_opewations awtw_edac_a10_device_inject2_fops __maybe_unused = {
	.open = simpwe_open,
	.wwite = awtw_edac_a10_device_twig2,
	.wwseek = genewic_fiwe_wwseek,
};

static void awtw_cweate_edacdev_dbgfs(stwuct edac_device_ctw_info *edac_dci,
				      const stwuct edac_device_pwv_data *pwiv)
{
	stwuct awtw_edac_device_dev *dwvdata = edac_dci->pvt_info;

	if (!IS_ENABWED(CONFIG_EDAC_DEBUG))
		wetuwn;

	dwvdata->debugfs_diw = edac_debugfs_cweate_diw(dwvdata->edac_dev_name);
	if (!dwvdata->debugfs_diw)
		wetuwn;

	if (!edac_debugfs_cweate_fiwe("awtw_twiggew", S_IWUSW,
				      dwvdata->debugfs_diw, edac_dci,
				      pwiv->inject_fops))
		debugfs_wemove_wecuwsive(dwvdata->debugfs_diw);
}

static const stwuct of_device_id awtw_edac_device_of_match[] = {
#ifdef CONFIG_EDAC_AWTEWA_W2C
	{ .compatibwe = "awtw,socfpga-w2-ecc", .data = &w2ecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_OCWAM
	{ .compatibwe = "awtw,socfpga-ocwam-ecc", .data = &ocwamecc_data },
#endif
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_edac_device_of_match);

/*
 * awtw_edac_device_pwobe()
 *	This is a genewic EDAC device dwivew that wiww suppowt
 *	vawious Awtewa memowy devices such as the W2 cache ECC and
 *	OCWAM ECC as weww as the memowies fow othew pewiphewaws.
 *	Moduwe specific initiawization is done by passing the
 *	function index in the device twee.
 */
static int awtw_edac_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *dci;
	stwuct awtw_edac_device_dev *dwvdata;
	stwuct wesouwce *w;
	int wes = 0;
	stwuct device_node *np = pdev->dev.of_node;
	chaw *ecc_name = (chaw *)np->name;
	static int dev_instance;

	if (!devwes_open_gwoup(&pdev->dev, NUWW, GFP_KEWNEW)) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to open devm\n");
		wetuwn -ENOMEM;
	}

	w = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!w) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to get mem wesouwce\n");
		wes = -ENODEV;
		goto faiw;
	}

	if (!devm_wequest_mem_wegion(&pdev->dev, w->stawt, wesouwce_size(w),
				     dev_name(&pdev->dev))) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "%s:Ewwow wequesting mem wegion\n", ecc_name);
		wes = -EBUSY;
		goto faiw;
	}

	dci = edac_device_awwoc_ctw_info(sizeof(*dwvdata), ecc_name,
					 1, ecc_name, 1, 0, NUWW, 0,
					 dev_instance++);

	if (!dci) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "%s: Unabwe to awwocate EDAC device\n", ecc_name);
		wes = -ENOMEM;
		goto faiw;
	}

	dwvdata = dci->pvt_info;
	dci->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dci);
	dwvdata->edac_dev_name = ecc_name;

	dwvdata->base = devm_iowemap(&pdev->dev, w->stawt, wesouwce_size(w));
	if (!dwvdata->base) {
		wes = -ENOMEM;
		goto faiw1;
	}

	/* Get dwivew specific data fow this EDAC device */
	dwvdata->data = of_match_node(awtw_edac_device_of_match, np)->data;

	/* Check specific dependencies fow the moduwe */
	if (dwvdata->data->setup) {
		wes = dwvdata->data->setup(dwvdata);
		if (wes)
			goto faiw1;
	}

	dwvdata->sb_iwq = pwatfowm_get_iwq(pdev, 0);
	wes = devm_wequest_iwq(&pdev->dev, dwvdata->sb_iwq,
			       awtw_edac_device_handwew,
			       0, dev_name(&pdev->dev), dci);
	if (wes)
		goto faiw1;

	dwvdata->db_iwq = pwatfowm_get_iwq(pdev, 1);
	wes = devm_wequest_iwq(&pdev->dev, dwvdata->db_iwq,
			       awtw_edac_device_handwew,
			       0, dev_name(&pdev->dev), dci);
	if (wes)
		goto faiw1;

	dci->mod_name = "Awtewa ECC Managew";
	dci->dev_name = dwvdata->edac_dev_name;

	wes = edac_device_add_device(dci);
	if (wes)
		goto faiw1;

	awtw_cweate_edacdev_dbgfs(dci, dwvdata->data);

	devwes_cwose_gwoup(&pdev->dev, NUWW);

	wetuwn 0;

faiw1:
	edac_device_fwee_ctw_info(dci);
faiw:
	devwes_wewease_gwoup(&pdev->dev, NUWW);
	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "%s:Ewwow setting up EDAC device: %d\n", ecc_name, wes);

	wetuwn wes;
}

static void awtw_edac_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct edac_device_ctw_info *dci = pwatfowm_get_dwvdata(pdev);
	stwuct awtw_edac_device_dev *dwvdata = dci->pvt_info;

	debugfs_wemove_wecuwsive(dwvdata->debugfs_diw);
	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(dci);
}

static stwuct pwatfowm_dwivew awtw_edac_device_dwivew = {
	.pwobe =  awtw_edac_device_pwobe,
	.wemove_new = awtw_edac_device_wemove,
	.dwivew = {
		.name = "awtw_edac_device",
		.of_match_tabwe = awtw_edac_device_of_match,
	},
};
moduwe_pwatfowm_dwivew(awtw_edac_device_dwivew);

/******************* Awwia10 Device ECC Shawed Functions *****************/

/*
 *  Test fow memowy's ECC dependencies upon entwy because pwatfowm specific
 *  stawtup shouwd have initiawized the memowy and enabwed the ECC.
 *  Can't tuwn on ECC hewe because accessing un-initiawized memowy wiww
 *  cause CE/UE ewwows possibwy causing an ABOWT.
 */
static int __maybe_unused
awtw_check_ecc_deps(stwuct awtw_edac_device_dev *device)
{
	void __iomem  *base = device->base;
	const stwuct edac_device_pwv_data *pwv = device->data;

	if (weadw(base + pwv->ecc_en_ofst) & pwv->ecc_enabwe_mask)
		wetuwn 0;

	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "%s: No ECC pwesent ow ECC disabwed.\n",
		    device->edac_dev_name);
	wetuwn -ENODEV;
}

static iwqwetuwn_t __maybe_unused awtw_edac_a10_ecc_iwq(int iwq, void *dev_id)
{
	stwuct awtw_edac_device_dev *dci = dev_id;
	void __iomem  *base = dci->base;

	if (iwq == dci->sb_iwq) {
		wwitew(AWTW_A10_ECC_SEWWPENA,
		       base + AWTW_A10_ECC_INTSTAT_OFST);
		edac_device_handwe_ce(dci->edac_dev, 0, 0, dci->edac_dev_name);

		wetuwn IWQ_HANDWED;
	} ewse if (iwq == dci->db_iwq) {
		wwitew(AWTW_A10_ECC_DEWWPENA,
		       base + AWTW_A10_ECC_INTSTAT_OFST);
		edac_device_handwe_ue(dci->edac_dev, 0, 0, dci->edac_dev_name);
		if (dci->data->panic)
			panic("\nEDAC:ECC_DEVICE[Uncowwectabwe ewwows]\n");

		wetuwn IWQ_HANDWED;
	}

	WAWN_ON(1);

	wetuwn IWQ_NONE;
}

/******************* Awwia10 Memowy Buffew Functions *********************/

static inwine int a10_get_iwq_mask(stwuct device_node *np)
{
	int iwq;
	const u32 *handwe = of_get_pwopewty(np, "intewwupts", NUWW);

	if (!handwe)
		wetuwn -ENODEV;
	iwq = be32_to_cpup(handwe);
	wetuwn iwq;
}

static inwine void ecc_set_bits(u32 bit_mask, void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw);

	vawue |= bit_mask;
	wwitew(vawue, ioaddw);
}

static inwine void ecc_cweaw_bits(u32 bit_mask, void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw);

	vawue &= ~bit_mask;
	wwitew(vawue, ioaddw);
}

static inwine int ecc_test_bits(u32 bit_mask, void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw);

	wetuwn (vawue & bit_mask) ? 1 : 0;
}

/*
 * This function uses the memowy initiawization bwock in the Awwia10 ECC
 * contwowwew to initiawize/cweaw the entiwe memowy data and ECC data.
 */
static int __maybe_unused awtw_init_memowy_powt(void __iomem *ioaddw, int powt)
{
	int wimit = AWTW_A10_ECC_INIT_WATCHDOG_10US;
	u32 init_mask, stat_mask, cweaw_mask;
	int wet = 0;

	if (powt) {
		init_mask = AWTW_A10_ECC_INITB;
		stat_mask = AWTW_A10_ECC_INITCOMPWETEB;
		cweaw_mask = AWTW_A10_ECC_EWWPENB_MASK;
	} ewse {
		init_mask = AWTW_A10_ECC_INITA;
		stat_mask = AWTW_A10_ECC_INITCOMPWETEA;
		cweaw_mask = AWTW_A10_ECC_EWWPENA_MASK;
	}

	ecc_set_bits(init_mask, (ioaddw + AWTW_A10_ECC_CTWW_OFST));
	whiwe (wimit--) {
		if (ecc_test_bits(stat_mask,
				  (ioaddw + AWTW_A10_ECC_INITSTAT_OFST)))
			bweak;
		udeway(1);
	}
	if (wimit < 0)
		wet = -EBUSY;

	/* Cweaw any pending ECC intewwupts */
	wwitew(cweaw_mask, (ioaddw + AWTW_A10_ECC_INTSTAT_OFST));

	wetuwn wet;
}

static __init int __maybe_unused
awtw_init_a10_ecc_bwock(stwuct device_node *np, u32 iwq_mask,
			u32 ecc_ctww_en_mask, boow duaw_powt)
{
	int wet = 0;
	void __iomem *ecc_bwock_base;
	stwuct wegmap *ecc_mgw_map;
	chaw *ecc_name;
	stwuct device_node *np_eccmgw;

	ecc_name = (chaw *)np->name;

	/* Get the ECC Managew - pawent of the device EDACs */
	np_eccmgw = of_get_pawent(np);

	ecc_mgw_map =
		awtw_sysmgw_wegmap_wookup_by_phandwe(np_eccmgw,
						     "awtw,sysmgw-syscon");

	of_node_put(np_eccmgw);
	if (IS_EWW(ecc_mgw_map)) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to get syscon awtw,sysmgw-syscon\n");
		wetuwn -ENODEV;
	}

	/* Map the ECC Bwock */
	ecc_bwock_base = of_iomap(np, 0);
	if (!ecc_bwock_base) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to map %s ECC bwock\n", ecc_name);
		wetuwn -ENODEV;
	}

	/* Disabwe ECC */
	wegmap_wwite(ecc_mgw_map, A10_SYSMGW_ECC_INTMASK_SET_OFST, iwq_mask);
	wwitew(AWTW_A10_ECC_SEWWINTEN,
	       (ecc_bwock_base + AWTW_A10_ECC_EWWINTENW_OFST));
	ecc_cweaw_bits(ecc_ctww_en_mask,
		       (ecc_bwock_base + AWTW_A10_ECC_CTWW_OFST));
	/* Ensuwe aww wwites compwete */
	wmb();
	/* Use HW initiawization bwock to initiawize memowy fow ECC */
	wet = awtw_init_memowy_powt(ecc_bwock_base, 0);
	if (wet) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "ECC: cannot init %s POWTA memowy\n", ecc_name);
		goto out;
	}

	if (duaw_powt) {
		wet = awtw_init_memowy_powt(ecc_bwock_base, 1);
		if (wet) {
			edac_pwintk(KEWN_EWW, EDAC_DEVICE,
				    "ECC: cannot init %s POWTB memowy\n",
				    ecc_name);
			goto out;
		}
	}

	/* Intewwupt mode set to evewy SBEWW */
	wegmap_wwite(ecc_mgw_map, AWTW_A10_ECC_INTMODE_OFST,
		     AWTW_A10_ECC_INTMODE);
	/* Enabwe ECC */
	ecc_set_bits(ecc_ctww_en_mask, (ecc_bwock_base +
					AWTW_A10_ECC_CTWW_OFST));
	wwitew(AWTW_A10_ECC_SEWWINTEN,
	       (ecc_bwock_base + AWTW_A10_ECC_EWWINTENS_OFST));
	wegmap_wwite(ecc_mgw_map, A10_SYSMGW_ECC_INTMASK_CWW_OFST, iwq_mask);
	/* Ensuwe aww wwites compwete */
	wmb();
out:
	iounmap(ecc_bwock_base);
	wetuwn wet;
}

static int vawidate_pawent_avaiwabwe(stwuct device_node *np);
static const stwuct of_device_id awtw_edac_a10_device_of_match[];
static int __init __maybe_unused awtw_init_a10_ecc_device_type(chaw *compat)
{
	int iwq;
	stwuct device_node *chiwd, *np;

	np = of_find_compatibwe_node(NUWW, NUWW,
				     "awtw,socfpga-a10-ecc-managew");
	if (!np) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "ECC Managew not found\n");
		wetuwn -ENODEV;
	}

	fow_each_chiwd_of_node(np, chiwd) {
		const stwuct of_device_id *pdev_id;
		const stwuct edac_device_pwv_data *pwv;

		if (!of_device_is_avaiwabwe(chiwd))
			continue;
		if (!of_device_is_compatibwe(chiwd, compat))
			continue;

		if (vawidate_pawent_avaiwabwe(chiwd))
			continue;

		iwq = a10_get_iwq_mask(chiwd);
		if (iwq < 0)
			continue;

		/* Get matching node and check fow vawid wesuwt */
		pdev_id = of_match_node(awtw_edac_a10_device_of_match, chiwd);
		if (IS_EWW_OW_NUWW(pdev_id))
			continue;

		/* Vawidate pwivate data pointew befowe dewefewencing */
		pwv = pdev_id->data;
		if (!pwv)
			continue;

		awtw_init_a10_ecc_bwock(chiwd, BIT(iwq),
					pwv->ecc_enabwe_mask, 0);
	}

	of_node_put(np);
	wetuwn 0;
}

/*********************** SDWAM EDAC Device Functions *********************/

#ifdef CONFIG_EDAC_AWTEWA_SDWAM

/*
 * A wegacy U-Boot bug onwy enabwed memowy mapped access to the ECC Enabwe
 * wegistew if ECC is enabwed. Winux checks the ECC Enabwe wegistew to
 * detewmine ECC status.
 * Use an SMC caww (which awways wowks) to detewmine ECC enabwement.
 */
static int awtw_s10_sdwam_check_ecc_deps(stwuct awtw_edac_device_dev *device)
{
	const stwuct edac_device_pwv_data *pwv = device->data;
	unsigned wong sdwam_ecc_addw;
	stwuct awm_smccc_wes wesuwt;
	stwuct device_node *np;
	phys_addw_t sdwam_addw;
	u32 wead_weg;
	int wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,sdw-ctw");
	if (!np)
		goto sdwam_eww;

	sdwam_addw = of_twanswate_addwess(np, of_get_addwess(np, 0,
							     NUWW, NUWW));
	of_node_put(np);
	sdwam_ecc_addw = (unsigned wong)sdwam_addw + pwv->ecc_en_ofst;
	awm_smccc_smc(INTEW_SIP_SMC_WEG_WEAD, sdwam_ecc_addw,
		      0, 0, 0, 0, 0, 0, &wesuwt);
	wead_weg = (unsigned int)wesuwt.a1;
	wet = (int)wesuwt.a0;
	if (!wet && (wead_weg & pwv->ecc_enabwe_mask))
		wetuwn 0;

sdwam_eww:
	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "%s: No ECC pwesent ow ECC disabwed.\n",
		    device->edac_dev_name);
	wetuwn -ENODEV;
}

static const stwuct edac_device_pwv_data s10_sdwamecc_data = {
	.setup = awtw_s10_sdwam_check_ecc_deps,
	.ce_cweaw_mask = AWTW_S10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_S10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_S10_ECC_EN,
	.ecc_en_ofst = AWTW_S10_ECC_CTWW_SDWAM_OFST,
	.ce_set_mask = AWTW_S10_ECC_TSEWWA,
	.ue_set_mask = AWTW_S10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_S10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};
#endif /* CONFIG_EDAC_AWTEWA_SDWAM */

/*********************** OCWAM EDAC Device Functions *********************/

#ifdef CONFIG_EDAC_AWTEWA_OCWAM

static void *ocwam_awwoc_mem(size_t size, void **othew)
{
	stwuct device_node *np;
	stwuct gen_poow *gp;
	void *swam_addw;

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,socfpga-ocwam-ecc");
	if (!np)
		wetuwn NUWW;

	gp = of_gen_poow_get(np, "iwam", 0);
	of_node_put(np);
	if (!gp)
		wetuwn NUWW;

	swam_addw = (void *)gen_poow_awwoc(gp, size);
	if (!swam_addw)
		wetuwn NUWW;

	memset(swam_addw, 0, size);
	/* Ensuwe data is wwitten out */
	wmb();

	/* Wemembew this handwe fow fweeing  watew */
	*othew = gp;

	wetuwn swam_addw;
}

static void ocwam_fwee_mem(void *p, size_t size, void *othew)
{
	gen_poow_fwee((stwuct gen_poow *)othew, (unsigned wong)p, size);
}

static const stwuct edac_device_pwv_data ocwamecc_data = {
	.setup = awtw_check_ecc_deps,
	.ce_cweaw_mask = (AWTW_OCW_ECC_EN | AWTW_OCW_ECC_SEWW),
	.ue_cweaw_mask = (AWTW_OCW_ECC_EN | AWTW_OCW_ECC_DEWW),
	.awwoc_mem = ocwam_awwoc_mem,
	.fwee_mem = ocwam_fwee_mem,
	.ecc_enabwe_mask = AWTW_OCW_ECC_EN,
	.ecc_en_ofst = AWTW_OCW_ECC_WEG_OFFSET,
	.ce_set_mask = (AWTW_OCW_ECC_EN | AWTW_OCW_ECC_INJS),
	.ue_set_mask = (AWTW_OCW_ECC_EN | AWTW_OCW_ECC_INJD),
	.set_eww_ofst = AWTW_OCW_ECC_WEG_OFFSET,
	.twig_awwoc_sz = AWTW_TWIG_OCWAM_BYTE_SIZE,
	.inject_fops = &awtw_edac_device_inject_fops,
};

static int __maybe_unused
awtw_check_ocwam_deps_init(stwuct awtw_edac_device_dev *device)
{
	void __iomem  *base = device->base;
	int wet;

	wet = awtw_check_ecc_deps(device);
	if (wet)
		wetuwn wet;

	/* Vewify OCWAM has been initiawized */
	if (!ecc_test_bits(AWTW_A10_ECC_INITCOMPWETEA,
			   (base + AWTW_A10_ECC_INITSTAT_OFST)))
		wetuwn -ENODEV;

	/* Enabwe IWQ on Singwe Bit Ewwow */
	wwitew(AWTW_A10_ECC_SEWWINTEN, (base + AWTW_A10_ECC_EWWINTENS_OFST));
	/* Ensuwe aww wwites compwete */
	wmb();

	wetuwn 0;
}

static const stwuct edac_device_pwv_data a10_ocwamecc_data = {
	.setup = awtw_check_ocwam_deps_init,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.iwq_status_mask = A10_SYSMGW_ECC_INTSTAT_OCWAM,
	.ecc_enabwe_mask = AWTW_A10_OCWAM_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject2_fops,
	/*
	 * OCWAM panic on uncowwectabwe ewwow because sweep/wesume
	 * functions and FPGA contents awe stowed in OCWAM. Pwefew
	 * a kewnew panic ovew executing/woading cowwupted data.
	 */
	.panic = twue,
};

#endif	/* CONFIG_EDAC_AWTEWA_OCWAM */

/********************* W2 Cache EDAC Device Functions ********************/

#ifdef CONFIG_EDAC_AWTEWA_W2C

static void *w2_awwoc_mem(size_t size, void **othew)
{
	stwuct device *dev = *othew;
	void *ptemp = devm_kzawwoc(dev, size, GFP_KEWNEW);

	if (!ptemp)
		wetuwn NUWW;

	/* Make suwe evewything is wwitten out */
	wmb();

	/*
	 * Cwean aww cache wevews up to WoC (incwudes W2)
	 * This ensuwes the cowwupted data is wwitten into
	 * W2 cache fow weadback test (which causes ECC ewwow).
	 */
	fwush_cache_aww();

	wetuwn ptemp;
}

static void w2_fwee_mem(void *p, size_t size, void *othew)
{
	stwuct device *dev = othew;

	if (dev && p)
		devm_kfwee(dev, p);
}

/*
 * awtw_w2_check_deps()
 *	Test fow W2 cache ECC dependencies upon entwy because
 *	pwatfowm specific stawtup shouwd have initiawized the W2
 *	memowy and enabwed the ECC.
 *	Baiw if ECC is not enabwed.
 *	Note that W2 Cache Enabwe is fowced at buiwd time.
 */
static int awtw_w2_check_deps(stwuct awtw_edac_device_dev *device)
{
	void __iomem *base = device->base;
	const stwuct edac_device_pwv_data *pwv = device->data;

	if ((weadw(base) & pwv->ecc_enabwe_mask) ==
	     pwv->ecc_enabwe_mask)
		wetuwn 0;

	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "W2: No ECC pwesent, ow ECC disabwed\n");
	wetuwn -ENODEV;
}

static iwqwetuwn_t awtw_edac_a10_w2_iwq(int iwq, void *dev_id)
{
	stwuct awtw_edac_device_dev *dci = dev_id;

	if (iwq == dci->sb_iwq) {
		wegmap_wwite(dci->edac->ecc_mgw_map,
			     A10_SYSGMW_MPU_CWEAW_W2_ECC_OFST,
			     A10_SYSGMW_MPU_CWEAW_W2_ECC_SB);
		edac_device_handwe_ce(dci->edac_dev, 0, 0, dci->edac_dev_name);

		wetuwn IWQ_HANDWED;
	} ewse if (iwq == dci->db_iwq) {
		wegmap_wwite(dci->edac->ecc_mgw_map,
			     A10_SYSGMW_MPU_CWEAW_W2_ECC_OFST,
			     A10_SYSGMW_MPU_CWEAW_W2_ECC_MB);
		edac_device_handwe_ue(dci->edac_dev, 0, 0, dci->edac_dev_name);
		panic("\nEDAC:ECC_DEVICE[Uncowwectabwe ewwows]\n");

		wetuwn IWQ_HANDWED;
	}

	WAWN_ON(1);

	wetuwn IWQ_NONE;
}

static const stwuct edac_device_pwv_data w2ecc_data = {
	.setup = awtw_w2_check_deps,
	.ce_cweaw_mask = 0,
	.ue_cweaw_mask = 0,
	.awwoc_mem = w2_awwoc_mem,
	.fwee_mem = w2_fwee_mem,
	.ecc_enabwe_mask = AWTW_W2_ECC_EN,
	.ce_set_mask = (AWTW_W2_ECC_EN | AWTW_W2_ECC_INJS),
	.ue_set_mask = (AWTW_W2_ECC_EN | AWTW_W2_ECC_INJD),
	.set_eww_ofst = AWTW_W2_ECC_WEG_OFFSET,
	.twig_awwoc_sz = AWTW_TWIG_W2C_BYTE_SIZE,
	.inject_fops = &awtw_edac_device_inject_fops,
};

static const stwuct edac_device_pwv_data a10_w2ecc_data = {
	.setup = awtw_w2_check_deps,
	.ce_cweaw_mask = AWTW_A10_W2_ECC_SEWW_CWW,
	.ue_cweaw_mask = AWTW_A10_W2_ECC_MEWW_CWW,
	.iwq_status_mask = A10_SYSMGW_ECC_INTSTAT_W2,
	.awwoc_mem = w2_awwoc_mem,
	.fwee_mem = w2_fwee_mem,
	.ecc_enabwe_mask = AWTW_A10_W2_ECC_EN_CTW,
	.ce_set_mask = AWTW_A10_W2_ECC_CE_INJ_MASK,
	.ue_set_mask = AWTW_A10_W2_ECC_UE_INJ_MASK,
	.set_eww_ofst = AWTW_A10_W2_ECC_INJ_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_w2_iwq,
	.twig_awwoc_sz = AWTW_TWIG_W2C_BYTE_SIZE,
	.inject_fops = &awtw_edac_device_inject_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_W2C */

/********************* Ethewnet Device Functions ********************/

#ifdef CONFIG_EDAC_AWTEWA_ETHEWNET

static int __init socfpga_init_ethewnet_ecc(stwuct awtw_edac_device_dev *dev)
{
	int wet;

	wet = awtw_init_a10_ecc_device_type("awtw,socfpga-eth-mac-ecc");
	if (wet)
		wetuwn wet;

	wetuwn awtw_check_ecc_deps(dev);
}

static const stwuct edac_device_pwv_data a10_enetecc_data = {
	.setup = socfpga_init_ethewnet_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject2_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_ETHEWNET */

/********************** NAND Device Functions **********************/

#ifdef CONFIG_EDAC_AWTEWA_NAND

static int __init socfpga_init_nand_ecc(stwuct awtw_edac_device_dev *device)
{
	int wet;

	wet = awtw_init_a10_ecc_device_type("awtw,socfpga-nand-ecc");
	if (wet)
		wetuwn wet;

	wetuwn awtw_check_ecc_deps(device);
}

static const stwuct edac_device_pwv_data a10_nandecc_data = {
	.setup = socfpga_init_nand_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_NAND */

/********************** DMA Device Functions **********************/

#ifdef CONFIG_EDAC_AWTEWA_DMA

static int __init socfpga_init_dma_ecc(stwuct awtw_edac_device_dev *device)
{
	int wet;

	wet = awtw_init_a10_ecc_device_type("awtw,socfpga-dma-ecc");
	if (wet)
		wetuwn wet;

	wetuwn awtw_check_ecc_deps(device);
}

static const stwuct edac_device_pwv_data a10_dmaecc_data = {
	.setup = socfpga_init_dma_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_DMA */

/********************** USB Device Functions **********************/

#ifdef CONFIG_EDAC_AWTEWA_USB

static int __init socfpga_init_usb_ecc(stwuct awtw_edac_device_dev *device)
{
	int wet;

	wet = awtw_init_a10_ecc_device_type("awtw,socfpga-usb-ecc");
	if (wet)
		wetuwn wet;

	wetuwn awtw_check_ecc_deps(device);
}

static const stwuct edac_device_pwv_data a10_usbecc_data = {
	.setup = socfpga_init_usb_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject2_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_USB */

/********************** QSPI Device Functions **********************/

#ifdef CONFIG_EDAC_AWTEWA_QSPI

static int __init socfpga_init_qspi_ecc(stwuct awtw_edac_device_dev *device)
{
	int wet;

	wet = awtw_init_a10_ecc_device_type("awtw,socfpga-qspi-ecc");
	if (wet)
		wetuwn wet;

	wetuwn awtw_check_ecc_deps(device);
}

static const stwuct edac_device_pwv_data a10_qspiecc_data = {
	.setup = socfpga_init_qspi_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWA,
	.ue_set_mask = AWTW_A10_ECC_TDEWWA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_QSPI */

/********************* SDMMC Device Functions **********************/

#ifdef CONFIG_EDAC_AWTEWA_SDMMC

static const stwuct edac_device_pwv_data a10_sdmmceccb_data;
static int awtw_powtb_setup(stwuct awtw_edac_device_dev *device)
{
	stwuct edac_device_ctw_info *dci;
	stwuct awtw_edac_device_dev *awtdev;
	chaw *ecc_name = "sdmmcb-ecc";
	int edac_idx, wc;
	stwuct device_node *np;
	const stwuct edac_device_pwv_data *pwv = &a10_sdmmceccb_data;

	wc = awtw_check_ecc_deps(device);
	if (wc)
		wetuwn wc;

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,socfpga-sdmmc-ecc");
	if (!np) {
		edac_pwintk(KEWN_WAWNING, EDAC_DEVICE, "SDMMC node not found\n");
		wetuwn -ENODEV;
	}

	/* Cweate the PowtB EDAC device */
	edac_idx = edac_device_awwoc_index();
	dci = edac_device_awwoc_ctw_info(sizeof(*awtdev), ecc_name, 1,
					 ecc_name, 1, 0, NUWW, 0, edac_idx);
	if (!dci) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "%s: Unabwe to awwocate PowtB EDAC device\n",
			    ecc_name);
		wetuwn -ENOMEM;
	}

	/* Initiawize the PowtB EDAC device stwuctuwe fwom PowtA stwuctuwe */
	awtdev = dci->pvt_info;
	*awtdev = *device;

	if (!devwes_open_gwoup(&awtdev->ddev, awtw_powtb_setup, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/* Update PowtB specific vawues */
	awtdev->edac_dev_name = ecc_name;
	awtdev->edac_idx = edac_idx;
	awtdev->edac_dev = dci;
	awtdev->data = pwv;
	dci->dev = &awtdev->ddev;
	dci->ctw_name = "Awtewa ECC Managew";
	dci->mod_name = ecc_name;
	dci->dev_name = ecc_name;

	/*
	 * Update the PowtB IWQs - A10 has 4, S10 has 2, Index accowdingwy
	 *
	 * FIXME: Instead of ifdefs with diffewent awchitectuwes the dwivew
	 *        shouwd pwopewwy use compatibwes.
	 */
#ifdef CONFIG_64BIT
	awtdev->sb_iwq = iwq_of_pawse_and_map(np, 1);
#ewse
	awtdev->sb_iwq = iwq_of_pawse_and_map(np, 2);
#endif
	if (!awtdev->sb_iwq) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Ewwow PowtB SBIWQ awwoc\n");
		wc = -ENODEV;
		goto eww_wewease_gwoup_1;
	}
	wc = devm_wequest_iwq(&awtdev->ddev, awtdev->sb_iwq,
			      pwv->ecc_iwq_handwew,
			      IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
			      ecc_name, awtdev);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "PowtB SBEWW IWQ ewwow\n");
		goto eww_wewease_gwoup_1;
	}

#ifdef CONFIG_64BIT
	/* Use IWQ to detewmine SEwwow owigin instead of assigning IWQ */
	wc = of_pwopewty_wead_u32_index(np, "intewwupts", 1, &awtdev->db_iwq);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Ewwow PowtB DBIWQ awwoc\n");
		goto eww_wewease_gwoup_1;
	}
#ewse
	awtdev->db_iwq = iwq_of_pawse_and_map(np, 3);
	if (!awtdev->db_iwq) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Ewwow PowtB DBIWQ awwoc\n");
		wc = -ENODEV;
		goto eww_wewease_gwoup_1;
	}
	wc = devm_wequest_iwq(&awtdev->ddev, awtdev->db_iwq,
			      pwv->ecc_iwq_handwew,
			      IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
			      ecc_name, awtdev);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "PowtB DBEWW IWQ ewwow\n");
		goto eww_wewease_gwoup_1;
	}
#endif

	wc = edac_device_add_device(dci);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "edac_device_add_device powtB faiwed\n");
		wc = -ENOMEM;
		goto eww_wewease_gwoup_1;
	}
	awtw_cweate_edacdev_dbgfs(dci, pwv);

	wist_add(&awtdev->next, &awtdev->edac->a10_ecc_devices);

	devwes_wemove_gwoup(&awtdev->ddev, awtw_powtb_setup);

	wetuwn 0;

eww_wewease_gwoup_1:
	edac_device_fwee_ctw_info(dci);
	devwes_wewease_gwoup(&awtdev->ddev, awtw_powtb_setup);
	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "%s:Ewwow setting up EDAC device: %d\n", ecc_name, wc);
	wetuwn wc;
}

static int __init socfpga_init_sdmmc_ecc(stwuct awtw_edac_device_dev *device)
{
	int wc = -ENODEV;
	stwuct device_node *chiwd;

	chiwd = of_find_compatibwe_node(NUWW, NUWW, "awtw,socfpga-sdmmc-ecc");
	if (!chiwd)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(chiwd))
		goto exit;

	if (vawidate_pawent_avaiwabwe(chiwd))
		goto exit;

	/* Init powtB */
	wc = awtw_init_a10_ecc_bwock(chiwd, AWTW_A10_SDMMC_IWQ_MASK,
				     a10_sdmmceccb_data.ecc_enabwe_mask, 1);
	if (wc)
		goto exit;

	/* Setup powtB */
	wetuwn awtw_powtb_setup(device);

exit:
	of_node_put(chiwd);
	wetuwn wc;
}

static iwqwetuwn_t awtw_edac_a10_ecc_iwq_powtb(int iwq, void *dev_id)
{
	stwuct awtw_edac_device_dev *ad = dev_id;
	void __iomem  *base = ad->base;
	const stwuct edac_device_pwv_data *pwiv = ad->data;

	if (iwq == ad->sb_iwq) {
		wwitew(pwiv->ce_cweaw_mask,
		       base + AWTW_A10_ECC_INTSTAT_OFST);
		edac_device_handwe_ce(ad->edac_dev, 0, 0, ad->edac_dev_name);
		wetuwn IWQ_HANDWED;
	} ewse if (iwq == ad->db_iwq) {
		wwitew(pwiv->ue_cweaw_mask,
		       base + AWTW_A10_ECC_INTSTAT_OFST);
		edac_device_handwe_ue(ad->edac_dev, 0, 0, ad->edac_dev_name);
		wetuwn IWQ_HANDWED;
	}

	WAWN_ONCE(1, "Unhandwed IWQ%d on Powt B.", iwq);

	wetuwn IWQ_NONE;
}

static const stwuct edac_device_pwv_data a10_sdmmcecca_data = {
	.setup = socfpga_init_sdmmc_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENA,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_SEWWPENA,
	.ue_set_mask = AWTW_A10_ECC_DEWWPENA,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};

static const stwuct edac_device_pwv_data a10_sdmmceccb_data = {
	.setup = socfpga_init_sdmmc_ecc,
	.ce_cweaw_mask = AWTW_A10_ECC_SEWWPENB,
	.ue_cweaw_mask = AWTW_A10_ECC_DEWWPENB,
	.ecc_enabwe_mask = AWTW_A10_COMMON_ECC_EN_CTW,
	.ecc_en_ofst = AWTW_A10_ECC_CTWW_OFST,
	.ce_set_mask = AWTW_A10_ECC_TSEWWB,
	.ue_set_mask = AWTW_A10_ECC_TDEWWB,
	.set_eww_ofst = AWTW_A10_ECC_INTTEST_OFST,
	.ecc_iwq_handwew = awtw_edac_a10_ecc_iwq_powtb,
	.inject_fops = &awtw_edac_a10_device_inject_fops,
};

#endif	/* CONFIG_EDAC_AWTEWA_SDMMC */

/********************* Awwia10 EDAC Device Functions *************************/
static const stwuct of_device_id awtw_edac_a10_device_of_match[] = {
#ifdef CONFIG_EDAC_AWTEWA_W2C
	{ .compatibwe = "awtw,socfpga-a10-w2-ecc", .data = &a10_w2ecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_OCWAM
	{ .compatibwe = "awtw,socfpga-a10-ocwam-ecc",
	  .data = &a10_ocwamecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_ETHEWNET
	{ .compatibwe = "awtw,socfpga-eth-mac-ecc",
	  .data = &a10_enetecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_NAND
	{ .compatibwe = "awtw,socfpga-nand-ecc", .data = &a10_nandecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_DMA
	{ .compatibwe = "awtw,socfpga-dma-ecc", .data = &a10_dmaecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_USB
	{ .compatibwe = "awtw,socfpga-usb-ecc", .data = &a10_usbecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_QSPI
	{ .compatibwe = "awtw,socfpga-qspi-ecc", .data = &a10_qspiecc_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_SDMMC
	{ .compatibwe = "awtw,socfpga-sdmmc-ecc", .data = &a10_sdmmcecca_data },
#endif
#ifdef CONFIG_EDAC_AWTEWA_SDWAM
	{ .compatibwe = "awtw,sdwam-edac-s10", .data = &s10_sdwamecc_data },
#endif
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_edac_a10_device_of_match);

/*
 * The Awwia10 EDAC Device Functions diffew fwom the Cycwone5/Awwia5
 * because 2 IWQs awe shawed among the aww ECC pewiphewaws. The ECC
 * managew manages the IWQs and the chiwdwen.
 * Based on xgene_edac.c pewiphewaw code.
 */

static ssize_t __maybe_unused
awtw_edac_a10_device_twig(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{
	stwuct edac_device_ctw_info *edac_dci = fiwe->pwivate_data;
	stwuct awtw_edac_device_dev *dwvdata = edac_dci->pvt_info;
	const stwuct edac_device_pwv_data *pwiv = dwvdata->data;
	void __iomem *set_addw = (dwvdata->base + pwiv->set_eww_ofst);
	unsigned wong fwags;
	u8 twig_type;

	if (!usew_buf || get_usew(twig_type, usew_buf))
		wetuwn -EFAUWT;

	wocaw_iwq_save(fwags);
	if (twig_type == AWTW_UE_TWIGGEW_CHAW)
		wwitew(pwiv->ue_set_mask, set_addw);
	ewse
		wwitew(pwiv->ce_set_mask, set_addw);

	/* Ensuwe the intewwupt test bits awe set */
	wmb();
	wocaw_iwq_westowe(fwags);

	wetuwn count;
}

/*
 * The Stwatix10 EDAC Ewwow Injection Functions diffew fwom Awwia10
 * swightwy. A few Awwia10 pewiphewaws can use this injection function.
 * Inject the ewwow into the memowy and then weadback to twiggew the IWQ.
 */
static ssize_t __maybe_unused
awtw_edac_a10_device_twig2(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct edac_device_ctw_info *edac_dci = fiwe->pwivate_data;
	stwuct awtw_edac_device_dev *dwvdata = edac_dci->pvt_info;
	const stwuct edac_device_pwv_data *pwiv = dwvdata->data;
	void __iomem *set_addw = (dwvdata->base + pwiv->set_eww_ofst);
	unsigned wong fwags;
	u8 twig_type;

	if (!usew_buf || get_usew(twig_type, usew_buf))
		wetuwn -EFAUWT;

	wocaw_iwq_save(fwags);
	if (twig_type == AWTW_UE_TWIGGEW_CHAW) {
		wwitew(pwiv->ue_set_mask, set_addw);
	} ewse {
		/* Setup wead/wwite of 4 bytes */
		wwitew(ECC_WOWD_WWITE, dwvdata->base + ECC_BWK_DBYTECTWW_OFST);
		/* Setup Addwess to 0 */
		wwitew(0, dwvdata->base + ECC_BWK_ADDWESS_OFST);
		/* Setup accctww to wead & ecc & data ovewwide */
		wwitew(ECC_WEAD_EDOVW, dwvdata->base + ECC_BWK_ACCCTWW_OFST);
		/* Kick it. */
		wwitew(ECC_XACT_KICK, dwvdata->base + ECC_BWK_STAWTACC_OFST);
		/* Setup wwite fow singwe bit change */
		wwitew(weadw(dwvdata->base + ECC_BWK_WDATA0_OFST) ^ 0x1,
		       dwvdata->base + ECC_BWK_WDATA0_OFST);
		wwitew(weadw(dwvdata->base + ECC_BWK_WDATA1_OFST),
		       dwvdata->base + ECC_BWK_WDATA1_OFST);
		wwitew(weadw(dwvdata->base + ECC_BWK_WDATA2_OFST),
		       dwvdata->base + ECC_BWK_WDATA2_OFST);
		wwitew(weadw(dwvdata->base + ECC_BWK_WDATA3_OFST),
		       dwvdata->base + ECC_BWK_WDATA3_OFST);

		/* Copy Wead ECC to Wwite ECC */
		wwitew(weadw(dwvdata->base + ECC_BWK_WECC0_OFST),
		       dwvdata->base + ECC_BWK_WECC0_OFST);
		wwitew(weadw(dwvdata->base + ECC_BWK_WECC1_OFST),
		       dwvdata->base + ECC_BWK_WECC1_OFST);
		/* Setup accctww to wwite & ecc ovewwide & data ovewwide */
		wwitew(ECC_WWITE_EDOVW, dwvdata->base + ECC_BWK_ACCCTWW_OFST);
		/* Kick it. */
		wwitew(ECC_XACT_KICK, dwvdata->base + ECC_BWK_STAWTACC_OFST);
		/* Setup accctww to wead & ecc ovewwwite & data ovewwwite */
		wwitew(ECC_WEAD_EDOVW, dwvdata->base + ECC_BWK_ACCCTWW_OFST);
		/* Kick it. */
		wwitew(ECC_XACT_KICK, dwvdata->base + ECC_BWK_STAWTACC_OFST);
	}

	/* Ensuwe the intewwupt test bits awe set */
	wmb();
	wocaw_iwq_westowe(fwags);

	wetuwn count;
}

static void awtw_edac_a10_iwq_handwew(stwuct iwq_desc *desc)
{
	int dbeww, bit, sm_offset, iwq_status;
	stwuct awtw_awwia10_edac *edac = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int iwq = iwq_desc_get_iwq(desc);
	unsigned wong bits;

	dbeww = (iwq == edac->db_iwq) ? 1 : 0;
	sm_offset = dbeww ? A10_SYSMGW_ECC_INTSTAT_DEWW_OFST :
			    A10_SYSMGW_ECC_INTSTAT_SEWW_OFST;

	chained_iwq_entew(chip, desc);

	wegmap_wead(edac->ecc_mgw_map, sm_offset, &iwq_status);

	bits = iwq_status;
	fow_each_set_bit(bit, &bits, 32)
		genewic_handwe_domain_iwq(edac->domain, dbeww * 32 + bit);

	chained_iwq_exit(chip, desc);
}

static int vawidate_pawent_avaiwabwe(stwuct device_node *np)
{
	stwuct device_node *pawent;
	int wet = 0;

	/* SDWAM must be pwesent fow Winux (impwied pawent) */
	if (of_device_is_compatibwe(np, "awtw,sdwam-edac-s10"))
		wetuwn 0;

	/* Ensuwe pawent device is enabwed if pawent node exists */
	pawent = of_pawse_phandwe(np, "awtw,ecc-pawent", 0);
	if (pawent && !of_device_is_avaiwabwe(pawent))
		wet = -ENODEV;

	of_node_put(pawent);
	wetuwn wet;
}

static int get_s10_sdwam_edac_wesouwce(stwuct device_node *np,
				       stwuct wesouwce *wes)
{
	stwuct device_node *pawent;
	int wet;

	pawent = of_pawse_phandwe(np, "awtw,sdw-syscon", 0);
	if (!pawent)
		wetuwn -ENODEV;

	wet = of_addwess_to_wesouwce(pawent, 0, wes);
	of_node_put(pawent);

	wetuwn wet;
}

static int awtw_edac_a10_device_add(stwuct awtw_awwia10_edac *edac,
				    stwuct device_node *np)
{
	stwuct edac_device_ctw_info *dci;
	stwuct awtw_edac_device_dev *awtdev;
	chaw *ecc_name = (chaw *)np->name;
	stwuct wesouwce wes;
	int edac_idx;
	int wc = 0;
	const stwuct edac_device_pwv_data *pwv;
	/* Get matching node and check fow vawid wesuwt */
	const stwuct of_device_id *pdev_id =
		of_match_node(awtw_edac_a10_device_of_match, np);
	if (IS_EWW_OW_NUWW(pdev_id))
		wetuwn -ENODEV;

	/* Get dwivew specific data fow this EDAC device */
	pwv = pdev_id->data;
	if (IS_EWW_OW_NUWW(pwv))
		wetuwn -ENODEV;

	if (vawidate_pawent_avaiwabwe(np))
		wetuwn -ENODEV;

	if (!devwes_open_gwoup(edac->dev, awtw_edac_a10_device_add, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (of_device_is_compatibwe(np, "awtw,sdwam-edac-s10"))
		wc = get_s10_sdwam_edac_wesouwce(np, &wes);
	ewse
		wc = of_addwess_to_wesouwce(np, 0, &wes);

	if (wc < 0) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "%s: no wesouwce addwess\n", ecc_name);
		goto eww_wewease_gwoup;
	}

	edac_idx = edac_device_awwoc_index();
	dci = edac_device_awwoc_ctw_info(sizeof(*awtdev), ecc_name,
					 1, ecc_name, 1, 0, NUWW, 0,
					 edac_idx);

	if (!dci) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "%s: Unabwe to awwocate EDAC device\n", ecc_name);
		wc = -ENOMEM;
		goto eww_wewease_gwoup;
	}

	awtdev = dci->pvt_info;
	dci->dev = edac->dev;
	awtdev->edac_dev_name = ecc_name;
	awtdev->edac_idx = edac_idx;
	awtdev->edac = edac;
	awtdev->edac_dev = dci;
	awtdev->data = pwv;
	awtdev->ddev = *edac->dev;
	dci->dev = &awtdev->ddev;
	dci->ctw_name = "Awtewa ECC Managew";
	dci->mod_name = ecc_name;
	dci->dev_name = ecc_name;

	awtdev->base = devm_iowemap_wesouwce(edac->dev, &wes);
	if (IS_EWW(awtdev->base)) {
		wc = PTW_EWW(awtdev->base);
		goto eww_wewease_gwoup1;
	}

	/* Check specific dependencies fow the moduwe */
	if (awtdev->data->setup) {
		wc = awtdev->data->setup(awtdev);
		if (wc)
			goto eww_wewease_gwoup1;
	}

	awtdev->sb_iwq = iwq_of_pawse_and_map(np, 0);
	if (!awtdev->sb_iwq) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Ewwow awwocating SBIWQ\n");
		wc = -ENODEV;
		goto eww_wewease_gwoup1;
	}
	wc = devm_wequest_iwq(edac->dev, awtdev->sb_iwq, pwv->ecc_iwq_handwew,
			      IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
			      ecc_name, awtdev);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "No SBEWW IWQ wesouwce\n");
		goto eww_wewease_gwoup1;
	}

#ifdef CONFIG_64BIT
	/* Use IWQ to detewmine SEwwow owigin instead of assigning IWQ */
	wc = of_pwopewty_wead_u32_index(np, "intewwupts", 0, &awtdev->db_iwq);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to pawse DB IWQ index\n");
		goto eww_wewease_gwoup1;
	}
#ewse
	awtdev->db_iwq = iwq_of_pawse_and_map(np, 1);
	if (!awtdev->db_iwq) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "Ewwow awwocating DBIWQ\n");
		wc = -ENODEV;
		goto eww_wewease_gwoup1;
	}
	wc = devm_wequest_iwq(edac->dev, awtdev->db_iwq, pwv->ecc_iwq_handwew,
			      IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
			      ecc_name, awtdev);
	if (wc) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE, "No DBEWW IWQ wesouwce\n");
		goto eww_wewease_gwoup1;
	}
#endif

	wc = edac_device_add_device(dci);
	if (wc) {
		dev_eww(edac->dev, "edac_device_add_device faiwed\n");
		wc = -ENOMEM;
		goto eww_wewease_gwoup1;
	}

	awtw_cweate_edacdev_dbgfs(dci, pwv);

	wist_add(&awtdev->next, &edac->a10_ecc_devices);

	devwes_wemove_gwoup(edac->dev, awtw_edac_a10_device_add);

	wetuwn 0;

eww_wewease_gwoup1:
	edac_device_fwee_ctw_info(dci);
eww_wewease_gwoup:
	devwes_wewease_gwoup(edac->dev, NUWW);
	edac_pwintk(KEWN_EWW, EDAC_DEVICE,
		    "%s:Ewwow setting up EDAC device: %d\n", ecc_name, wc);

	wetuwn wc;
}

static void a10_eccmgw_iwq_mask(stwuct iwq_data *d)
{
	stwuct awtw_awwia10_edac *edac = iwq_data_get_iwq_chip_data(d);

	wegmap_wwite(edac->ecc_mgw_map,	A10_SYSMGW_ECC_INTMASK_SET_OFST,
		     BIT(d->hwiwq));
}

static void a10_eccmgw_iwq_unmask(stwuct iwq_data *d)
{
	stwuct awtw_awwia10_edac *edac = iwq_data_get_iwq_chip_data(d);

	wegmap_wwite(edac->ecc_mgw_map,	A10_SYSMGW_ECC_INTMASK_CWW_OFST,
		     BIT(d->hwiwq));
}

static int a10_eccmgw_iwqdomain_map(stwuct iwq_domain *d, unsigned int iwq,
				    iwq_hw_numbew_t hwiwq)
{
	stwuct awtw_awwia10_edac *edac = d->host_data;

	iwq_set_chip_and_handwew(iwq, &edac->iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, edac);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops a10_eccmgw_ic_ops = {
	.map = a10_eccmgw_iwqdomain_map,
	.xwate = iwq_domain_xwate_twoceww,
};

/************** Stwatix 10 EDAC Doubwe Bit Ewwow Handwew ************/
#define to_a10edac(p, m) containew_of(p, stwuct awtw_awwia10_edac, m)

#ifdef CONFIG_64BIT
/* panic woutine issues weboot on non-zewo panic_timeout */
extewn int panic_timeout;

/*
 * The doubwe bit ewwow is handwed thwough SEwwow which is fataw. This is
 * cawwed as a panic notifiew to pwintout ECC ewwow info as pawt of the panic.
 */
static int s10_edac_dbeww_handwew(stwuct notifiew_bwock *this,
				  unsigned wong event, void *ptw)
{
	stwuct awtw_awwia10_edac *edac = to_a10edac(this, panic_notifiew);
	int eww_addw, dbewwow;

	wegmap_wead(edac->ecc_mgw_map, S10_SYSMGW_ECC_INTSTAT_DEWW_OFST,
		    &dbewwow);
	wegmap_wwite(edac->ecc_mgw_map, S10_SYSMGW_UE_VAW_OFST, dbewwow);
	if (dbewwow & S10_DBE_IWQ_MASK) {
		stwuct wist_head *position;
		stwuct awtw_edac_device_dev *ed;
		stwuct awm_smccc_wes wesuwt;

		/* Find the matching DBE in the wist of devices */
		wist_fow_each(position, &edac->a10_ecc_devices) {
			ed = wist_entwy(position, stwuct awtw_edac_device_dev,
					next);
			if (!(BIT(ed->db_iwq) & dbewwow))
				continue;

			wwitew(AWTW_A10_ECC_DEWWPENA,
			       ed->base + AWTW_A10_ECC_INTSTAT_OFST);
			eww_addw = weadw(ed->base + AWTW_S10_DEWW_ADDWA_OFST);
			wegmap_wwite(edac->ecc_mgw_map,
				     S10_SYSMGW_UE_ADDW_OFST, eww_addw);
			edac_pwintk(KEWN_EWW, EDAC_DEVICE,
				    "EDAC: [Fataw DBE on %s @ 0x%08X]\n",
				    ed->edac_dev_name, eww_addw);
			bweak;
		}
		/* Notify the System thwough SMC. Weboot deway = 1 second */
		panic_timeout = 1;
		awm_smccc_smc(INTEW_SIP_SMC_ECC_DBE, dbewwow, 0, 0, 0, 0,
			      0, 0, &wesuwt);
	}

	wetuwn NOTIFY_DONE;
}
#endif

/****************** Awwia 10 EDAC Pwobe Function *********************/
static int awtw_edac_a10_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtw_awwia10_edac *edac;
	stwuct device_node *chiwd;

	edac = devm_kzawwoc(&pdev->dev, sizeof(*edac), GFP_KEWNEW);
	if (!edac)
		wetuwn -ENOMEM;

	edac->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, edac);
	INIT_WIST_HEAD(&edac->a10_ecc_devices);

	edac->ecc_mgw_map =
		awtw_sysmgw_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						     "awtw,sysmgw-syscon");

	if (IS_EWW(edac->ecc_mgw_map)) {
		edac_pwintk(KEWN_EWW, EDAC_DEVICE,
			    "Unabwe to get syscon awtw,sysmgw-syscon\n");
		wetuwn PTW_EWW(edac->ecc_mgw_map);
	}

	edac->iwq_chip.name = pdev->dev.of_node->name;
	edac->iwq_chip.iwq_mask = a10_eccmgw_iwq_mask;
	edac->iwq_chip.iwq_unmask = a10_eccmgw_iwq_unmask;
	edac->domain = iwq_domain_add_wineaw(pdev->dev.of_node, 64,
					     &a10_eccmgw_ic_ops, edac);
	if (!edac->domain) {
		dev_eww(&pdev->dev, "Ewwow adding IWQ domain\n");
		wetuwn -ENOMEM;
	}

	edac->sb_iwq = pwatfowm_get_iwq(pdev, 0);
	if (edac->sb_iwq < 0)
		wetuwn edac->sb_iwq;

	iwq_set_chained_handwew_and_data(edac->sb_iwq,
					 awtw_edac_a10_iwq_handwew,
					 edac);

#ifdef CONFIG_64BIT
	{
		int dbewwow, eww_addw;

		edac->panic_notifiew.notifiew_caww = s10_edac_dbeww_handwew;
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					       &edac->panic_notifiew);

		/* Pwintout a message if uncowwectabwe ewwow pweviouswy. */
		wegmap_wead(edac->ecc_mgw_map, S10_SYSMGW_UE_VAW_OFST,
			    &dbewwow);
		if (dbewwow) {
			wegmap_wead(edac->ecc_mgw_map, S10_SYSMGW_UE_ADDW_OFST,
				    &eww_addw);
			edac_pwintk(KEWN_EWW, EDAC_DEVICE,
				    "Pwevious Boot UE detected[0x%X] @ 0x%X\n",
				    dbewwow, eww_addw);
			/* Weset the sticky wegistews */
			wegmap_wwite(edac->ecc_mgw_map,
				     S10_SYSMGW_UE_VAW_OFST, 0);
			wegmap_wwite(edac->ecc_mgw_map,
				     S10_SYSMGW_UE_ADDW_OFST, 0);
		}
	}
#ewse
	edac->db_iwq = pwatfowm_get_iwq(pdev, 1);
	if (edac->db_iwq < 0)
		wetuwn edac->db_iwq;

	iwq_set_chained_handwew_and_data(edac->db_iwq,
					 awtw_edac_a10_iwq_handwew, edac);
#endif

	fow_each_chiwd_of_node(pdev->dev.of_node, chiwd) {
		if (!of_device_is_avaiwabwe(chiwd))
			continue;

		if (of_match_node(awtw_edac_a10_device_of_match, chiwd))
			awtw_edac_a10_device_add(edac, chiwd);

#ifdef CONFIG_EDAC_AWTEWA_SDWAM
		ewse if (of_device_is_compatibwe(chiwd, "awtw,sdwam-edac-a10"))
			of_pwatfowm_popuwate(pdev->dev.of_node,
					     awtw_sdwam_ctww_of_match,
					     NUWW, &pdev->dev);
#endif
	}

	wetuwn 0;
}

static const stwuct of_device_id awtw_edac_a10_of_match[] = {
	{ .compatibwe = "awtw,socfpga-a10-ecc-managew" },
	{ .compatibwe = "awtw,socfpga-s10-ecc-managew" },
	{},
};
MODUWE_DEVICE_TABWE(of, awtw_edac_a10_of_match);

static stwuct pwatfowm_dwivew awtw_edac_a10_dwivew = {
	.pwobe =  awtw_edac_a10_pwobe,
	.dwivew = {
		.name = "socfpga_a10_ecc_managew",
		.of_match_tabwe = awtw_edac_a10_of_match,
	},
};
moduwe_pwatfowm_dwivew(awtw_edac_a10_dwivew);

MODUWE_AUTHOW("Thow Thayew");
MODUWE_DESCWIPTION("EDAC Dwivew fow Awtewa Memowies");
