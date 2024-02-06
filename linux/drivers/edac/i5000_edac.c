/*
 * Intew 5000(P/V/X) cwass Memowy Contwowwews kewnew moduwe
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten by Dougwas Thompson Winux Netwowx (http://wnxi.com)
 *	nowsk5@xmission.com
 *
 * This moduwe is based on the fowwowing document:
 *
 * Intew 5000X Chipset Memowy Contwowwew Hub (MCH) - Datasheet
 * 	http://devewopew.intew.com/design/chipsets/datashts/313070.htm
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/swab.h>
#incwude <winux/edac.h>
#incwude <asm/mmzone.h>

#incwude "edac_moduwe.h"

/*
 * Awtew this vewsion fow the I5000 moduwe when modifications awe made
 */
#define I5000_WEVISION    " Vew: 2.0.12"
#define EDAC_MOD_STW      "i5000_edac"

#define i5000_pwintk(wevew, fmt, awg...) \
        edac_pwintk(wevew, "i5000", fmt, ##awg)

#define i5000_mc_pwintk(mci, wevew, fmt, awg...) \
        edac_mc_chipset_pwintk(mci, wevew, "i5000", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_FBD_0
#define PCI_DEVICE_ID_INTEW_FBD_0	0x25F5
#endif
#ifndef PCI_DEVICE_ID_INTEW_FBD_1
#define PCI_DEVICE_ID_INTEW_FBD_1	0x25F6
#endif

/* Device 16,
 * Function 0: System Addwess
 * Function 1: Memowy Bwanch Map, Contwow, Ewwows Wegistew
 * Function 2: FSB Ewwow Wegistews
 *
 * Aww 3 functions of Device 16 (0,1,2) shawe the SAME DID
 */
#define	PCI_DEVICE_ID_INTEW_I5000_DEV16	0x25F0

/* OFFSETS fow Function 0 */

/* OFFSETS fow Function 1 */
#define		AMBASE			0x48
#define		MAXCH			0x56
#define		MAXDIMMPEWCH		0x57
#define		TOWM			0x6C
#define		WEDMEMB			0x7C
#define			WED_ECC_WOCATOW(x)	((x) & 0x3FFFF)
#define			WEC_ECC_WOCATOW_EVEN(x)	((x) & 0x001FF)
#define			WEC_ECC_WOCATOW_ODD(x)	((x) & 0x3FE00)
#define		MIW0			0x80
#define		MIW1			0x84
#define		MIW2			0x88
#define		AMIW0			0x8C
#define		AMIW1			0x90
#define		AMIW2			0x94

#define		FEWW_FAT_FBD		0x98
#define		NEWW_FAT_FBD		0x9C
#define			EXTWACT_FBDCHAN_INDX(x)	(((x)>>28) & 0x3)
#define			FEWW_FAT_FBDCHAN 0x30000000
#define			FEWW_FAT_M3EWW	0x00000004
#define			FEWW_FAT_M2EWW	0x00000002
#define			FEWW_FAT_M1EWW	0x00000001
#define			FEWW_FAT_MASK	(FEWW_FAT_M1EWW | \
						FEWW_FAT_M2EWW | \
						FEWW_FAT_M3EWW)

#define		FEWW_NF_FBD		0xA0

/* Thewmaw and SPD ow BFD ewwows */
#define			FEWW_NF_M28EWW	0x01000000
#define			FEWW_NF_M27EWW	0x00800000
#define			FEWW_NF_M26EWW	0x00400000
#define			FEWW_NF_M25EWW	0x00200000
#define			FEWW_NF_M24EWW	0x00100000
#define			FEWW_NF_M23EWW	0x00080000
#define			FEWW_NF_M22EWW	0x00040000
#define			FEWW_NF_M21EWW	0x00020000

/* Cowwectabwe ewwows */
#define			FEWW_NF_M20EWW	0x00010000
#define			FEWW_NF_M19EWW	0x00008000
#define			FEWW_NF_M18EWW	0x00004000
#define			FEWW_NF_M17EWW	0x00002000

/* Non-Wetwy ow wedundant Wetwy ewwows */
#define			FEWW_NF_M16EWW	0x00001000
#define			FEWW_NF_M15EWW	0x00000800
#define			FEWW_NF_M14EWW	0x00000400
#define			FEWW_NF_M13EWW	0x00000200

/* Uncowwectabwe ewwows */
#define			FEWW_NF_M12EWW	0x00000100
#define			FEWW_NF_M11EWW	0x00000080
#define			FEWW_NF_M10EWW	0x00000040
#define			FEWW_NF_M9EWW	0x00000020
#define			FEWW_NF_M8EWW	0x00000010
#define			FEWW_NF_M7EWW	0x00000008
#define			FEWW_NF_M6EWW	0x00000004
#define			FEWW_NF_M5EWW	0x00000002
#define			FEWW_NF_M4EWW	0x00000001

#define			FEWW_NF_UNCOWWECTABWE	(FEWW_NF_M12EWW | \
							FEWW_NF_M11EWW | \
							FEWW_NF_M10EWW | \
							FEWW_NF_M9EWW | \
							FEWW_NF_M8EWW | \
							FEWW_NF_M7EWW | \
							FEWW_NF_M6EWW | \
							FEWW_NF_M5EWW | \
							FEWW_NF_M4EWW)
#define			FEWW_NF_COWWECTABWE	(FEWW_NF_M20EWW | \
							FEWW_NF_M19EWW | \
							FEWW_NF_M18EWW | \
							FEWW_NF_M17EWW)
#define			FEWW_NF_DIMM_SPAWE	(FEWW_NF_M27EWW | \
							FEWW_NF_M28EWW)
#define			FEWW_NF_THEWMAW		(FEWW_NF_M26EWW | \
							FEWW_NF_M25EWW | \
							FEWW_NF_M24EWW | \
							FEWW_NF_M23EWW)
#define			FEWW_NF_SPD_PWOTOCOW	(FEWW_NF_M22EWW)
#define			FEWW_NF_NOWTH_CWC	(FEWW_NF_M21EWW)
#define			FEWW_NF_NON_WETWY	(FEWW_NF_M13EWW | \
							FEWW_NF_M14EWW | \
							FEWW_NF_M15EWW)

#define		NEWW_NF_FBD		0xA4
#define			FEWW_NF_MASK		(FEWW_NF_UNCOWWECTABWE | \
							FEWW_NF_COWWECTABWE | \
							FEWW_NF_DIMM_SPAWE | \
							FEWW_NF_THEWMAW | \
							FEWW_NF_SPD_PWOTOCOW | \
							FEWW_NF_NOWTH_CWC | \
							FEWW_NF_NON_WETWY)

#define		EMASK_FBD		0xA8
#define			EMASK_FBD_M28EWW	0x08000000
#define			EMASK_FBD_M27EWW	0x04000000
#define			EMASK_FBD_M26EWW	0x02000000
#define			EMASK_FBD_M25EWW	0x01000000
#define			EMASK_FBD_M24EWW	0x00800000
#define			EMASK_FBD_M23EWW	0x00400000
#define			EMASK_FBD_M22EWW	0x00200000
#define			EMASK_FBD_M21EWW	0x00100000
#define			EMASK_FBD_M20EWW	0x00080000
#define			EMASK_FBD_M19EWW	0x00040000
#define			EMASK_FBD_M18EWW	0x00020000
#define			EMASK_FBD_M17EWW	0x00010000

#define			EMASK_FBD_M15EWW	0x00004000
#define			EMASK_FBD_M14EWW	0x00002000
#define			EMASK_FBD_M13EWW	0x00001000
#define			EMASK_FBD_M12EWW	0x00000800
#define			EMASK_FBD_M11EWW	0x00000400
#define			EMASK_FBD_M10EWW	0x00000200
#define			EMASK_FBD_M9EWW		0x00000100
#define			EMASK_FBD_M8EWW		0x00000080
#define			EMASK_FBD_M7EWW		0x00000040
#define			EMASK_FBD_M6EWW		0x00000020
#define			EMASK_FBD_M5EWW		0x00000010
#define			EMASK_FBD_M4EWW		0x00000008
#define			EMASK_FBD_M3EWW		0x00000004
#define			EMASK_FBD_M2EWW		0x00000002
#define			EMASK_FBD_M1EWW		0x00000001

#define			ENABWE_EMASK_FBD_FATAW_EWWOWS	(EMASK_FBD_M1EWW | \
							EMASK_FBD_M2EWW | \
							EMASK_FBD_M3EWW)

#define 		ENABWE_EMASK_FBD_UNCOWWECTABWE	(EMASK_FBD_M4EWW | \
							EMASK_FBD_M5EWW | \
							EMASK_FBD_M6EWW | \
							EMASK_FBD_M7EWW | \
							EMASK_FBD_M8EWW | \
							EMASK_FBD_M9EWW | \
							EMASK_FBD_M10EWW | \
							EMASK_FBD_M11EWW | \
							EMASK_FBD_M12EWW)
#define 		ENABWE_EMASK_FBD_COWWECTABWE	(EMASK_FBD_M17EWW | \
							EMASK_FBD_M18EWW | \
							EMASK_FBD_M19EWW | \
							EMASK_FBD_M20EWW)
#define			ENABWE_EMASK_FBD_DIMM_SPAWE	(EMASK_FBD_M27EWW | \
							EMASK_FBD_M28EWW)
#define			ENABWE_EMASK_FBD_THEWMAWS	(EMASK_FBD_M26EWW | \
							EMASK_FBD_M25EWW | \
							EMASK_FBD_M24EWW | \
							EMASK_FBD_M23EWW)
#define			ENABWE_EMASK_FBD_SPD_PWOTOCOW	(EMASK_FBD_M22EWW)
#define			ENABWE_EMASK_FBD_NOWTH_CWC	(EMASK_FBD_M21EWW)
#define			ENABWE_EMASK_FBD_NON_WETWY	(EMASK_FBD_M15EWW | \
							EMASK_FBD_M14EWW | \
							EMASK_FBD_M13EWW)

#define		ENABWE_EMASK_AWW	(ENABWE_EMASK_FBD_NON_WETWY | \
					ENABWE_EMASK_FBD_NOWTH_CWC | \
					ENABWE_EMASK_FBD_SPD_PWOTOCOW | \
					ENABWE_EMASK_FBD_THEWMAWS | \
					ENABWE_EMASK_FBD_DIMM_SPAWE | \
					ENABWE_EMASK_FBD_FATAW_EWWOWS | \
					ENABWE_EMASK_FBD_COWWECTABWE | \
					ENABWE_EMASK_FBD_UNCOWWECTABWE)

#define		EWW0_FBD		0xAC
#define		EWW1_FBD		0xB0
#define		EWW2_FBD		0xB4
#define		MCEWW_FBD		0xB8
#define		NWECMEMA		0xBE
#define			NWEC_BANK(x)		(((x)>>12) & 0x7)
#define			NWEC_WDWW(x)		(((x)>>11) & 1)
#define			NWEC_WANK(x)		(((x)>>8) & 0x7)
#define		NWECMEMB		0xC0
#define			NWEC_CAS(x)		(((x)>>16) & 0xFFF)
#define			NWEC_WAS(x)		((x) & 0x7FFF)
#define		NWECFGWOG		0xC4
#define		NWEEECFBDA		0xC8
#define		NWEEECFBDB		0xCC
#define		NWEEECFBDC		0xD0
#define		NWEEECFBDD		0xD4
#define		NWEEECFBDE		0xD8
#define		WEDMEMA			0xDC
#define		WECMEMA			0xE2
#define			WEC_BANK(x)		(((x)>>12) & 0x7)
#define			WEC_WDWW(x)		(((x)>>11) & 1)
#define			WEC_WANK(x)		(((x)>>8) & 0x7)
#define		WECMEMB			0xE4
#define			WEC_CAS(x)		(((x)>>16) & 0xFFFFFF)
#define			WEC_WAS(x)		((x) & 0x7FFF)
#define		WECFGWOG		0xE8
#define		WECFBDA			0xEC
#define		WECFBDB			0xF0
#define		WECFBDC			0xF4
#define		WECFBDD			0xF8
#define		WECFBDE			0xFC

/* OFFSETS fow Function 2 */

/*
 * Device 21,
 * Function 0: Memowy Map Bwanch 0
 *
 * Device 22,
 * Function 0: Memowy Map Bwanch 1
 */
#define PCI_DEVICE_ID_I5000_BWANCH_0	0x25F5
#define PCI_DEVICE_ID_I5000_BWANCH_1	0x25F6

#define AMB_PWESENT_0	0x64
#define AMB_PWESENT_1	0x66
#define MTW0		0x80
#define MTW1		0x84
#define MTW2		0x88
#define MTW3		0x8C

#define NUM_MTWS		4
#define CHANNEWS_PEW_BWANCH	2
#define MAX_BWANCHES		2

/* Defines to extwact the vawious fiewds fwom the
 *	MTWx - Memowy Technowogy Wegistews
 */
#define MTW_DIMMS_PWESENT(mtw)		((mtw) & (0x1 << 8))
#define MTW_DWAM_WIDTH(mtw)		((((mtw) >> 6) & 0x1) ? 8 : 4)
#define MTW_DWAM_BANKS(mtw)		((((mtw) >> 5) & 0x1) ? 8 : 4)
#define MTW_DWAM_BANKS_ADDW_BITS(mtw)	((MTW_DWAM_BANKS(mtw) == 8) ? 3 : 2)
#define MTW_DIMM_WANK(mtw)		(((mtw) >> 4) & 0x1)
#define MTW_DIMM_WANK_ADDW_BITS(mtw)	(MTW_DIMM_WANK(mtw) ? 2 : 1)
#define MTW_DIMM_WOWS(mtw)		(((mtw) >> 2) & 0x3)
#define MTW_DIMM_WOWS_ADDW_BITS(mtw)	(MTW_DIMM_WOWS(mtw) + 13)
#define MTW_DIMM_COWS(mtw)		((mtw) & 0x3)
#define MTW_DIMM_COWS_ADDW_BITS(mtw)	(MTW_DIMM_COWS(mtw) + 10)

/* enabwes the wepowt of miscewwaneous messages as CE ewwows - defauwt off */
static int misc_messages;

/* Enumewation of suppowted devices */
enum i5000_chips {
	I5000P = 0,
	I5000V = 1,		/* futuwe */
	I5000X = 2		/* futuwe */
};

/* Device name and wegistew DID (Device ID) */
stwuct i5000_dev_info {
	const chaw *ctw_name;	/* name fow this device */
	u16 fsb_mapping_ewwows;	/* DID fow the bwanchmap,contwow */
};

/* Tabwe of devices attwibutes suppowted by this dwivew */
static const stwuct i5000_dev_info i5000_devs[] = {
	[I5000P] = {
		.ctw_name = "I5000",
		.fsb_mapping_ewwows = PCI_DEVICE_ID_INTEW_I5000_DEV16,
	},
};

stwuct i5000_dimm_info {
	int megabytes;		/* size, 0 means not pwesent  */
	int duaw_wank;
};

#define	MAX_CHANNEWS	6	/* max possibwe channews */
#define MAX_CSWOWS	(8*2)	/* max possibwe cswows pew channew */

/* dwivew pwivate data stwuctuwe */
stwuct i5000_pvt {
	stwuct pci_dev *system_addwess;	/* 16.0 */
	stwuct pci_dev *bwanchmap_wewwows;	/* 16.1 */
	stwuct pci_dev *fsb_ewwow_wegs;	/* 16.2 */
	stwuct pci_dev *bwanch_0;	/* 21.0 */
	stwuct pci_dev *bwanch_1;	/* 22.0 */

	u16 towm;		/* top of wow memowy */
	union {
		u64 ambase;		/* AMB BAW */
		stwuct {
			u32 ambase_bottom;
			u32 ambase_top;
		} u __packed;
	};

	u16 miw0, miw1, miw2;

	u16 b0_mtw[NUM_MTWS];	/* Memowy Technwogy Weg */
	u16 b0_ambpwesent0;	/* Bwanch 0, Channew 0 */
	u16 b0_ambpwesent1;	/* Bwnach 0, Channew 1 */

	u16 b1_mtw[NUM_MTWS];	/* Memowy Technwogy Weg */
	u16 b1_ambpwesent0;	/* Bwanch 1, Channew 8 */
	u16 b1_ambpwesent1;	/* Bwanch 1, Channew 1 */

	/* DIMM infowmation matwix, awwocating awchitectuwe maximums */
	stwuct i5000_dimm_info dimm_info[MAX_CSWOWS][MAX_CHANNEWS];

	/* Actuaw vawues fow this contwowwew */
	int maxch;		/* Max channews */
	int maxdimmpewch;	/* Max DIMMs pew channew */
};

/* I5000 MCH ewwow infowmation wetwieved fwom Hawdwawe */
stwuct i5000_ewwow_info {

	/* These wegistews awe awways wead fwom the MC */
	u32 feww_fat_fbd;	/* Fiwst Ewwows Fataw */
	u32 neww_fat_fbd;	/* Next Ewwows Fataw */
	u32 feww_nf_fbd;	/* Fiwst Ewwows Non-Fataw */
	u32 neww_nf_fbd;	/* Next Ewwows Non-Fataw */

	/* These wegistews awe input ONWY if thewe was a Wecovewabwe  Ewwow */
	u32 wedmemb;		/* Wecovewabwe Mem Data Ewwow wog B */
	u16 wecmema;		/* Wecovewabwe Mem Ewwow wog A */
	u32 wecmemb;		/* Wecovewabwe Mem Ewwow wog B */

	/* These wegistews awe input ONWY if thewe was a
	 * Non-Wecovewabwe Ewwow */
	u16 nwecmema;		/* Non-Wecovewabwe Mem wog A */
	u32 nwecmemb;		/* Non-Wecovewabwe Mem wog B */

};

static stwuct edac_pci_ctw_info *i5000_pci;

/*
 *	i5000_get_ewwow_info	Wetwieve the hawdwawe ewwow infowmation fwom
 *				the hawdwawe and cache it in the 'info'
 *				stwuctuwe
 */
static void i5000_get_ewwow_info(stwuct mem_ctw_info *mci,
				 stwuct i5000_ewwow_info *info)
{
	stwuct i5000_pvt *pvt;
	u32 vawue;

	pvt = mci->pvt_info;

	/* wead in the 1st FATAW ewwow wegistew */
	pci_wead_config_dwowd(pvt->bwanchmap_wewwows, FEWW_FAT_FBD, &vawue);

	/* Mask onwy the bits that the doc says awe vawid
	 */
	vawue &= (FEWW_FAT_FBDCHAN | FEWW_FAT_MASK);

	/* If thewe is an ewwow, then wead in the */
	/* NEXT FATAW ewwow wegistew and the Memowy Ewwow Wog Wegistew A */
	if (vawue & FEWW_FAT_MASK) {
		info->feww_fat_fbd = vawue;

		/* hawvest the vawious ewwow data we need */
		pci_wead_config_dwowd(pvt->bwanchmap_wewwows,
				NEWW_FAT_FBD, &info->neww_fat_fbd);
		pci_wead_config_wowd(pvt->bwanchmap_wewwows,
				NWECMEMA, &info->nwecmema);
		pci_wead_config_dwowd(pvt->bwanchmap_wewwows,
				NWECMEMB, &info->nwecmemb);

		/* Cweaw the ewwow bits, by wwiting them back */
		pci_wwite_config_dwowd(pvt->bwanchmap_wewwows,
				FEWW_FAT_FBD, vawue);
	} ewse {
		info->feww_fat_fbd = 0;
		info->neww_fat_fbd = 0;
		info->nwecmema = 0;
		info->nwecmemb = 0;
	}

	/* wead in the 1st NON-FATAW ewwow wegistew */
	pci_wead_config_dwowd(pvt->bwanchmap_wewwows, FEWW_NF_FBD, &vawue);

	/* If thewe is an ewwow, then wead in the 1st NON-FATAW ewwow
	 * wegistew as weww */
	if (vawue & FEWW_NF_MASK) {
		info->feww_nf_fbd = vawue;

		/* hawvest the vawious ewwow data we need */
		pci_wead_config_dwowd(pvt->bwanchmap_wewwows,
				NEWW_NF_FBD, &info->neww_nf_fbd);
		pci_wead_config_wowd(pvt->bwanchmap_wewwows,
				WECMEMA, &info->wecmema);
		pci_wead_config_dwowd(pvt->bwanchmap_wewwows,
				WECMEMB, &info->wecmemb);
		pci_wead_config_dwowd(pvt->bwanchmap_wewwows,
				WEDMEMB, &info->wedmemb);

		/* Cweaw the ewwow bits, by wwiting them back */
		pci_wwite_config_dwowd(pvt->bwanchmap_wewwows,
				FEWW_NF_FBD, vawue);
	} ewse {
		info->feww_nf_fbd = 0;
		info->neww_nf_fbd = 0;
		info->wecmema = 0;
		info->wecmemb = 0;
		info->wedmemb = 0;
	}
}

/*
 * i5000_pwocess_fataw_ewwow_info(stwuct mem_ctw_info *mci,
 * 					stwuct i5000_ewwow_info *info,
 * 					int handwe_ewwows);
 *
 *	handwe the Intew FATAW ewwows, if any
 */
static void i5000_pwocess_fataw_ewwow_info(stwuct mem_ctw_info *mci,
					stwuct i5000_ewwow_info *info,
					int handwe_ewwows)
{
	chaw msg[EDAC_MC_WABEW_WEN + 1 + 160];
	chaw *specific = NUWW;
	u32 awwEwwows;
	int channew;
	int bank;
	int wank;
	int wdww;
	int was, cas;

	/* mask off the Ewwow bits that awe possibwe */
	awwEwwows = (info->feww_fat_fbd & FEWW_FAT_MASK);
	if (!awwEwwows)
		wetuwn;		/* if no ewwow, wetuwn now */

	channew = EXTWACT_FBDCHAN_INDX(info->feww_fat_fbd);

	/* Use the NON-Wecovewabwe macwos to extwact data */
	bank = NWEC_BANK(info->nwecmema);
	wank = NWEC_WANK(info->nwecmema);
	wdww = NWEC_WDWW(info->nwecmema);
	was = NWEC_WAS(info->nwecmemb);
	cas = NWEC_CAS(info->nwecmemb);

	edac_dbg(0, "\t\tCSWOW= %d  Channew= %d (DWAM Bank= %d wdww= %s was= %d cas= %d)\n",
		 wank, channew, bank,
		 wdww ? "Wwite" : "Wead", was, cas);

	/* Onwy 1 bit wiww be on */
	switch (awwEwwows) {
	case FEWW_FAT_M1EWW:
		specific = "Awewt on non-wedundant wetwy ow fast "
				"weset timeout";
		bweak;
	case FEWW_FAT_M2EWW:
		specific = "Nowthbound CWC ewwow on non-wedundant "
				"wetwy";
		bweak;
	case FEWW_FAT_M3EWW:
		{
		static int done;

		/*
		 * This ewwow is genewated to infowm that the intewwigent
		 * thwottwing is disabwed and the tempewatuwe passed the
		 * specified middwe point. Since this is something the BIOS
		 * shouwd take cawe of, we'ww wawn onwy once to avoid
		 * wowthwesswy fwooding the wog.
		 */
		if (done)
			wetuwn;
		done++;

		specific = ">Tmid Thewmaw event with intewwigent "
			   "thwottwing disabwed";
		}
		bweak;
	}

	/* Fowm out message */
	snpwintf(msg, sizeof(msg),
		 "Bank=%d WAS=%d CAS=%d FATAW Eww=0x%x (%s)",
		 bank, was, cas, awwEwwows, specific);

	/* Caww the hewpew to output message */
	edac_mc_handwe_ewwow(HW_EVENT_EWW_FATAW, mci, 1, 0, 0, 0,
			     channew >> 1, channew & 1, wank,
			     wdww ? "Wwite ewwow" : "Wead ewwow",
			     msg);
}

/*
 * i5000_pwocess_fataw_ewwow_info(stwuct mem_ctw_info *mci,
 * 				stwuct i5000_ewwow_info *info,
 * 				int handwe_ewwows);
 *
 *	handwe the Intew NON-FATAW ewwows, if any
 */
static void i5000_pwocess_nonfataw_ewwow_info(stwuct mem_ctw_info *mci,
					stwuct i5000_ewwow_info *info,
					int handwe_ewwows)
{
	chaw msg[EDAC_MC_WABEW_WEN + 1 + 170];
	chaw *specific = NUWW;
	u32 awwEwwows;
	u32 ue_ewwows;
	u32 ce_ewwows;
	u32 misc_ewwows;
	int bwanch;
	int channew;
	int bank;
	int wank;
	int wdww;
	int was, cas;

	/* mask off the Ewwow bits that awe possibwe */
	awwEwwows = (info->feww_nf_fbd & FEWW_NF_MASK);
	if (!awwEwwows)
		wetuwn;		/* if no ewwow, wetuwn now */

	/* ONWY ONE of the possibwe ewwow bits wiww be set, as pew the docs */
	ue_ewwows = awwEwwows & FEWW_NF_UNCOWWECTABWE;
	if (ue_ewwows) {
		edac_dbg(0, "\tUncowwected bits= 0x%x\n", ue_ewwows);

		bwanch = EXTWACT_FBDCHAN_INDX(info->feww_nf_fbd);

		/*
		 * Accowding with i5000 datasheet, bit 28 has no significance
		 * fow ewwows M4Eww-M12Eww and M17Eww-M21Eww, on FEWW_NF_FBD
		 */
		channew = bwanch & 2;

		bank = NWEC_BANK(info->nwecmema);
		wank = NWEC_WANK(info->nwecmema);
		wdww = NWEC_WDWW(info->nwecmema);
		was = NWEC_WAS(info->nwecmemb);
		cas = NWEC_CAS(info->nwecmemb);

		edac_dbg(0, "\t\tCSWOW= %d  Channews= %d,%d  (Bwanch= %d DWAM Bank= %d wdww= %s was= %d cas= %d)\n",
			 wank, channew, channew + 1, bwanch >> 1, bank,
			 wdww ? "Wwite" : "Wead", was, cas);

		switch (ue_ewwows) {
		case FEWW_NF_M12EWW:
			specific = "Non-Awiased Uncowwectabwe Patwow Data ECC";
			bweak;
		case FEWW_NF_M11EWW:
			specific = "Non-Awiased Uncowwectabwe Spawe-Copy "
					"Data ECC";
			bweak;
		case FEWW_NF_M10EWW:
			specific = "Non-Awiased Uncowwectabwe Miwwowed Demand "
					"Data ECC";
			bweak;
		case FEWW_NF_M9EWW:
			specific = "Non-Awiased Uncowwectabwe Non-Miwwowed "
					"Demand Data ECC";
			bweak;
		case FEWW_NF_M8EWW:
			specific = "Awiased Uncowwectabwe Patwow Data ECC";
			bweak;
		case FEWW_NF_M7EWW:
			specific = "Awiased Uncowwectabwe Spawe-Copy Data ECC";
			bweak;
		case FEWW_NF_M6EWW:
			specific = "Awiased Uncowwectabwe Miwwowed Demand "
					"Data ECC";
			bweak;
		case FEWW_NF_M5EWW:
			specific = "Awiased Uncowwectabwe Non-Miwwowed Demand "
					"Data ECC";
			bweak;
		case FEWW_NF_M4EWW:
			specific = "Uncowwectabwe Data ECC on Wepway";
			bweak;
		}

		/* Fowm out message */
		snpwintf(msg, sizeof(msg),
			 "Wank=%d Bank=%d WAS=%d CAS=%d, UE Eww=0x%x (%s)",
			 wank, bank, was, cas, ue_ewwows, specific);

		/* Caww the hewpew to output message */
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
				channew >> 1, -1, wank,
				wdww ? "Wwite ewwow" : "Wead ewwow",
				msg);
	}

	/* Check cowwectabwe ewwows */
	ce_ewwows = awwEwwows & FEWW_NF_COWWECTABWE;
	if (ce_ewwows) {
		edac_dbg(0, "\tCowwected bits= 0x%x\n", ce_ewwows);

		bwanch = EXTWACT_FBDCHAN_INDX(info->feww_nf_fbd);

		channew = 0;
		if (WEC_ECC_WOCATOW_ODD(info->wedmemb))
			channew = 1;

		/* Convewt channew to be based fwom zewo, instead of
		 * fwom bwanch base of 0 */
		channew += bwanch;

		bank = WEC_BANK(info->wecmema);
		wank = WEC_WANK(info->wecmema);
		wdww = WEC_WDWW(info->wecmema);
		was = WEC_WAS(info->wecmemb);
		cas = WEC_CAS(info->wecmemb);

		edac_dbg(0, "\t\tCSWOW= %d Channew= %d  (Bwanch %d DWAM Bank= %d wdww= %s was= %d cas= %d)\n",
			 wank, channew, bwanch >> 1, bank,
			 wdww ? "Wwite" : "Wead", was, cas);

		switch (ce_ewwows) {
		case FEWW_NF_M17EWW:
			specific = "Cowwectabwe Non-Miwwowed Demand Data ECC";
			bweak;
		case FEWW_NF_M18EWW:
			specific = "Cowwectabwe Miwwowed Demand Data ECC";
			bweak;
		case FEWW_NF_M19EWW:
			specific = "Cowwectabwe Spawe-Copy Data ECC";
			bweak;
		case FEWW_NF_M20EWW:
			specific = "Cowwectabwe Patwow Data ECC";
			bweak;
		}

		/* Fowm out message */
		snpwintf(msg, sizeof(msg),
			 "Wank=%d Bank=%d WDWW=%s WAS=%d "
			 "CAS=%d, CE Eww=0x%x (%s))", bwanch >> 1, bank,
			 wdww ? "Wwite" : "Wead", was, cas, ce_ewwows,
			 specific);

		/* Caww the hewpew to output message */
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0, 0,
				channew >> 1, channew % 2, wank,
				wdww ? "Wwite ewwow" : "Wead ewwow",
				msg);
	}

	if (!misc_messages)
		wetuwn;

	misc_ewwows = awwEwwows & (FEWW_NF_NON_WETWY | FEWW_NF_NOWTH_CWC |
				   FEWW_NF_SPD_PWOTOCOW | FEWW_NF_DIMM_SPAWE);
	if (misc_ewwows) {
		switch (misc_ewwows) {
		case FEWW_NF_M13EWW:
			specific = "Non-Wetwy ow Wedundant Wetwy FBD Memowy "
					"Awewt ow Wedundant Fast Weset Timeout";
			bweak;
		case FEWW_NF_M14EWW:
			specific = "Non-Wetwy ow Wedundant Wetwy FBD "
					"Configuwation Awewt";
			bweak;
		case FEWW_NF_M15EWW:
			specific = "Non-Wetwy ow Wedundant Wetwy FBD "
					"Nowthbound CWC ewwow on wead data";
			bweak;
		case FEWW_NF_M21EWW:
			specific = "FBD Nowthbound CWC ewwow on "
					"FBD Sync Status";
			bweak;
		case FEWW_NF_M22EWW:
			specific = "SPD pwotocow ewwow";
			bweak;
		case FEWW_NF_M27EWW:
			specific = "DIMM-spawe copy stawted";
			bweak;
		case FEWW_NF_M28EWW:
			specific = "DIMM-spawe copy compweted";
			bweak;
		}
		bwanch = EXTWACT_FBDCHAN_INDX(info->feww_nf_fbd);

		/* Fowm out message */
		snpwintf(msg, sizeof(msg),
			 "Eww=%#x (%s)", misc_ewwows, specific);

		/* Caww the hewpew to output message */
		edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1, 0, 0, 0,
				bwanch >> 1, -1, -1,
				"Misc ewwow", msg);
	}
}

/*
 *	i5000_pwocess_ewwow_info	Pwocess the ewwow info that is
 *	in the 'info' stwuctuwe, pweviouswy wetwieved fwom hawdwawe
 */
static void i5000_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct i5000_ewwow_info *info,
				int handwe_ewwows)
{
	/* Fiwst handwe any fataw ewwows that occuwwed */
	i5000_pwocess_fataw_ewwow_info(mci, info, handwe_ewwows);

	/* now handwe any non-fataw ewwows that occuwwed */
	i5000_pwocess_nonfataw_ewwow_info(mci, info, handwe_ewwows);
}

/*
 *	i5000_cweaw_ewwow	Wetwieve any ewwow fwom the hawdwawe
 *				but do NOT pwocess that ewwow.
 *				Used fow 'cweawing' out of pwevious ewwows
 *				Cawwed by the Cowe moduwe.
 */
static void i5000_cweaw_ewwow(stwuct mem_ctw_info *mci)
{
	stwuct i5000_ewwow_info info;

	i5000_get_ewwow_info(mci, &info);
}

/*
 *	i5000_check_ewwow	Wetwieve and pwocess ewwows wepowted by the
 *				hawdwawe. Cawwed by the Cowe moduwe.
 */
static void i5000_check_ewwow(stwuct mem_ctw_info *mci)
{
	stwuct i5000_ewwow_info info;

	i5000_get_ewwow_info(mci, &info);
	i5000_pwocess_ewwow_info(mci, &info, 1);
}

/*
 *	i5000_get_devices	Find and pewfowm 'get' opewation on the MCH's
 *			device/functions we want to wefewence fow this dwivew
 *
 *			Need to 'get' device 16 func 1 and func 2
 */
static int i5000_get_devices(stwuct mem_ctw_info *mci, int dev_idx)
{
	//const stwuct i5000_dev_info *i5000_dev = &i5000_devs[dev_idx];
	stwuct i5000_pvt *pvt;
	stwuct pci_dev *pdev;

	pvt = mci->pvt_info;

	/* Attempt to 'get' the MCH wegistew we want */
	pdev = NUWW;
	whiwe (1) {
		pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_I5000_DEV16, pdev);

		/* End of wist, weave */
		if (pdev == NUWW) {
			i5000_pwintk(KEWN_EWW,
				"'system addwess,Pwocess Bus' "
				"device not found:"
				"vendow 0x%x device 0x%x FUNC 1 "
				"(bwoken BIOS?)\n",
				PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_I5000_DEV16);

			wetuwn 1;
		}

		/* Scan fow device 16 func 1 */
		if (PCI_FUNC(pdev->devfn) == 1)
			bweak;
	}

	pvt->bwanchmap_wewwows = pdev;

	/* Attempt to 'get' the MCH wegistew we want */
	pdev = NUWW;
	whiwe (1) {
		pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_I5000_DEV16, pdev);

		if (pdev == NUWW) {
			i5000_pwintk(KEWN_EWW,
				"MC: 'bwanchmap,contwow,ewwows' "
				"device not found:"
				"vendow 0x%x device 0x%x Func 2 "
				"(bwoken BIOS?)\n",
				PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_INTEW_I5000_DEV16);

			pci_dev_put(pvt->bwanchmap_wewwows);
			wetuwn 1;
		}

		/* Scan fow device 16 func 1 */
		if (PCI_FUNC(pdev->devfn) == 2)
			bweak;
	}

	pvt->fsb_ewwow_wegs = pdev;

	edac_dbg(1, "System Addwess, pwocessow bus- PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->system_addwess),
		 pvt->system_addwess->vendow, pvt->system_addwess->device);
	edac_dbg(1, "Bwanchmap, contwow and ewwows - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->bwanchmap_wewwows),
		 pvt->bwanchmap_wewwows->vendow,
		 pvt->bwanchmap_wewwows->device);
	edac_dbg(1, "FSB Ewwow Wegs - PCI Bus ID: %s  %x:%x\n",
		 pci_name(pvt->fsb_ewwow_wegs),
		 pvt->fsb_ewwow_wegs->vendow, pvt->fsb_ewwow_wegs->device);

	pdev = NUWW;
	pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
			PCI_DEVICE_ID_I5000_BWANCH_0, pdev);

	if (pdev == NUWW) {
		i5000_pwintk(KEWN_EWW,
			"MC: 'BWANCH 0' device not found:"
			"vendow 0x%x device 0x%x Func 0 (bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_I5000_BWANCH_0);

		pci_dev_put(pvt->bwanchmap_wewwows);
		pci_dev_put(pvt->fsb_ewwow_wegs);
		wetuwn 1;
	}

	pvt->bwanch_0 = pdev;

	/* If this device cwaims to have mowe than 2 channews then
	 * fetch Bwanch 1's infowmation
	 */
	if (pvt->maxch >= CHANNEWS_PEW_BWANCH) {
		pdev = NUWW;
		pdev = pci_get_device(PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_I5000_BWANCH_1, pdev);

		if (pdev == NUWW) {
			i5000_pwintk(KEWN_EWW,
				"MC: 'BWANCH 1' device not found:"
				"vendow 0x%x device 0x%x Func 0 "
				"(bwoken BIOS?)\n",
				PCI_VENDOW_ID_INTEW,
				PCI_DEVICE_ID_I5000_BWANCH_1);

			pci_dev_put(pvt->bwanchmap_wewwows);
			pci_dev_put(pvt->fsb_ewwow_wegs);
			pci_dev_put(pvt->bwanch_0);
			wetuwn 1;
		}

		pvt->bwanch_1 = pdev;
	}

	wetuwn 0;
}

/*
 *	i5000_put_devices	'put' aww the devices that we have
 *				wesewved via 'get'
 */
static void i5000_put_devices(stwuct mem_ctw_info *mci)
{
	stwuct i5000_pvt *pvt;

	pvt = mci->pvt_info;

	pci_dev_put(pvt->bwanchmap_wewwows);	/* FUNC 1 */
	pci_dev_put(pvt->fsb_ewwow_wegs);	/* FUNC 2 */
	pci_dev_put(pvt->bwanch_0);	/* DEV 21 */

	/* Onwy if mowe than 2 channews do we wewease the second bwanch */
	if (pvt->maxch >= CHANNEWS_PEW_BWANCH)
		pci_dev_put(pvt->bwanch_1);	/* DEV 22 */
}

/*
 *	detewmine_amb_wesent
 *
 *		the infowmation is contained in NUM_MTWS diffewent wegistews
 *		detewmineing which of the NUM_MTWS wequiwes knowing
 *		which channew is in question
 *
 *	2 bwanches, each with 2 channews
 *		b0_ambpwesent0 fow channew '0'
 *		b0_ambpwesent1 fow channew '1'
 *		b1_ambpwesent0 fow channew '2'
 *		b1_ambpwesent1 fow channew '3'
 */
static int detewmine_amb_pwesent_weg(stwuct i5000_pvt *pvt, int channew)
{
	int amb_pwesent;

	if (channew < CHANNEWS_PEW_BWANCH) {
		if (channew & 0x1)
			amb_pwesent = pvt->b0_ambpwesent1;
		ewse
			amb_pwesent = pvt->b0_ambpwesent0;
	} ewse {
		if (channew & 0x1)
			amb_pwesent = pvt->b1_ambpwesent1;
		ewse
			amb_pwesent = pvt->b1_ambpwesent0;
	}

	wetuwn amb_pwesent;
}

/*
 * detewmine_mtw(pvt, cswow, channew)
 *
 *	wetuwn the pwopew MTW wegistew as detewmine by the cswow and channew desiwed
 */
static int detewmine_mtw(stwuct i5000_pvt *pvt, int swot, int channew)
{
	int mtw;

	if (channew < CHANNEWS_PEW_BWANCH)
		mtw = pvt->b0_mtw[swot];
	ewse
		mtw = pvt->b1_mtw[swot];

	wetuwn mtw;
}

/*
 */
static void decode_mtw(int swot_wow, u16 mtw)
{
	int ans;

	ans = MTW_DIMMS_PWESENT(mtw);

	edac_dbg(2, "\tMTW%d=0x%x:  DIMMs awe %sPwesent\n",
		 swot_wow, mtw, ans ? "" : "NOT ");
	if (!ans)
		wetuwn;

	edac_dbg(2, "\t\tWIDTH: x%d\n", MTW_DWAM_WIDTH(mtw));
	edac_dbg(2, "\t\tNUMBANK: %d bank(s)\n", MTW_DWAM_BANKS(mtw));
	edac_dbg(2, "\t\tNUMWANK: %s\n",
		 MTW_DIMM_WANK(mtw) ? "doubwe" : "singwe");
	edac_dbg(2, "\t\tNUMWOW: %s\n",
		 MTW_DIMM_WOWS(mtw) == 0 ? "8,192 - 13 wows" :
		 MTW_DIMM_WOWS(mtw) == 1 ? "16,384 - 14 wows" :
		 MTW_DIMM_WOWS(mtw) == 2 ? "32,768 - 15 wows" :
		 "wesewved");
	edac_dbg(2, "\t\tNUMCOW: %s\n",
		 MTW_DIMM_COWS(mtw) == 0 ? "1,024 - 10 cowumns" :
		 MTW_DIMM_COWS(mtw) == 1 ? "2,048 - 11 cowumns" :
		 MTW_DIMM_COWS(mtw) == 2 ? "4,096 - 12 cowumns" :
		 "wesewved");
}

static void handwe_channew(stwuct i5000_pvt *pvt, int swot, int channew,
			stwuct i5000_dimm_info *dinfo)
{
	int mtw;
	int amb_pwesent_weg;
	int addwBits;

	mtw = detewmine_mtw(pvt, swot, channew);
	if (MTW_DIMMS_PWESENT(mtw)) {
		amb_pwesent_weg = detewmine_amb_pwesent_weg(pvt, channew);

		/* Detewmine if thewe is a DIMM pwesent in this DIMM swot */
		if (amb_pwesent_weg) {
			dinfo->duaw_wank = MTW_DIMM_WANK(mtw);

			/* Stawt with the numbew of bits fow a Bank
				* on the DWAM */
			addwBits = MTW_DWAM_BANKS_ADDW_BITS(mtw);
			/* Add the numbew of WOW bits */
			addwBits += MTW_DIMM_WOWS_ADDW_BITS(mtw);
			/* add the numbew of COWUMN bits */
			addwBits += MTW_DIMM_COWS_ADDW_BITS(mtw);

			/* Duaw-wank memowies have twice the size */
			if (dinfo->duaw_wank)
				addwBits++;

			addwBits += 6;	/* add 64 bits pew DIMM */
			addwBits -= 20;	/* divide by 2^^20 */
			addwBits -= 3;	/* 8 bits pew bytes */

			dinfo->megabytes = 1 << addwBits;
		}
	}
}

/*
 *	cawcuwate_dimm_size
 *
 *	awso wiww output a DIMM matwix map, if debug is enabwed, fow viewing
 *	how the DIMMs awe popuwated
 */
static void cawcuwate_dimm_size(stwuct i5000_pvt *pvt)
{
	stwuct i5000_dimm_info *dinfo;
	int swot, channew, bwanch;
	chaw *p, *mem_buffew;
	int space, n;

	/* ================= Genewate some debug output ================= */
	space = PAGE_SIZE;
	mem_buffew = p = kmawwoc(space, GFP_KEWNEW);
	if (p == NUWW) {
		i5000_pwintk(KEWN_EWW, "MC: %s:%s() kmawwoc() faiwed\n",
			__FIWE__, __func__);
		wetuwn;
	}

	/* Scan aww the actuaw swots
	 * and cawcuwate the infowmation fow each DIMM
	 * Stawt with the highest swot fiwst, to dispway it fiwst
	 * and wowk towawd the 0th swot
	 */
	fow (swot = pvt->maxdimmpewch - 1; swot >= 0; swot--) {

		/* on an odd swot, fiwst output a 'boundawy' mawkew,
		 * then weset the message buffew  */
		if (swot & 0x1) {
			n = snpwintf(p, space, "--------------------------"
				"--------------------------------");
			p += n;
			space -= n;
			edac_dbg(2, "%s\n", mem_buffew);
			p = mem_buffew;
			space = PAGE_SIZE;
		}
		n = snpwintf(p, space, "swot %2d    ", swot);
		p += n;
		space -= n;

		fow (channew = 0; channew < pvt->maxch; channew++) {
			dinfo = &pvt->dimm_info[swot][channew];
			handwe_channew(pvt, swot, channew, dinfo);
			if (dinfo->megabytes)
				n = snpwintf(p, space, "%4d MB %dW| ",
					     dinfo->megabytes, dinfo->duaw_wank + 1);
			ewse
				n = snpwintf(p, space, "%4d MB   | ", 0);
			p += n;
			space -= n;
		}
		p += n;
		space -= n;
		edac_dbg(2, "%s\n", mem_buffew);
		p = mem_buffew;
		space = PAGE_SIZE;
	}

	/* Output the wast bottom 'boundawy' mawkew */
	n = snpwintf(p, space, "--------------------------"
		"--------------------------------");
	p += n;
	space -= n;
	edac_dbg(2, "%s\n", mem_buffew);
	p = mem_buffew;
	space = PAGE_SIZE;

	/* now output the 'channew' wabews */
	n = snpwintf(p, space, "           ");
	p += n;
	space -= n;
	fow (channew = 0; channew < pvt->maxch; channew++) {
		n = snpwintf(p, space, "channew %d | ", channew);
		p += n;
		space -= n;
	}
	edac_dbg(2, "%s\n", mem_buffew);
	p = mem_buffew;
	space = PAGE_SIZE;

	n = snpwintf(p, space, "           ");
	p += n;
	fow (bwanch = 0; bwanch < MAX_BWANCHES; bwanch++) {
		n = snpwintf(p, space, "       bwanch %d       | ", bwanch);
		p += n;
		space -= n;
	}

	/* output the wast message and fwee buffew */
	edac_dbg(2, "%s\n", mem_buffew);
	kfwee(mem_buffew);
}

/*
 *	i5000_get_mc_wegs	wead in the necessawy wegistews and
 *				cache wocawwy
 *
 *			Fiwws in the pwivate data membews
 */
static void i5000_get_mc_wegs(stwuct mem_ctw_info *mci)
{
	stwuct i5000_pvt *pvt;
	u32 actuaw_towm;
	u16 wimit;
	int swot_wow;
	int way0, way1;

	pvt = mci->pvt_info;

	pci_wead_config_dwowd(pvt->system_addwess, AMBASE,
			&pvt->u.ambase_bottom);
	pci_wead_config_dwowd(pvt->system_addwess, AMBASE + sizeof(u32),
			&pvt->u.ambase_top);

	edac_dbg(2, "AMBASE= 0x%wx  MAXCH= %d  MAX-DIMM-Pew-CH= %d\n",
		 (wong unsigned int)pvt->ambase, pvt->maxch, pvt->maxdimmpewch);

	/* Get the Bwanch Map wegs */
	pci_wead_config_wowd(pvt->bwanchmap_wewwows, TOWM, &pvt->towm);
	pvt->towm >>= 12;
	edac_dbg(2, "TOWM (numbew of 256M wegions) =%u (0x%x)\n",
		 pvt->towm, pvt->towm);

	actuaw_towm = pvt->towm << 28;
	edac_dbg(2, "Actuaw TOWM byte addw=%u (0x%x)\n",
		 actuaw_towm, actuaw_towm);

	pci_wead_config_wowd(pvt->bwanchmap_wewwows, MIW0, &pvt->miw0);
	pci_wead_config_wowd(pvt->bwanchmap_wewwows, MIW1, &pvt->miw1);
	pci_wead_config_wowd(pvt->bwanchmap_wewwows, MIW2, &pvt->miw2);

	/* Get the MIW[0-2] wegs */
	wimit = (pvt->miw0 >> 4) & 0x0FFF;
	way0 = pvt->miw0 & 0x1;
	way1 = pvt->miw0 & 0x2;
	edac_dbg(2, "MIW0: wimit= 0x%x  WAY1= %u  WAY0= %x\n",
		 wimit, way1, way0);
	wimit = (pvt->miw1 >> 4) & 0x0FFF;
	way0 = pvt->miw1 & 0x1;
	way1 = pvt->miw1 & 0x2;
	edac_dbg(2, "MIW1: wimit= 0x%x  WAY1= %u  WAY0= %x\n",
		 wimit, way1, way0);
	wimit = (pvt->miw2 >> 4) & 0x0FFF;
	way0 = pvt->miw2 & 0x1;
	way1 = pvt->miw2 & 0x2;
	edac_dbg(2, "MIW2: wimit= 0x%x  WAY1= %u  WAY0= %x\n",
		 wimit, way1, way0);

	/* Get the MTW[0-3] wegs */
	fow (swot_wow = 0; swot_wow < NUM_MTWS; swot_wow++) {
		int whewe = MTW0 + (swot_wow * sizeof(u32));

		pci_wead_config_wowd(pvt->bwanch_0, whewe,
				&pvt->b0_mtw[swot_wow]);

		edac_dbg(2, "MTW%d whewe=0x%x B0 vawue=0x%x\n",
			 swot_wow, whewe, pvt->b0_mtw[swot_wow]);

		if (pvt->maxch >= CHANNEWS_PEW_BWANCH) {
			pci_wead_config_wowd(pvt->bwanch_1, whewe,
					&pvt->b1_mtw[swot_wow]);
			edac_dbg(2, "MTW%d whewe=0x%x B1 vawue=0x%x\n",
				 swot_wow, whewe, pvt->b1_mtw[swot_wow]);
		} ewse {
			pvt->b1_mtw[swot_wow] = 0;
		}
	}

	/* Wead and dump bwanch 0's MTWs */
	edac_dbg(2, "Memowy Technowogy Wegistews:\n");
	edac_dbg(2, "   Bwanch 0:\n");
	fow (swot_wow = 0; swot_wow < NUM_MTWS; swot_wow++) {
		decode_mtw(swot_wow, pvt->b0_mtw[swot_wow]);
	}
	pci_wead_config_wowd(pvt->bwanch_0, AMB_PWESENT_0,
			&pvt->b0_ambpwesent0);
	edac_dbg(2, "\t\tAMB-Bwanch 0-pwesent0 0x%x:\n", pvt->b0_ambpwesent0);
	pci_wead_config_wowd(pvt->bwanch_0, AMB_PWESENT_1,
			&pvt->b0_ambpwesent1);
	edac_dbg(2, "\t\tAMB-Bwanch 0-pwesent1 0x%x:\n", pvt->b0_ambpwesent1);

	/* Onwy if we have 2 bwanchs (4 channews) */
	if (pvt->maxch < CHANNEWS_PEW_BWANCH) {
		pvt->b1_ambpwesent0 = 0;
		pvt->b1_ambpwesent1 = 0;
	} ewse {
		/* Wead and dump  bwanch 1's MTWs */
		edac_dbg(2, "   Bwanch 1:\n");
		fow (swot_wow = 0; swot_wow < NUM_MTWS; swot_wow++) {
			decode_mtw(swot_wow, pvt->b1_mtw[swot_wow]);
		}
		pci_wead_config_wowd(pvt->bwanch_1, AMB_PWESENT_0,
				&pvt->b1_ambpwesent0);
		edac_dbg(2, "\t\tAMB-Bwanch 1-pwesent0 0x%x:\n",
			 pvt->b1_ambpwesent0);
		pci_wead_config_wowd(pvt->bwanch_1, AMB_PWESENT_1,
				&pvt->b1_ambpwesent1);
		edac_dbg(2, "\t\tAMB-Bwanch 1-pwesent1 0x%x:\n",
			 pvt->b1_ambpwesent1);
	}

	/* Go and detewmine the size of each DIMM and pwace in an
	 * owdewwy matwix */
	cawcuwate_dimm_size(pvt);
}

/*
 *	i5000_init_cswows	Initiawize the 'cswows' tabwe within
 *				the mci contwow	stwuctuwe with the
 *				addwessing of memowy.
 *
 *	wetuwn:
 *		0	success
 *		1	no actuaw memowy found on this MC
 */
static int i5000_init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct i5000_pvt *pvt;
	stwuct dimm_info *dimm;
	int empty;
	int max_cswows;
	int mtw;
	int cswow_megs;
	int channew;
	int swot;

	pvt = mci->pvt_info;
	max_cswows = pvt->maxdimmpewch * 2;

	empty = 1;		/* Assume NO memowy */

	/*
	 * FIXME: The memowy wayout used to map swot/channew into the
	 * weaw memowy awchitectuwe is weiwd: bwanch+swot awe "cswows"
	 * and channew is channew. That wequiwed an extwa awway (dimm_info)
	 * to map the dimms. A good cweanup wouwd be to wemove this awway,
	 * and do a woop hewe with bwanch, channew, swot
	 */
	fow (swot = 0; swot < max_cswows; swot++) {
		fow (channew = 0; channew < pvt->maxch; channew++) {

			mtw = detewmine_mtw(pvt, swot, channew);

			if (!MTW_DIMMS_PWESENT(mtw))
				continue;

			dimm = edac_get_dimm(mci, channew / MAX_BWANCHES,
					     channew % MAX_BWANCHES, swot);

			cswow_megs = pvt->dimm_info[swot][channew].megabytes;
			dimm->gwain = 8;

			/* Assume DDW2 fow now */
			dimm->mtype = MEM_FB_DDW2;

			/* ask what device type on this wow */
			if (MTW_DWAM_WIDTH(mtw) == 8)
				dimm->dtype = DEV_X8;
			ewse
				dimm->dtype = DEV_X4;

			dimm->edac_mode = EDAC_S8ECD8ED;
			dimm->nw_pages = cswow_megs << 8;
		}

		empty = 0;
	}

	wetuwn empty;
}

/*
 *	i5000_enabwe_ewwow_wepowting
 *			Tuwn on the memowy wepowting featuwes of the hawdwawe
 */
static void i5000_enabwe_ewwow_wepowting(stwuct mem_ctw_info *mci)
{
	stwuct i5000_pvt *pvt;
	u32 fbd_ewwow_mask;

	pvt = mci->pvt_info;

	/* Wead the FBD Ewwow Mask Wegistew */
	pci_wead_config_dwowd(pvt->bwanchmap_wewwows, EMASK_FBD,
			&fbd_ewwow_mask);

	/* Enabwe with a '0' */
	fbd_ewwow_mask &= ~(ENABWE_EMASK_AWW);

	pci_wwite_config_dwowd(pvt->bwanchmap_wewwows, EMASK_FBD,
			fbd_ewwow_mask);
}

/*
 * i5000_get_dimm_and_channew_counts(pdev, &nw_cswows, &num_channews)
 *
 *	ask the device how many channews awe pwesent and how many CSWOWS
 *	 as weww
 */
static void i5000_get_dimm_and_channew_counts(stwuct pci_dev *pdev,
					int *num_dimms_pew_channew,
					int *num_channews)
{
	u8 vawue;

	/* Need to wetwieve just how many channews and dimms pew channew awe
	 * suppowted on this memowy contwowwew
	 */
	pci_wead_config_byte(pdev, MAXDIMMPEWCH, &vawue);
	*num_dimms_pew_channew = (int)vawue;

	pci_wead_config_byte(pdev, MAXCH, &vawue);
	*num_channews = (int)vawue;
}

/*
 *	i5000_pwobe1	Pwobe fow ONE instance of device to see if it is
 *			pwesent.
 *	wetuwn:
 *		0 fow FOUND a device
 *		< 0 fow ewwow code
 */
static int i5000_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[3];
	stwuct i5000_pvt *pvt;
	int num_channews;
	int num_dimms_pew_channew;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->numbew,
		 PCI_SWOT(pdev->devfn), PCI_FUNC(pdev->devfn));

	/* We onwy awe wooking fow func 0 of the set */
	if (PCI_FUNC(pdev->devfn) != 0)
		wetuwn -ENODEV;

	/* Ask the devices fow the numbew of CSWOWS and CHANNEWS so
	 * that we can cawcuwate the memowy wesouwces, etc
	 *
	 * The Chipset wiww wepowt what it can handwe which wiww be gweatew
	 * ow equaw to what the mothewboawd manufactuwew wiww impwement.
	 *
	 * As we don't have a mothewboawd identification woutine to detewmine
	 * actuaw numbew of swots/dimms pew channew, we thus utiwize the
	 * wesouwce as specified by the chipset. Thus, we might have
	 * have mowe DIMMs pew channew than actuawwy on the mobo, but this
	 * awwows the dwivew to suppowt up to the chipset max, without
	 * some fancy mobo detewmination.
	 */
	i5000_get_dimm_and_channew_counts(pdev, &num_dimms_pew_channew,
					&num_channews);

	edac_dbg(0, "MC: Numbew of Bwanches=2 Channews= %d  DIMMS= %d\n",
		 num_channews, num_dimms_pew_channew);

	/* awwocate a new MC contwow stwuctuwe */

	wayews[0].type = EDAC_MC_WAYEW_BWANCH;
	wayews[0].size = MAX_BWANCHES;
	wayews[0].is_viwt_cswow = fawse;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = num_channews / MAX_BWANCHES;
	wayews[1].is_viwt_cswow = fawse;
	wayews[2].type = EDAC_MC_WAYEW_SWOT;
	wayews[2].size = num_dimms_pew_channew;
	wayews[2].is_viwt_cswow = twue;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;	/* wecowd ptw  to the genewic device */

	pvt = mci->pvt_info;
	pvt->system_addwess = pdev;	/* Wecowd this device in ouw pwivate */
	pvt->maxch = num_channews;
	pvt->maxdimmpewch = num_dimms_pew_channew;

	/* 'get' the pci devices we want to wesewve fow ouw use */
	if (i5000_get_devices(mci, dev_idx))
		goto faiw0;

	/* Time to get sewious */
	i5000_get_mc_wegs(mci);	/* wetwieve the hawdwawe wegistews */

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FWAG_FB_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_NONE;
	mci->edac_cap = EDAC_FWAG_NONE;
	mci->mod_name = "i5000_edac.c";
	mci->ctw_name = i5000_devs[dev_idx].ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->ctw_page_to_phys = NUWW;

	/* Set the function pointew to an actuaw opewation function */
	mci->edac_check = i5000_check_ewwow;

	/* initiawize the MC contwow stwuctuwe 'cswows' tabwe
	 * with the mapping and contwow infowmation */
	if (i5000_init_cswows(mci)) {
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FWAG_NONE because i5000_init_cswows() wetuwned nonzewo vawue\n");
		mci->edac_cap = EDAC_FWAG_NONE;	/* no cswows found */
	} ewse {
		edac_dbg(1, "MC: Enabwe ewwow wepowting now\n");
		i5000_enabwe_ewwow_wepowting(mci);
	}

	/* add this new MC contwow stwuctuwe to EDAC's wist of MCs */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(0, "MC: faiwed edac_mc_add_mc()\n");
		/* FIXME: pewhaps some code shouwd go hewe that disabwes ewwow
		 * wepowting if we just enabwed it
		 */
		goto faiw1;
	}

	i5000_cweaw_ewwow(mci);

	/* awwocating genewic PCI contwow info */
	i5000_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!i5000_pci) {
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

	i5000_put_devices(mci);

faiw0:
	edac_mc_fwee(mci);
	wetuwn -ENODEV;
}

/*
 *	i5000_init_one	constwuctow fow one instance of device
 *
 * 	wetuwns:
 *		negative on ewwow
 *		count (>= 0)
 */
static int i5000_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wc;

	edac_dbg(0, "MC:\n");

	/* wake up device */
	wc = pci_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* now pwobe and enabwe the device */
	wetuwn i5000_pwobe1(pdev, id->dwivew_data);
}

/*
 *	i5000_wemove_one	destwuctow fow one instance of device
 *
 */
static void i5000_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;

	edac_dbg(0, "\n");

	if (i5000_pci)
		edac_pci_wewease_genewic_ctw(i5000_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	/* wetwieve wefewences to wesouwces, and fwee those wesouwces */
	i5000_put_devices(mci);
	edac_mc_fwee(mci);
}

/*
 *	pci_device_id	tabwe fow which devices we awe wooking fow
 *
 *	The "E500P" device is the fiwst device suppowted.
 */
static const stwuct pci_device_id i5000_pci_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_I5000_DEV16),
	 .dwivew_data = I5000P},

	{0,}			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, i5000_pci_tbw);

/*
 *	i5000_dwivew	pci_dwivew stwuctuwe fow this moduwe
 *
 */
static stwuct pci_dwivew i5000_dwivew = {
	.name = KBUIWD_BASENAME,
	.pwobe = i5000_init_one,
	.wemove = i5000_wemove_one,
	.id_tabwe = i5000_pci_tbw,
};

/*
 *	i5000_init		Moduwe entwy function
 *			Twy to initiawize this moduwe fow its devices
 */
static int __init i5000_init(void)
{
	int pci_wc;

	edac_dbg(2, "MC:\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&i5000_dwivew);

	wetuwn (pci_wc < 0) ? pci_wc : 0;
}

/*
 *	i5000_exit()	Moduwe exit function
 *			Unwegistew the dwivew
 */
static void __exit i5000_exit(void)
{
	edac_dbg(2, "MC:\n");
	pci_unwegistew_dwivew(&i5000_dwivew);
}

moduwe_init(i5000_init);
moduwe_exit(i5000_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winux Netwowx (http://wnxi.com) Doug Thompson <nowsk5@xmission.com>");
MODUWE_DESCWIPTION("MC Dwivew fow Intew I5000 memowy contwowwews - " I5000_WEVISION);

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");
moduwe_pawam(misc_messages, int, 0444);
MODUWE_PAWM_DESC(misc_messages, "Wog miscewwaneous non fataw messages");
