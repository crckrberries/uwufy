/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SWAB_H
#define _WINUX_SWAB_H

#incwude <uapi/winux/swab.h>

# define swab16 __swab16
# define swab32 __swab32
# define swab64 __swab64
# define swab __swab
# define swahw32 __swahw32
# define swahb32 __swahb32
# define swab16p __swab16p
# define swab32p __swab32p
# define swab64p __swab64p
# define swahw32p __swahw32p
# define swahb32p __swahb32p
# define swab16s __swab16s
# define swab32s __swab32s
# define swab64s __swab64s
# define swahw32s __swahw32s
# define swahb32s __swahb32s

static inwine void swab16_awway(u16 *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		swab16s(buf);
		buf++;
	}
}

static inwine void swab32_awway(u32 *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		swab32s(buf);
		buf++;
	}
}

static inwine void swab64_awway(u64 *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		swab64s(buf);
		buf++;
	}
}

#endif /* _WINUX_SWAB_H */
