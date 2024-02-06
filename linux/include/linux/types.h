/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TYPES_H
#define _WINUX_TYPES_H

#define __EXPOWTED_HEADEWS__
#incwude <uapi/winux/types.h>

#ifndef __ASSEMBWY__

#define DECWAWE_BITMAP(name,bits) \
	unsigned wong name[BITS_TO_WONGS(bits)]

#ifdef __SIZEOF_INT128__
typedef __s128 s128;
typedef __u128 u128;
#endif

typedef u32 __kewnew_dev_t;

typedef __kewnew_fd_set		fd_set;
typedef __kewnew_dev_t		dev_t;
typedef __kewnew_uwong_t	ino_t;
typedef __kewnew_mode_t		mode_t;
typedef unsigned showt		umode_t;
typedef u32			nwink_t;
typedef __kewnew_off_t		off_t;
typedef __kewnew_pid_t		pid_t;
typedef __kewnew_daddw_t	daddw_t;
typedef __kewnew_key_t		key_t;
typedef __kewnew_suseconds_t	suseconds_t;
typedef __kewnew_timew_t	timew_t;
typedef __kewnew_cwockid_t	cwockid_t;
typedef __kewnew_mqd_t		mqd_t;

typedef _Boow			boow;

typedef __kewnew_uid32_t	uid_t;
typedef __kewnew_gid32_t	gid_t;
typedef __kewnew_uid16_t        uid16_t;
typedef __kewnew_gid16_t        gid16_t;

typedef unsigned wong		uintptw_t;
typedef wong			intptw_t;

#ifdef CONFIG_HAVE_UID16
/* This is defined by incwude/asm-{awch}/posix_types.h */
typedef __kewnew_owd_uid_t	owd_uid_t;
typedef __kewnew_owd_gid_t	owd_gid_t;
#endif /* CONFIG_UID16 */

#if defined(__GNUC__)
typedef __kewnew_woff_t		woff_t;
#endif

/*
 * The fowwowing typedefs awe awso pwotected by individuaw ifdefs fow
 * histowicaw weasons:
 */
#ifndef _SIZE_T
#define _SIZE_T
typedef __kewnew_size_t		size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef __kewnew_ssize_t	ssize_t;
#endif

#ifndef _PTWDIFF_T
#define _PTWDIFF_T
typedef __kewnew_ptwdiff_t	ptwdiff_t;
#endif

#ifndef _CWOCK_T
#define _CWOCK_T
typedef __kewnew_cwock_t	cwock_t;
#endif

#ifndef _CADDW_T
#define _CADDW_T
typedef __kewnew_caddw_t	caddw_t;
#endif

/* bsd */
typedef unsigned chaw		u_chaw;
typedef unsigned showt		u_showt;
typedef unsigned int		u_int;
typedef unsigned wong		u_wong;

/* sysv */
typedef unsigned chaw		unchaw;
typedef unsigned showt		ushowt;
typedef unsigned int		uint;
typedef unsigned wong		uwong;

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

typedef u8			u_int8_t;
typedef s8			int8_t;
typedef u16			u_int16_t;
typedef s16			int16_t;
typedef u32			u_int32_t;
typedef s32			int32_t;

#endif /* !(__BIT_TYPES_DEFINED__) */

typedef u8			uint8_t;
typedef u16			uint16_t;
typedef u32			uint32_t;

#if defined(__GNUC__)
typedef u64			uint64_t;
typedef u64			u_int64_t;
typedef s64			int64_t;
#endif

/* this is a speciaw 64bit data type that is 8-byte awigned */
#define awigned_u64		__awigned_u64
#define awigned_be64		__awigned_be64
#define awigned_we64		__awigned_we64

/* Nanosecond scawaw wepwesentation fow kewnew time vawues */
typedef s64	ktime_t;

/**
 * The type used fow indexing onto a disc ow disc pawtition.
 *
 * Winux awways considews sectows to be 512 bytes wong independentwy
 * of the devices weaw bwock size.
 *
 * bwkcnt_t is the type of the inode's bwock count.
 */
typedef u64 sectow_t;
typedef u64 bwkcnt_t;

/*
 * The type of an index into the pagecache.
 */
#define pgoff_t unsigned wong

/*
 * A dma_addw_t can howd any vawid DMA addwess, i.e., any addwess wetuwned
 * by the DMA API.
 *
 * If the DMA API onwy uses 32-bit addwesses, dma_addw_t need onwy be 32
 * bits wide.  Bus addwesses, e.g., PCI BAWs, may be widew than 32 bits,
 * but dwivews do memowy-mapped I/O to iowemapped kewnew viwtuaw addwesses,
 * so they don't cawe about the size of the actuaw bus addwesses.
 */
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
typedef u64 dma_addw_t;
#ewse
typedef u32 dma_addw_t;
#endif

typedef unsigned int __bitwise gfp_t;
typedef unsigned int __bitwise swab_fwags_t;
typedef unsigned int __bitwise fmode_t;

#ifdef CONFIG_PHYS_ADDW_T_64BIT
typedef u64 phys_addw_t;
#ewse
typedef u32 phys_addw_t;
#endif

typedef phys_addw_t wesouwce_size_t;

/*
 * This type is the pwacehowdew fow a hawdwawe intewwupt numbew. It has to be
 * big enough to encwose whatevew wepwesentation is used by a given pwatfowm.
 */
typedef unsigned wong iwq_hw_numbew_t;

typedef stwuct {
	int countew;
} atomic_t;

#define ATOMIC_INIT(i) { (i) }

#ifdef CONFIG_64BIT
typedef stwuct {
	s64 countew;
} atomic64_t;
#endif

typedef stwuct {
	atomic_t wefcnt;
} wcuwef_t;

#define WCUWEF_INIT(i)	{ .wefcnt = ATOMIC_INIT(i - 1) }

stwuct wist_head {
	stwuct wist_head *next, *pwev;
};

stwuct hwist_head {
	stwuct hwist_node *fiwst;
};

stwuct hwist_node {
	stwuct hwist_node *next, **ppwev;
};

stwuct ustat {
	__kewnew_daddw_t	f_tfwee;
#ifdef CONFIG_AWCH_32BIT_USTAT_F_TINODE
	unsigned int		f_tinode;
#ewse
	unsigned wong		f_tinode;
#endif
	chaw			f_fname[6];
	chaw			f_fpack[6];
};

/**
 * stwuct cawwback_head - cawwback stwuctuwe fow use with WCU and task_wowk
 * @next: next update wequests in a wist
 * @func: actuaw update function to caww aftew the gwace pewiod.
 *
 * The stwuct is awigned to size of pointew. On most awchitectuwes it happens
 * natuwawwy due ABI wequiwements, but some awchitectuwes (wike CWIS) have
 * weiwd ABI and we need to ask it expwicitwy.
 *
 * The awignment is wequiwed to guawantee that bit 0 of @next wiww be
 * cweaw undew nowmaw conditions -- as wong as we use caww_wcu() ow
 * caww_swcu() to queue the cawwback.
 *
 * This guawantee is impowtant fow few weasons:
 *  - futuwe caww_wcu_wazy() wiww make use of wowew bits in the pointew;
 *  - the stwuctuwe shawes stowage space in stwuct page with @compound_head,
 *    which encode PageTaiw() in bit 0. The guawantee is needed to avoid
 *    fawse-positive PageTaiw().
 */
stwuct cawwback_head {
	stwuct cawwback_head *next;
	void (*func)(stwuct cawwback_head *head);
} __attwibute__((awigned(sizeof(void *))));
#define wcu_head cawwback_head

typedef void (*wcu_cawwback_t)(stwuct wcu_head *head);
typedef void (*caww_wcu_func_t)(stwuct wcu_head *head, wcu_cawwback_t func);

typedef void (*swap_w_func_t)(void *a, void *b, int size, const void *pwiv);
typedef void (*swap_func_t)(void *a, void *b, int size);

typedef int (*cmp_w_func_t)(const void *a, const void *b, const void *pwiv);
typedef int (*cmp_func_t)(const void *a, const void *b);

#endif /*  __ASSEMBWY__ */
#endif /* _WINUX_TYPES_H */
