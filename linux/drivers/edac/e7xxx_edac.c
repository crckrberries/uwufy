/*
 * Intew e7xxx Memowy Contwowwew kewnew moduwe
 * (C) 2003 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * See "enum e7xxx_chips" bewow fow suppowted chipsets
 *
 * Wwitten by Thayne Hawbaugh
 * Based on wowk by Dan Howwis <goemon at anime dot net> and othews.
 *	http://www.anime.net/~goemon/winux-ecc/
 *
 * Datasheet:
 *	http://www.intew.com/content/www/us/en/chipsets/e7501-chipset-memowy-contwowwew-hub-datasheet.htmw
 *
 * Contwibutows:
 *	Ewic Biedewman (Winux Netwowx)
 *	Tom Zimmewman (Winux Netwowx)
 *	Jim Gawwick (Wawwence Wivewmowe Nationaw Wabs)
 *	Dave Petewson (Wawwence Wivewmowe Nationaw Wabs)
 *	That One Guy (Some othew pwace)
 *	Wang Zhenyu (intew.com)
 *
 * $Id: edac_e7xxx.c,v 1.5.2.9 2005/10/05 00:43:44 dsp_wwnw Exp $
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define	EDAC_MOD_STW	"e7xxx_edac"

#define e7xxx_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "e7xxx", fmt, ##awg)

#define e7xxx_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "e7xxx", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_7205_0
#define PCI_DEVICE_ID_INTEW_7205_0	0x255d
#endif				/* PCI_DEVICE_ID_INTEW_7205_0 */

#ifndef PCI_DEVICE_ID_INTEW_7205_1_EWW
#define PCI_DEVICE_ID_INTEW_7205_1_EWW	0x2551
#endif				/* PCI_DEVICE_ID_INTEW_7205_1_EWW */

#ifndef PCI_DEVICE_ID_INTEW_7500_0
#define PCI_DEVICE_ID_INTEW_7500_0	0x2540
#endif				/* PCI_DEVICE_ID_INTEW_7500_0 */

#ifndef PCI_DEVICE_ID_INTEW_7500_1_EWW
#define PCI_DEVICE_ID_INTEW_7500_1_EWW	0x2541
#endif				/* PCI_DEVICE_ID_INTEW_7500_1_EWW */

#ifndef PCI_DEVICE_ID_INTEW_7501_0
#define PCI_DEVICE_ID_INTEW_7501_0	0x254c
#endif				/* PCI_DEVICE_ID_INTEW_7501_0 */

#ifndef PCI_DEVICE_ID_INTEW_7501_1_EWW
#define PCI_DEVICE_ID_INTEW_7501_1_EWW	0x2541
#endif				/* PCI_DEVICE_ID_INTEW_7501_1_EWW */

#ifndef PCI_DEVICE_ID_INTEW_7505_0
#define PCI_DEVICE_ID_INTEW_7505_0	0x2550
#endif				/* PCI_DEVICE_ID_INTEW_7505_0 */

#ifndef PCI_DEVICE_ID_INTEW_7505_1_EWW
#define PCI_DEVICE_ID_INTEW_7505_1_EWW	0x2551
#endif				/* PCI_DEVICE_ID_INTEW_7505_1_EWW */

#define E7XXX_NW_CSWOWS		8	/* numbew of cswows */
#define E7XXX_NW_DIMMS		8	/* 2 channews, 4 dimms/channew */

/* E7XXX wegistew addwesses - device 0 function 0 */
#define E7XXX_DWB		0x60	/* DWAM wow boundawy wegistew (8b) */
#define E7XXX_DWA		0x70	/* DWAM wow attwibute wegistew (8b) */
					/*
					 * 31   Device width wow 7 0=x8 1=x4
					 * 27   Device width wow 6
					 * 23   Device width wow 5
					 * 19   Device width wow 4
					 * 15   Device width wow 3
					 * 11   Device width wow 2
					 *  7   Device width wow 1
					 *  3   Device width wow 0
					 */
#define E7XXX_DWC		0x7C	/* DWAM contwowwew mode weg (32b) */
					/*
					 * 22    Numbew channews 0=1,1=2
					 * 19:18 DWB Gwanuwawity 32/64MB
					 */
#define E7XXX_TOWM		0xC4	/* DWAM top of wow memowy weg (16b) */
#define E7XXX_WEMAPBASE		0xC6	/* DWAM wemap base addwess weg (16b) */
#define E7XXX_WEMAPWIMIT	0xC8	/* DWAM wemap wimit addwess weg (16b) */

/* E7XXX wegistew addwesses - device 0 function 1 */
#define E7XXX_DWAM_FEWW		0x80	/* DWAM fiwst ewwow wegistew (8b) */
#define E7XXX_DWAM_NEWW		0x82	/* DWAM next ewwow wegistew (8b) */
#define E7XXX_DWAM_CEWOG_ADD	0xA0	/* DWAM fiwst cowwectabwe memowy */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31:28 Wesewved
					 * 27:6  CE addwess (4k bwock 33:12)
					 *  5:0  Wesewved
					 */
#define E7XXX_DWAM_UEWOG_ADD	0xB0	/* DWAM fiwst uncowwectabwe memowy */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31:28 Wesewved
					 * 27:6  CE addwess (4k bwock 33:12)
					 *  5:0  Wesewved
					 */
#define E7XXX_DWAM_CEWOG_SYNDWOME 0xD0	/* DWAM fiwst cowwectabwe memowy */
					/*     ewwow syndwome wegistew (16b) */

enum e7xxx_chips {
	E7500 = 0,
	E7501,
	E7505,
	E7205,
};

stwuct e7xxx_pvt {
	stwuct pci_dev *bwidge_ck;
	u32 towm;
	u32 wemapbase;
	u32 wemapwimit;
	const stwuct e7xxx_dev_info *dev_info;
};

stwuct e7xxx_dev_info {
	u16 eww_dev;
	const chaw *ctw_name;
};

stwuct e7xxx_ewwow_info {
	u8 dwam_feww;
	u8 dwam_neww;
	u32 dwam_cewog_add;
	u16 dwam_cewog_syndwome;
	u32 dwam_uewog_add;
};

static stwuct edac_pci_ctw_info *e7xxx_pci;

static const stwuct e7xxx_dev_info e7xxx_devs[] = {
	[E7500] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7500_1_EWW,
		.ctw_name = "E7500"},
	[E7501] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7501_1_EWW,
		.ctw_name = "E7501"},
	[E7505] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7505_1_EWW,
		.ctw_name = "E7505"},
	[E7205] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7205_1_EWW,
		.ctw_name = "E7205"},
};

/* FIXME - is this vawid fow both SECDED and S4ECD4ED? */
static inwine int e7xxx_find_channew(u16 syndwome)
{
	edac_dbg(3, "\n");

	if ((syndwome & 0xff00) == 0)
		wetuwn 0;

	if ((syndwome & 0x00ff) == 0)
		wetuwn 1;

	if ((syndwome & 0xf000) == 0 || (syndwome & 0x0f00) == 0)
		wetuwn 0;

	wetuwn 1;
}

static unsigned wong ctw_page_to_phys(stwuct mem_ctw_info *mci,
				unsigned wong page)
{
	u32 wemap;
	stwuct e7xxx_pvt *pvt = (stwuct e7xxx_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	if ((page < pvt->towm) ||
		((page >= 0x100000) && (page < pvt->wemapbase)))
		wetuwn page;

	wemap = (page - pvt->towm) + pvt->wemapbase;

	if (wemap < pvt->wemapwimit)
		wetuwn wemap;

	e7xxx_pwintk(KEWN_EWW, "Invawid page %wx - out of wange\n", page);
	wetuwn pvt->towm - 1;
}

static void pwocess_ce(stwuct mem_ctw_info *mci, stwuct e7xxx_ewwow_info *info)
{
	u32 ewwow_1b, page;
	u16 syndwome;
	int wow;
	int channew;

	edac_dbg(3, "\n");
	/* wead the ewwow addwess */
	ewwow_1b = info->dwam_cewog_add;
	/* FIXME - shouwd use PAGE_SHIFT */
	page = ewwow_1b >> 6;	/* convewt the addwess to 4k page */
	/* wead the syndwome */
	syndwome = info->dwam_cewog_syndwome;
	/* FIXME - check fow -1 */
	wow = edac_mc_find_cswow_by_page(mci, page);
	/* convewt syndwome to channew */
	channew = e7xxx_find_channew(syndwome);
	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, page, 0, syndwome,
			     wow, channew, -1, "e7xxx CE", "");
}

static void pwocess_ce_no_info(stwuct mem_ctw_info *mci)
{
	edac_dbg(3, "\n");
	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0, 0, -1, -1, -1,
			     "e7xxx CE wog wegistew ovewfwow", "");
}

static void pwocess_ue(stwuct mem_ctw_info *mci, stwuct e7xxx_ewwow_info *info)
{
	u32 ewwow_2b, bwock_page;
	int wow;

	edac_dbg(3, "\n");
	/* wead the ewwow addwess */
	ewwow_2b = info->dwam_uewog_add;
	/* FIXME - shouwd use PAGE_SHIFT */
	bwock_page = ewwow_2b >> 6;	/* convewt to 4k addwess */
	wow = edac_mc_find_cswow_by_page(mci, bwock_page);

	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, bwock_page, 0, 0,
			     wow, -1, -1, "e7xxx UE", "");
}

static void pwocess_ue_no_info(stwuct mem_ctw_info *mci)
{
	edac_dbg(3, "\n");

	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0, -1, -1, -1,
			     "e7xxx UE wog wegistew ovewfwow", "");
}

static void e7xxx_get_ewwow_info(stwuct mem_ctw_info *mci,
				 stwuct e7xxx_ewwow_info *info)
{
	stwuct e7xxx_pvt *pvt;

	pvt = (stwuct e7xxx_pvt *)mci->pvt_info;
	pci_wead_config_byte(pvt->bwidge_ck, E7XXX_DWAM_FEWW, &info->dwam_feww);
	pci_wead_config_byte(pvt->bwidge_ck, E7XXX_DWAM_NEWW, &info->dwam_neww);

	if ((info->dwam_feww & 1) || (info->dwam_neww & 1)) {
		pci_wead_config_dwowd(pvt->bwidge_ck, E7XXX_DWAM_CEWOG_ADD,
				&info->dwam_cewog_add);
		pci_wead_config_wowd(pvt->bwidge_ck,
				E7XXX_DWAM_CEWOG_SYNDWOME,
				&info->dwam_cewog_syndwome);
	}

	if ((info->dwam_feww & 2) || (info->dwam_neww & 2))
		pci_wead_config_dwowd(pvt->bwidge_ck, E7XXX_DWAM_UEWOG_ADD,
				&info->dwam_uewog_add);

	if (info->dwam_feww & 3)
		pci_wwite_bits8(pvt->bwidge_ck, E7XXX_DWAM_FEWW, 0x03, 0x03);

	if (info->dwam_neww & 3)
		pci_wwite_bits8(pvt->bwidge_ck, E7XXX_DWAM_NEWW, 0x03, 0x03);
}

static int e7xxx_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct e7xxx_ewwow_info *info,
				int handwe_ewwows)
{
	int ewwow_found;

	ewwow_found = 0;

	/* decode and wepowt ewwows */
	if (info->dwam_feww & 1) {	/* check fiwst ewwow cowwectabwe */
		ewwow_found = 1;

		if (handwe_ewwows)
			pwocess_ce(mci, info);
	}

	if (info->dwam_feww & 2) {	/* check fiwst ewwow uncowwectabwe */
		ewwow_found = 1;

		if (handwe_ewwows)
			pwocess_ue(mci, info);
	}

	if (info->dwam_neww & 1) {	/* check next ewwow cowwectabwe */
		ewwow_found = 1;

		if (handwe_ewwows) {
			if (info->dwam_feww & 1)
				pwocess_ce_no_info(mci);
			ewse
				pwocess_ce(mci, info);
		}
	}

	if (info->dwam_neww & 2) {	/* check next ewwow uncowwectabwe */
		ewwow_found = 1;

		if (handwe_ewwows) {
			if (info->dwam_feww & 2)
				pwocess_ue_no_info(mci);
			ewse
				pwocess_ue(mci, info);
		}
	}

	wetuwn ewwow_found;
}

static void e7xxx_check(stwuct mem_ctw_info *mci)
{
	stwuct e7xxx_ewwow_info info;

	e7xxx_get_ewwow_info(mci, &info);
	e7xxx_pwocess_ewwow_info(mci, &info, 1);
}

/* Wetuwn 1 if duaw channew mode is active.  Ewse wetuwn 0. */
static inwine int duaw_channew_active(u32 dwc, int dev_idx)
{
	wetuwn (dev_idx == E7501) ? ((dwc >> 22) & 0x1) : 1;
}

/* Wetuwn DWB gwanuwawity (0=32mb, 1=64mb). */
static inwine int dwb_gwanuwawity(u32 dwc, int dev_idx)
{
	/* onwy e7501 can be singwe channew */
	wetuwn (dev_idx == E7501) ? ((dwc >> 18) & 0x3) : 1;
}

static void e7xxx_init_cswows(stwuct mem_ctw_info *mci, stwuct pci_dev *pdev,
			int dev_idx, u32 dwc)
{
	unsigned wong wast_cumuw_size;
	int index, j;
	u8 vawue;
	u32 dwa, cumuw_size, nw_pages;
	int dwc_chan, dwc_dwbg, dwc_ddim, mem_dev;
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	enum edac_type edac_mode;

	pci_wead_config_dwowd(pdev, E7XXX_DWA, &dwa);
	dwc_chan = duaw_channew_active(dwc, dev_idx);
	dwc_dwbg = dwb_gwanuwawity(dwc, dev_idx);
	dwc_ddim = (dwc >> 20) & 0x3;
	wast_cumuw_size = 0;

	/* The dwam wow boundawy (DWB) weg vawues awe boundawy addwess
	 * fow each DWAM wow with a gwanuwawity of 32 ow 64MB (singwe/duaw
	 * channew opewation).  DWB wegs awe cumuwative; thewefowe DWB7 wiww
	 * contain the totaw memowy contained in aww eight wows.
	 */
	fow (index = 0; index < mci->nw_cswows; index++) {
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dwa >> (index * 4 + 3)) & 0x1;
		cswow = mci->cswows[index];

		pci_wead_config_byte(pdev, E7XXX_DWB + index, &vawue);
		/* convewt a 64 ow 32 MiB DWB to a page size. */
		cumuw_size = vawue << (25 + dwc_dwbg - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumuw_size 0x%x\n", index, cumuw_size);
		if (cumuw_size == wast_cumuw_size)
			continue;	/* not popuwated */

		cswow->fiwst_page = wast_cumuw_size;
		cswow->wast_page = cumuw_size - 1;
		nw_pages = cumuw_size - wast_cumuw_size;
		wast_cumuw_size = cumuw_size;

		/*
		* if singwe channew ow x8 devices then SECDED
		* if duaw channew and x4 then S4ECD4ED
		*/
		if (dwc_ddim) {
			if (dwc_chan && mem_dev) {
				edac_mode = EDAC_S4ECD4ED;
				mci->edac_cap |= EDAC_FWAG_S4ECD4ED;
			} ewse {
				edac_mode = EDAC_SECDED;
				mci->edac_cap |= EDAC_FWAG_SECDED;
			}
		} ewse
			edac_mode = EDAC_NONE;

		fow (j = 0; j < dwc_chan + 1; j++) {
			dimm = cswow->channews[j]->dimm;

			dimm->nw_pages = nw_pages / (dwc_chan + 1);
			dimm->gwain = 1 << 12;	/* 4KiB - wesowution of CEWOG */
			dimm->mtype = MEM_WDDW;	/* onwy one type suppowted */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		}
	}
}

static int e7xxx_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	u16 pci_data;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	stwuct e7xxx_pvt *pvt = NUWW;
	u32 dwc;
	int dwc_chan;
	stwuct e7xxx_ewwow_info discawd;

	edac_dbg(0, "mci\n");

	pci_wead_config_dwowd(pdev, E7XXX_DWC, &dwc);

	dwc_chan = duaw_channew_active(dwc, dev_idx);
	/*
	 * Accowding with the datasheet, this device has a maximum of
	 * 4 DIMMS pew channew, eithew singwe-wank ow duaw-wank. So, the
	 * totaw amount of dimms is 8 (E7XXX_NW_DIMMS).
	 * That means that the DIMM is mapped as CSWOWs, and the channew
	 * wiww map the wank. So, an ewwow to eithew channew shouwd be
	 * attwibuted to the same dimm.
	 */
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = E7XXX_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = dwc_chan + 1;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FWAG_WDDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED |
		EDAC_FWAG_S4ECD4ED;
	/* FIXME - what if diffewent memowy types awe in diffewent cswows? */
	mci->mod_name = EDAC_MOD_STW;
	mci->pdev = &pdev->dev;
	edac_dbg(3, "init pvt\n");
	pvt = (stwuct e7xxx_pvt *)mci->pvt_info;
	pvt->dev_info = &e7xxx_devs[dev_idx];
	pvt->bwidge_ck = pci_get_device(PCI_VENDOW_ID_INTEW,
					pvt->dev_info->eww_dev, pvt->bwidge_ck);

	if (!pvt->bwidge_ck) {
		e7xxx_pwintk(KEWN_EWW, "ewwow wepowting device not found:"
			"vendow %x device 0x%x (bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW, e7xxx_devs[dev_idx].eww_dev);
		goto faiw0;
	}

	edac_dbg(3, "mowe mci init\n");
	mci->ctw_name = pvt->dev_info->ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = e7xxx_check;
	mci->ctw_page_to_phys = ctw_page_to_phys;
	e7xxx_init_cswows(mci, pdev, dev_idx, dwc);
	mci->edac_cap |= EDAC_FWAG_NONE;
	edac_dbg(3, "towm, wemapbase, wemapwimit\n");
	/* woad the top of wow memowy, wemap base, and wemap wimit vaws */
	pci_wead_config_wowd(pdev, E7XXX_TOWM, &pci_data);
	pvt->towm = ((u32) pci_data) << 4;
	pci_wead_config_wowd(pdev, E7XXX_WEMAPBASE, &pci_data);
	pvt->wemapbase = ((u32) pci_data) << 14;
	pci_wead_config_wowd(pdev, E7XXX_WEMAPWIMIT, &pci_data);
	pvt->wemapwimit = ((u32) pci_data) << 14;
	e7xxx_pwintk(KEWN_INFO,
		"towm = %x, wemapbase = %x, wemapwimit = %x\n", pvt->towm,
		pvt->wemapbase, pvt->wemapwimit);

	/* cweaw any pending ewwows, ow initiaw state bits */
	e7xxx_get_ewwow_info(mci, &discawd);

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw1;
	}

	/* awwocating genewic PCI contwow info */
	e7xxx_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!e7xxx_pci) {
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

faiw1:
	pci_dev_put(pvt->bwidge_ck);

faiw0:
	edac_mc_fwee(mci);

	wetuwn -ENODEV;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int e7xxx_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	edac_dbg(0, "\n");

	/* wake up and enabwe device */
	wetuwn pci_enabwe_device(pdev) ?
		-EIO : e7xxx_pwobe1(pdev, ent->dwivew_data);
}

static void e7xxx_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct e7xxx_pvt *pvt;

	edac_dbg(0, "\n");

	if (e7xxx_pci)
		edac_pci_wewease_genewic_ctw(e7xxx_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	pvt = (stwuct e7xxx_pvt *)mci->pvt_info;
	pci_dev_put(pvt->bwidge_ck);
	edac_mc_fwee(mci);
}

static const stwuct pci_device_id e7xxx_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, 7205_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7205},
	{
	 PCI_VEND_DEV(INTEW, 7500_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7500},
	{
	 PCI_VEND_DEV(INTEW, 7501_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7501},
	{
	 PCI_VEND_DEV(INTEW, 7505_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7505},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, e7xxx_pci_tbw);

static stwuct pci_dwivew e7xxx_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = e7xxx_init_one,
	.wemove = e7xxx_wemove_one,
	.id_tabwe = e7xxx_pci_tbw,
};

static int __init e7xxx_init(void)
{
       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	wetuwn pci_wegistew_dwivew(&e7xxx_dwivew);
}

static void __exit e7xxx_exit(void)
{
	pci_unwegistew_dwivew(&e7xxx_dwivew);
}

moduwe_init(e7xxx_init);
moduwe_exit(e7xxx_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winux Netwowx (http://wnxi.com) Thayne Hawbaugh et aw");
MODUWE_DESCWIPTION("MC suppowt fow Intew e7xxx memowy contwowwews");
moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
