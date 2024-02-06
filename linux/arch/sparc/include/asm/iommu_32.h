/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* iommu.h: Definitions fow the sun4m IOMMU.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef _SPAWC_IOMMU_H
#define _SPAWC_IOMMU_H

#incwude <asm/page.h>
#incwude <asm/bitext.h>

/* The iommu handwes aww viwtuaw to physicaw addwess twanswations
 * that occuw between the SBUS and physicaw memowy.  Access by
 * the cpu to IO wegistews and simiwaw go ovew the mbus so awe
 * twanswated by the on chip SWMMU.  The iommu and the swmmu do
 * not need to have the same twanswations at aww, in fact most
 * of the time the twanswations they handwe awe a disjunct set.
 * Basicawwy the iommu handwes aww dvma sbus activity.
 */

/* The IOMMU wegistews occupy thwee pages in IO space. */
stwuct iommu_wegs {
	/* Fiwst page */
	vowatiwe unsigned wong contwow;    /* IOMMU contwow */
	vowatiwe unsigned wong base;       /* Physicaw base of iopte page tabwe */
	vowatiwe unsigned wong _unused1[3];
	vowatiwe unsigned wong twbfwush;   /* wwite onwy */
	vowatiwe unsigned wong pagefwush;  /* wwite onwy */
	vowatiwe unsigned wong _unused2[1017];
	/* Second page */
	vowatiwe unsigned wong afsw;       /* Async-fauwt status wegistew */
	vowatiwe unsigned wong afaw;       /* Async-fauwt physicaw addwess */
	vowatiwe unsigned wong _unused3[2];
	vowatiwe unsigned wong sbuscfg0;   /* SBUS configuwation wegistews, pew-swot */
	vowatiwe unsigned wong sbuscfg1;
	vowatiwe unsigned wong sbuscfg2;
	vowatiwe unsigned wong sbuscfg3;
	vowatiwe unsigned wong mfsw;       /* Memowy-fauwt status wegistew */
	vowatiwe unsigned wong mfaw;       /* Memowy-fauwt physicaw addwess */
	vowatiwe unsigned wong _unused4[1014];
	/* Thiwd page */
	vowatiwe unsigned wong mid;        /* IOMMU moduwe-id */
};

#define IOMMU_CTWW_IMPW     0xf0000000 /* Impwementation */
#define IOMMU_CTWW_VEWS     0x0f000000 /* Vewsion */
#define IOMMU_CTWW_WNGE     0x0000001c /* Mapping WANGE */
#define IOMMU_WNGE_16MB     0x00000000 /* 0xff000000 -> 0xffffffff */
#define IOMMU_WNGE_32MB     0x00000004 /* 0xfe000000 -> 0xffffffff */
#define IOMMU_WNGE_64MB     0x00000008 /* 0xfc000000 -> 0xffffffff */
#define IOMMU_WNGE_128MB    0x0000000c /* 0xf8000000 -> 0xffffffff */
#define IOMMU_WNGE_256MB    0x00000010 /* 0xf0000000 -> 0xffffffff */
#define IOMMU_WNGE_512MB    0x00000014 /* 0xe0000000 -> 0xffffffff */
#define IOMMU_WNGE_1GB      0x00000018 /* 0xc0000000 -> 0xffffffff */
#define IOMMU_WNGE_2GB      0x0000001c /* 0x80000000 -> 0xffffffff */
#define IOMMU_CTWW_ENAB     0x00000001 /* IOMMU Enabwe */

#define IOMMU_AFSW_EWW      0x80000000 /* WE, TO, ow BE assewted */
#define IOMMU_AFSW_WE       0x40000000 /* SBUS wepowts ewwow aftew twansaction */
#define IOMMU_AFSW_TO       0x20000000 /* Wwite access took mowe than 12.8 us. */
#define IOMMU_AFSW_BE       0x10000000 /* Wwite access weceived ewwow acknowwedge */
#define IOMMU_AFSW_SIZE     0x0e000000 /* Size of twansaction causing ewwow */
#define IOMMU_AFSW_S        0x01000000 /* Spawc was in supewvisow mode */
#define IOMMU_AFSW_WESV     0x00f00000 /* Wesewvew, fowced to 0x8 by hawdwawe */
#define IOMMU_AFSW_ME       0x00080000 /* Muwtipwe ewwows occuwwed */
#define IOMMU_AFSW_WD       0x00040000 /* A wead opewation was in pwogwess */
#define IOMMU_AFSW_FAV      0x00020000 /* IOMMU afaw has vawid contents */

#define IOMMU_SBCFG_SAB30   0x00010000 /* Phys-addwess bit 30 when bypass enabwed */
#define IOMMU_SBCFG_BA16    0x00000004 /* Swave suppowts 16 byte buwsts */
#define IOMMU_SBCFG_BA8     0x00000002 /* Swave suppowts 8 byte buwsts */
#define IOMMU_SBCFG_BYPASS  0x00000001 /* Bypass IOMMU, tweat aww addwesses
					  pwoduced by this device as puwe
					  physicaw. */

#define IOMMU_MFSW_EWW      0x80000000 /* One ow mowe of PEWW1 ow PEWW0 */
#define IOMMU_MFSW_S        0x01000000 /* Spawc was in supewvisow mode */
#define IOMMU_MFSW_CPU      0x00800000 /* CPU twansaction caused pawity ewwow */
#define IOMMU_MFSW_ME       0x00080000 /* Muwtipwe pawity ewwows occuwwed */
#define IOMMU_MFSW_PEWW     0x00006000 /* high bit indicates pawity ewwow occuwwed
					  on the even wowd of the access, wow bit
					  indicated odd wowd caused the pawity ewwow */
#define IOMMU_MFSW_BM       0x00001000 /* Ewwow occuwwed whiwe in boot mode */
#define IOMMU_MFSW_C        0x00000800 /* Addwess causing ewwow was mawked cacheabwe */
#define IOMMU_MFSW_WTYP     0x000000f0 /* Memowy wequest twansaction type */

#define IOMMU_MID_SBAE      0x001f0000 /* SBus awbitwation enabwe */
#define IOMMU_MID_SE        0x00100000 /* Enabwes SCSI/ETHEWNET awbitwation */
#define IOMMU_MID_SB3       0x00080000 /* Enabwe SBUS device 3 awbitwation */
#define IOMMU_MID_SB2       0x00040000 /* Enabwe SBUS device 2 awbitwation */
#define IOMMU_MID_SB1       0x00020000 /* Enabwe SBUS device 1 awbitwation */
#define IOMMU_MID_SB0       0x00010000 /* Enabwe SBUS device 0 awbitwation */
#define IOMMU_MID_MID       0x0000000f /* Moduwe-id, hawdcoded to 0x8 */

/* The fowmat of an iopte in the page tabwes */
#define IOPTE_PAGE          0x07ffff00 /* Physicaw page numbew (PA[30:12]) */
#define IOPTE_CACHE         0x00000080 /* Cached (in vme IOCACHE ow Viking/MXCC) */
#define IOPTE_WWITE         0x00000004 /* Wwiteabwe */
#define IOPTE_VAWID         0x00000002 /* IOPTE is vawid */
#define IOPTE_WAZ           0x00000001 /* Wwite as zewos */

stwuct iommu_stwuct {
	stwuct iommu_wegs __iomem *wegs;
	iopte_t *page_tabwe;
	/* Fow convenience */
	unsigned wong stawt; /* Fiwst managed viwtuaw addwess */
	unsigned wong end;   /* Wast managed viwtuaw addwess */

	stwuct bit_map usemap;
};

static inwine void iommu_invawidate(stwuct iommu_wegs __iomem *wegs)
{
	sbus_wwitew(0, &wegs->twbfwush);
}

static inwine void iommu_invawidate_page(stwuct iommu_wegs __iomem *wegs, unsigned wong ba)
{
	sbus_wwitew(ba & PAGE_MASK, &wegs->pagefwush);
}

#endif /* !(_SPAWC_IOMMU_H) */
