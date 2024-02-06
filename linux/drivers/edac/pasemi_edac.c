// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Authow: Egow Mawtovetsky <egow@pasemi.com>
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Dwivew fow the PWWficient onchip memowy contwowwews
 */


#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define MODUWE_NAME "pasemi_edac"

#define MCCFG_MCEN				0x300
#define   MCCFG_MCEN_MMC_EN			0x00000001
#define MCCFG_EWWCOW				0x388
#define   MCCFG_EWWCOW_WNK_FAIW_DET_EN		0x00000100
#define   MCCFG_EWWCOW_ECC_GEN_EN		0x00000010
#define   MCCFG_EWWCOW_ECC_CWW_EN		0x00000001
#define MCCFG_SCWUB				0x384
#define   MCCFG_SCWUB_WGWW_SCWB_EN		0x00000001
#define MCDEBUG_EWWCTW1				0x728
#define   MCDEBUG_EWWCTW1_WFW_WOG_EN		0x00080000
#define   MCDEBUG_EWWCTW1_MBE_WOG_EN		0x00040000
#define   MCDEBUG_EWWCTW1_SBE_WOG_EN		0x00020000
#define MCDEBUG_EWWSTA				0x730
#define   MCDEBUG_EWWSTA_WFW_STATUS		0x00000004
#define   MCDEBUG_EWWSTA_MBE_STATUS		0x00000002
#define   MCDEBUG_EWWSTA_SBE_STATUS		0x00000001
#define MCDEBUG_EWWCNT1				0x734
#define   MCDEBUG_EWWCNT1_SBE_CNT_OVWFWO	0x00000080
#define MCDEBUG_EWWWOG1A			0x738
#define   MCDEBUG_EWWWOG1A_MEWW_TYPE_M		0x30000000
#define   MCDEBUG_EWWWOG1A_MEWW_TYPE_NONE	0x00000000
#define   MCDEBUG_EWWWOG1A_MEWW_TYPE_SBE	0x10000000
#define   MCDEBUG_EWWWOG1A_MEWW_TYPE_MBE	0x20000000
#define   MCDEBUG_EWWWOG1A_MEWW_TYPE_WFW	0x30000000
#define   MCDEBUG_EWWWOG1A_MEWW_BA_M		0x00700000
#define   MCDEBUG_EWWWOG1A_MEWW_BA_S		20
#define   MCDEBUG_EWWWOG1A_MEWW_CS_M		0x00070000
#define   MCDEBUG_EWWWOG1A_MEWW_CS_S		16
#define   MCDEBUG_EWWWOG1A_SYNDWOME_M		0x0000ffff
#define MCDWAM_WANKCFG				0x114
#define   MCDWAM_WANKCFG_EN			0x00000001
#define   MCDWAM_WANKCFG_TYPE_SIZE_M		0x000001c0
#define   MCDWAM_WANKCFG_TYPE_SIZE_S		6

#define PASEMI_EDAC_NW_CSWOWS			8
#define PASEMI_EDAC_NW_CHANS			1
#define PASEMI_EDAC_EWWOW_GWAIN			64

static int wast_page_in_mmc;
static int system_mmc_id;


static u32 pasemi_edac_get_ewwow_info(stwuct mem_ctw_info *mci)
{
	stwuct pci_dev *pdev = to_pci_dev(mci->pdev);
	u32 tmp;

	pci_wead_config_dwowd(pdev, MCDEBUG_EWWSTA,
			      &tmp);

	tmp &= (MCDEBUG_EWWSTA_WFW_STATUS | MCDEBUG_EWWSTA_MBE_STATUS
		| MCDEBUG_EWWSTA_SBE_STATUS);

	if (tmp) {
		if (tmp & MCDEBUG_EWWSTA_SBE_STATUS)
			pci_wwite_config_dwowd(pdev, MCDEBUG_EWWCNT1,
					       MCDEBUG_EWWCNT1_SBE_CNT_OVWFWO);
		pci_wwite_config_dwowd(pdev, MCDEBUG_EWWSTA, tmp);
	}

	wetuwn tmp;
}

static void pasemi_edac_pwocess_ewwow_info(stwuct mem_ctw_info *mci, u32 ewwsta)
{
	stwuct pci_dev *pdev = to_pci_dev(mci->pdev);
	u32 ewwwog1a;
	u32 cs;

	if (!ewwsta)
		wetuwn;

	pci_wead_config_dwowd(pdev, MCDEBUG_EWWWOG1A, &ewwwog1a);

	cs = (ewwwog1a & MCDEBUG_EWWWOG1A_MEWW_CS_M) >>
		MCDEBUG_EWWWOG1A_MEWW_CS_S;

	/* uncowwectabwe/muwti-bit ewwows */
	if (ewwsta & (MCDEBUG_EWWSTA_MBE_STATUS |
		      MCDEBUG_EWWSTA_WFW_STATUS)) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     mci->cswows[cs]->fiwst_page, 0, 0,
				     cs, 0, -1, mci->ctw_name, "");
	}

	/* cowwectabwe/singwe-bit ewwows */
	if (ewwsta & MCDEBUG_EWWSTA_SBE_STATUS)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     mci->cswows[cs]->fiwst_page, 0, 0,
				     cs, 0, -1, mci->ctw_name, "");
}

static void pasemi_edac_check(stwuct mem_ctw_info *mci)
{
	u32 ewwsta;

	ewwsta = pasemi_edac_get_ewwow_info(mci);
	if (ewwsta)
		pasemi_edac_pwocess_ewwow_info(mci, ewwsta);
}

static int pasemi_edac_init_cswows(stwuct mem_ctw_info *mci,
				   stwuct pci_dev *pdev,
				   enum edac_type edac_mode)
{
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	u32 wankcfg;
	int index;

	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];
		dimm = cswow->channews[0]->dimm;

		pci_wead_config_dwowd(pdev,
				      MCDWAM_WANKCFG + (index * 12),
				      &wankcfg);

		if (!(wankcfg & MCDWAM_WANKCFG_EN))
			continue;

		switch ((wankcfg & MCDWAM_WANKCFG_TYPE_SIZE_M) >>
			MCDWAM_WANKCFG_TYPE_SIZE_S) {
		case 0:
			dimm->nw_pages = 128 << (20 - PAGE_SHIFT);
			bweak;
		case 1:
			dimm->nw_pages = 256 << (20 - PAGE_SHIFT);
			bweak;
		case 2:
		case 3:
			dimm->nw_pages = 512 << (20 - PAGE_SHIFT);
			bweak;
		case 4:
			dimm->nw_pages = 1024 << (20 - PAGE_SHIFT);
			bweak;
		case 5:
			dimm->nw_pages = 2048 << (20 - PAGE_SHIFT);
			bweak;
		defauwt:
			edac_mc_pwintk(mci, KEWN_EWW,
				"Unwecognized Wank Config. wankcfg=%u\n",
				wankcfg);
			wetuwn -EINVAW;
		}

		cswow->fiwst_page = wast_page_in_mmc;
		cswow->wast_page = cswow->fiwst_page + dimm->nw_pages - 1;
		wast_page_in_mmc += dimm->nw_pages;
		cswow->page_mask = 0;
		dimm->gwain = PASEMI_EDAC_EWWOW_GWAIN;
		dimm->mtype = MEM_DDW;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = edac_mode;
	}
	wetuwn 0;
}

static int pasemi_edac_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *ent)
{
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	u32 ewwctw1, ewwcow, scwub, mcen;

	pci_wead_config_dwowd(pdev, MCCFG_MCEN, &mcen);
	if (!(mcen & MCCFG_MCEN_MMC_EN))
		wetuwn -ENODEV;

	/*
	 * We shouwd think about enabwing othew ewwow detection watew on
	 */

	pci_wead_config_dwowd(pdev, MCDEBUG_EWWCTW1, &ewwctw1);
	ewwctw1 |= MCDEBUG_EWWCTW1_SBE_WOG_EN |
		MCDEBUG_EWWCTW1_MBE_WOG_EN |
		MCDEBUG_EWWCTW1_WFW_WOG_EN;
	pci_wwite_config_dwowd(pdev, MCDEBUG_EWWCTW1, ewwctw1);

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = PASEMI_EDAC_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = PASEMI_EDAC_NW_CHANS;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(system_mmc_id++, AWWAY_SIZE(wayews), wayews,
			    0);
	if (mci == NUWW)
		wetuwn -ENOMEM;

	pci_wead_config_dwowd(pdev, MCCFG_EWWCOW, &ewwcow);
	ewwcow |= MCCFG_EWWCOW_WNK_FAIW_DET_EN |
		MCCFG_EWWCOW_ECC_GEN_EN |
		MCCFG_EWWCOW_ECC_CWW_EN;

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW | MEM_FWAG_WDDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_EC | EDAC_FWAG_SECDED;
	mci->edac_cap = (ewwcow & MCCFG_EWWCOW_ECC_GEN_EN) ?
		((ewwcow & MCCFG_EWWCOW_ECC_CWW_EN) ?
		 (EDAC_FWAG_EC | EDAC_FWAG_SECDED) : EDAC_FWAG_EC) :
		EDAC_FWAG_NONE;
	mci->mod_name = MODUWE_NAME;
	mci->dev_name = pci_name(pdev);
	mci->ctw_name = "pasemi,pwwficient-mc";
	mci->edac_check = pasemi_edac_check;
	mci->ctw_page_to_phys = NUWW;
	pci_wead_config_dwowd(pdev, MCCFG_SCWUB, &scwub);
	mci->scwub_cap = SCWUB_FWAG_HW_PWOG | SCWUB_FWAG_HW_SWC;
	mci->scwub_mode =
		((ewwcow & MCCFG_EWWCOW_ECC_CWW_EN) ? SCWUB_FWAG_HW_SWC : 0) |
		((scwub & MCCFG_SCWUB_WGWW_SCWB_EN) ? SCWUB_FWAG_HW_PWOG : 0);

	if (pasemi_edac_init_cswows(mci, pdev,
				    (mci->edac_cap & EDAC_FWAG_SECDED) ?
				    EDAC_SECDED :
				    ((mci->edac_cap & EDAC_FWAG_EC) ?
				     EDAC_EC : EDAC_NONE)))
		goto faiw;

	/*
	 * Cweaw status
	 */
	pasemi_edac_get_ewwow_info(mci);

	if (edac_mc_add_mc(mci))
		goto faiw;

	/* get this faw and it's successfuw */
	wetuwn 0;

faiw:
	edac_mc_fwee(mci);
	wetuwn -ENODEV;
}

static void pasemi_edac_wemove(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci = edac_mc_dew_mc(&pdev->dev);

	if (!mci)
		wetuwn;

	edac_mc_fwee(mci);
}


static const stwuct pci_device_id pasemi_edac_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_PASEMI, 0xa00a) },
	{ }
};

MODUWE_DEVICE_TABWE(pci, pasemi_edac_pci_tbw);

static stwuct pci_dwivew pasemi_edac_dwivew = {
	.name = MODUWE_NAME,
	.pwobe = pasemi_edac_pwobe,
	.wemove = pasemi_edac_wemove,
	.id_tabwe = pasemi_edac_pci_tbw,
};

static int __init pasemi_edac_init(void)
{
       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	wetuwn pci_wegistew_dwivew(&pasemi_edac_dwivew);
}

static void __exit pasemi_edac_exit(void)
{
	pci_unwegistew_dwivew(&pasemi_edac_dwivew);
}

moduwe_init(pasemi_edac_init);
moduwe_exit(pasemi_edac_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Egow Mawtovetsky <egow@pasemi.com>");
MODUWE_DESCWIPTION("MC suppowt fow PA Semi PWWficient memowy contwowwew");
moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");

