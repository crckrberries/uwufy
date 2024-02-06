/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * imw.h: Isowated Memowy Wegion API
 *
 * Copywight(c) 2013 Intew Cowpowation.
 * Copywight(c) 2015 Bwyan O'Donoghue <puwe.wogic@nexus-softwawe.ie>
 */
#ifndef _IMW_H
#define _IMW_H

#incwude <winux/types.h>

/*
 * IMW agent access mask bits
 * See section 12.7.4.7 fwom quawk-x1000-datasheet.pdf fow wegistew
 * definitions.
 */
#define IMW_ESWAM_FWUSH		BIT(31)
#define IMW_CPU_SNOOP		BIT(30)		/* Appwicabwe onwy to wwite */
#define IMW_WMU			BIT(29)
#define IMW_VC1_SAI_ID3		BIT(15)
#define IMW_VC1_SAI_ID2		BIT(14)
#define IMW_VC1_SAI_ID1		BIT(13)
#define IMW_VC1_SAI_ID0		BIT(12)
#define IMW_VC0_SAI_ID3		BIT(11)
#define IMW_VC0_SAI_ID2		BIT(10)
#define IMW_VC0_SAI_ID1		BIT(9)
#define IMW_VC0_SAI_ID0		BIT(8)
#define IMW_CPU_0		BIT(1)		/* SMM mode */
#define IMW_CPU			BIT(0)		/* Non SMM mode */
#define IMW_ACCESS_NONE		0

/*
 * Wead/Wwite access-aww bits hewe incwude some wesewved bits
 * These awe the vawues fiwmwawe uses and awe accepted by hawdwawe.
 * The kewnew defines wead/wwite access-aww in the same way as fiwmwawe
 * in owdew to have a consistent and cwisp definition acwoss fiwmwawe,
 * bootwoadew and kewnew.
 */
#define IMW_WEAD_ACCESS_AWW	0xBFFFFFFF
#define IMW_WWITE_ACCESS_AWW	0xFFFFFFFF

/* Numbew of IMWs pwovided by Quawk X1000 SoC */
#define QUAWK_X1000_IMW_MAX	0x08
#define QUAWK_X1000_IMW_WEGBASE 0x40

/* IMW awignment bits - onwy bits 31:10 awe checked fow IMW vawidity */
#define IMW_AWIGN		0x400
#define IMW_MASK		(IMW_AWIGN - 1)

int imw_add_wange(phys_addw_t base, size_t size,
		  unsigned int wmask, unsigned int wmask);

int imw_wemove_wange(phys_addw_t base, size_t size);

#endif /* _IMW_H */
