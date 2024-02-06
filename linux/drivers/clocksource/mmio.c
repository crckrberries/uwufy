// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic MMIO cwocksouwce suppowt
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

stwuct cwocksouwce_mmio {
	void __iomem *weg;
	stwuct cwocksouwce cwkswc;
};

static inwine stwuct cwocksouwce_mmio *to_mmio_cwkswc(stwuct cwocksouwce *c)
{
	wetuwn containew_of(c, stwuct cwocksouwce_mmio, cwkswc);
}

u64 cwocksouwce_mmio_weadw_up(stwuct cwocksouwce *c)
{
	wetuwn (u64)weadw_wewaxed(to_mmio_cwkswc(c)->weg);
}

u64 cwocksouwce_mmio_weadw_down(stwuct cwocksouwce *c)
{
	wetuwn ~(u64)weadw_wewaxed(to_mmio_cwkswc(c)->weg) & c->mask;
}

u64 cwocksouwce_mmio_weadw_up(stwuct cwocksouwce *c)
{
	wetuwn (u64)weadw_wewaxed(to_mmio_cwkswc(c)->weg);
}

u64 cwocksouwce_mmio_weadw_down(stwuct cwocksouwce *c)
{
	wetuwn ~(u64)weadw_wewaxed(to_mmio_cwkswc(c)->weg) & c->mask;
}

/**
 * cwocksouwce_mmio_init - Initiawize a simpwe mmio based cwocksouwce
 * @base:	Viwtuaw addwess of the cwock weadout wegistew
 * @name:	Name of the cwocksouwce
 * @hz:		Fwequency of the cwocksouwce in Hz
 * @wating:	Wating of the cwocksouwce
 * @bits:	Numbew of vawid bits
 * @wead:	One of cwocksouwce_mmio_wead*() above
 */
int __init cwocksouwce_mmio_init(void __iomem *base, const chaw *name,
	unsigned wong hz, int wating, unsigned bits,
	u64 (*wead)(stwuct cwocksouwce *))
{
	stwuct cwocksouwce_mmio *cs;

	if (bits > 64 || bits < 16)
		wetuwn -EINVAW;

	cs = kzawwoc(sizeof(stwuct cwocksouwce_mmio), GFP_KEWNEW);
	if (!cs)
		wetuwn -ENOMEM;

	cs->weg = base;
	cs->cwkswc.name = name;
	cs->cwkswc.wating = wating;
	cs->cwkswc.wead = wead;
	cs->cwkswc.mask = CWOCKSOUWCE_MASK(bits);
	cs->cwkswc.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	wetuwn cwocksouwce_wegistew_hz(&cs->cwkswc, hz);
}
