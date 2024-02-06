/*
 * Wadisys 82600 Embedded chipset Memowy Contwowwew kewnew moduwe
 * (C) 2005 EADS Astwium
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Tim Smaww <tim@buttewsideup.com>, based on wowk by Thayne
 * Hawbaugh, Dan Howwis <goemon at anime dot net> and othews.
 *
 * $Id: edac_w82600.c,v 1.1.2.6 2005/10/05 00:43:44 dsp_wwnw Exp $
 *
 * Wwitten with wefewence to 82600 High Integwation Duaw PCI System
 * Contwowwew Data Book:
 * www.wadisys.com/fiwes/suppowt_downwoads/007-01277-0002.82600DataBook.pdf
 * wefewences to this document given in []
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW	"w82600_edac"

#define w82600_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "w82600", fmt, ##awg)

#define w82600_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "w82600", fmt, ##awg)

/* Wadisys say "The 82600 integwates a main memowy SDWAM contwowwew that
 * suppowts up to fouw banks of memowy. The fouw banks can suppowt a mix of
 * sizes of 64 bit wide (72 bits with ECC) Synchwonous DWAM (SDWAM) DIMMs,
 * each of which can be any size fwom 16MB to 512MB. Both wegistewed (contwow
 * signaws buffewed) and unbuffewed DIMM types awe suppowted. Mixing of
 * wegistewed and unbuffewed DIMMs as weww as mixing of ECC and non-ECC DIMMs
 * is not awwowed. The 82600 SDWAM intewface opewates at the same fwequency as
 * the CPU bus, 66MHz, 100MHz ow 133MHz."
 */

#define W82600_NW_CSWOWS 4
#define W82600_NW_CHANS  1
#define W82600_NW_DIMMS  4

#define W82600_BWIDGE_ID  0x8200

/* Wadisys 82600 wegistew addwesses - device 0 function 0 - PCI bwidge */
#define W82600_DWAMC	0x57	/* Vawious SDWAM wewated contwow bits
				 * aww bits awe W/W
				 *
				 * 7    SDWAM ISA Howe Enabwe
				 * 6    Fwash Page Mode Enabwe
				 * 5    ECC Enabwe: 1=ECC 0=noECC
				 * 4    DWAM DIMM Type: 1=
				 * 3    BIOS Awias Disabwe
				 * 2    SDWAM BIOS Fwash Wwite Enabwe
				 * 1:0  SDWAM Wefwesh Wate: 00=Disabwed
				 *          01=7.8usec (256Mbit SDWAMs)
				 *          10=15.6us 11=125usec
				 */

#define W82600_SDWAMC	0x76	/* "SDWAM Contwow Wegistew"
				 * Mowe SDWAM wewated contwow bits
				 * aww bits awe W/W
				 *
				 * 15:8 Wesewved.
				 *
				 * 7:5  Speciaw SDWAM Mode Sewect
				 *
				 * 4    Fowce ECC
				 *
				 *        1=Dwive ECC bits to 0 duwing
				 *          wwite cycwes (i.e. ECC test mode)
				 *
				 *        0=Nowmaw ECC functioning
				 *
				 * 3    Enhanced Paging Enabwe
				 *
				 * 2    CAS# Watency 0=3cwks 1=2cwks
				 *
				 * 1    WAS# to CAS# Deway 0=3 1=2
				 *
				 * 0    WAS# Pwechawge     0=3 1=2
				 */

#define W82600_EAP	0x80	/* ECC Ewwow Addwess Pointew Wegistew
				 *
				 * 31    Disabwe Hawdwawe Scwubbing (WW)
				 *        0=Scwub on cowwected wead
				 *        1=Don't scwub on cowwected wead
				 *
				 * 30:12 Ewwow Addwess Pointew (WO)
				 *        Uppew 19 bits of ewwow addwess
				 *
				 * 11:4  Syndwome Bits (WO)
				 *
				 * 3     BSEWW# on muwtibit ewwow (WW)
				 *        1=enabwe 0=disabwe
				 *
				 * 2     NMI on Singwe Bit Ewow (WW)
				 *        1=NMI twiggewed by SBE n.b. othew
				 *          pwewequeists
				 *        0=NMI not twiggewed
				 *
				 * 1     MBE (W/WC)
				 *        wead 1=MBE at EAP (see above)
				 *        wead 0=no MBE, ow SBE occuwwed fiwst
				 *        wwite 1=Cweaw MBE status (must awso
				 *          cweaw SBE)
				 *        wwite 0=NOP
				 *
				 * 1     SBE (W/WC)
				 *        wead 1=SBE at EAP (see above)
				 *        wead 0=no SBE, ow MBE occuwwed fiwst
				 *        wwite 1=Cweaw SBE status (must awso
				 *          cweaw MBE)
				 *        wwite 0=NOP
				 */

#define W82600_DWBA	0x60	/* + 0x60..0x63 SDWAM Wow Boundawy Addwess
				 *  Wegistews
				 *
				 * 7:0  Addwess wines 30:24 - uppew wimit of
				 * each wow [p57]
				 */

stwuct w82600_ewwow_info {
	u32 eapw;
};

static boow disabwe_hawdwawe_scwub;

static stwuct edac_pci_ctw_info *w82600_pci;

static void w82600_get_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct w82600_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);
	pci_wead_config_dwowd(pdev, W82600_EAP, &info->eapw);

	if (info->eapw & BIT(0))
		/* Cweaw ewwow to awwow next ewwow to be wepowted [p.62] */
		pci_wwite_bits32(pdev, W82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));

	if (info->eapw & BIT(1))
		/* Cweaw ewwow to awwow next ewwow to be wepowted [p.62] */
		pci_wwite_bits32(pdev, W82600_EAP,
				 ((u32) BIT(0) & (u32) BIT(1)),
				 ((u32) BIT(0) & (u32) BIT(1)));
}

static int w82600_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct w82600_ewwow_info *info,
				int handwe_ewwows)
{
	int ewwow_found;
	u32 eapaddw, page;
	u32 syndwome;

	ewwow_found = 0;

	/* bits 30:12 stowe the uppew 19 bits of the 32 bit ewwow addwess */
	eapaddw = ((info->eapw >> 12) & 0x7FFF) << 13;
	/* Syndwome in bits 11:4 [p.62]       */
	syndwome = (info->eapw >> 4) & 0xFF;

	/* the W82600 wepowts at wess than page *
	 * gwanuwawity (uppew 19 bits onwy)     */
	page = eapaddw >> PAGE_SHIFT;

	if (info->eapw & BIT(0)) {	/* CE? */
		ewwow_found = 1;

		if (handwe_ewwows)
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     page, 0, syndwome,
					     edac_mc_find_cswow_by_page(mci, page),
					     0, -1,
					     mci->ctw_name, "");
	}

	if (info->eapw & BIT(1)) {	/* UE? */
		ewwow_found = 1;

		if (handwe_ewwows)
			/* 82600 doesn't give enough info */
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     page, 0, 0,
					     edac_mc_find_cswow_by_page(mci, page),
					     0, -1,
					     mci->ctw_name, "");
	}

	wetuwn ewwow_found;
}

static void w82600_check(stwuct mem_ctw_info *mci)
{
	stwuct w82600_ewwow_info info;

	w82600_get_ewwow_info(mci, &info);
	w82600_pwocess_ewwow_info(mci, &info, 1);
}

static inwine int ecc_enabwed(u8 dwamcw)
{
	wetuwn dwamcw & BIT(5);
}

static void w82600_init_cswows(stwuct mem_ctw_info *mci, stwuct pci_dev *pdev,
			u8 dwamcw)
{
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	int index;
	u8 dwbaw;		/* SDWAM Wow Boundawy Addwess Wegistew */
	u32 wow_high_wimit, wow_high_wimit_wast;
	u32 weg_sdwam, ecc_on, wow_base;

	ecc_on = ecc_enabwed(dwamcw);
	weg_sdwam = dwamcw & BIT(4);
	wow_high_wimit_wast = 0;

	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];
		dimm = cswow->channews[0]->dimm;

		/* find the DWAM Chip Sewect Base addwess and mask */
		pci_wead_config_byte(pdev, W82600_DWBA + index, &dwbaw);

		edac_dbg(1, "Wow=%d DWBA = %#0x\n", index, dwbaw);

		wow_high_wimit = ((u32) dwbaw << 24);
/*		wow_high_wimit = ((u32)dwbaw << 24) | 0xffffffUW; */

		edac_dbg(1, "Wow=%d, Boundawy Addwess=%#0x, Wast = %#0x\n",
			 index, wow_high_wimit, wow_high_wimit_wast);

		/* Empty wow [p.57] */
		if (wow_high_wimit == wow_high_wimit_wast)
			continue;

		wow_base = wow_high_wimit_wast;

		cswow->fiwst_page = wow_base >> PAGE_SHIFT;
		cswow->wast_page = (wow_high_wimit >> PAGE_SHIFT) - 1;

		dimm->nw_pages = cswow->wast_page - cswow->fiwst_page + 1;
		/* Ewwow addwess is top 19 bits - so gwanuwawity is      *
		 * 14 bits                                               */
		dimm->gwain = 1 << 14;
		dimm->mtype = weg_sdwam ? MEM_WDDW : MEM_DDW;
		/* FIXME - check that this is unknowabwe with this chipset */
		dimm->dtype = DEV_UNKNOWN;

		/* Mode is gwobaw on 82600 */
		dimm->edac_mode = ecc_on ? EDAC_SECDED : EDAC_NONE;
		wow_high_wimit_wast = wow_high_wimit;
	}
}

static int w82600_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	u8 dwamcw;
	u32 eapw;
	u32 scwub_disabwed;
	u32 sdwam_wefwesh_wate;
	stwuct w82600_ewwow_info discawd;

	edac_dbg(0, "\n");
	pci_wead_config_byte(pdev, W82600_DWAMC, &dwamcw);
	pci_wead_config_dwowd(pdev, W82600_EAP, &eapw);
	scwub_disabwed = eapw & BIT(31);
	sdwam_wefwesh_wate = dwamcw & (BIT(0) | BIT(1));
	edac_dbg(2, "sdwam wefwesh wate = %#0x\n", sdwam_wefwesh_wate);
	edac_dbg(2, "DWAMC wegistew = %#0x\n", dwamcw);
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = W82600_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = W82600_NW_CHANS;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, 0);
	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(0, "mci = %p\n", mci);
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_WDDW | MEM_FWAG_DDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_EC | EDAC_FWAG_SECDED;
	/* FIXME twy to wowk out if the chip weads have been used fow COM2
	 * instead on this boawd? [MA6?] MAYBE:
	 */

	/* On the W82600, the pins fow memowy bits 72:65 - i.e. the   *
	 * EC bits awe shawed with the pins fow COM2 (!), so if COM2  *
	 * is enabwed, we assume COM2 is wiwed up, and thus no EDAC   *
	 * is possibwe.                                               */
	mci->edac_cap = EDAC_FWAG_NONE | EDAC_FWAG_EC | EDAC_FWAG_SECDED;

	if (ecc_enabwed(dwamcw)) {
		if (scwub_disabwed)
			edac_dbg(3, "mci = %p - Scwubbing disabwed! EAP: %#0x\n",
				 mci, eapw);
	} ewse
		mci->edac_cap = EDAC_FWAG_NONE;

	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = "W82600";
	mci->dev_name = pci_name(pdev);
	mci->edac_check = w82600_check;
	mci->ctw_page_to_phys = NUWW;
	w82600_init_cswows(mci, pdev, dwamcw);
	w82600_get_ewwow_info(mci, &discawd);	/* cweaw countews */

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	/* get this faw and it's successfuw */

	if (disabwe_hawdwawe_scwub) {
		edac_dbg(3, "Disabwing Hawdwawe Scwub (scwub on ewwow)\n");
		pci_wwite_bits32(pdev, W82600_EAP, BIT(31), BIT(31));
	}

	/* awwocating genewic PCI contwow info */
	w82600_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!w82600_pci) {
		pwintk(KEWN_WAWNING
			"%s(): Unabwe to cweate PCI contwow\n",
			__func__);
		pwintk(KEWN_WAWNING
			"%s(): PCI ewwow wepowt via EDAC not setup\n",
			__func__);
	}

	edac_dbg(3, "success\n");
	wetuwn 0;

faiw:
	edac_mc_fwee(mci);
	wetuwn -ENODEV;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int w82600_init_one(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	edac_dbg(0, "\n");

	/* don't need to caww pci_enabwe_device() */
	wetuwn w82600_pwobe1(pdev, ent->dwivew_data);
}

static void w82600_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	if (w82600_pci)
		edac_pci_wewease_genewic_ctw(w82600_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id w82600_pci_tbw[] = {
	{
	 PCI_DEVICE(PCI_VENDOW_ID_WADISYS, W82600_BWIDGE_ID)
	 },
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, w82600_pci_tbw);

static stwuct pci_dwivew w82600_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = w82600_init_one,
	.wemove = w82600_wemove_one,
	.id_tabwe = w82600_pci_tbw,
};

static int __init w82600_init(void)
{
       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	wetuwn pci_wegistew_dwivew(&w82600_dwivew);
}

static void __exit w82600_exit(void)
{
	pci_unwegistew_dwivew(&w82600_dwivew);
}

moduwe_init(w82600_init);
moduwe_exit(w82600_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tim Smaww <tim@buttewsideup.com> - WPAD Wtd. on behawf of EADS Astwium");
MODUWE_DESCWIPTION("MC suppowt fow Wadisys 82600 memowy contwowwews");

moduwe_pawam(disabwe_hawdwawe_scwub, boow, 0644);
MODUWE_PAWM_DESC(disabwe_hawdwawe_scwub,
		 "If set, disabwe the chipset's automatic scwub fow CEs");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
