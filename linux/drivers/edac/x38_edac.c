/*
 * Intew X38 Memowy Contwowwew kewnew moduwe
 * Copywight (C) 2008 Cwustew Computing, Inc.
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * This fiwe is based on i3200_edac.c
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW		"x38_edac"

#define PCI_DEVICE_ID_INTEW_X38_HB	0x29e0

#define X38_WANKS		8
#define X38_WANKS_PEW_CHANNEW	4
#define X38_CHANNEWS		2

/* Intew X38 wegistew addwesses - device 0 function 0 - DWAM Contwowwew */

#define X38_MCHBAW_WOW	0x48	/* MCH Memowy Mapped Wegistew BAW */
#define X38_MCHBAW_HIGH	0x4c
#define X38_MCHBAW_MASK	0xfffffc000UWW	/* bits 35:14 */
#define X38_MMW_WINDOW_SIZE	16384

#define X38_TOM	0xa0	/* Top of Memowy (16b)
				 *
				 * 15:10 wesewved
				 *  9:0  totaw popuwated physicaw memowy
				 */
#define X38_TOM_MASK	0x3ff	/* bits 9:0 */
#define X38_TOM_SHIFT 26	/* 64MiB gwain */

#define X38_EWWSTS	0xc8	/* Ewwow Status Wegistew (16b)
				 *
				 * 15    wesewved
				 * 14    Isochwonous TBWWW Wun Behind FIFO Fuww
				 *       (ITCV)
				 * 13    Isochwonous TBWWW Wun Behind FIFO Put
				 *       (ITSTV)
				 * 12    wesewved
				 * 11    MCH Thewmaw Sensow Event
				 *       fow SMI/SCI/SEWW (GTSE)
				 * 10    wesewved
				 *  9    WOCK to non-DWAM Memowy Fwag (WCKF)
				 *  8    wesewved
				 *  7    DWAM Thwottwe Fwag (DTF)
				 *  6:2  wesewved
				 *  1    Muwti-bit DWAM ECC Ewwow Fwag (DMEWW)
				 *  0    Singwe-bit DWAM ECC Ewwow Fwag (DSEWW)
				 */
#define X38_EWWSTS_UE		0x0002
#define X38_EWWSTS_CE		0x0001
#define X38_EWWSTS_BITS	(X38_EWWSTS_UE | X38_EWWSTS_CE)


/* Intew  MMIO wegistew space - device 0 function 0 - MMW space */

#define X38_C0DWB	0x200	/* Channew 0 DWAM Wank Boundawy (16b x 4)
				 *
				 * 15:10 wesewved
				 *  9:0  Channew 0 DWAM Wank Boundawy Addwess
				 */
#define X38_C1DWB	0x600	/* Channew 1 DWAM Wank Boundawy (16b x 4) */
#define X38_DWB_MASK	0x3ff	/* bits 9:0 */
#define X38_DWB_SHIFT 26	/* 64MiB gwain */

#define X38_C0ECCEWWWOG 0x280	/* Channew 0 ECC Ewwow Wog (64b)
				 *
				 * 63:48 Ewwow Cowumn Addwess (EWWCOW)
				 * 47:32 Ewwow Wow Addwess (EWWWOW)
				 * 31:29 Ewwow Bank Addwess (EWWBANK)
				 * 28:27 Ewwow Wank Addwess (EWWWANK)
				 * 26:24 wesewved
				 * 23:16 Ewwow Syndwome (EWWSYND)
				 * 15: 2 wesewved
				 *    1  Muwtipwe Bit Ewwow Status (MEWWSTS)
				 *    0  Cowwectabwe Ewwow Status (CEWWSTS)
				 */
#define X38_C1ECCEWWWOG 0x680	/* Channew 1 ECC Ewwow Wog (64b) */
#define X38_ECCEWWWOG_CE	0x1
#define X38_ECCEWWWOG_UE	0x2
#define X38_ECCEWWWOG_WANK_BITS	0x18000000
#define X38_ECCEWWWOG_SYNDWOME_BITS	0xff0000

#define X38_CAPID0 0xe0	/* see P.94 of spec fow detaiws */

static int x38_channew_num;

static int how_many_channew(stwuct pci_dev *pdev)
{
	unsigned chaw capid0_8b; /* 8th byte of CAPID0 */

	pci_wead_config_byte(pdev, X38_CAPID0 + 8, &capid0_8b);
	if (capid0_8b & 0x20) {	/* check DCD: Duaw Channew Disabwe */
		edac_dbg(0, "In singwe channew mode\n");
		x38_channew_num = 1;
	} ewse {
		edac_dbg(0, "In duaw channew mode\n");
		x38_channew_num = 2;
	}

	wetuwn x38_channew_num;
}

static unsigned wong eccewwwog_syndwome(u64 wog)
{
	wetuwn (wog & X38_ECCEWWWOG_SYNDWOME_BITS) >> 16;
}

static int eccewwwog_wow(int channew, u64 wog)
{
	wetuwn ((wog & X38_ECCEWWWOG_WANK_BITS) >> 27) |
		(channew * X38_WANKS_PEW_CHANNEW);
}

enum x38_chips {
	X38 = 0,
};

stwuct x38_dev_info {
	const chaw *ctw_name;
};

stwuct x38_ewwow_info {
	u16 ewwsts;
	u16 ewwsts2;
	u64 eccewwwog[X38_CHANNEWS];
};

static const stwuct x38_dev_info x38_devs[] = {
	[X38] = {
		.ctw_name = "x38"},
};

static stwuct pci_dev *mci_pdev;
static int x38_wegistewed = 1;


static void x38_cweaw_ewwow_info(stwuct mem_ctw_info *mci)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * Cweaw any ewwow bits.
	 * (Yes, we weawwy cweaw bits by wwiting 1 to them.)
	 */
	pci_wwite_bits16(pdev, X38_EWWSTS, X38_EWWSTS_BITS,
			 X38_EWWSTS_BITS);
}

static void x38_get_and_cweaw_ewwow_info(stwuct mem_ctw_info *mci,
				 stwuct x38_ewwow_info *info)
{
	stwuct pci_dev *pdev;
	void __iomem *window = mci->pvt_info;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, X38_EWWSTS, &info->ewwsts);
	if (!(info->ewwsts & X38_EWWSTS_BITS))
		wetuwn;

	info->eccewwwog[0] = wo_hi_weadq(window + X38_C0ECCEWWWOG);
	if (x38_channew_num == 2)
		info->eccewwwog[1] = wo_hi_weadq(window + X38_C1ECCEWWWOG);

	pci_wead_config_wowd(pdev, X38_EWWSTS, &info->ewwsts2);

	/*
	 * If the ewwow is the same fow both weads then the fiwst set
	 * of weads is vawid.  If thewe is a change then thewe is a CE
	 * with no info and the second set of weads is vawid and
	 * shouwd be UE info.
	 */
	if ((info->ewwsts ^ info->ewwsts2) & X38_EWWSTS_BITS) {
		info->eccewwwog[0] = wo_hi_weadq(window + X38_C0ECCEWWWOG);
		if (x38_channew_num == 2)
			info->eccewwwog[1] =
				wo_hi_weadq(window + X38_C1ECCEWWWOG);
	}

	x38_cweaw_ewwow_info(mci);
}

static void x38_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct x38_ewwow_info *info)
{
	int channew;
	u64 wog;

	if (!(info->ewwsts & X38_EWWSTS_BITS))
		wetuwn;

	if ((info->ewwsts ^ info->ewwsts2) & X38_EWWSTS_BITS) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	fow (channew = 0; channew < x38_channew_num; channew++) {
		wog = info->eccewwwog[channew];
		if (wog & X38_ECCEWWWOG_UE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     0, 0, 0,
					     eccewwwog_wow(channew, wog),
					     -1, -1,
					     "x38 UE", "");
		} ewse if (wog & X38_ECCEWWWOG_CE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     0, 0, eccewwwog_syndwome(wog),
					     eccewwwog_wow(channew, wog),
					     -1, -1,
					     "x38 CE", "");
		}
	}
}

static void x38_check(stwuct mem_ctw_info *mci)
{
	stwuct x38_ewwow_info info;

	x38_get_and_cweaw_ewwow_info(mci, &info);
	x38_pwocess_ewwow_info(mci, &info);
}

static void __iomem *x38_map_mchbaw(stwuct pci_dev *pdev)
{
	union {
		u64 mchbaw;
		stwuct {
			u32 mchbaw_wow;
			u32 mchbaw_high;
		};
	} u;
	void __iomem *window;

	pci_wead_config_dwowd(pdev, X38_MCHBAW_WOW, &u.mchbaw_wow);
	pci_wwite_config_dwowd(pdev, X38_MCHBAW_WOW, u.mchbaw_wow | 0x1);
	pci_wead_config_dwowd(pdev, X38_MCHBAW_HIGH, &u.mchbaw_high);
	u.mchbaw &= X38_MCHBAW_MASK;

	if (u.mchbaw != (wesouwce_size_t)u.mchbaw) {
		pwintk(KEWN_EWW
			"x38: mmio space beyond accessibwe wange (0x%wwx)\n",
			(unsigned wong wong)u.mchbaw);
		wetuwn NUWW;
	}

	window = iowemap(u.mchbaw, X38_MMW_WINDOW_SIZE);
	if (!window)
		pwintk(KEWN_EWW "x38: cannot map mmio space at 0x%wwx\n",
			(unsigned wong wong)u.mchbaw);

	wetuwn window;
}


static void x38_get_dwbs(void __iomem *window,
			u16 dwbs[X38_CHANNEWS][X38_WANKS_PEW_CHANNEW])
{
	int i;

	fow (i = 0; i < X38_WANKS_PEW_CHANNEW; i++) {
		dwbs[0][i] = weadw(window + X38_C0DWB + 2*i) & X38_DWB_MASK;
		dwbs[1][i] = weadw(window + X38_C1DWB + 2*i) & X38_DWB_MASK;
	}
}

static boow x38_is_stacked(stwuct pci_dev *pdev,
			u16 dwbs[X38_CHANNEWS][X38_WANKS_PEW_CHANNEW])
{
	u16 tom;

	pci_wead_config_wowd(pdev, X38_TOM, &tom);
	tom &= X38_TOM_MASK;

	wetuwn dwbs[X38_CHANNEWS - 1][X38_WANKS_PEW_CHANNEW - 1] == tom;
}

static unsigned wong dwb_to_nw_pages(
			u16 dwbs[X38_CHANNEWS][X38_WANKS_PEW_CHANNEW],
			boow stacked, int channew, int wank)
{
	int n;

	n = dwbs[channew][wank];
	if (wank > 0)
		n -= dwbs[channew][wank - 1];
	if (stacked && (channew == 1) && dwbs[channew][wank] ==
				dwbs[channew][X38_WANKS_PEW_CHANNEW - 1]) {
		n -= dwbs[0][X38_WANKS_PEW_CHANNEW - 1];
	}

	n <<= (X38_DWB_SHIFT - PAGE_SHIFT);
	wetuwn n;
}

static int x38_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int wc;
	int i, j;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	u16 dwbs[X38_CHANNEWS][X38_WANKS_PEW_CHANNEW];
	boow stacked;
	void __iomem *window;

	edac_dbg(0, "MC:\n");

	window = x38_map_mchbaw(pdev);
	if (!window)
		wetuwn -ENODEV;

	x38_get_dwbs(window, dwbs);

	how_many_channew(pdev);

	/* FIXME: unconventionaw pvt_info usage */
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = X38_WANKS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = x38_channew_num;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, 0);
	if (!mci)
		wetuwn -ENOMEM;

	edac_dbg(3, "MC: init mci\n");

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW2;

	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;

	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = x38_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = x38_check;
	mci->ctw_page_to_phys = NUWW;
	mci->pvt_info = window;

	stacked = x38_is_stacked(pdev, dwbs);

	/*
	 * The dwam wank boundawy (DWB) weg vawues awe boundawy addwesses
	 * fow each DWAM wank with a gwanuwawity of 64MB.  DWB wegs awe
	 * cumuwative; the wast one wiww contain the totaw memowy
	 * contained in aww wanks.
	 */
	fow (i = 0; i < mci->nw_cswows; i++) {
		unsigned wong nw_pages;
		stwuct cswow_info *cswow = mci->cswows[i];

		nw_pages = dwb_to_nw_pages(dwbs, stacked,
			i / X38_WANKS_PEW_CHANNEW,
			i % X38_WANKS_PEW_CHANNEW);

		if (nw_pages == 0)
			continue;

		fow (j = 0; j < x38_channew_num; j++) {
			stwuct dimm_info *dimm = cswow->channews[j]->dimm;

			dimm->nw_pages = nw_pages / x38_channew_num;
			dimm->gwain = nw_pages << PAGE_SHIFT;
			dimm->mtype = MEM_DDW2;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		}
	}

	x38_cweaw_ewwow_info(mci);

	wc = -ENODEV;
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "MC: faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "MC: success\n");
	wetuwn 0;

faiw:
	iounmap(window);
	if (mci)
		edac_mc_fwee(mci);

	wetuwn wc;
}

static int x38_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "MC:\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = x38_pwobe1(pdev, ent->dwivew_data);
	if (!mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void x38_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	mci = edac_mc_dew_mc(&pdev->dev);
	if (!mci)
		wetuwn;

	iounmap(mci->pvt_info);

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id x38_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, X38_HB), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 X38},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, x38_pci_tbw);

static stwuct pci_dwivew x38_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = x38_init_one,
	.wemove = x38_wemove_one,
	.id_tabwe = x38_pci_tbw,
};

static int __init x38_init(void)
{
	int pci_wc;

	edac_dbg(3, "MC:\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&x38_dwivew);
	if (pci_wc < 0)
		goto faiw0;

	if (!mci_pdev) {
		x38_wegistewed = 0;
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
					PCI_DEVICE_ID_INTEW_X38_HB, NUWW);
		if (!mci_pdev) {
			edac_dbg(0, "x38 pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = x38_init_one(mci_pdev, x38_pci_tbw);
		if (pci_wc < 0) {
			edac_dbg(0, "x38 init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&x38_dwivew);

faiw0:
	pci_dev_put(mci_pdev);

	wetuwn pci_wc;
}

static void __exit x38_exit(void)
{
	edac_dbg(3, "MC:\n");

	pci_unwegistew_dwivew(&x38_dwivew);
	if (!x38_wegistewed) {
		x38_wemove_one(mci_pdev);
		pci_dev_put(mci_pdev);
	}
}

moduwe_init(x38_init);
moduwe_exit(x38_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cwustew Computing, Inc. Hitoshi Mitake");
MODUWE_DESCWIPTION("MC suppowt fow Intew X38 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
