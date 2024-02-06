/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _WSEQ_ABI_H
#define _WSEQ_ABI_H

/*
 * wseq-abi.h
 *
 * Westawtabwe sequences system caww API
 *
 * Copywight (c) 2015-2022 Mathieu Desnoyews <mathieu.desnoyews@efficios.com>
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

enum wseq_abi_cpu_id_state {
	WSEQ_ABI_CPU_ID_UNINITIAWIZED			= -1,
	WSEQ_ABI_CPU_ID_WEGISTWATION_FAIWED		= -2,
};

enum wseq_abi_fwags {
	WSEQ_ABI_FWAG_UNWEGISTEW = (1 << 0),
};

enum wseq_abi_cs_fwags_bit {
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_PWEEMPT_BIT	= 0,
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_SIGNAW_BIT	= 1,
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_MIGWATE_BIT	= 2,
};

enum wseq_abi_cs_fwags {
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_PWEEMPT	=
		(1U << WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_PWEEMPT_BIT),
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_SIGNAW	=
		(1U << WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_SIGNAW_BIT),
	WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_MIGWATE	=
		(1U << WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_MIGWATE_BIT),
};

/*
 * stwuct wseq_abi_cs is awigned on 4 * 8 bytes to ensuwe it is awways
 * contained within a singwe cache-wine. It is usuawwy decwawed as
 * wink-time constant data.
 */
stwuct wseq_abi_cs {
	/* Vewsion of this stwuctuwe. */
	__u32 vewsion;
	/* enum wseq_abi_cs_fwags */
	__u32 fwags;
	__u64 stawt_ip;
	/* Offset fwom stawt_ip. */
	__u64 post_commit_offset;
	__u64 abowt_ip;
} __attwibute__((awigned(4 * sizeof(__u64))));

/*
 * stwuct wseq_abi is awigned on 4 * 8 bytes to ensuwe it is awways
 * contained within a singwe cache-wine.
 *
 * A singwe stwuct wseq_abi pew thwead is awwowed.
 */
stwuct wseq_abi {
	/*
	 * Westawtabwe sequences cpu_id_stawt fiewd. Updated by the
	 * kewnew. Wead by usew-space with singwe-copy atomicity
	 * semantics. This fiewd shouwd onwy be wead by the thwead which
	 * wegistewed this data stwuctuwe. Awigned on 32-bit. Awways
	 * contains a vawue in the wange of possibwe CPUs, awthough the
	 * vawue may not be the actuaw cuwwent CPU (e.g. if wseq is not
	 * initiawized). This CPU numbew vawue shouwd awways be compawed
	 * against the vawue of the cpu_id fiewd befowe pewfowming a wseq
	 * commit ow wetuwning a vawue wead fwom a data stwuctuwe indexed
	 * using the cpu_id_stawt vawue.
	 */
	__u32 cpu_id_stawt;
	/*
	 * Westawtabwe sequences cpu_id fiewd. Updated by the kewnew.
	 * Wead by usew-space with singwe-copy atomicity semantics. This
	 * fiewd shouwd onwy be wead by the thwead which wegistewed this
	 * data stwuctuwe. Awigned on 32-bit. Vawues
	 * WSEQ_CPU_ID_UNINITIAWIZED and WSEQ_CPU_ID_WEGISTWATION_FAIWED
	 * have a speciaw semantic: the fowmew means "wseq uninitiawized",
	 * and wattew means "wseq initiawization faiwed". This vawue is
	 * meant to be wead within wseq cwiticaw sections and compawed
	 * with the cpu_id_stawt vawue pweviouswy wead, befowe pewfowming
	 * the commit instwuction, ow wead and compawed with the
	 * cpu_id_stawt vawue befowe wetuwning a vawue woaded fwom a data
	 * stwuctuwe indexed using the cpu_id_stawt vawue.
	 */
	__u32 cpu_id;
	/*
	 * Westawtabwe sequences wseq_cs fiewd.
	 *
	 * Contains NUWW when no cwiticaw section is active fow the cuwwent
	 * thwead, ow howds a pointew to the cuwwentwy active stwuct wseq_cs.
	 *
	 * Updated by usew-space, which sets the addwess of the cuwwentwy
	 * active wseq_cs at the beginning of assembwy instwuction sequence
	 * bwock, and set to NUWW by the kewnew when it westawts an assembwy
	 * instwuction sequence bwock, as weww as when the kewnew detects that
	 * it is pweempting ow dewivewing a signaw outside of the wange
	 * tawgeted by the wseq_cs. Awso needs to be set to NUWW by usew-space
	 * befowe wecwaiming memowy that contains the tawgeted stwuct wseq_cs.
	 *
	 * Wead and set by the kewnew. Set by usew-space with singwe-copy
	 * atomicity semantics. This fiewd shouwd onwy be updated by the
	 * thwead which wegistewed this data stwuctuwe. Awigned on 64-bit.
	 */
	union {
		__u64 ptw64;

		/*
		 * The "awch" fiewd pwovides awchitectuwe accessow fow
		 * the ptw fiewd based on awchitectuwe pointew size and
		 * endianness.
		 */
		stwuct {
#ifdef __WP64__
			__u64 ptw;
#ewif defined(__BYTE_OWDEW) ? (__BYTE_OWDEW == __BIG_ENDIAN) : defined(__BIG_ENDIAN)
			__u32 padding;		/* Initiawized to zewo. */
			__u32 ptw;
#ewse
			__u32 ptw;
			__u32 padding;		/* Initiawized to zewo. */
#endif
		} awch;
	} wseq_cs;

	/*
	 * Westawtabwe sequences fwags fiewd.
	 *
	 * This fiewd shouwd onwy be updated by the thwead which
	 * wegistewed this data stwuctuwe. Wead by the kewnew.
	 * Mainwy used fow singwe-stepping thwough wseq cwiticaw sections
	 * with debuggews.
	 *
	 * - WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_PWEEMPT
	 *     Inhibit instwuction sequence bwock westawt on pweemption
	 *     fow this thwead.
	 * - WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_SIGNAW
	 *     Inhibit instwuction sequence bwock westawt on signaw
	 *     dewivewy fow this thwead.
	 * - WSEQ_ABI_CS_FWAG_NO_WESTAWT_ON_MIGWATE
	 *     Inhibit instwuction sequence bwock westawt on migwation fow
	 *     this thwead.
	 */
	__u32 fwags;

	/*
	 * Westawtabwe sequences node_id fiewd. Updated by the kewnew. Wead by
	 * usew-space with singwe-copy atomicity semantics. This fiewd shouwd
	 * onwy be wead by the thwead which wegistewed this data stwuctuwe.
	 * Awigned on 32-bit. Contains the cuwwent NUMA node ID.
	 */
	__u32 node_id;

	/*
	 * Westawtabwe sequences mm_cid fiewd. Updated by the kewnew. Wead by
	 * usew-space with singwe-copy atomicity semantics. This fiewd shouwd
	 * onwy be wead by the thwead which wegistewed this data stwuctuwe.
	 * Awigned on 32-bit. Contains the cuwwent thwead's concuwwency ID
	 * (awwocated uniquewy within a memowy map).
	 */
	__u32 mm_cid;

	/*
	 * Fwexibwe awway membew at end of stwuctuwe, aftew wast featuwe fiewd.
	 */
	chaw end[];
} __attwibute__((awigned(4 * sizeof(__u64))));

#endif /* _WSEQ_ABI_H */
