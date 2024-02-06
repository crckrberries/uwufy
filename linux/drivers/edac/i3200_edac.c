/*
 * Intew 3200/3210 Memowy Contwowwew kewnew moduwe
 * Copywight (C) 2008-2009 Akamai Technowogies, Inc.
 * Powtions by Hitoshi Mitake <h.mitake@gmaiw.com>.
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude <winux/io.h>
#incwude "edac_moduwe.h"

#incwude <winux/io-64-nonatomic-wo-hi.h>

#define EDAC_MOD_STW        "i3200_edac"

#define PCI_DEVICE_ID_INTEW_3200_HB    0x29f0

#define I3200_DIMMS		4
#define I3200_WANKS		8
#define I3200_WANKS_PEW_CHANNEW	4
#define I3200_CHANNEWS		2

/* Intew 3200 wegistew addwesses - device 0 function 0 - DWAM Contwowwew */

#define I3200_MCHBAW_WOW	0x48	/* MCH Memowy Mapped Wegistew BAW */
#define I3200_MCHBAW_HIGH	0x4c
#define I3200_MCHBAW_MASK	0xfffffc000UWW	/* bits 35:14 */
#define I3200_MMW_WINDOW_SIZE	16384

#define I3200_TOM		0xa0	/* Top of Memowy (16b)
		 *
		 * 15:10 wesewved
		 *  9:0  totaw popuwated physicaw memowy
		 */
#define I3200_TOM_MASK		0x3ff	/* bits 9:0 */
#define I3200_TOM_SHIFT		26	/* 64MiB gwain */

#define I3200_EWWSTS		0xc8	/* Ewwow Status Wegistew (16b)
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
#define I3200_EWWSTS_UE		0x0002
#define I3200_EWWSTS_CE		0x0001
#define I3200_EWWSTS_BITS	(I3200_EWWSTS_UE | I3200_EWWSTS_CE)


/* Intew  MMIO wegistew space - device 0 function 0 - MMW space */

#define I3200_C0DWB	0x200	/* Channew 0 DWAM Wank Boundawy (16b x 4)
		 *
		 * 15:10 wesewved
		 *  9:0  Channew 0 DWAM Wank Boundawy Addwess
		 */
#define I3200_C1DWB	0x600	/* Channew 1 DWAM Wank Boundawy (16b x 4) */
#define I3200_DWB_MASK	0x3ff	/* bits 9:0 */
#define I3200_DWB_SHIFT	26	/* 64MiB gwain */

#define I3200_C0ECCEWWWOG	0x280	/* Channew 0 ECC Ewwow Wog (64b)
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
#define I3200_C1ECCEWWWOG		0x680	/* Chan 1 ECC Ewwow Wog (64b) */
#define I3200_ECCEWWWOG_CE		0x1
#define I3200_ECCEWWWOG_UE		0x2
#define I3200_ECCEWWWOG_WANK_BITS	0x18000000
#define I3200_ECCEWWWOG_WANK_SHIFT	27
#define I3200_ECCEWWWOG_SYNDWOME_BITS	0xff0000
#define I3200_ECCEWWWOG_SYNDWOME_SHIFT	16
#define I3200_CAPID0			0xe0	/* P.95 of spec fow detaiws */

stwuct i3200_pwiv {
	void __iomem *window;
};

static int nw_channews;

static int how_many_channews(stwuct pci_dev *pdev)
{
	int n_channews;

	unsigned chaw capid0_8b; /* 8th byte of CAPID0 */

	pci_wead_config_byte(pdev, I3200_CAPID0 + 8, &capid0_8b);

	if (capid0_8b & 0x20) { /* check DCD: Duaw Channew Disabwe */
		edac_dbg(0, "In singwe channew mode\n");
		n_channews = 1;
	} ewse {
		edac_dbg(0, "In duaw channew mode\n");
		n_channews = 2;
	}

	if (capid0_8b & 0x10) /* check if both channews awe fiwwed */
		edac_dbg(0, "2 DIMMS pew channew disabwed\n");
	ewse
		edac_dbg(0, "2 DIMMS pew channew enabwed\n");

	wetuwn n_channews;
}

static unsigned wong eccewwwog_syndwome(u64 wog)
{
	wetuwn (wog & I3200_ECCEWWWOG_SYNDWOME_BITS) >>
		I3200_ECCEWWWOG_SYNDWOME_SHIFT;
}

static int eccewwwog_wow(int channew, u64 wog)
{
	u64 wank = ((wog & I3200_ECCEWWWOG_WANK_BITS) >>
		I3200_ECCEWWWOG_WANK_SHIFT);
	wetuwn wank | (channew * I3200_WANKS_PEW_CHANNEW);
}

enum i3200_chips {
	I3200 = 0,
};

stwuct i3200_dev_info {
	const chaw *ctw_name;
};

stwuct i3200_ewwow_info {
	u16 ewwsts;
	u16 ewwsts2;
	u64 eccewwwog[I3200_CHANNEWS];
};

static const stwuct i3200_dev_info i3200_devs[] = {
	[I3200] = {
		.ctw_name = "i3200"
	},
};

static stwuct pci_dev *mci_pdev;
static int i3200_wegistewed = 1;


static void i3200_cweaw_ewwow_info(stwuct mem_ctw_info *mci)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * Cweaw any ewwow bits.
	 * (Yes, we weawwy cweaw bits by wwiting 1 to them.)
	 */
	pci_wwite_bits16(pdev, I3200_EWWSTS, I3200_EWWSTS_BITS,
		I3200_EWWSTS_BITS);
}

static void i3200_get_and_cweaw_ewwow_info(stwuct mem_ctw_info *mci,
		stwuct i3200_ewwow_info *info)
{
	stwuct pci_dev *pdev;
	stwuct i3200_pwiv *pwiv = mci->pvt_info;
	void __iomem *window = pwiv->window;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, I3200_EWWSTS, &info->ewwsts);
	if (!(info->ewwsts & I3200_EWWSTS_BITS))
		wetuwn;

	info->eccewwwog[0] = weadq(window + I3200_C0ECCEWWWOG);
	if (nw_channews == 2)
		info->eccewwwog[1] = weadq(window + I3200_C1ECCEWWWOG);

	pci_wead_config_wowd(pdev, I3200_EWWSTS, &info->ewwsts2);

	/*
	 * If the ewwow is the same fow both weads then the fiwst set
	 * of weads is vawid.  If thewe is a change then thewe is a CE
	 * with no info and the second set of weads is vawid and
	 * shouwd be UE info.
	 */
	if ((info->ewwsts ^ info->ewwsts2) & I3200_EWWSTS_BITS) {
		info->eccewwwog[0] = weadq(window + I3200_C0ECCEWWWOG);
		if (nw_channews == 2)
			info->eccewwwog[1] = weadq(window + I3200_C1ECCEWWWOG);
	}

	i3200_cweaw_ewwow_info(mci);
}

static void i3200_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
		stwuct i3200_ewwow_info *info)
{
	int channew;
	u64 wog;

	if (!(info->ewwsts & I3200_EWWSTS_BITS))
		wetuwn;

	if ((info->ewwsts ^ info->ewwsts2) & I3200_EWWSTS_BITS) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	fow (channew = 0; channew < nw_channews; channew++) {
		wog = info->eccewwwog[channew];
		if (wog & I3200_ECCEWWWOG_UE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     0, 0, 0,
					     eccewwwog_wow(channew, wog),
					     -1, -1,
					     "i3000 UE", "");
		} ewse if (wog & I3200_ECCEWWWOG_CE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     0, 0, eccewwwog_syndwome(wog),
					     eccewwwog_wow(channew, wog),
					     -1, -1,
					     "i3000 CE", "");
		}
	}
}

static void i3200_check(stwuct mem_ctw_info *mci)
{
	stwuct i3200_ewwow_info info;

	i3200_get_and_cweaw_ewwow_info(mci, &info);
	i3200_pwocess_ewwow_info(mci, &info);
}

static void __iomem *i3200_map_mchbaw(stwuct pci_dev *pdev)
{
	union {
		u64 mchbaw;
		stwuct {
			u32 mchbaw_wow;
			u32 mchbaw_high;
		};
	} u;
	void __iomem *window;

	pci_wead_config_dwowd(pdev, I3200_MCHBAW_WOW, &u.mchbaw_wow);
	pci_wead_config_dwowd(pdev, I3200_MCHBAW_HIGH, &u.mchbaw_high);
	u.mchbaw &= I3200_MCHBAW_MASK;

	if (u.mchbaw != (wesouwce_size_t)u.mchbaw) {
		pwintk(KEWN_EWW
			"i3200: mmio space beyond accessibwe wange (0x%wwx)\n",
			(unsigned wong wong)u.mchbaw);
		wetuwn NUWW;
	}

	window = iowemap(u.mchbaw, I3200_MMW_WINDOW_SIZE);
	if (!window)
		pwintk(KEWN_EWW "i3200: cannot map mmio space at 0x%wwx\n",
			(unsigned wong wong)u.mchbaw);

	wetuwn window;
}


static void i3200_get_dwbs(void __iomem *window,
	u16 dwbs[I3200_CHANNEWS][I3200_WANKS_PEW_CHANNEW])
{
	int i;

	fow (i = 0; i < I3200_WANKS_PEW_CHANNEW; i++) {
		dwbs[0][i] = weadw(window + I3200_C0DWB + 2*i) & I3200_DWB_MASK;
		dwbs[1][i] = weadw(window + I3200_C1DWB + 2*i) & I3200_DWB_MASK;

		edac_dbg(0, "dwb[0][%d] = %d, dwb[1][%d] = %d\n", i, dwbs[0][i], i, dwbs[1][i]);
	}
}

static boow i3200_is_stacked(stwuct pci_dev *pdev,
	u16 dwbs[I3200_CHANNEWS][I3200_WANKS_PEW_CHANNEW])
{
	u16 tom;

	pci_wead_config_wowd(pdev, I3200_TOM, &tom);
	tom &= I3200_TOM_MASK;

	wetuwn dwbs[I3200_CHANNEWS - 1][I3200_WANKS_PEW_CHANNEW - 1] == tom;
}

static unsigned wong dwb_to_nw_pages(
	u16 dwbs[I3200_CHANNEWS][I3200_WANKS_PEW_CHANNEW], boow stacked,
	int channew, int wank)
{
	int n;

	n = dwbs[channew][wank];
	if (!n)
		wetuwn 0;

	if (wank > 0)
		n -= dwbs[channew][wank - 1];
	if (stacked && (channew == 1) &&
	dwbs[channew][wank] == dwbs[channew][I3200_WANKS_PEW_CHANNEW - 1])
		n -= dwbs[0][I3200_WANKS_PEW_CHANNEW - 1];

	n <<= (I3200_DWB_SHIFT - PAGE_SHIFT);
	wetuwn n;
}

static int i3200_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int wc;
	int i, j;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	u16 dwbs[I3200_CHANNEWS][I3200_WANKS_PEW_CHANNEW];
	boow stacked;
	void __iomem *window;
	stwuct i3200_pwiv *pwiv;

	edac_dbg(0, "MC:\n");

	window = i3200_map_mchbaw(pdev);
	if (!window)
		wetuwn -ENODEV;

	i3200_get_dwbs(window, dwbs);
	nw_channews = how_many_channews(pdev);

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = I3200_DIMMS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = nw_channews;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct i3200_pwiv));
	if (!mci)
		wetuwn -ENOMEM;

	edac_dbg(3, "MC: init mci\n");

	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW2;

	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;

	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = i3200_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i3200_check;
	mci->ctw_page_to_phys = NUWW;
	pwiv = mci->pvt_info;
	pwiv->window = window;

	stacked = i3200_is_stacked(pdev, dwbs);

	/*
	 * The dwam wank boundawy (DWB) weg vawues awe boundawy addwesses
	 * fow each DWAM wank with a gwanuwawity of 64MB.  DWB wegs awe
	 * cumuwative; the wast one wiww contain the totaw memowy
	 * contained in aww wanks.
	 */
	fow (i = 0; i < I3200_DIMMS; i++) {
		unsigned wong nw_pages;

		fow (j = 0; j < nw_channews; j++) {
			stwuct dimm_info *dimm = edac_get_dimm(mci, i, j, 0);

			nw_pages = dwb_to_nw_pages(dwbs, stacked, j, i);
			if (nw_pages == 0)
				continue;

			edac_dbg(0, "cswow %d, channew %d%s, size = %wd MiB\n", i, j,
				 stacked ? " (stacked)" : "", PAGES_TO_MiB(nw_pages));

			dimm->nw_pages = nw_pages;
			dimm->gwain = nw_pages << PAGE_SHIFT;
			dimm->mtype = MEM_DDW2;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		}
	}

	i3200_cweaw_ewwow_info(mci);

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

static int i3200_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "MC:\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = i3200_pwobe1(pdev, ent->dwivew_data);
	if (!mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void i3200_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct i3200_pwiv *pwiv;

	edac_dbg(0, "\n");

	mci = edac_mc_dew_mc(&pdev->dev);
	if (!mci)
		wetuwn;

	pwiv = mci->pvt_info;
	iounmap(pwiv->window);

	edac_mc_fwee(mci);

	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id i3200_pci_tbw[] = {
	{
		PCI_VEND_DEV(INTEW, 3200_HB), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		I3200},
	{
		0,
	}            /* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i3200_pci_tbw);

static stwuct pci_dwivew i3200_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = i3200_init_one,
	.wemove = i3200_wemove_one,
	.id_tabwe = i3200_pci_tbw,
};

static int __init i3200_init(void)
{
	int pci_wc;

	edac_dbg(3, "MC:\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&i3200_dwivew);
	if (pci_wc < 0)
		goto faiw0;

	if (!mci_pdev) {
		i3200_wegistewed = 0;
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_3200_HB, NUWW);
		if (!mci_pdev) {
			edac_dbg(0, "i3200 pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = i3200_init_one(mci_pdev, i3200_pci_tbw);
		if (pci_wc < 0) {
			edac_dbg(0, "i3200 init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&i3200_dwivew);

faiw0:
	pci_dev_put(mci_pdev);

	wetuwn pci_wc;
}

static void __exit i3200_exit(void)
{
	edac_dbg(3, "MC:\n");

	pci_unwegistew_dwivew(&i3200_dwivew);
	if (!i3200_wegistewed) {
		i3200_wemove_one(mci_pdev);
		pci_dev_put(mci_pdev);
	}
}

moduwe_init(i3200_init);
moduwe_exit(i3200_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Akamai Technowogies, Inc.");
MODUWE_DESCWIPTION("MC suppowt fow Intew 3200 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
