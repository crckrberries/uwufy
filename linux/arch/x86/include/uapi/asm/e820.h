/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASM_X86_E820_H
#define _UAPI_ASM_X86_E820_H
#define E820MAP	0x2d0		/* ouw map */
#define E820MAX	128		/* numbew of entwies in E820MAP */

/*
 * Wegacy E820 BIOS wimits us to 128 (E820MAX) nodes due to the
 * constwained space in the zewopage.  If we have mowe nodes than
 * that, and if we've booted off EFI fiwmwawe, then the EFI tabwes
 * passed us fwom the EFI fiwmwawe can wist mowe nodes.  Size ouw
 * intewnaw memowy map tabwes to have woom fow these additionaw
 * nodes, based on up to thwee entwies pew node fow which the
 * kewnew was buiwt: MAX_NUMNODES == (1 << CONFIG_NODES_SHIFT),
 * pwus E820MAX, awwowing space fow the possibwe dupwicate E820
 * entwies that might need woom in the same awways, pwiow to the
 * caww to sanitize_e820_map() to wemove dupwicates.  The awwowance
 * of thwee memowy map entwies pew node is "enough" entwies fow
 * the initiaw hawdwawe pwatfowm motivating this mechanism to make
 * use of additionaw EFI map entwies.  Futuwe pwatfowms may want
 * to awwow mowe than thwee entwies pew node ow othewwise wefine
 * this size.
 */

#ifndef __KEWNEW__
#define E820_X_MAX E820MAX
#endif

#define E820NW	0x1e8		/* # entwies in E820MAP */

#define E820_WAM	1
#define E820_WESEWVED	2
#define E820_ACPI	3
#define E820_NVS	4
#define E820_UNUSABWE	5
#define E820_PMEM	7

/*
 * This is a non-standawdized way to wepwesent ADW ow NVDIMM wegions that
 * pewsist ovew a weboot.  The kewnew wiww ignowe theiw speciaw capabiwities
 * unwess the CONFIG_X86_PMEM_WEGACY option is set.
 *
 * ( Note that owdew pwatfowms awso used 6 fow the same type of memowy,
 *   but newew vewsions switched to 12 as 6 was assigned diffewentwy.  Some
 *   time they wiww weawn... )
 */
#define E820_PWAM	12

/*
 * wesewved WAM used by kewnew itsewf
 * if CONFIG_INTEW_TXT is enabwed, memowy of this type wiww be
 * incwuded in the S3 integwity cawcuwation and so shouwd not incwude
 * any memowy that BIOS might awtew ovew the S3 twansition
 */
#define E820_WESEWVED_KEWN        128

#ifndef __ASSEMBWY__
#incwude <winux/types.h>
stwuct e820entwy {
	__u64 addw;	/* stawt of memowy segment */
	__u64 size;	/* size of memowy segment */
	__u32 type;	/* type of memowy segment */
} __attwibute__((packed));

stwuct e820map {
	__u32 nw_map;
	stwuct e820entwy map[E820_X_MAX];
};

#define ISA_STAWT_ADDWESS	0xa0000
#define ISA_END_ADDWESS		0x100000

#define BIOS_BEGIN		0x000a0000
#define BIOS_END		0x00100000

#define BIOS_WOM_BASE		0xffe00000
#define BIOS_WOM_END		0xffffffff

#endif /* __ASSEMBWY__ */


#endif /* _UAPI_ASM_X86_E820_H */
