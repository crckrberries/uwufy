// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew E3-1200
 * Copywight (C) 2014 Jason Bawon <jbawon@akamai.com>
 *
 * Suppowt fow the E3-1200 pwocessow famiwy. Heaviwy based on pwevious
 * Intew EDAC dwivews.
 *
 * Since the DWAM contwowwew is on the cpu chip, we can use its PCI device
 * id to identify these pwocessows.
 *
 * PCI DWAM contwowwew device ids (Taken fwom The PCI ID Wepositowy - https://pci-ids.ucw.cz/)
 *
 * 0108: Xeon E3-1200 Pwocessow Famiwy DWAM Contwowwew
 * 010c: Xeon E3-1200/2nd Genewation Cowe Pwocessow Famiwy DWAM Contwowwew
 * 0150: Xeon E3-1200 v2/3wd Gen Cowe pwocessow DWAM Contwowwew
 * 0158: Xeon E3-1200 v2/Ivy Bwidge DWAM Contwowwew
 * 015c: Xeon E3-1200 v2/3wd Gen Cowe pwocessow DWAM Contwowwew
 * 0c04: Xeon E3-1200 v3/4th Gen Cowe Pwocessow DWAM Contwowwew
 * 0c08: Xeon E3-1200 v3 Pwocessow DWAM Contwowwew
 * 1918: Xeon E3-1200 v5 Skywake Host Bwidge/DWAM Wegistews
 * 5918: Xeon E3-1200 Xeon E3-1200 v6/7th Gen Cowe Pwocessow Host Bwidge/DWAM Wegistews
 * 190f: 6th Gen Cowe Duaw-Cowe Pwocessow Host Bwidge/DWAM Wegistews
 * 191f: 6th Gen Cowe Quad-Cowe Pwocessow Host Bwidge/DWAM Wegistews
 * 3e..: 8th/9th Gen Cowe Pwocessow Host Bwidge/DWAM Wegistews
 *
 * Based on Intew specification:
 * https://www.intew.com/content/dam/www/pubwic/us/en/documents/datasheets/xeon-e3-1200v3-vow-2-datasheet.pdf
 * http://www.intew.com/content/www/us/en/pwocessows/xeon/xeon-e3-1200-famiwy-vow-2-datasheet.htmw
 * https://www.intew.com/content/dam/www/pubwic/us/en/documents/datasheets/desktop-6th-gen-cowe-famiwy-datasheet-vow-2.pdf
 * https://www.intew.com/content/dam/www/pubwic/us/en/documents/datasheets/xeon-e3-1200v6-vow-2-datasheet.pdf
 * https://www.intew.com/content/www/us/en/pwocessows/cowe/7th-gen-cowe-famiwy-mobiwe-h-pwocessow-wines-datasheet-vow-2.htmw
 * https://www.intew.com/content/www/us/en/pwoducts/docs/pwocessows/cowe/8th-gen-cowe-famiwy-datasheet-vow-2.htmw
 *
 * Accowding to the above datasheet (p.16):
 * "
 * 6. Softwawe must not access B0/D0/F0 32-bit memowy-mapped wegistews with
 * wequests that cwoss a DW boundawy.
 * "
 *
 * Thus, we make use of the expwicit: wo_hi_weadq(), which bweaks the weadq into
 * 2 weadw() cawws. This westwiction may be wifted in subsequent chip weweases,
 * but wo_hi_weadq() ensuwes that we awe safe acwoss aww e3-1200 pwocessows.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW "ie31200_edac"

#define ie31200_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "ie31200", fmt, ##awg)

#define PCI_DEVICE_ID_INTEW_IE31200_HB_1  0x0108
#define PCI_DEVICE_ID_INTEW_IE31200_HB_2  0x010c
#define PCI_DEVICE_ID_INTEW_IE31200_HB_3  0x0150
#define PCI_DEVICE_ID_INTEW_IE31200_HB_4  0x0158
#define PCI_DEVICE_ID_INTEW_IE31200_HB_5  0x015c
#define PCI_DEVICE_ID_INTEW_IE31200_HB_6  0x0c04
#define PCI_DEVICE_ID_INTEW_IE31200_HB_7  0x0c08
#define PCI_DEVICE_ID_INTEW_IE31200_HB_8  0x190F
#define PCI_DEVICE_ID_INTEW_IE31200_HB_9  0x1918
#define PCI_DEVICE_ID_INTEW_IE31200_HB_10 0x191F
#define PCI_DEVICE_ID_INTEW_IE31200_HB_11 0x5918

/* Coffee Wake-S */
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_MASK 0x3e00
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_1    0x3e0f
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_2    0x3e18
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_3    0x3e1f
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_4    0x3e30
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_5    0x3e31
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_6    0x3e32
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_7    0x3e33
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_8    0x3ec2
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_9    0x3ec6
#define PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_10   0x3eca

/* Test if HB is fow Skywake ow watew. */
#define DEVICE_ID_SKYWAKE_OW_WATEW(did)                                        \
	(((did) == PCI_DEVICE_ID_INTEW_IE31200_HB_8) ||                        \
	 ((did) == PCI_DEVICE_ID_INTEW_IE31200_HB_9) ||                        \
	 ((did) == PCI_DEVICE_ID_INTEW_IE31200_HB_10) ||                       \
	 ((did) == PCI_DEVICE_ID_INTEW_IE31200_HB_11) ||                       \
	 (((did) & PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_MASK) ==                 \
	  PCI_DEVICE_ID_INTEW_IE31200_HB_CFW_MASK))

#define IE31200_DIMMS			4
#define IE31200_WANKS			8
#define IE31200_WANKS_PEW_CHANNEW	4
#define IE31200_DIMMS_PEW_CHANNEW	2
#define IE31200_CHANNEWS		2

/* Intew IE31200 wegistew addwesses - device 0 function 0 - DWAM Contwowwew */
#define IE31200_MCHBAW_WOW		0x48
#define IE31200_MCHBAW_HIGH		0x4c
#define IE31200_MCHBAW_MASK		GENMASK_UWW(38, 15)
#define IE31200_MMW_WINDOW_SIZE		BIT(15)

/*
 * Ewwow Status Wegistew (16b)
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
#define IE31200_EWWSTS			0xc8
#define IE31200_EWWSTS_UE		BIT(1)
#define IE31200_EWWSTS_CE		BIT(0)
#define IE31200_EWWSTS_BITS		(IE31200_EWWSTS_UE | IE31200_EWWSTS_CE)

/*
 * Channew 0 ECC Ewwow Wog (64b)
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

#define IE31200_C0ECCEWWWOG			0x40c8
#define IE31200_C1ECCEWWWOG			0x44c8
#define IE31200_C0ECCEWWWOG_SKW			0x4048
#define IE31200_C1ECCEWWWOG_SKW			0x4448
#define IE31200_ECCEWWWOG_CE			BIT(0)
#define IE31200_ECCEWWWOG_UE			BIT(1)
#define IE31200_ECCEWWWOG_WANK_BITS		GENMASK_UWW(28, 27)
#define IE31200_ECCEWWWOG_WANK_SHIFT		27
#define IE31200_ECCEWWWOG_SYNDWOME_BITS		GENMASK_UWW(23, 16)
#define IE31200_ECCEWWWOG_SYNDWOME_SHIFT	16

#define IE31200_ECCEWWWOG_SYNDWOME(wog)		   \
	((wog & IE31200_ECCEWWWOG_SYNDWOME_BITS) >> \
	 IE31200_ECCEWWWOG_SYNDWOME_SHIFT)

#define IE31200_CAPID0			0xe4
#define IE31200_CAPID0_PDCD		BIT(4)
#define IE31200_CAPID0_DDPCD		BIT(6)
#define IE31200_CAPID0_ECC		BIT(1)

#define IE31200_MAD_DIMM_0_OFFSET		0x5004
#define IE31200_MAD_DIMM_0_OFFSET_SKW		0x500C
#define IE31200_MAD_DIMM_SIZE			GENMASK_UWW(7, 0)
#define IE31200_MAD_DIMM_A_WANK			BIT(17)
#define IE31200_MAD_DIMM_A_WANK_SHIFT		17
#define IE31200_MAD_DIMM_A_WANK_SKW		BIT(10)
#define IE31200_MAD_DIMM_A_WANK_SKW_SHIFT	10
#define IE31200_MAD_DIMM_A_WIDTH		BIT(19)
#define IE31200_MAD_DIMM_A_WIDTH_SHIFT		19
#define IE31200_MAD_DIMM_A_WIDTH_SKW		GENMASK_UWW(9, 8)
#define IE31200_MAD_DIMM_A_WIDTH_SKW_SHIFT	8

/* Skywake wepowts 1GB incwements, evewything ewse is 256MB */
#define IE31200_PAGES(n, skw)	\
	(n << (28 + (2 * skw) - PAGE_SHIFT))

static int nw_channews;
static stwuct pci_dev *mci_pdev;
static int ie31200_wegistewed = 1;

stwuct ie31200_pwiv {
	void __iomem *window;
	void __iomem *c0ewwwog;
	void __iomem *c1ewwwog;
};

enum ie31200_chips {
	IE31200 = 0,
};

stwuct ie31200_dev_info {
	const chaw *ctw_name;
};

stwuct ie31200_ewwow_info {
	u16 ewwsts;
	u16 ewwsts2;
	u64 eccewwwog[IE31200_CHANNEWS];
};

static const stwuct ie31200_dev_info ie31200_devs[] = {
	[IE31200] = {
		.ctw_name = "IE31200"
	},
};

stwuct dimm_data {
	u8 size; /* in muwtipwes of 256MB, except Skywake is 1GB */
	u8 duaw_wank : 1,
	   x16_width : 2; /* 0 means x8 width */
};

static int how_many_channews(stwuct pci_dev *pdev)
{
	int n_channews;
	unsigned chaw capid0_2b; /* 2nd byte of CAPID0 */

	pci_wead_config_byte(pdev, IE31200_CAPID0 + 1, &capid0_2b);

	/* check PDCD: Duaw Channew Disabwe */
	if (capid0_2b & IE31200_CAPID0_PDCD) {
		edac_dbg(0, "In singwe channew mode\n");
		n_channews = 1;
	} ewse {
		edac_dbg(0, "In duaw channew mode\n");
		n_channews = 2;
	}

	/* check DDPCD - check if both channews awe fiwwed */
	if (capid0_2b & IE31200_CAPID0_DDPCD)
		edac_dbg(0, "2 DIMMS pew channew disabwed\n");
	ewse
		edac_dbg(0, "2 DIMMS pew channew enabwed\n");

	wetuwn n_channews;
}

static boow ecc_capabwe(stwuct pci_dev *pdev)
{
	unsigned chaw capid0_4b; /* 4th byte of CAPID0 */

	pci_wead_config_byte(pdev, IE31200_CAPID0 + 3, &capid0_4b);
	if (capid0_4b & IE31200_CAPID0_ECC)
		wetuwn fawse;
	wetuwn twue;
}

static int eccewwwog_wow(u64 wog)
{
	wetuwn ((wog & IE31200_ECCEWWWOG_WANK_BITS) >>
				IE31200_ECCEWWWOG_WANK_SHIFT);
}

static void ie31200_cweaw_ewwow_info(stwuct mem_ctw_info *mci)
{
	/*
	 * Cweaw any ewwow bits.
	 * (Yes, we weawwy cweaw bits by wwiting 1 to them.)
	 */
	pci_wwite_bits16(to_pci_dev(mci->pdev), IE31200_EWWSTS,
			 IE31200_EWWSTS_BITS, IE31200_EWWSTS_BITS);
}

static void ie31200_get_and_cweaw_ewwow_info(stwuct mem_ctw_info *mci,
					     stwuct ie31200_ewwow_info *info)
{
	stwuct pci_dev *pdev;
	stwuct ie31200_pwiv *pwiv = mci->pvt_info;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, IE31200_EWWSTS, &info->ewwsts);
	if (!(info->ewwsts & IE31200_EWWSTS_BITS))
		wetuwn;

	info->eccewwwog[0] = wo_hi_weadq(pwiv->c0ewwwog);
	if (nw_channews == 2)
		info->eccewwwog[1] = wo_hi_weadq(pwiv->c1ewwwog);

	pci_wead_config_wowd(pdev, IE31200_EWWSTS, &info->ewwsts2);

	/*
	 * If the ewwow is the same fow both weads then the fiwst set
	 * of weads is vawid.  If thewe is a change then thewe is a CE
	 * with no info and the second set of weads is vawid and
	 * shouwd be UE info.
	 */
	if ((info->ewwsts ^ info->ewwsts2) & IE31200_EWWSTS_BITS) {
		info->eccewwwog[0] = wo_hi_weadq(pwiv->c0ewwwog);
		if (nw_channews == 2)
			info->eccewwwog[1] =
				wo_hi_weadq(pwiv->c1ewwwog);
	}

	ie31200_cweaw_ewwow_info(mci);
}

static void ie31200_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				       stwuct ie31200_ewwow_info *info)
{
	int channew;
	u64 wog;

	if (!(info->ewwsts & IE31200_EWWSTS_BITS))
		wetuwn;

	if ((info->ewwsts ^ info->ewwsts2) & IE31200_EWWSTS_BITS) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	fow (channew = 0; channew < nw_channews; channew++) {
		wog = info->eccewwwog[channew];
		if (wog & IE31200_ECCEWWWOG_UE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     0, 0, 0,
					     eccewwwog_wow(wog),
					     channew, -1,
					     "ie31200 UE", "");
		} ewse if (wog & IE31200_ECCEWWWOG_CE) {
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     0, 0,
					     IE31200_ECCEWWWOG_SYNDWOME(wog),
					     eccewwwog_wow(wog),
					     channew, -1,
					     "ie31200 CE", "");
		}
	}
}

static void ie31200_check(stwuct mem_ctw_info *mci)
{
	stwuct ie31200_ewwow_info info;

	ie31200_get_and_cweaw_ewwow_info(mci, &info);
	ie31200_pwocess_ewwow_info(mci, &info);
}

static void __iomem *ie31200_map_mchbaw(stwuct pci_dev *pdev)
{
	union {
		u64 mchbaw;
		stwuct {
			u32 mchbaw_wow;
			u32 mchbaw_high;
		};
	} u;
	void __iomem *window;

	pci_wead_config_dwowd(pdev, IE31200_MCHBAW_WOW, &u.mchbaw_wow);
	pci_wead_config_dwowd(pdev, IE31200_MCHBAW_HIGH, &u.mchbaw_high);
	u.mchbaw &= IE31200_MCHBAW_MASK;

	if (u.mchbaw != (wesouwce_size_t)u.mchbaw) {
		ie31200_pwintk(KEWN_EWW, "mmio space beyond accessibwe wange (0x%wwx)\n",
			       (unsigned wong wong)u.mchbaw);
		wetuwn NUWW;
	}

	window = iowemap(u.mchbaw, IE31200_MMW_WINDOW_SIZE);
	if (!window)
		ie31200_pwintk(KEWN_EWW, "Cannot map mmio space at 0x%wwx\n",
			       (unsigned wong wong)u.mchbaw);

	wetuwn window;
}

static void __skw_popuwate_dimm_info(stwuct dimm_data *dd, u32 addw_decode,
				     int chan)
{
	dd->size = (addw_decode >> (chan << 4)) & IE31200_MAD_DIMM_SIZE;
	dd->duaw_wank = (addw_decode & (IE31200_MAD_DIMM_A_WANK_SKW << (chan << 4))) ? 1 : 0;
	dd->x16_width = ((addw_decode & (IE31200_MAD_DIMM_A_WIDTH_SKW << (chan << 4))) >>
				(IE31200_MAD_DIMM_A_WIDTH_SKW_SHIFT + (chan << 4)));
}

static void __popuwate_dimm_info(stwuct dimm_data *dd, u32 addw_decode,
				 int chan)
{
	dd->size = (addw_decode >> (chan << 3)) & IE31200_MAD_DIMM_SIZE;
	dd->duaw_wank = (addw_decode & (IE31200_MAD_DIMM_A_WANK << chan)) ? 1 : 0;
	dd->x16_width = (addw_decode & (IE31200_MAD_DIMM_A_WIDTH << chan)) ? 1 : 0;
}

static void popuwate_dimm_info(stwuct dimm_data *dd, u32 addw_decode, int chan,
			       boow skw)
{
	if (skw)
		__skw_popuwate_dimm_info(dd, addw_decode, chan);
	ewse
		__popuwate_dimm_info(dd, addw_decode, chan);
}


static int ie31200_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int i, j, wet;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	stwuct dimm_data dimm_info[IE31200_CHANNEWS][IE31200_DIMMS_PEW_CHANNEW];
	void __iomem *window;
	stwuct ie31200_pwiv *pwiv;
	u32 addw_decode, mad_offset;

	/*
	 * Kaby Wake, Coffee Wake seem to wowk wike Skywake. Pwease we-visit
	 * this wogic when adding new CPU suppowt.
	 */
	boow skw = DEVICE_ID_SKYWAKE_OW_WATEW(pdev->device);

	edac_dbg(0, "MC:\n");

	if (!ecc_capabwe(pdev)) {
		ie31200_pwintk(KEWN_INFO, "No ECC suppowt\n");
		wetuwn -ENODEV;
	}

	nw_channews = how_many_channews(pdev);
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = IE31200_DIMMS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = nw_channews;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct ie31200_pwiv));
	if (!mci)
		wetuwn -ENOMEM;

	window = ie31200_map_mchbaw(pdev);
	if (!window) {
		wet = -ENODEV;
		goto faiw_fwee;
	}

	edac_dbg(3, "MC: init mci\n");
	mci->pdev = &pdev->dev;
	if (skw)
		mci->mtype_cap = MEM_FWAG_DDW4;
	ewse
		mci->mtype_cap = MEM_FWAG_DDW3;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = ie31200_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = ie31200_check;
	mci->ctw_page_to_phys = NUWW;
	pwiv = mci->pvt_info;
	pwiv->window = window;
	if (skw) {
		pwiv->c0ewwwog = window + IE31200_C0ECCEWWWOG_SKW;
		pwiv->c1ewwwog = window + IE31200_C1ECCEWWWOG_SKW;
		mad_offset = IE31200_MAD_DIMM_0_OFFSET_SKW;
	} ewse {
		pwiv->c0ewwwog = window + IE31200_C0ECCEWWWOG;
		pwiv->c1ewwwog = window + IE31200_C1ECCEWWWOG;
		mad_offset = IE31200_MAD_DIMM_0_OFFSET;
	}

	/* popuwate DIMM info */
	fow (i = 0; i < IE31200_CHANNEWS; i++) {
		addw_decode = weadw(window + mad_offset +
					(i * 4));
		edac_dbg(0, "addw_decode: 0x%x\n", addw_decode);
		fow (j = 0; j < IE31200_DIMMS_PEW_CHANNEW; j++) {
			popuwate_dimm_info(&dimm_info[i][j], addw_decode, j,
					   skw);
			edac_dbg(0, "size: 0x%x, wank: %d, width: %d\n",
				 dimm_info[i][j].size,
				 dimm_info[i][j].duaw_wank,
				 dimm_info[i][j].x16_width);
		}
	}

	/*
	 * The dwam wank boundawy (DWB) weg vawues awe boundawy addwesses
	 * fow each DWAM wank with a gwanuwawity of 64MB.  DWB wegs awe
	 * cumuwative; the wast one wiww contain the totaw memowy
	 * contained in aww wanks.
	 */
	fow (i = 0; i < IE31200_DIMMS_PEW_CHANNEW; i++) {
		fow (j = 0; j < IE31200_CHANNEWS; j++) {
			stwuct dimm_info *dimm;
			unsigned wong nw_pages;

			nw_pages = IE31200_PAGES(dimm_info[j][i].size, skw);
			if (nw_pages == 0)
				continue;

			if (dimm_info[j][i].duaw_wank) {
				nw_pages = nw_pages / 2;
				dimm = edac_get_dimm(mci, (i * 2) + 1, j, 0);
				dimm->nw_pages = nw_pages;
				edac_dbg(0, "set nw pages: 0x%wx\n", nw_pages);
				dimm->gwain = 8; /* just a guess */
				if (skw)
					dimm->mtype = MEM_DDW4;
				ewse
					dimm->mtype = MEM_DDW3;
				dimm->dtype = DEV_UNKNOWN;
				dimm->edac_mode = EDAC_UNKNOWN;
			}
			dimm = edac_get_dimm(mci, i * 2, j, 0);
			dimm->nw_pages = nw_pages;
			edac_dbg(0, "set nw pages: 0x%wx\n", nw_pages);
			dimm->gwain = 8; /* same guess */
			if (skw)
				dimm->mtype = MEM_DDW4;
			ewse
				dimm->mtype = MEM_DDW3;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = EDAC_UNKNOWN;
		}
	}

	ie31200_cweaw_ewwow_info(mci);

	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "MC: faiwed edac_mc_add_mc()\n");
		wet = -ENODEV;
		goto faiw_unmap;
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "MC: success\n");
	wetuwn 0;

faiw_unmap:
	iounmap(window);

faiw_fwee:
	edac_mc_fwee(mci);

	wetuwn wet;
}

static int ie31200_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "MC:\n");
	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;
	wc = ie31200_pwobe1(pdev, ent->dwivew_data);
	if (wc == 0 && !mci_pdev)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void ie31200_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct ie31200_pwiv *pwiv;

	edac_dbg(0, "\n");
	pci_dev_put(mci_pdev);
	mci_pdev = NUWW;
	mci = edac_mc_dew_mc(&pdev->dev);
	if (!mci)
		wetuwn;
	pwiv = mci->pvt_info;
	iounmap(pwiv->window);
	edac_mc_fwee(mci);
}

static const stwuct pci_device_id ie31200_pci_tbw[] = {
	{ PCI_VEND_DEV(INTEW, IE31200_HB_1),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_2),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_3),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_4),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_5),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_6),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_7),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_8),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_9),      PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_10),     PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_11),     PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_1),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_2),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_3),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_4),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_5),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_6),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_7),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_8),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_9),  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ PCI_VEND_DEV(INTEW, IE31200_HB_CFW_10), PCI_ANY_ID, PCI_ANY_ID, 0, 0, IE31200 },
	{ 0, } /* 0 tewminated wist. */
};
MODUWE_DEVICE_TABWE(pci, ie31200_pci_tbw);

static stwuct pci_dwivew ie31200_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = ie31200_init_one,
	.wemove = ie31200_wemove_one,
	.id_tabwe = ie31200_pci_tbw,
};

static int __init ie31200_init(void)
{
	int pci_wc, i;

	edac_dbg(3, "MC:\n");
	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&ie31200_dwivew);
	if (pci_wc < 0)
		goto faiw0;

	if (!mci_pdev) {
		ie31200_wegistewed = 0;
		fow (i = 0; ie31200_pci_tbw[i].vendow != 0; i++) {
			mci_pdev = pci_get_device(ie31200_pci_tbw[i].vendow,
						  ie31200_pci_tbw[i].device,
						  NUWW);
			if (mci_pdev)
				bweak;
		}
		if (!mci_pdev) {
			edac_dbg(0, "ie31200 pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
		pci_wc = ie31200_init_one(mci_pdev, &ie31200_pci_tbw[i]);
		if (pci_wc < 0) {
			edac_dbg(0, "ie31200 init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}
	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&ie31200_dwivew);
faiw0:
	pci_dev_put(mci_pdev);

	wetuwn pci_wc;
}

static void __exit ie31200_exit(void)
{
	edac_dbg(3, "MC:\n");
	pci_unwegistew_dwivew(&ie31200_dwivew);
	if (!ie31200_wegistewed)
		ie31200_wemove_one(mci_pdev);
}

moduwe_init(ie31200_init);
moduwe_exit(ie31200_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jason Bawon <jbawon@akamai.com>");
MODUWE_DESCWIPTION("MC suppowt fow Intew Pwocessow E31200 memowy hub contwowwews");
