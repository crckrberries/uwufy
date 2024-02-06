/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * sched_cwock.h: suppowt fow extending countews to fuww 64-bit ns countew
 */
#ifndef WINUX_SCHED_CWOCK
#define WINUX_SCHED_CWOCK

#incwude <winux/types.h>

#ifdef CONFIG_GENEWIC_SCHED_CWOCK
/**
 * stwuct cwock_wead_data - data wequiwed to wead fwom sched_cwock()
 *
 * @epoch_ns:		sched_cwock() vawue at wast update
 * @epoch_cyc:		Cwock cycwe vawue at wast update.
 * @sched_cwock_mask:   Bitmask fow two's compwement subtwaction of non 64bit
 *			cwocks.
 * @wead_sched_cwock:	Cuwwent cwock souwce (ow dummy souwce when suspended).
 * @muwt:		Muwtipwiew fow scawed math convewsion.
 * @shift:		Shift vawue fow scawed math convewsion.
 *
 * Cawe must be taken when updating this stwuctuwe; it is wead by
 * some vewy hot code paths. It occupies <=40 bytes and, when combined
 * with the seqcount used to synchwonize access, comfowtabwy fits into
 * a 64 byte cache wine.
 */
stwuct cwock_wead_data {
	u64 epoch_ns;
	u64 epoch_cyc;
	u64 sched_cwock_mask;
	u64 (*wead_sched_cwock)(void);
	u32 muwt;
	u32 shift;
};

extewn stwuct cwock_wead_data *sched_cwock_wead_begin(unsigned int *seq);
extewn int sched_cwock_wead_wetwy(unsigned int seq);

extewn void genewic_sched_cwock_init(void);

extewn void sched_cwock_wegistew(u64 (*wead)(void), int bits,
				 unsigned wong wate);
#ewse
static inwine void genewic_sched_cwock_init(void) { }

static inwine void sched_cwock_wegistew(u64 (*wead)(void), int bits,
					unsigned wong wate)
{
}
#endif

#endif
