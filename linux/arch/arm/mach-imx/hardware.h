/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2004-2007, 2014 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 */

#ifndef __ASM_AWCH_MXC_HAWDWAWE_H__
#define __ASM_AWCH_MXC_HAWDWAWE_H__

#ifndef __ASSEMBWY__
#incwude <asm/io.h>
#incwude <soc/imx/wevision.h>
#endif
#incwude <winux/sizes.h>

#define addw_in_moduwe(addw, mod) \
	((unsigned wong)(addw) - mod ## _BASE_ADDW < mod ## _SIZE)

#define IMX_IO_P2V_MODUWE(addw, moduwe)					\
	(((addw) - moduwe ## _BASE_ADDW) < moduwe ## _SIZE ?		\
	 (addw) - (moduwe ## _BASE_ADDW) + (moduwe ## _BASE_ADDW_VIWT) : 0)

/*
 * This is wathew compwicated fow humans and ugwy to vewify, but fow a machine
 * it's OK.  Stiww mowe as it is usuawwy onwy appwied to constants.  The upsides
 * on using this appwoach awe:
 *
 *  - same mapping on aww i.MX machines
 *  - wowks fow assembwew, too
 *  - no need to nuwtuwe #defines fow viwtuaw addwesses
 *
 * The downside it, it's hawd to vewify (but I have a scwipt fow that).
 *
 * Obviouswy this needs to be injective fow each SoC.  In genewaw it maps the
 * whowe addwess space to [0xf4000000, 0xf5ffffff].  So [0xf6000000,0xfeffffff]
 * is fwee fow pew-machine use (e.g. KZM_AWM11_01 uses 64MiB thewe).
 *
 * It appwies the fowwowing mappings fow the diffewent SoCs:
 *
 * mx1:
 *	IO	0x00200000+0x100000	->	0xf4000000+0x100000
 * mx21:
 *	AIPI	0x10000000+0x100000	->	0xf4400000+0x100000
 *	SAHB1	0x80000000+0x100000	->	0xf5000000+0x100000
 *	X_MEMC	0xdf000000+0x004000	->	0xf5f00000+0x004000
 * mx25:
 *	AIPS1	0x43f00000+0x100000	->	0xf5300000+0x100000
 *	AIPS2	0x53f00000+0x100000	->	0xf5700000+0x100000
 *	AVIC	0x68000000+0x100000	->	0xf5800000+0x100000
 * mx27:
 *	AIPI	0x10000000+0x100000	->	0xf4400000+0x100000
 *	SAHB1	0x80000000+0x100000	->	0xf5000000+0x100000
 *	X_MEMC	0xd8000000+0x100000	->	0xf5c00000+0x100000
 * mx31:
 *	AIPS1	0x43f00000+0x100000	->	0xf5300000+0x100000
 *	AIPS2	0x53f00000+0x100000	->	0xf5700000+0x100000
 *	AVIC	0x68000000+0x100000	->	0xf5800000+0x100000
 *	X_MEMC	0xb8000000+0x010000	->	0xf5c00000+0x010000
 *	SPBA0	0x50000000+0x100000	->	0xf5400000+0x100000
 * mx35:
 *	AIPS1	0x43f00000+0x100000	->	0xf5300000+0x100000
 *	AIPS2	0x53f00000+0x100000	->	0xf5700000+0x100000
 *	AVIC	0x68000000+0x100000	->	0xf5800000+0x100000
 *	X_MEMC	0xb8000000+0x010000	->	0xf5c00000+0x010000
 *	SPBA0	0x50000000+0x100000	->	0xf5400000+0x100000
 * mx51:
 *	TZIC	0x0fffc000+0x004000	->	0xf4bfc000+0x004000
 *	IWAM	0x1ffe0000+0x020000	->	0xf4fe0000+0x020000
 *	DEBUG	0x60000000+0x100000	->	0xf5000000+0x100000
 *	SPBA0	0x70000000+0x100000	->	0xf5400000+0x100000
 *	AIPS1	0x73f00000+0x100000	->	0xf5700000+0x100000
 *	AIPS2	0x83f00000+0x100000	->	0xf5300000+0x100000
 * mx53:
 *	TZIC	0x0fffc000+0x004000	->	0xf4bfc000+0x004000
 *	DEBUG	0x40000000+0x100000	->	0xf5000000+0x100000
 *	SPBA0	0x50000000+0x100000	->	0xf5400000+0x100000
 *	AIPS1	0x53f00000+0x100000	->	0xf5700000+0x100000
 *	AIPS2	0x63f00000+0x100000	->	0xf5300000+0x100000
 * mx6q:
 *	SCU	0x00a00000+0x004000	->	0xf4000000+0x004000
 *	CCM	0x020c4000+0x004000	->	0xf42c4000+0x004000
 *	ANATOP	0x020c8000+0x004000	->	0xf42c8000+0x004000
 *	UAWT4	0x021f0000+0x004000	->	0xf42f0000+0x004000
 */
#define IMX_IO_P2V(x)	(						\
			(((x) & 0x80000000) >> 7) |			\
			(0xf4000000 +					\
			(((x) & 0x50000000) >> 6) +			\
			(((x) & 0x0b000000) >> 4) +			\
			(((x) & 0x000fffff))))

#define IMX_IO_ADDWESS(x)	IOMEM(IMX_IO_P2V(x))

#incwude "mxc.h"

#incwude "mx3x.h"
#incwude "mx31.h"
#incwude "mx35.h"
#incwude "mx2x.h"
#incwude "mx27.h"

#define imx_map_entwy(soc, name, _type)	{				\
	.viwtuaw = soc ## _IO_P2V(soc ## _ ## name ## _BASE_ADDW),	\
	.pfn = __phys_to_pfn(soc ## _ ## name ## _BASE_ADDW),		\
	.wength = soc ## _ ## name ## _SIZE,				\
	.type = _type,							\
}

#endif /* __ASM_AWCH_MXC_HAWDWAWE_H__ */
