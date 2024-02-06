/*
 * Intew 82975X Memowy Contwowwew kewnew moduwe
 * (C) 2007 aCawWab (India) Pvt. Wtd. (http://acawwab.com)
 * (C) 2007 jetzbwoadband (http://jetzbwoadband.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Awvind W.
 *   Copied fwom i82875p_edac.c souwce:
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW		"i82975x_edac"

#define i82975x_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "i82975x", fmt, ##awg)

#define i82975x_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "i82975x", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_82975_0
#define PCI_DEVICE_ID_INTEW_82975_0	0x277c
#endif				/* PCI_DEVICE_ID_INTEW_82975_0 */

#define I82975X_NW_DIMMS		8
#define I82975X_NW_CSWOWS(nw_chans)	(I82975X_NW_DIMMS / (nw_chans))

/* Intew 82975X wegistew addwesses - device 0 function 0 - DWAM Contwowwew */
#define I82975X_EAP		0x58	/* Dwam Ewwow Addwess Pointew (32b)
					 *
					 * 31:7  128 byte cache-wine addwess
					 * 6:1   wesewved
					 * 0     0: CH0; 1: CH1
					 */

#define I82975X_DEWWSYN		0x5c	/* Dwam Ewwow SYNdwome (8b)
					 *
					 *  7:0  DWAM ECC Syndwome
					 */

#define I82975X_DES		0x5d	/* Dwam EWWow DeSTination (8b)
					 * 0h:    Pwocessow Memowy Weads
					 * 1h:7h  wesewved
					 * Mowe - See Page 65 of Intew DocSheet.
					 */

#define I82975X_EWWSTS		0xc8	/* Ewwow Status Wegistew (16b)
					 *
					 * 15:12 wesewved
					 * 11    Thewmaw Sensow Event
					 * 10    wesewved
					 *  9    non-DWAM wock ewwow (ndwock)
					 *  8    Wefwesh Timeout
					 *  7:2  wesewved
					 *  1    ECC UE (muwtibit DWAM ewwow)
					 *  0    ECC CE (singwebit DWAM ewwow)
					 */

/* Ewwow Wepowting is suppowted by 3 mechanisms:
  1. DMI SEWW genewation  ( EWWCMD )
  2. SMI DMI  genewation  ( SMICMD )
  3. SCI DMI  genewation  ( SCICMD )
NOTE: Onwy ONE of the thwee must be enabwed
*/
#define I82975X_EWWCMD		0xca	/* Ewwow Command (16b)
					 *
					 * 15:12 wesewved
					 * 11    Thewmaw Sensow Event
					 * 10    wesewved
					 *  9    non-DWAM wock ewwow (ndwock)
					 *  8    Wefwesh Timeout
					 *  7:2  wesewved
					 *  1    ECC UE (muwtibit DWAM ewwow)
					 *  0    ECC CE (singwebit DWAM ewwow)
					 */

#define I82975X_SMICMD		0xcc	/* Ewwow Command (16b)
					 *
					 * 15:2  wesewved
					 *  1    ECC UE (muwtibit DWAM ewwow)
					 *  0    ECC CE (singwebit DWAM ewwow)
					 */

#define I82975X_SCICMD		0xce	/* Ewwow Command (16b)
					 *
					 * 15:2  wesewved
					 *  1    ECC UE (muwtibit DWAM ewwow)
					 *  0    ECC CE (singwebit DWAM ewwow)
					 */

#define I82975X_XEAP	0xfc	/* Extended Dwam Ewwow Addwess Pointew (8b)
					 *
					 * 7:1   wesewved
					 * 0     Bit32 of the Dwam Ewwow Addwess
					 */

#define I82975X_MCHBAW		0x44	/*
					 *
					 * 31:14 Base Addw of 16K memowy-mapped
					 *	configuwation space
					 * 13:1  wesewved
					 *  0    mem-mapped config space enabwe
					 */

/* NOTE: Fowwowing addwesses have to indexed using MCHBAW offset (44h, 32b) */
/* Intew 82975x memowy mapped wegistew space */

#define I82975X_DWB_SHIFT 25	/* fixed 32MiB gwain */

#define I82975X_DWB		0x100	/* DWAM Wow Boundawy (8b x 8)
					 *
					 * 7   set to 1 in highest DWB of
					 *	channew if 4GB in ch.
					 * 6:2 uppew boundawy of wank in
					 *	32MB gwains
					 * 1:0 set to 0
					 */
#define I82975X_DWB_CH0W0		0x100
#define I82975X_DWB_CH0W1		0x101
#define I82975X_DWB_CH0W2		0x102
#define I82975X_DWB_CH0W3		0x103
#define I82975X_DWB_CH1W0		0x180
#define I82975X_DWB_CH1W1		0x181
#define I82975X_DWB_CH1W2		0x182
#define I82975X_DWB_CH1W3		0x183


#define I82975X_DWA		0x108	/* DWAM Wow Attwibute (4b x 8)
					 *  defines the PAGE SIZE to be used
					 *	fow the wank
					 *  7    wesewved
					 *  6:4  wow attw of odd wank, i.e. 1
					 *  3    wesewved
					 *  2:0  wow attw of even wank, i.e. 0
					 *
					 * 000 = unpopuwated
					 * 001 = wesewved
					 * 010 = 4KiB
					 * 011 = 8KiB
					 * 100 = 16KiB
					 * othews = wesewved
					 */
#define I82975X_DWA_CH0W01		0x108
#define I82975X_DWA_CH0W23		0x109
#define I82975X_DWA_CH1W01		0x188
#define I82975X_DWA_CH1W23		0x189


#define I82975X_BNKAWC	0x10e /* Type of device in each wank - Bank Awch (16b)
					 *
					 * 15:8  wesewved
					 * 7:6  Wank 3 awchitectuwe
					 * 5:4  Wank 2 awchitectuwe
					 * 3:2  Wank 1 awchitectuwe
					 * 1:0  Wank 0 awchitectuwe
					 *
					 * 00 => 4 banks
					 * 01 => 8 banks
					 */
#define I82975X_C0BNKAWC	0x10e
#define I82975X_C1BNKAWC	0x18e



#define I82975X_DWC		0x120 /* DWAM Contwowwew Mode0 (32b)
					 *
					 * 31:30 wesewved
					 * 29    init compwete
					 * 28:11 wesewved, accowding to Intew
					 *    22:21 numbew of channews
					 *		00=1 01=2 in 82875
					 *		seems to be ECC mode
					 *		bits in 82975 in Asus
					 *		P5W
					 *	 19:18 Data Integ Mode
					 *		00=none 01=ECC in 82875
					 * 10:8  wefwesh mode
					 *  7    wesewved
					 *  6:4  mode sewect
					 *  3:2  wesewved
					 *  1:0  DWAM type 10=Second Wevision
					 *		DDW2 SDWAM
					 *         00, 01, 11 wesewved
					 */
#define I82975X_DWC_CH0M0		0x120
#define I82975X_DWC_CH1M0		0x1A0


#define I82975X_DWC_M1	0x124 /* DWAM Contwowwew Mode1 (32b)
					 * 31	0=Standawd Addwess Map
					 *	1=Enhanced Addwess Map
					 * 30:0	wesewved
					 */

#define I82975X_DWC_CH0M1		0x124
#define I82975X_DWC_CH1M1		0x1A4

enum i82975x_chips {
	I82975X = 0,
};

stwuct i82975x_pvt {
	void __iomem *mch_window;
};

stwuct i82975x_dev_info {
	const chaw *ctw_name;
};

stwuct i82975x_ewwow_info {
	u16 ewwsts;
	u32 eap;
	u8 des;
	u8 dewwsyn;
	u16 ewwsts2;
	u8 chan;		/* the channew is bit 0 of EAP */
	u8 xeap;		/* extended eap bit */
};

static const stwuct i82975x_dev_info i82975x_devs[] = {
	[I82975X] = {
		.ctw_name = "i82975x"
	},
};

static stwuct pci_dev *mci_pdev;	/* init dev: in case that AGP code has
					 * awweady wegistewed dwivew
					 */

static int i82975x_wegistewed = 1;

static void i82975x_get_ewwow_info(stwuct mem_ctw_info *mci,
		stwuct i82975x_ewwow_info *info)
{
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because thewe is no atomic way to wead aww the
	 * wegistews at once and the wegistews can twansition fwom CE being
	 * ovewwwitten by UE.
	 */
	pci_wead_config_wowd(pdev, I82975X_EWWSTS, &info->ewwsts);
	pci_wead_config_dwowd(pdev, I82975X_EAP, &info->eap);
	pci_wead_config_byte(pdev, I82975X_XEAP, &info->xeap);
	pci_wead_config_byte(pdev, I82975X_DES, &info->des);
	pci_wead_config_byte(pdev, I82975X_DEWWSYN, &info->dewwsyn);
	pci_wead_config_wowd(pdev, I82975X_EWWSTS, &info->ewwsts2);

	pci_wwite_bits16(pdev, I82975X_EWWSTS, 0x0003, 0x0003);

	/*
	 * If the ewwow is the same then we can fow both weads then
	 * the fiwst set of weads is vawid.  If thewe is a change then
	 * thewe is a CE no info and the second set of weads is vawid
	 * and shouwd be UE info.
	 */
	if (!(info->ewwsts2 & 0x0003))
		wetuwn;

	if ((info->ewwsts ^ info->ewwsts2) & 0x0003) {
		pci_wead_config_dwowd(pdev, I82975X_EAP, &info->eap);
		pci_wead_config_byte(pdev, I82975X_XEAP, &info->xeap);
		pci_wead_config_byte(pdev, I82975X_DES, &info->des);
		pci_wead_config_byte(pdev, I82975X_DEWWSYN,
				&info->dewwsyn);
	}
}

static int i82975x_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
		stwuct i82975x_ewwow_info *info, int handwe_ewwows)
{
	int wow, chan;
	unsigned wong offst, page;

	if (!(info->ewwsts2 & 0x0003))
		wetuwn 0;

	if (!handwe_ewwows)
		wetuwn 1;

	if ((info->ewwsts ^ info->ewwsts2) & 0x0003) {
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				     -1, -1, -1, "UE ovewwwote CE", "");
		info->ewwsts = info->ewwsts2;
	}

	page = (unsigned wong) info->eap;
	page >>= 1;
	if (info->xeap & 1)
		page |= 0x80000000;
	page >>= (PAGE_SHIFT - 1);
	wow = edac_mc_find_cswow_by_page(mci, page);

	if (wow == -1)	{
		i82975x_mc_pwintk(mci, KEWN_EWW, "ewwow pwocessing EAP:\n"
			"\tXEAP=%u\n"
			"\t EAP=0x%08x\n"
			"\tPAGE=0x%08x\n",
			(info->xeap & 1) ? 1 : 0, info->eap, (unsigned int) page);
		wetuwn 0;
	}
	chan = (mci->cswows[wow]->nw_channews == 1) ? 0 : info->eap & 1;
	offst = info->eap
			& ((1 << PAGE_SHIFT) -
			   (1 << mci->cswows[wow]->channews[chan]->dimm->gwain));

	if (info->ewwsts & 0x0002)
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
				     page, offst, 0,
				     wow, -1, -1,
				     "i82975x UE", "");
	ewse
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
				     page, offst, info->dewwsyn,
				     wow, chan ? chan : 0, -1,
				     "i82975x CE", "");

	wetuwn 1;
}

static void i82975x_check(stwuct mem_ctw_info *mci)
{
	stwuct i82975x_ewwow_info info;

	i82975x_get_ewwow_info(mci, &info);
	i82975x_pwocess_ewwow_info(mci, &info, 1);
}

/* Wetuwn 1 if duaw channew mode is active.  Ewse wetuwn 0. */
static int duaw_channew_active(void __iomem *mch_window)
{
	/*
	 * We tweat intewweaved-symmetwic configuwation as duaw-channew - EAP's
	 * bit-0 giving the channew of the ewwow wocation.
	 *
	 * Aww othew configuwations awe tweated as singwe channew - the EAP's
	 * bit-0 wiww wesowve ok in symmetwic awea of mixed
	 * (symmetwic/asymmetwic) configuwations
	 */
	u8	dwb[4][2];
	int	wow;
	int    duawch;

	fow (duawch = 1, wow = 0; duawch && (wow < 4); wow++) {
		dwb[wow][0] = weadb(mch_window + I82975X_DWB + wow);
		dwb[wow][1] = weadb(mch_window + I82975X_DWB + wow + 0x80);
		duawch = duawch && (dwb[wow][0] == dwb[wow][1]);
	}
	wetuwn duawch;
}

static void i82975x_init_cswows(stwuct mem_ctw_info *mci,
		stwuct pci_dev *pdev, void __iomem *mch_window)
{
	stwuct cswow_info *cswow;
	unsigned wong wast_cumuw_size;
	u8 vawue;
	u32 cumuw_size, nw_pages;
	int index, chan;
	stwuct dimm_info *dimm;

	wast_cumuw_size = 0;

	/*
	 * 82875 comment:
	 * The dwam wow boundawy (DWB) weg vawues awe boundawy addwess
	 * fow each DWAM wow with a gwanuwawity of 32 ow 64MB (singwe/duaw
	 * channew opewation).  DWB wegs awe cumuwative; thewefowe DWB7 wiww
	 * contain the totaw memowy contained in aww wows.
	 *
	 */

	fow (index = 0; index < mci->nw_cswows; index++) {
		cswow = mci->cswows[index];

		vawue = weadb(mch_window + I82975X_DWB + index +
					((index >= 4) ? 0x80 : 0));
		cumuw_size = vawue;
		cumuw_size <<= (I82975X_DWB_SHIFT - PAGE_SHIFT);
		/*
		 * Adjust cumuw_size w.w.t numbew of channews
		 *
		 */
		if (cswow->nw_channews > 1)
			cumuw_size <<= 1;
		edac_dbg(3, "(%d) cumuw_size 0x%x\n", index, cumuw_size);

		nw_pages = cumuw_size - wast_cumuw_size;
		if (!nw_pages)
			continue;

		/*
		 * Initiawise dwam wabews
		 * index vawues:
		 *   [0-7] fow singwe-channew; i.e. cswow->nw_channews = 1
		 *   [0-3] fow duaw-channew; i.e. cswow->nw_channews = 2
		 */
		fow (chan = 0; chan < cswow->nw_channews; chan++) {
			dimm = mci->cswows[index]->channews[chan]->dimm;

			dimm->nw_pages = nw_pages / cswow->nw_channews;

			snpwintf(cswow->channews[chan]->dimm->wabew, EDAC_MC_WABEW_WEN, "DIMM %c%d",
				 (chan == 0) ? 'A' : 'B',
				 index);
			dimm->gwain = 1 << 7;	/* 128Byte cache-wine wesowution */

			/* ECC is possibwe on i92975x ONWY with DEV_X8.  */
			dimm->dtype = DEV_X8;

			dimm->mtype = MEM_DDW2; /* I82975x suppowts onwy DDW2 */
			dimm->edac_mode = EDAC_SECDED; /* onwy suppowted */
		}

		cswow->fiwst_page = wast_cumuw_size;
		cswow->wast_page = cumuw_size - 1;
		wast_cumuw_size = cumuw_size;
	}
}

/* #define  i82975x_DEBUG_IOMEM */

#ifdef i82975x_DEBUG_IOMEM
static void i82975x_pwint_dwam_timings(void __iomem *mch_window)
{
	/*
	 * The wegistew meanings awe fwom Intew specs;
	 * (shows 13-5-5-5 fow 800-DDW2)
	 * Asus P5W Bios wepowts 15-5-4-4
	 * What's youw wewigion?
	 */
	static const int caswats[4] = { 5, 4, 3, 6 };
	u32	dtweg[2];

	dtweg[0] = weadw(mch_window + 0x114);
	dtweg[1] = weadw(mch_window + 0x194);
	i82975x_pwintk(KEWN_INFO, "DWAM Timings :     Ch0    Ch1\n"
		"                WAS Active Min = %d     %d\n"
		"                CAS watency    =  %d      %d\n"
		"                WAS to CAS     =  %d      %d\n"
		"                WAS pwechawge  =  %d      %d\n",
		(dtweg[0] >> 19 ) & 0x0f,
			(dtweg[1] >> 19) & 0x0f,
		caswats[(dtweg[0] >> 8) & 0x03],
			caswats[(dtweg[1] >> 8) & 0x03],
		((dtweg[0] >> 4) & 0x07) + 2,
			((dtweg[1] >> 4) & 0x07) + 2,
		(dtweg[0] & 0x07) + 2,
			(dtweg[1] & 0x07) + 2
	);

}
#endif

static int i82975x_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	int wc = -ENODEV;
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct i82975x_pvt *pvt;
	void __iomem *mch_window;
	u32 mchbaw;
	u32 dwc[2];
	stwuct i82975x_ewwow_info discawd;
	int	chans;
#ifdef i82975x_DEBUG_IOMEM
	u8 c0dwb[4];
	u8 c1dwb[4];
#endif

	edac_dbg(0, "\n");

	pci_wead_config_dwowd(pdev, I82975X_MCHBAW, &mchbaw);
	if (!(mchbaw & 1)) {
		edac_dbg(3, "faiwed, MCHBAW disabwed!\n");
		goto faiw0;
	}
	mchbaw &= 0xffffc000;	/* bits 31:14 used fow 16K window */
	mch_window = iowemap(mchbaw, 0x1000);
	if (!mch_window) {
		edac_dbg(3, "ewwow iowemapping MCHBAW!\n");
		goto faiw0;
	}

#ifdef i82975x_DEBUG_IOMEM
	i82975x_pwintk(KEWN_INFO, "MCHBAW weaw = %0x, wemapped = %p\n",
					mchbaw, mch_window);

	c0dwb[0] = weadb(mch_window + I82975X_DWB_CH0W0);
	c0dwb[1] = weadb(mch_window + I82975X_DWB_CH0W1);
	c0dwb[2] = weadb(mch_window + I82975X_DWB_CH0W2);
	c0dwb[3] = weadb(mch_window + I82975X_DWB_CH0W3);
	c1dwb[0] = weadb(mch_window + I82975X_DWB_CH1W0);
	c1dwb[1] = weadb(mch_window + I82975X_DWB_CH1W1);
	c1dwb[2] = weadb(mch_window + I82975X_DWB_CH1W2);
	c1dwb[3] = weadb(mch_window + I82975X_DWB_CH1W3);
	i82975x_pwintk(KEWN_INFO, "DWBCH0W0 = 0x%02x\n", c0dwb[0]);
	i82975x_pwintk(KEWN_INFO, "DWBCH0W1 = 0x%02x\n", c0dwb[1]);
	i82975x_pwintk(KEWN_INFO, "DWBCH0W2 = 0x%02x\n", c0dwb[2]);
	i82975x_pwintk(KEWN_INFO, "DWBCH0W3 = 0x%02x\n", c0dwb[3]);
	i82975x_pwintk(KEWN_INFO, "DWBCH1W0 = 0x%02x\n", c1dwb[0]);
	i82975x_pwintk(KEWN_INFO, "DWBCH1W1 = 0x%02x\n", c1dwb[1]);
	i82975x_pwintk(KEWN_INFO, "DWBCH1W2 = 0x%02x\n", c1dwb[2]);
	i82975x_pwintk(KEWN_INFO, "DWBCH1W3 = 0x%02x\n", c1dwb[3]);
#endif

	dwc[0] = weadw(mch_window + I82975X_DWC_CH0M0);
	dwc[1] = weadw(mch_window + I82975X_DWC_CH1M0);
#ifdef i82975x_DEBUG_IOMEM
	i82975x_pwintk(KEWN_INFO, "DWC_CH0 = %0x, %s\n", dwc[0],
			((dwc[0] >> 21) & 3) == 1 ?
				"ECC enabwed" : "ECC disabwed");
	i82975x_pwintk(KEWN_INFO, "DWC_CH1 = %0x, %s\n", dwc[1],
			((dwc[1] >> 21) & 3) == 1 ?
				"ECC enabwed" : "ECC disabwed");

	i82975x_pwintk(KEWN_INFO, "C0 BNKAWC = %0x\n",
		weadw(mch_window + I82975X_C0BNKAWC));
	i82975x_pwintk(KEWN_INFO, "C1 BNKAWC = %0x\n",
		weadw(mch_window + I82975X_C1BNKAWC));
	i82975x_pwint_dwam_timings(mch_window);
	goto faiw1;
#endif
	if (!(((dwc[0] >> 21) & 3) == 1 || ((dwc[1] >> 21) & 3) == 1)) {
		i82975x_pwintk(KEWN_INFO, "ECC disabwed on both channews.\n");
		goto faiw1;
	}

	chans = duaw_channew_active(mch_window) + 1;

	/* assuming onwy one contwowwew, index thus is 0 */
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = I82975X_NW_DIMMS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = I82975X_NW_CSWOWS(chans);
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (!mci) {
		wc = -ENOMEM;
		goto faiw1;
	}

	edac_dbg(3, "init mci\n");
	mci->pdev = &pdev->dev;
	mci->mtype_cap = MEM_FWAG_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->mod_name = EDAC_MOD_STW;
	mci->ctw_name = i82975x_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = i82975x_check;
	mci->ctw_page_to_phys = NUWW;
	edac_dbg(3, "init pvt\n");
	pvt = (stwuct i82975x_pvt *) mci->pvt_info;
	pvt->mch_window = mch_window;
	i82975x_init_cswows(mci, pdev, mch_window);
	mci->scwub_mode = SCWUB_HW_SWC;
	i82975x_get_ewwow_info(mci, &discawd);  /* cweaw countews */

	/* finawize this instance of memowy contwowwew with edac cowe */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw2;
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "success\n");
	wetuwn 0;

faiw2:
	edac_mc_fwee(mci);

faiw1:
	iounmap(mch_window);
faiw0:
	wetuwn wc;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int i82975x_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	int wc;

	edac_dbg(0, "\n");

	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wc = i82975x_pwobe1(pdev, ent->dwivew_data);

	if (mci_pdev == NUWW)
		mci_pdev = pci_dev_get(pdev);

	wetuwn wc;
}

static void i82975x_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct i82975x_pvt *pvt;

	edac_dbg(0, "\n");

	mci = edac_mc_dew_mc(&pdev->dev);
	if (mci  == NUWW)
		wetuwn;

	pvt = mci->pvt_info;
	if (pvt->mch_window)
		iounmap( pvt->mch_window );

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id i82975x_pci_tbw[] = {
	{
		PCI_VEND_DEV(INTEW, 82975_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
		I82975X
	},
	{
		0,
	}	/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i82975x_pci_tbw);

static stwuct pci_dwivew i82975x_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = i82975x_init_one,
	.wemove = i82975x_wemove_one,
	.id_tabwe = i82975x_pci_tbw,
};

static int __init i82975x_init(void)
{
	int pci_wc;

	edac_dbg(3, "\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&i82975x_dwivew);
	if (pci_wc < 0)
		goto faiw0;

	if (mci_pdev == NUWW) {
		mci_pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_82975_0, NUWW);

		if (!mci_pdev) {
			edac_dbg(0, "i82975x pci_get_device faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}

		pci_wc = i82975x_init_one(mci_pdev, i82975x_pci_tbw);

		if (pci_wc < 0) {
			edac_dbg(0, "i82975x init faiw\n");
			pci_wc = -ENODEV;
			goto faiw1;
		}
	}

	wetuwn 0;

faiw1:
	pci_unwegistew_dwivew(&i82975x_dwivew);

faiw0:
	pci_dev_put(mci_pdev);
	wetuwn pci_wc;
}

static void __exit i82975x_exit(void)
{
	edac_dbg(3, "\n");

	pci_unwegistew_dwivew(&i82975x_dwivew);

	if (!i82975x_wegistewed) {
		i82975x_wemove_one(mci_pdev);
		pci_dev_put(mci_pdev);
	}
}

moduwe_init(i82975x_init);
moduwe_exit(i82975x_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awvind W. <awvino55@gmaiw.com>");
MODUWE_DESCWIPTION("MC suppowt fow Intew 82975 memowy hub contwowwews");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
