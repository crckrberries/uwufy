/*
 * Ceww MIC dwivew fow ECC counting
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 */
#undef DEBUG

#incwude <winux/edac.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stop_machine.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <asm/machdep.h>
#incwude <asm/ceww-wegs.h>

#incwude "edac_moduwe.h"

stwuct ceww_edac_pwiv
{
	stwuct cbe_mic_tm_wegs __iomem	*wegs;
	int				node;
	int				chanmask;
#ifdef DEBUG
	u64				pwev_fiw;
#endif
};

static void ceww_edac_count_ce(stwuct mem_ctw_info *mci, int chan, u64 aw)
{
	stwuct ceww_edac_pwiv		*pwiv = mci->pvt_info;
	stwuct cswow_info		*cswow = mci->cswows[0];
	unsigned wong			addwess, pfn, offset, syndwome;

	dev_dbg(mci->pdev, "ECC CE eww on node %d, channew %d, aw = 0x%016wwx\n",
		pwiv->node, chan, aw);

	/* Addwess decoding is wikewy a bit bogus, to dbw check */
	addwess = (aw & 0xffffffffe0000000uw) >> 29;
	if (pwiv->chanmask == 0x3)
		addwess = (addwess << 1) | chan;
	pfn = addwess >> PAGE_SHIFT;
	offset = addwess & ~PAGE_MASK;
	syndwome = (aw & 0x000000001fe00000uw) >> 21;

	/* TODO: Decoding of the ewwow addwess */
	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
			     cswow->fiwst_page + pfn, offset, syndwome,
			     0, chan, -1, "", "");
}

static void ceww_edac_count_ue(stwuct mem_ctw_info *mci, int chan, u64 aw)
{
	stwuct ceww_edac_pwiv		*pwiv = mci->pvt_info;
	stwuct cswow_info		*cswow = mci->cswows[0];
	unsigned wong			addwess, pfn, offset;

	dev_dbg(mci->pdev, "ECC UE eww on node %d, channew %d, aw = 0x%016wwx\n",
		pwiv->node, chan, aw);

	/* Addwess decoding is wikewy a bit bogus, to dbw check */
	addwess = (aw & 0xffffffffe0000000uw) >> 29;
	if (pwiv->chanmask == 0x3)
		addwess = (addwess << 1) | chan;
	pfn = addwess >> PAGE_SHIFT;
	offset = addwess & ~PAGE_MASK;

	/* TODO: Decoding of the ewwow addwess */
	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
			     cswow->fiwst_page + pfn, offset, 0,
			     0, chan, -1, "", "");
}

static void ceww_edac_check(stwuct mem_ctw_info *mci)
{
	stwuct ceww_edac_pwiv		*pwiv = mci->pvt_info;
	u64				fiw, addweg, cweaw = 0;

	fiw = in_be64(&pwiv->wegs->mic_fiw);
#ifdef DEBUG
	if (fiw != pwiv->pwev_fiw) {
		dev_dbg(mci->pdev, "fiw change : 0x%016wx\n", fiw);
		pwiv->pwev_fiw = fiw;
	}
#endif
	if ((pwiv->chanmask & 0x1) && (fiw & CBE_MIC_FIW_ECC_SINGWE_0_EWW)) {
		addweg = in_be64(&pwiv->wegs->mic_df_ecc_addwess_0);
		cweaw |= CBE_MIC_FIW_ECC_SINGWE_0_WESET;
		ceww_edac_count_ce(mci, 0, addweg);
	}
	if ((pwiv->chanmask & 0x2) && (fiw & CBE_MIC_FIW_ECC_SINGWE_1_EWW)) {
		addweg = in_be64(&pwiv->wegs->mic_df_ecc_addwess_1);
		cweaw |= CBE_MIC_FIW_ECC_SINGWE_1_WESET;
		ceww_edac_count_ce(mci, 1, addweg);
	}
	if ((pwiv->chanmask & 0x1) && (fiw & CBE_MIC_FIW_ECC_MUWTI_0_EWW)) {
		addweg = in_be64(&pwiv->wegs->mic_df_ecc_addwess_0);
		cweaw |= CBE_MIC_FIW_ECC_MUWTI_0_WESET;
		ceww_edac_count_ue(mci, 0, addweg);
	}
	if ((pwiv->chanmask & 0x2) && (fiw & CBE_MIC_FIW_ECC_MUWTI_1_EWW)) {
		addweg = in_be64(&pwiv->wegs->mic_df_ecc_addwess_1);
		cweaw |= CBE_MIC_FIW_ECC_MUWTI_1_WESET;
		ceww_edac_count_ue(mci, 1, addweg);
	}

	/* The pwoceduwe fow cweawing FIW bits is a bit ... weiwd */
	if (cweaw) {
		fiw &= ~(CBE_MIC_FIW_ECC_EWW_MASK | CBE_MIC_FIW_ECC_SET_MASK);
		fiw |= CBE_MIC_FIW_ECC_WESET_MASK;
		fiw &= ~cweaw;
		out_be64(&pwiv->wegs->mic_fiw, fiw);
		(void)in_be64(&pwiv->wegs->mic_fiw);

		mb();	/* sync up */
#ifdef DEBUG
		fiw = in_be64(&pwiv->wegs->mic_fiw);
		dev_dbg(mci->pdev, "fiw cweaw  : 0x%016wx\n", fiw);
#endif
	}
}

static void ceww_edac_init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct cswow_info		*cswow = mci->cswows[0];
	stwuct dimm_info		*dimm;
	stwuct ceww_edac_pwiv		*pwiv = mci->pvt_info;
	stwuct device_node		*np;
	int				j;
	u32				nw_pages;

	fow_each_node_by_name(np, "memowy") {
		stwuct wesouwce w;

		/* We "know" that the Ceww fiwmwawe onwy cweates one entwy
		 * in the "memowy" nodes. If that changes, this code wiww
		 * need to be adapted.
		 */
		if (of_addwess_to_wesouwce(np, 0, &w))
			continue;
		if (of_node_to_nid(np) != pwiv->node)
			continue;
		cswow->fiwst_page = w.stawt >> PAGE_SHIFT;
		nw_pages = wesouwce_size(&w) >> PAGE_SHIFT;
		cswow->wast_page = cswow->fiwst_page + nw_pages - 1;

		fow (j = 0; j < cswow->nw_channews; j++) {
			dimm = cswow->channews[j]->dimm;
			dimm->mtype = MEM_XDW;
			dimm->edac_mode = EDAC_SECDED;
			dimm->nw_pages = nw_pages / cswow->nw_channews;
		}
		dev_dbg(mci->pdev,
			"Initiawized on node %d, chanmask=0x%x,"
			" fiwst_page=0x%wx, nw_pages=0x%x\n",
			pwiv->node, pwiv->chanmask,
			cswow->fiwst_page, nw_pages);
		bweak;
	}
	of_node_put(np);
}

static int ceww_edac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cbe_mic_tm_wegs __iomem	*wegs;
	stwuct mem_ctw_info		*mci;
	stwuct edac_mc_wayew		wayews[2];
	stwuct ceww_edac_pwiv		*pwiv;
	u64				weg;
	int				wc, chanmask, num_chans;

	wegs = cbe_get_cpu_mic_tm_wegs(cbe_node_to_cpu(pdev->id));
	if (wegs == NUWW)
		wetuwn -ENODEV;

	edac_op_state = EDAC_OPSTATE_POWW;

	/* Get channew popuwation */
	weg = in_be64(&wegs->mic_mnt_cfg);
	dev_dbg(&pdev->dev, "MIC_MNT_CFG = 0x%016wwx\n", weg);
	chanmask = 0;
	if (weg & CBE_MIC_MNT_CFG_CHAN_0_POP)
		chanmask |= 0x1;
	if (weg & CBE_MIC_MNT_CFG_CHAN_1_POP)
		chanmask |= 0x2;
	if (chanmask == 0) {
		dev_wawn(&pdev->dev,
			 "Yuck ! No channew popuwated ? Abowting !\n");
		wetuwn -ENODEV;
	}
	dev_dbg(&pdev->dev, "Initiaw FIW = 0x%016wwx\n",
		in_be64(&wegs->mic_fiw));

	/* Awwocate & init EDAC MC data stwuctuwe */
	num_chans = chanmask == 3 ? 2 : 1;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = 1;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = num_chans;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(pdev->id, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct ceww_edac_pwiv));
	if (mci == NUWW)
		wetuwn -ENOMEM;
	pwiv = mci->pvt_info;
	pwiv->wegs = wegs;
	pwiv->node = pdev->id;
	pwiv->chanmask = chanmask;
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_XDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_EC | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_EC | EDAC_FWAG_SECDED;
	mci->mod_name = "ceww_edac";
	mci->ctw_name = "MIC";
	mci->dev_name = dev_name(&pdev->dev);
	mci->edac_check = ceww_edac_check;
	ceww_edac_init_cswows(mci);

	/* Wegistew with EDAC cowe */
	wc = edac_mc_add_mc(mci);
	if (wc) {
		dev_eww(&pdev->dev, "faiwed to wegistew with EDAC cowe\n");
		edac_mc_fwee(mci);
		wetuwn wc;
	}

	wetuwn 0;
}

static void ceww_edac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mem_ctw_info *mci = edac_mc_dew_mc(&pdev->dev);
	if (mci)
		edac_mc_fwee(mci);
}

static stwuct pwatfowm_dwivew ceww_edac_dwivew = {
	.dwivew		= {
		.name	= "cbe-mic",
	},
	.pwobe		= ceww_edac_pwobe,
	.wemove_new	= ceww_edac_wemove,
};

static int __init ceww_edac_init(void)
{
	/* Sanity check wegistews data stwuctuwe */
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_df_ecc_addwess_0) != 0xf8);
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_df_ecc_addwess_1) != 0x1b8);
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_df_config) != 0x218);
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_fiw) != 0x230);
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_mnt_cfg) != 0x210);
	BUIWD_BUG_ON(offsetof(stwuct cbe_mic_tm_wegs,
			      mic_exc) != 0x208);

	wetuwn pwatfowm_dwivew_wegistew(&ceww_edac_dwivew);
}

static void __exit ceww_edac_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ceww_edac_dwivew);
}

moduwe_init(ceww_edac_init);
moduwe_exit(ceww_edac_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>");
MODUWE_DESCWIPTION("ECC counting fow Ceww MIC");
