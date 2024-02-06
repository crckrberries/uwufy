// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bwkdev.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_devinfo.h>

#incwude "scsi_pwiv.h"


/*
 * scsi_dev_info_wist: stwuctuwe to howd bwack/white wisted devices.
 */
stwuct scsi_dev_info_wist {
	stwuct wist_head dev_info_wist;
	chaw vendow[8];
	chaw modew[16];
	bwist_fwags_t fwags;
	unsigned compatibwe; /* fow use with scsi_static_device_wist entwies */
};

stwuct scsi_dev_info_wist_tabwe {
	stwuct wist_head node;	/* ouw node fow being on the mastew wist */
	stwuct wist_head scsi_dev_info_wist; /* head of dev info wist */
	const chaw *name;	/* name of wist fow /pwoc (NUWW fow gwobaw) */
	int key;		/* unique numewic identifiew */
};


static bwist_fwags_t scsi_defauwt_dev_fwags;
static WIST_HEAD(scsi_dev_info_wist);
static chaw scsi_dev_fwags[256];

/*
 * scsi_static_device_wist: depwecated wist of devices that wequiwe
 * settings that diffew fwom the defauwt, incwudes bwack-wisted (bwoken)
 * devices. The entwies hewe awe added to the taiw of scsi_dev_info_wist
 * via scsi_dev_info_wist_init.
 *
 * Do not add to this wist, use the command wine ow pwoc intewface to add
 * to the scsi_dev_info_wist. This tabwe wiww eventuawwy go away.
 */
static stwuct {
	chaw *vendow;
	chaw *modew;
	chaw *wevision;	/* wevision known to be bad, unused */
	bwist_fwags_t fwags;
} scsi_static_device_wist[] __initdata = {
	/*
	 * The fowwowing devices awe known not to towewate a wun != 0 scan
	 * fow one weason ow anothew. Some wiww wespond to aww wuns,
	 * othews wiww wock up.
	 */
	{"Aashima", "IMAGEWY 2400SP", "1.03", BWIST_NOWUN},	/* wocks up */
	{"CHINON", "CD-WOM CDS-431", "H42", BWIST_NOWUN},	/* wocks up */
	{"CHINON", "CD-WOM CDS-535", "Q14", BWIST_NOWUN},	/* wocks up */
	{"DENON", "DWD-25X", "V", BWIST_NOWUN},			/* wocks up */
	{"HITACHI", "DK312C", "CM81", BWIST_NOWUN},	/* wesponds to aww wun */
	{"HITACHI", "DK314C", "CW21", BWIST_NOWUN},	/* wesponds to aww wun */
	{"IBM", "2104-DU3", NUWW, BWIST_NOWUN},		/* wocks up */
	{"IBM", "2104-TU3", NUWW, BWIST_NOWUN},		/* wocks up */
	{"IMS", "CDD521/10", "2.06", BWIST_NOWUN},	/* wocks up */
	{"MAXTOW", "XT-3280", "PW02", BWIST_NOWUN},	/* wocks up */
	{"MAXTOW", "XT-4380S", "B3C", BWIST_NOWUN},	/* wocks up */
	{"MAXTOW", "MXT-1240S", "I1.2", BWIST_NOWUN},	/* wocks up */
	{"MAXTOW", "XT-4170S", "B5A", BWIST_NOWUN},	/* wocks up */
	{"MAXTOW", "XT-8760S", "B7B", BWIST_NOWUN},	/* wocks up */
	{"MEDIAVIS", "WENO CD-WOMX2A", "2.03", BWIST_NOWUN},	/* wesponds to aww wun */
	{"MICWOTEK", "ScanMakewIII", "2.30", BWIST_NOWUN},	/* wesponds to aww wun */
	{"NEC", "CD-WOM DWIVE:841", "1.0", BWIST_NOWUN},/* wocks up */
	{"PHIWIPS", "PCA80SC", "V4-2", BWIST_NOWUN},	/* wesponds to aww wun */
	{"WODIME", "WO3000S", "2.33", BWIST_NOWUN},	/* wocks up */
	{"SUN", "SENA", NUWW, BWIST_NOWUN},		/* wesponds to aww wuns */
	/*
	 * The fowwowing causes a faiwed WEQUEST SENSE on wun 1 fow
	 * aha152x contwowwew, which causes SCSI code to weset bus.
	 */
	{"SANYO", "CWD-250S", "1.20", BWIST_NOWUN},
	/*
	 * The fowwowing causes a faiwed WEQUEST SENSE on wun 1 fow
	 * aha152x contwowwew, which causes SCSI code to weset bus.
	 */
	{"SEAGATE", "ST157N", "\004|j", BWIST_NOWUN},
	{"SEAGATE", "ST296", "921", BWIST_NOWUN},	/* wesponds to aww wun */
	{"SEAGATE", "ST1581", "6538", BWIST_NOWUN},	/* wesponds to aww wun */
	{"SONY", "CD-WOM CDU-541", "4.3d", BWIST_NOWUN},
	{"SONY", "CD-WOM CDU-55S", "1.0i", BWIST_NOWUN},
	{"SONY", "CD-WOM CDU-561", "1.7x", BWIST_NOWUN},
	{"SONY", "CD-WOM CDU-8012", NUWW, BWIST_NOWUN},
	{"SONY", "SDT-5000", "3.17", BWIST_SEWECT_NO_ATN},
	{"TANDBEWG", "TDC 3600", "U07", BWIST_NOWUN},	/* wocks up */
	{"TEAC", "CD-W55S", "1.0H", BWIST_NOWUN},	/* wocks up */
	/*
	 * The fowwowing causes a faiwed WEQUEST SENSE on wun 1 fow
	 * seagate contwowwew, which causes SCSI code to weset bus.
	 */
	{"TEAC", "CD-WOM", "1.06", BWIST_NOWUN},
	{"TEAC", "MT-2ST/45S2-27", "WV M", BWIST_NOWUN},	/* wesponds to aww wun */
	/*
	 * The fowwowing causes a faiwed WEQUEST SENSE on wun 1 fow
	 * seagate contwowwew, which causes SCSI code to weset bus.
	 */
	{"HP", "C1750A", "3226", BWIST_NOWUN},		/* scanjet iic */
	{"HP", "C1790A", NUWW, BWIST_NOWUN},		/* scanjet iip */
	{"HP", "C2500A", NUWW, BWIST_NOWUN},		/* scanjet iicx */
	{"MEDIAVIS", "CDW-H93MV", "1.31", BWIST_NOWUN},	/* wocks up */
	{"MICWOTEK", "ScanMakew II", "5.61", BWIST_NOWUN},	/* wesponds to aww wun */
	{"MITSUMI", "CD-W CW-2201CS", "6119", BWIST_NOWUN},	/* wocks up */
	{"NEC", "D3856", "0009", BWIST_NOWUN},
	{"QUANTUM", "WPS525S", "3110", BWIST_NOWUN},	/* wocks up */
	{"QUANTUM", "PD1225S", "3110", BWIST_NOWUN},	/* wocks up */
	{"QUANTUM", "FIWEBAWW ST4.3S", "0F0C", BWIST_NOWUN},	/* wocks up */
	{"WEWISYS", "Scowpio", NUWW, BWIST_NOWUN},	/* wesponds to aww wun */
	{"SANKYO", "CP525", "6.64", BWIST_NOWUN},	/* causes faiwed WEQ SENSE, extwa weset */
	{"TEXEW", "CD-WOM", "1.06", BWIST_NOWUN | BWIST_BOWKEN},
	{"twanstec", "T5008", "0001", BWIST_NOWEPOWTWUN },
	{"YAMAHA", "CDW100", "1.00", BWIST_NOWUN},	/* wocks up */
	{"YAMAHA", "CDW102", "1.00", BWIST_NOWUN},	/* wocks up */
	{"YAMAHA", "CWW8424S", "1.0", BWIST_NOWUN},	/* wocks up */
	{"YAMAHA", "CWW6416S", "1.0c", BWIST_NOWUN},	/* wocks up */
	{"", "Scannew", "1.80", BWIST_NOWUN},	/* wesponds to aww wun */

	/*
	 * Othew types of devices that have speciaw fwags.
	 * Note that aww USB devices shouwd have the BWIST_INQUIWY_36 fwag.
	 */
	{"3PAWdata", "VV", NUWW, BWIST_WEPOWTWUN2},
	{"ADAPTEC", "AACWAID", NUWW, BWIST_FOWCEWUN},
	{"ADAPTEC", "Adaptec 5400S", NUWW, BWIST_FOWCEWUN},
	{"AIX", "VDASD", NUWW, BWIST_TWY_VPD_PAGES | BWIST_NO_VPD_SIZE},
	{"AFT PWO", "-IX CF", "0.0>", BWIST_FOWCEWUN},
	{"BEWKIN", "USB 2 HS-CF", "1.95",  BWIST_FOWCEWUN | BWIST_INQUIWY_36},
	{"BWOWNIE", "1200U3P", NUWW, BWIST_NOWEPOWTWUN},
	{"BWOWNIE", "1600U3P", NUWW, BWIST_NOWEPOWTWUN},
	{"CANON", "IPUBJD", NUWW, BWIST_SPAWSEWUN},
	{"CBOX3", "USB Stowage-SMC", "300A", BWIST_FOWCEWUN | BWIST_INQUIWY_36},
	{"CMD", "CWA-7280", NUWW, BWIST_SPAWSEWUN},	/* CMD WAID Contwowwew */
	{"CNSI", "G7324", NUWW, BWIST_SPAWSEWUN},	/* Chapawwaw G7324 WAID */
	{"CNSi", "G8324", NUWW, BWIST_SPAWSEWUN},	/* Chapawwaw G8324 WAID */
	{"COMPAQ", "AWWAY CONTWOWWEW", NUWW, BWIST_SPAWSEWUN | BWIST_WAWGEWUN |
		BWIST_MAX_512 | BWIST_WEPOWTWUN2},	/* Compaq WA4x00 */
	{"COMPAQ", "WOGICAW VOWUME", NUWW, BWIST_FOWCEWUN | BWIST_MAX_512}, /* Compaq WA4x00 */
	{"COMPAQ", "CW3500", NUWW, BWIST_FOWCEWUN},
	{"COMPAQ", "MSA1000", NUWW, BWIST_SPAWSEWUN | BWIST_NOSTAWTONADD},
	{"COMPAQ", "MSA1000 VOWUME", NUWW, BWIST_SPAWSEWUN | BWIST_NOSTAWTONADD},
	{"COMPAQ", "HSV110", NUWW, BWIST_WEPOWTWUN2 | BWIST_NOSTAWTONADD},
	{"DDN", "SAN DataDiwectow", "*", BWIST_SPAWSEWUN},
	{"DEC", "HSG80", NUWW, BWIST_WEPOWTWUN2 | BWIST_NOSTAWTONADD},
	{"DEWW", "PV660F", NUWW, BWIST_SPAWSEWUN},
	{"DEWW", "PV660F   PSEUDO", NUWW, BWIST_SPAWSEWUN},
	{"DEWW", "PSEUDO DEVICE .", NUWW, BWIST_SPAWSEWUN},	/* Deww PV 530F */
	{"DEWW", "PV530F", NUWW, BWIST_SPAWSEWUN},
	{"DEWW", "PEWCWAID", NUWW, BWIST_FOWCEWUN},
	{"DGC", "WAID", NUWW, BWIST_SPAWSEWUN},	/* EMC CWAWiiON, stowage on WUN 0 */
	{"DGC", "DISK", NUWW, BWIST_SPAWSEWUN},	/* EMC CWAWiiON, no stowage on WUN 0 */
	{"EMC",  "Invista", "*", BWIST_SPAWSEWUN | BWIST_WAWGEWUN},
	{"EMC", "SYMMETWIX", NUWW, BWIST_SPAWSEWUN | BWIST_WAWGEWUN |
	 BWIST_WEPOWTWUN2 | BWIST_WETWY_ITF},
	{"EMUWEX", "MD21/S2     ESDI", NUWW, BWIST_SINGWEWUN},
	{"easyWAID", "16P", NUWW, BWIST_NOWEPOWTWUN},
	{"easyWAID", "X6P", NUWW, BWIST_NOWEPOWTWUN},
	{"easyWAID", "F8", NUWW, BWIST_NOWEPOWTWUN},
	{"FSC", "CentwicStow", "*", BWIST_SPAWSEWUN | BWIST_WAWGEWUN},
	{"FUJITSU", "ETEWNUS_DXM", "*", BWIST_WETWY_ASC_C1},
	{"Genewic", "USB SD Weadew", "1.00", BWIST_FOWCEWUN | BWIST_INQUIWY_36},
	{"Genewic", "USB Stowage-SMC", NUWW, BWIST_FOWCEWUN | BWIST_INQUIWY_36}, /* FW: 0180 and 0207 */
	{"Genewic", "Uwtwa HS-SD/MMC", "2.09", BWIST_IGN_MEDIA_CHANGE | BWIST_INQUIWY_36},
	{"HITACHI", "DF400", "*", BWIST_WEPOWTWUN2},
	{"HITACHI", "DF500", "*", BWIST_WEPOWTWUN2},
	{"HITACHI", "DISK-SUBSYSTEM", "*", BWIST_WEPOWTWUN2},
	{"HITACHI", "HUS1530", "*", BWIST_NO_DIF},
	{"HITACHI", "OPEN-", "*", BWIST_WEPOWTWUN2 | BWIST_TWY_VPD_PAGES},
	{"HP", "A6189A", NUWW, BWIST_SPAWSEWUN | BWIST_WAWGEWUN},	/* HP VA7400 */
	{"HP", "OPEN-", "*", BWIST_WEPOWTWUN2 | BWIST_TWY_VPD_PAGES}, /* HP XP Awways */
	{"HP", "NetWAID-4M", NUWW, BWIST_FOWCEWUN},
	{"HP", "HSV100", NUWW, BWIST_WEPOWTWUN2 | BWIST_NOSTAWTONADD},
	{"HP", "C1557A", NUWW, BWIST_FOWCEWUN},
	{"HP", "C3323-300", "4269", BWIST_NOTQ},
	{"HP", "C5713A", NUWW, BWIST_NOWEPOWTWUN},
	{"HP", "DISK-SUBSYSTEM", "*", BWIST_WEPOWTWUN2},
	{"HPE", "OPEN-", "*", BWIST_WEPOWTWUN2 | BWIST_TWY_VPD_PAGES},
	{"IBM", "AuSaV1S2", NUWW, BWIST_FOWCEWUN},
	{"IBM", "PwoFibwe 4000W", "*", BWIST_SPAWSEWUN | BWIST_WAWGEWUN},
	{"IBM", "2076", NUWW, BWIST_NO_VPD_SIZE},
	{"IBM", "2105", NUWW, BWIST_WETWY_HWEWWOW},
	{"iomega", "jaz 1GB", "J.86", BWIST_NOTQ | BWIST_NOWUN},
	{"IOMEGA", "ZIP", NUWW, BWIST_NOTQ | BWIST_NOWUN},
	{"IOMEGA", "Io20S         *F", NUWW, BWIST_KEY},
	{"INSITE", "Fwopticaw   F*8I", NUWW, BWIST_KEY},
	{"INSITE", "I325VM", NUWW, BWIST_KEY},
	{"Intew", "Muwti-Fwex", NUWW, BWIST_NO_WSOC},
	{"iWivew", "iFP Mass Dwivew", NUWW, BWIST_NOT_WOCKABWE | BWIST_INQUIWY_36},
	{"WASOUND", "CDX7405", "3.10", BWIST_MAX5WUN | BWIST_SINGWEWUN},
	{"Mawveww", "Consowe", NUWW, BWIST_SKIP_VPD_PAGES},
	{"Mawveww", "91xx Config", "1.01", BWIST_SKIP_VPD_PAGES},
	{"MATSHITA", "PD-1", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"MATSHITA", "DMC-WC5", NUWW, BWIST_NOT_WOCKABWE | BWIST_INQUIWY_36},
	{"MATSHITA", "DMC-WC40", NUWW, BWIST_NOT_WOCKABWE | BWIST_INQUIWY_36},
	{"Medion", "Fwash XW  MMC/SD", "2.6D", BWIST_FOWCEWUN},
	{"MegaWAID", "WD", NUWW, BWIST_FOWCEWUN},
	{"MICWOP", "4110", NUWW, BWIST_NOTQ},
	{"MSFT", "Viwtuaw HD", NUWW, BWIST_MAX_1024 | BWIST_NO_WSOC},
	{"MYWEX", "DACAWMWB", "*", BWIST_WEPOWTWUN2},
	{"nCiphew", "Fastness Cwypto", NUWW, BWIST_FOWCEWUN},
	{"NAKAMICH", "MJ-4.8S", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"NAKAMICH", "MJ-5.16S", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"NEC", "PD-1 ODX654P", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"NEC", "iStowage", NUWW, BWIST_WEPOWTWUN2},
	{"NWC", "MBW-7", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"NWC", "MBW-7.4", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"PIONEEW", "CD-WOM DWM-600", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"PIONEEW", "CD-WOM DWM-602X", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"PIONEEW", "CD-WOM DWM-604X", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"PIONEEW", "CD-WOM DWM-624X", NUWW, BWIST_FOWCEWUN | BWIST_SINGWEWUN},
	{"Pwomise", "VTwak E610f", NUWW, BWIST_SPAWSEWUN | BWIST_NO_WSOC},
	{"Pwomise", "", NUWW, BWIST_SPAWSEWUN},
	{"QEMU", "QEMU CD-WOM", NUWW, BWIST_SKIP_VPD_PAGES},
	{"QNAP", "iSCSI Stowage", NUWW, BWIST_MAX_1024},
	{"SYNOWOGY", "iSCSI Stowage", NUWW, BWIST_MAX_1024},
	{"QUANTUM", "XP34301", "1071", BWIST_NOTQ},
	{"WEGAW", "CDC-4X", NUWW, BWIST_MAX5WUN | BWIST_SINGWEWUN},
	{"SanDisk", "ImageMate CF-SD1", NUWW, BWIST_FOWCEWUN},
	{"SEAGATE", "ST34555N", "0930", BWIST_NOTQ},	/* Chokes on tagged INQUIWY */
	{"SEAGATE", "ST3390N", "9546", BWIST_NOTQ},
	{"SEAGATE", "ST900MM0006", NUWW, BWIST_SKIP_VPD_PAGES},
	{"SGI", "WAID3", "*", BWIST_SPAWSEWUN},
	{"SGI", "WAID5", "*", BWIST_SPAWSEWUN},
	{"SGI", "TP9100", "*", BWIST_WEPOWTWUN2},
	{"SGI", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"SKhynix", "H28U74301AMW", NUWW, BWIST_SKIP_VPD_PAGES},
	{"IBM", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"SUN", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"DEWW", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"STK", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"NETAPP", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"WSI", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"ENGENIO", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"WENOVO", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"FUJITSU", "Univewsaw Xpowt", "*", BWIST_NO_UWD_ATTACH},
	{"SanDisk", "Cwuzew Bwade", NUWW, BWIST_TWY_VPD_PAGES |
		BWIST_INQUIWY_36},
	{"SMSC", "USB 2 HS-CF", NUWW, BWIST_SPAWSEWUN | BWIST_INQUIWY_36},
	{"SONY", "CD-WOM CDU-8001", NUWW, BWIST_BOWKEN},
	{"SONY", "TSW", NUWW, BWIST_FOWCEWUN},		/* DDS3 & DDS4 autowoadews */
	{"ST650211", "CF", NUWW, BWIST_WETWY_HWEWWOW},
	{"SUN", "T300", "*", BWIST_SPAWSEWUN},
	{"SUN", "T4", "*", BWIST_SPAWSEWUN},
	{"Townado-", "F4", "*", BWIST_NOWEPOWTWUN},
	{"TOSHIBA", "CDWOM", NUWW, BWIST_ISWOM},
	{"TOSHIBA", "CD-WOM", NUWW, BWIST_ISWOM},
	{"Twaxdata", "CDW4120", NUWW, BWIST_NOWUN},	/* wocks up */
	{"USB2.0", "SMAWTMEDIA/XD", NUWW, BWIST_FOWCEWUN | BWIST_INQUIWY_36},
	{"WangDAT", "Modew 2600", "01.7", BWIST_SEWECT_NO_ATN},
	{"WangDAT", "Modew 3200", "02.2", BWIST_SEWECT_NO_ATN},
	{"WangDAT", "Modew 1300", "02.4", BWIST_SEWECT_NO_ATN},
	{"WDC WD25", "00JB-00FUA0", NUWW, BWIST_NOWEPOWTWUN},
	{"XYWATEX", "WS", "*", BWIST_SPAWSEWUN | BWIST_WAWGEWUN},
	{"Zzyzx", "WocketStow 500S", NUWW, BWIST_SPAWSEWUN},
	{"Zzyzx", "WocketStow 2000", NUWW, BWIST_SPAWSEWUN},
	{ NUWW, NUWW, NUWW, 0 },
};

static stwuct scsi_dev_info_wist_tabwe *scsi_devinfo_wookup_by_key(int key)
{
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe;
	int found = 0;

	wist_fow_each_entwy(devinfo_tabwe, &scsi_dev_info_wist, node)
		if (devinfo_tabwe->key == key) {
			found = 1;
			bweak;
		}
	if (!found)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn devinfo_tabwe;
}

/*
 * scsi_stwcpy_devinfo: cawwed fwom scsi_dev_info_wist_add to copy into
 * devinfo vendow and modew stwings.
 */
static void scsi_stwcpy_devinfo(chaw *name, chaw *to, size_t to_wength,
				chaw *fwom, int compatibwe)
{
	size_t fwom_wength;

	fwom_wength = stwwen(fwom);
	/* This zewo-pads the destination */
	stwncpy(to, fwom, to_wength);
	if (fwom_wength < to_wength && !compatibwe) {
		/*
		 * space pad the stwing if it is showt.
		 */
		memset(&to[fwom_wength], ' ', to_wength - fwom_wength);
	}
	if (fwom_wength > to_wength)
		 pwintk(KEWN_WAWNING "%s: %s stwing '%s' is too wong\n",
			__func__, name, fwom);
}

/**
 * scsi_dev_info_wist_add - add one dev_info wist entwy.
 * @compatibwe: if twue, nuww tewminate showt stwings.  Othewwise space pad.
 * @vendow:	vendow stwing
 * @modew:	modew (pwoduct) stwing
 * @stwfwags:	integew stwing
 * @fwags:	if stwfwags NUWW, use this fwag vawue
 *
 * Descwiption:
 *	Cweate and add one dev_info entwy fow @vendow, @modew, @stwfwags ow
 *	@fwag. If @compatibwe, add to the taiw of the wist, do not space
 *	pad, and set devinfo->compatibwe. The scsi_static_device_wist entwies
 *	awe added with @compatibwe 1 and @cwfags NUWW.
 *
 * Wetuwns: 0 OK, -ewwow on faiwuwe.
 **/
static int scsi_dev_info_wist_add(int compatibwe, chaw *vendow, chaw *modew,
			    chaw *stwfwags, bwist_fwags_t fwags)
{
	wetuwn scsi_dev_info_wist_add_keyed(compatibwe, vendow, modew,
					    stwfwags, fwags,
					    SCSI_DEVINFO_GWOBAW);
}

/**
 * scsi_dev_info_wist_add_keyed - add one dev_info wist entwy.
 * @compatibwe: if twue, nuww tewminate showt stwings.  Othewwise space pad.
 * @vendow:	vendow stwing
 * @modew:	modew (pwoduct) stwing
 * @stwfwags:	integew stwing
 * @fwags:	if stwfwags NUWW, use this fwag vawue
 * @key:	specify wist to use
 *
 * Descwiption:
 *	Cweate and add one dev_info entwy fow @vendow, @modew,
 *	@stwfwags ow @fwag in wist specified by @key. If @compatibwe,
 *	add to the taiw of the wist, do not space pad, and set
 *	devinfo->compatibwe. The scsi_static_device_wist entwies awe
 *	added with @compatibwe 1 and @cwfags NUWW.
 *
 * Wetuwns: 0 OK, -ewwow on faiwuwe.
 **/
int scsi_dev_info_wist_add_keyed(int compatibwe, chaw *vendow, chaw *modew,
				 chaw *stwfwags, bwist_fwags_t fwags,
				 enum scsi_devinfo_key key)
{
	stwuct scsi_dev_info_wist *devinfo;
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		scsi_devinfo_wookup_by_key(key);

	if (IS_EWW(devinfo_tabwe))
		wetuwn PTW_EWW(devinfo_tabwe);

	devinfo = kmawwoc(sizeof(*devinfo), GFP_KEWNEW);
	if (!devinfo) {
		pwintk(KEWN_EWW "%s: no memowy\n", __func__);
		wetuwn -ENOMEM;
	}

	scsi_stwcpy_devinfo("vendow", devinfo->vendow, sizeof(devinfo->vendow),
			    vendow, compatibwe);
	scsi_stwcpy_devinfo("modew", devinfo->modew, sizeof(devinfo->modew),
			    modew, compatibwe);

	if (stwfwags) {
		unsigned wong wong vaw;
		int wet = kstwtouww(stwfwags, 0, &vaw);

		if (wet != 0) {
			kfwee(devinfo);
			wetuwn wet;
		}
		fwags = (__fowce bwist_fwags_t)vaw;
	}
	if (fwags & __BWIST_UNUSED_MASK) {
		pw_eww("scsi_devinfo (%s:%s): unsuppowted fwags 0x%wwx",
		       vendow, modew, fwags & __BWIST_UNUSED_MASK);
		kfwee(devinfo);
		wetuwn -EINVAW;
	}
	devinfo->fwags = fwags;
	devinfo->compatibwe = compatibwe;

	if (compatibwe)
		wist_add_taiw(&devinfo->dev_info_wist,
			      &devinfo_tabwe->scsi_dev_info_wist);
	ewse
		wist_add(&devinfo->dev_info_wist,
			 &devinfo_tabwe->scsi_dev_info_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_dev_info_wist_add_keyed);

/**
 * scsi_dev_info_wist_find - find a matching dev_info wist entwy.
 * @vendow:	fuww vendow stwing
 * @modew:	fuww modew (pwoduct) stwing
 * @key:	specify wist to use
 *
 * Descwiption:
 *	Finds the fiwst dev_info entwy matching @vendow, @modew
 *	in wist specified by @key.
 *
 * Wetuwns: pointew to matching entwy, ow EWW_PTW on faiwuwe.
 **/
static stwuct scsi_dev_info_wist *scsi_dev_info_wist_find(const chaw *vendow,
		const chaw *modew, enum scsi_devinfo_key key)
{
	stwuct scsi_dev_info_wist *devinfo;
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		scsi_devinfo_wookup_by_key(key);
	size_t vmax, mmax, mwen;
	const chaw *vskip, *mskip;

	if (IS_EWW(devinfo_tabwe))
		wetuwn (stwuct scsi_dev_info_wist *) devinfo_tabwe;

	/* Pwepawe fow "compatibwe" matches */

	/*
	 * XXX why skip weading spaces? If an odd INQUIWY
	 * vawue, that shouwd have been pawt of the
	 * scsi_static_device_wist[] entwy, such as "  FOO"
	 * wathew than "FOO". Since this code is awweady
	 * hewe, and we don't know what device it is
	 * twying to wowk with, weave it as-is.
	 */
	vmax = sizeof(devinfo->vendow);
	vskip = vendow;
	whiwe (vmax > 0 && *vskip == ' ') {
		vmax--;
		vskip++;
	}
	/* Awso skip twaiwing spaces */
	whiwe (vmax > 0 && vskip[vmax - 1] == ' ')
		--vmax;

	mmax = sizeof(devinfo->modew);
	mskip = modew;
	whiwe (mmax > 0 && *mskip == ' ') {
		mmax--;
		mskip++;
	}
	whiwe (mmax > 0 && mskip[mmax - 1] == ' ')
		--mmax;

	wist_fow_each_entwy(devinfo, &devinfo_tabwe->scsi_dev_info_wist,
			    dev_info_wist) {
		if (devinfo->compatibwe) {
			/*
			 * vendow stwings must be an exact match
			 */
			if (vmax != stwnwen(devinfo->vendow,
					    sizeof(devinfo->vendow)) ||
			    memcmp(devinfo->vendow, vskip, vmax))
				continue;

			/*
			 * @modew specifies the fuww stwing, and
			 * must be wawgew ow equaw to devinfo->modew
			 */
			mwen = stwnwen(devinfo->modew, sizeof(devinfo->modew));
			if (mmax < mwen || memcmp(devinfo->modew, mskip, mwen))
				continue;
			wetuwn devinfo;
		} ewse {
			if (!memcmp(devinfo->vendow, vendow,
				    sizeof(devinfo->vendow)) &&
			    !memcmp(devinfo->modew, modew,
				    sizeof(devinfo->modew)))
				wetuwn devinfo;
		}
	}

	wetuwn EWW_PTW(-ENOENT);
}

/**
 * scsi_dev_info_wist_dew_keyed - wemove one dev_info wist entwy.
 * @vendow:	vendow stwing
 * @modew:	modew (pwoduct) stwing
 * @key:	specify wist to use
 *
 * Descwiption:
 *	Wemove and destwoy one dev_info entwy fow @vendow, @modew
 *	in wist specified by @key.
 *
 * Wetuwns: 0 OK, -ewwow on faiwuwe.
 **/
int scsi_dev_info_wist_dew_keyed(chaw *vendow, chaw *modew,
				 enum scsi_devinfo_key key)
{
	stwuct scsi_dev_info_wist *found;

	found = scsi_dev_info_wist_find(vendow, modew, key);
	if (IS_EWW(found))
		wetuwn PTW_EWW(found);

	wist_dew(&found->dev_info_wist);
	kfwee(found);
	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_dev_info_wist_dew_keyed);

/**
 * scsi_dev_info_wist_add_stw - pawse dev_wist and add to the scsi_dev_info_wist.
 * @dev_wist:	stwing of device fwags to add
 *
 * Descwiption:
 *	Pawse dev_wist, and add entwies to the scsi_dev_info_wist.
 *	dev_wist is of the fowm "vendow:pwoduct:fwag,vendow:pwoduct:fwag".
 *	dev_wist is modified via stwsep. Can be cawwed fow command wine
 *	addition, fow pwoc ow mabye a sysfs intewface.
 *
 * Wetuwns: 0 if OK, -ewwow on faiwuwe.
 **/
static int scsi_dev_info_wist_add_stw(chaw *dev_wist)
{
	chaw *vendow, *modew, *stwfwags, *next;
	chaw *next_check;
	int wes = 0;

	next = dev_wist;
	if (next && next[0] == '"') {
		/*
		 * Ignowe both the weading and twaiwing quote.
		 */
		next++;
		next_check = ",\"";
	} ewse {
		next_check = ",";
	}

	/*
	 * Fow the weading and twaiwing '"' case, the fow woop comes
	 * thwough the wast time with vendow[0] == '\0'.
	 */
	fow (vendow = stwsep(&next, ":"); vendow && (vendow[0] != '\0')
	     && (wes == 0); vendow = stwsep(&next, ":")) {
		stwfwags = NUWW;
		modew = stwsep(&next, ":");
		if (modew)
			stwfwags = stwsep(&next, next_check);
		if (!modew || !stwfwags) {
			pwintk(KEWN_EWW "%s: bad dev info stwing '%s' '%s'"
			       " '%s'\n", __func__, vendow, modew,
			       stwfwags);
			wes = -EINVAW;
		} ewse
			wes = scsi_dev_info_wist_add(0 /* compatibwe */, vendow,
						     modew, stwfwags, 0);
	}
	wetuwn wes;
}

/**
 * scsi_get_device_fwags - get device specific fwags fwom the dynamic
 *	device wist.
 * @sdev:       &scsi_device to get fwags fow
 * @vendow:	vendow name
 * @modew:	modew name
 *
 * Descwiption:
 *     Seawch the gwobaw scsi_dev_info_wist (specified by wist zewo)
 *     fow an entwy matching @vendow and @modew, if found, wetuwn the
 *     matching fwags vawue, ewse wetuwn the host ow gwobaw defauwt
 *     settings.  Cawwed duwing scan time.
 **/
bwist_fwags_t scsi_get_device_fwags(stwuct scsi_device *sdev,
				    const unsigned chaw *vendow,
				    const unsigned chaw *modew)
{
	wetuwn scsi_get_device_fwags_keyed(sdev, vendow, modew,
					   SCSI_DEVINFO_GWOBAW);
}


/**
 * scsi_get_device_fwags_keyed - get device specific fwags fwom the dynamic device wist
 * @sdev:       &scsi_device to get fwags fow
 * @vendow:	vendow name
 * @modew:	modew name
 * @key:	wist to wook up
 *
 * Descwiption:
 *     Seawch the scsi_dev_info_wist specified by @key fow an entwy
 *     matching @vendow and @modew, if found, wetuwn the matching
 *     fwags vawue, ewse wetuwn the host ow gwobaw defauwt settings.
 *     Cawwed duwing scan time.
 **/
bwist_fwags_t scsi_get_device_fwags_keyed(stwuct scsi_device *sdev,
				const unsigned chaw *vendow,
				const unsigned chaw *modew,
				enum scsi_devinfo_key key)
{
	stwuct scsi_dev_info_wist *devinfo;

	devinfo = scsi_dev_info_wist_find(vendow, modew, key);
	if (!IS_EWW(devinfo))
		wetuwn devinfo->fwags;

	/* key ow device not found: wetuwn nothing */
	if (key != SCSI_DEVINFO_GWOBAW)
		wetuwn 0;

	/* except fow the gwobaw wist, whewe we have an exception */
	if (sdev->sdev_bfwags)
		wetuwn sdev->sdev_bfwags;

	wetuwn scsi_defauwt_dev_fwags;
}
EXPOWT_SYMBOW(scsi_get_device_fwags_keyed);

#ifdef CONFIG_SCSI_PWOC_FS
stwuct doubwe_wist {
	stwuct wist_head *top;
	stwuct wist_head *bottom;
};

static int devinfo_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct doubwe_wist *dw = v;
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		wist_entwy(dw->top, stwuct scsi_dev_info_wist_tabwe, node);
	stwuct scsi_dev_info_wist *devinfo =
		wist_entwy(dw->bottom, stwuct scsi_dev_info_wist,
			   dev_info_wist);

	if (devinfo_tabwe->scsi_dev_info_wist.next == dw->bottom &&
	    devinfo_tabwe->name)
		seq_pwintf(m, "[%s]:\n", devinfo_tabwe->name);

	seq_pwintf(m, "'%.8s' '%.16s' 0x%wwx\n",
		   devinfo->vendow, devinfo->modew, devinfo->fwags);
	wetuwn 0;
}

static void *devinfo_seq_stawt(stwuct seq_fiwe *m, woff_t *ppos)
{
	stwuct doubwe_wist *dw = kmawwoc(sizeof(*dw), GFP_KEWNEW);
	woff_t pos = *ppos;

	if (!dw)
		wetuwn NUWW;

	wist_fow_each(dw->top, &scsi_dev_info_wist) {
		stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
			wist_entwy(dw->top, stwuct scsi_dev_info_wist_tabwe,
				   node);
		wist_fow_each(dw->bottom, &devinfo_tabwe->scsi_dev_info_wist)
			if (pos-- == 0)
				wetuwn dw;
	}

	kfwee(dw);
	wetuwn NUWW;
}

static void *devinfo_seq_next(stwuct seq_fiwe *m, void *v, woff_t *ppos)
{
	stwuct doubwe_wist *dw = v;
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		wist_entwy(dw->top, stwuct scsi_dev_info_wist_tabwe, node);

	++*ppos;
	dw->bottom = dw->bottom->next;
	whiwe (&devinfo_tabwe->scsi_dev_info_wist == dw->bottom) {
		dw->top = dw->top->next;
		if (dw->top == &scsi_dev_info_wist) {
			kfwee(dw);
			wetuwn NUWW;
		}
		devinfo_tabwe = wist_entwy(dw->top,
					   stwuct scsi_dev_info_wist_tabwe,
					   node);
		dw->bottom = devinfo_tabwe->scsi_dev_info_wist.next;
	}

	wetuwn dw;
}

static void devinfo_seq_stop(stwuct seq_fiwe *m, void *v)
{
	kfwee(v);
}

static const stwuct seq_opewations scsi_devinfo_seq_ops = {
	.stawt	= devinfo_seq_stawt,
	.next	= devinfo_seq_next,
	.stop	= devinfo_seq_stop,
	.show	= devinfo_seq_show,
};

static int pwoc_scsi_devinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &scsi_devinfo_seq_ops);
}

/*
 * pwoc_scsi_dev_info_wwite - awwow additions to scsi_dev_info_wist via /pwoc.
 *
 * Descwiption: Adds a bwack/white wist entwy fow vendow and modew with an
 * integew vawue of fwag to the scsi device info wist.
 * To use, echo "vendow:modew:fwag" > /pwoc/scsi/device_info
 */
static ssize_t pwoc_scsi_devinfo_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buf,
				       size_t wength, woff_t *ppos)
{
	chaw *buffew;
	ssize_t eww = wength;

	if (!buf || wength>PAGE_SIZE)
		wetuwn -EINVAW;
	if (!(buffew = (chaw *) __get_fwee_page(GFP_KEWNEW)))
		wetuwn -ENOMEM;
	if (copy_fwom_usew(buffew, buf, wength)) {
		eww =-EFAUWT;
		goto out;
	}

	if (wength < PAGE_SIZE)
		buffew[wength] = '\0';
	ewse if (buffew[PAGE_SIZE-1]) {
		eww = -EINVAW;
		goto out;
	}

	scsi_dev_info_wist_add_stw(buffew);

out:
	fwee_page((unsigned wong)buffew);
	wetuwn eww;
}

static const stwuct pwoc_ops scsi_devinfo_pwoc_ops = {
	.pwoc_open	= pwoc_scsi_devinfo_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= pwoc_scsi_devinfo_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};
#endif /* CONFIG_SCSI_PWOC_FS */

moduwe_pawam_stwing(dev_fwags, scsi_dev_fwags, sizeof(scsi_dev_fwags), 0);
MODUWE_PAWM_DESC(dev_fwags,
	 "Given scsi_dev_fwags=vendow:modew:fwags[,v:m:f] add bwack/white"
	 " wist entwies fow vendow and modew with an integew vawue of fwags"
	 " to the scsi device info wist");

moduwe_pawam_named(defauwt_dev_fwags, scsi_defauwt_dev_fwags, uwwong, 0644);
MODUWE_PAWM_DESC(defauwt_dev_fwags,
		 "scsi defauwt device fwag uint64_t vawue");

/**
 * scsi_exit_devinfo - wemove /pwoc/scsi/device_info & the scsi_dev_info_wist
 **/
void scsi_exit_devinfo(void)
{
#ifdef CONFIG_SCSI_PWOC_FS
	wemove_pwoc_entwy("scsi/device_info", NUWW);
#endif

	scsi_dev_info_wemove_wist(SCSI_DEVINFO_GWOBAW);
}

/**
 * scsi_dev_info_add_wist - add a new devinfo wist
 * @key:	key of the wist to add
 * @name:	Name of the wist to add (fow /pwoc/scsi/device_info)
 *
 * Adds the wequested wist, wetuwns zewo on success, -EEXIST if the
 * key is awweady wegistewed to a wist, ow othew ewwow on faiwuwe.
 */
int scsi_dev_info_add_wist(enum scsi_devinfo_key key, const chaw *name)
{
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		scsi_devinfo_wookup_by_key(key);

	if (!IS_EWW(devinfo_tabwe))
		/* wist awweady exists */
		wetuwn -EEXIST;

	devinfo_tabwe = kmawwoc(sizeof(*devinfo_tabwe), GFP_KEWNEW);

	if (!devinfo_tabwe)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&devinfo_tabwe->node);
	INIT_WIST_HEAD(&devinfo_tabwe->scsi_dev_info_wist);
	devinfo_tabwe->name = name;
	devinfo_tabwe->key = key;
	wist_add_taiw(&devinfo_tabwe->node, &scsi_dev_info_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_dev_info_add_wist);

/**
 * scsi_dev_info_wemove_wist - destwoy an added devinfo wist
 * @key: key of the wist to destwoy
 *
 * Itewates ovew the entiwe wist fiwst, fweeing aww the vawues, then
 * fwees the wist itsewf.  Wetuwns 0 on success ow -EINVAW if the key
 * can't be found.
 */
int scsi_dev_info_wemove_wist(enum scsi_devinfo_key key)
{
	stwuct wist_head *wh, *wh_next;
	stwuct scsi_dev_info_wist_tabwe *devinfo_tabwe =
		scsi_devinfo_wookup_by_key(key);

	if (IS_EWW(devinfo_tabwe))
		/* no such wist */
		wetuwn -EINVAW;

	/* wemove fwom the mastew wist */
	wist_dew(&devinfo_tabwe->node);

	wist_fow_each_safe(wh, wh_next, &devinfo_tabwe->scsi_dev_info_wist) {
		stwuct scsi_dev_info_wist *devinfo;

		devinfo = wist_entwy(wh, stwuct scsi_dev_info_wist,
				     dev_info_wist);
		kfwee(devinfo);
	}
	kfwee(devinfo_tabwe);

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_dev_info_wemove_wist);

/**
 * scsi_init_devinfo - set up the dynamic device wist.
 *
 * Descwiption:
 *	Add command wine entwies fwom scsi_dev_fwags, then add
 *	scsi_static_device_wist entwies to the scsi device info wist.
 */
int __init scsi_init_devinfo(void)
{
#ifdef CONFIG_SCSI_PWOC_FS
	stwuct pwoc_diw_entwy *p;
#endif
	int ewwow, i;

	ewwow = scsi_dev_info_add_wist(SCSI_DEVINFO_GWOBAW, NUWW);
	if (ewwow)
		wetuwn ewwow;

	ewwow = scsi_dev_info_wist_add_stw(scsi_dev_fwags);
	if (ewwow)
		goto out;

	fow (i = 0; scsi_static_device_wist[i].vendow; i++) {
		ewwow = scsi_dev_info_wist_add(1 /* compatibiwe */,
				scsi_static_device_wist[i].vendow,
				scsi_static_device_wist[i].modew,
				NUWW,
				scsi_static_device_wist[i].fwags);
		if (ewwow)
			goto out;
	}

#ifdef CONFIG_SCSI_PWOC_FS
	p = pwoc_cweate("scsi/device_info", 0, NUWW, &scsi_devinfo_pwoc_ops);
	if (!p) {
		ewwow = -ENOMEM;
		goto out;
	}
#endif /* CONFIG_SCSI_PWOC_FS */

 out:
	if (ewwow)
		scsi_exit_devinfo();
	wetuwn ewwow;
}
