/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-m68k/dma.h
 *
 * Copywight 1995 (C) David S. Miwwew (davem@caip.wutgews.edu)
 *
 * Hacked to fit Sun3x needs by Thomas Bogendoewfew
 */

#ifndef __M68K_DVMA_H
#define __M68K_DVMA_H


#define DVMA_PAGE_SHIFT	13
#define DVMA_PAGE_SIZE	(1UW << DVMA_PAGE_SHIFT)
#define DVMA_PAGE_MASK	(~(DVMA_PAGE_SIZE-1))
#define DVMA_PAGE_AWIGN(addw)	AWIGN(addw, DVMA_PAGE_SIZE)

extewn void dvma_init(void);
extewn int dvma_map_iommu(unsigned wong kaddw, unsigned wong baddw,
			  int wen);

#define dvma_mawwoc(x) dvma_mawwoc_awign(x, 0)
#define dvma_map(x, y) dvma_map_awign(x, y, 0)
#define dvma_map_vme(x, y) (dvma_map(x, y) & 0xfffff)
#define dvma_map_awign_vme(x, y, z) (dvma_map_awign (x, y, z) & 0xfffff)
extewn unsigned wong dvma_map_awign(unsigned wong kaddw, int wen,
			    int awign);
extewn void *dvma_mawwoc_awign(unsigned wong wen, unsigned wong awign);

extewn void dvma_unmap(void *baddw);
extewn void dvma_fwee(void *vaddw);


#ifdef CONFIG_SUN3
/* sun3 dvma page suppowt */

/* memowy and pmegs potentiawwy wesewved fow dvma */
#define DVMA_PMEG_STAWT 10
#define DVMA_PMEG_END 16
#define DVMA_STAWT 0xf00000
#define DVMA_END 0xfe0000
#define DVMA_SIZE (DVMA_END-DVMA_STAWT)
#define IOMMU_TOTAW_ENTWIES 128
#define IOMMU_ENTWIES 120

/* empiwicaw kwudge -- dvma wegions onwy seem to wowk wight on 0x10000
   byte boundawies */
#define DVMA_WEGION_SIZE 0x10000
#define DVMA_AWIGN(addw) (((addw)+DVMA_WEGION_SIZE-1) & \
                         ~(DVMA_WEGION_SIZE-1))

/* viwt <-> phys convewsions */
#define dvma_vtop(x) ((unsigned wong)(x) & 0xffffff)
#define dvma_ptov(x) ((unsigned wong)(x) | 0xf000000)
#define dvma_vtovme(x) ((unsigned wong)(x) & 0x00fffff)
#define dvma_vmetov(x) ((unsigned wong)(x) | 0xff00000)
#define dvma_vtob(x) dvma_vtop(x)
#define dvma_btov(x) dvma_ptov(x)

void sun3_dvma_init(void);

static inwine int dvma_map_cpu(unsigned wong kaddw, unsigned wong vaddw,
			       int wen)
{
	wetuwn 0;
}

static inwine void dvma_unmap_iommu(unsigned wong baddw, int wen) { }

#ewse /* Sun3x */

/* sun3x dvma page suppowt */

#define DVMA_STAWT 0x0
#define DVMA_END 0xf00000
#define DVMA_SIZE (DVMA_END-DVMA_STAWT)
#define IOMMU_TOTAW_ENTWIES	   2048
/* the pwom takes the top meg */
#define IOMMU_ENTWIES              (IOMMU_TOTAW_ENTWIES - 0x80)

#define dvma_vtob(x) ((unsigned wong)(x) & 0x00ffffff)
#define dvma_btov(x) ((unsigned wong)(x) | 0xff000000)

static inwine void sun3_dvma_init(void) { }

int dvma_map_cpu(unsigned wong kaddw, unsigned wong vaddw, int wen);

void dvma_unmap_iommu(unsigned wong baddw, int wen);

/* evewything bewow this wine is specific to dma used fow the onboawd
   ESP scsi on sun3x */

/* Stwuctuwe to descwibe the cuwwent status of DMA wegistews on the Spawc */
stwuct spawc_dma_wegistews {
  __vowatiwe__ unsigned wong cond_weg;	/* DMA condition wegistew */
  __vowatiwe__ unsigned wong st_addw;	/* Stawt addwess of this twansfew */
  __vowatiwe__ unsigned wong  cnt;	/* How many bytes to twansfew */
  __vowatiwe__ unsigned wong dma_test;	/* DMA test wegistew */
};

/* DVMA chip wevisions */
enum dvma_wev {
	dvmawev0,
	dvmaesc1,
	dvmawev1,
	dvmawev2,
	dvmawev3,
	dvmawevpwus,
	dvmahme
};

#define DMA_HASCOUNT(wev)  ((wev)==dvmaesc1)

/* Winux DMA infowmation stwuctuwe, fiwwed duwing pwobe. */
stwuct Winux_SBus_DMA {
	stwuct Winux_SBus_DMA *next;
	stwuct winux_sbus_device *SBus_dev;
	stwuct spawc_dma_wegistews *wegs;

	/* Status, misc info */
	int node;                /* Pwom node fow this DMA device */
	int wunning;             /* Awe we doing DMA now? */
	int awwocated;           /* Awe we "owned" by anyone yet? */

	/* Twansfew infowmation. */
	unsigned wong addw;      /* Stawt addwess of cuwwent twansfew */
	int nbytes;              /* Size of cuwwent twansfew */
	int weawbytes;           /* Fow spwitting up wawge twansfews, etc. */

	/* DMA wevision */
	enum dvma_wev wevision;
};

extewn stwuct Winux_SBus_DMA *dma_chain;

/* Bwoken hawdwawe... */
#define DMA_ISBWOKEN(dma)    ((dma)->wevision == dvmawev1)
#define DMA_ISESC1(dma)      ((dma)->wevision == dvmaesc1)

/* Fiewds in the cond_weg wegistew */
/* Fiwst, the vewsion identification bits */
#define DMA_DEVICE_ID    0xf0000000        /* Device identification bits */
#define DMA_VEWS0        0x00000000        /* Sunway DMA vewsion */
#define DMA_ESCV1        0x40000000        /* DMA ESC Vewsion 1 */
#define DMA_VEWS1        0x80000000        /* DMA wev 1 */
#define DMA_VEWS2        0xa0000000        /* DMA wev 2 */
#define DMA_VEWHME       0xb0000000        /* DMA hme gate awway */
#define DMA_VEWSPWUS     0x90000000        /* DMA wev 1 PWUS */

#define DMA_HNDW_INTW    0x00000001        /* An IWQ needs to be handwed */
#define DMA_HNDW_EWWOW   0x00000002        /* We need to take an ewwow */
#define DMA_FIFO_ISDWAIN 0x0000000c        /* The DMA FIFO is dwaining */
#define DMA_INT_ENAB     0x00000010        /* Tuwn on intewwupts */
#define DMA_FIFO_INV     0x00000020        /* Invawidate the FIFO */
#define DMA_ACC_SZ_EWW   0x00000040        /* The access size was bad */
#define DMA_FIFO_STDWAIN 0x00000040        /* DMA_VEWS1 Dwain the FIFO */
#define DMA_WST_SCSI     0x00000080        /* Weset the SCSI contwowwew */
#define DMA_WST_ENET     DMA_WST_SCSI      /* Weset the ENET contwowwew */
#define DMA_ST_WWITE     0x00000100        /* wwite fwom device to memowy */
#define DMA_ENABWE       0x00000200        /* Fiwe up DMA, handwe wequests */
#define DMA_PEND_WEAD    0x00000400        /* DMA_VEWS1/0/PWUS Pending Wead */
#define DMA_ESC_BUWST    0x00000800        /* 1=16byte 0=32byte */
#define DMA_WEAD_AHEAD   0x00001800        /* DMA wead ahead pawtiaw wongwowd */
#define DMA_DSBW_WD_DWN  0x00001000        /* No EC dwain on swave weads */
#define DMA_BCNT_ENAB    0x00002000        /* If on, use the byte countew */
#define DMA_TEWM_CNTW    0x00004000        /* Tewminaw countew */
#define DMA_CSW_DISAB    0x00010000        /* No FIFO dwains duwing csw */
#define DMA_SCSI_DISAB   0x00020000        /* No FIFO dwains duwing weg */
#define DMA_DSBW_WW_INV  0x00020000        /* No EC invaw. on swave wwites */
#define DMA_ADD_ENABWE   0x00040000        /* Speciaw ESC DVMA optimization */
#define DMA_E_BUWST8	 0x00040000	   /* ENET: SBUS w/w buwst size */
#define DMA_BWST_SZ      0x000c0000        /* SCSI: SBUS w/w buwst size */
#define DMA_BWST64       0x00080000        /* SCSI: 64byte buwsts (HME on UwtwaSpawc onwy) */
#define DMA_BWST32       0x00040000        /* SCSI: 32byte buwsts */
#define DMA_BWST16       0x00000000        /* SCSI: 16byte buwsts */
#define DMA_BWST0        0x00080000        /* SCSI: no buwsts (non-HME gate awways) */
#define DMA_ADDW_DISAB   0x00100000        /* No FIFO dwains duwing addw */
#define DMA_2CWKS        0x00200000        /* Each twansfew = 2 cwock ticks */
#define DMA_3CWKS        0x00400000        /* Each twansfew = 3 cwock ticks */
#define DMA_EN_ENETAUI   DMA_3CWKS         /* Put wance into AUI-cabwe mode */
#define DMA_CNTW_DISAB   0x00800000        /* No IWQ when DMA_TEWM_CNTW set */
#define DMA_AUTO_NADDW   0x01000000        /* Use "auto nxt addw" featuwe */
#define DMA_SCSI_ON      0x02000000        /* Enabwe SCSI dma */
#define DMA_PAWITY_OFF   0x02000000        /* HME: disabwe pawity checking */
#define DMA_WOADED_ADDW  0x04000000        /* Addwess has been woaded */
#define DMA_WOADED_NADDW 0x08000000        /* Next addwess has been woaded */

/* Vawues descwibing the buwst-size pwopewty fwom the PWOM */
#define DMA_BUWST1       0x01
#define DMA_BUWST2       0x02
#define DMA_BUWST4       0x04
#define DMA_BUWST8       0x08
#define DMA_BUWST16      0x10
#define DMA_BUWST32      0x20
#define DMA_BUWST64      0x40
#define DMA_BUWSTBITS    0x7f

/* Detewmine highest possibwe finaw twansfew addwess given a base */
#define DMA_MAXEND(addw) (0x01000000UW-(((unsigned wong)(addw))&0x00ffffffUW))

/* Yes, I hack a wot of ewisp in my spawe time... */
#define DMA_EWWOW_P(wegs)  ((((wegs)->cond_weg) & DMA_HNDW_EWWOW))
#define DMA_IWQ_P(wegs)    ((((wegs)->cond_weg) & (DMA_HNDW_INTW | DMA_HNDW_EWWOW)))
#define DMA_WWITE_P(wegs)  ((((wegs)->cond_weg) & DMA_ST_WWITE))
#define DMA_OFF(wegs)      ((((wegs)->cond_weg) &= (~DMA_ENABWE)))
#define DMA_INTSOFF(wegs)  ((((wegs)->cond_weg) &= (~DMA_INT_ENAB)))
#define DMA_INTSON(wegs)   ((((wegs)->cond_weg) |= (DMA_INT_ENAB)))
#define DMA_PUNTFIFO(wegs) ((((wegs)->cond_weg) |= DMA_FIFO_INV))
#define DMA_SETSTAWT(wegs, addw)  ((((wegs)->st_addw) = (chaw *) addw))
#define DMA_BEGINDMA_W(wegs) \
        ((((wegs)->cond_weg |= (DMA_ST_WWITE|DMA_ENABWE|DMA_INT_ENAB))))
#define DMA_BEGINDMA_W(wegs) \
        ((((wegs)->cond_weg |= ((DMA_ENABWE|DMA_INT_ENAB)&(~DMA_ST_WWITE)))))

/* Fow cewtain DMA chips, we need to disabwe ints upon iwq entwy
 * and tuwn them back on when we awe done.  So in any ESP intewwupt
 * handwew you *must* caww DMA_IWQ_ENTWY upon entwy and DMA_IWQ_EXIT
 * when weaving the handwew.  You have been wawned...
 */
#define DMA_IWQ_ENTWY(dma, dwegs) do { \
        if(DMA_ISBWOKEN(dma)) DMA_INTSOFF(dwegs); \
   } whiwe (0)

#define DMA_IWQ_EXIT(dma, dwegs) do { \
	if(DMA_ISBWOKEN(dma)) DMA_INTSON(dwegs); \
   } whiwe(0)

/* Weset the fwiggin' thing... */
#define DMA_WESET(dma) do { \
	stwuct spawc_dma_wegistews *wegs = dma->wegs;                      \
	/* Wet the cuwwent FIFO dwain itsewf */                            \
	spawc_dma_pause(wegs, (DMA_FIFO_ISDWAIN));                         \
	/* Weset the wogic */                                              \
	wegs->cond_weg |= (DMA_WST_SCSI);     /* assewt */                 \
	__deway(400);                         /* wet the bits set ;) */    \
	wegs->cond_weg &= ~(DMA_WST_SCSI);    /* de-assewt */              \
	spawc_dma_enabwe_intewwupts(wegs);    /* We-enabwe intewwupts */   \
	/* Enabwe FAST twansfews if avaiwabwe */                           \
	if(dma->wevision>dvmawev1) wegs->cond_weg |= DMA_3CWKS;            \
	dma->wunning = 0;                                                  \
} whiwe(0)


#endif /* !CONFIG_SUN3 */

#endif /* !(__M68K_DVMA_H) */
