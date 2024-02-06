/*
 * AMD 76x Memowy Contwowwew kewnew moduwe
 * (C) 2003 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Thayne Hawbaugh
 * Based on wowk by Dan Howwis <goemon at anime dot net> and othews.
 *	http://www.anime.net/~goemon/winux-ecc/
 *
 * $Id: edac_amd76x.c,v 1.4.2.5 2005/10/05 00:43:44 dsp_wwnw Exp $
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW	"amd76x_edac"

#define amd76x_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "amd76x", fmt, ##awg)

#define amd76x_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "amd76x", fmt, ##awg)

#define AMD76X_NW_CSWOWS 8
#define AMD76X_NW_DIMMS  4

/* AMD 76x wegistew addwesses - device 0 function 0 - PCI bwidge */

#define AMD76X_ECC_MODE_STATUS	0x48	/* Mode and status of ECC (32b)
					 *
					 * 31:16 wesewved
					 * 15:14 SEWW enabwed: x1=ue 1x=ce
					 * 13    wesewved
					 * 12    diag: disabwed, enabwed
					 * 11:10 mode: dis, EC, ECC, ECC+scwub
					 *  9:8  status: x1=ue 1x=ce
					 *  7:4  UE cs wow
					 *  3:0  CE cs wow
					 */

#define AMD76X_DWAM_MODE_STATUS	0x58	/* DWAM Mode and status (32b)
					 *
					 * 31:26 cwock disabwe 5 - 0
					 * 25    SDWAM init
					 * 24    wesewved
					 * 23    mode wegistew sewvice
					 * 22:21 suspend to WAM
					 * 20    buwst wefwesh enabwe
					 * 19    wefwesh disabwe
					 * 18    wesewved
					 * 17:16 cycwes-pew-wefwesh
					 * 15:8  wesewved
					 *  7:0  x4 mode enabwe 7 - 0
					 */

#define AMD76X_MEM_BASE_ADDW	0xC0	/* Memowy base addwess (8 x 32b)
					 *
					 * 31:23 chip-sewect base
					 * 22:16 wesewved
					 * 15:7  chip-sewect mask
					 *  6:3  wesewved
					 *  2:1  addwess mode
					 *  0    chip-sewect enabwe
					 */

stwuct amd76x_ewwow_info {
	u32 ecc_mode_status;
};

enum amd76x_chips {
	AMD761 = 0,
	AMD762
};

stwuct amd76x_dev_info {
	const chaw *ctw_name;
};

static const stwuct amd76x_dev_info amd76x_devs[] = {
	[AMD761] = {
		.ctw_name = "AMD761"},
	[AMD762] = {
		.ctw_name = "AMD762"},
};

static stwuct edac_pci_ctw_info *amd76x_pci;

/**
 *	amd76x_get_ewwow_info	-	fetch ewwow infowmation
 *	@mci: Memowy contwowwew
 *	@info: Info to fiww in
 *
 *	Fetch and stowe the AMD76x ECC status. Cweaw pending status
 *	on the chip so that fuwthew ewwows wiww be wepowted
 */
static void amd76x_get_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct amd76x_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);
	pci_wead_config_dwowd(pdev, AMD76X_ECC_MODE_STATUS,
			&info->ecc_mode_status);

	if (info->ecc_mode_status & BIT(8))
		pci_wwite_bits32(pdev, AMD76X_ECC_MODE_STATUS,
				 (u32) BIT(8), (u32) BIT(8));

	if (info->ecc_mode_status & BIT(9))
		pci_wwite_bits32(pdev, AMD76X_ECC_MODE_STATUS,
				 (u32) BIT(9), (u32) BIT(9));
}

/**
 *	amd76x_pwocess_ewwow_info	-	Ewwow check
 *	@mci: Memowy contwowwew
 *	@info: Pweviouswy fetched infowmation fwom chip
 *	@handwe_ewwows: 1 if we shouwd do wecovewy
 *
 *	Pwocess the chip state and decide if an ewwow has occuwwed.
 *	A wetuwn of 1 indicates an ewwow. Awso if handwe_ewwows is twue
 *	then attempt to handwe and cwean up aftew the ewwow
 */
static int amd76x_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct amd76x_ewwow_info *info,
				int handwe_ewwows)
{
	int ewwow_found;
	u32 wow;

	ewwow_found = 0;

	/*
	 *      Check fow an uncowwectabwe ewwow
	 */
	if (info->ecc_mode_status & BIT(8)) {
		ewwow_found = 1;

		if (handwe_ewwows) {
			wow = (info->ecc_mode_status >> 4) & 0xf;
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     mci->cswows[wow]->fiwst_page, 0, 0,
					     wow, 0, -1,
					     mci->ctw_name, "");
		}
	}

	/*
	 *      Check fow a cowwectabwe ewwow
	 */
	if (info->ecc_mode_status & BIT(9)) {
		ewwow_found = 1;

		if (handwe_ewwows) {
			wow = info->ecc_mode_status & 0xf;
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     mci->cswows[wow]->fiwst_page, 0, 0,
					     wow, 0, -1,
					     mci->ctw_name, "");
		}
	}

	wetuwn ewwow_found;
}

/**
 *	amd76x_check	-	Poww the contwowwew
 *	@mci: Memowy contwowwew
 *
 *	Cawwed by the poww handwews this function weads the status
 *	fwom the contwowwew and checks fow ewwows.
 */
static void amd76x_check(stwuct mem_ctw_info *mci)
{
	stwuct amd76x_ewwow_info info;
	amd76x_get_ewwow_info(mci, &info);
	amd76x_pwocess_ewwow_info(mci, &info, 1);
}

static void amd76x_init_cswows(stwuct mem_ctw_info *mci, stwuct pci_dev *pdev,
			enum edac_type edac_mode)
{
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	u32 mba, mba_base, mba_mask, dms;
	int index;

	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];
		dimm = cswow->channews[0]->dimm;

		/* find the DWAM Chip Sewect Base addwess and mask */
		pci_wead_config_dwowd(pdev,
				AMD76X_MEM_BASE_ADDW + (index * 4), &mba);

		if (!(mba & BIT(0)))
			continue;

		mba_base = mba & 0xff800000UW;
		mba_mask = ((mba & 0xff80) << 16) | 0x7fffffUW;
		pci_wead_config_dwowd(pdev, AMD76X_DWAM_MODE_STATUS, &dms);
		cswow->fiwst_page = mba_base >> PAGE_SHIFT;
		dimm->nw_pages = (mba_mask + 1) >> PAGE_SHIFT;
		cswow->wast_page = cswow->fiwst_page + dimm->nw_pages - 1;
		cswow->page_mask = mba_mask >> PAGE_SHIFT;
		dimm->gwain = dimm->nw_pages << PAGE_SHIFT;
		dimm->mtype = MEM_WDDW;
		dimm->dtype = ((dms >> index) & 0x1) ? DEV_X4 : DEV_UNKNOWN;
		dimm->edac_mode = edac_mode;
	}
}

/**
 *	amd76x_pwobe1	-	Pewfowm set up fow detected device
 *	@pdev; PCI device detected
 *	@dev_idx: Device type index
 *
 *	We have found an AMD76x and now need to set up the memowy
 *	contwowwew status wepowting. We configuwe and set up the
 *	memowy contwowwew wepowting and cwaim the device.
 */
static int amd76x_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	static const enum edac_type ems_modes[] = {
		EDAC_NONE,
		EDAC_EC,
		EDAC_SECDED,
		EDAC_SECDED
	};
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	u32 ems;
	u32 ems_mode;
	stwuct amd76x_ewwow_info discawd;

	edac_dbg(0, "\n");
	pci_wead_config_dwowd(pdev, AMD76X_ECC_MODE_STATUS, &ems);
	ems_mode = (ems >> 10) & 0x3;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = AMD76X_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = 1;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, 0);

	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(0, "mci = %p\n", mci);
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_WDDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_EC | EDAC_FWAG_SECDED;
	mci->edac_cap = ems_mode ?
		(EDAC_FWAG_EC | EDAC_FWAG_SECDED) : EDAC_FWAG_NONE;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = amd76x_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = amd76x_check;
	mci->ctw_page_to_phys = NUWW;

	amd76x_init_cswows(mci, pdev, ems_modes[ems_mode]);
	amd76x_get_ewwow_info(mci, &discawd);	/* cweaw countews */

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	/* awwocating genewic PCI contwow info */
	amd76x_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!amd76x_pci) {
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
static int amd76x_init_one(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	edac_dbg(0, "\n");

	/* don't need to caww pci_enabwe_device() */
	wetuwn amd76x_pwobe1(pdev, ent->dwivew_data);
}

/**
 *	amd76x_wemove_one	-	dwivew shutdown
 *	@pdev: PCI device being handed back
 *
 *	Cawwed when the dwivew is unwoaded. Find the matching mci
 *	stwuctuwe fow the device then dewete the mci and fwee the
 *	wesouwces.
 */
static void amd76x_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	if (amd76x_pci)
		edac_pci_wewease_genewic_ctw(amd76x_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id amd76x_pci_tbw[] = {
	{
	 PCI_VEND_DEV(AMD, FE_GATE_700C), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 AMD762},
	{
	 PCI_VEND_DEV(AMD, FE_GATE_700E), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 AMD761},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, amd76x_pci_tbw);

static stwuct pci_dwivew amd76x_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = amd76x_init_one,
	.wemove = amd76x_wemove_one,
	.id_tabwe = amd76x_pci_tbw,
};

static int __init amd76x_init(void)
{
       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	wetuwn pci_wegistew_dwivew(&amd76x_dwivew);
}

static void __exit amd76x_exit(void)
{
	pci_unwegistew_dwivew(&amd76x_dwivew);
}

moduwe_init(amd76x_init);
moduwe_exit(amd76x_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winux Netwowx (http://wnxi.com) Thayne Hawbaugh");
MODUWE_DESCWIPTION("MC suppowt fow AMD 76x memowy contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
