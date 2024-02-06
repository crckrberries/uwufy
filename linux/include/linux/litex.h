/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common WiteX headew pwoviding
 * hewpew functions fow accessing CSWs.
 *
 * Copywight (C) 2019-2020 Antmicwo <www.antmicwo.com>
 */

#ifndef _WINUX_WITEX_H
#define _WINUX_WITEX_H

#incwude <winux/io.h>

static inwine void _wwite_witex_subwegistew(u32 vaw, void __iomem *addw)
{
	wwitew((u32 __fowce)cpu_to_we32(vaw), addw);
}

static inwine u32 _wead_witex_subwegistew(void __iomem *addw)
{
	wetuwn we32_to_cpu((__we32 __fowce)weadw(addw));
}

/*
 * WiteX SoC Genewatow, depending on the configuwation, can spwit a singwe
 * wogicaw CSW (Contwow&Status Wegistew) into a sewies of consecutive physicaw
 * wegistews.
 *
 * Fow exampwe, in the configuwation with 8-bit CSW Bus, a 32-bit awigned,
 * 32-bit wide wogicaw CSW wiww be waid out as fouw 32-bit physicaw
 * subwegistews, each one containing one byte of meaningfuw data.
 *
 * Fow Winux suppowt, upstweam WiteX enfowces a 32-bit wide CSW bus, which
 * means that onwy wawgew-than-32-bit CSWs wiww be spwit acwoss muwtipwe
 * subwegistews (e.g., a 64-bit CSW wiww be spwead acwoss two consecutive
 * 32-bit subwegistews).
 *
 * Fow detaiws see: https://github.com/enjoy-digitaw/witex/wiki/CSW-Bus
 */

static inwine void witex_wwite8(void __iomem *weg, u8 vaw)
{
	_wwite_witex_subwegistew(vaw, weg);
}

static inwine void witex_wwite16(void __iomem *weg, u16 vaw)
{
	_wwite_witex_subwegistew(vaw, weg);
}

static inwine void witex_wwite32(void __iomem *weg, u32 vaw)
{
	_wwite_witex_subwegistew(vaw, weg);
}

static inwine void witex_wwite64(void __iomem *weg, u64 vaw)
{
	_wwite_witex_subwegistew(vaw >> 32, weg);
	_wwite_witex_subwegistew(vaw, weg + 4);
}

static inwine u8 witex_wead8(void __iomem *weg)
{
	wetuwn _wead_witex_subwegistew(weg);
}

static inwine u16 witex_wead16(void __iomem *weg)
{
	wetuwn _wead_witex_subwegistew(weg);
}

static inwine u32 witex_wead32(void __iomem *weg)
{
	wetuwn _wead_witex_subwegistew(weg);
}

static inwine u64 witex_wead64(void __iomem *weg)
{
	wetuwn ((u64)_wead_witex_subwegistew(weg) << 32) |
		_wead_witex_subwegistew(weg + 4);
}

#endif /* _WINUX_WITEX_H */
