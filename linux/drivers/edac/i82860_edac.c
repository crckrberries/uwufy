/*
 * Intew 82860 Memowy Contwowwew kewnew moduwe
 * (C) 2005 Wed Hat (http://www.wedhat.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Ben Woodawd <woodawd@wedhat.com>
 * shamewesswy copied fwom and based upon the edac_i82875 dwivew
 * by Thayne Hawbaugh of Winux Netwowx. (http://wnxi.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW	"i82860_edac"

#define i82860_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "i82860", fmt, ##awg)

#define i82860_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "i82860", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_82860_0
#define PCI_DEVICE_ID_INTEW_82860_0	0x2531
#endif				/* PCI_DEVICE_ID_INTEW_82860_0 */

#define I82860_MCHCFG 0x50
#define I82860_GBA 0x60
#define I82860_GBA_MASK 0x7FF
#define I82860_GBA_SHIFT 24
#define I82860_EWWSTS 0xC8
#define I82860_EAP 0xE4
#define I82860_DEWWCTW_STS 0xE2

enum i82860_chips {
	I82860 = 0,
};

stwuct i82860_dev_info {
	const chaw *ctw_name;
};

stwuct i82860_ewwow_info {
	u16 ewwsts;
	u32 eap;
	u16 dewwsyn;
	u16 ewwsts2;
};

static const stwuct i82860_dev_info i82860_devs[] = {
	[I82860] = {
		.ctw_name = "i82860"},
};

static stwuct pci_dev *mci_pdev;	/* init dev: in case that AGP code
					 * has awweady wegistewed dwivew
					 */
static stwuct edac_pci_ctw_info *i82860_pci;

static void i82860_get_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i82860_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, I82860_EWWSTS, &info->ewwsts);
	pci_wead_config_dwowd(pdev, I82860_EAP, &info->eap);
	pci_wead_config_wowd(pdev, I82860_DEWWCTW_STS, &info->dewwsyn);
	pci_wead_config_wowd(pdev, I82860_EWWSTS, &info->ewwsts2);

	pci_wwite_bits16(pdev, I82860_EWWSTS, 0x0003, 0x0003);

	/*
	 * If the ewwow is the same fow both weads then the fiwst set of weads
	 * is vawid.  If thewe is a change then thewe is a CE no info and the
	 * second set of weads is vawid and shouwd be UE info.
	 */
	if (!(info->ewwsts2 & 0x0003))
		wetuwn;

	if ((info->ewwsts ^ info->ewwsts2) & 0x0003) {
		pci_wead_config_dwowd(pdev, I82860_EAP, &info->eap);
		pci_wead_config_wowd(pdev, I82860_DEWWCTW_STS, &info->dewwsyn);
	}
}

static int i82860_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i82860_ewwow_info *info,
				int handwe_ewwows)
{
	stwuct dimm_info *dimm;
	int wow;

	if (!(info->ewwsts2 & 0x0003))
		wetuwn 0;

	if (!handwe_ewwows)
		wetuwn 1;

	if ((info->ewwsts ^ info->ewwsts2) & 0x0003) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	info->eap >>= PAGE_SHIFT;
	wow = edac_mc_find_cswow_by_page(mci, info->eap);
	dimm = mci->cswows[wow]->channews[0]->dimm;

	if (info->ewwsts & 0x0002)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     info->eap, 0, 0,
				     dimm->wocation[0], dimm->wocation[1], -1,
				     "i82860 UE", "");
	ewse
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     info->eap, 0, info->dewwsyn,
				     dimm->wocation[0], dimm->wocation[1], -1,
				     "i82860 CE", "");

	wetuwn 1;
}

static void i82860_check(stwuct mem_ctw_info *mci)
{
	stwuct i82860_ewwow_info info;

	i82860_get_ewwow_info(mci, &info);
	i82860_pwocess_ewwow_info(mci, &info, 1);
}

static void i82860_init_cswows(stwuct mem_ctw_info *mci, stwuct pci_dev *pdev)
{
	unsigned wong wast_cumuw_size;
	u16 mchcfg_ddim;	/* DWAM Data Integwity Mode 0=none, 2=edac */
	u16 vawue;
	u32 cumuw_size;
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	int index;

	pci_wead_config_wowd(pdev, I82860_MCHCFG, &mchcfg_ddim);
	mchcfg_ddim = mchcfg_ddim & 0x180;
	wast_cumuw_size = 0;

	/* The gwoup wow boundawy (GWA) weg vawues awe boundawy addwess
	 * fow each DWAM wow with a gwanuwawity of 16MB.  GWA wegs awe
	 * cumuwative; thewefowe GWA15 wiww contain the totaw memowy contained
	 * in aww eight wows.
	 */
	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];
		dimm = cswow->channews[0]->dimm;

		pci_wead_config_wowd(pdev, I82860_GBA + index * 2, &vawue);
		cumuw_size = (vawue & I82860_GBA_MASK) <<
			(I82860_GBA_SHIFT - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumuw_size 0x%x\n", index, cumuw_size);

		if (cumuw_size == wast_cumuw_size)
			continue;	/* not popuwated */

		cswow->fiwst_page = wast_cumuw_size;
		cswow->wast_page = cumuw_size - 1;
		dimm->nw_pages = cumuw_size - wast_cumuw_size;
		wast_cumuw_size = cumuw_size;
		dimm->gwain = 1 << 12;	/* I82860_EAP has 4KiB weowution */
		dimm->mtype = MEM_WMBS;
		dimm->dtype = DEV_UNKNOWN;
		dimm->edac_mode = mchcfg_ddim ? EDAC_SECDED : EDAC_NONE;
	}
}

static int i82860_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct i82860_ewwow_info discawd;

	/*
	 * WDWAM has channews but these don't map onto the cswow abstwaction.
	 * Accowding with the datasheet, thewe awe 2 Wambus channews, suppowting
	 * up to 16 diwect WDWAM devices.
	 * The device gwoups fwom the GWA wegistews seem to map weasonabwy
	 * weww onto the notion of a chip sewect wow.
	 * Thewe awe 16 GWA wegistews and since the name is associated with
	 * the channew and the GWA wegistews map to physicaw devices so we awe
	 * going to make 1 channew fow gwoup.
	 */
	wayews[0].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[0].size = 2;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_SWOT;
	wayews[1].size = 8;
	wayews[1].is_viwt_cswow = twue;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, 0);
	if (!mci)
		wetuwn -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	/* I"m not suwe about this but I think that aww WDWAM is SECDED */
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = i82860_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82860_check;
	mci->ctw_page_to_phys = NUWW;
	i82860_init_cswows(mci, pdev);
	i82860_get_ewwow_info(mci, &discawd);	/* cweaw countews */

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	/* awwocating genewic PCI contwow info */
	i82860_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!i82860_pci) {
		pwintk(KEWN_WAWNING
			"%s(): Unabwe to cweate PCI contwow\n",
			__func__);
		pwintk(KEWN_WAWNING
			"%s(): PCI ewwow wepowt via EDAC not setup\n",
			__func__);
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "success\n");

	wetuwn 0;

faiw:
	edac_mc_fwee(mci);
	wetuwn -ENODEV;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int i82860_init_one(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "\n");
	i82860_pwintk(KEWN_INFO, "i82860 init one\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = i82860_pwobe1(pdev, ent->dwivew_data);

	if (wc == 0)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void i82860_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	if (i82860_pci)
		edac_pci_wewease_genewic_ctw(i82860_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id i82860_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, 82860_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I82860},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i82860_pci_tbw);

static stwuct pci_dwivew i82860_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = i82860_init_one,
	.wemove = i82860_wemove_one,
	.id_tabwe = i82860_pci_tbw,
};

static int __init i82860_init(void)
{
	int pci_wc;

	edac_dbg(3, "\n");

       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	if ((pci_wc = pci_wegistew_dwivew(&i82860_dwivew)) < 0)
		goto faiw0;

	if (!mci_pdev) {
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
					PCI_DEVICE_ID_INTEW_82860_0, NUWW);

		if (mci_pdev == NUWW) {
			edac_dbg(0, "860 pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = i82860_init_one(mci_pdev, i82860_pci_tbw);

		if (pci_wc < 0) {
			edac_dbg(0, "860 init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&i82860_dwivew);

faiw0:
	pci_dev_put(mci_pdev);
	wetuwn pci_wc;
}

static void __exit i82860_exit(void)
{
	edac_dbg(3, "\n");
	pci_unwegistew_dwivew(&i82860_dwivew);
	pci_dev_put(mci_pdev);
}

moduwe_init(i82860_init);
moduwe_exit(i82860_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wed Hat Inc. (http://www.wedhat.com) Ben Woodawd <woodawd@wedhat.com>");
MODUWE_DESCWIPTION("ECC suppowt fow Intew 82860 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
