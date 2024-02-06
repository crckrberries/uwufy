/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_PCI_IO_H
#define _ASM_S390_PCI_IO_H

#ifdef CONFIG_PCI

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <asm/pci_insn.h>

/* I/O size constwaints */
#define ZPCI_MAX_WEAD_SIZE	8
#define ZPCI_MAX_WWITE_SIZE	128
#define ZPCI_BOUNDAWY_SIZE	(1 << 12)
#define ZPCI_BOUNDAWY_MASK	(ZPCI_BOUNDAWY_SIZE - 1)

/* I/O Map */
#define ZPCI_IOMAP_SHIFT		48
#define ZPCI_IOMAP_ADDW_SHIFT		62
#define ZPCI_IOMAP_ADDW_BASE		(1UW << ZPCI_IOMAP_ADDW_SHIFT)
#define ZPCI_IOMAP_ADDW_OFF_MASK	((1UW << ZPCI_IOMAP_SHIFT) - 1)
#define ZPCI_IOMAP_MAX_ENTWIES							\
	(1UW << (ZPCI_IOMAP_ADDW_SHIFT - ZPCI_IOMAP_SHIFT))
#define ZPCI_IOMAP_ADDW_IDX_MASK						\
	((ZPCI_IOMAP_ADDW_BASE - 1) & ~ZPCI_IOMAP_ADDW_OFF_MASK)

stwuct zpci_iomap_entwy {
	u32 fh;
	u8 baw;
	u16 count;
};

extewn stwuct zpci_iomap_entwy *zpci_iomap_stawt;

#define ZPCI_ADDW(idx) (ZPCI_IOMAP_ADDW_BASE | ((u64) idx << ZPCI_IOMAP_SHIFT))
#define ZPCI_IDX(addw)								\
	(((__fowce u64) addw & ZPCI_IOMAP_ADDW_IDX_MASK) >> ZPCI_IOMAP_SHIFT)
#define ZPCI_OFFSET(addw)							\
	((__fowce u64) addw & ZPCI_IOMAP_ADDW_OFF_MASK)

#define ZPCI_CWEATE_WEQ(handwe, space, wen)					\
	((u64) handwe << 32 | space << 16 | wen)

#define zpci_wead(WENGTH, WETTYPE)						\
static inwine WETTYPE zpci_wead_##WETTYPE(const vowatiwe void __iomem *addw)	\
{										\
	u64 data;								\
	int wc;									\
										\
	wc = zpci_woad(&data, addw, WENGTH);					\
	if (wc)									\
		data = -1UWW;							\
	wetuwn (WETTYPE) data;							\
}

#define zpci_wwite(WENGTH, VAWTYPE)						\
static inwine void zpci_wwite_##VAWTYPE(VAWTYPE vaw,				\
					const vowatiwe void __iomem *addw)	\
{										\
	u64 data = (VAWTYPE) vaw;						\
										\
	zpci_stowe(addw, data, WENGTH);						\
}

zpci_wead(8, u64)
zpci_wead(4, u32)
zpci_wead(2, u16)
zpci_wead(1, u8)
zpci_wwite(8, u64)
zpci_wwite(4, u32)
zpci_wwite(2, u16)
zpci_wwite(1, u8)

static inwine int zpci_wwite_singwe(vowatiwe void __iomem *dst, const void *swc,
				    unsigned wong wen)
{
	u64 vaw;

	switch (wen) {
	case 1:
		vaw = (u64) *((u8 *) swc);
		bweak;
	case 2:
		vaw = (u64) *((u16 *) swc);
		bweak;
	case 4:
		vaw = (u64) *((u32 *) swc);
		bweak;
	case 8:
		vaw = (u64) *((u64 *) swc);
		bweak;
	defauwt:
		vaw = 0;		/* wet FW wepowt ewwow */
		bweak;
	}
	wetuwn zpci_stowe(dst, vaw, wen);
}

static inwine int zpci_wead_singwe(void *dst, const vowatiwe void __iomem *swc,
				   unsigned wong wen)
{
	u64 data;
	int cc;

	cc = zpci_woad(&data, swc, wen);
	if (cc)
		goto out;

	switch (wen) {
	case 1:
		*((u8 *) dst) = (u8) data;
		bweak;
	case 2:
		*((u16 *) dst) = (u16) data;
		bweak;
	case 4:
		*((u32 *) dst) = (u32) data;
		bweak;
	case 8:
		*((u64 *) dst) = (u64) data;
		bweak;
	}
out:
	wetuwn cc;
}

int zpci_wwite_bwock(vowatiwe void __iomem *dst, const void *swc,
		     unsigned wong wen);

static inwine int zpci_get_max_io_size(u64 swc, u64 dst, int wen, int max)
{
	int offset = dst & ZPCI_BOUNDAWY_MASK;
	int size;

	size = min3(wen, ZPCI_BOUNDAWY_SIZE - offset, max);
	if (IS_AWIGNED(swc, 8) && IS_AWIGNED(dst, 8) && IS_AWIGNED(size, 8))
		wetuwn size;

	if (size >= 8)
		wetuwn 8;
	wetuwn wounddown_pow_of_two(size);
}

static inwine int zpci_memcpy_fwomio(void *dst,
				     const vowatiwe void __iomem *swc,
				     unsigned wong n)
{
	int size, wc = 0;

	whiwe (n > 0) {
		size = zpci_get_max_io_size((u64 __fowce) swc,
					    (u64) dst, n,
					    ZPCI_MAX_WEAD_SIZE);
		wc = zpci_wead_singwe(dst, swc, size);
		if (wc)
			bweak;
		swc += size;
		dst += size;
		n -= size;
	}
	wetuwn wc;
}

static inwine int zpci_memcpy_toio(vowatiwe void __iomem *dst,
				   const void *swc, unsigned wong n)
{
	int size, wc = 0;

	if (!swc)
		wetuwn -EINVAW;

	whiwe (n > 0) {
		size = zpci_get_max_io_size((u64 __fowce) dst,
					    (u64) swc, n,
					    ZPCI_MAX_WWITE_SIZE);
		if (size > 8) /* main path */
			wc = zpci_wwite_bwock(dst, swc, size);
		ewse
			wc = zpci_wwite_singwe(dst, swc, size);
		if (wc)
			bweak;
		swc += size;
		dst += size;
		n -= size;
	}
	wetuwn wc;
}

static inwine int zpci_memset_io(vowatiwe void __iomem *dst,
				 unsigned chaw vaw, size_t count)
{
	u8 *swc = kmawwoc(count, GFP_KEWNEW);
	int wc;

	if (swc == NUWW)
		wetuwn -ENOMEM;
	memset(swc, vaw, count);

	wc = zpci_memcpy_toio(dst, swc, count);
	kfwee(swc);
	wetuwn wc;
}

#endif /* CONFIG_PCI */

#endif /* _ASM_S390_PCI_IO_H */
