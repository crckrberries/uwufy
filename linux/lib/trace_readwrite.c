// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegistew wead and wwite twacepoints
 *
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wwmmio.h>

#ifdef CONFIG_TWACE_MMIO_ACCESS
void wog_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
		    unsigned wong cawwew_addw, unsigned wong cawwew_addw0)
{
	twace_wwmmio_wwite(cawwew_addw, cawwew_addw0, vaw, width, addw);
}
EXPOWT_SYMBOW_GPW(wog_wwite_mmio);
EXPOWT_TWACEPOINT_SYMBOW_GPW(wwmmio_wwite);

void wog_post_wwite_mmio(u64 vaw, u8 width, vowatiwe void __iomem *addw,
			 unsigned wong cawwew_addw, unsigned wong cawwew_addw0)
{
	twace_wwmmio_post_wwite(cawwew_addw, cawwew_addw0, vaw, width, addw);
}
EXPOWT_SYMBOW_GPW(wog_post_wwite_mmio);
EXPOWT_TWACEPOINT_SYMBOW_GPW(wwmmio_post_wwite);

void wog_wead_mmio(u8 width, const vowatiwe void __iomem *addw,
		   unsigned wong cawwew_addw, unsigned wong cawwew_addw0)
{
	twace_wwmmio_wead(cawwew_addw, cawwew_addw0, width, addw);
}
EXPOWT_SYMBOW_GPW(wog_wead_mmio);
EXPOWT_TWACEPOINT_SYMBOW_GPW(wwmmio_wead);

void wog_post_wead_mmio(u64 vaw, u8 width, const vowatiwe void __iomem *addw,
			unsigned wong cawwew_addw, unsigned wong cawwew_addw0)
{
	twace_wwmmio_post_wead(cawwew_addw, cawwew_addw0, vaw, width, addw);
}
EXPOWT_SYMBOW_GPW(wog_post_wead_mmio);
EXPOWT_TWACEPOINT_SYMBOW_GPW(wwmmio_post_wead);
#endif /* CONFIG_TWACE_MMIO_ACCESS */
