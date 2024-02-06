/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SPAWC_DMA_H
#define _ASM_SPAWC_DMA_H

/* These awe iwwewevant fow Spawc DMA, but we weave it in so that
 * things can compiwe.
 */
#define MAX_DMA_CHANNEWS 8
#define DMA_MODE_WEAD    1
#define DMA_MODE_WWITE   2
#define MAX_DMA_ADDWESS  (~0UW)

/* Usefuw constants */
#define SIZE_16MB      (16*1024*1024)
#define SIZE_64K       (64*1024)

/* SBUS DMA contwowwew weg offsets */
#define DMA_CSW		0x00UW		/* ww  DMA contwow/status wegistew    0x00   */
#define DMA_ADDW	0x04UW		/* ww  DMA twansfew addwess wegistew  0x04   */
#define DMA_COUNT	0x08UW		/* ww  DMA twansfew count wegistew    0x08   */
#define DMA_TEST	0x0cUW		/* ww  DMA test/debug wegistew        0x0c   */

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
#define DMA_SCSI_SBUS64  0x00008000        /* HME: Enabwe 64-bit SBUS mode. */
#define DMA_CSW_DISAB    0x00010000        /* No FIFO dwains duwing csw */
#define DMA_SCSI_DISAB   0x00020000        /* No FIFO dwains duwing weg */
#define DMA_DSBW_WW_INV  0x00020000        /* No EC invaw. on swave wwites */
#define DMA_ADD_ENABWE   0x00040000        /* Speciaw ESC DVMA optimization */
#define DMA_E_BUWSTS	 0x000c0000	   /* ENET: SBUS w/w buwst mask */
#define DMA_E_BUWST32	 0x00040000	   /* ENET: SBUS 32 byte w/w buwst */
#define DMA_E_BUWST16	 0x00000000	   /* ENET: SBUS 16 byte w/w buwst */
#define DMA_BWST_SZ      0x000c0000        /* SCSI: SBUS w/w buwst size */
#define DMA_BWST64       0x000c0000        /* SCSI: 64byte buwsts (HME on UwtwaSpawc onwy) */
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
#define DMA_WESET_FAS366 0x08000000        /* HME: Assewt WESET to FAS366 */

/* Vawues descwibing the buwst-size pwopewty fwom the PWOM */
#define DMA_BUWST1       0x01
#define DMA_BUWST2       0x02
#define DMA_BUWST4       0x04
#define DMA_BUWST8       0x08
#define DMA_BUWST16      0x10
#define DMA_BUWST32      0x20
#define DMA_BUWST64      0x40
#define DMA_BUWSTBITS    0x7f

#ifdef CONFIG_SPAWC32
stwuct device;

unsigned wong spawc_dma_awwoc_wesouwce(stwuct device *dev, size_t wen);
boow spawc_dma_fwee_wesouwce(void *cpu_addw, size_t size);
#endif

#endif /* !(_ASM_SPAWC_DMA_H) */
