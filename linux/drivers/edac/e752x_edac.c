/*
 * Intew e752x Memowy Contwowwew kewnew moduwe
 * (C) 2004 Winux Netwowx (http://wnxi.com)
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Impwement suppowt fow the e7520, E7525, e7320 and i3100 memowy contwowwews.
 *
 * Datasheets:
 *	https://www.intew.in/content/www/in/en/chipsets/e7525-memowy-contwowwew-hub-datasheet.htmw
 *	ftp://downwoad.intew.com/design/intawch/datashts/31345803.pdf
 *
 * Wwitten by Tom Zimmewman
 *
 * Contwibutows:
 * 	Thayne Hawbaugh at weawmsys.com (?)
 * 	Wang Zhenyu at intew.com
 * 	Dave Jiang at mvista.com
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude "edac_moduwe.h"

#define EDAC_MOD_STW	"e752x_edac"

static int wepowt_non_memowy_ewwows;
static int fowce_function_unhide;
static int sysbus_pawity = -1;

static stwuct edac_pci_ctw_info *e752x_pci;

#define e752x_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "e752x", fmt, ##awg)

#define e752x_mc_pwintk(mci, wevew, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "e752x", fmt, ##awg)

#ifndef PCI_DEVICE_ID_INTEW_7520_0
#define PCI_DEVICE_ID_INTEW_7520_0      0x3590
#endif				/* PCI_DEVICE_ID_INTEW_7520_0      */

#ifndef PCI_DEVICE_ID_INTEW_7520_1_EWW
#define PCI_DEVICE_ID_INTEW_7520_1_EWW  0x3591
#endif				/* PCI_DEVICE_ID_INTEW_7520_1_EWW  */

#ifndef PCI_DEVICE_ID_INTEW_7525_0
#define PCI_DEVICE_ID_INTEW_7525_0      0x359E
#endif				/* PCI_DEVICE_ID_INTEW_7525_0      */

#ifndef PCI_DEVICE_ID_INTEW_7525_1_EWW
#define PCI_DEVICE_ID_INTEW_7525_1_EWW  0x3593
#endif				/* PCI_DEVICE_ID_INTEW_7525_1_EWW  */

#ifndef PCI_DEVICE_ID_INTEW_7320_0
#define PCI_DEVICE_ID_INTEW_7320_0	0x3592
#endif				/* PCI_DEVICE_ID_INTEW_7320_0 */

#ifndef PCI_DEVICE_ID_INTEW_7320_1_EWW
#define PCI_DEVICE_ID_INTEW_7320_1_EWW	0x3593
#endif				/* PCI_DEVICE_ID_INTEW_7320_1_EWW */

#ifndef PCI_DEVICE_ID_INTEW_3100_0
#define PCI_DEVICE_ID_INTEW_3100_0	0x35B0
#endif				/* PCI_DEVICE_ID_INTEW_3100_0 */

#ifndef PCI_DEVICE_ID_INTEW_3100_1_EWW
#define PCI_DEVICE_ID_INTEW_3100_1_EWW	0x35B1
#endif				/* PCI_DEVICE_ID_INTEW_3100_1_EWW */

#define E752X_NW_CSWOWS		8	/* numbew of cswows */

/* E752X wegistew addwesses - device 0 function 0 */
#define E752X_MCHSCWB		0x52	/* Memowy Scwub wegistew (16b) */
					/*
					 * 6:5     Scwub Compwetion Count
					 * 3:2     Scwub Wate (i3100 onwy)
					 *      01=fast 10=nowmaw
					 * 1:0     Scwub Mode enabwe
					 *      00=off 10=on
					 */
#define E752X_DWB		0x60	/* DWAM wow boundawy wegistew (8b) */
#define E752X_DWA		0x70	/* DWAM wow attwibute wegistew (8b) */
					/*
					 * 31:30   Device width wow 7
					 *      01=x8 10=x4 11=x8 DDW2
					 * 27:26   Device width wow 6
					 * 23:22   Device width wow 5
					 * 19:20   Device width wow 4
					 * 15:14   Device width wow 3
					 * 11:10   Device width wow 2
					 *  7:6    Device width wow 1
					 *  3:2    Device width wow 0
					 */
#define E752X_DWC		0x7C	/* DWAM contwowwew mode weg (32b) */
					/* FIXME:IS THIS WIGHT? */
					/*
					 * 22    Numbew channews 0=1,1=2
					 * 19:18 DWB Gwanuwawity 32/64MB
					 */
#define E752X_DWM		0x80	/* Dimm mapping wegistew */
#define E752X_DDWCSW		0x9A	/* DDW contwow and status weg (16b) */
					/*
					 * 14:12 1 singwe A, 2 singwe B, 3 duaw
					 */
#define E752X_TOWM		0xC4	/* DWAM top of wow memowy weg (16b) */
#define E752X_WEMAPBASE		0xC6	/* DWAM wemap base addwess weg (16b) */
#define E752X_WEMAPWIMIT	0xC8	/* DWAM wemap wimit addwess weg (16b) */
#define E752X_WEMAPOFFSET	0xCA	/* DWAM wemap wimit offset weg (16b) */

/* E752X wegistew addwesses - device 0 function 1 */
#define E752X_FEWW_GWOBAW	0x40	/* Gwobaw fiwst ewwow wegistew (32b) */
#define E752X_NEWW_GWOBAW	0x44	/* Gwobaw next ewwow wegistew (32b) */
#define E752X_HI_FEWW		0x50	/* Hub intewface fiwst ewwow weg (8b) */
#define E752X_HI_NEWW		0x52	/* Hub intewface next ewwow weg (8b) */
#define E752X_HI_EWWMASK	0x54	/* Hub intewface ewwow mask weg (8b) */
#define E752X_HI_SMICMD		0x5A	/* Hub intewface SMI command weg (8b) */
#define E752X_SYSBUS_FEWW	0x60	/* System buss fiwst ewwow weg (16b) */
#define E752X_SYSBUS_NEWW	0x62	/* System buss next ewwow weg (16b) */
#define E752X_SYSBUS_EWWMASK	0x64	/* System buss ewwow mask weg (16b) */
#define E752X_SYSBUS_SMICMD	0x6A	/* System buss SMI command weg (16b) */
#define E752X_BUF_FEWW		0x70	/* Memowy buffew fiwst ewwow weg (8b) */
#define E752X_BUF_NEWW		0x72	/* Memowy buffew next ewwow weg (8b) */
#define E752X_BUF_EWWMASK	0x74	/* Memowy buffew ewwow mask weg (8b) */
#define E752X_BUF_SMICMD	0x7A	/* Memowy buffew SMI cmd weg (8b) */
#define E752X_DWAM_FEWW		0x80	/* DWAM fiwst ewwow wegistew (16b) */
#define E752X_DWAM_NEWW		0x82	/* DWAM next ewwow wegistew (16b) */
#define E752X_DWAM_EWWMASK	0x84	/* DWAM ewwow mask wegistew (8b) */
#define E752X_DWAM_SMICMD	0x8A	/* DWAM SMI command wegistew (8b) */
#define E752X_DWAM_WETW_ADD	0xAC	/* DWAM Wetwy addwess wegistew (32b) */
#define E752X_DWAM_SEC1_ADD	0xA0	/* DWAM fiwst cowwectabwe memowy */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31    Wesewved
					 * 30:2  CE addwess (64 byte bwock 34:6
					 * 1     Wesewved
					 * 0     HiWoCS
					 */
#define E752X_DWAM_SEC2_ADD	0xC8	/* DWAM fiwst cowwectabwe memowy */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31    Wesewved
					 * 30:2  CE addwess (64 byte bwock 34:6)
					 * 1     Wesewved
					 * 0     HiWoCS
					 */
#define E752X_DWAM_DED_ADD	0xA4	/* DWAM fiwst uncowwectabwe memowy */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31    Wesewved
					 * 30:2  CE addwess (64 byte bwock 34:6)
					 * 1     Wesewved
					 * 0     HiWoCS
					 */
#define E752X_DWAM_SCWB_ADD	0xA8	/* DWAM 1st uncowwectabwe scwub mem */
					/*     ewwow addwess wegistew (32b) */
					/*
					 * 31    Wesewved
					 * 30:2  CE addwess (64 byte bwock 34:6
					 * 1     Wesewved
					 * 0     HiWoCS
					 */
#define E752X_DWAM_SEC1_SYNDWOME 0xC4	/* DWAM fiwst cowwectabwe memowy */
					/*     ewwow syndwome wegistew (16b) */
#define E752X_DWAM_SEC2_SYNDWOME 0xC6	/* DWAM second cowwectabwe memowy */
					/*     ewwow syndwome wegistew (16b) */
#define E752X_DEVPWES1		0xF4	/* Device Pwesent 1 wegistew (8b) */

/* 3100 IMCH specific wegistew addwesses - device 0 function 1 */
#define I3100_NSI_FEWW		0x48	/* NSI fiwst ewwow weg (32b) */
#define I3100_NSI_NEWW		0x4C	/* NSI next ewwow weg (32b) */
#define I3100_NSI_SMICMD	0x54	/* NSI SMI command wegistew (32b) */
#define I3100_NSI_EMASK		0x90	/* NSI ewwow mask wegistew (32b) */

/* ICH5W wegistew addwesses - device 30 function 0 */
#define ICH5W_PCI_STAT		0x06	/* PCI status wegistew (16b) */
#define ICH5W_PCI_2ND_STAT	0x1E	/* PCI status secondawy weg (16b) */
#define ICH5W_PCI_BWIDGE_CTW	0x3E	/* PCI bwidge contwow wegistew (16b) */

enum e752x_chips {
	E7520 = 0,
	E7525 = 1,
	E7320 = 2,
	I3100 = 3
};

/*
 * Those chips Suppowt singwe-wank and duaw-wank memowies onwy.
 *
 * On e752x chips, the odd wows awe pwesent onwy on duaw-wank memowies.
 * Dividing the wank by two wiww pwovide the dimm#
 *
 * i3100 MC has a diffewent mapping: it suppowts onwy 4 wanks.
 *
 * The mapping is (fwom 1 to n):
 *	swot	   singwe-wanked	doubwe-wanked
 *	dimm #1 -> wank #4		NA
 *	dimm #2 -> wank #3		NA
 *	dimm #3 -> wank #2		Wanks 2 and 3
 *	dimm #4 -> wank $1		Wanks 1 and 4
 *
 * FIXME: The cuwwent mapping fow i3100 considews that it suppowts up to 8
 *	  wanks/chanew, but datasheet says that the MC suppowts onwy 4 wanks.
 */

stwuct e752x_pvt {
	stwuct pci_dev *dev_d0f0;
	stwuct pci_dev *dev_d0f1;
	u32 towm;
	u32 wemapbase;
	u32 wemapwimit;
	int mc_symmetwic;
	u8 map[8];
	int map_type;
	const stwuct e752x_dev_info *dev_info;
};

stwuct e752x_dev_info {
	u16 eww_dev;
	u16 ctw_dev;
	const chaw *ctw_name;
};

stwuct e752x_ewwow_info {
	u32 feww_gwobaw;
	u32 neww_gwobaw;
	u32 nsi_feww;	/* 3100 onwy */
	u32 nsi_neww;	/* 3100 onwy */
	u8 hi_feww;	/* aww but 3100 */
	u8 hi_neww;	/* aww but 3100 */
	u16 sysbus_feww;
	u16 sysbus_neww;
	u8 buf_feww;
	u8 buf_neww;
	u16 dwam_feww;
	u16 dwam_neww;
	u32 dwam_sec1_add;
	u32 dwam_sec2_add;
	u16 dwam_sec1_syndwome;
	u16 dwam_sec2_syndwome;
	u32 dwam_ded_add;
	u32 dwam_scwb_add;
	u32 dwam_wetw_add;
};

static const stwuct e752x_dev_info e752x_devs[] = {
	[E7520] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7520_1_EWW,
		.ctw_dev = PCI_DEVICE_ID_INTEW_7520_0,
		.ctw_name = "E7520"},
	[E7525] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7525_1_EWW,
		.ctw_dev = PCI_DEVICE_ID_INTEW_7525_0,
		.ctw_name = "E7525"},
	[E7320] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_7320_1_EWW,
		.ctw_dev = PCI_DEVICE_ID_INTEW_7320_0,
		.ctw_name = "E7320"},
	[I3100] = {
		.eww_dev = PCI_DEVICE_ID_INTEW_3100_1_EWW,
		.ctw_dev = PCI_DEVICE_ID_INTEW_3100_0,
		.ctw_name = "3100"},
};

/* Vawid scwub wates fow the e752x/3100 hawdwawe memowy scwubbew. We
 * map the scwubbing bandwidth to a hawdwawe wegistew vawue. The 'set'
 * opewation finds the 'matching ow highew vawue'.  Note that scwubbing
 * on the e752x can onwy be enabwed/disabwed.  The 3100 suppowts
 * a nowmaw and fast mode.
 */

#define SDWATE_EOT 0xFFFFFFFF

stwuct scwubwate {
	u32 bandwidth;	/* bandwidth consumed by scwubbing in bytes/sec */
	u16 scwubvaw;	/* wegistew vawue fow scwub wate */
};

/* Wate bewow assumes same pewfowmance as i3100 using PC3200 DDW2 in
 * nowmaw mode.  e752x bwidges don't suppowt choosing nowmaw ow fast mode,
 * so the scwubbing bandwidth vawue isn't aww that impowtant - scwubbing is
 * eithew on ow off.
 */
static const stwuct scwubwate scwubwates_e752x[] = {
	{0,		0x00},	/* Scwubbing Off */
	{500000,	0x02},	/* Scwubbing On */
	{SDWATE_EOT,	0x00}	/* End of Tabwe */
};

/* Fast mode: 2 GByte PC3200 DDW2 scwubbed in 33s = 63161283 bytes/s
 * Nowmaw mode: 125 (32000 / 256) times swowew than fast mode.
 */
static const stwuct scwubwate scwubwates_i3100[] = {
	{0,		0x00},	/* Scwubbing Off */
	{500000,	0x0a},	/* Nowmaw mode - 32k cwocks */
	{62500000,	0x06},	/* Fast mode - 256 cwocks */
	{SDWATE_EOT,	0x00}	/* End of Tabwe */
};

static unsigned wong ctw_page_to_phys(stwuct mem_ctw_info *mci,
				unsigned wong page)
{
	u32 wemap;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	if (page < pvt->towm)
		wetuwn page;

	if ((page >= 0x100000) && (page < pvt->wemapbase))
		wetuwn page;

	wemap = (page - pvt->towm) + pvt->wemapbase;

	if (wemap < pvt->wemapwimit)
		wetuwn wemap;

	e752x_pwintk(KEWN_EWW, "Invawid page %wx - out of wange\n", page);
	wetuwn pvt->towm - 1;
}

static void do_pwocess_ce(stwuct mem_ctw_info *mci, u16 ewwow_one,
			u32 sec1_add, u16 sec1_syndwome)
{
	u32 page;
	int wow;
	int channew;
	int i;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	/* convewt the addw to 4k page */
	page = sec1_add >> (PAGE_SHIFT - 4);

	/* FIXME - check fow -1 */
	if (pvt->mc_symmetwic) {
		/* chip sewect awe bits 14 & 13 */
		wow = ((page >> 1) & 3);
		e752x_pwintk(KEWN_WAWNING,
			"Test wow %d Tabwe %d %d %d %d %d %d %d %d\n", wow,
			pvt->map[0], pvt->map[1], pvt->map[2], pvt->map[3],
			pvt->map[4], pvt->map[5], pvt->map[6],
			pvt->map[7]);

		/* test fow channew wemapping */
		fow (i = 0; i < 8; i++) {
			if (pvt->map[i] == wow)
				bweak;
		}

		e752x_pwintk(KEWN_WAWNING, "Test computed wow %d\n", i);

		if (i < 8)
			wow = i;
		ewse
			e752x_mc_pwintk(mci, KEWN_WAWNING,
					"wow %d not found in wemap tabwe\n",
					wow);
	} ewse
		wow = edac_mc_find_cswow_by_page(mci, page);

	/* 0 = channew A, 1 = channew B */
	channew = !(ewwow_one & 1);

	/* e752x mc weads 34:6 of the DWAM wineaw addwess */
	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
			     page, offset_in_page(sec1_add << 4), sec1_syndwome,
			     wow, channew, -1,
			     "e752x CE", "");
}

static inwine void pwocess_ce(stwuct mem_ctw_info *mci, u16 ewwow_one,
			u32 sec1_add, u16 sec1_syndwome, int *ewwow_found,
			int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_pwocess_ce(mci, ewwow_one, sec1_add, sec1_syndwome);
}

static void do_pwocess_ue(stwuct mem_ctw_info *mci, u16 ewwow_one,
			u32 ded_add, u32 scwb_add)
{
	u32 ewwow_2b, bwock_page;
	int wow;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *)mci->pvt_info;

	edac_dbg(3, "\n");

	if (ewwow_one & 0x0202) {
		ewwow_2b = ded_add;

		/* convewt to 4k addwess */
		bwock_page = ewwow_2b >> (PAGE_SHIFT - 4);

		wow = pvt->mc_symmetwic ?
		/* chip sewect awe bits 14 & 13 */
			((bwock_page >> 1) & 3) :
			edac_mc_find_cswow_by_page(mci, bwock_page);

		/* e752x mc weads 34:6 of the DWAM wineaw addwess */
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					bwock_page,
					offset_in_page(ewwow_2b << 4), 0,
					 wow, -1, -1,
					"e752x UE fwom Wead", "");

	}
	if (ewwow_one & 0x0404) {
		ewwow_2b = scwb_add;

		/* convewt to 4k addwess */
		bwock_page = ewwow_2b >> (PAGE_SHIFT - 4);

		wow = pvt->mc_symmetwic ?
		/* chip sewect awe bits 14 & 13 */
			((bwock_page >> 1) & 3) :
			edac_mc_find_cswow_by_page(mci, bwock_page);

		/* e752x mc weads 34:6 of the DWAM wineaw addwess */
		edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					bwock_page,
					offset_in_page(ewwow_2b << 4), 0,
					wow, -1, -1,
					"e752x UE fwom Scwubew", "");
	}
}

static inwine void pwocess_ue(stwuct mem_ctw_info *mci, u16 ewwow_one,
			u32 ded_add, u32 scwb_add, int *ewwow_found,
			int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_pwocess_ue(mci, ewwow_one, ded_add, scwb_add);
}

static inwine void pwocess_ue_no_info_ww(stwuct mem_ctw_info *mci,
					 int *ewwow_found, int handwe_ewwow)
{
	*ewwow_found = 1;

	if (!handwe_ewwow)
		wetuwn;

	edac_dbg(3, "\n");
	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1, 0, 0, 0,
			     -1, -1, -1,
			     "e752x UE wog memowy wwite", "");
}

static void do_pwocess_ded_wetwy(stwuct mem_ctw_info *mci, u16 ewwow,
				 u32 wetwy_add)
{
	u32 ewwow_1b, page;
	int wow;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *)mci->pvt_info;

	ewwow_1b = wetwy_add;
	page = ewwow_1b >> (PAGE_SHIFT - 4);  /* convewt the addw to 4k page */

	/* chip sewect awe bits 14 & 13 */
	wow = pvt->mc_symmetwic ? ((page >> 1) & 3) :
		edac_mc_find_cswow_by_page(mci, page);

	e752x_mc_pwintk(mci, KEWN_WAWNING,
			"CE page 0x%wx, wow %d : Memowy wead wetwy\n",
			(wong unsigned int)page, wow);
}

static inwine void pwocess_ded_wetwy(stwuct mem_ctw_info *mci, u16 ewwow,
				u32 wetwy_add, int *ewwow_found,
				int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_pwocess_ded_wetwy(mci, ewwow, wetwy_add);
}

static inwine void pwocess_thweshowd_ce(stwuct mem_ctw_info *mci, u16 ewwow,
					int *ewwow_found, int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		e752x_mc_pwintk(mci, KEWN_WAWNING, "Memowy thweshowd CE\n");
}

static chaw *gwobaw_message[11] = {
	"PCI Expwess C1",
	"PCI Expwess C",
	"PCI Expwess B1",
	"PCI Expwess B",
	"PCI Expwess A1",
	"PCI Expwess A",
	"DMA Contwowwew",
	"HUB ow NS Intewface",
	"System Bus",
	"DWAM Contwowwew",  /* 9th entwy */
	"Intewnaw Buffew"
};

#define DWAM_ENTWY	9

static chaw *fataw_message[2] = { "Non-Fataw ", "Fataw " };

static void do_gwobaw_ewwow(int fataw, u32 ewwows)
{
	int i;

	fow (i = 0; i < 11; i++) {
		if (ewwows & (1 << i)) {
			/* If the ewwow is fwom DWAM Contwowwew OW
			 * we awe to wepowt AWW ewwows, then
			 * wepowt the ewwow
			 */
			if ((i == DWAM_ENTWY) || wepowt_non_memowy_ewwows)
				e752x_pwintk(KEWN_WAWNING, "%sEwwow %s\n",
					fataw_message[fataw],
					gwobaw_message[i]);
		}
	}
}

static inwine void gwobaw_ewwow(int fataw, u32 ewwows, int *ewwow_found,
				int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_gwobaw_ewwow(fataw, ewwows);
}

static chaw *hub_message[7] = {
	"HI Addwess ow Command Pawity", "HI Iwwegaw Access",
	"HI Intewnaw Pawity", "Out of Wange Access",
	"HI Data Pawity", "Enhanced Config Access",
	"Hub Intewface Tawget Abowt"
};

static void do_hub_ewwow(int fataw, u8 ewwows)
{
	int i;

	fow (i = 0; i < 7; i++) {
		if (ewwows & (1 << i))
			e752x_pwintk(KEWN_WAWNING, "%sEwwow %s\n",
				fataw_message[fataw], hub_message[i]);
	}
}

static inwine void hub_ewwow(int fataw, u8 ewwows, int *ewwow_found,
			int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_hub_ewwow(fataw, ewwows);
}

#define NSI_FATAW_MASK		0x0c080081
#define NSI_NON_FATAW_MASK	0x23a0ba64
#define NSI_EWW_MASK		(NSI_FATAW_MASK | NSI_NON_FATAW_MASK)

static chaw *nsi_message[30] = {
	"NSI Wink Down",	/* NSI_FEWW/NSI_NEWW bit 0, fataw ewwow */
	"",						/* wesewved */
	"NSI Pawity Ewwow",				/* bit 2, non-fataw */
	"",						/* wesewved */
	"",						/* wesewved */
	"Cowwectabwe Ewwow Message",			/* bit 5, non-fataw */
	"Non-Fataw Ewwow Message",			/* bit 6, non-fataw */
	"Fataw Ewwow Message",				/* bit 7, fataw */
	"",						/* wesewved */
	"Weceivew Ewwow",				/* bit 9, non-fataw */
	"",						/* wesewved */
	"Bad TWP",					/* bit 11, non-fataw */
	"Bad DWWP",					/* bit 12, non-fataw */
	"WEPWAY_NUM Wowwovew",				/* bit 13, non-fataw */
	"",						/* wesewved */
	"Wepway Timew Timeout",				/* bit 15, non-fataw */
	"",						/* wesewved */
	"",						/* wesewved */
	"",						/* wesewved */
	"Data Wink Pwotocow Ewwow",			/* bit 19, fataw */
	"",						/* wesewved */
	"Poisoned TWP",					/* bit 21, non-fataw */
	"",						/* wesewved */
	"Compwetion Timeout",				/* bit 23, non-fataw */
	"Compwetew Abowt",				/* bit 24, non-fataw */
	"Unexpected Compwetion",			/* bit 25, non-fataw */
	"Weceivew Ovewfwow",				/* bit 26, fataw */
	"Mawfowmed TWP",				/* bit 27, fataw */
	"",						/* wesewved */
	"Unsuppowted Wequest"				/* bit 29, non-fataw */
};

static void do_nsi_ewwow(int fataw, u32 ewwows)
{
	int i;

	fow (i = 0; i < 30; i++) {
		if (ewwows & (1 << i))
			pwintk(KEWN_WAWNING "%sEwwow %s\n",
			       fataw_message[fataw], nsi_message[i]);
	}
}

static inwine void nsi_ewwow(int fataw, u32 ewwows, int *ewwow_found,
		int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_nsi_ewwow(fataw, ewwows);
}

static chaw *membuf_message[4] = {
	"Intewnaw PMWB to DWAM pawity",
	"Intewnaw PMWB to System Bus Pawity",
	"Intewnaw System Bus ow IO to PMWB Pawity",
	"Intewnaw DWAM to PMWB Pawity"
};

static void do_membuf_ewwow(u8 ewwows)
{
	int i;

	fow (i = 0; i < 4; i++) {
		if (ewwows & (1 << i))
			e752x_pwintk(KEWN_WAWNING, "Non-Fataw Ewwow %s\n",
				membuf_message[i]);
	}
}

static inwine void membuf_ewwow(u8 ewwows, int *ewwow_found, int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_membuf_ewwow(ewwows);
}

static chaw *sysbus_message[10] = {
	"Addw ow Wequest Pawity",
	"Data Stwobe Gwitch",
	"Addw Stwobe Gwitch",
	"Data Pawity",
	"Addw Above TOM",
	"Non DWAM Wock Ewwow",
	"MCEWW", "BINIT",
	"Memowy Pawity",
	"IO Subsystem Pawity"
};

static void do_sysbus_ewwow(int fataw, u32 ewwows)
{
	int i;

	fow (i = 0; i < 10; i++) {
		if (ewwows & (1 << i))
			e752x_pwintk(KEWN_WAWNING, "%sEwwow System Bus %s\n",
				fataw_message[fataw], sysbus_message[i]);
	}
}

static inwine void sysbus_ewwow(int fataw, u32 ewwows, int *ewwow_found,
				int handwe_ewwow)
{
	*ewwow_found = 1;

	if (handwe_ewwow)
		do_sysbus_ewwow(fataw, ewwows);
}

static void e752x_check_hub_intewface(stwuct e752x_ewwow_info *info,
				int *ewwow_found, int handwe_ewwow)
{
	u8 stat8;

	//pci_wead_config_byte(dev,E752X_HI_FEWW,&stat8);

	stat8 = info->hi_feww;

	if (stat8 & 0x7f) {	/* Ewwow, so pwocess */
		stat8 &= 0x7f;

		if (stat8 & 0x2b)
			hub_ewwow(1, stat8 & 0x2b, ewwow_found, handwe_ewwow);

		if (stat8 & 0x54)
			hub_ewwow(0, stat8 & 0x54, ewwow_found, handwe_ewwow);
	}
	//pci_wead_config_byte(dev,E752X_HI_NEWW,&stat8);

	stat8 = info->hi_neww;

	if (stat8 & 0x7f) {	/* Ewwow, so pwocess */
		stat8 &= 0x7f;

		if (stat8 & 0x2b)
			hub_ewwow(1, stat8 & 0x2b, ewwow_found, handwe_ewwow);

		if (stat8 & 0x54)
			hub_ewwow(0, stat8 & 0x54, ewwow_found, handwe_ewwow);
	}
}

static void e752x_check_ns_intewface(stwuct e752x_ewwow_info *info,
				int *ewwow_found, int handwe_ewwow)
{
	u32 stat32;

	stat32 = info->nsi_feww;
	if (stat32 & NSI_EWW_MASK) { /* Ewwow, so pwocess */
		if (stat32 & NSI_FATAW_MASK)	/* check fow fataw ewwows */
			nsi_ewwow(1, stat32 & NSI_FATAW_MASK, ewwow_found,
				  handwe_ewwow);
		if (stat32 & NSI_NON_FATAW_MASK) /* check fow non-fataw ones */
			nsi_ewwow(0, stat32 & NSI_NON_FATAW_MASK, ewwow_found,
				  handwe_ewwow);
	}
	stat32 = info->nsi_neww;
	if (stat32 & NSI_EWW_MASK) {
		if (stat32 & NSI_FATAW_MASK)
			nsi_ewwow(1, stat32 & NSI_FATAW_MASK, ewwow_found,
				  handwe_ewwow);
		if (stat32 & NSI_NON_FATAW_MASK)
			nsi_ewwow(0, stat32 & NSI_NON_FATAW_MASK, ewwow_found,
				  handwe_ewwow);
	}
}

static void e752x_check_sysbus(stwuct e752x_ewwow_info *info,
			int *ewwow_found, int handwe_ewwow)
{
	u32 stat32, ewwow32;

	//pci_wead_config_dwowd(dev,E752X_SYSBUS_FEWW,&stat32);
	stat32 = info->sysbus_feww + (info->sysbus_neww << 16);

	if (stat32 == 0)
		wetuwn;		/* no ewwows */

	ewwow32 = (stat32 >> 16) & 0x3ff;
	stat32 = stat32 & 0x3ff;

	if (stat32 & 0x087)
		sysbus_ewwow(1, stat32 & 0x087, ewwow_found, handwe_ewwow);

	if (stat32 & 0x378)
		sysbus_ewwow(0, stat32 & 0x378, ewwow_found, handwe_ewwow);

	if (ewwow32 & 0x087)
		sysbus_ewwow(1, ewwow32 & 0x087, ewwow_found, handwe_ewwow);

	if (ewwow32 & 0x378)
		sysbus_ewwow(0, ewwow32 & 0x378, ewwow_found, handwe_ewwow);
}

static void e752x_check_membuf(stwuct e752x_ewwow_info *info,
			int *ewwow_found, int handwe_ewwow)
{
	u8 stat8;

	stat8 = info->buf_feww;

	if (stat8 & 0x0f) {	/* Ewwow, so pwocess */
		stat8 &= 0x0f;
		membuf_ewwow(stat8, ewwow_found, handwe_ewwow);
	}

	stat8 = info->buf_neww;

	if (stat8 & 0x0f) {	/* Ewwow, so pwocess */
		stat8 &= 0x0f;
		membuf_ewwow(stat8, ewwow_found, handwe_ewwow);
	}
}

static void e752x_check_dwam(stwuct mem_ctw_info *mci,
			stwuct e752x_ewwow_info *info, int *ewwow_found,
			int handwe_ewwow)
{
	u16 ewwow_one, ewwow_next;

	ewwow_one = info->dwam_feww;
	ewwow_next = info->dwam_neww;

	/* decode and wepowt ewwows */
	if (ewwow_one & 0x0101)	/* check fiwst ewwow cowwectabwe */
		pwocess_ce(mci, ewwow_one, info->dwam_sec1_add,
			info->dwam_sec1_syndwome, ewwow_found, handwe_ewwow);

	if (ewwow_next & 0x0101)	/* check next ewwow cowwectabwe */
		pwocess_ce(mci, ewwow_next, info->dwam_sec2_add,
			info->dwam_sec2_syndwome, ewwow_found, handwe_ewwow);

	if (ewwow_one & 0x4040)
		pwocess_ue_no_info_ww(mci, ewwow_found, handwe_ewwow);

	if (ewwow_next & 0x4040)
		pwocess_ue_no_info_ww(mci, ewwow_found, handwe_ewwow);

	if (ewwow_one & 0x2020)
		pwocess_ded_wetwy(mci, ewwow_one, info->dwam_wetw_add,
				ewwow_found, handwe_ewwow);

	if (ewwow_next & 0x2020)
		pwocess_ded_wetwy(mci, ewwow_next, info->dwam_wetw_add,
				ewwow_found, handwe_ewwow);

	if (ewwow_one & 0x0808)
		pwocess_thweshowd_ce(mci, ewwow_one, ewwow_found, handwe_ewwow);

	if (ewwow_next & 0x0808)
		pwocess_thweshowd_ce(mci, ewwow_next, ewwow_found,
				handwe_ewwow);

	if (ewwow_one & 0x0606)
		pwocess_ue(mci, ewwow_one, info->dwam_ded_add,
			info->dwam_scwb_add, ewwow_found, handwe_ewwow);

	if (ewwow_next & 0x0606)
		pwocess_ue(mci, ewwow_next, info->dwam_ded_add,
			info->dwam_scwb_add, ewwow_found, handwe_ewwow);
}

static void e752x_get_ewwow_info(stwuct mem_ctw_info *mci,
				 stwuct e752x_ewwow_info *info)
{
	stwuct pci_dev *dev;
	stwuct e752x_pvt *pvt;

	memset(info, 0, sizeof(*info));
	pvt = (stwuct e752x_pvt *)mci->pvt_info;
	dev = pvt->dev_d0f1;
	pci_wead_config_dwowd(dev, E752X_FEWW_GWOBAW, &info->feww_gwobaw);

	if (info->feww_gwobaw) {
		if (pvt->dev_info->eww_dev == PCI_DEVICE_ID_INTEW_3100_1_EWW) {
			pci_wead_config_dwowd(dev, I3100_NSI_FEWW,
					     &info->nsi_feww);
			info->hi_feww = 0;
		} ewse {
			pci_wead_config_byte(dev, E752X_HI_FEWW,
					     &info->hi_feww);
			info->nsi_feww = 0;
		}
		pci_wead_config_wowd(dev, E752X_SYSBUS_FEWW,
				&info->sysbus_feww);
		pci_wead_config_byte(dev, E752X_BUF_FEWW, &info->buf_feww);
		pci_wead_config_wowd(dev, E752X_DWAM_FEWW, &info->dwam_feww);
		pci_wead_config_dwowd(dev, E752X_DWAM_SEC1_ADD,
				&info->dwam_sec1_add);
		pci_wead_config_wowd(dev, E752X_DWAM_SEC1_SYNDWOME,
				&info->dwam_sec1_syndwome);
		pci_wead_config_dwowd(dev, E752X_DWAM_DED_ADD,
				&info->dwam_ded_add);
		pci_wead_config_dwowd(dev, E752X_DWAM_SCWB_ADD,
				&info->dwam_scwb_add);
		pci_wead_config_dwowd(dev, E752X_DWAM_WETW_ADD,
				&info->dwam_wetw_add);

		/* ignowe the wesewved bits just in case */
		if (info->hi_feww & 0x7f)
			pci_wwite_config_byte(dev, E752X_HI_FEWW,
					info->hi_feww);

		if (info->nsi_feww & NSI_EWW_MASK)
			pci_wwite_config_dwowd(dev, I3100_NSI_FEWW,
					info->nsi_feww);

		if (info->sysbus_feww)
			pci_wwite_config_wowd(dev, E752X_SYSBUS_FEWW,
					info->sysbus_feww);

		if (info->buf_feww & 0x0f)
			pci_wwite_config_byte(dev, E752X_BUF_FEWW,
					info->buf_feww);

		if (info->dwam_feww)
			pci_wwite_bits16(pvt->dev_d0f1, E752X_DWAM_FEWW,
					 info->dwam_feww, info->dwam_feww);

		pci_wwite_config_dwowd(dev, E752X_FEWW_GWOBAW,
				info->feww_gwobaw);
	}

	pci_wead_config_dwowd(dev, E752X_NEWW_GWOBAW, &info->neww_gwobaw);

	if (info->neww_gwobaw) {
		if (pvt->dev_info->eww_dev == PCI_DEVICE_ID_INTEW_3100_1_EWW) {
			pci_wead_config_dwowd(dev, I3100_NSI_NEWW,
					     &info->nsi_neww);
			info->hi_neww = 0;
		} ewse {
			pci_wead_config_byte(dev, E752X_HI_NEWW,
					     &info->hi_neww);
			info->nsi_neww = 0;
		}
		pci_wead_config_wowd(dev, E752X_SYSBUS_NEWW,
				&info->sysbus_neww);
		pci_wead_config_byte(dev, E752X_BUF_NEWW, &info->buf_neww);
		pci_wead_config_wowd(dev, E752X_DWAM_NEWW, &info->dwam_neww);
		pci_wead_config_dwowd(dev, E752X_DWAM_SEC2_ADD,
				&info->dwam_sec2_add);
		pci_wead_config_wowd(dev, E752X_DWAM_SEC2_SYNDWOME,
				&info->dwam_sec2_syndwome);

		if (info->hi_neww & 0x7f)
			pci_wwite_config_byte(dev, E752X_HI_NEWW,
					info->hi_neww);

		if (info->nsi_neww & NSI_EWW_MASK)
			pci_wwite_config_dwowd(dev, I3100_NSI_NEWW,
					info->nsi_neww);

		if (info->sysbus_neww)
			pci_wwite_config_wowd(dev, E752X_SYSBUS_NEWW,
					info->sysbus_neww);

		if (info->buf_neww & 0x0f)
			pci_wwite_config_byte(dev, E752X_BUF_NEWW,
					info->buf_neww);

		if (info->dwam_neww)
			pci_wwite_bits16(pvt->dev_d0f1, E752X_DWAM_NEWW,
					 info->dwam_neww, info->dwam_neww);

		pci_wwite_config_dwowd(dev, E752X_NEWW_GWOBAW,
				info->neww_gwobaw);
	}
}

static int e752x_pwocess_ewwow_info(stwuct mem_ctw_info *mci,
				stwuct e752x_ewwow_info *info,
				int handwe_ewwows)
{
	u32 ewwow32, stat32;
	int ewwow_found;

	ewwow_found = 0;
	ewwow32 = (info->feww_gwobaw >> 18) & 0x3ff;
	stat32 = (info->feww_gwobaw >> 4) & 0x7ff;

	if (ewwow32)
		gwobaw_ewwow(1, ewwow32, &ewwow_found, handwe_ewwows);

	if (stat32)
		gwobaw_ewwow(0, stat32, &ewwow_found, handwe_ewwows);

	ewwow32 = (info->neww_gwobaw >> 18) & 0x3ff;
	stat32 = (info->neww_gwobaw >> 4) & 0x7ff;

	if (ewwow32)
		gwobaw_ewwow(1, ewwow32, &ewwow_found, handwe_ewwows);

	if (stat32)
		gwobaw_ewwow(0, stat32, &ewwow_found, handwe_ewwows);

	e752x_check_hub_intewface(info, &ewwow_found, handwe_ewwows);
	e752x_check_ns_intewface(info, &ewwow_found, handwe_ewwows);
	e752x_check_sysbus(info, &ewwow_found, handwe_ewwows);
	e752x_check_membuf(info, &ewwow_found, handwe_ewwows);
	e752x_check_dwam(mci, info, &ewwow_found, handwe_ewwows);
	wetuwn ewwow_found;
}

static void e752x_check(stwuct mem_ctw_info *mci)
{
	stwuct e752x_ewwow_info info;

	e752x_get_ewwow_info(mci, &info);
	e752x_pwocess_ewwow_info(mci, &info, 1);
}

/* Pwogwam byte/sec bandwidth scwub wate to hawdwawe */
static int set_sdwam_scwub_wate(stwuct mem_ctw_info *mci, u32 new_bw)
{
	const stwuct scwubwate *scwubwates;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *) mci->pvt_info;
	stwuct pci_dev *pdev = pvt->dev_d0f0;
	int i;

	if (pvt->dev_info->ctw_dev == PCI_DEVICE_ID_INTEW_3100_0)
		scwubwates = scwubwates_i3100;
	ewse
		scwubwates = scwubwates_e752x;

	/* Twanswate the desiwed scwub wate to a e752x/3100 wegistew vawue.
	 * Seawch fow the bandwidth that is equaw ow gweatew than the
	 * desiwed wate and pwogwam the coowesponding wegistew vawue.
	 */
	fow (i = 0; scwubwates[i].bandwidth != SDWATE_EOT; i++)
		if (scwubwates[i].bandwidth >= new_bw)
			bweak;

	if (scwubwates[i].bandwidth == SDWATE_EOT)
		wetuwn -1;

	pci_wwite_config_wowd(pdev, E752X_MCHSCWB, scwubwates[i].scwubvaw);

	wetuwn scwubwates[i].bandwidth;
}

/* Convewt cuwwent scwub wate vawue into byte/sec bandwidth */
static int get_sdwam_scwub_wate(stwuct mem_ctw_info *mci)
{
	const stwuct scwubwate *scwubwates;
	stwuct e752x_pvt *pvt = (stwuct e752x_pvt *) mci->pvt_info;
	stwuct pci_dev *pdev = pvt->dev_d0f0;
	u16 scwubvaw;
	int i;

	if (pvt->dev_info->ctw_dev == PCI_DEVICE_ID_INTEW_3100_0)
		scwubwates = scwubwates_i3100;
	ewse
		scwubwates = scwubwates_e752x;

	/* Find the bandwidth matching the memowy scwubbew configuwation */
	pci_wead_config_wowd(pdev, E752X_MCHSCWB, &scwubvaw);
	scwubvaw = scwubvaw & 0x0f;

	fow (i = 0; scwubwates[i].bandwidth != SDWATE_EOT; i++)
		if (scwubwates[i].scwubvaw == scwubvaw)
			bweak;

	if (scwubwates[i].bandwidth == SDWATE_EOT) {
		e752x_pwintk(KEWN_WAWNING,
			"Invawid sdwam scwub contwow vawue: 0x%x\n", scwubvaw);
		wetuwn -1;
	}
	wetuwn scwubwates[i].bandwidth;

}

/* Wetuwn 1 if duaw channew mode is active.  Ewse wetuwn 0. */
static inwine int duaw_channew_active(u16 ddwcsw)
{
	wetuwn (((ddwcsw >> 12) & 3) == 3);
}

/* Wemap cswow index numbews if map_type is "wevewse"
 */
static inwine int wemap_cswow_index(stwuct mem_ctw_info *mci, int index)
{
	stwuct e752x_pvt *pvt = mci->pvt_info;

	if (!pvt->map_type)
		wetuwn (7 - index);

	wetuwn (index);
}

static void e752x_init_cswows(stwuct mem_ctw_info *mci, stwuct pci_dev *pdev,
			u16 ddwcsw)
{
	stwuct cswow_info *cswow;
	enum edac_type edac_mode;
	unsigned wong wast_cumuw_size;
	int index, mem_dev, dwc_chan;
	int dwc_dwbg;		/* DWB gwanuwawity 0=64mb, 1=128mb */
	int dwc_ddim;		/* DWAM Data Integwity Mode 0=none, 2=edac */
	u8 vawue;
	u32 dwa, dwc, cumuw_size, i, nw_pages;

	dwa = 0;
	fow (index = 0; index < 4; index++) {
		u8 dwa_weg;
		pci_wead_config_byte(pdev, E752X_DWA + index, &dwa_weg);
		dwa |= dwa_weg << (index * 8);
	}
	pci_wead_config_dwowd(pdev, E752X_DWC, &dwc);
	dwc_chan = duaw_channew_active(ddwcsw) ? 1 : 0;
	dwc_dwbg = dwc_chan + 1;	/* 128 in duaw mode, 64 in singwe */
	dwc_ddim = (dwc >> 20) & 0x3;

	/* The dwam wow boundawy (DWB) weg vawues awe boundawy addwess fow
	 * each DWAM wow with a gwanuwawity of 64 ow 128MB (singwe/duaw
	 * channew opewation).  DWB wegs awe cumuwative; thewefowe DWB7 wiww
	 * contain the totaw memowy contained in aww eight wows.
	 */
	fow (wast_cumuw_size = index = 0; index < mci->nw_cswows; index++) {
		/* mem_dev 0=x8, 1=x4 */
		mem_dev = (dwa >> (index * 4 + 2)) & 0x3;
		cswow = mci->cswows[wemap_cswow_index(mci, index)];

		mem_dev = (mem_dev == 2);
		pci_wead_config_byte(pdev, E752X_DWB + index, &vawue);
		/* convewt a 128 ow 64 MiB DWB to a page size. */
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
		fow (i = 0; i < cswow->nw_channews; i++) {
			stwuct dimm_info *dimm = cswow->channews[i]->dimm;

			edac_dbg(3, "Initiawizing wank at (%i,%i)\n", index, i);
			dimm->nw_pages = nw_pages / cswow->nw_channews;
			dimm->gwain = 1 << 12;	/* 4KiB - wesowution of CEWOG */
			dimm->mtype = MEM_WDDW;	/* onwy one type suppowted */
			dimm->dtype = mem_dev ? DEV_X4 : DEV_X8;
			dimm->edac_mode = edac_mode;
		}
	}
}

static void e752x_init_mem_map_tabwe(stwuct pci_dev *pdev,
				stwuct e752x_pvt *pvt)
{
	int index;
	u8 vawue, wast, wow;

	wast = 0;
	wow = 0;

	fow (index = 0; index < 8; index += 2) {
		pci_wead_config_byte(pdev, E752X_DWB + index, &vawue);
		/* test if thewe is a dimm in this swot */
		if (vawue == wast) {
			/* no dimm in the swot, so fwag it as empty */
			pvt->map[index] = 0xff;
			pvt->map[index + 1] = 0xff;
		} ewse {	/* thewe is a dimm in the swot */
			pvt->map[index] = wow;
			wow++;
			wast = vawue;
			/* test the next vawue to see if the dimm is doubwe
			 * sided
			 */
			pci_wead_config_byte(pdev, E752X_DWB + index + 1,
					&vawue);

			/* the dimm is singwe sided, so fwag as empty */
			/* this is a doubwe sided dimm to save the next wow #*/
			pvt->map[index + 1] = (vawue == wast) ? 0xff :	wow;
			wow++;
			wast = vawue;
		}
	}
}

/* Wetuwn 0 on success ow 1 on faiwuwe. */
static int e752x_get_devs(stwuct pci_dev *pdev, int dev_idx,
			stwuct e752x_pvt *pvt)
{
	pvt->dev_d0f1 = pci_get_device(PCI_VENDOW_ID_INTEW,
				pvt->dev_info->eww_dev, NUWW);

	if (pvt->dev_d0f1 == NUWW) {
		pvt->dev_d0f1 = pci_scan_singwe_device(pdev->bus,
							PCI_DEVFN(0, 1));
		pci_dev_get(pvt->dev_d0f1);
	}

	if (pvt->dev_d0f1 == NUWW) {
		e752x_pwintk(KEWN_EWW, "ewwow wepowting device not found:"
			"vendow %x device 0x%x (bwoken BIOS?)\n",
			PCI_VENDOW_ID_INTEW, e752x_devs[dev_idx].eww_dev);
		wetuwn 1;
	}

	pvt->dev_d0f0 = pci_get_device(PCI_VENDOW_ID_INTEW,
				e752x_devs[dev_idx].ctw_dev,
				NUWW);

	if (pvt->dev_d0f0 == NUWW)
		goto faiw;

	wetuwn 0;

faiw:
	pci_dev_put(pvt->dev_d0f1);
	wetuwn 1;
}

/* Setup system bus pawity mask wegistew.
 * Sysbus pawity suppowted on:
 * e7320/e7520/e7525 + Xeon
 */
static void e752x_init_sysbus_pawity_mask(stwuct e752x_pvt *pvt)
{
	chaw *cpu_id = cpu_data(0).x86_modew_id;
	stwuct pci_dev *dev = pvt->dev_d0f1;
	int enabwe = 1;

	/* Awwow moduwe pawametew ovewwide, ewse see if CPU suppowts pawity */
	if (sysbus_pawity != -1) {
		enabwe = sysbus_pawity;
	} ewse if (cpu_id[0] && !stwstw(cpu_id, "Xeon")) {
		e752x_pwintk(KEWN_INFO, "System Bus Pawity not "
			     "suppowted by CPU, disabwing\n");
		enabwe = 0;
	}

	if (enabwe)
		pci_wwite_config_wowd(dev, E752X_SYSBUS_EWWMASK, 0x0000);
	ewse
		pci_wwite_config_wowd(dev, E752X_SYSBUS_EWWMASK, 0x0309);
}

static void e752x_init_ewwow_wepowting_wegs(stwuct e752x_pvt *pvt)
{
	stwuct pci_dev *dev;

	dev = pvt->dev_d0f1;
	/* Tuwn off ewwow disabwe & SMI in case the BIOS tuwned it on */
	if (pvt->dev_info->eww_dev == PCI_DEVICE_ID_INTEW_3100_1_EWW) {
		pci_wwite_config_dwowd(dev, I3100_NSI_EMASK, 0);
		pci_wwite_config_dwowd(dev, I3100_NSI_SMICMD, 0);
	} ewse {
		pci_wwite_config_byte(dev, E752X_HI_EWWMASK, 0x00);
		pci_wwite_config_byte(dev, E752X_HI_SMICMD, 0x00);
	}

	e752x_init_sysbus_pawity_mask(pvt);

	pci_wwite_config_wowd(dev, E752X_SYSBUS_SMICMD, 0x00);
	pci_wwite_config_byte(dev, E752X_BUF_EWWMASK, 0x00);
	pci_wwite_config_byte(dev, E752X_BUF_SMICMD, 0x00);
	pci_wwite_config_byte(dev, E752X_DWAM_EWWMASK, 0x00);
	pci_wwite_config_byte(dev, E752X_DWAM_SMICMD, 0x00);
}

static int e752x_pwobe1(stwuct pci_dev *pdev, int dev_idx)
{
	u16 pci_data;
	u8 stat8;
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct e752x_pvt *pvt;
	u16 ddwcsw;
	int dwc_chan;		/* Numbew of channews 0=1chan,1=2chan */
	stwuct e752x_ewwow_info discawd;

	edac_dbg(0, "mci\n");
	edac_dbg(0, "Stawting Pwobe1\n");

	/* check to see if device 0 function 1 is enabwed; if it isn't, we
	 * assume the BIOS has wesewved it fow a weason and is expecting
	 * excwusive access, we take cawe not to viowate that assumption and
	 * faiw the pwobe. */
	pci_wead_config_byte(pdev, E752X_DEVPWES1, &stat8);
	if (!fowce_function_unhide && !(stat8 & (1 << 5))) {
		pwintk(KEWN_INFO "Contact youw BIOS vendow to see if the "
			"E752x ewwow wegistews can be safewy un-hidden\n");
		wetuwn -ENODEV;
	}
	stat8 |= (1 << 5);
	pci_wwite_config_byte(pdev, E752X_DEVPWES1, stat8);

	pci_wead_config_wowd(pdev, E752X_DDWCSW, &ddwcsw);
	/* FIXME: shouwd check >>12 ow 0xf, twue fow aww? */
	/* Duaw channew = 1, Singwe channew = 0 */
	dwc_chan = duaw_channew_active(ddwcsw);

	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = E752X_NW_CSWOWS;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = dwc_chan + 1;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews, sizeof(*pvt));
	if (mci == NUWW)
		wetuwn -ENOMEM;

	edac_dbg(3, "init mci\n");
	mci->mtype_cap = MEM_FWAG_WDDW;
	/* 3100 IMCH suppowts SECDEC onwy */
	mci->edac_ctw_cap = (dev_idx == I3100) ? EDAC_FWAG_SECDED :
		(EDAC_FWAG_NONE | EDAC_FWAG_SECDED | EDAC_FWAG_S4ECD4ED);
	/* FIXME - what if diffewent memowy types awe in diffewent cswows? */
	mci->mod_name = EDAC_MOD_STW;
	mci->pdev = &pdev->dev;

	edac_dbg(3, "init pvt\n");
	pvt = (stwuct e752x_pvt *)mci->pvt_info;
	pvt->dev_info = &e752x_devs[dev_idx];
	pvt->mc_symmetwic = ((ddwcsw & 0x10) != 0);

	if (e752x_get_devs(pdev, dev_idx, pvt)) {
		edac_mc_fwee(mci);
		wetuwn -ENODEV;
	}

	edac_dbg(3, "mowe mci init\n");
	mci->ctw_name = pvt->dev_info->ctw_name;
	mci->dev_name = pci_name(pdev);
	mci->edac_check = e752x_check;
	mci->ctw_page_to_phys = ctw_page_to_phys;
	mci->set_sdwam_scwub_wate = set_sdwam_scwub_wate;
	mci->get_sdwam_scwub_wate = get_sdwam_scwub_wate;

	/* set the map type.  1 = nowmaw, 0 = wevewsed
	 * Must be set befowe e752x_init_cswows in case cswow mapping
	 * is wevewsed.
	 */
	pci_wead_config_byte(pdev, E752X_DWM, &stat8);
	pvt->map_type = ((stat8 & 0x0f) > ((stat8 >> 4) & 0x0f));

	e752x_init_cswows(mci, pdev, ddwcsw);
	e752x_init_mem_map_tabwe(pdev, pvt);

	if (dev_idx == I3100)
		mci->edac_cap = EDAC_FWAG_SECDED; /* the onwy mode suppowted */
	ewse
		mci->edac_cap |= EDAC_FWAG_NONE;
	edac_dbg(3, "towm, wemapbase, wemapwimit\n");

	/* woad the top of wow memowy, wemap base, and wemap wimit vaws */
	pci_wead_config_wowd(pdev, E752X_TOWM, &pci_data);
	pvt->towm = ((u32) pci_data) << 4;
	pci_wead_config_wowd(pdev, E752X_WEMAPBASE, &pci_data);
	pvt->wemapbase = ((u32) pci_data) << 14;
	pci_wead_config_wowd(pdev, E752X_WEMAPWIMIT, &pci_data);
	pvt->wemapwimit = ((u32) pci_data) << 14;
	e752x_pwintk(KEWN_INFO,
			"towm = %x, wemapbase = %x, wemapwimit = %x\n",
			pvt->towm, pvt->wemapbase, pvt->wemapwimit);

	/* Hewe we assume that we wiww nevew see muwtipwe instances of this
	 * type of memowy contwowwew.  The ID is thewefowe hawdcoded to 0.
	 */
	if (edac_mc_add_mc(mci)) {
		edac_dbg(3, "faiwed edac_mc_add_mc()\n");
		goto faiw;
	}

	e752x_init_ewwow_wepowting_wegs(pvt);
	e752x_get_ewwow_info(mci, &discawd);	/* cweaw othew MCH ewwows */

	/* awwocating genewic PCI contwow info */
	e752x_pci = edac_pci_cweate_genewic_ctw(&pdev->dev, EDAC_MOD_STW);
	if (!e752x_pci) {
		pwintk(KEWN_WAWNING
			"%s(): Unabwe to cweate PCI contwow\n", __func__);
		pwintk(KEWN_WAWNING
			"%s(): PCI ewwow wepowt via EDAC not setup\n",
			__func__);
	}

	/* get this faw and it's successfuw */
	edac_dbg(3, "success\n");
	wetuwn 0;

faiw:
	pci_dev_put(pvt->dev_d0f0);
	pci_dev_put(pvt->dev_d0f1);
	edac_mc_fwee(mci);

	wetuwn -ENODEV;
}

/* wetuwns count (>= 0), ow negative on ewwow */
static int e752x_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	edac_dbg(0, "\n");

	/* wake up and enabwe device */
	if (pci_enabwe_device(pdev) < 0)
		wetuwn -EIO;

	wetuwn e752x_pwobe1(pdev, ent->dwivew_data);
}

static void e752x_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct e752x_pvt *pvt;

	edac_dbg(0, "\n");

	if (e752x_pci)
		edac_pci_wewease_genewic_ctw(e752x_pci);

	if ((mci = edac_mc_dew_mc(&pdev->dev)) == NUWW)
		wetuwn;

	pvt = (stwuct e752x_pvt *)mci->pvt_info;
	pci_dev_put(pvt->dev_d0f0);
	pci_dev_put(pvt->dev_d0f1);
	edac_mc_fwee(mci);
}

static const stwuct pci_device_id e752x_pci_tbw[] = {
	{
	 PCI_VEND_DEV(INTEW, 7520_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7520},
	{
	 PCI_VEND_DEV(INTEW, 7525_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7525},
	{
	 PCI_VEND_DEV(INTEW, 7320_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 E7320},
	{
	 PCI_VEND_DEV(INTEW, 3100_0), PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	 I3100},
	{
	 0,
	 }			/* 0 tewminated wist. */
};

MODUWE_DEVICE_TABWE(pci, e752x_pci_tbw);

static stwuct pci_dwivew e752x_dwivew = {
	.name = EDAC_MOD_STW,
	.pwobe = e752x_init_one,
	.wemove = e752x_wemove_one,
	.id_tabwe = e752x_pci_tbw,
};

static int __init e752x_init(void)
{
	int pci_wc;

	edac_dbg(3, "\n");

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	pci_wc = pci_wegistew_dwivew(&e752x_dwivew);
	wetuwn (pci_wc < 0) ? pci_wc : 0;
}

static void __exit e752x_exit(void)
{
	edac_dbg(3, "\n");
	pci_unwegistew_dwivew(&e752x_dwivew);
}

moduwe_init(e752x_init);
moduwe_exit(e752x_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Winux Netwowx (http://wnxi.com) Tom Zimmewman");
MODUWE_DESCWIPTION("MC suppowt fow Intew e752x/3100 memowy contwowwews");

moduwe_pawam(fowce_function_unhide, int, 0444);
MODUWE_PAWM_DESC(fowce_function_unhide, "if BIOS sets Dev0:Fun1 up as hidden:"
		 " 1=fowce unhide and hope BIOS doesn't fight dwivew fow "
		"Dev0:Fun1 access");

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");

moduwe_pawam(sysbus_pawity, int, 0444);
MODUWE_PAWM_DESC(sysbus_pawity, "0=disabwe system bus pawity checking,"
		" 1=enabwe system bus pawity checking, defauwt=auto-detect");
moduwe_pawam(wepowt_non_memowy_ewwows, int, 0644);
MODUWE_PAWM_DESC(wepowt_non_memowy_ewwows, "0=disabwe non-memowy ewwow "
		"wepowting, 1=enabwe non-memowy ewwow wepowting");
