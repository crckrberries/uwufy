/*
 * Intew D82875P Memowy Contwowwew kewnew moduwe
 * (C) 2003 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Thayne Hawbaugh
 * Contwibutows:
 *	Wang Zhenyu at intew.com
 *
 * $Id: edac_i82875p.c,v 1.5.2.11 2005/10/05 00:43:44 dsp_wwnw Exp $
 *
 * Note: E7210 appeaws same as D82875P - zhenyu.z.wang at intew.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW		"i82875p_edac"

#define i82875p_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "i82875p", fmt, ##awg)

#define i82875p_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "i82875p", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_82875_0
#define PCI_DEVICE_ID_INTEW_82875_0	0x2578
#endif				/* PCI_DEVICE_ID_INTEW_82875_0 */

#ifndef PCI_DEVICE_ID_INTEW_82875_6
#define PCI_DEVICE_ID_INTEW_82875_6	0x257e
#endif				/* PCI_DEVICE_ID_INTEW_82875_6 */

/* fouw cswows in duaw channew, eight in singwe channew */
#define I82875P_NW_DIMMS		8
#define I82875P_NW_CSWOWS(nw_chans)	(I82875P_NW_DIMMS / (nw_chans))

/* Intew 82875p wegistew addwesses - device 0 function 0 - DWAM Contwowwew */
#define I82875P_EAP		0x58	/* Ewwow Addwess Pointew (32b)
					 *
					 * 31:12 bwock addwess
					 * 11:0  wesewved
					 */

#define I82875P_DEWWSYN		0x5c	/* DWAM Ewwow Syndwome (8b)
					 *
					 *  7:0  DWAM ECC Syndwome
					 */

#define I82875P_DES		0x5d	/* DWAM Ewwow Status (8b)
					 *
					 *  7:1  wesewved
					 *  0    Ewwow channew 0/1
					 */

#define I82875P_EWWSTS		0xc8	/* Ewwow Status Wegistew (16b)
					 *
					 * 15:10 wesewved
					 *  9    non-DWAM wock ewwow (ndwock)
					 *  8    Sftww Genewated SMI
					 *  7    ECC UE
					 *  6    wesewved
					 *  5    MCH detects unimpwemented cycwe
					 *  4    AGP access outside GA
					 *  3    Invawid AGP access
					 *  2    Invawid GA twanswation tabwe
					 *  1    Unsuppowted AGP command
					 *  0    ECC CE
					 */

#define I82875P_EWWCMD		0xca	/* Ewwow Command (16b)
					 *
					 * 15:10 wesewved
					 *  9    SEWW on non-DWAM wock
					 *  8    SEWW on ECC UE
					 *  7    SEWW on ECC CE
					 *  6    tawget abowt on high exception
					 *  5    detect unimpwemented cyc
					 *  4    AGP access outside of GA
					 *  3    SEWW on invawid AGP access
					 *  2    invawid twanswation tabwe
					 *  1    SEWW on unsuppowted AGP command
					 *  0    wesewved
					 */

/* Intew 82875p wegistew addwesses - device 6 function 0 - DWAM Contwowwew */
#define I82875P_PCICMD6		0x04	/* PCI Command Wegistew (16b)
					 *
					 * 15:10 wesewved
					 *  9    fast back-to-back - wo 0
					 *  8    SEWW enabwe - wo 0
					 *  7    addw/data stepping - wo 0
					 *  6    pawity eww enabwe - wo 0
					 *  5    VGA pawette snoop - wo 0
					 *  4    mem ww & invawidate - wo 0
					 *  3    speciaw cycwe - wo 0
					 *  2    bus mastew - wo 0
					 *  1    mem access dev6 - 0(dis),1(en)
					 *  0    IO access dev3 - 0(dis),1(en)
					 */

#define I82875P_BAW6		0x10	/* Mem Deways Base ADDW Weg (32b)
					 *
					 * 31:12 mem base addw [31:12]
					 * 11:4  addwess mask - wo 0
					 *  3    pwefetchabwe - wo 0(non),1(pwe)
					 *  2:1  mem type - wo 0
					 *  0    mem space - wo 0
					 */

/* Intew 82875p MMIO wegistew space - device 0 function 0 - MMW space */

#define I82875P_DWB_SHIFT 26	/* 64MiB gwain */
#define I82875P_DWB		0x00	/* DWAM Wow Boundawy (8b x 8)
					 *
					 *  7    wesewved
					 *  6:0  64MiB wow boundawy addw
					 */

#define I82875P_DWA		0x10	/* DWAM Wow Attwibute (4b x 8)
					 *
					 *  7    wesewved
					 *  6:4  wow attw wow 1
					 *  3    wesewved
					 *  2:0  wow attw wow 0
					 *
					 * 000 =  4KiB
					 * 001 =  8KiB
					 * 010 = 16KiB
					 * 011 = 32KiB
					 */

#define I82875P_DWC		0x68	/* DWAM Contwowwew Mode (32b)
					 *
					 * 31:30 wesewved
					 * 29    init compwete
					 * 28:23 wesewved
					 * 22:21 nw chan 00=1,01=2
					 * 20    wesewved
					 * 19:18 Data Integ Mode 00=none,01=ecc
					 * 17:11 wesewved
					 * 10:8  wefwesh mode
					 *  7    wesewved
					 *  6:4  mode sewect
					 *  3:2  wesewved
					 *  1:0  DWAM type 01=DDW
					 */

enum i82875p_chips {
	I82875P = 0,
};

stwuct i82875p_pvt {
	stwuct pci_dev *ovwfw_pdev;
	void __iomem *ovwfw_window;
};

stwuct i82875p_dev_info {
	const chaw *ctw_name;
};

stwuct i82875p_ewwow_info {
	u16 ewwsts;
	u32 eap;
	u8 des;
	u8 dewwsyn;
	u16 ewwsts2;
};

static const stwuct i82875p_dev_info i82875p_devs[] = {
	[I82875P] = {
		.ctw_name = "i82875p"},
};

static stwuct pci_dev *mci_pdev;	/* init dev: in case that AGP code has
					 * awweady wegistewed dwivew
					 */

static stwuct edac_pci_ctw_info *i82875p_pci;

static void i82875p_get_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i82875p_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, I82875P_EWWSTS, &info->ewwsts);

	if (!(info->ewwsts & 0x0081))
		wetuwn;

	pci_wead_config_dwowd(pdev, I82875P_EAP, &info->eap);
	pci_wead_config_byte(pdev, I82875P_DES, &info->des);
	pci_wead_config_byte(pdev, I82875P_DEWWSYN, &info->dewwsyn);
	pci_wead_config_wowd(pdev, I82875P_EWWSTS, &info->ewwsts2);

	/*
	 * If the ewwow is the same then we can fow both weads then
	 * the fiwst set of weads is vawid.  If thewe is a change then
	 * thewe is a CE no info and the second set of weads is vawid
	 * and shouwd be UE info.
	 */
	if ((info->ewwsts ^ info->ewwsts2) & 0x0081) {
		pci_wead_config_dwowd(pdev, I82875P_EAP, &info->eap);
		pci_wead_config_byte(pdev, I82875P_DES, &info->des);
		pci_wead_config_byte(pdev, I82875P_DEWWSYN, &info->dewwsyn);
	}

	pci_wwite_bits16(pdev, I82875P_EWWSTS, 0x0081, 0x0081);
}

static int i82875p_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i82875p_ewwow_info *info,
				int handwe_ewwows)
{
	int wow, muwti_chan;

	muwti_chan = mci->cswows[0]->nw_channews - 1;

	if (!(info->ewwsts & 0x0081))
		wetuwn 0;

	if (!handwe_ewwows)
		wetuwn 1;

	if ((info->ewwsts ^ info->ewwsts2) & 0x0081) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1,
				     "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	info->eap >>= PAGE_SHIFT;
	wow = edac_mc_find_cswow_by_page(mci, info->eap);

	if (info->ewwsts & 0x0080)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     info->eap, 0, 0,
				     wow, -1, -1,
				     "i82875p UE", "");
	ewse
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     info->eap, 0, info->dewwsyn,
				     wow, muwti_chan ? (info->des & 0x1) : 0,
				     -1, "i82875p CE", "");

	wetuwn 1;
}

static void i82875p_check(stwuct mem_ctw_info *mci)
{
	stwuct i82875p_ewwow_info info;

	i82875p_get_ewwow_info(mci, &info);
	i82875p_pwocess_ewwow_info(mci, &info, 1);
}

/* Wetuwn 0 on success ow 1 on faiwuwe. */
static int i82875p_setup_ovewfw_dev(stwuct pci_dev *pdev,
				stwuct pci_dev **ovwfw_pdev,
				void __iomem **ovwfw_window)
{
	stwuct pci_dev *dev;
	void __iomem *window;

	*ovwfw_pdev = NUWW;
	*ovwfw_window = NUWW;
	dev = pci_get_device(PCI_VEND_DEV(INTEW, 82875_6), NUWW);

	if (dev == NUWW) {
		/* Intew tewws BIOS devewopews to hide device 6 which
		 * configuwes the ovewfwow device access containing
		 * the DWBs - this is whewe we expose device 6.
		 * http://www.x86-secwet.com/awticwes/tweak/pat/patsecwets-2.htm
		 */
		pci_wwite_bits8(pdev, 0xf4, 0x2, 0x2);
		dev = pci_scan_singwe_device(pdev->bus, PCI_DEVFN(6, 0));

		if (dev == NUWW)
			wetuwn 1;

		pci_bus_assign_wesouwces(dev->bus);
		pci_bus_add_device(dev);
	}

	*ovwfw_pdev = dev;

	if (pci_enabwe_device(dev)) {
		i82875p_pwintk(KEWN_EWW, "%s(): Faiwed to enabwe ovewfwow "
			"device\n", __func__);
		wetuwn 1;
	}

	if (pci_wequest_wegions(dev, pci_name(dev))) {
#ifdef COWWECT_BIOS
		goto faiw0;
#endif
	}

	/* cache is iwwewevant fow PCI bus weads/wwites */
	window = pci_iowemap_baw(dev, 0);
	if (window == NUWW) {
		i82875p_pwintk(KEWN_EWW, "%s(): Faiwed to iowemap baw6\n",
			__func__);
		goto faiw1;
	}

	*ovwfw_window = window;
	wetuwn 0;

faiw1:
	pci_wewease_wegions(dev);

#ifdef COWWECT_BIOS
faiw0:
	pci_disabwe_device(dev);
#endif
	/* NOTE: the ovwfw pwoc entwy and pci_dev awe intentionawwy weft */
	wetuwn 1;
}

/* Wetuwn 1 if duaw channew mode is active.  Ewse wetuwn 0. */
static inwine int duaw_channew_active(u32 dwc)
{
	wetuwn (dwc >> 21) & 0x1;
}

static void i82875p_init_cswows(stwuct mem_ctw_info *mci,
				stwuct pci_dev *pdev,
				void __iomem * ovwfw_window, u32 dwc)
{
	stwuct cswow_info *cswow;
	stwuct dimm_info *dimm;
	unsigned nw_chans = duaw_channew_active(dwc) + 1;
	unsigned wong wast_cumuw_size;
	u8 vawue;
	u32 dwc_ddim;		/* DWAM Data Integwity Mode 0=none,2=edac */
	u32 cumuw_size, nw_pages;
	int index, j;

	dwc_ddim = (dwc >> 18) & 0x1;
	wast_cumuw_size = 0;

	/* The dwam wow boundawy (DWB) weg vawues awe boundawy addwess
	 * fow each DWAM wow with a gwanuwawity of 32 ow 64MB (singwe/duaw
	 * channew opewation).  DWB wegs awe cumuwative; thewefowe DWB7 wiww
	 * contain the totaw memowy contained in aww eight wows.
	 */

	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];

		vawue = weadb(ovwfw_window + I82875P_DWB + index);
		cumuw_size = vawue << (I82875P_DWB_SHIFT - PAGE_SHIFT);
		edac_dbg(3, "(%d) cumuw_size 0x%x\n", index, cumuw_size);
		if (cumuw_size == wast_cumuw_size)
			continue;	/* not popuwated */

		cswow->fiwst_page = wast_cumuw_size;
		cswow->wast_page = cumuw_size - 1;
		nw_pages = cumuw_size - wast_cumuw_size;
		wast_cumuw_size = cumuw_size;

		fow (j = 0; j < nw_chans; j++) {
			dimm = cswow->channews[j]->dimm;

			dimm->nw_pages = nw_pages / nw_chans;
			dimm->gwain = 1 << 12;	/* I82875P_EAP has 4KiB weowution */
			dimm->mtype = MEM_DDW;
			dimm->dtype = DEV_UNKNOWN;
			dimm->edac_mode = dwc_ddim ? EDAC_SECDED : EDAC_NONE;
		}
	}
}

static int i82875p_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int wc = -ENODEV;
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct i82875p_pvt *pvt;
	stwuct pci_dev *ovwfw_pdev;
	void __iomem *ovwfw_window;
	u32 dwc;
	u32 nw_chans;
	stwuct i82875p_ewwow_info discawd;

	edac_dbg(0, "\n");

	if (i82875p_setup_ovewfw_dev(pdev, &ovwfw_pdev, &ovwfw_window))
		wetuwn -ENODEV;
	dwc = weadw(ovwfw_window + I82875P_DWC);
	nw_chans = duaw_channew_active(dwc) + 1;

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = I82875P_NW_CSWOWS(nw_chans);
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = nw_chans;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (!mci) {
		wc = -ENOMEM;
		goto faiw0;
	}

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_UNKNOWN;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = i82875p_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82875p_check;
	mci->ctw_page_to_phys = NUWW;
	edac_dbg(3, "init pvt\n");
	pvt = (stwuct i82875p_pvt *)mci->pvt_info;
	pvt->ovwfw_pdev = ovwfw_pdev;
	pvt->ovwfw_window = ovwfw_window;
	i82875p_init_cswows(mci, pdev, ovwfw_window, dwc);
	i82875p_get_ewwow_info(mci, &discawd);	/* cweaw countews */

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw1;
	}

	/* awwocating genewic PCI contwow info */
	i82875p_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!i82875p_pci) {
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
	edac_mc_fwee(mci);

faiw0:
	iounmap(ovwfw_window);
	pci_wewease_wegions(ovwfw_pdev);

	pci_disabwe_device(ovwfw_pdev);
	/* NOTE: the ovwfw pwoc entwy and pci_dev awe intentionawwy weft */
	wetuwn wc;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int i82875p_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "\n");
	i82875p_pwintk(KEWN_INFO, "i82875p init one\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = i82875p_pwobe1(pdev, ent->dwivew_data);

	if (mci_pdev == NUWW)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void i82875p_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct i82875p_pvt *pvt = NUWW;

	edac_dbg(0, "\n");

	if (i82875p_pci)
		edac_pci_wewease_genewic_ctw(i82875p_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	pvt = (stwuct i82875p_pvt *)mci->pvt_info;

	if (pvt->ovwfw_window)
		iounmap(pvt->ovwfw_window);

	if (pvt->ovwfw_pdev) {
#ifdef COWWECT_BIOS
		pci_wewease_wegions(pvt->ovwfw_pdev);
#endif				/*COWWECT_BIOS */
		pci_disabwe_device(pvt->ovwfw_pdev);
		pci_dev_put(pvt->ovwfw_pdev);
	}

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id i82875p_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, 82875_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I82875P},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i82875p_pci_tbw);

static stwuct pci_dwivew i82875p_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = i82875p_init_one,
	.wemove = i82875p_wemove_one,
	.id_tabwe = i82875p_pci_tbw,
};

static int __init i82875p_init(void)
{
	int pci_wc;

	edac_dbg(3, "\n");

       /* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
       opstate_init();

	pci_wc = pci_wegistew_dwivew(&i82875p_dwivew);

	if (pci_wc < 0)
		goto faiw0;

	if (mci_pdev == NUWW) {
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
					PCI_DEVICE_ID_INTEW_82875_0, NUWW);

		if (!mci_pdev) {
			edac_dbg(0, "875p pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = i82875p_init_one(mci_pdev, i82875p_pci_tbw);

		if (pci_wc < 0) {
			edac_dbg(0, "875p init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&i82875p_dwivew);

faiw0:
	pci_dev_put(mci_pdev);
	wetuwn pci_wc;
}

static void __exit i82875p_exit(void)
{
	edac_dbg(3, "\n");

	i82875p_wemove_one(mci_pdev);
	pci_dev_put(mci_pdev);

	pci_unwegistew_dwivew(&i82875p_dwivew);

}

moduwe_init(i82875p_init);
moduwe_exit(i82875p_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winux Netwowx (http://wnxi.com) Thayne Hawbaugh");
MODUWE_DESCWIPTION("MC suppowt fow Intew 82875 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
