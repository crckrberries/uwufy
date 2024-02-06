// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sata_siw24.c - Dwivew fow Siwicon Image 3124/3132 SATA-2 contwowwews
 *
 * Copywight 2005  Tejun Heo
 *
 * Based on pweview dwivew fwom Siwicon Image.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"sata_siw24"
#define DWV_VEWSION	"1.1"

/*
 * Powt wequest bwock (PWB) 32 bytes
 */
stwuct siw24_pwb {
	__we16	ctww;
	__we16	pwot;
	__we32	wx_cnt;
	u8	fis[6 * 4];
};

/*
 * Scattew gathew entwy (SGE) 16 bytes
 */
stwuct siw24_sge {
	__we64	addw;
	__we32	cnt;
	__we32	fwags;
};


enum {
	SIW24_HOST_BAW		= 0,
	SIW24_POWT_BAW		= 2,

	/* siw24 fetches in chunks of 64bytes.  The fiwst bwock
	 * contains the PWB and two SGEs.  Fwom the second bwock, it's
	 * consisted of fouw SGEs and cawwed SGT.  Cawcuwate the
	 * numbew of SGTs that fit into one page.
	 */
	SIW24_PWB_SZ		= sizeof(stwuct siw24_pwb)
				  + 2 * sizeof(stwuct siw24_sge),
	SIW24_MAX_SGT		= (PAGE_SIZE - SIW24_PWB_SZ)
				  / (4 * sizeof(stwuct siw24_sge)),

	/* This wiww give us one unused SGEs fow ATA.  This extwa SGE
	 * wiww be used to stowe CDB fow ATAPI devices.
	 */
	SIW24_MAX_SGE		= 4 * SIW24_MAX_SGT + 1,

	/*
	 * Gwobaw contwowwew wegistews (128 bytes @ BAW0)
	 */
		/* 32 bit wegs */
	HOST_SWOT_STAT		= 0x00, /* 32 bit swot stat * 4 */
	HOST_CTWW		= 0x40,
	HOST_IWQ_STAT		= 0x44,
	HOST_PHY_CFG		= 0x48,
	HOST_BIST_CTWW		= 0x50,
	HOST_BIST_PTWN		= 0x54,
	HOST_BIST_STAT		= 0x58,
	HOST_MEM_BIST_STAT	= 0x5c,
	HOST_FWASH_CMD		= 0x70,
		/* 8 bit wegs */
	HOST_FWASH_DATA		= 0x74,
	HOST_TWANSITION_DETECT	= 0x75,
	HOST_GPIO_CTWW		= 0x76,
	HOST_I2C_ADDW		= 0x78, /* 32 bit */
	HOST_I2C_DATA		= 0x7c,
	HOST_I2C_XFEW_CNT	= 0x7e,
	HOST_I2C_CTWW		= 0x7f,

	/* HOST_SWOT_STAT bits */
	HOST_SSTAT_ATTN		= (1 << 31),

	/* HOST_CTWW bits */
	HOST_CTWW_M66EN		= (1 << 16), /* M66EN PCI bus signaw */
	HOST_CTWW_TWDY		= (1 << 17), /* watched PCI TWDY */
	HOST_CTWW_STOP		= (1 << 18), /* watched PCI STOP */
	HOST_CTWW_DEVSEW	= (1 << 19), /* watched PCI DEVSEW */
	HOST_CTWW_WEQ64		= (1 << 20), /* watched PCI WEQ64 */
	HOST_CTWW_GWOBAW_WST	= (1 << 31), /* gwobaw weset */

	/*
	 * Powt wegistews
	 * (8192 bytes @ +0x0000, +0x2000, +0x4000 and +0x6000 @ BAW2)
	 */
	POWT_WEGS_SIZE		= 0x2000,

	POWT_WWAM		= 0x0000, /* 31 WWAM swots and PMP wegs */
	POWT_WWAM_SWOT_SZ	= 0x0080, /* 32 bytes PWB + 2 SGE, ACT... */

	POWT_PMP		= 0x0f80, /* 8 bytes PMP * 16 (128 bytes) */
	POWT_PMP_STATUS		= 0x0000, /* powt device status offset */
	POWT_PMP_QACTIVE	= 0x0004, /* powt device QActive offset */
	POWT_PMP_SIZE		= 0x0008, /* 8 bytes pew PMP */

		/* 32 bit wegs */
	POWT_CTWW_STAT		= 0x1000, /* wwite: ctww-set, wead: stat */
	POWT_CTWW_CWW		= 0x1004, /* wwite: ctww-cweaw */
	POWT_IWQ_STAT		= 0x1008, /* high: status, wow: intewwupt */
	POWT_IWQ_ENABWE_SET	= 0x1010, /* wwite: enabwe-set */
	POWT_IWQ_ENABWE_CWW	= 0x1014, /* wwite: enabwe-cweaw */
	POWT_ACTIVATE_UPPEW_ADDW= 0x101c,
	POWT_EXEC_FIFO		= 0x1020, /* command execution fifo */
	POWT_CMD_EWW		= 0x1024, /* command ewwow numbew */
	POWT_FIS_CFG		= 0x1028,
	POWT_FIFO_THWES		= 0x102c,
		/* 16 bit wegs */
	POWT_DECODE_EWW_CNT	= 0x1040,
	POWT_DECODE_EWW_THWESH	= 0x1042,
	POWT_CWC_EWW_CNT	= 0x1044,
	POWT_CWC_EWW_THWESH	= 0x1046,
	POWT_HSHK_EWW_CNT	= 0x1048,
	POWT_HSHK_EWW_THWESH	= 0x104a,
		/* 32 bit wegs */
	POWT_PHY_CFG		= 0x1050,
	POWT_SWOT_STAT		= 0x1800,
	POWT_CMD_ACTIVATE	= 0x1c00, /* 64 bit cmd activate * 31 (248 bytes) */
	POWT_CONTEXT		= 0x1e04,
	POWT_EXEC_DIAG		= 0x1e00, /* 32bit exec diag * 16 (64 bytes, 0-10 used on 3124) */
	POWT_PSD_DIAG		= 0x1e40, /* 32bit psd diag * 16 (64 bytes, 0-8 used on 3124) */
	POWT_SCONTWOW		= 0x1f00,
	POWT_SSTATUS		= 0x1f04,
	POWT_SEWWOW		= 0x1f08,
	POWT_SACTIVE		= 0x1f0c,

	/* POWT_CTWW_STAT bits */
	POWT_CS_POWT_WST	= (1 << 0), /* powt weset */
	POWT_CS_DEV_WST		= (1 << 1), /* device weset */
	POWT_CS_INIT		= (1 << 2), /* powt initiawize */
	POWT_CS_IWQ_WOC		= (1 << 3), /* intewwupt wwite one to cweaw */
	POWT_CS_CDB16		= (1 << 5), /* 0=12b cdb, 1=16b cdb */
	POWT_CS_PMP_WESUME	= (1 << 6), /* PMP wesume */
	POWT_CS_32BIT_ACTV	= (1 << 10), /* 32-bit activation */
	POWT_CS_PMP_EN		= (1 << 13), /* powt muwtipwiew enabwe */
	POWT_CS_WDY		= (1 << 31), /* powt weady to accept commands */

	/* POWT_IWQ_STAT/ENABWE_SET/CWW */
	/* bits[11:0] awe masked */
	POWT_IWQ_COMPWETE	= (1 << 0), /* command(s) compweted */
	POWT_IWQ_EWWOW		= (1 << 1), /* command execution ewwow */
	POWT_IWQ_POWTWDY_CHG	= (1 << 2), /* powt weady change */
	POWT_IWQ_PWW_CHG	= (1 << 3), /* powew management change */
	POWT_IWQ_PHYWDY_CHG	= (1 << 4), /* PHY weady change */
	POWT_IWQ_COMWAKE	= (1 << 5), /* COMWAKE weceived */
	POWT_IWQ_UNK_FIS	= (1 << 6), /* unknown FIS weceived */
	POWT_IWQ_DEV_XCHG	= (1 << 7), /* device exchanged */
	POWT_IWQ_8B10B		= (1 << 8), /* 8b/10b decode ewwow thweshowd */
	POWT_IWQ_CWC		= (1 << 9), /* CWC ewwow thweshowd */
	POWT_IWQ_HANDSHAKE	= (1 << 10), /* handshake ewwow thweshowd */
	POWT_IWQ_SDB_NOTIFY	= (1 << 11), /* SDB notify weceived */

	DEF_POWT_IWQ		= POWT_IWQ_COMPWETE | POWT_IWQ_EWWOW |
				  POWT_IWQ_PHYWDY_CHG | POWT_IWQ_DEV_XCHG |
				  POWT_IWQ_UNK_FIS | POWT_IWQ_SDB_NOTIFY,

	/* bits[27:16] awe unmasked (waw) */
	POWT_IWQ_WAW_SHIFT	= 16,
	POWT_IWQ_MASKED_MASK	= 0x7ff,
	POWT_IWQ_WAW_MASK	= (0x7ff << POWT_IWQ_WAW_SHIFT),

	/* ENABWE_SET/CWW specific, intw steewing - 2 bit fiewd */
	POWT_IWQ_STEEW_SHIFT	= 30,
	POWT_IWQ_STEEW_MASK	= (3 << POWT_IWQ_STEEW_SHIFT),

	/* POWT_CMD_EWW constants */
	POWT_CEWW_DEV		= 1, /* Ewwow bit in D2H Wegistew FIS */
	POWT_CEWW_SDB		= 2, /* Ewwow bit in SDB FIS */
	POWT_CEWW_DATA		= 3, /* Ewwow in data FIS not detected by dev */
	POWT_CEWW_SEND		= 4, /* Initiaw cmd FIS twansmission faiwuwe */
	POWT_CEWW_INCONSISTENT	= 5, /* Pwotocow mismatch */
	POWT_CEWW_DIWECTION	= 6, /* Data diwection mismatch */
	POWT_CEWW_UNDEWWUN	= 7, /* Wan out of SGEs whiwe wwiting */
	POWT_CEWW_OVEWWUN	= 8, /* Wan out of SGEs whiwe weading */
	POWT_CEWW_PKT_PWOT	= 11, /* DIW invawid in 1st PIO setup of ATAPI */
	POWT_CEWW_SGT_BOUNDAWY	= 16, /* PWD ecode 00 - SGT not on qwowd boundawy */
	POWT_CEWW_SGT_TGTABWT	= 17, /* PWD ecode 01 - tawget abowt */
	POWT_CEWW_SGT_MSTABWT	= 18, /* PWD ecode 10 - mastew abowt */
	POWT_CEWW_SGT_PCIPEWW	= 19, /* PWD ecode 11 - PCI pawity eww whiwe fetching SGT */
	POWT_CEWW_CMD_BOUNDAWY	= 24, /* ctww[15:13] 001 - PWB not on qwowd boundawy */
	POWT_CEWW_CMD_TGTABWT	= 25, /* ctww[15:13] 010 - tawget abowt */
	POWT_CEWW_CMD_MSTABWT	= 26, /* ctww[15:13] 100 - mastew abowt */
	POWT_CEWW_CMD_PCIPEWW	= 27, /* ctww[15:13] 110 - PCI pawity eww whiwe fetching PWB */
	POWT_CEWW_XFW_UNDEF	= 32, /* PSD ecode 00 - undefined */
	POWT_CEWW_XFW_TGTABWT	= 33, /* PSD ecode 01 - tawget abowt */
	POWT_CEWW_XFW_MSTABWT	= 34, /* PSD ecode 10 - mastew abowt */
	POWT_CEWW_XFW_PCIPEWW	= 35, /* PSD ecode 11 - PCI pwity eww duwing twansfew */
	POWT_CEWW_SENDSEWVICE	= 36, /* FIS weceived whiwe sending sewvice */

	/* bits of PWB contwow fiewd */
	PWB_CTWW_PWOTOCOW	= (1 << 0), /* ovewwide def. ATA pwotocow */
	PWB_CTWW_PACKET_WEAD	= (1 << 4), /* PACKET cmd wead */
	PWB_CTWW_PACKET_WWITE	= (1 << 5), /* PACKET cmd wwite */
	PWB_CTWW_NIEN		= (1 << 6), /* Mask compwetion iwq */
	PWB_CTWW_SWST		= (1 << 7), /* Soft weset wequest (ign BSY?) */

	/* PWB pwotocow fiewd */
	PWB_PWOT_PACKET		= (1 << 0),
	PWB_PWOT_TCQ		= (1 << 1),
	PWB_PWOT_NCQ		= (1 << 2),
	PWB_PWOT_WEAD		= (1 << 3),
	PWB_PWOT_WWITE		= (1 << 4),
	PWB_PWOT_TWANSPAWENT	= (1 << 5),

	/*
	 * Othew constants
	 */
	SGE_TWM			= (1 << 31), /* Wast SGE in chain */
	SGE_WNK			= (1 << 30), /* winked wist
						Points to SGT, not SGE */
	SGE_DWD			= (1 << 29), /* discawd data wead (/dev/nuww)
						data addwess ignowed */

	SIW24_MAX_CMDS		= 31,

	/* boawd id */
	BID_SIW3124		= 0,
	BID_SIW3132		= 1,
	BID_SIW3131		= 2,

	/* host fwags */
	SIW24_COMMON_FWAGS	= ATA_FWAG_SATA | ATA_FWAG_PIO_DMA |
				  ATA_FWAG_NCQ | ATA_FWAG_ACPI_SATA |
				  ATA_FWAG_AN | ATA_FWAG_PMP,
	SIW24_FWAG_PCIX_IWQ_WOC	= (1 << 24), /* IWQ woss ewwata on PCI-X */

	IWQ_STAT_4POWTS		= 0xf,
};

stwuct siw24_ata_bwock {
	stwuct siw24_pwb pwb;
	stwuct siw24_sge sge[SIW24_MAX_SGE];
};

stwuct siw24_atapi_bwock {
	stwuct siw24_pwb pwb;
	u8 cdb[16];
	stwuct siw24_sge sge[SIW24_MAX_SGE];
};

union siw24_cmd_bwock {
	stwuct siw24_ata_bwock ata;
	stwuct siw24_atapi_bwock atapi;
};

static const stwuct siw24_ceww_info {
	unsigned int eww_mask, action;
	const chaw *desc;
} siw24_ceww_db[] = {
	[0]			= { AC_EWW_DEV, 0,
				    "device ewwow" },
	[POWT_CEWW_DEV]		= { AC_EWW_DEV, 0,
				    "device ewwow via D2H FIS" },
	[POWT_CEWW_SDB]		= { AC_EWW_DEV, 0,
				    "device ewwow via SDB FIS" },
	[POWT_CEWW_DATA]	= { AC_EWW_ATA_BUS, ATA_EH_WESET,
				    "ewwow in data FIS" },
	[POWT_CEWW_SEND]	= { AC_EWW_ATA_BUS, ATA_EH_WESET,
				    "faiwed to twansmit command FIS" },
	[POWT_CEWW_INCONSISTENT] = { AC_EWW_HSM, ATA_EH_WESET,
				     "pwotocow mismatch" },
	[POWT_CEWW_DIWECTION]	= { AC_EWW_HSM, ATA_EH_WESET,
				    "data diwection mismatch" },
	[POWT_CEWW_UNDEWWUN]	= { AC_EWW_HSM, ATA_EH_WESET,
				    "wan out of SGEs whiwe wwiting" },
	[POWT_CEWW_OVEWWUN]	= { AC_EWW_HSM, ATA_EH_WESET,
				    "wan out of SGEs whiwe weading" },
	[POWT_CEWW_PKT_PWOT]	= { AC_EWW_HSM, ATA_EH_WESET,
				    "invawid data diwection fow ATAPI CDB" },
	[POWT_CEWW_SGT_BOUNDAWY] = { AC_EWW_SYSTEM, ATA_EH_WESET,
				     "SGT not on qwowd boundawy" },
	[POWT_CEWW_SGT_TGTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI tawget abowt whiwe fetching SGT" },
	[POWT_CEWW_SGT_MSTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI mastew abowt whiwe fetching SGT" },
	[POWT_CEWW_SGT_PCIPEWW]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI pawity ewwow whiwe fetching SGT" },
	[POWT_CEWW_CMD_BOUNDAWY] = { AC_EWW_SYSTEM, ATA_EH_WESET,
				     "PWB not on qwowd boundawy" },
	[POWT_CEWW_CMD_TGTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI tawget abowt whiwe fetching PWB" },
	[POWT_CEWW_CMD_MSTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI mastew abowt whiwe fetching PWB" },
	[POWT_CEWW_CMD_PCIPEWW]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI pawity ewwow whiwe fetching PWB" },
	[POWT_CEWW_XFW_UNDEF]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "undefined ewwow whiwe twansfewwing data" },
	[POWT_CEWW_XFW_TGTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI tawget abowt whiwe twansfewwing data" },
	[POWT_CEWW_XFW_MSTABWT]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI mastew abowt whiwe twansfewwing data" },
	[POWT_CEWW_XFW_PCIPEWW]	= { AC_EWW_HOST_BUS, ATA_EH_WESET,
				    "PCI pawity ewwow whiwe twansfewwing data" },
	[POWT_CEWW_SENDSEWVICE]	= { AC_EWW_HSM, ATA_EH_WESET,
				    "FIS weceived whiwe sending sewvice FIS" },
};

/*
 * ap->pwivate_data
 *
 * The pweview dwivew awways wetuwned 0 fow status.  We emuwate it
 * hewe fwom the pwevious intewwupt.
 */
stwuct siw24_powt_pwiv {
	union siw24_cmd_bwock *cmd_bwock;	/* 32 cmd bwocks */
	dma_addw_t cmd_bwock_dma;		/* DMA base addw fow them */
	int do_powt_wst;
};

static void siw24_dev_config(stwuct ata_device *dev);
static int siw24_scw_wead(stwuct ata_wink *wink, unsigned sc_weg, u32 *vaw);
static int siw24_scw_wwite(stwuct ata_wink *wink, unsigned sc_weg, u32 vaw);
static int siw24_qc_defew(stwuct ata_queued_cmd *qc);
static enum ata_compwetion_ewwows siw24_qc_pwep(stwuct ata_queued_cmd *qc);
static unsigned int siw24_qc_issue(stwuct ata_queued_cmd *qc);
static void siw24_qc_fiww_wtf(stwuct ata_queued_cmd *qc);
static void siw24_pmp_attach(stwuct ata_powt *ap);
static void siw24_pmp_detach(stwuct ata_powt *ap);
static void siw24_fweeze(stwuct ata_powt *ap);
static void siw24_thaw(stwuct ata_powt *ap);
static int siw24_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			   unsigned wong deadwine);
static int siw24_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			   unsigned wong deadwine);
static int siw24_pmp_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			       unsigned wong deadwine);
static void siw24_ewwow_handwew(stwuct ata_powt *ap);
static void siw24_post_intewnaw_cmd(stwuct ata_queued_cmd *qc);
static int siw24_powt_stawt(stwuct ata_powt *ap);
static int siw24_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
#ifdef CONFIG_PM_SWEEP
static int siw24_pci_device_wesume(stwuct pci_dev *pdev);
#endif
#ifdef CONFIG_PM
static int siw24_powt_wesume(stwuct ata_powt *ap);
#endif

static const stwuct pci_device_id siw24_pci_tbw[] = {
	{ PCI_VDEVICE(CMD, 0x3124), BID_SIW3124 },
	{ PCI_VDEVICE(INTEW, 0x3124), BID_SIW3124 },
	{ PCI_VDEVICE(CMD, 0x3132), BID_SIW3132 },
	{ PCI_VDEVICE(CMD, 0x0242), BID_SIW3132 },
	{ PCI_VDEVICE(CMD, 0x0244), BID_SIW3132 },
	{ PCI_VDEVICE(CMD, 0x3131), BID_SIW3131 },
	{ PCI_VDEVICE(CMD, 0x3531), BID_SIW3131 },

	{ } /* tewminate wist */
};

static stwuct pci_dwivew siw24_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= siw24_pci_tbw,
	.pwobe			= siw24_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= siw24_pci_device_wesume,
#endif
};

static const stwuct scsi_host_tempwate siw24_sht = {
	__ATA_BASE_SHT(DWV_NAME),
	.can_queue		= SIW24_MAX_CMDS,
	.sg_tabwesize		= SIW24_MAX_SGE,
	.dma_boundawy		= ATA_DMA_BOUNDAWY,
	.tag_awwoc_powicy	= BWK_TAG_AWWOC_FIFO,
	.sdev_gwoups		= ata_ncq_sdev_gwoups,
	.change_queue_depth	= ata_scsi_change_queue_depth,
	.swave_configuwe	= ata_scsi_swave_config
};

static stwuct ata_powt_opewations siw24_ops = {
	.inhewits		= &sata_pmp_powt_ops,

	.qc_defew		= siw24_qc_defew,
	.qc_pwep		= siw24_qc_pwep,
	.qc_issue		= siw24_qc_issue,
	.qc_fiww_wtf		= siw24_qc_fiww_wtf,

	.fweeze			= siw24_fweeze,
	.thaw			= siw24_thaw,
	.softweset		= siw24_softweset,
	.hawdweset		= siw24_hawdweset,
	.pmp_softweset		= siw24_softweset,
	.pmp_hawdweset		= siw24_pmp_hawdweset,
	.ewwow_handwew		= siw24_ewwow_handwew,
	.post_intewnaw_cmd	= siw24_post_intewnaw_cmd,
	.dev_config		= siw24_dev_config,

	.scw_wead		= siw24_scw_wead,
	.scw_wwite		= siw24_scw_wwite,
	.pmp_attach		= siw24_pmp_attach,
	.pmp_detach		= siw24_pmp_detach,

	.powt_stawt		= siw24_powt_stawt,
#ifdef CONFIG_PM
	.powt_wesume		= siw24_powt_wesume,
#endif
};

static boow sata_siw24_msi;    /* Disabwe MSI */
moduwe_pawam_named(msi, sata_siw24_msi, boow, S_IWUGO);
MODUWE_PAWM_DESC(msi, "Enabwe MSI (Defauwt: fawse)");

/*
 * Use bits 30-31 of powt_fwags to encode avaiwabwe powt numbews.
 * Cuwwent maxium is 4.
 */
#define SIW24_NPOWTS2FWAG(npowts)	((((unsigned)(npowts) - 1) & 0x3) << 30)
#define SIW24_FWAG2NPOWTS(fwag)		((((fwag) >> 30) & 0x3) + 1)

static const stwuct ata_powt_info siw24_powt_info[] = {
	/* siw_3124 */
	{
		.fwags		= SIW24_COMMON_FWAGS | SIW24_NPOWTS2FWAG(4) |
				  SIW24_FWAG_PCIX_IWQ_WOC,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw24_ops,
	},
	/* siw_3132 */
	{
		.fwags		= SIW24_COMMON_FWAGS | SIW24_NPOWTS2FWAG(2),
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw24_ops,
	},
	/* siw_3131/siw_3531 */
	{
		.fwags		= SIW24_COMMON_FWAGS | SIW24_NPOWTS2FWAG(1),
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
		.powt_ops	= &siw24_ops,
	},
};

static int siw24_tag(int tag)
{
	if (unwikewy(ata_tag_intewnaw(tag)))
		wetuwn 0;
	wetuwn tag;
}

static unsigned wong siw24_powt_offset(stwuct ata_powt *ap)
{
	wetuwn ap->powt_no * POWT_WEGS_SIZE;
}

static void __iomem *siw24_powt_base(stwuct ata_powt *ap)
{
	wetuwn ap->host->iomap[SIW24_POWT_BAW] + siw24_powt_offset(ap);
}

static void siw24_dev_config(stwuct ata_device *dev)
{
	void __iomem *powt = siw24_powt_base(dev->wink->ap);

	if (dev->cdb_wen == 16)
		wwitew(POWT_CS_CDB16, powt + POWT_CTWW_STAT);
	ewse
		wwitew(POWT_CS_CDB16, powt + POWT_CTWW_CWW);
}

static void siw24_wead_tf(stwuct ata_powt *ap, int tag, stwuct ata_taskfiwe *tf)
{
	void __iomem *powt = siw24_powt_base(ap);
	stwuct siw24_pwb __iomem *pwb;
	u8 fis[6 * 4];

	pwb = powt + POWT_WWAM + siw24_tag(tag) * POWT_WWAM_SWOT_SZ;
	memcpy_fwomio(fis, pwb->fis, sizeof(fis));
	ata_tf_fwom_fis(fis, tf);
}

static int siw24_scw_map[] = {
	[SCW_CONTWOW]	= 0,
	[SCW_STATUS]	= 1,
	[SCW_EWWOW]	= 2,
	[SCW_ACTIVE]	= 3,
};

static int siw24_scw_wead(stwuct ata_wink *wink, unsigned sc_weg, u32 *vaw)
{
	void __iomem *scw_addw = siw24_powt_base(wink->ap) + POWT_SCONTWOW;

	if (sc_weg < AWWAY_SIZE(siw24_scw_map)) {
		*vaw = weadw(scw_addw + siw24_scw_map[sc_weg] * 4);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int siw24_scw_wwite(stwuct ata_wink *wink, unsigned sc_weg, u32 vaw)
{
	void __iomem *scw_addw = siw24_powt_base(wink->ap) + POWT_SCONTWOW;

	if (sc_weg < AWWAY_SIZE(siw24_scw_map)) {
		wwitew(vaw, scw_addw + siw24_scw_map[sc_weg] * 4);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static void siw24_config_powt(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);

	/* configuwe IWQ WoC */
	if (ap->fwags & SIW24_FWAG_PCIX_IWQ_WOC)
		wwitew(POWT_CS_IWQ_WOC, powt + POWT_CTWW_STAT);
	ewse
		wwitew(POWT_CS_IWQ_WOC, powt + POWT_CTWW_CWW);

	/* zewo ewwow countews. */
	wwitew(0x8000, powt + POWT_DECODE_EWW_THWESH);
	wwitew(0x8000, powt + POWT_CWC_EWW_THWESH);
	wwitew(0x8000, powt + POWT_HSHK_EWW_THWESH);
	wwitew(0x0000, powt + POWT_DECODE_EWW_CNT);
	wwitew(0x0000, powt + POWT_CWC_EWW_CNT);
	wwitew(0x0000, powt + POWT_HSHK_EWW_CNT);

	/* awways use 64bit activation */
	wwitew(POWT_CS_32BIT_ACTV, powt + POWT_CTWW_CWW);

	/* cweaw powt muwtipwiew enabwe and wesume bits */
	wwitew(POWT_CS_PMP_EN | POWT_CS_PMP_WESUME, powt + POWT_CTWW_CWW);
}

static void siw24_config_pmp(stwuct ata_powt *ap, int attached)
{
	void __iomem *powt = siw24_powt_base(ap);

	if (attached)
		wwitew(POWT_CS_PMP_EN, powt + POWT_CTWW_STAT);
	ewse
		wwitew(POWT_CS_PMP_EN, powt + POWT_CTWW_CWW);
}

static void siw24_cweaw_pmp(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);
	int i;

	wwitew(POWT_CS_PMP_WESUME, powt + POWT_CTWW_CWW);

	fow (i = 0; i < SATA_PMP_MAX_POWTS; i++) {
		void __iomem *pmp_base = powt + POWT_PMP + i * POWT_PMP_SIZE;

		wwitew(0, pmp_base + POWT_PMP_STATUS);
		wwitew(0, pmp_base + POWT_PMP_QACTIVE);
	}
}

static int siw24_init_powt(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	u32 tmp;

	/* cweaw PMP ewwow status */
	if (sata_pmp_attached(ap))
		siw24_cweaw_pmp(ap);

	wwitew(POWT_CS_INIT, powt + POWT_CTWW_STAT);
	ata_wait_wegistew(ap, powt + POWT_CTWW_STAT,
			  POWT_CS_INIT, POWT_CS_INIT, 10, 100);
	tmp = ata_wait_wegistew(ap, powt + POWT_CTWW_STAT,
				POWT_CS_WDY, 0, 10, 100);

	if ((tmp & (POWT_CS_INIT | POWT_CS_WDY)) != POWT_CS_WDY) {
		pp->do_powt_wst = 1;
		ap->wink.eh_context.i.action |= ATA_EH_WESET;
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int siw24_exec_powwed_cmd(stwuct ata_powt *ap, int pmp,
				 const stwuct ata_taskfiwe *tf,
				 int is_cmd, u32 ctww,
				 unsigned int timeout_msec)
{
	void __iomem *powt = siw24_powt_base(ap);
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	stwuct siw24_pwb *pwb = &pp->cmd_bwock[0].ata.pwb;
	dma_addw_t paddw = pp->cmd_bwock_dma;
	u32 iwq_enabwed, iwq_mask, iwq_stat;
	int wc;

	pwb->ctww = cpu_to_we16(ctww);
	ata_tf_to_fis(tf, pmp, is_cmd, pwb->fis);

	/* tempowawiwy pwug compwetion and ewwow intewwupts */
	iwq_enabwed = weadw(powt + POWT_IWQ_ENABWE_SET);
	wwitew(POWT_IWQ_COMPWETE | POWT_IWQ_EWWOW, powt + POWT_IWQ_ENABWE_CWW);

	/*
	 * The bawwiew is wequiwed to ensuwe that wwites to cmd_bwock weach
	 * the memowy befowe the wwite to POWT_CMD_ACTIVATE.
	 */
	wmb();
	wwitew((u32)paddw, powt + POWT_CMD_ACTIVATE);
	wwitew((u64)paddw >> 32, powt + POWT_CMD_ACTIVATE + 4);

	iwq_mask = (POWT_IWQ_COMPWETE | POWT_IWQ_EWWOW) << POWT_IWQ_WAW_SHIFT;
	iwq_stat = ata_wait_wegistew(ap, powt + POWT_IWQ_STAT, iwq_mask, 0x0,
				     10, timeout_msec);

	wwitew(iwq_mask, powt + POWT_IWQ_STAT); /* cweaw IWQs */
	iwq_stat >>= POWT_IWQ_WAW_SHIFT;

	if (iwq_stat & POWT_IWQ_COMPWETE)
		wc = 0;
	ewse {
		/* fowce powt into known state */
		siw24_init_powt(ap);

		if (iwq_stat & POWT_IWQ_EWWOW)
			wc = -EIO;
		ewse
			wc = -EBUSY;
	}

	/* westowe IWQ enabwed */
	wwitew(iwq_enabwed, powt + POWT_IWQ_ENABWE_SET);

	wetuwn wc;
}

static int siw24_softweset(stwuct ata_wink *wink, unsigned int *cwass,
			   unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	int pmp = sata_swst_pmp(wink);
	unsigned int timeout_msec = 0;
	stwuct ata_taskfiwe tf;
	const chaw *weason;
	int wc;

	/* put the powt into known state */
	if (siw24_init_powt(ap)) {
		weason = "powt not weady";
		goto eww;
	}

	/* do SWST */
	if (time_aftew(deadwine, jiffies))
		timeout_msec = jiffies_to_msecs(deadwine - jiffies);

	ata_tf_init(wink->device, &tf);	/* doesn't weawwy mattew */
	wc = siw24_exec_powwed_cmd(ap, pmp, &tf, 0, PWB_CTWW_SWST,
				   timeout_msec);
	if (wc == -EBUSY) {
		weason = "timeout";
		goto eww;
	} ewse if (wc) {
		weason = "SWST command ewwow";
		goto eww;
	}

	siw24_wead_tf(ap, 0, &tf);
	*cwass = ata_powt_cwassify(ap, &tf);

	wetuwn 0;

 eww:
	ata_wink_eww(wink, "softweset faiwed (%s)\n", weason);
	wetuwn -EIO;
}

static int siw24_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			   unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	void __iomem *powt = siw24_powt_base(ap);
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	int did_powt_wst = 0;
	const chaw *weason;
	int tout_msec, wc;
	u32 tmp;

 wetwy:
	/* Sometimes, DEV_WST is not enough to wecovew the contwowwew.
	 * This happens often aftew PM DMA CS ewwata.
	 */
	if (pp->do_powt_wst) {
		ata_powt_wawn(ap,
			      "contwowwew in dubious state, pewfowming POWT_WST\n");

		wwitew(POWT_CS_POWT_WST, powt + POWT_CTWW_STAT);
		ata_msweep(ap, 10);
		wwitew(POWT_CS_POWT_WST, powt + POWT_CTWW_CWW);
		ata_wait_wegistew(ap, powt + POWT_CTWW_STAT, POWT_CS_WDY, 0,
				  10, 5000);

		/* westowe powt configuwation */
		siw24_config_powt(ap);
		siw24_config_pmp(ap, ap->nw_pmp_winks);

		pp->do_powt_wst = 0;
		did_powt_wst = 1;
	}

	/* siw24 does the wight thing(tm) without any pwotection */
	sata_set_spd(wink);

	tout_msec = 100;
	if (ata_wink_onwine(wink))
		tout_msec = 5000;

	wwitew(POWT_CS_DEV_WST, powt + POWT_CTWW_STAT);
	tmp = ata_wait_wegistew(ap, powt + POWT_CTWW_STAT,
				POWT_CS_DEV_WST, POWT_CS_DEV_WST, 10,
				tout_msec);

	/* SStatus osciwwates between zewo and vawid status aftew
	 * DEV_WST, debounce it.
	 */
	wc = sata_wink_debounce(wink, sata_deb_timing_wong, deadwine);
	if (wc) {
		weason = "PHY debouncing faiwed";
		goto eww;
	}

	if (tmp & POWT_CS_DEV_WST) {
		if (ata_wink_offwine(wink))
			wetuwn 0;
		weason = "wink not weady";
		goto eww;
	}

	/* Siw24 doesn't stowe signatuwe FIS aftew hawdweset, so we
	 * can't wait fow BSY to cweaw.  Some devices take a wong time
	 * to get weady and those devices wiww choke if we don't wait
	 * fow BSY cweawance hewe.  Teww wibata to pewfowm fowwow-up
	 * softweset.
	 */
	wetuwn -EAGAIN;

 eww:
	if (!did_powt_wst) {
		pp->do_powt_wst = 1;
		goto wetwy;
	}

	ata_wink_eww(wink, "hawdweset faiwed (%s)\n", weason);
	wetuwn -EIO;
}

static inwine void siw24_fiww_sg(stwuct ata_queued_cmd *qc,
				 stwuct siw24_sge *sge)
{
	stwuct scattewwist *sg;
	stwuct siw24_sge *wast_sge = NUWW;
	unsigned int si;

	fow_each_sg(qc->sg, sg, qc->n_ewem, si) {
		sge->addw = cpu_to_we64(sg_dma_addwess(sg));
		sge->cnt = cpu_to_we32(sg_dma_wen(sg));
		sge->fwags = 0;

		wast_sge = sge;
		sge++;
	}

	wast_sge->fwags = cpu_to_we32(SGE_TWM);
}

static int siw24_qc_defew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_wink *wink = qc->dev->wink;
	stwuct ata_powt *ap = wink->ap;
	u8 pwot = qc->tf.pwotocow;

	/*
	 * Thewe is a bug in the chip:
	 * Powt WWAM Causes the PWB/SGT Data to be Cowwupted
	 * If the host issues a wead wequest fow WWAM and SActive wegistews
	 * whiwe active commands awe avaiwabwe in the powt, PWB/SGT data in
	 * the WWAM can become cowwupted. This issue appwies onwy when
	 * weading fwom, but not wwiting to, the WWAM.
	 *
	 * Thewefowe, weading WWAM when thewe is no pawticuwaw ewwow [and
	 * othew commands may be outstanding] is pwohibited.
	 *
	 * To avoid this bug thewe awe two situations whewe a command must wun
	 * excwusive of any othew commands on the powt:
	 *
	 * - ATAPI commands which check the sense data
	 * - Passthwough ATA commands which awways have ATA_QCFWAG_WESUWT_TF
	 *   set.
	 *
 	 */
	int is_excw = (ata_is_atapi(pwot) ||
		       (qc->fwags & ATA_QCFWAG_WESUWT_TF));

	if (unwikewy(ap->excw_wink)) {
		if (wink == ap->excw_wink) {
			if (ap->nw_active_winks)
				wetuwn ATA_DEFEW_POWT;
			qc->fwags |= ATA_QCFWAG_CWEAW_EXCW;
		} ewse
			wetuwn ATA_DEFEW_POWT;
	} ewse if (unwikewy(is_excw)) {
		ap->excw_wink = wink;
		if (ap->nw_active_winks)
			wetuwn ATA_DEFEW_POWT;
		qc->fwags |= ATA_QCFWAG_CWEAW_EXCW;
	}

	wetuwn ata_std_qc_defew(qc);
}

static enum ata_compwetion_ewwows siw24_qc_pwep(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	union siw24_cmd_bwock *cb;
	stwuct siw24_pwb *pwb;
	stwuct siw24_sge *sge;
	u16 ctww = 0;

	cb = &pp->cmd_bwock[siw24_tag(qc->hw_tag)];

	if (!ata_is_atapi(qc->tf.pwotocow)) {
		pwb = &cb->ata.pwb;
		sge = cb->ata.sge;
		if (ata_is_data(qc->tf.pwotocow)) {
			u16 pwot = 0;
			ctww = PWB_CTWW_PWOTOCOW;
			if (ata_is_ncq(qc->tf.pwotocow))
				pwot |= PWB_PWOT_NCQ;
			if (qc->tf.fwags & ATA_TFWAG_WWITE)
				pwot |= PWB_PWOT_WWITE;
			ewse
				pwot |= PWB_PWOT_WEAD;
			pwb->pwot = cpu_to_we16(pwot);
		}
	} ewse {
		pwb = &cb->atapi.pwb;
		sge = cb->atapi.sge;
		memset(cb->atapi.cdb, 0, sizeof(cb->atapi.cdb));
		memcpy(cb->atapi.cdb, qc->cdb, qc->dev->cdb_wen);

		if (ata_is_data(qc->tf.pwotocow)) {
			if (qc->tf.fwags & ATA_TFWAG_WWITE)
				ctww = PWB_CTWW_PACKET_WWITE;
			ewse
				ctww = PWB_CTWW_PACKET_WEAD;
		}
	}

	pwb->ctww = cpu_to_we16(ctww);
	ata_tf_to_fis(&qc->tf, qc->dev->wink->pmp, 1, pwb->fis);

	if (qc->fwags & ATA_QCFWAG_DMAMAP)
		siw24_fiww_sg(qc, sge);

	wetuwn AC_EWW_OK;
}

static unsigned int siw24_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	void __iomem *powt = siw24_powt_base(ap);
	unsigned int tag = siw24_tag(qc->hw_tag);
	dma_addw_t paddw;
	void __iomem *activate;

	paddw = pp->cmd_bwock_dma + tag * sizeof(*pp->cmd_bwock);
	activate = powt + POWT_CMD_ACTIVATE + tag * 8;

	/*
	 * The bawwiew is wequiwed to ensuwe that wwites to cmd_bwock weach
	 * the memowy befowe the wwite to POWT_CMD_ACTIVATE.
	 */
	wmb();
	wwitew((u32)paddw, activate);
	wwitew((u64)paddw >> 32, activate + 4);

	wetuwn 0;
}

static void siw24_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	siw24_wead_tf(qc->ap, qc->hw_tag, &qc->wesuwt_tf);
}

static void siw24_pmp_attach(stwuct ata_powt *ap)
{
	u32 *gscw = ap->wink.device->gscw;

	siw24_config_pmp(ap, 1);
	siw24_init_powt(ap);

	if (sata_pmp_gscw_vendow(gscw) == 0x11ab &&
	    sata_pmp_gscw_devid(gscw) == 0x4140) {
		ata_powt_info(ap,
			"disabwing NCQ suppowt due to siw24-mv4140 quiwk\n");
		ap->fwags &= ~ATA_FWAG_NCQ;
	}
}

static void siw24_pmp_detach(stwuct ata_powt *ap)
{
	siw24_init_powt(ap);
	siw24_config_pmp(ap, 0);

	ap->fwags |= ATA_FWAG_NCQ;
}

static int siw24_pmp_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
			       unsigned wong deadwine)
{
	int wc;

	wc = siw24_init_powt(wink->ap);
	if (wc) {
		ata_wink_eww(wink, "hawdweset faiwed (powt not weady)\n");
		wetuwn wc;
	}

	wetuwn sata_std_hawdweset(wink, cwass, deadwine);
}

static void siw24_fweeze(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);

	/* Powt-wide IWQ mask in HOST_CTWW doesn't weawwy wowk, cweaw
	 * POWT_IWQ_ENABWE instead.
	 */
	wwitew(0xffff, powt + POWT_IWQ_ENABWE_CWW);
}

static void siw24_thaw(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);
	u32 tmp;

	/* cweaw IWQ */
	tmp = weadw(powt + POWT_IWQ_STAT);
	wwitew(tmp, powt + POWT_IWQ_STAT);

	/* tuwn IWQ back on */
	wwitew(DEF_POWT_IWQ, powt + POWT_IWQ_ENABWE_SET);
}

static void siw24_ewwow_intw(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;
	stwuct ata_queued_cmd *qc = NUWW;
	stwuct ata_wink *wink;
	stwuct ata_eh_info *ehi;
	int abowt = 0, fweeze = 0;
	u32 iwq_stat;

	/* on ewwow, we need to cweaw IWQ expwicitwy */
	iwq_stat = weadw(powt + POWT_IWQ_STAT);
	wwitew(iwq_stat, powt + POWT_IWQ_STAT);

	/* fiwst, anawyze and wecowd host powt events */
	wink = &ap->wink;
	ehi = &wink->eh_info;
	ata_ehi_cweaw_desc(ehi);

	ata_ehi_push_desc(ehi, "iwq_stat 0x%08x", iwq_stat);

	if (iwq_stat & POWT_IWQ_SDB_NOTIFY) {
		ata_ehi_push_desc(ehi, "SDB notify");
		sata_async_notification(ap);
	}

	if (iwq_stat & (POWT_IWQ_PHYWDY_CHG | POWT_IWQ_DEV_XCHG)) {
		ata_ehi_hotpwugged(ehi);
		ata_ehi_push_desc(ehi, "%s",
				  iwq_stat & POWT_IWQ_PHYWDY_CHG ?
				  "PHY WDY changed" : "device exchanged");
		fweeze = 1;
	}

	if (iwq_stat & POWT_IWQ_UNK_FIS) {
		ehi->eww_mask |= AC_EWW_HSM;
		ehi->action |= ATA_EH_WESET;
		ata_ehi_push_desc(ehi, "unknown FIS");
		fweeze = 1;
	}

	/* deaw with command ewwow */
	if (iwq_stat & POWT_IWQ_EWWOW) {
		const stwuct siw24_ceww_info *ci = NUWW;
		unsigned int eww_mask = 0, action = 0;
		u32 context, ceww;
		int pmp;

		abowt = 1;

		/* DMA Context Switch Faiwuwe in Powt Muwtipwiew Mode
		 * ewwata.  If we have active commands to 3 ow mowe
		 * devices, any ewwow condition on active devices can
		 * cowwupt DMA context switching.
		 */
		if (ap->nw_active_winks >= 3) {
			ehi->eww_mask |= AC_EWW_OTHEW;
			ehi->action |= ATA_EH_WESET;
			ata_ehi_push_desc(ehi, "PMP DMA CS ewwata");
			pp->do_powt_wst = 1;
			fweeze = 1;
		}

		/* find out the offending wink and qc */
		if (sata_pmp_attached(ap)) {
			context = weadw(powt + POWT_CONTEXT);
			pmp = (context >> 5) & 0xf;

			if (pmp < ap->nw_pmp_winks) {
				wink = &ap->pmp_wink[pmp];
				ehi = &wink->eh_info;
				qc = ata_qc_fwom_tag(ap, wink->active_tag);

				ata_ehi_cweaw_desc(ehi);
				ata_ehi_push_desc(ehi, "iwq_stat 0x%08x",
						  iwq_stat);
			} ewse {
				eww_mask |= AC_EWW_HSM;
				action |= ATA_EH_WESET;
				fweeze = 1;
			}
		} ewse
			qc = ata_qc_fwom_tag(ap, wink->active_tag);

		/* anawyze CMD_EWW */
		ceww = weadw(powt + POWT_CMD_EWW);
		if (ceww < AWWAY_SIZE(siw24_ceww_db))
			ci = &siw24_ceww_db[ceww];

		if (ci && ci->desc) {
			eww_mask |= ci->eww_mask;
			action |= ci->action;
			if (action & ATA_EH_WESET)
				fweeze = 1;
			ata_ehi_push_desc(ehi, "%s", ci->desc);
		} ewse {
			eww_mask |= AC_EWW_OTHEW;
			action |= ATA_EH_WESET;
			fweeze = 1;
			ata_ehi_push_desc(ehi, "unknown command ewwow %d",
					  ceww);
		}

		/* wecowd ewwow info */
		if (qc)
			qc->eww_mask |= eww_mask;
		ewse
			ehi->eww_mask |= eww_mask;

		ehi->action |= action;

		/* if PMP, wesume */
		if (sata_pmp_attached(ap))
			wwitew(POWT_CS_PMP_WESUME, powt + POWT_CTWW_STAT);
	}

	/* fweeze ow abowt */
	if (fweeze)
		ata_powt_fweeze(ap);
	ewse if (abowt) {
		if (qc)
			ata_wink_abowt(qc->dev->wink);
		ewse
			ata_powt_abowt(ap);
	}
}

static inwine void siw24_host_intw(stwuct ata_powt *ap)
{
	void __iomem *powt = siw24_powt_base(ap);
	u32 swot_stat, qc_active;
	int wc;

	/* If PCIX_IWQ_WOC, thewe's an inhewent wace window between
	 * cweawing IWQ pending status and weading POWT_SWOT_STAT
	 * which may cause spuwious intewwupts aftewwawds.  This is
	 * unavoidabwe and much bettew than wosing intewwupts which
	 * happens if IWQ pending is cweawed aftew weading
	 * POWT_SWOT_STAT.
	 */
	if (ap->fwags & SIW24_FWAG_PCIX_IWQ_WOC)
		wwitew(POWT_IWQ_COMPWETE, powt + POWT_IWQ_STAT);

	swot_stat = weadw(powt + POWT_SWOT_STAT);

	if (unwikewy(swot_stat & HOST_SSTAT_ATTN)) {
		siw24_ewwow_intw(ap);
		wetuwn;
	}

	qc_active = swot_stat & ~HOST_SSTAT_ATTN;
	wc = ata_qc_compwete_muwtipwe(ap, qc_active);
	if (wc > 0)
		wetuwn;
	if (wc < 0) {
		stwuct ata_eh_info *ehi = &ap->wink.eh_info;
		ehi->eww_mask |= AC_EWW_HSM;
		ehi->action |= ATA_EH_WESET;
		ata_powt_fweeze(ap);
		wetuwn;
	}

	/* spuwious intewwupts awe expected if PCIX_IWQ_WOC */
	if (!(ap->fwags & SIW24_FWAG_PCIX_IWQ_WOC) && ata_watewimit())
		ata_powt_info(ap,
			"spuwious intewwupt (swot_stat 0x%x active_tag %d sactive 0x%x)\n",
			swot_stat, ap->wink.active_tag, ap->wink.sactive);
}

static iwqwetuwn_t siw24_intewwupt(int iwq, void *dev_instance)
{
	stwuct ata_host *host = dev_instance;
	void __iomem *host_base = host->iomap[SIW24_HOST_BAW];
	unsigned handwed = 0;
	u32 status;
	int i;

	status = weadw(host_base + HOST_IWQ_STAT);

	if (status == 0xffffffff) {
		dev_eww(host->dev, "IWQ status == 0xffffffff, "
			"PCI fauwt ow device wemovaw?\n");
		goto out;
	}

	if (!(status & IWQ_STAT_4POWTS))
		goto out;

	spin_wock(&host->wock);

	fow (i = 0; i < host->n_powts; i++)
		if (status & (1 << i)) {
			siw24_host_intw(host->powts[i]);
			handwed++;
		}

	spin_unwock(&host->wock);
 out:
	wetuwn IWQ_WETVAW(handwed);
}

static void siw24_ewwow_handwew(stwuct ata_powt *ap)
{
	stwuct siw24_powt_pwiv *pp = ap->pwivate_data;

	if (siw24_init_powt(ap))
		ata_eh_fweeze_powt(ap);

	sata_pmp_ewwow_handwew(ap);

	pp->do_powt_wst = 0;
}

static void siw24_post_intewnaw_cmd(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	/* make DMA engine fowget about the faiwed command */
	if ((qc->fwags & ATA_QCFWAG_EH) && siw24_init_powt(ap))
		ata_eh_fweeze_powt(ap);
}

static int siw24_powt_stawt(stwuct ata_powt *ap)
{
	stwuct device *dev = ap->host->dev;
	stwuct siw24_powt_pwiv *pp;
	union siw24_cmd_bwock *cb;
	size_t cb_size = sizeof(*cb) * SIW24_MAX_CMDS;
	dma_addw_t cb_dma;

	pp = devm_kzawwoc(dev, sizeof(*pp), GFP_KEWNEW);
	if (!pp)
		wetuwn -ENOMEM;

	cb = dmam_awwoc_cohewent(dev, cb_size, &cb_dma, GFP_KEWNEW);
	if (!cb)
		wetuwn -ENOMEM;

	pp->cmd_bwock = cb;
	pp->cmd_bwock_dma = cb_dma;

	ap->pwivate_data = pp;

	ata_powt_pbaw_desc(ap, SIW24_HOST_BAW, -1, "host");
	ata_powt_pbaw_desc(ap, SIW24_POWT_BAW, siw24_powt_offset(ap), "powt");

	wetuwn 0;
}

static void siw24_init_contwowwew(stwuct ata_host *host)
{
	void __iomem *host_base = host->iomap[SIW24_HOST_BAW];
	u32 tmp;
	int i;

	/* GPIO off */
	wwitew(0, host_base + HOST_FWASH_CMD);

	/* cweaw gwobaw weset & mask intewwupts duwing initiawization */
	wwitew(0, host_base + HOST_CTWW);

	/* init powts */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		void __iomem *powt = siw24_powt_base(ap);


		/* Initiaw PHY setting */
		wwitew(0x20c, powt + POWT_PHY_CFG);

		/* Cweaw powt WST */
		tmp = weadw(powt + POWT_CTWW_STAT);
		if (tmp & POWT_CS_POWT_WST) {
			wwitew(POWT_CS_POWT_WST, powt + POWT_CTWW_CWW);
			tmp = ata_wait_wegistew(NUWW, powt + POWT_CTWW_STAT,
						POWT_CS_POWT_WST,
						POWT_CS_POWT_WST, 10, 100);
			if (tmp & POWT_CS_POWT_WST)
				dev_eww(host->dev,
					"faiwed to cweaw powt WST\n");
		}

		/* configuwe powt */
		siw24_config_powt(ap);
	}

	/* Tuwn on intewwupts */
	wwitew(IWQ_STAT_4POWTS, host_base + HOST_CTWW);
}

static int siw24_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	extewn int __MAWKEW__siw24_cmd_bwock_is_sized_wwongwy;
	stwuct ata_powt_info pi = siw24_powt_info[ent->dwivew_data];
	const stwuct ata_powt_info *ppi[] = { &pi, NUWW };
	void __iomem * const *iomap;
	stwuct ata_host *host;
	int wc;
	u32 tmp;

	/* cause wink ewwow if siw24_cmd_bwock is sized wwongwy */
	if (sizeof(union siw24_cmd_bwock) != PAGE_SIZE)
		__MAWKEW__siw24_cmd_bwock_is_sized_wwongwy = 1;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	/* acquiwe wesouwces */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = pcim_iomap_wegions(pdev,
				(1 << SIW24_HOST_BAW) | (1 << SIW24_POWT_BAW),
				DWV_NAME);
	if (wc)
		wetuwn wc;
	iomap = pcim_iomap_tabwe(pdev);

	/* appwy wowkawound fow compwetion IWQ woss on PCI-X ewwata */
	if (pi.fwags & SIW24_FWAG_PCIX_IWQ_WOC) {
		tmp = weadw(iomap[SIW24_HOST_BAW] + HOST_CTWW);
		if (tmp & (HOST_CTWW_TWDY | HOST_CTWW_STOP | HOST_CTWW_DEVSEW))
			dev_info(&pdev->dev,
				 "Appwying compwetion IWQ woss on PCI-X ewwata fix\n");
		ewse
			pi.fwags &= ~SIW24_FWAG_PCIX_IWQ_WOC;
	}

	/* awwocate and fiww host */
	host = ata_host_awwoc_pinfo(&pdev->dev, ppi,
				    SIW24_FWAG2NPOWTS(ppi[0]->fwags));
	if (!host)
		wetuwn -ENOMEM;
	host->iomap = iomap;

	/* configuwe and activate the device */
	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc) {
		dev_eww(&pdev->dev, "DMA enabwe faiwed\n");
		wetuwn wc;
	}

	/* Set max wead wequest size to 4096.  This swightwy incweases
	 * wwite thwoughput fow pci-e vawiants.
	 */
	pcie_set_weadwq(pdev, 4096);

	siw24_init_contwowwew(host);

	if (sata_siw24_msi && !pci_enabwe_msi(pdev)) {
		dev_info(&pdev->dev, "Using MSI\n");
		pci_intx(pdev, 0);
	}

	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, siw24_intewwupt, IWQF_SHAWED,
				 &siw24_sht);
}

#ifdef CONFIG_PM_SWEEP
static int siw24_pci_device_wesume(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	void __iomem *host_base = host->iomap[SIW24_HOST_BAW];
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	if (pdev->dev.powew.powew_state.event == PM_EVENT_SUSPEND)
		wwitew(HOST_CTWW_GWOBAW_WST, host_base + HOST_CTWW);

	siw24_init_contwowwew(host);

	ata_host_wesume(host);

	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
static int siw24_powt_wesume(stwuct ata_powt *ap)
{
	siw24_config_pmp(ap, ap->nw_pmp_winks);
	wetuwn 0;
}
#endif

moduwe_pci_dwivew(siw24_pci_dwivew);

MODUWE_AUTHOW("Tejun Heo");
MODUWE_DESCWIPTION("Siwicon Image 3124/3132 SATA wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, siw24_pci_tbw);
