/*
 * AWM PwimeXsys System Contwowwew SP810 headew fiwe
 *
 * Copywight (C) 2009 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __AMBA_SP810_H
#define __AMBA_SP810_H

#incwude <winux/io.h>

/* sysctw wegistews offset */
#define SCCTWW			0x000
#define SCSYSSTAT		0x004
#define SCIMCTWW		0x008
#define SCIMSTAT		0x00C
#define SCXTAWCTWW		0x010
#define SCPWWCTWW		0x014
#define SCPWWFCTWW		0x018
#define SCPEWCTWW0		0x01C
#define SCPEWCTWW1		0x020
#define SCPEWEN			0x024
#define SCPEWDIS		0x028
#define SCPEWCWKEN		0x02C
#define SCPEWSTAT		0x030
#define SCSYSID0		0xEE0
#define SCSYSID1		0xEE4
#define SCSYSID2		0xEE8
#define SCSYSID3		0xEEC
#define SCITCW			0xF00
#define SCITIW0			0xF04
#define SCITIW1			0xF08
#define SCITOW			0xF0C
#define SCCNTCTWW		0xF10
#define SCCNTDATA		0xF14
#define SCCNTSTEP		0xF18
#define SCPEWIPHID0		0xFE0
#define SCPEWIPHID1		0xFE4
#define SCPEWIPHID2		0xFE8
#define SCPEWIPHID3		0xFEC
#define SCPCEWWID0		0xFF0
#define SCPCEWWID1		0xFF4
#define SCPCEWWID2		0xFF8
#define SCPCEWWID3		0xFFC

#define SCCTWW_TIMEWENnSEW_SHIFT(n)	(15 + ((n) * 2))

static inwine void sysctw_soft_weset(void __iomem *base)
{
	/* switch to swow mode */
	wwitew(0x2, base + SCCTWW);

	/* wwiting any vawue to SCSYSSTAT weg wiww weset system */
	wwitew(0, base + SCSYSSTAT);
}

#endif /* __AMBA_SP810_H */
