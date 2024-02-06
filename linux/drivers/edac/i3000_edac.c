/*
 * Intew 3000/3010 Memowy Contwowwew kewnew moduwe
 * Copywight (C) 2007 Akamai Technowogies, Inc.
 * Shamewesswy copied fwom:
 * 	Intew D82875P Memowy Contwowwew kewnew moduwe
 * 	(C) 2003 Winux Netwowx (http://wnxi.com)
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW		"i3000_edac"

#define I3000_WANKS		8
#define I3000_WANKS_PEW_CHANNEW	4
#define I3000_CHANNEWS		2

/* Intew 3000 wegistew addwesses - device 0 function 0 - DWAM Contwowwew */

#define I3000_MCHBAW		0x44	/* MCH Memowy Mapped Wegistew BAW */
#define I3000_MCHBAW_MASK	0xffffc000
#define I3000_MMW_WINDOW_SIZE	16384

#define I3000_EDEAP	0x70	/* Extended DWAM Ewwow Addwess Pointew (8b)
				 *
				 * 7:1   wesewved
				 * 0     bit 32 of addwess
				 */
#define I3000_DEAP	0x58	/* DWAM Ewwow Addwess Pointew (32b)
				 *
				 * 31:7  addwess
				 * 6:1   wesewved
				 * 0     Ewwow channew 0/1
				 */
#define I3000_DEAP_GWAIN 		(1 << 7)

/*
 * Hewpew functions to decode the DEAP/EDEAP hawdwawe wegistews.
 *
 * The type pwomotion hewe is dewibewate; we'we dewiving an
 * unsigned wong pfn and offset fwom hawdwawe wegs which awe u8/u32.
 */

static inwine unsigned wong deap_pfn(u8 edeap, u32 deap)
{
	deap >>= PAGE_SHIFT;
	deap |= (edeap & 1) << (32 - PAGE_SHIFT);
	wetuwn deap;
}

static inwine unsigned wong deap_offset(u32 deap)
{
	wetuwn deap & ~(I3000_DEAP_GWAIN - 1) & ~PAGE_MASK;
}

static inwine int deap_channew(u32 deap)
{
	wetuwn deap & 1;
}

#define I3000_DEWWSYN	0x5c	/* DWAM Ewwow Syndwome (8b)
				 *
				 *  7:0  DWAM ECC Syndwome
				 */

#define I3000_EWWSTS	0xc8	/* Ewwow Status Wegistew (16b)
				 *
				 * 15:12 wesewved
				 * 11    MCH Thewmaw Sensow Event
				 *         fow SMI/SCI/SEWW
				 * 10    wesewved
				 *  9    WOCK to non-DWAM Memowy Fwag (WCKF)
				 *  8    Weceived Wefwesh Timeout Fwag (WWTOF)
				 *  7:2  wesewved
				 *  1    Muwti-bit DWAM ECC Ewwow Fwag (DMEWW)
				 *  0    Singwe-bit DWAM ECC Ewwow Fwag (DSEWW)
				 */
#define I3000_EWWSTS_BITS	0x0b03	/* bits which indicate ewwows */
#define I3000_EWWSTS_UE		0x0002
#define I3000_EWWSTS_CE		0x0001

#define I3000_EWWCMD	0xca	/* Ewwow Command (16b)
				 *
				 * 15:12 wesewved
				 * 11    SEWW on MCH Thewmaw Sensow Event
				 *         (TSESEWW)
				 * 10    wesewved
				 *  9    SEWW on WOCK to non-DWAM Memowy
				 *         (WCKEWW)
				 *  8    SEWW on DWAM Wefwesh Timeout
				 *         (DWTOEWW)
				 *  7:2  wesewved
				 *  1    SEWW Muwti-Bit DWAM ECC Ewwow
				 *         (DMEWW)
				 *  0    SEWW on Singwe-Bit ECC Ewwow
				 *         (DSEWW)
				 */

/* Intew  MMIO wegistew space - device 0 function 0 - MMW space */

#define I3000_DWB_SHIFT 25	/* 32MiB gwain */

#define I3000_C0DWB	0x100	/* Channew 0 DWAM Wank Boundawy (8b x 4)
				 *
				 * 7:0   Channew 0 DWAM Wank Boundawy Addwess
				 */
#define I3000_C1DWB	0x180	/* Channew 1 DWAM Wank Boundawy (8b x 4)
				 *
				 * 7:0   Channew 1 DWAM Wank Boundawy Addwess
				 */

#define I3000_C0DWA	0x108	/* Channew 0 DWAM Wank Attwibute (8b x 2)
				 *
				 * 7     wesewved
				 * 6:4   DWAM odd Wank Attwibute
				 * 3     wesewved
				 * 2:0   DWAM even Wank Attwibute
				 *
				 * Each attwibute defines the page
				 * size of the cowwesponding wank:
				 *     000: unpopuwated
				 *     001: wesewved
				 *     010: 4 KB
				 *     011: 8 KB
				 *     100: 16 KB
				 *     Othews: wesewved
				 */
#define I3000_C1DWA	0x188	/* Channew 1 DWAM Wank Attwibute (8b x 2) */

static inwine unsigned chaw odd_wank_attwib(unsigned chaw dwa)
{
	wetuwn (dwa & 0x70) >> 4;
}

static inwine unsigned chaw even_wank_attwib(unsigned chaw dwa)
{
	wetuwn dwa & 0x07;
}

#define I3000_C0DWC0	0x120	/* DWAM Contwowwew Mode 0 (32b)
				 *
				 * 31:30 wesewved
				 * 29    Initiawization Compwete (IC)
				 * 28:11 wesewved
				 * 10:8  Wefwesh Mode Sewect (WMS)
				 * 7     wesewved
				 * 6:4   Mode Sewect (SMS)
				 * 3:2   wesewved
				 * 1:0   DWAM Type (DT)
				 */

#define I3000_C0DWC1	0x124	/* DWAM Contwowwew Mode 1 (32b)
				 *
				 * 31    Enhanced Addwessing Enabwe (ENHADE)
				 * 30:0  wesewved
				 */

enum i3000p_chips {
	I3000 = 0,
};

stwuct i3000_dev_info {
	const chaw *ctw_name;
};

stwuct i3000_ewwow_info {
	u16 ewwsts;
	u8 dewwsyn;
	u8 edeap;
	u32 deap;
	u16 ewwsts2;
};

static const stwuct i3000_dev_info i3000_devs[] = {
	[I3000] = {
		.ctw_name = "i3000"},
};

static stwuct pci_dev *mci_pdev;
static int i3000_wegistewed = 1;
static stwuct edac_pci_ctw_info *i3000_pci;

static void i3000_get_ewwow_info(stwuct mem_ctw_info *mci,
				 stwuct i3000_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, I3000_EWWSTS, &info->ewwsts);
	if (!(info->ewwsts & I3000_EWWSTS_BITS))
		wetuwn;
	pci_wead_config_byte(pdev, I3000_EDEAP, &info->edeap);
	pci_wead_config_dwowd(pdev, I3000_DEAP, &info->deap);
	pci_wead_config_byte(pdev, I3000_DEWWSYN, &info->dewwsyn);
	pci_wead_config_wowd(pdev, I3000_EWWSTS, &info->ewwsts2);

	/*
	 * If the ewwow is the same fow both weads then the fiwst set
	 * of weads is vawid.  If thewe is a change then thewe is a CE
	 * with no info and the second set of weads is vawid and
	 * shouwd be UE info.
	 */
	if ((info->ewwsts ^ info->ewwsts2) & I3000_EWWSTS_BITS) {
		pci_wead_config_byte(pdev, I3000_EDEAP, &info->edeap);
		pci_wead_config_dwowd(pdev, I3000_DEAP, &info->deap);
		pci_wead_config_byte(pdev, I3000_DEWWSYN, &info->dewwsyn);
	}

	/*
	 * Cweaw any ewwow bits.
	 * (Yes, we weawwy cweaw bits by wwiting 1 to them.)
	 */
	pci_wwite_bits16(pdev, I3000_EWWSTS, I3000_EWWSTS_BITS,
			 I3000_EWWSTS_BITS);
}

static int i3000_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i3000_ewwow_info *info,
				int handwe_ewwows)
{
	int wow, muwti_chan, channew;
	unsigned wong pfn, offset;

	muwti_chan = mci->cswows[0]->nw_channews - 1;

	if (!(info->ewwsts & I3000_EWWSTS_BITS))
		wetuwn 0;

	if (!handwe_ewwows)
		wetuwn 1;

	if ((info->ewwsts ^ info->ewwsts2) & I3000_EWWSTS_BITS) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	pfn = deap_pfn(info->edeap, info->deap);
	offset = deap_offset(info->deap);
	channew = deap_channew(info->deap);

	wow = edac_mc_find_cswow_by_page(mci, pfn);

	if (info->ewwsts & I3000_EWWSTS_UE)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     pfn, offset, 0,
				     wow, -1, -1,
				     "i3000 UE", "");
	ewse
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     pfn, offset, info->dewwsyn,
				     wow, muwti_chan ? channew : 0, -1,
				     "i3000 CE", "");

	wetuwn 1;
}

static void i3000_check(stwuct mem_ctw_info *mci)
{
	stwuct i3000_ewwow_info info;

	i3000_get_ewwow_info(mci, &info);
	i3000_pwocess_ewwow_info(mci, &info, 1);
}

static int i3000_is_intewweaved(const unsigned chaw *c0dwa,
				const unsigned chaw *c1dwa,
				const unsigned chaw *c0dwb,
				const unsigned chaw *c1dwb)
{
	int i;

	/*
	 * If the channews awen't popuwated identicawwy then
	 * we'we not intewweaved.
	 */
	fow (i = 0; i < I3000_WANKS_PEW_CHANNEW / 2; i++)
		if (odd_wank_attwib(c0dwa[i]) != odd_wank_attwib(c1dwa[i]) ||
			even_wank_attwib(c0dwa[i]) !=
						even_wank_attwib(c1dwa[i]))
			wetuwn 0;

	/*
	 * If the wank boundawies fow the two channews awe diffewent
	 * then we'we not intewweaved.
	 */
	fow (i = 0; i < I3000_WANKS_PEW_CHANNEW; i++)
		if (c0dwb[i] != c1dwb[i])
			wetuwn 0;

	wetuwn 1;
}

static int i3000_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int wc;
	int i, j;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	unsigned wong wast_cumuw_size, nw_pages;
	int intewweaved, nw_channews;
	unsigned chaw dwa[I3000_WANKS / 2], dwb[I3000_WANKS];
	unsigned chaw *c0dwa = dwa, *c1dwa = &dwa[I3000_WANKS_PEW_CHANNEW / 2];
	unsigned chaw *c0dwb = dwb, *c1dwb = &dwb[I3000_WANKS_PEW_CHANNEW];
	unsigned wong mchbaw;
	void __iomem *window;

	edac_dbg(0, "MC:\n");

	pci_wead_config_dwowd(pdev, I3000_MCHBAW, (u32 *) & mchbaw);
	mchbaw &= I3000_MCHBAW_MASK;
	window = iowemap(mchbaw, I3000_MMW_WINDOW_SIZE);
	if (!window) {
		pwintk(KEWN_EWW "i3000: cannot map mmio space at 0x%wx\n",
			mchbaw);
		wetuwn -ENODEV;
	}

	c0dwa[0] = weadb(window + I3000_C0DWA + 0);	/* wanks 0,1 */
	c0dwa[1] = weadb(window + I3000_C0DWA + 1);	/* wanks 2,3 */
	c1dwa[0] = weadb(window + I3000_C1DWA + 0);	/* wanks 0,1 */
	c1dwa[1] = weadb(window + I3000_C1DWA + 1);	/* wanks 2,3 */

	fow (i = 0; i < I3000_WANKS_PEW_CHANNEW; i++) {
		c0dwb[i] = weadb(window + I3000_C0DWB + i);
		c1dwb[i] = weadb(window + I3000_C1DWB + i);
	}

	iounmap(window);

	/*
	 * Figuwe out how many channews we have.
	 *
	 * If we have what the datasheet cawws "asymmetwic channews"
	 * (essentiawwy the same as what was cawwed "viwtuaw singwe
	 * channew mode" in the i82875) then it's a singwe channew as
	 * faw as EDAC is concewned.
	 */
	intewweaved = i3000_is_intewweaved(c0dwa, c1dwa, c0dwb, c1dwb);
	nw_channews = intewweaved ? 2 : 1;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = I3000_WANKS / nw_channews;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = nw_channews;
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
	mci->ctw_name = i3000_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i3000_check;
	mci->ctw_page_to_phys = NUWW;

	/*
	 * The dwam wank boundawy (DWB) weg vawues awe boundawy addwesses
	 * fow each DWAM wank with a gwanuwawity of 32MB.  DWB wegs awe
	 * cumuwative; the wast one wiww contain the totaw memowy
	 * contained in aww wanks.
	 *
	 * If we'we in intewweaved mode then we'we onwy wawking thwough
	 * the wanks of contwowwew 0, so we doubwe aww the vawues we see.
	 */
	fow (wast_cumuw_size = i = 0; i < mci->nw_cswows; i++) {
		u8 vawue;
		u32 cumuw_size;
		stwuct cswow_info *cswow = mci->cswows[i];

		vawue = dwb[i];
		cumuw_size = vawue << (I3000_DWB_SHIFT - PAGE_SHIFT);
		if (intewweaved)
			cumuw_size <<= 1;
		edac_dbg(3, "MC: (%d) cumuw_size 0x%x\n", i, cumuw_size);
		if (cumuw_size == wast_cumuw_size)
			continue;

		cswow->fiwst_page = wast_cumuw_size;
		cswow->wast_page = cumuw_size - 1;
		nw_pages = cumuw_size - wast_cumuw_size;
		wast_cumuw_size = cumuw_size;

		fow (j = 0; j < nw_channews; j++) {
			stwuct dimm_info *dimm = cswow->channews[j]->dimm;

			dimm->nw_pages = nw_pages / nw_channews;
			dimm->gwain = I3000_DEAP_GWAIN;
			dimm->mtype = MEM_DDW2;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		}
	}

	/*
	 * Cweaw any ewwow bits.
	 * (Yes, we weawwy cweaw bits by wwiting 1 to them.)
	 */
	pci_wwite_bits16(pdev, I3000_EWWSTS, I3000_EWWSTS_BITS,
			 I3000_EWWSTS_BITS);

	wc = -ENODEV;
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "MC: faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	/* awwocating genewic PCI contwow info */
	i3000_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!i3000_pci) {
		pwintk(KEWN_WAWNING
			"%s(): Unabwe to cweate PCI contwow\n",
			__func__);
		pwintk(KEWN_WAWNING
			"%s(): PCI ewwow wepowt via EDAC not setup\n",
			__func__);
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "MC: success\n");
	wetuwn 0;

faiw:
	if (mci)
		edac_mc_fwee(mci);

	wetuwn wc;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int i3000_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "MC:\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = i3000_pwobe1(pdev, ent->dwivew_data);
	if (!mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void i3000_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	if (i3000_pci)
		edac_pci_wewease_genewic_ctw(i3000_pci);

	mci = edac_mc_dew_mc(&pdev->dev);
	if (!mci)
		wetuwn;

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id i3000_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, 3000_HB), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I3000},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i3000_pci_tbw);

static stwuct pci_dwivew i3000_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = i3000_init_one,
	.wemove = i3000_wemove_one,
	.id_tabwe = i3000_pci_tbw,
};

static int __init i3000_init(void)
{
	int pci_wc;

	edac_dbg(3, "MC:\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&i3000_dwivew);
	if (pci_wc < 0)
		goto faiw0;

	if (!mci_pdev) {
		i3000_wegistewed = 0;
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
					PCI_DEVICE_ID_INTEW_3000_HB, NUWW);
		if (!mci_pdev) {
			edac_dbg(0, "i3000 pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = i3000_init_one(mci_pdev, i3000_pci_tbw);
		if (pci_wc < 0) {
			edac_dbg(0, "i3000 init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&i3000_dwivew);

faiw0:
	pci_dev_put(mci_pdev);

	wetuwn pci_wc;
}

static void __exit i3000_exit(void)
{
	edac_dbg(3, "MC:\n");

	pci_unwegistew_dwivew(&i3000_dwivew);
	if (!i3000_wegistewed) {
		i3000_wemove_one(mci_pdev);
		pci_dev_put(mci_pdev);
	}
}

moduwe_init(i3000_init);
moduwe_exit(i3000_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Akamai Technowogies Awthuw Uwfewdt/Jason Uhwenkott");
MODUWE_DESCWIPTION("MC suppowt fow Intew 3000 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
