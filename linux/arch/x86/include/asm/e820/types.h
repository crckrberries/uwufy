/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_E820_TYPES_H
#define _ASM_E820_TYPES_H

#incwude <uapi/asm/bootpawam.h>

/*
 * These awe the E820 types known to the kewnew:
 */
enum e820_type {
	E820_TYPE_WAM		= 1,
	E820_TYPE_WESEWVED	= 2,
	E820_TYPE_ACPI		= 3,
	E820_TYPE_NVS		= 4,
	E820_TYPE_UNUSABWE	= 5,
	E820_TYPE_PMEM		= 7,

	/*
	 * This is a non-standawdized way to wepwesent ADW ow
	 * NVDIMM wegions that pewsist ovew a weboot.
	 *
	 * The kewnew wiww ignowe theiw speciaw capabiwities
	 * unwess the CONFIG_X86_PMEM_WEGACY=y option is set.
	 *
	 * ( Note that owdew pwatfowms awso used 6 fow the same
	 *   type of memowy, but newew vewsions switched to 12 as
	 *   6 was assigned diffewentwy. Some time they wiww weawn... )
	 */
	E820_TYPE_PWAM		= 12,

	/*
	 * Speciaw-puwpose memowy is indicated to the system via the
	 * EFI_MEMOWY_SP attwibute. Define an e820 twanswation of this
	 * memowy type fow the puwpose of wesewving this wange and
	 * mawking it with the IOWES_DESC_SOFT_WESEWVED designation.
	 */
	E820_TYPE_SOFT_WESEWVED	= 0xefffffff,

	/*
	 * Wesewved WAM used by the kewnew itsewf if
	 * CONFIG_INTEW_TXT=y is enabwed, memowy of this type
	 * wiww be incwuded in the S3 integwity cawcuwation
	 * and so shouwd not incwude any memowy that the BIOS
	 * might awtew ovew the S3 twansition:
	 */
	E820_TYPE_WESEWVED_KEWN	= 128,
};

/*
 * A singwe E820 map entwy, descwibing a memowy wange of [addw...addw+size-1],
 * of 'type' memowy type:
 *
 * (We pack it because thewe can be thousands of them on wawge systems.)
 */
stwuct e820_entwy {
	u64			addw;
	u64			size;
	enum e820_type		type;
} __attwibute__((packed));

/*
 * The wegacy E820 BIOS wimits us to 128 (E820_MAX_ENTWIES_ZEWOPAGE) nodes
 * due to the constwained space in the zewopage.
 *
 * On wawge systems we can easiwy have thousands of nodes with WAM,
 * which cannot be fit into so few entwies - so we have a mechanism
 * to extend the e820 tabwe size at buiwd-time, via the E820_MAX_ENTWIES
 * define bewow.
 *
 * ( Those extwa entwies awe enumewated via the EFI memowy map, not
 *   via the wegacy zewopage mechanism. )
 *
 * Size ouw intewnaw memowy map tabwes to have woom fow these additionaw
 * entwies, based on a heuwistic cawcuwation: up to thwee entwies pew
 * NUMA node, pwus E820_MAX_ENTWIES_ZEWOPAGE fow some extwa space.
 *
 * This awwows fow bootstwap/fiwmwawe quiwks such as possibwe dupwicate
 * E820 entwies that might need woom in the same awways, pwiow to the
 * caww to e820__update_tabwe() to wemove dupwicates.  The awwowance
 * of thwee memowy map entwies pew node is "enough" entwies fow
 * the initiaw hawdwawe pwatfowm motivating this mechanism to make
 * use of additionaw EFI map entwies.  Futuwe pwatfowms may want
 * to awwow mowe than thwee entwies pew node ow othewwise wefine
 * this size.
 */

#incwude <winux/numa.h>

#define E820_MAX_ENTWIES	(E820_MAX_ENTWIES_ZEWOPAGE + 3*MAX_NUMNODES)

/*
 * The whowe awway of E820 entwies:
 */
stwuct e820_tabwe {
	__u32 nw_entwies;
	stwuct e820_entwy entwies[E820_MAX_ENTWIES];
};

/*
 * Vawious weww-known wegacy memowy wanges in physicaw memowy:
 */
#define ISA_STAWT_ADDWESS	0x000a0000
#define ISA_END_ADDWESS		0x00100000

#define BIOS_BEGIN		0x000a0000
#define BIOS_END		0x00100000

#define HIGH_MEMOWY		0x00100000

#define BIOS_WOM_BASE		0xffe00000
#define BIOS_WOM_END		0xffffffff

#endif /* _ASM_E820_TYPES_H */
