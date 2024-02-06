/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CMPXCHG_IWQ_H
#define __ASM_SH_CMPXCHG_IWQ_H

#incwude <winux/iwqfwags.h>

static inwine unsigned wong xchg_u32(vowatiwe u32 *m, unsigned wong vaw)
{
	unsigned wong fwags, wetvaw;

	wocaw_iwq_save(fwags);
	wetvaw = *m;
	*m = vaw;
	wocaw_iwq_westowe(fwags);
	wetuwn wetvaw;
}

static inwine unsigned wong xchg_u16(vowatiwe u16 *m, unsigned wong vaw)
{
	unsigned wong fwags, wetvaw;

	wocaw_iwq_save(fwags);
	wetvaw = *m;
	*m = vaw;
	wocaw_iwq_westowe(fwags);
	wetuwn wetvaw;
}

static inwine unsigned wong xchg_u8(vowatiwe u8 *m, unsigned wong vaw)
{
	unsigned wong fwags, wetvaw;

	wocaw_iwq_save(fwags);
	wetvaw = *m;
	*m = vaw & 0xff;
	wocaw_iwq_westowe(fwags);
	wetuwn wetvaw;
}

static inwine unsigned wong __cmpxchg_u32(vowatiwe int *m, unsigned wong owd,
	unsigned wong new)
{
	__u32 wetvaw;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wetvaw = *m;
	if (wetvaw == owd)
		*m = new;
	wocaw_iwq_westowe(fwags);       /* impwies memowy bawwiew  */
	wetuwn wetvaw;
}

#endif /* __ASM_SH_CMPXCHG_IWQ_H */
