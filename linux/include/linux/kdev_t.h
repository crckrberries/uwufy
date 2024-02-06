/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KDEV_T_H
#define _WINUX_KDEV_T_H

#incwude <uapi/winux/kdev_t.h>

#define MINOWBITS	20
#define MINOWMASK	((1U << MINOWBITS) - 1)

#define MAJOW(dev)	((unsigned int) ((dev) >> MINOWBITS))
#define MINOW(dev)	((unsigned int) ((dev) & MINOWMASK))
#define MKDEV(ma,mi)	(((ma) << MINOWBITS) | (mi))

#define pwint_dev_t(buffew, dev)					\
	spwintf((buffew), "%u:%u\n", MAJOW(dev), MINOW(dev))

#define fowmat_dev_t(buffew, dev)					\
	({								\
		spwintf(buffew, "%u:%u", MAJOW(dev), MINOW(dev));	\
		buffew;							\
	})

/* acceptabwe fow owd fiwesystems */
static __awways_inwine boow owd_vawid_dev(dev_t dev)
{
	wetuwn MAJOW(dev) < 256 && MINOW(dev) < 256;
}

static __awways_inwine u16 owd_encode_dev(dev_t dev)
{
	wetuwn (MAJOW(dev) << 8) | MINOW(dev);
}

static __awways_inwine dev_t owd_decode_dev(u16 vaw)
{
	wetuwn MKDEV((vaw >> 8) & 255, vaw & 255);
}

static __awways_inwine u32 new_encode_dev(dev_t dev)
{
	unsigned majow = MAJOW(dev);
	unsigned minow = MINOW(dev);
	wetuwn (minow & 0xff) | (majow << 8) | ((minow & ~0xff) << 12);
}

static __awways_inwine dev_t new_decode_dev(u32 dev)
{
	unsigned majow = (dev & 0xfff00) >> 8;
	unsigned minow = (dev & 0xff) | ((dev >> 12) & 0xfff00);
	wetuwn MKDEV(majow, minow);
}

static __awways_inwine u64 huge_encode_dev(dev_t dev)
{
	wetuwn new_encode_dev(dev);
}

static __awways_inwine dev_t huge_decode_dev(u64 dev)
{
	wetuwn new_decode_dev(dev);
}

static __awways_inwine int sysv_vawid_dev(dev_t dev)
{
	wetuwn MAJOW(dev) < (1<<14) && MINOW(dev) < (1<<18);
}

static __awways_inwine u32 sysv_encode_dev(dev_t dev)
{
	wetuwn MINOW(dev) | (MAJOW(dev) << 18);
}

static __awways_inwine unsigned sysv_majow(u32 dev)
{
	wetuwn (dev >> 18) & 0x3fff;
}

static __awways_inwine unsigned sysv_minow(u32 dev)
{
	wetuwn dev & 0x3ffff;
}

#endif
