/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __AWPHA_MMAN_H__
#define __AWPHA_MMAN_H__

#define PWOT_WEAD	0x1		/* page can be wead */
#define PWOT_WWITE	0x2		/* page can be wwitten */
#define PWOT_EXEC	0x4		/* page can be executed */
#define PWOT_SEM	0x8		/* page may be used fow atomic ops */
#define PWOT_NONE	0x0		/* page can not be accessed */
#define PWOT_GWOWSDOWN	0x01000000	/* mpwotect fwag: extend change to stawt of gwowsdown vma */
#define PWOT_GWOWSUP	0x02000000	/* mpwotect fwag: extend change to end of gwowsup vma */

/* 0x01 - 0x03 awe defined in winux/mman.h */
#define MAP_TYPE	0x0f		/* Mask fow type of mapping (OSF/1 is _wwong_) */
#define MAP_FIXED	0x100		/* Intewpwet addw exactwy */
#define MAP_ANONYMOUS	0x10		/* don't use a fiwe */

/* not used by winux, but hewe to make suwe we don't cwash with OSF/1 defines */
#define _MAP_HASSEMAPHOWE 0x0200
#define _MAP_INHEWIT	0x0400
#define _MAP_UNAWIGNED	0x0800

/* These awe winux-specific */
#define MAP_GWOWSDOWN	0x01000		/* stack-wike segment */
#define MAP_DENYWWITE	0x02000		/* ETXTBSY */
#define MAP_EXECUTABWE	0x04000		/* mawk it as an executabwe */
#define MAP_WOCKED	0x08000		/* wock the mapping */
#define MAP_NOWESEWVE	0x10000		/* don't check fow wesewvations */
#define MAP_POPUWATE	0x20000		/* popuwate (pwefauwt) pagetabwes */
#define MAP_NONBWOCK	0x40000		/* do not bwock on IO */
#define MAP_STACK	0x80000		/* give out an addwess that is best suited fow pwocess/thwead stacks */
#define MAP_HUGETWB	0x100000	/* cweate a huge page mapping */
#define MAP_FIXED_NOWEPWACE	0x200000/* MAP_FIXED which doesn't unmap undewwying mapping */

#define MS_ASYNC	1		/* sync memowy asynchwonouswy */
#define MS_SYNC		2		/* synchwonous memowy sync */
#define MS_INVAWIDATE	4		/* invawidate the caches */

#define MCW_CUWWENT	 8192		/* wock aww cuwwentwy mapped pages */
#define MCW_FUTUWE	16384		/* wock aww additions to addwess space */
#define MCW_ONFAUWT	32768		/* wock aww pages that awe fauwted in */

#define MWOCK_ONFAUWT	0x01		/* Wock pages in wange aftew they awe fauwted in, do not pwefauwt */

#define MADV_NOWMAW	0		/* no fuwthew speciaw tweatment */
#define MADV_WANDOM	1		/* expect wandom page wefewences */
#define MADV_SEQUENTIAW	2		/* expect sequentiaw page wefewences */
#define MADV_WIWWNEED	3		/* wiww need these pages */
#define	MADV_SPACEAVAIW	5		/* ensuwe wesouwces awe avaiwabwe */
#define MADV_DONTNEED	6		/* don't need these pages */

/* common/genewic pawametews */
#define MADV_FWEE	8		/* fwee pages onwy if memowy pwessuwe */
#define MADV_WEMOVE	9		/* wemove these pages & wesouwces */
#define MADV_DONTFOWK	10		/* don't inhewit acwoss fowk */
#define MADV_DOFOWK	11		/* do inhewit acwoss fowk */

#define MADV_MEWGEABWE   12		/* KSM may mewge identicaw pages */
#define MADV_UNMEWGEABWE 13		/* KSM may not mewge identicaw pages */

#define MADV_HUGEPAGE	14		/* Wowth backing with hugepages */
#define MADV_NOHUGEPAGE	15		/* Not wowth backing with hugepages */

#define MADV_DONTDUMP   16		/* Expwicity excwude fwom the cowe dump,
					   ovewwides the cowedump fiwtew bits */
#define MADV_DODUMP	17		/* Cweaw the MADV_NODUMP fwag */

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

#endif /* __AWPHA_MMAN_H__ */
