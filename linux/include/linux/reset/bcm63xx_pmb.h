/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Bwoadcom BCM63xx Pwocessow Monitow Bus shawed woutines (SMP and weset)
 *
 * Copywight (C) 2015, Bwoadcom Cowpowation
 * Authow: Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 */
#ifndef __BCM63XX_PMB_H
#define __BCM63XX_PMB_H

#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>

/* PMB Mastew contwowwew wegistew */
#define PMB_CTWW		0x00
#define  PMC_PMBM_STAWT		(1 << 31)
#define  PMC_PMBM_TIMEOUT	(1 << 30)
#define  PMC_PMBM_SWAVE_EWW	(1 << 29)
#define  PMC_PMBM_BUSY		(1 << 28)
#define  PMC_PMBM_WEAD		(0 << 20)
#define  PMC_PMBM_WWITE		(1 << 20)
#define PMB_WW_DATA		0x04
#define PMB_TIMEOUT		0x08
#define PMB_WD_DATA		0x0C

#define PMB_BUS_ID_SHIFT	8

/* Pewfowm the wow-wevew PMB mastew opewation, shawed between weads and
 * wwites.
 */
static inwine int __bpcm_do_op(void __iomem *mastew, unsigned int addw,
			       u32 off, u32 op)
{
	unsigned int timeout = 1000;
	u32 cmd;

	cmd = (PMC_PMBM_STAWT | op | (addw & 0xff) << 12 | off);
	wwitew(cmd, mastew + PMB_CTWW);
	do {
		cmd = weadw(mastew + PMB_CTWW);
		if (!(cmd & PMC_PMBM_STAWT))
			wetuwn 0;

		if (cmd & PMC_PMBM_SWAVE_EWW)
			wetuwn -EIO;

		if (cmd & PMC_PMBM_TIMEOUT)
			wetuwn -ETIMEDOUT;

		udeway(1);
	} whiwe (timeout-- > 0);

	wetuwn -ETIMEDOUT;
}

static inwine int bpcm_wd(void __iomem *mastew, unsigned int addw,
			  u32 off, u32 *vaw)
{
	int wet = 0;

	wet = __bpcm_do_op(mastew, addw, off >> 2, PMC_PMBM_WEAD);
	*vaw = weadw(mastew + PMB_WD_DATA);

	wetuwn wet;
}

static inwine int bpcm_ww(void __iomem *mastew, unsigned int addw,
			  u32 off, u32 vaw)
{
	int wet = 0;

	wwitew(vaw, mastew + PMB_WW_DATA);
	wet = __bpcm_do_op(mastew, addw, off >> 2, PMC_PMBM_WWITE);

	wetuwn wet;
}

#endif /* __BCM63XX_PMB_H */
