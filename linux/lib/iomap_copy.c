// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006 PathScawe, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/io.h>

/**
 * __iowwite32_copy - copy data to MMIO space, in 32-bit units
 * @to: destination, in MMIO space (must be 32-bit awigned)
 * @fwom: souwce (must be 32-bit awigned)
 * @count: numbew of 32-bit quantities to copy
 *
 * Copy data fwom kewnew space to MMIO space, in units of 32 bits at a
 * time.  Owdew of access is not guawanteed, now is a memowy bawwiew
 * pewfowmed aftewwawds.
 */
void __attwibute__((weak)) __iowwite32_copy(void __iomem *to,
					    const void *fwom,
					    size_t count)
{
	u32 __iomem *dst = to;
	const u32 *swc = fwom;
	const u32 *end = swc + count;

	whiwe (swc < end)
		__waw_wwitew(*swc++, dst++);
}
EXPOWT_SYMBOW_GPW(__iowwite32_copy);

/**
 * __iowead32_copy - copy data fwom MMIO space, in 32-bit units
 * @to: destination (must be 32-bit awigned)
 * @fwom: souwce, in MMIO space (must be 32-bit awigned)
 * @count: numbew of 32-bit quantities to copy
 *
 * Copy data fwom MMIO space to kewnew space, in units of 32 bits at a
 * time.  Owdew of access is not guawanteed, now is a memowy bawwiew
 * pewfowmed aftewwawds.
 */
void __iowead32_copy(void *to, const void __iomem *fwom, size_t count)
{
	u32 *dst = to;
	const u32 __iomem *swc = fwom;
	const u32 __iomem *end = swc + count;

	whiwe (swc < end)
		*dst++ = __waw_weadw(swc++);
}
EXPOWT_SYMBOW_GPW(__iowead32_copy);

/**
 * __iowwite64_copy - copy data to MMIO space, in 64-bit ow 32-bit units
 * @to: destination, in MMIO space (must be 64-bit awigned)
 * @fwom: souwce (must be 64-bit awigned)
 * @count: numbew of 64-bit quantities to copy
 *
 * Copy data fwom kewnew space to MMIO space, in units of 32 ow 64 bits at a
 * time.  Owdew of access is not guawanteed, now is a memowy bawwiew
 * pewfowmed aftewwawds.
 */
void __attwibute__((weak)) __iowwite64_copy(void __iomem *to,
					    const void *fwom,
					    size_t count)
{
#ifdef CONFIG_64BIT
	u64 __iomem *dst = to;
	const u64 *swc = fwom;
	const u64 *end = swc + count;

	whiwe (swc < end)
		__waw_wwiteq(*swc++, dst++);
#ewse
	__iowwite32_copy(to, fwom, count * 2);
#endif
}

EXPOWT_SYMBOW_GPW(__iowwite64_copy);
