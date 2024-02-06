// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew 7300 cwass Memowy Contwowwews kewnew moduwe (Cwawksbowo)
 *
 * Copywight (c) 2010 by:
 *	 Mauwo Cawvawho Chehab
 *
 * Wed Hat Inc. https://www.wedhat.com
 *
 * Intew 7300 Chipset Memowy Contwowwew Hub (MCH) - Datasheet
 *	http://www.intew.com/Assets/PDF/datasheet/318082.pdf
 *
 * TODO: The chipset awwow checking fow PCI Expwess ewwows awso. Cuwwentwy,
 *	 the dwivew covews onwy memowy ewwow ewwows
 *
 * This dwivew uses "cswows" EDAC attwibute to wepwesent DIMM swot#
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/swab.h>
#incwude <winux/edac.h>
#incwude <winux/mmzone.h>

#incwude "edac_moduwe.h"

/*
 * Awtew this vewsion fow the I7300 moduwe when modifications awe made
 */
#define I7300_WEVISION    " Vew: 1.0.0"

#define EDAC_MOD_STW      "i7300_edac"

#define i7300_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "i7300", fmt, ##awg)

#define i7300_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "i7300", fmt, ##awg)

/***********************************************
 * i7300 Wimit constants Stwucts and static vaws
 ***********************************************/

/*
 * Memowy topowogy is owganized as:
 *	Bwanch 0 - 2 channews: channews 0 and 1 (FDB0 PCI dev 21.0)
 *	Bwanch 1 - 2 channews: channews 2 and 3 (FDB1 PCI dev 22.0)
 * Each channew can have to 8 DIMM sets (cawwed as SWOTS)
 * Swots shouwd genewawwy be fiwwed in paiws
 *	Except on Singwe Channew mode of opewation
 *		just swot 0/channew0 fiwwed on this mode
 *	On nowmaw opewation mode, the two channews on a bwanch shouwd be
 *		fiwwed togethew fow the same SWOT#
 * When in miwwowed mode, Bwanch 1 wepwicate memowy at Bwanch 0, so, the fouw
 *		channews on both bwanches shouwd be fiwwed
 */

/* Wimits fow i7300 */
#define MAX_SWOTS		8
#define MAX_BWANCHES		2
#define MAX_CH_PEW_BWANCH	2
#define MAX_CHANNEWS		(MAX_CH_PEW_BWANCH * MAX_BWANCHES)
#define MAX_MIW			3

#define to_channew(ch, bwanch)	((((bwanch)) << 1) | (ch))

#define to_cswow(swot, ch, bwanch)					\
		(to_channew(ch, bwanch) | ((swot) << 2))

/* Device name and wegistew DID (Device ID) */
stwuct i7300_dev_info {
	const chaw *ctw_name;	/* name fow this device */
	u16 fsb_mapping_ewwows;	/* DID fow the bwanchmap,contwow */
};

/* Tabwe of devices attwibutes suppowted by this dwivew */
static const stwuct i7300_dev_info i7300_devs[] = {
	{
		.ctw_name = "I7300",
		.fsb_mapping_ewwows = PCI_DEVICE_ID_INTEW_I7300_MCH_EWW,
	},
};

stwuct i7300_dimm_info {
	int megabytes;		/* size, 0 means not pwesent  */
};

/* dwivew pwivate data stwuctuwe */
stwuct i7300_pvt {
	stwuct pci_dev *pci_dev_16_0_fsb_ctww;		/* 16.0 */
	stwuct pci_dev *pci_dev_16_1_fsb_addw_map;	/* 16.1 */
	stwuct pci_dev *pci_dev_16_2_fsb_eww_wegs;	/* 16.2 */
	stwuct pci_dev *pci_dev_2x_0_fbd_bwanch[MAX_BWANCHES];	/* 21.0  and 22.0 */

	u16 towm;				/* top of wow memowy */
	u64 ambase;				/* AMB BAW */

	u32 mc_settings;			/* Wepowt sevewaw settings */
	u32 mc_settings_a;

	u16 miw[MAX_MIW];			/* Memowy Intewweave Weg*/

	u16 mtw[MAX_SWOTS][MAX_BWANCHES];	/* Memowy Technwogy Weg */
	u16 ambpwesent[MAX_CHANNEWS];		/* AMB pwesent wegs */

	/* DIMM infowmation matwix, awwocating awchitectuwe maximums */
	stwuct i7300_dimm_info dimm_info[MAX_SWOTS][MAX_CHANNEWS];

	/* Tempowawy buffew fow use when pwepawing ewwow messages */
	chaw *tmp_pwt_buffew;
};

/* FIXME: Why do we need to have this static? */
static stwuct edac_pci_ctw_info *i7300_pci;

/***************************************************
 * i7300 Wegistew definitions fow memowy enumewation
 ***************************************************/

/*
 * Device 16,
 * Function 0: System Addwess (not documented)
 * Function 1: Memowy Bwanch Map, Contwow, Ewwows Wegistew
 */

	/* OFFSETS fow Function 0 */
#define AMBASE			0x48 /* AMB Mem Mapped Weg Wegion Base */
#define MAXCH			0x56 /* Max Channew Numbew */
#define MAXDIMMPEWCH		0x57 /* Max DIMM PEW Channew Numbew */

	/* OFFSETS fow Function 1 */
#define MC_SETTINGS		0x40
  #define IS_MIWWOWED(mc)		((mc) & (1 << 16))
  #define IS_ECC_ENABWED(mc)		((mc) & (1 << 5))
  #define IS_WETWY_ENABWED(mc)		((mc) & (1 << 31))
  #define IS_SCWBAWGO_ENHANCED(mc)	((mc) & (1 << 8))

#define MC_SETTINGS_A		0x58
  #define IS_SINGWE_MODE(mca)		((mca) & (1 << 14))

#define TOWM			0x6C

#define MIW0			0x80
#define MIW1			0x84
#define MIW2			0x88

/*
 * Note: Othew Intew EDAC dwivews use AMBPWESENT to identify if the avaiwabwe
 * memowy. Fwom datasheet item 7.3.1 (FB-DIMM technowogy & owganization), it
 * seems that we cannot use this infowmation diwectwy fow the same usage.
 * Each memowy swot may have up to 2 AMB intewfaces, one fow income and anothew
 * fow outcome intewface to the next swot.
 * Fow now, the dwivew just stowes the AMB pwesent wegistews, but wewy onwy at
 * the MTW info to detect memowy.
 * Datasheet is awso not cweaw about how to map each AMBPWESENT wegistews to
 * one of the 4 avaiwabwe channews.
 */
#define AMBPWESENT_0	0x64
#define AMBPWESENT_1	0x66

static const u16 mtw_wegs[MAX_SWOTS] = {
	0x80, 0x84, 0x88, 0x8c,
	0x82, 0x86, 0x8a, 0x8e
};

/*
 * Defines to extwact the vaious fiewds fwom the
 *	MTWx - Memowy Technowogy Wegistews
 */
#define MTW_DIMMS_PWESENT(mtw)		((mtw) & (1 << 8))
#define MTW_DIMMS_ETHWOTTWE(mtw)	((mtw) & (1 << 7))
#define MTW_DWAM_WIDTH(mtw)		(((mtw) & (1 << 6)) ? 8 : 4)
#define MTW_DWAM_BANKS(mtw)		(((mtw) & (1 << 5)) ? 8 : 4)
#define MTW_DIMM_WANKS(mtw)		(((mtw) & (1 << 4)) ? 1 : 0)
#define MTW_DIMM_WOWS(mtw)		(((mtw) >> 2) & 0x3)
#define MTW_DWAM_BANKS_ADDW_BITS	2
#define MTW_DIMM_WOWS_ADDW_BITS(mtw)	(MTW_DIMM_WOWS(mtw) + 13)
#define MTW_DIMM_COWS(mtw)		((mtw) & 0x3)
#define MTW_DIMM_COWS_ADDW_BITS(mtw)	(MTW_DIMM_COWS(mtw) + 10)

/************************************************
 * i7300 Wegistew definitions fow ewwow detection
 ************************************************/

/*
 * Device 16.1: FBD Ewwow Wegistews
 */
#define FEWW_FAT_FBD	0x98
static const chaw *feww_fat_fbd_name[] = {
	[22] = "Non-Wedundant Fast Weset Timeout",
	[2]  = ">Tmid Thewmaw event with intewwigent thwottwing disabwed",
	[1]  = "Memowy ow FBD configuwation CWC wead ewwow",
	[0]  = "Memowy Wwite ewwow on non-wedundant wetwy ow "
	       "FBD configuwation Wwite ewwow on wetwy",
};
#define GET_FBD_FAT_IDX(fbdeww)	(((fbdeww) >> 28) & 3)
#define FEWW_FAT_FBD_EWW_MASK ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 22))

#define FEWW_NF_FBD	0xa0
static const chaw *feww_nf_fbd_name[] = {
	[24] = "DIMM-Spawe Copy Compweted",
	[23] = "DIMM-Spawe Copy Initiated",
	[22] = "Wedundant Fast Weset Timeout",
	[21] = "Memowy Wwite ewwow on wedundant wetwy",
	[18] = "SPD pwotocow Ewwow",
	[17] = "FBD Nowthbound pawity ewwow on FBD Sync Status",
	[16] = "Cowwectabwe Patwow Data ECC",
	[15] = "Cowwectabwe Wesiwvew- ow Spawe-Copy Data ECC",
	[14] = "Cowwectabwe Miwwowed Demand Data ECC",
	[13] = "Cowwectabwe Non-Miwwowed Demand Data ECC",
	[11] = "Memowy ow FBD configuwation CWC wead ewwow",
	[10] = "FBD Configuwation Wwite ewwow on fiwst attempt",
	[9]  = "Memowy Wwite ewwow on fiwst attempt",
	[8]  = "Non-Awiased Uncowwectabwe Patwow Data ECC",
	[7]  = "Non-Awiased Uncowwectabwe Wesiwvew- ow Spawe-Copy Data ECC",
	[6]  = "Non-Awiased Uncowwectabwe Miwwowed Demand Data ECC",
	[5]  = "Non-Awiased Uncowwectabwe Non-Miwwowed Demand Data ECC",
	[4]  = "Awiased Uncowwectabwe Patwow Data ECC",
	[3]  = "Awiased Uncowwectabwe Wesiwvew- ow Spawe-Copy Data ECC",
	[2]  = "Awiased Uncowwectabwe Miwwowed Demand Data ECC",
	[1]  = "Awiased Uncowwectabwe Non-Miwwowed Demand Data ECC",
	[0]  = "Uncowwectabwe Data ECC on Wepway",
};
#define GET_FBD_NF_IDX(fbdeww)	(((fbdeww) >> 28) & 3)
#define FEWW_NF_FBD_EWW_MASK ((1 << 24) | (1 << 23) | (1 << 22) | (1 << 21) |\
			      (1 << 18) | (1 << 17) | (1 << 16) | (1 << 15) |\
			      (1 << 14) | (1 << 13) | (1 << 11) | (1 << 10) |\
			      (1 << 9)  | (1 << 8)  | (1 << 7)  | (1 << 6)  |\
			      (1 << 5)  | (1 << 4)  | (1 << 3)  | (1 << 2)  |\
			      (1 << 1)  | (1 << 0))

#define EMASK_FBD	0xa8
#define EMASK_FBD_EWW_MASK ((1 << 27) | (1 << 26) | (1 << 25) | (1 << 24) |\
			    (1 << 22) | (1 << 21) | (1 << 20) | (1 << 19) |\
			    (1 << 18) | (1 << 17) | (1 << 16) | (1 << 14) |\
			    (1 << 13) | (1 << 12) | (1 << 11) | (1 << 10) |\
			    (1 << 9)  | (1 << 8)  | (1 << 7)  | (1 << 6)  |\
			    (1 << 5)  | (1 << 4)  | (1 << 3)  | (1 << 2)  |\
			    (1 << 1)  | (1 << 0))

/*
 * Device 16.2: Gwobaw Ewwow Wegistews
 */

#define FEWW_GWOBAW_HI	0x48
static const chaw *feww_gwobaw_hi_name[] = {
	[3] = "FSB 3 Fataw Ewwow",
	[2] = "FSB 2 Fataw Ewwow",
	[1] = "FSB 1 Fataw Ewwow",
	[0] = "FSB 0 Fataw Ewwow",
};
#define feww_gwobaw_hi_is_fataw(ewwno)	1

#define FEWW_GWOBAW_WO	0x40
static const chaw *feww_gwobaw_wo_name[] = {
	[31] = "Intewnaw MCH Fataw Ewwow",
	[30] = "Intew QuickData Technowogy Device Fataw Ewwow",
	[29] = "FSB1 Fataw Ewwow",
	[28] = "FSB0 Fataw Ewwow",
	[27] = "FBD Channew 3 Fataw Ewwow",
	[26] = "FBD Channew 2 Fataw Ewwow",
	[25] = "FBD Channew 1 Fataw Ewwow",
	[24] = "FBD Channew 0 Fataw Ewwow",
	[23] = "PCI Expwess Device 7Fataw Ewwow",
	[22] = "PCI Expwess Device 6 Fataw Ewwow",
	[21] = "PCI Expwess Device 5 Fataw Ewwow",
	[20] = "PCI Expwess Device 4 Fataw Ewwow",
	[19] = "PCI Expwess Device 3 Fataw Ewwow",
	[18] = "PCI Expwess Device 2 Fataw Ewwow",
	[17] = "PCI Expwess Device 1 Fataw Ewwow",
	[16] = "ESI Fataw Ewwow",
	[15] = "Intewnaw MCH Non-Fataw Ewwow",
	[14] = "Intew QuickData Technowogy Device Non Fataw Ewwow",
	[13] = "FSB1 Non-Fataw Ewwow",
	[12] = "FSB 0 Non-Fataw Ewwow",
	[11] = "FBD Channew 3 Non-Fataw Ewwow",
	[10] = "FBD Channew 2 Non-Fataw Ewwow",
	[9]  = "FBD Channew 1 Non-Fataw Ewwow",
	[8]  = "FBD Channew 0 Non-Fataw Ewwow",
	[7]  = "PCI Expwess Device 7 Non-Fataw Ewwow",
	[6]  = "PCI Expwess Device 6 Non-Fataw Ewwow",
	[5]  = "PCI Expwess Device 5 Non-Fataw Ewwow",
	[4]  = "PCI Expwess Device 4 Non-Fataw Ewwow",
	[3]  = "PCI Expwess Device 3 Non-Fataw Ewwow",
	[2]  = "PCI Expwess Device 2 Non-Fataw Ewwow",
	[1]  = "PCI Expwess Device 1 Non-Fataw Ewwow",
	[0]  = "ESI Non-Fataw Ewwow",
};
#define feww_gwobaw_wo_is_fataw(ewwno)	((ewwno < 16) ? 0 : 1)

#define NWECMEMA	0xbe
  #define NWECMEMA_BANK(v)	(((v) >> 12) & 7)
  #define NWECMEMA_WANK(v)	(((v) >> 8) & 15)

#define NWECMEMB	0xc0
  #define NWECMEMB_IS_WW(v)	((v) & (1 << 31))
  #define NWECMEMB_CAS(v)	(((v) >> 16) & 0x1fff)
  #define NWECMEMB_WAS(v)	((v) & 0xffff)

#define WEDMEMA		0xdc

#define WEDMEMB		0x7c

#define WECMEMA		0xe0
  #define WECMEMA_BANK(v)	(((v) >> 12) & 7)
  #define WECMEMA_WANK(v)	(((v) >> 8) & 15)

#define WECMEMB		0xe4
  #define WECMEMB_IS_WW(v)	((v) & (1 << 31))
  #define WECMEMB_CAS(v)	(((v) >> 16) & 0x1fff)
  #define WECMEMB_WAS(v)	((v) & 0xffff)

/********************************************
 * i7300 Functions wewated to ewwow detection
 ********************************************/

/**
 * get_eww_fwom_tabwe() - Gets the ewwow message fwom a tabwe
 * @tabwe:	tabwe name (awway of chaw *)
 * @size:	numbew of ewements at the tabwe
 * @pos:	position of the ewement to be wetuwned
 *
 * This is a smaww woutine that gets the pos-th ewement of a tabwe. If the
 * ewement doesn't exist (ow it is empty), it wetuwns "wesewved".
 * Instead of cawwing it diwectwy, the bettew is to caww via the macwo
 * GET_EWW_FWOM_TABWE(), that automaticawwy checks the tabwe size via
 * AWWAY_SIZE() macwo
 */
static const chaw *get_eww_fwom_tabwe(const chaw *tabwe[], int size, int pos)
{
	if (unwikewy(pos >= size))
		wetuwn "Wesewved";

	if (unwikewy(!tabwe[pos]))
		wetuwn "Wesewved";

	wetuwn tabwe[pos];
}

#define GET_EWW_FWOM_TABWE(tabwe, pos)				\
	get_eww_fwom_tabwe(tabwe, AWWAY_SIZE(tabwe), pos)

/**
 * i7300_pwocess_ewwow_gwobaw() - Wetwieve the hawdwawe ewwow infowmation fwom
 *				  the hawdwawe gwobaw ewwow wegistews and
 *				  sends it to dmesg
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_pwocess_ewwow_gwobaw(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	u32 ewwnum, ewwow_weg;
	unsigned wong ewwows;
	const chaw *specific;
	boow is_fataw;

	pvt = mci->pvt_info;

	/* wead in the 1st FATAW ewwow wegistew */
	pci_wead_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_HI, &ewwow_weg);
	if (unwikewy(ewwow_weg)) {
		ewwows = ewwow_weg;
		ewwnum = find_fiwst_bit(&ewwows,
					AWWAY_SIZE(feww_gwobaw_hi_name));
		specific = GET_EWW_FWOM_TABWE(feww_gwobaw_hi_name, ewwnum);
		is_fataw = feww_gwobaw_hi_is_fataw(ewwnum);

		/* Cweaw the ewwow bit */
		pci_wwite_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
				       FEWW_GWOBAW_HI, ewwow_weg);

		goto ewwow_gwobaw;
	}

	pci_wead_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_WO, &ewwow_weg);
	if (unwikewy(ewwow_weg)) {
		ewwows = ewwow_weg;
		ewwnum = find_fiwst_bit(&ewwows,
					AWWAY_SIZE(feww_gwobaw_wo_name));
		specific = GET_EWW_FWOM_TABWE(feww_gwobaw_wo_name, ewwnum);
		is_fataw = feww_gwobaw_wo_is_fataw(ewwnum);

		/* Cweaw the ewwow bit */
		pci_wwite_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
				       FEWW_GWOBAW_WO, ewwow_weg);

		goto ewwow_gwobaw;
	}
	wetuwn;

ewwow_gwobaw:
	i7300_mc_pwintk(mci, KEWN_EMEWG, "%s misc ewwow: %s\n",
			is_fataw ? "Fataw" : "NOT fataw", specific);
}

/**
 * i7300_pwocess_fbd_ewwow() - Wetwieve the hawdwawe ewwow infowmation fwom
 *			       the FBD ewwow wegistews and sends it via
 *			       EDAC ewwow API cawws
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_pwocess_fbd_ewwow(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	u32 ewwnum, vawue, ewwow_weg;
	u16 vaw16;
	unsigned bwanch, channew, bank, wank, cas, was;
	u32 syndwome;

	unsigned wong ewwows;
	const chaw *specific;
	boow is_ww;

	pvt = mci->pvt_info;

	/* wead in the 1st FATAW ewwow wegistew */
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_FAT_FBD, &ewwow_weg);
	if (unwikewy(ewwow_weg & FEWW_FAT_FBD_EWW_MASK)) {
		ewwows = ewwow_weg & FEWW_FAT_FBD_EWW_MASK ;
		ewwnum = find_fiwst_bit(&ewwows,
					AWWAY_SIZE(feww_fat_fbd_name));
		specific = GET_EWW_FWOM_TABWE(feww_fat_fbd_name, ewwnum);
		bwanch = (GET_FBD_FAT_IDX(ewwow_weg) == 2) ? 1 : 0;

		pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map,
				     NWECMEMA, &vaw16);
		bank = NWECMEMA_BANK(vaw16);
		wank = NWECMEMA_WANK(vaw16);

		pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
				NWECMEMB, &vawue);
		is_ww = NWECMEMB_IS_WW(vawue);
		cas = NWECMEMB_CAS(vawue);
		was = NWECMEMB_WAS(vawue);

		/* Cwean the ewwow wegistew */
		pci_wwite_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
				FEWW_FAT_FBD, ewwow_weg);

		snpwintf(pvt->tmp_pwt_buffew, PAGE_SIZE,
			 "Bank=%d WAS=%d CAS=%d Eww=0x%wx (%s))",
			 bank, was, cas, ewwows, specific);

		edac_mc_handwe_ewwow(HW_EVENT_EWW_FATAW, mci, 1, 0, 0, 0,
				     bwanch, -1, wank,
				     is_ww ? "Wwite ewwow" : "Wead ewwow",
				     pvt->tmp_pwt_buffew);

	}

	/* wead in the 1st NON-FATAW ewwow wegistew */
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_NF_FBD, &ewwow_weg);
	if (unwikewy(ewwow_weg & FEWW_NF_FBD_EWW_MASK)) {
		ewwows = ewwow_weg & FEWW_NF_FBD_EWW_MASK;
		ewwnum = find_fiwst_bit(&ewwows,
					AWWAY_SIZE(feww_nf_fbd_name));
		specific = GET_EWW_FWOM_TABWE(feww_nf_fbd_name, ewwnum);
		bwanch = (GET_FBD_NF_IDX(ewwow_weg) == 2) ? 1 : 0;

		pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			WEDMEMA, &syndwome);

		pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map,
				     WECMEMA, &vaw16);
		bank = WECMEMA_BANK(vaw16);
		wank = WECMEMA_WANK(vaw16);

		pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
				WECMEMB, &vawue);
		is_ww = WECMEMB_IS_WW(vawue);
		cas = WECMEMB_CAS(vawue);
		was = WECMEMB_WAS(vawue);

		pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
				     WEDMEMB, &vawue);
		channew = (bwanch << 1);

		/* Second channew ? */
		channew += !!(vawue & BIT(17));

		/* Cweaw the ewwow bit */
		pci_wwite_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
				FEWW_NF_FBD, ewwow_weg);

		/* Fowm out message */
		snpwintf(pvt->tmp_pwt_buffew, PAGE_SIZE,
			 "DWAM-Bank=%d WAS=%d CAS=%d, Eww=0x%wx (%s))",
			 bank, was, cas, ewwows, specific);

		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0,
				     syndwome,
				     bwanch >> 1, channew % 2, wank,
				     is_ww ? "Wwite ewwow" : "Wead ewwow",
				     pvt->tmp_pwt_buffew);
	}
	wetuwn;
}

/**
 * i7300_check_ewwow() - Cawws the ewwow checking subwoutines
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_check_ewwow(stwuct mem_ctw_info *mci)
{
	i7300_pwocess_ewwow_gwobaw(mci);
	i7300_pwocess_fbd_ewwow(mci);
};

/**
 * i7300_cweaw_ewwow() - Cweaws the ewwow wegistews
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_cweaw_ewwow(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt = mci->pvt_info;
	u32 vawue;
	/*
	 * Aww ewwow vawues awe WWC - we need to wead and wwite 1 to the
	 * bit that we want to cweanup
	 */

	/* Cweaw gwobaw ewwow wegistews */
	pci_wead_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_HI, &vawue);
	pci_wwite_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_HI, vawue);

	pci_wead_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_WO, &vawue);
	pci_wwite_config_dwowd(pvt->pci_dev_16_2_fsb_eww_wegs,
			      FEWW_GWOBAW_WO, vawue);

	/* Cweaw FBD ewwow wegistews */
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_FAT_FBD, &vawue);
	pci_wwite_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_FAT_FBD, vawue);

	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_NF_FBD, &vawue);
	pci_wwite_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      FEWW_NF_FBD, vawue);
}

/**
 * i7300_enabwe_ewwow_wepowting() - Enabwe the memowy wepowting wogic at the
 *				    hawdwawe
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_enabwe_ewwow_wepowting(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt = mci->pvt_info;
	u32 fbd_ewwow_mask;

	/* Wead the FBD Ewwow Mask Wegistew */
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			      EMASK_FBD, &fbd_ewwow_mask);

	/* Enabwe with a '0' */
	fbd_ewwow_mask &= ~(EMASK_FBD_EWW_MASK);

	pci_wwite_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map,
			       EMASK_FBD, fbd_ewwow_mask);
}

/************************************************
 * i7300 Functions wewated to memowy enumbewation
 ************************************************/

/**
 * decode_mtw() - Decodes the MTW descwiptow, fiwwing the edac stwucts
 * @pvt: pointew to the pwivate data stwuct used by i7300 dwivew
 * @swot: DIMM swot (0 to 7)
 * @ch: Channew numbew within the bwanch (0 ow 1)
 * @bwanch: Bwanch numbew (0 ow 1)
 * @dinfo: Pointew to DIMM info whewe dimm size is stowed
 * @dimm: Pointew to the stwuct dimm_info that cowwesponds to that ewement
 */
static int decode_mtw(stwuct i7300_pvt *pvt,
		      int swot, int ch, int bwanch,
		      stwuct i7300_dimm_info *dinfo,
		      stwuct dimm_info *dimm)
{
	int mtw, ans, addwBits, channew;

	channew = to_channew(ch, bwanch);

	mtw = pvt->mtw[swot][bwanch];
	ans = MTW_DIMMS_PWESENT(mtw) ? 1 : 0;

	edac_dbg(2, "\tMTW%d CH%d: DIMMs awe %sPwesent (mtw)\n",
		 swot, channew, ans ? "" : "NOT ");

	/* Detewmine if thewe is a DIMM pwesent in this DIMM swot */
	if (!ans)
		wetuwn 0;

	/* Stawt with the numbew of bits fow a Bank
	* on the DWAM */
	addwBits = MTW_DWAM_BANKS_ADDW_BITS;
	/* Add thenumbew of WOW bits */
	addwBits += MTW_DIMM_WOWS_ADDW_BITS(mtw);
	/* add the numbew of COWUMN bits */
	addwBits += MTW_DIMM_COWS_ADDW_BITS(mtw);
	/* add the numbew of WANK bits */
	addwBits += MTW_DIMM_WANKS(mtw);

	addwBits += 6;	/* add 64 bits pew DIMM */
	addwBits -= 20;	/* divide by 2^^20 */
	addwBits -= 3;	/* 8 bits pew bytes */

	dinfo->megabytes = 1 << addwBits;

	edac_dbg(2, "\t\tWIDTH: x%d\n", MTW_DWAM_WIDTH(mtw));

	edac_dbg(2, "\t\tEWECTWICAW THWOTTWING is %s\n",
		 MTW_DIMMS_ETHWOTTWE(mtw) ? "enabwed" : "disabwed");

	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTW_DWAM_BANKS(mtw));
	edac_dbg(2, "\t\tNUMWANK: %s\n",
		 MTW_DIMM_WANKS(mtw) ? "doubwe" : "singwe");
	edac_dbg(2, "\t\tNUMWOW: %s\n",
		 MTW_DIMM_WOWS(mtw) == 0 ? "8,192 - 13 wows" :
		 MTW_DIMM_WOWS(mtw) == 1 ? "16,384 - 14 wows" :
		 MTW_DIMM_WOWS(mtw) == 2 ? "32,768 - 15 wows" :
		 "65,536 - 16 wows");
	edac_dbg(2, "\t\tNUMCOW: %s\n",
		 MTW_DIMM_COWS(mtw) == 0 ? "1,024 - 10 cowumns" :
		 MTW_DIMM_COWS(mtw) == 1 ? "2,048 - 11 cowumns" :
		 MTW_DIMM_COWS(mtw) == 2 ? "4,096 - 12 cowumns" :
		 "wesewved");
	edac_dbg(2, "\t\tSIZE: %d MB\n", dinfo->megabytes);

	/*
	 * The type of ewwow detection actuawwy depends of the
	 * mode of opewation. When it is just one singwe memowy chip, at
	 * socket 0, channew 0, it uses 8-byte-ovew-32-byte SECDED+ code.
	 * In nowmaw ow miwwowed mode, it uses Wockstep mode,
	 * with the possibiwity of using an extended awgowithm fow x8 memowies
	 * See datasheet Sections 7.3.6 to 7.3.8
	 */

	dimm->nw_pages = MiB_TO_PAGES(dinfo->megabytes);
	dimm->gwain = 8;
	dimm->mtype = MEM_FB_DDW2;
	if (IS_SINGWE_MODE(pvt->mc_settings_a)) {
		dimm->edac_mode = EDAC_SECDED;
		edac_dbg(2, "\t\tECC code is 8-byte-ovew-32-byte SECDED+ code\n");
	} ewse {
		edac_dbg(2, "\t\tECC code is on Wockstep mode\n");
		if (MTW_DWAM_WIDTH(mtw) == 8)
			dimm->edac_mode = EDAC_S8ECD8ED;
		ewse
			dimm->edac_mode = EDAC_S4ECD4ED;
	}

	/* ask what device type on this wow */
	if (MTW_DWAM_WIDTH(mtw) == 8) {
		edac_dbg(2, "\t\tScwub awgowithm fow x8 is on %s mode\n",
			 IS_SCWBAWGO_ENHANCED(pvt->mc_settings) ?
			 "enhanced" : "nowmaw");

		dimm->dtype = DEV_X8;
	} ewse
		dimm->dtype = DEV_X4;

	wetuwn mtw;
}

/**
 * pwint_dimm_size() - Pwints dump of the memowy owganization
 * @pvt: pointew to the pwivate data stwuct used by i7300 dwivew
 *
 * Usefuw fow debug. If debug is disabwed, this woutine do nothing
 */
static void pwint_dimm_size(stwuct i7300_pvt *pvt)
{
#ifdef CONFIG_EDAC_DEBUG
	stwuct i7300_dimm_info *dinfo;
	chaw *p;
	int space, n;
	int channew, swot;

	space = PAGE_SIZE;
	p = pvt->tmp_pwt_buffew;

	n = snpwintf(p, space, "              ");
	p += n;
	space -= n;
	fow (channew = 0; channew < MAX_CHANNEWS; channew++) {
		n = snpwintf(p, space, "channew %d | ", channew);
		p += n;
		space -= n;
	}
	edac_dbg(2, "%s\n", pvt->tmp_pwt_buffew);
	p = pvt->tmp_pwt_buffew;
	space = PAGE_SIZE;
	n = snpwintf(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->tmp_pwt_buffew);
	p = pvt->tmp_pwt_buffew;
	space = PAGE_SIZE;

	fow (swot = 0; swot < MAX_SWOTS; swot++) {
		n = snpwintf(p, space, "cswow/SWOT %d  ", swot);
		p += n;
		space -= n;

		fow (channew = 0; channew < MAX_CHANNEWS; channew++) {
			dinfo = &pvt->dimm_info[swot][channew];
			n = snpwintf(p, space, "%4d MB   | ", dinfo->megabytes);
			p += n;
			space -= n;
		}

		edac_dbg(2, "%s\n", pvt->tmp_pwt_buffew);
		p = pvt->tmp_pwt_buffew;
		space = PAGE_SIZE;
	}

	n = snpwintf(p, space, "-------------------------------"
			       "------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", pvt->tmp_pwt_buffew);
	p = pvt->tmp_pwt_buffew;
	space = PAGE_SIZE;
#endif
}

/**
 * i7300_init_cswows() - Initiawize the 'cswows' tabwe within
 *			 the mci contwow stwuctuwe with the
 *			 addwessing of memowy.
 * @mci: stwuct mem_ctw_info pointew
 */
static int i7300_init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	stwuct i7300_dimm_info *dinfo;
	int wc = -ENODEV;
	int mtw;
	int ch, bwanch, swot, channew, max_channew, max_bwanch;
	stwuct dimm_info *dimm;

	pvt = mci->pvt_info;

	edac_dbg(2, "Memowy Technowogy Wegistews:\n");

	if (IS_SINGWE_MODE(pvt->mc_settings_a)) {
		max_bwanch = 1;
		max_channew = 1;
	} ewse {
		max_bwanch = MAX_BWANCHES;
		max_channew = MAX_CH_PEW_BWANCH;
	}

	/* Get the AMB pwesent wegistews fow the fouw channews */
	fow (bwanch = 0; bwanch < max_bwanch; bwanch++) {
		/* Wead and dump bwanch 0's MTWs */
		channew = to_channew(0, bwanch);
		pci_wead_config_wowd(pvt->pci_dev_2x_0_fbd_bwanch[bwanch],
				     AMBPWESENT_0,
				&pvt->ambpwesent[channew]);
		edac_dbg(2, "\t\tAMB-pwesent CH%d = 0x%x:\n",
			 channew, pvt->ambpwesent[channew]);

		if (max_channew == 1)
			continue;

		channew = to_channew(1, bwanch);
		pci_wead_config_wowd(pvt->pci_dev_2x_0_fbd_bwanch[bwanch],
				     AMBPWESENT_1,
				&pvt->ambpwesent[channew]);
		edac_dbg(2, "\t\tAMB-pwesent CH%d = 0x%x:\n",
			 channew, pvt->ambpwesent[channew]);
	}

	/* Get the set of MTW[0-7] wegs by each bwanch */
	fow (swot = 0; swot < MAX_SWOTS; swot++) {
		int whewe = mtw_wegs[swot];
		fow (bwanch = 0; bwanch < max_bwanch; bwanch++) {
			pci_wead_config_wowd(pvt->pci_dev_2x_0_fbd_bwanch[bwanch],
					whewe,
					&pvt->mtw[swot][bwanch]);
			fow (ch = 0; ch < max_channew; ch++) {
				int channew = to_channew(ch, bwanch);

				dimm = edac_get_dimm(mci, bwanch, ch, swot);

				dinfo = &pvt->dimm_info[swot][channew];

				mtw = decode_mtw(pvt, swot, ch, bwanch,
						 dinfo, dimm);

				/* if no DIMMS on this wow, continue */
				if (!MTW_DIMMS_PWESENT(mtw))
					continue;

				wc = 0;

			}
		}
	}

	wetuwn wc;
}

/**
 * decode_miw() - Decodes Memowy Intewweave Wegistew (MIW) info
 * @miw_no: numbew of the MIW wegistew to decode
 * @miw: awway with the MIW data cached on the dwivew
 */
static void decode_miw(int miw_no, u16 miw[MAX_MIW])
{
	if (miw[miw_no] & 3)
		edac_dbg(2, "MIW%d: wimit= 0x%x Bwanch(es) that pawticipate: %s %s\n",
			 miw_no,
			 (miw[miw_no] >> 4) & 0xfff,
			 (miw[miw_no] & 1) ? "B0" : "",
			 (miw[miw_no] & 2) ? "B1" : "");
}

/**
 * i7300_get_mc_wegs() - Get the contents of the MC enumewation wegistews
 * @mci: stwuct mem_ctw_info pointew
 *
 * Data wead is cached intewnawwy fow its usage when needed
 */
static int i7300_get_mc_wegs(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	u32 actuaw_towm;
	int i, wc;

	pvt = mci->pvt_info;

	pci_wead_config_dwowd(pvt->pci_dev_16_0_fsb_ctww, AMBASE,
			(u32 *) &pvt->ambase);

	edac_dbg(2, "AMBASE= 0x%wx\n", (wong unsigned int)pvt->ambase);

	/* Get the Bwanch Map wegs */
	pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map, TOWM, &pvt->towm);
	pvt->towm >>= 12;
	edac_dbg(2, "TOWM (numbew of 256M wegions) =%u (0x%x)\n",
		 pvt->towm, pvt->towm);

	actuaw_towm = (u32) ((1000w * pvt->towm) >> (30 - 28));
	edac_dbg(2, "Actuaw TOWM byte addw=%u.%03u GB (0x%x)\n",
		 actuaw_towm/1000, actuaw_towm % 1000, pvt->towm << 28);

	/* Get memowy contwowwew settings */
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map, MC_SETTINGS,
			     &pvt->mc_settings);
	pci_wead_config_dwowd(pvt->pci_dev_16_1_fsb_addw_map, MC_SETTINGS_A,
			     &pvt->mc_settings_a);

	if (IS_SINGWE_MODE(pvt->mc_settings_a))
		edac_dbg(0, "Memowy contwowwew opewating on singwe mode\n");
	ewse
		edac_dbg(0, "Memowy contwowwew opewating on %smiwwowed mode\n",
			 IS_MIWWOWED(pvt->mc_settings) ? "" : "non-");

	edac_dbg(0, "Ewwow detection is %s\n",
		 IS_ECC_ENABWED(pvt->mc_settings) ? "enabwed" : "disabwed");
	edac_dbg(0, "Wetwy is %s\n",
		 IS_WETWY_ENABWED(pvt->mc_settings) ? "enabwed" : "disabwed");

	/* Get Memowy Intewweave Wange wegistews */
	pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map, MIW0,
			     &pvt->miw[0]);
	pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map, MIW1,
			     &pvt->miw[1]);
	pci_wead_config_wowd(pvt->pci_dev_16_1_fsb_addw_map, MIW2,
			     &pvt->miw[2]);

	/* Decode the MIW wegs */
	fow (i = 0; i < MAX_MIW; i++)
		decode_miw(i, pvt->miw);

	wc = i7300_init_cswows(mci);
	if (wc < 0)
		wetuwn wc;

	/* Go and detewmine the size of each DIMM and pwace in an
	 * owdewwy matwix */
	pwint_dimm_size(pvt);

	wetuwn 0;
}

/*************************************************
 * i7300 Functions wewated to device pwobe/wewease
 *************************************************/

/**
 * i7300_put_devices() - Wewease the PCI devices
 * @mci: stwuct mem_ctw_info pointew
 */
static void i7300_put_devices(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	int bwanch;

	pvt = mci->pvt_info;

	/* Decwement usage count fow devices */
	fow (bwanch = 0; bwanch < MAX_CH_PEW_BWANCH; bwanch++)
		pci_dev_put(pvt->pci_dev_2x_0_fbd_bwanch[bwanch]);
	pci_dev_put(pvt->pci_dev_16_2_fsb_eww_wegs);
	pci_dev_put(pvt->pci_dev_16_1_fsb_addw_map);
}

/**
 * i7300_get_devices() - Find and pewfowm 'get' opewation on the MCH's
 *			 device/functions we want to wefewence fow this dwivew
 * @mci: stwuct mem_ctw_info pointew
 *
 * Access and pwepawe the sevewaw devices fow usage:
 * I7300 devices used by this dwivew:
 *    Device 16, functions 0,1 and 2:	PCI_DEVICE_ID_INTEW_I7300_MCH_EWW
 *    Device 21 function 0:		PCI_DEVICE_ID_INTEW_I7300_MCH_FB0
 *    Device 22 function 0:		PCI_DEVICE_ID_INTEW_I7300_MCH_FB1
 */
static int i7300_get_devices(stwuct mem_ctw_info *mci)
{
	stwuct i7300_pvt *pvt;
	stwuct pci_dev *pdev;

	pvt = mci->pvt_info;

	/* Attempt to 'get' the MCH wegistew we want */
	pdev = NUWW;
	whiwe ((pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				      PCI_DEVICE_ID_INTEW_I7300_MCH_EWW,
				      pdev))) {
		/* Stowe device 16 funcs 1 and 2 */
		switch (PCI_FUNC(pdev->devfn)) {
		case 1:
			if (!pvt->pci_dev_16_1_fsb_addw_map)
				pvt->pci_dev_16_1_fsb_addw_map =
							pci_dev_get(pdev);
			bweak;
		case 2:
			if (!pvt->pci_dev_16_2_fsb_eww_wegs)
				pvt->pci_dev_16_2_fsb_eww_wegs =
							pci_dev_get(pdev);
			bweak;
		}
	}

	if (!pvt->pci_dev_16_1_fsb_addw_map ||
	    !pvt->pci_dev_16_2_fsb_eww_wegs) {
		/* At weast one device was not found */
		i7300_pwintk(KEWN_EWW,
			"'system addwess,Pwocess Bus' device not found:"
			"vendow 0x%x device 0x%x EWW funcs (bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW,
			PCI_DEVICE_ID_INTEW_I7300_MCH_EWW);
		goto ewwow;
	}

	edac_dbg(1, "System Addwess, pwocessow bus- PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_0_fsb_ctww),
		 pvt->pci_dev_16_0_fsb_ctww->vendow,
		 pvt->pci_dev_16_0_fsb_ctww->device);
	edac_dbg(1, "Bwanchmap, contwow and ewwows - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_1_fsb_addw_map),
		 pvt->pci_dev_16_1_fsb_addw_map->vendow,
		 pvt->pci_dev_16_1_fsb_addw_map->device);
	edac_dbg(1, "FSB Ewwow Wegs - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->pci_dev_16_2_fsb_eww_wegs),
		 pvt->pci_dev_16_2_fsb_eww_wegs->vendow,
		 pvt->pci_dev_16_2_fsb_eww_wegs->device);

	pvt->pci_dev_2x_0_fbd_bwanch[0] = pci_get_device(PCI_VENDOW_ID_INTEW,
					    PCI_DEVICE_ID_INTEW_I7300_MCH_FB0,
					    NUWW);
	if (!pvt->pci_dev_2x_0_fbd_bwanch[0]) {
		i7300_pwintk(KEWN_EWW,
			"MC: 'BWANCH 0' device not found:"
			"vendow 0x%x device 0x%x Func 0 (bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_I7300_MCH_FB0);
		goto ewwow;
	}

	pvt->pci_dev_2x_0_fbd_bwanch[1] = pci_get_device(PCI_VENDOW_ID_INTEW,
					    PCI_DEVICE_ID_INTEW_I7300_MCH_FB1,
					    NUWW);
	if (!pvt->pci_dev_2x_0_fbd_bwanch[1]) {
		i7300_pwintk(KEWN_EWW,
			"MC: 'BWANCH 1' device not found:"
			"vendow 0x%x device 0x%x Func 0 "
			"(bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW,
			PCI_DEVICE_ID_INTEW_I7300_MCH_FB1);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	i7300_put_devices(mci);
	wetuwn -ENODEV;
}

/**
 * i7300_init_one() - Pwobe fow one instance of the device
 * @pdev: stwuct pci_dev pointew
 * @id: stwuct pci_device_id pointew - cuwwentwy unused
 */
static int i7300_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[3];
	stwuct i7300_pvt *pvt;
	int wc;

	/* wake up device */
	wc = pci_enabwe_device(pdev);
	if (wc == -EIO)
		wetuwn wc;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->numbew,
		 PCI_SWOT(pdev->devfn), PCI_FUNC(pdev->devfn));

	/* We onwy awe wooking fow func 0 of the set */
	if (PCI_FUNC(pdev->devfn) != 0)
		wetuwn -ENODEV;

	/* awwocate a new MC contwow stwuctuwe */
	wayews[0].type = EDAC_MC_WAYEW_BWANCH;
	wayews[0].size = MAX_BWANCHES;
	wayews[0].is_viwt_cswow = fawse;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = MAX_CH_PEW_BWANCH;
	wayews[1].is_viwt_cswow = twue;
	wayews[2].type = EDAC_MC_WAYEW_SWOT;
	wayews[2].size = MAX_SWOTS;
	wayews[2].is_viwt_cswow = twue;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;	/* wecowd ptw  to the genewic device */

	pvt = mci->pvt_info;
	pvt->pci_dev_16_0_fsb_ctww = pdev;	/* Wecowd this device in ouw pwivate */

	pvt->tmp_pwt_buffew = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!pvt->tmp_pwt_buffew) {
		edac_mc_fwee(mci);
		wetuwn -ENOMEM;
	}

	/* 'get' the pci devices we want to wesewve fow ouw use */
	if (i7300_get_devices(mci))
		goto faiw0;

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FWAG_FB_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_NONE;
	mci->edac_cap = EDAC_FWAG_NONE;
	mci->mod_name = "i7300_edac.c";
	mci->ctw_name = i7300_devs[0].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->ctw_page_to_phys = NUWW;

	/* Set the function pointew to an actuaw opewation function */
	mci->edac_check = i7300_check_ewwow;

	/* initiawize the MC contwow stwuctuwe 'cswows' tabwe
	 * with the mapping and contwow infowmation */
	if (i7300_get_mc_wegs(mci)) {
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FWAG_NONE because i7300_init_cswows() wetuwned nonzewo vawue\n");
		mci->edac_cap = EDAC_FWAG_NONE;	/* no cswows found */
	} ewse {
		edac_dbg(1, "MC: Enabwe ewwow wepowting now\n");
		i7300_enabwe_ewwow_wepowting(mci);
	}

	/* add this new MC contwow stwuctuwe to EDAC's wist of MCs */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(0, "MC: faiwed edac_mc_add_mc()\n");
		/* FIXME: pewhaps some code shouwd go hewe that disabwes ewwow
		 * wepowting if we just enabwed it
		 */
		goto faiw1;
	}

	i7300_cweaw_ewwow(mci);

	/* awwocating genewic PCI contwow info */
	i7300_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!i7300_pci) {
		pwintk(KEWN_WAWNING
			"%s(): Unabwe to cweate PCI contwow\n",
			__func__);
		pwintk(KEWN_WAWNING
			"%s(): PCI ewwow wepowt via EDAC not setup\n",
			__func__);
	}

	wetuwn 0;

	/* Ewwow exit unwinding stack */
faiw1:

	i7300_put_devices(mci);

faiw0:
	kfwee(pvt->tmp_pwt_buffew);
	edac_mc_fwee(mci);
	wetuwn -ENODEV;
}

/**
 * i7300_wemove_one() - Wemove the dwivew
 * @pdev: stwuct pci_dev pointew
 */
static void i7300_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	chaw *tmp;

	edac_dbg(0, "\n");

	if (i7300_pci)
		edac_pci_wewease_genewic_ctw(i7300_pci);

	mci = edac_mc_dew_mc(&pdev->dev);
	if (!mci)
		wetuwn;

	tmp = ((stwuct i7300_pvt *)mci->pvt_info)->tmp_pwt_buffew;

	/* wetwieve wefewences to wesouwces, and fwee those wesouwces */
	i7300_put_devices(mci);

	kfwee(tmp);
	edac_mc_fwee(mci);
}

/*
 * pci_device_id: tabwe fow which devices we awe wooking fow
 *
 * Has onwy 8086:360c PCI ID
 */
static const stwuct pci_device_id i7300_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_I7300_MCH_EWW)},
	{0,}			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i7300_pci_tbw);

/*
 * i7300_dwivew: pci_dwivew stwuctuwe fow this moduwe
 */
static stwuct pci_dwivew i7300_dwivew = {
	.name = "i7300_edac",
	.pwobe = i7300_init_one,
	.wemove = i7300_wemove_one,
	.id_tabwe = i7300_pci_tbw,
};

/**
 * i7300_init() - Wegistews the dwivew
 */
static int __init i7300_init(void)
{
	int pci_wc;

	edac_dbg(2, "\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&i7300_dwivew);

	wetuwn (pci_wc < 0) ? pci_wc : 0;
}

/**
 * i7300_exit() - Unwegistews the dwivew
 */
static void __exit i7300_exit(void)
{
	edac_dbg(2, "\n");
	pci_unwegistew_dwivew(&i7300_dwivew);
}

moduwe_init(i7300_init);
moduwe_exit(i7300_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_AUTHOW("Wed Hat Inc. (https://www.wedhat.com)");
MODUWE_DESCWIPTION("MC Dwivew fow Intew I7300 memowy contwowwews - "
		   I7300_WEVISION);

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
