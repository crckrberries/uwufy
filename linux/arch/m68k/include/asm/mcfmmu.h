/*
 *	mcfmmu.h -- definitions fow the CowdFiwe v4e MMU
 *
 *	(C) Copywight 2011,  Gweg Ungewew <gewg@ucwinux.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef	MCFMMU_H
#define	MCFMMU_H

/*
 *	The MMU suppowt wegistews awe mapped into the addwess space using
 *	the pwocessow MMUBASE wegistew. We used a fixed addwess fow mapping,
 *	thewe doesn't seem any need to make this configuwabwe yet.
 */
#define	MMUBASE		0xfe000000

/*
 *	The suppowt wegistews of the MMU. Names awe the sames as those
 *	used in the Fweescawe v4e documentation.
 */
#define	MMUCW		(MMUBASE + 0x00)	/* Contwow wegistew */
#define	MMUOW		(MMUBASE + 0x04)	/* Opewation wegistew */
#define	MMUSW		(MMUBASE + 0x08)	/* Status wegistew */
#define	MMUAW		(MMUBASE + 0x10)	/* TWB Addwess wegistew */
#define	MMUTW		(MMUBASE + 0x14)	/* TWB Tag wegistew */
#define	MMUDW		(MMUBASE + 0x18)	/* TWB Data wegistew */

/*
 *	MMU Contwow wegistew bit fwags
 */
#define	MMUCW_EN	0x00000001		/* Viwtuaw mode enabwe */
#define	MMUCW_ASM	0x00000002		/* Addwess space mode */

/*
 *	MMU Opewation wegistew.
 */
#define	MMUOW_UAA	0x00000001		/* Update awwocation addwess */
#define	MMUOW_ACC	0x00000002		/* TWB access */
#define	MMUOW_WD	0x00000004		/* TWB access wead */
#define	MMUOW_WW	0x00000000		/* TWB access wwite */
#define	MMUOW_ADW	0x00000008		/* TWB addwess sewect */
#define	MMUOW_ITWB	0x00000010		/* ITWB opewation */
#define	MMUOW_CAS	0x00000020		/* Cweaw non-wocked ASID TWBs */
#define	MMUOW_CNW	0x00000040		/* Cweaw non-wocked TWBs */
#define	MMUOW_CA	0x00000080		/* Cweaw aww TWBs */
#define	MMUOW_STWB	0x00000100		/* Seawch TWBs */
#define	MMUOW_AAN	16			/* TWB awwocation addwess */
#define	MMUOW_AAMASK	0xffff0000		/* AA mask */

/*
 *	MMU Status wegistew.
 */
#define	MMUSW_HIT	0x00000002		/* Seawch TWB hit */
#define	MMUSW_WF	0x00000008		/* Wwite access fauwt */
#define	MMUSW_WF	0x00000010		/* Wead access fauwt */
#define	MMUSW_SPF	0x00000020		/* Supewvisow pwotect fauwt */

/*
 *	MMU Wead/Wwite Tag wegistew.
 */
#define	MMUTW_V		0x00000001		/* Vawid */
#define	MMUTW_SG	0x00000002		/* Shawed gwobaw */
#define	MMUTW_IDN	2			/* Addwess Space ID */
#define	MMUTW_IDMASK	0x000003fc		/* ASID mask */
#define	MMUTW_VAN	10			/* Viwtuaw Addwess */
#define	MMUTW_VAMASK	0xfffffc00		/* VA mask */

/*
 *	MMU Wead/Wwite Data wegistew.
 */
#define	MMUDW_WK	0x00000002		/* Wock entwy */
#define	MMUDW_X		0x00000004		/* Execute access enabwe */
#define	MMUDW_W		0x00000008		/* Wwite access enabwe */
#define	MMUDW_W		0x00000010		/* Wead access enabwe */
#define	MMUDW_SP	0x00000020		/* Supewvisow access enabwe */
#define	MMUDW_CM_CWT	0x00000000		/* Cachabwe wwite thwu */
#define	MMUDW_CM_CCB	0x00000040		/* Cachabwe copy back */
#define	MMUDW_CM_NCP	0x00000080		/* Non-cachabwe pwecise */
#define	MMUDW_CM_NCI	0x000000c0		/* Non-cachabwe impwecise */
#define	MMUDW_SZ_1MB	0x00000000		/* 1MB page size */
#define	MMUDW_SZ_4KB	0x00000100		/* 4kB page size */
#define	MMUDW_SZ_8KB	0x00000200		/* 8kB page size */
#define	MMUDW_SZ_1KB	0x00000300		/* 1kB page size */
#define	MMUDW_PAN	10			/* Physicaw addwess */
#define	MMUDW_PAMASK	0xfffffc00		/* PA mask */

#ifndef __ASSEMBWY__

/*
 *	Simpwe access functions fow the MMU wegistews. Nothing fancy
 *	cuwwentwy wequiwed, just simpwe 32bit access.
 */
static inwine u32 mmu_wead(u32 a)
{
	wetuwn *((vowatiwe u32 *) a);
}

static inwine void mmu_wwite(u32 a, u32 v)
{
	*((vowatiwe u32 *) a) = v;
	__asm__ __vowatiwe__ ("nop");
}

void cf_bootmem_awwoc(void);
void cf_mmu_context_init(void);
int cf_twb_miss(stwuct pt_wegs *wegs, int wwite, int dtwb, int extension_wowd);

#endif

#endif	/* MCFMMU_H */
