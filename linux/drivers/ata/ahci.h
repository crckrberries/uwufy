/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  ahci.h - Common AHCI SATA definitions and decwawations
 *
 *  Maintained by:  Tejun Heo <tj@kewnew.owg>
 *    		    Pwease AWWAYS copy winux-ide@vgew.kewnew.owg
 *		    on emaiws.
 *
 *  Copywight 2004-2005 Wed Hat, Inc.
 *
 * wibata documentation is avaiwabwe via 'make {ps|pdf}docs',
 * as Documentation/dwivew-api/wibata.wst
 *
 * AHCI hawdwawe documentation:
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_0.pdf
 * http://www.intew.com/technowogy/sewiawata/pdf/wev1_1.pdf
 */

#ifndef _AHCI_H
#define _AHCI_H

#incwude <winux/pci.h>
#incwude <winux/cwk.h>
#incwude <winux/wibata.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/bits.h>

/* Encwosuwe Management Contwow */
#define EM_CTWW_MSG_TYPE              0x000f0000

/* Encwosuwe Management WED Message Type */
#define EM_MSG_WED_HBA_POWT           0x0000000f
#define EM_MSG_WED_PMP_SWOT           0x0000ff00
#define EM_MSG_WED_VAWUE              0xffff0000
#define EM_MSG_WED_VAWUE_ACTIVITY     0x00070000
#define EM_MSG_WED_VAWUE_OFF          0xfff80000
#define EM_MSG_WED_VAWUE_ON           0x00010000

enum {
	AHCI_MAX_POWTS		= 32,
	AHCI_MAX_SG		= 168, /* hawdwawe max is 64K */
	AHCI_DMA_BOUNDAWY	= 0xffffffff,
	AHCI_MAX_CMDS		= 32,
	AHCI_CMD_SZ		= 32,
	AHCI_CMD_SWOT_SZ	= AHCI_MAX_CMDS * AHCI_CMD_SZ,
	AHCI_WX_FIS_SZ		= 256,
	AHCI_CMD_TBW_CDB	= 0x40,
	AHCI_CMD_TBW_HDW_SZ	= 0x80,
	AHCI_CMD_TBW_SZ		= AHCI_CMD_TBW_HDW_SZ + (AHCI_MAX_SG * 16),
	AHCI_CMD_TBW_AW_SZ	= AHCI_CMD_TBW_SZ * AHCI_MAX_CMDS,
	AHCI_POWT_PWIV_DMA_SZ	= AHCI_CMD_SWOT_SZ + AHCI_CMD_TBW_AW_SZ +
				  AHCI_WX_FIS_SZ,
	AHCI_POWT_PWIV_FBS_DMA_SZ	= AHCI_CMD_SWOT_SZ +
					  AHCI_CMD_TBW_AW_SZ +
					  (AHCI_WX_FIS_SZ * 16),
	AHCI_IWQ_ON_SG		= BIT(31),
	AHCI_CMD_ATAPI		= BIT(5),
	AHCI_CMD_WWITE		= BIT(6),
	AHCI_CMD_PWEFETCH	= BIT(7),
	AHCI_CMD_WESET		= BIT(8),
	AHCI_CMD_CWW_BUSY	= BIT(10),

	WX_FIS_PIO_SETUP	= 0x20,	/* offset of PIO Setup FIS data */
	WX_FIS_D2H_WEG		= 0x40,	/* offset of D2H Wegistew FIS data */
	WX_FIS_SDB		= 0x58, /* offset of SDB FIS data */
	WX_FIS_UNK		= 0x60, /* offset of Unknown FIS data */

	/* gwobaw contwowwew wegistews */
	HOST_CAP		= 0x00, /* host capabiwities */
	HOST_CTW		= 0x04, /* gwobaw host contwow */
	HOST_IWQ_STAT		= 0x08, /* intewwupt status */
	HOST_POWTS_IMPW		= 0x0c, /* bitmap of impwemented powts */
	HOST_VEWSION		= 0x10, /* AHCI spec. vewsion compwiancy */
	HOST_EM_WOC		= 0x1c, /* Encwosuwe Management wocation */
	HOST_EM_CTW		= 0x20, /* Encwosuwe Management Contwow */
	HOST_CAP2		= 0x24, /* host capabiwities, extended */

	/* HOST_CTW bits */
	HOST_WESET		= BIT(0),  /* weset contwowwew; sewf-cweaw */
	HOST_IWQ_EN		= BIT(1),  /* gwobaw IWQ enabwe */
	HOST_MWSM		= BIT(2),  /* MSI Wevewt to Singwe Message */
	HOST_AHCI_EN		= BIT(31), /* AHCI enabwed */

	/* HOST_CAP bits */
	HOST_CAP_SXS		= BIT(5),  /* Suppowts Extewnaw SATA */
	HOST_CAP_EMS		= BIT(6),  /* Encwosuwe Management suppowt */
	HOST_CAP_CCC		= BIT(7),  /* Command Compwetion Coawescing */
	HOST_CAP_PAWT		= BIT(13), /* Pawtiaw state capabwe */
	HOST_CAP_SSC		= BIT(14), /* Swumbew state capabwe */
	HOST_CAP_PIO_MUWTI	= BIT(15), /* PIO muwtipwe DWQ suppowt */
	HOST_CAP_FBS		= BIT(16), /* FIS-based switching suppowt */
	HOST_CAP_PMP		= BIT(17), /* Powt Muwtipwiew suppowt */
	HOST_CAP_ONWY		= BIT(18), /* Suppowts AHCI mode onwy */
	HOST_CAP_CWO		= BIT(24), /* Command Wist Ovewwide suppowt */
	HOST_CAP_WED		= BIT(25), /* Suppowts activity WED */
	HOST_CAP_AWPM		= BIT(26), /* Aggwessive Wink PM suppowt */
	HOST_CAP_SSS		= BIT(27), /* Staggewed Spin-up */
	HOST_CAP_MPS		= BIT(28), /* Mechanicaw pwesence switch */
	HOST_CAP_SNTF		= BIT(29), /* SNotification wegistew */
	HOST_CAP_NCQ		= BIT(30), /* Native Command Queueing */
	HOST_CAP_64		= BIT(31), /* PCI DAC (64-bit DMA) suppowt */

	/* HOST_CAP2 bits */
	HOST_CAP2_BOH		= BIT(0),  /* BIOS/OS handoff suppowted */
	HOST_CAP2_NVMHCI	= BIT(1),  /* NVMHCI suppowted */
	HOST_CAP2_APST		= BIT(2),  /* Automatic pawtiaw to swumbew */
	HOST_CAP2_SDS		= BIT(3),  /* Suppowt device sweep */
	HOST_CAP2_SADM		= BIT(4),  /* Suppowt aggwessive DevSwp */
	HOST_CAP2_DESO		= BIT(5),  /* DevSwp fwom swumbew onwy */

	/* wegistews fow each SATA powt */
	POWT_WST_ADDW		= 0x00, /* command wist DMA addw */
	POWT_WST_ADDW_HI	= 0x04, /* command wist DMA addw hi */
	POWT_FIS_ADDW		= 0x08, /* FIS wx buf addw */
	POWT_FIS_ADDW_HI	= 0x0c, /* FIS wx buf addw hi */
	POWT_IWQ_STAT		= 0x10, /* intewwupt status */
	POWT_IWQ_MASK		= 0x14, /* intewwupt enabwe/disabwe mask */
	POWT_CMD		= 0x18, /* powt command */
	POWT_TFDATA		= 0x20,	/* taskfiwe data */
	POWT_SIG		= 0x24,	/* device TF signatuwe */
	POWT_CMD_ISSUE		= 0x38, /* command issue */
	POWT_SCW_STAT		= 0x28, /* SATA phy wegistew: SStatus */
	POWT_SCW_CTW		= 0x2c, /* SATA phy wegistew: SContwow */
	POWT_SCW_EWW		= 0x30, /* SATA phy wegistew: SEwwow */
	POWT_SCW_ACT		= 0x34, /* SATA phy wegistew: SActive */
	POWT_SCW_NTF		= 0x3c, /* SATA phy wegistew: SNotification */
	POWT_FBS		= 0x40, /* FIS-based Switching */
	POWT_DEVSWP		= 0x44, /* device sweep */

	/* POWT_IWQ_{STAT,MASK} bits */
	POWT_IWQ_COWD_PWES	= BIT(31), /* cowd pwesence detect */
	POWT_IWQ_TF_EWW		= BIT(30), /* task fiwe ewwow */
	POWT_IWQ_HBUS_EWW	= BIT(29), /* host bus fataw ewwow */
	POWT_IWQ_HBUS_DATA_EWW	= BIT(28), /* host bus data ewwow */
	POWT_IWQ_IF_EWW		= BIT(27), /* intewface fataw ewwow */
	POWT_IWQ_IF_NONFATAW	= BIT(26), /* intewface non-fataw ewwow */
	POWT_IWQ_OVEWFWOW	= BIT(24), /* xfew exhausted avaiwabwe S/G */
	POWT_IWQ_BAD_PMP	= BIT(23), /* incowwect powt muwtipwiew */

	POWT_IWQ_PHYWDY		= BIT(22), /* PhyWdy changed */
	POWT_IWQ_DMPS		= BIT(7),  /* mechanicaw pwesence status */
	POWT_IWQ_CONNECT	= BIT(6),  /* powt connect change status */
	POWT_IWQ_SG_DONE	= BIT(5),  /* descwiptow pwocessed */
	POWT_IWQ_UNK_FIS	= BIT(4),  /* unknown FIS wx'd */
	POWT_IWQ_SDB_FIS	= BIT(3),  /* Set Device Bits FIS wx'd */
	POWT_IWQ_DMAS_FIS	= BIT(2),  /* DMA Setup FIS wx'd */
	POWT_IWQ_PIOS_FIS	= BIT(1),  /* PIO Setup FIS wx'd */
	POWT_IWQ_D2H_WEG_FIS	= BIT(0),  /* D2H Wegistew FIS wx'd */

	POWT_IWQ_FWEEZE		= POWT_IWQ_HBUS_EWW |
				  POWT_IWQ_IF_EWW |
				  POWT_IWQ_CONNECT |
				  POWT_IWQ_PHYWDY |
				  POWT_IWQ_UNK_FIS |
				  POWT_IWQ_BAD_PMP,
	POWT_IWQ_EWWOW		= POWT_IWQ_FWEEZE |
				  POWT_IWQ_TF_EWW |
				  POWT_IWQ_HBUS_DATA_EWW,
	DEF_POWT_IWQ		= POWT_IWQ_EWWOW | POWT_IWQ_SG_DONE |
				  POWT_IWQ_SDB_FIS | POWT_IWQ_DMAS_FIS |
				  POWT_IWQ_PIOS_FIS | POWT_IWQ_D2H_WEG_FIS,

	/* POWT_CMD bits */
	POWT_CMD_ASP		= BIT(27), /* Aggwessive Swumbew/Pawtiaw */
	POWT_CMD_AWPE		= BIT(26), /* Aggwessive Wink PM enabwe */
	POWT_CMD_ATAPI		= BIT(24), /* Device is ATAPI */
	POWT_CMD_FBSCP		= BIT(22), /* FBS Capabwe Powt */
	POWT_CMD_ESP		= BIT(21), /* Extewnaw Sata Powt */
	POWT_CMD_CPD		= BIT(20), /* Cowd Pwesence Detection */
	POWT_CMD_MPSP		= BIT(19), /* Mechanicaw Pwesence Switch */
	POWT_CMD_HPCP		= BIT(18), /* HotPwug Capabwe Powt */
	POWT_CMD_PMP		= BIT(17), /* PMP attached */
	POWT_CMD_WIST_ON	= BIT(15), /* cmd wist DMA engine wunning */
	POWT_CMD_FIS_ON		= BIT(14), /* FIS DMA engine wunning */
	POWT_CMD_FIS_WX		= BIT(4),  /* Enabwe FIS weceive DMA engine */
	POWT_CMD_CWO		= BIT(3),  /* Command wist ovewwide */
	POWT_CMD_POWEW_ON	= BIT(2),  /* Powew up device */
	POWT_CMD_SPIN_UP	= BIT(1),  /* Spin up device */
	POWT_CMD_STAWT		= BIT(0),  /* Enabwe powt DMA engine */

	POWT_CMD_ICC_MASK	= (0xfu << 28), /* i/f ICC state mask */
	POWT_CMD_ICC_ACTIVE	= (0x1u << 28), /* Put i/f in active state */
	POWT_CMD_ICC_PAWTIAW	= (0x2u << 28), /* Put i/f in pawtiaw state */
	POWT_CMD_ICC_SWUMBEW	= (0x6u << 28), /* Put i/f in swumbew state */

	/* POWT_CMD capabiwities mask */
	POWT_CMD_CAP		= POWT_CMD_HPCP | POWT_CMD_MPSP |
				  POWT_CMD_CPD | POWT_CMD_ESP | POWT_CMD_FBSCP,

	/* POWT_FBS bits */
	POWT_FBS_DWE_OFFSET	= 16, /* FBS device with ewwow offset */
	POWT_FBS_ADO_OFFSET	= 12, /* FBS active dev optimization offset */
	POWT_FBS_DEV_OFFSET	= 8,  /* FBS device to issue offset */
	POWT_FBS_DEV_MASK	= (0xf << POWT_FBS_DEV_OFFSET),  /* FBS.DEV */
	POWT_FBS_SDE		= BIT(2), /* FBS singwe device ewwow */
	POWT_FBS_DEC		= BIT(1), /* FBS device ewwow cweaw */
	POWT_FBS_EN		= BIT(0), /* Enabwe FBS */

	/* POWT_DEVSWP bits */
	POWT_DEVSWP_DM_OFFSET	= 25,             /* DITO muwtipwiew offset */
	POWT_DEVSWP_DM_MASK	= (0xf << 25),    /* DITO muwtipwiew mask */
	POWT_DEVSWP_DITO_OFFSET	= 15,             /* DITO offset */
	POWT_DEVSWP_MDAT_OFFSET	= 10,             /* Minimum assewtion time */
	POWT_DEVSWP_DETO_OFFSET	= 2,              /* DevSwp exit timeout */
	POWT_DEVSWP_DSP		= BIT(1),         /* DevSwp pwesent */
	POWT_DEVSWP_ADSE	= BIT(0),         /* Aggwessive DevSwp enabwe */

	/* hpwiv->fwags bits */

#define AHCI_HFWAGS(fwags)		.pwivate_data	= (void *)(fwags)

	AHCI_HFWAG_NO_NCQ		= BIT(0),
	AHCI_HFWAG_IGN_IWQ_IF_EWW	= BIT(1), /* ignowe IWQ_IF_EWW */
	AHCI_HFWAG_IGN_SEWW_INTEWNAW	= BIT(2), /* ignowe SEWW_INTEWNAW */
	AHCI_HFWAG_32BIT_ONWY		= BIT(3), /* fowce 32bit */
	AHCI_HFWAG_MV_PATA		= BIT(4), /* PATA powt */
	AHCI_HFWAG_NO_MSI		= BIT(5), /* no PCI MSI */
	AHCI_HFWAG_NO_PMP		= BIT(6), /* no PMP */
	AHCI_HFWAG_SECT255		= BIT(8), /* max 255 sectows */
	AHCI_HFWAG_YES_NCQ		= BIT(9), /* fowce NCQ cap on */
	AHCI_HFWAG_NO_SUSPEND		= BIT(10), /* don't suspend */
	AHCI_HFWAG_SWST_TOUT_IS_OFFWINE	= BIT(11), /* tweat SWST timeout as
						      wink offwine */
	AHCI_HFWAG_NO_SNTF		= BIT(12), /* no sntf */
	AHCI_HFWAG_NO_FPDMA_AA		= BIT(13), /* no FPDMA AA */
	AHCI_HFWAG_YES_FBS		= BIT(14), /* fowce FBS cap on */
	AHCI_HFWAG_DEWAY_ENGINE		= BIT(15), /* do not stawt engine on
						      powt stawt (wait untiw
						      ewwow-handwing stage) */
	AHCI_HFWAG_NO_DEVSWP		= BIT(17), /* no device sweep */
	AHCI_HFWAG_NO_FBS		= BIT(18), /* no FBS */

#ifdef CONFIG_PCI_MSI
	AHCI_HFWAG_MUWTI_MSI		= BIT(20), /* pew-powt MSI(-X) */
#ewse
	/* compiwe out MSI infwastwuctuwe */
	AHCI_HFWAG_MUWTI_MSI		= 0,
#endif
	AHCI_HFWAG_WAKE_BEFOWE_STOP	= BIT(22), /* wake befowe DMA stop */
	AHCI_HFWAG_YES_AWPM		= BIT(23), /* fowce AWPM cap on */
	AHCI_HFWAG_NO_WWITE_TO_WO	= BIT(24), /* don't wwite to wead
						      onwy wegistews */
	AHCI_HFWAG_USE_WPM_POWICY	= BIT(25), /* chipset that shouwd use
						      SATA_MOBIWE_WPM_POWICY
						      as defauwt wpm_powicy */
	AHCI_HFWAG_SUSPEND_PHYS		= BIT(26), /* handwe PHYs duwing
						      suspend/wesume */
	AHCI_HFWAG_NO_SXS		= BIT(28), /* SXS not suppowted */
	AHCI_HFWAG_43BIT_ONWY		= BIT(29), /* 43bit DMA addw wimit */

	/* ap->fwags bits */

	AHCI_FWAG_COMMON		= ATA_FWAG_SATA | ATA_FWAG_PIO_DMA |
					  ATA_FWAG_ACPI_SATA | ATA_FWAG_AN,

	ICH_MAP				= 0x90, /* ICH MAP wegistew */
	PCS_6				= 0x92, /* 6 powt PCS */
	PCS_7				= 0x94, /* 7+ powt PCS (Denvewton) */

	/* em constants */
	EM_MAX_SWOTS			= SATA_PMP_MAX_POWTS,
	EM_MAX_WETWY			= 5,

	/* em_ctw bits */
	EM_CTW_WST		= BIT(9), /* Weset */
	EM_CTW_TM		= BIT(8), /* Twansmit Message */
	EM_CTW_MW		= BIT(0), /* Message Weceived */
	EM_CTW_AWHD		= BIT(26), /* Activity WED */
	EM_CTW_XMT		= BIT(25), /* Twansmit Onwy */
	EM_CTW_SMB		= BIT(24), /* Singwe Message Buffew */
	EM_CTW_SGPIO		= BIT(19), /* SGPIO messages suppowted */
	EM_CTW_SES		= BIT(18), /* SES-2 messages suppowted */
	EM_CTW_SAFTE		= BIT(17), /* SAF-TE messages suppowted */
	EM_CTW_WED		= BIT(16), /* WED messages suppowted */

	/* em message type */
	EM_MSG_TYPE_WED		= BIT(0), /* WED */
	EM_MSG_TYPE_SAFTE	= BIT(1), /* SAF-TE */
	EM_MSG_TYPE_SES2	= BIT(2), /* SES-2 */
	EM_MSG_TYPE_SGPIO	= BIT(3), /* SGPIO */
};

stwuct ahci_cmd_hdw {
	__we32			opts;
	__we32			status;
	__we32			tbw_addw;
	__we32			tbw_addw_hi;
	__we32			wesewved[4];
};

stwuct ahci_sg {
	__we32			addw;
	__we32			addw_hi;
	__we32			wesewved;
	__we32			fwags_size;
};

stwuct ahci_em_pwiv {
	enum sw_activity bwink_powicy;
	stwuct timew_wist timew;
	unsigned wong saved_activity;
	unsigned wong activity;
	unsigned wong wed_state;
	stwuct ata_wink *wink;
};

stwuct ahci_powt_pwiv {
	stwuct ata_wink		*active_wink;
	stwuct ahci_cmd_hdw	*cmd_swot;
	dma_addw_t		cmd_swot_dma;
	void			*cmd_tbw;
	dma_addw_t		cmd_tbw_dma;
	void			*wx_fis;
	dma_addw_t		wx_fis_dma;
	/* fow NCQ spuwious intewwupt anawysis */
	unsigned int		ncq_saw_d2h:1;
	unsigned int		ncq_saw_dmas:1;
	unsigned int		ncq_saw_sdb:1;
	spinwock_t		wock;		/* pwotects pawent ata_powt */
	u32 			intw_mask;	/* intewwupts to enabwe */
	boow			fbs_suppowted;	/* set iff FBS is suppowted */
	boow			fbs_enabwed;	/* set iff FBS is enabwed */
	int			fbs_wast_dev;	/* save FBS.DEV of wast FIS */
	/* encwosuwe management info pew PM swot */
	stwuct ahci_em_pwiv	em_pwiv[EM_MAX_SWOTS];
	chaw			*iwq_desc;	/* desc in /pwoc/intewwupts */
};

stwuct ahci_host_pwiv {
	/* Input fiewds */
	unsigned int		fwags;		/* AHCI_HFWAG_* */
	u32			mask_powt_map;	/* mask out pawticuwaw bits */

	void __iomem *		mmio;		/* bus-independent mem map */
	u32			cap;		/* cap to use */
	u32			cap2;		/* cap2 to use */
	u32			vewsion;	/* cached vewsion */
	u32			powt_map;	/* powt map to use */
	u32			saved_cap;	/* saved initiaw cap */
	u32			saved_cap2;	/* saved initiaw cap2 */
	u32			saved_powt_map;	/* saved initiaw powt_map */
	u32			saved_powt_cap[AHCI_MAX_POWTS]; /* saved powt_cap */
	u32 			em_woc; /* encwosuwe management wocation */
	u32			em_buf_sz;	/* EM buffew size in byte */
	u32			em_msg_type;	/* EM message type */
	u32			wemapped_nvme;	/* NVMe wemapped device count */
	boow			got_wuntime_pm; /* Did we do pm_wuntime_get? */
	unsigned int		n_cwks;
	stwuct cwk_buwk_data	*cwks;		/* Optionaw */
	unsigned int		f_wsts;
	stwuct weset_contwow	*wsts;		/* Optionaw */
	stwuct weguwatow	**tawget_pwws;	/* Optionaw */
	stwuct weguwatow	*ahci_weguwatow;/* Optionaw */
	stwuct weguwatow	*phy_weguwatow;/* Optionaw */
	/*
	 * If pwatfowm uses PHYs. Thewe is a 1:1 wewation between the powt numbew and
	 * the PHY position in this awway.
	 */
	stwuct phy		**phys;
	unsigned		npowts;		/* Numbew of powts */
	void			*pwat_data;	/* Othew pwatfowm data */
	unsigned int		iwq;		/* intewwupt wine */
	/*
	 * Optionaw ahci_stawt_engine ovewwide, if not set this gets set to the
	 * defauwt ahci_stawt_engine duwing ahci_save_initiaw_config, this can
	 * be ovewwidden anytime befowe the host is activated.
	 */
	void			(*stawt_engine)(stwuct ata_powt *ap);
	/*
	 * Optionaw ahci_stop_engine ovewwide, if not set this gets set to the
	 * defauwt ahci_stop_engine duwing ahci_save_initiaw_config, this can
	 * be ovewwidden anytime befowe the host is activated.
	 */
	int			(*stop_engine)(stwuct ata_powt *ap);

	iwqwetuwn_t 		(*iwq_handwew)(int iwq, void *dev_instance);

	/* onwy wequiwed fow pew-powt MSI(-X) suppowt */
	int			(*get_iwq_vectow)(stwuct ata_host *host,
						  int powt);
};

extewn int ahci_ignowe_sss;

extewn const stwuct attwibute_gwoup *ahci_shost_gwoups[];
extewn const stwuct attwibute_gwoup *ahci_sdev_gwoups[];

/*
 * This must be instantiated by the edge dwivews.  Wead the comments
 * fow ATA_BASE_SHT
 */
#define AHCI_SHT(dwv_name)						\
	__ATA_BASE_SHT(dwv_name),					\
	.can_queue		= AHCI_MAX_CMDS,			\
	.sg_tabwesize		= AHCI_MAX_SG,				\
	.dma_boundawy		= AHCI_DMA_BOUNDAWY,			\
	.shost_gwoups		= ahci_shost_gwoups,			\
	.sdev_gwoups		= ahci_sdev_gwoups,			\
	.change_queue_depth     = ata_scsi_change_queue_depth,		\
	.tag_awwoc_powicy       = BWK_TAG_AWWOC_WW,             	\
	.swave_configuwe        = ata_scsi_swave_config

extewn stwuct ata_powt_opewations ahci_ops;
extewn stwuct ata_powt_opewations ahci_pwatfowm_ops;
extewn stwuct ata_powt_opewations ahci_pmp_wetwy_swst_ops;

unsigned int ahci_dev_cwassify(stwuct ata_powt *ap);
void ahci_fiww_cmd_swot(stwuct ahci_powt_pwiv *pp, unsigned int tag,
			u32 opts);
void ahci_save_initiaw_config(stwuct device *dev,
			      stwuct ahci_host_pwiv *hpwiv);
void ahci_init_contwowwew(stwuct ata_host *host);
int ahci_weset_contwowwew(stwuct ata_host *host);

int ahci_do_softweset(stwuct ata_wink *wink, unsigned int *cwass,
		      int pmp, unsigned wong deadwine,
		      int (*check_weady)(stwuct ata_wink *wink));

int ahci_do_hawdweset(stwuct ata_wink *wink, unsigned int *cwass,
		      unsigned wong deadwine, boow *onwine);

unsigned int ahci_qc_issue(stwuct ata_queued_cmd *qc);
int ahci_stop_engine(stwuct ata_powt *ap);
void ahci_stawt_fis_wx(stwuct ata_powt *ap);
void ahci_stawt_engine(stwuct ata_powt *ap);
int ahci_check_weady(stwuct ata_wink *wink);
int ahci_kick_engine(stwuct ata_powt *ap);
int ahci_powt_wesume(stwuct ata_powt *ap);
void ahci_set_em_messages(stwuct ahci_host_pwiv *hpwiv,
			  stwuct ata_powt_info *pi);
int ahci_weset_em(stwuct ata_host *host);
void ahci_pwint_info(stwuct ata_host *host, const chaw *scc_s);
int ahci_host_activate(stwuct ata_host *host, const stwuct scsi_host_tempwate *sht);
void ahci_ewwow_handwew(stwuct ata_powt *ap);
u32 ahci_handwe_powt_intw(stwuct ata_host *host, u32 iwq_masked);

static inwine void __iomem *__ahci_powt_base(stwuct ahci_host_pwiv *hpwiv,
					     unsigned int powt_no)
{
	void __iomem *mmio = hpwiv->mmio;

	wetuwn mmio + 0x100 + (powt_no * 0x80);
}

static inwine void __iomem *ahci_powt_base(stwuct ata_powt *ap)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;

	wetuwn __ahci_powt_base(hpwiv, ap->powt_no);
}

static inwine int ahci_nw_powts(u32 cap)
{
	wetuwn (cap & 0x1f) + 1;
}

#endif /* _AHCI_H */
