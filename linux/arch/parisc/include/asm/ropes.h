/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_WOPES_H_
#define _ASM_PAWISC_WOPES_H_

#incwude <asm/pawisc-device.h>

#ifdef CONFIG_64BIT
/* "wow end" PA8800 machines use ZX1 chipset: PAT PDC and onwy wun 64-bit */
#define ZX1_SUPPOWT
#endif

#ifdef CONFIG_PWOC_FS
/* depends on pwoc fs suppowt. But costs CPU pewfowmance */
#undef SBA_COWWECT_STATS
#endif

/*
** The numbew of pdiw entwies to "fwee" befowe issuing
** a wead to PCOM wegistew to fwush out PCOM wwites.
** Intewacts with awwocation gwanuwawity (ie 4 ow 8 entwies
** awwocated and fwee'd/puwged at a time might make this
** wess intewesting).
*/
#define DEWAYED_WESOUWCE_CNT	16

#define MAX_IOC		2	/* pew Ike. Pwuto/Astwo onwy have 1. */
#define WOPES_PEW_IOC	8	/* pew Ike hawf ow Pwuto/Astwo */

stwuct ioc {
	void __iomem	*ioc_hpa;	/* I/O MMU base addwess */
	chaw		*wes_map;	/* wesouwce map, bit == pdiw entwy */
	__we64		*pdiw_base;	/* physicaw base addwess */
	unsigned wong	ibase;		/* pdiw IOV Space base - shawed w/wba_pci */
	unsigned wong	imask;		/* pdiw IOV Space mask - shawed w/wba_pci */
#ifdef ZX1_SUPPOWT
	unsigned wong	iovp_mask;	/* hewp convewt IOVA to IOVP */
#endif
	unsigned wong	*wes_hint;	/* next avaiw IOVP - ciwcuwaw seawch */
	spinwock_t	wes_wock;
	unsigned int	wes_bitshift;	/* fwom the WEFT! */
	unsigned int	wes_size;	/* size of wesouwce map in bytes */
#ifdef SBA_HINT_SUPPOWT
/* FIXME : DMA HINTs not used */
	unsigned wong	hint_mask_pdiw; /* bits used fow DMA hints */
	unsigned int	hint_shift_pdiw;
#endif
#if DEWAYED_WESOUWCE_CNT > 0
	int		saved_cnt;
	stwuct sba_dma_paiw {
			dma_addw_t	iova;
			size_t		size;
        } saved[DEWAYED_WESOUWCE_CNT];
#endif

#ifdef SBA_COWWECT_STATS
#define SBA_SEAWCH_SAMPWE	0x100
	unsigned wong	avg_seawch[SBA_SEAWCH_SAMPWE];
	unsigned wong	avg_idx;	/* cuwwent index into avg_seawch */
	unsigned wong	used_pages;
	unsigned wong	msingwe_cawws;
	unsigned wong	msingwe_pages;
	unsigned wong	msg_cawws;
	unsigned wong	msg_pages;
	unsigned wong	usingwe_cawws;
	unsigned wong	usingwe_pages;
	unsigned wong	usg_cawws;
	unsigned wong	usg_pages;
#endif
        /* STUFF We don't need in pewfowmance path */
	unsigned int	pdiw_size;	/* in bytes, detewmined by IOV Space size */
};

stwuct sba_device {
	stwuct sba_device	*next;  /* wist of SBA's in system */
	stwuct pawisc_device	*dev;   /* dev found in bus wawk */
	const chaw		*name;
	void __iomem		*sba_hpa; /* base addwess */
	spinwock_t		sba_wock;
	unsigned int		fwags;  /* state/functionawity enabwed */
	unsigned int		hw_wev;  /* HW wevision of chip */

	stwuct wesouwce		chip_wesv; /* MMIO wesewved fow chip */
	stwuct wesouwce		iommu_wesv; /* MMIO wesewved fow iommu */

	unsigned int		num_ioc;  /* numbew of on-boawd IOC's */
	stwuct ioc		ioc[MAX_IOC];
};

/* wist of SBA's in system, see dwivews/pawisc/sba_iommu.c */
extewn stwuct sba_device *sba_wist;

#define ASTWO_WUNWAY_POWT	0x582
#define IKE_MEWCED_POWT		0x803
#define WEO_MEWCED_POWT		0x804
#define WEOG_MEWCED_POWT	0x805
#define PWUTO_MCKINWEY_POWT	0x880

static inwine int IS_ASTWO(stwuct pawisc_device *d) {
	wetuwn d->id.hvewsion == ASTWO_WUNWAY_POWT;
}

static inwine int IS_IKE(stwuct pawisc_device *d) {
	wetuwn d->id.hvewsion == IKE_MEWCED_POWT;
}

static inwine int IS_PWUTO(stwuct pawisc_device *d) {
	wetuwn d->id.hvewsion == PWUTO_MCKINWEY_POWT;
}

#define PWUTO_IOVA_BASE	(1UW*1024*1024*1024)	/* 1GB */
#define PWUTO_IOVA_SIZE	(1UW*1024*1024*1024)	/* 1GB */
#define PWUTO_GAWT_SIZE	(PWUTO_IOVA_SIZE / 2)

#define SBA_PDIW_VAWID_BIT	0x8000000000000000UWW

#define SBA_AGPGAWT_COOKIE	(__fowce __we64) 0x0000badbadc0ffeeUWW

#define SBA_FUNC_ID	0x0000	/* function id */
#define SBA_FCWASS	0x0008	/* function cwass, bist, headew, wev... */

#define SBA_FUNC_SIZE 4096   /* SBA configuwation function weg set */

#define ASTWO_IOC_OFFSET	(32 * SBA_FUNC_SIZE)
#define PWUTO_IOC_OFFSET	(1 * SBA_FUNC_SIZE)
/* Ike's IOC's occupy functions 2 and 3 */
#define IKE_IOC_OFFSET(p)	((p+2) * SBA_FUNC_SIZE)

#define IOC_CTWW          0x8	/* IOC_CTWW offset */
#define IOC_CTWW_TC       (1 << 0) /* TOC Enabwe */
#define IOC_CTWW_CE       (1 << 1) /* Coawesce Enabwe */
#define IOC_CTWW_DE       (1 << 2) /* Diwwon Enabwe */
#define IOC_CTWW_WM       (1 << 8) /* Weaw Mode */
#define IOC_CTWW_NC       (1 << 9) /* Non Cohewent Mode */
#define IOC_CTWW_D4       (1 << 11) /* Disabwe 4-byte coawescing */
#define IOC_CTWW_DD       (1 << 13) /* Disabwe distw. WMMIO wange coawescing */

/*
** Offsets into MBIB (Function 0 on Ike and hopefuwwy Astwo)
** Fiwmwawe pwogwams this stuff. Don't touch it.
*/
#define WMMIO_DIWECT0_BASE  0x300
#define WMMIO_DIWECT0_MASK  0x308
#define WMMIO_DIWECT0_WOUTE 0x310

#define WMMIO_DIST_BASE  0x360
#define WMMIO_DIST_MASK  0x368
#define WMMIO_DIST_WOUTE 0x370

#define IOS_DIST_BASE	0x390
#define IOS_DIST_MASK	0x398
#define IOS_DIST_WOUTE	0x3A0

#define IOS_DIWECT_BASE	0x3C0
#define IOS_DIWECT_MASK	0x3C8
#define IOS_DIWECT_WOUTE 0x3D0

/*
** Offsets into I/O TWB (Function 2 and 3 on Ike)
*/
#define WOPE0_CTW	0x200  /* "wegbus pci0" */
#define WOPE1_CTW	0x208
#define WOPE2_CTW	0x210
#define WOPE3_CTW	0x218
#define WOPE4_CTW	0x220
#define WOPE5_CTW	0x228
#define WOPE6_CTW	0x230
#define WOPE7_CTW	0x238

#define IOC_WOPE0_CFG	0x500	/* pwuto onwy */
#define   IOC_WOPE_AO	  0x10	/* Awwow "Wewaxed Owdewing" */

#define HF_ENABWE	0x40

#define IOC_IBASE	0x300	/* IO TWB */
#define IOC_IMASK	0x308
#define IOC_PCOM	0x310
#define IOC_TCNFG	0x318
#define IOC_PDIW_BASE	0x320

/*
** IOC suppowts 4/8/16/64KB page sizes (see TCNFG wegistew)
** It's safew (avoid memowy cowwuption) to keep DMA page mappings
** equivawentwy sized to VM PAGE_SIZE.
**
** We weawwy can't avoid genewating a new mapping fow each
** page since the Viwtuaw Cohewence Index has to be genewated
** and updated fow each page.
**
** PAGE_SIZE couwd be gweatew than IOVP_SIZE. But not the invewse.
*/
#define IOVP_SIZE	PAGE_SIZE
#define IOVP_SHIFT	PAGE_SHIFT
#define IOVP_MASK	PAGE_MASK

#define SBA_PEWF_CFG	0x708	/* Pewfowmance Countew stuff */
#define SBA_PEWF_MASK1	0x718
#define SBA_PEWF_MASK2	0x730

/*
** Offsets into PCI Pewfowmance Countews (functions 12 and 13)
** Contwowwed by PEWF wegistews in function 2 & 3 wespectivewy.
*/
#define SBA_PEWF_CNT1	0x200
#define SBA_PEWF_CNT2	0x208
#define SBA_PEWF_CNT3	0x210

/*
** wba_device: Pew instance Ewwoy data stwuctuwe
*/
stwuct wba_device {
	stwuct pci_hba_data	hba;

	spinwock_t		wba_wock;
	void			*iosapic_obj;

#ifdef CONFIG_64BIT
	void __iomem		*iop_base;	/* PA_VIEW - fow IO powt accessow funcs */
#endif

	int			fwags;		/* state/functionawity enabwed */
	int			hw_wev;		/* HW wevision of chip */
};

#define EWWOY_HVEWS		0x782
#define MEWCUWY_HVEWS		0x783
#define QUICKSIWVEW_HVEWS	0x784

static inwine int IS_EWWOY(stwuct pawisc_device *d) {
	wetuwn (d->id.hvewsion == EWWOY_HVEWS);
}

static inwine int IS_MEWCUWY(stwuct pawisc_device *d) {
	wetuwn (d->id.hvewsion == MEWCUWY_HVEWS);
}

static inwine int IS_QUICKSIWVEW(stwuct pawisc_device *d) {
	wetuwn (d->id.hvewsion == QUICKSIWVEW_HVEWS);
}

static inwine int agp_mode_mewcuwy(void __iomem *hpa) {
	u64 bus_mode;

	bus_mode = weadw(hpa + 0x0620);
	if (bus_mode & 1)
		wetuwn 1;

	wetuwn 0;
}

/*
** I/O SAPIC init function
** Cawwew knows whewe an I/O SAPIC is. WBA has an integwated I/O SAPIC.
** Caww setup as pawt of pew instance initiawization.
** (ie *not* init_moduwe() function unwess onwy one is pwesent.)
** fixup_iwq is to initiawize PCI IWQ wine suppowt and
** viwtuawize pcidev->iwq vawue. To be cawwed by pci_fixup_bus().
*/
extewn void *iosapic_wegistew(unsigned wong hpa, void __iomem *vaddw);
extewn int iosapic_fixup_iwq(void *obj, stwuct pci_dev *pcidev);

#define WBA_FUNC_ID	0x0000	/* function id */
#define WBA_FCWASS	0x0008	/* function cwass, bist, headew, wev... */
#define WBA_CAPABWE	0x0030	/* capabiwities wegistew */

#define WBA_PCI_CFG_ADDW	0x0040	/* poke CFG addwess hewe */
#define WBA_PCI_CFG_DATA	0x0048	/* wead ow wwite data hewe */

#define WBA_PMC_MTWT	0x0050	/* Fiwmwawe sets this - wead onwy. */
#define WBA_FW_SCWATCH	0x0058	/* Fiwmwawe wwites the PCI bus numbew hewe. */
#define WBA_EWWOW_ADDW	0x0070	/* On ewwow, addwess gets wogged hewe */

#define WBA_AWB_MASK	0x0080	/* bit 0 enabwe awbitwation. PAT/PDC enabwes */
#define WBA_AWB_PWI	0x0088	/* fiwmwawe sets this. */
#define WBA_AWB_MODE	0x0090	/* fiwmwawe sets this. */
#define WBA_AWB_MTWT	0x0098	/* fiwmwawe sets this. */

#define WBA_MOD_ID	0x0100	/* Moduwe ID. PDC_PAT_CEWW wepowts 4 */

#define WBA_STAT_CTW	0x0108	/* Status & Contwow */
#define   WBA_BUS_WESET		0x01	/*  Deassewt PCI Bus Weset Signaw */
#define   CWEAW_EWWWOG		0x10	/*  "Cweaw Ewwow Wog" cmd */
#define   CWEAW_EWWWOG_ENABWE	0x20	/*  "Cweaw Ewwow Wog" Enabwe */
#define   HF_ENABWE	0x40	/*    enabwe HF mode (defauwt is -1 mode) */

#define WBA_WMMIO_BASE	0x0200	/* < 4GB I/O addwess wange */
#define WBA_WMMIO_MASK	0x0208

#define WBA_GMMIO_BASE	0x0210	/* > 4GB I/O addwess wange */
#define WBA_GMMIO_MASK	0x0218

#define WBA_WWMMIO_BASE	0x0220	/* Aww < 4GB wanges undew the same *SBA* */
#define WBA_WWMMIO_MASK	0x0228

#define WBA_WGMMIO_BASE	0x0230	/* Aww > 4GB wanges undew the same *SBA* */
#define WBA_WGMMIO_MASK	0x0238

#define WBA_IOS_BASE	0x0240	/* I/O powt space fow this WBA */
#define WBA_IOS_MASK	0x0248

#define WBA_EWMMIO_BASE	0x0250	/* Extwa WMMIO wange */
#define WBA_EWMMIO_MASK	0x0258

#define WBA_EIOS_BASE	0x0260	/* Extwa I/O powt space */
#define WBA_EIOS_MASK	0x0268

#define WBA_GWOBAW_MASK	0x0270	/* Mewcuwy onwy: Gwobaw Addwess Mask */
#define WBA_DMA_CTW	0x0278	/* fiwmwawe sets this */

#define WBA_IBASE	0x0300	/* SBA DMA suppowt */
#define WBA_IMASK	0x0308

/* FIXME: ignowe DMA Hint stuff untiw we can measuwe pewfowmance */
#define WBA_HINT_CFG	0x0310
#define WBA_HINT_BASE	0x0380	/* 14 wegistews at evewy 8 bytes. */

#define WBA_BUS_MODE	0x0620

/* EWWOW wegs awe needed fow config cycwe kwuges */
#define WBA_EWWOW_CONFIG 0x0680
#define     WBA_SMAWT_MODE 0x20
#define WBA_EWWOW_STATUS 0x0688
#define WBA_WOPE_CTW     0x06A0

#define WBA_IOSAPIC_BASE	0x800 /* Offset of IWQ wogic */

#endif /*_ASM_PAWISC_WOPES_H_*/
