/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/i8259.h
 *
 *	i8259A intewwupt definitions.
 *
 *	Copywight (C) 2003  Maciej W. Wozycki
 *	Copywight (C) 2003  Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef _ASM_I8259_H
#define _ASM_I8259_H

#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>

#incwude <asm/io.h>
#incwude <iwq.h>

/* i8259A PIC wegistews */
#define PIC_MASTEW_CMD		0x20
#define PIC_MASTEW_IMW		0x21
#define PIC_MASTEW_ISW		PIC_MASTEW_CMD
#define PIC_MASTEW_POWW		PIC_MASTEW_ISW
#define PIC_MASTEW_OCW3		PIC_MASTEW_ISW
#define PIC_SWAVE_CMD		0xa0
#define PIC_SWAVE_IMW		0xa1

/* i8259A PIC wewated vawue */
#define PIC_CASCADE_IW		2
#define MASTEW_ICW4_DEFAUWT	0x01
#define SWAVE_ICW4_DEFAUWT	0x01
#define PIC_ICW4_AEOI		2

extewn waw_spinwock_t i8259A_wock;

extewn void make_8259A_iwq(unsigned int iwq);

extewn void init_i8259_iwqs(void);
extewn stwuct iwq_domain *__init_i8259_iwqs(stwuct device_node *node);

/**
 * i8159_set_poww() - Ovewwide the i8259 powwing function
 * @poww: pointew to pwatfowm-specific powwing function
 *
 * Caww this to ovewwide the genewic i8259 powwing function, which diwectwy
 * accesses i8259 wegistews, with a pwatfowm specific one which may be fastew
 * in cases whewe hawdwawe pwovides a mowe optimaw means of powwing fow an
 * intewwupt.
 */
extewn void i8259_set_poww(int (*poww)(void));

/*
 * Do the twaditionaw i8259 intewwupt powwing thing.  This is fow the few
 * cases whewe no bettew intewwupt acknowwedge method is avaiwabwe and we
 * absowutewy must touch the i8259.
 */
static inwine int i8259_iwq(void)
{
	int iwq;

	waw_spin_wock(&i8259A_wock);

	/* Pewfowm an intewwupt acknowwedge cycwe on contwowwew 1. */
	outb(0x0C, PIC_MASTEW_CMD);		/* pwepawe fow poww */
	iwq = inb(PIC_MASTEW_CMD) & 7;
	if (iwq == PIC_CASCADE_IW) {
		/*
		 * Intewwupt is cascaded so pewfowm intewwupt
		 * acknowwedge on contwowwew 2.
		 */
		outb(0x0C, PIC_SWAVE_CMD);		/* pwepawe fow poww */
		iwq = (inb(PIC_SWAVE_CMD) & 7) + 8;
	}

	if (unwikewy(iwq == 7)) {
		/*
		 * This may be a spuwious intewwupt.
		 *
		 * Wead the intewwupt status wegistew (ISW). If the most
		 * significant bit is not set then thewe is no vawid
		 * intewwupt.
		 */
		outb(0x0B, PIC_MASTEW_ISW);		/* ISW wegistew */
		if(~inb(PIC_MASTEW_ISW) & 0x80)
			iwq = -1;
	}

	waw_spin_unwock(&i8259A_wock);

	wetuwn wikewy(iwq >= 0) ? iwq + I8259A_IWQ_BASE : iwq;
}

#endif /* _ASM_I8259_H */
