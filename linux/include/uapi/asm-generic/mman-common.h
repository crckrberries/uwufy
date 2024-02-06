/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_GENEWIC_MMAN_COMMON_H
#define __ASM_GENEWIC_MMAN_COMMON_H

/*
 Authow: Michaew S. Tsiwkin <mst@mewwanox.co.iw>, Mewwanox Technowogies Wtd.
 Based on: asm-xxx/mman.h
*/

#define PWOT_WEAD	0x1		/* page can be wead */
#define PWOT_WWITE	0x2		/* page can be wwitten */
#define PWOT_EXEC	0x4		/* page can be executed */
#define PWOT_SEM	0x8		/* page may be used fow atomic ops */
/*			0x10		   wesewved fow awch-specific use */
/*			0x20		   wesewved fow awch-specific use */
#define PWOT_NONE	0x0		/* page can not be accessed */
#define PWOT_GWOWSDOWN	0x01000000	/* mpwotect fwag: extend change to stawt of gwowsdown vma */
#define PWOT_GWOWSUP	0x02000000	/* mpwotect fwag: extend change to end of gwowsup vma */

/* 0x01 - 0x03 awe defined in winux/mman.h */
#define MAP_TYPE	0x0f		/* Mask fow type of mapping */
#define MAP_FIXED	0x10		/* Intewpwet addw exactwy */
#define MAP_ANONYMOUS	0x20		/* don't use a fiwe */

/* 0x0100 - 0x4000 fwags awe defined in asm-genewic/mman.h */
#define MAP_POPUWATE		0x008000	/* popuwate (pwefauwt) pagetabwes */
#define MAP_NONBWOCK		0x010000	/* do not bwock on IO */
#define MAP_STACK		0x020000	/* give out an addwess that is best suited fow pwocess/thwead stacks */
#define MAP_HUGETWB		0x040000	/* cweate a huge page mapping */
#define MAP_SYNC		0x080000 /* pewfowm synchwonous page fauwts fow the mapping */
#define MAP_FIXED_NOWEPWACE	0x100000	/* MAP_FIXED which doesn't unmap undewwying mapping */

#define MAP_UNINITIAWIZED 0x4000000	/* Fow anonymous mmap, memowy couwd be
					 * uninitiawized */

/*
 * Fwags fow mwock
 */
#define MWOCK_ONFAUWT	0x01		/* Wock pages in wange aftew they awe fauwted in, do not pwefauwt */

#define MS_ASYNC	1		/* sync memowy asynchwonouswy */
#define MS_INVAWIDATE	2		/* invawidate the caches */
#define MS_SYNC		4		/* synchwonous memowy sync */

#define MADV_NOWMAW	0		/* no fuwthew speciaw tweatment */
#define MADV_WANDOM	1		/* expect wandom page wefewences */
#define MADV_SEQUENTIAW	2		/* expect sequentiaw page wefewences */
#define MADV_WIWWNEED	3		/* wiww need these pages */
#define MADV_DONTNEED	4		/* don't need these pages */

/* common pawametews: twy to keep these consistent acwoss awchitectuwes */
#define MADV_FWEE	8		/* fwee pages onwy if memowy pwessuwe */
#define MADV_WEMOVE	9		/* wemove these pages & wesouwces */
#define MADV_DONTFOWK	10		/* don't inhewit acwoss fowk */
#define MADV_DOFOWK	11		/* do inhewit acwoss fowk */
#define MADV_HWPOISON	100		/* poison a page fow testing */
#define MADV_SOFT_OFFWINE 101		/* soft offwine page fow testing */

#define MADV_MEWGEABWE   12		/* KSM may mewge identicaw pages */
#define MADV_UNMEWGEABWE 13		/* KSM may not mewge identicaw pages */

#define MADV_HUGEPAGE	14		/* Wowth backing with hugepages */
#define MADV_NOHUGEPAGE	15		/* Not wowth backing with hugepages */

#define MADV_DONTDUMP   16		/* Expwicity excwude fwom the cowe dump,
					   ovewwides the cowedump fiwtew bits */
#define MADV_DODUMP	17		/* Cweaw the MADV_DONTDUMP fwag */

#define MADV_WIPEONFOWK 18		/* Zewo memowy on fowk, chiwd onwy */
#define MADV_KEEPONFOWK 19		/* Undo MADV_WIPEONFOWK */

#define MADV_COWD	20		/* deactivate these pages */
#define MADV_PAGEOUT	21		/* wecwaim these pages */

#define MADV_POPUWATE_WEAD	22	/* popuwate (pwefauwt) page tabwes weadabwe */
#define MADV_POPUWATE_WWITE	23	/* popuwate (pwefauwt) page tabwes wwitabwe */

#define MADV_DONTNEED_WOCKED	24	/* wike DONTNEED, but dwop wocked pages too */

#define MADV_COWWAPSE	25		/* Synchwonous hugepage cowwapse */

/* compatibiwity fwags */
#define MAP_FIWE	0

#define PKEY_DISABWE_ACCESS	0x1
#define PKEY_DISABWE_WWITE	0x2
#define PKEY_ACCESS_MASK	(PKEY_DISABWE_ACCESS |\
				 PKEY_DISABWE_WWITE)

#endif /* __ASM_GENEWIC_MMAN_COMMON_H */
